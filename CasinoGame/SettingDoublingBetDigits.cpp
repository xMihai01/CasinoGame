#include "SettingDoublingBetDigits.h"
SettingDoublingBetDigits::SettingDoublingBetDigits()
{
	profile = profile->GetInstance();
	m_betDigits = 1;
}

void SettingDoublingBetDigits::ChangeSetting()
{
	int aux;
	std::cout << "\nWARNING! The default value for this setting is 1\n";

	while (true) {

		std::cout << "\nNumber of digits for a RandomDoubling bet: ";
		std::cin >> aux;
		if (aux >= 1 && aux <= 350) {
			m_betDigits = aux;
			std::cout << "\nThis setting has been successfully changed!\n";
			return;
		}
		else {
			std::cout << "\nAn error occurred while changing this setting\n";
			std::cout << "This setting only accepts values between 1 and 350\n\n";
		}
	}
}

void SettingDoublingBetDigits::LoadSetting()
{
	std::ifstream getSetting("accounts/" + profile->GetUsername() + "_drb.txt");
	getSetting >> m_betDigits;
}
