#include "gg/core/time/type/minute.h"

//==============================================================================

#include "gg/core/time/type/day.h"
#include "gg/core/time/type/hour.h"
#include "gg/core/time/type/microsecond.h"
#include "gg/core/time/type/millisecond.h"
#include "gg/core/time/type/nanosecond.h"
#include "gg/core/time/type/second.h"

//==============================================================================
namespace gg
{
//==============================================================================

minute::storage_type const minute::amount_per_day   = 1440;
minute::storage_type const minute::amount_per_hour  = 60;

//==============================================================================

minute::minute(day const & day)
    : base(storage_type(day.get() * amount_per_day))
{
}

minute::minute(hour const & hour)
    : base(storage_type(hour.get() * amount_per_hour)
    )
{
}

minute::minute(microsecond const & microsecond)
    : base(storage_type(microsecond.get() / microsecond::amount_per_minute))
{
}

minute::minute(millisecond const & millisecond)
    : base(storage_type(millisecond.get() / millisecond::amount_per_minute))
{
}

minute::minute(minute const & minute)
    : base(minute)
{
}

minute::minute(nanosecond const & nanosecond)
    : base(storage_type(nanosecond.get() / nanosecond::amount_per_minute))
{
}

minute::minute(second const & second)
    : base(storage_type(second.get() / second::amount_per_minute))
{
}

//==============================================================================
}
//==============================================================================
