
#pragma once
#include <Talon/TalonPublic.h>
#include <Talon/Input/InputDevice.h>
#include <regex>

namespace Talon
{
    class RawInputDevice
    {
    public:
        static InputDevice::Kind Kind;

        static std::vector<std::shared_ptr<InputDevice>> Enumerate();

		inline HANDLE GetHandle() const { return m_deviceHandle; }

        virtual ~RawInputDevice();

    protected:
        RawInputDevice(HANDLE hDevice);

		void PollForUpdatesCore();

	private:
        HANDLE m_deviceHandle;
		RID_DEVICE_INFO m_deviceInfo;
		std::string m_deviceName;
		//\\{2}\?\\([^#]+)#([^#]+)#([^#]+)#
		static std::regex s_rgDeviceId;
    };
}