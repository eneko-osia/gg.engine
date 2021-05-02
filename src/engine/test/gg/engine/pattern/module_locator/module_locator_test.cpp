#include "gg/test/catch.h"

//==============================================================================

#include "gg/engine/pattern/module_locator/module_locator.h"

//==============================================================================
namespace gg::engine::module_locator_test
{
//==============================================================================

class mock_module : public module
{
    void on_finalize(void) noexcept override { }
    bool8 on_init(void) noexcept override { return true; }
};

//==============================================================================

TEST_CASE("module_locator", "[gg.module_locator]")
{
    SECTION("assign")
    {
        REQUIRE(type::is_assignable<module_locator>::value);
        REQUIRE(!type::has_trivial_assign<module_locator>::value);
    }

    SECTION("construct")
    {
        REQUIRE(type::is_constructible<module_locator>::value);
        REQUIRE(!type::has_trivial_constructor<module_locator>::value);
    }

    SECTION("copy")
    {
        REQUIRE(type::is_copyable<module_locator>::value);
        REQUIRE(!type::has_trivial_copy<module_locator>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(type::is_destructible<module_locator>::value);
        REQUIRE(!type::has_trivial_destructor<module_locator>::value);
    }

    SECTION("equality")
    {
        REQUIRE(!type::has_equality<module_locator>::value);
    }

    SECTION("pod")
    {
        REQUIRE(!type::is_pod<module_locator>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<module_locator>::value);
    }
}

TEST_CASE("module_locator.publish", "[gg.module_locator]")
{
    SECTION("publish")
    {
        module_locator locator;
        REQUIRE(!locator.has(1));

        mock_module module;
        locator.publish(1, &module);
        REQUIRE(locator.has(1));
    }
}

TEST_CASE("module_locator.unpublish", "[gg.module_locator]")
{
    SECTION("unpublish")
    {
        module_locator locator;
        REQUIRE(!locator.has(1));

        mock_module module;
        locator.publish(1, &module);
        REQUIRE(locator.has(1));

        locator.unpublish(1);
        REQUIRE(!locator.has(1));
    }
}

TEST_CASE("module_locator.get", "[gg.module_locator]")
{
    SECTION("get")
    {
        module_locator locator;
        mock_module module;
        locator.publish(1, &module);
        REQUIRE(&module == locator.get<mock_module>(1));
    }
}

//==============================================================================
}
//==============================================================================
