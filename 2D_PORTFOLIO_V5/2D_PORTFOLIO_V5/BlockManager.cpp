#include "Block.h"

BlockManager::BlockManager()
{
	for (int i = 0; i < count; i++)
	{
		depot[i] = NULL;
	}
}
BlockManager::~BlockManager()
{
	for (int i = 0; i < count; i++)
	{
		if (depot[i])
			delete depot[i];
	}
}

BlockManager& BlockManager::GetReference()
{
	static BlockManager instance;
	return instance;
}

void BlockManager::Input(DWORD tick)
{
	for (int i = 0; i < count; i++)
	{
		if (depot[i])
			depot[i]->Input(tick);
	}
}
void BlockManager::Update(DWORD tick)
{
	for (int i = 0; i < count; i++)
	{
		if (depot[i])
		{
			depot[i]->Update(tick);

		/*	if (depot[i]->hp == 0)
			{
				delete depot[i];
				depot[i] = NULL;
			}*/
		}
	}
}/*
void BlockManager::Draw(HDC hdc)
{
	for (int i = 0; i < count; i++)
	{
		if (depot[i])
			depot[i]->Draw(hdc, rand()%8);
	}
}*/

void BlockManager::push(Block* pBlock)
{
	for (int i = 0; i < count; i++)
	{
		if (depot[i] == NULL)
		{
			depot[i] = pBlock;
			break;
		}
	}
}
void BlockManager::pop(const int& i)
{
	if (depot[i])
	{
		delete depot[i];
		depot[i] = NULL;
	}
}
Block** BlockManager::getDepot()
{
	return depot;
}
