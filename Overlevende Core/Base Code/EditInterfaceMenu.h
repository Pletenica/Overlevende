#pragma once
#include "Globals.h"
#include "glmath.h"

//Include ImGui
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_opengl3.h"

class EditInterfaceMenu
{
public:
	EditInterfaceMenu();
	~EditInterfaceMenu();

	bool booleditinterface = false;

	bool isNightModeSelected = true;
	bool isDayModeSelected = false;
	bool isLightModeSelected = false;

	void CreateMainBar();
	void CreateTestWindow();
	void CreateEditInterfaceMenu();

	void LightModeSelected();
	void NightModeSelected();
	void DayModeSelected();

	void PutGreenColor();
	void PutBlueColor();
	void PutOrangeColor();
	void PutPurpleColor();
	void PutPinkColor();
	void PutYellowColor();
};