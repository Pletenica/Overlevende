#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"

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
	bool quit = false;
	bool booleditinterface = false;

	void CreateMainBar();
	void CreateTestWindow();
	void CreateEditInterfaceMenu();
	void LightModeSelected();
	void NightModeSelected();
	void DayModeSelected();
};