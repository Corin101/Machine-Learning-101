#pragma once
#include <iostream>
#include <string>
#include <list>
#include <vector>
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
	bool InitPool(int noOfSticks);
	bool LoadFromFile();
	CString TransformValueToString();



private:

	int sticksTaken;
	int GetRandomNumber(int maxNumber);
};

