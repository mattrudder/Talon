
#pragma once
#include <Talon/TalonPublic.h>

namespace Talon
{
	enum class InputDeviceButton : u32
	{
		None,
		Up,
		Down,
		Left,
		Right,
		Start,
		Back,
		LeftThumb,
		RightThumb,
		LeftShoulder,
		RightShoulder,
		Button0,
		Button1,
		Button2,
		Button3,
		Button4,
	};

	TalonApi std::ostream& operator<<(std::ostream& os, const InputDeviceButton& e);
}