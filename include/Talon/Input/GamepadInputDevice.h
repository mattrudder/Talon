
#pragma once

#include <Talon/TalonPublic.h>
#include <Talon/Input/InputDevice.h>

namespace Talon
{
	class TalonApi GamepadInputDevice : public InputDevice
	{
	public:
		virtual ~GamepadInputDevice();

	protected:
		GamepadInputDevice();

	private:
	};
}