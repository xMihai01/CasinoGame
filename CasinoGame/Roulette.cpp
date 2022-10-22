#include "Roulette.h"
#include "Utils.h"

Roulette::Roulette()
{
    m_bet = 0;
    m_colorPicked = -1;
    m_colorName = "none";
    m_numberPicked = -1;
}

void Roulette::runGame()
{

    std::cout << "\n\nSet bet to 0 to exit Roulette.\n\n";
    double credit = profile->GetCredit();

    while (profile->GetCredit()) {

        m_bet = SetBet(profile->GetCredit());
        if (m_bet == 0)
            break;
        std::cout << "\nColor(0 RED, 1 BLACK, 2 GREEN): ";
        std::cin >> m_colorPicked;
        m_numberPicked = rand() % 37;
        SetColorName();

        profile->GetLevel()->AddLevel(m_bet);
        profile->Jackpot(m_bet);

        if (CheckIfWinner()) {
            std::cout << "\nWIN!\n"; 
            //m_bet += m_bet;
            if (m_colorPicked == 2 && m_colorName == "GREEN")
                m_bet = m_bet * 35;

        }
        else {
            std::cout << "\nLOSE!\n"; 
            m_bet -= m_bet*2;

        }
        std::cout << "Color: " << m_colorName << "        Number: " << m_numberPicked;
    
        profile->SetCredit(profile->GetCredit() + m_bet);
        profile->SetRouletteRounds(profile->GetRouletteRounds() + 1);

        std::cout << "\n\nCREDIT remaining: " << profile->GetCredit() << "\n";

    }

}

void Roulette::SetColorName() {

    if (m_numberPicked == 0)
        m_colorName = "GREEN";
    else if (m_numberPicked % 2 == 0 && m_numberPicked != 0)
        m_colorName = "RED";
    else
        m_colorName = "BLACK";

}

bool Roulette::CheckIfWinner() {

    if (m_colorPicked == 0 && m_colorName == "RED")
        return true;
    else if (m_colorPicked == 1 && m_colorName == "BLACK")
        return true;
    else if (m_colorPicked == 2 && m_colorName == "GREEN")
        return true;
    else
        return false;

    return false;
}


