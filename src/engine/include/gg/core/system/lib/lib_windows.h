#ifndef _gg_lib_windows_h_
#define _gg_lib_windows_h_

#include "gg/core/string/type/string_ref.h"
#include <windows.h>

namespace gg
{
    class lib_windows
    {
    public:

        // methods

        bool8 load(string_ref const & path) noexcept;
        bool8 unload(void) noexcept;

        template <typename FUNCTION_PTR>
        FUNCTION_PTR get_method(string_ref const & name) noexcept
        {
            GG_ASSERT(m_hinstance);
            return (FUNCTION_PTR) GetProcAddress(m_hinstance, name.c_str());
        }

    protected:

        // constructors

        lib_windows(void) noexcept;
        virtual ~lib_windows(void) noexcept;

    private:

        // attributes

        HINSTANCE m_hinstance;
    };

    typedef lib_windows lib_platform;
}

#endif // _gg_lib_windows_h_
