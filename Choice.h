#pragma once


// CChoice �Ի���

class CChoice : public CDialogEx
{
	DECLARE_DYNAMIC(CChoice)

public:
	CChoice(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChoice();

// �Ի�������
	enum { IDD = IDD_CHOICE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo1();
	// ��״ѡ��
	CString Choice;
	afx_msg void OnBnClickedOk();
};
