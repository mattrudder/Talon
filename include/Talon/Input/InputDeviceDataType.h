
#pragma once
#include <Talon/TalonPublic.h>

namespace Talon
{
    enum class InputDeviceDataType
    {
        None,
        Boolean,
        Float,
    };

	TalonApi std::ostream& operator<<(std::ostream& os, const InputDeviceDataType& e);
}