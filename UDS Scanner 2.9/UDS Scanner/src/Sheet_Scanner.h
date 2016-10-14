#pragma once


#include "MFC_UI.h"
#include "Page_About.h"
#include "Page_Base.h"
#include "Page_Advanced.h"

class MFC_UI;
// CSheet_Scanner
class CSheet_Scanner : public CPropertySheet
{
	DECLARE_DYNAMIC(CSheet_Scanner)

public:
	///< 重载构造函数，添加形参MFC_UI *pUI
	CSheet_Scanner(MFC_UI *pUI, UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CSheet_Scanner(MFC_UI *pUI, LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CSheet_Scanner();

protected:
	DECLARE_MESSAGE_MAP()

private:
	MFC_UI *m_pUI;

public:
	CPage_Base *m_p_page_base;
	CPage_Advanced *m_p_page_advanced;
	CPage_About m_page_about;
	
public:
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
};


