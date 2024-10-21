#ifndef _gg_string_ref_h_
#define _gg_string_ref_h_

#include "gg/core/container/iterator/contiguous_iterator.h"
#include "gg/core/macro/macro.h"
#include "gg/core/string/type/string.h"

namespace gg
{
    class string_ref final
    {
    public:

        // type definitions

        typedef char8                               item_type;
        typedef item_type *                         pointer;
        typedef item_type const *                   const_pointer;
        typedef item_type const &                   const_reference;
        typedef contiguous_iterator<
            item_type, iterator_type::is_const>     const_iterator;

        // constructors

        constexpr string_ref(void) noexcept
            : m_data()
        {
            set(string::k_empty);
        }

        constexpr string_ref(string_ref const & string) noexcept
            : m_data()
        {
            set(string);
        }

        constexpr string_ref(string_ref && string) noexcept
            : m_data()
        {
            set(type::move(string));
        }

        template <typename STRING_TYPE>
        constexpr string_ref(STRING_TYPE const & string) noexcept
            : m_data()
        {
            set(string);
        }

        ~string_ref(void) noexcept = default;

        // operators

        constexpr const_reference operator[](size_type idx) const noexcept
        {
            GG_ASSERT(idx < size());
            return m_data[idx];
        }

        constexpr string_ref & operator=(const_pointer string) noexcept
        {
            return set(string);
        }

        constexpr string_ref & operator=(string_ref const & string) noexcept
        {
            return set(string);
        }

        constexpr string_ref & operator=(string_ref && string) noexcept
        {
            return set(type::move(string));
        }

        template <typename STRING_TYPE>
        constexpr string_ref & operator=(STRING_TYPE const & string) noexcept
        {
            return set(string);
        }

        constexpr bool8 operator==(pointer string) const noexcept
        {
            return *this == type::cast_const<const_pointer>(string);
        }

        constexpr bool8 operator==(const_pointer string) const noexcept
        {
            return string::compare(c_str(), string) == 0;
        }

        constexpr bool8 operator==(string_ref const & string) const noexcept
        {
            return *this == string.c_str();
        }

        template <typename STRING_TYPE>
        constexpr bool8 operator==(STRING_TYPE const & string) const noexcept
        {
            return *this == string.c_str();
        }

        constexpr bool8 operator!=(const_pointer string) const noexcept
        {
            return !(*this == string);
        }

        constexpr bool8 operator!=(string_ref const & string) const noexcept
        {
            return !(*this == string);
        }

        template <typename STRING_TYPE>
        constexpr bool8 operator!=(STRING_TYPE const & string) const noexcept
        {
            return !(*this == string);
        }

        constexpr bool8 operator<(const_pointer string) const noexcept
        {
            return string::compare(c_str(), string) < 0;
        }

        template <typename STRING_TYPE>
        constexpr bool8 operator<(STRING_TYPE const & string) const noexcept
        {
            return *this < string.c_str();
        }

        constexpr bool8 operator>(const_pointer string) const noexcept
        {
            return string::compare(c_str(), string) > 0;
        }

        template <typename STRING_TYPE>
        constexpr bool8 operator>(STRING_TYPE const & string) const noexcept
        {
            return *this > string.c_str();
        }

        // methods

        constexpr const_iterator begin(void) const noexcept
        {
            return const_iterator(c_str());
        }

        constexpr const_pointer c_str(void) const noexcept
        {
            return m_data;
        }

        constexpr void clear(void) noexcept
        {
            m_data = string::k_empty;
        }

        constexpr const_iterator end(void) const noexcept
        {
            return begin() + size();
        }

        constexpr size_type
        find(const_pointer string, size_type idx = 0) const noexcept
        {
            GG_ASSERT(idx < size());
            const_pointer position = string::find(c_str() + idx, string);
            return size_type(position ? (position - c_str()) : string::npos);
        }

        template <typename STRING_TYPE>
        constexpr size_type
        find(STRING_TYPE const & string, size_type idx = 0) const noexcept
        {
            return find(string.c_str(), idx);
        }

        constexpr string_ref & set(char8 * string) noexcept
        {
            return set(type::cast_const<const_pointer>(string));
        }

        constexpr string_ref & set(const_pointer string) noexcept
        {
            m_data = string;
            return *this;
        }

        constexpr string_ref & set(string_ref const & string) noexcept
        {
            GG_ASSERT(this != &string);
            m_data = string.m_data;
            return *this;
        }

        constexpr string_ref & set(string_ref && string) noexcept
        {
            GG_ASSERT(this != &string);
            m_data = type::move(string.m_data);
            string.m_data = string::k_empty;
            return *this;
        }

        template <typename STRING_TYPE>
        constexpr string_ref & set(STRING_TYPE const & string) noexcept
        {
            return set(string.c_str());
        }

        constexpr size_type size(void) const noexcept
        {
            return string::length(c_str());
        }

        // inquiries

        constexpr bool8 is_empty(void) const noexcept
        {
            return ('\0' == *c_str());
        }

    private:

        // attributes

        const_pointer m_data;
    };

    inline constexpr bool8
    operator<(string_ref::const_pointer lhs, string_ref const & rhs)
    {
        return rhs > lhs;
    }

    inline constexpr bool8
    operator>(string_ref::const_pointer lhs, string_ref const & rhs)
    {
        return rhs < lhs;
    }

    inline constexpr bool8
    operator==(string_ref::const_pointer lhs, string_ref const & rhs)
    {
        return rhs == lhs;
    }

    inline constexpr bool8
    operator!=(string_ref::const_pointer lhs, string_ref const & rhs)
    {
        return rhs != lhs;
    }
}

#endif // _gg_string_ref_h_
