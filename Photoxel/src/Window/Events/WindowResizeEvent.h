#pragma once
#ifndef _PHOTOXEL_WINDOW_RESIZE_EVENT_H_
#define _PHOTOXEL_WINDOW_RESIZE_EVENT_H_

#include <inttypes.h>
#include <string>
#include <tuple>
#include <functional>

namespace Photoxel
{
	class WindowResizeEvent
	{
	public:
		WindowResizeEvent();
		WindowResizeEvent(uint32_t width, uint32_t height);
		WindowResizeEvent(const WindowResizeEvent& other) = default;
		WindowResizeEvent(WindowResizeEvent&& other) noexcept = default;
		~WindowResizeEvent() = default;

		WindowResizeEvent& operator=(const WindowResizeEvent& other) = default;
		WindowResizeEvent& operator=(WindowResizeEvent&& other) noexcept = default;

		bool operator==(const WindowResizeEvent& other) const;
		bool operator!=(const WindowResizeEvent& other) const;

		inline std::pair<uint32_t, uint32_t> Get() const;
		inline uint32_t GetWidth() const;
		inline uint32_t GetHeight() const;

		inline std::string ToString() const;
	private:
		uint32_t m_Width, m_Height;
	};

	inline uint32_t WindowResizeEvent::GetWidth() const
	{
		return m_Width;
	}

	inline uint32_t WindowResizeEvent::GetHeight() const
	{
		return m_Height;
	}

	using WindowResizeEventFn = std::function<void(WindowResizeEvent)>;
}

#endif // _PHOTOXEL_WINDOW_RESIZE_EVENT_H_
