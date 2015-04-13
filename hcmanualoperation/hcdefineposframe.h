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
    void on_setInPos1_1_clicked();
    void on_setInPos1_2_clicked();
    void on_setInPos1_3_clicked();
    void on_setInPos1_4_clicked();
    void on_setInPos1_5_clicked();
    void on_setInPos1_6_clicked();
    void on_setInPos1_7_clicked();
    void on_setInPos1_8_clicked();

    void on_setInPos2_1_clicked();
    void on_setInPos2_2_clicked();
    void on_setInPos2_3_clicked();
    void on_setInPos2_4_clicked();
    void on_setInPos2_5_clicked();
    void on_setInPos2_6_clicked();
    void on_setInPos2_7_clicked();
    void on_setInPos2_8_clicked();

    void on_setInPos3_1_clicked();
    void on_setInPos3_2_clicked();
    void on_setInPos3_3_clicked();
    void on_setInPos3_4_clicked();
    void on_setInPos3_5_clicked();
    void on_setInPos3_6_clicked();
    void on_setInPos3_7_clicked();
    void on_setInPos3_8_clicked();

    void OnLevelChanged(int level);

    void ClearSelection1();
    void ClearSelection2();
    void ClearSelection3();


private:
    Ui::HCDefinePosFrame *ui;
    QString oldStyle_;
    QString newStyle_;
};

#endif // HCDEFINEPOSFRAME_H
