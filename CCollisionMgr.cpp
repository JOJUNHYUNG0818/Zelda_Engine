#include "pch.h"
#include "CCollisionMgr.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"
#include "CCollider.h"







CCollisionMgr::CCollisionMgr()
	: m_arrCheck{}
{

}

CCollisionMgr::~CCollisionMgr()
{

}


void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// �� ���� ���� �׷� Ÿ���� ������
	// ū ���� ��(��Ʈ)�� ���

	UINT iRow = (UINT)_eLeft;  // ��
	UINT iCol = (UINT)_eRight; // ��

	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	if (m_arrCheck[iRow] & (1 << iCol))
	{
		m_arrCheck[iRow] &= ~(1 << iCol);
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol);
	}
}



void CCollisionMgr::update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}

}


void CCollisionMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);
	map<ULONGLONG, bool>::iterator iter;

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// �浹ü�� �������� �ʴ� ���
		if (nullptr == vecLeft[i]->GetCollider())
		{
			continue;
		}

		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			
			if (nullptr == vecRight[j]->GetCollider() || vecLeft[i] == vecRight[j])
			{
				continue;
			}

			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();

			// �� �浹ü ���� ���̵� ����
			COLLIDER_ID ID;
			ID.Left_id = pLeftCol->GetID();
			ID.Right_id = pRightCol->GetID();
			

			 iter = m_mapColInfo.find(ID.ID);

			// �浹 ������ �̵�� ������ ��� ���(�浹���� �ʾҴ� ��)
			if (m_mapColInfo.end() == iter)
			{
				 m_mapColInfo.insert(make_pair(ID.ID, false));
				 iter = m_mapColInfo.find(ID.ID);
			}


			if (IsCollision(pLeftCol, pRightCol))
			{
				// ���� �浹 ���̴�.

				if (iter->second)
				{
					// �������� �浹 �ϰ� �־���.
					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
					{
						// �ٵ� ���� �ϳ��� ���� �����̶��, �浹 ���������ش�.
						pLeftCol->OnCollisionExit(pRightCol);
						pRightCol->OnCollisionExit(pLeftCol);
						iter->second = false;
					

					}
					else
					{
						pLeftCol->OnCollision(pRightCol);
						pRightCol->OnCollision(pLeftCol);
					}

				}
				else
				{
					if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
					{
						// �ٵ� ���� �ϳ��� ���� �����̶��, �浹���� ���������� ���
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}
				}
			}
			else
			{
				// ���� �浹�ϰ� ���� �ʴ�.
				if (iter->second)
				{
					// ����� �浹���������� �������� �浹�ϰ� �־���.
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;

				}
			}
		}
	}
}

bool CCollisionMgr::IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{
	Vec2 vLeftPos = _pLeftCol->GetfinalPos();
	Vec2 vLeftScale = _pLeftCol->GetScale();

	Vec2 vRightPos = _pRightCol->GetfinalPos();
	Vec2 vRightScale = _pRightCol->GetScale();

	if (abs(vRightPos.x - vLeftPos.x) <= (vLeftScale.x + vRightScale.x) / 2.f 
		&& abs(vRightPos.y - vLeftPos.y) <= (vLeftScale.y + vRightScale.y) / 2.f)
	{
		return true;
	}

	return false;
}


