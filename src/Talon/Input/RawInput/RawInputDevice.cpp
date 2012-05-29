
#include "TalonPrefix.h"
#include "Input/RawInput/RawInputDevice.h"
#include "Input/RawInput/RawInputKeyboardDevice.h"
#include "Input/RawInput/RawInputMouseDevice.h"

namespace Talon
{
	std::regex RawInputDevice::s_rgDeviceId("\\{2}\?\\([^#]+)#([^#]+)#([^#]+)#");
    InputDevice::Kind RawInputDevice::Kind = { "RawInput", RawInputDevice::Enumerate };

    std::vector<std::shared_ptr<InputDevice>> RawInputDevice::Enumerate()
    {
        std::vector<std::shared_ptr<InputDevice>> devices;

        u32 deviceCount;
        PRAWINPUTDEVICELIST deviceList;
        if (GetRawInputDeviceList(nullptr, &deviceCount, sizeof(RAWINPUTDEVICELIST)) == 0)
        {
            deviceList = (PRAWINPUTDEVICELIST) malloc(sizeof(RAWINPUTDEVICELIST) * deviceCount);
            GetRawInputDeviceList(deviceList, &deviceCount, sizeof(RAWINPUTDEVICELIST));

            for (u32 i = 0; i < deviceCount; ++i)
            {
				u32 deviceInfoSize;
				HANDLE hDevice = deviceList[i].hDevice;
				if (GetRawInputDeviceInfoW(hDevice, RIDI_DEVICEINFO, nullptr, &deviceInfoSize) == 0)
				{
					RID_DEVICE_INFO deviceInfo = { 0 };
					deviceInfo.cbSize = sizeof(RID_DEVICE_INFO);

					if (GetRawInputDeviceInfoW(hDevice, RIDI_DEVICEINFO, &deviceInfo, &deviceInfoSize))
						m_deviceInfo = deviceInfo;
				}

				std::smatch matches;

				if (regex_match(deviceList[i].)

                if (deviceList[i].dwType == RIM_TYPEKEYBOARD)
                    devices.push_back(std::make_shared<RawInputKeyboardDevice>(deviceList[i].hDevice));
                else if (deviceList[i].dwType == RIM_TYPEMOUSE)
                    devices.push_back(std::make_shared<RawInputMouseDevice>(deviceList[i].hDevice));
            }

            free(deviceList);
        }

        return devices;
    }

    RawInputDevice::~RawInputDevice()
    {

    }

    RawInputDevice::RawInputDevice(HANDLE hDevice)
        : m_deviceHandle(hDevice)
    {
		u32 deviceInfoSize;
		
		if (GetRawInputDeviceInfoW(hDevice, RIDI_DEVICENAME, nullptr, &deviceInfoSize) == 0)
		{
			wchar_t* deviceName = (wchar_t*) malloc(deviceInfoSize * sizeof(wchar_t));
			if (GetRawInputDeviceInfoW(hDevice, RIDI_DEVICENAME, deviceName, &deviceInfoSize))
				m_deviceName = convert(deviceName);
		}

		if (GetRawInputDeviceInfoW(hDevice, RIDI_DEVICEINFO, nullptr, &deviceInfoSize) == 0)
		{
			RID_DEVICE_INFO deviceInfo = { 0 };
			deviceInfo.cbSize = sizeof(RID_DEVICE_INFO);

			if (GetRawInputDeviceInfoW(hDevice, RIDI_DEVICEINFO, &deviceInfo, &deviceInfoSize))
				m_deviceInfo = deviceInfo;
		}
    }

	void RawInputDevice::PollForUpdatesCore()
	{
	}
}