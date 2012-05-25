
#include "TalonPrefix.h"
#include "Input/RawInput/RawInputDevice.h"

namespace Talon
{
	InputDevice::Kind RawInputDevice::Kind = { "RawInput", RawInputDevice::Enumerate };

	std::vector<std::shared_ptr<InputDevice>> RawInputDevice::Enumerate()
	{
		std::vector<std::shared_ptr<InputDevice>> devices;
		return devices;
	}

	RawInputDevice::~RawInputDevice()
	{

	}

	RawInputDevice::RawInputDevice()
	{

	}
}