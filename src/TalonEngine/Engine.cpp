
#include <Talon/Engine.h>

namespace Talon
{
	PlatformSupport Engine::s_platform;
	GraphicsSupport Engine::s_graphics;

	void Engine::initialize()
	{
		m_window = s_platform.CreateWindow(800, 600);
	}

	void Engine::shutdown()
	{
	}
}