
#include "TalonPrefix.h"
#include "Input/RawInput/RawInputKeyboardDevice.h"
#include "Input/RawInput/RawInputEventArgs.h"
#include <sstream>

namespace Talon
{
	RawInputKeyboardDevice::~RawInputKeyboardDevice()
	{

	}

	RawInputKeyboardDevice::RawInputKeyboardDevice(HANDLE hDevice)
		: RawInputDevice(hDevice)
	{
	}

	void RawInputKeyboardDevice::ProcessEvent(RawInputEventArgs& e)
	{
		if (!IsConnected())
			SetIsConnected(true);

		auto& keyboardEvent = e.RawInputData->data.keyboard;
		std::stringstream ss;
		ss << "INPUT [Keys]: (" << keyboardEvent.VKey << ")" << std::endl;

		//TalonLog(ss.str().c_str());
	}
}