#pragma once


// CPointNum �Ի���

class CPointNum : public CDialogEx
{
	DECLARE_DYNAMIC(CPointNum)

public:
	CPointNum(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPointNum();

// �Ի�������
	enum { IDD = IDD_PointNum };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	// ��ĸ���
	int NumOfPoint;
	afx_msg void OnBnClickedOk();
};
