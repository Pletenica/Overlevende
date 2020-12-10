#include "Globals.h"
#include "Application.h"
#include "Glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include "WindowManager.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */
#pragma comment (lib, "Glew/libx86/glew32.lib") /* link Microsoft OpenGL lib   */

#include "ConsoleWindow.h"
#include "InspectorWindow.h"

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


io.IniFilename = "WindowSaving";
	CreateAllWindows();

return ret;
}

// Load assets
bool ModuleBaseMotor::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleBaseMotor::Draw(float dt)
{
	quit = false;
	SDL_GLContext* test = &App->renderer3D->context;
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();

	//Docking Principal
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::DockSpaceOverViewport(viewport,ImGuiDockNodeFlags_::ImGuiDockNodeFlags_PassthruCentralNode);

	//ImGui Windows
	CreateMainBar();
	
	for (int i = 0; i < App->window_manager->windows.size(); i++)
	{
		if (App->window_manager->windows[i]->active == true) {
			App->window_manager->windows[i]->Draw(dt);
		}
	}

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
			if (ImGui::MenuItem("Save Project")) {
				App->scene_intro->Save("Library/Scenes/Scene.json");
			}
			if (ImGui::MenuItem("Open Project")) {
				App->scene_intro->Load("Library/Scenes/Scene.json");
			}
			if (ImGui::MenuItem("Configuration")) {
				configuration_window->active = true;
			}
			if (ImGui::MenuItem("Exit")) {
				quit = true;
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help", true)) {
			if (ImGui::MenuItem("Documentation")) {
				ShellExecuteA(NULL, "open", "https://github.com/Pletenica/Overlevende/wiki", NULL, NULL, SW_SHOWNORMAL);
			}
			if (ImGui::MenuItem("Download Latest")) {
				ShellExecuteA(NULL, "open", "https://github.com/Pletenica/Overlevende/releases", NULL, NULL, SW_SHOWNORMAL);
			}
			if (ImGui::MenuItem("Report a bug")) {
				ShellExecuteA(NULL, "open", "https://github.com/Pletenica/Overlevende/issues", NULL, NULL, SW_SHOWNORMAL);
			}
			if (ImGui::MenuItem("About")) {
				about_window->active = true;
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

void ModuleBaseMotor::CreateAllWindows() {
	inspector_window=(InspectorWindow*)App->window_manager->CreateWin(WindowType::Inspector);
	configuration_window = (ConfigurationWindow*)App->window_manager->CreateWin(WindowType::Configuration);
	about_window = (AboutWindow*)App->window_manager->CreateWin(WindowType::About);
	console_window = (ConsoleWindow*)console_window = (ConsoleWindow*)App->window_manager->CreateWin(WindowType::Console);
	scene_window = (SceneWindow*)App->window_manager->CreateWin(WindowType::Scene);
	options_window = (OptionsWindow*)options_window = (OptionsWindow*)App->window_manager->CreateWin(WindowType::Options);
	hierarchy_window = (HierarchyWindow*)App->window_manager->CreateWin(WindowType::Hierarchy);
	resources_window = (ResourcesWindow*)App->window_manager->CreateWin(WindowType::Resources);
}