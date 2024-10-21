#ifndef _gg_second_h_
#define _gg_second_h_

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
    class nanosecond;

    // class in charge of define a second

    class second final : public number<second, uint64>
    {
    private:

        // type definitions

        typedef number<second, uint64> base;

    public:

        // using

        using base::storage_type;

        // constants

        static storage_type const amount_per_day;
        static storage_type const amount_per_hour;
        static storage_type const amount_per_minute;

        // constructors

        second(void) = default;
        second(storage_type && second) : base(type::move(second))
        {
        }
        ~second(void) = default;

        second(day const & day);
        second(hour const & hour);
        second(microsecond const & microsecond);
        second(millisecond const & millisecond);
        second(minute const & minute);
        second(nanosecond const & nanosecond);
        second(second const & second);
    };
}

#endif // _gg_second_h_
