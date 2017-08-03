// DialogParam.cpp : 实现文件
//

#include "stdafx.h"
#include "radio.h"
#include "DialogParam.h"
#include "afxdialogex.h"


// DialogParam 对话框

IMPLEMENT_DYNAMIC(DialogParam, CDialogEx)

DialogParam::DialogParam(CWnd* pParent /*=NULL*/)
	: CDialogEx(DialogParam::IDD, pParent)
{
	m_val = -1;
}

DialogParam::~DialogParam()
{
}

void DialogParam::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
}


BEGIN_MESSAGE_MAP(DialogParam, CDialogEx)
	ON_BN_CLICKED(IDOK, &DialogParam::OnBnClickedOk)
END_MESSAGE_MAP()


// DialogParam 消息处理程序

int DialogParam::getInput() {
	return m_val;
}




void DialogParam::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	m_edit.GetWindowText(str);
	m_val = _ttoi(str);
	CDialogEx::OnOK();
}
