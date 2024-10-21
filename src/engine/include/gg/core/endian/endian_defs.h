#ifndef _gg_endian_defs_h_
#define _gg_endian_defs_h_

#include "gg/core/type/enum.h"

#if defined(GG_DEBUG)
#include "gg/core/debug/assert.h"
#include "gg/core/string/macro/macro.h"
#endif

namespace gg
{
    enum class endian_mode : uint8
    {
        big_endian,
        little_endian,
        max
    };

    GG_ENUM(endian_mode);

#if defined(GG_DEBUG)
    static constexpr char8 const * k_endian_mode_descriptors[] = {
        GG_TEXT("big_endian"),
        GG_TEXT("little_endian")
    };

    GG_ASSERT_STATIC(
        enums::cast(endian_mode::max) ==
            sizeof(k_endian_mode_descriptors) /
                sizeof(k_endian_mode_descriptors[0]),
        "descriptor missing for endian_mode_descriptors enumeration");
#endif
}

#endif // _gg_endian_defs_h_
