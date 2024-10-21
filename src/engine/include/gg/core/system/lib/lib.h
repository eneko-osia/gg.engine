#ifndef _gg_lib_h_
#define _gg_lib_h_

#include "gg/core/system/lib/lib_platform.h"

namespace gg
{
    class lib final : public lib_platform
    {
    public:

        // constructors

        lib(void) noexcept = default;
        ~lib(void) noexcept = default;
    };
}

#endif // _gg_lib_h_
