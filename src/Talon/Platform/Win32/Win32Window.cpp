
#include <Talon/Platform/Win32/Win32Window.h>
#include <Talon/Graphics/RenderDevice.h>
#include <string>

namespace Talon
{
	struct WindowClass
	{
		WindowClass(WNDPROC fnWndProc)
		{
			WNDCLASSA wc = {0};
			wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
			wc.lpfnWndProc = fnWndProc;
			wc.cbClsExtra = 0;
			wc.hInstance = GetModuleHandle(nullptr);
			wc.hIcon = LoadIcon(0, IDI_APPLICATION);
			wc.hCursor = LoadCursor(0, IDC_ARROW);
			wc.hbrBackground = nullptr;
			wc.lpszMenuName = 0;
			wc.lpszClassName = "TalonWindow";

			// Allocate a pointer-sized chunk to be stored on the HWND, for our Window instance.
			wc.cbWndExtra = sizeof(Win32Window*);

			if (RegisterClassA(&wc))
				Name = wc.lpszClassName;
		}

		~WindowClass()
		{
			UnregisterClassA(Name.c_str(), GetModuleHandle(nullptr));
		}

		std::string Name;
	};

	std::unique_ptr<WindowClass> Win32Window::s_windowClass;

	std::wstring utf8_decode(const std::string &str)
	{
		int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
		std::wstring wstrTo( size_needed, 0 );
		MultiByteToWideChar                  (CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
		return wstrTo;
	}

	Win32Window::Win32Window(std::string title, int width, int height)
		: WindowBase(title, width, height)
	{
		auto windowClass = GetOrRegisterClass();
		if (windowClass)
		{
			RECT rClient = { 0 };
			rClient.bottom = height;
			rClient.right = width;

			AdjustWindowRect(&rClient, WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, FALSE);

			// WTF: CreateWindowA requires a wchar_t title?!
			m_hWnd = CreateWindowA(windowClass->Name.c_str(), (char *)&utf8_decode(title)[0], WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT, CW_USEDEFAULT, rClient.right - rClient.left, rClient.bottom - rClient.top, 0, 0, GetModuleHandle(nullptr), this);
			

			if (m_hWnd)
			{
				SetWindowLongPtr(m_hWnd, GWLP_USERDATA, (LONG_PTR)this);

				ShowWindow(m_hWnd, SW_SHOW);
				UpdateWindow(m_hWnd);
			}
		}
	}

	Win32Window::~Win32Window()
	{
		DestroyWindow(m_hWnd);
	}

	void Win32Window::DoEvents()
	{
		WindowBase::DoEvents();

		MSG msg = {0};
		while (PeekMessage(&msg, m_hWnd, 0, 0, PM_REMOVE))
		{	
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	const WindowClass* Win32Window::GetOrRegisterClass()
	{
		if (!s_windowClass.get())
			s_windowClass = make_unique<WindowClass>(Win32Window::TalonWndProc);

		return s_windowClass.get();
	}

	LRESULT CALLBACK Win32Window::TalonWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		Win32Window* pWindow = (Win32Window *) GetWindowLongPtr(hWnd, GWLP_USERDATA);
		switch (msg)
		{
		case WM_CREATE:
			{
				// Hook up wrapper with HWND in both directions.
				CREATESTRUCT* pCS = (CREATESTRUCT*)lParam;
				if (pCS != nullptr && pCS->lpCreateParams != nullptr)
				{
					pWindow = (Win32Window*)pCS->lpCreateParams;
					SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pWindow);

					pWindow->m_hWnd = hWnd;
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

	void Win32Window::OnResized(int width, int height)
	{
		Base::OnResized(width, height);
	}

	void Win32Window::OnClosed()
	{
		Base::OnClosed();
	}

	void Win32Window::OnCreated()
	{
		Base::OnCreated();
	}

	void Win32Window::OnDestroyed()
	{
		Base::OnDestroyed();
	}
}