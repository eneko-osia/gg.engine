#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/container/map/hash_map.h"
#include <functional>

//==============================================================================
namespace gg::hash_map_test
{
//==============================================================================

class mock_item
{
public:

    explicit mock_item(int32 value = 0) noexcept : m_value(value)
    {
    }
    ~mock_item(void) noexcept = default;

    bool8 operator==(mock_item const & item) const noexcept
    {
        return m_value == item.m_value;
    }

    int32 m_value;
};

using mock_item_map = hash_map<int32, mock_item>;

//==============================================================================

TEST_CASE("hash_map", "[gg.hash_map]")
{
    SECTION("assign")
    {
        REQUIRE(type::is_copy_assignable<mock_item_map>::value);
        REQUIRE(!type::is_trivially_assignable<mock_item_map>::value);
    }

    SECTION("construct")
    {
        REQUIRE(type::is_constructible<mock_item_map>::value);
        REQUIRE(!type::is_trivially_constructible<mock_item_map>::value);
    }

    SECTION("copy")
    {
        REQUIRE(type::is_copy_constructible<mock_item_map>::value);
        REQUIRE(!type::is_trivially_copy_constructible<mock_item_map>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(type::is_destructible<mock_item_map>::value);
        REQUIRE(!type::is_trivially_destructible<mock_item_map>::value);
    }

    SECTION("compare")
    {
        REQUIRE(type::is_comparable<mock_item_map>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<mock_item_map>::value);
    }
}

TEST_CASE("hash_map.constructor", "[gg.hash_map]")
{
    SECTION("hash_map()")
    {
        mock_item_map hash_map;

        // REQUIRE(hash_map.begin() == nullptr);
        REQUIRE(hash_map.begin() == hash_map.end());
        // REQUIRE(hash_map.max_size() == 0);
        REQUIRE(hash_map.size() == 0);
        REQUIRE(hash_map.is_empty());
    }

    SECTION("hash_map(hash_map)")
    {
        mock_item_map copied_map;
        copied_map.insert(1, mock_item(1));
        copied_map.insert(2, mock_item(2));
        copied_map.insert(3, mock_item(3));

        mock_item_map hash_map(copied_map);
        REQUIRE((hash_map == copied_map));
        REQUIRE(hash_map.max_size() == copied_map.max_size());
        REQUIRE(hash_map.size() == 3);
    }

    SECTION("hash_map(rvalue_map)")
    {
        mock_item_map moved_map;
        moved_map.insert(1, mock_item(1));
        moved_map.insert(2, mock_item(2));
        moved_map.insert(3, mock_item(3));

        mock_item_map copied_map(moved_map);
        mock_item_map hash_map(type::move(moved_map));
        REQUIRE((hash_map == copied_map));
        REQUIRE(hash_map.max_size() == copied_map.max_size());
        REQUIRE(hash_map.size() == 3);

        // REQUIRE(moved_map.begin() == nullptr);
        REQUIRE(moved_map.begin() == moved_map.end());
        // REQUIRE(moved_map.max_size() == 0);
        REQUIRE(moved_map.size() == 0);
        REQUIRE(moved_map.is_empty());
    }
}

TEST_CASE("hash_map.operator-access", "[gg.hash_map]")
{
    SECTION("operator[key]")
    {
        mock_item_map hash_map;
        hash_map.insert(1, mock_item(3));
        hash_map.insert(2, mock_item(2));
        hash_map.insert(3, mock_item(1));

        REQUIRE(hash_map[1].m_value == 3);
        REQUIRE(hash_map[2].m_value == 2);
        REQUIRE(hash_map[3].m_value == 1);
    }
}

TEST_CASE("hash_map.operator=", "[gg.hash_map]")
{
    SECTION("hash_map = hash_map")
    {
        mock_item_map copied_map;
        copied_map.insert(1, mock_item(1));
        copied_map.insert(2, mock_item(2));
        copied_map.insert(3, mock_item(3));

        mock_item_map hash_map;
        hash_map = copied_map;
        REQUIRE((hash_map == copied_map));
        REQUIRE(hash_map.max_size() == copied_map.max_size());
        REQUIRE(hash_map.size() == 3);
    }

    SECTION("hash_map = rvalue_map")
    {
        mock_item_map moved_map;
        moved_map.insert(1, mock_item(1));
        moved_map.insert(2, mock_item(2));
        moved_map.insert(3, mock_item(3));

        mock_item_map copied_map(moved_map);
        mock_item_map hash_map;
        hash_map = type::move(moved_map);
        REQUIRE((hash_map == copied_map));
        REQUIRE(hash_map.max_size() == copied_map.max_size());
        REQUIRE(hash_map.size() == 3);

        // REQUIRE(moved_map.begin() == nullptr);
        REQUIRE(moved_map.begin() == moved_map.end());
        // REQUIRE(moved_map.max_size() == 0);
        REQUIRE(moved_map.size() == 0);
        REQUIRE(moved_map.is_empty());
    }
}

TEST_CASE("hash_map.operator==", "[gg.hash_map]")
{
    SECTION("hash_map == hash_map")
    {
        mock_item_map map_1;
        mock_item_map map_2;

        map_1.insert(1, mock_item(1));
        map_1.insert(2, mock_item(2));
        map_1.insert(3, mock_item(3));

        map_2.insert(1, mock_item(1));
        map_2.insert(2, mock_item(2));
        map_2.insert(3, mock_item(3));

        REQUIRE((map_1 == map_2));
    }

    SECTION("hash_map == hash_map(wrong data)")
    {
        mock_item_map map_1;
        mock_item_map map_2;

        map_1.insert(1, mock_item(1));
        map_1.insert(2, mock_item(2));
        map_1.insert(3, mock_item(3));

        map_2.insert(1, mock_item(1));
        map_2.insert(2, mock_item(2));
        map_2.insert(3, mock_item(2));

        REQUIRE(!(map_1 == map_2));
    }

    SECTION("hash_map == hash_map(wrong size)")
    {
        mock_item_map map_1;
        mock_item_map map_2;

        map_1.insert(1, mock_item(1));
        map_1.insert(2, mock_item(2));
        map_1.insert(3, mock_item(3));

        map_2.insert(1, mock_item(1));
        map_2.insert(2, mock_item(2));
        map_2.insert(3, mock_item(3));
        map_2.insert(4, mock_item(4));

        REQUIRE(!(map_1 == map_2));
    }
}

TEST_CASE("hash_map.operator!=", "[gg.hash_map]")
{
    SECTION("hash_map != hash_map(wrong data)")
    {
        mock_item_map map_1;
        mock_item_map map_2;

        map_1.insert(1, mock_item(1));
        map_1.insert(2, mock_item(2));
        map_1.insert(3, mock_item(3));

        map_2.insert(1, mock_item(3));
        map_2.insert(2, mock_item(2));
        map_2.insert(3, mock_item(1));

        REQUIRE((map_1 != map_2));
    }

    SECTION("hash_map != hash_map(wrong size)")
    {
        mock_item_map map_1;
        mock_item_map map_2;

        map_1.insert(1, mock_item(1));
        map_1.insert(2, mock_item(2));
        map_1.insert(3, mock_item(3));

        map_2.insert(1, mock_item(1));
        map_2.insert(2, mock_item(2));

        REQUIRE((map_1 != map_2));
    }
}

TEST_CASE("hash_map.begin", "[gg.hash_map]")
{
    SECTION("begin")
    {
        mock_item_map hash_map;
        hash_map.insert(3, mock_item(2));
        REQUIRE(hash_map.begin()->second.m_value == 2);
    }
}

TEST_CASE("hash_map.clear", "[gg.hash_map]")
{
    SECTION("clear")
    {
        mock_item_map hash_map;
        hash_map.insert(1, mock_item(1));
        hash_map.insert(2, mock_item(2));
        hash_map.insert(3, mock_item(3));
        REQUIRE(!hash_map.is_empty());

        hash_map.clear();
        REQUIRE(hash_map.is_empty());
    }
}

TEST_CASE("hash_map.emplace", "[gg.hash_map]")
{
    SECTION("emplace key arguments")
    {
        mock_item_map hash_map;
        hash_map.insert(1, mock_item(1));
        hash_map.insert(2, mock_item(2));
        hash_map.insert(3, mock_item(3));

        hash_map.emplace(4, 4);
        REQUIRE(hash_map.size() == 4);
        REQUIRE(hash_map[4].m_value == 4);

        // REQUIRE(hash_map.max_size() == 16);
    }
}

TEST_CASE("hash_map.end", "[gg.hash_map]")
{
    SECTION("end")
    {
        mock_item_map hash_map;
        hash_map.insert(3, mock_item(3));
        REQUIRE(++hash_map.begin() == hash_map.end());
    }
}

TEST_CASE("hash_map.erase", "[gg.hash_map]")
{
    SECTION("erase key")
    {
        mock_item_map hash_map;
        hash_map.insert(1, mock_item(1));
        hash_map.insert(2, mock_item(2));
        hash_map.insert(3, mock_item(3));

        REQUIRE(hash_map.has(1));
        REQUIRE(hash_map.find(1)->second.m_value == 1);
        hash_map.erase(1);
        REQUIRE(hash_map.size() == 2);
        REQUIRE(!hash_map.has(1));

        // REQUIRE(hash_map.max_size() == 16);
    }

    SECTION("erase it")
    {
        mock_item_map hash_map;
        hash_map.insert(1, mock_item(1));
        hash_map.insert(2, mock_item(2));
        hash_map.insert(3, mock_item(3));

        REQUIRE(hash_map.has(1));
        REQUIRE(hash_map.find(1)->second.m_value == 1);
        hash_map.erase(hash_map.find(1));
        REQUIRE(hash_map.size() == 2);
        REQUIRE(!hash_map.has(1));

        // REQUIRE(hash_map.max_size() == 16);
    }

    SECTION("erase it_start it_end")
    {
        mock_item_map hash_map;
        hash_map.insert(1, mock_item(1));
        hash_map.insert(2, mock_item(2));
        hash_map.insert(3, mock_item(3));

        int32 value = hash_map.begin()->second.m_value;
        hash_map.erase(hash_map.begin(), ++hash_map.begin());
        REQUIRE(hash_map.size() == 2);
        REQUIRE(hash_map.begin()->second.m_value != value);

        // REQUIRE(hash_map.max_size() == 16);
    }
}

TEST_CASE("hash_map.find", "[gg.hash_map]")
{
    SECTION("find")
    {
        mock_item_map hash_map;
        hash_map.insert(1, mock_item(1));
        hash_map.insert(3, mock_item(2));
        hash_map.insert(5, mock_item(3));

        mock_item_map::const_iterator cit = hash_map.find(5);

        REQUIRE(cit->first == 5);
        REQUIRE(cit->second.m_value == 3);
    }

    SECTION("!(find)")
    {
        mock_item_map hash_map;
        hash_map.insert(1, mock_item(1));
        hash_map.insert(3, mock_item(2));
        hash_map.insert(5, mock_item(3));

        mock_item_map::const_iterator cit = hash_map.find(7);

        REQUIRE(cit == hash_map.end());
    }
}

TEST_CASE("hash_map.find_if", "[gg.hash_map]")
{
    SECTION("find_if")
    {
        mock_item_map hash_map;
        hash_map.insert(1, mock_item(1));
        hash_map.insert(3, mock_item(2));
        hash_map.insert(5, mock_item(3));

        mock_item_map::const_iterator cit =
            hash_map.find_if(
                [value = 3](mock_item_map::value_type const & item)
                {
                    return item.second.m_value == value;
                }
            );

        REQUIRE(cit->first == 5);
        REQUIRE(cit->second.m_value == 3);
    }

    SECTION("!(find_if)")
    {
        mock_item_map hash_map;
        hash_map.insert(1, mock_item(1));
        hash_map.insert(3, mock_item(2));
        hash_map.insert(5, mock_item(3));

        mock_item_map::const_iterator cit =
            hash_map.find_if(
                [value = 5](mock_item_map::value_type const & item)
                {
                    return item.second.m_value == value;
                }
            );

        REQUIRE(cit == hash_map.end());
    }
}

TEST_CASE("hash_map.for_each", "[gg.hash_map]")
{
    SECTION("for_each")
    {
        mock_item_map hash_map;
        hash_map.insert(1, mock_item(1));
        hash_map.insert(2, mock_item(2));
        hash_map.insert(3, mock_item(3));

        int32 i = 0;
        hash_map.for_each(
            [&i](mock_item_map::value_type const &)
            {
                ++i;
            }
        );

        REQUIRE(i == 3);
    }
}

TEST_CASE("hash_map.insert", "[gg.hash_map]")
{
    SECTION("insert key item")
    {
        mock_item_map hash_map;
        hash_map.insert(1, mock_item(1));
        hash_map.insert(2, mock_item(2));
        hash_map.insert(3, mock_item(3));

        REQUIRE(!hash_map.has(4));
        hash_map.insert(4, mock_item(4));
        REQUIRE(hash_map.size() == 4);
        REQUIRE(hash_map.has(4));
        REQUIRE(hash_map.find(4)->second.m_value == 4);

        // REQUIRE(hash_map.max_size() == 16);
    }

    SECTION("insert key rvalue_item")
    {
        mock_item_map hash_map;
        hash_map.insert(1, mock_item(1));
        hash_map.insert(2, mock_item(2));
        hash_map.insert(3, mock_item(3));

        REQUIRE(!hash_map.has(4));
        hash_map.insert(4, type::move(mock_item(4)));
        REQUIRE(hash_map.size() == 4);
        REQUIRE(hash_map.has(4));
        REQUIRE(hash_map.find(4)->second.m_value == 4);

        // REQUIRE(hash_map.max_size() == 16);
    }
}

TEST_CASE("hash_map.size", "[gg.hash_map]")
{
    SECTION("size")
    {
        mock_item_map hash_map;

        hash_map.insert(1, mock_item(1));
        REQUIRE(hash_map.size() == 1);

        hash_map.insert(2, mock_item(1));
        REQUIRE(hash_map.size() == 2);

        hash_map.insert(3, mock_item(1));
        REQUIRE(hash_map.size() == 3);

        hash_map.insert(3, mock_item(4));
        REQUIRE(hash_map.size() == 3);
    }
}

TEST_CASE("hash_map.has", "[gg.hash_map]")
{
    SECTION("has")
    {
        mock_item_map hash_map;
        REQUIRE(!hash_map.has(1));
        hash_map.insert(1, mock_item(1));
        REQUIRE(hash_map.has(1));
    }
}

TEST_CASE("hash_map.is_empty", "[gg.hash_map]")
{
    SECTION("is_empty")
    {
        mock_item_map hash_map;
        REQUIRE(hash_map.is_empty());

        hash_map.insert(1, mock_item(3));
        hash_map.insert(2, mock_item(7));
        hash_map.insert(3, mock_item(4));
        hash_map.insert(4, mock_item(1));
        hash_map.insert(5, mock_item(5));

        size_type max_size = hash_map.max_size();
        REQUIRE(hash_map.size() == 5);
        REQUIRE(!hash_map.is_empty());

        hash_map.clear();

        REQUIRE(hash_map.max_size() == max_size);
        REQUIRE(hash_map.size() == 0);
        REQUIRE(hash_map.is_empty());
    }
}

//==============================================================================
}
//==============================================================================
