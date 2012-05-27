
#include "TalonPrefix.h"
#include <Talon/Input/GamepadInputDevice.h>

namespace Talon
{
	GamepadInputDevice::~GamepadInputDevice()
	{
	}

	GamepadInputDevice::GamepadInputDevice()
		: InputDevice(InputDeviceType::Gamepad)
	{
	}
}