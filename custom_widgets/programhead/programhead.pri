INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    custom_widgets/programhead/icprogramheadframe.h \
    custom_widgets/programhead/passwdlevellabel.h \
    custom_widgets/programhead/passworddialog.h

SOURCES += \
    custom_widgets/programhead/icprogramheadframe.cpp \
    custom_widgets/programhead/passwdlevellabel.cpp \
    custom_widgets/programhead/passworddialog.cpp

FORMS += \
    custom_widgets/programhead/icprogramheadframe.ui
#    custom_widgets/programhead/passworddialog.ui \
#    custom_widgets/programhead/passworddialog_5.ui

RESOURCES += \
    resource.qrc

contains(DEFINES, HC_SK_8){
FORMS += passworddialog.ui
}
contains(DEFINES, HC_SK_5){
FORMS += passworddialog_5.ui
}
