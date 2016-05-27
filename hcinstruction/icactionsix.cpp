#include "icactionsix.h"
#include "ui_icactionsix.h"

#include <QKeyEvent>
#include "ickeyboard.h"
#include "ickeyboardhandler.h"
#include "mainframe.h"


icactionsix::icactionsix(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::icactionsix)
{
    ui->setupUi(this);
    connect(ui->CloseButton,SIGNAL(clicked()),this,SLOT(close()));
    this->setGeometry(QRect(450,70,262,286));
    this->setFixedSize(262,286);
    //this->setBackgroundRole(QPalette::Dark);
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
}

icactionsix::~icactionsix()
{
    delete ui;
}

void icactionsix::on_StartButton_clicked()
{
    QKeyEvent* ke = new QKeyEvent(QEvent::KeyPress,Qt::Key_F11,Qt::NoModifier);
    qApp->postEvent(icMainFrame, ke);
}

void icactionsix::on_StopButton_clicked()
{
    QKeyEvent* ke = new QKeyEvent(QEvent::KeyPress,Qt::Key_X,Qt::NoModifier);
    qApp->postEvent(icMainFrame, ke);
}

void icactionsix::on_OriginButton_clicked()
{
    QKeyEvent* ke = new QKeyEvent(QEvent::KeyPress,Qt::Key_S,Qt::NoModifier);
    qApp->postEvent(icMainFrame, ke);
}

void icactionsix::on_ReturnButton_clicked()
{
    QKeyEvent* ke = new QKeyEvent(QEvent::KeyPress,Qt::Key_D,Qt::NoModifier);
    qApp->postEvent(icMainFrame, ke);
}

void icactionsix::on_UpButton_clicked()
{
    QKeyEvent* ke = new QKeyEvent(QEvent::KeyPress,Qt::Key_I,Qt::NoModifier);
    qApp->postEvent(icMainFrame, ke);
}

void icactionsix::on_DownButton_clicked()
{
    QKeyEvent* ke = new QKeyEvent(QEvent::KeyPress,Qt::Key_N,Qt::NoModifier);
    qApp->postEvent(icMainFrame, ke);
}
void icactionsix::keyPressEvent(QKeyEvent *e)
{
    QKeyEvent* ke = new QKeyEvent(*e);
    qApp->postEvent(icMainFrame, ke);
   // this->reject();
}
