#include "CRigidBody.h"
#include "pch.h"
#include "CTimeMgr.h"
#include "CObject.h"

CRigidBody::CRigidBody()
	: m_pOwner(nullptr)
	, m_fMass(1.f)
	, m_fFricCoeff(100.f)
	, m_vMaxVelocity(Vec2(200.f,600.f))
{
}

CRigidBody::~CRigidBody()
{
}


void CRigidBody::finalupdate()
{
	// 힘의 크기
	float fForce = m_vForce.Length();

	if (0.f != fForce)
	{
		// 힘의 방향
		m_vForce.Normalize();

		// 가속도의 크기
		float m_fAccel = fForce / m_fMass;

		// 가속도
		m_vAccel = m_vForce * m_fAccel; // m_vForce / m_fMass;
	}

	// 추가 가속도
	m_vAccel += m_vAccelA;

	// 속도
	m_vVelocity += m_vAccel * fDT;

	// 마찰력에의한 반대방향으로의 가속도
	if (!m_vVelocity.IsZero())
	{
		Vec2 vFricDir = -m_vVelocity;
		vFricDir.Normalize();

		Vec2 vFriction = vFricDir * m_fFricCoeff * fDT;
		if (m_vVelocity.Length() <= vFriction.Length())
		{
			// 마찰 가속도가 본래 속도보다 더 큰 경우
			m_vVelocity = Vec2(0.f, 0.f);
		}
		else
		{
			m_vVelocity += vFriction;
		}
	}
	
	// 속도 제한 검사
	if (abs(m_vMaxVelocity.x) < abs(m_vVelocity.x))
	{
		m_vVelocity.x = (m_vVelocity.x / abs(m_vMaxVelocity.x)) * abs(m_vMaxVelocity.x);
	}

	if (abs(m_vMaxVelocity.y) < abs(m_vVelocity.y))
	{
		m_vVelocity.y = (m_vVelocity.y / abs(m_vMaxVelocity.y)) * abs(m_vMaxVelocity.y);
	}

	// 속도에 따른 이동
	Move();

	// 힘 초기화
	m_vForce = Vec2(0.f, 0.f);

	// 추가 가속도 초기화
	m_vAccel = Vec2(0.f, 0.f);
	m_vAccelA = Vec2(0.f, 0.f);

}

void CRigidBody::Move()
{
	// 이동 속력
	float fSpeed = m_vVelocity.Length();

	if (0.f != fSpeed)
	{
		//  이동 방향
		Vec2 vDir = m_vVelocity;
		vDir.Normalize();

		Vec2 vPos = m_pOwner->GetPos();

		vPos += m_vVelocity * fDT;  // m_vVeloctity = vDir * fSpeed

		m_pOwner->SetPos(vPos);
	}
}
