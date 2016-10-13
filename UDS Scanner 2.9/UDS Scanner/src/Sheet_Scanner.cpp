// Sheet_Scanner.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UDS Scanner.h"
#include "Sheet_Scanner.h"


// CSheet_Scanner

IMPLEMENT_DYNAMIC(CSheet_Scanner, CPropertySheet)

CSheet_Scanner::CSheet_Scanner(MFC_UI* pUI, UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:m_pUI(pUI),CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	/**
	* �����Ա����������ҳ.
	*/	
	m_p_page_base = new CPage_Base(pUI);
	AddPage(m_p_page_base);

	m_p_page_advanced = new CPage_Advanced(pUI);
	AddPage(m_p_page_advanced);

	AddPage(&m_page_about);
	
}

CSheet_Scanner::CSheet_Scanner(MFC_UI* pUI, LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:m_pUI(pUI),CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	/**
	* �����Ա����������ҳ.
	*/
	m_p_page_base = new CPage_Base(pUI);
	AddPage(m_p_page_base);

	m_p_page_advanced = new CPage_Advanced(pUI);
	AddPage(m_p_page_advanced);

	AddPage(&m_page_about);
	
}

CSheet_Scanner::~CSheet_Scanner()
{
	if (m_p_page_base)
	{
		delete m_p_page_base;
		m_p_page_base = NULL;
	}

	if (m_p_page_advanced)
	{
		delete m_p_page_advanced;
		m_p_page_advanced = NULL;
	}
}


BEGIN_MESSAGE_MAP(CSheet_Scanner, CPropertySheet)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CSheet_Scanner ��Ϣ�������


void CSheet_Scanner::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	/*AfxMessageBox("Close");
	Sleep(3000);
	DestroyUI(m_pUI);
	CPropertySheet::OnClose();
	m_pUI->Cancel();*/
	//return;
}


void CSheet_Scanner::OnDestroy()
{
	CPropertySheet::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	///< ��������ǰ����
	//m_pUI->Cancel();
	
}


BOOL CSheet_Scanner::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	// TODO:  �ڴ��������ר�ô���

	if(m_pUI->m_bSetup)  ///< EnableDSUIOnly��ֻ���������棩�����İ�ť����Ϊ�����桱
	{
		GetDlgItem(IDOK)->SetWindowText("����");
	}
	else
	{
		GetDlgItem(IDOK)->SetWindowText("ɨ��");
	}
	return bResult;
}
