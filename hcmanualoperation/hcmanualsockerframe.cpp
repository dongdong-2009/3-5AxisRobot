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
    ICCommandKeyWrapper *wrapper;
    wrapper = new ICCommandKeyWrapper(ui->connectSucker1ToolButton, IC::VKEY_CLIP5ON);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->connectSucker2ToolButton, IC::VKEY_CLIP6ON);
    wrappers_.append(wrapper);

    wrapper = new ICCommandKeyWrapper(ui->disconnectSucker1ToolButton, IC::VKEY_CLIP5OFF);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->disconnectSucker2ToolButton, IC::VKEY_CLIP6OFF);
    wrappers_.append(wrapper);

    wrapper = new ICCommandKeyWrapper(ui->connectSucker3ToolButton, IC::VKEY_RESERVE1_ON);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->connectSucker4ToolButton, IC::VKEY_RESERVE2_ON);
    wrappers_.append(wrapper);

    wrapper = new ICCommandKeyWrapper(ui->disconnectSucker3ToolButton, IC::VKEY_RESERVE1_OFF);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->disconnectSucker4ToolButton, IC::VKEY_RESERVE2_OFF);
    wrappers_.append(wrapper);

    wrapper = new ICCommandKeyWrapper(ui->connectSucker5ToolButton, IC::VKEY_RESERVE3_ON);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->connectSucker6ToolButton, IC::VKEY_RESERVE4_ON);
    wrappers_.append(wrapper);

    wrapper = new ICCommandKeyWrapper(ui->disconnectSucker5ToolButton, IC::VKEY_RESERVE3_OFF);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->disconnectSucker6ToolButton, IC::VKEY_RESERVE4_OFF);
    wrappers_.append(wrapper);

    wrapper = new ICCommandKeyWrapper(ui->connectSucker7ToolButton, IC::VKEY_RESERVE5_ON);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->connectSucker8ToolButton, IC::VKEY_RESERVE6_ON);
    wrappers_.append(wrapper);

    wrapper = new ICCommandKeyWrapper(ui->disconnectSucker7ToolButton, IC::VKEY_RESERVE5_OFF);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->disconnectSucker8ToolButton, IC::VKEY_RESERVE6_OFF);
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
    if(host->IsClipOn(4))
    {
        ui->sucker1StatusLabel->setPixmap(on);
    }
    else
    {
        ui->sucker1StatusLabel->setPixmap(off);
    }

    if(host->IsClipOn(5))
    {
        ui->sucker2StatusLabel->setPixmap(on);
    }
    else
    {
        ui->sucker2StatusLabel->setPixmap(off);
    }

    if(host->IsInputOn(5))
    {
        ui->sucker1Label->setPixmap(inOn);
    }
    else
    {
        ui->sucker1Label->setPixmap(off);
    }

    if(host->IsInputOn(4))
    {
        ui->sucker2Label->setPixmap(inOn);
    }
    else
    {
        ui->sucker2Label->setPixmap(off);
    }

    if(host->IsInputOn(11))
    {
        ui->sucker3Label->setPixmap(inOn);
    }
    else
    {
        ui->sucker3Label->setPixmap(off);
    }

    if(host->IsInputOn(23))
    {
        ui->sucker4Label->setPixmap(inOn);
    }
    else
    {
        ui->sucker4Label->setPixmap(off);
    }

    if(host->IsInputOn(6))
    {
        ui->sucker5Label->setPixmap(inOn);
    }
    else
    {
        ui->sucker5Label->setPixmap(off);
    }

    if(host->IsInputOn(22))
    {
        ui->sucker6Label->setPixmap(inOn);
    }
    else
    {
        ui->sucker6Label->setPixmap(off);
    }

    if(host->IsInputOn(24))
    {
        ui->sucker7Label->setPixmap(inOn);
    }
    else
    {
        ui->sucker7Label->setPixmap(off);
    }

    if(host->IsInputOn(26))
    {
        ui->sucker8Label->setPixmap(inOn);
    }
    else
    {
        ui->sucker8Label->setPixmap(off);
    }

    if(host->IsOutputOn(7))
    {
        ui->sucker3StatusLabel->setPixmap(on);
    }
    else
    {
        ui->sucker3StatusLabel->setPixmap(off);
    }

    if(host->IsOutputOn(10))
    {
        ui->sucker4StatusLabel->setPixmap(on);
    }
    else
    {
        ui->sucker4StatusLabel->setPixmap(off);
    }

    if(host->IsOutputOn(17))
    {
        ui->sucker5StatusLabel->setPixmap(on);
    }
    else
    {
        ui->sucker5StatusLabel->setPixmap(off);
    }

    if(host->IsOutputOn(18))
    {
        ui->sucker6StatusLabel->setPixmap(on);
    }
    else
    {
        ui->sucker6StatusLabel->setPixmap(off);
    }

    if(host->IsOutputOn(21))
    {
        ui->sucker7StatusLabel->setPixmap(on);
    }
    else
    {
        ui->sucker7StatusLabel->setPixmap(off);
    }

    if(host->IsOutputOn(22))
    {
        ui->sucker8StatusLabel->setPixmap(on);
    }
    else
    {
        ui->sucker8StatusLabel->setPixmap(off);
    }

}
