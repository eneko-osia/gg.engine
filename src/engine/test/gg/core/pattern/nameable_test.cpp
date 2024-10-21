#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/pattern/nameable.h"
#include "gg/core/string/type/string_dynamic.h"
#include "gg/core/string/type/string_ref.h"
#include "gg/core/string/type/string_static.h"

//==============================================================================
namespace gg::nameable_test
{
//==============================================================================

class mock_nameable : public nameable<string_dynamic>
{
public:

    mock_nameable(void) noexcept = default;
    mock_nameable(mock_nameable const & obj) noexcept = default;
    mock_nameable(mock_nameable && obj) noexcept = default;

    mock_nameable(string_dynamic const & name) noexcept
        : nameable<string_dynamic>(name)
    {
    }

    mock_nameable(string_dynamic && name) noexcept
        : nameable<string_dynamic>(type::move(name))
    {
    }
};

class trivial_mock_nameable : public nameable<char8 const *>
{
public:

    trivial_mock_nameable(void) noexcept = default;
    trivial_mock_nameable(trivial_mock_nameable const & obj) noexcept = default;
    trivial_mock_nameable(trivial_mock_nameable && obj) noexcept = default;
};

//==============================================================================

TEST_CASE("nameable", "[gg.nameable]")
{
    SECTION("assign")
    {
        REQUIRE(!type::is_copy_assignable<nameable<string_dynamic>>::value);
        REQUIRE(!type::is_trivially_assignable<nameable<string_dynamic>>::value);

        REQUIRE(!type::is_copy_assignable<mock_nameable>::value);
        REQUIRE(!type::is_trivially_assignable<mock_nameable>::value);

        REQUIRE(!type::is_copy_assignable<nameable<char8 const *>>::value);
        REQUIRE(!type::is_trivially_assignable<nameable<char8 const *>>::value);

        REQUIRE(!type::is_copy_assignable<trivial_mock_nameable>::value);
        REQUIRE(!type::is_trivially_assignable<trivial_mock_nameable>::value);
    }

    SECTION("construct")
    {
        REQUIRE(!type::is_constructible<nameable<string_dynamic>>::value);
        REQUIRE(!type::is_trivially_constructible<nameable<string_dynamic>>::value);

        REQUIRE(type::is_constructible<mock_nameable>::value);
        REQUIRE(!type::is_trivially_constructible<mock_nameable>::value);

        REQUIRE(!type::is_constructible<nameable<char8 const *>>::value);
        REQUIRE(!type::is_trivially_constructible<nameable<char8 const *>>::value);

        REQUIRE(type::is_constructible<trivial_mock_nameable>::value);
        REQUIRE(type::is_trivially_constructible<trivial_mock_nameable>::value);
    }

    SECTION("copy")
    {
        REQUIRE(!type::is_copy_constructible<nameable<string_dynamic>>::value);
        REQUIRE(!type::is_trivially_copy_constructible<nameable<string_dynamic>>::value);

        REQUIRE(type::is_copy_constructible<mock_nameable>::value);
        REQUIRE(!type::is_trivially_copy_constructible<mock_nameable>::value);

        REQUIRE(!type::is_copy_constructible<nameable<char8 const *>>::value);
        REQUIRE(!type::is_trivially_copy_constructible<nameable<char8 const *>>::value);

        REQUIRE(type::is_copy_constructible<trivial_mock_nameable>::value);
        REQUIRE(type::is_trivially_copy_constructible<trivial_mock_nameable>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(!type::is_destructible<nameable<string_dynamic>>::value);
        REQUIRE(!type::is_trivially_destructible<nameable<string_dynamic>>::value);

        REQUIRE(type::is_destructible<mock_nameable>::value);
        REQUIRE(!type::is_trivially_destructible<mock_nameable>::value);

        REQUIRE(!type::is_destructible<nameable<char8 const *>>::value);
        REQUIRE(!type::is_trivially_destructible<nameable<char8 const *>>::value);

        REQUIRE(type::is_destructible<trivial_mock_nameable>::value);
        REQUIRE(type::is_trivially_destructible<trivial_mock_nameable>::value);
    }

    SECTION("compare")
    {
        REQUIRE(!type::is_comparable<nameable<string_dynamic>>::value);
        REQUIRE(!type::is_comparable<mock_nameable>::value);
        REQUIRE(!type::is_comparable<nameable<char8 const *>>::value);
        REQUIRE(!type::is_comparable<trivial_mock_nameable>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<nameable<string_dynamic>>::value);
        REQUIRE(!type::is_polymorphic<mock_nameable>::value);
        REQUIRE(!type::is_polymorphic<nameable<char8 const *>>::value);
        REQUIRE(!type::is_polymorphic<trivial_mock_nameable>::value);
    }

    SECTION("sizeof")
    {
        REQUIRE(
            sizeof(nameable<string_dynamic>) ==
            sizeof(nameable<string_dynamic>::name_type));
        REQUIRE(
            sizeof(mock_nameable) ==
            sizeof(mock_nameable::name_type));
        REQUIRE(
            sizeof(nameable<uint32>) ==
            sizeof(nameable<uint32>::name_type));
        REQUIRE(
            sizeof(trivial_mock_nameable) ==
            sizeof(trivial_mock_nameable::name_type));
    }
}

TEST_CASE("nameable.constructor", "[gg.nameable]")
{
    SECTION("nameable")
    {
        mock_nameable nameable;
        REQUIRE(nameable.is_named(string::k_empty));
    }

    SECTION("nameable(name_type)")
    {
        string_dynamic name("123");
        mock_nameable nameable(name);
        REQUIRE(nameable.is_named(name));
        REQUIRE(name == "123");
    }

    SECTION("nameable(rvalue_name_type)")
    {
        string_dynamic name("123");
        string_dynamic moved_name(name);
        mock_nameable nameable(type::move(moved_name));
        REQUIRE(nameable.is_named(name));
        REQUIRE(moved_name.is_empty());
        REQUIRE(name == "123");
    }

    SECTION("nameable(nameable)")
    {
        string_dynamic name("123");
        mock_nameable copied_nameable(name);
        mock_nameable nameable(copied_nameable);
        REQUIRE(nameable.is_named(copied_nameable.get_name()));
    }

    SECTION("nameable(rvalue_nameable)")
    {
        mock_nameable moved_nameable("123");
        mock_nameable copied_nameable(moved_nameable);
        mock_nameable nameable(type::move(moved_nameable));
        REQUIRE(nameable.is_named(copied_nameable.get_name()));
        REQUIRE(moved_nameable.get_name().is_empty());
    }
}

TEST_CASE("nameable.get_name", "[gg.nameable]")
{
    SECTION("get_name")
    {
        mock_nameable nameable("123");
        REQUIRE(nameable.get_name() == "123");
    }
}

TEST_CASE("nameable.set_name", "[gg.nameable]")
{
    SECTION("set_name(name_type)")
    {
        string_dynamic name("123");
        mock_nameable nameable;
        nameable.set_name(name);
        REQUIRE(nameable.is_named(name));
        REQUIRE(name == "123");
    }

    SECTION("set_name(rvalue_name_type)")
    {
        string_dynamic name("123");
        string_dynamic moved_name(name);
        mock_nameable nameable;
        nameable.set_name(type::move(moved_name));
        REQUIRE(nameable.is_named(name));
        REQUIRE(moved_name.is_empty());
        REQUIRE(name == "123");
    }

    SECTION("set_name<TYPE>(name_type)")
    {
        string_ref referenced_string("123");
        mock_nameable nameable;
        nameable.set_name(referenced_string);
        REQUIRE(nameable.is_named("123"));
    }
}

TEST_CASE("nameable.is_named", "[gg.nameable]")
{
    SECTION("is_named")
    {
        mock_nameable nameable;
        nameable.set_name("123");
        REQUIRE(nameable.is_named("123"));
    }

    SECTION("!is_named")
    {
        mock_nameable nameable;
        nameable.set_name("123");
        REQUIRE(!nameable.is_named("321"));
    }
}

//==============================================================================
}
//==============================================================================
