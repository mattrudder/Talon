#pragma once

#include "TalonTypes.h"
#include "TalonConfig.h"
#include "TalonVersion.h"
#include "TalonAssert.h"

#include "Exception.h"

#include <math.h>
#include <string>
#include <vector>
#include <memory>
#include <functional>

#if TALON_GRAPHICS == TALON_GRAPHICS_OPENGL
#	include <GL/glew.h>
#	if TALON_COMPILER_VENDOR == TALON_COMPILER_VENDOR_VS && (defined(BUILDING_TALON) || !defined(TALON_DLL))
#		pragma comment(lib, "OpenGL32.lib")
#	endif
#	if TALON_WINDOWS
#		include <GL/wglew.h>
#	elif TALON_MAC
#		include <OpenGL/gl.h>
#	endif
#elif TALON_GRAPHICS == TALON_GRAPHICS_D3D11
#	include <d3d11.h>
#	include <d3dcompiler.h>
#endif

// Placeholders for functions missing from the C++11 spec.
namespace std
{
	template<class T>
	auto cbegin(const T& t) -> decltype(t.cbegin()) { return t.cbegin(); }

	template<class T>
	auto cend(const T& t) -> decltype(t.cend()) { return t.cend(); }

	// Variadic template version of unique_ptr
	//template<typename T, typename ...Args>
	//std::unique_ptr<T> make_unique(Args&& ...args)
	//{
	//	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
	//}

	template<typename T>
	std::unique_ptr<T> make_unique() { return std::unique_ptr<T>(new T()); }
	template<typename T, typename A0>
	std::unique_ptr<T> make_unique(A0&& a0) { return std::unique_ptr<T>(new T(std::forward<A0>(a0))); }
	template<typename T, typename A0, typename A1>
	std::unique_ptr<T> make_unique(A0&& a0, A1&& a1) { return std::unique_ptr<T>(new T(std::forward<A0>(a0), std::forward<A1>(a1))); }
	template<typename T, typename A0, typename A1, typename A2>
	std::unique_ptr<T> make_unique(A0&& a0, A1&& a1, A2&& a2) { return std::unique_ptr<T>(new T(std::forward<A0>(a0), std::forward<A1>(a1), std::forward<A2>(a2))); }
	template<typename T, typename A0, typename A1, typename A2, typename A3>
	std::unique_ptr<T> make_unique(A0&& a0, A1&& a1, A2&& a2, A3&& a3) { return std::unique_ptr<T>(new T(std::forward<A0>(a0), std::forward<A1>(a1), std::forward<A2>(a2), std::forward<A3>(a3))); }
	template<typename T, typename A0, typename A1, typename A2, typename A3, typename A4>
	std::unique_ptr<T> make_unique(A0&& a0, A1&& a1, A2&& a2, A3&& a3, A4&& a4) { return std::unique_ptr<T>(new T(std::forward<A0>(a0), std::forward<A1>(a1), std::forward<A2>(a2), std::forward<A3>(a3), std::forward<A4>(a4))); }
	template<typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5>
	std::unique_ptr<T> make_unique(A0&& a0, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5) { return std::unique_ptr<T>(new T(std::forward<A0>(a0), std::forward<A1>(a1), std::forward<A2>(a2), std::forward<A3>(a3), std::forward<A4>(a4), std::forward<A5>(a5))); }
	template<typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
	std::unique_ptr<T> make_unique(A0&& a0, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6) { return std::unique_ptr<T>(new T(std::forward<A0>(a0), std::forward<A1>(a1), std::forward<A2>(a2), std::forward<A3>(a3), std::forward<A4>(a4), std::forward<A5>(a5), std::forward<A6>(a6))); }
	template<typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
	std::unique_ptr<T> make_unique(A0&& a0, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7) { return std::unique_ptr<T>(new T(std::forward<A0>(a0), std::forward<A1>(a1), std::forward<A2>(a2), std::forward<A3>(a3), std::forward<A4>(a4), std::forward<A5>(a5), std::forward<A6>(a6), std::forward<A7>(a7))); }
	template<typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
	std::unique_ptr<T> make_unique(A0&& a0, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7, A8&& a8) { return std::unique_ptr<T>(new T(std::forward<A0>(a0), std::forward<A1>(a1), std::forward<A2>(a2), std::forward<A3>(a3), std::forward<A4>(a4), std::forward<A5>(a5), std::forward<A6>(a6), std::forward<A7>(a7), std::forward<A8>(a8))); }
	template<typename T, typename A0, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
	std::unique_ptr<T> make_unique(A0&& a0, A1&& a1, A2&& a2, A3&& a3, A4&& a4, A5&& a5, A6&& a6, A7&& a7, A8&& a8, A9&& a9) { return std::unique_ptr<T>(new T(std::forward<A0>(a0), std::forward<A1>(a1), std::forward<A2>(a2), std::forward<A3>(a3), std::forward<A4>(a4), std::forward<A5>(a5), std::forward<A6>(a6), std::forward<A7>(a7), std::forward<A8>(a8), std::forward<A9>(a9))); }
}