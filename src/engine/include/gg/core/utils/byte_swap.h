#ifndef _gg_byte_swap_h_
#define	_gg_byte_swap_h_

#include "gg/core/type/type.h"

namespace gg
{
    namespace byte_swap
    {
        // methods

        inline constexpr bool8 swap(bool8 value) noexcept
        {
            return value;
        }

        inline constexpr int8 swap(int8 value) noexcept
        {
            return value;
        }

        inline constexpr uint8 swap(uint8 value) noexcept
        {
            return value;
        }
        inline constexpr int16 swap(int16 value) noexcept
        {
            return ((value << 8) & 0xFF00) |
                   ((value >> 8) & 0x00FF);
        }

        inline constexpr uint16 swap(uint16 value) noexcept
        {
            return ((value << 8) & 0xFF00) |
                   ((value >> 8) & 0x00FF);
        }

        inline constexpr int32 swap(int32 value) noexcept
        {
            return ((value << 24) & 0xFF000000) |
                   ((value <<  8) & 0x00FF0000) |
                   ((value >>  8) & 0x0000FF00) |
                   ((value >> 24) & 0x000000FF);
        }

        inline constexpr uint32 swap(uint32 value) noexcept
        {
            return ((value << 24) & 0xFF000000) |
                   ((value <<  8) & 0x00FF0000) |
                   ((value >>  8) & 0x0000FF00) |
                   ((value >> 24) & 0x000000FF);
        }

        inline float32 swap(float32 value) noexcept
        {
            union { float32 as_float; uint32 as_unsigned; } temp;
            temp.as_float = value;
            temp.as_unsigned = swap(temp.as_unsigned);
            return temp.as_float;
        }

        inline constexpr int64 swap(int64 value) noexcept
        {
            return ((value << 56) & 0xFF00000000000000LL) |
                   ((value << 40) & 0x00FF000000000000LL) |
                   ((value << 24) & 0x0000FF0000000000LL) |
                   ((value <<  8) & 0x000000FF00000000LL) |
                   ((value >>  8) & 0x00000000FF000000LL) |
                   ((value >> 24) & 0x0000000000FF0000LL) |
                   ((value >> 40) & 0x000000000000FF00LL) |
                   ((value >> 56) & 0x00000000000000FFLL);
        }

        inline constexpr uint64 swap(uint64 value) noexcept
        {
            return ((value << 56) & 0xFF00000000000000LL) |
                   ((value << 40) & 0x00FF000000000000LL) |
                   ((value << 24) & 0x0000FF0000000000LL) |
                   ((value <<  8) & 0x000000FF00000000LL) |
                   ((value >>  8) & 0x00000000FF000000LL) |
                   ((value >> 24) & 0x0000000000FF0000LL) |
                   ((value >> 40) & 0x000000000000FF00LL) |
                   ((value >> 56) & 0x00000000000000FFLL);
        }

        inline float64 swap(float64 value) noexcept
        {
            union { float64 as_float; uint64 as_unsigned; } temp;
            temp.as_float = value;
            temp.as_unsigned = swap(temp.as_unsigned);
            return temp.as_float;
        }
    }
}

#endif // _gg_byte_swap_h_
