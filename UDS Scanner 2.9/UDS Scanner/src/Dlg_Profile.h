#pragma once
#include "afxwin.h"

/**
* @file   Dlg_Profile.h
* @brief 新建模版对话框类
* @author UDS
* @par   Copyright (c) 2016 UDS.
*         All Rights Reserved.
* @date   2016/9/26 
*/ 
// CDlg_Profile 对话框


class CDlg_Profile : public CDialog
{
	DECLARE_DYNAMIC(CDlg_Profile)

public:
	CDlg_Profile(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlg_Profile();

// 对话框数据
	enum { IDD = IDD_DLG_PROFILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	CEdit m_edit_profile;

//private:
//	CDlg_Profile *m_ui;

public:
	CString GetProfileName();  ///< 获取模版名
	BOOL m_bOk;		///< 判断是否点击确定按钮

private:
	CString m_strProfileName;  ///< 当前模版名
	virtual BOOL OnInitDialog();
	
	virtual void OnOK();
};
