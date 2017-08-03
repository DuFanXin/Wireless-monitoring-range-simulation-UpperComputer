// Dialog3Detail.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "radio.h"
#include "Dialog3Detail.h"
#include "afxdialogex.h"
#include "Dialog4Detail.h"

// CDialog3Detail �Ի���

IMPLEMENT_DYNAMIC(CDialog3Detail, CDialogEx)

CDialog3Detail::CDialog3Detail(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialog3Detail::IDD, pParent)
	, AntennaHeight(5.0)
	, Power(0.05)
	, Frequentcy(1000)
	, BandWidth(10)
	, DataRate(250000)
	, StationNum(0)
{

}

CDialog3Detail::~CDialog3Detail()
{
}

void CDialog3Detail::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, AntennaHeight);
	DDX_Text(pDX, IDC_EDIT7, Power);
	DDX_Text(pDX, IDC_EDIT6, Frequentcy);
	DDX_Text(pDX, IDC_EDIT3, BandWidth);
	DDX_Text(pDX, IDC_EDIT4, DataRate);
	DDX_Text(pDX, IDC_EDIT1, StationNum);
	DDX_Control(pDX, IDC_EDIT1, NumEdit);
}


BEGIN_MESSAGE_MAP(CDialog3Detail, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialog3Detail::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK1, &CDialog3Detail::OnBnClickedCheck1)
END_MESSAGE_MAP()
// CDialog3Detail ��Ϣ�������
void CDialog3Detail::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	CDialogEx::OnOK();
}


void CDialog3Detail::OnBnClickedCheck1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK1);
	int state = pBtn->GetCheck();
	if(state){NumEdit.EnableWindow(true);}
	else{NumEdit.EnableWindow(false);}
}
