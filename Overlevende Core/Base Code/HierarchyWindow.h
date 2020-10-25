#ifndef __hierarchyWindow_H__
#define __hierarchyWindow_H__

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "WindowManager.h"
#include "SDL/include/SDL.h"

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
};

#endif // __HierarchyWindow_H__