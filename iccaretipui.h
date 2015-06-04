#ifndef ICCARETIPUI_H
#define ICCARETIPUI_H

#include <QDialog>
#include <QMap>

namespace Ui {
class ICCareTipUI;
}

class ICCareTipUI : public QDialog
{
    Q_OBJECT

public:
    explicit ICCareTipUI(QWidget *parent = 0);
    ~ICCareTipUI();

protected:
    void changeEvent(QEvent *e);

private slots:
    void OnHasCareBtnClicked();

private:
    Ui::ICCareTipUI *ui;
    QList<QPushButton*> hasCareBtns_;
    QMap<QWidget*, int> hasCareBtnToItemIndex_;
};

#endif // ICCARETIPUI_H
