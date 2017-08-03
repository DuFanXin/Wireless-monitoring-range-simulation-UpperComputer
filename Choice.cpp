// Choice.cpp : 实现文件
//

#include "stdafx.h"
#include "radio.h"
#include "Choice.h"
#include "afxdialogex.h"


// CChoice 对话框

IMPLEMENT_DYNAMIC(CChoice, CDialogEx)

CChoice::CChoice(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChoice::IDD, pParent)
	, Choice(_T(""))
{

}

CChoice::~CChoice()
{
}

void CChoice::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO1, Choice);
}


BEGIN_MESSAGE_MAP(CChoice, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CChoice::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDOK, &CChoice::OnBnClickedOk)
END_MESSAGE_MAP()


// CChoice 消息处理程序


void CChoice::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CChoice::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	CDialogEx::OnOK();
}
