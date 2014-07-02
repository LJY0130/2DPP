#include "Bullet.h"

Bullet::Bullet()
   : Object(OBJ_BULLET, true)
{
}
Bullet::~Bullet()
{
}
void Bullet::Input(DWORD)
{
}
void Bullet::Update(DWORD)
{
	// TODO
	pos().x = pos().x + 10;
}
void Bullet::Draw(HDC hdc)
{
	::Ellipse(hdc, pos().x - radius, pos().y - radius,
		pos().x + radius, pos().y + radius);
}

bool Bullet::IsCollide(Object* obj)
{
   if (obj->type() == OBJ_TANK)
   {
      return obj->IsCollide(this);
   }
   else if (obj->type() == OBJ_BLOCK)
   {
      return obj->IsCollide(this);
   }

   return false;
}
void Bullet::DoBreak()
{
   SetNeedToClean();
   //ObjectDepot.pop(this);
}

void Bullet::SetRadius(const LONG& r)
{
	radius = r;
}
void Bullet::SetAngle(const float& ang)
{
	angle = ang;
}
LONG Bullet::GetRadius() const
{
	return radius;
}
