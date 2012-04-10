
#include <Talon/Platform/Base/WindowBase.h>

namespace Talon
{
	WindowBase::WindowBase(std::wstring title, U32 width, U32 height)
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

	void WindowBase::OnResized(U32 width, U32 height)
	{
		Resized(width, height);
	}

	void WindowBase::OnClosed()
	{
		Closed();
	}
}