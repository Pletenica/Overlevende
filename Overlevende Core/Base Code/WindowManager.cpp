#include "Globals.h"
#include "Application.h"
#include "InspectorWindow.h"
#include "AboutWindow.h"
#include "ResourcesWindow.h"
#include "ConfigurationWindow.h"
#include "WindowManager.h"


WindowManager::WindowManager(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

// Destructor
WindowManager::~WindowManager()
{
}

// Called before render is available
bool WindowManager::Init()
{
	bool ret = true;

	for (int i = 0; i < windows.size(); i++)
	{
		windows[i]->Init();
	}

	return ret;
}

update_status WindowManager::PostUpdate(float dt)
{
	//for ( int i = 0; i < windows.size(); i++)
	//{
	//	windows[i]->Draw(dt);
	//}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool WindowManager::CleanUp()
{
	for (int i = 0; i < windows.size(); i++)
	{
		windows[i]->CleanUp();
		delete windows[i];
	}

	return true;
}


Window* WindowManager::CreateWin(WindowType w_type) {
	Window* win = nullptr;

	switch (w_type) {
	case(WindowType::Inspector):
		win = new InspectorWindow();
		break;
	case(WindowType::Resources):
		win = new ResourcesWindow();
		break;
	case(WindowType::About):
		win = new AboutWindow();
		break;
	case(WindowType::Configuration):
		win = new ConfigurationWindow();
		break;
	case(WindowType::ThingsOnScene):
		//win = new ThingsOnSceneWindow();
		break;
	}

	windows.push_back(win);
	return win;
}

///WINDOW NOW

Window::Window()
{

}

// Destructor
Window::~Window()
{
}

// Called before render is available
bool Window::Init()
{
	bool ret = true;

	return ret;
}

bool Window::Draw(float dt)
{

	return true;
}

// Called before quitting
bool Window::CleanUp()
{

	return true;
}