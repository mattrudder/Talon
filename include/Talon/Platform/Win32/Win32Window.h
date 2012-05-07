
#pragma once
#include <Talon/TalonPublic.h>
#include <Talon/Platform/Base/WindowBase.h>

namespace Talon
{
	struct WindowClass;

	class TalonApi Win32Window : public WindowBase
	{
	public:
		inline HWND GetHandle() const { return m_hWnd; };

	private:
		static LRESULT CALLBACK TalonWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

		static const WindowClass* GetOrRegisterClass();

	private:
		static std::unique_ptr<WindowClass> s_windowClass;

		HWND m_hWnd;

#include <Talon/Platform/Win32/Generated/Win32Window.h>
	};
}