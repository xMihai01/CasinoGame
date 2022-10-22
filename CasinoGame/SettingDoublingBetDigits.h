#pragma once
#include "Settings.h"

class SettingDoublingBetDigits : public Settings {

protected:

	int m_betDigits;

public:

	SettingDoublingBetDigits();

	void ChangeSetting();
	void LoadSetting();

};