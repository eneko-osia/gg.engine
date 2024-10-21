#include "gg/core/time/type/second.h"

//==============================================================================

#include "gg/core/time/type/day.h"
#include "gg/core/time/type/hour.h"
#include "gg/core/time/type/microsecond.h"
#include "gg/core/time/type/millisecond.h"
#include "gg/core/time/type/nanosecond.h"
#include "gg/core/time/type/minute.h"

//==============================================================================
namespace gg
{
//==============================================================================

second::storage_type const second::amount_per_day       = 86400;
second::storage_type const second::amount_per_hour      = 3600;
second::storage_type const second::amount_per_minute    = 60;

//==============================================================================

second::second(day const & day)
    : base(storage_type(day.get() * amount_per_day))
{
}

second::second(hour const & hour)
    : base(storage_type(hour.get() * amount_per_hour))
{
}

second::second(microsecond const & microsecond)
    : base(storage_type(microsecond.get() / microsecond::amount_per_second))
{
}

second::second(millisecond const & millisecond)
    : base(storage_type(millisecond.get() / millisecond::amount_per_second))
{
}

second::second(minute const & minute)
    : base(storage_type(minute.get() * amount_per_minute))
{
}

second::second(nanosecond const & nanosecond)
    : base(storage_type(nanosecond.get() / nanosecond::amount_per_second))
{
}

second::second(second const & second)
    : base(second)
{
}

//==============================================================================
}
//==============================================================================
