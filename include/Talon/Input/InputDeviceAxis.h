
#pragma once
#include <Talon/TalonPublic.h>

namespace Talon
{
	enum class InputDeviceAxis : u32
	{
		LeftX,
		LeftY,
		LeftZ,
		RightX,
		RightY,
		RightZ
	};

	TalonApi std::ostream& operator<<(std::ostream& os, const InputDeviceAxis& e);
}