#ifndef ICPLAINTEXTEDIT_H
#define ICPLAINTEXTEDIT_H

#include <QPlainTextEdit>
#include "icinputmethodkeyboard.h"


class ICPlainTextEdit : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit ICPlainTextEdit(QWidget *parent = 0);


protected:
    void mousePressEvent(QMouseEvent *e);
signals:

public slots:

private:
    ICInputMethodKeyboard* keyboard_;

};

#endif // ICPLAINTEXTEDIT_H
