#pragma once
#include "afxwin.h"


// CDetailDialog �Ի���

class CDetailDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CDetailDialog)

public:
	CDetailDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDetailDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_bound;
	CEdit m_freq;
	CEdit m_height;
	CEdit longitude;
	CEdit latitude;
	CEdit m_ratio;
	CEdit m_power;
private:
	//CString getContent(CEdit* pEdit);

public:
	//void getValueFromEdit();
	afx_msg void OnBnClickedOk();
	//CString  Strlongitude,  Strlatitude, Strm_height, Strm_power,Strm_bound, Strm_freq, Strm_ratio;
	//pEdit->GetWindowText(str);
	//double lo,la,h,p,b,f,r;
	afx_msg void OnEnChangeEdit5();
	// ����վ�㾭��
	double Longitude;
	// ����վ��γ��
	double Latitude;
	// ���߸߶�
	double AntennaHeight;
	// ���������
	double Power;
	// Ƶ��
	double Frequentcy;
	// ����
	double BandWidth;
	// ������
	double DataRate;
	afx_msg void OnBnClickedCancel();
};
