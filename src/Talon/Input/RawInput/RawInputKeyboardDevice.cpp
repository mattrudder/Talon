
#include "TalonPrefix.h"
#include "Input/RawInput/RawInputKeyboardDevice.h"

namespace Talon
{
	RawInputKeyboardDevice::~RawInputKeyboardDevice()
	{

	}

	RawInputKeyboardDevice::RawInputKeyboardDevice(HANDLE hDevice)
		: RawInputDevice(hDevice)
	{
	}

	void RawInputKeyboardDevice::PollForUpdates()
	{
		RawInputDevice::PollForUpdatesCore();
	}
}