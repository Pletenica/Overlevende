#ifndef __ConsoleWindow_H__
#define __ConsoleWindow_H__

#include "Globals.h"

#include "WindowManager.h"

class ConsoleWindow : public Window
{
public:

	ConsoleWindow();

	// Destructor
	virtual ~ConsoleWindow();

	bool Init();
	bool Draw(float dt);
	bool PreUpdate(float dt);
	bool CleanUp();

	void AddConsoleLog(const char* log);

public:
	std::vector<std::string> console_log;
};

#endif // __ConsoleWindow_H__