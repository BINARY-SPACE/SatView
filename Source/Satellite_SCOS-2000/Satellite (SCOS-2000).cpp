// SATELLITE (SCOS-2000).CPP : Satellite Database Driver (SCOS-2000).
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of a SCOS-2000 derived
// database driver related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2013/03/06 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#define LIBRARYENVIRONMENT
#define SATELLITESCOS2000ENVIRONMENT

#include "Satellite (SCOS-2000).h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CSatelliteSCOS2000LibraryApp  cSatelliteSCOS2000LibraryApp;



/////////////////////////////////////////////////////////////////////////////
// CSatelliteSCOS2000DatabaseEngine

/* class CSatelliteSCOS2000DatabaseEngine : public CSCOS2000DatabaseEngine
This class defines the deviative behavior compared to the one defined in the base class;
overwrite the corresponding virtual functions in order to implement the desired satellite
specific behavior.
Contact support@binary-space.com for examples.
*/


/////////////////////////////////////////////////////////////////////////////
// CSatelliteSCOS2000MemoryDumpsServiceEngine

/* class CSatelliteSCOS2000MemoryDumpsServiceEngine : public CSCOS2000MemoryDumpsServiceEngine
This class defines the memory dump processing capabilities of the satellite i.e.
identifies & specifies the available dumps, associates them with the telemetry data and
provides ways to format/save them to an archive.
Contact support@binary-space.com for examples.
*/


/////////////////////////////////////////////////////////////////////////////
// CSatelliteSCOS2000TPEPServiceEngine

/*class CSatelliteSCOS2000TPEPServiceEngine : public CSCOS2000TPEPServiceEngine
This class implements the 'Telemetry Parameter Export Protocol' (TPEP) i.e.
adds the capability to exchange telemetry packets or parameters with other
(non-Windows®) systems via TPEP over TCP/IP.
Contact support@binary-space.com for examples.
*/


/////////////////////////////////////////////////////////////////////////////
// CSatelliteSCOS2000PFLPServiceEngine

/* CSatelliteSCOS2000PFLPServiceEngine : public CSCOS2000PFLPServiceEngine
This class implements the 'Packet Front-End Link Protocol' (PFLP) i.e.
adds the capability to distribute telemetry packets via PFLP over TCP/IP.
Contact support@binary-space.com for examples.
*/


/////////////////////////////////////////////////////////////////////////////
// CSatelliteSCOS2000TMProcessInfo

/* CSatelliteSCOS2000TMProcessInfo : public CSCOS2000TMProcessInfo
This class defines the auxiliary data that is related to the telemetry data
processing (e.g. counters, OBRTs). It is automatically allocated as a member
of CSatelliteSCOS2000TMProcessEngine.
Contact support@binary-space.com for more information.
*/


/////////////////////////////////////////////////////////////////////////////
// CSatelliteSCOS2000TMProcessEngine

/*class CSatelliteSCOS2000TMProcessEngine : public CSCOS2000TMProcessEngine
This class defines the telemetry data processing i.e. the decoding of the telemetry packets,
processing of the parameters (incl. limit checking & derived parameters) and also implements
the time correlation.
Contact support@binary-space.com for more information.
*/


/////////////////////////////////////////////////////////////////////////////
// CSatelliteSCOS2000TCProcessInfo

/* CSatelliteSCOS2000TCProcessInfo : public CSCOS2000TCProcessInfo
This class defines the auxiliary data that is related to the telecommand data
processing (e.g. counters, OBRTs). It is automatically allocated as a member
of CSatelliteSCOS2000TCProcessEngine.
Contact support@binary-space.com for more information.
*/


/////////////////////////////////////////////////////////////////////////////
// CSatelliteSCOS2000TCProcessEngine

/*class CSatelliteSCOS2000TCProcessEngine : public CSCOS2000TCProcessEngine
This class defines the telecommand data processing i.e. the encoding of the telecommand packets,
resp. their paramters (incl. limit checking) and also implements functions handling the
commands for on-board memory diagnostics, on-board buffers, memory patch generations and
time correlation.
Contact support@binary-space.com for more information.
*/


/////////////////////////////////////////////////////////////////////////////
// CSatelliteSCOS2000LibraryApp

BOOL CSatelliteSCOS2000LibraryApp::InitInstance()
{
	return((CSCOS2000LibraryApp::InitInstance()) ? LoadStrings() : FALSE);
}

int CSatelliteSCOS2000LibraryApp::ExitInstance()
{
	FreeStrings();
	return CSCOS2000LibraryApp::ExitInstance();
}

CDatabaseEngine *CSatelliteSCOS2000LibraryApp::GetDatabaseEngine() CONST
{
	return(&cSatelliteSCOS2000LibraryApp.m_cDatabaseEngine);
}

CTMProcessEngine *CSatelliteSCOS2000LibraryApp::GetTMProcessEngine() CONST
{
	return(&cSatelliteSCOS2000LibraryApp.m_cTMProcessEngine);
}

CTCProcessEngine *CSatelliteSCOS2000LibraryApp::GetTCProcessEngine() CONST
{
	return(&cSatelliteSCOS2000LibraryApp.m_cTCProcessEngine);
}

CMemoryDumpsServiceEngine *CSatelliteSCOS2000LibraryApp::GetMemoryDumpsServiceEngine() CONST
{
	return(&cSatelliteSCOS2000LibraryApp.m_cMemoryDumpsServiceEngine);
}

CTPEPServiceEngine *CSatelliteSCOS2000LibraryApp::GetTPEPServiceEngine() CONST
{
	return(&cSatelliteSCOS2000LibraryApp.m_cTPEPServiceEngine);
}

CPFLPServiceEngine *CSatelliteSCOS2000LibraryApp::GetPFLPServiceEngine() CONST
{
	return(&cSatelliteSCOS2000LibraryApp.m_cPFLPServiceEngine);
}

CSatelliteSCOS2000LibraryApp *CSatelliteSCOS2000LibraryApp::GetLibraryApp()
{
	return(&cSatelliteSCOS2000LibraryApp);
}

__declspec(dllexport) CDatabaseEngine *GetDatabaseEngineProc()
{
	return GetDatabaseEngine();
}
__declspec(dllexport) CTMProcessEngine *GetTMProcessEngineProc()
{
	return GetTMProcessEngine();
}
__declspec(dllexport) CTCProcessEngine *GetTCProcessEngineProc()
{
	return GetTCProcessEngine();
}
__declspec(dllexport) CMemoryDumpsServiceEngine *GetMemoryDumpsServiceEngineProc()
{
	return GetMemoryDumpsServiceEngine();
}
__declspec(dllexport) CTPEPServiceEngine *GetTPEPServiceEngineProc()
{
	return GetTPEPServiceEngine();
}
__declspec(dllexport) CPFLPServiceEngine *GetPFLPServiceEngineProc()
{
	return GetPFLPServiceEngine();
}

BEGIN_MESSAGE_MAP(CSatelliteSCOS2000LibraryApp, CSCOS2000LibraryApp)
	//{{AFX_MSG_MAP(CSatelliteSCOS2000LibraryApp)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSatelliteSCOS2000LibraryApp message handlers
