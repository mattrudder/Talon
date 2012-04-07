
#include <Talon/Platforms/Window.h>

namespace Talon
{
	Window::Window(std::wstring title, U32 width, U32 height)
#if TALON_WINDOWS
		: Win32Window(title, width, height)
#endif
	{
	}

	void Window::DoEvents()
	{
		Base::DoEvents();
	}

	Window::~Window()
	{
	}
}