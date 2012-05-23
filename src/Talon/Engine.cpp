
#include "TalonPrefix.h"
#include <Talon/Engine.h>
#include <Talon/Platform/Window.h>
#include <Talon/Graphics/RenderDevice.h>
#include <Talon/Simulation.h>

//#include <zlib.h>
//#include <png.h>
//#include <cairo.h>

namespace Talon
{
	bool Engine::Initialize(std::shared_ptr<Simulation> sim)
	{
		try
		{
			m_simulation = sim;

//		char line[MAX_PATH];
//		sprintf_s(line, "Talon version: %s\n", TALON_VERSION_STRING);
//		OutputDebugStringA(line);
//
//		sprintf_s(line, "zlib version: %s\n", zlibVersion());
//		OutputDebugStringA(line);
//
//		sprintf_s(line, "libpng version: %s\n", png_get_header_ver(nullptr));
//		OutputDebugStringA(line);
//
//		sprintf_s(line, "Cairo version: %s\n", cairo_version_string());
//		OutputDebugStringA(line);

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
		}
		catch (std::exception& e)
		{
			// TODO: Better error reporting.
#if TALON_WINDOWS
			OutputDebugString(convert(e.what()).c_str());
#endif
			return false;
		}

		return true;
	}

	void Engine::Shutdown()
	{
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
}