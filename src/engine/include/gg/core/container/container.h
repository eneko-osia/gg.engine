#ifndef _gg_container_h_
#define _gg_container_h_

#include "gg/core/type/type_trait.h"
#include <algorithm>

namespace gg
{
    namespace container
    {
        // methods

        template <typename ITERATOR, typename FUNCTION>
        inline ITERATOR
        find_if(ITERATOR begin, ITERATOR end, FUNCTION && function) noexcept
        {
            return std::find_if(begin, end, type::forward<FUNCTION>(function));
        }

        template <typename ITERATOR, typename FUNCTION>
        inline FUNCTION
        for_each(ITERATOR begin, ITERATOR end, FUNCTION && function) noexcept
        {
            return std::for_each(begin, end, type::forward<FUNCTION>(function));
        }

        template <typename ITERATOR, typename FUNCTION>
        inline ITERATOR
        remove_if(ITERATOR begin, ITERATOR end, FUNCTION && function) noexcept
        {
            return std::remove_if(begin, end, type::forward<FUNCTION>(function));
        }

        template <typename ITERATOR>
        inline void
        sort(ITERATOR begin, ITERATOR end) noexcept
        {
            std::sort(begin, end);
        }

        template <typename ITERATOR, typename FUNCTION>
        inline void
        sort(ITERATOR begin, ITERATOR end, FUNCTION && function) noexcept
        {
            std::sort(begin, end, type::forward<FUNCTION>(function));
        }
    }
}

#endif // _gg_container_h_
