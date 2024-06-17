#include "CGround.h"
#include "CCollider.h"
#include "CGravity.h"

CGround::CGround()
{
	CreateCollider();
}

CGround::~CGround()
{
}


void CGround::start()
{
	GetCollider()->SetScale(Vec2(GetScale()));
}

void CGround::update()
{
}

void CGround::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Player")
	{
		pOtherObj->GetGravity()->SetGround(true);

		Vec2 vObjPos = _pOther->GetfinalPos();
		Vec2 vObjScale = _pOther->GetScale();

		Vec2 vPos = GetCollider()->GetfinalPos();
		Vec2 vScale = GetCollider()->GetScale();

		float fLen = abs(vObjPos.y - vPos.y);
		float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

		vObjPos = pOtherObj->GetPos();
		vObjPos.y -= (fValue);

		pOtherObj->SetPos(vObjPos);
	} 
}

void CGround::OnCollision(CCollider* _pOther)
{

	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Player")
	{
		pOtherObj->GetGravity()->SetGround(true);

		Vec2 vObjPos = _pOther->GetfinalPos();
		Vec2 vObjScale = _pOther->GetScale();

		Vec2 vPos = GetCollider()->GetfinalPos();
		Vec2 vScale = GetCollider()->GetScale();

		float fLen = abs(vObjPos.y - vPos.y);
		float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

		// 충돌을 접한상태로 유지하기 위해서 일부로 1픽셀 덜 올려줌
		vObjPos = pOtherObj->GetPos();
		vObjPos.y -= (fValue);

		pOtherObj->SetPos(vObjPos);
	}
}

void CGround::OnCollisionExit(CCollider* _pOther)
{

	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Player")
	{
		pOtherObj->GetGravity()->SetGround(false);

	}
}

