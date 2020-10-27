#ifndef _gg_engine_module_h_
#define _gg_engine_module_h_

#include "gg/core/hash/hash.h"
#include "gg/core/string/type/string_ref.h"
#include "gg/core/type/type.h"

namespace gg::engine
{
    class module
    {
    public:

        // constructors

        module(void) noexcept = default;
        virtual ~module(void) noexcept = default;

        // methods

        void finalize(void) noexcept
        {
            on_finalize();
        }

        bool8 init(void) noexcept
        {
            bool8 initialized = on_init();
            if (!initialized)
            {
                finalize();
            }
            return initialized;
        }

    private:

        // virtual methods

        virtual void on_finalize(void) noexcept = 0;
        virtual bool8 on_init(void) noexcept = 0;
    };

    // macros

    #define GG_DECLARE_MODULE(MODULE_TYPE)              \
        static uint32 get_id(void) noexcept             \
        {                                               \
            static uint32 const module_id =             \
                gg::hash::fnv1::generate(get_name());   \
            return module_id;                           \
        }                                               \
        static gg::string_ref get_name(void) noexcept   \
        {                                               \
            return GG_TEXT(#MODULE_TYPE);               \
        }
}

#endif // _gg_engine_module_h_
