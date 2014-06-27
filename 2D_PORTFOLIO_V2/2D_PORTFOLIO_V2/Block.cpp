#include "Block.h"

Block::Block()
: speed(5), hp(300)
{
}
Block::~Block()
{
}

void Block::Input(DWORD)
{
}
void Block::Update(DWORD tick)
{
	pos.y = pos.y + speed;
}
void Block::Draw(HDC hdc)
{
	/*Bblock.SetRect(Rect(mapIleft+64*j, mapItop+addy, 
		mapIleft+64*j+BlockSize, mapItop+BlockSize+addy));
	Bblock.Draw(backbuffer);*/
}
void Block::DoBreak()
{
   hp -= 1;

   if (hp == 0);
//
}
void Block::SetPosition(const Point& pt)
{
	pos = pt;
}
void Block::SetSpeed(const LONG& s)
{
	speed = s;
}

Point Block::GetPosition() const
{
	return pos;
}
