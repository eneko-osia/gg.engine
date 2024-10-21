#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/string/type/string.h"

//==============================================================================
namespace gg::string_test
{
//==============================================================================

TEST_CASE("string.compare", "[gg.string]")
{
    SECTION("compare")
    {
        char8 text[] =
            GG_TEXT(
                "Lorem ipsum dolor sit amet, "
                "consectetur adipiscing elit,\r\n");
        REQUIRE(
            string::compare(
                text,
                "Lorem ipsum dolor sit amet, consectetur "
                "adipiscing elit,\r\n") == 0);
    }
}

TEST_CASE("string.find", "[gg.string]")
{
    SECTION("find")
    {
        char8 text[] =
            GG_TEXT(
                "Lorem ipsum dolor sit amet, "
                "consectetur adipiscing elit,\r\n");
        REQUIRE((string::find(text, GG_TEXT("consectetur")) - text) == 28);
    }
}

TEST_CASE("string.format", "[gg.version]")
{
    SECTION("format")
    {
        char8 text[256];
        string::format(text, 256,
            "Lorem ipsum dolor sit amet, %s",
            "consectetur adipiscing elit,\r\n");
        REQUIRE(
            string::compare(
                text,
                "Lorem ipsum dolor sit amet, consectetur "
                "adipiscing elit,\r\n") == 0);
    }
}

TEST_CASE("string.from", "[gg.version]")
{
    SECTION("from<bool8>")
    {
        char8 text[256];
        string::from(true, text, 256);
        REQUIRE(string::compare(text, "1") == 0);
    }

    SECTION("from<int32>")
    {
        char8 text[256];
        string::from<int32>(2, text, 256);
        REQUIRE(string::compare(text, "2") == 0);
    }

    SECTION("from<uint32>")
    {
        char8 text[256];
        string::from<uint32>(4, text, 256);
        REQUIRE(string::compare(text, "4") == 0);
    }

    SECTION("from<int64>")
    {
        char8 text[256];
        string::from<int64>(8, text, 256);
        REQUIRE(string::compare(text, "8") == 0);
    }

    SECTION("from<float32>")
    {
        char8 text[256];
        string::from<float32>(3.14f, text, 256);
        REQUIRE(string::compare(text, "3.140000") == 0);
    }
}

TEST_CASE("string.length", "[gg.string]")
{
    SECTION("length")
    {
        char8 text[] =
            GG_TEXT(
                "Lorem ipsum dolor sit amet, "
                "consectetur adipiscing elit,\r\n");
        REQUIRE(string::length(text) == 58);
    }
}

TEST_CASE("string.trim", "[gg.string]")
{
    SECTION("trim")
    {
        char8 text[] =
            GG_TEXT(
                "\r Lorem ipsum dolor sit amet, consectetur adipiscing elit,\r\n"
                " \tsed do eiusmod tempor incididunt ut labore et dolore magna \n"
                " aliqua. \t\n\r");
        REQUIRE(string::length(text) == 134);
        REQUIRE(string::trim(text, string::length(text)) == 128);
        REQUIRE(string::length(text) == 128);
        REQUIRE(
            string::compare(
                text,
                GG_TEXT(
                    "Lorem ipsum dolor sit amet, consectetur adipiscing elit,\r\n"
                    " \tsed do eiusmod tempor incididunt ut labore et dolore magna \n"
                    " aliqua.")) == 0);
    }

    SECTION("trim custom delims")
    {
        char8 text[] =
            GG_TEXT(
                "a b c Lorem ipsum dolor sit amet, consectetur adipiscing elit,\r\n"
                " \tsed do eiusmod tempor incididunt ut labore et dolore magna \n"
                " aliqua. \t\n\r a c b");
        REQUIRE(string::length(text) == 144);
        REQUIRE(string::trim(text, string::length(text), GG_TEXT(" abc")) == 132);
        REQUIRE(string::length(text) == 132);
        REQUIRE(
            string::compare(
                text,
                GG_TEXT(
                    "Lorem ipsum dolor sit amet, consectetur adipiscing elit,\r\n"
                    " \tsed do eiusmod tempor incididunt ut labore et dolore magna \n"
                    " aliqua. \t\n\r")) == 0);
    }
}

//==============================================================================
}
//==============================================================================
