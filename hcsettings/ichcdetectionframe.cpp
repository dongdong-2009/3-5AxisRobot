#include "ichcdetectionframe.h"
#include "ui_ichcdetectionframe.h"

#include "ictwoselectioncomboboxwrapper.h"
#include "icmold.h"
#include "icvirtualhost.h"
//#include "icactioncommand.h"

ICHCDetectionFrame::ICHCDetectionFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ICHCDetectionFrame)
{
    ui->setupUi(this);

    ICTwoSelectionComboBoxWrapper* wrapper;
    wrapper = new ICTwoSelectionComboBoxWrapper(ui->ms1, ICMold::StackCount0);
    wrappers_.append(wrapper);
    wrapper = new ICTwoSelectionComboBoxWrapper(ui->ms2, ICMold::StackCount1);
    wrappers_.append(wrapper);
    wrapper = new ICTwoSelectionComboBoxWrapper(ui->ms3, ICMold::StackCount2);
    wrappers_.append(wrapper);
    wrapper = new ICTwoSelectionComboBoxWrapper(ui->ss1, ICMold::StackCount3);
    wrappers_.append(wrapper);
    wrapper = new ICTwoSelectionComboBoxWrapper(ui->ss2, ICMold::CheckClip1);
    wrappers_.append(wrapper);
    wrapper = new ICTwoSelectionComboBoxWrapper(ui->ss3, ICMold::CheckClip2);
    wrappers_.append(wrapper);
    wrapper = new ICTwoSelectionComboBoxWrapper(ui->mc1, ICMold::CheckClip3);
    wrappers_.append(wrapper);
    wrapper = new ICTwoSelectionComboBoxWrapper(ui->mc2, ICMold::CheckClip4);
    wrappers_.append(wrapper);
    wrapper = new ICTwoSelectionComboBoxWrapper(ui->mc3, ICMold::CheckClip5);
    wrappers_.append(wrapper);
    wrapper = new ICTwoSelectionComboBoxWrapper(ui->sc1, ICMold::CheckClip6);
    wrappers_.append(wrapper);
    wrapper = new ICTwoSelectionComboBoxWrapper(ui->sc2, ICMold::CheckClip7);
    wrappers_.append(wrapper);
    wrapper = new ICTwoSelectionComboBoxWrapper(ui->sc3, ICMold::CheckClip8);
    wrappers_.append(wrapper);
//    wrapper = new ICTwoSelectionComboBoxWrapper(ui->detectSucker1ComboBox, ICMold::CheckClip5);
//    wrappers_.append(wrapper);
//    wrapper = new ICTwoSelectionComboBoxWrapper(ui->detectSucker2ComboBox, ICMold::CheckClip6);
//    wrappers_.append(wrapper);

//    wrapper = new ICTwoSelectionComboBoxWrapper(ui->standbyPositionBox, ICMold::StandbyPose);
//    wrappers_.append(wrapper);
    //    wrapper = new ICTwoSelectionComboBoxWrapper(ui->converyotComboBox, ICMold::CheckClip7);
    //    wrappers_.append(wrapper);
    //    wrapper = new ICTwoSelectionComboBoxWrapper(ui->injectionComboBox, ICMold::CheckClip8);
    //    wrappers_.append(wrapper);
    //    ui->converyotComboBox->hide();
    //    ui->injectionComboBox->hide();
    //    ui->label_13->hide();
    //    ui->label_8->hide();
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    ui->detectPressureComboBox->setCurrentIndex(qAbs(host->IsPressureCheck() - 1));
//    ui->detectSecurityComboBox->setCurrentIndex(qAbs(host->IsSecurityCheck() - 1));
//    ui->detectMidMoldComboBox->setCurrentIndex(qAbs(host->IsMidMoldCheck() - 1));
//    ui->ejectionLinkLockBox->setCurrentIndex(qAbs(host->IsEjectionLink() - 1));
//    ui->detectOriginBox->setCurrentIndex(qAbs(host->IsAlarmWhenOrigin() - 1));
    //    ui->detectPositionBox->setCurrentIndex(qAbs(host->IsPositionDetect() - 1));
//    ui->detectPositionBox->setCurrentIndex(host->TranserferPosition());
//    ui->originPositionBox->setCurrentIndex(host->OriginPosition());
//    ui->detectSucker1ComboBox->setCurrentIndex(host->IsCloseMoldEn());
//    ui->detectSucker2ComboBox->setCurrentIndex(host->IsAutoSignalUse());


    connect(ICMold::CurrentMold(),
            SIGNAL(MoldNumberParamChanged()),
            this,
            SLOT(OnMoldNumberParamChanged()));

//    ui->downPositionBox->hide();
//    ui->label_16->hide();
}

ICHCDetectionFrame::~ICHCDetectionFrame()
{
    delete ui;
    qDeleteAll(wrappers_);
}

void ICHCDetectionFrame::hideEvent(QHideEvent *e)
{
    if(ICVirtualHost::GlobalVirtualHost()->IsParamChanged())
    {
        qDebug("Detection hide");
        ICMold::CurrentMold()->SaveMoldParamsFile();
        ICVirtualHost::GlobalVirtualHost()->SaveSystemConfig();
        ICVirtualHost::GlobalVirtualHost()->ReConfigure();
    }
    //    ICCommandProcessor::Instance()->ExecuteHCCommand(IC::CMD_TurnStop, 0);
    QFrame::hideEvent(e);
}

void ICHCDetectionFrame::changeEvent(QEvent *e)
{
    QFrame::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
    {
        RetranslateUi_();
    }
    break;
    default:
        break;
    }
}
void ICHCDetectionFrame::on_detectPressureComboBox_activated(int index)
{
    bool isCheck = qAbs(index - 1);
    ICVirtualHost::GlobalVirtualHost()->SetPressureCheck(isCheck);
}

//void ICHCDetectionFrame::on_detectSecurityComboBox_activated(int index)
//{
//    bool isCheck = qAbs(index - 1);
//    ICVirtualHost::GlobalVirtualHost()->SetSecurityCheck(isCheck);
//}

//void ICHCDetectionFrame::on_detectMidMoldComboBox_activated(int index)
//{
//    bool isCheck = qAbs(index - 1);
//    ICVirtualHost::GlobalVirtualHost()->SetMidMoldCheck(isCheck);
//}

void ICHCDetectionFrame::OnMoldNumberParamChanged()
{
    for(int i = 0; i != wrappers_.size(); ++i)
    {
        wrappers_[i]->UpdateParameter();
    }
}

//void ICHCDetectionFrame::on_closeMoldStatusComboBox_activated(int index)
//{
//    bool isCheck = qAbs(index - 1);
//    ICVirtualHost::GlobalVirtualHost()->SetCloseMoldPermit(isCheck);
//}

//void ICHCDetectionFrame::on_ejectionLinkLockBox_activated(int index)
//{
//    bool isCheck = qAbs(index - 1);
//    ICVirtualHost::GlobalVirtualHost()->SetEjectionLink(isCheck);
//}

//void ICHCDetectionFrame::on_detectPositionBox_activated(int index)
//{
//    //    bool isCheck = qAbs(index - 1);
//    //    ICVirtualHost::GlobalVirtualHost()->SetPositionDetect(isCheck);
//    ICVirtualHost::GlobalVirtualHost()->SetTranserferPosition(index);
//}

//void ICHCDetectionFrame::on_detectOriginBox_activated(int index)
//{
//    bool isCheck = qAbs(index - 1);
//    ICVirtualHost::GlobalVirtualHost()->SetAlarmWhenOrigin(isCheck);
//}

//void ICHCDetectionFrame::on_originPositionBox_activated(int index)
//{
//    ICVirtualHost::GlobalVirtualHost()->SetOriginPosition(index);
//}

//void ICHCDetectionFrame::on_detectSucker1ComboBox_activated(int index)
//{
//    ICVirtualHost::GlobalVirtualHost()->SetCloseMoldEn(index);
//}

//void ICHCDetectionFrame::on_detectSucker2ComboBox_activated(int index)
//{
//    ICVirtualHost::GlobalVirtualHost()->SetAutoSignalUse(index);
//}


void ICHCDetectionFrame::RetranslateUi_()
{
    const QString rp = tr("Reversed Phase");
    const QString pp = tr("Positive Phase");
    const QString use = tr("Use");
    const QString noUse = tr("Not Use");
    ui->label_9->setText(tr("Detect Pressure"));
    ui->detectPressureComboBox->setItemText(0, noUse);
    ui->detectPressureComboBox->setItemText(1, use);
    ui->ms1l->setText(tr("MS1"));
    ui->ms2l->setText(tr("MS2"));
    ui->ms3l->setText(tr("MS3"));
    ui->ss1l->setText(tr("SS1"));
    ui->ss2l->setText(tr("SS2"));
    ui->ss3l->setText(tr("SS3"));
    ui->mc1l->setText(tr("MC1"));
    ui->mc2l->setText(tr("MC2"));
    ui->mc3l->setText(tr("MC3"));
    ui->sc1l->setText(tr("SC1"));
    ui->sc2l->setText(tr("SC2"));
    ui->sc3l->setText(tr("SC3"));
    ui->ms1->setItemText(1, rp);
    ui->ms1->setItemText(0, pp);
    ui->ms2->setItemText(1, rp);
    ui->ms2->setItemText(0, pp);
    ui->ms3->setItemText(1, rp);
    ui->ms3->setItemText(0, pp);
    ui->ss1->setItemText(1, rp);
    ui->ss1->setItemText(0, pp);
    ui->ss2->setItemText(1, rp);
    ui->ss2->setItemText(0, pp);
    ui->ss3->setItemText(1, rp);
    ui->ss3->setItemText(0, pp);
    ui->mc1->setItemText(1, rp);
    ui->mc1->setItemText(0, pp);
    ui->mc2->setItemText(1, rp);
    ui->mc2->setItemText(0, pp);
    ui->mc3->setItemText(1, rp);
    ui->mc3->setItemText(0, pp);
    ui->sc1->setItemText(1, rp);
    ui->sc1->setItemText(0, pp);
    ui->sc2->setItemText(1, rp);
    ui->sc2->setItemText(0, pp);
    ui->sc3->setItemText(1, rp);
    ui->sc3->setItemText(0, pp);

}
