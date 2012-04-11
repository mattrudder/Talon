
#include <Talon/Platform/Window.h>

namespace Talon
{
	Window::Window(std::wstring title, int width, int height)
		: Base(title, width, height)
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