#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string getUsername();
double getRequiredEXP(int level, double experience);
int highRequiredEXP(int level);
void levelRewards(int level, double& credit, string mode, double ups);

void loadLevel() {

    string username = getUsername();
    int level; double exp;

    ifstream getLevel("userdata/" + username + "_level.txt");
    if (!(getLevel >> level)) {
        ofstream setLevel("userdata/" + username + "_level.txt", ios::app);
        setLevel << 1 << "\n" << 0;
    }
    else {
        ifstream getLevel("userdata/" + username + "_level.txt");
        getLevel >> level >> exp;
    }
}

int getLevel() {

    string username = getUsername();

    ifstream getLevel("userdata/" + username + "_level.txt");
    int level;
    getLevel >> level;
    return level;

}

double getEXP() {

    string username = getUsername();

    ifstream getEXP("userdata/" + username + "_level.txt");
    int level; double exp;
    getEXP >> level >> exp;
    return exp;

}

void addLevel(double bet, double& credit) {

    string username = getUsername();

    int level; double experience;
    double addXP;
    ifstream getLevel("userdata/" + username + "_level.txt");

    getLevel >> level >> experience;
   // addXP = bet * 0.006843;

    if (level == INT_MAX) {
        return;
    }

    addXP = bet * 0.01;
    experience += addXP;

    int reqXP = getRequiredEXP(level, experience);

    if (experience >= reqXP) {
        level++;
        cout << "\nLEVEL UP! You are now at level " << level;
        levelRewards(level-1, credit, "single", 0);
        experience -= reqXP;
    }

    int a = 0;
    reqXP = getRequiredEXP(level, experience);
    while (experience > reqXP) {
        if (level == INT_MAX)
            break;
        level++;
        a++;
        experience -= reqXP;
        if (level > 9999)
            reqXP = 999999;
        else
        reqXP = getRequiredEXP(level, experience);

    } 
    if (a > 0) {
        cout << "\nLEVEL UP! You are now at level " << level;
        levelRewards(level - 1, credit, "double", a);
    }

    ofstream setLevel("userdata/" + username + "_level.txt");
    setLevel << level << "\n" << experience;

}

void levelRewards(int level, double& credit, string mode, double ups) {

    if (mode == "single") {
        double rewards = highRequiredEXP(level) * 5;
        cout << "\nReward for leveling up: " << rewards << " CREDIT\n\n";
        credit += rewards;
    }
    else {
        double rewards = 0;
        if (level > 9999) {
            rewards = 999999 * ups * 5;
            cout << "\nReward for leveling up " << ups << " times: " << rewards << " CREDIT\n\n";
            credit += rewards;
            return;
        }
        for (int i = 0; i < ups; i++) {
            rewards += highRequiredEXP(level + i) * 5;
        }
        cout << "\nReward for leveling up " << ups << " times: " << rewards << " CREDIT\n\n";
        credit += rewards;
        return;
    }

}

double getRequiredEXP(int level, double experience) {

   // double requiredXP = 100, beforeXP = 0;
  //  double coeff = 0.25, coeff2 = 0.25;

   // for (int i = 1; i <= level; i++) {
     //   if (level >= 10)
            return highRequiredEXP(level);
       // requiredXP = requiredXP * level*0.15 + beforeXP;
        //beforeXP = requiredXP*0.15;
    //}

    //return requiredXP;
}

int highRequiredEXP(int level) {

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