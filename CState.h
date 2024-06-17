#pragma once
#include "define.h"
class AI;
class CMonster;

class CState
{
private:
	AI*         m_pAI;
	MON_STATE   m_eState;

public:
	AI* GetAI() { return m_pAI; }
	MON_STATE GetType() { return m_eState; }
	CMonster* GetMonster();

public:
	virtual void update() = 0;
	virtual void Enter() = 0;  // 순수 가상함수 (자식이 구현)
	virtual void Exit() = 0;  //  


public:
    CState(MON_STATE _eState); //반드시 몬스터상태를 입력받을수 있는 생성자
	virtual ~CState();

	friend class AI;

};

