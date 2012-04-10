
#include <Talon/Platform/Base/WindowBase.h>

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
}