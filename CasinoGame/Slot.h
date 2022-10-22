#pragma once
#include <vector>
#include "Profile.h"
#include "SettingEnableDoubling.h"

class Slot : public SettingEnableDoubling {

protected:

	void GenerateSlotResult();
	void ReviewSlotResult();
	void CheckSlotResult();
	void checkSlotWin(int value);
	void ResetGame();

	
	Profile* profile = profile->GetInstance();
	std::vector<std::vector<int>> m_slotMachineScreen;
	double m_winnings;
	double m_criteria;
	bool m_isBot;

	double m_bet;
	double m_credit;
	

public:

	Slot();

	void runGame();

};