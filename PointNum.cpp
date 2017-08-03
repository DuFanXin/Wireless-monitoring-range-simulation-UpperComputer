// PointNum.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "radio.h"
#include "PointNum.h"
#include "afxdialogex.h"


// CPointNum �Ի���

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


// CPointNum ��Ϣ�������


void CPointNum::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CPointNum::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	CDialogEx::OnOK();
}
