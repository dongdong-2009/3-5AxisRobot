#ifndef ICCURVEEDITOR_H
#define ICCURVEEDITOR_H

#include "icinstructioneditorbase.h"
#include <QIntValidator>


namespace Ui {
class ICCurveEditor;
}
class QAbstractButton;

class ICCurveEditor : public ICInstructionEditorBase
{
    Q_OBJECT

public:
    explicit ICCurveEditor(QWidget *parent = 0);
    ~ICCurveEditor();


protected:
    void changeEvent(QEvent *);
    void hideEvent(QHideEvent *e);
    void showEvent(QShowEvent *e);
    void SyncStatusImpl(const QList<ICMoldItem> &items) {}
    QList<ICMoldItem> CreateCommandImpl() const;

private slots:
    void onTypeChanged(QAbstractButton* button);

    void on_setInPoint1_clicked();

    void on_setInPoint2_clicked();

private:
    Ui::ICCurveEditor *ui;
    int posMaxs_[3];
    int posMins_[3];
    QIntValidator posValidators_[3];
};

#endif // ICCURVEEDITOR_H
