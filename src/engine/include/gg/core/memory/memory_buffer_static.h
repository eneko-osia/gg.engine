#ifndef _gg_memory_buffer_static_h_
#define _gg_memory_buffer_static_h_

#include "gg/core/debug/assert.h"
#include "gg/core/pattern/non_copyable.h"
#include "gg/core/type/type_trait.h"

namespace gg
{
    template <size_type SIZE>
    class memory_buffer_static final : public non_copyable
    {
    public:

        // accessors

        template <typename ITEM_TYPE = void>
        constexpr ITEM_TYPE * data(void) noexcept
        {
            void * data = m_data;
            return type::cast_static<ITEM_TYPE *>(data);
        }

        template <typename ITEM_TYPE = void>
        constexpr ITEM_TYPE const * data(void) const noexcept
        {
            void const * data = m_data;
            return type::cast_static<ITEM_TYPE const *>(data);
        }

        template <typename ITEM_TYPE = byte>
        constexpr ITEM_TYPE & get(size_type idx) noexcept
        {
            GG_ASSERT(idx < size<ITEM_TYPE>());
            return data<ITEM_TYPE>()[idx];
        }

        template <typename ITEM_TYPE = byte>
        constexpr ITEM_TYPE const & get(size_type idx) const noexcept
        {
            GG_ASSERT(idx < size<ITEM_TYPE>());
            return data<ITEM_TYPE>()[idx];
        }

        template <typename ITEM_TYPE = byte>
        constexpr size_type size(void) const
        {
            return type::cast_static<size_type>(SIZE / sizeof(ITEM_TYPE));
        }

    private:

        // attributes

        byte m_data[SIZE];
    };
}

#endif // _gg_memory_buffer_static_h_
