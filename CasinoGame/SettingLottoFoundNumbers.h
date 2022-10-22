#pragma once
#include "Settings.h"

class SettingLottoFoundNumbers : public Settings {

protected:

	int m_requiredFoundNumbers;

public:

	SettingLottoFoundNumbers();

	int GetRequiredFoundNumbers() const;
	void ChangeSetting();
	void LoadSetting();
};

