#ifndef ICPAGESWITCH_H
#define ICPAGESWITCH_H

#include <QAbstractButton>

class ICPageSwitch : public QAbstractButton
{
    Q_OBJECT

public:
    explicit ICPageSwitch(QWidget *parent = 0);
    ~ICPageSwitch();

    QSize sizeHint() const { return QSize(151, 80);}
    QSize minimumSizeHint() const { return sizeHint();}
    void SetTextColor(const QColor& color) { textColor_ = color;}
protected:
    void paintEvent(QPaintEvent *e);

private:
    QPixmap background_;
    QPixmap disableBG_;
    QPixmap checkedBG_;
    QColor textColor_;
};

#endif // ICPAGESWITCH_H
