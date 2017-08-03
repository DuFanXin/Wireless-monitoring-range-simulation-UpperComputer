// IrregularPoint.cpp : 实现文件
//

#include "stdafx.h"
#include "radio.h"
#include "IrregularPoint.h"
#include "afxdialogex.h"


// CIrregularPoint 对话框

IMPLEMENT_DYNAMIC(CIrregularPoint, CDialogEx)

CIrregularPoint::CIrregularPoint(CWnd* pParent /*=NULL*/)
	: CDialogEx(CIrregularPoint::IDD, pParent)
	, IregPointLong(73.1611)
	, IregPointLati(51.7756)
{
   	
}

CIrregularPoint::~CIrregularPoint()
{
}

void CIrregularPoint::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, IregPointLong);
	DDX_Text(pDX, IDC_EDIT2, IregPointLati);
}


BEGIN_MESSAGE_MAP(CIrregularPoint, CDialogEx)
	ON_BN_CLICKED(IDOK, &CIrregularPoint::OnBnClickedOk)
	ON_STN_CLICKED(IDC_STATIC1, &CIrregularPoint::OnStnClickedStatic1)
END_MESSAGE_MAP()


// CIrregularPoint 消息处理程序


void CIrregularPoint::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	CDialogEx::OnOK();
}

void CIrregularPoint::SetStaticText(int Num)
{
	this->GetDlgItem(IDC_STATIC1)->SetWindowTextW(_T("ds"));
}

void CIrregularPoint::OnStnClickedStatic1()
{
	// TODO: 在此添加控件通知处理程序代码
}
