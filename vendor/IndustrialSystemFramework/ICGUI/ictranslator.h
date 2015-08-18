#ifndef ICTRANSLATOR_H
#define ICTRANSLATOR_H

#include <QTranslator>
#include <QSharedPointer>
#include <QApplication>
class ICTranslator;
typedef QSharedPointer<ICTranslator> ICTranslatorPTR;
class ICTranslator
{
public:
    virtual ~ICTranslator();
    static ICTranslatorPTR Instance(QApplication* app)
    {
        if(instance_.isNull())
        {
            instance_ = ICTranslatorPTR(new ICTranslator(app));
        }
        return instance_;
    }

    void LoadCustomWidgetsTranslator(const QString& path) { widgetsTranslator_->load(path); app_->installTranslator(widgetsTranslator_); }
    void LoadQtTranslator(const QString& path) { qtTranslator_->load(path); app_->installTranslator(qtTranslator_);}
    void LoadIndustrialFrameworkTranslator(const QString& path) { icframeTranslator_->load(path); app_->installTranslator(icframeTranslator_);}
    void LoadAppTranslator(const QString& path) { appTranslator_->load(path); app_->installTranslator(appTranslator_);}


protected:
    ICTranslator(QApplication* app);
private:
    QTranslator *appTranslator_;
    QTranslator *widgetsTranslator_;
    QTranslator *qtTranslator_;
    QTranslator *icframeTranslator_;
    static ICTranslatorPTR instance_;
    QApplication *app_;
};

#endif // ICTRANSLATOR_H
