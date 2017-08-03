// Dialog4Detail.cpp : 实现文件
//
#include "stdafx.h"
#include "radio.h"
#include "Dialog4Detail.h"
#include "afxdialogex.h"

// CDialog4Detail 对话框

IMPLEMENT_DYNAMIC(CDialog4Detail, CDialogEx)

CDialog4Detail::CDialog4Detail(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialog4Detail::IDD, pParent)
{
}

CDialog4Detail::~CDialog4Detail()
{
}

BOOL CDialog4Detail::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	m_shape.AddString(_T("圆形"));
	m_shape.AddString(_T("矩形"));
	m_shape.AddString(_T("多边形"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
void CDialog4Detail::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_shape);
}

BEGIN_MESSAGE_MAP(CDialog4Detail, CDialogEx)
	//ON_CBN_SELCHANGE(IDC_COMBO1, &CDialog4Detail::OnCbnSelchangeCombo1)
	//ON_BN_CLICKED(IDOK, &CDialog4Detail::OnBnClickedOk)
	ON_CBN_DROPDOWN(IDC_COMBO1, &CDialog4Detail::OnDropdownCombo1)
END_MESSAGE_MAP()

void CDialog4Detail::OnCbnSelchangeCombo1()
{
	CString str;
	int index;
    index = m_shape.GetCurSel(); 
	m_shape.GetLBText(index, str);  
	if(str=="圆形")
	{
	
	}
}

void CDialog4Detail::OnDropdownCombo1()
{
}



