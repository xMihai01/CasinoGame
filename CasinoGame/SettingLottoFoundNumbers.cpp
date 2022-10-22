#include "SettingLottoFoundNumbers.h"

SettingLottoFoundNumbers::SettingLottoFoundNumbers()
{
	profile = profile->GetInstance();
	m_requiredFoundNumbers = 3;
}

int SettingLottoFoundNumbers::GetRequiredFoundNumbers() const
{
	return m_requiredFoundNumbers;
}

void SettingLottoFoundNumbers::ChangeSetting()
{
	int aux;
	bool success = false;
	std::cout << "\nWARNING! The default value for this setting is 3\n";

	while (!success) {

		std::cout << "\nRequired found numbers in order to win loto: ";
		std::cin >> aux;
		if (aux >= 1 && aux <= 6) {
			std::cout << "\nThis setting has been successfully changed!\n";
			m_requiredFoundNumbers = aux;
			break;
		}
		else {
			std::cout << "\nAn error occurred while changing this setting\n";
			std::cout << "This setting only accepts values between 1 and 6\n\n";
		}
	}
	
}

void SettingLottoFoundNumbers::LoadSetting()
{
	std::ifstream getSetting("accounts/" + profile->GetUsername() + "_rfn.txt");
	getSetting >> m_requiredFoundNumbers;
}
