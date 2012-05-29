
#pragma once
#include <Talon/TalonPublic.h>
#include <Talon/Input/MouseInputDevice.h>
#include "Input/RawInput/RawInputDevice.h"

namespace Talon
{
    class RawInputMouseDevice : public MouseInputDevice, public RawInputDevice
    {
    public:
		RawInputMouseDevice(HANDLE hDevice);
        ~RawInputMouseDevice();

		virtual void PollForUpdates();
    };
}