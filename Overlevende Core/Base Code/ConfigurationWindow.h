#ifndef __ConfigurationWindow_H__
#define __ConfigurationWindow_H__

#include "Globals.h"

class WindowManager;

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

public:
	bool isBlueColor = true;
	bool isGreenColor = false;
	bool isOrangeColor = false;

	bool isNightModeSelected = true;
	bool isDayModeSelected = false;
	bool isLightModeSelected = false;

private:
	ImTextureID iconprovingtex;
	std::vector<float> fps;
	std::vector<float> ms;

	void LightModeSelected();
	void NightModeSelected();
	void DayModeSelected();

	void CreateMainBar();
	void CreateTestWindow();
	void CreateEditInterfaceMenu();

	void PutBlueColor();
	void PutGreenColor();
	void PutOrangeColor();
	void PutPurpleColor();
	void PutPinkColor();
	void PutYellowColor();

};

#endif // __ConfigurationWindow_H__