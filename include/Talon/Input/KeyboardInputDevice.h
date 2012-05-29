
#pragma once

#include <Talon/TalonPublic.h>
#include <Talon/Input/InputDevice.h>

namespace Talon
{
    class TalonApi KeyboardInputDevice : public InputDevice
    {
    public:
        virtual ~KeyboardInputDevice();

    protected:
        KeyboardInputDevice();

    private:
    };
}