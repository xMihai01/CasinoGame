#pragma once
#include "Profile.h"

class Shop {
	
private:

	double m_maxBetUpgradeCost[15] = { 2000, 5000, 20000, 40000, 75000, 150000, 500000, 1000000, 10000000, 50000000,
	150000000,1000000000,5000000000,100000000000, -1 };
	double m_getMaxBetValue[15] = { 500, 1000, 2000, 3500, 5000, 7500, 10000, 25000, 50000, 100000,
	200000, 300000, 5000000,750000, 999999 };

	Profile* profile;

public: 

	Shop();

	void IncreaseBetLimit();

	double GetMaxBetUpgradeCost(int element) const;
	double GetMaxBetValue(int element) const;

};