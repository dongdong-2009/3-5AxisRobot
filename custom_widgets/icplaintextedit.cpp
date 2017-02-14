#include "icplaintextedit.h"

#include <QApplication>


ICPlainTextEdit::ICPlainTextEdit(QWidget *parent) :
    QPlainTextEdit(parent)
{
    keyboard_ = new ICInputMethodKeyboard(this);
    keyboard_->SetTextEditor(this);
}

void ICPlainTextEdit::mousePressEvent(QMouseEvent *e)
{
    if(!keyboard_->isVisible())
    {
        keyboard_->move(0, 140);
        keyboard_->show();
    }
    QPlainTextEdit::mousePressEvent(e);
}
