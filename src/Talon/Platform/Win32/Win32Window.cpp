
#include "TalonPrefix.h"
#include <Talon/Platform/Window.h>
#include <Talon/Graphics/RenderDevice.h>

using namespace std;

namespace Talon
{
	struct WindowClass
	{
		WindowClass(WNDPROC fnWndProc)
		{
			WNDCLASSW wc = {0};
			wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
			wc.lpfnWndProc = fnWndProc;
			wc.cbClsExtra = 0;
			wc.hInstance = GetModuleHandle(nullptr);
			wc.hIcon = LoadIcon(0, IDI_APPLICATION);
			wc.hCursor = LoadCursor(0, IDC_ARROW);
			wc.hbrBackground = nullptr;
			wc.lpszMenuName = 0;
			wc.lpszClassName = L"TalonWindow";

			// Allocate a pointer-sized chunk to be stored on the HWND, for our Window instance.
			wc.cbWndExtra = sizeof(Window*);

			if (RegisterClassW(&wc))
				Name = wc.lpszClassName;
		}

		~WindowClass()
		{
			UnregisterClassW(Name.c_str(), GetModuleHandle(nullptr));
		}

		std::wstring Name;
	};

	class Window::Impl
	{
	public:
		~Impl()
		{
			//if (hWnd)
			//{
			//	DestroyWindow(hWnd);
			//	hWnd = 0;
			//}
		}

		static const WindowClass* GetOrRegisterClass()
		{
			if (!s_windowClass.get())
				s_windowClass = make_unique<WindowClass>(TalonWndProc);

			return s_windowClass.get();
		}

		static LRESULT CALLBACK TalonWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
		{
			Window* pWindow = (Window *) GetWindowLongPtr(hWnd, GWLP_USERDATA);
			switch (msg)
			{
			case WM_CREATE:
				{
					// Hook up wrapper with HWND in both directions.
					CREATESTRUCT* pCS = (CREATESTRUCT*)lParam;
					if (pCS != nullptr && pCS->lpCreateParams != nullptr)
					{
						pWindow = (Window*)pCS->lpCreateParams;
						SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pWindow);

						pWindow->m_pImpl->hWnd = hWnd;
						pWindow->OnCreated();
					}
				}
				return 0;
			case WM_DESTROY:
				{
					pWindow->OnDestroyed();
				}
				return 0;
			case WM_CLOSE:
				{
					pWindow->OnClosed();
				}
				return 0;
			case WM_SIZE:
				{
					int w = LOWORD(lParam);
					int h = HIWORD(lParam);

					pWindow->OnResized(w, h);
				}
				return 0;
			}

			return DefWindowProc(hWnd, msg, wParam, lParam);
		}

	public:
		HWND hWnd;

		static std::unique_ptr<WindowClass> s_windowClass;
	};

	std::unique_ptr<WindowClass> Window::Impl::s_windowClass;

	Window::Window(std::string title, int width, int height)
		: m_title(title)
		, m_width(width)
		, m_height(height)
		, m_renderDevice(nullptr)
		, m_pImpl(make_unique<Impl>())
	{
		auto windowClass = Impl::GetOrRegisterClass();
		if (windowClass)
		{
			RECT rClient = { 0 };
			rClient.bottom = m_height;
			rClient.right = m_width;

			AdjustWindowRect(&rClient, WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, FALSE);

			m_pImpl->hWnd = CreateWindowW(windowClass->Name.c_str(), convert(m_title).c_str(), WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT, CW_USEDEFAULT, rClient.right - rClient.left, rClient.bottom - rClient.top, 0, 0, GetModuleHandle(nullptr), this);


			if (m_pImpl->hWnd)
			{
				SetWindowLongPtr(m_pImpl->hWnd, GWLP_USERDATA, (LONG_PTR)this);

				ShowWindow(m_pImpl->hWnd, SW_SHOW);
				UpdateWindow(m_pImpl->hWnd);
			}
		}
	}

	Window::~Window()
	{
	}

	void Window::DoEvents()
	{
		MSG msg = {0};
		while (PeekMessage(&msg, m_pImpl->hWnd, 0, 0, PM_REMOVE))
		{	
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	HWND Window::GetHandle() const
	{
		return m_pImpl->hWnd;
	}
}