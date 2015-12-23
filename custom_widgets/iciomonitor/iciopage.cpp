#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "iciopage.h"
#include "icvirtualhost.h"
#include "icvirtualhost.h"


QLabel* labelNull;
const QString X010 = "X010";
const QString X011 = "X011";
const QString X016 = "X016";
const QString X020 = "X020";
const QString X022 = "X022";
const QString X035 = "X035";
const QString X041 = "X041";
const QString X025 = "X025";
const QString X024 = "X024";
const QString X030 = "X030";
const QString X031 = "X031";
const QString X032 = "X032";
const QString X033 = "X033";
const QString X023 = "X023";
const QString X037 = "X037";
const QString X040 = "X040";
const QString X042 = "X042";
const QString X026 = "X026";
const QString Y017 = "Y017";
const QString Y022 = "Y022";
const QString Y031 = "Y031";
const QString Y032 = "Y032";
const QString Y010 = "Y010";
const QString Y011 = "Y011";
const QString Y024 = "Y024";
const QString Y046 = "Y046";
const QString Y023 = "Y023";
const QString Y035 = "Y035";
//const QString Y023 = "Y036";
ICIOPage::ICIOPage(QWidget *parent) :
    QWidget(parent),
    inputs_(64, false),
    outputs_(64, false),
    offPixmap_(":/resource/ledgray(16).png"),
    inputOnPixmap_(":/resource/ledred(16).png"),
    outputOnPixmap_(":/resource/ledgreen(16).png")
{
    frameLayout_ = new QVBoxLayout();
#ifdef HC_SK_5
    frameLayout_->setContentsMargins(2, 0, 2, 0);
    frameLayout_->setSpacing(12);
#else
    frameLayout_->setContentsMargins(2, 10, 2, 2);
    frameLayout_->setSpacing(15);
#endif
    this->setLayout(frameLayout_);

    labelNull = new QLabel();
    labelNull->hide();
    multiLabels.insert(X010, labelNull);
    multiLabels.insert(X011, labelNull);
    multiLabels.insert(X016, labelNull);
    multiLabels.insert(X020, labelNull);
    multiLabels.insert(X022, labelNull);
    multiLabels.insert(X035, labelNull);
    multiLabels.insert(X041, labelNull);
    multiLabels.insert(X025, labelNull);
    multiLabels.insert(X024, labelNull);
    multiLabels.insert(X030, labelNull);
    multiLabels.insert(X031, labelNull);
    multiLabels.insert(X032, labelNull);
    multiLabels.insert(X033, labelNull);
    multiLabels.insert(X023, labelNull);
    multiLabels.insert(X037, labelNull);
    multiLabels.insert(X026, labelNull);
    multiLabels.insert(X040, labelNull);
    multiLabels.insert(X042, labelNull);
    multiLabels.insert(Y017, labelNull);
    multiLabels.insert(Y022, labelNull);
    multiLabels.insert(Y031, labelNull);
    multiLabels.insert(Y032, labelNull);
    multiLabels.insert(Y010, labelNull);
    multiLabels.insert(Y011, labelNull);
    multiLabels.insert(Y024, labelNull);
    multiLabels.insert(Y046, labelNull);
    multiLabels.insert(Y023, labelNull);
    multiLabels.insert(Y035, labelNull);
    //    multiLabels.insert(Y036, labelNull);
}
ICIOPage::~ICIOPage()
{
    delete frameLayout_;
}


void ICIOPage::BindingIOPoints(const QList<ICIOPoint> &points)
{
    const int size = points.size();
    QLabel *nums;
    QLabel *leds;
    QLabel *descr;
    QHBoxLayout* itemLayout_;

    ICIOPoint point;
    if(!descrLabels_.isEmpty())
    {
        for(int i = 0; i != size; ++i)
        {
            descrLabels_.at(i)->setText(points.at(i).PointDescription());
            //            if(multiLabels.contains(point.PointNum()))
            //                multiLabels.insert(point.PointNum(), descr);
        }
    }
    else
    {
        for(int i = 0; i != size; ++i)
        {
            point = points.at(i);
            nums = new QLabel(point.PointNum());
            descr = new QLabel(point.PointDescription());
            leds = new QLabel();
            leds->setMaximumHeight(18);
            leds->setMinimumHeight(18);
            itemLayout_ = new QHBoxLayout();
            leds->setPixmap(offPixmap_);
            ledToPoint_.insert(leds, point);
            descrLabels_.append(descr);

            nums->setFixedWidth(50);
            descr->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
            descr->setFixedWidth(243);

            itemLayout_->addWidget(nums);
            itemLayout_->addWidget(descr);
            itemLayout_->addWidget(leds);
            itemLayout_->addStretch();
            frameLayout_->addLayout(itemLayout_);

            if(multiLabels.contains(point.PointNum()))
            {
                multiLabels.insert(point.PointNum(), descr);
                //                qDebug()<<point.PointNum()<<descr;
            }
        }
        frameLayout_->addStretch();
    }
}

void ICIOPage::UpdateIO()
{
    QMap<QLabel*, ICIOPoint>::iterator p = ledToPoint_.begin();
    ICVirtualHost* virtualHost = ICVirtualHost::GlobalVirtualHost();
    int pos;
    if(PageType() == Input)
    {
        while(p != ledToPoint_.end())
        {
            pos = p.value().HostIOPos();
            if(virtualHost->IsInputOn(pos))
            {
                if(!inputs_.at(pos))
                {
                    inputs_.setBit(pos);
                    p.key()->setPixmap(inputOnPixmap_);
                }
            }
            else
            {
                if(inputs_.at(pos))
                {
                    inputs_.clearBit(pos);
                    p.key()->setPixmap(offPixmap_);
                }
            }
            ++p;
        }
    }
    else
    {
        while(p != ledToPoint_.end())
        {
            pos = p.value().HostIOPos();
            if(virtualHost->IsOutputOn(pos))
            {
                if(!outputs_.at(pos))
                {
                    outputs_.setBit(pos);
                    p.key()->setPixmap(outputOnPixmap_);
                }
            }
            else
            {
                if(outputs_.at(pos))
                {
                    outputs_.clearBit(pos);
                    p.key()->setPixmap(offPixmap_);
                }
            }
            ++p;
        }
    }
}

void ICIOPage::showEvent(QShowEvent *e)
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    if(host->PeripheryOutput(0))
    {
        multiLabels.value(Y017)->setText(tr("Reserve-1"));
    }
    else
    {
        multiLabels.value(Y017)->setText(tr("M0"));
    }
    if(host->PeripheryOutput(1))
    {
        multiLabels.value(Y022)->setText(tr("Reserve-2"));
    }
    else
    {
        multiLabels.value(Y022)->setText(tr("M1"));
    }
    if(host->PeripheryOutput(2))
    {
        multiLabels.value(Y031)->setText(tr("Reserve-3"));
    }
    else
    {
        multiLabels.value(Y031)->setText(tr("M2"));
    }
    if(host->PeripheryOutput(3))
    {
        multiLabels.value(Y032)->setText(tr("Reserve-4"));
    }
    else
    {
        multiLabels.value(Y032)->setText(tr("M3"));
    }
    if(host->PeripheryOutput(4))
    {
        multiLabels.value(Y035)->setText(tr("Sucker-3 Valve"));
    }
    else
    {
        multiLabels.value(Y035)->setText(tr("Motor Invert"));
    }


    if(host->AxisDefine(ICVirtualHost::ICAxis_AxisC) == ICVirtualHost::ICAxisDefine_Servo)
    {
        multiLabels.value(X010)->setText(tr("C Origin"));
        multiLabels.value(X011)->setText(tr("C end limit"));
        //        multiLabels.value(X010)->setText(tr("Horizon-1 Limit"));
        //        multiLabels.value(X011)->setText(tr("Vertical-1 Limit "));
    }
    else if(ICVirtualHost::GlobalVirtualHost()->FixtureDefine() == 1)
    {
        multiLabels.value(X010)->setText(tr("Horizon-1 Limit"));
        multiLabels.value(X011)->setText(tr("Vertical-1 Limit "));

        multiLabels.value(Y010)->setText(tr("Horizon-1 Valve"));
        multiLabels.value(Y011)->setText(tr("Vertical-1 Valve "));
    }
    else
    {
        multiLabels.value(X011)->setText(tr("Horizon-1 Limit"));
        multiLabels.value(X010)->setText(tr("Vertical-1 Limit"));
        multiLabels.value(Y011)->setText(tr("Horizon-1 Valve"));
        multiLabels.value(Y010)->setText(tr("Vertical-1 Valve"));
    }

    if(host->AxisDefine(ICVirtualHost::ICAxis_AxisX1) == ICVirtualHost::ICAxisDefine_Servo)
    {
        multiLabels.value(X020)->setText(tr("X1 Origin"));
        multiLabels.value(X016)->setText(tr("X1 end Limit"));
    }
    else if(host->AxisDefine(ICVirtualHost::ICAxis_AxisX1) == ICVirtualHost::ICAxisDefine_Pneumatic)
    {
        multiLabels.value(X020)->setText(tr("X1 BW Limit"));
        multiLabels.value(X016)->setText(tr("X1 FW Limit"));
    }
    else
    {
        multiLabels.value(X020)->setText(tr("X020"));
        multiLabels.value(X016)->setText(tr("X016"));
    }

    if(host->AxisDefine(ICVirtualHost::ICAxis_AxisY1) == ICVirtualHost::ICAxisDefine_Servo)
    {
        multiLabels.value(X022)->setText(tr("Y1 Begin Limit"));
        multiLabels.value(X035)->setText(tr("Y1 Origin"));
        multiLabels.value(Y023)->setText(tr("Aid Pneu"));
    }
    else if(host->AxisDefine(ICVirtualHost::ICAxis_AxisY1) == ICVirtualHost::ICAxisDefine_Pneumatic)
    {
        multiLabels.value(X022)->setText(tr("Y1 DW Limit"));
        multiLabels.value(X035)->setText(tr("Y1 UP Limit"));
        multiLabels.value(Y023)->setText(tr("Y1 DW Valve"));
    }
    else
    {
        multiLabels.value(X022)->setText(tr("X022"));
        multiLabels.value(X035)->setText(tr("X035"));
        multiLabels.value(Y023)->setText(tr("Y023"));
    }

    if(host->AxisDefine(ICVirtualHost::ICAxis_AxisZ) == ICVirtualHost::ICAxisDefine_Servo)
    {
        multiLabels.value(X025)->setText(tr("Z Origin"));
        multiLabels.value(X041)->setText(tr("Z begin Limit"));
        multiLabels.value(X024)->setText(tr("Sec zone outside"));
        multiLabels.value(X042)->setText(tr("Z end Limit"));

    }
    else if(host->AxisDefine(ICVirtualHost::ICAxis_AxisZ) == ICVirtualHost::ICAxisDefine_Pneumatic)
    {
        multiLabels.value(X025)->setText(tr("Z BW Limit"));
        multiLabels.value(X024)->setText(tr("Z FW Limit"));
        multiLabels.value(X041)->setText(tr("Middle Release"));
        multiLabels.value(X042)->setText(tr("X042"));

    }
    else
    {
        multiLabels.value(X041)->setText(tr("X041"));
        multiLabels.value(X025)->setText(tr("X025"));
        multiLabels.value(X024)->setText(tr("X024"));
        multiLabels.value(X042)->setText(tr("X042"));
    }

    if(host->AxisDefine(ICVirtualHost::ICAxis_AxisX2) == ICVirtualHost::ICAxisDefine_Servo)
    {
        multiLabels.value(X031)->setText(tr("X2 Origin"));
        multiLabels.value(X030)->setText(tr("X2 Begin Limit"));
    }
    else if(host->AxisDefine(ICVirtualHost::ICAxis_AxisX2) == ICVirtualHost::ICAxisDefine_Pneumatic)
    {
        multiLabels.value(X031)->setText(tr("X2 BW Limit"));
        if(host->HasSubArmForwardLimit())
            multiLabels.value(X030)->setText(tr("X2 FW Limit"));
        else
            multiLabels.value(X030)->setText(tr("X030"));
    }
    else
    {
        multiLabels.value(X030)->setText(tr("X030"));
        multiLabels.value(X031)->setText(tr("X031"));
    }

    if(host->AxisDefine(ICVirtualHost::ICAxis_AxisY2) == ICVirtualHost::ICAxisDefine_Servo)
    {
        multiLabels.value(X032)->setText(tr("Y2 Origin"));
        multiLabels.value(X033)->setText(tr("Y2 Begin Limit"));
    }
    else if(host->AxisDefine(ICVirtualHost::ICAxis_AxisY2) == ICVirtualHost::ICAxisDefine_Pneumatic)
    {
        multiLabels.value(X032)->setText(tr("Y2 UP Limit"));
        if(host->HasSubArmForwardLimit())
            multiLabels.value(X033)->setText(tr("Y2 DW Limit"));
        else
            multiLabels.value(X033)->setText(tr("X033"));
    }
    else
    {
        multiLabels.value(X032)->setText(tr("X032"));
        multiLabels.value(X033)->setText(tr("X033"));
    }

    if(host->AxisDefine(ICVirtualHost::ICAxis_AxisA) == ICVirtualHost::ICAxisDefine_Servo)
    {
        multiLabels.value(X023)->setText(tr("A Origin"));
        multiLabels.value(X037)->setText(tr("A begin limit"));
        //        multiLabels.value(X023)->setText(tr("A Origin/Horizon-2 Limit"));
//        multiLabels.value(X037)->setText(tr("Vertical-2 Limit "));
    }
    else if(host->AxisDefine(ICVirtualHost::ICAxis_AxisA) == ICVirtualHost::ICAxisDefine_None)
    {
        multiLabels.value(X023)->setText(tr("M0"));
        multiLabels.value(X037)->setText(tr("X037"));
        multiLabels.value(Y024)->setText(tr("Y024"));
        multiLabels.value(Y046)->setText(tr("Y046"));
    }
    else if(ICVirtualHost::GlobalVirtualHost()->FixtureDefine() == 1)
    {
        multiLabels.value(X023)->setText(tr("Horizon-2 Limit"));
        multiLabels.value(X037)->setText(tr("Vertical-2 Limit "));

        multiLabels.value(Y024)->setText(tr("Horizon-2 Valve"));
        multiLabels.value(Y046)->setText(tr("Vertical-2 Valve "));
    }
    else
    {
        multiLabels.value(X037)->setText(tr("Horizon-2 Limit"));
        multiLabels.value(X023)->setText(tr("Vertical-2 Limit"));
        multiLabels.value(Y046)->setText(tr("Horizon-2 Valve"));
        multiLabels.value(Y024)->setText(tr("Vertical-2 Valve"));
    }

    if(host->AxisDefine(ICVirtualHost::ICAxis_AxisB) == ICVirtualHost::ICAxisDefine_Servo ||
            host->AxisDefine(ICVirtualHost::ICAxis_AxisB) == ICVirtualHost::ICAxisDefine_Pneumatic)
    {
        multiLabels.value(X026)->setText(tr("B Begin limit"));
        multiLabels.value(X040)->setText(tr("B Origin"));
        //        multiLabels.value(X037)->setText(tr("A end limit"));
    }
    else
    {
        multiLabels.value(X026)->setText(tr("X026"));
        multiLabels.value(X040)->setText(tr("X040"));
        //        multiLabels.value(X037)->setText(tr("X037"));
        //        multiLabels.value(Y024)->setText(tr("Y024"));
        //        multiLabels.value(Y046)->setText(tr("Y046"));
    }






    QWidget::showEvent(e);
    connect(ICVirtualHost::GlobalVirtualHost(),
            SIGNAL(StatusRefreshed()),
            this,
            SLOT(UpdateIO()));
}

void ICIOPage::hideEvent(QHideEvent *e)
{
    QWidget::hideEvent(e);
    disconnect(ICVirtualHost::GlobalVirtualHost(),
               SIGNAL(StatusRefreshed()),
               this,
               SLOT(UpdateIO()));
}
