#ifndef _gg_iterator_defs_h_
#define _gg_iterator_defs_h_

#include "gg/core/type/enum.h"

namespace gg
{
    enum class iterator_type : uint8
    {
        no_const,
        is_const,
        max
    };
    GG_ENUM(iterator_type);
}

#endif // _gg_iterator_defs_h_
