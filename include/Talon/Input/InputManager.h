
#pragma once
#include <Talon/TalonPublic.h>
#include <Talon/Input/InputDevice.h>

#include <vector>
#include <functional>

namespace Talon
{
	class TalonApi InputManager
	{
	public:
		InputManager();

		void Update();

	private:
		static InputDevice::Kind s_inputDeviceKinds[];

		std::vector<std::shared_ptr<InputDevice>> m_devices;
	};
}