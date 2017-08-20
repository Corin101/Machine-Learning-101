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
	bool Player1IsHuman;
	bool Player2IsHuman;
	int numberOfSticks = STICKS;
	bool VictoryCondition;
	bool isPlayer1Turn;
	vector<list<int> > pool;
	

	void GetValueFromList(int listPosition);
	void InitPool();
	bool OpenFile(bool option);
	void LoadFromFile();
	void SaveToFile();
	CString TransformValueToString();
	void PlayerConfig(string namePlayer1, bool isP1Human, string namePlayer2, bool isP2Human, bool isPlayer1First);
	void ComputerTurn();


private:

	int sticksTaken;
	fstream mySaveFile;
	int GetRandomNumber(int maxNumber);
};

