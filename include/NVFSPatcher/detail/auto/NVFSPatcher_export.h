
#ifndef NVFSPATCHER_EXPORT_H
#define NVFSPATCHER_EXPORT_H

#ifdef NVFSPATCHER_STATIC_DEFINE
#  define NVFSPATCHER_EXPORT
#  define NVFSPATCHER_NO_EXPORT
#else
#  ifndef NVFSPATCHER_EXPORT
#    ifdef NVFSPatcher_EXPORTS
        /* We are building this library */
#      define NVFSPATCHER_EXPORT 
#    else
        /* We are using this library */
#      define NVFSPATCHER_EXPORT 
#    endif
#  endif

#  ifndef NVFSPATCHER_NO_EXPORT
#    define NVFSPATCHER_NO_EXPORT 
#  endif
#endif

#ifndef NVFSPATCHER_DEPRECATED
#  define NVFSPATCHER_DEPRECATED __declspec(deprecated)
#endif

#ifndef NVFSPATCHER_DEPRECATED_EXPORT
#  define NVFSPATCHER_DEPRECATED_EXPORT NVFSPATCHER_EXPORT NVFSPATCHER_DEPRECATED
#endif

#ifndef NVFSPATCHER_DEPRECATED_NO_EXPORT
#  define NVFSPATCHER_DEPRECATED_NO_EXPORT NVFSPATCHER_NO_EXPORT NVFSPATCHER_DEPRECATED
#endif

/* NOLINTNEXTLINE(readability-avoid-unconditional-preprocessor-if) */
#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef NVFSPATCHER_NO_DEPRECATED
#    define NVFSPATCHER_NO_DEPRECATED
#  endif
#endif

#endif /* NVFSPATCHER_EXPORT_H */
