// Dialog4Detail.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "radio.h"
#include "Dialog4Detail.h"
#include "afxdialogex.h"

// CDialog4Detail �Ի���

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
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_shape.AddString(_T("Բ��"));
	m_shape.AddString(_T("����"));
	m_shape.AddString(_T("�����"));
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
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
	if(str=="Բ��")
	{
	
	}
}

void CDialog4Detail::OnDropdownCombo1()
{
}



