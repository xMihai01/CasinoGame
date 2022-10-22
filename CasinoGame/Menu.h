#pragma once
#include "Roulette.h"
#include "Craps.h"
#include "Lotto.h"
#include "Blackjack.h"
#include "Slot.h"
#include "Doubling.h"
#include "Profile.h"
#include "TournamentBlackjack.h"
#include "TournamentSlot.h"
#include "Shop.h"

class Menu {

protected:

	Profile* profile = nullptr;
	bool gamePlay = true;

public:

	virtual void ShowMenu() = 0;
	virtual void Info() = 0;

};