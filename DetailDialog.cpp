// DetailDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "radio.h"
#include "DetailDialog.h"
#include "afxdialogex.h"
#include <fstream>
#include "iostream"
using namespace std;


// CDetailDialog 对话框

IMPLEMENT_DYNAMIC(CDetailDialog, CDialogEx)

CDetailDialog::CDetailDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDetailDialog::IDD, pParent)
	, Longitude(73.1611)
	, Latitude(51.7756)
	, AntennaHeight(5.0)
	, Power(0.05)
	, Frequentcy(10)
	, BandWidth(1000)
	, DataRate(250000)
{
}
CDetailDialog::~CDetailDialog()
{
}
BEGIN_MESSAGE_MAP(CDetailDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDetailDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDetailDialog::OnBnClickedCancel)
END_MESSAGE_MAP()

void CDetailDialog::OnBnClickedOk()
{
//	::MessageBox(NULL,getContent(&m_bound),_T("带宽"),MB_OK);
//	::MessageBox(NULL,getContent(&m_freq),_T("频率"),MB_OK);
//	::MessageBox(NULL,getContent(&m_height),_T("高度"),MB_OK);
//	::MessageBox(NULL,getContent(&m_ratio),_T("比特率"),MB_OK);
//  ::MessageBox(NULL,getContent(&longitude),_T("经度"),MB_OK);
//	::MessageBox(NULL,getContent(&latitude),_T("纬度"),MB_OK);
//	::MessageBox(NULL,getContent(&m_power),_T("功率"),MB_OK);
//	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	FindBoundary(Longitude,Latitude,AntennaHeight,Power,Frequentcy,BandWidth,DataRate);
	CDialogEx::OnOK();
}

void CDetailDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	/*DDX_Control(pDX, IDC_EDIT3, m_bound);
	DDX_Control(pDX, IDC_EDIT6, m_freq);
	DDX_Control(pDX, IDC_EDIT2, m_height);
	DDX_Control(pDX, IDC_EDIT4, m_ratio);
	DDX_Control(pDX, IDC_EDIT5, longitude);
	DDX_Control(pDX, IDC_EDIT1, latitude);
	DDX_Control(pDX, IDC_EDIT7, m_power);*/
	DDX_Text(pDX, IDC_EDIT5, Longitude);
	DDX_Text(pDX, IDC_EDIT1, Latitude);
	DDX_Text(pDX, IDC_EDIT2, AntennaHeight);
	DDX_Text(pDX, IDC_EDIT7, Power);
	DDX_Text(pDX, IDC_EDIT6, Frequentcy);
	DDX_Text(pDX, IDC_EDIT3, BandWidth);
	DDX_Text(pDX, IDC_EDIT4, DataRate);
}
/*void CDetailDialog::getValueFromEdit() {

	longitude.GetWindowText(Strlongitude);
	latitude.GetWindowText(Strlatitude);
	m_height.GetWindowText(Strm_height);
	m_power.GetWindowText(Strm_power);
	m_bound.GetWindowText(Strm_bound);
	m_freq.GetWindowText(Strm_freq);
	m_ratio.GetWindowText(Strm_ratio);
	lo=_wtof(Strlongitude);
	la=_wtof(Strlatitude);
	h=_wtof(Strm_height);
	p=_wtof(Strm_power);
	b=_wtof(Strm_bound);
	f=_wtof(Strm_freq);
	r=_wtof(Strm_ratio);
	cout<<lo<<la<<h<<p<<b<<f<<r<<endl;
}
*/
/*CString CDetailDialog::getContent(CEdit* pEdit) {
	CString str;
	pEdit->GetWindowText(str);
	return str;
	}
*/
// CDetailDialog 消息处理程序

void CDetailDialog::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
