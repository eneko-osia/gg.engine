#ifndef _gg_engine_module_h_
#define _gg_engine_module_h_

#include "gg/core/string/macro/macro.h"
#include "gg/core/type/type.h"
#include "gg/crypt/hash/hash.h"

namespace gg::engine
{
    class module
    {
    public:

        // constructors

        module(void) noexcept : m_initialized(false)
        {
        }
        virtual ~module(void) noexcept = default;

        // methods

        void finalize(void) noexcept
        {
            if (m_initialized)
            {
                on_finalize();
                m_initialized = false;
            }
        }

        bool8 init(void) noexcept
        {
            if (!m_initialized)
            {
                m_initialized = on_init();
            }

            return m_initialized;
        }

    private:

        // virtual methods

        virtual void on_finalize(void) noexcept = 0;
        virtual bool8 on_init(void) noexcept = 0;

    private:

        // attributes

        bool8 m_initialized;
    };

    // macros

    #define GG_DECLARE_MODULE_ID(MODULE_TYPE)               \
        static uint32 get_id(void) noexcept                 \
        {                                                   \
            static uint32 const module_id =                 \
                hash::fnv1::generate(GG_TEXT(#MODULE_TYPE));\
            return module_id;                               \
        }
}

#endif // _gg_engine_module_h_
