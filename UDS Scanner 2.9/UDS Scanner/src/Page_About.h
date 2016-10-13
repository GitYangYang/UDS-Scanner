#pragma once


// CPage_About 对话框

class CPage_About : public CPropertyPage
{
	DECLARE_DYNAMIC(CPage_About)

public:
	CPage_About();
	virtual ~CPage_About();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_ABOUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
