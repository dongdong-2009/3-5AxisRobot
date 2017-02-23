#ifndef ICACTIONSIX_H
#define ICACTIONSIX_H

#include <QWidget>

namespace Ui {
class icactionsix;
}

class icactionsix : public QWidget
{
    Q_OBJECT

public:
    explicit icactionsix(QWidget *parent = 0);
    ~icactionsix();

private slots:
    void on_StartButton_clicked();

    void on_StopButton_clicked();

    void on_DownButton_clicked();

    void on_OriginButton_clicked();

    void on_ReturnButton_clicked();

    void on_UpButton_clicked();

protected:
    void keyPressEvent(QKeyEvent* e);
    void keyReleaseEvent(QKeyEvent* e);
    void changeEvent(QEvent *);

private:
    Ui::icactionsix *ui;
};

#endif // ICACTIONSIX_H
