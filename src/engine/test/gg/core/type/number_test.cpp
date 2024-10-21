#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/type/number.h"

//==============================================================================
namespace gg::number_test
{
//==============================================================================

class mock_number : public number<mock_number, int32>
{
public:

    mock_number(void) = default;
    mock_number(int32 && value) : number<mock_number, int32>(type::move(value)) {}
    ~mock_number(void) = default;
};

//==============================================================================

TEST_CASE("number", "[gg.number]")
{
    SECTION("construct")
    {
        REQUIRE(!type::is_constructible<number<mock_number, int32>>::value);
        REQUIRE(!type::is_trivially_constructible<number<mock_number, int32>>::value);
        REQUIRE(!type::is_trivially_constructible<number<mock_number, int32>>::value);
    }

    SECTION("copy")
    {
        REQUIRE(!type::is_copy_constructible<number<mock_number, int32>>::value);
        REQUIRE(!type::is_trivially_copy_constructible<number<mock_number, int32>>::value);
        REQUIRE(!type::is_copy_constructible<number<mock_number, int32>>::value);
        REQUIRE(!type::is_trivially_copy_constructible<number<mock_number, int32>>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(!type::is_destructible<number<mock_number, int32>>::value);
        REQUIRE(!type::is_trivially_destructible<number<mock_number, int32>>::value);
        REQUIRE(!type::is_trivially_destructible<number<mock_number, int32>>::value);
    }

    SECTION("assign")
    {
        REQUIRE(type::is_copy_assignable<number<mock_number, int32>>::value);
        REQUIRE(type::is_trivially_assignable<number<mock_number, int32>>::value);
    }

    SECTION("compare")
    {
        REQUIRE(!type::is_comparable<number<mock_number, int32>>::value);
    }

    SECTION("pod")
    {
        REQUIRE(type::is_pod<number<mock_number, int32>>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<number<mock_number, int32>>::value);
    }

    SECTION("sizeof")
    {
        REQUIRE(
            sizeof(number<mock_number, int32>) ==
            sizeof(number<mock_number, int32>::storage_type)
        );
    }
}

TEST_CASE("number.constructor", "[gg.number]")
{
    SECTION("number()")
    {
        REQUIRE(mock_number().get() == 0);
    }

    SECTION("number(int)")
    {
        REQUIRE(mock_number(5).get() == 5);
    }

    SECTION("number(number)")
    {
        mock_number number(5);
        REQUIRE(mock_number(number).get() == 5);
        REQUIRE(number.get() == 5);
    }
}

TEST_CASE("number.operator+", "[gg.number]")
{
    SECTION("number +")
    {
        mock_number number(5);
        REQUIRE((+number).get() == 5);
    }

    SECTION("number + number")
    {
        REQUIRE((mock_number(5) + mock_number(5)).get() == 10);
    }
}

TEST_CASE("number.operator+=", "[gg.number]")
{
    SECTION("number += number")
    {
        mock_number number(5);
        number += mock_number(5);
        REQUIRE(number.get() == 10);
    }
}

TEST_CASE("number.operator-", "[gg.number]")
{
    SECTION("number -")
    {
        mock_number number(5);
        REQUIRE((-number).get() == -5);
    }

    SECTION("number - number")
    {
        REQUIRE((mock_number(5) - mock_number(5)).get() == 0);
    }
}

TEST_CASE("number.operator-=", "[gg.number]")
{
    SECTION("number -= number")
    {
        mock_number number(5);
        number -= mock_number(5);
        REQUIRE(number.get() == 0);
    }
}

TEST_CASE("number.operator*", "[gg.number]")
{
    SECTION("number * number")
    {
        REQUIRE((mock_number(5) * mock_number(5)).get() == 25);
    }
}

TEST_CASE("number.operator*=", "[gg.number]")
{
    SECTION("number *= number")
    {
        mock_number number(5);
        number *= mock_number(5);
        REQUIRE(number.get() == 25);
    }
}

TEST_CASE("number.operator/", "[gg.number]")
{
    SECTION("number * number")
    {
        REQUIRE((mock_number(5) / mock_number(5)).get() == 1);
    }
}

TEST_CASE("number.operator/=", "[gg.number]")
{
    SECTION("number /= number")
    {
        mock_number number(5);
        number /= mock_number(5);
        REQUIRE(number.get() == 1);
    }
}

TEST_CASE("number.operator=", "[gg.number]")
{
    SECTION("number = number")
    {
        mock_number number;
        number = mock_number(5);
        REQUIRE(number.get() == 5);
    }
}

TEST_CASE("number.operator==", "[gg.number]")
{
    SECTION("number == number")
    {
        REQUIRE(mock_number(5) == mock_number(5));
    }

    SECTION("!(number == number)")
    {
        REQUIRE(!(mock_number(0) == mock_number(5)));
    }
}

TEST_CASE("number.operator!=", "[gg.number]")
{
    SECTION("number != number")
    {
        REQUIRE(mock_number(0) != mock_number(5));
    }

    SECTION("!(number != number)")
    {
        REQUIRE(!(mock_number(5) != mock_number(5)));
    }
}

TEST_CASE("number.operator<", "[gg.number]")
{
    SECTION("number < number")
    {
        REQUIRE(mock_number(0) < mock_number(5));
    }

    SECTION("!(number < number)")
    {
        REQUIRE(!(mock_number(5) < mock_number(0)));
    }
}

TEST_CASE("number.operator<=", "[gg.number]")
{
    SECTION("number <= number")
    {
        REQUIRE(mock_number(0) <= mock_number(5));
    }

    SECTION("number <= number")
    {
        REQUIRE(mock_number(5) <= mock_number(5));
    }

    SECTION("!(number <= number)")
    {
        REQUIRE(!(mock_number(5) <= mock_number(0)));
    }
}

TEST_CASE("number.operator>", "[gg.number]")
{
    SECTION("number > number")
    {
        REQUIRE(mock_number(5) > mock_number(0));
    }

    SECTION("!(number > number)")
    {
        REQUIRE(!(mock_number(0) > mock_number(5)));
    }
}

TEST_CASE("number.operator>=", "[gg.number]")
{
    SECTION("number >= number")
    {
        REQUIRE(mock_number(5) >= mock_number(0));
    }

    SECTION("number >= number")
    {
        REQUIRE(mock_number(5) >= mock_number(5));
    }

    SECTION("!(number >= number)")
    {
        REQUIRE(!(mock_number(0) >= mock_number(5)));
    }
}

//==============================================================================
}
//==============================================================================
