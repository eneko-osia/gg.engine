#ifndef _gg_handle_h_
#define _gg_handle_h_

#include "gg/core/type/type_trait.h"

namespace gg
{
    class handle
    {
    public:

        // constructors

        handle(void) noexcept
            : m_handle(nullptr)
        {
        }

        template <typename HANDLE_TYPE>
        handle(HANDLE_TYPE _handle) noexcept
            : m_handle(type::cast_static<void *>(_handle))
        {
        }

        ~handle(void) noexcept = default;

        // operators

        operator bool8() const noexcept{ return !is_null(); }

        // methods

        template <typename HANDLE_TYPE>
        HANDLE_TYPE get(void) const noexcept
        {
            return type::cast_static<HANDLE_TYPE>(m_handle);
        }

        template <typename HANDLE_TYPE>
        void set(HANDLE_TYPE _handle) noexcept
        {
            m_handle = type::cast_static<void *>(_handle);
        }

        // inquiries

        bool8 is_null(void) const noexcept
        {
            return nullptr == m_handle;
        }

    private:

        // attributes

        void * m_handle;
    };
}

#endif // _gg_handle_h_
