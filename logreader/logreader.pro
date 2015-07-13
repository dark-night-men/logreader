TARGET = logreader

CONFIG += debug

TEMPLATE = app

QT += widgets

SOURCES += main.cpp \
           mymodel.cpp \
           logfile.cpp \
           ilogfile.cpp \
           myview.cpp

HEADERS += mymodel.h \
           logfile.h \
           ilogfile.h \
           myview.h

# install
#target.path = $$[QT_INSTALL_EXAMPLES]/widgets/tutorials/modelview/1_readonly
#INSTALLS += target
