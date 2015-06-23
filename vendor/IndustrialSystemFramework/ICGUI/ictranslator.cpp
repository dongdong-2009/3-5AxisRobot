#include "ictranslator.h"

ICTranslatorPTR ICTranslator::instance_;
ICTranslator::ICTranslator(QApplication* app)
{
    appTranslator_ = new QTranslator();
    widgetsTranslator_ = new QTranslator();
    qtTranslator_ = new QTranslator();
    icframeTranslator_ = new QTranslator();
    app_ = app;
//    app->installTranslator(appTranslator_);
//    app->installTranslator(widgetsTranslator_);
//    app->installTranslator(qtTranslator_);
//    app->installEventFilter(icframeTranslator_);

}

ICTranslator::~ICTranslator()
{
    delete appTranslator_;
    delete widgetsTranslator_;
    delete qtTranslator_;
    delete icframeTranslator_;
}
