
#include "TalonPrefix.h"
#include "Input/RawInput/RawInputMouseDevice.h"

namespace Talon
{
    RawInputMouseDevice::~RawInputMouseDevice()
    {

    }

	RawInputMouseDevice::RawInputMouseDevice(HANDLE hDevice)
		: RawInputDevice(hDevice)
	{
	}

	void RawInputMouseDevice::PollForUpdates()
	{
		RawInputDevice::PollForUpdatesCore();
	}
}