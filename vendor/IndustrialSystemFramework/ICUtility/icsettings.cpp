#include "icsettings.h"

ICSettings::ICSettings( const QString & fileName, Format format, QObject * parent )
{
    if(format == ICSettings::IniFormat)
    {
        this->fileName_ = fileName;
        this->groupName_ = '\0';
        this->fileToMap();
//        this->icSettingsTimer_ = new QTimer(this);
//        connect(icSettingsTimer_,SIGNAL(timeout()),this,SLOT(sync()));
    }
    else this->fileName_ = '\0';
}

ICSettings::~ICSettings()
{
    this->fileName_ = '\0';
    delete icSettingsTimer_;
}

void ICSettings::beginGroup( const QString & prefix )
{
    if(this->fileName_ == '\0') return;
    this->groupName_ = prefix;
}

void ICSettings::endGroup ()
{
    if(this->fileName_=='\0') return;
    this->groupName_ = '\0';
//    this->icSettingsTimer_->start(300000);
    QTimer::singleShot(5000,this,SLOT(sync()));
}

void ICSettings::setValue( const QString & key, const QVariant & value )
{
    if(this->fileName_ == '\0' || this->groupName_ == "\0") return;
    QMap<QString,QVariant> subMap(this->textMap_.value(this->groupName_));
    subMap.insert(key,value);
    this->textMap_.insert(this->groupName_,subMap);
}

QVariant ICSettings::value( const QString & key, const QVariant & defaultValue) const
{
    if(this->fileName_ == '\0' || this->groupName_ == "\0") return defaultValue;
    if(!this->textMap_.contains(this->groupName_)) return defaultValue;
    return this->textMap_.value(this->groupName_).value(key,defaultValue);
}

bool ICSettings::fileToMap()
{
    QStringList subTemp;
    QMap<QString,QVariant> subMap;
    if(this->fileName_ == '\0') return false;
    ICFile file(this->fileName_);
    QString Text(file.ICRead());
    QStringList textSub(Text.split("\n\n"));
    for(int i = 0;i < textSub.size();i ++)
    {
        subTemp = textSub.at(i).split("\n");
        QString group(subTemp[0].remove(QRegExp("\\[|\\]|\\n")));
        for(int j = 1;j < subTemp.size();j ++)
        {
            subTemp[j].remove(QRegExp("\\n"));
            if(subTemp.at(j).size() == 0) continue;
            QString value(subTemp.at(j));
            QString key(subTemp.at(j));
            key.remove(QRegExp("=.*"));
            value.remove(QRegExp(".*="));
            subMap.insert(key,value);
        }
        this->textMap_.insert(group,subMap);
        subMap.clear();
    }
    return true;
}

bool ICSettings::sync()
{
    QString writeBuf;
    QMap<QString,QVariant> subMap;
    QMap<QString, QMapsub>::const_iterator i;
    QMap<QString, QVariant>::const_iterator j;
    for(i = this->textMap_.constBegin();i != this->textMap_.constEnd();i ++)
    {
        writeBuf.append("[").append(i.key()).append("]\n");
        subMap = this->textMap_.value(i.key());
        for(j = subMap.constBegin();j != subMap.constEnd();j ++)
        {
            writeBuf.append(j.key()).append("=");
            writeBuf.append(j.value().toString()).append("\n");
        }
        if(i == this->textMap_.constEnd()-1) break;
        writeBuf.append("\n");
    }
    ICFile file(this->fileName_);
    if(file.ICWrite(writeBuf.toUtf8())) return true;
    return false;
}

