#ifndef _gg_constant_h_
#define _gg_constant_h_

// include files

#include "gg/core/type/limit.h"
#include "gg/core/type/type.h"

// namespace

namespace gg
{
    // namespace in charge of define constant utilities

    namespace constant
    {
        // int8 constants

        static constexpr int8 k_int8_max = limit::numeric<int8>::max();
        static constexpr int8 k_int8_min = limit::numeric<int8>::min();

        // uint8 constants

        static constexpr uint8 k_uint8_max = limit::numeric<uint8>::max();
        static constexpr uint8 k_uint8_min = limit::numeric<uint8>::min();

        // int16 constants

        static constexpr int16 k_int16_max = limit::numeric<int16>::max();
        static constexpr int16 k_int16_min = limit::numeric<int16>::min();

        // uint16 constants

        static constexpr uint16 k_uint16_max = limit::numeric<uint16>::max();
        static constexpr uint16 k_uint16_min = limit::numeric<uint16>::min();

        // int32 constants

        static constexpr int32 k_int32_max = limit::numeric<int32>::max();
        static constexpr int32 k_int32_min = limit::numeric<int32>::min();

        // uint32 constants

        static constexpr uint32 k_uint32_max = limit::numeric<uint32>::max();
        static constexpr uint32 k_uint32_min = limit::numeric<uint32>::min();

        // int64 constants

        static constexpr int64 k_int64_max = limit::numeric<int64>::max();
        static constexpr int64 k_int64_min = limit::numeric<int64>::min();

        // uint64 constants

        static constexpr uint64 k_uint64_max = limit::numeric<uint64>::max();
        static constexpr uint64 k_uint64_min = limit::numeric<uint64>::min();

        // float32 constants

        static constexpr float32 k_float32_epsilon = limit::numeric<float32>::epsilon();
        static constexpr float32 k_float32_max = limit::numeric<float32>::max();
        static constexpr float32 k_float32_min = limit::numeric<float32>::min();

        // float64 constants

        static constexpr float64 k_float64_epsilon = limit::numeric<float64>::epsilon();
        static constexpr float64 k_float64_max = limit::numeric<float64>::max();
        static constexpr float64 k_float64_min = limit::numeric<float64>::min();

        // id_type constants

        static constexpr id_type k_id_type_invalid = limit::numeric<id_type>::max();
    }
}

// core fundamental constants

using gg::constant::k_int8_max;
using gg::constant::k_int8_min;

using gg::constant::k_uint8_max;
using gg::constant::k_uint8_min;

using gg::constant::k_int16_max;
using gg::constant::k_int16_min;

using gg::constant::k_uint16_max;
using gg::constant::k_uint16_min;

using gg::constant::k_int32_max;
using gg::constant::k_int32_min;

using gg::constant::k_uint32_max;
using gg::constant::k_uint32_min;

using gg::constant::k_int64_max;
using gg::constant::k_int64_min;

using gg::constant::k_uint64_max;
using gg::constant::k_uint64_min;

using gg::constant::k_float32_epsilon;
using gg::constant::k_float32_max;
using gg::constant::k_float32_min;

using gg::constant::k_float64_epsilon;
using gg::constant::k_float64_max;
using gg::constant::k_float64_min;

using gg::constant::k_id_type_invalid;

#endif // _gg_constant_h_
