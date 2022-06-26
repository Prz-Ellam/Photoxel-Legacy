#include "fxpch.h"
#include "Win32Window.h"
#include "Core/Core.h"

namespace Photoxel
{
	Win32Window::Win32Window()
		: Window()
	{
		RegisterWindowClass();
		CreateWindowInstance();
		Show();
		m_Context = new D3D11Context(this);
	}

	Win32Window::Win32Window(uint32_t width, uint32_t height, const std::string& title)
		: Window(width, height, title)
	{
		RegisterWindowClass();
		CreateWindowInstance();
		Show();
		m_Context = new D3D11Context(this);
	}

	Win32Window::~Win32Window()
	{
		delete m_Context;
	}

	void Win32Window::RegisterWindowClass()
	{
		WNDCLASSEX wndClass = {};
		wndClass.cbSize = sizeof(WNDCLASSEX);
		wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;
		wndClass.lpfnWndProc = StaticMessageCallback;
		wndClass.cbClsExtra = 0;
		wndClass.cbWndExtra = 0;
		wndClass.hInstance = GetModuleHandle(nullptr);
		wndClass.hIcon = nullptr;
		wndClass.hCursor = nullptr;
		wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(COLOR_WINDOW));
		wndClass.lpszMenuName = nullptr;
		wndClass.lpszClassName = m_WindowClassName.c_str();
		wndClass.hIconSm = nullptr;

		ATOM result = RegisterClassEx(&wndClass);
		PX_ASSERT(result, "No se pudo registrar la clase de la ventana");
	}

	void Win32Window::CreateWindowInstance()
	{
		RECT windowSize = { 0, 0, static_cast<LONG>(m_Width), static_cast<LONG>(m_Height) };
		AdjustWindowRectEx(&windowSize, WS_OVERLAPPEDWINDOW, 0, 0);

		m_Handler = CreateWindowEx(0, 
			m_WindowClassName.c_str(),
			m_WindowClassName.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			windowSize.right - windowSize.left,
			windowSize.bottom - windowSize.top,
			nullptr,
			nullptr,
			GetModuleHandle(nullptr),
			nullptr
		);

		PX_ASSERT(m_Handler, "No se pudo crear la ventana");

		PX_INFO("La ventana ha sido generada con exito")

		SetWindowLongPtr(m_Handler, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

		int dummy = -1;



	}

	void Win32Window::Show()
	{
		ShowWindow(m_Handler, SW_SHOW);
	}

	void Win32Window::Hide()
	{
		ShowWindow(m_Handler, SW_HIDE);
	}

	LRESULT Win32Window::StaticMessageCallback(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		Win32Window* window = reinterpret_cast<Win32Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

		if (window)
		{
			return window->MessageCallback(hWnd, uMsg, wParam, lParam);
		}

		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	LRESULT Win32Window::MessageCallback(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
			//case WM_NULL:
			//case WM_CREATE:
			//case WM_DESTROY:
			//case WM_MOVE:
			//case WM_SIZE:
			//case WM_ACTIVATE:
			//case WM_SETFOCUS:
			//case WM_KILLFOCUS:
			//case WM_ENABLE:
			//case WM_SETREDRAW:
			//case WM_SETTEXT:
			//case WM_GETTEXT:
			//case WM_GETTEXTLENGTH:
			//case WM_PAINT:
			case WM_CLOSE:
			{
				if (m_WindowCloseEventCallback)	m_WindowCloseEventCallback(WindowCloseEvent());
				break;
			}
			case WM_QUERYENDSESSION:
			case WM_QUIT:


			case WM_KEYUP:
			case WM_KEYDOWN:
			{


				if (m_KeyPressedEventCallback)	m_KeyPressedEventCallback(KeyPressedEvent());
				break;
			}

			// Mouse Events
			case WM_MOUSEMOVE:
			{
				int x = GET_X_LPARAM(lParam);
				int y = GET_Y_LPARAM(lParam);
				if (m_MouseMoveEventCallback)	m_MouseMoveEventCallback(MouseMoveEvent(x, y));
				break;
			}
			case WM_LBUTTONDOWN:
			case WM_LBUTTONUP:
			case WM_LBUTTONDBLCLK:
			case WM_RBUTTONDOWN:
			case WM_RBUTTONUP:
			case WM_RBUTTONDBLCLK:
			case WM_MBUTTONDOWN:
			case WM_MBUTTONUP:
			case WM_MBUTTONDBLCLK:
			case WM_MOUSELAST:
			case WM_MOUSEWHEEL:
			case WM_XBUTTONDOWN:
			case WM_XBUTTONUP:
			case WM_XBUTTONDBLCLK:
				break;
		}


		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	void Win32Window::SetTitle(const std::string& title)
	{
		//SetWindowText(m_Handler)
	}

	void Win32Window::SetIcons(const std::string& filepath)
	{
		PX_ASSERT(false, "Not implemented yet");
	}

	void* Win32Window::GetNativeHandler() const
	{
		return m_Handler;
	}

	void Win32Window::PollEvents()
	{
		while (PeekMessage(&m_Message, m_Handler, 0, 0, PM_REMOVE) > 0)
		{
			if (m_Message.message == WM_QUIT)
			{
				// TODO: Sucede algo
			}

			TranslateMessage(&m_Message);
			DispatchMessage(&m_Message);
		}

		m_Context->Present();
	}
}