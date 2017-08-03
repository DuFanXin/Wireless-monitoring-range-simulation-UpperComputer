// Dialog5Detail.cpp : 实现文件
//

#include "stdafx.h"
#include "radio.h"
#include "Dialog5Detail.h"
#include "afxdialogex.h"


// CDialog5Detail 对话框

IMPLEMENT_DYNAMIC(CDialog5Detail, CDialogEx)

CDialog5Detail::CDialog5Detail(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialog5Detail::IDD, pParent)
	, longtitude(0)
	, latitude(0)
	, radius(0)
{

}

CDialog5Detail::~CDialog5Detail()
{
}

void CDialog5Detail::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT5, longtitude);
	DDX_Text(pDX, IDC_EDIT1, latitude);
	DDX_Text(pDX, IDC_EDIT6, radius);
}


BEGIN_MESSAGE_MAP(CDialog5Detail, CDialogEx)
END_MESSAGE_MAP()


// CDialog5Detail 消息处理程序
