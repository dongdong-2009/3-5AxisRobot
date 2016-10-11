#include "hcmanualfixtureframe.h"
#include "ui_hcmanualfixtureframe.h"
#include "iccommandkeywrapper.h"
#include "icvirtualkey.h"
#include "icvirtualhost.h"
#include "ictimerpool.h"

HCManualFixtureFrame::HCManualFixtureFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::HCManualFixtureFrame),
    clips_(16, false)
{
    ui->setupUi(this);
    ICCommandKeyWrapper *wrapper;
    wrapper = new ICCommandKeyWrapper(ui->connectFixture1ToolButton, IC::VKEY_CLIP1ON);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->connectFixture2ToolButton, IC::VKEY_CLIP2ON);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->connectFixture3ToolButton, IC::VKEY_CLIP3ON);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->connectFixture4ToolButton, IC::VKEY_CLIP4ON);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->connectSucker1ToolButton, IC::VKEY_CLIP5ON);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->connectSucker2ToolButton, IC::VKEY_CLIP6ON);
    wrappers_.append(wrapper);

    wrapper = new ICCommandKeyWrapper(ui->disconnectFixture1ToolButton, IC::VKEY_CLIP1OFF);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->disconnectFixture2ToolButton, IC::VKEY_CLIP2OFF);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->disconnectFixture3ToolButton, IC::VKEY_CLIP3OFF);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->disconnectFixture4ToolButton, IC::VKEY_CLIP4OFF);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->disconnectSucker1ToolButton, IC::VKEY_CLIP5OFF);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->disconnectSucker2ToolButton, IC::VKEY_CLIP6OFF);
    wrappers_.append(wrapper);

    ui->reserve1InLabel->hide();
    ui->reserve2InLabel->hide();

    wrapper = new ICCommandKeyWrapper(ui->connectReserve1ToolButton, IC::VKEY_RESERVE1_ON);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->connectReserve2ToolButton, IC::VKEY_RESERVE2_ON);
    wrappers_.append(wrapper);

    wrapper = new ICCommandKeyWrapper(ui->disconnectReserve1ToolButton, IC::VKEY_RESERVE1_OFF);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->disconnectReserve2ToolButton, IC::VKEY_RESERVE2_OFF);
    wrappers_.append(wrapper);

    wrapper = new ICCommandKeyWrapper(ui->conveyorOnButton, IC::VKEY_CLIP8ON);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->onInjectionButton, IC::VKEY_CLIP7ON);
    wrappers_.append(wrapper);

    wrapper = new ICCommandKeyWrapper(ui->conveyorOFFButton, IC::VKEY_CLIP8OFF);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->offInjectionButton, IC::VKEY_CLIP7OFF);
    wrappers_.append(wrapper);
}

HCManualFixtureFrame::~HCManualFixtureFrame()
{
    delete ui;
    qDeleteAll(wrappers_);
}

void HCManualFixtureFrame::showEvent(QShowEvent *e)
{
    QFrame::showEvent(e);
    //    connect(ICVirtualHost::GlobalVirtualHost(),
    //            SIGNAL(StatusRefreshed()),
    //            this,
    //            SLOT(StatusRefreshed()));
    timerID_ = ICTimerPool::Instance()->Start(ICTimerPool::RefreshTime, this, SLOT(StatusRefreshed()));
}

void HCManualFixtureFrame::hideEvent(QHideEvent *e)
{
    QFrame::hideEvent(e);
    //    disconnect(ICVirtualHost::GlobalVirtualHost(),
    //               SIGNAL(StatusRefreshed()),
    //               this,
    //               SLOT(StatusRefreshed()));
    ICTimerPool::Instance()->Stop(timerID_, this, SLOT(StatusRefreshed()));
}

void HCManualFixtureFrame::changeEvent(QEvent *e)
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

void HCManualFixtureFrame::StatusRefreshed()
{
    static QPixmap off(":/resource/ledgray(16).png");
    static QPixmap on(":/resource/ledgreen(16).png");
    static QPixmap inOn(":/resource/ledred(16).png");
    static ICVirtualHost *host = ICVirtualHost::GlobalVirtualHost();
    if(host->IsClipOn(0))
    {
        if(!clips_.at(0))
        {
            clips_.setBit(0);
            ui->fixture1StatusLabel->setPixmap(on);
        }
    }
    else
    {
        if(clips_.at(0))
        {
            clips_.clearBit(0);
            ui->fixture1StatusLabel->setPixmap(off);
        }
    }
    if(host->IsClipOn(1))
    {
        if(!clips_.at(1))
        {
            clips_.setBit(1);
            ui->fixture2StatusLabel->setPixmap(on);
        }
    }
    else
    {
        if(clips_.at(1))
        {
            clips_.clearBit(1);
            ui->fixture2StatusLabel->setPixmap(off);
        }
    }
    if(host->IsOutputOn(20))
    {
        if(!clips_.at(2))
        {
            clips_.setBit(2);
            ui->fixture3StatusLabel->setPixmap(on);
        }
    }
    else
    {
        if(clips_.at(2))
        {
            clips_.clearBit(2);
            ui->fixture3StatusLabel->setPixmap(off);
        }
    }
    if(host->IsClipOn(3))
    {
        if(!clips_.at(3))
        {
            clips_.setBit(3);
            ui->fixture4StatusLabel->setPixmap(on);
        }
    }
    else
    {
        if(clips_.at(3))
        {
            clips_.clearBit(3);
            ui->fixture4StatusLabel->setPixmap(off);
        }
    }
    if(host->IsInputOn(2))
    {
        if(!clips_.at(4))
        {
            clips_.setBit(4);
            ui->fixture1InLabel->setPixmap(inOn);
        }
    }
    else
    {
        if(clips_.at(4))
        {
            clips_.clearBit(4);
            ui->fixture1InLabel->setPixmap(off);
        }
    }
    if(host->IsInputOn(3))
    {
        if(!clips_.at(5))
        {
            clips_.setBit(5);
            ui->fixture2InLabel->setPixmap(inOn);
        }
    }
    else
    {
        if(clips_.at(5))
        {
            clips_.clearBit(5);
            ui->fixture2InLabel->setPixmap(off);
        }
    }
    if(host->IsInputOn(20))
    {
        if(!clips_.at(6))
        {
            clips_.setBit(6);
            ui->fixture3InLabel->setPixmap(inOn);
        }
    }
    else
    {
        if(clips_.at(6))
        {
            clips_.clearBit(6);
            ui->fixture3InLabel->setPixmap(off);
        }
    }
    if(host->IsInputOn(9))
    {
        if(!clips_.at(7))
        {
            clips_.setBit(7);
            ui->fixture4InLabel->setPixmap(inOn);
        }
    }
    else
    {
        if(clips_.at(7))
        {
            clips_.clearBit(7);
            ui->fixture4InLabel->setPixmap(off);
        }
    }

    if(host->PeripheryOutput(0) == 1)
    {
        if(host->IsOutputOn(7))
        {
            ui->reserve1StatusLabel->setPixmap(on);

        }
        else
        {
            ui->reserve1StatusLabel->setPixmap(off);
        }
    }

    if(host->PeripheryOutput(1) == 1)
    {
        if(host->IsOutputOn(10))
        {
            ui->reserve2StatusLabel->setPixmap(on);
        }
        else
        {
            ui->reserve2StatusLabel->setPixmap(off);
        }
    }

    if(host->IsClipOn(6))
    {
        ui->injectionStatusLabel->setPixmap(on);
    }
    else
    {
        ui->injectionStatusLabel->setPixmap(off);
    }

    if(host->IsClipOn(7))
    {
        ui->conveyorStatusLabel->setPixmap(on);
    }
    else
    {
        ui->conveyorStatusLabel->setPixmap(off);
    }

    ui->sucker1Label->setPixmap(host->IsInputOn(5) ? inOn : off);
    ui->sucker2Label->setPixmap(host->IsInputOn(4) ? inOn : off);

    ui->sucker1StatusLabel->setPixmap(host->IsOutputOn(5) ? on : off);
    ui->sucker2StatusLabel->setPixmap(host->IsOutputOn(4) ? on : off);
}
