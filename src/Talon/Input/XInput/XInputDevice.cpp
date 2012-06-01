
#include "TalonPrefix.h"
#include "Input/XInput/XInputDevice.h"
#include <Talon/Input/InputDeviceButton.h>
#include <unordered_map>

namespace Talon
{
	u32 XInputDevice::c_maxDevices = 4;
	InputDevice::Kind XInputDevice::Kind = { "XInput", XInputDevice::Enumerate };

	struct tXInputToInputDeviceButton
	{
		u16 xinput;
		InputDeviceButton button;
	};

	struct tXInputToInputDeviceAxis
	{
		u16 xinput;
		InputDeviceButton button;
	};

	tXInputToInputDeviceButton xinputToInputDeviceMap[] =
	{
		{ XINPUT_GAMEPAD_DPAD_UP,	 InputDeviceButton::Up },
		{ XINPUT_GAMEPAD_DPAD_DOWN, InputDeviceButton::Down },
		{ XINPUT_GAMEPAD_DPAD_LEFT, InputDeviceButton::Left },
		{ XINPUT_GAMEPAD_DPAD_RIGHT, InputDeviceButton::Right },
		{ XINPUT_GAMEPAD_START, InputDeviceButton::Start },
		{ XINPUT_GAMEPAD_BACK, InputDeviceButton::Back },
		{ XINPUT_GAMEPAD_LEFT_THUMB, InputDeviceButton::LeftThumb },
		{ XINPUT_GAMEPAD_RIGHT_THUMB, InputDeviceButton::RightThumb },
		{ XINPUT_GAMEPAD_LEFT_SHOULDER, InputDeviceButton::LeftShoulder },
		{ XINPUT_GAMEPAD_RIGHT_SHOULDER, InputDeviceButton::RightShoulder },
		{ XINPUT_GAMEPAD_A, InputDeviceButton::Button0 },
		{ XINPUT_GAMEPAD_B, InputDeviceButton::Button1 },
		{ XINPUT_GAMEPAD_X, InputDeviceButton::Button2 },
		{ XINPUT_GAMEPAD_Y, InputDeviceButton::Button3 },
		{ 0, InputDeviceButton::None },
	};

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

	f32 XInputDevice::GetAxis(InputDeviceAxis axis) const
	{
		f32 value = 0;
		f32 max = 1;

		switch (axis)
		{
		case InputDeviceAxis::LeftX:
			value = m_state.Gamepad.sThumbLX;
			value += 32768;
			max = 65535;
			break;
		case InputDeviceAxis::LeftY:
			value = m_state.Gamepad.sThumbLY;
			value += 32768;
			max = 65535;
			break;
		case InputDeviceAxis::LeftZ:
			value = m_state.Gamepad.bLeftTrigger;
			max = 255;
			break;
		case InputDeviceAxis::RightX:
			value = m_state.Gamepad.sThumbRX;
			value += 32768;
			max = 65535;
			break;
		case InputDeviceAxis::RightY:
			value = m_state.Gamepad.sThumbRY;
			value += 32768;
			max = 65535;
			break;
		case InputDeviceAxis::RightZ:
			value = m_state.Gamepad.bRightTrigger;
			max = 255;
			break;
		}

		return value / max;
	}

	bool XInputDevice::GetButton(InputDeviceButton button) const
	{
		for (auto& i : xinputToInputDeviceMap)
		{
			if (i.button == button)
				return (m_state.Gamepad.wButtons & i.xinput) == i.xinput;
		}

		return false;
	}

	void XInputDevice::PollForUpdates()
	{
		m_lastState = m_state;

		SetIsConnected(XInputGetState(m_controllerId, &m_state) == ERROR_SUCCESS);

		if (m_state.Gamepad.wButtons != m_lastState.Gamepad.wButtons)
		{
			for (auto& i : xinputToInputDeviceMap)
			{
				bool oldState = (m_lastState.Gamepad.wButtons & i.xinput) == i.xinput;
				bool newState = (m_state.Gamepad.wButtons & i.xinput) == i.xinput;
				
				if (oldState == newState)
					continue;

				if (oldState)
					OnReleased(i.button);
				else
					OnPressed(i.button);
			}
		}
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