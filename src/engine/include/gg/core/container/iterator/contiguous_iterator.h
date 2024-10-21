#ifndef _gg_contiguous_iterator_h_
#define _gg_contiguous_iterator_h_

#include "gg/core/container/iterator/iterator_defs.h"
#include "gg/core/type/type_trait.h"
#include <iterator>

namespace gg
{
    template <typename ITEM_TYPE, iterator_type IT_TYPE>
    class contiguous_iterator final
    {
    public:

        // type definitions

        typedef typename type::conditional<
            IT_TYPE == iterator_type::is_const,
            ITEM_TYPE const,
            ITEM_TYPE>
            ::type                                  item_type;

        // stl iterator support type definitions

        typedef std::random_access_iterator_tag     iterator_category;
        typedef item_type                           value_type;
        typedef item_type *                         pointer;
        typedef item_type &                         reference;
        typedef diff_type                           difference_type;

        // constructors

        constexpr contiguous_iterator(pointer ptr) noexcept
            : m_ptr(ptr)
        {
        }

        constexpr contiguous_iterator(
            contiguous_iterator<
                ITEM_TYPE,
                iterator_type::no_const> const & it) noexcept
            : m_ptr(&(*it))
        {
        }

        ~contiguous_iterator(void) noexcept = default;

        // operators

        constexpr reference operator[](size_type idx) const noexcept
        {
            return m_ptr[idx];
        }

        constexpr reference operator*(void) const noexcept
        {
            return *m_ptr;
        }

        constexpr pointer operator->(void) const noexcept
        {
            return m_ptr;
        }

        constexpr contiguous_iterator & operator++(void) noexcept
        {
            ++m_ptr;
            return *this;
        }

        constexpr contiguous_iterator operator++(int32) noexcept
        {
            return contiguous_iterator(m_ptr++);
        }

        constexpr contiguous_iterator & operator--(void) noexcept
        {
            --m_ptr;
            return *this;
        }

        constexpr contiguous_iterator operator--(int32) noexcept
        {
            return contiguous_iterator(m_ptr--);
        }

        constexpr contiguous_iterator operator+(size_type offset) const noexcept
        {
            return contiguous_iterator(m_ptr + offset);
        }

        constexpr contiguous_iterator & operator+=(size_type offset) noexcept
        {
            m_ptr += offset;
            return *this;
        }

        constexpr contiguous_iterator operator-(size_type offset) const noexcept
        {
            return contiguous_iterator(m_ptr - offset);
        }

        constexpr contiguous_iterator & operator-=(size_type offset) noexcept
        {
            m_ptr -= offset;
            return *this;
        }

        constexpr diff_type
        operator-(contiguous_iterator const & it) const noexcept
        {
            return diff_type(m_ptr - it.m_ptr);
        }

        constexpr bool8
        operator==(contiguous_iterator const & it) const noexcept
        {
           return m_ptr == it.m_ptr;
        }

        constexpr bool8
        operator!=(contiguous_iterator const & it) const noexcept
        {
            return !(*this == it);
        }

        constexpr bool8
        operator<(contiguous_iterator const & it) const noexcept
        {
            return m_ptr < it.m_ptr;
        }

        constexpr bool8
        operator<=(contiguous_iterator const & it) const noexcept
        {
            return m_ptr <= it.m_ptr;
        }

        constexpr bool8
        operator>(contiguous_iterator const & it) const noexcept
        {
            return m_ptr > it.m_ptr;
        }

        constexpr bool8
        operator>=(contiguous_iterator const & it) const noexcept
        {
            return m_ptr >= it.m_ptr;
        }

    private:

        // attributes

        pointer m_ptr;
    };
}

#endif // _gg_contiguous_iterator_h_
