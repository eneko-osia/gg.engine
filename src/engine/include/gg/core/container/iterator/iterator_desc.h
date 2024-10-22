#ifndef _gg_iterator_desc_h_
#define _gg_iterator_desc_h_

#if defined(GG_DEBUG)
#include "gg/core/container/iterator/iterator_defs.h"
#include "gg/core/debug/assert.h"
#include "gg/core/string/macro/macro.h"
#include "gg/core/string/type/string_ref.h"

namespace gg
{
    static constexpr string_ref const k_iterator_type_descriptors[] = {
        GG_TEXT("no_const"),
        GG_TEXT("is_const")
    };

    GG_ASSERT_STATIC(
        enums::cast(iterator_type::max) ==
            sizeof(k_iterator_type_descriptors) /
                sizeof(k_iterator_type_descriptors[0]),
        "descriptor missing for iterator_type enumeration");
}

#endif // GG_DEBUG
#endif // _gg_iterator_desc_h_
