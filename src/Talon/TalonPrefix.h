
#define NOMINMAX
#include <Talon/TalonPublic.h>

#ifdef TALON_ALLOCATORS_ONLY
#define malloc(x) \
	nullptr; \
	std::static_assert(false, "Invalid memory allocation method! Use Talon allocators only!"); \
	TALON_ASSERT(false && "Invalid memory allocation method! Use Talon allocators only!");

namespace {
	void* operator new(size_t size);
}
#endif

// Precompiled header file for Talon Engine.
#include <nowide/convert.h>
using namespace nowide;

#if TALON_IOS
#   define TalonLog(x) printf("%s", x)
#elif TALON_MAC
#   define TalonLog(x) printf("%s", x)
#elif TALON_WINDOWS
#	define TalonLog(x) OutputDebugStringA(x)
#	define WIN32_LEAN_AND_MEAN // TODO: Define additional NO_* defines to slim down windows.h
#	define PATH_MAX MAX_PATH
#	define NAME_MAX 255
#	include <atlbase.h> // For CComPtr
#	include <windows.h>
#	include <Talon/Platform/Win32/ComException.h>
#endif

#include "Graphics/GraphicsUtility.h"