#include (../libs.pri)

TEMPLATE = lib
QT += gui

# For locating the files.
#RESOURCES = cards2.qrc
SOURCES += debugprint.cpp

HEADERS +=  debugprint.h

win32 {
	DEFINES += DBGPRINT_DLL 
}
