#include <QFile>
#include <QDebug>
#include "icmold.h"
#include "icinstructparam.h"
#include "icfile.h"

struct MoldStepData
{
    MoldStepData():step(-1), begin(-1), end(-1){}
    int step;
    int begin;
    int end;
};

QString ICSubMoldUIItem::ToString() const
{
    QString ret;
    ret += "        " + ICInstructParam::ConvertCommandStr(baseItem_);
    return ret;
}
int ICGroupMoldUIItem::ItemCount() const
{
    int count = 0;
    for(int i = 0; i != topItems_.size(); ++i)
    {
        count += topItems_.at(i).ItemCount();
    }
    return count;
}

void ICGroupMoldUIItem::SetStepNum(int stepNum)
{
    for(int i = 0; i != topItems_.size(); ++i)
    {
        topItems_[i].SetStepNum(stepNum);
    }
}

QList<ICMoldItem> ICGroupMoldUIItem::ToMoldItems() const
{
    QList<ICMoldItem> ret;
    for(int i = 0; i != topItems_.size(); ++i)
    {
        ret.append(topItems_.at(i).ToMoldItems());
    }
    return ret;
}

QStringList ICGroupMoldUIItem::ToStringList() const
{
    QStringList ret;
    for(int i = 0; i != topItems_.size(); ++i)
    {
        ret.append(topItems_.at(i).ToStringList());
    }
    return ret;
}

QList<ICGroupMoldUIItem> ICGroupMoldUIItem::SpliteToTwoGroup(int pos) const
{
    QList<ICGroupMoldUIItem> ret;
    ICGroupMoldUIItem item1;
    ICGroupMoldUIItem item2;
    item1.SetStepNum(StepNum());
    item2.SetStepNum(StepNum() + 1);
    for(int i = 0; i != pos; ++i)
    {
        item1.AddToMoldUIItem(topItems_.at(i));
    }
    for(int i = pos; i != topItems_.size(); ++i)
    {
        item2.AddToMoldUIItem(topItems_.at(i));
    }
    ret<<item1<<item2;
    return ret;
}
void ICGroupMoldUIItem::AddOtherGroup(const ICGroupMoldUIItem &other)
{
    for(int i = 0; i != other.ItemCount(); ++i)
    {
        AddToMoldUIItem(other.at(i));
    }
}

ICMoldItem* ICGroupMoldUIItem::MoldItemAt(int index)
{
    const int topItemCount = TopItemCount();
    for(int i = 0; i != topItemCount; ++i)
    {
        if(index < at(i).ItemCount())
        {
            if(index == 0)
            {
                return at(i).BaseItem();
            }
            else
            {
                return at(i).at(index - 1).BaseItem();
            }
        }
        index -= at(i).ItemCount();
    }
    return NULL;
}

void ICTopMoldUIItem::SetStepNum(int stepNum)
{
    baseItem_.SetNum(stepNum);
    for(int i = 0; i != subItems_.size(); ++i)
    {
        subItems_[i].SetStepNum(stepNum);
    }
}

QStringList ICTopMoldUIItem::ToStringList() const
{
    QStringList ret;
    ret.append(ICInstructParam::ConvertCommandStr(baseItem_));
    for(int i = 0; i != subItems_.size(); ++i)
    {
        ret.append(subItems_.at(i).ToString());
    }
    return ret;
}

bool ICTopMoldUIItem::IsSyncSubItem(int pos) const
{
    if(SubItemCount() == 1)
    {
        return false;
    }
    else if(pos == 0)
    {
        return at(pos + 1).SubNum() == at(pos).SubNum();
    }
    else if(pos == SubItemCount() - 1)
    {
        return at(pos - 1).SubNum() == at(pos).SubNum();
    }
    else
    {
        return (at(pos + 1).SubNum() == at(pos).SubNum()) ||
                at(pos - 1).SubNum() == at(pos).SubNum();
    }
}
//void ICTopMoldUIItem::ReCalSubNum()
//{
//    int currentNum = 0;
//    subItems_[0].SetSubNum(currentNum);
//    for(int i = 1; i != subItems_.size(); ++i)
//    {
//        if(subItems_.at(i).SubNum() == currentNum && subItems_.at(i).IsSyncItem() && subItems_.at(i - 1).IsSyncItem())
//        {
//            subItems_[i].SetSubNum(currentNum);
//        }
//        else
//        {
//            subItems_[i].SetSubNum(++currentNum);
//        }
//    }
//}

QList<ICMoldItem> ICTopMoldUIItem::ToMoldItems() const
{
    QList<ICMoldItem> ret;
    ret.append(baseItem_);
    for(int i = 0; i != subItems_.size(); ++i)
    {
        ret.append(subItems_.at(i).ToMoldItem());
    }
    return ret;
}

ICMold* ICMold::currentMold_ = NULL;
ICMold::ICMold(QObject *parent) :
    QObject(parent)
{
    ICInstructParam::Instance();
    //    axisActions_.append(GX);
    //    axisActions_.append();
}

bool ICMold::ReadMoldFile(const QString &fileName, bool isLoadParams)
{
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        return false;
    }
    //    QTextStream fs(&file);
    //    moldName_ = fileName;
    QString content = QString::fromUtf8(file.readAll());
    file.close();
    //    content = content.remove('\r');

    if(content.isNull())
    {
        qDebug("mold null");
        return false;
    }
    QStringList records = content.split("\n", QString::SkipEmptyParts);
    if(records.size() < 1)
    {
        qDebug("mold less than 4");
        return false;
    }
    QStringList items;
    ICMoldItem moldItem;
    qDebug("before read");
    qDebug()<<"size"<<records.size();
    QList<ICMoldItem> tempmoldContent;
    QString itemsContent;
    for(int i = 0; i != records.size(); ++i)
    {
        itemsContent = records.at(i);
        items = itemsContent.split(' ', QString::SkipEmptyParts);
        if(items.size() > 12)
        {
            QStringList commentItem = items.mid(11);
            while(items.size() > 11)
                items.removeAt(11);
            items.append(commentItem.join(" "));
        }
        if(items.size() != 10 &&
                items.size() != 11 &&
                items.size() != 12)
        {
            qDebug()<<i<<"th line size wrong";
            return false;
        }
        moldItem.SetValue(items.at(0).toUInt(),
                          items.at(1).toUInt(),
                          items.at(2).toUInt(),
                          items.at(3).toUInt(),
                          items.at(4).toUInt(),
                          items.at(5).toUInt(),
                          items.at(6).toUInt(),
                          items.at(7).toUInt(),
                          items.at(8).toUInt(),
                          items.at(9).toUInt());
        if(items.size() > 10)
        {
            moldItem.SetFlag(items.at(10).toUInt());
        }
        if(items.size() > 11)
        {
            moldItem.SetComment(items.at(11));
        }
        tempmoldContent.append(moldItem);
    }
    qDebug("read ok");
    bool ret = true;
    if(isLoadParams)
    {
        QString moldParamFileName = fileName;
        moldParamFileName.chop(3);
        moldParamFileName += "fnc";
        ret = ReadMoldParamsFile(moldParamFileName);
        emit MoldNumberParamChanged();
    }
    if(ret == true)
    {
        moldContent_ = tempmoldContent;
        moldName_ = fileName;
    }
    QString simpleTeachFileName = fileName;
    simpleTeachFileName.chop(3);
    simpleTeachFileName += "st";
    ReadSimpleTeachFile(simpleTeachFileName);

    Compile();
    return ret;
}

bool ICMold::ReadMoldParamsFile(const QString &fileName)
{
    //    moldParamName_ = fileName;
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        return false;
    }
    QString fileContent = file.readAll();
    file.close();
    //    fileContent = fileContent.remove('\r');

    QStringList items = fileContent.split('\n', QString::SkipEmptyParts);
    if(items.size() != MoldParamCount + StackParamCount * 4 + 1)
    {
        return false;
    }
    moldParams_.clear();
    stackParams_.clear();
    for(int i = 0; i != MoldParamCount; ++i)
    {
        moldParams_.append(items.at(i).toUInt());
    }
    //    Q_ASSERT_X(items.size() == 58, "ICMold::ReadMoldParamFile", "fnc file is not correct!");

    QList<int> stackParam;
    int base;
    int count;
    for(int i = 0; i != 4; ++i)
    {
        base = MoldParamCount + StackParamCount * i;
        count = base + StackParamCount;
        stackParam.clear();
        for(int j = base; j != count; ++j)
        {
            stackParam.append(items.at(j).toUInt());
        }
        stackParams_.append(stackParam);
    }
    //    moldParams_[CheckClip5] = 0;
    //    moldParams_[CheckClip6] = 0;
    checkSum_ = items.last().toUInt();
    //    UpdateSyncSum();
    moldParamName_ = fileName;
    return true;
}

bool ICMold::ReadSimpleTeachFile(const QString &fileName)
{
    QFile file(fileName);
    simpleTeachFileName_ = fileName;
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        simpleTeachData_.usedMainArm = true;
        simpleTeachData_.usedMainArmOutlet = false;
        simpleTeachData_.usedSubArm = false;
        simpleTeachData_.usedCutOutlet = false;
        simpleTeachData_.stdPos.b.x1 = 0;
        simpleTeachData_.stdPos.b.x1D = 0;
        simpleTeachData_.stdPos.b.x1S = 80;
        simpleTeachData_.stdPos.b.y1 = 0;
        simpleTeachData_.stdPos.b.y1D = 0;
        simpleTeachData_.stdPos.b.y1S = 80;
        simpleTeachData_.stdPos.b.z = 0;
        simpleTeachData_.stdPos.b.zD = 0;
        simpleTeachData_.stdPos.b.zS = 80;
        simpleTeachData_.stdPos.b.x2 = 0;
        simpleTeachData_.stdPos.b.x2D = 0;
        simpleTeachData_.stdPos.b.x2S = 80;
        simpleTeachData_.stdPos.b.y2 = 0;
        simpleTeachData_.stdPos.b.y2D = 0;
        simpleTeachData_.stdPos.b.y2S = 80;

        simpleTeachData_.getProductPos.pos.b.x1 = 0;
        simpleTeachData_.getProductPos.pos.b.x1D = 0;
        simpleTeachData_.getProductPos.pos.b.x1S = 80;
        simpleTeachData_.getProductPos.pos.b.y1 = 0;
        simpleTeachData_.getProductPos.pos.b.y1D = 0;
        simpleTeachData_.getProductPos.pos.b.y1S = 80;
        simpleTeachData_.getProductPos.pos.b.z = 0;
        simpleTeachData_.getProductPos.pos.b.zD = 0;
        simpleTeachData_.getProductPos.pos.b.zS = 80;
        simpleTeachData_.getProductPos.pos.b.x2 = 0;
        simpleTeachData_.getProductPos.pos.b.x2D = 0;
        simpleTeachData_.getProductPos.pos.b.x2S = 80;
        simpleTeachData_.getProductPos.pos.b.y2 = 0;
        simpleTeachData_.getProductPos.pos.b.y2D = 0;
        simpleTeachData_.getProductPos.pos.b.y2S = 80;

        simpleTeachData_.getOutletPos.pos.b.x1 = 0;
        simpleTeachData_.getOutletPos.pos.b.x1D = 0;
        simpleTeachData_.getOutletPos.pos.b.x1S = 80;
        simpleTeachData_.getOutletPos.pos.b.y1 = 0;
        simpleTeachData_.getOutletPos.pos.b.y1D = 0;
        simpleTeachData_.getOutletPos.pos.b.y1S = 80;
        simpleTeachData_.getOutletPos.pos.b.z = 0;
        simpleTeachData_.getOutletPos.pos.b.zD = 0;
        simpleTeachData_.getOutletPos.pos.b.zS = 80;
        simpleTeachData_.getOutletPos.pos.b.x2 = 0;
        simpleTeachData_.getOutletPos.pos.b.x2D = 0;
        simpleTeachData_.getOutletPos.pos.b.x2S = 80;
        simpleTeachData_.getOutletPos.pos.b.y2 = 0;
        simpleTeachData_.getOutletPos.pos.b.y2D = 0;
        simpleTeachData_.getOutletPos.pos.b.y2S = 80;

        simpleTeachData_.posBH.b.x1 = 0;
        simpleTeachData_.posBH.b.x1D = 0;
        simpleTeachData_.posBH.b.x1S = 80;
        simpleTeachData_.posBH.b.y1 = 0;
        simpleTeachData_.posBH.b.y1D = 0;
        simpleTeachData_.posBH.b.y1S = 80;
        simpleTeachData_.posBH.b.z = 0;
        simpleTeachData_.posBH.b.zD = 0;
        simpleTeachData_.posBH.b.zS = 80;
        simpleTeachData_.posBH.b.x2 = 0;
        simpleTeachData_.posBH.b.x2D = 0;
        simpleTeachData_.posBH.b.x2S = 80;
        simpleTeachData_.posBH.b.y2 = 0;
        simpleTeachData_.posBH.b.y2D = 0;
        simpleTeachData_.posBH.b.y2S = 80;

        simpleTeachData_.releaseProductPosList.append(simpleTeachData_.getProductPos);
        simpleTeachData_.releaseOutletPosList.append(simpleTeachData_.getOutletPos);

        simpleTeachData_.releaseProductYUp = 0;
        simpleTeachData_.releaseProductYUpS = 80;
        simpleTeachData_.releaseProductYUpD = 0;

        simpleTeachData_.releaseOutletYUp = 0;
        simpleTeachData_.releaseOutletYUpS = 80;
        simpleTeachData_.releaseOutletYUpD = 0;

        simpleTeachData_.cutOutletYUp = 0;
        simpleTeachData_.cutOutletYUpS = 80;
        simpleTeachData_.cutOutletYUpD = 0;

//        simpleTeachData_.cutTime.all = 50;
        simpleTeachData_.cutTime.b.cutOnTime = 50;
        simpleTeachData_.cutTime.b.cutAfterPullTime = 10;
        simpleTeachData_.cutTime.b.pullOffAfterCutOffTime = 0;

        simpleTeachData_.afterGetX1 = 0;
        simpleTeachData_.afterGetX1S = 80;
        simpleTeachData_.afterGetX1D = 0;

        simpleTeachData_.afterGetX2 = 0;
        simpleTeachData_.afterGetX2S = 80;
        simpleTeachData_.afterGetX2D = 0;

        simpleTeachData_.afterGetY1 = 0;
        simpleTeachData_.afterGetY1S = 80;
        simpleTeachData_.afterGetY1D = 0;

        simpleTeachData_.afterGetY2 = 0;
        simpleTeachData_.afterGetY2S = 80;
        simpleTeachData_.afterGetY2D = 0;
        return true;
    }

    QString simpleTeachContent = file.readAll();
    qDebug()<<simpleTeachContent;
    file.close();
    simpleTeachData_.InitFromByteArray(simpleTeachContent);
    return true;

}

bool ICMold::SaveMoldFile(bool isSaveParams)
{
    bool ret = false;
    Compile();
    //    MoldReSum();
    QByteArray toWrite;
    if(moldContent_.size() < 1)
    {
        qDebug("mold content less than 4 when save");
        return false;
    }
    for(int i = 0; i != moldContent_.size(); ++i)
    {
        toWrite += moldContent_.at(i).ToString() + "\n";
    }
    ICFile file(moldName_);
    ret = file.ICWrite(toWrite);
    if(isSaveParams)
    {
        SaveMoldParamsFile();
    }
    return ret;
}

bool ICMold::SaveMoldParamsFile()
{
    bool ret = false;
    moldParams_[CheckClip5] = 0;
    moldParams_[CheckClip6] = 0;
    UpdateSyncSum();
    QByteArray toWrite;
    QList<int> allParams = AllParams();
    for(int i = 0; i != allParams.size(); ++i)
    {
        toWrite += QByteArray::number(allParams.at(i)) + "\n";
    }
    ICFile file(moldParamName_);
    ret = file.ICWrite(toWrite);
    return ret;
}

bool ICMold::SaveSimpleTeachFile()
{
    QByteArray toWrite = simpleTeachData_.toByteArray();
    ICFile file(simpleTeachFileName_);
    return file.ICWrite(toWrite);
}

uint ICMold::SyncAct() const
{
    uint ret = 0;
    for(int i = 0; i != toSentContent_.size(); ++i)
    {
        //        if(toSentContent_.at(i).Action() != ACTCOMMENT)
        ret += toSentContent_.at(i).GMVal();
    }
    return ret;
}

uint ICMold::SyncSum() const
{
    uint ret = 0;
    for(int i = 0; i != toSentContent_.size(); ++i)
    {
        //        if(toSentContent_.at(i).Action() != ACTCOMMENT)
        ret += toSentContent_.at(i).Sum();
    }
    return ret;
}


void ICMold::Insert(const QList<ICMoldItem> &items, QList<ICMoldItem> &sourceItems)
{
    Q_UNUSED(items)
    Q_UNUSED(sourceItems)
}

void ICMold::Modify(const QList<ICMoldItem> &items, QList<ICMoldItem> &sourceItems)
{
    Q_UNUSED(items)
    Q_UNUSED(sourceItems)
}

void ICMold::Delete(int step, QList<ICMoldItem> &sourceItems)
{
    Q_UNUSED(step)
    Q_UNUSED(sourceItems)
}

void ICMold::MoldReSum(QList<ICMoldItem> &items)
{
    int seq = 0;
    for(int i = 0; i != items.size(); ++i)
    {
        items[i].SetSeq(seq);
        items[i].ReSum();
        if(items.at(i).Action() != ACTCOMMENT)
            ++seq;
    }
}

void ICMold::UpdateSyncSum()
{
    int sum = 0;
    for(int i = 0; i != moldParams_.size(); ++i)
    {
        sum += moldParams_.at(i);
    }
    for(int i = 0; i != stackParams_.size(); ++i)
    {
        for(int j = 0; j != stackParams_.at(i).size(); ++j)
        {
            sum += stackParams_.at(i).at(j);
        }
    }
    //    sum += checkSum_;
    checkSum_ = (-sum) & 0xFFFF;
}

QList<ICMoldItem> ICMold::UIItemToMoldItem(const QList<ICGroupMoldUIItem> &items)
{
    QList<ICMoldItem> ret;
    for(int i = 0; i != items.size(); ++i)
    {
        ret.append(items.at(i).ToMoldItems());
    }
    return ret;
}

QList<ICGroupMoldUIItem> ICMold::MoldItemToUIItem(const QList<ICMoldItem> &items)
{
    QList<ICTopMoldUIItem> ret;
    QList<ICGroupMoldUIItem> groupRet;
    ICTopMoldUIItem topItem;
    ICSubMoldUIItem subItem;
    ICMoldItem moldItem;
    for(int i = 0; i != items.size(); ++i)
    {
        moldItem = items.at(i);
        if(moldItem.SubNum() == 255)
        {
            topItem.SetBaseItem(moldItem);
            ret.append(topItem);
        }
        else
        {
            if(moldItem.SubNum() == items.at(i + 1).SubNum())
            {
                subItem.SetSyncItem(true);
            }
            subItem.SetBaseItem(moldItem);
            if(ret.isEmpty())
            {
                return groupRet;
            }
            ret.last().AddSubMoldUIItem(subItem);
        }
    }
    ICGroupMoldUIItem groupItem;
    if(ret.isEmpty())
    {
        return groupRet;
    }
    groupItem.AddToMoldUIItem(ret.first());
    groupRet.append(groupItem);
    for(int i = 1; i != ret.size(); ++i)
    {
        topItem = ret.at(i);
        if(topItem.StepNum() == groupRet.last().StepNum())
        {
            groupRet.last().AddToMoldUIItem(topItem);
        }
        else
        {
            ICGroupMoldUIItem newItem;
            newItem.AddToMoldUIItem(topItem);
            groupRet.append(newItem);
        }
    }
    return groupRet;
}

QStringList ICMold::UIItemsToStringList(const QList<ICGroupMoldUIItem> &items)
{
    QStringList ret;
    ICGroupMoldUIItem item;
    for(int i = 0; i != items.size(); ++i)
    {
        item = items.at(i);
        ret.append(item.ToStringList());
    }
    return ret;
}


int ICGroupMoldUIItem::RunableTopItemCount()
{
    int ret = 0;
    for(int i = 0 ; i != topItems_.size(); ++i)
    {
        if(topItems_[i].BaseItem()->Action() != ICMold::ACTCOMMENT)
        {
            ++ret;
        }
    }
    return ret;
}

void ICMold::Compile()
{
    QMap<int, int> flagToSetp;
    QList<int> conditionPos;
    int stepOffset = 0;
    ICMoldItem item;
    ICMoldItem toSentItem;
    QList<ICMoldItem> tmpContent = moldContent_;
    stepMap_.clear();
    for(int i = 0; i != tmpContent.size(); ++i)
    {
        moldContent_[i].SetSeq(i);
        item = tmpContent.at(i);
        tmpContent[i].SetNum(item.Num() - stepOffset);
        qDebug()<<tmpContent[i].ToString();
        stepMap_.insert(tmpContent.at(i).Num(), moldContent_.at(i).Num());
        if(item.Action() == ACTCOMMENT)
        {
            qDebug()<<item.Flag()<<item.Num();
            flagToSetp.insert(item.Flag(), tmpContent[i].Num());
            if(i == 0 && moldContent_.at(i + 1).Num() == item.Num())
            {
                continue;
            }
            else if(moldContent_.at(i + 1).Num() == item.Num() ||
                    moldContent_.at(i - 1).Num() == item.Num())
            {
                continue;
            }
            else
                ++stepOffset;
            continue;
        }
        else if(tmpContent.at(i).Action() == ACTCHECKINPUT)
        {
            conditionPos.append(i);
        }
    }
    int returnStep;
    for(int i = 0; i != conditionPos.size(); ++i)
    {
        qDebug()<<moldContent_.at(conditionPos.at(i)).Flag()<<tmpContent.at(conditionPos.at(i)).Num();
        returnStep = flagToSetp.value(moldContent_.at(conditionPos.at(i)).Flag(), 0) -
                tmpContent.at(conditionPos.at(i)).Num();
        moldContent_[conditionPos.at(i)].SetDVal(
                    returnStep);
        tmpContent[conditionPos.at(i)].SetDVal(
                    returnStep);
    }
    toSentContent_.clear();
    for(int i = 0; i < moldContent_.size(); ++i)
    {
        toSentItem = tmpContent.at(i);
        if(toSentItem.Action() == ACTCOMMENT)
            continue;
        toSentItem.SetSeq(toSentContent_.size());
        toSentItem.ReSum();
        toSentContent_.append(toSentItem);
    }
}

int ICMold::ToHostSeq(int seq) const
{
    int countComment = 0;
    for(int i = 0; i < seq; ++i)
    {
        if(moldContent_.at(i).Action() == ACTCOMMENT)
            ++countComment;
    }
    return seq - countComment;
}

int ICMold::ToHostNum(int seq) const
{
    return toSentContent_.at(seq).Num();
}

bool AxisPosData::InitFromByteArray(const QString &text)
{
    QStringList lineItems = text.split(",", QString::SkipEmptyParts);
    return InitFormStringItems(lineItems);
}

bool AxisPosData::InitFormStringItems(const QList<QString> &items)
{
    if(items.size() != AXISPOSDATASIZE) return false;
    for(int i = 0; i < AXISPOSDATASIZE; ++i)
    {
        all[i] = items.at(i).toInt();
    }
    return true;
}

bool ReleasePosData::InitFromByteArray(const QString &text)
{
    QStringList lineItems = text.split(",", QString::SkipEmptyParts);
    if(!pos.InitFormStringItems(lineItems.mid(0, AXISPOSDATASIZE))) return false;
    int fixtureCount = lineItems.size();
    if((fixtureCount - AXISPOSDATASIZE) % 2 != 0) return false;
    for(int i = AXISPOSDATASIZE; i < fixtureCount; i +=2)
    {
        fixtureConfis.append(qMakePair<int, bool>(lineItems.at(i).toInt(),
                                                  lineItems.at(i + 1).toInt()));
    }
    return true;
}

bool SimpleTeachData::InitFromByteArray(const QString &text)
{
    QStringList contentList = text.split("\n");
    if(contentList.size() < 9) return false;
    QStringList lineItems = contentList.at(0).split(",", QString::SkipEmptyParts);
    if(lineItems.size() != 4) return false;
    usedMainArm = lineItems.at(0).toInt();
    usedMainArmOutlet = lineItems.at(1).toInt();
    usedSubArm = lineItems.at(2).toInt();
    usedCutOutlet = lineItems.at(3).toInt();

    if(!stdPos.InitFromByteArray(contentList.at(1))) return false;
    if(!getProductPos.InitFromByteArray(contentList.at(2))) return false;
    if(!getOutletPos.InitFromByteArray(contentList.at(3))) return false;
    if(!posBH.InitFromByteArray(contentList.at(4))) return false;
    QStringList releasePos = contentList.at(5).split("|", QString::SkipEmptyParts);
    for(int i = 0; i < releasePos.size(); ++i)
    {
        ReleasePosData data;
        if(!data.InitFromByteArray(releasePos.at(i))) return false;
        releaseProductPosList.append(data);
    }
    releasePos = contentList.at(6).split("|", QString::SkipEmptyParts);
    for(int i = 0; i < releasePos.size(); ++i)
    {
        ReleasePosData data;
        if(!data.InitFromByteArray(releasePos.at(i))) return false;
        releaseOutletPosList.append(data);
    }
    releasePos = contentList.at(7).split("|", QString::SkipEmptyParts);
    for(int i = 0; i < releasePos.size(); ++i)
    {
        ReleasePosData data;
        if(!data.InitFromByteArray(releasePos.at(i))) return false;
        cutOutletPosList.append(data);
    }
    lineItems = contentList.at(8).split(",");
//    if(lineItems.size() != 10) return false;
    releaseProductYUp = lineItems.at(0).toInt();
    releaseProductYUpS = lineItems.at(1).toInt();
    releaseProductYUpD = lineItems.at(2).toInt();
    releaseOutletYUp = lineItems.at(3).toInt();
    releaseOutletYUpS = lineItems.at(4).toInt();
    releaseOutletYUpD = lineItems.at(5).toInt();
    cutOutletYUp = lineItems.at(6).toInt();
    cutOutletYUpS = lineItems.at(7).toInt();
    cutOutletYUpD = lineItems.at(8).toInt();
    cutTime.all = lineItems.at(9).toInt();
    if(lineItems.size() < 24)
    {
        afterGetX1 = 0;
        afterGetX1S = 80;
        afterGetX1D = 0;

        afterGetX2 = 0;
        afterGetX2S = 80;
        afterGetX2D = 0;

        afterGetY1 = 0;
        afterGetY1S = 80;
        afterGetY1D = 0;

        afterGetY2 = 0;
        afterGetY2S = 80;
        afterGetY2D = 0;

    }
    else
    {
        afterGetX1 = lineItems.at(10).toInt();
        afterGetX1S = lineItems.at(11).toInt();
        afterGetX1D = lineItems.at(12).toInt();
        afterGetX2 = lineItems.at(13).toInt();
        afterGetX2S = lineItems.at(14).toInt();
        afterGetX2D = lineItems.at(15).toInt();
        usedAfterGetPos = lineItems.at(16).toInt();
        usedPBHPos = lineItems.at(17).toInt();
        afterGetY1 = lineItems.at(18).toInt();;
        afterGetY1S = lineItems.at(19).toInt();;
        afterGetY1D = lineItems.at(20).toInt();;

        afterGetY2 = lineItems.at(21).toInt();;
        afterGetY2S = lineItems.at(22).toInt();;
        afterGetY2D = lineItems.at(23).toInt();;
    }
    if(contentList.size() < 10)
    {
        advanceData.flags.all = 0;
    }
    else
    {
        advanceData.InitFromByteArray(contentList.at(9));
    }
    return true;
}

void FillAxisPItem(int action, ICMoldItem& item, const AxisPosData& data)
{
    item.SetSVal(0);
    if(action == ICMold::ACTMAINFORWARD ||
            action == ICMold::ACTMAINBACKWARD)
        item.SetDVal(data.b.x1D);
    else if(action == ICMold::ACTMAINUP ||
            action == ICMold::ACTMAINDOWN)
        item.SetDVal(data.b.y1D);
    else if(action == ICMold::ACTCOMEIN ||
            action == ICMold::ACTGOOUT)
        item.SetDVal(data.b.zD);
    else if(action == ICMold::ACTVICEFORWARD ||
            action == ICMold::ACTVICEFORWARD)
        item.SetDVal(data.b.x2D);
    else if(action == ICMold::ACTVICEUP ||
            action == ICMold::ACTVICEDOWN)
        item.SetDVal(data.b.y2D);
    item.SetAction(action);
}


void FillAxisItem(int action, const AxisPosData& data, ICMoldItem& item)
{
    if(action == -1) return;
    if(action < ICMold::GB)
    {
        int dataIndex = (action - 1) * 3;
        item.SetAction(action);
        item.SetActualPos(data.all[dataIndex++]);
        item.SetSVal(data.all[dataIndex++]);
        item.SetDVal(data.all[dataIndex]);
    }
    else
        FillAxisPItem(action, item, data);
}

inline void InsertDealyToPosIndex(QMultiMap<quint32*, int > & delayToPosIndex, quint32* delay, int posIndex)
{
    delayToPosIndex.insert(delay, posIndex);
}


void SetPosToDelayMap(int action,
                      AxisPosData& data,
                      int line,
                      QMultiMap<quint32*, int > & delayToPosIndex)
{
    if(action < ICMold::GB)
    {
        int dataIndex = (action - 1) * 3;
        InsertDealyToPosIndex(delayToPosIndex, data.all + dataIndex + 2, line);
    }
    else if(action == ICMold::ACTMAINFORWARD ||
            action == ICMold::ACTMAINBACKWARD)
    {
        InsertDealyToPosIndex(delayToPosIndex, &data.b.x1D, line);
    }

    else if(action == ICMold::ACTMAINUP ||
            action == ICMold::ACTMAINDOWN)
    {
        InsertDealyToPosIndex(delayToPosIndex, &data.b.y1D, line);

    }
    else if(action == ICMold::ACTCOMEIN ||
            action == ICMold::ACTGOOUT)
    {
        InsertDealyToPosIndex(delayToPosIndex, &data.b.zD, line);
    }
    else if(action == ICMold::ACTVICEFORWARD ||
            action == ICMold::ACTVICEFORWARD)
    {
        InsertDealyToPosIndex(delayToPosIndex, &data.b.x2D, line);
    }
    else if(action == ICMold::ACTVICEUP ||
            action == ICMold::ACTVICEDOWN)
    {
        InsertDealyToPosIndex(delayToPosIndex, &data.b.y2D, line);

    }
}

void FillPosItems(const QList<int>& actionSeq,
                  AxisPosData& data,
                  QList<ICMoldItem>& program,
                  const QList<int>& steps,
                  QMultiMap<quint32*, int > & delayToPosIndex_)
{
    ICMoldItem item;
    for(int i = 0; i < actionSeq.size(); ++i)
    {
        if(actionSeq.at(i) < 0) continue;
        item.SetNum(steps.at(i));
        FillAxisItem(actionSeq.at(i), data, item);
        SetPosToDelayMap(actionSeq.at(i), data, program.size(), delayToPosIndex_);
        program.append(item);
    }
}

int getXAction(int type, int pA)
{
    if(type == 3)
        return ICMold::GX;
    else if(type == 1)
        return pA;
    else
        return -1;
}
int getYAction(int type, int pA)
{
    if(type == 3)
        return ICMold::GY;
    else if(type == 1)
        return pA;
    else
        return -1;
}
int getZAction(int type, int pA)
{
    if(type == 3)
        return ICMold::GZ;
    else if(type == 1)
        return pA;
    else
        return -1;
}int getX2Action(int type, int pA)
{
    if(type == 3)
        return ICMold::GP;
    else if(type == 1)
        return pA;
    else
        return -1;
}int getY2Action(int type, int pA)
{
    if(type == 3)
        return ICMold::GQ;
    else if(type == 1)
        return pA;
    else
        return -1;
}

QList<int> fixtureOnAction_(QList<int>()<<ICMold::ACTCLIP1ON<<ICMold::ACTCLIP2ON<<ICMold::ACTCLIP3ON
                            <<ICMold::ACTCLIP4ON<<ICMold::ACTCLIP5ON<<ICMold::ACTCLIP6ON
                            <<ICMold::ACT_AUX5<<ICMold::ACT_AUX6<<ICMold::ACT_AUX1
                            <<ICMold::ACT_AUX2<<ICMold::ACT_AUX3<<ICMold::ACT_AUX4);
QList<int> fixtureOffAction_(QList<int>()<<ICMold::ACTCLIP1OFF<<ICMold::ACTCLIP2OFF<<ICMold::ACTCLIP3OFF
                             <<ICMold::ACTCLIP4OFF<<ICMold::ACTCLIP5OFF<<ICMold::ACTCLIP6OFF
                             <<(ICMold::ACT_AUX5)<<(ICMold::ACT_AUX6)<<(ICMold::ACT_AUX1)
                             <<(ICMold::ACT_AUX2)<<(ICMold::ACT_AUX3)<<(ICMold::ACT_AUX4));

static int flag = 0;
void AddCommentAction(const QString& comment, int step, QList<ICMoldItem>& program)
{
    ICMoldItem item;
    item.SetAction(ICMold::ACTCOMMENT);
    item.SetComment(comment);
    item.SetFlag(flag++);
    item.SetNum(step);
    program.append(item);
}

void FillFixtureItems(const FixtureConfigs& fConfigs, bool isOn,  QList<ICMoldItem>& program, int step, int delay = 10)
{
    ICMoldItem item;
    item.SetDVal(delay);
    item.SetNum(step);
    item.SetIFVal(isOn);
    item.SetActualMoldCount(0);
    for(int i = 0; i < fConfigs.size(); ++i)
    {
        if(isOn)
            item.SetClip(fixtureOnAction_.at(fConfigs.at(i).first));
        else
            item.SetClip(fixtureOffAction_.at(fConfigs.at(i).first));
        program.append(item);
    }
}

void FillFixtureCheckItems(const FixtureConfigs& fConfigs, bool isOn,  QList<ICMoldItem>& program, int &step)
{
    ICMoldItem item;
    item.SetDVal(50);
    item.SetIFVal(isOn);
    item.SetAction(ICMold::ACT_Cut);
    for(int i = 0; i < fConfigs.size(); ++i)
    {
        if(fConfigs.at(i).second)
        {
            item.SetNum(++step);
            item.SetSVal(fConfigs.at(i).first);
            program.append(item);
        }
    }
}

void FillPoseItem(int action, ICMoldItem& item)
{
    item.SetAction(action);
    item.SetDVal(0);
    item.SetSVal(0);
}

void SetEditorInfoHelper(int line, quint32* delay, QMultiMap<quint32*, int > & delayToPosIndex)
{
    InsertDealyToPosIndex(delayToPosIndex, delay, line);
}

void FillReleasePoseItems(QList<ReleasePosData>& data,
                          QList<ICMoldItem>& program,
                          int& step,
                          quint32 &yUp,
                          quint32 &yUps,
                          quint32 &yUpd,
                          int x1Type, int y1Type, int zType, int x2Type, int y2Type,
                          QMultiMap<quint32*, int > & delayToPosIndex,
                          bool isSub = false,
                          bool isCut = false,
                          CutTime cutTime = CutTime(),
                          const QString& comment = "")
{
    if(data.isEmpty()) return;
    ICMoldItem item;
    QList<int> axisActionList;
    axisActionList
            <<getZAction(zType, ICMold::ACTCOMEIN)
           <<getXAction(x1Type, ICMold::ACTMAINFORWARD);
    if(isSub)
    {
        axisActionList[1] = getX2Action(x2Type, ICMold::ACTVICEFORWARD);
    }
    QList<int> steps;
    steps<<step + 1<<step + 1;
    for(int i = 0; i < data.size(); ++i)
    {
        ++step;
        if(!comment.isEmpty())
        {
            AddCommentAction(QString("%1%2").arg(comment).arg(i + 1), step++, program);
        }
        steps[0] = steps[1] = step;
        FillPosItems(axisActionList, data[i].pos, program, steps, delayToPosIndex);
        // release product
        if(isSub)
        {
            FillAxisItem(getY2Action(y2Type, ICMold::ACTVICEDOWN), data.at(i).pos, item);
        }
        else
        {
            FillAxisItem(getYAction(y1Type, ICMold::ACTMAINDOWN), data.at(i).pos, item);
        }
        SetPosToDelayMap(item.Action(), data[i].pos, program.size(), delayToPosIndex);
        item.SetNum(++step);
        program.append(item);
        if(isCut)
        {
            if(data.at(i).fixtureConfis.size() == 1)
            {
                FillFixtureItems(data.at(i).fixtureConfis, true, program, ++step);
                FillFixtureItems(data.at(i).fixtureConfis, false, program, ++step, cutTime.b.cutOnTime);
            }
            else if(data.at(i).fixtureConfis.size() == 2)
            {
                FixtureConfigs fConfigs = data.at(i).fixtureConfis;
                item.SetDVal(0);
                item.SetNum(++step);
                item.SetIFVal(true);
                item.SetActualMoldCount(0);
                item.SetClip(fixtureOnAction_.at(fConfigs.at(0).first));
                program.append(item);
                item.SetClip(fixtureOnAction_.at(fConfigs.at(1).first));
                item.SetNum(++step);
                item.SetDVal(cutTime.b.cutAfterPullTime);
                program.append(item);

                item.SetIFVal(false);
                item.SetClip(fixtureOffAction_.at(fConfigs.at(1).first));
                item.SetNum(++step);
                item.SetDVal(cutTime.b.cutOnTime);
                program.append(item);

                item.SetClip(fixtureOffAction_.at(fConfigs.at(0).first));
                item.SetNum(++step);
                item.SetDVal(cutTime.b.pullOffAfterCutOffTime);
                program.append(item);
            }
        }
        else
            FillFixtureItems(data.at(i).fixtureConfis, false, program, ++step);
        // PYU
        item.SetAction(getYAction(y1Type,  ICMold::ACTMAINUP));
        if(isSub)
            item.SetAction(getY2Action(y2Type,  ICMold::ACTVICEUP));
        item.SetNum(++step);
        item.SetActualPos(yUp);
        item.SetSVal(yUps);
        item.SetDVal(yUpd);
        SetEditorInfoHelper(program.size(), &yUpd, delayToPosIndex);

        program.append(item);
    }
    // remove the more one y up
    if(!data.isEmpty() && !isCut)
    {
        program.pop_back();
        --step;
    }
}




bool ICMold::CompileSimpleTeachFile(int x1Type, int y1Type, int zType, int x2Type, int y2Type)
{
    flag = 0;
    simpleTeachData_.delayToPosIndex.clear();
    QList<ICMoldItem> program;
    ICMoldItem item;
    int step = 0;


//    AddCommentAction(QString::fromUtf8("待机点开始"), step, program);
    QList<int> axisActionList;
    QList<int> steps;
    steps<<step<<step<<step<<step<<step;
    axisActionList<<getXAction(x1Type, ACTMAINBACKWARD)
                 <<getYAction(y1Type, ACTMAINUP)
                <<getZAction(zType, ACTCOMEIN)
               <<getX2Action(x2Type, ACTVICEBACKWARD)
              <<getY2Action(y2Type, ACTVICEUP);
    FillPosItems(axisActionList, simpleTeachData_.stdPos, program, steps,
                simpleTeachData_.delayToPosIndex);

    item.SetAction(ACTPOSEVERT);
    item.SetDVal(0);
    item.SetSVal(0);
    program.append(item);
    item.SetNum(++step);
    item.SetAction(ACT_WaitMoldOpened);
    item.SetSVal(1);
    program.append(item);
    step++;


    //only use mian arm
    if(simpleTeachData_.usedMainArm && !simpleTeachData_.usedMainArmOutlet && !simpleTeachData_.usedSubArm)
    {
        //get product
        AddCommentAction(QString::fromUtf8("取产品开始"), step++, program);
        steps.clear();
        steps<<step<<step + 1;
        axisActionList.clear();
        axisActionList
                <<getZAction(zType, ACTCOMEIN)
               <<getYAction(y1Type, ACTMAINDOWN);
        FillPosItems(axisActionList, simpleTeachData_.getProductPos.pos, program, steps,
                     simpleTeachData_.delayToPosIndex);
        step += 1;
        item.SetNum(++step);
        item.SetClip(ACTEJECTON); // Ejector on
        item.SetDVal(10);
        program.append(item);
        // forward
        FillAxisItem(getXAction(x1Type, ACTMAINFORWARD), simpleTeachData_.getProductPos.pos, item);
        item.SetNum(++step);
        SetEditorInfoHelper(program.size(), &simpleTeachData_.getProductPos.pos.b.x1D,
                            simpleTeachData_.delayToPosIndex);
        program.append(item);
        // fixture
        FillFixtureItems(simpleTeachData_.getProductPos.fixtureConfis, true, program, ++step);
        // backward
        if(simpleTeachData_.usedAfterGetPos)
        {
            AddCommentAction(QString::fromUtf8("取产品后引拔位置"), ++step, program);
            item.SetAction(getXAction(x1Type, ACTMAINBACKWARD));
            item.SetActualPos(simpleTeachData_.afterGetX1);
            item.SetDVal(simpleTeachData_.afterGetX1D);
            item.SetSVal(simpleTeachData_.afterGetX1S);
            item.SetNum(++step);
            SetEditorInfoHelper(program.size(), &simpleTeachData_.afterGetX1D,
                                simpleTeachData_.delayToPosIndex);
            program.append(item);
        }
        // fixture check
        FillFixtureCheckItems(simpleTeachData_.getProductPos.fixtureConfis, true, program, step);
        // go up
        FillAxisItem(getYAction(y1Type, ACTMAINUP), simpleTeachData_.stdPos, item);
        item.SetNum(++step);
        item.SetActualPos(0);
        item.SetDVal(simpleTeachData_.afterGetY1D);
        SetEditorInfoHelper(program.size(), &simpleTeachData_.afterGetY1D, simpleTeachData_.delayToPosIndex);
        program.append(item);
        // close Mold
        item.SetNum(++step);
        item.SetClip(ICMold::ACTCLSMDON);
        item.SetDVal(0);
        program.append(item);
        // close check
        if(!simpleTeachData_.advanceData.flags.b.alwaysCheck)
        {
            FillFixtureCheckItems(simpleTeachData_.getProductPos.fixtureConfis, false, program, step);
        }

        // pos before hor
        if(simpleTeachData_.usedPBHPos)
        {
            AddCommentAction(QString::fromUtf8("姿势前位置"), ++step, program);
            FillAxisItem(getXAction(x1Type, ACTMAINFORWARD), simpleTeachData_.posBH, item);
            item.SetNum(++step);
            SetEditorInfoHelper(program.size(), &simpleTeachData_.posBH.b.x1D,
                                simpleTeachData_.delayToPosIndex);
            program.append(item);
        }
        // hor
        FillPoseItem(ACTPOSEHORI, item);
        item.SetNum(++step);
        program.append(item);

        // go out
        if(simpleTeachData_.usedCutOutlet)
        {
            FillReleasePoseItems(simpleTeachData_.cutOutletPosList, program, step,
                                 simpleTeachData_.cutOutletYUp, simpleTeachData_.cutOutletYUpS,
                                 simpleTeachData_.cutOutletYUpD, x1Type, y1Type, zType, x2Type, y2Type,
                                 simpleTeachData_.delayToPosIndex,
                                 false, true, simpleTeachData_.cutTime,
                                 QString::fromUtf8("剪刀位置"));
        }

        FillReleasePoseItems(simpleTeachData_.releaseProductPosList, program, step,
                             simpleTeachData_.releaseProductYUp, simpleTeachData_.releaseProductYUpS,
                             simpleTeachData_.releaseProductYUpD, x1Type, y1Type, zType, x2Type, y2Type,
                             simpleTeachData_.delayToPosIndex,
                             false, false, simpleTeachData_.cutTime, QString::fromUtf8("放产品位置"));

        // up to go in
//        if(simpleTeachData_.usedMainArm)
        {
            item.SetAction(getYAction(y1Type, ACTMAINUP));
            item.SetNum(++step);
            item.SetActualPos(0);
            item.SetSVal(simpleTeachData_.releaseProductYUpS);
            item.SetDVal(simpleTeachData_.releaseProductYUpD);
            SetEditorInfoHelper(program.size(), &simpleTeachData_.releaseProductYUpD, simpleTeachData_.delayToPosIndex);
            program.append(item);
            if(simpleTeachData_.usedPBHPos)
            {
                item.SetAction(getXAction(x1Type, ACTMAINFORWARD));
                item.SetNum(++step);
                item.SetActualPos(simpleTeachData_.posBH.b.x1);
                item.SetSVal(simpleTeachData_.posBH.b.x1S);
                item.SetDVal(simpleTeachData_.posBH.b.x1D);
                SetEditorInfoHelper(program.size(), &simpleTeachData_.posBH.b.x1D, simpleTeachData_.delayToPosIndex);
                program.append(item);
            }
        }

    }
    else if(simpleTeachData_.usedMainArm && !simpleTeachData_.usedMainArmOutlet && simpleTeachData_.usedSubArm) // main and sub
    {
        //get product
        AddCommentAction(QString::fromUtf8("取产品和水口开始"), step++, program);
        steps.clear();
        steps<<step<<step + 1;
        axisActionList.clear();
        axisActionList
                <<getZAction(zType, ACTCOMEIN)
               <<getYAction(y1Type, ACTMAINDOWN);
        FillPosItems(axisActionList, simpleTeachData_.getProductPos.pos, program, steps,
                     simpleTeachData_.delayToPosIndex);
        FillAxisItem(getY2Action(y2Type, ACTVICEDOWN), simpleTeachData_.getOutletPos.pos, item);
        step += 1;
        item.SetNum(step);
        SetEditorInfoHelper(program.size(), &simpleTeachData_.getOutletPos.pos.b.y2D,
                            simpleTeachData_.delayToPosIndex);
        program.append(item);

        item.SetNum(++step);
        item.SetClip(ACTEJECTON); // Ejector on
        item.SetDVal(10);
        program.append(item);
        // forward
        FillAxisItem(getXAction(x1Type, ACTMAINFORWARD), simpleTeachData_.getProductPos.pos, item);
        item.SetNum(++step);
        SetEditorInfoHelper(program.size(), &simpleTeachData_.getProductPos.pos.b.x1D, simpleTeachData_.delayToPosIndex);
        program.append(item);
        FillAxisItem(getX2Action(x2Type, ACTVICEFORWARD), simpleTeachData_.getOutletPos.pos, item);
        SetEditorInfoHelper(program.size(), &simpleTeachData_.getProductPos.pos.b.x2D, simpleTeachData_.delayToPosIndex);
        program.append(item);
        // fixture
        FillFixtureItems(simpleTeachData_.getProductPos.fixtureConfis, true, program, ++step);
        FillFixtureItems(simpleTeachData_.getOutletPos.fixtureConfis, true, program, step);
        // backward
        if(simpleTeachData_.usedAfterGetPos)
        {
            AddCommentAction(QString::fromUtf8("取产品和水口后引拔位置"), ++step, program);
            item.SetAction(getXAction(x1Type, ACTMAINBACKWARD));
            item.SetActualPos(simpleTeachData_.afterGetX1);
            item.SetDVal(simpleTeachData_.afterGetX1D);
            item.SetSVal(simpleTeachData_.afterGetX1S);
            item.SetNum(++step);
            SetEditorInfoHelper(program.size(), &simpleTeachData_.afterGetX1D,
                                simpleTeachData_.delayToPosIndex);
            program.append(item);
            item.SetAction(getX2Action(x2Type, ACTVICEBACKWARD));
            item.SetActualPos(simpleTeachData_.afterGetX2);
            item.SetDVal(simpleTeachData_.afterGetX2D);
            item.SetSVal(simpleTeachData_.afterGetX2S);
            item.SetNum(step);
            SetEditorInfoHelper(program.size(), &simpleTeachData_.afterGetX2D,
                                simpleTeachData_.delayToPosIndex);
            program.append(item);

        }
        // fixture check
        FillFixtureCheckItems(simpleTeachData_.getProductPos.fixtureConfis, true, program, step);
        FillFixtureCheckItems(simpleTeachData_.getOutletPos.fixtureConfis, true, program, step);
        // go up
        FillAxisItem(getYAction(y1Type, ACTMAINUP), simpleTeachData_.stdPos, item);
        item.SetNum(++step);
        item.SetActualPos(0);
        item.SetDVal(simpleTeachData_.afterGetY1D);
        SetEditorInfoHelper(program.size(), &simpleTeachData_.afterGetY1D,
                            simpleTeachData_.delayToPosIndex);
        program.append(item);
        FillAxisItem(getY2Action(y2Type, ACTVICEUP), simpleTeachData_.stdPos, item);
        item.SetActualPos(0);
        item.SetDVal(simpleTeachData_.afterGetY2D);
        SetEditorInfoHelper(program.size(), &simpleTeachData_.afterGetY2D,
                            simpleTeachData_.delayToPosIndex);
        program.append(item);
        // close Mold
        item.SetNum(++step);
        item.SetClip(ICMold::ACTCLSMDON);
        item.SetDVal(0);
        program.append(item);
        // close check
        if(!simpleTeachData_.advanceData.flags.b.alwaysCheck)
        {
            FillFixtureCheckItems(simpleTeachData_.getProductPos.fixtureConfis, false, program, step);
            FillFixtureCheckItems(simpleTeachData_.getOutletPos.fixtureConfis, false, program, step);
        }
        // pos before hor
        if(simpleTeachData_.usedPBHPos)
        {
            AddCommentAction(QString::fromUtf8("姿势前位置"), ++step, program);
            FillAxisItem(getXAction(x1Type, ACTMAINFORWARD), simpleTeachData_.posBH, item);
            item.SetNum(++step);
            SetEditorInfoHelper(program.size(), &simpleTeachData_.posBH.b.x1D,
                                simpleTeachData_.delayToPosIndex);
            program.append(item);
            FillAxisItem(getX2Action(x2Type, ACTVICEFORWARD), simpleTeachData_.posBH, item);
            SetEditorInfoHelper(program.size(), &simpleTeachData_.posBH.b.x2D,
                                simpleTeachData_.delayToPosIndex);
            program.append(item);
        }
        // hor
        FillPoseItem(ACTPOSEHORI, item);
        item.SetNum(++step);
        program.append(item);
        // go out

        if(simpleTeachData_.usedCutOutlet)
        {
            FillReleasePoseItems(simpleTeachData_.cutOutletPosList, program, step,
                                 simpleTeachData_.cutOutletYUp, simpleTeachData_.cutOutletYUpS,
                                 simpleTeachData_.cutOutletYUpD, x1Type, y1Type, zType, x2Type, y2Type,
                                 simpleTeachData_.delayToPosIndex,
                                 false, true, simpleTeachData_.cutTime,
                                 QString::fromUtf8("剪刀位置"));
        }

        FillReleasePoseItems(simpleTeachData_.releaseProductPosList, program, step,
                             simpleTeachData_.releaseProductYUp, simpleTeachData_.releaseProductYUpS,
                             simpleTeachData_.releaseProductYUpD, x1Type, y1Type, zType, x2Type, y2Type,
                             simpleTeachData_.delayToPosIndex,
                             false, false, simpleTeachData_.cutTime, QString::fromUtf8("放产品位置"));
        item.SetAction(getYAction(y1Type, ACTMAINUP));
        item.SetNum(++step);
        item.SetActualPos(0);
        item.SetSVal(simpleTeachData_.releaseProductYUpS);
        item.SetDVal(simpleTeachData_.releaseProductYUpD);
        SetEditorInfoHelper(program.size(), &simpleTeachData_.releaseProductYUpD,
                            simpleTeachData_.delayToPosIndex);
        program.append(item);

        FillReleasePoseItems(simpleTeachData_.releaseOutletPosList, program, step,
                             simpleTeachData_.releaseOutletYUp, simpleTeachData_.releaseOutletYUpS,
                             simpleTeachData_.releaseOutletYUpD, x1Type, y1Type, zType, x2Type, y2Type,
                             simpleTeachData_.delayToPosIndex,
                             true, false, simpleTeachData_.cutTime, QString::fromUtf8("放水口位置"));


        item.SetAction(getY2Action(y2Type, ACTVICEUP));
        item.SetNum(++step);
        item.SetActualPos(0);
        item.SetSVal(simpleTeachData_.releaseOutletYUpS);
        item.SetDVal(simpleTeachData_.releaseOutletYUpD);
        SetEditorInfoHelper(program.size(), &simpleTeachData_.releaseOutletYUpD,
                            simpleTeachData_.delayToPosIndex);
        program.append(item);

        if(simpleTeachData_.usedPBHPos)
        {
            item.SetAction(getXAction(x1Type, ACTMAINFORWARD));
            item.SetNum(++step);
            item.SetActualPos(simpleTeachData_.posBH.b.x1);
            item.SetSVal(simpleTeachData_.posBH.b.x1S);
            item.SetDVal(simpleTeachData_.posBH.b.x1D);
            SetEditorInfoHelper(program.size(), &simpleTeachData_.posBH.b.x1D,
                                simpleTeachData_.delayToPosIndex);
            program.append(item);
            item.SetAction(getX2Action(x2Type, ACTVICEFORWARD));
            item.SetNum(step);
            item.SetActualPos(simpleTeachData_.posBH.b.x2);
            item.SetSVal(simpleTeachData_.posBH.b.x2S);
            item.SetDVal(simpleTeachData_.posBH.b.x2D);
            SetEditorInfoHelper(program.size(), &simpleTeachData_.posBH.b.x2D,
                                simpleTeachData_.delayToPosIndex);
            program.append(item);
        }
    }
    else if(!simpleTeachData_.usedMainArm && simpleTeachData_.usedMainArmOutlet && !simpleTeachData_.usedSubArm) // main and main outlet
    {
        //get product
        AddCommentAction(QString::fromUtf8("取水口开始"), step++, program);
        steps.clear();
        steps<<step<<step + 1;
        axisActionList.clear();
        axisActionList
                <<getZAction(zType, ACTCOMEIN)
               <<getYAction(y1Type, ACTMAINDOWN);
        FillPosItems(axisActionList, simpleTeachData_.getOutletPos.pos, program, steps,
                     simpleTeachData_.delayToPosIndex);
        step += 1;
        item.SetNum(++step);
        item.SetClip(ACTEJECTON); // Ejector on
        item.SetDVal(10);
        program.append(item);
        // forward
        FillAxisItem(getXAction(x1Type, ACTMAINFORWARD), simpleTeachData_.getOutletPos.pos, item);
        item.SetNum(++step);
        SetEditorInfoHelper(program.size(), &simpleTeachData_.getOutletPos.pos.b.x1D,
                            simpleTeachData_.delayToPosIndex);
        program.append(item);
        // fixture
        FillFixtureItems(simpleTeachData_.getOutletPos.fixtureConfis, true, program, ++step);
        // backward
        if(simpleTeachData_.usedAfterGetPos)
        {
            AddCommentAction(QString::fromUtf8("取水口后引拔位置"), ++step, program);
            item.SetAction(getXAction(x1Type, ACTMAINBACKWARD));
            item.SetActualPos(simpleTeachData_.afterGetX1);
            item.SetDVal(simpleTeachData_.afterGetX1D);
            item.SetSVal(simpleTeachData_.afterGetX1S);
            item.SetNum(++step);
            SetEditorInfoHelper(program.size(), &simpleTeachData_.afterGetX1D,
                                simpleTeachData_.delayToPosIndex);
            program.append(item);
        }
        // fixture check
        FillFixtureCheckItems(simpleTeachData_.getOutletPos.fixtureConfis, true, program, step);
        // go up
        FillAxisItem(getYAction(y1Type, ACTMAINUP), simpleTeachData_.stdPos, item);
        item.SetNum(++step);
        item.SetDVal(simpleTeachData_.afterGetY1D);
        item.SetActualPos(0);
        SetEditorInfoHelper(program.size(), &simpleTeachData_.afterGetY1D, simpleTeachData_.delayToPosIndex);
        program.append(item);
        // close Mold
        item.SetNum(++step);
        item.SetClip(ICMold::ACTCLSMDON);
        item.SetDVal(0);
        program.append(item);
        // close check
        if(!simpleTeachData_.advanceData.flags.b.alwaysCheck)
        {
            FillFixtureCheckItems(simpleTeachData_.getOutletPos.fixtureConfis, false, program, step);
        }
        // pos before hor
        if(simpleTeachData_.usedPBHPos)
        {
            AddCommentAction(QString::fromUtf8("姿势前位置"), ++step, program);
            FillAxisItem(getXAction(x1Type, ACTMAINFORWARD), simpleTeachData_.posBH, item);
            item.SetNum(++step);
            SetEditorInfoHelper(program.size(), &simpleTeachData_.posBH.b.x1D,
                                simpleTeachData_.delayToPosIndex);
            program.append(item);
        }
        // hor
        FillPoseItem(ACTPOSEHORI, item);
        item.SetNum(++step);
        program.append(item);
        // go out

        FillReleasePoseItems(simpleTeachData_.releaseOutletPosList, program, step,
                             simpleTeachData_.releaseOutletYUp, simpleTeachData_.releaseOutletYUpS,
                             simpleTeachData_.releaseOutletYUpD, x1Type, y1Type, zType, x2Type, y2Type,
                             simpleTeachData_.delayToPosIndex,
                             false, false, simpleTeachData_.cutTime, QString::fromUtf8("放水口位置"));

        // up to go in
//        if(simpleTeachData_.usedMainArm)
        {
            item.SetAction(getYAction(y1Type, ACTMAINUP));
            item.SetNum(++step);
            item.SetActualPos(0);
            item.SetSVal(simpleTeachData_.releaseOutletYUpS);
            item.SetDVal(simpleTeachData_.releaseOutletYUpD);
            SetEditorInfoHelper(program.size(), &simpleTeachData_.releaseOutletYUpD, simpleTeachData_.delayToPosIndex);
            program.append(item);
            if(simpleTeachData_.usedPBHPos)
            {
                item.SetAction(getXAction(x1Type, ACTMAINFORWARD));
                item.SetNum(++step);
                item.SetActualPos(simpleTeachData_.posBH.b.x1);
                item.SetSVal(simpleTeachData_.posBH.b.x1S);
                item.SetDVal(simpleTeachData_.posBH.b.x1D);
                SetEditorInfoHelper(program.size(), &simpleTeachData_.posBH.b.x1D, simpleTeachData_.delayToPosIndex);
                program.append(item);
            }
        }
    }
    else if(!simpleTeachData_.usedMainArm && !simpleTeachData_.usedMainArmOutlet && simpleTeachData_.usedSubArm)
    {
        //get product
        AddCommentAction(QString::fromUtf8("取水口开始"), step++, program);
        steps.clear();
        steps<<step<<step + 1;
        axisActionList.clear();
        axisActionList
                <<getZAction(zType, ACTCOMEIN)
               <<getY2Action(y2Type, ACTVICEDOWN);
        FillPosItems(axisActionList, simpleTeachData_.getOutletPos.pos, program, steps,
                     simpleTeachData_.delayToPosIndex);
        step += 1;
        item.SetNum(++step);
        item.SetClip(ACTEJECTON); // Ejector on
        item.SetDVal(10);
        program.append(item);
        // forward
        FillAxisItem(getX2Action(x2Type, ACTVICEFORWARD), simpleTeachData_.getOutletPos.pos, item);
        item.SetNum(++step);
        SetEditorInfoHelper(program.size(), &simpleTeachData_.getOutletPos.pos.b.x2D, simpleTeachData_.delayToPosIndex);
        program.append(item);
        // fixture
        FillFixtureItems(simpleTeachData_.getOutletPos.fixtureConfis, true, program, ++step);
        // backward
        if(simpleTeachData_.usedAfterGetPos)
        {
            AddCommentAction(QString::fromUtf8("取水口后引拔位置"), ++step, program);
            item.SetAction(getX2Action(x2Type, ACTVICEBACKWARD));
            item.SetActualPos(simpleTeachData_.afterGetX2);
            item.SetDVal(simpleTeachData_.afterGetX2D);
            item.SetSVal(simpleTeachData_.afterGetX2S);
            item.SetNum(++step);
            SetEditorInfoHelper(program.size(), &simpleTeachData_.afterGetX2D,
                                simpleTeachData_.delayToPosIndex);
            program.append(item);
        }
        // fixture check
        FillFixtureCheckItems(simpleTeachData_.getOutletPos.fixtureConfis, true, program, step);
        // go up
        FillAxisItem(getY2Action(y2Type, ACTVICEUP), simpleTeachData_.stdPos, item);
        item.SetNum(++step);
        item.SetActualPos(0);
        item.SetDVal(simpleTeachData_.afterGetY2D);
        SetEditorInfoHelper(program.size(), &simpleTeachData_.afterGetY2D, simpleTeachData_.delayToPosIndex);
        program.append(item);
        // close Mold
        item.SetNum(++step);
        item.SetClip(ICMold::ACTCLSMDON);
        item.SetDVal(0);
        program.append(item);
        // close check
        if(!simpleTeachData_.advanceData.flags.b.alwaysCheck)
        {
            FillFixtureCheckItems(simpleTeachData_.getOutletPos.fixtureConfis, false, program, step);
        }
        // pos before hor
        if(simpleTeachData_.usedPBHPos)
        {
            AddCommentAction(QString::fromUtf8("姿势前位置"), ++step, program);
            FillAxisItem(getX2Action(x2Type, ACTMAINFORWARD), simpleTeachData_.posBH, item);
            item.SetNum(++step);
            SetEditorInfoHelper(program.size(), &simpleTeachData_.posBH.b.x2D,
                                simpleTeachData_.delayToPosIndex);
            program.append(item);
        }
        // hor
        FillPoseItem(ACTPOSEHORI, item);
        item.SetNum(++step);
        program.append(item);
        // go out


        FillReleasePoseItems(simpleTeachData_.releaseOutletPosList, program, step,
                             simpleTeachData_.releaseOutletYUp, simpleTeachData_.releaseOutletYUpS,
                             simpleTeachData_.releaseOutletYUpD, x1Type, y1Type, zType, x2Type, y2Type,
                             simpleTeachData_.delayToPosIndex,
                             true, false, simpleTeachData_.cutTime, QString::fromUtf8("放水口位置"));

        // up to go in
//        if(simpleTeachData_.usedMainArm)
        {
            item.SetAction(getY2Action(y2Type, ACTVICEUP));
            item.SetNum(++step);
            item.SetActualPos(0);
            item.SetSVal(simpleTeachData_.releaseOutletYUpS);
            item.SetDVal(simpleTeachData_.releaseOutletYUpD);
            SetEditorInfoHelper(program.size(), &simpleTeachData_.releaseOutletYUpD, simpleTeachData_.delayToPosIndex);
            program.append(item);
            if(simpleTeachData_.usedPBHPos)
            {
                item.SetAction(getX2Action(x2Type, ACTVICEFORWARD));
                item.SetNum(++step);
                item.SetActualPos(simpleTeachData_.posBH.b.x2);
                item.SetSVal(simpleTeachData_.posBH.b.x2S);
                item.SetDVal(simpleTeachData_.posBH.b.x2D);
                SetEditorInfoHelper(program.size(), &simpleTeachData_.posBH.b.x2D, simpleTeachData_.delayToPosIndex);

                program.append(item);
            }
        }
    }


    // end
    item.SetNum(++step);
    item.SetAction(ACTEND);
    item.SetDVal(0);
    program.append(item);


    moldContent_ = program;
    MoldReSum();
    SaveMoldFile(false);

    return true;
}
