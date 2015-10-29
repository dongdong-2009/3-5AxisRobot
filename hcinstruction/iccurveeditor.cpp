#include "iccurveeditor.h"
#include "ui_iccurveeditor.h"
#include "icvirtualhost.h"
#include "config.h"

ICCurveEditor::ICCurveEditor(QWidget *parent) :
    ICInstructionEditorBase(parent),
    ui(new Ui::ICCurveEditor)
{

    ui->setupUi(this);
    connect(ui->buttonGroup,
            SIGNAL(buttonClicked(QAbstractButton*)),
            SLOT(onTypeChanged(QAbstractButton*)));
    ui->speedEdit->setValidator(new QIntValidator(0, 100, this));
    ui->delayEdit->SetDecimalPlaces(POS_DECIMAL);
    ui->delayEdit->setValidator(new QIntValidator(0, 30000, this));
    ui->x1PosLineEdit->SetDecimalPlaces(POS_DECIMAL);
    ui->y1PosLineEdit->SetDecimalPlaces(POS_DECIMAL);
    ui->zPosLineEdit->SetDecimalPlaces(POS_DECIMAL);
    ui->x1PosLineEdit_2->SetDecimalPlaces(POS_DECIMAL);
    ui->y1PosLineEdit_2->SetDecimalPlaces(POS_DECIMAL);
    ui->zPosLineEdit_2->SetDecimalPlaces(POS_DECIMAL);
    ui->angleLineEdit->SetDecimalPlaces(1);
    ui->angleLineEdit->setValidator(new QIntValidator(0, 3600, this));

    for(int i = 0; i < 3; i++)
    {

        posValidators_[i].setBottom(0);
    }

}

ICCurveEditor::~ICCurveEditor()
{
    delete ui;
}

void ICCurveEditor::changeEvent(QEvent *e)
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

void ICCurveEditor::showEvent(QShowEvent *e)
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    posMaxs_[0] = host->SystemParameter(ICVirtualHost::SYS_X_Maxium).toInt();
    posMaxs_[1] = host->SystemParameter(ICVirtualHost::SYS_Y_Maxium).toInt();
    posMaxs_[2] = host->SystemParameter(ICVirtualHost::SYS_Z_Maxium).toInt();
    for(int i = 0; i < 3; i++)
    {
        posValidators_[i].setTop(posMaxs_[i]);
    }
    ICInstructionEditorBase::showEvent(e);
}

void ICCurveEditor::hideEvent(QHideEvent *e)
{
    ICInstructionEditorBase::hideEvent(e);
}

QList<ICMoldItem> ICCurveEditor::CreateCommandImpl() const
{
    QList<ICMoldItem> ret;
    ICMoldItem item;
    int type = ui->curveButton->isChecked() ? 1 : 0;
    int speed = ui->speedEdit->TransThisTextToThisInt();
    int delay = ui->delayEdit->TransThisTextToThisInt();
    item.Set3DAction(ICMold::GX, type, ui->x1PosLineEdit->TransThisTextToThisInt(),
                     speed, delay);
    ret.append(item);
    item.Set3DAction(ICMold::GY, type, ui->y1PosLineEdit->TransThisTextToThisInt(),
                      speed, delay);
    ret.append(item);
    item.Set3DAction(ICMold::GZ, type, ui->zPosLineEdit->TransThisTextToThisInt(),
                      speed, delay);
    ret.append(item);
    if(ui->curveButton->isChecked())
    {
        item.Set3DAction(ICMold::GA, type, ui->x1PosLineEdit_2->TransThisTextToThisInt(),
                          speed, delay);
        ret.append(item);
        item.Set3DAction(ICMold::GB, type, ui->y1PosLineEdit_2->TransThisTextToThisInt(),
                          speed, delay);
        ret.append(item);
        item.Set3DAction(ICMold::GC, type, ui->zPosLineEdit_2->TransThisTextToThisInt(),
                          speed, delay);
        ret.append(item);

        ret[0].Set3DAction(ICMold::GX, type, ui->x1PosLineEdit->TransThisTextToThisInt(),
                           speed, delay, ui->angleLineEdit->TransThisTextToThisInt(), ui->dirBox->currentIndex());

    }
    return ret;
}

void ICCurveEditor::onTypeChanged(QAbstractButton *button)
{
    if(button == ui->lineButton)
    {
        ui->point2Group->setEnabled(false);
    }
    else if(button == ui->curveButton)
    {
        ui->point2Group->setEnabled(true);

    }
}


void ICCurveEditor::on_setInPoint1_clicked()
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    ui->x1PosLineEdit->setText(QString().sprintf("%.2f", host->GetActualPos(ICVirtualHost::ICAxis_AxisX1) / 100.0));
    ui->y1PosLineEdit->setText(QString().sprintf("%.2f", host->GetActualPos(ICVirtualHost::ICAxis_AxisY1) / 100.0));
    ui->zPosLineEdit->setText(QString().sprintf("%.2f", host->GetActualPos(ICVirtualHost::ICAxis_AxisZ) / 100.0));
}

void ICCurveEditor::on_setInPoint2_clicked()
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    ui->x1PosLineEdit_2->setText(QString().sprintf("%.2f", host->GetActualPos(ICVirtualHost::ICAxis_AxisX1) / 100.0));
    ui->y1PosLineEdit_2->setText(QString().sprintf("%.2f", host->GetActualPos(ICVirtualHost::ICAxis_AxisY1) / 100.0));
    ui->zPosLineEdit_2->setText(QString().sprintf("%.2f", host->GetActualPos(ICVirtualHost::ICAxis_AxisZ) / 100.0));

}
