INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    virtualkeyboarddialog.h \
    iclineeditwithvirtualkeyboard.h

SOURCES += \
    virtualkeyboarddialog.cpp \
    iclineeditwithvirtualkeyboard.cpp

#FORMS +=
#    virtualkeyboarddialog.ui

contains(DEFINES, HC_SK_8){
FORMS += $$PWD/virtualkeyboarddialog.ui
}
contains(DEFINES, HC_SK_5){
FORMS += $$PWD/virtualkeyboarddialog_5.ui
}
