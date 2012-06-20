
#include "TalonPrefix.h"
#include <Talon/Input/InputDevice.h>
#include <sstream>

namespace Talon
{
	std::atomic<u32> InputDevice::s_deviceIdGenerator;

	InputDevice::InputDevice(InputDeviceType type)
		: m_id(s_deviceIdGenerator++)
		, m_isConnected(false)
		, m_type(type)
	{
	}

	InputDevice::~InputDevice()
	{
	}

	void InputDevice::PollForUpdates()
	{
	}

	void InputDevice::SetIsConnected(bool value)
	{
		if (m_isConnected != value)
		{
			if (m_isConnected)
				Disconnected(this);
			else
				Connected(this);

			m_isConnected = value;
		}
	}

	void InputDevice::LogEvent(InputDeviceEvent e)
	{
		std::stringstream ss;
		ss << "INPUT: [Device " << e.deviceId << " (" << e.deviceType << ")]: " << e.channelType << " ";

		switch (e.channelType)
		{
		case InputDeviceChannel::Axis:
			ss << e.axisValue;
			break;
		case InputDeviceChannel::Button:
			ss << e.buttonValue;
			break;
		case InputDeviceChannel::Key:
			ss << e.keyValue;
			break;
        default:
            ss << "None";
            break;
		}

		ss << " = ";
		switch (e.dataType)
		{
		case InputDeviceDataType::Float:
			ss << e.floatValue;
			break;
		case InputDeviceDataType::Boolean:
			ss << e.boolValue;
			break;
        default:
            ss << "null";
            break;
		}
		ss << std::endl;

		TalonLog(ss.str().c_str());

		m_events.push(e);
	}
}