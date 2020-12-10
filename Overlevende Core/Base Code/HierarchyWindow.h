#ifndef __hierarchyWindow_H__
#define __hierarchyWindow_H__

#include "Globals.h"

class WindowManager;
class GameObject;

class HierarchyWindow : public Window
{
public:

	HierarchyWindow();

	// Destructor
	virtual ~HierarchyWindow();

	bool Init();
	bool Draw(float dt);
	bool PreUpdate(float dt);
	bool CleanUp();

	void RecursiveDraw(GameObject* node);

private:
	GameObject* dropGO = nullptr;
};

#endif // __HierarchyWindow_H__