#pragma once


// CRectangle 对话框

class CRectangle : public CDialogEx
{
	DECLARE_DYNAMIC(CRectangle)

public:
	CRectangle(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRectangle();

// 对话框数据
	enum { IDD = IDD_RECTANGLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	// 矩形左上角经度
	double LURectLong;
	// 矩形左上角纬度
	double UPRectLati;
	// 矩形右上角经度
	double RURectLong;
	// 矩形右上角纬度
	double RURectLati;
	// 矩形左下角经度
	double LDRectLong;
	// 矩形左下角纬度
	double LDRectLati;
	// 矩形右下角经度
	double RDRectLong;
	// 矩形右下角纬度
	double RDRectLati;
};
