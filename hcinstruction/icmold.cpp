#include <QFile>
#include <QStringList>
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

        simpleTeachData_.cutOnTime = 50;
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
    if((lineItems.size() - AXISPOSDATASIZE) % 2 != 0) return false;
    for(int i = AXISPOSDATASIZE; i < lineItems.size(); i +=2)
    {
        fixtureConfis.append(qMakePair<int, bool>(lineItems.at(i).toInt(),
                                                  lineItems.at(i + 1).toInt()));
    }
    return true;
}

bool SimpleTeachData::InitFromByteArray(const QString &text)
{
    QStringList contentList = text.split("\n");
    if(contentList.size() != 9) return false;
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
    cutOnTime = contentList.at(8).toInt();
    return true;
}
