#include "Level.h"
#include "Profile.h"
#include <iostream>
#include <fstream>

Level::Level()
{
	m_levelNumber = 1;
	m_levelExperience = 0.0;
}
Level::Level(int levelNumber, double levelExperience)
{
	m_levelNumber = levelNumber;
	m_levelExperience = levelExperience;
}

int Level::GetLevelNumber() const
{
	return m_levelNumber;
}

double Level::GetLevelExperience() const
{
	return m_levelExperience;
}

void Level::SetLevelNumber(int levelNumber)
{
    m_levelNumber = levelNumber;
}

void Level::SetLevelExperience(double levelExperience)
{
    m_levelExperience = levelExperience;
}

void Level::AddLevel(double bet)
{

    double addXP;
    Profile* profile = Profile::GetInstance();
    // addXP = bet * 0.006843;

    if (m_levelNumber == INT_MAX) {
        return;
    }

    addXP = bet * 0.01;
    m_levelExperience += addXP;

    int reqXP = GetRequiredEXP(m_levelNumber);

    if (m_levelExperience >= reqXP) {
        m_levelNumber++;
        std::cout << "\nLEVEL UP! You are now at level " << m_levelNumber;
        LevelRewards(m_levelNumber - 1, "single", 0);
        m_levelExperience -= reqXP;
    }

    int a = 0;
    reqXP = GetRequiredEXP(m_levelNumber);
    while (m_levelExperience > reqXP) {
        if (m_levelNumber == INT_MAX)
            break;
        m_levelNumber++;
        a++;
        m_levelExperience -= reqXP;
        if (m_levelNumber > 9999)
            reqXP = 999999;
        else
            reqXP = GetRequiredEXP(m_levelNumber);

    }
    if (a > 0) {
        std::cout << "\nLEVEL UP! You are now at level " << m_levelNumber;
        LevelRewards(m_levelNumber - 1, "double", a);
    }

    std::ofstream setLevel("userdata/" + profile->GetUsername() +"_level.txt");
    setLevel << m_levelNumber << "\n" << m_levelExperience;
}



void Level::LevelRewards(int level, std::string mode, double ups) {

    Profile* profile = Profile::GetInstance();
    double m_credit = profile->GetCredit();
    double rewards = 0;

    do {
        if (mode == "single") {
            rewards = GetRequiredEXP(level) * 5;
            std::cout << "\nReward for leveling up: " << rewards << " CREDIT\n\n";
            
           // profile->SetCredit(profile->GetCredit() + rewards);
        }
        else {
            rewards = 0;
            if (level > 9999) {
                rewards = 999999 * ups * 5;
                std::cout << "\nReward for leveling up " << ups << " times: " << rewards << " CREDIT\n\n";
                
                break;
            }
            for (int i = 0; i < ups; i++) {
                rewards += GetRequiredEXP(level + i) * 5;
            }
            std::cout << "\nReward for leveling up " << ups << " times: " << rewards << " CREDIT\n\n";
       
            break;
        }
    } while (0);
    profile->SetCredit(profile->GetCredit() + rewards);
}

int Level::GetRequiredEXP(int level) {

    if (level == 1)
        return 10;
    if (level == 2)
        return 15;
    if (level == 3)
        return 20;
    if (level == 4)
        return 25;
    if (level == 5)
        return 35;
    if (level == 6)
        return 50;
    if (level == 7)
        return 75;
    if (level == 8)
        return 100;
    if (level == 9)
        return 125;
    if (level == 10)
        return 150;
    if (level == 11)
        return 175;
    if (level == 12)
        return 200;
    if (level == 13)
        return 250;
    if (level == 14)
        return 300;
    if (level == 15)
        return 400;
    if (level == 16)
        return 500;
    if (level == 17)
        return 600;
    if (level == 18)
        return 750;
    if (level == 19)
        return 1000;
    if (level > 19 && level <= 29)
        return 1500;
    if (level > 29 && level <= 39)
        return 2000;
    if (level > 39 && level <= 49)
        return 2500;
    if (level > 49 && level <= 59)
        return 3500;
    if (level > 59 && level <= 69)
        return 4500;
    if (level > 69 && level <= 79)
        return 5500;
    if (level > 79 && level <= 89)
        return 6500;
    if (level > 89 && level <= 99)
        return 7500;
    if (level > 99 && level <= 249)
        return 10000;
    if (level > 249 && level <= 499)
        return 25000;
    if (level > 499 && level <= 749)
        return 50000;
    if (level > 749 && level <= 999)
        return 100000;
    if (level > 999 && level <= 2499)
        return 250000;
    if (level > 2499 && level <= 4999)
        return 500000;
    if (level > 4999 && level <= 9999)
        return 750000;
    if (level > 9999)
        return 999999;

    return 999999;

}
