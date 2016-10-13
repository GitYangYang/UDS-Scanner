#pragma once
#include "MFC_UI.h"
#include "afxwin.h"
#include "Dlg_Profile.h"

class MFC_UI;
// CPage_Base 对话框

class CPage_Base : public CPropertyPage
{
	DECLARE_DYNAMIC(CPage_Base)

public:
	///< 重载构造函数，添加形参MFC_UI *pUI
	CPage_Base(MFC_UI *pUI);
	virtual ~CPage_Base();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_BASE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnOK();
	virtual void OnCancel();

private:
	/**
	* @brief 在构造函数中初始化 
	* @see  CPage_Base(MFC_UI *pUI)
	*/
	MFC_UI  *m_pUI;  

private:
	void UpdateControls(void);  ///< 更新控件状态
	void InitSliderCtrl();  ///< 初始化滑动条控件
	void InitComboProfile();  ///< 初始化模版Combo
	void LoadProfile();  ///< 加载模版


private:
	CComboBox m_combo_source;   ///< 扫描方式:  ADF/Flatbed
	CComboBox m_combo_colormode;  ///< 图像类型:  黑白/灰度/彩色
	CComboBox m_combo_resolution;  ///< 分辨率:  50/100/200/.../600
	CComboBox m_combo_profile;  ///< 模版
	/**
	* @brief 单面/双面扫:  单面/双面  
	* @see CTWAINDS_FreeIMage.cpp Line 675
	*/
	CComboBox m_combo_scanside;

	CSliderCtrl m_slider_contrast;  ///< 对比度:  -100~+100
	CSliderCtrl m_slider_brightness;  ///< 亮度:  -100~+100

	CEdit m_edit_contrast;  ///< 用于同步显示m_slider_contrast值
	CEdit m_edit_brightness;   ///< 用于同步显示m_slider_brightness值

	//CDlg_Profile *m_pDlg;

	virtual BOOL OnInitDialog();
	//virtual BOOL OnApply();
	
	afx_msg void OnNMCustomdrawBase_Slider_Contrast(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawBase_Slider_Brightness(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnEnChangeBase_Edit_Contrast();
	afx_msg void OnEnChangeBase_Edit_Brightness();

	afx_msg void OnCbnSelchangeBase_Combo_Source();
	afx_msg void OnCbnSelchangeBase_Combo_Colormode();
	afx_msg void OnCbnSelchangeBase_Combo_Resolution();
	afx_msg void OnCbnSelchangeBase_Combo_Profile();
	afx_msg void OnCbnSelchangeBase_Combo_Scanside();

	afx_msg void OnBase_Btn_Newprofile();
	afx_msg void OnBase_Btn_Deleteprofile();

};

