#ifndef _gg_singleton_manual_h_
#define _gg_singleton_manual_h_

#include "gg/core/memory/memory.h"
#include "gg/core/pattern/non_copyable.h"

namespace gg
{
    template <typename SINGLETON_TYPE>
    class singleton_manual : public non_copyable
    {
    public:

        // type definitions

        typedef SINGLETON_TYPE singleton_type;

        // static asserts

        GG_ASSERT_STATIC(
            !type::is_pointer<singleton_type>::value,
            "pointer singleton_type is not allowed");

        // static methods

        template <typename... ARGS>
        static void create(ARGS &&... args) noexcept
        {
            create<singleton_type>(type::forward<ARGS>(args)...);
        }

        template <typename TYPE, typename... ARGS>
        static void create(ARGS &&... args) noexcept
        {
            GG_ASSERT(!is_available());
            m_instance =
                memory::new_object<TYPE>(type::forward<ARGS>(args)...);
        }

        static void destroy(void) noexcept
        {
            singleton_type * instance = m_instance;
            m_instance = nullptr;
            memory::delete_object(instance);
        }

        // static accessors

        static singleton_type & get_instance(void) noexcept
        {
            return get_instance<singleton_type>();
        }

        template <typename TYPE>
        static TYPE & get_instance(void) noexcept
        {
            GG_ASSERT(is_available());
            GG_ASSERT(type::cast_dynamic<TYPE *>(m_instance));
            return *type::cast_static<TYPE *>(m_instance);
        }

        // static inquiries

        static bool8 is_available(void) noexcept
        {
            return nullptr != m_instance;
        }

    protected:

        // constructors

        singleton_manual(void) noexcept = default;
        ~singleton_manual(void) noexcept
        {
            GG_ASSERT(!m_instance);
        }

    private:

        // static attributes

        static singleton_type * m_instance;
    };

    // initialize static pointer

    template <typename SINGLETON_TYPE>
    SINGLETON_TYPE * singleton_manual<SINGLETON_TYPE>::m_instance = nullptr;
}

#endif // _gg_singleton_manual_h_

