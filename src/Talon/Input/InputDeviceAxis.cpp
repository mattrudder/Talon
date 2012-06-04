
#include "TalonPrefix.h"
#include <Talon/Input/InputDeviceAxis.h>

namespace Talon
{
	std::ostream& operator<<(std::ostream& os, const InputDeviceAxis& e)
	{
		switch(e)
		{
		case InputDeviceAxis::LeftX:
			os << "LeftX";
			break;
		case InputDeviceAxis::LeftY:
			os << "LeftY";
			break;
		case InputDeviceAxis::LeftZ:
			os << "LeftZ";
			break;
		case InputDeviceAxis::RightX:
			os << "RightX";
			break;
		case InputDeviceAxis::RightY:
			os << "RightY";
			break;
		case InputDeviceAxis::RightZ:
			os << "RightZ";
			break;
		}

		return os;
	}
}