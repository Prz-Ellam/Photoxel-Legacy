#include "fxpch.h"
#include "KeyPressedEvent.h"

namespace Photoxel
{
	KeyPressedEvent::KeyPressedEvent() : m_KeyCode(KeyCode::None) {}

	KeyPressedEvent::KeyPressedEvent(KeyCode keyCode) : m_KeyCode(keyCode) {}

	bool KeyPressedEvent::operator==(const KeyPressedEvent& other) const
	{
		return m_KeyCode == other.m_KeyCode;
	}

	bool KeyPressedEvent::operator!=(const KeyPressedEvent& other) const
	{
		return m_KeyCode != other.m_KeyCode;
	}
}