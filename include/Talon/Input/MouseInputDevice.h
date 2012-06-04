
#pragma once

#include <Talon/TalonPublic.h>
#include <Talon/Input/InputDevice.h>
#include <Talon/Input/InputDeviceButton.h>

namespace Talon
{
    class TalonApi MouseInputDevice : public InputDevice
    {
    public:
        virtual ~MouseInputDevice();

		delegate<MouseInputDevice, void(i32, i32)> MouseMoved;
		delegate<MouseInputDevice, void(InputDeviceButton)> MouseDown;
		delegate<MouseInputDevice, void(InputDeviceButton)> MouseUp;

    protected:
        MouseInputDevice();

		void OnMouseMoved(i32 x, i32 y);
		void OnMouseDown(InputDeviceButton button);
		void OnMouseUp(InputDeviceButton button);

    private:
    };
}