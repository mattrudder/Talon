
#pragma once
#include <Talon/TalonPublic.h>
#include <Talon/Input/InputDeviceAxis.h>
#include <Talon/Input/InputDeviceButton.h>
#include <Talon/Input/InputDeviceChannel.h>
#include <Talon/Input/InputDeviceDataType.h>
#include <Talon/Input/InputDeviceKey.h>
#include <Talon/Input/InputDeviceType.h>

namespace Talon
{
    struct InputDeviceEvent
    {
        u32 deviceId;

        InputDeviceType deviceType;

        InputDeviceChannel channelType;
        union
        {
            InputDeviceAxis axisValue;
            InputDeviceButton buttonValue;
            InputDeviceKey keyValue;
        };

        InputDeviceDataType dataType;
        union
        {
            f32 floatValue;
            bool boolValue;
        };

		InputDeviceEvent(InputDeviceType type, InputDeviceAxis channel, f32 value)
			: deviceId(0)
			, deviceType(type)
			, channelType(InputDeviceChannel::Axis)
			, axisValue(channel)
			, dataType(InputDeviceDataType::Float)
			, floatValue(value)
		{
		}

		InputDeviceEvent(InputDeviceType type, InputDeviceButton channel, bool value)
			: deviceId(0)
			, deviceType(type)
			, channelType(InputDeviceChannel::Button)
			, buttonValue(channel)
			, dataType(InputDeviceDataType::Boolean)
			, boolValue(value)
		{
		}

		InputDeviceEvent(InputDeviceType type, InputDeviceButton channel, f32 value)
			: deviceId(0)
			, deviceType(type)
			, channelType(InputDeviceChannel::Button)
			, buttonValue(channel)
			, dataType(InputDeviceDataType::Float)
			, floatValue(value)
		{
		}

		InputDeviceEvent(InputDeviceType type, InputDeviceKey channel, bool value)
			: deviceId(0)
			, deviceType(type)
			, channelType(InputDeviceChannel::Key)
			, keyValue(channel)
			, dataType(InputDeviceDataType::Boolean)
			, boolValue(value)
		{
		}
    };
}