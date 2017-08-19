#include "stdafx.h"
#include "GameConfig.h"


GameConfig::GameConfig()
{
	pool.resize(numberOfSticks);
	InitPool(numberOfSticks);
}


GameConfig::~GameConfig()
{
}

bool GameConfig::InitPool(int noOfSticks)
{
	try {
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
		return true;
	}
	catch (...)
	{
		return false;
	}
}

bool GameConfig::LoadFromFile()
{
	return false;
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

int GameConfig::GetRandomNumber(int maxNumber)
{
	srand(time(NULL));
	return rand() % maxNumber;
}
