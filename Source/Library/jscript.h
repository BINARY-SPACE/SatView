// JSCRIPT.H : JScript Code Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the automation script related interface
// declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2008/05/10 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __JSCRIPT_H__
#define __JSCRIPT_H__

#include "ttcprocess.h"


/////////////////////////////////////////////////////////////////////////////
// CJScriptTaskScheduler

class CJScriptTaskScheduler : public CObject
{
	// Construction
public:
	CJScriptTaskScheduler();
	~CJScriptTaskScheduler();

	// Attributes
private:
	CStringArray  m_szTelemetryReports;
	CTimeKeyArray  m_tTelemetryReportStartTimes;
	CTimeKeyArray  m_tTelemetryReportIntervals;
	CTimeKeyArray  m_tTelemetryReportStopTimes;
	CDWordArray  m_dwTelemetryReportProcessIDs;
	CUIntArray  m_nTelemetryReportIDs;
private:
	CStringArray  m_szTelemetryDataExtractions;
	CTimeKeyArray  m_tTelemetryDataExtractionScheduleTimes;
	CTimeKeyArray  m_tTelemetryDataExtractionStartTimes;
	CTimeKeyArray  m_tTelemetryDataExtractionStopTimes;
	CDWordArray  m_dwTelemetryDataExtractionProcessIDs;
	CUIntArray  m_nTelemetryDataExtractionIDs;
private:
	CPtrArray  m_pProcessEvents[2];
	CUIntArray  m_nProcessTelemetryReportIDs;
	CUIntArray  m_nProcessTelemetryDataExtractionIDs;
	CDWordArray  m_dwProcessIDs;
private:
	CCriticalSection  *m_pCriticalSection;

	// Operations
public:
	BOOL Initialize(HANDLE hTelemetryReportEvent, HANDLE hTelemetryDataExtractionEvent);
	BOOL Uninitialize();

	INT EnumTelemetryReports(CStringArray &szNames, CUIntArray &nIDs, CTimeKeyArray &tStartTimes, CTimeKeyArray &tIntervals, CTimeKeyArray &tStopTimes) CONST;
	UINT AddTelemetryReport(LPCTSTR pszName, CONST CTimeKey &tStartTime, CONST CTimeSpan &tInterval, CONST CTimeKey &tStopTime);
	BOOL DeleteTelemetryReport(UINT nID);

	INT EnumTelemetryDataExtractions(CStringArray &szNames, CUIntArray &nIDs, CTimeKeyArray &tScheduleTimes, CTimeKeyArray &tStartTimes, CTimeKeyArray &tStopTimes) CONST;
	UINT AddTelemetryDataExtraction(LPCTSTR pszName, CONST CTimeKey &tScheduleTime, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime);
	BOOL DeleteTelemetryDataExtraction(UINT nID);

private:
	BOOL Lock();
	BOOL Unlock();
};

// Specify the associated export definitions
extern "C"
{
	__declspec(dllexport) BOOL InitializeJScriptTaskScheduler(HANDLE hTelemetryReportEvent = NULL, HANDLE hTelemetryDataExtractionEvent = NULL);
	__declspec(dllexport) BOOL UninitializeJScriptTaskScheduler();
	__declspec(dllexport) INT EnumJScriptTaskSchedulerTelemetryReports(LPCWSTR *pszNames[], UINT *nIDs[], TIMEKEY *tStartTimes[], TIMEKEY *tIntervals[], TIMEKEY *tStopTimes[]);
	__declspec(dllexport) UINT AddJScriptTaskSchedulerTelemetryReport(LPCWSTR pszName, TIMEKEY tStartTime, TIMEKEY tInterval, TIMEKEY tStopTime);
	__declspec(dllexport) BOOL DeleteJScriptTaskSchedulerTelemetryReport(UINT nID);
	__declspec(dllexport) INT EnumJScriptTaskSchedulerTelemetryDataExtractions(LPCWSTR *pszNames[], UINT *nIDs[], TIMEKEY *tScheduleTimes[], TIMEKEY *tStartTimes[], TIMEKEY *tStopTimes[]);
	__declspec(dllexport) UINT AddJScriptTaskSchedulerTelemetryDataExtraction(LPCWSTR pszName, TIMEKEY tScheduleTime, TIMEKEY tStartTime, TIMEKEY tStopTime);
	__declspec(dllexport) BOOL DeleteJScriptTaskSchedulerTelemetryDataExtraction(UINT nID);
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CJScriptTelemetryInterface

class CJScriptTelemetryInterface : public CObject
{
	// Construction
public:
	CJScriptTelemetryInterface();
	~CJScriptTelemetryInterface();

	// Attributes
private:
	CPtrArray  m_pDatabases;
	CPtrArray  m_pTMEnvironments;
	CDWordArray  m_dwProcessIDs;
	CStringArray  m_szProcessCounts;
private:
	CCriticalSection  *m_pCriticalSection;

	// Operations
public:
	BOOL Initialize(CONST CDatabaseEngine *pDatabase, CTMEnvironment *pTMEnvironment);
	BOOL Uninitialize();

	BOOL GetParameterIntValue(LPCTSTR pszTag, INT nSample, LONGLONG &nValue) CONST;
	BOOL GetParameterUIntValue(LPCTSTR pszTag, INT nSample, ULONGLONG &nValue) CONST;
	BOOL GetParameterFloatValue(LPCTSTR pszTag, INT nSample, double &fValue) CONST;
	BOOL GetParameterStringValue(LPCTSTR pszTag, INT nSample, CString &szValue) CONST;
	BOOL GetParameterRawIntValue(LPCTSTR pszTag, INT nSample, LONGLONG &nValue) CONST;
	BOOL GetParameterRawUIntValue(LPCTSTR pszTag, INT nSample, ULONGLONG &nValue) CONST;
	BOOL GetParameterRawFloatValue(LPCTSTR pszTag, INT nSample, double &fValue) CONST;
	CTimeTag GetParameterValueTime(LPCTSTR pszTag, INT nSample) CONST;
	BOOL SetParameterPastValueSamples(LPCTSTR pszTag, WORD wSamples);
	WORD GetParameterPastValueSamples(LPCTSTR pszTag) CONST;
	BOOL GetParameterPastIntValue(LPCTSTR pszTag, INT nSample, LONGLONG &nValue) CONST;
	BOOL GetParameterPastUIntValue(LPCTSTR pszTag, INT nSample, ULONGLONG &nValue) CONST;
	BOOL GetParameterPastFloatValue(LPCTSTR pszTag, INT nSample, double &fValue) CONST;
	BOOL GetParameterPastStringValue(LPCTSTR pszTag, INT nSample, CString &szValue) CONST;
	BOOL GetParameterPastRawIntValue(LPCTSTR pszTag, INT nSample, LONGLONG &nValue) CONST;
	BOOL GetParameterPastRawUIntValue(LPCTSTR pszTag, INT nSample, ULONGLONG &nValue) CONST;
	BOOL GetParameterPastRawFloatValue(LPCTSTR pszTag, INT nSample, double &fValue) CONST;
	CTimeTag GetParameterPastValueTime(LPCTSTR pszTag, INT nSample) CONST;
	CTimeTag GetParameterLastUpdateTime(LPCTSTR pszTag) CONST;
	CTimeTag GetParameterLastChangeTime(LPCTSTR pszTag) CONST;
	UINT GetParameterStatus(LPCTSTR pszTag, INT nSample) CONST;

	BOOL Lock(LPCTSTR pszName);
	BOOL Unlock(LPCTSTR pszName);

	BOOL Exit(LPCTSTR pszName, BOOL bCode);

private:
	INT FindProcessIndex() CONST;

	LONGLONG UpdateProcessCount(INT nIndex, LPCTSTR pszName, INT nDelta = 0);
};

// Specify the associated export definitions
extern "C"
{
	__declspec(dllexport) BOOL InitializeJScriptTelemetryInterface(CONST CDatabaseEngine *pDatabase = NULL, CTMEnvironment *pTMEnvironment = NULL);
	__declspec(dllexport) BOOL UninitializeJScriptTelemetryInterface();
	__declspec(dllexport) BOOL GetJScriptTelemetryInterfaceParameterIntValue(LPCWSTR pszTag, INT nSample, LONGLONG &nValue);
	__declspec(dllexport) BOOL GetJScriptTelemetryInterfaceParameterUIntValue(LPCWSTR pszTag, INT nSample, ULONGLONG &nValue);
	__declspec(dllexport) BOOL GetJScriptTelemetryInterfaceParameterFloatValue(LPCWSTR pszTag, INT nSample, double &fValue);
	__declspec(dllexport) BOOL GetJScriptTelemetryInterfaceParameterStringValue(LPCWSTR pszTag, INT nSample, LPWSTR *pszValue);
	__declspec(dllexport) BOOL GetJScriptTelemetryInterfaceParameterRawIntValue(LPCWSTR pszTag, INT nSample, LONGLONG &nValue);
	__declspec(dllexport) BOOL GetJScriptTelemetryInterfaceParameterRawUIntValue(LPCWSTR pszTag, INT nSample, ULONGLONG &nValue);
	__declspec(dllexport) BOOL GetJScriptTelemetryInterfaceParameterRawFloatValue(LPCWSTR pszTag, INT nSample, double &fValue);
	__declspec(dllexport) TIMETAG GetJScriptTelemetryInterfaceParameterValueTime(LPCWSTR pszTag, INT nSample);
	__declspec(dllexport) BOOL SetJScriptTelemetryInterfaceParameterPastValueSamples(LPCWSTR pszTag, WORD wSamples);
	__declspec(dllexport) WORD GetJScriptTelemetryInterfaceParameterPastValueSamples(LPCWSTR pszTag);
	__declspec(dllexport) BOOL GetJScriptTelemetryInterfaceParameterPastIntValue(LPCWSTR pszTag, INT nSample, LONGLONG &nValue);
	__declspec(dllexport) BOOL GetJScriptTelemetryInterfaceParameterPastUIntValue(LPCWSTR pszTag, INT nSample, ULONGLONG &nValue);
	__declspec(dllexport) BOOL GetJScriptTelemetryInterfaceParameterPastFloatValue(LPCWSTR pszTag, INT nSample, double &fValue);
	__declspec(dllexport) BOOL GetJScriptTelemetryInterfaceParameterPastStringValue(LPCWSTR pszTag, INT nSample, LPWSTR *pszValue);
	__declspec(dllexport) BOOL GetJScriptTelemetryInterfaceParameterPastRawIntValue(LPCWSTR pszTag, INT nSample, LONGLONG &nValue);
	__declspec(dllexport) BOOL GetJScriptTelemetryInterfaceParameterPastRawUIntValue(LPCWSTR pszTag, INT nSample, ULONGLONG &nValue);
	__declspec(dllexport) BOOL GetJScriptTelemetryInterfaceParameterPastRawFloatValue(LPCWSTR pszTag, INT nSample, double &fValue);
	__declspec(dllexport) TIMETAG GetJScriptTelemetryInterfaceParameterPastValueTime(LPCWSTR pszTag, INT nSample);
	__declspec(dllexport) TIMETAG GetJScriptTelemetryInterfaceParameterLastUpdateTime(LPCWSTR pszTag);
	__declspec(dllexport) TIMETAG GetJScriptTelemetryInterfaceParameterLastChangeTime(LPCWSTR pszTag);
	__declspec(dllexport) UINT GetJScriptTelemetryInterfaceParameterStatus(LPCWSTR pszTag, INT nSample);
	__declspec(dllexport) BOOL LockJScriptTelemetryInterface(LPCWSTR pszName);
	__declspec(dllexport) BOOL UnlockJScriptTelemetryInterface(LPCWSTR pszName);
	__declspec(dllexport) BOOL ExitJScriptTelemetryInterface(LPCWSTR pszName, BOOL bCode);
}

/////////////////////////////////////////////////////////////////////////////


#endif // __JSCRIPT_H__
