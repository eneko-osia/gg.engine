#ifndef _gg_engine_runtime_base_h_
#define _gg_engine_runtime_base_h_

#include "gg/app/runtime/runtime.h"
#include "gg/core/thread/atomic.h"
#include "gg/engine/pattern/module_locator/module_locator.h"
#include "gg/engine/runtime/runtime_log.h"
#include "gg/log/logger.h"

namespace gg::engine
{
    class runtime_base : public app::runtime
    {
    public:

        // methods

        void request_exit(void) noexcept
        {
            m_exit_requested = true;
        }

        // accessors

        template <typename MODULE_TYPE>
        MODULE_TYPE * get_module(void) noexcept
        {
            return m_modules.get<MODULE_TYPE>(MODULE_TYPE::get_id());
        }

        template <typename MODULE_TYPE>
        MODULE_TYPE const * get_module(void) const noexcept
        {
            return m_modules.get<MODULE_TYPE>(MODULE_TYPE::get_id());
        }

        // inquiries

        template <typename MODULE_TYPE>
        bool8 has_module(void) const noexcept
        {
            return m_modules.has(MODULE_TYPE::get_id());
        }

        bool8 is_exit_requested(void) const noexcept
        {
            return m_exit_requested;
        }

    protected:

        // constructors

        runtime_base(app::data const & data) noexcept;
        virtual ~runtime_base(void) noexcept = default;

        // methods

        template <typename MODULE_TYPE>
        void finalize_module(void) noexcept
        {
            GG_RETURN_IF(!m_modules.has(MODULE_TYPE::get_id()));
            finalize_module(m_modules.get<MODULE_TYPE>(MODULE_TYPE::get_id()));
            m_modules.unpublish(MODULE_TYPE::get_id());
        }

        template <typename MODULE_TYPE>
        bool8 init_module(void) noexcept
        {
            GG_RETURN_FALSE_IF(m_modules.has(MODULE_TYPE::get_id()));
            MODULE_TYPE * module = memory::new_object<MODULE_TYPE>();
            GG_RETURN_FALSE_IF(!init_module(module));
            m_modules.publish(MODULE_TYPE::get_id(), module);
            return true;
        }

    private:

        // virtual methods

        virtual void finalize(void) noexcept = 0;
        virtual bool8 init(void) noexcept = 0;
        virtual void run(void) noexcept = 0;

        // runtime_base override methods

        int32 main(void) noexcept override final;

        // methods

        template <typename MODULE_TYPE>
        void finalize_module(MODULE_TYPE * module) noexcept
        {
            GG_ASSERT(nullptr != module);

            log::logger::normal<log::runtime>(
                GG_TEXT("%s finalizing"),
                MODULE_TYPE::get_name().c_str());

            module->finalize();
            memory::delete_object(module);

            log::logger::normal<log::runtime>(
                GG_TEXT("%s finalized"),
                MODULE_TYPE::get_name().c_str());
        }

        template <typename MODULE_TYPE>
        bool8 init_module(MODULE_TYPE * module) noexcept
        {
            GG_ASSERT(nullptr != module);

            log::logger::normal<log::runtime>(
                GG_TEXT("%s initializing"),
                MODULE_TYPE::get_name().c_str());

            if (!module->init())
            {
                log::logger::normal<log::runtime>(
                    GG_TEXT("%s initialization failed"),
                    MODULE_TYPE::get_name().c_str());
                finalize_module(module);
                return false;
            }

            log::logger::normal<log::runtime>(
                GG_TEXT("%s initialized"),
                MODULE_TYPE::get_name().c_str());
            return true;
        }

        // attributes

        module_locator m_modules;
        atomic<bool8> m_exit_requested;
    };
}

#endif // _gg_engine_runtime_base_h_
