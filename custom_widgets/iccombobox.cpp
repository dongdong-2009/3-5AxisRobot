#include "iccombobox.h"

#include <QKeyEvent>
#include <QAbstractItemView>
#include <QApplication>

ICComboBox::ICComboBox(QWidget *parent) :
    QComboBox(parent)
{
    this->view()->installEventFilter(this);
}

void ICComboBox::keyPressEvent(QKeyEvent *e)
{
    e->ignore();
}

void ICComboBox::keyReleaseEvent(QKeyEvent *e)
{
    e->ignore();
}

void ICComboBox::focusInEvent(QFocusEvent *e)
{
    oldValue_ = currentIndex();
    QComboBox::focusInEvent(e);
}

bool ICComboBox::eventFilter(QObject *o, QEvent *e)
{
    if(o != this->view())
        return QComboBox::eventFilter(o, e);
    if(e->type() == QEvent::KeyPress)
    {
        QKeyEvent* k = static_cast<QKeyEvent*>(e);
        QKeyEvent* ke = new QKeyEvent(*k);
        qApp->postEvent(this->parentWidget(), ke);
        e->ignore();
        this->hidePopup();
        return true;
    }
    return QComboBox::eventFilter(o, e);

}
