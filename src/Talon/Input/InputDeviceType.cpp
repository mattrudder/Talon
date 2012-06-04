
#include "TalonPrefix.h"
#include <Talon/Input/InputDeviceType.h>

namespace Talon
{
	std::ostream& operator<<(std::ostream& os, const InputDeviceType& e)
	{
		switch(e)
		{
		case InputDeviceType::Gamepad:
			os << "Gamepad";
			break;
		case InputDeviceType::Keyboard:
			os << "Keyboard";
			break;
		case InputDeviceType::Mouse:
			os << "Mouse";
			break;
		case InputDeviceType::Touch:
			os << "Touch";
			break;
		}

		return os;
	}
}