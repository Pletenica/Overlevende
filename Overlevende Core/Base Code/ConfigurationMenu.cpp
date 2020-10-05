#include "Globals.h"
#include "Application.h"
#include "ConfigurationMenu.h"
#include "Glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>



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
	if (ImGui::CollapsingHeader("Application")) {
		/*char name[25];
		sprintf_s(name, 25, "Framerate %.1f", fps_log[fps_log.size() - 1]);
		ImGui::PlotHistogram("##Framerate", &fps_log.size(), 0, name, 0.0f, 100.0f, ImVec2(310, 100));
		sprintf_s(name, 25, "Milliseconds %.1f", ms_log[ms_log.size() - 1]);
		ImGui::PlotHistogram("##Milliseconds", &ms_log.size(), 0, name, 0.0f, 100.0f, ImVec2(310, 100));
		*/
	}
	if (ImGui::CollapsingHeader("General Settings")) {
		ImGui::Text("Window Size:"); 
		/*if (ImGui::Checkbox("Fullscreen", &fullscreen)) {
			
		}*/
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