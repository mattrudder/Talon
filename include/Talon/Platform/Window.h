
#pragma once

#include <Talon/TalonPublic.h>

#if TALON_WINDOWS
#include <Talon/Platform/Win32/Win32Window.h>
#elif TALON_MAC
#include <Talon/Platform/Mac/MacWindow.h>
#endif

namespace Talon
{
#if TALON_WINDOWS
	class TalonApi Window : public Win32Window
	{
	public:
		typedef Win32Window Base;

		Window(std::wstring title, int width, int height);
		virtual ~Window();

	public:
		void DoEvents();
	};
#elif TALON_MAC
	class TalonApi Window : public MacWindow
	{
	public:
		typedef MacWindow Base;

		Window(std::wstring title, int width, int height);
		virtual ~Window();

	public:
		void DoEvents();
	};
#endif
}

