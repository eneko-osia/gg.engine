#ifndef _gg_hash_h_
#define _gg_hash_h_

#include "gg/core/string/type/string_ref.h"

namespace gg
{
    class string_ref;

    namespace hash
    {
        namespace fnv1
        {
            // methods

            inline constexpr uint32 generate(string_ref const & string)
            {
                constexpr uint32 k_offset_basis = 0x811c9dc5;
                constexpr uint32 k_prime = (1 << 24) + (1 << 8) + 0x93;

                uint32 hash = k_offset_basis;
                for (auto cit = string.begin(); cit != string.end(); ++cit)
                {
                    hash *= k_prime;
                    hash ^= type::cast_static<uint8>(*cit);
                }
                return hash;
            }
        }

        namespace fnv1a
        {
            // methods

            inline constexpr uint32 generate(string_ref const & string)
            {
                constexpr uint32 k_offset_basis = 0x811c9dc5;
                constexpr uint32 k_prime = (1 << 24) + (1 << 8) + 0x93;

                uint32 hash = k_offset_basis;
                for (auto cit = string.begin(); cit != string.end(); ++cit)
                {
                    hash ^= type::cast_static<uint8>(*cit);
                    hash *= k_prime;
                }
                return hash;
            }
        }
    }
}

#endif // _gg_hash_h_
