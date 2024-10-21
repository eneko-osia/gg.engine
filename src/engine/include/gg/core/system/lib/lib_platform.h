#ifndef _gg_lib_platform_h_
#define _gg_lib_platform_h_

#if defined(GG_MAC)
    #error "Can't include lib platform for mac osx"
#elif defined(GG_LINUX)
    #include "gg/core/system/lib/lib_linux.h"
#elif defined(GG_WINDOWS)
    #include "gg/core/system/lib/lib_windows.h"
#else
    #error "Can't include lib platform for unsupported platform"
#endif

#endif // _gg_lib_platform_h_
