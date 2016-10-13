// Page_Base.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UDS Scanner.h"
#include "Page_Base.h"
#include "afxdialogex.h"
#include "Dlg_Profile.h"

#define SLIDER_MIN -100  ///< ��������Сֵ
#define SLIDER_MAX  100  ///< ���������ֵ
// CPage_Base �Ի���
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


// CPage_Base ��Ϣ�������


void CPage_Base::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
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
	// TODO: �ڴ����ר�ô����/����û���
	m_pUI->Cancel();
	CPropertyPage::OnCancel();
}

//BOOL CPage_Base::OnApply()  //�����ȷ�����롰Ӧ�á���ť������
//{
//	// TODO: �ڴ����ר�ô����/����û���
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
	* ɨ�跽ʽ
	*/
	m_combo_source.ResetContent();
	nCapIndex = m_pUI->GetCurrentCapIndex(CAP_FEEDERENABLED);
	lstCapValues = m_pUI->GetValidCap(CAP_FEEDERENABLED);
	if(lstCapValues && lstCapValues->size()>0)
	{
		m_combo_source.InsertString(0,lstCapValues->at(0)!=0?"�Զ���ֽ��":"ƽ��");
		if(lstCapValues->size()>1)
		{
			m_combo_source.InsertString(1,lstCapValues->at(1)!=0?"�Զ���ֽ��":"ƽ��");
		}
		
	}
	m_combo_source.SetCurSel(nCapIndex);


	/**
	* ͼ������
	*/ 
	m_combo_colormode.ResetContent();
	//m_pUI->SetCapValueInt(ICAP_PIXELTYPE,TWPT_RGB);  ///< ����Ĭ��ͼ�����ͣ���ɫ��ԭ��Ĭ��:�Ҷ�
	nCapIndex = m_pUI->GetCurrentCapIndex(ICAP_PIXELTYPE);
	lstCapValues = m_pUI->GetValidCap(ICAP_PIXELTYPE);
	for(unsigned int i=0; i<lstCapValues->size();i++)
	{
		switch(lstCapValues->at(i))
		{
		case TWPT_BW:
			m_combo_colormode.InsertString(i,"�ڰ�");
			break;
		case TWPT_GRAY:
			m_combo_colormode.InsertString(i,"�Ҷ�");
			break;
		case TWPT_RGB:
			m_combo_colormode.InsertString(i,"��ɫ");
			break;
		default:
			continue;
		}
	}
	m_combo_colormode.SetCurSel(nCapIndex);

	/**
	* �ֱ���
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
	* ����/˫��ɨ
	* @see CTWAINDS_FreeIMage.cpp Line 675
	*/
	m_combo_scanside.ResetContent();  ///< �������
	nCapIndex = m_pUI->GetCurrentCapIndex(CAP_DUPLEXENABLED);
	lstCapValues = m_pUI->GetValidCap(CAP_DUPLEXENABLED);
	if(lstCapValues && lstCapValues->size()>0)
	{
		m_combo_scanside.InsertString(0,lstCapValues->at(0)!=0?"˫��":"����");
		if(lstCapValues->size()>1)
		{
			m_combo_scanside.InsertString(1,lstCapValues->at(1)!=0?"˫��":"����");
		}
		m_combo_scanside.SetCurSel(nCapIndex);  ///< ��ʾĬ��ֵ
	}

	UpdateData(FALSE);
}


BOOL CPage_Base::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitComboProfile();
	InitSliderCtrl();
	UpdateControls();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CPage_Base::InitSliderCtrl()
{
	m_slider_contrast.SetRange(SLIDER_MIN,SLIDER_MAX);
	m_slider_contrast.SetTicFreq(1);  ///< ���û������̶ȵ�Ƶ��Ϊ1����λ������Ҫ����������们���ʼλ�ò���
	m_slider_contrast.SetPos(0);

	m_slider_brightness.SetRange(SLIDER_MIN,SLIDER_MAX);
	m_slider_brightness.SetTicFreq(1);
	m_slider_brightness.SetPos(0);
	UpdateData(FALSE);  ///< ���¿ؼ�
}

/**
* Slider�ؼ����ݱ䶯
*/
void CPage_Base::OnNMCustomdrawBase_Slider_Contrast(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);  ///< ��������
	CString str;
	int sldValue = m_slider_contrast.GetPos();  ///< ��ȡ���鵱ǰλ��
	m_pUI->SetCapValueFloat(ICAP_CONTRAST,(float)sldValue);  ///< ���öԱȶ�Ϊ��ǰ������ֵ
	str.Format("%d", sldValue);
	m_edit_contrast.SetWindowText(str);  ///< �ڱ༭��ͬ����ʾ������ֵ
	UpdateData(FALSE);  ///< ���¿ؼ�
	/*///< ����Ӧ�ð�ťΪ����״̬
	SetModified(TRUE);*/
	*pResult = 0;
}


void CPage_Base::OnNMCustomdrawBase_Slider_Brightness(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);  ///< ��������
	CString str;
	int sldValue = m_slider_brightness.GetPos();  ///< ��ȡ���鵱ǰλ��
	m_pUI->SetCapValueFloat(ICAP_BRIGHTNESS,(float)sldValue);  ///< ��������Ϊ��ǰ������ֵ
	str.Format("%d", sldValue);
	m_edit_brightness.SetWindowText(str);  ///< �ڱ༭��ͬ����ʾ������ֵ
	UpdateData(FALSE);  ///< ���¿ؼ�
	/*///< ����Ӧ�ð�ťΪ����״̬
	SetModified(TRUE);*/
	*pResult = 0;
}


/**
* Edit�ؼ����ݱ䶯
*/
void CPage_Base::OnEnChangeBase_Edit_Contrast()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CPropertyPage::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);  ///< ��������
	CString str;
	m_edit_contrast.GetWindowText(str);
	m_slider_contrast.SetPos(_ttoi(str));
	m_edit_contrast.SetSel(str.GetLength(), str.GetLength(),TRUE);  ///< ���ñ༭��ؼ���Χ
	UpdateData(FALSE);  ///< ���¿ؼ�
	/*///< ����Ӧ�ð�ťΪ����״̬
	SetModified(TRUE);*/
}


void CPage_Base::OnEnChangeBase_Edit_Brightness()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CPropertyPage::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);  ///< ��������
	CString str;
	m_edit_brightness.GetWindowText(str);
	m_slider_brightness.SetPos(_ttoi(str));
	m_edit_brightness.SetSel(str.GetLength(), str.GetLength(),TRUE);  ///< ���ñ༭��ؼ���Χ
	UpdateData(FALSE);  ///< ���¿ؼ�
	/*///< ����Ӧ�ð�ťΪ����״̬
	SetModified(TRUE);*/
}

/**
* Combobox�ؼ����ݱ䶯
*/
void CPage_Base::OnCbnSelchangeBase_Combo_Source()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nIndex = m_combo_source.GetCurSel();  ///<��ǰcombo���
	//m_pUI->SetCapValueInt(CAP_FEEDERENABLED,nIndex?1:0);  ///<���ö�Ӧ����
	CString strCBText; 
	m_combo_source.GetLBText( nIndex, strCBText);  ///<��ȡ��ǰѡ������
	//int bval = _ttoi(strCBText);  ///<�ַ�תint
	int nval;
	if (strCBText.Find("ƽ��"))
	{
		nval = 0;
	} 
	else
	{
		nval = 1;
	}
	m_pUI->SetCapValueInt(CAP_FEEDERENABLED,nval);  ///<���ö�Ӧ����
	/*///< ����Ӧ�ð�ťΪ����״̬
	SetModified(TRUE);*/
	return;
}


void CPage_Base::OnCbnSelchangeBase_Combo_Colormode()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nIndex = m_combo_colormode.GetCurSel();
	///< ֱ�Ӹ��ݵ�ǰ���nIndex����ͼ������
	m_pUI->SetCapValueInt(ICAP_PIXELTYPE,nIndex);  
	UpdateControls();
	/*///< ����Ӧ�ð�ťΪ����״̬
	SetModified(TRUE);*/
	//return;
}


void CPage_Base::OnCbnSelchangeBase_Combo_Resolution()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nIndex = m_combo_resolution.GetCurSel();
	CString strCBText; 
	m_combo_resolution.GetLBText( nIndex, strCBText);
	int nval = _ttoi(strCBText);  ///< Cstring ת int
	m_pUI->SetCapValueInt(ICAP_XRESOLUTION,nval); 
	m_pUI->SetCapValueInt(ICAP_YRESOLUTION,nval); 
	/*///< ����Ӧ�ð�ťΪ����״̬
	SetModified(TRUE);*/
	return;
}

///< ˫��/����ɨ
void CPage_Base::OnCbnSelchangeBase_Combo_Scanside()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nIndex = m_combo_scanside.GetCurSel();
	//m_pUI->SetCapValueInt(CAP_DUPLEXENABLED,nIndex?1:0);
	CString strCBText; 
	m_combo_scanside.GetLBText( nIndex, strCBText);
	//int nval = _ttoi(strCBText);  ///< Cstring ת int
	int nval;
	m_combo_scanside.GetLBText( nIndex, strCBText);
  if (strCBText.Find("����") >= 0)
  {
		nval = 0;
  } 
  else
  {
		nval = 1;
  }
	m_pUI->SetCapValueInt(CAP_DUPLEXENABLED,nval?1:0);
}

///< �½�ģ��
void CPage_Base::OnBase_Btn_Newprofile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDlg_Profile *pDlg = new CDlg_Profile;
	//dlg.DoModal();
	//CWnd *pMainWnd = CWnd::FromHandle(g_hwndDLG);
	//m_pDlg = new CDlg_Profile;
	//int nRes = m_pDlg->Create(CDlg_Profile::IDD);
	//m_pDlg->ShowWindow(SW_SHOW);

	CDlg_Profile dlg;  ///< �½�ģ��Ի���
	dlg.DoModal();

	CString strExistName;

	if (TRUE == dlg.m_bOk)  ///< ȷ���½�ģ��
	{
		strExistName = dlg.GetProfileName();  ///< ��ȡ�Ի����б����ģ����
	}
	else
	{
		return;
	}

	/**
	* �ж��½�ģ�����Ƿ��Ѵ���
	**/
	CString strCombo;  
	int nLength;   
	for (int i=0;i < m_combo_profile.GetCount();i++)
	{        
		nLength = m_combo_profile.GetLBTextLen( i );  ///< ��ȡCombobox���ݳ���
		m_combo_profile.GetLBText( i, strCombo.GetBuffer(nLength));
		if (strCombo == strExistName)
		{
			if (AfxMessageBox("ģ���Ѵ��ڣ�����Ҫ���´�����",MB_OKCANCEL) == IDCANCEL)  
			{
				return;  ///< ȡ���½�ͬ��ģ��
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

///< ɾ��ģ��
void CPage_Base::OnBase_Btn_Deleteprofile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);  ///< ��������
	int nIndex = m_combo_profile.GetCurSel();
	CString strProfile; 
	m_combo_profile.GetLBText( nIndex, strProfile);
	
	if(m_pUI->TW_DeleteProfile(strProfile.GetBuffer()))
	{
		m_combo_profile.DeleteString(nIndex);
	}
	int nCount = m_combo_profile.GetCount();
	m_combo_profile.SetCurSel(nCount-1);  ///< �л������һ��
	LoadProfile();
}

void CPage_Base::InitComboProfile()
{
	m_combo_profile.ResetContent();
	m_combo_profile.InsertString(0,"Ĭ��ģ��");
	m_combo_profile.SetCurSel(0);

	///< �����Ѵ��ڵ�ģ��
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
	UpdateData(TRUE);  ///< ��������
	int nIndex = m_combo_profile.GetCurSel();
	if(0 == nIndex)  ///< Ĭ��ģ�壬������������
	{
		m_pUI->ResetAllCaps();
	}
	else  ///< ����ģ��
	{	
		CString strProfile; 
		m_combo_profile.GetLBText( nIndex, strProfile);
		m_pUI->TW_LoadProfileFromFile(strProfile.GetBuffer());
	}
	UpdateControls();
}

///< ɨ�����ͬ��Ϊģ��ֵ
void CPage_Base::OnCbnSelchangeBase_Combo_Profile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	LoadProfile();
}



