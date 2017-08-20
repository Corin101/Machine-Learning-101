#include "stdafx.h"
#include "GameConfig.h"


GameConfig::GameConfig()
{
	pool.resize(numberOfSticks);
	tempPool.resize(numberOfSticks);
	InitPool();
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
	if (isPlayer1Human)
		sticksTaken = sticks;
	else
		GetValueFromList(numberOfSticks);

	if (!ValidateMove())
		return false;

	list<int>::iterator li = tempPool[numberOfSticks].end();
	tempPool[numberOfSticks].insert(li, sticksTaken);

	isPlayer1Turn = !isPlayer1Turn;
	numberOfSticks = numberOfSticks - sticksTaken;

	CheckVictoryCondition();
	return true;
}

bool GameConfig::ValidateMove()
{
	if (sticksTaken > numberOfSticks)
		return false;
	return true;
}

bool GameConfig::CheckVictoryCondition()
{
	if (numberOfSticks == 0)
		return true;
	return false;
}

int GameConfig::GetRandomNumber(int maxNumber)
{
	srand(time(NULL));
	return rand() % maxNumber;
}
