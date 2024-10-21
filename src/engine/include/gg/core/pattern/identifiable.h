#ifndef _gg_identifiable_h_
#define _gg_identifiable_h_

#include "gg/core/type/type_trait.h"

namespace gg
{
    template <typename ID_TYPE>
    class identifiable
    {
    public:

        // type definitions

        typedef ID_TYPE id_type;

        // constructors

        identifiable(void) noexcept = default;
        identifiable(identifiable const & obj) noexcept = default;
        identifiable(identifiable && obj) noexcept = default;

        identifiable(id_type const & id) noexcept
            : m_id(id)
        {
        }

        identifiable(id_type && id) noexcept
            : m_id(type::move(id))
        {
        }

        template <typename TYPE>
        identifiable(TYPE && id) noexcept
            : m_id(type::forward<TYPE>(id))
        {
        }

        // accessors

        id_type const & get_id(void) const noexcept
        {
            return m_id;
        }

        void set_id(id_type const & id) noexcept
        {
            m_id = id;
        }

        void set_id(id_type && id) noexcept
        {
            m_id = type::move(id);
        }

        template <typename TYPE>
        void set_id(TYPE && id) noexcept
        {
            m_id = type::forward<TYPE>(id);
        }

        // inquiries

        bool8 is_id(id_type const & id) const noexcept
        {
            return m_id == id;
        }

        template <typename TYPE>
        bool8 is_id(TYPE const & id) const noexcept
        {
            return m_id == id;
        }

    protected:

        // constructors

        ~identifiable(void) noexcept = default;

    private:

        // attributes

        id_type m_id;
    };
}

#endif // _gg_identifiable_h_
