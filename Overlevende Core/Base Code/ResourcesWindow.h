#ifndef __ResourcesWindow_H__
#define __ResourcesWindow_H__

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "WindowManager.h"
#include "SDL/include/SDL.h"

class ResourcesWindow : public Window
{
public:

	ResourcesWindow();

	// Destructor
	virtual ~ResourcesWindow();

	bool Init();
	bool Draw(float dt);
	bool PreUpdate(float dt);
	bool CleanUp();
};

#endif // __ResourcesWindow_H__