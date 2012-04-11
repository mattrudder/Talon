
#pragma once

#include <Talon/TalonPublic.h>

#if TALON_GRAPHICS == TALON_GRAPHICS_D3D11
#include <Talon/Graphics/Direct3D11/D3D11RenderDevice.h>
#elif TALON_GRAPHICS == TALON_GRAPHICS_OPENGL
#include <Talon/Graphics/OpenGL/GLRenderDevice.h>
#endif

namespace Talon
{
#if TALON_GRAPHICS == TALON_GRAPHICS_D3D11
	class TalonApi RenderDevice : public D3D11RenderDevice
	{
	public:
		typedef D3D11RenderDevice Base;

		RenderDevice(Window* window);
		virtual ~RenderDevice();

	private:
	};
#elif TALON_GRAPHICS == TALON_GRAPHICS_OPENGL
	class TalonApi RenderDevice : public GLRenderDevice
	{
	public:
		typedef GLRenderDevice Base;

		RenderDevice(Window* window);
		virtual ~RenderDevice();

	private:
	};
#endif
}