#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "iciopage.h"
#include "icvirtualhost.h"
#include "icvirtualhost.h"

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
    for(int i = 0; i != 6; ++i)
    {
        recsLabels_.append(NULL);
    }
    for(int i = 0; i != 4; ++i)
    {
        ioLabels_.append(NULL);
        adjustLabels_.append(NULL);
    }
    servoOutLabels_.append(NULL);
    servoOutLabels_.append(NULL);
    servoInLabels_.append(NULL);
    servoInLabels_.append(NULL);
    servoInLabels_.append(NULL);
    servoInLabels_.append(NULL);
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
            if(points.at(i).PointNum() == tr("Y017"))
            {
                backupDescrMap_.insert(0, points.at(i));
            }
            else if(points.at(i).PointNum() == tr("Y022"))
            {
                backupDescrMap_.insert(1, points.at(i));
            }
            else if(points.at(i).PointNum() == tr("Y031"))
            {
                backupDescrMap_.insert(2, points.at(i));
            }
            else if(points.at(i).PointNum() == tr("Y032"))
            {
                backupDescrMap_.insert(3, points.at(i));
            }
            else if(points.at(i).PointNum() == tr("Y035"))
            {
                backupDescrMap_.insert(4, points.at(i));
            }
            else if(points.at(i).PointNum() == tr("Y036"))
            {
                backupDescrMap_.insert(5, points.at(i));
            }
            else if(points.at(i).PointNum() == tr("Y023"))
            {
                backupDescrMap_.insert(6, points.at(i));
            }
            else if(points.at(i).PointNum() == tr("Y026"))
            {
                backupDescrMap_.insert(7, points.at(i));
            }
            else if(points.at(i).PointNum() == tr("X017"))
            {
                backupDescrMap_.insert(8, points.at(i));
            }
            else if(points.at(i).PointNum() == tr("X020"))
            {
                backupDescrMap_.insert(9, points.at(i));
            }
            else if(points.at(i).PointNum() == tr("X022"))
            {
                backupDescrMap_.insert(10, points.at(i));
            }
            else if(points.at(i).PointNum() == tr("X035"))
            {
                backupDescrMap_.insert(11, points.at(i));
            }
            else if(points.at(i).PointNum() == tr("X025"))
            {
                backupDescrMap_.insert(12, points.at(i));
            }
            else if(points.at(i).PointNum() == tr("X024"))
            {
                backupDescrMap_.insert(13, points.at(i));
            }

            descrLabels_.at(i)->setText(points.at(i).PointDescription());
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
            if(point.PointNum() == tr("Y017"))
            {
                recsLabels_[0] = (descr);
                backupDescrMap_.insert(0, point);
            }
            else if(point.PointNum() == tr("Y022"))
            {
                recsLabels_[1] = descr;
                backupDescrMap_.insert(1, point);
            }
            else if(point.PointNum() == tr("Y031"))
            {
                recsLabels_[2] = descr;
                backupDescrMap_.insert(2, point);
            }
            else if(point.PointNum() == tr("Y032"))
            {
                recsLabels_[3] = descr;
                backupDescrMap_.insert(3, point);
            }
            else if(point.PointNum() == tr("Y035"))
            {
                recsLabels_[4] = descr;
                backupDescrMap_.insert(4, point);
            }
            else if(point.PointNum() == tr("Y036"))
            {
                recsLabels_[5] = descr;
                backupDescrMap_.insert(5, point);
            }
            else if(point.PointNum() == tr("Y010"))
            {
                ioLabels_[0] = descr ;
            }
            else if(point.PointNum() == tr("Y011"))
            {
                ioLabels_[1] = descr ;
            }
            else if(point.PointNum() == tr("X010"))
            {
                ioLabels_[2] = descr ;
            }
            else if(point.PointNum() == tr("X011"))
            {
                ioLabels_[3] = descr ;
            }

            else if(point.PointNum() == tr("X023"))
            {
                adjustLabels_[0] = descr;
            }
//            else if(point.PointNum() == tr("X026"))
//            {
//                adjustLabels_[1] = descr;
//            }
            else if(point.PointNum() == tr("X030"))
            {
                adjustLabels_[1] = descr;
            }
            else if(point.PointNum() == tr("X033"))
            {
                adjustLabels_[2] = descr;
            }
            else if(point.PointNum() == tr("Y023"))
            {
                backupDescrMap_.insert(6, points.at(i));
                servoOutLabels_[0] =descr;
            }
            else if(point.PointNum() == tr("Y026"))
            {
                backupDescrMap_.insert(7, points.at(i));
                servoOutLabels_[1] =descr;
            }
            else if(point.PointNum() == tr("X017"))
            {
                backupDescrMap_.insert(8, points.at(i));
                servoInLabels_[0] =descr;
            }
            else if(point.PointNum() == tr("X020"))
            {
                backupDescrMap_.insert(9, points.at(i));
                servoInLabels_[1] =descr;
            }
            else if(point.PointNum() == tr("X022"))
            {
                backupDescrMap_.insert(10, points.at(i));
                servoInLabels_[2] =descr;
            }
            else if(point.PointNum() == tr("X035"))
            {
                backupDescrMap_.insert(11, points.at(i));
                servoInLabels_[3] =descr;
            }
            nums->setFixedWidth(50);
            descr->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
            descr->setFixedWidth(243);

            itemLayout_->addWidget(nums);
            itemLayout_->addWidget(descr);
            itemLayout_->addWidget(leds);
            itemLayout_->addStretch();
            frameLayout_->addLayout(itemLayout_);
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
    for(int i = 0; i != recsLabels_.size(); ++i)
    {
        if(recsLabels_.at(i) != NULL)
        {
            if(host->PeripheryOutput(i) == 1)
            {
                if(i > 3)
                    recsLabels_[i]->setText(tr("Sucker") + QString::number(i - 1) + tr("Valve"));
                else
                    recsLabels_[i]->setText(tr("Reserve") + QString::number(i+1));
            }
            else
            {
                recsLabels_[i]->setText(backupDescrMap_.value(i).PointDescription());
            }
        }
    }
//    if(recsLabels_.at(0) != NULL)
//    {
//        if(host->PeripheryOutput(0) == 1)
//        {
//            recsLabels_[0]->setText(tr("Thimble 2") + QString::number(0));
//        }
//        else
//        {
//            recsLabels_[0]->setText(backupDescrMap_.value(0).PointDescription());
//        }
//    }

        if(ICVirtualHost::GlobalVirtualHost()->FixtureDefine() == 1)
        {
            if(ioLabels_.at(0) != NULL)
            {
                ioLabels_[0]->setText(tr("Horizon-1"));
            }
            if(ioLabels_.at(2) != NULL)
            {
                if(host->AxisDefine(ICVirtualHost::ICAxis_AxisC) == ICVirtualHost::ICAxisDefine_Servo)
                {
                    ioLabels_[2]->setText(tr("C Origin"));
                }
                else
                {
                    ioLabels_[2]->setText(tr("Horizon-1"));
                }
            }

        }
        else
        {
            if(ioLabels_.at(0) != NULL)
            {
                ioLabels_[0]->setText(tr("Vertical-1"));
            }
            if(ioLabels_.at(2) != NULL)
            {
                if(host->AxisDefine(ICVirtualHost::ICAxis_AxisC) == ICVirtualHost::ICAxisDefine_Servo)
                {
                    ioLabels_[2]->setText(tr("C Origin"));
                }
                else
                {
                    ioLabels_[2]->setText(tr("Vertical-1"));
                }
            }
        }
        if(ICVirtualHost::GlobalVirtualHost()->FixtureDefine() == 1)
        {
            if(ioLabels_.at(1) != NULL)
            {
                ioLabels_[1]->setText(tr("Vertical-1"));
            }
            if(ioLabels_.at(3) != NULL)
            {
                if(host->AxisDefine(ICVirtualHost::ICAxis_AxisC) == ICVirtualHost::ICAxisDefine_Servo)
                {
                    ioLabels_[3]->setText(tr("C Origin Limit"));
                }
                else
                {
                    ioLabels_[3]->setText(tr("Vertical-1"));
                }
            }
        }
        else
        {
            if(ioLabels_.at(1) != NULL)
            {
                ioLabels_[1]->setText(tr("Horizon-1"));
            }
            if(ioLabels_.at(3) != NULL)
            {
                if(host->AxisDefine(ICVirtualHost::ICAxis_AxisC) == ICVirtualHost::ICAxisDefine_Servo)
                {
                    ioLabels_[3]->setText(tr("C Origin Limit"));
                }
                else
                {
                    ioLabels_[3]->setText(tr("Horizon-1"));
                }
            }
        }


        if(host->AxisDefine(ICVirtualHost::ICAxis_AxisX2) == ICVirtualHost::ICAxisDefine_Pneumatic)
        {
            if(adjustLabels_.at(0) != NULL)
            {
                adjustLabels_[0]->setText(tr("Adjust Sub Forward"));
            }
//            if(adjustLabels_.at(1) != NULL)
//            {
//                adjustLabels_[1]->setText(tr("Adjust Sub Down"));
//            }
        }
        else
        {
            if(adjustLabels_.at(0) != NULL)
            {
                adjustLabels_[0]->setText(tr("A Origin/Horizon-2"));
            }
//            if(adjustLabels_.at(1) != NULL)
//            {
//                adjustLabels_[1]->setText(tr("Reserve"));
//            }
        }
        if(host->AxisDefine(ICVirtualHost::ICAxis_AxisY2) == ICVirtualHost::ICAxisDefine_Pneumatic)
        {
            if(adjustLabels_.at(1) != NULL)
            {
                adjustLabels_[1]->setText(tr("Adjust Sub Backward"));
            }
            if(adjustLabels_.at(2) != NULL)
            {
                adjustLabels_[2]->setText(tr("Adjust Sub Up"));
            }
        }
        else
        {
            if(adjustLabels_.at(1) != NULL)
            {
                adjustLabels_[1]->setText(tr("X2 In Limit"));
            }
            if(adjustLabels_.at(2) != NULL)
            {
                adjustLabels_[2]->setText(tr("Y2 In Limit"));
            }
        }

        if(host->AxisDefine(ICVirtualHost::ICAxis_AxisY1) == ICVirtualHost::ICAxisDefine_Pneumatic)
        {
            if(servoOutLabels_[0] != NULL)
                servoOutLabels_[0]->setText(tr("Main Arm down valve"));
            if(servoInLabels_[2] != NULL)
                servoInLabels_[2]->setText(tr("Main Arm Down Limit"));
            if(servoInLabels_[3] != NULL)
                servoInLabels_[3]->setText(tr("Main Arm Up Limit"));
        }
        else
        {
            if(servoOutLabels_[0] != NULL)
                servoOutLabels_[0]->setText(tr("Aid Pneumatic"));
            if(servoInLabels_[2] != NULL)
                servoInLabels_[2]->setText(backupDescrMap_.value(10).PointDescription());
            if(servoInLabels_[3] != NULL)
                servoInLabels_[3]->setText(backupDescrMap_.value(11).PointDescription());
        }


        if(host->AxisDefine(ICVirtualHost::ICAxis_AxisX1) == ICVirtualHost::ICAxisDefine_Pneumatic)
        {
            if(servoOutLabels_[1] != NULL)
                servoOutLabels_[1]->setText(tr("Main Arm Foward valve"));
            if(servoInLabels_[0] != NULL)
                servoInLabels_[0]->setText(tr("Main Arm Forward Limit"));
            if(servoInLabels_[1] != NULL)
                servoInLabels_[1]->setText(tr("Main Arm Backward Limit"));
        }
        else
        {
            if(servoOutLabels_[1] != NULL)
                servoOutLabels_[1]->setText(backupDescrMap_.value(7).PointDescription());
            if(servoInLabels_[0] != NULL)
                servoInLabels_[0]->setText(backupDescrMap_.value(8).PointDescription());
            if(servoInLabels_[1] != NULL)
                servoInLabels_[1]->setText(backupDescrMap_.value(9).PointDescription());
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
