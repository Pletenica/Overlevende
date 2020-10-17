#ifndef __ConfigurationWindow_H__
#define __ConfigurationWindow_H__

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "WindowManager.h"
#include "SDL/include/SDL.h"

class ConfigurationWindow : public Window
{
public:

	ConfigurationWindow();

	// Destructor
	virtual ~ConfigurationWindow();

	bool Init();
	bool Draw(float dt);
	bool PreUpdate(float dt);
	bool CleanUp();

	void AddToVector(std::vector<float>& vec, float value);

private:
	ImTextureID iconprovingtex;
	std::vector<float> fps;
	std::vector<float> ms;

	bool isNightModeSelected = true;
	bool isDayModeSelected = false;
	bool isLightModeSelected = false;

	void LightModeSelected();
	void NightModeSelected();
	void DayModeSelected();

	void CreateMainBar();
	void CreateTestWindow();
	void CreateEditInterfaceMenu();

	bool isBlueColor = true;
	bool isGreenColor = false;
	bool isOrangeColor = false;
	bool isPurpleColor = false;
	bool isPinkColor = false;
	bool isYellowColor = false;

	void PutBlueColor();
	void PutGreenColor();
	void PutOrangeColor();
	void PutPurpleColor();
	void PutPinkColor();
	void PutYellowColor();

};

#endif // __ConfigurationWindow_H__