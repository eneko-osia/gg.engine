#ifndef _gg_hour_h_
#define _gg_hour_h_

// include files

#include "gg/core/type/number.h"

// namespace

namespace gg
{
    // forward declarations

    class day;
    class microsecond;
    class millisecond;
    class minute;
    class nanosecond;
    class second;

    // class in charge of define an hour

    class hour final : public number<hour, uint64>
    {
    private:

        // type definitions

        typedef number<hour, uint64> base;

    public:

        // using

        using base::storage_type;

        // constants

        static storage_type const amount_per_day;

        // constructors

        hour(void) = default;
        hour(storage_type && hour) : base(type::move(hour))
        {
        }

        ~hour(void) = default;

        hour(day const & day);
        hour(hour const & hour);
        hour(microsecond const & microsecond);
        hour(millisecond const & millisecond);
        hour(minute const & minute);
        hour(nanosecond const & nanosecond);
        hour(second const & second);
    };
}

#endif // _gg_hour_h_
