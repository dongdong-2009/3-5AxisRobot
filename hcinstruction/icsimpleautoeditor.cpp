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

    ui->getOutletDlyX1->setValidator(&delayValidator_);
    ui->getOutletDlyY1->setValidator(&delayValidator_);
    ui->getOutletDlyZ->setValidator(&delayValidator_);
    ui->getOutletDlyX2->setValidator(&delayValidator_);
    ui->getOutletDlyY2->setValidator(&delayValidator_);

    ui->DlyBHorX1->setValidator(&delayValidator_);
    ui->DlyBHorX2->setValidator(&delayValidator_);

    ui->afterGetPosX1D->setValidator(&delayValidator_);
    ui->afterGetPosX2D->setValidator(&delayValidator_);
    ui->afterGetPosY1D->setValidator(&delayValidator_);
    ui->afterGetPosY2D->setValidator(&delayValidator_);

    ui->afterReleaseProductY1D->setValidator(&delayValidator_);
    ui->afterReleaseProductY1D_2->setValidator(&delayValidator_);
    ui->afterReleaseOutletY2D->setValidator(&delayValidator_);
    ui->afterCutOutletY1D->setValidator(&delayValidator_);

    ui->stdDlyX1->SetDecimalPlaces(2);
    ui->stdDlyY1->SetDecimalPlaces(2);
    ui->stdDlyZ->SetDecimalPlaces(2);
    ui->stdDlyX2->SetDecimalPlaces(2);
    ui->stdDlyY2->SetDecimalPlaces(2);


    ui->getProductDlyX1->SetDecimalPlaces(2);
    ui->getProductDlyY1->SetDecimalPlaces(2);
    ui->getProductDlyZ->SetDecimalPlaces(2);

    ui->getOutletDlyX1->SetDecimalPlaces(2);
    ui->getOutletDlyY1->SetDecimalPlaces(2);
    ui->getOutletDlyZ->SetDecimalPlaces(2);
    ui->getOutletDlyX2->SetDecimalPlaces(2);
    ui->getOutletDlyY2->SetDecimalPlaces(2);

    ui->DlyBHorX1->SetDecimalPlaces(2);
    ui->DlyBHorX2->SetDecimalPlaces(2);

    ui->afterGetPosX1D->SetDecimalPlaces(2);
    ui->afterGetPosX2D->SetDecimalPlaces(2);
    ui->afterGetPosY1D->SetDecimalPlaces(2);
    ui->afterGetPosY2D->SetDecimalPlaces(2);

    ui->afterReleaseProductY1D->SetDecimalPlaces(2);
    ui->afterReleaseProductY1D_2->SetDecimalPlaces(2);
    ui->afterReleaseOutletY2D->SetDecimalPlaces(2);
    ui->afterCutOutletY1D->SetDecimalPlaces(2);

//    delayEditToPosIndexMap_.insert(ui->stdDlyX1, 0);
//    delayEditToPosIndexMap_.insert(ui->stdDlyY1, 1);
//    delayEditToPosIndexMap_.insert(ui->stdDlyZ, 2);
//    delayEditToPosIndexMap_.insert(ui->stdDlyX2, 3);
//    delayEditToPosIndexMap_.insert(ui->stdDlyY2, 4);


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

ICLineEditWithVirtualNumericKeypad* CreateDlyEdit(int dly, const QValidator* v)
{
    ICLineEditWithVirtualNumericKeypad* tmp = new ICLineEditWithVirtualNumericKeypad();
    tmp->SetDecimalPlaces(0);
    tmp->setValidator(v);
    tmp->SetThisIntToThisText(dly);
    tmp->setMinimumHeight(30);
    tmp->setMaximumHeight(30);
    tmp->SetDecimalPlaces(2);

    return tmp;
}


void ICSimpleAutoEditor::AddPosHelper(QGridLayout *layout, QList<PosDlyUIWidgets> &dlyUI, const QString& posName, int defaultDly)
{
    int toInsertRow = dlyUI.size();
    PosDlyUIWidgets tmp;
    tmp.b.posName = new QLabel(QString(tr("%2-%1")).arg(toInsertRow + 1).arg(posName));
    tmp.b.posName->setMinimumWidth(ui->label_20->minimumWidth());
    tmp.b.posName->setMaximumWidth(ui->label_20->maximumWidth());
    tmp.b.x1DlyEdit = CreateDlyEdit(defaultDly, &delayValidator_);
    tmp.b.y1DlyEdit = CreateDlyEdit(defaultDly, &delayValidator_);
    tmp.b.zDlyEdit = CreateDlyEdit(defaultDly, &delayValidator_);
    tmp.b.x2DlyEdit = CreateDlyEdit(defaultDly, &delayValidator_);
    tmp.b.y2DlyEdit = CreateDlyEdit(defaultDly, &delayValidator_);
    dlyUI.append(tmp);
    for(int i = 0; i < 6; ++i)
        layout->addWidget(tmp.all[i], toInsertRow, i);
}

void ClearGirdUIHelper(QList<PosDlyUIWidgets>& uis)
{
    for(int i = 0; i < uis.size(); ++i)
    {
        PosDlyUIWidgets w = uis[i];
        w.b.posName->close();
        w.b.x1DlyEdit->close();
        w.b.y1DlyEdit->close();
        w.b.zDlyEdit->close();
        w.b.x2DlyEdit->close();
        w.b.y2DlyEdit->close();
        w.b.posName->deleteLater();
        w.b.x1DlyEdit->deleteLater();
        w.b.y1DlyEdit->deleteLater();
        w.b.zDlyEdit->deleteLater();
        w.b.x2DlyEdit->deleteLater();
        w.b.y2DlyEdit->deleteLater();
    }
    uis.clear();
}

void ICSimpleAutoEditor::showEvent(QShowEvent *e)
{
    stData_ = ICMold::CurrentMold()->GetSimpleTeachData();

    ui->stdDlyX1->SetThisIntToThisText(stData_->stdPos.b.x1D);
    ui->stdDlyY1->SetThisIntToThisText(stData_->stdPos.b.y1D);
    ui->stdDlyZ->SetThisIntToThisText(stData_->stdPos.b.zD);
    ui->stdDlyX2->SetThisIntToThisText(stData_->stdPos.b.x2D);
    ui->stdDlyY2->SetThisIntToThisText(stData_->stdPos.b.y2D);

    ui->getProductDlyX1->SetThisIntToThisText(stData_->getProductPos.pos.b.x1D);
    ui->getProductDlyY1->SetThisIntToThisText(stData_->getProductPos.pos.b.y1D);
    ui->getProductDlyZ->SetThisIntToThisText(stData_->getProductPos.pos.b.zD);

    ui->getOutletDlyX1->SetThisIntToThisText(stData_->getOutletPos.pos.b.x1D);
    ui->getOutletDlyY1->SetThisIntToThisText(stData_->getOutletPos.pos.b.y1D);
    ui->getOutletDlyZ->SetThisIntToThisText(stData_->getOutletPos.pos.b.zD);
    ui->getOutletDlyX2->SetThisIntToThisText(stData_->getOutletPos.pos.b.x2D);
    ui->getOutletDlyY2->SetThisIntToThisText(stData_->getOutletPos.pos.b.y2D);

    ui->DlyBHorX1->SetThisIntToThisText(stData_->posBH.b.x1D);
    ui->DlyBHorX2->SetThisIntToThisText(stData_->posBH.b.x2D);

    ui->afterGetPosX1D->SetThisIntToThisText(stData_->afterGetX1D);
    ui->afterGetPosX2D->SetThisIntToThisText(stData_->afterGetX2D);
    ui->afterGetPosY1D->SetThisIntToThisText(stData_->afterGetY1D);
    ui->afterGetPosY2D->SetThisIntToThisText(stData_->afterGetY2D);

    ui->afterReleaseProductY1D->SetThisIntToThisText(stData_->releaseProductYUpD);
    ui->afterReleaseOutletY2D->SetThisIntToThisText(stData_->releaseOutletYUpD);
    ui->afterCutOutletY1D->SetThisIntToThisText(stData_->cutOutletYUpD);
    ui->afterReleaseProductY1D_2->SetThisIntToThisText(stData_->releaseOutletYUpD);

    ClearGirdUIHelper(releaseProductDlyUI);
    for(int i = 0; i < stData_->releaseProductPosList.size(); ++i)
    {
        ReleasePosData posData = stData_->releaseProductPosList.at(i);
        AddPosHelper(ui->releaseProductDlyGroup, releaseProductDlyUI, tr("Rel Product"));
        PosDlyUIWidgets tmp = releaseProductDlyUI.last();
        tmp.b.x1DlyEdit->SetThisIntToThisText(posData.pos.b.x1D);
        tmp.b.y1DlyEdit->SetThisIntToThisText(posData.pos.b.y1D);
        tmp.b.zDlyEdit->SetThisIntToThisText(posData.pos.b.zD);
        tmp.b.x2DlyEdit->SetThisIntToThisText(posData.pos.b.x2D);
        tmp.b.y2DlyEdit->SetThisIntToThisText(posData.pos.b.y2D);
    }

    ClearGirdUIHelper(releaseOutletDlyUI);
    for(int i = 0; i < stData_->releaseOutletPosList.size(); ++i)
    {
        ReleasePosData posData = stData_->releaseOutletPosList.at(i);
        AddPosHelper(ui->releaseOutletDlyGroup, releaseOutletDlyUI, tr("Rel Outlet"));
        PosDlyUIWidgets tmp = releaseOutletDlyUI.last();
        tmp.b.x1DlyEdit->SetThisIntToThisText(posData.pos.b.x1D);
        tmp.b.y1DlyEdit->SetThisIntToThisText(posData.pos.b.y1D);
        tmp.b.zDlyEdit->SetThisIntToThisText(posData.pos.b.zD);
        tmp.b.x2DlyEdit->SetThisIntToThisText(posData.pos.b.x2D);
        tmp.b.y2DlyEdit->SetThisIntToThisText(posData.pos.b.y2D);
    }

    ClearGirdUIHelper(cutOutletDlyUI);
    for(int i = 0; i < stData_->cutOutletPosList.size(); ++i)
    {
        ReleasePosData posData = stData_->cutOutletPosList.at(i);
        AddPosHelper(ui->cutOutletDlyGroup, cutOutletDlyUI, tr("Cut Outlet"));
        PosDlyUIWidgets tmp = cutOutletDlyUI.last();
        tmp.b.x1DlyEdit->SetThisIntToThisText(posData.pos.b.x1D);
        tmp.b.y1DlyEdit->SetThisIntToThisText(posData.pos.b.y1D);
        tmp.b.zDlyEdit->SetThisIntToThisText(posData.pos.b.zD);
        tmp.b.x2DlyEdit->SetThisIntToThisText(posData.pos.b.x2D);
        tmp.b.y2DlyEdit->SetThisIntToThisText(posData.pos.b.y2D);
    }

    SetMainArmPosEnabled(UsedMainArm());
    SetSubArmPosEnabled(stData_->usedSubArm);
    SetReleaseProductEnabled(stData_->usedMainArm);
    SetReleaseOutletEnabled(UsedReleaseOutlet());
    SetCutOutletEnabled(stData_->usedCutOutlet);

    QDialog::showEvent(e);
}

void ICSimpleAutoEditor::SetMainArmPosEnabled(bool en)
{
    ui->label_27->setVisible(en && stData_->usedMainArm);
    ui->afterReleaseProductY1D->setVisible(en && stData_->usedMainArm);

    ui->label_21->setVisible(en && stData_->usedMainArm);
    ui->getProductDlyX1->setVisible(en && stData_->usedMainArm);
    ui->getProductDlyY1->setVisible(en && stData_->usedMainArm);
    ui->getProductDlyZ->setVisible(en && stData_->usedMainArm);


    ui->afterGetPosX1D->setVisible(en);
    ui->afterGetPosY1D->setVisible(en);
    ui->stdDlyX1->setVisible(en);
    ui->stdDlyY1->setVisible(en);
    ui->getProductDlyX1->setVisible(stData_->usedMainArm);
    ui->getProductDlyY1->setVisible(stData_->usedMainArm);
    ui->getOutletDlyX1->setVisible(en && UsedReleaseOutlet());
    ui->getOutletDlyY1->setVisible(en && UsedReleaseOutlet());
    ui->DlyBHorX1->setVisible(en);

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
    ui->afterGetPosY2D->setVisible(en);
    ui->afterReleaseOutletY2D->setVisible(en);

    ui->stdDlyX2->setVisible(en);
    ui->stdDlyY2->setVisible(en);
    ui->getOutletDlyX2->setVisible(en);
    ui->getOutletDlyY2->setVisible(en);
    ui->DlyBHorX2->setVisible(en);

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

    ui->getOutletDlyX1->setEnabled(en && stData_->usedMainArmOutlet);
    ui->getOutletDlyY1->setEnabled(en && stData_->usedMainArmOutlet);
    ui->getOutletDlyX1->setEchoMode(en && stData_->usedMainArmOutlet ? QLineEdit::Normal : QLineEdit::Password);
    ui->getOutletDlyY1->setEchoMode(en && stData_->usedMainArmOutlet ? QLineEdit::Normal : QLineEdit::Password);
    ui->getOutletDlyX2->setVisible(en && UsedSubArm());
    ui->getOutletDlyY2->setVisible(en && UsedSubArm());
    ui->getOutletDlyZ->setVisible(en);
    ui->getOutletDlyZ->setEnabled(en && !stData_->usedMainArm);
    ui->getOutletDlyZ->setEchoMode(ui->getOutletDlyZ->isEnabled() ? QLineEdit::Normal : QLineEdit::Password);
    ui->label_22->setVisible(en);
    ui->label_28->setVisible(en);
    ui->afterReleaseProductY1D_2->setVisible(en && stData_->usedMainArmOutlet);


    for(int i = 0; i < releaseOutletDlyUI.size(); ++i)
    {
        releaseOutletDlyUI[i].b.posName->setVisible(en);
        releaseOutletDlyUI[i].b.x1DlyEdit->setEnabled(en && stData_->usedMainArmOutlet);
        releaseOutletDlyUI[i].b.y1DlyEdit->setEnabled(en && stData_->usedMainArmOutlet);
        releaseOutletDlyUI[i].b.x1DlyEdit->setEchoMode(en && stData_->usedMainArmOutlet ? QLineEdit::Normal : QLineEdit::Password);
        releaseOutletDlyUI[i].b.y1DlyEdit->setEchoMode(en && stData_->usedMainArmOutlet ? QLineEdit::Normal : QLineEdit::Password);
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
    ui->label->setVisible(en);
    ui->getOutletDlyZ->setEnabled(!en);
    ui->getOutletDlyZ->setEchoMode(ui->getOutletDlyZ->isEnabled() ? QLineEdit::Normal : QLineEdit::Password);

    for(int i = 0; i < releaseProductDlyUI.size(); ++i)
    {
        releaseProductDlyUI[i].b.posName->setVisible(en);
        releaseProductDlyUI[i].b.x1DlyEdit->setVisible(en);
        releaseProductDlyUI[i].b.y1DlyEdit->setVisible(en);
        releaseProductDlyUI[i].b.zDlyEdit->setVisible(en);
        releaseProductDlyUI[i].b.x2DlyEdit->setEnabled(false);
        releaseProductDlyUI[i].b.y2DlyEdit->setEnabled(false);
        releaseProductDlyUI[i].b.x2DlyEdit->setEchoMode(QLineEdit::Password);
        releaseProductDlyUI[i].b.y2DlyEdit->setEchoMode(QLineEdit::Password);



    }
}

void ICSimpleAutoEditor::SetCutOutletEnabled(bool en)
{
    ui->label_29->setVisible(en);
    ui->afterCutOutletY1D->setVisible(en && stData_->usedMainArm);
    for(int i = 0; i < cutOutletDlyUI.size(); ++i)
    {
        cutOutletDlyUI[i].b.posName->setVisible(en);
        cutOutletDlyUI[i].b.x1DlyEdit->setVisible(en);
        cutOutletDlyUI[i].b.y1DlyEdit->setVisible(en);
        cutOutletDlyUI[i].b.zDlyEdit->setVisible(en);
        cutOutletDlyUI[i].b.x2DlyEdit->setEnabled(false);
        cutOutletDlyUI[i].b.y2DlyEdit->setEnabled(false);
        cutOutletDlyUI[i].b.x2DlyEdit->setEchoMode(QLineEdit::Password);
        cutOutletDlyUI[i].b.y2DlyEdit->setEchoMode(QLineEdit::Password);
    }
}

void ICSimpleAutoEditor::on_cancelButton_clicked()
{
    this->reject();
}

void CheckModifyHelper(ICLineEditWithVirtualNumericKeypad* editor, quint32* delayAddr, QMap<int, int> & ret,
                       const SimpleTeachData* stData)
{
    if(editor->TransThisTextToThisInt() != *delayAddr)
    {
        *delayAddr = editor->TransThisTextToThisInt();
        QList<int> line = stData->GetEditorLine(delayAddr);
        for(int i = 0; i < line.size(); ++i)
        {
            ret.insert(line.at(i), *delayAddr);
        }
    }
}

void ICSimpleAutoEditor::on_okButton_clicked()
{
    modifiedDelays.clear();

    CheckModifyHelper(ui->stdDlyX1, &stData_->stdPos.b.x1D, modifiedDelays, stData_);
    CheckModifyHelper(ui->stdDlyY1, &stData_->stdPos.b.y1D, modifiedDelays, stData_);
    CheckModifyHelper(ui->stdDlyZ, &stData_->stdPos.b.zD, modifiedDelays, stData_);
    CheckModifyHelper(ui->stdDlyX2, &stData_->stdPos.b.x2D, modifiedDelays, stData_);
    CheckModifyHelper(ui->stdDlyY2, &stData_->stdPos.b.y2D, modifiedDelays, stData_);

    CheckModifyHelper(ui->getProductDlyX1, &stData_->getProductPos.pos.b.x1D, modifiedDelays, stData_);
    CheckModifyHelper(ui->getProductDlyY1, &stData_->getProductPos.pos.b.y1D, modifiedDelays, stData_);
    CheckModifyHelper(ui->getProductDlyZ, &stData_->getProductPos.pos.b.zD, modifiedDelays, stData_);

    CheckModifyHelper(ui->getOutletDlyX1, &stData_->getOutletPos.pos.b.x1D, modifiedDelays, stData_);
    CheckModifyHelper(ui->getOutletDlyY1, &stData_->getOutletPos.pos.b.y1D, modifiedDelays, stData_);
    CheckModifyHelper(ui->getOutletDlyZ, &stData_->getOutletPos.pos.b.zD, modifiedDelays, stData_);
    CheckModifyHelper(ui->getOutletDlyX2, &stData_->getOutletPos.pos.b.x2D, modifiedDelays, stData_);
    CheckModifyHelper(ui->getOutletDlyY2, &stData_->getOutletPos.pos.b.y2D, modifiedDelays, stData_);

    CheckModifyHelper(ui->DlyBHorX1, &stData_->posBH.b.x1D, modifiedDelays, stData_);
    CheckModifyHelper(ui->DlyBHorX2, &stData_->posBH.b.x2D, modifiedDelays, stData_);

    CheckModifyHelper(ui->afterGetPosX1D, &stData_->afterGetX1D, modifiedDelays, stData_);
    CheckModifyHelper(ui->afterGetPosX2D, &stData_->afterGetX2D, modifiedDelays, stData_);
    CheckModifyHelper(ui->afterGetPosY1D, &stData_->afterGetY1D, modifiedDelays, stData_);
    CheckModifyHelper(ui->afterGetPosY2D, &stData_->afterGetY2D, modifiedDelays, stData_);
    CheckModifyHelper(ui->afterReleaseProductY1D, &stData_->releaseProductYUpD, modifiedDelays, stData_);
    CheckModifyHelper(ui->afterCutOutletY1D, &stData_->cutOutletYUpD, modifiedDelays, stData_);
    if(stData_->usedSubArm)
        CheckModifyHelper(ui->afterReleaseOutletY2D, &stData_->releaseOutletYUpD, modifiedDelays, stData_);
    if(stData_->usedMainArmOutlet)
        CheckModifyHelper(ui->afterReleaseProductY1D_2, &stData_->releaseOutletYUpD, modifiedDelays, stData_);

    for(int i = 0; i < releaseProductDlyUI.size(); ++i)
    {
        PosDlyUIWidgets ws = releaseProductDlyUI.at(i);
        CheckModifyHelper(ws.b.x1DlyEdit, &stData_->releaseProductPosList[i].pos.b.x1D, modifiedDelays, stData_);
        CheckModifyHelper(ws.b.y1DlyEdit, &stData_->releaseProductPosList[i].pos.b.y1D, modifiedDelays, stData_);
        CheckModifyHelper(ws.b.zDlyEdit, &stData_->releaseProductPosList[i].pos.b.zD, modifiedDelays, stData_);
        CheckModifyHelper(ws.b.x2DlyEdit, &stData_->releaseProductPosList[i].pos.b.x2D, modifiedDelays, stData_);
        CheckModifyHelper(ws.b.y2DlyEdit, &stData_->releaseProductPosList[i].pos.b.y2D, modifiedDelays, stData_);
    }

    for(int i = 0; i < releaseOutletDlyUI.size(); ++i)
    {
        PosDlyUIWidgets ws = releaseOutletDlyUI.at(i);
        CheckModifyHelper(ws.b.x1DlyEdit, &stData_->releaseOutletPosList[i].pos.b.x1D, modifiedDelays, stData_);
        CheckModifyHelper(ws.b.y1DlyEdit, &stData_->releaseOutletPosList[i].pos.b.y1D, modifiedDelays, stData_);
        CheckModifyHelper(ws.b.zDlyEdit, &stData_->releaseOutletPosList[i].pos.b.zD, modifiedDelays, stData_);
        CheckModifyHelper(ws.b.x2DlyEdit, &stData_->releaseOutletPosList[i].pos.b.x2D, modifiedDelays, stData_);
        CheckModifyHelper(ws.b.y2DlyEdit, &stData_->releaseOutletPosList[i].pos.b.y2D, modifiedDelays, stData_);
    }

    for(int i = 0; i < cutOutletDlyUI.size(); ++i)
    {
        PosDlyUIWidgets ws = cutOutletDlyUI.at(i);
        CheckModifyHelper(ws.b.x1DlyEdit, &stData_->cutOutletPosList[i].pos.b.x1D, modifiedDelays, stData_);
        CheckModifyHelper(ws.b.y1DlyEdit, &stData_->cutOutletPosList[i].pos.b.y1D, modifiedDelays, stData_);
        CheckModifyHelper(ws.b.zDlyEdit, &stData_->cutOutletPosList[i].pos.b.zD, modifiedDelays, stData_);
        CheckModifyHelper(ws.b.x2DlyEdit, &stData_->cutOutletPosList[i].pos.b.x2D, modifiedDelays, stData_);
        CheckModifyHelper(ws.b.y2DlyEdit, &stData_->cutOutletPosList[i].pos.b.y2D, modifiedDelays, stData_);
    }


    this->accept();
}

void ICSimpleAutoEditor::keyPressEvent(QKeyEvent *e)
{
    QKeyEvent* ke = new QKeyEvent(*e);
    qApp->postEvent(this->parentWidget(), ke);
    this->reject();
}
