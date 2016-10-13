/**
* @file dllmain.h
* Reveals the main entry point for the DSM
* @author UDS
* @date August 2016
*/

#ifndef __DLLMAIN_H__
#define __DLLMAIN_H__

#include "CTWAINDS_FreeImage.h"

/**
* The main entry point - defined in twain.h
FAR PASCAL TW_UINT16 DS_Entry( pTW_IDENTITY _pOrigin,
                               TW_UINT32    _DG,
                               TW_UINT16    _DAT,
                               TW_UINT16    _MSG,
                               TW_MEMREF    _pData);
*/

#endif //__DLLMAIN_H__