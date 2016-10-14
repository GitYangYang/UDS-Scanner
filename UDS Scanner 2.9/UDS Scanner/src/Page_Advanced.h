#pragma once
#include "MFC_UI.h"
#include "afxwin.h"
class MFC_UI;

// CPage_Advanced �Ի���

class CPage_Advanced : public CPropertyPage
{
	DECLARE_DYNAMIC(CPage_Advanced)

public:
	//CPage_Advanced();
	CPage_Advanced(MFC_UI *pUI);
	virtual ~CPage_Advanced();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_ADVANCED };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()


private:
	/**
	* @brief ������
	* @see  MFC_UI::DisplayTWAINGUI()
	* @note ���ⲿ����ֵ
	*/
	MFC_UI  *m_pUI; 
private:

	    
	/**
	* @brief ֽ�Ŵ�С: US Letter/US Legal/A4/A5  
	* @see CTWAINDS_FreeIMage.cpp Line 606
	*/
	CComboBox m_combo_standardsizes;  

	/**
	* @brief ֽ�ŷ���: ����/����  
	* @see CTWAINDS_FreeIMage.cpp Line 615
	*/
	CComboBox m_combo_orientation;

	CComboBox m_combo_uints;  ///<����λ

	CEdit m_edit_custom_width;  ///< ֽ�Ŵ�С���Զ�����
	CEdit m_edit_custom_height;  ///< ֽ�Ŵ�С���Զ���߶�

private:
	void UpdateControls(void);  ///< ���¿ؼ�״̬

private:
	virtual BOOL OnInitDialog();
	
	afx_msg void OnCbnSelchangeAdvanced_Combo_Standardsizes();
	afx_msg void OnCbnSelchangeAdvanced_Combo_Orientation();
	afx_msg void OnCbnSelchangeAdvanced_Combo_Uints();

	/*afx_msg void OnEnChangeAdvanced_Edit_Customwidth();
	afx_msg void OnEnChangeAdvanced_Edit_Customheight();*/
};
