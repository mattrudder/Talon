
#pragma once
#include <Talon/Input/GamepadInputDevice.h>
#include <Xinput.h>

namespace Talon
{
	class XInputDevice : public GamepadInputDevice
	{
	public:
		static Kind Kind;

		static std::vector<std::shared_ptr<InputDevice>> Enumerate();

		virtual float GetAxis(InputDeviceAxis axis) const;
		virtual bool GetButton(InputDeviceButton button) const;

		virtual void PollForUpdates();

		~XInputDevice();

	private:
		XInputDevice(u32 controllerId);

		static const u32 c_countDimensions = 3;
		static const u32 c_maxDevices = 4;

		float3 m_leftState;
		float3 m_rightState;

		u32 m_controllerId;
		XINPUT_STATE m_state;
		XINPUT_STATE m_lastState;
	};
}