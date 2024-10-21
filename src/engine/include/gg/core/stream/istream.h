#ifndef _gg_istream_h_
#define _gg_istream_h_

#include "gg/core/endian/endian.h"
#include "gg/core/macro/macro.h"
#include "gg/core/pattern/non_copyable.h"
#include "gg/core/type/type_trait.h"
#include "gg/core/utils/byte_swap.h"

namespace gg
{
    template <typename STREAM_TYPE>
    class istream : public non_copyable
    {
    public:

        // type definitions

        typedef STREAM_TYPE stream_type;

        // methods

        template <typename TYPE>
        size_type read(TYPE & value) noexcept
        {
            stream_type * stream = type::cast_static<stream_type *>(this);
            size_type read_size = stream->read(&value, sizeof(TYPE));
            GG_RETURN_VALUE_IF(0 == read_size, 0);
            if (!is_endian_mode(endian::system_mode))
            {
                value = byte_swap::swap(value);
            }
            return read_size;
        }

        // inquiries

        bool8 is_endian_mode(endian_mode mode) const noexcept
        {
            return m_endian_mode == mode;
        }

    protected:

        // constructors

        istream(endian_mode endian_mode = endian::system_mode) noexcept
            : m_endian_mode(endian_mode)
        {
        }
        ~istream(void) noexcept = default;

    private:

        // attributes

        endian_mode m_endian_mode;
    };
}

#endif // _gg_istream_h_
