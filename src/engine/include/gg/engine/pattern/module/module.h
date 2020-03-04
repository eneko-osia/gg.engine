#ifndef _gg_module_h_
#define _gg_module_h_

// include files

#include "gg/core/type/type.h"

// namespace

namespace gg
{
    // class in charge of define a module

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

        // methods

        virtual void on_finalize(void) noexcept = 0;
        virtual bool8 on_init(void) noexcept = 0;

    private:

        // attributes

        bool8 m_initialized;
    };
}

#endif // _gg_module_h_
