#pragma once
#include "Security.h"
#include "Level.h"
#include <iostream>

class Profile : public Security{
private:

	Profile(Profile& otherProfile) = delete;
	void operator=(const Profile&) = delete;

protected:

	static Profile* instance;

	double m_credit;
	Level* m_level;

	int m_rouletteRounds;
	int m_crapsRounds;
	int m_lottoRounds; 
	int m_blackjackRounds;
	int m_slotRounds;
	int m_doublingRounds;
	
	int m_maxBetLevel;

	int m_tournamentRounds;
	int m_tournamentWins;

	Profile();

public:
	

	static Profile* GetInstance();
	static void DeleteInstance();

	double GetCredit();
	std::string GetUsername();
	int GetRouletteRounds() const;
	int GetCrapsRounds() const;
	int GetLottoRounds() const;
	int GetBlackjackRounds() const;
	int GetSlotRounds() const;
	int GetDoublingRounds() const;
	int GetTournamentRounds() const;
	int GetTournamentWins() const;
	int GetMaxBetLevel() const;
	std::string GetUsername() const;
	Level* GetLevel();

	void SetCredit(double credit);
	void SetRouletteRounds(int rouletteRounds);
	void SetCrapsRounds(int crapsRounds);
	void SetLottoRounds(int lottoRounds);
	void SetBlackjackRounds(int blackjackRounds);
	void SetSlotRounds(int slotRounds);
	void SetDoublingRounds(int doublingRounds);
	void SetTournamentRounds(int tournamentRounds);
	void SetTournamentWins(int tournamentWins);
	void SetMaxBetLevel(int maxBetLevel);

	void Jackpot(double bet);

	void LoadProfile();
	void ShowProfile();
	void UpdateProfile();

};