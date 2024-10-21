#include "gg/core/time/type/millisecond.h"

//==============================================================================

#include "gg/core/time/type/day.h"
#include "gg/core/time/type/hour.h"
#include "gg/core/time/type/microsecond.h"
#include "gg/core/time/type/minute.h"
#include "gg/core/time/type/nanosecond.h"
#include "gg/core/time/type/second.h"

//==============================================================================
namespace gg
{
//==============================================================================

millisecond::storage_type const millisecond::amount_per_day     = 86400000;
millisecond::storage_type const millisecond::amount_per_hour    = 3600000;
millisecond::storage_type const millisecond::amount_per_minute  = 60000;
millisecond::storage_type const millisecond::amount_per_second  = 1000;

//==============================================================================

millisecond::millisecond(day const & day)
    : base(storage_type(day.get() * amount_per_day))
{
}

millisecond::millisecond(hour const & hour)
    : base(storage_type(hour.get() * amount_per_hour))
{
}

millisecond::millisecond(microsecond const & microsecond)
    : base(storage_type(microsecond.get() / microsecond::amount_per_millisecond))
{
}

millisecond::millisecond(millisecond const & millisecond)
    : base(millisecond)
{
}

millisecond::millisecond(minute const & minute)
    : base(storage_type(minute.get() * amount_per_minute))
{
}

millisecond::millisecond(nanosecond const & nanosecond)
    : base(storage_type(nanosecond.get() / nanosecond::amount_per_millisecond))
{
}

millisecond::millisecond(second const & second)
    : base(storage_type(second.get() * amount_per_second))
{
}

//==============================================================================
}
//==============================================================================
