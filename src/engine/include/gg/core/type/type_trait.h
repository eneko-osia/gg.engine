#ifndef _gg_type_trait_h_
#define _gg_type_trait_h_

#include "gg/core/type/type.h"

#include <functional>
#include <type_traits>
#include <utility>

namespace gg
{
    namespace type
    {
        namespace impl
        {
            // structs

            struct equality {};
            template <typename TYPE>
            equality operator==(TYPE const &, TYPE const &);

            template <typename TYPE>
            struct is_comparable
            {
                static constexpr bool8 value =
                    !std::is_same<decltype(*(TYPE *)(0) == *(TYPE *)(0)), equality>::value;
            };
        }

        // structs

        template <bool8 TEST, typename TYPE1, typename TYPE2>
        using conditional = std::conditional<TEST, TYPE1, TYPE2>;

        template<bool8 TEST, typename TYPE = void>
        using enable_if = std::enable_if<TEST, TYPE>;

        template<bool8 TEST, typename TYPE = void>
        using enable_if_t = std::enable_if_t<TEST, TYPE>;

        template <typename TYPE1, typename TYPE2 = TYPE1>
        using is_assignable = std::is_assignable<TYPE1, TYPE2>;

        template <typename TYPE>
        struct is_comparable
        {
            static constexpr bool8 value =
                impl::is_comparable<TYPE>::value;
        };

        template <typename TYPE>
        using is_const = std::is_const<TYPE>;

        template <typename TYPE, typename... ARGS>
        using is_constructible = std::is_constructible<TYPE, ARGS...>;

        template <typename TYPE>
        using is_copy_assignable = std::is_copy_assignable<TYPE>;

        template <typename TYPE>
        using is_copy_constructible = std::is_copy_constructible<TYPE>;

        template <typename TYPE>
        using is_destructible = std::is_destructible<TYPE>;

        template <typename TYPE>
        using is_pod = std::is_pod<TYPE>;

        template <typename TYPE>
        using is_pointer = std::is_pointer<TYPE>;

        template <typename TYPE>
        using is_polymorphic = std::is_polymorphic<TYPE>;

        template <typename TYPE1, typename TYPE2 = TYPE1>
        using is_trivially_assignable = std::is_trivially_assignable<TYPE1, TYPE2>;

        template <typename TYPE, typename... ARGS>
        using is_trivially_constructible = std::is_trivially_constructible<TYPE, ARGS...>;

        template <typename TYPE>
        using is_trivially_copy_constructible = std::is_trivially_copy_constructible<TYPE>;

        template <typename TYPE>
        using is_trivially_destructible = std::is_trivially_destructible<TYPE>;

        template <typename TYPE>
        using underlying = std::underlying_type<TYPE>;

        // methods

        template <typename TO, typename FROM>
        inline constexpr TO cast_const(FROM const & value) noexcept
        {
            return const_cast<TO>(value);
        }

        template <typename TO, typename FROM>
        inline constexpr TO cast_dynamic(FROM const & value) noexcept
        {
            return dynamic_cast<TO>(value);
        }

        template <typename TO, typename FROM>
        inline constexpr TO cast_reinterpret(FROM const & value) noexcept
        {
            return reinterpret_cast<TO>(value);
        }

        template <typename TO, typename FROM>
        inline constexpr TO cast_static(FROM const & value) noexcept
        {
            return static_cast<TO>(value);
        }

        template <typename TYPE>
        inline constexpr TYPE &&
        forward(typename std::remove_reference<TYPE>::type & args) noexcept
        {
            return std::forward<TYPE>(args);
        }

        template <typename TYPE>
        inline constexpr TYPE &&
        forward(typename std::remove_reference<TYPE>::type && args) noexcept
        {
            return std::forward<TYPE>(args);
        }

        template <typename TYPE>
        inline constexpr typename std::remove_reference<TYPE>::type &&
        move(TYPE && args) noexcept
        {
            return std::move(args);
        }

        template <typename TYPE>
        inline std::reference_wrapper<TYPE> ref(TYPE & value) noexcept
        {
            return std::ref<TYPE>(value);
        }
    }
}

#endif // _gg_type_trait_h_
