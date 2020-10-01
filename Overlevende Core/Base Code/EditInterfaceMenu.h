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
private:
	ImTextureID iconprovingtex;
public:
	EditInterfaceMenu();
	~EditInterfaceMenu();

	bool booleditinterface = false;

	bool isNightModeSelected = true;
	bool isDayModeSelected = false;
	bool isLightModeSelected = false;

	void LightModeSelected();
	void NightModeSelected();
	void DayModeSelected();

	void CreateMainBar();
	void CreateTestWindow();
	void CreateEditInterfaceMenu();

	bool isBlueColor = true;
	bool isGreenColor = false;
	bool isOrangeColor = false;
	bool isPurpleColor = false;
	bool isPinkColor = false;
	bool isYellowColor = false;

	void PutBlueColor();
	void PutGreenColor();
	void PutOrangeColor();
	void PutPurpleColor();
	void PutPinkColor();
	void PutYellowColor();
};