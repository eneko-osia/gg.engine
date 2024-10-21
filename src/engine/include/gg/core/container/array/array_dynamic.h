#ifndef _gg_array_dynamic_h_
#define _gg_array_dynamic_h_

#include "gg/core/container/iterator/contiguous_iterator.h"
#include "gg/core/macro/macro.h"
#include "gg/core/memory/memory_buffer_dynamic.h"
#include "gg/core/type/limit.h"

namespace gg
{
    template <typename ITEM_TYPE>
    class array_dynamic final
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

        typedef item_type &&                        rvalue_reference;

        // constructors

        array_dynamic(void) noexcept
            : m_buffer()
            , m_size(0)
        {
        }

        array_dynamic(array_dynamic const & array) noexcept
            : m_buffer()
            , m_size(0)
        {
            allocate(array.size());
            construct_data(array);
            m_size = array.size();
        }

        array_dynamic(array_dynamic && array) noexcept
            : m_buffer(type::move(array.m_buffer))
            , m_size(type::move(array.m_size))
        {
            array.m_size = 0;
        }

        array_dynamic(const_reference item, size_type size) noexcept
            : m_buffer()
            , m_size(0)
        {
            allocate(size);
            construct_data(end(), item, size);
            m_size = size;
        }

        ~array_dynamic(void) noexcept
        {
            clear_data();
        }

        // operators

        reference operator[](size_type idx) noexcept
        {
            GG_ASSERT(idx < size());
            return m_buffer.get<item_type>(idx);
        }

        const_reference operator[](size_type idx) const noexcept
        {
            GG_ASSERT(idx < size());
            return m_buffer.get<item_type>(idx);
        }

        array_dynamic & operator=(array_dynamic const & array) noexcept
        {
            GG_ASSERT(this != &array);
            clear_data();
            reallocate_if_needed(array.size());
            construct_data(array);
            m_size = array.size();
            return *this;
        }

        array_dynamic & operator=(array_dynamic && array) noexcept
        {
            GG_ASSERT(this != &array);
            clear_data();
            m_buffer = type::move(array.m_buffer);
            m_size = type::move(array.m_size);
            array.m_size = 0;
            return *this;
        }

        bool operator==(array_dynamic const & array) const noexcept
        {
            GG_RETURN_FALSE_IF(size() != array.size());
            return compare_data(array);
        }

        bool operator!=(array_dynamic const & array) const noexcept
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

        void clear(void) noexcept
        {
            clear_data();
            m_size = 0;
        }

        pointer data(void) noexcept
        {
            return m_buffer.data<item_type>();
        }

        const_pointer data(void) const noexcept
        {
            return m_buffer.data<item_type>();
        }

        template <typename... ARGS>
        reference emplace(size_type idx, ARGS &&... args) noexcept
        {
            GG_ASSERT(idx <= size());
            reallocate_if_needed();
            iterator it = (begin() + idx);
            memory::move(&(*(it + 1)), &(*it), (size() - idx));
            memory::construct_object(&(*it), type::forward<ARGS>(args)...);
            ++m_size;
            return *it;
        }

        template <typename... ARGS>
        reference emplace(const_iterator cit, ARGS &&... args) noexcept
        {
            return emplace(cit - begin(), type::forward<ARGS>(args)...);
        }

        template <typename... ARGS>
        reference emplace_back(ARGS &&... args) noexcept
        {
            reallocate_if_needed();
            iterator it = end();
            memory::construct_object(&(*it), type::forward<ARGS>(args)...);
            ++m_size;
            return *it;
        }

        iterator end(void) noexcept
        {
            return begin() + size();
        }

        const_iterator end(void) const noexcept
        {
            return begin() + size();
        }

        iterator erase(size_type idx) noexcept
        {
            return erase(idx, idx + 1);
        }

        iterator erase(size_type idx_start, size_type idx_end) noexcept
        {
            GG_ASSERT(idx_start < size());
            GG_ASSERT(idx_end <= size());
            iterator it_start = (begin() + idx_start);
            iterator it_end = (begin() + idx_end);
            clear_data(it_start, it_end);
            memory::move(&(*it_start), &(*it_end), (size() - idx_end));
            m_size -= (idx_end - idx_start);
            return it_start;
        }

        iterator erase(const_iterator cit) noexcept
        {
            return erase(cit - begin());
        }

        iterator
        erase(const_iterator cit_start, const_iterator cit_end) noexcept
        {
            return erase(cit_start - begin(), cit_end - begin());
        }

        reference front(void) noexcept
        {
            return operator[](0);
        }

        const_reference front(void) const noexcept
        {
            return operator[](0);
        }

        iterator insert(size_type idx, const_reference item) noexcept
        {
            GG_ASSERT(idx <= size());
            reallocate_if_needed();
            iterator it = (begin() + idx);
            memory::move(&(*(it + 1)), &(*it), (size() - idx));
            memory::construct_object(&(*it), item);
            ++m_size;
            return it;
        }

        iterator insert(size_type idx, rvalue_reference item) noexcept
        {
            GG_ASSERT(idx <= size());
            reallocate_if_needed();
            iterator it = (begin() + idx);
            memory::move(&(*(it + 1)), &(*it), (size() - idx));
            memory::construct_object(&(*it), type::move(item));
            ++m_size;
            return it;
        }

        iterator insert(const_iterator cit, const_reference item) noexcept
        {
            return insert(cit - begin(), item);
        }

        iterator insert(const_iterator cit, rvalue_reference item) noexcept
        {
            return insert(cit - begin(), type::move(item));
        }

        iterator insert(
            size_type idx,
            const_iterator cit_start,
            const_iterator cit_end) noexcept
        {
            GG_ASSERT(idx <= size());
            diff_type size = (cit_end - cit_start);
            reallocate_if_needed(this->size() + size);
            iterator it = (begin() + idx);
            memory::move(&(*(it + size)), &(*it), (this->size() - idx));
            construct_data(it, cit_start, cit_end);
            m_size += size;
            return it;
        }

        iterator insert(
            const_iterator cit,
            const_iterator cit_start,
            const_iterator cit_end) noexcept
        {
            return insert(cit - begin(), cit_start, cit_end);
        }

        void pop_back(void) noexcept
        {
            iterator it_start = (end() - 1);
            iterator it_end = end();
            clear_data(it_start, it_end);
            --m_size;
        }

        void push_back(const_reference item) noexcept
        {
            reallocate_if_needed();
            memory::construct_object(&(*end()), item);
            ++m_size;
        }

        void push_back(rvalue_reference item) noexcept
        {
            reallocate_if_needed();
            memory::construct_object(&(*end()), type::move(item));
            ++m_size;
        }

        void reserve(size_type size) noexcept
        {
            reallocate_if_needed(size);
        }

        template <typename... ARGS>
        void resize(size_type size, ARGS &&... args) noexcept
        {
            reallocate_if_needed(size);
            (size > this->size()) ?
                construct_data(
                    end(),
                    item_type(type::forward<ARGS>(args)...),
                    size - this->size()) :
                clear_data(end() - (this->size() - size), end());
            m_size = size;
        }

        size_type max_size(void) const noexcept
        {
            return m_buffer.size<item_type>();
        }

        size_type size(void) const noexcept
        {
            return m_size;
        }

        // inquiries

        bool8 is_empty(void) const noexcept
        {
            return 0 == size();
        }

    private:

        // type definitions

        typedef memory_buffer_dynamic data_type;

        // methods

        void allocate(size_type size) noexcept
        {
            m_buffer.allocate(sizeof(item_type) * size);
        }

        void deallocate(void) noexcept
        {
            m_buffer.deallocate();
        }

        void reallocate(size_type size) noexcept
        {
            GG_ASSERT(size > max_size());
            m_buffer.reallocate(sizeof(item_type) * size);
        }

        void reallocate_if_needed(void) noexcept
        {
            if (size() == max_size())
            {
                static constexpr size_type k_min_allocation = 8;
                reallocate(
                    limit::max<size_type>(k_min_allocation, max_size() << 1));
            }
        }

        void reallocate_if_needed(size_type size) noexcept
        {
            if (size > max_size())
            {
                reallocate(size);
            }
        }

        template<typename T = array_dynamic>
        type::enable_if_t<
            type::is_trivially_destructible<typename T::item_type>::value>
        clear_data(void) noexcept
        {
        }

        template<typename T = array_dynamic>
        type::enable_if_t<
            !type::is_trivially_destructible<typename T::item_type>::value>
        clear_data(void) noexcept
        {
            for (size_type i = 0; i < size(); ++i)
            {
                data()[i].~item_type();
            }
        }

        template<typename T>
        type::enable_if_t<
            type::is_trivially_destructible<typename T::item_type>::value>
        clear_data(
            T GG_UNUSED_ARGUMENT(it_start),
            T GG_UNUSED_ARGUMENT(it_end)) noexcept
        {
        }

        template<typename T>
        type::enable_if_t<
            !type::is_trivially_destructible<typename T::item_type>::value>
        clear_data(T it_start, T it_end) noexcept
        {
            for (auto it = it_start; it != it_end; ++it)
            {
                (*it).~item_type();
            }
        }

        template<typename T>
        type::enable_if_t<
            type::is_trivially_copy_constructible<typename T::item_type>::value>
        construct_data(T const & array) noexcept
        {
            memory::copy(data(), array.data(), array.size());
        }

        template<typename T>
        type::enable_if_t<
            !type::is_trivially_copy_constructible<typename T::item_type>::value>
        construct_data(T const & array) noexcept
        {
            for (size_type i = 0; i < array.size(); ++i)
            {
                memory::construct_object(&(data()[i]), array.data()[i]);
            }
        }

        template<typename T>
        type::enable_if_t<
            type::is_trivially_copy_constructible<typename T::item_type>::value>
        construct_data(
            T it,
            typename T::item_type const & item,
            size_type size) noexcept
        {
            for (size_type i = 0; i < size; ++i, ++it)
            {
                memory::copy(&(*it), &item);
            }
        }

        template<typename T>
        type::enable_if_t<
            !type::is_trivially_copy_constructible<typename T::item_type>::value>
        construct_data(
            T it,
            typename T::item_type const & item,
            size_type size) noexcept
        {
            for (size_type i = 0; i < size; ++i, ++it)
            {
                memory::construct_object(&(*it), item);
            }
        }

        template<typename T, typename U>
        type::enable_if_t<
            type::is_trivially_copy_constructible<typename T::item_type>::value>
        construct_data(T it, U const & cit_start, U const & cit_end) noexcept
        {
            memory::copy(&(*it), &(*cit_start), (cit_end - cit_start));
        }

        template<typename T, typename U>
        type::enable_if_t<
            !type::is_trivially_copy_constructible<typename T::item_type>::value>
        construct_data(T it, U const & cit_start, U const & cit_end) noexcept
        {
            for (auto cit = cit_start; cit != cit_end; ++cit, ++it)
            {
                memory::construct_object(&(*it), (*cit));
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
        size_type m_size;
    };
}

#endif // _gg_array_dynamic_h_
