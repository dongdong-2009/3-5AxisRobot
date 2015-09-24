#include "ichcstackedsettingsframe.h"
#include "ui_ichcstackedsettingsframe.h"

#include "icmold.h"
#include "icvirtualhost.h"
#include "config.h"
#include <QTimer>
#include "icconfigstring.h"

#include <QDebug>

ICHCStackedSettingsFrame::ICHCStackedSettingsFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ICHCStackedSettingsFrame)
{
    ui->setupUi(this);

    InitInterface();
//    ui->currentPageLabel->setText(ui->page0ToolButton->text());
    currentPage_ = 0;
    RefreshStackParams_(currentPage_);
    connect(ICMold::CurrentMold(),
            SIGNAL(MoldNumberParamChanged()),
            this,
            SLOT(OnMoldNumberParamChanged()));
    ui->xUnit->hide();
    ui->xUnit_2->hide();
    ui->yUnit->hide();
    ui->yUnit_2->hide();
    ui->zUnit->hide();
    ui->zUnit_2->hide();

    editorToConfigIDs_.insert(ui->buttonGroup, ICConfigString::kCS_STACK_Group1_Seq);
    editorToConfigIDs_.insert(ui->buttonGroup_3, ICConfigString::kCS_STACK_Group1_X_Dir);
    editorToConfigIDs_.insert(ui->buttonGroup_4, ICConfigString::kCS_STACK_Group1_Y_Dir);
    editorToConfigIDs_.insert(ui->buttonGroup_5, ICConfigString::kCS_STACK_Group1_Z_Dir);
    editorToConfigIDs_.insert(ui->xRPLatticeLineEdit, ICConfigString::kCS_STACK_Group1_X_Number);
    editorToConfigIDs_.insert(ui->yRPLatticeLineEdit, ICConfigString::kCS_STACK_Group1_Y_Number);
    editorToConfigIDs_.insert(ui->zRPLatticeLineEdit, ICConfigString::kCS_STACK_Group1_Z_Number);
    editorToConfigIDs_.insert(ui->xRPStepLineEdit, ICConfigString::kCS_STACK_Group1_X_Space);
    editorToConfigIDs_.insert(ui->yRPStepLineEdit, ICConfigString::kCS_STACK_Group1_Y_Space);
    editorToConfigIDs_.insert(ui->zRPStepLineEdit, ICConfigString::kCS_STACK_Group1_Z_Space);
    editorToConfigIDs_.insert(ui->subArm, ICConfigString::kCS_STACK_Group1_Is_SArm);
    editorToConfigIDs_.insert(ui->countWayBox, ICConfigString::kCS_STACK_Group1_Count_Way);
    ICLogInit

            this->hide();


}

ICHCStackedSettingsFrame::~ICHCStackedSettingsFrame()
{
    delete ui;
}

void ICHCStackedSettingsFrame::on_page3ToolButton_clicked()
{
    QList<int> status = GetCurrentStatus_();
    SetStackStatus_(status);
//    ui->currentPageLabel->setText(ui->page3ToolButton->text());
    currentPage_ = 3;
    RefreshStackParams_(currentPage_);
}

void ICHCStackedSettingsFrame::on_page2ToolButton_clicked()
{

    QList<int> status = GetCurrentStatus_();
    SetStackStatus_(status);
//    ui->currentPageLabel->setText(ui->page2ToolButton->text());
    currentPage_ = 2;
    RefreshStackParams_(currentPage_);
}

void ICHCStackedSettingsFrame::on_page1ToolButton_clicked()
{

    QList<int> status = GetCurrentStatus_();
    SetStackStatus_(status);

//    ui->currentPageLabel->setText(ui->page1ToolButton->text());
    currentPage_ = 1;
    RefreshStackParams_(currentPage_);
}

void ICHCStackedSettingsFrame::on_page0ToolButton_clicked()
{
    QList<int> status = GetCurrentStatus_();
    SetStackStatus_(status);
//    ui->currentPageLabel->setText(ui->page0ToolButton->text());
    currentPage_ = 0;
    RefreshStackParams_(currentPage_);
}

void ICHCStackedSettingsFrame::InitInterface()
{
    QIntValidator * validator = new QIntValidator(0, 32760, this);
    QIntValidator * validator_ = new QIntValidator(0, 65530, this);

    ui->xRPLatticeLineEdit->SetDecimalPlaces(0);
    ui->xRPLatticeLineEdit->setValidator(validator);
    ui->xRPStepLineEdit->SetDecimalPlaces(STACK_DECIMAL);
//    ui->xRPStepLineEdit->setValidator(validator_);

    ui->xRPLatticeLineEdit->SetDecimalPlaces(0);
    ui->yRPLatticeLineEdit->setValidator(validator);
    ui->yRPStepLineEdit->SetDecimalPlaces(STACK_DECIMAL);
//    ui->yRPStepLineEdit->setValidator(validator_);

    ui->xRPLatticeLineEdit->SetDecimalPlaces(0);
    ui->zRPLatticeLineEdit->setValidator(validator);
    ui->zRPStepLineEdit->SetDecimalPlaces(STACK_DECIMAL);
//    ui->zRPStepLineEdit->setValidator(validator_);

//    ui->stackCount->setValidator(validator);

}

void ICHCStackedSettingsFrame::RefreshStackParams_(int group)
{
    QMap<QObject*, int>::iterator p = editorToConfigIDs_.begin();
    while(p != editorToConfigIDs_.end())
    {
        p.key()->blockSignals(true);
        ++p;
    }
    QList<int> stackParams = ICMold::CurrentMold()->StackParams(group);
    int seq = stackParams.at(ICMold::Seq);
    int seqH;
    int seqL;
    seqH = seq;
    seqL = seq & 0x000F;
    if(seqL == 0)
    {
        ui->xzyCheckBox->setChecked(true);
    }
    else if(seqL == 1)
    {
        ui->zxyCheckBox->setChecked(true);
    }
    else if(seqL == 2)
    {
        ui->yxzCheckBox->setChecked(true);
    }
    else if(seqL == 3)
    {
        ui->yzxCheckBox->setChecked(true);
    }
    ui->xRPLatticeLineEdit->SetThisIntToThisText(stackParams.at(ICMold::X_Array) & 0x7FFF);
    seqH & 32 ? ui->xRPCheckBox->click() : ui->xPPCheckBox->click();
    stackParams.at(ICMold::X_Array) >> 15 ? ui->xUnit->setChecked(true) : ui->xUnit_2->setChecked(true);
    ui->xUnit->isChecked() ? ui->xRPStepLineEdit->SetDecimalPlaces(1) : ui->xRPStepLineEdit->SetDecimalPlaces(2);
    ui->xRPStepLineEdit->SetThisIntToThisText(stackParams.at(ICMold::X_Gap));
    ui->yRPLatticeLineEdit->SetThisIntToThisText(stackParams.at(ICMold::Y_Array) & 0x7FFF);
    seqH & 64 ? ui->yRPCheckBox->click() : ui->yPPCheckBox->click();
    ui->yPPCheckBox->setChecked(!ui->yRPCheckBox->isChecked());
    stackParams.at(ICMold::Y_Array) >> 15 ? ui->yUnit->setChecked(true) : ui->yUnit_2->setChecked(true);
    ui->yUnit->isChecked() ? ui->yRPStepLineEdit->SetDecimalPlaces(1) : ui->yRPStepLineEdit->SetDecimalPlaces(2);
    ui->yRPStepLineEdit->SetThisIntToThisText(stackParams.at(ICMold::Y_Gap));
    ui->zRPLatticeLineEdit->SetThisIntToThisText(stackParams.at(ICMold::Z_Array) & 0x7FFF);
    seqH & 128 ? ui->zRPCheckBox->click() : ui->zPPCheckBox->click();
    ui->zPPCheckBox->setChecked(!ui->zRPCheckBox->isChecked());
    stackParams.at(ICMold::Z_Array) >> 15 ? ui->zUnit->setChecked(true) : ui->zUnit_2->setChecked(true);
    ui->zUnit->isChecked() ? ui->zRPStepLineEdit->SetDecimalPlaces(1) : ui->zRPStepLineEdit->SetDecimalPlaces(2);
    ui->zRPStepLineEdit->SetThisIntToThisText(stackParams.at(ICMold::Z_Gap));
    ui->countWayBox->setCurrentIndex(ICMold::CurrentMold()->MoldParam(static_cast<ICMold::ICMoldParam>(currentPage_)));
    ui->subArm->setChecked(stackParams.at(ICMold::Seq) >> 15);

    p = editorToConfigIDs_.begin();
    while(p != editorToConfigIDs_.end())
    {
        p.key()->blockSignals(false);
        ++p;
    }
}

QList<int> ICHCStackedSettingsFrame::GetCurrentStatus_() const
{
    int seqL = 0;
    int seqH = 0;
    QList<int> status;
    QAbstractButton *checkedButton = ui->buttonGroup->checkedButton();
    if(checkedButton == ui->xzyCheckBox)
    {
        seqL = 0;
    }
    else if(checkedButton == ui->zxyCheckBox)
    {
        seqL = 1;
    }
    else if(checkedButton == ui->yxzCheckBox)
    {
        seqL = 2;
    }
    else
    {
        seqL = 3;
    }
    if(ui->xRPCheckBox->isChecked())
    {
        seqH |= 32;
    }
    if(ui->yRPCheckBox->isChecked())
    {
        seqH |= 64;
    }
    if(ui->zRPCheckBox->isChecked())
    {
        seqH |= 128;
    }
    if(ui->subArm->isChecked())
    {
        seqH |= (1 << 15);
    }
    else
    {
        seqH &= 0x7FFF;
    }

    status.append(seqH + seqL);
    status.append(ui->xRPLatticeLineEdit->TransThisTextToThisInt() | (ui->xUnit->isChecked() << 15));
    status.append(ui->yRPLatticeLineEdit->TransThisTextToThisInt() | (ui->yUnit->isChecked() << 15));
    status.append(ui->zRPLatticeLineEdit->TransThisTextToThisInt() | (ui->zUnit->isChecked() << 15));
    status.append(ui->xRPStepLineEdit->TransThisTextToThisInt() );
    status.append(ui->yRPStepLineEdit->TransThisTextToThisInt() );
    status.append(ui->zRPStepLineEdit->TransThisTextToThisInt());
    status.append(ui->countWayBox->currentIndex());
    qDebug()<<status;
//    status.append(ui->xRPCheckBox->isChecked() ? 1 : 0);
//    status.append(ui->yRPCheckBox->isChecked() ? 1 : 0);
//    status.append(ui->zRPCheckBox->isChecked() ? 1 : 0);
    return status;
}

void ICHCStackedSettingsFrame::SetStackStatus_(const QList<int> &status)
{
    ICMold *currentMold = ICMold::CurrentMold();
    const int count = status.size() - 1;
    for(int i = 0; i != count; ++i)
    {
        currentMold->SetStackParam(currentPage_, static_cast<ICMold::ICStatckParam>(i), status.at(i));
    }
    currentMold->SetMoldParam(static_cast<ICMold::ICMoldParam>(currentPage_), status.at(count));
}

void ICHCStackedSettingsFrame::hideEvent(QHideEvent *e)
{
    if(this->isVisible()) return;
    QFrame::hideEvent(e);
    qDebug("stack hide");
    QList<int> status = GetCurrentStatus_();
    SetStackStatus_(status);
    ICMold::CurrentMold()->SaveMoldParamsFile();
//    qApp->processEvents(QEventLoop::WaitForMoreEvents);
//    QTimer::singleShot(5, this, SLOT(TimeOutToReconfig()));
//    ICVirtualHost::GlobalVirtualHost()->ReConfigure();
}

void ICHCStackedSettingsFrame::changeEvent(QEvent *e)
{
    QFrame::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
    {
        int index= ui->countWayBox->currentIndex();
        ui->countWayBox->blockSignals(true);
        ui->retranslateUi(this);
        ui->countWayBox->setCurrentIndex(index);
        ui->countWayBox->blockSignals(false);
    }
        break;
    default:
        break;
    }
}

void ICHCStackedSettingsFrame::OnMoldNumberParamChanged()
{
    RefreshStackParams_(currentPage_);
}

void ICHCStackedSettingsFrame::on_xUnit_toggled(bool checked)
{
//    if(checked)
//        ui->xRPStepLineEdit->SetDecimalPlaces(1);
//    else
//        ui->xRPStepLineEdit->SetDecimalPlaces(2);
}

void ICHCStackedSettingsFrame::on_yUnit_toggled(bool checked)
{
//    if(checked)
//        ui->yRPStepLineEdit->SetDecimalPlaces(1);
//    else
//        ui->yRPStepLineEdit->SetDecimalPlaces(2);
}

void ICHCStackedSettingsFrame::on_zUnit_toggled(bool checked)
{
//    if(checked)
//        ui->zRPStepLineEdit->SetDecimalPlaces(1);
//    else
//        ui->zRPStepLineEdit->SetDecimalPlaces(2);
}

void ICHCStackedSettingsFrame::on_xRPStepLineEdit_textChanged(const QString &arg1)
{
    double v = arg1.toDouble();
    ui->xRPStepLineEdit->blockSignals(true);

    if(v > 600)
    {
        ui->xUnit->setChecked(true);
        ui->xRPStepLineEdit->setText(QString::number(v, 'f', 1));
//        ui->xRPStepLineEdit->setText(QString("%1").arg(v, 0 , 'f', 1, "0"));
        ui->xRPStepLineEdit->SetDecimalPlaces(1);
    }
    else
    {
        ui->xUnit_2->setChecked(true);
        ui->xRPStepLineEdit->setText(QString::number(v, 'f', 2));
//        ui->xRPStepLineEdit->setText(QString("%1").arg(v, 0 , 'f', 2), "0");

        ui->xRPStepLineEdit->SetDecimalPlaces(2);

    }
    ui->xRPStepLineEdit->blockSignals(false);

}

void ICHCStackedSettingsFrame::on_yRPStepLineEdit_textChanged(const QString &arg1)
{
    double v = arg1.toDouble();
    ui->yRPStepLineEdit->blockSignals(true);

    if(v > 600)
    {
        ui->yUnit->setChecked(true);
        ui->yRPStepLineEdit->setText(QString::number(v, 'f', 1));
        ui->yRPStepLineEdit->SetDecimalPlaces(1);
    }
    else
    {
        ui->yUnit_2->setChecked(true);
        ui->yRPStepLineEdit->setText(QString::number(v, 'f', 2));
        ui->yRPStepLineEdit->SetDecimalPlaces(2);
    }
    ui->yRPStepLineEdit->blockSignals(false);

}

void ICHCStackedSettingsFrame::on_zRPStepLineEdit_textChanged(const QString &arg1)
{
    double v = arg1.toDouble();
    ui->zRPStepLineEdit->blockSignals(true);
    if(v > 600)
    {
        ui->zUnit->setChecked(true);
        ui->zRPStepLineEdit->setText(QString::number(v, 'f', 1));
        ui->zRPStepLineEdit->SetDecimalPlaces(1);
    }
    else
    {
        ui->zUnit_2->setChecked(true);
        ui->zRPStepLineEdit->setText(QString::number(v, 'f', 2));
        ui->zRPStepLineEdit->SetDecimalPlaces(2);
    }
    ui->zRPStepLineEdit->blockSignals(false);

}

void ICHCStackedSettingsFrame::OnConfigChanged(QObject *w, const QString& newV, const QString& oldV)
{
    ICAlarmFrame::Instance()->OnActionTriggered(editorToConfigIDs_.value(w, ICConfigString::kCS_Err) + currentPage_,
                                                newV,
                                                oldV);
}

void ICHCStackedSettingsFrame::OnConfigChanged(const QString &text)
{
    ICLineEditWithVirtualNumericKeypad* edit = qobject_cast<ICLineEditWithVirtualNumericKeypad*>(sender());
    OnConfigChanged(edit, text, edit->LastValue());
}

void ICHCStackedSettingsFrame::OnConfigChanged(int v, int ov)
{
    ICButtonGroup* icbg = qobject_cast<ICButtonGroup*>(sender());
    QButtonGroup* bg = icbg->ButtongGroup();
    OnConfigChanged(bg, bg->button(v)->text(), bg->button(ov)->text());
}

void ICHCStackedSettingsFrame::OnConfigChanged(int v)
{
    ICComboBox* edit = qobject_cast<ICComboBox*>(sender());
    OnConfigChanged(edit, edit->currentText(), edit->itemText(edit->LastValue()));
}

void ICHCStackedSettingsFrame::OnConfigChanged(bool b)
{
    QCheckBox* edit = qobject_cast<QCheckBox*>(sender());
    OnConfigChanged(edit, QString::number(b), QString::number(!b));
}
