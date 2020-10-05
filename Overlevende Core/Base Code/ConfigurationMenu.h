#pragma once
#include "Globals.h"
#include "glmath.h"

//Include ImGui
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_opengl3.h"

class ConfigurationMenu
{

public:
	ConfigurationMenu();
	~ConfigurationMenu();

	bool boolconfigurationmenu = false;

	void CreateConfigurationMenu();

private:
	ImTextureID iconprovingtex;
};
