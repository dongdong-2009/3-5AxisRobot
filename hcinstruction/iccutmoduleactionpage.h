#ifndef ICCUTMODULEACTIONPAGE_H
#define ICCUTMODULEACTIONPAGE_H

#include "icinstructioneditorbase.h"

namespace Ui {
class ICCutModuleActionPage;
}

class ICCutModuleActionPage : public ICInstructionEditorBase
{
    Q_OBJECT

public:
    explicit ICCutModuleActionPage(QWidget *parent = 0);
    ~ICCutModuleActionPage();

    ICTopMoldUIItem CreateTopUIItem() const;

protected:
    void changeEvent(QEvent *e);
//    void hideEvent(QHideEvent *e);
//    void showEvent(QShowEvent *e);
    void SyncStatusImpl(const QList<ICMoldItem> &items) {}
    QList<ICMoldItem> CreateCommandImpl() const;

private slots:
    void on_setIn1_clicked();

    void on_setIn2_clicked();

private:
    Ui::ICCutModuleActionPage *ui;
};

#endif // ICCUTMODULEACTIONPAGE_H
