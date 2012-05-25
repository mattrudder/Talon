
#pragma once
#include <Talon/Input/InputDevice.h>
#include <Xinput.h>

namespace Talon
{
	class XInputDevice : public InputDevice
	{
	public:
		static Kind Kind;

		static std::vector<std::shared_ptr<InputDevice>> Enumerate();

		virtual void PollForUpdates();

		~XInputDevice();

	private:
		XInputDevice(u32 controllerId);

		static u32 c_maxDevices;
		u32 m_controllerId;
		XINPUT_STATE m_state;
	};
}