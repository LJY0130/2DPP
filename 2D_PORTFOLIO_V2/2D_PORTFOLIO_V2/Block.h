#pragma once

#include "BaseType.h"
#include "Utility.hpp"

class Block
{

public :
	void Update(DWORD);
	void Draw(HDC);

	void SetPosition(const Point& );
	void SetSize(const LONG& );
	void SetSpeed(const LONG& );

	Point GetPosition() const;

private :
	Point pos;
	LONG size;
	LONG speed;
};