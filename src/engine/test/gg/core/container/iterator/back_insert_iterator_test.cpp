#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/container/iterator/back_insert_iterator.h"
#include "gg/core/memory/memory.h"

//==============================================================================
namespace gg::back_insert_iterator_test
{
//==============================================================================

struct mock_container
{
    typedef int8 item_type;

    mock_container(void) : m_index(0)
    {
        memory::zero(m_data, k_max_items);
    }

    void push_back(int8 item) noexcept
    {
        m_data[m_index++] = item;
    }

    static constexpr size_type k_max_items = 16;
    int8 m_data[k_max_items];
    size_type m_index;
};

using mock_back_insert_iterator = back_insert_iterator<mock_container>;

//==============================================================================

TEST_CASE("back_insert_iterator", "[gg.back_insert_iterator]")
{
    SECTION("assign")
    {
        REQUIRE(!type::is_copy_assignable<mock_back_insert_iterator>::value);
        REQUIRE(!type::is_trivially_assignable<mock_back_insert_iterator>::value);
    }

    SECTION("construct")
    {
        REQUIRE(!type::is_constructible<mock_back_insert_iterator>::value);
        REQUIRE(!type::is_trivially_constructible<mock_back_insert_iterator>::value);
    }

    SECTION("copy")
    {
        REQUIRE(type::is_copy_constructible<mock_back_insert_iterator>::value);
        REQUIRE(type::is_trivially_copy_constructible<mock_back_insert_iterator>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(type::is_destructible<mock_back_insert_iterator>::value);
        REQUIRE(type::is_trivially_destructible<mock_back_insert_iterator>::value);
    }

    SECTION("compare")
    {
        REQUIRE(!type::is_comparable<mock_back_insert_iterator>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<mock_back_insert_iterator>::value);
    }
}

TEST_CASE("back_insert_iterator.operator=", "[gg.back_insert_iterator]")
{
    SECTION("back_insert_iterator = item")
    {
        mock_container container;
        mock_back_insert_iterator inserter = back_inserter(container);

        *(inserter++) = 2;
        *(inserter++) = 4;
        *(++inserter) = 7;

        REQUIRE(container.m_data[0] == 2);
        REQUIRE(container.m_data[1] == 4);
        REQUIRE(container.m_data[2] == 7);
    }
}

//==============================================================================
}
//==============================================================================
