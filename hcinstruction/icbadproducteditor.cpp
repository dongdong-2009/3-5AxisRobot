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
    ui->x2Pos->SetDecimalPlaces(2);
    ui->y2Pos->SetDecimalPlaces(2);
    ui->x1Speed->SetDecimalPlaces(0);
    ui->y1Speed->SetDecimalPlaces(0);
    ui->zSpeed->SetDecimalPlaces(0);
    ui->x2Speed->SetDecimalPlaces(0);
    ui->y2Speed->SetDecimalPlaces(0);


    ui->x1Pos->setValidator(new QIntValidator(0, 655300, this));
    ui->y1Pos->setValidator(ui->x1Pos->validator());
    ui->zPos->setValidator(ui->x1Pos->validator());
    ui->x2Pos->setValidator(ui->x1Pos->validator());
    ui->y2Pos->setValidator(ui->x1Pos->validator());

    ui->x1Speed->setValidator(new QIntValidator(0, 100, this));
    ui->y1Speed->setValidator(ui->x1Speed->validator());
    ui->zSpeed->setValidator(ui->x1Speed->validator());
    ui->x2Speed->setValidator(ui->x1Speed->validator());
    ui->y2Speed->setValidator(ui->x1Speed->validator());

    ui->x1Pos_2->SetDecimalPlaces(2);
    ui->y1Pos_2->SetDecimalPlaces(2);
    ui->zPos_2->SetDecimalPlaces(2);
    ui->x2Pos_2->SetDecimalPlaces(2);
    ui->y2Pos_2->SetDecimalPlaces(2);
    ui->x1Speed_2->SetDecimalPlaces(0);
    ui->y1Speed_2->SetDecimalPlaces(0);
    ui->zSpeed_2->SetDecimalPlaces(0);
    ui->x2Speed_2->SetDecimalPlaces(0);
    ui->y2Speed_2->SetDecimalPlaces(0);

    ui->x1Pos_2->setValidator(new QIntValidator(0, 655300, this));
    ui->y1Pos_2->setValidator(ui->x1Pos_2->validator());
    ui->zPos_2->setValidator(ui->x1Pos_2->validator());
    ui->x2Pos_2->setValidator(ui->x1Pos_2->validator());
    ui->y2Pos_2->setValidator(ui->x1Pos_2->validator());

    ui->x1Speed_2->setValidator(new QIntValidator(0, 100, this));
    ui->y1Speed_2->setValidator(ui->x1Speed_2->validator());
    ui->zSpeed_2->setValidator(ui->x1Speed_2->validator());
    ui->x2Speed_2->setValidator(ui->x1Speed_2->validator());
    ui->y2Speed_2->setValidator(ui->x1Speed_2->validator());

    ui->tryCount->setValidator(new QIntValidator(0, 65530, this));
}

ICBadProductEditor::~ICBadProductEditor()
{
    delete ui;
}

void ICBadProductEditor::showEvent(QShowEvent *e)
{
    QList<uint> badPos = ICMold::CurrentMold()->BadProductPos();
    ui->badProductEn->setChecked(ICMold::CurrentMold()->IsBadProductEn());
    ui->subArm->setChecked(ICMold::CurrentMold()->IsSubArmBPEn());
    ui->mainArm->setChecked(!ui->subArm->isChecked());
    ui->x1Pos->SetThisIntToThisText(badPos.at(0));
    ui->y1Pos->SetThisIntToThisText(badPos.at(1));
    ui->zPos->SetThisIntToThisText(badPos.at(2));
    ui->x2Pos->SetThisIntToThisText(badPos.at(3));
    ui->y2Pos->SetThisIntToThisText(badPos.at(4));
    ui->x1Speed->SetThisIntToThisText(badPos.at(5));
    ui->y1Speed->SetThisIntToThisText(badPos.at(6));
    ui->zSpeed->SetThisIntToThisText(badPos.at(7));
    ui->x2Speed->SetThisIntToThisText(badPos.at(8));
    ui->y2Speed->SetThisIntToThisText(badPos.at(9));

    QList<uint> tryPos = ICMold::CurrentMold()->TryProductPos();
    ui->tryProductEn->setChecked(ICMold::CurrentMold()->IsTryProductEn());
    ui->x1Pos_2->SetThisIntToThisText(tryPos.at(0));
    ui->y1Pos_2->SetThisIntToThisText(tryPos.at(1));
    ui->zPos_2->SetThisIntToThisText(tryPos.at(2));
    ui->x2Pos_2->SetThisIntToThisText(tryPos.at(3));
    ui->y2Pos_2->SetThisIntToThisText(tryPos.at(4));
    ui->x1Speed_2->SetThisIntToThisText(tryPos.at(5));
    ui->y1Speed_2->SetThisIntToThisText(tryPos.at(6));
    ui->zSpeed_2->SetThisIntToThisText(tryPos.at(7));
    ui->x2Speed_2->SetThisIntToThisText(tryPos.at(8));
    ui->y2Speed_2->SetThisIntToThisText(tryPos.at(9));

    ui->tryCount->SetThisIntToThisText(ICMold::CurrentMold()->MoldParam(ICMold::TryProduct));
//    ui->mainArm->setChecked(true);
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
                                            <<ui->x2Pos->TransThisTextToThisInt()
                                            <<ui->y2Pos->TransThisTextToThisInt()
                                            <<ui->x1Speed->TransThisTextToThisInt()
                                            <<ui->y1Speed->TransThisTextToThisInt()
                                            <<ui->zSpeed->TransThisTextToThisInt()
                                            <<ui->x2Speed->TransThisTextToThisInt()
                                            <<ui->y2Speed->TransThisTextToThisInt());

    ICMold::CurrentMold()->SetTryProductEn(ui->tryProductEn->isChecked());
    ICMold::CurrentMold()->SetTryProductPos(QList<uint>()<<ui->x1Pos_2->TransThisTextToThisInt()
                                            <<ui->y1Pos_2->TransThisTextToThisInt()
                                            <<ui->zPos_2->TransThisTextToThisInt()
                                            <<ui->x2Pos_2->TransThisTextToThisInt()
                                            <<ui->y2Pos_2->TransThisTextToThisInt()
                                            <<ui->x1Speed_2->TransThisTextToThisInt()
                                            <<ui->y1Speed_2->TransThisTextToThisInt()
                                            <<ui->zSpeed_2->TransThisTextToThisInt()
                                            <<ui->x2Speed_2->TransThisTextToThisInt()
                                            <<ui->y2Speed_2->TransThisTextToThisInt());

    ICMold::CurrentMold()->SetMoldParam(ICMold::TryProduct, ui->tryCount->TransThisTextToThisInt());
    ICMold::CurrentMold()->SetSubArmBPEn(ui->subArm->isChecked());
    emit BadProductSettingChanged();
}

void ICBadProductEditor::on_setInBtn_clicked()
{
    ui->x1Pos->SetThisIntToThisText(ICVirtualHost::GlobalVirtualHost()->GetActualPos(ICVirtualHost::ICAxis_AxisX1));
    ui->y1Pos->SetThisIntToThisText(ICVirtualHost::GlobalVirtualHost()->GetActualPos(ICVirtualHost::ICAxis_AxisY1));
    ui->zPos->SetThisIntToThisText(ICVirtualHost::GlobalVirtualHost()->GetActualPos(ICVirtualHost::ICAxis_AxisZ));
    ui->x2Pos->SetThisIntToThisText(ICVirtualHost::GlobalVirtualHost()->GetActualPos(ICVirtualHost::ICAxis_AxisX2));
    ui->y2Pos->SetThisIntToThisText(ICVirtualHost::GlobalVirtualHost()->GetActualPos(ICVirtualHost::ICAxis_AxisY2));
}

void ICBadProductEditor::on_badProductEn_toggled(bool checked)
{
    ui->okButton->setStyleSheet((checked || ui->tryProductEn->isChecked()) ? "background-color: rgb(0, 255, 0);" : "");
}



void ICBadProductEditor::on_tryProductEn_toggled(bool checked)
{
    ui->okButton->setStyleSheet((checked || ui->badProductEn->isChecked()) ? "background-color: rgb(0, 255, 0);" : "");
}

void ICBadProductEditor::on_setInBtn_2_clicked()
{
    ui->x1Pos_2->SetThisIntToThisText(ICVirtualHost::GlobalVirtualHost()->GetActualPos(ICVirtualHost::ICAxis_AxisX1));
    ui->y1Pos_2->SetThisIntToThisText(ICVirtualHost::GlobalVirtualHost()->GetActualPos(ICVirtualHost::ICAxis_AxisY1));
    ui->zPos_2->SetThisIntToThisText(ICVirtualHost::GlobalVirtualHost()->GetActualPos(ICVirtualHost::ICAxis_AxisZ));
    ui->x2Pos_2->SetThisIntToThisText(ICVirtualHost::GlobalVirtualHost()->GetActualPos(ICVirtualHost::ICAxis_AxisX2));
    ui->y2Pos_2->SetThisIntToThisText(ICVirtualHost::GlobalVirtualHost()->GetActualPos(ICVirtualHost::ICAxis_AxisY2));
}
