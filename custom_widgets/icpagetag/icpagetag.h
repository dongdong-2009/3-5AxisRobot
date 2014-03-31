#ifndef ICPAGETAG_H
#define ICPAGETAG_H

#include <QAbstractButton>
#include <QPixmap>

class ICPageTag : public QAbstractButton
{
    Q_OBJECT

public:
    enum IconSide{IconOnLeft, IconOnRight};
    explicit ICPageTag(QWidget *parent = 0);
    ~ICPageTag();

    IconSide Direction() const {return iconSide_;}
    void SetDirection(IconSide iconSide) { iconSide_ = iconSide;}
#ifdef HC_SK_5
    QSize sizeHint() const { return QSize(390, 50);}
#else
    QSize sizeHint() const { return QSize(430, 55);}
#endif
    QSize minimumSizeHint() const { return sizeHint();}

protected:
    void paintEvent(QPaintEvent *e);

private:
    IconSide iconSide_;
    QPixmap leftBackground_;
    QPixmap rightBackground_;
    QPixmap leftPressBG_;
    QPixmap rightPressBG_;
    QPixmap leftDisableBG_;
    QPixmap rightDisableBG_;
};

#endif // ICPAGETAG_H
