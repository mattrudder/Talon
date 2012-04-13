
#include <Talon/Graphics/OpenGL/GLRenderDevice.h>
#include <Talon/Platform/Window.h>

#include <GL/glew.h>
#if TALON_WINDOWS
#include <GL/wglew.h>
#endif

namespace Talon
{
#if TALON_WINDOWS
	class GLContext
	{
	public:
		GLContext(HDC hDC, HGLRC hRC)
			: m_hDC(hDC)
			, m_hRC(hRC)
		{
			wglMakeCurrent(m_hDC, m_hRC);
		}
		~GLContext()
		{
			wglMakeCurrent(m_hDC, nullptr);
		}

	private:
		HDC m_hDC;
		HGLRC m_hRC;
	};

	bool SetPixelFormat(HDC hDC)
	{
		int pixelFormat;

		static PIXELFORMATDESCRIPTOR pfd = {0};
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cDepthBits = 32;
		pfd.iLayerType = PFD_MAIN_PLANE;

		pixelFormat = ChoosePixelFormat(hDC, &pfd);
		if (pixelFormat == 0)
			return false;
		if (!::SetPixelFormat(hDC, pixelFormat, &pfd))
			return false;

		return true;
	}
#endif

	GLRenderDevice::GLRenderDevice(Window* window)
		: RenderDeviceBase(window)
	{
#if TALON_WINDOWS
		HWND hWnd = window->GetHandle();
		m_hDC = ::GetDC(hWnd);

		if (SetPixelFormat(m_hDC))
		{
			HGLRC tempContext = wglCreateContext(m_hDC);
			wglMakeCurrent(m_hDC, tempContext);

			char line[MAX_PATH];
			glewExperimental = GL_TRUE;
			if (glewInit() == GLEW_OK)
			{
				sprintf_s(line, "GLEW version %s\n", glewGetString(GLEW_VERSION));
				OutputDebugStringA(line);
			}

			int attributes[] = 
			{
				WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
				WGL_CONTEXT_MINOR_VERSION_ARB, 0,
				WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
				0
			};

			if (WGLEW_ARB_create_context)
			{
				m_hRC = wglCreateContextAttribsARB(m_hDC, 0, attributes);
				wglMakeCurrent(nullptr, nullptr);
				wglDeleteContext(tempContext);

				wglMakeCurrent(m_hDC, m_hRC);
				sprintf_s(line, "OpenGL Version: %s\n", glGetString(GL_VERSION));
				OutputDebugStringA(line);
				wglMakeCurrent(nullptr, nullptr);
			}
			else
			{
				// Only GL 2.1 is supported
				OutputDebugString(L"OpenGL 3.2 not supported! Falling back to OpenGL 2.1.\n");
				m_hRC = tempContext;
			}

			SetInitialized(true);
		}
#endif

		if (IsInitialized())
		{
			WithContext([window]
			{
				glClearColor(0.392156862745098f, 0.5843137254901961f, 0.9294117647058824f, 1.0f);
				glViewport(0, 0, window->GetWidth(), window->GetHeight());
			});

			window->Resized += [this](int width, int height)
			{
				WithContext([width, height]()
				{
					glViewport(0, 0, width, height);
				});
			};
		}
	}

	GLRenderDevice::~GLRenderDevice()
	{
#if TALON_WINDOWS
		wglMakeCurrent(m_hDC, nullptr);
		wglDeleteContext(m_hRC);
		::ReleaseDC(GetWindow()->GetHandle(), m_hDC);
#endif
	}

	void GLRenderDevice::BeginFrame()
	{
#if TALON_WINDOWS
		wglMakeCurrent(m_hDC, m_hRC);
#endif

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void GLRenderDevice::EndFrame()
	{
#if TALON_WINDOWS
		SwapBuffers(m_hDC);
		ValidateRect(GetWindow()->GetHandle(), nullptr);
		wglMakeCurrent(m_hDC, nullptr);
#endif
	}

	void GLRenderDevice::WithContext(std::function<void()> fn)
	{
#if TALON_WINDOWS
		GLContext context(m_hDC, m_hRC);
#endif
		fn();
	}
}