#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/string/type/string_ref.h"
#include "gg/core/string/type/string_static.h"

//==============================================================================
namespace gg::string_ref_test
{
//==============================================================================

TEST_CASE("string_ref", "[gg.string_ref]")
{
    SECTION("assign")
    {
        REQUIRE(type::is_copy_assignable<string_ref>::value);
        REQUIRE(!type::is_trivially_assignable<string_ref>::value);
        REQUIRE(type::is_copy_assignable<string_ref>::value);
        REQUIRE(!type::is_trivially_assignable<string_ref>::value);
    }

    SECTION("construct")
    {
        REQUIRE(type::is_constructible<string_ref>::value);
        REQUIRE(!type::is_trivially_constructible<string_ref>::value);
        REQUIRE(!type::is_trivially_constructible<string_ref>::value);
    }

    SECTION("copy")
    {
        REQUIRE(type::is_copy_constructible<string_ref>::value);
        REQUIRE(!type::is_trivially_copy_constructible<string_ref>::value);
        REQUIRE(type::is_copy_constructible<string_ref>::value);
        REQUIRE(!type::is_trivially_copy_constructible<string_ref>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(type::is_destructible<string_ref>::value);
        REQUIRE(type::is_trivially_destructible<string_ref>::value);
        REQUIRE(type::is_trivially_destructible<string_ref>::value);
    }

    SECTION("compare")
    {
        // @todo fix this
        // REQUIRE(type::is_comparable<string_ref>::value);
    }

    SECTION("pod")
    {
        REQUIRE(!type::is_pod<string_ref>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<string_ref>::value);
    }
}

TEST_CASE("string_ref.constructor", "[gg.string_ref]")
{
    SECTION("string_ref()")
    {
        string_ref string;
        REQUIRE(string.begin() == string.end());
        REQUIRE(string.size() == 0);
        REQUIRE(string.is_empty());
    }

    SECTION("string_ref(char*)")
    {
        string_ref string("test");
        REQUIRE(string == "test");
    }

    SECTION("string_ref(string_ref)")
    {
        string_ref copied_string("test");
        string_ref string(copied_string);
        REQUIRE(string == copied_string);
    }

    SECTION("string_ref(rvalue_string_ref)")
    {
        string_ref moved_string("test");
        string_ref copied_string(moved_string);
        string_ref string(type::move(moved_string));
        REQUIRE((string == copied_string));

        REQUIRE(moved_string.begin() == moved_string.end());
        REQUIRE(moved_string.size() == 0);
        REQUIRE(moved_string.is_empty());
    }

    SECTION("string_ref(string)")
    {
        string_static<> referenced_string("test");
        string_ref string(referenced_string);
        REQUIRE(string == referenced_string);
    }
}

TEST_CASE("string_ref.operator-access", "[gg.string_ref]")
{
    SECTION("operator[idx]")
    {
        string_ref string("test");

        REQUIRE(string[0] == 't');
        REQUIRE(string[1] == 'e');
        REQUIRE(string[2] == 's');
        REQUIRE(string[3] == 't');
    }
}

TEST_CASE("string_ref.operator=", "[gg.string_ref]")
{
    SECTION("string_ref = char*")
    {
        string_ref string;
        string = "test";
        REQUIRE(string == "test");
    }

    SECTION("string_ref = string_ref")
    {
        string_ref string;
        string = string_ref("test");
        REQUIRE(string == "test");
    }

    SECTION("string_ref = rvalue_string_ref")
    {
        string_ref string;
        string_ref moved_string("test");
        string = type::move(moved_string);
        REQUIRE((string == "test"));

        REQUIRE(moved_string.begin() == moved_string.end());
        REQUIRE(moved_string.size() == 0);
        REQUIRE(moved_string.is_empty());
    }

    SECTION("string_ref = string")
    {
        string_static<> referenced_string("test");
        string_ref string;
        string = referenced_string;
        REQUIRE(string == referenced_string);
    }
}

TEST_CASE("string_ref.operator==", "[gg.string_ref]")
{
    SECTION("string_ref == char*")
    {
        REQUIRE(string_ref("test") == "test");
    }

    SECTION("!(string_ref == char*)")
    {
        REQUIRE(!(string_ref("test") == "string"));
    }

    SECTION("char* == string_ref")
    {
        REQUIRE("test" == string_ref("test"));
    }

    SECTION("!(char* == string_ref)")
    {
        REQUIRE(!("test" == string_ref("string")));
    }

    SECTION("string_ref == string")
    {
        REQUIRE(string_ref("test") == string_ref("test"));
    }

    SECTION("!(string_ref == string)")
    {
        REQUIRE(!(string_ref("test") == string_ref("string")));
    }
}

TEST_CASE("string_ref.operator!=", "[gg.string_ref]")
{
    SECTION("string_ref != char*")
    {
        REQUIRE(string_ref("test") != "string");
    }

    SECTION("!(string_ref != char*)")
    {
        REQUIRE(!(string_ref("test") != "test"));
    }

    SECTION("char* != string_ref")
    {
        REQUIRE("test" != string_ref("string"));
    }

    SECTION("!(char* != string_ref)")
    {
        REQUIRE(!("test" != string_ref("test")));
    }

    SECTION("string_ref != string")
    {
        REQUIRE(string_ref("test") != string_ref("string"));
    }

    SECTION("!(string_ref != string)")
    {
        REQUIRE(!(string_ref("test") != string_ref("test")));
    }
}

TEST_CASE("string_ref.operator<", "[gg.string_ref]")
{
    SECTION("string_ref < char*")
    {
        REQUIRE(string_ref("test_a") < "test_b");
    }

    SECTION("!(string_ref < char*)")
    {
        REQUIRE(!(string_ref("test_b") < "test_a"));
    }

    SECTION("char* < string_ref")
    {
        REQUIRE("test_a" < string_ref("test_b"));
    }

    SECTION("!(char* < string_ref)")
    {
        REQUIRE(!("test_b" < string_ref("test_a")));
    }

    SECTION("string_ref < string")
    {
        REQUIRE(string_ref("test_a") < string_ref("test_b"));
    }

    SECTION("!(string_ref < string)")
    {
        REQUIRE(!(string_ref("test_b") < string_ref("test_a")));
    }
}

TEST_CASE("string_ref.operator>", "[gg.string_ref]")
{
    SECTION("string_ref > char*")
    {
        REQUIRE(string_ref("test_b") > "test_a");
    }

    SECTION("!(string_ref > char*)")
    {
        REQUIRE(!(string_ref("test_a") > "test_b"));
    }

    SECTION("char* > string_ref")
    {
        REQUIRE("test_b" > string_ref("test_a"));
    }

    SECTION("!(char* > string_ref)")
    {
        REQUIRE(!("test_a" > string_ref("test_b")));
    }

    SECTION("string_ref > string")
    {
        REQUIRE(string_ref("test_b") > string_ref("test_a"));
    }

    SECTION("!(string_ref > string)")
    {
        REQUIRE(!(string_ref("test_a") > string_ref("test_b")));
    }
}

TEST_CASE("string_ref.begin", "[gg.string_ref]")
{
    SECTION("begin")
    {
        string_ref string("this is a test string");
        REQUIRE(*string.begin() == 't');
    }
}

TEST_CASE("string_ref.clear", "[gg.string_ref]")
{
    SECTION("clear")
    {
        string_ref string("this is a test string");
        REQUIRE(!string.is_empty());

        string.clear();
        REQUIRE(string.is_empty());
    }
}

TEST_CASE("string_ref.end", "[gg.string_ref]")
{
    SECTION("end")
    {
        string_ref string("this is a test string");
        REQUIRE(*(string.end() - 1) == 'g');
    }
}

TEST_CASE("string_ref.find", "[gg.string_ref]")
{
    SECTION("find char*")
    {
        string_ref string("this is a test string");
        REQUIRE(string.find("is") == 2);
    }

    SECTION("!(find char*)")
    {
        string_ref string("this is a test string");
        REQUIRE(string.find("ddfv") == string::npos);
    }

    SECTION("find char* idx")
    {
        string_ref string("this is a test string");
        REQUIRE(string.find("is", 3) == 5);
    }

    SECTION("find string")
    {
        string_ref string("this is a test string");
        string_ref pattern("ng");
        REQUIRE(string.find(pattern) == 19);
    }

    SECTION("!(find string)")
    {
        string_ref string("this is a test string");
        string_ref pattern("b");
        REQUIRE(string.find(pattern) == string::npos);
    }

    SECTION("find string idx")
    {
        string_ref string("this is a test string");
        string_ref pattern("t");
        REQUIRE(string.find(pattern, 10) == 10);
    }
}

TEST_CASE("string_ref.set", "[gg.string_ref]")
{
    SECTION("set char*")
    {
        string_ref string;
        string.set("this is a test string");
        REQUIRE(string == "this is a test string");
    }

    SECTION("set string_ref")
    {
        string_ref string;
        string.set(string_ref("this is a test string"));
        REQUIRE(string == "this is a test string");
    }

    SECTION("set rvalue_string_ref")
    {
        string_ref string;
        string_ref moved_string("this is a test string");
        string.set(type::move(moved_string));
        REQUIRE((string == "this is a test string"));

        REQUIRE(moved_string.begin() == moved_string.end());
        REQUIRE(moved_string.size() == 0);
        REQUIRE(moved_string.is_empty());
    }

    SECTION("set string")
    {
        string_static<32> referenced_string("this is a test string");
        string_ref string;
        string.set(referenced_string);
        REQUIRE(string == referenced_string);
    }
}

TEST_CASE("string_ref.size", "[gg.string_ref]")
{
    SECTION("size")
    {
        string_ref string("test");
        REQUIRE(string.size() == 4);
    }
}

TEST_CASE("string_ref.is_empty", "[gg.string_ref]")
{
    SECTION("is_empty")
    {
        string_ref string;
        REQUIRE(string.is_empty());
    }

    SECTION("!(is_empty)")
    {
        string_ref string("test");
        REQUIRE(!string.is_empty());
    }
}

//==============================================================================

TEST_CASE("string_ref::compare", "[gg.string]")
{
    SECTION("compare")
    {
        string_ref text(
            GG_TEXT(
                "Lorem ipsum dolor sit amet, "
                "consectetur adipiscing elit,\r\n"));
        REQUIRE(
            string::compare(
                text.c_str(),
                "Lorem ipsum dolor sit amet, consectetur "
                "adipiscing elit,\r\n") == 0);
    }
}

TEST_CASE("string_ref::find", "[gg.string]")
{
    SECTION("find")
    {
        string_ref text(
            GG_TEXT(
                "Lorem ipsum dolor sit amet, "
                "consectetur adipiscing elit,\r\n"));
        REQUIRE(
            (string::find(
                text.c_str(), GG_TEXT("consectetur")) -
            text.c_str()) == 28);
    }
}

TEST_CASE("string_ref::length", "[gg.string]")
{
    SECTION("length")
    {
        string_ref text(
            GG_TEXT(
                "Lorem ipsum dolor sit amet, "
                "consectetur adipiscing elit,\r\n"));
        REQUIRE(string::length(text.c_str()) == 58);
        REQUIRE(text.size() == 58);
    }
}

//==============================================================================
}
//==============================================================================
