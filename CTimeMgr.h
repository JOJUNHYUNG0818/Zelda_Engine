#pragma once


class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER m_lICurCount;
	LARGE_INTEGER m_lIPrevCount;
	LARGE_INTEGER m_lIFrequency;

	double        m_dDT; // ������ ������ �ð���
	double        m_dAcc;  // 1�� üũ�� ���� ���� �ð�
	UINT          m_iCallCount;// �Լ� ȣ�� ȸ�� üũ
	UINT          m_iFPS; // �ʴ� ȣ�� Ƚ��
	// FPS  �ʴ� ������
	// 1 �����Ӵ� �ð� (Delta Time)    FPS �� ��������

public:
	void init();
	void update();
	void render();

public:
	double GetDT() { return m_dDT; }
	float GetfDT() { return (float)m_dDT; }
};

