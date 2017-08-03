#pragma once
#include "afxwin.h"


// Dialog6Detail 对话框

class Dialog6Detail : public CDialogEx
{
	DECLARE_DYNAMIC(Dialog6Detail)

public:
	Dialog6Detail(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Dialog6Detail();

// 对话框数据
	enum { IDD = IDD_DIALOG6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double LeftUpLongitude;
	double LeftUpLatitude;
	double RightUpLongitude;
	double RightUpLatitude;
	double LeftDownLongitude;
	double LeftDownLatitude;
	double RightDownLongitude;
	double RightDownLatitude;
};
