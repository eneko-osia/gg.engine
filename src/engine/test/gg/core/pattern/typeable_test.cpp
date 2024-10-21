#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/pattern/typeable.h"

//==============================================================================
namespace gg::typeable_test
{
//==============================================================================

class mock_type
{
public:

    // constructors

    mock_type(void) noexcept : m_type (0)
    {
    }

    mock_type(uint32 type) noexcept : m_type(type)
    {
    }

    mock_type(mock_type const & type) noexcept : m_type(type.m_type)
    {
    }

    mock_type(mock_type && type) noexcept : m_type(type.m_type)
    {
        type.m_type = 0;
    }

    // operators

    mock_type & operator=(mock_type const & type) noexcept
    {
        m_type = type.m_type;
        return *this;
    }

    mock_type & operator=(mock_type && type) noexcept
    {
        *this = type;
        type.m_type = 0;
        return *this;
    }

    bool8 operator==(mock_type const & type) const noexcept
    {
        return m_type == type.m_type;
    }

private:

    uint32 m_type;
};

class mock_typeable : public typeable<mock_type>
{
public:

    mock_typeable(void) noexcept = default;
    mock_typeable(mock_typeable const & obj) noexcept = default;
    mock_typeable(mock_typeable && obj) noexcept = default;

    mock_typeable(mock_type const & type) noexcept
        : typeable<mock_type>(type)
    {
    }

    mock_typeable(mock_type && type) noexcept
        : typeable<mock_type>(type::move(type))
    {
    }
};

class trivial_mock_typeable : public typeable<uint32>
{
public:

    trivial_mock_typeable(void) noexcept = default;
    trivial_mock_typeable(trivial_mock_typeable const & obj) noexcept = default;
    trivial_mock_typeable(trivial_mock_typeable && obj) noexcept = default;
};

//==============================================================================

TEST_CASE("typeable", "[gg.typeable]")
{
    SECTION("assign")
    {
        REQUIRE(!type::is_copy_assignable<typeable<mock_type>>::value);
        REQUIRE(!type::is_trivially_assignable<typeable<mock_type>>::value);

        REQUIRE(!type::is_copy_assignable<mock_typeable>::value);
        REQUIRE(!type::is_trivially_assignable<mock_typeable>::value);

        REQUIRE(!type::is_copy_assignable<typeable<uint32>>::value);
        REQUIRE(!type::is_trivially_assignable<typeable<uint32>>::value);

        REQUIRE(!type::is_copy_assignable<trivial_mock_typeable>::value);
        REQUIRE(!type::is_trivially_assignable<trivial_mock_typeable>::value);
    }

    SECTION("construct")
    {
        REQUIRE(!type::is_constructible<typeable<mock_type>>::value);
        REQUIRE(!type::is_trivially_constructible<typeable<mock_type>>::value);

        REQUIRE(type::is_constructible<mock_typeable>::value);
        REQUIRE(!type::is_trivially_constructible<mock_typeable>::value);

        REQUIRE(!type::is_constructible<typeable<uint32>>::value);
        REQUIRE(!type::is_trivially_constructible<typeable<uint32>>::value);

        REQUIRE(type::is_constructible<trivial_mock_typeable>::value);
        REQUIRE(type::is_trivially_constructible<trivial_mock_typeable>::value);
    }

    SECTION("copy")
    {
        REQUIRE(!type::is_copy_constructible<typeable<mock_type>>::value);
        REQUIRE(!type::is_trivially_copy_constructible<typeable<mock_type>>::value);

        REQUIRE(type::is_copy_constructible<mock_typeable>::value);
        REQUIRE(!type::is_trivially_copy_constructible<mock_typeable>::value);

        REQUIRE(!type::is_copy_constructible<typeable<uint32>>::value);
        REQUIRE(!type::is_trivially_copy_constructible<typeable<uint32>>::value);

        REQUIRE(type::is_copy_constructible<trivial_mock_typeable>::value);
        REQUIRE(type::is_trivially_copy_constructible<trivial_mock_typeable>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(!type::is_destructible<typeable<mock_type>>::value);
        REQUIRE(!type::is_trivially_destructible<typeable<mock_type>>::value);

        REQUIRE(type::is_destructible<mock_typeable>::value);
        REQUIRE(type::is_trivially_destructible<mock_typeable>::value);

        REQUIRE(!type::is_destructible<typeable<uint32>>::value);
        REQUIRE(!type::is_trivially_destructible<typeable<uint32>>::value);

        REQUIRE(type::is_destructible<trivial_mock_typeable>::value);
        REQUIRE(type::is_trivially_destructible<trivial_mock_typeable>::value);
    }

    SECTION("compare")
    {
        REQUIRE(!type::is_comparable<typeable<mock_type>>::value);
        REQUIRE(!type::is_comparable<mock_typeable>::value);
        REQUIRE(!type::is_comparable<typeable<uint32>>::value);
        REQUIRE(!type::is_comparable<trivial_mock_typeable>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<typeable<mock_type>>::value);
        REQUIRE(!type::is_polymorphic<mock_typeable>::value);
        REQUIRE(!type::is_polymorphic<typeable<uint32>>::value);
        REQUIRE(!type::is_polymorphic<trivial_mock_typeable>::value);
    }

    SECTION("sizeof")
    {
        REQUIRE(
            sizeof(typeable<mock_type>) ==
            sizeof(typeable<mock_type>::item_type));
        REQUIRE(
            sizeof(mock_typeable) ==
            sizeof(mock_typeable::item_type));
        REQUIRE(
            sizeof(typeable<uint32>) ==
            sizeof(typeable<uint32>::item_type));
        REQUIRE(
            sizeof(trivial_mock_typeable) ==
            sizeof(trivial_mock_typeable::item_type));
    }
}

TEST_CASE("typeable.constructor", "[gg.typeable]")
{
    SECTION("typeable")
    {
        mock_typeable typeable;
        REQUIRE(typeable.is_type(0));
    }

    SECTION("typeable(type)")
    {
        mock_type type(123);
        mock_typeable typeable(type);
        REQUIRE(typeable.is_type(type));
        REQUIRE(type == 123);
    }

    SECTION("typeable(rvalue_type_type)")
    {
        mock_type type(123);
        mock_type moved_type(type);
        mock_typeable typeable(type::move(moved_type));
        REQUIRE(typeable.is_type(type));
        REQUIRE(moved_type == 0);
        REQUIRE(type == 123);
    }

    SECTION("typeable(typeable)")
    {
        mock_type type(123);
        mock_typeable copied_typeable(type);
        mock_typeable typeable(copied_typeable);
        REQUIRE(typeable.is_type(copied_typeable.get_type()));
    }

    SECTION("typeable(rvalue_typeable)")
    {
        mock_typeable moved_typeable(123);
        mock_typeable copied_typeable(moved_typeable);
        mock_typeable typeable(type::move(moved_typeable));
        REQUIRE(typeable.is_type(copied_typeable.get_type()));
        REQUIRE(moved_typeable.is_type(0));
    }
}

TEST_CASE("typeable.get_type", "[gg.typeable]")
{
    SECTION("get_type")
    {
        mock_typeable typeable(123);
        REQUIRE(typeable.get_type() == 123);
    }
}

TEST_CASE("typeable.set_type", "[gg.typeable]")
{
    SECTION("set_type(type)")
    {
        mock_type type(123);
        mock_typeable typeable(0);
        typeable.set_type(type);
        REQUIRE(typeable.is_type(type));
        REQUIRE(type == 123);
    }

    SECTION("set_type(rvalue_type_type)")
    {
        mock_type type(123);
        mock_type moved_type(type);
        mock_typeable typeable(0);
        typeable.set_type(type::move(moved_type));
        REQUIRE(typeable.is_type(type));
        REQUIRE(moved_type == 0);
        REQUIRE(type == 123);
    }

    SECTION("set_type<TYPE>(type)")
    {
        mock_typeable typeable(0);
        typeable.set_type(123);
        REQUIRE(typeable.is_type(123));
    }
}

TEST_CASE("typeable.is_type", "[gg.typeable]")
{
    SECTION("is_type")
    {
        mock_typeable typeable(0);
        typeable.set_type(123);
        REQUIRE(typeable.is_type(123));
    }

    SECTION("!is_type")
    {
        mock_typeable typeable(0);
        typeable.set_type(123);
        REQUIRE(!typeable.is_type(321));
    }
}

//==============================================================================
}
//==============================================================================
