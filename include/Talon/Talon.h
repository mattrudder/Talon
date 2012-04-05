
#include <Talon/TalonPublic.h>
#include <Talon/TalonMath.h>

// Platform-specific std function redirects
#if TALON_WINDOWS
#	define snprintf _snprintf
#	define stricmp _stricmp
#	define wcsicmp _wcsicmp
#elif TALON_MAC
#	define stricmp strcasecmp
#endif

// Platform-specific includes
#if TALON_MAC
#	include <CoreFoundation/CoreFoundation.h>
#elif TALON_IOS
#	define stricmp strcasecmp
#	include <CoreFoundation/CoreFoundation.h>
#elif TALON_WINDOWS
#	define WIN32_LEAN_AND_MEAN // TODO: Define additional NO_* defines to slim down windows.h
#	define NOMINMAX
#	define PATH_MAX MAX_PATH
#	define NAME_MAX 255
#	include <windows.h>
#endif