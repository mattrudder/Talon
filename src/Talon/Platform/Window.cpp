
#include <Talon/Platform/Window.h>

namespace Talon
{
	Window::Window(std::wstring title, int width, int height)
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