
#pragma once
#include <Talon/TalonPublic.h>
#include <Talon/Input/KeyboardInputDevice.h>
#include "Input/RawInput/RawInputDevice.h"

namespace Talon
{
	class RawInputKeyboardDevice : public KeyboardInputDevice, public RawInputDevice
	{
	public:
		RawInputKeyboardDevice(HANDLE hDevice);
		~RawInputKeyboardDevice();

		virtual void ProcessEvent(RawInputEventArgs& e);
	};
}