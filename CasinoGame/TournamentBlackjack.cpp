#include "TournamentBlackjack.h"
#pragma once

TournamentBlackjack::TournamentBlackjack() : Blackjack(true)
{
	m_tournamentDealerWins = 0;
	m_tournamentPlayerWins = 0;
	m_tournamentMatch = 1;
	m_tournamentRounds = 0;
	m_tbet = -1;
	m_credit = profile->GetCredit();
}

void TournamentBlackjack::runTournament()
{

	std::cout << "\nSet BET to 0 to exit Blackjack Tournament\n\n";

	m_tbet = SetBet(m_credit); std::cout << "\n";

	while (m_tbet != 0) {

		m_tournamentRounds++;
		std::cout << "\nGame: " << m_tournamentRounds << "\n";
		std::cout << "Round: " << GetRoundStatus() << "\n\n";
		
		runGame();
		TournamentRoundSummary();

		// check who wins the round

		if (m_tournamentPlayerWins == 5) {
			m_tournamentPlayerWins = 0;
			m_tournamentDealerWins = 0;
			m_tournamentRounds = 0;
			m_tournamentMatch++;


			if (m_tournamentMatch == 6) {
				profile->SetCredit(profile->GetCredit() + m_tbet * 16);
				TournamentSummary("WIN");
				profile->GetLevel()->AddLevel(m_tbet*16);
				profile->Jackpot(m_bet);
				profile->SetTournamentWins(profile->GetTournamentWins() + 1);
				profile->SetTournamentRounds(profile->GetTournamentRounds() + 1);
				break;
				
			}
			std::cout << "\n\nYou have advanced to the next round!\n\n";
		}
		else if (m_tournamentDealerWins == 5) {
			profile->SetCredit(profile->GetCredit() - m_tbet);
			TournamentSummary("LOSE");
			std::cout << "\n\nYou have been eliminated!\n\n";
			profile->Jackpot(m_bet);
			profile->GetLevel()->AddLevel(m_tbet);
			profile->SetTournamentRounds(profile->GetTournamentRounds() + 1);
			break;
		}
		ResetGame();
	}

}

std::string TournamentBlackjack::GetRoundStatus()
{
	if (m_tournamentMatch == 5)
		return "FINAL";
	if (m_tournamentMatch == 4)
		return "SEMI-FINAL";
	if (m_tournamentMatch == 3)
		return "QUARTER-FINAL";
	if (m_tournamentMatch == 2)
		return "2";
	if (m_tournamentMatch == 1)
		return "1";
	return "ERROR";
}

void TournamentBlackjack::TournamentRoundSummary()
{
	int zece = 0;
	int spatiu = 0;

	std::cout << "\n\n################################# GameSummary #################################\n\n";

	std::cout << "Status: " << m_status;

	std::cout << "\n\nDealer Cards: | ";
	for (int i = 0; i < m_dealerCardsNumber; i++) {
		std::cout << VerifyCard(m_dealerCards[i]) << " | ";
		if (m_dealerCards[i] == 10)
			zece++;
	}


	for (int i = 0; i < m_dealerCardsNumber; i++) {
		std::cout << "    ";
	}

	std::cout << "Your cards: | ";
	for (int i = 0; i < m_playerCardsNumber; i++) {
		std::cout << VerifyCard(m_playerCards[i]) << " | ";
	}
	std::cout << "\nDealer Points: " << m_dealerPoints;
	std::cout << "       ";
	for (int i = 0; i < m_dealerCardsNumber; i++) {
		std::cout << "    ";
		if (i > 1)
			std::cout << "    ";
		if (zece > 0) {
			std::cout << " ";
			zece--;
		}
	}
	std::cout << "Your Points: " << m_playerPoints;

	std::cout << "\n\n";
	if (m_status == "LOSE") {
		m_tournamentDealerWins++;
		std::cout << "Player game wins: " << m_tournamentPlayerWins << "\n";
		std::cout << "Enemy game wins: " << m_tournamentDealerWins;
	}
	else if (m_status == "WIN") {
		m_tournamentPlayerWins++;
		std::cout << "Player game wins: " << m_tournamentPlayerWins << "\n";
		std::cout << "Enemy game wins: " << m_tournamentDealerWins;
	}
	else {
		m_tournamentRounds--;
		std::cout << "This round is going to be repeated!";
	}
	std::cout << "\n\nROUND: " << GetRoundStatus();

	std::cout << "\n\n################################# GameSummary #################################\n\n";
	system("PAUSE");
}

void TournamentBlackjack::TournamentSummary(std::string status)
{
	std::cout << "\n\n################################# TournamentSummary #################################\n\n";
	std::cout << "Status: " << status << "\n\n";
	if (status == "WIN") {
		std::cout << "Winner: " << profile->GetUsername();
		std::cout << "\n\nCREDIT won: " << m_tbet * 16;
	}
	else {
		std::cout << "Winner: BOT_NUMBER" << rand() % 1000;
		std::cout << "\n\nCREDIT lost: " << m_tbet;
	}
	std::cout << "\nCREDIT remaining: " << profile->GetCredit();

	std::cout << "\n\n################################# TournamentSummary #################################\n\n";

}
