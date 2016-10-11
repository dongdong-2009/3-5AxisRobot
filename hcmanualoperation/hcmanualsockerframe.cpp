#include "hcmanualsockerframe.h"
#include "ui_hcmanualsockerframe.h"

#include "iccommandkeywrapper.h"
#include "icvirtualkey.h"
#include "icvirtualhost.h"

HCManualSockerFrame::HCManualSockerFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::HCManualSockerFrame)
{
    ui->setupUi(this);
    ui->reserve3InLabel->hide();
    ui->reserve4InLabel->hide();
    ICCommandKeyWrapper *wrapper;

    wrapper = new ICCommandKeyWrapper(ui->connectReserve3ToolButton, IC::VKEY_RESERVE3_ON);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->connectReserve4ToolButton, IC::VKEY_RESERVE4_ON);
    wrappers_.append(wrapper);

    wrapper = new ICCommandKeyWrapper(ui->disconnectReserve3ToolButton, IC::VKEY_RESERVE3_OFF);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->disconnectReserve4ToolButton, IC::VKEY_RESERVE4_OFF);
    wrappers_.append(wrapper);

    wrapper = new ICCommandKeyWrapper(ui->connectReserve5ToolButton, IC::VKEY_RESERVE5_ON);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->connectReserve6ToolButton, IC::VKEY_RESERVE6_ON);
    wrappers_.append(wrapper);

    wrapper = new ICCommandKeyWrapper(ui->disconnectReserve5ToolButton, IC::VKEY_RESERVE5_OFF);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->disconnectReserve6ToolButton, IC::VKEY_RESERVE6_OFF);
    wrappers_.append(wrapper);

}

HCManualSockerFrame::~HCManualSockerFrame()
{
    delete ui;
    qDeleteAll(wrappers_);
}

void HCManualSockerFrame::showEvent(QShowEvent *e)
{
    QFrame::showEvent(e);
    connect(ICVirtualHost::GlobalVirtualHost(),
            SIGNAL(StatusRefreshed()),
            SLOT(StatusRefreshed()));
}

void HCManualSockerFrame::hideEvent(QHideEvent *e)
{
    QFrame::hideEvent(e);
    disconnect(ICVirtualHost::GlobalVirtualHost(),
               SIGNAL(StatusRefreshed()),
               this,
               SLOT(StatusRefreshed()));
}

void HCManualSockerFrame::changeEvent(QEvent *e)
{
    QFrame::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
    {
        ui->retranslateUi(this);
    }
        break;
    default:
        break;
    }
}

void HCManualSockerFrame::StatusRefreshed()
{
    static QPixmap off(":/resource/ledgray(16).png");
    static QPixmap on(":/resource/ledgreen(16).png");
    static QPixmap inOn(":/resource/ledred(16).png");
    static ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();

    if(host->PeripheryOutput(2) == 1)
    {
        if(host->IsOutputOn(17))
        {
            ui->reserve3StatusLabel->setPixmap(on);
        }
        else
        {
            ui->reserve3StatusLabel->setPixmap(off);
        }
    }

    if(host->PeripheryOutput(3) == 1)
    {
        if(host->IsOutputOn(18))
        {
            ui->reserve4StatusLabel->setPixmap(on);
        }
        else
        {
            ui->reserve4StatusLabel->setPixmap(off);
        }
    }

    if(host->PeripheryOutput(4) == 1)
    {
        if(host->IsOutputOn(21))
        {
            ui->reserve5StatusLabel->setPixmap(on);

        }
        else
        {

            ui->reserve5StatusLabel->setPixmap(off);

        }
    }

    if(host->PeripheryOutput(5) == 1)
    {
        if(host->IsOutputOn(22))
        {

            ui->reserve6StatusLabel->setPixmap(on);

        }
        else
        {

            ui->reserve6StatusLabel->setPixmap(off);

        }
    }

    ui->reserve5InLabel->setPixmap(host->IsInputOn(28) ? inOn : off);
    ui->reserve6InLabel->setPixmap(host->IsInputOn(29) ? inOn : off);

}
