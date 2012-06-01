
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

	void GamepadInputDevice::OnPressed(InputDeviceButton button)
	{
		Pressed(button);
	}

	void GamepadInputDevice::OnReleased(InputDeviceButton button)
	{
		Released(button);
	}
}