
#pragma once

#include <Talon/TalonPublic.h>

#if TALON_GRAPHICS == TALON_GRAPHICS_DIRECT3D11
#include <Talon/Graphics/Direct3D11/D3D11VertexBuffer.h>
#elif TALON_GRAPHICS == TALON_GRAPHICS_OPENGL
#include <Talon/Graphics/OpenGL/GLVertexBuffer.h>
#endif

namespace Talon
{
#if TALON_GRAPHICS == TALON_GRAPHICS_DIRECT3D11
	class TalonApi VertexBuffer : public D3D11VertexBuffer
	{
	public:
		typedef D3D11VertexBuffer Base;

	private:
#include <Talon/Graphics/Generated/VertexBuffer.h>
	};
#elif TALON_GRAPHICS == TALON_GRAPHICS_OPENGL
	class TalonApi VertexBuffer : public GLVertexBuffer
	{
	public:
		typedef GLVertexBuffer Base;

	private:
#include <Talon/Graphics/Generated/VertexBuffer.h>
	};
#endif
}