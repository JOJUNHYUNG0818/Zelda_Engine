#pragma once
#include "CObject.h"

struct tMonInfo
{
    float     fHP;        // ü��
    float     fSpeed;     // �ӵ�
    float     fRecogRange;// ���� ����
    float     fAttRange;  // ���� ����
    float     fAtt;       // ���ݷ�

};




class AI;

class CMonster :
    public CObject
{
private:

    AI*         m_pAI;
    tMonInfo    m_tInfo;


public:
    float GetSpeed() { return m_tInfo.fSpeed; }
    void SetSpeed(float _f) { m_tInfo.fSpeed = _f; }
    void SetAI(AI* _AI);
    const tMonInfo& GetInfo() { return m_tInfo; }

private:
    void SetMonInfo(const tMonInfo& _info) { m_tInfo = _info;}


public:
    virtual void OnCollisionEnter(CCollider* _pOther);

public:
    virtual void update();

    CLONE(CMonster);

public:
    CMonster();
    ~CMonster();
    

    friend class CMonFactory;
};

