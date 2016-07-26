#include "icmachineconfigpage.h"
#include "ui_icmachineconfigpage.h"
#include "iclineeditwrapper.h"
#include "icvirtualhost.h"
#include "icparameterssave.h"
#include "icconfigstring.h"

ICMachineConfigPage::ICMachineConfigPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ICMachineConfigPage)
{
    ui->setupUi(this);
    axisWidgets_.append(QList<QWidget*>()<<ui->x1ALabel<<ui->x1MLabel<<ui->xADEdit<<ui->x1SLabel<<ui->xMaxSpeedEdit<<ui->x1SLabel_2<<ui->x1ALabel_2<<ui->x1SLabel_10<<ui->xADEdit_2);
    axisWidgets_.append(QList<QWidget*>()<<ui->y1MLabel<<ui->y1ALabel<<ui->y1SLabel<<ui->yADEdit<<ui->yMaxSpeedEdit<<ui->x1SLabel_3<<ui->y1ALabel_2<<ui->y1SLabel_2<<ui->yADEdit_2);
    axisWidgets_.append(QList<QWidget*>()<<ui->zALabel<<ui->zADEdit<<ui->zMaxSpeedEdit<<ui->zMLabel<<ui->zSLabel<<ui->x1SLabel_4<<ui->zALabel_2<<ui->zSLabel_2<<ui->zADEdit_2);
    axisWidgets_.append(QList<QWidget*>()<<ui->x2ADEdit<<ui->x2ALabel<<ui->x2MaxSpeedEdit<<ui->x2MLabel<<ui->x2SLabel<<ui->x1SLabel_5<<ui->x2ALabel_2<<ui->x2SLabel_2<<ui->x2ADEdit_2);
    axisWidgets_.append(QList<QWidget*>()<<ui->y2ADEdit<<ui->y2ALabel<<ui->y2MaxSpeedEdit<<ui->y2MLabel<<ui->y2SLabel<<ui->x1SLabel_6<<ui->y2ALabel_2<<ui->y2SLabel_2<<ui->y2ADEdit_2);
    axisWidgets_.append(QList<QWidget*>()<<ui->aADEdit<<ui->aALabel<<ui->aMaxSpeedEdit<<ui->aMLabel<<ui->aSLabel<<ui->x1SLabel_7<<ui->aADEdit_2<<ui->aSLabel_2<<ui->aALabel_2);
    axisWidgets_.append(QList<QWidget*>()<<ui->bADEdit<<ui->bALabel<<ui->bMaxSpeedEdit<<ui->bMLabel<<ui->bSLabel<<ui->x1SLabel_8<<ui->bALabel_2<<ui->bSLabel_2<<ui->bADEdit_2);
    axisWidgets_.append(QList<QWidget*>()<<ui->cADEdit<<ui->cALabel<<ui->cMaxSpeedEdit<<ui->cMLabel<<ui->cSLabel<<ui->x1SLabel_9<<ui->cALabel_2<<ui->cSLabel_2<<ui->cADEdit_2);
    QIntValidator * validator = new QIntValidator(0, 255, this);
    ui->xADEdit->SetDecimalPlaces(2);
    ui->xADEdit->setValidator(validator);
    ui->yADEdit->SetDecimalPlaces(2);
    ui->yADEdit->setValidator(validator);
    ui->zADEdit->SetDecimalPlaces(2);
    ui->zADEdit->setValidator(validator);
    ui->x2ADEdit->SetDecimalPlaces(2);
    ui->x2ADEdit->setValidator(validator);
    ui->y2ADEdit->SetDecimalPlaces(2);
    ui->y2ADEdit->setValidator(validator);
    ui->aADEdit->SetDecimalPlaces(2);
    ui->aADEdit->setValidator(validator);
    ui->bADEdit->SetDecimalPlaces(2);
    ui->bADEdit->setValidator(validator);
    ui->cADEdit->SetDecimalPlaces(2);
    ui->cADEdit->setValidator(validator);

    ui->xADEdit_2->SetDecimalPlaces(2);
    ui->xADEdit_2->setValidator(validator);
    ui->yADEdit_2->SetDecimalPlaces(2);
    ui->yADEdit_2->setValidator(validator);
    ui->zADEdit_2->SetDecimalPlaces(2);
    ui->zADEdit_2->setValidator(validator);
    ui->x2ADEdit_2->SetDecimalPlaces(2);
    ui->x2ADEdit_2->setValidator(validator);
    ui->y2ADEdit_2->SetDecimalPlaces(2);
    ui->y2ADEdit_2->setValidator(validator);
    ui->aADEdit_2->SetDecimalPlaces(2);
    ui->aADEdit_2->setValidator(validator);
    ui->bADEdit_2->SetDecimalPlaces(2);
    ui->bADEdit_2->setValidator(validator);
    ui->cADEdit_2->SetDecimalPlaces(2);
    ui->cADEdit_2->setValidator(validator);
    ui->toleranceLineEdit->SetDecimalPlaces(2);
    ui->toleranceLineEdit->setValidator(new QIntValidator(0, 65530, this));
    ui->pullPushDistance->SetDecimalPlaces(1);
    ui->pullPushDistance->setValidator(new QIntValidator(100, 1000, this));
    //    ui->xEarlyEndEdit->SetDecimalPlaces(1);
    //    ui->xEarlyEndEdit->setValidator(validator);
    //    ui->yEarlyEndEdit->SetDecimalPlaces(1);
    //    ui->yEarlyEndEdit->setValidator(validator);
    //    ui->zEarlyEndEdit->SetDecimalPlaces(1);
    //    ui->zEarlyEndEdit->setValidator(validator);

    validator = new QIntValidator(0, 200, this);
    ui->xMaxSpeedEdit->setValidator(validator);
    ui->yMaxSpeedEdit->setValidator(validator);
    ui->zMaxSpeedEdit->setValidator(validator);
    ui->x2MaxSpeedEdit->setValidator(validator);
    ui->y2MaxSpeedEdit->setValidator(validator);
    ui->aMaxSpeedEdit->setValidator(validator);
    ui->bMaxSpeedEdit->setValidator(validator);
    ui->cMaxSpeedEdit->setValidator(validator);

    ICLineEditWrapper* wrapper ;
    //    wrapper = new ICLineEditWrapper(ui->xADEdit,
    //                                                       ICVirtualHost::SM_ACCTIMEX,
    //                                                       ICLineEditWrapper::System,
    //                                                       ICLineEditWrapper::TwoFraction);
    //    wrappers_.append(wrapper);
    //    wrapper = new ICLineEditWrapper(ui->yADEdit,
    //                                    ICVirtualHost::SM_ACCTIMEY,
    //                                    ICLineEditWrapper::System,
    //                                    ICLineEditWrapper::TwoFraction);
    //    wrappers_.append(wrapper);
    //    wrapper = new ICLineEditWrapper(ui->yADEdit,
    //                                    ICVirtualHost::SM_ACCTIMEY,
    //                                    ICLineEditWrapper::System,
    //                                    ICLineEditWrapper::TwoFraction);
    //    wrappers_.append(wrapper);
    //    wrapper = new ICLineEditWrapper(ui->zADEdit,
    //                                    ICVirtualHost::SM_ACCTIMEZ,
    //                                    ICLineEditWrapper::System,
    //                                    ICLineEditWrapper::TwoFraction);
    //    wrappers_.append(wrapper);
    wrapper = new ICLineEditWrapper(ui->xMaxSpeedEdit,
                                    ICVirtualHost::SM_LMTVX,
                                    ICLineEditWrapper::System,
                                    ICLineEditWrapper::Integer);
    wrappers_.append(wrapper);
    wrapper = new ICLineEditWrapper(ui->yMaxSpeedEdit,
                                    ICVirtualHost::SM_LMTVY,
                                    ICLineEditWrapper::System,
                                    ICLineEditWrapper::Integer);
    wrappers_.append(wrapper);
    wrapper = new ICLineEditWrapper(ui->zMaxSpeedEdit,
                                    ICVirtualHost::SM_LMTVZ,
                                    ICLineEditWrapper::System,
                                    ICLineEditWrapper::Integer);
    wrappers_.append(wrapper);

    wrapper = new ICLineEditWrapper(ui->toleranceLineEdit,
                                    ICVirtualHost::SM_ALLOWANCE,
                                    ICLineEditWrapper::System,
                                    ICLineEditWrapper::TwoFraction);
    wrappers_.append(wrapper);

    //    wrapper = new ICLineEditWrapper(ui->x2ADEdit,
    //                                    ICVirtualHost::SM_ACCTIMEP,
    //                                    ICLineEditWrapper::System,
    //                                    ICLineEditWrapper::TwoFraction);
    //    wrappers_.append(wrapper);

    //    wrapper = new ICLineEditWrapper(ui->y2ADEdit,
    //                                    ICVirtualHost::SM_ACCTIMEQ,
    //                                    ICLineEditWrapper::System,
    //                                    ICLineEditWrapper::TwoFraction);
    //    wrappers_.append(wrapper);

    //    wrapper = new ICLineEditWrapper(ui->aADEdit,
    //                                    ICVirtualHost::SM_ACCTIMEA,
    //                                    ICLineEditWrapper::System,
    //                                    ICLineEditWrapper::TwoFraction);
    //    wrappers_.append(wrapper);

    //    wrapper = new ICLineEditWrapper(ui->bADEdit,
    //                                    ICVirtualHost::SM_ACCTIMEB,
    //                                    ICLineEditWrapper::System,
    //                                    ICLineEditWrapper::TwoFraction);
    //    wrappers_.append(wrapper);

    //    wrapper = new ICLineEditWrapper(ui->cADEdit,
    //                                    ICVirtualHost::SM_ACCTIMEC,
    //                                    ICLineEditWrapper::System,
    //                                    ICLineEditWrapper::TwoFraction);

    //    wrappers_.append(wrapper);

    wrapper = new ICLineEditWrapper(ui->x2MaxSpeedEdit,
                                    ICVirtualHost::SM_LMTVP,
                                    ICLineEditWrapper::System,
                                    ICLineEditWrapper::Integer);
    wrappers_.append(wrapper);

    wrapper = new ICLineEditWrapper(ui->y2MaxSpeedEdit,
                                    ICVirtualHost::SM_LMTVQ,
                                    ICLineEditWrapper::System,
                                    ICLineEditWrapper::Integer);
    wrappers_.append(wrapper);

    wrapper = new ICLineEditWrapper(ui->aMaxSpeedEdit,
                                    ICVirtualHost::SM_LMTVA,
                                    ICLineEditWrapper::System,
                                    ICLineEditWrapper::Integer);
    wrappers_.append(wrapper);

    wrapper = new ICLineEditWrapper(ui->bMaxSpeedEdit,
                                    ICVirtualHost::SM_LMTVB,
                                    ICLineEditWrapper::System,
                                    ICLineEditWrapper::Integer);
    wrappers_.append(wrapper);

    wrapper = new ICLineEditWrapper(ui->cMaxSpeedEdit,
                                    ICVirtualHost::SM_LMTVC,
                                    ICLineEditWrapper::System,
                                    ICLineEditWrapper::Integer);
    wrappers_.append(wrapper);

    wrapper = new ICLineEditWrapper(ui->pullPushDistance,
                                    ICVirtualHost::SM_PullPushDistance,
                                    ICLineEditWrapper::System,
                                    ICLineEditWrapper::OneFraction);
    wrappers_.append(wrapper);

    int xValue = ICVirtualHost::GlobalVirtualHost()->SystemParameter(ICVirtualHost::SYS_AccTimeX).toInt();
    int yValue = ICVirtualHost::GlobalVirtualHost()->SystemParameter(ICVirtualHost::SYS_AccTimeY).toInt();
    int zValue = ICVirtualHost::GlobalVirtualHost()->SystemParameter(ICVirtualHost::SYS_AccTimeZ).toInt();
    int x2Value = ICVirtualHost::GlobalVirtualHost()->SystemParameter(ICVirtualHost::SYS_AccTimeP).toInt();
    int y2Value = ICVirtualHost::GlobalVirtualHost()->SystemParameter(ICVirtualHost::SYS_AccTimeQ).toInt();
    int aValue = ICVirtualHost::GlobalVirtualHost()->SystemParameter(ICVirtualHost::SYS_AccTimeA).toInt();
    int bValue = ICVirtualHost::GlobalVirtualHost()->SystemParameter(ICVirtualHost::SYS_AccTimeB).toInt();
    int cValue = ICVirtualHost::GlobalVirtualHost()->SystemParameter(ICVirtualHost::SYS_AccTimeC).toInt();

    ui->xADEdit->blockSignals(true);
    ui->xADEdit_2->blockSignals(true);
    ui->yADEdit->blockSignals(true);
    ui->yADEdit_2->blockSignals(true);
    ui->zADEdit->blockSignals(true);
    ui->zADEdit_2->blockSignals(true);
    ui->x2ADEdit->blockSignals(true);
    ui->x2ADEdit_2->blockSignals(true);
    ui->y2ADEdit->blockSignals(true);
    ui->y2ADEdit_2->blockSignals(true);
    ui->aADEdit->blockSignals(true);
    ui->aADEdit_2->blockSignals(true);
    ui->bADEdit->blockSignals(true);
    ui->bADEdit_2->blockSignals(true);
    ui->cADEdit->blockSignals(true);
    ui->cADEdit_2->blockSignals(true);
    ui->xADEdit->SetThisIntToThisText(xValue & 0xFF);
    ui->xADEdit_2->SetThisIntToThisText(xValue >> 8);
    ui->yADEdit->SetThisIntToThisText(yValue & 0xFF);
    ui->yADEdit_2->SetThisIntToThisText(yValue >> 8);
    ui->zADEdit->SetThisIntToThisText(zValue & 0xFF);
    ui->zADEdit_2->SetThisIntToThisText(zValue >> 8);
    ui->x2ADEdit->SetThisIntToThisText(x2Value & 0xFF);
    ui->x2ADEdit_2->SetThisIntToThisText(x2Value >> 8);
    ui->y2ADEdit->SetThisIntToThisText(y2Value & 0xFF);
    ui->y2ADEdit_2->SetThisIntToThisText(y2Value >> 8);
    ui->aADEdit->SetThisIntToThisText(aValue & 0xFF);
    ui->aADEdit_2->SetThisIntToThisText(aValue >> 8);
    ui->bADEdit->SetThisIntToThisText(bValue & 0xFF);
    ui->bADEdit_2->SetThisIntToThisText(bValue >> 8);
    ui->cADEdit->SetThisIntToThisText(cValue & 0xFF);
    ui->cADEdit_2->SetThisIntToThisText(cValue >> 8);
    ui->xADEdit->blockSignals(false);
    ui->xADEdit_2->blockSignals(false);
    ui->yADEdit->blockSignals(false);
    ui->yADEdit_2->blockSignals(false);
    ui->zADEdit->blockSignals(false);
    ui->zADEdit_2->blockSignals(false);
    ui->x2ADEdit->blockSignals(false);
    ui->x2ADEdit_2->blockSignals(false);
    ui->y2ADEdit->blockSignals(false);
    ui->y2ADEdit_2->blockSignals(false);
    ui->aADEdit->blockSignals(false);
    ui->aADEdit_2->blockSignals(false);
    ui->bADEdit->blockSignals(false);
    ui->bADEdit_2->blockSignals(false);
    ui->cADEdit->blockSignals(false);
    ui->cADEdit_2->blockSignals(false);


    editorToConfigIDs_.insert(ui->toleranceLineEdit, ICConfigString::kCS_RUN_Tolerance);
    editorToConfigIDs_.insert(ui->pullPushDistance, ICConfigString::kCS_RUN_Distance_X1_X2);
    editorToConfigIDs_.insert(ui->xADEdit, ICConfigString::kCS_RUN_Acc_Time_X1);
    editorToConfigIDs_.insert(ui->yADEdit, ICConfigString::kCS_RUN_Acc_Time_Y1);
    editorToConfigIDs_.insert(ui->zADEdit, ICConfigString::kCS_RUN_Acc_Time_Z);
    editorToConfigIDs_.insert(ui->x2ADEdit, ICConfigString::kCS_RUN_Acc_Time_X2);
    editorToConfigIDs_.insert(ui->y2ADEdit, ICConfigString::kCS_RUN_Acc_Time_Y2);
    editorToConfigIDs_.insert(ui->aADEdit, ICConfigString::kCS_RUN_Acc_Time_A);
    editorToConfigIDs_.insert(ui->bADEdit, ICConfigString::kCS_RUN_Acc_Time_B);
    editorToConfigIDs_.insert(ui->cADEdit, ICConfigString::kCS_RUN_Acc_Time_C);
    editorToConfigIDs_.insert(ui->xMaxSpeedEdit, ICConfigString::kCS_RUN_Speed_Limit_X1);
    editorToConfigIDs_.insert(ui->yMaxSpeedEdit, ICConfigString::kCS_RUN_Speed_Limit_Y1);
    editorToConfigIDs_.insert(ui->zMaxSpeedEdit, ICConfigString::kCS_RUN_Speed_Limit_Z);
    editorToConfigIDs_.insert(ui->x2MaxSpeedEdit, ICConfigString::kCS_RUN_Speed_Limit_X2);
    editorToConfigIDs_.insert(ui->y2MaxSpeedEdit, ICConfigString::kCS_RUN_Speed_Limit_Y2);
    editorToConfigIDs_.insert(ui->aMaxSpeedEdit, ICConfigString::kCS_RUN_Speed_Limit_A);
    editorToConfigIDs_.insert(ui->bMaxSpeedEdit, ICConfigString::kCS_RUN_Speed_Limit_B);
    editorToConfigIDs_.insert(ui->cMaxSpeedEdit, ICConfigString::kCS_RUN_Speed_Limit_C);

    ICLogInit;
    //    ui->servoFlex->blockSignals(true);
    //    ui->servoFlex->setCurrentIndex(ICVirtualHost::GlobalVirtualHost()->SystemParameter(ICVirtualHost::SYS_Language).toInt());
    //    ui->servoFlex->blockSignals(false);
}

ICMachineConfigPage::~ICMachineConfigPage()
{
    qDeleteAll(wrappers_);
    delete ui;
}

void ICMachineConfigPage::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
    {
        //        int ci = ui->servoFlex->currentIndex();
        //        ui->servoFlex->blockSignals(true);
        ui->retranslateUi(this);
        //        ui->servoFlex->setCurrentIndex(ci);
        //        ui->servoFlex->blockSignals(false);
    }
        break;
    default:
        break;
    }
}

void ICMachineConfigPage::hideEvent(QHideEvent *e)
{
    qDebug("machine config hide");
    //    ICMold::CurrentMold()->SaveMoldParamsFile();
    if(ICVirtualHost::GlobalVirtualHost()->IsParamChanged())
    {
        ICVirtualHost::GlobalVirtualHost()->SaveSystemConfig();
        ICVirtualHost::GlobalVirtualHost()->ReConfigure();
    }
    QWidget::hideEvent(e);
}

void ICMachineConfigPage::showEvent(QShowEvent *e)
{
    //    bool isExtent = ICParametersSave::Instance()->IsExtentFunctionUsed();
    UpdateAxisDefine_();
    QWidget::showEvent(e);
}

void ICMachineConfigPage::UpdateAxisDefine_()
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    int currentAxis = host->SystemParameter(ICVirtualHost::SYS_Config_Arm).toInt();
    if(axisDefine_ != currentAxis)
    {
        axisDefine_ = currentAxis;
        for(int i = 0 ; i != axisWidgets_.size(); ++i)
        {
            HideWidgets_(axisWidgets_[i]);
        }


        if(host->AxisDefine(ICVirtualHost::ICAxis_AxisX1) == ICVirtualHost::ICAxisDefine_None)
        {
            HideWidgets_(axisWidgets_[0]);
        }
        else
        {
            ShowWidgets_(axisWidgets_[0]);
        }

        if(host->AxisDefine(ICVirtualHost::ICAxis_AxisY1) == ICVirtualHost::ICAxisDefine_None)
        {
            HideWidgets_(axisWidgets_[1]);
        }
        else
        {
            ShowWidgets_(axisWidgets_[1]);
        }

        if(host->AxisDefine(ICVirtualHost::ICAxis_AxisZ) == ICVirtualHost::ICAxisDefine_None)
        {
            HideWidgets_(axisWidgets_[2]);
        }
        else
        {
            ShowWidgets_(axisWidgets_[2]);
        }

        if(host->AxisDefine(ICVirtualHost::ICAxis_AxisX2) == ICVirtualHost::ICAxisDefine_None)
        {
            HideWidgets_(axisWidgets_[3]);
        }
        else
        {
            ShowWidgets_(axisWidgets_[3]);
        }

        if(host->AxisDefine(ICVirtualHost::ICAxis_AxisY2) == ICVirtualHost::ICAxisDefine_None)
        {
            HideWidgets_(axisWidgets_[4]);
        }
        else
        {
            ShowWidgets_(axisWidgets_[4]);
        }

        if(host->AxisDefine(ICVirtualHost::ICAxis_AxisA) == ICVirtualHost::ICAxisDefine_None)
        {
            HideWidgets_(axisWidgets_[5]);
        }
        else
        {
            ShowWidgets_(axisWidgets_[5]);
        }

        if(host->AxisDefine(ICVirtualHost::ICAxis_AxisB) == ICVirtualHost::ICAxisDefine_None)
        {
            HideWidgets_(axisWidgets_[6]);
        }
        else
        {
            ShowWidgets_(axisWidgets_[6]);
        }

        if(host->AxisDefine(ICVirtualHost::ICAxis_AxisC) == ICVirtualHost::ICAxisDefine_None)
        {
            HideWidgets_(axisWidgets_[7]);
        }
        else
        {
            ShowWidgets_(axisWidgets_[7]);
        }
    }
}

void ICMachineConfigPage::ShowWidgets_(QList<QWidget *> &widgets)
{
    for(int i = 0; i != widgets.size(); ++i)
    {
        widgets[i]->show();
    }
}

void ICMachineConfigPage::HideWidgets_(QList<QWidget *> &widgets)
{
    for(int i = 0; i != widgets.size(); ++i)
    {
        widgets[i]->hide();
    }
}

void ICMachineConfigPage::on_xADEdit_textChanged(const QString &arg1)
{
    int v = (ui->xADEdit->TransThisTextToThisInt() ) | (ui->xADEdit_2->TransThisTextToThisInt()<<8);
    ICVirtualHost::GlobalVirtualHost()->SetSystemParameter(ICVirtualHost::SYS_AccTimeX, v);

}

void ICMachineConfigPage::on_yADEdit_textChanged(const QString &arg1)
{
    int v = (ui->yADEdit->TransThisTextToThisInt() ) | (ui->yADEdit_2->TransThisTextToThisInt()<<8);
    ICVirtualHost::GlobalVirtualHost()->SetSystemParameter(ICVirtualHost::SYS_AccTimeY, v);
}

void ICMachineConfigPage::on_zADEdit_textChanged(const QString &arg1)
{
    int v = (ui->zADEdit->TransThisTextToThisInt() ) | (ui->zADEdit_2->TransThisTextToThisInt()<<8);
    ICVirtualHost::GlobalVirtualHost()->SetSystemParameter(ICVirtualHost::SYS_AccTimeZ, v);
}

void ICMachineConfigPage::on_x2ADEdit_textChanged(const QString &arg1)
{
    int v = (ui->x2ADEdit->TransThisTextToThisInt() ) | (ui->x2ADEdit_2->TransThisTextToThisInt()<<8);
    ICVirtualHost::GlobalVirtualHost()->SetSystemParameter(ICVirtualHost::SYS_AccTimeP, v);
}

void ICMachineConfigPage::on_y2ADEdit_textChanged(const QString &arg1)
{
    int v = (ui->y2ADEdit->TransThisTextToThisInt() ) | (ui->y2ADEdit_2->TransThisTextToThisInt()<<8);
    ICVirtualHost::GlobalVirtualHost()->SetSystemParameter(ICVirtualHost::SYS_AccTimeQ, v);
}

void ICMachineConfigPage::on_aADEdit_textChanged(const QString &arg1)
{
    int v = (ui->aADEdit->TransThisTextToThisInt() ) | (ui->aADEdit_2->TransThisTextToThisInt()<<8);
    ICVirtualHost::GlobalVirtualHost()->SetSystemParameter(ICVirtualHost::SYS_AccTimeA, v);
}

void ICMachineConfigPage::on_bADEdit_textChanged(const QString &arg1)
{
    int v = (ui->bADEdit->TransThisTextToThisInt() ) | (ui->bADEdit_2->TransThisTextToThisInt()<<8);
    ICVirtualHost::GlobalVirtualHost()->SetSystemParameter(ICVirtualHost::SYS_AccTimeB, v);
}

void ICMachineConfigPage::on_cADEdit_textChanged(const QString &arg1)
{
    int v = (ui->cADEdit->TransThisTextToThisInt() ) | (ui->cADEdit_2->TransThisTextToThisInt()<<8);
    ICVirtualHost::GlobalVirtualHost()->SetSystemParameter(ICVirtualHost::SYS_AccTimeC, v);
}

//LOW SPEED
void ICMachineConfigPage::on_xADEdit_2_textChanged(const QString &arg1)
{
    int v = (ui->xADEdit->TransThisTextToThisInt() ) | (ui->xADEdit_2->TransThisTextToThisInt()<<8);
    ICVirtualHost::GlobalVirtualHost()->SetSystemParameter(ICVirtualHost::SYS_AccTimeX, v);
}

void ICMachineConfigPage::on_yADEdit_2_textChanged(const QString &arg1)
{
    int v = (ui->yADEdit->TransThisTextToThisInt() ) | (ui->yADEdit_2->TransThisTextToThisInt()<<8);
    ICVirtualHost::GlobalVirtualHost()->SetSystemParameter(ICVirtualHost::SYS_AccTimeY, v);
}

void ICMachineConfigPage::on_zADEdit_2_textChanged(const QString &arg1)
{
    int v = (ui->zADEdit->TransThisTextToThisInt() ) | (ui->zADEdit_2->TransThisTextToThisInt()<<8);
    ICVirtualHost::GlobalVirtualHost()->SetSystemParameter(ICVirtualHost::SYS_AccTimeZ, v);
}

void ICMachineConfigPage::on_x2ADEdit_2_textChanged(const QString &arg1)
{
    int v = (ui->x2ADEdit->TransThisTextToThisInt() ) | (ui->x2ADEdit_2->TransThisTextToThisInt()<<8);
    ICVirtualHost::GlobalVirtualHost()->SetSystemParameter(ICVirtualHost::SYS_AccTimeP, v);
}

void ICMachineConfigPage::on_y2ADEdit_2_textChanged(const QString &arg1)
{
    int v = (ui->y2ADEdit->TransThisTextToThisInt() ) | (ui->y2ADEdit_2->TransThisTextToThisInt()<<8);
    ICVirtualHost::GlobalVirtualHost()->SetSystemParameter(ICVirtualHost::SYS_AccTimeQ, v);
}

void ICMachineConfigPage::on_aADEdit_2_textChanged(const QString &arg1)
{
    int v = (ui->aADEdit->TransThisTextToThisInt() ) | (ui->aADEdit_2->TransThisTextToThisInt()<<8);
    ICVirtualHost::GlobalVirtualHost()->SetSystemParameter(ICVirtualHost::SYS_AccTimeA, v);
}

void ICMachineConfigPage::on_bADEdit_2_textChanged(const QString &arg1)
{
    int v = (ui->bADEdit->TransThisTextToThisInt() ) | (ui->bADEdit_2->TransThisTextToThisInt()<<8);
    ICVirtualHost::GlobalVirtualHost()->SetSystemParameter(ICVirtualHost::SYS_AccTimeB, v);
}

void ICMachineConfigPage::on_cADEdit_2_textChanged(const QString &arg1)
{
    int v = (ui->cADEdit->TransThisTextToThisInt() ) | (ui->cADEdit_2->TransThisTextToThisInt()<<8);
    ICVirtualHost::GlobalVirtualHost()->SetSystemParameter(ICVirtualHost::SYS_AccTimeC, v);
}

ICLogFunctions(ICMachineConfigPage)
