#include "ichcstyle.h"
#include <QStyle>
#include <QStyleOption>
#include <QPainter>
#include <QStringBuilder>
#include <QPixmapCache>
#include <QApplication>


template <typename T>
struct HexString
{
    inline HexString(const T t)
        : val(t)
    {}

    inline void write(QChar *&dest) const
    {
        const ushort hexChars[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
        const char *c = reinterpret_cast<const char *>(&val);
        for (uint i = 0; i < sizeof(T); ++i) {
            *dest++ = hexChars[*c & 0xf];
            *dest++ = hexChars[(*c & 0xf0) >> 4];
            ++c;
        }
    }
    const T val;
};

template <typename T>
struct QConcatenable<HexString<T> >
{
    typedef HexString<T> type;
    enum { ExactSize = true };
    static int size(const HexString<T> &) { return sizeof(T) * 2; }
    static inline void appendTo(const HexString<T> &str, QChar *&out) { str.write(out); }
    typedef QString ConvertTo;
};

static QLinearGradient qMapGradientToRect(const QLinearGradient &gradient, const QRectF &rect)
{
    QLinearGradient tmpGrad(rect.center().x(), rect.top(),
                            rect.center().x(), rect.bottom());
    tmpGrad.setStops(gradient.stops());
    return tmpGrad;
}

static QBrush qMapBrushToRect(const QBrush &brush, const QRectF &rect)
{
    if (!brush.gradient())
        return brush;

    // ### Ugly assumption that it's a linear gradient
    QBrush tmp(qMapGradientToRect(*static_cast<const QLinearGradient *>(brush.gradient()), rect));
    return tmp;
}

static void qBrushSetAlphaF(QBrush *brush, qreal alpha)
{
    if (const QGradient *gradient = brush->gradient()) {
        // Use the gradient. Call QColor::setAlphaF() on all color stops.
        QGradientStops stops = gradient->stops();
        QMutableVectorIterator<QGradientStop> it(stops);
        QColor tmpColor;
        while (it.hasNext()) {
            it.next();
            tmpColor = it.value().second;
            tmpColor.setAlphaF(alpha * tmpColor.alphaF());
            it.setValue(QPair<qreal, QColor>(it.value().first, tmpColor));
        }

        switch (gradient->type()) {
        case QGradient::RadialGradient: {
            QRadialGradient grad = *static_cast<const QRadialGradient *>(gradient);
            grad.setStops(stops);
            *brush = QBrush(grad);
            break;
        }
        case QGradient::ConicalGradient: {
            QConicalGradient grad = *static_cast<const QConicalGradient *>(gradient);
            grad.setStops(stops);
            *brush = QBrush(grad);
            break;
        }
        default:
            qWarning("QPlastiqueStyle::qBrushLight() - unknown gradient type"
                     " - falling back to QLinearGradient");
        case QGradient::LinearGradient: {
            QLinearGradient grad = *static_cast<const QLinearGradient *>(gradient);
            grad.setStops(stops);
            *brush = QBrush(grad);
            break;
        }
        }
    }
    else {
        // Use the color
        QColor tmpColor = brush->color();
        tmpColor.setAlphaF(alpha * tmpColor.alphaF());
        brush->setColor(tmpColor);
    }
}

static void qt_plastique_draw_gradient(QPainter *painter, const QRect &rect, const QColor &gradientStart,
                                       const QColor &gradientStop)
{
    QString gradientName = QLatin1Literal("qplastique-g")
                   % HexString<int>(rect.width())
                   % HexString<int>(rect.height())
                   % HexString<QRgb>(gradientStart.rgba())
                   % HexString<QRgb>(gradientStop.rgba());

    QPixmap cache;
    QPainter *p = painter;
    QRect r = rect;

    bool doPixmapCache = painter->deviceTransform().isIdentity()
    && painter->worldMatrix().isIdentity();
    if (doPixmapCache && QPixmapCache::find(gradientName, cache)) {
        painter->drawPixmap(rect, cache);
    } else {
        if (doPixmapCache) {
            cache = QPixmap(rect.size());
            cache.fill(Qt::transparent);
            p = new QPainter(&cache);
        r = QRect(0, 0, rect.width(), rect.height());
        }

//        int x = r.center().x();
        QLinearGradient gradient(r.width(), 0, r.width(), r.height() * 0.312);
        gradient.setColorAt(0, gradientStart);
        gradient.setColorAt(1, gradientStop);
        p->fillRect(r, gradient);

        if (doPixmapCache) {
        p->end();
        delete p;
        painter->drawPixmap(rect, cache);
            QPixmapCache::insert(gradientName, cache);
    }
    }
}

static QColor mergedColors(const QColor &colorA, const QColor &colorB, int factor = 50)
{
    const int maxFactor = 100;
    QColor tmp = colorA;
    tmp.setRed((tmp.red() * factor) / maxFactor + (colorB.red() * (maxFactor - factor)) / maxFactor);
    tmp.setGreen((tmp.green() * factor) / maxFactor + (colorB.green() * (maxFactor - factor)) / maxFactor);
    tmp.setBlue((tmp.blue() * factor) / maxFactor + (colorB.blue() * (maxFactor - factor)) / maxFactor);
    return tmp;
}

static QString uniqueName(const QString &key, const QStyleOption *option, const QSize &size)
{
    const QStyleOptionComplex *complexOption = qstyleoption_cast<const QStyleOptionComplex *>(option);
    QString tmp = key % HexString<uint>(option->state)
                      % HexString<uint>(option->direction)
                      % HexString<uint>(complexOption ? uint(complexOption->activeSubControls) : 0u)
                      % HexString<quint64>(option->palette.cacheKey())
                      % HexString<uint>(size.width())
                      % HexString<uint>(size.height());
    return tmp;
}

ICHCStyle::ICHCStyle()
{
}

void ICHCStyle::drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    switch(element)
    {
    case PE_FrameFocusRect:
    {
        if (const QStyleOptionFocusRect *fropt = qstyleoption_cast<const QStyleOptionFocusRect *>(option))
        {
            //### check for d->alt_down
            if (!(fropt->state & State_KeyboardFocusChange) && !proxy()->styleHint(SH_UnderlineShortcut, option))
                return;
            QRect r = option->rect;
            painter->save();
            painter->setBackgroundMode(Qt::TransparentMode);
            //            QColor bg_col = fropt->backgroundColor;
            QColor bg_col = FocusColor();
            // Create an "XOR" color.
            QColor patternCol((bg_col.red() ^ 0xff) & 0xff,
                              (bg_col.green() ^ 0xff) & 0xff,
                              (bg_col.blue() ^ 0xff) & 0xff);
            painter->setBrush(QBrush(patternCol, Qt::Dense4Pattern));
            painter->setBrushOrigin(r.topLeft());
            painter->setPen(Qt::NoPen);
            painter->drawRect(r.left(), r.top(), r.width(), 1);    // Top
            painter->drawRect(r.left(), r.bottom(), r.width(), 1); // Bottom
            painter->drawRect(r.left(), r.top(), 1, r.height());   // Left
            painter->drawRect(r.right(), r.top(), 1, r.height());  // Right
            painter->restore();
        }
    }
        break;
    case PE_PanelButtonCommand:
    {
        if(const QStyleOptionButton *btn = qstyleoption_cast<const QStyleOptionButton*>(option))
        {
            if ((option->state & State_HasFocus)
                    && ((option->state & State_KeyboardFocusChange) || styleHint(SH_UnderlineShortcut, option, widget)))
            {

                QStyleOptionButton buttonOption;
                buttonOption.QStyleOption::operator=(*btn);
                buttonOption.palette.setBrush(QPalette::Button, QBrush(FocusColor()));
                QPlastiqueStyle::drawPrimitive(element, &buttonOption, painter,widget);
            }
            else
            {
                QPlastiqueStyle::drawPrimitive(element, option, painter,widget);
            }
        }
    }
        break;
    case PE_IndicatorCheckBox:
    {
        static QPixmap checkBoxFullNormal(":/image/checkbox_full_normal.png");
        static QPixmap checkBoxFullFocus(":/image/checkbox_full_focus.png");
        static QPixmap checkBoxEmptyNormal(":/image/checkbox_empty_normal.png");
        static QPixmap checkBoxEmptyFocus(":/image/checkbox_empty_focus.png");
        static QPixmap checkBoxTristateNormal(":/image/checkbox_tristate_normal.png");
        static QPixmap checkBoxTristateFocus(":/image/checkbox_tristate_focus.png");
        QPixmap toDraw;
        if(option->state & State_On)
        {
            if ((option->state & State_HasFocus)
                    && ((option->state & State_KeyboardFocusChange) || styleHint(SH_UnderlineShortcut, option, widget)))
            {
                toDraw = checkBoxFullFocus;
            }
            else
            {
                toDraw = checkBoxFullNormal;
            }
        }
        else if(option->state & State_NoChange)
        {
            if ((option->state & State_HasFocus)
                    && ((option->state & State_KeyboardFocusChange) || styleHint(SH_UnderlineShortcut, option, widget)))
            {
                toDraw = checkBoxTristateFocus;
            }
            else
            {
                toDraw = checkBoxTristateNormal;
            }
        }
        else if(option->state & State_Off)
        {
            if ((option->state & State_HasFocus)
                    && ((option->state & State_KeyboardFocusChange) || styleHint(SH_UnderlineShortcut, option, widget)))
            {
                toDraw = checkBoxEmptyFocus;
            }
            else
            {
                toDraw = checkBoxEmptyNormal;
            }
        }
        QRect ir(0, 0, toDraw.width(), toDraw.height());
        painter->drawPixmap(ir, toDraw);

    }
        break;
    default:
    {
        QPlastiqueStyle::drawPrimitive(element,
                                       option,
                                       painter,
                                       widget);
    }
        break;
    }
}

void ICHCStyle::drawControl(ControlElement element,
                            const QStyleOption *option,
                            QPainter *painter, const QWidget *widget) const
{
    switch (element) {
    case CE_CheckBoxLabel:
    {
        if (const QStyleOptionButton *btn = qstyleoption_cast<const QStyleOptionButton *>(option)) {
            uint alignment = visualAlignment(btn->direction, Qt::AlignLeft | Qt::AlignVCenter);

            if (!proxy()->styleHint(SH_UnderlineShortcut, btn, widget))
                alignment |= Qt::TextHideMnemonic;
            //            QPixmap pix;
            QRect textRect = btn->rect;
            //            if (!btn->icon.isNull())
            //            {
            //                pix = btn->icon.pixmap(btn->iconSize, btn->state & State_Enabled ? QIcon::Normal : QIcon::Disabled);
            //                proxy()->drawItemPixmap(painter, btn->rect, alignment, pix);
            //                if (btn->direction == Qt::RightToLeft)
            //                {
            //                    textRect.setRight(textRect.right() - btn->iconSize.width() - 10);
            //                }
            //                else
            //                {
            //                    textRect.setLeft(textRect.left() + btn->iconSize.width() + 10);
            //                }
            //            }

            textRect.setTopLeft(textRect.topLeft() + QPoint(15, 0));
            if (!btn->text.isEmpty()){
                proxy()->drawItemText(painter, textRect, alignment | Qt::TextShowMnemonic,
                                      btn->palette, btn->state & State_Enabled, btn->text, QPalette::WindowText);
            }
        }
    }
        break;
    case CE_RadioButton:
    case CE_CheckBox:
    {
        if (const QStyleOptionButton *btn = qstyleoption_cast<const QStyleOptionButton *>(option))
        {
            bool isRadio = (element == CE_RadioButton);
            QStyleOptionButton subopt = *btn;
            subopt.rect = subElementRect(isRadio ? SE_RadioButtonIndicator
                                                 : SE_CheckBoxIndicator, btn, widget);
            proxy()->drawPrimitive(isRadio ? PE_IndicatorRadioButton : PE_IndicatorCheckBox,
                                   &subopt, painter, widget);
            subopt.rect = subElementRect(isRadio ? SE_RadioButtonContents
                                                 : SE_CheckBoxContents, btn, widget);
            proxy()->drawControl(isRadio ? CE_RadioButtonLabel : CE_CheckBoxLabel, &subopt, painter, widget);
        }
    }
        break;
    case CE_HeaderSection:
    {
        if (const QStyleOptionHeader *header = qstyleoption_cast<const QStyleOptionHeader *>(option))
        {
            QColor gradientStartColor(255, 255, 255);
            QColor gradientStopColor(FocusColor());
            QColor borderColor = option->palette.background().color().darker(178);
            QColor alphaCornerColor;
            if (widget)
            {
                alphaCornerColor = mergedColors(option->palette.color(widget->backgroundRole()), borderColor);
            }
            else
            {
                alphaCornerColor = mergedColors(option->palette.background().color(), borderColor);
            }
            QString pixmapName = uniqueName(QLatin1String("headersection"), option, option->rect.size());
            pixmapName += QString::number(- int(header->position));
            pixmapName += QString::number(- int(header->orientation));
            QPixmap cache;
            cache = QPixmap(option->rect.size());
            cache.fill(Qt::white);
            QRect pixmapRect(0, 0, option->rect.width(), option->rect.height());
            QPainter cachePainter(&cache);
//            bool sunken = (header->state & State_Enabled) && (header->state & State_Sunken);

//            QColor headerGradientStart = sunken ? option->palette.background().color().darker(114) : gradientStartColor;
//            QColor headerGradientStop = sunken ? option->palette.background().color().darker(106) : gradientStopColor;

//            QColor lightLine = sunken ? option->palette.background().color().darker(118) : gradientStartColor;
//            QColor darkLine = sunken ? option->palette.background().color().darker(110) : gradientStopColor.darker(105);

            QColor headerGradientStart = gradientStartColor;
            QColor headerGradientStop = gradientStopColor;

            QColor lightLine = gradientStartColor;
            QColor darkLine = gradientStopColor.darker(105);


            qt_plastique_draw_gradient(&cachePainter, pixmapRect,
                                       headerGradientStart, headerGradientStop);

            cachePainter.setPen(borderColor);
            cachePainter.drawRect(pixmapRect.adjusted(0, 0, -1, -1));
            cachePainter.setPen(alphaCornerColor);

            const QPoint points[4] =
            {
                pixmapRect.topLeft(), pixmapRect.topRight(),
                pixmapRect.bottomLeft(), pixmapRect.bottomRight()
            };
            cachePainter.drawPoints(points, 4);

            QLine lines[2];

            // inner lines
            cachePainter.setPen(lightLine);
            lines[0] = QLine(pixmapRect.left() + 2, pixmapRect.top() + 1,
                             pixmapRect.right() - 2, pixmapRect.top() + 1);
            lines[1] = QLine(pixmapRect.left() + 1, pixmapRect.top() + 2,
                             pixmapRect.left() + 1, pixmapRect.bottom() - 2);
            cachePainter.drawLines(lines, 2);

            cachePainter.setPen(darkLine);
            lines[0] = QLine(pixmapRect.left() + 2, pixmapRect.bottom() - 1,
                             pixmapRect.right() - 2, pixmapRect.bottom() - 1);
            lines[1] = QLine(pixmapRect.right() - 1, pixmapRect.bottom() - 2,
                             pixmapRect.right() - 1, pixmapRect.top() + 2);
            cachePainter.drawLines(lines, 2);

            cachePainter.end();
            QPixmapCache::insert(pixmapName, cache);

            painter->drawPixmap(option->rect.topLeft(), cache);

        }
    }
        break;
    default:
    {
        QPlastiqueStyle::drawControl(element,
                                     option,
                                     painter,
                                     widget);
    }
        break;
    }
}

void ICHCStyle::drawComplexControl(ComplexControl control,
                                   const QStyleOptionComplex *option,
                                   QPainter *painter, const QWidget *widget) const
{
    switch (control)
    {
    case QStyle::CC_ComboBox:
    {
        if (const QStyleOptionComboBox *comboBox = qstyleoption_cast<const QStyleOptionComboBox *>(option))
        {
            bool sunken = comboBox->state & State_On; // play dead if combobox has no items
            bool reverse = comboBox->direction == Qt::RightToLeft;
            int menuButtonWidth = 16;
            int xoffset = sunken ? (reverse ? -1 : 1) : 0;
            int yoffset = sunken ? 1 : 0;
            QRect rect = comboBox->rect;
            QPen oldPen = painter->pen();
            // Fill
            if (comboBox->editable)
            {
                QPlastiqueStyle::drawComplexControl(control,
                                                    option,
                                                    painter,
                                                    widget);
                return;
            }
            else
            {
                // Start with a standard panel button fill
                QStyleOptionButton buttonOption;
                buttonOption.QStyleOption::operator=(*comboBox);
                if (!sunken)
                {
                    buttonOption.state &= ~State_Sunken;
                }
                proxy()->drawPrimitive(PE_PanelButtonCommand, &buttonOption, painter, widget);

                // Draw the menu button separator line
                QBrush border = qMapBrushToRect(option->palette.shadow(), rect);
                qBrushSetAlphaF(&border, qreal(0.35));
                painter->setPen(QPen(border, 0));
                if (!reverse)
                {
                    painter->drawLine(rect.right() - menuButtonWidth + xoffset, rect.top() + 1,
                                      rect.right() - menuButtonWidth + xoffset, rect.bottom() - 1);
                } else
                {
                    painter->drawLine(rect.left() + menuButtonWidth + xoffset, rect.top() + 1,
                                      rect.left() + menuButtonWidth + xoffset, rect.bottom() - 1);
                }
            }

            // Draw the little arrow
            if (comboBox->subControls & SC_ComboBoxArrow)
            {
                int left = !reverse ? rect.right() - menuButtonWidth : rect.left();
                int right = !reverse ? rect.right() : rect.left() + menuButtonWidth;
                QRect arrowRect((left + right) / 2 - 3 + xoffset,
                                rect.center().y() - 1 + yoffset, 7, 4);
                painter->setPen(QPen(qMapBrushToRect(option->palette.buttonText(), rect), 0));
                const QLine lines[3] = {
                    QLine(arrowRect.topLeft(), arrowRect.topRight()),
                    QLine(arrowRect.left() + 1, arrowRect.top() + 1,
                    arrowRect.right() - 1, arrowRect.top() + 1),
                    QLine(arrowRect.left() + 2, arrowRect.top() + 2,
                    arrowRect.right() - 2, arrowRect.top() + 2) };
                painter->drawLines(lines, 3);
                painter->drawPoint(arrowRect.center().x(), arrowRect.bottom());
            }
            painter->setPen(oldPen);
        }
    }

        break;
    default:
        QPlastiqueStyle::drawComplexControl(control,
                                            option,
                                            painter,
                                            widget);
        break;
    }
}

void ICHCStyle::InitAppPallete()
{
    QPalette palette;
    QBrush brush(ICHCStyle::FocusColor());
    palette.setBrush(QPalette::Active, QPalette::Highlight, brush);
    palette.setBrush(QPalette::Inactive, QPalette::Highlight, brush);

    QPalette tableViewPalette;
    QBrush brush1(QColor(64, 143, 212, 30));
    tableViewPalette.setBrush(QPalette::Active, QPalette::Base, brush1);
    tableViewPalette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
    QBrush brush2(QColor(187, 213, 234, 30));
    tableViewPalette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush2);
    tableViewPalette.setBrush(QPalette::Active, QPalette::AlternateBase, brush2);

    QPalette scrollBarPalette;
    QBrush brush3(ICHCStyle::FocusColor());
    scrollBarPalette.setBrush(QPalette::Active, QPalette::Button, brush3);


    QPalette tipWidgetPalette;
    tipWidgetPalette.setBrush(QPalette::Active, QPalette::Window, brush);
    tipWidgetPalette.setBrush(QPalette::Inactive, QPalette::Window, brush);

    QApplication::setPalette(palette);
    QApplication::setPalette(tableViewPalette, "QTableView");
    QApplication::setPalette(scrollBarPalette, "QScrollBar");
    QApplication::setPalette(tipWidgetPalette, "ICTipsWidget");
}
