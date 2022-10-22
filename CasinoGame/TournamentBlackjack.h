#pragma once
#include "Blackjack.h"
#include "Utils.h"

class TournamentBlackjack : public Blackjack {

private:

	std::string GetRoundStatus();
	void TournamentRoundSummary();
	void TournamentSummary(std::string status);

	int m_tournamentPlayerWins;
	int m_tournamentDealerWins;
	int m_tournamentRounds;
	int m_tournamentMatch;
	double m_tbet;

public:

	TournamentBlackjack();
	void runTournament();

};