#ifndef __SceneWindow_H__
#define __SceneWindow_H__

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "WindowManager.h"
#include "SDL/include/SDL.h"
#include "ImGuizmo/ImGuizmo.h"

class SceneWindow : public Window
{
public:

	SceneWindow();

	// Destructor
	virtual ~SceneWindow();

	bool Init();
	bool Draw(float dt);
	bool PreUpdate(float dt);
	bool CleanUp();

	void DoGuizmo();

private:
	ImGuizmo::OPERATION gOperation = ImGuizmo::TRANSLATE;
};

#endif // __SceneWindow_H__