#ifndef ICSETTINGS_H
#define ICSETTINGS_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QRegExp>
#include <QTimer>
#include "icfile.h"

class ICSettings : public QObject
{
    Q_OBJECT
public:
    enum Format
    {
        IniFormat = 1
    };

public:
//    ICSettings ( const QString & organization, const QString & application = QString(), QObject * parent = 0 );
//    ICSettings ( Scope scope, const QString & organization, const QString & application = QString(), QObject * parent = 0 );
//    ICSettings ( Format format, Scope scope, const QString & organization, const QString & application = QString(), QObject * parent = 0 );
    ICSettings ( const QString & fileName, Format format, QObject * parent = 0 );
//    ICSettings ( QObject * parent = 0 );
    ~ICSettings ();
    bool fileToMap();
    void beginGroup ( const QString & prefix );
    void endGroup ();
    void setValue ( const QString & key, const QVariant & value );
    QVariant value ( const QString & key, const QVariant & defaultValue = QVariant() ) const;

private:
    QString fileName_;
    QString groupName_;
    typedef QMap<QString,QVariant> QMapsub;
    QMap<QString,QMapsub> textMap_;
    QTimer* icSettingsTimer_;


signals:
public slots:
    bool sync();
};
#endif // ICSETTINGS_H
