#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/memory/memory.h"
#include "gg/core/memory/memory_buffer_ref.h"
#include "gg/core/type/type_trait.h"

//==============================================================================
namespace gg::memory_buffer_ref_test
{
//==============================================================================

TEST_CASE("memory_buffer_ref", "[gg.memory_buffer_ref]")
{
    SECTION("assign")
    {
        REQUIRE(type::is_copy_assignable<memory_buffer_ref>::value);
        REQUIRE(!type::is_trivially_assignable<memory_buffer_ref>::value);
    }

    SECTION("construct")
    {
        REQUIRE(type::is_constructible<memory_buffer_ref>::value);
        REQUIRE(!type::is_trivially_constructible<memory_buffer_ref>::value);
    }

    SECTION("copy")
    {
        REQUIRE(type::is_copy_constructible<memory_buffer_ref>::value);
        REQUIRE(!type::is_trivially_copy_constructible<memory_buffer_ref>::value);
    }

    SECTION("destroy")
    {
        REQUIRE(type::is_destructible<memory_buffer_ref>::value);
        REQUIRE(type::is_trivially_destructible<memory_buffer_ref>::value);
    }

    SECTION("compare")
    {
        REQUIRE(!type::is_comparable<memory_buffer_ref>::value);
    }

    SECTION("polymorphic")
    {
        REQUIRE(!type::is_polymorphic<memory_buffer_ref>::value);
    }
}

TEST_CASE("memory_buffer_ref.constructor", "[gg.memory_buffer_ref]")
{
    SECTION("memory_buffer_ref")
    {
        memory_buffer_ref buffer;
        REQUIRE(buffer.data() == nullptr);
        REQUIRE(buffer.size() == 0);
    }

    SECTION("memory_buffer_ref(pointer, size)")
    {
        uint8 data[32];
        memory_buffer_ref buffer(data, 16);
        REQUIRE(buffer.data() == data);
        REQUIRE(buffer.size() == 16);
        REQUIRE(memory::compare(data, buffer.data(), buffer.size()) == 0);
    }

    SECTION("memory_buffer_ref(memory_buffer_ref)")
    {
        uint8 data[32];
        memory_buffer_ref copied_buffer(data, 16);
        memory_buffer_ref buffer(copied_buffer);
        REQUIRE(buffer.data() == data);
        REQUIRE(buffer.size() == 16);
        REQUIRE(memory::compare(data, buffer.data(), buffer.size()) == 0);
        REQUIRE(copied_buffer.data() == data);
        REQUIRE(copied_buffer.size() == 16);
        REQUIRE(memory::compare(data, copied_buffer.data(), copied_buffer.size()) == 0);
    }

    SECTION("memory_buffer_ref(rvalue_memory_buffer_ref)")
    {
        uint8 data[32];
        memory_buffer_ref moved_buffer(data, 16);
        memory_buffer_ref buffer(type::move(moved_buffer));
        REQUIRE(buffer.data() == data);
        REQUIRE(buffer.size() == 16);
        REQUIRE(memory::compare(data, buffer.data(), buffer.size()) == 0);
        REQUIRE(moved_buffer.data() == nullptr);
        REQUIRE(moved_buffer.size() == 0);
    }
}

TEST_CASE("memory_buffer_ref.operator=", "[gg.memory_buffer_ref]")
{
    SECTION("memory_buffer_ref = memory_buffer_ref")
    {
        uint8 data[32];
        memory_buffer_ref copied_buffer(data, 16);
        memory_buffer_ref buffer;
        buffer = copied_buffer;

        REQUIRE(buffer.data() == data);
        REQUIRE(buffer.size() == 16);
        REQUIRE(memory::compare(data, buffer.data(), buffer.size()) == 0);

        REQUIRE(copied_buffer.data() == data);
        REQUIRE(copied_buffer.size() == 16);
        REQUIRE(memory::compare(data, copied_buffer.data(), copied_buffer.size()) == 0);
    }

    SECTION("memory_buffer_ref = rvalue_memory_buffer_ref")
    {
        uint8 data[32];
        memory_buffer_ref moved_buffer(data, 16);
        memory_buffer_ref buffer;
        buffer = type::move(moved_buffer);

        REQUIRE(buffer.data() == data);
        REQUIRE(buffer.size() == 16);
        REQUIRE(memory::compare(data, buffer.data(), buffer.size()) == 0);

        REQUIRE(moved_buffer.data() == nullptr);
        REQUIRE(moved_buffer.size() == 0);
    }
}

TEST_CASE("memory_buffer_ref.get", "[gg.memory_buffer_ref]")
{
    SECTION("get")
    {
        uint8 data[32] = { 0 };
        memory_buffer_ref buffer(data, 16);
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
