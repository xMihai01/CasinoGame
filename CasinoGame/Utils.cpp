#pragma once
#include <iostream>
#include "Profile.h"
#include "Shop.h"

double SetBet(double credit) {
    Profile* profile = profile->GetInstance();
    Shop shop;
    double bet, i = 1;
    double maxbet = shop.GetMaxBetValue(profile->GetMaxBetLevel());
    while (i) {
        i = 0;
        std::cout << "BET: ";
        std::cin >> bet;
        if (bet > maxbet) {
            std::cout << "\nERROR: You can't place a bet that is higher than " << maxbet;
            if (!(maxbet == 999999))
                std::cout << "\nUpgrade your max bet in the shop!\n";
            i = 1;
        }
        if (credit < bet) {
            std::cout << "\nERROR: Not enough credits to place bet.\n";
            i = 1;
        }
        else if (bet < 0) {
            std::cout << "\nERROR: Invalid bet.\n";
            i = 1;
        }
    }

    return bet;
}