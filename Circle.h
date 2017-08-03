#pragma once


// CCircle 对话框

class CCircle : public CDialogEx
{
	DECLARE_DYNAMIC(CCircle)

public:
	CCircle(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCircle();

// 对话框数据
	enum { IDD = IDD_CIRCLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 圆形经度
	double CircLong;
	// 圆形纬度
	double CircLati;
	// 覆盖半径
	double CircRadius;
	afx_msg void OnBnClickedOk();
};
