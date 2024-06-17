#pragma once
#include "pch.h"

class CMonster;

enum class MON_TYPE
{
	NOMAL,
	RANGE,
	
};

class CMonFactory
{
public:
	static CMonster* CreateMonster(MON_TYPE _eType, Vec2 _vPos);



private:
	CMonFactory() {}
	~CMonFactory() {}



};

