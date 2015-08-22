INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/statuslabel.h \
    $$PWD/icsystemstatusframe.h \
    $$PWD/speedstatuslabel.h \
    $$PWD/operatingratiosetdialog.h \
    $$PWD/icclosemoldlabel.h \
    $$PWD/ictunemolddialog.h

SOURCES += \
    $$PWD/statuslabel.cpp \
    $$PWD/icsystemstatusframe.cpp \
    $$PWD/speedstatuslabel.cpp \
    $$PWD/operatingratiosetdialog.cpp \
    $$PWD/icclosemoldlabel.cpp \
    $$PWD/ictunemolddialog.cpp

FORMS += \
    icsystemstatusframe.ui \
    operatingratiosetdialog.ui \
    custom_widgets/systemstatusframe/ictunemolddialog.ui
