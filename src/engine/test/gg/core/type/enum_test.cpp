#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/type/enum.h"
#include "gg/core/type/type_trait.h"

//==============================================================================
namespace gg::enum_test
{
//==============================================================================

enum class mock_enum : uint8
{
    value_1 =   1 << 0,
    value_2 =   1 << 1,
    value_4 =   1 << 2,
    value_8 =   1 << 3
};
GG_ENUM(mock_enum);

//==============================================================================

TEST_CASE("enum", "[gg.enum]")
{
    SECTION("construct")
    {
        REQUIRE(type::is_constructible<mock_enum>::value);
        REQUIRE(type::is_trivially_constructible<mock_enum>::value);
        REQUIRE(type::is_trivially_constructible<mock_enum>::value);
    }

    SECTION("copy")
    {
        REQUIRE(type::is_copy_constructible<mock_enum>::value);
        REQUIRE(type::is_trivially_copy_constructible<mock_enum>::value);
        REQUIRE(type::is_copy_constructible<mock_enum>::value);
        REQUIRE(type::is_trivially_copy_constructible<mock_enum>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(type::is_destructible<mock_enum>::value);
        REQUIRE(type::is_trivially_destructible<mock_enum>::value);
        REQUIRE(type::is_trivially_destructible<mock_enum>::value);
    }

    SECTION("assign")
    {
        REQUIRE(type::is_copy_assignable<mock_enum>::value);
        REQUIRE(!type::is_trivially_assignable<mock_enum>::value);
    }

    SECTION("compare")
    {
        REQUIRE(type::is_comparable<mock_enum>::value);
    }

    SECTION("pod")
    {
        REQUIRE(type::is_pod<mock_enum>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<mock_enum>::value);
    }

    SECTION("sizeof")
    {
        REQUIRE(sizeof(mock_enum) == sizeof(mock_enum_underlying));
    }
}

TEST_CASE("enum.cast", "[gg.enum]")
{
    SECTION("enum cast to underlying")
    {
        mock_enum_underlying value =
            enums::cast<mock_enum>(mock_enum::value_1);
        REQUIRE(value == mock_enum_underlying(1));
    }

    SECTION("underlying cast to enum")
    {
        mock_enum value = enums::cast<mock_enum>(1);
        REQUIRE(value == mock_enum::value_1);
    }
}

TEST_CASE("enum.operator&", "[gg.enum]")
{
    SECTION("enum & enum")
    {
        mock_enum value = mock_enum::value_1 | mock_enum::value_4;
        REQUIRE((value & mock_enum::value_1) == mock_enum::value_1);
    }
}

TEST_CASE("enum.operator&=", "[gg.enum]")
{
    SECTION("enum &= enum")
    {
        mock_enum value = mock_enum::value_1 | mock_enum::value_4;
        value &= mock_enum::value_1;
        REQUIRE(value == mock_enum::value_1);
    }
}

TEST_CASE("enum.operator|", "[gg.enum]")
{
    SECTION("enum | enum")
    {
        REQUIRE(
            (mock_enum::value_1 | mock_enum::value_4) == enums::cast<mock_enum>(5)
        );
    }
}

TEST_CASE("enum.operator|=", "[gg.enum]")
{
    SECTION("enum |= enum")
    {
        mock_enum value = mock_enum::value_1;
        value |= mock_enum::value_4;
        REQUIRE(value == enums::cast<mock_enum>(5));
    }
}

TEST_CASE("enum.operator-xor", "[gg.enum]")
{
    SECTION("enum ^ enum")
    {
        mock_enum lvalue = mock_enum::value_1 | mock_enum::value_4;
        mock_enum rvalue = mock_enum::value_1 | mock_enum::value_8;
        REQUIRE((lvalue ^ rvalue) == enums::cast<mock_enum>(12));
    }
}

TEST_CASE("enum.operator-xor=", "[gg.enum]")
{
    SECTION("enum ^= enum")
    {
        mock_enum lvalue = mock_enum::value_1 | mock_enum::value_4;
        mock_enum rvalue = mock_enum::value_1 | mock_enum::value_8;
        lvalue ^= rvalue;
        REQUIRE(lvalue == enums::cast<mock_enum>(12));
    }
}

TEST_CASE("enum.operator~", "[gg.enum]")
{
    SECTION("enum &= ~enum")
    {
        mock_enum value = mock_enum::value_1 | mock_enum::value_4;
        value &= ~mock_enum::value_1;
        REQUIRE(value == mock_enum::value_4);
    }
}

TEST_CASE("enum.operator++", "[gg.enum]")
{
    SECTION("++enum")
    {
        mock_enum value = mock_enum::value_1;
        REQUIRE(++value == enums::cast<mock_enum>(2));
        REQUIRE(++value == enums::cast<mock_enum>(3));
        REQUIRE(++value == enums::cast<mock_enum>(4));
    }

    SECTION("enum++")
    {
        mock_enum value = mock_enum::value_1;
        REQUIRE(value++ == enums::cast<mock_enum>(1));
        REQUIRE(value++ == enums::cast<mock_enum>(2));
        REQUIRE(value++ == enums::cast<mock_enum>(3));
    }
}

//==============================================================================
}
//==============================================================================
