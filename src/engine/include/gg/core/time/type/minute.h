#ifndef _gg_minute_h_
#define _gg_minute_h_

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
    class nanosecond;
    class second;

    // class in charge of define a minute

    class minute final : public number<minute, uint64>
    {
    private:

        // type definitions

        typedef number<minute, uint64> base;

    public:

        // using

        using base::storage_type;

        // constants

        static storage_type const amount_per_day;
        static storage_type const amount_per_hour;

        // constructors

        minute(void) = default;
        minute(storage_type && minute) : base(type::move(minute))
        {
        }
        ~minute(void) = default;

        minute(day const & day);
        minute(hour const & hour);
        minute(microsecond const & microsecond);
        minute(millisecond const & millisecond);
        minute(minute const & minute);
        minute(nanosecond const & nanosecond);
        minute(second const & second);
    };
}

#endif // _gg_minute_h_
