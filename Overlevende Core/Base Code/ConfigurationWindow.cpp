#include "Globals.h"
#include "Application.h"
#include "ConfigurationWindow.h"
#include "Glew/include/glew.h"
#include "Time.h"

ConfigurationWindow::ConfigurationWindow() :Window()
{
	active = true;
	ms.reserve(50);
	fps.reserve(50);
	NightModeSelected();
	PutBlueColor();
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
	if (ImGui::CollapsingHeader("Hardware Performance")) {
		
		static HardwareInfo specs = ExternalApp->GetHardware();

		ImGui::TextColored(ImVec4(0.5, 0.5, 1.0, 1.0f), "GPUs:");
		ImGui::SameLine();
		ImGui::Text( "%s", specs.GPU);

		ImGui::TextColored(ImVec4(0.5, 0.5, 1.0, 1.0f), "Brand:");
		ImGui::SameLine();
		ImGui::Text("%s", specs.GPU_brand);

		ImGui::TextColored(ImVec4(0.5, 0.5, 1.0, 1.0f), "CPUs:");
		ImGui::SameLine();
		ImGui::Text("%d (Cache: %dkb)", specs.GPUs, specs.CACHE);

		ImGui::TextColored(ImVec4(0.5, 0.5, 1.0, 1.0f), "RAM:");
		ImGui::SameLine();
		ImGui::Text("%.1f Gb", specs.RAM);

		ImGui::TextColored(ImVec4(0.5, 0.5, 1.0, 1.0f), "Caps:");
		ImGui::SameLine();
		ImGui::Text("%s", specs.caps.c_str());

	}
	if (ImGui::CollapsingHeader("Libraries Information")) {

		SDL_version version;
		SDL_GetVersion(&version);
		ImGui::Text("SDL Version:");
		ImGui::SameLine();
		ImGui::Text("%d.%d.%d", version.major, version.minor, version.patch);

	}
	if (ImGui::CollapsingHeader("Main Controls")) {
		ImGui::Text("Mouse");
		ImGui::Text("You can use F1 to disable the grid in the scene window.");
		ImGui::Text("While Right clicking, “WASD” fps-like movement and free look around is enabled.");
		ImGui::Text("Shift will double the speed of movement.");
		ImGui::Text("You can use 0 to deselect the gameobject from the inspector.");
		ImGui::Text("You can use 2 to create empty objects children of the general scene.");

	}
	if (ImGui::CollapsingHeader("Time Configuration")) {

		ImGui::Text("Time: %f", Time::time);
		ImGui::Text("DeltaTime: %f", Time::deltaTime);
		ImGui::Text("Real time DeltaTime: %f", Time::realTimeDeltaTime);
		ImGui::Text("Real time since StartUp: %f", Time::realTimeSinceStartup);
		ImGui::Text("Time scale: %f", Time::timeScale);
	}
	if (ImGui::CollapsingHeader("Choose Theme")) {
		///////////////// MODES ///////////////////////
		static ImVec4 color = ImVec4(ExternalApp->camera->background.r, ExternalApp->camera->background.g, ExternalApp->camera->background.b, ExternalApp->camera->background.a);

		ImGui::Text("Choose your favourite interface mode.");
		

		if (ImGui::ColorEdit3("Background Color##1", (float*)&color)) {
			ExternalApp->camera->SetBackgroundColor(color.x, color.y, color.z, color.w);
		}
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
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);

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

	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.321f, 0.698f, 0.345f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.321f, 0.698f, 0.345f, 1.0f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.321f, 0.698f, 0.345f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.321f, 0.698f, 0.345f, 1.0f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.321f, 0.698f, 0.345f, 1.0f);
	//style.Colors[ImGuiCol_TooltipBg] = ImVec4(0.521f, 0.898f, 0.545f, 1.0f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.321f, 0.698f, 0.345f, 1.0f);

	style.Colors[ImGuiCol_DockingPreview] = ImVec4(0.321f, 0.698f, 0.345f, 1.0f); // Color que es veu quan vas a juntar finestres (quadres)
	style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.321f, 0.698f, 0.345f, 1.0f);// Color que es veu quan vas a juntar finestres en gran(ficar el mateix que a dalt)

}

void ConfigurationWindow::PutBlueColor() {
	isBlueColor = true;
	isGreenColor = false;
	isOrangeColor = false;

	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.1f, 0.502f, 0.808f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.1f, 0.502f, 0.808f, 1.0f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.1f, 0.502f, 0.808f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.1f, 0.502f, 0.808f, 1.0f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.1f, 0.502f, 0.808f, 1.0f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.1f, 0.502f, 0.808f, 1.0f);

	style.Colors[ImGuiCol_DockingPreview] = ImVec4(0.1f, 0.502f, 0.808f, 1.0f); // Color que es veu quan vas a juntar finestres (quadres)
	style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.1f, 0.502f, 0.808f, 1.0f);// Color que es veu quan vas a juntar finestres en gran(ficar el mateix que a dalt)

}

void ConfigurationWindow::PutOrangeColor() {
	isBlueColor = false;
	isGreenColor = false;
	isOrangeColor = true;

	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.925f, 0.533f, 0.356f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.925f, 0.533f, 0.356f, 1.0f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.925f, 0.533f, 0.356f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.925f, 0.533f, 0.356f, 1.0f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.925f, 0.533f, 0.356f, 1.0f);

	style.Colors[ImGuiCol_DockingPreview] = ImVec4(0.925f, 0.533f, 0.356f, 1.0f); // Color que es veu quan vas a juntar finestres (quadres)
	style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.925f, 0.533f, 0.356f, 1.0f);// Color que es veu quan vas a juntar finestres en gran(ficar el mateix que a dalt)

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
	style.Colors[ImGuiCol_Button] = ImVec4(0.8f, 0.8f, 0.8f, 1.0f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.8f, 0.8f, 0.8f, 1.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.9f, 0.9f, 0.9f, 1.0f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.9f, 0.9f, 0.9f, 1.0f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.75f, 0.75f, 0.75f, 1.0f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.75f, 0.75f, 0.75f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.9f, 0.9f, 0.9f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.8f, 0.8f, 0.8f, 1.0f);

	
	

	style.Colors[ImGuiCol_Tab] = ImVec4(0.5f, 0.5f, 0.5f, 0.1f);  //La pestanya que no esta seleccionada, color
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.8f, 0.8f, 0.8f, 1.00f); //Suda de eso
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.8f, 0.8f, 0.8f, 1.0f); //La pestanya que esta seleccionada, color
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.8f, 0.8f, 0.8f, 1.00f); //Quan la ventana no està seleccionada, com es veu la pestanya activa, color
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.8f, 0.8f, 0.8f, 1.00f); //Quan la ventana no està seleccionada, com es veu les pestanyes no actives, color
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
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);

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