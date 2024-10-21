#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/memory/memory_buffer_static.h"

//==============================================================================
namespace gg::memory_buffer_static_test
{
//==============================================================================

static constexpr uint32 k_bytes = 32;
using mock_memory_buffer_static = memory_buffer_static<k_bytes>;

//==============================================================================

TEST_CASE("memory_buffer_static", "[gg.memory_buffer_static]")
{
    SECTION("assign")
    {
        REQUIRE(!type::is_copy_assignable<mock_memory_buffer_static>::value);
        REQUIRE(!type::is_trivially_assignable<mock_memory_buffer_static>::value);
    }

    SECTION("construct")
    {
        REQUIRE(type::is_constructible<mock_memory_buffer_static>::value);
        REQUIRE(type::is_trivially_constructible<mock_memory_buffer_static>::value);
    }

    SECTION("copy")
    {
        REQUIRE(!type::is_copy_constructible<mock_memory_buffer_static>::value);
        REQUIRE(!type::is_trivially_copy_constructible<mock_memory_buffer_static>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(type::is_destructible<mock_memory_buffer_static>::value);
        REQUIRE(type::is_trivially_destructible<mock_memory_buffer_static>::value);
    }

    SECTION("compare")
    {
        REQUIRE(!type::is_comparable<mock_memory_buffer_static>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<mock_memory_buffer_static>::value);
    }

    SECTION("sizeof")
    {
        REQUIRE(sizeof(mock_memory_buffer_static) == k_bytes);
    }
}

TEST_CASE("memory_buffer_static.constructor", "[gg.memory_buffer_static]")
{
    SECTION("memory_buffer_static")
    {
        mock_memory_buffer_static buffer;
        REQUIRE(buffer.data() != nullptr);
        REQUIRE(buffer.size() == k_bytes);
    }
}

TEST_CASE("memory_buffer_static.get", "[gg.memory_buffer_static]")
{
    SECTION("get")
    {
        mock_memory_buffer_static buffer;
        buffer.get(0) = 3;
        buffer.get(1) = 2;
        buffer.get(2) = 1;

        REQUIRE(buffer.get(0) == 3);
        REQUIRE(buffer.get(1) == 2);
        REQUIRE(buffer.get(2) == 1);

        REQUIRE(buffer.get(0) == buffer.data<byte>()[0]);
        REQUIRE(buffer.get(1) == buffer.data<byte>()[1]);
        REQUIRE(buffer.get(2) == buffer.data<byte>()[2]);
    }
}

//==============================================================================
}
//==============================================================================
