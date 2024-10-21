//==============================================================================
#if defined(GG_LINUX)
//==============================================================================

#include "gg/core/system/lib/lib_linux.h"

//==============================================================================
namespace gg
{
//==============================================================================

lib_linux::lib_linux(void) noexcept
    : m_image(nullptr)
{
}

lib_linux::~lib_linux(void) noexcept
{
    GG_ASSERT(!m_image);
}

//==============================================================================

bool8 lib_linux::load(string_ref const & path) noexcept
{
    GG_ASSERT(!m_image);

    m_image = dlopen(path.c_str(), RTLD_LAZY | RTLD_LOCAL);
    return nullptr != m_image;
}

bool8 lib_linux::unload(void) noexcept
{
    GG_ASSERT(m_image);

    GG_RETURN_FALSE_IF(0 != dlclose(m_image));
    m_image = nullptr;
    return true;
}

//==============================================================================
}
//==============================================================================
#endif
//==============================================================================

