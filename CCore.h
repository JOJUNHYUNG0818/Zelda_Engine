#pragma once

// �̱��� ����
// ��ü�� ������ 1���� ����
// ��𼭵� ���� ���� ����

// static ���� ����Լ�, ��ü���� ȣ�� ����, this �� ����.(��� ���� �Ұ�)
// ��������� ���� ���� ex) static int = m_iStatic;

//class CCore
//{
//
//private:
//	static CCore* g_pInst;
//
//public:
//	// ���� ����Լ�
//	static CCore* GetInstance()
//	{	 	
//		// ���� ȣ�� �� ���
//		if (nullptr == g_pInst)
//		{
//			g_pInst = new CCore;
//		}
//		// �ι� �̻� ȣ�� �� ���
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
	HWND m_hWnd;          // ���� ������ �ڵ�
	POINT m_ptResolution; // ���� ������ �ػ�
	HDC  m_hDC;           // ���� �����쿡 Draw �� DC

	CTexture* m_pMemTex;  // ����� �ؽ���

	// ���� ����ϴ� GDI object
	HBRUSH m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN   m_arrPen[(UINT)PEN_TYPE::END];

	// �޴�
	HMENU   m_hMenu; // Tool Scene ������ ���



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
