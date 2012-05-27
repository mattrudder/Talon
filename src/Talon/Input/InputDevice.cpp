
#include "TalonPrefix.h"
#include <Talon/Input/InputDevice.h>

namespace Talon
{
	InputDevice::InputDevice(InputDeviceType type)
		: m_type(type)
	{
	}

	InputDevice::~InputDevice()
	{
	}

	void InputDevice::SetIsConnected(bool value)
	{
		if (m_isConnected != value)
		{
			if (m_isConnected)
				Disconnected();
			else
				Connected();

			m_isConnected = value;
		}
	}
}