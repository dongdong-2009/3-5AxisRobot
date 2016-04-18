#include "icsimpleteachpage.h"
#include "ui_icsimpleteachpage.h"
#include "config.h"
#include <QDebug>

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

void ICSimpleTeachPage::on_posOutsideBtn_toggled(bool checked)
{
    if(checked)
        ui->posPageContainer->setCurrentIndex(1);
}

void ICSimpleTeachPage::on_posOfCutBtn_toggled(bool checked)
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
    SetMainArmPosEnabled(checked || ui->mainArmOutletEn->isChecked());
}

void ICSimpleTeachPage::on_mainArmOutletEn_toggled(bool checked)
{
    if(checked)
        ui->subArmEn->setChecked(false);
    SetMainArmPosEnabled(checked || ui->mainArmEn->isChecked());

}

void ICSimpleTeachPage::on_subArmEn_toggled(bool checked)
{
    if(checked)
        ui->mainArmOutletEn->setChecked(false);
    SetSubArmPosEnabled(checked);
}

void ICSimpleTeachPage::SetMainArmPosEnabled(bool en)
{
    ui->stdPosX1->setVisible(en);
    ui->stdPosY1->setVisible(en);

    ui->getProductPosX1->setVisible(en);
    ui->getProductPosY1->setVisible(en);

    ui->getOutletPosX1->setVisible(en);
    ui->getOutletPosY1->setVisible(en);

    ui->posBHorX1->setVisible(en);
    ui->posBHorY1->setVisible(en);

    ui->releaseProductPosX1->setVisible(en);
    ui->releaseProductPosY1->setVisible(en);

    ui->releaseOutletPosX1->setVisible(en);
    ui->releaseOutletPosY1->setVisible(en);

    ui->cutOutletPosX1->setVisible(en);
    ui->cutOutletPosY1->setVisible(en);

    ui->stdSpeedX1->setVisible(en);
    ui->stdSpeedY1->setVisible(en);
    ui->getProductSpeedX1->setVisible(en);
    ui->getProductSpeedY1->setVisible(en);
    ui->getOutletSpeedX1->setVisible(en);
    ui->getOutletSpeedY1->setVisible(en);
    ui->speedBHorX1->setVisible(en);
    ui->speedBHorY1->setVisible(en);

    ui->pIX1Label->setVisible(en);
    ui->pIX1Label_2->setVisible(en);
    ui->pIX1Label_3->setVisible(en);
    ui->pIX1Label_4->setVisible(en);
    ui->pIX1mmLabel->setVisible(en);
    ui->pIX1mmLabel_2->setVisible(en);
    ui->pIX1mmLabel_3->setVisible(en);
    ui->pIX1SpeedLabel->setVisible(en);


    ui->pIY1Label->setVisible(en);
    ui->pIY1Label_2->setVisible(en);
    ui->pIY1Label_3->setVisible(en);
    ui->pIY1Label_4->setVisible(en);
    ui->pIY1mmLabel->setVisible(en);
    ui->pIY1mmLabel_2->setVisible(en);
    ui->pIY1mmLabel_3->setVisible(en);
    ui->pIY1SpeedLabel->setVisible(en);
}

void ICSimpleTeachPage::SetSubArmPosEnabled(bool en)
{
    ui->stdPosX2->setVisible(en);
    ui->stdPosY2->setVisible(en);

    ui->getProductPosX2->setVisible(en);
    ui->getProductPosY2->setVisible(en);

    ui->getOutletPosX2->setVisible(en);
    ui->getOutletPosY2->setVisible(en);

    ui->posBHorX2->setVisible(en);
    ui->posBHorY2->setVisible(en);

    ui->releaseProductPosX2->setVisible(en);
    ui->releaseProductPosY2->setVisible(en);

    ui->releaseOutletPosX2->setVisible(en);
    ui->releaseOutletPosY2->setVisible(en);

    ui->stdSpeedX2->setVisible(en);
    ui->stdSpeedY2->setVisible(en);
    ui->getProductSpeedX2->setVisible(en);
    ui->getProductSpeedY2->setVisible(en);
    ui->getOutletSpeedX2->setVisible(en);
    ui->getOutletSpeedY2->setVisible(en);
    ui->speedBHorX2->setVisible(en);
    ui->speedBHorY2->setVisible(en);

    ui->pIX2Label->setVisible(en);
    ui->pIX2Label_2->setVisible(en);
    ui->pIX2Label_3->setVisible(en);
    ui->pIX2mmLabel->setVisible(en);
    ui->pIX2mmLabel_2->setVisible(en);
    ui->pIX2SpeedLabel->setVisible(en);

    ui->pIY2Label->setVisible(en);
    ui->pIY2Label_2->setVisible(en);
    ui->pIY2Label_3->setVisible(en);
    ui->pIY2mmLabel->setVisible(en);
    ui->pIY2mmLabel_2->setVisible(en);
    ui->pIY2SpeedLabel->setVisible(en);

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

ICLineEditWithVirtualNumericKeypad* CreateSpeedEdit(int speed, const QValidator* v)
{
    ICLineEditWithVirtualNumericKeypad* tmp = new ICLineEditWithVirtualNumericKeypad();
    tmp->SetDecimalPlaces(0);
    tmp->setValidator(v);
    tmp->SetThisIntToThisText(speed);
    return tmp;
}

void ICSimpleTeachPage::AddPosHelper(QGridLayout *layout, QList<PosSpeedUIWidgets> &speedUI, const QString& posName)
{
    int toInsertRow = speedUI.size();
    PosSpeedUIWidgets tmp;
    tmp.b.posName = new QLabel(QString(tr("%2-%1")).arg(toInsertRow + 1).arg(posName));
    tmp.b.posName->setMinimumWidth(ui->label_20->minimumWidth());
    tmp.b.posName->setMaximumWidth(ui->label_20->maximumWidth());
    tmp.b.x1SpeedEdit = CreateSpeedEdit(80, &speedValidator_);
    tmp.b.y1SpeedEdit = CreateSpeedEdit(80, &speedValidator_);
    tmp.b.zSpeedEdit = CreateSpeedEdit(80, &speedValidator_);
    tmp.b.x2SpeedEdit = CreateSpeedEdit(80, &speedValidator_);
    tmp.b.y2SpeedEdit = CreateSpeedEdit(80, &speedValidator_);
    speedUI.append(tmp);
    for(int i = 0; i < 6; ++i)
        layout->addWidget(tmp.all[i], toInsertRow, i);
}

void ICSimpleTeachPage::DelPosHelper(int row, QGridLayout *layout, QList<PosSpeedUIWidgets> &speedUI, const QString &posName)
{
    PosSpeedUIWidgets toDel = speedUI.at(row);
    for(int i = 0;i < 6; ++i)
    {
        layout->removeWidget(toDel.all[i]);
        toDel.all[i]->close();
        toDel.all[i]->deleteLater();
    }
    speedUI.removeAt(row);
    for(int i = row; i < speedUI.size(); ++i)
    {
        speedUI[i].b.posName->setText(QString(tr("%2-%1")).arg(i + 1).arg(posName));
    }
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

    AddPosHelper(ui->releaseProductSpeedGroup, releaseProductSpeedUI, tr("Rel Product"));
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

    DelPosHelper(toModifyIndex, ui->releaseProductSpeedGroup, releaseProductSpeedUI, tr("Rel Product"));
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

    AddPosHelper(ui->releaseOutletSpeedGroup, releaseOutletSpeedUI, tr("Rel Outlet"));
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

    DelPosHelper(toModifyIndex, ui->releaseOutletSpeedGroup, releaseOutletSpeedUI, tr("Rel Outlet"));
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

    AddPosHelper(ui->cutOutletSpeedGroup, cutOutletSpeedUI, tr("Cut Pos"));
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

    DelPosHelper(toModifyIndex, ui->cutOutletSpeedGroup, cutOutletSpeedUI, tr("Cut Pos"));
}



