#include "fxpch.h"
#include "MouseMoveEvent.h"

namespace Photoxel
{
	MouseMoveEvent::MouseMoveEvent() : m_X(0), m_Y(0)
	{
	}

	MouseMoveEvent::MouseMoveEvent(int x, int y) : m_X(x), m_Y(y)
	{
	}

	inline bool MouseMoveEvent::operator==(const MouseMoveEvent& other) const
	{
		return m_X == other.m_X && m_Y == other.m_Y;
	}

	bool MouseMoveEvent::operator!=(const MouseMoveEvent& other) const
	{
		return m_X != other.m_X || m_Y == other.m_Y;
	}
}