//#pragma once
#include "stdafx.h"
#include "CTWAINDS_FreeImage.h"

#ifndef __MFC_UI_H__
#define __MFC_UI_H__

#include "TWAIN_UI.h"
//#include "Dlg_UI.h"

class CSheet_Scanner;

/**
* @file   MFC_UI.h
* @brief This is a brief description.
* @author UDS
* @par   Copyright (c) 2016 UDS.
*         All Rights Reserved.
* @date   2016/9/12 
* @note   matters needing attention
* @version <version  number>
*/ 
class MFC_UI : public CTWAIN_UI
{
public:


	MFC_UI(CTWAINDS_FreeImage *pDS);
	~MFC_UI(void);

public:
	
	/**
	* Will show the TWAIN GUI
	* @param[in] _pData contains info about if the UI should be shown etc.
	* @return a valid TWRC_xxxx return code.
	*/
	TW_INT16 DisplayTWAINGUI(TW_USERINTERFACE Data, bool bSetup, bool bIndicators);

	/**
	* Close the user interface for TWAIN
	*/
	void DestroyTWAINGUI();
	void UpdateProgress(bool bShow, unsigned char ucProgress, unsigned int unPageNo, string strProgressTitle);
	unsigned int MessageBox(string strMessage,string strTitle, unsigned int unIconID);
	bool processEvent(pTW_EVENT _pEvent);

public:

	//CDlg_UI *m_pDlg;  
  CSheet_Scanner *m_pSheet;  ///< ÊôÐÔÒ³¶Ô»°¿ò

};

#endif // __MFC_UI_H__