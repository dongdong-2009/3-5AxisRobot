#include "icbackuputility.h"
#include <QDir>
#include <QFile>
#include <QDebug>

ICBackupUtility::ICBackupUtility()
{
}

void ICBackupUtility::SetBackupDestDir(const QString &dest)
{
    destDir_ = dest;
    QDir destDir(DestDir());
    if(!destDir.exists())
    {
        destDir.mkpath(destDir_);
    }
}

bool ICBackupUtility::BackupDir(const QStringList &nameFilter) const
{
    if(!_IsDirValid_())
    {
        return false;
    }
    _CleanDestDir_(nameFilter);
    QDir destDir(destDir_);
    bool ret = _CopyFiles_(nameFilter);
    QFile end(QDir::toNativeSeparators(destDir.absolutePath() + "/" + ".CopyEnd"));
    if(!end.open(QFile::WriteOnly))
    {
        return false;
    }
    end.write("CopyEnd");
    end.close();
    system("sync");
    return ret;
}

bool ICBackupUtility::BackupDir(const QString &src,
                                const QString &dest,
                                const QStringList &nameFilter)
{
    SetBackupSrcDir(src);
    SetBackupDestDir(dest);
    return BackupDir(nameFilter);
}

bool ICBackupUtility::RestoreDir(const QStringList& nameFilter) const
{
    if(!_IsDirValid_())
    {
        return false;
    }
    QDir srcDir(SrcDir());
    if(!srcDir.exists(".CopyEnd"))
    {
        return false;
    }
    bool ret = _CopyFiles_(nameFilter);
    system("sync");
    return ret;
}

bool ICBackupUtility::RestoreDir(const QString &src, const QString &dest, const QStringList &nameFilter)
{
    srcDir_ = src;
    destDir_ = dest;
    return RestoreDir(nameFilter);
}

QStringList ICBackupUtility::SrcDirFiles() const
{
    QDir dir(srcDir_);
    dir.setFilter(QDir::Files);
    return dir.entryList();
}

QStringList ICBackupUtility::DestDirFiles(bool isShowHidden) const
{
    QDir dir(destDir_);
    if(isShowHidden)
    {
        dir.setFilter(QDir::Files | QDir::Hidden);
    }
    else
    {
        dir.setFilter(QDir::Files);
    }
    return dir.entryList();
}

void ICBackupUtility::_CleanDestDir_(const QStringList &nameFilter) const
{
    if(DestDir().isEmpty())
    {
        return;
    }
    QDir destDir(DestDir());
    QStringList tempFilter = nameFilter;
    if(!nameFilter.isEmpty())
    {
        tempFilter.append(".CopyEnd");
    }
    QStringList files = destDir.entryList(tempFilter, QDir::Files | QDir::Hidden);
    for(int i = 0; i != files.size(); ++i)
    {
        destDir.remove(files.at(i));
    }

}

bool ICBackupUtility::_CopyFiles_(const QStringList &nameFilter) const
{
    QDir srcDir(SrcDir());
    QDir destDir(DestDir());
    QStringList srcFiles = srcDir.entryList(nameFilter, QDir::Files);
    bool ret = true;
    for(int i = 0; i != srcFiles.size(); ++i)
    {
        if(destDir.exists(srcFiles.at(i)))
        {
            destDir.remove(srcFiles.at(i));
        }
        ret = ret && (QFile::copy(srcDir.absoluteFilePath(srcFiles.at(i)),
                    QDir::toNativeSeparators(destDir.absolutePath() + "/" + srcFiles.at(i))));
    }
    return ret;
}

void ICBackupUtility::MakeGhost(const QString &name)
{
#ifdef Q_WS_QWS
    QDir dir("/mnt/udisk");
#else
    QDir dir = QDir::current();
#endif
    ::system(QString("tar -zcvf - %1 | openssl des3 -salt -k szhcSZHCGaussCheng | dd of=%2")
             .arg(QDir::current().absolutePath())
             .arg(dir.absoluteFilePath(name + ".ghost.hcdbxs5")).toUtf8());
    ::system("sync");
}

void ICBackupUtility::LoadGhost(const QString &name)
{
#ifdef Q_WS_QWS
    QDir dir("/mnt/udisk");
#else
    QDir dir = QDir::current();
#endif
    if(dir.exists(name))
    {
        ::system(QString("cd %2 && dd if=%1 | openssl des3 -d -k szhcSZHCGaussCheng | tar zxf - -C /")
                   .arg(dir.absoluteFilePath(name))
                   .arg(dir.absolutePath()).toUtf8());
        ::system("sync");
    }
}


QStringList ICBackupUtility::ScanGhost()
{
#ifdef Q_WS_QWS
    QDir dir("/mnt/udisk");
#else
    QDir dir = QDir::current();
#endif
    return dir.entryList(QStringList()<<"*.ghost.hcdbxs5", QDir::Files);
}
