#ifndef _gg_memory_desc_h_
#define _gg_memory_desc_h_

#if defined(GG_DEBUG)
#include "gg/core/debug/assert.h"
#include "gg/core/memory/memory_defs.h"
#include "gg/core/string/macros.h"
#include "gg/core/string/type/string_ref.h"

namespace gg
{
    static constexpr string_ref const k_memory_owner_mode_descriptors[] = {
        GG_TEXT("is_not_owner"),
        GG_TEXT("is_owner")
    };

    GG_ASSERT_STATIC(
        enums::cast(memory_owner_mode::max) ==
            sizeof(k_memory_owner_mode_descriptors) / sizeof(k_memory_owner_mode_descriptors[0]),
        "descriptor missing for memory_owner_mode enumeration"
    );
}

#endif // GG_DEBUG
#endif // _gg_memory_desc_h_
