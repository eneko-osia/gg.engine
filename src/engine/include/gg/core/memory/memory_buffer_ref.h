#ifndef _gg_memory_buffer_ref_h_
#define _gg_memory_buffer_ref_h_

#include "gg/core/debug/assert.h"
#include "gg/core/type/type_trait.h"

namespace gg
{
    class memory_buffer_ref final
    {
    public:

        // constructors

        memory_buffer_ref(void) noexcept
            : m_data(nullptr)
            , m_size(0)
        {
        }

        memory_buffer_ref(byte * data, size_type size) noexcept
            : m_data(data)
            , m_size(size)
        {
        }

        memory_buffer_ref(memory_buffer_ref const & buffer) noexcept
            : m_data(buffer.m_data)
            , m_size(buffer.m_size)
        {
        }

        memory_buffer_ref(memory_buffer_ref && buffer) noexcept
            : m_data(type::move(buffer.m_data))
            , m_size(type::move(buffer.m_size))
        {
            buffer.m_data = nullptr;
            buffer.m_size = 0;
        }

        // operators

        memory_buffer_ref &
        operator=(memory_buffer_ref const & buffer) noexcept
        {
            GG_ASSERT(this != &buffer);
            m_data = buffer.m_data;
            m_size = buffer.m_size;
            return *this;
        }

        memory_buffer_ref &
        operator=(memory_buffer_ref && buffer) noexcept
        {
            GG_ASSERT(this != &buffer);
            m_data = type::move(buffer.m_data);
            m_size = type::move(buffer.m_size);
            buffer.m_data = nullptr;
            buffer.m_size = 0;
            return *this;
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

#endif // _gg_memory_buffer_ref_h_
