#pragma once
#ifndef _PHOTOXEL_MOUSE_MOVE_EVENT_H_
#define _PHOTOXEL_MOUSE_MOVE_EVENT_H_

#include <functional>
#include <stdint.h>

namespace Photoxel
{
	class MouseMoveEvent
	{
	public:
		MouseMoveEvent();
		MouseMoveEvent(int x, int y);
		MouseMoveEvent(const MouseMoveEvent& other) = default;
		MouseMoveEvent(MouseMoveEvent&& other) noexcept = default;
		~MouseMoveEvent() = default;

		MouseMoveEvent& operator=(const MouseMoveEvent& other) = default;
		MouseMoveEvent& operator=(MouseMoveEvent&& other) noexcept = default;

		bool operator==(const MouseMoveEvent& other) const;
		bool operator!=(const MouseMoveEvent& other) const;

		inline std::pair<int, int> Get() const;
		inline int GetX() const;
		inline int GetY() const;

		inline std::string ToString() const;
	private:
		int m_X, m_Y;
	};

	inline std::pair<int, int> MouseMoveEvent::Get() const
	{
		return std::make_pair(m_X, m_Y);
	}

	inline int MouseMoveEvent::GetX() const
	{
		return m_X;
	}

	inline int MouseMoveEvent::GetY() const
	{
		return m_Y;
	}

	inline std::string MouseMoveEvent::ToString() const
	{
		return '(' + std::to_string(m_X) + ", " + std::to_string(m_Y) + ')';
	}

	using MouseMoveEventFn = std::function<void(MouseMoveEvent)>;
}

#endif
