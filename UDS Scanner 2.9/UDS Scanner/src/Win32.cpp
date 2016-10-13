// Win32.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"

#include "dllmain.h"
#include <list>
#include "resource.h"
//////////////////////////////////////////////////////////////////////////////
/************************************************************************
Most DLL developers have faced the challenge of detecting a HMODULE/HINSTANCE
handle within the module you're running in. It may be a difficult task if you 
wrote the DLL without a DLLMain() function or you are unaware of its name. For 
example:Your DLL was built without ATL/MFC, so the DLLMain() function exists,
but it's hidden from you code and you cannot access the hinstDLL parameter. 
 You do not know the DLL's real file name because it could be renamedby everyone
, so GetModuleHandle() is not for you.This small code can help you solve this 
problem:                                                                      
************************************************************************/


#if _MSC_VER >= 1300    // for VC 7.0
// from ATL 7.0 sources
#ifndef _delayimp_h
extern "C" IMAGE_DOS_HEADER __ImageBase;
#endif
#endif


//获取DLL自身的句柄
static HMODULE GetCurrentModule()
{
#if _MSC_VER < 1300    // earlier than .NET compiler (VC 6.0)

	// Here's a trick that will get you the handle of the module
	// you're running in without any a-priori knowledge:
	MEMORY_BASIC_INFORMATION mbi;
	static int dummy;
	VirtualQuery( &dummy, &mbi, sizeof(mbi) );

	return reinterpret_cast<HMODULE>(mbi.AllocationBase);
#else    // VC 7.0
	// from ATL 7.0 sources
	return reinterpret_cast<HMODULE>(&__ImageBase);
#endif
}


////注意：TRUE会导致DLL引用计数加1，FALSE不会改变引用计数，通常用FALSE
//HMODULE GetCurrentModule2(BOOL bRef/* = FALSE*/)  
//{  
//	HMODULE hModule = NULL;  
//	if (GetModuleHandleEx(bRef ? GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS : (GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS   
//		| GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT),    (LPCSTR)GetCurrentModule2, &hModule))  
//	{  
//		return hModule;  
//	}  
//
//	return NULL;  
//} 
//
//
//HMODULE GetSelfModuleHandle()  
//{  
//	MEMORY_BASIC_INFORMATION mbi;  
//
//	return ((::VirtualQuery(GetSelfModuleHandle, &mbi, sizeof(mbi)) != 0)   
//		? (HMODULE) mbi.AllocationBase : NULL);  
//}


// Globals
/**
* gloabal pointer of the Data Source, for access to the main DS_Entry.
*/
typedef struct _DS_inst
{
  TW_IDENTITY AppId;
  CTWAINDS_Base *pDS; 
}DS_inst;

typedef list<DS_inst> lstDS;
lstDS g_lstDS;

#ifdef TWH_CMP_MSC
  /** 
  * gloadbal Windows Instance handle for the DSM DLL... 
  */
  HINSTANCE g_hinstance = (HINSTANCE)GetCurrentModule();
#endif

  HWND g_hwndDLG = NULL;     


//////////////////////////////////////////////////////////////////////////////
// This is the main entry point. This function is dlsym'd by the DSM.

#ifdef TWH_CMP_MSC
TW_UINT16 FAR PASCAL
#else
FAR PASCAL TW_UINT16 
#endif
DS_Entry( pTW_IDENTITY _pOrigin,
          TW_UINT32    _DG,
          TW_UINT16    _DAT,
          TW_UINT16    _MSG,
          TW_MEMREF    _pData)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());  //很重要，导出函数必须添加这一句
  CTWAINDS_Base* pTWAINLayer = 0;

  if(_pOrigin)
  {
    lstDS::iterator llIter=g_lstDS.begin();
    for(;llIter!=g_lstDS.end();llIter++)
    {
      if((*llIter).AppId.Id==_pOrigin->Id)
      {
        pTWAINLayer=(*llIter).pDS;
      }
    }
  }
  // Curently we are not open
  if( 0 == pTWAINLayer )
  {
    // Special case DSM can request to get identity information about 
    // DS before it is open.  In this special case, where the DS is not
    // open, we return this static Idenity.
    if( DG_CONTROL == _DG && DAT_IDENTITY == _DAT && MSG_GET == _MSG )
    {
      // Copy the ID assigned by the DSM eventhough the spec states
      // that the id will not be assigned until MSG_OPENDS
      CTWAINDS_Base::m_TheIdentity.Id = ((pTW_IDENTITY)_pData)->Id;
      memcpy( _pData, &CTWAINDS_Base::m_TheIdentity, sizeof(CTWAINDS_Base::m_TheIdentity) );

      return TWRC_SUCCESS;
    }

    // The DS is not open.  If we get a request to close DS do not open 
    // just to close, instead return that it is success closed.
    if( DG_CONTROL == _DG && DAT_IDENTITY == _DAT && MSG_CLOSEDS == _MSG )
    {
      return TWRC_SUCCESS;
    }

    // Open the DS
    pTWAINLayer = new CTWAINDS_FreeImage(*_pOrigin);
    if( NULL == pTWAINLayer 
     || TWRC_SUCCESS != pTWAINLayer->Initialize())
    {
      // Failed to create the DS 
      //setConditionCode(TWCC_LOWMEMORY);
      if(pTWAINLayer)
      {
        // Created but could not Initialize
        delete pTWAINLayer;
      }
      return TWRC_FAILURE;
    }
    DS_inst _DS;
    _DS.pDS = pTWAINLayer;
    _DS.AppId = *_pOrigin;
    g_lstDS.push_back(_DS);

  }

  // If we were not open before, we are now, so continue with the TWAIN call
  TW_INT16 result = pTWAINLayer->DS_Entry(_pOrigin, _DG, _DAT, _MSG, _pData);

  /**
  * Special case - free memory if closing DS 
  * @todo keep track of what apps are connecting to the ds and only 
  * delete when count goes down to 0
  */
  if( TWRC_SUCCESS == result && 
      DG_CONTROL == _DG && DAT_IDENTITY == _DAT && MSG_CLOSEDS == _MSG &&
      NULL != pTWAINLayer )
  {
    lstDS::iterator llIter=g_lstDS.begin();
    for(;llIter!=g_lstDS.end();)
    {
      if((*llIter).AppId.Id==_pOrigin->Id)
      {
        delete  (*llIter).pDS;
        llIter = g_lstDS.erase(llIter);
        continue;
      }
      llIter++;
    }
  }

  return result;
}


