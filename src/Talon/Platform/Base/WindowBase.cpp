
#include <Talon/Platform/Base/WindowBase.h>

#include <Talon/Graphics/RenderDevice.h>

namespace Talon
{
	WindowBase::WindowBase(std::wstring title, int width, int height)
	{
		m_title = title;
		m_width = width;
		m_height = height;
	}

	WindowBase::~WindowBase()
	{
	}

	void WindowBase::DoEvents()
	{
	}

	void WindowBase::OnResized(int width, int height)
	{
		Resized(width, height);
	}

	void WindowBase::OnClosed()
	{
		Closed();
	}

	void WindowBase::OnCreated()
	{
		Created();

		m_renderDevice = std::make_shared<RenderDevice>((Window *) this);
	}

	void WindowBase::OnDestroyed()
	{
		m_renderDevice.reset();

		Destroyed();
	}
}