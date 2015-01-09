#include "hcdefineposframe.h"
#include "ui_hcdefineposframe.h"
#include "icmold.h"
#include "icvirtualhost.h"

QList<QList<QWidget*> > widgets;
HCDefinePosFrame::HCDefinePosFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::HCDefinePosFrame)
{
    ui->setupUi(this);
    widgets    <<(QList<QWidget*>()<<ui->p1C<<ui->p2C<<ui->p3C)
            <<(QList<QWidget*>()<<ui->p1X1<<ui->p2X1<<ui->p3X1)
          <<(QList<QWidget*>()<<ui->p1Y1<<ui->p2Y1<<ui->p3Y1)
         <<(QList<QWidget*>()<<ui->p1Z<<ui->p2Z<<ui->p3Z)
        <<(QList<QWidget*>()<<ui->p1X2<<ui->p2X2<<ui->p3X2)
       <<(QList<QWidget*>()<<ui->p1Y2<<ui->p2Y2<<ui->p3Y2)
      <<(QList<QWidget*>()<<ui->p1A<<ui->p2A<<ui->p3A)
     <<(QList<QWidget*>()<<ui->p1B<<ui->p2B<<ui->p3B);

    ICLineEditWithVirtualNumericKeypad* edit;
    QIntValidator* v= new  QIntValidator(0, 65530, this);
    for(int i = 0; i != widgets.size(); ++i)
    {
        for(int j = 0; j != widgets.at(i).size(); ++j)
        {
            edit = qobject_cast<ICLineEditWithVirtualNumericKeypad*>(widgets[i][j]);
            edit->SetDecimalPlaces(1);
            edit->setValidator(v);
        }
    }
}

HCDefinePosFrame::~HCDefinePosFrame()
{
    delete ui;
}

void HCDefinePosFrame::changeEvent(QEvent *e)
{
    QFrame::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void HCDefinePosFrame::showEvent(QShowEvent *e)
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    bool isVis = host->AxisDefine(ICVirtualHost::ICAxis_AxisX1) == ICVirtualHost::ICAxisDefine_Servo;
    ui->p1X1->setVisible(isVis);
    ui->p1X1Label->setVisible(isVis);
    ui->p1X1mm->setVisible(isVis);
    ui->p2X1->setVisible(isVis);
    ui->p2X1Label->setVisible(isVis);
    ui->p2X1mm->setVisible(isVis);
    ui->p3X1->setVisible(isVis);
    ui->p3X1Label->setVisible(isVis);
    ui->p3X1mm->setVisible(isVis);

    isVis = host->AxisDefine(ICVirtualHost::ICAxis_AxisY1) == ICVirtualHost::ICAxisDefine_Servo;
    ui->p1Y1->setVisible(isVis);
    ui->p1Y1Label->setVisible(isVis);
    ui->p1Y1mm->setVisible(isVis);
    ui->p2Y1->setVisible(isVis);
    ui->p2Y1Label->setVisible(isVis);
    ui->p2Y1mm->setVisible(isVis);
    ui->p3Y1->setVisible(isVis);
    ui->p3Y1Label->setVisible(isVis);
    ui->p3Y1mm->setVisible(isVis);

    isVis = host->AxisDefine(ICVirtualHost::ICAxis_AxisZ) == ICVirtualHost::ICAxisDefine_Servo;
    ui->p1Z->setVisible(isVis);
    ui->p1ZLabel->setVisible(isVis);
    ui->p1Zmm->setVisible(isVis);
    ui->p2Z->setVisible(isVis);
    ui->p2ZLabel->setVisible(isVis);
    ui->p2Zmm->setVisible(isVis);
    ui->p3Z->setVisible(isVis);
    ui->p3ZLabel->setVisible(isVis);
    ui->p3Zmm->setVisible(isVis);

    isVis = host->AxisDefine(ICVirtualHost::ICAxis_AxisX2) == ICVirtualHost::ICAxisDefine_Servo;
    ui->p1X2->setVisible(isVis);
    ui->p1X2Label->setVisible(isVis);
    ui->p1X2mm->setVisible(isVis);
    ui->p2X2->setVisible(isVis);
    ui->p2X2Label->setVisible(isVis);
    ui->p2X2mm->setVisible(isVis);
    ui->p3X2->setVisible(isVis);
    ui->p3X2Label->setVisible(isVis);
    ui->p3X2mm->setVisible(isVis);

    isVis = host->AxisDefine(ICVirtualHost::ICAxis_AxisY2) == ICVirtualHost::ICAxisDefine_Servo;
    ui->p1Y2->setVisible(isVis);
    ui->p1Y2Label->setVisible(isVis);
    ui->p1Y2mm->setVisible(isVis);
    ui->p2Y2->setVisible(isVis);
    ui->p2Y2Label->setVisible(isVis);
    ui->p2Y2mm->setVisible(isVis);
    ui->p3Y2->setVisible(isVis);
    ui->p3Y2Label->setVisible(isVis);
    ui->p3Y2mm->setVisible(isVis);

    isVis = host->AxisDefine(ICVirtualHost::ICAxis_AxisA) == ICVirtualHost::ICAxisDefine_Servo;
    ui->p1A->setVisible(isVis);
    ui->p1ALabel->setVisible(isVis);
    ui->p1Amm->setVisible(isVis);
    ui->p2A->setVisible(isVis);
    ui->p2ALabel->setVisible(isVis);
    ui->p2Amm->setVisible(isVis);
    ui->p3A->setVisible(isVis);
    ui->p3ALabel->setVisible(isVis);
    ui->p3Amm->setVisible(isVis);

    isVis = host->AxisDefine(ICVirtualHost::ICAxis_AxisB) == ICVirtualHost::ICAxisDefine_Servo;
    ui->p1B->setVisible(isVis);
    ui->p1BLabel->setVisible(isVis);
    ui->p1Bmm->setVisible(isVis);
    ui->p2B->setVisible(isVis);
    ui->p2BLabel->setVisible(isVis);
    ui->p2Bmm->setVisible(isVis);
    ui->p3B->setVisible(isVis);
    ui->p3BLabel->setVisible(isVis);
    ui->p3Bmm->setVisible(isVis);

    isVis = host->AxisDefine(ICVirtualHost::ICAxis_AxisC) == ICVirtualHost::ICAxisDefine_Servo;
    ui->p1C->setVisible(isVis);
    ui->p1CLabel->setVisible(isVis);
    ui->p1Cmm->setVisible(isVis);
    ui->p2C->setVisible(isVis);
    ui->p2CLabel->setVisible(isVis);
    ui->p2Cmm->setVisible(isVis);
    ui->p3C->setVisible(isVis);
    ui->p3CLabel->setVisible(isVis);
    ui->p3Cmm->setVisible(isVis);
    ICMold *mold = ICMold::CurrentMold();
    ICLineEditWithVirtualNumericKeypad* edit;
    int p = ICMold::DefinePosStart;
    for(int i = 0; i != widgets.size(); ++i)
    {
        p = ICMold::DefinePosStart + i;
        for(int j = 0; j != widgets.at(i).size(); ++j)
        {
            edit = qobject_cast<ICLineEditWithVirtualNumericKeypad*>(widgets[i][j]);
            edit->SetThisIntToThisText(mold->DefinePos((ICMold::ICDefinePos)(p)));
            p += 8;
        }

    }
    QFrame::showEvent(e);
}

void HCDefinePosFrame::hideEvent(QHideEvent *e)
{
    ICMold *mold = ICMold::CurrentMold();
    ICLineEditWithVirtualNumericKeypad* edit;
    int p = ICMold::DefinePosStart;
    for(int i = 0; i != widgets.size(); ++i)
    {
        p = ICMold::DefinePosStart + i;
        for(int j = 0; j != widgets.at(i).size(); ++j)
        {
            edit = qobject_cast<ICLineEditWithVirtualNumericKeypad*>(widgets[i][j]);
            mold->SetDefinePos((ICMold::ICDefinePos)(p), edit->TransThisTextToThisInt());
            p += 8;
        }
    }
    mold->UpdateSyncSum();
    mold->SaveMoldParamsFile();
    ICVirtualHost::GlobalVirtualHost()->ReConfigure();
    QFrame::hideEvent(e);
}

void HCDefinePosFrame::on_setInPos1_clicked()
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    ui->p1X1->SetThisIntToThisText(host->HostStatus(ICVirtualHost::XPos).toInt());
    ui->p1Y1->SetThisIntToThisText(host->HostStatus(ICVirtualHost::YPos).toInt());
    ui->p1Z->SetThisIntToThisText(host->HostStatus(ICVirtualHost::ZPos).toInt());
    ui->p1X2->SetThisIntToThisText(host->HostStatus(ICVirtualHost::PPos).toInt());
    ui->p1Y2->SetThisIntToThisText(host->HostStatus(ICVirtualHost::QPos).toInt());
    ui->p1A->SetThisIntToThisText(host->HostStatus(ICVirtualHost::APos).toInt());
    ui->p1B->SetThisIntToThisText(host->HostStatus(ICVirtualHost::BPos).toInt());
    ui->p1C->SetThisIntToThisText(host->HostStatus(ICVirtualHost::CPos).toInt());
}

void HCDefinePosFrame::on_setInPos2_clicked()
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    ui->p2X1->SetThisIntToThisText(host->HostStatus(ICVirtualHost::XPos).toInt());
    ui->p2Y1->SetThisIntToThisText(host->HostStatus(ICVirtualHost::YPos).toInt());
    ui->p2Z->SetThisIntToThisText(host->HostStatus(ICVirtualHost::ZPos).toInt());
    ui->p2X2->SetThisIntToThisText(host->HostStatus(ICVirtualHost::PPos).toInt());
    ui->p2Y2->SetThisIntToThisText(host->HostStatus(ICVirtualHost::QPos).toInt());
    ui->p2A->SetThisIntToThisText(host->HostStatus(ICVirtualHost::APos).toInt());
    ui->p2B->SetThisIntToThisText(host->HostStatus(ICVirtualHost::BPos).toInt());
    ui->p2C->SetThisIntToThisText(host->HostStatus(ICVirtualHost::CPos).toInt());
}

void HCDefinePosFrame::on_setInPos3_clicked()
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    ui->p3X1->SetThisIntToThisText(host->HostStatus(ICVirtualHost::XPos).toInt());
    ui->p3Y1->SetThisIntToThisText(host->HostStatus(ICVirtualHost::YPos).toInt());
    ui->p3Z->SetThisIntToThisText(host->HostStatus(ICVirtualHost::ZPos).toInt());
    ui->p3X2->SetThisIntToThisText(host->HostStatus(ICVirtualHost::PPos).toInt());
    ui->p3Y2->SetThisIntToThisText(host->HostStatus(ICVirtualHost::QPos).toInt());
    ui->p3A->SetThisIntToThisText(host->HostStatus(ICVirtualHost::APos).toInt());
    ui->p3B->SetThisIntToThisText(host->HostStatus(ICVirtualHost::BPos).toInt());
    ui->p3C->SetThisIntToThisText(host->HostStatus(ICVirtualHost::CPos).toInt());
}
