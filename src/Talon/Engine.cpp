
#include "TalonPrefix.h"
#include <Talon/Engine.h>
#include <Talon/Input/InputManager.h>

#include <Talon/Platform/Window.h>
#include <Talon/Graphics/RenderDevice.h>
#include <Talon/Simulation.h>

#include <zlib.h>
#include <png.h>
#include <cairo.h>
#include <FreeImage.h>

namespace Talon
{
	Engine& Engine::Instance()
	{
		static Engine s_engine;
		return s_engine;
	}

	bool Engine::Initialize(std::shared_ptr<Simulation> sim)
	{
		CreateManagers();

		m_simulation = sim;

		char line[MAX_PATH];
		sprintf(line, "Talon version: %s\n", TALON_VERSION_STRING);
		TalonLog(line);

		sprintf(line, "zlib version: %s\n", zlibVersion());
		TalonLog(line);

		sprintf(line, "libpng version: %s\n", png_get_header_ver(nullptr));
		TalonLog(line);

		sprintf(line, "Cairo version: %s\n", cairo_version_string());
		TalonLog(line);

		sprintf(line, "FreeImage version: %s\n", FreeImage_GetVersion());
		TalonLog(line);
		FreeImage_Initialise();

		m_window = std::make_shared<Window>(m_simulation->GetTitle(), 1280, 720);
		if (!m_window->GetRenderDevice())
		{
			m_window = nullptr;
			return false;
		}

		m_window->Closed += [this] ()
		{
			m_running = false;
		};

		sim->Device = m_window->GetRenderDevice().get();

		m_running = true;


		return true;
	}

	void Engine::Shutdown()
	{
		m_window = nullptr;
		m_simulation = nullptr;

		m_inputManager = nullptr;

		FreeImage_DeInitialise();
	}

	void Engine::RunFrame()
	{
		m_window->DoEvents();

		auto device = m_window->GetRenderDevice();
		if (device)
		{
			device->BeginFrame();
			m_simulation->BeginFrame();

			m_simulation->EndFrame();
			device->EndFrame();
		}
	}

	void Engine::CreateManagers()
	{
		m_inputManager = std::make_shared<InputManager>();
	}

	Engine::Engine()
	{
	}

	Engine::~Engine()
	{
	}
}