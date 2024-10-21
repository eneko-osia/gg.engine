#ifndef _gg_non_movable_h_
#define	_gg_non_movable_h_

namespace gg
{
    class non_movable
    {
    protected:

        // constructors

        non_movable(void) noexcept = default;
        ~non_movable(void) noexcept = default;

    private:

        // constructors

        non_movable(non_movable &&) noexcept = delete;

        // operators

        non_movable const & operator=(non_movable &&) noexcept = delete;
    };
}

#endif // _gg_non_movable_h_
