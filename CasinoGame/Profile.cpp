#include "Profile.h"

Profile::Profile()
{

	m_credit = 1000;
	m_rouletteRounds = 0;
	m_blackjackRounds = 0;
	m_crapsRounds = 0;
	m_lottoRounds = 0;
	m_slotRounds = 0;
	m_doublingRounds = 0;
	m_tournamentRounds = 0;
	m_tournamentWins = 0;
	m_maxBetLevel = 1;
	LogIn();
	LoadProfile();
	
}

void Profile::LoadProfile()
{
	std::ifstream getCredit("userdata/" + m_username + "_credit.txt");
	if (!(getCredit >> m_credit)) {
		std::cout << "Welcome to CasinoGame, " + m_username + ", you received 1000 CREDITS, enjoy!\n\n";
	}
	else {
		std::ifstream getCredit("userdata/" + m_username + "_credit.txt");
		getCredit >> m_credit;
	}

	std::ifstream getGames("userdata/" + m_username + "_games.txt");
	if (!(getGames >> m_lottoRounds)) {
		std::ofstream setGames("userdata/" + m_username + "_games.txt", std::ios::app);
		setGames << m_lottoRounds << "\n";
		setGames << m_doublingRounds << "\n";
		setGames << m_rouletteRounds << "\n";
		setGames << m_slotRounds << "\n";
		setGames << m_blackjackRounds << "\n";
		setGames << m_crapsRounds << "\n";

	}
	else {
		std::ifstream getGames("userdata/" + m_username + "_games.txt");
		getGames >> m_lottoRounds;
		getGames >> m_doublingRounds;
		getGames >> m_rouletteRounds;
		getGames >> m_slotRounds;
		getGames >> m_blackjackRounds;
		getGames >> m_crapsRounds;
	}
	int lvl;
	double xp;
	std::ifstream getLevel("userdata/" + m_username + "_level.txt");
	if (!(getLevel >> lvl)) {
		std::ofstream setLevel("userdata/" + m_username + "_level.txt", std::ios::app);
		setLevel << 1 << "\n" << 0;
		m_level = new Level();
	}
	else {
		std::ifstream getLevel("userdata/" + m_username + "_level.txt");
		getLevel >> lvl >> xp;
		m_level = new Level(lvl, xp);
	}

	std::ifstream getTGames("userdata/" + m_username + "_tournamentgames.txt");
	if (!(getTGames >> m_tournamentRounds)) {
		std::ofstream setTGames("userdata/" + m_username + "_tournamentgames.txt", std::ios::app);
		setTGames << m_tournamentRounds << "\n";
		setTGames << m_tournamentWins << "\n";
	}
	else {
		std::ifstream getTGames("userdata/" + m_username + "_tournamentgames.txt");
		getTGames >> m_tournamentRounds;
		getTGames >> m_tournamentWins;

	}
	std::ifstream getShopItems("userdata/" + m_username + "_shop.txt");
	if (!(getShopItems >> m_maxBetLevel)) {
		std::ofstream setShopItems("userdata/" + m_username + "_shop.txt");
		setShopItems << 1;
	}
	else {
		std::ifstream getShopItems("userdata/" + m_username + "_shop.txt");
		getShopItems >> m_maxBetLevel;
	}
}

void Profile::UpdateProfile()
{

	std::ofstream setGames("userdata/" + m_username + "_games.txt");
	setGames << m_lottoRounds << "\n" << m_doublingRounds << "\n" << m_rouletteRounds << "\n"
		<< m_slotRounds << "\n" << m_blackjackRounds << "\n" << m_crapsRounds;

	std::ofstream setTournamentGames("userdata/" + m_username + "_tournamentgames.txt");
	setTournamentGames << m_tournamentRounds << "\n" << m_tournamentWins;

}

void Profile::ShowProfile()
{
	std::cout << "\n\n#################### CasinoStats ####################\n\n";
	int level = m_level->GetLevelNumber();
	double exp = m_level->GetLevelExperience();

	std::cout << "USERNAME: " << m_username << "\n";
	std::cout << "CREDIT: " << m_credit << "\n";
	std::cout << "LEVEL: " << level << "\n";
	std::cout << "EXPERIENCE: " << exp << " (" << m_level->GetRequiredEXP(level) - exp << " more to LEVEL UP) \n\n";
	std::cout << "Played Lotto: " << m_lottoRounds << "\n";
	std::cout << "Played Doubling: " << m_doublingRounds << "\n";
	std::cout << "Played Roulette: " << m_rouletteRounds << "\n";
	std::cout << "Played Slots: " << m_slotRounds << "\n";
	std::cout << "Played Blackjack: " << m_blackjackRounds << "\n";
	std::cout << "Played Craps: " << m_crapsRounds << "\n\n";

	std::cout << "#################### CasinoStats ####################\n\n";
}

Profile* Profile::GetInstance()
{
	if (instance == nullptr)
		instance = new Profile();
	return instance;
}

void Profile::DeleteInstance()
{
	delete instance;
	instance = nullptr;
}

double Profile::GetCredit()
{
	return m_credit;
}

std::string Profile::GetUsername()
{
	return m_username;
}

int Profile::GetRouletteRounds() const
{
	return m_rouletteRounds;
}

int Profile::GetCrapsRounds() const
{
	return m_crapsRounds;
}

int Profile::GetLottoRounds() const
{
	return m_lottoRounds;
}

int Profile::GetBlackjackRounds() const
{
	return m_blackjackRounds;
}

int Profile::GetSlotRounds() const
{
	return m_slotRounds;
}

int Profile::GetDoublingRounds() const
{
	return m_doublingRounds;
}

int Profile::GetTournamentRounds() const
{
	return m_tournamentRounds;
}

int Profile::GetTournamentWins() const
{
	return m_tournamentWins;
}

int Profile::GetMaxBetLevel() const
{
	return m_maxBetLevel;
}

std::string Profile::GetUsername() const
{
	return m_username;
}

Level* Profile::GetLevel()
{
	return this->m_level;
}

void Profile::SetCredit(double credit)
{
	if (credit < 0) {
		m_credit = 0;
		return;
	}
	m_credit = credit;
	std::ofstream setCredit("userdata/" + m_username + "_credit.txt");
	setCredit << m_credit;
}

void Profile::SetRouletteRounds(int rouletteRounds)
{
	m_rouletteRounds = rouletteRounds;
}

void Profile::SetCrapsRounds(int crapsRounds)
{
	m_crapsRounds = crapsRounds;
}

void Profile::SetLottoRounds(int lottoRounds)
{
	m_lottoRounds = lottoRounds;
}

void Profile::SetBlackjackRounds(int blackjackRounds)
{
	m_blackjackRounds = blackjackRounds;
}

void Profile::SetSlotRounds(int slotRounds)
{
	m_slotRounds = slotRounds;
}

void Profile::SetDoublingRounds(int doublingRounds)
{
	m_doublingRounds = doublingRounds;
}

void Profile::SetTournamentRounds(int tournamentRounds)
{
	m_tournamentRounds = tournamentRounds;
}

void Profile::SetTournamentWins(int tournamentWins)
{
	m_tournamentWins = tournamentWins;
}

void Profile::SetMaxBetLevel(int maxBetLevel)
{
	m_maxBetLevel = maxBetLevel;
}

void Profile::Jackpot(double bet)
{
	std::ifstream getJackpot("userdata/" + m_username + "_jackpot.txt");
	double jackpot = -1;
	double randomValue = rand() % 10 + 1;
	double addedValue = randomValue / 100;
	if (!(getJackpot >> jackpot)) {

		std::ofstream setJackpot("userdata/" + m_username + "_jackpot.txt");
		setJackpot << 1;
	}
	else {
		getJackpot >> jackpot;
		std::ofstream setJackpot("userdata/" + m_username + "_jackpot.txt");
		jackpot = jackpot + (bet * addedValue);
		setJackpot << jackpot;

	}

	if (rand() % 1000 == 73) {

		getJackpot >> jackpot;
		m_credit += jackpot;
		std::cout << "\n\n##################################################################\n\n";
		std::cout << "Congratulations, you won the JACKPOT of " << jackpot << " CREDITS";
		std::cout << "\n\n##################################################################\n\n";
		std::ofstream setJackpot("userdata/" + m_username + "_jackpot.txt");
		setJackpot << 1;
		system("PAUSE");
	}


}
