#include "Globals.h"
#include "Application.h"
#include "ModuleBaseMotor.h"
#include "ConfigurationMenu.h"
#include "Glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>



ConfigurationMenu::ConfigurationMenu()
{
	ms.reserve(50);
	fps.reserve(50);
}

ConfigurationMenu::~ConfigurationMenu()
{}

void ConfigurationMenu::CreateConfigurationMenu(float dt) {
	
	float actualFPS = (1.f / dt);
	float actualMS = (1000.f * dt);
	AddToVector(fps, actualFPS);
	AddToVector(ms, actualMS);

	ImGui::Begin("WireFrame", NULL);
	
	if (ImGui::Checkbox("WireFrame Mode", &wireSphere)) {
		(wireSphere) ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	
	ImGui::End();


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
		ImGui::PlotHistogram("##framerate", &fps[0], fps.size(), 0,"Framerate", 0.0f, 100.0f, ImVec2(310, 100));
		ImGui::PlotHistogram("##milliseconds",&ms[0], ms.size(), 0, "Milliseconds", 0.0f, 100.0f, ImVec2(310, 100));
		
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

void ConfigurationMenu::AddToVector(std::vector<float>& vec, float value)
{
	

	if (vec.size() == 50) {

		for (unsigned int i = 0; i < vec.size(); i++)
		{
			if (i + 1 < vec.size()) {
				float iCopy = vec[i + 1];
				vec[i] = iCopy;
			}
		}
		vec[vec.capacity() - 1] = value;
	}
	else {
		vec.push_back(value);
	}
}
