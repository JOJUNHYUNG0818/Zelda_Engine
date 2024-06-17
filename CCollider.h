#pragma once


class CObject;

class CCollider
{

private:
	static UINT g_iNextID;
	
	CObject* m_pOwner;      // collider �� �����ϰ� �ִ� ������Ʈ
	Vec2     m_vOffsetPos;  // ������Ʈ�� ���� ������� ��ġ
	Vec2     m_vFinalaPos;  // finalupdate ���� �� �����Ӹ��� ���
	Vec2     m_vScale;      // �浹ü�� ũ��

	UINT     m_iID;         // �浹ü ������ ID ��
	UINT     m_iCol;

	bool     m_bActive;      // �浹ü Ȱ��ȭ ����


public: 
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }

	Vec2 GetfinalPos() { return m_vFinalaPos; }

	UINT GetID() { return m_iID; }

	CObject* GetObj() {return m_pOwner;}
	

public:
	void finalupdate();
	void render(HDC _dc);

public:
	// �浹 ���� �Լ�
	void OnCollision(CCollider* _pOther); // �浹 ���� ��� ȣ��Ǵ� �Լ�
	void OnCollisionEnter(CCollider* _pOther); // �浹 ���� ��
	void OnCollisionExit(CCollider* _pOther); // �浹 ���� ��

	CCollider& operator = (CCollider* _origin) = delete;


public:

	CCollider();
	CCollider(const CCollider& _origin);
	~CCollider();

	friend class CObject;

	
};

