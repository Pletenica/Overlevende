#include "EditInterfaceMenu.h"
#include "Glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */
#pragma comment (lib, "Glew/libx86/glew32.lib") /* link Microsoft OpenGL lib   */

EditInterfaceMenu::EditInterfaceMenu()
{

}

EditInterfaceMenu::~EditInterfaceMenu()
{}

void EditInterfaceMenu::CreateEditInterfaceMenu() {
	ImGui::Begin("Edit Interface", NULL);

	///////////////// MODES ///////////////////////
	ImGui::Text("Choose your favourite interface mode.");
	/*
	PER A FER ELS BOTONS EN IMATGES (En un futur)
	if (ImGui::ImageButton(iconprovingtex, ImVec2(100, 40))) {

	}
	*/
	if (ImGui::Checkbox("Night Mode", &isNightModeSelected)) {
		isDayModeSelected = false;
		isNightModeSelected = true;
		isLightModeSelected = false;
		NightModeSelected();
	}
	ImGui::SameLine();
	if (ImGui::Checkbox("Day Mode", &isDayModeSelected)) {
		isDayModeSelected = true;
		isNightModeSelected = false;
		isLightModeSelected = false;
		DayModeSelected();
	}
	ImGui::SameLine();
	if (ImGui::Checkbox("Light Mode", &isLightModeSelected)) {
		isDayModeSelected = false;
		isNightModeSelected = false;
		isLightModeSelected = true;
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

	if (ImGui::Button("Close Window", ImVec2(100, 25))) {
		booleditinterface = false;
	}
	ImGui::End();

}

void EditInterfaceMenu::LightModeSelected() {

	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 6.0f;
	style.FrameRounding = 3.0f;
	style.ScrollbarRounding = 0;

	style.Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.35f, 0.35f, 0.35f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.35f, 0.35f, 0.35f, 1.0f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.35f, 0.35f, 0.35f, 1.0f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.35f, 0.35f, 0.35f, 1.0f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.35f, 0.35f, 0.35f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);

	style.Colors[ImGuiCol_Tab] = ImVec4(0.1f, 0.1f, 0.1f, 0.5f);  //La pestanya que no esta seleccionada, color
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.29f, 0.29f, 0.29f, 1.00f); //Suda de eso
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.4f, 0.4f, 0.4f, 1.0f); //La pestanya que esta seleccionada, color
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f); //Quan la ventana no està seleccionada, com es veu la pestanya activa, color
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f); //Quan la ventana no està seleccionada, com es veu les pestanyes no actives, color
}

void EditInterfaceMenu::PutGreenColor() {
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

void EditInterfaceMenu::PutBlueColor() {
	isBlueColor = true;
	isGreenColor = false;
	isOrangeColor = false;
	isPurpleColor = false;
	isPinkColor = false;
	isYellowColor = false;

	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.556f, 0.756f, 0.925f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.556f, 0.756f, 0.925f, 1.0f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.556f, 0.756f, 0.925f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.556f, 0.756f, 0.925f, 1.0f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.556f, 0.756f, 0.925f, 1.0f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.556f, 0.756f, 0.925f, 1.0f);

	style.Colors[ImGuiCol_DockingPreview] = ImVec4(0.250f, 0.415f, 0.529f, 1.0f); // Color que es veu quan vas a juntar finestres (quadres)
	style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.250f, 0.415f, 0.529f, 1.0f);// Color que es veu quan vas a juntar finestres en gran(ficar el mateix que a dalt)

}

void EditInterfaceMenu::PutOrangeColor() {
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

void EditInterfaceMenu::DayModeSelected() {

	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 6.0f;
	style.FrameRounding = 3.0f;
	style.ScrollbarRounding = 0;

	style.Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.9f, 0.9f, 0.9f, 1.0f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.6f, 0.6f, 0.6f, 1.0f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.65f, 0.65f, 0.65f, 1.0f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.8f, 0.8f, 0.8f, 1.0f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.85f, 0.85f, 0.85f, 1.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.8f, 0.8f, 0.8f, 1.0f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.8f, 0.8f, 0.8f, 1.0f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.75f, 0.75f, 0.75f, 1.0f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.75f, 0.75f, 0.75f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.8f, 0.8f, 0.8f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.8f, 0.8f, 0.8f, 1.0f);

	style.Colors[ImGuiCol_Tab] = ImVec4(0.1f, 0.1f, 0.1f, 0.5f);  //La pestanya que no esta seleccionada, color
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.29f, 0.29f, 0.29f, 1.00f); //Suda de eso
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.4f, 0.4f, 0.4f, 1.0f); //La pestanya que esta seleccionada, color
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f); //Quan la ventana no està seleccionada, com es veu la pestanya activa, color
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f); //Quan la ventana no està seleccionada, com es veu les pestanyes no actives, color
}

void EditInterfaceMenu::NightModeSelected() {

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
	style.Colors[ImGuiCol_Button] = ImVec4(0.6f, 0.6f, 0.6f, 1.0f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.65f, 0.65f, 0.65f, 1.0f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.35f, 0.35f, 0.35f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);

	style.Colors[ImGuiCol_Tab] = ImVec4(0.1f, 0.1f, 0.1f, 0.5f);  //La pestanya que no esta seleccionada, color
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.29f, 0.29f, 0.29f, 1.00f); //Suda de eso
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.4f, 0.4f, 0.4f, 1.0f); //La pestanya que esta seleccionada, color
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.01f, 0.01f, 0.01f, 1.00f); //Quan la ventana no està seleccionada, com es veu la pestanya activa, color
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f); //Quan la ventana no està seleccionada, com es veu les pestanyes no actives, color
}