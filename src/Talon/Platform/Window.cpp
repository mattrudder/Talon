
#include "TalonPrefix.h"
#include <Talon/Platform/Window.h>
#include <Talon/Graphics/RenderDevice.h>

namespace Talon
{
	const std::string& Window::GetTitle() const
	{
		return m_title;
	}

	void Window::SetTitle(const std::string& value)
	{
		m_title = value;
	}

	int Window::GetWidth() const
	{
		return m_width;
	}

	void Window::SetWidth(int value)
	{
		m_width = value;
	}

	int Window::GetHeight() const
	{
		return m_height;
	}

	void Window::SetHeight(int value)
	{
		m_height = value;
	}

	std::shared_ptr<RenderDevice> Window::GetRenderDevice() const
	{
		return m_renderDevice;
	}

	void Window::SetRenderDevice(std::shared_ptr<RenderDevice> value)
	{
		m_renderDevice = value;
	}

	void Window::OnResized(int width, int height)
	{
		Resized(width, height);
	}

	void Window::OnClosed()
	{
		Closed();
	}

	void Window::OnCreated()
	{
		m_renderDevice = std::make_shared<RenderDevice>(this);
		Created();
	}

	void Window::OnDestroyed()
	{
		Destroyed();
	}
}