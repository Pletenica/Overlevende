#pragma once
#include "Globals.h"
#include "glmath.h"
#include <vector>

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

	void CreateConfigurationMenu(float dt);

private:
	ImTextureID iconprovingtex;
	std::vector<float> fps;
	std::vector<float> ms;
	bool wireSphere;
	void AddToVector(std::vector<float>& vec, float value);
};
