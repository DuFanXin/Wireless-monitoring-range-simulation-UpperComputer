#pragma once


// CDialog5Detail �Ի���

class CDialog5Detail : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog5Detail)

public:
	CDialog5Detail(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialog5Detail();

// �Ի�������
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	double longtitude;
	double latitude;
	double radius;
};
