#pragma once
#ifndef _PHOTOXEL_WIN32_WINDOW_H_
#define _PHOTOXEL_WIN32_WINDOW_H_

#include "../../Window.h"
#include "IncludeWindow.h"
#include "Rendering/Platform/D3D11Context.h"

namespace Photoxel
{
	class Win32Window : public Window
	{
	public:
		Win32Window();
		Win32Window(uint32_t width, uint32_t height, const std::string& title);
		Win32Window(const Win32Window& other) = default;
		Win32Window(Win32Window&& other) noexcept = default;
		virtual ~Win32Window();

		virtual void Show() override;
		virtual void Hide() override;

		virtual void SetTitle(const std::string& title) override;

		virtual void SetIcons(const std::string& filepath) override;
		virtual void* GetNativeHandler() const override;
		virtual void Update() override;


		virtual void Present() override {
			m_Context->Present();
		}

	private:
		HWND m_Handler = nullptr;
		//WNDCLASSEX m_WindowClass; // TODO: Que hacer con esto
		std::wstring m_WindowClassName = L"Photoxel Editor";
		MSG m_Message = {};

		// TODO: Solo un Context pls
		D3D11Context* m_Context;

		void RegisterWindowClass();
		void CreateWindowInstance();
		void ReleaseWindow();

		static LRESULT CALLBACK StaticMessageCallback(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT MessageCallback(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		MouseMoveEventFn m_MouseMoveEventCallback;

	};
}

#endif