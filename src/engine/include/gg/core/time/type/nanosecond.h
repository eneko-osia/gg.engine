#ifndef _gg_nanosecond_h_
#define _gg_nanosecond_h_

// include files

#include "gg/core/type/number.h"

// namespace

namespace gg
{
    // forward declarations

    class day;
    class hour;
    class microsecond;
    class millisecond;
    class minute;
    class second;

    // class in charge of define a nanosecond

    class nanosecond final : public number<nanosecond, uint64>
    {
    private:

        // type definitions

        typedef number<nanosecond, uint64> base;

    public:

        // using

        using base::storage_type;

        // constants

        static storage_type const amount_per_day;
        static storage_type const amount_per_hour;
        static storage_type const amount_per_microsecond;
        static storage_type const amount_per_millisecond;
        static storage_type const amount_per_minute;
        static storage_type const amount_per_second;

        // constructors

        nanosecond(void) = default;
        nanosecond(storage_type && nanosecond) : base(type::move(nanosecond))
        {
        }
        ~nanosecond(void) = default;

        nanosecond(day const & day);
        nanosecond(hour const & hour);
        nanosecond(microsecond const & microsecond);
        nanosecond(millisecond const & millisecond);
        nanosecond(minute const & minute);
        nanosecond(nanosecond const & nanosecond);
        nanosecond(second const & second);
    };
}

#endif // _gg_nanosecond_h_
