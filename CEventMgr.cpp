#include "pch.h"
#include "CEventMgr.h"
#include "CObject.h"
#include "CSceneMgr.h"
#include "CScene.h"

#include "AI.h"
#include "CState.h"
#include "CUIMgr.h"




CEventMgr::CEventMgr()
{
}

CEventMgr::~CEventMgr()
{
}


void CEventMgr::update()
{
	// ================================================
	// 이전 프레임에서 등록해둔 Dead Object 들을 삭제한다.
	// ================================================
	for (size_t i = 0; i < m_vecDead.size(); ++i)
	{
		delete m_vecDead[i];
	}
	m_vecDead.clear();

	// ==========
	// Event 처리
	// ==========

	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		Excute(m_vecEvent[i]);
	}

	m_vecEvent.clear();
}

void CEventMgr::Excute(const tEvent& _eve)
{
	_eve.eEven;

	switch (_eve.eEven)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		// lParam : Object Adress
		// wParam : Group Type
		CObject* pNewObj = (CObject*)_eve.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_eve.wParam;

		CSceneMgr::GetInst()->GetCurScene()->AddObject(pNewObj, eType);
	}
	break;
	case EVENT_TYPE::DELETE_OBJECT:
	{
		// lParam : Object Adress
		// Object 를 Dead 상태로 변경
		// 삭제예정 오브젝트들을 모아둔다.
		CObject* pDeadObj = (CObject*)_eve.lParam;
		pDeadObj->SetDead();
		m_vecDead.push_back(pDeadObj);

	}
	break;
	case EVENT_TYPE::SCENE_CHANGE:
	{
		// lParam : Next Scene Type
		// Scene 변경
		CSceneMgr::GetInst()->ChangeScene((SCENE_TYPE)_eve.lParam);

		// 포커스 UI 해제 (이전 Scene 의 UI 를 가리키고 있기 때문에 해제)
		CUIMgr::GetInst()->SetFocusedUI(nullptr);
		break;
	}

	case EVENT_TYPE::CHANCE_AI_STATE:
	{
		// lParam : AI
		// wParam : Next Type
		AI* pAI = (AI*)_eve.lParam;
		MON_STATE eNextState = (MON_STATE)_eve.wParam;

		pAI->ChangeState(eNextState);
	}
	break;
	}
}
