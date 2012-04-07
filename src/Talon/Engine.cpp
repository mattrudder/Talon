
#include <Talon/Engine.h>
#include <Talon/Platforms/Window.h>

namespace Talon
{
	void Engine::Initialize(const char* /*arguments*/)
	{
		m_running = true;
		m_window = make_unique<Window>(L"Talon", 800, 600);
		m_window->Closed += [this] ()
		{
			m_running = false;
		};
	}

	void Engine::Shutdown()
	{
	}

	void Engine::RunFrame()
	{
		m_window->DoEvents();
	}
}