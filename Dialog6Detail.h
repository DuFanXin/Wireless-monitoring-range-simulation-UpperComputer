#pragma once
#include "afxwin.h"


// Dialog6Detail �Ի���

class Dialog6Detail : public CDialogEx
{
	DECLARE_DYNAMIC(Dialog6Detail)

public:
	Dialog6Detail(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Dialog6Detail();

// �Ի�������
	enum { IDD = IDD_DIALOG6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	double LeftUpLongitude;
	double LeftUpLatitude;
	double RightUpLongitude;
	double RightUpLatitude;
	double LeftDownLongitude;
	double LeftDownLatitude;
	double RightDownLongitude;
	double RightDownLatitude;
};
