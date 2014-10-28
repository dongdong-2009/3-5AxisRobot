INCLUDEPATH += $$PWD

HEADERS += \
    hcmaintains/icupdatelogodialog.h \
    hcmaintains/icupdatesystempage.h

SOURCES += \
    hcmaintains/icupdatelogodialog.cpp \
    hcmaintains/icupdatesystempage.cpp

FORMS += \
#    hcmaintains/icupdatesystem.ui \
    hcmaintains/icupdatelogodialog.ui \
#    hcmaintains/icupdatesystempage.ui
#    hcmaintains/icupdatesystempage_5.ui


contains(DEFINES, HC_SK_8){
FORMS += $$PWD/icupdatesystempage.ui
}
contains(DEFINES, HC_SK_5){
FORMS += $$PWD/icupdatesystempage_5.ui
}
