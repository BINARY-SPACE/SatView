// JSCRIPT.CPP : JScript Code Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the automation script
// related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2008/05/10 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CJScriptTaskScheduler

static CJScriptTaskScheduler  cJScriptTaskScheduler;

CJScriptTaskScheduler::CJScriptTaskScheduler() : CObject()
{
	m_pCriticalSection = new CCriticalSection;
}

CJScriptTaskScheduler::~CJScriptTaskScheduler()
{
	delete m_pCriticalSection;
}

BOOL CJScriptTaskScheduler::Initialize(HANDLE hTelemetryReportEvent, HANDLE hTelemetryDataExtractionEvent)
{
	INT  nProcess;
	INT  nProcesses;
	DWORD  dwProcessID;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nProcess = 0, nProcesses = (!hTelemetryReportEvent) ? (INT)m_dwProcessIDs.GetSize() : 0, dwProcessID = GetCurrentProcessId(); nProcess < nProcesses; nProcess++)
	{
		if (m_dwProcessIDs.GetAt(nProcess) == dwProcessID)
		{
			hTelemetryReportEvent = m_pProcessEvents[0].GetAt(nProcess);
			break;
		}
	}
	for (nProcess = 0, nProcesses = (!hTelemetryDataExtractionEvent) ? (INT)m_dwProcessIDs.GetSize() : 0; nProcess < nProcesses; nProcess++)
	{
		if (m_dwProcessIDs.GetAt(nProcess) == dwProcessID)
		{
			hTelemetryDataExtractionEvent = m_pProcessEvents[1].GetAt(nProcess);
			break;
		}
	}
	if (hTelemetryReportEvent != (HANDLE)NULL  &&  hTelemetryDataExtractionEvent != (HANDLE)NULL)
	{
		for (nProcess = 0, nProcesses = (INT)m_dwProcessIDs.GetSize(); nProcess < nProcesses; nProcess++)
		{
			if (m_dwProcessIDs.GetAt(nProcess) == dwProcessID)
			{
				m_pProcessEvents[0].SetAt(nProcess, hTelemetryReportEvent);
				m_pProcessEvents[1].SetAt(nProcess, hTelemetryDataExtractionEvent);
				for (; m_nProcessTelemetryReportIDs.GetAt(nProcess) > 0; )
				{
					SetEvent(hTelemetryReportEvent);
					break;
				}
				for (; m_nProcessTelemetryDataExtractionIDs.GetAt(nProcess) > 0; )
				{
					SetEvent(hTelemetryDataExtractionEvent);
					break;
				}
				break;
			}
		}
		if (nProcess == nProcesses)
		{
			ResetEvent(hTelemetryReportEvent);
			ResetEvent(hTelemetryDataExtractionEvent);
			m_pProcessEvents[0].Add(hTelemetryReportEvent);
			m_pProcessEvents[1].Add(hTelemetryDataExtractionEvent);
			m_nProcessTelemetryReportIDs.Add(0);
			m_nProcessTelemetryDataExtractionIDs.Add(0);
			m_dwProcessIDs.Add(dwProcessID);
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CJScriptTaskScheduler::Uninitialize()
{
	INT  nProcess;
	INT  nProcesses;
	DWORD  dwProcessID;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nProcess = 0, nProcesses = (INT)m_dwTelemetryReportProcessIDs.GetSize(), dwProcessID = GetCurrentProcessId(); nProcess < nProcesses; nProcess++)
	{
		if (m_dwTelemetryReportProcessIDs.GetAt(nProcess) == dwProcessID)
		{
			m_szTelemetryReports.RemoveAt(nProcess);
			m_tTelemetryReportStartTimes.RemoveAt(nProcess);
			m_tTelemetryReportIntervals.RemoveAt(nProcess);
			m_tTelemetryReportStopTimes.RemoveAt(nProcess);
			m_dwTelemetryReportProcessIDs.RemoveAt(nProcess);
			m_nTelemetryReportIDs.RemoveAt(nProcess);
			nProcesses--;
			nProcess--;
		}
	}
	for (nProcess = 0, nProcesses = (INT)m_dwTelemetryDataExtractionProcessIDs.GetSize(); nProcess < nProcesses; nProcess++)
	{
		if (m_dwTelemetryDataExtractionProcessIDs.GetAt(nProcess) == dwProcessID)
		{
			m_szTelemetryDataExtractions.RemoveAt(nProcess);
			m_tTelemetryDataExtractionScheduleTimes.RemoveAt(nProcess);
			m_tTelemetryDataExtractionStartTimes.RemoveAt(nProcess);
			m_tTelemetryDataExtractionStopTimes.RemoveAt(nProcess);
			m_dwTelemetryDataExtractionProcessIDs.RemoveAt(nProcess);
			m_nTelemetryDataExtractionIDs.RemoveAt(nProcess);
			nProcesses--;
			nProcess--;
		}
	}
	for (nProcess = 0, nProcesses = (INT)m_dwProcessIDs.GetSize(); nProcess < nProcesses; nProcess++)
	{
		if (m_dwProcessIDs.GetAt(nProcess) == dwProcessID)
		{
			m_pProcessEvents[0].RemoveAt(nProcess);
			m_pProcessEvents[1].RemoveAt(nProcess);
			m_nProcessTelemetryReportIDs.RemoveAt(nProcess);
			m_nProcessTelemetryDataExtractionIDs.RemoveAt(nProcess);
			m_dwProcessIDs.RemoveAt(nProcess);
			break;
		}
	}
	return TRUE;
}

INT CJScriptTaskScheduler::EnumTelemetryReports(CStringArray &szNames, CUIntArray &nIDs, CTimeKeyArray &tStartTimes, CTimeKeyArray &tIntervals, CTimeKeyArray &tStopTimes) CONST
{
	INT  nProcess;
	INT  nProcesses;
	DWORD  dwProcessID;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nProcess = 0, nProcesses = (INT)m_dwTelemetryReportProcessIDs.GetSize(), dwProcessID = GetCurrentProcessId(), szNames.RemoveAll(), nIDs.RemoveAll(), tStartTimes.RemoveAll(), tIntervals.RemoveAll(), tStopTimes.RemoveAll(); nProcess < nProcesses; nProcess++)
	{
		if (m_dwTelemetryReportProcessIDs.GetAt(nProcess) == dwProcessID)
		{
			szNames.Add(m_szTelemetryReports.GetAt(nProcess));
			nIDs.Add(m_nTelemetryReportIDs.GetAt(nProcess));
			tStartTimes.Add(m_tTelemetryReportStartTimes.GetAt(nProcess));
			tIntervals.Add(m_tTelemetryReportIntervals.GetAt(nProcess));
			tStopTimes.Add(m_tTelemetryReportStopTimes.GetAt(nProcess));
		}
	}
	return((INT)szNames.GetSize());
}

UINT CJScriptTaskScheduler::AddTelemetryReport(LPCTSTR pszName, CONST CTimeKey &tStartTime, CONST CTimeSpan &tInterval, CONST CTimeKey &tStopTime)
{
	INT  nID;
	INT  nItem;
	INT  nItems;
	INT  nProcess;
	INT  nProcesses;
	DWORD  dwProcessID;
	HANDLE  hSuccess;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nProcess = 0, nProcesses = (lstrlen(pszName) > 0 && tStartTime > 0 && ((tInterval == 0 && tStopTime == 0) || (tInterval > 0 && (tStopTime == 0 || (tStopTime >= tStartTime.GetTime() + tInterval.GetTotalSeconds()))))) ? (INT)m_dwProcessIDs.GetSize() : -1, dwProcessID = GetCurrentProcessId(); nProcess < nProcesses; nProcess++)
	{
		if (m_dwProcessIDs.GetAt(nProcess) == dwProcessID) break;
		continue;
	}
	if (nProcess == nProcesses)
	{
		m_pProcessEvents[0].Add(NULL);
		m_pProcessEvents[1].Add(NULL);
		m_nProcessTelemetryReportIDs.Add(0);
		m_nProcessTelemetryDataExtractionIDs.Add(0);
		m_dwProcessIDs.Add(dwProcessID);
	}
	for (nItem = 0, nItems = (nProcess <= nProcesses) ? (INT)m_nTelemetryReportIDs.GetSize() : -1, nID = (nProcess <= nProcesses) ? m_nProcessTelemetryReportIDs.GetAt(nProcess) : -1; nItem < nItems; nItem++)
	{
		if (m_dwTelemetryReportProcessIDs.GetAt(nItem) == dwProcessID  &&  m_nTelemetryReportIDs.GetAt(nItem) == nID)
		{
			nID = nID + 1;
			nItem = -1;
		}
	}
	if (nItem == nItems)
	{
		for (m_szTelemetryReports.Add(pszName), m_nTelemetryReportIDs.Add(nID), m_tTelemetryReportStartTimes.Add(tStartTime), m_tTelemetryReportIntervals.Add((UINT)tInterval.GetTotalSeconds()), m_tTelemetryReportStopTimes.Add(tStopTime), m_dwTelemetryReportProcessIDs.Add(dwProcessID), m_nProcessTelemetryReportIDs.SetAt(nProcess, nID + 1); (hSuccess = (HANDLE)m_pProcessEvents[0].GetAt(nProcess)); )
		{
			SetEvent(hSuccess);
			break;
		}
		return nID;
	}
	return -1;
}

BOOL CJScriptTaskScheduler::DeleteTelemetryReport(UINT nID)
{
	INT  nItem;
	INT  nItems;
	INT  nProcess;
	INT  nProcesses;
	DWORD  dwProcessID;
	HANDLE  hSuccess;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nProcess = 0, nProcesses = (INT)m_dwProcessIDs.GetSize(), dwProcessID = GetCurrentProcessId(); nProcess < nProcesses; nProcess++)
	{
		if (m_dwProcessIDs.GetAt(nProcess) == dwProcessID) break;
		continue;
	}
	for (nItem = 0, nItems = (nProcess < nProcesses) ? (INT)m_nTelemetryReportIDs.GetSize() : -1; nItem < nItems; nItem++)
	{
		if (m_dwTelemetryReportProcessIDs.GetAt(nItem) == dwProcessID  &&  m_nTelemetryReportIDs.GetAt(nItem) == nID) break;
		continue;
	}
	if (nItem < nItems)
	{
		for (m_szTelemetryReports.RemoveAt(nItem), m_nTelemetryReportIDs.RemoveAt(nItem), m_tTelemetryReportStartTimes.RemoveAt(nItem), m_tTelemetryReportIntervals.RemoveAt(nItem), m_tTelemetryReportStopTimes.RemoveAt(nItem), m_dwTelemetryReportProcessIDs.RemoveAt(nItem); (hSuccess = (HANDLE)m_pProcessEvents[0].GetAt(nProcess)); )
		{
			SetEvent(hSuccess);
			break;
		}
		return TRUE;
	}
	return FALSE;
}

INT CJScriptTaskScheduler::EnumTelemetryDataExtractions(CStringArray &szNames, CUIntArray &nIDs, CTimeKeyArray &tScheduleTimes, CTimeKeyArray &tStartTimes, CTimeKeyArray &tStopTimes) CONST
{
	INT  nProcess;
	INT  nProcesses;
	DWORD  dwProcessID;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nProcess = 0, nProcesses = (INT)m_dwTelemetryDataExtractionProcessIDs.GetSize(), dwProcessID = GetCurrentProcessId(), szNames.RemoveAll(), nIDs.RemoveAll(), tScheduleTimes.RemoveAll(), tStartTimes.RemoveAll(), tStopTimes.RemoveAll(); nProcess < nProcesses; nProcess++)
	{
		if (m_dwTelemetryDataExtractionProcessIDs.GetAt(nProcess) == dwProcessID)
		{
			szNames.Add(m_szTelemetryDataExtractions.GetAt(nProcess));
			nIDs.Add(m_nTelemetryDataExtractionIDs.GetAt(nProcess));
			tScheduleTimes.Add(m_tTelemetryDataExtractionScheduleTimes.GetAt(nProcess));
			tStartTimes.Add(m_tTelemetryDataExtractionStartTimes.GetAt(nProcess));
			tStopTimes.Add(m_tTelemetryDataExtractionStopTimes.GetAt(nProcess));
		}
	}
	return((INT)szNames.GetSize());
}

UINT CJScriptTaskScheduler::AddTelemetryDataExtraction(LPCTSTR pszName, CONST CTimeKey &tScheduleTime, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime)
{
	INT  nID;
	INT  nItem;
	INT  nItems;
	INT  nProcess;
	INT  nProcesses;
	DWORD  dwProcessID;
	HANDLE  hSuccess;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nProcess = 0, nProcesses = (lstrlen(pszName) > 0 && tScheduleTime >= tStopTime && tStartTime <= tStopTime) ? (INT)m_dwProcessIDs.GetSize() : -1, dwProcessID = GetCurrentProcessId(); nProcess < nProcesses; nProcess++)
	{
		if (m_dwProcessIDs.GetAt(nProcess) == dwProcessID) break;
		continue;
	}
	if (nProcess == nProcesses)
	{
		m_pProcessEvents[0].Add(NULL);
		m_pProcessEvents[1].Add(NULL);
		m_nProcessTelemetryReportIDs.Add(0);
		m_nProcessTelemetryDataExtractionIDs.Add(0);
		m_dwProcessIDs.Add(dwProcessID);
	}
	for (nItem = 0, nItems = (nProcess <= nProcesses) ? (INT)m_nTelemetryDataExtractionIDs.GetSize() : -1, nID = (nProcess <= nProcesses) ? m_nProcessTelemetryDataExtractionIDs.GetAt(nProcess) : -1; nItem < nItems; nItem++)
	{
		if (m_dwTelemetryDataExtractionProcessIDs.GetAt(nItem) == dwProcessID  &&  m_nTelemetryDataExtractionIDs.GetAt(nItem) == nID)
		{
			nID = nID + 1;
			nItem = -1;
		}
	}
	if (nItem == nItems)
	{
		for (m_szTelemetryDataExtractions.Add(pszName), m_nTelemetryDataExtractionIDs.Add(nID), m_tTelemetryDataExtractionScheduleTimes.Add(tScheduleTime), m_tTelemetryDataExtractionStartTimes.Add(tStartTime), m_tTelemetryDataExtractionStopTimes.Add(tStopTime), m_dwTelemetryDataExtractionProcessIDs.Add(dwProcessID), m_nProcessTelemetryDataExtractionIDs.SetAt(nProcess, nID + 1); (hSuccess = (HANDLE)m_pProcessEvents[1].GetAt(nProcess)); )
		{
			SetEvent(hSuccess);
			break;
		}
		return nID;
	}
	return -1;
}

BOOL CJScriptTaskScheduler::DeleteTelemetryDataExtraction(UINT nID)
{
	INT  nItem;
	INT  nItems;
	INT  nProcess;
	INT  nProcesses;
	DWORD  dwProcessID;
	HANDLE  hSuccess;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nProcess = 0, nProcesses = (INT)m_dwProcessIDs.GetSize(), dwProcessID = GetCurrentProcessId(); nProcess < nProcesses; nProcess++)
	{
		if (m_dwProcessIDs.GetAt(nProcess) == dwProcessID) break;
		continue;
	}
	for (nItem = 0, nItems = (nProcess < nProcesses) ? (INT)m_nTelemetryDataExtractionIDs.GetSize() : -1; nItem < nItems; nItem++)
	{
		if (m_dwTelemetryDataExtractionProcessIDs.GetAt(nItem) == dwProcessID  &&  m_nTelemetryDataExtractionIDs.GetAt(nItem) == nID) break;
		continue;
	}
	if (nItem < nItems)
	{
		for (m_szTelemetryDataExtractions.RemoveAt(nItem), m_nTelemetryDataExtractionIDs.RemoveAt(nItem), m_tTelemetryDataExtractionScheduleTimes.RemoveAt(nItem), m_tTelemetryDataExtractionStartTimes.RemoveAt(nItem), m_tTelemetryDataExtractionStopTimes.RemoveAt(nItem), m_dwTelemetryDataExtractionProcessIDs.RemoveAt(nItem); (hSuccess = (HANDLE)m_pProcessEvents[1].GetAt(nProcess)); )
		{
			SetEvent(hSuccess);
			break;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CJScriptTaskScheduler::Lock()
{
	return m_pCriticalSection->Lock();
}

BOOL CJScriptTaskScheduler::Unlock()
{
	return m_pCriticalSection->Unlock();
}

/////////////////////////////////////////////////////////////////////////////
// CJScriptTaskScheduler exports

BOOL InitializeJScriptTaskScheduler(HANDLE hTelemetryReportEvent, HANDLE hTelemetryDataExtractionEvent)
{
	return cJScriptTaskScheduler.Initialize(hTelemetryReportEvent, hTelemetryDataExtractionEvent);
}

BOOL UninitializeJScriptTaskScheduler()
{
	return cJScriptTaskScheduler.Uninitialize();
}

INT EnumJScriptTaskSchedulerTelemetryReports(LPCWSTR *pszNames[], UINT *nIDs[], TIMEKEY *tStartTimes[], TIMEKEY *tIntervals[], TIMEKEY *tStopTimes[])
{
	INT  nItem;
	INT  nItems;
	LPWSTR  pszName;
	CUIntArray  nTaskIDs;
	CStringArray  szTaskNames;
	CTimeKeyArray  tTaskTimes[2];
	CTimeKeyArray  tTaskIntervals;

	if ((nItems = cJScriptTaskScheduler.EnumTelemetryReports(szTaskNames, nTaskIDs, tTaskTimes[0], tTaskIntervals, tTaskTimes[1])) > 0)
	{
		if ((*pszNames = new LPCWSTR[nItems]))
		{
			if ((*tStartTimes = new TIMEKEY[nItems]))
			{
				if ((*tStopTimes = new TIMEKEY[nItems]))
				{
					if ((*tIntervals = new TIMEKEY[nItems]))
					{
						if ((*nIDs = new UINT[nItems]))
						{
							for (nItem = 0; nItem < nItems; nItem++)
							{
								if ((pszName = new WCHAR[szTaskNames.GetAt(nItem).GetLength() + 1]))
								{
#ifndef UNICODE
									MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szTaskNames.GetAt(nItem), -1, pszName, szTaskNames.GetAt(nItem).GetLength() + 1);
#else
									wcscpy_s(pszName, szTaskNames.GetAt(nItem).GetLength() + 1, szTaskNames.GetAt(nItem));
#endif
									(*pszNames)[nItem] = pszName;
									(*nIDs)[nItem] = nTaskIDs.GetAt(nItem);
									(*tStartTimes)[nItem] = tTaskTimes[0].GetAt(nItem).GetTime();
									(*tStopTimes)[nItem] = tTaskTimes[1].GetAt(nItem).GetTime();
									(*tIntervals)[nItem] = tTaskIntervals.GetAt(nItem).GetTime();
									continue;
								}
								break;
							}
							if (nItem != nItems)
							{
								for (; nItem > 0; nItem--)
								{
									delete[] pszNames[nItem - 1];
									continue;
								}
								delete nIDs;
								delete pszNames;
								delete tStartTimes;
								delete tStopTimes;
								delete tIntervals;
								return 0;
							}
							return nItems;
						}
						delete tIntervals;
					}
					delete tStopTimes;
				}
				delete tStartTimes;
			}
			delete pszNames;
		}
	}
	return 0;
}

UINT AddJScriptTaskSchedulerTelemetryReport(LPCWSTR pszName, TIMEKEY tStartTime, TIMEKEY tInterval, TIMEKEY tStopTime)
{
	UINT  nID;
	CString  szName;

#ifndef UNICODE
	WideCharToMultiByte(CP_ACP, 0, pszName, -1, szName.GetBufferSetLength((INT)wcslen(pszName)), (INT)wcslen(pszName) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
	for (szName.ReleaseBuffer(); (nID = cJScriptTaskScheduler.AddTelemetryReport(szName, tStartTime, tInterval, tStopTime)) != (UINT)-1; ) return nID;
#else
	return(((nID = cJScriptTaskScheduler.AddTelemetryReport(pszName, tStartTime, tInterval, tStopTime)) != (UINT)-1) ? nID : -1);
#endif
	return -1;
}

BOOL DeleteJScriptTaskSchedulerTelemetryReport(UINT nID)
{
	return cJScriptTaskScheduler.DeleteTelemetryReport(nID);
}

INT EnumJScriptTaskSchedulerTelemetryDataExtractions(LPCWSTR *pszNames[], UINT *nIDs[], TIMEKEY *tScheduleTimes[], TIMEKEY *tStartTimes[], TIMEKEY *tStopTimes[])
{
	INT  nItem;
	INT  nItems;
	LPWSTR  pszName;
	CUIntArray  nTaskIDs;
	CStringArray  szTaskNames;
	CTimeKeyArray  tTaskTimes[3];

	if ((nItems = cJScriptTaskScheduler.EnumTelemetryDataExtractions(szTaskNames, nTaskIDs, tTaskTimes[0], tTaskTimes[1], tTaskTimes[2])) > 0)
	{
		if ((*pszNames = new LPCWSTR[nItems]))
		{
			if ((*tScheduleTimes = new TIMEKEY[nItems]))
			{
				if ((*tStartTimes = new TIMEKEY[nItems]))
				{
					if ((*tStopTimes = new TIMEKEY[nItems]))
					{
						if ((*nIDs = new UINT[nItems]))
						{
							for (nItem = 0; nItem < nItems; nItem++)
							{
								if ((pszName = new WCHAR[szTaskNames.GetAt(nItem).GetLength() + 1]))
								{
#ifndef UNICODE
									MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szTaskNames.GetAt(nItem), -1, pszName, szTaskNames.GetAt(nItem).GetLength() + 1);
#else
									wcscpy_s(pszName, szTaskNames.GetAt(nItem).GetLength() + 1, szTaskNames.GetAt(nItem));
#endif
									(*pszNames)[nItem] = pszName;
									(*nIDs)[nItem] = nTaskIDs.GetAt(nItem);
									(*tScheduleTimes)[nItem] = tTaskTimes[0].GetAt(nItem).GetTime();
									(*tStartTimes)[nItem] = tTaskTimes[1].GetAt(nItem).GetTime();
									(*tStopTimes)[nItem] = tTaskTimes[2].GetAt(nItem).GetTime();
									continue;
								}
								break;
							}
							if (nItem != nItems)
							{
								for (; nItem > 0; nItem--)
								{
									delete[] pszNames[nItem - 1];
									continue;
								}
								delete nIDs;
								delete pszNames;
								delete tScheduleTimes;
								delete tStartTimes;
								delete tStopTimes;
								return 0;
							}
							return nItems;
						}
						delete tStopTimes;
					}
					delete tStartTimes;
				}
				delete tScheduleTimes;
			}
			delete pszNames;
		}
	}
	return 0;
}

UINT AddJScriptTaskSchedulerTelemetryDataExtraction(LPCWSTR pszName, TIMEKEY tScheduleTime, TIMEKEY tStartTime, TIMEKEY tStopTime)
{
	UINT  nID;
	CString  szName;

#ifndef UNICODE
	WideCharToMultiByte(CP_ACP, 0, pszName, -1, szName.GetBufferSetLength((INT)wcslen(pszName)), (INT)wcslen(pszName) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
	for (szName.ReleaseBuffer(); (nID = cJScriptTaskScheduler.AddTelemetryDataExtraction(szName, tScheduleTime, tStartTime, tStopTime)) != (UINT)-1; ) return nID;
#else
	return(((nID = cJScriptTaskScheduler.AddTelemetryDataExtraction(pszName, tScheduleTime, tStartTime, tStopTime)) != (UINT)-1) ? nID : -1);
#endif
	return -1;
}

BOOL DeleteJScriptTaskSchedulerTelemetryDataExtraction(UINT nID)
{
	return cJScriptTaskScheduler.DeleteTelemetryDataExtraction(nID);
}


/////////////////////////////////////////////////////////////////////////////
// CJScriptTelemetryInterface

static CJScriptTelemetryInterface  cJScriptTelemetryInterface;

CJScriptTelemetryInterface::CJScriptTelemetryInterface() : CObject()
{
	m_pCriticalSection = new CCriticalSection;
}

CJScriptTelemetryInterface::~CJScriptTelemetryInterface()
{
	delete m_pCriticalSection;
}

BOOL CJScriptTelemetryInterface::Initialize(CONST CDatabaseEngine *pDatabase, CTMEnvironment *pTMEnvironment)
{
	INT  nIndex;
	INT  nProcess;
	INT  nProcesses;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((nIndex = FindProcessIndex()) >= 0)
	{
		m_pDatabases.SetAt(nIndex, (LPVOID)pDatabase);
		m_pTMEnvironments.SetAt(nIndex, pTMEnvironment);
		m_szProcessCounts.SetAt(nIndex, EMPTYSTRING);
		return TRUE;
	}
	for (m_dwProcessIDs.Add(GetCurrentProcessId()); pDatabase != (CDatabaseEngine *)NULL && pTMEnvironment != (CTMEnvironment *)NULL; )
	{
		m_pDatabases.Add((LPVOID)pDatabase);
		m_pTMEnvironments.Add(pTMEnvironment);
		m_szProcessCounts.Add(EMPTYSTRING);
		return TRUE;
	}
	for (nProcess = 0, nProcesses = (INT)m_dwProcessIDs.GetSize(); nProcess < nProcesses; nProcess++)
	{
		if (m_dwProcessIDs.GetAt(nProcess) == GetCurrentProcessId())
		{
			m_pTMEnvironments.Add(m_pTMEnvironments.GetAt(nProcess));
			m_pDatabases.Add(m_pDatabases.GetAt(nProcess));
			m_szProcessCounts.Add(EMPTYSTRING);
			break;
		}
	}
	return TRUE;
}

BOOL CJScriptTelemetryInterface::Uninitialize()
{
	INT  nIndex;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((nIndex = FindProcessIndex()) >= 0)
	{
		m_pTMEnvironments.RemoveAt(nIndex);
		m_pDatabases.RemoveAt(nIndex);
		m_szProcessCounts.RemoveAt(nIndex);
		m_dwProcessIDs.RemoveAt(nIndex);
		return TRUE;
	}
	return FALSE;
}

BOOL CJScriptTelemetryInterface::GetParameterIntValue(LPCTSTR pszTag, INT nSample, LONGLONG &nValue) CONST
{
	INT  nIndex;
	double  fValue;
	CTMParameter  *pTMParameter;
	CTMEnvironment  *pTMEnvironment;
	CDatabaseEngine  *pDatabase;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pTMEnvironment = ((pDatabase = ((nIndex = FindProcessIndex()) >= 0) ? (CDatabaseEngine *)m_pDatabases.GetAt(nIndex) : (CDatabaseEngine *)NULL)) ? (CTMEnvironment *)m_pTMEnvironments.GetAt(nIndex) : (CTMEnvironment *)NULL))
	{
		for (pTMEnvironment->Lock(); (pTMParameter = pTMEnvironment->GetTMParameters()->GetAt(pTMEnvironment->GetTMParameters()->Find(pszTag))) != (CTMParameter *)NULL; )
		{
			if (((pTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS)) == 0) && ((pTMParameter->GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) || (pTMParameter->GetAttributes() & TMPARAMETER_CODING_COMPLEMENTCOMPLEX)))
			{
				if (pTMParameter->GetValue(pDatabase, nSample, fValue))
				{
					nValue = (LONGLONG)fValue;
					pTMEnvironment->Unlock();
					return TRUE;
				}
			}
			break;
		}
		pTMEnvironment->Unlock();
	}
	return FALSE;
}

BOOL CJScriptTelemetryInterface::GetParameterUIntValue(LPCTSTR pszTag, INT nSample, ULONGLONG &nValue) CONST
{
	INT  nIndex;
	double  fValue;
	CTMParameter  *pTMParameter;
	CTMEnvironment  *pTMEnvironment;
	CDatabaseEngine  *pDatabase;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pTMEnvironment = ((pDatabase = ((nIndex = FindProcessIndex()) >= 0) ? (CDatabaseEngine *)m_pDatabases.GetAt(nIndex) : (CDatabaseEngine *)NULL)) ? (CTMEnvironment *)m_pTMEnvironments.GetAt(nIndex) : (CTMEnvironment *)NULL))
	{
		for (pTMEnvironment->Lock(); (pTMParameter = pTMEnvironment->GetTMParameters()->GetAt(pTMEnvironment->GetTMParameters()->Find(pszTag))) != (CTMParameter *)NULL; )
		{
			if (((pTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS)) == 0) && ((pTMParameter->GetAttributes() & TMPARAMETER_CODING_BITPATTERN) || (pTMParameter->GetAttributes() & TMPARAMETER_CODING_INVERSEBITPATTERN) || (pTMParameter->GetAttributes() & TMPARAMETER_CODING_UNSIGNEDINTEGER) || (pTMParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_FLOATINGPOINT)) == 0))
			{
				if (pTMParameter->GetValue(pDatabase, nSample, fValue))
				{
					nValue = (ULONGLONG)fValue;
					pTMEnvironment->Unlock();
					return TRUE;
				}
			}
			break;
		}
		pTMEnvironment->Unlock();
	}
	return FALSE;
}

BOOL CJScriptTelemetryInterface::GetParameterFloatValue(LPCTSTR pszTag, INT nSample, double &fValue) CONST
{
	INT  nIndex;
	CTMParameter  *pTMParameter;
	CTMEnvironment  *pTMEnvironment;
	CDatabaseEngine  *pDatabase;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pTMEnvironment = ((pDatabase = ((nIndex = FindProcessIndex()) >= 0) ? (CDatabaseEngine *)m_pDatabases.GetAt(nIndex) : (CDatabaseEngine *)NULL)) ? (CTMEnvironment *)m_pTMEnvironments.GetAt(nIndex) : (CTMEnvironment *)NULL))
	{
		for (pTMEnvironment->Lock(); (pTMParameter = pTMEnvironment->GetTMParameters()->GetAt(pTMEnvironment->GetTMParameters()->Find(pszTag))) != (CTMParameter *)NULL; )
		{
			if ((((pTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS)) == 0) && (pTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT)) || (pTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL))
			{
				if (pTMParameter->GetValue(pDatabase, nSample, fValue))
				{
					pTMEnvironment->Unlock();
					return TRUE;
				}
			}
			break;
		}
		pTMEnvironment->Unlock();
	}
	return FALSE;
}

BOOL CJScriptTelemetryInterface::GetParameterStringValue(LPCTSTR pszTag, INT nSample, CString &szValue) CONST
{
	INT  nIndex;
	CTMParameter  *pTMParameter;
	CTMEnvironment  *pTMEnvironment;
	CDatabaseEngine  *pDatabase;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pTMEnvironment = ((pDatabase = ((nIndex = FindProcessIndex()) >= 0) ? (CDatabaseEngine *)m_pDatabases.GetAt(nIndex) : (CDatabaseEngine *)NULL)) ? (CTMEnvironment *)m_pTMEnvironments.GetAt(nIndex) : (CTMEnvironment *)NULL))
	{
		for (pTMEnvironment->Lock(); (pTMParameter = pTMEnvironment->GetTMParameters()->GetAt(pTMEnvironment->GetTMParameters()->Find(pszTag))) && (pTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS); )
		{
			if (pTMParameter->GetValueAsText(pDatabase, nSample, szValue))
			{
				pTMEnvironment->Unlock();
				return TRUE;
			}
			break;
		}
		pTMEnvironment->Unlock();
	}
	return FALSE;
}

BOOL CJScriptTelemetryInterface::GetParameterRawIntValue(LPCTSTR pszTag, INT nSample, LONGLONG &nValue) CONST
{
	INT  nIndex;
	UINT  nStatus;
	ULONGLONG  nRawValue;
	CTMParameter  *pTMParameter;
	CTMEnvironment  *pTMEnvironment;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pTMEnvironment = ((nIndex = FindProcessIndex()) >= 0) ? (CTMEnvironment *)m_pTMEnvironments.GetAt(nIndex) : (CTMEnvironment *)NULL))
	{
		for (pTMEnvironment->Lock(); (pTMParameter = pTMEnvironment->GetTMParameters()->GetAt(pTMEnvironment->GetTMParameters()->Find(pszTag))); )
		{
			if ((pTMParameter->GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) || (pTMParameter->GetAttributes() & TMPARAMETER_CODING_COMPLEMENTCOMPLEX))
			{
				if (pTMParameter->GetRawValue(nSample, nRawValue, nStatus))
				{
					nValue = (LONGLONG)nRawValue;
					pTMEnvironment->Unlock();
					return TRUE;
				}
			}
			break;
		}
		pTMEnvironment->Unlock();
	}
	return FALSE;
}

BOOL CJScriptTelemetryInterface::GetParameterRawUIntValue(LPCTSTR pszTag, INT nSample, ULONGLONG &nValue) CONST
{
	INT  nIndex;
	UINT  nStatus;
	ULONGLONG  nRawValue;
	CTMParameter  *pTMParameter;
	CTMEnvironment  *pTMEnvironment;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pTMEnvironment = ((nIndex = FindProcessIndex()) >= 0) ? (CTMEnvironment *)m_pTMEnvironments.GetAt(nIndex) : (CTMEnvironment *)NULL))
	{
		for (pTMEnvironment->Lock(); (pTMParameter = pTMEnvironment->GetTMParameters()->GetAt(pTMEnvironment->GetTMParameters()->Find(pszTag))); )
		{
			if ((pTMParameter->GetAttributes() & TMPARAMETER_CODING_BITPATTERN) || (pTMParameter->GetAttributes() & TMPARAMETER_CODING_INVERSEBITPATTERN) || (pTMParameter->GetAttributes() & TMPARAMETER_CODING_UNSIGNEDINTEGER) || (pTMParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_FLOATINGPOINT)) == 0)
			{
				if (pTMParameter->GetRawValue(nSample, nRawValue, nStatus))
				{
					nValue = nRawValue;
					pTMEnvironment->Unlock();
					return TRUE;
				}
			}
			break;
		}
		pTMEnvironment->Unlock();
	}
	return FALSE;
}

BOOL CJScriptTelemetryInterface::GetParameterRawFloatValue(LPCTSTR pszTag, INT nSample, double &fValue) CONST
{
	INT  nIndex;
	CTMParameter  *pTMParameter;
	CTMEnvironment  *pTMEnvironment;
	CDatabaseEngine  *pDatabase;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pTMEnvironment = ((pDatabase = ((nIndex = FindProcessIndex()) >= 0) ? (CDatabaseEngine *)m_pDatabases.GetAt(nIndex) : (CDatabaseEngine *)NULL)) ? (CTMEnvironment *)m_pTMEnvironments.GetAt(nIndex) : (CTMEnvironment *)NULL))
	{
		for (pTMEnvironment->Lock(); (pTMParameter = pTMEnvironment->GetTMParameters()->GetAt(pTMEnvironment->GetTMParameters()->Find(pszTag))); )
		{
			if (pTMParameter->GetValue(pDatabase, nSample, (pTMParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS)) | TMPARAMETER_CALIBRATION_NONE, fValue))
			{
				pTMEnvironment->Unlock();
				return TRUE;
			}
			break;
		}
		pTMEnvironment->Unlock();
	}
	return FALSE;
}

CTimeTag CJScriptTelemetryInterface::GetParameterValueTime(LPCTSTR pszTag, INT nOccurrence) CONST
{
	INT  nIndex;
	CTimeTag  tUpdate;
	CTMParameter  *pTMParameter;
	CTMEnvironment  *pTMEnvironment;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pTMEnvironment = ((nIndex = FindProcessIndex()) >= 0) ? (CTMEnvironment *)m_pTMEnvironments.GetAt(nIndex) : (CTMEnvironment *)NULL))
	{
		for (pTMEnvironment->Lock(); (pTMParameter = pTMEnvironment->GetTMParameters()->GetAt(pTMEnvironment->GetTMParameters()->Find(pszTag))); )
		{
			tUpdate = pTMParameter->GetValueTime(nOccurrence);
			pTMEnvironment->Unlock();
			return tUpdate;
		}
		pTMEnvironment->Unlock();
	}
	return 0;
}

BOOL CJScriptTelemetryInterface::SetParameterPastValueSamples(LPCTSTR pszTag, WORD wSamples)
{
	INT  nIndex;
	CTMParameter  *pTMParameter;
	CTMEnvironment  *pTMEnvironment;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pTMEnvironment = ((nIndex = FindProcessIndex()) >= 0) ? (CTMEnvironment *)m_pTMEnvironments.GetAt(nIndex) : (CTMEnvironment *)NULL))
	{
		for (pTMEnvironment->Lock(); (pTMParameter = pTMEnvironment->GetTMParameters()->GetAt(pTMEnvironment->GetTMParameters()->Find(pszTag))); )
		{
			pTMParameter->SetPastValueSamples(max(pTMParameter->GetPastValueSamples(), wSamples));
			pTMEnvironment->Unlock();
			return TRUE;
		}
		pTMEnvironment->Unlock();
	}
	return FALSE;
}

WORD CJScriptTelemetryInterface::GetParameterPastValueSamples(LPCTSTR pszTag) CONST
{
	INT  nIndex;
	WORD  wSamples;
	CTMParameter  *pTMParameter;
	CTMEnvironment  *pTMEnvironment;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pTMEnvironment = ((nIndex = FindProcessIndex()) >= 0) ? (CTMEnvironment *)m_pTMEnvironments.GetAt(nIndex) : (CTMEnvironment *)NULL))
	{
		for (pTMEnvironment->Lock(); (pTMParameter = pTMEnvironment->GetTMParameters()->GetAt(pTMEnvironment->GetTMParameters()->Find(pszTag))); )
		{
			wSamples = pTMParameter->GetPastValueSamples();
			pTMEnvironment->Unlock();
			return wSamples;
		}
		pTMEnvironment->Unlock();
	}
	return 0;
}

BOOL CJScriptTelemetryInterface::GetParameterPastIntValue(LPCTSTR pszTag, INT nSample, LONGLONG &nValue) CONST
{
	INT  nIndex;
	double  fValue;
	CTMParameter  *pTMParameter;
	CTMEnvironment  *pTMEnvironment;
	CDatabaseEngine  *pDatabase;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pTMEnvironment = ((pDatabase = ((nIndex = FindProcessIndex()) >= 0) ? (CDatabaseEngine *)m_pDatabases.GetAt(nIndex) : (CDatabaseEngine *)NULL)) ? (CTMEnvironment *)m_pTMEnvironments.GetAt(nIndex) : (CTMEnvironment *)NULL))
	{
		for (pTMEnvironment->Lock(); (pTMParameter = pTMEnvironment->GetTMParameters()->GetAt(pTMEnvironment->GetTMParameters()->Find(pszTag))) != (CTMParameter *)NULL; )
		{
			if (((pTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS)) == 0) && ((pTMParameter->GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) || (pTMParameter->GetAttributes() & TMPARAMETER_CODING_COMPLEMENTCOMPLEX)))
			{
				if (pTMParameter->GetValue(pDatabase, nSample, fValue, TRUE))
				{
					nValue = (LONGLONG)fValue;
					pTMEnvironment->Unlock();
					return TRUE;
				}
			}
			break;
		}
		pTMEnvironment->Unlock();
	}
	return FALSE;
}

BOOL CJScriptTelemetryInterface::GetParameterPastUIntValue(LPCTSTR pszTag, INT nSample, ULONGLONG &nValue) CONST
{
	INT  nIndex;
	double  fValue;
	CTMParameter  *pTMParameter;
	CTMEnvironment  *pTMEnvironment;
	CDatabaseEngine  *pDatabase;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pTMEnvironment = ((pDatabase = ((nIndex = FindProcessIndex()) >= 0) ? (CDatabaseEngine *)m_pDatabases.GetAt(nIndex) : (CDatabaseEngine *)NULL)) ? (CTMEnvironment *)m_pTMEnvironments.GetAt(nIndex) : (CTMEnvironment *)NULL))
	{
		for (pTMEnvironment->Lock(); (pTMParameter = pTMEnvironment->GetTMParameters()->GetAt(pTMEnvironment->GetTMParameters()->Find(pszTag))); )
		{
			if (((pTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS)) == 0) && ((pTMParameter->GetAttributes() & TMPARAMETER_CODING_BITPATTERN) || (pTMParameter->GetAttributes() & TMPARAMETER_CODING_INVERSEBITPATTERN) || (pTMParameter->GetAttributes() & TMPARAMETER_CODING_UNSIGNEDINTEGER) || (pTMParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_FLOATINGPOINT)) == 0))
			{
				if (pTMParameter->GetValue(pDatabase, nSample, fValue, TRUE))
				{
					nValue = (ULONGLONG)fValue;
					pTMEnvironment->Unlock();
					return TRUE;
				}
			}
			break;
		}
		pTMEnvironment->Unlock();
	}
	return FALSE;
}

BOOL CJScriptTelemetryInterface::GetParameterPastFloatValue(LPCTSTR pszTag, INT nSample, double &fValue) CONST
{
	INT  nIndex;
	CTMParameter  *pTMParameter;
	CTMEnvironment  *pTMEnvironment;
	CDatabaseEngine  *pDatabase;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pTMEnvironment = ((pDatabase = ((nIndex = FindProcessIndex()) >= 0) ? (CDatabaseEngine *)m_pDatabases.GetAt(nIndex) : (CDatabaseEngine *)NULL)) ? (CTMEnvironment *)m_pTMEnvironments.GetAt(nIndex) : (CTMEnvironment *)NULL))
	{
		for (pTMEnvironment->Lock(); (pTMParameter = pTMEnvironment->GetTMParameters()->GetAt(pTMEnvironment->GetTMParameters()->Find(pszTag))) != (CTMParameter *)NULL; )
		{
			if ((((pTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS)) == 0) && (pTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT)) || (pTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL))
			{
				if (pTMParameter->GetValue(pDatabase, nSample, fValue, TRUE))
				{
					pTMEnvironment->Unlock();
					return TRUE;
				}
			}
			break;
		}
		pTMEnvironment->Unlock();
	}
	return FALSE;
}

BOOL CJScriptTelemetryInterface::GetParameterPastStringValue(LPCTSTR pszTag, INT nSample, CString &szValue) CONST
{
	INT  nIndex;
	CTMParameter  *pTMParameter;
	CTMEnvironment  *pTMEnvironment;
	CDatabaseEngine  *pDatabase;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pTMEnvironment = ((pDatabase = ((nIndex = FindProcessIndex()) >= 0) ? (CDatabaseEngine *)m_pDatabases.GetAt(nIndex) : (CDatabaseEngine *)NULL)) ? (CTMEnvironment *)m_pTMEnvironments.GetAt(nIndex) : (CTMEnvironment *)NULL))
	{
		for (pTMEnvironment->Lock(); (pTMParameter = pTMEnvironment->GetTMParameters()->GetAt(pTMEnvironment->GetTMParameters()->Find(pszTag))) && (pTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS); )
		{
			if (pTMParameter->GetValueAsText(pDatabase, nSample, szValue, TRUE))
			{
				pTMEnvironment->Unlock();
				return TRUE;
			}
			break;
		}
		pTMEnvironment->Unlock();
	}
	return FALSE;
}

BOOL CJScriptTelemetryInterface::GetParameterPastRawIntValue(LPCTSTR pszTag, INT nSample, LONGLONG &nValue) CONST
{
	INT  nIndex;
	UINT  nStatus;
	ULONGLONG  nRawValue;
	CTMParameter  *pTMParameter;
	CTMEnvironment  *pTMEnvironment;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pTMEnvironment = ((nIndex = FindProcessIndex()) >= 0) ? (CTMEnvironment *)m_pTMEnvironments.GetAt(nIndex) : (CTMEnvironment *)NULL))
	{
		for (pTMEnvironment->Lock(); (pTMParameter = pTMEnvironment->GetTMParameters()->GetAt(pTMEnvironment->GetTMParameters()->Find(pszTag))); )
		{
			if ((pTMParameter->GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) || (pTMParameter->GetAttributes() & TMPARAMETER_CODING_COMPLEMENTCOMPLEX))
			{
				if (pTMParameter->GetRawValue(nSample, nRawValue, nStatus, TRUE))
				{
					nValue = (LONGLONG)nRawValue;
					pTMEnvironment->Unlock();
					return TRUE;
				}
			}
			break;
		}
		pTMEnvironment->Unlock();
	}
	return FALSE;
}

BOOL CJScriptTelemetryInterface::GetParameterPastRawUIntValue(LPCTSTR pszTag, INT nSample, ULONGLONG &nValue) CONST
{
	INT  nIndex;
	UINT  nStatus;
	ULONGLONG  nRawValue;
	CTMParameter  *pTMParameter;
	CTMEnvironment  *pTMEnvironment;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pTMEnvironment = ((nIndex = FindProcessIndex()) >= 0) ? (CTMEnvironment *)m_pTMEnvironments.GetAt(nIndex) : (CTMEnvironment *)NULL))
	{
		for (pTMEnvironment->Lock(); (pTMParameter = pTMEnvironment->GetTMParameters()->GetAt(pTMEnvironment->GetTMParameters()->Find(pszTag))); )
		{
			if ((pTMParameter->GetAttributes() & TMPARAMETER_CODING_BITPATTERN) || (pTMParameter->GetAttributes() & TMPARAMETER_CODING_INVERSEBITPATTERN) || (pTMParameter->GetAttributes() & TMPARAMETER_CODING_UNSIGNEDINTEGER) || (pTMParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_FLOATINGPOINT)) == 0)
			{
				if (pTMParameter->GetRawValue(nSample, nRawValue, nStatus, TRUE))
				{
					nValue = nRawValue;
					pTMEnvironment->Unlock();
					return TRUE;
				}
			}
			break;
		}
		pTMEnvironment->Unlock();
	}
	return FALSE;
}

BOOL CJScriptTelemetryInterface::GetParameterPastRawFloatValue(LPCTSTR pszTag, INT nSample, double &fValue) CONST
{
	INT  nIndex;
	CTMParameter  *pTMParameter;
	CTMEnvironment  *pTMEnvironment;
	CDatabaseEngine  *pDatabase;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pTMEnvironment = ((pDatabase = ((nIndex = FindProcessIndex()) >= 0) ? (CDatabaseEngine *)m_pDatabases.GetAt(nIndex) : (CDatabaseEngine *)NULL)) ? (CTMEnvironment *)m_pTMEnvironments.GetAt(nIndex) : (CTMEnvironment *)NULL))
	{
		for (pTMEnvironment->Lock(); (pTMParameter = pTMEnvironment->GetTMParameters()->GetAt(pTMEnvironment->GetTMParameters()->Find(pszTag))) != (CTMParameter *)NULL; )
		{
			if (pTMParameter->GetValue(pDatabase, nSample, (pTMParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS)) | TMPARAMETER_CALIBRATION_NONE, fValue, TRUE))
			{
				pTMEnvironment->Unlock();
				return TRUE;
			}
			break;
		}
		pTMEnvironment->Unlock();
	}
	return FALSE;
}

CTimeTag CJScriptTelemetryInterface::GetParameterPastValueTime(LPCTSTR pszTag, INT nSample) CONST
{
	INT  nIndex;
	CTimeTag  tUpdate;
	CTMParameter  *pTMParameter;
	CTMEnvironment  *pTMEnvironment;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pTMEnvironment = ((nIndex = FindProcessIndex()) >= 0) ? (CTMEnvironment *)m_pTMEnvironments.GetAt(nIndex) : (CTMEnvironment *)NULL))
	{
		for (pTMEnvironment->Lock(); (pTMParameter = pTMEnvironment->GetTMParameters()->GetAt(pTMEnvironment->GetTMParameters()->Find(pszTag))); )
		{
			tUpdate = pTMParameter->GetValueTime(nSample, TRUE);
			pTMEnvironment->Unlock();
			return tUpdate;
		}
		pTMEnvironment->Unlock();
	}
	return 0;
}

CTimeTag CJScriptTelemetryInterface::GetParameterLastUpdateTime(LPCTSTR pszTag) CONST
{
	INT  nIndex;
	CTimeTag  tUpdate;
	CTMParameter  *pTMParameter;
	CTMEnvironment  *pTMEnvironment;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pTMEnvironment = ((nIndex = FindProcessIndex()) >= 0) ? (CTMEnvironment *)m_pTMEnvironments.GetAt(nIndex) : (CTMEnvironment *)NULL))
	{
		for (pTMEnvironment->Lock(); (pTMParameter = pTMEnvironment->GetTMParameters()->GetAt(pTMEnvironment->GetTMParameters()->Find(pszTag))); )
		{
			tUpdate = pTMParameter->GetLastUpdateTime();
			pTMEnvironment->Unlock();
			return tUpdate;
		}
		pTMEnvironment->Unlock();
	}
	return 0;
}

CTimeTag CJScriptTelemetryInterface::GetParameterLastChangeTime(LPCTSTR pszTag) CONST
{
	INT  nIndex;
	CTimeTag  tChange;
	CTMParameter  *pTMParameter;
	CTMEnvironment  *pTMEnvironment;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pTMEnvironment = ((nIndex = FindProcessIndex()) >= 0) ? (CTMEnvironment *)m_pTMEnvironments.GetAt(nIndex) : (CTMEnvironment *)NULL))
	{
		for (pTMEnvironment->Lock(); (pTMParameter = pTMEnvironment->GetTMParameters()->GetAt(pTMEnvironment->GetTMParameters()->Find(pszTag))); )
		{
			tChange = pTMParameter->GetLastChangeTime();
			pTMEnvironment->Unlock();
			return tChange;
		}
		pTMEnvironment->Unlock();
	}
	return 0;
}

UINT CJScriptTelemetryInterface::GetParameterStatus(LPCTSTR pszTag, INT nSample) CONST
{
	INT  nIndex;
	UINT  nStatus;
	ULONGLONG  nRawValue;
	CTMParameter  *pTMParameter;
	CTMEnvironment  *pTMEnvironment;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pTMEnvironment = ((nIndex = FindProcessIndex()) >= 0) ? (CTMEnvironment *)m_pTMEnvironments.GetAt(nIndex) : (CTMEnvironment *)NULL))
	{
		for (pTMEnvironment->Lock(); (pTMParameter = pTMEnvironment->GetTMParameters()->GetAt(pTMEnvironment->GetTMParameters()->Find(pszTag))); )
		{
			if (pTMParameter->GetRawValue(nSample, nRawValue, nStatus))
			{
				pTMEnvironment->Unlock();
				return nStatus;
			}
			break;
		}
		pTMEnvironment->Unlock();
	}
	return TMPARAMETER_STATUS_NONE;
}

BOOL CJScriptTelemetryInterface::Lock(LPCTSTR pszName)
{
	INT  nIndex;
	CTMEnvironment  *pTMEnvironment;

	if ((pTMEnvironment = ((nIndex = FindProcessIndex()) >= 0) ? (CTMEnvironment *)m_pTMEnvironments.GetAt(nIndex) : (CTMEnvironment *)NULL) && pTMEnvironment->Lock())
	{
		UpdateProcessCount(nIndex, pszName, 1);
		return TRUE;
	}
	return FALSE;
}

BOOL CJScriptTelemetryInterface::Unlock(LPCTSTR pszName)
{
	INT  nIndex;
	CTMEnvironment  *pTMEnvironment;

	if ((pTMEnvironment = ((nIndex = FindProcessIndex()) >= 0) ? (CTMEnvironment *)m_pTMEnvironments.GetAt(nIndex) : (CTMEnvironment *)NULL) && pTMEnvironment->Unlock())
	{
		UpdateProcessCount(nIndex, pszName, -1);
		return TRUE;
	}
	return FALSE;
}

BOOL CJScriptTelemetryInterface::Exit(LPCTSTR pszName, BOOL bCode)
{
	INT  nIndex;
	CTMEnvironment  *pTMEnvironment;

	if ((pTMEnvironment = ((nIndex = FindProcessIndex()) >= 0) ? (CTMEnvironment *)m_pTMEnvironments.GetAt(nIndex) : (CTMEnvironment *)NULL))
	{
		for (; UpdateProcessCount(nIndex, pszName, 0) > 0; UpdateProcessCount(nIndex, pszName, -1))
		{
			pTMEnvironment->Unlock();
			continue;
		}
		return bCode;
	}
	return FALSE;
}

INT CJScriptTelemetryInterface::FindProcessIndex() CONST
{
	INT  nProcess;
	INT  nProcesses;
	DWORD  dwProcessID;

	for (nProcess = 0, nProcesses = (INT)m_dwProcessIDs.GetSize(), dwProcessID = GetCurrentProcessId(); nProcess < nProcesses; nProcess++)
	{
		if (m_dwProcessIDs.GetAt(nProcess) == dwProcessID) break;
		continue;
	}
	return((nProcess < nProcesses) ? nProcess : -1);
}

LONGLONG CJScriptTelemetryInterface::UpdateProcessCount(INT nIndex, LPCTSTR pszName, INT nDelta)
{
	INT  nPos[2];
	CString  szCounts;
	CStringTools  cStringTools;
	LONGLONG  lCount;

	if (nIndex < m_szProcessCounts.GetSize())
	{
		for (szCounts = m_szProcessCounts.GetAt(nIndex); (nPos[0] = szCounts.Find(CString(pszName) + TAB)) >= 0; )
		{
			szCounts = ((nPos[1] = szCounts.Mid(nPos[0]).Find(EOL)) >= 0) ? (szCounts.Left(nPos[0]) + pszName + TAB + cStringTools.ConvertLongUIntToString((lCount = _ttoi64(szCounts.Mid(nPos[0] + lstrlen(pszName) + 1))) + nDelta) + EOL + szCounts.Mid(nPos[0] + nPos[1] + 1)) : (szCounts.Left(nPos[0]) + pszName + TAB + cStringTools.ConvertLongUIntToString((lCount = _ttoi64(szCounts.Mid(nPos[0] + lstrlen(pszName) + 1))) + nDelta) + EOL);
			m_szProcessCounts.SetAt(nIndex, szCounts);
			return lCount;
		}
		szCounts += CString(pszName) + TAB + cStringTools.ConvertLongUIntToString(nDelta) + EOL;
		m_szProcessCounts.SetAt(nIndex, szCounts);
		return 0;
	}
	return -1;
}


/////////////////////////////////////////////////////////////////////////////
// CJScriptTelemetryInterface exports

BOOL InitializeJScriptTelemetryInterface(CONST CDatabaseEngine *pDatabase, CTMEnvironment *pTMEnvironment)
{
	return cJScriptTelemetryInterface.Initialize(pDatabase, pTMEnvironment);
}

BOOL UninitializeJScriptTelemetryInterface()
{
	return cJScriptTelemetryInterface.Uninitialize();
}

BOOL GetJScriptTelemetryInterfaceParameterIntValue(LPCWSTR pszTag, INT nSample, LONGLONG &nValue)
{
	BOOL  bResult;
	CString  szTag;

#ifndef UNICODE
	WideCharToMultiByte(CP_ACP, 0, pszTag, -1, szTag.GetBufferSetLength((INT)wcslen(pszTag)), (INT)wcslen(pszTag) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
	bResult = cJScriptTelemetryInterface.GetParameterIntValue(szTag, nSample, nValue);
	szTag.ReleaseBuffer();
#else
	bResult = cJScriptTelemetryInterface.GetParameterIntValue(pszTag, nSample, nValue);
#endif
	return bResult;
}

BOOL GetJScriptTelemetryInterfaceParameterUIntValue(LPCWSTR pszTag, INT nSample, ULONGLONG &nValue)
{
	BOOL  bResult;
	CString  szTag;

#ifndef UNICODE
	WideCharToMultiByte(CP_ACP, 0, pszTag, -1, szTag.GetBufferSetLength((INT)wcslen(pszTag)), (INT)wcslen(pszTag) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
	bResult = cJScriptTelemetryInterface.GetParameterUIntValue(szTag, nSample, nValue);
	szTag.ReleaseBuffer();
#else
	bResult = cJScriptTelemetryInterface.GetParameterUIntValue(pszTag, nSample, nValue);
#endif
	return bResult;
}

BOOL GetJScriptTelemetryInterfaceParameterFloatValue(LPCWSTR pszTag, INT nSample, double &fValue)
{
	BOOL  bResult;
	CString  szTag;

#ifndef UNICODE
	WideCharToMultiByte(CP_ACP, 0, pszTag, -1, szTag.GetBufferSetLength((INT)wcslen(pszTag)), (INT)wcslen(pszTag) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
	bResult = cJScriptTelemetryInterface.GetParameterFloatValue(szTag, nSample, fValue);
	szTag.ReleaseBuffer();
#else
	bResult = cJScriptTelemetryInterface.GetParameterFloatValue(pszTag, nSample, fValue);
#endif
	return bResult;
}

BOOL GetJScriptTelemetryInterfaceParameterStringValue(LPCWSTR pszTag, INT nSample, LPWSTR *pszValue)
{
	BOOL  bResult;
	CString  szTag;
	CString  szValue;

#ifndef UNICODE
	WideCharToMultiByte(CP_ACP, 0, pszTag, -1, szTag.GetBufferSetLength((INT)wcslen(pszTag)), (INT)wcslen(pszTag) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
	bResult = cJScriptTelemetryInterface.GetParameterStringValue(szTag, nSample, szValue);
	szTag.ReleaseBuffer();
#else
	bResult = cJScriptTelemetryInterface.GetParameterStringValue(pszTag, nSample, szValue);
#endif
	if ((*pszValue = (bResult) ? (LPWSTR)GlobalAlloc(GPTR, (szValue.GetLength() + 1)*sizeof(WCHAR)) : (LPWSTR)NULL))
	{
#ifndef UNICODE
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szValue, -1, *pszValue, szValue.GetLength() + 1);
#else
		wcscpy_s(*pszValue, szValue.GetLength() + 1, szValue);
#endif
		return TRUE;
	}
	return FALSE;
}

BOOL GetJScriptTelemetryInterfaceParameterRawIntValue(LPCWSTR pszTag, INT nSample, LONGLONG &nValue)
{
	BOOL  bResult;
	CString  szTag;

#ifndef UNICODE
	WideCharToMultiByte(CP_ACP, 0, pszTag, -1, szTag.GetBufferSetLength((INT)wcslen(pszTag)), (INT)wcslen(pszTag) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
	bResult = cJScriptTelemetryInterface.GetParameterRawIntValue(szTag, nSample, nValue);
	szTag.ReleaseBuffer();
#else
	bResult = cJScriptTelemetryInterface.GetParameterRawIntValue(pszTag, nSample, nValue);
#endif
	return bResult;
}

BOOL GetJScriptTelemetryInterfaceParameterRawUIntValue(LPCWSTR pszTag, INT nSample, ULONGLONG &nValue)
{
	BOOL  bResult;
	CString  szTag;

#ifndef UNICODE
	WideCharToMultiByte(CP_ACP, 0, pszTag, -1, szTag.GetBufferSetLength((INT)wcslen(pszTag)), (INT)wcslen(pszTag) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
	bResult = cJScriptTelemetryInterface.GetParameterRawUIntValue(szTag, nSample, nValue);
	szTag.ReleaseBuffer();
#else
	bResult = cJScriptTelemetryInterface.GetParameterRawUIntValue(pszTag, nSample, nValue);
#endif
	return bResult;
}

BOOL GetJScriptTelemetryInterfaceParameterRawFloatValue(LPCWSTR pszTag, INT nSample, double &fValue)
{
	BOOL  bResult;
	CString  szTag;

#ifndef UNICODE
	WideCharToMultiByte(CP_ACP, 0, pszTag, -1, szTag.GetBufferSetLength((INT)wcslen(pszTag)), (INT)wcslen(pszTag) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
	bResult = cJScriptTelemetryInterface.GetParameterRawFloatValue(szTag, nSample, fValue);
	szTag.ReleaseBuffer();
#else
	bResult = cJScriptTelemetryInterface.GetParameterRawFloatValue(pszTag, nSample, fValue);
#endif
	return bResult;
}

TIMETAG GetJScriptTelemetryInterfaceParameterValueTime(LPCWSTR pszTag, INT nSample)
{
	CString  szTag;
	TIMETAG  tTime;

#ifndef UNICODE
	WideCharToMultiByte(CP_ACP, 0, pszTag, -1, szTag.GetBufferSetLength((INT)wcslen(pszTag)), (INT)wcslen(pszTag) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
	tTime = cJScriptTelemetryInterface.GetParameterValueTime(szTag, nSample).GetTime();
	szTag.ReleaseBuffer();
#else
	tTime = cJScriptTelemetryInterface.GetParameterValueTime(pszTag, nSample).GetTime();
#endif
	return tTime;
}

BOOL SetJScriptTelemetryInterfaceParameterPastValueSamples(LPCWSTR pszTag, WORD wSamples)
{
	BOOL  bResult;
	CString  szTag;

#ifndef UNICODE
	WideCharToMultiByte(CP_ACP, 0, pszTag, -1, szTag.GetBufferSetLength((INT)wcslen(pszTag)), (INT)wcslen(pszTag) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
	bResult = cJScriptTelemetryInterface.SetParameterPastValueSamples(szTag, wSamples);
	szTag.ReleaseBuffer();
#else
	bResult = cJScriptTelemetryInterface.SetParameterPastValueSamples(pszTag, wSamples);
#endif
	return bResult;
}

WORD GetJScriptTelemetryInterfaceParameterPastValueSamples(LPCWSTR pszTag)
{
	WORD  wSamples;
	CString  szTag;

#ifndef UNICODE
	WideCharToMultiByte(CP_ACP, 0, pszTag, -1, szTag.GetBufferSetLength((INT)wcslen(pszTag)), (INT)wcslen(pszTag) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
	wSamples = cJScriptTelemetryInterface.GetParameterPastValueSamples(szTag);
	szTag.ReleaseBuffer();
#else
	wSamples = cJScriptTelemetryInterface.GetParameterPastValueSamples(pszTag);
#endif
	return wSamples;
}

BOOL GetJScriptTelemetryInterfaceParameterPastIntValue(LPCWSTR pszTag, INT nSample, LONGLONG &nValue)
{
	BOOL  bResult;
	CString  szTag;

#ifndef UNICODE
	WideCharToMultiByte(CP_ACP, 0, pszTag, -1, szTag.GetBufferSetLength((INT)wcslen(pszTag)), (INT)wcslen(pszTag) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
	bResult = cJScriptTelemetryInterface.GetParameterPastIntValue(szTag, nSample, nValue);
	szTag.ReleaseBuffer();
#else
	bResult = cJScriptTelemetryInterface.GetParameterPastIntValue(pszTag, nSample, nValue);
#endif
	return bResult;
}

BOOL GetJScriptTelemetryInterfaceParameterPastUIntValue(LPCWSTR pszTag, INT nSample, ULONGLONG &nValue)
{
	BOOL  bResult;
	CString  szTag;

#ifndef UNICODE
	WideCharToMultiByte(CP_ACP, 0, pszTag, -1, szTag.GetBufferSetLength((INT)wcslen(pszTag)), (INT)wcslen(pszTag) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
	bResult = cJScriptTelemetryInterface.GetParameterPastUIntValue(szTag, nSample, nValue);
	szTag.ReleaseBuffer();
#else
	bResult = cJScriptTelemetryInterface.GetParameterPastUIntValue(pszTag, nSample, nValue);
#endif
	return bResult;
}

BOOL GetJScriptTelemetryInterfaceParameterPastFloatValue(LPCWSTR pszTag, INT nSample, double &fValue)
{
	BOOL  bResult;
	CString  szTag;

#ifndef UNICODE
	WideCharToMultiByte(CP_ACP, 0, pszTag, -1, szTag.GetBufferSetLength((INT)wcslen(pszTag)), (INT)wcslen(pszTag) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
	bResult = cJScriptTelemetryInterface.GetParameterPastFloatValue(szTag, nSample, fValue);
	szTag.ReleaseBuffer();
#else
	bResult = cJScriptTelemetryInterface.GetParameterPastFloatValue(pszTag, nSample, fValue);
#endif
	return bResult;
}

BOOL GetJScriptTelemetryInterfaceParameterPastStringValue(LPCWSTR pszTag, INT nSample, LPWSTR *pszValue)
{
	BOOL  bResult;
	CString  szTag;
	CString  szValue;

#ifndef UNICODE
	WideCharToMultiByte(CP_ACP, 0, pszTag, -1, szTag.GetBufferSetLength((INT)wcslen(pszTag)), (INT)wcslen(pszTag) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
	bResult = cJScriptTelemetryInterface.GetParameterPastStringValue(szTag, nSample, szValue);
	szTag.ReleaseBuffer();
#else
	bResult = cJScriptTelemetryInterface.GetParameterPastStringValue(pszTag, nSample, szValue);
#endif
	if ((*pszValue = (bResult) ? (LPWSTR)GlobalAlloc(GPTR, (szValue.GetLength() + 1)*sizeof(WCHAR)) : (LPWSTR)NULL))
	{
#ifndef UNICODE
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szValue, -1, *pszValue, szValue.GetLength() + 1);
#else
		wcscpy_s(*pszValue, szValue.GetLength() + 1, szValue);
#endif
		return TRUE;
	}
	return FALSE;
}

BOOL GetJScriptTelemetryInterfaceParameterPastRawIntValue(LPCWSTR pszTag, INT nSample, LONGLONG &nValue)
{
	BOOL  bResult;
	CString  szTag;

#ifndef UNICODE
	WideCharToMultiByte(CP_ACP, 0, pszTag, -1, szTag.GetBufferSetLength((INT)wcslen(pszTag)), (INT)wcslen(pszTag) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
	bResult = cJScriptTelemetryInterface.GetParameterPastRawIntValue(szTag, nSample, nValue);
	szTag.ReleaseBuffer();
#else
	bResult = cJScriptTelemetryInterface.GetParameterPastRawIntValue(pszTag, nSample, nValue);
#endif
	return bResult;
}

BOOL GetJScriptTelemetryInterfaceParameterPastRawUIntValue(LPCWSTR pszTag, INT nSample, ULONGLONG &nValue)
{
	BOOL  bResult;
	CString  szTag;

#ifndef UNICODE
	WideCharToMultiByte(CP_ACP, 0, pszTag, -1, szTag.GetBufferSetLength((INT)wcslen(pszTag)), (INT)wcslen(pszTag) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
	bResult = cJScriptTelemetryInterface.GetParameterPastRawUIntValue(szTag, nSample, nValue);
	szTag.ReleaseBuffer();
#else
	bResult = cJScriptTelemetryInterface.GetParameterPastRawUIntValue(pszTag, nSample, nValue);
#endif
	return bResult;
}

BOOL GetJScriptTelemetryInterfaceParameterPastRawFloatValue(LPCWSTR pszTag, INT nSample, double &fValue)
{
	BOOL  bResult;
	CString  szTag;

#ifndef UNICODE
	WideCharToMultiByte(CP_ACP, 0, pszTag, -1, szTag.GetBufferSetLength((INT)wcslen(pszTag)), (INT)wcslen(pszTag) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
	bResult = cJScriptTelemetryInterface.GetParameterPastRawFloatValue(szTag, nSample, fValue);
	szTag.ReleaseBuffer();
#else
	bResult = cJScriptTelemetryInterface.GetParameterPastRawFloatValue(pszTag, nSample, fValue);
#endif
	return bResult;
}

TIMETAG GetJScriptTelemetryInterfaceParameterPastValueTime(LPCWSTR pszTag, INT nSample)
{
	CString  szTag;
	TIMETAG  tTime;

#ifndef UNICODE
	WideCharToMultiByte(CP_ACP, 0, pszTag, -1, szTag.GetBufferSetLength((INT)wcslen(pszTag)), (INT)wcslen(pszTag) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
	tTime = cJScriptTelemetryInterface.GetParameterPastValueTime(szTag, nSample).GetTime();
	szTag.ReleaseBuffer();
#else
	tTime = cJScriptTelemetryInterface.GetParameterPastValueTime(pszTag, nSample).GetTime();
#endif
	return tTime;
}

TIMETAG GetJScriptTelemetryInterfaceParameterLastUpdateTime(LPCWSTR pszTag)
{
	CString  szTag;
	TIMETAG  tTime;

#ifndef UNICODE
	WideCharToMultiByte(CP_ACP, 0, pszTag, -1, szTag.GetBufferSetLength((INT)wcslen(pszTag)), (INT)wcslen(pszTag) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
	tTime = cJScriptTelemetryInterface.GetParameterLastUpdateTime(szTag).GetTime();
	szTag.ReleaseBuffer();
#else
	tTime = cJScriptTelemetryInterface.GetParameterLastUpdateTime(pszTag).GetTime();
#endif
	return tTime;
}

TIMETAG GetJScriptTelemetryInterfaceParameterLastChangeTime(LPCWSTR pszTag)
{
	CString  szTag;
	TIMETAG  tTime;

#ifndef UNICODE
	WideCharToMultiByte(CP_ACP, 0, pszTag, -1, szTag.GetBufferSetLength((INT)wcslen(pszTag)), (INT)wcslen(pszTag) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
	tTime = cJScriptTelemetryInterface.GetParameterLastChangeTime(szTag).GetTime();
	szTag.ReleaseBuffer();
#else
	tTime = cJScriptTelemetryInterface.GetParameterLastChangeTime(pszTag).GetTime();
#endif
	return tTime;
}

UINT GetJScriptTelemetryInterfaceParameterStatus(LPCWSTR pszTag, INT nSample)
{
	UINT  nStatus;
	CString  szTag;

#ifndef UNICODE
	WideCharToMultiByte(CP_ACP, 0, pszTag, -1, szTag.GetBufferSetLength((INT)wcslen(pszTag)), (INT)wcslen(pszTag) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
	nStatus = cJScriptTelemetryInterface.GetParameterStatus(szTag, nSample);
	szTag.ReleaseBuffer();
#else
	nStatus = cJScriptTelemetryInterface.GetParameterStatus(pszTag, nSample);
#endif
	return nStatus;
}

BOOL LockJScriptTelemetryInterface(LPCWSTR pszName)
{
#ifndef UNICODE
	TCHAR  szModule[MAX_PATH];

	WideCharToMultiByte(CP_ACP, 0, pszName, -1, szModule, sizeof(szModule) / sizeof(TCHAR), (LPCSTR)NULL, (LPBOOL)NULL);
	return cJScriptTelemetryInterface.Lock(szModule);
#else
	return cJScriptTelemetryInterface.Lock(pszName);
#endif
}

BOOL UnlockJScriptTelemetryInterface(LPCWSTR pszName)
{
#ifndef UNICODE
	TCHAR  szModule[MAX_PATH];

	WideCharToMultiByte(CP_ACP, 0, pszName, -1, szModule, sizeof(szModule) / sizeof(TCHAR), (LPCSTR)NULL, (LPBOOL)NULL);
	return cJScriptTelemetryInterface.Unlock(szModule);
#else
	return cJScriptTelemetryInterface.Unlock(pszName);
#endif
}

BOOL ExitJScriptTelemetryInterface(LPCWSTR pszName, BOOL bCode)
{
#ifndef UNICODE
	TCHAR  szModule[MAX_PATH];

	WideCharToMultiByte(CP_ACP, 0, pszName, -1, szModule, sizeof(szModule) / sizeof(TCHAR), (LPCSTR)NULL, (LPBOOL)NULL);
	return cJScriptTelemetryInterface.Exit(szModule, bCode);
#else
	return cJScriptTelemetryInterface.Exit(pszName, bCode);
#endif
}
