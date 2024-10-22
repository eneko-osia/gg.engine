#ifndef _gg_endian_defs_h_
#define _gg_endian_defs_h_

#include "gg/core/type/enum.h"

namespace gg
{
    enum class endian_mode : uint8
    {
        big_endian,
        little_endian,
        max
    };
    GG_ENUM(endian_mode);
}

#endif // _gg_endian_defs_h_
