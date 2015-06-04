#ifndef ICVIRTUALKEYBOARD_H
#define ICVIRTUALKEYBOARD_H

#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>
#include <QHideEvent>
#include <QMoveEvent>
#include <QShowEvent>
//#include "icupperkeyboard.h"
#include "ICGUI_global.h"
namespace Ui {
class ICVirtualKeyboard;
}

class ICGUISHARED_EXPORT ICVirtualKeyboard : public QWidget
{
    Q_OBJECT
    
public:
    explicit ICVirtualKeyboard(QWidget *parent = 0);
    ~ICVirtualKeyboard();
    void SetDigital(bool);
    bool isDigital();

signals:
    void ENTClicked();
    void CommitString(QString);
    void SetText(int,QString);

protected:
private slots:
    void OnNumberClicked();
    
    void on_enter_clicked();

    void on_bs_clicked();

    void on_n0_clicked();

    void on_abc_clicked();

    void on_n1_clicked();

private:
    Ui::ICVirtualKeyboard *ui;
    bool isUpper;
    bool isDigit;
    QList <QPushButton *> numList;
};

#endif // ICVIRTUALKEYBOARD_H
