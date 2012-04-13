
#pragma once

#include <Talon/TalonPublic.h>
#include <Talon/Graphics/Base/RenderDeviceBase.h>
#include <functional>

namespace Talon
{
	class TalonApi GLRenderDevice : public RenderDeviceBase
	{
	public:
		typedef RenderDeviceBase Base;

		GLRenderDevice(Window* window);
		virtual ~GLRenderDevice();

		void BeginFrame();
		void EndFrame();

	private:
		void WithContext(std::function<void()> fn);

	private:
#if TALON_WINDOWS
		HDC m_hDC;
		HGLRC m_hRC;
#endif

	};
}