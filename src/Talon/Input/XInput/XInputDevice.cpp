
#include "TalonPrefix.h"
#include "Input/XInput/XInputDevice.h"

namespace Talon
{
	u32 XInputDevice::c_maxDevices = 4;
	InputDevice::Kind XInputDevice::Kind = { "XInput", XInputDevice::Enumerate };

	std::vector<std::shared_ptr<InputDevice>> XInputDevice::Enumerate()
	{
		std::vector<std::shared_ptr<InputDevice>> devices;

		for (u32 i = 0; i < c_maxDevices; ++i)
		{
			// TODO: use make_shared?
			auto ptr = std::shared_ptr<XInputDevice>(new XInputDevice(i));
			devices.push_back(ptr);
		}

		return devices;
	}

	void XInputDevice::PollForUpdates()
	{
		SetIsConnected(XInputGetState(m_controllerId, &m_state) == ERROR_SUCCESS);

		//if (m_state.Gamepad.wButtons & VK_PAD_A)

		XINPUT_VIBRATION vib = { 0 };
		vib.wRightMotorSpeed = m_state.Gamepad.wButtons & VK_PAD_A ? 32768 : 0;
		XInputSetState(m_controllerId, &vib);
	}

	XInputDevice::~XInputDevice()
	{
	}

	XInputDevice::XInputDevice(u32 controllerId)
		: m_controllerId(controllerId)
	{
		SetIsConnected(XInputGetState(controllerId, &m_state) == ERROR_SUCCESS);
	}
}