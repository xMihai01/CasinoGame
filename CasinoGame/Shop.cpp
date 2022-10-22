#include "Shop.h"

Shop::Shop()
{
	profile = profile->GetInstance();
}

void Shop::IncreaseBetLimit()
{
	int itemlevel = profile->GetMaxBetLevel();
	double upgradeCost = GetMaxBetUpgradeCost(itemlevel);

	if (upgradeCost == -1) {
		std::cout << "\nMaxBET is at MAX level!\n";
		return;
	}


	std::cout << "\nItem: BET limit (MAX BET)\n";
	std::cout << "Item level: " << itemlevel << " --> " << itemlevel + 1 << "\n";
	std::cout << "Current Max BET: " << GetMaxBetValue(itemlevel) << " --> " << GetMaxBetValue(itemlevel + 1) << "\n\n";
	std::cout << "Upgrade cost: " << upgradeCost << "\n\n";
	std::cout << "To upgrade, press 1. To cancel, press 0: ";

	int action;
	std::cin >> action;

	if (action == 1 && profile->GetCredit() > upgradeCost) {
		std::ofstream setLevel("userdata/" + profile->GetUsername() + "_shop.txt");
		setLevel << itemlevel + 1;
		profile->SetMaxBetLevel(profile->GetMaxBetLevel() + 1);
		std::cout << "\nYour MaxBET level has been upgraded to " << itemlevel + 1 << "\n\n";
		profile->SetCredit(profile->GetCredit() + 5000 - upgradeCost);
	}
	else if (action == 1 && profile->GetCredit() < upgradeCost) {
		std::cout << "Not enough credit! You need " << upgradeCost - profile->GetCredit() << " more CREDIT\n";
	}
}


double Shop::GetMaxBetUpgradeCost(int element) const
{
	return m_maxBetUpgradeCost[element-1];
}

double Shop::GetMaxBetValue(int element) const
{
	return m_getMaxBetValue[element-1];
}
