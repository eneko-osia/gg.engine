#ifndef _gg_assert_h_
#define _gg_assert_h_

#ifdef GG_ASSERT_ENABLED
    #undef GG_ASSERT_ENABLED
#endif

#if defined(GG_DEBUG)
    #define GG_ASSERT_ENABLED 1
#else
    #define GG_ASSERT_ENABLED 0
#endif

#include "gg/core/debug/assert_platform.h"

#ifdef GG_ASSERT
    #undef GG_ASSERT
#endif

#ifdef GG_ASSERT_FAILED
    #undef GG_ASSERT_FAILED
#endif

#ifdef GG_ASSERT_STATIC
    #undef GG_ASSERT_STATIC
#endif

#if GG_ASSERT_ENABLED
    #define GG_ASSERT(cond)                 GG_ASSERT_PLATFORM(cond)
    #define GG_ASSERT_FAILED()              GG_ASSERT(false)
#else
    #define GG_ASSERT(cond)
    #define GG_ASSERT_FAILED()
#endif

#define GG_ASSERT_STATIC(cond, message) static_assert(cond, message)

#endif // _gg_assert_h_
