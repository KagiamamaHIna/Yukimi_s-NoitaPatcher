
#ifndef YNOITAPATCHER_EXPORT_H
#define YNOITAPATCHER_EXPORT_H

#ifdef YNOITAPATCHER_STATIC_DEFINE
#  define YNOITAPATCHER_EXPORT
#  define YNOITAPATCHER_NO_EXPORT
#else
#  ifndef YNOITAPATCHER_EXPORT
#    ifdef YNoitaPatcher_EXPORTS
        /* We are building this library */
#      define YNOITAPATCHER_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define YNOITAPATCHER_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef YNOITAPATCHER_NO_EXPORT
#    define YNOITAPATCHER_NO_EXPORT 
#  endif
#endif

#ifndef YNOITAPATCHER_DEPRECATED
#  define YNOITAPATCHER_DEPRECATED __declspec(deprecated)
#endif

#ifndef YNOITAPATCHER_DEPRECATED_EXPORT
#  define YNOITAPATCHER_DEPRECATED_EXPORT YNOITAPATCHER_EXPORT YNOITAPATCHER_DEPRECATED
#endif

#ifndef YNOITAPATCHER_DEPRECATED_NO_EXPORT
#  define YNOITAPATCHER_DEPRECATED_NO_EXPORT YNOITAPATCHER_NO_EXPORT YNOITAPATCHER_DEPRECATED
#endif

/* NOLINTNEXTLINE(readability-avoid-unconditional-preprocessor-if) */
#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef YNOITAPATCHER_NO_DEPRECATED
#    define YNOITAPATCHER_NO_DEPRECATED
#  endif
#endif

#endif /* YNOITAPATCHER_EXPORT_H */
