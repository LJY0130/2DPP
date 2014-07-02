#pragma once

#include <windows.h>
#include "BaseType.h"
#include "Object.h"
#include "Character.h"
#include "Block.h"

class Bullet : public Object
{
public :
	Bullet();
	virtual ~Bullet();

public :
	virtual void Input(DWORD);
	virtual void Update(DWORD);
	virtual void Draw(HDC);

   virtual bool IsCollide(Object* );

   virtual void DoBreak();

	void SetRadius(const LONG& r);
	void SetAngle(const float& ang);

	LONG GetRadius() const;

private :
	LONG radius;

	float angle;
};

