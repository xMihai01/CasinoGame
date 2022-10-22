#pragma once
#include "Settings.h"

class SettingEnableDoubling : public Settings {

protected:

	bool m_enableDoubling;

public:

	SettingEnableDoubling();

	bool GetDoublingSettingValue() const;
	void SetDoublingSettingValue(bool enableDoubling);
	void ChangeSetting();
	void LoadSetting();

	

};