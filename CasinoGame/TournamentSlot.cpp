#include "TournamentSlot.h"

// DISABLED

TournamentSlot::TournamentSlot()
{
	m_enemyPoints = 0;
	m_points = 0;
	m_tournamentRounds = 0;
	m_tbet = 0;
}

void TournamentSlot::runTournament()
{
	m_points = 0; m_enemyPoints = 0;
	m_tournamentRounds;
	std::cout << "\nSet BET to 0 to exit Slot Tournament\n\n";
	bool keepGoing = true;
	m_tbet = SetBet(profile->GetCredit()); std::cout << "\n";

	while ((keepGoing && m_tbet != 0) && m_tournamentRounds <= 5) {

		m_points = 0; m_enemyPoints = 0;
		m_winnings = 0;
		m_criteria = 0;
		m_bet = 1;
		m_tournamentRounds++;
		std::cout << "ROUND: " << GetRoundStatus();

		m_credit = 0;
		m_isBot = true;
		for (int i = 0; i < 50; i++) {

			GenerateSlotResult();
			ReviewSlotResult();
			CheckSlotResult();

		}
		m_enemyPoints = m_credit;

		if (m_enemyPoints >= 0 && m_enemyPoints <= 40)
			m_enemyPoints -= 5;
		else if (m_enemyPoints > 40 && m_enemyPoints <= 50)
			m_enemyPoints -= 7.5;
		else if (m_enemyPoints > 50 && m_enemyPoints <= 60)
			m_enemyPoints -= 10;
		else if (m_enemyPoints > 60 && m_enemyPoints <= 70)
			m_enemyPoints -= 12.5;
		else if (m_enemyPoints > 70 && m_enemyPoints <= 80)
			m_enemyPoints -= 15;
		else
			m_enemyPoints -= 20;

		m_isBot = false;
		m_credit = 0;
		m_winnings = 0;
		m_criteria = 0;
		for (int i = 0; i < 50; i++) {
			GenerateSlotResult();
			ReviewSlotResult();
			CheckSlotResult();
		}
		m_points = m_credit;

		if (m_points > m_enemyPoints) {
			//win
			TournamentRoundSummary("WIN");
			if (m_tournamentRounds == 5) {
				//win tourney
				profile->SetCredit(profile->GetCredit() + m_tbet * 16);
				TournamentSummary("WIN");
				profile->SetTournamentRounds(profile->GetTournamentRounds() + 1);
				profile->SetTournamentWins(profile->GetTournamentWins() + 1);
				profile->Jackpot(m_tbet);
				profile->GetLevel()->AddLevel(m_tbet);
				break;
			}

		}
		else if (m_points < m_enemyPoints) {
			//lose
			TournamentRoundSummary("LOSE");
			profile->SetCredit(profile->GetCredit() - m_tbet);
			TournamentSummary("LOSE");
			profile->SetTournamentRounds(profile->GetTournamentRounds() + 1);
			profile->SetTournamentWins(profile->GetTournamentWins() + 1);
			profile->Jackpot(m_tbet);
			profile->GetLevel()->AddLevel(m_tbet);
			break;
		}
		else if (m_points == m_enemyPoints) {
			//tie
			TournamentRoundSummary("TIED");
			m_tournamentRounds--;
		}
	}
	
}

std::string TournamentSlot::GetRoundStatus()
{
	if (m_tournamentRounds == 5)
		return "FINAL";
	if (m_tournamentRounds == 4)
		return "SEMI-FINAL";
	if (m_tournamentRounds == 3)
		return "QUARTER-FINAL";
	if (m_tournamentRounds == 2)
		return "2";
	if (m_tournamentRounds == 1)
		return "1";
	return "ERROR";
}

void TournamentSlot::TournamentRoundSummary(std::string status)
{
	std::cout << "\n\n################################# GameSummary #################################\n\n";

	std::cout << "Status: " << status;

	std::cout << "\n\nEnemy points: " << m_enemyPoints;
	std::cout << "\nYour points: " << m_points;

	std::cout << "\n\nRound: " << GetRoundStatus();

	std::cout << "\n\n################################# GameSummary #################################\n\n";
	system("PAUSE");
}

void TournamentSlot::TournamentSummary(std::string status)
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