#pragma once
#include "Profile.h"

class Settings {

protected:

	Profile* profile = nullptr;

public:

	virtual void ChangeSetting() = 0;
	virtual void LoadSetting() = 0;

};