#pragma once
#include "Profile.h"

class Roulette {

	void SetColorName();
	bool CheckIfWinner();

	Profile* profile = profile->GetInstance();
	
	double m_bet;
	int m_colorPicked;
	std::string m_colorName;
	int m_numberPicked;

public:

	Roulette();

	void runGame();

};