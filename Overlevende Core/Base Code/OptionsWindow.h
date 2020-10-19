#ifndef __OptionsWindow_H__
#define __OptionsWindow_H__

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "WindowManager.h"
#include "SDL/include/SDL.h"

class OptionsWindow : public Window
{
public:

	OptionsWindow();

	// Destructor
	virtual ~OptionsWindow();

	bool Init();
	bool Draw(float dt);
	bool PreUpdate(float dt);
	bool CleanUp();

private:
	bool wireframe_bool = false;
};

#endif // __OptionsWindow_H__