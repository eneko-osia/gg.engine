#ifndef _gg_array_static_h_
#define _gg_array_static_h_

#include "gg/core/container/iterator/contiguous_iterator.h"
#include "gg/core/memory/memory_buffer_static.h"
#include "gg/core/memory/memory.h"
#include <array>

namespace gg
{
    template <typename ITEM_TYPE, size_type SIZE>
    class array_static final
    {
    public:

        // type definitions

        typedef ITEM_TYPE                           item_type;

        typedef item_type *                         pointer;
        typedef item_type const *                   const_pointer;

        typedef item_type &                         reference;
        typedef item_type const &                   const_reference;

        typedef contiguous_iterator<
            item_type, iterator_type::no_const>     iterator;
        typedef contiguous_iterator<
            item_type, iterator_type::is_const>     const_iterator;

        // constructors

        array_static(void) noexcept
            : m_buffer()
        {
            construct_data();
        }

        array_static(array_static const & array) noexcept
            : m_buffer()
        {
            construct_data(array);
        }

        array_static(const_reference item) noexcept
            : m_buffer()
        {
            construct_data(item);
        }

        ~array_static(void) noexcept
        {
            clear_data();
        }

        // operators

        reference operator[](size_type idx) noexcept
        {
            return m_buffer.template get<item_type>(idx);
        }

        const_reference operator[](size_type idx) const noexcept
        {
            return m_buffer.template get<item_type>(idx);
        }

        array_static & operator=(array_static const & array) noexcept
        {
            GG_ASSERT(this != &array);
            clear_data();
            construct_data(array);
            return *this;
        }

        bool8 operator==(array_static const & array) const noexcept
        {
            return compare_data(array);
        }

        bool8 operator!=(array_static const & array) const noexcept
        {
            return !(*this == array);
        }

        // methods

        reference back(void) noexcept
        {
            return operator[](size() - 1);
        }

        const_reference back(void) const noexcept
        {
            return operator[](size() - 1);
        }

        iterator begin(void) noexcept
        {
            return iterator(data());
        }

        const_iterator begin(void) const noexcept
        {
            return const_iterator(data());
        }

        pointer data(void) noexcept
        {
            return m_buffer.template data<item_type>();
        }

        const_pointer data(void) const noexcept
        {
            return m_buffer.template data<item_type>();
        }

        iterator end(void) noexcept
        {
            return begin() + size();
        }

        const_iterator end(void) const noexcept
        {
            return begin() + size();
        }

        reference front(void) noexcept
        {
            return operator[](0);
        }

        const_reference front(void) const noexcept
        {
            return operator[](0);
        }

        size_type size(void) const noexcept
        {
            return m_buffer.template size<item_type>();
        }

    private:

        // type definitions

        typedef memory_buffer_static<sizeof(item_type) * SIZE> data_type;

        // methods

        template<typename T = array_static>
        type::enable_if_t<type::is_trivially_destructible<typename T::item_type>::value>
        clear_data(void) noexcept
        {
        }

        template<typename T = array_static>
        type::enable_if_t<!type::is_trivially_destructible<typename T::item_type>::value>
        clear_data(void) noexcept
        {
            for (size_type i = 0; i < size(); ++i)
            {
                data()[i].~item_type();
            }
        }

        template<typename T = array_static>
        type::enable_if_t<
            type::is_trivially_constructible<typename T::item_type>::value>
        construct_data(void) noexcept
        {
        }

        template<typename T = array_static>
        type::enable_if_t<
            !type::is_trivially_constructible<typename T::item_type>::value>
        construct_data(void) noexcept
        {
            for (size_type i = 0; i < size(); ++i)
            {
                memory::construct_object(&(data()[i]));
            }
        }

        template<typename T>
        type::enable_if_t<type::is_trivially_copy_constructible<typename T::item_type>::value>
        construct_data(T const & array) noexcept
        {
            memory::copy(data(), array.data(), array.size());
        }

        template<typename T>
        type::enable_if_t<!type::is_trivially_copy_constructible<typename T::item_type>::value>
        construct_data(T const & array) noexcept
        {
            for (size_type i = 0; i < array.size(); ++i)
            {
                memory::construct_object(&(data()[i]), array.data()[i]);
            }
        }

        template<typename T = array_static>
        type::enable_if_t<type::is_trivially_copy_constructible<typename T::item_type>::value>
        construct_data(typename T::item_type const & item) noexcept
        {
            for (size_type i = 0; i < size(); ++i)
            {
                memory::copy(&(data()[i]), &item);
            }
        }

        template<typename T = array_static>
        type::enable_if_t<!type::is_trivially_copy_constructible<typename T::item_type>::value>
        construct_data(typename T::item_type const & item) noexcept
        {
            for (size_type i = 0; i < size(); ++i)
            {
                memory::construct_object(&(data()[i]), item);
            }
        }

        template<typename T>
        type::enable_if_t<
            type::is_comparable<typename T::item_type>::value, bool8>
        compare_data(T const & array) const noexcept
        {
            bool8 equals = true;
            for (size_type i = 0; i < array.size() && equals; ++i)
            {
                equals &= (data()[i] == array.data()[i]);
            }
            return equals;
        }

        template<typename T>
        type::enable_if_t<
            !type::is_comparable<typename T::item_type>::value, bool8>
        compare_data(T const & array) const noexcept
        {
            return memory::compare(data(), array.data(), array.size()) == 0;
        }

    private:

        // attributes

        data_type m_buffer;
    };
}

#endif // _gg_array_static_h_
