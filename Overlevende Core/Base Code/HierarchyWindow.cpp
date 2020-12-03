#include "Globals.h"
#include "Application.h"
#include "HierarchyWindow.h"
#include "Glew/include/glew.h"

HierarchyWindow::HierarchyWindow() :Window()
{
	active = true;
}

// Destructor
HierarchyWindow::~HierarchyWindow()
{
}

// Called before render is available
bool HierarchyWindow::Init()
{
	bool ret = true;

	return ret;
}

bool HierarchyWindow::Draw(float dt)
{
	ImGui::Begin("Hierarchy", NULL);
	if (ImGui::Button("CREATE EMPTY ROOT", ImVec2(130, 20))) {
		ExternalApp->scene_intro->CreateGameObject("Empty GameObject", ExternalApp->scene_intro->rootGO);
	}
	ImGui::SameLine();
	if (ImGui::Button("CREATE EMPTY SELECTED", ImVec2(170, 20))) {
		if (ExternalApp->base_motor->inspector_window->_selectedGO != nullptr) {
			ExternalApp->scene_intro->CreateGameObject("Empty GameObject", ExternalApp->base_motor->inspector_window->_selectedGO);
		}
	}
	if (ImGui::Button("CLEAR", ImVec2(70, 20))) {
		ExternalApp->base_motor->inspector_window->DeleteSelectedGameObject();
		ExternalApp->scene_intro->ClearHierarchy();
	}
	if(ExternalApp->scene_intro->rootGO != nullptr)
		RecursiveDraw(ExternalApp->scene_intro->rootGO);
	
	ImGui::End();

	return true;
}

// Called before quitting
bool HierarchyWindow::CleanUp()
{

	return true;
}

void HierarchyWindow::RecursiveDraw(GameObject* node)
{

	ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
	if (node->children.size() == 0) 
	{
		flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
	}

	bool nodeIsOpened = ImGui::TreeNodeEx(node, flags, node->name.c_str());
	if (ImGui::IsItemClicked()) {
		ExternalApp->base_motor->inspector_window->PutNewSelectedGameObject(node);
	}

	if (ImGui::BeginDragDropSource()) {
		ImGui::SetDragDropPayload("_go", node, sizeof(GameObject*));
		dropGO = node;
		ImGui::Text("Changing parent...");
		ImGui::EndDragDropSource();
	}
	bool showChildren = (node->children.size() == 0) ? false : nodeIsOpened;

	if (ImGui::BeginDragDropTarget()) {
		if (const ImGuiPayload* payLoad = ImGui::AcceptDragDropPayload("_go")) {
			//Reparent
			dropGO->ChangeParent(node);

			//Tornem a posar a null el drop (fuera memory leaks)
			dropGO = nullptr;
		}
		ImGui::EndDragDropTarget();
	}


	if (showChildren == true)
	{
		for (size_t i = 0; i < node->children.size(); ++i)
		{
			RecursiveDraw(node->children[i]);
		}
		ImGui::TreePop();
	}
}

// Called before quitting
bool HierarchyWindow::PreUpdate(float dt)
{

	return true;
}