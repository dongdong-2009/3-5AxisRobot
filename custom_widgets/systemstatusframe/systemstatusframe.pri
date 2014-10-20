INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/statuslabel.h \
    $$PWD/icsystemstatusframe.h \
    $$PWD/speedstatuslabel.h \
    $$PWD/operatingratiosetdialog.h \
    custom_widgets/systemstatusframe/icclosemoldlabel.h \
    custom_widgets/systemstatusframe/ictunemolddialog.h

SOURCES += \
    $$PWD/statuslabel.cpp \
    $$PWD/icsystemstatusframe.cpp \
    $$PWD/speedstatuslabel.cpp \
    $$PWD/operatingratiosetdialog.cpp \
    custom_widgets/systemstatusframe/icclosemoldlabel.cpp \
    custom_widgets/systemstatusframe/ictunemolddialog.cpp

FORMS += \
    $$PWD/icsystemstatusframe.ui \
    $$PWD/operatingratiosetdialog.ui \
    custom_widgets/systemstatusframe/ictunemolddialog.ui
