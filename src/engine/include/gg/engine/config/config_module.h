#ifndef _gg_engine_config_module_h_
#define _gg_engine_config_module_h_

#include "gg/config/configuration.h"
#include "gg/engine/pattern/module/module.h"

namespace gg::engine
{
    class config_module final : public module
    {
    public:

        GG_DECLARE_MODULE(config_module);

        // accessors

        template <typename TYPE>
        TYPE get_value(string_ref const & key, TYPE const & ret_value) const noexcept
        {
            return m_configuration.get_value<TYPE>(key, ret_value);
        }

        template <typename TYPE>
        void set_value(string_ref const & key, TYPE const & value) noexcept
        {
            return m_configuration.set_value<TYPE>(key, value);
        }

        // inquiries

        bool8 has_value(string_ref const & key) const noexcept
        {
            return m_configuration.has_value(key);
        }

        bool8 has_values(void) const noexcept
        {
            return m_configuration.has_values();
        }

    private:

        // module override methods

        void on_finalize(void) noexcept override;
        bool8 on_init(void) noexcept override;

    private:

        // attributes

        configuration m_configuration;
    };
}

#endif // _gg_engine_config_module_h_
