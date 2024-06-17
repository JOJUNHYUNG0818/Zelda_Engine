#pragma once
#include "CObject.h"

class CTexture;

class CTile :
    public CObject
{


private:
    CTexture* m_pTileTex;
    int       m_iImgIdx; // 인트로 잡은이유는 -1은 아무것도 사용하지 않겠다는 의미

public:
    void SetTexture(CTexture* _pTex)
    {
        m_pTileTex = _pTex;
    }

    void AddImgIdx()
    {
        ++m_iImgIdx;
    }
private:
    virtual void update();
    virtual void render(HDC _dc);

public:
    virtual void Save(FILE* _pFile);
    virtual void Load(FILE* _pFile);


    CLONE(CTile);
public:
    CTile();
    ~CTile();






};

