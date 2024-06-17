#include "pch.h"
#include "CScene_Start.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CCore.h"
#include "CTexture.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CCamera.h"
#include "AI.h"
#include "CIdleState.h"
#include "CTraceState.h"
#include "CRigidBody.h"
#include "SelectGDI.h"
#include "CTimeMgr.h"
#include "CGround.h"

CScene_Start::CScene_Start()
	: m_bUseForce(false)
	, m_fForceRadius(500.f)
	, m_fCurRadius(0.f)
	, m_fForce(500.f)
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::update()
{
	if (KEY_HOLD(KEY::LBTN))
	{
		m_bUseForce = true;
		CreateForce();
	}
	else
	{
		m_bUseForce = false;
	}

	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		const vector<CObject*>& vecObj = GetGroupObject((GROUP_TYPE)i);

		for (size_t j = 0; j < vecObj.size(); ++j)
		{
			if (!vecObj[j]->IsDead())
			{
				if (m_bUseForce && vecObj[j]->GetRigidBody())
				{
					Vec2 vDiff = vecObj[j]->GetPos() - m_vForcePos;
					float fLen = vDiff.Length();
					if (fLen < m_fForceRadius)
					{
						float fRatio = 1.f - (fLen / m_fForceRadius);
						float fForce = m_fForce * fRatio;

						vecObj[j]->GetRigidBody()->AddForce(vDiff.Normalize() * fForce);

					}
				}

				vecObj[j]->update();
			}
		}
	}

	
	// �� ü����
	/*if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}*/

	/*if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vLookAt = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		CCamera::GetInst()->SetLookAt(vLookAt);
	}*/ //Ŭ���� ī�޶� ������

}

void CScene_Start::render(HDC _dc)
{
	CScene::render(_dc);

	if (!m_bUseForce)
		return;

	SelectGDI gdi1(_dc, BRUSH_TYPE::HOLLOW);
	SelectGDI gdi2(_dc, PEN_TYPE::GREEN);

	m_fCurRadius += m_fForceRadius * 2.f * fDT;

	if (m_fCurRadius > m_fForceRadius)
	{
		m_fCurRadius = 0.f;
	}

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vForcePos);

	Ellipse(_dc
		,(int)(vRenderPos.x - m_fCurRadius)
		,(int)(vRenderPos.y - m_fCurRadius)
		,(int)(vRenderPos.x + m_fCurRadius)
		,(int)(vRenderPos.y + m_fCurRadius));

}

void CScene_Start::Enter()
{
	// Object �߰�
	CObject* pObj = new CPlayer;
	pObj->setName(L"Player");
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f,100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	RegisterPlayer(pObj);

	//CCamera::GetInst()->SetTarget(pObj);

	/*CObject* pOtherPlayer = pObj->Clone();
	pOtherPlayer->SetPos(Vec2(740.f, 384.f));
	AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);*/


	// ���� ��ġ
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::NOMAL, vResolution / 2.f - Vec2(0.f, 300.f));
	AddObject(pMon, GROUP_TYPE::MONSTER);

	// �� ��ü ��ġ
	CObject* pGround = new CGround;
	pGround->setName(L"Ground");
	pGround->SetPos(Vec2(640.f, 584.f));
	pGround->SetScale(Vec2(500.f, 60.f));
	AddObject(pGround, GROUP_TYPE::GROUND);


	// Ÿ�� �ε�
	

	// �浹 ����
	// Player �׷�� Monster �׷� ���� �浹 üũ

	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PROJ_PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);


	// Camera Look ����
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);

	// Camera ȿ�� ����
	CCamera::GetInst()->FadeOut(1.f);
	CCamera::GetInst()->FadeIn(1.f);

	start();


}

void CScene_Start::Exit()
{
	DeleteAll();

	CCollisionMgr::GetInst()->Reset();

}

void CScene_Start::CreateForce()
{
	m_vForcePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);
}


