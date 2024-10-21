#include "gg/test/catch.h"

//==============================================================================

#include "gg/core/memory/memory_defs.h"
#include "gg/core/memory/memory.h"
#include "gg/core/string/type/string_ref.h"

//==============================================================================
namespace gg::memory_test
{
//==============================================================================

struct mock_item
{
    mock_item(int32 value = 0) noexcept : m_value(value) {}
    ~mock_item(void) noexcept = default;
    int32 m_value;
};

//==============================================================================

TEST_CASE("memory", "[gg.memory]")
{
#if defined(GG_DEBUG)
    SECTION("memory owner mode descriptors")
    {
        REQUIRE(
            string_ref(GG_TEXT("is_not_owner")) ==
            k_memory_owner_mode_descriptors[
                enums::cast(memory_owner_mode::is_not_owner)]);

        REQUIRE(
            string_ref(GG_TEXT("is_owner")) ==
            k_memory_owner_mode_descriptors[
                enums::cast(memory_owner_mode::is_owner)]);
    }
#endif
}

TEST_CASE("memory.compare", "[gg.memory]")
{
    SECTION("compare")
    {
        static uint32 constexpr k_max_num = 8;
        uint32 lhs[k_max_num];
        uint32 rhs[k_max_num];
        for (uint32 i = 0; i < k_max_num; ++i)
        {
            lhs[i] = i;
            rhs[i] = i;
        }
        REQUIRE(memory::compare(lhs, rhs, k_max_num) == 0);
    }

    SECTION("!compare")
    {
        static uint32 constexpr k_max_num = 8;
        uint32 lhs[k_max_num];
        uint32 rhs[k_max_num];
        for (uint32 i = 0; i < k_max_num; ++i)
        {
            lhs[i] = i;
            rhs[i] = k_max_num + i;
        }
        REQUIRE(memory::compare(lhs, rhs, k_max_num) != 0);
    }
}

TEST_CASE("memory.copy", "[gg.memory]")
{
    SECTION("copy")
    {
        static uint32 constexpr k_max_num = 8;
        uint32 lhs[k_max_num];
        uint32 rhs[k_max_num];
        for (uint32 i = 0; i < k_max_num; ++i)
        {
            lhs[i] = i;
            rhs[i] = k_max_num + i;
            REQUIRE(lhs[i] != rhs[i]);
        }
        memory::copy(rhs, lhs, k_max_num);
        for (uint32 i = 0; i < k_max_num; ++i)
        {
            REQUIRE(lhs[i] == rhs[i]);
        }
    }
}

TEST_CASE("memory.move", "[gg.memory]")
{
    SECTION("move")
    {
        static uint32 constexpr k_max_num = 8;
        uint32 lhs[k_max_num];
        uint32 rhs[k_max_num];
        for (uint32 i = 0; i < k_max_num; ++i)
        {
            lhs[i] = i;
            rhs[i] = k_max_num + i;
            REQUIRE(lhs[i] != rhs[i]);
        }
        memory::move(rhs, lhs, k_max_num);
        for (uint32 i = 0; i < k_max_num; ++i)
        {
            REQUIRE(lhs[i] == rhs[i]);
        }
    }
}

TEST_CASE("memory.zero", "[gg.memory]")
{
    SECTION("zero")
    {
        static uint32 constexpr k_max_num = 8;
        uint32 ptr[k_max_num];
        for (uint32 i = 0; i < k_max_num; ++i)
        {
            ptr[i] = i;
            REQUIRE(ptr[i] == i);
        }
        memory::zero(ptr, k_max_num);
        for (uint32 i = 0; i < k_max_num; ++i)
        {
            REQUIRE(ptr[i] == 0);
        }
    }
}

TEST_CASE("memory.allocate", "[gg.memory]")
{
    SECTION("allocate")
    {
        static uint32 constexpr k_bytes = 16;
        void * ptr = memory::allocate(k_bytes);
        REQUIRE(ptr);
        memory::deallocate(ptr);
    }
}

TEST_CASE("memory.deallocate", "[gg.memory]")
{
    SECTION("deallocate")
    {
        void * ptr = nullptr;
        memory::deallocate(ptr);
    }
}

TEST_CASE("memory.reallocate", "[gg.memory]")
{
    SECTION("reallocate")
    {
        static uint32 constexpr k_bytes = 16;
        void * ptr = nullptr;
        ptr = memory::reallocate(ptr, k_bytes);
        REQUIRE(ptr);
        memory::deallocate(ptr);
    }
}

TEST_CASE("memory.construct_object", "[gg.memory]")
{
    SECTION("construct_object")
    {
        static uint32 constexpr k_value = 8;
        mock_item * object = memory::allocate<mock_item>();
        memory::construct_object(object, k_value);
        REQUIRE(object->m_value == k_value);
        object->~mock_item();
        memory::deallocate(object);
    }
}

TEST_CASE("memory.delete_object", "[gg.memory]")
{
    SECTION("delete_object")
    {
        mock_item * object = nullptr;
        memory::delete_object(object);
    }
}

TEST_CASE("memory.delete_object_array", "[gg.memory]")
{
    SECTION("delete_object_array")
    {
        mock_item * object = nullptr;
        memory::delete_object_array(object);
    }
}

TEST_CASE("memory.new_object", "[gg.memory]")
{
    SECTION("new_object")
    {
        static uint32 constexpr k_value = 8;
        mock_item * object = memory::new_object<mock_item>(k_value);
        REQUIRE(object->m_value == k_value);
        memory::delete_object(object);
    }
}

TEST_CASE("memory.new_object_array", "[gg.memory]")
{
    SECTION("new_object_array")
    {
        static uint32 constexpr k_max_num = 8;
        mock_item * object = memory::new_object_array<mock_item>(k_max_num);
        for (uint32 i = 0; i < k_max_num; ++i)
        {
            REQUIRE(object[i].m_value == 0);
        }
        memory::delete_object_array(object);
    }
}

//==============================================================================
}
//==============================================================================
