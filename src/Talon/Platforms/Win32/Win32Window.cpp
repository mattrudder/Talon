
#include <Talon/Platforms/Win32/Win32Window.h>
#include <string>

namespace Talon { namespace Win32
{
	struct WindowClass
	{
		WindowClass(WNDPROC fnWndProc)
		{
			WNDCLASS wc = {0};
			wc.style = CS_HREDRAW | CS_VREDRAW;
			wc.lpfnWndProc = fnWndProc;
			wc.cbClsExtra = 0;
			wc.hInstance = GetModuleHandle(nullptr);
			wc.hIcon = LoadIcon(0, IDI_APPLICATION);
			wc.hCursor = LoadCursor(0, IDC_ARROW);
			wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
			wc.lpszMenuName = 0;
			wc.lpszClassName = L"TalonWindow";

			// Allocate a pointer-sized chunk to be stored on the HWND, for our Window instance.
			wc.cbWndExtra = sizeof(Win32Window*);

			if (RegisterClass(&wc))
				Name = wc.lpszClassName;
		}

		~WindowClass()
		{
			UnregisterClass(Name.c_str(), GetModuleHandle(nullptr));
		}

		std::wstring Name;
	};

	std::unique_ptr<WindowClass> Win32Window::s_windowClass;

	Win32Window::Win32Window(std::wstring title, U32 width, U32 height)
		: WindowBase(title, width, height)
	{
		auto windowClass = GetOrRegisterClass();
		if (windowClass)
		{
			RECT rClient = { 0 };
			rClient.bottom = height;
			rClient.right = width;

			AdjustWindowRect(&rClient, WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX, FALSE);

			m_hWnd = CreateWindow(windowClass->Name.c_str(), title.c_str(), WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT, CW_USEDEFAULT, rClient.right - rClient.left, rClient.bottom - rClient.top, 0, 0, GetModuleHandle(nullptr), 0);

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
		case WM_CLOSE:
			pWindow->OnClosed();
			return 0;
		case WM_SIZE:
			{
				U32 w = LOWORD(lParam);
				U32 h = HIWORD(lParam);

				pWindow->OnResized(w, h);
			}
			return 0;
		}

		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}}