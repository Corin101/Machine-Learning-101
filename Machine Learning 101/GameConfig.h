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
	GameConfig();
	~GameConfig();
	string player1Name;
	string player2Name;
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
	void PlayerConfig(string namePlayer1, bool isP1Human, string namePlayer2, bool isPlayer1First);
	bool GameTurn(int sticks = 0);
	bool ValidateMove();
	bool CheckVictoryCondition();
	void EndGameLearning();
	void GameWonLearning();
	void GameLostLearning();
	Stats GetGameStatistic();



private:

	int sticksTaken;
	fstream mySaveFile;
	int GetRandomNumber(int maxNumber);
};

