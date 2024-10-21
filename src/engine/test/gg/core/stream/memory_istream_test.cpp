#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/stream/memory_istream.h"
#include "gg/core/string/type/string_static.h"

//==============================================================================
namespace gg::memory_istream_test
{
//==============================================================================

TEST_CASE("memory_istream", "[gg.memory_istream]")
{
    SECTION("assign")
    {
        REQUIRE(!type::is_copy_assignable<memory_istream>::value);
        REQUIRE(!type::is_trivially_assignable<memory_istream>::value);
    }

    SECTION("construct")
    {
        REQUIRE(!type::is_constructible<memory_istream>::value);
        REQUIRE(!type::is_trivially_constructible<memory_istream>::value);
    }

    SECTION("copy")
    {
        REQUIRE(!type::is_copy_constructible<memory_istream>::value);
        REQUIRE(!type::is_trivially_copy_constructible<memory_istream>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(type::is_destructible<memory_istream>::value);
        REQUIRE(type::is_trivially_destructible<memory_istream>::value);
    }

    SECTION("compare")
    {
        REQUIRE(!type::is_comparable<memory_istream>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<memory_istream>::value);
    }
}

TEST_CASE("memory_istream.constructor", "[gg.memory_istream]")
{
    SECTION("memory_istream(buffer)")
    {
        char8 data[16];
        memory::copy(data, "This is a buffer", sizeof(data));
        memory_buffer_ref buffer((byte *) (data), sizeof(data));
        memory_istream stream(buffer);
        REQUIRE(stream.is_valid());
        REQUIRE(stream.get_position() == 0);
        REQUIRE(stream.size() == sizeof(data));
    }

    SECTION("memory_istream(invalid buffer)")
    {
        memory_buffer_ref buffer;
        memory_istream stream(buffer);
        REQUIRE(!stream.is_valid());
        REQUIRE(stream.get_position() == 0);
        REQUIRE(stream.size() == 0);
    }
}

TEST_CASE("memory_istream.move", "[gg.memory_istream]")
{
    SECTION("move")
    {
        char8 data[16];
        memory::copy(data, "This is a buffer", sizeof(data));
        memory_buffer_ref buffer((byte *) (data), sizeof(data));
        memory_istream stream(buffer);
        REQUIRE(stream.move(10));
        REQUIRE(stream.get_position() == 10);
        REQUIRE(stream.size() == sizeof(data));
    }
}

TEST_CASE("memory_istream.read", "[gg.memory_istream]")
{
    SECTION("read")
    {
        char8 data[16];
        memory::copy(data, "This is a buffer", sizeof(data));
        memory_buffer_ref buffer((byte *) (data), sizeof(data));
        memory_istream stream(buffer);

        char8 character = '\0';
        REQUIRE(sizeof(char8) == stream.read(character));
        REQUIRE(character == 'T');
        REQUIRE(stream.get_position() == sizeof(char8));
        REQUIRE(stream.size() == sizeof(data));
    }
}

TEST_CASE("memory_istream.read_line", "[gg.memory_istream]")
{
    SECTION("read_line - one line")
    {
        char8 data[16];
        memory::copy(data, "This is a buffer", sizeof(data));
        memory_buffer_ref buffer((byte *) (data), sizeof(data));
        memory_istream stream(buffer);

        string_static<32> line;
        REQUIRE(stream.read_line(line.c_str(), line.max_size()));
        REQUIRE(line == "This is a buffer");
        REQUIRE(stream.get_position() == sizeof(data));
        REQUIRE(stream.size() == sizeof(data));

        REQUIRE(!stream.read_line(line.c_str(), line.max_size()));
        REQUIRE(stream.get_position() == sizeof(data));
        REQUIRE(stream.size() == sizeof(data));
    }

    SECTION("read_line - multi line")
    {
        char8 data[37];
        memory::copy(data, "This is a buffer\nThis is another line", sizeof(data));
        memory_buffer_ref buffer((byte *) (data), sizeof(data));
        memory_istream stream(buffer);

        string_static<32> line;
        REQUIRE(stream.read_line(line.c_str(), line.max_size()));
        REQUIRE(line == "This is a buffer\n");
        REQUIRE(stream.get_position() == line.size());
        REQUIRE(stream.size() == sizeof(data));

        REQUIRE(stream.read_line(line.c_str(), line.max_size()));
        REQUIRE(line == "This is another line");
        REQUIRE(stream.get_position() == sizeof(data));
        REQUIRE(stream.size() == sizeof(data));

        REQUIRE(!stream.read_line(line.c_str(), line.max_size()));
        REQUIRE(stream.get_position() == sizeof(data));
        REQUIRE(stream.size() == sizeof(data));
    }
}

//==============================================================================
}
//==============================================================================
