#include "SettingEnableDoubling.h"

SettingEnableDoubling::SettingEnableDoubling()
{
	profile = profile->GetInstance();
	m_enableDoubling = true;
}

bool SettingEnableDoubling::GetDoublingSettingValue() const
{
	return m_enableDoubling;
}

void SettingEnableDoubling::SetDoublingSettingValue(bool enableDoubling)
{
	m_enableDoubling = enableDoubling;
}

void SettingEnableDoubling::ChangeSetting()
{
	int aux;
	std::cout << "\nWARNING! The default value for this setting is 1 (enabled)\n";

		while (true) {

			std::cout << "\nEnable doubling at SLOTS(0 for NO, 1 for YES): ";
			std::cin >> aux;
			if (aux == 1 || aux == 0) {
				std::cout << "\nThis setting has been successfully changed!\n";
				m_enableDoubling = aux;
				break;
			}
			else {
				std::cout << "\nAn error occurred while changing this setting\n";
				std::cout << "This setting only accepts value 0 or 1\n\n";
			}
		}
}

void SettingEnableDoubling::LoadSetting()
{
	std::ifstream getSetting("accounts/" + profile->GetUsername() + "_dss.txt");
	getSetting >> m_enableDoubling;
}
