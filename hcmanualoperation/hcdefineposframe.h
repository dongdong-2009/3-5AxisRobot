#ifndef HCDEFINEPOSFRAME_H
#define HCDEFINEPOSFRAME_H

#include <QFrame>

namespace Ui {
class HCDefinePosFrame;
}

class HCDefinePosFrame : public QFrame
{
    Q_OBJECT

public:
    explicit HCDefinePosFrame(QWidget *parent = 0);
    ~HCDefinePosFrame();

protected:
    void changeEvent(QEvent *e);
    void showEvent(QShowEvent* e);
    void hideEvent(QHideEvent* e);

private slots:
    void on_setInPos1_clicked();

    void on_setInPos2_clicked();

    void on_setInPos3_clicked();

private:
    Ui::HCDefinePosFrame *ui;
};

#endif // HCDEFINEPOSFRAME_H
