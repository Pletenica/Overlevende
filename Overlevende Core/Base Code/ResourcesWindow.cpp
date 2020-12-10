#include "Globals.h"
#include "Application.h"
#include "WindowManager.h"
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

	return ret;
}

bool ResourcesWindow::Draw(float dt)
{
	ImGui::Begin("Resources", NULL);
	ImGui::Text("This is the resources window.");

	if (principalAsset != nullptr)
		RecursiveResourcesDraw(principalAsset);

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
			RecursiveResourcesDraw(_resource->children[i]);
		}
		ImGui::TreePop();
	}
}