#ifndef _gg_lib_linux_h_
#define _gg_lib_linux_h_

#include "gg/core/string/type/string_ref.h"
#include <dlfcn.h>

namespace gg
{
    class lib_linux
    {
    public:

        // methods

        bool8 load(string_ref const & path) noexcept;
        bool8 unload(void) noexcept;

        template <typename FUNCTION_PTR>
        FUNCTION_PTR get_method(string_ref const & name) noexcept
        {
            GG_ASSERT(m_image);
            return (FUNCTION_PTR) dlsym(m_image, name.c_str());
        }

    protected:

        // constructors

        lib_linux(void) noexcept;
        virtual ~lib_linux(void) noexcept;

    private:

        // attributes

        void * m_image;
    };

    typedef lib_linux lib_platform;
}

#endif // _gg_lib_linux_h_
