#include "icupdatelogodialog.h"
#include "ui_icupdatelogodialog.h"
#include "icmessagebox.h"

ICUpdateLogoDialog::ICUpdateLogoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ICUpdateLogoDialog)
{
    ui->setupUi(this);
    this->showMaximized();
}

ICUpdateLogoDialog::~ICUpdateLogoDialog()
{
    delete ui;
}

void ICUpdateLogoDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void ICUpdateLogoDialog::on_scanPictures_clicked()
{
#ifdef Q_WS_X11
    ui->picView->ScanPictures("./resource");
#else
    ui->picView->ScanPictures("/mnt/udisk/HCUpdate_pic");
#endif
}

void ICUpdateLogoDialog::on_setToStartup_clicked()
{
    if(ui->picView->CurrentSelectedPicture().isEmpty())
    {
        ICMessageBox::ICWarning(this,tr("warning"),tr("No select picture!"));
        return;
    }
    startupPage_ = ui->picView->CurrentSelectedPicture();
    ui->startupPage->setText(startupPage_);

    ::system("rm ./resource/startup_page.png");
    if(!startupPage_.isEmpty())
    {
#ifdef Q_WS_X11
        QFile::copy(startupPage_, "/home/gausscheng/startup_page.png");
#else
        QFile::copy(startupPage_, "./resource/startup_page.png");
#endif
    }
    ::system("sync");
    ICMessageBox::ICWarning(this,tr("Tips"),tr("Setting success,In operation after reboot!"));
}

void ICUpdateLogoDialog::on_setToStandby_clicked()
{
    if(ui->picView->CurrentSelectedPicture().isEmpty())
    {
        ICMessageBox::ICWarning(this,tr("warning"),tr("No select picture!"));
        return;
    }
    standbyPage_ = ui->picView->CurrentSelectedPicture();
    ui->standbyPage->setText(standbyPage_);

    ::system("rm ./resource/Standby.png");
    if(!standbyPage_.isEmpty())
    {
#ifdef Q_WS_X11
        QFile::copy(standbyPage_, "/home/gausscheng/Standby.png");
#else
        QFile::copy(standbyPage_, "./resource/Standby.png");
#endif
    }
    ::system("sync");
    ICMessageBox::ICWarning(this,tr("Tips"),tr("Setting success,In operation after reboot!"));
}

//void ICUpdateLogoDialog::on_okButton_clicked()
//{
//    ::system("rm /opt/Qt/bin/resource/*");
//    if(!startupPage_.isEmpty())
//    {
//#ifdef Q_WS_X11
//        QFile::copy(startupPage_, "/home/gausscheng/startup_page.png");
//#else
//        QFile::copy(startupPage_, "/opt/Qt/bin/resource/startup_page.png");
//#endif
//    }
//    if(!standbyPage_.isEmpty())
//    {
//#ifdef Q_WS_X11
//        QFile::copy(standbyPage_, "/home/gausscheng/Standby.png");
//#else
//        QFile::copy(standbyPage_, "/opt/Qt/bin/resource/Standby.png");
//#endif
//    }
//    this->accept();
//}

void ICUpdateLogoDialog::on_cancelButton_clicked()
{
    this->reject();
}

void ICUpdateLogoDialog::on_setToAppIcon_clicked()
{
    if(ui->picView->CurrentSelectedPicture().isEmpty())
    {
        ICMessageBox::ICWarning(this,tr("warning"),tr("No select picture!"));
        return;
    }
    appIconPage_ = ui->picView->CurrentSelectedPicture();
    ui->appIconPage->setText(appIconPage_);

    ::system("rm ./resource/logo_icon.png");
    if(!appIconPage_.isEmpty())
    {
#ifdef Q_WS_X11
        QFile::copy(appIconPage_, "/home/gausscheng/logo_icon.png");
#else
        QFile::copy(appIconPage_, "./resource/logo_icon.png");
#endif
    }
    ::system("sync");
    ICMessageBox::ICWarning(this,tr("Tips"),tr("Setting success,In operation after reboot!"));
}
