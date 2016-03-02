#include "icbadproducteditor.h"
#include "ui_icbadproducteditor.h"
#include "icmold.h"
#include "icvirtualhost.h"

ICBadProductEditor::ICBadProductEditor(QWidget *parent) :
    ICInstructionEditorBase(parent),
    ui(new Ui::ICBadProductEditor)
{
    ui->setupUi(this);
    ui->x1Pos->SetDecimalPlaces(2);
    ui->y1Pos->SetDecimalPlaces(2);
    ui->zPos->SetDecimalPlaces(2);
    ui->x1Speed->SetDecimalPlaces(0);
    ui->y1Speed->SetDecimalPlaces(0);
    ui->zSpeed->SetDecimalPlaces(0);

    ui->x1Pos->setValidator(new QIntValidator(0, 655300, this));
    ui->y1Pos->setValidator(ui->x1Pos->validator());
    ui->zPos->setValidator(ui->x1Pos->validator());

    ui->x1Speed->setValidator(new QIntValidator(0, 100, this));
    ui->y1Speed->setValidator(ui->x1Speed->validator());
    ui->zSpeed->setValidator(ui->x1Speed->validator());

}

ICBadProductEditor::~ICBadProductEditor()
{
    delete ui;
}

void ICBadProductEditor::showEvent(QShowEvent *e)
{
    QList<uint> badPos = ICMold::CurrentMold()->BadProductPos();
    ui->badProductEn->setChecked(ICMold::CurrentMold()->IsBadProductEn());
    ui->x1Pos->SetThisIntToThisText(badPos.at(0));
    ui->y1Pos->SetThisIntToThisText(badPos.at(1));
    ui->zPos->SetThisIntToThisText(badPos.at(2));
    ui->x1Speed->SetThisIntToThisText(badPos.at(3));
    ui->y1Speed->SetThisIntToThisText(badPos.at(4));
    ui->zSpeed->SetThisIntToThisText(badPos.at(5));
}

void ICBadProductEditor::changeEvent(QEvent *e)
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

void ICBadProductEditor::on_okButton_clicked()
{
    ICMold::CurrentMold()->SetBadProductEn(ui->badProductEn->isChecked());
    ICMold::CurrentMold()->SetBadProductPos(QList<uint>()<<ui->x1Pos->TransThisTextToThisInt()
                                            <<ui->y1Pos->TransThisTextToThisInt()
                                            <<ui->zPos->TransThisTextToThisInt()
                                            <<ui->x1Speed->TransThisTextToThisInt()
                                            <<ui->y1Speed->TransThisTextToThisInt()
                                            <<ui->zSpeed->TransThisTextToThisInt());
    emit BadProductSettingChanged();
}

void ICBadProductEditor::on_setInBtn_clicked()
{
    ui->x1Pos->SetThisIntToThisText(ICVirtualHost::GlobalVirtualHost()->GetActualPos(ICVirtualHost::ICAxis_AxisX1));
    ui->y1Pos->SetThisIntToThisText(ICVirtualHost::GlobalVirtualHost()->GetActualPos(ICVirtualHost::ICAxis_AxisY1));
    ui->zPos->SetThisIntToThisText(ICVirtualHost::GlobalVirtualHost()->GetActualPos(ICVirtualHost::ICAxis_AxisZ));

}
