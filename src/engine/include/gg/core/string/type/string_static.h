#ifndef _gg_string_static_h_
#define _gg_string_static_h_

#include "gg/core/container/array/array_static.h"
#include "gg/core/string/type/string.h"

namespace gg
{
    template <size_type MAX_SIZE = 8>
    class string_static final
    {
    private:

        // type definitions

        typedef array_static<char8, MAX_SIZE> data_type;

    public:

        // type definitions

        typedef typename data_type::item_type       item_type;

        typedef typename data_type::pointer         pointer;
        typedef typename data_type::const_pointer   const_pointer;

        typedef typename data_type::reference       reference;
        typedef typename data_type::const_reference const_reference;

        typedef typename data_type::iterator        iterator;
        typedef typename data_type::const_iterator  const_iterator;

        // constructors

        string_static(void) noexcept
            : m_data()
        {
            set(string::k_empty);
        }

        string_static(string_static const & string) noexcept
            : m_data()
        {
            set(string);
        }

        template <typename STRING_TYPE>
        string_static(STRING_TYPE const & string) noexcept
            : m_data()
        {
            set(string);
        }

        template <typename STRING_TYPE>
        string_static(STRING_TYPE const & string, size_type size) noexcept
            : m_data()
        {
            set(string, size);
        }

        template <typename STRING_TYPE>
        string_static(
            STRING_TYPE const & string,
            size_type idx_start,
            size_type idx_end) noexcept
            : m_data()
        {
            set(string, idx_start, idx_end);
        }

        ~string_static(void) noexcept = default;

        // operators

        reference operator[](size_type idx) noexcept
        {
            GG_ASSERT(idx < size());
            return m_data[idx];
        }

        const_reference operator[](size_type idx) const noexcept
        {
            GG_ASSERT(idx < size());
            return m_data[idx];
        }

        string_static & operator=(const_pointer string) noexcept
        {
            return set(string);
        }

        string_static & operator=(string_static const & string) noexcept
        {
            return set(string);
        }

        template <typename STRING_TYPE>
        string_static & operator=(STRING_TYPE const & string) noexcept
        {
            return set(string);
        }

        bool8 operator==(pointer string) const noexcept
        {
            return *this == type::cast_const<const_pointer>(string);
        }

        bool8 operator==(const_pointer string) const noexcept
        {
            return string::compare(c_str(), string) == 0;
        }

        bool8 operator==(string_static const & string) const noexcept
        {
            return *this == string.c_str();
        }

        template <typename STRING_TYPE>
        bool8 operator==(STRING_TYPE const & string) const noexcept
        {
            return *this == string.c_str();
        }

        bool8 operator!=(const_pointer string) const noexcept
        {
            return !(*this == string);
        }

        bool8 operator!=(string_static const & string) const noexcept
        {
            return !(*this == string);
        }

        template <typename STRING_TYPE>
        bool8 operator!=(STRING_TYPE const & string) const noexcept
        {
            return !(*this == string);
        }

        bool8 operator<(const_pointer string) const noexcept
        {
            return string::compare(c_str(), string) < 0;
        }

        template <typename STRING_TYPE>
        bool8 operator<(STRING_TYPE const & string) const noexcept
        {
            return *this < string.c_str();
        }

        bool8 operator>(const_pointer string) const noexcept
        {
            return string::compare(c_str(), string) > 0;
        }

        template <typename STRING_TYPE>
        bool8 operator>(STRING_TYPE const & string) const noexcept
        {
            return *this > string.c_str();
        }

        // methods

        string_static & append(const_reference character) noexcept
        {
            return insert(size(), character);
        }

        string_static & append(const_pointer string) noexcept
        {
            return insert(size(), string);
        }

        string_static &
        append(const_pointer string, size_type size) noexcept
        {
            return insert(this->size(), string, size);
        }

        string_static &
        append(
            const_pointer string,
            size_type idx_start,
            size_type idx_end) noexcept
        {
            return insert(size(), string, idx_start, idx_end);
        }

        template <typename STRING_TYPE>
        string_static & append(STRING_TYPE const & string) noexcept
        {
            return insert(size(), string);
        }

        template <typename STRING_TYPE>
        string_static &
        append(STRING_TYPE const & string, size_type size) noexcept
        {
            return insert(this->size(), string, size);
        }

        template <typename STRING_TYPE>
        string_static &
        append(
            STRING_TYPE const & string,
            size_type idx_start,
            size_type idx_end) noexcept
        {
            return insert(size(), string, idx_start, idx_end);
        }

        iterator begin(void) noexcept
        {
            return m_data.begin();
        }

        const_iterator begin(void) const noexcept
        {
            return m_data.begin();
        }

        pointer c_str(void) noexcept
        {
            return m_data.data();
        }

        const_pointer c_str(void) const noexcept
        {
            return m_data.data();
        }

        void clear(void) noexcept
        {
            memory::zero(c_str(), size());
        }

        iterator end(void) noexcept
        {
            return begin() + size();
        }

        const_iterator end(void) const noexcept
        {
            return begin() + size();
        }

        string_static & erase(size_type idx, size_type size = 1) noexcept
        {
            GG_ASSERT(idx < this->size());
            size_type cur_size = this->size();
            size_type end_idx = limit::min<size_type>(idx + size, cur_size);
            memory::move(&m_data[idx], &m_data[end_idx], cur_size - end_idx);
            m_data[cur_size - (end_idx - idx)] = '\0';
            return *this;
        }

        size_type find(const_pointer string, size_type idx = 0) const noexcept
        {
            GG_ASSERT(idx < size());
            const_pointer position = string::find(c_str() + idx, string);
            return size_type(position ? (position - c_str()) : string::npos);
        }

        template <typename STRING_TYPE>
        size_type
        find(STRING_TYPE const & string, size_type idx = 0) const noexcept
        {
            return find(string.c_str(), idx);
        }

        string_static &
        insert(size_type idx, const_reference character) noexcept
        {
            return insert(idx, &character, 1);
        }

        string_static & insert(size_type idx, const_pointer string) noexcept
        {
            return insert(idx, string, string::length(string));
        }

        string_static &
        insert(size_type idx, const_pointer string, size_type size) noexcept
        {
            GG_ASSERT(idx <= this->size());
            size_type cur_size = this->size();
            size_type new_size = limit::min<size_type>(cur_size + size, max_size() - 1);
            size_type end_idx = limit::min<size_type>(idx + size, new_size);
            memory::move(&m_data[end_idx], &m_data[idx], new_size - end_idx);
            memory::copy(&m_data[idx], string, end_idx - idx);
            m_data[new_size] = '\0';
            return *this;
        }

        string_static &
        insert(
            size_type idx,
            const_pointer string,
            size_type idx_start,
            size_type idx_end) noexcept
        {
            return insert(idx, string + idx_start, idx_end - idx_start + 1);
        }

        template <typename STRING_TYPE>
        string_static &
        insert(size_type idx, STRING_TYPE const & string) noexcept
        {
            return insert(idx, string.c_str(), string.size());
        }

        template <typename STRING_TYPE>
        string_static & insert(
            size_type idx,
            STRING_TYPE const & string,
            size_type size) noexcept
        {
            return insert(idx, string.c_str(), size);
        }

        template <typename STRING_TYPE>
        string_static &
        insert(
            size_type idx,
            STRING_TYPE const & string,
            size_type idx_start,
            size_type idx_end) noexcept
        {
            return insert(idx, string.c_str(), idx_start, idx_end);
        }

        string_static & set(const_reference character) noexcept
        {
            return set(&character, 1);
        }

        string_static & set(const_pointer string) noexcept
        {
            return set(string, string::length(string));
        }

        string_static & set(const_pointer string, size_type size) noexcept
        {
            size_type new_size = limit::min<size_type>(size, max_size() - 1);
            memory::copy(c_str(), string, new_size);
            m_data[new_size] = '\0';
            return *this;
        }

        string_static & set(
            const_pointer string,
            size_type idx_start,
            size_type idx_end) noexcept
        {
            return set(string + idx_start, idx_end - idx_start + 1);
        }

        string_static & set(string_static const & string) noexcept
        {
            m_data = string.m_data;
            return *this;
        }

        template <typename STRING_TYPE>
        string_static & set(STRING_TYPE const & string) noexcept
        {
            return set(string.c_str(), string.size());
        }

        template <typename STRING_TYPE>
        string_static &
        set(STRING_TYPE const & string, size_type size) noexcept
        {
            return set(string.c_str(), size);
        }

        template <typename STRING_TYPE>
        string_static &
        set(
            STRING_TYPE const & string,
            size_type idx_start,
            size_type idx_end) noexcept
        {
            return set(string.c_str(), idx_start, idx_end);
        }

        constexpr size_type max_size(void) const noexcept
        {
            return m_data.size();
        }

        size_type size(void) const noexcept
        {
            return string::length(c_str());
        }

        size_type
        trim(char8 const * delimiters = GG_TEXT(" \f\n\r\t\v")) noexcept
        {
            return string::trim(c_str(), size(), delimiters);
        }

        // inquiries

        bool8 is_empty(void) const noexcept
        {
            return '\0' == m_data.front();
        }

    private:

        // attributes

        data_type m_data;
    };

    template <size_type MAX_SIZE>
    inline bool8
    operator<(
        typename string_static<MAX_SIZE>::const_pointer lhs,
        string_static<MAX_SIZE> const & rhs) noexcept
    {
        return rhs > lhs;
    }

    template <size_type MAX_SIZE>
    inline bool8
    operator>(
        typename string_static<MAX_SIZE>::const_pointer lhs,
        string_static<MAX_SIZE> const & rhs) noexcept
    {
        return rhs < lhs;
    }

    template <size_type MAX_SIZE>
    inline bool8
    operator==(
        typename string_static<MAX_SIZE>::const_pointer lhs,
        string_static<MAX_SIZE> const & rhs) noexcept
    {
        return rhs == lhs;
    }

    template <size_type MAX_SIZE>
    inline bool8
    operator!=(
        typename string_static<MAX_SIZE>::const_pointer lhs,
        string_static<MAX_SIZE> const & rhs) noexcept
    {
        return rhs != lhs;
    }
}

#endif // _gg_string_static_h_
