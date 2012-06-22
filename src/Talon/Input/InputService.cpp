
#include "TalonPrefix.h"
#include <Talon/Platform/Window.h>
#include <Talon/Input/InputService.h>

#if TALON_WINDOWS
#include "Input/XInput/XInputDevice.h"
#include "Input/RawInput/RawInputDevice.h"
#endif

#include <algorithm>
using namespace std;

namespace Talon
{
	InputService::InputService(Window* window)
		: m_window(window)
	{
	}

	void InputService::Initialize()
	{
		TalonLog("InputService started.\n Input devices:\n");

		InputDevice::Kind* kind = s_inputDeviceKinds;
		while (kind->Name != nullptr)
		{
			char line[255];
			sprintf(line, "\t%s\n", kind->Name);
			TalonLog(line);

			auto newDevices = kind->Enumerator();
			m_devices.insert(m_devices.end(), newDevices.begin(), newDevices.end());

			++kind;
		};

		for (auto device : m_devices)
		{
			device->Connected += [this](InputDevice* dev)
			{
				OnDeviceConnected(dev);
			};

			device->Disconnected += [this](InputDevice* dev)
			{
				OnDeviceDisconnected(dev);
			};
		}
	}

	void InputService::Update()
	{
		for (auto i = m_devices.begin(); i != m_devices.end(); ++i)
			(*i)->PollForUpdates();
	}

	void InputService::OnDeviceConnected(InputDevice* device)
	{
		DeviceConnected(device);
	}

	void InputService::OnDeviceDisconnected(InputDevice* device)
	{
		DeviceDisconnected(device);
	}

	InputDevice::Kind InputService::s_inputDeviceKinds[] = {
#if TALON_WINDOWS
		RawInputDevice::Kind,
		XInputDevice::Kind,
#endif
		{ nullptr, nullptr }
	};
}