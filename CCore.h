#pragma once

// 싱글톤 패턴
// 객체의 생성을 1개로 제한
// 어디서든 쉽게 접근 가능

// static 정적 멤버함수, 객체없이 호출 가능, this 가 없다.(멤버 접근 불가)
// 정적멤버는 접근 가능 ex) static int = m_iStatic;

//class CCore
//{
//
//private:
//	static CCore* g_pInst;
//
//public:
//	// 정적 멤버함수
//	static CCore* GetInstance()
//	{	 	
//		// 최초 호출 된 경우
//		if (nullptr == g_pInst)
//		{
//			g_pInst = new CCore;
//		}
//		// 두번 이상 호출 된 경우
//		return g_pInst;
//	}
//
//	static void Release()
//	{
//		if (nullptr != g_pInst)
//		{
//			delete g_pInst;
//			g_pInst = nullptr;
//		}
//	}
//
//private:
//	CCore();
//	~CCore();
//
//};
class Texture;

#include"define.h"
#include"pch.h"

class CCore
{
	SINGLE(CCore);

private:
	HWND m_hWnd;          // 메인 윈도우 핸들
	POINT m_ptResolution; // 메인 윈도우 해상도
	HDC  m_hDC;           // 메인 윈도우에 Draw 할 DC

	CTexture* m_pMemTex;  // 백버퍼 텍스쳐

	// 자주 사용하는 GDI object
	HBRUSH m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN   m_arrPen[(UINT)PEN_TYPE::END];

	// 메뉴
	HMENU   m_hMenu; // Tool Scene 에서만 사용



public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();
	

private:
	void Clear();
	void CreateBrushPen();

public:
	void DockMenu();
	void DividMenu();
	void ChangeWindowSize(Vec2 _vResolution, bool _bMenu);

public:
	HWND GetmainHwnd() { return m_hWnd; }
	POINT GetResolution() { return m_ptResolution; }
	HDC GetMainDC() { return m_hDC; }
	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN   GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }
	
};
