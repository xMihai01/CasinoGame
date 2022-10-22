#include "Blackjack.h"
#include "Utils.h"

Blackjack::Blackjack()
{
	for (int i = 0; i < 5; i++) {
		m_playerCards.push_back(0);
		m_dealerCards.push_back(0);
	}

	m_playerPoints = 0;
	m_playerCardsNumber = 0;
	m_playerAce = 0;
	m_dealerPoints = 0;
	m_dealerCardsNumber = 0;
	m_dealerAce = 0;
	m_status = "none";
	m_isTournament = false;

	m_bet = 0;
	m_credit = -1;
}

Blackjack::Blackjack(bool isTournament)
{
	for (int i = 0; i < 5; i++) {
		m_playerCards.push_back(0);
		m_dealerCards.push_back(0);
	}

	m_playerPoints = 0;
	m_playerCardsNumber = 0;
	m_playerAce = 0;
	m_dealerPoints = 0;
	m_dealerCardsNumber = 0;
	m_dealerAce = 0;
	m_status = "none";
	m_isTournament = isTournament;

	m_bet = 0;
	m_credit = -1;
}

void Blackjack::runGame()
{
	std::cout << "\nSet BET to 0 to exit Blackjack\n\n";
	m_credit = profile->GetCredit();
	// 0,A,2,3,4,5,6,7,8,9,10,A,J,Q,K

	while (m_credit) {

		if (!m_isTournament) {
			m_bet = SetBet(m_credit); std::cout << "\n";
			if (m_bet == 0)
				break;
		}

		profile->GetLevel()->AddLevel(m_bet);
		profile->Jackpot(m_bet);

		GenerateDealerCards();
		GeneratePlayerCards();

		if ((m_playerPoints == m_dealerPoints) || (m_playerPoints > 21 && m_dealerPoints > 21)) 
			RoundSummary("TIED");
		else if (((m_playerPoints > m_dealerPoints) || m_dealerPoints > 21) && (m_playerPoints <= 21)) 
			RoundSummary("WIN");
		else if (((m_playerPoints < m_dealerPoints) || m_playerPoints > 21) && (m_dealerPoints <= 21)) {
			m_bet -= m_bet * 2;
			RoundSummary("LOSE");
		}
		else {
			std::cout << "\nError occurred.\n";
		}
		
		profile->SetCredit(m_credit + m_bet);
		profile->SetBlackjackRounds(profile->GetBlackjackRounds() + 1);
		if (m_isTournament)
			break;
		ResetGame();
	}

}

void Blackjack::GeneratePlayerCards()
{
	int action;
	for (int i = 0; i < 2; i++) {
		m_playerCards[i] = rand() % 13 + 1;
		m_playerPoints += CheckCardPoints(m_playerCards[i], m_playerPoints, m_playerAce);
		m_playerCardsNumber++;
	}
	ShowCards();
	if (m_playerPoints == 21)
		return;
	std::cin >> action; std::cout << "\n";

	while (action && m_playerCardsNumber < 5) {

		if (m_playerPoints <= 20 && m_playerAce >= 1) {
			m_playerPoints -= 10;
			m_playerAce--;
		}

		m_playerCards[m_playerCardsNumber] = rand() % 13 + 1;
		m_playerPoints += CheckCardPoints(m_playerCards[m_playerCardsNumber], m_playerPoints, m_playerAce);
		m_playerCardsNumber++;

		if (m_playerCardsNumber < 5 && m_playerPoints < 21) {
			ShowCards();
			std::cin >> action; std::cout << "\n";
		}
		else {
			ShowCards();
			break;
		}
	}
}

void Blackjack::GenerateDealerCards()
{
	for (int i = 0; i < 2; i++) {
		m_dealerCards[i] = rand() % 13 + 1;
		m_dealerPoints += CheckCardPoints(m_dealerCards[i], m_dealerPoints, m_dealerAce);
		m_dealerCardsNumber++;
	}

	while (m_dealerPoints <= 11 && m_dealerCardsNumber < 5) {

		if (m_dealerPoints <= 20 && m_dealerAce >= 1) {
			m_dealerPoints -= 10;
			m_dealerAce--;
		}

		m_dealerCards[m_dealerCardsNumber] = rand() % 13 + 1;
		m_dealerPoints += CheckCardPoints(m_dealerCards[m_dealerCardsNumber], m_dealerPoints, m_dealerAce);
		m_dealerCardsNumber++;
	}

	int randomAction = rand() % 6 + 11;
	if (m_dealerCardsNumber < 5 && m_dealerPoints < randomAction) {
		m_dealerCards[m_dealerCardsNumber] = rand() % 13 + 1;
		m_dealerPoints += CheckCardPoints(m_dealerCards[m_dealerCardsNumber], m_dealerPoints, m_dealerAce);
		m_dealerCardsNumber++;

	}
}

void Blackjack::ShowCards()
{
	std::cout << "CARDS: | ";
	for (int i = 0; i < m_playerCardsNumber; i++) {
		std::cout << VerifyCard(m_playerCards[i]) << " | ";
	}
	std::cout << "\nPoints: " << m_playerPoints << "\n";
	if (m_playerCardsNumber < 5 && m_playerPoints < 21)
		std::cout << "\n\n0 for STOP, 1 for ANOTHER CARD: ";
}

std::string Blackjack::VerifyCard(int card)
{
	if (card >= 2 && card <= 10) return std::to_string(card);
	if (card == 11) return "J";
	if (card == 12)	return "Q";
	if (card == 13)	return "K";
	if (card == 1) 	return "A";
	else return "ERROR";
}

int Blackjack::CheckCardPoints(int card, int points, int& ace)
{
	if (card >= 2 && card <= 10) return card;
	if (card > 10) return 10;
	if (card == 1) {

		if (points < 11) {
			ace++;
			return 11;
		}
		else return 1;
	}
	return -1000;
}

void Blackjack::RoundSummary(std::string status)
{
	m_status = status;
	if (m_isTournament)
		return;
	int zece = 0;
	int spatiu = 0;

	std::cout << "\n\n################################# RoundSummary #################################\n\n";

	std::cout << "Status: " << status;

	std::cout << "\n\nDealer Cards: | ";
	for (int i = 0; i < m_dealerCardsNumber; i++) {
		std::cout << VerifyCard(m_dealerCards[i]) << " | ";
		if (m_dealerCards[i] == 10)
			zece++;
	}

	for (int i = 0; i < m_dealerCardsNumber; i++) {
		std::cout << "    ";
	}

	std::cout << "Your cards: | ";
	for (int i = 0; i < m_playerCardsNumber; i++) {
		std::cout << VerifyCard(m_playerCards[i]) << " | ";
	}
	std::cout << "\nDealer Points: " << m_dealerPoints;
	std::cout << "       ";
	for (int i = 0; i < m_dealerCardsNumber; i++) {
		std::cout << "    ";
		if (i > 1)
			std::cout << "    ";
		if (zece > 0) {
			std::cout << " ";
			zece--;
		}
	}
	std::cout << "Your Points: " << m_playerPoints << "\n\n";

	if (status == "LOSE") 
		std::cout << "CREDIT lost: " << -m_bet << "\n";
	else if (status == "WIN") 
		std::cout << "CREDIT won: " << m_bet << "\n";
	else {
		m_bet = 0;
		std::cout << "You didn't lose/win any credits!\n";
	}
	std::cout << "CREDIT remaining " << m_credit + m_bet;

	std::cout << "\n\n################################# RoundSummary #################################\n\n";
}

void Blackjack::ResetGame()
{
	m_playerPoints = 0;
	m_playerCardsNumber = 0;
	m_playerAce = 0;
	m_dealerPoints = 0;
	m_dealerCardsNumber = 0;
	m_dealerAce = 0;

	m_credit = profile->GetCredit();
}
