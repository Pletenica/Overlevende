#ifndef __InspectorWindow_H__
#define __InspectorWindow_H__

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "WindowManager.h"
#include "SDL/include/SDL.h"

class InspectorWindow : public Window
{
public:

	InspectorWindow();

	// Destructor
	virtual ~InspectorWindow();

	bool Init();
	bool Draw(float dt);
	bool CleanUp();

private:
	bool wireframe_bool = false;
};

#endif // __InspectorWindow_H__