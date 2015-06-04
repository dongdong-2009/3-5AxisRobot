#include "icvirtualkeyboard.h"
#include "ui_icvirtualkeyboard.h"
#include <QDebug>
#include <QWSInputMethod>

const char charMap[8][5] = {
    {'2','A','B','C',' '},
    {'3','D','E','F',' '},
    {'4','G','H','I',' '},
    {'5','J','K','L',' '},
    {'6','M','N','O',' '},
    {'7','P','Q','R','S'},
    {'8','T','U','V',' '},
    {'9','W','X','Y','Z'},
};

ICVirtualKeyboard::ICVirtualKeyboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ICVirtualKeyboard),
    isUpper(false),
    isDigit(false)
{
    ui->setupUi(this);     
    //{{widgetMatrix_     
//    widgetMatrix_<<(ICWidgetArray()<<ui->n1<<ui->n2<<ui->n3<<ui->n4<<ui->n5<<ui->n6<<ui->n7<<ui->n8<<ui->n9<<ui->n0<<ui->abc<<ui->bs<<ui->enter);
    //}}widgetMatrix_     
        //    ui->abc->setChecked(true);
    ui->abc->hide();
    numList  << ui->n2 << ui->n3 << ui->n4
             <<ui->n5 << ui->n6 << ui->n7 << ui->n8 << ui->n9;
    for(int i = 0;i < numList.size();i++)
    {
        numList.at(i)->setText(numList.at(i)->text().toUpper());
    }
    for(int id = 0;id < numList.size(); id++)
    {
        connect(numList.at(id),SIGNAL(clicked()),
                this,SLOT(OnNumberClicked()));
    }
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(  Qt::X11BypassWindowManagerHint | Qt::Tool/* | Qt::FramelessWindowHint*/ );
}

ICVirtualKeyboard::~ICVirtualKeyboard()
{
    delete ui;
}

void ICVirtualKeyboard::SetDigital(bool flag)
{
    if(isDigit ==false && flag == true)
        ui->abc->click();
    else if(isDigit == true && flag == false)
        ui->abc->click();

}

bool ICVirtualKeyboard::isDigital()
{
    return isDigit;
}

void ICVirtualKeyboard::OnNumberClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    int index = numList.indexOf(button);

    //    ui->widget->setGeometry(button->pos().x(),button->pos().y(),
    //                            201,51);
//    if(isDigit){
        //        qDebug() << qApp->focusWidget();
        //        qDebug() << QChar(charMap[index][0]).unicode();
        if(qApp->focusWidget())
            QApplication::postEvent(qApp->focusWidget(),
                                    new QKeyEvent(QEvent::KeyPress, QChar(charMap[index][0]).unicode(), Qt::NoModifier,QString(QChar(charMap[index][0]))));
//        return;
//    }

//    upperkeyboard->move(button->pos().x(),button->pos().y() - button->size().height());
//    QPoint point = button->mapToGlobal(QPoint(0,0));
   // upperkeyboard->move(point.x(),point.y()- button->height());
   // if(upperkeyboard->isVisible() && QString(button->text().at(0)) == old)
    //    upperkeyboard->hide();
  //  else
  //      upperkeyboard->show();

}


//void ICVirtualKeyboard::on_shift_clicked()
//{
//    isUpper = !isUpper;
//    if(isUpper)
//    {
//        for(int i = 0;i<numList.size(); ++i)
//        {
//            QString text = numList[i]->text();
//            numList[i]->setText(text.toUpper());
//        }
//    }
//    else
//    {
//        for(int i = 0;i<numList.size(); ++i)
//        {
//            QString text = numList[i]->text();
//            numList[i]->setText(text.toLower());
//        }
//    }
//}

void ICVirtualKeyboard::on_enter_clicked()
{
    if(qApp->focusWidget())
        QApplication::postEvent(qApp->focusWidget(),
                                new QKeyEvent(QEvent::KeyPress, Qt::Key_Return, Qt::NoModifier));
    hide();
}

void ICVirtualKeyboard::on_bs_clicked()
{
    if(qApp->focusWidget())
        QApplication::postEvent(qApp->focusWidget(),
                                new QKeyEvent(QEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier));

}


void ICVirtualKeyboard::on_n0_clicked()
{
    if(qApp->focusWidget())
        QApplication::postEvent(qApp->focusWidget(),
                                new QKeyEvent(QEvent::KeyPress, QChar('0').unicode(), Qt::NoModifier,QString(QChar('0'))));

}

void ICVirtualKeyboard::on_abc_clicked()
{
    isDigit = !isDigit;
    if(isDigit)
    {
        for(int i=0;i<numList.size();i++)
        {
            numList.at(i)->setText(QString(QChar(charMap[i][0])));
        }
    }
    else
    {
        for(int i=0;i<numList.size();i++)
        {
            QString qs = QString("%1%2%3%4%5").arg(charMap[i][0])
                    .arg('\n')
                    .arg(charMap[i][1])
                    .arg(charMap[i][2])
                    .arg(charMap[i][3]);
            if(charMap[i][4] != ' ')
            {
                qs += QString("%1").arg(charMap[i][4]);
            }
            if(isUpper)
                qs = qs.toUpper();
            numList.at(i)->setText(qs);

        }
    }
}


void ICVirtualKeyboard::on_n1_clicked()
{
    if(qApp->focusWidget())
        QApplication::postEvent(qApp->focusWidget(),
                                new QKeyEvent(QEvent::KeyPress, QChar('1').unicode(), Qt::NoModifier,QString(QChar('1'))));

}
