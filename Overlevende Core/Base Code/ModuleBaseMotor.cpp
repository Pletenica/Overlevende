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

}

void ModuleBaseMotor::CreateTestWindow() {
	ImGui::Begin("Test", NULL);
	ImGui::Text("hola que tal mochuletes.");
	if (ImGui::Button("pene", ImVec2(50, 50))) {
		quit = true;
	}
	ImGui::End();

	ImGui::Begin("Test2", NULL);
	ImGui::Text("hola que tal mochuletes.");
	ImGui::End();
}