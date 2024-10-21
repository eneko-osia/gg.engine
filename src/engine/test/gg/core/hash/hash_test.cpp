#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/hash/hash.h"
#include "gg/core/string/type/string_ref.h"

//==============================================================================
namespace gg::hash_test
{
//==============================================================================

TEST_CASE("hash", "[gg.hash]")
{
    SECTION("fnv1")
    {
        REQUIRE(0x6F19393E == hash::fnv1::generate(GG_TEXT("hash1")));
        REQUIRE(0x6F19393D == hash::fnv1::generate(GG_TEXT("hash2")));
        REQUIRE(0x6F19393C == hash::fnv1::generate(GG_TEXT("hash3")));
    }

    SECTION("fnv1a")
    {
        REQUIRE(0x60dbb5a0 == hash::fnv1a::generate(GG_TEXT("hash1")));
        REQUIRE(0x63dbba59 == hash::fnv1a::generate(GG_TEXT("hash2")));
        REQUIRE(0x62dbb8c6 == hash::fnv1a::generate(GG_TEXT("hash3")));
    }
}

//==============================================================================
}
//==============================================================================
