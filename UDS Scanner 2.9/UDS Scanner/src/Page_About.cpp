// Page_About.cpp : 实现文件
//

#include "stdafx.h"
#include "UDS Scanner.h"
#include "Page_About.h"
#include "afxdialogex.h"


// CPage_About 对话框

IMPLEMENT_DYNAMIC(CPage_About, CPropertyPage)

CPage_About::CPage_About()
	: CPropertyPage(CPage_About::IDD)
{

}

CPage_About::~CPage_About()
{
}

void CPage_About::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPage_About, CPropertyPage)
END_MESSAGE_MAP()


// CPage_About 消息处理程序
