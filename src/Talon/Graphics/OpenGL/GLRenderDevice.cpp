
#include <Talon/Graphics/OpenGL/GLRenderDevice.h>
#include <Talon/Platform/Window.h>
#if TALON_WINDOWS
#include <GL/GL.h>
#endif

namespace Talon
{
#if TALON_WINDOWS
	void SetPixelFormat(HDC hDC)
	{
		int pixelFormat;

		static PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW |
			PFD_SUPPORT_OPENGL |
			PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			32,						// color buffer
			0, 0, 0, 0, 0, 0,
			0, 0,
			0, 0, 0, 0, 0,
			16,						// depth buffer
			0,
			0,
			0,
			0,
			0, 0, 0
		};

		pixelFormat = ChoosePixelFormat(hDC, &pfd);
		::SetPixelFormat(hDC, pixelFormat, &pfd);
	}
#endif

	GLRenderDevice::GLRenderDevice(Window* window)
		: RenderDeviceBase(window)
	{
#if TALON_WINDOWS
		HWND hWnd = window->GetHandle();
		m_hDC = ::GetDC(hWnd);
		SetPixelFormat(m_hDC);

		m_hRC = wglCreateContext(m_hDC);

		RECT rClient = { 0 };
		GetClientRect(hWnd, &rClient);
		WithContext([&rClient]
		{
			glClearColor(0.392156862745098f, 0.5843137254901961f, 0.9294117647058824f, 1.0f);
			glViewport(0, 0, rClient.right - rClient.left, rClient.bottom - rClient.top);
		});
#endif

		window->Resized += [this](int width, int height)
		{
			WithContext([width, height]()
			{
				glViewport(0, 0, width, height);
			});
		};
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
		wglMakeCurrent(m_hDC, m_hRC);

		fn();

		wglMakeCurrent(m_hDC, nullptr);
#endif
	}
}