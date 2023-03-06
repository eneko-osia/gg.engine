#ifndef _gg_engine_game_state_defs_h_
#define _gg_engine_game_state_defs_h_

#include "gg/core/type/enum.h"

#if defined(GG_DEBUG)
#include "gg/core/debug/assert.h"
#include "gg/core/string/macro/macro.h"
#endif

namespace gg::engine
{
    enum class completion_type : uint8
    {
        error,
        success,
        uncompleted,
        max
    };
    GG_ENUM(completion_type);

    static constexpr uint32 k_no_param = 0;

#if defined(GG_DEBUG)
    static constexpr char8 const * k_completion_type_descriptors[] = {
        GG_TEXT("error"),
        GG_TEXT("success"),
        GG_TEXT("uncompleted")
    };

    GG_ASSERT_STATIC(
        enums::cast(completion_type::max) ==
            sizeof(k_completion_type_descriptors) /
                sizeof(k_completion_type_descriptors[0]),
        "descriptor missing for completion_type enumeration");
#endif
}

#endif // _gg_engine_game_state_defs_h_
