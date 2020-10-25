#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"

#include "ConsoleWindow.h"
#include "InspectorWindow.h"

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
	update_status Draw(float dt);
	bool CleanUp();

	void CreateAllWindows();

public:
	SDL_GLContext context;
	ConsoleWindow* console_window;
	InspectorWindow* inspector_window;

private:
	bool wireSphere = false;
	bool quit = false;
	void CreateMainBar();	
};