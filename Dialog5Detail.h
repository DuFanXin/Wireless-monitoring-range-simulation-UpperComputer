#pragma once


// CDialog5Detail 对话框

class CDialog5Detail : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog5Detail)

public:
	CDialog5Detail(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialog5Detail();

// 对话框数据
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double longtitude;
	double latitude;
	double radius;
};
