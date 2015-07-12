TARGET = logreader

CONFIG += debug

TEMPLATE = app

QT += widgets

SOURCES += main.cpp \
           mymodel.cpp \
           logfile.cpp

HEADERS += mymodel.h \
           logfile.h


# install
#target.path = $$[QT_INSTALL_EXAMPLES]/widgets/tutorials/modelview/1_readonly
#INSTALLS += target
