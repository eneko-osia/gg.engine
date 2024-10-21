#ifndef _gg_nameable_h_
#define _gg_nameable_h_

#include "gg/core/type/type_trait.h"

namespace gg
{
    template <typename NAME_TYPE>
    class nameable
    {
    public:

        // type definitions

        typedef NAME_TYPE name_type;

        // constructors

        nameable(void) noexcept = default;
        nameable(nameable const & obj) noexcept = default;
        nameable(nameable && obj) noexcept = default;

        nameable(name_type const & name) noexcept
            : m_name(name)
        {
        }

        nameable(name_type && name) noexcept
            : m_name(type::move(name))
        {
        }

        template <typename TYPE>
        nameable(TYPE && name) noexcept
            : m_name(type::forward<TYPE>(name))
        {
        }

        // accessors

        name_type const & get_name(void) const noexcept
        {
            return m_name;
        }

        void set_name(name_type const & name) noexcept
        {
            m_name = name;
        }

        void set_name(name_type && name) noexcept
        {
            m_name = type::move(name);
        }

        template <typename TYPE>
        void set_name(TYPE && name) noexcept
        {
            m_name = type::forward<TYPE>(name);
        }

        // inquiries

        bool8 is_named(name_type const & name) const noexcept
        {
            return m_name == name;
        }

        template <typename TYPE>
        bool8 is_named(TYPE const & name) const noexcept
        {
            return m_name == name;
        }

    protected:

        // constructors

        ~nameable(void) noexcept = default;

    private:

        // attributes

        name_type m_name;
    };
}

#endif // _gg_nameable_h_
