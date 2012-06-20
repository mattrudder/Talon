
#include "TalonPrefix.h"
#include <Talon/Input/InputDeviceChannel.h>

namespace Talon
{
	std::ostream& operator<<(std::ostream& os, const InputDeviceChannel& e)
	{
        const char* label = nullptr;
		switch(e)
		{
		case InputDeviceChannel::None:
			label = "None";
			break;
		case InputDeviceChannel::Axis:
			label = "Axis";
			break;
		case InputDeviceChannel::Button:
			label = "Button";
			break;
		case InputDeviceChannel::Key:
			label = "Key";
			break;
		}
        
        os << std::string(label);
		return os;
	}
}