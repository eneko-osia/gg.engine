#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/type/type_trait.h"
#include "gg/core/utils/byte_swap.h"

//==============================================================================
namespace gg::byte_swap_test
{
//==============================================================================

TEST_CASE("byte_swap.swap", "[gg.byte_swap]")
{
    SECTION("bool8")
    {
        REQUIRE(
            byte_swap::swap(type::cast_static<bool8>(0x01)) ==
            type::cast_static<bool8>(0x01)
        );
    }

    SECTION("int8")
    {
        REQUIRE(
            byte_swap::swap(type::cast_static<int8>(0x01)) ==
            type::cast_static<int8>(0x01)
        );
    }

    SECTION("uint8")
    {
        REQUIRE(
            byte_swap::swap(type::cast_static<uint8>(0x01)) ==
            type::cast_static<int8>(0x01)
        );
    }

    SECTION("int16")
    {
        REQUIRE(
            byte_swap::swap(type::cast_static<int16>(0x0001)) ==
            type::cast_static<int16>(0x0100)
        );
    }

    SECTION("uint16")
    {
        REQUIRE(
            byte_swap::swap(type::cast_static<uint16>(0x0001)) ==
            type::cast_static<uint16>(0x0100)
        );
    }

    SECTION("int32")
    {
        REQUIRE(
            byte_swap::swap(type::cast_static<int32>(0x00000001)) ==
            type::cast_static<int32>(0x01000000)
        );
    }

    SECTION("uint32")
    {
        REQUIRE(
            byte_swap::swap(type::cast_static<uint32>(0x00000001)) ==
            type::cast_static<uint32>(0x01000000)
        );
    }

    SECTION("int64")
    {
        REQUIRE(
            byte_swap::swap(type::cast_static<int64>(0x0000000000000001)) ==
            type::cast_static<int64>(0x0100000000000000)
        );
    }

    SECTION("uint64")
    {
        REQUIRE(
            byte_swap::swap(type::cast_static<uint64>(0x0000000000000001)) ==
            type::cast_static<uint64>(0x0100000000000000)
        );
    }
}

//==============================================================================
}
//==============================================================================
