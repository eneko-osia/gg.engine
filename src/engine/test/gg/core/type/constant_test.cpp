#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/type/constant.h"

//==============================================================================
namespace gg::constant_test
{
//==============================================================================

TEST_CASE("constant.int8", "[gg.constant]")
{
    SECTION("min < max")
    {
        REQUIRE(k_int8_min < k_int8_max);
    }
}

TEST_CASE("constant.uint8", "[gg.constant]")
{
    SECTION("min < max")
    {
        REQUIRE(k_uint8_min < k_uint8_max);
    }
}

TEST_CASE("constant.int16", "[gg.constant]")
{
    SECTION("min < max")
    {
        REQUIRE(k_int16_min < k_int16_max);
    }
}

TEST_CASE("constant.uint16", "[gg.constant]")
{
    SECTION("min < max")
    {
        REQUIRE(k_uint16_min < k_uint16_max);
    }
}

TEST_CASE("constant.int32", "[gg.constant]")
{
    SECTION("min < max")
    {
        REQUIRE(k_int32_min < k_int32_max);
    }
}

TEST_CASE("constant.uint32", "[gg.constant]")
{
    SECTION("min < max")
    {
        REQUIRE(k_uint32_min < k_uint32_max);
    }
}

TEST_CASE("constant.int64", "[gg.constant]")
{
    SECTION("min < max")
    {
        REQUIRE(k_int64_min < k_int64_max);
    }
}

TEST_CASE("constant.uint64", "[gg.constant]")
{
    SECTION("min < max")
    {
        REQUIRE(k_uint64_min < k_uint64_max);
    }
}

TEST_CASE("constant.float32", "[gg.constant]")
{
    SECTION("min < max")
    {
        REQUIRE(k_float32_min < k_float32_max);
    }
}

TEST_CASE("constant.float64", "[gg.constant]")
{
    SECTION("min < max")
    {
        REQUIRE(k_float64_min < k_float64_max);
    }
}

//==============================================================================
}
//==============================================================================
