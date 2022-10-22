#pragma once
#include "Profile.h"

class Craps {

private:

	void GenerateRandomDice(int& player);
	void RoundSummaryCraps();

	Profile* profile = profile->GetInstance();

	double m_bet;
	int m_player;
	int m_dealer;

public:

	Craps();

	void runGame();

};