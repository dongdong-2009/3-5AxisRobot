///////////////////////////////////////////////////////////
//  icpagebase.h
//  Implementation of the Class ICPageBase
//  Created on:      21-七月-2011 19:00:53
//  Original author: GaussCheng
///////////////////////////////////////////////////////////

#if !defined(EA_82B6F48A_EBC3_4f02_B579_E64B72DFB8F3__INCLUDED_)
#define EA_82B6F48A_EBC3_4f02_B579_E64B72DFB8F3__INCLUDED_

#include <QWidget>
#include <QMap>
#include "ICGUI_global.h"

class QAction;

/**
 * 该类为工控页面提供基本的接口
 * @author GaussCheng
 * @version 1.0
 * @updated 23-七月-2011 9:52:19
 */
class ICGUISHARED_EXPORT ICPageBase : public QWidget
{
    Q_OBJECT
public:
    typedef QMap<QAction*, int> ICActionToKeyMap;
    explicit ICPageBase(QWidget* parent = 0);
	virtual ~ICPageBase();
	void BindingKey(int key);
    void BindingKeys(const QList<int> &keys);

    int CurrentModifyLevel() const { return modifyLevel_;}
    void SetModifyLevel(int level) { modifyLevel_ = level;}
    void SetLoginDialog(QDialog* dialog) { dialog_ = dialog;}

protected:
	virtual void KeyHandler(int key);
    virtual QWidget* NextFocusWidget(int row, int column) { Q_UNUSED(row) Q_UNUSED(column) return NULL;}
    virtual int FocusWidgetMatrixRowCount() const { return 0;}
    virtual int FocusWidgetMatrixColumnCount(int row) const { Q_UNUSED(row) return 0;}
    virtual void GetFocusWidgetIndex(int &row,int &colum);
//    virtual uint GetWidgetValueWhenInit(QWidget* widget){ return 0;}
//    virtual void UpdateWidgetValue(uint value, QWidget* widget){}
    bool eventFilter(QObject *obj, QEvent *e);
    void showEvent(QShowEvent *e);
    void IgnoreEventHelper(QWidget* widgets[], int size);
    void IgnoreEventHelper(QList<QWidget*> widgets);
//    void InitPageHelper(QList<QList<QWidget*> >& widgets);
//    void ReInitPageHelper(QList<QList<QWidget*> >& widgets);

private Q_SLOTS:
    void ActionTriggered();
//    void OnDoubleSpinBoxValueChanged(double value);
//    void OnSpinBoxValueChanged(int value);
//    void OnCheckBoxToggled(bool checked);
//    void OnComBoBoxIndexChanged(int index);
private:
    void WidgetNavigate_(int key);
    ICActionToKeyMap actionToKeyMap_;
    int currentFocusRow_;
    int currentFocusColumn_;
    int modifyLevel_;
    QDialog* dialog_;
    int oldCurrentFocusRow_;
    int oldCurrentFocusColumn_;
    int clickCount_;
    int findnavRowCount_;
};
#endif // !defined(EA_82B6F48A_EBC3_4f02_B579_E64B72DFB8F3__INCLUDED_)
