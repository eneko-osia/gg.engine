#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/container/iterator/iterator_defs.h"
#include "gg/core/container/iterator/iterator_desc.h"

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
            k_iterator_type_descriptors[enums::cast(iterator_type::no_const)] ==
            GG_TEXT("no_const")
        );

        REQUIRE(
            k_iterator_type_descriptors[enums::cast(iterator_type::is_const)] ==
            GG_TEXT("is_const")
        );
    }
#endif
}

//==============================================================================
}
//==============================================================================
