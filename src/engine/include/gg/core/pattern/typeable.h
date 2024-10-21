#ifndef _gg_typeable_h_
#define _gg_typeable_h_

#include "gg/core/type/type_trait.h"

namespace gg
{
    template <typename ITEM_TYPE>
    class typeable
    {
    public:

        // item_type definitions

        typedef ITEM_TYPE item_type;

        // constructors

        typeable(void) noexcept = default;
        typeable(typeable const & obj) noexcept = default;
        typeable(typeable && obj) noexcept = default;

        typeable(item_type const & type) noexcept
            : m_type(type)
        {
        }

        typeable(item_type && type) noexcept
            : m_type(type::move(type))
        {
        }

        template <typename TYPE>
        typeable(item_type && type) noexcept
            : m_type(type::forward<TYPE>(type))
        {
        }

        // accessors

        item_type const & get_type(void) const noexcept
        {
            return m_type;
        }

        void set_type(item_type const & type) noexcept
        {
            m_type = type;
        }

        void set_type(item_type && type) noexcept
        {
            m_type = type::move(type);
        }

        template <typename TYPE>
        void set_type(TYPE && type) noexcept
        {
            m_type = type::forward<TYPE>(type);
        }

        // inquiries

        bool8 is_type(item_type const & type) const noexcept
        {
            return m_type == type;
        }

        template <typename TYPE>
        bool8 is_type(TYPE const & type) const noexcept
        {
            return m_type == type;
        }

    protected:

        // constructors

        ~typeable(void) noexcept = default;

    private:

        // attributes

        item_type m_type;
    };
}

#endif // _gg_typeable_h_
