
#include <stdlib.h>
#include <ctype.h>

#include <unistd.h>
#include <execinfo.h>
#include <assert.h>

#include <QString>
#include <QDebug>

int stackTraceDepth = 0 ;

void logprint( const QString & s)
{
    qDebug() << s ;
}

void setTraceDepth( int d )
{
    stackTraceDepth = d ;
}

QStringList  stackTrace( int k ) 
{

    logprint( "                                          "  ) ;
    logprint( " >>>> stackTrace started !!!  <<<<"  ) ;

    void *bt[1024];
    int bt_size;
    char **bt_syms;

    bt_syms = 0 ;
    bt_size = 0 ;

    bt_size = backtrace( bt, 1024 );
    bt_syms = backtrace_symbols( bt , bt_size );

    assert( bt_size ) ;
    assert( bt_syms ) ;

    QStringList res ;

    int k1 = k ;

    if ( k1 > bt_size - 1  ) {
        //logprint( "Warning callstack is not so deep !!!"  ) ;
        k1 = bt_size - 1 ;
    }

    //for ( int j = bt_size - 1 - k1 ;  j < bt_size ; ++j ) {
    for ( int j = 0 ;  j < k1 ; ++j ) {

        //        res << qPrintable( QString( *( bt_syms + j) ) ) ;
        res <<  QString( *( bt_syms + j) ) ;
    }

    free( bt_syms ) ;

    return res ;
}

void printStack1( const QStringList & sl  )
{
    foreach ( const QString & s , sl  )
        logprint( s ) ;

    logprint( "                                        "  ) ;
}

void printStack( int x ) 
{
    printStack1( QStringList( stackTrace( x ) ) ) ;
}

void printStack( ) 
{
    printStack1( QStringList( stackTrace( stackTraceDepth ) ) );
}

void printStack( QString comment ) 
{
    logprint( "COMMENT " + comment );
    printStack1( QStringList( stackTrace( stackTraceDepth ) ) );
}

static void dumpRecursive(int level, QObject *object)
{
    if (object) {
        QByteArray buf;
        buf.fill(' ', level / 2 * 8);
        if (level % 2)
            buf += "    ";
        QString name = object->objectName();
        QString flags = QLatin1String("");
#if 0
        if (qApp->focusWidget() == object)
            flags += 'F';
        if (object->isWidgetType()) {
            QWidget * w = (QWidget *)object;
            if (w->isVisible()) {
                QString t("<%1,%2,%3,%4>");
                flags += t.arg(w->x()).arg(w->y()).arg(w->width()).arg(w->height());
            } else {
                flags += 'I';
            }
        }
#endif
        //qDebug("%s%s::%s %s", (const char*)buf, object->metaObject()->className(), name.toLocal8Bit().data(),
        //       flags.toLatin1().data());

        logprint( QString("%1%2::%3 %4 [LEVEL %5]") . arg( (const char*)buf, object->metaObject()->className(), name.toLocal8Bit().data()
                    , flags.toLatin1().data() ) . arg( level ) ); 

        QObjectList children = object->children();
        if (!children.isEmpty()) {
            for (int i = 0; i < children.size(); ++i)
                dumpRecursive(level+1, children.at(i));
        }
    }
}

/*!
  Dumps a tree of children to the debug output.

  This function is useful for debugging, but does nothing if the
  library has been compiled in release mode (i.e. without debugging
  information).

  \sa dumpObjectInfo()
  */

/*
   void QObject::dumpObjectTree()
   {
   dumpRecursive(0, this);
   }
   */

void dumpObjectTree1( QObject * o )
{
    logprint( "dumpObjectTree1"  );
    dumpRecursive(0, o);
}





