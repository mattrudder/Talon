
#include "TalonPrefix.h"
#include <Talon/Input/InputDeviceKey.h>

namespace Talon
{
	std::ostream& operator<<(std::ostream& os, const InputDeviceKey&)
	{
		os << "(Unknown)";

		return os;
	}
}