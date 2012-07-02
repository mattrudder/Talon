
#include "TalonPrefix.h"
#include <Talon/Engine.h>
#include <Talon/ComponentService.h>
#include <Talon/Platform/Platform.h>
#include <Talon/Input/InputService.h>

#include <Talon/Platform/Window.h>
#include <Talon/Graphics/RenderDevice.h>
#include <Talon/Simulation.h>

//#include <zlib.h>
//#include <png.h>
//#include <cairo.h>
#include <FreeImage.h>

// HACKS: Remove at once!
#include <Talon/Graphics/Texture.h>
#include <Talon/Graphics/SpriteBatch.h>
#ifdef TALON_USING_AWESOMIUM
#	include <Awesomium/WebConfig.h>
#	include <Awesomium/WebCore.h>
#	include <Awesomium/WebView.h>
#	include <Awesomium/STLHelpers.h>
#	include <Awesomium/BitmapSurface.h>
using namespace Awesomium;

Awesomium::WebView* g_myWebView = nullptr;
std::shared_ptr<Talon::Texture> g_myWebViewTexture;
std::shared_ptr<Talon::SpriteBatch> g_mySpriteBatch;
#endif

namespace Talon
{
	Engine* Engine::Instance()
	{
		static Engine s_engine;
		return &s_engine;
	}

	bool Engine::Initialize(std::shared_ptr<Simulation> sim)
	{
		char line[255];
		sprintf(line, "Talon version: %s\n", TALON_VERSION_STRING);
		TalonLog(line);

//		sprintf(line, "zlib version: %s\n", zlibVersion());
//		TalonLog(line);

//		sprintf(line, "libpng version: %s\n", png_get_header_ver(nullptr));
//		TalonLog(line);

//		sprintf(line, "Cairo version: %s\n", cairo_version_string());
//		TalonLog(line);

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

#ifdef TALON_USING_AWESOMIUM
		// HACKS: Remove at once!
		Awesomium::WebConfig cfg;
		m_webCore = WebCore::Initialize(cfg);
		g_myWebView = m_webCore->CreateWebView(1280, 720);
		g_myWebView->LoadURL(WebURL(WSLit("http://vyrso.com/")));
#endif
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
#ifdef TALON_USING_AWESOMIUM
		g_mySpriteBatch = nullptr;
		g_myWebView->Destroy();
		g_myWebViewTexture = nullptr;

		m_webCore = nullptr;
		Awesomium::WebCore::Shutdown();
#endif
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

#ifdef TALON_USING_AWESOMIUM
			// HACKS: Remove at once!
			m_webCore->Update();
			if (!g_myWebView->IsLoading())
			{

				if (!g_mySpriteBatch)
				{
					BitmapSurface* surface = (BitmapSurface*)g_myWebView->surface();
					if (surface)
					{
						g_mySpriteBatch = std::make_shared<SpriteBatch>(m_window->GetRenderDevice().get());
						g_myWebViewTexture = Texture::FromMemory(m_window->GetRenderDevice().get(), 1280, 720, BufferFormat::B8G8R8A8U, BufferUsage::Dynamic, surface->buffer(), "Awesomium Surface");
					}
				}
				else
				{
					BitmapSurface* surface = (BitmapSurface*)g_myWebView->surface();
					g_myWebViewTexture->Update(surface->buffer());
				}

				if (g_myWebViewTexture)
				{
					g_mySpriteBatch->Begin();
					g_mySpriteBatch->Draw(g_myWebViewTexture, 0, 0);
					g_mySpriteBatch->End();
				}
			}
#endif

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

		m_componentService = std::make_shared<ComponentService>();

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
		m_componentService = nullptr;
		m_inputService = nullptr;
	}

	Engine::Engine()
#ifdef TALON_USING_AWESOMIUM
		: m_webCore(nullptr)
#endif
	{
	}

	Engine::~Engine()
	{
	}
}