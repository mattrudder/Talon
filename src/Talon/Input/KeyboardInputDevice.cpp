
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

	void KeyboardInputDevice::OnPressed(InputDeviceKey key)
	{
		Pressed(key);
	}

	void KeyboardInputDevice::OnReleased(InputDeviceKey key)
	{
		Released(key);
	}
}