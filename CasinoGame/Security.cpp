#include "Security.h"

Security::Security()
{
	_mkdir("accounts");
	_mkdir("userdata");
	m_username = "";
	m_loggedIn = false;
}

bool Security::GetLogInStatus() const
{
    return m_loggedIn;
}


void Security::LogIn()
{

    std::string password = "";
    std::string username = "";
    std::cout << "Username: ";
    std::cin >> username;
    m_username = username;

    while (!m_loggedIn) {
        std::ifstream getPassword("accounts/" + m_username + ".txt");
        if (!(getPassword >> password)) {
            std::cout << "There is no account matching this username.\nCreating one...\nSet your password: ";
            std::cin >> password;
            std::ofstream setPassword("accounts/" + m_username + ".txt", std::ios::app);
            setPassword << password;

            std::ofstream setRfn("accounts/" + m_username + "_rfn.txt"); //random found numbers
            setRfn << 3;
            std::ofstream setDss("accounts/" + m_username + "_dss.txt"); //doubling status
            setDss << 1 << "\n";
            std::ofstream setDrb("accounts/" + m_username + "_drb.txt"); // random doubling digits for bet
            setDrb << 1 << "\n";
        }
        else {
            std::ifstream getPassword("accounts/" + m_username + ".txt");
            std::string temp = "unknown";
            getline(getPassword, temp);
            std::cout << "Password: ";
            std::cin >> password;

            if (temp == password) {
                m_loggedIn = true;
            }
            else {
                std::cout << "Incorrect password!\n";
            }
        }
    }

    std::cout << "Successfully logged in!\n\n";

}

void Security::LogOut()
{
    std::cout << "\n\nYou ahve been logged out!.\n\n";
    m_loggedIn = false;
}

void Security::ChangePassword()
{
    std::ifstream getPassword("accounts/" + m_username + ".txt");

    std::string password = "";
    std::string inputPassword = "";
    bool keepGoing = true;

    while (keepGoing) {
        std::cout << "Old Password: ";
        std::cin >> inputPassword;
        getPassword >> password;

        if (inputPassword == password) {

            std::ofstream setPassword("accounts/" + m_username + ".txt");
            std::cout << "New password: ";
            std::cin >> inputPassword;
            setPassword << inputPassword;
            std::cout << "Your password has been successfully changed!\n";
            keepGoing = false;
        }
        else {
            std::cout << "Incorrect password! \n";

            std::cout << "Do you want to continue?(yes/no): ";
            std::string retry;
            std::cin >> retry;
            if (retry != "yes") {
                std::cout << "Returning...\n";
                keepGoing = false;
            }
        }
    }

}

void Security::ResetAccount()
{
    std::string choice;
    std::cout << "\n\n\n\n\n\n\n\n##################### WARNING #####################\n\nYou are about to RESET your account!\nAre you sure you want to continue? This cannot be undone!\n\n##################### WARNING#####################\n\n";
    std::cout << "\nContinue?(YES or NO): "; std::cin >> choice;

    if (choice != "YES") {
        std::cout << "Returning...\n";
        return;
    }

    std::fstream getPassword("accounts/" + m_username + ".txt");
    bool confirmed = false;

    std::string password = "";
    std::string inputPassword = "";
    bool keepGoing = true;

    std::cout << "\n\nPlease enter your password in order to reset your account!\n";

    while (keepGoing) {
        std::cout << "Password: ";
        std::cin >> inputPassword;
        getPassword >> password;

        if (inputPassword == password) {
            keepGoing = false;
            confirmed = true;
        }
        else {
            std::cout << "Incorrect password! \n";
            std::cout << "Do you want to continue?(yes/no): ";
            std::string retry;
            std::cin >> retry;
            if (retry != "yes") {
                std::cout << "Returning...\n";
                keepGoing = false;
                return;
            }

        }
    }

    if (confirmed) {

        std::string c;
        std::cout << "\n\n\n\n\nYOU ARE ABOUT TO RESET THIS ACCOUNT\nTHIS ACTION CANNOT BE UNDONE\n";
        std::cout << "Reset(YES or NO): "; std::cin >> c;

        if (c == "YES") {
            std::ofstream getGames("userdata/" + m_username + "_games.txt");
            std::ofstream getCredit("userdata/" + m_username + "_credit.txt");
            std::ofstream getCredit1("userdata/" + m_username + "_jackpot.txt");
            std::ofstream getCredit2("userdata/" + m_username + "_tournamentgames.txt");
            std::ofstream getCredit3("userdata/" + m_username + "_pass.txt");
            std::ofstream getCredit4("userdata/" + m_username + "_level.txt");
            std::ofstream getCredit5("accounts/" + m_username + ".txt");
            std::ofstream getCredit6("accounts/" + m_username + "_drb.txt");
            std::ofstream getCredit7("accounts/" + m_username + "_dss.txt");
            std::ofstream getCredit8("accounts/" + m_username + "_rfn.txt");
            std::ofstream getCredit9("userdata/" + m_username + "_maxbet.txt");
            std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            std::cout << "Your account has been successfully reset!\nYou have been logged out!\n";
            m_loggedIn = false;
        }
        else 
            std::cout << "\nReturning...\n";
        



    }
}
