#include "Block.h"

void Block::Update(DWORD tick)
{
	pos.y = pos.y + speed;
}
void Block::Draw(HDC hdc)
{
	::Rectangle(hdc, pos.x - size, pos.y - size,
		pos.x + size, pos.y + size);
}

void Block::SetPosition(const Point& pt)
{
	pos = pt;
}
void Block::SetSize(const LONG& s)
{
	size = s;
}
void Block::SetSpeed(const LONG& s)
{
	speed = s;
}

Point Block::GetPosition() const
{
	return pos;
}
