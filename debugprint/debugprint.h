#ifndef DEBUGPRINTINC_H
#define DEBUGPRINTINC_H

#include "dbgprint_export.h"
#include <QObject>

DBGPRINT_EXPORT void logprint( const QString & s);
DBGPRINT_EXPORT QStringList stackTrace( int k ) ;
DBGPRINT_EXPORT void printStack( const QStringList & sl ) ;
DBGPRINT_EXPORT void printStack( int x ) ;
DBGPRINT_EXPORT void printStack( ) ;
DBGPRINT_EXPORT void printStack( QString comment ) ;
DBGPRINT_EXPORT void setTraceDepth( int x ) ;
DBGPRINT_EXPORT void dumpObjectTree1( QObject * o ) ;



#endif /* def DEBUGPRINTINC_H */
