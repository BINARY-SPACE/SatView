// TPEP.CPP : TPEP Display Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the TPEP display
// related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1998/11/23 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static UINT BASED_CODE nTPEPStatusBarIndicators[] =
{
	ID_TPEP_STATUSBAR_MESSAGEPANE,
	ID_TPEP_STATUSBAR_COMPUTERPANE,
	ID_TPEP_STATUSBAR_MODEPANE,
	ID_TPEP_STATUSBAR_TYPEPANE
};



/////////////////////////////////////////////////////////////////////////////
// CTPEPPrintJobInfo

CTPEPPrintJobInfo::CTPEPPrintJobInfo() : CObject()
{
	m_nPrintMode = 0;
	m_nPrintFlags = 0;
	m_nPrintCount[0] = 0;
	m_nPrintCount[1] = 0;
	m_nPrintByCount = 0;
	m_tPrintAtTime = 0;
	m_tPrintAtDailyTime = 0;
	m_tPrintLastTime[0] = 0;
	m_tPrintLastTime[1] = 0;
	m_tRepeatInterval = 0;
	m_nRepeatStopByCount[0] = 0;
	m_nRepeatStopByCount[1] = 0;
	m_tRepeatStopByTime[0] = 0;
	m_tRepeatStopByTime[1] = 0;
}

VOID CTPEPPrintJobInfo::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CTPEPPrintJobInfo::GetName() CONST
{
	return m_szName;
}

VOID CTPEPPrintJobInfo::SetProfile(LPCTSTR pszProfile)
{
	m_szProfile = pszProfile;
}

CString CTPEPPrintJobInfo::GetProfile() CONST
{
	return m_szProfile;
}

VOID CTPEPPrintJobInfo::SetComments(LPCTSTR pszComments)
{
	m_szComments = pszComments;
}

CString CTPEPPrintJobInfo::GetComments() CONST
{
	return m_szComments;
}

BOOL CTPEPPrintJobInfo::SetPrintMode(UINT nMode)
{
	m_nPrintMode = nMode;
	return TRUE;
}

UINT CTPEPPrintJobInfo::GetPrintMode() CONST
{
	return m_nPrintMode;
}

BOOL CTPEPPrintJobInfo::SetPrintFlags(UINT nFlags)
{
	if (nFlags == TPEP_PRINT_ATTIME || nFlags == TPEP_PRINT_ATDAILYTIME || nFlags == TPEP_PRINT_ATEVENT || !nFlags)
	{
		m_nPrintFlags = nFlags;
		return TRUE;
	}
	return FALSE;
}

UINT CTPEPPrintJobInfo::GetPrintFlags() CONST
{
	return m_nPrintFlags;
}

BOOL CTPEPPrintJobInfo::SetPrintBySide(UINT nCount)
{
	if ((m_nPrintMode & TPEP_PRINT_FIRSTSIDE) || (m_nPrintMode & TPEP_PRINT_LASTSIDE))
	{
		m_nPrintByCount = nCount;
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPPrintJobInfo::GetPrintBySide(UINT &nCount) CONST
{
	if ((m_nPrintMode & TPEP_PRINT_FIRSTSIDE) || (m_nPrintMode & TPEP_PRINT_LASTSIDE))
	{
		nCount = m_nPrintByCount;
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPPrintJobInfo::SetPrintAtTime(CONST CTimeKey &tTime)
{
	if ((m_nPrintMode & TPEP_PRINT_ATTIME) && !(m_nPrintMode & TPEP_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & TPEP_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & TPEP_PRINT_REPEATSTOPBYTIME))
	{
		m_tPrintAtTime = tTime;
		m_tRepeatInterval = 0;
		m_tRepeatStopByTime[0] = 0;
		m_nRepeatStopByCount[0] = 0;
		m_tPrintLastTime[0] = 0;
		m_nPrintCount[0] = 0;
		return TRUE;
	}
	return FALSE;
}
BOOL CTPEPPrintJobInfo::SetPrintAtTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval)
{
	if ((m_nPrintMode & TPEP_PRINT_ATTIME) && (m_nPrintMode & TPEP_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & TPEP_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & TPEP_PRINT_REPEATSTOPBYTIME))
	{
		m_tPrintAtTime = tTime;
		m_tRepeatInterval = tInterval;
		m_tRepeatStopByTime[0] = 0;
		m_nRepeatStopByCount[0] = 0;
		m_tPrintLastTime[0] = 0;
		m_nPrintCount[0] = 0;
		return TRUE;
	}
	return FALSE;
}
BOOL CTPEPPrintJobInfo::SetPrintAtTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval, UINT nStopCount)
{
	if ((m_nPrintMode & TPEP_PRINT_ATTIME) && (m_nPrintMode & TPEP_PRINT_REPEATBYINTERVAL) && (m_nPrintMode & TPEP_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & TPEP_PRINT_REPEATSTOPBYTIME))
	{
		m_tPrintAtTime = tTime;
		m_tRepeatInterval = tInterval;
		m_nRepeatStopByCount[0] = nStopCount;
		m_tRepeatStopByTime[0] = 0;
		m_tPrintLastTime[0] = 0;
		m_nPrintCount[0] = 0;
		return TRUE;
	}
	return FALSE;
}
BOOL CTPEPPrintJobInfo::SetPrintAtTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval, CONST CTimeKey &tStopTime)
{
	if ((m_nPrintMode & TPEP_PRINT_ATTIME) && (m_nPrintMode & TPEP_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & TPEP_PRINT_REPEATSTOPBYCOUNT) && (m_nPrintMode & TPEP_PRINT_REPEATSTOPBYTIME))
	{
		m_tPrintAtTime = tTime;
		m_tRepeatInterval = tInterval;
		m_tRepeatStopByTime[0] = tStopTime;
		m_nRepeatStopByCount[0] = 0;
		m_tPrintLastTime[0] = 0;
		m_nPrintCount[0] = 0;
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPPrintJobInfo::GetPrintAtTime(CTimeKey &tTime) CONST
{
	if ((m_nPrintMode & TPEP_PRINT_ATTIME) && !(m_nPrintMode & TPEP_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & TPEP_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & TPEP_PRINT_REPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtTime;
		return TRUE;
	}
	return FALSE;
}
BOOL CTPEPPrintJobInfo::GetPrintAtTime(CTimeKey &tTime, CTimeSpan &tInterval) CONST
{
	if ((m_nPrintMode & TPEP_PRINT_ATTIME) && (m_nPrintMode & TPEP_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & TPEP_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & TPEP_PRINT_REPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtTime;
		tInterval = m_tRepeatInterval;
		return TRUE;
	}
	return FALSE;
}
BOOL CTPEPPrintJobInfo::GetPrintAtTime(CTimeKey &tTime, CTimeSpan &tInterval, UINT &nStopCount) CONST
{
	if ((m_nPrintMode & TPEP_PRINT_ATTIME) && (m_nPrintMode & TPEP_PRINT_REPEATBYINTERVAL) && (m_nPrintMode & TPEP_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & TPEP_PRINT_REPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtTime;
		tInterval = m_tRepeatInterval;
		nStopCount = m_nRepeatStopByCount[0];
		return TRUE;
	}
	return FALSE;
}
BOOL CTPEPPrintJobInfo::GetPrintAtTime(CTimeKey &tTime, CTimeSpan &tInterval, CTimeKey &tStopTime) CONST
{
	if ((m_nPrintMode & TPEP_PRINT_ATTIME) && (m_nPrintMode & TPEP_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & TPEP_PRINT_REPEATSTOPBYCOUNT) && (m_nPrintMode & TPEP_PRINT_REPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtTime;
		tInterval = m_tRepeatInterval;
		tStopTime = m_tRepeatStopByTime[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPPrintJobInfo::SetPrintAtDailyTime(CONST CTimeSpan &tTime)
{
	TIMEKEY  tTimeKey;

	if ((m_nPrintMode & TPEP_PRINT_ATDAILYTIME) && !(m_nPrintMode & TPEP_PRINT_DAILYREPEATSTOPBYCOUNT) && !(m_nPrintMode & TPEP_PRINT_DAILYREPEATSTOPBYTIME))
	{
		m_tPrintAtDailyTime = tTime;
		m_tRepeatStopByTime[1] = 0;
		m_nRepeatStopByCount[1] = 0;
		m_tPrintLastTime[1] = ((tTimeKey = CTime::GetCurrentTime().GetTime()) % SECONDSPERDAY > tTime.GetTotalSeconds()) ? (SECONDSPERDAY*(tTimeKey / SECONDSPERDAY) + tTime.GetTotalSeconds()) : 0;
		m_nPrintCount[1] = 0;
		return TRUE;
	}
	return FALSE;
}
BOOL CTPEPPrintJobInfo::SetPrintAtDailyTime(CONST CTimeSpan &tTime, UINT nStopCount)
{
	TIMEKEY  tTimeKey;

	if ((m_nPrintMode & TPEP_PRINT_ATDAILYTIME) && (m_nPrintMode & TPEP_PRINT_DAILYREPEATSTOPBYCOUNT) && !(m_nPrintMode & TPEP_PRINT_DAILYREPEATSTOPBYTIME))
	{
		m_tPrintAtDailyTime = tTime;
		m_nRepeatStopByCount[1] = nStopCount;
		m_tRepeatStopByTime[1] = 0;
		m_tPrintLastTime[1] = ((tTimeKey = CTime::GetCurrentTime().GetTime()) % SECONDSPERDAY > tTime.GetTotalSeconds()) ? (SECONDSPERDAY*(tTimeKey / SECONDSPERDAY) + tTime.GetTotalSeconds()) : 0;
		m_nPrintCount[1] = 0;
		return TRUE;
	}
	return FALSE;
}
BOOL CTPEPPrintJobInfo::SetPrintAtDailyTime(CONST CTimeSpan &tTime, CONST CTimeKey &tStopTime)
{
	TIMEKEY  tTimeKey;

	if ((m_nPrintMode & TPEP_PRINT_ATDAILYTIME) && !(m_nPrintMode & TPEP_PRINT_DAILYREPEATSTOPBYCOUNT) && (m_nPrintMode & TPEP_PRINT_DAILYREPEATSTOPBYTIME))
	{
		m_tPrintAtDailyTime = tTime;
		m_tRepeatStopByTime[1] = tStopTime;
		m_nRepeatStopByCount[1] = 0;
		m_tPrintLastTime[1] = ((tTimeKey = CTime::GetCurrentTime().GetTime()) % SECONDSPERDAY > tTime.GetTotalSeconds()) ? (SECONDSPERDAY*(tTimeKey / SECONDSPERDAY) + tTime.GetTotalSeconds()) : 0;
		m_nPrintCount[1] = 0;
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPPrintJobInfo::GetPrintAtDailyTime(CTimeSpan &tTime) CONST
{
	if ((m_nPrintMode & TPEP_PRINT_ATDAILYTIME) && !(m_nPrintMode & TPEP_PRINT_DAILYREPEATSTOPBYCOUNT) && !(m_nPrintMode & TPEP_PRINT_DAILYREPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtDailyTime;
		return TRUE;
	}
	return FALSE;
}
BOOL CTPEPPrintJobInfo::GetPrintAtDailyTime(CTimeSpan &tTime, UINT &nStopCount) CONST
{
	if ((m_nPrintMode & TPEP_PRINT_ATDAILYTIME) && (m_nPrintMode & TPEP_PRINT_DAILYREPEATSTOPBYCOUNT) && !(m_nPrintMode & TPEP_PRINT_DAILYREPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtDailyTime;
		nStopCount = m_nRepeatStopByCount[1];
		return TRUE;
	}
	return FALSE;
}
BOOL CTPEPPrintJobInfo::GetPrintAtDailyTime(CTimeSpan &tTime, CTimeKey &tStopTime) CONST
{
	if ((m_nPrintMode & TPEP_PRINT_ATDAILYTIME) && !(m_nPrintMode & TPEP_PRINT_DAILYREPEATSTOPBYCOUNT) && (m_nPrintMode & TPEP_PRINT_DAILYREPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtDailyTime;
		tStopTime = m_tRepeatStopByTime[1];
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPPrintJobInfo::SetPrintAtEvent(LPCTSTR pszEvent)
{
	if (m_nPrintMode & TPEP_PRINT_ATEVENT)
	{
		m_szEvent = pszEvent;
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPPrintJobInfo::GetPrintAtEvent(CString &szEvent) CONST
{
	if (m_nPrintMode & TPEP_PRINT_ATEVENT)
	{
		szEvent = m_szEvent;
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPPrintJobInfo::SetPrintCount(UINT nCount)
{
	if (m_nPrintMode & TPEP_PRINT_ATTIME)
	{
		m_nPrintCount[0] = nCount;
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPPrintJobInfo::GetPrintCount(UINT &nCount) CONST
{
	if (m_nPrintMode & TPEP_PRINT_ATTIME)
	{
		nCount = m_nPrintCount[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPPrintJobInfo::SetPrintDailyCount(UINT nCount)
{
	if (m_nPrintMode & TPEP_PRINT_ATDAILYTIME)
	{
		m_nPrintCount[1] = nCount;
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPPrintJobInfo::GetPrintDailyCount(UINT &nCount) CONST
{
	if (m_nPrintMode & TPEP_PRINT_ATDAILYTIME)
	{
		nCount = m_nPrintCount[1];
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPPrintJobInfo::SetPrintLastTime(CONST CTimeKey &tTime)
{
	if (m_nPrintMode & TPEP_PRINT_ATTIME)
	{
		m_tPrintLastTime[0] = tTime;
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPPrintJobInfo::GetPrintLastTime(CTimeKey &tTime) CONST
{
	if (m_nPrintMode & TPEP_PRINT_ATTIME)
	{
		tTime = m_tPrintLastTime[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPPrintJobInfo::SetPrintLastDailyTime(CONST CTimeKey &tTime)
{
	if (m_nPrintMode & TPEP_PRINT_ATDAILYTIME)
	{
		m_tPrintLastTime[1] = tTime;
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPPrintJobInfo::GetPrintLastDailyTime(CTimeKey &tTime) CONST
{
	if (m_nPrintMode & TPEP_PRINT_ATDAILYTIME)
	{
		tTime = m_tPrintLastTime[1];
		return TRUE;
	}
	return FALSE;
}

VOID CTPEPPrintJobInfo::Copy(CONST CTPEPPrintJobInfo *pJobInfo)
{
	m_szName = pJobInfo->m_szName;
	m_szEvent = pJobInfo->m_szEvent;
	m_szProfile = pJobInfo->m_szProfile;
	m_szComments = pJobInfo->m_szComments;
	m_nPrintMode = pJobInfo->m_nPrintMode;
	m_nPrintFlags = pJobInfo->m_nPrintFlags;
	m_nPrintCount[0] = pJobInfo->m_nPrintCount[0];
	m_nPrintCount[1] = pJobInfo->m_nPrintCount[1];
	m_nPrintByCount = pJobInfo->m_nPrintByCount;
	m_tPrintAtTime = pJobInfo->m_tPrintAtTime;
	m_tPrintAtDailyTime = pJobInfo->m_tPrintAtDailyTime;
	m_tPrintLastTime[0] = pJobInfo->m_tPrintLastTime[0];
	m_tPrintLastTime[1] = pJobInfo->m_tPrintLastTime[1];
	m_tRepeatInterval = pJobInfo->m_tRepeatInterval;
	m_nRepeatStopByCount[0] = pJobInfo->m_nRepeatStopByCount[0];
	m_nRepeatStopByCount[1] = pJobInfo->m_nRepeatStopByCount[1];
	m_tRepeatStopByTime[0] = pJobInfo->m_tRepeatStopByTime[0];
	m_tRepeatStopByTime[1] = pJobInfo->m_tRepeatStopByTime[1];
}

BOOL CTPEPPrintJobInfo::Compare(CONST CTPEPPrintJobInfo *pJobInfo) CONST
{
	return((pJobInfo->m_szName == m_szName  &&  pJobInfo->m_szProfile == m_szProfile  &&  pJobInfo->m_szComments == m_szComments  &&  pJobInfo->m_nPrintMode == m_nPrintMode && ((!(m_nPrintMode & TPEP_PRINT_FIRSTSIDE) && !(m_nPrintMode & TPEP_PRINT_LASTSIDE)) || pJobInfo->m_nPrintByCount == m_nPrintByCount) && (!(m_nPrintMode & TPEP_PRINT_ATTIME) || pJobInfo->m_tPrintAtTime == m_tPrintAtTime) && (!(m_nPrintMode & TPEP_PRINT_ATDAILYTIME) || pJobInfo->m_tPrintAtDailyTime == m_tPrintAtDailyTime) && (!(m_nPrintMode & TPEP_PRINT_ATEVENT) || pJobInfo->m_szEvent == m_szEvent) && (!(m_nPrintMode & TPEP_PRINT_REPEATBYINTERVAL) || pJobInfo->m_tRepeatInterval == m_tRepeatInterval) && (!(m_nPrintMode & TPEP_PRINT_REPEATSTOPBYCOUNT) || pJobInfo->m_nRepeatStopByCount[0] == m_nRepeatStopByCount[0]) && (!(m_nPrintMode & TPEP_PRINT_REPEATSTOPBYTIME) || pJobInfo->m_tRepeatStopByTime[0] == m_tRepeatStopByTime[0]) && (!(m_nPrintMode & TPEP_PRINT_DAILYREPEATSTOPBYCOUNT) || pJobInfo->m_nRepeatStopByCount[1] == m_nRepeatStopByCount[1]) && (!(m_nPrintMode & TPEP_PRINT_DAILYREPEATSTOPBYTIME) || pJobInfo->m_tRepeatStopByTime[1] == m_tRepeatStopByTime[1])) ? TRUE : FALSE);
}

BOOL CTPEPPrintJobInfo::Map(CByteArray &nInfo) CONST
{
	INT  cbData;
	DATA  sData;

	sData.cbName = (m_szName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbEvent = (m_szEvent.GetLength() + 1)*sizeof(TCHAR);
	sData.cbProfile = (m_szProfile.GetLength() + 1)*sizeof(TCHAR);
	sData.cbComments = (m_szComments.GetLength() + 1)*sizeof(TCHAR);
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbName + sData.cbProfile + sData.cbComments + sData.cbEvent)), sData.nPrintMode = m_nPrintMode, sData.nPrintCount[0] = m_nPrintCount[0], sData.nPrintCount[1] = m_nPrintCount[1], sData.nPrintByCount = m_nPrintByCount, sData.tPrintAtTime = m_tPrintAtTime.GetTime(), sData.tPrintAtDailyTime = m_tPrintAtDailyTime.GetTotalSeconds(), sData.tPrintLastTime[0] = m_tPrintLastTime[0].GetTime(), sData.tPrintLastTime[1] = m_tPrintLastTime[1].GetTime(), sData.tRepeatInterval = m_tRepeatInterval.GetTotalSeconds(), sData.nRepeatStopByCount[0] = m_nRepeatStopByCount[0], sData.nRepeatStopByCount[1] = m_nRepeatStopByCount[1], sData.tRepeatStopByTime[0] = m_tRepeatStopByTime[0].GetTime(), sData.tRepeatStopByTime[1] = m_tRepeatStopByTime[1].GetTime(); nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szName, sData.cbName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbName), (LPCTSTR)m_szProfile, sData.cbProfile);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbProfile), (LPCTSTR)m_szComments, sData.cbComments);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbComments), (LPCTSTR)m_szEvent, sData.cbEvent);
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPPrintJobInfo::Unmap(CONST CByteArray &nInfo)
{
	INT  cbData;
	DATA  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbName + sData.cbProfile + sData.cbComments + sData.cbEvent && sData.cbName > 0 && sData.cbProfile > 0 && sData.cbComments > 0 && sData.cbEvent > 0; )
	{
		CopyMemory(m_szName.GetBufferSetLength(STRINGCHARS(sData.cbName)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbName));
		CopyMemory(m_szProfile.GetBufferSetLength(STRINGCHARS(sData.cbProfile)), nInfo.GetData() + (cbData = cbData + sData.cbName), STRINGBYTES(sData.cbProfile));
		CopyMemory(m_szComments.GetBufferSetLength(STRINGCHARS(sData.cbComments)), nInfo.GetData() + (cbData = cbData + sData.cbProfile), STRINGBYTES(sData.cbComments));
		CopyMemory(m_szEvent.GetBufferSetLength(STRINGCHARS(sData.cbEvent)), nInfo.GetData() + (cbData = cbData + sData.cbComments), STRINGBYTES(sData.cbEvent));
		m_nPrintMode = sData.nPrintMode;
		m_nPrintCount[0] = sData.nPrintCount[0];
		m_nPrintCount[1] = sData.nPrintCount[1];
		m_nPrintByCount = sData.nPrintByCount;
		m_tPrintAtTime = sData.tPrintAtTime;
		m_tPrintAtDailyTime = sData.tPrintAtDailyTime;
		m_tPrintLastTime[0] = sData.tPrintLastTime[0];
		m_tPrintLastTime[1] = sData.tPrintLastTime[1];
		m_tRepeatInterval = sData.tRepeatInterval;
		m_nRepeatStopByCount[0] = sData.nRepeatStopByCount[0];
		m_nRepeatStopByCount[1] = sData.nRepeatStopByCount[1];
		m_tRepeatStopByTime[0] = sData.tRepeatStopByTime[0];
		m_tRepeatStopByTime[1] = sData.tRepeatStopByTime[1];
		m_szName.ReleaseBuffer();
		m_szProfile.ReleaseBuffer();
		m_szComments.ReleaseBuffer();
		m_szEvent.ReleaseBuffer();
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CTPEPPrintJobs

CTPEPPrintJobs::CTPEPPrintJobs() : CPtrArray()
{
	return;
}

CTPEPPrintJobs::~CTPEPPrintJobs()
{
	RemoveAll();
}

INT CTPEPPrintJobs::Add(CTPEPPrintJobInfo *pJobInfo)
{
	return((INT)CPtrArray::Add(pJobInfo));
}

INT CTPEPPrintJobs::Find(LPCTSTR pszName) CONST
{
	INT  nJob;
	INT  nJobs;
	CTPEPPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (INT)GetSize(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = GetAt(nJob)) && pJobInfo->GetName() == pszName) break;
		continue;
	}
	return((nJob < nJobs) ? nJob : -1);
}

CTPEPPrintJobInfo *CTPEPPrintJobs::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTPEPPrintJobInfo *)CPtrArray::GetAt(nIndex) : (CTPEPPrintJobInfo *)NULL);
}

CTPEPPrintJobInfo *CTPEPPrintJobs::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTPEPPrintJobInfo *)CPtrArray::GetAt(nIndex) : (CTPEPPrintJobInfo *)NULL);
}

TIMEKEY CTPEPPrintJobs::Schedule()
{
	INT  nJob;
	INT  nJobs;
	UINT  nJobMode;
	UINT  nJobPrintCount[2];
	TIMEKEY  tJobPrintTimeout[2];
	CTimeKey  tJobPrintTime[4];
	CTimeSpan  tJobPrintInterval;
	CTimeSpan  tJobPrintDailyTime;
	CTPEPPrintJobInfo  *pJobInfo[2];

	for (nJob = 0, nJobs = (INT)GetSize(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo[0] = GetAt(nJob)) != (CTPEPPrintJobInfo *)NULL)
		{
			if (((nJobMode = pJobInfo[0]->GetPrintMode()) & TPEP_PRINT_ACTIVE) && (((nJobMode & TPEP_PRINT_ATTIME) && pJobInfo[0]->GetPrintLastTime(tJobPrintTime[1]) && (tJobPrintTime[1] > 0 || pJobInfo[0]->SetPrintLastTime(tJobPrintTime[3]))) || (nJobMode & TPEP_PRINT_ATDAILYTIME)) &&
				((pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0]) && pJobInfo[0]->GetPrintCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastTime(tJobPrintTime[1]) && tJobPrintTime[3] >= tJobPrintTime[0] && tJobPrintTime[0] > tJobPrintTime[1] && pJobInfo[0]->SetPrintFlags(TPEP_PRINT_ATTIME) && pJobInfo[0]->SetPrintCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0], tJobPrintInterval) && pJobInfo[0]->GetPrintCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastTime(tJobPrintTime[1]) && tJobPrintTime[3] >= tJobPrintTime[0] && (tJobPrintTime[0] > tJobPrintTime[1] || (tJobPrintTime[1].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds() < (tJobPrintTime[3].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds()) && pJobInfo[0]->SetPrintFlags(TPEP_PRINT_ATTIME) && pJobInfo[0]->SetPrintCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0], tJobPrintInterval, nJobPrintCount[1]) && pJobInfo[0]->GetPrintCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastTime(tJobPrintTime[1]) && tJobPrintTime[3] >= tJobPrintTime[0] && (tJobPrintTime[0] > tJobPrintTime[1] || (tJobPrintTime[1].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds() < (tJobPrintTime[3].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds()) && nJobPrintCount[0] < nJobPrintCount[1] && pJobInfo[0]->SetPrintFlags(TPEP_PRINT_ATTIME) && pJobInfo[0]->SetPrintCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0], tJobPrintInterval, tJobPrintTime[2]) && pJobInfo[0]->GetPrintCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastTime(tJobPrintTime[1]) && tJobPrintTime[3] >= tJobPrintTime[0] && (tJobPrintTime[0] > tJobPrintTime[1] || (tJobPrintTime[1].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds() < (tJobPrintTime[3].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds()) && tJobPrintTime[3] <= tJobPrintTime[2] && pJobInfo[0]->SetPrintFlags(TPEP_PRINT_ATTIME) && pJobInfo[0]->SetPrintCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtDailyTime(tJobPrintDailyTime) && pJobInfo[0]->GetPrintDailyCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastDailyTime(tJobPrintTime[1]) && tJobPrintTime[3].GetTime() % SECONDSPERDAY >= tJobPrintDailyTime.GetTotalSeconds() && tJobPrintTime[3].GetTime() / SECONDSPERDAY != tJobPrintTime[1].GetTime() / SECONDSPERDAY  &&  pJobInfo[0]->SetPrintFlags(TPEP_PRINT_ATDAILYTIME) && pJobInfo[0]->SetPrintDailyCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastDailyTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtDailyTime(tJobPrintDailyTime, nJobPrintCount[1]) && pJobInfo[0]->GetPrintDailyCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastDailyTime(tJobPrintTime[1]) && tJobPrintTime[3].GetTime() % SECONDSPERDAY >= tJobPrintDailyTime.GetTotalSeconds() && tJobPrintTime[3].GetTime() / SECONDSPERDAY != tJobPrintTime[1].GetTime() / SECONDSPERDAY  &&  nJobPrintCount[0] < nJobPrintCount[1] && pJobInfo[0]->SetPrintFlags(TPEP_PRINT_ATDAILYTIME) && pJobInfo[0]->SetPrintDailyCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastDailyTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtDailyTime(tJobPrintDailyTime, tJobPrintTime[2]) && pJobInfo[0]->GetPrintDailyCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastDailyTime(tJobPrintTime[1]) && tJobPrintTime[3].GetTime() % SECONDSPERDAY >= tJobPrintDailyTime.GetTotalSeconds() && tJobPrintTime[3].GetTime() / SECONDSPERDAY != tJobPrintTime[1].GetTime() / SECONDSPERDAY  &&  tJobPrintTime[3] <= tJobPrintTime[2] && pJobInfo[0]->SetPrintFlags(TPEP_PRINT_ATDAILYTIME) && pJobInfo[0]->SetPrintDailyCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastDailyTime(tJobPrintTime[3]))))
			{
				if ((pJobInfo[1] = new CTPEPPrintJobInfo))
				{
					pJobInfo[1]->Copy(pJobInfo[0]);
					InsertAt(0, pJobInfo[1], 1);
					if (!pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0], tJobPrintInterval) && !pJobInfo[0]->GetPrintAtDailyTime(tJobPrintDailyTime) &&
						(!pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0]) || tJobPrintTime[3] >= tJobPrintTime[0]) &&
						(!pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0], tJobPrintInterval, nJobPrintCount[1]) || !pJobInfo[0]->GetPrintCount(nJobPrintCount[0]) || nJobPrintCount[0] >= nJobPrintCount[1]) &&
						(!pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0], tJobPrintInterval, tJobPrintTime[2]) || tJobPrintTime[0].GetTime() + ((tJobPrintTime[3].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds() + 1)*tJobPrintInterval.GetTotalSeconds() > tJobPrintTime[2].GetTime()) &&
						(!pJobInfo[0]->GetPrintAtDailyTime(tJobPrintDailyTime, nJobPrintCount[1]) || !pJobInfo[0]->GetPrintDailyCount(nJobPrintCount[0]) || nJobPrintCount[0] >= nJobPrintCount[1]) &&
						(!pJobInfo[0]->GetPrintAtDailyTime(tJobPrintDailyTime, tJobPrintTime[2]) || tJobPrintTime[0].GetTime() + ((tJobPrintTime[3].GetTime() - tJobPrintTime[0].GetTime()) / SECONDSPERDAY + 1)*SECONDSPERDAY > tJobPrintTime[2].GetTime()))
					{
						delete pJobInfo[0];
						RemoveAt(nJob + 1);
					}
					break;
				}
			}
		}
	}
	if (nJob == nJobs)
	{
		for (nJob = 0, tJobPrintTimeout[0] = tJobPrintTimeout[1] = -1; nJob < nJobs; nJob++)
		{
			tJobPrintTimeout[0] = ((pJobInfo[0] = GetAt(nJob))->GetPrintAtTime(tJobPrintTime[0]) && tJobPrintTime[3] < tJobPrintTime[0]) ? tJobPrintTime[0].GetTime() : tJobPrintTimeout[1];
			tJobPrintTimeout[1] = (tJobPrintTimeout[0] > 0 && (tJobPrintTimeout[1] < 0 || tJobPrintTimeout[0] < tJobPrintTimeout[1])) ? tJobPrintTimeout[0] : tJobPrintTimeout[1];
			tJobPrintTimeout[0] = (pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0], tJobPrintInterval)) ? ((tJobPrintTime[3] > tJobPrintTime[0]) ? (tJobPrintTime[0].GetTime() + ((tJobPrintTime[3].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds() + 1)*tJobPrintInterval.GetTotalSeconds()) : tJobPrintTime[0].GetTime()) : tJobPrintTimeout[1];
			tJobPrintTimeout[1] = (tJobPrintTimeout[0] > 0 && (tJobPrintTimeout[1] < 0 || tJobPrintTimeout[0] < tJobPrintTimeout[1])) ? tJobPrintTimeout[0] : tJobPrintTimeout[1];
			tJobPrintTimeout[0] = (pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0], tJobPrintInterval, nJobPrintCount[1]) && pJobInfo[0]->GetPrintCount(nJobPrintCount[0]) && nJobPrintCount[0] < nJobPrintCount[1]) ? ((tJobPrintTime[3] > tJobPrintTime[0]) ? (tJobPrintTime[0].GetTime() + ((tJobPrintTime[3].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds() + 1)*tJobPrintInterval.GetTotalSeconds()) : tJobPrintTime[0].GetTime()) : tJobPrintTimeout[1];
			tJobPrintTimeout[1] = (tJobPrintTimeout[0] > 0 && (tJobPrintTimeout[1] < 0 || tJobPrintTimeout[0] < tJobPrintTimeout[1])) ? tJobPrintTimeout[0] : tJobPrintTimeout[1];
			tJobPrintTimeout[0] = (pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0], tJobPrintInterval, tJobPrintTime[2]) && (tJobPrintTime[3] <= tJobPrintTime[0] || tJobPrintTime[0].GetTime() + ((tJobPrintTime[3].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds() + 1)*tJobPrintInterval.GetTotalSeconds() <= tJobPrintTime[2].GetTime())) ? ((tJobPrintTime[3] > tJobPrintTime[0]) ? (tJobPrintTime[0].GetTime() + ((tJobPrintTime[3].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds() + 1)*tJobPrintInterval.GetTotalSeconds()) : tJobPrintTime[0].GetTime()) : tJobPrintTimeout[1];
			tJobPrintTimeout[1] = (tJobPrintTimeout[0] > 0 && (tJobPrintTimeout[1] < 0 || tJobPrintTimeout[0] < tJobPrintTimeout[1])) ? tJobPrintTimeout[0] : tJobPrintTimeout[1];
			tJobPrintTimeout[0] = (pJobInfo[0]->GetPrintAtDailyTime(tJobPrintDailyTime)) ? ((tJobPrintTime[3].GetTime() % SECONDSPERDAY >= tJobPrintDailyTime.GetTotalSeconds()) ? (SECONDSPERDAY*(tJobPrintTime[3].GetTime() / SECONDSPERDAY + 1) + tJobPrintDailyTime.GetTotalSeconds()) : (SECONDSPERDAY*(tJobPrintTime[3].GetTime() / SECONDSPERDAY) + tJobPrintDailyTime.GetTotalSeconds())) : tJobPrintTimeout[1];
			tJobPrintTimeout[1] = (tJobPrintTimeout[0] > 0 && (tJobPrintTimeout[1] < 0 || tJobPrintTimeout[0] < tJobPrintTimeout[1])) ? tJobPrintTimeout[0] : tJobPrintTimeout[1];
			tJobPrintTimeout[0] = (pJobInfo[0]->GetPrintAtDailyTime(tJobPrintDailyTime, nJobPrintCount[1]) && pJobInfo[0]->GetPrintDailyCount(nJobPrintCount[0]) && nJobPrintCount[0] < nJobPrintCount[1]) ? ((tJobPrintTime[3].GetTime() % SECONDSPERDAY >= tJobPrintDailyTime.GetTotalSeconds()) ? (SECONDSPERDAY*(tJobPrintTime[3].GetTime() / SECONDSPERDAY + 1) + tJobPrintDailyTime.GetTotalSeconds()) : (SECONDSPERDAY*(tJobPrintTime[3].GetTime() / SECONDSPERDAY) + tJobPrintDailyTime.GetTotalSeconds())) : tJobPrintTimeout[1];
			tJobPrintTimeout[1] = (tJobPrintTimeout[0] > 0 && (tJobPrintTimeout[1] < 0 || tJobPrintTimeout[0] < tJobPrintTimeout[1])) ? tJobPrintTimeout[0] : tJobPrintTimeout[1];
			tJobPrintTimeout[0] = (pJobInfo[0]->GetPrintAtDailyTime(tJobPrintDailyTime, tJobPrintTime[2]) && ((tJobPrintTime[3].GetTime() % SECONDSPERDAY < tJobPrintDailyTime.GetTotalSeconds() && SECONDSPERDAY*(tJobPrintTime[3].GetTime() / SECONDSPERDAY) + tJobPrintDailyTime.GetTotalSeconds() <= tJobPrintTime[2].GetTime()) || (tJobPrintTime[3].GetTime() % SECONDSPERDAY >= tJobPrintDailyTime.GetTotalSeconds() && SECONDSPERDAY*(tJobPrintTime[3].GetTime() / SECONDSPERDAY + 1) + tJobPrintDailyTime.GetTotalSeconds() <= tJobPrintTime[2].GetTime()))) ? ((tJobPrintTime[3].GetTime() % SECONDSPERDAY >= tJobPrintDailyTime.GetTotalSeconds()) ? (SECONDSPERDAY*(tJobPrintTime[3].GetTime() / SECONDSPERDAY + 1) + tJobPrintDailyTime.GetTotalSeconds()) : (SECONDSPERDAY*(tJobPrintTime[3].GetTime() / SECONDSPERDAY) + tJobPrintDailyTime.GetTotalSeconds())) : tJobPrintTimeout[1];
			tJobPrintTimeout[1] = (tJobPrintTimeout[0] > 0 && (tJobPrintTimeout[1] < 0 || tJobPrintTimeout[0] < tJobPrintTimeout[1])) ? tJobPrintTimeout[0] : tJobPrintTimeout[1];
		}
		return((tJobPrintTimeout[1] != (TIMEKEY)-1) ? max(tJobPrintTimeout[1] - tJobPrintTime[3].GetTime(), 0) : -1);
	}
	return 0;
}

VOID CTPEPPrintJobs::RemoveAll()
{
	INT  nJob;
	INT  nJobs;

	for (nJob = 0, nJobs = (INT)GetSize(); nJob < nJobs; nJob++)
	{
		delete GetAt(nJob);
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CTPEPPrintJobs::Copy(CONST CTPEPPrintJobs *pPrintJobs)
{
	INT  nJob;
	INT  nJobs;
	CTPEPPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (INT)pPrintJobs->GetSize(), RemoveAll(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = new CTPEPPrintJobInfo) != (CTPEPPrintJobInfo *)NULL)
		{
			pJobInfo->Copy(pPrintJobs->GetAt(nJob));
			InsertAt(nJob, pJobInfo, 1);
			continue;
		}
		break;
	}
	return((nJob == nJobs) ? TRUE : FALSE);
}

BOOL CTPEPPrintJobs::Compare(CONST CTPEPPrintJobs *pPrintJobs) CONST
{
	INT  nJob[2];
	INT  nJobs[2];

	for (nJob[0] = 0, nJobs[0] = (INT)GetSize(), nJobs[1] = (INT)pPrintJobs->GetSize(); nJob[0] < nJobs[0]; nJob[0]++)
	{
		for (nJob[1] = (nJobs[0] != nJobs[1]) ? nJobs[1] : 0; nJob[1] < nJobs[1]; nJob[1]++)
		{
			if (pPrintJobs->GetAt(nJob[0])->Compare(GetAt(nJob[1]))) break;
			continue;
		}
		if (nJob[1] == nJobs[1]) break;
	}
	return((nJob[0] == nJobs[0] && nJobs[0] == nJobs[1]) ? TRUE : FALSE);
}

BOOL CTPEPPrintJobs::Map(CByteArray &nInfo) CONST
{
	INT  nJob;
	INT  nJobs;
	CByteArray  nJobData;
	CTPEPPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (INT)GetSize(), nInfo.RemoveAll(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = GetAt(nJob)) && pJobInfo->Map(nJobData) && nInfo.Append(nJobData) >= 0) continue;
		break;
	}
	return((nJob == nJobs) ? TRUE : FALSE);
}

BOOL CTPEPPrintJobs::Unmap(CONST CByteArray &nInfo)
{
	INT  cbJob;
	INT  cbJobs;
	CByteArray  nJobData;
	CTPEPPrintJobInfo  *pJobInfo;

	for (cbJobs = 0, RemoveAll(); cbJobs < nInfo.GetSize(); cbJobs += cbJob)
	{
		for (CopyMemory(&cbJob, nInfo.GetData() + cbJobs, sizeof(cbJob)), nJobData.SetSize(max(min(cbJob, nInfo.GetSize() - cbJobs), 0)); nJobData.GetSize() >= 0; )
		{
			CopyMemory(nJobData.GetData(), nInfo.GetData() + cbJobs, nJobData.GetSize());
			break;
		}
		if ((pJobInfo = new CTPEPPrintJobInfo))
		{
			if (pJobInfo->Unmap(nJobData) && Add(pJobInfo) >= 0) continue;
			delete pJobInfo;
		}
		break;
	}
	if ((pJobInfo = (!GetSize()) ? new CTPEPPrintJobInfo : (CTPEPPrintJobInfo *)NULL))
	{
		for (pJobInfo->SetName(STRING(IDS_PRINTJOB_DEFAULTNAME)), pJobInfo->SetProfile(STRING(IDS_PRINTPROFILE_DEFAULTNAME)), pJobInfo->SetPrintMode(TPEP_PRINT_ALL); Add(pJobInfo) >= 0; ) return TRUE;
		delete pJobInfo;
		return FALSE;
	}
	return((cbJobs == nInfo.GetSize()) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTPEPAlert

CTPEPAlert::CTPEPAlert() : CObject()
{
	m_nOptions = 0;
	m_nOperator = 0;
	m_fValue[0] = 0.0;
	m_fValue[1] = 0.0;
}

VOID CTPEPAlert::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CTPEPAlert::GetName() CONST
{
	return m_szName;
}

VOID CTPEPAlert::SetParameter(LPCTSTR pszParameter)
{
	m_szParameter = pszParameter;
}

CString CTPEPAlert::GetParameter() CONST
{
	return m_szParameter;
}

VOID CTPEPAlert::SetOperator(UINT nOperator)
{
	m_nOperator = nOperator;
}

UINT CTPEPAlert::GetOperator() CONST
{
	return m_nOperator;
}

VOID CTPEPAlert::SetValue(LPCTSTR pszValue)
{
	m_szValue = pszValue;
}
VOID CTPEPAlert::SetValue(double fValue)
{
	m_fValue[0] = m_fValue[1] = fValue;
}
VOID CTPEPAlert::SetValue(double fLowValue, double fHighValue)
{
	m_fValue[0] = fLowValue;
	m_fValue[1] = fHighValue;
}

CString CTPEPAlert::GetValue() CONST
{
	return m_szValue;
}
BOOL CTPEPAlert::GetValue(double &fValue) CONST
{
	if (m_fValue[0] == m_fValue[1])
	{
		fValue = m_fValue[0];
		return TRUE;
	}
	return FALSE;
}
BOOL CTPEPAlert::GetValue(double &fLowValue, double &fHighValue) CONST
{
	fLowValue = m_fValue[0];
	fHighValue = m_fValue[1];
	return TRUE;
}

VOID CTPEPAlert::SetAudition(LPCTSTR pszAudition)
{
	m_szAudition = pszAudition;
}

CString CTPEPAlert::GetAudition() CONST
{
	return m_szAudition;
}

VOID CTPEPAlert::SetNotification(LPCTSTR pszNotification)
{
	m_szNotification = pszNotification;
}

CString CTPEPAlert::GetNotification() CONST
{
	return m_szNotification;
}

VOID CTPEPAlert::SetText(LPCTSTR pszText)
{
	m_szText = pszText;
}

CString CTPEPAlert::GetText() CONST
{
	return m_szText;
}

VOID CTPEPAlert::SetOptions(UINT nOptions)
{
	m_nOptions = nOptions;
}

UINT CTPEPAlert::GetOptions() CONST
{
	return m_nOptions;
}

VOID CTPEPAlert::Copy(CONST CTPEPAlert *pAlert)
{
	m_szName = pAlert->m_szName;
	m_szText = pAlert->m_szText;
	m_szValue = pAlert->m_szValue;
	m_szAudition = pAlert->m_szAudition;
	m_szParameter = pAlert->m_szParameter;
	m_szNotification = pAlert->m_szNotification;
	m_fValue[0] = pAlert->m_fValue[0];
	m_fValue[1] = pAlert->m_fValue[1];
	m_nOperator = pAlert->m_nOperator;
	m_nOptions = pAlert->m_nOptions;
}

BOOL CTPEPAlert::Compare(CONST CTPEPAlert *pAlert) CONST
{
	return((pAlert->m_szName == m_szName  &&  pAlert->m_szParameter == m_szParameter  &&  pAlert->m_nOperator == m_nOperator  &&  pAlert->m_szValue == m_szValue  &&  pAlert->m_fValue[0] == m_fValue[0] && pAlert->m_fValue[1] == m_fValue[1] && pAlert->m_szAudition == m_szAudition  &&  pAlert->m_szNotification == m_szNotification  &&  pAlert->m_szText == m_szText  &&  pAlert->m_nOptions == m_nOptions) ? TRUE : FALSE);
}

BOOL CTPEPAlert::Map(CByteArray &nInfo) CONST
{
	INT  cbData;
	DATA  sData;

	sData.cbName = (m_szName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbText = (m_szText.GetLength() + 1)*sizeof(TCHAR);
	sData.cbValue = (m_szValue.GetLength() + 1)*sizeof(TCHAR);
	sData.cbAudition = (m_szAudition.GetLength() + 1)*sizeof(TCHAR);
	sData.cbParameter = (m_szParameter.GetLength() + 1)*sizeof(TCHAR);
	sData.cbNotification = (m_szNotification.GetLength() + 1)*sizeof(TCHAR);
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbName + sData.cbParameter + sData.cbValue + sData.cbAudition + sData.cbNotification + sData.cbText)), sData.nOptions = m_nOptions, sData.nOperator = m_nOperator, sData.fValue[0] = m_fValue[0], sData.fValue[1] = m_fValue[1]; nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szName, sData.cbName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbName), (LPCTSTR)m_szParameter, sData.cbParameter);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbParameter), (LPCTSTR)m_szValue, sData.cbValue);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbValue), (LPCTSTR)m_szAudition, sData.cbAudition);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbAudition), (LPCTSTR)m_szNotification, sData.cbNotification);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbNotification), (LPCTSTR)m_szText, sData.cbText);
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPAlert::Unmap(CONST CByteArray &nInfo)
{
	INT  cbData;
	DATA  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbName + sData.cbParameter + sData.cbValue + sData.cbAudition + sData.cbNotification + sData.cbText && sData.cbName > 0 && sData.cbParameter > 0 && sData.cbValue > 0 && sData.cbAudition > 0 && sData.cbNotification > 0 && sData.cbText > 0; )
	{
		CopyMemory(m_szName.GetBufferSetLength(STRINGCHARS(sData.cbName)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbName));
		CopyMemory(m_szParameter.GetBufferSetLength(STRINGCHARS(sData.cbParameter)), nInfo.GetData() + (cbData = cbData + sData.cbName), STRINGBYTES(sData.cbParameter));
		CopyMemory(m_szValue.GetBufferSetLength(STRINGCHARS(sData.cbValue)), nInfo.GetData() + (cbData = cbData + sData.cbParameter), STRINGBYTES(sData.cbValue));
		CopyMemory(m_szAudition.GetBufferSetLength(STRINGCHARS(sData.cbAudition)), nInfo.GetData() + (cbData = cbData + sData.cbValue), STRINGBYTES(sData.cbAudition));
		CopyMemory(m_szNotification.GetBufferSetLength(STRINGCHARS(sData.cbNotification)), nInfo.GetData() + (cbData = cbData + sData.cbAudition), STRINGBYTES(sData.cbNotification));
		CopyMemory(m_szText.GetBufferSetLength(STRINGCHARS(sData.cbText)), nInfo.GetData() + (cbData = cbData + sData.cbNotification), STRINGBYTES(sData.cbText));
		m_nOptions = sData.nOptions;
		m_nOperator = sData.nOperator;
		m_fValue[0] = sData.fValue[0];
		m_fValue[1] = sData.fValue[1];
		m_szName.ReleaseBuffer();
		m_szParameter.ReleaseBuffer();
		m_szValue.ReleaseBuffer();
		m_szAudition.ReleaseBuffer();
		m_szNotification.ReleaseBuffer();
		m_szText.ReleaseBuffer();
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CTPEPAlerts

CTPEPAlerts::CTPEPAlerts() : CPtrArray()
{
	return;
}

CTPEPAlerts::~CTPEPAlerts()
{
	RemoveAll();
}

INT CTPEPAlerts::Add(CTPEPAlert *pAlert)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pAlert->GetName(), TRUE)) >= 0) InsertAt(nIndex, pAlert, 1);
	return nIndex;
}

INT CTPEPAlerts::Find(LPCTSTR pszName) CONST
{
	return FindIndex(pszName);
}

CTPEPAlert *CTPEPAlerts::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTPEPAlert *)CPtrArray::GetAt(nIndex) : (CTPEPAlert *)NULL);
}

CTPEPAlert *CTPEPAlerts::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTPEPAlert *)CPtrArray::GetAt(nIndex) : (CTPEPAlert *)NULL);
}

VOID CTPEPAlerts::RemoveAll()
{
	INT  nAlert;
	INT  nAlerts;

	for (nAlert = 0, nAlerts = (INT)GetSize(); nAlert < nAlerts; nAlert++)
	{
		delete GetAt(nAlert);
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CTPEPAlerts::Copy(CONST CTPEPAlerts *pAlerts)
{
	INT  nAlert;
	INT  nAlerts;
	CTPEPAlert  *pAlert;

	for (nAlert = 0, nAlerts = (INT)pAlerts->GetSize(), RemoveAll(); nAlert < nAlerts; nAlert++)
	{
		if ((pAlert = new CTPEPAlert) != (CTPEPAlert *)NULL)
		{
			pAlert->Copy(pAlerts->GetAt(nAlert));
			InsertAt(nAlert, pAlert, 1);
			continue;
		}
		break;
	}
	return((nAlert == nAlerts) ? TRUE : FALSE);
}

BOOL CTPEPAlerts::Compare(CONST CTPEPAlerts *pAlerts) CONST
{
	INT  nAlert;
	INT  nAlerts;

	for (nAlert = 0, nAlerts = (pAlerts->GetSize() == GetSize()) ? (INT)GetSize() : -1; nAlert < nAlerts; nAlert++)
	{
		if (!pAlerts->GetAt(nAlert)->Compare(GetAt(nAlert))) break;
		continue;
	}
	return((nAlert == nAlerts) ? TRUE : FALSE);
}

BOOL CTPEPAlerts::Map(CByteArray &nInfo) CONST
{
	INT  nAlert;
	INT  nAlerts;
	CByteArray  nAlertData;
	CTPEPAlert  *pAlert;

	for (nAlert = 0, nAlerts = (INT)GetSize(), nInfo.RemoveAll(); nAlert < nAlerts; nAlert++)
	{
		if ((pAlert = GetAt(nAlert)) && pAlert->Map(nAlertData) && nInfo.Append(nAlertData) >= 0) continue;
		break;
	}
	return((nAlert == nAlerts) ? TRUE : FALSE);
}

BOOL CTPEPAlerts::Unmap(CONST CByteArray &nInfo)
{
	INT  cbAlert;
	INT  cbAlerts;
	CByteArray  nAlertData;
	CTPEPAlert  *pAlert;

	for (cbAlerts = 0, RemoveAll(); cbAlerts < nInfo.GetSize(); cbAlerts += cbAlert)
	{
		for (CopyMemory(&cbAlert, nInfo.GetData() + cbAlerts, sizeof(cbAlert)), nAlertData.SetSize(max(min(cbAlert, nInfo.GetSize() - cbAlerts), 0)); nAlertData.GetSize() >= 0; )
		{
			CopyMemory(nAlertData.GetData(), nInfo.GetData() + cbAlerts, nAlertData.GetSize());
			break;
		}
		if ((pAlert = new CTPEPAlert))
		{
			if (pAlert->Unmap(nAlertData) && Add(pAlert) >= 0) continue;
			delete pAlert;
		}
		break;
	}
	return((cbAlerts == nInfo.GetSize()) ? TRUE : FALSE);
}

INT CTPEPAlerts::FindIndex(LPCTSTR pszName, BOOL bInsert) CONST
{
	INT  nIndex[2];
	INT  nMinIndex;
	INT  nMaxIndex;
	CTPEPAlert  *pAlert;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex[0] = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex[0] = (nMinIndex + nMaxIndex) / 2)
	{
		nMinIndex = ((pAlert = GetAt(nIndex[0]))) ? ((nIndex[1] = (pAlert->GetName() <= pszName)) ? (nIndex[0] + 1) : nMinIndex) : (nIndex[0] = -1);
		nMaxIndex = (nIndex[0] < 0 || !nIndex[1]) ? nIndex[0] : nMaxIndex;
	}
	return((((!bInsert && (pAlert = GetAt((nIndex[0] = max(nIndex[0] - 1, 0)))) && pAlert->GetName() == pszName) || (bInsert && (((pAlert = GetAt(max(nIndex[0] - 1, 0))) && pAlert->GetName() != pszName && (pAlert = GetAt((INT)min(nIndex[0], GetUpperBound()))) && pAlert->GetName() != pszName) || !GetSize()))) && lstrlen(pszName) > 0) ? nIndex[0] : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CTPEPSettingsLayoutPage property page

IMPLEMENT_DYNCREATE(CTPEPSettingsLayoutPage, CLocalePropertyPage)

CTPEPSettingsLayoutPage::CTPEPSettingsLayoutPage() : CLocalePropertyPage(CTPEPSettingsLayoutPage::IDD)
{
	//{{AFX_DATA_INIT(CTPEPSettingsLayoutPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTPEPSettingsLayoutPage::Initialize()
{
	CTPEPOpenDialog  *pDialog;

	if (((pDialog = GetParentDialog()->GetParentDialog()) && (pDialog->GetLayoutColumns(m_nColumns[0]) || GetParentDisplay()->GetLayoutColumns(m_nColumns[0])) && (pDialog->GetLayoutTitleFont(&m_fntTitle[0]) || GetParentDisplay()->GetTitleFont(&m_fntTitle[0])) && (pDialog->GetLayoutMessagesFont(&m_fntMessages[0]) || GetParentDisplay()->GetMessagesFont(&m_fntMessages[0]))) || (GetParentDisplay()->GetLayoutColumns(m_nColumns[0]) && GetParentDisplay()->GetTitleFont(&m_fntTitle[0]) && GetParentDisplay()->GetMessagesFont(&m_fntMessages[0])))
	{
		m_bToolTips[0] = m_bToolTips[1] = (!pDialog || !pDialog->GetLayoutToolTipMode(m_bToolTips[0])) ? GetParentDisplay()->IsToolTipModeEnabled() : m_bToolTips[0];
		m_nColumnType = (GetParentDisplay()->GetLayout(m_nColumnType) || !pDialog) ? m_nColumnType : pDialog->GetType();
		CopyMemory(&m_fntMessages[1], &m_fntMessages[0], sizeof(LOGFONT));
		CopyMemory(&m_fntTitle[1], &m_fntTitle[0], sizeof(LOGFONT));
		m_nColumns[1].Copy(m_nColumns[0]);
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPSettingsLayoutPage::GetLayout(CUIntArray &nColumns) CONST
{
	nColumns.Copy(m_nColumns[0]);
	return((nColumns.GetSize() > 0) ? Check(FALSE) : FALSE);
}

BOOL CTPEPSettingsLayoutPage::GetTitleFont(LPLOGFONT pTitleFont) CONST
{
	CopyMemory(pTitleFont, &m_fntTitle[0], sizeof(LOGFONT));
	return Check(FALSE);
}

BOOL CTPEPSettingsLayoutPage::GetMessagesFont(LPLOGFONT pMessagesFont) CONST
{
	CopyMemory(pMessagesFont, &m_fntMessages[0], sizeof(LOGFONT));
	return Check(FALSE);
}

BOOL CTPEPSettingsLayoutPage::GetToolTipMode(BOOL &bEnable) CONST
{
	bEnable = m_bToolTips[0];
	return Check(FALSE);
}

CTPEPSettingsDialog *CTPEPSettingsLayoutPage::GetParentDialog() CONST
{
	return((CTPEPSettingsDialog *)CLocalePropertyPage::GetParent());
}

CTPEPWnd *CTPEPSettingsLayoutPage::GetParentDisplay() CONST
{
	return((CTPEPWnd *)GetParentDialog()->GetParentDisplay());
}

BOOL CTPEPSettingsLayoutPage::EnumLayoutColumns()
{
	INT  nColumn;
	INT  nColumns;
	CStringArray  szColumns;

	switch (m_nColumnType)
	{
	case TPEP_TYPE_NORMAL:
	{ szColumns.Add(LookupColumnName(TPEP_TITLEITEM_ID));
	szColumns.Add(LookupColumnName(TPEP_TITLEITEM_DESCRIPTION));
	szColumns.Add(LookupColumnName(TPEP_TITLEITEM_VALUE));
	szColumns.Add(LookupColumnName(TPEP_TITLEITEM_UNIT));
	szColumns.Add(LookupColumnName(TPEP_TITLEITEM_CHANGETMUNIT));
	szColumns.Add(LookupColumnName(TPEP_TITLEITEM_CHANGETIME));
	szColumns.Add(LookupColumnName(TPEP_TITLEITEM_UPDATETMUNIT));
	szColumns.Add(LookupColumnName(TPEP_TITLEITEM_UPDATETIME));
	break;
	}
	case TPEP_TYPE_SIMPLE:
	{ szColumns.Add(STRING(IDS_TPEP_TITLEITEM_MESSAGES));
	break;
	}
	}
	for (nColumn = 0, nColumns = (INT)szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		SendDlgItemMessage(IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_NAME, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szColumns.GetAt(nColumn));
		continue;
	}
	SendDlgItemMessage(IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_NAME, CB_SETCURSEL);
	return((nColumn == nColumns) ? TRUE : FALSE);
}

BOOL CTPEPSettingsLayoutPage::ShowLayoutColumns()
{
	INT  nColumn;
	INT  nColumns;

	for (nColumn = 0, nColumns = (INT)m_nColumns[0].GetSize(), SendDlgItemMessage(IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_VIEW, LVM_DELETEALLITEMS), m_nColumnIndex = 0; nColumn < nColumns; nColumn++)
	{
		if ((nColumn >= m_szColumns.GetSize() && InsertLayoutColumn(nColumn, LookupColumnName(m_nColumns[0].GetAt(nColumn)))) || (nColumn < m_szColumns.GetSize() && ModifyLayoutColumn(nColumn, LookupColumnName(m_nColumns[0].GetAt(nColumn))))) continue;
		break;
	}
	while (nColumn < m_szColumns.GetSize())
	{
		if (!RemoveLayoutColumn(nColumn)) break;
		continue;
	}
	for (nColumn = (nColumn != nColumns) ? (nColumns + 1) : 0; nColumn < nColumns; nColumn++)
	{
		if ((!nColumn  &&  Listview_InsertText(GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_VIEW), 0, EMPTYSTRING)) || (nColumn > 0 && Listview_SetText(GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_VIEW), 0, nColumn, EMPTYSTRING))) continue;
		break;
	}
	return((nColumn == nColumns) ? SetCurLayoutColumn() : FALSE);
}

VOID CTPEPSettingsLayoutPage::ShowLayoutFontDetails()
{
	INT  nSize;
	INT  nSizes;
	INT  nStyle;
	INT  nStyles;
	BOOL  bUnderlined;
	CStringArray  szSizes;
	CStringArray  szStyles;
	CFontTools  cFontTools;

	for (SendDlgItemMessage(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_RESETCONTENT), SendDlgItemMessage(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_RESETCONTENT), SendDlgItemMessage(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)((IsDlgButtonChecked(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE)) ? m_fntTitle[0].lfFaceName : m_fntMessages[0].lfFaceName))); (IsDlgButtonChecked(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE) && cFontTools.EnumerateFont(m_fntTitle[0].lfFaceName, szStyles, szSizes, bUnderlined)) || (IsDlgButtonChecked(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_MESSAGES) && cFontTools.EnumerateFont(m_fntMessages[0].lfFaceName, szStyles, szSizes, bUnderlined)); )
	{
		for (nStyle = 0, nStyles = (INT)szStyles.GetSize(); nStyle < nStyles; nStyle++) SendDlgItemMessage(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szStyles.GetAt(nStyle));
		for (nSize = 0, nSizes = (INT)szSizes.GetSize(); nSize < nSizes; nSize++) SendDlgItemMessage(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szSizes.GetAt(nSize));
		break;
	}
	if (IsDlgButtonChecked(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		SendDlgItemMessage(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_fntTitle[0])), 0));
		SendDlgItemMessage(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntTitle[0])), max(SendDlgItemMessage(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntTitle[1])), 0)));
	}
	if (IsDlgButtonChecked(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_MESSAGES))
	{
		SendDlgItemMessage(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_fntMessages[0])), 0));
		SendDlgItemMessage(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntMessages[0])), max(SendDlgItemMessage(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntMessages[1])), 0)));
	}
	GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_STYLE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_STYLE)->EnableWindow((SendDlgItemMessage(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_SIZE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_SIZE)->EnableWindow((SendDlgItemMessage(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_SAMPLE)->EnableWindow((SendDlgItemMessage(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->EnableWindow((SendDlgItemMessage(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CTPEPSettingsLayoutPage::ShowLayoutFontSample()
{
	CRect  rSampleText;

	GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->GetWindowRect(rSampleText);
	ScreenToClient(rSampleText);
	InvalidateRect(rSampleText);
	UpdateWindow();
}

BOOL CTPEPSettingsLayoutPage::InsertLayoutColumn(INT nIndex, LPCTSTR pszColumn)
{
	m_szColumns.InsertAt(nIndex, pszColumn);
	m_nColumnIndex = (nIndex <= m_nColumnIndex) ? (INT)min(m_nColumnIndex + 1, m_szColumns.GetSize() - 1) : m_nColumnIndex;
	return Listview_InsertColumn(GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_VIEW), nIndex, m_szColumns.GetAt(nIndex), CalcColumnWidth(pszColumn));
}

BOOL CTPEPSettingsLayoutPage::ModifyLayoutColumn(INT nIndex, LPCTSTR pszColumn)
{
	m_szColumns.SetAt(nIndex, pszColumn);
	return Listview_SetColumn(GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_VIEW), nIndex, m_szColumns.GetAt(nIndex), CalcColumnWidth(pszColumn));
}

BOOL CTPEPSettingsLayoutPage::RemoveLayoutColumn(INT nIndex)
{
	if (Listview_DeleteColumn(GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_VIEW), nIndex))
	{
		m_nColumnIndex = (nIndex >= m_nColumnIndex) ? ((nIndex > m_nColumnIndex) ? m_nColumnIndex : 0) : max(m_nColumnIndex - 1, 0);
		m_szColumns.RemoveAt(nIndex);
		return SetCurLayoutColumn(m_nColumnIndex);
	}
	return FALSE;
}

BOOL CTPEPSettingsLayoutPage::SetCurLayoutColumn(INT nIndex)
{
	if (nIndex < m_nColumns[0].GetSize())
	{
		for (m_szColumns.SetAt(m_nColumnIndex, (m_szColumns.GetAt(m_nColumnIndex).Right(lstrlen(STRING(IDS_TPEPSETTINGS_LAYOUTPAGE_COLUMNMARKER))) == STRING(IDS_TPEPSETTINGS_LAYOUTPAGE_COLUMNMARKER)) ? (m_szColumns.GetAt(m_nColumnIndex).Left(m_szColumns.GetAt(m_nColumnIndex).GetLength() - lstrlen(STRING(IDS_TPEPSETTINGS_LAYOUTPAGE_COLUMNMARKER)))) : m_szColumns.GetAt(m_nColumnIndex)), m_szColumns.SetAt(nIndex, m_szColumns.GetAt(nIndex) + STRING(IDS_TPEPSETTINGS_LAYOUTPAGE_COLUMNMARKER)); TRUE; )
		{
			Listview_SetColumn(GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_VIEW), m_nColumnIndex, m_szColumns.GetAt(m_nColumnIndex), CalcColumnWidth(m_szColumns.GetAt(m_nColumnIndex)));
			Listview_SetColumn(GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_VIEW), nIndex, m_szColumns.GetAt(nIndex), CalcColumnWidth(m_szColumns.GetAt((m_nColumnIndex = nIndex))));
			break;
		}
		GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_INSERTBEFORE)->EnableWindow((m_nColumnIndex > 0) ? CheckLayoutColumn() : FALSE);
		GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_INSERTAFTER)->EnableWindow((m_nColumnIndex >= 0) ? CheckLayoutColumn() : FALSE);
		GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_REMOVE)->EnableWindow((m_nColumnIndex > 0) ? TRUE : FALSE);
		return TRUE;
	}
	return FALSE;
}

INT CTPEPSettingsLayoutPage::GetCurLayoutColumn() CONST
{
	return m_nColumnIndex;
}

BOOL CTPEPSettingsLayoutPage::CheckLayoutColumn() CONST
{
	INT  nColumn;
	INT  nColumns;
	CString  szColumn;

	GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_NAME)->GetWindowText(szColumn);
	for (nColumn = (LookupColumnName(szColumn) != TPEP_TITLEITEM_ID) ? m_nColumnIndex : -1, nColumns = (INT)m_nColumns[0].GetSize(); nColumn >= 0 && nColumn < nColumns; nColumn++)
	{
		if (m_nColumns[0].GetAt(nColumn) == TPEP_TITLEITEM_ID  &&  nColumn != m_nColumnIndex)
		{
			nColumn = nColumns;
			break;
		}
		if (m_nColumns[0].GetAt(nColumn) == LookupColumnName(szColumn)) break;
	}
	for (nColumn = (nColumn == nColumns) ? m_nColumnIndex : nColumn; nColumn >= 0; nColumn--)
	{
		if (m_nColumns[0].GetAt(nColumn) == TPEP_TITLEITEM_ID)
		{
			nColumn = nColumns;
			break;
		}
		if (m_nColumns[0].GetAt(nColumn) == LookupColumnName(szColumn)) break;
	}
	return((nColumn == nColumns || nColumn < 0) ? TRUE : FALSE);
}

CString CTPEPSettingsLayoutPage::LookupColumnName(UINT nColumn) CONST
{
	if (nColumn == TPEP_TITLEITEM_ID) return STRING(IDS_TPEP_TITLEITEM_ID);
	if (nColumn == TPEP_TITLEITEM_DESCRIPTION) return STRING(IDS_TPEP_TITLEITEM_DESCRIPTION);
	if (nColumn == TPEP_TITLEITEM_VALUE) return STRING(IDS_TPEP_TITLEITEM_VALUE);
	if (nColumn == TPEP_TITLEITEM_UNIT) return STRING(IDS_TPEP_TITLEITEM_UNIT);
	if (nColumn == TPEP_TITLEITEM_CHANGETMUNIT) return STRING(IDS_TPEP_TITLEITEM_CHANGETMUNIT);
	if (nColumn == TPEP_TITLEITEM_CHANGETIME) return STRING(IDS_TPEP_TITLEITEM_CHANGETIME);
	if (nColumn == TPEP_TITLEITEM_UPDATETMUNIT) return STRING(IDS_TPEP_TITLEITEM_UPDATETMUNIT);
	if (nColumn == TPEP_TITLEITEM_UPDATETIME) return STRING(IDS_TPEP_TITLEITEM_UPDATETIME);
	if (nColumn == TPEP_TITLEITEM_MESSAGES) return STRING(IDS_TPEP_TITLEITEM_MESSAGES);
	return EMPTYSTRING;
}
UINT CTPEPSettingsLayoutPage::LookupColumnName(LPCTSTR pszColumn) CONST
{
	if (!_tcsncmp(pszColumn, STRING(IDS_TPEP_TITLEITEM_ID), lstrlen(STRING(IDS_TPEP_TITLEITEM_ID)))) return TPEP_TITLEITEM_ID;
	if (!_tcsncmp(pszColumn, STRING(IDS_TPEP_TITLEITEM_DESCRIPTION), lstrlen(STRING(IDS_TPEP_TITLEITEM_DESCRIPTION)))) return TPEP_TITLEITEM_DESCRIPTION;
	if (!_tcsncmp(pszColumn, STRING(IDS_TPEP_TITLEITEM_VALUE), lstrlen(STRING(IDS_TPEP_TITLEITEM_VALUE)))) return TPEP_TITLEITEM_VALUE;
	if (!_tcsncmp(pszColumn, STRING(IDS_TPEP_TITLEITEM_UNIT), lstrlen(STRING(IDS_TPEP_TITLEITEM_UNIT)))) return TPEP_TITLEITEM_UNIT;
	if (!_tcsncmp(pszColumn, STRING(IDS_TPEP_TITLEITEM_CHANGETMUNIT), lstrlen(STRING(IDS_TPEP_TITLEITEM_CHANGETMUNIT)))) return TPEP_TITLEITEM_CHANGETMUNIT;
	if (!_tcsncmp(pszColumn, STRING(IDS_TPEP_TITLEITEM_CHANGETIME), lstrlen(STRING(IDS_TPEP_TITLEITEM_CHANGETIME)))) return TPEP_TITLEITEM_CHANGETIME;
	if (!_tcsncmp(pszColumn, STRING(IDS_TPEP_TITLEITEM_UPDATETMUNIT), lstrlen(STRING(IDS_TPEP_TITLEITEM_UPDATETMUNIT)))) return TPEP_TITLEITEM_UPDATETMUNIT;
	if (!_tcsncmp(pszColumn, STRING(IDS_TPEP_TITLEITEM_UPDATETIME), lstrlen(STRING(IDS_TPEP_TITLEITEM_UPDATETIME)))) return TPEP_TITLEITEM_UPDATETIME;
	if (!_tcsncmp(pszColumn, STRING(IDS_TPEP_TITLEITEM_MESSAGES), lstrlen(STRING(IDS_TPEP_TITLEITEM_MESSAGES)))) return TPEP_TITLEITEM_MESSAGES;
	return 0;
}

INT CTPEPSettingsLayoutPage::CalcColumnsWidth(CONST CUIntArray &nColumns, CUIntArray &nWidths)
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = 0, nCount = (INT)nColumns.GetSize(), nWidths.RemoveAll(); nIndex < nCount; nIndex++)
	{
		nWidths.Add((nIndex > 0) ? (nWidths.GetAt(nIndex - 1) + CalcColumnWidth(LookupColumnName(nColumns.GetAt(nIndex)))) : CalcColumnWidth(LookupColumnName(nColumns.GetAt(nIndex))));
		continue;
	}
	return((nCount == nWidths.GetSize()) ? (INT)nWidths.GetSize() : 0);
}

INT CTPEPSettingsLayoutPage::CalcColumnWidth(LPCTSTR pszColumn)
{
	CDC  *pDC;
	INT  nWidth;
	UINT  nColumn;
	CFont  *pOldFont;
	TEXTMETRIC  tmFont;

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(GetFont())))
		{
			if (pDC->GetTextMetrics(&tmFont) && tmFont.tmAveCharWidth > 0)
			{
				nWidth = ((nColumn = LookupColumnName(pszColumn)) == TPEP_TITLEITEM_ID) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTPEPIDColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : 0;
				nWidth = (nColumn == TPEP_TITLEITEM_DESCRIPTION) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTPEPDescriptionColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TPEP_TITLEITEM_VALUE) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTPEPValueColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TPEP_TITLEITEM_UNIT) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTPEPUnitColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TPEP_TITLEITEM_CHANGETMUNIT) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTPEPChangeTMUnitColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TPEP_TITLEITEM_UPDATETMUNIT) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTPEPUpdateTMUnitColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TPEP_TITLEITEM_CHANGETIME) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTPEPChangeTimeColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == TPEP_TITLEITEM_UPDATETIME) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetTPEPUpdateTimeColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (!nWidth) ? (2 * CalcColumnIndent() + pDC->GetTextExtent(pszColumn).cx) : nWidth;
				pDC->SelectObject(pOldFont);
				ReleaseDC(pDC);
				return nWidth;
			}
			pDC->SelectObject(pOldFont);
		}
		ReleaseDC(pDC);
	}
	return 0;
}

INT CTPEPSettingsLayoutPage::CalcColumnIndent() CONST
{
	return 3 * GetSystemMetrics(SM_CXEDGE);
}

BOOL CTPEPSettingsLayoutPage::IsModified(BOOL bAll) CONST
{
	INT  nColumn;
	INT  nColumns;
	CFontTools  cFontTools;

	if (IsWindow(GetSafeHwnd()) && !bAll)
	{
		for (nColumn = 0, nColumns = (m_nColumns[0].GetSize() == m_nColumns[1].GetSize() && !lstrcmp(m_fntTitle[0].lfFaceName, m_fntTitle[1].lfFaceName) && (m_fntTitle[0].lfHeight == m_fntTitle[1].lfHeight || cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntTitle[0])) == cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntTitle[1]))) && m_fntTitle[0].lfWeight == m_fntTitle[1].lfWeight && m_fntTitle[0].lfItalic == m_fntTitle[1].lfItalic && !lstrcmp(m_fntMessages[0].lfFaceName, m_fntMessages[1].lfFaceName) && (m_fntMessages[0].lfHeight == m_fntMessages[1].lfHeight || cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntMessages[0])) == cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntMessages[1]))) && m_fntMessages[0].lfWeight == m_fntMessages[1].lfWeight && m_fntMessages[0].lfItalic == m_fntMessages[1].lfItalic && m_bToolTips[0] == m_bToolTips[1]) ? (INT)m_nColumns[0].GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			if (m_nColumns[0].GetAt(nColumn) != m_nColumns[1].GetAt(nColumn)) break;
			continue;
		}
		return((nColumn != nColumns) ? TRUE : FALSE);
	}
	return((bAll) ? CLocalePropertyPage::IsModified() : FALSE);
}

BOOL CTPEPSettingsLayoutPage::Check(BOOL bAll) CONST
{
	INT  nColumn[2];
	INT  nColumns[2];

	if (IsWindow(GetSafeHwnd()) && !bAll)
	{
		for (nColumn[0] = 0, nColumns[0] = (GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_NAMES)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowTextLength() > 0) ? (INT)m_nColumns[0].GetSize() : -1; nColumn[0] < nColumns[0]; nColumn[0]++)
		{
			for (nColumn[1] = nColumn[0] + 1, nColumns[1] = nColumns[0]; nColumn[1] < nColumns[1]; nColumn[1]++)
			{
				if (m_nColumns[0].GetAt(nColumn[1]) == TPEP_TITLEITEM_ID)
				{
					nColumn[1] = nColumns[1];
					break;
				}
				if (m_nColumns[0].GetAt(nColumn[0]) == m_nColumns[0].GetAt(nColumn[1])) break;
			}
			if (nColumn[1] != nColumns[1]) break;
		}
		return((nColumn[0] == nColumns[0]) ? TRUE : FALSE);
	}
	return((bAll) ? CLocalePropertyPage::Check() : TRUE);
}

void CTPEPSettingsLayoutPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTPEPSettingsLayoutPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTPEPSettingsLayoutPage::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_nColumns[0].RemoveAll();
	m_nColumns[1].RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTPEPSettingsLayoutPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CTPEPSettingsLayoutPage)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_INSERTBEFORE, OnInsertColumnBefore)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_INSERTAFTER, OnInsertColumnAfter)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_REMOVE, OnRemoveColumn)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_TOOLTIPS, OnToolTips)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE, OnTitleFont)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_MESSAGES, OnMessagesFont)
	ON_CBN_EDITCHANGE(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_NAMES, OnEditchangeFontName)
	ON_CBN_SELCHANGE(IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_NAME, OnSelchangeColumnName)
	ON_CBN_SELCHANGE(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_NAMES, OnSelchangeFontName)
	ON_CBN_SELCHANGE(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_STYLE, OnSelchangeFontStyle)
	ON_CBN_SELCHANGE(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_SIZE, OnSelchangeFontSize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTPEPSettingsLayoutPage message handlers

BOOL CTPEPSettingsLayoutPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	CheckDlgButton(IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_TOOLTIPS, m_bToolTips[0]);
	CheckRadioButton(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE, IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_MESSAGES, IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE);
	GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->GetWindowText(m_szFontSampleText);
	GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT)->EnableWindow();
	GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_NAME)->EnableWindow();
	GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_VIEW)->EnableWindow();
	GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_SHOWDATA)->EnableWindow();
	GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_TOOLTIPS)->EnableWindow();
	GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS)->EnableWindow();
	GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_STATIC)->EnableWindow();
	GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE)->EnableWindow();
	GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_MESSAGES)->EnableWindow();
	GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_CHARACTERISTICS)->EnableWindow();
	GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_NAMES_STATIC)->EnableWindow();
	GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_NAMES)->EnableWindow();
	SendDlgItemMessage(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_NAMES, FCB_DIR, CF_EFFECTS | CF_SCREENFONTS);
	SendDlgItemMessage(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)m_fntTitle[0].lfFaceName));
	EnumLayoutColumns();
	ShowLayoutColumns();
	ShowLayoutFontDetails();
	return TRUE;
}

void CTPEPSettingsLayoutPage::OnPaint()
{
	INT  nBkMode;
	CFont  cFont;
	CFont  *pOldFont;
	CRect  rSampleText;
	COLORREF  nOldColor;
	CPaintDC  cDC(this);

	for (GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->GetWindowRect(rSampleText), ScreenToClient(rSampleText); cFont.CreateFontIndirect((IsDlgButtonChecked(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE)) ? &m_fntTitle[0] : &m_fntMessages[0]); )
	{
		if ((pOldFont = cDC.SelectObject(&cFont)))
		{
			nBkMode = cDC.SetBkMode(TRANSPARENT);
			nOldColor = cDC.SetTextColor((SendDlgItemMessage(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? GetSysColor(COLOR_WINDOWTEXT) : GetSysColor(COLOR_GRAYTEXT));
			cDC.DrawText(m_szFontSampleText, rSampleText, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			cDC.SetTextColor(nOldColor);
			cDC.SelectObject(pOldFont);
			cDC.SetBkMode(nBkMode);
			ValidateRect(rSampleText);
		}
		cFont.DeleteObject();
		break;
	}
}

BOOL CTPEPSettingsLayoutPage::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMLISTVIEW  *pNotifyInfo = (NMLISTVIEW *)lParam;

	if (pNotifyInfo->hdr.idFrom == IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_VIEW)
	{
		if (pNotifyInfo->hdr.code == LVN_COLUMNCLICK) SetCurLayoutColumn(pNotifyInfo->iSubItem);
		if (pNotifyInfo->hdr.code == LVN_ITEMCHANGING  &&  !(pNotifyInfo->uChanged & LVIF_TEXT))
		{
			*pResult = TRUE;
			return TRUE;
		}
	}
	return CLocalePropertyPage::OnNotify(wParam, lParam, pResult);
}

void CTPEPSettingsLayoutPage::OnInsertColumnBefore()
{
	INT  nIndex;
	CString  szColumn;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_NAME)->GetWindowText(szColumn); InsertLayoutColumn((nIndex = m_nColumnIndex), szColumn); )
	{
		m_nColumns[0].InsertAt(nIndex, LookupColumnName(szColumn));
		SetCurLayoutColumn(nIndex);
		break;
	}
	GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsLayoutPage::OnInsertColumnAfter()
{
	INT  nIndex;
	CString  szColumn;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_NAME)->GetWindowText(szColumn); InsertLayoutColumn((nIndex = m_nColumnIndex + 1), szColumn); )
	{
		m_nColumns[0].InsertAt(nIndex, LookupColumnName(szColumn));
		SetCurLayoutColumn(nIndex);
		break;
	}
	GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsLayoutPage::OnRemoveColumn()
{
	INT  nIndex;
	CHourglassCursor  cCursor;

	if (RemoveLayoutColumn((nIndex = m_nColumnIndex)))
	{
		m_nColumns[0].RemoveAt(nIndex);
		SetCurLayoutColumn();
	}
	GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsLayoutPage::OnToolTips()
{
	m_bToolTips[0] = IsDlgButtonChecked(IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_TOOLTIPS);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsLayoutPage::OnTitleFont()
{
	ShowLayoutFontDetails();
	ShowLayoutFontSample();
}

void CTPEPSettingsLayoutPage::OnMessagesFont()
{
	ShowLayoutFontDetails();
	ShowLayoutFontSample();
}

void CTPEPSettingsLayoutPage::OnEditchangeFontName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsLayoutPage::OnSelchangeColumnName()
{
	GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_INSERTBEFORE)->EnableWindow((m_nColumnIndex > 0) ? CheckLayoutColumn() : FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_INSERTAFTER)->EnableWindow((m_nColumnIndex >= 0) ? CheckLayoutColumn() : FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FORMAT_REMOVE)->EnableWindow((m_nColumnIndex > 0) ? TRUE : FALSE);
}

void CTPEPSettingsLayoutPage::OnSelchangeFontName()
{
	CString  szSize;
	CString  szStyle;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		_tcscpy_s(m_fntTitle[0].lfFaceName, sizeof(m_fntTitle[0].lfFaceName) / sizeof(TCHAR), Combobox_GetText(GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_NAMES), (INT)SendDlgItemMessage(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_GETCURSEL)));
		ShowLayoutFontDetails();
	}
	if (IsDlgButtonChecked(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_MESSAGES))
	{
		_tcscpy_s(m_fntMessages[0].lfFaceName, sizeof(m_fntMessages[0].lfFaceName) / sizeof(TCHAR), Combobox_GetText(GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_NAMES), (INT)SendDlgItemMessage(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_GETCURSEL)));
		ShowLayoutFontDetails();
	}
	if (IsDlgButtonChecked(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntTitle[0].lfWeight, m_fntTitle[0].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_fntTitle[0].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_fntTitle[0]);
	}
	if (IsDlgButtonChecked(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_MESSAGES))
	{
		GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntMessages[0].lfWeight, m_fntMessages[0].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_fntMessages[0].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_fntMessages[0]);
	}
	ShowLayoutFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsLayoutPage::OnSelchangeFontStyle()
{
	CString  szStyle;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntTitle[0].lfWeight, m_fntTitle[0].lfItalic);
	}
	if (IsDlgButtonChecked(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_MESSAGES))
	{
		GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntMessages[0].lfWeight, m_fntMessages[0].lfItalic);
	}
	ShowLayoutFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsLayoutPage::OnSelchangeFontSize()
{
	CString  szSize;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_fntTitle[0].lfHeight);
	}
	if (IsDlgButtonChecked(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_LOCATION_MESSAGES))
	{
		GetDlgItem(IDC_TPEPSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_fntMessages[0].lfHeight);
	}
	ShowLayoutFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CTPEPSettingsFilteringPage property page

IMPLEMENT_DYNCREATE(CTPEPSettingsFilteringPage, CLocalePropertyPage)

CTPEPSettingsFilteringPage::CTPEPSettingsFilteringPage() : CLocalePropertyPage(CTPEPSettingsFilteringPage::IDD)
{
	//{{AFX_DATA_INIT(CTPEPSettingsFilteringPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTPEPSettingsFilteringPage::Initialize()
{
	CTPEPOpenDialog  *pDialog;

	if (((pDialog = GetParentDialog()->GetParentDialog()) && (pDialog->GetFilterMode(m_nMode[0]) || GetParentDisplay()->GetFilterMode(m_nMode[0])) && (pDialog->GetFilterLimit(m_nLimit[0]) >= 0 || GetParentDisplay()->GetFilterLimit(m_nLimit[0]) >= 0) && (pDialog->GetFilterStatus(m_nStatus[0]) >= 0 || GetParentDisplay()->GetFilterStatus(m_nStatus[0]) >= 0) && (pDialog->GetFilterRange(m_tRange[0][0][0], m_tRange[0][0][1]) >= 0 || GetParentDisplay()->GetFilterRange(m_tRange[0][0][0], m_tRange[0][0][1]) >= 0) && (pDialog->GetFilterDailyRange(m_tDailyRange[0][0], m_tDailyRange[0][1]) >= 0 || GetParentDisplay()->GetFilterDailyRange(m_tDailyRange[0][0], m_tDailyRange[0][1]) >= 0) && (pDialog->GetFilterPeriodicalRange(m_tRange[0][1][0], m_tPeriodical[0], m_tRange[0][1][1]) >= 0 || GetParentDisplay()->GetFilterPeriodicalRange(m_tRange[0][1][0], m_tPeriodical[0], m_tRange[0][1][1]) >= 0) && (pDialog->GetFilterDigits(m_nDigits[0]) || GetParentDisplay()->GetFilterDigits(m_nDigits[0])) && (pDialog->GetFilterColors(m_nColor[0], m_nOOLColors[0]) || GetParentDisplay()->GetFilterColors(m_nColor[0], m_nOOLColors[0]))) || (GetParentDisplay()->GetFilterMode(m_nMode[0]) && GetParentDisplay()->GetFilterLimit(m_nLimit[0]) >= 0 && GetParentDisplay()->GetFilterStatus(m_nStatus[0]) >= 0 && GetParentDisplay()->GetFilterRange(m_tRange[0][0][0], m_tRange[0][0][1]) >= 0 && GetParentDisplay()->GetFilterDailyRange(m_tDailyRange[0][0], m_tDailyRange[0][1]) >= 0 && GetParentDisplay()->GetFilterPeriodicalRange(m_tRange[0][1][0], m_tPeriodical[0], m_tRange[0][1][1]) >= 0 && GetParentDisplay()->GetFilterDigits(m_nDigits[0]) && GetParentDisplay()->GetFilterColors(m_nColor[0], m_nOOLColors[0])))
	{
		m_nType = (GetParentDisplay()->GetLayout(m_nType) || !pDialog) ? m_nType : pDialog->GetType();
		m_nLimit[0] = m_nLimit[1] = (m_nMode[0] & TPEP_FILTER_LIMIT) ? m_nLimit[0] : 0;
		m_nStatus[0] = m_nStatus[1] = (m_nMode[0] & TPEP_FILTER_STATUS) ? m_nStatus[0] : 0;
		m_tRange[1][0][0] = m_tRange[0][0][0] = (m_nMode[0] & TPEP_FILTER_RANGE) ? m_tRange[0][0][0] : 0;
		m_tRange[1][0][1] = m_tRange[0][0][1] = (m_nMode[0] & TPEP_FILTER_RANGE) ? m_tRange[0][0][1] : 0;
		m_tRange[0][1][0] = m_tRange[1][1][0] = (m_nMode[0] & TPEP_FILTER_PERIODICALRANGE) ? m_tRange[0][1][0] : 0;
		m_tRange[0][1][1] = m_tRange[1][1][1] = (m_nMode[0] & TPEP_FILTER_PERIODICALRANGE) ? m_tRange[0][1][1] : 0;
		m_tPeriodical[0] = m_tPeriodical[1] = (m_nMode[0] & TPEP_FILTER_PERIODICALRANGE) ? m_tPeriodical[0] : 0;
		m_tDailyRange[0][0] = m_tDailyRange[1][0] = (m_nMode[0] & TPEP_FILTER_DAILYRANGE) ? m_tDailyRange[0][0] : 0;
		m_tDailyRange[0][1] = m_tDailyRange[1][1] = (m_nMode[0] & TPEP_FILTER_DAILYRANGE) ? m_tDailyRange[0][1] : 0;
		m_nOOLColors[1].Copy(m_nOOLColors[0]);
		m_nDigits[1] = m_nDigits[0];
		m_nColor[1] = m_nColor[0];
		m_nMode[1] = m_nMode[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPSettingsFilteringPage::GetMode(UINT &nMode) CONST
{
	nMode = m_nMode[0];
	return Check(FALSE);
}

BOOL CTPEPSettingsFilteringPage::GetLimit(UINT &nLimit) CONST
{
	if (m_nMode[0] & TPEP_FILTER_LIMIT)
	{
		nLimit = m_nLimit[0];
		return Check(FALSE);
	}
	return FALSE;
}

BOOL CTPEPSettingsFilteringPage::GetDigits(UINT &nDigits) CONST
{
	nDigits = m_nDigits[0];
	return Check(FALSE);
}

BOOL CTPEPSettingsFilteringPage::GetStatus(UINT &nStatus) CONST
{
	if (m_nMode[0] & TPEP_FILTER_STATUS)
	{
		nStatus = m_nStatus[0];
		return Check(FALSE);
	}
	return FALSE;
}

BOOL CTPEPSettingsFilteringPage::GetRange(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	if (m_nMode[0] & TPEP_FILTER_RANGE)
	{
		tStartTime = m_tRange[0][0][0];
		tStopTime = m_tRange[0][0][1];
		return Check(FALSE);
	}
	return FALSE;
}

BOOL CTPEPSettingsFilteringPage::GetDailyRange(CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST
{
	if (m_nMode[0] & TPEP_FILTER_DAILYRANGE)
	{
		tStartTime = m_tDailyRange[0][0];
		tStopTime = m_tDailyRange[0][1];
		return Check(FALSE);
	}
	return FALSE;
}

BOOL CTPEPSettingsFilteringPage::GetPeriodicalRange(CTimeKey &tStartTime, CTimeSpan &tInterval, CTimeKey &tStopTime) CONST
{
	if (m_nMode[0] & TPEP_FILTER_PERIODICALRANGE)
	{
		tStartTime = m_tRange[0][1][0];
		tStopTime = m_tRange[0][1][1];
		tInterval = m_tPeriodical[0];
		return Check(FALSE);
	}
	return FALSE;
}

BOOL CTPEPSettingsFilteringPage::GetColors(COLORREF &nColor, CUIntArray &nOOLColors) CONST
{
	nColor = m_nColor[0];
	nOOLColors.Copy(m_nOOLColors[0]);
	return Check(FALSE);
}

CTPEPSettingsDialog *CTPEPSettingsFilteringPage::GetParentDialog() CONST
{
	return((CTPEPSettingsDialog *)CLocalePropertyPage::GetParent());
}

CTPEPWnd *CTPEPSettingsFilteringPage::GetParentDisplay() CONST
{
	return((CTPEPWnd *)GetParentDialog()->GetParentDisplay());
}

BOOL CTPEPSettingsFilteringPage::EnumFilterStatus()
{
	return((SendDlgItemMessage(IDC_TPEPSETTINGS_FILTERINGPAGE_COLORS_STATUS, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TPEPSETTINGS_FILTERINGPAGE_NOOOL)) >= 0 && SendDlgItemMessage(IDC_TPEPSETTINGS_FILTERINGPAGE_COLORS_STATUS, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TPEPSETTINGS_FILTERINGPAGE_SOFTOOL)) >= 0 && SendDlgItemMessage(IDC_TPEPSETTINGS_FILTERINGPAGE_COLORS_STATUS, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TPEPSETTINGS_FILTERINGPAGE_HARDOOL)) >= 0 && SendDlgItemMessage(IDC_TPEPSETTINGS_FILTERINGPAGE_COLORS_STATUS, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TPEPSETTINGS_FILTERINGPAGE_DELTAOOL)) >= 0 && SendDlgItemMessage(IDC_TPEPSETTINGS_FILTERINGPAGE_COLORS_STATUS, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TPEPSETTINGS_FILTERINGPAGE_CONSISTENCYOOL)) >= 0) ? TRUE : FALSE);
}

UINT CTPEPSettingsFilteringPage::GetFilterStatus() CONST
{
	UINT  nStatus;

	nStatus = (IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_NOOOL)) ? TMPARAMETER_STATUS_NOLIMIT : 0;
	nStatus |= (IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_SOFTOOL)) ? TMPARAMETER_STATUS_SOFTLIMIT : 0;
	nStatus |= (IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_HARDOOL)) ? TMPARAMETER_STATUS_HARDLIMIT : 0;
	nStatus |= (IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_DELTAOOL)) ? TMPARAMETER_STATUS_DELTALIMIT : 0;
	nStatus |= (IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_CONSISTENCYOOL)) ? TMPARAMETER_STATUS_CONSISTENCYLIMIT : 0;
	nStatus |= (IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_VALID)) ? TMPARAMETER_STATUS_VALID : 0;
	nStatus |= (IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_INVALID)) ? TMPARAMETER_STATUS_INVALID : 0;
	nStatus |= (IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_GOOD)) ? TMPARAMETER_STATUS_GOOD : 0;
	nStatus |= (IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_BAD)) ? TMPARAMETER_STATUS_BAD : 0;
	return nStatus;
}

VOID CTPEPSettingsFilteringPage::ShowFilterInfo()
{
	CTimeKey  tTimeKey;

	CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL, (m_nMode[0] & TPEP_FILTER_RANGE) ? TRUE : FALSE);
	CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DAILY, (m_nMode[0] & TPEP_FILTER_DAILYRANGE) ? TRUE : FALSE);
	CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL, (m_nMode[0] & TPEP_FILTER_PERIODICALRANGE) ? TRUE : FALSE);
	CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_START, (IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL) && m_tRange[0][1][0].GetTime() > 0) ? TRUE : FALSE);
	CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOP, (IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL) && m_tRange[0][1][1].GetTime() > 0) ? TRUE : FALSE);
	CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_LIMITMESSAGES, ((m_nMode[0] & TPEP_FILTER_LIMIT) && m_nLimit[0] > 0) ? TRUE : FALSE);
	CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DIGITS, (m_nType == TPEP_TYPE_NORMAL  &&  m_nDigits[0] > 0) ? TRUE : FALSE);
	CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS, (m_nType == TPEP_TYPE_NORMAL  &&  m_nStatus[0] != 0) ? TRUE : FALSE);
	CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_NOOOL, (m_nType == TPEP_TYPE_NORMAL && (m_nStatus[0] & TMPARAMETER_STATUS_NOLIMIT)) ? TRUE : FALSE);
	CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_SOFTOOL, (m_nType == TPEP_TYPE_NORMAL && (m_nStatus[0] & TMPARAMETER_STATUS_SOFTLIMIT)) ? TRUE : FALSE);
	CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_HARDOOL, (m_nType == TPEP_TYPE_NORMAL && (m_nStatus[0] & TMPARAMETER_STATUS_HARDLIMIT)) ? TRUE : FALSE);
	CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_DELTAOOL, (m_nType == TPEP_TYPE_NORMAL && (m_nStatus[0] & TMPARAMETER_STATUS_DELTALIMIT)) ? TRUE : FALSE);
	CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_CONSISTENCYOOL, (m_nType == TPEP_TYPE_NORMAL && (m_nStatus[0] & TMPARAMETER_STATUS_CONSISTENCYLIMIT)) ? TRUE : FALSE);
	CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_VALID, (m_nType == TPEP_TYPE_NORMAL && (m_nStatus[0] & TMPARAMETER_STATUS_VALID)) ? TRUE : FALSE);
	CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_INVALID, (m_nType == TPEP_TYPE_NORMAL && (m_nStatus[0] & TMPARAMETER_STATUS_INVALID)) ? TRUE : FALSE);
	CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY, (m_nType == TPEP_TYPE_NORMAL && (m_nStatus[0] & (TMPARAMETER_STATUS_GOOD | TMPARAMETER_STATUS_BAD))) ? TRUE : FALSE);
	CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_GOOD, (m_nType == TPEP_TYPE_NORMAL && (m_nStatus[0] & TMPARAMETER_STATUS_GOOD)) ? TRUE : FALSE);
	CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_BAD, (m_nType == TPEP_TYPE_NORMAL && (m_nStatus[0] & TMPARAMETER_STATUS_BAD)) ? TRUE : FALSE);
	Timespinbox_SetTime(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STARTTIME), (m_tRange[0][0][0].GetTime() > 0) ? m_tRange[0][0][0] : tTimeKey);
	Timespinbox_SetTime(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STOPTIME), (m_tRange[0][0][1].GetTime() > 0) ? m_tRange[0][0][1] : tTimeKey);
	Timespinbox_SetTime(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STARTTIME), (m_tDailyRange[0][0].GetTotalSeconds() > 0) ? (SECONDSPERDAY*(tTimeKey.GetTime() / SECONDSPERDAY) + m_tDailyRange[0][0].GetTotalSeconds()) : tTimeKey);
	Timespinbox_SetTime(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STOPTIME), (m_tDailyRange[0][1].GetTotalSeconds() > 0) ? (SECONDSPERDAY*(tTimeKey.GetTime() / SECONDSPERDAY) + m_tDailyRange[0][1].GetTotalSeconds()) : tTimeKey);
	Timespinbox_SetTime(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STARTTIME), (m_tRange[0][1][0].GetTime() > 0) ? m_tRange[0][1][0] : tTimeKey);
	Timespinbox_SetTime(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOPTIME), (m_tRange[0][1][1].GetTime() > 0) ? m_tRange[0][1][1] : tTimeKey);
	Spinbox_SetRange(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_INTERVAL), TPEPSETTINGSFILTERINGPAGE_MINIMUMINTERVAL, TPEPSETTINGSFILTERINGPAGE_MAXIMUMINTERVAL);
	Spinbox_SetRange(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_LIMITMESSAGES_NUMBER), TPEPSETTINGSFILTERINGPAGE_MINIMUMMESSAGES, TPEPSETTINGSFILTERINGPAGE_MAXIMUMMESSAGES);
	Spinbox_SetRange(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DIGITS_NUMBER), TPEPSETTINGSFILTERINGPAGE_MINIMUMDIGITS, TPEPSETTINGSFILTERINGPAGE_MAXIMUMDIGITS);
	Spinbox_SetPos(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_INTERVAL), m_tPeriodical[0].GetTotalMinutes());
	Spinbox_SetPos(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_LIMITMESSAGES_NUMBER), m_nLimit[0]);
	Spinbox_SetPos(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DIGITS_NUMBER), m_nDigits[0]);
	SendDlgItemMessage(IDC_TPEPSETTINGS_FILTERINGPAGE_COLORS_MESSAGES, CCB_SELECTCOLOR, (WPARAM)-1, (m_nColor[0] != 0) ? m_nColor[0] : (LPARAM)VGA_COLOR_BLACK);
	SendDlgItemMessage(IDC_TPEPSETTINGS_FILTERINGPAGE_COLORS_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (m_nType == TPEP_TYPE_NORMAL) ? ((m_nOOLColors[0].GetSize() > 0) ? (LPARAM)m_nOOLColors[0].GetAt(0) : (LPARAM)VGA_COLOR_BLACK) : 0);
	SendDlgItemMessage(IDC_TPEPSETTINGS_FILTERINGPAGE_COLORS_STATUS, CB_SETCURSEL, (m_nType == TPEP_TYPE_NORMAL) ? 0 : -1);
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATIC)->EnableWindow();
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL)->EnableWindow();
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STARTTIME)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DAILY)->EnableWindow();
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STARTTIME)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DAILY));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DAILY));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DAILY));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL)->EnableWindow();
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_INTERVAL)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_INTERVAL_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_START)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STARTTIME)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL) && IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_START));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOP)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL) && IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOP));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_LIMITMESSAGES)->EnableWindow();
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_LIMITMESSAGES_NUMBER)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_LIMITMESSAGES));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_LIMITMESSAGES_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_LIMITMESSAGES));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DIGITS)->EnableWindow((m_nType == TPEP_TYPE_NORMAL) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DIGITS_NUMBER)->EnableWindow((m_nType == TPEP_TYPE_NORMAL  &&  IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DIGITS)) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS)->EnableWindow((m_nType == TPEP_TYPE_NORMAL) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_NOOOL)->EnableWindow((m_nType == TPEP_TYPE_NORMAL  &&  IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS)) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_SOFTOOL)->EnableWindow((m_nType == TPEP_TYPE_NORMAL  &&  IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS)) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_HARDOOL)->EnableWindow((m_nType == TPEP_TYPE_NORMAL  &&  IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS)) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_DELTAOOL)->EnableWindow((m_nType == TPEP_TYPE_NORMAL  &&  IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS)) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_CONSISTENCYOOL)->EnableWindow((m_nType == TPEP_TYPE_NORMAL  &&  IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS)) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_VALID)->EnableWindow((m_nType == TPEP_TYPE_NORMAL  &&  IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS)) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_INVALID)->EnableWindow((m_nType == TPEP_TYPE_NORMAL  &&  IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS)) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY)->EnableWindow((m_nType == TPEP_TYPE_NORMAL) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_GOOD)->EnableWindow((m_nType == TPEP_TYPE_NORMAL  &&  IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY)) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_BAD)->EnableWindow((m_nType == TPEP_TYPE_NORMAL  &&  IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY)) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_COLORS)->EnableWindow();
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_COLORS_MESSAGES_STATIC)->EnableWindow();
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_COLORS_MESSAGES)->EnableWindow();
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_COLORS_STATUS_STATIC)->EnableWindow((m_nType == TPEP_TYPE_NORMAL) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_COLORS_STATUS)->EnableWindow((m_nType == TPEP_TYPE_NORMAL) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_COLORS_COLOR_STATIC)->EnableWindow((m_nType == TPEP_TYPE_NORMAL) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_COLORS_COLOR)->EnableWindow((m_nType == TPEP_TYPE_NORMAL) ? TRUE : FALSE);
}

BOOL CTPEPSettingsFilteringPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (m_nMode[0] != m_nMode[1] || m_nLimit[0] != m_nLimit[1] || m_nStatus[0] != m_nStatus[1] || m_tRange[0][0][0] != m_tRange[1][0][0] || m_tRange[0][0][1] != m_tRange[1][0][1] || m_tRange[0][1][0] != m_tRange[1][1][0] || m_tRange[0][1][1] != m_tRange[1][1][1] || m_tDailyRange[0][0] != m_tDailyRange[1][0] || m_tDailyRange[0][1] != m_tDailyRange[1][1] || m_tPeriodical[0] != m_tPeriodical[1] || m_nDigits[0] != m_nDigits[1] || m_nColor[0] != m_nColor[1] || m_nOOLColors[0].GetSize() != m_nOOLColors[1].GetSize() || memcmp(m_nOOLColors[0].GetData(), m_nOOLColors[1].GetData(), m_nOOLColors[0].GetSize()*sizeof(UINT))) : CLocalePropertyPage::IsModified()) : FALSE);
}

BOOL CTPEPSettingsFilteringPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (!IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS) || IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_NOOOL) || IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_SOFTOOL) || IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_HARDOOL) || IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_DELTAOOL) || IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_CONSISTENCYOOL)) : CLocalePropertyPage::Check()) : TRUE);
}

void CTPEPSettingsFilteringPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTPEPSettingsFilteringPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTPEPSettingsFilteringPage::PostNcDestroy()
{
	m_nOOLColors[0].RemoveAll();
	m_nOOLColors[1].RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTPEPSettingsFilteringPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CTPEPSettingsFilteringPage)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL, OnFilterByTime)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DAILY, OnFilterByDailyTime)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL, OnFilterByPeriodicalTime)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_START, OnFilterByPeriodicalStartTime)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOP, OnFilterByPeriodicalStopTime)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_LIMITMESSAGES, OnFilterByLimit)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DIGITS, OnFilterByDigits)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS, OnFilterByStatus)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_NOOOL, OnFilterByStatusValue)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_SOFTOOL, OnFilterByStatusValue)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_HARDOOL, OnFilterByStatusValue)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_DELTAOOL, OnFilterByStatusValue)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_CONSISTENCYOOL, OnFilterByStatusValue)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_VALID, OnFilterByStatusValue)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_INVALID, OnFilterByStatusValue)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY, OnFilterByQuality)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_GOOD, OnFilterByQualityValue)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_BAD, OnFilterByQualityValue)
	ON_CBN_SELCHANGE(IDC_TPEPSETTINGS_FILTERINGPAGE_COLORS_MESSAGES, OnSelchangeFilterColorMessages)
	ON_CBN_SELCHANGE(IDC_TPEPSETTINGS_FILTERINGPAGE_COLORS_STATUS, OnSelchangeFilterColorLocation)
	ON_CBN_SELCHANGE(IDC_TPEPSETTINGS_FILTERINGPAGE_COLORS_COLOR, OnSelchangeFilterColor)
	ON_CONTROL(SBXN_CHANGE, IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_INTERVAL, OnSpinchangeFilterPeriodicalInterval)
	ON_CONTROL(SBXN_CHANGE, IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_LIMITMESSAGES_NUMBER, OnSpinchangeFilterLimit)
	ON_CONTROL(SBXN_CHANGE, IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DIGITS_NUMBER, OnSpinchangeFilterDigits)
	ON_CONTROL(TSBXN_CHANGE, IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STARTTIME, OnSpinchangeFilterStartTime)
	ON_CONTROL(TSBXN_CHANGE, IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STOPTIME, OnSpinchangeFilterStopTime)
	ON_CONTROL(TSBXN_CHANGE, IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STARTTIME, OnSpinchangeFilterDailyStartTime)
	ON_CONTROL(TSBXN_CHANGE, IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STOPTIME, OnSpinchangeFilterDailyStopTime)
	ON_CONTROL(TSBXN_CHANGE, IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STARTTIME, OnSpinchangeFilterPeriodicalStartTime)
	ON_CONTROL(TSBXN_CHANGE, IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOPTIME, OnSpinchangeFilterPeriodicalStopTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTPEPSettingsFilteringPage message handlers

BOOL CTPEPSettingsFilteringPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	EnumFilterStatus();
	ShowFilterInfo();
	return TRUE;
}

void CTPEPSettingsFilteringPage::OnFilterByTime()
{
	CTimeKey  tTimeKey;

	m_nMode[0] = (IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL)) ? (m_nMode[0] | TPEP_FILTER_RANGE) : (m_nMode[0] & ~TPEP_FILTER_RANGE);
	m_tRange[0][0][0] = (IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL)) ? tTimeKey.GetTime() : 0;
	m_tRange[0][0][1] = (IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL)) ? (tTimeKey.GetTime() + SECONDSPERMINUTE*TPEPSETTINGSFILTERINGPAGE_DEFAULTRANGE) : 0;
	Timespinbox_SetTime(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STARTTIME), (m_tRange[0][0][0].GetTime() > 0) ? m_tRange[0][0][0] : tTimeKey);
	Timespinbox_SetTime(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STOPTIME), (m_tRange[0][0][1].GetTime() > 0) ? m_tRange[0][0][1] : tTimeKey);
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STARTTIME)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STARTTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsFilteringPage::OnFilterByDailyTime()
{
	CTimeKey  tTimeKey;

	m_nMode[0] = (IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DAILY)) ? (m_nMode[0] | TPEP_FILTER_DAILYRANGE) : (m_nMode[0] & ~TPEP_FILTER_DAILYRANGE);
	m_tDailyRange[0][0] = (IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DAILY)) ? TPEPSETTINGSFILTERINGPAGE_DEFAULTDAILYSTARTTIME : 0;
	m_tDailyRange[0][1] = (IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DAILY)) ? TPEPSETTINGSFILTERINGPAGE_DEFAULTDAILYSTOPTIME : 0;
	Timespinbox_SetTime(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STARTTIME), CTimeKey(SECONDSPERDAY*(tTimeKey.GetTime() / SECONDSPERDAY) + m_tDailyRange[0][0].GetTotalSeconds()));
	Timespinbox_SetTime(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STOPTIME), CTimeKey(SECONDSPERDAY*(tTimeKey.GetTime() / SECONDSPERDAY) + m_tDailyRange[0][1].GetTotalSeconds()));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STARTTIME)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DAILY));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DAILY));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DAILY));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STARTTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsFilteringPage::OnFilterByPeriodicalTime()
{
	m_nMode[0] = (IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL)) ? (m_nMode[0] | TPEP_FILTER_PERIODICALRANGE) : (m_nMode[0] & ~TPEP_FILTER_PERIODICALRANGE);
	m_tPeriodical[0] = (IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL)) ? (SECONDSPERMINUTE*TPEPSETTINGSFILTERINGPAGE_DEFAULTINTERVAL) : 0;
	m_tRange[0][1][0] = m_tRange[0][1][1] = (IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL)) ? 0 : 0;
	Spinbox_SetPos(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_INTERVAL), TPEPSETTINGSFILTERINGPAGE_DEFAULTINTERVAL);
	CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_START, FALSE);
	CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOP, FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_INTERVAL)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_INTERVAL_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_START)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STARTTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOP)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOPTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_INTERVAL)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsFilteringPage::OnFilterByPeriodicalStartTime()
{
	CTimeKey  tTimeKey;

	m_tRange[0][1][0] = (IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_START)) ? tTimeKey.GetTime() : 0;
	Timespinbox_SetTime(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STARTTIME), (m_tRange[0][1][0].GetTime() > 0) ? m_tRange[0][1][0] : tTimeKey);
	Timespinbox_SetTime(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOPTIME), (m_tRange[0][1][0] >= m_tRange[0][1][1] && m_tRange[0][1][0] > 0) ? (m_tRange[0][1][0].GetTime() + 1) : ((m_tRange[0][1][1] > 0) ? m_tRange[0][1][1].GetTime() : tTimeKey));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STARTTIME)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_START));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STARTTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsFilteringPage::OnFilterByPeriodicalStopTime()
{
	CTimeKey  tTimeKey;

	m_tRange[0][1][1] = (IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOP)) ? (tTimeKey.GetTime() + SECONDSPERMINUTE*TPEPSETTINGSFILTERINGPAGE_DEFAULTRANGE) : 0;
	Timespinbox_SetTime(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOPTIME), (m_tRange[0][1][1].GetTime() > 0) ? m_tRange[0][1][1] : tTimeKey);
	Timespinbox_SetTime(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STARTTIME), (m_tRange[0][1][0] >= m_tRange[0][1][1] && m_tRange[0][1][1] > 0) ? (m_tRange[0][1][1].GetTime() - 1) : ((m_tRange[0][1][0] > 0) ? m_tRange[0][1][0].GetTime() : tTimeKey));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOP));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOPTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsFilteringPage::OnFilterByLimit()
{
	m_nMode[0] = (IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_LIMITMESSAGES)) ? (m_nMode[0] | TPEP_FILTER_LIMIT) : (m_nMode[0] & ~TPEP_FILTER_LIMIT);
	m_nLimit[0] = (IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_LIMITMESSAGES)) ? TPEPSETTINGSFILTERINGPAGE_DEFAULTMESSAGES : 0;
	Spinbox_SetPos(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_LIMITMESSAGES_NUMBER), TPEPSETTINGSFILTERINGPAGE_DEFAULTMESSAGES);
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_LIMITMESSAGES_NUMBER)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_LIMITMESSAGES));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_LIMITMESSAGES_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_LIMITMESSAGES));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_LIMITMESSAGES_NUMBER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsFilteringPage::OnFilterByDigits()
{
	m_nDigits[0] = (IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DIGITS)) ? TPEPSETTINGSFILTERINGPAGE_DEFAULTDIGITS : 0;
	Spinbox_SetPos(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DIGITS_NUMBER), TPEPSETTINGSFILTERINGPAGE_DEFAULTDIGITS);
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DIGITS_NUMBER)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DIGITS));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DIGITS_NUMBER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsFilteringPage::OnFilterByStatus()
{
	m_nMode[0] = (IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS) || IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY)) ? (m_nMode[0] | TPEP_FILTER_STATUS) : (m_nMode[0] & ~TPEP_FILTER_STATUS);
	m_nStatus[0] = (IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS)) ? (TMPARAMETER_STATUS_NOLIMIT | TMPARAMETER_STATUS_VALID | (GetFilterStatus() & (TMPARAMETER_STATUS_GOOD | TMPARAMETER_STATUS_BAD))) : (GetFilterStatus() & (TMPARAMETER_STATUS_GOOD | TMPARAMETER_STATUS_BAD));
	CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_NOOOL, IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS));
	CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_SOFTOOL, FALSE);
	CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_HARDOOL, FALSE);
	CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_DELTAOOL, FALSE);
	CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_CONSISTENCYOOL, FALSE);
	CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_INVALID, FALSE);
	CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_VALID, IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_NOOOL)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_SOFTOOL)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_HARDOOL)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_DELTAOOL)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_CONSISTENCYOOL)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_VALID)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_INVALID)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsFilteringPage::OnFilterByStatusValue()
{
	if ((!IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_NOOOL) && !IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_SOFTOOL) && !IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_HARDOOL) && !IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_DELTAOOL) && !IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_CONSISTENCYOOL)) || (!IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_VALID) && !IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_INVALID)))
	{
		CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS, FALSE);
		CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_NOOOL, FALSE);
		CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_SOFTOOL, FALSE);
		CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_HARDOOL, FALSE);
		CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_DELTAOOL, FALSE);
		CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_CONSISTENCYOOL, FALSE);
		CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_VALID, FALSE);
		CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_INVALID, FALSE);
		GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_NOOOL)->EnableWindow(FALSE);
		GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_SOFTOOL)->EnableWindow(FALSE);
		GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_HARDOOL)->EnableWindow(FALSE);
		GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_DELTAOOL)->EnableWindow(FALSE);
		GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_CONSISTENCYOOL)->EnableWindow(FALSE);
		GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_VALID)->EnableWindow(FALSE);
		GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_INVALID)->EnableWindow(FALSE);
	}
	m_nStatus[0] = GetFilterStatus();
	m_nMode[0] = (IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS) || IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY)) ? (m_nMode[0] | TPEP_FILTER_STATUS) : (m_nMode[0] & ~TPEP_FILTER_STATUS);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsFilteringPage::OnFilterByQuality()
{
	m_nMode[0] = (IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS) || IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY)) ? (m_nMode[0] | TPEP_FILTER_STATUS) : (m_nMode[0] & ~TPEP_FILTER_STATUS);
	m_nStatus[0] = (IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY)) ? ((GetFilterStatus() & (TMPARAMETER_STATUS_NOLIMIT | TMPARAMETER_STATUS_SOFTLIMIT | TMPARAMETER_STATUS_HARDLIMIT | TMPARAMETER_STATUS_DELTALIMIT | TMPARAMETER_STATUS_CONSISTENCYLIMIT | TMPARAMETER_STATUS_VALID | TMPARAMETER_STATUS_INVALID)) | TMPARAMETER_STATUS_GOOD) : (GetFilterStatus() & (TMPARAMETER_STATUS_NOLIMIT | TMPARAMETER_STATUS_SOFTLIMIT | TMPARAMETER_STATUS_HARDLIMIT | TMPARAMETER_STATUS_DELTALIMIT | TMPARAMETER_STATUS_CONSISTENCYLIMIT | TMPARAMETER_STATUS_VALID | TMPARAMETER_STATUS_INVALID));
	CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_GOOD, IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY));
	CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_BAD, FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_GOOD)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_BAD)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsFilteringPage::OnFilterByQualityValue()
{
	m_nStatus[0] = GetFilterStatus();
	m_nMode[0] = (IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_STATUS) || IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_GOOD) || IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_BAD)) ? (m_nMode[0] | TPEP_FILTER_STATUS) : (m_nMode[0] & ~TPEP_FILTER_STATUS);
	CheckDlgButton(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY, IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_GOOD) || IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_BAD));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_GOOD)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY));
	GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_BAD)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsFilteringPage::OnSpinchangeFilterStartTime()
{
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;

	for (tStartTime = Timespinbox_GetTime(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STARTTIME)), tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STOPTIME)); tStartTime >= tStopTime; )
	{
		Timespinbox_SetTime(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STOPTIME), (tStopTime = tStartTime.GetTime() + 1));
		break;
	}
	m_tRange[0][0][0] = tStartTime;
	m_tRange[0][0][1] = tStopTime;
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsFilteringPage::OnSpinchangeFilterStopTime()
{
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;

	for (tStartTime = Timespinbox_GetTime(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STARTTIME)), tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STOPTIME)); tStartTime >= tStopTime; )
	{
		Timespinbox_SetTime(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STARTTIME), (tStartTime = max(tStopTime.GetTime() - 1, 0)));
		break;
	}
	m_tRange[0][0][0] = tStartTime;
	m_tRange[0][0][1] = tStopTime;
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsFilteringPage::OnSpinchangeFilterDailyStartTime()
{
	m_tDailyRange[0][0] = Timespinbox_GetTime(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STARTTIME)).GetTime() % SECONDSPERDAY;
	m_tDailyRange[0][1] = Timespinbox_GetTime(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STOPTIME)).GetTime() % SECONDSPERDAY;
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsFilteringPage::OnSpinchangeFilterDailyStopTime()
{
	m_tDailyRange[0][0] = Timespinbox_GetTime(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STARTTIME)).GetTime() % SECONDSPERDAY;
	m_tDailyRange[0][1] = Timespinbox_GetTime(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STOPTIME)).GetTime() % SECONDSPERDAY;
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsFilteringPage::OnSpinchangeFilterPeriodicalInterval()
{
	for (; IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL); )
	{
		if (IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOP))
		{
			m_tPeriodical[0] = SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_INTERVAL));
			m_tRange[0][1][1] = (m_tRange[0][1][0] + m_tPeriodical[0] > m_tRange[0][1][1]) ? (m_tRange[0][1][0].GetTime() + m_tPeriodical[0].GetTotalSeconds()) : m_tRange[0][1][1].GetTime();
			Timespinbox_SetTime(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOPTIME), m_tRange[0][1][1]);
			break;
		}
		m_tPeriodical[0] = SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_INTERVAL));
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsFilteringPage::OnSpinchangeFilterPeriodicalStartTime()
{
	CTimeKey  tTime;

	if (IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOP))
	{
		Timespinbox_SetTime(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOPTIME), m_tRange[0][1][1]);
		m_tRange[0][1][1] = ((tTime = Timespinbox_GetTime(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STARTTIME))).GetTime() + m_tPeriodical[0].GetTotalSeconds() > m_tRange[0][1][1].GetTime()) ? (tTime.GetTime() + m_tPeriodical[0].GetTotalSeconds()) : m_tRange[0][1][1];
		m_tRange[0][1][0] = tTime;
	}
	else
	{
		tTime = Timespinbox_GetTime(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STARTTIME));
		m_tRange[0][1][0] = tTime;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsFilteringPage::OnSpinchangeFilterPeriodicalStopTime()
{
	CTimeKey  tTime;

	if (IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_START))
	{
		Timespinbox_SetTime(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STARTTIME), m_tRange[0][1][0]);
		m_tRange[0][1][0] = ((tTime = Timespinbox_GetTime(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOPTIME))) < m_tRange[0][1][0] + m_tPeriodical[0].GetTotalSeconds()) ? (tTime.GetTime() - m_tPeriodical[0].GetTotalSeconds()) : m_tRange[0][1][0];
		m_tRange[0][1][1] = tTime;
	}
	else
	{
		tTime = Timespinbox_GetTime(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOPTIME));
		m_tRange[0][1][1] = tTime;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsFilteringPage::OnSpinchangeFilterLimit()
{
	m_nLimit[0] = (IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_LIMITMESSAGES)) ? (UINT)Spinbox_GetPos(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_LIMITMESSAGES_NUMBER)) : 0;
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsFilteringPage::OnSpinchangeFilterDigits()
{
	m_nDigits[0] = (IsDlgButtonChecked(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DIGITS)) ? (UINT)Spinbox_GetPos(GetDlgItem(IDC_TPEPSETTINGS_FILTERINGPAGE_OPTIONS_DIGITS_NUMBER)) : 0;
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsFilteringPage::OnSelchangeFilterColorMessages()
{
	m_nColor[0] = (SendDlgItemMessage(IDC_TPEPSETTINGS_FILTERINGPAGE_COLORS_MESSAGES, CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)((m_nColor[1] != 0) ? m_nColor[1] : VGA_COLOR_BLACK)) != SendDlgItemMessage(IDC_TPEPSETTINGS_FILTERINGPAGE_COLORS_MESSAGES, CB_GETCURSEL)) ? (COLORREF)SendDlgItemMessage(IDC_TPEPSETTINGS_FILTERINGPAGE_COLORS_MESSAGES, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_TPEPSETTINGS_FILTERINGPAGE_COLORS_MESSAGES, CB_GETCURSEL)) : m_nColor[1];
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsFilteringPage::OnSelchangeFilterColorLocation()
{
	INT  nIndex;

	SendDlgItemMessage(IDC_TPEPSETTINGS_FILTERINGPAGE_COLORS_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, ((nIndex = (INT)SendDlgItemMessage(IDC_TPEPSETTINGS_FILTERINGPAGE_COLORS_STATUS, CB_GETCURSEL)) < m_nOOLColors[0].GetSize()) ? (LPARAM)m_nOOLColors[0].GetAt(nIndex) : (LPARAM)VGA_COLOR_BLACK);
}

void CTPEPSettingsFilteringPage::OnSelchangeFilterColor()
{
	INT  nIndex;

	for (nIndex = (INT)SendDlgItemMessage(IDC_TPEPSETTINGS_FILTERINGPAGE_COLORS_STATUS, CB_GETCURSEL); nIndex < m_nOOLColors[0].GetSize(); )
	{
		m_nOOLColors[0].SetAt(nIndex, (UINT)SendDlgItemMessage(IDC_TPEPSETTINGS_FILTERINGPAGE_COLORS_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_TPEPSETTINGS_FILTERINGPAGE_COLORS_COLOR, CB_GETCURSEL)));
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CTPEPSettingsPrintingComments

IMPLEMENT_DYNCREATE(CTPEPSettingsPrintingComments, CEdit)

BEGIN_MESSAGE_MAP(CTPEPSettingsPrintingComments, CEdit)
	//{{AFX_MSG_MAP(CTPEPSettingsPrintingComments)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTPEPSettingsPrintingComments message handlers

void CTPEPSettingsPrintingComments::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_TAB)
	{
		if (!HIBYTE(GetKeyState(VK_SHIFT)))
		{
			GetParent()->GetParent()->GetNextDlgTabItem(GetParent())->SetFocus();
			return;
		}
	}
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}


/////////////////////////////////////////////////////////////////////////////
// CTPEPSettingsPrintingPage property page

IMPLEMENT_DYNCREATE(CTPEPSettingsPrintingPage, CLocalePropertyPage)

CTPEPSettingsPrintingPage::CTPEPSettingsPrintingPage() : CLocalePropertyPage(CTPEPSettingsPrintingPage::IDD)
{
	//{{AFX_DATA_INIT(CTPEPSettingsPrintingPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTPEPSettingsPrintingPage::Initialize()
{
	CTPEPOpenDialog  *pDialog;

	return((((pDialog = GetParentDialog()->GetParentDialog()) && pDialog->GetPrintJobs(m_pJobs[0])) || GetParentDisplay()->GetPrintJobs(m_pJobs[0])) ? m_pJobs[1].Copy(&m_pJobs[0]) : FALSE);
}

BOOL CTPEPSettingsPrintingPage::GetJobs(CTPEPPrintJobs &pJobs) CONST
{
	return((pJobs.Copy(&m_pJobs[0])) ? Check(FALSE) : FALSE);
}

CTPEPSettingsDialog *CTPEPSettingsPrintingPage::GetParentDialog() CONST
{
	return((CTPEPSettingsDialog *)CLocalePropertyPage::GetParent());
}

CTPEPWnd *CTPEPSettingsPrintingPage::GetParentDisplay() CONST
{
	return((CTPEPWnd *)GetParentDialog()->GetParentDisplay());
}

VOID CTPEPSettingsPrintingPage::ShowJobInfo()
{
	UINT  nMode;
	UINT  nCount;
	CTimeSpan  tStartTime;
	CTimeSpan  tStopTime;
	CTPEPPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		CheckDlgButton(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL, ((nMode = pJobInfo->GetPrintMode()) & TPEP_PRINT_ALL) ? TRUE : FALSE);
		CheckDlgButton(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE, ((nMode & TPEP_PRINT_FIRSTSIDE) || (nMode & TPEP_PRINT_LASTSIDE)) ? TRUE : FALSE);
		CheckDlgButton(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL, (nMode & TPEP_PRINT_UNDERLINEOOL) ? TRUE : FALSE);
		CheckDlgButton(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND, (nMode & TPEP_PRINT_COLORLEGEND) ? TRUE : FALSE);
		CheckDlgButton(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS, (nMode & TPEP_PRINT_CLEARCOMMENTS) ? TRUE : FALSE);
		SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetProfile()));
		SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_SELECTTEXT, (WPARAM)-1, (nMode & TPEP_PRINT_FIRSTSIDE) ? (LPARAM)STRING(IDS_TPEPSETTINGS_PRINTINGPAGE_FIRSTSIDE) : ((nMode & TPEP_PRINT_LASTSIDE) ? (LPARAM)STRING(IDS_TPEPSETTINGS_PRINTINGPAGE_LASTSIDE) : (LPARAM)EMPTYSTRING));
		Spinbox_SetPos(GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT), (pJobInfo->GetPrintBySide(nCount)) ? nCount : 0);
		GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->SetWindowText(pJobInfo->GetComments());
		GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_ADDNAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_REMOVENAME)->EnableWindow((pJobInfo->GetName() != STRING(IDS_PRINTJOB_DEFAULTNAME)) ? TRUE : FALSE);
		GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_REMOVEALLNAMES)->EnableWindow((SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTINGPAGE_NAME, CB_GETCOUNT) > 1) ? TRUE : FALSE);
		GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES)->EnableWindow();
		GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE_STATIC)->EnableWindow();
		GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE)->EnableWindow();
		GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_OPTIONS)->EnableWindow();
		GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL)->EnableWindow();
		GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE)->EnableWindow();
		GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE));
		GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE));
		GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE));
		GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL)->EnableWindow();
		GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND)->EnableWindow();
		GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTS)->EnableWindow();
		GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT_STATIC)->EnableWindow();
		GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->EnableWindow();
		GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)->EnableWindow(!pJobInfo->GetComments().IsEmpty());
		return;
	}
	SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)-1);
	SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_SETCURSEL, (WPARAM)-1);
	CheckDlgButton(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL, FALSE);
	CheckDlgButton(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE, FALSE);
	CheckDlgButton(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL, FALSE);
	CheckDlgButton(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND, FALSE);
	CheckDlgButton(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS, FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_ADDNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_REMOVENAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_REMOVEALLNAMES)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_OPTIONS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)->EnableWindow(FALSE);
}

CTPEPPrintJobInfo *CTPEPSettingsPrintingPage::FindJobInfo() CONST
{
	CString  szJobName;

	GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_NAME)->GetWindowText(szJobName);
	return m_pJobs[0].GetAt(m_pJobs[0].Find(szJobName));
}

BOOL CTPEPSettingsPrintingPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? !m_pJobs[0].Compare(&m_pJobs[1]) : CLocalePropertyPage::IsModified()) : FALSE);
}

BOOL CTPEPSettingsPrintingPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? ((GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_NAME)->GetWindowTextLength() > 0 && FindJobInfo()) ? TRUE : FALSE) : CLocalePropertyPage::Check()) : TRUE);
}

void CTPEPSettingsPrintingPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTPEPSettingsPrintingPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTPEPSettingsPrintingPage::PostNcDestroy()
{
	m_pJobs[0].RemoveAll();
	m_pJobs[1].RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTPEPSettingsPrintingPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CTPEPSettingsPrintingPage)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_PRINTINGPAGE_ADDNAME, OnAddName)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_PRINTINGPAGE_REMOVENAME, OnRemoveName)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_PRINTINGPAGE_REMOVEALLNAMES, OnRemoveAllNames)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL, OnPrintAll)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE, OnPrintBySide)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL, OnPrintUnderlineOOL)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND, OnPrintColorLegend)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS, OnResetComments)
	ON_CBN_EDITCHANGE(IDC_TPEPSETTINGS_PRINTINGPAGE_NAME, OnEditchangeName)
	ON_CBN_SELCHANGE(IDC_TPEPSETTINGS_PRINTINGPAGE_NAME, OnSelchangeName)
	ON_CBN_SELCHANGE(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, OnSelchangeProfile)
	ON_EN_CHANGE(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, OnChangePrintSide)
	ON_EN_CHANGE(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT, OnEditchangeComments)
	ON_CONTROL(SBXN_CHANGE, IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT, OnSpinchangePrintSideCount)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTPEPSettingsPrintingPage message handlers

BOOL CTPEPSettingsPrintingPage::OnInitDialog()
{
	INT  nJob;
	INT  nJobs;
	INT  nProfile;
	INT  nProfiles;
	CStringArray  szProfiles;
	CTPEPPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	for (CLocalePropertyPage::OnInitDialog(); m_wndComments.SubclassWindow(GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->GetSafeHwnd()); )
	{
		for (nJob = 0, nJobs = (INT)m_pJobs[0].GetSize(); nJob < nJobs; nJob++)
		{
			if ((pJobInfo = m_pJobs[0].GetAt(nJob)) != (CTPEPPrintJobInfo *)NULL)
			{
				SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTINGPAGE_NAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pJobInfo->GetName());
				continue;
			}
		}
		for (nProfile = 0, nProfiles = (EnumPrintProfiles(szProfiles)) ? (INT)szProfiles.GetSize() : 0; nProfile < nProfiles; nProfile++)
		{
			SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szProfiles.GetAt(nProfile));
			continue;
		}
		Spinbox_SetRange(GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT), TPEPSETTINGSPRINTINGPAGE_OPTIONS_MINIMUMMESSAGES, TPEPSETTINGSPRINTINGPAGE_OPTIONS_MAXIMUMMESSAGES);
		SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_PRINTJOB_DEFAULTNAME)));
		SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_ADDTEXT, (WPARAM)NULL, (LPARAM)STRING(IDS_TPEPSETTINGS_PRINTINGPAGE_FIRSTSIDE));
		SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_ADDTEXT, (WPARAM)NULL, (LPARAM)STRING(IDS_TPEPSETTINGS_PRINTINGPAGE_LASTSIDE));
		GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_DETAILS)->EnableWindow();
		GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_NAME_STATIC)->EnableWindow();
		GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_NAME)->EnableWindow();
		ShowJobInfo();
		break;
	}
	return TRUE;
}

BOOL CTPEPSettingsPrintingPage::OnSetActive()
{
	ShowJobInfo();
	return CLocalePropertyPage::OnSetActive();
}

BOOL CTPEPSettingsPrintingPage::OnKillActive()
{
	GetParentDialog()->OnDataExchange(GetSafeHwnd(), m_pJobs[0]);
	return CLocalePropertyPage::OnKillActive();
}

BOOL CTPEPSettingsPrintingPage::OnDataExchange(CONST CTPEPPrintJobs &pJobs)
{
	return m_pJobs[0].Copy(&pJobs);
}

void CTPEPSettingsPrintingPage::OnEditchangeName()
{
	CString  szJobName;
	CTPEPPrintJobInfo  *pJobInfo;

	for (GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_NAME)->GetWindowText(szJobName); (pJobInfo = FindJobInfo()); )
	{
		ShowJobInfo();
		return;
	}
	GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_ADDNAME)->EnableWindow((!pJobInfo  &&  szJobName.GetLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_REMOVENAME)->EnableWindow((pJobInfo != (CTPEPPrintJobInfo *)NULL  &&  szJobName != STRING(IDS_PRINTJOB_DEFAULTNAME)) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_REMOVEALLNAMES)->EnableWindow((SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTINGPAGE_NAME, CB_GETCOUNT) > 1) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)->EnableWindow((szJobName != STRING(IDS_PRINTJOB_DEFAULTNAME)) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsPrintingPage::OnSelchangeName()
{
	SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTINGPAGE_NAME, CB_GETCURSEL));
	ShowJobInfo();
}

void CTPEPSettingsPrintingPage::OnAddName()
{
	INT  nIndex;
	UINT  nMode;
	UINT  nCount;
	CString  szJobName;
	CString  szProfile;
	CString  szComments;
	CTPEPPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	for (; (pJobInfo = new CTPEPPrintJobInfo); )
	{
		GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_NAME)->GetWindowText(szJobName);
		GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE)->GetWindowText(szProfile);
		GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->GetWindowText(szComments);
		nMode = (IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL)) ? ((pJobInfo->GetPrintMode() | TPEP_PRINT_ALL) & ~(TPEP_PRINT_FIRSTSIDE | TPEP_PRINT_LASTSIDE)) : pJobInfo->GetPrintMode();
		nMode = (IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE)) ? ((!GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE)->SendMessage(TEM_GETPOS)) ? ((nMode | TPEP_PRINT_FIRSTSIDE) & ~(TPEP_PRINT_ALL | TPEP_PRINT_LASTSIDE)) : ((nMode | TPEP_PRINT_LASTSIDE) & ~(TPEP_PRINT_ALL | TPEP_PRINT_FIRSTSIDE))) : nMode;
		nMode = (IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL)) ? (nMode | TPEP_PRINT_UNDERLINEOOL) : nMode;
		nMode = (IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND)) ? (nMode | TPEP_PRINT_COLORLEGEND) : nMode;
		nMode = (IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)) ? (nMode | TPEP_PRINT_CLEARCOMMENTS) : (nMode & ~TPEP_PRINT_CLEARCOMMENTS);
		nCount = ((nMode & TPEP_PRINT_FIRSTSIDE) || (nMode & TPEP_PRINT_LASTSIDE)) ? (UINT)Spinbox_GetPos(GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)) : 0;
		if (SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTINGPAGE_NAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szJobName) >= 0 && SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szJobName)) >= 0)
		{
			for (pJobInfo->SetName(szJobName), pJobInfo->SetProfile(szProfile), pJobInfo->SetComments(szComments), pJobInfo->SetPrintMode(nMode), pJobInfo->SetPrintBySide(nCount); (nIndex = m_pJobs[0].Add(pJobInfo)) >= 0; )
			{
				ShowJobInfo();
				break;
			}
			if (nIndex >= 0) break;
		}
		delete pJobInfo;
		break;
	}
	GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsPrintingPage::OnRemoveName()
{
	INT  nJob;
	INT  nJobs;
	CTPEPPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	for (nJob = 0, nJobs = (INT)m_pJobs[0].GetSize(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = m_pJobs[0].GetAt(nJob)) && pJobInfo == FindJobInfo())
		{
			if (SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTINGPAGE_NAME, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName())) > 0)
			{
				m_pJobs[0].RemoveAt(nJob);
				delete pJobInfo;
			}
			break;
		}
	}
	for (; SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_PRINTJOB_DEFAULTNAME))) >= 0; )
	{
		ShowJobInfo();
		break;
	}
	GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsPrintingPage::OnRemoveAllNames()
{
	INT  nJob;
	INT  nJobs;
	CTPEPPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	for (nJob = 0, nJobs = (INT)m_pJobs[0].GetSize(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = m_pJobs[0].GetAt(nJob)) && pJobInfo->GetName() != STRING(IDS_PRINTJOB_DEFAULTNAME) && SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTINGPAGE_NAME, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName())) > 0)
		{
			m_pJobs[0].RemoveAt(nJob);
			delete pJobInfo;
			nJobs--;
			nJob--;
		}
	}
	for (; SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_PRINTJOB_DEFAULTNAME))) >= 0; )
	{
		ShowJobInfo();
		break;
	}
	GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsPrintingPage::OnSelchangeProfile()
{
	CString  szProfile;
	CTPEPPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE)->GetWindowText(szProfile);
		pJobInfo->SetProfile(szProfile);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsPrintingPage::OnPrintAll()
{
	CTPEPPrintJobInfo  *pJobInfo;

	if (!IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL))
	{
		for (CheckDlgButton(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL, TRUE), CheckDlgButton(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE, FALSE), SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_SELECTTEXT, (WPARAM)-1, (LPARAM)EMPTYSTRING); (pJobInfo = FindJobInfo()); )
		{
			pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | TPEP_PRINT_ALL) & ~(TPEP_PRINT_FIRSTSIDE | TPEP_PRINT_LASTSIDE));
			break;
		}
		GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_ADDNAME)->EnableWindow((GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_NAME)->GetWindowTextLength() > 0 && SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_GETCURSEL) != CB_ERR  &&  !pJobInfo) ? TRUE : FALSE);
		GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE)->EnableWindow(FALSE);
		GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)->EnableWindow(FALSE);
		GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE_STATIC)->EnableWindow(FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsPrintingPage::OnPrintBySide()
{
	CTPEPPrintJobInfo  *pJobInfo;

	if (!IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE))
	{
		for (CheckDlgButton(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL, FALSE), CheckDlgButton(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE, TRUE), SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_SELECTTEXT, (WPARAM)-1, (LPARAM)STRING(IDS_TPEPSETTINGS_PRINTINGPAGE_LASTSIDE)), Spinbox_SetPos(GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT), TPEPSETTINGSPRINTINGPAGE_OPTIONS_DEFAULTMESSAGES); (pJobInfo = FindJobInfo()); )
		{
			pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | TPEP_PRINT_LASTSIDE) & ~(TPEP_PRINT_ALL | TPEP_PRINT_FIRSTSIDE));
			pJobInfo->SetPrintBySide(TPEPSETTINGSPRINTINGPAGE_OPTIONS_DEFAULTMESSAGES);
			break;
		}
		SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, EM_SETSEL, 0, (LPARAM)-1);
		GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_ADDNAME)->EnableWindow((GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_NAME)->GetWindowTextLength() > 0 && SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_GETCURSEL) != CB_ERR  &&  !pJobInfo) ? TRUE : FALSE);
		GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE)->EnableWindow();
		GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)->EnableWindow();
		GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE_STATIC)->EnableWindow();
		GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE)->SetFocus();
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsPrintingPage::OnPrintUnderlineOOL()
{
	UINT  nMode;
	CTPEPPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		nMode = (IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL)) ? (pJobInfo->GetPrintMode() | TPEP_PRINT_UNDERLINEOOL) : (pJobInfo->GetPrintMode() & ~TPEP_PRINT_UNDERLINEOOL);
		pJobInfo->SetPrintMode(nMode);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsPrintingPage::OnPrintColorLegend()
{
	UINT  nMode;
	CTPEPPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		nMode = (IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND)) ? (pJobInfo->GetPrintMode() | TPEP_PRINT_COLORLEGEND) : (pJobInfo->GetPrintMode() & ~TPEP_PRINT_COLORLEGEND);
		pJobInfo->SetPrintMode(nMode);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsPrintingPage::OnChangePrintSide()
{
	UINT  nMode;
	CTPEPPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		nMode = (!SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_GETPOS)) ? ((pJobInfo->GetPrintMode() | TPEP_PRINT_FIRSTSIDE) & ~(TPEP_PRINT_ALL | TPEP_PRINT_LASTSIDE)) : ((pJobInfo->GetPrintMode() | TPEP_PRINT_LASTSIDE) & ~(TPEP_PRINT_ALL | TPEP_PRINT_FIRSTSIDE));
		pJobInfo->SetPrintMode(nMode);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsPrintingPage::OnSpinchangePrintSideCount()
{
	CTPEPPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo())) pJobInfo->SetPrintBySide((UINT)Spinbox_GetPos(GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsPrintingPage::OnEditchangeComments()
{
	CString  szComments;
	CTPEPPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->GetWindowText(szComments);
		GetDlgItem(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)->EnableWindow(!szComments.IsEmpty());
		CheckDlgButton(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS, (!szComments.IsEmpty()) ? IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS) : FALSE);
		pJobInfo->SetPrintMode((IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)) ? (pJobInfo->GetPrintMode() | TPEP_PRINT_CLEARCOMMENTS) : (pJobInfo->GetPrintMode() & ~TPEP_PRINT_CLEARCOMMENTS));
		pJobInfo->SetComments(szComments);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsPrintingPage::OnResetComments()
{
	UINT  nMode;
	CTPEPPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		nMode = (IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)) ? (pJobInfo->GetPrintMode() | TPEP_PRINT_CLEARCOMMENTS) : (pJobInfo->GetPrintMode() & ~TPEP_PRINT_CLEARCOMMENTS);
		pJobInfo->SetPrintMode(nMode);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CTPEPSettingsPrintJobsPage property page

IMPLEMENT_DYNCREATE(CTPEPSettingsPrintJobsPage, CLocalePropertyPage)

CTPEPSettingsPrintJobsPage::CTPEPSettingsPrintJobsPage() : CLocalePropertyPage(CTPEPSettingsPrintJobsPage::IDD)
{
	//{{AFX_DATA_INIT(CTPEPSettingsPrintJobsPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CTPEPSettingsPrintJobsPage::Initialize()
{
	CTPEPOpenDialog  *pDialog;

	return((((pDialog = GetParentDialog()->GetParentDialog()) && pDialog->GetPrintJobs(m_pJobs[0])) || GetParentDisplay()->GetPrintJobs(m_pJobs[0])) ? m_pJobs[1].Copy(&m_pJobs[0]) : FALSE);
}

BOOL CTPEPSettingsPrintJobsPage::GetJobs(CTPEPPrintJobs &pJobs) CONST
{
	return((pJobs.Copy(&m_pJobs[0])) ? Check(FALSE) : FALSE);
}

CTPEPSettingsDialog *CTPEPSettingsPrintJobsPage::GetParentDialog() CONST
{
	return((CTPEPSettingsDialog *)CLocalePropertyPage::GetParent());
}

CTPEPWnd *CTPEPSettingsPrintJobsPage::GetParentDisplay() CONST
{
	return((CTPEPWnd *)GetParentDialog()->GetParentDisplay());
}

BOOL CTPEPSettingsPrintJobsPage::EnumJobs()
{
	INT  nJob;
	INT  nJobs;
	UINT  nMode;
	CTPEPPrintJobInfo  *pJobInfo;

	SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, LB_RESETCONTENT);
	SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_RESETCONTENT);
	for (nJob = 0, nJobs = (INT)m_pJobs[0].GetSize(); nJob < nJobs; nJob = nJob + 1)
	{
		if ((pJobInfo = m_pJobs[0].GetAt(nJob)) && pJobInfo->GetName() != STRING(IDS_PRINTJOB_DEFAULTNAME))
		{
			if (SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pJobInfo->GetName()) >= 0)
			{
				if (((nMode = pJobInfo->GetPrintMode()) & TPEP_PRINT_ACTIVE) && ((nMode & TPEP_PRINT_ATTIME) || (nMode & TPEP_PRINT_ATDAILYTIME) || (nMode & TPEP_PRINT_ATEVENT)))
				{
					if (SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR)
					{
						pJobInfo->SetPrintMode(nMode & ~(TPEP_PRINT_ACTIVE | TPEP_PRINT_ATTIME | TPEP_PRINT_ATDAILYTIME | TPEP_PRINT_ATEVENT | TPEP_PRINT_REPEATBYINTERVAL | TPEP_PRINT_REPEATSTOPBYCOUNT | TPEP_PRINT_REPEATSTOPBYTIME | TPEP_PRINT_DAILYREPEATSTOPBYCOUNT | TPEP_PRINT_DAILYREPEATSTOPBYTIME));
						continue;
					}
				}
			}
		}
	}
	if (SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, LB_GETCOUNT) > 0)
	{
		SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, LB_SETCURSEL);
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_DETAILS)->EnableWindow();
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS_STATIC)->EnableWindow();
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS)->EnableWindow();
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS)->EnableWindow((SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)Listbox_GetText(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS), (INT)SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, LB_GETCURSEL))) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_REMOVEJOB)->EnableWindow((SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
		ShowJobInfo();
		return TRUE;
	}
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_DETAILS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_REMOVEJOB)->EnableWindow(FALSE);
	ShowJobInfo();
	return FALSE;
}

BOOL CTPEPSettingsPrintJobsPage::EnumEvents()
{
	INT  nEvent;
	INT  nEvents;
	CTelemetryEvents  pEvents;
	CTelemetryEventInfo  *pEventInfo;

	for (nEvent = 0, nEvents = (GetTelemetryEvents(pEvents)) ? (INT)pEvents.GetSize() : 0; nEvent < nEvents; nEvent++)
	{
		if ((pEventInfo = pEvents.GetAt(nEvent))) SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pEventInfo->GetName());
		continue;
	}
	return((SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CTPEPSettingsPrintJobsPage::ShowJobInfo()
{
	UINT  nStopCount;
	CString  szEvent;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CTimeSpan  tDailyTime;
	CTPEPPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		Timespinbox_SetTime(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME), (pJobInfo->GetPrintAtTime(tTime) || pJobInfo->GetPrintAtTime(tTime, tInterval) || pJobInfo->GetPrintAtTime(tTime, tInterval, nStopCount) || pJobInfo->GetPrintAtTime(tTime, tInterval, tStopTime)) ? tTime : CTime::GetCurrentTime().GetTime());
		Timespinbox_SetTime(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME), (pJobInfo->GetPrintAtDailyTime(tDailyTime) || pJobInfo->GetPrintAtDailyTime(tDailyTime, nStopCount) || pJobInfo->GetPrintAtDailyTime(tDailyTime, tStopTime)) ? CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + tDailyTime.GetTotalSeconds()) : CTime::GetCurrentTime().GetTime());
		SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_SETCURSEL, (pJobInfo->GetPrintAtEvent(szEvent)) ? (WPARAM)SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szEvent) : (WPARAM)-1);
		SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, (SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_TPEPSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS)) < 0 && (pJobInfo->GetPrintMode() & TPEP_PRINT_ATTIME)) ? CB_ADDSTRING : CB_FINDSTRING, (WPARAM)NULL, (LPARAM)STRING(IDS_TPEPSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS));
		SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, (SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_TPEPSETTINGS_PRINTJOBSPAGE_DAILYPRINTS)) < 0 && (pJobInfo->GetPrintMode() & TPEP_PRINT_ATDAILYTIME)) ? CB_ADDSTRING : CB_FINDSTRING, (WPARAM)NULL, (LPARAM)STRING(IDS_TPEPSETTINGS_PRINTJOBSPAGE_DAILYPRINTS));
		SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_SETCURSEL, ((pJobInfo->GetPrintMode() & TPEP_PRINT_ATTIME) || (pJobInfo->GetPrintMode() & TPEP_PRINT_ATDAILYTIME)) ? (WPARAM)SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)((pJobInfo->GetPrintMode() & TPEP_PRINT_ATTIME) ? STRING(IDS_TPEPSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS) : STRING(IDS_TPEPSETTINGS_PRINTJOBSPAGE_DAILYPRINTS))) : (WPARAM)-1);
		CheckDlgButton(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME, (pJobInfo->GetPrintMode() & TPEP_PRINT_ATTIME) ? TRUE : FALSE);
		CheckDlgButton(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME, (pJobInfo->GetPrintMode() & TPEP_PRINT_ATDAILYTIME) ? TRUE : FALSE);
		CheckDlgButton(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT, (pJobInfo->GetPrintMode() & TPEP_PRINT_ATEVENT) ? ((SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_GETCURSEL) >= 0) ? TRUE : FALSE) : FALSE);
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR)->EnableWindow();
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME)->EnableWindow();
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME));
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)->EnableWindow();
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT)->EnableWindow((SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT));
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT));
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		SetJobRepetitionInfo();
		return;
	}
	CheckDlgButton(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME, FALSE);
	CheckDlgButton(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME, FALSE);
	CheckDlgButton(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT, FALSE);
	CheckDlgButton(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME, FALSE);
	CheckDlgButton(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, FALSE);
	CheckDlgButton(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, FALSE);
	SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_SETCURSEL, (WPARAM)-1);
	SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_SETCURSEL, (WPARAM)-1);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow(FALSE);
}

BOOL CTPEPSettingsPrintJobsPage::CheckJobInfo() CONST
{
	UINT  nStopCount;
	CString  szEvent;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CTimeSpan  tDailyTime;
	CTPEPPrintJobInfo  *pJobInfo;

	return(((pJobInfo = FindJobInfo())) ? ((pJobInfo->GetPrintAtTime(tTime) && tTime > CTime::GetCurrentTime()) || pJobInfo->GetPrintAtTime(tTime, tInterval) || (pJobInfo->GetPrintAtTime(tTime, tInterval, nStopCount) && tTime.GetTime() + tInterval.GetTotalSeconds()*(TIMEKEY)nStopCount > CTime::GetCurrentTime().GetTime()) || (pJobInfo->GetPrintAtTime(tTime, tInterval, tStopTime) && tStopTime > CTime::GetCurrentTime()) || pJobInfo->GetPrintAtDailyTime(tDailyTime) || pJobInfo->GetPrintAtDailyTime(tDailyTime, nStopCount) || (pJobInfo->GetPrintAtDailyTime(tDailyTime, tStopTime) && tStopTime > CTime::GetCurrentTime()) || pJobInfo->GetPrintAtEvent(szEvent)) : FALSE);
}

CTPEPPrintJobInfo *CTPEPSettingsPrintJobsPage::FindJobInfo(BOOL bActive) CONST
{
	INT  nJob;
	INT  nJobs;
	CString  szJobName[2];
	CTPEPPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (INT)m_pJobs[0].GetSize(), szJobName[0] = Listbox_GetText(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS), (INT)GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS)->SendMessage(LB_GETCURSEL)), szJobName[1] = Listbox_GetText(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS), (INT)GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS)->SendMessage(LB_GETCURSEL)), szJobName[0] = (!bActive) ? szJobName[0] : szJobName[1]; nJob < nJobs; nJob++)
	{
		if ((pJobInfo = m_pJobs[0].GetAt(nJob)) && pJobInfo->GetName() == szJobName[0]) break;
		continue;
	}
	return((nJob < nJobs) ? pJobInfo : (CTPEPPrintJobInfo *)NULL);
}

VOID CTPEPSettingsPrintJobsPage::SetJobRepetitionInfo()
{
	UINT  nStopCount;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CTimeSpan  tDailyTime;
	CTPEPPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		Timespinbox_SetTime(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), ((GetJobRepetitionType() == TPEPSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  pJobInfo->GetPrintAtTime(tTime, tInterval, tStopTime)) || (GetJobRepetitionType() == TPEPSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  pJobInfo->GetPrintAtDailyTime(tDailyTime, tStopTime))) ? tStopTime : CTime::GetCurrentTime().GetTime());
		Spinbox_SetPos(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME), (pJobInfo->GetPrintAtTime(tTime, tInterval) || pJobInfo->GetPrintAtTime(tTime, tInterval, nStopCount) || pJobInfo->GetPrintAtTime(tTime, tInterval, tStopTime)) ? (tInterval.GetTotalSeconds() / SECONDSPERMINUTE) : 0);
		Spinbox_SetPos(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), ((GetJobRepetitionType() == TPEPSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  pJobInfo->GetPrintAtTime(tTime, tInterval, nStopCount)) || (GetJobRepetitionType() == TPEPSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  pJobInfo->GetPrintAtDailyTime(tDailyTime, nStopCount))) ? nStopCount : 0);
		CheckDlgButton(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME, (GetJobRepetitionType() == TPEPSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY && (pJobInfo->GetPrintMode() & TPEP_PRINT_REPEATBYINTERVAL)) ? TRUE : FALSE);
		CheckDlgButton(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, ((GetJobRepetitionType() == TPEPSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY && (pJobInfo->GetPrintMode() & TPEP_PRINT_REPEATSTOPBYCOUNT)) || (GetJobRepetitionType() == TPEPSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY && (pJobInfo->GetPrintMode() & TPEP_PRINT_DAILYREPEATSTOPBYCOUNT))) ? TRUE : FALSE);
		CheckDlgButton(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, ((GetJobRepetitionType() == TPEPSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY && (pJobInfo->GetPrintMode() & TPEP_PRINT_REPEATSTOPBYTIME)) || (GetJobRepetitionType() == TPEPSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY && (pJobInfo->GetPrintMode() & TPEP_PRINT_DAILYREPEATSTOPBYTIME))) ? TRUE : FALSE);
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)->EnableWindow((GetJobRepetitionType() == TPEPSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY) ? TRUE : FALSE);
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)->EnableWindow(GetJobRepetitionType() == TPEPSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC)->EnableWindow(GetJobRepetitionType() == TPEPSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC)->EnableWindow((IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && (GetJobRepetitionType() == TPEPSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY || IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)));
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)->EnableWindow((IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && (GetJobRepetitionType() == TPEPSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY || IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)));
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow((IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES));
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow((IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES));
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)->EnableWindow((IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && (GetJobRepetitionType() == TPEPSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY || IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)));
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow((IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME));
		return;
	}
	CheckDlgButton(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME, FALSE);
	CheckDlgButton(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, FALSE);
	CheckDlgButton(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow(FALSE);
}

UINT CTPEPSettingsPrintJobsPage::GetJobRepetitionType() CONST
{
	CString  szRepetitionType;

	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE)->GetWindowText(szRepetitionType);
	return((szRepetitionType == STRING(IDS_TPEPSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS) || szRepetitionType == STRING(IDS_TPEPSETTINGS_PRINTJOBSPAGE_DAILYPRINTS)) ? ((szRepetitionType == STRING(IDS_TPEPSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS)) ? TPEPSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY : TPEPSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY) : 0);
}

BOOL CTPEPSettingsPrintJobsPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? !m_pJobs[0].Compare(&m_pJobs[1]) : CLocalePropertyPage::IsModified()) : FALSE);
}

BOOL CTPEPSettingsPrintJobsPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? TRUE : CLocalePropertyPage::Check()) : TRUE);
}

void CTPEPSettingsPrintJobsPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTPEPSettingsPrintJobsPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTPEPSettingsPrintJobsPage::PostNcDestroy()
{
	m_pJobs[0].RemoveAll();
	m_pJobs[1].RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTPEPSettingsPrintJobsPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CTPEPSettingsPrintJobsPage)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ADDJOB, OnAddJob)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_PRINTJOBSPAGE_REMOVEJOB, OnRemoveJob)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME, OnPrintAtTime)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME, OnPrintAtDailyTime)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT, OnPrintAtEvent)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME, OnRepeatByTime)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, OnRepetitionStopByCopies)
	ON_BN_CLICKED(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, OnRepetitionStopByTime)
	ON_CBN_SELCHANGE(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, OnSelchangeEvent)
	ON_CBN_SELCHANGE(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, OnSelchangeRepetitionType)
	ON_LBN_SELCHANGE(IDC_TPEPSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, OnSelchangeDefinedJob)
	ON_LBN_SELCHANGE(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, OnSelchangeActiveJob)
	ON_CONTROL(SBXN_CHANGE, IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME, OnSpinchangeRepeatTime)
	ON_CONTROL(SBXN_CHANGE, IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES, OnSpinchangeRepetitionStopCopies)
	ON_CONTROL(TSBXN_CHANGE, IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME, OnSpinchangePrintTime)
	ON_CONTROL(TSBXN_CHANGE, IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME, OnSpinchangePrintDailyTime)
	ON_CONTROL(TSBXN_CHANGE, IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME, OnSpinchangeRepetitionStopTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTPEPSettingsPrintJobsPage message handlers

BOOL CTPEPSettingsPrintJobsPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	Spinbox_SetRange(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME), TPEPSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMINTERVAL, TPEPSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMINTERVAL);
	Spinbox_SetRange(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), TPEPSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES, TPEPSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES);
	EnumEvents();
	return TRUE;
}

BOOL CTPEPSettingsPrintJobsPage::OnSetActive()
{
	EnumJobs();
	return CLocalePropertyPage::OnSetActive();
}

BOOL CTPEPSettingsPrintJobsPage::OnKillActive()
{
	GetParentDialog()->OnDataExchange(GetSafeHwnd(), m_pJobs[0]);
	return CLocalePropertyPage::OnKillActive();
}

BOOL CTPEPSettingsPrintJobsPage::OnDataExchange(CONST CTPEPPrintJobs &pJobs)
{
	return m_pJobs[0].Copy(&pJobs);
}

void CTPEPSettingsPrintJobsPage::OnAddJob()
{
	CTPEPPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	if ((pJobInfo = FindJobInfo()))
	{
		pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() | TPEP_PRINT_ACTIVE);
		SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pJobInfo->GetName());
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS)->EnableWindow((SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow(FALSE);
	}
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsPrintJobsPage::OnRemoveJob()
{
	CTPEPPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	if ((pJobInfo = FindJobInfo(TRUE)))
	{
		for (pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~(TPEP_PRINT_ACTIVE | TPEP_PRINT_ATTIME | TPEP_PRINT_ATDAILYTIME | TPEP_PRINT_ATEVENT | TPEP_PRINT_REPEATBYINTERVAL | TPEP_PRINT_REPEATSTOPBYCOUNT | TPEP_PRINT_REPEATSTOPBYTIME | TPEP_PRINT_DAILYREPEATSTOPBYCOUNT | TPEP_PRINT_DAILYREPEATSTOPBYTIME)), SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCURSEL)); pJobInfo == FindJobInfo(); )
		{
			ShowJobInfo();
			break;
		}
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS)->EnableWindow((SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_REMOVEJOB)->EnableWindow(FALSE);
	}
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsPrintJobsPage::OnSelchangeDefinedJob()
{
	CTPEPPrintJobInfo  *pJobInfo;

	ShowJobInfo();
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow(((pJobInfo = FindJobInfo()) && SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
}

void CTPEPSettingsPrintJobsPage::OnSelchangeActiveJob()
{
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_REMOVEJOB)->EnableWindow();
}

void CTPEPSettingsPrintJobsPage::OnPrintAtTime()
{
	CTimeKey  tTime;
	CTPEPPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		if (IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME))
		{
			Timespinbox_SetTime(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME), (tTime = CTime::GetCurrentTime().GetTime() + SECONDSPERMINUTE*TPEPSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL));
			SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)STRING(IDS_TPEPSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS));
			pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | TPEP_PRINT_ATTIME) & ~(TPEP_PRINT_REPEATBYINTERVAL | TPEP_PRINT_REPEATSTOPBYCOUNT | TPEP_PRINT_REPEATSTOPBYTIME));
			pJobInfo->SetPrintAtTime(tTime);
		}
		else
		{
			SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_TPEPSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS)));
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~(TPEP_PRINT_ATTIME | TPEP_PRINT_REPEATBYINTERVAL | TPEP_PRINT_REPEATSTOPBYCOUNT | TPEP_PRINT_REPEATSTOPBYTIME));
		}
		SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_SETCURSEL, (IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) ? (WPARAM)SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)((IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME)) ? STRING(IDS_TPEPSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS) : STRING(IDS_TPEPSETTINGS_PRINTJOBSPAGE_DAILYPRINTS))) : (WPARAM)-1);
		Spinbox_SetRange(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), (IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME)) ? (TPEPSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES + 1) : TPEPSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES, TPEPSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES);
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME));
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		SetJobRepetitionInfo();
	}
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsPrintJobsPage::OnPrintAtDailyTime()
{
	CTimeKey  tTime;
	CTPEPPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		if (IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME))
		{
			Timespinbox_SetTime(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME), (tTime = CTime::GetCurrentTime().GetTime() + SECONDSPERMINUTE*TPEPSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL));
			SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)STRING(IDS_TPEPSETTINGS_PRINTJOBSPAGE_DAILYPRINTS));
			pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | TPEP_PRINT_ATDAILYTIME) & ~(TPEP_PRINT_DAILYREPEATSTOPBYCOUNT | TPEP_PRINT_DAILYREPEATSTOPBYTIME));
			pJobInfo->SetPrintAtDailyTime(tTime.GetTime() % SECONDSPERDAY);
		}
		else
		{
			SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_TPEPSETTINGS_PRINTJOBSPAGE_DAILYPRINTS)));
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~(TPEP_PRINT_ATDAILYTIME | TPEP_PRINT_DAILYREPEATSTOPBYCOUNT | TPEP_PRINT_DAILYREPEATSTOPBYTIME));
		}
		SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_SETCURSEL, (IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) ? (WPARAM)SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)((IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) ? STRING(IDS_TPEPSETTINGS_PRINTJOBSPAGE_DAILYPRINTS) : STRING(IDS_TPEPSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS))) : (WPARAM)-1);
		Spinbox_SetRange(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), (IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) ? TPEPSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES : (TPEPSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES + 1), TPEPSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES);
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		SetJobRepetitionInfo();
	}
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsPrintJobsPage::OnPrintAtEvent()
{
	CString  szEvent;
	CTPEPPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		if (IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT))
		{
			SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_SETCURSEL);
			GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT)->GetWindowText(szEvent);
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() | TPEP_PRINT_ATEVENT);
			pJobInfo->SetPrintAtEvent(szEvent);
		}
		else
		{
			SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_SETCURSEL, (WPARAM)-1);
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~TPEP_PRINT_ATEVENT);
			pJobInfo->SetPrintAtEvent(EMPTYSTRING);
		}
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT));
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT));
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsPrintJobsPage::OnSelchangeEvent()
{
	CString  szEvent;
	CTPEPPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT)->GetWindowText(szEvent);
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() | TPEP_PRINT_ATEVENT);
		pJobInfo->SetPrintAtEvent(szEvent);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsPrintJobsPage::OnSelchangeRepetitionType()
{
	Spinbox_SetRange(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), (GetJobRepetitionType() == TPEPSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY) ? (TPEPSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES + 1) : TPEPSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES, TPEPSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES);
	SetJobRepetitionInfo();
}

void CTPEPSettingsPrintJobsPage::OnRepeatByTime()
{
	CTPEPPrintJobInfo  *pJobInfo;

	for (CheckDlgButton(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME, !IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)); IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME); )
	{
		Spinbox_SetPos(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME), TPEPSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL);
		break;
	}
	for (; (pJobInfo = FindJobInfo()); )
	{
		if (IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME))
		{
			pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | TPEP_PRINT_REPEATBYINTERVAL) & ~(TPEP_PRINT_REPEATSTOPBYCOUNT | TPEP_PRINT_REPEATSTOPBYTIME));
			pJobInfo->SetPrintAtTime(Timespinbox_GetTime(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), SECONDSPERMINUTE*TPEPSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL);
			GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
			break;
		}
		pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~(TPEP_PRINT_REPEATBYINTERVAL | TPEP_PRINT_REPEATSTOPBYCOUNT | TPEP_PRINT_REPEATSTOPBYTIME));
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		break;
	}
	CheckDlgButton(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, FALSE);
	CheckDlgButton(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsPrintJobsPage::OnRepetitionStopByCopies()
{
	CTPEPPrintJobInfo  *pJobInfo;

	for (CheckDlgButton(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, !IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)), GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)), GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)); IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES); )
	{
		Spinbox_SetPos(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), TPEPSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTCOPIES);
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow(FALSE);
		CheckDlgButton(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, FALSE);
		break;
	}
	for (; (pJobInfo = FindJobInfo()); )
	{
		if (IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES))
		{
			if (GetJobRepetitionType() == TPEPSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY)
			{
				pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | TPEP_PRINT_REPEATSTOPBYCOUNT) & ~TPEP_PRINT_REPEATSTOPBYTIME);
				pJobInfo->SetPrintAtTime(Timespinbox_GetTime(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)), TPEPSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTCOPIES);
			}
			if (GetJobRepetitionType() == TPEPSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY)
			{
				pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | TPEP_PRINT_DAILYREPEATSTOPBYCOUNT) & ~TPEP_PRINT_DAILYREPEATSTOPBYTIME);
				pJobInfo->SetPrintAtDailyTime(Timespinbox_GetTime(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)).GetTime() % SECONDSPERDAY, TPEPSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTCOPIES);
			}
			GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
			break;
		}
		pJobInfo->SetPrintMode((GetJobRepetitionType() == TPEPSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY) ? (pJobInfo->GetPrintMode() & ~TPEP_PRINT_REPEATSTOPBYCOUNT) : (pJobInfo->GetPrintMode() & ~TPEP_PRINT_DAILYREPEATSTOPBYCOUNT));
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		break;
	}
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsPrintJobsPage::OnRepetitionStopByTime()
{
	CTimeKey  tStopTime;
	CTPEPPrintJobInfo  *pJobInfo;

	for (CheckDlgButton(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, !IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)), GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)); IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME); )
	{
		for (CheckDlgButton(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, FALSE); GetJobRepetitionType() == TPEPSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY; )
		{
			Timespinbox_SetTime(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)).GetTime() + SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME))));
			break;
		}
		if (GetJobRepetitionType() == TPEPSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY) Timespinbox_SetTime(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)).GetTime() + CTimeSpan(1, 0, 0, 0).GetTotalSeconds()));
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow(FALSE);
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow(FALSE);
		break;
	}
	for (; (pJobInfo = FindJobInfo()); )
	{
		if (IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME))
		{
			if (GetJobRepetitionType() == TPEPSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY)
			{
				pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | TPEP_PRINT_REPEATSTOPBYTIME) & ~TPEP_PRINT_REPEATSTOPBYCOUNT);
				pJobInfo->SetPrintAtTime(Timespinbox_GetTime(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)), tStopTime);
			}
			if (GetJobRepetitionType() == TPEPSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY)
			{
				pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | TPEP_PRINT_DAILYREPEATSTOPBYTIME) & ~TPEP_PRINT_DAILYREPEATSTOPBYCOUNT);
				pJobInfo->SetPrintAtDailyTime(Timespinbox_GetTime(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)).GetTime() % SECONDSPERDAY, tStopTime);
			}
			GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
			break;
		}
		pJobInfo->SetPrintMode((GetJobRepetitionType() == TPEPSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY) ? (pJobInfo->GetPrintMode() & ~TPEP_PRINT_REPEATSTOPBYTIME) : (pJobInfo->GetPrintMode() & ~TPEP_PRINT_DAILYREPEATSTOPBYTIME));
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		break;
	}
	GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsPrintJobsPage::OnSpinchangePrintTime()
{
	UINT  nStopCount;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeKey  tPrintTime;
	CTimeKey  tPrintStopTime;
	CTimeSpan  tPrintInterval;
	CTPEPPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)); pJobInfo->GetPrintAtTime(tPrintTime); )
		{
			pJobInfo->SetPrintAtTime(tTime);
			break;
		}
		if (pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval)) pJobInfo->SetPrintAtTime(tTime, tPrintInterval);
		if (pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, nStopCount)) pJobInfo->SetPrintAtTime(tTime, tPrintInterval, nStopCount);
		if (pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, tPrintStopTime)) pJobInfo->SetPrintAtTime(tTime, tPrintInterval, (tTime + tPrintInterval.GetTotalSeconds() > tPrintStopTime.GetTime()) ? CTimeKey(tTime.GetTime() + tPrintInterval.GetTotalSeconds()) : tPrintStopTime);
		Timespinbox_SetTime(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (GetJobRepetitionType() == TPEPSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)) ? ((tTime + tPrintInterval.GetTotalSeconds() > tPrintStopTime.GetTime()) ? (tTime.GetTime() + tPrintInterval.GetTotalSeconds()) : tPrintStopTime) : tStopTime);
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsPrintJobsPage::OnSpinchangePrintDailyTime()
{
	UINT  nStopCount;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeKey  tPrintStopTime;
	CTimeSpan  tPrintTime;
	CTPEPPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)), tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)); pJobInfo->GetPrintAtDailyTime(tPrintTime); )
		{
			pJobInfo->SetPrintAtDailyTime(tTime.GetTime() % SECONDSPERDAY);
			break;
		}
		if (pJobInfo->GetPrintAtDailyTime(tPrintTime, nStopCount)) pJobInfo->SetPrintAtDailyTime(tTime.GetTime() % SECONDSPERDAY, nStopCount);
		if (pJobInfo->GetPrintAtDailyTime(tPrintTime, tPrintStopTime)) pJobInfo->SetPrintAtDailyTime(tTime.GetTime() % SECONDSPERDAY, (SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + tTime.GetTime() % SECONDSPERDAY > tPrintStopTime.GetTime()) ? CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY + 1) + tTime.GetTime() % SECONDSPERDAY) : tPrintStopTime);
		Timespinbox_SetTime(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (GetJobRepetitionType() == TPEPSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)) ? ((SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + tTime.GetTime() % SECONDSPERDAY > tPrintStopTime.GetTime()) ? CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY + 1) + tTime.GetTime() % SECONDSPERDAY) : tPrintStopTime) : tStopTime);
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsPrintJobsPage::OnSpinchangeRepeatTime()
{
	UINT  nStopCount;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeKey  tPrintTime;
	CTimeKey  tPrintStopTime;
	CTimeSpan  tPrintInterval;
	CTPEPPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)); pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval); )
		{
			pJobInfo->SetPrintAtTime(tPrintTime, SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)));
			break;
		}
		if (pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, nStopCount)) pJobInfo->SetPrintAtTime(tPrintTime, SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)), nStopCount);
		if (pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, tPrintStopTime)) pJobInfo->SetPrintAtTime(tPrintTime, SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)), (tPrintTime.GetTime() + SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)) > tPrintStopTime.GetTime()) ? CTimeKey(tPrintTime.GetTime() + SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME))) : tPrintStopTime);
		Timespinbox_SetTime(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (GetJobRepetitionType() == TPEPSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  IsDlgButtonChecked(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)) ? ((tPrintTime.GetTime() + SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)) > tPrintStopTime.GetTime()) ? CTimeKey(tPrintTime.GetTime() + SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME))) : tPrintStopTime) : tStopTime);
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsPrintJobsPage::OnSpinchangeRepetitionStopCopies()
{
	UINT  nStopCount;
	UINT  nPrintStopCount;
	CTimeKey  tPrintTime;
	CTimeSpan  tPrintInterval;
	CTimeSpan  tPrintDailyTime;
	CTPEPPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (nStopCount = (UINT)Spinbox_GetPos(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)); GetJobRepetitionType() == TPEPSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY && pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, nPrintStopCount); )
		{
			pJobInfo->SetPrintAtTime(tPrintTime, tPrintInterval, nStopCount);
			break;
		}
		if (GetJobRepetitionType() == TPEPSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  pJobInfo->GetPrintAtDailyTime(tPrintDailyTime, nPrintStopCount)) pJobInfo->SetPrintAtDailyTime(tPrintDailyTime, nStopCount);
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPSettingsPrintJobsPage::OnSpinchangeRepetitionStopTime()
{
	CTimeKey  tTime;
	CTimeKey  tTimeKey;
	CTimeKey  tStopTime;
	CTimeKey  tPrintTime;
	CTimeKey  tPrintStopTime;
	CTimeSpan  tPrintInterval;
	CTimeSpan  tPrintDailyTime;
	CTPEPPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)); GetJobRepetitionType() == TPEPSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY && pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, tPrintStopTime); )
		{
			if (tTime > tStopTime.GetTime() - tPrintInterval.GetTotalSeconds()) Timespinbox_SetTime(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (tStopTime = tTime.GetTime() + tPrintInterval.GetTotalSeconds()));
			pJobInfo->SetPrintAtTime(tTime, tPrintInterval, tStopTime);
			break;
		}
		if (GetJobRepetitionType() == TPEPSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  pJobInfo->GetPrintAtDailyTime(tPrintDailyTime, tPrintStopTime))
		{
			if (SECONDSPERDAY*(tTimeKey.GetTime() / SECONDSPERDAY) + tPrintDailyTime.GetTotalSeconds() > tStopTime.GetTime()) Timespinbox_SetTime(GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (tStopTime = SECONDSPERDAY*(tTimeKey.GetTime() / SECONDSPERDAY) + tPrintDailyTime.GetTotalSeconds()));
			pJobInfo->SetPrintAtDailyTime(tPrintDailyTime, tStopTime);
		}
		GetDlgItem(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_TPEPSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CTPEPSettingsTabCtrl

IMPLEMENT_DYNCREATE(CTPEPSettingsTabCtrl, CTabCtrl)

BEGIN_MESSAGE_MAP(CTPEPSettingsTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CTPEPSettingsTabCtrl)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTPEPSettingsTabCtrl message handlers


/////////////////////////////////////////////////////////////////////////////
// CTPEPSettingsDialog

IMPLEMENT_DYNCREATE(CTPEPSettingsDialog, CDisplayPropertySheetDialog)

CTPEPSettingsDialog::CTPEPSettingsDialog() : CDisplayPropertySheetDialog()
{
	AddPage(&m_pageLayout);
	AddPage(&m_pageFiltering);
	AddPage(&m_pagePrinting);
	AddPage(&m_pagePrintJobs);
}

BOOL CTPEPSettingsDialog::GetLayoutColumns(CUIntArray &nColumns) CONST
{
	return m_pageLayout.GetLayout(nColumns);
}

BOOL CTPEPSettingsDialog::GetLayoutTitleFont(LPLOGFONT pTitleFont) CONST
{
	return m_pageLayout.GetTitleFont(pTitleFont);
}

BOOL CTPEPSettingsDialog::GetLayoutMessagesFont(LPLOGFONT pMessagesFont) CONST
{
	return m_pageLayout.GetMessagesFont(pMessagesFont);
}

BOOL CTPEPSettingsDialog::GetLayoutToolTipMode(BOOL &bEnable) CONST
{
	return m_pageLayout.GetToolTipMode(bEnable);
}

BOOL CTPEPSettingsDialog::IsLayoutModified() CONST
{
	return m_pageLayout.IsModified();
}

BOOL CTPEPSettingsDialog::GetFilterMode(UINT &nMode) CONST
{
	return m_pageFiltering.GetMode(nMode);
}

BOOL CTPEPSettingsDialog::GetFilterLimit(UINT &nLimit) CONST
{
	return m_pageFiltering.GetLimit(nLimit);
}

BOOL CTPEPSettingsDialog::GetFilterDigits(UINT &nDigits) CONST
{
	return m_pageFiltering.GetDigits(nDigits);
}

BOOL CTPEPSettingsDialog::GetFilterStatus(UINT &nStatus) CONST
{
	return m_pageFiltering.GetStatus(nStatus);
}

BOOL CTPEPSettingsDialog::GetFilterRange(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	return m_pageFiltering.GetRange(tStartTime, tStopTime);
}

BOOL CTPEPSettingsDialog::GetFilterDailyRange(CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST
{
	return m_pageFiltering.GetDailyRange(tStartTime, tStopTime);
}

BOOL CTPEPSettingsDialog::GetFilterPeriodicalRange(CTimeKey &tStartTime, CTimeSpan &tInterval, CTimeKey &tStopTime) CONST
{
	return m_pageFiltering.GetPeriodicalRange(tStartTime, tInterval, tStopTime);
}

BOOL CTPEPSettingsDialog::GetFilterColors(COLORREF &nColor, CUIntArray &nOOLColors) CONST
{
	return m_pageFiltering.GetColors(nColor, nOOLColors);
}

BOOL CTPEPSettingsDialog::IsFilteringModified() CONST
{
	return m_pageFiltering.IsModified();
}

BOOL CTPEPSettingsDialog::GetPrintJobs(CTPEPPrintJobs &pPrintJobs) CONST
{
	return(((GetActivePage()->GetSafeHwnd() != m_pagePrintJobs.GetSafeHwnd() && m_pagePrinting.GetJobs(pPrintJobs)) || (GetActivePage()->GetSafeHwnd() == m_pagePrintJobs.GetSafeHwnd() && m_pagePrintJobs.GetJobs(pPrintJobs))) ? TRUE : FALSE);
}

BOOL CTPEPSettingsDialog::IsPrintingModified() CONST
{
	return m_pagePrinting.IsModified() || m_pagePrintJobs.IsModified();
}

CTPEPOpenDialog *CTPEPSettingsDialog::GetParentDialog() CONST
{
	return((GetParent() != (CWnd *)GetParentDisplay()) ? (CTPEPOpenDialog *)GetParent() : (CTPEPOpenDialog *)NULL);
}

CTPEPWnd *CTPEPSettingsDialog::GetParentDisplay() CONST
{
	return((CTPEPWnd *)CDisplayPropertySheetDialog::GetParentDisplay());
}

BEGIN_MESSAGE_MAP(CTPEPSettingsDialog, CDisplayPropertySheetDialog)
	//{{AFX_MSG_MAP(CTPEPSettingsDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDHELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTPEPSettingsDialog message handlers

BOOL CTPEPSettingsDialog::OnInitDialog()
{
	INT  nPage;
	INT  nPages;
	CHourglassCursor  cCursor;

	CDisplayPropertySheetDialog::OnInitDialog();
	SetTitle(STRING(IDS_TPEPSETTINGSDIALOG_TITLE));
	for (nPage = 0, nPages = GetPageCount(), m_wndTabCtrl.SubclassWindow(GetTabControl()->GetSafeHwnd()); nPage < nPages; nPage++)
	{
		SetActivePage((nPage + 1) % nPages);
		continue;
	}
	m_wndTabCtrl.SetFocus();
	return FALSE;
}

BOOL CTPEPSettingsDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	CRect  rTab;
	CTPEPPrintJobs  pPrintJobs;
	LPNMHDR  pNotifyInfo = (LPNMHDR)lParam;

	if (pNotifyInfo->code == TCN_SELCHANGING)
	{
		if (HIBYTE(GetKeyState(VK_RIGHT)) && GetActivePage()->GetSafeHwnd() == m_pagePrinting.GetSafeHwnd() && m_pagePrinting.GetJobs(pPrintJobs) && pPrintJobs.GetSize() <= 1)
		{
			CAudioDevice::AlertBySound();
			*pResult = TRUE;
			return TRUE;
		}
		if (HIBYTE(GetKeyState(VK_LBUTTON)))
		{
			if (GetPrintJobs(pPrintJobs) && pPrintJobs.GetSize() <= 1)
			{
				if (GetTabControl()->GetItemRect(GetPageIndex(&m_pagePrintJobs), rTab))
				{
					GetTabControl()->ClientToScreen(rTab);
					if (rTab.PtInRect(GetCurrentMessage()->pt))
					{
						CAudioDevice::AlertBySound();
						*pResult = TRUE;
						return TRUE;
					}
				}
			}
		}
	}
	return CDisplayPropertySheetDialog::OnNotify(wParam, lParam, pResult);
}

BOOL CTPEPSettingsDialog::OnDataExchange(HWND hPage, CONST CTPEPPrintJobs &pJobs)
{
	return(((hPage == m_pagePrinting.GetSafeHwnd() && m_pagePrintJobs.OnDataExchange(pJobs)) || (hPage == m_pagePrintJobs.GetSafeHwnd() && m_pagePrinting.OnDataExchange(pJobs))) ? TRUE : FALSE);
}

void CTPEPSettingsDialog::OnOK()
{
	CHourglassCursor  cCursor;

	ReportEvent(((!GetParentDialog() && !GetParentDisplay()->OnCloseSettingsDialog(IDOK)) || (GetParentDialog() && !GetParentDialog()->OnCloseSettingsDialog(IDOK))) ? SYSTEM_WARNING_TPEP_SETUP_FAILURE : SYSTEM_NOERROR);
	CDisplayPropertySheetDialog::OnOK();
}

void CTPEPSettingsDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	if (!GetParentDialog()) GetParentDisplay()->OnCloseSettingsDialog(IDCANCEL);
	else  GetParentDialog()->OnCloseSettingsDialog(IDCANCEL);
	CDisplayPropertySheetDialog::OnCancel();
}

BOOL CTPEPSettingsDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TPEPSETTINGSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTPEPSettingsDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TPEPSETTINGSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTPEPConnectionDialog dialog

IMPLEMENT_DYNCREATE(CTPEPConnectionDialog, CDisplayDialog)

CTPEPConnectionDialog::CTPEPConnectionDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTPEPConnectionDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CTPEPConnectionDialog::Create(CWnd *pParentWnd, LPCTSTR pszComputer, CONST CTPEPConnection *pConnection, BOOL bConnection)
{
	INT  nResult;

	for (m_szComputer = pszComputer, m_bConnection = bConnection, m_cConnection.Copy(pConnection); (nResult = CDisplayDialog::Create(pParentWnd, CTPEPConnectionDialog::IDD)) == IDOK; ) break;
	return nResult;
}

CTPEPWnd *CTPEPConnectionDialog::GetParent() CONST
{
	return((CTPEPWnd *)CDisplayDialog::GetParent());
}

BOOL CTPEPConnectionDialog::ShowConnectionInfo()
{
	INT  nItem;
	INT  nItems;
	INT  nColumn;
	INT  nColumns;
	UINT  nType;
	UINT  nSpeed;
	UINT  nDataMode;
	UINT  nDataLink;
	UINT  nDataType;
	UINT  nTriggerMode;
	CString  szItem;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CStringArray  szPackets;
	CStringArray  szParameters;
	CComputerToken  cComputerToken;
	CDatabaseTMPacket  *pDatabaseTMPacket;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	if (m_cConnection.IsInitialized())
	{
		for (nItem = 0, nItems = m_cConnection.GetPackets(szPackets), nType = m_cConnection.GetType(), nDataMode = m_cConnection.GetDataMode(), nDataLink = m_cConnection.GetDataLink(), nDataType = m_cConnection.GetDataType(), nTriggerMode = m_cConnection.GetTriggerMode(), tStartTime = m_cConnection.GetRetrieveStartTime(), tStopTime = m_cConnection.GetRetrieveStopTime(), nSpeed = m_cConnection.GetRetrieveSpeed(), SendDlgItemMessage(IDC_TPEP_CONNECTION_PROPERTIES_CONTENTS, LVM_DELETEALLITEMS); nItem < nItems; nItem++)
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TPEPCONNECTIONDIALOG_CONTENTS_ID); )
				{
					szItem = szPackets.GetAt(nItem);
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TPEPCONNECTIONDIALOG_CONTENTS_DESCRIPTION); )
				{
					for (szItem.Empty(); (pDatabaseTMPacket = GetDatabase()->GetTMPackets()->GetAt(GetDatabase()->GetTMPackets()->Find(szPackets.GetAt(nItem)))); )
					{
						szItem = pDatabaseTMPacket->GetDescription();
						break;
					}
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_CONTENTS), nItem, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_CONTENTS), nItem, nColumn, szItem);
			}
		}
		for (nItem = 0, nItems = m_cConnection.GetParameters(szParameters); nItem < nItems; nItem++)
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TPEPCONNECTIONDIALOG_CONTENTS_ID); )
				{
					szItem = szParameters.GetAt(nItem);
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TPEPCONNECTIONDIALOG_CONTENTS_DESCRIPTION); )
				{
					for (szItem.Empty(); (pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(szParameters.GetAt(nItem)))); )
					{
						szItem = pDatabaseTMParameter->GetDescription();
						break;
					}
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_CONTENTS), nItem, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_CONTENTS), nItem, nColumn, szItem);
			}
		}
		if (SendDlgItemMessage(IDC_TPEP_CONNECTION_PROPERTIES_CONTENTS, LVM_GETITEMCOUNT) > 0)
		{
			Listview_SetCurText(GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_CONTENTS), 0);
			SendDlgItemMessage(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_SPEED, TBM_SETPOS, TRUE, nSpeed);
			CheckDlgButton(IDC_TPEP_CONNECTION_PROPERTIES_LINKTYPE_HOT, (nDataLink == TPEP_DATALINK_HOT) ? TRUE : FALSE);
			CheckDlgButton(IDC_TPEP_CONNECTION_PROPERTIES_LINKTYPE_COLD, (nDataLink == TPEP_DATALINK_COLD) ? TRUE : FALSE);
			CheckDlgButton(IDC_TPEP_CONNECTION_PROPERTIES_DATATYPE_RAW, (nDataType == TPEP_DATATYPE_RAW) ? TRUE : FALSE);
			CheckDlgButton(IDC_TPEP_CONNECTION_PROPERTIES_DATATYPE_PIE, (nDataType != TPEP_DATATYPE_RAW) ? TRUE : FALSE);
			CheckDlgButton(IDC_TPEP_CONNECTION_PROPERTIES_TRIGGERMODE_UPDATE, (nTriggerMode == TPEP_TRIGGERMODE_UPDATE) ? TRUE : FALSE);
			CheckDlgButton(IDC_TPEP_CONNECTION_PROPERTIES_TRIGGERMODE_CHANGE, (nTriggerMode == TPEP_TRIGGERMODE_CHANGE) ? TRUE : FALSE);
			CheckDlgButton(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_REALTIME, (nDataMode == TPEP_DATAMODE_REALTIME) ? TRUE : FALSE);
			CheckDlgButton(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_RANDOM, (nDataMode == TPEP_DATAMODE_RANDOM) ? TRUE : FALSE);
			CheckDlgButton(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_HISTORICAL, (nDataMode == TPEP_DATAMODE_HISTORY) ? TRUE : FALSE);
			SetDlgItemInt(IDC_TPEP_CONNECTION_PROPERTIES_DATATYPE_PIE_NUMBER, nDataType);
			GetDlgItem(IDC_TPEP_CONNECTION_SERVER)->SetWindowText((m_bConnection) ? m_szComputer : cComputerToken.GetComputerName());
			GetDlgItem(IDC_TPEP_CONNECTION_CLIENT)->SetWindowText((m_bConnection) ? cComputerToken.GetComputerName() : m_szComputer);
			GetDlgItem(IDC_TPEP_CONNECTION_DETAILS)->EnableWindow();
			GetDlgItem(IDC_TPEP_CONNECTION_SERVER_STATIC)->EnableWindow();
			GetDlgItem(IDC_TPEP_CONNECTION_SERVER)->EnableWindow();
			GetDlgItem(IDC_TPEP_CONNECTION_CLIENT_STATIC)->EnableWindow();
			GetDlgItem(IDC_TPEP_CONNECTION_CLIENT)->EnableWindow();
			GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES)->EnableWindow();
			GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_CONTENTS_STATIC)->EnableWindow();
			GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_CONTENTS_PACKETS)->ShowWindow((nType == TPEP_TYPE_PACKETS) ? SW_SHOW : SW_HIDE);
			GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_CONTENTS_PACKETS)->EnableWindow((nType == TPEP_TYPE_PACKETS) ? TRUE : FALSE);
			GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_CONTENTS_PARAMETERS)->ShowWindow((nType == TPEP_TYPE_PARAMETERS) ? SW_SHOW : SW_HIDE);
			GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_CONTENTS_PARAMETERS)->EnableWindow((nType == TPEP_TYPE_PARAMETERS) ? TRUE : FALSE);
			GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_CONTENTS)->EnableWindow();
			GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_LINKTYPE_STATIC)->EnableWindow();
			GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_LINKTYPE_HOT)->EnableWindow();
			GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_LINKTYPE_COLD)->EnableWindow();
			GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATATYPE_STATIC)->EnableWindow();
			GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATATYPE_RAW)->EnableWindow();
			GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATATYPE_PIE)->EnableWindow();
			GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATATYPE_PIE_NUMBER)->ShowWindow((nDataType != TPEP_DATATYPE_RAW) ? SW_SHOW : SW_HIDE);
			GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATATYPE_PIE_NUMBER)->EnableWindow((nDataType != TPEP_DATATYPE_RAW) ? TRUE : FALSE);
			GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_TRIGGERMODE_STATIC)->EnableWindow();
			GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_TRIGGERMODE_UPDATE)->EnableWindow();
			GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_TRIGGERMODE_CHANGE)->EnableWindow();
			GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_STATIC)->EnableWindow();
			GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_REALTIME)->EnableWindow();
			GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_RANDOM)->EnableWindow();
			GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_HISTORICAL)->EnableWindow();
			GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_STARTTIME_STATIC)->ShowWindow((nDataMode == TPEP_DATAMODE_HISTORY) ? SW_SHOW : SW_HIDE);
			GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_STARTTIME_STATIC)->EnableWindow((nDataMode == TPEP_DATAMODE_HISTORY) ? TRUE : FALSE);
			GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_STARTTIME)->ShowWindow((nDataMode == TPEP_DATAMODE_HISTORY) ? SW_SHOW : SW_HIDE);
			GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_STARTTIME)->EnableWindow((nDataMode == TPEP_DATAMODE_HISTORY) ? TRUE : FALSE);
			GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_STARTTIME)->SetWindowText((nDataMode == TPEP_DATAMODE_HISTORY) ? (LPCTSTR)tStartTime.FormatGmt() : EMPTYSTRING);
			GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_STOPTIME_STATIC)->ShowWindow((nDataMode == TPEP_DATAMODE_HISTORY) ? SW_SHOW : SW_HIDE);
			GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_STOPTIME_STATIC)->EnableWindow((nDataMode == TPEP_DATAMODE_HISTORY) ? TRUE : FALSE);
			GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_STOPTIME)->ShowWindow((nDataMode == TPEP_DATAMODE_HISTORY) ? SW_SHOW : SW_HIDE);
			GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_STOPTIME)->EnableWindow((nDataMode == TPEP_DATAMODE_HISTORY) ? TRUE : FALSE);
			GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_STOPTIME)->SetWindowText((nDataMode == TPEP_DATAMODE_HISTORY) ? (LPCTSTR)tStopTime.FormatGmt() : EMPTYSTRING);
			GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_SPEED_STATIC)->EnableWindow((nDataMode == TPEP_DATAMODE_HISTORY) ? TRUE : FALSE);
			GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_SPEED)->EnableWindow((nDataMode == TPEP_DATAMODE_HISTORY) ? TRUE : FALSE);
			return TRUE;
		}
	}
	SendDlgItemMessage(IDC_TPEP_CONNECTION_PROPERTIES_CONTENTS, LVM_DELETEALLITEMS);
	SendDlgItemMessage(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_SPEED, TBM_SETPOS, TRUE);
	CheckDlgButton(IDC_TPEP_CONNECTION_PROPERTIES_LINKTYPE_HOT, FALSE);
	CheckDlgButton(IDC_TPEP_CONNECTION_PROPERTIES_LINKTYPE_COLD, FALSE);
	CheckDlgButton(IDC_TPEP_CONNECTION_PROPERTIES_DATATYPE_RAW, FALSE);
	CheckDlgButton(IDC_TPEP_CONNECTION_PROPERTIES_DATATYPE_PIE, FALSE);
	CheckDlgButton(IDC_TPEP_CONNECTION_PROPERTIES_TRIGGERMODE_UPDATE, FALSE);
	CheckDlgButton(IDC_TPEP_CONNECTION_PROPERTIES_TRIGGERMODE_CHANGE, FALSE);
	CheckDlgButton(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_REALTIME, FALSE);
	CheckDlgButton(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_RANDOM, FALSE);
	CheckDlgButton(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_HISTORICAL, FALSE);
	GetDlgItem(IDC_TPEP_CONNECTION_SERVER)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TPEP_CONNECTION_CLIENT)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TPEP_CONNECTION_DETAILS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_CONNECTION_SERVER_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_CONNECTION_SERVER)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_CONNECTION_CLIENT_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_CONNECTION_CLIENT)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_CONTENTS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_CONTENTS_PACKETS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_CONTENTS_PACKETS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_CONTENTS_PARAMETERS)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_CONTENTS_PARAMETERS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_CONTENTS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_LINKTYPE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_LINKTYPE_HOT)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_LINKTYPE_COLD)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATATYPE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATATYPE_RAW)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATATYPE_PIE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATATYPE_PIE_NUMBER)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATATYPE_PIE_NUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATATYPE_PIE_NUMBER)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_TRIGGERMODE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_TRIGGERMODE_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_TRIGGERMODE_CHANGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_REALTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_RANDOM)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_HISTORICAL)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_STARTTIME_STATIC)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_STARTTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_STARTTIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_STARTTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_STARTTIME)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_STOPTIME_STATIC)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_STOPTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_STOPTIME)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_STOPTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_STOPTIME)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_SPEED_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_SPEED)->EnableWindow(FALSE);
	return FALSE;
}

INT CTPEPConnectionDialog::CalcColumnExtent(LPCTSTR pszColumn)
{
	CDC  *pDC;
	CFont  *pOldFont;
	CSize  sizeColumn;

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(GetFont())))
		{
			sizeColumn = pDC->GetTextExtent(pszColumn);
			sizeColumn.cx += 8 * GetSystemMetrics(SM_CXEDGE);
			pDC->SelectObject(pOldFont);
			ReleaseDC(pDC);
			return sizeColumn.cx;
		}
		ReleaseDC(pDC);
	}
	return 0;
}

BOOL CTPEPConnectionDialog::Check(BOOL bModified) CONST
{
	return m_cConnection.IsInitialized();
}

void CTPEPConnectionDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTPEPConnectionDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTPEPConnectionDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTPEPConnectionDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTPEPConnectionDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TPEP_CONNECTION_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTPEPConnectionDialog message handlers

BOOL CTPEPConnectionDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CString  szMessages;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	AccessControl(IDC_TPEP_CONNECTION_PROPERTIES_LINKTYPE_HOT, FALSE);
	AccessControl(IDC_TPEP_CONNECTION_PROPERTIES_LINKTYPE_COLD, FALSE);
	AccessControl(IDC_TPEP_CONNECTION_PROPERTIES_DATATYPE_RAW, FALSE);
	AccessControl(IDC_TPEP_CONNECTION_PROPERTIES_DATATYPE_PIE, FALSE);
	AccessControl(IDC_TPEP_CONNECTION_PROPERTIES_TRIGGERMODE_UPDATE, FALSE);
	AccessControl(IDC_TPEP_CONNECTION_PROPERTIES_TRIGGERMODE_CHANGE, FALSE);
	AccessControl(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_REALTIME, FALSE);
	AccessControl(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_RANDOM, FALSE);
	AccessControl(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_HISTORICAL, FALSE);
	AccessControl(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_SPEED, FALSE);
	m_szColumns.Add(STRING(IDS_TPEPCONNECTIONDIALOG_CONTENTS_ID));
	m_szColumns.Add(STRING(IDS_TPEPCONNECTIONDIALOG_CONTENTS_DESCRIPTION));
	GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_CONTENTS)->GetClientRect(rColumns);
	SendDlgItemMessage(IDC_TPEP_CONNECTION_PROPERTIES_CONTENTS, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	SendDlgItemMessage(IDC_TPEP_CONNECTION_PROPERTIES_DATAMODE_SPEED, TBM_SETRANGE, TRUE, MAKELPARAM(TPEP_RETRIEVESPEED_MINIMUM, TPEP_RETRIEVESPEED_MAXIMUM));
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = rColumns.Width() / 6; nColumn < nColumns; nWidth = (++nColumn < nColumns) ? ((5 * rColumns.Width()) / 6) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TPEP_CONNECTION_PROPERTIES_CONTENTS), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	ShowConnectionInfo();
	GetDlgItem(IDOK)->EnableWindow(Check());
	return TRUE;
}

void CTPEPConnectionDialog::OnOK()
{
	CHourglassCursor  cCursor;

	EndDialog(IDOK);
}

BOOL CTPEPConnectionDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TPEPCONNECTIONDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTPEPConnectionDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TPEPCONNECTIONDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTPEPParametersCalibrationPage property page

IMPLEMENT_DYNCREATE(CTPEPParametersCalibrationPage, CLocalePropertyPage)

CTPEPParametersCalibrationPage::CTPEPParametersCalibrationPage() : CLocalePropertyPage(CTPEPParametersCalibrationPage::IDD)
{
	//{{AFX_DATA_INIT(CTPEPParametersCalibrationPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

VOID CTPEPParametersCalibrationPage::ShowParameterInfo(LPCTSTR pszParameter)
{
	INT  nTable;
	INT  nTables;
	CString  szName;
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CDatabaseTMNumCalTable  *pDatabaseTMNumCalTable;
	CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;

	for (SendDlgItemMessage(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_NAME, CB_RESETCONTENT); (pDatabaseTMParameter = (pszParameter != (LPCTSTR)NULL) ? GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pszParameter)) : (CDatabaseTMParameter *)NULL); )
	{
		for (nTable = 0, nTables = pDatabaseTMParameter->GetCalTableRefs(m_nCalTableRefs, m_nCalValidityRefs); nTable < nTables; nTable++)
		{
			if ((m_nCalTableType = (pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS))) == TMPARAMETER_CALIBRATION_NUMERICAL)
			{
				if ((pDatabaseTMNumCalTable = GetDatabase()->GetTMNumCalTables()->GetAt(m_nCalTableRefs.GetAt(nTable))) != (CDatabaseTMNumCalTable *)NULL)
				{
					for (szName.Format(STRING(IDS_TPEPPARAMETERS_CALIBRATIONPAGE_TABLE_FORMAT), (LPCTSTR)pDatabaseTMNumCalTable->GetDescription(), (LPCTSTR)pDatabaseTMNumCalTable->GetName()); pDatabaseTMNumCalTable->GetDescription().IsEmpty(); )
					{
						szName = pDatabaseTMNumCalTable->GetName();
						break;
					}
					SendDlgItemMessage(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_NAME, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szName);
					continue;
				}
			}
			if (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS)
			{
				if ((pDatabaseTMTxtCalTable = GetDatabase()->GetTMTxtCalTables()->GetAt(m_nCalTableRefs.GetAt(nTable))))
				{
					for (szName.Format(STRING(IDS_TPEPPARAMETERS_CALIBRATIONPAGE_TABLE_FORMAT), (LPCTSTR)pDatabaseTMTxtCalTable->GetDescription(), (LPCTSTR)pDatabaseTMTxtCalTable->GetName()); pDatabaseTMTxtCalTable->GetDescription().IsEmpty(); )
					{
						szName = pDatabaseTMTxtCalTable->GetName();
						break;
					}
					SendDlgItemMessage(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_NAME, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szName);
					continue;
				}
			}
		}
		break;
	}
	SendDlgItemMessage(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_NAME, CB_SETCURSEL);
	GetDlgItem(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_NAME_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_NAME)->EnableWindow((SendDlgItemMessage(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	ShowCalibrationInfo();
}

VOID CTPEPParametersCalibrationPage::ShowCalibrationInfo()
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	INT  nColumn;
	INT  nColumns;
	double  fCalPtX;
	double  fCalPtY;
	CString  szItem;
	CString  szCalPtX;
	CString  szCalPtY;
	CString  szCalText;
	CStringTools  cStringTools;
	CDatabaseTMNumCalTable  *pDatabaseTMNumCalTable;
	CDatabaseTMNumCalPoint  *pDatabaseTMNumCalPoint;
	CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;
	CDatabaseTMTxtCalPoint  *pDatabaseTMTxtCalPoint;

	SendDlgItemMessage(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_POINTS, LVM_DELETEALLITEMS);
	if ((nIndex = (INT)SendDlgItemMessage(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_NAME, CB_GETCURSEL)) >= 0 && nIndex < m_nCalTableRefs.GetSize())
	{
		if ((pDatabaseTMNumCalTable = (m_nCalTableType == TMPARAMETER_CALIBRATION_NUMERICAL) ? GetDatabase()->GetTMNumCalTables()->GetAt(m_nCalTableRefs.GetAt(nIndex)) : (CDatabaseTMNumCalTable *)NULL))
		{
			for (nItem = 0, nItems = (INT)pDatabaseTMNumCalTable->GetSize(); nItem < nItems; nItem++)
			{
				if ((pDatabaseTMNumCalPoint = pDatabaseTMNumCalTable->GetAt(nItem)))
				{
					for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn = nColumn + 1)
					{
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TPEPPARAMETERS_CALIBRATIONPAGE_TITLEITEM_NUMBER); )
						{
							szItem = cStringTools.ConvertIntToString(nItem + 1);
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TPEPPARAMETERS_CALIBRATIONPAGE_TITLEITEM_X); )
						{
							szItem = cStringTools.ConvertFloatToTruncatedString(pDatabaseTMNumCalPoint->GetX());
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TPEPPARAMETERS_CALIBRATIONPAGE_TITLEITEM_Y); )
						{
							szItem = cStringTools.ConvertFloatToString(pDatabaseTMNumCalPoint->GetY());
							break;
						}
						if (!nColumn)
						{
							Listview_InsertText(GetDlgItem(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_POINTS), nItem, szItem);
							continue;
						}
						Listview_SetText(GetDlgItem(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_POINTS), nItem, nColumn, szItem);
					}
				}
			}
			GetDlgItem(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_ID)->SetWindowText(pDatabaseTMNumCalTable->GetName());
			GetDlgItem(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_TYPE)->SetWindowText(STRING(IDS_TPEPPARAMETERS_CALIBRATIONPAGE_TYPE_NUMERICAL));
			GetDlgItem(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_ID_STATIC)->EnableWindow((GetDlgItem(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_ID)->EnableWindow((GetDlgItem(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_POINTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_POINTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_POINTS)->EnableWindow((SendDlgItemMessage(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_POINTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_TYPE_STATIC)->EnableWindow();
			GetDlgItem(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_TYPE)->EnableWindow();
			return;
		}
		if ((pDatabaseTMTxtCalTable = (m_nCalTableType == TMPARAMETER_CALIBRATION_STATUS) ? GetDatabase()->GetTMTxtCalTables()->GetAt(m_nCalTableRefs.GetAt(nIndex)) : (CDatabaseTMTxtCalTable *)NULL))
		{
			for (nItem = 0, nItems = (INT)pDatabaseTMTxtCalTable->GetSize(); nItem < nItems; nItem++)
			{
				if ((pDatabaseTMTxtCalPoint = pDatabaseTMTxtCalTable->GetAt(nItem)))
				{
					for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn = nColumn + 1)
					{
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TPEPPARAMETERS_CALIBRATIONPAGE_TITLEITEM_NUMBER); )
						{
							szItem = cStringTools.ConvertIntToString(nItem + 1);
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TPEPPARAMETERS_CALIBRATIONPAGE_TITLEITEM_X); )
						{
							if (pDatabaseTMTxtCalPoint->GetRange(fCalPtX, fCalPtY, szCalText) || pDatabaseTMTxtCalPoint->GetPoint(fCalPtX, szCalText))
							{
								for (szCalPtX = szItem = cStringTools.ConvertFloatToTruncatedString(fCalPtX, -1), szCalPtY = cStringTools.ConvertFloatToTruncatedString(fCalPtY, -1); fCalPtX != fCalPtY; )
								{
									szItem.Format(STRING(IDS_TPEPPARAMETERS_CALIBRATIONPAGE_POINT_RANGE), (LPCTSTR)szCalPtX, (LPCTSTR)szCalPtY);
									break;
								}
								break;
							}
							szItem.Empty();
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TPEPPARAMETERS_CALIBRATIONPAGE_TITLEITEM_Y); )
						{
							szItem = (pDatabaseTMTxtCalPoint->GetPoint(fCalPtX, szCalText) || pDatabaseTMTxtCalPoint->GetRange(fCalPtX, fCalPtY, szCalText)) ? (LPCTSTR)szCalText : EMPTYSTRING;
							break;
						}
						if (!nColumn)
						{
							Listview_InsertText(GetDlgItem(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_POINTS), nItem, szItem);
							continue;
						}
						Listview_SetText(GetDlgItem(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_POINTS), nItem, nColumn, szItem);
					}
				}
			}
			GetDlgItem(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_ID)->SetWindowText(pDatabaseTMTxtCalTable->GetName());
			GetDlgItem(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_TYPE)->SetWindowText(STRING(IDS_TPEPPARAMETERS_CALIBRATIONPAGE_TYPE_STATUS));
			GetDlgItem(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_ID_STATIC)->EnableWindow((GetDlgItem(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_ID)->EnableWindow((GetDlgItem(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_POINTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_POINTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_POINTS)->EnableWindow((SendDlgItemMessage(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_POINTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_TYPE_STATIC)->EnableWindow();
			GetDlgItem(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_TYPE)->EnableWindow();
			return;
		}
	}
	SendDlgItemMessage(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_POINTS, LVM_DELETEALLITEMS);
	GetDlgItem(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_ID)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_TYPE)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_ID_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_ID)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_TYPE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_TYPE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_POINTS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_POINTS)->EnableWindow(FALSE);
}

void CTPEPParametersCalibrationPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTPEPParametersCalibrationPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTPEPParametersCalibrationPage::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_nCalTableRefs.RemoveAll();
	m_nCalValidityRefs.RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTPEPParametersCalibrationPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CTPEPParametersCalibrationPage)
	ON_CBN_SELCHANGE(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_NAME, OnSelchangeName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTPEPParametersCalibrationPage message handlers

BOOL CTPEPParametersCalibrationPage::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	m_szColumns.Add(STRING(IDS_TPEPPARAMETERS_CALIBRATIONPAGE_TITLEITEM_NUMBER));
	m_szColumns.Add(STRING(IDS_TPEPPARAMETERS_CALIBRATIONPAGE_TITLEITEM_X));
	m_szColumns.Add(STRING(IDS_TPEPPARAMETERS_CALIBRATIONPAGE_TITLEITEM_Y));
	GetDlgItem(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_POINTS)->GetClientRect(rColumns);
	SendDlgItemMessage(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_POINTS, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = rColumns.Width() / 5; nColumn < nColumns; nWidth = (++nColumn < nColumns) ? ((2 * rColumns.Width()) / 5) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TPEP_PARAMETERS_CALIBRATIONPAGE_POINTS), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	return TRUE;
}

void CTPEPParametersCalibrationPage::OnSelchangeName()
{
	ShowCalibrationInfo();
}


/////////////////////////////////////////////////////////////////////////////
// CTPEPParametersFolderTabCtrl

IMPLEMENT_DYNCREATE(CTPEPParametersFolderTabCtrl, CTabCtrl)

CTPEPParametersFolder *CTPEPParametersFolderTabCtrl::GetParent() CONST
{
	return((CTPEPParametersFolder *)CTabCtrl::GetParent());
}

BEGIN_MESSAGE_MAP(CTPEPParametersFolderTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CTPEPParametersFolderTabCtrl)
	ON_WM_GETDLGCODE()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTPEPParametersFolderTabCtrl message handlers

UINT CTPEPParametersFolderTabCtrl::OnGetDlgCode()
{
	return CTabCtrl::OnGetDlgCode() | DLGC_WANTTAB;
}

void CTPEPParametersFolderTabCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CWnd  *pWnd;

	if (nChar == VK_TAB)
	{
		if ((pWnd = GetParent()->GetParent()->GetNextDlgTabItem(GetParent(), (HIBYTE(GetKeyState(VK_SHIFT))) ? TRUE : FALSE)))
		{
			pWnd->SetFocus();
			return;
		}
	}
	if (nChar == VK_DOWN)
	{
		if ((pWnd = GetParent()->GetActivePage()->GetNextDlgTabItem((CWnd *)NULL)))
		{
			pWnd->SetFocus();
			return;
		}
	}
	CTabCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}


/////////////////////////////////////////////////////////////////////////////
// CTPEPParametersFolder

IMPLEMENT_DYNCREATE(CTPEPParametersFolder, CLocalePropertySheetDialog)

CTPEPParametersFolder::CTPEPParametersFolder() : CLocalePropertySheetDialog()
{
	AddPage(&m_pageCalibration);
}

BOOL CTPEPParametersFolder::Create(CWnd *pParentWnd, CONST RECT &rect)
{
	INT  nIndex;

	if (CLocalePropertySheetDialog::Create(pParentWnd, WS_CHILD | WS_TABSTOP | WS_DISABLED))
	{
		for (nIndex = GetPageCount() - 1, m_wndTabCtrl.SubclassWindow(GetTabControl()->GetSafeHwnd()); nIndex >= 0; nIndex--)
		{
			SetActivePage(nIndex);
			continue;
		}
		MoveWindow(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
		ShowWindow(SW_SHOWNORMAL);
		return TRUE;
	}
	return FALSE;
}

VOID CTPEPParametersFolder::ShowParameterInfo(LPCTSTR pszParameter)
{
	m_pageCalibration.ShowParameterInfo(pszParameter);
}

CTPEPParametersDialog *CTPEPParametersFolder::GetParentDialog() CONST
{
	return((CTPEPParametersDialog *)CLocalePropertySheetDialog::GetParent());
}

CTPEPWnd *CTPEPParametersFolder::GetParentDisplay() CONST
{
	return((CTPEPWnd *)GetParentDialog()->GetParent());
}

BEGIN_MESSAGE_MAP(CTPEPParametersFolder, CLocalePropertySheetDialog)
	//{{AFX_MSG_MAP(CTPEPParametersFolder)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTPEPParametersFolder message handlers

void CTPEPParametersFolder::OnSetFocus(CWnd *pOldWnd)
{
	if (IsWindow(m_wndTabCtrl.GetSafeHwnd()))
	{
		m_wndTabCtrl.SetFocus();
		return;
	}
	CLocalePropertySheetDialog::OnSetFocus(pOldWnd);
}


/////////////////////////////////////////////////////////////////////////////
// CTPEPParametersDialog dialog

IMPLEMENT_DYNCREATE(CTPEPParametersDialog, CDisplayDialog)

CTPEPParametersDialog::CTPEPParametersDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTPEPParametersDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CTPEPParametersDialog::Create(CWnd *pParentWnd)
{
	return Create(pParentWnd, EMPTYSTRING);
}
INT CTPEPParametersDialog::Create(CWnd *pParentWnd, LPCTSTR pszParameter)
{
	m_szParameter = pszParameter;
	return CDisplayDialog::Create(pParentWnd, CTPEPParametersDialog::IDD);
}

CTPEPWnd *CTPEPParametersDialog::GetParent() CONST
{
	return((CTPEPWnd *)CDisplayDialog::GetParent());
}

BOOL CTPEPParametersDialog::EnumParameters()
{
	INT  nParameter;
	INT  nParameters;
	CString  szParameter;
	CStringArray  szParameters;
	CTPEPConnection  cConnection;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	for (nParameter = 0, nParameters = (GetParent()->GetConnectionProperties(&cConnection)) ? cConnection.GetParameters(szParameters) : -1; nParameter < nParameters; nParameter++)
	{
		if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(szParameters.GetAt(nParameter)))))
		{
			szParameter.Format(STRING(IDS_TPEPPARAMETERSDIALOG_PARAMETERFORMAT), (LPCTSTR)pDatabaseTMParameter->GetTag(), (LPCTSTR)pDatabaseTMParameter->GetDescription());
			SendDlgItemMessage(IDC_TPEP_PARAMETERS_ITEM, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szParameter);
		}
	}
	SendDlgItemMessage(IDC_TPEP_PARAMETERS_ITEM, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_TPEP_PARAMETERS_ITEM, CB_FINDSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)m_szParameter), 0));
	GetDlgItem(IDC_TPEP_PARAMETERS_DETAILS)->EnableWindow((SendDlgItemMessage(IDC_TPEP_PARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEP_PARAMETERS_ITEM_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TPEP_PARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEP_PARAMETERS_ITEM)->EnableWindow((SendDlgItemMessage(IDC_TPEP_PARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	m_wndFolderCtrl.EnableWindow((SendDlgItemMessage(IDC_TPEP_PARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_TPEP_PARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CTPEPParametersDialog::ShowParameterInfo()
{
	INT  nParameter;
	INT  nParameters;
	CString  szParameter[2];
	CStringArray  szParameters;
	CTPEPConnection  cConnection;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	GetDlgItem(IDC_TPEP_PARAMETERS_ITEM)->GetWindowText(szParameter[0]);
	for (nParameter = 0, nParameters = (GetParent()->GetConnectionProperties(&cConnection)) ? cConnection.GetParameters(szParameters) : -1; nParameter < nParameters; nParameter++)
	{
		if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(szParameters.GetAt(nParameter)))))
		{
			szParameter[1].Format(STRING(IDS_TPEPPARAMETERSDIALOG_PARAMETERFORMAT), (LPCTSTR)pDatabaseTMParameter->GetTag(), (LPCTSTR)pDatabaseTMParameter->GetDescription());
			if (szParameter[0] == szParameter[1]) break;
		}
	}
	if (nParameter < nParameters)
	{
		m_wndFolderCtrl.ShowParameterInfo(pDatabaseTMParameter->GetTag());
		return;
	}
	m_wndFolderCtrl.ShowParameterInfo();
}

CRect CTPEPParametersDialog::CalcFolderSize() CONST
{
	CRect  rFolder;

	GetDlgItem(IDC_TPEP_PARAMETERS_FOLDER)->GetWindowRect(rFolder);
	ScreenToClient(rFolder);
	return rFolder;
}

void CTPEPParametersDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTPEPParametersDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTPEPParametersDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTPEPParametersDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TPEP_PARAMETERS_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_TPEP_PARAMETERS_ITEM, OnSelchangeParameter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTPEPParametersDialog message handlers

BOOL CTPEPParametersDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (; m_wndFolderCtrl.Create(this, CalcFolderSize()) && SetChildSheet(&m_wndFolderCtrl, GetDlgItem(IDC_TPEP_PARAMETERS_FOLDER - 1)); )
	{
		if (EnumParameters()) ShowParameterInfo();
		break;
	}
	return TRUE;
}

void CTPEPParametersDialog::OnSelchangeParameter()
{
	ShowParameterInfo();
}

BOOL CTPEPParametersDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TPEPPARAMETERSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTPEPParametersDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TPEPPARAMETERSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTPEPAlertsDialog dialog

IMPLEMENT_DYNCREATE(CTPEPAlertsDialog, CDisplayDialog)

CTPEPAlertsDialog::CTPEPAlertsDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTPEPAlertsDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CTPEPAlertsDialog::Create(CWnd *pParentWnd, CONST CTPEPAlerts &pAlerts, CONST CTPEPConnection *pConnection)
{
	INT  nResult;

	for (m_pAlerts[0].Copy(&pAlerts), m_pAlerts[1].Copy(&pAlerts), m_cConnection.Copy(pConnection); (nResult = CDisplayDialog::Create(pParentWnd, CTPEPAlertsDialog::IDD)) == IDOK; ) break;
	return nResult;
}

CTPEPWnd *CTPEPAlertsDialog::GetParent() CONST
{
	return((CTPEPWnd *)CDisplayDialog::GetParent());
}

BOOL CTPEPAlertsDialog::EnumAlerts()
{
	INT  nItem;
	INT  nItems;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CTPEPAlert  *pAlert;

	for (nItem = 0, nItems = (INT)m_pAlerts[0].GetSize(); nItem < nItems; nItem++)
	{
		if ((pAlert = (CTPEPAlert *)m_pAlerts[0].GetAt(nItem)) != (CTPEPAlert *)NULL)
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TPEPALERTSDIALOG_LISTTITLEITEM_NAME); )
				{
					szItem = pAlert->GetName();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TPEPALERTSDIALOG_LISTTITLEITEM_PARAMETER); )
				{
					szItem = pAlert->GetParameter();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TPEPALERTSDIALOG_LISTTITLEITEM_STATUS); )
				{
					szItem = ((pAlert->GetOptions() & TPEPALERT_OPTION_DISABLED) != TPEPALERT_OPTION_DISABLED) ? STRING(IDS_TPEPALERTSDIALOG_LISTITEM_STATUS_ENABLED) : STRING(IDS_TPEPALERTSDIALOG_LISTITEM_STATUS_DISABLED);
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_TPEP_ALERTS_LIST), nItem, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_TPEP_ALERTS_LIST), nItem, nColumn, szItem);
			}
		}
	}
	Listview_SetCurText(GetDlgItem(IDC_TPEP_ALERTS_LIST), 0);
	return((SendDlgItemMessage(IDC_TPEP_ALERTS_LIST, LVM_GETITEMCOUNT) == nItems) ? TRUE : FALSE);
}

BOOL CTPEPAlertsDialog::EnumParameters()
{
	INT  nParameter;
	INT  nParameters;
	CStringArray  szParameters;

	for (nParameter = 0, nParameters = m_cConnection.GetParameters(szParameters); nParameter < nParameters; nParameter++)
	{
		SendDlgItemMessage(IDC_TPEP_ALERTS_PROPERTIES_WATCH_PARAMETER, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szParameters.GetAt(nParameter));
		continue;
	}
	return((SendDlgItemMessage(IDC_TPEP_ALERTS_PROPERTIES_WATCH_PARAMETER, CB_GETCOUNT) == nParameters) ? TRUE : FALSE);
}

BOOL CTPEPAlertsDialog::EnumOperators()
{
	INT  nOperator;
	INT  nOperators;

	for (nOperator = 0, nOperators = MAXTPEPALERTSDIALOGOPERATOR - MINTPEPALERTSDIALOGOPERATOR + 1; nOperator < nOperators; nOperator++)
	{
		SendDlgItemMessage(IDC_TPEP_ALERTS_PROPERTIES_WATCH_OPERATOR, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(MINTPEPALERTSDIALOGOPERATOR + nOperator));
		continue;
	}
	return((SendDlgItemMessage(IDC_TPEP_ALERTS_PROPERTIES_WATCH_OPERATOR, CB_GETCOUNT) == nOperators) ? TRUE : FALSE);
}

BOOL CTPEPAlertsDialog::EnumValues()
{
	INT  nTable;
	INT  nPoint;
	INT  nTables;
	INT  nPoints;
	double  fX[2];
	CString  szY;
	CString  szValue;
	CString  szParameter;
	CUIntArray  nCalTables[2];
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;

	SendDlgItemMessage(IDC_TPEP_ALERTS_PROPERTIES_WATCH_VALUE, CB_RESETCONTENT);
	GetDlgItem(IDC_TPEP_ALERTS_PROPERTIES_WATCH_PARAMETER)->GetWindowText(szParameter);
	if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(szParameter))))
	{
		for (nTable = 0, nTables = (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS) ? pDatabaseTMParameter->GetCalTableRefs(nCalTables[0], nCalTables[1]) : 0; nTable < nTables; nTable++)
		{
			for (nPoint = 0, nPoints = ((pDatabaseTMTxtCalTable = GetDatabase()->GetTMTxtCalTables()->GetAt(nCalTables[0].GetAt(nTable)))) ? (INT)pDatabaseTMTxtCalTable->GetCount() : 0; nPoint < nPoints; nPoint++)
			{
				if (pDatabaseTMTxtCalTable->GetAt(nPoint)->GetPoint(fX[0], szY))
				{
					szValue.Format(STRING(IDS_TPEPALERTSDIALOG_VALUE_POINTFORMAT), (LPCTSTR)szY, (LONGLONG)fX[0]);
					if (SendDlgItemMessage(IDC_TPEP_ALERTS_PROPERTIES_WATCH_VALUE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szValue) < 0)
					{
						SendDlgItemMessage(IDC_TPEP_ALERTS_PROPERTIES_WATCH_VALUE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szValue);
						continue;
					}
				}
				if (pDatabaseTMTxtCalTable->GetAt(nPoint)->GetRange(fX[0], fX[1], szY))
				{
					szValue.Format(STRING(IDS_TPEPALERTSDIALOG_VALUE_RANGEFORMAT), (LPCTSTR)szY, (LONGLONG)fX[0], (LONGLONG)fX[1]);
					if (SendDlgItemMessage(IDC_TPEP_ALERTS_PROPERTIES_WATCH_VALUE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szValue) < 0)
					{
						SendDlgItemMessage(IDC_TPEP_ALERTS_PROPERTIES_WATCH_VALUE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szValue);
						continue;
					}
				}
			}
		}
		SendDlgItemMessage(IDC_TPEP_ALERTS_PROPERTIES_WATCH_VALUE, CB_SETCURSEL);
	}
	return TRUE;
}

BOOL CTPEPAlertsDialog::EnumAuditions()
{
	INT  nAudition;
	INT  nAuditions;
	CStringArray  szAuditions;

	for (nAudition = 0, nAuditions = (EnumAuditionProfiles(szAuditions)) ? (INT)szAuditions.GetSize() : 0, SendDlgItemMessage(IDC_TPEP_ALERTS_PROPERTIES_AUDITION, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TPEPALERTSDIALOG_AUDITION_NONE)); nAudition < nAuditions; nAudition++)
	{
		SendDlgItemMessage(IDC_TPEP_ALERTS_PROPERTIES_AUDITION, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szAuditions.GetAt(nAudition));
		continue;
	}
	return((SendDlgItemMessage(IDC_TPEP_ALERTS_PROPERTIES_AUDITION, CB_GETCOUNT) > nAuditions) ? TRUE : FALSE);
}

BOOL CTPEPAlertsDialog::EnumNotifications()
{
	INT  nNotification;
	INT  nNotifications;
	CStringArray  szNotifications;

	for (nNotification = 0, nNotifications = (EnumNotificationProfiles(szNotifications)) ? (INT)szNotifications.GetSize() : 0, SendDlgItemMessage(IDC_TPEP_ALERTS_PROPERTIES_NOTIFICATION, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TPEPALERTSDIALOG_NOTIFICATION_NONE)); nNotification < nNotifications; nNotification++)
	{
		SendDlgItemMessage(IDC_TPEP_ALERTS_PROPERTIES_NOTIFICATION, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szNotifications.GetAt(nNotification));
		continue;
	}
	return((SendDlgItemMessage(IDC_TPEP_ALERTS_PROPERTIES_NOTIFICATION, CB_GETCOUNT) > nNotifications) ? TRUE : FALSE);
}

VOID CTPEPAlertsDialog::ShowAlertInfo()
{
	ShowAlertInfo(Listview_GetCurText(GetDlgItem(IDC_TPEP_ALERTS_LIST)));
}
VOID CTPEPAlertsDialog::ShowAlertInfo(INT nIndex)
{
	CString  szName;
	CTPEPAlert  *pAlert;

	if ((pAlert = m_pAlerts[0].GetAt(nIndex)))
	{
		CheckDlgButton(IDC_TPEP_ALERTS_PROPERTIES_DISABLED, (pAlert->GetOptions() & TPEPALERT_OPTION_DISABLED) ? TRUE : FALSE);
		SendDlgItemMessage(IDC_TPEP_ALERTS_PROPERTIES_WATCH_PARAMETER, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TPEP_ALERTS_PROPERTIES_WATCH_PARAMETER, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pAlert->GetParameter()));
		SendDlgItemMessage(IDC_TPEP_ALERTS_PROPERTIES_WATCH_OPERATOR, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TPEP_ALERTS_PROPERTIES_WATCH_OPERATOR, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(MINTPEPALERTSDIALOGOPERATOR + pAlert->GetOperator() - 1)));
		SendDlgItemMessage(IDC_TPEP_ALERTS_PROPERTIES_WATCH_VALUE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TPEP_ALERTS_PROPERTIES_WATCH_VALUE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)((EnumValues()) ? (LPCTSTR)pAlert->GetValue() : EMPTYSTRING)));
		SendDlgItemMessage(IDC_TPEP_ALERTS_PROPERTIES_AUDITION, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TPEP_ALERTS_PROPERTIES_AUDITION, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pAlert->GetAudition()));
		SendDlgItemMessage(IDC_TPEP_ALERTS_PROPERTIES_NOTIFICATION, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TPEP_ALERTS_PROPERTIES_NOTIFICATION, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pAlert->GetNotification()));
		for (GetDlgItem(IDC_TPEP_ALERTS_NAME)->GetWindowText(szName); pAlert->GetName() != szName; )
		{
			GetDlgItem(IDC_TPEP_ALERTS_NAME)->SetWindowText(pAlert->GetName());
			break;
		}
		GetDlgItem(IDC_TPEP_ALERTS_PROPERTIES_WATCH_VALUE)->SetWindowText(pAlert->GetValue());
		GetDlgItem(IDC_TPEP_ALERTS_PROPERTIES_TEXT)->SetWindowText(pAlert->GetText());
		GetDlgItem(IDC_TPEP_ALERTS_ADD)->EnableWindow(FALSE);
		GetDlgItem(IDC_TPEP_ALERTS_REMOVE)->EnableWindow();
		GetDlgItem(IDC_TPEP_ALERTS_REMOVEALL)->EnableWindow();
		return;
	}
	CheckDlgButton(IDC_TPEP_ALERTS_PROPERTIES_DISABLED, FALSE);
	SendDlgItemMessage(IDC_TPEP_ALERTS_PROPERTIES_WATCH_PARAMETER, CB_SETCURSEL);
	SendDlgItemMessage(IDC_TPEP_ALERTS_PROPERTIES_WATCH_OPERATOR, CB_SETCURSEL);
	SendDlgItemMessage(IDC_TPEP_ALERTS_PROPERTIES_WATCH_VALUE, CB_SETCURSEL, (EnumValues()) ? 0 : -1);
	SendDlgItemMessage(IDC_TPEP_ALERTS_PROPERTIES_AUDITION, CB_SETCURSEL);
	SendDlgItemMessage(IDC_TPEP_ALERTS_PROPERTIES_NOTIFICATION, CB_SETCURSEL);
	GetDlgItem(IDC_TPEP_ALERTS_NAME)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TPEP_ALERTS_PROPERTIES_WATCH_VALUE)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TPEP_ALERTS_PROPERTIES_TEXT)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_TPEP_ALERTS_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_ALERTS_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_ALERTS_REMOVEALL)->EnableWindow(FALSE);
}

BOOL CTPEPAlertsDialog::CheckAlertInfo() CONST
{
	return((GetDlgItem(IDC_TPEP_ALERTS_NAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TPEP_ALERTS_PROPERTIES_WATCH_VALUE)->GetWindowTextLength() > 0 && GetDlgItem(IDC_TPEP_ALERTS_PROPERTIES_TEXT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

CTPEPAlert *CTPEPAlertsDialog::FindAlertInfo() CONST
{
	CString  szName;

	GetDlgItem(IDC_TPEP_ALERTS_NAME)->GetWindowText(szName);
	return m_pAlerts[0].GetAt(m_pAlerts[0].Find(szName));
}

INT CTPEPAlertsDialog::CalcColumnWidth(LPCTSTR pszColumn)
{
	CDC  *pDC;
	INT  nWidth;
	CRect  rColumns;
	CFont  *pOldFont;
	TEXTMETRIC  tmFont;

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(GetFont())))
		{
			for (GetDlgItem(IDC_TPEP_ALERTS_LIST)->GetClientRect(rColumns), pDC->GetTextMetrics(&tmFont), nWidth = 0; !_tcscmp(pszColumn, STRING(IDS_TPEPALERTSDIALOG_LISTTITLEITEM_NAME)); )
			{
				nWidth = rColumns.Width() - CalcColumnWidth(STRING(IDS_TPEPALERTSDIALOG_LISTTITLEITEM_PARAMETER)) - CalcColumnWidth(STRING(IDS_TPEPALERTSDIALOG_LISTTITLEITEM_STATUS));
				break;
			}
			if (!_tcscmp(pszColumn, STRING(IDS_TPEPALERTSDIALOG_LISTTITLEITEM_PARAMETER)))
			{
				nWidth = GetDatabase()->GetTMParameterTagLength()*tmFont.tmAveCharWidth;
				nWidth = max(pDC->GetTextExtent(pszColumn).cx, nWidth);
				nWidth += 2 * CalcColumnIndent();
			}
			if (!_tcscmp(pszColumn, STRING(IDS_TPEPALERTSDIALOG_LISTTITLEITEM_STATUS)))
			{
				nWidth = pDC->GetTextExtent(pszColumn).cx;
				nWidth = max(pDC->GetTextExtent(STRING(IDS_TPEPALERTSDIALOG_LISTITEM_STATUS_ENABLED)).cx, nWidth);
				nWidth = max(pDC->GetTextExtent(STRING(IDS_TPEPALERTSDIALOG_LISTITEM_STATUS_DISABLED)).cx, nWidth);
				nWidth += 2 * CalcColumnIndent();
			}
			pDC->SelectObject(pOldFont);
			ReleaseDC(pDC);
			return nWidth;
		}
		ReleaseDC(pDC);
	}
	return 0;
}

INT CTPEPAlertsDialog::CalcColumnIndent() CONST
{
	return 3 * GetSystemMetrics(SM_CXEDGE);
}

BOOL CTPEPAlertsDialog::IsModified() CONST
{
	return !m_pAlerts[0].Compare(&m_pAlerts[1]);
}

BOOL CTPEPAlertsDialog::Check(BOOL bModified) CONST
{
	CString  szName;

	GetDlgItem(IDC_TPEP_ALERTS_NAME)->GetWindowText(szName);
	return(((m_pAlerts[0].Find(szName) >= 0 && CheckAlertInfo()) || (!m_pAlerts[0].GetSize() && szName.IsEmpty())) ? (!bModified || IsModified()) : FALSE);
}

void CTPEPAlertsDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTPEPAlertsDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTPEPAlertsDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_pAlerts[0].RemoveAll();
	m_pAlerts[1].RemoveAll();
	CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTPEPAlertsDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTPEPAlertsDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TPEP_ALERTS_ADD, OnAdd)
	ON_BN_CLICKED(IDC_TPEP_ALERTS_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_TPEP_ALERTS_REMOVEALL, OnRemoveAll)
	ON_BN_CLICKED(IDC_TPEP_ALERTS_PROPERTIES_DISABLED, OnDisabled)
	ON_BN_CLICKED(IDC_TPEP_ALERTS_HELP, OnHelp)
	ON_CBN_EDITCHANGE(IDC_TPEP_ALERTS_PROPERTIES_WATCH_VALUE, OnEditchangeValue)
	ON_CBN_SELCHANGE(IDC_TPEP_ALERTS_PROPERTIES_WATCH_PARAMETER, OnSelchangeParameter)
	ON_CBN_SELCHANGE(IDC_TPEP_ALERTS_PROPERTIES_WATCH_OPERATOR, OnSelchangeOperator)
	ON_CBN_SELCHANGE(IDC_TPEP_ALERTS_PROPERTIES_WATCH_VALUE, OnSelchangeValue)
	ON_CBN_SELCHANGE(IDC_TPEP_ALERTS_PROPERTIES_AUDITION, OnSelchangeAudition)
	ON_CBN_SELCHANGE(IDC_TPEP_ALERTS_PROPERTIES_NOTIFICATION, OnSelchangeNotification)
	ON_EN_CHANGE(IDC_TPEP_ALERTS_NAME, OnEditchangeName)
	ON_EN_CHANGE(IDC_TPEP_ALERTS_PROPERTIES_TEXT, OnEditchangeText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTPEPAlertsDialog message handlers

BOOL CTPEPAlertsDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	m_szColumns.Add(STRING(IDS_TPEPALERTSDIALOG_LISTTITLEITEM_NAME));
	m_szColumns.Add(STRING(IDS_TPEPALERTSDIALOG_LISTTITLEITEM_PARAMETER));
	m_szColumns.Add(STRING(IDS_TPEPALERTSDIALOG_LISTTITLEITEM_STATUS));
	SendDlgItemMessage(IDC_TPEP_ALERTS_LIST, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = CalcColumnWidth(m_szColumns.GetAt(nColumn)); nColumn < nColumns; nWidth = (++nColumn < nColumns) ? CalcColumnWidth(m_szColumns.GetAt(nColumn)) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TPEP_ALERTS_LIST), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	EnumAlerts();
	EnumParameters();
	EnumOperators();
	EnumAuditions();
	EnumNotifications();
	GetDlgItem(IDC_TPEP_ALERTS_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TPEP_ALERTS_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_TPEP_ALERTS_NAME)->EnableWindow();
	GetDlgItem(IDC_TPEP_ALERTS_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TPEP_ALERTS_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEP_ALERTS_LIST)->EnableWindow((SendDlgItemMessage(IDC_TPEP_ALERTS_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEP_ALERTS_PROPERTIES)->EnableWindow();
	GetDlgItem(IDC_TPEP_ALERTS_PROPERTIES_WATCH_STATIC)->EnableWindow();
	GetDlgItem(IDC_TPEP_ALERTS_PROPERTIES_WATCH_PARAMETER)->EnableWindow();
	GetDlgItem(IDC_TPEP_ALERTS_PROPERTIES_WATCH_OPERATOR)->EnableWindow();
	GetDlgItem(IDC_TPEP_ALERTS_PROPERTIES_WATCH_VALUE)->EnableWindow();
	GetDlgItem(IDC_TPEP_ALERTS_PROPERTIES_AUDITION_STATIC)->EnableWindow();
	GetDlgItem(IDC_TPEP_ALERTS_PROPERTIES_AUDITION)->EnableWindow();
	GetDlgItem(IDC_TPEP_ALERTS_PROPERTIES_NOTIFICATION_STATIC)->EnableWindow();
	GetDlgItem(IDC_TPEP_ALERTS_PROPERTIES_NOTIFICATION)->EnableWindow();
	GetDlgItem(IDC_TPEP_ALERTS_PROPERTIES_TEXT_STATIC)->EnableWindow();
	GetDlgItem(IDC_TPEP_ALERTS_PROPERTIES_TEXT)->EnableWindow();
	GetDlgItem(IDC_TPEP_ALERTS_PROPERTIES_DISABLED)->EnableWindow();
	ShowAlertInfo();
	return TRUE;
}

BOOL CTPEPAlertsDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TPEP_ALERTS_LIST)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED && (pNotifyListView->uNewState & LVIS_SELECTED)) ShowAlertInfo(pNotifyListView->iItem);
	}
	return CDisplayDialog::OnNotify(wParam, lParam, pResult);
}

void CTPEPAlertsDialog::OnAdd()
{
	INT  nIndex;
	INT  nColumn;
	INT  nColumns;
	UINT  nOptions;
	UINT  nOperator;
	CString  szItem;
	CString  szName;
	CString  szText;
	CString  szValue;
	CString  szParameter;
	CString  szNotification;
	CString  szAudition;
	CTPEPAlert  *pAlert;
	CHourglassCursor  cCursor;

	for (; (pAlert = new CTPEPAlert); )
	{
		GetDlgItem(IDC_TPEP_ALERTS_NAME)->GetWindowText(szName);
		GetDlgItem(IDC_TPEP_ALERTS_PROPERTIES_TEXT)->GetWindowText(szText);
		GetDlgItem(IDC_TPEP_ALERTS_PROPERTIES_WATCH_PARAMETER)->GetWindowText(szParameter);
		GetDlgItem(IDC_TPEP_ALERTS_PROPERTIES_WATCH_VALUE)->GetWindowText(szValue);
		GetDlgItem(IDC_TPEP_ALERTS_PROPERTIES_AUDITION)->GetWindowText(szAudition);
		GetDlgItem(IDC_TPEP_ALERTS_PROPERTIES_NOTIFICATION)->GetWindowText(szNotification);
		for (nOperator = (UINT)(SendDlgItemMessage(IDC_TPEP_ALERTS_PROPERTIES_WATCH_OPERATOR, CB_GETCURSEL) + 1), nOptions = (IsDlgButtonChecked(IDC_TPEP_ALERTS_PROPERTIES_DISABLED)) ? TPEPALERT_OPTION_DISABLED : 0, pAlert->SetName(szName), pAlert->SetText(szText), pAlert->SetValue(szValue), pAlert->SetOptions(nOptions), pAlert->SetOperator(nOperator), pAlert->SetAudition(szAudition), pAlert->SetParameter(szParameter), pAlert->SetNotification(szNotification); (nIndex = m_pAlerts[0].Add(pAlert)) >= 0; )
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TPEPALERTSDIALOG_LISTTITLEITEM_NAME); )
				{
					szItem = pAlert->GetName();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TPEPALERTSDIALOG_LISTTITLEITEM_PARAMETER); )
				{
					szItem = pAlert->GetParameter();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TPEPALERTSDIALOG_LISTTITLEITEM_STATUS); )
				{
					szItem = ((pAlert->GetOptions() & TPEPALERT_OPTION_DISABLED) != TPEPALERT_OPTION_DISABLED) ? STRING(IDS_TPEPALERTSDIALOG_LISTITEM_STATUS_ENABLED) : STRING(IDS_TPEPALERTSDIALOG_LISTITEM_STATUS_DISABLED);
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_TPEP_ALERTS_LIST), nIndex, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_TPEP_ALERTS_LIST), nIndex, nColumn, szItem);
			}
			Listview_SetCurText(GetDlgItem(IDC_TPEP_ALERTS_LIST), nIndex);
			break;
		}
		if (nIndex < 0) delete pAlert;
		break;
	}
	SendDlgItemMessage(IDC_TPEP_ALERTS_NAME, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_TPEP_ALERTS_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TPEP_ALERTS_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEP_ALERTS_LIST)->EnableWindow((SendDlgItemMessage(IDC_TPEP_ALERTS_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEP_ALERTS_ADD)->EnableWindow((GetDlgItem(IDC_TPEP_ALERTS_NAME)->GetWindowTextLength() > 0 && !FindAlertInfo()) ? CheckAlertInfo() : FALSE);
	GetDlgItem(IDC_TPEP_ALERTS_REMOVE)->EnableWindow((Listview_GetCurText(GetDlgItem(IDC_TPEP_ALERTS_LIST)) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEP_ALERTS_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_TPEP_ALERTS_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEP_ALERTS_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPAlertsDialog::OnRemove()
{
	INT  nIndex;
	CTPEPAlert  *pAlert;
	CHourglassCursor  cCursor;

	if (Listview_DeleteText(GetDlgItem(IDC_TPEP_ALERTS_LIST), (nIndex = Listview_GetCurText(GetDlgItem(IDC_TPEP_ALERTS_LIST)))))
	{
		if ((pAlert = m_pAlerts[0].GetAt(0)) != (CTPEPAlert *)NULL)
		{
			GetDlgItem(IDC_TPEP_ALERTS_NAME)->SetWindowText(pAlert->GetName());
			Listview_SetCurText(GetDlgItem(IDC_TPEP_ALERTS_LIST), 0);
		}
		if (!SendDlgItemMessage(IDC_TPEP_ALERTS_LIST, LVM_GETITEMCOUNT))
		{
			GetDlgItem(IDC_TPEP_ALERTS_NAME)->SetWindowText(EMPTYSTRING);
			GetDlgItem(IDC_TPEP_ALERTS_NAME)->SetFocus();
		}
		delete m_pAlerts[0].GetAt(nIndex);
		m_pAlerts[0].RemoveAt(nIndex);
		ShowAlertInfo();
	}
	GetDlgItem(IDC_TPEP_ALERTS_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TPEP_ALERTS_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEP_ALERTS_LIST)->EnableWindow((SendDlgItemMessage(IDC_TPEP_ALERTS_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPAlertsDialog::OnRemoveAll()
{
	CHourglassCursor  cCursor;

	for (m_pAlerts[0].RemoveAll(); SendDlgItemMessage(IDC_TPEP_ALERTS_LIST, LVM_DELETEALLITEMS); )
	{
		GetDlgItem(IDC_TPEP_ALERTS_NAME)->SetWindowText(EMPTYSTRING);
		GetDlgItem(IDC_TPEP_ALERTS_NAME)->SetFocus();
		ShowAlertInfo();
		break;
	}
	GetDlgItem(IDC_TPEP_ALERTS_LIST_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_ALERTS_LIST)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPAlertsDialog::OnDisabled()
{
	INT  nColumn;
	INT  nColumns;
	CTPEPAlert  *pAlert;

	if ((pAlert = FindAlertInfo()))
	{
		for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
		{
			if (m_szColumns.GetAt(nColumn) == STRING(IDS_TPEPALERTSDIALOG_LISTTITLEITEM_STATUS)) break;
			continue;
		}
		Listview_SetText(GetDlgItem(IDC_TPEP_ALERTS_LIST), Listview_GetCurText(GetDlgItem(IDC_TPEP_ALERTS_LIST)), nColumn, (!IsDlgButtonChecked(IDC_TPEP_ALERTS_PROPERTIES_DISABLED)) ? STRING(IDS_TPEPALERTSDIALOG_LISTITEM_STATUS_ENABLED) : STRING(IDS_TPEPALERTSDIALOG_LISTITEM_STATUS_DISABLED));
		pAlert->SetOptions((IsDlgButtonChecked(IDC_TPEP_ALERTS_PROPERTIES_DISABLED)) ? (pAlert->GetOptions() | TPEPALERT_OPTION_DISABLED) : (pAlert->GetOptions() & ~TPEPALERT_OPTION_DISABLED));
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPAlertsDialog::OnEditchangeName()
{
	CString  szName;

	for (GetDlgItem(IDC_TPEP_ALERTS_NAME)->GetWindowText(szName); m_pAlerts[0].Find(szName) >= 0; )
	{
		ShowAlertInfo();
		break;
	}
	GetDlgItem(IDC_TPEP_ALERTS_ADD)->EnableWindow((GetDlgItem(IDC_TPEP_ALERTS_NAME)->GetWindowTextLength() > 0 && !FindAlertInfo()) ? CheckAlertInfo() : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPAlertsDialog::OnEditchangeText()
{
	CString  szText;
	CTPEPAlert  *pAlert;

	if ((pAlert = FindAlertInfo()))
	{
		GetDlgItem(IDC_TPEP_ALERTS_PROPERTIES_TEXT)->GetWindowText(szText);
		pAlert->SetText(szText);
	}
	GetDlgItem(IDC_TPEP_ALERTS_ADD)->EnableWindow((GetDlgItem(IDC_TPEP_ALERTS_NAME)->GetWindowTextLength() > 0 && !pAlert) ? CheckAlertInfo() : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPAlertsDialog::OnEditchangeValue()
{
	CString  szValue;
	CTPEPAlert  *pAlert;

	if ((pAlert = FindAlertInfo()))
	{
		GetDlgItem(IDC_TPEP_ALERTS_PROPERTIES_WATCH_VALUE)->GetWindowText(szValue);
		pAlert->SetValue(szValue);
	}
	GetDlgItem(IDC_TPEP_ALERTS_ADD)->EnableWindow((GetDlgItem(IDC_TPEP_ALERTS_NAME)->GetWindowTextLength() > 0 && !pAlert) ? CheckAlertInfo() : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPAlertsDialog::OnSelchangeParameter()
{
	CString  szValue;
	CTPEPAlert  *pAlert;

	for (EnumValues(); (pAlert = FindAlertInfo()); )
	{
		GetDlgItem(IDC_TPEP_ALERTS_PROPERTIES_WATCH_VALUE)->GetWindowText(szValue);
		pAlert->SetValue(szValue);
		break;
	}
	GetDlgItem(IDC_TPEP_ALERTS_ADD)->EnableWindow((GetDlgItem(IDC_TPEP_ALERTS_NAME)->GetWindowTextLength() > 0 && !pAlert) ? CheckAlertInfo() : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPAlertsDialog::OnSelchangeOperator()
{
	UINT  nOperator;
	CTPEPAlert  *pAlert;

	if ((pAlert = FindAlertInfo()))
	{
		nOperator = (UINT)(SendDlgItemMessage(IDC_TPEP_ALERTS_PROPERTIES_WATCH_OPERATOR, CB_GETCURSEL) + 1);
		pAlert->SetOperator(nOperator);
	}
	GetDlgItem(IDC_TPEP_ALERTS_ADD)->EnableWindow((GetDlgItem(IDC_TPEP_ALERTS_NAME)->GetWindowTextLength() > 0 && !pAlert) ? CheckAlertInfo() : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPAlertsDialog::OnSelchangeValue()
{
	CString  szValue;
	CTPEPAlert  *pAlert;

	for (SendDlgItemMessage(IDC_TPEP_ALERTS_PROPERTIES_WATCH_VALUE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_TPEP_ALERTS_PROPERTIES_WATCH_VALUE, CB_GETCURSEL)); (pAlert = FindAlertInfo()); )
	{
		GetDlgItem(IDC_TPEP_ALERTS_PROPERTIES_WATCH_VALUE)->GetWindowText(szValue);
		pAlert->SetValue(szValue);
		break;
	}
	GetDlgItem(IDC_TPEP_ALERTS_ADD)->EnableWindow((GetDlgItem(IDC_TPEP_ALERTS_NAME)->GetWindowTextLength() > 0 && !pAlert) ? CheckAlertInfo() : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPAlertsDialog::OnSelchangeAudition()
{
	CString  szAudition;
	CTPEPAlert  *pAlert;

	if ((pAlert = FindAlertInfo()))
	{
		GetDlgItem(IDC_TPEP_ALERTS_PROPERTIES_AUDITION)->GetWindowText(szAudition);
		pAlert->SetAudition((szAudition != STRING(IDS_TPEPALERTSDIALOG_AUDITION_NONE)) ? (LPCTSTR)szAudition : EMPTYSTRING);
	}
	GetDlgItem(IDC_TPEP_ALERTS_ADD)->EnableWindow((GetDlgItem(IDC_TPEP_ALERTS_NAME)->GetWindowTextLength() > 0 && !pAlert) ? CheckAlertInfo() : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPAlertsDialog::OnSelchangeNotification()
{
	CString  szNotification;
	CTPEPAlert  *pAlert;

	if ((pAlert = FindAlertInfo()))
	{
		GetDlgItem(IDC_TPEP_ALERTS_PROPERTIES_NOTIFICATION)->GetWindowText(szNotification);
		pAlert->SetNotification((szNotification != STRING(IDS_TPEPALERTSDIALOG_NOTIFICATION_NONE)) ? (LPCTSTR)szNotification : EMPTYSTRING);
	}
	GetDlgItem(IDC_TPEP_ALERTS_ADD)->EnableWindow((GetDlgItem(IDC_TPEP_ALERTS_NAME)->GetWindowTextLength() > 0 && !pAlert) ? CheckAlertInfo() : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CTPEPAlertsDialog::OnOK()
{
	INT  nAlert;
	INT  nAlerts;
	INT  nTable;
	INT  nTables;
	INT  nPoint;
	INT  nPoints;
	double  fX[2];
	CString  szY;
	CString  szValue;
	CString  szParameter;
	CTPEPAlert  *pAlert;
	CUIntArray  nCalTables[2];
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;
	CHourglassCursor  cCursor;

	for (nAlert = 0, nAlerts = (INT)m_pAlerts[0].GetSize(); nAlert < nAlerts; nAlert++)
	{
		if ((pAlert = (CTPEPAlert *)m_pAlerts[0].GetAt(nAlert)) != (CTPEPAlert *)NULL)
		{
			if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pAlert->GetParameter()))))
			{
				for (nTable = 0, nTables = (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS) ? pDatabaseTMParameter->GetCalTableRefs(nCalTables[0], nCalTables[1]) : 0; nTable < nTables; nTable++)
				{
					for (nPoint = 0, nPoints = ((pDatabaseTMTxtCalTable = GetDatabase()->GetTMTxtCalTables()->GetAt(nCalTables[0].GetAt(nTable)))) ? (INT)pDatabaseTMTxtCalTable->GetCount() : 0; nPoint < nPoints; nPoint++)
					{
						if (pDatabaseTMTxtCalTable->GetAt(nPoint)->GetPoint(fX[0], szY))
						{
							szValue.Format(STRING(IDS_TPEPALERTSDIALOG_VALUE_POINTFORMAT), (LPCTSTR)szY, (LONGLONG)fX[0]);
							if (pAlert->GetValue() == szValue)
							{
								pAlert->SetValue(fX[0]);
								break;
							}
						}
						if (pDatabaseTMTxtCalTable->GetAt(nPoint)->GetRange(fX[0], fX[1], szY))
						{
							szValue.Format(STRING(IDS_TPEPALERTSDIALOG_VALUE_RANGEFORMAT), (LPCTSTR)szY, (LONGLONG)fX[0], (LONGLONG)fX[1]);
							if (pAlert->GetValue() == szValue)
							{
								pAlert->SetValue(fX[0], fX[1]);
								break;
							}
						}
					}
					if (nPoint < nPoints) break;
				}
				if (nTable == nTables) pAlert->SetValue(_ttof(pAlert->GetValue()));
				continue;
			}
		}
		m_pAlerts[0].RemoveAt(nAlert);
		delete pAlert;
		nAlerts--;
		nAlert--;
	}
	GetParent()->SetAlerts(m_pAlerts[0]);
	EndDialog(IDOK);
}

BOOL CTPEPAlertsDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TPEPALERTSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTPEPAlertsDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TPEPALERTSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTPEPFindDialog dialog

IMPLEMENT_DYNCREATE(CTPEPFindDialog, CDisplayDialog)

CTPEPFindDialog::CTPEPFindDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTPEPFindDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CTPEPFindDialog::Create(CWnd *pParentWnd, CString &szServer, CString &szClient, CTPEPConnection *pConnection)
{
	if (CDisplayDialog::Create(pParentWnd, CTPEPFindDialog::IDD) == IDOK  &&  m_pConnections.GetSize() == 1)
	{
		pConnection->Copy(m_pConnections.GetAt(0));
		szServer = m_szServers.GetAt(0);
		szClient = m_szClients.GetAt(0);
		return IDOK;
	}
	return IDCANCEL;
}

CTPEPWnd *CTPEPFindDialog::GetParent() CONST
{
	return((CTPEPWnd *)CDisplayDialog::GetParent());
}

BOOL CTPEPFindDialog::EnumSearchKeys()
{
	SendDlgItemMessage(IDC_TPEP_FIND_KEY, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TPEPFINDDIALOG_KEY_PACKET));
	SendDlgItemMessage(IDC_TPEP_FIND_KEY, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_TPEPFINDDIALOG_KEY_PARAMETER));
	return((SendDlgItemMessage(IDC_TPEP_FIND_KEY, CB_SETCURSEL) >= 0) ? TRUE : FALSE);
}

BOOL CTPEPFindDialog::EnumSearchValues()
{
	INT  nItem;
	INT  nItems;
	CString  szKey;
	CString  szValue;
	CDatabaseTMPacket  *pDatabaseTMPacket;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	GetDlgItem(IDC_TPEP_FIND_KEY)->GetWindowText(szKey);
	if (szKey == STRING(IDS_TPEPFINDDIALOG_KEY_PACKET))
	{
		for (nItem = 0, nItems = (INT)GetDatabase()->GetTMPackets()->GetSize(), SendDlgItemMessage(IDC_TPEP_FIND_VALUE, CB_RESETCONTENT); nItem < nItems; nItem++)
		{
			if ((pDatabaseTMPacket = (CDatabaseTMPacket *)GetDatabase()->GetTMPackets()->GetAt(nItem)) != (CDatabaseTMPacket *)NULL)
			{
				szValue.Format(STRING(IDS_TPEPFINDDIALOG_VALUE_FORMAT), (LPCTSTR)pDatabaseTMPacket->GetTag(), (LPCTSTR)pDatabaseTMPacket->GetDescription());
				SendDlgItemMessage(IDC_TPEP_FIND_VALUE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szValue);
			}
		}
	}
	if (szKey == STRING(IDS_TPEPFINDDIALOG_KEY_PARAMETER))
	{
		for (nItem = 0, nItems = (INT)GetDatabase()->GetTMParameters()->GetSize(), SendDlgItemMessage(IDC_TPEP_FIND_VALUE, CB_RESETCONTENT); nItem < nItems; nItem++)
		{
			if ((pDatabaseTMParameter = (CDatabaseTMParameter *)GetDatabase()->GetTMParameters()->GetAt(nItem)) != (CDatabaseTMParameter *)NULL)
			{
				szValue.Format(STRING(IDS_TPEPFINDDIALOG_VALUE_FORMAT), (LPCTSTR)pDatabaseTMParameter->GetTag(), (LPCTSTR)pDatabaseTMParameter->GetDescription());
				SendDlgItemMessage(IDC_TPEP_FIND_VALUE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szValue);
			}
		}
	}
	return((SendDlgItemMessage(IDC_TPEP_FIND_VALUE, CB_GETCOUNT) >= 0) ? TRUE : FALSE);
}

VOID CTPEPFindDialog::DoFindByPacket(LPCTSTR pszPacket)
{
	INT  nPacket;
	INT  nPackets;
	INT  nConnection;
	INT  nConnections;
	CStringArray  szPackets;
	CStringArray  szServers;
	CStringArray  szClients;
	CTPEPConnection  *pConnection;
	CTPEPConnections  pConnections;
	CComputerToken  cComputerToken;

	for (nConnection = 0, nConnections = GetTPEPService()->GetClientConnections(szServers, pConnections), SendDlgItemMessage(IDC_TPEP_FIND_RESULTS, LVM_DELETEALLITEMS), m_szServers.RemoveAll(), m_szClients.RemoveAll(), m_szConnections.RemoveAll(), m_pConnections.RemoveAll(); nConnection < nConnections; nConnection++)
	{
		if ((pConnection = pConnections.GetAt(nConnection)) && pConnection->GetType() == TPEP_TYPE_PACKETS)
		{
			for (nPacket = 0, nPackets = pConnection->GetPackets(szPackets); nPacket < nPackets; nPacket++)
			{
				if (!szPackets.GetAt(nPacket).Compare(pszPacket)) break;
				continue;
			}
			if (nPacket < nPackets)
			{
				ShowConnection(szServers.GetAt(nConnection), cComputerToken.GetComputerName(), pConnection);
				continue;
			}
		}
	}
	for (nConnection = 0, nConnections = GetTPEPService()->GetServerConnections(szClients, pConnections); nConnection < nConnections; nConnection++)
	{
		if ((pConnection = (szClients.GetAt(nConnection).CompareNoCase(cComputerToken.GetComputerName())) ? pConnections.GetAt(nConnection) : (CTPEPConnection *)NULL) && pConnection->GetType() == TPEP_TYPE_PACKETS)
		{
			for (nPacket = 0, nPackets = pConnection->GetPackets(szPackets); nPacket < nPackets; nPacket++)
			{
				if (!szPackets.GetAt(nPacket).Compare(pszPacket)) break;
				continue;
			}
			if (nPacket < nPackets)
			{
				ShowConnection(cComputerToken.GetComputerName(), szClients.GetAt(nConnection), pConnection);
				continue;
			}
		}
	}
	if (SendDlgItemMessage(IDC_TPEP_FIND_RESULTS, LVM_GETITEMCOUNT) > 0)
	{
		GetDlgItem(IDC_TPEP_FIND_RESULTS_STATIC)->EnableWindow();
		GetDlgItem(IDC_TPEP_FIND_RESULTS)->EnableWindow();
		GetDlgItem(IDC_TPEP_FIND_OPEN)->EnableWindow();
		GetDlgItem(IDC_TPEP_FIND_RESULTS)->SetFocus();
		return;
	}
	GetDlgItem(IDC_TPEP_FIND_RESULTS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_FIND_RESULTS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_FIND_OPEN)->EnableWindow(FALSE);
}

VOID CTPEPFindDialog::DoFindByPackets(CONST CStringArray &szPackets)
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	INT  nCount;
	INT  nPacket;
	INT  nPackets;
	INT  nConnection;
	INT  nConnections;
	CStringArray  szItems;
	CStringArray  szServers[2];
	CStringArray  szClients[2];
	CTPEPConnection  *pConnection[2];
	CTPEPConnections  pConnections[2][2];
	CComputerToken  cComputerToken;

	for (nConnection = 0, nConnections = GetTPEPService()->GetClientConnections(szServers[0], pConnections[0][0]), SendDlgItemMessage(IDC_TPEP_FIND_RESULTS, LVM_DELETEALLITEMS), m_szServers.RemoveAll(), m_szClients.RemoveAll(), m_szConnections.RemoveAll(), m_pConnections.RemoveAll(); nConnection < nConnections; nConnection++)
	{
		if ((pConnection[0] = pConnections[0][0].GetAt(nConnection)) && pConnection[0]->GetType() != TPEP_TYPE_PACKETS)
		{
			pConnections[0][0].RemoveAt(nConnection);
			szServers[0].RemoveAt(nConnection);
			delete pConnection[0];
			nConnections--;
			nConnection--;
		}
	}
	for (nConnection = 0, nConnections = GetTPEPService()->GetServerConnections(szClients[0], pConnections[0][1]); nConnection < nConnections; nConnection++)
	{
		if ((pConnection[1] = (szClients[0].GetAt(nConnection).CompareNoCase(cComputerToken.GetComputerName())) ? pConnections[0][1].GetAt(nConnection) : (CTPEPConnection *)NULL) == (CTPEPConnection *)NULL || pConnection[1]->GetType() != TPEP_TYPE_PACKETS)
		{
			delete pConnections[0][1].GetAt(nConnection);
			pConnections[0][1].RemoveAt(nConnection);
			szClients[0].RemoveAt(nConnection);
			nConnections--;
			nConnection--;
		}
	}
	for (nPacket = 0, nPackets = (INT)szPackets.GetSize(), pConnections[1][0].Copy(&pConnections[0][0]), pConnections[1][1].Copy(&pConnections[0][1]), szServers[1].Copy(szServers[0]), szClients[1].Copy(szClients[0]); nPacket < nPackets; nPacket += 2)
	{
		for (nConnection = 0, nConnections = (!nPacket || szPackets.GetAt(nPacket - 1) == STRING(IDS_TPEPFINDDIALOG_QUERY_AND)) ? (INT)pConnections[0][0].GetSize() : -1; nConnection < nConnections; nConnection++)
		{
			for (nItem = 0, nItems = ((pConnection[0] = pConnections[0][0].GetAt(nConnection)) && pConnection[0]->GetPackets(szItems) > 0) ? (INT)szItems.GetSize() : -1; nItem < nItems; nItem++)
			{
				if (szItems.GetAt(nItem) == szPackets.GetAt(nPacket)) break;
				continue;
			}
			if (nItem == nItems)
			{
				pConnections[0][0].RemoveAt(nConnection);
				szServers[0].RemoveAt(nConnection);
				delete pConnection[0];
				nConnections--;
				nConnection--;
			}
		}
		for (nConnection = 0, nConnections = (nPacket > 0 && szPackets.GetAt(nPacket - 1) == STRING(IDS_TPEPFINDDIALOG_QUERY_OR)) ? (INT)pConnections[1][0].GetSize() : -1; nConnection < nConnections; nConnection++)
		{
			for (nItem = 0, nItems = ((pConnection[0] = pConnections[1][0].GetAt(nConnection)) && pConnection[0]->GetPackets(szItems) > 0) ? (INT)szItems.GetSize() : -1; nItem < nItems; nItem++)
			{
				if (szItems.GetAt(nItem) == szPackets.GetAt(nPacket)) break;
				continue;
			}
			if (nItem < nItems)
			{
				for (nIndex = 0, nCount = (INT)pConnections[0][0].GetSize(); nIndex < nCount; nIndex++)
				{
					if (szServers[0].GetAt(nIndex) == szServers[1].GetAt(nConnection) && pConnection[0]->Compare(pConnections[0][0].GetAt(nIndex))) break;
					continue;
				}
				if (nIndex == nCount)
				{
					if ((pConnection[1] = new CTPEPConnection))
					{
						pConnection[1]->Copy(pConnection[0]);
						pConnections[0][0].Add(pConnection[1]);
						szServers[0].Add(szServers[1].GetAt(nConnection));
					}
				}
			}
		}
		for (nConnection = 0, nConnections = (nPacket > 0 && szPackets.GetAt(nPacket - 1) == STRING(IDS_TPEPFINDDIALOG_QUERY_OR)) ? (INT)pConnections[1][1].GetSize() : -1; nConnection < nConnections; nConnection++)
		{
			for (nItem = 0, nItems = ((pConnection[0] = pConnections[1][1].GetAt(nConnection)) && pConnection[0]->GetPackets(szItems) > 0) ? (INT)szItems.GetSize() : -1; nItem < nItems; nItem++)
			{
				if (szItems.GetAt(nItem) == szPackets.GetAt(nPacket)) break;
				continue;
			}
			if (nItem < nItems)
			{
				for (nIndex = 0, nCount = (INT)pConnections[0][1].GetSize(); nIndex < nCount; nIndex++)
				{
					if (szClients[0].GetAt(nIndex) == szClients[1].GetAt(nConnection) && pConnection[0]->Compare(pConnections[0][1].GetAt(nIndex))) break;
					continue;
				}
				if (nIndex == nCount)
				{
					if ((pConnection[1] = new CTPEPConnection))
					{
						pConnection[1]->Copy(pConnection[0]);
						pConnections[0][1].Add(pConnection[1]);
						szClients[0].Add(szClients[1].GetAt(nConnection));
					}
				}
			}
		}
	}
	for (nConnection = 0, nConnections = (INT)pConnections[0][0].GetSize(); nConnection < nConnections; nConnection++)
	{
		if ((pConnection[0] = (CTPEPConnection *)pConnections[0][0].GetAt(nConnection)) != (CTPEPConnection *)NULL)
		{
			ShowConnection(szServers[0].GetAt(nConnection), cComputerToken.GetComputerName(), pConnection[0]);
			continue;
		}
	}
	for (nConnection = 0, nConnections = (INT)pConnections[0][1].GetSize(); nConnection < nConnections; nConnection++)
	{
		if ((pConnection[0] = (CTPEPConnection *)pConnections[0][1].GetAt(nConnection)) != (CTPEPConnection *)NULL)
		{
			ShowConnection(cComputerToken.GetComputerName(), szClients[0].GetAt(nConnection), pConnection[0]);
			continue;
		}
	}
	if (SendDlgItemMessage(IDC_TPEP_FIND_RESULTS, LVM_GETITEMCOUNT) > 0)
	{
		GetDlgItem(IDC_TPEP_FIND_RESULTS_STATIC)->EnableWindow();
		GetDlgItem(IDC_TPEP_FIND_RESULTS)->EnableWindow();
		GetDlgItem(IDC_TPEP_FIND_OPEN)->EnableWindow();
		GetDlgItem(IDC_TPEP_FIND_RESULTS)->SetFocus();
		return;
	}
	GetDlgItem(IDC_TPEP_FIND_RESULTS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_FIND_RESULTS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_FIND_OPEN)->EnableWindow(FALSE);
}

VOID CTPEPFindDialog::DoFindByParameter(LPCTSTR pszParameter)
{
	INT  nParameter;
	INT  nParameters;
	INT  nConnection;
	INT  nConnections;
	CStringArray  szServers;
	CStringArray  szClients;
	CStringArray  szParameters;
	CTPEPConnection  *pConnection;
	CTPEPConnections  pConnections;
	CComputerToken  cComputerToken;

	for (nConnection = 0, nConnections = GetTPEPService()->GetClientConnections(szServers, pConnections), SendDlgItemMessage(IDC_TPEP_FIND_RESULTS, LVM_DELETEALLITEMS), m_szServers.RemoveAll(), m_szClients.RemoveAll(), m_szConnections.RemoveAll(), m_pConnections.RemoveAll(); nConnection < nConnections; nConnection++)
	{
		if ((pConnection = pConnections.GetAt(nConnection)) && pConnection->GetType() == TPEP_TYPE_PARAMETERS)
		{
			for (nParameter = 0, nParameters = pConnection->GetParameters(szParameters); nParameter < nParameters; nParameter++)
			{
				if (!szParameters.GetAt(nParameter).Compare(pszParameter)) break;
				continue;
			}
			if (nParameter < nParameters)
			{
				ShowConnection(szServers.GetAt(nConnection), cComputerToken.GetComputerName(), pConnection);
				continue;
			}
		}
	}
	for (nConnection = 0, nConnections = GetTPEPService()->GetServerConnections(szClients, pConnections); nConnection < nConnections; nConnection++)
	{
		if ((pConnection = (szClients.GetAt(nConnection).CompareNoCase(cComputerToken.GetComputerName())) ? pConnections.GetAt(nConnection) : (CTPEPConnection *)NULL) && pConnection->GetType() == TPEP_TYPE_PACKETS)
		{
			for (nParameter = 0, nParameters = pConnection->GetParameters(szParameters); nParameter < nParameters; nParameter++)
			{
				if (!szParameters.GetAt(nParameter).Compare(pszParameter)) break;
				continue;
			}
			if (nParameter < nParameters)
			{
				ShowConnection(cComputerToken.GetComputerName(), szClients.GetAt(nConnection), pConnection);
				continue;
			}
		}
	}
	if (SendDlgItemMessage(IDC_TPEP_FIND_RESULTS, LVM_GETITEMCOUNT) > 0)
	{
		GetDlgItem(IDC_TPEP_FIND_RESULTS_STATIC)->EnableWindow();
		GetDlgItem(IDC_TPEP_FIND_RESULTS)->EnableWindow();
		GetDlgItem(IDC_TPEP_FIND_OPEN)->EnableWindow();
		GetDlgItem(IDC_TPEP_FIND_RESULTS)->SetFocus();
		return;
	}
	GetDlgItem(IDC_TPEP_FIND_RESULTS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_FIND_RESULTS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_FIND_OPEN)->EnableWindow(FALSE);
}

VOID CTPEPFindDialog::DoFindByParameters(CONST CStringArray &szParameters)
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	INT  nCount;
	INT  nParameter;
	INT  nParameters;
	INT  nConnection;
	INT  nConnections;
	CStringArray  szItems;
	CStringArray  szServers[2];
	CStringArray  szClients[2];
	CTPEPConnection  *pConnection[2];
	CTPEPConnections  pConnections[2][2];
	CComputerToken  cComputerToken;

	for (nConnection = 0, nConnections = GetTPEPService()->GetClientConnections(szServers[0], pConnections[0][0]), SendDlgItemMessage(IDC_TPEP_FIND_RESULTS, LVM_DELETEALLITEMS), m_szServers.RemoveAll(), m_szClients.RemoveAll(), m_szConnections.RemoveAll(), m_pConnections.RemoveAll(); nConnection < nConnections; nConnection++)
	{
		if ((pConnection[0] = pConnections[0][0].GetAt(nConnection)) && pConnection[0]->GetType() != TPEP_TYPE_PARAMETERS)
		{
			pConnections[0][0].RemoveAt(nConnection);
			szServers[0].RemoveAt(nConnection);
			delete pConnection[0];
			nConnections--;
			nConnection--;
		}
	}
	for (nConnection = 0, nConnections = GetTPEPService()->GetServerConnections(szClients[0], pConnections[0][1]); nConnection < nConnections; nConnection++)
	{
		if ((pConnection[1] = (szClients[0].GetAt(nConnection).CompareNoCase(cComputerToken.GetComputerName())) ? pConnections[0][1].GetAt(nConnection) : (CTPEPConnection *)NULL) == (CTPEPConnection *)NULL || pConnection[1]->GetType() != TPEP_TYPE_PARAMETERS)
		{
			delete pConnections[0][1].GetAt(nConnection);
			pConnections[0][1].RemoveAt(nConnection);
			szClients[0].RemoveAt(nConnection);
			nConnections--;
			nConnection--;
		}
	}
	for (nParameter = 0, nParameters = (INT)szParameters.GetSize(), pConnections[1][0].Copy(&pConnections[0][0]), pConnections[1][1].Copy(&pConnections[0][1]), szServers[1].Copy(szServers[0]), szClients[1].Copy(szClients[0]); nParameter < nParameters; nParameter += 2)
	{
		for (nConnection = 0, nConnections = (!nParameter || szParameters.GetAt(nParameter - 1) == STRING(IDS_TPEPFINDDIALOG_QUERY_AND)) ? (INT)pConnections[0][0].GetSize() : -1; nConnection < nConnections; nConnection++)
		{
			for (nItem = 0, nItems = ((pConnection[0] = pConnections[0][0].GetAt(nConnection)) && pConnection[0]->GetParameters(szItems) > 0) ? (INT)szItems.GetSize() : -1; nItem < nItems; nItem++)
			{
				if (szItems.GetAt(nItem) == szParameters.GetAt(nParameter)) break;
				continue;
			}
			if (nItem == nItems)
			{
				pConnections[0][0].RemoveAt(nConnection);
				szServers[0].RemoveAt(nConnection);
				delete pConnection[0];
				nConnections--;
				nConnection--;
			}
		}
		for (nConnection = 0, nConnections = (nParameter > 0 && szParameters.GetAt(nParameter - 1) == STRING(IDS_TPEPFINDDIALOG_QUERY_OR)) ? (INT)pConnections[1][0].GetSize() : -1; nConnection < nConnections; nConnection++)
		{
			for (nItem = 0, nItems = ((pConnection[0] = pConnections[1][0].GetAt(nConnection)) && pConnection[0]->GetParameters(szItems) > 0) ? (INT)szItems.GetSize() : -1; nItem < nItems; nItem++)
			{
				if (szItems.GetAt(nItem) == szParameters.GetAt(nParameter)) break;
				continue;
			}
			if (nItem < nItems)
			{
				for (nIndex = 0, nCount = (INT)pConnections[0][0].GetSize(); nIndex < nCount; nIndex++)
				{
					if (szServers[0].GetAt(nIndex) == szServers[1].GetAt(nConnection) && pConnection[0]->Compare(pConnections[0][0].GetAt(nIndex))) break;
					continue;
				}
				if (nIndex == nCount)
				{
					if ((pConnection[1] = new CTPEPConnection))
					{
						pConnection[1]->Copy(pConnection[0]);
						pConnections[0][0].Add(pConnection[1]);
						szServers[0].Add(szServers[1].GetAt(nConnection));
					}
				}
			}
		}
		for (nConnection = 0, nConnections = (nParameter > 0 && szParameters.GetAt(nParameter - 1) == STRING(IDS_TPEPFINDDIALOG_QUERY_OR)) ? (INT)pConnections[1][1].GetSize() : -1; nConnection < nConnections; nConnection++)
		{
			for (nItem = 0, nItems = ((pConnection[0] = pConnections[1][1].GetAt(nConnection)) && pConnection[0]->GetParameters(szItems) > 0) ? (INT)szItems.GetSize() : -1; nItem < nItems; nItem++)
			{
				if (szItems.GetAt(nItem) == szParameters.GetAt(nParameter)) break;
				continue;
			}
			if (nItem < nItems)
			{
				for (nIndex = 0, nCount = (INT)pConnections[0][1].GetSize(); nIndex < nCount; nIndex++)
				{
					if (szClients[0].GetAt(nIndex) == szClients[1].GetAt(nConnection) && pConnection[0]->Compare(pConnections[0][1].GetAt(nIndex))) break;
					continue;
				}
				if (nIndex == nCount)
				{
					if ((pConnection[1] = new CTPEPConnection))
					{
						pConnection[1]->Copy(pConnection[0]);
						pConnections[0][1].Add(pConnection[1]);
						szClients[0].Add(szClients[1].GetAt(nConnection));
					}
				}
			}
		}
	}
	for (nConnection = 0, nConnections = (INT)pConnections[0][0].GetSize(); nConnection < nConnections; nConnection++)
	{
		if ((pConnection[0] = (CTPEPConnection *)pConnections[0][0].GetAt(nConnection)) != (CTPEPConnection *)NULL)
		{
			ShowConnection(szServers[0].GetAt(nConnection), cComputerToken.GetComputerName(), pConnection[0]);
			continue;
		}
	}
	for (nConnection = 0, nConnections = (INT)pConnections[0][1].GetSize(); nConnection < nConnections; nConnection++)
	{
		if ((pConnection[0] = (CTPEPConnection *)pConnections[0][1].GetAt(nConnection)) != (CTPEPConnection *)NULL)
		{
			ShowConnection(cComputerToken.GetComputerName(), szClients[0].GetAt(nConnection), pConnection[0]);
			continue;
		}
	}
	if (SendDlgItemMessage(IDC_TPEP_FIND_RESULTS, LVM_GETITEMCOUNT) > 0)
	{
		GetDlgItem(IDC_TPEP_FIND_RESULTS_STATIC)->EnableWindow();
		GetDlgItem(IDC_TPEP_FIND_RESULTS)->EnableWindow();
		GetDlgItem(IDC_TPEP_FIND_OPEN)->EnableWindow();
		GetDlgItem(IDC_TPEP_FIND_RESULTS)->SetFocus();
		return;
	}
	GetDlgItem(IDC_TPEP_FIND_RESULTS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_FIND_RESULTS)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_FIND_OPEN)->EnableWindow(FALSE);
}

VOID CTPEPFindDialog::ShowConnection(LPCTSTR pszServer, LPCTSTR pszClient, CONST CTPEPConnection *pConnection)
{
	INT  nIndex;
	INT  nColumn;
	INT  nColumns;
	INT  nPacket;
	INT  nPackets;
	INT  nParameter;
	INT  nParameters;
	CString  szItem;
	CString  szConnection[2];
	CStringArray  szPackets;
	CStringArray  szParameters;
	CTPEPConnection  *pConnectionInfo;

	if ((pConnectionInfo = new CTPEPConnection))
	{
		for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), pConnectionInfo->Copy(pConnection), m_pConnections.Add(pConnectionInfo), m_szServers.Add(pszServer), m_szClients.Add(pszClient), nIndex = (INT)m_pConnections.GetUpperBound(); nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TPEPFINDDIALOG_RESULT_TITLEITEM_SERVERNAME); )
			{
				szItem = m_szServers.GetAt(nIndex);
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TPEPFINDDIALOG_RESULT_TITLEITEM_CLIENTNAME); )
			{
				szItem = m_szClients.GetAt(nIndex);
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TPEPFINDDIALOG_RESULT_TITLEITEM_DESCRIPTION); )
			{
				for (nPacket = 0, nPackets = pConnectionInfo->GetPackets(szPackets), szConnection[0].Empty(); nPacket < nPackets; nPacket++)
				{
					szConnection[0] = (nPacket > 0) ? (szConnection[0] + STRING(IDS_TPEPFINDDIALOG_RESULT_SAMPLE_SEPARATOR) + szPackets.GetAt(nPacket)) : (STRING(IDS_TPEPFINDDIALOG_RESULT_TYPE_PACKETS) + szPackets.GetAt(nPacket));
					continue;
				}
				for (nParameter = 0, nParameters = pConnectionInfo->GetParameters(szParameters); nParameter < nParameters; nParameter++)
				{
					szConnection[0] = (nParameter > 0) ? (szConnection[0] + STRING(IDS_TPEPFINDDIALOG_RESULT_SAMPLE_SEPARATOR) + szParameters.GetAt(nParameter)) : (STRING(IDS_TPEPFINDDIALOG_RESULT_TYPE_PARAMETERS) + szParameters.GetAt(nParameter));
					continue;
				}
				if (nPackets > 0 || nParameters > 0)
				{
					szConnection[1].Format(STRING(IDS_TPEPFINDDIALOG_RESULT_FORMAT), (LPCTSTR)szConnection[0], (pConnection->GetDataMode() == TPEP_DATAMODE_REALTIME) ? STRING(IDS_TPEPFINDDIALOG_RESULT_MODE_REALTIME) : ((pConnection->GetDataMode() == TPEP_DATAMODE_HISTORY) ? STRING(IDS_TPEPFINDDIALOG_RESULT_MODE_HISTORY) : ((pConnection->GetDataMode() == TPEP_DATAMODE_RANDOM) ? STRING(IDS_TPEPFINDDIALOG_RESULT_MODE_RANDOM) : EMPTYSTRING)));
					szItem = szConnection[1];
				}
				else
				{
					szConnection[1] = STRING(IDS_TPEPFINDDIALOG_RESULT_SAMPLE_UNKNOWN);
					szItem = szConnection[1];
				}
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_TPEP_FIND_RESULTS), nIndex, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_TPEP_FIND_RESULTS), nIndex, nColumn, szItem);
		}
		Listview_SetCurText(GetDlgItem(IDC_TPEP_FIND_RESULTS), nIndex);
	}
}

void CTPEPFindDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTPEPFindDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTPEPFindDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTPEPFindDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTPEPFindDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TPEP_FIND_SEARCH, OnSearch)
	ON_BN_CLICKED(IDC_TPEP_FIND_OPEN, OnOpen)
	ON_BN_CLICKED(IDC_TPEP_FIND_HELP, OnHelp)
	ON_CBN_EDITCHANGE(IDC_TPEP_FIND_VALUE, OnEditchangeValue)
	ON_CBN_SELCHANGE(IDC_TPEP_FIND_KEY, OnSelchangeKey)
	ON_CBN_SELCHANGE(IDC_TPEP_FIND_VALUE, OnSelchangeValue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTPEPFindDialog message handlers

BOOL CTPEPFindDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	GetDlgItem(IDC_TPEP_FIND_RESULTS)->GetClientRect(rColumns);
	m_szColumns.Add(STRING(IDS_TPEPFINDDIALOG_RESULT_TITLEITEM_SERVERNAME));
	m_szColumns.Add(STRING(IDS_TPEPFINDDIALOG_RESULT_TITLEITEM_CLIENTNAME));
	m_szColumns.Add(STRING(IDS_TPEPFINDDIALOG_RESULT_TITLEITEM_DESCRIPTION));
	SendDlgItemMessage(IDC_TPEP_FIND_RESULTS, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = rColumns.Width() / 4; nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (3 * rColumns.Width() / 2 - nColumn*nWidth) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TPEP_FIND_RESULTS), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	EnumSearchKeys();
	EnumSearchValues();
	GetDlgItem(IDC_TPEP_FIND_KEY_STATIC)->EnableWindow();
	GetDlgItem(IDC_TPEP_FIND_KEY)->EnableWindow();
	GetDlgItem(IDC_TPEP_FIND_VALUE_STATIC)->EnableWindow();
	GetDlgItem(IDC_TPEP_FIND_VALUE)->EnableWindow();
	return TRUE;
}

BOOL CTPEPFindDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TPEP_FIND_RESULTS)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED)
		{
			GetDlgItem(IDOK)->EnableWindow();
			return TRUE;
		}
		if (pNotifyListView->hdr.code == NM_DBLCLK)
		{
			OnOK();
			return TRUE;
		}
	}
	return CDisplayDialog::OnNotify(wParam, lParam, pResult);
}

void CTPEPFindDialog::OnSearch()
{
	INT  nPos;
	INT  nIndex;
	CString  szKey;
	CString  szValue;
	CString  szPacket;
	CString  szParameter;
	CStringArray  szPackets;
	CStringArray  szParameters;
	CDatabaseTMPacket  *pDatabaseTMPacket;
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_TPEP_FIND_KEY)->GetWindowText(szKey);
	GetDlgItem(IDC_TPEP_FIND_VALUE)->GetWindowText(szValue);
	if (szKey == STRING(IDS_TPEPFINDDIALOG_KEY_PACKET))
	{
		if ((nIndex = (INT)SendDlgItemMessage(IDC_TPEP_FIND_VALUE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szValue)) >= 0)
		{
			if ((pDatabaseTMPacket = GetDatabase()->GetTMPackets()->GetAt(nIndex)))
			{
				DoFindByPacket(pDatabaseTMPacket->GetTag());
				return;
			}
		}
		if ((pDatabaseTMPacket = GetDatabase()->GetTMPackets()->GetAt(GetDatabase()->GetTMPackets()->Find(szValue))))
		{
			DoFindByPacket(pDatabaseTMPacket->GetTag());
			return;
		}
		for (nPos = 0; nPos < szValue.GetLength(); nPos++)
		{
			for (szPacket.Empty(); nPos < szValue.GetLength(); nPos++)
			{
				if (!_istspace(szValue.GetAt(nPos))) break;
				continue;
			}
			if (szValue.GetAt(nPos) != STRINGCHAR(IDS_TPEPFINDDIALOG_QUERY_QUOTE))
			{
				nPos = -1;
				break;
			}
			for (nPos = nPos + 1; nPos < szValue.GetLength(); nPos++)
			{
				if (!_istspace(szValue.GetAt(nPos)) && szValue.GetAt(nPos) != STRINGCHAR(IDS_TPEPFINDDIALOG_QUERY_QUOTE))
				{
					szPacket += szValue.GetAt(nPos);
					continue;
				}
				break;
			}
			if (szValue.GetAt(nPos) != STRINGCHAR(IDS_TPEPFINDDIALOG_QUERY_QUOTE))
			{
				nPos = -1;
				break;
			}
			if ((pDatabaseTMPacket = GetDatabase()->GetTMPackets()->GetAt(GetDatabase()->GetTMPackets()->Find(szPacket))))
			{
				for (nPos = nPos + 1, szPackets.Add(szPacket); nPos < szValue.GetLength(); nPos++)
				{
					if (!_istspace(szValue.GetAt(nPos))) break;
					continue;
				}
				if (szValue.GetAt(nPos) == STRINGCHAR(IDS_TPEPFINDDIALOG_QUERY_AND) || szValue.GetAt(nPos) == STRINGCHAR(IDS_TPEPFINDDIALOG_QUERY_OR))
				{
					szPackets.Add(szValue.GetAt(nPos));
					continue;
				}
			}
			break;
		}
		if (nPos >= szValue.GetLength())
		{
			if (szPackets.GetSize() > 0)
			{
				DoFindByPackets(szPackets);
				return;
			}
		}
		GetDlgItem(IDC_TPEP_FIND_VALUE)->SetFocus();
		CAudioDevice::AlertBySound();
		return;
	}
	if (szKey == STRING(IDS_TPEPFINDDIALOG_KEY_PARAMETER))
	{
		if ((nIndex = (INT)SendDlgItemMessage(IDC_TPEP_FIND_VALUE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szValue)) >= 0)
		{
			if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(nIndex)))
			{
				DoFindByParameter(pDatabaseTMParameter->GetTag());
				return;
			}
		}
		if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(szValue))))
		{
			DoFindByParameter(pDatabaseTMParameter->GetTag());
			return;
		}
		for (nPos = 0; nPos < szValue.GetLength(); nPos++)
		{
			for (szParameter.Empty(); nPos < szValue.GetLength(); nPos++)
			{
				if (!_istspace(szValue.GetAt(nPos))) break;
				continue;
			}
			if (szValue.GetAt(nPos) != STRINGCHAR(IDS_TPEPFINDDIALOG_QUERY_QUOTE))
			{
				nPos = -1;
				break;
			}
			for (nPos = nPos + 1; nPos < szValue.GetLength(); nPos++)
			{
				if (!_istspace(szValue.GetAt(nPos)) && szValue.GetAt(nPos) != STRINGCHAR(IDS_TPEPFINDDIALOG_QUERY_QUOTE))
				{
					szParameter += szValue.GetAt(nPos);
					continue;
				}
				break;
			}
			if (szValue.GetAt(nPos) != STRINGCHAR(IDS_TPEPFINDDIALOG_QUERY_QUOTE))
			{
				nPos = -1;
				break;
			}
			if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(szParameter))))
			{
				for (nPos = nPos + 1, szParameters.Add(szParameter); nPos < szValue.GetLength(); nPos++)
				{
					if (!_istspace(szValue.GetAt(nPos))) break;
					continue;
				}
				if (szValue.GetAt(nPos) == STRINGCHAR(IDS_TPEPFINDDIALOG_QUERY_AND) || szValue.GetAt(nPos) == STRINGCHAR(IDS_TPEPFINDDIALOG_QUERY_OR))
				{
					szParameters.Add(szValue.GetAt(nPos));
					continue;
				}
			}
			break;
		}
		if (nPos >= szValue.GetLength())
		{
			if (szParameters.GetSize() > 0)
			{
				DoFindByParameters(szParameters);
				return;
			}
		}
		GetDlgItem(IDC_TPEP_FIND_VALUE)->SetFocus();
		CAudioDevice::AlertBySound();
		return;
	}
}

void CTPEPFindDialog::OnOpen()
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	CHourglassCursor  cCursor;

	if ((nIndex = Listview_GetCurText(GetDlgItem(IDC_TPEP_FIND_RESULTS))) >= 0)
	{
		for (m_pConnections.InsertAt(0, m_pConnections.GetAt(nIndex)), m_pConnections.RemoveAt(nIndex + 1); nIndex < m_szServers.GetSize(); )
		{
			m_szServers.InsertAt(0, (LPCTSTR)m_szServers.GetAt(nIndex));
			m_szServers.RemoveAt(nIndex + 1);
			break;
		}
		if (nIndex < m_szClients.GetSize())
		{
			m_szClients.InsertAt(0, (LPCTSTR)m_szClients.GetAt(nIndex));
			m_szClients.RemoveAt(nIndex + 1);
		}
		for (nItem = 1, nItems = (INT)SendDlgItemMessage(IDC_TPEP_FIND_RESULTS, LVM_GETITEMCOUNT); nItem < nItems; nItem++)
		{
			delete m_pConnections.GetAt(nItem);
			m_pConnections.RemoveAt(nItem);
			m_szServers.RemoveAt(nItem);
			m_szClients.RemoveAt(nItem);
			nItems--;
			nItem--;
		}
	}
	EndDialog((nIndex >= 0) ? IDOK : IDCANCEL);
}

void CTPEPFindDialog::OnSelchangeKey()
{
	EnumSearchValues();
	GetDlgItem(IDC_TPEP_FIND_SEARCH)->EnableWindow(FALSE);
	GetDlgItem(IDC_TPEP_FIND_VALUE)->SetFocus();
}

void CTPEPFindDialog::OnSelchangeValue()
{
	GetDlgItem(IDC_TPEP_FIND_SEARCH)->EnableWindow((SendDlgItemMessage(IDC_TPEP_FIND_VALUE, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
}

void CTPEPFindDialog::OnEditchangeValue()
{
	GetDlgItem(IDC_TPEP_FIND_SEARCH)->EnableWindow((GetDlgItem(IDC_TPEP_FIND_VALUE)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

void CTPEPFindDialog::OnOK()
{
	CDisplayDialog::OnCancel();
}

BOOL CTPEPFindDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TPEPFINDDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTPEPFindDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TPEPFINDDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTPEPOpenDialog dialog

IMPLEMENT_DYNCREATE(CTPEPOpenDialog, CDisplayDialog)

CTPEPOpenDialog::CTPEPOpenDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CTPEPOpenDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CTPEPOpenDialog::Create(CWnd *pParentWnd)
{
	return CDisplayDialog::Create(pParentWnd, CTPEPOpenDialog::IDD);
}

BOOL CTPEPOpenDialog::Initialize()
{
	m_nFilterMode = 0;
	m_nFilterLimit = 0;
	m_nFilterDigits = 0;
	m_nFilterStatus = 0;
	m_tFilterRange[0][0] = 0;
	m_tFilterRange[0][1] = 0;
	m_tFilterRange[1][0] = 0;
	m_tFilterRange[1][1] = 0;
	m_tFilterDailyRange[0] = 0;
	m_tFilterDailyRange[1] = 0;
	m_tFilterPeriodical = 0;
	m_bLayoutToolTips = FALSE;
	ZeroMemory(&m_fntLayoutTitle, sizeof(LOGFONT));
	ZeroMemory(&m_fntLayoutMessages, sizeof(LOGFONT));
	return TRUE;
}

CString CTPEPOpenDialog::GetTitle() CONST
{
	CString  szTitle;
	CString  szComputer;
	CTPEPConnection  cConnection;
	BOOL  bConnection;

	if (GetConnection(szComputer, &cConnection, bConnection))
	{
		if (cConnection.GetType() == TPEP_TYPE_PACKETS || cConnection.GetType() == TPEP_TYPE_PARAMETERS)
		{
			szTitle.Format(STRING(IDS_WINDOW_FULLTITLE), STRING(IDS_DISPLAY_TITLE_TPEP), (cConnection.GetType() == TPEP_TYPE_PACKETS) ? STRING(IDS_TPEP_TITLE_PACKETS) : STRING(IDS_TPEP_TITLE_PARAMETERS));
			return szTitle;
		}
	}
	return STRING(IDS_DISPLAY_TITLE_TPEP);
}

UINT CTPEPOpenDialog::GetType() CONST
{
	return((IsDlgButtonChecked(IDC_TPEP_OPEN_TYPE_NORMAL) || IsDlgButtonChecked(IDC_TPEP_OPEN_TYPE_SIMPLE)) ? ((IsDlgButtonChecked(IDC_TPEP_OPEN_TYPE_NORMAL)) ? TPEP_TYPE_NORMAL : TPEP_TYPE_SIMPLE) : -1);
}

BOOL CTPEPOpenDialog::GetConnection(CString &szComputer, CTPEPConnection *pConnection, BOOL &bConnection) CONST
{
	INT  nIndex;

	if ((nIndex = Listview_GetCurText(GetDlgItem(IDC_TPEP_OPEN_CONNECTION))) >= 0)
	{
		if (nIndex < m_pConnections[0].GetSize())
		{
			szComputer = m_szServers.GetAt(nIndex);
			pConnection->Copy(m_pConnections[0].GetAt(nIndex));
			bConnection = TRUE;
			return TRUE;
		}
		szComputer = m_szClients.GetAt(nIndex - m_pConnections[0].GetSize());
		pConnection->Copy(m_pConnections[1].GetAt((INT)(nIndex - m_pConnections[0].GetSize())));
		bConnection = FALSE;
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPOpenDialog::GetLayoutColumns(CUIntArray &nColumns) CONST
{
	if (IsDlgButtonChecked(IDC_TPEP_OPEN_TYPE_NORMAL))
	{
		for (nColumns.RemoveAll(); !m_nLayoutColumns.GetSize(); )
		{
			if (TPEP_TITLEITEMS_DEFAULT & TPEP_TITLEITEM_ID) nColumns.Add(TPEP_TITLEITEM_ID);
			if (TPEP_TITLEITEMS_DEFAULT & TPEP_TITLEITEM_DESCRIPTION) nColumns.Add(TPEP_TITLEITEM_DESCRIPTION);
			if (TPEP_TITLEITEMS_DEFAULT & TPEP_TITLEITEM_VALUE) nColumns.Add(TPEP_TITLEITEM_VALUE);
			if (TPEP_TITLEITEMS_DEFAULT & TPEP_TITLEITEM_UNIT) nColumns.Add(TPEP_TITLEITEM_UNIT);
			if (TPEP_TITLEITEMS_DEFAULT & TPEP_TITLEITEM_CHANGETMUNIT) nColumns.Add(TPEP_TITLEITEM_CHANGETMUNIT);
			if (TPEP_TITLEITEMS_DEFAULT & TPEP_TITLEITEM_CHANGETIME) nColumns.Add(TPEP_TITLEITEM_CHANGETIME);
			if (TPEP_TITLEITEMS_DEFAULT & TPEP_TITLEITEM_UPDATETMUNIT) nColumns.Add(TPEP_TITLEITEM_UPDATETMUNIT);
			if (TPEP_TITLEITEMS_DEFAULT & TPEP_TITLEITEM_UPDATETIME) nColumns.Add(TPEP_TITLEITEM_UPDATETIME);
			return TRUE;
		}
		nColumns.Copy(m_nLayoutColumns);
		return((m_nLayoutColumns.GetSize() == nColumns.GetSize()) ? TRUE : FALSE);
	}
	if (IsDlgButtonChecked(IDC_TPEP_OPEN_TYPE_SIMPLE))
	{
		nColumns.SetAtGrow(0, TPEP_TITLEITEM_MESSAGES);
		nColumns.SetSize(1);
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPOpenDialog::GetLayoutTitleFont(LPLOGFONT pTitleFont) CONST
{
	if (IsLayoutModified())
	{
		CopyMemory(pTitleFont, &m_fntLayoutTitle, sizeof(LOGFONT));
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPOpenDialog::GetLayoutMessagesFont(LPLOGFONT pMessagesFont) CONST
{
	if (IsLayoutModified())
	{
		CopyMemory(pMessagesFont, &m_fntLayoutMessages, sizeof(LOGFONT));
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPOpenDialog::GetLayoutToolTipMode(BOOL &bEnable) CONST
{
	if (IsLayoutModified())
	{
		bEnable = m_bLayoutToolTips;
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPOpenDialog::IsLayoutModified() CONST
{
	LOGFONT  fntSample = { 0 };

	return((m_nLayoutColumns.GetSize() > 0 || memcmp(&m_fntLayoutTitle, &fntSample, sizeof(LOGFONT)) || memcmp(&m_fntLayoutMessages, &fntSample, sizeof(LOGFONT)) || m_bLayoutToolTips) ? TRUE : FALSE);
}

BOOL CTPEPOpenDialog::GetFilterMode(UINT &nMode) CONST
{
	if (IsFilteringModified())
	{
		nMode = m_nFilterMode;
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPOpenDialog::GetFilterLimit(UINT &nLimit) CONST
{
	if (IsFilteringModified())
	{
		nLimit = m_nFilterLimit;
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPOpenDialog::GetFilterDigits(UINT &nDigits) CONST
{
	if (IsFilteringModified())
	{
		nDigits = m_nFilterDigits;
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPOpenDialog::GetFilterStatus(UINT &nStatus) CONST
{
	if (IsFilteringModified())
	{
		nStatus = m_nFilterStatus;
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPOpenDialog::GetFilterRange(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	if (IsFilteringModified())
	{
		tStartTime = m_tFilterRange[0][0];
		tStopTime = m_tFilterRange[0][1];
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPOpenDialog::GetFilterDailyRange(CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST
{
	if (IsFilteringModified())
	{
		tStartTime = m_tFilterDailyRange[0];
		tStopTime = m_tFilterDailyRange[1];
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPOpenDialog::GetFilterPeriodicalRange(CTimeKey &tStartTime, CTimeSpan &tInterval, CTimeKey &tStopTime) CONST
{
	if (IsFilteringModified())
	{
		tStartTime = m_tFilterRange[1][0];
		tStopTime = m_tFilterRange[1][1];
		tInterval = m_tFilterPeriodical;
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPOpenDialog::GetFilterColors(COLORREF &nColor, CUIntArray &nOOLColors) CONST
{
	if (IsFilteringModified())
	{
		nColor = m_nFilterColor;
		nOOLColors.Copy(m_nFilterOOLColors);
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPOpenDialog::IsFilteringModified() CONST
{
	return((m_nFilterMode || m_nFilterDigits > 0 || m_nFilterOOLColors.GetSize() > 0) ? TRUE : FALSE);
}

BOOL CTPEPOpenDialog::GetPrintJobs(CTPEPPrintJobs &pPrintJobs) CONST
{
	CByteArray  nPrintInfo;

	return((IsPrintingModified()) ? pPrintJobs.Copy(&m_pPrintJobs) : pPrintJobs.Unmap(nPrintInfo));
}

BOOL CTPEPOpenDialog::IsPrintingModified() CONST
{
	return((m_pPrintJobs.GetSize() > 0) ? TRUE : FALSE);
}

CTPEPWnd *CTPEPOpenDialog::GetParent() CONST
{
	return((CTPEPWnd *)CDisplayDialog::GetParent());
}

BOOL CTPEPOpenDialog::EnumConnections()
{
	INT  nItem[2];
	INT  nItems[2];
	INT  nColumn;
	INT  nColumns;
	INT  nPacket;
	INT  nPackets;
	INT  nParameter;
	INT  nParameters;
	UINT  nConnectionMode;
	CHAR  szHost[1024];
	CString  szItem[2];
	CString  szHostComputer;
	CStringArray  szServers;
	CStringArray  szClients;
	CStringArray  szPackets;
	CStringArray  szParameters;
	CComputerToken  cComputerToken;

	for (nItem[0] = 0, nItems[0] = GetTPEPService()->GetClientConnections(szServers, m_pConnections[0]), m_szServers.Copy(szServers); nItem[0] < nItems[0]; nItem[0]++)
	{
		for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), m_szClients.InsertAt(nItem[0], cComputerToken.GetComputerName()); nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TPEPOPENDIALOG_TITLEITEM_SERVERNAME); )
			{
				szItem[0] = m_szServers.GetAt(nItem[0]);
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TPEPOPENDIALOG_TITLEITEM_CLIENTNAME); )
			{
				szItem[0] = m_szClients.GetAt(nItem[0]);
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TPEPOPENDIALOG_TITLEITEM_DESCRIPTION); )
			{
				for (nPacket = 0, nPackets = m_pConnections[0].GetAt(nItem[0])->GetPackets(szPackets); nPacket < nPackets; nPacket++)
				{
					szItem[0] = (nPacket > 0) ? (szItem[0] + STRING(IDS_TPEPOPENDIALOG_SAMPLE_SEPARATOR) + szPackets.GetAt(nPacket)) : (STRING(IDS_TPEPOPENDIALOG_TYPE_PACKETS) + szPackets.GetAt(nPacket));
					continue;
				}
				for (nParameter = 0, nParameters = m_pConnections[0].GetAt(nItem[0])->GetParameters(szParameters); nParameter < nParameters; nParameter++)
				{
					szItem[0] = (nParameter > 0) ? (szItem[0] + STRING(IDS_TPEPOPENDIALOG_SAMPLE_SEPARATOR) + szParameters.GetAt(nParameter)) : (STRING(IDS_TPEPOPENDIALOG_TYPE_PARAMETERS) + szParameters.GetAt(nParameter));
					continue;
				}
				szItem[0] += (!szItem[0].IsEmpty()) ? (((nConnectionMode = m_pConnections[0].GetAt(nItem[0])->GetDataMode()) == TPEP_DATAMODE_REALTIME) ? (CString(SPACE) + STRING(IDS_TPEPOPENDIALOG_MODE_REALTIME)) : ((nConnectionMode == TPEP_DATAMODE_HISTORY) ? (CString(SPACE) + STRING(IDS_TPEPOPENDIALOG_MODE_HISTORY)) : ((nConnectionMode == TPEP_DATAMODE_RANDOM) ? (CString(SPACE) + STRING(IDS_TPEPOPENDIALOG_MODE_RANDOM)) : EMPTYSTRING))) : STRING(IDS_TPEPOPENDIALOG_SAMPLE_UNKNOWN);
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_TPEP_OPEN_CONNECTION), nItem[0], szItem[0]);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_TPEP_OPEN_CONNECTION), nItem[0], nColumn, szItem[0]);
		}
	}
	gethostname(szHost, sizeof(szHost) / sizeof(CHAR));
#ifndef UNICODE
	szHostComputer = szHost;
#else
	MultiByteToWideChar(CP_ACP, 0, szHost, -1, szHostComputer.GetBufferSetLength((INT)strlen(szHost)), (INT)(strlen(szHost) + 1));
	szHostComputer.ReleaseBuffer();
#endif
	for (nItem[1] = 0, nItems[1] = GetTPEPService()->GetServerConnections(szClients, m_pConnections[1]), m_szClients.Append(szClients); nItem[1] < nItems[1]; nItem[1]++)
	{
		for (m_szServers.InsertAt(nItems[0] + nItem[1], cComputerToken.GetComputerName()), nItem[0] = (m_szServers.GetAt(nItems[0] + nItem[1]) != m_szClients.GetAt(nItems[0] + nItem[1]) && (m_szServers.GetAt(nItems[0] + nItem[1]) != cComputerToken.GetComputerName() || m_szClients.GetAt(nItems[0] + nItem[1]) != szHostComputer) && (m_szServers.GetAt(nItems[0] + nItem[1]) != szHostComputer || m_szClients.GetAt(nItems[0] + nItem[1]) != cComputerToken.GetComputerName())) ? nItems[0] : 0; nItem[0] < nItems[0]; nItem[0]++)
		{
			if (m_pConnections[1][nItem[1]]->Compare(m_pConnections[0][nItem[0]])) break;
			continue;
		}
		if (nItem[0] < nItems[0])
		{
			m_szServers.RemoveAt(nItems[0] + nItem[1]);
			m_szClients.RemoveAt(nItems[0] + nItem[1]);
			delete m_pConnections[1].GetAt(nItem[1]);
			m_pConnections[1].RemoveAt(nItem[1]);
			nItems[1]--;
			nItem[1]--;
			continue;
		}
		for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TPEPOPENDIALOG_TITLEITEM_SERVERNAME);)
			{
				szItem[1] = m_szServers.GetAt(nItems[0] + nItem[1]);
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TPEPOPENDIALOG_TITLEITEM_CLIENTNAME); )
			{
				szItem[1] = m_szClients.GetAt(nItems[0] + nItem[1]);
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_TPEPOPENDIALOG_TITLEITEM_DESCRIPTION); )
			{
				for (nPacket = 0, nPackets = m_pConnections[1].GetAt(nItem[1])->GetPackets(szPackets); nPacket < nPackets; nPacket++)
				{
					szItem[1] = (nPacket > 0) ? (szItem[1] + STRING(IDS_TPEPOPENDIALOG_SAMPLE_SEPARATOR) + szPackets.GetAt(nPacket)) : (STRING(IDS_TPEPOPENDIALOG_TYPE_PACKETS) + szPackets.GetAt(nPacket));
					continue;
				}
				for (nParameter = 0, nParameters = m_pConnections[1].GetAt(nItem[1])->GetParameters(szParameters); nParameter < nParameters; nParameter++)
				{
					szItem[1] = (nParameter > 0) ? (szItem[1] + STRING(IDS_TPEPOPENDIALOG_SAMPLE_SEPARATOR) + szParameters.GetAt(nParameter)) : (STRING(IDS_TPEPOPENDIALOG_TYPE_PARAMETERS) + szParameters.GetAt(nParameter));
					continue;
				}
				szItem[1] += (!szItem[1].IsEmpty()) ? (((nConnectionMode = m_pConnections[1].GetAt(nItem[1])->GetDataMode()) == TPEP_DATAMODE_REALTIME) ? (CString(SPACE) + STRING(IDS_TPEPOPENDIALOG_MODE_REALTIME)) : ((nConnectionMode == TPEP_DATAMODE_HISTORY) ? (CString(SPACE) + STRING(IDS_TPEPOPENDIALOG_MODE_HISTORY)) : ((nConnectionMode == TPEP_DATAMODE_RANDOM) ? (CString(SPACE) + STRING(IDS_TPEPOPENDIALOG_MODE_RANDOM)) : EMPTYSTRING))) : STRING(IDS_TPEPOPENDIALOG_SAMPLE_UNKNOWN);
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_TPEP_OPEN_CONNECTION), nItems[0] + nItem[1], szItem[1]);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_TPEP_OPEN_CONNECTION), nItems[0] + nItem[1], nColumn, szItem[1]);
		}
	}
	Listview_SetCurText(GetDlgItem(IDC_TPEP_OPEN_CONNECTION), 0);
	return TRUE;
}

INT CTPEPOpenDialog::FindConnection(LPCTSTR pszServer, LPCTSTR pszClient, CONST CTPEPConnection *pConnection) CONST
{
	INT  nConnection;
	INT  nConnections;

	for (nConnection = 0, nConnections = (INT)(m_pConnections[0].GetSize() + m_pConnections[1].GetSize()); nConnection < nConnections; nConnection++)
	{
		if (!m_szServers.GetAt(nConnection).CompareNoCase(pszServer) && !m_szClients.GetAt(nConnection).CompareNoCase(pszClient))
		{
			if ((nConnection < m_pConnections[0].GetSize() && m_pConnections[0].GetAt(nConnection)->Compare(pConnection))) break;
			if ((nConnection >= m_pConnections[0].GetSize() && m_pConnections[1].GetAt((INT)(nConnection - m_pConnections[0].GetSize()))->Compare(pConnection))) break;
		}
	}
	return((nConnection < nConnections) ? nConnection : -1);
}

BOOL CTPEPOpenDialog::Check(BOOL bModified) CONST
{
	CString  szComputer;
	CTPEPConnection  cConnection;
	BOOL  bConnection;

	return((GetConnection(szComputer, &cConnection, bConnection)) ? cConnection.IsInitialized() : FALSE);
}

void CTPEPOpenDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTPEPOpenDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CTPEPOpenDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_szServers.RemoveAll();
	m_szClients.RemoveAll();
	m_pPrintJobs.RemoveAll();
	m_nLayoutColumns.RemoveAll();
	m_pConnections[0].RemoveAll();
	m_pConnections[1].RemoveAll();
	m_nFilterOOLColors.RemoveAll();
	CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CTPEPOpenDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CTPEPOpenDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_TPEP_OPEN_SETTINGS, OnSettings)
	ON_BN_CLICKED(IDC_TPEP_OPEN_FIND, OnFind)
	ON_BN_CLICKED(IDC_TPEP_OPEN_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTPEPOpenDialog message handlers

BOOL CTPEPOpenDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	BOOL  bConnection;
	CRect  rColumns;
	CString  szComputer;
	CTPEPConnection  cConnection;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	m_szColumns.Add(STRING(IDS_TPEPOPENDIALOG_TITLEITEM_SERVERNAME));
	m_szColumns.Add(STRING(IDS_TPEPOPENDIALOG_TITLEITEM_CLIENTNAME));
	m_szColumns.Add(STRING(IDS_TPEPOPENDIALOG_TITLEITEM_DESCRIPTION));
	GetDlgItem(IDC_TPEP_OPEN_CONNECTION)->GetClientRect(rColumns);
	CheckRadioButton(IDC_TPEP_OPEN_TYPE_NORMAL, IDC_TPEP_OPEN_TYPE_SIMPLE, IDC_TPEP_OPEN_TYPE_SIMPLE);
	SendDlgItemMessage(IDC_TPEP_OPEN_CONNECTION, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = rColumns.Width() / 4; nColumn < nColumns; nWidth = (++nColumn == nColumns - 1) ? (3 * rColumns.Width() / 2 - nColumn*nWidth) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_TPEP_OPEN_CONNECTION), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	EnumConnections();
	GetConnection(szComputer, &cConnection, bConnection);
	GetDlgItem(IDC_TPEP_OPEN_DETAILS)->EnableWindow();
	GetDlgItem(IDC_TPEP_OPEN_TYPE)->EnableWindow();
	GetDlgItem(IDC_TPEP_OPEN_TYPE_NORMAL)->EnableWindow((cConnection.GetType() == TPEP_TYPE_PARAMETERS) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEP_OPEN_TYPE_SIMPLE)->EnableWindow((cConnection.GetType() == TPEP_TYPE_PACKETS || cConnection.GetType() == TPEP_TYPE_PARAMETERS) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEP_OPEN_CONNECTION_STATIC)->EnableWindow((SendDlgItemMessage(IDC_TPEP_OPEN_CONNECTION, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEP_OPEN_CONNECTION)->EnableWindow((SendDlgItemMessage(IDC_TPEP_OPEN_CONNECTION, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEP_OPEN_SETTINGS)->EnableWindow((SendDlgItemMessage(IDC_TPEP_OPEN_CONNECTION, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_TPEP_OPEN_FIND)->EnableWindow((SendDlgItemMessage(IDC_TPEP_OPEN_CONNECTION, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
	return TRUE;
}

BOOL CTPEPOpenDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	BOOL  bConnection;
	CString  szComputer;
	CTPEPConnection  cConnection;
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_TPEP_OPEN_CONNECTION)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED && (pNotifyListView->uNewState & LVIS_SELECTED))
		{
			if (GetConnection(szComputer, &cConnection, bConnection))
			{
				if (cConnection.GetType() == TPEP_TYPE_PACKETS)
				{
					if (IsDlgButtonChecked(IDC_TPEP_OPEN_TYPE_NORMAL))
					{
						CheckDlgButton(IDC_TPEP_OPEN_TYPE_NORMAL, FALSE);
						CheckDlgButton(IDC_TPEP_OPEN_TYPE_SIMPLE, TRUE);
					}
					GetDlgItem(IDC_TPEP_OPEN_TYPE_NORMAL)->EnableWindow(FALSE);
				}
				if (cConnection.GetType() == TPEP_TYPE_PARAMETERS) GetDlgItem(IDC_TPEP_OPEN_TYPE_NORMAL)->EnableWindow();
			}
			GetDlgItem(IDOK)->EnableWindow(Check());
			return TRUE;
		}
		if (pNotifyListView->hdr.code == NM_DBLCLK  &&  Check())
		{
			OnOK();
			return TRUE;
		}
	}
	return CDisplayDialog::OnNotify(wParam, lParam, pResult);
}

void CTPEPOpenDialog::OnSettings()
{
	ReportEvent((m_dlgSettings.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CTPEPOpenDialog::OnFind()
{
	INT  nIndex;
	INT  nResult;
	CString  szServer;
	CString  szClient;
	CTPEPConnection  cConnection;

	if ((nResult = m_dlgFindDisplay.Create(this, szServer, szClient, &cConnection)) == IDOK)
	{
		for (; (nIndex = FindConnection(szServer, szClient, &cConnection)) >= 0; )
		{
			Listview_SetCurText(GetDlgItem(IDC_TPEP_OPEN_CONNECTION), nIndex);
			break;
		}
	}
	ReportEvent((nResult <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
	GetDlgItem(IDC_TPEP_OPEN_CONNECTION)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

BOOL CTPEPOpenDialog::OnCloseSettingsDialog(UINT nCode)
{
	if (nCode == IDOK)
	{
		if (m_dlgSettings.IsLayoutModified())
		{
			m_dlgSettings.GetLayoutColumns(m_nLayoutColumns);
			m_dlgSettings.GetLayoutTitleFont(&m_fntLayoutTitle);
			m_dlgSettings.GetLayoutMessagesFont(&m_fntLayoutMessages);
			m_dlgSettings.GetLayoutToolTipMode(m_bLayoutToolTips);
		}
		if (m_dlgSettings.IsFilteringModified())
		{
			m_dlgSettings.GetFilterMode(m_nFilterMode);
			m_dlgSettings.GetFilterLimit(m_nFilterLimit);
			m_dlgSettings.GetFilterDigits(m_nFilterDigits);
			m_dlgSettings.GetFilterStatus(m_nFilterStatus);
			m_dlgSettings.GetFilterRange(m_tFilterRange[0][0], m_tFilterRange[0][1]);
			m_dlgSettings.GetFilterDailyRange(m_tFilterDailyRange[0], m_tFilterDailyRange[1]);
			m_dlgSettings.GetFilterPeriodicalRange(m_tFilterRange[1][0], m_tFilterPeriodical, m_tFilterRange[1][1]);
			m_dlgSettings.GetFilterColors(m_nFilterColor, m_nFilterOOLColors);
		}
		if (m_dlgSettings.IsPrintingModified()) m_dlgSettings.GetPrintJobs(m_pPrintJobs);
	}
	return TRUE;
}

void CTPEPOpenDialog::OnOK()
{
	BOOL  bConnection;
	CString  szComputer;
	CTPEPWnd  *pTPEPWnd[2];
	CTPEPConnection  cConnection;
	CHourglassCursor  cCursor;

	if ((pTPEPWnd[0] = GetParent()))
	{
		if ((pTPEPWnd[1] = (GetConnection(szComputer, &cConnection, bConnection)) ? pTPEPWnd[0]->Find(MAKELONG(DISPLAY_TYPE_TPEP, GetType()), szComputer, &cConnection, bConnection) : (CTPEPWnd *)NULL))
		{
			GetDisplayArea()->ActivateDisplay(pTPEPWnd[1]);
			EndDialog(IDCANCEL);
			return;
		}
		if (!pTPEPWnd[0]->OnCloseOpenDialog(IDOK))
		{
			EndDialog(-1);
			return;
		}
	}
	else
	{
		EndDialog(-1);
		return;
	}
	CDisplayDialog::OnOK();
}

void CTPEPOpenDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	GetParent()->OnCloseOpenDialog(IDCANCEL);
	CDisplayDialog::OnCancel();
}

BOOL CTPEPOpenDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TPEPOPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CTPEPOpenDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_TPEPOPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CTPEPPrintThread

IMPLEMENT_DYNCREATE(CTPEPPrintThread, CThread)

BOOL CTPEPPrintThread::Start(CTPEPWnd *pParentWnd)
{
	return CreateThread(pParentWnd);
}

BOOL CTPEPPrintThread::Stop()
{
	return((DestroyThread() >= 0) ? TRUE : FALSE);
}

BOOL CTPEPPrintThread::SetPrintJobs(CONST CTPEPPrintJobs &pPrintJobs)
{
	INT  nJob[2][2];
	INT  nJobs[2][2];
	CTPEPPrintJobInfo  *pJobInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nJob[0][0] = 0, nJobs[0][0] = (INT)pPrintJobs.GetSize(); nJob[0][0] < nJobs[0][0]; nJob[0][0]++)
	{
		for (nJob[0][1] = 0, nJobs[0][1] = (INT)m_pPrintJobs.GetSize(); nJob[0][1] < nJobs[0][1]; nJob[0][1]++)
		{
			if (pPrintJobs.GetAt(nJob[0][0])->GetName() == m_pPrintJobs.GetAt(nJob[0][1])->GetName())
			{
				if (!pPrintJobs.GetAt(nJob[0][0])->Compare(m_pPrintJobs.GetAt(nJob[0][1]))) m_pPrintJobs.GetAt(nJob[0][1])->Copy(pPrintJobs.GetAt(nJob[0][0]));
				break;
			}
		}
		if (nJob[0][1] == nJobs[0][1])
		{
			if ((pJobInfo = new CTPEPPrintJobInfo))
			{
				pJobInfo->Copy(pPrintJobs.GetAt(nJob[0][0]));
				m_pPrintJobs.Add(pJobInfo);
				continue;
			}
			break;
		}
	}
	for (nJob[1][0] = 0, nJobs[1][0] = (INT)m_pPrintJobs.GetSize(); nJob[1][0] < nJobs[1][0]; nJob[1][0]++)
	{
		for (nJob[1][1] = 0, nJobs[1][1] = (INT)pPrintJobs.GetSize(); nJob[1][1] < nJobs[1][1]; nJob[1][1]++)
		{
			if (pPrintJobs.GetAt(nJob[1][1])->GetName() == m_pPrintJobs.GetAt(nJob[1][0])->GetName()) break;
			continue;
		}
		if (nJob[1][1] == nJobs[1][1])
		{
			delete m_pPrintJobs.GetAt(nJob[1][0]);
			m_pPrintJobs.RemoveAt(nJob[1][0]);
			nJobs[1][0]--;
			nJob[1][0]--;
		}
	}
	return((nJob[0][0] == nJobs[0][0] && nJob[1][0] == nJobs[1][0]) ? m_cEvent.SetEvent() : FALSE);
}

BOOL CTPEPPrintThread::GetPrintJobs(CTPEPPrintJobs &pPrintJobs) CONST
{
	CByteArray  nPrintInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(((m_pPrintJobs.GetSize() > 0 && pPrintJobs.Copy(&m_pPrintJobs)) || pPrintJobs.Unmap(nPrintInfo)) ? TRUE : FALSE);
}

int CTPEPPrintThread::Run()
{
	INT  nJob;
	INT  nJobs;
	BOOL  bJobPrint;
	UINT  nJobStopCount;
	DWORD  dwJobResult;
	TIMEKEY  tJobInterval;
	CTimeKey  tJobTime;
	CTimeKey  tJobStopTime;
	CTimeSpan  tJobDailyTime;
	CTPEPPrintJobInfo  *pJobInfo[2];
	CTPEPWnd  *pTPEPWnd = (CTPEPWnd *)GetThreadInfo();

	for (dwJobResult = 0; Lock(); )
	{
		if (dwJobResult == WAIT_OBJECT_0 + 1 || !dwJobResult)
		{
			for (nJob = 0, nJobs = (INT)m_pPrintJobs.GetSize(); nJob < nJobs; nJob++)
			{
				if ((pJobInfo[0] = m_pPrintJobs.GetAt(nJob)) && (pJobInfo[0]->GetPrintMode() & TPEP_PRINT_ACTIVE))
				{
					if (pJobInfo[0]->GetPrintAtDailyTime(tJobDailyTime) || pJobInfo[0]->GetPrintAtDailyTime(tJobDailyTime, nJobStopCount) || pJobInfo[0]->GetPrintAtDailyTime(tJobDailyTime, tJobStopTime))
					{
						pJobInfo[0]->SetPrintLastDailyTime(((tJobTime = CTime::GetCurrentTime().GetTime()).GetTime() % SECONDSPERDAY >= tJobDailyTime.GetTotalSeconds()) ? ((SECONDSPERDAY*(tJobTime.GetTime() / SECONDSPERDAY)) + tJobDailyTime.GetTotalSeconds()) : ((SECONDSPERDAY*(tJobTime.GetTime() / SECONDSPERDAY - 1)) + tJobDailyTime.GetTotalSeconds()));
						continue;
					}
				}
			}
		}
		if ((pJobInfo[0] = ((tJobInterval = m_pPrintJobs.Schedule()) == 0) ? m_pPrintJobs.GetAt(0) : (CTPEPPrintJobInfo *)NULL))
		{
			for (bJobPrint = pTPEPWnd->Print(pJobInfo[0]); (pJobInfo[0]->GetPrintMode() & TPEP_PRINT_CLEARCOMMENTS) && bJobPrint; )
			{
				for (nJob = 1, nJobs = (INT)m_pPrintJobs.GetSize(); nJob < nJobs; nJob++)
				{
					if ((pJobInfo[1] = m_pPrintJobs.GetAt(nJob)))
					{
						if (pJobInfo[0]->GetName() == pJobInfo[1]->GetName())
						{
							pJobInfo[1]->SetPrintMode(pJobInfo[0]->GetPrintMode() & ~TPEP_PRINT_CLEARCOMMENTS);
							pJobInfo[1]->SetComments(EMPTYSTRING);
							break;
						}
					}
				}
				break;
			}
			ReportEvent((!bJobPrint) ? SYSTEM_WARNING_TPEP_PRINT_FAILURE : SYSTEM_NOERROR);
			m_pPrintJobs.RemoveAt(0);
			delete pJobInfo[0];
		}
		Unlock();
		if ((dwJobResult = Wait(m_cEvent, FALSE, (tJobInterval >= 0) ? (DWORD)(1000 * min(tJobInterval, SECONDSPERDAY)) : INFINITE)) != WAIT_TIMEOUT  &&  dwJobResult != WAIT_OBJECT_0 + 1) break;
	}
	return 0;
}

BEGIN_MESSAGE_MAP(CTPEPPrintThread, CThread)
	//{{AFX_MSG_MAP(CTPEPPrintThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTPEPPrintThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CTPEPToolBar

IMPLEMENT_DYNCREATE(CTPEPToolBar, CDisplayToolBar)

CTPEPToolBar::CTPEPToolBar() : CDisplayToolBar()
{
	return;
}

BEGIN_MESSAGE_MAP(CTPEPToolBar, CDisplayToolBar)
	//{{AFX_MSG_MAP(CTPEPToolBar)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTPEPToolBar message handlers


/////////////////////////////////////////////////////////////////////////////
// CTPEPStatusBar

IMPLEMENT_DYNCREATE(CTPEPStatusBar, CDisplayStatusBar)

CTPEPStatusBar::CTPEPStatusBar() : CDisplayStatusBar()
{
	return;
}

BOOL CTPEPStatusBar::SetIndicators(CONST UINT *pPanesID, INT nCount)
{
	INT  nIndex;
	CRect  rPane;
	CString  szPane;
	CToolInfo  cToolInfo;
	CDisplayLock  cLock(this);

	if (CDisplayStatusBar::SetIndicators(pPanesID, nCount))
	{
		if (CommandToIndex(ID_TPEP_STATUSBAR_MESSAGEPANE) >= 0)
		{
			szPane.Format(STRING(IDS_TPEP_STATUSBAR_UPDATEMESSAGE), (LPCTSTR)CTimeTag().FormatGmt(), (LPCTSTR)CString(CTimeTag().FormatGmt().Right(1), GetDatabase()->GetTMPacketTagLength()), -1, STRING(IDS_TPEP_STATUSBAR_QUALITYGOOD));
			SetPaneInfo(CommandToIndex(ID_TPEP_STATUSBAR_MESSAGEPANE), ID_TPEP_STATUSBAR_MESSAGEPANE, SBPS_NOBORDERS | SBPS_STRETCH, CalcPaneWidth(szPane));
		}
		if (!IsWindow(m_wndToolTip.GetSafeHwnd()))
		{
			m_wndToolTip.Create(this, TTS_ALWAYSTIP | TTS_NOPREFIX | TTS_BALLOON);
			SetClassLongPtr(m_wndToolTip.GetSafeHwnd(), GCL_STYLE, GetClassLongPtr(m_wndToolTip.GetSafeHwnd(), GCL_STYLE) | CS_DROPSHADOW);
		}
		if (IsWindow(m_wndToolTip.GetSafeHwnd()))
		{
			if ((nIndex = CommandToIndex(ID_TPEP_STATUSBAR_COMPUTERPANE)) >= 0)
			{
				for (GetItemRect(nIndex, rPane); !m_wndToolTip.GetToolInfo(cToolInfo, this, ID_TPEP_STATUSBAR_COMPUTERPANE); )
				{
					m_wndToolTip.AddTool(this, LPSTR_TEXTCALLBACK, rPane, ID_TPEP_STATUSBAR_COMPUTERPANE);
					break;
				}
			}
			if ((nIndex = CommandToIndex(ID_TPEP_STATUSBAR_MODEPANE)) >= 0)
			{
				for (GetItemRect(nIndex, rPane); !m_wndToolTip.GetToolInfo(cToolInfo, this, ID_TPEP_STATUSBAR_MODEPANE); )
				{
					m_wndToolTip.AddTool(this, LPSTR_TEXTCALLBACK, rPane, ID_TPEP_STATUSBAR_MODEPANE);
					break;
				}
			}
			if ((nIndex = CommandToIndex(ID_TPEP_STATUSBAR_TYPEPANE)) >= 0)
			{
				for (GetItemRect(nIndex, rPane); !m_wndToolTip.GetToolInfo(cToolInfo, this, ID_TPEP_STATUSBAR_TYPEPANE); )
				{
					m_wndToolTip.AddTool(this, LPSTR_TEXTCALLBACK, rPane, ID_TPEP_STATUSBAR_TYPEPANE);
					break;
				}
			}
			m_wndToolTip.SetMaxTipWidth(GetSystemMetrics(SM_CXSCREEN));
			m_wndToolTip.Activate(TRUE);
		}
		return TRUE;
	}
	return FALSE;
}

CTPEPWnd *CTPEPStatusBar::GetParent() CONST
{
	return((CTPEPWnd *)CDisplayStatusBar::GetParent());
}

BEGIN_MESSAGE_MAP(CTPEPStatusBar, CDisplayStatusBar)
	//{{AFX_MSG_MAP(CTPEPStatusBar)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipNotify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTPEPStatusBar message handlers

void CTPEPStatusBar::OnPaint()
{
	INT  nIndex;
	RECT  rPane;
	CToolInfo  cToolInfo;

	for (CDisplayStatusBar::OnPaint(); IsWindow(m_wndToolTip.GetSafeHwnd()); )
	{
		if ((nIndex = CommandToIndex(ID_TPEP_STATUSBAR_COMPUTERPANE)) >= 0 && nIndex < m_prPanes.GetSize())
		{
			for (m_wndToolTip.GetToolInfo(cToolInfo, this, ID_TPEP_STATUSBAR_COMPUTERPANE), CopyMemory(&rPane, m_prPanes.GetAt(nIndex), sizeof(RECT)); !EqualRect(&cToolInfo.rect, &rPane); )
			{
				SetRect(&cToolInfo.rect, rPane.left, rPane.top, rPane.right, rPane.bottom);
				m_wndToolTip.SetToolInfo(&cToolInfo);
				break;
			}
		}
		if ((nIndex = CommandToIndex(ID_TPEP_STATUSBAR_MODEPANE)) >= 0 && nIndex < m_prPanes.GetSize())
		{
			for (m_wndToolTip.GetToolInfo(cToolInfo, this, ID_TPEP_STATUSBAR_MODEPANE), CopyMemory(&rPane, m_prPanes.GetAt(nIndex), sizeof(RECT)); !EqualRect(&cToolInfo.rect, &rPane); )
			{
				SetRect(&cToolInfo.rect, rPane.left, rPane.top, rPane.right, rPane.bottom);
				m_wndToolTip.SetToolInfo(&cToolInfo);
				break;
			}
		}
		if ((nIndex = CommandToIndex(ID_TPEP_STATUSBAR_TYPEPANE)) >= 0 && nIndex < m_prPanes.GetSize())
		{
			for (m_wndToolTip.GetToolInfo(cToolInfo, this, ID_TPEP_STATUSBAR_TYPEPANE), CopyMemory(&rPane, m_prPanes.GetAt(nIndex), sizeof(RECT)); !EqualRect(&cToolInfo.rect, &rPane); )
			{
				SetRect(&cToolInfo.rect, rPane.left, rPane.top, rPane.right, rPane.bottom);
				m_wndToolTip.SetToolInfo(&cToolInfo);
				break;
			}
		}
		break;
	}
}

void CTPEPStatusBar::OnMouseMove(UINT nFlags, CPoint point)
{
	MSG  sMsg;

	if (IsWindow(m_wndToolTip.GetSafeHwnd()))
	{
		CopyMemory(&sMsg, GetCurrentMessage(), sizeof(MSG));
		m_wndToolTip.RelayEvent(&sMsg);
	}
	CDisplayStatusBar::OnMouseMove(nFlags, point);
}

BOOL CTPEPStatusBar::OnToolTipNotify(UINT nID, NMHDR *pNotifyInfo, LRESULT *pResult)
{
	TOOLTIPTEXT  *pToolTipInfo = (TOOLTIPTEXT *)pNotifyInfo;

	switch (pNotifyInfo->idFrom)
	{
	case ID_TPEP_STATUSBAR_COMPUTERPANE:
	{ pToolTipInfo->lpszText = (LPTSTR)STRING(IDS_TPEP_STATUSBAR_COMPUTERPANE);
	return TRUE;
	}
	case ID_TPEP_STATUSBAR_MODEPANE:
	{ pToolTipInfo->lpszText = (LPTSTR)STRING(IDS_TPEP_STATUSBAR_MODEPANE);
	return TRUE;
	}
	case ID_TPEP_STATUSBAR_TYPEPANE:
	{ pToolTipInfo->lpszText = (LPTSTR)STRING(IDS_TPEP_STATUSBAR_TYPEPANE);
	return TRUE;
	}
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CTPEPToolTip

IMPLEMENT_DYNCREATE(CTPEPToolTip, CDisplayToolTip)

CTPEPToolTip::CTPEPToolTip() : CDisplayToolTip()
{
	return;
}

BEGIN_MESSAGE_MAP(CTPEPToolTip, CDisplayToolTip)
	//{{AFX_MSG_MAP(CTPEPToolTip)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTPEPToolTip message handlers


/////////////////////////////////////////////////////////////////////////////
// CTPEPDataContainer

IMPLEMENT_DYNCREATE(CTPEPDataContainer, CTextView)

CTPEPDataContainer::CTPEPDataContainer() : CTextView()
{
	m_nType = 0;
	m_nFilterMode = 0;
	m_nFilterLimit = 0;
	m_nFilterDigits = 0;
	m_nFilterStatus = 0;
	m_nFilterColor = 0;
	m_tFilterRange[0][0] = 0;
	m_tFilterRange[0][1] = 0;
	m_tFilterRange[1][0] = 0;
	m_tFilterRange[1][1] = 0;
	m_tFilterDailyRange[0] = 0;
	m_tFilterDailyRange[1] = 0;
	m_tFilterPeriodical = 0;
	m_nParameterCount = 0;
	m_bToolTipMode = TRUE;
	m_bConnection = FALSE;
}

BOOL CTPEPDataContainer::SetLayout(UINT nType)
{
	CTextViewLock  cLock(this);

	for (m_nType = nType; nType == TPEP_TYPE_SIMPLE || nType == TPEP_TYPE_NORMAL; )
	{
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPDataContainer::GetLayout(UINT &nType) CONST
{
	CTextViewLock  cLock(this);

	return(((nType = m_nType) == TPEP_TYPE_SIMPLE || nType == TPEP_TYPE_NORMAL) ? TRUE : FALSE);
}

BOOL CTPEPDataContainer::SetLayoutColumns(CONST CUIntArray &nColumns)
{
	CUIntArray  nWidths;
	CTextViewLock  cLock(this);

	return(((m_nType == TPEP_TYPE_NORMAL  &&  CalcColumnsWidth(nColumns, nWidths) > 0 && SetLayoutColumns(nColumns, nWidths)) || (m_nType == TPEP_TYPE_SIMPLE  &&  SetLayoutColumns(nColumns, nWidths))) ? TRUE : FALSE);
}
BOOL CTPEPDataContainer::SetLayoutColumns(CONST CUIntArray &nColumns, CONST CUIntArray &nWidths)
{
	INT  nIndex;
	INT  nCount;
	LOGFONT  lfFont;
	CStringArray  szColumns;
	CTextViewLock  cLock(this);

	for (nIndex = 0, nCount = (GetColumns(szColumns)) ? (INT)szColumns.GetSize() : 0; nIndex < nCount; nIndex++)
	{
		if (nIndex >= nColumns.GetSize() || nCount != nColumns.GetSize() || LookupColumnName(szColumns.GetAt(nIndex)) != nColumns.GetAt(nIndex))
		{
			ClearAllMessages();
			break;
		}
	}
	if ((m_nType == TPEP_TYPE_NORMAL  &&  LookupColumnsName(nColumns, szColumns) && SetColumns(szColumns, nWidths)) || m_nType == TPEP_TYPE_SIMPLE)
	{
		for (nIndex = 0, nCount = (m_nType == TPEP_TYPE_NORMAL) ? (INT)nColumns.GetSize() : 0, m_nLayoutColumns.Copy(nColumns); nIndex < nCount; nIndex++)
		{
			if (nColumns.GetAt(nIndex) == TPEP_TITLEITEM_VALUE)
			{
				if (GetMessagesFont(&lfFont, TRUE))
				{
					SetColumnFont(nIndex, &lfFont, FALSE);
					continue;
				}
			}
		}
		AdjustColumns();
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPDataContainer::GetLayoutColumns(CUIntArray &nColumns) CONST
{
	CTextViewLock  cLock(this);

	if (m_nType == TPEP_TYPE_NORMAL)
	{
		for (nColumns.RemoveAll(); !m_nLayoutColumns.GetSize(); )
		{
			if (TPEP_TITLEITEMS_DEFAULT & TPEP_TITLEITEM_ID) nColumns.Add(TPEP_TITLEITEM_ID);
			if (TPEP_TITLEITEMS_DEFAULT & TPEP_TITLEITEM_DESCRIPTION) nColumns.Add(TPEP_TITLEITEM_DESCRIPTION);
			if (TPEP_TITLEITEMS_DEFAULT & TPEP_TITLEITEM_VALUE) nColumns.Add(TPEP_TITLEITEM_VALUE);
			if (TPEP_TITLEITEMS_DEFAULT & TPEP_TITLEITEM_UNIT) nColumns.Add(TPEP_TITLEITEM_UNIT);
			if (TPEP_TITLEITEMS_DEFAULT & TPEP_TITLEITEM_CHANGETMUNIT) nColumns.Add(TPEP_TITLEITEM_CHANGETMUNIT);
			if (TPEP_TITLEITEMS_DEFAULT & TPEP_TITLEITEM_CHANGETIME) nColumns.Add(TPEP_TITLEITEM_CHANGETIME);
			if (TPEP_TITLEITEMS_DEFAULT & TPEP_TITLEITEM_UPDATETMUNIT) nColumns.Add(TPEP_TITLEITEM_UPDATETMUNIT);
			if (TPEP_TITLEITEMS_DEFAULT & TPEP_TITLEITEM_UPDATETIME) nColumns.Add(TPEP_TITLEITEM_UPDATETIME);
			return TRUE;
		}
		nColumns.Copy(m_nLayoutColumns);
		return TRUE;
	}
	if (m_nType == TPEP_TYPE_SIMPLE)
	{
		nColumns.SetAtGrow(0, TPEP_TITLEITEM_MESSAGES);
		nColumns.SetSize(1);
		return TRUE;
	}
	return FALSE;
}
BOOL CTPEPDataContainer::GetLayoutColumns(CUIntArray &nColumns, CUIntArray &nWidths) CONST
{
	CRect  rView;
	CTextViewLock  cLock(this);

	for (nColumns.RemoveAll(), nWidths.RemoveAll(); m_nType == TPEP_TYPE_NORMAL; )
	{
		nColumns.Copy(m_nLayoutColumns);
		nWidths.Copy(m_wndHeaderCtrl.m_nColumnsWidth);
		return TRUE;
	}
	if (m_nType == TPEP_TYPE_SIMPLE)
	{
		for (GetClientRect(rView); GetLayoutColumns(nColumns); )
		{
			nWidths.Add(rView.Width());
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CTPEPDataContainer::SetTitleFont(CONST LOGFONT *plfFont)
{
	return CTextView::SetTitleFont(plfFont);
}

BOOL CTPEPDataContainer::GetTitleFont(LOGFONT *plfFont) CONST
{
	return CTextView::GetTitleFont(plfFont);
}

BOOL CTPEPDataContainer::SetMessagesFont(CONST LOGFONT *plfFont)
{
	return SetTextFont(plfFont);
}

BOOL CTPEPDataContainer::GetMessagesFont(LOGFONT *plfFont, BOOL bValues) CONST
{
	if (GetTextFont(plfFont))
	{
		plfFont->lfWeight = (bValues) ? FW_BOLD : plfFont->lfWeight;
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPDataContainer::EnableToolTipMode(BOOL bEnable)
{
	m_bToolTipMode = bEnable;
	return TRUE;
}

BOOL CTPEPDataContainer::IsToolTipModeEnabled() CONST
{
	return m_bToolTipMode;
}

BOOL CTPEPDataContainer::SetFilterMode(UINT nMode)
{
	m_nFilterMode = nMode;
	return TRUE;
}

BOOL CTPEPDataContainer::GetFilterMode(UINT &nMode) CONST
{
	nMode = m_nFilterMode;
	return TRUE;
}

BOOL CTPEPDataContainer::SetFilterLimit(UINT nLimit)
{
	CTextViewLock  cLock(this);

	if (m_nFilterMode & TPEP_FILTER_LIMIT)
	{
		m_nFilterLimit = nLimit;
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPDataContainer::GetFilterLimit(UINT &nLimit) CONST
{
	CTextViewLock  cLock(this);

	if (m_nFilterMode & TPEP_FILTER_LIMIT)
	{
		nLimit = m_nFilterLimit;
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPDataContainer::SetFilterStatus(UINT nStatus)
{
	CTextViewLock  cLock(this);

	if (m_nFilterMode & TPEP_FILTER_STATUS)
	{
		m_nFilterStatus = nStatus;
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPDataContainer::GetFilterStatus(UINT &nStatus) CONST
{
	CTextViewLock  cLock(this);

	if (m_nFilterMode & TPEP_FILTER_STATUS)
	{
		nStatus = m_nFilterStatus;
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPDataContainer::SetFilterRange(CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime)
{
	CTextViewLock  cLock(this);

	if (m_nFilterMode & TPEP_FILTER_RANGE)
	{
		m_tFilterRange[0][0] = tStartTime.GetTime();
		m_tFilterRange[0][1] = tStopTime.GetTime();
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPDataContainer::GetFilterRange(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	CTextViewLock  cLock(this);

	if (m_nFilterMode & TPEP_FILTER_RANGE)
	{
		tStartTime = m_tFilterRange[0][0];
		tStopTime = m_tFilterRange[0][1];
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPDataContainer::SetFilterDailyRange(CONST CTimeSpan &tStartTime, CONST CTimeSpan &tStopTime)
{
	CTextViewLock  cLock(this);

	if (m_nFilterMode & TPEP_FILTER_DAILYRANGE)
	{
		m_tFilterDailyRange[0] = tStartTime;
		m_tFilterDailyRange[1] = tStopTime;
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPDataContainer::GetFilterDailyRange(CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST
{
	CTextViewLock  cLock(this);

	if (m_nFilterMode & TPEP_FILTER_DAILYRANGE)
	{
		tStartTime = m_tFilterDailyRange[0];
		tStopTime = m_tFilterDailyRange[1];
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPDataContainer::SetFilterPeriodicalRange(CONST CTimeKey &tStartTime, CONST CTimeSpan &tInterval, CONST CTimeKey &tStopTime)
{
	CTextViewLock  cLock(this);

	if (m_nFilterMode & TPEP_FILTER_PERIODICALRANGE)
	{
		m_tFilterRange[1][0] = tStartTime;
		m_tFilterRange[1][1] = tStopTime;
		m_tFilterPeriodical = tInterval;
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPDataContainer::GetFilterPeriodicalRange(CTimeKey &tStartTime, CTimeSpan &tInterval, CTimeKey &tStopTime) CONST
{
	CTextViewLock  cLock(this);

	if (m_nFilterMode & TPEP_FILTER_PERIODICALRANGE)
	{
		tStartTime = m_tFilterRange[1][0];
		tStopTime = m_tFilterRange[1][1];
		tInterval = m_tFilterPeriodical;
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPDataContainer::SetFilterDigits(UINT nDigits)
{
	m_nFilterDigits = nDigits;
	return TRUE;
}

BOOL CTPEPDataContainer::GetFilterDigits(UINT &nDigits) CONST
{
	nDigits = m_nFilterDigits;
	return TRUE;
}

BOOL CTPEPDataContainer::SetFilterColors()
{
	CTextViewLock  cLock(this);

	m_nFilterOOLColors.RemoveAll();
	m_nFilterOOLColors.InsertAt(TPEP_OOLCOLOR_NOLIMIT, VGA_COLOR_BLACK);
	m_nFilterOOLColors.InsertAt(TPEP_OOLCOLOR_SOFTLIMIT, VGA_COLOR_RED);
	m_nFilterOOLColors.InsertAt(TPEP_OOLCOLOR_HARDLIMIT, VGA_COLOR_LTRED);
	m_nFilterOOLColors.InsertAt(TPEP_OOLCOLOR_DELTALIMIT, VGA_COLOR_MAGENTA);
	m_nFilterOOLColors.InsertAt(TPEP_OOLCOLOR_CONSISTENCYLIMIT, VGA_COLOR_YELLOW);
	return TRUE;
}
BOOL CTPEPDataContainer::SetFilterColors(COLORREF nColor, CONST CUIntArray &nOOLColors)
{
	INT  nIndex;
	INT  nCount;
	CTextViewLock  cLock(this);

	for (nIndex = 0, nCount = (INT)nOOLColors.GetSize(), m_nFilterColor = nColor; nIndex < nCount; nIndex++)
	{
		m_nFilterOOLColors.SetAtGrow(nIndex, nOOLColors.GetAt(nIndex));
		continue;
	}
	return(nOOLColors.GetSize() > 0);
}

BOOL CTPEPDataContainer::GetFilterColors(COLORREF &nColor, CUIntArray &nOOLColors) CONST
{
	CTextViewLock  cLock(this);

	nColor = m_nFilterColor;
	nOOLColors.Copy(m_nFilterOOLColors);
	return(nOOLColors.GetSize() > 0);
}

BOOL CTPEPDataContainer::SetAlerts(CONST CTPEPAlerts &pAlerts)
{
	CTextViewLock  cLock(this);

	return m_pAlerts.Copy(&pAlerts);
}

BOOL CTPEPDataContainer::GetAlerts(CTPEPAlerts &pAlerts) CONST
{
	CTextViewLock  cLock(this);

	return pAlerts.Copy(&m_pAlerts);
}

BOOL CTPEPDataContainer::AddMessage(LPCTSTR pszMessage)
{
	INT  nRow;
	INT  nIndex;
	INT  nAlert;
	INT  nAlerts;
	INT  nTable;
	INT  nTables;
	INT  nPoint;
	INT  nPoints;
	INT  nColumn;
	INT  nParameter;
	INT  nParameters;
	BOOL  bMessage;
	UINT  nOptions;
	double  fRaw[2];
	double  fValue[2];
	CPoint  ptToolTip;
	CString  szValue;
	CString  szError;
	CString  szMessage;
	CString  szParameter;
	CTPEPAlert  *pAlert;
	CUIntArray  nCalTables[2];
	CStringArray  szErrors;
	CStringArray  szPackets;
	CStringArray  szParameters;
	CTextViewAttribute  cAttribute;
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;
	CTextViewLock  cLock(this);

	if (FilterMessage(pszMessage))
	{
		if ((bMessage = ParseMessage(pszMessage, szMessage, &cAttribute)) && !szMessage.IsEmpty())
		{
			if (InsertText(GetTextCount(), szMessage, &cAttribute) && SetCurText(GetTextCount() - 1))
			{
				for (nAlert = 0, nAlerts = (INT)m_pAlerts.GetSize(); nAlert < nAlerts; nAlert = nAlert + 1)
				{
					if ((pAlert = m_pAlerts.GetAt(nAlert)) && (pAlert->GetOptions() & TPEPALERT_OPTION_DISABLED) != TPEPALERT_OPTION_DISABLED)
					{
						for (nParameter = 0, nParameters = m_cConnection.GetParameters(szParameters); nParameter < nParameters; nParameter++)
						{
							if (szParameters.GetAt(nParameter) == pAlert->GetParameter()) break;
							continue;
						}
						if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pAlert->GetParameter()))) && nParameter < nParameters)
						{
							if ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL))
							{
								if ((nIndex = (GetTextCount() - 1)*nParameters + nParameter) < m_szParameterValues[0].GetSize() && !m_szParameterValues[0].GetAt(nIndex).IsEmpty() && pAlert->GetValue(fValue[0]))
								{
									fValue[1] = _ttof(m_szParameterValues[0].GetAt(nIndex));
									switch (pAlert->GetOperator())
									{
									case TPEPALERT_OPERATOR_BELOW:
									{ if (fValue[1] < fValue[0])
									{
										DoAlert(pAlert);
										break;
									}
									pAlert->SetOptions(pAlert->GetOptions() & ~TPEPALERT_OPTION_ACTIVATED);
									break;
									}
									case TPEPALERT_OPERATOR_ABOVE:
									{ if (fValue[1] > fValue[0])
									{
										DoAlert(pAlert);
										break;
									}
									pAlert->SetOptions(pAlert->GetOptions() & ~TPEPALERT_OPTION_ACTIVATED);
									break;
									}
									case TPEPALERT_OPERATOR_EQUAL:
									{ if (fValue[1] == fValue[0])
									{
										DoAlert(pAlert);
										break;
									}
									pAlert->SetOptions(pAlert->GetOptions() & ~TPEPALERT_OPTION_ACTIVATED);
									break;
									}
									case TPEPALERT_OPERATOR_UNEQUAL:
									{ if (fValue[1] != fValue[0])
									{
										DoAlert(pAlert);
										break;
									}
									pAlert->SetOptions(pAlert->GetOptions() & ~TPEPALERT_OPTION_ACTIVATED);
									break;
									}
									case TPEPALERT_OPERATOR_BELOWEQUAL:
									{ if (fValue[1] <= fValue[0])
									{
										DoAlert(pAlert);
										break;
									}
									pAlert->SetOptions(pAlert->GetOptions() & ~TPEPALERT_OPTION_ACTIVATED);
									break;
									}
									case TPEPALERT_OPERATOR_ABOVEEQUAL:
									{ if (fValue[1] >= fValue[0])
									{
										DoAlert(pAlert);
										break;
									}
									pAlert->SetOptions(pAlert->GetOptions() & ~TPEPALERT_OPTION_ACTIVATED);
									break;
									}
									}
								}
							}
							if (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS)
							{
								for (nTable = 0, nTables = ((nIndex = (GetTextCount() - 1)*nParameters + nParameter) < m_szParameterValues[0].GetSize() && !m_szParameterValues[0].GetAt(nIndex).IsEmpty() && pAlert->GetValue(fValue[0], fValue[1])) ? pDatabaseTMParameter->GetCalTableRefs(nCalTables[0], nCalTables[1]) : 0; nTable < nTables; nTable++)
								{
									for (nPoint = 0, nPoints = ((pDatabaseTMTxtCalTable = GetDatabase()->GetTMTxtCalTables()->GetAt(nCalTables[0].GetAt(nTable)))) ? (INT)pDatabaseTMTxtCalTable->GetSize() : 0; nPoint < nPoints; nPoint++)
									{
										if (pDatabaseTMTxtCalTable->GetAt(nPoint)->GetPoint(fRaw[0], szValue))
										{
											if (szValue == m_szParameterValues[0].GetAt(nIndex))
											{
												fRaw[1] = fRaw[0];
												break;
											}
											continue;
										}
										if (pDatabaseTMTxtCalTable->GetAt(nPoint)->GetRange(fRaw[0], fRaw[1], szValue))
										{
											if (szValue == m_szParameterValues[0].GetAt(nIndex)) break;
											continue;
										}
									}
									if (nPoint < nPoints)
									{
										switch (pAlert->GetOperator())
										{
										case TPEPALERT_OPERATOR_BELOW:
										{ if (fRaw[1] < fValue[0])
										{
											DoAlert(pAlert);
											break;
										}
										pAlert->SetOptions(pAlert->GetOptions() & ~TPEPALERT_OPTION_ACTIVATED);
										break;
										}
										case TPEPALERT_OPERATOR_ABOVE:
										{ if (fRaw[0] > fValue[1])
										{
											DoAlert(pAlert);
											break;
										}
										pAlert->SetOptions(pAlert->GetOptions() & ~TPEPALERT_OPTION_ACTIVATED);
										break;
										}
										case TPEPALERT_OPERATOR_EQUAL:
										{ if (fRaw[0] == fValue[0] && fRaw[1] == fValue[1])
										{
											DoAlert(pAlert);
											break;
										}
										pAlert->SetOptions(pAlert->GetOptions() & ~TPEPALERT_OPTION_ACTIVATED);
										break;
										}
										case TPEPALERT_OPERATOR_UNEQUAL:
										{ if (fRaw[0] != fValue[0] || fRaw[1] != fValue[1])
										{
											DoAlert(pAlert);
											break;
										}
										pAlert->SetOptions(pAlert->GetOptions() & ~TPEPALERT_OPTION_ACTIVATED);
										break;
										}
										case TPEPALERT_OPERATOR_BELOWEQUAL:
										{ if (fRaw[1] <= fValue[1])
										{
											DoAlert(pAlert);
											break;
										}
										pAlert->SetOptions(pAlert->GetOptions() & ~TPEPALERT_OPTION_ACTIVATED);
										break;
										}
										case TPEPALERT_OPERATOR_ABOVEEQUAL:
										{ if (fRaw[0] >= fValue[0])
										{
											DoAlert(pAlert);
											break;
										}
										pAlert->SetOptions(pAlert->GetOptions() & ~TPEPALERT_OPTION_ACTIVATED);
										break;
										}
										}
										break;
									}
								}
							}
						}
					}
					if (pAlert->GetOptions() & TPEPALERT_OPTION_DISABLED)
					{
						nOptions = pAlert->GetOptions() & ~TPEPALERT_OPTION_ACTIVATED;
						pAlert->SetOptions(nOptions);
					}
				}
				if (m_wndToolTip.IsVisibleAtPoint(ptToolTip))
				{
					for (nRow = PointToRow(ptToolTip), nColumn = PointToColumn(ptToolTip); m_nType == TPEP_TYPE_NORMAL && ParseMessage(PointToPoint(ptToolTip), szParameter, szError); )
					{
						m_wndToolTip.Update(ConstructToolTipTitle(szParameter, szError), ConstructToolTipText(PointToPoint(ptToolTip), szParameter, szError));
						break;
					}
					for (; m_nType == TPEP_TYPE_SIMPLE && ParseMessage(m_wndContentCtrl.m_szContentText.GetAt(PointToPoint(ptToolTip).y), szPackets, szParameters, szErrors); )
					{
						m_wndToolTip.Update(ConstructToolTipTitle(szPackets, szParameters), ConstructToolTipText(szPackets, szParameters, szErrors));
						break;
					}
				}
				return TRUE;
			}
			return FALSE;
		}
		return bMessage;
	}
	return FALSE;
}

BOOL CTPEPDataContainer::ClearAllMessages()
{
	CTextViewLock  cLock(this);

	if (DeleteAllText())
	{
		m_szParameterIDs.RemoveAll();
		m_szParameterValues[0].RemoveAll();
		m_szParameterValues[1].RemoveAll();
		m_szParameterPackets[0].RemoveAll();
		m_szParameterPackets[1].RemoveAll();
		m_szParameterTimeTags[0][0].RemoveAll();
		m_szParameterTimeTags[0][1].RemoveAll();
		m_szParameterTimeTags[1][0].RemoveAll();
		m_szParameterTimeTags[1][1].RemoveAll();
		m_nParameterStatus.RemoveAll();
		return TRUE;
	}
	return FALSE;
}

INT CTPEPDataContainer::GetMessageCount() CONST
{
	return GetTextCount();
}

BOOL CTPEPDataContainer::SetConnectionProperties(CONST CTPEPConnection *pConnection)
{
	CTextViewLock  cLock(this);

	m_cConnection.Copy(pConnection);
	return TRUE;
}
BOOL CTPEPDataContainer::SetConnectionProperties(LPCTSTR pszComputer, CONST CTPEPConnection *pConnection, BOOL bConnection)
{
	CTextViewLock  cLock(this);

	m_szConnectionComputer = pszComputer;
	m_cConnection.Copy(pConnection);
	m_bConnection = bConnection;
	return TRUE;
}

BOOL CTPEPDataContainer::GetConnectionProperties(CTPEPConnection *pConnection) CONST
{
	CTextViewLock  cLock(this);

	pConnection->Copy(&m_cConnection);
	return pConnection->IsInitialized();
}
BOOL CTPEPDataContainer::GetConnectionProperties(CString &szComputer, CTPEPConnection *pConnection, BOOL &bConnection) CONST
{
	CTextViewLock  cLock(this);

	szComputer = m_szConnectionComputer;
	pConnection->Copy(&m_cConnection);
	bConnection = m_bConnection;
	return pConnection->IsInitialized();
}

BOOL CTPEPDataContainer::GetPrintProperties(CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, CStringArray &szParameterValues, CUIntArray &nParameterStatus, CUIntArray &nOOLColors, LOGFONT *pTitleFont, LOGFONT *pMessagesFont, LOGFONT *pValuesFont) CONST
{
	CTextViewLock  cLock(this);

	if (((m_nType == TPEP_TYPE_NORMAL  &&  GetColumns(szColumns)) || (m_nType == TPEP_TYPE_SIMPLE  &&  szColumns.Add(STRING(IDS_TPEP_TITLEITEM_MESSAGES)) >= 0)) && GetContent(szContents, pAttributes))
	{
		if (GetTitleFont(pTitleFont) && GetMessagesFont(pMessagesFont) && GetMessagesFont(pValuesFont, TRUE))
		{
			szParameterValues.Copy(m_szParameterValues[0]);
			nParameterStatus.Copy(m_nParameterStatus);
			nOOLColors.Copy(m_nFilterOOLColors);
			return TRUE;
		}
	}
	return FALSE;
}

CTPEPView *CTPEPDataContainer::GetParent() CONST
{
	return((CTPEPView *)CTextView::GetParent());
}

CTPEPWnd *CTPEPDataContainer::GetParentDisplay() CONST
{
	CTPEPView  *pView;

	return(((pView = GetParent())) ? pView->GetParent() : (CTPEPWnd *)NULL);
}

CString CTPEPDataContainer::LookupColumnName(UINT nColumn) CONST
{
	if (nColumn == TPEP_TITLEITEM_ID) return STRING(IDS_TPEP_TITLEITEM_ID);
	if (nColumn == TPEP_TITLEITEM_DESCRIPTION) return STRING(IDS_TPEP_TITLEITEM_DESCRIPTION);
	if (nColumn == TPEP_TITLEITEM_VALUE) return STRING(IDS_TPEP_TITLEITEM_VALUE);
	if (nColumn == TPEP_TITLEITEM_UNIT) return STRING(IDS_TPEP_TITLEITEM_UNIT);
	if (nColumn == TPEP_TITLEITEM_CHANGETMUNIT) return STRING(IDS_TPEP_TITLEITEM_CHANGETMUNIT);
	if (nColumn == TPEP_TITLEITEM_CHANGETIME) return STRING(IDS_TPEP_TITLEITEM_CHANGETIME);
	if (nColumn == TPEP_TITLEITEM_UPDATETMUNIT) return STRING(IDS_TPEP_TITLEITEM_UPDATETMUNIT);
	if (nColumn == TPEP_TITLEITEM_UPDATETIME) return STRING(IDS_TPEP_TITLEITEM_UPDATETIME);
	if (nColumn == TPEP_TITLEITEM_MESSAGES) return STRING(IDS_TPEP_TITLEITEM_MESSAGES);
	return EMPTYSTRING;
}
UINT CTPEPDataContainer::LookupColumnName(LPCTSTR pszColumn) CONST
{
	if (!lstrcmp(pszColumn, STRING(IDS_TPEP_TITLEITEM_ID))) return TPEP_TITLEITEM_ID;
	if (!lstrcmp(pszColumn, STRING(IDS_TPEP_TITLEITEM_DESCRIPTION))) return TPEP_TITLEITEM_DESCRIPTION;
	if (!lstrcmp(pszColumn, STRING(IDS_TPEP_TITLEITEM_VALUE))) return TPEP_TITLEITEM_VALUE;
	if (!lstrcmp(pszColumn, STRING(IDS_TPEP_TITLEITEM_UNIT))) return TPEP_TITLEITEM_UNIT;
	if (!lstrcmp(pszColumn, STRING(IDS_TPEP_TITLEITEM_CHANGETMUNIT))) return TPEP_TITLEITEM_CHANGETMUNIT;
	if (!lstrcmp(pszColumn, STRING(IDS_TPEP_TITLEITEM_CHANGETIME))) return TPEP_TITLEITEM_CHANGETIME;
	if (!lstrcmp(pszColumn, STRING(IDS_TPEP_TITLEITEM_UPDATETMUNIT))) return TPEP_TITLEITEM_UPDATETMUNIT;
	if (!lstrcmp(pszColumn, STRING(IDS_TPEP_TITLEITEM_UPDATETIME))) return TPEP_TITLEITEM_UPDATETIME;
	if (!lstrcmp(pszColumn, STRING(IDS_TPEP_TITLEITEM_MESSAGES))) return TPEP_TITLEITEM_MESSAGES;
	return 0;
}

INT CTPEPDataContainer::LookupColumnsName(CONST CUIntArray &nColumns, CStringArray &szColumns) CONST
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = 0, nCount = (INT)nColumns.GetSize(), szColumns.RemoveAll(); nIndex < nCount; nIndex++)
	{
		szColumns.Add(LookupColumnName(nColumns.GetAt(nIndex)));
		continue;
	}
	return((nCount == szColumns.GetSize()) ? (INT)szColumns.GetSize() : 0);
}

INT CTPEPDataContainer::CalcColumnWidth(LPCTSTR pszColumn)
{
	CDC  *pDC;
	INT  nWidth;
	UINT  nColumn;
	CFont  *pOldFont;
	CString  szColumn;
	CStringTools  cStringTools;
	TEXTMETRIC  tmFont;

	if ((pDC = GetDC()))
	{
		if ((nColumn = LookupColumnName(pszColumn)) == 0)
		{
			for (nWidth = 0; (pOldFont = pDC->SelectObject(&m_wndContentCtrl.m_cFont)); )
			{
				nWidth = LOWORD(GetTextIndents()) + pDC->GetTextExtent(pszColumn).cx + HIWORD(GetTextIndents());
				pDC->SelectObject(pOldFont);
				break;
			}
			ReleaseDC(pDC);
			return nWidth;
		}
		for (nWidth = 0; (pOldFont = pDC->SelectObject(&m_wndHeaderCtrl.m_cFont)); )
		{
			nWidth = LOWORD(GetTextIndents()) + pDC->GetTextExtent(pszColumn).cx + HIWORD(GetTextIndents());
			pDC->SelectObject(pOldFont);
			break;
		}
		if ((pOldFont = pDC->SelectObject(&m_wndContentCtrl.m_cFont)))
		{
			if (pDC->GetTextMetrics(&tmFont) > 0 && tmFont.tmAveCharWidth > 0)
			{
				nWidth = (nColumn == TPEP_TITLEITEM_ID) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTPEPIDColumnCharWidth()*tmFont.tmAveCharWidth + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TPEP_TITLEITEM_DESCRIPTION) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTPEPDescriptionColumnCharWidth()*tmFont.tmAveCharWidth + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TPEP_TITLEITEM_VALUE) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTPEPValueColumnCharWidth()*tmFont.tmAveCharWidth + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TPEP_TITLEITEM_UNIT) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTPEPUnitColumnCharWidth()*tmFont.tmAveCharWidth + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TPEP_TITLEITEM_CHANGETMUNIT) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTPEPChangeTMUnitColumnCharWidth()*tmFont.tmAveCharWidth + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TPEP_TITLEITEM_UPDATETMUNIT) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTPEPUpdateTMUnitColumnCharWidth()*tmFont.tmAveCharWidth + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TPEP_TITLEITEM_CHANGETIME) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTPEPChangeTimeColumnCharWidth()*tmFont.tmAveCharWidth + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == TPEP_TITLEITEM_UPDATETIME) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetTPEPUpdateTimeColumnCharWidth()*tmFont.tmAveCharWidth + HIWORD(GetTextIndents()), nWidth) : nWidth;
			}
			pDC->SelectObject(pOldFont);
		}
		for (szColumn = pszColumn; nColumn == TPEP_TITLEITEM_VALUE; )
		{
			szColumn = CString(cStringTools.ConvertIntToString(0).GetAt(0), GetDatabase()->GetTPEPValueColumnCharWidth());
			break;
		}
		for (; nColumn == TPEP_TITLEITEM_CHANGETIME || nColumn == TPEP_TITLEITEM_UPDATETIME; )
		{
			szColumn = CTimeTag().FormatGmt();
			break;
		}
		if ((pOldFont = pDC->SelectObject(&m_wndContentCtrl.m_cFont)))
		{
			nWidth = max(LOWORD(GetTextIndents()) + pDC->GetTextExtent(szColumn).cx + HIWORD(GetTextIndents()), nWidth);
			pDC->SelectObject(pOldFont);
		}
		ReleaseDC(pDC);
		return nWidth;
	}
	return 0;
}

INT CTPEPDataContainer::CalcColumnsWidth(CONST CStringArray &szColumns, CUIntArray &nWidths)
{
	INT  nIndex;
	INT  nCount;
	CUIntArray  nColumns;

	for (nIndex = 0, nCount = (INT)szColumns.GetSize(); nIndex < nCount; nIndex++)
	{
		nColumns.Add(LookupColumnName(szColumns.GetAt(nIndex)));
		continue;
	}
	return CalcColumnsWidth(nColumns, nWidths);
}
INT CTPEPDataContainer::CalcColumnsWidth(CONST CUIntArray &nColumns, CUIntArray &nWidths)
{
	INT  nWidth;
	INT  nIndex[2];
	INT  nCount[2];

	for (nIndex[0] = 0, nCount[0] = (INT)nColumns.GetSize(), nWidths.RemoveAll(); nIndex[0] < nCount[0]; nIndex[0]++)
	{
		for (nIndex[1] = 0, nCount[1] = (INT)m_wndHeaderCtrl.m_szColumnsText.GetSize(); nIndex[1] < nCount[1]; nIndex[1]++)
		{
			if (nColumns.GetAt(nIndex[0]) == LookupColumnName(m_wndHeaderCtrl.m_szColumnsText.GetAt(nIndex[1])))
			{
				nWidth = (nIndex[1] > 0) ? (m_wndHeaderCtrl.m_nColumnsWidth.GetAt(nIndex[1]) - m_wndHeaderCtrl.m_nColumnsWidth.GetAt(nIndex[1] - 1)) : m_wndHeaderCtrl.m_nColumnsWidth.GetAt(nIndex[1]);
				nWidths.Add((nIndex[0] > 0) ? (nWidths.GetAt(nIndex[0] - 1) + nWidth) : nWidth);
				break;
			}
		}
		if (nIndex[1] == nCount[1])
		{
			nWidths.Add((nIndex[0] > 0) ? (nWidths.GetAt(nIndex[0] - 1) + CalcColumnWidth(LookupColumnName(nColumns.GetAt(nIndex[0])))) : CalcColumnWidth(LookupColumnName(nColumns.GetAt(nIndex[0]))));
			continue;
		}
	}
	return((nCount[0] == nWidths.GetSize()) ? (INT)nWidths.GetSize() : 0);
}

BOOL CTPEPDataContainer::FilterMessage(LPCTSTR pszMessage)
{
	INT  nCount[2];
	UINT  nLimit[1];

	for (nLimit[0] = (!GetFilterLimit(nLimit[0])) ? TPEP_FILTER_DEFAULTNOLIMIT : nLimit[0], nCount[0] = GetMessageCount(); nCount[0] >= (INT)nLimit[0] && nLimit[0] > 0; nCount[0]--)
	{
		if ((nCount[1] = (DeleteText(0, (nCount[0] == (INT)nLimit[0]) ? TRUE : FALSE)) ? m_nParameterCount : 0) > 0 || !m_nParameterCount)
		{
			m_szParameterIDs.RemoveAt(0, nCount[1]);
			m_szParameterValues[0].RemoveAt(0, nCount[1]);
			m_szParameterValues[1].RemoveAt(0, nCount[1]);
			m_szParameterPackets[0].RemoveAt(0, nCount[1]);
			m_szParameterPackets[1].RemoveAt(0, nCount[1]);
			m_szParameterTimeTags[0][0].RemoveAt(0, nCount[1]);
			m_szParameterTimeTags[0][1].RemoveAt(0, nCount[1]);
			m_szParameterTimeTags[1][0].RemoveAt(0, nCount[1]);
			m_szParameterTimeTags[1][1].RemoveAt(0, nCount[1]);
			m_nParameterStatus.RemoveAt(0, nCount[1]);
			continue;
		}
		break;
	}
	return((nCount[0] < (INT)nLimit[0] || !nLimit[0]) ? TRUE : FALSE);
}

BOOL CTPEPDataContainer::ParseMessage(LPCTSTR pszMessage, CString &szMessage, CTextViewAttribute *pAttribute)
{
	INT  nPos;
	INT  nPIE;
	INT  nPIEs;
	INT  nIndex;
	INT  nColumn;
	INT  nColumns;
	INT  nParameter;
	INT  nParameters;
	UINT  nParameterStatus;
	UINT  nFilterDigits;
	UINT  nFilterStatus;
	double  fPIEType;
	double  fPIECount;
	double  fSequence;
	double  fQuality;
	double  fStatus;
	CString  szID;
	CString  szOBRT;
	CString  szValue;
	CString  szError;
	CString  szStatus;
	CString  szPacket;
	CString  szParameter;
	CString  szTimeTag[2];
	CString  szParameterPacket[2];
	CString  szParameterTimeTag[2][2];
	CUIntArray  nParameterFilterOOLColors;
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CTimeSpan  tFilterDailyRange[2];
	CTimeSpan  tFilterInterval;
	CTimeKey  tFilterStartTime;
	CTimeKey  tFilterStopTime;
	CTimeKey  tFilterRange[2];
	CTimeTag  tFilterTimeTag;
	COLORREF  nFilterColor;

	if (m_nType == TPEP_TYPE_NORMAL)
	{
		if (ReadMessageText(pszMessage, szID, (nPos = 0)) && ReadMessageNumber(pszMessage, fSequence, nPos) && ReadMessageText(pszMessage, szError, nPos) && ReadMessageText(pszMessage, szStatus, nPos) && szID == STRING(IDS_TPEP_DATA_PARAMETERS_ID) && floor(fSequence) == fSequence  &&  floor(fSequence) > 0.0  &&  _ttoi(szError) >= 0 && (_ttoi(szStatus) == LOWORD(TPEP_SYNCSTATUS_NONE) || _ttoi(szStatus) == LOWORD(TPEP_SYNCSTATUS_GOOD) || _ttoi(szStatus) == LOWORD(TPEP_SYNCSTATUS_BAD)))
		{
			if (ReadMessageText(pszMessage, szPacket, nPos) && ReadMessageText(pszMessage, szTimeTag[0], nPos) && ReadMessageText(pszMessage, szTimeTag[1], nPos) && ReadMessageText(pszMessage, szOBRT, nPos) && ReadMessageNumber(pszMessage, fPIEType, nPos) && ReadMessageNumber(pszMessage, fPIECount, nPos) && floor(fPIEType) == fPIEType  &&  fPIEType >= TPEP_DATATYPE_PIE1  &&  fPIEType <= TPEP_DATATYPE_PIE3  &&  floor(fPIECount) == fPIECount  &&  fPIECount >= 0.0)
			{
				if (ConvertMessageTextToTimeTag(szTimeTag[0] + SPACE + szTimeTag[1], tFilterTimeTag) && tFilterTimeTag.GetTimeInSeconds() > 0)
				{
					if (GetFilterRange(tFilterRange[0], tFilterRange[1]) && (tFilterRange[0] > tFilterTimeTag.GetTimeInSeconds() || tFilterRange[1] < tFilterTimeTag.GetTimeInSeconds()))
					{
						szMessage.Empty();
						return TRUE;
					}
					if (GetFilterDailyRange(tFilterDailyRange[0], tFilterDailyRange[1]) && (tFilterDailyRange[0].GetTotalSeconds() > tFilterTimeTag.GetTimeInSeconds() % SECONDSPERDAY || tFilterDailyRange[1].GetTotalSeconds() < tFilterTimeTag.GetTimeInSeconds() % SECONDSPERDAY))
					{
						szMessage.Empty();
						return TRUE;
					}
					if (GetFilterPeriodicalRange(tFilterStartTime, tFilterInterval, tFilterStopTime))
					{
						if ((tFilterStartTime.GetTime() > 0 && tFilterStartTime > tFilterTimeTag.GetTimeInSeconds()) || (tFilterStopTime.GetTime() > 0 && tFilterStopTime < tFilterTimeTag.GetTimeInSeconds()))
						{
							szMessage.Empty();
							return TRUE;
						}
						if (((tFilterTimeTag.GetTimeInSeconds() - tFilterStartTime.GetTime()) / tFilterInterval.GetTotalSeconds()) % 2 == 1)
						{
							szMessage.Empty();
							return TRUE;
						}
					}
				}
				for (nPIE = 0, nPIEs = (INT)fPIECount, nIndex = (INT)m_szParameterIDs.GetSize(), m_nParameterCount = nPIEs; nPIE < nPIEs; nPIE++)
				{
					if (ReadMessageText(pszMessage, szParameter, nPos))
					{
						if (ReadMessageNumber(pszMessage, fQuality, nPos))
						{
							m_szParameterIDs.Add(szParameter);
							m_szParameterValues[0].Add(EMPTYSTRING);
							m_szParameterValues[1].Add(EMPTYSTRING);
							m_szParameterPackets[0].Add(EMPTYSTRING);
							m_szParameterPackets[1].Add(EMPTYSTRING);
							m_szParameterTimeTags[0][0].Add(EMPTYSTRING);
							m_szParameterTimeTags[0][1].Add(EMPTYSTRING);
							m_szParameterTimeTags[1][0].Add(EMPTYSTRING);
							m_szParameterTimeTags[1][1].Add(EMPTYSTRING);
							m_nParameterStatus.Add((fQuality != TPEP_DATAQUALITY_BAD) ? TMPARAMETER_STATUS_GOOD : TMPARAMETER_STATUS_BAD);
							if (floor(fQuality) == fQuality && (fQuality == TPEP_DATAQUALITY_UNCHANGED || fQuality == TPEP_DATAQUALITY_UPDATED || fQuality == TPEP_DATAQUALITY_CHANGED || fQuality == TPEP_DATAQUALITY_BAD))
							{
								if (ReadMessageText(pszMessage, szValue, nPos))
								{
									m_szParameterValues[0].SetAt(nIndex + nPIE, szValue);
									if (fPIEType == TPEP_DATATYPE_PIE2)
									{
										if (ReadMessageNumber(pszMessage, fStatus, nPos))
										{
											if ((nParameterStatus = (UINT)fStatus) & TPEP_DATASTATUS_NOLIMIT) m_nParameterStatus.SetAt(nIndex + nPIE, m_nParameterStatus.GetAt(nIndex + nPIE) | TMPARAMETER_STATUS_NOLIMIT);
											if (nParameterStatus & TPEP_DATASTATUS_SOFTLIMIT) m_nParameterStatus.SetAt(nIndex + nPIE, m_nParameterStatus.GetAt(nIndex + nPIE) | TMPARAMETER_STATUS_SOFTLIMIT);
											if (nParameterStatus & TPEP_DATASTATUS_HARDLIMIT) m_nParameterStatus.SetAt(nIndex + nPIE, m_nParameterStatus.GetAt(nIndex + nPIE) | TMPARAMETER_STATUS_HARDLIMIT);
											if (nParameterStatus & TPEP_DATASTATUS_DELTALIMIT) m_nParameterStatus.SetAt(nIndex + nPIE, m_nParameterStatus.GetAt(nIndex + nPIE) | TMPARAMETER_STATUS_DELTALIMIT);
											if (nParameterStatus & TPEP_DATASTATUS_CONSISTENCYLIMIT) m_nParameterStatus.SetAt(nIndex + nPIE, m_nParameterStatus.GetAt(nIndex + nPIE) | TMPARAMETER_STATUS_CONSISTENCYLIMIT);
											if (nParameterStatus & TPEP_DATASTATUS_VALID) m_nParameterStatus.SetAt(nIndex + nPIE, m_nParameterStatus.GetAt(nIndex + nPIE) | TMPARAMETER_STATUS_VALID);
											if (nParameterStatus & TPEP_DATASTATUS_INVALID) m_nParameterStatus.SetAt(nIndex + nPIE, m_nParameterStatus.GetAt(nIndex + nPIE) | TMPARAMETER_STATUS_INVALID);
											continue;
										}
										break;
									}
									if (fPIEType == TPEP_DATATYPE_PIE3)
									{
										if (ReadMessageText(pszMessage, szValue, nPos) && ReadMessageNumber(pszMessage, fStatus, nPos) && ReadMessageText(pszMessage, szParameterPacket[0], nPos) && ReadMessageText(pszMessage, szParameterTimeTag[0][0], nPos) && ReadMessageText(pszMessage, szParameterTimeTag[0][1], nPos) && ReadMessageText(pszMessage, szParameterPacket[1], nPos) && ReadMessageText(pszMessage, szParameterTimeTag[1][0], nPos) && ReadMessageText(pszMessage, szParameterTimeTag[1][1], nPos))
										{
											m_szParameterValues[1].SetAt(nIndex + nPIE, szValue);
											m_szParameterPackets[0].SetAt(nIndex + nPIE, szParameterPacket[0]);
											m_szParameterPackets[1].SetAt(nIndex + nPIE, szParameterPacket[1]);
											m_szParameterTimeTags[0][0].SetAt(nIndex + nPIE, szParameterTimeTag[0][0]);
											m_szParameterTimeTags[0][1].SetAt(nIndex + nPIE, szParameterTimeTag[0][1]);
											m_szParameterTimeTags[1][0].SetAt(nIndex + nPIE, szParameterTimeTag[1][0]);
											m_szParameterTimeTags[1][1].SetAt(nIndex + nPIE, szParameterTimeTag[1][1]);
											if ((nParameterStatus = (UINT)fStatus) & TPEP_DATASTATUS_NOLIMIT) m_nParameterStatus.SetAt(nIndex + nPIE, m_nParameterStatus.GetAt(nIndex + nPIE) | TMPARAMETER_STATUS_NOLIMIT);
											if (nParameterStatus & TPEP_DATASTATUS_SOFTLIMIT) m_nParameterStatus.SetAt(nIndex + nPIE, m_nParameterStatus.GetAt(nIndex + nPIE) | TMPARAMETER_STATUS_SOFTLIMIT);
											if (nParameterStatus & TPEP_DATASTATUS_HARDLIMIT) m_nParameterStatus.SetAt(nIndex + nPIE, m_nParameterStatus.GetAt(nIndex + nPIE) | TMPARAMETER_STATUS_HARDLIMIT);
											if (nParameterStatus & TPEP_DATASTATUS_DELTALIMIT) m_nParameterStatus.SetAt(nIndex + nPIE, m_nParameterStatus.GetAt(nIndex + nPIE) | TMPARAMETER_STATUS_DELTALIMIT);
											if (nParameterStatus & TPEP_DATASTATUS_CONSISTENCYLIMIT) m_nParameterStatus.SetAt(nIndex + nPIE, m_nParameterStatus.GetAt(nIndex + nPIE) | TMPARAMETER_STATUS_CONSISTENCYLIMIT);
											if (nParameterStatus & TPEP_DATASTATUS_VALID) m_nParameterStatus.SetAt(nIndex + nPIE, m_nParameterStatus.GetAt(nIndex + nPIE) | TMPARAMETER_STATUS_VALID);
											if (nParameterStatus & TPEP_DATASTATUS_INVALID) m_nParameterStatus.SetAt(nIndex + nPIE, m_nParameterStatus.GetAt(nIndex + nPIE) | TMPARAMETER_STATUS_INVALID);
											continue;
										}
										break;
									}
									continue;
								}
								break;
							}
							if (floor(fQuality) == fQuality  &&  fQuality == TPEP_DATAQUALITY_NONE) continue;
						}
					}
					break;
				}
				if (nPIE == nPIEs)
				{
					for (nColumn = 0, nColumns = (INT)m_nLayoutColumns.GetSize(), nParameter = nIndex, nParameters = nIndex + nPIEs, szMessage.Empty(), GetFilterColors(nFilterColor, nParameterFilterOOLColors); nColumn < nColumns && nParameters > 0; nColumn++)
					{
						pAttribute->SetColumnColor(nColumn, nFilterColor);
						if (m_nLayoutColumns.GetAt(nColumn) == TPEP_TITLEITEM_ID)
						{
							if ((nParameter = (nColumn > 0) ? (nParameter + 1) : nParameter) >= nParameters) break;
							szMessage += (nColumn > 0) ? (GetColumnDelimiter() + m_szParameterIDs.GetAt(nParameter)) : m_szParameterIDs.GetAt(nParameter);
							continue;
						}
						if (m_nLayoutColumns.GetAt(nColumn) == TPEP_TITLEITEM_DESCRIPTION)
						{
							if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(m_szParameterIDs.GetAt(nParameter)))))
							{
								szMessage += (nColumn > 0) ? (GetColumnDelimiter() + pDatabaseTMParameter->GetDescription()) : pDatabaseTMParameter->GetDescription();
								continue;
							}
						}
						if (m_nLayoutColumns.GetAt(nColumn) == TPEP_TITLEITEM_VALUE)
						{
							if (m_nParameterStatus.GetAt(nParameter) != TMPARAMETER_STATUS_NONE)
							{
								if (m_nParameterStatus.GetAt(nParameter) & TMPARAMETER_STATUS_NOLIMIT) pAttribute->SetColumnColor(nColumn, nParameterFilterOOLColors.GetAt(TPEP_OOLCOLOR_NOLIMIT));
								if (m_nParameterStatus.GetAt(nParameter) & TMPARAMETER_STATUS_SOFTLIMIT) pAttribute->SetColumnColor(nColumn, nParameterFilterOOLColors.GetAt(TPEP_OOLCOLOR_SOFTLIMIT));
								if (m_nParameterStatus.GetAt(nParameter) & TMPARAMETER_STATUS_HARDLIMIT) pAttribute->SetColumnColor(nColumn, nParameterFilterOOLColors.GetAt(TPEP_OOLCOLOR_HARDLIMIT));
								if (m_nParameterStatus.GetAt(nParameter) & TMPARAMETER_STATUS_DELTALIMIT) pAttribute->SetColumnColor(nColumn, nParameterFilterOOLColors.GetAt(TPEP_OOLCOLOR_DELTALIMIT));
								if (m_nParameterStatus.GetAt(nParameter) & TMPARAMETER_STATUS_CONSISTENCYLIMIT) pAttribute->SetColumnColor(nColumn, nParameterFilterOOLColors.GetAt(TPEP_OOLCOLOR_CONSISTENCYLIMIT));
							}
							for (GetFilterDigits(nFilterDigits); nFilterDigits > 0; )
							{
								m_szParameterValues[0].SetAt(nParameter, m_szParameterValues[0].GetAt(nParameter).Left(nFilterDigits));
								m_szParameterValues[1].SetAt(nParameter, m_szParameterValues[1].GetAt(nParameter).Left(nFilterDigits));
								break;
							}
							if (GetFilterStatus(nFilterStatus))
							{
								if ((nFilterStatus & (TMPARAMETER_STATUS_NOLIMIT | TMPARAMETER_STATUS_SOFTLIMIT | TMPARAMETER_STATUS_HARDLIMIT | TMPARAMETER_STATUS_DELTALIMIT | TMPARAMETER_STATUS_CONSISTENCYLIMIT)) && (m_nParameterStatus.GetAt(nParameter) & (TMPARAMETER_STATUS_NOLIMIT | TMPARAMETER_STATUS_SOFTLIMIT | TMPARAMETER_STATUS_HARDLIMIT | TMPARAMETER_STATUS_DELTALIMIT | TMPARAMETER_STATUS_CONSISTENCYLIMIT)))
								{
									if (((nFilterStatus & (TMPARAMETER_STATUS_NOLIMIT | TMPARAMETER_STATUS_SOFTLIMIT | TMPARAMETER_STATUS_HARDLIMIT | TMPARAMETER_STATUS_DELTALIMIT | TMPARAMETER_STATUS_CONSISTENCYLIMIT)) & (m_nParameterStatus.GetAt(nParameter) & (TMPARAMETER_STATUS_NOLIMIT | TMPARAMETER_STATUS_SOFTLIMIT | TMPARAMETER_STATUS_HARDLIMIT | TMPARAMETER_STATUS_DELTALIMIT | TMPARAMETER_STATUS_CONSISTENCYLIMIT))) == 0)
									{
										szMessage += (nColumn > 0) ? (LPCTSTR)CString(GetColumnDelimiter()) : EMPTYSTRING;
										continue;
									}
								}
								if ((nFilterStatus & (TMPARAMETER_STATUS_VALID | TMPARAMETER_STATUS_INVALID)) && (m_nParameterStatus.GetAt(nParameter) & (TMPARAMETER_STATUS_VALID | TMPARAMETER_STATUS_INVALID)))
								{
									if (((nFilterStatus & (TMPARAMETER_STATUS_VALID | TMPARAMETER_STATUS_INVALID)) & (m_nParameterStatus.GetAt(nParameter) & (TMPARAMETER_STATUS_VALID | TMPARAMETER_STATUS_INVALID))) == 0)
									{
										szMessage += (nColumn > 0) ? (LPCTSTR)CString(GetColumnDelimiter()) : EMPTYSTRING;
										continue;
									}
								}
								if ((nFilterStatus & (TMPARAMETER_STATUS_GOOD | TMPARAMETER_STATUS_BAD)) && (m_nParameterStatus.GetAt(nParameter) & (TMPARAMETER_STATUS_GOOD | TMPARAMETER_STATUS_BAD)))
								{
									if (((nFilterStatus & (TMPARAMETER_STATUS_GOOD | TMPARAMETER_STATUS_BAD)) & (m_nParameterStatus.GetAt(nParameter) & (TMPARAMETER_STATUS_GOOD | TMPARAMETER_STATUS_BAD))) == 0)
									{
										szMessage += (nColumn > 0) ? (LPCTSTR)CString(GetColumnDelimiter()) : EMPTYSTRING;
										continue;
									}
								}
							}
							szMessage += (nColumn > 0) ? (GetColumnDelimiter() + m_szParameterValues[0].GetAt(nParameter)) : m_szParameterValues[0].GetAt(nParameter);
							continue;
						}
						if (m_nLayoutColumns.GetAt(nColumn) == TPEP_TITLEITEM_UNIT)
						{
							if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(m_szParameterIDs.GetAt(nParameter)))))
							{
								szMessage += (nColumn > 0) ? (GetColumnDelimiter() + pDatabaseTMParameter->GetUnit()) : pDatabaseTMParameter->GetUnit();
								continue;
							}
						}
						if ((m_nLayoutColumns.GetAt(nColumn) == TPEP_TITLEITEM_CHANGETMUNIT || m_nLayoutColumns.GetAt(nColumn) == TPEP_TITLEITEM_CHANGETIME || m_nLayoutColumns.GetAt(nColumn) == TPEP_TITLEITEM_UPDATETMUNIT || m_nLayoutColumns.GetAt(nColumn) == TPEP_TITLEITEM_UPDATETIME) && GetFilterStatus(nFilterStatus))
						{
							if ((nFilterStatus & (TMPARAMETER_STATUS_NOLIMIT | TMPARAMETER_STATUS_SOFTLIMIT | TMPARAMETER_STATUS_HARDLIMIT | TMPARAMETER_STATUS_DELTALIMIT | TMPARAMETER_STATUS_CONSISTENCYLIMIT)) && (m_nParameterStatus.GetAt(nParameter) & (TMPARAMETER_STATUS_NOLIMIT | TMPARAMETER_STATUS_SOFTLIMIT | TMPARAMETER_STATUS_HARDLIMIT | TMPARAMETER_STATUS_DELTALIMIT | TMPARAMETER_STATUS_CONSISTENCYLIMIT)))
							{
								if (((nFilterStatus & (TMPARAMETER_STATUS_NOLIMIT | TMPARAMETER_STATUS_SOFTLIMIT | TMPARAMETER_STATUS_HARDLIMIT | TMPARAMETER_STATUS_DELTALIMIT | TMPARAMETER_STATUS_CONSISTENCYLIMIT)) & (m_nParameterStatus.GetAt(nParameter) & (TMPARAMETER_STATUS_NOLIMIT | TMPARAMETER_STATUS_SOFTLIMIT | TMPARAMETER_STATUS_HARDLIMIT | TMPARAMETER_STATUS_DELTALIMIT | TMPARAMETER_STATUS_CONSISTENCYLIMIT))) == 0)
								{
									szMessage += (nColumn > 0) ? (LPCTSTR)CString(GetColumnDelimiter()) : EMPTYSTRING;
									continue;
								}
							}
							if ((nFilterStatus & (TMPARAMETER_STATUS_VALID | TMPARAMETER_STATUS_INVALID)) && (m_nParameterStatus.GetAt(nParameter) & (TMPARAMETER_STATUS_VALID | TMPARAMETER_STATUS_INVALID)))
							{
								if (((nFilterStatus & (TMPARAMETER_STATUS_VALID | TMPARAMETER_STATUS_INVALID)) & (m_nParameterStatus.GetAt(nParameter) & (TMPARAMETER_STATUS_VALID | TMPARAMETER_STATUS_INVALID))) == 0)
								{
									szMessage += (nColumn > 0) ? (LPCTSTR)CString(GetColumnDelimiter()) : EMPTYSTRING;
									continue;
								}
							}
							if ((nFilterStatus & (TMPARAMETER_STATUS_GOOD | TMPARAMETER_STATUS_BAD)) && (m_nParameterStatus.GetAt(nParameter) & (TMPARAMETER_STATUS_GOOD | TMPARAMETER_STATUS_BAD)))
							{
								if (((nFilterStatus & (TMPARAMETER_STATUS_GOOD | TMPARAMETER_STATUS_BAD)) & (m_nParameterStatus.GetAt(nParameter) & (TMPARAMETER_STATUS_GOOD | TMPARAMETER_STATUS_BAD))) == 0)
								{
									szMessage += (nColumn > 0) ? (LPCTSTR)CString(GetColumnDelimiter()) : EMPTYSTRING;
									continue;
								}
							}
						}
						if (m_nLayoutColumns.GetAt(nColumn) == TPEP_TITLEITEM_CHANGETMUNIT)
						{
							szMessage += (nColumn > 0) ? (GetColumnDelimiter() + m_szParameterPackets[0].GetAt(nParameter)) : m_szParameterPackets[0].GetAt(nParameter);
							continue;
						}
						if (m_nLayoutColumns.GetAt(nColumn) == TPEP_TITLEITEM_CHANGETIME)
						{
							szMessage += (nColumn > 0) ? (GetColumnDelimiter() + m_szParameterTimeTags[0][0].GetAt(nParameter) + SPACE + m_szParameterTimeTags[0][1].GetAt(nParameter)) : (m_szParameterTimeTags[0][0].GetAt(nParameter) + SPACE + m_szParameterTimeTags[0][1].GetAt(nParameter));
							continue;
						}
						if (m_nLayoutColumns.GetAt(nColumn) == TPEP_TITLEITEM_UPDATETMUNIT)
						{
							szMessage += (nColumn > 0) ? (GetColumnDelimiter() + m_szParameterPackets[1].GetAt(nParameter)) : m_szParameterPackets[1].GetAt(nParameter);
							continue;
						}
						if (m_nLayoutColumns.GetAt(nColumn) == TPEP_TITLEITEM_UPDATETIME)
						{
							szMessage += (nColumn > 0) ? (GetColumnDelimiter() + m_szParameterTimeTags[1][0].GetAt(nParameter) + SPACE + m_szParameterTimeTags[1][1].GetAt(nParameter)) : (m_szParameterTimeTags[1][0].GetAt(nParameter) + SPACE + m_szParameterTimeTags[1][1].GetAt(nParameter));
							continue;
						}
						szMessage += (nColumn > 0) ? (LPCTSTR)CString(GetColumnDelimiter()) : EMPTYSTRING;
					}
					if (_tcsspn(szMessage, CString(GetColumnDelimiter())) == szMessage.GetLength() && nParameters > 0)
					{
						m_szParameterIDs.RemoveAt(m_szParameterIDs.GetSize() - m_nParameterCount, m_nParameterCount);
						m_szParameterValues[0].RemoveAt(m_szParameterValues[0].GetSize() - m_nParameterCount, m_nParameterCount);
						m_szParameterValues[1].RemoveAt(m_szParameterValues[1].GetSize() - m_nParameterCount, m_nParameterCount);
						m_szParameterPackets[0].RemoveAt(m_szParameterPackets[0].GetSize() - m_nParameterCount, m_nParameterCount);
						m_szParameterPackets[1].RemoveAt(m_szParameterPackets[1].GetSize() - m_nParameterCount, m_nParameterCount);
						m_szParameterTimeTags[0][0].RemoveAt(m_szParameterTimeTags[0][0].GetSize() - m_nParameterCount, m_nParameterCount);
						m_szParameterTimeTags[0][1].RemoveAt(m_szParameterTimeTags[0][1].GetSize() - m_nParameterCount, m_nParameterCount);
						m_szParameterTimeTags[1][0].RemoveAt(m_szParameterTimeTags[1][0].GetSize() - m_nParameterCount, m_nParameterCount);
						m_szParameterTimeTags[1][1].RemoveAt(m_szParameterTimeTags[1][1].GetSize() - m_nParameterCount, m_nParameterCount);
						m_nParameterStatus.RemoveAt(m_nParameterStatus.GetSize() - m_nParameterCount, m_nParameterCount);
						szMessage.Empty();
					}
					return TRUE;
				}
				return FALSE;
			}
			if (_ttoi(szError) > 0)
			{
				for (nColumn = 0, nColumns = (INT)m_nLayoutColumns.GetSize(), szMessage.Empty(), nIndex = -1; nColumn < nColumns; nColumn++)
				{
					if (m_nLayoutColumns.GetAt(nColumn) == TPEP_TITLEITEM_VALUE)
					{
						szMessage += (nColumn > 0) ? (GetColumnDelimiter() + szError) : szError;
						nIndex = nColumn;
						continue;
					}
					szMessage += (nColumn > 0) ? (LPCTSTR)CString(GetColumnDelimiter()) : EMPTYSTRING;
				}
				for (nParameter = 0, nParameters = m_nParameterCount; nParameter < nParameters; nParameter++)
				{
					m_szParameterIDs.Add((nIndex < 0) ? (LPCTSTR)szError : EMPTYSTRING);
					m_szParameterValues[0].Add((nIndex >= 0) ? (LPCTSTR)szError : EMPTYSTRING);
					m_szParameterValues[1].Add(EMPTYSTRING);
					m_szParameterPackets[0].Add(EMPTYSTRING);
					m_szParameterPackets[1].Add(EMPTYSTRING);
					m_szParameterTimeTags[0][0].Add(EMPTYSTRING);
					m_szParameterTimeTags[0][1].Add(EMPTYSTRING);
					m_szParameterTimeTags[1][0].Add(EMPTYSTRING);
					m_szParameterTimeTags[1][1].Add(EMPTYSTRING);
					m_nParameterStatus.Add(TMPARAMETER_STATUS_NONE);
				}
				szMessage = (nIndex < 0) ? (szError + szMessage) : szMessage;
				return TRUE;
			}
		}
		szMessage.Empty();
		return FALSE;
	}
	if (m_nType == TPEP_TYPE_SIMPLE)
	{
		if (ReadMessageText(pszMessage, szID, (nPos = 0)) && ReadMessageNumber(pszMessage, fSequence, nPos) && ReadMessageText(pszMessage, szError, nPos) && ReadMessageText(pszMessage, szStatus, nPos) && (szID == STRING(IDS_TPEP_DATA_PACKETS_ID) || szID == STRING(IDS_TPEP_DATA_PARAMETERS_ID) || szID == STRING(IDS_TPEP_DATA_UNKNOWN_ID)) && floor(fSequence) == fSequence  &&  floor(fSequence) > 0.0  &&  _ttoi(szError) >= 0 && (_ttoi(szStatus) == LOWORD(TPEP_SYNCSTATUS_NONE) || _ttoi(szStatus) == LOWORD(TPEP_SYNCSTATUS_GOOD) || _ttoi(szStatus) == LOWORD(TPEP_SYNCSTATUS_BAD)))
		{
			if (ReadMessageText(pszMessage, szPacket, nPos) && ReadMessageText(pszMessage, szTimeTag[0], nPos) && ReadMessageText(pszMessage, szTimeTag[1], nPos) && ReadMessageText(pszMessage, szOBRT, nPos) && ReadMessageNumber(pszMessage, fPIEType, nPos) && ReadMessageNumber(pszMessage, fPIECount, nPos) && floor(fPIEType) == fPIEType  &&  fPIEType >= TPEP_DATATYPE_RAW  &&  fPIEType <= TPEP_DATATYPE_PIE3  &&  floor(fPIECount) == fPIECount  &&  fPIECount >= 0.0)
			{
				if (ConvertMessageTextToTimeTag(szTimeTag[0] + SPACE + szTimeTag[1], tFilterTimeTag) && tFilterTimeTag.GetTimeInSeconds() > 0)
				{
					if (GetFilterRange(tFilterRange[0], tFilterRange[1]) && (tFilterRange[0] > tFilterTimeTag.GetTimeInSeconds() || tFilterRange[1] < tFilterTimeTag.GetTimeInSeconds()))
					{
						szMessage.Empty();
						return TRUE;
					}
					if (GetFilterDailyRange(tFilterDailyRange[0], tFilterDailyRange[1]) && (tFilterDailyRange[0].GetTotalSeconds() > tFilterTimeTag.GetTimeInSeconds() % SECONDSPERDAY || tFilterDailyRange[1].GetTotalSeconds() < tFilterTimeTag.GetTimeInSeconds() % SECONDSPERDAY))
					{
						szMessage.Empty();
						return TRUE;
					}
					if (GetFilterPeriodicalRange(tFilterStartTime, tFilterInterval, tFilterStopTime))
					{
						if ((tFilterStartTime.GetTime() > 0 && tFilterStartTime > tFilterTimeTag.GetTimeInSeconds()) || (tFilterStopTime.GetTime() > 0 && tFilterStopTime < tFilterTimeTag.GetTimeInSeconds()))
						{
							szMessage.Empty();
							return TRUE;
						}
						if (((tFilterTimeTag.GetTimeInSeconds() - tFilterStartTime.GetTime()) / tFilterInterval.GetTotalSeconds()) % 2 == 1)
						{
							szMessage.Empty();
							return TRUE;
						}
					}
				}
				GetFilterColors(nFilterColor, nParameterFilterOOLColors);
				pAttribute->SetColumnColor(-1, nFilterColor);
				szMessage = pszMessage;
				return TRUE;
			}
			if (_ttoi(szError) > 0)
			{
				GetFilterColors(nFilterColor, nParameterFilterOOLColors);
				pAttribute->SetColumnColor(-1, nFilterColor);
				szMessage = pszMessage;
				return TRUE;
			}
		}
	}
	szMessage.Empty();
	return FALSE;
}
BOOL CTPEPDataContainer::ParseMessage(LPCTSTR pszMessage, CStringArray &szPackets, CStringArray &szParameters, CStringArray &szErrors)
{
	INT  nPos;
	INT  nPIE;
	INT  nPIEs;
	CString  szID;
	CString  szOBRT;
	CString  szError;
	CString  szValue;
	CString  szStatus;
	CString  szPacket;
	CString  szParameter;
	CString  szTimeTag[2];
	CString  szParameterPacket[2];
	CString  szParameterTimeTag[2][2];
	double  fPIEType;
	double  fPIECount;
	double  fSequence;
	double  fQuality;
	double  fStatus;

	if (m_nType == TPEP_TYPE_SIMPLE)
	{
		if (ReadMessageText(pszMessage, szID, (nPos = 0)) && ReadMessageNumber(pszMessage, fSequence, nPos) && ReadMessageText(pszMessage, szError, nPos) && ReadMessageText(pszMessage, szStatus, nPos) && (szID == STRING(IDS_TPEP_DATA_PACKETS_ID) || szID == STRING(IDS_TPEP_DATA_PARAMETERS_ID) || szID == STRING(IDS_TPEP_DATA_UNKNOWN_ID)) && floor(fSequence) == fSequence  &&  floor(fSequence) > 0.0  &&  _ttoi(szError) >= 0 && (_ttoi(szStatus) == LOWORD(TPEP_SYNCSTATUS_NONE) || _ttoi(szStatus) == LOWORD(TPEP_SYNCSTATUS_GOOD) || _ttoi(szStatus) == LOWORD(TPEP_SYNCSTATUS_BAD)))
		{
			if (ReadMessageText(pszMessage, szPacket, nPos) && ReadMessageText(pszMessage, szTimeTag[0], nPos) && ReadMessageText(pszMessage, szTimeTag[1], nPos) && ReadMessageText(pszMessage, szOBRT, nPos) && ReadMessageNumber(pszMessage, fPIEType, nPos) && ReadMessageNumber(pszMessage, fPIECount, nPos) && floor(fPIEType) == fPIEType  &&  fPIEType >= TPEP_DATATYPE_RAW  &&  fPIEType <= TPEP_DATATYPE_PIE3  &&  floor(fPIECount) == fPIECount  &&  fPIECount >= 0.0)
			{
				if (szID == STRING(IDS_TPEP_DATA_PACKETS_ID))
				{
					szPackets.SetAtGrow(0, szPacket);
					szParameters.RemoveAll();
					szErrors.RemoveAll();
					szPackets.SetSize(1);
					return TRUE;
				}
				if (szID == STRING(IDS_TPEP_DATA_PARAMETERS_ID))
				{
					for (nPIE = 0, nPIEs = (INT)fPIECount, szPackets.RemoveAll(), szParameters.RemoveAll(), szErrors.RemoveAll(); nPIE < nPIEs; nPIE++)
					{
						if (ReadMessageText(pszMessage, szParameter, nPos) && ReadMessageNumber(pszMessage, fQuality, nPos) && floor(fQuality) == fQuality && (((fQuality == TPEP_DATAQUALITY_UNCHANGED || fQuality == TPEP_DATAQUALITY_UPDATED || fQuality == TPEP_DATAQUALITY_CHANGED || fQuality == TPEP_DATAQUALITY_BAD) && ReadMessageText(pszMessage, szValue, nPos)) || fQuality == TPEP_DATAQUALITY_NONE))
						{
							if (fPIEType == TPEP_DATATYPE_PIE1 || fQuality == TPEP_DATAQUALITY_NONE)
							{
								szParameters.Add(szParameter);
								continue;
							}
							if (fPIEType == TPEP_DATATYPE_PIE2)
							{
								if (ReadMessageNumber(pszMessage, fStatus, nPos))
								{
									szParameters.Add(szParameter);
									continue;
								}
								break;
							}
							if (fPIEType == TPEP_DATATYPE_PIE3)
							{
								if (ReadMessageText(pszMessage, szValue, nPos) && ReadMessageNumber(pszMessage, fStatus, nPos) && ReadMessageText(pszMessage, szParameterPacket[0], nPos) && ReadMessageText(pszMessage, szParameterTimeTag[0][0], nPos) && ReadMessageText(pszMessage, szParameterTimeTag[0][1], nPos) && ReadMessageText(pszMessage, szParameterPacket[1], nPos) && ReadMessageText(pszMessage, szParameterTimeTag[1][0], nPos) && ReadMessageText(pszMessage, szParameterTimeTag[1][1], nPos))
								{
									szParameters.Add(szParameter);
									continue;
								}
							}
						}
						break;
					}
					return((nPIE == nPIEs) ? TRUE : FALSE);
				}
			}
			if (_ttoi(szError) > 0)
			{
				szErrors.SetAtGrow(0, szError);
				szParameters.RemoveAll();
				szPackets.RemoveAll();
				szErrors.SetSize(1);
				return TRUE;
			}
		}
		szPackets.RemoveAll();
		szParameters.RemoveAll();
		szErrors.RemoveAll();
	}
	return FALSE;
}
BOOL CTPEPDataContainer::ParseMessage(CONST POINT &point, CString &szParameter, CString &szError)
{
	INT  nIndex;

	if (m_nType == TPEP_TYPE_NORMAL)
	{
		if ((nIndex = ConvertMessagePositionToIndex(point)) < m_szParameterIDs.GetSize())
		{
			if (GetDatabase()->GetTMParameters()->Find(m_szParameterIDs.GetAt(nIndex)) >= 0)
			{
				szParameter = m_szParameterIDs.GetAt(nIndex);
				szError.Empty();
				return TRUE;
			}
			if (!m_szParameterIDs.GetAt(nIndex).IsEmpty() && m_szParameterValues[0].GetAt(nIndex).IsEmpty())
			{
				szError = m_szParameterIDs.GetAt(nIndex);
				szParameter.Empty();
				return TRUE;
			}
			if (m_szParameterIDs.GetAt(nIndex).IsEmpty() && !m_szParameterValues[0].GetAt(nIndex).IsEmpty())
			{
				szError = m_szParameterValues[0].GetAt(nIndex);
				szParameter.Empty();
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CTPEPDataContainer::ReadMessageText(LPCTSTR pszMessage, CString &szText, INT &nPos) CONST
{
	for (szText.Empty(); nPos < lstrlen(pszMessage); nPos++)
	{
		if ((szText.IsEmpty() || szText.GetAt(0) != STRINGCHAR(IDS_TPEP_DATA_DELIMITER)) && _istspace(pszMessage[nPos]))
		{
			nPos++;
			break;
		}
		for (szText += pszMessage[nPos]; szText.GetAt(0) == STRINGCHAR(IDS_TPEP_DATA_DELIMITER) && pszMessage[nPos] == STRINGCHAR(IDS_TPEP_DATA_DELIMITER) && szText.GetLength() > lstrlen(STRING(IDS_TPEP_DATA_DELIMITER)); )
		{
			szText = szText.Mid(lstrlen(STRING(IDS_TPEP_DATA_DELIMITER)), szText.GetLength() - 2 * lstrlen(STRING(IDS_TPEP_DATA_DELIMITER)));
			nPos++;
			nPos++;
			return TRUE;
		}
	}
	return !szText.IsEmpty();
}

BOOL CTPEPDataContainer::ReadMessageNumber(LPCTSTR pszMessage, double &fNumber, INT &nPos) CONST
{
	CString  szNumber;

	if (ReadMessageText(pszMessage, szNumber, nPos))
	{
		fNumber = _ttof(szNumber);
		return TRUE;
	}
	fNumber = 0.0;
	return FALSE;
}

BOOL CTPEPDataContainer::ConvertMessageTextToTimeTag(LPCTSTR pszTimeTag, CTimeTag &tTimeTag) CONST
{
	INT  nPos;
	TCHAR  szDigit;
	CString  szZero;
	CString  szTimeTag;
	SYSTEMTIME  sTime;
	CStringTools  cStringTools;

	for (szTimeTag = STRING(IDS_TPEP_PACKET_TIMETAG_NONE), szTimeTag += SPACE, szTimeTag += STRING(IDS_TPEP_PACKET_TIMETAG_NONE); !_tcscmp(pszTimeTag, szTimeTag); )
	{
		tTimeTag = 0;
		return TRUE;
	}
	for (nPos = 0, sTime.wYear = 0, szZero = cStringTools.ConvertIntToString(0); nPos < lstrlen(pszTimeTag); nPos++)
	{
		if (_istdigit((szDigit = pszTimeTag[nPos])))
		{
			sTime.wYear = 10 * sTime.wYear;
			sTime.wYear += (WORD)(szDigit - szZero[0]);
			continue;
		}
		nPos++;
		break;
	}
	for (sTime.wMonth = 0; nPos < lstrlen(pszTimeTag); nPos++)
	{
		if (_istdigit((szDigit = pszTimeTag[nPos])))
		{
			sTime.wMonth = 10 * sTime.wMonth;
			sTime.wMonth += (WORD)(szDigit - szZero[0]);
			continue;
		}
		nPos++;
		break;
	}
	for (sTime.wDay = 0; nPos < lstrlen(pszTimeTag); nPos++)
	{
		if (_istdigit((szDigit = pszTimeTag[nPos])))
		{
			sTime.wDay = 10 * sTime.wDay;
			sTime.wDay += (WORD)(szDigit - szZero[0]);
			continue;
		}
		nPos++;
		break;
	}
	for (sTime.wHour = 0; nPos < lstrlen(pszTimeTag); nPos++)
	{
		if (_istdigit((szDigit = pszTimeTag[nPos])))
		{
			sTime.wHour = 10 * sTime.wHour;
			sTime.wHour += (WORD)(szDigit - szZero[0]);
			continue;
		}
		nPos++;
		break;
	}
	for (sTime.wMinute = 0; nPos < lstrlen(pszTimeTag); nPos++)
	{
		if (_istdigit((szDigit = pszTimeTag[nPos])))
		{
			sTime.wMinute = 10 * sTime.wMinute;
			sTime.wMinute += (WORD)(szDigit - szZero[0]);
			continue;
		}
		nPos++;
		break;
	}
	for (sTime.wSecond = 0; nPos < lstrlen(pszTimeTag); nPos++)
	{
		if (_istdigit((szDigit = pszTimeTag[nPos])))
		{
			sTime.wSecond = 10 * sTime.wSecond;
			sTime.wSecond += (WORD)(szDigit - szZero[0]);
			continue;
		}
		nPos++;
		break;
	}
	for (sTime.wMilliseconds = 0; nPos < lstrlen(pszTimeTag); nPos++)
	{
		if (_istdigit((szDigit = pszTimeTag[nPos])))
		{
			sTime.wMilliseconds = 10 * sTime.wMilliseconds;
			sTime.wMilliseconds += (WORD)(szDigit - szZero[0]);
			continue;
		}
		nPos++;
		break;
	}
	tTimeTag = CTimeTag(sTime);
	tTimeTag = CTimeTag(tTimeTag.GetTime() - tTimeTag.GetBias());
	return TRUE;
}

CString CTPEPDataContainer::ConvertMessagePositionToParameter(CONST POINT &point) CONST
{
	INT  nIndex;

	return(((nIndex = ConvertMessagePositionToIndex(point)) < m_szParameterIDs.GetSize()) ? (LPCTSTR)m_szParameterIDs.GetAt(nIndex) : EMPTYSTRING);
}

INT CTPEPDataContainer::ConvertMessagePositionToIndex(CONST POINT &point) CONST
{
	INT  nIndex[2];

	for (nIndex[0] = 0, nIndex[1] = point.y*m_nParameterCount; nIndex[0] <= point.x && nIndex[0] < m_nLayoutColumns.GetSize(); nIndex[0]++)
	{
		if (m_nLayoutColumns.GetAt(nIndex[0]) == TPEP_TITLEITEM_ID  &&  nIndex[0] > 0)
		{
			nIndex[1]++;
			continue;
		}
	}
	return nIndex[1];
}

UINT CTPEPDataContainer::PointToRow(CONST POINT &point) CONST
{
	INT  nRow;
	INT  nColumn;

	return((FindTextFromPoint(point, nRow, nColumn, FALSE) && nRow < GetTextCount()) ? nRow : -1);
}

UINT CTPEPDataContainer::PointToColumn(CONST POINT &point) CONST
{
	INT  nRow;
	INT  nColumn;

	return((FindTextFromPoint(point, nRow, nColumn, FALSE) && nRow < GetTextCount()) ? ((m_nType == TPEP_TYPE_NORMAL) ? ((nColumn >= 0 && nColumn < m_nLayoutColumns.GetSize()) ? m_nLayoutColumns.GetAt(nColumn) : -1) : TPEP_TITLEITEM_MESSAGES) : -1);
}

POINT CTPEPDataContainer::PointToPoint(CONST POINT &point) CONST
{
	INT  nRow;
	INT  nColumn;

	return((FindTextFromPoint(point, nRow, nColumn, FALSE) && nRow < GetTextCount()) ? CPoint(nColumn, nRow) : CPoint(-1, -1));
}

CString CTPEPDataContainer::ConstructToolTipTitle(LPCTSTR pszParameter, LPCTSTR pszError) CONST
{
	CString  szTitle;

	if (m_nType == TPEP_TYPE_NORMAL)
	{
		szTitle.Format(STRING(IDS_TPEP_TOOLTIP_TITLE_NORMAL), pszParameter);
		szTitle = (lstrlen(pszError) > 0) ? (CString(STRING(IDS_TPEP_TOOLTIP_TITLE_SIMPLE)) + STRING(IDS_TPEP_TOOLTIP_TYPE_PARAMETERS)) : szTitle;
	}
	return szTitle;
}
CString CTPEPDataContainer::ConstructToolTipTitle(CONST CStringArray &szPackets, CONST CStringArray &szParameters) CONST
{
	CString  szTitle;

	if (m_nType == TPEP_TYPE_SIMPLE)
	{
		szTitle = (szPackets.GetSize() > 0) ? (LPCTSTR)(CString(STRING(IDS_TPEP_TOOLTIP_TITLE_SIMPLE)) + STRING(IDS_TPEP_TOOLTIP_TYPE_PACKETS)) : STRING(IDS_TPEP_TOOLTIP_TITLE_SIMPLE);
		szTitle += (szParameters.GetSize() > 0) ? STRING(IDS_TPEP_TOOLTIP_TYPE_PARAMETERS) : EMPTYSTRING;
	}
	return szTitle;
}

CString CTPEPDataContainer::ConstructToolTipText(CONST POINT &point, LPCTSTR pszParameter, LPCTSTR pszError) CONST
{
	INT  nIndex;
	UINT  nRawValue;
	float  fRawValue;
	CString  szValue;
	CString  szText[2];
	CString  szRawValue;
	CTimeTag  tChangeTime;
	CTimeTag  tUpdateTime;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	if (m_nType == TPEP_TYPE_NORMAL)
	{
		if ((nIndex = ConvertMessagePositionToIndex(point)) >= 0)
		{
			if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pszParameter))))
			{
				szText[0].Format(STRING(IDS_TPEP_TOOLTIP_DESCRIPTION_PARAMETER), (LPCTSTR)pDatabaseTMParameter->GetDescription());
				if ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_NATURE_CONSTANT) == TMPARAMETER_NATURE_CONSTANT)
				{
					szText[1].Format(STRING(IDS_TPEP_TOOLTIP_RAWTEXT), (LPCTSTR)pDatabaseTMParameter->GetConstValueAsText());
					szText[0] = (!szText[0].IsEmpty()) ? (szText[0] + EOL + szText[1]) : szText[1];
				}
				else if (!m_szParameterValues[1].GetAt(nIndex).IsEmpty())
				{
					if ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) != TMPARAMETER_CODING_FLOATINGPOINT)
					{
						szText[1].Format(STRING(IDS_TPEP_TOOLTIP_RAWVALUE), _ttoi64(m_szParameterValues[1].GetAt(nIndex)));
						szText[0] = (!szText[0].IsEmpty()) ? (szText[0] + EOL + szText[1]) : szText[1];
					}
					else
					{
						CopyMemory(&nRawValue, &(fRawValue = (float)_ttof(m_szParameterValues[1].GetAt(nIndex))), sizeof(nRawValue));
						szText[1].Format(STRING(IDS_TPEP_TOOLTIP_RAWVALUE), _ttoi64(m_szParameterValues[1].GetAt(nIndex)));
						szText[0] = (!szText[0].IsEmpty()) ? (szText[0] + EOL + szText[1]) : szText[1];
					}
				}
				if (lstrlen((szRawValue = m_szParameterValues[1].GetAt(nIndex))) > 0)
				{
					szText[1].Format(STRING(IDS_TPEP_TOOLTIP_CODEDVALUE), (LPCTSTR)szRawValue, (pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN)) ? STRING(IDS_TPEP_TOOLTIP_BITVALUE) : ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) ? STRING(IDS_TPEP_TOOLTIP_SIGNEDVALUE) : ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_COMPLEMENTCOMPLEX) ? STRING(IDS_TPEP_TOOLTIP_COMPLEMENTVALUE) : ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_UNSIGNEDINTEGER) ? STRING(IDS_TPEP_TOOLTIP_UNSIGNEDVALUE) : ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) ? STRING(IDS_TPEP_TOOLTIP_FLOATINGVALUE) : STRING(IDS_TPEP_TOOLTIP_UNSIGNEDVALUE))))));
					szText[0] = (!szText[0].IsEmpty()) ? (szText[0] + EOL + szText[1]) : szText[1];
				}
				if (lstrlen((szValue = m_szParameterValues[0].GetAt(nIndex))) > 0)
				{
					szText[1].Format(((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL)) ? STRING(IDS_TPEP_TOOLTIP_CALIBRATEDNUMERICALVALUE) : STRING(IDS_TPEP_TOOLTIP_CALIBRATEDSTATUSVALUE), (LPCTSTR)szValue);
					szText[0] = (!szText[0].IsEmpty()) ? (szText[0] + EOL + szText[1]) : szText[1];
				}
				if (lstrlen(m_szParameterPackets[0].GetAt(nIndex)) > 0 && lstrlen(m_szParameterTimeTags[0][0].GetAt(nIndex)) > 0 && lstrlen(m_szParameterTimeTags[0][1].GetAt(nIndex)) > 0 && ConvertMessageTextToTimeTag(m_szParameterTimeTags[0][0].GetAt(nIndex) + SPACE + m_szParameterTimeTags[0][1].GetAt(nIndex), tChangeTime))
				{
					szText[1].Format(STRING(IDS_TPEP_TOOLTIP_VALUECHANGE), (LPCTSTR)tChangeTime.FormatGmt(), (LPCTSTR)m_szParameterPackets[0].GetAt(nIndex));
					szText[0] = (!szText[0].IsEmpty()) ? (szText[0] + EOL + szText[1]) : szText[1];
				}
				if (lstrlen(m_szParameterPackets[1].GetAt(nIndex)) > 0 && lstrlen(m_szParameterTimeTags[1][0].GetAt(nIndex)) > 0 && lstrlen(m_szParameterTimeTags[1][1].GetAt(nIndex)) > 0 && ConvertMessageTextToTimeTag(m_szParameterTimeTags[1][0].GetAt(nIndex) + SPACE + m_szParameterTimeTags[1][1].GetAt(nIndex), tUpdateTime))
				{
					szText[1].Format(STRING(IDS_TPEP_TOOLTIP_VALUEUPDATE), (LPCTSTR)tUpdateTime.FormatGmt(), (LPCTSTR)m_szParameterPackets[1].GetAt(nIndex));
					szText[0] = (!szText[0].IsEmpty()) ? (szText[0] + EOL + szText[1]) : szText[1];
				}
				if (m_nParameterStatus.GetAt(nIndex) & (TMPARAMETER_STATUS_NOLIMIT | TMPARAMETER_STATUS_SOFTLIMIT | TMPARAMETER_STATUS_HARDLIMIT | TMPARAMETER_STATUS_DELTALIMIT | TMPARAMETER_STATUS_CONSISTENCYLIMIT | TMPARAMETER_STATUS_VALID | TMPARAMETER_STATUS_INVALID))
				{
					szText[1].Format(STRING(IDS_TPEP_TOOLTIP_STATUS), (m_nParameterStatus.GetAt(nIndex) & TMPARAMETER_STATUS_GOOD) ? STRING(IDS_TPEP_TOOLTIP_GOODQUALITY) : STRING(IDS_TPEP_TOOLTIP_BADQUALITY), (m_nParameterStatus.GetAt(nIndex) & TMPARAMETER_STATUS_SOFTLIMIT) ? STRING(IDS_TPEP_TOOLTIP_SOFTOOL) : ((m_nParameterStatus.GetAt(nIndex) & TMPARAMETER_STATUS_HARDLIMIT) ? STRING(IDS_TPEP_TOOLTIP_HARDOOL) : ((m_nParameterStatus.GetAt(nIndex) & TMPARAMETER_STATUS_DELTALIMIT) ? STRING(IDS_TPEP_TOOLTIP_DELTAOOL) : ((m_nParameterStatus.GetAt(nIndex) & TMPARAMETER_STATUS_CONSISTENCYLIMIT) ? STRING(IDS_TPEP_TOOLTIP_CONSISTENCYOOL) : STRING(IDS_TPEP_TOOLTIP_NOOOL)))), (m_nParameterStatus.GetAt(nIndex) & TMPARAMETER_STATUS_VALID) ? STRING(IDS_TPEP_TOOLTIP_VALID) : STRING(IDS_TPEP_TOOLTIP_INVALID));
					szText[0] = (!szText[0].IsEmpty()) ? (szText[0] + EOL + szText[1]) : szText[1];
				}
				return szText[0];
			}
			if (lstrlen(pszError) > 0)
			{
				szText[0] = pszError;
				return szText[0];
			}
		}
	}
	return szText[0];
}
CString CTPEPDataContainer::ConstructToolTipText(CONST CStringArray &szPackets, CONST CStringArray &szParameters, CONST CStringArray &szErrors) CONST
{
	INT  nPacket;
	INT  nPackets;
	INT  nParameter;
	INT  nParameters;
	CString  szText[2];
	CDatabaseTMPacket  *pDatabaseTMPacket;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	if (m_nType == TPEP_TYPE_SIMPLE)
	{
		for (nPacket = 0, nPackets = (INT)szPackets.GetSize(), szText[0].Empty(); nPacket < nPackets; nPacket++)
		{
			if ((pDatabaseTMPacket = GetDatabase()->GetTMPackets()->GetAt(GetDatabase()->GetTMPackets()->Find(szPackets.GetAt(nPacket)))))
			{
				szText[1].Format(STRING(IDS_TPEP_TOOLTIP_DESCRIPTION_MESSAGE), (LPCTSTR)pDatabaseTMPacket->GetTag(), (LPCTSTR)pDatabaseTMPacket->GetDescription());
				szText[0] += (!szText[0].IsEmpty()) ? (EOL + szText[1]) : szText[1];
			}
		}
		for (nParameter = 0, nParameters = (INT)szParameters.GetSize(); nParameter < nParameters; nParameter++)
		{
			if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(szParameters.GetAt(nParameter)))))
			{
				szText[1].Format(STRING(IDS_TPEP_TOOLTIP_DESCRIPTION_MESSAGE), (LPCTSTR)pDatabaseTMParameter->GetTag(), (LPCTSTR)pDatabaseTMParameter->GetDescription());
				szText[0] += (!szText[0].IsEmpty()) ? (EOL + szText[1]) : szText[1];
			}
		}
		if (szErrors.GetSize() > 0)
		{
			szText[0] = szErrors.GetAt(0);
			return szText[0];
		}
	}
	return szText[0];
}

BOOL CTPEPDataContainer::LoadToolTipCursor()
{
	return(((m_hToolTipCursor = (HCURSOR)LoadImage(GetModuleHandle((LPCTSTR)NULL), MAKEINTRESOURCE(IDC_TOOLTIPCURSOR), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR))) ? TRUE : FALSE);
}

HCURSOR CTPEPDataContainer::GetToolTipCursor() CONST
{
	return((!m_hToolTipCursor) ? (HCURSOR)(DWORD_PTR)GetClassLongPtr(GetSafeHwnd(), GCLP_HCURSOR) : m_hToolTipCursor);
}

BOOL CTPEPDataContainer::FreeToolTipCursor()
{
	if (m_hToolTipCursor)
	{
		DestroyCursor(m_hToolTipCursor);
		m_hToolTipCursor = (HCURSOR)NULL;
		return TRUE;
	}
	return FALSE;
}

VOID CTPEPDataContainer::DoAlert(CTPEPAlert *pAlert)
{
	WORD  wAge;
	WORD  wGender;
	DWORD  dwPitch;
	DWORD  dwVolume;
	DWORD  dwPlayback;
	CString  szAdapter;
	CString  szSpeaker;
	CString  szAudition;
	CString  szNotification;
	CEventObject  *pEvent;
	CAuditionProfiles  pAuditionProfiles;
	CAuditionProfileInfo  *pAuditionProfileInfo;

	if ((pAlert->GetOptions() & TPEPALERT_OPTION_ACTIVATED) != TPEPALERT_OPTION_ACTIVATED && (pAlert->GetOptions() & TPEPALERT_OPTION_DISABLED) != TPEPALERT_OPTION_DISABLED  &&  lstrlen((szAudition = pAlert->GetAudition())) > 0 && szAudition != STRING(IDS_TPEPALERTSDIALOG_AUDITION_NONE))
	{
		if ((pAuditionProfileInfo = (GetAuditionProfiles(pAuditionProfiles)) ? pAuditionProfiles.GetAt(pAuditionProfiles.Find(szAudition)) : (CAuditionProfileInfo *)NULL))
		{
			for (pAuditionProfileInfo->GetAdapterInfo(szAdapter, dwVolume, dwPitch, dwPlayback), pAuditionProfileInfo->GetVoiceSound(szSpeaker, wGender, wAge); (pEvent = new CEventObject); )
			{
				pEvent->SetCategory(EVENT_CATEGORY_SYSTEM);
				pEvent->SetType(STRING(IDS_EVENTTYPE_SUCCESS));
				pEvent->SetAudition(pAuditionProfileInfo->GetAudition());
				pEvent->SetAudioInfo(szAdapter, dwVolume, dwPitch, dwPlayback);
				pEvent->SetAuditBeep(pAuditionProfileInfo->GetBeepSound());
				pEvent->SetAuditWave(pAuditionProfileInfo->GetWaveSound());
				pEvent->SetAuditVoice(szSpeaker, wGender, wAge);
				pEvent->SetAuditTime(CTime::GetCurrentTime().GetTime());
				pEvent->SetMessage(pAlert->GetText());
				pEvent->SetAuditColor(VGA_COLOR_BLACK);
				pEvent->SetUser(GetAccountUserName());
				pEvent->Acknowledge(FALSE);
				pEvent->Show(TRUE);
				ReportEvent(pEvent);
				break;
			}
		}
	}
	if ((pAlert->GetOptions() & TPEPALERT_OPTION_ACTIVATED) != TPEPALERT_OPTION_ACTIVATED)
	{
		if ((pAlert->GetOptions() & TPEPALERT_OPTION_DISABLED) != TPEPALERT_OPTION_DISABLED  &&  lstrlen((szNotification = pAlert->GetNotification())) > 0 && szNotification != STRING(IDS_TPEPALERTSDIALOG_NOTIFICATION_NONE)) DoNotification(szNotification, pAlert->GetText());
		pAlert->SetOptions(pAlert->GetOptions() | TPEPALERT_OPTION_ACTIVATED);
	}
}

BOOL CTPEPDataContainer::AdjustColumns()
{
	CDC  *pDC;
	INT  nItem;
	INT  nItems;
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CFont  *pOldFont;
	CString  szText;
	CUIntArray  nWidths[2];
	CStringArray  szColumns;

	if ((pDC = (IsWindow(GetSafeHwnd())) ? GetDC() : (CDC *)NULL))
	{
		if ((pOldFont = pDC->SelectObject(&m_wndContentCtrl.m_cFont)))
		{
			for (nColumn = 0, nColumns = (GetColumns(szColumns) && CalcColumnsWidth(szColumns, nWidths[0]) > 0) ? (INT)szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
			{
				for (nItem = 0, nItems = GetTextCount(), nWidth = 0; nItem < nItems; nItem = nItem + 1)
				{
					if (GetText(nItem, nColumn, szText)) nWidth = max(pDC->GetTextExtent(szText).cx, nWidth);
					continue;
				}
				nWidth = (nColumn > 0) ? max(nWidths[0].GetAt(nColumn) - nWidths[0].GetAt(nColumn - 1), (UINT)(LOWORD(GetTextIndents()) + HIWORD(GetTextIndents()) + nWidth)) : max(nWidths[0].GetAt(0), (UINT)(LOWORD(GetTextIndents()) + HIWORD(GetTextIndents()) + nWidth));
				nWidths[1].SetAtGrow(nColumn, (nColumn > 0) ? (nWidths[1].GetAt(nColumn - 1) + nWidth) : nWidth);
			}
			if (nColumn == nColumns  &&  nColumns > 0)
			{
				if (SetColumns(szColumns, nWidths[1]))
				{
					pDC->SelectObject(pOldFont);
					ReleaseDC(pDC);
					return TRUE;
				}
			}
			pDC->SelectObject(pOldFont);
		}
		ReleaseDC(pDC);
	}
	return FALSE;
}

VOID CTPEPDataContainer::RecalcLayout()
{
	if (IsWindow(GetSafeHwnd()))
	{
		if (m_nType == TPEP_TYPE_SIMPLE && (GetStyle() & TVS_HEADER))
		{
			m_wndHeaderCtrl.ModifyStyle(WS_VISIBLE, 0);
			ModifyStyle(TVS_HEADER | TVS_TOP, 0);
		}
		if (m_nType == TPEP_TYPE_NORMAL && (GetStyle() & TVS_HEADER) != TVS_HEADER)
		{
			m_wndHeaderCtrl.ModifyStyle(0, WS_VISIBLE);
			ModifyStyle(0, TVS_HEADER | TVS_TOP);
		}
	}
	CTextView::RecalcLayout();
}

void CTPEPDataContainer::PostNcDestroy()
{
	m_nLayoutColumns.RemoveAll();
	m_szParameterIDs.RemoveAll();
	m_szParameterValues[0].RemoveAll();
	m_szParameterValues[1].RemoveAll();
	m_szParameterPackets[0].RemoveAll();
	m_szParameterPackets[1].RemoveAll();
	m_szParameterTimeTags[0][0].RemoveAll();
	m_szParameterTimeTags[0][1].RemoveAll();
	m_szParameterTimeTags[1][0].RemoveAll();
	m_szParameterTimeTags[1][1].RemoveAll();
	m_nParameterStatus.RemoveAll();
	m_nFilterOOLColors.RemoveAll();
	CTextView::PostNcDestroy();
}

BOOL CTPEPDataContainer::Lock()
{
	return((IsWindow(GetSafeHwnd())) ? (GetParentDisplay()->Lock() && CTextView::Lock()) : CTextView::Lock());
}

BOOL CTPEPDataContainer::Unlock()
{
	return((IsWindow(GetSafeHwnd())) ? (CTextView::Unlock() && GetParentDisplay()->Unlock()) : CTextView::Unlock());
}

BEGIN_MESSAGE_MAP(CTPEPDataContainer, CTextView)
	//{{AFX_MSG_MAP(CTPEPDataContainer)
	ON_WM_CREATE()
	ON_WM_SETCURSOR()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTPEPDataContainer message handlers

int CTPEPDataContainer::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CTextViewLock  cLock(this);

	if (CTextView::OnCreate(lpCreateStruct) != -1)
	{
		LoadToolTipCursor();
		return 0;
	}
	return -1;
}

BOOL CTPEPDataContainer::OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message)
{
	POINT  ptCursor;
	CRect  rContent;
	CTextViewLock  cLock(this);

	for (GetCursorPos(&ptCursor), m_wndContentCtrl.ScreenToClient(&ptCursor), m_wndContentCtrl.GetClientRect(rContent); rContent.PtInRect(ptCursor); )
	{
		if (GetParentDisplay()->IsRetrievingData())
		{
			SetCursor(LoadCursor((HINSTANCE)NULL, IDC_WAIT));
			return TRUE;
		}
		switch (PointToColumn(ptCursor))
		{
		case TPEP_TITLEITEM_ID:
		case TPEP_TITLEITEM_DESCRIPTION:
		case TPEP_TITLEITEM_VALUE:
		case TPEP_TITLEITEM_UNIT:
		case TPEP_TITLEITEM_CHANGETMUNIT:
		case TPEP_TITLEITEM_CHANGETIME:
		case TPEP_TITLEITEM_UPDATETMUNIT:
		case TPEP_TITLEITEM_UPDATETIME:
		case TPEP_TITLEITEM_MESSAGES:
		{ if (IsToolTipModeEnabled())
		{
			SetCursor(GetToolTipCursor());
			return TRUE;
		}
		}
		default: break;
		}
		break;
	}
	return CTextView::OnSetCursor(pWnd, nHitTest, message);
}

BOOL CTPEPDataContainer::OnContentMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	CFont  cFont[2];
	CPoint  ptToolTip;
	LOGFONT  lfFont[2];
	CString  szError;
	CString  szParameter;
	CString  szToolTip[2];
	CStringArray  szErrors;
	CStringArray  szPackets;
	CStringArray  szParameters;
	CTextViewLock  cLock(this);

	if (message == WM_KEYDOWN)
	{
		if (wParam == VK_TAB) GetParent()->SetFocus();
		return FALSE;
	}
	if (message == WM_LBUTTONDBLCLK)
	{
		if (!GetParentDisplay()->IsRetrievingData())
		{
			if (m_cConnection.GetType() == TPEP_TYPE_PARAMETERS)
			{
				for (szParameter = ConvertMessagePositionToParameter(PointToPoint(CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)))), cLock.Release(); !szParameter.IsEmpty(); )
				{
					GetParentDisplay()->SetParameterInfo(szParameter);
					break;
				}
			}
		}
		return FALSE;
	}
	if (message == WM_RBUTTONDOWN)
	{
		if (!GetParentDisplay()->IsRetrievingData())
		{
			switch (PointToColumn((ptToolTip = CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)))))
			{
			case TPEP_TITLEITEM_ID:
			case TPEP_TITLEITEM_DESCRIPTION:
			case TPEP_TITLEITEM_VALUE:
			case TPEP_TITLEITEM_UNIT:
			case TPEP_TITLEITEM_CHANGETMUNIT:
			case TPEP_TITLEITEM_CHANGETIME:
			case TPEP_TITLEITEM_UPDATETMUNIT:
			case TPEP_TITLEITEM_UPDATETIME:
			case TPEP_TITLEITEM_MESSAGES:
			{ if (IsToolTipModeEnabled())
			{
				if (m_nType == TPEP_TYPE_NORMAL)
				{
					if (ParseMessage(PointToPoint(ptToolTip), szParameter, szError))
					{
						for (szToolTip[0] = ConstructToolTipTitle(szParameter, szError), szToolTip[1] = ConstructToolTipText(PointToPoint(ptToolTip), szParameter, szError), GetTextFont(&lfFont[0]), GetTextFont(&lfFont[1]), lfFont[0].lfWeight = FW_BOLD, lfFont[1].lfWeight = FW_NORMAL; cFont[0].CreateFontIndirect(&lfFont[0]) && cFont[1].CreateFontIndirect(&lfFont[1]); )
						{
							m_wndToolTip.SetTitleFont(&cFont[0]);
							m_wndToolTip.SetTextFont(&cFont[1]);
							break;
						}
						m_wndToolTip.Create(&m_wndContentCtrl, ptToolTip, szToolTip[0], szToolTip[1]);
					}
					break;
				}
				if (m_nType == TPEP_TYPE_SIMPLE)
				{
					if (ParseMessage(m_wndContentCtrl.m_szContentText.GetAt(PointToPoint(ptToolTip).y), szPackets, szParameters, szErrors))
					{
						for (szToolTip[0] = ConstructToolTipTitle(szPackets, szParameters), szToolTip[1] = ConstructToolTipText(szPackets, szParameters, szErrors), GetTextFont(&lfFont[0]), GetTextFont(&lfFont[1]), lfFont[0].lfWeight = FW_BOLD, lfFont[1].lfWeight = FW_NORMAL; cFont[0].CreateFontIndirect(&lfFont[0]) && cFont[1].CreateFontIndirect(&lfFont[1]); )
						{
							m_wndToolTip.SetTitleFont(&cFont[0]);
							m_wndToolTip.SetTextFont(&cFont[1]);
							break;
						}
						m_wndToolTip.Create(&m_wndContentCtrl, ptToolTip, szToolTip[0], szToolTip[1]);
					}
					break;
				}
			}
			}
			default: break;
			}
		}
	}
	if (message == WM_RBUTTONUP)
	{
		m_wndToolTip.Destroy();
		return FALSE;
	}
	return FALSE;
}

void CTPEPDataContainer::OnDestroy()
{
	CTextViewLock  cLock(this);

	FreeToolTipCursor();
	CTextView::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CTPEPDataHeaderCtrl

IMPLEMENT_DYNCREATE(CTPEPDataHeaderCtrl, CMFCHeaderCtrl)

CTPEPDataHeaderCtrl::CTPEPDataHeaderCtrl() : CMFCHeaderCtrl()
{
	CFontTools  cFontTools(&m_cFont);

	m_wTextIndent[0] = m_wTextIndent[1] = 0;
	m_wTextSpacing[0] = m_wTextSpacing[1] = 0;
	m_pParentWnd = (CTPEPView *)NULL;
}

BOOL CTPEPDataHeaderCtrl::Create(CTPEPView *pParentWnd, DWORD dwStyle, UINT nID)
{
	return CMFCHeaderCtrl::Create(dwStyle, CRect(0, 0, 0, 0), pParentWnd, nID);
}

BOOL CTPEPDataHeaderCtrl::SetTitle(LPCTSTR pszTitle)
{
	HDITEM  sItem;
	TCHAR  szItem[32];

	for (sItem.mask = HDI_TEXT | HDI_FORMAT, sItem.fmt = HDF_STRING | HDF_LEFT, _tcscpy_s((sItem.pszText = szItem), sizeof(szItem) / sizeof(TCHAR), (m_szTitle = pszTitle)); IsWindow(GetSafeHwnd()); )
	{
		if ((!GetItemCount() && InsertItem(0, &sItem) >= 0) || (GetItemCount() > 0 && SetItem(0, &sItem))) return TRUE;
		return FALSE;
	}
	return TRUE;
}

CString CTPEPDataHeaderCtrl::GetTitle() CONST
{
	return m_szTitle;
}

BOOL CTPEPDataHeaderCtrl::SetFont(CFont *pFont)
{
	LOGFONT  lfFont[2];

	if (!m_cFont.GetSafeHandle() || !pFont->GetLogFont(&lfFont[0]) || !m_cFont.GetLogFont(&lfFont[1]) || memcmp(&lfFont[0], &lfFont[1], sizeof(LOGFONT)))
	{
		for (m_cFont.DeleteObject(); pFont->GetLogFont(&lfFont[0]) > 0 && m_cFont.CreateFontIndirect(&lfFont[0]); )
		{
			m_wTextIndent[0] = m_wTextIndent[1] = CalcDefaultIndent();
			m_wTextSpacing[0] = m_wTextSpacing[1] = CalcDefaultSpacing();
			return TRUE;
		}
		return FALSE;
	}
	return TRUE;
}
BOOL CTPEPDataHeaderCtrl::SetFont(CONST LOGFONT *plfFont)
{
	CFont  cFont;

	return((cFont.CreateFontIndirect(plfFont) && SetFont(&cFont)) ? TRUE : FALSE);
}

BOOL CTPEPDataHeaderCtrl::GetFont(CFont *pFont) CONST
{
	LOGFONT  lfFont;

	return(GetFont(&lfFont) && pFont->CreateFontIndirect(&lfFont));
}

BOOL CTPEPDataHeaderCtrl::GetFont(LOGFONT *plfFont) CONST
{
	return((m_cFont.GetSafeHandle() != (HGDIOBJ)NULL  &&  m_cFont.GetObject(sizeof(LOGFONT), plfFont) > 0) ? TRUE : FALSE);
}

WORD CTPEPDataHeaderCtrl::CalcDefaultIndent() CONST
{
	INT  nIndent;
	CFont  *pOldFont;
	CClientDC  cDC(NULL);

	if ((pOldFont = cDC.SelectObject((CFont *)&m_cFont)))
	{
		nIndent = GetSystemMetrics(SM_CXEDGE) + cDC.GetTextExtent(SPACE).cy / 4;
		cDC.SelectObject(pOldFont);
		return nIndent;
	}
	return 0;
}

WORD CTPEPDataHeaderCtrl::CalcDefaultSpacing() CONST
{
	return GetSystemMetrics(SM_CYEDGE) + GetSystemMetrics(SM_CYBORDER);
}

CTPEPView *CTPEPDataHeaderCtrl::GetParent() CONST
{
	return m_pParentWnd;
}

BEGIN_MESSAGE_MAP(CTPEPDataHeaderCtrl, CMFCHeaderCtrl)
	//{{AFX_MSG_MAP(CTPEPDataHeaderCtrl)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTPEPDataHeaderCtrl message handlers

int CTPEPDataHeaderCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CFontTools  cFontTools;

	if (CMFCHeaderCtrl::OnCreate(lpCreateStruct) != -1)
	{
		m_wTextIndent[0] = m_wTextIndent[1] = CalcDefaultIndent();
		m_wTextSpacing[0] = CalcDefaultSpacing();
		m_wTextSpacing[1] = m_wTextSpacing[0] + 1;
		return 0;
	}
	return -1;
}

BOOL CTPEPDataHeaderCtrl::OnEraseBkgnd(CDC *pDC)
{
	UpdateWindow();
	return TRUE;
}

void CTPEPDataHeaderCtrl::OnDrawItem(CDC *pDC, int iItem, CRect rect, BOOL bIsPressed, BOOL bIsHighlighted)
{
	UINT  nFlags;
	CRect  rItem;
	CFont  *pOldFont;
	TCHAR  szText[256];
	HD_ITEM  sItem;

	for (CMFCVisualManager::GetInstance()->OnDrawHeaderCtrlBorder(this, pDC, rect, bIsPressed, bIsHighlighted), sItem.mask = HDI_FORMAT | HDI_TEXT, sItem.pszText = szText, sItem.cchTextMax = sizeof(szText) / sizeof(TCHAR); iItem >= 0; )
	{
		if ((pOldFont = (GetItem(iItem, &sItem) && (sItem.fmt & HDF_STRING) == HDF_STRING  &&  sItem.pszText != (LPTSTR)NULL) ? pDC->SelectObject(&m_cFont) : (CFont *)NULL) != (CFont *)NULL)
		{
			for (rItem = rect, rItem.DeflateRect(m_wTextIndent[0], m_wTextSpacing[0], m_wTextIndent[1], m_wTextSpacing[1]), nFlags = ((sItem.fmt & HDF_CENTER) ? DT_CENTER : 0) | ((sItem.fmt & HDF_RIGHT) ? DT_RIGHT : 0) | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS | DT_NOPREFIX | DT_WORD_ELLIPSIS; lstrlen(sItem.pszText) > 0; )
			{
				pDC->DrawText(sItem.pszText, (bIsPressed) ? CRect(rItem.left + 1, rItem.top + 1, rItem.right + 1, rItem.bottom + 1) : rItem, nFlags);
				break;
			}
			pDC->SelectObject(pOldFont);
		}
		break;
	}
}


/////////////////////////////////////////////////////////////////////////////
// CTPEPView

IMPLEMENT_DYNCREATE(CTPEPView, CWnd)

CTPEPView::CTPEPView() : CWnd()
{
	m_sizeTrackLayout.cx = 0;
	m_sizeTrackLayout.cy = 0;
	m_pwndHeaderCtrl = new CTPEPDataHeaderCtrl;
	m_pwndView = new CTPEPDataContainer;
	m_pParentWnd = (CWnd *)NULL;
}

CTPEPView::~CTPEPView()
{
	delete m_pwndHeaderCtrl;
	delete m_pwndView;
}

BOOL CTPEPView::Create(CWnd *pParentWnd)
{
	if (CWnd::Create(AfxRegisterWndClass(CS_NOCLOSE, LoadCursor((HINSTANCE)NULL, IDC_ARROW), GetSysColorBrush(COLOR_WINDOW)), (LPCTSTR)NULL, WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE, CRect(0, 0, 0, 0), (m_pParentWnd = pParentWnd), 0))
	{
		SetTitle(STRING(IDS_TPEP_TITLEITEM_MESSAGES));
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPView::SetTitle(LPCTSTR pszTitle)
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndHeaderCtrl->SetTitle(pszTitle);
}

BOOL CTPEPView::GetTitle(CString &szTitle) CONST
{
	CTextViewLock  cLock(m_pwndView);

	return(!(szTitle = m_pwndHeaderCtrl->GetTitle()).IsEmpty());
}

BOOL CTPEPView::SetLayout(UINT nType)
{
	CTextViewLock  cLock(m_pwndView);

	for (m_pwndView->SetLayout(nType); nType == TPEP_TYPE_NORMAL; )
	{
		if (IsWindow(GetSafeHwnd()))
		{
			SetTitle(EMPTYSTRING);
			RecalcLayout();
		}
		return TRUE;
	}
	if (nType == TPEP_TYPE_SIMPLE)
	{
		if (IsWindow(GetSafeHwnd()))
		{
			SetTitle(STRING(IDS_TPEP_TITLEITEM_MESSAGES));
			RecalcLayout();
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPView::GetLayout(UINT &nType) CONST
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndView->GetLayout(nType);
}

BOOL CTPEPView::SetLayoutColumns(CONST CUIntArray &nColumns)
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndView->SetLayoutColumns(nColumns);
}
BOOL CTPEPView::SetLayoutColumns(CONST CUIntArray &nColumns, CONST CUIntArray &nWidths)
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndView->SetLayoutColumns(nColumns, nWidths);
}

BOOL CTPEPView::GetLayoutColumns(CUIntArray &nColumns) CONST
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndView->GetLayoutColumns(nColumns);
}
BOOL CTPEPView::GetLayoutColumns(CUIntArray &nColumns, CUIntArray &nWidths) CONST
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndView->GetLayoutColumns(nColumns, nWidths);
}

BOOL CTPEPView::SetTitleFont(CONST LOGFONT *plfFont)
{
	LOGFONT  lfFont;
	CTextViewLock  cLock(m_pwndView);

	if (!m_pwndHeaderCtrl->GetFont(&lfFont) || memcmp(plfFont, &lfFont, sizeof(LOGFONT)))
	{
		if (m_pwndHeaderCtrl->SetFont(plfFont) && m_pwndView->SetTitleFont(plfFont))
		{
			RecalcLayout();
			return TRUE;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CTPEPView::GetTitleFont(LOGFONT *plfFont) CONST
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndHeaderCtrl->GetFont(plfFont);
}

BOOL CTPEPView::SetMessagesFont(CONST LOGFONT *plfFont)
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndView->SetMessagesFont(plfFont);
}

BOOL CTPEPView::GetMessagesFont(LOGFONT *plfFont) CONST
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndView->GetMessagesFont(plfFont);
}

BOOL CTPEPView::EnableToolTipMode(BOOL bEnable)
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndView->EnableToolTipMode(bEnable);
}

BOOL CTPEPView::IsToolTipModeEnabled() CONST
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndView->IsToolTipModeEnabled();
}

BOOL CTPEPView::SetFilterMode(UINT nMode)
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndView->SetFilterMode(nMode);
}

BOOL CTPEPView::GetFilterMode(UINT &nMode) CONST
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndView->GetFilterMode(nMode);
}

BOOL CTPEPView::SetFilterLimit(UINT nLimit)
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndView->SetFilterLimit(nLimit);
}

BOOL CTPEPView::GetFilterLimit(UINT &nLimit) CONST
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndView->GetFilterLimit(nLimit);
}

BOOL CTPEPView::SetFilterStatus(UINT nStatus)
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndView->SetFilterStatus(nStatus);
}

BOOL CTPEPView::GetFilterStatus(UINT &nStatus) CONST
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndView->GetFilterStatus(nStatus);
}

BOOL CTPEPView::SetFilterRange(CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime)
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndView->SetFilterRange(tStartTime, tStopTime);
}

BOOL CTPEPView::GetFilterRange(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndView->GetFilterRange(tStartTime, tStopTime);
}

BOOL CTPEPView::SetFilterDailyRange(CONST CTimeSpan &tStartTime, CONST CTimeSpan &tStopTime)
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndView->SetFilterDailyRange(tStartTime, tStopTime);
}

BOOL CTPEPView::GetFilterDailyRange(CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndView->GetFilterDailyRange(tStartTime, tStopTime);
}

BOOL CTPEPView::SetFilterPeriodicalRange(CONST CTimeKey &tStartTime, CONST CTimeSpan &tInterval, CONST CTimeKey &tStopTime)
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndView->SetFilterPeriodicalRange(tStartTime, tInterval, tStopTime);
}

BOOL CTPEPView::GetFilterPeriodicalRange(CTimeKey &tStartTime, CTimeSpan &tInterval, CTimeKey &tStopTime) CONST
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndView->GetFilterPeriodicalRange(tStartTime, tInterval, tStopTime);
}

BOOL CTPEPView::SetFilterDigits(UINT nDigits)
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndView->SetFilterDigits(nDigits);
}

BOOL CTPEPView::GetFilterDigits(UINT &nDigits) CONST
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndView->GetFilterDigits(nDigits);
}

BOOL CTPEPView::SetFilterColors()
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndView->SetFilterColors();
}
BOOL CTPEPView::SetFilterColors(COLORREF nColor, CONST CUIntArray &nOOLColors)
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndView->SetFilterColors(nColor, nOOLColors);
}

BOOL CTPEPView::GetFilterColors(COLORREF &nColor, CUIntArray &nOOLColors) CONST
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndView->GetFilterColors(nColor, nOOLColors);
}

BOOL CTPEPView::SetAlerts(CONST CTPEPAlerts &pAlerts)
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndView->SetAlerts(pAlerts);
}

BOOL CTPEPView::GetAlerts(CTPEPAlerts &pAlerts) CONST
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndView->GetAlerts(pAlerts);
}

BOOL CTPEPView::AddMessage(LPCTSTR pszMessage)
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndView->AddMessage(pszMessage);
}

BOOL CTPEPView::ClearAllMessages()
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndView->ClearAllMessages();
}

INT CTPEPView::GetMessageCount() CONST
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndView->GetMessageCount();
}

BOOL CTPEPView::SetConnectionProperties(CONST CTPEPConnection *pConnection)
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndView->SetConnectionProperties(pConnection);
}
BOOL CTPEPView::SetConnectionProperties(LPCTSTR pszComputer, CONST CTPEPConnection *pConnection, BOOL bConnection)
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndView->SetConnectionProperties(pszComputer, pConnection, bConnection);
}

BOOL CTPEPView::GetConnectionProperties(CTPEPConnection *pConnection) CONST
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndView->GetConnectionProperties(pConnection);
}
BOOL CTPEPView::GetConnectionProperties(CString &szComputer, CTPEPConnection *pConnection, BOOL &bConnection) CONST
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndView->GetConnectionProperties(szComputer, pConnection, bConnection);
}

BOOL CTPEPView::GetPrintProperties(CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, CStringArray &szParameterValues, CUIntArray &nParameterStatus, CUIntArray &nOOLColors, LOGFONT *pTitleFont, LOGFONT *pMessagesFont, LOGFONT *pValuesFont) CONST
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndView->GetPrintProperties(szColumns, szContents, pAttributes, szParameterValues, nParameterStatus, nOOLColors, pTitleFont, pMessagesFont, pValuesFont);
}

VOID CTPEPView::SetTrackSize(CONST SIZE &size)
{
	CTextViewLock  cLock(m_pwndView);

	m_sizeTrackLayout = size;
}

CSize CTPEPView::GetTrackSize() CONST
{
	CTextViewLock  cLock(m_pwndView);

	return m_sizeTrackLayout;
}

CTPEPWnd *CTPEPView::GetParent() CONST
{
	return((CTPEPWnd *)m_pParentWnd);
}

VOID CTPEPView::RecalcLayout()
{
	CDC  *pDC;
	CWnd  *pWnd;
	CRect  rWnd;
	CRect  rView;
	CFont  cFont;
	CFont  *pOldFont;
	HDITEM  sHeaderItem;
	LOGFONT  lfFont;
	TEXTMETRIC  tmFont;
	CTextViewLock  cLock(m_pwndView);

	if (CThread::IsSameThread(this))
	{
		for (pWnd = GetParent()->GetWindow(GW_CHILD), GetParent()->GetClientRect(rView); pWnd != (CWnd *)NULL; pWnd = pWnd->GetNextWindow())
		{
			if (pWnd->GetSafeHwnd() != GetSafeHwnd())
			{
				pWnd->GetWindowRect(rWnd);
				GetParent()->ScreenToClient(rWnd);
				rWnd.left = rView.left;
				rWnd.right = rView.right;
				rView.SubtractRect(rView, rWnd);
			}
		}
		for (MoveWindow(rView); (pDC = GetDC()); )
		{
			if ((pOldFont = (GetTitleFont(&lfFont) && cFont.CreateFontIndirect(&lfFont)) ? pDC->SelectObject(&cFont) : (CFont *)NULL))
			{
				for (GetClientRect(rView); HIWORD(GetParent()->GetType()) != TPEP_TYPE_NORMAL; )
				{
					for (sHeaderItem.mask = HDI_WIDTH, sHeaderItem.cxy = rView.Width() + GetSystemMetrics(SM_CXEDGE); pDC->GetTextMetrics(&tmFont); )
					{
						for (m_pwndHeaderCtrl->MoveWindow(CRect(rView.left, rView.top, rView.right, rView.top + 2 * (GetSystemMetrics(SM_CYEDGE) + GetSystemMetrics(SM_CYBORDER)) + tmFont.tmHeight)), m_pwndView->MoveWindow(rView.left, rView.top + 2 * (GetSystemMetrics(SM_CYEDGE) + GetSystemMetrics(SM_CYBORDER)) + tmFont.tmHeight + 1, rView.Width(), rView.bottom - (rView.top + 2 * (GetSystemMetrics(SM_CYEDGE) + GetSystemMetrics(SM_CYBORDER)) + tmFont.tmHeight + 1)), m_pwndView->RecalcLayout(); m_pwndHeaderCtrl->GetItemCount() > 0; )
						{
							m_pwndHeaderCtrl->SetItem(0, &sHeaderItem);
							break;
						}
						SetTrackSize(CSize(m_pwndView->GetTrackSize().cx, m_pwndView->GetTrackSize().cy + 2 * (GetSystemMetrics(SM_CYEDGE) + GetSystemMetrics(SM_CYBORDER)) + tmFont.tmHeight));
						break;
					}
					break;
				}
				if (HIWORD(GetParent()->GetType()) == TPEP_TYPE_NORMAL)
				{
					m_pwndHeaderCtrl->MoveWindow(rView.left, rView.top, rView.Width(), 0);
					m_pwndView->MoveWindow(rView);
					m_pwndView->RecalcLayout();
					SetTrackSize(m_pwndView->GetTrackSize());
				}
				pDC->SelectObject(pOldFont);
				cFont.DeleteObject();
			}
			ReleaseDC(pDC);
			break;
		}
	}
}

BOOL CTPEPView::Lock()
{
	return m_pwndView->Lock();
}

BOOL CTPEPView::Unlock()
{
	return m_pwndView->Unlock();
}

BEGIN_MESSAGE_MAP(CTPEPView, CWnd)
	//{{AFX_MSG_MAP(CTPEPView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTPEPView message handlers

int CTPEPView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	return((CWnd::OnCreate(lpCreateStruct) != -1 && m_pwndHeaderCtrl->Create(this, CCS_TOP | WS_CHILD | WS_VISIBLE | WS_DISABLED, 0) && m_pwndView->Create(this, CRect(0, 0, 0, 0), TVS_HSCROLL | TVS_VSCROLL | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE)) ? 0 : -1);
}

void CTPEPView::OnSize(UINT nType, int cx, int cy)
{
	RecalcLayout();
	CWnd::OnSize(nType, cx, cy);
}

void CTPEPView::OnSetFocus(CWnd *pOldWnd)
{
	CWnd  *pWnd;

	if (IsWindow(pOldWnd->GetSafeHwnd()))
	{
		if ((pWnd = (!IsChild(pOldWnd)) ? (CWnd *)m_pwndView : GetParent()))
		{
			pWnd->SetFocus();
			return;
		}
	}
	CWnd::OnSetFocus(pOldWnd);
}


/////////////////////////////////////////////////////////////////////////////
// CTPEPWnd

IMPLEMENT_DYNAMIC(CTPEPWnd, CDisplayWnd)

CTPEPWnd::CTPEPWnd() : CDisplayWnd()
{
	SetType(DISPLAY_TYPE_TPEP);
	SetFilterMode();
	SetFilterLimit();
	SetFilterDigits();
	SetFilterStatus();
	SetFilterColors();
	SetRetrieveMode();
	SetUpdateInfo();
	SetHoldFlag();
}

BOOL CTPEPWnd::Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszTitle, PDISPLAYINFO pDefaultInfo, BOOL bDefault)
{
	if (CDisplayWnd::Create(pParentWnd, (!AfxIsValidString(pszTitle)) ? STRING(IDS_DISPLAY_TITLE_TPEP) : pszTitle, pDefaultInfo->rWnd, IDR_TPEPFRAME))
	{
		if (SetScope(pDefaultInfo->nScope) && SetMode(pDefaultInfo->nMode) && Customize(bDefault)) return TRUE;
		DestroyWindow();
	}
	return FALSE;
}

BOOL CTPEPWnd::SetLayout(UINT nType)
{
	return m_wndView.SetLayout(nType);
}

BOOL CTPEPWnd::GetLayout(UINT &nType) CONST
{
	return m_wndView.GetLayout(nType);
}

BOOL CTPEPWnd::SetLayoutColumns(CONST CUIntArray &nColumns)
{
	return m_wndView.SetLayoutColumns(nColumns);
}
BOOL CTPEPWnd::SetLayoutColumns(CONST CUIntArray &nColumns, CONST CUIntArray &nWidths)
{
	return m_wndView.SetLayoutColumns(nColumns, nWidths);
}

BOOL CTPEPWnd::GetLayoutColumns(CUIntArray &nColumns) CONST
{
	return m_wndView.GetLayoutColumns(nColumns);
}
BOOL CTPEPWnd::GetLayoutColumns(CUIntArray &nColumns, CUIntArray &nWidths) CONST
{
	return m_wndView.GetLayoutColumns(nColumns, nWidths);
}

BOOL CTPEPWnd::SetTitleFont(CONST LOGFONT *plfFont)
{
	if (m_wndView.SetTitleFont(plfFont))
	{
		RepositionView();
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPWnd::GetTitleFont(LOGFONT *plfFont) CONST
{
	return m_wndView.GetTitleFont(plfFont);
}

BOOL CTPEPWnd::SetMessagesFont(CONST LOGFONT *plfFont)
{
	return m_wndView.SetMessagesFont(plfFont);
}

BOOL CTPEPWnd::GetMessagesFont(LOGFONT *plfFont) CONST
{
	return m_wndView.GetMessagesFont(plfFont);
}

BOOL CTPEPWnd::EnableToolTipMode(BOOL bEnable)
{
	return m_wndView.EnableToolTipMode(bEnable);
}

BOOL CTPEPWnd::IsToolTipModeEnabled() CONST
{
	return m_wndView.IsToolTipModeEnabled();
}

BOOL CTPEPWnd::AddMessage(LPCTSTR pszMessage)
{
	CDisplayLock  cLock(this);

	if (m_wndView.AddMessage(pszMessage))
	{
		UpdateMessagePane();
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPWnd::ClearAllMessages()
{
	CDisplayLock  cLock(this);

	if (m_wndView.ClearAllMessages())
	{
		UpdateMessagePane();
		return TRUE;
	}
	return FALSE;
}

INT CTPEPWnd::GetMessageCount() CONST
{
	return m_wndView.GetMessageCount();
}

BOOL CTPEPWnd::Start()
{
	if (StartConnection() && StartSchedulePrintJobs())
	{
		Initialize(TRUE);
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPWnd::Prepare(BOOL bDialog)
{
	INT  nResult;
	CTPEPConnection  cConnection;

	if (bDialog  &&  !GetConnectionProperties(&cConnection))
	{
		if ((nResult = m_dlgOpen.Create(this)) == IDCANCEL || nResult <= 0) MDIDestroy();
		return((nResult == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
	}
	return TRUE;
}

BOOL CTPEPWnd::Check() CONST
{
	return CheckAccountPrivilege(PRIVILEGE_TPEP_VIEW);
}

VOID CTPEPWnd::Update()
{
	if (!Check())
	{
		ReportEvent(USER_INFORMATIONAL_DISPLAY_ACCESS_VIOLATION);
		DestroyWindow();
		return;
	}
	UpdateAllPanes();
	CDisplayWnd::Update();
}
BOOL CTPEPWnd::Update(LPVOID pData)
{
	CTPEPConnection  *pConnection = (CTPEPConnection *)pData;
	CDisplayLock  cLock(this);

	if (SetConnectionProperties(pConnection))
	{
		ClearAllMessages();
		UpdateBars();
		return TRUE;
	}
	return FALSE;
}
BOOL CTPEPWnd::Update(LPCTSTR pszData)
{
	UINT  nTag;
	BOOL  bQuality;
	CString  szTag;
	CTimeTag  tTag;
	CDisplayLock  cLock(this);

	if (IsInitialized())
	{
		if (!lstrlen(pszData))
		{
			SetUpdateInfo();
			return TRUE;
		}
		for (; IsRetrievingData() && !GetMessageCount(); )
		{
			StopRetrieveData();
			break;
		}
		if (!GetHoldFlag())
		{
			if (AddMessage(pszData) && ParseData(pszData, szTag, tTag, nTag, bQuality))
			{
				SetUpdateInfo(szTag, tTag, nTag, bQuality);
				return TRUE;
			}
			SetUpdateInfo();
		}
	}
	return FALSE;
}

BOOL CTPEPWnd::Stop()
{
	Initialize(FALSE);
	StopSchedulePrintJobs();
	StopConnection();
	return TRUE;
}

BOOL CTPEPWnd::SaveInfo(INT nPage, INT nDisplay, LPCTSTR pszTitle, CONST PDISPLAYINFO pDisplayInfo)
{
	UINT  nType;
	UINT  nMode;
	UINT  nLimit;
	UINT  nDigits;
	UINT  nStatus;
	BOOL  bConnection;
	CString  szComputer;
	LOGFONT  sFontInfo[2];
	COLORREF  nColor;
	CTimeKey  tRange[2][2];
	CTimeSpan  tPeriodical;
	CTimeSpan  tDailyRange[2];
	CUIntArray  nColumns;
	CUIntArray  nWidths;
	CUIntArray  nColors;
	CByteArray  nPrintInfo;
	CByteArray  nAlertsInfo;
	CByteArray  nConnectionInfo;
	CTPEPConnection  cConnection;
	CProfile  cProfile;

	return((CDisplayWnd::SaveInfo(nPage, nDisplay, pszTitle, pDisplayInfo) && GetLayout(nType) && GetLayoutColumns(nColumns, nWidths) && GetTitleFont(&sFontInfo[0]) && GetMessagesFont(&sFontInfo[1]) && GetConnectionProperties(szComputer, &cConnection, bConnection) && cConnection.Map(nConnectionInfo) && GetFilterMode(nMode) && GetFilterDigits(nDigits) && GetFilterColors(nColor, nColors) && GetAlerts(nAlertsInfo) && GetPrintJobs(nPrintInfo) && cProfile.SetTPEPLayoutInfo(nPage, nDisplay, nType, nColumns, nWidths, IsToolTipModeEnabled()) && cProfile.SetTPEPFontsInfo(nPage, nDisplay, &sFontInfo[0], &sFontInfo[1]) && cProfile.SetTPEPConnectionInfo(nPage, nDisplay, szComputer, nConnectionInfo, bConnection) && cProfile.SetTPEPFilterInfo(nPage, nDisplay, nMode, (GetFilterLimit(nLimit)) ? nLimit : 0, nDigits, (GetFilterStatus(nStatus)) ? nStatus : 0, (GetFilterRange(tRange[0][0], tRange[0][1])) ? tRange[0][0] : 0, (GetFilterRange(tRange[0][0], tRange[0][1])) ? tRange[0][1] : 0, (GetFilterDailyRange(tDailyRange[0], tDailyRange[1])) ? tDailyRange[0] : 0, (GetFilterDailyRange(tDailyRange[0], tDailyRange[1])) ? tDailyRange[1] : 0, (GetFilterPeriodicalRange(tRange[1][0], tPeriodical, tRange[1][1])) ? tRange[1][0] : 0, (GetFilterPeriodicalRange(tRange[1][0], tPeriodical, tRange[1][1])) ? tPeriodical : 0, (GetFilterPeriodicalRange(tRange[1][0], tPeriodical, tRange[1][1])) ? tRange[1][1] : 0, nColor, nColors) && cProfile.SetTPEPAlertsInfo(nPage, nDisplay, nAlertsInfo) && cProfile.SetTPEPPrintInfo(nPage, nDisplay, nPrintInfo)) ? TRUE : FALSE);
}

BOOL CTPEPWnd::LoadInfo(INT nPage, INT nDisplay, CString &szTitle, PDISPLAYINFO pDisplayInfo)
{
	UINT  nType;
	UINT  nMode;
	UINT  nLimit;
	UINT  nDigits;
	UINT  nStatus;
	BOOL  bToolTips;
	BOOL  bConnection;
	CString  szComputer;
	LOGFONT  sFontInfo[2];
	COLORREF  nColor;
	CTimeKey  tRange[2][2];
	CTimeSpan  tPeriodical;
	CTimeSpan  tDailyRange[2];
	CUIntArray  nColumns;
	CUIntArray  nWidths;
	CUIntArray  nColors;
	CByteArray  nPrintInfo;
	CByteArray  nAlertsInfo;
	CByteArray  nConnectionInfo;
	CTPEPConnection  cConnection;
	CProfile  cProfile;

	return((CDisplayWnd::LoadInfo(nPage, nDisplay, szTitle, pDisplayInfo) && cProfile.GetTPEPLayoutInfo(nPage, nDisplay, nType, nColumns, nWidths, bToolTips) && cProfile.GetTPEPFontsInfo(nPage, nDisplay, &sFontInfo[0], &sFontInfo[1]) && cProfile.GetTPEPConnectionInfo(nPage, nDisplay, szComputer, nConnectionInfo, bConnection) && cConnection.Unmap(nConnectionInfo) && cProfile.GetTPEPFilterInfo(nPage, nDisplay, nMode, nLimit, nDigits, nStatus, tRange[0][0], tRange[0][1], tDailyRange[0], tDailyRange[1], tRange[1][0], tPeriodical, tRange[1][1], nColor, nColors) && cProfile.GetTPEPAlertsInfo(nPage, nDisplay, nAlertsInfo) && cProfile.GetTPEPPrintInfo(nPage, nDisplay, nPrintInfo) && SetLayout(nType) && SetLayoutColumns(nColumns, nWidths) && SetTitleFont(&sFontInfo[0]) && SetMessagesFont(&sFontInfo[1]) && SetConnectionProperties(szComputer, &cConnection, bConnection) && SetFilterMode(nMode) && SetFilterLimit(nLimit) >= 0 && SetFilterStatus(nStatus) >= 0 && SetFilterRange(tRange[0][0], tRange[0][1]) >= 0 && SetFilterDailyRange(tDailyRange[0], tDailyRange[1]) >= 0 && SetFilterPeriodicalRange(tRange[1][0], tPeriodical, tRange[1][1]) >= 0 && SetFilterDigits(nDigits) && SetFilterColors(nColor, nColors) && SetAlerts(nAlertsInfo) && SetPrintJobs(nPrintInfo)) ? TRUE : FALSE);
}

BOOL CTPEPWnd::QueryDefaultInfo(PDISPLAYINFO pDefaultInfo) CONST
{
	pDefaultInfo->ptWnd.x = 0;
	pDefaultInfo->ptWnd.y = 0;
	pDefaultInfo->nNumber = -1;
	pDefaultInfo->rWnd = rectDefault;
	pDefaultInfo->nScope = DISPLAY_SCOPE_LOCAL;
	pDefaultInfo->nMode = DISPLAY_MODE_HISTORY;
	pDefaultInfo->pData = (LPVOID)NULL;
	pDefaultInfo->nShow = SW_SHOWNORMAL;
	pDefaultInfo->bShow = TRUE;
	return TRUE;
}

BOOL CTPEPWnd::QueryDefaultMenu(CLocaleMenu &cMenu, CImageList &cImages, CUIntArray &nImageIDs) CONST
{
	INT  nIndex;
	INT  nCount;
	INT  iImage;
	UINT  nButtonID;
	UINT  nButtonStyle;
	CBitmap  cBitmap;
	BITMAP  sBitmap;

	for (cImages.DeleteImageList(), nImageIDs.RemoveAll(); cBitmap.LoadBitmap(IDB_TPEPFRAMESMALLIMAGES) && cBitmap.GetBitmap(&sBitmap); )
	{
		for (nIndex = 0, nCount = (cImages.Create(sBitmap.bmHeight, sBitmap.bmHeight, ILC_COLOR32, sBitmap.bmWidth / sBitmap.bmHeight, 1) && cImages.Add(&cBitmap, RGB(0, 0, 0)) >= 0) ? m_wndToolBar.GetCount() : 0; nIndex < nCount; nIndex++)
		{
			for (m_wndToolBar.GetButtonInfo(nIndex, nButtonID, nButtonStyle, iImage); nButtonID != 0 && nButtonID != (UINT)-1; )
			{
				nImageIDs.Add(nButtonID);
				break;
			}
		}
		cBitmap.DeleteObject();
		break;
	}
	return cMenu.LoadMenu(IDR_TPEPFRAME);
}

VOID CTPEPWnd::UpdateBars()
{
	CDisplayLock  cLock(this);

	UpdateMessagePane();
	UpdateComputerPane();
	UpdateModePane();
	UpdateTypePane();
}

BOOL CTPEPWnd::Print(PRINTDLG *pPrintInfo)
{
	INT  nJob;
	INT  nJobs;
	CTPEPPrintJobs  pJobs;
	CTPEPPrintJobInfo  *pJobInfo;
	CDisplayLock  cLock(this);

	for (nJob = 0, nJobs = (GetPrintJobs(pJobs)) ? (INT)pJobs.GetSize() : 0; nJob < nJobs; nJob++)
	{
		if ((pJobInfo = pJobs.GetAt(nJob)) && pJobInfo->GetName() == STRING(IDS_PRINTJOB_DEFAULTNAME))
		{
			if (Print(pJobInfo, pPrintInfo)) break;
			continue;
		}
	}
	if (nJob < nJobs)
	{
		if (pJobInfo->GetPrintMode() & TPEP_PRINT_CLEARCOMMENTS)
		{
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~TPEP_PRINT_CLEARCOMMENTS);
			pJobInfo->SetComments(EMPTYSTRING);
			SetPrintJobs(pJobs);
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPWnd::CanPrint() CONST
{
	return((GetMessageCount() > 0) ? TRUE : FALSE);
}

BOOL CTPEPWnd::SetFilterMode(UINT nMode)
{
	return m_wndView.SetFilterMode(nMode);
}

BOOL CTPEPWnd::GetFilterMode(UINT &nMode) CONST
{
	return m_wndView.GetFilterMode(nMode);
}

BOOL CTPEPWnd::SetFilterLimit(UINT nLimit)
{
	return m_wndView.SetFilterLimit(nLimit);
}

BOOL CTPEPWnd::GetFilterLimit(UINT &nLimit) CONST
{
	return m_wndView.GetFilterLimit(nLimit);
}

BOOL CTPEPWnd::SetFilterStatus(UINT nStatus)
{
	return m_wndView.SetFilterStatus(nStatus);
}

BOOL CTPEPWnd::GetFilterStatus(UINT &nStatus) CONST
{
	return m_wndView.GetFilterStatus(nStatus);
}

BOOL CTPEPWnd::SetFilterRange(CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime)
{
	return m_wndView.SetFilterRange(tStartTime, tStopTime);
}

BOOL CTPEPWnd::GetFilterRange(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	return m_wndView.GetFilterRange(tStartTime, tStopTime);
}

BOOL CTPEPWnd::SetFilterDailyRange(CONST CTimeSpan &tStartTime, CONST CTimeSpan &tStopTime)
{
	return m_wndView.SetFilterDailyRange(tStartTime, tStopTime);
}

BOOL CTPEPWnd::GetFilterDailyRange(CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST
{
	return m_wndView.GetFilterDailyRange(tStartTime, tStopTime);
}

BOOL CTPEPWnd::SetFilterPeriodicalRange(CONST CTimeKey &tStartTime, CONST CTimeSpan &tInterval, CONST CTimeKey &tStopTime)
{
	return m_wndView.SetFilterPeriodicalRange(tStartTime, tInterval, tStopTime);
}

BOOL CTPEPWnd::GetFilterPeriodicalRange(CTimeKey &tStartTime, CTimeSpan &tInterval, CTimeKey &tStopTime) CONST
{
	return m_wndView.GetFilterPeriodicalRange(tStartTime, tInterval, tStopTime);
}

BOOL CTPEPWnd::SetFilterDigits(UINT nDigits)
{
	return m_wndView.SetFilterDigits(nDigits);
}

BOOL CTPEPWnd::GetFilterDigits(UINT &nDigits) CONST
{
	return m_wndView.GetFilterDigits(nDigits);
}

BOOL CTPEPWnd::SetFilterColors()
{
	CUIntArray  nOOLColors;

	nOOLColors.InsertAt(TPEP_OOLCOLOR_NOLIMIT, VGA_COLOR_BLACK);
	nOOLColors.InsertAt(TPEP_OOLCOLOR_SOFTLIMIT, VGA_COLOR_RED);
	nOOLColors.InsertAt(TPEP_OOLCOLOR_HARDLIMIT, VGA_COLOR_LTRED);
	nOOLColors.InsertAt(TPEP_OOLCOLOR_DELTALIMIT, VGA_COLOR_MAGENTA);
	nOOLColors.InsertAt(TPEP_OOLCOLOR_CONSISTENCYLIMIT, VGA_COLOR_YELLOW);
	return SetFilterColors(GetSysColor(COLOR_WINDOWTEXT), nOOLColors);
}
BOOL CTPEPWnd::SetFilterColors(COLORREF nColor, CONST CUIntArray &nOOLColors)
{
	return m_wndView.SetFilterColors(nColor, nOOLColors);
}

BOOL CTPEPWnd::GetFilterColors(COLORREF &nColor, CUIntArray &nOOLColors) CONST
{
	return m_wndView.GetFilterColors(nColor, nOOLColors);
}

BOOL CTPEPWnd::SetAlerts(CONST CTPEPAlerts &pAlerts)
{
	return m_wndView.SetAlerts(pAlerts);
}

BOOL CTPEPWnd::GetAlerts(CTPEPAlerts &pAlerts) CONST
{
	return m_wndView.GetAlerts(pAlerts);
}

BOOL CTPEPWnd::ProcessRealtimeData()
{
	CTPEPConnection  cConnection;

	if (GetConnectionProperties(&cConnection))
	{
		if ((cConnection.GetDataMode() == TPEP_DATAMODE_REALTIME || cConnection.GetDataMode() == TPEP_DATAMODE_RANDOM) && !cConnection.GetRetrieveStartTime().GetTime() && !cConnection.GetRetrieveStopTime().GetTime())
		{
			InterlockedExchange(&m_bRetrieveFlag, FALSE);
			UpdateAllPanes();
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CTPEPWnd::StartRetrieveData()
{
	POINT  ptCursor;
	CTPEPConnection  cConnection;

	if (GetConnectionProperties(&cConnection))
	{
		for (GetCursorPos(&ptCursor); cConnection.GetDataMode() == TPEP_DATAMODE_HISTORY && cConnection.GetRetrieveStartTime() <= cConnection.GetRetrieveStopTime() && cConnection.GetRetrieveStartTime() > 0; )
		{
			InterlockedExchange(&m_bRetrieveFlag, TRUE);
			SetCursorPos(ptCursor.x, ptCursor.y);
			UpdateAllPanes();
			SetUpdateInfo();
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CTPEPWnd::IsRetrievingData() CONST
{
	LONG  bFlag;

	InterlockedExchange(&bFlag, m_bRetrieveFlag);
	return((bFlag) ? TRUE : FALSE);
}

BOOL CTPEPWnd::StopRetrieveData()
{
	POINT  ptCursor;
	CTPEPConnection  cConnection;

	if (GetConnectionProperties(&cConnection))
	{
		for (GetCursorPos(&ptCursor); cConnection.GetDataMode() == TPEP_DATAMODE_HISTORY && cConnection.GetRetrieveStartTime() <= cConnection.GetRetrieveStopTime() && cConnection.GetRetrieveStartTime() > 0; )
		{
			InterlockedExchange(&m_bRetrieveFlag, FALSE);
			SetCursorPos(ptCursor.x, ptCursor.y);
			UpdateBars();
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CTPEPWnd::SetRetrieveMode(UINT nMode)
{
	CDisplayLock  cLock(this);

	m_nRetrieveMode = nMode;
	m_bRetrieveFlag = (nMode) ? m_bRetrieveFlag : FALSE;
	return TRUE;
}

BOOL CTPEPWnd::GetRetrieveMode(UINT &nMode) CONST
{
	nMode = m_nRetrieveMode;
	return TRUE;
}
UINT CTPEPWnd::GetRetrieveMode() CONST
{
	return m_nRetrieveMode;
}

BOOL CTPEPWnd::SetConnectionProperties(CONST CTPEPConnection *pConnection)
{
	return m_wndView.SetConnectionProperties(pConnection);
}
BOOL CTPEPWnd::SetConnectionProperties(LPCTSTR pszComputer, CONST CTPEPConnection *pConnection, BOOL bConnection)
{
	INT  nIndex;
	INT  nCount;
	INT  nColumnGroup;
	CUIntArray  nWidths;
	CUIntArray  nColumns;
	CStringArray  szParameters;
	CDisplayLock  cLock(this);

	if (HIWORD(GetType()) == TPEP_TYPE_NORMAL)
	{
		for (nIndex = 0, nCount = pConnection->GetParameters(szParameters), nCount = max(nCount, 1), GetLayoutColumns(nColumns, nWidths), nColumnGroup = 0; nIndex < nColumns.GetSize(); nIndex++)
		{
			nColumnGroup = (nColumns.GetAt(nIndex) == TPEP_TITLEITEM_ID) ? (nColumnGroup + 1) : nColumnGroup;
			continue;
		}
		for (; nColumnGroup < nCount; nColumnGroup++)
		{
			if (TPEP_TITLEITEMS_DEFAULT & TPEP_TITLEITEM_ID) nColumns.Add(TPEP_TITLEITEM_ID);
			if (TPEP_TITLEITEMS_DEFAULT & TPEP_TITLEITEM_DESCRIPTION) nColumns.Add(TPEP_TITLEITEM_DESCRIPTION);
			if (TPEP_TITLEITEMS_DEFAULT & TPEP_TITLEITEM_VALUE) nColumns.Add(TPEP_TITLEITEM_VALUE);
			if (TPEP_TITLEITEMS_DEFAULT & TPEP_TITLEITEM_UNIT) nColumns.Add(TPEP_TITLEITEM_UNIT);
			if (TPEP_TITLEITEMS_DEFAULT & TPEP_TITLEITEM_CHANGETMUNIT) nColumns.Add(TPEP_TITLEITEM_CHANGETMUNIT);
			if (TPEP_TITLEITEMS_DEFAULT & TPEP_TITLEITEM_CHANGETIME) nColumns.Add(TPEP_TITLEITEM_CHANGETIME);
			if (TPEP_TITLEITEMS_DEFAULT & TPEP_TITLEITEM_UPDATETMUNIT) nColumns.Add(TPEP_TITLEITEM_UPDATETMUNIT);
			if (TPEP_TITLEITEMS_DEFAULT & TPEP_TITLEITEM_UPDATETIME) nColumns.Add(TPEP_TITLEITEM_UPDATETIME);
		}
		for (; nColumns.GetSize() != nWidths.GetSize(); )
		{
			SetLayoutColumns(nColumns);
			break;
		}
		for (; nColumns.GetSize() == nWidths.GetSize(); )
		{
			SetLayoutColumns(nColumns, nWidths);
			break;
		}
	}
	for (; HIWORD(GetType()) == TPEP_TYPE_SIMPLE; )
	{
		SetLayoutColumns(nColumns);
		break;
	}
	return m_wndView.SetConnectionProperties(pszComputer, pConnection, bConnection);
}

BOOL CTPEPWnd::GetConnectionProperties(CTPEPConnection *pConnection) CONST
{
	return m_wndView.GetConnectionProperties(pConnection);
}
BOOL CTPEPWnd::GetConnectionProperties(CString &szComputer, CTPEPConnection *pConnection, BOOL &bConnection) CONST
{
	return m_wndView.GetConnectionProperties(szComputer, pConnection, bConnection);
}

VOID CTPEPWnd::SetParameterInfo(LPCTSTR pszTag)
{
	ReportEvent((m_dlgParameters.Create(this, pszTag) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

BOOL CTPEPWnd::SetPrintJobs(CONST CTPEPPrintJobs &pPrintJobs)
{
	return m_cPrintThread.SetPrintJobs(pPrintJobs);
}

BOOL CTPEPWnd::GetPrintJobs(CTPEPPrintJobs &pPrintJobs) CONST
{
	return m_cPrintThread.GetPrintJobs(pPrintJobs);
}

BOOL CTPEPWnd::Print(CONST CTPEPPrintJobInfo *pJobInfo, PRINTDLG *pPrintInfo)
{
	CDC  cDC;
	UINT  nMode;
	UINT  nTMUnit;
	BOOL  bMetric;
	BOOL  bQuality;
	RECT  rtMargin[2];
	SIZE  ptPaperSize;
	CString  szTMUnit;
	CTimeTag  tTMUnit;
	LOGFONT  lfFont[3];
	DEVMODE  *pDevMode;
	DEVNAMES  *pDevNames;
	CUIntArray  nOOLColors;
	CUIntArray  nItemStatus;
	CStringArray  szColumns;
	CStringArray  szContents;
	CStringArray  szItemValues;
	CPrintProfiles  cPrintProfiles;
	CTPEPConnection  cConnection;
	CPrintProfileInfo  *pPrintProfileInfo;
	CTextViewAttributes  pAttributes;

	if ((pPrintProfileInfo = (GetPrintProfiles(cPrintProfiles)) ? cPrintProfiles.GetAt(cPrintProfiles.Find(pJobInfo->GetProfile())) : (CPrintProfileInfo *)NULL) && pPrintProfileInfo->GetPaperInfo(ptPaperSize, rtMargin[0], rtMargin[1], bMetric))
	{
		if (GetConnectionProperties(&cConnection) && GetPrintProperties(pJobInfo, nMode, szTMUnit, tTMUnit, nTMUnit, bQuality, szColumns, szContents, pAttributes, szItemValues, nItemStatus, nOOLColors, &lfFont[0], &lfFont[1], &lfFont[2]))
		{
			if (!AfxIsValidAddress(pPrintInfo, sizeof(PRINTDLG)))
			{
				if (CreatePrinterDC(pPrintProfileInfo, cDC))
				{
					if (PrintJob(cDC, pJobInfo, pPrintProfileInfo->GetPrinterName(), 0, 0, rtMargin[0], bMetric, &cConnection, nMode, szTMUnit, tTMUnit, nTMUnit, bQuality, szColumns, szContents, pAttributes, szItemValues, nItemStatus, nOOLColors, &lfFont[0], &lfFont[1], &lfFont[2]))
					{
						cDC.DeleteDC();
						return TRUE;
					}
					cDC.DeleteDC();
				}
				return FALSE;
			}
			if ((pDevNames = (DEVNAMES *)GlobalLock(pPrintInfo->hDevNames)))
			{
				if ((pDevMode = (DEVMODE *)GlobalLock(pPrintInfo->hDevMode)))
				{
					if (CreatePrinterDC(pPrintInfo->hDevNames, pPrintInfo->hDevMode, cDC))
					{
						if (PrintJob(cDC, pJobInfo, (LPCTSTR)pDevMode->dmDeviceName, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nFromPage : 0, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nToPage : 0, rtMargin[0], bMetric, &cConnection, nMode, szTMUnit, tTMUnit, nTMUnit, bQuality, szColumns, szContents, pAttributes, szItemValues, nItemStatus, nOOLColors, &lfFont[0], &lfFont[1], &lfFont[2]))
						{
							GlobalUnlock(pPrintInfo->hDevNames);
							GlobalUnlock(pPrintInfo->hDevMode);
							cDC.DeleteDC();
							return TRUE;
						}
						cDC.DeleteDC();
					}
					GlobalUnlock(pPrintInfo->hDevMode);
				}
				GlobalUnlock(pPrintInfo->hDevNames);
			}
		}
	}
	return FALSE;
}

CTPEPWnd *CTPEPWnd::Find(INT nType, LPCTSTR pszComputer, CONST CTPEPConnection *pConnection, BOOL bClient) CONST
{
	INT  nDisplay;
	INT  nDisplays;
	BOOL  bConnection;
	CString  szComputer;
	CTPEPConnection  cConnection;
	CDisplayWnd  *pDisplayWnd;
	CPtrArray  pDisplays;
	CTPEPWnd  *pTPEPWnd;

	for (nDisplay = 0, nDisplays = GetDisplayArea()->EnumDisplays(pDisplays), pTPEPWnd = (CTPEPWnd *)NULL; nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_TPEP  &&  HIWORD(pDisplayWnd->GetType()) == HIWORD(nType))
		{
			if ((pTPEPWnd = (CTPEPWnd *)pDisplayWnd)->GetConnectionProperties(szComputer, &cConnection, bConnection) && szComputer == pszComputer  &&  cConnection.Compare(pConnection) && bConnection == bClient) break;
			continue;
		}
	}
	return((nDisplay < nDisplays) ? pTPEPWnd : (CTPEPWnd *)NULL);
}

VOID CTPEPWnd::SetUpdateInfo()
{
	CDisplayLock  cLock(this);

	m_szTMUnit.Empty();
	m_tTMUnit = 0;
	m_nTMUnit = 0;
	m_bTMUnit = FALSE;
	UpdateMessagePane();
}
VOID CTPEPWnd::SetUpdateInfo(LPCTSTR pszTag, CONST CTimeTag &tTag, UINT nTag, BOOL bQuality)
{
	CDisplayLock  cLock(this);

	m_szTMUnit = pszTag;
	m_tTMUnit = tTag;
	m_nTMUnit = nTag;
	m_bTMUnit = bQuality;
	UpdateMessagePane();
}

BOOL CTPEPWnd::GetUpdateInfo(CString &szTag, CTimeTag &tTag, UINT &nTag, BOOL &bQuality) CONST
{
	szTag = m_szTMUnit;
	tTag = m_tTMUnit;
	nTag = m_nTMUnit;
	bQuality = m_bTMUnit;
	return TRUE;
}

BOOL CTPEPWnd::CreateToolBar()
{
	if (m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE) && m_wndToolBar.LoadToolBar(IDB_TPEPFRAMELARGEIMAGES, 0, IDB_TPEPFRAMESMALLIMAGES, TRUE))
	{
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TPEPSETTINGS), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TPEPCONNECTION), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TPEPPARAMETERS), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TPEPALERTS), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TPEPHOLD), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TPEPCLEARALL), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_TPEPPRINT), TBBS_DISABLED);
		DockPane(&m_wndToolBar);
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPWnd::CreateStatusBar()
{
	if (m_wndStatusBar.Create(this, CBRS_BOTTOM | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE) && m_wndStatusBar.SetIndicators(nTPEPStatusBarIndicators, 1))
	{
		m_wndStatusBar.EnableToolTips();
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPWnd::CreateView()
{
	if (m_wndView.Create(this))
	{
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

CRect CTPEPWnd::RepositionView(BOOL bAdjust)
{
	CRect  rView;
	CRect  rWnd[2];
	CRect  rToolBar;
	CRect  rStatusBar;

	for (rWnd[0].SetRectEmpty(), rView.SetRectEmpty(); IsWindow(m_wndView.GetSafeHwnd()); )
	{
		rView.SetRect(0, 0, m_wndView.GetTrackSize().cx, m_wndView.GetTrackSize().cy);
		break;
	}
	for (rToolBar.SetRectEmpty(); IsWindow(m_wndToolBar.GetSafeHwnd()); )
	{
		m_wndToolBar.GetWindowRect(rToolBar);
		break;
	}
	for (rStatusBar.SetRectEmpty(); IsWindow(m_wndStatusBar.GetSafeHwnd()); )
	{
		m_wndStatusBar.GetWindowRect(rStatusBar);
		break;
	}
	if (IsWindow(GetSafeHwnd()))
	{
		for (rWnd[0].SetRect(0, 0, 2 * GetSystemMetrics(SM_CXFRAME) + rView.Width(), 2 * (GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYEDGE)) + GetSystemMetrics(SM_CYCAPTION) + rToolBar.Height() + rView.Height() + rStatusBar.Height()); bAdjust; )
		{
			for (GetWindowRect(rWnd[1]), GetParent()->ScreenToClient(rWnd[1]); rWnd[0].Height() > rWnd[1].Height(); )
			{
				MoveWindow(rWnd[1].left, rWnd[1].top, rWnd[1].Width(), rWnd[0].Height());
				break;
			}
			break;
		}
	}
	return rWnd[0];
}

BOOL CTPEPWnd::Customize(BOOL bDefault)
{
	UINT  nType;
	CString  szTitle[3];
	LOGFONT  sFontInfo[2];
	CUIntArray  nWidths;
	CUIntArray  nColumns;
	CTPEPConnection  cConnection;

	if ((nType = HIWORD(GetType())) == TPEP_TYPE_NORMAL || nType == TPEP_TYPE_SIMPLE || !nType)
	{
		if ((!bDefault  &&  GetLayoutColumns(nColumns, nWidths) && GetTitleFont(&sFontInfo[0]) && GetMessagesFont(&sFontInfo[1]) && SetLayout((!nType) ? TPEP_TYPE_SIMPLE : nType) && SetLayoutColumns(nColumns, nWidths) && SetTitleFont(&sFontInfo[0]) && SetMessagesFont(&sFontInfo[1])) || (bDefault  &&  SetLayout(TPEP_TYPE_SIMPLE)))
		{
			for (GetWindowText(szTitle[0]); GetConnectionProperties(&cConnection); )
			{
				szTitle[1].Format(STRING(IDS_WINDOW_FULLTITLE), STRING(IDS_DISPLAY_TITLE_TPEP), (cConnection.GetType() == TPEP_TYPE_PACKETS) ? STRING(IDS_TPEP_TITLE_PACKETS) : STRING(IDS_TPEP_TITLE_PARAMETERS));
				szTitle[2].Format(STRING(IDS_WINDOW_FULLTITLE), STRING(IDS_DISPLAY_TITLE_TPEP), EMPTYSTRING);
				SetWindowText((szTitle[0].Left(szTitle[2].GetLength()) == szTitle[2]) ? szTitle[0] : szTitle[1]);
				break;
			}
			return((!bDefault || Start()) ? TRUE : FALSE);
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CTPEPWnd::UpdateAllPanes()
{
	INT  nPane;
	INT  nPanes;

	for (nPane = 0, nPanes = sizeof(nTPEPStatusBarIndicators) / sizeof(UINT); nPane < nPanes; nPane++)
	{
		if (m_wndStatusBar.CommandToIndex(nTPEPStatusBarIndicators[nPane]) != nPane) break;
		continue;
	}
	if (nPane < nPanes)
	{
		if (m_wndStatusBar.SetIndicators(nTPEPStatusBarIndicators, sizeof(nTPEPStatusBarIndicators) / sizeof(UINT)))
		{
			UpdateBars();
			return TRUE;
		}
		return FALSE;
	}
	UpdateBars();
	return TRUE;
}

VOID CTPEPWnd::UpdateMessagePane()
{
	UINT  nTag;
	INT  nMessages;
	BOOL  bQuality;
	CTimeTag  tTag;
	CString  szTag;
	CString  szMessage;

	if (GetUpdateInfo(szTag, tTag, nTag, bQuality))
	{
		if (!szTag.IsEmpty() && tTag.GetTime() > 0)
		{
			szMessage.Format(STRING(IDS_TPEP_STATUSBAR_UPDATEMESSAGE), (LPCTSTR)tTag.FormatGmt(), (LPCTSTR)szTag, nTag, (bQuality) ? STRING(IDS_TPEP_STATUSBAR_QUALITYGOOD) : STRING(IDS_TPEP_STATUSBAR_QUALITYBAD));
			m_wndStatusBar.SetPaneText(ID_TPEP_STATUSBAR_MESSAGEPANE, szMessage);
			return;
		}
		szMessage.Format(((nMessages = m_wndView.GetMessageCount()) > 0 || !IsRetrievingData()) ? ((nMessages > 1) ? STRING(IDS_TPEP_STATUSBAR_MESSAGES) : ((nMessages == 1) ? STRING(IDS_TPEP_STATUSBAR_MESSAGE) : STRING(IDS_TPEP_STATUSBAR_NODATAMESSAGE))) : STRING(IDS_TPEP_STATUSBAR_RETRIEVEMESSAGE), nMessages);
		m_wndStatusBar.SetPaneText(ID_TPEP_STATUSBAR_MESSAGEPANE, szMessage);
	}
	m_wndToolBar.EnableButton(IDM_TPEPCLEARALL, (IsInitialized() && GetMessageCount() > 0) ? TRUE : FALSE);
}

VOID CTPEPWnd::UpdateComputerPane()
{
	CString  szComputer;
	CTPEPConnection  cConnection;
	BOOL  bConnection;

	if (GetConnectionProperties(szComputer, &cConnection, bConnection))
	{
		m_wndStatusBar.SetPaneText(ID_TPEP_STATUSBAR_COMPUTERPANE, szComputer);
		return;
	}
}

VOID CTPEPWnd::UpdateModePane()
{
	CString  szMode;
	CTPEPConnection  cConnection;

	if (GetConnectionProperties(&cConnection))
	{
		szMode.Format((cConnection.GetDataMode() == TPEP_DATAMODE_REALTIME) ? STRING(IDS_DISPLAY_MODE_REALTIME) : ((cConnection.GetDataMode() == TPEP_DATAMODE_HISTORY) ? STRING(IDS_DISPLAY_MODE_HISTORY) : ((cConnection.GetDataMode() == TPEP_DATAMODE_RANDOM) ? STRING(IDS_DISPLAY_MODE_RANDOM) : EMPTYSTRING)));
		m_wndStatusBar.SetPaneText(ID_TPEP_STATUSBAR_MODEPANE, szMode);
	}
}

VOID CTPEPWnd::UpdateTypePane()
{
	CString  szType;
	CTPEPConnection  cConnection;

	if (GetConnectionProperties(&cConnection))
	{
		szType.Format((HIWORD(GetType()) == TPEP_TYPE_NORMAL) ? STRING(IDS_TPEP_STATUSBAR_TYPENORMAL) : STRING(IDS_TPEP_STATUSBAR_TYPESIMPLE), (cConnection.GetType() == TPEP_TYPE_PACKETS) ? STRING(IDS_TPEP_STATUSBAR_CONTENTSPACKETS) : STRING(IDS_TPEP_STATUSBAR_CONTENTSPARAMETERS));
		m_wndStatusBar.SetPaneText(ID_TPEP_STATUSBAR_TYPEPANE, szType);
	}
}

BOOL CTPEPWnd::ParseData(LPCTSTR pszData, CString &szTag, CTimeTag &tTag, UINT &nTag, BOOL &bQuality) CONST
{
	INT  nPos[2];
	CString  szData;
	CString  szQuality;

	for (szTag.Empty(), tTag = 0, nTag = (UINT)-1, bQuality = FALSE; (nPos[0] = (szData = pszData).Find(STRING(IDS_TPEP_DATA_DELIMITER))) >= 0; )
	{
		for (szQuality.Format(STRING(IDS_TPEP_ERROR_NONE), LOWORD(TPEP_ERROR_NONE)), bQuality = (szData.Mid(nPos[0], szQuality.GetLength()) == szQuality) ? TRUE : FALSE; (nPos[1] = szData.Mid((nPos[0] = nPos[0] + 1)).Find(STRING(IDS_TPEP_DATA_DELIMITER))) >= 0; )
		{
			for (nPos[0] = ((nPos[1] = szData.Mid((nPos[0] = nPos[0] + nPos[1] + 1)).Find(STRING(IDS_TPEP_DATA_DELIMITER) + CString(SPACE))) >= 0) ? (nPos[0] + nPos[1] + lstrlen(STRING(IDS_TPEP_DATA_DELIMITER) + CString(SPACE))) : szData.GetLength(); nPos[0] < szData.GetLength(); nPos[0]++)
			{
				if (szData.GetAt(nPos[0]) != SPACE[0])
				{
					szTag += szData.GetAt(nPos[0]);
					continue;
				}
				if ((tTag = (GetDatabase()->GetTMPackets()->Find(szTag) >= 0) ? tTag.ParseGmt(szData.Mid(nPos[0] + 1), GetTPEPServiceSupport()->GetTPEPTimeKeyFormat()) : 0) > 0)
				{
					if ((nPos[0] = nPos[0] + tTag.FormatGmt(GetTPEPServiceSupport()->GetTPEPTimeKeyFormat()).GetLength() + 1) < szData.GetLength() && szData.GetAt(nPos[0]) == SPACE[0])
					{
						nTag = _ttoi(szData.Mid(nPos[0]));
						return TRUE;
					}
				}
				break;
			}
			szTag.Empty();
			break;
		}
		bQuality = FALSE;
		break;
	}
	return FALSE;
}

VOID CTPEPWnd::SetHoldFlag(BOOL bEnable)
{
	m_bUpdate = !bEnable;
}

BOOL CTPEPWnd::GetHoldFlag() CONST
{
	return !m_bUpdate;
}

BOOL CTPEPWnd::HasHoldFlag() CONST
{
	return TRUE;
}

BOOL CTPEPWnd::StartConnection()
{
	return((SetTimer(0, 0, NULL) > 0) ? TRUE : FALSE);
}

BOOL CTPEPWnd::ProcessConnection()
{
	CString  szComputer;
	CTPEPConnection  cConnection;
	BOOL  bConnection;

	if (GetConnectionProperties(szComputer, &cConnection, bConnection))
	{
		if ((bConnection  &&  GetTPEPService()->AttachClientConnection(szComputer, &cConnection, this)) || (!bConnection  &&  GetTPEPService()->AttachServerConnection(szComputer, &cConnection, this)))
		{
			InterlockedExchange(&m_bRetrieveFlag, FALSE);
			UpdateAllPanes();
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CTPEPWnd::StopConnection()
{
	CString  szComputer;
	CTPEPConnection  cConnection;
	BOOL  bConnection;

	return((GetConnectionProperties(szComputer, &cConnection, bConnection)) ? (((bConnection  &&  GetTPEPService()->DetachClientConnection(szComputer, &cConnection, this)) || (!bConnection  &&  GetTPEPService()->DetachServerConnection(szComputer, &cConnection, this))) ? TRUE : FALSE) : FALSE);
}

BOOL CTPEPWnd::StartSchedulePrintJobs()
{
	return IsSchedulingPrintJobs() || m_cPrintThread.Start(this);
}

BOOL CTPEPWnd::IsSchedulingPrintJobs() CONST
{
	return((m_cPrintThread.IsThreadActive()) ? TRUE : FALSE);
}

BOOL CTPEPWnd::StopSchedulePrintJobs()
{
	return((IsSchedulingPrintJobs() && m_cPrintThread.Stop()) ? TRUE : FALSE);
}

BOOL CTPEPWnd::SetAlerts(CONST CByteArray &nAlertsInfo)
{
	CTPEPAlerts  pAlerts;

	return((pAlerts.Unmap(nAlertsInfo)) ? SetAlerts(pAlerts) : FALSE);
}

BOOL CTPEPWnd::GetAlerts(CByteArray &nAlertsInfo) CONST
{
	CTPEPAlerts  pAlerts;

	return((GetAlerts(pAlerts)) ? pAlerts.Map(nAlertsInfo) : FALSE);
}

BOOL CTPEPWnd::SetPrintJobs(CONST CByteArray &nPrintInfo)
{
	CTPEPPrintJobs  pPrintJobs;

	return((pPrintJobs.Unmap(nPrintInfo)) ? SetPrintJobs(pPrintJobs) : FALSE);
}

BOOL CTPEPWnd::GetPrintJobs(CByteArray &nPrintInfo) CONST
{
	CTPEPPrintJobs  pPrintJobs;

	return((GetPrintJobs(pPrintJobs)) ? pPrintJobs.Map(nPrintInfo) : FALSE);
}

BOOL CTPEPWnd::GetPrintProperties(CONST CTPEPPrintJobInfo *pJobInfo, UINT &nMode, CString &szTMUnit, CTimeTag &tTMUnit, UINT &nTMUnit, BOOL &bQuality, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, CStringArray &szParameterValues, CUIntArray &nParameterStatus, CUIntArray &nOOLColors, LOGFONT *pTitleFont, LOGFONT *pMessagesFont, LOGFONT *pValuesFont) CONST
{
	INT  nIndex;
	INT  nCount[2];
	UINT  nPrintMode;
	UINT  nPrintCount;
	CTextViewAttribute  *pAttribute;
	CDisplayLock  cLock(this);

	if (((nMode = GetMode()) == DISPLAY_MODE_REALTIME || nMode == DISPLAY_MODE_HISTORY) && GetUpdateInfo(szTMUnit, tTMUnit, nTMUnit, bQuality) && m_wndView.GetPrintProperties(szColumns, szContents, pAttributes, szParameterValues, nParameterStatus, nOOLColors, pTitleFont, pMessagesFont, pValuesFont))
	{
		if ((nPrintMode = (pJobInfo->GetPrintBySide(nPrintCount)) ? pJobInfo->GetPrintMode() : 0) & TPEP_PRINT_FIRSTSIDE)
		{
			for (nIndex = ((nCount[0] = (INT)(szContents.GetSize() - nPrintCount)) > 0) ? nPrintCount : 0, szContents.RemoveAt((nCount[0] > 0) ? nPrintCount : 0, max(nCount[0], 0)), nCount[1] = 0; nCount[1] < nCount[0]; nCount[1]++)
			{
				if ((pAttribute = pAttributes.GetAt(nIndex))) delete pAttribute;
				pAttributes.RemoveAt(nIndex);
			}
		}
		if (nPrintMode & TPEP_PRINT_LASTSIDE)
		{
			for (nIndex = 0, nCount[1] = 0, nCount[0] = (INT)(szContents.GetSize() - nPrintCount), szContents.RemoveAt(0, max(nCount[0], 0)); nCount[1] < nCount[0]; nCount[1]++)
			{
				if ((pAttribute = pAttributes.GetAt(nIndex))) delete pAttribute;
				pAttributes.RemoveAt(nIndex);
			}
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPWnd::StartPrintJob(CDC &cDC)
{
	DOCINFO  sJobInfo;
	CString  szJobTitle;
	CTPEPConnection  cConnection;

	for (GetConnectionProperties(&cConnection), sJobInfo.fwType = 0, sJobInfo.cbSize = sizeof(DOCINFO), sJobInfo.lpszDocName = (LPTSTR)EMPTYSTRING, sJobInfo.lpszOutput = (LPCTSTR)NULL, sJobInfo.lpszDatatype = (LPCTSTR)NULL, szJobTitle.Format(STRING(IDS_PRINTJOB_DEFAULTTITLE), (LPCTSTR)GetAppTitle(), (LPCTSTR)GetAccountSpacecraftName(), (LPCTSTR)GetPrintDocSubTitle(&cConnection), STRING(IDS_DISPLAY_TITLE_TPEP)); szJobTitle.GetLength() >= 0; )
	{
		sJobInfo.lpszDocName = (LPTSTR)(LPCTSTR)szJobTitle;
		break;
	}
	return((cDC.StartDoc(&sJobInfo) >= 0) ? TRUE : FALSE);
}

BOOL CTPEPWnd::PrintJob(CDC &cDC, CONST CTPEPPrintJobInfo *pJobInfo, LPCTSTR pszPrinterName, INT nFromPage, INT nToPage, CONST RECT &rtMargin, BOOL bMetric, CONST CTPEPConnection *pConnection, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality, CONST CStringArray &szColumns, CONST CStringArray &szContents, CONST CTextViewAttributes &pAttributes, CONST CStringArray &szParameterValues, CONST CUIntArray &nParameterStatus, CONST CUIntArray &nOOLColors, CONST LOGFONT *pTitleFont, CONST LOGFONT *pMessagesFont, CONST LOGFONT *pValuesFont)
{
	INT  x;
	INT  y;
	INT  nPage;
	INT  nPages;
	INT  nLine;
	INT  nLines;
	INT  nIndex;
	INT  nBkMode;
	INT  nColumn;
	INT  nColumns;
	INT  nSpacing;
	INT  nHeight[2];
	BOOL  bOverlap;
	BOOL  bOutput;
	UINT  nStatus;
	CPen  cLinePen;
	CPen  *pOldPen;
	CRgn  rgnArea;
	CRect  rArea;
	CRect  rCalc;
	CRect  rClip;
	CRect  rItem;
	CFont  *pOldFont;
	CFont  cFont[TPEP_PRINTFONTS];
	CSize  sizeText[2];
	CString  szColumn;
	CString  szText;
	COLORREF  nColor;
	COLORREF  nOldColor;
	CTimeKey  tPrint;
	CPtrArray  pFonts;
	CUIntArray  nTabs;
	TEXTMETRIC  tmFont;
	CStringArray  szColumnsText;
	CStringArray  szContentText;
	CTextViewAttribute  *pAttribute;

	for (nPage = nPages = 0; (!nPages || nPage <= nPages) && (nPages > 0 || (nPages = (CalcPrintDocRect(cDC, rtMargin, bMetric) && cDC.GetClipBox(rArea) != ERROR && rgnArea.CreateRectRgnIndirect(rArea) && CalcPrintDocTitleFont(cDC, rArea, cFont[TPEP_PRINTFONT_TITLE]) && CalcPrintDocSubTitleFont(cDC, rArea, cFont[TPEP_PRINTFONT_SUBTITLE]) && CalcPrintDocOperatingDetailsFont(cDC, rArea, cFont[TPEP_PRINTFONT_OPERATINGDETAILS]) && CalcPrintDocOperatingModeFont(cDC, rArea, cFont[TPEP_PRINTFONT_OPERATINGMODE]) && CalcPrintDocMessagesFonts(cDC, rArea, szColumns, szContents, pTitleFont, pMessagesFont, pValuesFont, cFont[TPEP_PRINTFONT_MESSAGESTITLE], cFont[TPEP_PRINTFONT_MESSAGESTEXT], cFont[TPEP_PRINTFONT_MESSAGESVALUES]) && CalcPrintDocNoticeFonts(cDC, rArea, cFont[TPEP_PRINTFONT_NOTICE], cFont[TPEP_PRINTFONT_LOGO]) && CalcPrintDocFooterFont(cDC, rArea, cFont[TPEP_PRINTFONT_FOOTER]) && CalcPrintDocTitleWidth(cDC, szColumns, szContents, &cFont[TPEP_PRINTFONT_MESSAGESTITLE], &cFont[TPEP_PRINTFONT_MESSAGESTEXT], &cFont[TPEP_PRINTFONT_MESSAGESVALUES], nTabs) == szColumns.GetSize()) ? nPages : -1) == 0); )
	{
		for (nLine = 0, nLines = (INT)szContents.GetSize(), szContentText.Copy(szContents), nIndex = 0, nSpacing = 0, rCalc.SetRectEmpty(), rClip.SetRectEmpty(), bOverlap = FALSE, bOutput = TRUE; nPages >= 0 && nLine < nLines; nLine++, bOutput = TRUE)
		{
			for (nColumn = 0, nColumns = (INT)szColumns.GetSize(), ExtractPrintDocText(szContentText.GetAt(nLine), szColumnsText), nHeight[0] = nHeight[1] = 0; nPages >= 0 && nColumn < nColumns; nColumn++, nHeight[1] = 0)
			{
				for (; szColumns.GetAt(nColumn) == STRING(IDS_TPEP_TITLEITEM_ID); )
				{
					nIndex = (nLine > 0 || nColumn > 0) ? (nIndex + 1) : nIndex;
					break;
				}
				if (szColumns.GetAt(nColumn) == STRING(IDS_TPEP_TITLEITEM_MESSAGES))
				{
					if (CalcPrintDocText(cDC, &cFont[TPEP_PRINTFONT_MESSAGESTEXT], szColumnsText.GetAt(nColumn), rArea.Width(), szText) < szColumnsText.GetAt(nColumn).GetLength())
					{
						szContentText.SetAt(nLine, szContentText.GetAt(nLine).Mid(szText.GetLength()));
						szColumnsText.SetAt(nColumn, szText);
						nLine--;
					}
				}
				for (; pFonts.GetSize() < TPEP_PRINTFONTS; )
				{
					pFonts.Add(&cFont[pFonts.GetSize()]);
					continue;
				}
				if (rClip.Height() > 0)
				{
					if ((pOldFont = cDC.SelectObject((CFont *)pFonts.GetAt((szColumns.GetAt(nColumn) != STRING(IDS_TPEP_TITLEITEM_VALUE)) ? TPEP_PRINTFONT_MESSAGESTEXT : TPEP_PRINTFONT_MESSAGESVALUES))))
					{
						if ((nSpacing = (cDC.GetTextMetrics(&tmFont)) ? max(tmFont.tmHeight / 16, 1) : -1) >= 0)
						{
							nColor = (!(pAttribute = pAttributes.GetAt(nLine)) || !pAttribute->GetColumnColor(nColumn, nColor)) ? cDC.GetTextColor() : nColor;
							nOldColor = cDC.SetTextColor((cDC.GetDeviceCaps(NUMCOLORS) > 2) ? nColor : cDC.GetTextColor());
							sizeText[0] = (nColumn < szColumnsText.GetSize()) ? cDC.GetTextExtent((szColumn = szColumnsText.GetAt(nColumn) + SPACE)) : cDC.GetTextExtent((szColumn = EMPTYSTRING) + SPACE);
							sizeText[1] = (nColumn < szColumnsText.GetSize()) ? cDC.GetTextExtent(szColumnsText.GetAt(nColumn)) : cDC.GetTextExtent(EMPTYSTRING);
							rCalc.SetRect(rCalc.left, (!nColumn) ? (rCalc.top + nSpacing) : rCalc.top, rCalc.right, (!nColumn) ? (rCalc.top + nSpacing + tmFont.tmHeight*((rClip.bottom - (rCalc.top + nSpacing)) / tmFont.tmHeight)) : (rCalc.top + tmFont.tmHeight*((rClip.bottom - rCalc.top) / tmFont.tmHeight)));
							rItem.SetRect((nColumn > 0) ? (rCalc.left + nTabs.GetAt(nColumn - 1)) : rCalc.left, rCalc.top, rCalc.left + nTabs.GetAt(nColumn), rCalc.top + sizeText[0].cy);
							if (nPages > 0 && (nFromPage <= 0 || nToPage <= 0 || nFromPage > nToPage || (nPage >= nFromPage  &&  nPage <= nToPage)))
							{
								cDC.DrawText(szColumn, CRect(rItem.left, rItem.top, rItem.right, rCalc.bottom), DT_LEFT | DT_NOPREFIX | DT_SINGLELINE);
								if (szColumns.GetAt(nColumn) == STRING(IDS_TPEP_TITLEITEM_VALUE) && (pJobInfo->GetPrintMode() & TPEP_PRINT_UNDERLINEOOL))
								{
									if (((nStatus = (nIndex < nParameterStatus.GetSize()) ? nParameterStatus.GetAt(nIndex) : TMPARAMETER_STATUS_NONE) & TMPARAMETER_STATUS_SOFTLIMIT) || (nStatus & TMPARAMETER_STATUS_HARDLIMIT) || (nStatus & TMPARAMETER_STATUS_DELTALIMIT) || (nStatus & TMPARAMETER_STATUS_CONSISTENCYLIMIT))
									{
										if (cLinePen.CreatePen(PS_SOLID, tmFont.tmDescent / 3, cDC.GetTextColor()))
										{
											if ((pOldPen = cDC.SelectObject(&cLinePen)))
											{
												nBkMode = cDC.SetBkMode(TRANSPARENT);
												cDC.MoveTo((x = rItem.left), (y = rItem.bottom - max((2 * tmFont.tmDescent) / 3, 1)));
												cDC.LineTo(x + sizeText[1].cx, y);
												cDC.SelectObject(pOldPen);
												cDC.SetBkMode(nBkMode);
											}
											cLinePen.DeleteObject();
										}
									}
								}
							}
							nHeight[0] = ((nHeight[1] = rItem.Height()) > nHeight[0]) ? nHeight[1] : nHeight[0];
							cDC.SetTextColor(nOldColor);
							cDC.SelectObject(pOldFont);
						}
						else
						{
							cDC.SelectObject(pOldFont);
							break;
						}
					}
					else break;
				}
				if (((rCalc.top + nHeight[1] > rCalc.bottom || bOverlap) && nColumn == nColumns - 1) || !rClip.Height())
				{
					if (nPages > 0 && (nPage == nPages || (nFromPage > 0 && nToPage > 0 && nFromPage <= nToPage  &&  nPage == nToPage)))
					{
						nColumns = nColumn;
						nLines = nLine;
						nPages = nPage;
						break;
					}
					if (bOutput && (!nPages || ((!nPage || (nFromPage > 0 && nToPage > 0 && nFromPage <= nToPage && (nPage < nFromPage || nPage > nToPage)) || cDC.EndPage() >= 0) && ((nFromPage > 0 && nToPage > 0 && nFromPage <= nToPage && (nPage < nFromPage - 1 || nPage >= nToPage)) || (((((nFromPage <= 0 || nToPage <= 0 || nFromPage > nToPage) && nPage > 0) || (nFromPage > 0 && nToPage > 0 && nFromPage <= nToPage  &&  nPage != nFromPage - 1)) || StartPrintJob(cDC)) && cDC.StartPage() >= 0)))))
					{
						if (cDC.SelectClipRgn(&rgnArea) != ERROR  &&  DrawPrintDocPage(cDC, pJobInfo, tPrint, pszPrinterName, rtMargin, bMetric, pConnection, nMode, pszTMUnit, tTMUnit, nTMUnit, bQuality, szColumns, nOOLColors, pFonts, nTabs, nPages, (nPages > 0 && (nFromPage <= 0 || nToPage <= 0 || nFromPage > nToPage || (nPage >= nFromPage - 1 && nPage < nToPage))) ? (nPage + 1) : 0, rClip) && cDC.IntersectClipRect(rClip) != ERROR)
						{
							rCalc.SetRect(rClip.left, rClip.top - rCalc.Height() - nSpacing, rClip.right, rClip.bottom);
							bOverlap = FALSE;
							bOutput = FALSE;
							nColumn = -1;
							nPage++;
							continue;
						}
					}
					break;
				}
				bOverlap = (rCalc.top + nHeight[1] > rCalc.bottom) ? TRUE : bOverlap;
			}
			if (nLine < nLines  &&  nColumn == nColumns)
			{
				rCalc.DeflateRect(0, nHeight[0], 0, 0);
				continue;
			}
			break;
		}
		if (nPages >= 0)
		{
			if (nLine == nLines)
			{
				if (!szContents.GetSize())
				{
					if (nFromPage > 0 && nToPage > 0 && nFromPage <= nToPage  &&  nFromPage > 1)
					{
						nPages = nPage = 0;
						break;
					}
					if (StartPrintJob(cDC))
					{
						if (cDC.StartPage() >= 0)
						{
							if (DrawPrintDocPage(cDC, pJobInfo, tPrint, pszPrinterName, rtMargin, bMetric, pConnection, nMode, pszTMUnit, tTMUnit, nTMUnit, bQuality, szColumns, nOOLColors, pFonts, nTabs, 1, 1, rClip))
							{
								nPages = nPage = 1;
								break;
							}
							cDC.EndPage();
						}
						EndPrintJob(cDC);
					}
					nPages = -1;
					break;
				}
				if (!nPages)
				{
					if (nFromPage <= 0 || nToPage <= 0 || nFromPage > nToPage || nPage >= nFromPage)
					{
						nPages = nPage;
						nPage = 0;
						continue;
					}
					nPages = nPage = 0;
				}
			}
			else
			{
				if (nPages > 0) cDC.AbortDoc();
				nPages = -1;
			}
		}
		break;
	}
	return(((!nPages || (nPages > 0 && ((nFromPage > 0 && nToPage > 0 && nFromPage <= nToPage  &&  nPage < nFromPage) || (cDC.EndPage() >= 0 && EndPrintJob(cDC))))) && nPage == nPages) ? TRUE : FALSE);
}

BOOL CTPEPWnd::EndPrintJob(CDC &cDC)
{
	return((cDC.EndDoc() >= 0) ? TRUE : FALSE);
}

BOOL CTPEPWnd::DrawPrintDocPage(CDC &cDC, CONST CTPEPPrintJobInfo *pJobInfo, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, CONST RECT &rtMargin, BOOL bMetric, CONST CTPEPConnection *pConnection, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality, CONST CStringArray &szColumns, CONST CUIntArray &nOOLColors, CONST CPtrArray &pFonts, CONST CUIntArray &nTabs, INT nPages, INT nPage, LPRECT prClip)
{
	return((CalcPrintDocRect(cDC, rtMargin, bMetric) && cDC.GetClipBox(prClip) != ERROR  &&  DrawPrintDocTitle(cDC, prClip, GetPrintDocTitle(), (CFont *)pFonts.GetAt(TPEP_PRINTFONT_TITLE), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocSubTitle(cDC, prClip, GetPrintDocSubTitle(pConnection), (CFont *)pFonts.GetAt(TPEP_PRINTFONT_SUBTITLE), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocOperatingDetails(cDC, prClip, GetPrintDocOperatingDetails(pJobInfo, nMode, pszTMUnit, tTMUnit, nTMUnit, bQuality), (CFont *)pFonts.GetAt(TPEP_PRINTFONT_OPERATINGDETAILS), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocOperatingMode(cDC, prClip, GetPrintDocOperatingMode(pJobInfo, nOOLColors), nOOLColors, (CFont *)pFonts.GetAt(TPEP_PRINTFONT_OPERATINGMODE), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocMessagesTitle(cDC, prClip, szColumns, (CFont *)pFonts.GetAt(TPEP_PRINTFONT_MESSAGESTITLE), nTabs, (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocNotice(cDC, prClip, GetPrintDocNotice(), (CFont *)pFonts.GetAt(TPEP_PRINTFONT_NOTICE), (CFont *)pFonts.GetAt(TPEP_PRINTFONT_LOGO), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocFooter(cDC, prClip, GetPrintDocFooter(tTime, pszPrinterName, nPages, nPage), (CFont *)pFonts.GetAt(TPEP_PRINTFONT_FOOTER), (nPage <= 0) ? TRUE : FALSE)) ? TRUE : FALSE);
}

BOOL CTPEPWnd::DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc)
{
	CRect  rCalc;
	CFont  *pOldFont;

	if ((pOldFont = cDC.SelectObject(pFont)))
	{
		cDC.DrawText(pszTitle, (rCalc = CRect(0, 0, prClip->right - prClip->left, 0)), DT_CALCRECT | DT_CENTER | DT_NOPREFIX | DT_SINGLELINE);
		cDC.DrawText(pszTitle, (!bCalc) ? prClip : CRect(0, 0, 0, 0), DT_CENTER | DT_NOPREFIX | DT_SINGLELINE);
		prClip->top += rCalc.Height();
		cDC.SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPWnd::DrawPrintDocSubTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc)
{
	CRect  rCalc;
	CFont  *pOldFont;

	if ((pOldFont = cDC.SelectObject(pFont)))
	{
		cDC.DrawText(pszTitle, (rCalc = CRect(0, 0, prClip->right - prClip->left, 0)), DT_CALCRECT | DT_CENTER | DT_NOPREFIX | DT_SINGLELINE);
		cDC.DrawText(pszTitle, (!bCalc) ? prClip : CRect(0, 0, 0, 0), DT_CENTER | DT_NOPREFIX | DT_SINGLELINE);
		prClip->top += rCalc.Height();
		cDC.SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPWnd::DrawPrintDocOperatingDetails(CDC &cDC, LPRECT prClip, LPCTSTR pszComments, CFont *pFont, BOOL bCalc)
{
	CRect  rCalc;
	CFont  *pOldFont;

	if ((pOldFont = cDC.SelectObject(pFont)))
	{
		cDC.DrawText(pszComments, (rCalc = CRect(0, 0, prClip->right - prClip->left, 0)), DT_CALCRECT | DT_CENTER | DT_NOPREFIX | DT_WORDBREAK);
		cDC.DrawText(pszComments, (!bCalc) ? prClip : CRect(0, 0, 0, 0), DT_CENTER | DT_NOPREFIX | DT_WORDBREAK);
		prClip->top += rCalc.Height();
		cDC.SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPWnd::DrawPrintDocOperatingMode(CDC &cDC, LPRECT prClip, LPCTSTR pszMode, CONST CUIntArray &nOOLColors, CFont *pFont, BOOL bCalc)
{
	INT  X;
	INT  Y;
	INT  nPos;
	INT  nPart;
	INT  nParts;
	INT  nHeight;
	CRect  rCalc;
	CFont  *pOldFont;
	CString  szMode;
	CString  szToken;
	CString  szLegend[2];
	CString  szLegendPart;
	CStringArray  szLegendParts;
	COLORREF  nOldColor;

	if ((pOldFont = cDC.SelectObject(pFont)))
	{
		szToken = szToken.Left((szToken = STRING(IDS_TPEP_PRINTDOCUMENT_OOLLEGEND)).Find(SPACE));
		szLegend[0] = ((nPos = (szMode = pszMode).Find(szToken)) >= 0) ? (LPCTSTR)szMode.Mid(nPos) : EMPTYSTRING;
		cDC.DrawText((szMode = (nPos >= 0) ? szMode.Left(nPos) : szMode), (rCalc = CRect(0, 0, prClip->right - prClip->left, 0)), DT_CALCRECT | DT_CENTER | DT_NOPREFIX | DT_WORDBREAK);
		cDC.DrawText(szMode, (!bCalc) ? prClip : CRect(0, 0, 0, 0), DT_CENTER | DT_NOPREFIX | DT_WORDBREAK);
		for (szLegend[1] = szLegend[0]; (nPos = szLegend[1].Find(SPACE + szToken)) >= 0; )
		{
			for (szLegendPart = SPACE + szToken; --nPos >= 0; )
			{
				if (szLegend[1][nPos] != SPACE[0])
				{
					szLegendPart = szLegend[1][nPos] + szLegendPart;
					continue;
				}
				break;
			}
			if (nPos >= 0)
			{
				szLegendParts.Add(szLegend[1].Left((nPos = nPos + lstrlen(SPACE))));
				szLegendParts.Add(szLegendPart);
				szLegend[1] = szLegend[1].Mid(nPos + szLegendPart.GetLength());
				continue;
			}
			szLegend[0].Empty();
			szLegend[1].Empty();
			szLegendParts.RemoveAll();
			break;
		}
		szLegendParts.Add(szLegend[1]);
		for (nPart = 0, nParts = (INT)szLegendParts.GetSize(), X = prClip->left + (prClip->right - prClip->left - cDC.GetTextExtent(szLegend[0]).cx) / 2, Y = prClip->top + rCalc.Height(), nHeight = 0; nPart < nParts; nPart++, X += cDC.GetTextExtent(szLegendParts.GetAt(nPart - 1)).cx)
		{
			if (cDC.GetDeviceCaps(NUMCOLORS) > 2 && nPart % 2 && nPart / 2 < nOOLColors.GetSize())
			{
				nOldColor = cDC.SetTextColor(nOOLColors.GetAt(nPart / 2));
				nHeight = cDC.DrawText(szLegendParts.GetAt(nPart), CRect(X, Y, prClip->right, prClip->bottom), DT_LEFT | DT_NOPREFIX | DT_WORDBREAK);
				cDC.SetTextColor(nOldColor);
				continue;
			}
			nHeight = cDC.DrawText(szLegendParts.GetAt(nPart), CRect(X, Y, prClip->right, prClip->bottom), DT_LEFT | DT_NOPREFIX | DT_WORDBREAK);
		}
		prClip->top += rCalc.Height() + nHeight;
		cDC.SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPWnd::DrawPrintDocMessagesTitle(CDC &cDC, LPRECT prClip, CONST CStringArray &szColumns, CFont *pFont, CONST CUIntArray &nTabs, BOOL bCalc)
{
	CSize  rCalc;
	CFont  *pOldFont;
	CString  szItems;

	if ((pOldFont = cDC.SelectObject(pFont)))
	{
		szItems = GetPrintDocMessagesTitle(szColumns);
		rCalc = (!bCalc) ? cDC.TabbedTextOut(prClip->left, prClip->top + cDC.GetTextExtent(szItems, szItems.GetLength()).cy, szItems, (INT)nTabs.GetSize(), (LPINT)nTabs.GetData(), prClip->left) : CSize(nTabs.GetAt(nTabs.GetSize() - 1), cDC.GetTextExtent(szItems, szItems.GetLength()).cy);
		prClip->top += 2 * rCalc.cy;
		cDC.SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPWnd::DrawPrintDocNotice(CDC &cDC, LPRECT prClip, LPCTSTR pszNotice, CFont *pFont, CFont *pLogoFont, BOOL bCalc)
{
	INT  nPos;
	CFont  *pOldFont;
	CSize  sizeNotice[3];
	CString  szNotice[3];
	CString  szCopyrightNotice;
	CVersionInfo  cVersionInfo;

	for (szCopyrightNotice = pszNotice, sizeNotice[0].cx = sizeNotice[0].cy = 0, sizeNotice[1].cx = sizeNotice[1].cy = 0; (pOldFont = cDC.SelectObject(pFont)); )
	{
		szNotice[0] = ((nPos = szCopyrightNotice.Find((szNotice[2] = cVersionInfo.QueryCompanyName()))) >= 0) ? szCopyrightNotice.Left(nPos) : szCopyrightNotice;
		szNotice[1] = (nPos >= 0) ? szCopyrightNotice.Mid(nPos + szNotice[2].GetLength()) : EMPTYSTRING;
		sizeNotice[0] = cDC.GetTextExtent(szNotice[0]);
		sizeNotice[1] = cDC.GetTextExtent(szNotice[1]);
		cDC.SelectObject(pOldFont);
		break;
	}
	if ((pOldFont = cDC.SelectObject(pLogoFont)))
	{
		sizeNotice[2] = cDC.GetTextExtent(szNotice[2]);
		cDC.SelectObject(pOldFont);
	}
	if ((pOldFont = (sizeNotice[0].cx > 0 && sizeNotice[0].cy > 0 && sizeNotice[2].cx > 0 && sizeNotice[2].cy > 0) ? cDC.SelectObject(pFont) : (CFont *)NULL))
	{
		cDC.TextOut(prClip->left, prClip->bottom - sizeNotice[0].cy, (!bCalc) ? (LPCTSTR)szNotice[0] : EMPTYSTRING);
		cDC.SelectObject(pOldFont);
	}
	if ((pOldFont = (sizeNotice[0].cx > 0 && sizeNotice[0].cy > 0 && sizeNotice[2].cx > 0 && sizeNotice[2].cy > 0) ? cDC.SelectObject(pLogoFont) : (CFont *)NULL))
	{
		cDC.TextOut(prClip->left + sizeNotice[0].cx, prClip->bottom - sizeNotice[2].cy, (!bCalc) ? (LPCTSTR)szNotice[2] : EMPTYSTRING);
		cDC.SelectObject(pOldFont);
	}
	if ((pOldFont = (sizeNotice[0].cx > 0 && sizeNotice[0].cy > 0 && sizeNotice[1].cx > 0 && sizeNotice[1].cy > 0) ? cDC.SelectObject(pFont) : (CFont *)NULL))
	{
		cDC.TextOut(prClip->left + sizeNotice[0].cx + sizeNotice[2].cx, prClip->bottom - sizeNotice[1].cy, (!bCalc) ? (LPCTSTR)szNotice[1] : EMPTYSTRING);
		cDC.SelectObject(pOldFont);
	}
	if (sizeNotice[0].cx > 0 && sizeNotice[0].cy > 0 && sizeNotice[2].cx > 0 && sizeNotice[2].cy > 0)
	{
		prClip->bottom -= max(sizeNotice[0].cy, sizeNotice[2].cy);
		return TRUE;
	}
	return FALSE;
}

BOOL CTPEPWnd::DrawPrintDocFooter(CDC &cDC, LPRECT prClip, LPCTSTR pszFooter, CFont *pFont, BOOL bCalc)
{
	CRect  rCalc;
	CFont  *pOldFont;

	if ((pOldFont = cDC.SelectObject(pFont)))
	{
		cDC.DrawText(pszFooter, (rCalc = CRect(0, 0, prClip->right - prClip->left, 0)), DT_CALCRECT | DT_LEFT | DT_NOPREFIX | DT_SINGLELINE);
		cDC.DrawText(pszFooter, (!bCalc) ? prClip : CRect(0, 0, 0, 0), DT_LEFT | DT_BOTTOM | DT_NOPREFIX | DT_SINGLELINE);
		prClip->bottom -= 3 * rCalc.Height();
		cDC.SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

CString CTPEPWnd::GetPrintDocTitle() CONST
{
	CString  szTitle;

	szTitle.Format(STRING(IDS_TPEP_PRINTDOCUMENT_TITLE), (LPCTSTR)GetAccountSpacecraftName());
	return szTitle;
}

CString CTPEPWnd::GetPrintDocSubTitle(CONST CTPEPConnection *pConnection) CONST
{
	return((pConnection->GetType() == TPEP_TYPE_PACKETS) ? STRING(IDS_TPEP_TITLE_PACKETS) : STRING(IDS_TPEP_TITLE_PARAMETERS));
}

CString CTPEPWnd::GetPrintDocOperatingDetails(CONST CTPEPPrintJobInfo *pJobInfo, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality) CONST
{
	CString  szMode;
	CString  szUpdate;

	szMode = (nMode == DISPLAY_MODE_REALTIME) ? STRING(IDS_DISPLAY_MODE_REALTIME) : STRING(IDS_DISPLAY_MODE_HISTORY);
	szUpdate.Format((!lstrlen(pszTMUnit)) ? ((tTMUnit > 0) ? STRING(IDS_TPEP_PRINTDOCUMENT_FULLUPDATECOMMENT) : EMPTYSTRING) : ((nTMUnit == (UINT)-1) ? STRING(IDS_TPEP_PRINTDOCUMENT_INITUPDATECOMMENT) : STRING(IDS_TPEP_PRINTDOCUMENT_UPDATECOMMENT)), (LPCTSTR)tTMUnit.FormatGmt(), pszTMUnit, nTMUnit, (bQuality) ? STRING(IDS_TPEP_PRINTDOCUMENT_QUALITYGOOD) : STRING(IDS_TPEP_PRINTDOCUMENT_QUALITYBAD));
	return((!pJobInfo->GetComments().IsEmpty()) ? (((!szUpdate.IsEmpty()) ? (szUpdate + EOL + szMode) : szMode) + EOL + pJobInfo->GetComments()) : ((!szUpdate.IsEmpty()) ? (szUpdate + EOL + szMode) : szMode));
}

CString CTPEPWnd::GetPrintDocOperatingMode(CONST CTPEPPrintJobInfo *pJobInfo, CONST CUIntArray &nOOLColors) CONST
{
	UINT  nMode;
	UINT  nFlags;
	UINT  nColor;
	UINT  nCount;
	UINT  nStopCount;
	CString  szLegend;
	CString  szEvent;
	CString  szInfo;
	CString  szSide;
	CTimeKey  tTime;
	CTimeKey  tLastTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CTimeSpan  tDailyTime;
	CStringArray  szOOLColors;

	if ((nFlags = pJobInfo->GetPrintFlags()) & TPEP_PRINT_ATTIME)
	{
		if (pJobInfo->GetPrintAtTime(tTime))
		{
			szInfo.Format(STRING(IDS_TPEP_PRINTDOCUMENT_PRINTATTIME), (LPCTSTR)tTime.FormatGmt());
			szInfo += EOL;
		}
		if ((pJobInfo->GetPrintAtTime(tTime, tInterval) || pJobInfo->GetPrintAtTime(tTime, tInterval, nStopCount) || pJobInfo->GetPrintAtTime(tTime, tInterval, tStopTime)) && pJobInfo->GetPrintLastTime(tLastTime))
		{
			szInfo.Format(STRING(IDS_TPEP_PRINTDOCUMENT_PRINTATTIME), (LPCTSTR)CTimeKey(tTime.GetTime() + ((tLastTime.GetTime() - tTime.GetTime()) / tInterval.GetTotalSeconds())*tInterval.GetTotalSeconds()).FormatGmt());
			szInfo += EOL;
		}
	}
	if (nFlags & TPEP_PRINT_ATDAILYTIME)
	{
		if (pJobInfo->GetPrintAtDailyTime(tDailyTime) || pJobInfo->GetPrintAtDailyTime(tDailyTime, nStopCount) || pJobInfo->GetPrintAtDailyTime(tDailyTime, tStopTime))
		{
			szInfo.Format(STRING(IDS_TPEP_PRINTDOCUMENT_PRINTATDAILYTIME), (LPCTSTR)CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + tDailyTime.GetTotalSeconds()).FormatGmt(STRING(IDS_TIMEKEY_TIMEFORMAT)));
			szInfo += EOL;
		}
	}
	if (nFlags & TPEP_PRINT_ATEVENT)
	{
		if (pJobInfo->GetPrintAtEvent(szEvent))
		{
			szInfo.Format(STRING(IDS_TPEP_PRINTDOCUMENT_PRINTATEVENT), (LPCTSTR)szEvent);
			szInfo += EOL;
		}
	}
	if (!nFlags)
	{
		szInfo = STRING(IDS_TPEP_PRINTDOCUMENT_DEFAULTTIME);
		szInfo += EOL;
	}
	if ((nMode = pJobInfo->GetPrintMode()) & TPEP_PRINT_ALL)
	{
		szInfo += STRING(IDS_TPEP_PRINTDOCUMENT_PRINTALL);
		szInfo += EOL;
	}
	if (((nMode & TPEP_PRINT_FIRSTSIDE) || (nMode & TPEP_PRINT_LASTSIDE)) && pJobInfo->GetPrintBySide(nCount))
	{
		szSide.Format((nMode & TPEP_PRINT_FIRSTSIDE) ? STRING(IDS_TPEP_PRINTDOCUMENT_PRINTBYFIRSTSIDE) : STRING(IDS_TPEP_PRINTDOCUMENT_PRINTBYLASTSIDE), nCount);
		szSide = (nCount == 1) ? ((nMode & TPEP_PRINT_FIRSTSIDE) ? STRING(IDS_TPEP_PRINTDOCUMENT_PRINTBYFIRSTITEM) : STRING(IDS_TPEP_PRINTDOCUMENT_PRINTBYLASTITEM)) : (LPCTSTR)szSide;
		szInfo += szSide + EOL;
	}
	if (nMode & TPEP_PRINT_COLORLEGEND)
	{
		for (nColor = 0; nColor < (UINT)nOOLColors.GetSize(); nColor++)
		{
			switch (nOOLColors.GetAt(nColor))
			{
			case VGA_COLOR_BLACK:
			{ szOOLColors.Add(STRING(IDS_COLORSET_BLACK));
			break;
			}
			case VGA_COLOR_RED:
			{ szOOLColors.Add(STRING(IDS_COLORSET_RED));
			break;
			}
			case VGA_COLOR_GREEN:
			{ szOOLColors.Add(STRING(IDS_COLORSET_GREEN));
			break;
			}
			case VGA_COLOR_YELLOW:
			{ szOOLColors.Add(STRING(IDS_COLORSET_YELLOW));
			break;
			}
			case VGA_COLOR_BLUE:
			{ szOOLColors.Add(STRING(IDS_COLORSET_BLUE));
			break;
			}
			case VGA_COLOR_MAGENTA:
			{ szOOLColors.Add(STRING(IDS_COLORSET_MAGENTA));
			break;
			}
			case VGA_COLOR_CYAN:
			{ szOOLColors.Add(STRING(IDS_COLORSET_CYAN));
			break;
			}
			case VGA_COLOR_GRAY:
			{ szOOLColors.Add(STRING(IDS_COLORSET_GRAY));
			break;
			}
			case VGA_COLOR_LTGRAY:
			{ szOOLColors.Add(STRING(IDS_COLORSET_LTGRAY));
			break;
			}
			case VGA_COLOR_LTRED:
			{ szOOLColors.Add(STRING(IDS_COLORSET_LTRED));
			break;
			}
			case VGA_COLOR_LTGREEN:
			{ szOOLColors.Add(STRING(IDS_COLORSET_LTGREEN));
			break;
			}
			case VGA_COLOR_LTYELLOW:
			{ szOOLColors.Add(STRING(IDS_COLORSET_LTYELLOW));
			break;
			}
			case VGA_COLOR_LTBLUE:
			{ szOOLColors.Add(STRING(IDS_COLORSET_LTBLUE));
			break;
			}
			case VGA_COLOR_LTMAGENTA:
			{ szOOLColors.Add(STRING(IDS_COLORSET_LTMAGENTA));
			break;
			}
			case VGA_COLOR_LTCYAN:
			{ szOOLColors.Add(STRING(IDS_COLORSET_LTCYAN));
			break;
			}
			case VGA_COLOR_WHITE:
			{ szOOLColors.Add(STRING(IDS_COLORSET_WHITE));
			break;
			}
			}
		}
		szLegend.Format(STRING(IDS_TPEP_PRINTDOCUMENT_OOLLEGEND), (LPCTSTR)szOOLColors.GetAt(TPEP_OOLCOLOR_NOLIMIT), (LPCTSTR)szOOLColors.GetAt(TPEP_OOLCOLOR_SOFTLIMIT), (LPCTSTR)szOOLColors.GetAt(TPEP_OOLCOLOR_HARDLIMIT), (LPCTSTR)szOOLColors.GetAt(TPEP_OOLCOLOR_DELTALIMIT), (LPCTSTR)szOOLColors.GetAt(TPEP_OOLCOLOR_CONSISTENCYLIMIT));
		szInfo += szLegend + EOL;
	}
	return szInfo;
}

CString CTPEPWnd::GetPrintDocMessagesTitle(CONST CStringArray &szColumns) CONST
{
	INT  nColumn;
	INT  nColumns;
	CString  szItems;

	for (nColumn = 0, nColumns = (INT)szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		szItems += (nColumn > 0) ? CString(TAB) : EMPTYSTRING;
		szItems += szColumns.GetAt(nColumn);
	}
	return szItems;
}

CString CTPEPWnd::GetPrintDocNotice() CONST
{
	CVersionInfo  cVersionInfo;

	return cVersionInfo.QueryComments();
}

CString CTPEPWnd::GetPrintDocFooter(CONST CTimeKey &tTime, LPCTSTR pszPrinterName, INT nPages, INT nPage) CONST
{
	CString  szFooter;

	szFooter.Format(STRING(IDS_TPEP_PRINTDOCUMENT_FOOTER), (LPCTSTR)tTime.Format(IDS_TIMEKEY_DATEFORMAT), (LPCTSTR)tTime.Format(IDS_TIMEKEY_TIMEFORMAT), pszPrinterName, nPage, nPages);
	return szFooter;
}

INT CTPEPWnd::ExtractPrintDocText(LPCTSTR pszText, CStringArray &szColumnsText) CONST
{
	INT  nPos[2];
	INT  nLength;
	CString  szText;

	for (nPos[0] = 0, nLength = lstrlen(pszText), szColumnsText.RemoveAll(); nPos[0] <= nLength; nPos[0] += ++nPos[1])
	{
		if ((nPos[1] = (INT)_tcscspn((szText = pszText + nPos[0]), CString(CTextView::GetColumnDelimiter()))) < nLength - nPos[0])
		{
			szColumnsText.Add((nPos[1] > 0) ? szText.Left(nPos[1]) : EMPTYSTRING);
			continue;
		}
		szColumnsText.Add(szText);
		break;
	}
	return((INT)szColumnsText.GetSize());
}

INT CTPEPWnd::CalcPrintDocText(CDC &cDC, CFont *pFont, LPCTSTR pszColumnsText, INT nWidth, CString &szText) CONST
{
	INT  nPos;
	CFont  *pOldFont;

	if ((pOldFont = cDC.SelectObject(pFont)))
	{
		for (nPos = lstrlen(pszColumnsText), szText = pszColumnsText; nPos > 0; nPos--)
		{
			if (cDC.GetTextExtent(szText.Left(nPos)).cx >= nWidth) continue;
			break;
		}
		szText = szText.Left(nPos);
		cDC.SelectObject(pOldFont);
		return szText.GetLength();
	}
	return 0;
}

BOOL CTPEPWnd::CalcPrintDocTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 48, (INT)((-5.3*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CTPEPWnd::CalcPrintDocSubTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 64, (INT)((-4.0*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CTPEPWnd::CalcPrintDocOperatingDetailsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 76, (INT)((-3.3*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CTPEPWnd::CalcPrintDocOperatingModeFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 76, (INT)((-3.3*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CTPEPWnd::CalcPrintDocMessagesFonts(CDC &cDC, CONST RECT &rArea, CONST CStringArray &szColumns, CONST CStringArray &szContents, CONST LOGFONT *pTitleFont, CONST LOGFONT *pMessagesFont, CONST LOGFONT *pValuesFont, CFont &cTitleFont, CFont &cMessagesFont, CFont &cValuesFont) CONST
{
	INT  nWidth;
	INT  nHeight;
	CFont  cFont[3];
	CUIntArray  nTabs;

	for (nHeight = max(-(rArea.right - rArea.left) / 64, (INT)((-4.0*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))); nHeight < 0; nHeight++)
	{
		if (cFont[0].CreateFont(nHeight, 0, pTitleFont->lfEscapement, pTitleFont->lfOrientation, FW_BOLD, pTitleFont->lfItalic, pTitleFont->lfUnderline, pTitleFont->lfStrikeOut, pTitleFont->lfCharSet, pTitleFont->lfOutPrecision, pTitleFont->lfClipPrecision, pTitleFont->lfQuality, pTitleFont->lfPitchAndFamily, pTitleFont->lfFaceName))
		{
			if (cFont[1].CreateFont((4 * nHeight) / 5, 0, pMessagesFont->lfEscapement, pMessagesFont->lfOrientation, pMessagesFont->lfWeight, pMessagesFont->lfItalic, pMessagesFont->lfUnderline, pMessagesFont->lfStrikeOut, pMessagesFont->lfCharSet, pMessagesFont->lfOutPrecision, pMessagesFont->lfClipPrecision, pMessagesFont->lfQuality, pMessagesFont->lfPitchAndFamily, pMessagesFont->lfFaceName))
			{
				if (cFont[2].CreateFont((4 * nHeight) / 5, 0, pValuesFont->lfEscapement, pValuesFont->lfOrientation, pValuesFont->lfWeight, pValuesFont->lfItalic, pValuesFont->lfUnderline, pValuesFont->lfStrikeOut, pValuesFont->lfCharSet, pValuesFont->lfOutPrecision, pValuesFont->lfClipPrecision, pValuesFont->lfQuality, pValuesFont->lfPitchAndFamily, pValuesFont->lfFaceName))
				{
					if (CalcPrintDocTitleWidth(cDC, szColumns, szContents, &cFont[0], &cFont[1], &cFont[2], nTabs) > 0)
					{
						if (szColumns.GetSize() == 1 && szColumns.GetAt(0) == STRING(IDS_TPEP_TITLEITEM_MESSAGES))
						{
							cTitleFont.Attach(cFont[0].Detach());
							cMessagesFont.Attach(cFont[1].Detach());
							cValuesFont.Attach(cFont[2].Detach());
							break;
						}
						if ((nWidth = nTabs.GetAt(nTabs.GetSize() - 1)) > rArea.right - rArea.left)
						{
							nHeight = (nHeight*(rArea.right - rArea.left)) / nWidth - 1;
							cFont[0].DeleteObject();
							cFont[1].DeleteObject();
							cFont[2].DeleteObject();
							continue;
						}
						cTitleFont.Attach(cFont[0].Detach());
						cMessagesFont.Attach(cFont[1].Detach());
						cValuesFont.Attach(cFont[2].Detach());
						break;
					}
					cFont[2].DeleteObject();
				}
				cFont[1].DeleteObject();
			}
			cFont[0].DeleteObject();
		}
	}
	return((cTitleFont.GetSafeHandle() && cMessagesFont.GetSafeHandle() && cValuesFont.GetSafeHandle()) ? TRUE : FALSE);
}

BOOL CTPEPWnd::CalcPrintDocNoticeFonts(CDC &cDC, CONST RECT &rArea, CFont &cFont, CFont &cLogoFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 96, (INT)((-2.6*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL) && cLogoFont.CreateFont(max(-(rArea.right - rArea.left) / 96, (INT)((-2.6*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, STRING(IDS_FONTFACE_COMPANYLOGO));
}

BOOL CTPEPWnd::CalcPrintDocFooterFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 80, (INT)((-3.0*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

INT CTPEPWnd::CalcPrintDocTitleWidth(CDC &cDC, LPCTSTR pszColumn, CFont *pTitleFont) CONST
{
	INT  nWidth;
	CFont  *pOldFont;

	if ((pOldFont = cDC.SelectObject(pTitleFont)))
	{
		nWidth = cDC.GetTextExtent(pszColumn, lstrlen(pszColumn)).cx;
		cDC.SelectObject(pOldFont);
		return nWidth;
	}
	return 0;
}
INT CTPEPWnd::CalcPrintDocTitleWidth(CDC &cDC, CONST CStringArray &szColumns, CONST CStringArray &szContents, CFont *pTitleFont, CFont *pMessagesFont, CFont *pValuesFont, CUIntArray &nTabs) CONST
{
	INT  nIndent;
	INT  nColumn;
	INT  nColumns;
	INT  nWidth[2];
	CFont  *pOldFont;
	TEXTMETRIC  tmFont;
	CStringArray  szLines;

	for (nIndent = 0, nTabs.RemoveAll(); (pOldFont = cDC.SelectObject(pTitleFont)); )
	{
		nIndent = (cDC.GetTextMetrics(&tmFont)) ? max(tmFont.tmAveCharWidth, nIndent) : nIndent;
		cDC.SelectObject(pOldFont);
		break;
	}
	if ((pOldFont = cDC.SelectObject(pMessagesFont)))
	{
		if (cDC.GetTextMetrics(&tmFont)) nIndent = max(tmFont.tmAveCharWidth, nIndent);
		cDC.SelectObject(pOldFont);
	}
	for (nColumn = 0, nColumns = (INT)szColumns.GetSize(), szLines.Copy(szContents); nColumn < nColumns; nColumn++)
	{
		nWidth[0] = CalcPrintDocTitleWidth(cDC, szColumns.GetAt(nColumn), pTitleFont);
		nWidth[1] = CalcPrintDocColumnWidth(cDC, szColumns.GetAt(nColumn), szLines, pMessagesFont, pValuesFont);
		nTabs.Add((nTabs.GetSize() > 0) ? (2 * nIndent + nTabs.GetAt(nTabs.GetSize() - 1) + max(nWidth[0], nWidth[1])) : (2 * nIndent + max(nWidth[0], nWidth[1])));
	}
	if (nTabs.GetSize() > 0)
	{
		nTabs.SetAt(nTabs.GetSize() - 1, nTabs.GetAt(nTabs.GetSize() - 1) - nIndent);
		return((INT)nTabs.GetSize());
	}
	return 0;
}

INT CTPEPWnd::CalcPrintDocColumnWidth(CDC &cDC, LPCTSTR pszColumn, CStringArray &szContents, CFont *pMessagesFont, CFont *pValuesFont) CONST
{
	INT  nPos;
	INT  nLine;
	INT  nLines;
	INT  nWidth;
	CFont  *pOldFont;

	if ((pOldFont = (lstrcmp(pszColumn, STRING(IDS_TPEP_TITLEITEM_VALUE))) ? cDC.SelectObject(pMessagesFont) : cDC.SelectObject(pValuesFont)))
	{
		for (nLine = 0, nLines = (INT)szContents.GetSize(), nWidth = 0; nLine < nLines; nLine++)
		{
			if ((nPos = szContents.GetAt(nLine).Find(CTextView::GetColumnDelimiter())) >= 0)
			{
				nWidth = max(cDC.GetTextExtent(szContents.GetAt(nLine).Left(nPos)).cx, nWidth);
				szContents.SetAt(nLine, szContents.GetAt(nLine).Mid(nPos + 1));
				continue;
			}
			if (szContents.GetAt(nLine).GetLength() > 0)
			{
				nWidth = max(cDC.GetTextExtent(szContents.GetAt(nLine)).cx, nWidth);
				szContents.SetAt(nLine, EMPTYSTRING);
				continue;
			}
		}
		cDC.SelectObject(pOldFont);
		return nWidth;
	}
	return 0;
}

BOOL CTPEPWnd::CalcPrintDocRect(CDC &cDC, CONST RECT &rtMargin, BOOL bMetric) CONST
{
	CRect  rClip;

	rClip.SetRect(0, 0, cDC.GetDeviceCaps(HORZRES), cDC.GetDeviceCaps(VERTRES));
	rClip.DeflateRect((bMetric) ? (rtMargin.left*cDC.GetDeviceCaps(HORZRES)) / (100 * cDC.GetDeviceCaps(HORZSIZE)) : (rtMargin.left*cDC.GetDeviceCaps(LOGPIXELSX)) / 1000, (bMetric) ? (rtMargin.top*cDC.GetDeviceCaps(VERTRES)) / (100 * cDC.GetDeviceCaps(VERTSIZE)) : (rtMargin.top*cDC.GetDeviceCaps(LOGPIXELSY)) / 1000, (bMetric) ? (rtMargin.right*cDC.GetDeviceCaps(HORZRES)) / (100 * cDC.GetDeviceCaps(HORZSIZE)) : (rtMargin.right*cDC.GetDeviceCaps(LOGPIXELSX)) / 1000, (bMetric) ? (rtMargin.bottom*cDC.GetDeviceCaps(VERTRES)) / (100 * cDC.GetDeviceCaps(VERTSIZE)) : (rtMargin.bottom*cDC.GetDeviceCaps(LOGPIXELSY)) / 1000);
	return((cDC.IntersectClipRect(rClip) != ERROR) ? TRUE : FALSE);
}

BEGIN_MESSAGE_MAP(CTPEPWnd, CDisplayWnd)
	//{{AFX_MSG_MAP(CTPEPWnd)
	ON_WM_CREATE()
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_SETFOCUS()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_COMMAND(IDM_TPEPSETTINGS, OnSettings)
	ON_COMMAND(IDM_TPEPCONNECTION, OnConnection)
	ON_COMMAND(IDM_TPEPPARAMETERS, OnParameters)
	ON_COMMAND(IDM_TPEPALERTS, OnAlerts)
	ON_COMMAND(IDM_TPEPHOLD, OnHold)
	ON_COMMAND(IDM_TPEPCLEARALL, OnClearAll)
	ON_COMMAND(IDM_TPEPPRINT, OnPrint)
	ON_UPDATE_COMMAND_UI(IDM_TPEPSETTINGS, OnUpdateSettings)
	ON_UPDATE_COMMAND_UI(IDM_TPEPCONNECTION, OnUpdateConnection)
	ON_UPDATE_COMMAND_UI(IDM_TPEPPARAMETERS, OnUpdateParameters)
	ON_UPDATE_COMMAND_UI(IDM_TPEPALERTS, OnUpdateAlerts)
	ON_UPDATE_COMMAND_UI(IDM_TPEPHOLD, OnUpdateHold)
	ON_UPDATE_COMMAND_UI(IDM_TPEPCLEARALL, OnUpdateClearAll)
	ON_UPDATE_COMMAND_UI(IDM_TPEPPRINT, OnUpdatePrint)
	ON_UPDATE_COMMAND_UI(ID_TPEP_STATUSBAR_MESSAGEPANE, OnUpdateStatusBarMessagePane)
	ON_UPDATE_COMMAND_UI(ID_TPEP_STATUSBAR_COMPUTERPANE, OnUpdateStatusBarComputerPane)
	ON_UPDATE_COMMAND_UI(ID_TPEP_STATUSBAR_MODEPANE, OnUpdateStatusBarModePane)
	ON_UPDATE_COMMAND_UI(ID_TPEP_STATUSBAR_TYPEPANE, OnUpdateStatusBarTypePane)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTPEPWnd message handlers

int CTPEPWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDisplayWnd::OnCreate(lpCreateStruct) != -1)
	{
		for (EnableDocking(CBRS_ALIGN_TOP); CreateToolBar() && CreateStatusBar() && CreateView() && LoadAccelTable(MAKEINTRESOURCE(IDR_TPEPFRAME)); )
		{
			UpdateBars();
			return 0;
		}
	}
	return -1;
}

void CTPEPWnd::OnGetMinMaxInfo(MINMAXINFO *lpMMI)
{
	CRect  rWnd;

	rWnd = RepositionView(FALSE);
	lpMMI->ptMinTrackSize.x = max(lpMMI->ptMinTrackSize.x, rWnd.Width());
	lpMMI->ptMinTrackSize.y = max(lpMMI->ptMinTrackSize.y, rWnd.Height());
	CDisplayWnd::OnGetMinMaxInfo(lpMMI);
}

void CTPEPWnd::OnSize(UINT nType, int cx, int cy)
{
	CDisplayWnd::OnSize(nType, cx, cy);
	m_wndView.RecalcLayout();
}

BOOL CTPEPWnd::OnEraseBkgnd(CDC *pDC)
{
	if (!IsInitialized())
	{
		m_wndToolBar.UpdateWindow();
		m_wndStatusBar.UpdateWindow();
	}
	return TRUE;
}

void CTPEPWnd::OnSetFocus(CWnd *pOldWnd)
{
	if (pOldWnd->GetSafeHwnd() == m_wndView.GetSafeHwnd())
	{
		GetParent()->SetFocus();
		return;
	}
	if (m_wndView.GetMessageCount() > 0)
	{
		m_wndView.SetFocus();
		return;
	}
	CDisplayWnd::OnSetFocus(pOldWnd);
}

void CTPEPWnd::OnTimer(UINT_PTR nEventID)
{
	BOOL  bConnection;
	CString  szComputer;
	CComputerToken  cComputerToken;
	CTPEPConnection  cConnection;

	for (KillTimer(nEventID); GetTPEPService()->IsAvailable(); )
	{
		if (GetConnectionProperties(szComputer, &cConnection, bConnection))
		{
			if (cComputerToken == szComputer || GetNetworkBrowseService()->IsComputerOnNetwork(szComputer))
			{
				if (bConnection)
				{
					if (GetTPEPService()->AttachClientConnection(szComputer, &cConnection, this) || GetTPEPService()->AddClientConnection(szComputer, &cConnection, this))
					{
						if (ProcessRealtimeData() || StartRetrieveData())
						{
							UpdateBars();
							break;
						}
					}
				}
				else
				{
					UpdateBars();
					break;
				}
			}
			ReportEvent((!szComputer.IsEmpty() && cConnection.IsInitialized()) ? SYSTEM_WARNING_TPEP_CONNECT_FAILURE : SYSTEM_NOERROR);
		}
		UpdateBars();
		break;
	}
	CDisplayWnd::OnTimer(nEventID);
}

void CTPEPWnd::OnSettings()
{
	CHourglassCursor  cCursor;

	ReportEvent((m_dlgSettings.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CTPEPWnd::OnConnection()
{
	BOOL  bConnection;
	CString  szComputer;
	CTPEPConnection  cConnection;
	CHourglassCursor  cCursor;

	GetConnectionProperties(szComputer, &cConnection, bConnection);
	ReportEvent((m_dlgConnection.Create(this, szComputer, &cConnection, bConnection) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CTPEPWnd::OnParameters()
{
	CHourglassCursor  cCursor;

	ReportEvent((m_dlgParameters.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CTPEPWnd::OnAlerts()
{
	CTPEPAlerts  pAlerts;
	CTPEPConnection  cConnection;
	CHourglassCursor  cCursor;

	GetAlerts(pAlerts);
	GetConnectionProperties(&cConnection);
	ReportEvent((m_dlgAlerts.Create(this, pAlerts, &cConnection) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CTPEPWnd::OnHold()
{
	SetHoldFlag(!GetHoldFlag());
}

void CTPEPWnd::OnClearAll()
{
	CHourglassCursor  cCursor;

	ClearAllMessages();
}

void CTPEPWnd::OnPrint()
{
	CHourglassCursor  cCursor;

	ReportEvent((!Print()) ? SYSTEM_WARNING_DISPLAY_PRINT_FAILURE : SYSTEM_NOERROR);
}

BOOL CTPEPWnd::OnCloseOpenDialog(UINT nCode)
{
	UINT  nMode;
	UINT  nLimit;
	UINT  nDigits;
	UINT  nStatus;
	BOOL  bToolTips;
	BOOL  bConnection;
	LOGFONT  fntTitle;
	LOGFONT  fntMessages;
	CString  szComputer;
	COLORREF  nColor;
	CTimeKey  tRange[2][2];
	CTimeSpan  tDailyRange[2];
	CTimeSpan  tPeriodical;
	CUIntArray  nOOLColors;
	CUIntArray  nTitleItems;
	CTPEPConnection  cConnection;
	CTPEPPrintJobs  pJobs;

	if (nCode == IDOK)
	{
		for (SetWindowText(m_dlgOpen.GetTitle()), SetType(MAKELONG(DISPLAY_TYPE_TPEP, m_dlgOpen.GetType())), SetLayout(m_dlgOpen.GetType()); m_dlgOpen.IsLayoutModified(); )
		{
			m_dlgOpen.GetLayoutColumns(nTitleItems);
			m_dlgOpen.GetLayoutTitleFont(&fntTitle);
			m_dlgOpen.GetLayoutMessagesFont(&fntMessages);
			m_dlgOpen.GetLayoutToolTipMode(bToolTips);
			if (!SetLayoutColumns(nTitleItems) || !SetTitleFont(&fntTitle) || !SetMessagesFont(&fntMessages) || !EnableToolTipMode(bToolTips)) return FALSE;
			break;
		}
		if (m_dlgOpen.IsFilteringModified())
		{
			m_dlgOpen.GetFilterMode(nMode);
			m_dlgOpen.GetFilterLimit(nLimit);
			m_dlgOpen.GetFilterDigits(nDigits);
			m_dlgOpen.GetFilterStatus(nStatus);
			m_dlgOpen.GetFilterColors(nColor, nOOLColors);
			m_dlgOpen.GetFilterRange(tRange[0][0], tRange[0][1]);
			m_dlgOpen.GetFilterDailyRange(tDailyRange[0], tDailyRange[1]);
			m_dlgOpen.GetFilterPeriodicalRange(tRange[1][0], tPeriodical, tRange[1][1]);
			if (!SetFilterMode(nMode) || SetFilterLimit(nLimit) < 0 || SetFilterStatus(nStatus) < 0 || SetFilterRange(tRange[0][0], tRange[0][1]) < 0 || SetFilterDailyRange(tDailyRange[0], tDailyRange[1]) < 0 || SetFilterPeriodicalRange(tRange[1][0], tPeriodical, tRange[1][1]) < 0 || !SetFilterDigits(nDigits) || !SetFilterColors(nColor, nOOLColors)) return FALSE;
		}
		if (m_dlgOpen.IsPrintingModified())
		{
			m_dlgOpen.GetPrintJobs(pJobs);
			if (!SetPrintJobs(pJobs)) return FALSE;
		}
		m_dlgOpen.GetConnection(szComputer, &cConnection, bConnection);
		return((SetConnectionProperties(szComputer, &cConnection, bConnection)) ? ProcessConnection() : FALSE);
	}
	return TRUE;
}

BOOL CTPEPWnd::OnCloseSettingsDialog(UINT nCode)
{
	UINT  nMode;
	UINT  nLimit;
	UINT  nDigits;
	UINT  nStatus;
	BOOL  bToolTips;
	LOGFONT  fntTitle;
	LOGFONT  fntMessages;
	COLORREF  nColor;
	CTimeKey  tRange[2][2];
	CTimeSpan  tDailyRange[2];
	CTimeSpan  tPeriodical;
	CUIntArray  nColumns;
	CUIntArray  nOOLColors;
	CTPEPPrintJobs  pJobs;

	if (nCode == IDOK)
	{
		for (GetLayoutColumns(nColumns); m_dlgSettings.IsLayoutModified(); )
		{
			m_dlgSettings.GetLayoutColumns(nColumns);
			m_dlgSettings.GetLayoutTitleFont(&fntTitle);
			m_dlgSettings.GetLayoutMessagesFont(&fntMessages);
			m_dlgSettings.GetLayoutToolTipMode(bToolTips);
			if (!SetLayoutColumns(nColumns) || !SetTitleFont(&fntTitle) || !SetMessagesFont(&fntMessages) || !EnableToolTipMode(bToolTips)) return FALSE;
			break;
		}
		if (m_dlgSettings.IsFilteringModified())
		{
			m_dlgSettings.GetFilterMode(nMode);
			m_dlgSettings.GetFilterLimit(nLimit);
			m_dlgSettings.GetFilterDigits(nDigits);
			m_dlgSettings.GetFilterStatus(nStatus);
			m_dlgSettings.GetFilterColors(nColor, nOOLColors);
			m_dlgSettings.GetFilterRange(tRange[0][0], tRange[0][1]);
			m_dlgSettings.GetFilterDailyRange(tDailyRange[0], tDailyRange[1]);
			m_dlgSettings.GetFilterPeriodicalRange(tRange[1][0], tPeriodical, tRange[1][1]);
			if (!SetFilterMode(nMode) || SetFilterLimit(nLimit) < 0 || SetFilterStatus(nStatus) < 0 || SetFilterRange(tRange[0][0], tRange[0][1]) < 0 || SetFilterDailyRange(tDailyRange[0], tDailyRange[1]) < 0 || SetFilterPeriodicalRange(tRange[1][0], tPeriodical, tRange[1][1]) < 0 || !SetFilterDigits(nDigits) || !SetFilterColors(nColor, nOOLColors)) return FALSE;
		}
		if (m_dlgSettings.IsPrintingModified())
		{
			m_dlgSettings.GetPrintJobs(pJobs);
			if (!SetPrintJobs(pJobs)) return FALSE;
		}
		UpdateData();
		UpdateAllPanes();
	}
	return TRUE;
}

void CTPEPWnd::OnDestroy()
{
	CHourglassCursor  cCursor;

	Stop();
	CDisplayWnd::OnDestroy();
}

void CTPEPWnd::OnUpdateSettings(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsInitialized());
	pCmdUI->SetCheck(IsWindow(m_dlgSettings.GetSafeHwnd()));
}

void CTPEPWnd::OnUpdateConnection(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsInitialized());
	pCmdUI->SetCheck(IsWindow(m_dlgConnection.GetSafeHwnd()));
}

void CTPEPWnd::OnUpdateParameters(CCmdUI *pCmdUI)
{
	CTPEPConnection  cConnection;

	pCmdUI->Enable((IsInitialized() && (HIWORD(GetType()) == TPEP_TYPE_NORMAL || HIWORD(GetType()) == TPEP_TYPE_SIMPLE) && GetConnectionProperties(&cConnection) && cConnection.GetType() == TPEP_TYPE_PARAMETERS) ? TRUE : FALSE);
	pCmdUI->SetCheck(IsWindow(m_dlgParameters.GetSafeHwnd()));
}

void CTPEPWnd::OnUpdateAlerts(CCmdUI *pCmdUI)
{
	CTPEPConnection  cConnection;

	pCmdUI->Enable((IsInitialized() && HIWORD(GetType()) == TPEP_TYPE_NORMAL  &&  GetConnectionProperties(&cConnection) && cConnection.GetType() == TPEP_TYPE_PARAMETERS) ? TRUE : FALSE);
	pCmdUI->SetCheck(IsWindow(m_dlgAlerts.GetSafeHwnd()));
}

void CTPEPWnd::OnUpdateHold(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsInitialized() && HasHoldFlag());
	pCmdUI->SetCheck(GetHoldFlag());
}

void CTPEPWnd::OnUpdateClearAll(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsInitialized() && GetMessageCount() > 0) ? TRUE : FALSE);
}

void CTPEPWnd::OnUpdatePrint(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsInitialized() && IsDefaultPrinterAvailable() && CanPrint()) ? TRUE : FALSE);
}

void CTPEPWnd::OnUpdateStatusBarMessagePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CTPEPWnd::OnUpdateStatusBarComputerPane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CTPEPWnd::OnUpdateStatusBarModePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CTPEPWnd::OnUpdateStatusBarTypePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}
