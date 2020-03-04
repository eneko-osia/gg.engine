#ifndef _gg_runtime_h_
#define _gg_runtime_h_

// include files

#include "gg/engine/runtime/runtime_platform.h"

// namespace

namespace gg
{
    // class in charge of define a runtime

    class runtime final: public runtime_platform
    {
    public:

        // constructors

        runtime(data const & data) noexcept;
        ~runtime(void) noexcept = default;
    };
}

#endif // _gg_runtime_h_
