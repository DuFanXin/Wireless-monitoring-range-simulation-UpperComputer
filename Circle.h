#pragma once


// CCircle �Ի���

class CCircle : public CDialogEx
{
	DECLARE_DYNAMIC(CCircle)

public:
	CCircle(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCircle();

// �Ի�������
	enum { IDD = IDD_CIRCLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// Բ�ξ���
	double CircLong;
	// Բ��γ��
	double CircLati;
	// ���ǰ뾶
	double CircRadius;
	afx_msg void OnBnClickedOk();
};
