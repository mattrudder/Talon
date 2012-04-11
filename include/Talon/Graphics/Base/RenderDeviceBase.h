
#pragma once

#include <Talon/TalonPublic.h>

namespace Talon
{
	class Window;

	class TalonApi RenderDeviceBase	{
	public:
		RenderDeviceBase(Window* window);
		virtual ~RenderDeviceBase();

		inline Window* GetWindow() const { return m_window; }

		void BeginFrame();
		void EndFrame();

	private:
		Window* m_window;
	};
}