#include <Photoxel.h>

class Sandbox : public Photoxel::Application
{
public:
	void Create() override;
	void Run() override;
	void Delete() override;
	void D(Photoxel::WindowCloseEvent e)
	{
		Close();
	}
};

void Sandbox::Create()
{
	PX_DEBUG("Hola mundo");
	m_Window = CREATE_WINDOW(720u, 480u, "Mi ventana especial");
	m_Window->SetWindowCloseEventCallback([this](Photoxel::WindowCloseEvent e) { D(e); });
}

void Sandbox::Run()
{
	int counter = 0;
	while (m_Running)
	{

		m_Window->PollEvents();
	}
}

void Sandbox::Delete()
{
}

int main()
{
	Photoxel::Application* application = new Sandbox;
	application->Create();
	application->Run();
	application->Delete();
	delete application;
}