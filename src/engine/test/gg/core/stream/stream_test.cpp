#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/stream/stream_defs.h"
#include "gg/core/string/type/string_ref.h"

//==============================================================================
namespace gg::stream_test
{
//==============================================================================

TEST_CASE("stream", "[gg.stream]")
{
#if defined(GG_DEBUG)
    SECTION("stream mode descriptors")
    {
        REQUIRE(
            string_ref(GG_TEXT("binary")) ==
            k_stream_mode_descriptors[enums::cast(stream_mode::binary)]);

        REQUIRE(
            string_ref(GG_TEXT("text")) ==
            k_stream_mode_descriptors[enums::cast(stream_mode::text)]);
    }
#endif
}

//==============================================================================
}
//==============================================================================
