#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/string/type/string_dynamic.h"
#include "gg/core/string/type/string_ref.h"

//==============================================================================
namespace gg::string_dynamic_test
{
//==============================================================================

TEST_CASE("string_dynamic", "[gg.string_dynamic]")
{
    SECTION("assign")
    {
        REQUIRE(type::is_copy_assignable<string_dynamic>::value);
        REQUIRE(!type::is_trivially_assignable<string_dynamic>::value);
        REQUIRE(type::is_copy_assignable<string_dynamic>::value);
        REQUIRE(!type::is_trivially_assignable<string_dynamic>::value);
    }

    SECTION("construct")
    {
        REQUIRE(type::is_constructible<string_dynamic>::value);
        REQUIRE(!type::is_trivially_constructible<string_dynamic>::value);
        REQUIRE(!type::is_trivially_constructible<string_dynamic>::value);
    }

    SECTION("copy")
    {
        REQUIRE(type::is_copy_constructible<string_dynamic>::value);
        REQUIRE(!type::is_trivially_copy_constructible<string_dynamic>::value);
        REQUIRE(type::is_copy_constructible<string_dynamic>::value);
        REQUIRE(!type::is_trivially_copy_constructible<string_dynamic>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(type::is_destructible<string_dynamic>::value);
        REQUIRE(!type::is_trivially_destructible<string_dynamic>::value);
        REQUIRE(!type::is_trivially_destructible<string_dynamic>::value);
    }

    SECTION("compare")
    {
        // @todo fix this
        // REQUIRE(type::is_comparable<string_dynamic>::value);
    }

    SECTION("pod")
    {
        REQUIRE(!type::is_pod<string_dynamic>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<string_dynamic>::value);
    }
}

TEST_CASE("string_dynamic.constructor", "[gg.string_dynamic]")
{
    SECTION("string_dynamic")
    {
        string_dynamic string;
        REQUIRE(string.begin() == string.end());
        REQUIRE(string.max_size() == 1);
        REQUIRE(string.size() == 0);
        REQUIRE(string.is_empty());
    }

    SECTION("string_dynamic(char)")
    {
        string_dynamic string('a');
        REQUIRE(string == "a");
        REQUIRE(string.max_size() == 2);
        REQUIRE(string.size() == 1);
    }

    SECTION("string_dynamic(char*)")
    {
        string_dynamic string("test");
        REQUIRE(string == "test");
        REQUIRE(string.max_size() == 5);
        REQUIRE(string.size() == 4);
    }

    SECTION("string_dynamic(char*, size)")
    {
        string_dynamic string("this is a test string", 16);
        REQUIRE(string == "this is a test s");
        REQUIRE(string.size() + 1 == string.max_size());
    }

    SECTION("string_dynamic(char*, idx_start, idx_end)")
    {
        string_dynamic string("this is a test string", 4, 16);
        REQUIRE(string == " is a test st");
        REQUIRE(string.size() + 1 == string.max_size());
    }

    SECTION("string_dynamic(string_dynamic)")
    {
        string_dynamic copied_string("test");
        string_dynamic string(copied_string);
        REQUIRE(string == copied_string);
        REQUIRE(string.max_size() == 5);
        REQUIRE(string.size() == 4);
    }

    SECTION("string_dynamic(string_dynamic, size)")
    {
        string_dynamic copied_string("this is a test string");
        string_dynamic string(copied_string, 16);
        REQUIRE(string == "this is a test s");
        REQUIRE(string.size() + 1 == string.max_size());
    }

    SECTION("string_dynamic(string_dynamic, idx_start, idx_end)")
    {
        string_dynamic copied_string("this is a test string");
        string_dynamic string(copied_string, 4, 16);
        REQUIRE(string == " is a test st");
        REQUIRE(string.size() + 1 == string.max_size());
    }

    SECTION("string_dynamic(string)")
    {
        string_ref copied_string("test");
        string_dynamic string(copied_string);
        REQUIRE(string == copied_string);
        REQUIRE(string.max_size() == 5);
        REQUIRE(string.size() == 4);
    }

    SECTION("string_dynamic(string, size)")
    {
        string_ref copied_string("this is a test string");
        string_dynamic string(copied_string, 16);
        REQUIRE(string == "this is a test s");
        REQUIRE(string.size() + 1 == string.max_size());
    }

    SECTION("string_dynamic(string, idx_start, idx_end)")
    {
        string_ref copied_string("this is a test string");
        string_dynamic string(copied_string, 4, 16);
        REQUIRE(string == " is a test st");
        REQUIRE(string.size() + 1 == string.max_size());
    }

    SECTION("string_dynamic(rvalue_string_dynamic)")
    {
        string_dynamic moved_string("test");
        string_dynamic copied_string(moved_string);
        string_dynamic string(type::move(moved_string));
        REQUIRE((string == copied_string));
        REQUIRE(string.max_size() == 5);
        REQUIRE(string.size() == 4);

        REQUIRE(moved_string.begin() == nullptr);
        REQUIRE(moved_string.begin() == moved_string.end());
        REQUIRE(moved_string.max_size() == 0);
        REQUIRE(moved_string.size() == 0);
        REQUIRE(moved_string.is_empty());
    }
}

TEST_CASE("string_dynamic.operator-access", "[gg.string_dynamic]")
{
    SECTION("operator[idx]")
    {
        string_dynamic string("test");
        REQUIRE(string[0] == 't');
        REQUIRE(string[1] == 'e');
        REQUIRE(string[2] == 's');
        REQUIRE(string[3] == 't');
    }
}

TEST_CASE("string_dynamic.operator=", "[gg.string_dynamic]")
{
    SECTION("string_dynamic = char")
    {
        string_dynamic string;
        string = 'a';
        REQUIRE(string == "a");
        REQUIRE(string.max_size() == 2);
        REQUIRE(string.size() == 1);
    }

    SECTION("string_dynamic = char*")
    {
        string_dynamic string;
        string = "test";
        REQUIRE(string == "test");
        REQUIRE(string.max_size() == 5);
        REQUIRE(string.size() == 4);
    }

    SECTION("string_dynamic = string_dynamic")
    {
        string_dynamic string;
        string = string_dynamic("test");
        REQUIRE(string == "test");
        REQUIRE(string.max_size() == 5);
        REQUIRE(string.size() == 4);
    }

    SECTION("string_dynamic = rvalue_string_dynamic")
    {
        string_dynamic string;
        string_dynamic moved_string("test");
        string = type::move(moved_string);
        REQUIRE(string == "test");
        REQUIRE(string.max_size() == 5);
        REQUIRE(string.size() == 4);

        REQUIRE(moved_string.begin() == nullptr);
        REQUIRE(moved_string.begin() == moved_string.end());
        REQUIRE(moved_string.max_size() == 0);
        REQUIRE(moved_string.size() == 0);
        REQUIRE(moved_string.is_empty());
    }

    SECTION("string_dynamic = string")
    {
        string_dynamic string;
        string = string_ref("test");
        REQUIRE(string == "test");
        REQUIRE(string.max_size() == 5);
        REQUIRE(string.size() == 4);
    }
}

TEST_CASE("string_dynamic.operator==", "[gg.string_dynamic]")
{
    SECTION("string_dynamic == char*")
    {
        REQUIRE(string_dynamic("test") == "test");
    }

    SECTION("!(string_dynamic == char*)")
    {
        REQUIRE(!(string_dynamic("test") == "string"));
    }

    SECTION("char* == string_dynamic")
    {
        REQUIRE("test" == string_dynamic("test"));
    }

    SECTION("!(char* == string_dynamic)")
    {
        REQUIRE(!("test" == string_dynamic("string")));
    }

    SECTION("string_dynamic == string")
    {
        REQUIRE(string_dynamic("test") == string_dynamic("test"));
    }

    SECTION("!(string_dynamic == string)")
    {
        REQUIRE(!(string_dynamic("test") == string_dynamic("string")));
    }
}

TEST_CASE("string_dynamic.operator!=", "[gg.string_dynamic]")
{
    SECTION("string_dynamic != char*")
    {
        REQUIRE(string_dynamic("test") != "string");
    }

    SECTION("!(string_dynamic != char*)")
    {
        REQUIRE(!(string_dynamic("test") != "test"));
    }

    SECTION("char* != string_dynamic")
    {
        REQUIRE("test" != string_dynamic("string"));
    }

    SECTION("!(char* != string_dynamic)")
    {
        REQUIRE(!("test" != string_dynamic("test")));
    }

    SECTION("string_dynamic != string")
    {
        REQUIRE(string_dynamic("test") != string_dynamic("string"));
    }

    SECTION("!(string_dynamic != string)")
    {
        REQUIRE(!(string_dynamic("test") != string_dynamic("test")));
    }
}

TEST_CASE("string_dynamic.operator<", "[gg.string_dynamic]")
{
    SECTION("string_dynamic < char*")
    {
        REQUIRE(string_dynamic("test_a") < "test_b");
    }

    SECTION("!(string_dynamic < char*)")
    {
        REQUIRE(!(string_dynamic("test_b") < "test_a"));
    }

    SECTION("char* < string_dynamic")
    {
        REQUIRE("test_a" < string_dynamic("test_b"));
    }

    SECTION("!(char* < string_dynamic)")
    {
        REQUIRE(!("test_b" < string_dynamic("test_a")));
    }

    SECTION("string_dynamic < string")
    {
        REQUIRE(string_dynamic("test_a") < string_dynamic("test_b"));
    }

    SECTION("!(string_dynamic < string)")
    {
        REQUIRE(!(string_dynamic("test_b") < string_dynamic("test_a")));
    }
}

TEST_CASE("string_dynamic.operator>", "[gg.string_dynamic]")
{
    SECTION("string_dynamic > char*")
    {
        REQUIRE(string_dynamic("test_b") > "test_a");
    }

    SECTION("!(string_dynamic > char*)")
    {
        REQUIRE(!(string_dynamic("test_a") > "test_b"));
    }

    SECTION("char* > string_dynamic")
    {
        REQUIRE("test_b" > string_dynamic("test_a"));
    }

    SECTION("!(char* > string_dynamic)")
    {
        REQUIRE(!("test_a" > string_dynamic("test_b")));
    }

    SECTION("string_dynamic > string")
    {
        REQUIRE(string_dynamic("test_b") > string_dynamic("test_a"));
    }

    SECTION("!(string_dynamic > string)")
    {
        REQUIRE(!(string_dynamic("test_a") > string_dynamic("test_b")));
    }
}

TEST_CASE("string_dynamic.append", "[gg.string_dynamic]")
{
    SECTION("append char")
    {
        string_dynamic string("this is a test string");
        string.append('!');
        REQUIRE(string == "this is a test string!");
        REQUIRE(string.size() + 1 == string.max_size());
    }

    SECTION("append char*")
    {
        string_dynamic string("this is a test string");
        string.append(" with an appended string");
        REQUIRE(string == "this is a test string with an appended string");
        REQUIRE(string.size() + 1 == string.max_size());
    }

    SECTION("append string")
    {
        string_dynamic string("this is a test string");
        string.append(string_dynamic(" with an appended string"));
        REQUIRE(string == "this is a test string with an appended string");
        REQUIRE(string.size() + 1 == string.max_size());
    }

    SECTION("append char* size")
    {
        string_dynamic string("this is a test string");
        string.append(" with an appended string", 16);
        REQUIRE(string == "this is a test string with an appende");
        REQUIRE(string.size() + 1 == string.max_size());
    }

    SECTION("append char* idx_start idx_end")
    {
        string_dynamic string("this is a test string");
        string.append(" with an appended string", 8, 20);
        REQUIRE(string == "this is a test string appended str");
        REQUIRE(string.size() + 1 == string.max_size());
    }

    SECTION("append string size")
    {
        string_dynamic string("this is a test string");
        string.append(string_dynamic(" with an appended string"), 16);
        REQUIRE(string == "this is a test string with an appende");
        REQUIRE(string.size() + 1 == string.max_size());
    }
}

TEST_CASE("string_dynamic.begin", "[gg.string_dynamic]")
{
    SECTION("begin")
    {
        string_dynamic string("this is a test string");
        REQUIRE(*string.begin() == 't');
    }
}

TEST_CASE("string_dynamic.clear", "[gg.string_dynamic]")
{
    SECTION("clear")
    {
        string_dynamic string("this is a test string");
        REQUIRE(string.max_size() == 22);
        REQUIRE(string.size() == 21);
        REQUIRE(!string.is_empty());

        string.clear();
        REQUIRE(string.max_size() == 22);
        REQUIRE(string.size() == 0);
        REQUIRE(string.is_empty());
    }
}

TEST_CASE("string_dynamic.end", "[gg.string_dynamic]")
{
    SECTION("end")
    {
        string_dynamic string("this is a test string");
        REQUIRE(*(string.end() - 1) == 'g');
    }
}

TEST_CASE("string_dynamic.erase", "[gg.string_dynamic]")
{
    SECTION("erase idx size - first character")
    {
        string_dynamic string("this is a test string");
        string.erase(0);
        REQUIRE(string == "his is a test string");
        REQUIRE(string.max_size() == 22);
        REQUIRE(string.size() == 20);
    }

    SECTION("erase idx size - last character")
    {
        string_dynamic string("this is a test string");
        string.erase(20);
        REQUIRE(string == "this is a test strin");
        REQUIRE(string.max_size() == 22);
        REQUIRE(string.size() == 20);
    }

    SECTION("erase idx size - string in the middle")
    {
        string_dynamic string("this is a test string");
        string.erase(4, 3);
        REQUIRE(string == "this a test string");
        REQUIRE(string.max_size() == 22);
        REQUIRE(string.size() == 18);
    }

    SECTION("erase idx size - overflow")
    {
        string_dynamic string("this is a test string");
        string.erase(7, 128);
        REQUIRE(string == "this is");
        REQUIRE(string.max_size() == 22);
        REQUIRE(string.size() == 7);
    }
}

TEST_CASE("string_dynamic.find", "[gg.string_dynamic]")
{
    // SECTION("find empty")
    // {
    //     string_dynamic string;
    //     REQUIRE(string.find("is") == string::npos);
    // }

    SECTION("find char*")
    {
        string_dynamic string("this is a test string");
        REQUIRE(string.find("is") == 2);
    }

    SECTION("!(find char*)")
    {
        string_dynamic string("this is a test string");
        REQUIRE(string.find("ddfv") == string::npos);
    }

    SECTION("find char* idx")
    {
        string_dynamic string("this is a test string");
        REQUIRE(string.find("is", 3) == 5);
    }

    SECTION("find string")
    {
        string_dynamic string("this is a test string");
        string_dynamic pattern("ng");
        REQUIRE(string.find(pattern) == 19);
    }

    SECTION("!(find string)")
    {
        string_dynamic string("this is a test string");
        string_dynamic pattern("b");
        REQUIRE(string.find(pattern) == string::npos);
    }

    SECTION("find string idx")
    {
        string_dynamic string("this is a test string");
        string_dynamic pattern("t");
        REQUIRE(string.find(pattern, 10) == 10);
    }
}

TEST_CASE("string_dynamic.insert", "[gg.string_dynamic]")
{
    SECTION("insert idx char - first character")
    {
        string_dynamic string("this is a test string");
        string.insert(0, '!');
        REQUIRE(string == "!this is a test string");
        REQUIRE(string.size() + 1 == string.max_size());
    }

    SECTION("insert idx char - character in the middle")
    {
        string_dynamic string("this is a test string");
        string.insert(5, '!');
        REQUIRE(string == "this !is a test string");
        REQUIRE(string.size() + 1 == string.max_size());
    }

    SECTION("insert idx char*")
    {
        string_dynamic string("this is a test string");
        string.insert(10, " with an appended string ");
        REQUIRE(string == "this is a  with an appended string test string");
        REQUIRE(string.size() + 1 == string.max_size());
    }

    SECTION("insert idx string")
    {
        string_dynamic string("this is a test string");
        string.insert(10, string_dynamic(" with an appended string "));
        REQUIRE(string == "this is a  with an appended string test string");
        REQUIRE(string.size() + 1 == string.max_size());
    }

    SECTION("insert idx char* size")
    {
        string_dynamic string("this is a test string");
        string.insert(10, " with an appended string ", 16);
        REQUIRE(string == "this is a  with an appendetest string");
        REQUIRE(string.size() + 1 == string.max_size());
    }

    SECTION("insert idx string size")
    {
        string_dynamic string("this is a test string");
        string.insert(10, string_dynamic(" with an appended string "), 16);
        REQUIRE(string == "this is a  with an appendetest string");
        REQUIRE(string.size() + 1 == string.max_size());
    }
}

TEST_CASE("string_dynamic.set", "[gg.string_dynamic]")
{
    SECTION("set char*")
    {
        string_dynamic string;
        string.set("this is a test string");
        REQUIRE(string == "this is a test string");
        REQUIRE(string.size() + 1 == string.max_size());
    }

    SECTION("set char* size")
    {
        string_dynamic string;
        string.set("this is a test string", 16);
        REQUIRE(string == "this is a test s");
        REQUIRE(string.size() + 1 == string.max_size());
    }

    SECTION("set char* idx_start idx_end")
    {
        string_dynamic string;
        string.set("this is a test string", 4, 16);
        REQUIRE(string == " is a test st");
        REQUIRE(string.size() + 1 == string.max_size());
    }

    SECTION("set string_dynamic")
    {
        string_dynamic string;
        string.set(string_dynamic("this is a test string"));
        REQUIRE(string == "this is a test string");
        REQUIRE(string.size() + 1 == string.max_size());
    }

    SECTION("set rvalue_string_dynamic")
    {
        string_dynamic string;
        string_dynamic moved_string("this is a test string");
        string.set(type::move(moved_string));
        REQUIRE((string == "this is a test string"));
        REQUIRE(string.size() + 1 == string.max_size());

        REQUIRE(moved_string.begin() == nullptr);
        REQUIRE(moved_string.begin() == moved_string.end());
        REQUIRE(moved_string.max_size() == 0);
        REQUIRE(moved_string.size() == 0);
        REQUIRE(moved_string.is_empty());
    }

    SECTION("set string")
    {
        string_dynamic string;
        string.set(string_ref("this is a test string"));
        REQUIRE(string == "this is a test string");
        REQUIRE(string.size() + 1 == string.max_size());
    }

    SECTION("set string size")
    {
        string_dynamic string;
        string.set(string_ref("this is a test string"), 16);
        REQUIRE(string == "this is a test s");
        REQUIRE(string.size() + 1 == string.max_size());
    }

    SECTION("set string idx_start idx_end")
    {
        string_dynamic string;
        string.set(string_ref("this is a test string"), 4, 16);
        REQUIRE(string == " is a test st");
        REQUIRE(string.size() + 1 == string.max_size());
    }
}

TEST_CASE("string_dynamic.reserve", "[gg.string_dynamic]")
{
    SECTION("reserve")
    {
        string_dynamic string;
        string.reserve(32);
        REQUIRE(string.max_size() == 32);
    }
}

TEST_CASE("string_dynamic.resize", "[gg.string_dynamic]")
{
    SECTION("resize shrink")
    {
        string_dynamic string("this is a test string");
        REQUIRE(string.max_size() == 22);
        REQUIRE(string.size() == 21);

        string.resize(12);
        REQUIRE(string.max_size() == 22);
        REQUIRE(string.size() == 12);
    }
}

TEST_CASE("string_dynamic.max_size", "[gg.string_dynamic]")
{
    SECTION("max_size")
    {
        string_dynamic string;
        REQUIRE(string.max_size() == 1);
    }
}

TEST_CASE("string_dynamic.size", "[gg.string_dynamic]")
{
    SECTION("size")
    {
        string_dynamic string("test");
        REQUIRE(string.size() == 4);
    }
}

TEST_CASE("string_dynamic.trim", "[gg.string]")
{
    SECTION("trim")
    {
        string_dynamic text(
            GG_TEXT(
                "\r Lorem ipsum dolor sit amet, consectetur adipiscing elit,\r\n"
                " \tsed do eiusmod tempor incididunt ut labore et dolore magna \n"
                " aliqua. \t\n\r"));
        REQUIRE(text.size() == 134);
        REQUIRE(text.trim() == 128);
        REQUIRE(text.size() == 128);
        REQUIRE(
            text ==
            GG_TEXT(
                "Lorem ipsum dolor sit amet, consectetur adipiscing elit,\r\n"
                " \tsed do eiusmod tempor incididunt ut labore et dolore magna \n"
                " aliqua."));
    }

    SECTION("trim custom delims")
    {
        string_dynamic text(
            GG_TEXT(
                "a b c Lorem ipsum dolor sit amet, consectetur adipiscing elit,\r\n"
                " \tsed do eiusmod tempor incididunt ut labore et dolore magna \n"
                " aliqua. \t\n\r a c b"));

        REQUIRE(text.size() == 144);
        REQUIRE(text.trim(GG_TEXT(" abc")) == 132);
        REQUIRE(text.size() == 132);
        REQUIRE(
            text ==
            GG_TEXT(
                "Lorem ipsum dolor sit amet, consectetur adipiscing elit,\r\n"
                " \tsed do eiusmod tempor incididunt ut labore et dolore magna \n"
                " aliqua. \t\n\r"));
    }
}

TEST_CASE("string_dynamic.is_empty", "[gg.string_dynamic]")
{
    SECTION("is_empty")
    {
        string_dynamic string;
        REQUIRE(string.is_empty());
    }

    SECTION("!(is_empty)")
    {
        string_dynamic string("test");
        REQUIRE(!string.is_empty());
    }
}

//==============================================================================

TEST_CASE("string_dynamic::compare", "[gg.string]")
{
    SECTION("compare")
    {
        string_dynamic text(
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

TEST_CASE("string_dynamic::find", "[gg.string]")
{
    SECTION("find")
    {
        string_dynamic text(
            GG_TEXT(
                "Lorem ipsum dolor sit amet, "
                "consectetur adipiscing elit,\r\n"));
        REQUIRE(
            (string::find(
                text.c_str(), GG_TEXT("consectetur")) -
            text.c_str()) == 28);
    }
}

TEST_CASE("string_dynamic::length", "[gg.string]")
{
    SECTION("length")
    {
        string_dynamic text(
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
