// Choice.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "radio.h"
#include "Choice.h"
#include "afxdialogex.h"


// CChoice �Ի���

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


// CChoice ��Ϣ�������


void CChoice::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CChoice::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	CDialogEx::OnOK();
}
