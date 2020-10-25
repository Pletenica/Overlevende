#include "Globals.h"
#include "Application.h"
#include "ConfigurationWindow.h"
#include "Glew/include/glew.h"

ConfigurationWindow::ConfigurationWindow() :Window()
{
	active = false;
	ms.reserve(50);
	fps.reserve(50);
	NightModeSelected();
	PutGreenColor();
}

// Destructor
ConfigurationWindow::~ConfigurationWindow()
{
}

// Called before render is available
bool ConfigurationWindow::Init()
{
	bool ret = true;

	return ret;
}

bool ConfigurationWindow::Draw(float dt)
{
	float actualFPS = (1.f / dt);
	float actualMS = (1000.f * dt);
	AddToVector(fps, actualFPS);
	AddToVector(ms, actualMS);

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
		ImGui::PlotHistogram("##framerate", &fps[0], fps.size(), 0, "Framerate", 0.0f, 100.0f, ImVec2(310, 100));
		ImGui::PlotHistogram("##milliseconds", &ms[0], ms.size(), 0, "Milliseconds", 0.0f, 100.0f, ImVec2(310, 100));

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
	if (ImGui::CollapsingHeader("Choose Theme")) {
		///////////////// MODES ///////////////////////
		ImGui::Text("Choose your favourite interface mode.");
		/*
		PER A FER ELS BOTONS EN IMATGES (En un futur)
		if (ImGui::ImageButton(iconprovingtex, ImVec2(100, 40))) {

		}
		*/
		if (ImGui::Checkbox("Night Mode", &isNightModeSelected)) {
			NightModeSelected();
		}
		ImGui::SameLine();
		if (ImGui::Checkbox("Day Mode", &isDayModeSelected)) {
			DayModeSelected();
		}
		ImGui::SameLine();
		if (ImGui::Checkbox("Light Mode", &isLightModeSelected)) {

			LightModeSelected();
		}

		///////////////// COLORS ///////////////////////
		ImGui::Text("Choose your favourite interface color:");
		if (ImGui::Checkbox("Green", &isGreenColor)) {
			PutGreenColor();
		}
		ImGui::SameLine();
		if (ImGui::Checkbox("Blue", &isBlueColor)) {
			PutBlueColor();
		}
		ImGui::SameLine();
		if (ImGui::Checkbox("Orange", &isOrangeColor)) {
			PutOrangeColor();
		}

	}
	if (ImGui::Button("Close Window", ImVec2(100, 25))) {
		active = false;
	}
	ImGui::End();
	return true;
}

// Called before quitting
bool ConfigurationWindow::CleanUp()
{

	return true;
}

void ConfigurationWindow::AddToVector(std::vector<float>& vec, float value)
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


void ConfigurationWindow::LightModeSelected() {
	isDayModeSelected = false;
	isNightModeSelected = false;
	isLightModeSelected = true;

	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 6.0f;
	style.FrameRounding = 3.0f;
	style.ScrollbarRounding = 0;

	style.Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.75f, 0.75f, 0.75f, 1.0f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);

	style.Colors[ImGuiCol_Tab] = ImVec4(0.1f, 0.1f, 0.1f, 0.5f);  //La pestanya que no esta seleccionada, color
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.29f, 0.29f, 0.29f, 1.00f); //Suda de eso
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.4f, 0.4f, 0.4f, 1.0f); //La pestanya que esta seleccionada, color
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f); //Quan la ventana no està seleccionada, com es veu la pestanya activa, color
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f); //Quan la ventana no està seleccionada, com es veu les pestanyes no actives, color
}

void ConfigurationWindow::PutGreenColor() {
	isBlueColor = false;
	isGreenColor = true;
	isOrangeColor = false;
	isPurpleColor = false;
	isPinkColor = false;
	isYellowColor = false;

	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.521f, 0.898f, 0.545f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.521f, 0.898f, 0.545f, 1.0f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.521f, 0.898f, 0.545f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.521f, 0.898f, 0.545f, 1.0f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.521f, 0.898f, 0.545f, 1.0f);
	//style.Colors[ImGuiCol_TooltipBg] = ImVec4(0.521f, 0.898f, 0.545f, 1.0f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.521f, 0.898f, 0.545f, 1.0f);

	style.Colors[ImGuiCol_DockingPreview] = ImVec4(0.388f, 0.592f, 0.4f, 1.0f); // Color que es veu quan vas a juntar finestres (quadres)
	style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.388f, 0.592f, 0.4f, 1.0f);// Color que es veu quan vas a juntar finestres en gran(ficar el mateix que a dalt)

}

void ConfigurationWindow::PutBlueColor() {
	isBlueColor = true;
	isGreenColor = false;
	isOrangeColor = false;
	isPurpleColor = false;
	isPinkColor = false;
	isYellowColor = false;

	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.0f, 0.402f, 0.708f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.0f, 0.402f, 0.708f, 1.0f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.0f, 0.402f, 0.708f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.0f, 0.402f, 0.708f, 1.0f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.0f, 0.402f, 0.708f, 1.0f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.0f, 0.402f, 0.708f, 1.0f);

	style.Colors[ImGuiCol_DockingPreview] = ImVec4(0.0f, 0.402f, 0.708f, 1.0f); // Color que es veu quan vas a juntar finestres (quadres)
	style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.0f, 0.402f, 0.708f, 1.0f);// Color que es veu quan vas a juntar finestres en gran(ficar el mateix que a dalt)

}

void ConfigurationWindow::PutOrangeColor() {
	isBlueColor = false;
	isGreenColor = false;
	isOrangeColor = true;
	isPurpleColor = false;
	isPinkColor = false;
	isYellowColor = false;

	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.925f, 0.733f, 0.556f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.925f, 0.733f, 0.556f, 1.0f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.925f, 0.733f, 0.556f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.925f, 0.733f, 0.556f, 1.0f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.925f, 0.733f, 0.556f, 1.0f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.925f, 0.733f, 0.556f, 1.0f);

	style.Colors[ImGuiCol_DockingPreview] = ImVec4(0.745f, 0.533f, 0.254f, 1.0f); // Color que es veu quan vas a juntar finestres (quadres)
	style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.745f, 0.533f, 0.254f, 1.0f);// Color que es veu quan vas a juntar finestres en gran(ficar el mateix que a dalt)

}

void ConfigurationWindow::DayModeSelected() {
	isDayModeSelected = true;
	isNightModeSelected = false;
	isLightModeSelected = false;



	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 6.0f;
	style.FrameRounding = 3.0f;
	style.ScrollbarRounding = 0;

	style.Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.65f, 0.65f, 0.65f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.8f, 0.8f, 0.8f, 1.0f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.9f, 0.9f, 0.9f, 1.0f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.95f, 0.95f, 0.95f, 1.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.9f, 0.9f, 0.9f, 1.0f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.9f, 0.9f, 0.9f, 1.0f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.75f, 0.75f, 0.75f, 1.0f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.75f, 0.75f, 0.75f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.9f, 0.9f, 0.9f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

	style.Colors[ImGuiCol_Tab] = ImVec4(0.1f, 0.1f, 0.1f, 0.5f);  //La pestanya que no esta seleccionada, color
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.29f, 0.29f, 0.29f, 1.00f); //Suda de eso
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.4f, 0.4f, 0.4f, 1.0f); //La pestanya que esta seleccionada, color
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f); //Quan la ventana no està seleccionada, com es veu la pestanya activa, color
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f); //Quan la ventana no està seleccionada, com es veu les pestanyes no actives, color
}

void ConfigurationWindow::NightModeSelected() {
	isDayModeSelected = false;
	isNightModeSelected = true;
	isLightModeSelected = false;

	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 6.0f;
	style.FrameRounding = 3.0f;
	style.ScrollbarRounding = 0;

	style.Colors[ImGuiCol_Text] = ImVec4(0.9f, 0.9f, 0.9f, 1.0f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.65f, 0.65f, 0.65f, 1.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.35f, 0.35f, 0.35f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

	style.Colors[ImGuiCol_Tab] = ImVec4(0.1f, 0.1f, 0.1f, 0.5f);  //La pestanya que no esta seleccionada, color
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.29f, 0.29f, 0.29f, 1.00f); //Suda de eso
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.4f, 0.4f, 0.4f, 1.0f); //La pestanya que esta seleccionada, color
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.01f, 0.01f, 0.01f, 1.00f); //Quan la ventana no està seleccionada, com es veu la pestanya activa, color
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f); //Quan la ventana no està seleccionada, com es veu les pestanyes no actives, color
}

// Called before quitting
bool ConfigurationWindow::PreUpdate(float dt)
{

	return true;
}