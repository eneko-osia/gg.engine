#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/pattern/non_copyable.h"
#include "gg/core/type/type_trait.h"

//==============================================================================
namespace gg::non_copyable_test
{
//==============================================================================

TEST_CASE("non_copyable", "[gg.non_copyable]")
{
    SECTION("assign")
    {
        REQUIRE(!type::is_copy_assignable<non_copyable>::value);
        REQUIRE(!type::is_trivially_assignable<non_copyable>::value);
    }

    SECTION("construct")
    {
        REQUIRE(!type::is_constructible<non_copyable>::value);
        REQUIRE(!type::is_trivially_constructible<non_copyable>::value);
    }

    SECTION("copy")
    {
        REQUIRE(!type::is_copy_constructible<non_copyable>::value);
        REQUIRE(!type::is_trivially_copy_constructible<non_copyable>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(!type::is_destructible<non_copyable>::value);
        REQUIRE(!type::is_trivially_destructible<non_copyable>::value);
    }

    SECTION("compare")
    {
        REQUIRE(!type::is_comparable<non_copyable>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<non_copyable>::value);
    }
}

//==============================================================================
}
//==============================================================================
