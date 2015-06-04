#ifndef ICGUIUTILITY_H
#define ICGUIUTILITY_H

#include <QKeySequence>
#include <QAbstractButton>
#include <QComboBox>
#include <QList>

static inline void ResetButtonTextWithShortcut(QAbstractButton* btn, const QString& newText)
{
    QKeySequence ks = btn->shortcut();
    btn->setText(newText);
    btn->setShortcut(ks);
}

static inline QList<int> BeginResetComboBoxesText(QList<QComboBox*>& boxes)
{
    QList<int> ret;
    for(int i = 0; i != boxes.size(); ++i)
    {
        boxes[i]->blockSignals(true);
        ret.append(boxes.at(i)->currentIndex());
    }
    return ret;
}

static inline void EndResetComboBoxesText(QList<QComboBox*>& boxes, const QList<int> &indexs)
{
    for(int i = 0; i != boxes.size(); ++i)
    {
        boxes[i]->setCurrentIndex(indexs.at(i));
        boxes[i]->blockSignals(false);
    }
}

#endif // ICGUIUTILITY_H
