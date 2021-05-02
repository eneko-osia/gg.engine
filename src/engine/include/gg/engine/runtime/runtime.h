#ifndef _gg_engine_runtime_h_
#define _gg_engine_runtime_h_

#include "gg/engine/runtime/runtime_platform.h"

namespace gg::engine
{
    class runtime final: public runtime_platform
    {
    public:

        // constructors
        runtime(app::data const & data) noexcept;
    };
}

#endif // _gg_engine_runtime_h_
