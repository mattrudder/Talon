
#include <Talon/Engine.h>
#include <Talon/Platform/Window.h>
#include <Talon/Graphics/RenderDevice.h>

//#include <zlib.h>
//#include <png.h>
//#include <cairo.h>

namespace Talon
{
	void Engine::Initialize(const char* /*arguments*/)
	{
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