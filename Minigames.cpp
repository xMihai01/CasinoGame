#include <iostream>
#include <fstream>

void showMinigamesMenu(double credit);
std::string getUsername();
void guessTheNumber(double& credit);

void minigamesMenu(double& credit) {

	int action;
	bool keepGoing = true;

	while (keepGoing) {

		showMinigamesMenu(credit);
		std::cin >> action;

		switch (action) {

		case 0:
			keepGoing = false;
			break;
		case 1:
			guessTheNumber(credit);
			break;

		default:
			break;
		}
	}


}

void guessTheNumber(double& credit) {

	std::cout << "\n\nWelcome to Guess The Number.\n\nHere you can earn CREDIT just by playing! Press 1 to start and 0 to cancel: ";
	int action;
	std::cin >> action;
	
	int generatedNumber, number, guesses = 0;
	bool found = false;

	while (action) {

		generatedNumber = rand();
		std::cout << "\nA number has been generated. Try to guess it in less than 25 tries to earn a reward!\nYou can cancel at any time by pressing 0\n\n";
		guesses = 0;
		while (!found) {


			std::cout << "You have " << 25-guesses << " guesses left!\nGuess: ";
			std::cin >> number;

			if (number == 0) {
				action = 0;
				break;
			}
				

			if (number > generatedNumber) {
				std::cout << "\nLOWER!\n";
				guesses++;
			}
			else if (number < generatedNumber) {
				std::cout << "\nHIGHER\n";
				guesses++;
			}
			else {
				std::cout << "\nYou guessed the number (" << generatedNumber << ") and won " << 10 * (25 - guesses) << " CREDIT\n";
				credit += 10 * (25 - guesses);
				system("PAUSE");
				break;
			}
			
			if (guesses >= 25) {
				std::cout << "You reached the maximum number of guesses! \nYou didn't win anything.\n\n";
				system("PASUE");
				break;
			}

		}
		

	}

}

void showMinigamesMenu(double credit) {

	std::cout << "\n\n#################### Minigames ####################\n\n";

	std::cout << "Username: " << getUsername() << "\n";
	std::cout << "CREDIT: " << credit << "\n\n";

	std::cout << "Press 0 to EXIT.\n";
	std::cout << "Press 1 to play GuessTheNumber\n\n";

	std::cout << "#################### Minigames ####################\n\nMinigame(-1 for info): ";

}
