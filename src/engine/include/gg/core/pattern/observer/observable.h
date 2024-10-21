#ifndef _gg_observable_h_
#define _gg_observable_h_

// include files

#include "gg/core/container/array/array_dynamic.h"
#include "gg/core/container/container.h"

// namespace

namespace gg
{
    // class in charge of define an observable object

    template <typename OBSERVER_TYPE>
    class observable
    {
    public:

        // type definitions

        typedef OBSERVER_TYPE observer_type;

        // static asserts

        GG_ASSERT_STATIC(
            !type::is_pointer<observer_type>::value,
            "pointer observer_type is not allowed");

        // constructors

        observable(void) noexcept = default;
        observable(observable const & obj) noexcept = default;
        observable(observable && obj) noexcept = default;

        // methods

        void add_observer(observer_type * const observer) noexcept
        {
            GG_ASSERT(!has_observer(observer));
            m_observers.push_back(observer);
        }

        void clear_observers(void) noexcept
        {
            m_observers.clear();
        }

        void remove_observer(observer_type const * const observer) noexcept
        {
            m_observers.erase(
                container::find_if(
                    m_observers.begin(),
                    m_observers.end(),
                    [&] (typename observer_array::const_reference obs)
                    {
                        return obs == observer;
                    }));
        }

        template <typename FUNCTION, typename... ARGS>
        void
        notify_observers(FUNCTION && function, ARGS &&... args) const noexcept
        {
            container::for_each(
                m_observers.begin(),
                m_observers.end(),
                [&] (typename observer_array::const_reference obs)
                {
                    (obs->*function)(type::forward<ARGS>(args)...);
                });
        }

        // inquiry

        bool8 has_observer(observer_type const * const observer) const noexcept
        {
            return
                container::find_if(
                    m_observers.begin(),
                    m_observers.end(),
                    [&] (typename observer_array::const_reference obs)
                    {
                        return obs == observer;
                    }) !=
                m_observers.end();
        }

        bool8 has_observers(void) const noexcept
        {
            return !m_observers.is_empty();
        }

    protected:

        // constructors

        ~observable(void) noexcept = default;

    private:

        // type definitions

        typedef array_dynamic<observer_type *> observer_array;

    private:

        // attributes

        observer_array m_observers;
    };
}

#endif // _gg_observable_h_
