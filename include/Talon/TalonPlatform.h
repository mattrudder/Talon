
#pragma once

#ifdef __MACH__
#include <TargetConditionals.h>
#endif

#define TALON_PLATFORM_MAC 1
#define TALON_PLATFORM_IOS 2
#define TALON_PLATFORM_WINDOWS 3

#define TALON_MAC 0
#define TALON_IOS 0
#define TALON_WINDOWS 0

#define TALON_COMPILER_VENDOR_GCC 1
#define TALON_COMPILER_VENDOR_VS 2

#define TALON_COMPILER_VERSION_MSVC2005 1400
#define TALON_COMPILER_VERSION_MSVC2008 1500
#define TALON_COMPILER_VERSION_MSVC2010 1600
#define TALON_COMPILER_VERSION_MSVC2012 1700

#define TALON_GRAPHICS_D3D11 1
#define TALON_GRAPHICS_OPENGL 2
#define TALON_GRAPHICS_OPENGLES1 3
#define TALON_GRAPHICS_OPENGLES2 4

#define TALON_GRAPHICS TALON_GRAPHICS_OPENGL

#define TALON_MATH_FPU 1
#define TALON_MATH_SSE2 2
#define TALON_MATH_EIGEN 3

#define TALON_MATH TALON_MATH_EIGEN

#define TALON_DEBUG 0

#if defined(_MSC_VER)
#	define TALON_PLATFORM TALON_PLATFORM_WINDOWS
#	define TALON_COMPILER_VERSION _MSC_VER
#	define TALON_COMPILER_VENDOR TALON_COMPILER_VENDOR_VS
#	undef TALON_WINDOWS
#	define TALON_WINDOWS 1
#	if TALON_COMPILER_VERSION == TALON_COMPILER_VERSION_MSVC2005
#		define __VERSION__ "Microsoft Visual C++ 8.0"
#	elif TALON_COMPILER_VERSION == TALON_COMPILER_VERSION_MSVC2008
#		define __VERSION__ "Microsoft Visual C++ 9.0"
#	elif TALON_COMPILER_VERSION == TALON_COMPILER_VERSION_MSVC2010
#		define __VERSION__ "Microsoft Visual C++ 10.0"
#	elif TALON_COMPILER_VERSION == TALON_COMPILER_VERSION_MSVC2012
#		define __VERSION__ "Microsoft Visual C++ 11.0"
#	else
#		define __VERSION__ "Unknown Windows Compiler"
#	endif
#	ifdef _DEBUG
#		undef TALON_DEBUG
#		define TALON_DEBUG 1
#	endif
// Talon Math library support detection
// TODO: Add support for alternative vector processing implementations.
#	if _M_IX86_FP == 2
//#		undef TALON_MATH
//#		define TALON_MATH TALON_MATH_SSE2
#	endif
#elif defined(__MACH__)
#	define TALON_COMPILER_VERSION __GNUC__
#	define TALON_COMPILER_VENDOR TALON_COMPILER_VENDOR_GCC
#	if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE
#		define TALON_PLATFORM TALON_PLATFORM_IOS
#		undef TALON_IOS
#		define TALON_IOS 1
#		undef TALON_GRAPHICS
#		define TALON_GRAPHICS TALON_GRAPHICS_OPENGLES2
#	else
#		define TALON_PLATFORM TALON_PLATFORM_MAC
#		undef TALON_MAC
#		define TALON_MAC 1
#	endif
// TODO: Not sure off the top of my head what the default Mac debug define is...
#	ifdef _DEBUG
#		undef TALON_DEBUG
#		define TALON_DEBUG 1
#	endif
// Talon Math library support detection
#	if __SSE2__
//#		undef TALON_MATH
//#		define TALON_MATH TALON_MATH_SSE2
#	endif
#else
#	error Platform not officially supported.
#endif

// Shared Library Export Attributes
#ifdef TALON_DLL // Building Talon as a shared library.
#	if TALON_PLATFORM == TALON_PLATFORM_WINDOWS
#		ifdef BUILDING_TALON
#			ifdef __GNUC__
#				define TalonApi __attribute__((dllexport))
#			else
#				define TalonApi __declspec(dllexport)
#			endif
#		else
#			ifdef __GNUC__
#				define TalonApi __attribute__((dllimport))
#			else
#				define TalonApi __declspec(dllimport)
#			endif
#		endif
#		define TalonPluginApi __declspec(dllexport)
#		define TalonPrivate
#	else
#		if __GNUC__ >= 4
#			define TalonApi __attribute__ ((visibility("default")))
#			define TalonPluginApi __attribute__ ((visibility("default")))
#			define TalonPrivate  __attribute__ ((visibility("hidden")))
#		else
#			define TalonApi
#			define TalonPrivate
#		endif
#	endif
#else // Building Talon as a static library.
#	define TalonApi
#	define TalonPrivate
#endif

#if TALON_COMPILER_VENDOR == TALON_COMPILER_VENDOR_VS
#	define TALON_ALIGN(a, decl) _declspec(align(a)) decl 
#elif TALON_COMPILER_VENDOR == TALON_COMPILER_VENDOR_GCC
#	define TALON_ALIGN(a, decl) decl __attribute__((aligned(a)))
#endif

#if TALON_WINDOWS
#   define _HAS_EXCEPTIONS 0
#   pragma warning(disable : 4251)	// STL usage in DLL-interface class
#   pragma warning(disable : 4275)	// non dll-interface used as base for dll-interface
#endif

