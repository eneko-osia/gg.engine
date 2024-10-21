#include "gg/core/time/type/day.h"

//==============================================================================

#include "gg/core/time/type/hour.h"
#include "gg/core/time/type/microsecond.h"
#include "gg/core/time/type/millisecond.h"
#include "gg/core/time/type/minute.h"
#include "gg/core/time/type/nanosecond.h"
#include "gg/core/time/type/second.h"

//==============================================================================
namespace gg
{
//==============================================================================

day::day(day const & day)
    : base(day)
{
}

day::day(hour const & hour)
    : base(storage_type(hour.get() / hour::amount_per_day))
{
}

day::day(microsecond const & microsecond)
    : base(storage_type(microsecond.get() / microsecond::amount_per_day))
{
}

day::day(millisecond const & millisecond)
    : base(storage_type(millisecond.get() / millisecond::amount_per_day))
{
}

day::day(minute const & minute)
    : base(storage_type(minute.get() / minute::amount_per_day))
{
}

day::day(nanosecond const & nanosecond)
    : base(storage_type(nanosecond.get() / nanosecond::amount_per_day))
{
}

day::day(second const & second)
    : base(storage_type(second.get() / second::amount_per_day))
{
}

//==============================================================================
}
//==============================================================================
