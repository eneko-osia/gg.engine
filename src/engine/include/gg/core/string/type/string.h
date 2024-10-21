#ifndef _gg_string_h_
#define _gg_string_h_

#include "gg/core/debug/assert.h"
#include "gg/core/macro/macro.h"
#include "gg/core/string/macro/macro.h"
#include "gg/core/type/constant.h"
#include "gg/core/type/type_trait.h"
#include <cstdio>

namespace gg
{
    namespace string
    {
        // constants

        static constexpr char8 const * k_empty = GG_TEXT("");
        static constexpr size_type npos = k_uint32_max;

        // methods

        inline constexpr diff_type
        compare(char8 const * lhs, char8 const * rhs) noexcept
        {
            GG_ASSERT(lhs);
            GG_ASSERT(rhs);

            for (; (*lhs && *rhs) && (*lhs == *rhs); ++lhs, ++rhs) {}
            return *(uchar8 const *) lhs - *(uchar8 const *) rhs;
        }

        inline constexpr char8 const *
        find(char8 const * lhs, char8 const * rhs) noexcept
        {
            GG_ASSERT(lhs);
            GG_ASSERT(rhs);

            for (; *lhs; ++lhs)
            {
                char8 const * j = rhs;
                for (char8 const * i = lhs; (*i && *j) && (*i == *j); ++i, ++j) {}
                GG_RETURN_VALUE_IF(!(*j), lhs);
            }
            return nullptr;
        }

        template <typename... ARGS>
        inline int32
        format(
            char8 * buffer,
            size_type size,
            char8 const * format,
            ARGS &&... args)
        {
            return
                snprintf(buffer, size, format, type::forward<ARGS>(args)...);
        }

        template <typename TYPE>
        void from(TYPE value, char8 * buffer, size_type size) noexcept;

        template <>
        inline void from<bool8>(bool8 value, char8 * buffer, size_type size) noexcept
        {
            format(buffer, size, "%hhd", value);
        }

        template <>
        inline void from<int8>(int8 value, char8 * buffer, size_type size) noexcept
        {
            format(buffer, size, "%hhd", value);
        }

        template <>
        inline void from<uint8>(uint8 value, char8 * buffer, size_type size) noexcept
        {
            format(buffer, size, "%hhu", value);
        }

        template <>
        inline void from<int16>(int16 value, char8 * buffer, size_type size) noexcept
        {
            format(buffer, size, "%hd", value);
        }

        template <>
        inline void from<uint16>(uint16 value, char8 * buffer, size_type size) noexcept
        {
            format(buffer, size, "%hu", value);
        }

        template <>
        inline void from<int32>(int32 value, char8 * buffer, size_type size) noexcept
        {
            format(buffer, size, "%d", value);
        }

        template <>
        inline void from<uint32>(uint32 value, char8 * buffer, size_type size) noexcept
        {
            format(buffer, size, "%u", value);
        }

        template <>
        inline void from<int64>(int64 value, char8 * buffer, size_type size) noexcept
        {
            format(buffer, size, "%lld", value);
        }

        template <>
        inline void from<uint64>(uint64 value, char8 * buffer, size_type size) noexcept
        {
            format(buffer, size, "%llu", value);
        }

        template <>
        inline void from<float32>(float32 value, char8 * buffer, size_type size) noexcept
        {
            format(buffer, size, "%f", value);
        }

        template <>
        inline void from<float64>(float64 value, char8 * buffer, size_type size) noexcept
        {
            format(buffer, size, "%f", value);
        }

        inline constexpr size_type length(char8 const * str) noexcept
        {
            GG_ASSERT(str);

            size_type size = 0;
            for (; *str; ++str, ++size) {}
            return size;
        }

        inline constexpr size_type
        ltrim(
            char8 * str,
            size_type size,
            char8 const * delimiters = GG_TEXT(" \f\n\r\t\v")) noexcept
        {
            GG_ASSERT(str);
            GG_ASSERT(delimiters);

            char8 const * delimiters_end = delimiters + length(delimiters);
            char8 const * str_start = str;
            char8 const * str_end = str + size;
            char8 const * str_it = str;

            for(; str_it != str_end; ++str_it)
            {
                char8 const * delimiter = delimiters;
                for(; delimiter != delimiters_end; ++delimiter)
                {
                    GG_BREAK_IF(*str_it == *delimiter)
                }
                GG_BREAK_IF(delimiter == delimiters_end);
            }
            for(; str_it != str_end; ++str_it) { *str++ = *str_it; }
            *str = '\0';
            return str - str_start;
        }

        inline constexpr size_type
        rtrim(
            char8 * str,
            size_type size,
            char8 const * delimiters = GG_TEXT(" \f\n\r\t\v")) noexcept
        {
            GG_ASSERT(str);
            GG_ASSERT(delimiters);

            char8 const * delimiters_end = delimiters + length(delimiters);
            char8 const * str_start = str;

            for(str = str + size - 1; str != str_start; --str)
            {
                char8 const * delimiter = delimiters;
                for(; delimiter != delimiters_end; ++delimiter)
                {
                    GG_BREAK_IF(*str == *delimiter)
                }
                GG_BREAK_IF(delimiter == delimiters_end);
            }
            *++str = '\0';
            return str - str_start;
        }

        inline constexpr size_type
        trim(
            char8 * str,
            size_type size,
            char8 const * delimiters = GG_TEXT(" \f\n\r\t\v")) noexcept
        {
            return ltrim(str, rtrim(str, size, delimiters), delimiters);
        }
    }
}

#endif // _gg_string_h_
