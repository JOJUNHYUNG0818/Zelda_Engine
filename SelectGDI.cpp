#include "pch.h"
#include "SelectGDI.h"
#include "CCore.h"


SelectGDI::SelectGDI(HDC _dc, PEN_TYPE _ePenType)
	: m_hDC(_dc)
	, m_hDefaultPen(nullptr)
	, m_hDefaultBrush(nullptr)
{
	HPEN hPen = CCore::GetInst()->GetPen(_ePenType);
	m_hDefaultPen = (HPEN)SelectObject(_dc, hPen);
}

SelectGDI::SelectGDI(HDC _dc, BRUSH_TYPE _ePenType)
	: m_hDC(_dc)
	, m_hDefaultPen(nullptr)
	, m_hDefaultBrush(nullptr)
{

	HBRUSH hBrush = CCore::GetInst()->GetBrush(_ePenType);
	m_hDefaultBrush = (HBRUSH)SelectObject(_dc, hBrush);
}

SelectGDI::~SelectGDI()
{

	SelectObject(m_hDC, m_hDefaultPen);
	SelectObject(m_hDC, m_hDefaultBrush);
}
