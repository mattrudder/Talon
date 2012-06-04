
#pragma once
#include <Talon/TalonPublic.h>
#include <Talon/Input/InputDevice.h>
#include <Talon/Input/InputDeviceType.h>
#include <regex>

namespace Talon
{
	struct RawInputEventArgs;

    class RawInputDevice
    {
    public:
        static InputDevice::Kind Kind;

        static std::vector<std::shared_ptr<InputDevice>> Enumerate();

		inline HANDLE GetHandle() const { return m_deviceHandle; }

		virtual void ProcessEvent(RawInputEventArgs& e) = 0;
        virtual ~RawInputDevice();

    protected:
		RawInputDevice(HANDLE hDevice);

	private:
        HANDLE m_deviceHandle;
		RID_DEVICE_INFO m_deviceInfo;
		std::string m_deviceName;
		
		static std::regex s_rgDeviceId;
		static std::regex s_rgRdpDevices;
		static std::vector<RAWINPUT> s_polledInputs;
    };
}