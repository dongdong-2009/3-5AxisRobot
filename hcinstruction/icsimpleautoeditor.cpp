#include "icsimpleautoeditor.h"
#include "ui_icsimpleautoeditor.h"
#include <QKeyEvent>

ICSimpleAutoEditor::ICSimpleAutoEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ICSimpleAutoEditor)
{
    ui->setupUi(this);
    delayValidator_.setRange(0, 30000);

    ui->stdDlyX1->setValidator(&delayValidator_);
    ui->stdDlyY1->setValidator(&delayValidator_);
    ui->stdDlyZ->setValidator(&delayValidator_);
    ui->stdDlyX2->setValidator(&delayValidator_);
    ui->stdDlyY2->setValidator(&delayValidator_);


    ui->getProductDlyX1->setValidator(&delayValidator_);
    ui->getProductDlyY1->setValidator(&delayValidator_);
    ui->getProductDlyZ->setValidator(&delayValidator_);
    ui->getProductDlyX2->setValidator(&delayValidator_);
    ui->getProductDlyY2->setValidator(&delayValidator_);

    ui->getOutletDlyX1->setValidator(&delayValidator_);
    ui->getOutletDlyY1->setValidator(&delayValidator_);
    ui->getOutletDlyZ->setValidator(&delayValidator_);
    ui->getOutletDlyX2->setValidator(&delayValidator_);
    ui->getOutletDlyY2->setValidator(&delayValidator_);

    ui->DlyBHorX1->setValidator(&delayValidator_);
    ui->DlyBHorY1->setValidator(&delayValidator_);
    ui->DlyBHorZ->setValidator(&delayValidator_);
    ui->DlyBHorX2->setValidator(&delayValidator_);
    ui->DlyBHorY2->setValidator(&delayValidator_);

    ui->stdDlyX1->SetDecimalPlaces(2);
    ui->stdDlyY1->SetDecimalPlaces(2);
    ui->stdDlyZ->SetDecimalPlaces(2);
    ui->stdDlyX2->SetDecimalPlaces(2);
    ui->stdDlyY2->SetDecimalPlaces(2);


    ui->getProductDlyX1->SetDecimalPlaces(2);
    ui->getProductDlyY1->SetDecimalPlaces(2);
    ui->getProductDlyZ->SetDecimalPlaces(2);
    ui->getProductDlyX2->SetDecimalPlaces(2);
    ui->getProductDlyY2->SetDecimalPlaces(2);

    ui->getOutletDlyX1->SetDecimalPlaces(2);
    ui->getOutletDlyY1->SetDecimalPlaces(2);
    ui->getOutletDlyZ->SetDecimalPlaces(2);
    ui->getOutletDlyX2->SetDecimalPlaces(2);
    ui->getOutletDlyY2->SetDecimalPlaces(2);

    ui->DlyBHorX1->SetDecimalPlaces(2);
    ui->DlyBHorY1->SetDecimalPlaces(2);
    ui->DlyBHorZ->SetDecimalPlaces(2);
    ui->DlyBHorX2->SetDecimalPlaces(2);
    ui->DlyBHorY2->SetDecimalPlaces(2);

}

ICSimpleAutoEditor::~ICSimpleAutoEditor()
{
    delete ui;
}

void ICSimpleAutoEditor::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void ICSimpleAutoEditor::showEvent(QShowEvent *e)
{
    stData_ = ICMold::CurrentMold()->GetSimpleTeachData();
    SetMainArmPosEnabled(UsedMainArm());
    QDialog::showEvent(e);
}

void ICSimpleAutoEditor::SetMainArmPosEnabled(bool en)
{
    ui->afterGetPosX1D->setVisible(en);
    ui->stdDlyX1->setVisible(en);
    ui->stdDlyY1->setVisible(en);
    ui->getProductDlyX1->setVisible(stData_->usedMainArm);
    ui->getProductDlyY1->setVisible(stData_->usedMainArm);
    ui->getOutletDlyX1->setVisible(en && UsedReleaseOutlet());
    ui->getOutletDlyY1->setVisible(en && UsedReleaseOutlet());
    ui->DlyBHorX1->setVisible(en);
    ui->DlyBHorY1->setVisible(en);

    ui->pIX1Label_4->setVisible(en);
    ui->pIX1DlyLabel->setVisible(UsedMainArm());


    ui->pIY1Label_4->setVisible(en);
    ui->pIY1DlyLabel->setVisible(UsedMainArm());

    PosDlyUIWidgets DlyUI;
    for(int i = 0; i < releaseProductDlyUI.size(); ++i)
    {
        DlyUI = releaseProductDlyUI.at(i);
        DlyUI.b.x1DlyEdit->setVisible(stData_->usedMainArm);
        DlyUI.b.y1DlyEdit->setVisible(stData_->usedMainArm);

    }

    for(int i = 0; i < releaseOutletDlyUI.size(); ++i)
    {
        DlyUI = releaseOutletDlyUI.at(i);
        DlyUI.b.x1DlyEdit->setVisible(en && UsedReleaseOutlet());
        DlyUI.b.y1DlyEdit->setVisible(en && UsedReleaseOutlet());
    }

    for(int i = 0; i < cutOutletDlyUI.size(); ++i)
    {
        DlyUI = cutOutletDlyUI.at(i);
        DlyUI.b.x1DlyEdit->setVisible(stData_->usedMainArm);
        DlyUI.b.y1DlyEdit->setVisible(stData_->usedMainArm);
    }
}

void ICSimpleAutoEditor::SetSubArmPosEnabled(bool en)
{
    ui->afterGetPosX2D->setVisible(en);


    ui->stdDlyX2->setVisible(en);
    ui->stdDlyY2->setVisible(en);
    ui->getProductDlyX2->setVisible(en && UsedMainArm());
    ui->getProductDlyY2->setVisible(en && UsedMainArm());
    ui->getOutletDlyX2->setVisible(en);
    ui->getOutletDlyY2->setVisible(en);
    ui->DlyBHorX2->setVisible(en);
    ui->DlyBHorY2->setVisible(en);

    ui->pIX2Label_3->setVisible(en);
    ui->pIX2DlyLabel->setVisible(en);

    ui->pIY2Label_3->setVisible(en);
    ui->pIY2DlyLabel->setVisible(en);

    PosDlyUIWidgets DlyUI;
    for(int i = 0; i < releaseProductDlyUI.size(); ++i)
    {
        DlyUI = releaseProductDlyUI.at(i);
        DlyUI.b.x2DlyEdit->setVisible(en && UsedMainArm());
        DlyUI.b.y2DlyEdit->setVisible(en && UsedMainArm());
    }

    for(int i = 0; i < releaseOutletDlyUI.size(); ++i)
    {
        DlyUI = releaseOutletDlyUI.at(i);
        DlyUI.b.x2DlyEdit->setVisible(en);
        DlyUI.b.y2DlyEdit->setVisible(en);
    }

    for(int i = 0; i < cutOutletDlyUI.size(); ++i)
    {
        DlyUI = cutOutletDlyUI.at(i);
        DlyUI.b.x2DlyEdit->setVisible(en && stData_->usedCutOutlet);
        DlyUI.b.y2DlyEdit->setVisible(en && stData_->usedCutOutlet);
    }
}

void ICSimpleAutoEditor::SetReleaseOutletEnabled(bool en)
{
    ui->getOutletDlyX1->setVisible(en && UsedMainArm());
    ui->getOutletDlyY1->setVisible(en && UsedMainArm());
    ui->getOutletDlyX2->setVisible(en && UsedSubArm());
    ui->getOutletDlyY2->setVisible(en && UsedSubArm());
    ui->getOutletDlyZ->setVisible(en);
    ui->label_22->setVisible(en);


    for(int i = 0; i < releaseOutletDlyUI.size(); ++i)
    {
        releaseOutletDlyUI[i].b.posName->setVisible(en);
        releaseOutletDlyUI[i].b.x1DlyEdit->setVisible(en && UsedMainArm());
        releaseOutletDlyUI[i].b.y1DlyEdit->setVisible(en && UsedMainArm());
        releaseOutletDlyUI[i].b.zDlyEdit->setVisible(en);
        releaseOutletDlyUI[i].b.x2DlyEdit->setVisible(en && UsedSubArm());
        releaseOutletDlyUI[i].b.y2DlyEdit->setVisible(en && UsedSubArm());

    }
}

void ICSimpleAutoEditor::SetReleaseProductEnabled(bool en)
{
    ui->label_21->setVisible(en);
    ui->getProductDlyX1->setVisible(en);
    ui->getProductDlyY1->setVisible(en);
    ui->getProductDlyZ->setVisible(en);
    ui->getProductDlyX2->setVisible(en  && UsedReleaseOutlet());
    ui->getProductDlyY2->setVisible(en  && UsedReleaseOutlet());
    ui->label->setVisible(en);

    for(int i = 0; i < releaseProductDlyUI.size(); ++i)
    {
        releaseProductDlyUI[i].b.posName->setVisible(en);
        releaseProductDlyUI[i].b.x1DlyEdit->setVisible(en);
        releaseProductDlyUI[i].b.y1DlyEdit->setVisible(en);
        releaseProductDlyUI[i].b.zDlyEdit->setVisible(en);
        releaseProductDlyUI[i].b.x2DlyEdit->setVisible(en  && UsedReleaseOutlet());
        releaseProductDlyUI[i].b.y2DlyEdit->setVisible(en  && UsedReleaseOutlet());

    }
}

void ICSimpleAutoEditor::SetCutOutletEnabled(bool en)
{
    for(int i = 0; i < cutOutletDlyUI.size(); ++i)
    {
        cutOutletDlyUI[i].b.posName->setVisible(en);
        cutOutletDlyUI[i].b.x1DlyEdit->setVisible(en);
        cutOutletDlyUI[i].b.y1DlyEdit->setVisible(en);
        cutOutletDlyUI[i].b.zDlyEdit->setVisible(en);
        cutOutletDlyUI[i].b.x2DlyEdit->setVisible(en);
        cutOutletDlyUI[i].b.y2DlyEdit->setVisible(en);
    }
}

void ICSimpleAutoEditor::on_cancelButton_clicked()
{
    this->reject();
}

void ICSimpleAutoEditor::on_okButton_clicked()
{
    this->accept();
}

void ICSimpleAutoEditor::keyPressEvent(QKeyEvent *e)
{
    QKeyEvent* ke = new QKeyEvent(*e);
    qApp->postEvent(this->parentWidget(), ke);
    this->reject();
}
