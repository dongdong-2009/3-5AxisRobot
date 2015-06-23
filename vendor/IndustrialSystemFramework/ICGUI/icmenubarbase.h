///////////////////////////////////////////////////////////
//  icmenubarbase.h
//  Implementation of the Class ICMenuBarBase
//  Created on:      07-九月-2011 14:16:44
//  Original author: GaussCheng
///////////////////////////////////////////////////////////

#if !defined(EA_77B52875_6154_4715_B7D9_8F376340CA5A__INCLUDED_)
#define EA_77B52875_6154_4715_B7D9_8F376340CA5A__INCLUDED_

#include <QStackedWidget>
#include <QPushButton>
#include <QMap>
#include <QLayout>
#include <QSignalMapper>

#include "ICGUI_global.h"
#include "icslidingwidget.h"

/**
 * 菜单条基类，定义菜单条的基本接口
 * @author GaussCheng
 * @version 1.0
 * @created 07-九月-2011 14:16:44
 */
class ICGUISHARED_EXPORT ICMenuBarBase:public ICSlidingWidget
{
    Q_OBJECT
public:
    ICMenuBarBase(QWidget* parent = NULL);
	virtual ~ICMenuBarBase();

    QAbstractButton* AddMenuItem(const QString& text, int key, int pageIndex = 0);
    QAbstractButton* AddCustomMenuItem(const QString& text, int key, int pageIndex = 0);
    virtual void ClearItemStatus(){}

signals:
    void MenuItemTriggered(QWidget* whitch);
protected:
    void changeEvent(QEvent *e);
    virtual QAbstractButton* CreateMenuButton(const QString& text, int key, int pageIndex);
    virtual QAbstractButton* CreateCustomMenuButton(const QString& text, int key, int pageIndex);

private Q_SLOTS:
    void OnMenuItemTriggeed(QWidget* whitch);
private:
    QSignalMapper buttonSignalMapper_;
};

inline QAbstractButton* ICMenuBarBase::AddMenuItem(const QString &text, int key, int pageIndex)
{
    QAbstractButton* ret = CreateMenuButton(text, key, pageIndex);
    if(ret != NULL)
    {
        ret->setFocusPolicy(Qt::NoFocus);
        buttonSignalMapper_.setMapping(ret, ret);
        connect(ret,
                SIGNAL(clicked()),
                &buttonSignalMapper_,
                SLOT(map()));
    }
    return ret;
}

inline QAbstractButton* ICMenuBarBase::AddCustomMenuItem(const QString &text, int key, int pageIndex)
{
    QAbstractButton* ret = CreateCustomMenuButton(text, key, pageIndex);
    if(ret != NULL)
    {
        ret->setFocusPolicy(Qt::NoFocus);
        buttonSignalMapper_.setMapping(ret, ret);
        connect(ret,
                SIGNAL(clicked()),
                &buttonSignalMapper_,
                SLOT(map()));
    }
    return ret;
}

#endif // !defined(EA_77B52875_6154_4715_B7D9_8F376340CA5A__INCLUDED_)
