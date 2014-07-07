#include "FSM.h"

State::State()
: m_pMachine(NULL)
{}
State::~State()
{}
void State::SetMachine(StateMachine* pMachine)
{
	m_pMachine = pMachine;
}





StateMachine::StateMachine()
: _current(NULL)
{
}
StateMachine::~StateMachine()
{
	DepotType::iterator it;
	for (it = depot.begin(); it != depot.end(); )
	{
		delete it->second;
		it = depot.erase(it);
	}
}

void StateMachine::transition(const KeyType& key)
{
	DepotType::iterator it = depot.find(key);
	if (it == depot.end())
		return;

	State* pPrevState = _current;

	(it->second)->Enter();

	_current = it->second;

	if (pPrevState)
		pPrevState->Leave();
}

void StateMachine::AddEntry(const KeyType& key, State* pState)
{
	DepotType::iterator it = depot.find(key);
	if (it == depot.end())
	{
		pState->SetMachine(this);
		depot.insert(std::make_pair(key,pState));
	}
}
void StateMachine::RemoveEntry(const KeyType& key)
{
	DepotType::iterator it = depot.find(key);
	if (it == depot.end())
		return;

	delete it->second;
	depot.erase(it);
}

void StateMachine::Input(DWORD tick)
{
	if (_current)
		_current->Input(tick);
}
void StateMachine::Update(DWORD tick)
{
	if (_current)
		_current->Update(tick);
}
void StateMachine::Draw(HDC hdc)
{
	if (_current)
		_current->Draw(hdc);
}
