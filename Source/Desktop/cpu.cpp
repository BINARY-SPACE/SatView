// CPU.CPP : CPU Performance Monitor Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the CPU performance
// monitor related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2005/11/28 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CCPUPerformanceMonitor

CCPUPerformanceMonitor::CCPUPerformanceMonitor() : CObject()
{
	PdhSetDefaultRealTimeDataSource(DATA_SOURCE_WBEM);
	PdhOpenQuery((LPCTSTR)NULL, 0, &m_hQuery[0]);
	PdhOpenQuery((LPCTSTR)NULL, 0, &m_hQuery[1]);
}

CCPUPerformanceMonitor::~CCPUPerformanceMonitor()
{
	Stop();
	if (m_hQuery[0]) PdhCloseQuery(m_hQuery[0]);
	if (m_hQuery[1]) PdhCloseQuery(m_hQuery[1]);
}

BOOL CCPUPerformanceMonitor::Start(UINT nCounterIDs)
{
	return UpdateCounters(nCounterIDs);
}

BOOL CCPUPerformanceMonitor::Stop(UINT nCounterIDs)
{
	return UpdateCounters(nCounterIDs, TRUE);
}

BOOL CCPUPerformanceMonitor::Measure(UINT nCounterID, double &fValue)
{
	SYSTEM_INFO  sInfo;
	PDH_HCOUNTER  hCounter;
	PDH_FMT_COUNTERVALUE  sValue;

	for (ZeroMemory(&sValue, sizeof(PDH_FMT_COUNTERVALUE)), fValue = 0.0; (hCounter = UpdateCounter(nCounterID)); )
	{
		if (PdhCollectQueryData(m_hQuery[ConvertCounterIDToQuery(nCounterID)]) == ERROR_SUCCESS  &&  PdhGetFormattedCounterValue(hCounter, PDH_FMT_DOUBLE | PDH_FMT_NOCAP100, (LPDWORD)NULL, &sValue) == ERROR_SUCCESS)
		{
			if (sValue.CStatus == PDH_CSTATUS_NEW_DATA || sValue.CStatus == PDH_CSTATUS_VALID_DATA)
			{
				if (nCounterID != CPUPERFORMANCEMONITOR_COUNTER_PROCESSORTIME)
				{
					fValue = sValue.doubleValue;
					return TRUE;
				}
				GetSystemInfo(&sInfo);
				fValue = sValue.doubleValue / (double)max(sInfo.dwNumberOfProcessors, 1);
				fValue = min(fValue, 100.0);
				return TRUE;
			}
		}
		break;
	}
	return FALSE;
}
CString CCPUPerformanceMonitor::Measure(UINT nCounterID)
{
	DWORD  cbInfo;
	CString  szValue;
	SYSTEM_INFO  sInfo;
	PDH_HCOUNTER  hCounter;
	PPDH_COUNTER_INFO  pInfo;
	PDH_FMT_COUNTERVALUE  sValue;
	CStringTools  cStringTools;

	for (ZeroMemory(&sValue, sizeof(PDH_FMT_COUNTERVALUE)); (hCounter = UpdateCounter(nCounterID)); )
	{
		if (PdhCollectQueryData(m_hQuery[ConvertCounterIDToQuery(nCounterID)]) == ERROR_SUCCESS  &&  PdhGetFormattedCounterValue(hCounter, PDH_FMT_DOUBLE | PDH_FMT_NOCAP100, (LPDWORD)NULL, &sValue) == ERROR_SUCCESS)
		{
			if (sValue.CStatus == PDH_CSTATUS_NEW_DATA || sValue.CStatus == PDH_CSTATUS_VALID_DATA)
			{
				if (PdhGetCounterInfo(hCounter, FALSE, &(cbInfo = 0), (PPDH_COUNTER_INFO)NULL) == PDH_MORE_DATA)
				{
					if ((pInfo = (PPDH_COUNTER_INFO)GlobalAlloc(GPTR, cbInfo)))
					{
						if (PdhGetCounterInfo(hCounter, FALSE, &cbInfo, pInfo) == ERROR_SUCCESS)
						{
							if (nCounterID == CPUPERFORMANCEMONITOR_COUNTER_TOTALPROCESSORTIME)
							{
								szValue.Format(ConvertCounterIDToString(nCounterID), pInfo->szCounterName, (LPCTSTR)cStringTools.ConvertUIntToString((UINT)sValue.doubleValue));
								GlobalFree(pInfo);
								return szValue;
							}
							if (nCounterID == CPUPERFORMANCEMONITOR_COUNTER_PROCESSORTIME)
							{
								for (GetSystemInfo(&sInfo); sValue.doubleValue >= 0.0; )
								{
									szValue.Format(ConvertCounterIDToString(nCounterID), pInfo->szCounterName, (LPCTSTR)cStringTools.ConvertUIntToString((UINT)min(sValue.doubleValue / (double)max(sInfo.dwNumberOfProcessors, 1), 100.0)));
									break;
								}
								GlobalFree(pInfo);
								return szValue;
							}
							if (nCounterID == CPUPERFORMANCEMONITOR_COUNTER_POOLNONPAGEDBYTES || nCounterID == CPUPERFORMANCEMONITOR_COUNTER_POOLPAGEDBYTES || nCounterID == CPUPERFORMANCEMONITOR_COUNTER_PRIVATEBYTES || nCounterID == CPUPERFORMANCEMONITOR_COUNTER_VIRTUALBYTES)
							{
								szValue.Format(ConvertCounterIDToString(nCounterID), pInfo->szCounterName, (LPCTSTR)cStringTools.ConvertLongUIntToStructuredString((ULONGLONG)(sValue.doubleValue / 1024.0)));
								GlobalFree(pInfo);
								return szValue;
							}
							if (nCounterID == CPUPERFORMANCEMONITOR_COUNTER_THREADCOUNT)
							{
								szValue.Format(ConvertCounterIDToString(nCounterID), pInfo->szCounterName, (LPCTSTR)cStringTools.ConvertUIntToString((UINT)sValue.doubleValue));
								GlobalFree(pInfo);
								return szValue;
							}
						}
						GlobalFree(pInfo);
					}
				}
			}
		}
		break;
	}
	return EMPTYSTRING;
}

PDH_HCOUNTER CCPUPerformanceMonitor::IsAvailable(UINT nCounterID) CONST
{
	INT  nIndex;

	return(((nIndex = ConvertCounterIDToIndex(nCounterID)) >= 0 && nIndex < m_hCounters.GetSize()) ? (PDH_HCOUNTER)m_hCounters.GetAt(nIndex) : (PDH_HCOUNTER)NULL);
}

PDH_HCOUNTER CCPUPerformanceMonitor::UpdateCounter(UINT nCounterID, BOOL bAdd)
{
	INT  nIndex;
	INT  nInstanceID;
	PDH_HCOUNTER  hCounter;

	if (bAdd)
	{
		for (nInstanceID = DetermineInstanceID(); (nIndex = ConvertCounterIDToIndex(nCounterID)) < m_nInstanceIDs.GetSize(); )
		{
			if (m_nInstanceIDs.GetAt(nIndex) != nInstanceID)
			{
				if ((hCounter = (PDH_HCOUNTER)m_hCounters.GetAt(nIndex)))
				{
					m_nInstanceIDs.SetAt(nIndex, -1);
					m_hCounters.SetAt(nIndex, NULL);
					PdhRemoveCounter(hCounter);
				}
				break;
			}
			return IsAvailable(nCounterID);
		}
		if (PdhAddCounter(m_hQuery[ConvertCounterIDToQuery(nCounterID)], ConstructCounterPath(nCounterID, nInstanceID), 0, &hCounter) == ERROR_SUCCESS)
		{
			m_nInstanceIDs.SetAtGrow(nIndex, nInstanceID);
			m_hCounters.SetAtGrow(nIndex, hCounter);
			return IsAvailable(nCounterID);
		}
		return((PDH_HCOUNTER)NULL);
	}
	if ((nIndex = ConvertCounterIDToIndex(nCounterID)) < m_nInstanceIDs.GetSize())
	{
		if ((hCounter = (PDH_HCOUNTER)m_hCounters.GetAt(nIndex)))
		{
			m_nInstanceIDs.SetAt(nIndex, -1);
			m_hCounters.SetAt(nIndex, NULL);
			PdhRemoveCounter(hCounter);
		}
	}
	return((PDH_HCOUNTER)NULL);
}

BOOL CCPUPerformanceMonitor::UpdateCounters(UINT nCounterIDs, BOOL bRemove)
{
	INT  nIndex;
	INT  nCount;
	UINT  nCounterID;

	for (nIndex = 0, nCount = CPUPERFORMANCEMONITOR_COUNTERS; nIndex < nCount; nIndex++)
	{
		if (((nCounterID = ConvertIndexToCounterID(nIndex)) & nCounterIDs) && (!UpdateCounter(nCounterID, !bRemove) && !bRemove)) break;
		continue;
	}
	return(nIndex == nCount);
}

CString CCPUPerformanceMonitor::ConstructCounterPath(UINT nCounterID, INT nInstanceID) CONST
{
	INT  nPos;
	CString  szFormat;
	CString  szCounter;
	CComputerToken  cComputerToken;
	CVersionInfo  cVersionInfo;

	for (szCounter.Format(ConvertCounterIDToString(nCounterID, FALSE), (LPCTSTR)cComputerToken.GetComputerName(), (LPCTSTR)cVersionInfo.QueryInternalName(), nInstanceID); !nInstanceID; )
	{
		for (szFormat.Format(STRING(IDS_CPUPERFORMANCEMONITOR_COUNTER_INSTANCEFORMAT), nInstanceID); (nPos = szCounter.Find(szFormat)) >= 0; )
		{
			szCounter = szCounter.Left(nPos) + szCounter.Mid(nPos + szFormat.GetLength());
			break;
		}
		break;
	}
	return((nInstanceID >= 0) ? szCounter : EMPTYSTRING);
}

CString CCPUPerformanceMonitor::ConvertCounterIDToString(UINT nCounterID, BOOL bFormat) CONST
{
	INT  nIndex;

	return(((nIndex = ConvertCounterIDToIndex(nCounterID)) >= 0) ? ((bFormat) ? STRING(MINCPUPERFORMANCECOUNTERFORMATS + nIndex) : STRING(MINCPUPERFORMANCECOUNTERS + nIndex)) : EMPTYSTRING);
}

INT CCPUPerformanceMonitor::ConvertCounterIDToQuery(UINT nCounterID) CONST
{
	return((nCounterID == CPUPERFORMANCEMONITOR_COUNTER_TOTALPROCESSORTIME) ? 1 : 0);
}

INT CCPUPerformanceMonitor::ConvertCounterIDToIndex(UINT nCounterID) CONST
{
	INT  nIndex[2];

	for (nIndex[0] = 0, nIndex[1] = 1; nIndex[1] < CPUPERFORMANCEMONITOR_COUNTER_ALL; nIndex[0]++)
	{
		if (nCounterID & nIndex[1]) break;
		nIndex[1] = nIndex[1] << 1;
	}
	return((nIndex[1] < CPUPERFORMANCEMONITOR_COUNTER_ALL) ? nIndex[0] : -1);
}

UINT CCPUPerformanceMonitor::ConvertIndexToCounterID(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < CPUPERFORMANCEMONITOR_COUNTERS) ? (1 << nIndex) : 0);
}

INT CCPUPerformanceMonitor::DetermineInstanceID() CONST
{
	INT  nInstanceID;
	CString  szCounter;
	PDH_HQUERY  hQuery;
	PDH_HCOUNTER  hCounter;
	PDH_FMT_COUNTERVALUE  sValue;
	CComputerToken  cComputerToken;
	CVersionInfo  cVersionInfo;

	if (PdhOpenQuery((LPCTSTR)NULL, 0, &hQuery) == ERROR_SUCCESS)
	{
		for (ZeroMemory(&sValue, sizeof(PDH_FMT_COUNTERVALUE)), nInstanceID = 0; TRUE; nInstanceID++)
		{
			for (szCounter.Format(STRING(IDS_CPUPERFORMANCEMONITOR_COUNTER_PROCESSID), (LPCTSTR)cComputerToken.GetComputerName(), (LPCTSTR)cVersionInfo.QueryInternalName()); nInstanceID > 0; )
			{
				szCounter.Format(STRING(IDS_CPUPERFORMANCEMONITOR_COUNTER_PROCESSINSTANCEID), (LPCTSTR)cComputerToken.GetComputerName(), (LPCTSTR)cVersionInfo.QueryInternalName(), nInstanceID);
				break;
			}
			if (PdhAddCounter(hQuery, szCounter, 0, &hCounter) == ERROR_SUCCESS)
			{
				if (PdhCollectQueryData(hQuery) == ERROR_SUCCESS  &&  PdhGetFormattedCounterValue(hCounter, PDH_FMT_LONG, (LPDWORD)NULL, &sValue) == ERROR_SUCCESS)
				{
					if (sValue.longValue == GetCurrentProcessId())
					{
						PdhRemoveCounter(hCounter);
						break;
					}
					PdhRemoveCounter(hCounter);
					continue;
				}
				PdhRemoveCounter(hCounter);
			}
			nInstanceID = -1;
			break;
		}
		PdhCloseQuery(hQuery);
		return nInstanceID;
	}
	return -1;
}
