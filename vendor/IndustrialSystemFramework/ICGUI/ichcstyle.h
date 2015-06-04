#ifndef ICHCSTYLE_H
#define ICHCSTYLE_H

#include <QPlastiqueStyle>
#include "ICGUI_global.h"

class ICGUISHARED_EXPORT ICHCStyle : public QPlastiqueStyle
{
    Q_OBJECT
public:
    static QColor FocusColor() { return QColor(246, 153, 63);}
    static void InitAppPallete();
    ICHCStyle();
    void drawPrimitive(PrimitiveElement element, const QStyleOption *option,
                            QPainter *painter, const QWidget *widget) const;

    void drawComplexControl(ComplexControl control,
                            const QStyleOptionComplex *option,
                            QPainter *painter, const QWidget *widget) const;

    void drawControl(ControlElement element,
                     const QStyleOption *option,
                     QPainter *painter, const QWidget *widget) const;
};

#endif // ICHCSTYLE_H
