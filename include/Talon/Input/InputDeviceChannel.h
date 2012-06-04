
#pragma once
#include <Talon/TalonPublic.h>

namespace Talon
{
    enum class InputDeviceChannel
    {
        None,
        Axis,
        Button,
        Key
    };

	TalonApi std::ostream& operator<<(std::ostream& os, const InputDeviceChannel& e);
}