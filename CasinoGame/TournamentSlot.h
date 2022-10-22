#pragma once
#include "Slot.h"
#include "Utils.h"

class TournamentSlot : public Slot {

private:

	double m_enemyPoints;
	double m_points;
	int m_tournamentRounds;

	double m_tbet;

public:

	TournamentSlot();

	void runTournament();

	std::string GetRoundStatus();
	void TournamentRoundSummary(std::string status);
	void TournamentSummary(std::string status);


};
