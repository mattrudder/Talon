
#pragma once

#include <Talon/TalonPublic.h>
#include <Talon/Input/InputDevice.h>

namespace Talon
{
    class TalonApi KeyboardInputDevice : public InputDevice
    {
    public:
        virtual ~KeyboardInputDevice();

		//virtual bool GetKey(InputDeviceKey key) const = 0;

		delegate<KeyboardInputDevice, void (InputDeviceKey)> Pressed;
		delegate<KeyboardInputDevice, void (InputDeviceKey)> Released;

    protected:
        KeyboardInputDevice();

		void OnPressed(InputDeviceKey key);
		void OnReleased(InputDeviceKey key);

    private:
    };
}