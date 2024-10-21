#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/type/type.h"

//==============================================================================
namespace gg::type_test
{
//==============================================================================

TEST_CASE("type.bool8", "[gg.type]")
{
    SECTION("sizeof")
    {
        REQUIRE(sizeof(bool8) == 1);
    }
}

TEST_CASE("type.int8", "[gg.type]")
{
    SECTION("sizeof")
    {
        REQUIRE(sizeof(int8) == 1);
    }
}

TEST_CASE("type.uint8", "[gg.type]")
{
    SECTION("sizeof")
    {
        REQUIRE(sizeof(uint8) == 1);
    }
}

TEST_CASE("type.int16", "[gg.type]")
{
    SECTION("sizeof")
    {
        REQUIRE(sizeof(int16) == 2);
    }
}

TEST_CASE("type.uint16", "[gg.type]")
{
    SECTION("sizeof")
    {
        REQUIRE(sizeof(uint16) == 2);
    }
}

TEST_CASE("type.int32", "[gg.type]")
{
    SECTION("sizeof")
    {
        REQUIRE(sizeof(int32) == 4);
    }
}

TEST_CASE("type.uint32", "[gg.type]")
{
    SECTION("sizeof")
    {
        REQUIRE(sizeof(uint32) == 4);
    }
}

TEST_CASE("type.int64", "[gg.type]")
{
    SECTION("sizeof")
    {
        REQUIRE(sizeof(int64) == 8);
    }
}

TEST_CASE("type.uint64", "[gg.type]")
{
    SECTION("sizeof")
    {
        REQUIRE(sizeof(uint64) == 8);
    }
}

TEST_CASE("type.float32", "[gg.type]")
{
    SECTION("sizeof")
    {
        REQUIRE(sizeof(float32) == 4);
    }
}

TEST_CASE("type.float64", "[gg.type]")
{
    SECTION("sizeof")
    {
        REQUIRE(sizeof(float64) == 8);
    }
}

TEST_CASE("type.char8", "[gg.type]")
{
    SECTION("sizeof")
    {
        REQUIRE(sizeof(char8) == 1);
    }
}

TEST_CASE("type.uchar8", "[gg.type]")
{
    SECTION("sizeof")
    {
        REQUIRE(sizeof(uchar8) == 1);
    }
}

TEST_CASE("type.char16", "[gg.type]")
{
    SECTION("sizeof")
    {
        REQUIRE(sizeof(char16) == 2);
    }
}

TEST_CASE("type.uchar16", "[gg.type]")
{
    SECTION("sizeof")
    {
        REQUIRE(sizeof(uchar16) == 2);
    }
}

TEST_CASE("type.char32", "[gg.type]")
{
    SECTION("sizeof")
    {
        REQUIRE(sizeof(char32) == 4);
    }
}

TEST_CASE("type.uchar32", "[gg.type]")
{
    SECTION("sizeof")
    {
        REQUIRE(sizeof(uchar32) == 4);
    }
}

TEST_CASE("type.byte", "[gg.type]")
{
    SECTION("sizeof")
    {
        REQUIRE(sizeof(byte) == 1);
    }
}

TEST_CASE("type.diff_type", "[gg.type]")
{
    SECTION("sizeof")
    {
    #if defined(GG_X86)
        REQUIRE(sizeof(diff_type) == 4);
    #elif defined(GG_X86_64)
        REQUIRE(sizeof(diff_type) == 8);
    #endif
    }
}

TEST_CASE("type.size_type", "[gg.type]")
{
    SECTION("sizeof")
    {
    #if defined(GG_X86)
        REQUIRE(sizeof(size_type) == 4);
    #elif defined(GG_X86_64)
        REQUIRE(sizeof(size_type) == 8);
    #endif
    }
}

//==============================================================================
}
//==============================================================================
