#include "icupdatesystem.h"
#include <stdlib.h>
#include <errno.h>
#include <QDebug>
#include <QProcess>

ICUpdateSystem::ICUpdateSystem():
    unpackCmd_("decrypt.sh")
{
    SetPacksDir("/mnt/udisk/HCUpdate");
}

QStringList ICUpdateSystem::ScanUpdatePacks() const
{
    return packPath_.entryList(QStringList()<<ScanPattern(), QDir::Files);
}

QString ICUpdateSystem::PackProfile(const QString &packName)
{
    QFile readMe(packPath_.absoluteFilePath(packName + "_README"));
    if(readMe.open(QFile::ReadOnly))
    {
        return QString::fromUtf8(readMe.readAll());
    }
    return QString();
}

bool ICUpdateSystem::StartUpdate(const QString &packName)
{
    if(packPath_.exists(packName))
    {
//        QString dataDir("/opt/Qt/UpdateApps");
        QFile file(packPath_.absoluteFilePath(packName));
        QDir tmpDir = QDir::temp();
        QString tmpFile = tmpDir.absoluteFilePath(packName);
        system(QString("rm " + tmpFile).toUtf8());
        if(file.copy(tmpFile))
        {
            system((unpackCmd_ + " " + tmpFile).toUtf8());
            QStringList tars = tmpDir.entryList(QStringList()<<"*.tar");
            if(tars.isEmpty()) return false;
            tmpFile = tmpDir.absoluteFilePath(tars.at(0));
//            tmpFile.chop(4);
//            system(QString("cd %1 && tar -xf %2").arg(QDir::tempPath()).arg(tmpFile).toAscii());
            system(QString("rm -r %1/HCUpdateTmp").arg(QDir::tempPath()).toUtf8());
            system(QString("mkdir -p %1/HCUpdateTmp && cd %1 && tar -xf %2 -C %1/HCUpdateTmp").arg(QDir::tempPath()).arg(tmpFile).toUtf8());
//            tmpFile.chop(4);
            tmpDir.cd("HCUpdateTmp");
            QStringList tarDirs = tmpDir.entryList(QStringList()<<"HC*");
            if(tarDirs.isEmpty()) return false;
            tmpDir.cdUp();
            tmpFile = tmpDir.absoluteFilePath("HCUpdateTmp/" + tarDirs.at(0));
            system(QString("chmod 777 %1/ -R").arg(tmpFile).toUtf8());
            system(QString("cd %1 && ./UpdateSystem.sh").arg(tmpFile).toUtf8());
            system(QString("rm %1/*.tar").arg(QDir::tempPath()).toUtf8());
//            system(QString("cp %1/%2/UpdateSystem.sh %1/UpdateApps && sync && umount /mnt/udisk && reboot").arg(dataDir).arg(tmpFile.mid(4)).toLatin1());
//            qDebug()<<"Switch to update:"<<QProcess::startDetached(QString("%1/UpdateSystem.sh %1").arg(QDir::temp().absoluteFilePath(tmpFile)).toAscii());
            return true;
            //return system(QString("cd %1 && chmod +x ./UpdateSystem.sh &&./UpdateSystem.sh").arg(QDir::temp().absoluteFilePath(tmpFile)).toAscii()) > 0;
        }
    }
    return false;
}
