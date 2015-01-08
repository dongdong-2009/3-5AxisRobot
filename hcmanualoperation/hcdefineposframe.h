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

private:
    Ui::HCDefinePosFrame *ui;
};

#endif // HCDEFINEPOSFRAME_H
