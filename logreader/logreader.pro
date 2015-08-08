TARGET = logreader

CONFIG += debug

TEMPLATE = app

QT += widgets

SOURCES += main.cpp \
           mymodel.cpp \
           logfile.cpp \
           ilogfile.cpp \
           myview.cpp \
           mainwidget.cpp

HEADERS += mymodel.h \
           logfile.h \
           ilogfile.h \
           myview.h \
           mainwidget.h

LIBS += -ldebugprint -L../debugprint
INCLUDEPATH += ../debugprint

# install
#target.path = $$[QT_INSTALL_EXAMPLES]/widgets/tutorials/modelview/1_readonly
#INSTALLS += target
