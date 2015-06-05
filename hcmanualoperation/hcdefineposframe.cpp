#include "hcdefineposframe.h"
#include "ui_hcdefineposframe.h"
#include "icmold.h"
#include "icvirtualhost.h"
#include "icprogramheadframe.h"

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
    ICMold *mold = ICMold::CurrentMold();
    int p = ICMold::DefinePosStart;
    for(int i = 0; i != widgets.size(); ++i)
    {
        p = ICMold::DefinePosStart + i;
        for(int j = 0; j != widgets.at(i).size(); ++j)
        {
            edit = qobject_cast<ICLineEditWithVirtualNumericKeypad*>(widgets[i][j]);
            edit->SetDecimalPlaces(1);
            edit->setValidator(v);
//            edit = qobject_cast<ICLineEditWithVirtualNumericKeypad*>(widgets[i][j]);
            edit->SetThisIntToThisText(mold->DefinePos((ICMold::ICDefinePos)(p)));
            p += 8;
        }
    }
    connect(ICProgramHeadFrame::Instance(),
            SIGNAL(LevelChanged(int)),
            this,
            SLOT(OnLevelChanged(int)));

//    oldStyle_ = ui->p1X1->styleSheet();
//    newStyle_ =
//            "border: 2px solid gray;
//            border-radius: 6px;
//            padding: 0 4px;
//            /*background: rgb(79, 223, 255);
//    ICLineEditWithVirtualNumericKeypad* edit;
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
    ui->setInPos1_1->setVisible(isVis);
    ui->setInPos2_1->setVisible(isVis);
    ui->setInPos3_1->setVisible(isVis);



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
    ui->setInPos1_2->setVisible(isVis);
    ui->setInPos2_2->setVisible(isVis);
    ui->setInPos3_2->setVisible(isVis);

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
    ui->setInPos1_3->setVisible(isVis);
    ui->setInPos2_3->setVisible(isVis);
    ui->setInPos3_3->setVisible(isVis);

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
    ui->setInPos1_4->setVisible(isVis);
    ui->setInPos2_4->setVisible(isVis);
    ui->setInPos3_4->setVisible(isVis);

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
    ui->setInPos1_5->setVisible(isVis);
    ui->setInPos2_5->setVisible(isVis);
    ui->setInPos3_5->setVisible(isVis);

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
    ui->setInPos1_6->setVisible(isVis);
    ui->setInPos2_6->setVisible(isVis);
    ui->setInPos3_6->setVisible(isVis);

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
    ui->setInPos1_7->setVisible(isVis);
    ui->setInPos2_7->setVisible(isVis);
    ui->setInPos3_7->setVisible(isVis);

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
    ui->setInPos1_8->setVisible(isVis);
    ui->setInPos2_8->setVisible(isVis);
    ui->setInPos3_8->setVisible(isVis);
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

    OnLevelChanged(ICProgramHeadFrame::Instance()->CurrentLevel());
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

void HCDefinePosFrame::on_setInPos1_1_clicked()
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    ui->p1X1->SetThisIntToThisText(host->HostStatus(ICVirtualHost::XPos).toInt());

    ui->p1X1->selectAll();
    QTimer::singleShot(2000, this, SLOT(ClearSelection1()));
}
void HCDefinePosFrame::on_setInPos1_2_clicked()
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    ui->p1Y1->SetThisIntToThisText(host->HostStatus(ICVirtualHost::YPos).toInt());

    ui->p1Y1->selectAll();
    QTimer::singleShot(2000, this, SLOT(ClearSelection1()));
}
void HCDefinePosFrame::on_setInPos1_3_clicked()
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    ui->p1Z->SetThisIntToThisText(host->HostStatus(ICVirtualHost::ZPos).toInt());

    ui->p1Z->selectAll();
    QTimer::singleShot(2000, this, SLOT(ClearSelection1()));
}
void HCDefinePosFrame::on_setInPos1_4_clicked()
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    ui->p1X2->SetThisIntToThisText(host->HostStatus(ICVirtualHost::PPos).toInt());

    ui->p1X2->selectAll();
    QTimer::singleShot(2000, this, SLOT(ClearSelection1()));
}
void HCDefinePosFrame::on_setInPos1_5_clicked()
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    ui->p1Y2->SetThisIntToThisText(host->HostStatus(ICVirtualHost::QPos).toInt());

    ui->p1Y2->selectAll();
    QTimer::singleShot(2000, this, SLOT(ClearSelection1()));
}
void HCDefinePosFrame::on_setInPos1_6_clicked()
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    ui->p1A->SetThisIntToThisText(host->HostStatus(ICVirtualHost::APos).toInt());

    ui->p1A->selectAll();
    QTimer::singleShot(2000, this, SLOT(ClearSelection1()));
}
void HCDefinePosFrame::on_setInPos1_7_clicked()
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    ui->p1B->SetThisIntToThisText(host->HostStatus(ICVirtualHost::BPos).toInt());

    ui->p1B->selectAll();
    QTimer::singleShot(2000, this, SLOT(ClearSelection1()));
}
void HCDefinePosFrame::on_setInPos1_8_clicked()
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    ui->p1C->SetThisIntToThisText(host->HostStatus(ICVirtualHost::CPos).toInt());

    ui->p1C->selectAll();
    QTimer::singleShot(2000, this, SLOT(ClearSelection1()));
}

void HCDefinePosFrame::on_setInPos2_1_clicked()
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    ui->p2X1->SetThisIntToThisText(host->HostStatus(ICVirtualHost::XPos).toInt());

    ui->p2X1->selectAll();
    QTimer::singleShot(2000, this, SLOT(ClearSelection1()));
}
void HCDefinePosFrame::on_setInPos2_2_clicked()
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    ui->p2Y1->SetThisIntToThisText(host->HostStatus(ICVirtualHost::YPos).toInt());

    ui->p2Y1->selectAll();
    QTimer::singleShot(2000, this, SLOT(ClearSelection1()));
}
void HCDefinePosFrame::on_setInPos2_3_clicked()
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    ui->p2Z->SetThisIntToThisText(host->HostStatus(ICVirtualHost::ZPos).toInt());

    ui->p2Z->selectAll();
    QTimer::singleShot(2000, this, SLOT(ClearSelection1()));
}
void HCDefinePosFrame::on_setInPos2_4_clicked()
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    ui->p2X2->SetThisIntToThisText(host->HostStatus(ICVirtualHost::PPos).toInt());

    ui->p2X2->selectAll();
    QTimer::singleShot(2000, this, SLOT(ClearSelection1()));
}
void HCDefinePosFrame::on_setInPos2_5_clicked()
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    ui->p2Y2->SetThisIntToThisText(host->HostStatus(ICVirtualHost::QPos).toInt());

    ui->p2Y2->selectAll();
    QTimer::singleShot(2000, this, SLOT(ClearSelection1()));
}
void HCDefinePosFrame::on_setInPos2_6_clicked()
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    ui->p2A->SetThisIntToThisText(host->HostStatus(ICVirtualHost::APos).toInt());

    ui->p2A->selectAll();
    QTimer::singleShot(2000, this, SLOT(ClearSelection1()));
}
void HCDefinePosFrame::on_setInPos2_7_clicked()
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    ui->p2B->SetThisIntToThisText(host->HostStatus(ICVirtualHost::BPos).toInt());

    ui->p2B->selectAll();
    QTimer::singleShot(2000, this, SLOT(ClearSelection1()));
}
void HCDefinePosFrame::on_setInPos2_8_clicked()
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    ui->p2C->SetThisIntToThisText(host->HostStatus(ICVirtualHost::CPos).toInt());

    ui->p2C->selectAll();
    QTimer::singleShot(2000, this, SLOT(ClearSelection1()));
}

void HCDefinePosFrame::on_setInPos3_1_clicked()
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    ui->p3X1->SetThisIntToThisText(host->HostStatus(ICVirtualHost::XPos).toInt());

    ui->p3X1->selectAll();
    QTimer::singleShot(2000, this, SLOT(ClearSelection1()));
}
void HCDefinePosFrame::on_setInPos3_2_clicked()
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    ui->p3Y1->SetThisIntToThisText(host->HostStatus(ICVirtualHost::YPos).toInt());

    ui->p3Y1->selectAll();
    QTimer::singleShot(2000, this, SLOT(ClearSelection1()));
}
void HCDefinePosFrame::on_setInPos3_3_clicked()
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    ui->p3Z->SetThisIntToThisText(host->HostStatus(ICVirtualHost::ZPos).toInt());

    ui->p3Z->selectAll();
    QTimer::singleShot(2000, this, SLOT(ClearSelection1()));
}
void HCDefinePosFrame::on_setInPos3_4_clicked()
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    ui->p3X2->SetThisIntToThisText(host->HostStatus(ICVirtualHost::PPos).toInt());

    ui->p3X2->selectAll();
    QTimer::singleShot(2000, this, SLOT(ClearSelection1()));
}
void HCDefinePosFrame::on_setInPos3_5_clicked()
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    ui->p3Y2->SetThisIntToThisText(host->HostStatus(ICVirtualHost::QPos).toInt());

    ui->p3Y2->selectAll();
    QTimer::singleShot(2000, this, SLOT(ClearSelection1()));
}
void HCDefinePosFrame::on_setInPos3_6_clicked()
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    ui->p3A->SetThisIntToThisText(host->HostStatus(ICVirtualHost::APos).toInt());

    ui->p3A->selectAll();
    QTimer::singleShot(2000, this, SLOT(ClearSelection1()));
}
void HCDefinePosFrame::on_setInPos3_7_clicked()
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    ui->p3B->SetThisIntToThisText(host->HostStatus(ICVirtualHost::BPos).toInt());

    ui->p3B->selectAll();
    QTimer::singleShot(2000, this, SLOT(ClearSelection1()));
}
void HCDefinePosFrame::on_setInPos3_8_clicked()
{
    ICVirtualHost* host = ICVirtualHost::GlobalVirtualHost();
    ui->p3C->SetThisIntToThisText(host->HostStatus(ICVirtualHost::CPos).toInt());

    ui->p3C->selectAll();
    QTimer::singleShot(2000, this, SLOT(ClearSelection1()));
}


void HCDefinePosFrame::OnLevelChanged(int level)
{
    setEnabled(level >= 1);
}

void HCDefinePosFrame::ClearSelection1()
{
    ui->p1X1->deselect();
    ui->p1Y1->deselect();
    ui->p1Z->deselect();
    ui->p1X2->deselect();
    ui->p1Y2->deselect();
    ui->p1A->deselect();
    ui->p1B->deselect();
    ui->p1B->deselect();
    ui->p2X1->deselect();
    ui->p2Y1->deselect();
    ui->p2Z->deselect();
    ui->p2X2->deselect();
    ui->p2Y2->deselect();
    ui->p2A->deselect();
    ui->p2B->deselect();
    ui->p2B->deselect();
    ui->p3X1->deselect();
    ui->p3Y1->deselect();
    ui->p3Z->deselect();
    ui->p3X2->deselect();
    ui->p3Y2->deselect();
    ui->p3A->deselect();
    ui->p3B->deselect();
    ui->p3B->deselect();
}

void HCDefinePosFrame::ClearSelection2()
{
    ui->p2X1->deselect();
    ui->p2Y1->deselect();
    ui->p2Z->deselect();
    ui->p2X2->deselect();
    ui->p2Y2->deselect();
    ui->p2A->deselect();
    ui->p2B->deselect();
    ui->p2B->deselect();
}

void HCDefinePosFrame::ClearSelection3()
{
    ui->p3X1->deselect();
    ui->p3Y1->deselect();
    ui->p3Z->deselect();
    ui->p3X2->deselect();
    ui->p3Y2->deselect();
    ui->p3A->deselect();
    ui->p3B->deselect();
    ui->p3B->deselect();
}
