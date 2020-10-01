#include "Globals.h"
#include "Application.h"
#include "ModuleBaseMotor.h"
#include "Glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */
#pragma comment (lib, "Glew/libx86/glew32.lib") /* link Microsoft OpenGL lib   */

ModuleBaseMotor::ModuleBaseMotor(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleBaseMotor::~ModuleBaseMotor()
{}

// Load assets
bool ModuleBaseMotor::Init()
{
	LOG("Creating Base Motor context");
	bool ret = true;

	//ImGui (to do new module in future)
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

ImGuiIO& io = ImGui::GetIO(); (void)io;
io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
ImGui_ImplOpenGL3_Init();

return ret;
}

// Load assets
bool ModuleBaseMotor::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleBaseMotor::PostUpdate(float dt)
{
	quit = false;
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();

	//ImGui Windows
	CreateMainBar();
	CreateTestWindow();
	if(booleditinterface==true)CreateEditInterfaceMenu();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
		SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
	}

	if (quit == true) {
		return UPDATE_STOP;
	}
	else {
		return UPDATE_CONTINUE;
	}
}

void ModuleBaseMotor::CreateMainBar() {
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("Edit", true)) {
			if (ImGui::MenuItem("New Project")) {

			}
			if (ImGui::MenuItem("Open Project")) {

			}
			if (ImGui::MenuItem("Save Project")) {

			}
			if (ImGui::MenuItem("Interface colors")) {
				booleditinterface = true;
			}
			if (ImGui::MenuItem("Exit")) {
				quit = true;
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Github", true)) {
			if (ImGui::MenuItem("Github Web")) {

			}
			if (ImGui::MenuItem("Github Repository: Overlevende")) {
				ShellExecuteA(NULL, "open", "https://github.com/Pletenica/Overlevende", NULL, NULL, SW_SHOWNORMAL);
			}
			if (ImGui::MenuItem("Github Pletenica")) {
				ShellExecuteA(NULL, "open", "https://github.com/Pletenica", NULL, NULL, SW_SHOWNORMAL);
			}
			if (ImGui::MenuItem("Between Worlds(Soon)")) {
				ShellExecuteA(NULL, "open", "https://github.com/Pletenica/Between-Worlds", NULL, NULL, SW_SHOWNORMAL);
			}

			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}


}

void ModuleBaseMotor::CreateTestWindow() {
	ImGui::ShowDemoWindow();



	
}

void ModuleBaseMotor::CreateEditInterfaceMenu() {
	ImGui::Begin("Edit Interface", NULL);
	ImGui::Text("Choose your favourite interface mode.");
	if (ImGui::Button("Night Mode", ImVec2(100, 25))) {
		
	}
	ImGui::SameLine();
	if (ImGui::Button("Day Mode", ImVec2(100, 25))) {
		
	}
	ImGui::SameLine();
	if (ImGui::Button("Light Mode", ImVec2(100, 25))) {
		
	}
	if (ImGui::Button("Close Window", ImVec2(100, 25))) {
		booleditinterface = false;
	}
	ImGui::End();




}