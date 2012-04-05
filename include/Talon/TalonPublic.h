#pragma once

#include "TalonTypes.h"
#include "TalonConfig.h"
#include "TalonVersion.h"

#if TALON_IOS
#elif TALON_MAC
#elif TALON_WINDOWS
#	define WIN32_LEAN_AND_MEAN // TODO: Define additional NO_* defines to slim down windows.h
#	define NOMINMAX
#	define PATH_MAX MAX_PATH
#	define NAME_MAX 255
//#	include <comdef.h>
//#	include <windows.h>
#endif