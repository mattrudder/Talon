
#include "TalonPrefix.h"
#include <Talon/Input/InputDeviceAxis.h>

namespace Talon
{
	std::ostream& operator<<(std::ostream& os, const InputDeviceAxis& e)
	{
        const char* label = nullptr;
		switch(e)
		{
		case InputDeviceAxis::LeftX:
			label = "LeftX";
			break;
		case InputDeviceAxis::LeftY:
			label = "LeftY";
			break;
		case InputDeviceAxis::LeftZ:
			label = "LeftZ";
			break;
		case InputDeviceAxis::RightX:
			label = "RightX";
			break;
		case InputDeviceAxis::RightY:
			label = "RightY";
			break;
		case InputDeviceAxis::RightZ:
			label = "RightZ";
			break;
		}
        
        os << std::string(label);

		return os;
	}
}