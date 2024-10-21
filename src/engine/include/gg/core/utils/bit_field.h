#ifndef _gg_bit_field_h_
#define	_gg_bit_field_h_

#include "gg/core/type/type.h"

namespace gg
{
    namespace bit_field
    {
        // methods

        template <typename BIT_TYPE>
        inline constexpr BIT_TYPE add(BIT_TYPE lhs, BIT_TYPE rhs)
        {
            return lhs | rhs;
        }

        template <typename BIT_TYPE>
        inline constexpr BIT_TYPE remove(BIT_TYPE lhs, BIT_TYPE rhs)
        {
            return lhs & ~rhs;
        }

        // inquiries

        template <typename BIT_TYPE>
        inline constexpr bool8 is_partially_set(BIT_TYPE value, BIT_TYPE mask)
        {
            return (value & mask) != BIT_TYPE(0);
        }

        template <typename BIT_TYPE>
        inline constexpr bool8 is_set(BIT_TYPE value, BIT_TYPE mask)
        {
            return (value & mask) == mask;
        }
    }
}

#endif // _gg_bit_field_h_
