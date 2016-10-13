// Page_Base.cpp : 实现文件
//

#include "stdafx.h"
#include "UDS Scanner.h"
#include "Page_Base.h"
#include "afxdialogex.h"
#include "Dlg_Profile.h"

#define SLIDER_MIN -100  ///< 滑动条最小值
#define SLIDER_MAX  100  ///< 滑动条最大值
// CPage_Base 对话框
extern HWND g_hwndDLG;

IMPLEMENT_DYNAMIC(CPage_Base, CPropertyPage)

CPage_Base::CPage_Base(MFC_UI *pUI)
	: m_pUI(pUI),CPropertyPage(CPage_Base::IDD)
{

}

CPage_Base::~CPage_Base()
{
	/*if (m_pDlg)
	{
		delete m_pDlg;
		m_pDlg = NULL;
	}
	*/
}

void CPage_Base::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BASE_COMBO_SOURCE, m_combo_source);
	DDX_Control(pDX, IDC_BASE_COMBO_COLORMODE, m_combo_colormode);
	DDX_Control(pDX, IDC_BASE_COMBO_RESOLUTION, m_combo_resolution);
	DDX_Control(pDX, IDC_BASE_SLIDER_CONTRAST, m_slider_contrast);
	DDX_Control(pDX, IDC_BASE_SLIDER_BRIGHTNESS, m_slider_brightness);
	DDX_Control(pDX, IDC_BASE_EDIT_BRIGHTNESS, m_edit_brightness);
	DDX_Control(pDX, IDC_BASE_EDIT_CONTRAST, m_edit_contrast);
	DDX_Control(pDX, IDC_BASE_COMBO_PROFILE, m_combo_profile);
	DDX_Control(pDX, IDC_BASE_COMBO_SCANSIDE, m_combo_scanside);
}


BEGIN_MESSAGE_MAP(CPage_Base, CPropertyPage)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_BASE_SLIDER_CONTRAST, &CPage_Base::OnNMCustomdrawBase_Slider_Contrast)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_BASE_SLIDER_BRIGHTNESS, &CPage_Base::OnNMCustomdrawBase_Slider_Brightness)
	ON_EN_CHANGE(IDC_BASE_EDIT_CONTRAST, &CPage_Base::OnEnChangeBase_Edit_Contrast)
	ON_EN_CHANGE(IDC_BASE_EDIT_BRIGHTNESS, &CPage_Base::OnEnChangeBase_Edit_Brightness)
	ON_CBN_SELCHANGE(IDC_BASE_COMBO_SOURCE, &CPage_Base::OnCbnSelchangeBase_Combo_Source)
	ON_CBN_SELCHANGE(IDC_BASE_COMBO_COLORMODE, &CPage_Base::OnCbnSelchangeBase_Combo_Colormode)
	ON_CBN_SELCHANGE(IDC_BASE_COMBO_RESOLUTION, &CPage_Base::OnCbnSelchangeBase_Combo_Resolution)
	ON_BN_CLICKED(IDC_BASE_BTN_NEWPROFILE, &CPage_Base::OnBase_Btn_Newprofile)
	ON_BN_CLICKED(IDC_BASE_BTN_DELETEPROFILE, &CPage_Base::OnBase_Btn_Deleteprofile)
	ON_CBN_SELCHANGE(IDC_BASE_COMBO_PROFILE, &CPage_Base::OnCbnSelchangeBase_Combo_Profile)
	ON_CBN_SELCHANGE(IDC_BASE_COMBO_SCANSIDE, &CPage_Base::OnCbnSelchangeBase_Combo_Scanside)
END_MESSAGE_MAP()


// CPage_Base 消息处理程序


void CPage_Base::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	//AfxMessageBox("CPage_Base::OnOK");
	if(m_pUI->m_bSetup)  // EnableDSOnly
	{
		m_pUI->Save();
	}
	else  
	{
		m_pUI->Scan();
	}

	CPropertyPage::OnOK();
}


void CPage_Base::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	m_pUI->Cancel();
	CPropertyPage::OnCancel();
}

//BOOL CPage_Base::OnApply()  //点击“确定”与“应用”按钮都调用
//{
//	// TODO: 在此添加专用代码和/或调用基类
//	AfxMessageBox("OnApply");
//	ChangeControls();
//	return CPropertyPage::OnApply();
//}

void CPage_Base::UpdateControls(void)
{
	int nCapIndex;
	const IntVector* lstCapValues;
	const FloatVector* lstCapValuesFlt;
	/**
	* 扫描方式
	*/
	m_combo_source.ResetContent();
	nCapIndex = m_pUI->GetCurrentCapIndex(CAP_FEEDERENABLED);
	lstCapValues = m_pUI->GetValidCap(CAP_FEEDERENABLED);
	if(lstCapValues && lstCapValues->size()>0)
	{
		m_combo_source.InsertString(0,lstCapValues->at(0)!=0?"自动送纸器":"平板");
		if(lstCapValues->size()>1)
		{
			m_combo_source.InsertString(1,lstCapValues->at(1)!=0?"自动送纸器":"平板");
		}
		
	}
	m_combo_source.SetCurSel(nCapIndex);


	/**
	* 图像类型
	*/ 
	m_combo_colormode.ResetContent();
	//m_pUI->SetCapValueInt(ICAP_PIXELTYPE,TWPT_RGB);  ///< 设置默认图像类型：彩色，原来默认:灰度
	nCapIndex = m_pUI->GetCurrentCapIndex(ICAP_PIXELTYPE);
	lstCapValues = m_pUI->GetValidCap(ICAP_PIXELTYPE);
	for(unsigned int i=0; i<lstCapValues->size();i++)
	{
		switch(lstCapValues->at(i))
		{
		case TWPT_BW:
			m_combo_colormode.InsertString(i,"黑白");
			break;
		case TWPT_GRAY:
			m_combo_colormode.InsertString(i,"灰度");
			break;
		case TWPT_RGB:
			m_combo_colormode.InsertString(i,"彩色");
			break;
		default:
			continue;
		}
	}
	m_combo_colormode.SetCurSel(nCapIndex);

	/**
	* 分辨率
	*/
	//m_pUI->SetCapValueFloat(ICAP_XRESOLUTION,0);
	m_combo_resolution.ResetContent();
	nCapIndex = m_pUI->GetCurrentCapIndex(ICAP_XRESOLUTION);
	lstCapValuesFlt = m_pUI->GetValidCapFloat(ICAP_XRESOLUTION);

	for(unsigned int i=0; i<lstCapValuesFlt->size();i++)
	{
		CString strTemp;
		strTemp.Format("%d",(int)lstCapValuesFlt->at(i));
		m_combo_resolution.InsertString(i,strTemp);
	}
	m_combo_resolution.SetCurSel(nCapIndex);

	/**
	* 单面/双面扫
	* @see CTWAINDS_FreeIMage.cpp Line 675
	*/
	m_combo_scanside.ResetContent();  ///< 清空内容
	nCapIndex = m_pUI->GetCurrentCapIndex(CAP_DUPLEXENABLED);
	lstCapValues = m_pUI->GetValidCap(CAP_DUPLEXENABLED);
	if(lstCapValues && lstCapValues->size()>0)
	{
		m_combo_scanside.InsertString(0,lstCapValues->at(0)!=0?"双面":"单面");
		if(lstCapValues->size()>1)
		{
			m_combo_scanside.InsertString(1,lstCapValues->at(1)!=0?"双面":"单面");
		}
		m_combo_scanside.SetCurSel(nCapIndex);  ///< 显示默认值
	}

	UpdateData(FALSE);
}


BOOL CPage_Base::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitComboProfile();
	InitSliderCtrl();
	UpdateControls();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CPage_Base::InitSliderCtrl()
{
	m_slider_contrast.SetRange(SLIDER_MIN,SLIDER_MAX);
	m_slider_contrast.SetTicFreq(1);  ///< 设置滑动条刻度的频度为1个单位，很重要，若不加这句滑块初始位置不变
	m_slider_contrast.SetPos(0);

	m_slider_brightness.SetRange(SLIDER_MIN,SLIDER_MAX);
	m_slider_brightness.SetTicFreq(1);
	m_slider_brightness.SetPos(0);
	UpdateData(FALSE);  ///< 更新控件
}

/**
* Slider控件内容变动
*/
void CPage_Base::OnNMCustomdrawBase_Slider_Contrast(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);  ///< 接收数据
	CString str;
	int sldValue = m_slider_contrast.GetPos();  ///< 获取滑块当前位置
	m_pUI->SetCapValueFloat(ICAP_CONTRAST,(float)sldValue);  ///< 设置对比度为当前滚动条值
	str.Format("%d", sldValue);
	m_edit_contrast.SetWindowText(str);  ///< 在编辑框同步显示滚动条值
	UpdateData(FALSE);  ///< 更新控件
	/*///< 设置应用按钮为可用状态
	SetModified(TRUE);*/
	*pResult = 0;
}


void CPage_Base::OnNMCustomdrawBase_Slider_Brightness(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);  ///< 接收数据
	CString str;
	int sldValue = m_slider_brightness.GetPos();  ///< 获取滑块当前位置
	m_pUI->SetCapValueFloat(ICAP_BRIGHTNESS,(float)sldValue);  ///< 设置亮度为当前滚动条值
	str.Format("%d", sldValue);
	m_edit_brightness.SetWindowText(str);  ///< 在编辑框同步显示滚动条值
	UpdateData(FALSE);  ///< 更新控件
	/*///< 设置应用按钮为可用状态
	SetModified(TRUE);*/
	*pResult = 0;
}


/**
* Edit控件内容变动
*/
void CPage_Base::OnEnChangeBase_Edit_Contrast()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);  ///< 接收数据
	CString str;
	m_edit_contrast.GetWindowText(str);
	m_slider_contrast.SetPos(_ttoi(str));
	m_edit_contrast.SetSel(str.GetLength(), str.GetLength(),TRUE);  ///< 设置编辑框控件范围
	UpdateData(FALSE);  ///< 更新控件
	/*///< 设置应用按钮为可用状态
	SetModified(TRUE);*/
}


void CPage_Base::OnEnChangeBase_Edit_Brightness()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);  ///< 接收数据
	CString str;
	m_edit_brightness.GetWindowText(str);
	m_slider_brightness.SetPos(_ttoi(str));
	m_edit_brightness.SetSel(str.GetLength(), str.GetLength(),TRUE);  ///< 设置编辑框控件范围
	UpdateData(FALSE);  ///< 更新控件
	/*///< 设置应用按钮为可用状态
	SetModified(TRUE);*/
}

/**
* Combobox控件内容变动
*/
void CPage_Base::OnCbnSelchangeBase_Combo_Source()
{
	// TODO: 在此添加控件通知处理程序代码
	int nIndex = m_combo_source.GetCurSel();  ///<当前combo序号
	//m_pUI->SetCapValueInt(CAP_FEEDERENABLED,nIndex?1:0);  ///<设置对应参数
	CString strCBText; 
	m_combo_source.GetLBText( nIndex, strCBText);  ///<获取当前选项内容
	//int bval = _ttoi(strCBText);  ///<字符转int
	int nval;
	if (strCBText.Find("平板"))
	{
		nval = 0;
	} 
	else
	{
		nval = 1;
	}
	m_pUI->SetCapValueInt(CAP_FEEDERENABLED,nval);  ///<设置对应参数
	/*///< 设置应用按钮为可用状态
	SetModified(TRUE);*/
	return;
}


void CPage_Base::OnCbnSelchangeBase_Combo_Colormode()
{
	// TODO: 在此添加控件通知处理程序代码
	int nIndex = m_combo_colormode.GetCurSel();
	///< 直接根据当前序号nIndex设置图像类型
	m_pUI->SetCapValueInt(ICAP_PIXELTYPE,nIndex);  
	UpdateControls();
	/*///< 设置应用按钮为可用状态
	SetModified(TRUE);*/
	//return;
}


void CPage_Base::OnCbnSelchangeBase_Combo_Resolution()
{
	// TODO: 在此添加控件通知处理程序代码
	int nIndex = m_combo_resolution.GetCurSel();
	CString strCBText; 
	m_combo_resolution.GetLBText( nIndex, strCBText);
	int nval = _ttoi(strCBText);  ///< Cstring 转 int
	m_pUI->SetCapValueInt(ICAP_XRESOLUTION,nval); 
	m_pUI->SetCapValueInt(ICAP_YRESOLUTION,nval); 
	/*///< 设置应用按钮为可用状态
	SetModified(TRUE);*/
	return;
}

///< 双面/单面扫
void CPage_Base::OnCbnSelchangeBase_Combo_Scanside()
{
	// TODO: 在此添加控件通知处理程序代码
	int nIndex = m_combo_scanside.GetCurSel();
	//m_pUI->SetCapValueInt(CAP_DUPLEXENABLED,nIndex?1:0);
	CString strCBText; 
	m_combo_scanside.GetLBText( nIndex, strCBText);
	//int nval = _ttoi(strCBText);  ///< Cstring 转 int
	int nval;
	m_combo_scanside.GetLBText( nIndex, strCBText);
  if (strCBText.Find("单面") >= 0)
  {
		nval = 0;
  } 
  else
  {
		nval = 1;
  }
	m_pUI->SetCapValueInt(CAP_DUPLEXENABLED,nval?1:0);
}

///< 新建模板
void CPage_Base::OnBase_Btn_Newprofile()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDlg_Profile *pDlg = new CDlg_Profile;
	//dlg.DoModal();
	//CWnd *pMainWnd = CWnd::FromHandle(g_hwndDLG);
	//m_pDlg = new CDlg_Profile;
	//int nRes = m_pDlg->Create(CDlg_Profile::IDD);
	//m_pDlg->ShowWindow(SW_SHOW);

	CDlg_Profile dlg;  ///< 新建模版对话框
	dlg.DoModal();

	CString strExistName;

	if (TRUE == dlg.m_bOk)  ///< 确定新建模版
	{
		strExistName = dlg.GetProfileName();  ///< 获取对话框中保存的模版名
	}
	else
	{
		return;
	}

	/**
	* 判断新建模板名是否已存在
	**/
	CString strCombo;  
	int nLength;   
	for (int i=0;i < m_combo_profile.GetCount();i++)
	{        
		nLength = m_combo_profile.GetLBTextLen( i );  ///< 获取Combobox内容长度
		m_combo_profile.GetLBText( i, strCombo.GetBuffer(nLength));
		if (strCombo == strExistName)
		{
			if (AfxMessageBox("模版已存在，您想要重新创建吗？",MB_OKCANCEL) == IDCANCEL)  
			{
				return;  ///< 取消新建同名模版
			}
			
		}
		strCombo.ReleaseBuffer();      
	}

	CString strName = strExistName;
	string strProfile = strName.GetBuffer();  ///< CString->string
	//strName.ReleaseBuffer();

	if(m_pUI->TW_SaveProfileToFile(strProfile))
	{		
		m_combo_profile.AddString(strName);
		m_combo_profile.SetCurSel(m_combo_profile.GetCount()-1);
	}
  	
	UpdateData(FALSE);
	
}

///< 删除模版
void CPage_Base::OnBase_Btn_Deleteprofile()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);  ///< 接收数据
	int nIndex = m_combo_profile.GetCurSel();
	CString strProfile; 
	m_combo_profile.GetLBText( nIndex, strProfile);
	
	if(m_pUI->TW_DeleteProfile(strProfile.GetBuffer()))
	{
		m_combo_profile.DeleteString(nIndex);
	}
	int nCount = m_combo_profile.GetCount();
	m_combo_profile.SetCurSel(nCount-1);  ///< 切换到最后一个
	LoadProfile();
}

void CPage_Base::InitComboProfile()
{
	m_combo_profile.ResetContent();
	m_combo_profile.InsertString(0,"默认模板");
	m_combo_profile.SetCurSel(0);

	///< 遍历已存在的模版
	lstString strFileNames;
	m_pUI->TW_GetAllProfiles(strFileNames);
	lstString::iterator iter = strFileNames.begin();
	for(;iter!=strFileNames.end(); iter++)
	{
		CString strTemp(iter->c_str());
		m_combo_profile.AddString(strTemp);
	}
}

void CPage_Base::LoadProfile()
{
	UpdateData(TRUE);  ///< 接收数据
	int nIndex = m_combo_profile.GetCurSel();
	if(0 == nIndex)  ///< 默认模板，重置驱动参数
	{
		m_pUI->ResetAllCaps();
	}
	else  ///< 其它模板
	{	
		CString strProfile; 
		m_combo_profile.GetLBText( nIndex, strProfile);
		m_pUI->TW_LoadProfileFromFile(strProfile.GetBuffer());
	}
	UpdateControls();
}

///< 扫描参数同步为模板值
void CPage_Base::OnCbnSelchangeBase_Combo_Profile()
{
	// TODO: 在此添加控件通知处理程序代码
	LoadProfile();
}



