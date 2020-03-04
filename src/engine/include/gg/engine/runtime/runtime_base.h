#ifndef _gg_runtime_base_h_
#define _gg_runtime_base_h_

// include files

#include "gg/app/application/application.h"
#include "gg/engine/pattern/module_locator/module_locator.h"

// namespace

namespace gg
{
    // class in charge of define a base runtime

    class runtime_base : public application
    {
    protected:

        // constructors

        runtime_base(data const & data) noexcept;
        virtual ~runtime_base(void) noexcept;

        template <typename MODULE_TYPE>
        void finalize_module(uint32 module_id) noexcept
        {
            GG_RETURN_IF_FALSE_ASSERT(m_modules.has(module_id));
            MODULE_TYPE * module = m_modules.get<MODULE_TYPE>(module_id);
            m_modules.unpublish(module_id);
            module->finalize();
            memory::delete_object(module);
        }

        template <typename MODULE_TYPE>
        MODULE_TYPE * get_module(uint32 module_id) noexcept
        {
            return m_modules.get<MODULE_TYPE>(module_id);
        }

        template <typename MODULE_TYPE>
        MODULE_TYPE const * get_module(uint32 module_id) const noexcept
        {
            return m_modules.get<MODULE_TYPE>(module_id);
        }

        template <typename MODULE_TYPE>
        bool8 init_module(uint32 module_id) noexcept
        {
            GG_RETURN_FALSE_IF_TRUE_ASSERT(m_modules.has(module_id));
            MODULE_TYPE * module = memory::new_object<MODULE_TYPE>();
            if (!module->init())
            {
                GG_ASSERT_FAILED();
                memory::delete_object(module);
                return false;
            }
            m_modules.publish(module_id, module);
            return true;
        }

    private:

        // virtual methods

        virtual void finalize(void) noexcept = 0;
        virtual bool8 init(void) noexcept = 0;
        virtual int32 run(void) noexcept = 0;

        // override methods

        int32 main(void) noexcept override final;

    private:

        // attributes

        module_locator m_modules;
    };
}

#endif // _gg_runtime_base_h_
