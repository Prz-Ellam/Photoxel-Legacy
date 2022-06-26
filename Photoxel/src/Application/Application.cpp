#include "fxpch.h"
#include "Application.h"

namespace Photoxel
{
	std::shared_ptr<Application> Application::s_Application;

	Application::Application()
	{
	}

	void Application::Close()
	{
		m_Running = false;
	}

	std::shared_ptr<Application> Application::GetInstance()
	{
		return s_Application;
	}
}