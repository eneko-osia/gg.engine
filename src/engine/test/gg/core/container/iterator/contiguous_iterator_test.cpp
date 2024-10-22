#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/container/iterator/contiguous_iterator.h"

//==============================================================================
namespace gg::contiguous_iterator_test
{
//==============================================================================

struct mock_container
{
    mock_container(void)
    {
        for (uint32 i = 0; i < k_max_items; ++i)
        {
            m_data[i] = (i << 1);
        }
    }
    ~mock_container(void) = default;

    static constexpr uint32 k_max_items = 16;
    uint32 m_data[k_max_items];
};

using iterator = contiguous_iterator<uint32, iterator_type::no_const>;
using const_iterator = contiguous_iterator<uint32, iterator_type::is_const>;

//==============================================================================

TEST_CASE("contiguous_iterator", "[gg.contiguous_iterator]")
{
    SECTION("no_const")
    {
        REQUIRE(!type::is_const<iterator::item_type>::value);

        SECTION("assign")
        {
            REQUIRE(type::is_copy_assignable<iterator>::value);
            REQUIRE(type::is_trivially_assignable<iterator>::value);
        }

        SECTION("construct")
        {
            REQUIRE(!type::is_constructible<iterator>::value);
            REQUIRE(!type::is_trivially_constructible<iterator>::value);
        }

        SECTION("copy")
        {
            REQUIRE(type::is_copy_constructible<iterator>::value);
            REQUIRE(!type::is_trivially_copy_constructible<iterator>::value);
        }

        SECTION("destroy")
        {
            REQUIRE(type::is_destructible<iterator>::value);
            REQUIRE(type::is_trivially_destructible<iterator>::value);
        }

        SECTION("compare")
        {
            REQUIRE(type::is_comparable<iterator>::value);
        }

        SECTION("polymorphic")
        {
            REQUIRE(!type::is_polymorphic<iterator>::value);
        }
    }

    SECTION("is_const")
    {
        REQUIRE(type::is_const<const_iterator::item_type>::value);

        SECTION("assign")
        {
            REQUIRE(type::is_copy_assignable<const_iterator>::value);
            REQUIRE(type::is_trivially_assignable<const_iterator>::value);
        }

        SECTION("construct")
        {
            REQUIRE(!type::is_constructible<const_iterator>::value);
            REQUIRE(!type::is_trivially_constructible<const_iterator>::value);
        }

        SECTION("copy")
        {
            REQUIRE(type::is_copy_constructible<const_iterator>::value);
            REQUIRE(type::is_trivially_copy_constructible<const_iterator>::value);
        }

        SECTION("destroy")
        {
            REQUIRE(type::is_destructible<const_iterator>::value);
            REQUIRE(type::is_trivially_destructible<const_iterator>::value);
        }

        SECTION("compare")
        {
            REQUIRE(type::is_comparable<const_iterator>::value);
        }

        SECTION("polymorphic")
        {
            REQUIRE(!type::is_polymorphic<const_iterator>::value);
        }
    }
}

TEST_CASE("contiguous_iterator.constructor", "[gg.contiguous_iterator]")
{
    SECTION("iterator(pointer)")
    {
        iterator::item_type value = 0;
        iterator it(&value);
        REQUIRE(&(*it) == &value);
    }

    SECTION("iterator(iterator)")
    {
        iterator::item_type value = 0;
        iterator it_1(&value);
        iterator it_2(it_1);
        REQUIRE(&(*it_1) == &(*it_2));
    }

    SECTION("const_iterator(pointer)")
    {
        const_iterator::item_type value = 0;
        const_iterator cit(&value);
        REQUIRE(&(*cit) == &value);
    }

    SECTION("const_iterator(const_iterator)")
    {
        const_iterator::item_type value = 0;
        const_iterator cit_1(&value);
        const_iterator cit_2(cit_1);
        REQUIRE(&(*cit_1) == &(*cit_2));
    }

    SECTION("const_iterator(iterator)")
    {
        iterator::item_type value = 0;
        iterator it(&value);
        const_iterator cit(it);
        REQUIRE(&(*it) == &(*cit));
    }
}

TEST_CASE("contiguous_iterator.operator-access", "[gg.contiguous_iterator]")
{
    SECTION("iterator[idx]")
    {
        mock_container container;
        iterator it(container.m_data);

        REQUIRE(it[3] == 6);
        REQUIRE(it[6] == 12);
        REQUIRE(it[7] == 14);
    }

    SECTION("const_iterator[idx]")
    {
        mock_container container;
        const_iterator cit(container.m_data);

        REQUIRE(cit[1] == 2);
        REQUIRE(cit[9] == 18);
        REQUIRE(cit[14] == 28);
    }
}

TEST_CASE("contiguous_iterator.operator*", "[gg.contiguous_iterator]")
{
    SECTION("*iterator")
    {
        iterator::item_type value = 123;
        iterator it(&value);
        REQUIRE(*it == value);
    }

    SECTION("*const_iterator")
    {
        const_iterator::item_type value = 123;
        const_iterator cit(&value);
        REQUIRE(*cit == value);
    }
}

TEST_CASE("contiguous_iterator.operator->", "[gg.contiguous_iterator]")
{
    struct mock_item { uint32 m_value; };
    typedef contiguous_iterator<
        mock_item, iterator_type::no_const> mock_item_iterator;
    typedef contiguous_iterator<
        mock_item, iterator_type::is_const> mock_item_const_iterator;

    SECTION("iterator->object")
    {
        mock_item_iterator::item_type item{ 123 };
        mock_item_iterator it(&item);
        REQUIRE(it->m_value == 123);
    }

    SECTION("const_iterator->object")
    {
        mock_item_const_iterator::item_type item{ 123 };
        mock_item_const_iterator cit(&item);
        REQUIRE(cit->m_value == 123);
    }
}

TEST_CASE("contiguous_iterator.operator++", "[gg.contiguous_iterator]")
{
    SECTION("++iterator")
    {
        mock_container container;
        iterator it(container.m_data);

        REQUIRE(*(++it) == 2);
        REQUIRE(*(++it) == 4);
        REQUIRE(*(++it) == 6);
    }

    SECTION("iterator++")
    {
        mock_container container;
        iterator it(container.m_data);

        REQUIRE(*(it++) == 0);
        REQUIRE(*(it++) == 2);
        REQUIRE(*(it++) == 4);
    }

    SECTION("++const_iterator")
    {
        mock_container container;
        const_iterator cit(container.m_data);

        REQUIRE(*(++cit) == 2);
        REQUIRE(*(++cit) == 4);
        REQUIRE(*(++cit) == 6);
    }

    SECTION("const_iterator++")
    {
        mock_container container;
        const_iterator cit(container.m_data);

        REQUIRE(*(cit++) == 0);
        REQUIRE(*(cit++) == 2);
        REQUIRE(*(cit++) == 4);
    }
}

TEST_CASE("contiguous_iterator.operator--", "[gg.contiguous_iterator]")
{
    SECTION("--iterator")
    {
        mock_container container;
        iterator it(container.m_data + mock_container::k_max_items - 1);

        REQUIRE(*(--it) == 28);
        REQUIRE(*(--it) == 26);
        REQUIRE(*(--it) == 24);
    }

    SECTION("iterator--")
    {
        mock_container container;
        iterator it(container.m_data + mock_container::k_max_items - 1);

        REQUIRE(*(it--) == 30);
        REQUIRE(*(it--) == 28);
        REQUIRE(*(it--) == 26);
    }

    SECTION("--const_iterator")
    {
        mock_container container;
        const_iterator cit(container.m_data + mock_container::k_max_items - 1);

        REQUIRE(*(--cit) == 28);
        REQUIRE(*(--cit) == 26);
        REQUIRE(*(--cit) == 24);
    }

    SECTION("const_iterator--")
    {
        mock_container container;
        const_iterator cit(container.m_data + mock_container::k_max_items - 1);

        REQUIRE(*(cit--) == 30);
        REQUIRE(*(cit--) == 28);
        REQUIRE(*(cit--) == 26);
    }
}

TEST_CASE("contiguous_iterator.operator+", "[gg.contiguous_iterator]")
{
    SECTION("iterator + offset")
    {
        mock_container container;
        iterator it(container.m_data);

        REQUIRE(*(it + 3) == 6);
        REQUIRE(*(it + 6) == 12);
        REQUIRE(*(it + 7) == 14);
    }

    SECTION("const_iterator + offset")
    {
        mock_container container;
        const_iterator cit(container.m_data);

        REQUIRE(*(cit + 1) == 2);
        REQUIRE(*(cit + 9) == 18);
        REQUIRE(*(cit + 14) == 28);
    }
}

TEST_CASE("contiguous_iterator.operator+=", "[gg.contiguous_iterator]")
{
    SECTION("iterator += offset")
    {
        mock_container container;
        iterator it(container.m_data);

        REQUIRE(*(it += 3) == 6);
        REQUIRE(*(it += 3) == 12);
        REQUIRE(*(it += 1) == 14);
    }

    SECTION("const_iterator += offset")
    {
        mock_container container;
        const_iterator cit(container.m_data);

        REQUIRE(*(cit += 1) == 2);
        REQUIRE(*(cit += 8) == 18);
        REQUIRE(*(cit += 5) == 28);
    }
}

TEST_CASE("contiguous_iterator.operator-", "[gg.contiguous_iterator]")
{
    SECTION("iterator - offset")
    {
        mock_container container;
        iterator it(container.m_data + mock_container::k_max_items - 1);

        REQUIRE(*(it - 3) == 24);
        REQUIRE(*(it - 6) == 18);
        REQUIRE(*(it - 7) == 16);
    }

    SECTION("iterator - iterator")
    {
        mock_container container;
        iterator it_start(container.m_data);
        iterator it_end(container.m_data + mock_container::k_max_items);
        REQUIRE((it_end - it_start) == mock_container::k_max_items);
    }

    SECTION("const_iterator - offset")
    {
        mock_container container;
        const_iterator cit(container.m_data + mock_container::k_max_items - 1);

        REQUIRE(*(cit - 1) == 28);
        REQUIRE(*(cit - 9) == 12);
        REQUIRE(*(cit - 14) == 2);
    }

    SECTION("const_iterator - const_iterator")
    {
        mock_container container;
        const_iterator cit_start(container.m_data);
        const_iterator cit_end(container.m_data + mock_container::k_max_items);
        REQUIRE((cit_end - cit_start) == mock_container::k_max_items);
    }
}

TEST_CASE("contiguous_iterator.operator-=", "[gg.contiguous_iterator]")
{
    SECTION("iterator -= offset")
    {
        mock_container container;
        iterator it(container.m_data + mock_container::k_max_items - 1);

        REQUIRE(*(it -= 3) == 24);
        REQUIRE(*(it -= 3) == 18);
        REQUIRE(*(it -= 1) == 16);
    }

    SECTION("const_iterator -= offset")
    {
        mock_container container;
        const_iterator cit(container.m_data + mock_container::k_max_items - 1);

        REQUIRE(*(cit -= 1) == 28);
        REQUIRE(*(cit -= 8) == 12);
        REQUIRE(*(cit -= 5) == 2);
    }
}

TEST_CASE("contiguous_iterator.operator==", "[gg.contiguous_iterator]")
{
    SECTION("iterator == iterator")
    {
        mock_container container;
        iterator it_1(container.m_data);
        iterator it_2(container.m_data);
        REQUIRE(it_1 == it_2);
    }

    SECTION("!(iterator == iterator)")
    {
        mock_container container;
        iterator it_1(container.m_data);
        iterator it_2(container.m_data);
        REQUIRE(!(it_1 == (++it_2)));
    }

    SECTION("const_iterator == const_iterator")
    {
        mock_container container;
        const_iterator cit_1(container.m_data);
        const_iterator cit_2(container.m_data);
        REQUIRE(cit_1 == cit_2);
    }

    SECTION("!(const_iterator == const_iterator)")
    {
        mock_container container;
        const_iterator cit_1(container.m_data);
        const_iterator cit_2(container.m_data);
        REQUIRE(!(cit_1 == (++cit_2)));
    }
}

TEST_CASE("contiguous_iterator.operator!=", "[gg.contiguous_iterator]")
{
    SECTION("iterator != iterator")
    {
        mock_container container;
        iterator it_1(container.m_data);
        iterator it_2(container.m_data);
        REQUIRE(!(it_1 != it_2));
    }

    SECTION("!(iterator != iterator)")
    {
        mock_container container;
        iterator it_1(container.m_data);
        iterator it_2(container.m_data);
        REQUIRE(it_1 != (++it_2));
    }

    SECTION("const_iterator != const_iterator")
    {
        mock_container container;
        const_iterator cit_1(container.m_data);
        const_iterator cit_2(container.m_data);
        REQUIRE(!(cit_1 != cit_2));
    }

    SECTION("!(const_iterator != const_iterator)")
    {
        mock_container container;
        const_iterator cit_1(container.m_data);
        const_iterator cit_2(container.m_data);
        REQUIRE(cit_1 != (++cit_2));
    }
}

TEST_CASE("contiguous_iterator.operator<", "[gg.contiguous_iterator]")
{
    SECTION("iterator < iterator")
    {
        mock_container container;
        iterator it_1(container.m_data);
        iterator it_2(container.m_data);
        REQUIRE(it_1 < (++it_2));
    }

    SECTION("!(iterator < iterator)")
    {
        mock_container container;
        iterator it_1(container.m_data);
        iterator it_2(container.m_data);
        REQUIRE(!(it_1 < it_2));
    }

    SECTION("const_iterator < const_iterator")
    {
        mock_container container;
        const_iterator cit_1(container.m_data);
        const_iterator cit_2(container.m_data);
        REQUIRE(cit_1 < (++cit_2));
    }

    SECTION("!(const_iterator < const_iterator)")
    {
        mock_container container;
        const_iterator cit_1(container.m_data);
        const_iterator cit_2(container.m_data);
        REQUIRE(!(cit_1 < cit_2));
    }
}

TEST_CASE("contiguous_iterator.operator<=", "[gg.contiguous_iterator]")
{
    SECTION("iterator <= iterator")
    {
        mock_container container;
        iterator it_1(container.m_data);
        iterator it_2(container.m_data);
        REQUIRE(it_1 <= it_2);
    }

    SECTION("iterator <= iterator")
    {
        mock_container container;
        iterator it_1(container.m_data);
        iterator it_2(container.m_data);
        REQUIRE(it_1 <= (++it_2));
    }

    SECTION("!(iterator <= iterator)")
    {
        mock_container container;
        iterator it_1(container.m_data);
        iterator it_2(container.m_data);
        REQUIRE(!((++it_1) < it_2));
    }

    SECTION("const_iterator <= const_iterator")
    {
        mock_container container;
        const_iterator cit_1(container.m_data);
        const_iterator cit_2(container.m_data);
        REQUIRE(cit_1 <= cit_2);
    }

    SECTION("const_iterator <= const_iterator")
    {
        mock_container container;
        const_iterator cit_1(container.m_data);
        const_iterator cit_2(container.m_data);
        REQUIRE(cit_1 <= (++cit_2));
    }

    SECTION("!(const_iterator <= const_iterator)")
    {
        mock_container container;
        const_iterator cit_1(container.m_data);
        const_iterator cit_2(container.m_data);
        REQUIRE(!((++cit_1) < cit_2));
    }
}

TEST_CASE("contiguous_iterator.operator>", "[gg.contiguous_iterator]")
{
    SECTION("iterator > iterator")
    {
        mock_container container;
        iterator it_1(container.m_data);
        iterator it_2(container.m_data);
        REQUIRE((++it_1) > it_2);
    }

    SECTION("!(iterator > iterator)")
    {
        mock_container container;
        iterator it_1(container.m_data);
        iterator it_2(container.m_data);
        REQUIRE(!(it_1 > it_2));
    }

    SECTION("const_iterator > const_iterator")
    {
        mock_container container;
        const_iterator cit_1(container.m_data);
        const_iterator cit_2(container.m_data);
        REQUIRE((++cit_1) > cit_2);
    }

    SECTION("!(const_iterator > const_iterator)")
    {
        mock_container container;
        const_iterator cit_1(container.m_data);
        const_iterator cit_2(container.m_data);
        REQUIRE(!(cit_1 > cit_2));
    }
}

TEST_CASE("contiguous_iterator.operator>=", "[gg.contiguous_iterator]")
{
    SECTION("iterator >= iterator")
    {
        mock_container container;
        iterator it_1(container.m_data);
        iterator it_2(container.m_data);
        REQUIRE(it_1 >= it_2);
    }

    SECTION("iterator >= iterator")
    {
        mock_container container;
        iterator it_1(container.m_data);
        iterator it_2(container.m_data);
        REQUIRE((++it_1) >= it_2);
    }

    SECTION("!(iterator >= iterator)")
    {
        mock_container container;
        iterator it_1(container.m_data);
        iterator it_2(container.m_data);
        REQUIRE(!(it_1 > (++it_2)));
    }

    SECTION("const_iterator >= const_iterator")
    {
        mock_container container;
        const_iterator cit_1(container.m_data);
        const_iterator cit_2(container.m_data);
        REQUIRE(cit_1 >= cit_2);
    }

    SECTION("const_iterator >= const_iterator")
    {
        mock_container container;
        const_iterator cit_1(container.m_data);
        const_iterator cit_2(container.m_data);
        REQUIRE((++cit_1) >= cit_2);
    }

    SECTION("!(const_iterator >= const_iterator)")
    {
        mock_container container;
        const_iterator cit_1(container.m_data);
        const_iterator cit_2(container.m_data);
        REQUIRE(!(cit_1 > (++cit_2)));
    }
}

//==============================================================================
}
//==============================================================================
