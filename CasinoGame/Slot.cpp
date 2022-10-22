#include "Slot.h"
#include "Utils.h"

Slot::Slot() : SettingEnableDoubling()
{
	m_slotMachineScreen = { {0,0,0},{0,0,0},{0,0,0} };

	m_winnings = 0;
	m_criteria = 0;
	m_bet = -1;
	m_credit = -1;
	m_isBot = false;
}

void Slot::runGame()
{

	LoadSetting();

	std::cout << "\nSet BET to 0 to exit slots.\nWARNING! Placing the bet will automatically start the spin.\n";

	m_credit = profile->GetCredit();

	while (m_credit) {

		m_bet = SetBet(m_credit);
		m_credit -= m_bet;
		if (m_bet == 0)
			break;


		GenerateSlotResult();
		ReviewSlotResult();
		CheckSlotResult();


		profile->GetLevel()->AddLevel(m_bet);
		profile->Jackpot(m_bet);
		profile->SetSlotRounds(profile->GetSlotRounds() + 1);
		profile->SetCredit(m_credit);
		ResetGame();
	
	}
}


void Slot::GenerateSlotResult()
{

	for (int i = 0; i < 3; i++) 
		for (int j = 0; j< 3; j++) 
			m_slotMachineScreen[i][j] = rand() % 101;
		
	
}

void Slot::ReviewSlotResult()
{
	// 1 = x2, 2 = x2, 3 = x4, 4 = x8, 0 = x20
	// 1,2 = x2, 3 = x4, 4 = x8, 5 = x20, 0 = x50 [NEW]

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {

			if (m_slotMachineScreen[i][j] >= 2 && m_slotMachineScreen[i][j] <= 30) {
				m_slotMachineScreen[i][j] = 1;
			}
			else if (m_slotMachineScreen[i][j] >= 32 && m_slotMachineScreen[i][j] <= 60) {
				m_slotMachineScreen[i][j] = 2;
			}
			else if (m_slotMachineScreen[i][j] >= 61 && m_slotMachineScreen[i][j] <= 80) {
				m_slotMachineScreen[i][j] = 3;
			}
			else if (m_slotMachineScreen[i][j] >= 81 && m_slotMachineScreen[i][j] <= 95) {
				m_slotMachineScreen[i][j] = 4;
			}
			else if (m_slotMachineScreen[i][j] >= 96 && m_slotMachineScreen[i][j] <= 100) {
				m_slotMachineScreen[i][j] = 5;
			}
			else if (m_slotMachineScreen[i][j] == 1 || m_slotMachineScreen[i][j] == 31) {
				m_slotMachineScreen[i][j] = 0;
			}
		}
	}
	if (!m_isBot) {
		std::cout << "\n\n\n";
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				std::cout << m_slotMachineScreen[i][j] << " ";
			}
			std::cout << "\n";
		}
	}
}

void Slot::CheckSlotResult()
{

	if ((m_slotMachineScreen[0][0] == m_slotMachineScreen[0][1]) && (m_slotMachineScreen[0][0] == m_slotMachineScreen[0][2])) 
		checkSlotWin(m_slotMachineScreen[0][0]);
	
	if ((m_slotMachineScreen[1][0] == m_slotMachineScreen[1][1]) && (m_slotMachineScreen[1][0] == m_slotMachineScreen[1][2])) 
		checkSlotWin(m_slotMachineScreen[1][0]);

	if ((m_slotMachineScreen[2][0] == m_slotMachineScreen[2][1]) && (m_slotMachineScreen[2][0] == m_slotMachineScreen[2][2])) 
		checkSlotWin(m_slotMachineScreen[2][0]);

	if ((m_slotMachineScreen[0][0] == m_slotMachineScreen[1][1]) && (m_slotMachineScreen[0][0] == m_slotMachineScreen[2][2])) 
		checkSlotWin(m_slotMachineScreen[0][0]);

	if ((m_slotMachineScreen[2][0] == m_slotMachineScreen[1][1]) && (m_slotMachineScreen[2][0] == m_slotMachineScreen[0][2])) 
		checkSlotWin(m_slotMachineScreen[2][0]);

	

	if ((m_winnings > 0 && !m_isBot) && m_enableDoubling) {

		std::cout << "\nYou won " << m_winnings << " CREDITS!\n";
		std::cout << "Do you want to double the winnings? (0 for NO, 1 for YES): ";
		int choice, numarDublaje = 0;
		std::cin >> choice;
		while (choice && m_winnings) {
			if (choice == 1) {
				int doubleResult = rand() % 2;
				if (doubleResult == 1) {
					m_winnings = m_winnings * 2;
					std::cout << "\nDOUBLED!\n";
					numarDublaje++;
				}
				else {
					m_winnings = 0;
					choice = 0;
					std::cout << "\nLOST!\n";
					break;
				}
			}
			if (numarDublaje == 5) {
				std::cout << "\nCongratulations, you reached the maximum number of doubling!\n";
				break;
			}
			std::cout << "\nYou won " << m_winnings << " CREDITS!\n";
			std::cout << "Do you want to continue doubling? (0 for NO, 1 for YES): ";
			std::cin >> choice;
		}

	}

	m_credit += m_winnings;
	if (m_winnings > 0 && !m_isBot) {
		std::cout << "\nYou won " << m_winnings << " CREDITS!\n";
		std::cout << "You have " << m_credit << " remaining CREDITS\n";
	}
	else {
		std::cout << "\nYou lost " << m_bet << " CREDITS!\n";
		std::cout << "You have " << m_credit << " remaining CREDITS\n";
	}
	//winnings = 0;
}

void Slot::checkSlotWin(int value)
{
	if (m_criteria <= 3)
		m_criteria++;
	if (value == 1 || value == 2)
		m_winnings = m_winnings + m_bet * 2.5 * m_criteria;
	if (value == 3)
		m_winnings = m_winnings + m_bet * 5 * m_criteria;
	if (value == 4)
		m_winnings = m_winnings + m_bet * 10 * m_criteria;
	if (value == 5)
		m_winnings = m_winnings + m_bet * 25 * m_criteria;
	if (value == 0)
		m_winnings = m_winnings + m_bet * 100 * m_criteria;


}

void Slot::ResetGame() {

	m_winnings = 0;
	m_criteria = 0;
	m_credit = profile->GetCredit();
}
