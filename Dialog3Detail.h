#pragma once
#include "afxwin.h"


// CDialog3Detail �Ի���

class CDialog3Detail : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog3Detail)

public:
	CDialog3Detail(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialog3Detail();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	double AntennaHeight;//���߸߶�
	double Power;//���������
	double Frequentcy;//Ƶ��
	double BandWidth;//����
	double DataRate;//������
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCheck1();
	int StationNum;
	CEdit NumEdit;
};
