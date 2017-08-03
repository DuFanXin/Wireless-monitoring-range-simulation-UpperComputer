// PointNum.cpp : 实现文件
//

#include "stdafx.h"
#include "radio.h"
#include "PointNum.h"
#include "afxdialogex.h"


// CPointNum 对话框

IMPLEMENT_DYNAMIC(CPointNum, CDialogEx)

CPointNum::CPointNum(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPointNum::IDD, pParent)
	, NumOfPoint(0)
{

}

CPointNum::~CPointNum()
{
}

void CPointNum::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, NumOfPoint);
}


BEGIN_MESSAGE_MAP(CPointNum, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &CPointNum::OnEnChangeEdit1)
	ON_BN_CLICKED(IDOK, &CPointNum::OnBnClickedOk)
END_MESSAGE_MAP()


// CPointNum 消息处理程序


void CPointNum::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CPointNum::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	CDialogEx::OnOK();
}
