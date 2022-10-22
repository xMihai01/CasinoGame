#include "Doubling.h"

Doubling::Doubling() : SettingDoublingBetDigits()
{
	m_initialValue = 0;
	m_nrDub = 0;
	m_colorWin = -1;
	m_bet = -1;
	m_credit = 0;
	m_keepGoing = true;
}

void Doubling::runGame()
{

	LoadSetting();

	std::cout << "\n\nPlace color to 2 to exit RandomDoubling.\n\n";
	m_keepGoing = true;
	while (m_keepGoing && profile->GetCredit() > 0) {

		m_credit = profile->GetCredit();
		GenerateRandomBet();
	
		std::cout << "\nNEW RANDOM BET: " << m_nrDub << "\n\n";

		StartDoubling(m_nrDub);

		std::cout << "\nCREDIT remaining: " << m_credit << "\n";
		profile->SetCredit(m_credit);
		ResetGame();
	}
}

void Doubling::StartDoubling(double& nrDub)
{
	int culoare;
	int count = 0;
	while (nrDub) {

		if (count == 5) {
			std::cout << "\nYou reached the maximum number of doublings! \nCREDIT won: " << nrDub;
			m_credit += nrDub;
			profile->SetDoublingRounds(profile->GetDoublingRounds() + 1);
			profile->Jackpot(m_initialValue);
			profile->GetLevel()->AddLevel(m_initialValue);
			break;
		}

		if (count == 0)	std::cout << "Color(0 for RED, 1 for BLACK, 2 for EXIT): ";
		else std::cout << "\nColor(0 for RED, 1 for BLACK, 2 for STOP): ";

		std::cin >> culoare;

		if (count == 0 && culoare == 2) {
			m_keepGoing = false;
			break;
		}

		if (count > 0 && culoare == 2) {
			std::cout << "\nSTOPPED! \nCREDIT won: " << nrDub;
			m_credit += nrDub;
			profile->SetDoublingRounds(profile->GetDoublingRounds() + 1);
			profile->Jackpot(m_initialValue);
			profile->GetLevel()->AddLevel(m_initialValue);
			break;
		}

		int colorWin = rand() % 2;
		if (colorWin == culoare) {
			std::cout << "\nWIN!				Color: " << GetColor();
			nrDub *= 2;
			count++;
		}
		else {
			nrDub = 0;
			m_credit -= m_initialValue;
			std::cout << "\nLOST!				Color: " << GetColor();
			m_credit += nrDub;
			profile->SetDoublingRounds(profile->GetDoublingRounds() + 1);
			profile->Jackpot(m_initialValue);
			profile->GetLevel()->AddLevel(m_initialValue);
		}
		if (nrDub != 0)
			std::cout << "\nDoubling remaining: " << nrDub << "\n";
	}
}

void Doubling::ResetGame()
{
	m_initialValue = 0;
	m_nrDub = 0;
	m_colorWin = -1;
}

void Doubling::GenerateRandomBet()
{

	double multiply = 0.1;
	for (int i = 0; i < m_betDigits; i++)
		multiply *= 10;

	for (int i = 0; i < m_betDigits; i++) {
		if (i == 0 && m_betDigits != 1)
			m_nrDub += (rand() % 9 + 1) * multiply;
		else
			m_nrDub += rand() % 10 * multiply;
		multiply /= 10;
	}

	if (m_nrDub == 0) {
		double virgula = (rand() % 10) * 0.1;
		m_nrDub += virgula;
	}
	m_initialValue = m_nrDub;

	if (m_initialValue > m_credit) {
		m_initialValue = m_credit;
		m_nrDub = m_credit;
	}
}

std::string Doubling::GetColor() const
{
	if (m_colorWin == 0) return "RED";
	else return "BLACK";
}
