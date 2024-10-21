#ifndef _gg_atomic_h_
#define _gg_atomic_h_

#include <atomic>

namespace gg
{
    template <typename TYPE>
    using atomic = std::atomic<TYPE>;
}

#endif // _gg_atomic_h_
