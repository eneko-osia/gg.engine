#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/pattern/sizeable.h"

//==============================================================================
namespace gg::sizeable_test
{
//==============================================================================

class mock_size
{
public:

    // constructors

    mock_size(void) noexcept : m_size(0)
    {
    }

    mock_size(uint32 size) noexcept : m_size(size)
    {
    }

    mock_size(mock_size const & size) noexcept : m_size(size.m_size)
    {
    }

    mock_size(mock_size && size) noexcept : m_size(size.m_size)
    {
        size.m_size = 0;
    }

    // operators

    mock_size & operator=(mock_size const & size) noexcept
    {
        m_size = size.m_size;
        return *this;
    }

    mock_size & operator=(mock_size && size) noexcept
    {
        *this = size;
        size.m_size = 0;
        return *this;
    }

    bool8 operator==(mock_size const & size) const noexcept
    {
        return m_size == size.m_size;
    }

private:

    uint32 m_size;
};

class mock_sizeable : public sizeable<mock_size>
{
public:

    mock_sizeable(void) noexcept = default;
    mock_sizeable(mock_sizeable const & obj) noexcept = default;
    mock_sizeable(mock_sizeable && obj) noexcept = default;

    mock_sizeable(mock_size const & height, mock_size const & width) noexcept
        : sizeable<mock_size>(height, width)
    {
    }

    mock_sizeable(mock_size && height, mock_size && width) noexcept
        : sizeable<mock_size>(type::move(height), type::move(width))
    {
    }
};

class trivial_mock_sizeable : public sizeable<uint32>
{
public:

    trivial_mock_sizeable(void) noexcept = default;
    trivial_mock_sizeable(trivial_mock_sizeable const & obj) noexcept = default;
    trivial_mock_sizeable(trivial_mock_sizeable && obj) noexcept = default;
};

//==============================================================================

TEST_CASE("sizeable", "[gg.sizeable]")
{
    SECTION("assign")
    {
        REQUIRE(!type::is_copy_assignable<sizeable<mock_size>>::value);
        REQUIRE(!type::is_trivially_assignable<sizeable<mock_size>>::value);

        REQUIRE(!type::is_copy_assignable<mock_sizeable>::value);
        REQUIRE(!type::is_trivially_assignable<mock_sizeable>::value);

        REQUIRE(!type::is_copy_assignable<sizeable<uint32>>::value);
        REQUIRE(!type::is_trivially_assignable<sizeable<uint32>>::value);

        REQUIRE(!type::is_copy_assignable<trivial_mock_sizeable>::value);
        REQUIRE(!type::is_trivially_assignable<trivial_mock_sizeable>::value);
    }

    SECTION("construct")
    {
        REQUIRE(!type::is_constructible<sizeable<mock_size>>::value);
        REQUIRE(!type::is_trivially_constructible<sizeable<mock_size>>::value);

        REQUIRE(type::is_constructible<mock_sizeable>::value);
        REQUIRE(!type::is_trivially_constructible<mock_sizeable>::value);

        REQUIRE(!type::is_constructible<sizeable<uint32>>::value);
        REQUIRE(!type::is_trivially_constructible<sizeable<uint32>>::value);

        REQUIRE(type::is_constructible<trivial_mock_sizeable>::value);
        REQUIRE(type::is_trivially_constructible<trivial_mock_sizeable>::value);
    }

    SECTION("copy")
    {
        REQUIRE(!type::is_copy_constructible<sizeable<mock_size>>::value);
        REQUIRE(!type::is_trivially_copy_constructible<sizeable<mock_size>>::value);

        REQUIRE(type::is_copy_constructible<mock_sizeable>::value);
        REQUIRE(!type::is_trivially_copy_constructible<mock_sizeable>::value);

        REQUIRE(!type::is_copy_constructible<sizeable<uint32>>::value);
        REQUIRE(!type::is_trivially_copy_constructible<sizeable<uint32>>::value);

        REQUIRE(type::is_copy_constructible<trivial_mock_sizeable>::value);
        REQUIRE(type::is_trivially_copy_constructible<trivial_mock_sizeable>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(!type::is_destructible<sizeable<mock_size>>::value);
        REQUIRE(!type::is_trivially_destructible<sizeable<mock_size>>::value);

        REQUIRE(type::is_destructible<mock_sizeable>::value);
        REQUIRE(type::is_trivially_destructible<mock_sizeable>::value);

        REQUIRE(!type::is_destructible<sizeable<uint32>>::value);
        REQUIRE(!type::is_trivially_destructible<sizeable<uint32>>::value);

        REQUIRE(type::is_destructible<trivial_mock_sizeable>::value);
        REQUIRE(type::is_trivially_destructible<trivial_mock_sizeable>::value);
    }

    SECTION("compare")
    {
        REQUIRE(!type::is_comparable<sizeable<mock_size>>::value);
        REQUIRE(!type::is_comparable<mock_sizeable>::value);
        REQUIRE(!type::is_comparable<sizeable<uint32>>::value);
        REQUIRE(!type::is_comparable<trivial_mock_sizeable>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<sizeable<mock_size>>::value);
        REQUIRE(!type::is_polymorphic<mock_sizeable>::value);
        REQUIRE(!type::is_polymorphic<sizeable<uint32>>::value);
        REQUIRE(!type::is_polymorphic<trivial_mock_sizeable>::value);
    }

    SECTION("sizeof")
    {
        REQUIRE(
            sizeof(sizeable<mock_size>) ==
            (sizeof(sizeable<mock_size>::size_type) << 1));
        REQUIRE(
            sizeof(mock_sizeable) ==
            (sizeof(mock_sizeable::size_type) << 1));
        REQUIRE(
            sizeof(sizeable<uint32>) ==
            (sizeof(sizeable<uint32>::size_type) << 1));
        REQUIRE(
            sizeof(trivial_mock_sizeable) ==
            (sizeof(trivial_mock_sizeable::size_type) << 1));
    }
}

TEST_CASE("sizeable.constructor", "[gg.sizeable]")
{
    SECTION("sizeable")
    {
        mock_sizeable sizeable;
        REQUIRE(sizeable.is_sized(0, 0));
    }

    SECTION("sizeable(size_type)")
    {
        mock_size height(123);
        mock_size width(456);
        mock_sizeable sizeable(height, width);
        REQUIRE(sizeable.is_sized(height, width));
        REQUIRE(width == 456);
        REQUIRE(height == 123);
    }

    SECTION("sizeable(rvalue_size_type)")
    {
        mock_size height(123);
        mock_size width(456);
        mock_size moved_height(height);
        mock_size moved_width(width);
        mock_sizeable sizeable(
            type::move(moved_height), type::move(moved_width));
        REQUIRE(sizeable.is_sized(height, width));
        REQUIRE(moved_width == 0);
        REQUIRE(moved_height == 0);
        REQUIRE(width == 456);
        REQUIRE(height == 123);
    }

    SECTION("sizeable(sizeable)")
    {
        mock_size height(123);
        mock_size width(456);
        mock_sizeable copied_sizeable(height, width);
        mock_sizeable sizeable(copied_sizeable);
        REQUIRE(
            sizeable.is_sized(
                copied_sizeable.get_height(), copied_sizeable.get_width()));
    }

    SECTION("sizeable(rvalue_sizeable)")
    {
        mock_sizeable moved_sizeable(123, 456);
        mock_sizeable copied_sizeable(moved_sizeable);
        mock_sizeable sizeable(type::move(moved_sizeable));
        REQUIRE(
            sizeable.is_sized(
                copied_sizeable.get_height(), copied_sizeable.get_width()));
        REQUIRE(moved_sizeable.is_sized(0, 0));
    }
}

TEST_CASE("sizeable.get_height", "[gg.sizeable]")
{
    SECTION("get_height")
    {
        mock_sizeable sizeable(123, 456);
        REQUIRE(sizeable.get_height() == 123);
    }
}

TEST_CASE("sizeable.set_height", "[gg.sizeable]")
{
    SECTION("set_height(size_type)")
    {
        mock_size height(123);
        mock_sizeable sizeable(0, 0);
        sizeable.set_height(height);
        REQUIRE(sizeable.is_sized(height, 0));
        REQUIRE(height == 123);
    }

    SECTION("set_height(rvalue_size_type)")
    {
        mock_size height(123);
        mock_size moved_height(height);
        mock_sizeable sizeable(0, 0);
        sizeable.set_height(type::move(moved_height));
        REQUIRE(sizeable.is_sized(height, 0));
        REQUIRE(moved_height == 0);
        REQUIRE(height == 123);
    }

    SECTION("set_height<TYPE>(size_type)")
    {
        mock_sizeable sizeable(0, 0);
        sizeable.set_height(123);
        REQUIRE(sizeable.is_sized(123, 0));
    }
}

TEST_CASE("sizeable.get_width", "[gg.sizeable]")
{
    SECTION("get_width")
    {
        mock_sizeable sizeable(123, 456);
        REQUIRE(sizeable.get_width() == 456);
    }
}

TEST_CASE("sizeable.set_width", "[gg.sizeable]")
{
    SECTION("set_width(size_type)")
    {
        mock_size width(123);
        mock_sizeable sizeable(0, 0);
        sizeable.set_width(width);
        REQUIRE(sizeable.is_sized(0, width));
        REQUIRE(width == 123);
    }

    SECTION("set_width(rvalue_size_type)")
    {
        mock_size width(123);
        mock_size moved_width(width);
        mock_sizeable sizeable(0, 0);
        sizeable.set_width(type::move(moved_width));
        REQUIRE(sizeable.is_sized(0, width));
        REQUIRE(moved_width == 0);
        REQUIRE(width == 123);
    }

    SECTION("set_width<TYPE>(size_type)")
    {
        mock_sizeable sizeable(0, 0);
        sizeable.set_width(123);
        REQUIRE(sizeable.is_sized(0, 123));
    }
}

TEST_CASE("sizeable.is_sized", "[gg.sizeable]")
{
    SECTION("is_sized")
    {
        mock_sizeable sizeable(0, 0);
        sizeable.set_height(123);
        sizeable.set_width(456);
        REQUIRE(sizeable.is_sized(123, 456));
    }

    SECTION("!is_sized")
    {
        mock_sizeable sizeable(0, 0);
        sizeable.set_height(123);
        sizeable.set_width(456);
        REQUIRE(!sizeable.is_sized(321, 654));
    }
}

//==============================================================================
}
//==============================================================================
