#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/string/type/string_ref.h"
#include "gg/core/string/type/string_static.h"

//==============================================================================
namespace gg::string_static_test
{
//==============================================================================

TEST_CASE("string_static", "[gg.string_static]")
{
    SECTION("assign")
    {
        REQUIRE(type::is_copy_assignable<string_static<>>::value);
        REQUIRE(!type::is_trivially_assignable<string_static<>>::value);
        REQUIRE(type::is_copy_assignable<string_static<>>::value);
        REQUIRE(!type::is_trivially_assignable<string_static<>>::value);
    }

    SECTION("construct")
    {
        REQUIRE(type::is_constructible<string_static<>>::value);
        REQUIRE(!type::is_trivially_constructible<string_static<>>::value);
        REQUIRE(!type::is_trivially_constructible<string_static<>>::value);
    }

    SECTION("copy")
    {
        REQUIRE(type::is_copy_constructible<string_static<>>::value);
        REQUIRE(!type::is_trivially_copy_constructible<string_static<>>::value);
        REQUIRE(type::is_copy_constructible<string_static<>>::value);
        REQUIRE(!type::is_trivially_copy_constructible<string_static<>>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(type::is_destructible<string_static<>>::value);
        REQUIRE(!type::is_trivially_destructible<string_static<>>::value);
        REQUIRE(!type::is_trivially_destructible<string_static<>>::value);
    }

    SECTION("compare")
    {
        // @todo fix this
        // REQUIRE(type::is_comparable<string_static<>>::value);
    }

    SECTION("pod")
    {
        REQUIRE(!type::is_pod<string_static<>>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<string_static<>>::value);
    }

    SECTION("sizeof")
    {
        REQUIRE(sizeof(string_static<>) == 8);
        REQUIRE(sizeof(string_static<16>) == 16);
        REQUIRE(sizeof(string_static<32>) == 32);
        REQUIRE(sizeof(string_static<128>) == 128);
        REQUIRE(sizeof(string_static<256>) == 256);
    }
}

TEST_CASE("string_static.constructor", "[gg.string_static]")
{
    SECTION("string_static")
    {
        string_static<> string;
        REQUIRE(string.begin() == string.end());
        REQUIRE(string.max_size() == 8);
        REQUIRE(string.size() == 0);
        REQUIRE(string.is_empty());
    }

    SECTION("string_static(char)")
    {
        string_static<> string('a');
        REQUIRE(string == "a");
        REQUIRE(string.max_size() == 8);
        REQUIRE(string.size() == 1);
        REQUIRE(!string.is_empty());
    }

    SECTION("string_static(char*)")
    {
        string_static<> string("test");
        REQUIRE(string == "test");
        REQUIRE(string.size() == 4);
    }

    SECTION("string_static(char*, size)")
    {
        string_static<32> string("this is a test string", 16);
        REQUIRE(string == "this is a test s");
        REQUIRE(string.size() == 16);
    }

    SECTION("string_static(char*, idx_start, idx_end)")
    {
        string_static<32> string("this is a test string", 4, 16);
        REQUIRE(string == " is a test st");
        REQUIRE(string.size() == 13);
    }

    SECTION("string_static(string_static)")
    {
        string_static<> copied_string("test");
        string_static<> string(copied_string);
        REQUIRE(string == copied_string);
        REQUIRE(string.size() == 4);
    }

    SECTION("string_static(string_static, size)")
    {
        string_static<32> copied_string("this is a test string");
        string_static<32> string(copied_string, 16);
        REQUIRE(string == "this is a test s");
        REQUIRE(string.size() == 16);
    }

    SECTION("string_static(string_static, idx_start, idx_end)")
    {
        string_static<32> copied_string("this is a test string");
        string_static<32> string(copied_string, 4, 16);
        REQUIRE(string == " is a test st");
        REQUIRE(string.size() == 13);
    }

    SECTION("string_static(string)")
    {
        string_ref copied_string("test");
        string_static<> string(copied_string);
        REQUIRE(string == copied_string);
        REQUIRE(string.size() == 4);
    }

    SECTION("string_static(string, size)")
    {
        string_ref copied_string("this is a test string");
        string_static<32> string(copied_string, 16);
        REQUIRE(string == "this is a test s");
        REQUIRE(string.size() == 16);
    }

    SECTION("string_static(string, idx_start, idx_end)")
    {
        string_ref copied_string("this is a test string");
        string_static<32> string(copied_string, 4, 16);
        REQUIRE(string == " is a test st");
        REQUIRE(string.size() == 13);
    }
}

TEST_CASE("string_static.operator-access", "[gg.string_static]")
{
    SECTION("operator[idx]")
    {
        string_static<> string("test");

        REQUIRE(string[0] == 't');
        REQUIRE(string[1] == 'e');
        REQUIRE(string[2] == 's');
        REQUIRE(string[3] == 't');
    }
}

TEST_CASE("string_static.operator=", "[gg.string_static]")
{
    SECTION("string_static = char*")
    {
        string_static<> string;
        string = "test";
        REQUIRE(string == "test");
    }

    SECTION("string_static = string_static")
    {
        string_static<> string;
        string = string_static<>("test");
        REQUIRE(string == "test");
    }

    SECTION("string_static = string")
    {
        string_static<> string;
        string = string_ref("test");
        REQUIRE(string == "test");
    }
}

TEST_CASE("string_static.operator==", "[gg.string_static]")
{
    SECTION("string_static == char*")
    {
        REQUIRE(string_static<>("test") == "test");
    }

    SECTION("!(string_static == char*)")
    {
        REQUIRE(!(string_static<>("test") == "string"));
    }

    SECTION("char* == string_static")
    {
        REQUIRE("test" == string_static<>("test"));
    }

    SECTION("!(char* == string_static)")
    {
        REQUIRE(!("test" == string_static<>("string")));
    }

    SECTION("string_static == string")
    {
        REQUIRE(string_static<>("test") == string_static<>("test"));
    }

    SECTION("!(string_static == string)")
    {
        REQUIRE(!(string_static<>("test") == string_static<>("string")));
    }
}

TEST_CASE("string_static.operator!=", "[gg.string_static]")
{
    SECTION("string_static != char*")
    {
        REQUIRE(string_static<>("test") != "string");
    }

    SECTION("!(string_static != char*)")
    {
        REQUIRE(!(string_static<>("test") != "test"));
    }

    SECTION("char* != string_static")
    {
        REQUIRE("test" != string_static<>("string"));
    }

    SECTION("!(char* != string_static)")
    {
        REQUIRE(!("test" != string_static<>("test")));
    }

    SECTION("string_static != string")
    {
        REQUIRE(string_static<>("test") != string_static<>("string"));
    }

    SECTION("!(string_static != string)")
    {
        REQUIRE(!(string_static<>("test") != string_static<>("test")));
    }
}

TEST_CASE("string_static.operator<", "[gg.string_static]")
{
    SECTION("string_static < char*")
    {
        REQUIRE(string_static<>("test_a") < "test_b");
    }

    SECTION("!(string_static < char*)")
    {
        REQUIRE(!(string_static<>("test_b") < "test_a"));
    }

    SECTION("char* < string_static")
    {
        REQUIRE("test_a" < string_static<>("test_b"));
    }

    SECTION("!(char* < string_static)")
    {
        REQUIRE(!("test_b" < string_static<>("test_a")));
    }

    SECTION("string_static < string")
    {
        REQUIRE(string_static<>("test_a") < string_static<>("test_b"));
    }

    SECTION("!(string_static < string)")
    {
        REQUIRE(!(string_static<>("test_b") < string_static<>("test_a")));
    }
}

TEST_CASE("string_static.operator>", "[gg.string_static]")
{
    SECTION("string_static > char*")
    {
        REQUIRE(string_static<>("test_b") > "test_a");
    }

    SECTION("!(string_static > char*)")
    {
        REQUIRE(!(string_static<>("test_a") > "test_b"));
    }

    SECTION("char* > string_static")
    {
        REQUIRE("test_b" > string_static<>("test_a"));
    }

    SECTION("!(char* > string_static)")
    {
        REQUIRE(!("test_a" > string_static<>("test_b")));
    }

    SECTION("string_static > string")
    {
        REQUIRE(string_static<>("test_b") > string_static<>("test_a"));
    }

    SECTION("!(string_static > string)")
    {
        REQUIRE(!(string_static<>("test_a") > string_static<>("test_b")));
    }
}

TEST_CASE("string_static.append", "[gg.string_static]")
{
    SECTION("append char")
    {
        string_static<32> string("this is a test string");
        string.append('!');
        REQUIRE(string == "this is a test string!");
    }

    SECTION("append char - overflow")
    {
        string_static<22> string("this is a test string");
        string.append('!');
        REQUIRE(string == "this is a test string");
    }

    SECTION("append char*")
    {
        string_static<64> string("this is a test string");
        string.append(" with an appended string");
        REQUIRE(string == "this is a test string with an appended string");
    }

    SECTION("append char* - overflow")
    {
        string_static<32> string("this is a test string");
        string.append(" with an appended string");
        REQUIRE(string == "this is a test string with an a");
    }

    SECTION("append string")
    {
        string_static<64> string("this is a test string");
        string.append(string_static<32>(" with an appended string"));
        REQUIRE(string == "this is a test string with an appended string");
    }

    SECTION("append string - overflow")
    {
        string_static<24> string("this is a test string");
        string.append(string_static<32>(" with an appended string"));
        REQUIRE(string == "this is a test string w");
    }

    SECTION("append char* size")
    {
        string_static<64> string("this is a test string");
        string.append(" with an appended string", 16);
        REQUIRE(string == "this is a test string with an appende");
    }

    SECTION("append char* size - overflow")
    {
        string_static<32> string("this is a test string");
        string.append(" with an appended string", 16);
        REQUIRE(string == "this is a test string with an a");
    }

    SECTION("append char* idx_start idx_end")
    {
        string_static<64> string("this is a test string");
        string.append(" with an appended string", 8, 20);
        REQUIRE(string == "this is a test string appended str");
    }

    SECTION("append char* idx_start idx_end - overflow")
    {
        string_static<32> string("this is a test string");
        string.append(" with an appended string", 8, 20);
        REQUIRE(string == "this is a test string appended ");
    }

    SECTION("append string size")
    {
        string_static<64> string("this is a test string");
        string.append(string_static<32>(" with an appended string"), 16);
        REQUIRE(string == "this is a test string with an appende");
    }

    SECTION("append string size - overflow")
    {
        string_static<24> string("this is a test string");
        string.append(string_static<32>(" with an appended string"), 16);
        REQUIRE(string == "this is a test string w");
    }
}

TEST_CASE("string_static.begin", "[gg.string_static]")
{
    SECTION("begin")
    {
        string_static<32> string("this is a test string");
        REQUIRE(*string.begin() == 't');
    }
}

TEST_CASE("string_static.clear", "[gg.string_static]")
{
    SECTION("clear")
    {
        string_static<32> string("this is a test string");
        REQUIRE(!string.is_empty());

        string.clear();
        REQUIRE(string.is_empty());
    }
}

TEST_CASE("string_static.end", "[gg.string_static]")
{
    SECTION("end")
    {
        string_static<32> string("this is a test string");
        REQUIRE(*(string.end() - 1) == 'g');
    }
}

TEST_CASE("string_static.erase", "[gg.string_static]")
{
    SECTION("erase idx size - first character")
    {
        string_static<32> string("this is a test string");
        string.erase(0, 1);
        REQUIRE(string == "his is a test string");
    }

    SECTION("erase idx size - last character")
    {
        string_static<32> string("this is a test string");
        string.erase(20, 1);
        REQUIRE(string == "this is a test strin");
    }

    SECTION("erase idx size - string in the middle")
    {
        string_static<32> string("this is a test string");
        string.erase(4, 3);
        REQUIRE(string == "this a test string");
    }

    SECTION("erase idx size - overflow")
    {
        string_static<32> string("this is a test string");
        string.erase(7, 128);
        REQUIRE(string == "this is");
    }
}

TEST_CASE("string_static.find", "[gg.string_static]")
{
    SECTION("find char*")
    {
        string_static<32> string("this is a test string");
        REQUIRE(string.find("is") == 2);
    }

    SECTION("!(find char*)")
    {
        string_static<32> string("this is a test string");
        REQUIRE(string.find("ddfv") == string::npos);
    }

    SECTION("find char* idx")
    {
        string_static<32> string("this is a test string");
        REQUIRE(string.find("is", 3) == 5);
    }

    SECTION("find string")
    {
        string_static<32> string("this is a test string");
        string_static<32> pattern("ng");
        REQUIRE(string.find(pattern) == 19);
    }

    SECTION("!(find string)")
    {
        string_static<16> string("this is a test string");
        string_static<> pattern("b");
        REQUIRE(string.find(pattern) == string::npos);
    }

    SECTION("find string idx")
    {
        string_static<16> string("this is a test string");
        string_static<> pattern("t");
        REQUIRE(string.find(pattern, 10) == 10);
    }
}

TEST_CASE("string_static.insert", "[gg.string_static]")
{
    SECTION("insert idx char - first character")
    {
        string_static<32> string("this is a test string");
        string.insert(0, '!');
        REQUIRE(string == "!this is a test string");
    }

    SECTION("insert idx char - character in the middle")
    {
        string_static<32> string("this is a test string");
        string.insert(5, '!');
        REQUIRE(string == "this !is a test string");
    }

    SECTION("insert idx char - overflow")
    {
        string_static<22> string("this is a test string");
        string.insert(5, '!');
        REQUIRE(string == "this !is a test strin");
    }

    SECTION("insert idx char*")
    {
        string_static<64> string("this is a test string");
        string.insert(10, " with an appended string ");
        REQUIRE(string == "this is a  with an appended string test string");
    }

    SECTION("insert idx char* - overflow")
    {
        string_static<32> string("this is a test string");
        string.insert(10, " with an appended string ");
        REQUIRE(string == "this is a  with an appended str");
    }

    SECTION("insert idx string")
    {
        string_static<64> string("this is a test string");
        string.insert(10, string_static<32>(" with an appended string "));
        REQUIRE(string == "this is a  with an appended string test string");
    }

    SECTION("insert idx string - overflow")
    {
        string_static<32> string("this is a test string");
        string.insert(10, string_static<32>(" with an appended string "));
        REQUIRE(string == "this is a  with an appended str");
    }

    SECTION("insert idx char* size")
    {
        string_static<64> string("this is a test string");
        string.insert(10, " with an appended string ", 16);
        REQUIRE(string == "this is a  with an appendetest string");
    }

    SECTION("insert idx char* size - overflow")
    {
        string_static<32> string("this is a test string");
        string.insert(10, " with an appended string ", 16);
        REQUIRE(string == "this is a  with an appendetest ");
    }

    SECTION("insert idx string size")
    {
        string_static<64> string("this is a test string");
        string.insert(10, string_static<32>(" with an appended string "), 16);
        REQUIRE(string == "this is a  with an appendetest string");
    }

    SECTION("insert idx string size - overflow")
    {
        string_static<32> string("this is a test string");
        string.insert(10, string_static<32>(" with an appended string "), 16);
        REQUIRE(string == "this is a  with an appendetest ");
    }
}

TEST_CASE("string_static.set", "[gg.string_static]")
{
    SECTION("set char*")
    {
        string_static<32> string;
        string.set("this is a test string");
        REQUIRE(string == "this is a test string");
    }

    SECTION("set char* - overflow")
    {
        string_static<16> string;
        string.set("this is a test string");
        REQUIRE(string == "this is a test ");
    }

    SECTION("set char* size")
    {
        string_static<32> string;
        string.set("this is a test string", 16);
        REQUIRE(string == "this is a test s");
    }

    SECTION("set char* size - overflow")
    {
        string_static<12> string;
        string.set("this is a test string", 16);
        REQUIRE(string == "this is a t");
    }

    SECTION("set char* start end")
    {
        string_static<32> string;
        string.set("this is a test string", 4, 16);
        REQUIRE(string == " is a test st");
    }

    SECTION("set char* start end - overflow")
    {
        string_static<12> string;
        string.set("this is a test string", 4, 16);
        REQUIRE(string == " is a test ");
    }

    SECTION("set string_static")
    {
        string_static<32> string;
        string.set(string_static<32>("this is a test string"));
        REQUIRE(string == "this is a test string");
    }

    SECTION("set string")
    {
        string_static<32> string;
        string.set(string_ref("this is a test string"));
        REQUIRE(string == "this is a test string");
    }

    SECTION("set string - overflow")
    {
        string_static<16> string;
        string.set(string_ref("this is a test string"));
        REQUIRE(string == "this is a test ");
    }

    SECTION("set string size")
    {
        string_static<32> string;
        string.set(string_ref("this is a test string"), 16);
        REQUIRE(string == "this is a test s");
    }

    SECTION("set string size - overflow")
    {
        string_static<12> string;
        string.set(string_ref("this is a test string"), 16);
        REQUIRE(string == "this is a t");
    }

    SECTION("set string start end")
    {
        string_static<32> string;
        string.set(string_ref("this is a test string"), 4, 16);
        REQUIRE(string == " is a test st");
    }

    SECTION("set string start end - overflow")
    {
        string_static<12> string;
        string.set(string_ref("this is a test string"), 4, 16);
        REQUIRE(string == " is a test ");
    }
}

TEST_CASE("string_static.max_size", "[gg.string_static]")
{
    SECTION("max_size")
    {
        string_static<16> string;
        REQUIRE(string.max_size() == 16);
    }
}

TEST_CASE("string_static.size", "[gg.string_static]")
{
    SECTION("size")
    {
        string_static<> string("test");
        REQUIRE(string.size() == 4);
    }
}

TEST_CASE("string_static.trim", "[gg.string]")
{
    SECTION("trim")
    {
        string_static<256> text(
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
        string_static<256> text(
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

TEST_CASE("string_static.is_empty", "[gg.string_static]")
{
    SECTION("is_empty")
    {
        string_static<> string;
        REQUIRE(string.is_empty());
    }

    SECTION("!(is_empty)")
    {
        string_static<> string("test");
        REQUIRE(!string.is_empty());
    }
}

//==============================================================================

TEST_CASE("string_static::compare", "[gg.string]")
{
    SECTION("compare")
    {
        string_static<256> text(
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

TEST_CASE("string_static::find", "[gg.string]")
{
    SECTION("find")
    {
        string_static<256> text(
            GG_TEXT(
                "Lorem ipsum dolor sit amet, "
                "consectetur adipiscing elit,\r\n"));
        REQUIRE(
            (string::find(
                text.c_str(), GG_TEXT("consectetur")) -
            text.c_str()) == 28);
    }
}

TEST_CASE("string_static::length", "[gg.string]")
{
    SECTION("length")
    {
        string_static<256> text(
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
