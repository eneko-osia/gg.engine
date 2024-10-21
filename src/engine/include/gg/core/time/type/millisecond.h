#ifndef _gg_millisecond_h_
#define _gg_millisecond_h_

// include files

#include "gg/core/type/number.h"

// namespace

namespace gg
{
    // forward declarations

    class day;
    class hour;
    class microsecond;
    class minute;
    class nanosecond;
    class second;

    // class in charge of define a millisecond

    class millisecond final : public number<millisecond, uint64>
    {
    private:

        // type definitions

        typedef number<millisecond, uint64> base;

    public:

        // using

        using base::storage_type;

        // constants

        static storage_type const amount_per_day;
        static storage_type const amount_per_hour;
        static storage_type const amount_per_minute;
        static storage_type const amount_per_second;

        // constructors

        millisecond(void) = default;
        millisecond(storage_type && millisecond) : base(type::move(millisecond))
        {
        }
        ~millisecond(void) = default;

        millisecond(day const & day);
        millisecond(hour const & hour);
        millisecond(microsecond const & microsecond);
        millisecond(millisecond const & millisecond);
        millisecond(minute const & minute);
        millisecond(nanosecond const & nanosecond);
        millisecond(second const & second);
    };
}

#endif // _gg_millisecond_h_
