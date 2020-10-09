#pragma once
#include "Globals.h"
#include "glmath.h"

//Include ImGui
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_opengl3.h"

class AboutWindow
{
private:
	ImTextureID iconprovingtex;
public:
	AboutWindow();
	~AboutWindow();

	bool boolaboutwindow = true;

	void CreateAboutWindow();

}; 
