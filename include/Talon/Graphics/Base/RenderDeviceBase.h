
#pragma once

#include <Talon/TalonPublic.h>

namespace Talon
{
	class Window;

	class TalonApi RenderDeviceBase
	{
	public:
		RenderDeviceBase(std::shared_ptr<Window> window);
		virtual ~RenderDeviceBase();

		std::shared_ptr<Window> GetWindow() const;
		bool GetInitialized() const;


		void BeginFrame();
		void EndFrame();

	protected:

	private:
		std::shared_ptr<Window> m_window;
		bool m_initialized;
	};
}