#include "gg/core/time/type/nanosecond.h"

//==============================================================================

#include "gg/core/time/type/day.h"
#include "gg/core/time/type/hour.h"
#include "gg/core/time/type/microsecond.h"
#include "gg/core/time/type/millisecond.h"
#include "gg/core/time/type/minute.h"
#include "gg/core/time/type/second.h"

//==============================================================================
namespace gg
{
//==============================================================================

nanosecond::storage_type const nanosecond::amount_per_day         = 86400000000000;
nanosecond::storage_type const nanosecond::amount_per_hour        = 3600000000000;
nanosecond::storage_type const nanosecond::amount_per_microsecond = 1000;
nanosecond::storage_type const nanosecond::amount_per_millisecond = 1000000;
nanosecond::storage_type const nanosecond::amount_per_minute      = 60000000000;
nanosecond::storage_type const nanosecond::amount_per_second      = 1000000000;

//==============================================================================

nanosecond::nanosecond(day const & day)
    : base(storage_type(day.get() * amount_per_day))
{
}

nanosecond::nanosecond(hour const & hour)
    : base(storage_type(hour.get() * amount_per_hour))
{
}

nanosecond::nanosecond(microsecond const & microsecond)
    : base(storage_type(microsecond.get() * amount_per_microsecond))
{
}

nanosecond::nanosecond(millisecond const & millisecond)
    : base(storage_type(millisecond.get() * amount_per_millisecond))
{
}

nanosecond::nanosecond(minute const & minute)
    : base(storage_type(minute.get() * amount_per_minute))
{
}

nanosecond::nanosecond(nanosecond const & nanosecond)
    : base(nanosecond)
{
}

nanosecond::nanosecond(second const & second)
    : base(storage_type(second.get() * amount_per_second))
{
}

//==============================================================================
}
//==============================================================================
