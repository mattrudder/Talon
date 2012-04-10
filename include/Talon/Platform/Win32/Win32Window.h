
#pragma once
#include <Talon/TalonPublic.h>
#include <Talon/Platform/Base/WindowBase.h>

namespace Talon { namespace Win32
{
	struct WindowClass;

	class TalonApi Win32Window : public WindowBase
	{
	public:
		Win32Window(std::wstring title, U32 width, U32 height);
		virtual ~Win32Window();

	public:
		void DoEvents();

	private:
		static LRESULT CALLBACK TalonWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

		static const WindowClass* GetOrRegisterClass();

	private:
		static std::unique_ptr<WindowClass> s_windowClass;

		HWND m_hWnd;
	};
}}