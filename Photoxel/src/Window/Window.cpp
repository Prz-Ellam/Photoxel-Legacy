#include "fxpch.h"
#include "Window.h"

namespace Photoxel
{
	Window::Window()
		: m_Width(1280u), m_Height(720u), m_Title("Photoxel Application")
	{
	}

	Window::Window(uint32_t width, uint32_t height, const std::string& title)
		: m_Width(width), m_Height(height), m_Title(title)
	{
	}

	uint32_t Window::GetWidth() const
	{
		return m_Width;
	}

	uint32_t Window::GetHeight() const
	{
		return m_Height;
	}

	std::string Window::GetTitle() const
	{
		return m_Title;
	}

	void Window::SetWindowCloseEventCallback(WindowCloseEventFn windowCloseEventFn)
	{
		m_WindowCloseEventCallback = windowCloseEventFn;
	}
}