
#include <Talon/TalonPublic.h>
#include <Talon/PlatformSupport.h>
#include <Talon/GraphicsSupport.h>

namespace Talon
{
	class Engine
	{
	public:
		void initialize();
		void shutdown();

	private:
		static PlatformSupport s_platform;
		static GraphicsSupport s_graphics;

		PlatformSupport::WindowType* m_window;
	};
}