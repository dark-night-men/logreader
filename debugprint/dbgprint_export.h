#ifndef DBGPRINT_EXPORT

#include <QtGlobal>
#ifndef Q_OS_WIN
#define DBGPRINT_EXPORT
#elif defined(DBGPRINT_DLL)
#define DBGPRINT_EXPORT Q_DECL_EXPORT
#else
#define DBGPRINT_EXPORT Q_DECL_IMPORT
#endif

#endif // DBGPRINT_EXPORT_H
