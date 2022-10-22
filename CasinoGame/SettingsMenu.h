#pragma once
#include "Menu.h"

class SettingsMenu : public Menu{

private:

	SettingEnableDoubling sEnableDoubling;
	SettingLottoFoundNumbers sLottoFoundNumber;

public:

	SettingsMenu();

	void ShowMenu();
	void Info();

	void SaveSettings();
	void LoadSettings();

};