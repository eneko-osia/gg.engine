#ifndef _gg_endian_desc_h_
#define _gg_endian_desc_h_

#if defined(GG_DEBUG)
#include "gg/core/endian/endian_defs.h"
#include "gg/core/debug/assert.h"
#include "gg/core/string/macros.h"
#include "gg/core/string/type/string_ref.h"

namespace gg
{
    static constexpr string_ref const k_endian_mode_descriptors[] = {
        GG_TEXT("big_endian"),
        GG_TEXT("little_endian")
    };

    GG_ASSERT_STATIC(
        enums::cast(endian_mode::max) ==
            sizeof(k_endian_mode_descriptors) / sizeof(k_endian_mode_descriptors[0]),
        "descriptor missing for endian_mode enumeration"
    );
}

#endif // GG_DEBUG
#endif // _gg_endian_desc_h_
