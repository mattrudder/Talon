
#pragma once
#include <Talon/TalonPublic.h>
#include <ostream>

namespace Talon
{
	enum class InputDeviceType
	{
		Gamepad,
		Keyboard,
		Mouse,
		Touch
	};

	TalonApi std::ostream& operator<<(std::ostream& os, const InputDeviceType& e);
}