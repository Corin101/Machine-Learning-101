#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <array>
#include <sstream>
using namespace std;


#define STICKS 30; 


class GameConfig
{
public:
	GameConfig(bool isP1Human = true, bool isPlayer1First= true);
	~GameConfig();
	bool isPlayer1Human;
	int numberOfSticks = STICKS;
	bool isPlayer1Turn;
	int sticksTaken;
	struct Stats { int won; int lost; };	
	Stats gameStats;	
	bool GameTurn(int sticks = 0);
	bool ValidateMove();
	bool CheckVictoryCondition();	
	void GameReset(bool isP1Human = true, bool isPlayer1First = true);

private:
	vector<std::array<int, 3> > pool;
	map <int, int> tempPool;
	fstream mySaveFile;
	int GetRandomNumber(int one, int two, int three);
	int GetRandomNumberSimple(int maxNumber);
	void GetValueFromList(int listPosition);
	void InitPool();
	bool OpenFile(bool option);
	void LoadFromFile();
	void SaveToFile();
	void GameWonLearning();
	void GameLostLearning();
	Stats GetGameStatistic();
};

