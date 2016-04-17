#include "icsimpleteachpage.h"
#include "ui_icsimpleteachpage.h"
#include "config.h"

ICSimpleTeachPage::ICSimpleTeachPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ICSimpleTeachPage)
{
    ui->setupUi(this);
    ui->stdPosX1->SetDecimalPlaces(POS_DECIMAL);
    ui->stdPosY1->SetDecimalPlaces(POS_DECIMAL);
    ui->stdPosZ->SetDecimalPlaces(POS_DECIMAL);
    ui->stdPosX2->SetDecimalPlaces(POS_DECIMAL);
    ui->stdPosY2->SetDecimalPlaces(POS_DECIMAL);

    ui->getProductPosX1->SetDecimalPlaces(POS_DECIMAL);
    ui->getProductPosY1->SetDecimalPlaces(POS_DECIMAL);
    ui->getProductPosZ->SetDecimalPlaces(POS_DECIMAL);
    ui->getProductPosX2->SetDecimalPlaces(POS_DECIMAL);
    ui->getProductPosY2->SetDecimalPlaces(POS_DECIMAL);

    ui->getOutletPosX1->SetDecimalPlaces(POS_DECIMAL);
    ui->getOutletPosY1->SetDecimalPlaces(POS_DECIMAL);
    ui->getOutletPosZ->SetDecimalPlaces(POS_DECIMAL);
    ui->getOutletPosX2->SetDecimalPlaces(POS_DECIMAL);
    ui->getOutletPosY2->SetDecimalPlaces(POS_DECIMAL);

    ui->posBHorX1->SetDecimalPlaces(POS_DECIMAL);
    ui->posBHorY1->SetDecimalPlaces(POS_DECIMAL);
    ui->posBHorZ->SetDecimalPlaces(POS_DECIMAL);
    ui->posBHorX2->SetDecimalPlaces(POS_DECIMAL);
    ui->posBHorY2->SetDecimalPlaces(POS_DECIMAL);

    ui->releaseProductPosX1->SetDecimalPlaces(POS_DECIMAL);
    ui->releaseProductPosY1->SetDecimalPlaces(POS_DECIMAL);
    ui->releaseProductPosZ->SetDecimalPlaces(POS_DECIMAL);
    ui->releaseProductPosX2->SetDecimalPlaces(POS_DECIMAL);
    ui->releaseProductPosY2->SetDecimalPlaces(POS_DECIMAL);

    ui->releaseOutletPosX1->SetDecimalPlaces(POS_DECIMAL);
    ui->releaseOutletPosY1->SetDecimalPlaces(POS_DECIMAL);
    ui->releaseOutletPosZ->SetDecimalPlaces(POS_DECIMAL);
    ui->releaseOutletPosX2->SetDecimalPlaces(POS_DECIMAL);
    ui->releaseOutletPosY2->SetDecimalPlaces(POS_DECIMAL);

    ui->cutOutletPosX1->SetDecimalPlaces(POS_DECIMAL);
    ui->cutOutletPosY1->SetDecimalPlaces(POS_DECIMAL);
    ui->cutOutletPosZ->SetDecimalPlaces(POS_DECIMAL);

}

ICSimpleTeachPage::~ICSimpleTeachPage()
{
    delete ui;
}

void ICSimpleTeachPage::changeEvent(QEvent *e)
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

void ICSimpleTeachPage::showEvent(QShowEvent *e)
{
    ui->posInsideBtn->setChecked(true);

    QWidget::showEvent(e);
}


void ICSimpleTeachPage::on_pushButton_2_toggled(bool checked)
{
    if(checked)
        ui->posPageContainer->setCurrentIndex(1);
}

void ICSimpleTeachPage::on_pushButton_3_toggled(bool checked)
{
    if(checked)
        ui->posPageContainer->setCurrentIndex(2);
}

void ICSimpleTeachPage::on_posInsideBtn_toggled(bool checked)
{
    if(checked)
        ui->posPageContainer->setCurrentIndex(0);
}

void ICSimpleTeachPage::on_mainArmEn_toggled(bool checked)
{
    ui->cutOutletEn->setEnabled(checked);
}

void ICSimpleTeachPage::on_mainArmOutletEn_toggled(bool checked)
{
    if(checked)
        ui->subArmEn->setChecked(false);
}

void ICSimpleTeachPage::on_subArmEn_toggled(bool checked)
{
    if(checked)
        ui->mainArmOutletEn->setChecked(false);
}

void ICSimpleTeachPage::SetMainArmPosEnabled(bool en)
{

}

void ICSimpleTeachPage::SetSubArmPosEnabled(bool en)
{

}

bool ICSimpleTeachPage::UsedMainArm() const
{
    return ui->mainArmEn->isChecked() || ui->mainArmOutletEn->isChecked();
}

bool ICSimpleTeachPage::UsedSubArm() const
{
    return ui->subArmEn->isChecked();
}

QString ICSimpleTeachPage::PosDataToString(const QVariantList &data, bool noSubArm,  const QString& dataName) const
{
    QString ret;
    if(UsedMainArm())
        ret += QString(tr("X1:%1, Y1:%2, ")).arg(QString::number(data.at(0).toInt() / 100.0, 'f', 2))
                .arg(QString::number(data.at(1).toInt() / 100.0, 'f', 2));
    ret += QString(tr("Z:%1\n")).arg(QString::number(data.at(2).toInt() / 100.0, 'f', 2));
    if(UsedSubArm() && !noSubArm)
        ret += QString(tr(", X2:%1, Y2:%2")).arg(QString::number(data.at(3).toInt() / 100.0, 'f', 2))
                .arg(QString::number(data.at(4).toInt() / 100.0, 'f', 2));
    return ret;

}

void ICSimpleTeachPage::on_addProductPos_clicked()
{
    QVariantList posData;
    posData<<ui->releaseProductPosX1->TransThisTextToThisInt()
          <<ui->releaseProductPosY1->TransThisTextToThisInt()
            <<ui->releaseProductPosZ->TransThisTextToThisInt()
              <<ui->releaseProductPosX2->TransThisTextToThisInt()
                <<ui->releaseProductPosY2->TransThisTextToThisInt();
    releasePosModelData.append(posData);
    ui->releasePosView->addItem(PosDataToString(posData));
}

void ICSimpleTeachPage::on_modifyProductPos_clicked()
{
    QList<QListWidgetItem*> selected = ui->releasePosView->selectedItems();
    if(selected.size() == 0) return;
    int toModifyIndex = ui->releasePosView->row(selected.at(0));
    QVariantList posData;
    posData<<ui->releaseProductPosX1->TransThisTextToThisInt()
          <<ui->releaseProductPosY1->TransThisTextToThisInt()
            <<ui->releaseProductPosZ->TransThisTextToThisInt()
              <<ui->releaseProductPosX2->TransThisTextToThisInt()
                <<ui->releaseProductPosY2->TransThisTextToThisInt();
    releasePosModelData[toModifyIndex] = posData;
    selected[0]->setText(PosDataToString(posData));
}

void ICSimpleTeachPage::on_deleteProductPos_clicked()
{
    QList<QListWidgetItem*> selected = ui->releasePosView->selectedItems();
    if(selected.size() == 0) return;
    int toModifyIndex = ui->releasePosView->row(selected.at(0));
    releasePosModelData.removeAt(toModifyIndex);
    delete ui->releasePosView->takeItem(toModifyIndex);
}


void ICSimpleTeachPage::on_addOutletPos_clicked()
{
    QVariantList posData;
    posData<<ui->releaseOutletPosX1->TransThisTextToThisInt()
          <<ui->releaseOutletPosY1->TransThisTextToThisInt()
            <<ui->releaseOutletPosZ->TransThisTextToThisInt()
              <<ui->releaseOutletPosX2->TransThisTextToThisInt()
                <<ui->releaseOutletPosY2->TransThisTextToThisInt();
    releaseOutletModelData.append(posData);
    ui->releaseOutletView->addItem(PosDataToString(posData));

}

void ICSimpleTeachPage::on_modifyOutletPos_clicked()
{
    QList<QListWidgetItem*> selected = ui->releaseOutletView->selectedItems();
    if(selected.size() == 0) return;
    int toModifyIndex = ui->releaseOutletView->row(selected.at(0));
    QVariantList posData;
    posData<<ui->releaseOutletPosX1->TransThisTextToThisInt()
          <<ui->releaseOutletPosY1->TransThisTextToThisInt()
            <<ui->releaseOutletPosZ->TransThisTextToThisInt()
              <<ui->releaseOutletPosX2->TransThisTextToThisInt()
                <<ui->releaseOutletPosY2->TransThisTextToThisInt();
    releaseOutletModelData[toModifyIndex] = posData;
    selected[0]->setText(PosDataToString(posData));
}

void ICSimpleTeachPage::on_deleteOutletPos_clicked()
{
    QList<QListWidgetItem*> selected = ui->releaseOutletView->selectedItems();
    if(selected.size() == 0) return;
    int toModifyIndex = ui->releaseOutletView->row(selected.at(0));
    releaseOutletModelData.removeAt(toModifyIndex);
    delete ui->releaseOutletView->takeItem(toModifyIndex);
}

void ICSimpleTeachPage::on_addCut_clicked()
{
    QVariantList posData;
    posData<<ui->cutOutletPosX1->TransThisTextToThisInt()
          <<ui->cutOutletPosY1->TransThisTextToThisInt()
            <<ui->cutOutletPosZ->TransThisTextToThisInt()
              <<0<<0;
    cutOutletModelData.append(posData);
    ui->cutPosView->addItem(PosDataToString(posData, true));
}

void ICSimpleTeachPage::on_modifyCut_clicked()
{
    QList<QListWidgetItem*> selected = ui->cutPosView->selectedItems();
    if(selected.size() == 0) return;
    int toModifyIndex = ui->cutPosView->row(selected.at(0));
    QVariantList posData;
    posData<<ui->cutOutletPosX1->TransThisTextToThisInt()
          <<ui->cutOutletPosY1->TransThisTextToThisInt()
            <<ui->cutOutletPosZ->TransThisTextToThisInt()
              <<0<<0;
    cutOutletModelData[toModifyIndex] = posData;
    selected[0]->setText(PosDataToString(posData, true));
}

void ICSimpleTeachPage::on_deleteCut_clicked()
{
    QList<QListWidgetItem*> selected = ui->cutPosView->selectedItems();
    if(selected.size() == 0) return;
    int toModifyIndex = ui->cutPosView->row(selected.at(0));
    cutOutletModelData.removeAt(toModifyIndex);
    delete ui->cutPosView->takeItem(toModifyIndex);
}
