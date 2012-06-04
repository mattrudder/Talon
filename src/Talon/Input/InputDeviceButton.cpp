
#include "TalonPrefix.h"
#include <Talon/Input/InputDeviceButton.h>

namespace Talon
{
	std::ostream& operator<<(std::ostream& os, const InputDeviceButton& e)
	{
		switch(e)
		{
		case InputDeviceButton::None:
			os << "None";
			break;
		case InputDeviceButton::Up:
			os << "Up";
			break;
		case InputDeviceButton::Down:
			os << "Down";
			break;
		case InputDeviceButton::Left:
			os << "Left";
			break;
		case InputDeviceButton::Right:
			os << "Right";
			break;
		case InputDeviceButton::Start:
			os << "Start";
			break;
		case InputDeviceButton::Back:
			os << "Back";
			break;
		case InputDeviceButton::LeftThumb:
			os << "LeftThumb";
			break;
		case InputDeviceButton::RightThumb:
			os << "RightThumb";
			break;
		case InputDeviceButton::LeftShoulder:
			os << "LeftShoulder";
			break;
		case InputDeviceButton::RightShoulder:
			os << "RightShoulder";
			break;
		case InputDeviceButton::Button0:
			os << "Button0";
			break;
		case InputDeviceButton::Button1:
			os << "Button1";
			break;
		case InputDeviceButton::Button2:
			os << "Button2";
			break;
		case InputDeviceButton::Button3:
			os << "Button3";
			break;
		case InputDeviceButton::Button4:
			os << "Button4";
			break;
		}

		return os;
	}
}