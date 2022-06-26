#pragma once
#ifndef _PHOTOXEL_KEY_PRESSED_EVENT_H_
#define _PHOTOXEL_KEY_PRESSED_EVENT_H_

#include "../KeyCodes/KeyCode.h"

#include <string>

#define NAMEOF(variable) ((decltype(&variable))nullptr, #variable)

namespace Photoxel
{
	class KeyPressedEvent
	{
	public:
		KeyPressedEvent();
		KeyPressedEvent(KeyCode keyCode);
		KeyPressedEvent(const KeyPressedEvent& other) = default;
		KeyPressedEvent(KeyPressedEvent&& other) noexcept = default;
		~KeyPressedEvent() = default;

		KeyPressedEvent& operator=(const KeyPressedEvent& other) = default;
		KeyPressedEvent& operator=(KeyPressedEvent&& other) noexcept = default;

		bool operator==(const KeyPressedEvent& other) const;
		bool operator!=(const KeyPressedEvent& other) const;

		inline KeyCode GetKeyCode() const;
		inline std::string ToString() const;
	private:
		KeyCode m_KeyCode;
	};

	inline KeyCode KeyPressedEvent::GetKeyCode() const
	{
		return m_KeyCode;
	}

	inline std::string KeyPressedEvent::ToString() const
	{
		return std::string(NAMEOF(m_KeyCode));
	}

	using KeyPressedEventFn = std::function<void(KeyPressedEvent)>;
}

#endif // _PHOTOXEL_KEY_PRESSED_EVENT_H_
