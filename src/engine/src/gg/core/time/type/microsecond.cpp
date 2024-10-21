#include "gg/core/time/type/microsecond.h"

//==============================================================================

#include "gg/core/time/type/day.h"
#include "gg/core/time/type/hour.h"
#include "gg/core/time/type/millisecond.h"
#include "gg/core/time/type/minute.h"
#include "gg/core/time/type/nanosecond.h"
#include "gg/core/time/type/second.h"

//==============================================================================
namespace gg
{
//==============================================================================

microsecond::storage_type const microsecond::amount_per_day         = 86400000000;
microsecond::storage_type const microsecond::amount_per_hour        = 3600000000;
microsecond::storage_type const microsecond::amount_per_millisecond = 1000;
microsecond::storage_type const microsecond::amount_per_minute      = 60000000;
microsecond::storage_type const microsecond::amount_per_second      = 1000000;

//==============================================================================

microsecond::microsecond(day const & day)
    : base(storage_type(day.get() * amount_per_day))
{
}

microsecond::microsecond(hour const & hour)
    : base(storage_type(hour.get() * amount_per_hour))
{
}

microsecond::microsecond(microsecond const & microsecond)
    : base(microsecond)
{
}

microsecond::microsecond(millisecond const & millisecond)
    : base(storage_type(millisecond.get() * amount_per_millisecond))
{
}

microsecond::microsecond(minute const & minute)
    : base(storage_type(minute.get() * amount_per_minute))
{
}

microsecond::microsecond(nanosecond const & nanosecond)
    : base(storage_type(nanosecond.get() / nanosecond::amount_per_microsecond))
{
}

microsecond::microsecond(second const & second)
    : base(storage_type(second.get() * amount_per_second))
{
}

//==============================================================================
}
//==============================================================================
