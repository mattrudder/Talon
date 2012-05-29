
#pragma once
#include <Talon/TalonPublic.h>
#include <Talon/Input/InputDevice.h>

#include <vector>
#include <functional>

namespace Talon
{
	class TalonApi InputService
	{
	public:
		InputService();

#if TALON_WINDOWS
		void OnInput();
#endif

		void Update();

	private:
		static InputDevice::Kind s_inputDeviceKinds[];

		std::vector<std::shared_ptr<InputDevice>> m_devices;
	};
}