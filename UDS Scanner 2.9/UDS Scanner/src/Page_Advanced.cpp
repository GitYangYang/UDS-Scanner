// Page_Advanced.cpp : 实现文件
//

#include "stdafx.h"
#include "UDS Scanner.h"
#include "Page_Advanced.h"
#include "afxdialogex.h"


// CPage_Advanced 对话框

IMPLEMENT_DYNAMIC(CPage_Advanced, CPropertyPage)

	CPage_Advanced::CPage_Advanced(MFC_UI *pUI)
	: m_pUI(pUI), CPropertyPage(CPage_Advanced::IDD)
{

}

CPage_Advanced::~CPage_Advanced()
{
}

void CPage_Advanced::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADVANCED_COMBO_STANDARDSIZES, m_combo_standardsizes);
	DDX_Control(pDX, IDC_ADVANCED_COMBO_ORIENTATION, m_combo_orientation);
	DDX_Control(pDX, IDC_ADVANCED_EDIT_CUSTOMWIDTH, m_edit_custom_width);
	DDX_Control(pDX, IDC_ADVANCED_EDIT_CUSTOMHEIGHT, m_edit_custom_height);
	DDX_Control(pDX, IDC_ADVANCED_COMBO_UINTS, m_combo_uints);
}


BEGIN_MESSAGE_MAP(CPage_Advanced, CPropertyPage)
	ON_CBN_SELCHANGE(IDC_ADVANCED_COMBO_STANDARDSIZES, &CPage_Advanced::OnCbnSelchangeAdvanced_Combo_Standardsizes)
	ON_CBN_SELCHANGE(IDC_ADVANCED_COMBO_ORIENTATION, &CPage_Advanced::OnCbnSelchangeAdvanced_Combo_Orientation)
	ON_CBN_SELCHANGE(IDC_ADVANCED_COMBO_UINTS, &CPage_Advanced::OnCbnSelchangeAdvanced_Combo_Uints)
	//ON_EN_CHANGE(IDC_ADVANCED_EDIT_CUSTOMWIDTH, &CPage_Advanced::OnEnChangeAdvanced_Edit_Customwidth)
END_MESSAGE_MAP()

void CPage_Advanced::UpdateControls(void)
{
	int nCapIndex;
	const IntVector* lstCapValues;

	/**
	* 纸张方向
	*/
	m_combo_orientation.ResetContent();  ///< 清空内容
	nCapIndex = m_pUI->GetCurrentCapIndex(ICAP_ORIENTATION);
	lstCapValues = m_pUI->GetValidCap(ICAP_ORIENTATION);
	for(unsigned int i=0; i<lstCapValues->size();i++)
	{
		switch(lstCapValues->at(i))
		{
		case TWOR_PORTRAIT:
			m_combo_orientation.InsertString(i,"纵向");
			break;
		case TWOR_LANDSCAPE:
			m_combo_orientation.InsertString(i,"横向");
			break;
		default:
			continue;
		}
		
	}
	m_combo_orientation.SetCurSel(nCapIndex);  ///< 显示默认值


	/**
	* 纸张大小 (未完...)
	*/
	m_combo_standardsizes.ResetContent();  ///< 清空内容
	nCapIndex = m_pUI->GetCurrentCapIndex(ICAP_SUPPORTEDSIZES);
	lstCapValues = m_pUI->GetValidCap(ICAP_SUPPORTEDSIZES);
	for(unsigned int i=0; i<lstCapValues->size();i++)
	{
		switch(lstCapValues->at(i))
		{
		case TWSS_NONE:
			m_combo_standardsizes.InsertString(i,"自定义");
			break;
		case TWSS_USLETTER:
			m_combo_standardsizes.InsertString(i,"US Letter (8.5\" x 11\")");  //216mm x 280mm
			break;
		case TWSS_USLEGAL:
			m_combo_standardsizes.InsertString(i,"US Legal (8.5\" x 14\")");  //216mm x 356mm
			break;
		case TWSS_A4:
			m_combo_standardsizes.InsertString(i,"A4 (210mm x 297mm)");
			break;
		case TWSS_A5:
			m_combo_standardsizes.InsertString(i,"A5 (148mm x 210mm)");
			break;
		default:
			continue;
		}
	}
	m_combo_standardsizes.SetCurSel(nCapIndex);  ///< 显示默认值

	if (TWSS_NONE == lstCapValues->at(nCapIndex))  ///<　纸张大小：自定义。控件不可用
	{
		m_edit_custom_width.EnableWindow(TRUE);
		m_edit_custom_height.EnableWindow(TRUE);
		m_combo_orientation.EnableWindow(FALSE);
		GetDlgItem(IDC_ADVANCED_STATIC_CUSTOM_WIDTH)->EnableWindow(TRUE);
		GetDlgItem(IDC_ADVANCED_STATIC_CUSTOM_HEIGHT)->EnableWindow(TRUE);
		GetDlgItem(IDC_ADVANCED_STATIC_ORIENTATION)->EnableWindow(FALSE);
	} 
	else
	{
		m_edit_custom_width.EnableWindow(FALSE);
		m_edit_custom_height.EnableWindow(FALSE);
		m_combo_orientation.EnableWindow(TRUE);
		GetDlgItem(IDC_ADVANCED_STATIC_CUSTOM_WIDTH)->EnableWindow(FALSE);
		GetDlgItem(IDC_ADVANCED_STATIC_CUSTOM_HEIGHT)->EnableWindow(FALSE);
		GetDlgItem(IDC_ADVANCED_STATIC_ORIENTATION)->EnableWindow(TRUE);
	}


	/**
	* 自定义宽与高
	*/
	TW_FRAME frame;
	CString strTemp;

	frame = m_pUI->GetCurrentFrame();
	strTemp.Format("%0.2f",FIX32ToFloat(frame.Right));
	m_edit_custom_width.SetWindowText(strTemp);

	frame = m_pUI->GetCurrentFrame();
	strTemp.Format("%0.2f",FIX32ToFloat(frame.Bottom));
	m_edit_custom_height.SetWindowText(strTemp);


	/**
	* 单位
	*/
	m_combo_uints.ResetContent();  ///< 清空内容
	nCapIndex = m_pUI->GetCurrentCapIndex(ICAP_UNITS);
	lstCapValues = m_pUI->GetValidCap(ICAP_UNITS);
	for(unsigned int i=0; i<lstCapValues->size();i++)
	{
		switch(lstCapValues->at(i))
		{
		case TWUN_INCHES:
			m_combo_uints.InsertString(i,"Inches");
			break;
		case TWUN_PIXELS:
			m_combo_uints.InsertString(i,"Pixels");
			break;
		case TWUN_CENTIMETERS:
			m_combo_uints.InsertString(i,"Centimeters");
			break;
		case TWUN_PICAS:
			m_combo_uints.InsertString(i,"Picas");
			break;
		case TWUN_POINTS:
			m_combo_uints.InsertString(i,"Points");
			break;
		case TWUN_TWIPS:
			m_combo_uints.InsertString(i,"Twips");
			break;
		default:
			continue;
		}
	}
	m_combo_uints.SetCurSel(nCapIndex);
}


// CPage_Advanced 消息处理程序


BOOL CPage_Advanced::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
	UpdateControls();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CPage_Advanced::OnCbnSelchangeAdvanced_Combo_Standardsizes()
{
	// TODO: 在此添加控件通知处理程序代码
	int nIndex = m_combo_standardsizes.GetCurSel();
	CString strCBText; 
	m_combo_standardsizes.GetLBText( nIndex, strCBText);
	int nval;
	//int nval = _ttoi(strCBText);  ///< Cstring 转 int
	if (strCBText.Find("自定义") >= 0)
	{
		nval = TWSS_NONE;
	}
	else if (strCBText.Find("US Letter") >= 0)
	{
		nval = TWSS_USLETTER;
	}
	else if (strCBText.Find("US Legal") >= 0)
	{
		nval = TWSS_USLEGAL;
	}
	else if (strCBText.Find("A4") >= 0)
	{
		nval = TWSS_A4;
	}
	else if (strCBText.Find("A5") >= 0)
	{
		nval = TWSS_A5;
	}
	else
	{
		return;
	}
	m_pUI->SetCapValueInt(ICAP_SUPPORTEDSIZES,nval); 
	UpdateControls(); 
}


void CPage_Advanced::OnCbnSelchangeAdvanced_Combo_Orientation()
{
	// TODO: 在此添加控件通知处理程序代码
	int nIndex = m_combo_orientation.GetCurSel();
	CString strCBText; 
	m_combo_orientation.GetLBText( nIndex, strCBText);
	/*int nval = _ttoi(strCBText);  ///< Cstring 转 int*/
	int nval;
	if (strCBText.Find("纵向") >= 0)
	{
		nval = TWOR_PORTRAIT;
	}
	else
	{
		nval = TWOR_LANDSCAPE;
	}
	m_pUI->SetCapValueFloat(ICAP_ORIENTATION,(float)nval);	
	UpdateControls(); 
}


void CPage_Advanced::OnCbnSelchangeAdvanced_Combo_Uints()
{
	// TODO: 在此添加控件通知处理程序代码
	int nIndex = m_combo_uints.GetCurSel();
	CString strCBText; 
	m_combo_uints.GetLBText( nIndex, strCBText);
	int nval;
	//int nval = _ttoi(strCBText);  ///< Cstring 转 int
	if (strCBText.Find("Inches") >= 0)
	{
		nval = TWUN_INCHES;
	}
	else if (strCBText.Find("Pixels") >= 0)
	{
		nval = TWUN_PIXELS;
	}
	else if (strCBText.Find("Centimeters") >= 0)
	{
		nval = TWUN_CENTIMETERS;
	}
	else if (strCBText.Find("Picas") >= 0)
	{
		nval = TWUN_PICAS;
	}
	else if (strCBText.Find("Points") >= 0)
	{
		nval = TWUN_POINTS;
	}
	else if (strCBText.Find("Twips") >= 0)
	{
		nval = TWUN_TWIPS;
	}
	else
	{
		return;
	}
	m_pUI->SetCapValueInt(ICAP_UNITS,nval); 
	UpdateControls(); 
}


//void CPage_Advanced::OnEnChangeAdvanced_Edit_Customwidth()
//{
//	// TODO:  如果该控件是 RICHEDIT 控件，它将不
//	// 发送此通知，除非重写 CPropertyPage::OnInitDialog()
//	// 函数并调用 CRichEditCtrl().SetEventMask()，
//	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
//
//	// TODO:  在此添加控件通知处理程序代码
//	CString strWidth,strHeight;
//	m_edit_custom_width.GetWindowText(strWidth);
//	m_edit_custom_height.GetWindowText(strHeight);
//	float fW = _ttof(strWidth);  // CString -> float
//	float fH = _ttof(strHeight); 
//	m_pUI->SetCurrentFrame(0.0f,0.0f,fH,fW);
//	UpdateControls(); 
//}
