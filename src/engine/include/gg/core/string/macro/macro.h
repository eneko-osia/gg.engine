#ifndef _gg_string_macro_h_
#define _gg_string_macro_h_

#ifdef GG_TEXT
    #undef GG_TEXT
#endif

#define GG_TEXT(text) u8##text

#endif // _gg_string_macro_h_
