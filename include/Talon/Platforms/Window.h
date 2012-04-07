
#pragma once
#include <Talon/TalonPublic.h>

#if TALON_WINDOWS
#include <Talon/Platforms/Win32/Win32Window.h>

namespace Talon
{
	class TalonApi Window : public Win32::Win32Window
	{
	public:
		typedef Win32::Win32Window Base;

		Window(std::wstring title, U32 width, U32 height);
		virtual ~Window();

	public:
		void DoEvents();
	};
}

#endif