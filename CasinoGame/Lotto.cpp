#pragma once
#include "Lotto.h"
#include "Utils.h"

Lotto::Lotto() : SettingLottoFoundNumbers()
{

	for (int i = 0; i < 6; i++) {
		m_winningNumbers.push_back(0);
		m_choices.push_back(0);
		m_foundNumbers.push_back(0);
	}
	m_bet = -1;
	m_foundNumbersInteger = 0;

}

void Lotto::runGame() {

	LoadSetting();

	std::cout << "\n\nPlace bet to 0 to exit Lotto.\n\n";
	while (profile->GetCredit()) {

		m_bet = SetBet(profile->GetCredit());
		if (m_bet == 0)
			break;

		m_foundNumbersInteger = 0;
		profile->GetLevel()->AddLevel(m_bet);
		profile->Jackpot(m_bet);
		SetChoices();
		SetWinningNumbers();
		SetFoundNumbers();

		if (m_foundNumbersInteger >= m_requiredFoundNumbers)  
			m_bet = m_bet * pow(4, m_foundNumbersInteger);
		else 
			m_bet -= m_bet * 2;
		RoundSummary();


		profile->SetCredit(profile->GetCredit() + m_bet);
		profile->SetLottoRounds(profile->GetLottoRounds() + 1);
		ResetGame();
	}

}

void Lotto::SetChoices()
{
	int number;
	for (int i = 0; i < 6; i++) {
		std::cout << "Number " << i + 1 << ": ";
		std::cin >> number;
		if (ValidateChoices(m_choices, number, i)) {
			m_choices[i] = number;
		}
		else {
			std::cout << "\n\n" << m_choices[i] << " + " << number << "\n\n";
			std::cout << "\nERROR: The number is already a choice, negative or higher than 49.\nRetrying...\n\n";
			i--;
		}
	}
}

void Lotto::SetWinningNumbers()
{
	int generatedNumber;

	for (int i = 0; i < 6; i++) {
		generatedNumber = (rand() % 49) + 1;

		if (ValidateChoices(m_winningNumbers, generatedNumber, i)) 
			m_winningNumbers[i] = generatedNumber;
		else 
			i--;
	}
	std::cout << "Winning numbers are: ";
	for (int i = 0; i < 6; i++) {
		std::cout << m_winningNumbers[i] << " ";
	}

}

void Lotto::SetFoundNumbers()
{
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (m_choices[i] == m_winningNumbers[j]) {
				m_foundNumbers[m_foundNumbersInteger] = m_winningNumbers[j];
				m_foundNumbersInteger++;
			}
		}
	}
}

bool Lotto::ValidateChoices(std::vector<int> vector, int number, int position)
{
	for (int i = 0; i <= position; i++) 
		if (vector[i] == number || number <= 0 || number > 49) 
			return false;
		
	return true;
}


void Lotto::RoundSummary() {

	std::cout << "\n\n################################# RoundSummary #################################\n\n";

	std::cout << "\nWinning numbers: | ";
	for (int i = 0; i < 6; i++) {
		std::cout << m_winningNumbers[i] << " | ";
	} std::cout << "      ";

	std::cout << "Your choices: | ";
	for (int i = 0; i < 6; i++) {
		std::cout << m_choices[i] << " | ";
	}

	if (m_foundNumbersInteger != 0) {

		std::cout << "\nFound numbers: | ";
		for (int i = 0; i < m_foundNumbersInteger; i++) {
			std::cout << m_foundNumbers[i] << " | ";
		}std::cout << "\n";

	}
	else if (m_foundNumbersInteger == 0) {
		std::cout << "\nYou didn't find any numbers!\n";
	}

	if (m_foundNumbersInteger < m_requiredFoundNumbers) {
		std::cout << "\nYou must find " << m_requiredFoundNumbers << " numbers in order to win " << "\n\nYou lost " << -m_bet << " credits.";

	}
	else {
		std::cout << "\nYou found " << m_foundNumbersInteger << " numbers!\n\nYou won " << m_bet << " credits!";
	}
	std::cout << "\nRemaining CREDIT: " << profile->GetCredit() + m_bet;

	std::cout << "\n\n################################# RoundSummary #################################\n\n";

}

void Lotto::ResetGame() {
	for (int i = 0; i < 6; i++) {
		m_choices[i] = 0;
	}
	m_foundNumbersInteger = 0;
}