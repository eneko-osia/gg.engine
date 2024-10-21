#ifndef _gg_mock_item_array_test_h_
#define _gg_mock_item_array_test_h_

// include files

#include "gg/core/type/type.h"

// namespace

namespace gg
{
    // structs

    struct simple_mock_item
    {
        simple_mock_item(void) noexcept = default;
        simple_mock_item(int32 value) noexcept : value(value) {}
        int32 value;
    };

    struct complex_mock_item
    {
        int32 value;
        bool8 constructor_called        : 1;
        bool8 copy_constructor_called   : 1;
        bool8 destructor_called         : 1;
        bool8 assign_called             : 1;
        mutable bool8 equality_called   : 1;

        complex_mock_item(void) noexcept
            : value(0)
            , constructor_called(false)
            , copy_constructor_called(false)
            , destructor_called(false)
            , assign_called(false)
            , equality_called(false)
        {
            constructor_called = true;
        }

        complex_mock_item(int32 value) noexcept
            : value(value)
            , constructor_called(false)
            , copy_constructor_called(false)
            , destructor_called(false)
            , assign_called(false)
            , equality_called(false)
        {
            constructor_called = true;
        }

        complex_mock_item(complex_mock_item const & item) noexcept
            : value(item.value)
            , constructor_called(false)
            , copy_constructor_called(false)
            , destructor_called(false)
            , assign_called(false)
            , equality_called(false)
        {
            copy_constructor_called = true;
        }

        ~complex_mock_item(void) noexcept
        {
            destructor_called = true;
        }

        void operator=(complex_mock_item const & item) noexcept
        {
            value = item.value;
            assign_called = true;
        }
        bool8 operator==(complex_mock_item const & item) const noexcept
        {
            equality_called = true;
            return value == item.value;
        }
    };

    inline bool8 operator<(
        simple_mock_item const & litem,
        simple_mock_item const & ritem)
    {
        return litem.value < ritem.value;
    }

    inline bool8 operator<(
        complex_mock_item const & litem,
        complex_mock_item const & ritem)
    {
        return litem.value < ritem.value;
    }
}

#endif // _gg_mock_item_array_test_h_
