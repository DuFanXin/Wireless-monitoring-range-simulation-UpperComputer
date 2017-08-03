#pragma once
#include "afxwin.h"


// CIrregular 对话框

class CIrregular : public CDialogEx
{
	DECLARE_DYNAMIC(CIrregular)

public:
	CIrregular(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CIrregular();

// 对话框数据
	enum { IDD = IDD_IRREGULAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 第一个点的经度
	double Point1Long;
	// 第一个点的纬度
	double Point1Lati;
	// 第二个点的经度
	double Point2Long;
	// 第二个点的纬度
	double Point2Lati;
	// 第三个点的经度
	double Point3Long;
	// 第三个点的纬度
	double Point3Lati;
	// 第四个点的经度
	double Point4Long;
	// 第四个点的纬度
	double Point4Lati;
	// 第五个点的经度
	double Point5Long;
	// 第五个点的纬度
	double Point5Lati;
	// 第六个点的经度
	double Point6Long;
	// 第六个点的纬度
	double Point6Lati;
	// 第七个点的经度
	double Point7Long;
	// 第七个点的纬度
	double Point7Lati;
	// 第八个点的经度
	double Point8Long;
	// 第八个点的纬度
	double Point8Lati;
	// 第九个点的经度
	double Point9Long;
	// 第九个点的纬度
	double Point9Lati;
	// 第十个点的经度
	double Point10Long;
	// 第十个点的纬度
	double Point10Lati;
	// 第十一个点的经度
	double Point11Long;
	// 第十一个点的纬度
	double Point11Lati;
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck6();
	afx_msg void OnBnClickedCheck10();
	CEdit P1Lo;
	CEdit P1La;
	CEdit P2Lo;
	CEdit P2La;
	CEdit P3Lo;
	CEdit P3La;
	CEdit P4Lo;
	CEdit P4La;
	CEdit P5Lo;
	CEdit P5La;
	CEdit P6Lo;
	CEdit P6La;
	CEdit P7Lo;
	CEdit P7La;
	CEdit P8Lo;
	CEdit P8La;
	CEdit P9Lo;
	CEdit P9La;
	CEdit P10Lo;
	CEdit P10La;
	CEdit P11Lo;
	CEdit P11La;
	int PointNum;
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnBnClickedCheck5();
	afx_msg void OnBnClickedCheck7();
	afx_msg void OnBnClickedCheck8();
	afx_msg void OnBnClickedCheck9();
	afx_msg void OnBnClickedCheck11();
};
