#ifndef _gg_engine_plugin_h_
#define _gg_engine_plugin_h_

#include "gg/core/type/type.h"

namespace gg::engine
{
    class plugin
    {
    public:

        // constructors

        virtual ~plugin(void) noexcept = default;

        // virtual methods

        virtual void finalize(void) noexcept = 0;
        virtual bool8 init(void) noexcept = 0;
    };
}

#endif // _gg_engine_plugin_h_
