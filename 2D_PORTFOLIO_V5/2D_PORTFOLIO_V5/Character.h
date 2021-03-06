﻿#pragma once

#include "FSM.h"
#include "Animation.h"
#include "Bullet.h"
#include "Object.h"
#include "Collision.h"

enum Character_State_id
{
	RIDLE,
	GO_RIGHT,
	RFIRE,
	LIDLE,
	GO_LEFT,
	LFIRE
};

class CharacterState : public State, public Object
{
public :
	CharacterState();
	virtual ~CharacterState();

	virtual void Enter() = 0;
	virtual void Input(DWORD tick) = 0;
	virtual void Update(DWORD tick) = 0;
	virtual void Draw(HDC hdc) = 0;
	virtual void Leave() = 0;

	virtual bool IsCollide(Object* );
	virtual void DoBreak();

	void SetPositionLink(Point& p);
	Point GetPosition() const;

	// fire 
	DWORD fire_dt;
	DWORD fire_delay;

protected :
	Point* pos;
	Animation* pAni;

	Bullet* pMissile;
};

class Character : public StateMachine
{
public :
	Character();
	virtual ~Character();

	void SetPosition(const Point& p);
	Point GetPosition() const;

protected :
	Point pos;
};

class CS_RIdle : public CharacterState
{
public :
	CS_RIdle();
	virtual ~CS_RIdle();

	virtual void Enter();
	virtual void Input(DWORD tick);
	virtual void Update(DWORD tick);
	virtual void Draw(HDC hdc);
	virtual void Leave();

//	virtual bool IsCollide(Object* );
};

class CS_Go_Right : public CharacterState
{
public :
	CS_Go_Right();
	virtual ~CS_Go_Right();

	virtual void Enter();
	virtual void Input(DWORD tick);
	virtual void Update(DWORD tick);
	virtual void Draw(HDC hdc);
	virtual void Leave();

//	virtual bool IsCollide(Object* );
};

class CS_RFire : public CharacterState
{
public :
	CS_RFire();
	virtual ~CS_RFire();

	virtual void Enter();
	virtual void Input(DWORD tick);
	virtual void Update(DWORD tick);
	virtual void Draw(HDC hdc);
	virtual void Leave();

//	virtual bool IsCollide(Object* );
};

class CS_LIdle : public CharacterState
{
public :
	CS_LIdle();
	virtual ~CS_LIdle();

	virtual void Enter();
	virtual void Input(DWORD tick);
	virtual void Update(DWORD tick);
	virtual void Draw(HDC hdc);
	virtual void Leave();

//	virtual bool IsCollide(Object* );

};
class CS_Go_Left : public CharacterState
{
public :
	CS_Go_Left();
	virtual ~CS_Go_Left();

	virtual void Enter();
	virtual void Input(DWORD tick);
	virtual void Update(DWORD tick);
	virtual void Draw(HDC hdc);
	virtual void Leave();

//	virtual bool IsCollide(Object* );

};

class CS_LFire : public CharacterState
{
public :
	CS_LFire();
	virtual ~CS_LFire();

	virtual void Enter();
	virtual void Input(DWORD tick);
	virtual void Update(DWORD tick);
	virtual void Draw(HDC hdc);
	virtual void Leave();

//	virtual bool IsCollide(Object* );

};
