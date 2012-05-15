
#pragma once

#include <Talon/TalonPublic.h>

#if TALON_GRAPHICS == TALON_GRAPHICS_DIRECT3D11
#include <Talon/Graphics/Direct3D11/D3D11IndexBuffer.h>
#elif TALON_GRAPHICS == TALON_GRAPHICS_OPENGL
#include <Talon/Graphics/OpenGL/GLIndexBuffer.h>
#endif

namespace Talon
{
#if TALON_GRAPHICS == TALON_GRAPHICS_DIRECT3D11
	class TalonApi IndexBuffer : public D3D11IndexBuffer
	{
	public:
		typedef D3D11IndexBuffer Base;

	private:
#include <Talon/Graphics/Generated/IndexBuffer.h>
	};
#elif TALON_GRAPHICS == TALON_GRAPHICS_OPENGL
	class TalonApi IndexBuffer : public GLIndexBuffer
	{
	public:
		typedef GLIndexBuffer Base;

	private:
#include <Talon/Graphics/Generated/IndexBuffer.h>
	};
#endif
}