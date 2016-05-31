// SATELLITE (SCOS-2000).H : Satellite Database Driver (SCOS-2000).
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the SCOS-2000 compatible satellite
// database driver related interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2013/03/06 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __SATELLITE_SCOS2000_H__
#define __SATELLITE_SCOS2000_H__

#ifndef RC_INVOKED
#include "SCOS-2000.h"
#endif

#include "resource.h"		// main symbols
#include "Satellite (SCOS-2000).rh"


/////////////////////////////////////////////////////////////////////////////
// CSatelliteSCOS2000DatabaseEngine

class CSatelliteSCOS2000DatabaseEngine : public CSCOS2000DatabaseEngine
{
	// Construction
public:

	// Attributes
public:

	// Operations
public:
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSatelliteSCOS2000MemoryDumpsServiceEngine

class CSatelliteSCOS2000MemoryDumpsServiceEngine : public CSCOS2000MemoryDumpsServiceEngine
{
	// Construction
public:

	// Attributes
public:

	// Operators
public:
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSatelliteSCOS2000TPEPServiceEngine

class CSatelliteSCOS2000TPEPServiceEngine : public CSCOS2000TPEPServiceEngine
{
	// Construction
public:

	// Attributes
public:

	// Operators
public:
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSatelliteSCOS2000PFLPServiceEngine

class CSatelliteSCOS2000PFLPServiceEngine : public CSCOS2000PFLPServiceEngine
{
	// Construction
public:

	// Attributes
public:

	// Operators
public:
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSatelliteSCOS2000TMProcessInfo

class CSatelliteSCOS2000TMProcessInfo : public CSCOS2000TMProcessInfo
{
	// Construction
public:

	// Attributes
public:

	// Operations
public:
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSatelliteSCOS2000TMProcessEngine

class CSatelliteSCOS2000TMProcessEngine : public CSCOS2000TMProcessEngine
{
	// Construction
public:

	// Attributes
public:

	// Operations
public:
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSatelliteSCOS2000TCProcessInfo

class CSatelliteSCOS2000TCProcessInfo : public CSCOS2000TCProcessInfo
{
	// Construction
public:

	// Attributes
public:

	// Operations
public:
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSatelliteSCOS2000TCProcessEngine

class CSatelliteSCOS2000TCProcessEngine : public CSCOS2000TCProcessEngine
{
	// Construction
public:

	// Attributes
public:

	// Operations
public:
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSatelliteSCOS2000LibraryApp application

class CSatelliteSCOS2000LibraryApp : public CSCOS2000LibraryApp
{
	// Construction
public:

	// Attributes
public:
	CSatelliteSCOS2000DatabaseEngine  m_cDatabaseEngine;
	CSatelliteSCOS2000TMProcessEngine  m_cTMProcessEngine;
	CSatelliteSCOS2000TCProcessEngine  m_cTCProcessEngine;
	CSatelliteSCOS2000MemoryDumpsServiceEngine  m_cMemoryDumpsServiceEngine;
	CSatelliteSCOS2000TPEPServiceEngine  m_cTPEPServiceEngine;
	CSatelliteSCOS2000PFLPServiceEngine  m_cPFLPServiceEngine;

	// Operations
public:
	CDatabaseEngine *GetDatabaseEngine() CONST;
	CTMProcessEngine *GetTMProcessEngine() CONST;
	CTCProcessEngine *GetTCProcessEngine() CONST;
	CMemoryDumpsServiceEngine *GetMemoryDumpsServiceEngine() CONST;
	CTPEPServiceEngine *GetTPEPServiceEngine() CONST;
	CPFLPServiceEngine *GetPFLPServiceEngine() CONST;

	static CSatelliteSCOS2000LibraryApp *GetLibraryApp();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSatelliteSCOS2000LibraryApp)
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSatelliteSCOS2000LibraryApp)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

// Specify the associated inline definitions
#ifdef SATELLITESCOS2000ENVIRONMENT
inline CDatabaseEngine *GetDatabaseEngine()
{
	return(CSatelliteSCOS2000LibraryApp::GetLibraryApp()->GetDatabaseEngine());
}
inline CTMProcessEngine *GetTMProcessEngine()
{
	return(CSatelliteSCOS2000LibraryApp::GetLibraryApp()->GetTMProcessEngine());
}
inline CTCProcessEngine *GetTCProcessEngine()
{
	return(CSatelliteSCOS2000LibraryApp::GetLibraryApp()->GetTCProcessEngine());
}
inline CMemoryDumpsServiceEngine *GetMemoryDumpsServiceEngine()
{
	return(CSatelliteSCOS2000LibraryApp::GetLibraryApp()->GetMemoryDumpsServiceEngine());
}
inline CTPEPServiceEngine *GetTPEPServiceEngine()
{
	return(CSatelliteSCOS2000LibraryApp::GetLibraryApp()->GetTPEPServiceEngine());
}
inline CPFLPServiceEngine *GetPFLPServiceEngine()
{
	return(CSatelliteSCOS2000LibraryApp::GetLibraryApp()->GetPFLPServiceEngine());
}
inline LPCTSTR STRING(INT nID)
{
	return(CSatelliteSCOS2000LibraryApp::GetLibraryApp()->String(nID));
}
inline TCHAR STRINGCHAR(INT nID)
{
	return(CSatelliteSCOS2000LibraryApp::GetLibraryApp()->StringChar(nID));
}
inline LPCTSTR GetLibraryName()
{
	return(CSatelliteSCOS2000LibraryApp::GetLibraryApp()->GetLibraryName());
}
inline HINSTANCE GetLibraryInstance()
{
	return(CSatelliteSCOS2000LibraryApp::GetLibraryApp()->GetLibraryInstance());
}
#endif

// Specify the associated export definitions
extern "C"
{
	__declspec(dllexport) CDatabaseEngine *GetDatabaseEngineProc();
	__declspec(dllexport) CTMProcessEngine *GetTMProcessEngineProc();
	__declspec(dllexport) CTCProcessEngine *GetTCProcessEngineProc();
	__declspec(dllexport) CMemoryDumpsServiceEngine *GetMemoryDumpsServiceEngineProc();
	__declspec(dllexport) CTPEPServiceEngine *GetTPEPServiceEngineProc();
	__declspec(dllexport) CPFLPServiceEngine *GetPFLPServiceEngineProc();
}

/////////////////////////////////////////////////////////////////////////////


#endif // __SATELLITE_SCOS2000_H__
