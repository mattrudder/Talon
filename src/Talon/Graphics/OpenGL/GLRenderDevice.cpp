
#include <GL/glew.h>

#include <Talon/Graphics/OpenGL/GLRenderDevice.h>

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
	struct GLRenderDevice::Impl
	{
		HDC hDC;
		HGLRC hRC;
		
		void Bind() { wglMakeCurrent(m_hDC, m_hRC); }
		void Unbind() { wglMakeCurrent(m_hDC, nullptr); }
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
	struct GLRenderDevice::Impl
	{
		NSOpenGLContext* context;
		
		void Bind() { [context makeCurrentContext]; }
		void Unbind() { [NSOpenGLContext clearCurrentContext]; }
	};
#endif
	
	class GLContext
	{
	public:
		GLContext(GLRenderDevice::Impl* impl)
		: m_pImpl(impl)
		{
			m_pImpl->Bind();
		}
		~GLContext()
		{
			m_pImpl->Unbind();
		}
		
	private:
		GLRenderDevice::Impl* m_pImpl;
	};

	GLRenderDevice::GLRenderDevice(Window* window)
		: RenderDeviceBase(window)
		, m_impl(make_unique<Impl>())
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
				WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
				WGL_CONTEXT_MINOR_VERSION_ARB, 0,
				WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
				0
			};

			if (WGLEW_ARB_create_context)
			{
				HGLRC hRC = wglCreateContextAttribsARB(hDC, 0, attributes);
				wglMakeCurrent(nullptr, nullptr);
				wglDeleteContext(tempContext);

				wglMakeCurrent(hDC, hRC);
				sprintf_s(line, "OpenGL Version: %s\n", glGetString(GL_VERSION));
				OutputDebugStringA(line);
				wglMakeCurrent(nullptr, nullptr);
			}
			else
			{
				// Only GL 2.1 is supported
				OutputDebugString(L"OpenGL 3.2 not supported! Falling back to OpenGL 2.1.\n");
				hRC = tempContext;
			}

			m_impl->hDC = hDC;
			m_impl->hRC = hRC;
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
		m_impl->context = [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:nil];
#endif

		SetInitialized(true);
		WithContext([window, this]
		{
			glShadeModel(GL_SMOOTH);
			glClearColor(0.392156862745098f, 0.5843137254901961f, 0.9294117647058824f, 1.0f);
			glClearDepth(1.0f);
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LEQUAL);
			glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
			glViewport(0, 0, window->GetWidth(), window->GetHeight());
				
#if TALON_MAC
			NSWindow* cocoaWindow = (__bridge NSWindow*)window->GetWindow();
			NSOpenGLContext* context = (NSOpenGLContext*) m_impl->context;
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

	GLRenderDevice::~GLRenderDevice()
	{
#if TALON_WINDOWS
		wglMakeCurrent(m_hDC, nullptr);
		wglDeleteContext(m_hRC);
		::ReleaseDC(GetWindow()->GetHandle(), m_hDC);
#elif TALON_MAC
		[NSOpenGLContext clearCurrentContext];
#endif
	}

	void GLRenderDevice::BeginFrame()
	{
#if TALON_WINDOWS
		wglMakeCurrent(m_hDC, m_hRC);
#elif TALON_MAC
		NSOpenGLContext* context = (NSOpenGLContext*) m_impl->context;
		[context makeCurrentContext];
#endif

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void GLRenderDevice::EndFrame()
	{
#if TALON_WINDOWS
		SwapBuffers(m_hDC);
		ValidateRect(GetWindow()->GetHandle(), nullptr);
		wglMakeCurrent(m_hDC, nullptr);
#elif TALON_MAC
		NSOpenGLContext* context = (NSOpenGLContext*) m_impl->context;
		[context flushBuffer];
		[NSOpenGLContext clearCurrentContext];
#endif
	}

	void GLRenderDevice::WithContext(std::function<void()> fn)
	{
		GLContext context(m_impl.get());
		
		fn();
	}
}