#pragma once
#include "MFC_UI.h"
#include "afxwin.h"
#include "Dlg_Profile.h"

class MFC_UI;
// CPage_Base �Ի���

class CPage_Base : public CPropertyPage
{
	DECLARE_DYNAMIC(CPage_Base)

public:
	///< ���ع��캯��������β�MFC_UI *pUI
	CPage_Base(MFC_UI *pUI);
	virtual ~CPage_Base();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_BASE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnOK();
	virtual void OnCancel();

private:
	/**
	* @brief �ڹ��캯���г�ʼ�� 
	* @see  CPage_Base(MFC_UI *pUI)
	*/
	MFC_UI  *m_pUI;  

private:
	void UpdateControls(void);  ///< ���¿ؼ�״̬
	void InitSliderCtrl();  ///< ��ʼ���������ؼ�
	void InitComboProfile();  ///< ��ʼ��ģ��Combo
	void LoadProfile();  ///< ����ģ��


private:
	CComboBox m_combo_source;   ///< ɨ�跽ʽ:  ADF/Flatbed
	CComboBox m_combo_colormode;  ///< ͼ������:  �ڰ�/�Ҷ�/��ɫ
	CComboBox m_combo_resolution;  ///< �ֱ���:  50/100/200/.../600
	CComboBox m_combo_profile;  ///< ģ��
	/**
	* @brief ����/˫��ɨ:  ����/˫��  
	* @see CTWAINDS_FreeIMage.cpp Line 675
	*/
	CComboBox m_combo_scanside;

	CSliderCtrl m_slider_contrast;  ///< �Աȶ�:  -100~+100
	CSliderCtrl m_slider_brightness;  ///< ����:  -100~+100

	CEdit m_edit_contrast;  ///< ����ͬ����ʾm_slider_contrastֵ
	CEdit m_edit_brightness;   ///< ����ͬ����ʾm_slider_brightnessֵ

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

