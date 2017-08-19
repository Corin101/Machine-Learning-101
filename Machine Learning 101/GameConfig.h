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
	int numberOfSticks = STICKS;
	bool VictoryCondition;
	vector<list<int> > pool;
	

	void GetValueFromList(int listPosition);
	void InitPool();
	bool OpenFile(bool option);
	void LoadFromFile();
	void SaveToFile();
	CString TransformValueToString();



private:

	int sticksTaken;
	fstream mySaveFile;
	int GetRandomNumber(int maxNumber);
};

