// Irregular.cpp : 实现文件
//

#include "stdafx.h"
#include "radio.h"
#include "Irregular.h"
#include "afxdialogex.h"


// CIrregular 对话框

IMPLEMENT_DYNAMIC(CIrregular, CDialogEx)

CIrregular::CIrregular(CWnd* pParent /*=NULL*/)
	: CDialogEx(CIrregular::IDD, pParent)
	, Point1Long(73.1611)
	, Point1Lati(51.7756)
	, Point2Long(73.1611)
	, Point2Lati(51.7756)
	, Point3Long(73.1611)
	, Point3Lati(51.7756)
	, Point4Long(73.1611)
	, Point4Lati(51.7756)
	, Point5Long(73.1611)
	, Point5Lati(51.7756)
	, Point6Long(73.1611)
	, Point6Lati(51.7756)
	, Point7Long(73.1611)
	, Point7Lati(51.7756)
	, Point8Long(73.1611)
	, Point8Lati(51.7756)
	, Point9Long(73.1611)
	, Point9Lati(51.7756)
	, Point10Long(73.1611)
	, Point10Lati(51.7756)
	, Point11Long(73.1611)
	, Point11Lati(51.7756)
	, PointNum(0)
{

}

CIrregular::~CIrregular()
{
}

void CIrregular::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, Point1Long);
	DDX_Text(pDX, IDC_EDIT3, Point1Lati);
	DDX_Text(pDX, IDC_EDIT4, Point2Long);
	DDX_Text(pDX, IDC_EDIT5, Point2Lati);
	DDX_Text(pDX, IDC_EDIT6, Point3Long);
	DDX_Text(pDX, IDC_EDIT7, Point3Lati);
	DDX_Text(pDX, IDC_EDIT8, Point4Long);
	DDX_Text(pDX, IDC_EDIT9, Point4Lati);
	DDX_Text(pDX, IDC_EDIT10, Point5Long);
	DDX_Text(pDX, IDC_EDIT11, Point5Lati);
	DDX_Text(pDX, IDC_EDIT12, Point6Long);
	DDX_Text(pDX, IDC_EDIT13, Point6Lati);
	DDX_Text(pDX, IDC_EDIT14, Point7Long);
	DDX_Text(pDX, IDC_EDIT15, Point7Lati);
	DDX_Text(pDX, IDC_EDIT16, Point8Long);
	DDX_Text(pDX, IDC_EDIT17, Point8Lati);
	DDX_Text(pDX, IDC_EDIT18, Point9Long);
	DDX_Text(pDX, IDC_EDIT19, Point9Lati);
	DDX_Text(pDX, IDC_EDIT20, Point10Long);
	DDX_Text(pDX, IDC_EDIT21, Point10Lati);
	DDX_Text(pDX, IDC_EDIT22, Point11Long);
	DDX_Text(pDX, IDC_EDIT23, Point11Lati);
	DDX_Control(pDX, IDC_EDIT2, P1Lo);
	DDX_Control(pDX, IDC_EDIT3, P1La);
	DDX_Control(pDX, IDC_EDIT4, P2Lo);
	DDX_Control(pDX, IDC_EDIT5, P2La);
	DDX_Control(pDX, IDC_EDIT6, P3Lo);
	DDX_Control(pDX, IDC_EDIT7, P3La);
	DDX_Control(pDX, IDC_EDIT8, P4Lo);
	DDX_Control(pDX, IDC_EDIT9, P4La);
	DDX_Control(pDX, IDC_EDIT10, P5Lo);
	DDX_Control(pDX, IDC_EDIT11, P5La);
	DDX_Control(pDX, IDC_EDIT12, P6Lo);
	DDX_Control(pDX, IDC_EDIT13, P6La);
	DDX_Control(pDX, IDC_EDIT14, P7Lo);
	DDX_Control(pDX, IDC_EDIT15, P7La);
	DDX_Control(pDX, IDC_EDIT16, P8Lo);
	DDX_Control(pDX, IDC_EDIT17, P8La);
	DDX_Control(pDX, IDC_EDIT18, P9Lo);
	DDX_Control(pDX, IDC_EDIT19, P9La);
	DDX_Control(pDX, IDC_EDIT20, P10Lo);
	DDX_Control(pDX, IDC_EDIT21, P10La);
	DDX_Control(pDX, IDC_EDIT22, P11Lo);
	DDX_Control(pDX, IDC_EDIT23, P11La);
}
BEGIN_MESSAGE_MAP(CIrregular, CDialogEx)
	ON_BN_CLICKED(IDOK, &CIrregular::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK1, &CIrregular::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK3, &CIrregular::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK6, &CIrregular::OnBnClickedCheck6)
	ON_BN_CLICKED(IDC_CHECK10, &CIrregular::OnBnClickedCheck10)
	ON_BN_CLICKED(IDC_CHECK2, &CIrregular::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK4, &CIrregular::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_CHECK5, &CIrregular::OnBnClickedCheck5)
	ON_BN_CLICKED(IDC_CHECK7, &CIrregular::OnBnClickedCheck7)
	ON_BN_CLICKED(IDC_CHECK8, &CIrregular::OnBnClickedCheck8)
	ON_BN_CLICKED(IDC_CHECK9, &CIrregular::OnBnClickedCheck9)
	ON_BN_CLICKED(IDC_CHECK11, &CIrregular::OnBnClickedCheck11)
END_MESSAGE_MAP()


void CIrregular::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	CDialogEx::OnOK();
}


void CIrregular::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK1);
	int state = pBtn->GetCheck();
	if(state){P1Lo.EnableWindow(true);P1La.EnableWindow(true);PointNum++;}
	else{P1Lo.EnableWindow(false);P1La.EnableWindow(false);PointNum--;}
}


void CIrregular::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK2);
	int state = pBtn->GetCheck();
	if(state){P2Lo.EnableWindow(true);P2La.EnableWindow(true);PointNum++;}
	else{P2Lo.EnableWindow(false);P2La.EnableWindow(false);PointNum--;}
}


void CIrregular::OnBnClickedCheck3()
{
	// TODO: 在此添加控件通知处理程序代码
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK3);
	int state = pBtn->GetCheck();
	if(state){P3Lo.EnableWindow(true);P3La.EnableWindow(true);PointNum++;}
	else{P3Lo.EnableWindow(false);P3La.EnableWindow(false);PointNum--;}
}


void CIrregular::OnBnClickedCheck4()
{
	// TODO: 在此添加控件通知处理程序代码
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK4);
	int state = pBtn->GetCheck();
	if(state){P4Lo.EnableWindow(true);P4La.EnableWindow(true);PointNum++;}
	else{P4Lo.EnableWindow(false);P4La.EnableWindow(false);PointNum--;}
}


void CIrregular::OnBnClickedCheck5()
{
	// TODO: 在此添加控件通知处理程序代码
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK5);
	int state = pBtn->GetCheck();
	if(state){P5Lo.EnableWindow(true);P5La.EnableWindow(true);PointNum++;}
	else{P5Lo.EnableWindow(false);P5La.EnableWindow(false);PointNum--;}
}


void CIrregular::OnBnClickedCheck6()
{
	// TODO: 在此添加控件通知处理程序代码
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK6);
	int state = pBtn->GetCheck();
	if(state){P6Lo.EnableWindow(true);P6La.EnableWindow(true);PointNum++;}
	else{P6Lo.EnableWindow(false);P6La.EnableWindow(false);PointNum--;}
}


void CIrregular::OnBnClickedCheck7()
{
	// TODO: 在此添加控件通知处理程序代码
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK7);
	int state = pBtn->GetCheck();
	if(state){P7Lo.EnableWindow(true);P7La.EnableWindow(true);PointNum++;}
	else{P7Lo.EnableWindow(false);P7La.EnableWindow(false);PointNum--;}
}


void CIrregular::OnBnClickedCheck8()
{
	// TODO: 在此添加控件通知处理程序代码
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK8);
	int state = pBtn->GetCheck();
	if(state){P8Lo.EnableWindow(true);P8La.EnableWindow(true);PointNum++;}
	else{P8Lo.EnableWindow(false);P8La.EnableWindow(false);PointNum--;}
}


void CIrregular::OnBnClickedCheck9()
{
	// TODO: 在此添加控件通知处理程序代码
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK9);
	int state = pBtn->GetCheck();
	if(state){P9Lo.EnableWindow(true);P9La.EnableWindow(true);PointNum++;}
	else{P9Lo.EnableWindow(false);P9La.EnableWindow(false);PointNum--;}
}


void CIrregular::OnBnClickedCheck10()
{
	// TODO: 在此添加控件通知处理程序代码
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK10);
	int state = pBtn->GetCheck();
	if(state){P10Lo.EnableWindow(true);P10La.EnableWindow(true);PointNum++;}
	else{P10Lo.EnableWindow(false);P10La.EnableWindow(false);PointNum--;}
}


void CIrregular::OnBnClickedCheck11()
{
	// TODO: 在此添加控件通知处理程序代码
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK11);
	//CString a;
	int state = pBtn->GetCheck();
	if(state){P11Lo.EnableWindow(true);P11La.EnableWindow(true);PointNum++;}
	else{P11Lo.EnableWindow(false);P11La.EnableWindow(false);PointNum--;}
	//a.Format(_T("%d"),PointNum);
	//this->GetDlgItem(IDC_STATIC1)->SetWindowTextW(a);

}
