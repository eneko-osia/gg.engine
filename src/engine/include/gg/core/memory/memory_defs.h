#ifndef _gg_memory_defs_h_
#define _gg_memory_defs_h_

#include "gg/core/type/enum.h"

namespace gg
{
    enum class memory_owner_mode : uint8
    {
        is_not_owner,
        is_owner,
        max
    };
    GG_ENUM(memory_owner_mode);
}

#endif // _gg_memory_defs_h_
