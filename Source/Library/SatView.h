// SATVIEW.H : SatView Library.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the library related interface declaration
// and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1995/04/02 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __SATVIEW_H__
#define __SATVIEW_H__

#define _USE_MATH_DEFINES
#define SOCKET_MFC_EXTENSTIONS
#define SECURITY_WIN32

#ifndef RC_INVOKED
#include <afxwin.h>
#include <afxext.h>
#include <afxvisualmanager.h>
#include <afxwinappex.h>
#include <afxdialogex.h>
#include <afxframewndex.h>
#include <afxmdiframewndex.h>
#include <afxmdichildwndex.h>
#include <afxpropertysheet.h>
#include <afxpropertypage.h>
#include <afxheaderctrl.h>
#include <afxctl.h>
#include <afxdisp.h>
#include <afxinet.h>
#include <afxpriv.h>
#include <afxcmn.h>
#include <afxdb.h>
#include <afxmt.h>

#include <atlenc.h>
#include <atlfile.h>
#include <atlsocket.h>
#include <atlsecurity.h>

#include <cryptuiapi.h>

#include <comdef.h>

#include <evntprov.h>

#include <locale.h>

#include <lmaccess.h>
#include <lmapibuf.h>
#include <lmerr.h>

#include <math.h>
#include <float.h>

#include <mmsystem.h>

#include <richole.h>
#include <tom.h>

#include <sddl.h>

#include <sapi.h>
#pragma warning(push)
#pragma warning(disable: 4996)
#include <sphelper.h>
#pragma warning(pop)

#include <schannel.h>
#include <security.h>
#include <sspi.h>

#include <windns.h>
#include <wininet.h>
#include <winioctl.h>

#include <ws2tcpip.h>


#include "audio.h"
#include "books.h"
#include "email.h"
#include "event.h"
#include "mutex.h"
#include "token.h"
#include "tools.h"
#include "views.h"
#include "macros.h"
#include "mimics.h"
#include "thread.h"
#include "archive.h"
#include "devices.h"
#include "jscript.h"
#include "logfile.h"
#include "network.h"
#include "timekey.h"
#include "version.h"
#include "accounts.h"
#include "controls.h"
#include "database.h"
#include "eventlog.h"
#include "language.h"
#include "messages.h"
#include "profiles.h"
#include "registry.h"
#include "security.h"
#include "assistant.h"
#include "documents.h"
#include "ttcprocess.h"
#include "tcprocedures.h"
#endif

#ifndef LIBRARYENVIRONMENT
#include "strings.h"
#endif

#include "resource.h"		// main symbols


/////////////////////////////////////////////////////////////////////////////
// CLibraryApp application

class AFX_EXT_CLASS CLibraryApp : public CWinAppEx
{
	// Construction
public:
	CLibraryApp();

	// Attributes
protected:
	LPTSTR  *m_pStringTable;
	LPINT  m_pStringIDTable;
	INT  m_nStringCount;

	// Operations
public:
	LPCTSTR String(INT nID) CONST;
	TCHAR StringChar(INT nID) CONST;

	LPCTSTR GetLibraryName() CONST;
	HINSTANCE GetLibraryInstance() CONST;

	static CLibraryApp *GetLibraryApp();

protected:
	BOOL LoadStrings();
	VOID FreeStrings();

	INT SearchString(INT nID) CONST;

	static BOOL CALLBACK EnumStrings(HINSTANCE hModule, LPCTSTR pszType, LPTSTR pszName, CLibraryApp *pLibraryApp);
	static BOOL CALLBACK EnumLocaleStrings(HINSTANCE hModule, LPCTSTR pszType, LPCTSTR pszName, WORD wLanguageID, CLibraryApp *pLibraryApp);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLibraryApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CLibraryApp)
	// NOTE - the ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

// Specify the associated inline definitions
#ifdef USELIBRARYSTRINGS
inline LPCTSTR STRING(INT nID)
{
	return(CLibraryApp::GetLibraryApp()->String(nID));
}
inline TCHAR STRINGCHAR(INT nID)
{
	return(CLibraryApp::GetLibraryApp()->StringChar(nID));
}
#endif
#ifndef LIBRARYENVIRONMENT
#ifndef SPACEENGINEENVIRONMENT
inline LPCTSTR GetLibraryName()
{
	return(CLibraryApp::GetLibraryApp()->GetLibraryName());
}
inline HINSTANCE GetLibraryInstance()
{
	return(CLibraryApp::GetLibraryApp()->GetLibraryInstance());
}
#endif
#endif

/////////////////////////////////////////////////////////////////////////////


#endif // __SATVIEW_H__
