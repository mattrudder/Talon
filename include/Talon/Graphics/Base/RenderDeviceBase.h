
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
		inline bool IsInitialized() const { return m_initialized; }

		void BeginFrame();
		void EndFrame();

	protected:
		inline void SetInitialized(bool value) { m_initialized = value; }

	private:
		Window* m_window;
		bool m_initialized;
	};
}