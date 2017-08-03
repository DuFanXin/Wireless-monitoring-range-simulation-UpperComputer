#pragma once
#include "afxwin.h"


// CDetailDialog 对话框

class CDetailDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CDetailDialog)

public:
	CDetailDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDetailDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_bound;
	CEdit m_freq;
	CEdit m_height;
	CEdit longitude;
	CEdit latitude;
	CEdit m_ratio;
	CEdit m_power;
private:
	//CString getContent(CEdit* pEdit);

public:
	//void getValueFromEdit();
	afx_msg void OnBnClickedOk();
	//CString  Strlongitude,  Strlatitude, Strm_height, Strm_power,Strm_bound, Strm_freq, Strm_ratio;
	//pEdit->GetWindowText(str);
	//double lo,la,h,p,b,f,r;
	afx_msg void OnEnChangeEdit5();
	// 中心站点经度
	double Longitude;
	// 中心站点纬度
	double Latitude;
	// 天线高度
	double AntennaHeight;
	// 发射机功率
	double Power;
	// 频率
	double Frequentcy;
	// 带宽
	double BandWidth;
	// 比特率
	double DataRate;
	afx_msg void OnBnClickedCancel();
};
