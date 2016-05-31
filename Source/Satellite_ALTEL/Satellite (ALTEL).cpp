// SATELLITE (ALTEL).CPP : Satellite Database Driver (ALTEL).
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of an ALTEL derived
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
#define SATELLITEALTELENVIRONMENT

#include "Satellite (ALTEL).h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CSatelliteALTELLibraryApp  cSatelliteALTELLibraryApp;



/////////////////////////////////////////////////////////////////////////////
// CSatelliteALTELDatabaseEngine

/* class CSatelliteALTELDatabaseEngine : public CALTELDatabaseEngine
This class defines the deviative behavior compared to the one defined in the base class;
overwrite the corresponding virtual functions in order to implement the desired satellite
specific behavior.
Contact support@binary-space.com for examples.
*/


/////////////////////////////////////////////////////////////////////////////
// CSatelliteALTELMemoryDumpsServiceEngine

/* class CSatelliteALTELMemoryDumpsServiceEngine : public CALTELMemoryDumpsServiceEngine
This class defines the memory dump processing capabilities of the satellite i.e.
identifies & specifies the available dumps, associates them with the telemetry data and
provides ways to format/save them to an archive.
Contact support@binary-space.com for examples.
*/


/////////////////////////////////////////////////////////////////////////////
// CSatelliteALTELTPEPServiceEngine

/*class CSatelliteALTELTPEPServiceEngine : public CALTELTPEPServiceEngine
This class implements the 'Telemetry Parameter Export Protocol' (TPEP) i.e.
adds the capability to exchange telemetry packets or parameters with other
(non-Windows®) systems via TPEP over TCP/IP.
Contact support@binary-space.com for examples.
*/


/////////////////////////////////////////////////////////////////////////////
// CSatelliteALTELPFLPServiceEngine

/* CSatelliteALTELPFLPServiceEngine : public CALTELPFLPServiceEngine
This class implements the 'Packet Front-End Link Protocol' (PFLP) i.e.
adds the capability to distribute telemetry packets via PFLP over TCP/IP.
Contact support@binary-space.com for examples.
*/


/////////////////////////////////////////////////////////////////////////////
// CSatelliteALTELTMProcessInfo

/* CSatelliteALTELTMProcessInfo : public CALTELTMProcessInfo
This class defines the auxiliary data that is related to the telemetry data
processing (e.g. counters, OBRTs). It is automatically allocated as a member
of CSatelliteALTELTMProcessEngine.
Contact support@binary-space.com for more information.
*/


/////////////////////////////////////////////////////////////////////////////
// CSatelliteALTELTMProcessEngine

/*class CSatelliteALTELTMProcessEngine : public CALTELTMProcessEngine
This class defines the telemetry data processing i.e. the decoding of the telemetry packets,
processing of the parameters (incl. limit checking & derived parameters) and also implements
the time correlation.
Contact support@binary-space.com for more information.
*/


/////////////////////////////////////////////////////////////////////////////
// CSatelliteALTELTCProcessInfo

/* CSatelliteALTELTCProcessInfo : public CALTELTCProcessInfo
This class defines the auxiliary data that is related to the telecommand data
processing (e.g. counters, OBRTs). It is automatically allocated as a member
of CSatelliteALTELTCProcessEngine.
Contact support@binary-space.com for more information.
*/


/////////////////////////////////////////////////////////////////////////////
// CSatelliteALTELTCProcessEngine

/*class CSatelliteALTELTCProcessEngine : public CALTELTCProcessEngine
This class defines the telecommand data processing i.e. the encoding of the telecommand packets,
resp. their paramters (incl. limit checking) and also implements functions handling the
commands for on-board memory diagnostics, on-board buffers, memory patch generations and
time correlation.
Contact support@binary-space.com for more information.
*/


/////////////////////////////////////////////////////////////////////////////
// CSatelliteALTELLibraryApp

BOOL CSatelliteALTELLibraryApp::InitInstance()
{
	return((CALTELLibraryApp::InitInstance()) ? LoadStrings() : FALSE);
}

int CSatelliteALTELLibraryApp::ExitInstance()
{
	FreeStrings();
	return CALTELLibraryApp::ExitInstance();
}

CDatabaseEngine *CSatelliteALTELLibraryApp::GetDatabaseEngine() CONST
{
	return(&cSatelliteALTELLibraryApp.m_cDatabaseEngine);
}

CTMProcessEngine *CSatelliteALTELLibraryApp::GetTMProcessEngine() CONST
{
	return(&cSatelliteALTELLibraryApp.m_cTMProcessEngine);
}

CTCProcessEngine *CSatelliteALTELLibraryApp::GetTCProcessEngine() CONST
{
	return(&cSatelliteALTELLibraryApp.m_cTCProcessEngine);
}

CMemoryDumpsServiceEngine *CSatelliteALTELLibraryApp::GetMemoryDumpsServiceEngine() CONST
{
	return(&cSatelliteALTELLibraryApp.m_cMemoryDumpsServiceEngine);
}

CTPEPServiceEngine *CSatelliteALTELLibraryApp::GetTPEPServiceEngine() CONST
{
	return(&cSatelliteALTELLibraryApp.m_cTPEPServiceEngine);
}

CPFLPServiceEngine *CSatelliteALTELLibraryApp::GetPFLPServiceEngine() CONST
{
	return(&cSatelliteALTELLibraryApp.m_cPFLPServiceEngine);
}

CSatelliteALTELLibraryApp *CSatelliteALTELLibraryApp::GetLibraryApp()
{
	return(&cSatelliteALTELLibraryApp);
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

BEGIN_MESSAGE_MAP(CSatelliteALTELLibraryApp, CALTELLibraryApp)
	//{{AFX_MSG_MAP(CSatelliteALTELLibraryApp)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSatelliteALTELLibraryApp message handlers
