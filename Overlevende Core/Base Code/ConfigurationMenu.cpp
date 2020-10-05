#include "ConfigurationMenu.h"
#include "Glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */
#pragma comment (lib, "Glew/libx86/glew32.lib") /* link Microsoft OpenGL lib   */

ConfigurationMenu::ConfigurationMenu()
{

}

ConfigurationMenu::~ConfigurationMenu()
{}

void ConfigurationMenu::CreateConfigurationMenu() {
	ImGui::Begin("Configuration", NULL);

	///////////////// MODES ///////////////////////
	ImGui::Text("Choose your favourite settings for a better use.");
	/*
	PER A FER ELS BOTONS EN IMATGES (En un futur)
	if (ImGui::ImageButton(iconprovingtex, ImVec2(100, 40))) {

	}
	*/
	
	if (ImGui::CollapsingHeader("General Settings")) {
		ImGui::Text("Window Size");
		ImGui::Text("Brightness");
		
	}
	if (ImGui::CollapsingHeader("Render Sync")) {
		ImGui::Text("Coming Soon.");

	}
	if (ImGui::CollapsingHeader("Input Readings")) {
		ImGui::Text("Mouse");
		ImGui::Text("F1				Show/Hide Grid");

	}
	if (ImGui::CollapsingHeader("Audio")) {
		ImGui::Text("No audio so far.");

	}
	if (ImGui::CollapsingHeader("Textures")) {
		ImGui::Text("Estandar Textures.");

	}

	
	


	if (ImGui::Button("Close Window", ImVec2(100, 25))) {
		boolconfigurationmenu = false;
	}
	ImGui::End();

}