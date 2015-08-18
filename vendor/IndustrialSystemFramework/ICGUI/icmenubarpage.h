///////////////////////////////////////////////////////////
//  icmenubarpage.h
//  Implementation of the Class ICMenubarPage
//  Created on:      07-九月-2011 14:16:22
//  Original author: GaussCheng
///////////////////////////////////////////////////////////

#if !defined(EA_DE779847_0CD6_49fe_BFFB_2F00B07C4C2E__INCLUDED_)
#define EA_DE779847_0CD6_49fe_BFFB_2F00B07C4C2E__INCLUDED_

#include <QStackedWidget>
#include <QApplication>
#include "icmenubarbase.h"
#include "ICGUI_global.h"

class QAbstractButton;

/**
 * 带菜单支持的页面widget，用于构造动态菜单的项目
 * @author GaussCheng
 * @version 1.0
 * @created 07-九月-2011 14:16:22
 */
class ICGUISHARED_EXPORT ICMenuBarPage : public QStackedWidget
{
    Q_OBJECT
public:
    ICMenuBarPage(QWidget* parent = NULL);
    virtual ~ICMenuBarPage();

    ICMenuBarBase* MenuBar() { return menubar_;}
    void SetMenuBar(ICMenuBarBase* menuBar);
    void ReFocusWidget();

signals:
    void ReturnToParent();
    void CurrentPageChanged(QWidget*);

protected:
    virtual void MenuItemTriggeredHandler(QAbstractButton* whitch){Q_UNUSED(whitch)}
//    void keyPressEvent(QKeyEvent *e);

private Q_SLOTS:
    void OnMenuItemTriggered(QWidget* whitch);
    void OnCurrentWidgetChanged(int index);

private:
    ICMenuBarBase *menubar_;

};

inline void ICMenuBarPage::SetMenuBar(ICMenuBarBase *menuBar)
{
    if(menubar_ != NULL)
    {
        menubar_->disconnect();
    }
    menubar_ = menuBar;
    connect(menubar_,
            SIGNAL(MenuItemTriggered(QWidget*)),
            this,
            SLOT(OnMenuItemTriggered(QWidget*)));
}

inline void ICMenuBarPage::OnMenuItemTriggered(QWidget *whitch)
{
//    QWidget* fwidget = QWidget::focusWidget();
//    if(fwidget != NULL)
//    {
//        fwidget->clearFocus();
//        fwidget->setFocus();
//    }
    MenuItemTriggeredHandler(qobject_cast<QAbstractButton*>(whitch));
}

inline void ICMenuBarPage::ReFocusWidget()
{
    QWidget* fwidget = QWidget::focusWidget();
    if(fwidget != NULL)
    {
        fwidget->clearFocus();
        fwidget->setFocus();
    }
}

#endif // !defined(EA_DE779847_0CD6_49fe_BFFB_2F00B07C4C2E__INCLUDED_)
