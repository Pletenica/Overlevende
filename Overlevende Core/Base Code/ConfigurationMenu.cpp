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


	
	


	if (ImGui::Button("Close Window", ImVec2(100, 25))) {
		boolconfigurationmenu = false;
	}
	ImGui::End();

}