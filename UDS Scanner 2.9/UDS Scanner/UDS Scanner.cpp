// UDS Scanner.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "UDS Scanner.h"

#include "src/dllmain.h"
extern HINSTANCE g_hinstance;
extern HWND g_hwndDLG;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CUDSScannerApp

BEGIN_MESSAGE_MAP(CUDSScannerApp, CWinApp)
END_MESSAGE_MAP()


// CUDSScannerApp ����

CUDSScannerApp::CUDSScannerApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
	
}


// Ψһ��һ�� CUDSScannerApp ����

CUDSScannerApp theApp;


// CUDSScannerApp ��ʼ��
//HINSTANCE g_hinstance;
BOOL CUDSScannerApp::InitInstance()
{
	//g_hinstance = (HINSTANCE)GetCurrentModule(); //��ȡDLL����ľ��
	CWinApp::InitInstance();
	//::MessageBox(hwndDLG,"Init","UDS",MB_OK);

	//�÷����õ����ǵ��õ�exe�ľ��
	//AFX_MODULE_STATE* state = AfxGetModuleState();
	//g_hinstance = state->m_hCurrentInstanceHandle;

	//��ȡDLL�ľ���·��
	/*TCHAR lib_name[MAX_PATH]; 
	::GetModuleFileName( GetCurrentModule(), lib_name, MAX_PATH );
	::MessageBox(hwndDLG,lib_name,"UDS",MB_OK);*/

	return TRUE;
}


int CUDSScannerApp::ExitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
	unLoadDSMLib();
	g_hinstance = 0;
	return CWinApp::ExitInstance();
}


