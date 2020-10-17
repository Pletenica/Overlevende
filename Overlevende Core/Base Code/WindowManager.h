#ifndef __ModuleFatherWindow_H__
#define __ModuleFatherWindow_H__

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "SDL/include/SDL.h"
#include <vector>

//Include ImGui
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_opengl3.h"

class Application;

enum WindowType {
	About,
	Configuration,
	Inspector,
	Resources,
	Hierarchy,
	Console,
	Play,
	Scene
};


class Window
{
public:

	Window();

	// Destructor
	virtual ~Window();

	virtual bool Init();
	virtual bool PreUpdate(float dt);
	virtual bool Draw(float dt);
	virtual bool CleanUp();

public:
	bool active=true;
};

class WindowManager : public Module
{
public:

	WindowManager(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~WindowManager();

	bool Init();
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	Window* CreateWin(WindowType w_type);

public:
	std::vector<Window*> windows;
};




#endif // __ModuleFatherWindow_H__