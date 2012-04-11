
#include <Talon/Engine.h>
#include <Talon/Platform/Window.h>
#include <Talon/Graphics/RenderDevice.h>

namespace Talon
{
	void Engine::Initialize(const char* /*arguments*/)
	{
		m_running = true;
		m_window = std::make_shared<Window>(L"Talon", 800, 600);
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

		auto device = m_window->GetRenderDevice();
		device->BeginFrame();

		device->EndFrame();
	}
}