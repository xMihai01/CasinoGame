#pragma once
#include <iostream>
#include <fstream>
#include "Menu.h"
#include "TournamentMenu.h"
#include "ShopMenu.h"
#include "SettingsMenu.h"

class GameMenu : public Menu{

private:

	Roulette r;
	Craps cr;
	Lotto lotto;
	Blackjack bj;
	Slot slot;
	Doubling d;
	TournamentMenu tMenu;
	ShopMenu sMenu;
	SettingsMenu settingsMenu;

public:

	GameMenu();

	void ShowMenu();
	void Welcome();
	void Info();
};
