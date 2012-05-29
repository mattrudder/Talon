
#include "TalonPrefix.h"
#include <Talon/Input/MouseInputDevice.h>

namespace Talon
{
    MouseInputDevice::~MouseInputDevice()
    {
    }

    MouseInputDevice::MouseInputDevice()
        : InputDevice(InputDeviceType::Mouse)
    {
    }
}