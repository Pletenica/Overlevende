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
	if (ImGui::Checkbox("Green", &isNightModeSelected)) {
		isDayModeSelected = false;
		isNightModeSelected = true;
		isLightModeSelected = false;
		PutGreenColor();
	}
	ImGui::SameLine();
	if (ImGui::Checkbox("Blue", &isDayModeSelected)) {
		isDayModeSelected = true;
		isNightModeSelected = false;
		isLightModeSelected = false;
		//PutBlueColor();
	}
	ImGui::SameLine();
	if (ImGui::Checkbox("Purple", &isLightModeSelected)) {
		isDayModeSelected = false;
		isNightModeSelected = false;
		isLightModeSelected = true;
		//PutPurpleColor();
	}

	if (ImGui::Button("Close Window", ImVec2(100, 25))) {
		booleditinterface = false;
	}
	ImGui::End();

}

void EditInterfaceMenu::LightModeSelected() {

	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 0.0f;
	style.FrameRounding = 0.0f;
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

}

void EditInterfaceMenu::PutGreenColor() {

	ImGuiStyle& style = ImGui::GetStyle();

	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.521f, 0.898f, 0.545f, 1.0f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.521f, 0.898f, 0.545f, 1.0f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.521f, 0.898f, 0.545f, 1.0f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.521f, 0.898f, 0.545f, 1.0f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.521f, 0.898f, 0.545f, 1.0f);
	//style.Colors[ImGuiCol_TooltipBg] = ImVec4(0.521f, 0.898f, 0.545f, 1.0f);
}

void EditInterfaceMenu::DayModeSelected() {

	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 5.3f;
	style.FrameRounding = 2.3f;
	style.ScrollbarRounding = 0;

	style.Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);


}

void EditInterfaceMenu::NightModeSelected() {

	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 5.3f;
	style.FrameRounding = 2.3f;
	style.ScrollbarRounding = 0;

	style.Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);


}