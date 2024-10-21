#ifndef _gg_sizeable_h_
#define _gg_sizeable_h_

// include files

#include "gg/core/type/type_trait.h"

// namespace

namespace gg
{
    // class in charge of define a sizeable object

    template <typename SIZE_TYPE>
    class sizeable
    {
    public:

        // type definitions

        typedef SIZE_TYPE size_type;

        // constructors

        sizeable(void) noexcept = default;
        sizeable(sizeable const & obj) noexcept = default;
        sizeable(sizeable && obj) noexcept = default;

        sizeable(size_type const & height, size_type const & width) noexcept
            : m_height(height)
            , m_width(width)
        {
        }

        sizeable(size_type && height, size_type && width) noexcept
            : m_height(type::move(height))
            , m_width(type::move(width))
        {
        }

        // accessors

        size_type const & get_height(void) const noexcept
        {
            return m_height;
        }

        void set_height(size_type const & height) noexcept
        {
            m_height = height;
        }

        void set_height(size_type && height) noexcept
        {
            m_height = type::move(height);
        }

        template <typename TYPE>
        void set_height(TYPE && height) noexcept
        {
            m_height = type::forward<TYPE>(height);
        }

        size_type const & get_width(void) const noexcept
        {
            return m_width;
        }

        void set_width(size_type const & width) noexcept
        {
            m_width = width;
        }

        void set_width(size_type && width) noexcept
        {
            m_width = type::move(width);
        }

        template <typename TYPE>
        void set_width(TYPE && width) noexcept
        {
            m_width = type::forward<TYPE>(width);
        }

        // inquiries

        bool8
        is_sized(size_type const & height, size_type const & width) const noexcept
        {
            return m_height == height && m_width == width;
        }

        template <typename TYPE>
        bool8 is_sized(TYPE const & height, TYPE const & width) const noexcept
        {
            return m_height == height && m_width == width;
        }

    protected:

        // constructors

        ~sizeable(void) noexcept = default;

    private:

        // attributes

        size_type m_height;
        size_type m_width;
    };
}

#endif // _gg_sizeable_h_
