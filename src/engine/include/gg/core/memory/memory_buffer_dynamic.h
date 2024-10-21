#ifndef _gg_memory_buffer_dynamic_h_
#define _gg_memory_buffer_dynamic_h_

#include "gg/core/debug/assert.h"
#include "gg/core/memory/memory.h"
#include "gg/core/pattern/non_copyable.h"

namespace gg
{
    class memory_buffer_dynamic final : public non_copyable
    {
    public:

        // constructors

        memory_buffer_dynamic(void) noexcept
            : m_data(nullptr)
            , m_size(0)
        {
        }

        explicit memory_buffer_dynamic(size_type size) noexcept
            : m_data(nullptr)
            , m_size(0)
        {
            allocate(size);
        }

        memory_buffer_dynamic(memory_buffer_dynamic && buffer) noexcept
            : m_data(type::move(buffer.m_data))
            , m_size(type::move(buffer.m_size))
        {
            buffer.m_data = nullptr;
            buffer.m_size = 0;
        }

        ~memory_buffer_dynamic(void) noexcept
        {
            deallocate();
        }

        // operators

        memory_buffer_dynamic &
        operator=(memory_buffer_dynamic && buffer) noexcept
        {
            GG_ASSERT(this != &buffer);
            deallocate();
            m_data = type::move(buffer.m_data);
            m_size = type::move(buffer.m_size);
            buffer.m_data = nullptr;
            buffer.m_size = 0;
            return *this;
        }

        // methods

        void allocate(size_type size) noexcept
        {
            GG_ASSERT(!m_data);
            m_data = memory::allocate<byte>(size);
            m_size = size;
        }

        void deallocate(void) noexcept
        {
            memory::deallocate(m_data);
            m_data = nullptr;
            m_size = 0;
        }

        void reallocate(size_type size) noexcept
        {
            m_data = memory::reallocate<byte>(m_data, size);
            m_size = size;
        }

        // accessors

        template <typename ITEM_TYPE = void>
        ITEM_TYPE * data(void) noexcept
        {
            void * data = m_data;
            return type::cast_static<ITEM_TYPE *>(data);
        }

        template <typename ITEM_TYPE = void>
        ITEM_TYPE const * data(void) const noexcept
        {
            void const * data = m_data;
            return type::cast_static<ITEM_TYPE const *>(data);
        }

        template <typename ITEM_TYPE = byte>
        ITEM_TYPE & get(size_type idx) noexcept
        {
            GG_ASSERT(idx < size<ITEM_TYPE>());
            return data<ITEM_TYPE>()[idx];
        }

        template <typename ITEM_TYPE = byte>
        ITEM_TYPE const & get(size_type idx) const noexcept
        {
            GG_ASSERT(idx < size<ITEM_TYPE>());
            return data<ITEM_TYPE>()[idx];
        }

        template <typename ITEM_TYPE = byte>
        size_type size(void) const
        {
            return type::cast_static<size_type>(m_size / sizeof(ITEM_TYPE));
        }

    private:

        // attributes

        byte * m_data;
        size_type m_size;
    };
}

#endif // _gg_memory_buffer_dynamic_h_
