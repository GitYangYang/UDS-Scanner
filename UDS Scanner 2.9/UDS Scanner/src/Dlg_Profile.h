#pragma once
#include "afxwin.h"

/**
* @file   Dlg_Profile.h
* @brief �½�ģ��Ի�����
* @author UDS
* @par   Copyright (c) 2016 UDS.
*         All Rights Reserved.
* @date   2016/9/26 
*/ 
// CDlg_Profile �Ի���


class CDlg_Profile : public CDialog
{
	DECLARE_DYNAMIC(CDlg_Profile)

public:
	CDlg_Profile(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlg_Profile();

// �Ի�������
	enum { IDD = IDD_DLG_PROFILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	CEdit m_edit_profile;

//private:
//	CDlg_Profile *m_ui;

public:
	CString GetProfileName();  ///< ��ȡģ����
	BOOL m_bOk;		///< �ж��Ƿ���ȷ����ť

private:
	CString m_strProfileName;  ///< ��ǰģ����
	virtual BOOL OnInitDialog();
	
	virtual void OnOK();
};
