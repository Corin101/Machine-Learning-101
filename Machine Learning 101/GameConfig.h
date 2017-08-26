#pragma once
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <fstream>
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
	struct Stats { int won; int lost; };
	vector<list<int> > pool;
	vector<list<int> > tempPool;
	Stats gameStats;
	

	void GetValueFromList(int listPosition);
	void InitPool();
	bool OpenFile(bool option);
	void LoadFromFile();
	void SaveToFile();
	CString TransformValueToString();
	bool GameTurn(int sticks = 0);
	bool ValidateMove();
	bool CheckVictoryCondition();
	void GameWonLearning();
	void GameLostLearning();
	Stats GetGameStatistic();
	void GameReset(bool isP1Human = true, bool isPlayer1First = true);



private:

	int sticksTaken;
	fstream mySaveFile;
	int GetRandomNumber(int maxNumber);
};

