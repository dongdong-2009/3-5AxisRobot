#include "hcmanualfixtureframe.h"
#include "ui_hcmanualfixtureframe.h"
#include "iccommandkeywrapper.h"
#include "icvirtualkey.h"
#include "icvirtualhost.h"
#include "ictimerpool.h"

QList<QLabel*> fixtureInLabels;
QList<QLabel*> fixtureOutLabels;

HCManualFixtureFrame::HCManualFixtureFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::HCManualFixtureFrame),
    clips_(32, false)
{
    ui->setupUi(this);
    ICCommandKeyWrapper *wrapper;
    wrapper = new ICCommandKeyWrapper(ui->ms1On, IC::VKEY_CLIP1ON);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->ms2On, IC::VKEY_CLIP2ON);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->ms3On, IC::VKEY_CLIP3ON);
    wrappers_.append(wrapper);

    wrapper = new ICCommandKeyWrapper(ui->ss1On, IC::VKEY_CLIP4ON);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->ss2On, IC::VKEY_CLIP5ON);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->ss3On, IC::VKEY_CLIP6ON);
    wrappers_.append(wrapper);

    wrapper = new ICCommandKeyWrapper(ui->mc1On, IC::VKEY_CLIP7ON);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->mc2On, IC::VKEY_CLIP8ON);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->mc3On, IC::VKEY_CLIP9ON);
    wrappers_.append(wrapper);

    wrapper = new ICCommandKeyWrapper(ui->sc1On, IC::VKEY_CLIP10ON);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->sc2On, IC::VKEY_CLIP11ON);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->sc3On, IC::VKEY_CLIP12ON);
    wrappers_.append(wrapper);

    wrapper = new ICCommandKeyWrapper(ui->ms1Off, IC::VKEY_CLIP1OFF);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->ms2Off, IC::VKEY_CLIP2OFF);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->ms3Off, IC::VKEY_CLIP3OFF);
    wrappers_.append(wrapper);

    wrapper = new ICCommandKeyWrapper(ui->ss1Off, IC::VKEY_CLIP4OFF);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->ss2Off, IC::VKEY_CLIP5OFF);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->ss3Off, IC::VKEY_CLIP6OFF);
    wrappers_.append(wrapper);

    wrapper = new ICCommandKeyWrapper(ui->ms1Off, IC::VKEY_CLIP1OFF);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->ms2Off, IC::VKEY_CLIP2OFF);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->ms3Off, IC::VKEY_CLIP3OFF);
    wrappers_.append(wrapper);

    wrapper = new ICCommandKeyWrapper(ui->ss1Off, IC::VKEY_CLIP4OFF);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->ss2Off, IC::VKEY_CLIP5OFF);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->ss3Off, IC::VKEY_CLIP6OFF);
    wrappers_.append(wrapper);

    wrapper = new ICCommandKeyWrapper(ui->mc1Off, IC::VKEY_CLIP7OFF);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->mc2Off, IC::VKEY_CLIP8OFF);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->mc3Off, IC::VKEY_CLIP9OFF);
    wrappers_.append(wrapper);

    wrapper = new ICCommandKeyWrapper(ui->sc1Off, IC::VKEY_CLIP10OFF);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->sc2Off, IC::VKEY_CLIP11OFF);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->sc3Off, IC::VKEY_CLIP12OFF);
    wrappers_.append(wrapper);

    fixtureInLabels<<ui->ms1In<<ui->ms2In<<ui->ms3In<<ui->ss1In<<ui->ss2In<<ui->ss3In
              <<ui->mc1In<<ui->mc2In<<ui->mc3In<<ui->sc1In<<ui->sc2In<<ui->sc3In;

    fixtureOutLabels<<ui->ms1Out<<ui->ms2Out<<ui->ms3Out<<ui->ss1Out<<ui->ss2Out<<ui->ss3Out
              <<ui->mc1Out<<ui->mc2Out<<ui->mc3Out<<ui->sc1Out<<ui->sc2Out<<ui->sc3Out;
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
    for(int i = 0; i != fixtureInLabels.size(); ++i)
    {
        if(host->IsInputOn(15 + i))
        {
            if(!clips_.at(i))
            {
                clips_.setBit(i);
                fixtureInLabels[i]->setPixmap(inOn);
            }
        }
        else
        {
            if(clips_.at(i))
            {
                clips_.clearBit(i);
                fixtureInLabels[i]->setPixmap(off);
            }
        }
    }

    for(int i = 0; i != fixtureOutLabels.size(); ++i)
    {
        if(host->IsOutputOn(15 + i))
        {
            if(!clips_.at(i + fixtureOutLabels.size()))
            {
                clips_.setBit(i + fixtureOutLabels.size());
                fixtureOutLabels[i]->setPixmap(on);
            }
        }
        else
        {
            if(clips_.at(i + fixtureOutLabels.size()))
            {
                clips_.clearBit(i + fixtureOutLabels.size());
                fixtureOutLabels[i]->setPixmap(off);
            }
        }
    }

}
