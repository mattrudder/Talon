
#include "TalonPrefix.h"
#include <Talon/Input/InputDevice.h>
#include <sstream>

namespace Talon
{
	std::atomic<u32> InputDevice::s_deviceIdGenerator = 0;

	InputDevice::InputDevice(InputDeviceType type)
		: m_id(s_deviceIdGenerator++)
		, m_type(type)
		, m_isConnected(false)
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
		}
		ss << std::endl;

		TalonLog(ss.str().c_str());

		m_events.push(e);
	}
}