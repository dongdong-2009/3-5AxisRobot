#include <QtGui/QApplication>
#include "mainframe.h"
#include "icvirtualhost.h"
#include "ickeyboard.h"
#include "icsplashscreen.h"
#include "icparameterssave.h"
#include "ICHacker.h"

#ifdef Q_WS_WIN
#include <QFile>
#endif

int main(int argc, char *argv[])
{    
    QApplication a(argc, argv);
#ifdef Q_WS_WIN
    QFile file("./stylesheet/global.qss");
    if(file.open(QFile::ReadOnly))
    {
        qApp->setStyleSheet(file.readAll());
        file.close();
    }
#endif
//    system("BackLight initrobot");
//    qApp->setStyleSheet("./stylesheet/global.qss");
    ICParametersSave* paraSave = ICParametersSave::Instance();
    paraSave->SetCountry(paraSave->Country());
    QPixmap splashPixmap("resource/startup_page.png");
    ICSplashScreen *splash= new ICSplashScreen(splashPixmap);
    splash->SetRange(0, 20);
    splash->show();
    paraSave->SetBrightness(ICParametersSave::Instance()->Brightness());

    a.setGlobalStrut(QSize(32, 32));
    paraSave->LoadInitLocale();
    ICVirtualHost host;
    MainFrame w(splash);
#ifndef Q_WS_QWS
    DeepSetWidgetToolStatus(&w);
#endif
    w.show();
    splash->finish(&w);
    delete splash;
    return a.exec();
}
