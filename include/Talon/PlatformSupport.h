
#pragma once
#include <Talon/TalonPublic.h>

#if TALON_WINDOWS
#	include <Talon/Platforms/WindowsPlatformSupport.h>
#	include <Talon/Platforms/Windows/Win32Window.h>
#endif

namespace Talon
{
#if TALON_WINDOWS
	typedef PlatformSupportBase<WindowsPlatformSupport> PlatformSupport;
	typedef WindowBase<Win32Window> Window;
#else
#	error PlatformSupport is undefined for this platform.
#endif
}