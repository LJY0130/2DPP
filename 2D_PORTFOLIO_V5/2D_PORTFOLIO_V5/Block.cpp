#include "Block.h"

Block::Block()
: hOwner(NULL), speed(5)
,hp_total(300), hp_current(300)
,addy(0), BlockSize(64), i(rand()%3)
,pblockImg(NULL), BrockDrop(false)
, Object(OBJ_BLOCK, true)
{
}
Block::~Block()
{
}
void Block::Attach(HWND hWnd)
{
	hOwner = hWnd;
}
void Block::Input(DWORD)
{
}
void Block::Update(DWORD tick)
{
	if(addy < 48)
	{
		addy++;
	}
	if(addy < 448)
	{
		int add = addy;
		add *= 5.11f;
		addy=add/5;

	}
	if(addy >= 448)
		BrockDrop = false;
}
void Block::Draw(HDC hdc)
{
	/*if(BrockDrop == true)
	{
		Image* pblockImg = new Image;
		pblockImg->Load(_T("BlockSheet01b.bmp"), Rect(16, 16*i, 32, 16*i+16));
		pblockImg->SetTransparent(RGB(255,255,255));
		pblockImg->SetRect(Rect(Point(pos.x, pos.y+addy), Size(BlockSize,BlockSize)));
		pblockImg->Draw(hdc);
	}*/
	/*if(BrockDrop == false)
	{*/
		Image* pblockImg = new Image;
		pblockImg->Load(_T("BlockSheet01b.bmp"), Rect(16, 16*i, 32, 16*i+16));
		pblockImg->SetTransparent(RGB(255,255,255));
		pblockImg->SetRect(Rect(Point(pos.x, pos.y+addy), Size(BlockSize,BlockSize)));
		pblockImg->Draw(hdc);
		
		BrockDrop = true;
	//}
}
bool Block::IsCollide(Object* obj)
{
   if (obj->type() == OBJ_CHARACTER)
   {
      Character* pCharacter = dynamic_cast<Character*>(obj);
      Point pt = pCharacter->GetPosition();
//      LONG r = pCharacter->GetRadius();
      for (int i = 0; i < hp_total/25 + 1; i++)
      {
         if (Collision(Rect(pos.x-32, pos.y-32, pos.x+32, pos.y+32),pt, 32))
            return true;
      }
   }
   else if (obj->type() == OBJ_BULLET)
   {
      Bullet* pBullet = dynamic_cast<Bullet*>(obj);
      Point pt = pBullet->GetPosition();
     // LONG r = pBullet->GetRadius();
      for (int i = 0; i < hp_total/25 + 1; i++)
      {
         if (Collision(Rect(pos.x-32, pos.y-32, pos.x+32, pos.y+32),pt, 32))
            return true;
      }
   }
   return false;
}
void Block::ChangeHealth(const int& diff)
{
	hp_current += diff;
	
	if (hp_current < 0)
		hp_current = 0;
	else if (hp_current > hp_total)
		hp_current = hp_total;
}
void Block::DoBreak()
{
   hp_current -= 100;

   if (hp_current == 0);
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
