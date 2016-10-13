#include "MFC_UI.h"
//#include "UDS Scanner.h"
#include "Sheet_Scanner.h"  // 必须放cpp文件中，因为重复包含
/**
* @file   MFC_UI.cpp
* @brief This is a brief description.
* @author UDS
* @par   Copyright (c) 2016 UDS.
*         All Rights Reserved.
* @date   2016/9/12 
* @note   matters needing attention
* @version <version  number>
*/ 
extern HINSTANCE   g_hinstance;
extern HWND   g_hwndDLG;

CTWAIN_UI* CreateUI(CTWAINDS_FreeImage *pDS)
{
	return new MFC_UI(pDS);
}

void DestroyUI(CTWAIN_UI* pUI)
{
	if(pUI)
	{
		delete ((MFC_UI*)pUI);
		//AfxMessageBox("DestroyUI");
	}
}

//MFC_UI* MFC_UI::m_mfcUi = NULL;

//MFC_UI::MFC_UI(void)
//{
//}

MFC_UI::MFC_UI(CTWAINDS_FreeImage *pDS):CTWAIN_UI(pDS)
{
	m_pSheet = NULL;
}


MFC_UI::~MFC_UI(void)
{
	
	if (m_pSheet)
	{
		delete m_pSheet;
		m_pSheet = NULL;		
		//AfxMessageBox("MFC 析构");
	}
}

TW_INT16 MFC_UI::DisplayTWAINGUI(TW_USERINTERFACE Data, bool bSetup, bool bIndicators)
{
	
  TW_INT16 nRes = CTWAIN_UI::DisplayTWAINGUI(Data, bSetup, bIndicators);
	if(nRes)
	{
		return nRes;
	}
	if(bSetup)
	{
		Data.ShowUI=1;
	}

	if(Data.ShowUI==0 && !bIndicators)
	{
		return TWRC_SUCCESS;
	}

	HWND hMainWnd =  (HWND)Data.hParent;
	CWnd *pMainWnd = CWnd::FromHandle(hMainWnd);
	
	if(Data.ShowUI)
	{

		m_pSheet = new CSheet_Scanner(this,IDS_DS_CAPTION);
	
		if (m_pSheet)
		{
			m_pSheet->DoModal();

		} 
		else
		{
			return TWRC_FAILURE;
		}
	
	}
	return TWRC_SUCCESS;

}

void MFC_UI::DestroyTWAINGUI()
{
	CTWAIN_UI::DestroyTWAINGUI();

	/*if(m_pDlg)
	{
		delete m_pDlg;
		m_pDlg = NULL;
	}*/

	if (m_pSheet)
	{
		delete m_pSheet;
		m_pSheet = NULL;	
		//AfxMessageBox("MFC::DestroyTWAINGUI");
	}
	
}


void MFC_UI::UpdateProgress(bool bShow, unsigned char ucProgress, 
	unsigned int unPageNo, string strProgressTitle)
{
	;
}

unsigned int MFC_UI::MessageBox(string strMessage,string strTitle, unsigned int unIconID)
{
	//QMessageBox msgBox(QMessageBox::NoIcon, strTitle.c_str(),strMessage.c_str());
	//return msgBox.exec();
	//return ::MessageBox(m_pDlg->m_hWnd,strMessage.c_str(),strTitle.c_str(),unIconID);
	return ::MessageBox(m_pSheet->m_hWnd,strMessage.c_str(),strTitle.c_str(),unIconID);
	//return 0;
}


bool MFC_UI::processEvent(pTW_EVENT _pEvent)
{
//#ifdef TWNDS_OS_WIN
//	if(qApp)
//	{
//		qApp->sendPostedEvents();
//	}
//#endif
//	return false;
	//？？
	return false;
}


//void MFC_UI::ShowDlg()     
//{     
//
//	hwndDLG = CreateDialog(g_hinstance,MAKEINTRESOURCE(IDD_DLG_SHOW),     
//		NULL,(DLGPROC)DlgProc);     
//	ShowWindow(hwndDLG,   SW_SHOW);     
//
//}

