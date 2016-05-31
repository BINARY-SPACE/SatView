// ENERTEC.H : ENERTEC TT&C 3801 Device Driver.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the ENERTEC TT&C 3801 device driver
// related interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2010/12/19 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __ENERTEC_H__
#define __ENERTEC_H__

#ifndef RC_INVOKED
#include <afxsock.h>

#include "SatView.h"
#endif

#include "resource.h"		// main symbols
#include "ENERTEC.rh"

#include "device.h"
#include "dialogs.h"


/////////////////////////////////////////////////////////////////////////////
// CENERTECDeviceApp application

class CENERTECDeviceApp : public CLibraryApp
{
	// Construction
public:

	// Attributes
private:
	CString  m_szHelpFileName;

	// Operations
public:
	INT EnumIODeviceProducts(LPTSTR *ppszProducts = NULL, INT nCount = 0) CONST;
	INT EnumIODeviceProducts(CStringArray &szProducts) CONST;

	CENERTECDevice *GetIODevice() CONST;

	BOOL ShowHelp(LPCTSTR pszTopic);
	BOOL IsHelpAvailable() CONST;

	static CENERTECDeviceApp *GetLibraryApp();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CENERTECDeviceApp)
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CENERTECDeviceApp)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

// Specify the associated inline definitions
inline INT EnumIODeviceProducts(LPTSTR *ppszProducts = NULL, INT nCount = 0)
{
	return(CENERTECDeviceApp::GetLibraryApp()->EnumIODeviceProducts(ppszProducts, nCount));
}
inline INT EnumIODeviceProducts(CStringArray &szProducts)
{
	return(CENERTECDeviceApp::GetLibraryApp()->EnumIODeviceProducts(szProducts));
}
inline CENERTECDevice *GetIODevice()
{
	return(CENERTECDeviceApp::GetLibraryApp()->GetIODevice());
}
inline BOOL ShowHelp(LPCTSTR pszTopic)
{
	return(CENERTECDeviceApp::GetLibraryApp()->ShowHelp(pszTopic));
}
inline BOOL IsHelpAvailable()
{
	return(CENERTECDeviceApp::GetLibraryApp()->IsHelpAvailable());
}
#ifdef USEENERTECDEVICESTRINGS
inline LPCTSTR STRING(INT nID)
{
	return(CENERTECDeviceApp::GetLibraryApp()->String(nID));
}
inline TCHAR STRINGCHAR(INT nID)
{
	return(CENERTECDeviceApp::GetLibraryApp()->StringChar(nID));
}
inline LPCTSTR GetLibraryName()
{
	return(CENERTECDeviceApp::GetLibraryApp()->GetLibraryName());
}
inline HINSTANCE GetLibraryInstance()
{
	return(CENERTECDeviceApp::GetLibraryApp()->GetLibraryInstance());
}
#endif

// Specify the associated export definitions
extern "C"
{
	__declspec(dllexport) INT EnumIODeviceProductsProc(LPTSTR *ppszProducts = NULL, INT nCount = 0);
	__declspec(dllexport) CIODevice *GetIODeviceEngineProc();
}

/////////////////////////////////////////////////////////////////////////////


#endif // __ENERTEC_H__
