#ifndef ICGUI_GLOBAL_H
#define ICGUI_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ICGUI_LIBRARY)
#  define ICGUISHARED_EXPORT Q_DECL_EXPORT
#else
#ifndef Q_WS_WIN32
#  define ICGUISHARED_EXPORT Q_DECL_IMPORT
#else
#  define ICGUISHARED_EXPORT
#endif
#endif

#endif // ICGUI_GLOBAL_H
