// Circle.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "radio.h"
#include "Circle.h"
#include "afxdialogex.h"


// CCircle �Ի���

IMPLEMENT_DYNAMIC(CCircle, CDialogEx)

CCircle::CCircle(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCircle::IDD, pParent)
	, CircLong(73.1611)
	, CircLati(51.7756)
	, CircRadius(8000)
{

}

CCircle::~CCircle()
{
}

void CCircle::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT5, CircLong);
	DDX_Text(pDX, IDC_EDIT1, CircLati);
	DDX_Text(pDX, IDC_EDIT6, CircRadius);
}


BEGIN_MESSAGE_MAP(CCircle, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCircle::OnBnClickedOk)
END_MESSAGE_MAP()


// CCircle ��Ϣ�������


void CCircle::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	CDialogEx::OnOK();
}
