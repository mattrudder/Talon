
#pragma once
#include <Talon/TalonPublic.h>
#include <Talon/Platform/Base/WindowBase.h>

namespace Talon
{
	struct WindowClass;

	class TalonApi Win32Window : public WindowBase
	{
	public:
		Win32Window(std::wstring title, int width, int height);
		virtual ~Win32Window();

		inline HWND GetHandle() const { return m_hWnd; };

	public:
		void DoEvents();

	private:
		static LRESULT CALLBACK TalonWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

		static const WindowClass* GetOrRegisterClass();

	private:
		static std::unique_ptr<WindowClass> s_windowClass;

		HWND m_hWnd;
	};
}