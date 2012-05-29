
#include "TalonPrefix.h"
#include <Talon/Input/KeyboardInputDevice.h>

namespace Talon
{
    KeyboardInputDevice::~KeyboardInputDevice()
    {
    }

    KeyboardInputDevice::KeyboardInputDevice()
        : InputDevice(InputDeviceType::Keyboard)
    {
    }
}