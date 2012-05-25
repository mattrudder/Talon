
#include <Talon/TalonPublic.h>

// Precompiled header file for Talon Engine.
#include <nowide/convert.h>
using namespace nowide;

#if TALON_IOS
#elif TALON_MAC
#elif TALON_WINDOWS
#	define TalonLog(x) OutputDebugStringA(x)
#	define WIN32_LEAN_AND_MEAN // TODO: Define additional NO_* defines to slim down windows.h
#	define NOMINMAX
#	define PATH_MAX MAX_PATH
#	define NAME_MAX 255
#	include <wincodec.h>	// Windows Imaging Component (WIC)
#	include <wincodecsdk.h>
#	pragma comment(lib, "WindowsCodecs.lib")
#	include <atlbase.h> // For CComPtr
#	include <windows.h>
#	include <Talon/Platform/Win32/ComException.h>
#endif

#include "Graphics/GraphicsUtility.h"