#include "iccutmoduleactionpage.h"
#include "ui_iccutmoduleactionpage.h"
#include "icvirtualhost.h"

QMap<int, QPair<int, int> > indexTofixture;

ICCutModuleActionPage::ICCutModuleActionPage(QWidget *parent) :
    ICInstructionEditorBase(parent),
    ui(new Ui::ICCutModuleActionPage)
{
    ui->setupUi(this);
    ui->zPos->setValidator(new QIntValidator(0, 65530, this));
    ui->x1Pos->setValidator(ui->zPos->validator());
    ui->y1Pos->setValidator(ui->zPos->validator());
    ui->y1UpPos->setValidator(ui->zPos->validator());
    ui->zPos->SetDecimalPlaces(2);
    ui->y1Pos->SetDecimalPlaces(2);
    ui->x1Pos->SetDecimalPlaces(2);
    ui->y1UpPos->SetDecimalPlaces(2);
    ui->x1Speed->setValidator(new QIntValidator(0,100, this));
    ui->y1Speed->setValidator(ui->x1Speed->validator());
    ui->zSpeed->setValidator(ui->x1Speed->validator());
    ui->y1UpSpeed->setValidator(ui->x1Speed->validator());
    ui->fixtureDelay->SetDecimalPlaces(2);
    ui->fixtureDelay->setValidator(new QIntValidator(0, 30000, this));

    indexTofixture.insert(0, qMakePair<int, int>(ICMold::ACTCLIP1ON, ICMold::ACTCLIP1OFF));
    indexTofixture.insert(1, qMakePair<int, int>(ICMold::ACTCLIP2ON, ICMold::ACTCLIP2OFF));
    indexTofixture.insert(2, qMakePair<int, int>(ICMold::ACTCLIP3ON, ICMold::ACTCLIP2OFF));
    indexTofixture.insert(3, qMakePair<int, int>(ICMold::ACTCLIP4ON, ICMold::ACTCLIP2OFF));
    indexTofixture.insert(4, qMakePair<int, int>(ICMold::ACTCLIP5ON, ICMold::ACTCLIP2OFF));
    indexTofixture.insert(5, qMakePair<int, int>(ICMold::ACTCLIP6ON, ICMold::ACTCLIP2OFF));
    indexTofixture.insert(6, qMakePair<int, int>(ICMold::ACT_AUX5, ICMold::ACT_AUX5));
    indexTofixture.insert(7, qMakePair<int, int>(ICMold::ACT_AUX6, ICMold::ACT_AUX6));
    indexTofixture.insert(8, qMakePair<int, int>(ICMold::ACT_AUX1, ICMold::ACT_AUX1));
    indexTofixture.insert(9, qMakePair<int, int>(ICMold::ACT_AUX2, ICMold::ACT_AUX2));
    indexTofixture.insert(10, qMakePair<int, int>(ICMold::ACT_AUX3, ICMold::ACT_AUX3));
    indexTofixture.insert(11, qMakePair<int, int>(ICMold::ACT_AUX4, ICMold::ACT_AUX4));

}

ICCutModuleActionPage::~ICCutModuleActionPage()
{
    delete ui;
}

void ICCutModuleActionPage::changeEvent(QEvent *e)
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

QList<ICMoldItem> ICCutModuleActionPage::CreateCommandImpl() const
{
    QList<ICMoldItem> ret;
//    ICMoldItem item;
//    item.SetDVal(0);

//    item.SetAction(ICMold::GZ);
//    item.SetActualPos(ui->zPos->TransThisTextToThisInt());
//    item.SetSVal(ui->zSpeed->TransThisTextToThisInt());
//    ret.append(item);

//    item.SetAction(ICMold::GX);
//    item.SetActualPos(ui->x1Pos->TransThisTextToThisInt());
//    item.SetSVal(ui->x1Speed->TransThisTextToThisInt());
//    ret.append(item);

//    item.SetAction(ICMold::GY);
//    item.SetActualPos(ui->y1Pos->TransThisTextToThisInt());
//    item.SetSVal(ui->y1Speed->TransThisTextToThisInt());
//    ret.append(item);

//    QPair<int, int> fixture = indexTofixture.value(ui->fixtureSel->currentIndex());
//    item.SetClip(fixture.first);
//    item.SetDVal(0);
//    item.SetIFVal(true);
//    ret.append(item);

//    item.SetClip(fixture.second);
//    item.SetDVal(ui->fixtureDelay->TransThisTextToThisInt());
//    item.SetIFVal(false);
//    ret.append(item);

//    item.SetAction(ICMold::GY);
//    item.SetActualPos(ui->y1UpPos->TransThisTextToThisInt());
//    item.SetSVal(ui->y1UpSpeed->TransThisTextToThisInt());
//    ret.append(item);

    return ret;
}

void ICCutModuleActionPage::on_setIn1_clicked()
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    ui->x1Pos->setText(QString().sprintf("%.2f", host->GetActualPos(ICVirtualHost::ICAxis_AxisX1) / 100.0));
    ui->y1Pos->setText(QString().sprintf("%.2f", host->GetActualPos(ICVirtualHost::ICAxis_AxisY1)  / 100.0));
    ui->zPos->setText(QString().sprintf("%.2f", host->GetActualPos(ICVirtualHost::ICAxis_AxisZ)  / 100.0));
}

void ICCutModuleActionPage::on_setIn2_clicked()
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    ui->y1UpPos->setText(QString().sprintf("%.2f", host->GetActualPos(ICVirtualHost::ICAxis_AxisY1)  / 100.0));
}

ICTopMoldUIItem ICCutModuleActionPage::CreateTopUIItem() const
{
    ICTopMoldUIItem topItem;
    ICMoldItem item;
    ICSubMoldUIItem subItem;
    item.SetAction(ICMold::ACTParallel);
    item.SetSubNum(255);
    topItem.SetBaseItem(item);

    item.SetSubNum(0);
    item.SetDVal(0);
    item.SetAction(ICMold::GZ);
    item.SetActualPos(ui->zPos->TransThisTextToThisInt());
    item.SetSVal(ui->zSpeed->TransThisTextToThisInt());
    subItem.SetBaseItem(item);
    topItem.AddSubMoldUIItem(subItem);

    item.SetSubNum(1);
    item.SetAction(ICMold::GX);
    item.SetActualPos(ui->x1Pos->TransThisTextToThisInt());
    item.SetSVal(ui->x1Speed->TransThisTextToThisInt());
    subItem.SetBaseItem(item);
    topItem.AddSubMoldUIItem(subItem);

    item.SetSubNum(2);
    item.SetAction(ICMold::GY);
    item.SetActualPos(ui->y1Pos->TransThisTextToThisInt());
    item.SetSVal(ui->y1Speed->TransThisTextToThisInt());
    subItem.SetBaseItem(item);
    topItem.AddSubMoldUIItem(subItem);

    item.SetSubNum(3);
    QPair<int, int> fixture = indexTofixture.value(ui->fixtureSel->currentIndex());
    item.SetClip(fixture.first);
    item.SetDVal(0);
    item.SetIFVal(true);
    subItem.SetBaseItem(item);
    topItem.AddSubMoldUIItem(subItem);

    item.SetSubNum(4);
    item.SetClip(fixture.second);
    item.SetDVal(ui->fixtureDelay->TransThisTextToThisInt());
    item.SetIFVal(false);
    subItem.SetBaseItem(item);
    topItem.AddSubMoldUIItem(subItem);

    item.SetSubNum(5);
    item.SetAction(ICMold::GY);
    item.SetActualPos(ui->y1UpPos->TransThisTextToThisInt());
    item.SetSVal(ui->y1UpSpeed->TransThisTextToThisInt());
    subItem.SetBaseItem(item);
    topItem.AddSubMoldUIItem(subItem);
    return topItem;
}
