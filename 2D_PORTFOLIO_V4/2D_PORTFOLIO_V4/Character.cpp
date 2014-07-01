#include "Character.h"

Character::Character()
{
	CS_RIdle* pRIdle = new CS_RIdle;
	pRIdle->SetPositionLink(pos);
	AddEntry(RIDLE, pRIdle);

	CS_Go_Right* pGoR = new CS_Go_Right;
	pGoR->SetPositionLink(pos);
	AddEntry(GO_RIGHT, pGoR);

	CS_RFire* pRFire = new CS_RFire;
	pRFire->SetPositionLink(pos);
	AddEntry(RFIRE, pRFire);

	CS_LIdle* pLIdle = new CS_LIdle;
	pLIdle->SetPositionLink(pos);
	AddEntry(LIDLE, pLIdle);

	CS_Go_Left* pGoL = new CS_Go_Left;
	pGoL->SetPositionLink(pos);
	AddEntry(GO_LEFT, pGoL);

	CS_LFire* pLFire = new CS_LFire;
	pLFire->SetPositionLink(pos);
	AddEntry(LFIRE, pLFire);

	transition(RIDLE);
}
Character::~Character()
{}

void Character::SetPosition(const Point& p)
{
	pos = p;
}
