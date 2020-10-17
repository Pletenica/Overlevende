#ifndef __AboutWindow_H__
#define __AboutWindow_H__

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "WindowManager.h"
#include "SDL/include/SDL.h"

class AboutWindow : public Window
{
public:

	AboutWindow();

	// Destructor
	virtual ~AboutWindow();

	bool Init();
	bool Draw(float dt);
	bool PreUpdate(float dt);
	bool CleanUp();
};

#endif // __AboutWindow_H__