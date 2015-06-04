INCLUDEPATH += $$PWD

HEADERS += \
    hcmaintains/icupdatelogodialog.h \
    hcmaintains/icupdatesystempage.h \
    hcmaintains/icinputdialog.h

SOURCES += \
    hcmaintains/icupdatelogodialog.cpp \
    hcmaintains/icupdatesystempage.cpp \
    hcmaintains/icinputdialog.cpp

FORMS += \
#    hcmaintains/icupdatesystem.ui \
    hcmaintains/icupdatelogodialog.ui \
#    hcmaintains/icupdatesystempage.ui
#    hcmaintains/icupdatesystempage_5.ui
    hcmaintains/icinputdialog.ui


contains(DEFINES, HC_SK_8){
FORMS += $$PWD/icupdatesystempage.ui
}
contains(DEFINES, HC_SK_5){
FORMS += $$PWD/icupdatesystempage_5.ui
}
