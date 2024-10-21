#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/type/enum.h"
#include "gg/core/utils/bit_field.h"

//==============================================================================
namespace gg::bit_field_test
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

TEST_CASE("bit_field.add", "[gg.bit_field]")
{
    SECTION("add")
    {
        mock_enum value = bit_field::add(mock_enum::value_1, mock_enum::value_4);
        REQUIRE(value == enums::cast<mock_enum>(5));
    }
}

TEST_CASE("bit_field.remove", "[gg.bit_field]")
{
    SECTION("remove")
    {
        mock_enum value = bit_field::add(mock_enum::value_1, mock_enum::value_4);
        value = bit_field::remove(value, mock_enum::value_1);
        REQUIRE(value == mock_enum::value_4);
    }
}

TEST_CASE("bit_field.is_partially_set", "[gg.bit_field]")
{
    SECTION("is_partially_set")
    {
        mock_enum value = bit_field::add(mock_enum::value_1, mock_enum::value_4);
        REQUIRE(
            bit_field::is_partially_set(
                value, bit_field::add(mock_enum::value_1, mock_enum::value_8)
            )
        );
    }

    SECTION("!is_partially_set")
    {
        mock_enum value = bit_field::add(mock_enum::value_1, mock_enum::value_4);
        REQUIRE(
            !bit_field::is_partially_set(
                value, bit_field::add(mock_enum::value_2, mock_enum::value_8)
            )
        );
    }
}

TEST_CASE("bit_field.is_set", "[gg.bit_field]")
{
    SECTION("is_set")
    {
        mock_enum value = bit_field::add(mock_enum::value_1, mock_enum::value_4);
        REQUIRE(bit_field::is_set(value, mock_enum::value_1));
    }

    SECTION("!is_set")
    {
        mock_enum value = bit_field::add(mock_enum::value_1, mock_enum::value_4);
        REQUIRE(
            !bit_field::is_set(
                value, bit_field::add(mock_enum::value_1, mock_enum::value_8)
            )
        );
    }
}

//==============================================================================
}
//==============================================================================
