#pragma once

#include <windows.h>
#include "BaseType.h"
#include "Animation.h"
#include "Object.h"

class Bullet : public Object
{
public :
	Bullet();
	virtual ~Bullet();

public :
	virtual void Input(DWORD tick);
	virtual void Update(DWORD tick);
	virtual void Draw(HDC hdc);

	virtual bool IsCollide(Object* );

	virtual void DoBreak();

	void SetPosition(const Point& );

	LONG GetRadius() const;

	void SetWay(const LONG& w);

private :
	Animation* pAni;
	Point Bpos;

	LONG way;

};

