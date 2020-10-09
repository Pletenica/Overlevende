#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"
#include "EditInterfaceMenu.h"
#include "AboutWindow.h"
#include "ConfigurationMenu.h"

//Include ImGui
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_opengl3.h"

class ModuleBaseMotor : public Module
{
public:
	ModuleBaseMotor(Application* app, bool start_enabled = true);
	~ModuleBaseMotor();

	bool Init();
	update_status PostUpdate(float dt);
	bool CleanUp();

public:
	SDL_GLContext context;

private:
	bool wireSphere = false;
	bool quit = false;
	EditInterfaceMenu interfacemenu;
	AboutWindow aboutwindow;
	ConfigurationMenu configurationmenu;
	void CreateMainBar();
	void CreateTestWindow();
	
};