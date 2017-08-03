#pragma once
#include "afxwin.h"


// CDialog4Detail 对话框

class CDialog4Detail : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog4Detail)

public:
	CDialog4Detail(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialog4Detail();

// 对话框数据
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_shape;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnDropdownCombo1();
	virtual BOOL OnInitDialog();
};
