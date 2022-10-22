#pragma once
#include <vector>
#include <string>
#include "Profile.h"

class Blackjack {

protected:

	void GeneratePlayerCards();
	void GenerateDealerCards();
	void ShowCards();
	std::string VerifyCard(int card);
	int CheckCardPoints(int card, int points, int& ace);
	void RoundSummary(std::string status);
	void ResetGame();

	Profile* profile = profile->GetInstance();

	std::vector<int> m_playerCards;
	std::vector<int> m_dealerCards;
	std::string m_status;
	
	int m_playerPoints;
	int m_playerCardsNumber;
	int m_playerAce;
	int m_dealerPoints;
	int m_dealerCardsNumber;
	int m_dealerAce;

	bool m_isTournament;

	double m_bet;
	double m_credit;

public:

	Blackjack();
	Blackjack(bool isTournament);

	void runGame();
};