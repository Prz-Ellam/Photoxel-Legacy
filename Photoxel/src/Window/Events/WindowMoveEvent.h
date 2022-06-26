#pragma once
#ifndef _PHOTOXEL_WINDOW_MOVE_EVENT_H_
#define _PHOTOXEL_WINDOW_MOVE_EVENT_H_

#include <tuple>
#include <string>

#include <functional>

namespace Photoxel
{
	class WindowMoveEvent
	{
	public:
		WindowMoveEvent();
		WindowMoveEvent(int x, int y);
		WindowMoveEvent(const WindowMoveEvent& other) = default;
		WindowMoveEvent(WindowMoveEvent&& other) noexcept = default;
		~WindowMoveEvent() = default;

		WindowMoveEvent& operator=(const WindowMoveEvent& other) = default;
		WindowMoveEvent& operator=(WindowMoveEvent&& other) noexcept = default;

		bool operator==(const WindowMoveEvent& other) const;
		bool operator!=(const WindowMoveEvent& other) const ;

		inline std::pair<int, int> Get() const;
		inline int GetX() const;
		inline int GetY() const;

		inline std::string ToString() const;
	private:
		int m_X, m_Y;
	};

	inline int WindowMoveEvent::GetX() const
	{
		return m_X;
	}

	inline int WindowMoveEvent::GetY() const
	{
		return m_Y;
	}

	inline std::pair<int, int> WindowMoveEvent::Get() const
	{
		return std::make_pair(m_X, m_Y);
	}

	inline std::string WindowMoveEvent::ToString() const
	{
		return '(' + std::to_string(m_X) + ", " + std::to_string(m_Y) + ')';
	}

	using WindowMoveEventFn = std::function<void(WindowMoveEvent)>;
}

#endif // _PHOTOXEL_WINDOW_MOVE_EVENT_H_
