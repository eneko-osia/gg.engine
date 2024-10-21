#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/string/type/string_static.h"
#include "gg/version.h"

//==============================================================================
namespace gg::version_test
{
//==============================================================================

TEST_CASE("version", "[gg.version]")
{
    SECTION("version number")
    {
        string_static<32> version_number;
        string::format(
            version_number.c_str(),
            version_number.max_size(),
            "%u.%u.%u",
            k_version_major, k_version_minor, k_version_patch);
        REQUIRE(version_number == version_string);
    }
}

//==============================================================================
}
//==============================================================================
