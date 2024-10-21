#ifndef _gg_stream_defs_h_
#define _gg_stream_defs_h_

#include "gg/core/type/enum.h"

#if defined(GG_DEBUG)
#include "gg/core/debug/assert.h"
#include "gg/core/string/macro/macro.h"
#endif

namespace gg
{
    enum class stream_mode : uint8
    {
        binary,
        text,
        max
    };

    GG_ENUM(stream_mode);

#if defined(GG_DEBUG)
    static constexpr char8 const * k_stream_mode_descriptors[] = {
        GG_TEXT("binary"),
        GG_TEXT("text")
    };

    GG_ASSERT_STATIC(
        enums::cast(stream_mode::max) ==
            sizeof(k_stream_mode_descriptors) /
                sizeof(k_stream_mode_descriptors[0]),
        "descriptor missing for stream_mode enumeration");
#endif
}

#endif // _gg_stream_defs_h_
