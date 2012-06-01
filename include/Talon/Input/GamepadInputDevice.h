
#pragma once

#include <Talon/TalonPublic.h>
#include <Talon/TalonDelegate.h>
#include <Talon/Input/InputDevice.h>
#include <Talon/Input/InputDeviceAxis.h>
#include <Talon/Input/InputDeviceButton.h>

namespace Talon
{
	class TalonApi GamepadInputDevice : public InputDevice
	{
	public:
		virtual ~GamepadInputDevice();

		virtual f32 GetAxis(InputDeviceAxis axis) const = 0;
		virtual bool GetButton(InputDeviceButton button) const = 0;

		delegate<GamepadInputDevice, void (InputDeviceButton)> Pressed;
		delegate<GamepadInputDevice, void (InputDeviceButton)> Released;

	protected:
		GamepadInputDevice();

		void OnPressed(InputDeviceButton button);
		void OnReleased(InputDeviceButton button);

	private:
	};
}