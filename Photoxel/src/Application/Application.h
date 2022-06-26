#pragma once
#ifndef _PHOTOXEL_APPLICATION_H_
#define _PHOTOXEL_APPLICATION_H_

#include <Window/Window.h>

namespace Photoxel
{
	class Application
	{
	public:
		Application();
		Application(const Application& other) = default;
		Application(Application&& other) noexcept = default;
		virtual ~Application() = default;

		Application& operator=(const Application& other) = default;
		Application& operator=(Application&& other) noexcept = default;

		void Close();

		virtual void Create() = 0;
		virtual void Run() = 0;
		virtual void Delete() = 0;

		static std::shared_ptr<Application> GetInstance();
	protected:
		bool m_Running = true;
		std::shared_ptr<Window> m_Window;
		static std::shared_ptr<Application> s_Application;
	};
}

#endif // _PHOTOXEL_APPLICATION_H_