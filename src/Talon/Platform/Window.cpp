
#include <Talon/TalonPrefix.h>
#include <Talon/Platform/Window.h>
#include <Talon/Graphics/RenderDevice.h>

namespace Talon
{
	Window::Window(std::string title, int width, int height)
		: Base(title, width, height)
	{
		SetRenderDevice(std::make_shared<RenderDevice>(this));
	}

	Window::~Window()
	{
	}

	void Window::OnResized(int width, int height)
	{
		Base::OnResized(width, height);
	}

	void Window::OnClosed()
	{
		Base::OnClosed();
	}

	void Window::OnCreated()
	{
		Base::OnCreated();
	}

	void Window::OnDestroyed()
	{
		Base::OnDestroyed();
	}
}