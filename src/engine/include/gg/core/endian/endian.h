#ifndef _gg_endian_h_
#define _gg_endian_h_

#include "gg/core/endian/endian_defs.h"

namespace gg
{
    namespace endian
    {
#if defined(GG_MAC) || defined(GG_LINUX) || defined(GG_WINDOWS)
    static constexpr endian_mode system_mode = endian_mode::little_endian;
#else
    #error "Cannot specify endian mode for unsupported platform"
#endif
    }
}

#endif // _gg_endian_h_
