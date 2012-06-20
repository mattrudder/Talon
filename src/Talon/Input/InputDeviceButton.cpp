
#include "TalonPrefix.h"
#include <Talon/Input/InputDeviceButton.h>

namespace Talon
{
	std::ostream& operator<<(std::ostream& os, const InputDeviceButton& e)
	{
        const char* label = nullptr;
		switch(e)
		{
		case InputDeviceButton::None:
			label = "None";
			break;
		case InputDeviceButton::Up:
			label = "Up";
			break;
		case InputDeviceButton::Down:
			label = "Down";
			break;
		case InputDeviceButton::Left:
			label = "Left";
			break;
		case InputDeviceButton::Right:
			label = "Right";
			break;
		case InputDeviceButton::Start:
			label = "Start";
			break;
		case InputDeviceButton::Back:
			label = "Back";
			break;
		case InputDeviceButton::LeftThumb:
			label = "LeftThumb";
			break;
		case InputDeviceButton::RightThumb:
			label = "RightThumb";
			break;
		case InputDeviceButton::LeftShoulder:
			label = "LeftShoulder";
			break;
		case InputDeviceButton::RightShoulder:
			label = "RightShoulder";
			break;
		case InputDeviceButton::Button0:
			label = "Button0";
			break;
		case InputDeviceButton::Button1:
			label = "Button1";
			break;
		case InputDeviceButton::Button2:
			label = "Button2";
			break;
		case InputDeviceButton::Button3:
			label = "Button3";
			break;
		case InputDeviceButton::Button4:
			label = "Button4";
			break;
		}

        os << std::string(label);
		return os;
	}
}