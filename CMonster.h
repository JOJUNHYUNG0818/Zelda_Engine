#pragma once
#include "CObject.h"

struct tMonInfo
{
    float     fHP;        // 체력
    float     fSpeed;     // 속도
    float     fRecogRange;// 인지 범위
    float     fAttRange;  // 공격 범위
    float     fAtt;       // 공격력

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

