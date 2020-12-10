#include "Globals.h"
#include "Application.h"
#include "WindowManager.h"
#include "AboutWindow.h"
#include "Glew/include/glew.h"

AboutWindow::AboutWindow() :Window()
{
	active = false;
}

// Destructor
AboutWindow::~AboutWindow()
{
}

// Called before render is available
bool AboutWindow::Init()
{
	bool ret = true;

	return ret;
}

bool AboutWindow::Draw(float dt)
{
	ImGui::Begin("About", NULL);

	///////////////// Readme ///////////////////////
	ImGui::Text("This is an engine done by Roger Perez Romera and Josep Sanchez Arbona.");
	ImGui::Text("");
	ImGui::Text("This project began from a subject in the grade Videogamaes Design and Development in CITM UPC Terrassa, we are two in-progress developers");
	ImGui::Text("that want to give the best experience through our engine: Overlende.");
	ImGui::Text("");
	ImGui::Text("Copyright 2020 Josep Sanchez Arbona and Roger Perez Romera.");
	ImGui::Text("Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files");
	ImGui::Text("(the 'Software'), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge,");
	ImGui::Text("publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do");
	ImGui::Text("so, subject to the following conditions:");
	ImGui::Text("");
	ImGui::Text("THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF ");
	ImGui::Text("MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE");
	ImGui::Text("FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION");
	ImGui::Text("WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.");

	if (ImGui::Button("Close Window", ImVec2(100, 25))) {
		active = false;
	}
	ImGui::End();

	return true;
}

// Called before quitting
bool AboutWindow::CleanUp()
{

	return true;
}

// Called before quitting
bool AboutWindow::PreUpdate(float dt)
{

	return true;
}