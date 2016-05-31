#define TCP_DLL

#include <afxwin.h>
#include <afxext.h>
#include <afxwinappex.h>
#include <afxdialogex.h>
#include <afxcontrolbars.h>
#include <afxheaderctrl.h>
#include <afxctl.h>
#include <afxdisp.h>
#include <afxrich.h>
#include <afxdb.h>
#include <afxmt.h>

#include <atlsecurity.h>

#include <evntprov.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <float.h>

#include "tcprocedures.h"

#include "Spacecraft.h"


__declspec(dllimport) double CalculateSpacecraftOrbitLongitude(LPCTSTR pszSpacecraft,UINT nNORADID,CONST CTimeKey &tTime);
__declspec(dllimport) double CalculateSpacecraftOrbitLatitude(LPCTSTR pszSpacecraft,UINT nNORADID,CONST CTimeKey &tTime);
__declspec(dllimport) double CalculateSpacecraftOrbitAltitude(LPCTSTR pszSpacecraft,UINT nNORADID,CONST CTimeKey &tTime);
__declspec(dllimport) double CalculateSpacecraftOrbitVelocity(LPCTSTR pszSpacecraft,UINT nNORADID,CONST CTimeKey &tTime);
__declspec(dllimport) CSpacecraftPosition CalculateSpacecraftPosition(LPCTSTR pszSpacecraft,UINT nNORADID,CONST CTimeKey &tTime);
__declspec(dllimport) CSpacecraftVelocity CalculateSpacecraftVelocity(LPCTSTR pszSpacecraft,UINT nNORADID,CONST CTimeKey &tTime);
__declspec(dllimport) TIMETAG CalculateSpacecraftPassStartTime(LPCTSTR pszSpacecraft,UINT nNORADID,LPCTSTR pszLocation,double fLocationLongitude,double fLocationLatitude,double fLocationAltitude,CONST CTimeKey &tStartTime,CONST CTimeSpan &tInterval);
__declspec(dllimport) TIMETAG CalculateSpacecraftPassStopTime(LPCTSTR pszSpacecraft,UINT nNORADID,LPCTSTR pszLocation,double fLocationLongitude,double fLocationLatitude,double fLocationAltitude,CONST CTimeKey &tStartTime,CONST CTimeSpan &tInterval);
__declspec(dllimport) TIMETAG CalculateSpacecraftInterlinkStartTime(LPCTSTR pszSpacecraftA,UINT nNORADIDA,LPCTSTR pszSpacecraftB,UINT nNORADIDB,CONST CTimeKey &tStartTime,CONST CTimeSpan &tInterval);
__declspec(dllimport) TIMETAG CalculateSpacecraftInterlinkStopTime(LPCTSTR pszSpacecraftA,UINT nNORADIDA,LPCTSTR pszSpacecraftB,UINT nNORADIDB,CONST CTimeKey &tStartTime,CONST CTimeSpan &tInterval);
__declspec(dllimport) TIMETAG CalculateSpacecraftInterlinkStartTime(LPCTSTR pszSpacecraftA,UINT nNORADIDA,LPCTSTR pszSpacecraftVia,UINT nNORADIDVia,LPCTSTR pszSpacecraftB,UINT nNORADIDB,CONST CTimeKey &tStartTime,CONST CTimeSpan &tInterval);
__declspec(dllimport) TIMETAG CalculateSpacecraftInterlinkStopTime(LPCTSTR pszSpacecraftA,UINT nNORADIDA,LPCTSTR pszSpacecraftVia,UINT nNORADIDVia,LPCTSTR pszSpacecraftB,UINT nNORADIDB,CONST CTimeKey &tStartTime,CONST CTimeSpan &tInterval);


%s%s%s%s%sstatic CUIntArray  __nSourceCodeLines_%s[2];



%sclass CTCProcedureProcessManager_%s : public CTCProcedureProcessManager
{
private:
	virtual CTCProcedureProcess *AllocateProcess(LPCTSTR pszName,INT nProcedureID,INT nProcessID,CTCProcessEngine *pTCProcessEngine,CTCEnvironment *pTCEnvironment);
	virtual CTCProcedureThread *AllocateThread(LPCTSTR pszName,CONST CDatabaseEngine *pDatabase,CTCProcessEngine *pTCProcessEngine,CTCEnvironment *pTCEnvironment,HANDLE hTMEvent,HANDLE hTCEvent,HANDLE hUpdate,HANDLE hExit);
};


class CTCProcedureProcess_%s : public CTCProcedureProcess
{
public:
	CTCProcedureProcess_%s(LPCTSTR pszName,INT nProcedureID,INT nID,CTCProcessEngine *pTCProcessEngine,CTCEnvironment *pTCEnvironment);

private:
	virtual VOID AssignArguments(CONST CDatabaseTCProcedureArguments &pArguments,va_list pArgumentList);
	virtual VOID AssignArguments(CONST CDatabaseTCProcedureArguments &pArguments);
	virtual VOID AssignVariables();

	virtual INT EnumIdentifiers(CStringArray &szIdentifiers,CUIntArray &nIdentifierTypes,CLongUIntArray &nIdentifierAttributes,CPtrArray &pIdentifiers) CONST;
	virtual INT EnumSynchronizationObjects(CStringArray &szObjects,CPtrArray &phObjects) CONST;
};

static INT TranslateLineNumber(INT nNumber);
%s

CTCProcedureProcess *CTCProcedureProcessManager_%s::AllocateProcess(LPCTSTR pszName,INT nProcedureID,INT nProcessID,CTCProcessEngine *pTCProcessEngine,CTCEnvironment *pTCEnvironment)
{
  return new CTCProcedureProcess_%s(pszName,nProcedureID,nProcessID,pTCProcessEngine,pTCEnvironment);
}

CTCProcedureThread *CTCProcedureProcessManager_%s::AllocateThread(LPCTSTR pszName,CONST CDatabaseEngine *pDatabase,CTCProcessEngine *pTCProcessEngine,CTCEnvironment *pTCEnvironment,HANDLE hTMEvent,HANDLE hTCEvent,HANDLE hUpdate,HANDLE hExit)
{
  %sreturn((CTCProcedureThread *) NULL);
}


CTCProcedureProcess_%s::CTCProcedureProcess_%s(LPCTSTR pszName,INT nProcedureID,INT nID,CTCProcessEngine *pTCProcessEngine,CTCEnvironment *pTCEnvironment) : CTCProcedureProcess(pszName,nProcedureID,nID,pTCProcessEngine,pTCEnvironment)
{
  return;
}

VOID CTCProcedureProcess_%s::AssignArguments(CONST CDatabaseTCProcedureArguments &pArguments,va_list pArgumentList)
{
  %sreturn;
}
VOID CTCProcedureProcess_%s::AssignArguments(CONST CDatabaseTCProcedureArguments &pArguments)
{
  INT  __nArgument;
  INT  __nArguments;
  CString  __szMessage;
  CDatabaseTCProcedureArgument  *__pArgument;

  for (__nArgument = 0,__nArguments = (INT) pArguments.GetSize(); __nArgument < __nArguments; __nArgument++)
  { if ((__pArgument = pArguments.GetAt(__nArgument)) &&  __pArgument -> GetConstValueAsText().IsEmpty())
    { __szMessage.Format(TEXT("The argument '%s' has no value."),(LPCTSTR) __pArgument -> GetTag());
      ReportWarningMessage(__szMessage);
    }
  }
  %sreturn;
}

VOID CTCProcedureProcess_%s::AssignVariables()
{
  %sreturn;
}

INT CTCProcedureProcess_%s::EnumIdentifiers(CStringArray &szIdentifiers,CUIntArray &nIdentifierTypes,CLongUIntArray &nIdentifierAttributes,CPtrArray &pIdentifiers) CONST
{
  szIdentifiers.RemoveAll();
  nIdentifierTypes.RemoveAll();
  nIdentifierAttributes.RemoveAll();
  pIdentifiers.RemoveAll();%s
  return((INT) szIdentifiers.GetSize());
}

INT CTCProcedureProcess_%s::EnumSynchronizationObjects(CStringArray &szObjects,CPtrArray &phObjects) CONST
{
  szObjects.RemoveAll();
  phObjects.RemoveAll();%s
  return((INT) szObjects.GetSize());
}


static CTCProcedureProcessManager_%s  cTCProcedureProcessManager;


static INT TranslateLineNumber(INT nLine)
{
  INT  nIndex;
  INT  nCount;

  for (nIndex = 0,nCount = (__nSourceCodeLines_%s[0].GetSize() == __nSourceCodeLines_%s[1].GetSize()) ? (INT) __nSourceCodeLines_%s[0].GetSize():0; nIndex < nCount; nIndex++)
  { if (__nSourceCodeLines_%s[0].GetAt(nIndex) == (UINT) nLine) break;
    continue;
  }
  return((nIndex < nCount) ? __nSourceCodeLines_%s[1].GetAt(nIndex):-1);
}



extern "C"
{
__declspec(dllexport) BOOL Initialize(CONST CDatabaseEngine *pDatabase,CTCProcessEngine *pTCProcessEngine,CTCEnvironment *pTCEnvironment,LPCTSTR pszName,INT nProcedureID,INT nProcessID,UINT nExecutionMode,BOOL bSynchronized,CONST CPtrArray &hEvents,CStringArray &szErrorParameters);
__declspec(dllexport) BOOL InitializeParameters(INT nProcessID,CONST CTMParameters &pTMParameters,double fTotalTMBandwidth,double fAvailableTMBandwidth,double fMaxDiagnosticTMBandwidth,double fAvailableDiagnosticTMBandwidth,CONST CTimeTag &tTMBandwidth);
__declspec(dllexport) BOOL Run(INT nProcessID,va_list pArgumentList,UINT nExecutionMode);
__declspec(dllexport) BOOL Start(INT nProcessID,CONST CDatabaseTCProcedureArguments &pArguments,UINT nExecutionMode);
__declspec(dllexport) BOOL Update(INT nProcessID,CONST CTMEnvironment *pTMEnvironment);
__declspec(dllexport) BOOL Suspend(INT nProcessID);
__declspec(dllexport) BOOL IsSuspended(INT nProcessID);
__declspec(dllexport) BOOL Resume(INT nProcessID,BOOL bAuto=TRUE);
__declspec(dllexport) BOOL IsRunning(INT nProcessID);
__declspec(dllexport) BOOL Terminate(INT nProcessID,BOOL bAuto=TRUE);
__declspec(dllexport) BOOL Abort(INT nProcessID);

__declspec(dllexport) INT EnumIdentifiers(INT nProcessID,CStringArray &szIdentifiers,CUIntArray &nIdentifierTypes,CLongUIntArray &nIdentifierAttributes,CPtrArray &pIdentifiers);

__declspec(dllexport) BOOL UpdateThreadBreakpoints(INT nProcessID,LPCTSTR pszThread,CONST CDatabaseTCProcedureThreadBreakpoints &pBreakpoints);

__declspec(dllexport) INT CheckThreadExecutionState(INT nProcessID,LPCTSTR pszThread,UINT &nState,CStringArray &szStepNames,CUIntArray &nStepStates,UINT &nLine);
__declspec(dllexport) BOOL AcknowledgeThreadExecutionState(INT nProcessID,LPCTSTR pszThread);

__declspec(dllexport) BOOL InitThreadTCFunction(INT nProcessID,LPCTSTR pszThread,LPCTSTR pszStep,INT nEntry,BOOL bExpanded,CDatabaseTCFunction *pTCFunction,CDatabaseTCPacket *pTCPacket,CString &szMemoryPatch,BOOL bAllowAuthorization);
__declspec(dllexport) BOOL EnumThreadTCFunctionExecutionVerificationTimeWindows(INT nProcessID,LPCTSTR pszThread,LPCTSTR pszStep,INT nEntry,CUIntArray &nStageIDs,CUIntArray &nStageTimeWindowOffsets,CUIntArray &nStageTimeWindowSizes,CUIntArray &nStageTimeWindowUncertainties);
__declspec(dllexport) BOOL CheckThreadTCFunctionPreexecutionExpression(INT nProcessID,LPCTSTR pszThread,LPCTSTR pszStep,INT nEntry,CStringArray &szParameters);
__declspec(dllexport) BOOL CheckThreadTCFunctionExecutionExpression(INT nProcessID,LPCTSTR pszThread,LPCTSTR pszStep,INT nEntry,CONST CDatabaseTCFunction *pTCFunction,UINT nStageID,CONST CTimeTag &tStageStart,CONST CTimeSpan &tUncertainty,CStringArray &szParameters);

__declspec(dllexport) BOOL HasThreadOpenDialogs(INT nProcessID,LPCTSTR pszThread);

__declspec(dllexport) BOOL CheckSourceCodeVersion(LPCTSTR pszSourceCode);
}

__declspec(dllexport) BOOL Initialize(CONST CDatabaseEngine *pDatabase,CTCProcessEngine *pTCProcessEngine,CTCEnvironment *pTCEnvironment,LPCTSTR pszName,INT nProcedureID,INT nProcessID,UINT nExecutionMode,BOOL bSynchronized,CONST CPtrArray &hEvents,CStringArray &szErrorParameters)
{
  CStringArray  szErrors;

  %s%sif (cTCProcedureProcessManager.Initialize(pDatabase,pTCProcessEngine,pTCEnvironment,pszName,nProcedureID,nProcessID,nExecutionMode,bSynchronized,hEvents,szErrorParameters))
  { %sszErrorParameters.Append(szErrors);
    return((!szErrorParameters.GetSize()) ? TRUE:FALSE);
  }
  szErrorParameters.Append(szErrors);
  return FALSE;
}

__declspec(dllexport) BOOL InitializeParameters(INT nProcessID,CONST CTMParameters &pTMParameters,double fTotalTMBandwidth,double fAvailableTMBandwidth,double fMaxDiagnosticTMBandwidth,double fAvailableDiagnosticTMBandwidth,CONST CTimeTag &tTMBandwidth)
{
  return cTCProcedureProcessManager.InitializeParameters(nProcessID,pTMParameters,fTotalTMBandwidth,fAvailableTMBandwidth,fMaxDiagnosticTMBandwidth,fAvailableDiagnosticTMBandwidth,tTMBandwidth);
}

__declspec(dllexport) BOOL Run(INT nProcessID,va_list pArgumentList,UINT nExecutionMode)
{
  return cTCProcedureProcessManager.Run(nProcessID,pArgumentList,nExecutionMode);
}

__declspec(dllexport) BOOL Start(INT nProcessID,CONST CDatabaseTCProcedureArguments &pArguments,UINT nExecutionMode)
{
  return cTCProcedureProcessManager.Start(nProcessID,pArguments,nExecutionMode);
}

__declspec(dllexport) BOOL Update(INT nProcessID,CONST CTMEnvironment *pTMEnvironment)
{
  return cTCProcedureProcessManager.Update(nProcessID,pTMEnvironment);
}

__declspec(dllexport) BOOL Suspend(INT nProcessID)
{
  return cTCProcedureProcessManager.Suspend(nProcessID);
}

__declspec(dllexport) BOOL IsSuspended(INT nProcessID)
{
  return cTCProcedureProcessManager.IsSuspended(nProcessID);
}

__declspec(dllexport) BOOL Resume(INT nProcessID,BOOL bAuto)
{
  return cTCProcedureProcessManager.Resume(nProcessID,bAuto);
}

__declspec(dllexport) BOOL IsRunning(INT nProcessID)
{
  return cTCProcedureProcessManager.IsRunning(nProcessID);
}

__declspec(dllexport) BOOL Terminate(INT nProcessID,BOOL bAuto)
{
  return cTCProcedureProcessManager.Terminate(nProcessID,bAuto);
}

__declspec(dllexport) BOOL Abort(INT nProcessID)
{
  return cTCProcedureProcessManager.Abort(nProcessID);
}

__declspec(dllexport) INT EnumIdentifiers(INT nProcessID,CStringArray &szIdentifiers,CUIntArray &nIdentifierTypes,CLongUIntArray &nIdentifierAttributes,CPtrArray &pIdentifiers)
{
  return cTCProcedureProcessManager.EnumIdentifiers(nProcessID,szIdentifiers,nIdentifierTypes,nIdentifierAttributes,pIdentifiers);
}

__declspec(dllexport) BOOL UpdateThreadBreakpoints(INT nProcessID,LPCTSTR pszThread,CONST CDatabaseTCProcedureThreadBreakpoints &pBreakpoints)
{
  return cTCProcedureProcessManager.UpdateThreadBreakpoints(nProcessID,pszThread,pBreakpoints);
}

__declspec(dllexport) INT CheckThreadExecutionState(INT nProcessID,LPCTSTR pszThread,UINT &nState,CStringArray &szStepNames,CUIntArray &nStepStates,UINT &nLine)
{
  return cTCProcedureProcessManager.EnumThreadStepStates(nProcessID,pszThread,nState,szStepNames,nStepStates,nLine);
}

__declspec(dllexport) BOOL AcknowledgeThreadExecutionState(INT nProcessID,LPCTSTR pszThread)
{
  return cTCProcedureProcessManager.AcknowledgeThreadStepState(nProcessID,pszThread);
}

__declspec(dllexport) BOOL InitThreadTCFunction(INT nProcessID,LPCTSTR pszThread,LPCTSTR pszStep,INT nEntry,BOOL bExpanded,CDatabaseTCFunction *pTCFunction,CDatabaseTCPacket *pTCPacket,CString &szMemoryPatch,BOOL bAllowAuthorization)
{
  return cTCProcedureProcessManager.InitThreadTCFunction(nProcessID,pszThread,pszStep,nEntry,bExpanded,pTCFunction,pTCPacket,szMemoryPatch,bAllowAuthorization);
}

__declspec(dllexport) BOOL EnumThreadTCFunctionExecutionVerificationTimeWindows(INT nProcessID,LPCTSTR pszThread,LPCTSTR pszStep,INT nEntry,CUIntArray &nStageIDs,CUIntArray &nStageTimeWindowOffsets,CUIntArray &nStageTimeWindowSizes,CUIntArray &nStageTimeWindowUncertainties)
{
  return cTCProcedureProcessManager.EnumThreadTCFunctionExecutionVerificationTimeWindows(nProcessID,pszThread,pszStep,nEntry,nStageIDs,nStageTimeWindowOffsets,nStageTimeWindowSizes,nStageTimeWindowUncertainties);
}

__declspec(dllexport) BOOL CheckThreadTCFunctionPreexecutionExpression(INT nProcessID,LPCTSTR pszThread,LPCTSTR pszStep,INT nEntry,CStringArray &szParameters)
{
  return cTCProcedureProcessManager.CheckThreadTCFunctionPreexecutionExpression(nProcessID,pszThread,pszStep,nEntry,szParameters);
}

__declspec(dllexport) BOOL CheckThreadTCFunctionExecutionExpression(INT nProcessID,LPCTSTR pszThread,LPCTSTR pszStep,INT nEntry,CONST CDatabaseTCFunction *pTCFunction,UINT nStageID,CONST CTimeTag &tStageStart,CONST CTimeSpan &tUncertainty,CStringArray &szParameters)
{
  return cTCProcedureProcessManager.CheckThreadTCFunctionExecutionExpression(nProcessID,pszThread,pszStep,nEntry,pTCFunction,nStageID,tStageStart,tUncertainty,szParameters);
}

__declspec(dllexport) BOOL HasThreadOpenDialogs(INT nProcessID,LPCTSTR pszThread)
{
  return cTCProcedureProcessManager.HasThreadOpenDialogs(nProcessID,pszThread);
}

__declspec(dllexport) BOOL CheckSourceCodeVersion(LPCTSTR pszSourceCode)
{
  CString  szSourceCode;

  %sreturn((szSourceCode == pszSourceCode) ? TRUE:FALSE);
}
