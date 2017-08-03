// Dialog6Detail.cpp : 实现文件
//

#include "stdafx.h"
#include "radio.h"
#include "Dialog6Detail.h"
#include "afxdialogex.h"


// Dialog6Detail 对话框

IMPLEMENT_DYNAMIC(Dialog6Detail, CDialogEx)

Dialog6Detail::Dialog6Detail(CWnd* pParent /*=NULL*/)
	: CDialogEx(Dialog6Detail::IDD, pParent)
	, LeftUpLongitude(0)
	, LeftUpLatitude(0)
	, RightUpLongitude(0)
	, RightUpLatitude(0)
	, LeftDownLongitude(0)
	, LeftDownLatitude(0)
	, RightDownLongitude(0)
	, RightDownLatitude(0)
{

}

Dialog6Detail::~Dialog6Detail()
{
}

void Dialog6Detail::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT5, LeftUpLongitude);
	DDX_Text(pDX, IDC_EDIT6, LeftUpLatitude);
	DDX_Text(pDX, IDC_EDIT7, RightUpLongitude);
	DDX_Text(pDX, IDC_EDIT8, RightUpLatitude);
	DDX_Text(pDX, IDC_EDIT9, LeftDownLongitude);
	DDX_Text(pDX, IDC_EDIT10, LeftDownLatitude);
	DDX_Text(pDX, IDC_EDIT11, RightDownLongitude);
	DDX_Text(pDX, IDC_EDIT12, RightDownLatitude);
}


BEGIN_MESSAGE_MAP(Dialog6Detail, CDialogEx)
END_MESSAGE_MAP()


// Dialog6Detail 消息处理程序
