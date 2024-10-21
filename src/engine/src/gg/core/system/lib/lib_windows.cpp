//==============================================================================
#if defined(GG_WINDOWS)
//==============================================================================

#include "gg/core/system/lib/lib_windows.h"

//==============================================================================
namespace gg
{
//==============================================================================

lib_windows::lib_windows(void) noexcept
    : m_hinstance(nullptr)
{
}

lib_windows::~lib_windows(void) noexcept
{
    GG_ASSERT(!m_hinstance);
}

//==============================================================================

bool8 lib_windows::load(string_ref const & path) noexcept
{
    GG_ASSERT(!m_hinstance);

    m_hinstance = LoadLibrary(path.c_str());
    return nullptr != m_hinstance;
}

bool8 lib_windows::unload(void) noexcept
{
    GG_ASSERT(m_hinstance);

    GG_RETURN_FALSE_IF(!FreeLibrary(m_hinstance));
    m_hinstance = nullptr;
    return true;
}

//==============================================================================
}
//==============================================================================
#endif
//==============================================================================

