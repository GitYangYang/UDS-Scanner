#pragma once


// CPage_About �Ի���

class CPage_About : public CPropertyPage
{
	DECLARE_DYNAMIC(CPage_About)

public:
	CPage_About();
	virtual ~CPage_About();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_ABOUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
