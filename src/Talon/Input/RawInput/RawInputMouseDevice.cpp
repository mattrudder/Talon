
#include "TalonPrefix.h"
#include "Input/RawInput/RawInputMouseDevice.h"
#include "Input/RawInput/RawInputEventArgs.h"
#include <sstream>

namespace Talon
{
    RawInputMouseDevice::~RawInputMouseDevice()
    {

    }

	RawInputMouseDevice::RawInputMouseDevice(HANDLE hDevice)
		: RawInputDevice(hDevice)
	{
	}

	void RawInputMouseDevice::ProcessEvent(RawInputEventArgs& e)
	{
		if (!IsConnected())
			SetIsConnected(true);

		auto& mouseEvent = e.RawInputData->data.mouse;
		if (mouseEvent.lLastX != 0 || mouseEvent.lLastY != 0)
		{
			TALON_ASSERT(mouseEvent.usFlags == MOUSE_MOVE_RELATIVE);
			OnMouseMoved(mouseEvent.lLastX, mouseEvent.lLastY);
		}

		if (mouseEvent.ulButtons & RI_MOUSE_BUTTON_1_DOWN)
			OnMouseDown(InputDeviceButton::Button0);
		if (mouseEvent.ulButtons & RI_MOUSE_BUTTON_2_DOWN)
			OnMouseDown(InputDeviceButton::Button1);
		if (mouseEvent.ulButtons & RI_MOUSE_BUTTON_3_DOWN)
			OnMouseDown(InputDeviceButton::Button2);
		if (mouseEvent.ulButtons & RI_MOUSE_BUTTON_4_DOWN)
			OnMouseDown(InputDeviceButton::Button3);
		if (mouseEvent.ulButtons & RI_MOUSE_BUTTON_5_DOWN)
			OnMouseDown(InputDeviceButton::Button4);

		if (mouseEvent.ulButtons & RI_MOUSE_BUTTON_1_UP)
			OnMouseUp(InputDeviceButton::Button0);
		if (mouseEvent.ulButtons & RI_MOUSE_BUTTON_2_UP)
			OnMouseUp(InputDeviceButton::Button1);
		if (mouseEvent.ulButtons & RI_MOUSE_BUTTON_3_UP)
			OnMouseUp(InputDeviceButton::Button2);
		if (mouseEvent.ulButtons & RI_MOUSE_BUTTON_4_UP)
			OnMouseUp(InputDeviceButton::Button3);
		if (mouseEvent.ulButtons & RI_MOUSE_BUTTON_5_UP)
			OnMouseUp(InputDeviceButton::Button4);

		std::stringstream ss;
		bool isAbsolute = mouseEvent.usFlags & MOUSE_MOVE_ABSOLUTE;
		ss << "INPUT [Mouse]: (" << mouseEvent.lLastX << ", " << mouseEvent.lLastY << "): " << (isAbsolute ? "absolute" : "relative") << std::endl;
		
		//TalonLog(ss.str().c_str());
	}
}