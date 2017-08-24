#include "stdafx.h"
#include "GameConfig.h"


GameConfig::GameConfig(bool isP1Human, bool isPlayer1First)
{
	pool.resize(numberOfSticks);
	tempPool.resize(numberOfSticks);
	InitPool();
	isPlayer1Human = isP1Human;
	isPlayer1Turn = isPlayer1First;
	gameStats = { 0, 0 };
}


GameConfig::~GameConfig()
{
	SaveToFile();
}
//Initialize the pool for the game.If there is a saved game file(save.txt) than it initializes
//values from the file, if there is no file, that it makes a starting initialization.
void GameConfig::InitPool()
{
	if (!OpenFile(true))
	{
		for (size_t i = 0; i < pool.size(); ++i)
		{
			list<int>::iterator li = pool[i].begin();
			if (i == 0)
			{
				pool[i].insert(li, 1);
			}
			else if (i == 1)
			{
				pool[i].insert(li, 1);
				pool[i].insert(li, 2);
			}
			else
			{
				pool[i].insert(li, 1);
				pool[i].insert(li, 2);
				pool[i].insert(li, 3);
			}
		}
	}
	else
		LoadFromFile();
}
// Open File::
//		- option == True - open file for reading
//		- option == false - open file for writing
bool GameConfig::OpenFile(bool option)
{
	if (option)
		mySaveFile.open("save.txt",fstream::in);
	else
		mySaveFile.open("save.txt", fstream::out);

	if (mySaveFile)
		return true;
	return false;
}
//Loads values from a saved file into a pool
void GameConfig::LoadFromFile()
{
	for (size_t i = 0; i < pool.size(); ++i)
	{
		list<int>::iterator li = pool[i].begin();
		string stringLine;

		getline(mySaveFile, stringLine);
		string::iterator it;
		for (it = stringLine.begin(); it != stringLine.end(); it++)
		{
			if ((*it) == ' ')
				continue;
			
			int value = *it - '0';
			pool[i].insert(li, value);
		}
	}
	mySaveFile.close();
}
//Opens a file for writing and saves the current pool into a file
void GameConfig::SaveToFile()
{
	OpenFile(false);
	for (size_t i = 0; i < pool.size(); ++i)
	{
		list<int>::iterator li;
		string stringLine;

		for (li = pool[i].begin(); li != pool[i].end(); li++)
		{
			stringLine.append(to_string(*li));
			stringLine.append(" ");
		}
		mySaveFile << stringLine << "\n";
	}
	mySaveFile.close();
}
//Gets a random number from a list at a specific position
void GameConfig::GetValueFromList(int listPosition)
{
	list<int>::iterator li = pool[listPosition].begin();
	int size = pool[listPosition].size();
	advance(li, GetRandomNumber(size));
	sticksTaken = *li;
}
//Prepares a value for display, this function was used for testing,
//it does not belong here, but it might be needed later.
CString GameConfig::TransformValueToString()
{
	CString str;
	str.Format(_T("%d"), sticksTaken);
	return str;
}

//Player turn, different actions depending if a player is human or computer.
bool GameConfig::GameTurn(int sticks)
{	
	if (isPlayer1Human && isPlayer1Turn)
	{
		sticksTaken = sticks;
		numberOfSticks -= sticksTaken;
		if (!ValidateMove())
			return false;
	}
	if (!isPlayer1Human && isPlayer1Turn)
	{
		sticksTaken = GetRandomNumber(3);
	}
	if (!isPlayer1Turn)
	{
		GetValueFromList(numberOfSticks);
		list<int>::iterator li = tempPool[numberOfSticks].end();
		tempPool[numberOfSticks].insert(li, sticksTaken);
	}
	numberOfSticks = numberOfSticks - sticksTaken;
	return true;
}
//Move validation, the player is allowed to take only 1 – 3 sticks,
//and cannot reduce the pool below 0 sticks.
bool GameConfig::ValidateMove()
{
	if (sticksTaken > numberOfSticks)
		return false;
	if (sticksTaken > 3 || sticksTaken < 1)
		return false;
	return true;
}
//Game ends if the pool(numberOfSticks) reaches zero.Write if the game was won or lost.
//Save what was learned into pool.
//If the game did not end, change active player.
bool GameConfig::CheckVictoryCondition()
{
	if (numberOfSticks == 0)
	{
		if (isPlayer1Turn)
		{
			gameStats.won++;
			GameWonLearning();
		}
		else
		{
			gameStats.lost++;
			GameLostLearning();
		}
		return true;
	}
	isPlayer1Turn = !isPlayer1Turn;
	return false;
}
//If the game was won the computer “memorizes” that games moves.
void GameConfig::GameWonLearning()
{
	list<int>::iterator li;
	list<int>::iterator templi;
	for (size_t i = 0; i < pool.size(); ++i)
	{
		if (tempPool[i].size() == 0)
			continue;
		else
		{
			li = pool[i].end();
			templi = tempPool[i].begin();
			pool[i].insert(li, *templi);
		}
	}
}
//If the game was lost the computer “forgets” that games moves
void GameConfig::GameLostLearning()
{
	list<int>::iterator li;
	list<int>::iterator templi;
	for (size_t i = 0; i < pool.size(); ++i)
	{
		if (tempPool[i].size() == 0)
			continue;
		else
		{
			templi = tempPool[i].begin();
			int count = 0;
			for (li = pool[i].begin(); li != pool[i].end(); li++)
			{
				if (*li == *templi)
					count++;
				if (count > 1)
				{
					pool[i].erase(li);
					break;
				}					
			}
		}
	}
}
//Returns game statistics, how many games were won and lost.
GameConfig::Stats GameConfig::GetGameStatistic()
{
	return gameStats;
}
// Resets a game is a player wants to play again. Player that lost starts the game.
void GameConfig::GameReset()
{
	numberOfSticks = STICKS;
	tempPool.clear();
}

//Returns a random number between 0 and maxNumber
int GameConfig::GetRandomNumber(int maxNumber)
{
	srand(time(NULL));
	return rand() % maxNumber;
}
