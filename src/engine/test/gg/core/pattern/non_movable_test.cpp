#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/pattern/non_movable.h"
#include "gg/core/type/type_trait.h"

//==============================================================================
namespace gg::non_movable_test
{
//==============================================================================

TEST_CASE("non_movable", "[gg.non_movable]")
{
    SECTION("assign")
    {
        REQUIRE(!type::is_copy_assignable<non_movable>::value);
        REQUIRE(!type::is_trivially_assignable<non_movable>::value);
    }

    SECTION("construct")
    {
        REQUIRE(!type::is_constructible<non_movable>::value);
        REQUIRE(!type::is_trivially_constructible<non_movable>::value);
    }

    SECTION("copy")
    {
        REQUIRE(!type::is_copy_constructible<non_movable>::value);
        REQUIRE(!type::is_trivially_copy_constructible<non_movable>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(!type::is_destructible<non_movable>::value);
        REQUIRE(!type::is_trivially_destructible<non_movable>::value);
    }

    SECTION("compare")
    {
        REQUIRE(!type::is_comparable<non_movable>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<non_movable>::value);
    }
}

//==============================================================================
}
//==============================================================================
