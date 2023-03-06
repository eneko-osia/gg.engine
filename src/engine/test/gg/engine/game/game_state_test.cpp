#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/string/type/string_ref.h"
#include "gg/engine/game/game_state.h"

//==============================================================================
namespace gg::engine::game_state_test
{
//==============================================================================

TEST_CASE("game_state", "[ggengine.game_state]")
{
#if defined(GG_DEBUG)
    SECTION("completion type descriptors")
    {
        REQUIRE(
            string_ref(GG_TEXT("error")) ==
                k_completion_type_descriptors[
                    enums::cast(completion_type::error)]);

        REQUIRE(
            string_ref(GG_TEXT("success")) ==
                k_completion_type_descriptors[
                    enums::cast(completion_type::success)]);

        REQUIRE(
            string_ref(GG_TEXT("uncompleted")) ==
                k_completion_type_descriptors[
                    enums::cast(completion_type::uncompleted)]);
    }
#endif
}

//==============================================================================
}
//==============================================================================
