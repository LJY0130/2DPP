#include "Character.h"

/////////////////////////////////////////////////
// CharacterState Impl
/////////////////////////////////////////////////
CharacterState::CharacterState()
: pos(NULL), pAni(NULL)
{}
CharacterState::~CharacterState()
{
	if (pAni)
	{
		delete pAni;
		pAni = NULL;
	}
}
void CharacterState::SetPositionLink(Point& p)
{
	pos = &p;
}

/////////////////////////////////////////////////
// CS_RIdle Impl
/////////////////////////////////////////////////
CS_RIdle::CS_RIdle()
: fire_dt(0), fire_delay(500), theta(0)	
{
	pAni = new Animation;
	for (int i = 0; i < 4; i++)
	{
		Image* pImg = new Image;
		pImg->Load(_T("Ninja.bmp"), Rect(16*i,0,16 + 16*i,16));
		pImg->SetTransparent(RGB(255, 255, 255));

		pAni->AddShot(pImg);
	}

	pAni->SetDelay(60);
	pAni->SetLoop(true);
}
CS_RIdle::~CS_RIdle()
{
}

void CS_RIdle::Enter()
{
	if (pAni)
		pAni->Reset();
}
void CS_RIdle::Input(DWORD tick)
{
	if ((::GetAsyncKeyState(VK_SPACE) & 0x8000) == 0x8000)
	{
		m_pMachine->transition(RFIRE);

		if (fire_dt > fire_delay)
		{
			Bullet* pMissile = new Bullet;
			pMissile->SetPosition(ptEnd);
			pMissile->SetRadius(10);
			pMissile->SetAngle(float(theta));

			ObjectDepot.push(pMissile);

			fire_dt = 0;
		}
		fire_dt += tick;

	}
	if ((::GetAsyncKeyState(VK_RIGHT) & 0x8000) == 0x8000)
	{
		m_pMachine->transition(GO_RIGHT);
	}
	if ((::GetAsyncKeyState(VK_LEFT) & 0x8000) == 0x8000)
	{
		m_pMachine->transition(GO_LEFT);
	}
	/*if ((::GetAsyncKeyState(VK_UP) & 0x8000) == 0x8000)
	{
		m_pMachine->transition(GO_LEFT);
	}*/
}
void CS_RIdle::Update(DWORD tick)
{
	if (pAni)
		pAni->Update(tick);
}
void CS_RIdle::Draw(HDC hdc)
{
	if (pAni)
	{
		pAni->SetRect(Rect(*pos, Size(64, 64)));
		pAni->Draw(hdc);
	}
}
void CS_RIdle::Leave()
{
}

/////////////////////////////////////////////////
// CS_Go_Right Impl
/////////////////////////////////////////////////
CS_Go_Right::CS_Go_Right()
{
	pAni = new Animation;
	for (int i = 0; i < 4; i++)
	{
		Image* pImg = new Image;
		pImg->Load(_T("Ninja.bmp"), Rect(16*i,16,16 + 16*i,32));
		pImg->SetTransparent(RGB(255, 255, 255));

		pAni->AddShot(pImg);
	}

	pAni->SetLoop();
	pAni->SetDelay(100);
}
CS_Go_Right::~CS_Go_Right()
{
}

void CS_Go_Right::Enter()
{
	if (pAni)
		pAni->Reset();
}
void CS_Go_Right::Input(DWORD tick)
{
	if ((::GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0x8000)
	{
		m_pMachine->transition(RIDLE);
	}
	if ((::GetAsyncKeyState(VK_SPACE) & 0x8000) == 0x8000)
	{
		m_pMachine->transition(RFIRE);
	}
	if ((::GetAsyncKeyState(VK_LEFT) & 0x8000) == 0x8000)
	{
		m_pMachine->transition(GO_LEFT);
	}

}
void CS_Go_Right::Update(DWORD tick)
{
	if (pAni)
	{
		pAni->Update(tick);
	}

	*pos = *pos + Point(2,0);
}
void CS_Go_Right::Draw(HDC hdc)
{
	if (pAni)
	{
		pAni->SetRect(Rect(*pos, Size(64,64)));
		pAni->Draw(hdc);
	}
}
void CS_Go_Right::Leave()
{
}


/////////////////////////////////////////////////
// CS_RFire Impl
/////////////////////////////////////////////////
CS_RFire::CS_RFire()
{
	pAni = new Animation;
	for (int i = 0; i < 4; i++)
	{
		Image* pImg = new Image;
		pImg->Load(_T("Ninja.bmp"), Rect(16*i,32,16 + 16*i,48));
		pImg->SetTransparent(RGB(255, 255, 255));

		pAni->AddShot(pImg);
	}

	pAni->SetDelay(60);
}


CS_RFire::~CS_RFire()
{
}

void CS_RFire::Enter()
{
	if (pAni)
		pAni->Reset();
}
void CS_RFire::Input(DWORD tick)
{
}
void CS_RFire::Update(DWORD tick)
{
	if (pAni)
	{
		pAni->Update(tick);
		if (!pAni->IsPlaying())
			m_pMachine->transition(RIDLE);
	}
}
void CS_RFire::Draw(HDC hdc)
{
	if (pAni)
	{
		pAni->SetRect(Rect(*pos, Size(64, 64)));
		pAni->Draw(hdc);
	}
}
void CS_RFire::Leave()
{
}


/////////////////////////////////////////////////
// CS_LIdle Impl
/////////////////////////////////////////////////
CS_LIdle::CS_LIdle()
{
	pAni = new Animation;
	for (int i = 0; i < 4; i++)
	{
		Image* pImg = new Image;
		pImg->Load(_T("Ninja.bmp"), Rect(16*i,96,16 + 16*i,112));
		pImg->SetTransparent(RGB(255, 255, 255));

		pAni->AddShot(pImg);
	}

	pAni->SetDelay(60);
	pAni->SetLoop(true);
}
CS_LIdle::~CS_LIdle()
{
}

void CS_LIdle::Enter()
{
	if (pAni)
		pAni->Reset();
}
void CS_LIdle::Input(DWORD tick)
{
	if ((::GetAsyncKeyState(VK_SPACE) & 0x8000) == 0x8000)
	{
		m_pMachine->transition(LFIRE);
	}
	if ((::GetAsyncKeyState(VK_RIGHT) & 0x8000) == 0x8000)
	{
		m_pMachine->transition(GO_RIGHT);
	}
	if ((::GetAsyncKeyState(VK_LEFT) & 0x8000) == 0x8000)
	{
		m_pMachine->transition(GO_LEFT);
	}
}
void CS_LIdle::Update(DWORD tick)
{
	if (pAni)
		pAni->Update(tick);
}
void CS_LIdle::Draw(HDC hdc)
{
	if (pAni)
	{
		pAni->SetRect(Rect(*pos, Size(64, 64)));
		pAni->Draw(hdc);
	}
}
void CS_LIdle::Leave()
{
}

/////////////////////////////////////////////////
// CS_Go_Left Impl
/////////////////////////////////////////////////
CS_Go_Left::CS_Go_Left()
{
	pAni = new Animation;
	for (int i = 0; i < 4; i++)
	{
		Image* pImg = new Image;
		pImg->Load(_T("Ninja.bmp"), Rect(16*i,112,16 + 16*i,128));
		pImg->SetTransparent(RGB(255, 255, 255));
		pAni->AddShot(pImg);
	}

	pAni->SetLoop();
	pAni->SetDelay(100);
}
CS_Go_Left::~CS_Go_Left()
{
}

void CS_Go_Left::Enter()
{
	if (pAni)
		pAni->Reset();
}
void CS_Go_Left::Input(DWORD tick)
{
	if ((::GetAsyncKeyState(VK_LEFT) & 0x8000) != 0x8000)
	{
		m_pMachine->transition(LIDLE);
	}
	if ((::GetAsyncKeyState(VK_SPACE) & 0x8000) == 0x8000)
	{
		m_pMachine->transition(LFIRE);
	}
	if ((::GetAsyncKeyState(VK_RIGHT) & 0x8000) == 0x8000)
	{
		m_pMachine->transition(GO_RIGHT);
	}

}
void CS_Go_Left::Update(DWORD tick)
{
	if (pAni)
	{
		pAni->Update(tick);
	}

	*pos = *pos + Point(-2,0);
}
void CS_Go_Left::Draw(HDC hdc)
{
	if (pAni)
	{
		pAni->SetRect(Rect(*pos, Size(64, 64)));
		pAni->Draw(hdc);
	}
}
void CS_Go_Left::Leave()
{
}

/////////////////////////////////////////////////
// CS_LFire Impl
/////////////////////////////////////////////////
CS_LFire::CS_LFire()
{
	pAni = new Animation;
	for (int i = 0; i < 4; i++)
	{
		Image* pImg = new Image;
		pImg->Load(_T("Ninja.bmp"), Rect(16*i,128,16 + 16*i,144));
		pImg->SetTransparent(RGB(255, 255, 255));
		pAni->AddShot(pImg);
	}

	pAni->SetDelay(60);
}
CS_LFire::~CS_LFire()
{
}

void CS_LFire::Enter()
{
	if (pAni)
		pAni->Reset();
}
void CS_LFire::Input(DWORD tick)
{
}
void CS_LFire::Update(DWORD tick)
{
	if (pAni)
	{
		pAni->Update(tick);
		if (!pAni->IsPlaying())
			m_pMachine->transition(LIDLE);
	}
}
void CS_LFire::Draw(HDC hdc)
{
	if (pAni)
	{
		pAni->SetRect(Rect(*pos, Size(64, 64)));
		pAni->Draw(hdc);
	}
}
void CS_LFire::Leave()
{
}
