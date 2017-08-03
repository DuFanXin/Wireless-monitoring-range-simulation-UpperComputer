#pragma once
#include "afxwin.h"


// CDialog3Detail 对话框

class CDialog3Detail : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog3Detail)

public:
	CDialog3Detail(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialog3Detail();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double AntennaHeight;//天线高度
	double Power;//发射机功率
	double Frequentcy;//频率
	double BandWidth;//带宽
	double DataRate;//比特率
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCheck1();
	int StationNum;
	CEdit NumEdit;
};
