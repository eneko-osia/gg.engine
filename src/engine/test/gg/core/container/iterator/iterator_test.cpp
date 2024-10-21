#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/container/iterator/iterator_defs.h"
#include "gg/core/string/type/string_ref.h"

//==============================================================================
namespace gg::iterator_test
{
//==============================================================================

TEST_CASE("iterator", "[gg.iterator]")
{
#if defined(GG_DEBUG)
    SECTION("iterator type descriptors")
    {
        REQUIRE(
            string_ref(GG_TEXT("no_const")) ==
            k_iterator_type_descriptors[enums::cast(iterator_type::no_const)]);

        REQUIRE(
            string_ref(GG_TEXT("is_const")) ==
            k_iterator_type_descriptors[enums::cast(iterator_type::is_const)]);
    }
#endif
}

//==============================================================================
}
//==============================================================================
