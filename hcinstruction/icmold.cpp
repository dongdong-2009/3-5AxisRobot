#include <QFile>
#include <QStringList>
#include <QDebug>
#include "icmold.h"
#include "icinstructparam.h"
#include "icfile.h"
#include "icmacrosubroutine.h"

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
    QObject(parent),
    isBadProductEn_(false),
    badProductPos_(QList<uint>()<<0<<0<<0<<80<<80<<80)
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
    int recordsStart = 0;
    if(records.size() >= 1)
    {
        itemsContent = records.at(0);
        items = itemsContent.split(' ', QString::SkipEmptyParts);
        if(items.size() == 7)
        {
            SetBadProductEn(items.at(0).toInt() == 1);
            SetBadProductPos(QList<uint>()<<items.at(1).toUInt()<<items.at(2).toUInt()<<items.at(3).toUInt()
                             <<items.at(4).toUInt()<<items.at(5).toUInt()<<items.at(6).toUInt());
            recordsStart = 1;
        }
    }
    for(int i = recordsStart; i != records.size(); ++i)
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
    if(IsBadProductEn())
    {
        toWrite += QString("%1 %2 %3 %4 %5 %6 %7\n").arg(1)
                .arg(badProductPos_.at(0)).arg(badProductPos_.at(1)).arg(badProductPos_.at(2))
                .arg(badProductPos_.at(3)).arg(badProductPos_.at(4)).arg(badProductPos_.at(5))
                .toUtf8();
        ICMacroSubroutine::Instance()->GenerateBadProductSub(needToCutOffFixtures_, BadProductPos());
        QString moldName = moldName_;
        moldName.chop(3);
        QFile::remove(QString("%1sub5").arg(moldName));
        qDebug()<<QFile::copy(QString("subs/sub5.prg"), QString("%1sub5").arg(moldName));
    }
    for(int i = 0; i != moldContent_.size(); ++i)
    {
        toWrite += moldContent_.at(i).ToString() + "\n";
    }
    ICFile file(moldName_);
    ret = file.ICWrite(toWrite);
//    QFile file(moldName_ + ".bak");
//    if(!file.open(QFile::Write | QFile::Text))
//    {
//        return false;
//    }
////    if(file.readAll() != toWrite)
////    {
//    //        QFile::copy(moldName_, moldName_ + "~");
////    file.resize(0);
//    file.write(toWrite);
//    file.close();
//    //    QDir dir(file.parent())
//    //    system(QString("rm %1~").arg(moldName_).toAscii());
//    //        QFile::remove(moldName_ + "~");
//    QFile::copy(moldName_ + ".bak", moldName_);
//    ret = true;
////    }
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
//    QFile file(moldParamName_ + ".bak");
//    if(!file.open(QFile::ReadWrite | QFile::Text))
//    {
//        return false;
//    }
////    if(file.readAll() != toWrite)
////    {
////    QFile::copy(moldParamName_, moldParamName_ + "~");
////    file.resize(0);
//    file.write(toWrite);
//    file.close();
//    //    system(QString("rm %1~").arg(moldParamName_).toAscii());
////    QFile::remove(moldParamName_ + "~");
//    QFile::copy(moldParamName_ + ".bak", moldParamName_);
//    ret = true;
////    }
    return ret;
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
    int itemCount;
    QList<int> pos;
    pos<<0<<0<<0<<0<<0<<0<<0<<0;
    ICMoldItem baseItem;
    for(int i = 0; i != items.size(); ++i)
    {
        item = items.at(i);
        itemCount = item.ItemCount();
        for(int j = 0; j != itemCount; ++j)
        {
            baseItem = *item.MoldItemAt(j);
            ret.append(ICInstructParam::ConvertCommandStr(baseItem, pos));
            if(ICMold::IsAxisAction(baseItem.Action()))
            {
                pos[baseItem.Action()] = baseItem.Pos();
            }
        }
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
//    QList<int> fixtureOnItems;
    needToCutOffFixtures_.clear();

    bool isYUp = false;
    bool isYDown = false;
    bool isBadProductInserted = !IsBadProductEn();
    int badProductStepFix = 0;
    int badProductStep = -1;
    for(int i = 0; i != tmpContent.size(); ++i)
    {
//        moldContent_[i].SetSeq(i);
        item = tmpContent.at(i);
        if((item.Action() == GZ) && isYUp && !isBadProductInserted)
        {
            // Find where to insert BadProduct check
            for(int j = i - 1; j >= 0; --j)
            {
                if(tmpContent.at(j).Num() != item.Num())
                {
                    ICMoldItem badProductCheckItem;
                    badProductCheckItem.SetAction(ACTCHECKINPUT);
                    badProductCheckItem.SetIFVal(0);
                    badProductCheckItem.SetSVal(5);
                    badProductCheckItem.SetFlag(j);
                    badProductCheckItem.SetNum(tmpContent.at(j).Num() + stepOffset);
                    badProductStep = j + 1;
                    tmpContent.insert(badProductStep,badProductCheckItem);
                    badProductStepFix = 1;
                    isBadProductInserted = true;
                    i = badProductStep;
                    item = tmpContent.at(badProductStep);
                    break;
                }
            }
        }
        tmpContent[i].SetNum(item.Num() - stepOffset + badProductStepFix);
        qDebug()<<tmpContent[i].ToString();
        stepMap_.insert(tmpContent.at(i).Num(), moldContent_.at(i - badProductStepFix).Num());
        if(item.Action() == ACTCOMMENT)
        {
            qDebug()<<item.Flag()<<item.Num();
            flagToSetp.insert(item.Flag(), tmpContent[i].Num());
            if(i == 0 && moldContent_.at(i + 1 - badProductStepFix).Num() == item.Num())
            {
                continue;
            }
            else if(moldContent_.at(i + 1 - badProductStepFix).Num() == item.Num() ||
                    moldContent_.at(i - 1 - badProductStepFix).Num() == item.Num())
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
        else if(((item.Clip() >= ACTCLIP1ON) && (item.Clip() <= ACTCLIP6ON)) ||
                ((item.Clip() >= ACT_AUX1) && (item.Clip() <= ACT_AUX3) && (item.IFVal() == 1)))
        {
//            fixtureOnItems.append(item.Clip());
            ICMoldItem fixtureItem = item;
            if(((item.Clip() >= ACTCLIP1ON) && (item.Clip() <= ACTCLIP6ON)))
            {
                fixtureItem.SetClip(ACTCLIP1OFF + item.Clip());
            }
            else if((item.Clip() >= ACT_AUX1) && (item.Clip() <= ACT_AUX3))
            {
                fixtureItem.SetIFVal(0);
            }
            needToCutOffFixtures_.append(fixtureItem);
        }
        else if(item.Action() == GY)
        {
            if(item.ActualPos() != 0)
            {
                isYDown = true;
            }
            else if(isYDown && item.ActualPos() == 0)
            {
                isYUp = true;
            }
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
    int newbadProductStep = badProductStep;
    for(int i = 0; i < tmpContent.size(); ++i)
    {
        toSentItem = tmpContent.at(i);
        if(toSentItem.Action() == ACTCOMMENT)
            continue;
        if(i == badProductStep)
        {
            newbadProductStep = toSentContent_.size();
        }
//        qDebug()<<toSentItem.ToString();
        toSentItem.SetSeq(toSentContent_.size());
        toSentItem.ReSum();
        toSentContent_.append(toSentItem);
    }

    toSentContent_[newbadProductStep].SetDVal(toSentContent_.last().Num() - toSentContent_.at(newbadProductStep).Num());
    toSentContent_[newbadProductStep].ReSum();
//    qDebug()<<toSentContent_[newbadProductStep].ToString();
//    qDebug("End");
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
