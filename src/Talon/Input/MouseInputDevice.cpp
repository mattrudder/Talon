
#include "TalonPrefix.h"
#include <Talon/Input/MouseInputDevice.h>

namespace Talon
{
    MouseInputDevice::~MouseInputDevice()
    {
    }

    MouseInputDevice::MouseInputDevice()
        : InputDevice(InputDeviceType::Mouse)
    {
    }

	void MouseInputDevice::OnMouseMoved(i32 x, i32 y)
	{
		MouseMoved(x, y);
	}

	void MouseInputDevice::OnMouseDown(InputDeviceButton button)
	{
		MouseDown(button);
	}

	void MouseInputDevice::OnMouseUp(InputDeviceButton button)
	{
		MouseUp(button);
	}
}