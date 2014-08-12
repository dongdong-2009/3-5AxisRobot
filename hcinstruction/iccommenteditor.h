#ifndef ICCOMMENTEDITOR_H
#define ICCOMMENTEDITOR_H

#include <QWidget>

namespace Ui {
class ICCommentEditor;
}

class ICCommentEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ICCommentEditor(QWidget *parent = 0);
    ~ICCommentEditor();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ICCommentEditor *ui;
};

#endif // ICCOMMENTEDITOR_H
