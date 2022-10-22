#pragma once
#include "Menu.h"

class TournamentMenu : public Menu {

private:

	TournamentBlackjack tournamentBlackjack;
	TournamentSlot tournamentSlot;

public:

	TournamentMenu();

	void ShowMenu();
	void Info();

};