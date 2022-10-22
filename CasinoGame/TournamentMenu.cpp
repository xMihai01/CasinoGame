#pragma once
#include "TournamentMenu.h"

TournamentMenu::TournamentMenu()
{
	profile = profile->GetInstance();
}

void TournamentMenu::ShowMenu()
{
	gamePlay = true;
	Info();
	int alg;
	while (profile->GetCredit() > 0 && gamePlay) {

		std:: cout << "\nTournament (-1 for info): "; std::cin >> alg;

		switch (alg) {
		case 1:
			tournamentBlackjack.runTournament();
			break;
		case 2:
			tournamentSlot.runTournament();
			break;
		case 0:
			gamePlay = false;
			break;
		default:
			Info();
			break;
		}
		profile->UpdateProfile();
	}
}

void TournamentMenu::Info()
{

	int level = profile->GetLevel()->GetLevelNumber();
	double exp = profile->GetLevel()->GetLevelExperience();

	std::cout << "\n\n#################### TournamentHall ####################\n\n";

	std::cout << "CREDIT: " << profile->GetCredit();
	std::cout << "\nLevel: " << level;
	std::cout << "\nExperience: " << exp << " (" << profile->GetLevel()->GetRequiredEXP(level)-exp << " more to LEVEL UP)";
	std::cout << "\n\nTournaments played: " << profile->GetTournamentRounds();
	std::cout << "\nTournaments won: " << profile->GetTournamentWins();

	std::cout << "\n\nPress 0 to exit TournamentHall.\n";
	std::cout << "Press 1 to join a Blackjack Tournament.\n";
	//std::cout << "Press 2 to join a Slots Tournament.";

	std::cout << "\n\n#################### TournamentHall ####################\n\n";
}
