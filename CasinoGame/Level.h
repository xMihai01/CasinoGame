#pragma once
#include <iostream>

class Level {

private:

	int m_levelNumber;
	double m_levelExperience;

	void LevelRewards(int level, std::string mode, double ups);

public:
	
	Level();
	Level(int levelNumber, double levelExperience);
	int GetLevelNumber() const;
	double GetLevelExperience() const;
	void SetLevelNumber(int levelNumber);
	void SetLevelExperience(double levelExperience);

	void AddLevel(double bet);
	int GetRequiredEXP(int level);


};