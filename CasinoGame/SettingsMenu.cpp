#include "SettingsMenu.h"

SettingsMenu::SettingsMenu()
{
	profile = profile->GetInstance();
}

void SettingsMenu::ShowMenu()
{
	gamePlay = true;

	while (gamePlay) {

		Info();
		int choice;
		std::cout << "\nSetting(-1 for info): ";
		std::cin >> choice;

		switch (choice) {
		case 1:
			sLottoFoundNumber.ChangeSetting();
			gamePlay = false;
			break;
		case 2:
			sEnableDoubling.ChangeSetting();
			gamePlay = false;
			break;
		case 3:
			//changeDoublingRandomBet(username);
			gamePlay = false;
			break;
		case 10:
			profile->ChangePassword();
			gamePlay = false;
			break;
		case 19:
			profile->ResetAccount();
			gamePlay = false;
			return;
			break;
		case 20:
			profile->LogOut();
			gamePlay = false;
			return;
			break;
		case 0:
			gamePlay = false;
			break;
		default:
			std::cout << "\nInvalid setting!\n";
			break;
		}
		SaveSettings();

	}
}

void SettingsMenu::Info()
{
	std::cout << "\n#################### CasinoSettings ####################\n\n";

	std::cout << "Username: " << profile->GetUsername() << "\n\n";

	std::cout << "Press 0 to exit Settings Menu\n";
	std::cout << "Press 1 to change Required Found Numbers to win at LOTO\n";
	std::cout << "Press 2 to turn on/off doubling wins at SLOTS\n";
	std::cout << "Press 3 to change number of digits for a RandomDoubling bet\n";
	std::cout << "Press 10 to change your password\n";
	std::cout << "Press 19 to RESET your account\n\n";

	std::cout << "#################### CasinoSettings ####################\n\n";
}

void SettingsMenu::SaveSettings()
{
	std::ofstream setEnableDoubling("accounts/" + profile->GetUsername() + "_dss.txt");
	setEnableDoubling << sEnableDoubling.GetDoublingSettingValue();
	std::ofstream setRandomFoundNumbers("accounts/" + profile->GetUsername() + "_rfn.txt");
	setRandomFoundNumbers << sLottoFoundNumber.GetRequiredFoundNumbers();
}

void SettingsMenu::LoadSettings()
{

}
