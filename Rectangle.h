#pragma once


// CRectangle �Ի���

class CRectangle : public CDialogEx
{
	DECLARE_DYNAMIC(CRectangle)

public:
	CRectangle(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRectangle();

// �Ի�������
	enum { IDD = IDD_RECTANGLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	// �������ϽǾ���
	double LURectLong;
	// �������Ͻ�γ��
	double UPRectLati;
	// �������ϽǾ���
	double RURectLong;
	// �������Ͻ�γ��
	double RURectLati;
	// �������½Ǿ���
	double LDRectLong;
	// �������½�γ��
	double LDRectLati;
	// �������½Ǿ���
	double RDRectLong;
	// �������½�γ��
	double RDRectLati;
};
