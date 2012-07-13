
#include "TalonPrefix.h"
#include "Input/XInput/XInputDevice.h"
#include <Talon/Input/InputDeviceButton.h>
#include <unordered_map>

namespace Talon
{
	InputDevice::Kind XInputDevice::Kind =
	{
		"XInput",
		XInputDevice::Enumerate,
	};

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

	void FilterAnalog(float& x, float& y, float threshold, float max)
	{
		float magnitude = sqrt(x*x + y*y);

		float normX = x / magnitude;
		float normY = y / magnitude;

		float normMagnitude = 0;

		if (magnitude > threshold)
		{
			if (magnitude > max)
				magnitude = max;

			magnitude -= threshold;
			normMagnitude = magnitude / (max - threshold);

			x = normX * normMagnitude;
			y = normY * normMagnitude;
		}
		else
		{
			x = 0.0f;
			y = 0.0f;
		}
	}

	void FilterAnalog(float& z, float threshold, float max)
	{
		float magnitude = z;

		if (magnitude > threshold)
		{
			if (magnitude > max)
				magnitude = max;

			magnitude -= threshold;
			z = magnitude / (max - threshold);
		}
		else
		{
			z = 0.0f;
		}
	}

	float XInputDevice::GetAxis(InputDeviceAxis axis) const
	{
		switch (axis)
		{
		case InputDeviceAxis::LeftX:	return m_leftState.x;
		case InputDeviceAxis::LeftY:	return m_leftState.y;
		case InputDeviceAxis::LeftZ:	return m_leftState.z;
		case InputDeviceAxis::RightX:	return m_rightState.x;
		case InputDeviceAxis::RightY:	return m_rightState.y;
		case InputDeviceAxis::RightZ:	return m_rightState.z;
		}

		return 0;
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

		m_leftState = float3(m_state.Gamepad.sThumbLX, m_state.Gamepad.sThumbLY, m_state.Gamepad.bLeftTrigger);
		m_rightState = float3(m_state.Gamepad.sThumbRX, m_state.Gamepad.sThumbRY, m_state.Gamepad.bRightTrigger);

		FilterAnalog(m_leftState.x, m_leftState.y, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, 32767);
		FilterAnalog(m_rightState.x, m_rightState.y, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE, 32767);
		FilterAnalog(m_leftState.z, XINPUT_GAMEPAD_TRIGGER_THRESHOLD, 255);
		FilterAnalog(m_rightState.z, XINPUT_GAMEPAD_TRIGGER_THRESHOLD, 255);

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

		char log[255];
		sprintf(log, "Left Z: %g\n", m_leftState.z);
		TalonLog(log);
	}

	XInputDevice::~XInputDevice()
	{
	}

	XInputDevice::XInputDevice(u32 controllerId)
		: m_controllerId(controllerId)
	{
		XInputGetState(controllerId, &m_state);
	}
}