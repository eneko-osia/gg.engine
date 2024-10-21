#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/container/array/array_static.h"
#include "gg/core/container/array/mock_item_array_test.h"
#include "gg/core/container/container.h"

//==============================================================================
namespace gg::array_static_test
{
//==============================================================================

static constexpr uint32 k_num_items = 8;
using simple_mock_item_array = array_static<simple_mock_item, k_num_items>;
using complex_mock_item_array = array_static<complex_mock_item, k_num_items>;

//==============================================================================

TEST_CASE("array_static", "[gg.array_static]")
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

    SECTION("sizeof")
    {
        REQUIRE(
            sizeof(simple_mock_item_array) ==
            k_num_items * sizeof(simple_mock_item_array::item_type));
        REQUIRE(
            sizeof(complex_mock_item_array) ==
            k_num_items * sizeof(complex_mock_item_array::item_type));
    }
}

TEST_CASE("array_static.constructor", "[gg.array_static]")
{
    SECTION("array_static - simple")
    {
        simple_mock_item_array array;
        REQUIRE(array.begin() != nullptr);
        REQUIRE(array.begin() != array.end());
        REQUIRE(array.data() != nullptr);
        REQUIRE(array.size() == k_num_items);
    }

    SECTION("array_static - complex")
    {
        complex_mock_item_array array;
        REQUIRE(array.begin() != nullptr);
        REQUIRE(array.begin() != array.end());
        REQUIRE(array.data() != nullptr);
        REQUIRE(array.size() == k_num_items);

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
    }

    SECTION("array_static(array_static) - simple")
    {
        simple_mock_item_array copied_array;
        copied_array[0].value = 3;
        copied_array[1].value = 2;
        copied_array[2].value = 1;

        simple_mock_item_array array(copied_array);
        REQUIRE((array == copied_array));
    }

    SECTION("array_static(array_static) - complex")
    {
        complex_mock_item_array copied_array;
        copied_array[0].value = 3;
        copied_array[1].value = 2;
        copied_array[2].value = 1;

        complex_mock_item_array array(copied_array);
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

    SECTION("array_static(item) - simple")
    {
        simple_mock_item_array array(1);
        container::for_each(
            array.begin(),
            array.end(),
            [] (simple_mock_item_array::const_reference item)
            {
                REQUIRE(item.value == 1);
            });
    }

    SECTION("array_static(item) - complex")
    {
        complex_mock_item_array array(1);
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

TEST_CASE("array_static.operator-access", "[gg.array_static]")
{
    SECTION("operator[idx]")
    {
        simple_mock_item_array array;
        array[0].value = 3;
        array[1].value = 2;
        array[2].value = 1;

        REQUIRE(array[0].value == 3);
        REQUIRE(array[1].value == 2);
        REQUIRE(array[2].value == 1);

        REQUIRE(array[0].value == array.data()[0].value);
        REQUIRE(array[1].value == array.data()[1].value);
        REQUIRE(array[2].value == array.data()[2].value);
    }
}

TEST_CASE("array_static.operator=", "[gg.array_static]")
{
    SECTION("array_static = array_static - simple")
    {
        simple_mock_item_array copied_array;
        copied_array[0].value = 3;
        copied_array[1].value = 2;
        copied_array[2].value = 1;

        simple_mock_item_array array;
        array = copied_array;
        REQUIRE((array == copied_array));
    }

    SECTION("array_static = array_static - complex")
    {
        complex_mock_item_array copied_array;
        copied_array[0].value = 3;
        copied_array[1].value = 2;
        copied_array[2].value = 1;

        complex_mock_item_array array;
        array = copied_array;
        REQUIRE((array == copied_array));

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
}

TEST_CASE("array_static.operator==", "[gg.array_static]")
{
    SECTION("array_static == array_static - simple")
    {
        simple_mock_item_array array_1;
        simple_mock_item_array array_2;

        array_1[0].value = 1;
        array_1[1].value = 2;
        array_1[2].value = 3;

        array_2[0].value = 1;
        array_2[1].value = 2;
        array_2[2].value = 3;

        REQUIRE((array_1 == array_2));
    }

    SECTION("array_static == array_static - complex")
    {
        complex_mock_item_array array_1;
        complex_mock_item_array array_2;

        array_1[0].value = 1;
        array_1[1].value = 2;
        array_1[2].value = 3;

        array_2[0].value = 1;
        array_2[1].value = 2;
        array_2[2].value = 3;

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

    SECTION("array_static == array_static(wrong data) - simple")
    {
        simple_mock_item_array array_1;
        simple_mock_item_array array_2;

        array_1[0].value = 1;
        array_1[1].value = 2;
        array_1[2].value = 3;

        array_2[0].value = 1;
        array_2[1].value = 2;
        array_2[2].value = 2;

        REQUIRE(!(array_1 == array_2));
    }

    SECTION("array_static == array_static(wrong data) - complex")
    {
        complex_mock_item_array array_1;
        complex_mock_item_array array_2;

        array_1[0].value = 1;
        array_1[1].value = 2;
        array_1[2].value = 3;

        array_2[0].value = 1;
        array_2[1].value = 1;
        array_2[2].value = 3;

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
}

TEST_CASE("array_static.operator!=", "[gg.array_static]")
{
    SECTION("array_static != array_static - simple")
    {
        simple_mock_item_array array_1;
        simple_mock_item_array array_2;

        array_1[0].value = 1;
        array_1[1].value = 2;
        array_1[2].value = 3;

        array_2[0].value = 3;
        array_2[1].value = 2;
        array_2[2].value = 1;

        REQUIRE((array_1 != array_2));
    }

    SECTION("array_static != array_static - complex")
    {
        complex_mock_item_array array_1;
        complex_mock_item_array array_2;

        array_1[0].value = 1;
        array_1[1].value = 2;
        array_1[2].value = 3;

        array_2[0].value = 3;
        array_2[1].value = 2;
        array_2[2].value = 1;

        REQUIRE((array_1 != array_2));

        container::for_each(
            array_1.begin(),
            array_1.begin() + 1,
            [] (complex_mock_item_array::const_reference item)
            {
                REQUIRE(item.constructor_called);
                REQUIRE(!item.copy_constructor_called);
                REQUIRE(!item.destructor_called);
                REQUIRE(!item.assign_called);
                REQUIRE(item.equality_called);
            });

        container::for_each(
            array_1.begin() + 1,
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

    SECTION("array_static != array_static(wrong data) - simple")
    {
        simple_mock_item_array array_1;
        simple_mock_item_array array_2;

        array_1[0].value = 1;
        array_1[1].value = 2;
        array_1[2].value = 3;

        array_2[0].value = 1;
        array_2[1].value = 2;
        array_2[2].value = 3;

        REQUIRE(!(array_1 != array_2));
    }

    SECTION("array_static != array_static(wrong data) - complex")
    {
        complex_mock_item_array array_1;
        complex_mock_item_array array_2;

        array_1[0].value = 1;
        array_1[1].value = 2;
        array_1[2].value = 3;

        array_2[0].value = 1;
        array_2[1].value = 2;
        array_2[2].value = 3;

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

TEST_CASE("array_static.back", "[gg.array_static]")
{
    SECTION("back")
    {
        simple_mock_item_array array;
        array[k_num_items - 1].value = 2;
        REQUIRE(array.back().value == 2);
    }
}

TEST_CASE("array_static.begin", "[gg.array_static]")
{
    SECTION("begin")
    {
        simple_mock_item_array array;
        array[0].value = 2;
        REQUIRE((*array.begin()).value == 2);
    }
}

TEST_CASE("array_static.end", "[gg.array_static]")
{
    SECTION("end")
    {
        simple_mock_item_array array;
        array[k_num_items - 1].value = 8;
        REQUIRE((*(array.end() - 1)).value == 8);
    }
}

TEST_CASE("array_static.front", "[gg.array_static]")
{
    SECTION("front")
    {
        simple_mock_item_array array;
        array[0].value = 1;
        REQUIRE(array.front().value == 1);
    }
}

TEST_CASE("array_static.size", "[gg.array_static]")
{
    SECTION("size")
    {
        simple_mock_item_array array;
        REQUIRE(array.size() == k_num_items);
    }
}

//==============================================================================

TEST_CASE("array_static.find_if", "[gg.array_static]")
{
    SECTION("find_if")
    {
        simple_mock_item_array array;
        array[0].value = 1;
        array[1].value = 2;
        array[2].value = 3;

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
        array[0].value = 1;
        array[1].value = 2;
        array[2].value = 3;

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

TEST_CASE("array_static.for_each", "[gg.array_static]")
{
    SECTION("for_each")
    {
        simple_mock_item_array array;

        int32 i = 0;
        container::for_each(
            array.begin(),
            array.end(),
            [&i] (simple_mock_item_array::const_reference)
            {
                ++i;
            });

        REQUIRE(i == k_num_items);
    }
}

TEST_CASE("array_static.sort", "[gg.array_static]")
{
    SECTION("sort - simple")
    {
        simple_mock_item_array array;
        array[0].value = 3;
        array[1].value = 1;
        array[2].value = 4;
        array[3].value = 2;
        array[4].value = 8;
        array[5].value = 7;
        array[6].value = 5;
        array[7].value = 6;

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
        array[0].value = 3;
        array[1].value = 1;
        array[2].value = 4;
        array[3].value = 2;
        array[4].value = 8;
        array[5].value = 7;
        array[6].value = 5;
        array[7].value = 6;

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
        array[0].value = 3;
        array[1].value = 1;
        array[2].value = 4;
        array[3].value = 2;
        array[4].value = 8;
        array[5].value = 7;
        array[6].value = 5;
        array[7].value = 6;

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
        array[0].value = 3;
        array[1].value = 1;
        array[2].value = 4;
        array[3].value = 2;
        array[4].value = 8;
        array[5].value = 7;
        array[6].value = 5;
        array[7].value = 6;

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
