#ifndef _gg_runtime_platform_h_
#define _gg_runtime_platform_h_

// include files

#if defined(GG_MAC) || defined(GG_LINUX) || defined(GG_WINDOWS)
    #include "gg/engine/runtime/pc/runtime_pc.h"
#else
    #error "Can't include runtime platform for unsupported platform"
#endif

#endif // _gg_runtime_platform_h_
