#ifndef _gg_number_h_
#define _gg_number_h_

#include "gg/core/debug/assert.h"
#include "gg/core/type/type_trait.h"

namespace gg
{
    template <typename ACTUAL_TYPE, typename STORAGE_TYPE>
    class number
    {
    public:

        // type definitions

        typedef ACTUAL_TYPE actual_type;
        typedef STORAGE_TYPE storage_type;

        // static asserts

        GG_ASSERT_STATIC(
            type::is_pod<storage_type>::value,
            "storage_type is not a pod type"
        );

        GG_ASSERT_STATIC(
            !type::is_pointer<actual_type>::value,
            "pointer actual_type is not allowed"
        );

        GG_ASSERT_STATIC(
            !type::is_pointer<storage_type>::value,
            "pointer storage_type is not allowed"
        );

        // operators

        actual_type & operator+(void) noexcept
        {
            return *type::cast_static<actual_type *>(this);
        }

        actual_type operator+(actual_type const & value) const noexcept
        {
            return actual_type(m_value + value.m_value);
        }

        actual_type & operator+=(actual_type const & value) noexcept
        {
            m_value += value.m_value;
            return *type::cast_static<actual_type *>(this);
        }

        actual_type & operator-(void) noexcept
        {
            m_value = -m_value;
            return *type::cast_static<actual_type *>(this);
        }

        actual_type operator-(actual_type const & value) const noexcept
        {
            return actual_type(m_value - value.m_value);
        }

        actual_type & operator-=(actual_type const & value) noexcept
        {
            m_value -= value.m_value;
            return *type::cast_static<actual_type *>(this);
        }

        actual_type operator*(actual_type const & value) const noexcept
        {
            return actual_type(m_value * value.m_value);
        }

        actual_type & operator*=(actual_type const & value) noexcept
        {
            m_value *= value.m_value;
            return *type::cast_static<actual_type *>(this);
        }

        actual_type operator/(actual_type const & value) const noexcept
        {
            return actual_type(m_value / value.m_value);
        }

        actual_type & operator/=(actual_type const & value) noexcept
        {
            m_value /= value.m_value;
            return *type::cast_static<actual_type *>(this);
        }

        actual_type & operator=(actual_type const & value) noexcept
        {
            m_value = value.m_value;
            return *type::cast_static<actual_type *>(this);
        }

        bool8 operator==(actual_type const & value) const noexcept
        {
            return m_value == value.m_value;
        }

        bool8 operator!=(actual_type const & value) const noexcept
        {
            return m_value != value.m_value;
        }

        bool8 operator<(actual_type const & value) const noexcept
        {
            return m_value < value.m_value;
        }

        bool8 operator<=(actual_type const & value) const noexcept
        {
            return m_value <= value.m_value;
        }

        bool8 operator>(actual_type const & value) const noexcept
        {
            return m_value > value.m_value;
        }

        bool8 operator>=(actual_type const & value) const noexcept
        {
            return m_value >= value.m_value;
        }

        // methods

        storage_type get(void) const noexcept
        {
            return m_value;
        }

    protected:

        // constructors

        number(void) noexcept = default;
        number(storage_type && value) noexcept : m_value(type::move(value))
        {
        }
        ~number(void) noexcept = default;

    private:

        // attributes

        storage_type m_value;
    };
}

#endif // _gg_number_h_
