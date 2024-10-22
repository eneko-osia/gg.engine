#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/container/array/array_dynamic.h"
#include "gg/core/container/array/mock_item_array_test.h"
#include "gg/core/container/container.h"

//==============================================================================
namespace gg::array_dynamic_test
{
//==============================================================================

using simple_mock_item_array = array_dynamic<simple_mock_item>;
using complex_mock_item_array = array_dynamic<complex_mock_item>;

//==============================================================================

TEST_CASE("array_dynamic", "[gg.array_dynamic]")
{
    SECTION("assign")
    {
        REQUIRE(type::is_copy_assignable<simple_mock_item_array::item_type>::value);
        REQUIRE(type::is_trivially_assignable<simple_mock_item_array::item_type>::value);

        REQUIRE(type::is_copy_assignable<complex_mock_item_array::item_type>::value);
        REQUIRE(!type::is_trivially_assignable<complex_mock_item_array::item_type>::value);

        REQUIRE(type::is_copy_assignable<simple_mock_item_array>::value);
        REQUIRE(!type::is_trivially_assignable<simple_mock_item_array>::value);

        REQUIRE(type::is_copy_assignable<complex_mock_item_array>::value);
        REQUIRE(!type::is_trivially_assignable<complex_mock_item_array>::value);
    }

    SECTION("construct")
    {
        REQUIRE(type::is_constructible<simple_mock_item_array::item_type>::value);
        REQUIRE(type::is_trivially_constructible<simple_mock_item_array::item_type>::value);

        REQUIRE(type::is_constructible<complex_mock_item_array::item_type>::value);
        REQUIRE(!type::is_trivially_constructible<complex_mock_item_array::item_type>::value);

        REQUIRE(type::is_constructible<simple_mock_item_array>::value);
        REQUIRE(!type::is_trivially_constructible<simple_mock_item_array>::value);

        REQUIRE(type::is_constructible<complex_mock_item_array>::value);
        REQUIRE(!type::is_trivially_constructible<complex_mock_item_array>::value);
    }

    SECTION("copy")
    {
        REQUIRE(type::is_copy_constructible<simple_mock_item_array::item_type>::value);
        REQUIRE(type::is_trivially_copy_constructible<simple_mock_item_array::item_type>::value);

        REQUIRE(type::is_copy_constructible<complex_mock_item_array::item_type>::value);
        REQUIRE(!type::is_trivially_copy_constructible<complex_mock_item_array::item_type>::value);

        REQUIRE(type::is_copy_constructible<simple_mock_item_array>::value);
        REQUIRE(!type::is_trivially_copy_constructible<simple_mock_item_array>::value);

        REQUIRE(type::is_copy_constructible<complex_mock_item_array>::value);
        REQUIRE(!type::is_trivially_copy_constructible<complex_mock_item_array>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(type::is_destructible<simple_mock_item_array::item_type>::value);
        REQUIRE(type::is_trivially_destructible<simple_mock_item_array::item_type>::value);

        REQUIRE(type::is_destructible<complex_mock_item_array::item_type>::value);
        REQUIRE(!type::is_trivially_destructible<complex_mock_item_array::item_type>::value);

        REQUIRE(type::is_destructible<simple_mock_item_array>::value);
        REQUIRE(!type::is_trivially_destructible<simple_mock_item_array>::value);

        REQUIRE(type::is_destructible<complex_mock_item_array>::value);
        REQUIRE(!type::is_trivially_destructible<complex_mock_item_array>::value);
    }

    SECTION("compare")
    {
        REQUIRE(!type::is_comparable<simple_mock_item_array::item_type>::value);
        REQUIRE(type::is_comparable<complex_mock_item_array::item_type>::value);

        REQUIRE(type::is_comparable<simple_mock_item_array>::value);
        REQUIRE(type::is_comparable<complex_mock_item_array>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<simple_mock_item_array::item_type>::value);
        REQUIRE(!type::is_polymorphic<complex_mock_item_array::item_type>::value);

        REQUIRE(!type::is_polymorphic<simple_mock_item_array>::value);
        REQUIRE(!type::is_polymorphic<complex_mock_item_array>::value);
    }
}

TEST_CASE("array_dynamic.constructor", "[gg.array_dynamic]")
{
    SECTION("array_dynamic - simple")
    {
        simple_mock_item_array array;
        REQUIRE(array.begin() == array.end());
        REQUIRE(array.data() == nullptr);
        REQUIRE(array.max_size() == 0);
        REQUIRE(array.size() == 0);
        REQUIRE(array.is_empty());
    }

    SECTION("array_dynamic - complex")
    {
        complex_mock_item_array array;
        REQUIRE(array.begin() == array.end());
        REQUIRE(array.data() == nullptr);
        REQUIRE(array.max_size() == 0);
        REQUIRE(array.size() == 0);
        REQUIRE(array.is_empty());
    }

    SECTION("array_dynamic(array_dynamic) - simple")
    {
        simple_mock_item_array copied_array;
        copied_array.emplace_back(1);
        copied_array.emplace_back(2);
        copied_array.emplace_back(3);

        simple_mock_item_array array(copied_array);
        REQUIRE((array == copied_array));
        REQUIRE(array.max_size() == copied_array.size());
        REQUIRE(array.size() == 3);
    }

    SECTION("array_dynamic(array_dynamic) - complex")
    {
        complex_mock_item_array copied_array;
        copied_array.emplace_back(1);
        copied_array.emplace_back(2);
        copied_array.emplace_back(3);

        complex_mock_item_array array(copied_array);
        REQUIRE(array.max_size() == copied_array.size());
        REQUIRE(array.size() == 3);

        container::for_each(
            array.begin(),
            array.end(),
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(!item.constructor_called);
                REQUIRE(item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });
        REQUIRE((array == copied_array));
    }

    SECTION("array_dynamic(rvalue_array_dynamic) - simple")
    {
        simple_mock_item_array moved_array;
        moved_array.emplace_back(1);
        moved_array.emplace_back(2);
        moved_array.emplace_back(3);

        simple_mock_item_array copied_array(moved_array);
        simple_mock_item_array array(type::move(moved_array));
        REQUIRE((array == copied_array));
        REQUIRE(array.max_size() == 8);
        REQUIRE(array.size() == 3);

        REQUIRE(moved_array.begin() == moved_array.end());
        REQUIRE(moved_array.max_size() == 0);
        REQUIRE(moved_array.size() == 0);
        REQUIRE(moved_array.is_empty());
    }

    SECTION("array_dynamic(rvalue_array_dynamic) - complex")
    {
        complex_mock_item_array moved_array;
        moved_array.emplace_back(1);
        moved_array.emplace_back(2);
        moved_array.emplace_back(3);

        complex_mock_item_array copied_array(moved_array);
        complex_mock_item_array array(type::move(moved_array));
        REQUIRE(array.max_size() == 8);
        REQUIRE(array.size() == 3);

        container::for_each(
            array.begin(),
            array.end(),
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(item.constructor_called);
                REQUIRE(!item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });
        REQUIRE((array == copied_array));

        REQUIRE(moved_array.begin() == moved_array.end());
        REQUIRE(moved_array.max_size() == 0);
        REQUIRE(moved_array.size() == 0);
        REQUIRE(moved_array.is_empty());
    }

    SECTION("array_dynamic(item, size) - simple")
    {
        simple_mock_item_array array(1, 10);
        REQUIRE(array.max_size() == 10);
        REQUIRE(array.size() == 10);

        container::for_each(
            array.begin(),
            array.end(),
            [] (simple_mock_item_array::const_reference item)
            {
                REQUIRE(item.value == 1);
            });
    }

    SECTION("array_dynamic(item, size) - complex")
    {
        complex_mock_item_array array(1, 10);
        REQUIRE(array.max_size() == 10);
        REQUIRE(array.size() == 10);

        container::for_each(
            array.begin(),
            array.end(),
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(!item.constructor_called);
                REQUIRE(item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
                REQUIRE(item.value == 1);
            });
    }
}

TEST_CASE("array_dynamic.operator-access", "[gg.array_dynamic]")
{
    SECTION("operator[idx]")
    {
        simple_mock_item_array array;
        array.emplace_back(3);
        array.emplace_back(2);
        array.emplace_back(1);

        REQUIRE(array[0].value == 3);
        REQUIRE(array[1].value == 2);
        REQUIRE(array[2].value == 1);

        REQUIRE(array[0].value == array.data()[0].value);
        REQUIRE(array[1].value == array.data()[1].value);
        REQUIRE(array[2].value == array.data()[2].value);
    }
}

TEST_CASE("array_dynamic.operator=", "[gg.array_dynamic]")
{
    SECTION("array_dynamic = array_dynamic - simple")
    {
        simple_mock_item_array copied_array;
        copied_array.emplace_back(3);
        copied_array.emplace_back(2);
        copied_array.emplace_back(1);

        simple_mock_item_array array;
        array = copied_array;
        REQUIRE((array == copied_array));
        REQUIRE(array.max_size() == copied_array.size());
        REQUIRE(array.size() == 3);
    }

    SECTION("array_dynamic = array_dynamic - complex")
    {
        complex_mock_item_array copied_array;
        copied_array.emplace_back(3);
        copied_array.emplace_back(2);
        copied_array.emplace_back(1);

        complex_mock_item_array array;
        array = copied_array;
        REQUIRE((array == copied_array));
        REQUIRE(array.max_size() == copied_array.size());
        REQUIRE(array.size() == 3);

        container::for_each(
            array.begin(),
            array.end(),
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(!item.constructor_called);
                REQUIRE(item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(item.equality_called);
            });

    }

    SECTION("array_dynamic = rvalue_array_dynamic - simple")
    {
        simple_mock_item_array moved_array;
        moved_array.emplace_back(1);
        moved_array.emplace_back(2);
        moved_array.emplace_back(3);

        simple_mock_item_array copied_array(moved_array);
        simple_mock_item_array array;
        array = type::move(moved_array);
        REQUIRE((array == copied_array));
        REQUIRE(array.max_size() == 8);
        REQUIRE(array.size() == 3);

        REQUIRE(moved_array.begin() == moved_array.end());
        REQUIRE(moved_array.max_size() == 0);
        REQUIRE(moved_array.size() == 0);
        REQUIRE(moved_array.is_empty());
    }

    SECTION("array_dynamic = rvalue_array_dynamic - complex")
    {
        complex_mock_item_array moved_array;
        moved_array.emplace_back(1);
        moved_array.emplace_back(2);
        moved_array.emplace_back(3);

        complex_mock_item_array copied_array(moved_array);
        complex_mock_item_array array;
        array = type::move(moved_array);
        REQUIRE((array == copied_array));
        REQUIRE(array.max_size() == 8);
        REQUIRE(array.size() == 3);

        container::for_each(
            array.begin(),
            array.end(),
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(item.constructor_called);
                REQUIRE(!item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(item.equality_called);
            });

        REQUIRE(moved_array.begin() == moved_array.end());
        REQUIRE(moved_array.max_size() == 0);
        REQUIRE(moved_array.size() == 0);
        REQUIRE(moved_array.is_empty());
    }
}

TEST_CASE("array_dynamic.operator==", "[gg.array_dynamic]")
{
    SECTION("array_dynamic == array_dynamic - simple")
    {
        simple_mock_item_array array_1;
        simple_mock_item_array array_2;

        array_1.emplace_back(1);
        array_1.emplace_back(2);
        array_1.emplace_back(3);

        array_2.emplace_back(1);
        array_2.emplace_back(2);
        array_2.emplace_back(3);

        REQUIRE((array_1 == array_2));
    }

    SECTION("array_dynamic == array_dynamic - complex")
    {
        complex_mock_item_array array_1;
        complex_mock_item_array array_2;

        array_1.emplace_back(1);
        array_1.emplace_back(2);
        array_1.emplace_back(3);

        array_2.emplace_back(1);
        array_2.emplace_back(2);
        array_2.emplace_back(3);

        REQUIRE((array_1 == array_2));

        container::for_each(
            array_1.begin(),
            array_1.end(),
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(item.constructor_called);
                REQUIRE(!item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(item.equality_called);
            });
    }

    SECTION("array_dynamic == array_dynamic(wrong data) - simple")
    {
        simple_mock_item_array array_1;
        simple_mock_item_array array_2;

        array_1.emplace_back(1);
        array_1.emplace_back(2);
        array_1.emplace_back(3);

        array_2.emplace_back(1);
        array_2.emplace_back(2);
        array_2.emplace_back(2);

        REQUIRE(!(array_1 == array_2));
    }

    SECTION("array_dynamic == array_dynamic(wrong data) - complex")
    {
        complex_mock_item_array array_1;
        complex_mock_item_array array_2;

        array_1.emplace_back(1);
        array_1.emplace_back(2);
        array_1.emplace_back(3);

        array_2.emplace_back(1);
        array_2.emplace_back(1);
        array_2.emplace_back(3);

        REQUIRE(!(array_1 == array_2));

        container::for_each(
            array_1.begin(),
            array_1.begin() + 2,
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(item.constructor_called);
                REQUIRE(!item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(item.equality_called);
            });

        container::for_each(
            array_1.begin() + 2,
            array_1.end(),
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(item.constructor_called);
                REQUIRE(!item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });
    }

    SECTION("array_dynamic == array_dynamic(wrong size) - simple")
    {
        simple_mock_item_array array_1;
        simple_mock_item_array array_2;

        array_1.emplace_back(1);
        array_1.emplace_back(2);
        array_1.emplace_back(3);

        array_2.emplace_back(1);
        array_2.emplace_back(2);
        array_2.emplace_back(3);
        array_2.emplace_back(4);

        REQUIRE(!(array_1 == array_2));
    }

    SECTION("array_dynamic == array_dynamic(wrong size) - complex")
    {
        complex_mock_item_array array_1;
        complex_mock_item_array array_2;

        array_1.emplace_back(1);
        array_1.emplace_back(2);
        array_1.emplace_back(3);

        array_2.emplace_back(1);
        array_2.emplace_back(2);
        array_2.emplace_back(3);
        array_2.emplace_back(4);

        REQUIRE(!(array_1 == array_2));

        container::for_each(
            array_1.begin(),
            array_1.end(),
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(item.constructor_called);
                REQUIRE(!item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });
    }
}

TEST_CASE("array_dynamic.operator!=", "[gg.array_dynamic]")
{
    SECTION("array_dynamic != array_dynamic(data) - simple")
    {
        simple_mock_item_array array_1;
        simple_mock_item_array array_2;

        array_1.emplace_back(1);
        array_1.emplace_back(2);
        array_1.emplace_back(3);

        array_2.emplace_back(1);
        array_2.emplace_back(1);
        array_2.emplace_back(3);

        REQUIRE((array_1 != array_2));
    }

    SECTION("array_dynamic != array_dynamic(data) - complex")
    {
        complex_mock_item_array array_1;
        complex_mock_item_array array_2;

        array_1.emplace_back(1);
        array_1.emplace_back(2);
        array_1.emplace_back(3);

        array_2.emplace_back(1);
        array_2.emplace_back(1);
        array_2.emplace_back(3);

        REQUIRE((array_1 != array_2));

        container::for_each(
            array_1.begin(),
            array_1.begin() + 2,
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(item.constructor_called);
                REQUIRE(!item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(item.equality_called);
            });

        container::for_each(
            array_1.begin() + 2,
            array_1.end(),
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(item.constructor_called);
                REQUIRE(!item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });
    }

    SECTION("array_dynamic != array_dynamic(size) - simple")
    {
        simple_mock_item_array array_1;
        simple_mock_item_array array_2;

        array_1.emplace_back(1);
        array_1.emplace_back(2);
        array_1.emplace_back(3);

        array_2.emplace_back(1);
        array_2.emplace_back(2);
        array_2.emplace_back(3);
        array_2.emplace_back(4);

        REQUIRE((array_1 != array_2));
    }

    SECTION("array_dynamic != array_dynamic(size) - complex")
    {
        complex_mock_item_array array_1;
        complex_mock_item_array array_2;

        array_1.emplace_back(1);
        array_1.emplace_back(2);
        array_1.emplace_back(3);

        array_2.emplace_back(1);
        array_2.emplace_back(2);
        array_2.emplace_back(3);
        array_2.emplace_back(4);

        REQUIRE((array_1 != array_2));

        container::for_each(
            array_1.begin(),
            array_1.end(),
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(item.constructor_called);
                REQUIRE(!item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });
    }

    SECTION("array_dynamic != array_dynamic(wrong data) - simple")
    {
        simple_mock_item_array array_1;
        simple_mock_item_array array_2;

        array_1.emplace_back(1);
        array_1.emplace_back(2);
        array_1.emplace_back(3);

        array_2.emplace_back(1);
        array_2.emplace_back(2);
        array_2.emplace_back(3);

        REQUIRE(!(array_1 != array_2));
    }

    SECTION("array_dynamic != array_dynamic(wrong data) - complex")
    {
        complex_mock_item_array array_1;
        complex_mock_item_array array_2;

        array_1.emplace_back(1);
        array_1.emplace_back(2);
        array_1.emplace_back(3);

        array_2.emplace_back(1);
        array_2.emplace_back(2);
        array_2.emplace_back(3);

        REQUIRE(!(array_1 != array_2));

        container::for_each(
            array_1.begin(),
            array_1.end(),
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(item.constructor_called);
                REQUIRE(!item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(item.equality_called);
            });
    }
}

TEST_CASE("array_dynamic.back", "[gg.array_dynamic]")
{
    SECTION("back")
    {
        simple_mock_item_array array;
        array.emplace_back(1);
        array.emplace_back(3);
        array.emplace_back(2);
        REQUIRE(array.back().value == 2);
    }
}

TEST_CASE("array_dynamic.begin", "[gg.array_dynamic]")
{
    SECTION("begin")
    {
        simple_mock_item_array array;
        array.emplace_back(2);
        array.emplace_back(3);
        array.emplace_back(1);
        REQUIRE((*array.begin()).value == 2);
    }
}

TEST_CASE("array_dynamic.clear", "[gg.array_dynamic]")
{
    SECTION("clear - simple")
    {
        simple_mock_item_array array;
        array.emplace_back(2);
        array.emplace_back(2);
        array.emplace_back(2);
        REQUIRE(!array.is_empty());

        container::for_each(
            array.begin(),
            array.end(),
            [] (simple_mock_item_array::const_reference item)
            {
                REQUIRE(item.value == 2);
            });

        array.clear();
        REQUIRE(array.is_empty());
    }

    SECTION("clear - complex")
    {
        complex_mock_item_array array;
        array.emplace_back(2);
        array.emplace_back(2);
        array.emplace_back(2);
        REQUIRE(!array.is_empty());

        container::for_each(
            array.begin(),
            array.end(),
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(item.value == 2);
                REQUIRE(item.constructor_called);
                REQUIRE(!item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });

        array.clear();
        REQUIRE(array.is_empty());
    }
}

TEST_CASE("array_dynamic.emplace", "[gg.array_dynamic]")
{
    SECTION("emplace idx arguments - simple")
    {
        simple_mock_item_array array;
        array.emplace_back(1);
        array.emplace_back(2);
        array.emplace_back(3);

        REQUIRE(array.front().value == 1);
        array.emplace(0, 0);
        REQUIRE(array.size() == 4);
        REQUIRE(array.front().value == 0);

        REQUIRE(array.back().value == 3);
        array.emplace(array.size(), 4);
        REQUIRE(array.size() == 5);
        REQUIRE(array.back().value == 4);

        REQUIRE(array[3].value == 3);
        array.emplace(3, 123);
        REQUIRE(array.size() == 6);
        REQUIRE(array[3].value == 123);

        REQUIRE(array.max_size() == 8);
    }

    SECTION("emplace idx arguments - complex")
    {
        complex_mock_item_array array;
        array.emplace_back(1);
        array.emplace_back(2);
        array.emplace_back(3);

        REQUIRE(array.front().value == 1);
        array.emplace(0, 0);
        REQUIRE(array.size() == 4);
        REQUIRE(array.front().value == 0);

        REQUIRE(array.back().value == 3);
        array.emplace(array.size(), 4);
        REQUIRE(array.size() == 5);
        REQUIRE(array.back().value == 4);

        REQUIRE(array[3].value == 3);
        array.emplace(3, 123);
        REQUIRE(array.size() == 6);
        REQUIRE(array[3].value == 123);

        container::for_each(
            array.begin(),
            array.end(),
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(item.constructor_called);
                REQUIRE(!item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });

        REQUIRE(array.max_size() == 8);
    }

    SECTION("emplace it arguments - simple")
    {
        simple_mock_item_array array;
        array.emplace_back(1);
        array.emplace_back(2);
        array.emplace_back(3);

        REQUIRE(array.front().value == 1);
        array.emplace(array.begin(), 0);
        REQUIRE(array.size() == 4);
        REQUIRE(array.front().value == 0);

        REQUIRE(array.back().value == 3);
        array.emplace(array.end(), 4);
        REQUIRE(array.size() == 5);
        REQUIRE(array.back().value == 4);

        REQUIRE(array[3].value == 3);
        array.emplace(array.begin() + 3, 123);
        REQUIRE(array.size() == 6);
        REQUIRE(array[3].value == 123);

        REQUIRE(array.max_size() == 8);
    }

    SECTION("emplace it arguments - complex")
    {
        complex_mock_item_array array;
        array.emplace_back(1);
        array.emplace_back(2);
        array.emplace_back(3);

        REQUIRE(array.front().value == 1);
        array.emplace(array.begin(), 0);
        REQUIRE(array.size() == 4);
        REQUIRE(array.front().value == 0);

        REQUIRE(array.back().value == 3);
        array.emplace(array.end(), 4);
        REQUIRE(array.size() == 5);
        REQUIRE(array.back().value == 4);

        REQUIRE(array[3].value == 3);
        array.emplace(array.begin() + 3, 123);
        REQUIRE(array.size() == 6);
        REQUIRE(array[3].value == 123);

        container::for_each(
            array.begin(),
            array.end(),
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(item.constructor_called);
                REQUIRE(!item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });

        REQUIRE(array.max_size() == 8);
    }
}

TEST_CASE("array_dynamic.emplace_back", "[gg.array_dynamic]")
{
    SECTION("emplace_back arguments - simple")
    {
        simple_mock_item_array array;
        array.emplace_back(1);
        array.emplace_back(2);
        array.emplace_back(3);

        REQUIRE(array.back().value == 3);
        array.emplace_back(4);
        REQUIRE(array.size() == 4);
        REQUIRE(array.back().value == 4);

        REQUIRE(array.max_size() == 8);
    }

    SECTION("emplace_back arguments - complex")
    {
        complex_mock_item_array array;
        array.emplace_back(1);
        array.emplace_back(2);
        array.emplace_back(3);

        REQUIRE(array.back().value == 3);
        array.emplace_back(4);
        REQUIRE(array.size() == 4);
        REQUIRE(array.back().value == 4);

        container::for_each(
            array.begin(),
            array.end(),
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(item.constructor_called);
                REQUIRE(!item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });

        REQUIRE(array.max_size() == 8);
    }
}

TEST_CASE("array_dynamic.end", "[gg.array_dynamic]")
{
    SECTION("end")
    {
        simple_mock_item_array array;
        array.emplace_back(2);
        array.emplace_back(3);
        array.emplace_back(1);
        REQUIRE((*(array.end() - 1)).value == 1);
    }
}

TEST_CASE("array_dynamic.erase", "[gg.array_dynamic]")
{
    SECTION("erase idx - simple")
    {
        simple_mock_item_array array;
        array.emplace_back(5);
        array.emplace_back(2);
        array.emplace_back(7);
        array.emplace_back(4);
        array.emplace_back(3);

        REQUIRE(array.front().value == 5);
        array.erase(0);
        REQUIRE(array.size() == 4);
        REQUIRE(array.front().value == 2);

        REQUIRE(array.back().value == 3);
        array.erase(array.size() - 1);
        REQUIRE(array.size() == 3);
        REQUIRE(array.back().value == 4);

        REQUIRE(array[1].value == 7);
        array.erase(1);
        REQUIRE(array.size() == 2);
        REQUIRE(array[1].value == 4);

        REQUIRE(array.max_size() == 8);
    }

    SECTION("erase idx - complex")
    {
        complex_mock_item_array array;
        array.emplace_back(5);
        array.emplace_back(2);
        array.emplace_back(7);
        array.emplace_back(4);
        array.emplace_back(3);

        REQUIRE(array.front().value == 5);
        array.erase(0);
        REQUIRE(array.size() == 4);
        REQUIRE(array.front().value == 2);

        REQUIRE(array.back().value == 3);
        array.erase(array.size() - 1);
        REQUIRE(array.size() == 3);
        REQUIRE(array.back().value == 4);

        REQUIRE(array[1].value == 7);
        array.erase(1);
        REQUIRE(array.size() == 2);
        REQUIRE(array[1].value == 4);

        container::for_each(
            array.begin(),
            array.end(),
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(item.constructor_called);
                REQUIRE(!item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });

        REQUIRE(array.max_size() == 8);
    }

    SECTION("erase idx_start idx_end - simple")
    {
        simple_mock_item_array array;
        array.emplace_back(5);
        array.emplace_back(2);
        array.emplace_back(7);
        array.emplace_back(4);
        array.emplace_back(1);
        array.emplace_back(3);
        array.emplace_back(6);
        array.emplace_back(9);
        array.emplace_back(8);

        REQUIRE(array.front().value == 5);
        array.erase(0, 1);
        REQUIRE(array.size() == 8);
        REQUIRE(array.front().value == 2);

        REQUIRE(array.back().value == 8);
        array.erase(array.size() - 1, array.size());
        REQUIRE(array.size() == 7);
        REQUIRE(array.back().value == 9);

        REQUIRE(array[3].value == 1);
        array.erase(3, 6);
        REQUIRE(array.size() == 4);
        REQUIRE(array[3].value == 9);

        REQUIRE(array.max_size() == 16);
    }

    SECTION("erase idx_start idx_end - complex")
    {
        complex_mock_item_array array;
        array.emplace_back(5);
        array.emplace_back(2);
        array.emplace_back(7);
        array.emplace_back(4);
        array.emplace_back(1);
        array.emplace_back(3);
        array.emplace_back(6);
        array.emplace_back(9);
        array.emplace_back(8);

        REQUIRE(array.front().value == 5);
        array.erase(0, 1);
        REQUIRE(array.size() == 8);
        REQUIRE(array.front().value == 2);

        REQUIRE(array.back().value == 8);
        array.erase(array.size() - 1, array.size());
        REQUIRE(array.size() == 7);
        REQUIRE(array.back().value == 9);

        REQUIRE(array[3].value == 1);
        array.erase(3, 6);
        REQUIRE(array.size() == 4);
        REQUIRE(array[3].value == 9);

        container::for_each(
            array.begin(),
            array.end(),
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(item.constructor_called);
                REQUIRE(!item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });

        REQUIRE(array.max_size() == 16);
    }

    SECTION("erase it - simple")
    {
        simple_mock_item_array array;
        array.emplace_back(5);
        array.emplace_back(2);
        array.emplace_back(7);
        array.emplace_back(4);
        array.emplace_back(3);

        REQUIRE(array.front().value == 5);
        array.erase(array.begin());
        REQUIRE(array.size() == 4);
        REQUIRE(array.front().value == 2);

        REQUIRE(array.back().value == 3);
        array.erase(array.end() - 1);
        REQUIRE(array.size() == 3);
        REQUIRE(array.back().value == 4);

        REQUIRE(array[1].value == 7);
        array.erase(array.begin() + 1);
        REQUIRE(array.size() == 2);
        REQUIRE(array[1].value == 4);

        REQUIRE(array.max_size() == 8);
    }

    SECTION("erase it - complex")
    {
        complex_mock_item_array array;
        array.emplace_back(5);
        array.emplace_back(2);
        array.emplace_back(7);
        array.emplace_back(4);
        array.emplace_back(3);

        REQUIRE(array.front().value == 5);
        array.erase(array.begin());
        REQUIRE(array.size() == 4);
        REQUIRE(array.front().value == 2);

        REQUIRE(array.back().value == 3);
        array.erase(array.end() - 1);
        REQUIRE(array.size() == 3);
        REQUIRE(array.back().value == 4);

        REQUIRE(array[1].value == 7);
        array.erase(array.begin() + 1);
        REQUIRE(array.size() == 2);
        REQUIRE(array[1].value == 4);

        container::for_each(
            array.begin(),
            array.end(),
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(item.constructor_called);
                REQUIRE(!item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });

        REQUIRE(array.max_size() == 8);
    }

    SECTION("erase it_start it_end - simple")
    {
        simple_mock_item_array array;
        array.emplace_back(5);
        array.emplace_back(2);
        array.emplace_back(7);
        array.emplace_back(4);
        array.emplace_back(1);
        array.emplace_back(3);
        array.emplace_back(6);
        array.emplace_back(9);
        array.emplace_back(8);

        REQUIRE(array.front().value == 5);
        array.erase(array.begin(), array.begin() + 1);
        REQUIRE(array.size() == 8);
        REQUIRE(array.front().value == 2);

        REQUIRE(array.back().value == 8);
        array.erase(array.end() - 1, array.end());
        REQUIRE(array.size() == 7);
        REQUIRE(array.back().value == 9);

        REQUIRE(array[3].value == 1);
        array.erase(array.begin() + 3, array.begin() + 6);
        REQUIRE(array.size() == 4);
        REQUIRE(array[3].value == 9);

        REQUIRE(array.max_size() == 16);
    }

    SECTION("erase it_start it_end - complex")
    {
        complex_mock_item_array array;
        array.emplace_back(5);
        array.emplace_back(2);
        array.emplace_back(7);
        array.emplace_back(4);
        array.emplace_back(1);
        array.emplace_back(3);
        array.emplace_back(6);
        array.emplace_back(9);
        array.emplace_back(8);

        REQUIRE(array.front().value == 5);
        array.erase(array.begin(), array.begin() + 1);
        REQUIRE(array.size() == 8);
        REQUIRE(array.front().value == 2);

        REQUIRE(array.back().value == 8);
        array.erase(array.end() - 1, array.end());
        REQUIRE(array.size() == 7);
        REQUIRE(array.back().value == 9);

        REQUIRE(array[3].value == 1);
        array.erase(array.begin() + 3, array.begin() + 6);
        REQUIRE(array.size() == 4);
        REQUIRE(array[3].value == 9);

        container::for_each(
            array.begin(),
            array.end(),
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(item.constructor_called);
                REQUIRE(!item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });

        REQUIRE(array.max_size() == 16);
    }
}

TEST_CASE("array_dynamic.front", "[gg.array_dynamic]")
{
    SECTION("front")
    {
        simple_mock_item_array array;
        array.emplace_back(1);
        array.emplace_back(3);
        array.emplace_back(2);
        REQUIRE(array.front().value == 1);
    }
}

TEST_CASE("array_dynamic.insert", "[gg.array_dynamic]")
{
    SECTION("insert idx item - simple")
    {
        simple_mock_item_array array;
        array.emplace_back(1);
        array.emplace_back(2);
        array.emplace_back(3);

        {
            REQUIRE(array.front().value == 1);
            simple_mock_item mock_item(0);
            array.insert(0, mock_item);
            REQUIRE(array.size() == 4);
            REQUIRE(array.front().value == 0);
        }

        {
            REQUIRE(array.back().value == 3);
            simple_mock_item mock_item(4);
            array.insert(array.size(), mock_item);
            REQUIRE(array.size() == 5);
            REQUIRE(array.back().value == 4);
        }

        {
            REQUIRE(array[3].value == 3);
            simple_mock_item mock_item(123);
            array.insert(3, mock_item);
            REQUIRE(array.size() == 6);
            REQUIRE(array[3].value == 123);
        }

        REQUIRE(array.max_size() == 8);
    }

    SECTION("insert idx item - complex")
    {
        complex_mock_item_array array;
        array.emplace_back(1);
        array.emplace_back(2);
        array.emplace_back(3);

        {
            REQUIRE(array.front().value == 1);
            complex_mock_item mock_item(0);
            array.insert(0, mock_item);
            REQUIRE(array.size() == 4);

            complex_mock_item const & item = array.front();
            REQUIRE(item.value == 0);
            REQUIRE(!item.constructor_called);
            REQUIRE(item.copy_constructor_called);
            REQUIRE(!item.destructor_called);
            REQUIRE(!item.assign_called);
            REQUIRE(!item.equality_called);
        }

        {
            REQUIRE(array.back().value == 3);
            complex_mock_item mock_item(4);
            array.insert(array.size(), mock_item);
            REQUIRE(array.size() == 5);

            complex_mock_item const & item = array.back();
            REQUIRE(item.value == 4);
            REQUIRE(!item.constructor_called);
            REQUIRE(item.copy_constructor_called);
            REQUIRE(!item.destructor_called);
            REQUIRE(!item.assign_called);
            REQUIRE(!item.equality_called);
        }

        {
            REQUIRE(array[3].value == 3);
            complex_mock_item mock_item(123);
            array.insert(3, mock_item);
            REQUIRE(array.size() == 6);

            complex_mock_item const & item = array[3];
            REQUIRE(item.value == 123);
            REQUIRE(!item.constructor_called);
            REQUIRE(item.copy_constructor_called);
            REQUIRE(!item.destructor_called);
            REQUIRE(!item.assign_called);
            REQUIRE(!item.equality_called);
        }

        REQUIRE(array.max_size() == 8);
    }

    SECTION("insert idx rvalue_item - simple")
    {
        simple_mock_item_array array;
        array.emplace_back(1);
        array.emplace_back(2);
        array.emplace_back(3);

        REQUIRE(array.front().value == 1);
        array.insert(0, type::move(simple_mock_item(0)));
        REQUIRE(array.size() == 4);
        REQUIRE(array.front().value == 0);

        REQUIRE(array.back().value == 3);
        array.insert(array.size(), type::move(simple_mock_item(4)));
        REQUIRE(array.size() == 5);
        REQUIRE(array.back().value == 4);

        REQUIRE(array[3].value == 3);
        array.insert(3, type::move(simple_mock_item(123)));
        REQUIRE(array.size() == 6);
        REQUIRE(array[3].value == 123);

        REQUIRE(array.max_size() == 8);
    }

    SECTION("insert idx rvalue_item - complex")
    {
        complex_mock_item_array array;
        array.emplace_back(1);
        array.emplace_back(2);
        array.emplace_back(3);

        REQUIRE(array.front().value == 1);
        array.insert(0, type::move(complex_mock_item(0)));
        REQUIRE(array.size() == 4);

        {
            complex_mock_item const & item = array.front();
            REQUIRE(item.value == 0);
            REQUIRE(!item.constructor_called);
            REQUIRE(item.copy_constructor_called);
            REQUIRE(!item.destructor_called);
            REQUIRE(!item.assign_called);
            REQUIRE(!item.equality_called);
        }

        REQUIRE(array.back().value == 3);
        array.insert(array.size(), type::move(complex_mock_item(4)));
        REQUIRE(array.size() == 5);

        {
            complex_mock_item const & item = array.back();
            REQUIRE(item.value == 4);
            REQUIRE(!item.constructor_called);
            REQUIRE(item.copy_constructor_called);
            REQUIRE(!item.destructor_called);
            REQUIRE(!item.assign_called);
            REQUIRE(!item.equality_called);
        }

        REQUIRE(array[3].value == 3);
        array.insert(3, type::move(complex_mock_item(123)));
        REQUIRE(array.size() == 6);

        {
            complex_mock_item const & item = array[3];
            REQUIRE(item.value == 123);
            REQUIRE(!item.constructor_called);
            REQUIRE(item.copy_constructor_called);
            REQUIRE(!item.destructor_called);
            REQUIRE(!item.assign_called);
            REQUIRE(!item.equality_called);
        }

        REQUIRE(array.max_size() == 8);
    }

    SECTION("insert it item - simple")
    {
        simple_mock_item_array array;
        array.emplace_back(1);
        array.emplace_back(2);
        array.emplace_back(3);

        {
            REQUIRE(array.front().value == 1);
            simple_mock_item mock_item(0);
            array.insert(array.begin(), mock_item);
            REQUIRE(array.size() == 4);
            REQUIRE(array.front().value == 0);
        }

        {
            REQUIRE(array.back().value == 3);
            simple_mock_item mock_item(4);
            array.insert(array.end(), mock_item);
            REQUIRE(array.size() == 5);
            REQUIRE(array.back().value == 4);
        }

        {
            REQUIRE(array[3].value == 3);
            simple_mock_item mock_item(123);
            array.insert(array.begin() + 3, mock_item);
            REQUIRE(array.size() == 6);
            REQUIRE(array[3].value == 123);
        }

        REQUIRE(array.max_size() == 8);
    }

    SECTION("insert it item - complex")
    {
        complex_mock_item_array array;
        array.emplace_back(1);
        array.emplace_back(2);
        array.emplace_back(3);

        {
            REQUIRE(array.front().value == 1);
            complex_mock_item mock_item(0);
            array.insert(array.begin(), mock_item);
            REQUIRE(array.size() == 4);

            complex_mock_item const & item = array.front();
            REQUIRE(item.value == 0);
            REQUIRE(!item.constructor_called);
            REQUIRE(item.copy_constructor_called);
            REQUIRE(!item.destructor_called);
            REQUIRE(!item.assign_called);
            REQUIRE(!item.equality_called);
        }

        {
            REQUIRE(array.back().value == 3);
            complex_mock_item mock_item(4);
            array.insert(array.end(), mock_item);
            REQUIRE(array.size() == 5);

            complex_mock_item const & item = array.back();
            REQUIRE(item.value == 4);
            REQUIRE(!item.constructor_called);
            REQUIRE(item.copy_constructor_called);
            REQUIRE(!item.destructor_called);
            REQUIRE(!item.assign_called);
            REQUIRE(!item.equality_called);
        }

        {
            REQUIRE(array[3].value == 3);
            complex_mock_item mock_item(123);
            array.insert(array.begin() + 3, mock_item);
            REQUIRE(array.size() == 6);

            complex_mock_item const & item = array[3];
            REQUIRE(item.value == 123);
            REQUIRE(!item.constructor_called);
            REQUIRE(item.copy_constructor_called);
            REQUIRE(!item.destructor_called);
            REQUIRE(!item.assign_called);
            REQUIRE(!item.equality_called);
        }

        REQUIRE(array.max_size() == 8);
    }

    SECTION("insert it rvalue_item - simple")
    {
        simple_mock_item_array array;
        array.emplace_back(1);
        array.emplace_back(2);
        array.emplace_back(3);

        REQUIRE(array.front().value == 1);
        array.insert(array.begin(), type::move(simple_mock_item(0)));
        REQUIRE(array.size() == 4);
        REQUIRE(array.front().value == 0);

        REQUIRE(array.back().value == 3);
        array.insert(array.end(), type::move(simple_mock_item(4)));
        REQUIRE(array.size() == 5);
        REQUIRE(array.back().value == 4);

        REQUIRE(array[3].value == 3);
        array.insert(array.begin() + 3, type::move(simple_mock_item(123)));
        REQUIRE(array.size() == 6);
        REQUIRE(array[3].value == 123);

        REQUIRE(array.max_size() == 8);
    }

    SECTION("insert it rvalue_item - complex")
    {
        complex_mock_item_array array;
        array.emplace_back(1);
        array.emplace_back(2);
        array.emplace_back(3);

        REQUIRE(array.front().value == 1);
        array.insert(array.begin(), type::move(complex_mock_item(0)));
        REQUIRE(array.size() == 4);

        {
            complex_mock_item const & item = array.front();
            REQUIRE(item.value == 0);
            REQUIRE(!item.constructor_called);
            REQUIRE(item.copy_constructor_called);
            REQUIRE(!item.destructor_called);
            REQUIRE(!item.assign_called);
            REQUIRE(!item.equality_called);
        }

        REQUIRE(array.back().value == 3);
        array.insert(array.end(), type::move(complex_mock_item(4)));
        REQUIRE(array.size() == 5);

        {
            complex_mock_item const & item = array.back();
            REQUIRE(item.value == 4);
            REQUIRE(!item.constructor_called);
            REQUIRE(item.copy_constructor_called);
            REQUIRE(!item.destructor_called);
            REQUIRE(!item.assign_called);
            REQUIRE(!item.equality_called);
        }

        REQUIRE(array[3].value == 3);
        array.insert(array.begin() + 3, type::move(complex_mock_item(123)));
        REQUIRE(array.size() == 6);

        {
            complex_mock_item const & item = array[3];
            REQUIRE(item.value == 123);
            REQUIRE(!item.constructor_called);
            REQUIRE(item.copy_constructor_called);
            REQUIRE(!item.destructor_called);
            REQUIRE(!item.assign_called);
            REQUIRE(!item.equality_called);
        }

        REQUIRE(array.max_size() == 8);
    }

    SECTION("insert idx it_start it_end - simple")
    {
        simple_mock_item_array array_1;
        simple_mock_item_array array_2;

        array_1.emplace_back(1);
        array_1.emplace_back(2);
        array_1.emplace_back(3);

        array_2.emplace_back(4);
        array_2.emplace_back(5);
        array_2.emplace_back(6);
        array_2.emplace_back(7);
        array_2.emplace_back(8);

        REQUIRE(array_1.front().value == 1);
        array_1.insert(0, array_2.begin(), array_2.begin() + 2);
        REQUIRE(array_1.size() == 5);
        REQUIRE(array_1.front().value == 4);

        REQUIRE(array_1.back().value == 3);
        array_1.insert(array_1.size(), array_2.end() - 1, array_2.end());
        REQUIRE(array_1.size() == 6);
        REQUIRE(array_1.back().value == 8);

        REQUIRE(array_1[3].value == 2);
        array_1.insert(3, array_2.begin(), array_2.end());
        REQUIRE(array_1.size() == 11);
        REQUIRE(array_1[3].value == 4);

        REQUIRE(array_1.max_size() == 11);
        REQUIRE(array_2.max_size() == 8);
    }

    SECTION("insert idx it_start it_end - complex")
    {
        complex_mock_item_array array_1;
        complex_mock_item_array array_2;

        array_1.emplace_back(1);
        array_1.emplace_back(2);
        array_1.emplace_back(3);

        array_2.emplace_back(4);
        array_2.emplace_back(5);
        array_2.emplace_back(6);
        array_2.emplace_back(7);
        array_2.emplace_back(8);

        REQUIRE(array_1.front().value == 1);
        array_1.insert(0, array_2.begin(), array_2.begin() + 2);
        REQUIRE(array_1.size() == 5);
        REQUIRE(array_1.front().value == 4);

        container::for_each(
            array_1.begin(),
            array_1.begin() + 2,
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(!item.constructor_called);
                REQUIRE(item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });

        container::for_each(
            array_1.begin() + 2,
            array_1.end(),
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(item.constructor_called);
                REQUIRE(!item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });

        REQUIRE(array_1.back().value == 3);
        array_1.insert(array_1.size(), array_2.end() - 1, array_2.end());
        REQUIRE(array_1.size() == 6);
        REQUIRE(array_1.back().value == 8);

        container::for_each(
            array_1.begin(),
            array_1.begin() + 2,
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(!item.constructor_called);
                REQUIRE(item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });

        container::for_each(
            array_1.begin() + 2,
            array_1.end() - 1,
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(item.constructor_called);
                REQUIRE(!item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });

        container::for_each(
            array_1.end() - 1,
            array_1.end(),
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(!item.constructor_called);
                REQUIRE(item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });

        REQUIRE(array_1[3].value == 2);
        array_1.insert(3, array_2.begin(), array_2.end());
        REQUIRE(array_1.size() == 11);
        REQUIRE(array_1[3].value == 4);

        container::for_each(
            array_1.begin(),
            array_1.begin() + 2,
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(!item.constructor_called);
                REQUIRE(item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });

        container::for_each(
            array_1.begin() + 2,
            array_1.begin() + 3,
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(item.constructor_called);
                REQUIRE(!item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });

        container::for_each(
            array_1.begin() + 3,
            array_1.begin() + 8,
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(!item.constructor_called);
                REQUIRE(item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });

        container::for_each(
            array_1.begin() + 8,
            array_1.end() - 1,
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(item.constructor_called);
                REQUIRE(!item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });

        container::for_each(
            array_1.end() - 1,
            array_1.end(),
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(!item.constructor_called);
                REQUIRE(item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });

        REQUIRE(array_1.max_size() == 11);
        REQUIRE(array_2.max_size() == 8);
    }

    SECTION("insert it it_start it_end - simple")
    {
        simple_mock_item_array array_1;
        simple_mock_item_array array_2;

        array_1.emplace_back(1);
        array_1.emplace_back(2);
        array_1.emplace_back(3);

        array_2.emplace_back(4);
        array_2.emplace_back(5);
        array_2.emplace_back(6);
        array_2.emplace_back(7);
        array_2.emplace_back(8);

        REQUIRE(array_1.front().value == 1);
        array_1.insert(array_1.begin(), array_2.begin(), array_2.begin() + 2);
        REQUIRE(array_1.size() == 5);
        REQUIRE(array_1.front().value == 4);

        REQUIRE(array_1.back().value == 3);
        array_1.insert(array_1.end(), array_2.end() - 1, array_2.end());
        REQUIRE(array_1.size() == 6);
        REQUIRE(array_1.back().value == 8);

        REQUIRE(array_1[3].value == 2);
        array_1.insert(array_1.begin() + 3, array_2.begin(), array_2.end());
        REQUIRE(array_1.size() == 11);
        REQUIRE(array_1[3].value == 4);

        REQUIRE(array_1.max_size() == 11);
        REQUIRE(array_2.max_size() == 8);
    }

    SECTION("insert it it_start it_end - complex")
    {
        complex_mock_item_array array_1;
        complex_mock_item_array array_2;

        array_1.emplace_back(1);
        array_1.emplace_back(2);
        array_1.emplace_back(3);

        array_2.emplace_back(4);
        array_2.emplace_back(5);
        array_2.emplace_back(6);
        array_2.emplace_back(7);
        array_2.emplace_back(8);

        REQUIRE(array_1.front().value == 1);
        array_1.insert(array_1.begin(), array_2.begin(), array_2.begin() + 2);
        REQUIRE(array_1.size() == 5);
        REQUIRE(array_1.front().value == 4);

        container::for_each(
            array_1.begin(),
            array_1.begin() + 2,
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(!item.constructor_called);
                REQUIRE(item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });

        container::for_each(
            array_1.begin() + 2,
            array_1.end(),
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(item.constructor_called);
                REQUIRE(!item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });

        REQUIRE(array_1.back().value == 3);
        array_1.insert(array_1.end(), array_2.end() - 1, array_2.end());
        REQUIRE(array_1.size() == 6);
        REQUIRE(array_1.back().value == 8);

        container::for_each(
            array_1.begin(),
            array_1.begin() + 2,
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(!item.constructor_called);
                REQUIRE(item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });

        container::for_each(
            array_1.begin() + 2,
            array_1.end() - 1,
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(item.constructor_called);
                REQUIRE(!item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });

        container::for_each(
            array_1.end() - 1,
            array_1.end(),
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(!item.constructor_called);
                REQUIRE(item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });

        REQUIRE(array_1[3].value == 2);
        array_1.insert(array_1.begin() + 3, array_2.begin(), array_2.end());
        REQUIRE(array_1.size() == 11);
        REQUIRE(array_1[3].value == 4);

        container::for_each(
            array_1.begin(),
            array_1.begin() + 2,
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(!item.constructor_called);
                REQUIRE(item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });

        container::for_each(
            array_1.begin() + 2,
            array_1.begin() + 3,
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(item.constructor_called);
                REQUIRE(!item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });

        container::for_each(
            array_1.begin() + 3,
            array_1.begin() + 8,
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(!item.constructor_called);
                REQUIRE(item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });

        container::for_each(
            array_1.begin() + 8,
            array_1.end() - 1,
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(item.constructor_called);
                REQUIRE(!item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });

        container::for_each(
            array_1.end() - 1,
            array_1.end(),
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(!item.constructor_called);
                REQUIRE(item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });

        REQUIRE(array_1.max_size() == 11);
        REQUIRE(array_2.max_size() == 8);
    }
}

TEST_CASE("array_dynamic.pop_back", "[gg.array_dynamic]")
{
    SECTION("pop_back")
    {
        simple_mock_item_array array;
        array.emplace_back(1);
        array.emplace_back(3);
        array.emplace_back(2);

        REQUIRE(array.back().value == 2);
        array.pop_back();
        REQUIRE(array.size() == 2);
        REQUIRE(array.back().value == 3);

        REQUIRE(array.max_size() == 8);
    }
}

TEST_CASE("array_dynamic.push_back", "[gg.array_dynamic]")
{
    SECTION("push_back item - simple")
    {
        simple_mock_item_array array;
        array.push_back(1);
        array.push_back(3);
        array.push_back(2);

        REQUIRE(array.back().value == 2);
        simple_mock_item mock_item(5);
        array.push_back(mock_item);
        REQUIRE(array.size() == 4);
        REQUIRE(array.back().value == 5);

        REQUIRE(array.max_size() == 8);
    }

    SECTION("push_back item - complex")
    {
        complex_mock_item_array array;
        array.push_back(1);
        array.push_back(3);
        array.push_back(2);

        REQUIRE(array.back().value == 2);
        complex_mock_item mock_item(5);
        array.push_back(mock_item);
        REQUIRE(array.size() == 4);
        REQUIRE(array.back().value == 5);

        container::for_each(
            array.begin(),
            array.end(),
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(!item.constructor_called);
                REQUIRE(item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });

        REQUIRE(array.max_size() == 8);
    }

    SECTION("push_back rvalue_item - simple")
    {
        simple_mock_item_array array;
        array.push_back(1);
        array.push_back(3);
        array.push_back(2);

        REQUIRE(array.back().value == 2);
        array.push_back(type::move(simple_mock_item(5)));
        REQUIRE(array.size() == 4);
        REQUIRE(array.back().value == 5);

        REQUIRE(array.max_size() == 8);
    }

    SECTION("push_back rvalue_item - complex")
    {
        complex_mock_item_array array;
        array.push_back(type::move(complex_mock_item(1)));
        array.push_back(type::move(complex_mock_item(3)));
        array.push_back(type::move(complex_mock_item(2)));

        REQUIRE(array.back().value == 2);
        array.push_back(type::move(complex_mock_item(5)));
        REQUIRE(array.size() == 4);
        REQUIRE(array.back().value == 5);

        container::for_each(
            array.begin(),
            array.end(),
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(!item.constructor_called);
                REQUIRE(item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });

        REQUIRE(array.max_size() == 8);
    }
}

TEST_CASE("array_dynamic.reserve", "[gg.array_dynamic]")
{
    SECTION("reserve increase")
    {
        simple_mock_item_array array;
        REQUIRE(array.max_size() == 0);
        REQUIRE(array.size() == 0);

        array.reserve(256);
        REQUIRE(array.max_size() == 256);
        REQUIRE(array.size() == 0);
    }

    SECTION("reserve shrink does nothing")
    {
        simple_mock_item_array array;
        REQUIRE(array.max_size() == 0);
        REQUIRE(array.size() == 0);

        array.reserve(256);
        REQUIRE(array.max_size() == 256);
        REQUIRE(array.size() == 0);

        array.reserve(16);
        REQUIRE(array.max_size() == 256);
        REQUIRE(array.size() == 0);
    }
}

TEST_CASE("array_dynamic.resize", "[gg.array_dynamic]")
{
    SECTION("resize increase - simple")
    {
        simple_mock_item_array array;
        REQUIRE(array.max_size() == 0);
        REQUIRE(array.size() == 0);

        array.resize(250);
        REQUIRE(array.max_size() == 250);
        REQUIRE(array.size() == 250);
    }

    SECTION("resize increase - complex")
    {
        complex_mock_item_array array;
        REQUIRE(array.max_size() == 0);
        REQUIRE(array.size() == 0);

        array.resize(250);
        REQUIRE(array.max_size() == 250);
        REQUIRE(array.size() == 250);

        container::for_each(
            array.begin(),
            array.end(),
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(!item.constructor_called);
                REQUIRE(item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
                REQUIRE(item.value == 0);
            });
    }

    SECTION("resize increase with arguments - simple")
    {
        simple_mock_item_array array;
        REQUIRE(array.max_size() == 0);
        REQUIRE(array.size() == 0);

        array.resize(250, 6);
        REQUIRE(array.max_size() == 250);
        REQUIRE(array.size() == 250);

        container::for_each(
            array.begin(),
            array.end(),
            [] (simple_mock_item_array::const_reference item)
            {
                REQUIRE(item.value == 6);
            });
    }

    SECTION("resize increase with arguments - complex")
    {
        complex_mock_item_array array;
        REQUIRE(array.max_size() == 0);
        REQUIRE(array.size() == 0);

        array.resize(250, 6);
        REQUIRE(array.max_size() == 250);
        REQUIRE(array.size() == 250);

        container::for_each(
            array.begin(),
            array.end(),
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(!item.constructor_called);
                REQUIRE(item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
                REQUIRE(item.value == 6);
            });
    }

    SECTION("resize decrease - simple")
    {
        simple_mock_item_array array;
        REQUIRE(array.max_size() == 0);
        REQUIRE(array.size() == 0);

        array.resize(250);
        REQUIRE(array.max_size() == 250);
        REQUIRE(array.size() == 250);

        array.resize(20);
        REQUIRE(array.max_size() == 250);
        REQUIRE(array.size() == 20);
    }

    SECTION("resize decrease - complex")
    {
        complex_mock_item_array array;
        REQUIRE(array.max_size() == 0);
        REQUIRE(array.size() == 0);

        array.resize(250);
        REQUIRE(array.max_size() == 250);
        REQUIRE(array.size() == 250);

        array.resize(20);
        REQUIRE(array.max_size() == 250);
        REQUIRE(array.size() == 20);

        container::for_each(
            array.begin(),
            array.end(),
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(!item.constructor_called);
                REQUIRE(item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
                REQUIRE(item.value == 0);
            });
    }
}

TEST_CASE("array_dynamic.max_size", "[gg.array_dynamic]")
{
    SECTION("max_size")
    {
        simple_mock_item_array array;

        array.reserve(1);
        REQUIRE(array.max_size() == 1);

        array.reserve(2);
        REQUIRE(array.max_size() == 2);

        array.reserve(3);
        REQUIRE(array.max_size() == 3);
    }
}

TEST_CASE("array_dynamic.size", "[gg.array_dynamic]")
{
    SECTION("size")
    {
        simple_mock_item_array array;

        array.resize(1);
        REQUIRE(array.size() == 1);

        array.resize(2);
        REQUIRE(array.size() == 2);

        array.resize(3);
        REQUIRE(array.size() == 3);
    }
}

TEST_CASE("array_dynamic.is_empty", "[gg.array_dynamic]")
{
    SECTION("is_empty")
    {
        simple_mock_item_array array;
        REQUIRE(array.is_empty());

        array.emplace_back(3);
        array.emplace_back(7);
        array.emplace_back(4);
        array.emplace_back(1);
        array.emplace_back(5);

        size_type max_size = array.max_size();
        REQUIRE(array.size() == 5);
        REQUIRE(!array.is_empty());

        array.clear();

        REQUIRE(array.max_size() == max_size);
        REQUIRE(array.size() == 0);
        REQUIRE(array.is_empty());
    }
}

//==============================================================================

TEST_CASE("array_dynamic.find_if", "[gg.array_dynamic]")
{
    SECTION("find_if")
    {
        simple_mock_item_array array;
        array.emplace_back(1);
        array.emplace_back(2);
        array.emplace_back(3);

        auto cit = container::find_if(
            array.begin(),
            array.end(),
            [value = 3](simple_mock_item_array::const_reference item)
            {
                return item.value == value;
            });

        REQUIRE(cit != array.end());
        REQUIRE(cit->value == 3);
    }

    SECTION("!(find_if)")
    {
        simple_mock_item_array array;
        array.emplace_back(1);
        array.emplace_back(2);
        array.emplace_back(3);

        auto cit = container::find_if(
            array.begin(),
            array.end(),
            [value = 5](simple_mock_item_array::const_reference item)
            {
                return item.value == value;
            });

        REQUIRE(cit == array.end());
    }
}

TEST_CASE("array_dynamic.for_each", "[gg.array_dynamic]")
{
    SECTION("for_each")
    {
        simple_mock_item_array array;
        array.emplace_back(1);
        array.emplace_back(2);
        array.emplace_back(3);

        int32 i = 0;
        container::for_each(
            array.begin(),
            array.end(),
            [&i] (simple_mock_item_array::const_reference)
            {
                ++i;
            });

        REQUIRE(i == 3);
    }
}

TEST_CASE("array_dynamic.remove_if", "[gg.array_dynamic]")
{
    SECTION("remove_if - simple")
    {
        simple_mock_item_array array;
        array.emplace_back(1);
        array.emplace_back(2);
        array.emplace_back(3);
        array.emplace_back(4);
        array.emplace_back(5);
        REQUIRE(array.size() == 5);
        REQUIRE(array[2].value == 3);

        auto cit =
            container::remove_if(
                array.begin(),
                array.end(),
                [value = 3](simple_mock_item_array::const_reference item)
                {
                    return item.value == value;
            });

        REQUIRE(cit != array.end());
        REQUIRE(array.size() == 5);
        REQUIRE(array[2].value == 4);
    }

    SECTION("remove_if - complex")
    {
        complex_mock_item_array array;
        array.emplace_back(1);
        array.emplace_back(2);
        array.emplace_back(3);
        array.emplace_back(4);
        array.emplace_back(5);
        REQUIRE(array.size() == 5);
        REQUIRE(array[2].value == 3);

        auto cit =
            container::remove_if(
                array.begin(),
                array.end(),
                [value = 3](complex_mock_item_array::const_reference item)
                {
                    return item.value == value;
            });

        REQUIRE(array.size() == 5);
        REQUIRE(array[2].value == 4);

        container::for_each(
            array.begin(),
            array.begin() + 2,
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(item.constructor_called);
                REQUIRE(!item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });

        container::for_each(
            array.begin() + 2,
            cit,
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(item.constructor_called);
                REQUIRE(!item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(item.assign_called);
                REQUIRE(!item.equality_called);
            });

        container::for_each(
            cit,
            array.end(),
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(item.constructor_called);
                REQUIRE(!item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });
    }
}

TEST_CASE("array_dynamic.sort", "[gg.array_dynamic]")
{
    SECTION("sort - simple")
    {
        simple_mock_item_array array;
        array.emplace_back(3);
        array.emplace_back(1);
        array.emplace_back(4);
        array.emplace_back(2);
        array.emplace_back(8);
        array.emplace_back(7);
        array.emplace_back(5);
        array.emplace_back(6);

        int32 i = 0;
        container::for_each(
            array.begin(),
            array.end(),
            [&i] (simple_mock_item_array::const_reference item)
            {
                REQUIRE(item.value != ++i);
            });

        container::sort(array.begin(), array.end());

        i = 0;
        container::for_each(
            array.begin(),
            array.end(),
            [&i] (simple_mock_item_array::const_reference item)
            {
                REQUIRE(item.value == ++i);
            });
    }

    SECTION("sort - complex")
    {
        complex_mock_item_array array;
        array.emplace_back(3);
        array.emplace_back(1);
        array.emplace_back(4);
        array.emplace_back(2);
        array.emplace_back(8);
        array.emplace_back(7);
        array.emplace_back(5);
        array.emplace_back(6);

        int32 i = 0;
        container::for_each(
            array.begin(),
            array.end(),
            [&i] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(item.value != ++i);
                REQUIRE(item.constructor_called);
                REQUIRE(!item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });

        container::sort(array.begin(), array.end());

        i = 0;
        container::for_each(
            array.begin(),
            array.end(),
            [&i] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(item.value == ++i);
                REQUIRE(item.constructor_called);
                REQUIRE(!item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(item.assign_called);
                REQUIRE(!item.equality_called);
            });
    }

    SECTION("sort function - simple")
    {
        simple_mock_item_array array;
        array.emplace_back(3);
        array.emplace_back(1);
        array.emplace_back(4);
        array.emplace_back(2);
        array.emplace_back(8);
        array.emplace_back(7);
        array.emplace_back(5);
        array.emplace_back(6);

        int32 i = 0;
        container::for_each(
            array.begin(),
            array.end(),
            [&i] (simple_mock_item_array::const_reference item)
            {
                REQUIRE(item.value != ++i);
            });

        container::sort(
            array.begin(),
            array.end(),
            [] (simple_mock_item_array::const_reference litem,
                simple_mock_item_array::const_reference ritem)
            {
                return litem.value < ritem.value;
            });

        i = 0;
        container::for_each(
            array.begin(),
            array.end(),
            [&i] (simple_mock_item_array::const_reference item)
            {
                REQUIRE(item.value == ++i);
            });
    }

    SECTION("sort function - complex")
    {
        complex_mock_item_array array;
        array.emplace_back(3);
        array.emplace_back(1);
        array.emplace_back(4);
        array.emplace_back(2);
        array.emplace_back(8);
        array.emplace_back(7);
        array.emplace_back(5);
        array.emplace_back(6);

        int32 i = 0;
        container::for_each(
            array.begin(),
            array.end(),
            [&i] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(item.value != ++i);
                REQUIRE(item.constructor_called);
                REQUIRE(!item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(!item.equality_called);
            });

        container::sort(
            array.begin(),
            array.end(),
            [] (complex_mock_item_array::const_reference litem,
                complex_mock_item_array::const_reference ritem)
            {
                return litem.value < ritem.value;
            });

        i = 0;
        container::for_each(
            array.begin(),
            array.end(),
            [&i] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(item.value == ++i);
                REQUIRE(item.constructor_called);
                REQUIRE(!item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(item.assign_called);
                REQUIRE(!item.equality_called);
            });
    }
}

//==============================================================================
}
//==============================================================================
