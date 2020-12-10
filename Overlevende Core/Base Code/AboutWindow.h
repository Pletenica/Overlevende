#ifndef __AboutWindow_H__
#define __AboutWindow_H__

#include "Globals.h"

class Window;
class WindowManager;

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