///////////////////////////////////////////////////////////
//  icmenubarbase.cpp
//  Implementation of the Class ICMenuBarBase
//  Created on:      07-九月-2011 14:16:44
//  Original author: GaussCheng
///////////////////////////////////////////////////////////

#include <QEvent>
#include "icmenubarbase.h"

#include <QDebug>

ICMenuBarBase::ICMenuBarBase(QWidget *parent):
    ICSlidingWidget(parent)
{

    connect(&buttonSignalMapper_,
            SIGNAL(mapped(QWidget*)),
            this,
            SLOT(OnMenuItemTriggeed(QWidget*)));
}



ICMenuBarBase::~ICMenuBarBase(){
//    QMap<QAbstractButton*, QString>::iterator p = buttonToTextMap_.begin();
//    while(p != buttonToTextMap_.end())
//    {
//        delete p.key();
//        ++p;
//    }
}

void ICMenuBarBase::changeEvent(QEvent *e)
{
    ICSlidingWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        break;
    default:
        break;
    }
}

void ICMenuBarBase::OnMenuItemTriggeed(QWidget *whitch)
{
    if(IsSliding())
    {
        return;
    }
//    QAbstractButton* button = qobject_cast<QAbstractButton*>(whitch);
//    if(button->isChecked())
//    {
//        return;
//    }
//    button->setChecked(true);
    emit MenuItemTriggered(whitch);
}

QAbstractButton* ICMenuBarBase::CreateMenuButton(const QString& text, int key, int pageIndex)
{
    Q_UNUSED(pageIndex)
    Q_UNUSED(key)
    return new QPushButton(text);
}

QAbstractButton* ICMenuBarBase::CreateCustomMenuButton(const QString& text, int key, int pageIndex)
{
    return CreateMenuButton(text, key, pageIndex);
}
