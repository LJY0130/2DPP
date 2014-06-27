#pragma once

#include "BaseType.h"
#include "Utility.hpp"
#include "Animation.h"

class Block
{
public :
	Block();
	~Block();

public :
	void Input(DWORD);
	void Update(DWORD);
	void Draw(HDC);

	void DoBreak();

	void SetPosition(const Point& );
	void SetSpeed(const LONG& );

	Point GetPosition() const;

private :
	Point pos;
	LONG speed;

	int hp;

	static Animation Bblock;
	static Animation Rblock;
	static Animation Gblock;

//	int mapIleft = 384;
//	int mapItop = 16;
//	int mapIright = 896;
//	int mapIbottom = 656;
};