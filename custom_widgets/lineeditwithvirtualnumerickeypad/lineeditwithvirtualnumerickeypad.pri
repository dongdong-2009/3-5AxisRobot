INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    custom_widgets/lineeditwithvirtualnumerickeypad/virtualnumerickeypaddialog.h \
    custom_widgets/lineeditwithvirtualnumerickeypad/icparameterconversion.h \
    custom_widgets/lineeditwithvirtualnumerickeypad/iclineeditwithvirtualnumerickeypad.h \
    custom_widgets/lineeditwithvirtualnumerickeypad/icfunctionsettingpagename.h

SOURCES += \
    custom_widgets/lineeditwithvirtualnumerickeypad/virtualnumerickeypaddialog.cpp \
    custom_widgets/lineeditwithvirtualnumerickeypad/icparameterconversion.cpp \
    custom_widgets/lineeditwithvirtualnumerickeypad/iclineeditwithvirtualnumerickeypad.cpp \
    custom_widgets/lineeditwithvirtualnumerickeypad/icfunctionsettingpagename.cpp

#FORMS +=
#    custom_widgets/lineeditwithvirtualnumerickeypad/virtualnumerickeypaddialog.ui \
#    custom_widgets/lineeditwithvirtualnumerickeypad/virtualnumerickeypaddialog_5.ui

RESOURCES += \
    resource.qrc
contains(DEFINES, HC_SK_8){
FORMS += $$PWD/virtualnumerickeypaddialog.ui
}
contains(DEFINES, HC_SK_5){
FORMS += $$PWD/virtualnumerickeypaddialog_5.ui
}
