// SATELLITE (ALTEL).H : Satellite Database Driver (ALTEL).
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the ALTEL compatible satellite database
// driver related interface declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2013/03/06 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __SATELLITE_ALTEL_H__
#define __SATELLITE_ALTEL_H__

#ifndef RC_INVOKED
#include "ALTEL.h"
#endif

#include "resource.h"		// main symbols
#include "Satellite (ALTEL).rh"


/////////////////////////////////////////////////////////////////////////////
// CSatelliteALTELDatabaseEngine

class CSatelliteALTELDatabaseEngine : public CALTELDatabaseEngine
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
// CSatelliteALTELMemoryDumpsServiceEngine

class CSatelliteALTELMemoryDumpsServiceEngine : public CALTELMemoryDumpsServiceEngine
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
// CSatelliteALTELTPEPServiceEngine

class CSatelliteALTELTPEPServiceEngine : public CALTELTPEPServiceEngine
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
// CSatelliteALTELPFLPServiceEngine

class CSatelliteALTELPFLPServiceEngine : public CALTELPFLPServiceEngine
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
// CSatelliteALTELTMProcessInfo

class CSatelliteALTELTMProcessInfo : public CALTELTMProcessInfo
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
// CSatelliteALTELTMProcessEngine

class CSatelliteALTELTMProcessEngine : public CALTELTMProcessEngine
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
// CSatelliteALTELTCProcessInfo

class CSatelliteALTELTCProcessInfo : public CALTELTCProcessInfo
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
// CSatelliteALTELTCProcessEngine

class CSatelliteALTELTCProcessEngine : public CALTELTCProcessEngine
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
// CSatelliteALTELLibraryApp application

class CSatelliteALTELLibraryApp : public CALTELLibraryApp
{
	// Construction
public:

	// Attributes
public:
	CSatelliteALTELDatabaseEngine  m_cDatabaseEngine;
	CSatelliteALTELTMProcessEngine  m_cTMProcessEngine;
	CSatelliteALTELTCProcessEngine  m_cTCProcessEngine;
	CSatelliteALTELMemoryDumpsServiceEngine  m_cMemoryDumpsServiceEngine;
	CSatelliteALTELTPEPServiceEngine  m_cTPEPServiceEngine;
	CSatelliteALTELPFLPServiceEngine  m_cPFLPServiceEngine;

	// Operations
public:
	CDatabaseEngine *GetDatabaseEngine() CONST;
	CTMProcessEngine *GetTMProcessEngine() CONST;
	CTCProcessEngine *GetTCProcessEngine() CONST;
	CMemoryDumpsServiceEngine *GetMemoryDumpsServiceEngine() CONST;
	CTPEPServiceEngine *GetTPEPServiceEngine() CONST;
	CPFLPServiceEngine *GetPFLPServiceEngine() CONST;

	static CSatelliteALTELLibraryApp *GetLibraryApp();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSatelliteALTELLibraryApp)
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSatelliteALTELLibraryApp)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

// Specify the associated inline definitions
#ifdef SATELLITEALTELENVIRONMENT
inline CDatabaseEngine *GetDatabaseEngine()
{
	return(CSatelliteALTELLibraryApp::GetLibraryApp()->GetDatabaseEngine());
}
inline CTMProcessEngine *GetTMProcessEngine()
{
	return(CSatelliteALTELLibraryApp::GetLibraryApp()->GetTMProcessEngine());
}
inline CTCProcessEngine *GetTCProcessEngine()
{
	return(CSatelliteALTELLibraryApp::GetLibraryApp()->GetTCProcessEngine());
}
inline CMemoryDumpsServiceEngine *GetMemoryDumpsServiceEngine()
{
	return(CSatelliteALTELLibraryApp::GetLibraryApp()->GetMemoryDumpsServiceEngine());
}
inline CTPEPServiceEngine *GetTPEPServiceEngine()
{
	return(CSatelliteALTELLibraryApp::GetLibraryApp()->GetTPEPServiceEngine());
}
inline CPFLPServiceEngine *GetPFLPServiceEngine()
{
	return(CSatelliteALTELLibraryApp::GetLibraryApp()->GetPFLPServiceEngine());
}
inline LPCTSTR STRING(INT nID)
{
	return(CSatelliteALTELLibraryApp::GetLibraryApp()->String(nID));
}
inline TCHAR STRINGCHAR(INT nID)
{
	return(CSatelliteALTELLibraryApp::GetLibraryApp()->StringChar(nID));
}
inline LPCTSTR GetLibraryName()
{
	return(CSatelliteALTELLibraryApp::GetLibraryApp()->GetLibraryName());
}
inline HINSTANCE GetLibraryInstance()
{
	return(CSatelliteALTELLibraryApp::GetLibraryApp()->GetLibraryInstance());
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


#endif // __SATELLITE_ALTEL_H__
