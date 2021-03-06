#include "Globals.h"
#include "Application.h"
#include "WindowManager.h"
#include "ModuleFileSystem.h"
#include "ResourcesWindow.h"
#include "Glew/include/glew.h"

#include "Resource.h"

ResourcesWindow::ResourcesWindow() :Window()
{

}

// Destructor
ResourcesWindow::~ResourcesWindow()
{
}

// Called before render is available
bool ResourcesWindow::Init()
{
	bool ret = true;

	principalAsset = Resource("Assets/", true);
	ExternalApp->file_system->GetFilesRecursive(&principalAsset);

	return ret;
}

bool ResourcesWindow::Draw(float dt)
{
	currenttime += dt;

	if (currenttime >= 2) {
		currenttime = 0;
		//principalAsset.~Resource();
		principalAsset.children.clear();
		ExternalApp->file_system->GetFilesRecursive(&principalAsset);
	}

	ImGui::Begin("Resources", NULL);
	ImGui::Text("This is the resources window.");

	RecursiveResourcesDraw(&principalAsset);

	ImGui::End();

	return true;
}

// Called before quitting
bool ResourcesWindow::CleanUp()
{

	return true;
}

// Called before quitting
bool ResourcesWindow::PreUpdate(float dt)
{

	return true;
}

void ResourcesWindow::RecursiveResourcesDraw(Resource* _resource)
{
	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
	if (_resource->children.size() == 0)
	{
		flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
	}

	bool nodeIsOpened = ImGui::TreeNodeEx(_resource, flags, _resource->name.c_str());

	bool showChildren = (_resource->children.size() == 0) ? false : nodeIsOpened;

	if (showChildren == true)
	{
		for (size_t i = 0; i < _resource->children.size(); ++i)
		{
			RecursiveResourcesDraw(&_resource->children[i]);
		}
		ImGui::TreePop();
	}
}