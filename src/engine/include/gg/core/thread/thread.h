#ifndef _gg_thread_h_
#define _gg_thread_h_

#include "gg/core/pattern/non_copyable.h"
#include "gg/core/time/type/nanosecond.h"

#include <thread>

namespace gg
{
    class thread final : public non_copyable
    {
    public:

        // class

        class current
        {
        public:

            // static methods

            static void sleep(nanosecond const & time) noexcept
            {
                std::this_thread::sleep_for(
                    std::chrono::nanoseconds(time.get()));
            }

            static void yield(void) noexcept
            {
                std::this_thread::yield();
            }

            // static accessors

            static uint64 get_id(void) noexcept
            {
                return
                    type::cast_static<uint64>(
                        std::hash<thread_type::id>{}(std::this_thread::get_id()));
            }
        };

        // constructors

        template <typename FUNCTION, typename... ARGS>
        thread(FUNCTION && function, ARGS &&... args) noexcept
            : m_thread(
                type::forward<FUNCTION>(function),
                type::forward<ARGS>(args)...)
        {
        }

        // static methods

        static uint32 max_threads(void) noexcept
        {
            return thread_type::hardware_concurrency();
        }

        // methods

        void detach(void) noexcept
        {
            m_thread.detach();
        }

        void join(void) noexcept
        {
            m_thread.join();
        }

        // accessors

        uint64 get_id(void) const noexcept
        {
            return
                type::cast_static<uint64>(
                    std::hash<thread_type::id>{}(m_thread.get_id()));
        }

        // inquiry

        bool8 is_joinable(void) const noexcept
        {
            return m_thread.joinable();
        }

    private:

        // type definitions

        typedef std::thread thread_type;

        // attributes

        thread_type m_thread;
    };
}

#endif // _gg_thread_h_
