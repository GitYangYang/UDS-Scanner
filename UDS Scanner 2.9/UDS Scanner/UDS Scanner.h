// UDS Scanner.h : UDS Scanner DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CUDSScannerApp
// �йش���ʵ�ֵ���Ϣ������� UDS Scanner.cpp
//

class CUDSScannerApp : public CWinApp
{
public:
	CUDSScannerApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};
