#ifndef _gg_day_h_
#define _gg_day_h_

// include files

#include "gg/core/type/number.h"

// namespace

namespace gg
{
    // forward declarations

    class hour;
    class microsecond;
    class millisecond;
    class minute;
    class nanosecond;
    class second;

    // class in charge of define a day

    class day final : public number<day, uint64>
    {
    private:

        // type definitions

        typedef number<day, uint64> base;

    public:

        // using

        using base::storage_type;

        // constructors

        day(void) = default;
        day(storage_type && day) : base(type::move(day))
        {
        }

        ~day(void) = default;

        day(day const & day);
        day(hour const & hour);
        day(microsecond const & microsecond);
        day(millisecond const & millisecond);
        day(minute const & minute);
        day(nanosecond const & nanosecond);
        day(second const & second);
    };
}

#endif // _gg_day_h_
