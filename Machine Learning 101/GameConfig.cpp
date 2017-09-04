#include "stdafx.h"
#include "GameConfig.h"


GameConfig::GameConfig()
{

}

GameConfig::~GameConfig()
{
	SaveToFile();
}

void GameConfig::GameSetter(bool isP1Human, bool isPlayer1First)
{
	InitPool();
	isPlayer1Human = isP1Human;
	isPlayer1Turn = isPlayer1First;
	gameStats = { 0, 0 };
	isGameReady = true;
	srand(time(NULL));
}

//Initialize the pool for the game.If there is a saved game file(save.txt) than it initializes
//values from the file, if there is no file, that it makes a starting initialization.
void GameConfig::InitPool()
{
	if (OpenFile(true) && LoadFromFile())
		return;
	else
	{
		pool.clear();
		for (size_t i = 0; i < 30; ++i)
		{
			array<int, 3> filler{ { 1,1,1 } };
			pool.push_back(filler);
		}
	}
}
// Open File::
//		- option == True - open file for reading
//		- option == false - open file for writing
bool GameConfig::OpenFile(bool option)
{
	option ? mySaveFile.open("save.txt", fstream::in) : mySaveFile.open("save.txt", fstream::out);

	if (mySaveFile)
		return true;
	return false;
}
//Loads values from a saved file into a pool
bool GameConfig::LoadFromFile()
{
	try {
		for (size_t i = 0; i < 30; ++i)
		{
			string stringLine;
			getline(mySaveFile, stringLine);
			stringstream stream(stringLine);
			array<int, 3> filler;
			int fillerCounter = 0;
			int value;

			while (stream >> value) {
				filler.at(fillerCounter) = value;
				fillerCounter++;
			}
			pool.push_back(filler);
		}
		mySaveFile.close();
	}
	catch (exception)
	{
		mySaveFile.close();
		return false;
	}	

}
//Opens a file for writing and saves the current pool into a file
void GameConfig::SaveToFile()
{
	OpenFile(false);
	for (size_t i = 0; i < pool.size(); ++i)
	{
		string stringLine;
		for (int arrayCounter = 0; arrayCounter < 3; arrayCounter++)
		{
			stringLine.append(to_string(pool[i].at(arrayCounter)));
			stringLine.append(" ");
		}
		mySaveFile << stringLine << "\n";
	}
	mySaveFile.close();
}
//Gets a random number from a list at a specific position
void GameConfig::GetValueFromList(int listPosition)
{
	sticksTaken = GetRandomNumber(pool[listPosition].at(0), pool[listPosition].at(1), pool[listPosition].at(2));
}

//Player turn, different actions depending if a player is human or computer.
bool GameConfig::GameTurn(int sticks)
{	
	if (isPlayer1Human && isPlayer1Turn)
	{
		sticksTaken = sticks;
		if (!ValidateMove())
			return false;
	}
	if (!isPlayer1Human && isPlayer1Turn)
	{
		numberOfSticks > 2 ? sticksTaken = GetRandomNumberSimple(3) + 1 : sticksTaken = 1;
	}
	if (!isPlayer1Turn)
	{
		if (numberOfSticks < 3)
		{
			sticksTaken = 1;
			tempPool[numberOfSticks - 1] = sticksTaken;
		}
		else
		{
		GetValueFromList(numberOfSticks - 1);
		tempPool[numberOfSticks - 1] = sticksTaken;
		}
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
	for (map<int, int>::iterator it = tempPool.begin(); it != tempPool.end(); ++it)
		pool[it->first].at(it->second - 1) += 1;
}
//If the game was lost the computer “forgets” that games moves
void GameConfig::GameLostLearning()
{
	for (map<int, int>::iterator it = tempPool.begin(); it != tempPool.end(); ++it)
		if (pool[it->first].at(it->second - 1) > 1)
			pool[it->first].at(it->second - 1) -= 1;
}
//Returns game statistics, how many games were won and lost.
GameConfig::Stats GameConfig::GetGameStatistic()
{
	return gameStats;
}
// Resets a game is a player wants to play again. Player that lost starts the game.
void GameConfig::GameReset(bool isP1Human, bool isPlayer1First)
{
	numberOfSticks = STICKS;
	tempPool.clear();
	isPlayer1Human = isP1Human;
	isPlayer1Turn = isPlayer1First;
}

//Returns a random number between 0 and maxNumber
int GameConfig::GetRandomNumber(int one, int two, int three)
{
	int randNum = rand() % (one + two + three ) + 1;
	if (randNum <= one)
		return 1;
	return randNum <= one + two ?  2 : 3;
}

int GameConfig::GetRandomNumberSimple(int maxNumber)
{
	return rand() % maxNumber;
}
