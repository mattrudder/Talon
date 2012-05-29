
#pragma once

#include <Talon/TalonPublic.h>
#include <Talon/Input/InputDevice.h>

namespace Talon
{
    class TalonApi MouseInputDevice : public InputDevice
    {
    public:
        virtual ~MouseInputDevice();

    protected:
        MouseInputDevice();

    private:
    };
}