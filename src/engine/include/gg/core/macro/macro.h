#ifndef _gg_macro_h_
#define _gg_macro_h_

#ifdef GG_DO_IF
    #undef GG_DO_IF
#endif

#ifdef GG_BREAK_IF
    #undef GG_BREAK_IF
#endif

#ifdef GG_CONTINUE_IF
    #undef GG_CONTINUE_IF
#endif

#ifdef GG_RETURN_FALSE_IF
    #undef GG_RETURN_FALSE_IF
#endif

#ifdef GG_RETURN_IF
    #undef GG_RETURN_IF
#endif

#ifdef GG_RETURN_NULL_IF
    #undef GG_RETURN_NULL_IF
#endif

#ifdef GG_RETURN_TRUE_IF
    #undef GG_RETURN_TRUE_IF
#endif

#ifdef GG_RETURN_VALUE_IF
    #undef GG_RETURN_VALUE_IF
#endif

#ifdef GG_UNUSED_ARGUMENT
    #undef GG_UNUSED_ARGUMENT
#endif

#ifdef GG_UNUSED_VARIABLE
    #undef GG_UNUSED_VARIABLE
#endif

#define GG_DO_IF(test, execute)         { if (test) { execute; } }
#define GG_BREAK_IF(test)               GG_DO_IF(test, break)
#define GG_CONTINUE_IF(test)            GG_DO_IF(test, continue)
#define GG_RETURN_FALSE_IF(test)        GG_DO_IF(test, return false)
#define GG_RETURN_IF(test)              GG_DO_IF(test, return)
#define GG_RETURN_NULL_IF(test)         GG_DO_IF(test, return nullptr)
#define GG_RETURN_TRUE_IF(test)         GG_DO_IF(test, return true)
#define GG_RETURN_VALUE_IF(test, value) GG_DO_IF(test, return value)
#define GG_UNUSED_ARGUMENT(variable)
#define GG_UNUSED_VARIABLE(variable)    { (void) variable; }

#endif // _gg_macro_h_
