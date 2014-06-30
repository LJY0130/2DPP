#pragma once

#include "BaseType.h"
#include "Animation.h"
#include "Utility.hpp"
#include "Collision.h"

class Block
{
public :
	Block();
	~Block();

public :
	void Attach(HWND);
	void Input(DWORD);
	void Update(DWORD);
	void Draw(HDC);

	void ChangeHealth(const int& );
	void DoBreak();

	void SetPosition(const Point& );
	void SetSpeed(const LONG& );

	bool BrockDrop;	// 떨어지는 중인 블록 체크

	Point GetPosition() const;
	Point pos;

private :
	HWND hOwner;

	LONG speed;

//	Animation block;	//test 블럭

	int hp_total;		// 총 HP
	int hp_current;		// HP 변화

	int addy;			//y축 ++
	int BlockSize;		//블록 지름
	int i;

	Image* pblockImg;

};

class BlockManager
{
public :
	enum { count = 100 };
private :
	BlockManager();
	~BlockManager();

public :
	static BlockManager& GetReference();

public :
	void Input(DWORD);
	void Update(DWORD);
	void Draw(HDC);

	void push(Block* pBlock);
	void pop(const int& i);

	Block** getDepot();

private :
	Block* depot[count];
};

#define BlockDepot BlockManager::GetReference()