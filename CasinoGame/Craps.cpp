#pragma once
#include <iostream>
#include "Craps.h"
#include "Utils.h"

Craps::Craps()
{
	m_bet = -1;
	m_player = 0;
	m_dealer = 0;
}

void Craps::runGame()
{

	std::cout << "\n\nWARNING! Placing the bet will automatically roll the dices!";
	std::cout << "\nSet the BET to 0 to exit Craps (Barbut).\n\n";

	while (profile->GetCredit() > 0) {

		m_bet = SetBet(profile->GetCredit()); std::cout << "\n";

		if (m_bet == 0) {
			break;
		}

		profile->GetLevel()->AddLevel(m_bet);
		profile->Jackpot(m_bet);

		GenerateRandomDice(m_player);
		GenerateRandomDice(m_dealer);

		RoundSummaryCraps();

		profile->SetCredit(profile->GetCredit() + m_bet);
		profile->SetCrapsRounds(profile->GetCrapsRounds() + 1);

	}

}

void Craps::GenerateRandomDice(int& player)
{
	player = 0;
	for (int i = 0; i < 2; i++) {
		player += rand() % 6 + 1;
	}
	if (player == 2)
		player = 13;
}

void Craps::RoundSummaryCraps() {


	std::cout << "\n\n################################# RoundSummary #################################\n\n";

	std::cout << "Dealer dice points: ";
	if (m_dealer == 13)
		std::cout << "2";
	else
		std::cout << m_dealer;
	std::cout << "		Your dice points: ";
	if (m_player == 13)
		std::cout << "2";
	else
		std::cout << m_player;
	std::cout << "\n\n";

	if (m_player < m_dealer) {
		m_bet -= m_bet * 2;
		std::cout << "CREDIT lost: " << -m_bet << "\n";
	}
	else if (m_player > m_dealer) {
		std::cout << "CREDIT won: " << m_bet << "\n";
	}
	else {
		std::cout << "You didn't lose/win any credits!\n";
		m_bet = 0;
	}
	std::cout << "CREDIT remaining " << profile->GetCredit() + m_bet;
	std::cout << "\n\n################################# RoundSummary #################################\n\n";

}
