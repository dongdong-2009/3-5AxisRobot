#include "ichcprogrammonitorframe.h"
#include "ui_ichcprogrammonitorframe.h"


#include "icinstructparam.h"
#include "icparameterconversion.h"
#include "icvirtualhost.h"
#include "icautorunrevise.h"
#include "icactioncommand.h"
#include "icmacrosubroutine.h"
#include "icvirtualkey.h"
#include "ickeyboard.h"
#include "icmessagebox.h"
#include "icprogramheadframe.h"
#include "icparameterssave.h"
#include "icmold.h"
#include "iccaretipui.h"

QMessageBox* checkMessageBox;

ICHCProgramMonitorFrame::ICHCProgramMonitorFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ICHCProgramMonitorFrame),
    isModify_(false),
    currentStepItem_(NULL),
    isFollow_(true),
    oldStep_(-1),
    currentMoldNum_(8),
    switchOn_(":/resource/switch_on.png"),
    switchOff_(":/resource/switch_off.png")
{
    ui->setupUi(this);

    autoRunRevise_ = new ICAutoRunRevise(this);
    InitSignal();
    //    UpdateHostParam();
    //    ICInstructParam::Instance()->UpdateHostParam();
    //    moldContent_ = ICMold::CurrentMold()->MoldContent();
    connect(&timer_,
            SIGNAL(timeout()),
            this,
            SLOT(OnTimeOut()));
    connect(&refreshTimer_,
            SIGNAL(timeout()),
            SLOT(StatusRefreshed()));
    fixtureToCountMap_.insert(ICMold::ACTCLIP1ON, fixtureCount_ + 0);
    fixtureToCountMap_.insert(ICMold::ACTCLIP2ON, fixtureCount_ + 1);
    fixtureToCountMap_.insert(ICMold::ACTCLIP3ON, fixtureCount_ + 2);
    fixtureToCountMap_.insert(ICMold::ACTCLIP4ON, fixtureCount_ + 3);
    fixtureToCountMap_.insert(ICMold::ACTCLIP5ON, fixtureCount_ + 4);
    fixtureToCountMap_.insert(ICMold::ACTCLIP6ON, fixtureCount_ + 5);
    checkToFixtureMap_.insert(0, ICMold::ACTCLIP1ON);
    checkToFixtureMap_.insert(1, ICMold::ACTCLIP2ON);
    checkToFixtureMap_.insert(2, ICMold::ACTCLIP3ON);
    checkToFixtureMap_.insert(3, ICMold::ACTCLIP4ON);
    checkToFixtureMap_.insert(4, ICMold::ACTCLIP5ON);
    checkToFixtureMap_.insert(5, ICMold::ACTCLIP6ON);
    checkResultMap_.insert(0, tr("Has not teach check Fixture-1!"));
    checkResultMap_.insert(1, tr("Has not teach check Fixture-2!"));
    checkResultMap_.insert(2, tr("Has not teach check Fixture-3!"));
    checkResultMap_.insert(3, tr("Has not teach check Fixture-4!"));
    checkResultMap_.insert(4, tr("Has not teach check Sucker-1!"));
    checkResultMap_.insert(5, tr("Has not teach check Sucker-2!"));

    connect(ICProgramHeadFrame::Instance(),
            SIGNAL(LevelChanged(int)),
            this,
            SLOT(LevelChanged(int)));
    LevelChanged(ICProgramHeadFrame::Instance()->CurrentLevel());
    checkMessageBox = new ICMessageBox(this);
    ui->pauseButton->hide();
}

ICHCProgramMonitorFrame::~ICHCProgramMonitorFrame()
{
    delete autoRunRevise_;
    delete checkMessageBox;
    delete ui;
}

void ICHCProgramMonitorFrame::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        checkResultMap_.insert(0, tr("Has not teach check Fixture-1!"));
        checkResultMap_.insert(1, tr("Has not teach check Fixture-2!"));
        checkResultMap_.insert(2, tr("Has not teach check Fixture-3!"));
        checkResultMap_.insert(3, tr("Has not teach check Fixture-4!"));
        checkResultMap_.insert(4, tr("Has not teach check Sucker-1!"));
        checkResultMap_.insert(5, tr("Has not teach check Sucker-2!"));
        break;
    default:
        break;
    }
}

void ICHCProgramMonitorFrame::showEvent(QShowEvent *e)
{
    //    ICCommandProcessor::Instance()->ExecuteHCCommand(IC::CMD_TurnStop, 0);
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    ICVirtualHost::GlobalVirtualHost()->SetSpeedEnable(false);
//    ui->speedEnableButton->setIcon(switchOff_);
    ui->speedEnableButton->setText(tr("Speed Disable"));
    ui->speedEnableButton->setChecked(false);
    SetProduct(ICMold::CurrentMold()->MoldParam(ICMold::Product));
    currentMoldNum_ = 8;
    UpdateHostParam();
//    programListBackup_ = ICMold::CurrentMold()->ToUIItems();
    if(!isModify_)
    {
        programListBackup_ = ICMold::CurrentMold()->ToUIItems();
    }
    QFrame::showEvent(e);
    connect(ICVirtualHost::GlobalVirtualHost(),
            SIGNAL(StepChanged(int)),
            this,
            SLOT(SelectCurrentStep(int)));
    connect(ICVirtualHost::GlobalVirtualHost(),
            SIGNAL(SubStepChanged(uint8_t*)),
            this,
            SLOT(SubStepChanged(uint8_t*)));
    connect(ICVirtualHost::GlobalVirtualHost(),
            SIGNAL(MoldNumChanged(int)),
            this,
            SLOT(MoldNumChanged(int)));
    refreshTimer_.start(20);
    timer_.start(30000);

//    if(ICVirtualHost::GlobalVirtualHost()->CurrentStatus() != ICVirtualHost::Auto)
//    {
//        ICCommandProcessor::Instance()->ExecuteHCCommand(IC::CMD_TurnAuto,
//                                                         0,
//                                                         ICMold::CurrentMold()->SyncAct() + ICMacroSubroutine::Instance()->SyncAct(),
//                                                         ICMold::CurrentMold()->SyncSum() + ICMacroSubroutine::Instance()->SyncSum());
//    }

    autoRunRevise_->SetFlagSel(Flags());
    int pSize;
    ICMoldItem* item;
    for(int i =0; i != programList_.size(); ++i)
    {
        pSize = programList_.at(i).ItemCount();
        for(int j = 0; j != pSize; ++j)
        {
            item = programList_[i].MoldItemAt(j);
            if(item->Action() == ICMold::ACTCOMMENT)
            {
                flagToSetp.insert(item->Flag(), item->Num());
            }
        }
    }

    CareCheck();
    if(!ICVirtualHost::GlobalVirtualHost()->IsFixtureCheck())
    {
        return;
    }
    memset(fixtureCount_, 0, sizeof(int) * 6);
    QList<ICMoldItem> moldItems = ICMold::UIItemToMoldItem(programList_);
    ICMoldItem tmpItem;
    int tmpClip;
    int *tmpCount;
    for(int i = 0; i != moldItems.size(); ++i)
    {
        tmpItem = moldItems.at(i);
        if(tmpItem.Action() == ICMold::ACT_Cut)
        {
            if(checkToFixtureMap_.contains(tmpItem.SVal()))
            {
                tmpCount = fixtureToCountMap_.value(checkToFixtureMap_.value(tmpItem.SVal()));
                if(*tmpCount > 0)
                {
                    *tmpCount -= 1;
                }
            }
            continue;
        }
        if(tmpItem.IsClip())
        {
            tmpClip = tmpItem.Clip();
            if(fixtureToCountMap_.contains(tmpClip))
            {
                *(fixtureToCountMap_.value(tmpClip)) += 1;
            }
        }
    }
    QString checkResult;
    bool needWarn = false;
    for(int i = 0; i != 6; ++i)
    {
        if(fixtureCount_[i] != 0)
        {
            checkResult.append(checkResultMap_.value(i) + "\n");
            needWarn = true;
        }
    }
    if(!checkResult.isEmpty())
    {
//        ICMessageBox::ICWarning(this,
//                             tr("Warning"),
//                             checkResult);
        checkMessageBox->setWindowTitle(tr("Warning"));
        checkMessageBox->setText(checkResult);
        checkMessageBox->setWindowFlags(checkMessageBox->windowFlags() | Qt::WindowStaysOnTopHint);
        checkMessageBox->show();
    }


    //    if(needWarn)
    //    {
    //        if(QMessageBox::warning(this,
    //                             tr("Warning"),
    //                             checkResult + tr("Do you want to ignor this warning?"),
    //                             QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    //        {
//                ICVirtualHost::GlobalVirtualHost()->SetFixtureCheck(false);
    //        }
    //    }
}


void ICHCProgramMonitorFrame::hideEvent(QHideEvent *e)
{
    qDebug("isModify change to false in hide");
    autoRunRevise_->hide();
    if(isModify_)
    {
        if(currentMoldNum_ == 8)
        {
            ICMold::CurrentMold()->SetMoldContent(ICMold::UIItemToMoldItem(programList_));
        }
        ICMold::CurrentMold()->SaveMoldFile();
//        isModify_ = false;
        if(ICKeyboard::Instace()->CurrentSwitchStatus() != ICKeyboard::KS_AutoStatu)
         {
             isModify_ = false;
         }
    }
    //    modifyMap_.clear();
    QFrame::hideEvent(e);
    disconnect(ICVirtualHost::GlobalVirtualHost(),
               SIGNAL(StepChanged(int)),
               this,
               SLOT(SelectCurrentStep(int)));
    disconnect(ICVirtualHost::GlobalVirtualHost(),
               SIGNAL(SubStepChanged(uint8_t*)),
               this,
               SLOT(SubStepChanged(uint8_t*)));
    disconnect(ICVirtualHost::GlobalVirtualHost(),
               SIGNAL(MoldNumChanged(int)),
               this,
               SLOT(MoldNumChanged(int)));
    timer_.stop();
    refreshTimer_.stop();
    ICVirtualHost::GlobalVirtualHost()->SetSpeedEnable(false);
//    ui->speedEnableButton->setIcon(switchOff_);
    ui->speedEnableButton->setText(tr("Speed Disable"));
    ui->speedEnableButton->setChecked(false);
    checkMessageBox->reject();

    //    ICCommandProcessor::Instance()->ExecuteHCCommand(IC::CMD_TurnStop,0);
}

void ICHCProgramMonitorFrame::LevelChanged(int level)
{
    if(level >=  ICParametersSave::MachineAdmin)
    {
        ui->editToolButton->show();
    }
    else
    {
        ui->editToolButton->hide();
    }
}
void ICHCProgramMonitorFrame::SetTime(int time)
{
    ui->timeLabel->setText(ICParameterConversion::TransThisIntToThisText(time, 2));
}

//void ICHCProgramMonitorFrame::SetFullTime(int fullTime)
//{
//    ui->fullTimeLabel->setText(ICParameterConversion::TransThisIntToThisText(fullTime, 1));
//}

void ICHCProgramMonitorFrame::SetProduct(int product)
{
    ui->settedProductsLabel->setText(QString::number(product));
}

//void ICHCProgramMonitorFrame::SetCurrentFinished(int currentFinished)
//{
//    ui->currentProductsLabel->setText(QString::number(currentFinished));
//}

void ICHCProgramMonitorFrame::StatusRefreshed()
{

    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    newTime_ = host->HostStatus(ICVirtualHost::DbgZ0).toUInt();
    if(host->CurrentStatus() != ICVirtualHost::Auto) return;
    if(host->currentMoldNum() != currentMoldNum_)
    {
        MoldNumChanged(host->currentMoldNum());
    }

    if(newTime_ != oldTime_)
    {

        oldTime_ = newTime_;
        SetTime(newTime_);
    }
    ui->getTime->setText(ICParameterConversion::TransThisIntToThisText(host->HostStatus(ICVirtualHost::DbgY1).toUInt(), 2));
    newCycleTimes_ = host->HostStatus(ICVirtualHost::DbgX1).toUInt();
    if(newCycleTimes_ != oldCycleTimes_)
    {

        oldCycleTimes_ = newCycleTimes_;
        //        ui->cycleTimes->setText(QString::number(oldCycleTimes_));
    }
    newGoodP_ = host->HostStatus(ICVirtualHost::DbgY0).toUInt();
    if(newGoodP_ != oldGoodP_)
    {
        oldGoodP_ = newGoodP_;
        ui->goodProducts->setText(QString::number(oldGoodP_));
    }
    newStackedP_ = host->HostStatus(ICVirtualHost::DbgZ1).toUInt();
    if(newStackedP_ != oldStackedP_)
    {
        oldStackedP_ = newStackedP_;
        ui->stackedProducts->setText(QString::number(oldStackedP_));
    }
    int status = host->HostStatus(ICVirtualHost::DbgP0).toInt();
    int mode = host->HostStatus(ICVirtualHost::DbgX0).toInt();
    if(status == 2 && mode != ICVirtualHost::AutoSingleCycle)
    {
        ui->infoLabel->setText(tr("Single run ready"));
    }
    else if(status == 4 && mode != ICVirtualHost::AutoOneCycle && mode != ICVirtualHost::AutoStopping)
    {
        ui->infoLabel->setText(tr("Single cycle ready"));
    }
    else
    {
        ui->infoLabel->setText("");
    }

    static uint oldCycleTime = 0;

    int cycleTime = host->HostStatus(ICVirtualHost::Time).toUInt();
    if(cycleTime != oldCycleTime)
    {
        ui->robotCycle->setText(QString().sprintf("%.2f", cycleTime / qreal(100)));
        oldCycleTime = cycleTime;
    }
    static int oldFinishCount = -1;
    int  finishCount = host->FinishProductCount();
    if(oldFinishCount != finishCount)
    {
        ui->finishedProductsLabel->setText(QString::number(finishCount));
        oldFinishCount = finishCount;
    }
}

void ICHCProgramMonitorFrame::SelectCurrentStep(int currentStep)
{
    currentStep = ICMold::CurrentMold()->DisplayStep(currentStep);
    if((currentStep != 0  && currentStep < oldStep_ && isModify_) ||
            (oldStep_ == 0 && currentStep > oldStep_ && isModify_))
    {
        //        QMap<ICMoldItem*, ICMoldItem>::iterator p = modifyMap_.begin();
        //        while(p != modifyMap_.end())
        //        {
        //            *(p.key()) = p.value();
        //            ++p;
        //        }

        if(currentMoldNum_ == 8)
        {
            ICMold::CurrentMold()->SetMoldContent(ICMold::UIItemToMoldItem(programList_));
            ICMold::CurrentMold()->SaveMoldFile();
            programListBackup_ = programList_;
            qDebug("run modify");
            UpdateHostParam();
            isModify_ = false;
        }
        //        modifyMap_.clear();
    }
    oldStep_ = currentStep;
    if(currentStep < 0 || currentStep >= programList_.size())
    {
        qDebug()<<"current step wrong"<<currentStep;
        return;
    }
    if(!isFollow_)
    {
        return;
    }
    ui->moldContentListWidget->clearSelection();
    ICGroupMoldUIItem* gItem = &programList_[currentStep];
    currentStepItem_ = gItem;
    //    int selectedCount = gItem->ItemCount();
    startIndex_ = 0;
    for(int i = 0; i != currentStep; ++i)
    {
        startIndex_ += programList_.at(i).ItemCount();
    }
    if(startIndex_ < ui->moldContentListWidget->count())
    {
        ui->moldContentListWidget->scrollToItem(ui->moldContentListWidget->item(startIndex_));
    }
    const int topItemCount = gItem->TopItemCount();
    int nextTopItemIndex = startIndex_;
    for(int i = 0; i != topItemCount; ++i)
    {
        if(nextTopItemIndex < ui->moldContentListWidget->count())
        {
            ui->moldContentListWidget->item(nextTopItemIndex)->setSelected(true);
        }
        if(gItem->at(i).SubItemCount() != 0)
        {
            nextTopItemIndex += gItem->at(i).ItemCount();
        }
        else
        {
            ++nextTopItemIndex;
        }
    }
}

void ICHCProgramMonitorFrame::SubStepChanged(uint8_t* subStep)
{
    if(!isFollow_)
    {
        return;
    }
    if(currentStepItem_ == NULL)
    {
        return;
    }
    const int topItemCount = currentStepItem_->TopItemCount();
    int currentSub = 0;
    int nextTopItemIndex = startIndex_ + 1;
    int size;
    for(int i = 0; i != topItemCount; ++i)
    {
        if(currentStepItem_->at(i).SubItemCount() != 0)
        {
            if(subStep[currentSub] != 0)
            {
                size = nextTopItemIndex + subStep[currentSub] - 1;
                if(size < ui->moldContentListWidget->count())
                {
                    ui->moldContentListWidget->item(nextTopItemIndex + subStep[currentSub] - 1)->setSelected(false);
                }
            }
            size = nextTopItemIndex + (subStep[currentSub]);
            if(size < ui->moldContentListWidget->count())
            {
                ui->moldContentListWidget->item(nextTopItemIndex + (subStep[currentSub++]))->setSelected(true);
            }
            nextTopItemIndex += currentStepItem_->at(i).ItemCount();
        }
        else
        {
            ++nextTopItemIndex;
        }
    }

}

void ICHCProgramMonitorFrame::UpdateHostParam()
{
    qDebug("m update");
    startIndex_ = 0;
    currentStepItem_ = NULL;
    if(currentMoldNum_ == 8)
    {
        programList_ = ICMold::CurrentMold()->ToUIItems();
    }
    else if(currentMoldNum_ >= 0 && currentMoldNum_ < 8)
    {
        programList_ = ICMold::MoldItemToUIItem(ICMacroSubroutine::Instance()->SubRoutine(currentMoldNum_));
    }
    else
    {
        currentMoldNum_ = 8;
        programList_ = ICMold::CurrentMold()->ToUIItems();
        //        return;
    }
    qDebug("after m update");

    qDebug() << "currentmoldNum:" << currentMoldNum_ ;
    UpdateUIProgramList_();
}

void ICHCProgramMonitorFrame::InitSignal()
{
    //    connect(ICInstructParam::Instance(),
    //            SIGNAL(HostParamChanged()),
    //            this,
    //            SLOT(UpdateHostParam()));
    //    connect(autoRunRevise_,
    //            SIGNAL(MoldItemChanged()),
    //            this,
    //            SLOT(MoldItemChanged()));
}


void ICHCProgramMonitorFrame::on_editToolButton_clicked()
{
    if(currentMoldNum_ != 8)
    {
        return;
    }
    const int selectedRow = ui->moldContentListWidget->currentRow();
    if(selectedRow < 0)
    {
        return;
    }
#ifdef Q_WS_QWS
    if(ICVirtualHost::GlobalVirtualHost()->CurrentStatus() != ICVirtualHost::Auto)
    {
        return;
    }
#endif
    int gIndex;
    int tIndex;
    int sIndex;
    qDebug("Before Find index");
    FindIndex_(selectedRow, gIndex, tIndex, sIndex);
    qDebug("End Find index");
    /************BUG#201**********/
//    if(programList_.at(gIndex).StepNum() == 0)  //表示待机点位置（自动运行时待机点位置不能删除）
//    {
//        QMessageBox::warning(this,
//                             tr("Warning"),
//                             tr("Can not edit standby position program"));
//        return;
//    }
    if(sIndex < 0)
    {
        qDebug("Sindex");
        ICTopMoldUIItem * topItem = &programList_[gIndex].at(tIndex);
//        ICTopMoldUIItem * topItemB = &programListBackup_[gIndex].at(tIndex);
        qDebug()<<(topItem == NULL);
        ICMoldItem* item = topItem->BaseItem();
        ICMoldItem * currentBackup;

        ICAutoAdjustCommand command;
        ICCommandProcessor* processor;
        ICMoldItem ret;
        qDebug("Before show editor");
        /*
         *调整对话框中标题栏文字显示
        */
        QString str = topItem->ToStringList().join("\n");
        if(str.size() > 37)
        {
            str.insert(38,"\n");
            str.insert(39,"\t");
        }
        if(str.size() > 65)
        {
            str.insert(66,"\n");
            str.insert(67,"\t");
        }

        /*****/
        bool isM = autoRunRevise_->ShowModifyItem(item, &ret, str);
//        if(item->Action() == ICMold::ACTCHECKINPUT)
//        {
//            ret.SetDVal(flagToSetp.value(ret.Flag(), 0) - ret.Num());
//        }
//        bool isM = autoRunRevise_->ShowModifyItem(item, &ret, topItem->ToStringList().join("\n"));
        if(isM)
        {          
          if(isModify_)
            {
                currentBackup = programListBackup_[gIndex].at(tIndex).BaseItem();
                item->SetDVal(ret.DVal());
                item->SetSVal(ret.SVal());
//                item->SetPos(currentBackup->Pos() + ret.Pos());
                item->SetActualPos(currentBackup->ActualPos() + ret.Pos() * 10);
//                if(item->Action() == ICMold::ACTCHECKINPUT)
//                    item->SetFlag(ret.Flag());
                item->ReSum();
                ICMoldItem toSendItem = *item;
                toSendItem.SetSeq(ICMold::CurrentMold()->ToHostSeq(item->Seq()));
                toSendItem.SetNum(ICMold::CurrentMold()->ToHostNum(toSendItem.Seq()));
                toSendItem.ReSum();
                UpdateUIProgramList_();
                processor = ICCommandProcessor::Instance();
                command.SetSlave(processor->SlaveID());
                command.SetSequence(toSendItem.Seq());
                command.SetDelayTime(toSendItem.DVal());
                command.SetSpeed(toSendItem.SVal());
                command.SetDPos(ret.Pos());
                command.SetGMValue(toSendItem.GMVal());
                command.SetCheckSum(toSendItem.Sum());
            }
            else
            {
                currentBackup = programList_[gIndex].at(tIndex).BaseItem();
                currentBackup->SetDVal(ret.DVal());
                currentBackup->SetSVal(ret.SVal());
//                currentBackup->SetPos(currentBackup->Pos() + ret.Pos());
                currentBackup->SetActualPos(currentBackup->ActualPos() + ret.Pos() * 10);
//                if(currentBackup->Action() == ICMold::ACTCHECKINPUT)
//                    currentBackup->SetFlag(ret.Flag());
                currentBackup->ReSum();
                ICMoldItem toSendItem = *currentBackup;
                toSendItem.SetSeq(ICMold::CurrentMold()->ToHostSeq(currentBackup->Seq()));
                toSendItem.SetNum(ICMold::CurrentMold()->ToHostNum(toSendItem.Seq()));
                toSendItem.ReSum();
                UpdateUIProgramList_();
                processor = ICCommandProcessor::Instance();
                command.SetSlave(processor->SlaveID());
                command.SetSequence(toSendItem.Seq());
                command.SetDelayTime(toSendItem.DVal());
                command.SetSpeed(toSendItem.SVal());
                command.SetDPos(ret.Pos());
                command.SetGMValue(toSendItem.GMVal());
                command.SetCheckSum(toSendItem.Sum());
            }
#ifdef Q_WS_X11
          isM = true ;
#else
            isM = processor->ExecuteCommand(command).toBool();
#endif
            qDebug()<<"after show"<<isM;
            if(isM)
            {
                ICMold::CurrentMold()->SetMoldContent(ICMold::UIItemToMoldItem(programList_));
            }
            isModify_ = isModify_ || isM;
        }
    }
    else
    {
        qDebug("Else Sindex");
        ICSubMoldUIItem *subItem = &programList_[gIndex].at(tIndex).at(sIndex);
//        ICSubMoldUIItem *subItemB = &programListBackup_[gIndex].at(tIndex).at(sIndex);
        ICMoldItem* item = subItem->BaseItem();
        ICMoldItem * currentBackup;
        ICMoldItem ret;
        ICAutoAdjustCommand command;
        ICCommandProcessor* processor;
        bool isM = autoRunRevise_->ShowModifyItem(subItem->BaseItem(), &ret, subItem->ToString());
//        if(item->Action() == ICMold::ACTCHECKINPUT)
//        {
//            ret.SetDVal(flagToSetp.value(ret.Flag(), 0) - ret.Num());
//        }
        if(isM)
        {
            if(isModify_)
            {
               currentBackup = programListBackup_[gIndex].at(tIndex).at(sIndex).BaseItem();
               item->SetDVal(ret.DVal());
               item->SetSVal(ret.SVal());
//               item->SetPos(currentBackup->Pos() + ret.Pos());
               item->SetActualPos(currentBackup->ActualPos() + ret.Pos() * 10);
//               if(item->Action() == ICMold::ACTCHECKINPUT)
//                   item->SetFlag(ret.Flag());
               item->ReSum();
               ICMoldItem toSendItem = *item;
               toSendItem.SetSeq(ICMold::CurrentMold()->ToHostSeq(item->Seq()));
               toSendItem.SetNum(ICMold::CurrentMold()->ToHostNum(toSendItem.Seq()));
               toSendItem.ReSum();
               UpdateUIProgramList_();
               processor = ICCommandProcessor::Instance();
               command.SetSlave(processor->SlaveID());
               command.SetSequence(toSendItem.Seq());
               command.SetDelayTime(toSendItem.DVal());
               command.SetSpeed(toSendItem.SVal());
               command.SetDPos(ret.Pos());
               command.SetGMValue(toSendItem.GMVal());
               command.SetCheckSum(toSendItem.Sum());
            }
            else
            {
               currentBackup = programList_[gIndex].at(tIndex).at(sIndex).BaseItem();
               currentBackup->SetDVal(ret.DVal());
               currentBackup->SetSVal(ret.SVal());
//               currentBackup->SetPos(currentBackup->Pos() + ret.Pos());
               currentBackup->SetActualPos(currentBackup->ActualPos() + ret.Pos() * 10);
//               if(currentBackup->Action() == ICMold::ACTCHECKINPUT)
//                   currentBackup->SetFlag(ret.Flag());
               currentBackup->ReSum();
               ICMoldItem toSendItem = *currentBackup;
               toSendItem.SetSeq(ICMold::CurrentMold()->ToHostSeq(currentBackup->Seq()));
               toSendItem.SetNum(ICMold::CurrentMold()->ToHostNum(toSendItem.Seq()));
               toSendItem.ReSum();
               UpdateUIProgramList_();
               processor = ICCommandProcessor::Instance();
               command.SetSlave(processor->SlaveID());
               command.SetSequence(toSendItem.Seq());
               command.SetDelayTime(toSendItem.DVal());
               command.SetSpeed(toSendItem.SVal());
               command.SetDPos(ret.Pos());
               command.SetGMValue(toSendItem.GMVal());
               command.SetCheckSum(toSendItem.Sum());
            }
            isM = processor->ExecuteCommand(command).toBool();
            qDebug()<<"after show"<<isM;
            if(isM)
            {
                ICMold::CurrentMold()->SetMoldContent(ICMold::UIItemToMoldItem(programList_));
            }
            isModify_ = isModify_ || isM;

        }
    }
    qDebug()<<"Modify"<<isModify_;

}

void ICHCProgramMonitorFrame::MoldItemChanged()
{
    //    ICMold::Modify(QList<ICMoldItem>()<<item, moldContent_);

    isModify_ = true;
}

void ICHCProgramMonitorFrame::UpdateUIProgramList_()
{
    ui->moldContentListWidget->clear();
    qDebug("after clear");
    ui->moldContentListWidget->addItems(ICMold::UIItemsToStringList(programList_, currentMoldNum_ == 8));
    ICGroupMoldUIItem groupItem;
    int topItemRowCount;
    int index = 0;
    QColor color;
    ICMoldItem* tmp = NULL;
    for(int i = 0; i != programList_.size(); ++i)
    {
        (i % 2 == 0 ? color.setRgb(255, 255, 154):color.setRgb(154, 255, 255));
        groupItem = programList_.at(i);
        topItemRowCount = groupItem.ItemCount();
        for(int j = 0; j != topItemRowCount; ++j)
        {
            tmp = groupItem.MoldItemAt(j);
            if(tmp != NULL)
            {
                if(tmp->Num() == 0)
                {
//                    if(tmp->Action() == ICMold::GY || tmp->Action() == ICMold::GQ)
//                        ui->moldContentListWidget->item(j + index)->setBackgroundColor(QColor(0xF5, 0x8E, 0xB7));
                    if(tmp->Action() == ICMold::GX || tmp->Action() == ICMold::GP)
                        ui->moldContentListWidget->item(j + index)->setBackgroundColor(QColor(0xF7, 0x9F, 0x9C));
                    else
                        ui->moldContentListWidget->item(j + index)->setBackgroundColor(QColor(239, 235, 231));
//                    ui->moldContentListWidget->item(j + index)->setBackgroundColor(QColor(239, 235, 231));
                    //                    ui->moldContentListWidget->item(j + index)->setForeground(QColor("white"));
                }
                else if(tmp->Action() == ICInstructParam::ACT_WaitMoldOpened)
                {
                    ui->moldContentListWidget->item(j + index)->setBackgroundColor("red");
                }
                else
                {
                    ui->moldContentListWidget->item(j + index)->setBackgroundColor(color);
                }
            }
        }
        index += topItemRowCount;
    }
    qDebug("updatge end");
}

//void ICHCProgramMonitorFrame::on_singleStepButton_clicked()
//{
//    ICCommandProcessor::Instance()->ExecuteVirtualKeyCommand(IC::VKEY_F6);
//}

void ICHCProgramMonitorFrame::FindIndex_(int currentIndex, int& groupItemIndex, int &topItemIndex, int &subItemIndex)
{
    for(int i = 0; i != programList_.size(); ++i)
    {
        if(currentIndex < programList_.at(i).ItemCount())
        {
            groupItemIndex = i;
            for(int j = 0; j != programList_.at(i).TopItemCount(); ++j)
            {
                if(currentIndex < programList_.at(i).at(j).ItemCount())
                {
                    topItemIndex = j;
                    if(currentIndex == 0)
                    {
                        subItemIndex = -1;
                    }
                    else
                    {
                        subItemIndex = currentIndex - 1;
                    }
                    break;
                }
                else
                {
                    currentIndex -= programList_.at(i).at(j).ItemCount();
                }
            }
            break;
        }
        else
        {
            currentIndex -= programList_.at(i).ItemCount();
        }
    }
}

void ICHCProgramMonitorFrame::MoldNumChanged(int mold)
{
    this->blockSignals(true);
    currentMoldNum_ = mold;
    if(currentMoldNum_ != 8)
    {
        autoRunRevise_->hide();
    }
    UpdateHostParam();
    this->blockSignals(false);
}

void ICHCProgramMonitorFrame::on_followToolButton_clicked()
{
    if(isFollow_)
    {
        isFollow_ = false;
        ui->followToolButton->setIcon(QPixmap(":/resource/play.png"));
        ui->followToolButton->setText(tr("Follow"));
    }
    else
    {
        isFollow_ = true;
        ui->followToolButton->setIcon(QPixmap(":/resource/stop.png"));
        ui->followToolButton->setText(tr("No Follow"));
    }
}

void ICHCProgramMonitorFrame::on_speedEnableButton_clicked()
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    host->SetSpeedEnable(!host->IsSpeedEnable());
//    ui->speedEnableButton->setIcon(host->IsSpeedEnable()? switchOn_ : switchOff_);
    ui->speedEnableButton->setText(host->IsSpeedEnable() ? tr("Speed Enable") : tr("Speed Disable"));
}

void ICHCProgramMonitorFrame::OnTimeOut()
{
    ICVirtualHost *host = ICVirtualHost::GlobalVirtualHost();
    if(!host->HasTuneSpeed())
    {
        host->SetSpeedEnable(false);
//        ui->speedEnableButton->setIcon(switchOff_);
        ui->speedEnableButton->setText(tr("Speed Disable"));
        ui->speedEnableButton->setChecked(false);
    }
    host->SetTuneSpeed(false);
}

void ICHCProgramMonitorFrame::on_singleStepButton_pressed()
{
    ICKeyboard::Instace()->SetKeyValue(ICKeyboard::VFB_SingleStep);
    ICKeyboard::Instace()->SetPressed(true);
}

void ICHCProgramMonitorFrame::on_singleStepButton_released()
{
    ICKeyboard::Instace()->SetPressed(false);
}

void ICHCProgramMonitorFrame::on_cycle_clicked()
{
    ICCommandProcessor::Instance()->ExecuteVirtualKeyCommand(IC::VKEY_CYCLE);
}


void ICHCProgramMonitorFrame::on_pauseButton_toggled(bool checked)
{
    if(checked)
    {
//        ui->pauseButton->setText(tr("Run"));
        ICCommandProcessor::Instance()->ExecuteVirtualKeyCommand(IC::VKEY_PAUSE);
    }
    else
    {
//        ui->pauseButton->setText(tr("Pause"));
        ICCommandProcessor::Instance()->ExecuteVirtualKeyCommand(IC::VKEY_RESTART);

    }
}

QStringList ICHCProgramMonitorFrame::Flags()
{
    QStringList selList;
    int count;
    ICMoldItem* item;
    for(int i = 0; i != programList_.size(); ++i)
    {
        count = programList_.at(i).ItemCount();
        for(int j = 0; j != count; ++j)
        {
            item = programList_[i].MoldItemAt(j);
            if(item->Action() == ICMold::ACTCOMMENT)
            {
                selList.append(QString(tr("Flag[%1]:%2")
                                       .arg(item->Flag())
                                       .arg(item->Comment())));
            }
        }
    }
    return selList;
}

void ICHCProgramMonitorFrame::CareCheck()
{
    QDate now = QDate::currentDate();
    ICParametersSave *ps = ICParametersSave::Instance();
    bool needToCare = false;
    for(int i = 0;  i != 7; ++i)
    {
        if(now >= ps->NextCycle(i))
        {
            needToCare = true;
            break;
        }
    }
    if(needToCare)
    {
        ICCareTipUI careTip;
        careTip.exec();
    }
}
