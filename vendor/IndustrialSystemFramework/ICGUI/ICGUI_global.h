#ifndef ICGUI_GLOBAL_H
#define ICGUI_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ICGUI_LIBRARY)
#  define ICGUISHARED_EXPORT Q_DECL_EXPORT
#else
#  define ICGUISHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ICGUI_GLOBAL_H
