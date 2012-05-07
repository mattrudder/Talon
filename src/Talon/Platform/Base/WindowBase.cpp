
#include <Talon/Platform/Base/WindowBase.h>

namespace Talon
{
	WindowBase::WindowBase(std::string title, int width, int height)
		: m_title(title)
		, m_width(width)
		, m_height(height)
	{
	}

	WindowBase::~WindowBase()
	{
	}

	const std::string& WindowBase::GetTitle() const
	{
		return m_title;
	}

	void WindowBase::SetTitle(const std::string& value)
	{
		m_title = value;
	}

	int WindowBase::GetWidth() const
	{
		return m_width;
	}

	int WindowBase::GetHeight() const
	{
		return m_height;
	}

	std::shared_ptr<RenderDevice> WindowBase::GetRenderDevice() const
	{
		return m_renderDevice;
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
	}

	void WindowBase::OnDestroyed()
	{
		Destroyed();
	}

}