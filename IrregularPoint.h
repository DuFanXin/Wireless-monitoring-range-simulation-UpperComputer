#pragma once


// CIrregularPoint 对话框

class CIrregularPoint : public CDialogEx
{
	DECLARE_DYNAMIC(CIrregularPoint)

public:
	CIrregularPoint(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CIrregularPoint();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double IregPointLong;
	double IregPointLati;
	void SetStaticText(int Num);
	afx_msg void OnBnClickedOk();
	afx_msg void OnStnClickedStatic1();
};
