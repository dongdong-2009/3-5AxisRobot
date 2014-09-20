#include "hcmanualreservepage.h"
#include "ui_hcmanualreservepage.h"
#include "icvirtualkey.h"
#include "iccommandkeywrapper.h"
#include "icvirtualhost.h"

QList<QLabel*> inLabels;
QList<QLabel*> outLabels;

HCManualReservePage::HCManualReservePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HCManualReservePage),
    clips_(32, false)
{
    ui->setupUi(this);
//    ui->reserve1InLabel->hide();
//    ui->reserve2InLabel->hide();
//    ui->reserve3InLabel->hide();
//    ui->reserve4InLabel->hide();
//    ui->reserve5InLabel->hide();
//    ui->reserve6InLabel->hide();
    ICCommandKeyWrapper *wrapper;
    wrapper = new ICCommandKeyWrapper(ui->connectReserve1ToolButton, IC::VKEY_RESERVE1_ON);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->connectReserve2ToolButton, IC::VKEY_RESERVE2_ON);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->connectReserve3ToolButton, IC::VKEY_RESERVE3_ON);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->connectReserve4ToolButton, IC::VKEY_RESERVE4_ON);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->connectReserve5ToolButton, IC::VKEY_RESERVE5_ON);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->connectReserve6ToolButton, IC::VKEY_RESERVE6_ON);
    wrappers_.append(wrapper);

    wrapper = new ICCommandKeyWrapper(ui->disconnectReserve1ToolButton, IC::VKEY_RESERVE1_OFF);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->disconnectReserve2ToolButton, IC::VKEY_RESERVE2_OFF);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->disconnectReserve3ToolButton, IC::VKEY_RESERVE3_OFF);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->disconnectReserve4ToolButton, IC::VKEY_RESERVE4_OFF);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->disconnectReserve5ToolButton, IC::VKEY_RESERVE5_OFF);
    wrappers_.append(wrapper);
    wrapper = new ICCommandKeyWrapper(ui->disconnectReserve6ToolButton, IC::VKEY_RESERVE6_OFF);
    wrappers_.append(wrapper);

    inLabels<<ui->reserve1InLabel<<ui->reserve2InLabel<<ui->reserve3InLabel
              <<ui->reserve4InLabel<<ui->reserve5InLabel<<ui->reserve6InLabel;

    outLabels<<ui->reserve1StatusLabel<<ui->reserve2StatusLabel<<ui->reserve3StatusLabel
               <<ui->reserve4StatusLabel<<ui->reserve5StatusLabel<<ui->reserve6StatusLabel;

}

HCManualReservePage::~HCManualReservePage()
{
    delete ui;
    qDeleteAll(wrappers_);
}

void HCManualReservePage::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void HCManualReservePage::showEvent(QShowEvent *e)
{
    QWidget::showEvent(e);
    connect(ICVirtualHost::GlobalVirtualHost(),
            SIGNAL(StatusRefreshed()),
            this,
            SLOT(StatusRefreshed()));
}

void HCManualReservePage::hideEvent(QHideEvent *e)
{
    QWidget::hideEvent(e);
    disconnect(ICVirtualHost::GlobalVirtualHost(),
            SIGNAL(StatusRefreshed()),
            this,
            SLOT(StatusRefreshed()));
}

void HCManualReservePage::StatusRefreshed()
{
    static QPixmap off(":/resource/ledgray(16).png");
    static QPixmap on(":/resource/ledgreen(16).png");
    static QPixmap inOn(":/resource/ledred(16).png");
    static ICVirtualHost *host = ICVirtualHost::GlobalVirtualHost();
    for(int i = 0; i != inLabels.size(); ++i)
    {
        if(host->IsInputOn(16 + i))
        {
            if(!clips_.at(i))
            {
                clips_.setBit(i);
                inLabels[i]->setPixmap(inOn);
            }
        }
        else
        {
            if(clips_.at(i))
            {
                clips_.clearBit(i);
                inLabels[i]->setPixmap(off);
            }
        }
    }

    for(int i = 0; i != outLabels.size(); ++i)
    {
        if(host->IsOutputOn(16 + i))
        {
            if(!clips_.at(i + inLabels.size()))
            {
                clips_.setBit(i + inLabels.size());
                outLabels[i]->setPixmap(on);
            }
        }
        else
        {
            if(clips_.at(i + inLabels.size()))
            {
                clips_.clearBit(i + inLabels.size());
                outLabels[i]->setPixmap(off);
            }
        }
    }


}
