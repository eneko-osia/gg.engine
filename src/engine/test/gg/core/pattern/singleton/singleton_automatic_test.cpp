#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/pattern/singleton/singleton_automatic.h"

//==============================================================================
namespace gg::singleton_automatic_test
{
//==============================================================================

class mock_singleton : public singleton_automatic<mock_singleton>
{
private:

    friend class gg::memory;
    mock_singleton(void) = default;
    ~mock_singleton(void) = default;
};

//==============================================================================

TEST_CASE("singleton_automatic", "[gg.singleton_automatic]")
{
    SECTION("assign")
    {
        REQUIRE(
            !type::is_copy_assignable<singleton_automatic<mock_singleton>>::value);
        REQUIRE(
            !type::is_trivially_assignable<singleton_automatic<mock_singleton>>::value);
    }

    SECTION("construct")
    {
        REQUIRE(
            !type::is_constructible<singleton_automatic<mock_singleton>>::value);
        REQUIRE(
            !type::is_trivially_constructible<singleton_automatic<mock_singleton>>::value);
    }

    SECTION("copy")
    {
        REQUIRE(
            !type::is_copy_constructible<singleton_automatic<mock_singleton>>::value);
        REQUIRE(
            !type::is_trivially_copy_constructible<singleton_automatic<mock_singleton>>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(
            !type::is_destructible<singleton_automatic<mock_singleton>>::value);
        REQUIRE(
            !type::is_trivially_destructible<singleton_automatic<mock_singleton>>::value);
    }

    SECTION("compare")
    {
        REQUIRE(
            !type::is_comparable<singleton_automatic<mock_singleton>>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<singleton_automatic<mock_singleton>>::value);
    }
}

TEST_CASE("singleton_automatic.get_instance", "[gg.singleton_automatic]")
{
    SECTION("get_instance")
    {
        mock_singleton const & instance = mock_singleton::get_instance();
        REQUIRE(&instance == &mock_singleton::get_instance());
    }
}

//==============================================================================
}
//==============================================================================
