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
	int sticksTaken;
	vector<list<int> > pool;


	bool InitPool(int noOfSticks);
	bool LoadFromFile();
};

