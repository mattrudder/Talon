
#include "TalonPrefix.h"
#include <Talon/Input/InputDeviceChannel.h>

namespace Talon
{
	std::ostream& operator<<(std::ostream& os, const InputDeviceChannel& e)
	{
		switch(e)
		{
		case InputDeviceChannel::None:
			os << "None";
			break;
		case InputDeviceChannel::Axis:
			os << "Axis";
			break;
		case InputDeviceChannel::Button:
			os << "Button";
			break;
		case InputDeviceChannel::Key:
			os << "Key";
			break;
		}

		return os;
	}
}