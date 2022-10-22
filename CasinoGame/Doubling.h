#pragma once
#include "SettingDoublingBetDigits.h"

class Doubling : public SettingDoublingBetDigits {

protected:

	double m_initialValue;
	double m_nrDub;
	int m_colorWin;
	bool m_keepGoing;

	double m_bet;
	double m_credit;


public:

	Doubling();

	void runGame();
	void StartDoubling(double& nrDub);
	void ResetGame();

	void GenerateRandomBet();
	std::string GetColor() const;


};