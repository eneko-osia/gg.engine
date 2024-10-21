#ifndef _gg_file_istream_h_
#define _gg_file_istream_h_

#include "gg/core/stream/istream.h"
#include "gg/core/stream/stream_defs.h"
#include <cstdio>

namespace gg
{
    class string_ref;

    class file_istream final : public istream<file_istream>
    {
    public:

        // constructors

        file_istream(
            string_ref const & filename,
            stream_mode stream_mode,
            endian_mode endian_mode = endian::system_mode) noexcept;
        ~file_istream(void) noexcept;

        // using

        using istream<file_istream>::read;

        // methods

        void close(void) noexcept;
        bool8 move(size_type position) noexcept;
        size_type read(void * buffer, size_type bytes) noexcept;
        size_type read_line(char8 * buffer, size_type max_size) noexcept;

        // accessors

        size_type get_position(void) const noexcept
        {
            return m_position;
        }

        size_type size(void) const noexcept
        {
            return m_size;
        }

        // inquiries

        bool8 is_valid(void) const noexcept
        {
            return nullptr != m_file;
        }

    private:

        // attributes

        FILE * m_file;
        size_type m_position;
        size_type m_size;
    };
}

#endif // _gg_file_istream_h_
