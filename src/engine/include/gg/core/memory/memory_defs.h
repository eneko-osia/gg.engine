#ifndef _gg_memory_defs_h_
#define _gg_memory_defs_h_

#include "gg/core/type/enum.h"

#if defined(GG_DEBUG)
#include "gg/core/debug/assert.h"
#include "gg/core/string/macro/macro.h"
#endif

namespace gg
{
    enum class memory_owner_mode : uint8
    {
        is_not_owner,
        is_owner,
        max
    };

    GG_ENUM(memory_owner_mode);

#if defined(GG_DEBUG)
    static constexpr char8 const * k_memory_owner_mode_descriptors[] = {
        GG_TEXT("is_not_owner"),
        GG_TEXT("is_owner")
    };

    GG_ASSERT_STATIC(
        enums::cast(memory_owner_mode::max) ==
            sizeof(k_memory_owner_mode_descriptors) /
                sizeof(k_memory_owner_mode_descriptors[0]),
        "descriptor missing for memory_owner_mode enumeration");
#endif
}

#endif // _gg_memory_defs_h_
