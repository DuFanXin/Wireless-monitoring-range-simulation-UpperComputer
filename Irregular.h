#pragma once
#include "afxwin.h"


// CIrregular �Ի���

class CIrregular : public CDialogEx
{
	DECLARE_DYNAMIC(CIrregular)

public:
	CIrregular(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CIrregular();

// �Ի�������
	enum { IDD = IDD_IRREGULAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ��һ����ľ���
	double Point1Long;
	// ��һ�����γ��
	double Point1Lati;
	// �ڶ�����ľ���
	double Point2Long;
	// �ڶ������γ��
	double Point2Lati;
	// ��������ľ���
	double Point3Long;
	// ���������γ��
	double Point3Lati;
	// ���ĸ���ľ���
	double Point4Long;
	// ���ĸ����γ��
	double Point4Lati;
	// �������ľ���
	double Point5Long;
	// ��������γ��
	double Point5Lati;
	// ��������ľ���
	double Point6Long;
	// ���������γ��
	double Point6Lati;
	// ���߸���ľ���
	double Point7Long;
	// ���߸����γ��
	double Point7Lati;
	// �ڰ˸���ľ���
	double Point8Long;
	// �ڰ˸����γ��
	double Point8Lati;
	// �ھŸ���ľ���
	double Point9Long;
	// �ھŸ����γ��
	double Point9Lati;
	// ��ʮ����ľ���
	double Point10Long;
	// ��ʮ�����γ��
	double Point10Lati;
	// ��ʮһ����ľ���
	double Point11Long;
	// ��ʮһ�����γ��
	double Point11Lati;
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck6();
	afx_msg void OnBnClickedCheck10();
	CEdit P1Lo;
	CEdit P1La;
	CEdit P2Lo;
	CEdit P2La;
	CEdit P3Lo;
	CEdit P3La;
	CEdit P4Lo;
	CEdit P4La;
	CEdit P5Lo;
	CEdit P5La;
	CEdit P6Lo;
	CEdit P6La;
	CEdit P7Lo;
	CEdit P7La;
	CEdit P8Lo;
	CEdit P8La;
	CEdit P9Lo;
	CEdit P9La;
	CEdit P10Lo;
	CEdit P10La;
	CEdit P11Lo;
	CEdit P11La;
	int PointNum;
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnBnClickedCheck5();
	afx_msg void OnBnClickedCheck7();
	afx_msg void OnBnClickedCheck8();
	afx_msg void OnBnClickedCheck9();
	afx_msg void OnBnClickedCheck11();
};
