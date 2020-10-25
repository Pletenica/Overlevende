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

	ImGui::End();

	return true;
}

// Called before quitting
bool HierarchyWindow::CleanUp()
{

	return true;
}

// Called before quitting
bool HierarchyWindow::PreUpdate(float dt)
{

	return true;
}