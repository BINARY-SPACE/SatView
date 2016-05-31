// MIMICS.H : SatView Mimics Controls Application.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the application related interface
// declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2000/01/01 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __MIMICS_H__
#define __MIMICS_H__

#define _USE_MATH_DEFINES

#ifndef RC_INVOKED
#include <afxwin.h>
#include <afxext.h>
#include <afxwinappex.h>
#include <afxdialogex.h>
#include <afxpropertysheet.h>
#include <afxctl.h>
#include <afxcmn.h>
#include <afxdtctl.h>
#include <afxmt.h>

#include <comdef.h>
#include <locale.h>
#include <atlimage.h>
#include <mmsystem.h>
#include <math.h>
#endif

#include "Mimics.rh"

#include "MimicsIIDs.h"

#include "MimicsTools.h"
#include "MimicsTimeKey.h"
#include "MimicsControls.h"

#include "MimicsCtl.h"
#include "MimicsPpg.h"
#include "MimicsDialogs.h"
#include "MimicsCtlEnum.h"
#include "MimicsLineCtl.h"
#include "MimicsLinePpg.h"
#include "MimicsRectangleCtl.h"
#include "MimicsRectanglePpg.h"
#include "MimicsEllipseCtl.h"
#include "MimicsEllipsePpg.h"
#include "MimicsArcCtl.h"
#include "MimicsArcPpg.h"
#include "MimicsTriangleCtl.h"
#include "MimicsTrianglePpg.h"
#include "MimicsSwitchCtl.h"
#include "MimicsSwitchPpg.h"
#include "MimicsTextCtl.h"
#include "MimicsTextPpg.h"
#include "MimicsImageCtl.h"
#include "MimicsImagePpg.h"
#include "MimicsGroupCtl.h"
#include "MimicsGroupPpg.h"

#include "macros.h"

#include "resource.h"       // main symbols


/////////////////////////////////////////////////////////////////////////////
// CMimicsApp application

class CMimicsApp : public COleControlModule
{
	// Construction
public:
	CMimicsApp();

	// Attributes
public:
	static const GUID CDECL  guidApp;
	static const WORD  wAppVerMajor;
	static const WORD  wAppVerMinor;
private:
	LANGID  m_nLanguageID;
	LPTSTR  *m_pStringTable;
	LPINT  m_pStringIDTable;
	INT  m_nStringCount;

	// Operations
public:
	LPCTSTR String(INT nID) CONST;
	TCHAR StringChar(INT nID) CONST;

	LANGID GetLanguageID() CONST;

	INT GetLocaleData(UINT nDataID, LPVOID pData = NULL, INT cbMax = 0) CONST;
	INT GetLocaleData(LPCTSTR pszDataName, LPVOID pData = NULL, INT cbMax = 0) CONST;

	LPCTSTR GetModuleName() CONST;
	HINSTANCE GetModuleInstance() CONST;

private:
	BOOL LoadStrings();
	VOID FreeStrings();

	INT SearchString(INT nID) CONST;

	static BOOL CALLBACK EnumStrings(HINSTANCE hModule, LPCTSTR pszType, LPTSTR pszName, CMimicsApp *pMimicsApp);
	static BOOL CALLBACK EnumLocaleStrings(HINSTANCE hModule, LPCTSTR pszType, LPCTSTR pszName, WORD wLanguageID, CMimicsApp *pMimicsApp);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMimicsApp)
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMimicsApp)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

// Specify the associated inline definitions
inline CMimicsApp *GetMimicsApp()
{
	return((CMimicsApp *)AfxGetApp());
}
inline LPCTSTR STRING(INT nID)
{
	return(GetMimicsApp()->String(nID));
}
inline TCHAR STRINGCHAR(INT nID)
{
	return(GetMimicsApp()->StringChar(nID));
}
inline LANGID GetLanguageID()
{
	return(GetMimicsApp()->GetLanguageID());
}
inline LPCTSTR GetModuleName()
{
	return(GetMimicsApp()->GetModuleName());
}
inline HINSTANCE GetModuleInstance()
{
	return(GetMimicsApp()->GetModuleInstance());
}

/////////////////////////////////////////////////////////////////////////////


#endif // __MIMICS_H__
