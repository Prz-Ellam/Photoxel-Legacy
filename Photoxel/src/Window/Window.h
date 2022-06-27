#pragma once
#ifndef _PHOTOXEL_WINDOW_H_
#define _PHOTOXEL_WINDOW_H_

#include <string>
#include <inttypes.h>

#include "Events/Events.h"

namespace Photoxel
{
	class Window
	{
	public:
		Window();
		Window(uint32_t width, uint32_t height, const std::string& title);
		virtual ~Window() = default;

		virtual void Show() = 0;
		virtual void Hide() = 0;

		uint32_t GetWidth() const;
		uint32_t GetHeight() const;

		std::string GetTitle() const;
		virtual void SetTitle(const std::string& title) = 0;

		virtual void SetIcons(const std::string& filepath) = 0;
		virtual void* GetNativeHandler() const = 0;
		virtual void Update() = 0;
		virtual void Present() = 0;

		void SetWindowCloseEventCallback(WindowCloseEventFn windowCloseEventFn);
		void SetWindowResizeEventCallback();
		void SetWindowMoveEventCallback();
		void SetWindowFocusEventCallback();
		void SetWindowUnfocusEventCallback();
		void SetKeyPressedCallback();
		void SetKeyReleaseCallback();
		void SetKeyRepeatCallback();
		void SetCharEventCallback();
		void SetMouseMoveEventCallback();
		void SetMouseButtonPressedEventCallback();
		void SetMouseButtonReleaseEventCallback();
		void SetMouseButtonRepeatEventCallback();
		void SetMouseScrollEventCallback();

	protected:
#if UNICODE
		std::string m_Title;
#else
		std::string m_Title;
#endif
		uint32_t m_Width, m_Height;

		WindowCloseEventFn m_WindowCloseEventCallback = nullptr;
		KeyPressedEventFn m_KeyPressedEventCallback = nullptr;

	};
}

#endif