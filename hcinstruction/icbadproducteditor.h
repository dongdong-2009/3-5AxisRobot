#ifndef ICBADPRODUCTEDITOR_H
#define ICBADPRODUCTEDITOR_H

#include <QWidget>
#include "icinstructioneditorbase.h"


namespace Ui {
class ICBadProductEditor;
}

class ICBadProductEditor : public ICInstructionEditorBase
{
    Q_OBJECT

public:
    explicit ICBadProductEditor(QWidget *parent = 0);
    ~ICBadProductEditor();

signals:
    void BadProductSettingChanged();
protected:
    void showEvent(QShowEvent* e);
    void changeEvent(QEvent *e);
    void SyncStatusImpl(const QList<ICMoldItem> &items){}
    QList<ICMoldItem> CreateCommandImpl() const { return QList<ICMoldItem>();}

private slots:
    void on_okButton_clicked();

    void on_setInBtn_clicked();

    void on_badProductEn_toggled(bool checked);

private:
    Ui::ICBadProductEditor *ui;
};

#endif // ICBADPRODUCTEDITOR_H
