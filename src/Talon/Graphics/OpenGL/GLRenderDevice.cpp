
#include "TalonPrefix.h"
#include <GL/glew.h>

#include <Talon/Graphics/RenderDevice.h>

#if TALON_WINDOWS
#include <GL/wglew.h>
#elif TALON_MAC
#import <Cocoa/Cocoa.h>
#import <OpenGL/OpenGL.h>
#endif

#include <Talon/Platform/Window.h>

namespace Talon
{
#if TALON_WINDOWS
	class RenderDevice::Impl
	{
	public:
		HDC hDC;
		HGLRC hRC;
		
		void Bind() { wglMakeCurrent(hDC, hRC); }
		void Unbind() { wglMakeCurrent(hDC, nullptr); }
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
#elif TALON_MAC
	class RenderDevice::Impl
	{
	public:
		NSOpenGLContext* context;
		
		void Bind() { [context makeCurrentContext]; }
		void Unbind() { [NSOpenGLContext clearCurrentContext]; }
	};
#endif
	
	class GLContext
	{
	public:
		GLContext(RenderDevice::Impl* impl)
		: m_pImpl(impl)
		{
			m_pImpl->Bind();
		}
		~GLContext()
		{
			m_pImpl->Unbind();
		}
		
	private:
		RenderDevice::Impl* m_pImpl;
	};

	RenderDevice::RenderDevice(Window* window)
		: m_window(window)
		, m_pImpl(make_unique<Impl>())
	{
#if TALON_WINDOWS
		HWND hWnd = window->GetHandle();
		HDC hDC = ::GetDC(hWnd);

		if (SetPixelFormat(hDC))
		{
			HGLRC tempContext = wglCreateContext(hDC);
			wglMakeCurrent(hDC, tempContext);

			char line[MAX_PATH];
			glewExperimental = GL_TRUE;
			if (glewInit() == GLEW_OK)
			{
				sprintf_s(line, "GLEW version %s\n", glewGetString(GLEW_VERSION));
				OutputDebugStringA(line);
			}

			int attributes[] = 
			{
				WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
				WGL_CONTEXT_MINOR_VERSION_ARB, 2,
				WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
				0
			};

			HGLRC hRC = tempContext;
			if (WGLEW_ARB_create_context)
			{
				hRC = wglCreateContextAttribsARB(hDC, 0, attributes);
				if (hRC != 0)
				{
					wglMakeCurrent(nullptr, nullptr);
					wglDeleteContext(tempContext);

					wglMakeCurrent(hDC, hRC);
					sprintf_s(line, "OpenGL Version: %s\n", glGetString(GL_VERSION));
					OutputDebugStringA(line);
				}
				else
				{
					// Only GL 2.1 is supported
					OutputDebugString(L"OpenGL 3.2 not supported! Falling back to OpenGL 2.1.\n");
					hRC = tempContext;
				}

				wglMakeCurrent(nullptr, nullptr);
			}
			else
			{
				// Only GL 2.1 is supported
				OutputDebugString(L"OpenGL 3.2 not supported! Falling back to OpenGL 2.1.\n");
				hRC = tempContext;
			}

			m_pImpl->hDC = hDC;
			m_pImpl->hRC = hRC;
		}
#elif TALON_MAC
		GLuint attrs[] =
		{
			NSOpenGLPFANoRecovery,
			NSOpenGLPFAColorSize, 24,
			NSOpenGLPFADepthSize, 16,
			NSOpenGLPFAStencilSize, 0,
			NSOpenGLPFADoubleBuffer,
			NSOpenGLPFAAccelerated,
			NSOpenGLPFAAllowOfflineRenderers,
			0
		};
		
		NSOpenGLPixelFormat* pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attrs];
		m_pImpl->context = [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:nil];
#endif

		SetInitialized(true);
		WithContext([window, this]
		{
			glShadeModel(GL_SMOOTH);
			//glClearColor(0.392156862745098f, 0.5843137254901961f, 0.9294117647058824f, 1.0f);
			glClearColor(1.0f, 0.3882352941176471f, 0.2784313725490196f, 1.0f); // TOMATO!
			glClearDepth(1.0f);
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LEQUAL);
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
			glViewport(0, 0, window->GetWidth(), window->GetHeight());
				
#if TALON_MAC
			NSWindow* cocoaWindow = (__bridge NSWindow*)window->GetWindow();
			NSOpenGLContext* context = (NSOpenGLContext*) m_pImpl->context;
			[context setView:[cocoaWindow contentView]];
#endif
		});

		window->Resized += [this](int width, int height)
		{
			WithContext([width, height]()
			{
				glViewport(0, 0, width, height);
			});
		};
	}

	RenderDevice::~RenderDevice()
	{
#if TALON_WINDOWS
		wglMakeCurrent(m_pImpl->hDC, nullptr);
		wglDeleteContext(m_pImpl->hRC);
		::ReleaseDC(GetWindow()->GetHandle(), m_pImpl->hDC);
#elif TALON_MAC
		[NSOpenGLContext clearCurrentContext];
#endif
	}

	void RenderDevice::BeginFrame()
	{
#if TALON_WINDOWS
		wglMakeCurrent(m_pImpl->hDC, m_pImpl->hRC);
#elif TALON_MAC
		NSOpenGLContext* context = (NSOpenGLContext*) m_pImpl->context;
		[context makeCurrentContext];
#endif

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void RenderDevice::EndFrame()
	{
#if TALON_WINDOWS
		SwapBuffers(m_pImpl->hDC);
		ValidateRect(GetWindow()->GetHandle(), nullptr);
		wglMakeCurrent(m_pImpl->hDC, nullptr);
#elif TALON_MAC
		NSOpenGLContext* context = (NSOpenGLContext*) m_pImpl->context;
		[context flushBuffer];
		[NSOpenGLContext clearCurrentContext];
#endif
	}

	void RenderDevice::WithContext(std::function<void()> fn)
	{
		GLContext context(m_pImpl.get());
		
		fn();
	}
}