#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/container/map/map.h"

//==============================================================================
namespace gg::map_test
{
//==============================================================================

class mock_key
{
public:

    explicit mock_key(int32 value = 0) noexcept : m_value(value)
    {
    }
    ~mock_key(void) noexcept = default;

    bool8 operator==(mock_key const & key) const noexcept
    {
        return m_value == key.m_value;
    }

    bool8 operator<(mock_key const & key) const
    {
        return m_value < key.m_value;
    }

    int32 m_value;
};

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

using mock_item_map = map<mock_key, mock_item>;

//==============================================================================

TEST_CASE("map", "[gg.map]")
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

TEST_CASE("map.constructor", "[gg.map]")
{
    SECTION("map()")
    {
        mock_item_map map;

        // REQUIRE(map.begin() == nullptr);
        REQUIRE(map.begin() == map.end());
        // REQUIRE(map.max_size() == 0);
        REQUIRE(map.size() == 0);
        REQUIRE(map.is_empty());
    }

    SECTION("map(map)")
    {
        mock_item_map copied_map;
        copied_map.insert(mock_key(1), mock_item(1));
        copied_map.insert(mock_key(2), mock_item(2));
        copied_map.insert(mock_key(3), mock_item(3));

        mock_item_map map(copied_map);
        REQUIRE((map == copied_map));
        REQUIRE(map.max_size() == copied_map.max_size());
        REQUIRE(map.size() == 3);
    }

    SECTION("map(rvalue_map)")
    {
        mock_item_map moved_map;
        moved_map.insert(mock_key(1), mock_item(1));
        moved_map.insert(mock_key(2), mock_item(2));
        moved_map.insert(mock_key(3), mock_item(3));

        mock_item_map copied_map(moved_map);
        mock_item_map map(type::move(moved_map));
        REQUIRE((map == copied_map));
        REQUIRE(map.max_size() == copied_map.max_size());
        REQUIRE(map.size() == 3);

        // REQUIRE(moved_map.begin() == nullptr);
        REQUIRE(moved_map.begin() == moved_map.end());
        // REQUIRE(moved_map.max_size() == 0);
        REQUIRE(moved_map.size() == 0);
        REQUIRE(moved_map.is_empty());
    }
}

TEST_CASE("map.operator-access", "[gg.map]")
{
    SECTION("operator[key]")
    {
        mock_item_map map;
        map.insert(mock_key(1), mock_item(3));
        map.insert(mock_key(2), mock_item(2));
        map.insert(mock_key(3), mock_item(1));

        REQUIRE(map[mock_key(1)].m_value == 3);
        REQUIRE(map[mock_key(2)].m_value == 2);
        REQUIRE(map[mock_key(3)].m_value == 1);
    }
}

TEST_CASE("map.operator=", "[gg.map]")
{
    SECTION("map = map")
    {
        mock_item_map copied_map;
        copied_map.insert(mock_key(1), mock_item(1));
        copied_map.insert(mock_key(2), mock_item(2));
        copied_map.insert(mock_key(3), mock_item(3));

        mock_item_map map;
        map = copied_map;
        REQUIRE((map == copied_map));
        REQUIRE(map.max_size() == copied_map.max_size());
        REQUIRE(map.size() == 3);
    }

    SECTION("map = rvalue_map")
    {
        mock_item_map moved_map;
        moved_map.insert(mock_key(1), mock_item(1));
        moved_map.insert(mock_key(2), mock_item(2));
        moved_map.insert(mock_key(3), mock_item(3));

        mock_item_map copied_map(moved_map);
        mock_item_map map;
        map = type::move(moved_map);
        REQUIRE((map == copied_map));
        REQUIRE(map.max_size() == copied_map.max_size());
        REQUIRE(map.size() == 3);

        // REQUIRE(moved_map.begin() == nullptr);
        REQUIRE(moved_map.begin() == moved_map.end());
        // REQUIRE(moved_map.max_size() == 0);
        REQUIRE(moved_map.size() == 0);
        REQUIRE(moved_map.is_empty());
    }
}

TEST_CASE("map.operator==", "[gg.map]")
{
    SECTION("map == map")
    {
        mock_item_map map_1;
        mock_item_map map_2;

        map_1.insert(mock_key(1), mock_item(1));
        map_1.insert(mock_key(2), mock_item(2));
        map_1.insert(mock_key(3), mock_item(3));

        map_2.insert(mock_key(1), mock_item(1));
        map_2.insert(mock_key(2), mock_item(2));
        map_2.insert(mock_key(3), mock_item(3));

        REQUIRE((map_1 == map_2));
    }

    SECTION("map == map(wrong data)")
    {
        mock_item_map map_1;
        mock_item_map map_2;

        map_1.insert(mock_key(1), mock_item(1));
        map_1.insert(mock_key(2), mock_item(2));
        map_1.insert(mock_key(3), mock_item(3));

        map_2.insert(mock_key(1), mock_item(1));
        map_2.insert(mock_key(2), mock_item(2));
        map_2.insert(mock_key(3), mock_item(2));

        REQUIRE(!(map_1 == map_2));
    }

    SECTION("map == map(wrong size)")
    {
        mock_item_map map_1;
        mock_item_map map_2;

        map_1.insert(mock_key(1), mock_item(1));
        map_1.insert(mock_key(2), mock_item(2));
        map_1.insert(mock_key(3), mock_item(3));

        map_2.insert(mock_key(1), mock_item(1));
        map_2.insert(mock_key(2), mock_item(2));
        map_2.insert(mock_key(3), mock_item(3));
        map_2.insert(mock_key(4), mock_item(4));

        REQUIRE(!(map_1 == map_2));
    }
}

TEST_CASE("map.operator!=", "[gg.map]")
{
    SECTION("map != map(wrong data)")
    {
        mock_item_map map_1;
        mock_item_map map_2;

        map_1.insert(mock_key(1), mock_item(1));
        map_1.insert(mock_key(2), mock_item(2));
        map_1.insert(mock_key(3), mock_item(3));

        map_2.insert(mock_key(1), mock_item(3));
        map_2.insert(mock_key(2), mock_item(2));
        map_2.insert(mock_key(3), mock_item(1));

        REQUIRE((map_1 != map_2));
    }

    SECTION("map != map(wrong size)")
    {
        mock_item_map map_1;
        mock_item_map map_2;

        map_1.insert(mock_key(1), mock_item(1));
        map_1.insert(mock_key(2), mock_item(2));
        map_1.insert(mock_key(3), mock_item(3));

        map_2.insert(mock_key(1), mock_item(1));
        map_2.insert(mock_key(2), mock_item(2));

        REQUIRE((map_1 != map_2));
    }
}

TEST_CASE("map.begin", "[gg.map]")
{
    SECTION("begin")
    {
        mock_item_map map;
        map.insert(mock_key(3), mock_item(2));
        map.insert(mock_key(1), mock_item(3));
        map.insert(mock_key(2), mock_item(1));

        REQUIRE(map.begin()->second.m_value == 3);
    }
}

TEST_CASE("map.clear", "[gg.map]")
{
    SECTION("clear")
    {
        mock_item_map map;
        map.insert(mock_key(1), mock_item(1));
        map.insert(mock_key(2), mock_item(2));
        map.insert(mock_key(3), mock_item(3));
        REQUIRE(!map.is_empty());

        map.clear();
        REQUIRE(map.is_empty());
    }
}

TEST_CASE("map.emplace", "[gg.map]")
{
    SECTION("emplace key arguments")
    {
        mock_item_map map;
        map.insert(mock_key(1), mock_item(1));
        map.insert(mock_key(2), mock_item(2));
        map.insert(mock_key(3), mock_item(3));

        map.emplace(mock_key(4), 4);
        REQUIRE(map.size() == 4);
        REQUIRE(map[mock_key(4)].m_value == 4);

        // REQUIRE(map.max_size() == 16);
    }
}

TEST_CASE("map.end", "[gg.map]")
{
    SECTION("end")
    {
        mock_item_map map;
        map.insert(mock_key(3), mock_item(3));
        map.insert(mock_key(2), mock_item(5));
        map.insert(mock_key(1), mock_item(8));

        REQUIRE((--map.end())->second.m_value == 3);
    }
}

TEST_CASE("map.erase", "[gg.map]")
{
    SECTION("erase key")
    {
        mock_item_map map;
        map.insert(mock_key(1), mock_item(1));
        map.insert(mock_key(2), mock_item(2));
        map.insert(mock_key(3), mock_item(3));

        REQUIRE(map.has(mock_key(1)));
        REQUIRE(map.find(mock_key(1))->second.m_value == 1);
        map.erase(mock_key(1));
        REQUIRE(map.size() == 2);
        REQUIRE(!map.has(mock_key(1)));

        // REQUIRE(map.max_size() == 16);
    }

    SECTION("erase it")
    {
        mock_item_map map;
        map.insert(mock_key(1), mock_item(1));
        map.insert(mock_key(2), mock_item(2));
        map.insert(mock_key(3), mock_item(3));

        REQUIRE(map.has(mock_key(1)));
        REQUIRE(map.find(mock_key(1))->second.m_value == 1);
        map.erase(map.find(mock_key(1)));
        REQUIRE(map.size() == 2);
        REQUIRE(!map.has(mock_key(1)));

        // REQUIRE(map.max_size() == 16);
    }

    SECTION("erase it_start it_end")
    {
        mock_item_map map;
        map.insert(mock_key(1), mock_item(1));
        map.insert(mock_key(2), mock_item(2));
        map.insert(mock_key(3), mock_item(3));

        int32 value = map.begin()->second.m_value;
        map.erase(map.begin(), ++map.begin());
        REQUIRE(map.size() == 2);
        REQUIRE(map.begin()->second.m_value != value);

        // REQUIRE(map.max_size() == 16);
    }
}

TEST_CASE("map.find", "[gg.map]")
{
    SECTION("find")
    {
        mock_item_map map;
        map.insert(mock_key(1), mock_item(1));
        map.insert(mock_key(3), mock_item(2));
        map.insert(mock_key(5), mock_item(3));

        mock_item_map::const_iterator cit = map.find(mock_key(5));

        REQUIRE(cit->first.m_value == 5);
        REQUIRE(cit->second.m_value == 3);
    }

    SECTION("!(find)")
    {
        mock_item_map map;
        map.insert(mock_key(1), mock_item(1));
        map.insert(mock_key(3), mock_item(2));
        map.insert(mock_key(5), mock_item(3));

        mock_item_map::const_iterator cit = map.find(mock_key(7));

        REQUIRE(cit == map.end());
    }
}

TEST_CASE("map.find_if", "[gg.map]")
{
    SECTION("find_if")
    {
        mock_item_map map;
        map.insert(mock_key(1), mock_item(1));
        map.insert(mock_key(3), mock_item(2));
        map.insert(mock_key(5), mock_item(3));

        mock_item_map::const_iterator cit =
            map.find_if(
                [value = 3](mock_item_map::value_type const & item)
                {
                    return item.second.m_value == value;
                }
            );

        REQUIRE(cit->first.m_value == 5);
        REQUIRE(cit->second.m_value == 3);
    }

    SECTION("!(find_if)")
    {
        mock_item_map map;
        map.insert(mock_key(1), mock_item(1));
        map.insert(mock_key(3), mock_item(2));
        map.insert(mock_key(5), mock_item(3));

        mock_item_map::const_iterator cit =
            map.find_if(
                [value = 5](mock_item_map::value_type const & item)
                {
                    return item.second.m_value == value;
                }
            );

        REQUIRE(cit == map.end());
    }
}

TEST_CASE("map.for_each", "[gg.map]")
{
    SECTION("for_each")
    {
        mock_item_map map;
        map.insert(mock_key(1), mock_item(1));
        map.insert(mock_key(2), mock_item(2));
        map.insert(mock_key(3), mock_item(3));

        int32 i = 0;
        map.for_each(
            [&i](mock_item_map::value_type const & item)
            {
                REQUIRE(item.second.m_value == ++i);
            }
        );

        REQUIRE(i == 3);
    }
}

TEST_CASE("map.insert", "[gg.map]")
{
    SECTION("insert key item")
    {
        mock_item_map map;
        map.insert(mock_key(1), mock_item(1));
        map.insert(mock_key(2), mock_item(2));
        map.insert(mock_key(3), mock_item(3));

        REQUIRE(!map.has(mock_key(4)));
        map.insert(mock_key(4), mock_item(4));
        REQUIRE(map.size() == 4);
        REQUIRE(map.has(mock_key(4)));
        REQUIRE(map.find(mock_key(4))->second.m_value == 4);

        // REQUIRE(map.max_size() == 16);
    }

    SECTION("insert key rvalue_item")
    {
        mock_item_map map;
        map.insert(mock_key(1), mock_item(1));
        map.insert(mock_key(2), mock_item(2));
        map.insert(mock_key(3), mock_item(3));

        REQUIRE(!map.has(mock_key(4)));
        map.insert(mock_key(4), type::move(mock_item(4)));
        REQUIRE(map.size() == 4);
        REQUIRE(map.has(mock_key(4)));
        REQUIRE(map.find(mock_key(4))->second.m_value == 4);

        // REQUIRE(map.max_size() == 16);
    }
}

TEST_CASE("map.size", "[gg.map]")
{
    SECTION("size")
    {
        mock_item_map map;

        map.insert(mock_key(1), mock_item(1));
        REQUIRE(map.size() == 1);

        map.insert(mock_key(2), mock_item(1));
        REQUIRE(map.size() == 2);

        map.insert(mock_key(3), mock_item(1));
        REQUIRE(map.size() == 3);

        map.insert(mock_key(3), mock_item(4));
        REQUIRE(map.size() == 3);
    }
}

TEST_CASE("map.has", "[gg.map]")
{
    SECTION("has")
    {
        mock_item_map map;
        REQUIRE(!map.has(mock_key(1)));
        map.insert(mock_key(1), mock_item(1));
        REQUIRE(map.has(mock_key(1)));
    }
}

TEST_CASE("map.is_empty", "[gg.map]")
{
    SECTION("is_empty")
    {
        mock_item_map map;
        REQUIRE(map.is_empty());

        map.insert(mock_key(1), mock_item(3));
        map.insert(mock_key(2), mock_item(7));
        map.insert(mock_key(3), mock_item(4));
        map.insert(mock_key(4), mock_item(1));
        map.insert(mock_key(5), mock_item(5));

        size_type max_size = map.max_size();
        REQUIRE(map.size() == 5);
        REQUIRE(!map.is_empty());

        map.clear();

        REQUIRE(map.max_size() == max_size);
        REQUIRE(map.size() == 0);
        REQUIRE(map.is_empty());
    }
}

//==============================================================================
}
//==============================================================================
