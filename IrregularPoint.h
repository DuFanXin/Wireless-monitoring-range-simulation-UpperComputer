#pragma once


// CIrregularPoint �Ի���

class CIrregularPoint : public CDialogEx
{
	DECLARE_DYNAMIC(CIrregularPoint)

public:
	CIrregularPoint(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CIrregularPoint();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	double IregPointLong;
	double IregPointLati;
	void SetStaticText(int Num);
	afx_msg void OnBnClickedOk();
	afx_msg void OnStnClickedStatic1();
};
