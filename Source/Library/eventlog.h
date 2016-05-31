// EVENTLOG.H : Eventlog Related Interface Declaration.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the eventlog related interface
// declaration and macros.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1994/05/23 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#ifndef __EVENTLOG_H__
#define __EVENTLOG_H__

#include "event.h"
#include "token.h"
#include "logfile.h"


/////////////////////////////////////////////////////////////////////////////
// CEventLog

// Specify the eventlog category related identifiers
#define EVENTLOG_CATEGORY_NONE   EVENT_CATEGORY_NONE
#define EVENTLOG_CATEGORY_SYSTEM   EVENT_CATEGORY_SYSTEM
#define EVENTLOG_CATEGORY_SPACECRAFT   EVENT_CATEGORY_SPACECRAFT
#define EVENTLOG_CATEGORY_USER   EVENT_CATEGORY_USER
#define EVENTLOG_CATEGORY_ALL   EVENT_CATEGORY_ALL
#define EVENTLOG_CATEGORIES   EVENT_CATEGORIES

class AFX_EXT_CLASS CEventLog : public CToken
{
	// Construction
public:
	CEventLog();
	CEventLog(LPCTSTR pszSystemName, LPCTSTR pszSpacecraftName, LPCTSTR pszUserName, BOOL bLocal = TRUE);

	// Attributes
private:
	CLogFile  m_fSystemLog;
	CLogFile  m_fSpacecraftLog;
	CLogFile  m_fUserLog;
	BOOL  m_bLocal;
private:
	CEventList  m_pBufferData;
	BOOL  m_bBuffering[3];

	// Operations
public:
	BOOL Open(LPCTSTR pszSystemName, LPCTSTR pszSpacecraftName, LPCTSTR pszUserName, UINT nEventLogs = EVENTLOG_CATEGORY_ALL, UINT nFlags = CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite, UINT bLocal = -1, BOOL bWait = FALSE);
	BOOL Open(UINT nEventLogs, UINT nFlags, UINT bLocal = -1, BOOL bWait = FALSE);
	BOOL Compress(UINT nEventLogs = EVENTLOG_CATEGORY_ALL, BOOL bCompress = TRUE);
	BOOL Reset(UINT nEventLogs = EVENTLOG_CATEGORY_ALL);
	VOID Close(UINT nEventLogs = EVENTLOG_CATEGORY_ALL);

	BOOL RegisterSource(LPCTSTR pszSystemLogName = NULL, LPCTSTR pszGlobalSpacecraftName = NULL, LPCTSTR pszSpacecraftLogName = NULL, LPCTSTR pszUserLogName = NULL);
	BOOL UnregisterSource(UINT nEventLogs = EVENTLOG_CATEGORY_ALL, BOOL bAll = FALSE);

	BOOL SetOwner(CToken *pToken, BOOL bLocal = TRUE);
	BOOL SetOwner(LPCTSTR pszSystemName, LPCTSTR pszSpacecraftName, LPCTSTR pszUserName, BOOL bLocal = TRUE);
	BOOL GetOwner(CString &szSystemName, CString &szSpacecraftName, CString &szUserName, BOOL &bLocal) CONST;
	BOOL GetOwner(CString &szSystemName, CString &szSpacecraftName, CString &szUserName) CONST;

	BOOL SetSystemLogMode(UINT nMode);
	BOOL GetSystemLogMode(UINT &nMode) CONST;
	BOOL SetSystemLogPolicy(UINT nPolicy);
	BOOL GetSystemLogPolicy(UINT &nPolicy) CONST;
	BOOL SetSystemLogRetentionByItem(INT nRetention);
	BOOL GetSystemLogRetentionByItem(INT &nRetention) CONST;
	BOOL SetSystemLogRetentionBySize(DWORDLONG fRetention);
	BOOL GetSystemLogRetentionBySize(DWORDLONG &fRetention) CONST;
	BOOL SetSystemLogRetentionByTime(CONST CTimeSpan &tRetention);
	BOOL GetSystemLogRetentionByTime(CTimeSpan &tRetention) CONST;
	BOOL SetSpacecraftLogMode(UINT nMode);
	BOOL GetSpacecraftLogMode(UINT &nMode) CONST;
	BOOL SetSpacecraftLogPolicy(UINT nPolicy);
	BOOL GetSpacecraftLogPolicy(UINT &nPolicy) CONST;
	BOOL SetSpacecraftLogRetentionByItem(INT nRetention);
	BOOL GetSpacecraftLogRetentionByItem(INT &nRetention) CONST;
	BOOL SetSpacecraftLogRetentionBySize(DWORDLONG fRetention);
	BOOL GetSpacecraftLogRetentionBySize(DWORDLONG &fRetention) CONST;
	BOOL SetSpacecraftLogRetentionByTime(CONST CTimeSpan &tRetention);
	BOOL GetSpacecraftLogRetentionByTime(CTimeSpan &tRetention) CONST;
	BOOL SetUserLogMode(UINT nMode);
	BOOL GetUserLogMode(UINT &nMode) CONST;
	BOOL SetUserLogPolicy(UINT nPolicy);
	BOOL GetUserLogPolicy(UINT &nPolicy) CONST;
	BOOL SetUserLogRetentionByItem(INT nRetention);
	BOOL GetUserLogRetentionByItem(INT &nRetention) CONST;
	BOOL SetUserLogRetentionBySize(DWORDLONG fRetention);
	BOOL GetUserLogRetentionBySize(DWORDLONG &fRetention) CONST;
	BOOL SetUserLogRetentionByTime(CONST CTimeSpan &tRetention);
	BOOL GetUserLogRetentionByTime(CTimeSpan &tRetention) CONST;

	BOOL Write(CONST EVENT_DESCRIPTOR sEvent);
	BOOL Write(CONST CEventObject *pEvent);
	BOOL Read(CEventList &cEventList, CONST CTimeKey &tStartTime, INT nCount = -1, UINT nEventLogs = EVENTLOG_CATEGORY_ALL, HANDLE hAbort = NULL);
	BOOL Read(CEventList &cEventList, CONST CTimeKey &tStartTime, CONST CTimeKey &tEndTime = MAX_TIMEKEY, UINT nEventLogs = EVENTLOG_CATEGORY_ALL, HANDLE hAbort = NULL);
	BOOL ReadAll(CEventList &cEventList, UINT nEventLogs = EVENTLOG_CATEGORY_ALL, HANDLE hAbort = NULL);
	BOOL CanFlush() CONST;
	BOOL FlushAll();

	INT BeginWatch(UINT nEventLogs, LPHANDLE phEventLogs = NULL, INT nCount = 0);
	BOOL Watch(UINT nEventLogs, CEventList &cEventList);
	BOOL EndWatch(UINT nEventLogs);

	BOOL Report(CONST CEventObject *pEvent);
	BOOL Report(EVENT_DESCRIPTOR sEvent);
	BOOL Report(EVENT_DESCRIPTOR sEvent, CONST CStringArray &szArguments);

public:
	BOOL QuerySystemLogFileName(CString &szFileName) CONST;
	BOOL QueryGlobalSpacecraftLogFileName(CString &szFileName) CONST;
	BOOL QuerySpacecraftLogFileName(CString &szFileName) CONST;
	BOOL QueryUserLogFileName(CString &szFileName) CONST;

private:
	BOOL QuerySystemLogSubKey(CString &szSubKey) CONST;
	BOOL QuerySpacecraftLogSubKey(CString &szSubKey) CONST;
	BOOL QueryUserLogSubKey(CString &szSubKey) CONST;
	BOOL QueryDefaultSystemLogName(CString &szName) CONST;
	BOOL QueryDefaultSpacecraftLogName(CString &szName) CONST;
	BOOL QueryDefaultUserLogName(CString &szName) CONST;

	BOOL TestDirectory(LPCTSTR pszFileName) CONST;

	BOOL CheckSecurity(LPCTSTR pszFileName) CONST;
};

/////////////////////////////////////////////////////////////////////////////


#endif // __EVENTLOG_H__
