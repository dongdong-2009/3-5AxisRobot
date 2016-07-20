#include <QDir>
#include <QFile>
#include <QDebug>
#include <QStringList>
#include "icmacrosubroutine.h"
#include "icfile.h"
#include "icvirtualhost.h"

QScopedPointer<ICMacroSubroutine> ICMacroSubroutine::instance_;
ICMacroSubroutine::ICMacroSubroutine(QObject *parent) :
    QObject(parent)
{
}

bool ICMacroSubroutine::ReadMacroSubroutieFiles(const QString &dir)
{
    QDir fileDir(dir);
    if(!fileDir.exists())
    {
        return false;
    }
    subsDir_ = dir;
//    QStringList fileList = fileDir.entryList(QStringList()<<"sub*");
    QStringList fileList(QStringList()<<"sub0.prg"<<"sub1.prg"<<"sub2.prg"<<"sub3.prg"<<"sub4.prg"<<"sub5.prg"<<"sub6.prg"<<"sub7.prg");
//    fileList.removeOne("sub8.prg");
    QFile file;
    QString fileContent;
    QStringList records;
    QStringList items;
    QString fileName;
    QList<ICMoldItem> sub;
    ICMoldItem subItem;
    subroutines_.clear();
    foreach(fileName, fileList)
    {
        file.setFileName(fileDir.filePath(fileName));
        if(!file.open(QFile::ReadOnly | QFile::Text))
        {
            qCritical()<<fileName<<" can't open";
            return false;
        }
        fileContent = QString::fromUtf8(file.readAll());
        file.close();

        records = fileContent.split('\n', QString::SkipEmptyParts);
        sub.clear();
        for(int i = 0; i != records.size(); ++i)
        {
            items = records.at(i).split(' ', QString::SkipEmptyParts);
//            items.removeAt(2);
            if(items.size() != 10 && items.size() != 11 && items.size() != 12)
            {
                break;
            }
            subItem.SetValue(items.at(0).toUInt(),
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
                subItem.SetComment(items.at(10));

            sub.append(subItem);
        }//foreach(record, records)
        subroutines_.append(sub);
    }//foreach(fileName, fileList)
    return true;
}

bool ICMacroSubroutine::SaveMacroSubroutieFile(int group)
{
    Q_ASSERT_X(group < subroutines_.size(), "ICMacroSubroutine::SaveMacroSubRoutineFile", "group is out of range");
    bool ret = false;
    ICMold::MoldReSum(subroutines_[group]);
    if(subsDir_.right(1) == "/")
    {
        subsDir_.chop(1);
    }
    QByteArray toWrite;
    QList<ICMoldItem> items = subroutines_.at(group);
    for(int i = 0; i != items.size(); ++i)
    {
        toWrite += items.at(i).ToString() + "\n";
    }
    ICFile file(subsDir_ + "/sub" + QString::number(group) + ".prg");
    ret = file.ICWrite(toWrite);
//    QFile file(subsDir_ + "/sub" + QString::number(group) + ".prg");
//    if(!file.open(QFile::ReadWrite | QFile::Text))
//    {
//        return false;
//    }
//    if(file.readAll() != toWrite)
//    {
//        QFile::copy(file.fileName(), file.fileName() + "~");
//        file.resize(0);
//        file.write(toWrite);
//        file.close();
//        QFile::remove(file.fileName() + "~");
//        ret = true;
//    }
    return ret;
}

uint ICMacroSubroutine::SyncAct() const
{
    uint ret = 0;
    for(int i = 0; i != subroutines_.size(); ++i)
    {
        for(int j = 0; j != subroutines_.at(i).size(); ++j)
        {
            if(subroutines_.at(i).at(j).Action() != ICMold::ACTCOMMENT)
                ret += subroutines_.at(i).at(j).GMVal();
        }
    }
    return ret;
}

uint ICMacroSubroutine::SyncSum() const
{
    uint ret = 0;
    for(int i = 0; i != subroutines_.size(); ++i)
    {
        for(int j = 0; j != subroutines_.at(i).size(); ++j)
        {
            if(subroutines_.at(i).at(j).Action() != ICMold::ACTCOMMENT)
                ret += subroutines_.at(i).at(j).Sum();
        }
    }
    return ret;
}

void ICMacroSubroutine::GenerateBadProductSub(const QList<ICMoldItem> &offFixtures, const QList<uint> pos, bool isSub)
{
    qDebug()<<"pos:"<<pos;
    subroutines_[5].clear();
    QList<ICMoldItem> sub;
    ICMoldItem item;
    item.SetNum(0);
    item.SetAction(isSub ? ICMold::GP : ICMold::GX);
    item.SetActualPos(isSub ? pos.at(3) : pos.at(0));
    item.SetSVal(isSub ? pos.at(8) : pos.at(5));
    item.SetDVal(0);
    bool x2Servo = ICVirtualHost::GlobalVirtualHost()->AxisDefine(ICVirtualHost::ICAxis_AxisX2) == ICVirtualHost::ICAxisDefine_Servo;
    bool y2Servo = ICVirtualHost::GlobalVirtualHost()->AxisDefine(ICVirtualHost::ICAxis_AxisY2) == ICVirtualHost::ICAxisDefine_Servo;
    if(((item.Action() == ICMold::GP) && x2Servo) ||
            item.Action() == ICMold::GX)
    {
        sub.append(item);
    }

    item.SetAction(ICMold::GZ);
    item.SetActualPos(pos.at(2));
    item.SetSVal(pos.at(7));
    sub.append(item);

    if(!isSub)
    {
        item.SetAction(ICMold::ACTPOSEHORI);
        item.SetNum(1);
        item.SetSVal(0);
        item.SetDVal(0);
        sub.append(item);
    }

    item.SetNum(sub.last().Num() + 1);
    item.SetAction(isSub ? ICMold::GQ : ICMold::GY);
    item.SetActualPos(isSub ? pos.at(4) : pos.at(1));
    item.SetSVal(isSub ? pos.at(9) : pos.at(6));
    if(((item.Action() == ICMold::GQ) && y2Servo) ||
            item.Action() == ICMold::GY)
        sub.append(item);


    int fN = sub.last().Num() + 1;
    for(int i = 0; i < offFixtures.size(); ++i)
    {
        item = offFixtures.at(i);
        item.SetNum(fN);
        sub.append(item);
    }

    item.SetNum(sub.last().Num() + 1);
    item.SetAction(isSub ? ICMold::GQ : ICMold::GY);
    item.SetActualPos(0);
    item.SetSVal(isSub ? pos.at(9) : pos.at(6));
    item.SetDVal(50);
    if(((item.Action() == ICMold::GQ) && y2Servo) ||
            item.Action() == ICMold::GY)
    {
        sub.append(item);
    }
    item.SetNum(sub.last().Num() + 1);
    item.SetDVal(0);
    item.SetSVal(0);
    item.SetIFVal(0);
    item.SetAction(ICMold::ACTEND);
    sub.append(item);

    SetSubRoutine(sub, 5);
    SaveMacroSubroutieFile(5);
//    pos.SetAction();
}

void ICMacroSubroutine::GenerateTryProductSub(const QList<ICMoldItem> &offFixtures, const QList<uint> pos, bool isSub)
{
    subroutines_[7].clear();
    QList<ICMoldItem> sub;
    ICMoldItem item;
    bool x2Servo = ICVirtualHost::GlobalVirtualHost()->AxisDefine(ICVirtualHost::ICAxis_AxisX2) == ICVirtualHost::ICAxisDefine_Servo;
    bool y2Servo = ICVirtualHost::GlobalVirtualHost()->AxisDefine(ICVirtualHost::ICAxis_AxisY2) == ICVirtualHost::ICAxisDefine_Servo;
    item.SetNum(0);
    item.SetAction(isSub ? ICMold::GP : ICMold::GX);
    item.SetActualPos(isSub ? pos.at(3) : pos.at(0));
    item.SetSVal(isSub ? pos.at(8) : pos.at(5));
    item.SetDVal(0);
    if(((item.Action() == ICMold::GP) && x2Servo) ||
            item.Action() == ICMold::GX)
        sub.append(item);

    item.SetAction(ICMold::GZ);
    item.SetActualPos(pos.at(2));
    item.SetSVal(pos.at(7));
    sub.append(item);

    if(!isSub)
    {
        item.SetAction(ICMold::ACTPOSEHORI);
        item.SetNum(1);
        item.SetSVal(0);
        item.SetDVal(0);
        sub.append(item);
    }

    item.SetNum(sub.last().Num() + 1);
    item.SetAction(isSub ? ICMold::GQ : ICMold::GY);
    item.SetActualPos(isSub ? pos.at(4) : pos.at(1));
    item.SetSVal(isSub ? pos.at(9) : pos.at(6));
    if(((item.Action() == ICMold::GQ) && y2Servo) ||
            item.Action() == ICMold::GY)
        sub.append(item);


    int fN = sub.last().Num() + 1;
    for(int i = 0; i < offFixtures.size(); ++i)
    {
        item = offFixtures.at(i);
        item.SetNum(fN);
        sub.append(item);
    }

    item.SetNum(sub.last().Num() + 1);
    item.SetAction(isSub ? ICMold::GQ : ICMold::GY);
    item.SetActualPos(0);
    item.SetSVal(isSub ? pos.at(9) : pos.at(6));
    item.SetDVal(50);
    if(((item.Action() == ICMold::GQ) && y2Servo) ||
            item.Action() == ICMold::GY)
    {
        sub.append(item);
    }

    item.SetNum(sub.last().Num() + 1);

    item.SetDVal(0);
    item.SetSVal(0);
    item.SetIFVal(0);
    item.SetAction(ICMold::ACTEND);
    sub.append(item);

    SetSubRoutine(sub, 7);
    SaveMacroSubroutieFile(7);
//    pos.SetAction();
}
