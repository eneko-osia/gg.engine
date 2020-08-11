#include "gg/engine/gui/gui_module.h"

//==============================================================================
namespace gg::engine
{
//==============================================================================

void gui_module::on_finalize(void) noexcept
{
}

bool8 gui_module::on_init(void) noexcept
{
    return true;
}

//==============================================================================
}
//==============================================================================

/*
class pid_controller
{
public:

    // constructors

    pid_controller(float32 p, float32 i, float32 d) noexcept
        : k_proportional(p)
        , k_integral(i)
        , k_derivative(d)
        , error(0.0f)
        , integral(0.0f)
    {
    }

    // methods

    float32 calculate(float32 elapsed, float32 goal, float32 actual) noexcept
    {
        float32 current_error = goal - actual;
        float32 current_integral = integral + (current_error * elapsed);
        float32 current =
            (k_proportional * current_error) +
            (k_integral * current_integral) +
            (k_derivative * ((current_error - error) / elapsed));
        error = current_error;
        integral = current_integral;
        return current;
    }

private:

    // attributes

    float32 const k_proportional;
    float32 const k_integral;
    float32 const k_derivative;

    float32 error;
    float32 integral;
};
*/