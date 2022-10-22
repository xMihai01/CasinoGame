#pragma once
#include "Profile.h"
#include "SettingLottoFoundNumbers.h"
#include <vector>

class Lotto : public SettingLottoFoundNumbers{

private:

	void SetChoices();
	void SetWinningNumbers();
	void SetFoundNumbers();
	bool ValidateChoices(std::vector<int> vector, int number, int position);
	void RoundSummary();
	void ResetGame();

	Profile* profile = profile->GetInstance();

	std::vector<int> m_winningNumbers;
	std::vector<int> m_choices;
	std::vector<int> m_foundNumbers;

	double m_bet;
	int m_foundNumbersInteger;
	
public:

	Lotto();
	
	void runGame();


};