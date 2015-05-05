///////////////////////////////////////////////////////////
//  icmenubarpage.cpp
//  Implementation of the Class ICMenubarPage
//  Created on:      07-九月-2011 14:16:23
//  Original author: GaussCheng
///////////////////////////////////////////////////////////

#include "icmenubarpage.h"

#include <QKeyEvent>

ICMenuBarPage::ICMenuBarPage(QWidget *parent)
    :QStackedWidget(parent),
      menubar_(NULL)
{
    connect(this,
            SIGNAL(currentChanged(int)),
            this,
            SLOT(OnCurrentWidgetChanged(int)));
}



ICMenuBarPage::~ICMenuBarPage(){

}

void ICMenuBarPage::OnCurrentWidgetChanged(int index)
{
    emit CurrentPageChanged(widget(index));
}

//void ICMenuBarPage::keyPressEvent(QKeyEvent *e)
//{
//    e->ignore();
//    qDebug("ICMenuBarPage ignor press");
//}
