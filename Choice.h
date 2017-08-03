#pragma once


// CChoice 对话框

class CChoice : public CDialogEx
{
	DECLARE_DYNAMIC(CChoice)

public:
	CChoice(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChoice();

// 对话框数据
	enum { IDD = IDD_CHOICE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo1();
	// 形状选择
	CString Choice;
	afx_msg void OnBnClickedOk();
};
