
#pragma once
#include <Talon/TalonPublic.h>
#include <Talon/PlatformSupportBase.h>
#include <Talon/Platforms/Windows/Win32Window.h>

namespace Talon
{
	/** Windows OS support policy for PlatformSupportImpl. */
	class WindowsPlatformSupport : public PlatformSupportBase<WindowsPlatformSupport, Win32Window>
	{
	private:
		Win32Window* CreateWindowCore(U32 width, U32 height);
	};
}