#include "Bullet.h"

Bullet::Bullet()
: Object(OBJ_BULLET, true)
{
	pAni = new Animation;
	for (int i = 0; i < 4; i++)
	{
		Image* pImg = new Image;
		pImg->Load(_T("NinjaStars.bmp"), Rect(8*i,0,8 + 8*i,8));
		pImg->SetTransparent(RGB(255, 0, 255));

		pAni->AddShot(pImg);
	}
	pAni->SetDelay(60);
	pAni->SetLoop(true);
}
Bullet::~Bullet()
{
}
void Bullet::Input(DWORD tick)
{
}
void Bullet::Update(DWORD tick)
{
	// TODO
	if (pAni)
		pAni->Update(tick);

	if(Bpos.x >= 384 && Bpos.x <= 896)
		Bpos.x += 10*way;
	else
		DoBreak();
}
void Bullet::Draw(HDC hdc)
{
	if (pAni)
	{
		pAni->SetRect(Rect(Bpos, Size(32,32)));
		pAni->Draw(hdc);
	}
}
bool Bullet::IsCollide(Object* obj)
{
   if (obj->type() == OBJ_CHARACTER)
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

/*	if(Bpos.x >= 384 && Bpos.x <= 896)
	ObjectDepot.pop(this);*/
}
void Bullet::SetPosition(const Point& pt)
{
	Bpos = pt;
}
void Bullet::SetWay(const LONG& w)
{
	way = w;
}