#pragma once

#include <windows.h>

class StateMachine;

class State
{
public :
	State();
	virtual ~State();

	virtual void Enter() = 0;
	virtual void Input(DWORD tick) = 0;
	virtual void Update(DWORD tick) = 0;
	virtual void Draw(HDC hdc) = 0;
	virtual void Leave() = 0;

	void SetMachine(StateMachine* pMachine);

protected :
	StateMachine* m_pMachine;
};

#include <map>

class StateMachine
{
	typedef INT KeyType;
	typedef std::map<KeyType,State*> DepotType;
public :
	StateMachine();
	virtual ~StateMachine();

	void transition(const KeyType& key);

	void AddEntry(const KeyType& key, State* pState);
	void RemoveEntry(const KeyType& key);

	virtual void Input(DWORD tick);
	virtual void Update(DWORD tick);
	virtual void Draw(HDC hdc);
protected :
	DepotType depot;
	State* _current;
};