#include "gg/core/time/type/hour.h"

//==============================================================================

#include "gg/core/time/type/day.h"
#include "gg/core/time/type/microsecond.h"
#include "gg/core/time/type/millisecond.h"
#include "gg/core/time/type/minute.h"
#include "gg/core/time/type/nanosecond.h"
#include "gg/core/time/type/second.h"

//==============================================================================
namespace gg
{
//==============================================================================

hour::storage_type const hour::amount_per_day = 24;

//==============================================================================

hour::hour(day const & day)
    : base(storage_type(day.get() * amount_per_day))
{
}

hour::hour(hour const & hour)
    : base(hour)
{
}

hour::hour(microsecond const & microsecond)
    : base(storage_type(microsecond.get() / microsecond::amount_per_hour))
{
}

hour::hour(millisecond const & millisecond)
    : base(storage_type(millisecond.get() / millisecond::amount_per_hour))
{
}

hour::hour(minute const & minute)
    : base(storage_type(minute.get() / minute::amount_per_hour))
{
}

hour::hour(nanosecond const & nanosecond)
    : base(storage_type(nanosecond.get() / nanosecond::amount_per_hour))
{
}

hour::hour(second const & second)
    : base(storage_type(second.get() / second::amount_per_hour))
{
}

//==============================================================================
}
//==============================================================================
