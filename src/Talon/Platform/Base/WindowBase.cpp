
#include <Talon/TalonPrefix.h>
#include <Talon/Platform/Base/WindowBase.h>
#include <Talon/Graphics/RenderDevice.h>

namespace Talon
{
// TODO: Code generation should mark unused parameters as such.
#pragma warning(push)
#pragma warning(disable : 4100)
	WindowBase::WindowBase(std::string title, int width, int height)
		: m_title(title)
		, m_width(width)
		, m_height(height)
		, m_renderDevice(nullptr)
	{
	}
#pragma warning(pop)
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


	void WindowBase::SetWidth(int value)
	{
		m_width = value;
	}

	int WindowBase::GetHeight() const
	{
		return m_height;
	}


	void WindowBase::SetHeight(int value)
	{
		m_height = value;
	}

	std::shared_ptr<RenderDevice> WindowBase::GetRenderDevice() const
	{
		return m_renderDevice;
	}


	void WindowBase::SetRenderDevice(std::shared_ptr<RenderDevice> value)
	{
		m_renderDevice = value;
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