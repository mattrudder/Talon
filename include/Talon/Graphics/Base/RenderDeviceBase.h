
#pragma once

#include <Talon/TalonPublic.h>

namespace Talon
{
	class Window;

	class TalonApi RenderDeviceBase
	{
	public:
		RenderDeviceBase(Window* window);
		virtual ~RenderDeviceBase();

		Window* GetWindow() const;
		bool IsInitialized() const;


		void BeginFrame();
		void EndFrame();

	protected:

		void SetWindow(Window* value);
		void SetInitialized(bool value);

	private:
		Window* m_window;
		bool m_initialized;
	};
}