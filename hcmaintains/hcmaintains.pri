INCLUDEPATH += $$PWD

HEADERS += \
    hcmaintains/icupdatesystem.h \
    hcmaintains/icupdatelogodialog.h

SOURCES += \
    hcmaintains/icupdatesystem.cpp \
    hcmaintains/icupdatelogodialog.cpp

FORMS += \
#    hcmaintains/icupdatesystem.ui \
    hcmaintains/icupdatelogodialog.ui \


contains(DEFINES, HC_SK_8){
FORMS +=  hcmaintains/icupdatesystem.ui
}
contains(DEFINES, HC_SK_5){
FORMS +=  hcmaintains/icupdatesystem_5.ui
}
