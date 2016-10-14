#pragma once
#include "MFC_UI.h"
#include "afxwin.h"
class MFC_UI;

// CPage_Advanced 对话框

class CPage_Advanced : public CPropertyPage
{
	DECLARE_DYNAMIC(CPage_Advanced)

public:
	//CPage_Advanced();
	CPage_Advanced(MFC_UI *pUI);
	virtual ~CPage_Advanced();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_ADVANCED };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


private:
	/**
	* @brief 主界面
	* @see  MFC_UI::DisplayTWAINGUI()
	* @note 从外部接收值
	*/
	MFC_UI  *m_pUI; 
private:

	    
	/**
	* @brief 纸张大小: US Letter/US Legal/A4/A5  
	* @see CTWAINDS_FreeIMage.cpp Line 606
	*/
	CComboBox m_combo_standardsizes;  

	/**
	* @brief 纸张方向: 纵向/横向  
	* @see CTWAINDS_FreeIMage.cpp Line 615
	*/
	CComboBox m_combo_orientation;

	CComboBox m_combo_uints;  ///<　单位

	CEdit m_edit_custom_width;  ///< 纸张大小，自定义宽度
	CEdit m_edit_custom_height;  ///< 纸张大小，自定义高度

private:
	void UpdateControls(void);  ///< 更新控件状态

private:
	virtual BOOL OnInitDialog();
	
	afx_msg void OnCbnSelchangeAdvanced_Combo_Standardsizes();
	afx_msg void OnCbnSelchangeAdvanced_Combo_Orientation();
	afx_msg void OnCbnSelchangeAdvanced_Combo_Uints();

	/*afx_msg void OnEnChangeAdvanced_Edit_Customwidth();
	afx_msg void OnEnChangeAdvanced_Edit_Customheight();*/
};
