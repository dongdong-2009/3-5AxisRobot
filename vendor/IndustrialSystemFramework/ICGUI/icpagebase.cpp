///////////////////////////////////////////////////////////
//  icpagebase.cpp
//  Implementation of the Class ICPageBase
//  Created on:      21-七月-2011 19:00:54
//  Original author: GaussCheng
///////////////////////////////////////////////////////////

//#include <qmath.h>
#include <QAction>
#include <QEvent>
#include <QKeyEvent>
//#include <QCheckBox>
//#include <QDoubleSpinBox>
//#include <QSpinBox>
//#include <QComboBox>
#include <QDialog>
#include <QComboBox>
#include <QMouseEvent>
#include <QLineEdit>
#include <QApplication>
#include <QMessageBox>
#include "icpagebase.h"
#include "icuser.h"
#include "qdatetimeedit.h"


#include <QDebug>

ICPageBase::ICPageBase(QWidget *parent):
    QWidget(parent),
    currentFocusRow_(0),
    currentFocusColumn_(0),
    modifyLevel_(-1),
    dialog_(NULL),
    oldCurrentFocusRow_(0),
    oldCurrentFocusColumn_(0),
    clickCount_(0)
{
    BindingKeys(QList<int>()<<Qt::Key_Left<<Qt::Key_Right<<Qt::Key_Up<<Qt::Key_Down);
}


ICPageBase::~ICPageBase()
{
}

bool ICPageBase::eventFilter(QObject *obj, QEvent *e)
{
//    if(ICUserCenter::CurrentUser()->Level() < CurrentModifyLevel())
//    if(!(ICUserCenter::CurrentUser()->HasPermission(CurrentModifyLevel())) && CurrentModifyLevel() != -1)
//    {
//        if(e->type() == QEvent::MouseButtonPress
//                || e->type() == QEvent::MouseButtonDblClick)
//        {
//            if(clickCount_ ++ == 0 )
//            {
//                QMessageBox::warning(this,tr("warning"),tr("the priviledge is lower!"));
//            }
//            e->ignore();
//            return true;
//        }
//        return QWidget::eventFilter(obj, e);
//    }

//    if(e->type() == QEvent::MouseButtonPress)
//    {
//        QWidget *widget = qobject_cast<QWidget* >(obj);
//        widget->setFocus();
//    }
//    if(e->type() == QEvent::KeyPress)
//    {
//        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(e);
//        int key = keyEvent->key();
//        if(key == Qt::Key_Left ||
//                key == Qt::Key_Right ||
//                key == Qt::Key_Up ||
//                key == Qt::Key_Down)
//        {
//            WidgetNavigate_(key);
//            return true;
//        }
//    }
    return QWidget::eventFilter(obj, e);
}

//void ICPageBase::keyPressEvent(QKeyEvent *e)
//{
//    qDebug("ICPageBase ignor pressed");
//    e->ignore();
//}

void ICPageBase::showEvent(QShowEvent *e)
{
//    clickCount_ = 0;
//    currentFocusRow_ = 0;
//    currentFocusColumn_ = 0;
//    QWidget* fwidget = qApp->focusWidget();
//    if(fwidget != NULL)
//    {
//        fwidget->clearFocus();
//    }
//    if(!(ICUserCenter::CurrentUser()->HasPermission(CurrentModifyLevel())) && CurrentModifyLevel() != -1)
//    {
//        QWidget::showEvent(e);
//        return;
//    }
//    QWidget* nw = NextFocusWidget(currentFocusRow_, currentFocusColumn_);
//    if(nw != NULL)
//    {
//        if(nw->isEnabled())
//        {
//            NextFocusWidget(currentFocusRow_, currentFocusColumn_)->setFocus();
//        }
//        else
//        {
//            WidgetNavigate_(Qt::Key_Right);
//        }
//    }
//    else
//    {
//        WidgetNavigate_(Qt::Key_Right);
//    }
    QWidget::showEvent(e);
}



/**
 * 绑定按键，让KeyHandler可以接收该按键
 * 
 * @param key    键值
 */
void ICPageBase::BindingKey(int key)
{
    if(actionToKeyMap_.values().indexOf(key) < 0)
    {
        QAction *action = new QAction(this);
        action->setShortcut(QKeySequence(key));
        addAction(action);
        actionToKeyMap_.insert(action, key);
        connect(action,
                SIGNAL(triggered()),
                this,
                SLOT(ActionTriggered()));
    }
}


/**
 * 绑定按键列表，让KeyHandler可以接收这些按键
 * 
 * @param keys    按键列表
 */
void ICPageBase::BindingKeys(const QList<int> &keys)
{
    for(int i = 0; i != keys.size(); ++i)
    {
        BindingKey(keys.at(i));
    }
}


/**
 * 页面按键事件处理器,默认什么都不做
 * 
 * @param key    键值
 */
void ICPageBase::KeyHandler(int key)
{
    Q_UNUSED(key)
}

/**
 * 当按键触发时执行该函数，函数会调用keyHandler虚函数进行按处理
 */
void ICPageBase::ActionTriggered()
{
//    QAction* action = qobject_cast<QAction*>(sender());
//    const int key = actionToKeyMap_.value(action);
////    if(ICUserCenter::CurrentUser()->Level() < CurrentModifyLevel())
//    if(!(ICUserCenter::CurrentUser()->HasPermission(CurrentModifyLevel())) && CurrentModifyLevel() != -1)
//    {
//        if(dialog_ != NULL)
//        {
//            dialog_->exec();
//        }
//        if(clickCount_ ++ == 0 )
//        {
//            QMessageBox::warning(this,tr("warning"),tr("the priviledge is lower!"));
//        }
//        return;
//    }

//    if(key == Qt::Key_Left   ||
//            key == Qt::Key_Right  ||
//            key == Qt::Key_Up     ||
//            key == Qt::Key_Down)
//    {
//        WidgetNavigate_(key);
//    }
//    else
//    {
//        KeyHandler(key);
//    }
}

void ICPageBase::GetFocusWidgetIndex(int &rowIndex,int &columIndex)
{
    int i,j;
    bool isFind = false;
    QWidget* fW = qApp->focusWidget();
    if(fW == NULL)
    {
        return;
    }
    for(i = 0;i < FocusWidgetMatrixRowCount();i++)
    {
        if(NextFocusWidget(i, columIndex) == fW)
        {
            isFind = true;
            j = columIndex;
            goto end;
        }
        for(j = 0;j < FocusWidgetMatrixColumnCount(i);j++)
        {
            if(NextFocusWidget(i, j) == fW)
            {
                isFind = true;
                goto end;
            }
        }
    }
end:

    if(isFind)
    {    rowIndex = i;columIndex = j;   }
    else
    {     rowIndex = 0;columIndex = 0;   }
}

void ICPageBase::WidgetNavigate_(int key)
{
    QWidget* widget = NULL;
    bool isContinue = false;
    findnavRowCount_ = 0;
    do
    {
//        if(!isContinue)
//        {
//            GetFocusWidgetIndex(currentFocusRow_,currentFocusColumn_);
////            qDebug() << "currentFocusRow_" << currentFocusRow_ << "currentFocusColumn_" << currentFocusColumn_;
//        }
//        qDebug()<<"CR CC"<<currentFocusRow_<<currentFocusColumn_;
        if(FocusWidgetMatrixRowCount() != 0)
        {
            if(key == Qt::Key_Right)
            {
                if(currentFocusColumn_ != FocusWidgetMatrixColumnCount(currentFocusRow_) - 1)
                {
                    oldCurrentFocusColumn_ = currentFocusColumn_;
                    ++currentFocusColumn_;
                }
                else
                {
                    oldCurrentFocusColumn_ = currentFocusColumn_;
                    currentFocusColumn_ = 0;
                    oldCurrentFocusRow_ = currentFocusRow_;
                    currentFocusRow_ = (currentFocusRow_ + 1) % FocusWidgetMatrixRowCount();
                    ++findnavRowCount_;
                }
            }
            else if(key == Qt::Key_Left)
            {
                if(currentFocusColumn_ > 0)
                {
                    oldCurrentFocusColumn_ = currentFocusColumn_;
                    --currentFocusColumn_;
                }
                else
                {
                    oldCurrentFocusRow_ = currentFocusRow_;
                    --currentFocusRow_;
                    ++findnavRowCount_;
                    if(currentFocusRow_ < 0)
                    {
                        currentFocusRow_ = (FocusWidgetMatrixRowCount() + currentFocusRow_);
                        oldCurrentFocusRow_ = currentFocusRow_;
                    }
                    oldCurrentFocusColumn_ = currentFocusColumn_;
                    currentFocusColumn_ = FocusWidgetMatrixColumnCount(currentFocusRow_) - 1;
                }
            }
            else if(key == Qt::Key_Up)
            {
                ++findnavRowCount_;
                oldCurrentFocusRow_ = currentFocusRow_;
                --currentFocusRow_;
                if(currentFocusRow_ < 0)
                {
                    currentFocusRow_ = (FocusWidgetMatrixRowCount() + currentFocusRow_);
                    oldCurrentFocusRow_ = currentFocusRow_;
                }
                if(currentFocusColumn_ > FocusWidgetMatrixColumnCount(currentFocusRow_) - 1)
                {
                    oldCurrentFocusColumn_ = currentFocusColumn_;
                    currentFocusColumn_ = FocusWidgetMatrixColumnCount(currentFocusRow_) - 1;
                }
            }
            else if(key == Qt::Key_Down)
            {
                ++findnavRowCount_;
                oldCurrentFocusRow_ = currentFocusRow_;
                currentFocusRow_ = (currentFocusRow_ + 1) % FocusWidgetMatrixRowCount();
                if(currentFocusColumn_ > FocusWidgetMatrixColumnCount(currentFocusRow_) - 1)
                {
                    oldCurrentFocusColumn_ = currentFocusColumn_;
                    currentFocusColumn_ = FocusWidgetMatrixColumnCount(currentFocusRow_) - 1;
                }
            }
            widget = NextFocusWidget(currentFocusRow_, currentFocusColumn_);
            if((widget == qApp->focusWidget()))
            {
                if((oldCurrentFocusRow_ != currentFocusRow_) ||
                        (oldCurrentFocusColumn_ != currentFocusColumn_))
                {
                    widget = NULL;
                    oldCurrentFocusRow_ = currentFocusRow_;
                    oldCurrentFocusColumn_ = currentFocusColumn_;
                }
                //                else
                //                {

                //                }
            }
            if(widget != NULL)
            {
                if(widget->isEnabled() && !widget->isHidden())
                {
                    findnavRowCount_ = 0;
                    widget->setFocus();
                    isContinue = !widget->isEnabled() || widget->isHidden();
                }
                else
                {
                    isContinue = (findnavRowCount_ < FocusWidgetMatrixRowCount());
                }
            }
            else
            {
                isContinue = (findnavRowCount_ < FocusWidgetMatrixRowCount());
            }
//            qDebug()<<"IsC"<<isContinue;
        }
        else
        {
            return;
        }
//        if(widget == NULL)
//        {
//            isContinue = (findnavRowCount_ < FocusWidgetMatrixRowCount());
//        }
//        else
//        {
//            isContinue = !widget->isEnabled() || widget->isHidden();
//        }
    }while(isContinue);

}

void ICPageBase::IgnoreEventHelper(QWidget * widgets[], int size)
{
    for(int i = 0; i != size; ++i)
    {
        if(widgets[i] != NULL)
        widgets[i]->installEventFilter(this);
        if(qobject_cast<QComboBox*>(widgets[i]) != NULL)
        {
            QComboBox *comboBox = qobject_cast<QComboBox*>(widgets[i]);
            if(comboBox->lineEdit())
                comboBox->lineEdit()->installEventFilter(this);
        }

    }
}

void ICPageBase::IgnoreEventHelper(QList<QWidget *> widgets)
{
    for(int i = 0; i!= widgets.size(); ++i)
    {
        if(widgets[i] != NULL)
            widgets[i]->installEventFilter(this);
        if(qobject_cast<QComboBox*>(widgets[i]) != NULL)
        {
            QComboBox *comboBox = qobject_cast<QComboBox*>(widgets[i]);
            if(comboBox->lineEdit())
                comboBox->lineEdit()->installEventFilter(this);
        }
    }
}

//void ICPageBase::InitPageHelper(QList<QList<QWidget *> > &widgets)
//{
//    QWidget* widget;
//    QDoubleSpinBox* dsb;
//    QSpinBox* sb;
//    QCheckBox* cb;
//    QComboBox* cbb;
//    QList<QWidget*> widgetsRow;
//    for(int i = 0; i != widgets.size(); ++i)
//    {
//        widgetsRow = widgets[i];
//        for(int j = 0; j != widgetsRow.size(); ++j)
//        {
//            widget = widgetsRow[j];
//            widget->installEventFilter(this);
//            if((dsb = qobject_cast<QDoubleSpinBox*>(widget)) != NULL)
//            {
//                dsb->setValue(GetWidgetValueWhenInit(widget) / qPow(10, dsb->decimals()));
//                connect(dsb,
//                        SIGNAL(valueChanged(double)),
//                        SLOT(OnDoubleSpinBoxValueChanged(double)));
//            }
//            else if((sb = qobject_cast<QSpinBox*>(widget)) != NULL)
//            {
//                sb->setValue(GetWidgetValueWhenInit(widget));
//                connect(sb,
//                        SIGNAL(valueChanged(int)),
//                        SLOT(OnSpinBoxValueChanged(int)));
//            }
//            else if((cb = qobject_cast<QCheckBox*>(widget)) != NULL)
//            {
//                cb->setChecked(GetWidgetValueWhenInit(widget) > 0);
//                connect(cb,
//                        SIGNAL(toggled(bool)),
//                        SLOT(OnCheckBoxToggled(bool)));
//            }
//            else if((cbb = qobject_cast<QComboBox*>(widget)) != NULL)
//            {
//                cbb->setCurrentIndex(GetWidgetValueWhenInit(widget));
//                connect(cbb,
//                        SIGNAL(currentIndexChanged(int)),
//                        SLOT(OnComBoBoxIndexChanged(int)));
//            }
//        }
//    }
//}

//void ICPageBase::ReInitPageHelper(QList<QList<QWidget *> > &widgets)
//{
//    QWidget* widget;
//    QDoubleSpinBox* dsb;
//    QSpinBox* sb;
//    QCheckBox* cb;
//    QComboBox* cbb;
//    QList<QWidget*> widgetsRow;
//    for(int i = 0; i != widgets.size(); ++i)
//    {
//        widgetsRow = widgets[i];
//        for(int j = 0; j != widgetsRow.size(); ++j)
//        {
//            widget = widgetsRow[j];
//            widget->blockSignals(true);
//            if((dsb = qobject_cast<QDoubleSpinBox*>(widget)) != NULL)
//            {
//                dsb->setValue(GetWidgetValueWhenInit(widget) / qPow(10, dsb->decimals()));
//            }
//            else if((sb = qobject_cast<QSpinBox*>(widget)) != NULL)
//            {
//                sb->setValue(GetWidgetValueWhenInit(widget));
//            }
//            else if((cb = qobject_cast<QCheckBox*>(widget)) != NULL)
//            {
//                cb->setChecked(GetWidgetValueWhenInit(widget) > 0);
//            }
//            else if((cbb = qobject_cast<QComboBox*>(widget)) != NULL)
//            {
//                cbb->setCurrentIndex(GetWidgetValueWhenInit(widget));
//            }
//            widget->blockSignals(false);
//        }
//    }
//}

//void ICPageBase::OnDoubleSpinBoxValueChanged(double value)
//{
//    QDoubleSpinBox* spinBox = qobject_cast<QDoubleSpinBox*>(sender());
//    uint v = value * qPow(10, spinBox->decimals());
//    UpdateWidgetValue(v, spinBox);
//}

//void ICPageBase::OnSpinBoxValueChanged(int value)
//{
//    UpdateWidgetValue(value, qobject_cast<QWidget*>(sender()));
//}

//void ICPageBase::OnCheckBoxToggled(bool checked)
//{
//    UpdateWidgetValue(checked ? 1 : 0, qobject_cast<QWidget*>(sender()));
//}

//void ICPageBase::OnComBoBoxIndexChanged(int index)
//{
//    if(index < 0)
//    {
//        return;
//    }
//    UpdateWidgetValue(index, qobject_cast<QWidget*>(sender()));
//}
