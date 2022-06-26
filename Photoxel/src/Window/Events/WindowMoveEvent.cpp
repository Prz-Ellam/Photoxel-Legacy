#include "fxpch.h"
#include "WindowMoveEvent.h"

namespace Photoxel
{
	WindowMoveEvent::WindowMoveEvent() : m_X(0), m_Y(0)
	{
	}

	WindowMoveEvent::WindowMoveEvent(int x, int y) : m_X(x), m_Y(y)
	{
	}

	bool WindowMoveEvent::operator==(const WindowMoveEvent& other) const
	{
		return m_X == other.m_X && m_Y == other.m_Y;
	}

	bool WindowMoveEvent::operator!=(const WindowMoveEvent& other) const
	{
		return m_X != other.m_X || m_Y != other.m_Y;
	}
}