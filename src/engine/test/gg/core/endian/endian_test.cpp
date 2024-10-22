#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/endian/endian_desc.h"
#include "gg/core/endian/endian.h"
#include "gg/core/string/type/string_ref.h"

//==============================================================================
namespace gg::endian_test
{
//==============================================================================

TEST_CASE("endian", "[gg.endian]")
{
    SECTION("system endian mode")
    {
        endian_mode mode = endian_mode::max;

    #if defined(GG_MAC) || defined(GG_LINUX) || defined(GG_WINDOWS)
        mode = endian_mode::little_endian;
    #endif

        REQUIRE(endian::system_mode == mode);
    }

#if defined(GG_DEBUG)
    SECTION("endian mode descriptors")
    {
        REQUIRE(
            k_endian_mode_descriptors[enums::cast(endian_mode::big_endian)] ==
            GG_TEXT("big_endian")
        );

        REQUIRE(
            k_endian_mode_descriptors[enums::cast(endian_mode::little_endian)] ==
            GG_TEXT("little_endian")
        );
    }
#endif
}

//==============================================================================
}
//==============================================================================
