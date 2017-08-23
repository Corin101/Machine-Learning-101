#include "stdafx.h"
#include "GameConfig.h"


GameConfig::GameConfig()
{
	pool.resize(numberOfSticks);
	tempPool.resize(numberOfSticks);
	InitPool();
	gameStats = { 0, 0 };
}


GameConfig::~GameConfig()
{
	SaveToFile();
}

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

void GameConfig::GetValueFromList(int listPosition)
{
	list<int>::iterator li = pool[listPosition].begin();
	int size = pool[listPosition].size();
	advance(li, GetRandomNumber(size));
	sticksTaken = *li;
}

CString GameConfig::TransformValueToString()
{
	CString str;
	str.Format(_T("%d"), sticksTaken);
	return str;
}

void GameConfig::PlayerConfig(string namePlayer1, bool isP1Human, string namePlayer2, bool isPlayer1First)
{
		player1Name = namePlayer1;
		isPlayer1Human = isP1Human;
		player2Name = namePlayer2;
		isPlayer1Turn = isPlayer1First;
}

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

bool GameConfig::ValidateMove()
{
	if (sticksTaken > numberOfSticks)
		return false;
	if (sticksTaken > 3 || sticksTaken < 1)
		return false;
	return true;
}

bool GameConfig::CheckVictoryCondition()
{
	if (numberOfSticks == 0)
	{
		if (isPlayer1Turn)
			gameStats.won++;
		else
			gameStats.lost++;
		return true;
	}
	isPlayer1Turn = !isPlayer1Turn;
	return false;
}

void GameConfig::EndGameLearning()
{
	if (isPlayer1Turn)
		GameWonLearning();
	else
		GameLostLearning();
}

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

GameConfig::Stats GameConfig::GetGameStatistic()
{
	return gameStats;
}


int GameConfig::GetRandomNumber(int maxNumber)
{
	srand(time(NULL));
	return rand() % maxNumber;
}
