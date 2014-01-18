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
FORMS += virtualkeyboarddialog.ui
}
contains(DEFINES, HC_SK_5){
FORMS += virtualkeyboarddialog_5.ui
}
