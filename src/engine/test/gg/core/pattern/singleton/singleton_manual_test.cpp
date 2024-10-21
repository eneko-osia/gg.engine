#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/pattern/singleton/singleton_manual.h"

//==============================================================================
namespace gg::singleton_manual_test
{
//==============================================================================

class mock_singleton : public singleton_manual<mock_singleton>
{
protected:

    friend class gg::memory;
    mock_singleton(void) = default;
    virtual ~mock_singleton(void) = default;
};

class mock_singleton_derived : public mock_singleton
{
private:

    friend class gg::memory;
    mock_singleton_derived(void) = default;
    ~mock_singleton_derived(void) = default;
};

//==============================================================================

TEST_CASE("singleton_manual", "[gg.singleton_manual]")
{
    SECTION("assign")
    {
        REQUIRE(
            !type::is_copy_assignable<singleton_manual<mock_singleton>>::value);
        REQUIRE(
            !type::is_trivially_assignable<singleton_manual<mock_singleton>>::value);
    }

    SECTION("construct")
    {
        REQUIRE(
            !type::is_constructible<singleton_manual<mock_singleton>>::value);
        REQUIRE(
            !type::is_trivially_constructible<singleton_manual<mock_singleton>>::value);
    }

    SECTION("copy")
    {
        REQUIRE(
            !type::is_copy_constructible<singleton_manual<mock_singleton>>::value);
        REQUIRE(
            !type::is_trivially_copy_constructible<singleton_manual<mock_singleton>>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(
            !type::is_destructible<singleton_manual<mock_singleton>>::value);
        REQUIRE(
            !type::is_trivially_destructible<singleton_manual<mock_singleton>>::value);
    }

    SECTION("compare")
    {
        REQUIRE(
            !type::is_comparable<singleton_manual<mock_singleton>>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<singleton_manual<mock_singleton>>::value);
    }
}

TEST_CASE("singleton_manual.create", "[gg.singleton_manual]")
{
    SECTION("create")
    {
        REQUIRE(!mock_singleton::is_available());
        mock_singleton::create();
        REQUIRE(mock_singleton::is_available());
        mock_singleton::destroy();
        REQUIRE(!mock_singleton::is_available());
    }

    SECTION("create<TYPE>")
    {
        REQUIRE(!mock_singleton::is_available());
        mock_singleton::create<mock_singleton_derived>();
        REQUIRE(mock_singleton::is_available());
        mock_singleton::destroy();
        REQUIRE(!mock_singleton::is_available());
    }
}

TEST_CASE("singleton_manual.get_instance", "[gg.singleton_manual]")
{
    SECTION("get_instance")
    {
        mock_singleton::create();
        mock_singleton& instance = mock_singleton::get_instance();
        REQUIRE(&instance == &mock_singleton::get_instance());
        mock_singleton::destroy();
    }

    SECTION("get_instance<TYPE>")
    {
        mock_singleton::create<mock_singleton_derived>();
        mock_singleton_derived& instance =
            mock_singleton::get_instance<mock_singleton_derived>();
        REQUIRE(
            &instance == &mock_singleton::get_instance<mock_singleton_derived>());
        mock_singleton::destroy();
    }
}

//==============================================================================
}
//==============================================================================
