#ifndef _gg_engine_module_locator_h_
#define _gg_engine_module_locator_h_

#include "gg/core/container/map/hash_map.h"
#include "gg/engine/pattern/module/module.h"

namespace gg::engine
{
    class module_locator final
    {
    public:

        // methods

        template <typename MODULE_TYPE>
        MODULE_TYPE * get(id_type id) noexcept
        {
            auto it = m_modules.find(id);
            module * module = (it != m_modules.end()) ? it->second : nullptr;
            GG_ASSERT(type::cast_dynamic<MODULE_TYPE *>(module));
            return type::cast_static<MODULE_TYPE *>(module);
        }

        template <typename MODULE_TYPE>
        MODULE_TYPE const * get(id_type id) const noexcept
        {
            auto it = m_modules.find(id);
            module * module = (it != m_modules.end()) ? it->second : nullptr;
            GG_ASSERT(type::cast_dynamic<MODULE_TYPE const *>(module));
            return type::cast_static<MODULE_TYPE const *>(module);
        }

        void publish(id_type id, module * module) noexcept
        {
            GG_ASSERT(!has(id));
            m_modules.insert(id, module);
        }

        void unpublish(id_type id) noexcept
        {
            GG_ASSERT(has(id));
            m_modules.erase(id);
        }

        // inquiries

        bool8 has(id_type id) const noexcept
        {
            return m_modules.has(id);
        }

    private:

        // type definitions

        typedef hash_map<id_type, module *> module_map;

        // attributes

        module_map m_modules;
    };
}

#endif // _gg_engine_module_locator_h_
