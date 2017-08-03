// Rectangle.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "radio.h"
#include "Rectangle.h"
#include "afxdialogex.h"


// CRectangle �Ի���

IMPLEMENT_DYNAMIC(CRectangle, CDialogEx)

CRectangle::CRectangle(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRectangle::IDD, pParent)
	, LURectLong(73.1611)
	, UPRectLati(51.7756)
	, RURectLong(73.1611)
	, RURectLati(51.7756)
	, LDRectLong(73.1611)
	, LDRectLati(51.7756)
	, RDRectLong(73.1611)
	, RDRectLati(51.7756)
{

}

CRectangle::~CRectangle()
{
}

void CRectangle::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT5, LURectLong);
	DDX_Text(pDX, IDC_EDIT6, UPRectLati);
	DDX_Text(pDX, IDC_EDIT7, RURectLong);
	DDX_Text(pDX, IDC_EDIT8, RURectLati);
	DDX_Text(pDX, IDC_EDIT9, LDRectLong);
	DDX_Text(pDX, IDC_EDIT10, LDRectLati);
	DDX_Text(pDX, IDC_EDIT11, RDRectLong);
	DDX_Text(pDX, IDC_EDIT12, RDRectLati);
}


BEGIN_MESSAGE_MAP(CRectangle, CDialogEx)
	ON_BN_CLICKED(IDOK, &CRectangle::OnBnClickedOk)
END_MESSAGE_MAP()


// CRectangle ��Ϣ�������


void CRectangle::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	CDialogEx::OnOK();
}
