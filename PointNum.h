#pragma once


// CPointNum 对话框

class CPointNum : public CDialogEx
{
	DECLARE_DYNAMIC(CPointNum)

public:
	CPointNum(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPointNum();

// 对话框数据
	enum { IDD = IDD_PointNum };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	// 点的个数
	int NumOfPoint;
	afx_msg void OnBnClickedOk();
};
