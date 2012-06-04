
#pragma once
#include <Talon/TalonPublic.h>
#include <Talon/Input/InputDevice.h>

#include <vector>
#include <functional>

namespace Talon
{
	class Window;
	
	typedef std::vector<std::shared_ptr<InputDevice>> InputDeviceList;

	class TalonApi InputService
	{
	public:
		InputService(Window* window);

		inline Window* GetWindow() const { return m_window; }

#if TALON_WINDOWS
		void OnInput();
#endif

		delegate<InputService, void(InputDevice*)> DeviceConnected;
		delegate<InputService, void(InputDevice*)> DeviceDisconnected;

		void Initialize();
		void Update();

	protected:
		void OnDeviceConnected(InputDevice* device);
		void OnDeviceDisconnected(InputDevice* device);

	private:

		static InputDevice::Kind s_inputDeviceKinds[];

		
		std::vector<std::shared_ptr<InputDevice>> m_devices;

		Window* m_window;
	};
}