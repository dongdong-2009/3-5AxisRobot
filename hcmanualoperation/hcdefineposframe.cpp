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
    widgets<<(QList<QWidget*>()<<ui->p1X1<<ui->p2X1<<ui->p3X1)
          <<(QList<QWidget*>()<<ui->p1Y1<<ui->p2Y1<<ui->p3Y1)
         <<(QList<QWidget*>()<<ui->p1Z<<ui->p2Z<<ui->p3Z)
        <<(QList<QWidget*>()<<ui->p1X2<<ui->p2X2<<ui->p3X2)
       <<(QList<QWidget*>()<<ui->p1Y2<<ui->p2Y2<<ui->p3Y2)
      <<(QList<QWidget*>()<<ui->p1A<<ui->p2A<<ui->p3A)
     <<(QList<QWidget*>()<<ui->p1B<<ui->p2B<<ui->p3B)
    <<(QList<QWidget*>()<<ui->p1C<<ui->p2C<<ui->p3C);

    ICLineEditWithVirtualNumericKeypad* edit;
    QIntValidator* v= new  QIntValidator(0, 65530, this);
    for(int i = 0; i != widgets.size(); ++i)
    {
        for(int j = 0; j != widgets.at(i).size(); ++j)
        {
            edit = qobject_cast<ICLineEditWithVirtualNumericKeypad*>(widgets[i][j]);
            edit->SetDecimalPlaces(2);
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
