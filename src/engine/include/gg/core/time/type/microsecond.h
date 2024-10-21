#ifndef _gg_microsecond_h_
#define _gg_microsecond_h_

// include files

#include "gg/core/type/number.h"

// namespace

namespace gg
{
    // forward declarations

    class day;
    class hour;
    class millisecond;
    class minute;
    class nanosecond;
    class second;

    // class in charge of define a microsecond

    class microsecond : public number<microsecond, uint64>
    {
    private:

        // type definitions

        typedef number<microsecond, uint64> base;

    public:

        // using

        using base::storage_type;

        // constants

        static storage_type const amount_per_day;
        static storage_type const amount_per_hour;
        static storage_type const amount_per_millisecond;
        static storage_type const amount_per_minute;
        static storage_type const amount_per_second;

        // constructors

        microsecond(void) = default;
        microsecond(storage_type && microsecond) : base(type::move(microsecond))
        {
        }
        ~microsecond(void) = default;

        microsecond(day const & day);
        microsecond(hour const & hour);
        microsecond(microsecond const & microsecond);
        microsecond(millisecond const & millisecond);
        microsecond(minute const & minute);
        microsecond(nanosecond const & nanosecond);
        microsecond(second const & second);
    };
}

#endif // _gg_microsecond_h_
