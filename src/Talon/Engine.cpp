
#include "TalonPrefix.h"
#include <Talon/Engine.h>
#include <Talon/ComponentRegistry.h>
#include <Talon/Platform/Platform.h>
#include <Talon/Input/InputService.h>

#include <Talon/Platform/Window.h>
#include <Talon/Graphics/RenderDevice.h>
#include <Talon/Simulation.h>

#include <zlib.h>
#include <png.h>
#include <cairo.h>
#include <FreeImage.h>

namespace Talon
{
	Engine* Engine::Instance()
	{
		static Engine s_engine;
		return &s_engine;
	}

	bool Engine::Initialize(std::shared_ptr<Simulation> sim)
	{
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

		sprintf(line, "Game launched from: %s\n", Platform::GetEnginePath().c_str());
		TalonLog(line);

		Platform::SetWorkingPath(Platform::GetEnginePath());

		m_simulation = sim;
		m_window = std::make_shared<Window>(m_simulation->GetTitle(), 1280, 720);
		if (!m_window->GetRenderDevice())
		{
			m_window = nullptr;
			return false;
		}

		CreateServices();

		sim->Device = m_window->GetRenderDevice().get();
		m_simulation->Initialize();

		m_window->Closed += [this] ()
		{
			m_running = false;
		};

		m_running = true;

		return true;
	}

	void Engine::Shutdown()
	{
		m_window = nullptr;
		m_simulation = nullptr;

		DestroyServices();

		FreeImage_DeInitialise();
	}

	void Engine::RunFrame()
	{
		UpdateServices();

		m_window->DoEvents();

		m_inputService->Update();

		auto device = m_window->GetRenderDevice();
		if (device)
		{
			device->BeginFrame();
			m_simulation->BeginFrame();

			m_simulation->EndFrame();
			device->EndFrame();
		}
	}

	void Engine::CreateServices()
	{
		// Initialize managers
		m_inputService = std::make_shared<InputService>(m_window.get());
		m_inputService->Initialize();

		// Setup managers for automatic throttled updates.
		m_serviceUpdates.push_back(TimedUpdate(33, std::bind(&InputService::Update, m_inputService)));
	}

	void Engine::UpdateServices()
	{
		for (auto i = m_serviceUpdates.begin(); i != m_serviceUpdates.end(); ++i)
		{
			// TODO: Throttle updates.
			i->UpdateFunc();
		}
	}

	void Engine::DestroyServices()
	{
		m_inputService = nullptr;
	}

	Engine::Engine()
	{
	}

	Engine::~Engine()
	{
	}
}