
#include "TalonPrefix.h"
#include <Talon/Input/InputService.h>

#if TALON_WINDOWS
#include "Input/XInput/XInputDevice.h"
#include "Input/RawInput/RawInputDevice.h"
#endif

#include <algorithm>
using namespace std;

namespace Talon
{
	InputService::InputService()
	{
		TalonLog("InputService started.\n Input devices:\n");
		
		InputDevice::Kind* kind = s_inputDeviceKinds;
		while (kind->Name != nullptr)
		{
			char line[MAX_PATH];
			sprintf(line, "\t%s\n", kind->Name);
			TalonLog(line);

			auto newDevices = kind->Enumerator();
			m_devices.insert(m_devices.end(), newDevices.begin(), newDevices.end());

			++kind;
		};
	}

	void InputService::Update()
	{
		for (auto i = m_devices.begin(); i != m_devices.end(); ++i)
			(*i)->PollForUpdates();
	}

	InputDevice::Kind InputService::s_inputDeviceKinds[] = {
#if TALON_WINDOWS
		XInputDevice::Kind,
		RawInputDevice::Kind,
#endif
		{ nullptr, nullptr }
	};
}