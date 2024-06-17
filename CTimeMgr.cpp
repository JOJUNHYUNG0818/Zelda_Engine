#include "pch.h"
#include "CTimeMgr.h"
#include "CCore.h"


CTimeMgr::CTimeMgr()
	: m_lICurCount{}
	, m_lIPrevCount{}
	, m_lIFrequency{}
	, m_dDT(0.)
	, m_dAcc(0.)
	, m_iCallCount(0)
{

}


CTimeMgr::~CTimeMgr()
{

}




void CTimeMgr::init()
{
	// 현재 카운트
	QueryPerformanceCounter(&m_lIPrevCount);

	// 초당 카운트 횟수
	QueryPerformanceFrequency(&m_lIFrequency);

}

void CTimeMgr::update()
{
	// 업데이트마다 생성된 카운트수
	QueryPerformanceCounter(&m_lICurCount);

	// 이전 프레임의 카운팅과 현재 프레임 카운팅 값의 차이를 구한다.
	m_dDT = (double)(m_lICurCount.QuadPart - m_lIPrevCount.QuadPart) / (double)m_lIFrequency.QuadPart;

	// = 1. / m_dDt; = FPS

	// 이전 카운트 값을 현재 값으로 갱신(다음번에 계산을 위해서)
	m_lIPrevCount = m_lICurCount;

#ifdef _DEBUG
	if (m_dDT > (1. / 60.))
		m_dDT = (1. / 60.);
#endif 

}

void CTimeMgr::render()
{
	++m_iCallCount;

	m_dAcc += m_dDT; // DT 누적 = 흘러간시간

	if (m_dAcc >= 1.)  // 1초에 한번씩 확인하는 문
	{
		m_iFPS = m_iCallCount;
		m_dAcc = 0;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d, DT : %f", m_iFPS, m_dDT);
		SetWindowText(CCore::GetInst()->GetmainHwnd(), szBuffer);
	}
}
