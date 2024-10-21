#ifndef _gg_time_h_
#define _gg_time_h_

#include "gg/core/time/type/nanosecond.h"
#include "gg/core/time/type/second.h"
#include <chrono>
#include <ctime>

namespace gg
{
    class time final
    {
    public:

        // methods

        template <typename TIME_TYPE>
        static void format(
            char8 * buffer,
            size_type size,
            char8 const * message,
            TIME_TYPE time)
        {
            std::time_t time_to_format = second(time).get();
            std::strftime(buffer, size, message, std::localtime(&time_to_format));
        }

        template <typename TIME_TYPE>
        static TIME_TYPE clock_now(void)
        {
            return now<TIME_TYPE, std::chrono::high_resolution_clock>();
        }

        template <typename TIME_TYPE>
        static TIME_TYPE system_now(void)
        {
            return now<TIME_TYPE, std::chrono::system_clock>();
        }

    private:

        // methods

        template <typename TIME_TYPE, typename TIME_GENERATOR>
        static TIME_TYPE now(void)
        {
            auto current_time = TIME_GENERATOR::now();
            std::chrono::nanoseconds time_since_epoch =
                std::chrono::duration_cast<
                    std::chrono::nanoseconds>(current_time.time_since_epoch());
            return TIME_TYPE(nanosecond(time_since_epoch.count()));
        }
    };
}

#endif // _gg_time_h_
