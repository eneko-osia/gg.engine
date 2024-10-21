#ifndef _gg_non_copyable_h_
#define	_gg_non_copyable_h_

namespace gg
{
    class non_copyable
    {
    protected:

        // constructors

        non_copyable(void) noexcept = default;
        ~non_copyable(void) noexcept = default;

    private:

        // constructors

        non_copyable(non_copyable const &) noexcept = delete;

        // operators

        non_copyable const & operator=(non_copyable const &) noexcept = delete;
    };
}

#endif // _gg_non_copyable_h_
