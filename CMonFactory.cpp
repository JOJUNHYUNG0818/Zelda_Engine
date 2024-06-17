#include "CMonFactory.h"
#include "CMonster.h"
#include "AI.h"
#include "CIdleState.h"
#include "CTraceState.h"
#include "pch.h"
#include "CRigidBody.h"


CMonster* CMonFactory::CreateMonster(MON_TYPE _eType, Vec2 _vPos)
{
	CMonster* pMon = nullptr;

	switch (_eType)
	{
	case MON_TYPE::NOMAL:
	{
		pMon = new CMonster;
		pMon->SetPos(_vPos);

		tMonInfo info = {};
		info.fAtt = 10.f;
		info.fAttRange = 50.f;
		info.fRecogRange = 300.f;
		info.fHP = 100.f;
		info.fSpeed = 150.f;

		pMon->SetMonInfo(info);

		pMon->CreateRigidBody();
		pMon->GetRigidBody()->SetMass(1.f);


		/*AI* pAI = new AI;
		pAI->AddState(new CIdleState);
		pAI->AddState(new CTraceState);
		pAI->SetCurState(MON_STATE::IDLE);
		pMon->SetAI(pAI);*/
	}
		break;
	case MON_TYPE::RANGE:
		break;
	}


	assert(pMon);

	return pMon;
}
