// AND.CPP : Alphanumeric Display Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the alphanumeric
// display related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1998/05/25 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static UINT BASED_CODE nANDStatusBarIndicators[] =
{
	ID_AND_STATUSBAR_MESSAGEPANE,
	ID_AND_STATUSBAR_MODEPANE,
	ID_AND_STATUSBAR_TYPEPANE
};



/////////////////////////////////////////////////////////////////////////////
// CANDPrintJobInfo

CANDPrintJobInfo::CANDPrintJobInfo() : CObject()
{
	m_nPrintMode = 0;
	m_nPrintFlags = 0;
	m_nPrintColumns = 0;
	m_nPrintByCount = 0;
	m_nPrintCount[0] = 0;
	m_nPrintCount[1] = 0;
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

VOID CANDPrintJobInfo::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CANDPrintJobInfo::GetName() CONST
{
	return m_szName;
}

VOID CANDPrintJobInfo::SetProfile(LPCTSTR pszProfile)
{
	m_szProfile = pszProfile;
}

CString CANDPrintJobInfo::GetProfile() CONST
{
	return m_szProfile;
}

VOID CANDPrintJobInfo::SetComments(LPCTSTR pszComments)
{
	m_szComments = pszComments;
}

CString CANDPrintJobInfo::GetComments() CONST
{
	return m_szComments;
}

BOOL CANDPrintJobInfo::SetPrintMode(UINT nMode)
{
	m_nPrintMode = nMode;
	return TRUE;
}

UINT CANDPrintJobInfo::GetPrintMode() CONST
{
	return m_nPrintMode;
}

BOOL CANDPrintJobInfo::SetPrintFlags(UINT nFlags)
{
	if (nFlags == AND_PRINT_ATTIME || nFlags == AND_PRINT_ATDAILYTIME || nFlags == AND_PRINT_ATEVENT || !nFlags)
	{
		m_nPrintFlags = nFlags;
		return TRUE;
	}
	return FALSE;
}

UINT CANDPrintJobInfo::GetPrintFlags() CONST
{
	return m_nPrintFlags;
}

BOOL CANDPrintJobInfo::SetPrintBySide(UINT nCount)
{
	if ((m_nPrintMode & AND_PRINT_FIRSTSIDE) || (m_nPrintMode & AND_PRINT_LASTSIDE))
	{
		m_nPrintByCount = nCount;
		return TRUE;
	}
	return FALSE;
}

BOOL CANDPrintJobInfo::GetPrintBySide(UINT &nCount) CONST
{
	if ((m_nPrintMode & AND_PRINT_FIRSTSIDE) || (m_nPrintMode & AND_PRINT_LASTSIDE))
	{
		nCount = m_nPrintByCount;
		return TRUE;
	}
	return FALSE;
}

BOOL CANDPrintJobInfo::SetPrintFormat(UINT nColumns)
{
	if (m_nPrintMode & AND_PRINT_CUSTOMLAYOUT)
	{
		m_nPrintColumns = nColumns;
		return TRUE;
	}
	return FALSE;
}

BOOL CANDPrintJobInfo::GetPrintFormat(UINT &nColumns) CONST
{
	if (m_nPrintMode & AND_PRINT_CUSTOMLAYOUT)
	{
		nColumns = m_nPrintColumns;
		return TRUE;
	}
	return FALSE;
}

BOOL CANDPrintJobInfo::SetPrintAtTime(CONST CTimeKey &tTime)
{
	if ((m_nPrintMode & AND_PRINT_ATTIME) && !(m_nPrintMode & AND_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & AND_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & AND_PRINT_REPEATSTOPBYTIME))
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
BOOL CANDPrintJobInfo::SetPrintAtTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval)
{
	if ((m_nPrintMode & AND_PRINT_ATTIME) && (m_nPrintMode & AND_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & AND_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & AND_PRINT_REPEATSTOPBYTIME))
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
BOOL CANDPrintJobInfo::SetPrintAtTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval, UINT nStopCount)
{
	if ((m_nPrintMode & AND_PRINT_ATTIME) && (m_nPrintMode & AND_PRINT_REPEATBYINTERVAL) && (m_nPrintMode & AND_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & AND_PRINT_REPEATSTOPBYTIME))
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
BOOL CANDPrintJobInfo::SetPrintAtTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval, CONST CTimeKey &tStopTime)
{
	if ((m_nPrintMode & AND_PRINT_ATTIME) && (m_nPrintMode & AND_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & AND_PRINT_REPEATSTOPBYCOUNT) && (m_nPrintMode & AND_PRINT_REPEATSTOPBYTIME))
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

BOOL CANDPrintJobInfo::GetPrintAtTime(CTimeKey &tTime) CONST
{
	if ((m_nPrintMode & AND_PRINT_ATTIME) && !(m_nPrintMode & AND_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & AND_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & AND_PRINT_REPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtTime;
		return TRUE;
	}
	return FALSE;
}
BOOL CANDPrintJobInfo::GetPrintAtTime(CTimeKey &tTime, CTimeSpan &tInterval) CONST
{
	if ((m_nPrintMode & AND_PRINT_ATTIME) && (m_nPrintMode & AND_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & AND_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & AND_PRINT_REPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtTime;
		tInterval = m_tRepeatInterval;
		return TRUE;
	}
	return FALSE;
}
BOOL CANDPrintJobInfo::GetPrintAtTime(CTimeKey &tTime, CTimeSpan &tInterval, UINT &nStopCount) CONST
{
	if ((m_nPrintMode & AND_PRINT_ATTIME) && (m_nPrintMode & AND_PRINT_REPEATBYINTERVAL) && (m_nPrintMode & AND_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & AND_PRINT_REPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtTime;
		tInterval = m_tRepeatInterval;
		nStopCount = m_nRepeatStopByCount[0];
		return TRUE;
	}
	return FALSE;
}
BOOL CANDPrintJobInfo::GetPrintAtTime(CTimeKey &tTime, CTimeSpan &tInterval, CTimeKey &tStopTime) CONST
{
	if ((m_nPrintMode & AND_PRINT_ATTIME) && (m_nPrintMode & AND_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & AND_PRINT_REPEATSTOPBYCOUNT) && (m_nPrintMode & AND_PRINT_REPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtTime;
		tInterval = m_tRepeatInterval;
		tStopTime = m_tRepeatStopByTime[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CANDPrintJobInfo::SetPrintAtDailyTime(CONST CTimeSpan &tTime)
{
	TIMEKEY  tTimeKey;

	if ((m_nPrintMode & AND_PRINT_ATDAILYTIME) && !(m_nPrintMode & AND_PRINT_DAILYREPEATSTOPBYCOUNT) && !(m_nPrintMode & AND_PRINT_DAILYREPEATSTOPBYTIME))
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
BOOL CANDPrintJobInfo::SetPrintAtDailyTime(CONST CTimeSpan &tTime, UINT nStopCount)
{
	TIMEKEY  tTimeKey;

	if ((m_nPrintMode & AND_PRINT_ATDAILYTIME) && (m_nPrintMode & AND_PRINT_DAILYREPEATSTOPBYCOUNT) && !(m_nPrintMode & AND_PRINT_DAILYREPEATSTOPBYTIME))
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
BOOL CANDPrintJobInfo::SetPrintAtDailyTime(CONST CTimeSpan &tTime, CONST CTimeKey &tStopTime)
{
	TIMEKEY  tTimeKey;

	if ((m_nPrintMode & AND_PRINT_ATDAILYTIME) && !(m_nPrintMode & AND_PRINT_DAILYREPEATSTOPBYCOUNT) && (m_nPrintMode & AND_PRINT_DAILYREPEATSTOPBYTIME))
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

BOOL CANDPrintJobInfo::GetPrintAtDailyTime(CTimeSpan &tTime) CONST
{
	if ((m_nPrintMode & AND_PRINT_ATDAILYTIME) && !(m_nPrintMode & AND_PRINT_DAILYREPEATSTOPBYCOUNT) && !(m_nPrintMode & AND_PRINT_DAILYREPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtDailyTime;
		return TRUE;
	}
	return FALSE;
}
BOOL CANDPrintJobInfo::GetPrintAtDailyTime(CTimeSpan &tTime, UINT &nStopCount) CONST
{
	if ((m_nPrintMode & AND_PRINT_ATDAILYTIME) && (m_nPrintMode & AND_PRINT_DAILYREPEATSTOPBYCOUNT) && !(m_nPrintMode & AND_PRINT_DAILYREPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtDailyTime;
		nStopCount = m_nRepeatStopByCount[1];
		return TRUE;
	}
	return FALSE;
}
BOOL CANDPrintJobInfo::GetPrintAtDailyTime(CTimeSpan &tTime, CTimeKey &tStopTime) CONST
{
	if ((m_nPrintMode & AND_PRINT_ATDAILYTIME) && !(m_nPrintMode & AND_PRINT_DAILYREPEATSTOPBYCOUNT) && (m_nPrintMode & AND_PRINT_DAILYREPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtDailyTime;
		tStopTime = m_tRepeatStopByTime[1];
		return TRUE;
	}
	return FALSE;
}

BOOL CANDPrintJobInfo::SetPrintAtEvent(LPCTSTR pszEvent)
{
	if (m_nPrintMode & AND_PRINT_ATEVENT)
	{
		m_szEvent = pszEvent;
		return TRUE;
	}
	return FALSE;
}

BOOL CANDPrintJobInfo::GetPrintAtEvent(CString &szEvent) CONST
{
	if (m_nPrintMode & AND_PRINT_ATEVENT)
	{
		szEvent = m_szEvent;
		return TRUE;
	}
	return FALSE;
}

BOOL CANDPrintJobInfo::SetPrintCount(UINT nCount)
{
	if (m_nPrintMode & AND_PRINT_ATTIME)
	{
		m_nPrintCount[0] = nCount;
		return TRUE;
	}
	return FALSE;
}

BOOL CANDPrintJobInfo::GetPrintCount(UINT &nCount) CONST
{
	if (m_nPrintMode & AND_PRINT_ATTIME)
	{
		nCount = m_nPrintCount[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CANDPrintJobInfo::SetPrintDailyCount(UINT nCount)
{
	if (m_nPrintMode & AND_PRINT_ATDAILYTIME)
	{
		m_nPrintCount[1] = nCount;
		return TRUE;
	}
	return FALSE;
}

BOOL CANDPrintJobInfo::GetPrintDailyCount(UINT &nCount) CONST
{
	if (m_nPrintMode & AND_PRINT_ATDAILYTIME)
	{
		nCount = m_nPrintCount[1];
		return TRUE;
	}
	return FALSE;
}

BOOL CANDPrintJobInfo::SetPrintLastTime(CONST CTimeKey &tTime)
{
	if (m_nPrintMode & AND_PRINT_ATTIME)
	{
		m_tPrintLastTime[0] = tTime;
		return TRUE;
	}
	return FALSE;
}

BOOL CANDPrintJobInfo::GetPrintLastTime(CTimeKey &tTime) CONST
{
	if (m_nPrintMode & AND_PRINT_ATTIME)
	{
		tTime = m_tPrintLastTime[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CANDPrintJobInfo::SetPrintLastDailyTime(CONST CTimeKey &tTime)
{
	if (m_nPrintMode & AND_PRINT_ATDAILYTIME)
	{
		m_tPrintLastTime[1] = tTime;
		return TRUE;
	}
	return FALSE;
}

BOOL CANDPrintJobInfo::GetPrintLastDailyTime(CTimeKey &tTime) CONST
{
	if (m_nPrintMode & AND_PRINT_ATDAILYTIME)
	{
		tTime = m_tPrintLastTime[1];
		return TRUE;
	}
	return FALSE;
}

VOID CANDPrintJobInfo::Copy(CONST CANDPrintJobInfo *pJobInfo)
{
	m_szName = pJobInfo->m_szName;
	m_szEvent = pJobInfo->m_szEvent;
	m_szProfile = pJobInfo->m_szProfile;
	m_szComments = pJobInfo->m_szComments;
	m_nPrintMode = pJobInfo->m_nPrintMode;
	m_nPrintFlags = pJobInfo->m_nPrintFlags;
	m_nPrintColumns = pJobInfo->m_nPrintColumns;
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

BOOL CANDPrintJobInfo::Compare(CONST CANDPrintJobInfo *pJobInfo) CONST
{
	return((pJobInfo->m_szName == m_szName  &&  pJobInfo->m_szProfile == m_szProfile  &&  pJobInfo->m_szComments == m_szComments  &&  pJobInfo->m_nPrintMode == m_nPrintMode && ((!(m_nPrintMode & AND_PRINT_FIRSTSIDE) && !(m_nPrintMode & AND_PRINT_LASTSIDE)) || pJobInfo->m_nPrintByCount == m_nPrintByCount) && (!(m_nPrintMode & AND_PRINT_CUSTOMLAYOUT) || pJobInfo->m_nPrintColumns == m_nPrintColumns) && (!(m_nPrintMode & AND_PRINT_ATTIME) || pJobInfo->m_tPrintAtTime == m_tPrintAtTime) && (!(m_nPrintMode & AND_PRINT_ATDAILYTIME) || pJobInfo->m_tPrintAtDailyTime == m_tPrintAtDailyTime) && (!(m_nPrintMode & AND_PRINT_ATEVENT) || pJobInfo->m_szEvent == m_szEvent) && (!(m_nPrintMode & AND_PRINT_REPEATBYINTERVAL) || pJobInfo->m_tRepeatInterval == m_tRepeatInterval) && (!(m_nPrintMode & AND_PRINT_REPEATSTOPBYCOUNT) || pJobInfo->m_nRepeatStopByCount[0] == m_nRepeatStopByCount[0]) && (!(m_nPrintMode & AND_PRINT_REPEATSTOPBYTIME) || pJobInfo->m_tRepeatStopByTime[0] == m_tRepeatStopByTime[0]) && (!(m_nPrintMode & AND_PRINT_DAILYREPEATSTOPBYCOUNT) || pJobInfo->m_nRepeatStopByCount[1] == m_nRepeatStopByCount[1]) && (!(m_nPrintMode & AND_PRINT_DAILYREPEATSTOPBYTIME) || pJobInfo->m_tRepeatStopByTime[1] == m_tRepeatStopByTime[1])) ? TRUE : FALSE);
}

BOOL CANDPrintJobInfo::Map(CByteArray &nInfo) CONST
{
	INT  cbData;
	DATA  sData;

	sData.cbName = (m_szName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbEvent = (m_szEvent.GetLength() + 1)*sizeof(TCHAR);
	sData.cbProfile = (m_szProfile.GetLength() + 1)*sizeof(TCHAR);
	sData.cbComments = (m_szComments.GetLength() + 1)*sizeof(TCHAR);
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbName + sData.cbProfile + sData.cbComments + sData.cbEvent)), sData.nPrintMode = m_nPrintMode, sData.nPrintColumns = m_nPrintColumns, sData.nPrintCount[0] = m_nPrintCount[0], sData.nPrintCount[1] = m_nPrintCount[1], sData.nPrintByCount = m_nPrintByCount, sData.tPrintAtTime = m_tPrintAtTime.GetTime(), sData.tPrintAtDailyTime = m_tPrintAtDailyTime.GetTotalSeconds(), sData.tPrintLastTime[0] = m_tPrintLastTime[0].GetTime(), sData.tPrintLastTime[1] = m_tPrintLastTime[1].GetTime(), sData.tRepeatInterval = m_tRepeatInterval.GetTotalSeconds(), sData.nRepeatStopByCount[0] = m_nRepeatStopByCount[0], sData.nRepeatStopByCount[1] = m_nRepeatStopByCount[1], sData.tRepeatStopByTime[0] = m_tRepeatStopByTime[0].GetTime(), sData.tRepeatStopByTime[1] = m_tRepeatStopByTime[1].GetTime(); nInfo.GetSize() == sData.cbSize; )
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

BOOL CANDPrintJobInfo::Unmap(CONST CByteArray &nInfo)
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
		m_nPrintColumns = sData.nPrintColumns;
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
// CANDPrintJobs

CANDPrintJobs::CANDPrintJobs() : CPtrArray()
{
	return;
}

CANDPrintJobs::~CANDPrintJobs()
{
	RemoveAll();
}

INT CANDPrintJobs::Add(CANDPrintJobInfo *pJobInfo)
{
	return((INT)CPtrArray::Add(pJobInfo));
}

INT CANDPrintJobs::Find(LPCTSTR pszName) CONST
{
	INT  nJob;
	INT  nJobs;
	CANDPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (INT)GetSize(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = GetAt(nJob)) && pJobInfo->GetName() == pszName) break;
		continue;
	}
	return((nJob < nJobs) ? nJob : -1);
}

CANDPrintJobInfo *CANDPrintJobs::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CANDPrintJobInfo *)CPtrArray::GetAt(nIndex) : (CANDPrintJobInfo *)NULL);
}

CANDPrintJobInfo *CANDPrintJobs::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CANDPrintJobInfo *)CPtrArray::GetAt(nIndex) : (CANDPrintJobInfo *)NULL);
}

TIMEKEY CANDPrintJobs::Schedule()
{
	INT  nJob;
	INT  nJobs;
	UINT  nJobMode;
	UINT  nJobPrintCount[2];
	CTimeKey  tJobPrintTime[4];
	CTimeSpan  tJobPrintInterval;
	CTimeSpan  tJobPrintDailyTime;
	TIMEKEY  tJobPrintTimeout[2];
	CANDPrintJobInfo  *pJobInfo[2];

	for (nJob = 0, nJobs = (INT)GetSize(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo[0] = GetAt(nJob)) != (CANDPrintJobInfo *)NULL)
		{
			if (((nJobMode = pJobInfo[0]->GetPrintMode()) & AND_PRINT_ACTIVE) && (((nJobMode & AND_PRINT_ATTIME) && pJobInfo[0]->GetPrintLastTime(tJobPrintTime[1]) && (tJobPrintTime[1] > 0 || pJobInfo[0]->SetPrintLastTime(tJobPrintTime[3]))) || (nJobMode & AND_PRINT_ATDAILYTIME)) &&
				((pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0]) && pJobInfo[0]->GetPrintCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastTime(tJobPrintTime[1]) && tJobPrintTime[3] >= tJobPrintTime[0] && tJobPrintTime[0] > tJobPrintTime[1] && pJobInfo[0]->SetPrintFlags(AND_PRINT_ATTIME) && pJobInfo[0]->SetPrintCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0], tJobPrintInterval) && pJobInfo[0]->GetPrintCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastTime(tJobPrintTime[1]) && tJobPrintTime[3] >= tJobPrintTime[0] && (tJobPrintTime[0] > tJobPrintTime[1] || (tJobPrintTime[1].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds() < (tJobPrintTime[3].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds()) && pJobInfo[0]->SetPrintFlags(AND_PRINT_ATTIME) && pJobInfo[0]->SetPrintCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0], tJobPrintInterval, nJobPrintCount[1]) && pJobInfo[0]->GetPrintCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastTime(tJobPrintTime[1]) && tJobPrintTime[3] >= tJobPrintTime[0] && (tJobPrintTime[0] > tJobPrintTime[1] || (tJobPrintTime[1].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds() < (tJobPrintTime[3].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds()) && nJobPrintCount[0] < nJobPrintCount[1] && pJobInfo[0]->SetPrintFlags(AND_PRINT_ATTIME) && pJobInfo[0]->SetPrintCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0], tJobPrintInterval, tJobPrintTime[2]) && pJobInfo[0]->GetPrintCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastTime(tJobPrintTime[1]) && tJobPrintTime[3] >= tJobPrintTime[0] && (tJobPrintTime[0] > tJobPrintTime[1] || (tJobPrintTime[1].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds() < (tJobPrintTime[3].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds()) && tJobPrintTime[3] <= tJobPrintTime[2] && pJobInfo[0]->SetPrintFlags(AND_PRINT_ATTIME) && pJobInfo[0]->SetPrintCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtDailyTime(tJobPrintDailyTime) && pJobInfo[0]->GetPrintDailyCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastDailyTime(tJobPrintTime[1]) && tJobPrintTime[3].GetTime() % SECONDSPERDAY >= tJobPrintDailyTime.GetTotalSeconds() && tJobPrintTime[3].GetTime() / SECONDSPERDAY != tJobPrintTime[1].GetTime() / SECONDSPERDAY  &&  pJobInfo[0]->SetPrintFlags(AND_PRINT_ATDAILYTIME) && pJobInfo[0]->SetPrintDailyCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastDailyTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtDailyTime(tJobPrintDailyTime, nJobPrintCount[1]) && pJobInfo[0]->GetPrintDailyCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastDailyTime(tJobPrintTime[1]) && tJobPrintTime[3].GetTime() % SECONDSPERDAY >= tJobPrintDailyTime.GetTotalSeconds() && tJobPrintTime[3].GetTime() / SECONDSPERDAY != tJobPrintTime[1].GetTime() / SECONDSPERDAY  &&  nJobPrintCount[0] < nJobPrintCount[1] && pJobInfo[0]->SetPrintFlags(AND_PRINT_ATDAILYTIME) && pJobInfo[0]->SetPrintDailyCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastDailyTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtDailyTime(tJobPrintDailyTime, tJobPrintTime[2]) && pJobInfo[0]->GetPrintDailyCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastDailyTime(tJobPrintTime[1]) && tJobPrintTime[3].GetTime() % SECONDSPERDAY >= tJobPrintDailyTime.GetTotalSeconds() && tJobPrintTime[3].GetTime() / SECONDSPERDAY != tJobPrintTime[1].GetTime() / SECONDSPERDAY  &&  tJobPrintTime[3] <= tJobPrintTime[2] && pJobInfo[0]->SetPrintFlags(AND_PRINT_ATDAILYTIME) && pJobInfo[0]->SetPrintDailyCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastDailyTime(tJobPrintTime[3]))))
			{
				if ((pJobInfo[1] = new CANDPrintJobInfo))
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

VOID CANDPrintJobs::RemoveAll()
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

BOOL CANDPrintJobs::Copy(CONST CANDPrintJobs *pPrintJobs)
{
	INT  nJob;
	INT  nJobs;
	CANDPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (INT)pPrintJobs->GetSize(), RemoveAll(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = new CANDPrintJobInfo) != (CANDPrintJobInfo *)NULL)
		{
			pJobInfo->Copy(pPrintJobs->GetAt(nJob));
			InsertAt(nJob, pJobInfo, 1);
			continue;
		}
		break;
	}
	return((nJob == nJobs) ? TRUE : FALSE);
}

BOOL CANDPrintJobs::Compare(CONST CANDPrintJobs *pPrintJobs) CONST
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

BOOL CANDPrintJobs::Map(CByteArray &nInfo) CONST
{
	INT  nJob;
	INT  nJobs;
	CByteArray  nJobData;
	CANDPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (INT)GetSize(), nInfo.RemoveAll(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = GetAt(nJob)) && pJobInfo->Map(nJobData) && nInfo.Append(nJobData) >= 0) continue;
		break;
	}
	return((nJob == nJobs) ? TRUE : FALSE);
}

BOOL CANDPrintJobs::Unmap(CONST CByteArray &nInfo)
{
	INT  cbJob;
	INT  cbJobs;
	CByteArray  nJobData;
	CANDPrintJobInfo  *pJobInfo;

	for (cbJobs = 0, RemoveAll(); cbJobs < nInfo.GetSize(); cbJobs += cbJob)
	{
		for (CopyMemory(&cbJob, nInfo.GetData() + cbJobs, sizeof(cbJob)), nJobData.SetSize(max(min(cbJob, nInfo.GetSize() - cbJobs), 0)); nJobData.GetSize() >= 0; )
		{
			CopyMemory(nJobData.GetData(), nInfo.GetData() + cbJobs, nJobData.GetSize());
			break;
		}
		if ((pJobInfo = new CANDPrintJobInfo))
		{
			if (pJobInfo->Unmap(nJobData) && Add(pJobInfo) >= 0) continue;
			delete pJobInfo;
		}
		break;
	}
	if ((pJobInfo = (!GetSize()) ? new CANDPrintJobInfo : (CANDPrintJobInfo *)NULL))
	{
		for (pJobInfo->SetName(STRING(IDS_PRINTJOB_DEFAULTNAME)), pJobInfo->SetProfile(STRING(IDS_PRINTPROFILE_DEFAULTNAME)), pJobInfo->SetPrintMode(AND_PRINT_ALL); Add(pJobInfo) >= 0; ) return TRUE;
		delete pJobInfo;
		return FALSE;
	}
	return((cbJobs == nInfo.GetSize()) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CANDSettingsLayoutPage property page

IMPLEMENT_DYNCREATE(CANDSettingsLayoutPage, CLocalePropertyPage)

CANDSettingsLayoutPage::CANDSettingsLayoutPage() : CLocalePropertyPage(CANDSettingsLayoutPage::IDD)
{
	//{{AFX_DATA_INIT(CANDSettingsLayoutPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CANDSettingsLayoutPage::Initialize()
{
	CANDLayout  cLayout;
	CANDOpenDialog  *pDialog;

	if (((pDialog = GetParentDialog()->GetParentDialog()) && (pDialog->GetLayout(cLayout, m_nColumns[0]) || GetParentDisplay()->GetLayout(cLayout, m_nColumns[0])) && (pDialog->GetLayoutTitleFont(&m_fntTitle[0]) || GetParentDisplay()->GetTitleFont(&m_fntTitle[0])) && (pDialog->GetLayoutLabelsFont(&m_fntLabels[0]) || GetParentDisplay()->GetLabelsFont(&m_fntLabels[0])) && (pDialog->GetLayoutItemsFont(&m_fntItems[0]) || GetParentDisplay()->GetItemsFont(&m_fntItems[0])) && (pDialog->GetLayoutValuesFont(&m_fntValues[0]) || GetParentDisplay()->GetValuesFont(&m_fntValues[0]))) || (GetParentDisplay()->GetLayout(cLayout, m_nColumns[0]) && GetParentDisplay()->GetTitleFont(&m_fntTitle[0]) && GetParentDisplay()->GetLabelsFont(&m_fntLabels[0]) && GetParentDisplay()->GetItemsFont(&m_fntItems[0]) && GetParentDisplay()->GetValuesFont(&m_fntValues[0])))
	{
		m_bInvalidData[1] = m_bInvalidData[0] = (!pDialog || !pDialog->GetLayoutInvalidDataMode(m_bInvalidData[0])) ? GetParentDisplay()->IsInvalidDataModeEnabled() : m_bInvalidData[0];
		m_bBadData[1] = m_bBadData[0] = (!pDialog || !pDialog->GetLayoutBadDataMode(m_bBadData[0])) ? GetParentDisplay()->IsBadDataModeEnabled() : m_bBadData[0];
		m_bToolTips[1] = m_bToolTips[0] = (!pDialog || !pDialog->GetLayoutToolTipMode(m_bToolTips[0])) ? GetParentDisplay()->IsToolTipModeEnabled() : m_bToolTips[0];
		CopyMemory(&m_fntTitle[1], &m_fntTitle[0], sizeof(LOGFONT));
		CopyMemory(&m_fntItems[1], &m_fntItems[0], sizeof(LOGFONT));
		CopyMemory(&m_fntLabels[1], &m_fntLabels[0], sizeof(LOGFONT));
		CopyMemory(&m_fntValues[1], &m_fntValues[0], sizeof(LOGFONT));
		m_nColumns[1].Copy(m_nColumns[0]);
		return TRUE;
	}
	return FALSE;
}

BOOL CANDSettingsLayoutPage::GetLayout(CUIntArray &nColumns) CONST
{
	nColumns.Copy(m_nColumns[0]);
	return((nColumns.GetSize() > 0) ? Check(FALSE) : FALSE);
}

BOOL CANDSettingsLayoutPage::GetTitleFont(LPLOGFONT pTitleFont) CONST
{
	CopyMemory(pTitleFont, &m_fntTitle[0], sizeof(LOGFONT));
	return Check(FALSE);
}

BOOL CANDSettingsLayoutPage::GetLabelsFont(LPLOGFONT pLabelsFont) CONST
{
	CopyMemory(pLabelsFont, &m_fntLabels[0], sizeof(LOGFONT));
	return Check(FALSE);
}

BOOL CANDSettingsLayoutPage::GetItemsFont(LPLOGFONT pItemsFont) CONST
{
	CopyMemory(pItemsFont, &m_fntItems[0], sizeof(LOGFONT));
	return Check(FALSE);
}

BOOL CANDSettingsLayoutPage::GetValuesFont(LPLOGFONT pValuesFont) CONST
{
	CopyMemory(pValuesFont, &m_fntValues[0], sizeof(LOGFONT));
	return Check(FALSE);
}

BOOL CANDSettingsLayoutPage::GetInvalidDataMode(BOOL &bEnable) CONST
{
	bEnable = m_bInvalidData[0];
	return Check(FALSE);
}

BOOL CANDSettingsLayoutPage::GetBadDataMode(BOOL &bEnable) CONST
{
	bEnable = m_bBadData[0];
	return Check(FALSE);
}

BOOL CANDSettingsLayoutPage::GetToolTipMode(BOOL &bEnable) CONST
{
	bEnable = m_bToolTips[0];
	return Check(FALSE);
}

CANDSettingsDialog *CANDSettingsLayoutPage::GetParentDialog() CONST
{
	return((CANDSettingsDialog *)CLocalePropertyPage::GetParent());
}

CANDWnd *CANDSettingsLayoutPage::GetParentDisplay() CONST
{
	return((CANDWnd *)GetParentDialog()->GetParentDisplay());
}

BOOL CANDSettingsLayoutPage::EnumLayoutColumns()
{
	INT  nColumn;
	INT  nColumns;
	CStringArray  szColumns;

	szColumns.Add(LookupColumnName(AND_TITLEITEM_ID));
	szColumns.Add(LookupColumnName(AND_TITLEITEM_DESCRIPTION));
	szColumns.Add(LookupColumnName(AND_TITLEITEM_VALUE));
	szColumns.Add(LookupColumnName(AND_TITLEITEM_UNIT));
	szColumns.Add(LookupColumnName(AND_TITLEITEM_CHANGETMUNIT));
	szColumns.Add(LookupColumnName(AND_TITLEITEM_CHANGETIME));
	szColumns.Add(LookupColumnName(AND_TITLEITEM_UPDATETMUNIT));
	szColumns.Add(LookupColumnName(AND_TITLEITEM_UPDATETIME));
	szColumns.Add(LookupColumnName(AND_TITLEITEM_EXPECTEDVALUES));
	for (nColumn = 0, nColumns = (INT)szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_NAME, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szColumns.GetAt(nColumn));
		continue;
	}
	SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_NAME, CB_SETCURSEL);
	return((nColumn == nColumns) ? TRUE : FALSE);
}

BOOL CANDSettingsLayoutPage::ShowLayoutColumns()
{
	INT  nColumn;
	INT  nColumns;

	for (nColumn = 0, nColumns = (INT)m_nColumns[0].GetSize(), SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_VIEW, LVM_DELETEALLITEMS), m_nColumnIndex = 0; nColumn < nColumns; nColumn++)
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
		if ((!nColumn  &&  !Listview_InsertText(GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_VIEW), 0, EMPTYSTRING)) || (nColumn > 0 && !Listview_SetText(GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_VIEW), 0, nColumn, EMPTYSTRING))) break;
		continue;
	}
	return((nColumn == nColumns) ? SetCurLayoutColumn() : FALSE);
}

VOID CANDSettingsLayoutPage::ShowLayoutFontDetails()
{
	INT  nSize;
	INT  nSizes;
	INT  nStyle;
	INT  nStyles;
	BOOL  bUnderlined;
	CStringArray  szSizes;
	CStringArray  szStyles;
	CFontTools  cFontTools;

	for (SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_RESETCONTENT), SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_RESETCONTENT), SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)((IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE)) ? m_fntTitle[0].lfFaceName : ((IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_LABELS)) ? m_fntLabels[0].lfFaceName : ((IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_PARAMETERS)) ? m_fntItems[0].lfFaceName : m_fntValues[0].lfFaceName))))); (IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE) && cFontTools.EnumerateFont(m_fntTitle[0].lfFaceName, szStyles, szSizes, bUnderlined)) || (IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_LABELS) && cFontTools.EnumerateFont(m_fntLabels[0].lfFaceName, szStyles, szSizes, bUnderlined)) || (IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_PARAMETERS) && cFontTools.EnumerateFont(m_fntItems[0].lfFaceName, szStyles, szSizes, bUnderlined)) || (IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_VALUES) && cFontTools.EnumerateFont(m_fntValues[0].lfFaceName, szStyles, szSizes, bUnderlined)); )
	{
		for (nStyle = 0, nStyles = (INT)szStyles.GetSize(); nStyle < nStyles; nStyle++) SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szStyles.GetAt(nStyle));
		for (nSize = 0, nSizes = (INT)szSizes.GetSize(); nSize < nSizes; nSize++) SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szSizes.GetAt(nSize));
		break;
	}
	if (IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_fntTitle[0])), 0));
		SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntTitle[0])), max(SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntTitle[1])), 0)));
		CheckDlgButton(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_UNDERLINED, FALSE);
	}
	if (IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_LABELS))
	{
		SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_fntLabels[0])), 0));
		SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntLabels[0])), max(SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntLabels[1])), 0)));
		CheckDlgButton(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_UNDERLINED, (m_fntLabels[0].lfUnderline) ? TRUE : FALSE);
	}
	if (IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_PARAMETERS))
	{
		SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_fntItems[0])), 0));
		SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntItems[0])), max(SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntItems[1])), 0)));
		CheckDlgButton(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_UNDERLINED, FALSE);
	}
	if (IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_VALUES))
	{
		SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_fntValues[0])), 0));
		SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntValues[0])), max(SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntValues[1])), 0)));
		CheckDlgButton(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_UNDERLINED, FALSE);
	}
	GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_STYLE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_STYLE)->EnableWindow((SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SIZE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SIZE)->EnableWindow((SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_UNDERLINED)->EnableWindow((SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_LABELS) : FALSE);
	GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SAMPLE)->EnableWindow((SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->EnableWindow((SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CANDSettingsLayoutPage::ShowLayoutFontSample()
{
	CRect  rSampleText;

	GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->GetWindowRect(rSampleText);
	ScreenToClient(rSampleText);
	InvalidateRect(rSampleText);
	UpdateWindow();
}

BOOL CANDSettingsLayoutPage::InsertLayoutColumn(INT nIndex, LPCTSTR pszColumn)
{
	m_szColumns.InsertAt(nIndex, pszColumn);
	m_nColumnIndex = (nIndex <= m_nColumnIndex) ? min(m_nColumnIndex + 1, (INT)(m_szColumns.GetSize() - 1)) : m_nColumnIndex;
	return Listview_InsertColumn(GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_VIEW), nIndex, m_szColumns.GetAt(nIndex), CalcColumnWidth(pszColumn));
}

BOOL CANDSettingsLayoutPage::ModifyLayoutColumn(INT nIndex, LPCTSTR pszColumn)
{
	m_szColumns.SetAt(nIndex, pszColumn);
	return Listview_SetColumn(GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_VIEW), nIndex, m_szColumns.GetAt(nIndex), CalcColumnWidth(pszColumn));
}

BOOL CANDSettingsLayoutPage::RemoveLayoutColumn(INT nIndex)
{
	if (Listview_DeleteColumn(GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_VIEW), nIndex))
	{
		m_nColumnIndex = (nIndex >= m_nColumnIndex) ? ((nIndex > m_nColumnIndex) ? m_nColumnIndex : 0) : max(m_nColumnIndex - 1, 0);
		m_szColumns.RemoveAt(nIndex);
		return SetCurLayoutColumn(m_nColumnIndex);
	}
	return FALSE;
}

BOOL CANDSettingsLayoutPage::SetCurLayoutColumn(INT nIndex)
{
	if (nIndex < m_nColumns[0].GetSize())
	{
		m_szColumns.SetAt(m_nColumnIndex, (m_szColumns.GetAt(m_nColumnIndex).Right(lstrlen(STRING(IDS_ANDSETTINGS_LAYOUTPAGE_COLUMNMARKER))) == STRING(IDS_ANDSETTINGS_LAYOUTPAGE_COLUMNMARKER)) ? (m_szColumns.GetAt(m_nColumnIndex).Left(m_szColumns.GetAt(m_nColumnIndex).GetLength() - lstrlen(STRING(IDS_ANDSETTINGS_LAYOUTPAGE_COLUMNMARKER)))) : m_szColumns.GetAt(m_nColumnIndex));
		m_szColumns.SetAt(nIndex, m_szColumns.GetAt(nIndex) + STRING(IDS_ANDSETTINGS_LAYOUTPAGE_COLUMNMARKER));
		Listview_SetColumn(GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_VIEW), m_nColumnIndex, m_szColumns.GetAt(m_nColumnIndex), CalcColumnWidth(m_szColumns.GetAt(m_nColumnIndex)));
		Listview_SetColumn(GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_VIEW), nIndex, m_szColumns.GetAt(nIndex), CalcColumnWidth(m_szColumns.GetAt((m_nColumnIndex = nIndex))));
		GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_INSERTBEFORE)->EnableWindow((m_nColumnIndex > 0) ? CheckLayoutColumn() : FALSE);
		GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_INSERTAFTER)->EnableWindow((m_nColumnIndex >= 0) ? CheckLayoutColumn() : FALSE);
		GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_REMOVE)->EnableWindow((m_nColumnIndex > 0) ? TRUE : FALSE);
		return TRUE;
	}
	return FALSE;
}

INT CANDSettingsLayoutPage::GetCurLayoutColumn() CONST
{
	return m_nColumnIndex;
}

BOOL CANDSettingsLayoutPage::CheckLayoutColumn() CONST
{
	INT  nType;
	INT  nCols;
	INT  nColumn;
	INT  nColumns;
	INT  nParameter;
	INT  nParameters;
	CString  szColumn;
	CANDLayout  cLayout;
	CANDLayoutParameter  *pParameter;

	GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_NAME)->GetWindowText(szColumn);
	for (nColumn = (LookupColumnName(szColumn) != AND_TITLEITEM_ID) ? m_nColumnIndex : -1, nColumns = (INT)m_nColumns[0].GetSize(); nColumn >= 0 && nColumn < nColumns; nColumn++)
	{
		if (m_nColumns[0].GetAt(nColumn) == AND_TITLEITEM_ID  &&  nColumn != m_nColumnIndex)
		{
			nColumn = nColumns;
			break;
		}
		if (m_nColumns[0].GetAt(nColumn) == LookupColumnName(szColumn)) break;
	}
	for (nColumn = (nColumn == nColumns) ? m_nColumnIndex : nColumn; nColumn >= 0; nColumn--)
	{
		if (m_nColumns[0].GetAt(nColumn) == AND_TITLEITEM_ID)
		{
			nColumn = nColumns;
			break;
		}
		if (m_nColumns[0].GetAt(nColumn) == LookupColumnName(szColumn)) break;
	}
	if (nColumn == nColumns || nColumn < 0)
	{
		if (((nType = (GetParentDialog()->GetParentDialog()) ? GetParentDialog()->GetParentDialog()->GetType() : HIWORD(GetParentDisplay()->GetType())) == AND_TYPE_NORMAL || nType == AND_TYPE_GENERIC) && nColumn < 0)
		{
			for (nParameter = 0, nParameters = ((GetParentDialog()->GetParentDialog() && GetParentDialog()->GetParentDialog()->GetLayout(cLayout)) || GetParentDisplay()->GetLayout(cLayout)) ? (INT)cLayout.GetSize() : -1, nCols = 0; nParameter < nParameters; nParameter++)
			{
				if ((pParameter = cLayout.GetAt(nParameter)))
				{
					nCols = max(pParameter->GetColumn() + 1, nCols);
					continue;
				}
			}
			for (nColumn = 0, nColumns = (nParameters >= 0) ? (INT)m_nColumns[0].GetSize() : -1; nColumn < nColumns; nColumn++)
			{
				nCols = (m_nColumns[0].GetAt(nColumn) == AND_TITLEITEM_ID) ? (nCols - 1) : nCols;
				continue;
			}
			return((nColumns >= 0 && nCols > 0) ? TRUE : FALSE);
		}
		return TRUE;
	}
	return FALSE;
}

CString CANDSettingsLayoutPage::LookupColumnName(UINT nColumn) CONST
{
	if (nColumn == AND_TITLEITEM_ID) return STRING(IDS_AND_TITLEITEM_ID);
	if (nColumn == AND_TITLEITEM_DESCRIPTION) return STRING(IDS_AND_TITLEITEM_DESCRIPTION);
	if (nColumn == AND_TITLEITEM_VALUE) return STRING(IDS_AND_TITLEITEM_VALUE);
	if (nColumn == AND_TITLEITEM_UNIT) return STRING(IDS_AND_TITLEITEM_UNIT);
	if (nColumn == AND_TITLEITEM_CHANGETMUNIT) return STRING(IDS_AND_TITLEITEM_CHANGETMUNIT);
	if (nColumn == AND_TITLEITEM_CHANGETIME) return STRING(IDS_AND_TITLEITEM_CHANGETIME);
	if (nColumn == AND_TITLEITEM_UPDATETMUNIT) return STRING(IDS_AND_TITLEITEM_UPDATETMUNIT);
	if (nColumn == AND_TITLEITEM_UPDATETIME) return STRING(IDS_AND_TITLEITEM_UPDATETIME);
	if (nColumn == AND_TITLEITEM_EXPECTEDVALUES) return STRING(IDS_AND_TITLEITEM_EXPECTEDVALUES);
	return EMPTYSTRING;
}
UINT CANDSettingsLayoutPage::LookupColumnName(LPCTSTR pszColumn) CONST
{
	if (!_tcsncmp(pszColumn, STRING(IDS_AND_TITLEITEM_ID), lstrlen(STRING(IDS_AND_TITLEITEM_ID)))) return AND_TITLEITEM_ID;
	if (!_tcsncmp(pszColumn, STRING(IDS_AND_TITLEITEM_DESCRIPTION), lstrlen(STRING(IDS_AND_TITLEITEM_DESCRIPTION)))) return AND_TITLEITEM_DESCRIPTION;
	if (!_tcsncmp(pszColumn, STRING(IDS_AND_TITLEITEM_VALUE), lstrlen(STRING(IDS_AND_TITLEITEM_VALUE)))) return AND_TITLEITEM_VALUE;
	if (!_tcsncmp(pszColumn, STRING(IDS_AND_TITLEITEM_UNIT), lstrlen(STRING(IDS_AND_TITLEITEM_UNIT)))) return AND_TITLEITEM_UNIT;
	if (!_tcsncmp(pszColumn, STRING(IDS_AND_TITLEITEM_CHANGETMUNIT), lstrlen(STRING(IDS_AND_TITLEITEM_CHANGETMUNIT)))) return AND_TITLEITEM_CHANGETMUNIT;
	if (!_tcsncmp(pszColumn, STRING(IDS_AND_TITLEITEM_CHANGETIME), lstrlen(STRING(IDS_AND_TITLEITEM_CHANGETIME)))) return AND_TITLEITEM_CHANGETIME;
	if (!_tcsncmp(pszColumn, STRING(IDS_AND_TITLEITEM_UPDATETMUNIT), lstrlen(STRING(IDS_AND_TITLEITEM_UPDATETMUNIT)))) return AND_TITLEITEM_UPDATETMUNIT;
	if (!_tcsncmp(pszColumn, STRING(IDS_AND_TITLEITEM_UPDATETIME), lstrlen(STRING(IDS_AND_TITLEITEM_UPDATETIME)))) return AND_TITLEITEM_UPDATETIME;
	if (!_tcsncmp(pszColumn, STRING(IDS_AND_TITLEITEM_EXPECTEDVALUES), lstrlen(STRING(IDS_AND_TITLEITEM_EXPECTEDVALUES)))) return AND_TITLEITEM_EXPECTEDVALUES;
	return 0;
}

INT CANDSettingsLayoutPage::CalcColumnsWidth(CONST CUIntArray &nColumns, CUIntArray &nWidths)
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

INT CANDSettingsLayoutPage::CalcColumnWidth(LPCTSTR pszColumn)
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
				nWidth = ((nColumn = LookupColumnName(pszColumn)) == AND_TITLEITEM_ID) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetANDIDColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : 0;
				nWidth = (nColumn == AND_TITLEITEM_DESCRIPTION) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetANDDescriptionColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == AND_TITLEITEM_VALUE) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetANDValueColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == AND_TITLEITEM_UNIT) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetANDUnitColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == AND_TITLEITEM_CHANGETMUNIT) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetANDChangeTMUnitColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == AND_TITLEITEM_UPDATETMUNIT) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetANDUpdateTMUnitColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == AND_TITLEITEM_CHANGETIME) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetANDChangeTimeColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == AND_TITLEITEM_UPDATETIME) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetANDUpdateTimeColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == AND_TITLEITEM_EXPECTEDVALUES) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetANDExpectedValuesColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
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

INT CANDSettingsLayoutPage::CalcColumnIndent() CONST
{
	return 3 * GetSystemMetrics(SM_CXEDGE);
}

BOOL CANDSettingsLayoutPage::IsModified(BOOL bAll) CONST
{
	INT  nColumn;
	INT  nColumns;
	CFontTools  cFontTools;

	if (IsWindow(GetSafeHwnd()) && !bAll)
	{
		for (nColumn = 0, nColumns = (m_nColumns[0].GetSize() == m_nColumns[1].GetSize() && !lstrcmp(m_fntTitle[0].lfFaceName, m_fntTitle[1].lfFaceName) && (m_fntTitle[0].lfHeight == m_fntTitle[1].lfHeight || cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntTitle[0])) == cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntTitle[1]))) && m_fntTitle[0].lfWeight == m_fntTitle[1].lfWeight && m_fntTitle[0].lfItalic == m_fntTitle[1].lfItalic && !lstrcmp(m_fntLabels[0].lfFaceName, m_fntLabels[1].lfFaceName) && (m_fntLabels[0].lfHeight == m_fntLabels[1].lfHeight || cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntLabels[0])) == cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntLabels[1]))) && m_fntLabels[0].lfWeight == m_fntLabels[1].lfWeight && m_fntLabels[0].lfItalic == m_fntLabels[1].lfItalic && m_fntLabels[0].lfUnderline == m_fntLabels[1].lfUnderline && !lstrcmp(m_fntItems[0].lfFaceName, m_fntItems[1].lfFaceName) && (m_fntItems[0].lfHeight == m_fntItems[1].lfHeight || cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntItems[0])) == cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntItems[1]))) && m_fntItems[0].lfWeight == m_fntItems[1].lfWeight && m_fntItems[0].lfItalic == m_fntItems[1].lfItalic && !lstrcmp(m_fntValues[0].lfFaceName, m_fntValues[1].lfFaceName) && (m_fntValues[0].lfHeight == m_fntValues[1].lfHeight || cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntValues[0])) == cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntValues[1]))) && m_fntValues[0].lfWeight == m_fntValues[1].lfWeight && m_fntValues[0].lfItalic == m_fntValues[1].lfItalic && m_bInvalidData[0] == m_bInvalidData[1] && m_bBadData[0] == m_bBadData[1] && m_bToolTips[0] == m_bToolTips[1]) ? (INT)m_nColumns[0].GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			if (m_nColumns[0].GetAt(nColumn) != m_nColumns[1].GetAt(nColumn)) break;
			continue;
		}
		return((nColumn != nColumns) ? TRUE : FALSE);
	}
	return((bAll) ? CLocalePropertyPage::IsModified() : FALSE);
}

BOOL CANDSettingsLayoutPage::Check(BOOL bAll) CONST
{
	INT  nColumn[2];
	INT  nColumns[2];

	if (IsWindow(GetSafeHwnd()) && !bAll)
	{
		for (nColumn[0] = 0, nColumns[0] = (GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_NAMES)->GetWindowTextLength() > 0 && GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowTextLength() > 0 && GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowTextLength() > 0) ? (INT)m_nColumns[0].GetSize() : -1; nColumn[0] < nColumns[0]; nColumn[0]++)
		{
			for (nColumn[1] = nColumn[0] + 1, nColumns[1] = nColumns[0]; nColumn[1] < nColumns[1]; nColumn[1]++)
			{
				if (m_nColumns[0].GetAt(nColumn[1]) == AND_TITLEITEM_ID)
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

void CANDSettingsLayoutPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CANDSettingsLayoutPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CANDSettingsLayoutPage::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_nColumns[0].RemoveAll();
	m_nColumns[1].RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CANDSettingsLayoutPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CANDSettingsLayoutPage)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_INSERTBEFORE, OnInsertColumnBefore)
	ON_BN_CLICKED(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_INSERTAFTER, OnInsertColumnAfter)
	ON_BN_CLICKED(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_REMOVE, OnRemoveColumn)
	ON_BN_CLICKED(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_INVALIDDATA, OnInvalidData)
	ON_BN_CLICKED(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_BADDATA, OnBadData)
	ON_BN_CLICKED(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_TOOLTIPS, OnToolTips)
	ON_BN_CLICKED(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE, OnTitleFont)
	ON_BN_CLICKED(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_LABELS, OnLabelsFont)
	ON_BN_CLICKED(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_PARAMETERS, OnItemsFont)
	ON_BN_CLICKED(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_VALUES, OnValuesFont)
	ON_BN_CLICKED(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_UNDERLINED, OnUnderlineFont)
	ON_CBN_EDITCHANGE(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_NAMES, OnEditchangeFontName)
	ON_CBN_SELCHANGE(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_NAME, OnSelchangeColumnName)
	ON_CBN_SELCHANGE(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_NAMES, OnSelchangeFontName)
	ON_CBN_SELCHANGE(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_STYLE, OnSelchangeFontStyle)
	ON_CBN_SELCHANGE(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SIZE, OnSelchangeFontSize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDSettingsLayoutPage message handlers

BOOL CANDSettingsLayoutPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	CheckRadioButton(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE, IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_VALUES, IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE);
	CheckDlgButton(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_INVALIDDATA, m_bInvalidData[0]);
	CheckDlgButton(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_BADDATA, m_bBadData[0]);
	CheckDlgButton(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_TOOLTIPS, m_bToolTips[0]);
	GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->GetWindowText(m_szFontSampleText);
	GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT)->EnableWindow();
	GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_NAME)->EnableWindow();
	GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_VIEW)->EnableWindow();
	GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_SHOWDATA)->EnableWindow();
	GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_INVALIDDATA)->EnableWindow();
	GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_BADDATA)->EnableWindow();
	GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_TOOLTIPS)->EnableWindow();
	GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS)->EnableWindow();
	GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_STATIC)->EnableWindow();
	GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE)->EnableWindow();
	GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_LABELS)->EnableWindow();
	GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_PARAMETERS)->EnableWindow();
	GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_VALUES)->EnableWindow();
	GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_CHARACTERISTICS)->EnableWindow();
	GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_NAMES_STATIC)->EnableWindow();
	GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_NAMES)->EnableWindow();
	SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_NAMES, FCB_DIR, CF_EFFECTS | CF_SCREENFONTS);
	SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)m_fntTitle[0].lfFaceName));
	EnumLayoutColumns();
	ShowLayoutColumns();
	ShowLayoutFontDetails();
	return TRUE;
}

BOOL CANDSettingsLayoutPage::OnSetActive()
{
	ShowLayoutColumns();
	return CLocalePropertyPage::OnSetActive();
}

BOOL CANDSettingsLayoutPage::OnKillActive()
{
	GetParentDialog()->OnDataExchange(GetSafeHwnd(), m_nColumns[0]);
	return CLocalePropertyPage::OnKillActive();
}

BOOL CANDSettingsLayoutPage::OnDataExchange(CONST CUIntArray &nColumns)
{
	m_nColumns[0].Copy(nColumns);
	return TRUE;
}

void CANDSettingsLayoutPage::OnPaint()
{
	INT  nBkMode;
	CFont  cFont;
	CFont  *pOldFont;
	CRect  rSampleText;
	COLORREF  nOldColor;
	CPaintDC  cDC(this);

	for (GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->GetWindowRect(rSampleText), ScreenToClient(rSampleText); cFont.CreateFontIndirect((IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE)) ? &m_fntTitle[0] : ((IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_LABELS)) ? &m_fntLabels[0] : ((IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_PARAMETERS)) ? &m_fntItems[0] : &m_fntValues[0]))); )
	{
		if ((pOldFont = cDC.SelectObject(&cFont)))
		{
			nBkMode = cDC.SetBkMode(TRANSPARENT);
			nOldColor = cDC.SetTextColor((SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? GetSysColor(COLOR_WINDOWTEXT) : GetSysColor(COLOR_GRAYTEXT));
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

BOOL CANDSettingsLayoutPage::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_VIEW)
	{
		if (pNotifyListView->hdr.code == LVN_COLUMNCLICK) SetCurLayoutColumn(pNotifyListView->iSubItem);
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGING  &&  !(pNotifyListView->uChanged & LVIF_TEXT))
		{
			*pResult = TRUE;
			return TRUE;
		}
	}
	return CLocalePropertyPage::OnNotify(wParam, lParam, pResult);
}

void CANDSettingsLayoutPage::OnInsertColumnBefore()
{
	INT  nIndex;
	CString  szColumn;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_NAME)->GetWindowText(szColumn); InsertLayoutColumn((nIndex = m_nColumnIndex), szColumn); )
	{
		m_nColumns[0].InsertAt(nIndex, LookupColumnName(szColumn));
		SetCurLayoutColumn(nIndex);
		break;
	}
	GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsLayoutPage::OnInsertColumnAfter()
{
	INT  nIndex;
	CString  szColumn;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_NAME)->GetWindowText(szColumn); InsertLayoutColumn((nIndex = m_nColumnIndex + 1), szColumn); )
	{
		m_nColumns[0].InsertAt(nIndex, LookupColumnName(szColumn));
		SetCurLayoutColumn(nIndex);
		break;
	}
	GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsLayoutPage::OnRemoveColumn()
{
	INT  nIndex;
	CHourglassCursor  cCursor;

	if (RemoveLayoutColumn((nIndex = m_nColumnIndex)))
	{
		m_nColumns[0].RemoveAt(nIndex);
		SetCurLayoutColumn();
	}
	GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsLayoutPage::OnInvalidData()
{
	m_bInvalidData[0] = IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_INVALIDDATA);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsLayoutPage::OnBadData()
{
	m_bBadData[0] = IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_BADDATA);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsLayoutPage::OnToolTips()
{
	m_bToolTips[0] = IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_TOOLTIPS);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsLayoutPage::OnTitleFont()
{
	ShowLayoutFontDetails();
	ShowLayoutFontSample();
}

void CANDSettingsLayoutPage::OnLabelsFont()
{
	ShowLayoutFontDetails();
	ShowLayoutFontSample();
}

void CANDSettingsLayoutPage::OnItemsFont()
{
	ShowLayoutFontDetails();
	ShowLayoutFontSample();
}

void CANDSettingsLayoutPage::OnValuesFont()
{
	ShowLayoutFontDetails();
	ShowLayoutFontSample();
}

void CANDSettingsLayoutPage::OnUnderlineFont()
{
	if (IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		m_fntTitle[0].lfUnderline = IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_UNDERLINED);
		ShowLayoutFontSample();
	}
	if (IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_LABELS))
	{
		m_fntLabels[0].lfUnderline = IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_UNDERLINED);
		ShowLayoutFontSample();
	}
	if (IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_PARAMETERS))
	{
		m_fntItems[0].lfUnderline = IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_UNDERLINED);
		ShowLayoutFontSample();
	}
	if (IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_VALUES))
	{
		m_fntValues[0].lfUnderline = IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_UNDERLINED);
		ShowLayoutFontSample();
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsLayoutPage::OnEditchangeFontName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsLayoutPage::OnSelchangeColumnName()
{
	GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_INSERTBEFORE)->EnableWindow((m_nColumnIndex > 0) ? CheckLayoutColumn() : FALSE);
	GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_INSERTAFTER)->EnableWindow((m_nColumnIndex >= 0) ? CheckLayoutColumn() : FALSE);
	GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FORMAT_REMOVE)->EnableWindow((m_nColumnIndex > 0) ? TRUE : FALSE);
}

void CANDSettingsLayoutPage::OnSelchangeFontName()
{
	CString  szSize;
	CString  szStyle;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		_tcscpy_s(m_fntTitle[0].lfFaceName, sizeof(m_fntTitle[0].lfFaceName) / sizeof(TCHAR), Combobox_GetText(GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_NAMES), (INT)SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_GETCURSEL)));
		ShowLayoutFontDetails();
	}
	if (IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_LABELS))
	{
		_tcscpy_s(m_fntLabels[0].lfFaceName, sizeof(m_fntLabels[0].lfFaceName) / sizeof(TCHAR), Combobox_GetText(GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_NAMES), (INT)SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_GETCURSEL)));
		ShowLayoutFontDetails();
	}
	if (IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_PARAMETERS))
	{
		_tcscpy_s(m_fntItems[0].lfFaceName, sizeof(m_fntItems[0].lfFaceName) / sizeof(TCHAR), Combobox_GetText(GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_NAMES), (INT)SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_GETCURSEL)));
		ShowLayoutFontDetails();
	}
	if (IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_VALUES))
	{
		_tcscpy_s(m_fntValues[0].lfFaceName, sizeof(m_fntValues[0].lfFaceName) / sizeof(TCHAR), Combobox_GetText(GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_NAMES), (INT)SendDlgItemMessage(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_GETCURSEL)));
		ShowLayoutFontDetails();
	}
	if (IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntTitle[0].lfWeight, m_fntTitle[0].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_fntTitle[0].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_fntTitle[0]);
	}
	if (IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_LABELS))
	{
		GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntLabels[0].lfWeight, m_fntLabels[0].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_fntLabels[0].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_fntLabels[0]);
	}
	if (IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_PARAMETERS))
	{
		GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntItems[0].lfWeight, m_fntItems[0].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_fntItems[0].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_fntItems[0]);
	}
	if (IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_VALUES))
	{
		GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntValues[0].lfWeight, m_fntValues[0].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_fntValues[0].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_fntValues[0]);
	}
	ShowLayoutFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsLayoutPage::OnSelchangeFontStyle()
{
	CString  szStyle;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntTitle[0].lfWeight, m_fntTitle[0].lfItalic);
	}
	if (IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_LABELS))
	{
		GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntLabels[0].lfWeight, m_fntLabels[0].lfItalic);
	}
	if (IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_PARAMETERS))
	{
		GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntItems[0].lfWeight, m_fntItems[0].lfItalic);
	}
	if (IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_VALUES))
	{
		GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntValues[0].lfWeight, m_fntValues[0].lfItalic);
	}
	ShowLayoutFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsLayoutPage::OnSelchangeFontSize()
{
	CString  szSize;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_fntTitle[0].lfHeight);
	}
	if (IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_LABELS))
	{
		GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_fntLabels[0].lfHeight);
	}
	if (IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_PARAMETERS))
	{
		GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_fntItems[0].lfHeight);
	}
	if (IsDlgButtonChecked(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_VALUES))
	{
		GetDlgItem(IDC_ANDSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_fntValues[0].lfHeight);
	}
	ShowLayoutFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CANDSettingsDirectoryDialog dialog

IMPLEMENT_DYNCREATE(CANDSettingsDirectoryDialog, CDisplayDialog)

CANDSettingsDirectoryDialog::CANDSettingsDirectoryDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CANDSettingsDirectoryDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CANDSettingsDirectoryDialog::Create(CWnd *pParentWnd)
{
	return CDisplayDialog::Create(pParentWnd, CANDSettingsDirectoryDialog::IDD);
}

BOOL CANDSettingsDirectoryDialog::GetLayout(CANDLayout &cLayout) CONST
{
	return((!m_cLayout.GetName().IsEmpty()) ? cLayout.Copy(&m_cLayout) : FALSE);
}

CANDSettingsDialog *CANDSettingsDirectoryDialog::GetParentDialog() CONST
{
	return((CANDSettingsDialog *)CDisplayDialog::GetParent());
}

CANDWnd *CANDSettingsDirectoryDialog::GetParentDisplay() CONST
{
	return((CANDWnd *)CDisplayDialog::GetParentDisplay());
}

BOOL CANDSettingsDirectoryDialog::EnumDisplays()
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szDisplay;
	CANDLayouts  pDisplays;

	for (nDisplay = 0, nDisplays = (IsDlgButtonChecked(IDC_ANDSETTINGS_DIRECTORY_TYPE_NORMAL)) ? GetDatabase()->EnumANDs(pDisplays, DATABASE_SUBCOMPONENT_AND_NORMAL) : 0, SendDlgItemMessage(IDC_ANDSETTINGS_DIRECTORY_LIST, CB_RESETCONTENT); nDisplay < nDisplays; nDisplay++)
	{
		SendDlgItemMessage(IDC_ANDSETTINGS_DIRECTORY_LIST, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pDisplays.GetAt(nDisplay)->GetTitle());
		continue;
	}
	for (nDisplay = 0, nDisplays = (IsDlgButtonChecked(IDC_ANDSETTINGS_DIRECTORY_TYPE_GENERIC)) ? GetDatabase()->EnumANDs(pDisplays, DATABASE_SUBCOMPONENT_AND_GENERIC) : 0; nDisplay < nDisplays; nDisplay++)
	{
		szDisplay.Format(STRING(IDS_ANDDIRECTORYDIALOG_GENERICTITLE), (LPCTSTR)pDisplays.GetAt(nDisplay)->GetTitle(), (LPCTSTR)pDisplays.GetAt(nDisplay)->GetName());
		SendDlgItemMessage(IDC_ANDSETTINGS_DIRECTORY_LIST, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szDisplay);
	}
	for (nDisplay = 0, nDisplays = (IsDlgButtonChecked(IDC_ANDSETTINGS_DIRECTORY_TYPE_TEMPORARY)) ? EnumTemporaryANDs(pDisplays) : 0; nDisplay < nDisplays; nDisplay++)
	{
		SendDlgItemMessage(IDC_ANDSETTINGS_DIRECTORY_LIST, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pDisplays.GetAt(nDisplay)->GetTitle());
		continue;
	}
	GetDlgItem(IDC_ANDSETTINGS_DIRECTORY_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_ANDSETTINGS_DIRECTORY_LIST, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_ANDSETTINGS_DIRECTORY_LIST)->EnableWindow((SendDlgItemMessage(IDC_ANDSETTINGS_DIRECTORY_LIST, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_ANDSETTINGS_DIRECTORY_LIST, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CANDSettingsDirectoryDialog::Check(BOOL bModified) CONST
{
	CString  szDisplay;

	GetDlgItem(IDC_ANDSETTINGS_DIRECTORY_LIST)->GetWindowText(szDisplay);
	return((GetDlgItem(IDC_ANDSETTINGS_DIRECTORY_LIST)->SendMessage(CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szDisplay) >= 0) ? TRUE : FALSE);
}

void CANDSettingsDirectoryDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CANDSettingsDirectoryDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CANDSettingsDirectoryDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CANDSettingsDirectoryDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_ANDSETTINGS_DIRECTORY_TYPE_NORMAL, OnNormalANDs)
	ON_BN_CLICKED(IDC_ANDSETTINGS_DIRECTORY_TYPE_GENERIC, OnGenericANDs)
	ON_BN_CLICKED(IDC_ANDSETTINGS_DIRECTORY_TYPE_TEMPORARY, OnTemporaryANDs)
	ON_BN_CLICKED(IDC_ANDSETTINGS_DIRECTORY_HELP, OnHelp)
	ON_CBN_EDITCHANGE(IDC_ANDSETTINGS_DIRECTORY_LIST, OnEditchangeAND)
	ON_CBN_SELCHANGE(IDC_ANDSETTINGS_DIRECTORY_LIST, OnSelchangeAND)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDSettingsDirectoryDialog message handlers

BOOL CANDSettingsDirectoryDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	CheckDlgButton(IDC_ANDSETTINGS_DIRECTORY_TYPE_NORMAL, TRUE);
	CheckDlgButton(IDC_ANDSETTINGS_DIRECTORY_TYPE_GENERIC, FALSE);
	GetDlgItem(IDC_ANDSETTINGS_DIRECTORY_DETAILS)->EnableWindow();
	GetDlgItem(IDC_ANDSETTINGS_DIRECTORY_TYPE)->EnableWindow();
	GetDlgItem(IDC_ANDSETTINGS_DIRECTORY_TYPE_NORMAL)->EnableWindow();
	GetDlgItem(IDC_ANDSETTINGS_DIRECTORY_TYPE_GENERIC)->EnableWindow();
	GetDlgItem(IDC_ANDSETTINGS_DIRECTORY_TYPE_TEMPORARY)->EnableWindow();
	EnumDisplays();
	return TRUE;
}

void CANDSettingsDirectoryDialog::OnNormalANDs()
{
	EnumDisplays();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsDirectoryDialog::OnGenericANDs()
{
	EnumDisplays();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsDirectoryDialog::OnTemporaryANDs()
{
	EnumDisplays();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsDirectoryDialog::OnEditchangeAND()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsDirectoryDialog::OnSelchangeAND()
{
	SendDlgItemMessage(IDC_ANDSETTINGS_DIRECTORY_LIST, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_ANDSETTINGS_DIRECTORY_LIST, CB_GETCURSEL));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsDirectoryDialog::OnOK()
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szDisplay[3];
	CANDLayouts  pDisplays;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_ANDSETTINGS_DIRECTORY_LIST)->GetWindowText(szDisplay[0]);
	for (nDisplay = 0, nDisplays = (IsDlgButtonChecked(IDC_ANDSETTINGS_DIRECTORY_TYPE_NORMAL)) ? GetDatabase()->EnumANDs(pDisplays, DATABASE_SUBCOMPONENT_AND_NORMAL) : 0; nDisplay < nDisplays; nDisplay++)
	{
		if (pDisplays.GetAt(nDisplay)->GetTitle() == szDisplay[0])
		{
			szDisplay[2] = pDisplays.GetAt(nDisplay)->GetName();
			break;
		}
	}
	for (nDisplay = 0, nDisplays = (IsDlgButtonChecked(IDC_ANDSETTINGS_DIRECTORY_TYPE_GENERIC)) ? GetDatabase()->EnumANDs(pDisplays, DATABASE_SUBCOMPONENT_AND_GENERIC) : 0; nDisplay < nDisplays; nDisplay++)
	{
		szDisplay[1].Format(STRING(IDS_ANDDIRECTORYDIALOG_GENERICTITLE), (LPCTSTR)pDisplays.GetAt(nDisplay)->GetTitle(), (LPCTSTR)pDisplays.GetAt(nDisplay)->GetName());
		szDisplay[2] = (szDisplay[0] == szDisplay[1]) ? pDisplays.GetAt(nDisplay)->GetName() : szDisplay[0];
		if (szDisplay[2] == pDisplays.GetAt(nDisplay)->GetName()) break;
	}
	for (nDisplay = 0, nDisplays = (IsDlgButtonChecked(IDC_ANDSETTINGS_DIRECTORY_TYPE_TEMPORARY)) ? EnumTemporaryANDs(pDisplays) : 0; nDisplay < nDisplays; nDisplay++)
	{
		if (pDisplays.GetAt(nDisplay)->GetTitle() == szDisplay[0])
		{
			szDisplay[2] = pDisplays.GetAt(nDisplay)->GetName();
			break;
		}
	}
	if ((IsDlgButtonChecked(IDC_ANDSETTINGS_DIRECTORY_TYPE_NORMAL) && !GetDatabase()->LoadAND(szDisplay[2], m_cLayout, DATABASE_SUBCOMPONENT_AND_NORMAL)) || (IsDlgButtonChecked(IDC_ANDSETTINGS_DIRECTORY_TYPE_GENERIC) && !GetDatabase()->LoadAND(szDisplay[2], m_cLayout, DATABASE_SUBCOMPONENT_AND_GENERIC)) || (IsDlgButtonChecked(IDC_ANDSETTINGS_DIRECTORY_TYPE_TEMPORARY) && !LoadTemporaryAND(szDisplay[2], m_cLayout)))
	{
		m_cLayout.SetName(EMPTYSTRING);
		m_cLayout.RemoveAll();
	}
	CDisplayDialog::OnOK();
}

BOOL CANDSettingsDirectoryDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_ANDSETTINGSDIRECTORYDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CANDSettingsDirectoryDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_ANDSETTINGSDIRECTORYDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CANDSettingsContentsPage property page

IMPLEMENT_DYNCREATE(CANDSettingsContentsPage, CLocalePropertyPage)

CANDSettingsContentsPage::CANDSettingsContentsPage() : CLocalePropertyPage(CANDSettingsContentsPage::IDD)
{
	//{{AFX_DATA_INIT(CANDSettingsContentsPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CANDSettingsContentsPage::Initialize()
{
	CANDOpenDialog  *pDialog;

	if (((pDialog = GetParentDialog()->GetParentDialog()) && (pDialog->GetLayout(m_cLayout[0], m_nLayoutColumns) || GetParentDisplay()->GetLayout(m_cLayout[0], m_nLayoutColumns)) && (pDialog->GetLayoutColors(m_nColors[0]) || GetParentDisplay()->GetOolColors(m_nColors[0]))) || (GetParentDisplay()->GetLayout(m_cLayout[0], m_nLayoutColumns) && GetParentDisplay()->GetOolColors(m_nColors[0])))
	{
		m_cLayout[1].Copy(&m_cLayout[0]);
		m_nColors[1].Copy(m_nColors[0]);
		m_ptLayout.x = 0;
		m_ptLayout.y = 0;
		return TRUE;
	}
	return FALSE;
}

BOOL CANDSettingsContentsPage::GetLayout(CANDLayout &cLayout) CONST
{
	return((cLayout.Copy(&m_cLayout[0])) ? Check(FALSE) : FALSE);
}
BOOL CANDSettingsContentsPage::GetLayout(CANDLayout &cLayout, CUIntArray &nColumns) CONST
{
	if (GetLayout(cLayout))
	{
		nColumns.Copy(m_nLayoutColumns);
		return TRUE;
	}
	return FALSE;
}

BOOL CANDSettingsContentsPage::GetColors(CUIntArray &nColors) CONST
{
	nColors.Copy(m_nColors[0]);
	return((nColors.GetSize() > 0) ? Check(FALSE) : FALSE);
}

CANDSettingsDialog *CANDSettingsContentsPage::GetParentDialog() CONST
{
	return((CANDSettingsDialog *)CLocalePropertyPage::GetParent());
}

CANDWnd *CANDSettingsContentsPage::GetParentDisplay() CONST
{
	return((CANDWnd *)GetParentDialog()->GetParentDisplay());
}

BOOL CANDSettingsContentsPage::EnumParameters()
{
	INT  nParameter;
	INT  nParameters;
	CString  szParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	for (nParameter = 0, nParameters = (INT)GetDatabase()->GetTMParameters()->GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(nParameter)) != (CDatabaseTMParameter *)NULL)
		{
			szParameter.Format(STRING(IDS_ANDSETTINGS_CONTENTSPAGE_PARAMETERFORMAT), (LPCTSTR)pDatabaseTMParameter->GetTag(), (LPCTSTR)pDatabaseTMParameter->GetDescription());
			if (SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szParameter) >= 0) continue;
		}
		break;
	}
	return((nParameter == nParameters  &&  nParameters > 0) ? TRUE : FALSE);
}

BOOL CANDSettingsContentsPage::EnumOOLs()
{
	return((SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_OOLCOLORS_TEXT, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_ANDSETTINGS_CONTENTSPAGE_NOOOL)) >= 0 && SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_OOLCOLORS_TEXT, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_ANDSETTINGS_CONTENTSPAGE_SOFTOOL)) >= 0 && SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_OOLCOLORS_TEXT, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_ANDSETTINGS_CONTENTSPAGE_HARDOOL)) >= 0 && SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_OOLCOLORS_TEXT, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_ANDSETTINGS_CONTENTSPAGE_DELTAOOL)) >= 0 && SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_OOLCOLORS_TEXT, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_ANDSETTINGS_CONTENTSPAGE_CONSISTENCYOOL)) >= 0 && SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_OOLCOLORS_TEXT, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_OOLCOLORS_TEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_ANDSETTINGS_CONTENTSPAGE_NOOOL))) >= 0 && SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_OOLCOLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nColors[0].GetAt(max(min(SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_OOLCOLORS_TEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_ANDSETTINGS_CONTENTSPAGE_NOOOL)), m_nColors[0].GetSize() - 1), 0))) >= 0) ? TRUE : FALSE);
}

BOOL CANDSettingsContentsPage::EnumTopics()
{
	return((SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_ANDSETTINGS_CONTENTSPAGE_TOPICS_COMMENTS)) >= 0 && SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_ANDSETTINGS_CONTENTSPAGE_TOPICS_EXPECTEDVALUES)) >= 0 && SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_ANDSETTINGS_CONTENTSPAGE_TOPICS_COMMENTS)), 0)) >= 0) ? TRUE : FALSE);
}

VOID CANDSettingsContentsPage::ShowContents()
{
	INT  nRow;
	INT  nRows;
	INT  nIndex;
	INT  nCount;
	INT  nParameter;
	INT  nParameters;
	INT  nColumnGroup;
	CANDLayoutParameter  *pParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	for (nIndex = 0, nCount = (INT)m_nLayoutColumns.GetSize(), nColumnGroup = 0; nIndex < nCount; nIndex++)
	{
		nColumnGroup = (m_nLayoutColumns.GetAt(nIndex) == AND_TITLEITEM_ID) ? (nColumnGroup + 1) : nColumnGroup;
		continue;
	}
	while (2 * nColumnGroup < m_szLayoutColumns.GetSize())
	{
		for (nParameter = 0, nParameters = (INT)m_cLayout[0].GetSize(); nParameter < nParameters; nParameter++)
		{
			if ((pParameter = m_cLayout[0].GetAt(nParameter)) && pParameter->GetColumn() >= nColumnGroup)
			{
				m_cLayout[0].RemoveAt(nParameter);
				delete pParameter;
				nParameters--;
				nParameter--;
			}
		}
		SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_VIEW, LVM_DELETECOLUMN, m_szLayoutColumns.GetUpperBound());
		SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_VIEW, LVM_DELETECOLUMN, m_szLayoutColumns.GetUpperBound() - 1);
		SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_VIEW, LVM_DELETEALLITEMS);
		m_szLayoutColumns.RemoveAt(m_szLayoutColumns.GetUpperBound());
		m_szLayoutColumns.RemoveAt(m_szLayoutColumns.GetUpperBound());
		m_ptLayout.x = min(nColumnGroup, m_ptLayout.x);
	}
	while (2 * nColumnGroup > m_szLayoutColumns.GetSize())
	{
		for (m_szLayoutColumns.InsertAt(m_szLayoutColumns.GetSize(), STRING(IDS_AND_TITLEITEM_ID)); SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_VIEW, LVM_DELETEALLITEMS) >= 0; )
		{
			Listview_InsertColumn(GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_VIEW), (INT)m_szLayoutColumns.GetUpperBound(), m_szLayoutColumns.GetAt(m_szLayoutColumns.GetUpperBound()), CalcColumnWidth(m_szLayoutColumns.GetAt(m_szLayoutColumns.GetUpperBound())));
			break;
		}
		m_szLayoutColumns.InsertAt(m_szLayoutColumns.GetSize(), STRING(IDS_AND_TITLEITEM_DESCRIPTION));
		Listview_InsertColumn(GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_VIEW), (INT)m_szLayoutColumns.GetUpperBound(), m_szLayoutColumns.GetAt(m_szLayoutColumns.GetUpperBound()), CalcColumnWidth(m_szLayoutColumns.GetAt(m_szLayoutColumns.GetUpperBound())));
	}
	if (2 * nColumnGroup == m_szLayoutColumns.GetSize() && nColumnGroup > 0)
	{
		for (nParameter = 0, nParameters = (INT)m_cLayout[0].GetSize(), SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_VIEW, LVM_DELETEALLITEMS), nRows = 0; nParameter < nParameters; nParameter++)
		{
			nRows = ((pParameter = m_cLayout[0].GetAt(nParameter))) ? (((nRow = pParameter->GetRow()) >= 0) ? max(nRow + 1, nRows) : max(nParameter + 1, nRows)) : nRows;
			continue;
		}
		for (nRow = 0, nRows = max(nRows, ANDSETTINGSCONTENTSPAGE_DEFAULT_ROWS), SetCurRow(), SetCurColumn(); nRow < nRows; nRow++)
		{
			for (nIndex = 0, nCount = (INT)m_szLayoutColumns.GetSize(); nIndex < nCount; nIndex = nIndex + 1)
			{
				if (!nIndex  &&  Listview_InsertText(GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_VIEW), nRow, EMPTYSTRING)) continue;
				if (nIndex > 0 && Listview_SetText(GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_VIEW), nRow, nIndex, EMPTYSTRING)) continue;
			}
		}
		for (nParameter = 0, nParameters = (INT)m_cLayout[0].GetSize(); nParameter < nParameters; nParameter++)
		{
			if ((pParameter = m_cLayout[0].GetAt(nParameter)) && ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pParameter->GetName()))) || pParameter->IsLabel()))
			{
				Listview_SetText(GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_VIEW), (pParameter->GetRow() >= 0) ? pParameter->GetRow() : nParameter, (pParameter->GetColumn() >= 0) ? (2 * pParameter->GetColumn()) : 0, pParameter->GetName());
				Listview_SetText(GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_VIEW), (pParameter->GetRow() >= 0) ? pParameter->GetRow() : nParameter, (pParameter->GetColumn() >= 0) ? (2 * pParameter->GetColumn() + 1) : 1, (!pParameter->IsLabel()) ? pDatabaseTMParameter->GetDescription() : pParameter->GetLabel());
			}
		}
		Listview_SetCurText(GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_VIEW), m_ptLayout.y);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_DETAILS)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_VIEW)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_OOLCOLORS_TEXT_STATIC)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_OOLCOLORS_TEXT)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_OOLCOLOR_STATIC)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_OOLCOLOR)->EnableWindow();
		SetParameterInfo();
		return;
	}
	SetCurRow();
	SetCurColumn();
	m_cLayout[0].RemoveAll();
	SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_VIEW, LVM_DELETEALLITEMS);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_VIEW)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_OOLCOLORS_TEXT_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_OOLCOLORS_TEXT)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_OOLCOLOR_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_OOLCOLOR)->EnableWindow(FALSE);
	SetParameterInfo();
}

VOID CANDSettingsContentsPage::SetParameterInfo()
{
	INT  nPos;
	INT  nIndex;
	CString  szName;
	CString  szPosition;
	CString  szParameter;
	CANDLayoutParameter  *pParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	if (SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_VIEW, LVM_GETITEMCOUNT) > 0)
	{
		if ((pDatabaseTMParameter = ((pParameter = FindParameter())) ? GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pParameter->GetName())) : (CDatabaseTMParameter *)NULL))
		{
			szParameter.Format(STRING(IDS_ANDSETTINGS_CONTENTSPAGE_PARAMETERFORMAT), pDatabaseTMParameter->GetTag(), pDatabaseTMParameter->GetDescription());
			SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szParameter));
			SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (pParameter->GetColor() == GetSysColor(COLOR_WINDOW)) ? (LPARAM)GetDatabase()->GetANDIDColumnColor() : (LPARAM)pParameter->GetColor());
			SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS, CB_SETCURSEL, ((nIndex = (INT)SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS, CB_GETCURSEL)) < 0) ? (WPARAM)max(SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_ANDSETTINGS_CONTENTSPAGE_TOPICS_COMMENTS)), 0) : nIndex);
			Spinbox_SetPos(GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_NUMBER), abs(pParameter->GetOccurrence()));
			Spinbox_SetPos(GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_COUNT), pParameter->GetDigits());
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DEFAULT, ((pParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT)) || (pParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_FLOATINGPOINT)) == 0) ? TRUE : FALSE);
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_FLOAT, (((pParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT)) == 0) && (pParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT)) ? TRUE : FALSE);
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DECIMAL, (((pParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT)) == 0) && (pParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) == 0 && (pParameter->GetAttributes() & TMPARAMETER_RADIX_DECIMAL)) ? TRUE : FALSE);
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_OCTAL, (((pParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT)) == 0) && (pParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) == 0 && (pParameter->GetAttributes() & TMPARAMETER_RADIX_OCTAL)) ? TRUE : FALSE);
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_HEXADECIMAL, (((pParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT)) == 0) && (pParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) == 0 && (pParameter->GetAttributes() & TMPARAMETER_RADIX_HEXADECIMAL)) ? TRUE : FALSE);
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_BINARY, (((pParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT)) == 0) && (pParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) == 0 && (pParameter->GetAttributes() & TMPARAMETER_RADIX_BINARY)) ? TRUE : FALSE);
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_INVERSE, (((pParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT)) == 0) && (pParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) == 0 && (pParameter->GetAttributes() & TMPARAMETER_CODING_INVERSEBITPATTERN)) ? TRUE : FALSE);
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_DEFAULT, (!pParameter->GetOccurrence()) ? TRUE : FALSE);
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_PAST, (pParameter->GetOccurrence() < 0) ? TRUE : FALSE);
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE, (pParameter->GetOccurrence() != 0) ? TRUE : FALSE);
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_DEFAULT, (!pParameter->GetDigits()) ? TRUE : FALSE);
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS, (pParameter->GetDigits() > 0) ? TRUE : FALSE);
			CheckRadioButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_ALIGN_LEFT, IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_ALIGN_RIGHT, (pParameter->GetAlignment() == DT_CENTER) ? IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_ALIGN_CENTER : ((pParameter->GetAlignment() == DT_RIGHT) ? IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_ALIGN_RIGHT : IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_ALIGN_LEFT));
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS_TEXT)->SetWindowText((Combobox_GetText(GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS), (INT)SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS, CB_GETCURSEL)) == STRING(IDS_ANDSETTINGS_CONTENTSPAGE_TOPICS_COMMENTS)) ? (((nPos = pParameter->GetComment().Find(EOL)) >= 0) ? pParameter->GetComment().Left(nPos) : pParameter->GetComment()) : (((nPos = pParameter->GetComment().Find(EOL)) >= 0) ? pParameter->GetComment().Mid(nPos + 1) : EMPTYSTRING));
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME_STATIC)->EnableWindow(TRUE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME_STATIC)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_LABEL_STATIC)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_LABEL_STATIC)->EnableWindow(FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_STATIC)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DEFAULT)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_FLOAT)->EnableWindow((pParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) ? TRUE : FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DECIMAL)->EnableWindow((pParameter->GetAttributes() & (TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER)) ? TRUE : FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_OCTAL)->EnableWindow((pParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_UNSIGNEDINTEGER)) ? TRUE : FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_HEXADECIMAL)->EnableWindow((pParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_UNSIGNEDINTEGER)) ? TRUE : FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_BINARY)->EnableWindow((pParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_UNSIGNEDINTEGER)) ? TRUE : FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_INVERSE)->EnableWindow((pParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN)) ? TRUE : FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_STATIC)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_DEFAULT)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_PAST)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_NUMBER)->EnableWindow(IsDlgButtonChecked(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE));
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_STATIC)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_DEFAULT)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_COUNT)->EnableWindow(IsDlgButtonChecked(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS));
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS_TEXT)->EnableWindow();
			m_szTopicsText.SetAtGrow(0, ((nPos = pParameter->GetComment().Find(EOL)) >= 0) ? pParameter->GetComment().Left(nPos) : pParameter->GetComment());
			m_szTopicsText.SetAtGrow(1, (nPos >= 0) ? pParameter->GetComment().Mid(nPos + 1) : EMPTYSTRING);
		}
		if (!pDatabaseTMParameter  &&  pParameter)
		{
			SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME, CB_SETCURSEL, (WPARAM)-1);
			SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (pParameter->GetColor() == GetSysColor(COLOR_WINDOW)) ? (LPARAM)GetDatabase()->GetANDIDColumnColor() : (LPARAM)pParameter->GetColor());
			SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS, CB_SETCURSEL, (WPARAM)-1);
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DEFAULT, FALSE);
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DECIMAL, FALSE);
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_FLOAT, FALSE);
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_BINARY, FALSE);
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_OCTAL, FALSE);
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_HEXADECIMAL, FALSE);
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_INVERSE, FALSE);
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_DEFAULT, FALSE);
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_PAST, FALSE);
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE, FALSE);
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_DEFAULT, FALSE);
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS, FALSE);
			CheckRadioButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_ALIGN_LEFT, IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_ALIGN_RIGHT, (pParameter->GetAlignment() == DT_CENTER) ? IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_ALIGN_CENTER : ((pParameter->GetAlignment() == DT_RIGHT) ? IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_ALIGN_RIGHT : IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_ALIGN_LEFT));
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS_TEXT)->SetWindowText(EMPTYSTRING);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_LABEL_STATIC)->EnableWindow(TRUE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_LABEL_STATIC)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME_STATIC)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME_STATIC)->EnableWindow(FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME)->SetWindowText(pParameter->GetLabel());
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_STATIC)->EnableWindow(FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DEFAULT)->EnableWindow(FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DECIMAL)->EnableWindow(FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_FLOAT)->EnableWindow(FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_BINARY)->EnableWindow(FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_OCTAL)->EnableWindow(FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_HEXADECIMAL)->EnableWindow(FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_INVERSE)->EnableWindow(FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_STATIC)->EnableWindow(FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_DEFAULT)->EnableWindow(FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_PAST)->EnableWindow(FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE)->EnableWindow(FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_NUMBER)->EnableWindow(FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_STATIC)->EnableWindow(FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_DEFAULT)->EnableWindow(FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS)->EnableWindow(FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_COUNT)->EnableWindow(FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS)->EnableWindow(FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS_TEXT)->EnableWindow(FALSE);
			m_szTopicsText.RemoveAll();
		}
		if ((pDatabaseTMParameter = (!pParameter  &&  SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME, CB_GETCURSEL), 0)) >= 0 && lstrlen((szName = Combobox_GetText(GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME), (INT)SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME, CB_GETCURSEL)))) >= 0) ? GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(szName.Left((szName.Find(SPACE) >= 0) ? szName.Find(SPACE) : szName.GetLength()))) : (CDatabaseTMParameter *)NULL))
		{
			SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)GetDatabase()->GetANDIDColumnColor());
			SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS, CB_SETCURSEL, ((nIndex = (INT)SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS, CB_GETCURSEL)) < 0) ? (WPARAM)max(SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_ANDSETTINGS_CONTENTSPAGE_TOPICS_COMMENTS)), 0) : nIndex);
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DEFAULT, ((pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT)) || (pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_FLOATINGPOINT)) == 0) ? TRUE : FALSE);
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_FLOAT, (((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT)) == 0) && (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT)) ? TRUE : FALSE);
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DECIMAL, (((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT)) == 0) && (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) == 0 && (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_RADIX_DECIMAL)) ? TRUE : FALSE);
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_OCTAL, (((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT)) == 0) && (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) == 0 && (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_RADIX_OCTAL)) ? TRUE : FALSE);
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_HEXADECIMAL, (((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT)) == 0) && (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) == 0 && (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_RADIX_HEXADECIMAL)) ? TRUE : FALSE);
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_BINARY, (((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT)) == 0) && (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) == 0 && (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_RADIX_BINARY)) ? TRUE : FALSE);
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_INVERSE, (((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT)) == 0) && (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) == 0 && (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_INVERSEBITPATTERN)) ? TRUE : FALSE);
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_DEFAULT, TRUE);
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_PAST, FALSE);
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE, FALSE);
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_DEFAULT, TRUE);
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS, FALSE);
			CheckRadioButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_ALIGN_LEFT, IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_ALIGN_RIGHT, IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_ALIGN_LEFT);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS_TEXT)->SetWindowText(EMPTYSTRING);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME_STATIC)->EnableWindow(TRUE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME_STATIC)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_LABEL_STATIC)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_LABEL_STATIC)->EnableWindow(FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_STATIC)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DEFAULT)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_FLOAT)->EnableWindow((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) ? TRUE : FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DECIMAL)->EnableWindow((pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER)) ? TRUE : FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_OCTAL)->EnableWindow((pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_UNSIGNEDINTEGER)) ? TRUE : FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_HEXADECIMAL)->EnableWindow((pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_UNSIGNEDINTEGER)) ? TRUE : FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_BINARY)->EnableWindow((pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_UNSIGNEDINTEGER)) ? TRUE : FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_INVERSE)->EnableWindow((pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN)) ? TRUE : FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_STATIC)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_DEFAULT)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_PAST)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_NUMBER)->EnableWindow(FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_STATIC)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_DEFAULT)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_COUNT)->EnableWindow(FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS_TEXT)->EnableWindow();
			m_szTopicsText.RemoveAll();
		}
		if (pDatabaseTMParameter || pParameter)
		{
			szPosition.Format(STRING(IDS_ANDSETTINGS_CONTENTSPAGE_POSITIONFORMAT), m_ptLayout.y + 1, m_ptLayout.x + 1);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_POSITION)->SetWindowText(szPosition);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_ADD)->ShowWindow((!pParameter) ? SW_SHOW : SW_HIDE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_ADD)->EnableWindow((!pParameter  &&  CheckParameter()) ? Check(FALSE) : FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_MODIFY)->ShowWindow((pParameter) ? SW_SHOW : SW_HIDE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow((pParameter  &&  CheckParameter()) ? Check(FALSE) : FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_REMOVE)->EnableWindow((pParameter) ? TRUE : FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_REMOVEALL)->EnableWindow((m_cLayout[0].GetSize() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_IMPORT)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_POSITION)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME_STATIC)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_COLOR_STATIC)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_COLOR)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_ALIGN_STATIC)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_ALIGN_LEFT)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_ALIGN_CENTER)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_ALIGN_RIGHT)->EnableWindow();
			return;
		}
	}
	SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME, CB_SETCURSEL, (WPARAM)-1);
	SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_OOLCOLORS_TEXT, CB_SETCURSEL, (WPARAM)-1);
	SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS, CB_SETCURSEL, (WPARAM)-1);
	CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DEFAULT, FALSE);
	CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DECIMAL, FALSE);
	CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_FLOAT, FALSE);
	CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_BINARY, FALSE);
	CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_OCTAL, FALSE);
	CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_HEXADECIMAL, FALSE);
	CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_INVERSE, FALSE);
	CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_ALIGN_LEFT, FALSE);
	CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_ALIGN_CENTER, FALSE);
	CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_ALIGN_RIGHT, FALSE);
	CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_DEFAULT, FALSE);
	CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_PAST, FALSE);
	CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE, FALSE);
	CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_DEFAULT, FALSE);
	CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_COUNT, FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_POSITION)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS_TEXT)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_ADD)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_MODIFY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_REMOVEALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_IMPORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_POSITION)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME_STATIC)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_LABEL_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_LABEL_STATIC)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_COLOR_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_COLOR)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DEFAULT)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DECIMAL)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_FLOAT)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_BINARY)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_OCTAL)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_HEXADECIMAL)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_INVERSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_ALIGN_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_ALIGN_LEFT)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_ALIGN_CENTER)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_ALIGN_RIGHT)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_DEFAULT)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_PAST)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_NUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_DEFAULT)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_COUNT)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS_TEXT)->EnableWindow(FALSE);
	m_szTopicsText.RemoveAll();
}

BOOL CANDSettingsContentsPage::GetParameterInfo(CString &szName, CString &szDescription, CString &szComments, ULONGLONG &nAttributes, COLORREF &nColor, UINT &nAlignment, INT &nOccurrence, INT &nDigits) CONST
{
	INT  nPos;
	CString  szParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	for (GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME)->GetWindowText(szName); (pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(((nPos = szName.Find(SPACE)) >= 0) ? szName.Left(nPos) : szName))); )
	{
		for (szParameter.Format(STRING(IDS_ANDSETTINGS_CONTENTSPAGE_PARAMETERFORMAT), (LPCTSTR)pDatabaseTMParameter->GetTag(), (LPCTSTR)pDatabaseTMParameter->GetDescription()); !(nPos = szParameter.Find(szName)); )
		{
			szName = pDatabaseTMParameter->GetTag();
			break;
		}
		if (nPos != 0) szName.Empty();
		break;
	}
	if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(szName))))
	{
		nAttributes = (IsDlgButtonChecked(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DEFAULT)) ? pDatabaseTMParameter->GetAttributes() : 0;
		nAttributes = (IsDlgButtonChecked(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DECIMAL) || IsDlgButtonChecked(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_FLOAT)) ? ((pDatabaseTMParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_HEXADECIMAL)) | TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_RADIX_DECIMAL) : nAttributes;
		nAttributes = (IsDlgButtonChecked(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_BINARY)) ? ((pDatabaseTMParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_DECIMAL | TMPARAMETER_RADIX_HEXADECIMAL)) | TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_RADIX_BINARY) : nAttributes;
		nAttributes = (IsDlgButtonChecked(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_OCTAL)) ? ((pDatabaseTMParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_DECIMAL | TMPARAMETER_RADIX_HEXADECIMAL)) | TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_RADIX_OCTAL) : nAttributes;
		nAttributes = (IsDlgButtonChecked(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_HEXADECIMAL)) ? ((pDatabaseTMParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_DECIMAL)) | TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_RADIX_HEXADECIMAL) : nAttributes;
		nAttributes = (IsDlgButtonChecked(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_INVERSE)) ? ((nAttributes & ~(TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_DECIMAL | TMPARAMETER_RADIX_HEXADECIMAL)) | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_RADIX_BINARY) : nAttributes;
		nAlignment = (IsDlgButtonChecked(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_ALIGN_CENTER)) ? DT_CENTER : ((IsDlgButtonChecked(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_ALIGN_RIGHT)) ? DT_RIGHT : DT_LEFT);
		nOccurrence = (IsDlgButtonChecked(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE)) ? ((IsDlgButtonChecked(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_PAST)) ? -(INT)Spinbox_GetPos(GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_NUMBER)) : (INT)Spinbox_GetPos(GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_NUMBER))) : 0;
		nColor = (COLORREF)GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_COLOR)->SendMessage(CCB_GETCOLOR, (WPARAM)GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_COLOR)->SendMessage(CB_GETCURSEL));
		nDigits = (IsDlgButtonChecked(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS)) ? (INT)Spinbox_GetPos(GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_COUNT)) : 0;
		szComments = (m_szTopicsText.GetSize() > 0) ? m_szTopicsText.GetAt(0) : EMPTYSTRING;
		szComments += (m_szTopicsText.GetSize() > 1) ? (EOL + m_szTopicsText.GetAt(1)) : EOL;
		szDescription = pDatabaseTMParameter->GetDescription();
		return TRUE;
	}
	szName.Empty();
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME)->GetWindowText(szComments);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME)->GetWindowText(szDescription);
	nColor = (COLORREF)GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_COLOR)->SendMessage(CCB_GETCOLOR, (WPARAM)GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_COLOR)->SendMessage(CB_GETCURSEL));
	nAlignment = (IsDlgButtonChecked(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_ALIGN_CENTER)) ? DT_CENTER : ((IsDlgButtonChecked(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_ALIGN_RIGHT)) ? DT_RIGHT : DT_LEFT);
	nAttributes = nOccurrence = nDigits = 0;
	return TRUE;
}

BOOL CANDSettingsContentsPage::SetCurRow(INT nRow)
{
	if (nRow >= 0)
	{
		m_ptLayout.y = nRow;
		return TRUE;
	}
	return FALSE;
}

INT CANDSettingsContentsPage::GetCurRow() CONST
{
	return m_ptLayout.y;
}

BOOL CANDSettingsContentsPage::SetCurColumn(INT nColumn)
{
	if (nColumn < m_szLayoutColumns.GetSize())
	{
		for (m_szLayoutColumns.SetAt(2 * m_ptLayout.x, (m_szLayoutColumns.GetAt(2 * m_ptLayout.x).Right(lstrlen(STRING(IDS_ANDSETTINGS_CONTENTSPAGE_COLUMNMARKER))) == STRING(IDS_ANDSETTINGS_CONTENTSPAGE_COLUMNMARKER)) ? m_szLayoutColumns.GetAt(2 * m_ptLayout.x).Left(m_szLayoutColumns.GetAt(2 * m_ptLayout.x).GetLength() - lstrlen(STRING(IDS_ANDSETTINGS_CONTENTSPAGE_COLUMNMARKER))) : m_szLayoutColumns.GetAt(2 * m_ptLayout.x)), m_szLayoutColumns.SetAt(2 * (nColumn / 2), m_szLayoutColumns.GetAt(2 * (nColumn / 2)) + STRING(IDS_ANDSETTINGS_CONTENTSPAGE_COLUMNMARKER)); TRUE; )
		{
			Listview_SetColumn(GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_VIEW), 2 * m_ptLayout.x, m_szLayoutColumns.GetAt(2 * m_ptLayout.x));
			Listview_SetColumn(GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_VIEW), 2 * m_ptLayout.x, m_szLayoutColumns.GetAt(2 * (m_ptLayout.x = nColumn / 2)));
			break;
		}
		return TRUE;
	}
	return FALSE;
}

INT CANDSettingsContentsPage::GetCurColumn() CONST
{
	return m_ptLayout.x;
}

CANDLayoutParameter *CANDSettingsContentsPage::FindParameter() CONST
{
	INT  nIndex;

	return(((nIndex = LookupParameter()) >= 0) ? m_cLayout[0].GetAt(nIndex) : (CANDLayoutParameter *)NULL);
}

BOOL CANDSettingsContentsPage::CheckParameter() CONST
{
	INT  nDigits;
	INT  nOccurrence;
	UINT  nAlignment;
	COLORREF  nColor;
	CString  szName;
	CString  szComments;
	CString  szDescription;
	ULONGLONG  nAttributes;
	CANDLayoutParameter  *pParameter;

	return((GetParameterInfo(szName, szDescription, szComments, nAttributes, nColor, nAlignment, nOccurrence, nDigits)) ? (((pParameter = FindParameter())) ? (!szName.IsEmpty() && (((!pParameter->IsLabel() && (pParameter->GetName() != szName || (pParameter->GetComment() != szComments  &&  pParameter->GetComment() + EOL != szComments))) || (pParameter->IsLabel() && pParameter->GetLabel() != szDescription) || ((pParameter->GetColor() == GetSysColor(COLOR_WINDOW) && GetDatabase()->GetANDIDColumnColor() != nColor) || (pParameter->GetColor() != GetSysColor(COLOR_WINDOW) && GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_COLOR)->SendMessage(CCB_FINDCOLOR, (WPARAM)-1, (LPARAM)pParameter->GetColor()) != GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_COLOR)->SendMessage(CB_GETCURSEL))) || (pParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT | TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_FLOATINGPOINT | TMPARAMETER_CODING_TEXTSTRING | TMPARAMETER_CODING_TIME | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_DECIMAL | TMPARAMETER_RADIX_HEXADECIMAL)) != (nAttributes & (TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT | TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_FLOATINGPOINT | TMPARAMETER_CODING_TEXTSTRING | TMPARAMETER_CODING_TIME | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_DECIMAL | TMPARAMETER_RADIX_HEXADECIMAL)) || pParameter->GetAlignment() != nAlignment || pParameter->GetOccurrence() != nOccurrence || pParameter->GetDigits() != nDigits)) ? TRUE : FALSE) : !szName.IsEmpty()) : FALSE);
}

INT CANDSettingsContentsPage::LookupParameter() CONST
{
	INT  nParameter;
	INT  nParameters;
	CANDLayoutParameter  *pParameter;

	for (nParameter = 0, nParameters = (INT)m_cLayout[0].GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pParameter = m_cLayout[0].GetAt(nParameter)) && ((pParameter->GetRow() >= 0 && pParameter->GetColumn() >= 0 && m_ptLayout.x == pParameter->GetColumn() && m_ptLayout.y == pParameter->GetRow()) || (pParameter->GetColumn() < 0 && !m_ptLayout.x && ((pParameter->GetRow() >= 0 && pParameter->GetRow() == m_ptLayout.y) || (pParameter->GetRow() < 0 && m_ptLayout.y == nParameter))))) break;
		continue;
	}
	return((nParameter < nParameters) ? nParameter : -1);
}

UINT CANDSettingsContentsPage::LookupColumnName(LPCTSTR pszColumn) CONST
{
	if (!_tcsncmp(pszColumn, STRING(IDS_AND_TITLEITEM_ID), lstrlen(STRING(IDS_AND_TITLEITEM_ID)))) return AND_TITLEITEM_ID;
	if (!_tcsncmp(pszColumn, STRING(IDS_AND_TITLEITEM_DESCRIPTION), lstrlen(STRING(IDS_AND_TITLEITEM_DESCRIPTION)))) return AND_TITLEITEM_DESCRIPTION;
	return 0;
}

INT CANDSettingsContentsPage::CalcColumnWidth(LPCTSTR pszColumn)
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
			if (pDC->GetTextMetrics(&tmFont))
			{
				nWidth = ((nColumn = LookupColumnName(pszColumn)) == AND_TITLEITEM_ID) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetANDIDColumnCharWidth() + 1)*(3 * tmFont.tmAveCharWidth / 2), pDC->GetTextExtent(pszColumn).cx)) : 0;
				nWidth = (nColumn == AND_TITLEITEM_DESCRIPTION) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetANDDescriptionColumnCharWidth() + 1)*(3 * tmFont.tmAveCharWidth / 2), pDC->GetTextExtent(pszColumn).cx)) : nWidth;
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

INT CANDSettingsContentsPage::CalcColumnIndent() CONST
{
	return 3 * GetSystemMetrics(SM_CXEDGE);
}

BOOL CANDSettingsContentsPage::IsModified(BOOL bAll) CONST
{
	INT  nColor;
	INT  nColors;

	if (IsWindow(GetSafeHwnd()) && !bAll)
	{
		for (nColor = 0, nColors = (m_nColors[0].GetSize() == m_nColors[1].GetSize()) ? (INT)m_nColors[0].GetSize() : 0; nColor < nColors; nColor++)
		{
			if (m_nColors[0].GetAt(nColor) != m_nColors[1].GetAt(nColor)) break;
			continue;
		}
		return((!m_cLayout[0].Compare(&m_cLayout[1]) || nColor < nColors) ? TRUE : FALSE);
	}
	return((bAll) ? CLocalePropertyPage::IsModified() : FALSE);
}

BOOL CANDSettingsContentsPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? TRUE : CLocalePropertyPage::Check()) : TRUE);
}

void CANDSettingsContentsPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CANDSettingsContentsPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CANDSettingsContentsPage::PostNcDestroy()
{
	m_cLayout[0].RemoveAll();
	m_cLayout[1].RemoveAll();
	m_nColors[0].RemoveAll();
	m_nColors[1].RemoveAll();
	m_nLayoutColumns.RemoveAll();
	m_szLayoutColumns.RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CANDSettingsContentsPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CANDSettingsContentsPage)
	ON_BN_CLICKED(IDC_ANDSETTINGS_CONTENTSPAGE_ADD, OnAddParameter)
	ON_BN_CLICKED(IDC_ANDSETTINGS_CONTENTSPAGE_MODIFY, OnModifyParameter)
	ON_BN_CLICKED(IDC_ANDSETTINGS_CONTENTSPAGE_REMOVE, OnRemoveParameter)
	ON_BN_CLICKED(IDC_ANDSETTINGS_CONTENTSPAGE_REMOVEALL, OnRemoveAllParameters)
	ON_BN_CLICKED(IDC_ANDSETTINGS_CONTENTSPAGE_IMPORT, OnImportParameters)
	ON_BN_CLICKED(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DEFAULT, OnCodingDefault)
	ON_BN_CLICKED(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DECIMAL, OnCodingDecimal)
	ON_BN_CLICKED(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_BINARY, OnCodingBinary)
	ON_BN_CLICKED(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_OCTAL, OnCodingOctal)
	ON_BN_CLICKED(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_HEXADECIMAL, OnCodingHexadecimal)
	ON_BN_CLICKED(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_FLOAT, OnCodingFloat)
	ON_BN_CLICKED(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_INVERSE, OnCodingInverse)
	ON_BN_CLICKED(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_ALIGN_LEFT, OnAlignLeft)
	ON_BN_CLICKED(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_ALIGN_CENTER, OnAlignCenter)
	ON_BN_CLICKED(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_ALIGN_RIGHT, OnAlignRight)
	ON_BN_CLICKED(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_DEFAULT, OnOccurrenceDefault)
	ON_BN_CLICKED(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_PAST, OnOccurrencePast)
	ON_BN_CLICKED(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE, OnOccurrenceNumber)
	ON_BN_CLICKED(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_DEFAULT, OnDigitsDefault)
	ON_BN_CLICKED(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS, OnDigitsCount)
	ON_CBN_SELCHANGE(IDC_ANDSETTINGS_CONTENTSPAGE_OOLCOLORS_TEXT, OnSelchangeOolText)
	ON_CBN_SELCHANGE(IDC_ANDSETTINGS_CONTENTSPAGE_OOLCOLOR, OnSelchangeOolColor)
	ON_CBN_SELCHANGE(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME, OnSelchangeName)
	ON_CBN_SELCHANGE(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_COLOR, OnSelchangeColor)
	ON_CBN_SELCHANGE(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS, OnSelchangeTopics)
	ON_CBN_EDITCHANGE(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME, OnEditchangeName)
	ON_CONTROL(SBXN_CHANGE, IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_NUMBER, OnSpinchangeOccurrence)
	ON_CONTROL(SBXN_CHANGE, IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_COUNT, OnSpinchangeDigits)
	ON_EN_CHANGE(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS_TEXT, OnEditchangeTopicsText)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDSettingsContentsPage message handlers

BOOL CANDSettingsContentsPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	Spinbox_SetRange(GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_NUMBER), ANDSETTINGSCONTENTSPAGE_PARAMETER_MINIMUMOCCURRENCE, ANDSETTINGSCONTENTSPAGE_PARAMETER_MAXIMUMOCCURRENCE);
	Spinbox_SetRange(GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_COUNT), ANDSETTINGSCONTENTSPAGE_PARAMETER_MINIMUMDIGITS, ANDSETTINGSCONTENTSPAGE_PARAMETER_MAXIMUMDIGITS);
	SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_VIEW, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	EnumParameters();
	EnumOOLs();
	EnumTopics();
	ShowContents();
	return TRUE;
}

BOOL CANDSettingsContentsPage::OnSetActive()
{
	ShowContents();
	return CLocalePropertyPage::OnSetActive();
}

BOOL CANDSettingsContentsPage::OnKillActive()
{
	GetParentDialog()->OnDataExchange(GetSafeHwnd(), m_nLayoutColumns);
	return CLocalePropertyPage::OnKillActive();
}

BOOL CANDSettingsContentsPage::OnDataExchange(CONST CUIntArray &nColumns)
{
	m_nLayoutColumns.Copy(nColumns);
	return TRUE;
}

BOOL CANDSettingsContentsPage::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	INT  nRow;
	INT  nRows;
	INT  nIndex;
	CANDLayoutParameter  *pParameter;
	NMUPDOWN  *pNotifyUpDown = (NMUPDOWN *)lParam;
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_ANDSETTINGS_CONTENTSPAGE_VIEW)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_COLUMNCLICK)
		{
			SetCurColumn(pNotifyListView->iSubItem);
			SetParameterInfo();
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED && (pNotifyListView->uNewState & LVIS_SELECTED))
		{
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_MOVEUPDOWN)->EnableWindow();
			SetCurRow(pNotifyListView->iItem);
			SetParameterInfo();
		}
	}
	if (pNotifyUpDown->hdr.idFrom == IDC_ANDSETTINGS_CONTENTSPAGE_MOVEUPDOWN)
	{
		for (nRow = 0, nRows = (pNotifyUpDown->iDelta > 0) ? (INT)m_cLayout[0].GetSize() : 0; nRow < nRows; nRow++)
		{
			if ((pParameter = (CANDLayoutParameter *)m_cLayout[0].GetAt(nRow)) != (CANDLayoutParameter *)NULL)
			{
				pParameter->SetRow(((nIndex = (pParameter->GetRow() >= 0) ? pParameter->GetRow() : nRow) >= GetCurRow()) ? (nIndex + 1) : nIndex);
				pParameter->SetColumn(max(pParameter->GetColumn(), 0));
			}
		}
		for (nRow = 0, nRows = (pNotifyUpDown->iDelta < 0) ? (INT)m_cLayout[0].GetSize() : 0; nRow < nRows; nRow++)
		{
			if ((pParameter = (CANDLayoutParameter *)m_cLayout[0].GetAt(nRow)) != (CANDLayoutParameter *)NULL)
			{
				if ((nIndex = (pParameter->GetRow() >= 0) ? pParameter->GetRow() : nRow) == max(GetCurRow() - 1, 0))
				{
					m_cLayout[0].SetAt(nRow, (CANDLayoutParameter *)NULL);
					delete pParameter;
					continue;
				}
				pParameter->SetRow((nIndex >= GetCurRow()) ? (nIndex - 1) : nIndex);
				pParameter->SetColumn(max(pParameter->GetColumn(), 0));
			}
		}
		for (nRow = 0, nRows = (pNotifyUpDown->iDelta < 0) ? (INT)m_cLayout[0].GetSize() : 0; nRow < nRows; nRow++)
		{
			if (!(pParameter = m_cLayout[0].GetAt(nRow)))
			{
				m_cLayout[0].RemoveAt(nRow);
				nRows = nRows - 1;
				nRow = nRow - 1;
			}
		}
		if (pNotifyUpDown->iDelta > 0)
		{
			Listview_InsertText(GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_VIEW), GetCurRow(), EMPTYSTRING);
			Listview_SetCurText(GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_VIEW), GetCurRow() + 1);
			SetCurRow(GetCurRow() + 1);
		}
		if (pNotifyUpDown->iDelta < 0)
		{
			Listview_DeleteText(GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_VIEW), max(GetCurRow() - 1, 0));
			Listview_SetCurText(GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_VIEW), max(GetCurRow() - 1, 0));
			SetCurRow(max(GetCurRow() - 1, 0));
		}
		SetParameterInfo();
		GetDlgItem(IDOK)->EnableWindow(Check());
	}
	return CLocalePropertyPage::OnNotify(wParam, lParam, pResult);
}

void CANDSettingsContentsPage::OnAddParameter()
{
	INT  nColumn;
	INT  nColumns;
	INT  nDigits;
	INT  nOccurrence;
	UINT  nAlignment;
	COLORREF  nColor;
	CString  szName;
	CString  szComments;
	CString  szDescription;
	ULONGLONG  nAttributes;
	CANDLayoutParameter  *pParameter;
	CHourglassCursor  cCursor;

	if ((pParameter = new CANDLayoutParameter))
	{
		for (nColumn = 2 * GetCurColumn(), nColumns = (GetParameterInfo(szName, szDescription, szComments, nAttributes, nColor, nAlignment, nOccurrence, nDigits)) ? (INT)m_szLayoutColumns.GetSize() : 0; nColumn <= 2 * GetCurColumn() + 1 && nColumn < nColumns; nColumn++)
		{
			Listview_SetText(GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_VIEW), GetCurRow(), nColumn, (nColumn % 2 == 0) ? szName : szDescription);
			continue;
		}
		pParameter->SetName(szName);
		pParameter->SetLabel(szDescription);
		pParameter->SetComment(szComments);
		pParameter->SetRef((!pParameter->IsLabel()) ? GetDatabase()->GetTMParameters()->Find(szName) : -1);
		pParameter->SetRow(GetCurRow());
		pParameter->SetColumn(GetCurColumn());
		pParameter->SetAttributes(nAttributes);
		pParameter->SetOccurrence(nOccurrence);
		pParameter->SetAlignment(nAlignment);
		pParameter->SetDigits(nDigits);
		pParameter->SetColor(nColor);
		m_cLayout[0].Add(pParameter);
		SetParameterInfo();
	}
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_VIEW)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsContentsPage::OnModifyParameter()
{
	INT  nColumn;
	INT  nColumns;
	INT  nDigits;
	INT  nOccurrence;
	UINT  nAlignment;
	COLORREF  nColor;
	CString  szName;
	CString  szComments;
	CString  szDescription;
	ULONGLONG  nAttributes;
	CANDLayoutParameter  *pParameter;
	CHourglassCursor  cCursor;

	if ((pParameter = FindParameter()))
	{
		for (nColumn = 2 * GetCurColumn(), nColumns = (GetParameterInfo(szName, szDescription, szComments, nAttributes, nColor, nAlignment, nOccurrence, nDigits)) ? (INT)m_szLayoutColumns.GetSize() : 0; nColumn <= 2 * GetCurColumn() + 1 && nColumn < nColumns; nColumn++)
		{
			Listview_SetText(GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_VIEW), GetCurRow(), nColumn, (nColumn % 2 == 0) ? szName : szDescription);
			continue;
		}
		pParameter->SetName(szName);
		pParameter->SetLabel(szDescription);
		pParameter->SetComment(szComments);
		pParameter->SetRef((!pParameter->IsLabel()) ? GetDatabase()->GetTMParameters()->Find(szName) : -1);
		pParameter->SetColumn((pParameter->GetColumn() >= 0) ? GetCurColumn() : -1);
		pParameter->SetRow((pParameter->GetRow() >= 0) ? GetCurRow() : -1);
		pParameter->SetAttributes(nAttributes);
		pParameter->SetOccurrence(nOccurrence);
		pParameter->SetAlignment(nAlignment);
		pParameter->SetDigits(nDigits);
		pParameter->SetColor(nColor);
		SetParameterInfo();
	}
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_VIEW)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsContentsPage::OnRemoveParameter()
{
	INT  nIndex;
	INT  nColumn;
	INT  nColumns;
	CHourglassCursor  cCursor;

	if ((nIndex = LookupParameter()) >= 0)
	{
		for (nColumn = 2 * GetCurColumn(), nColumns = (INT)m_szLayoutColumns.GetSize(); nColumn <= 2 * GetCurColumn() + 1 && nColumn < nColumns; nColumn++)
		{
			Listview_SetText(GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_VIEW), GetCurRow(), nColumn, EMPTYSTRING);
			continue;
		}
		delete m_cLayout[0].GetAt(nIndex);
		m_cLayout[0].RemoveAt(nIndex);
		SetParameterInfo();
	}
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_VIEW)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsContentsPage::OnRemoveAllParameters()
{
	INT  nRow;
	INT  nRows;
	INT  nColumn;
	INT  nColumns;
	CHourglassCursor  cCursor;

	for (nRow = 0, nRows = (INT)SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_VIEW, LVM_GETITEMCOUNT), m_cLayout[0].RemoveAll(); nRow < nRows; nRow++)
	{
		for (nColumn = 0, nColumns = (INT)m_szLayoutColumns.GetSize(); nColumn < nColumns; nColumn++)
		{
			Listview_SetText(GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_VIEW), nRow, nColumn, EMPTYSTRING);
			continue;
		}
	}
	SetCurRow();
	SetCurColumn();
	SetParameterInfo();
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_VIEW)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsContentsPage::OnImportParameters()
{
	INT  nItem;
	INT  nItems;
	INT  nParameter;
	INT  nParameters;
	INT  nColumns[2];
	CUIntArray  nColumnItems;
	CANDLayoutParameter  *pParameter;
	CANDSettingsDirectoryDialog  cANDDirectoryDialog;

	if (cANDDirectoryDialog.Create(GetParent()) == IDOK)
	{
		for (nParameter = 0, nParameters = (cANDDirectoryDialog.GetLayout(m_cLayout[0])) ? (INT)m_cLayout[0].GetSize() : 0, m_cLayout[0].SetName(m_cLayout[1].GetName()), m_cLayout[0].SetTitle(m_cLayout[1].GetTitle()), nColumns[0] = 0; nParameter < nParameters; nParameter++)
		{
			if ((pParameter = m_cLayout[0].GetAt(nParameter)) != (CANDLayoutParameter *)NULL)
			{
				if (pParameter->GetColumn() < 0 && pParameter->GetRow() < 0)
				{
					pParameter->SetRow(nParameter);
					pParameter->SetColumn(0);
					continue;
				}
				nColumns[0] = (pParameter->GetColumn() > nColumns[0]) ? pParameter->GetColumn() : nColumns[0];
				continue;
			}
			break;
		}
		for (nItem = 0, nItems = (INT)m_nLayoutColumns.GetSize(), nColumns[0] = nColumns[0] + 1, nColumns[1] = 0; nItem < nItems; nItem++)
		{
			if ((nColumns[1] = (m_nLayoutColumns.GetAt(nItem) == AND_TITLEITEM_ID) ? (nColumns[1] + 1) : nColumns[1]) == 1) nColumnItems.Add(m_nLayoutColumns.GetAt(nItem));
			continue;
		}
		while (nColumns[0] > nColumns[1])
		{
			m_nLayoutColumns.Append(nColumnItems);
			nColumns[1]++;
		}
		ShowContents();
	}
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_VIEW)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsContentsPage::OnSelchangeOolText()
{
	SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_OOLCOLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nColors[0].GetAt(max(min(SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_OOLCOLORS_TEXT, CB_GETCURSEL), m_nColors[0].GetSize() - 1), 0)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsContentsPage::OnSelchangeOolColor()
{
	m_nColors[0].SetAt(max(min(SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_OOLCOLORS_TEXT, CB_GETCURSEL), m_nColors[0].GetSize() - 1), 0), (UINT)SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_OOLCOLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_OOLCOLOR, CB_GETCURSEL)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsContentsPage::OnSelchangeName()
{
	INT  nPos;
	CString  szName;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(szName.Left(((nPos = (szName = Combobox_GetText(GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME), (INT)SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME, CB_GETCURSEL)))).Find(SPACE)) >= 0) ? nPos : szName.GetLength())))))
	{
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DEFAULT, ((pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT)) || (pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_FLOATINGPOINT)) == 0) ? TRUE : FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_FLOAT, (((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT)) == 0) && (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT)) ? TRUE : FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DECIMAL, (((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT)) == 0) && (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) == 0 && (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_RADIX_DECIMAL)) ? TRUE : FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_OCTAL, (((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT)) == 0) && (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) == 0 && (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_RADIX_OCTAL)) ? TRUE : FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_HEXADECIMAL, (((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT)) == 0) && (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) == 0 && (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_RADIX_HEXADECIMAL)) ? TRUE : FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_BINARY, (((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT)) == 0) && (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) == 0 && (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_RADIX_BINARY)) ? TRUE : FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_INVERSE, (((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT)) == 0) && (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) == 0 && (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_INVERSEBITPATTERN)) ? TRUE : FALSE);
		SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_ANDSETTINGS_CONTENTSPAGE_TOPICS_COMMENTS)), 0));
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME_STATIC)->EnableWindow(TRUE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME_STATIC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_LABEL_STATIC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_LABEL_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_STATIC)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DEFAULT)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_FLOAT)->EnableWindow((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) ? TRUE : FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DECIMAL)->EnableWindow((pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER)) ? TRUE : FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_OCTAL)->EnableWindow((pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_UNSIGNEDINTEGER)) ? TRUE : FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_HEXADECIMAL)->EnableWindow((pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_UNSIGNEDINTEGER)) ? TRUE : FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_BINARY)->EnableWindow((pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_UNSIGNEDINTEGER)) ? TRUE : FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_INVERSE)->EnableWindow((pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN)) ? TRUE : FALSE);
		if (!IsDlgButtonChecked(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_DEFAULT) && !IsDlgButtonChecked(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE))
		{
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_DEFAULT, TRUE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_STATIC)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_DEFAULT)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_PAST)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_NUMBER)->EnableWindow(FALSE);
		}
		if (!IsDlgButtonChecked(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_DEFAULT) && !IsDlgButtonChecked(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS))
		{
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_DEFAULT, TRUE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_STATIC)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_DEFAULT)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_COUNT)->EnableWindow(FALSE);
		}
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS_TEXT)->SetWindowText(EMPTYSTRING);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS_TEXT)->EnableWindow();
		m_szTopicsText.RemoveAll();
	}
	else
	{
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DEFAULT, FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DECIMAL, FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_FLOAT, FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_BINARY, FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_OCTAL, FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_HEXADECIMAL, FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_INVERSE, FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE, FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_DEFAULT, FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_PAST, FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_DEFAULT, FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS, FALSE);
		SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS, CB_SETCURSEL, (WPARAM)-1);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS_TEXT)->SetWindowText(EMPTYSTRING);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_LABEL_STATIC)->EnableWindow(TRUE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_LABEL_STATIC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME_STATIC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DEFAULT)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DECIMAL)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_FLOAT)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_BINARY)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_OCTAL)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_HEXADECIMAL)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_INVERSE)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_DEFAULT)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_PAST)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_NUMBER)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_DEFAULT)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_COUNT)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS_TEXT)->EnableWindow(FALSE);
		m_szTopicsText.RemoveAll();
	}
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_ADD)->EnableWindow((!FindParameter()) ? CheckParameter() : FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
}

void CANDSettingsContentsPage::OnSelchangeColor()
{
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
}

void CANDSettingsContentsPage::OnEditchangeName()
{
	INT  nPos;
	CString  szName;
	CString  szParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	for (GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME)->GetWindowText(szName), m_szTopicsText.RemoveAll(); (pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(((nPos = szName.Find(SPACE)) >= 0) ? szName.Left(nPos) : szName))); )
	{
		szParameter.Format(STRING(IDS_ANDSETTINGS_CONTENTSPAGE_PARAMETERFORMAT), (LPCTSTR)pDatabaseTMParameter->GetTag(), (LPCTSTR)pDatabaseTMParameter->GetDescription());
		szName = (!szParameter.Find(szName)) ? pDatabaseTMParameter->GetTag() : EMPTYSTRING;
		break;
	}
	if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(szName))))
	{
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DEFAULT, ((pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT)) || (pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_FLOATINGPOINT)) == 0) ? TRUE : FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_FLOAT, (((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT)) == 0) && (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT)) ? TRUE : FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DECIMAL, (((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT | TMPARAMETER_CODING_FLOATINGPOINT)) == 0) && (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_RADIX_DECIMAL)) ? TRUE : FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_OCTAL, (((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT)) == 0) && (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_RADIX_OCTAL)) ? TRUE : FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_HEXADECIMAL, (((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT)) == 0) && (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_RADIX_HEXADECIMAL)) ? TRUE : FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_BINARY, (((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT)) == 0) && (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_RADIX_BINARY)) ? TRUE : FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_INVERSE, (((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT)) == 0) && (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_INVERSEBITPATTERN)) ? TRUE : FALSE);
		SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_ANDSETTINGS_CONTENTSPAGE_TOPICS_COMMENTS)), 0));
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME_STATIC)->EnableWindow(TRUE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME_STATIC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_LABEL_STATIC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_LABEL_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_STATIC)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DEFAULT)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_FLOAT)->EnableWindow((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) ? TRUE : FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DECIMAL)->EnableWindow((pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER)) ? TRUE : FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_OCTAL)->EnableWindow((pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_UNSIGNEDINTEGER)) ? TRUE : FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_HEXADECIMAL)->EnableWindow((pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_UNSIGNEDINTEGER)) ? TRUE : FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_BINARY)->EnableWindow((pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_UNSIGNEDINTEGER)) ? TRUE : FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_INVERSE)->EnableWindow((pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN)) ? TRUE : FALSE);
		if (!IsDlgButtonChecked(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_DEFAULT) && !IsDlgButtonChecked(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE))
		{
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_DEFAULT, TRUE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_STATIC)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_DEFAULT)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_PAST)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_NUMBER)->EnableWindow(FALSE);
		}
		if (!IsDlgButtonChecked(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_DEFAULT) && !IsDlgButtonChecked(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS))
		{
			CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_DEFAULT, TRUE);
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_STATIC)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_DEFAULT)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS)->EnableWindow();
			GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_COUNT)->EnableWindow(FALSE);
		}
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS_TEXT)->SetWindowText(EMPTYSTRING);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS_TEXT)->EnableWindow();
	}
	else
	{
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DEFAULT, FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DECIMAL, FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_FLOAT, FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_BINARY, FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_OCTAL, FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_HEXADECIMAL, FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_INVERSE, FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE, FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_DEFAULT, FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_PAST, FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_DEFAULT, FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS, FALSE);
		SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS, CB_SETCURSEL, (WPARAM)-1);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS_TEXT)->SetWindowText(EMPTYSTRING);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_LABEL_STATIC)->EnableWindow(TRUE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_LABEL_STATIC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME_STATIC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_NAME_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DEFAULT)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DECIMAL)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_FLOAT)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_BINARY)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_OCTAL)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_HEXADECIMAL)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_INVERSE)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_DEFAULT)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_PAST)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_NUMBER)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_DEFAULT)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_COUNT)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS_TEXT)->EnableWindow(FALSE);
	}
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_ADD)->EnableWindow((!FindParameter()) ? CheckParameter() : FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
}

void CANDSettingsContentsPage::OnCodingDefault()
{
	CheckRadioButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DEFAULT, IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_FLOAT, IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DEFAULT);
	CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_INVERSE, FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
}

void CANDSettingsContentsPage::OnCodingDecimal()
{
	CheckRadioButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DEFAULT, IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_FLOAT, IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DECIMAL);
	CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_INVERSE, FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
}

void CANDSettingsContentsPage::OnCodingBinary()
{
	CheckRadioButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DEFAULT, IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_FLOAT, IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_BINARY);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
}

void CANDSettingsContentsPage::OnCodingOctal()
{
	CheckRadioButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DEFAULT, IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_FLOAT, IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_OCTAL);
	CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_INVERSE, FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
}

void CANDSettingsContentsPage::OnCodingHexadecimal()
{
	CheckRadioButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DEFAULT, IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_FLOAT, IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_HEXADECIMAL);
	CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_INVERSE, FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
}

void CANDSettingsContentsPage::OnCodingFloat()
{
	CheckRadioButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_DEFAULT, IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_FLOAT, IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_FLOAT);
	CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_CODING_INVERSE, FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
}

void CANDSettingsContentsPage::OnCodingInverse()
{
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
}

void CANDSettingsContentsPage::OnAlignLeft()
{
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
}

void CANDSettingsContentsPage::OnAlignCenter()
{
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
}

void CANDSettingsContentsPage::OnAlignRight()
{
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
}

void CANDSettingsContentsPage::OnOccurrenceDefault()
{
	CheckDlgButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_PAST, FALSE);
	CheckRadioButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_DEFAULT, IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE, IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_DEFAULT);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_NUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
}

void CANDSettingsContentsPage::OnOccurrencePast()
{
	CheckRadioButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_DEFAULT, IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE, IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE);
	Spinbox_SetPos(GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_NUMBER), ANDSETTINGSCONTENTSPAGE_PARAMETER_DEFAULTOCCURRENCE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_NUMBER)->EnableWindow();
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_NUMBER)->SetFocus();
}

void CANDSettingsContentsPage::OnOccurrenceNumber()
{
	CheckRadioButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_DEFAULT, IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE, IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE);
	Spinbox_SetPos(GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_NUMBER), ANDSETTINGSCONTENTSPAGE_PARAMETER_DEFAULTOCCURRENCE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_NUMBER)->EnableWindow();
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_OCCURRENCE_NUMBER)->SetFocus();
}

void CANDSettingsContentsPage::OnSpinchangeOccurrence()
{
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
}

void CANDSettingsContentsPage::OnDigitsDefault()
{
	CheckRadioButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_DEFAULT, IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS, IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_DEFAULT);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_COUNT)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
}

void CANDSettingsContentsPage::OnDigitsCount()
{
	CheckRadioButton(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_DEFAULT, IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS, IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS);
	Spinbox_SetPos(GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_COUNT), ANDSETTINGSCONTENTSPAGE_PARAMETER_DEFAULTDIGITS);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_COUNT)->EnableWindow();
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_DIGITS_COUNT)->SetFocus();
}

void CANDSettingsContentsPage::OnSpinchangeDigits()
{
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
}

void CANDSettingsContentsPage::OnSelchangeTopics()
{
	INT  nIndex;

	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS_TEXT)->SetWindowText(((nIndex = (INT)SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS, CB_GETCURSEL)) >= 0 && nIndex < m_szTopicsText.GetSize()) ? m_szTopicsText.GetAt(nIndex) : EMPTYSTRING);
}

void CANDSettingsContentsPage::OnEditchangeTopicsText()
{
	INT  nIndex;
	CString  szText;

	for (GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS_TEXT)->GetWindowText(szText); (nIndex = (INT)SendDlgItemMessage(IDC_ANDSETTINGS_CONTENTSPAGE_PARAMETERS_TOPICS, CB_GETCURSEL)) >= 0; )
	{
		m_szTopicsText.SetAtGrow(nIndex, szText);
		break;
	}
	GetDlgItem(IDC_ANDSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CANDSettingsRetrievingPage property page

IMPLEMENT_DYNCREATE(CANDSettingsRetrievingPage, CLocalePropertyPage)

CANDSettingsRetrievingPage::CANDSettingsRetrievingPage() : CLocalePropertyPage(CANDSettingsRetrievingPage::IDD)
{
	//{{AFX_DATA_INIT(CANDSettingsRetrievingPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CANDSettingsRetrievingPage::Initialize()
{
	CANDOpenDialog  *pDialog;

	if (((pDialog = GetParentDialog()->GetParentDialog()) && pDialog->GetRetrieveFileName(m_szFileName[0])) || GetParentDisplay()->GetRetrieveFileName(m_szFileName[0]))
	{
		m_szFileName[1] = m_szFileName[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CANDSettingsRetrievingPage::GetDataSourceFileName(CString &szFileName) CONST
{
	szFileName = m_szFileName[0];
	return Check(FALSE);
}

CANDSettingsDialog *CANDSettingsRetrievingPage::GetParentDialog() CONST
{
	return((CANDSettingsDialog *)CLocalePropertyPage::GetParent());
}

CANDWnd *CANDSettingsRetrievingPage::GetParentDisplay() CONST
{
	return((CANDWnd *)GetParentDialog()->GetParentDisplay());
}

VOID CANDSettingsRetrievingPage::EnumDataSources()
{
	INT  nFile;
	INT  nFiles;
	CHistoryStoreFile  cFile;
	CHistoryStoreFiles  pFiles;
	CUIntArray  nOptions;

	for (nFile = 0, nFiles = GetTMService()->GetTMHistoryFiles(HISTORYFILE_TYPE_RETRIEVE, pFiles), GetTMService()->GetDefaultTMHistoryFile(HISTORYFILE_TYPE_RETRIEVE, cFile), m_szFileName[0] = (pFiles.Find(m_szFileName[0]) < 0) ? cFile.GetFileName() : m_szFileName[0]; nFile < nFiles || (!nFiles && !nFile && !m_szFileName[0].IsEmpty()); nFile++)
	{
		SendDlgItemMessage(IDC_ANDSETTINGS_RETRIEVINGPAGE_DATASOURCE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)((nFiles > 0) ? (LPCTSTR)pFiles.GetAt(nFile)->GetFileName() : (LPCTSTR)m_szFileName[0]));
		continue;
	}
	SendDlgItemMessage(IDC_ANDSETTINGS_RETRIEVINGPAGE_DATASOURCE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_ANDSETTINGS_RETRIEVINGPAGE_DATASOURCE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)m_szFileName[0]), 0));
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_DATASOURCE)->GetWindowText(m_szFileName[0]);
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_DATASOURCE)->GetWindowText(m_szFileName[1]);
	ShowDataSourceInfo();
}

VOID CANDSettingsRetrievingPage::ShowDataSourceInfo()
{
	CString  szProduct;
	CString  szCompany;
	CString  szTrademark;
	CString  szSpacecraft;
	CString  szStartTime;
	CString  szStopTime;
	CString  szCreationTime;
	CString  szDataSourceType;
	CString  szDataSourceSize;

	if (CheckDataSource(m_szFileName[0], szProduct, szCompany, szTrademark, szSpacecraft, szDataSourceType, szStartTime, szStopTime, szCreationTime, szDataSourceSize))
	{
		GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT)->SetWindowText(szProduct);
		GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY)->SetWindowText(szCompany);
		GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT)->SetWindowText(szSpacecraft);
		GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE)->SetWindowText(szDataSourceType);
		GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->SetWindowText(szStartTime);
		GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->SetWindowText(szStopTime);
		GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->SetWindowText(szCreationTime);
		GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE)->SetWindowText(szDataSourceSize);
	}
	else
	{
		GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT)->SetWindowText((szProduct = EMPTYSTRING));
		GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY)->SetWindowText((szCompany = EMPTYSTRING));
		GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT)->SetWindowText((szSpacecraft = EMPTYSTRING));
		GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE)->SetWindowText((szDataSourceType = EMPTYSTRING));
		GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->SetWindowText((szStartTime = EMPTYSTRING));
		GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->SetWindowText((szStopTime = EMPTYSTRING));
		GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->SetWindowText((szCreationTime = EMPTYSTRING));
		GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE)->SetWindowText((szDataSourceSize = EMPTYSTRING));
	}
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO)->EnableWindow();
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMMENTS)->EnableWindow(szProduct.IsEmpty());
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMMENTS)->ShowWindow((szProduct.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT_STATIC)->ShowWindow((!szProduct.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT_STATIC)->EnableWindow(!szProduct.IsEmpty());
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT)->ShowWindow((!szProduct.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT)->EnableWindow(!szProduct.IsEmpty());
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY_STATIC)->ShowWindow((!szCompany.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY_STATIC)->EnableWindow(!szCompany.IsEmpty());
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY)->ShowWindow((!szCompany.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY)->EnableWindow(!szCompany.IsEmpty());
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT_STATIC)->ShowWindow((!szSpacecraft.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT_STATIC)->EnableWindow(!szSpacecraft.IsEmpty());
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT)->ShowWindow((!szSpacecraft.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT)->EnableWindow(!szSpacecraft.IsEmpty());
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE_STATIC)->ShowWindow((!szDataSourceType.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE_STATIC)->EnableWindow(!szDataSourceType.IsEmpty());
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE)->ShowWindow((!szDataSourceType.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE)->EnableWindow(!szDataSourceType.IsEmpty());
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STATIC)->ShowWindow((GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STATIC)->EnableWindow((GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->ShowWindow((GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->EnableWindow((GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_TO)->ShowWindow((GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_TO)->EnableWindow((GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->ShowWindow((GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->EnableWindow((GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME_STATIC)->ShowWindow((GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME_STATIC)->EnableWindow((GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->ShowWindow((GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->EnableWindow((GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE_STATIC)->ShowWindow((!szDataSourceSize.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE_STATIC)->EnableWindow(!szDataSourceSize.IsEmpty());
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE)->ShowWindow((!szDataSourceSize.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE)->EnableWindow(!szDataSourceSize.IsEmpty());
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_INSPECT)->EnableWindow(!m_szFileName[0].IsEmpty());
}

BOOL CANDSettingsRetrievingPage::CheckDataSource(LPCTSTR pszFileName) CONST
{
	CString  szProduct;
	CString  szCompany;
	CString  szTrademark;
	CString  szSpacecraft;
	CString  szStartTime;
	CString  szStopTime;
	CString  szCreationTime;
	CString  szDataSourceType;
	CString  szDataSourceSize;

	return((CheckDataSource(pszFileName, szProduct, szCompany, szTrademark, szSpacecraft, szDataSourceType, szStartTime, szStopTime, szCreationTime, szDataSourceSize) && szSpacecraft == GetAccountSpacecraftName()) ? TRUE : FALSE);
}
BOOL CANDSettingsRetrievingPage::CheckDataSource(LPCTSTR pszFileName, CString &szProduct, CString &szCompany, CString &szTrademark, CString &szSpacecraft, CString &szDataSourceType, CString &szStartTime, CString &szStopTime, CString &szCreationTime, CString &szDataSourceSize) CONST
{
	CTimeKey  tTime;
	DWORDLONG  dwSize;
	CByteArray  nData;
	CFileFindEx  cFileFind;
	CHistoryFile  cHistoryFile;

	if (cFileFind.FindFile(pszFileName))
	{
		if (cHistoryFile.Open(pszFileName, (LPCTSTR)NULL, HISTORYSTORE_TYPE_TM, CFile::modeRead, TRUE) == HISTORYFILE_SUCCESS)
		{
			for (cHistoryFile.GetCopyrightProduct(szProduct), cHistoryFile.GetCopyrightCompany(szCompany), cHistoryFile.GetCopyrightTrademark(szTrademark), cHistoryFile.GetSpacecraft(szSpacecraft), cHistoryFile.GetType(szDataSourceType), szStartTime = (cHistoryFile.CLogFile::SeekToFirst() && cHistoryFile.CLogFile::Read(tTime, nData)) ? (LPCTSTR)tTime.FormatGmt(STRING(IDS_ANDSETTINGS_RETRIEVINGPAGE_SOURCEDATATIMEFORMAT)) : EMPTYSTRING, szStopTime = (cHistoryFile.CLogFile::SeekToLast() && cHistoryFile.CLogFile::Read(tTime, nData)) ? (LPCTSTR)tTime.FormatGmt(STRING(IDS_ANDSETTINGS_RETRIEVINGPAGE_SOURCEDATATIMEFORMAT)) : EMPTYSTRING, szCreationTime = (cHistoryFile.GetCopyrightCreationTime(tTime)) ? (LPCTSTR)tTime.FormatGmt(STRING(IDS_ANDSETTINGS_RETRIEVINGPAGE_SOURCEDATAFILETIMEFORMAT)) : EMPTYSTRING, szDataSourceSize.Format(STRING(IDS_ANDSETTINGS_RETRIEVINGPAGE_SOURCEDATASIZEFORMAT), ((dwSize = cHistoryFile.CLogFile::GetSize()) + 512) / 1024), szDataSourceSize = FormatDataSourceSize(szDataSourceSize); !szProduct.IsEmpty() && !szCompany.IsEmpty() && !szTrademark.IsEmpty(); )
			{
				cHistoryFile.Close();
				cFileFind.Close();
				return TRUE;
			}
			cHistoryFile.Close();
		}
		cFileFind.Close();
	}
	return FALSE;
}

CString CANDSettingsRetrievingPage::FormatDataSourceSize(LPCTSTR pszDataSourceSize) CONST
{
	INT  cbSep;
	CString  szSep;
	CString  szSize;
	CString  szNumber;

	for (szNumber = pszDataSourceSize; (cbSep = GetLocaleInfo(MAKELCID(GetLanguageID(), SORT_DEFAULT), LOCALE_STHOUSAND, (LPTSTR)NULL, 0)); )
	{
		if (GetLocaleInfo(MAKELCID(GetLanguageID(), SORT_DEFAULT), LOCALE_STHOUSAND, szSep.GetBufferSetLength(cbSep - 1), cbSep))
		{
			for (szNumber = szNumber.Left(lstrlen(szNumber)), szSize.Empty(), szSep.ReleaseBuffer(); szNumber.GetLength() > 0 && !_istdigit(szNumber[szNumber.GetLength() - 1]); )
			{
				szSize = szNumber.Right(1) + szSize, szNumber = szNumber.Left(szNumber.GetLength() - 1);
				continue;
			}
			for (; szNumber.GetLength() > 0; szNumber = szNumber.Left(max(szNumber.GetLength() - 3, 0)))
			{
				szSize = (_istdigit(szSize[0])) ? (szNumber.Right(min(szNumber.GetLength(), 3)) + szSep + szSize) : (szNumber.Right(min(szNumber.GetLength(), 3)) + szSize);
				continue;
			}
			return szSize;
		}
		szSep.ReleaseBuffer();
	}
	return szNumber;
}

BOOL CANDSettingsRetrievingPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? ((m_szFileName[0].CompareNoCase(m_szFileName[1])) ? TRUE : FALSE) : CLocalePropertyPage::IsModified()) : FALSE);
}

BOOL CANDSettingsRetrievingPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (m_szFileName[0].IsEmpty() || CheckDataSource(m_szFileName[0])) : CLocalePropertyPage::Check()) : TRUE);
}

void CANDSettingsRetrievingPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CANDSettingsRetrievingPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CANDSettingsRetrievingPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CANDSettingsRetrievingPage)
	ON_BN_CLICKED(IDC_ANDSETTINGS_RETRIEVINGPAGE_INSPECT, OnInspect)
	ON_CBN_EDITCHANGE(IDC_ANDSETTINGS_RETRIEVINGPAGE_DATASOURCE, OnEditchangeFileName)
	ON_CBN_SELCHANGE(IDC_ANDSETTINGS_RETRIEVINGPAGE_DATASOURCE, OnSelchangeFileName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDSettingsRetrievingPage message handlers

BOOL CANDSettingsRetrievingPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_DATASOURCE_STATIC)->EnableWindow();
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_DATASOURCE)->EnableWindow();
	EnumDataSources();
	return TRUE;
}

BOOL CANDSettingsRetrievingPage::OnSetActive()
{
	ShowDataSourceInfo();
	return CLocalePropertyPage::OnSetActive();
}

void CANDSettingsRetrievingPage::OnInspect()
{
	CHourglassCursor  cCursor;

	ShowDataSourceInfo();
}

void CANDSettingsRetrievingPage::OnEditchangeFileName()
{
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_DATASOURCE)->GetWindowText(m_szFileName[0]);
	GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_INSPECT)->EnableWindow(!m_szFileName[0].IsEmpty());
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsRetrievingPage::OnSelchangeFileName()
{
	for (m_szFileName[0] = Combobox_GetText(GetDlgItem(IDC_ANDSETTINGS_RETRIEVINGPAGE_DATASOURCE), (INT)SendDlgItemMessage(IDC_ANDSETTINGS_RETRIEVINGPAGE_DATASOURCE, CB_GETCURSEL)); !m_szFileName[0].IsEmpty(); )
	{
		ShowDataSourceInfo();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CANDSettingsPrintingComments

IMPLEMENT_DYNCREATE(CANDSettingsPrintingComments, CEdit)

BEGIN_MESSAGE_MAP(CANDSettingsPrintingComments, CEdit)
	//{{AFX_MSG_MAP(CANDSettingsPrintingComments)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDSettingsPrintingComments message handlers

void CANDSettingsPrintingComments::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
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
// CANDSettingsPrintingPage property page

IMPLEMENT_DYNCREATE(CANDSettingsPrintingPage, CLocalePropertyPage)

CANDSettingsPrintingPage::CANDSettingsPrintingPage() : CLocalePropertyPage(CANDSettingsPrintingPage::IDD)
{
	//{{AFX_DATA_INIT(CANDSettingsPrintingPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CANDSettingsPrintingPage::Initialize()
{
	CANDOpenDialog  *pDialog;

	return((((pDialog = GetParentDialog()->GetParentDialog()) && pDialog->GetPrintJobs(m_pJobs[0])) || GetParentDisplay()->GetPrintJobs(m_pJobs[0])) ? m_pJobs[1].Copy(&m_pJobs[0]) : FALSE);
}

BOOL CANDSettingsPrintingPage::GetJobs(CANDPrintJobs &pJobs) CONST
{
	return((pJobs.Copy(&m_pJobs[0])) ? Check(FALSE) : FALSE);
}

CANDSettingsDialog *CANDSettingsPrintingPage::GetParentDialog() CONST
{
	return((CANDSettingsDialog *)CLocalePropertyPage::GetParent());
}

CANDWnd *CANDSettingsPrintingPage::GetParentDisplay() CONST
{
	return((CANDWnd *)GetParentDialog()->GetParentDisplay());
}

VOID CANDSettingsPrintingPage::ShowJobInfo()
{
	UINT  nMode;
	UINT  nCount;
	UINT  nPrintFormat;
	CUIntArray  nColumns;
	CANDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		pJobInfo->SetPrintMode((nMode = (HasMultipleColumns()) ? (pJobInfo->GetPrintMode() & ~AND_PRINT_CUSTOMLAYOUT) : pJobInfo->GetPrintMode()));
		pJobInfo->SetPrintFormat((nPrintFormat = (pJobInfo->GetPrintFormat(nPrintFormat) && !HasMultipleColumns()) ? nPrintFormat : 0));
		CheckDlgButton(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL, (nMode & AND_PRINT_ALL) ? TRUE : FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE, ((nMode & AND_PRINT_FIRSTSIDE) || (nMode & AND_PRINT_LASTSIDE)) ? TRUE : FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL, (nMode & AND_PRINT_UNDERLINEOOL) ? TRUE : FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND, (nMode & AND_PRINT_COLORLEGEND) ? TRUE : FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_GENERIC, (!(nMode & AND_PRINT_CUSTOMLAYOUT)) ? TRUE : FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_COLUMNS, (nMode & AND_PRINT_CUSTOMLAYOUT) ? TRUE : FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS, (nMode & AND_PRINT_CLEARCOMMENTS) ? TRUE : FALSE);
		SendDlgItemMessage(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetProfile()));
		SendDlgItemMessage(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_SELECTTEXT, (WPARAM)-1, (nMode & AND_PRINT_FIRSTSIDE) ? (LPARAM)STRING(IDS_ANDSETTINGS_PRINTINGPAGE_FIRSTSIDE) : ((nMode & AND_PRINT_LASTSIDE) ? (LPARAM)STRING(IDS_ANDSETTINGS_PRINTINGPAGE_LASTSIDE) : (LPARAM)EMPTYSTRING));
		Spinbox_SetPos(GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT), (pJobInfo->GetPrintBySide(nCount)) ? nCount : 0);
		Spinbox_SetPos(GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_COLUMNS_COUNT), (pJobInfo->GetPrintFormat(nPrintFormat)) ? nPrintFormat : 0);
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->SetWindowText(pJobInfo->GetComments());
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_ADDNAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_REMOVENAME)->EnableWindow((pJobInfo->GetName() != STRING(IDS_PRINTJOB_DEFAULTNAME)) ? TRUE : FALSE);
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_REMOVEALLNAMES)->EnableWindow((SendDlgItemMessage(IDC_ANDSETTINGS_PRINTINGPAGE_NAME, CB_GETCOUNT) > 1) ? TRUE : FALSE);
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE_STATIC)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_OPTIONS)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE)->EnableWindow(IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE));
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE));
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)->EnableWindow(IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE));
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_STATIC)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_GENERIC)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_COLUMNS)->EnableWindow(!HasMultipleColumns());
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_COLUMNS_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_COLUMNS));
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_COLUMNS_COUNT)->EnableWindow(IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_COLUMNS));
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTS)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT_STATIC)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)->EnableWindow(!pJobInfo->GetComments().IsEmpty());
		return;
	}
	SendDlgItemMessage(IDC_ANDSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)-1);
	SendDlgItemMessage(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_SETCURSEL, (WPARAM)-1);
	CheckDlgButton(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL, FALSE);
	CheckDlgButton(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE, FALSE);
	CheckDlgButton(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL, FALSE);
	CheckDlgButton(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND, FALSE);
	CheckDlgButton(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_GENERIC, FALSE);
	CheckDlgButton(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_COLUMNS, FALSE);
	CheckDlgButton(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS, FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_ADDNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_REMOVENAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_REMOVEALLNAMES)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_OPTIONS)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_GENERIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_COLUMNS)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_COLUMNS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_COLUMNS_COUNT)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTS)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)->EnableWindow(FALSE);
}

CANDPrintJobInfo *CANDSettingsPrintingPage::FindJobInfo() CONST
{
	CString  szJobName;

	GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_NAME)->GetWindowText(szJobName);
	return m_pJobs[0].GetAt(m_pJobs[0].Find(szJobName));
}

BOOL CANDSettingsPrintingPage::HasMultipleColumns() CONST
{
	INT  nIndex;
	INT  nCount;
	INT  nColumnGroup;
	CANDLayout  cLayout;
	CUIntArray  nColumns;

	for (nIndex = 0, nCount = (GetParentDialog()->GetLayout(cLayout, nColumns)) ? (INT)nColumns.GetSize() : -1, nColumnGroup = 0; nIndex < nCount; nIndex++)
	{
		nColumnGroup = (nColumns.GetAt(nIndex) == AND_TITLEITEM_ID) ? (nColumnGroup + 1) : nColumnGroup;
		continue;
	}
	return((nColumnGroup > 1) ? TRUE : FALSE);
}

BOOL CANDSettingsPrintingPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? !m_pJobs[0].Compare(&m_pJobs[1]) : CLocalePropertyPage::IsModified()) : FALSE);
}

BOOL CANDSettingsPrintingPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? ((GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_NAME)->GetWindowTextLength() > 0 && FindJobInfo()) ? TRUE : FALSE) : CLocalePropertyPage::Check()) : TRUE);
}

void CANDSettingsPrintingPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CANDSettingsPrintingPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CANDSettingsPrintingPage::PostNcDestroy()
{
	m_pJobs[0].RemoveAll();
	m_pJobs[1].RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CANDSettingsPrintingPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CANDSettingsPrintingPage)
	ON_BN_CLICKED(IDC_ANDSETTINGS_PRINTINGPAGE_ADDNAME, OnAddName)
	ON_BN_CLICKED(IDC_ANDSETTINGS_PRINTINGPAGE_REMOVENAME, OnRemoveName)
	ON_BN_CLICKED(IDC_ANDSETTINGS_PRINTINGPAGE_REMOVEALLNAMES, OnRemoveAllNames)
	ON_BN_CLICKED(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL, OnPrintAll)
	ON_BN_CLICKED(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE, OnPrintBySide)
	ON_BN_CLICKED(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL, OnPrintUnderlineOOL)
	ON_BN_CLICKED(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND, OnPrintColorLegend)
	ON_BN_CLICKED(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_GENERIC, OnPrintGenericFormat)
	ON_BN_CLICKED(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_COLUMNS, OnPrintCustomFormat)
	ON_BN_CLICKED(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS, OnResetComments)
	ON_CBN_EDITCHANGE(IDC_ANDSETTINGS_PRINTINGPAGE_NAME, OnEditchangeName)
	ON_CBN_SELCHANGE(IDC_ANDSETTINGS_PRINTINGPAGE_NAME, OnSelchangeName)
	ON_CBN_SELCHANGE(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, OnSelchangeProfile)
	ON_EN_CHANGE(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, OnChangePrintSide)
	ON_EN_CHANGE(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT, OnEditchangeComments)
	ON_CONTROL(SBXN_CHANGE, IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT, OnSpinchangePrintSideCount)
	ON_CONTROL(SBXN_CHANGE, IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_COLUMNS_COUNT, OnSpinchangePrintColumns)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDSettingsPrintingPage message handlers

BOOL CANDSettingsPrintingPage::OnInitDialog()
{
	INT  nJob;
	INT  nJobs;
	INT  nProfile;
	INT  nProfiles;
	CStringArray  szProfiles;
	CANDPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	for (CLocalePropertyPage::OnInitDialog(); m_wndComments.SubclassWindow(GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->GetSafeHwnd()); )
	{
		for (nJob = 0, nJobs = (INT)m_pJobs[0].GetSize(); nJob < nJobs; nJob++)
		{
			if ((pJobInfo = m_pJobs[0].GetAt(nJob)) != (CANDPrintJobInfo *)NULL)
			{
				SendDlgItemMessage(IDC_ANDSETTINGS_PRINTINGPAGE_NAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pJobInfo->GetName());
				continue;
			}
		}
		for (nProfile = 0, nProfiles = (EnumPrintProfiles(szProfiles)) ? (INT)szProfiles.GetSize() : 0; nProfile < nProfiles; nProfile++)
		{
			SendDlgItemMessage(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szProfiles.GetAt(nProfile));
			continue;
		}
		Spinbox_SetRange(GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT), ANDSETTINGSPRINTINGPAGE_OPTIONS_MINIMUMPARAMETERS, ANDSETTINGSPRINTINGPAGE_OPTIONS_MAXIMUMPARAMETERS);
		Spinbox_SetRange(GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_COLUMNS_COUNT), ANDSETTINGSPRINTINGPAGE_OPTIONS_MINIMUMCOLUMNS, ANDSETTINGSPRINTINGPAGE_OPTIONS_MAXIMUMCOLUMNS);
		SendDlgItemMessage(IDC_ANDSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_ANDSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_PRINTJOB_DEFAULTNAME)));
		SendDlgItemMessage(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_ADDTEXT, (WPARAM)NULL, (LPARAM)STRING(IDS_ANDSETTINGS_PRINTINGPAGE_FIRSTSIDE));
		SendDlgItemMessage(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_ADDTEXT, (WPARAM)NULL, (LPARAM)STRING(IDS_ANDSETTINGS_PRINTINGPAGE_LASTSIDE));
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_DETAILS)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_NAME_STATIC)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_NAME)->EnableWindow();
		ShowJobInfo();
		break;
	}
	return TRUE;
}

BOOL CANDSettingsPrintingPage::OnSetActive()
{
	ShowJobInfo();
	return CLocalePropertyPage::OnSetActive();
}

BOOL CANDSettingsPrintingPage::OnKillActive()
{
	GetParentDialog()->OnDataExchange(GetSafeHwnd(), m_pJobs[0]);
	return CLocalePropertyPage::OnKillActive();
}

BOOL CANDSettingsPrintingPage::OnDataExchange(CONST CANDPrintJobs &pJobs)
{
	return m_pJobs[0].Copy(&pJobs);
}

void CANDSettingsPrintingPage::OnEditchangeName()
{
	CString  szJobName;
	CANDPrintJobInfo  *pJobInfo;

	for (GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_NAME)->GetWindowText(szJobName); (pJobInfo = FindJobInfo()); )
	{
		ShowJobInfo();
		return;
	}
	GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_ADDNAME)->EnableWindow((!pJobInfo  &&  szJobName.GetLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_REMOVENAME)->EnableWindow((pJobInfo != (CANDPrintJobInfo *)NULL  &&  szJobName != STRING(IDS_PRINTJOB_DEFAULTNAME)) ? TRUE : FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_REMOVEALLNAMES)->EnableWindow((SendDlgItemMessage(IDC_ANDSETTINGS_PRINTINGPAGE_NAME, CB_GETCOUNT) > 1) ? TRUE : FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)->EnableWindow((szJobName != STRING(IDS_PRINTJOB_DEFAULTNAME)) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsPrintingPage::OnSelchangeName()
{
	SendDlgItemMessage(IDC_ANDSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_ANDSETTINGS_PRINTINGPAGE_NAME, CB_GETCURSEL));
	ShowJobInfo();
}

void CANDSettingsPrintingPage::OnAddName()
{
	INT  nIndex;
	UINT  nMode;
	UINT  nCount;
	UINT  nFormat;
	CString  szJobName;
	CString  szProfile;
	CString  szComments;
	CANDPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	for (; (pJobInfo = new CANDPrintJobInfo); )
	{
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_NAME)->GetWindowText(szJobName);
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE)->GetWindowText(szProfile);
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->GetWindowText(szComments);
		nMode = (IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL)) ? ((pJobInfo->GetPrintMode() | AND_PRINT_ALL) & ~(AND_PRINT_FIRSTSIDE | AND_PRINT_LASTSIDE)) : pJobInfo->GetPrintMode();
		nMode = (IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE)) ? ((!GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE)->SendMessage(TEM_GETPOS)) ? ((nMode | AND_PRINT_FIRSTSIDE) & ~(AND_PRINT_ALL | AND_PRINT_LASTSIDE)) : ((nMode | AND_PRINT_LASTSIDE) & ~(AND_PRINT_ALL | AND_PRINT_FIRSTSIDE))) : nMode;
		nMode = (IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL)) ? (nMode | AND_PRINT_UNDERLINEOOL) : nMode;
		nMode = (IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND)) ? (nMode | AND_PRINT_COLORLEGEND) : nMode;
		nMode = (IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_COLUMNS)) ? (nMode | AND_PRINT_CUSTOMLAYOUT) : nMode;
		nMode = (IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)) ? (nMode | AND_PRINT_CLEARCOMMENTS) : (nMode & ~AND_PRINT_CLEARCOMMENTS);
		nCount = ((nMode & AND_PRINT_FIRSTSIDE) || (nMode & AND_PRINT_LASTSIDE)) ? (UINT)Spinbox_GetPos(GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)) : 0;
		nFormat = (nMode & AND_PRINT_CUSTOMLAYOUT) ? (UINT)Spinbox_GetPos(GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_COLUMNS_COUNT)) : 0;
		if (SendDlgItemMessage(IDC_ANDSETTINGS_PRINTINGPAGE_NAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szJobName) >= 0 && SendDlgItemMessage(IDC_ANDSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_ANDSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szJobName)) >= 0)
		{
			for (pJobInfo->SetName(szJobName), pJobInfo->SetProfile(szProfile), pJobInfo->SetComments(szComments), pJobInfo->SetPrintMode(nMode), pJobInfo->SetPrintBySide(nCount), pJobInfo->SetPrintFormat(nFormat); (nIndex = m_pJobs[0].Add(pJobInfo)) >= 0; )
			{
				ShowJobInfo();
				break;
			}
			if (nIndex >= 0) break;
		}
		delete pJobInfo;
		break;
	}
	GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsPrintingPage::OnRemoveName()
{
	INT  nJob;
	INT  nJobs;
	CANDPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	for (nJob = 0, nJobs = (INT)m_pJobs[0].GetSize(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = m_pJobs[0].GetAt(nJob)) && pJobInfo == FindJobInfo())
		{
			if (SendDlgItemMessage(IDC_ANDSETTINGS_PRINTINGPAGE_NAME, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_ANDSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName())) > 0)
			{
				m_pJobs[0].RemoveAt(nJob);
				delete pJobInfo;
			}
			break;
		}
	}
	for (; SendDlgItemMessage(IDC_ANDSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_ANDSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_PRINTJOB_DEFAULTNAME))) >= 0; )
	{
		ShowJobInfo();
		break;
	}
	GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsPrintingPage::OnRemoveAllNames()
{
	INT  nJob;
	INT  nJobs;
	CANDPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	for (nJob = 0, nJobs = (INT)m_pJobs[0].GetSize(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = m_pJobs[0].GetAt(nJob)) && pJobInfo->GetName() != STRING(IDS_PRINTJOB_DEFAULTNAME) && SendDlgItemMessage(IDC_ANDSETTINGS_PRINTINGPAGE_NAME, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_ANDSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName())) > 0)
		{
			m_pJobs[0].RemoveAt(nJob);
			delete pJobInfo;
			nJobs--;
			nJob--;
		}
	}
	for (; SendDlgItemMessage(IDC_ANDSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_ANDSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_PRINTJOB_DEFAULTNAME))) >= 0; )
	{
		ShowJobInfo();
		break;
	}
	GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsPrintingPage::OnSelchangeProfile()
{
	CString  szProfile;
	CANDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE)->GetWindowText(szProfile);
		pJobInfo->SetProfile(szProfile);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsPrintingPage::OnPrintAll()
{
	CANDPrintJobInfo  *pJobInfo;

	if (!IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL))
	{
		for (CheckDlgButton(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL, TRUE), CheckDlgButton(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE, FALSE), SendDlgItemMessage(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_SELECTTEXT, (WPARAM)-1, (LPARAM)EMPTYSTRING); (pJobInfo = FindJobInfo()); )
		{
			pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | AND_PRINT_ALL) & ~(AND_PRINT_FIRSTSIDE | AND_PRINT_LASTSIDE));
			break;
		}
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_ADDNAME)->EnableWindow((GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_NAME)->GetWindowTextLength() > 0 && SendDlgItemMessage(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_GETCURSEL) != CB_ERR  &&  !pJobInfo) ? TRUE : FALSE);
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE_STATIC)->EnableWindow(FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsPrintingPage::OnPrintBySide()
{
	CANDPrintJobInfo  *pJobInfo;

	if (!IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE))
	{
		for (CheckDlgButton(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL, FALSE), CheckDlgButton(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE, TRUE), SendDlgItemMessage(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_SELECTTEXT, (WPARAM)-1, (LPARAM)STRING(IDS_ANDSETTINGS_PRINTINGPAGE_FIRSTSIDE)), Spinbox_SetPos(GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT), ANDSETTINGSPRINTINGPAGE_OPTIONS_DEFAULTPARAMETERS); (pJobInfo = FindJobInfo()); )
		{
			pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | AND_PRINT_FIRSTSIDE) & ~(AND_PRINT_ALL | AND_PRINT_LASTSIDE));
			pJobInfo->SetPrintBySide(ANDSETTINGSPRINTINGPAGE_OPTIONS_DEFAULTPARAMETERS);
			break;
		}
		SendDlgItemMessage(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, EM_SETSEL, 0, (LPARAM)-1);
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_ADDNAME)->EnableWindow((GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_NAME)->GetWindowTextLength() > 0 && SendDlgItemMessage(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_GETCURSEL) != CB_ERR  &&  !pJobInfo) ? TRUE : FALSE);
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE_STATIC)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE)->SetFocus();
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsPrintingPage::OnPrintUnderlineOOL()
{
	UINT  nMode;
	CANDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		nMode = (IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL)) ? (pJobInfo->GetPrintMode() | AND_PRINT_UNDERLINEOOL) : (pJobInfo->GetPrintMode() & ~AND_PRINT_UNDERLINEOOL);
		pJobInfo->SetPrintMode(nMode);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsPrintingPage::OnPrintColorLegend()
{
	UINT  nMode;
	CANDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		nMode = (IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND)) ? (pJobInfo->GetPrintMode() | AND_PRINT_COLORLEGEND) : (pJobInfo->GetPrintMode() & ~AND_PRINT_COLORLEGEND);
		pJobInfo->SetPrintMode(nMode);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsPrintingPage::OnPrintGenericFormat()
{
	UINT  nMode;
	CANDPrintJobInfo  *pJobInfo;

	if (!IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_GENERIC))
	{
		for (CheckDlgButton(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_GENERIC, TRUE), CheckDlgButton(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_COLUMNS, FALSE); (pJobInfo = FindJobInfo()); )
		{
			nMode = pJobInfo->GetPrintMode() & ~AND_PRINT_CUSTOMLAYOUT;
			pJobInfo->SetPrintMode(nMode);
			break;
		}
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_COLUMNS_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_COLUMNS_COUNT)->EnableWindow(FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsPrintingPage::OnPrintCustomFormat()
{
	CANDPrintJobInfo  *pJobInfo;

	if (!IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_COLUMNS))
	{
		for (CheckDlgButton(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_GENERIC, FALSE), CheckDlgButton(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_COLUMNS, TRUE), Spinbox_SetPos(GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_COLUMNS_COUNT), ANDSETTINGSPRINTINGPAGE_OPTIONS_DEFAULTCOLUMNS); (pJobInfo = FindJobInfo()); )
		{
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() | AND_PRINT_CUSTOMLAYOUT);
			pJobInfo->SetPrintFormat(ANDSETTINGSPRINTINGPAGE_OPTIONS_DEFAULTCOLUMNS);
			break;
		}
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_COLUMNS_STATIC)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_COLUMNS_COUNT)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_COLUMNS_COUNT)->SetFocus();
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsPrintingPage::OnChangePrintSide()
{
	UINT  nMode;
	CANDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		nMode = (!SendDlgItemMessage(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_GETPOS)) ? ((pJobInfo->GetPrintMode() | AND_PRINT_FIRSTSIDE) & ~(AND_PRINT_ALL | AND_PRINT_LASTSIDE)) : ((pJobInfo->GetPrintMode() | AND_PRINT_LASTSIDE) & ~(AND_PRINT_ALL | AND_PRINT_FIRSTSIDE));
		pJobInfo->SetPrintMode(nMode);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsPrintingPage::OnSpinchangePrintSideCount()
{
	CANDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo())) pJobInfo->SetPrintBySide((UINT)Spinbox_GetPos(GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsPrintingPage::OnSpinchangePrintColumns()
{
	CANDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo())) pJobInfo->SetPrintFormat((UINT)Spinbox_GetPos(GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FORMAT_COLUMNS_COUNT)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsPrintingPage::OnEditchangeComments()
{
	CString  szComments;
	CANDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->GetWindowText(szComments);
		GetDlgItem(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)->EnableWindow(!szComments.IsEmpty());
		CheckDlgButton(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS, (!szComments.IsEmpty()) ? IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS) : FALSE);
		pJobInfo->SetPrintMode((IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)) ? (pJobInfo->GetPrintMode() | AND_PRINT_CLEARCOMMENTS) : (pJobInfo->GetPrintMode() & ~AND_PRINT_CLEARCOMMENTS));
		pJobInfo->SetComments(szComments);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsPrintingPage::OnResetComments()
{
	UINT  nMode;
	CANDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		nMode = (IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)) ? (pJobInfo->GetPrintMode() | AND_PRINT_CLEARCOMMENTS) : (pJobInfo->GetPrintMode() & ~AND_PRINT_CLEARCOMMENTS);
		pJobInfo->SetPrintMode(nMode);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CANDSettingsPrintJobsPage property page

IMPLEMENT_DYNCREATE(CANDSettingsPrintJobsPage, CLocalePropertyPage)

CANDSettingsPrintJobsPage::CANDSettingsPrintJobsPage() : CLocalePropertyPage(CANDSettingsPrintJobsPage::IDD)
{
	//{{AFX_DATA_INIT(CANDSettingsPrintJobsPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CANDSettingsPrintJobsPage::Initialize()
{
	CANDOpenDialog  *pDialog;

	return((((pDialog = GetParentDialog()->GetParentDialog()) && pDialog->GetPrintJobs(m_pJobs[0])) || GetParentDisplay()->GetPrintJobs(m_pJobs[0])) ? m_pJobs[1].Copy(&m_pJobs[0]) : FALSE);
}

BOOL CANDSettingsPrintJobsPage::GetJobs(CANDPrintJobs &pJobs) CONST
{
	return((pJobs.Copy(&m_pJobs[0])) ? Check(FALSE) : FALSE);
}

CANDSettingsDialog *CANDSettingsPrintJobsPage::GetParentDialog() CONST
{
	return((CANDSettingsDialog *)CLocalePropertyPage::GetParent());
}

CANDWnd *CANDSettingsPrintJobsPage::GetParentDisplay() CONST
{
	return((CANDWnd *)GetParentDialog()->GetParentDisplay());
}

BOOL CANDSettingsPrintJobsPage::EnumJobs()
{
	INT  nJob;
	INT  nJobs;
	UINT  nMode;
	CANDPrintJobInfo  *pJobInfo;

	SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, LB_RESETCONTENT);
	SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_RESETCONTENT);
	for (nJob = 0, nJobs = (INT)m_pJobs[0].GetSize(); nJob < nJobs; nJob = nJob + 1)
	{
		if ((pJobInfo = m_pJobs[0].GetAt(nJob)) && pJobInfo->GetName() != STRING(IDS_PRINTJOB_DEFAULTNAME))
		{
			if (SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pJobInfo->GetName()) >= 0)
			{
				if (((nMode = pJobInfo->GetPrintMode()) & AND_PRINT_ACTIVE) && ((nMode & AND_PRINT_ATTIME) || (nMode & AND_PRINT_ATDAILYTIME) || (nMode & AND_PRINT_ATEVENT)))
				{
					if (SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR)
					{
						pJobInfo->SetPrintMode(nMode & ~(AND_PRINT_ACTIVE | AND_PRINT_ATTIME | AND_PRINT_ATDAILYTIME | AND_PRINT_ATEVENT | AND_PRINT_REPEATBYINTERVAL | AND_PRINT_REPEATSTOPBYCOUNT | AND_PRINT_REPEATSTOPBYTIME | AND_PRINT_DAILYREPEATSTOPBYCOUNT | AND_PRINT_DAILYREPEATSTOPBYTIME));
						continue;
					}
				}
			}
		}
	}
	if (SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, LB_GETCOUNT) > 0)
	{
		SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, LB_SETCURSEL);
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_DETAILS)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS_STATIC)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS)->EnableWindow((SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)Listbox_GetText(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS), (INT)SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, LB_GETCURSEL))) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_REMOVEJOB)->EnableWindow((SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
		ShowJobInfo();
		return TRUE;
	}
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_DETAILS)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_REMOVEJOB)->EnableWindow(FALSE);
	ShowJobInfo();
	return FALSE;
}

BOOL CANDSettingsPrintJobsPage::EnumEvents()
{
	INT  nEvent;
	INT  nEvents;
	CTelemetryEvents  pEvents;
	CTelemetryEventInfo  *pEventInfo;

	for (nEvent = 0, nEvents = (GetTelemetryEvents(pEvents)) ? (INT)pEvents.GetSize() : 0; nEvent < nEvents; nEvent++)
	{
		if ((pEventInfo = (CTelemetryEventInfo *)pEvents.GetAt(nEvent)) != (CTelemetryEventInfo *)NULL)
		{
			SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pEventInfo->GetName());
			continue;
		}
	}
	return((SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CANDSettingsPrintJobsPage::ShowJobInfo()
{
	UINT  nStopCount;
	CString  szEvent;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CTimeSpan  tDailyTime;
	CANDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		Timespinbox_SetTime(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME), (pJobInfo->GetPrintAtTime(tTime) || pJobInfo->GetPrintAtTime(tTime, tInterval) || pJobInfo->GetPrintAtTime(tTime, tInterval, nStopCount) || pJobInfo->GetPrintAtTime(tTime, tInterval, tStopTime)) ? tTime : CTime::GetCurrentTime().GetTime());
		Timespinbox_SetTime(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME), (pJobInfo->GetPrintAtDailyTime(tDailyTime) || pJobInfo->GetPrintAtDailyTime(tDailyTime, nStopCount) || pJobInfo->GetPrintAtDailyTime(tDailyTime, tStopTime)) ? CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + tDailyTime.GetTotalSeconds()) : CTime::GetCurrentTime().GetTime());
		SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_SETCURSEL, (pJobInfo->GetPrintAtEvent(szEvent)) ? (WPARAM)SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szEvent) : (WPARAM)-1);
		SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, (SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_ANDSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS)) < 0 && (pJobInfo->GetPrintMode() & AND_PRINT_ATTIME)) ? CB_ADDSTRING : CB_FINDSTRING, (WPARAM)NULL, (LPARAM)STRING(IDS_ANDSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS));
		SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, (SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_ANDSETTINGS_PRINTJOBSPAGE_DAILYPRINTS)) < 0 && (pJobInfo->GetPrintMode() & AND_PRINT_ATDAILYTIME)) ? CB_ADDSTRING : CB_FINDSTRING, (WPARAM)NULL, (LPARAM)STRING(IDS_ANDSETTINGS_PRINTJOBSPAGE_DAILYPRINTS));
		SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_SETCURSEL, ((pJobInfo->GetPrintMode() & AND_PRINT_ATTIME) || (pJobInfo->GetPrintMode() & AND_PRINT_ATDAILYTIME)) ? (WPARAM)SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)((pJobInfo->GetPrintMode() & AND_PRINT_ATTIME) ? STRING(IDS_ANDSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS) : STRING(IDS_ANDSETTINGS_PRINTJOBSPAGE_DAILYPRINTS))) : (WPARAM)-1);
		CheckDlgButton(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME, (pJobInfo->GetPrintMode() & AND_PRINT_ATTIME) ? TRUE : FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME, (pJobInfo->GetPrintMode() & AND_PRINT_ATDAILYTIME) ? TRUE : FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT, (pJobInfo->GetPrintMode() & AND_PRINT_ATEVENT) ? ((SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_GETCURSEL) >= 0) ? TRUE : FALSE) : FALSE);
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)->EnableWindow(IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME));
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)->EnableWindow();
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)->EnableWindow(IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT)->EnableWindow((SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT)->EnableWindow(IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT));
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT));
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION)->EnableWindow(IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE)->EnableWindow(IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		SetJobRepetitionInfo();
		return;
	}
	CheckDlgButton(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME, FALSE);
	CheckDlgButton(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME, FALSE);
	CheckDlgButton(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT, FALSE);
	CheckDlgButton(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME, FALSE);
	CheckDlgButton(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, FALSE);
	CheckDlgButton(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, FALSE);
	SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_SETCURSEL, (WPARAM)-1);
	SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_SETCURSEL, (WPARAM)-1);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow(FALSE);
}

BOOL CANDSettingsPrintJobsPage::CheckJobInfo() CONST
{
	UINT  nStopCount;
	CString  szEvent;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CTimeSpan  tDailyTime;
	CANDPrintJobInfo  *pJobInfo;

	return(((pJobInfo = FindJobInfo())) ? ((pJobInfo->GetPrintAtTime(tTime) && tTime > CTime::GetCurrentTime()) || pJobInfo->GetPrintAtTime(tTime, tInterval) || (pJobInfo->GetPrintAtTime(tTime, tInterval, nStopCount) && tTime.GetTime() + tInterval.GetTotalSeconds()*(TIMEKEY)nStopCount > CTime::GetCurrentTime().GetTime()) || (pJobInfo->GetPrintAtTime(tTime, tInterval, tStopTime) && tStopTime > CTime::GetCurrentTime()) || pJobInfo->GetPrintAtDailyTime(tDailyTime) || pJobInfo->GetPrintAtDailyTime(tDailyTime, nStopCount) || (pJobInfo->GetPrintAtDailyTime(tDailyTime, tStopTime) && tStopTime > CTime::GetCurrentTime()) || pJobInfo->GetPrintAtEvent(szEvent)) : FALSE);
}

CANDPrintJobInfo *CANDSettingsPrintJobsPage::FindJobInfo(BOOL bActive) CONST
{
	INT  nJob;
	INT  nJobs;
	CString  szJobName[2];
	CANDPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (INT)m_pJobs[0].GetSize(), szJobName[0] = Listbox_GetText(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS), (INT)GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS)->SendMessage(LB_GETCURSEL)), szJobName[1] = Listbox_GetText(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS), (INT)GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS)->SendMessage(LB_GETCURSEL)), szJobName[0] = (!bActive) ? szJobName[0] : szJobName[1]; nJob < nJobs; nJob++)
	{
		if ((pJobInfo = m_pJobs[0].GetAt(nJob)) && pJobInfo->GetName() == szJobName[0]) break;
		continue;
	}
	return((nJob < nJobs) ? pJobInfo : (CANDPrintJobInfo *)NULL);
}

VOID CANDSettingsPrintJobsPage::SetJobRepetitionInfo()
{
	UINT  nStopCount;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CTimeSpan  tDailyTime;
	CANDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		Timespinbox_SetTime(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), ((GetJobRepetitionType() == ANDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  pJobInfo->GetPrintAtTime(tTime, tInterval, tStopTime)) || (GetJobRepetitionType() == ANDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  pJobInfo->GetPrintAtDailyTime(tDailyTime, tStopTime))) ? tStopTime : CTime::GetCurrentTime().GetTime());
		Spinbox_SetPos(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME), (pJobInfo->GetPrintAtTime(tTime, tInterval) || pJobInfo->GetPrintAtTime(tTime, tInterval, nStopCount) || pJobInfo->GetPrintAtTime(tTime, tInterval, tStopTime)) ? (tInterval.GetTotalSeconds() / SECONDSPERMINUTE) : 0);
		Spinbox_SetPos(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), ((GetJobRepetitionType() == ANDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  pJobInfo->GetPrintAtTime(tTime, tInterval, nStopCount)) || (GetJobRepetitionType() == ANDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  pJobInfo->GetPrintAtDailyTime(tDailyTime, nStopCount))) ? nStopCount : 0);
		CheckDlgButton(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME, (GetJobRepetitionType() == ANDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY && (pJobInfo->GetPrintMode() & AND_PRINT_REPEATBYINTERVAL)) ? TRUE : FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, ((GetJobRepetitionType() == ANDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY && (pJobInfo->GetPrintMode() & AND_PRINT_REPEATSTOPBYCOUNT)) || (GetJobRepetitionType() == ANDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY && (pJobInfo->GetPrintMode() & AND_PRINT_DAILYREPEATSTOPBYCOUNT))) ? TRUE : FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, ((GetJobRepetitionType() == ANDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY && (pJobInfo->GetPrintMode() & AND_PRINT_REPEATSTOPBYTIME)) || (GetJobRepetitionType() == ANDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY && (pJobInfo->GetPrintMode() & AND_PRINT_DAILYREPEATSTOPBYTIME))) ? TRUE : FALSE);
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)->EnableWindow((GetJobRepetitionType() == ANDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY) ? TRUE : FALSE);
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)->EnableWindow(GetJobRepetitionType() == ANDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC)->EnableWindow(GetJobRepetitionType() == ANDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC)->EnableWindow((IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && (GetJobRepetitionType() == ANDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY || IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)));
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)->EnableWindow((IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && (GetJobRepetitionType() == ANDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY || IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)));
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow((IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES));
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow((IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES));
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)->EnableWindow((IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && (GetJobRepetitionType() == ANDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY || IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)));
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow((IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME));
		return;
	}
	CheckDlgButton(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME, FALSE);
	CheckDlgButton(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, FALSE);
	CheckDlgButton(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow(FALSE);
}

UINT CANDSettingsPrintJobsPage::GetJobRepetitionType() CONST
{
	CString  szRepetitionType;

	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE)->GetWindowText(szRepetitionType);
	return((szRepetitionType == STRING(IDS_ANDSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS) || szRepetitionType == STRING(IDS_ANDSETTINGS_PRINTJOBSPAGE_DAILYPRINTS)) ? ((szRepetitionType == STRING(IDS_ANDSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS)) ? ANDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY : ANDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY) : 0);
}

BOOL CANDSettingsPrintJobsPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? !m_pJobs[0].Compare(&m_pJobs[1]) : CLocalePropertyPage::IsModified()) : FALSE);
}

BOOL CANDSettingsPrintJobsPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? TRUE : CLocalePropertyPage::Check()) : TRUE);
}

void CANDSettingsPrintJobsPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CANDSettingsPrintJobsPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CANDSettingsPrintJobsPage::PostNcDestroy()
{
	m_pJobs[0].RemoveAll();
	m_pJobs[1].RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CANDSettingsPrintJobsPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CANDSettingsPrintJobsPage)
	ON_BN_CLICKED(IDC_ANDSETTINGS_PRINTJOBSPAGE_ADDJOB, OnAddJob)
	ON_BN_CLICKED(IDC_ANDSETTINGS_PRINTJOBSPAGE_REMOVEJOB, OnRemoveJob)
	ON_BN_CLICKED(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME, OnPrintAtTime)
	ON_BN_CLICKED(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME, OnPrintAtDailyTime)
	ON_BN_CLICKED(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT, OnPrintAtEvent)
	ON_BN_CLICKED(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME, OnRepeatByTime)
	ON_BN_CLICKED(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, OnRepetitionStopByCopies)
	ON_BN_CLICKED(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, OnRepetitionStopByTime)
	ON_CBN_SELCHANGE(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, OnSelchangeEvent)
	ON_CBN_SELCHANGE(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, OnSelchangeRepetitionType)
	ON_LBN_SELCHANGE(IDC_ANDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, OnSelchangeDefinedJob)
	ON_LBN_SELCHANGE(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, OnSelchangeActiveJob)
	ON_CONTROL(SBXN_CHANGE, IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME, OnSpinchangeRepeatTime)
	ON_CONTROL(SBXN_CHANGE, IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES, OnSpinchangeRepetitionStopCopies)
	ON_CONTROL(TSBXN_CHANGE, IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME, OnSpinchangePrintTime)
	ON_CONTROL(TSBXN_CHANGE, IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME, OnSpinchangePrintDailyTime)
	ON_CONTROL(TSBXN_CHANGE, IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME, OnSpinchangeRepetitionStopTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDSettingsPrintJobsPage message handlers

BOOL CANDSettingsPrintJobsPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	Spinbox_SetRange(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME), ANDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMINTERVAL, ANDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMINTERVAL);
	Spinbox_SetRange(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), ANDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES, ANDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES);
	EnumEvents();
	return TRUE;
}

BOOL CANDSettingsPrintJobsPage::OnSetActive()
{
	EnumJobs();
	return CLocalePropertyPage::OnSetActive();
}

BOOL CANDSettingsPrintJobsPage::OnKillActive()
{
	GetParentDialog()->OnDataExchange(GetSafeHwnd(), m_pJobs[0]);
	return CLocalePropertyPage::OnKillActive();
}

BOOL CANDSettingsPrintJobsPage::OnDataExchange(CONST CANDPrintJobs &pJobs)
{
	return m_pJobs[0].Copy(&pJobs);
}

void CANDSettingsPrintJobsPage::OnAddJob()
{
	CANDPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	if ((pJobInfo = FindJobInfo()))
	{
		pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() | AND_PRINT_ACTIVE);
		SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pJobInfo->GetName());
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS)->EnableWindow((SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow(FALSE);
	}
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsPrintJobsPage::OnRemoveJob()
{
	CANDPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	if ((pJobInfo = FindJobInfo(TRUE)))
	{
		for (pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~(AND_PRINT_ACTIVE | AND_PRINT_ATTIME | AND_PRINT_ATDAILYTIME | AND_PRINT_ATEVENT | AND_PRINT_REPEATBYINTERVAL | AND_PRINT_REPEATSTOPBYCOUNT | AND_PRINT_REPEATSTOPBYTIME | AND_PRINT_DAILYREPEATSTOPBYCOUNT | AND_PRINT_DAILYREPEATSTOPBYTIME)), SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCURSEL)); pJobInfo == FindJobInfo(); )
		{
			ShowJobInfo();
			break;
		}
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS)->EnableWindow((SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_REMOVEJOB)->EnableWindow(FALSE);
	}
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsPrintJobsPage::OnSelchangeDefinedJob()
{
	CANDPrintJobInfo  *pJobInfo;

	ShowJobInfo();
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow(((pJobInfo = FindJobInfo()) && SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
}

void CANDSettingsPrintJobsPage::OnSelchangeActiveJob()
{
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_REMOVEJOB)->EnableWindow();
}

void CANDSettingsPrintJobsPage::OnPrintAtTime()
{
	CTimeKey  tTime;
	CANDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		if (IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME))
		{
			Timespinbox_SetTime(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME), ((tTime = CTime::GetCurrentTime().GetTime() + SECONDSPERMINUTE*ANDSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL)));
			SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)STRING(IDS_ANDSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS));
			pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | AND_PRINT_ATTIME) & ~(AND_PRINT_REPEATBYINTERVAL | AND_PRINT_REPEATSTOPBYCOUNT | AND_PRINT_REPEATSTOPBYTIME));
			pJobInfo->SetPrintAtTime(tTime);
		}
		else
		{
			SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_ANDSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS)));
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~(AND_PRINT_ATTIME | AND_PRINT_REPEATBYINTERVAL | AND_PRINT_REPEATSTOPBYCOUNT | AND_PRINT_REPEATSTOPBYTIME));
		}
		SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_SETCURSEL, (IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) ? (WPARAM)SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)((IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME)) ? STRING(IDS_ANDSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS) : STRING(IDS_ANDSETTINGS_PRINTJOBSPAGE_DAILYPRINTS))) : (WPARAM)-1);
		Spinbox_SetRange(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), (IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME)) ? (ANDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES + 1) : ANDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES, ANDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES);
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)->EnableWindow(IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME));
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION)->EnableWindow(IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE)->EnableWindow(IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		SetJobRepetitionInfo();
	}
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsPrintJobsPage::OnPrintAtDailyTime()
{
	CTimeKey  tTime;
	CANDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		if (IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME))
		{
			Timespinbox_SetTime(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME), (tTime = CTime::GetCurrentTime().GetTime() + SECONDSPERMINUTE*ANDSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL));
			SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)STRING(IDS_ANDSETTINGS_PRINTJOBSPAGE_DAILYPRINTS));
			pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | AND_PRINT_ATDAILYTIME) & ~(AND_PRINT_DAILYREPEATSTOPBYCOUNT | AND_PRINT_DAILYREPEATSTOPBYTIME));
			pJobInfo->SetPrintAtDailyTime(tTime.GetTime() % SECONDSPERDAY);
		}
		else
		{
			SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_ANDSETTINGS_PRINTJOBSPAGE_DAILYPRINTS)));
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~(AND_PRINT_ATDAILYTIME | AND_PRINT_DAILYREPEATSTOPBYCOUNT | AND_PRINT_DAILYREPEATSTOPBYTIME));
		}
		SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_SETCURSEL, (IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) ? (WPARAM)SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)((IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) ? STRING(IDS_ANDSETTINGS_PRINTJOBSPAGE_DAILYPRINTS) : STRING(IDS_ANDSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS))) : (WPARAM)-1);
		Spinbox_SetRange(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), (IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) ? ANDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES : (ANDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES + 1), ANDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES);
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)->EnableWindow(IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION)->EnableWindow(IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE)->EnableWindow(IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		SetJobRepetitionInfo();
	}
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsPrintJobsPage::OnPrintAtEvent()
{
	CString  szEvent;
	CANDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		if (IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT))
		{
			SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_SETCURSEL);
			GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT)->GetWindowText(szEvent);
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() | AND_PRINT_ATEVENT);
			pJobInfo->SetPrintAtEvent(szEvent);
		}
		else
		{
			SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_SETCURSEL, (WPARAM)-1);
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~AND_PRINT_ATEVENT);
			pJobInfo->SetPrintAtEvent(EMPTYSTRING);
		}
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT)->EnableWindow(IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT));
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT));
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsPrintJobsPage::OnSelchangeEvent()
{
	CString  szEvent;
	CANDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT)->GetWindowText(szEvent);
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() | AND_PRINT_ATEVENT);
		pJobInfo->SetPrintAtEvent(szEvent);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsPrintJobsPage::OnSelchangeRepetitionType()
{
	Spinbox_SetRange(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), (GetJobRepetitionType() == ANDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY) ? (ANDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES + 1) : ANDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES, ANDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES);
	SetJobRepetitionInfo();
}

void CANDSettingsPrintJobsPage::OnRepeatByTime()
{
	CANDPrintJobInfo  *pJobInfo;

	for (CheckDlgButton(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME, !IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)); IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME); )
	{
		Spinbox_SetPos(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME), ANDSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL);
		break;
	}
	for (; (pJobInfo = FindJobInfo()); )
	{
		if (IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME))
		{
			pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | AND_PRINT_REPEATBYINTERVAL) & ~(AND_PRINT_REPEATSTOPBYCOUNT | AND_PRINT_REPEATSTOPBYTIME));
			pJobInfo->SetPrintAtTime(Timespinbox_GetTime(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), SECONDSPERMINUTE*ANDSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL);
			GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
			break;
		}
		pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~(AND_PRINT_REPEATBYINTERVAL | AND_PRINT_REPEATSTOPBYCOUNT | AND_PRINT_REPEATSTOPBYTIME));
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		break;
	}
	CheckDlgButton(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, FALSE);
	CheckDlgButton(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)->EnableWindow(IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)->EnableWindow(IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)->EnableWindow(IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsPrintJobsPage::OnRepetitionStopByCopies()
{
	CANDPrintJobInfo  *pJobInfo;

	for (CheckDlgButton(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, !IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)), GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow(IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)), GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)); IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES); )
	{
		Spinbox_SetPos(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), ANDSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTCOPIES);
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow(FALSE);
		CheckDlgButton(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, FALSE);
		break;
	}
	for (; (pJobInfo = FindJobInfo()); )
	{
		if (IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES))
		{
			if (GetJobRepetitionType() == ANDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY)
			{
				pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | AND_PRINT_REPEATSTOPBYCOUNT) & ~AND_PRINT_REPEATSTOPBYTIME);
				pJobInfo->SetPrintAtTime(Timespinbox_GetTime(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)), ANDSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTCOPIES);
			}
			if (GetJobRepetitionType() == ANDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY)
			{
				pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | AND_PRINT_DAILYREPEATSTOPBYCOUNT) & ~AND_PRINT_DAILYREPEATSTOPBYTIME);
				pJobInfo->SetPrintAtDailyTime(Timespinbox_GetTime(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)).GetTime() % SECONDSPERDAY, ANDSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTCOPIES);
			}
			GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
			break;
		}
		pJobInfo->SetPrintMode((GetJobRepetitionType() == ANDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY) ? (pJobInfo->GetPrintMode() & ~AND_PRINT_REPEATSTOPBYCOUNT) : (pJobInfo->GetPrintMode() & ~AND_PRINT_DAILYREPEATSTOPBYCOUNT));
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		break;
	}
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsPrintJobsPage::OnRepetitionStopByTime()
{
	CTimeKey  tStopTime;
	CANDPrintJobInfo  *pJobInfo;

	for (CheckDlgButton(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, !IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)), GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)); IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME); )
	{
		for (CheckDlgButton(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, FALSE); GetJobRepetitionType() == ANDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY; )
		{
			Timespinbox_SetTime(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), ((tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)).GetTime() + SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)))));
			break;
		}
		if (GetJobRepetitionType() == ANDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY) Timespinbox_SetTime(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), ((tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)).GetTime() + CTimeSpan(1, 0, 0, 0).GetTotalSeconds())));
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow(FALSE);
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow(FALSE);
		break;
	}
	for (; (pJobInfo = FindJobInfo()); )
	{
		if (IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME))
		{
			if (GetJobRepetitionType() == ANDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY)
			{
				pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | AND_PRINT_REPEATSTOPBYTIME) & ~AND_PRINT_REPEATSTOPBYCOUNT);
				pJobInfo->SetPrintAtTime(Timespinbox_GetTime(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)), tStopTime);
			}
			if (GetJobRepetitionType() == ANDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY)
			{
				pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | AND_PRINT_DAILYREPEATSTOPBYTIME) & ~AND_PRINT_DAILYREPEATSTOPBYCOUNT);
				pJobInfo->SetPrintAtDailyTime(Timespinbox_GetTime(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)).GetTime() % SECONDSPERDAY, tStopTime);
			}
			GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
			break;
		}
		pJobInfo->SetPrintMode((GetJobRepetitionType() == ANDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY) ? (pJobInfo->GetPrintMode() & ~AND_PRINT_REPEATSTOPBYTIME) : (pJobInfo->GetPrintMode() & ~AND_PRINT_DAILYREPEATSTOPBYTIME));
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		break;
	}
	GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsPrintJobsPage::OnSpinchangePrintTime()
{
	UINT  nStopCount;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeKey  tPrintTime;
	CTimeKey  tPrintStopTime;
	CTimeSpan  tPrintInterval;
	CANDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)); pJobInfo->GetPrintAtTime(tPrintTime); )
		{
			pJobInfo->SetPrintAtTime(tTime);
			break;
		}
		if (pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval)) pJobInfo->SetPrintAtTime(tTime, tPrintInterval);
		if (pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, nStopCount)) pJobInfo->SetPrintAtTime(tTime, tPrintInterval, nStopCount);
		if (pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, tPrintStopTime)) pJobInfo->SetPrintAtTime(tTime, tPrintInterval, (tTime.GetTime() + tPrintInterval.GetTotalSeconds() > tPrintStopTime.GetTime()) ? CTimeKey(tTime.GetTime() + tPrintInterval.GetTotalSeconds()) : tPrintStopTime);
		Timespinbox_SetTime(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (GetJobRepetitionType() == ANDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)) ? ((tTime + tPrintInterval.GetTotalSeconds() > tPrintStopTime.GetTime()) ? CTimeKey(tTime.GetTime() + tPrintInterval.GetTotalSeconds()) : tPrintStopTime) : tStopTime);
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsPrintJobsPage::OnSpinchangePrintDailyTime()
{
	UINT  nStopCount;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeKey  tPrintStopTime;
	CTimeSpan  tPrintTime;
	CANDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)), tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)); pJobInfo->GetPrintAtDailyTime(tPrintTime); )
		{
			pJobInfo->SetPrintAtDailyTime(tTime.GetTime() % SECONDSPERDAY);
			break;
		}
		if (pJobInfo->GetPrintAtDailyTime(tPrintTime, nStopCount)) pJobInfo->SetPrintAtDailyTime(tTime.GetTime() % SECONDSPERDAY, nStopCount);
		if (pJobInfo->GetPrintAtDailyTime(tPrintTime, tPrintStopTime)) pJobInfo->SetPrintAtDailyTime(tTime.GetTime() % SECONDSPERDAY, (SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + tTime.GetTime() % SECONDSPERDAY > tPrintStopTime.GetTime()) ? CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY + 1) + tTime.GetTime() % SECONDSPERDAY) : tPrintStopTime);
		Timespinbox_SetTime(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (GetJobRepetitionType() == ANDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)) ? ((SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + tTime.GetTime() % SECONDSPERDAY > tPrintStopTime.GetTime()) ? CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY + 1) + tTime.GetTime() % SECONDSPERDAY) : tPrintStopTime) : tStopTime);
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsPrintJobsPage::OnSpinchangeRepeatTime()
{
	UINT  nStopCount;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeKey  tPrintTime;
	CTimeKey  tPrintStopTime;
	CTimeSpan  tPrintInterval;
	CANDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)); pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval); )
		{
			pJobInfo->SetPrintAtTime(tPrintTime, SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)));
			break;
		}
		if (pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, nStopCount)) pJobInfo->SetPrintAtTime(tPrintTime, SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)), nStopCount);
		if (pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, tPrintStopTime)) pJobInfo->SetPrintAtTime(tPrintTime, SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)), (tPrintTime.GetTime() + SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)) > tPrintStopTime.GetTime()) ? CTimeKey(tPrintTime.GetTime() + SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME))) : tPrintStopTime);
		Timespinbox_SetTime(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (GetJobRepetitionType() == ANDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  IsDlgButtonChecked(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)) ? ((tPrintTime.GetTime() + SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)) > tPrintStopTime.GetTime()) ? CTimeKey(tPrintTime.GetTime() + SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME))) : tPrintStopTime) : tStopTime);
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsPrintJobsPage::OnSpinchangeRepetitionStopCopies()
{
	UINT  nStopCount;
	UINT  nPrintStopCount;
	CTimeKey  tPrintTime;
	CTimeSpan  tPrintInterval;
	CTimeSpan  tPrintDailyTime;
	CANDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (nStopCount = (UINT)Spinbox_GetPos(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)); GetJobRepetitionType() == ANDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY && pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, nPrintStopCount); )
		{
			pJobInfo->SetPrintAtTime(tPrintTime, tPrintInterval, nStopCount);
			break;
		}
		if (GetJobRepetitionType() == ANDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  pJobInfo->GetPrintAtDailyTime(tPrintDailyTime, nPrintStopCount)) pJobInfo->SetPrintAtDailyTime(tPrintDailyTime, nStopCount);
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDSettingsPrintJobsPage::OnSpinchangeRepetitionStopTime()
{
	CTimeKey  tTime;
	CTimeKey  tTimeKey;
	CTimeKey  tStopTime;
	CTimeKey  tPrintTime;
	CTimeKey  tPrintStopTime;
	CTimeSpan  tPrintInterval;
	CTimeSpan  tPrintDailyTime;
	CANDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)); GetJobRepetitionType() == ANDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY && pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, tPrintStopTime); )
		{
			if (tTime > tStopTime.GetTime() - tPrintInterval.GetTotalSeconds()) Timespinbox_SetTime(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (tStopTime = tTime.GetTime() + tPrintInterval.GetTotalSeconds()));
			pJobInfo->SetPrintAtTime(tTime, tPrintInterval, tStopTime);
			break;
		}
		if (GetJobRepetitionType() == ANDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  pJobInfo->GetPrintAtDailyTime(tPrintDailyTime, tPrintStopTime))
		{
			if (SECONDSPERDAY*(tTimeKey.GetTime() / SECONDSPERDAY) + tPrintDailyTime.GetTotalSeconds() > tStopTime.GetTime()) Timespinbox_SetTime(GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (tStopTime = SECONDSPERDAY*(tTimeKey.GetTime() / SECONDSPERDAY) + tPrintDailyTime.GetTotalSeconds()));
			pJobInfo->SetPrintAtDailyTime(tPrintDailyTime, tStopTime);
		}
		GetDlgItem(IDC_ANDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_ANDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CANDSettingsTabCtrl

IMPLEMENT_DYNCREATE(CANDSettingsTabCtrl, CTabCtrl)

BEGIN_MESSAGE_MAP(CANDSettingsTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CANDSettingsTabCtrl)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDSettingsTabCtrl message handlers


/////////////////////////////////////////////////////////////////////////////
// CANDSettingsDialog

IMPLEMENT_DYNCREATE(CANDSettingsDialog, CDisplayPropertySheetDialog)

CANDSettingsDialog::CANDSettingsDialog() : CDisplayPropertySheetDialog()
{
	AddPage(&m_pageLayout);
	AddPage(&m_pageContents);
	AddPage(&m_pageRetrieving);
	AddPage(&m_pagePrinting);
	AddPage(&m_pagePrintJobs);
}

BOOL CANDSettingsDialog::GetLayout(CANDLayout &cLayout, CUIntArray &nColumns) CONST
{
	INT  nIndex;
	INT  nCount;
	INT  nParameter;
	INT  nParameters;
	INT  nColumnGroup;
	CANDLayoutParameter  *pParameter;

	if ((GetActivePage()->GetSafeHwnd() != m_pageContents.GetSafeHwnd() && m_pageLayout.GetLayout(nColumns) && m_pageContents.GetLayout(cLayout)) || (GetActivePage()->GetSafeHwnd() == m_pageContents.GetSafeHwnd() && m_pageContents.GetLayout(cLayout, nColumns)))
	{
		for (nIndex = 0, nCount = (INT)nColumns.GetSize(), nColumnGroup = 0; nIndex < nCount; nIndex++)
		{
			if (nColumns.GetAt(nIndex) == AND_TITLEITEM_ID)
			{
				nColumnGroup++;
				continue;
			}
		}
		for (nParameter = 0, nParameters = (INT)cLayout.GetSize(); nParameter < nParameters; nParameter++)
		{
			if ((pParameter = cLayout.GetAt(nParameter)) && pParameter->GetColumn() >= nColumnGroup)
			{
				cLayout.RemoveAt(nParameter);
				delete pParameter;
				nParameters--;
				nParameter--;
			}
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CANDSettingsDialog::GetLayoutColors(CUIntArray &nColors) CONST
{
	return m_pageContents.GetColors(nColors);
}

BOOL CANDSettingsDialog::GetLayoutTitleFont(LPLOGFONT pTitleFont) CONST
{
	return m_pageLayout.GetTitleFont(pTitleFont);
}

BOOL CANDSettingsDialog::GetLayoutLabelsFont(LPLOGFONT pLabelsFont) CONST
{
	return m_pageLayout.GetLabelsFont(pLabelsFont);
}

BOOL CANDSettingsDialog::GetLayoutItemsFont(LPLOGFONT pItemsFont) CONST
{
	return m_pageLayout.GetItemsFont(pItemsFont);
}

BOOL CANDSettingsDialog::GetLayoutValuesFont(LPLOGFONT pValuesFont) CONST
{
	return m_pageLayout.GetValuesFont(pValuesFont);
}

BOOL CANDSettingsDialog::GetLayoutInvalidDataMode(BOOL &bEnable) CONST
{
	return m_pageLayout.GetInvalidDataMode(bEnable);
}

BOOL CANDSettingsDialog::GetLayoutBadDataMode(BOOL &bEnable) CONST
{
	return m_pageLayout.GetBadDataMode(bEnable);
}

BOOL CANDSettingsDialog::GetLayoutToolTipMode(BOOL &bEnable) CONST
{
	return m_pageLayout.GetToolTipMode(bEnable);
}

BOOL CANDSettingsDialog::IsLayoutModified() CONST
{
	return m_pageLayout.IsModified() || m_pageContents.IsModified();
}

BOOL CANDSettingsDialog::GetRetrieveFileName(CString &szFileName) CONST
{
	return m_pageRetrieving.GetDataSourceFileName(szFileName);
}

BOOL CANDSettingsDialog::IsRetrievingModified() CONST
{
	return m_pageRetrieving.IsModified();
}

BOOL CANDSettingsDialog::GetPrintJobs(CANDPrintJobs &pPrintJobs) CONST
{
	return(((GetActivePage()->GetSafeHwnd() != m_pagePrintJobs.GetSafeHwnd() && m_pagePrinting.GetJobs(pPrintJobs)) || (GetActivePage()->GetSafeHwnd() == m_pagePrintJobs.GetSafeHwnd() && m_pagePrintJobs.GetJobs(pPrintJobs))) ? TRUE : FALSE);
}

BOOL CANDSettingsDialog::IsPrintingModified() CONST
{
	return m_pagePrinting.IsModified() || m_pagePrintJobs.IsModified();
}

CANDOpenDialog *CANDSettingsDialog::GetParentDialog() CONST
{
	return((GetParent() != (CWnd *)GetParentDisplay()) ? (CANDOpenDialog *)GetParent() : (CANDOpenDialog *)NULL);
}

CANDWnd *CANDSettingsDialog::GetParentDisplay() CONST
{
	return((CANDWnd *)CDisplayPropertySheetDialog::GetParentDisplay());
}

BEGIN_MESSAGE_MAP(CANDSettingsDialog, CDisplayPropertySheetDialog)
	//{{AFX_MSG_MAP(CANDSettingsDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDHELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDSettingsDialog message handlers

BOOL CANDSettingsDialog::OnInitDialog()
{
	INT  nPage;
	INT  nPages;
	CHourglassCursor  cCursor;

	CDisplayPropertySheetDialog::OnInitDialog();
	SetTitle(STRING(IDS_ANDSETTINGSDIALOG_TITLE));
	for (nPage = 0, nPages = GetPageCount(), m_wndTabCtrl.SubclassWindow(GetTabControl()->GetSafeHwnd()); nPage < nPages; nPage++)
	{
		SetActivePage((nPage + 1) % nPages);
		continue;
	}
	m_wndTabCtrl.SetFocus();
	return FALSE;
}

BOOL CANDSettingsDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	CRect  rTab;
	CANDPrintJobs  pPrintJobs;
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

BOOL CANDSettingsDialog::OnDataExchange(HWND hPage, CONST CUIntArray &nColumns)
{
	return(((hPage == m_pageLayout.GetSafeHwnd() && m_pageContents.OnDataExchange(nColumns)) || (hPage == m_pageContents.GetSafeHwnd() && m_pageLayout.OnDataExchange(nColumns))) ? TRUE : FALSE);
}
BOOL CANDSettingsDialog::OnDataExchange(HWND hPage, CONST CANDPrintJobs &pJobs)
{
	return(((hPage == m_pagePrinting.GetSafeHwnd() && m_pagePrintJobs.OnDataExchange(pJobs)) || (hPage == m_pagePrintJobs.GetSafeHwnd() && m_pagePrinting.OnDataExchange(pJobs))) ? TRUE : FALSE);
}

void CANDSettingsDialog::OnOK()
{
	CHourglassCursor  cCursor;

	ReportEvent(((!GetParentDialog() && !GetParentDisplay()->OnCloseSettingsDialog(IDOK)) || (GetParentDialog() && !GetParentDialog()->OnCloseSettingsDialog(IDOK))) ? SYSTEM_WARNING_AND_SETUP_FAILURE : SYSTEM_NOERROR);
	CDisplayPropertySheetDialog::OnOK();
}

void CANDSettingsDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	if (!GetParentDialog()) GetParentDisplay()->OnCloseSettingsDialog(IDCANCEL);
	else  GetParentDialog()->OnCloseSettingsDialog(IDCANCEL);
	CDisplayPropertySheetDialog::OnCancel();
}

BOOL CANDSettingsDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_ANDSETTINGSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CANDSettingsDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_ANDSETTINGSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CANDLinkagesDialog dialog

IMPLEMENT_DYNCREATE(CANDLinkagesDialog, CDisplayDialog)

CANDLinkagesDialog::CANDLinkagesDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CANDLinkagesDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CANDLinkagesDialog::Create(CWnd *pParentWnd)
{
	return CDisplayDialog::Create(pParentWnd, CANDLinkagesDialog::IDD);
}

BOOL CANDLinkagesDialog::Initialize()
{
	GetDisplayArea()->EnumDisplays(m_pDisplays[0]);
	GetParent()->GetLinks(m_pDisplays[1]);
	return TRUE;
}

CANDWnd *CANDLinkagesDialog::GetParent() CONST
{
	return((CANDWnd *)CDisplayDialog::GetParent());
}

BOOL CANDLinkagesDialog::EnumDisplays()
{
	INT  nDisplay[2];
	INT  nDisplays[2];
	CString  szDisplay;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay[0] = 0, nDisplays[0] = (INT)m_pDisplays[0].GetSize(), SendDlgItemMessage(IDC_AND_LINKAGES_DISPLAYS, CB_RESETCONTENT), SendDlgItemMessage(IDC_AND_LINKAGES_LIST, LB_RESETCONTENT); nDisplay[0] < nDisplays[0]; nDisplay[0]++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)m_pDisplays[0].GetAt(nDisplay[0])) == GetParent() || !pDisplayWnd->IsLinkable())
		{
			m_pDisplays[0].RemoveAt(nDisplay[0]);
			nDisplays[0]--;
			nDisplay[0]--;
			continue;
		}
		for (nDisplay[1] = 0, nDisplays[1] = (INT)m_pDisplays[1].GetSize(); nDisplay[1] < nDisplays[1]; nDisplay[1]++)
		{
			if ((pDisplayWnd = (CDisplayWnd *)m_pDisplays[0].GetAt(nDisplay[0])) && pDisplayWnd == (CDisplayWnd *)m_pDisplays[1].GetAt(nDisplay[1]))
			{
				m_pDisplays[0].RemoveAt(nDisplay[0]);
				nDisplays[0]--;
				nDisplay[0]--;
				break;
			}
		}
	}
	for (nDisplay[0] = 0, nDisplays[0] = (INT)m_pDisplays[0].GetSize(); nDisplay[0] < nDisplays[0]; nDisplay[0]++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)m_pDisplays[0].GetAt(nDisplay[0])) != (CDisplayWnd *)NULL)
		{
			for (pDisplayWnd->GetWindowText(szDisplay); SendDlgItemMessage(IDC_AND_LINKAGES_DISPLAYS, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szDisplay) < 0 && !szDisplay.IsEmpty(); )
			{
				SendDlgItemMessage(IDC_AND_LINKAGES_DISPLAYS, CB_INSERTSTRING, nDisplay[0], (LPARAM)(LPCTSTR)szDisplay);
				break;
			}
		}
	}
	for (nDisplay[1] = 0, nDisplays[1] = (INT)m_pDisplays[1].GetSize(), m_pDisplays[2].Copy(m_pDisplays[1]); nDisplay[1] < nDisplays[1]; nDisplay[1]++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)m_pDisplays[1].GetAt(nDisplay[1])) != (CDisplayWnd *)NULL)
		{
			for (pDisplayWnd->GetWindowText(szDisplay); SendDlgItemMessage(IDC_AND_LINKAGES_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szDisplay) < 0 && !szDisplay.IsEmpty(); )
			{
				SendDlgItemMessage(IDC_AND_LINKAGES_LIST, LB_INSERTSTRING, nDisplay[1], (LPARAM)(LPCTSTR)szDisplay);
				break;
			}
		}
	}
	SendDlgItemMessage(IDC_AND_LINKAGES_LIST, LB_SETCURSEL);
	SendDlgItemMessage(IDC_AND_LINKAGES_DISPLAYS, CB_SETCURSEL);
	GetDlgItem(IDC_AND_LINKAGES_DISPLAYS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_AND_LINKAGES_DISPLAYS, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_LINKAGES_DISPLAYS)->EnableWindow((SendDlgItemMessage(IDC_AND_LINKAGES_DISPLAYS, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_LINKAGES_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_AND_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_LINKAGES_LIST)->EnableWindow((SendDlgItemMessage(IDC_AND_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_LINKAGES_ADD)->EnableWindow((SendDlgItemMessage(IDC_AND_LINKAGES_DISPLAYS, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_LINKAGES_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_AND_LINKAGES_LIST, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_LINKAGES_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_AND_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	return TRUE;
}

INT CANDLinkagesDialog::FindDisplay(LPCTSTR pszName, BOOL bLinked) CONST
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szDisplay;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay = 0, nDisplays = (INT)m_pDisplays[bLinked].GetSize(); nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)m_pDisplays[bLinked].GetAt(nDisplay)))
		{
			pDisplayWnd->GetWindowText(szDisplay);
			if (!szDisplay.Compare(pszName)) break;
		}
	}
	return((nDisplay < nDisplays) ? nDisplay : -1);
}

BOOL CANDLinkagesDialog::IsModified() CONST
{
	INT  nDisplay[2];
	INT  nDisplays[2];

	for (nDisplay[0] = 0, nDisplays[0] = (m_pDisplays[1].GetSize() == m_pDisplays[2].GetSize()) ? (INT)m_pDisplays[1].GetSize() : -1; nDisplay[0] < nDisplays[0]; nDisplay[0]++)
	{
		for (nDisplay[1] = 0, nDisplays[1] = (INT)m_pDisplays[2].GetSize(); nDisplay[1] < nDisplays[1]; nDisplay[1]++)
		{
			if (m_pDisplays[1].GetAt(nDisplay[0]) == m_pDisplays[2].GetAt(nDisplay[1])) break;
			continue;
		}
		if (nDisplay[1] == nDisplays[1]) break;
	}
	return((nDisplay[0] != nDisplays[0]) ? TRUE : FALSE);
}

BOOL CANDLinkagesDialog::Check(BOOL bModified) CONST
{
	return(!bModified || IsModified());
}

void CANDLinkagesDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CANDLinkagesDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CANDLinkagesDialog::PostNcDestroy()
{
	m_pDisplays[0].RemoveAll();
	m_pDisplays[1].RemoveAll();
	m_pDisplays[2].RemoveAll();
	CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CANDLinkagesDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CANDLinkagesDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_AND_LINKAGES_ADD, OnAddDisplay)
	ON_BN_CLICKED(IDC_AND_LINKAGES_REMOVE, OnRemoveLinkedDisplay)
	ON_BN_CLICKED(IDC_AND_LINKAGES_REMOVEALL, OnRemoveAllLinkedDisplays)
	ON_BN_CLICKED(IDC_AND_LINKAGES_HELP, OnHelp)
	ON_LBN_SELCHANGE(IDC_AND_LINKAGES_LIST, OnSelchangeLinkedDisplay)
	ON_CBN_EDITCHANGE(IDC_AND_LINKAGES_DISPLAYS, OnEditchangeDisplay)
	ON_CBN_SELCHANGE(IDC_AND_LINKAGES_DISPLAYS, OnSelchangeDisplay)
	ON_CBN_DBLCLK(IDC_AND_LINKAGES_DISPLAYS, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDLinkagesDialog message handlers

BOOL CANDLinkagesDialog::OnInitDialog()
{
	CString  szDisplay;
	CHourglassCursor  cCursor;

	for (CDisplayDialog::OnInitDialog(), GetParent()->GetWindowText(szDisplay); EnumDisplays(); )
	{
		GetDlgItem(IDC_AND_LINKAGES_NAME)->SetWindowText(szDisplay);
		GetDlgItem(IDC_AND_LINKAGES_DETAILS)->EnableWindow();
		GetDlgItem(IDC_AND_LINKAGES_NAME_STATIC)->EnableWindow();
		GetDlgItem(IDC_AND_LINKAGES_NAME)->EnableWindow();
		GetDlgItem(IDC_AND_LINKAGES_DISPLAYS)->SetFocus();
		return FALSE;
	}
	return TRUE;
}

void CANDLinkagesDialog::OnAddDisplay()
{
	INT  nIndex[2];
	CString  szDisplay;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_AND_LINKAGES_DISPLAYS)->GetWindowText(szDisplay); (nIndex[0] = FindDisplay(szDisplay)) >= 0; )
	{
		if ((nIndex[1] = (INT)SendDlgItemMessage(IDC_AND_LINKAGES_LIST, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szDisplay)) >= 0)
		{
			for (SendDlgItemMessage(IDC_AND_LINKAGES_LIST, LB_SETCURSEL, nIndex[1]); SendDlgItemMessage(IDC_AND_LINKAGES_DISPLAYS, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_AND_LINKAGES_DISPLAYS, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szDisplay)) >= 0; )
			{
				m_pDisplays[1].Add(m_pDisplays[0].GetAt(nIndex[0]));
				m_pDisplays[0].RemoveAt(nIndex[0]);
				break;
			}
			SendDlgItemMessage(IDC_AND_LINKAGES_DISPLAYS, CB_SETCURSEL);
			GetDlgItem(IDC_AND_LINKAGES_ADD)->EnableWindow((SendDlgItemMessage(IDC_AND_LINKAGES_DISPLAYS, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
			GetDlgItem(IDC_AND_LINKAGES_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_AND_LINKAGES_LIST, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
			GetDlgItem(IDC_AND_LINKAGES_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_AND_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_AND_LINKAGES_DISPLAYS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_AND_LINKAGES_DISPLAYS, CB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_AND_LINKAGES_DISPLAYS)->EnableWindow((SendDlgItemMessage(IDC_AND_LINKAGES_DISPLAYS, CB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_AND_LINKAGES_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_AND_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_AND_LINKAGES_LIST)->EnableWindow((SendDlgItemMessage(IDC_AND_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_AND_LINKAGES_LIST)->SetFocus();
		}
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDLinkagesDialog::OnRemoveLinkedDisplay()
{
	INT  nIndex[2];
	CString  szDisplay;
	CHourglassCursor  cCursor;

	for (szDisplay = Listbox_GetText(GetDlgItem(IDC_AND_LINKAGES_LIST), (INT)SendDlgItemMessage(IDC_AND_LINKAGES_LIST, LB_GETCURSEL)); (nIndex[0] = FindDisplay(szDisplay, TRUE)) >= 0; )
	{
		if ((nIndex[1] = (INT)SendDlgItemMessage(IDC_AND_LINKAGES_DISPLAYS, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szDisplay)) >= 0)
		{
			for (SendDlgItemMessage(IDC_AND_LINKAGES_DISPLAYS, CB_SETCURSEL, nIndex[1]); SendDlgItemMessage(IDC_AND_LINKAGES_LIST, LB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_AND_LINKAGES_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szDisplay)) >= 0; )
			{
				m_pDisplays[0].Add(m_pDisplays[1].GetAt(nIndex[0]));
				m_pDisplays[1].RemoveAt(nIndex[0]);
				break;
			}
			SendDlgItemMessage(IDC_AND_LINKAGES_LIST, LB_SETCURSEL);
			GetDlgItem(IDC_AND_LINKAGES_ADD)->EnableWindow((SendDlgItemMessage(IDC_AND_LINKAGES_DISPLAYS, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
			GetDlgItem(IDC_AND_LINKAGES_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_AND_LINKAGES_LIST, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
			GetDlgItem(IDC_AND_LINKAGES_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_AND_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_AND_LINKAGES_DISPLAYS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_AND_LINKAGES_DISPLAYS, CB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_AND_LINKAGES_DISPLAYS)->EnableWindow((SendDlgItemMessage(IDC_AND_LINKAGES_DISPLAYS, CB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_AND_LINKAGES_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_AND_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_AND_LINKAGES_LIST)->EnableWindow((SendDlgItemMessage(IDC_AND_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_AND_LINKAGES_DISPLAYS)->SetFocus();
		}
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDLinkagesDialog::OnRemoveAllLinkedDisplays()
{
	INT  nDisplay;
	INT  nDisplays;
	CHourglassCursor  cCursor;

	for (nDisplay = 0, nDisplays = (INT)SendDlgItemMessage(IDC_AND_LINKAGES_LIST, LB_GETCOUNT), m_pDisplays[0].Append(m_pDisplays[1]), m_pDisplays[1].RemoveAll(); nDisplay < nDisplays; nDisplay++)
	{
		if (SendDlgItemMessage(IDC_AND_LINKAGES_DISPLAYS, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)Listbox_GetText(GetDlgItem(IDC_AND_LINKAGES_LIST), nDisplay)) >= 0)
		{
			SendDlgItemMessage(IDC_AND_LINKAGES_LIST, LB_DELETESTRING, nDisplay);
			nDisplays--;
			nDisplay--;
		}
	}
	SendDlgItemMessage(IDC_AND_LINKAGES_LIST, LB_SETCURSEL);
	SendDlgItemMessage(IDC_AND_LINKAGES_DISPLAYS, CB_SETCURSEL);
	GetDlgItem(IDC_AND_LINKAGES_ADD)->EnableWindow((SendDlgItemMessage(IDC_AND_LINKAGES_DISPLAYS, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_LINKAGES_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_AND_LINKAGES_LIST, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_LINKAGES_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_AND_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_LINKAGES_DISPLAYS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_AND_LINKAGES_DISPLAYS, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_LINKAGES_DISPLAYS)->EnableWindow((SendDlgItemMessage(IDC_AND_LINKAGES_DISPLAYS, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_LINKAGES_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_AND_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_LINKAGES_LIST)->EnableWindow((SendDlgItemMessage(IDC_AND_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_LINKAGES_DISPLAYS)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDLinkagesDialog::OnEditchangeDisplay()
{
	CString  szDisplay;

	GetDlgItem(IDC_AND_LINKAGES_DISPLAYS)->GetWindowText(szDisplay);
	GetDlgItem(IDC_AND_LINKAGES_ADD)->EnableWindow((SendDlgItemMessage(IDC_AND_LINKAGES_DISPLAYS, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szDisplay) >= 0 && SendDlgItemMessage(IDC_AND_LINKAGES_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szDisplay) < 0) ? TRUE : FALSE);
}

void CANDLinkagesDialog::OnSelchangeDisplay()
{
	GetDlgItem(IDC_AND_LINKAGES_ADD)->EnableWindow();
}

void CANDLinkagesDialog::OnSelchangeLinkedDisplay()
{
	GetDlgItem(IDC_AND_LINKAGES_REMOVE)->EnableWindow();
}

void CANDLinkagesDialog::OnOK()
{
	INT  nDisplay[2];
	INT  nDisplays[2];
	CString  szLink;
	CDisplayWnd  *pDisplayWnd[2];
	CHourglassCursor  cCursor;

	for (nDisplay[0] = 0, nDisplays[0] = (INT)m_pDisplays[1].GetSize(); nDisplay[0] < nDisplays[0]; nDisplay[0]++)
	{
		for (nDisplay[1] = 0, nDisplays[1] = (INT)m_pDisplays[2].GetSize(); nDisplay[1] < nDisplays[1]; nDisplay[1]++)
		{
			if (m_pDisplays[1].GetAt(nDisplay[0]) == m_pDisplays[2].GetAt(nDisplay[1]))
			{
				m_pDisplays[1].RemoveAt(nDisplay[0]);
				m_pDisplays[2].RemoveAt(nDisplay[1]);
				nDisplays[0]--;
				nDisplays[1]--;
				nDisplay[0]--;
				nDisplay[1]--;
				break;
			}
		}
	}
	for (nDisplay[0] = 0, nDisplays[0] = (INT)m_pDisplays[1].GetSize(); nDisplay[0] < nDisplays[0]; nDisplay[0]++)
	{
		if ((pDisplayWnd[0] = (CDisplayWnd *)m_pDisplays[1].GetAt(nDisplay[0]))->Lock())
		{
			if ((pDisplayWnd[1] = GetParent())->Lock())
			{
				pDisplayWnd[1]->GetWindowText(szLink);
				pDisplayWnd[0]->SetLink(pDisplayWnd[1]);
				pDisplayWnd[0]->SetLinkByName(szLink);
				pDisplayWnd[1]->AddLink(pDisplayWnd[0]);
				pDisplayWnd[1]->Unlock();
			}
			pDisplayWnd[0]->InitializeTMData(pDisplayWnd[1]->GetMode());
			pDisplayWnd[0]->Unlock();
		}
	}
	for (nDisplay[1] = 0, nDisplays[1] = (INT)m_pDisplays[2].GetSize(); nDisplay[1] < nDisplays[1]; nDisplay[1]++)
	{
		if ((pDisplayWnd[0] = (CDisplayWnd *)m_pDisplays[2].GetAt(nDisplay[1]))->Lock())
		{
			if ((pDisplayWnd[1] = GetParent())->Lock())
			{
				pDisplayWnd[0]->SetLink();
				pDisplayWnd[0]->SetLinkByName();
				pDisplayWnd[1]->RemoveLink(pDisplayWnd[0]);
				pDisplayWnd[1]->Unlock();
			}
			pDisplayWnd[0]->Unlock();
			pDisplayWnd[0]->UpdateBars();
		}
	}
	for (; nDisplays[0] == 1; )
	{
		pDisplayWnd[0]->ActivateFrame(SW_SHOWNORMAL);
		break;
	}
	CDisplayDialog::OnOK();
}

BOOL CANDLinkagesDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_ANDLINKAGESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CANDLinkagesDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_ANDLINKAGESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CANDParametersCalibrationPage property page

IMPLEMENT_DYNCREATE(CANDParametersCalibrationPage, CLocalePropertyPage)

CANDParametersCalibrationPage::CANDParametersCalibrationPage() : CLocalePropertyPage(CANDParametersCalibrationPage::IDD)
{
	//{{AFX_DATA_INIT(CANDParametersCalibrationPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

VOID CANDParametersCalibrationPage::ShowParameterInfo()
{
	SendDlgItemMessage(IDC_AND_PARAMETERS_CALIBRATIONPAGE_NAME, CB_RESETCONTENT);
	GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_NAME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_NAME)->EnableWindow(FALSE);
	ShowCalibrationInfo();
}
VOID CANDParametersCalibrationPage::ShowParameterInfo(CONST CTMParameter *pTMParameter)
{
	INT  nIndex;
	INT  nTable;
	INT  nTables;
	UINT  nStatus;
	CString  szName;
	CString  szTable;
	ULONGLONG  nValue;
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CDatabaseTMNumCalTable  *pDatabaseTMNumCalTable;
	CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;

	for (SendDlgItemMessage(IDC_AND_PARAMETERS_CALIBRATIONPAGE_NAME, CB_RESETCONTENT), nIndex = -1; (pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pTMParameter->GetTag()))); )
	{
		for (nTable = 0, nTables = pDatabaseTMParameter->GetCalTableRefs(m_nCalTableRefs, m_nCalValidityRefs), szTable = (pTMParameter->GetRawValue(pTMParameter->GetValueCount() - 1, nValue, nStatus, szTable)) ? szTable : EMPTYSTRING; nTable < nTables; nTable++)
		{
			if ((m_nCalTableType = (pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS))) == TMPARAMETER_CALIBRATION_NUMERICAL)
			{
				if ((pDatabaseTMNumCalTable = GetDatabase()->GetTMNumCalTables()->GetAt(m_nCalTableRefs.GetAt(nTable))) != (CDatabaseTMNumCalTable *)NULL)
				{
					for (szName.Format(STRING(IDS_ANDPARAMETERS_CALIBRATIONPAGE_TABLE_FORMAT), (LPCTSTR)pDatabaseTMNumCalTable->GetDescription(), (LPCTSTR)pDatabaseTMNumCalTable->GetName()); pDatabaseTMNumCalTable->GetDescription().IsEmpty(); )
					{
						szName = pDatabaseTMNumCalTable->GetName();
						break;
					}
					for (SendDlgItemMessage(IDC_AND_PARAMETERS_CALIBRATIONPAGE_NAME, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szName); pDatabaseTMNumCalTable->GetName() == szTable; )
					{
						nIndex = nTable;
						break;
					}
					continue;
				}
			}
			if (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS)
			{
				if ((pDatabaseTMTxtCalTable = GetDatabase()->GetTMTxtCalTables()->GetAt(m_nCalTableRefs.GetAt(nTable))))
				{
					for (szName.Format(STRING(IDS_ANDPARAMETERS_CALIBRATIONPAGE_TABLE_FORMAT), (LPCTSTR)pDatabaseTMTxtCalTable->GetDescription(), (LPCTSTR)pDatabaseTMTxtCalTable->GetName()); pDatabaseTMTxtCalTable->GetDescription().IsEmpty(); )
					{
						szName = pDatabaseTMTxtCalTable->GetName();
						break;
					}
					for (SendDlgItemMessage(IDC_AND_PARAMETERS_CALIBRATIONPAGE_NAME, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szName); pDatabaseTMTxtCalTable->GetName() == szTable; )
					{
						nIndex = nTable;
						break;
					}
					continue;
				}
			}
		}
		break;
	}
	m_nCalTableID = (INT)SendDlgItemMessage(IDC_AND_PARAMETERS_CALIBRATIONPAGE_NAME, CB_SETCURSEL, max(nIndex, 0));
	GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_NAME_STATIC)->EnableWindow((SendDlgItemMessage(IDC_AND_PARAMETERS_CALIBRATIONPAGE_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_NAME)->EnableWindow((SendDlgItemMessage(IDC_AND_PARAMETERS_CALIBRATIONPAGE_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	ShowCalibrationInfo();
}

VOID CANDParametersCalibrationPage::ShowCalibrationInfo()
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

	SendDlgItemMessage(IDC_AND_PARAMETERS_CALIBRATIONPAGE_POINTS, LVM_DELETEALLITEMS);
	if ((nIndex = (INT)SendDlgItemMessage(IDC_AND_PARAMETERS_CALIBRATIONPAGE_NAME, CB_GETCURSEL)) >= 0 && nIndex < m_nCalTableRefs.GetSize())
	{
		if ((pDatabaseTMNumCalTable = (m_nCalTableType == TMPARAMETER_CALIBRATION_NUMERICAL) ? GetDatabase()->GetTMNumCalTables()->GetAt(m_nCalTableRefs.GetAt(nIndex)) : (CDatabaseTMNumCalTable *)NULL))
		{
			for (nItem = 0, nItems = (INT)pDatabaseTMNumCalTable->GetSize(); nItem < nItems; nItem++)
			{
				if ((pDatabaseTMNumCalPoint = pDatabaseTMNumCalTable->GetAt(nItem)))
				{
					for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn = nColumn + 1)
					{
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_ANDPARAMETERS_CALIBRATIONPAGE_TITLEITEM_NUMBER); )
						{
							szItem = cStringTools.ConvertIntToString(nItem + 1);
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_ANDPARAMETERS_CALIBRATIONPAGE_TITLEITEM_X); )
						{
							szItem = cStringTools.ConvertFloatToTruncatedString(pDatabaseTMNumCalPoint->GetX());
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_ANDPARAMETERS_CALIBRATIONPAGE_TITLEITEM_Y); )
						{
							szItem = cStringTools.ConvertFloatToString(pDatabaseTMNumCalPoint->GetY());
							break;
						}
						if (!nColumn)
						{
							Listview_InsertText(GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_POINTS), nItem, szItem);
							continue;
						}
						Listview_SetText(GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_POINTS), nItem, nColumn, szItem);
					}
				}
			}
			GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_ID)->SetWindowText(pDatabaseTMNumCalTable->GetName());
			GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_TYPE)->SetWindowText(STRING(IDS_ANDPARAMETERS_CALIBRATIONPAGE_TYPE_NUMERICAL));
			GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_STATUS)->SetWindowText((nIndex == m_nCalTableID) ? STRING(IDS_ANDPARAMETERS_CALIBRATIONPAGE_STATUS_ACTIVE) : STRING(IDS_ANDPARAMETERS_CALIBRATIONPAGE_STATUS_INACTIVE));
			GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_ID_STATIC)->EnableWindow((GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_ID)->EnableWindow((GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_POINTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_AND_PARAMETERS_CALIBRATIONPAGE_POINTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_POINTS)->EnableWindow((SendDlgItemMessage(IDC_AND_PARAMETERS_CALIBRATIONPAGE_POINTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_TYPE_STATIC)->EnableWindow();
			GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_TYPE)->EnableWindow();
			GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_STATUS_STATIC)->EnableWindow();
			GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_STATUS)->EnableWindow();
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
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_ANDPARAMETERS_CALIBRATIONPAGE_TITLEITEM_NUMBER); )
						{
							szItem = cStringTools.ConvertIntToString(nItem + 1);
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_ANDPARAMETERS_CALIBRATIONPAGE_TITLEITEM_X); )
						{
							if (pDatabaseTMTxtCalPoint->GetRange(fCalPtX, fCalPtY, szCalText) || pDatabaseTMTxtCalPoint->GetPoint(fCalPtX, szCalText))
							{
								for (szCalPtX = szItem = cStringTools.ConvertFloatToTruncatedString(fCalPtX, -1), szCalPtY = cStringTools.ConvertFloatToTruncatedString(fCalPtY, -1); fCalPtX != fCalPtY; )
								{
									szItem.Format(STRING(IDS_ANDPARAMETERS_CALIBRATIONPAGE_POINT_RANGE), (LPCTSTR)szCalPtX, (LPCTSTR)szCalPtY);
									break;
								}
								break;
							}
							szItem.Empty();
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_ANDPARAMETERS_CALIBRATIONPAGE_TITLEITEM_Y); )
						{
							szItem = (pDatabaseTMTxtCalPoint->GetPoint(fCalPtX, szCalText) || pDatabaseTMTxtCalPoint->GetRange(fCalPtX, fCalPtY, szCalText)) ? (LPCTSTR)szCalText : EMPTYSTRING;
							break;
						}
						if (!nColumn)
						{
							Listview_InsertText(GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_POINTS), nItem, szItem);
							continue;
						}
						Listview_SetText(GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_POINTS), nItem, nColumn, szItem);
					}
				}
			}
			GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_ID)->SetWindowText(pDatabaseTMTxtCalTable->GetName());
			GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_TYPE)->SetWindowText(STRING(IDS_ANDPARAMETERS_CALIBRATIONPAGE_TYPE_STATUS));
			GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_STATUS)->SetWindowText((nIndex == m_nCalTableID) ? STRING(IDS_ANDPARAMETERS_CALIBRATIONPAGE_STATUS_ACTIVE) : STRING(IDS_ANDPARAMETERS_CALIBRATIONPAGE_STATUS_INACTIVE));
			GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_ID_STATIC)->EnableWindow((GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_ID)->EnableWindow((GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_POINTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_AND_PARAMETERS_CALIBRATIONPAGE_POINTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_POINTS)->EnableWindow((SendDlgItemMessage(IDC_AND_PARAMETERS_CALIBRATIONPAGE_POINTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_TYPE_STATIC)->EnableWindow();
			GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_TYPE)->EnableWindow();
			GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_STATUS_STATIC)->EnableWindow();
			GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_STATUS)->EnableWindow();
			return;
		}
	}
	SendDlgItemMessage(IDC_AND_PARAMETERS_CALIBRATIONPAGE_POINTS, LVM_DELETEALLITEMS);
	GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_ID)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_TYPE)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_STATUS)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_ID_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_ID)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_TYPE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_TYPE)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_STATUS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_STATUS)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_POINTS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_POINTS)->EnableWindow(FALSE);
}

void CANDParametersCalibrationPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CANDParametersCalibrationPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CANDParametersCalibrationPage::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_nCalTableRefs.RemoveAll();
	m_nCalValidityRefs.RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CANDParametersCalibrationPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CANDParametersCalibrationPage)
	ON_CBN_SELCHANGE(IDC_AND_PARAMETERS_CALIBRATIONPAGE_NAME, OnSelchangeName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDParametersCalibrationPage message handlers

BOOL CANDParametersCalibrationPage::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	m_szColumns.Add(STRING(IDS_ANDPARAMETERS_CALIBRATIONPAGE_TITLEITEM_NUMBER));
	m_szColumns.Add(STRING(IDS_ANDPARAMETERS_CALIBRATIONPAGE_TITLEITEM_X));
	m_szColumns.Add(STRING(IDS_ANDPARAMETERS_CALIBRATIONPAGE_TITLEITEM_Y));
	GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_POINTS)->GetClientRect(rColumns);
	SendDlgItemMessage(IDC_AND_PARAMETERS_CALIBRATIONPAGE_POINTS, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = (rColumns.Width() - GetSystemMetrics(SM_CXVSCROLL)) / 5; nColumn < nColumns; nWidth = (++nColumn > 0) ? (2 * (rColumns.Width() - GetSystemMetrics(SM_CXVSCROLL)) / 5) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_AND_PARAMETERS_CALIBRATIONPAGE_POINTS), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	return TRUE;
}

void CANDParametersCalibrationPage::OnSelchangeName()
{
	ShowCalibrationInfo();
}


/////////////////////////////////////////////////////////////////////////////
// CANDParametersFolderTabCtrl

IMPLEMENT_DYNCREATE(CANDParametersFolderTabCtrl, CTabCtrl)

CANDParametersFolder *CANDParametersFolderTabCtrl::GetParent() CONST
{
	return((CANDParametersFolder *)CTabCtrl::GetParent());
}

BEGIN_MESSAGE_MAP(CANDParametersFolderTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CANDParametersFolderTabCtrl)
	ON_WM_GETDLGCODE()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDParametersFolderTabCtrl message handlers

UINT CANDParametersFolderTabCtrl::OnGetDlgCode()
{
	return CTabCtrl::OnGetDlgCode() | DLGC_WANTTAB;
}

void CANDParametersFolderTabCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
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
// CANDParametersFolder

IMPLEMENT_DYNCREATE(CANDParametersFolder, CLocalePropertySheetDialog)

CANDParametersFolder::CANDParametersFolder() : CLocalePropertySheetDialog()
{
	AddPage(&m_pageCalibration);
}

BOOL CANDParametersFolder::Create(CWnd *pParentWnd, CONST RECT &rect)
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

VOID CANDParametersFolder::ShowParameterInfo()
{
	m_pageCalibration.ShowParameterInfo();
}
VOID CANDParametersFolder::ShowParameterInfo(CONST CTMParameter *pTMParameter)
{
	m_pageCalibration.ShowParameterInfo(pTMParameter);
}

CANDParametersDialog *CANDParametersFolder::GetParentDialog() CONST
{
	return((CANDParametersDialog *)CLocalePropertySheetDialog::GetParent());
}

CANDWnd *CANDParametersFolder::GetParentDisplay() CONST
{
	return((CANDWnd *)GetParentDialog()->GetParent());
}

BEGIN_MESSAGE_MAP(CANDParametersFolder, CLocalePropertySheetDialog)
	//{{AFX_MSG_MAP(CANDParametersFolder)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDParametersFolder message handlers

void CANDParametersFolder::OnSetFocus(CWnd *pOldWnd)
{
	if (IsWindow(m_wndTabCtrl.GetSafeHwnd()))
	{
		m_wndTabCtrl.SetFocus();
		return;
	}
	CLocalePropertySheetDialog::OnSetFocus(pOldWnd);
}


/////////////////////////////////////////////////////////////////////////////
// CANDParametersDialog dialog

IMPLEMENT_DYNCREATE(CANDParametersDialog, CDisplayDialog)

CANDParametersDialog::CANDParametersDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CANDParametersDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CANDParametersDialog::Create(CWnd *pParentWnd)
{
	return Create(pParentWnd, EMPTYSTRING);
}
INT CANDParametersDialog::Create(CWnd *pParentWnd, LPCTSTR pszParameter)
{
	m_szParameter = pszParameter;
	return CDisplayDialog::Create(pParentWnd, CANDParametersDialog::IDD);
}

CANDWnd *CANDParametersDialog::GetParent() CONST
{
	return((CANDWnd *)CDisplayDialog::GetParent());
}

BOOL CANDParametersDialog::EnumParameters()
{
	INT  nParameter;
	INT  nParameters;
	CString  szParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CANDLayout  cLayout;

	for (nParameter = 0, nParameters = (GetParent()->GetLayout(cLayout)) ? (INT)cLayout.GetSize() : -1; nParameter < nParameters; nParameter++)
	{
		if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(cLayout.GetAt(nParameter)->GetName()))))
		{
			szParameter.Format(STRING(IDS_ANDPARAMETERSDIALOG_PARAMETERFORMAT), (LPCTSTR)pDatabaseTMParameter->GetTag(), (LPCTSTR)pDatabaseTMParameter->GetDescription());
			SendDlgItemMessage(IDC_AND_PARAMETERS_ITEM, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szParameter);
		}
	}
	SendDlgItemMessage(IDC_AND_PARAMETERS_ITEM, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_AND_PARAMETERS_ITEM, CB_FINDSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)m_szParameter), 0));
	GetDlgItem(IDC_AND_PARAMETERS_DETAILS)->EnableWindow((SendDlgItemMessage(IDC_AND_PARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_PARAMETERS_ITEM_STATIC)->EnableWindow((SendDlgItemMessage(IDC_AND_PARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_PARAMETERS_ITEM)->EnableWindow((SendDlgItemMessage(IDC_AND_PARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	m_wndFolderCtrl.EnableWindow((SendDlgItemMessage(IDC_AND_PARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_AND_PARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CANDParametersDialog::ShowParameterInfo()
{
	INT  nParameter;
	INT  nParameters;
	CString  szParameter[2];
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CTMParameter  cTMParameter;
	CANDLayout  cLayout;

	GetDlgItem(IDC_AND_PARAMETERS_ITEM)->GetWindowText(szParameter[0]);
	for (nParameter = 0, nParameters = (GetParent()->GetLayout(cLayout)) ? (INT)cLayout.GetSize() : -1; nParameter < nParameters; nParameter++)
	{
		if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(cLayout.GetAt(nParameter)->GetName()))))
		{
			szParameter[1].Format(STRING(IDS_ANDPARAMETERSDIALOG_PARAMETERFORMAT), (LPCTSTR)pDatabaseTMParameter->GetTag(), (LPCTSTR)pDatabaseTMParameter->GetDescription());
			if (szParameter[0] == szParameter[1]) break;
		}
	}
	if (nParameter < nParameters)
	{
		GetParent()->GetParameterInfo(pDatabaseTMParameter->GetTag(), &cTMParameter);
		m_wndFolderCtrl.ShowParameterInfo(&cTMParameter);
		return;
	}
	m_wndFolderCtrl.ShowParameterInfo();
}

CRect CANDParametersDialog::CalcFolderSize() CONST
{
	CRect  rFolder;

	GetDlgItem(IDC_AND_PARAMETERS_FOLDER)->GetWindowRect(rFolder);
	ScreenToClient(rFolder);
	return rFolder;
}

void CANDParametersDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CANDParametersDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CANDParametersDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CANDParametersDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_AND_PARAMETERS_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_AND_PARAMETERS_ITEM, OnSelchangeParameter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDParametersDialog message handlers

BOOL CANDParametersDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	for (CDisplayDialog::OnInitDialog(); m_wndFolderCtrl.Create(this, CalcFolderSize()) && SetChildSheet(&m_wndFolderCtrl, GetDlgItem(IDC_AND_PARAMETERS_FOLDER - 1)); )
	{
		if (EnumParameters()) ShowParameterInfo();
		break;
	}
	return TRUE;
}

void CANDParametersDialog::OnSelchangeParameter()
{
	ShowParameterInfo();
}

BOOL CANDParametersDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_ANDPARAMETERSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CANDParametersDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_ANDPARAMETERSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CANDRetrieveDialog dialog

IMPLEMENT_DYNCREATE(CANDRetrieveDialog, CDisplayDialog)

CANDRetrieveDialog::CANDRetrieveDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CANDRetrieveDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CANDRetrieveDialog::Create(CWnd *pParentWnd)
{
	CString  szType;
	CString  szTitle;
	CANDWnd  *pANDWnd;
	CANDLayout  cLayout;

	if ((pANDWnd = (CANDWnd *)pParentWnd))
	{
		for (szTitle = (pANDWnd->GetLayout(cLayout)) ? ((!cLayout.GetTitle().IsEmpty()) ? cLayout.GetTitle() : cLayout.GetName()) : STRING(IDS_WINDOW_UNKNOWNTITLE); HIWORD(pANDWnd->GetType()) == AND_TYPE_NORMAL; )
		{
			szType.Format(STRING(IDS_ANDRETRIEVEDIALOG_TYPENORMAL), (LPCTSTR)cLayout.GetName());
			break;
		}
		for (; HIWORD(pANDWnd->GetType()) == AND_TYPE_GENERIC; )
		{
			szType.Format(STRING(IDS_ANDRETRIEVEDIALOG_TYPEGENERIC), (LPCTSTR)cLayout.GetName());
			break;
		}
		for (; HIWORD(pANDWnd->GetType()) == AND_TYPE_TEMPORARY; )
		{
			szType = STRING(IDS_ANDRETRIEVEDIALOG_TYPETEMPORARY);
			break;
		}
		return Create(pParentWnd, szTitle, szType);
	}
	return -1;
}
INT CANDRetrieveDialog::Create(CWnd *pParentWnd, LPCTSTR pszTitle, LPCTSTR pszType)
{
	m_szType = pszType;
	m_szTitle = pszTitle;
	return CDisplayDialog::Create(pParentWnd, CANDRetrieveDialog::IDD);
}

BOOL CANDRetrieveDialog::GetMode(UINT &nMode) CONST
{
	nMode = (!IsDlgButtonChecked(IDC_AND_RETRIEVE_REALTIME)) ? ((IsDlgButtonChecked(IDC_AND_RETRIEVE_HISTORY_EXACTTIME)) ? AND_RETRIEVE_EXACTTIME : 0) : 0;
	nMode |= (!IsDlgButtonChecked(IDC_AND_RETRIEVE_REALTIME)) ? ((IsDlgButtonChecked(IDC_AND_RETRIEVE_HISTORY_STOPBYTIME) || IsDlgButtonChecked(IDC_AND_RETRIEVE_HISTORY_STOPBYEND) || IsDlgButtonChecked(IDC_AND_RETRIEVE_HISTORY_STOPBYREALTIME)) ? ((!IsDlgButtonChecked(IDC_AND_RETRIEVE_HISTORY_STOPBYTIME)) ? ((!IsDlgButtonChecked(IDC_AND_RETRIEVE_HISTORY_STOPBYEND)) ? AND_RETRIEVE_STOPBYREALTIME : AND_RETRIEVE_STOPBYEND) : AND_RETRIEVE_STOPBYTIME) : 0) : 0;
	nMode |= (!IsDlgButtonChecked(IDC_AND_RETRIEVE_REALTIME)) ? ((IsDlgButtonChecked(IDC_AND_RETRIEVE_HISTORY_AUTOMATIC)) ? AND_RETRIEVE_AUTOFORWARD : ((IsDlgButtonChecked(IDC_AND_RETRIEVE_HISTORY_PSEUDOREALTIME)) ? AND_RETRIEVE_PSEUDOREALTIME : AND_RETRIEVE_MANUALFORWARD)) : 0;
	return TRUE;
}

BOOL CANDRetrieveDialog::GetSpeed(UINT &nSpeed) CONST
{
	nSpeed = (!IsDlgButtonChecked(IDC_AND_RETRIEVE_HISTORY_AUTOMATIC)) ? (UINT)((GetDlgItem(IDC_AND_RETRIEVE_HISTORY_SPEED)->SendMessage(TBM_GETRANGEMIN) + GetDlgItem(IDC_AND_RETRIEVE_HISTORY_SPEED)->SendMessage(TBM_GETRANGEMAX)) / 2) : (UINT)GetDlgItem(IDC_AND_RETRIEVE_HISTORY_SPEED)->SendMessage(TBM_GETPOS);
	return((IsDlgButtonChecked(IDC_AND_RETRIEVE_HISTORY_AUTOMATIC)) ? TRUE : FALSE);
}

BOOL CANDRetrieveDialog::GetInterval(CTimeSpan &tInterval) CONST
{
	tInterval = (IsDlgButtonChecked(IDC_AND_RETRIEVE_HISTORY_INTERVAL)) ? (SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_AND_RETRIEVE_HISTORY_INTERVALTIME))) : 0;
	return((IsDlgButtonChecked(IDC_AND_RETRIEVE_HISTORY_INTERVAL)) ? TRUE : FALSE);
}

BOOL CANDRetrieveDialog::GetStartTime(CTimeKey &tTimeKey) CONST
{
	CTimeKey  tTime;

	for (tTimeKey = 0; !IsDlgButtonChecked(IDC_AND_RETRIEVE_REALTIME) && (tTime = Timespinbox_GetTime(GetDlgItem(IDC_AND_RETRIEVE_HISTORY_STARTTIME))) > 0; )
	{
		tTimeKey = tTime;
		return TRUE;
	}
	return FALSE;
}

BOOL CANDRetrieveDialog::GetStopTime(CTimeKey &tTimeKey) CONST
{
	CTimeKey  tTime;

	for (tTimeKey = 0; IsDlgButtonChecked(IDC_AND_RETRIEVE_HISTORY_STOPBYTIME) && (tTime = Timespinbox_GetTime(GetDlgItem(IDC_AND_RETRIEVE_HISTORY_STOPTIME))) > 0; )
	{
		tTimeKey = tTime;
		return TRUE;
	}
	return FALSE;
}

CANDOpenDialog *CANDRetrieveDialog::GetParentDialog() CONST
{
	return((GetParent() != (CWnd *)GetParentDisplay()) ? (CANDOpenDialog *)GetParent() : (CANDOpenDialog *)NULL);
}

CANDWnd *CANDRetrieveDialog::GetParentDisplay() CONST
{
	return((CANDWnd *)CDisplayDialog::GetParentDisplay());
}

BOOL CANDRetrieveDialog::SetRetrieveInfo()
{
	UINT  nMode;
	UINT  nSpeed;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;

	if (GetRetrieveInfo(nMode, nSpeed, tInterval, tStartTime, tStopTime))
	{
		Spinbox_SetPos(GetDlgItem(IDC_AND_RETRIEVE_HISTORY_INTERVALTIME), tInterval.GetTotalSeconds() / SECONDSPERMINUTE);
		Timespinbox_SetTime(GetDlgItem(IDC_AND_RETRIEVE_HISTORY_STARTTIME), (tStartTime > 0 || GetTMService()->GetRecentTMHistoryTimeKey(tStartTime)) ? tStartTime : CTime::GetCurrentTime().GetTime());
		Timespinbox_SetTime(GetDlgItem(IDC_AND_RETRIEVE_HISTORY_STOPTIME), (tStopTime.GetTime() > 0) ? tStopTime : CTime::GetCurrentTime().GetTime());
		Timespinbox_SetRange(GetDlgItem(IDC_AND_RETRIEVE_HISTORY_STOPTIME), Timespinbox_GetTime(GetDlgItem(IDC_AND_RETRIEVE_HISTORY_STARTTIME)), MAX_TIMEKEY);
		SendDlgItemMessage(IDC_AND_RETRIEVE_HISTORY_SPEED, TBM_SETPOS, TRUE, (!IsDlgButtonChecked(IDC_AND_RETRIEVE_REALTIME)) ? ((nMode) ? (((nMode & AND_RETRIEVE_AUTOFORWARD) || (nMode & AND_RETRIEVE_AUTOBACKWARD)) ? nSpeed : 0) : ((SendDlgItemMessage(IDC_AND_RETRIEVE_HISTORY_SPEED, TBM_GETRANGEMIN) + SendDlgItemMessage(IDC_AND_RETRIEVE_HISTORY_SPEED, TBM_GETRANGEMAX)) / 2)) : 0);
		CheckDlgButton(IDC_AND_RETRIEVE_HISTORY_EXACTTIME, (!IsDlgButtonChecked(IDC_AND_RETRIEVE_REALTIME) && (nMode & AND_RETRIEVE_EXACTTIME)) ? TRUE : FALSE);
		CheckDlgButton(IDC_AND_RETRIEVE_HISTORY_STOPBYTIME, (!IsDlgButtonChecked(IDC_AND_RETRIEVE_REALTIME) && (nMode & AND_RETRIEVE_STOPBYTIME) && (nMode & (AND_RETRIEVE_MANUALFORWARD | AND_RETRIEVE_MANUALBACKWARD)) == 0) ? TRUE : FALSE);
		CheckDlgButton(IDC_AND_RETRIEVE_HISTORY_STOPBYEND, (!IsDlgButtonChecked(IDC_AND_RETRIEVE_REALTIME) && (nMode & AND_RETRIEVE_STOPBYEND) && (nMode & (AND_RETRIEVE_MANUALFORWARD | AND_RETRIEVE_MANUALBACKWARD)) == 0) ? TRUE : FALSE);
		CheckDlgButton(IDC_AND_RETRIEVE_HISTORY_STOPBYREALTIME, (!IsDlgButtonChecked(IDC_AND_RETRIEVE_REALTIME) && (!nMode || (nMode & AND_RETRIEVE_STOPBYREALTIME))) ? TRUE : FALSE);
		CheckDlgButton(IDC_AND_RETRIEVE_HISTORY_AUTOMATIC, (!IsDlgButtonChecked(IDC_AND_RETRIEVE_REALTIME) && (!nMode || (nMode & AND_RETRIEVE_AUTOFORWARD) || (nMode & AND_RETRIEVE_AUTOBACKWARD))) ? TRUE : FALSE);
		CheckDlgButton(IDC_AND_RETRIEVE_HISTORY_MANUAL, (!IsDlgButtonChecked(IDC_AND_RETRIEVE_REALTIME) && ((nMode & AND_RETRIEVE_MANUALFORWARD) || (nMode & AND_RETRIEVE_MANUALBACKWARD))) ? TRUE : FALSE);
		CheckDlgButton(IDC_AND_RETRIEVE_HISTORY_PSEUDOREALTIME, (!IsDlgButtonChecked(IDC_AND_RETRIEVE_REALTIME) && (nMode & AND_RETRIEVE_PSEUDOREALTIME)) ? TRUE : FALSE);
		CheckDlgButton(IDC_AND_RETRIEVE_HISTORY_INTERVAL, (!IsDlgButtonChecked(IDC_AND_RETRIEVE_REALTIME) && (nMode & AND_RETRIEVE_PSEUDOREALTIME) == 0 && tInterval.GetTotalSeconds() > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_AND_RETRIEVE_HISTORY)->EnableWindow(!IsDlgButtonChecked(IDC_AND_RETRIEVE_REALTIME));
		GetDlgItem(IDC_AND_RETRIEVE_HISTORY_START_STATIC)->EnableWindow(!IsDlgButtonChecked(IDC_AND_RETRIEVE_REALTIME));
		GetDlgItem(IDC_AND_RETRIEVE_HISTORY_STARTTIME)->EnableWindow(!IsDlgButtonChecked(IDC_AND_RETRIEVE_REALTIME));
		GetDlgItem(IDC_AND_RETRIEVE_HISTORY_EXACTTIME)->EnableWindow(!IsDlgButtonChecked(IDC_AND_RETRIEVE_REALTIME));
		GetDlgItem(IDC_AND_RETRIEVE_HISTORY_STOP_STATIC)->EnableWindow(!IsDlgButtonChecked(IDC_AND_RETRIEVE_REALTIME));
		GetDlgItem(IDC_AND_RETRIEVE_HISTORY_STOPBYTIME)->EnableWindow(!IsDlgButtonChecked(IDC_AND_RETRIEVE_REALTIME) && !IsDlgButtonChecked(IDC_AND_RETRIEVE_HISTORY_MANUAL));
		GetDlgItem(IDC_AND_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(!IsDlgButtonChecked(IDC_AND_RETRIEVE_REALTIME) && IsDlgButtonChecked(IDC_AND_RETRIEVE_HISTORY_STOPBYTIME));
		GetDlgItem(IDC_AND_RETRIEVE_HISTORY_STOPBYEND)->EnableWindow(!IsDlgButtonChecked(IDC_AND_RETRIEVE_REALTIME) && !IsDlgButtonChecked(IDC_AND_RETRIEVE_HISTORY_MANUAL));
		GetDlgItem(IDC_AND_RETRIEVE_HISTORY_STOPBYREALTIME)->EnableWindow(!IsDlgButtonChecked(IDC_AND_RETRIEVE_REALTIME));
		GetDlgItem(IDC_AND_RETRIEVE_HISTORY_PLAYBACKMODE)->EnableWindow(!IsDlgButtonChecked(IDC_AND_RETRIEVE_REALTIME));
		GetDlgItem(IDC_AND_RETRIEVE_HISTORY_AUTOMATIC)->EnableWindow(!IsDlgButtonChecked(IDC_AND_RETRIEVE_REALTIME));
		GetDlgItem(IDC_AND_RETRIEVE_HISTORY_PSEUDOREALTIME)->EnableWindow(!IsDlgButtonChecked(IDC_AND_RETRIEVE_REALTIME));
		GetDlgItem(IDC_AND_RETRIEVE_HISTORY_MANUAL)->EnableWindow(!IsDlgButtonChecked(IDC_AND_RETRIEVE_REALTIME));
		GetDlgItem(IDC_AND_RETRIEVE_HISTORY_SPEED_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_AND_RETRIEVE_HISTORY_AUTOMATIC));
		GetDlgItem(IDC_AND_RETRIEVE_HISTORY_SPEED)->EnableWindow(IsDlgButtonChecked(IDC_AND_RETRIEVE_HISTORY_AUTOMATIC));
		GetDlgItem(IDC_AND_RETRIEVE_HISTORY_SLOW)->EnableWindow(IsDlgButtonChecked(IDC_AND_RETRIEVE_HISTORY_AUTOMATIC));
		GetDlgItem(IDC_AND_RETRIEVE_HISTORY_FAST)->EnableWindow(IsDlgButtonChecked(IDC_AND_RETRIEVE_HISTORY_AUTOMATIC));
		GetDlgItem(IDC_AND_RETRIEVE_HISTORY_INTERVAL)->EnableWindow(!IsDlgButtonChecked(IDC_AND_RETRIEVE_REALTIME) && !IsDlgButtonChecked(IDC_AND_RETRIEVE_HISTORY_PSEUDOREALTIME));
		GetDlgItem(IDC_AND_RETRIEVE_HISTORY_INTERVALTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_AND_RETRIEVE_HISTORY_INTERVAL));
		GetDlgItem(IDC_AND_RETRIEVE_HISTORY_INTERVALTIME)->EnableWindow(IsDlgButtonChecked(IDC_AND_RETRIEVE_HISTORY_INTERVAL));
		return TRUE;
	}
	return FALSE;
}

BOOL CANDRetrieveDialog::GetRetrieveInfo(UINT &nMode, UINT &nSpeed, CTimeSpan &tInterval, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	CANDWnd  *pANDWnd;
	CANDOpenDialog  *pDialog;

	if ((pDialog = GetParentDialog()))
	{
		for (pDialog->GetRetrieveMode(nMode), nSpeed = 0, tInterval = 0, tStartTime = tStopTime = 0; nMode; )
		{
			pDialog->GetRetrieveSpeed(nSpeed);
			pDialog->GetRetrieveInterval(tInterval);
			pDialog->GetRetrieveStartTime(tStartTime);
			pDialog->GetRetrieveStopTime(tStopTime);
			break;
		}
		return TRUE;
	}
	if ((pANDWnd = GetParentDisplay()))
	{
		for (pANDWnd->GetRetrieveMode(nMode), nSpeed = 0, tInterval = 0, tStartTime = tStopTime = 0; nMode; )
		{
			pANDWnd->GetRetrieveSpeed(nSpeed);
			pANDWnd->GetRetrieveInterval(tInterval);
			pANDWnd->GetRetrieveStartTime(tStartTime);
			pANDWnd->GetRetrieveStopTime(tStopTime);
			break;
		}
		return TRUE;
	}
	return FALSE;
}

void CANDRetrieveDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CANDRetrieveDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CANDRetrieveDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CANDRetrieveDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_AND_RETRIEVE_REALTIME, OnRetrieveRealtime)
	ON_BN_CLICKED(IDC_AND_RETRIEVE_HISTORY_STOPBYTIME, OnRetrieveByTime)
	ON_BN_CLICKED(IDC_AND_RETRIEVE_HISTORY_STOPBYEND, OnRetrieveByEnd)
	ON_BN_CLICKED(IDC_AND_RETRIEVE_HISTORY_STOPBYREALTIME, OnRetrieveByRealtime)
	ON_BN_CLICKED(IDC_AND_RETRIEVE_HISTORY_AUTOMATIC, OnRetrieveAutomatic)
	ON_BN_CLICKED(IDC_AND_RETRIEVE_HISTORY_PSEUDOREALTIME, OnRetrievePseudoRealtime)
	ON_BN_CLICKED(IDC_AND_RETRIEVE_HISTORY_MANUAL, OnRetrieveManual)
	ON_BN_CLICKED(IDC_AND_RETRIEVE_HISTORY_INTERVAL, OnRetrieveInterval)
	ON_BN_CLICKED(IDC_AND_RETRIEVE_HELP, OnHelp)
	ON_CONTROL(TSBXN_CHANGE, IDC_AND_RETRIEVE_HISTORY_STARTTIME, OnSpinchangeRetrieveStartTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDRetrieveDialog message handlers

BOOL CANDRetrieveDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	for (CDisplayDialog::OnInitDialog(), SendDlgItemMessage(IDC_AND_RETRIEVE_HISTORY_SPEED, TBM_SETRANGE, TRUE, MAKELPARAM(0, 10)), Spinbox_SetRange(GetDlgItem(IDC_AND_RETRIEVE_HISTORY_INTERVALTIME), ANDRETRIEVEDIALOG_MINIMUMINTERVAL, ANDRETRIEVEDIALOG_MAXIMUMINTERVAL), GetDlgItem(IDC_AND_RETRIEVE_TITLE)->SetWindowText(m_szTitle); SetRetrieveInfo(); )
	{
		GetDlgItem(IDC_AND_RETRIEVE_TYPE)->SetWindowText(m_szType);
		GetDlgItem(IDC_AND_RETRIEVE_DETAILS)->EnableWindow();
		GetDlgItem(IDC_AND_RETRIEVE_TITLE_STATIC)->EnableWindow();
		GetDlgItem(IDC_AND_RETRIEVE_TITLE)->EnableWindow();
		GetDlgItem(IDC_AND_RETRIEVE_TYPE_STATIC)->EnableWindow();
		GetDlgItem(IDC_AND_RETRIEVE_TYPE)->EnableWindow();
		GetDlgItem(IDC_AND_RETRIEVE_REALTIME)->EnableWindow((GetParentDisplay()->GetMode() == DISPLAY_MODE_HISTORY) ? TRUE : FALSE);
		GetDlgItem(IDC_AND_RETRIEVE_HISTORY_STARTTIME)->SetFocus();
		GetDlgItem(IDOK)->EnableWindow();
		return FALSE;
	}
	return TRUE;
}

void CANDRetrieveDialog::OnRetrieveRealtime()
{
	SetRetrieveInfo();
}

void CANDRetrieveDialog::OnRetrieveByTime()
{
	CheckDlgButton(IDC_AND_RETRIEVE_HISTORY_STOPBYTIME, TRUE);
	CheckDlgButton(IDC_AND_RETRIEVE_HISTORY_STOPBYEND, FALSE);
	CheckDlgButton(IDC_AND_RETRIEVE_HISTORY_STOPBYREALTIME, FALSE);
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_STOPTIME)->EnableWindow();
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_STOPTIME)->SetFocus();
}

void CANDRetrieveDialog::OnRetrieveByEnd()
{
	CheckDlgButton(IDC_AND_RETRIEVE_HISTORY_STOPBYTIME, FALSE);
	CheckDlgButton(IDC_AND_RETRIEVE_HISTORY_STOPBYEND, TRUE);
	CheckDlgButton(IDC_AND_RETRIEVE_HISTORY_STOPBYREALTIME, FALSE);
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(FALSE);
}

void CANDRetrieveDialog::OnRetrieveByRealtime()
{
	CheckDlgButton(IDC_AND_RETRIEVE_HISTORY_STOPBYTIME, FALSE);
	CheckDlgButton(IDC_AND_RETRIEVE_HISTORY_STOPBYEND, FALSE);
	CheckDlgButton(IDC_AND_RETRIEVE_HISTORY_STOPBYREALTIME, (IsDlgButtonChecked(IDC_AND_RETRIEVE_HISTORY_MANUAL)) ? !IsDlgButtonChecked(IDC_AND_RETRIEVE_HISTORY_STOPBYREALTIME) : TRUE);
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(FALSE);
}

void CANDRetrieveDialog::OnRetrieveAutomatic()
{
	SendDlgItemMessage(IDC_AND_RETRIEVE_HISTORY_SPEED, TBM_SETPOS, TRUE, (SendDlgItemMessage(IDC_AND_RETRIEVE_HISTORY_SPEED, TBM_GETRANGEMIN) + SendDlgItemMessage(IDC_AND_RETRIEVE_HISTORY_SPEED, TBM_GETRANGEMAX)) / 2);
	CheckDlgButton(IDC_AND_RETRIEVE_HISTORY_STOPBYTIME, FALSE);
	CheckDlgButton(IDC_AND_RETRIEVE_HISTORY_STOPBYEND, FALSE);
	CheckDlgButton(IDC_AND_RETRIEVE_HISTORY_STOPBYREALTIME, TRUE);
	CheckDlgButton(IDC_AND_RETRIEVE_HISTORY_AUTOMATIC, TRUE);
	CheckDlgButton(IDC_AND_RETRIEVE_HISTORY_PSEUDOREALTIME, FALSE);
	CheckDlgButton(IDC_AND_RETRIEVE_HISTORY_MANUAL, FALSE);
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_STOP_STATIC)->EnableWindow();
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_STOPBYTIME)->EnableWindow();
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_AND_RETRIEVE_HISTORY_STOPBYTIME));
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_STOPBYEND)->EnableWindow();
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_STOPBYREALTIME)->EnableWindow();
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_SPEED_STATIC)->EnableWindow();
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_SPEED)->EnableWindow();
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_SLOW)->EnableWindow();
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_FAST)->EnableWindow();
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_INTERVAL)->EnableWindow();
}

void CANDRetrieveDialog::OnRetrievePseudoRealtime()
{
	SendDlgItemMessage(IDC_AND_RETRIEVE_HISTORY_SPEED, TBM_SETPOS, TRUE, 0);
	CheckDlgButton(IDC_AND_RETRIEVE_HISTORY_STOPBYTIME, FALSE);
	CheckDlgButton(IDC_AND_RETRIEVE_HISTORY_STOPBYEND, FALSE);
	CheckDlgButton(IDC_AND_RETRIEVE_HISTORY_STOPBYREALTIME, TRUE);
	CheckDlgButton(IDC_AND_RETRIEVE_HISTORY_AUTOMATIC, FALSE);
	CheckDlgButton(IDC_AND_RETRIEVE_HISTORY_PSEUDOREALTIME, TRUE);
	CheckDlgButton(IDC_AND_RETRIEVE_HISTORY_MANUAL, FALSE);
	CheckDlgButton(IDC_AND_RETRIEVE_HISTORY_INTERVAL, FALSE);
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_STOP_STATIC)->EnableWindow();
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_STOPBYTIME)->EnableWindow();
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_AND_RETRIEVE_HISTORY_STOPBYTIME));
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_STOPBYEND)->EnableWindow();
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_STOPBYREALTIME)->EnableWindow();
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_SPEED_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_SPEED)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_SLOW)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_FAST)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_INTERVAL)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_INTERVALTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_INTERVALTIME)->EnableWindow(FALSE);
}

void CANDRetrieveDialog::OnRetrieveManual()
{
	SendDlgItemMessage(IDC_AND_RETRIEVE_HISTORY_SPEED, TBM_SETPOS, TRUE, 0);
	CheckDlgButton(IDC_AND_RETRIEVE_HISTORY_STOPBYTIME, FALSE);
	CheckDlgButton(IDC_AND_RETRIEVE_HISTORY_STOPBYEND, FALSE);
	CheckDlgButton(IDC_AND_RETRIEVE_HISTORY_STOPBYREALTIME, FALSE);
	CheckDlgButton(IDC_AND_RETRIEVE_HISTORY_AUTOMATIC, FALSE);
	CheckDlgButton(IDC_AND_RETRIEVE_HISTORY_PSEUDOREALTIME, FALSE);
	CheckDlgButton(IDC_AND_RETRIEVE_HISTORY_MANUAL, TRUE);
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_STOP_STATIC)->EnableWindow();
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_STOPBYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_STOPBYEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_STOPBYREALTIME)->EnableWindow();
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_SPEED_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_SPEED)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_SLOW)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_FAST)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_INTERVAL)->EnableWindow();
}

void CANDRetrieveDialog::OnRetrieveInterval()
{
	Spinbox_SetPos(GetDlgItem(IDC_AND_RETRIEVE_HISTORY_INTERVALTIME), ANDRETRIEVEDIALOG_DEFAULTINTERVAL);
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_INTERVALTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_AND_RETRIEVE_HISTORY_INTERVAL));
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_INTERVALTIME)->EnableWindow(IsDlgButtonChecked(IDC_AND_RETRIEVE_HISTORY_INTERVAL));
	GetDlgItem(IDC_AND_RETRIEVE_HISTORY_INTERVALTIME)->SetFocus();
}

void CANDRetrieveDialog::OnSpinchangeRetrieveStartTime()
{
	Timespinbox_SetRange(GetDlgItem(IDC_AND_RETRIEVE_HISTORY_STOPTIME), Timespinbox_GetTime(GetDlgItem(IDC_AND_RETRIEVE_HISTORY_STARTTIME)), MAX_TIMEKEY);
}

void CANDRetrieveDialog::OnOK()
{
	CANDWnd  *pANDWnd;
	CTimeKey  tTimeKey;
	CANDLayout  cLayout;
	CDisplayWnd  *pDisplayWnd;
	CANDOpenDialog  *pDialog;
	CHourglassCursor  cCursor;

	if ((pDisplayWnd = GetParentDisplay()->GetLink()))
	{
		if (GetParentDisplay()->Lock())
		{
			GetParentDisplay()->SetLink();
			GetParentDisplay()->SetLinkByName();
			GetParentDisplay()->Unlock();
		}
		if (pDisplayWnd->Lock())
		{
			pDisplayWnd->RemoveLink(GetParentDisplay());
			pDisplayWnd->Unlock();
		}
	}
	for (; !GetParentDialog(); )
	{
		if (IsDlgButtonChecked(IDC_AND_RETRIEVE_REALTIME))
		{
			if ((pANDWnd = (GetParentDisplay()->GetLayout(cLayout)) ? GetParentDisplay()->Find(GetParentDisplay()->GetType(), DISPLAY_MODE_REALTIME, cLayout.GetName()) : (CANDWnd *)NULL))
			{
				for (GetDisplayArea()->ActivateDisplay(pANDWnd); pANDWnd != GetParentDisplay(); )
				{
					GetParentDisplay()->PostMessage(WM_CLOSE);
					break;
				}
				EndDialog(IDOK);
				return;
			}
		}
		GetParentDisplay()->OnCloseRetrieveDialog(IDOK);
		break;
	}
	for (; (pDialog = GetParentDialog()); )
	{
		pDialog->OnCloseRetrieveDialog(IDOK);
		break;
	}
	for (; GetStartTime(tTimeKey); )
	{
		GetTMService()->SetRecentTMHistoryTimeKey(tTimeKey);
		break;
	}
	CDisplayDialog::OnOK();
}

void CANDRetrieveDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	if (!GetParentDialog()) GetParentDisplay()->OnCloseRetrieveDialog(IDCANCEL);
	else  GetParentDialog()->OnCloseRetrieveDialog(IDCANCEL);
	CDisplayDialog::OnCancel();
}

BOOL CANDRetrieveDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_ANDRETRIEVEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CANDRetrieveDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_ANDRETRIEVEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CANDImportDialog dialog

IMPLEMENT_DYNCREATE(CANDImportDialog, CLocaleDialog)

CANDImportDialog::CANDImportDialog(CWnd *pParentWnd) : CLocaleDialog(CANDImportDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CANDImportDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CANDImportDialog::Initialize()
{
	EnumTemporaryANDs(m_pDisplays[0]);
	return TRUE;
}

VOID CANDImportDialog::EnumDisplays()
{
	INT  nLayout;
	INT  nLayouts;
	DWORD  cbData;
	CFileEx  cFile;
	CString  szMessage;
	CString  szFileName;
	CByteArray  nFileData;
	CANDLayout  *pANDLayout;

	SendDlgItemMessage(IDC_AND_IMPORT_DIRECTORY, CB_RESETCONTENT);
	GetDlgItem(IDC_AND_IMPORT_FILENAME)->GetWindowText(szFileName);
	if (cFile.Open(szFileName, CFile::modeRead | CFile::shareExclusive))
	{
		nFileData.SetSize((cbData = (DWORD)cFile.GetLength()*sizeof(BYTE)));
		if (ReadFile(cFile.m_hFile, nFileData.GetData(), (DWORD)nFileData.GetSize(), &cbData, (LPOVERLAPPED)NULL))
		{
			for (nLayout = 0, nLayouts = (m_pDisplays[1].Unmap(nFileData)) ? (INT)m_pDisplays[1].GetSize() : 0; nLayout < nLayouts; nLayout++)
			{
				if ((pANDLayout = m_pDisplays[1].GetAt(nLayout))) SendDlgItemMessage(IDC_AND_IMPORT_DIRECTORY, CB_INSERTSTRING, nLayout, (LPARAM)(LPCTSTR)pANDLayout->GetTitle());
				continue;
			}
		}
		else
		{
			szMessage = STRING(IDS_AND_IMPORT_FILE_FAILURE);
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_ERROR, szMessage);
		}
		cFile.Close();
	}
	else
	{
		szMessage = STRING(IDS_AND_IMPORT_FILE_FAILURE);
		ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_ERROR, szMessage);
	}
	if (SendDlgItemMessage(IDC_AND_IMPORT_DIRECTORY, CB_GETCOUNT) > 0)
	{
		SendDlgItemMessage(IDC_AND_IMPORT_DIRECTORY, CB_SETCURSEL);
		GetDlgItem(IDC_AND_IMPORT_DIRECTORY_STATIC)->EnableWindow();
		GetDlgItem(IDC_AND_IMPORT_DIRECTORY)->EnableWindow();
		return;
	}
	GetDlgItem(IDC_AND_IMPORT_DIRECTORY_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_IMPORT_DIRECTORY)->EnableWindow(FALSE);
}

BOOL CANDImportDialog::Check(BOOL bModified) CONST
{
	return((m_pDisplays[2].GetSize() > 0) ? TRUE : FALSE);
}

void CANDImportDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CANDImportDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CANDImportDialog::PostNcDestroy()
{
	m_pDisplays[0].RemoveAll();
	m_pDisplays[1].RemoveAll();
	m_pDisplays[2].RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CANDImportDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CANDImportDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_AND_IMPORT_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_AND_IMPORT_INSPECT, OnInspect)
	ON_BN_CLICKED(IDC_AND_IMPORT_ADD, OnAdd)
	ON_BN_CLICKED(IDC_AND_IMPORT_ADDALL, OnAddAll)
	ON_BN_CLICKED(IDC_AND_IMPORT_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_AND_IMPORT_REMOVEALL, OnRemoveAll)
	ON_BN_CLICKED(IDC_AND_IMPORT_HELP, OnHelp)
	ON_EN_CHANGE(IDC_AND_IMPORT_FILENAME, OnEditchangeFileName)
	ON_CBN_SELCHANGE(IDC_AND_IMPORT_DIRECTORY, OnSelchangeSource)
	ON_LBN_SELCHANGE(IDC_AND_IMPORT_LIST, OnSelchangeDestination)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDImportDialog message handlers

BOOL CANDImportDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_AND_IMPORT_DETAILS)->EnableWindow();
	GetDlgItem(IDC_AND_IMPORT_FILENAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_AND_IMPORT_FILENAME)->EnableWindow();
	GetDlgItem(IDC_AND_IMPORT_BROWSE)->EnableWindow();
	GetDlgItem(IDC_AND_IMPORT_DIRECTORY_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_IMPORT_DIRECTORY)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_IMPORT_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_IMPORT_ADDALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_IMPORT_ATTENTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_IMPORT_ATTENTION_TEXT)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_IMPORT_LIST_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_IMPORT_LIST)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_IMPORT_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_IMPORT_REMOVEALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_IMPORT_FILENAME)->SetFocus();
	return FALSE;
}

void CANDImportDialog::OnBrowse()
{
	CString  szFileName;
	CFileBrowseDialog  cFileBrowseDialog(this, IDC_AND_IMPORT_FILENAME, STRING(IDS_FILEBROWSEDIALOG_DATABASEFILEEXTENSION), STRING(IDS_FILEBROWSEDIALOG_DATABASEFILEFILTER));

	if (cFileBrowseDialog.DoModal() == IDOK)
	{
		GetDlgItem(IDC_AND_IMPORT_FILENAME)->SetWindowText((szFileName = cFileBrowseDialog.GetPathName()));
		GetDlgItem(IDC_AND_IMPORT_BROWSE)->ShowWindow((szFileName.IsEmpty()) ? SW_SHOW : SW_HIDE);
		GetDlgItem(IDC_AND_IMPORT_INSPECT)->ShowWindow((!szFileName.IsEmpty()) ? SW_SHOW : SW_HIDE);
		GetDlgItem(IDC_AND_IMPORT_BROWSE)->EnableWindow((szFileName.IsEmpty()) ? TRUE : FALSE);
		GetDlgItem(IDC_AND_IMPORT_INSPECT)->EnableWindow((!szFileName.IsEmpty()) ? TRUE : FALSE);
	}
	SendDlgItemMessage(IDC_AND_IMPORT_FILENAME, EM_SETSEL, 0, (LPARAM)-1);
	GetDlgItem(IDC_AND_IMPORT_FILENAME)->SetFocus();
}

void CANDImportDialog::OnInspect()
{
	INT  nLayout;
	INT  nLayouts;
	CString  szLayout;
	CHourglassCursor  cCursor;

	EnumDisplays();
	for (nLayout = 0, nLayouts = (INT)SendDlgItemMessage(IDC_AND_IMPORT_DIRECTORY, CB_GETCOUNT); nLayout < nLayouts; nLayout++)
	{
		if (SendDlgItemMessage(IDC_AND_IMPORT_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)Combobox_GetText(GetDlgItem(IDC_AND_IMPORT_DIRECTORY), nLayout)) < 0) break;
		continue;
	}
	GetDlgItem(IDC_AND_IMPORT_DIRECTORY)->GetWindowText(szLayout);
	GetDlgItem(IDC_AND_IMPORT_ADD)->EnableWindow((SendDlgItemMessage(IDC_AND_IMPORT_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szLayout) < 0 && !szLayout.IsEmpty()) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_IMPORT_ADDALL)->EnableWindow((nLayout < nLayouts) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_IMPORT_DIRECTORY)->SetFocus();
}

void CANDImportDialog::OnAdd()
{
	INT  nLayout;
	INT  nLayouts;
	CString  szLayout;
	CANDLayout  *pLayout[2];
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_AND_IMPORT_DIRECTORY)->GetWindowText(szLayout);
	if (SendDlgItemMessage(IDC_AND_IMPORT_LIST, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szLayout) >= 0)
	{
		if ((pLayout[0] = m_pDisplays[1].GetAt(m_pDisplays[1].Find(szLayout))))
		{
			if ((pLayout[1] = new CANDLayout))
			{
				pLayout[1]->Copy(pLayout[0]);
				if (m_pDisplays[2].Add(pLayout[1]) < 0) delete pLayout[1];
			}
		}
		for (nLayout = 0, nLayouts = (INT)SendDlgItemMessage(IDC_AND_IMPORT_LIST, LB_GETCOUNT); nLayout < nLayouts; nLayout++)
		{
			if (m_pDisplays[0].Find(Listbox_GetText(GetDlgItem(IDC_AND_IMPORT_LIST), nLayout)) >= 0) break;
			continue;
		}
		SendDlgItemMessage(IDC_AND_IMPORT_LIST, LB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_AND_IMPORT_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szLayout));
		GetDlgItem(IDC_AND_IMPORT_ATTENTION)->ShowWindow((nLayout < nLayouts) ? SW_SHOW : SW_HIDE);
		GetDlgItem(IDC_AND_IMPORT_ATTENTION_TEXT)->ShowWindow((nLayout < nLayouts) ? SW_SHOW : SW_HIDE);
		GetDlgItem(IDC_AND_IMPORT_ATTENTION)->EnableWindow((nLayout < nLayouts) ? TRUE : FALSE);
		GetDlgItem(IDC_AND_IMPORT_ATTENTION_TEXT)->EnableWindow((nLayout < nLayouts) ? TRUE : FALSE);
		for (nLayout = 0, nLayouts = (INT)SendDlgItemMessage(IDC_AND_IMPORT_DIRECTORY, CB_GETCOUNT); nLayout < nLayouts; nLayout++)
		{
			if (SendDlgItemMessage(IDC_AND_IMPORT_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)Combobox_GetText(GetDlgItem(IDC_AND_IMPORT_DIRECTORY), nLayout)) < 0) break;
			continue;
		}
		GetDlgItem(IDC_AND_IMPORT_ADD)->EnableWindow(FALSE);
		GetDlgItem(IDC_AND_IMPORT_ADDALL)->EnableWindow((nLayout < nLayouts) ? TRUE : FALSE);
		GetDlgItem(IDC_AND_IMPORT_LIST_STATIC)->EnableWindow();
		GetDlgItem(IDC_AND_IMPORT_LIST)->EnableWindow();
		GetDlgItem(IDC_AND_IMPORT_REMOVE)->EnableWindow();
		GetDlgItem(IDC_AND_IMPORT_REMOVEALL)->EnableWindow();
		GetDlgItem(IDC_AND_IMPORT_DIRECTORY)->SetFocus();
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDImportDialog::OnAddAll()
{
	INT  nLayout;
	INT  nLayouts;
	CString  szLayout;
	CANDLayout  *pLayout[2];
	CHourglassCursor  cCursor;

	for (nLayout = 0, nLayouts = (INT)SendDlgItemMessage(IDC_AND_IMPORT_DIRECTORY, CB_GETCOUNT); nLayout < nLayouts; nLayout++)
	{
		if (SendDlgItemMessage(IDC_AND_IMPORT_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)(szLayout = Combobox_GetText(GetDlgItem(IDC_AND_IMPORT_DIRECTORY), nLayout))) < 0)
		{
			SendDlgItemMessage(IDC_AND_IMPORT_LIST, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szLayout);
			continue;
		}
	}
	for (nLayout = 0, nLayouts = (INT)m_pDisplays[1].GetSize(); nLayout < nLayouts; nLayout++)
	{
		if ((pLayout[0] = m_pDisplays[1].GetAt(nLayout)) && m_pDisplays[2].Find(pLayout[0]->GetTitle()) < 0)
		{
			if ((pLayout[1] = new CANDLayout))
			{
				pLayout[1]->Copy(pLayout[0]);
				if (m_pDisplays[2].Add(pLayout[1]) < 0)
				{
					delete pLayout[1];
					continue;
				}
			}
		}
	}
	for (nLayout = 0, nLayouts = (INT)SendDlgItemMessage(IDC_AND_IMPORT_LIST, LB_GETCOUNT); nLayout < nLayouts; nLayout++)
	{
		if (m_pDisplays[0].Find((szLayout = Listbox_GetText(GetDlgItem(IDC_AND_IMPORT_LIST), nLayout))) >= 0) break;
		continue;
	}
	GetDlgItem(IDC_AND_IMPORT_ATTENTION)->ShowWindow((nLayout < nLayouts) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_AND_IMPORT_ATTENTION_TEXT)->ShowWindow((nLayout < nLayouts) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_AND_IMPORT_ATTENTION)->EnableWindow((nLayout < nLayouts) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_IMPORT_ATTENTION_TEXT)->EnableWindow((nLayout < nLayouts) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_IMPORT_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_AND_IMPORT_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_IMPORT_LIST)->EnableWindow((SendDlgItemMessage(IDC_AND_IMPORT_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_IMPORT_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_IMPORT_ADDALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_IMPORT_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_AND_IMPORT_LIST, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_IMPORT_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_AND_IMPORT_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_IMPORT_DIRECTORY)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDImportDialog::OnRemove()
{
	INT  nIndex;
	INT  nLayout;
	INT  nLayouts;
	CString  szLayout;
	CHourglassCursor  cCursor;

	if ((nIndex = m_pDisplays[2].Find(Listbox_GetText(GetDlgItem(IDC_AND_IMPORT_LIST), (INT)SendDlgItemMessage(IDC_AND_IMPORT_LIST, LB_GETCURSEL)))) >= 0)
	{
		delete m_pDisplays[2].GetAt(nIndex);
		m_pDisplays[2].RemoveAt(nIndex);
	}
	if (SendDlgItemMessage(IDC_AND_IMPORT_LIST, LB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_AND_IMPORT_LIST, LB_GETCURSEL)) > 0)
	{
		for (nLayout = 0, nLayouts = (INT)SendDlgItemMessage(IDC_AND_IMPORT_LIST, LB_GETCOUNT); nLayout < nLayouts; nLayout++)
		{
			if (m_pDisplays[0].Find((szLayout = Listbox_GetText(GetDlgItem(IDC_AND_IMPORT_LIST), nLayout))) >= 0) break;
			continue;
		}
		SendDlgItemMessage(IDC_AND_IMPORT_LIST, LB_SETCURSEL);
		GetDlgItem(IDC_AND_IMPORT_DIRECTORY)->GetWindowText(szLayout);
		GetDlgItem(IDC_AND_IMPORT_ATTENTION)->ShowWindow((nLayout < nLayouts) ? SW_SHOW : SW_HIDE);
		GetDlgItem(IDC_AND_IMPORT_ATTENTION_TEXT)->ShowWindow((nLayout < nLayouts) ? SW_SHOW : SW_HIDE);
		GetDlgItem(IDC_AND_IMPORT_ATTENTION)->EnableWindow((nLayout < nLayouts) ? TRUE : FALSE);
		GetDlgItem(IDC_AND_IMPORT_ATTENTION_TEXT)->EnableWindow((nLayout < nLayouts) ? TRUE : FALSE);
		GetDlgItem(IDC_AND_IMPORT_ADD)->EnableWindow((SendDlgItemMessage(IDC_AND_IMPORT_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szLayout) < 0) ? TRUE : FALSE);
		GetDlgItem(IDC_AND_IMPORT_ADDALL)->EnableWindow((SendDlgItemMessage(IDC_AND_IMPORT_DIRECTORY, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	}
	else
	{
		GetDlgItem(IDC_AND_IMPORT_ATTENTION)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_AND_IMPORT_ATTENTION_TEXT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_AND_IMPORT_ATTENTION)->EnableWindow(FALSE);
		GetDlgItem(IDC_AND_IMPORT_ATTENTION_TEXT)->EnableWindow(FALSE);
		GetDlgItem(IDC_AND_IMPORT_LIST_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_AND_IMPORT_LIST)->EnableWindow(FALSE);
		GetDlgItem(IDC_AND_IMPORT_ADD)->EnableWindow((SendDlgItemMessage(IDC_AND_IMPORT_DIRECTORY, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
		GetDlgItem(IDC_AND_IMPORT_ADDALL)->EnableWindow((SendDlgItemMessage(IDC_AND_IMPORT_DIRECTORY, CB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_AND_IMPORT_REMOVE)->EnableWindow(FALSE);
		GetDlgItem(IDC_AND_IMPORT_REMOVEALL)->EnableWindow(FALSE);
	}
	GetDlgItem(IDC_AND_IMPORT_DIRECTORY)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDImportDialog::OnRemoveAll()
{
	CHourglassCursor  cCursor;

	m_pDisplays[2].RemoveAll();
	SendDlgItemMessage(IDC_AND_IMPORT_LIST, LB_RESETCONTENT);
	GetDlgItem(IDC_AND_IMPORT_ATTENTION)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_AND_IMPORT_ATTENTION_TEXT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_AND_IMPORT_ATTENTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_IMPORT_ATTENTION_TEXT)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_IMPORT_LIST_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_IMPORT_LIST)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_IMPORT_ADD)->EnableWindow((SendDlgItemMessage(IDC_AND_IMPORT_DIRECTORY, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_IMPORT_ADDALL)->EnableWindow((SendDlgItemMessage(IDC_AND_IMPORT_DIRECTORY, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_IMPORT_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_IMPORT_REMOVEALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_IMPORT_DIRECTORY)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDImportDialog::OnEditchangeFileName()
{
	CString  szFileName;

	GetDlgItem(IDC_AND_IMPORT_FILENAME)->GetWindowText(szFileName);
	GetDlgItem(IDC_AND_IMPORT_BROWSE)->ShowWindow((szFileName.IsEmpty()) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_AND_IMPORT_INSPECT)->ShowWindow((!szFileName.IsEmpty()) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_AND_IMPORT_BROWSE)->EnableWindow((szFileName.IsEmpty()) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_IMPORT_INSPECT)->EnableWindow((!szFileName.IsEmpty()) ? TRUE : FALSE);
}

void CANDImportDialog::OnSelchangeSource()
{
	CString  szLayout;

	GetDlgItem(IDC_AND_IMPORT_DIRECTORY)->GetWindowText(szLayout);
	GetDlgItem(IDC_AND_IMPORT_ADD)->EnableWindow((SendDlgItemMessage(IDC_AND_IMPORT_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szLayout) < 0) ? TRUE : FALSE);
}

void CANDImportDialog::OnSelchangeDestination()
{
	GetDlgItem(IDC_AND_IMPORT_REMOVE)->EnableWindow();
}

void CANDImportDialog::OnOK()
{
	INT  nLayout;
	INT  nLayouts;
	CString  szMessage;
	CANDLayout  cLayout;
	CHourglassCursor  cCursor;

	for (nLayout = 0, nLayouts = (INT)m_pDisplays[2].GetSize(); nLayout < nLayouts; nLayout++)
	{
		if (!cLayout.Copy(m_pDisplays[2].GetAt(nLayout)) || !AddTemporaryAND(cLayout.GetTitle(), cLayout))
		{
			szMessage.Format(STRING(IDS_AND_IMPORT_FAILURE), (LPCTSTR)cLayout.GetTitle());
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_ERROR, szMessage);
		}
	}
	CLocaleDialog::OnOK();
}

BOOL CANDImportDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_ANDIMPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CANDImportDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_ANDIMPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CANDExportDialog dialog

IMPLEMENT_DYNCREATE(CANDExportDialog, CLocaleDialog)

CANDExportDialog::CANDExportDialog(CWnd *pParentWnd) : CLocaleDialog(CANDExportDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CANDExportDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CANDExportDialog::Initialize()
{
	EnumTemporaryANDs(m_pDisplays[0]);
	return TRUE;
}

BOOL CANDExportDialog::EnumDisplays()
{
	INT  nLayout;
	INT  nLayouts;
	CANDLayout  *pANDLayout;

	for (nLayout = 0, nLayouts = (INT)m_pDisplays[0].GetSize(); nLayout < nLayouts; nLayout++)
	{
		if ((pANDLayout = m_pDisplays[0].GetAt(nLayout))) SendDlgItemMessage(IDC_AND_EXPORT_DIRECTORY, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pANDLayout->GetTitle());
		continue;
	}
	if (SendDlgItemMessage(IDC_AND_EXPORT_DIRECTORY, CB_GETCOUNT) > 0)
	{
		SendDlgItemMessage(IDC_AND_EXPORT_DIRECTORY, CB_SETCURSEL);
		GetDlgItem(IDC_AND_EXPORT_DIRECTORY_STATIC)->EnableWindow();
		GetDlgItem(IDC_AND_EXPORT_DIRECTORY)->EnableWindow();
		return TRUE;
	}
	GetDlgItem(IDC_AND_EXPORT_DIRECTORY_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_EXPORT_DIRECTORY)->EnableWindow(FALSE);
	return FALSE;
}

BOOL CANDExportDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_AND_EXPORT_FILENAME)->GetWindowTextLength() > 0 && m_pDisplays[1].GetSize() > 0) ? TRUE : FALSE);
}

void CANDExportDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CANDExportDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CANDExportDialog::PostNcDestroy()
{
	m_pDisplays[0].RemoveAll();
	m_pDisplays[1].RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CANDExportDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CANDExportDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_AND_EXPORT_ADD, OnAdd)
	ON_BN_CLICKED(IDC_AND_EXPORT_ADDALL, OnAddAll)
	ON_BN_CLICKED(IDC_AND_EXPORT_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_AND_EXPORT_REMOVEALL, OnRemoveAll)
	ON_BN_CLICKED(IDC_AND_EXPORT_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_AND_EXPORT_HELP, OnHelp)
	ON_EN_CHANGE(IDC_AND_EXPORT_FILENAME, OnEditchangeFileName)
	ON_CBN_SELCHANGE(IDC_AND_EXPORT_DIRECTORY, OnSelchangeSource)
	ON_LBN_SELCHANGE(IDC_AND_EXPORT_LIST, OnSelchangeDestination)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDExportDialog message handlers

BOOL CANDExportDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_AND_EXPORT_DETAILS)->EnableWindow();
	GetDlgItem(IDC_AND_EXPORT_ADD)->EnableWindow((EnumDisplays() && SendDlgItemMessage(IDC_AND_EXPORT_DIRECTORY, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_EXPORT_ADDALL)->EnableWindow((SendDlgItemMessage(IDC_AND_EXPORT_DIRECTORY, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_EXPORT_LIST_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_EXPORT_LIST)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_EXPORT_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_EXPORT_REMOVEALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_EXPORT_FILENAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_AND_EXPORT_FILENAME)->EnableWindow();
	GetDlgItem(IDC_AND_EXPORT_BROWSE)->EnableWindow();
	GetDlgItem(IDC_AND_EXPORT_DIRECTORY)->SetFocus();
	return FALSE;
}

void CANDExportDialog::OnAdd()
{
	INT  nLayout;
	INT  nLayouts;
	CString  szLayout;
	CANDLayout  *pLayout[2];
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_AND_EXPORT_DIRECTORY)->GetWindowText(szLayout);
	if (SendDlgItemMessage(IDC_AND_EXPORT_LIST, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szLayout) >= 0)
	{
		if ((pLayout[0] = m_pDisplays[0].GetAt(m_pDisplays[0].Find(szLayout))))
		{
			if ((pLayout[1] = new CANDLayout))
			{
				pLayout[1]->Copy(pLayout[0]);
				if (m_pDisplays[1].Add(pLayout[1]) < 0) delete pLayout[1];
			}
		}
		for (nLayout = 0, nLayouts = (INT)SendDlgItemMessage(IDC_AND_EXPORT_DIRECTORY, CB_GETCOUNT); nLayout < nLayouts; nLayout++)
		{
			if (SendDlgItemMessage(IDC_AND_EXPORT_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)Combobox_GetText(GetDlgItem(IDC_AND_EXPORT_DIRECTORY), nLayout)) < 0) break;
			continue;
		}
		SendDlgItemMessage(IDC_AND_EXPORT_LIST, LB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_AND_EXPORT_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szLayout));
		GetDlgItem(IDC_AND_EXPORT_ADD)->EnableWindow(FALSE);
		GetDlgItem(IDC_AND_EXPORT_ADDALL)->EnableWindow((nLayout < nLayouts) ? TRUE : FALSE);
		GetDlgItem(IDC_AND_EXPORT_LIST_STATIC)->EnableWindow();
		GetDlgItem(IDC_AND_EXPORT_LIST)->EnableWindow();
		GetDlgItem(IDC_AND_EXPORT_REMOVE)->EnableWindow();
		GetDlgItem(IDC_AND_EXPORT_REMOVEALL)->EnableWindow();
		GetDlgItem(IDC_AND_EXPORT_DIRECTORY)->SetFocus();
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDExportDialog::OnAddAll()
{
	INT  nLayout;
	INT  nLayouts;
	CString  szLayout;
	CANDLayout  *pLayout[2];
	CHourglassCursor  cCursor;

	for (nLayout = 0, nLayouts = (INT)SendDlgItemMessage(IDC_AND_EXPORT_DIRECTORY, CB_GETCOUNT); nLayout < nLayouts; nLayout++)
	{
		if (SendDlgItemMessage(IDC_AND_EXPORT_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)(szLayout = Combobox_GetText(GetDlgItem(IDC_AND_EXPORT_DIRECTORY), nLayout))) < 0)
		{
			SendDlgItemMessage(IDC_AND_EXPORT_LIST, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szLayout);
			continue;
		}
	}
	for (nLayout = 0, nLayouts = (INT)m_pDisplays[0].GetSize(); nLayout < nLayouts; nLayout++)
	{
		if ((pLayout[0] = m_pDisplays[0].GetAt(nLayout)) && m_pDisplays[1].Find(pLayout[0]->GetTitle()) < 0)
		{
			if ((pLayout[1] = new CANDLayout))
			{
				pLayout[1]->Copy(pLayout[0]);
				if (m_pDisplays[1].Add(pLayout[1]) < 0)
				{
					delete pLayout[1];
					continue;
				}
			}
		}
	}
	GetDlgItem(IDC_AND_EXPORT_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_AND_EXPORT_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_EXPORT_LIST)->EnableWindow((SendDlgItemMessage(IDC_AND_EXPORT_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_EXPORT_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_EXPORT_ADDALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_EXPORT_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_AND_EXPORT_LIST, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_EXPORT_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_AND_EXPORT_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_EXPORT_DIRECTORY)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDExportDialog::OnRemove()
{
	INT  nIndex;
	CString  szLayout;
	CHourglassCursor  cCursor;

	if ((nIndex = m_pDisplays[1].Find(Listbox_GetText(GetDlgItem(IDC_AND_EXPORT_LIST), (INT)SendDlgItemMessage(IDC_AND_EXPORT_LIST, LB_GETCURSEL)))) >= 0)
	{
		delete m_pDisplays[1].GetAt(nIndex);
		m_pDisplays[1].RemoveAt(nIndex);
	}
	if (SendDlgItemMessage(IDC_AND_EXPORT_LIST, LB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_AND_EXPORT_LIST, LB_GETCURSEL)) > 0)
	{
		SendDlgItemMessage(IDC_AND_EXPORT_LIST, LB_SETCURSEL);
		GetDlgItem(IDC_AND_EXPORT_DIRECTORY)->GetWindowText(szLayout);
		GetDlgItem(IDC_AND_EXPORT_ADD)->EnableWindow((SendDlgItemMessage(IDC_AND_EXPORT_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szLayout) < 0) ? TRUE : FALSE);
		GetDlgItem(IDC_AND_EXPORT_ADDALL)->EnableWindow((SendDlgItemMessage(IDC_AND_EXPORT_DIRECTORY, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	}
	else
	{
		GetDlgItem(IDC_AND_EXPORT_LIST_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_AND_EXPORT_LIST)->EnableWindow(FALSE);
		GetDlgItem(IDC_AND_EXPORT_ADD)->EnableWindow((SendDlgItemMessage(IDC_AND_EXPORT_DIRECTORY, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
		GetDlgItem(IDC_AND_EXPORT_ADDALL)->EnableWindow((SendDlgItemMessage(IDC_AND_EXPORT_DIRECTORY, CB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_AND_EXPORT_REMOVE)->EnableWindow(FALSE);
		GetDlgItem(IDC_AND_EXPORT_REMOVEALL)->EnableWindow(FALSE);
	}
	GetDlgItem(IDC_AND_EXPORT_DIRECTORY)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDExportDialog::OnRemoveAll()
{
	CHourglassCursor  cCursor;

	m_pDisplays[1].RemoveAll();
	SendDlgItemMessage(IDC_AND_EXPORT_LIST, LB_RESETCONTENT);
	GetDlgItem(IDC_AND_EXPORT_LIST_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_EXPORT_LIST)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_EXPORT_ADD)->EnableWindow((SendDlgItemMessage(IDC_AND_EXPORT_DIRECTORY, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_EXPORT_ADDALL)->EnableWindow((SendDlgItemMessage(IDC_AND_EXPORT_DIRECTORY, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_EXPORT_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_EXPORT_REMOVEALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_EXPORT_DIRECTORY)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDExportDialog::OnBrowse()
{
	CString  szFileName;
	CFileBrowseDialog  cFileBrowseDialog(this, IDC_AND_EXPORT_FILENAME, STRING(IDS_FILEBROWSEDIALOG_DATABASEFILEEXTENSION), STRING(IDS_FILEBROWSEDIALOG_DATABASEFILEFILTER));

	if (cFileBrowseDialog.DoModal() == IDOK)
	{
		szFileName = cFileBrowseDialog.GetPathName();
		GetDlgItem(IDC_AND_EXPORT_FILENAME)->SetWindowText(szFileName);
	}
	SendDlgItemMessage(IDC_AND_EXPORT_FILENAME, EM_SETSEL, 0, (LPARAM)-1);
	GetDlgItem(IDC_AND_EXPORT_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDExportDialog::OnEditchangeFileName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDExportDialog::OnSelchangeSource()
{
	CString  szLayout;

	GetDlgItem(IDC_AND_EXPORT_DIRECTORY)->GetWindowText(szLayout);
	GetDlgItem(IDC_AND_EXPORT_ADD)->EnableWindow((SendDlgItemMessage(IDC_AND_EXPORT_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szLayout) < 0) ? TRUE : FALSE);
}

void CANDExportDialog::OnSelchangeDestination()
{
	GetDlgItem(IDC_AND_EXPORT_REMOVE)->EnableWindow();
}

void CANDExportDialog::OnOK()
{
	DWORD  cbData;
	CFileEx  cFile;
	CString  szFileName;
	CByteArray  nFileData;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_AND_EXPORT_FILENAME)->GetWindowText(szFileName);
	if (cFile.Open(szFileName, CFile::modeCreate | CFile::modeReadWrite | CFile::shareExclusive))
	{
		ReportEvent((!WriteFile(cFile.m_hFile, nFileData.GetData(), (m_pDisplays[1].Map(nFileData)) ? (DWORD)nFileData.GetSize() : 0, &cbData, (LPOVERLAPPED)NULL) || !cbData) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_ERROR) : 0, STRING(IDS_AND_EXPORT_FILE_FAILURE));
		cFile.Close();
	}
	else  ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_ERROR, STRING(IDS_AND_EXPORT_FILE_FAILURE));
	CLocaleDialog::OnOK();
}

BOOL CANDExportDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_ANDEXPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CANDExportDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_ANDEXPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CANDFindDialog dialog

IMPLEMENT_DYNCREATE(CANDFindDialog, CDisplayDialog)

CANDFindDialog::CANDFindDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CANDFindDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CANDFindDialog::Create(CWnd *pParentWnd, INT nType, CANDLayout &cLayout)
{
	switch ((m_nType = nType))
	{
	case AND_TYPE_NORMAL:
	{ GetDatabase()->EnumANDs(m_pLayouts[0], DATABASE_SUBCOMPONENT_AND_NORMAL, FALSE);
	break;
	}
	case AND_TYPE_GENERIC:
	{ GetDatabase()->EnumANDs(m_pLayouts[0], DATABASE_SUBCOMPONENT_AND_GENERIC, FALSE);
	break;
	}
	case AND_TYPE_TEMPORARY:
	{ EnumTemporaryANDs(m_pLayouts[0]);
	break;
	}
	}
	if (CDisplayDialog::Create(pParentWnd, CANDFindDialog::IDD) == IDOK  &&  m_pLayouts[1].GetSize() == 1)
	{
		cLayout.Copy(m_pLayouts[1].GetAt((INT)m_pLayouts[1].GetUpperBound()));
		m_pLayouts[0].RemoveAll();
		m_pLayouts[1].RemoveAll();
		return IDOK;
	}
	m_pLayouts[0].RemoveAll();
	m_pLayouts[1].RemoveAll();
	return IDCANCEL;
}

CANDWnd *CANDFindDialog::GetParent() CONST
{
	return((CANDWnd *)CDisplayDialog::GetParent());
}

BOOL CANDFindDialog::EnumSearchKeys()
{
	SendDlgItemMessage(IDC_AND_FIND_KEY, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_ANDFINDDIALOG_KEY_PARAMETER));
	SendDlgItemMessage(IDC_AND_FIND_KEY, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_ANDFINDDIALOG_KEY_DESCRIPTION));
	return((SendDlgItemMessage(IDC_AND_FIND_KEY, CB_SETCURSEL) >= 0) ? TRUE : FALSE);
}

BOOL CANDFindDialog::EnumSearchValues()
{
	INT  nItem;
	INT  nItems;
	CString  szKey;
	CString  szValue;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	GetDlgItem(IDC_AND_FIND_KEY)->GetWindowText(szKey);
	if (szKey == STRING(IDS_ANDFINDDIALOG_KEY_PARAMETER))
	{
		for (nItem = 0, nItems = (INT)GetDatabase()->GetTMParameters()->GetSize(), SendDlgItemMessage(IDC_AND_FIND_VALUE, CB_RESETCONTENT); nItem < nItems; nItem++)
		{
			if ((pDatabaseTMParameter = (CDatabaseTMParameter *)GetDatabase()->GetTMParameters()->GetAt(nItem)) != (CDatabaseTMParameter *)NULL)
			{
				szValue.Format(STRING(IDS_ANDFINDDIALOG_VALUE_FORMAT), (LPCTSTR)pDatabaseTMParameter->GetTag(), (LPCTSTR)pDatabaseTMParameter->GetDescription());
				SendDlgItemMessage(IDC_AND_FIND_VALUE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szValue);
			}
		}
	}
	if (szKey == STRING(IDS_ANDFINDDIALOG_KEY_DESCRIPTION))
	{
		for (nItem = 0, nItems = (INT)m_szDescriptions.GetSize(), SendDlgItemMessage(IDC_AND_FIND_VALUE, CB_RESETCONTENT); nItem < nItems; nItem++)
		{
			SendDlgItemMessage(IDC_AND_FIND_VALUE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)m_szDescriptions.GetAt(nItem));
			continue;
		}
	}
	return((SendDlgItemMessage(IDC_AND_FIND_VALUE, CB_GETCOUNT) >= 0) ? TRUE : FALSE);
}

VOID CANDFindDialog::DoFindByParameter(LPCTSTR pszParameter)
{
	INT  nLayout;
	INT  nLayouts;
	CString  szResult[2];
	CANDLayout  *pLayout;

	SendDlgItemMessage(IDC_AND_FIND_RESULTS, LB_RESETCONTENT);
	for (nLayout = 0, nLayouts = (m_pLayouts[1].Copy(&m_pLayouts[0])) ? (INT)m_pLayouts[1].GetSize() : 0; nLayout < nLayouts; nLayout++)
	{
		if ((pLayout = m_pLayouts[1].GetAt(nLayout)))
		{
			if (pLayout->Find(pszParameter) >= 0)
			{
				if (pLayout->GetTitle().IsEmpty())
				{
					SendDlgItemMessage(IDC_AND_FIND_RESULTS, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)pLayout->GetName());
					continue;
				}
				szResult[0].Format(STRING(IDS_ANDFINDDIALOG_RESULT_FORMAT), (LPCTSTR)pLayout->GetName(), (LPCTSTR)pLayout->GetTitle());
				szResult[1].Format(STRING(IDS_ANDFINDDIALOG_RESULT_SPECIALFORMAT), (LPCTSTR)pLayout->GetTitle(), (LPCTSTR)pLayout->GetName());
				SendDlgItemMessage(IDC_AND_FIND_RESULTS, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)((m_nType == AND_TYPE_NORMAL) ? (LPCTSTR)szResult[0] : ((m_nType == AND_TYPE_GENERIC) ? (LPCTSTR)szResult[1] : (LPCTSTR)pLayout->GetTitle())));
			}
		}
	}
	GetDlgItem(IDC_AND_FIND_RESULTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_AND_FIND_RESULTS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_FIND_RESULTS)->EnableWindow((SendDlgItemMessage(IDC_AND_FIND_RESULTS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CANDFindDialog::DoFindByParameters(CONST CStringArray &szParameters)
{
	INT  nLayout;
	INT  nLayouts;
	INT  nParameter;
	INT  nParameters;
	CString  szResult[2];
	CANDLayout  *pLayout[2];

	for (nParameter = 0, nParameters = (m_pLayouts[1].Copy(&m_pLayouts[0])) ? (INT)szParameters.GetSize() : 0; nParameter < nParameters; nParameter += 2)
	{
		for (nLayout = 0, nLayouts = (!nParameter || szParameters.GetAt(nParameter - 1) == STRING(IDS_ANDFINDDIALOG_QUERY_AND)) ? (INT)m_pLayouts[1].GetSize() : -1; nLayout < nLayouts; nLayout++)
		{
			if ((pLayout[0] = m_pLayouts[1].GetAt(nLayout)) && pLayout[0]->Find(szParameters.GetAt(nParameter)) < 0)
			{
				m_pLayouts[1].RemoveAt(nLayout);
				delete pLayout[0];
				nLayouts--;
				nLayout--;
			}
		}
		for (nLayout = 0, nLayouts = (nParameter > 0 && szParameters.GetAt(nParameter - 1) == STRING(IDS_ANDFINDDIALOG_QUERY_OR)) ? (INT)m_pLayouts[0].GetSize() : -1; nLayout < nLayouts; nLayout++)
		{
			if ((pLayout[0] = m_pLayouts[0].GetAt(nLayout)) && pLayout[0]->Find(szParameters.GetAt(nParameter)) >= 0)
			{
				if ((pLayout[1] = (m_pLayouts[1].Find(pLayout[0]->GetName()) < 0) ? new CANDLayout : (CANDLayout *)NULL))
				{
					if (!pLayout[1]->Copy(pLayout[0]) || m_pLayouts[1].Add(pLayout[1]) < 0)
					{
						delete pLayout[1];
						continue;
					}
				}
			}
		}
	}
	for (SendDlgItemMessage(IDC_AND_FIND_RESULTS, LB_RESETCONTENT); !nParameters; )
	{
		m_pLayouts[1].RemoveAll();
		break;
	}
	for (nLayout = 0, nLayouts = (INT)m_pLayouts[1].GetSize(); nLayout < nLayouts; nLayout++)
	{
		if ((pLayout[0] = m_pLayouts[1].GetAt(nLayout)))
		{
			if (pLayout[0]->GetTitle().IsEmpty())
			{
				SendDlgItemMessage(IDC_AND_FIND_RESULTS, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)pLayout[0]->GetName());
				continue;
			}
			szResult[0].Format(STRING(IDS_ANDFINDDIALOG_RESULT_FORMAT), (LPCTSTR)pLayout[0]->GetName(), (LPCTSTR)pLayout[0]->GetTitle());
			szResult[1].Format(STRING(IDS_ANDFINDDIALOG_RESULT_SPECIALFORMAT), (LPCTSTR)pLayout[0]->GetTitle(), (LPCTSTR)pLayout[0]->GetName());
			SendDlgItemMessage(IDC_AND_FIND_RESULTS, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)((m_nType == AND_TYPE_NORMAL) ? (LPCTSTR)szResult[0] : ((m_nType == AND_TYPE_GENERIC) ? (LPCTSTR)szResult[1] : (LPCTSTR)pLayout[0]->GetTitle())));
		}
	}
	GetDlgItem(IDC_AND_FIND_RESULTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_AND_FIND_RESULTS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_FIND_RESULTS)->EnableWindow((SendDlgItemMessage(IDC_AND_FIND_RESULTS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CANDFindDialog::DoFindByDescription(LPCTSTR pszDescription)
{
	INT  nLayout;
	INT  nLayouts;
	CString  szResult[2];
	CANDLayout  *pLayout;

	SendDlgItemMessage(IDC_AND_FIND_RESULTS, LB_RESETCONTENT);
	for (nLayout = 0, nLayouts = (m_pLayouts[1].Copy(&m_pLayouts[0])) ? (INT)m_pLayouts[1].GetSize() : 0; nLayout < nLayouts; nLayout++)
	{
		if ((pLayout = m_pLayouts[1].GetAt(nLayout)) && pLayout->GetTitle().Find(pszDescription) >= 0)
		{
			szResult[0].Format(STRING(IDS_ANDFINDDIALOG_RESULT_FORMAT), (LPCTSTR)pLayout->GetName(), (LPCTSTR)pLayout->GetTitle());
			szResult[1].Format(STRING(IDS_ANDFINDDIALOG_RESULT_SPECIALFORMAT), (LPCTSTR)pLayout->GetTitle(), (LPCTSTR)pLayout->GetName());
			SendDlgItemMessage(IDC_AND_FIND_RESULTS, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)((m_nType == AND_TYPE_NORMAL) ? (LPCTSTR)szResult[0] : ((m_nType == AND_TYPE_GENERIC) ? (LPCTSTR)szResult[1] : (LPCTSTR)pLayout->GetTitle())));
		}
	}
	GetDlgItem(IDC_AND_FIND_RESULTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_AND_FIND_RESULTS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_FIND_RESULTS)->EnableWindow((SendDlgItemMessage(IDC_AND_FIND_RESULTS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CANDFindDialog::DoFindByDescriptions(CONST CStringArray &szDescriptions)
{
	INT  nLayout;
	INT  nLayouts;
	INT  nDescription;
	INT  nDescriptions;
	CString  szResult[2];
	CANDLayout  *pLayout[2];

	for (nDescription = 0, nDescriptions = (m_pLayouts[1].Copy(&m_pLayouts[0])) ? (INT)szDescriptions.GetSize() : 0; nDescription < nDescriptions; nDescription += 2)
	{
		for (nLayout = 0, nLayouts = (!nDescription || szDescriptions.GetAt(nDescription - 1) == STRING(IDS_ANDFINDDIALOG_QUERY_AND)) ? (INT)m_pLayouts[1].GetSize() : -1; nLayout < nLayouts; nLayout++)
		{
			if ((pLayout[0] = m_pLayouts[1].GetAt(nLayout)) && pLayout[0]->GetTitle().Find(szDescriptions.GetAt(nDescription)) < 0)
			{
				m_pLayouts[1].RemoveAt(nLayout);
				delete pLayout[0];
				nLayouts--;
				nLayout--;
			}
		}
		for (nLayout = 0, nLayouts = (nDescription > 0 && szDescriptions.GetAt(nDescription - 1) == STRING(IDS_ANDFINDDIALOG_QUERY_OR)) ? (INT)m_pLayouts[0].GetSize() : -1; nLayout < nLayouts; nLayout++)
		{
			if ((pLayout[0] = m_pLayouts[0].GetAt(nLayout)) && pLayout[0]->GetTitle().Find(szDescriptions.GetAt(nDescription)) >= 0)
			{
				if ((pLayout[1] = (m_pLayouts[1].Find(pLayout[0]->GetName()) < 0) ? new CANDLayout : (CANDLayout *)NULL))
				{
					if (!pLayout[1]->Copy(pLayout[0]) || m_pLayouts[1].Add(pLayout[1]) < 0)
					{
						delete pLayout[1];
						continue;
					}
				}
			}
		}
	}
	for (SendDlgItemMessage(IDC_AND_FIND_RESULTS, LB_RESETCONTENT); !nDescriptions; )
	{
		m_pLayouts[1].RemoveAll();
		break;
	}
	for (nLayout = 0, nLayouts = (INT)m_pLayouts[1].GetSize(); nLayout < nLayouts; nLayout++)
	{
		if ((pLayout[0] = m_pLayouts[1].GetAt(nLayout)) != (CANDLayout *)NULL)
		{
			szResult[0].Format(STRING(IDS_ANDFINDDIALOG_RESULT_FORMAT), (LPCTSTR)pLayout[0]->GetName(), (LPCTSTR)pLayout[0]->GetTitle());
			szResult[1].Format(STRING(IDS_ANDFINDDIALOG_RESULT_SPECIALFORMAT), (LPCTSTR)pLayout[0]->GetTitle(), (LPCTSTR)pLayout[0]->GetName());
			SendDlgItemMessage(IDC_AND_FIND_RESULTS, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)((m_nType == AND_TYPE_NORMAL) ? (LPCTSTR)szResult[0] : ((m_nType == AND_TYPE_GENERIC) ? (LPCTSTR)szResult[1] : (LPCTSTR)pLayout[0]->GetTitle())));
		}
	}
	GetDlgItem(IDC_AND_FIND_RESULTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_AND_FIND_RESULTS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_FIND_RESULTS)->EnableWindow((SendDlgItemMessage(IDC_AND_FIND_RESULTS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
}

void CANDFindDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CANDFindDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CANDFindDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CANDFindDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_AND_FIND_SEARCH, OnSearch)
	ON_BN_CLICKED(IDC_AND_FIND_OPEN, OnOpen)
	ON_BN_CLICKED(IDC_AND_FIND_HELP, OnHelp)
	ON_CBN_EDITCHANGE(IDC_AND_FIND_VALUE, OnEditchangeValue)
	ON_CBN_SELCHANGE(IDC_AND_FIND_KEY, OnSelchangeKey)
	ON_CBN_SELCHANGE(IDC_AND_FIND_VALUE, OnSelchangeValue)
	ON_LBN_DBLCLK(IDC_AND_FIND_RESULTS, OnOpen)
	ON_LBN_SELCHANGE(IDC_AND_FIND_RESULTS, OnSelchangeResult)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDFindDialog message handlers

BOOL CANDFindDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	if (EnumSearchKeys() && EnumSearchValues())
	{
		GetDlgItem(IDC_AND_FIND_KEY_STATIC)->EnableWindow();
		GetDlgItem(IDC_AND_FIND_KEY)->EnableWindow();
		GetDlgItem(IDC_AND_FIND_VALUE_STATIC)->EnableWindow();
		GetDlgItem(IDC_AND_FIND_VALUE)->EnableWindow();
	}
	return TRUE;
}

void CANDFindDialog::OnSearch()
{
	INT  nPos;
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	CString  szKey;
	CString  szValue;
	CString  szParameter;
	CString  szDescription;
	CStringArray  szParameters;
	CStringArray  szDescriptions;
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_AND_FIND_KEY)->GetWindowText(szKey);
	GetDlgItem(IDC_AND_FIND_VALUE)->GetWindowText(szValue);
	if (szKey == STRING(IDS_ANDFINDDIALOG_KEY_PARAMETER))
	{
		if ((nIndex = (INT)SendDlgItemMessage(IDC_AND_FIND_VALUE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szValue)) >= 0)
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
			if (szValue.GetAt(nPos) != STRINGCHAR(IDS_ANDFINDDIALOG_QUERY_QUOTE))
			{
				nPos = -1;
				break;
			}
			for (nPos = nPos + 1; nPos < szValue.GetLength(); nPos++)
			{
				if (!_istspace(szValue.GetAt(nPos)) && szValue.GetAt(nPos) != STRINGCHAR(IDS_ANDFINDDIALOG_QUERY_QUOTE))
				{
					szParameter += szValue.GetAt(nPos);
					continue;
				}
				break;
			}
			if (szValue.GetAt(nPos) != STRINGCHAR(IDS_ANDFINDDIALOG_QUERY_QUOTE))
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
				if (szValue.GetAt(nPos) == STRINGCHAR(IDS_ANDFINDDIALOG_QUERY_AND) || szValue.GetAt(nPos) == STRINGCHAR(IDS_ANDFINDDIALOG_QUERY_OR))
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
		GetDlgItem(IDC_AND_FIND_VALUE)->SetFocus();
		CAudioDevice::AlertBySound();
		return;
	}
	if (szKey == STRING(IDS_ANDFINDDIALOG_KEY_DESCRIPTION))
	{
		for (nItem = 0, nItems = (INT)m_szDescriptions.GetSize(); nItem < nItems; nItem++)
		{
			if (m_szDescriptions.GetAt(nItem) == szValue) break;
			continue;
		}
		for (; nItem == nItems; )
		{
			SendDlgItemMessage(IDC_AND_FIND_VALUE, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szValue);
			m_szDescriptions.Add(szValue);
			break;
		}
		if ((nPos = szValue.Find(STRING(IDS_ANDFINDDIALOG_QUERY_QUOTE))) < 0)
		{
			DoFindByDescription(szValue);
			return;
		}
		for (nPos = 0; nPos < szValue.GetLength(); nPos++)
		{
			for (szDescription.Empty(); nPos < szValue.GetLength(); nPos++)
			{
				if (!_istspace(szValue.GetAt(nPos))) break;
				continue;
			}
			if (szValue.GetAt(nPos) != STRINGCHAR(IDS_ANDFINDDIALOG_QUERY_QUOTE))
			{
				nPos = -1;
				break;
			}
			for (nPos = nPos + 1; nPos < szValue.GetLength(); nPos++)
			{
				if (!_istspace(szValue.GetAt(nPos)) && szValue.GetAt(nPos) != STRINGCHAR(IDS_ANDFINDDIALOG_QUERY_QUOTE))
				{
					szDescription += szValue.GetAt(nPos);
					continue;
				}
				break;
			}
			if (szValue.GetAt(nPos) != STRINGCHAR(IDS_ANDFINDDIALOG_QUERY_QUOTE))
			{
				nPos = -1;
				break;
			}
			for (nPos = nPos + 1, szDescriptions.Add(szDescription); nPos < szValue.GetLength(); nPos++)
			{
				if (!_istspace(szValue.GetAt(nPos))) break;
				continue;
			}
			if (szValue.GetAt(nPos) == STRINGCHAR(IDS_ANDFINDDIALOG_QUERY_AND) || szValue.GetAt(nPos) == STRINGCHAR(IDS_ANDFINDDIALOG_QUERY_OR))
			{
				szDescriptions.Add(szValue.GetAt(nPos));
				continue;
			}
			break;
		}
		if (nPos >= szValue.GetLength())
		{
			if (szDescriptions.GetSize() > 0)
			{
				DoFindByDescriptions(szDescriptions);
				return;
			}
		}
		GetDlgItem(IDC_AND_FIND_VALUE)->SetFocus();
		CAudioDevice::AlertBySound();
		return;
	}
}

void CANDFindDialog::OnOpen()
{
	INT  nLayout[2];
	INT  nLayouts[2];
	CString  szTitle[3];
	CANDLayout  *pLayout;
	CHourglassCursor  cCursor;

	for (nLayout[0] = 0, nLayouts[0] = (INT)m_pLayouts[1].GetSize(), szTitle[0] = Listbox_GetText(GetDlgItem(IDC_AND_FIND_RESULTS), (INT)SendDlgItemMessage(IDC_AND_FIND_RESULTS, LB_GETCURSEL)); nLayout[0] < nLayouts[0]; nLayout[0]++)
	{
		if ((pLayout = m_pLayouts[1].GetAt(nLayout[0])))
		{
			if (pLayout->GetTitle().IsEmpty())
			{
				szTitle[1] = pLayout->GetName();
				szTitle[2] = pLayout->GetName();
			}
			else
			{
				szTitle[1].Format(STRING(IDS_ANDFINDDIALOG_RESULT_FORMAT), (LPCTSTR)pLayout->GetName(), (LPCTSTR)pLayout->GetTitle());
				szTitle[2].Format(STRING(IDS_ANDFINDDIALOG_RESULT_SPECIALFORMAT), (LPCTSTR)pLayout->GetTitle(), (LPCTSTR)pLayout->GetName());
			}
			if ((m_nType == AND_TYPE_NORMAL  &&  szTitle[0] == szTitle[1]) || (m_nType == AND_TYPE_GENERIC  &&  szTitle[0] == szTitle[2]) || (m_nType == AND_TYPE_TEMPORARY  &&  szTitle[0] == pLayout->GetTitle())) break;
		}
	}
	for (nLayout[1] = 0, nLayouts[1] = (nLayout[0] < nLayouts[0]) ? nLayout[0] : nLayouts[0]; nLayout[1] < nLayouts[1]; nLayout[1]++)
	{
		if ((pLayout = m_pLayouts[1].GetAt(0))) delete pLayout;
		m_pLayouts[1].RemoveAt(0);
	}
	for (nLayout[1] = 1, nLayouts[1] = (nLayout[0] < nLayouts[0]) ? (INT)m_pLayouts[1].GetSize() : 0; nLayout[1] < nLayouts[1]; nLayout[1]++)
	{
		if ((pLayout = m_pLayouts[1].GetAt(1))) delete pLayout;
		m_pLayouts[1].RemoveAt(1);
	}
	EndDialog(IDOK);
}

void CANDFindDialog::OnSelchangeKey()
{
	EnumSearchValues();
	GetDlgItem(IDC_AND_FIND_SEARCH)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_FIND_VALUE)->SetFocus();
}

void CANDFindDialog::OnSelchangeValue()
{
	GetDlgItem(IDC_AND_FIND_SEARCH)->EnableWindow((SendDlgItemMessage(IDC_AND_FIND_VALUE, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
}

void CANDFindDialog::OnSelchangeResult()
{
	GetDlgItem(IDC_AND_FIND_OPEN)->EnableWindow();
}

void CANDFindDialog::OnEditchangeValue()
{
	GetDlgItem(IDC_AND_FIND_SEARCH)->EnableWindow((GetDlgItem(IDC_AND_FIND_VALUE)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

void CANDFindDialog::OnOK()
{
	CHourglassCursor  cCursor;

	m_pLayouts[1].RemoveAll();
	CDisplayDialog::OnOK();
}

BOOL CANDFindDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_ANDFINDDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CANDFindDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_ANDFINDDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CANDOpenDialog dialog

IMPLEMENT_DYNCREATE(CANDOpenDialog, CDisplayDialog)

CANDOpenDialog::CANDOpenDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CANDOpenDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CANDOpenDialog::Create(CWnd *pParentWnd)
{
	return CDisplayDialog::Create(pParentWnd, CANDOpenDialog::IDD);
}

BOOL CANDOpenDialog::Initialize()
{
	m_nRetrieveMode = 0;
	m_nRetrieveSpeed = 0;
	m_tRetrieveStartTime = 0;
	m_tRetrieveStopTime = 0;
	m_tRetrieveInterval = 0;
	m_bLayoutBadData = FALSE;
	m_bLayoutToolTips = FALSE;
	m_bLayoutInvalidData = FALSE;
	ZeroMemory(&m_fntLayoutTitle, sizeof(LOGFONT));
	ZeroMemory(&m_fntLayoutLabels, sizeof(LOGFONT));
	ZeroMemory(&m_fntLayoutItems, sizeof(LOGFONT));
	ZeroMemory(&m_fntLayoutValues, sizeof(LOGFONT));
	return TRUE;
}

CString CANDOpenDialog::GetTitle() CONST
{
	CString  szTitle;
	CANDLayout  cANDLayout;

	if (FindLayout(cANDLayout) || (GetType() == AND_TYPE_TEMPORARY  &&  GetLayout(cANDLayout)))
	{
		szTitle.Format(STRING(IDS_WINDOW_FULLTITLE), STRING(IDS_DISPLAY_TITLE_AND), (!cANDLayout.GetTitle().IsEmpty()) ? (LPCTSTR)cANDLayout.GetTitle() : (LPCTSTR)cANDLayout.GetName());
		return szTitle;
	}
	return STRING(IDS_DISPLAY_TITLE_AND);
}

UINT CANDOpenDialog::GetType() CONST
{
	return((IsDlgButtonChecked(IDC_AND_OPEN_TYPE_NORMAL) || IsDlgButtonChecked(IDC_AND_OPEN_TYPE_GENERIC) || IsDlgButtonChecked(IDC_AND_OPEN_TYPE_TEMPORARY)) ? ((IsDlgButtonChecked(IDC_AND_OPEN_TYPE_NORMAL) || IsDlgButtonChecked(IDC_AND_OPEN_TYPE_GENERIC)) ? ((IsDlgButtonChecked(IDC_AND_OPEN_TYPE_NORMAL)) ? AND_TYPE_NORMAL : AND_TYPE_GENERIC) : AND_TYPE_TEMPORARY) : -1);
}

UINT CANDOpenDialog::GetMode() CONST
{
	return((IsDlgButtonChecked(IDC_AND_OPEN_MODE_REALTIME) || IsDlgButtonChecked(IDC_AND_OPEN_MODE_HISTORY)) ? (IsDlgButtonChecked(IDC_AND_OPEN_MODE_REALTIME)*DISPLAY_MODE_REALTIME + IsDlgButtonChecked(IDC_AND_OPEN_MODE_HISTORY)*DISPLAY_MODE_HISTORY) : -1);
}

BOOL CANDOpenDialog::GetLayout(CANDLayout &cLayout) CONST
{
	CString  szTitle;

	if (GetType() == AND_TYPE_TEMPORARY  &&  !FindLayout(cLayout))
	{
		GetDlgItem(IDC_AND_OPEN_DISPLAY)->GetWindowText(szTitle);
		cLayout.SetTitle(szTitle);
		cLayout.SetName(szTitle);
		return InitializeLayout(cLayout);
	}
	return((FindLayout(cLayout)) ? InitializeLayout(cLayout) : FALSE);
}
BOOL CANDOpenDialog::GetLayout(CANDLayout &cLayout, CUIntArray &nColumns) CONST
{
	INT  nIndex;
	INT  nCount;
	INT  nColumn;
	INT  nParameter;
	INT  nParameters;
	INT  nColumnGroup;
	CUIntArray  nColumnItems[2];
	CANDLayoutParameter  *pParameter;

	if (GetLayout(cLayout))
	{
		if (m_cLayout.GetName() == cLayout.GetName())
		{
			if (m_nLayoutColumns.GetSize() > 0)
			{
				nColumns.Copy(m_nLayoutColumns);
				return TRUE;
			}
		}
		for (nParameter = 0, nParameters = (INT)cLayout.GetSize(), nColumnGroup = 1; nParameter < nParameters; nParameter++)
		{
			if ((pParameter = cLayout.GetAt(nParameter)) != (CANDLayoutParameter *)NULL)
			{
				nColumnGroup = max(max(pParameter->GetColumn(), 0) + 1, nColumnGroup);
				continue;
			}
		}
		for (nIndex = 0, nCount = cLayout.GetColumns(nColumnItems[0]); nIndex < nCount; nIndex++)
		{
			if ((nColumn = nColumnItems[0].GetAt(nIndex)) == (UINT)-1) nColumn = AND_TITLEITEMS_DEFAULT;
			if (nColumn & AND_TITLEITEM_ID) nColumnItems[1].Add(AND_TITLEITEM_ID);
			if (nColumn & AND_TITLEITEM_DESCRIPTION) nColumnItems[1].Add(AND_TITLEITEM_DESCRIPTION);
			if (nColumn & AND_TITLEITEM_VALUE) nColumnItems[1].Add(AND_TITLEITEM_VALUE);
			if (nColumn & AND_TITLEITEM_UNIT) nColumnItems[1].Add(AND_TITLEITEM_UNIT);
			if (nColumn & AND_TITLEITEM_CHANGETMUNIT) nColumnItems[1].Add(AND_TITLEITEM_CHANGETMUNIT);
			if (nColumn & AND_TITLEITEM_CHANGETIME) nColumnItems[1].Add(AND_TITLEITEM_CHANGETIME);
			if (nColumn & AND_TITLEITEM_UPDATETMUNIT) nColumnItems[1].Add(AND_TITLEITEM_UPDATETMUNIT);
			if (nColumn & AND_TITLEITEM_UPDATETIME) nColumnItems[1].Add(AND_TITLEITEM_UPDATETIME);
			if (nColumn & AND_TITLEITEM_EXPECTEDVALUES) nColumnItems[1].Add(AND_TITLEITEM_EXPECTEDVALUES);
		}
		for (; nIndex < nColumnGroup; nIndex++)
		{
			if (AND_TITLEITEMS_DEFAULT & AND_TITLEITEM_ID) nColumnItems[1].Add(AND_TITLEITEM_ID);
			if (AND_TITLEITEMS_DEFAULT & AND_TITLEITEM_DESCRIPTION) nColumnItems[1].Add(AND_TITLEITEM_DESCRIPTION);
			if (AND_TITLEITEMS_DEFAULT & AND_TITLEITEM_VALUE) nColumnItems[1].Add(AND_TITLEITEM_VALUE);
			if (AND_TITLEITEMS_DEFAULT & AND_TITLEITEM_UNIT) nColumnItems[1].Add(AND_TITLEITEM_UNIT);
			if (AND_TITLEITEMS_DEFAULT & AND_TITLEITEM_CHANGETMUNIT) nColumnItems[1].Add(AND_TITLEITEM_CHANGETMUNIT);
			if (AND_TITLEITEMS_DEFAULT & AND_TITLEITEM_CHANGETIME) nColumnItems[1].Add(AND_TITLEITEM_CHANGETIME);
			if (AND_TITLEITEMS_DEFAULT & AND_TITLEITEM_UPDATETMUNIT) nColumnItems[1].Add(AND_TITLEITEM_UPDATETMUNIT);
			if (AND_TITLEITEMS_DEFAULT & AND_TITLEITEM_UPDATETIME) nColumnItems[1].Add(AND_TITLEITEM_UPDATETIME);
			if (AND_TITLEITEMS_DEFAULT & AND_TITLEITEM_EXPECTEDVALUES) nColumnItems[1].Add(AND_TITLEITEM_EXPECTEDVALUES);
		}
		nColumns.Copy(nColumnItems[1]);
		return TRUE;
	}
	return FALSE;
}

BOOL CANDOpenDialog::GetLayoutColors(CUIntArray &nColors) CONST
{
	if (IsLayoutModified())
	{
		nColors.Copy(m_nLayoutColors);
		return TRUE;
	}
	return FALSE;
}

BOOL CANDOpenDialog::GetLayoutTitleFont(LPLOGFONT pTitleFont) CONST
{
	if (IsLayoutModified())
	{
		CopyMemory(pTitleFont, &m_fntLayoutTitle, sizeof(LOGFONT));
		return TRUE;
	}
	return FALSE;
}

BOOL CANDOpenDialog::GetLayoutLabelsFont(LPLOGFONT pLabelsFont) CONST
{
	if (IsLayoutModified())
	{
		CopyMemory(pLabelsFont, &m_fntLayoutLabels, sizeof(LOGFONT));
		return TRUE;
	}
	return FALSE;
}

BOOL CANDOpenDialog::GetLayoutItemsFont(LPLOGFONT pItemsFont) CONST
{
	if (IsLayoutModified())
	{
		CopyMemory(pItemsFont, &m_fntLayoutItems, sizeof(LOGFONT));
		return TRUE;
	}
	return FALSE;
}

BOOL CANDOpenDialog::GetLayoutValuesFont(LPLOGFONT pValuesFont) CONST
{
	if (IsLayoutModified())
	{
		CopyMemory(pValuesFont, &m_fntLayoutValues, sizeof(LOGFONT));
		return TRUE;
	}
	return FALSE;
}

BOOL CANDOpenDialog::GetLayoutInvalidDataMode(BOOL &bEnable) CONST
{
	if (IsLayoutModified())
	{
		bEnable = m_bLayoutInvalidData;
		return TRUE;
	}
	return FALSE;
}

BOOL CANDOpenDialog::GetLayoutBadDataMode(BOOL &bEnable) CONST
{
	if (IsLayoutModified())
	{
		bEnable = m_bLayoutBadData;
		return TRUE;
	}
	return FALSE;
}

BOOL CANDOpenDialog::GetLayoutToolTipMode(BOOL &bEnable) CONST
{
	if (IsLayoutModified())
	{
		bEnable = m_bLayoutToolTips;
		return TRUE;
	}
	return FALSE;
}

BOOL CANDOpenDialog::IsLayoutModified() CONST
{
	LOGFONT  fntSample = { 0 };
	CANDLayout  cANDLayout;

	return((!m_cLayout.Compare(&cANDLayout) || m_nLayoutColumns.GetSize() > 0 || m_nLayoutColors.GetSize() > 0 || memcmp(&m_fntLayoutTitle, &fntSample, sizeof(LOGFONT)) || memcmp(&m_fntLayoutLabels, &fntSample, sizeof(LOGFONT)) || memcmp(&m_fntLayoutItems, &fntSample, sizeof(LOGFONT)) || memcmp(&m_fntLayoutValues, &fntSample, sizeof(LOGFONT)) || m_bLayoutInvalidData || m_bLayoutBadData || m_bLayoutToolTips) ? TRUE : FALSE);
}

BOOL CANDOpenDialog::GetRetrieveMode(UINT &nMode) CONST
{
	nMode = m_nRetrieveMode;
	return TRUE;
}

BOOL CANDOpenDialog::GetRetrieveSpeed(UINT &nSpeed) CONST
{
	nSpeed = m_nRetrieveSpeed;
	return((m_nRetrieveMode & AND_RETRIEVE_AUTOFORWARD) ? TRUE : FALSE);
}

BOOL CANDOpenDialog::GetRetrieveInterval(CTimeSpan &tInterval) CONST
{
	tInterval = m_tRetrieveInterval;
	return(((m_nRetrieveMode & AND_RETRIEVE_AUTOFORWARD) || (m_nRetrieveMode & AND_RETRIEVE_MANUALFORWARD)) ? TRUE : FALSE);
}

BOOL CANDOpenDialog::GetRetrieveStartTime(CTimeKey &tTimeKey) CONST
{
	tTimeKey = m_tRetrieveStartTime;
	return(((m_nRetrieveMode & AND_RETRIEVE_AUTOFORWARD) || (m_nRetrieveMode & AND_RETRIEVE_PSEUDOREALTIME) || (m_nRetrieveMode & AND_RETRIEVE_MANUALFORWARD)) ? TRUE : FALSE);
}

BOOL CANDOpenDialog::GetRetrieveStopTime(CTimeKey &tTimeKey) CONST
{
	tTimeKey = m_tRetrieveStopTime;
	return((((m_nRetrieveMode & AND_RETRIEVE_AUTOFORWARD) || (m_nRetrieveMode & AND_RETRIEVE_PSEUDOREALTIME) || (m_nRetrieveMode & AND_RETRIEVE_MANUALFORWARD)) && (m_nRetrieveMode & AND_RETRIEVE_STOPBYTIME)) ? TRUE : FALSE);
}

BOOL CANDOpenDialog::GetRetrieveFileName(CString &szFileName) CONST
{
	szFileName = ((m_nRetrieveMode & AND_RETRIEVE_AUTOFORWARD) || (m_nRetrieveMode & AND_RETRIEVE_PSEUDOREALTIME) || (m_nRetrieveMode & AND_RETRIEVE_MANUALFORWARD)) ? (LPCTSTR)m_szRetrieveFileName : EMPTYSTRING;
	return !szFileName.IsEmpty();
}

BOOL CANDOpenDialog::IsRetrievingModified() CONST
{
	return((m_nRetrieveMode != 0) ? TRUE : FALSE);
}

BOOL CANDOpenDialog::GetPrintJobs(CANDPrintJobs &pPrintJobs) CONST
{
	CByteArray  nPrintInfo;

	return((IsPrintingModified()) ? pPrintJobs.Copy(&m_pPrintJobs) : pPrintJobs.Unmap(nPrintInfo));
}

BOOL CANDOpenDialog::IsPrintingModified() CONST
{
	return((m_pPrintJobs.GetSize() > 0) ? TRUE : FALSE);
}

CANDWnd *CANDOpenDialog::GetParent() CONST
{
	return((CANDWnd *)CDisplayDialog::GetParent());
}

VOID CANDOpenDialog::EnumLayouts()
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szDisplay[2];
	CANDLayout  *pANDLayout;
	CANDLayouts  pANDLayouts;

	for (nDisplay = 0, nDisplays = (IsDlgButtonChecked(IDC_AND_OPEN_TYPE_NORMAL)) ? GetDatabase()->EnumANDs(pANDLayouts, DATABASE_SUBCOMPONENT_AND_NORMAL) : ((IsDlgButtonChecked(IDC_AND_OPEN_TYPE_GENERIC)) ? GetDatabase()->EnumANDs(pANDLayouts, DATABASE_SUBCOMPONENT_AND_GENERIC) : EnumTemporaryANDs(pANDLayouts)), SendDlgItemMessage(IDC_AND_OPEN_DISPLAY, CB_RESETCONTENT); nDisplay < nDisplays; nDisplay++)
	{
		if ((pANDLayout = pANDLayouts.GetAt(nDisplay)))
		{
			if (pANDLayout->GetTitle().IsEmpty())
			{
				SendDlgItemMessage(IDC_AND_OPEN_DISPLAY, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pANDLayout->GetName());
				continue;
			}
			szDisplay[0].Format(STRING(IDS_ANDOPENDIALOG_TITLE), (LPCTSTR)pANDLayout->GetName(), (LPCTSTR)pANDLayout->GetTitle());
			szDisplay[1].Format(STRING(IDS_ANDOPENDIALOG_SPECIALTITLE), (LPCTSTR)pANDLayout->GetTitle(), (LPCTSTR)pANDLayout->GetName());
			SendDlgItemMessage(IDC_AND_OPEN_DISPLAY, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)((IsDlgButtonChecked(IDC_AND_OPEN_TYPE_NORMAL)) ? (LPCTSTR)szDisplay[0] : ((IsDlgButtonChecked(IDC_AND_OPEN_TYPE_GENERIC)) ? (LPCTSTR)szDisplay[1] : (LPCTSTR)pANDLayout->GetTitle())));
		}
	}
	GetDlgItem(IDC_AND_OPEN_REMOVE)->ShowWindow((IsDlgButtonChecked(IDC_AND_OPEN_TYPE_TEMPORARY)) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_AND_OPEN_DISPLAY_STATIC)->EnableWindow((IsDlgButtonChecked(IDC_AND_OPEN_TYPE_TEMPORARY) || SendDlgItemMessage(IDC_AND_OPEN_DISPLAY, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_OPEN_DISPLAY)->EnableWindow((IsDlgButtonChecked(IDC_AND_OPEN_TYPE_TEMPORARY) || SendDlgItemMessage(IDC_AND_OPEN_DISPLAY, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_OPEN_FIND)->EnableWindow((SendDlgItemMessage(IDC_AND_OPEN_DISPLAY, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_AND_OPEN_SETTINGS)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_OPEN_REMOVE)->EnableWindow(FALSE);
}

BOOL CANDOpenDialog::FindLayout() CONST
{
	CANDLayout  cANDLayout;

	return FindLayout(cANDLayout);
}
BOOL CANDOpenDialog::FindLayout(CANDLayout &cLayout) CONST
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szDisplay[2];
	CANDLayout  *pANDLayout;
	CANDLayouts  pANDLayouts;

	for (GetDlgItem(IDC_AND_OPEN_DISPLAY)->GetWindowText(szDisplay[0]); IsDlgButtonChecked(IDC_AND_OPEN_TYPE_NORMAL); )
	{
		for (nDisplay = 0, nDisplays = GetDatabase()->EnumANDs(pANDLayouts, DATABASE_SUBCOMPONENT_AND_NORMAL); nDisplay < nDisplays; nDisplay++)
		{
			if (!(pANDLayout = pANDLayouts.GetAt(nDisplay)))
			{
				pANDLayouts.RemoveAt(nDisplay);
				nDisplays--;
				nDisplay--;
				continue;
			}
			szDisplay[1].Format(STRING(IDS_ANDOPENDIALOG_TITLE), (LPCTSTR)pANDLayout->GetName(), (LPCTSTR)pANDLayout->GetTitle());
			if (!szDisplay[0].CompareNoCase(szDisplay[1]) || !szDisplay[0].CompareNoCase(pANDLayout->GetName()) || !szDisplay[0].CompareNoCase(pANDLayout->GetTitle()))
			{
				if (GetDatabase()->LoadAND(pANDLayout->GetName(), cLayout, DATABASE_SUBCOMPONENT_AND_NORMAL)) break;
				continue;
			}
		}
		return((nDisplay < nDisplays) ? TRUE : FALSE);
	}
	if (IsDlgButtonChecked(IDC_AND_OPEN_TYPE_GENERIC))
	{
		for (nDisplay = 0, nDisplays = GetDatabase()->EnumANDs(pANDLayouts, DATABASE_SUBCOMPONENT_AND_GENERIC); nDisplay < nDisplays; nDisplay++)
		{
			if (!(pANDLayout = pANDLayouts.GetAt(nDisplay)))
			{
				pANDLayouts.RemoveAt(nDisplay);
				nDisplays--;
				nDisplay--;
				continue;
			}
			szDisplay[1].Format(STRING(IDS_ANDOPENDIALOG_SPECIALTITLE), (LPCTSTR)pANDLayout->GetTitle(), (LPCTSTR)pANDLayout->GetName());
			if (!szDisplay[0].CompareNoCase(szDisplay[1]) || !szDisplay[0].CompareNoCase(pANDLayout->GetName()) || !szDisplay[0].CompareNoCase(pANDLayout->GetTitle()))
			{
				if (GetDatabase()->LoadAND(pANDLayout->GetName(), cLayout, DATABASE_SUBCOMPONENT_AND_GENERIC)) break;
				continue;
			}
		}
		return((nDisplay < nDisplays) ? TRUE : FALSE);
	}
	if (IsDlgButtonChecked(IDC_AND_OPEN_TYPE_TEMPORARY))
	{
		for (nDisplay = 0, nDisplays = EnumTemporaryANDs(pANDLayouts); nDisplay < nDisplays; nDisplay++)
		{
			if (!(pANDLayout = pANDLayouts.GetAt(nDisplay)))
			{
				pANDLayouts.RemoveAt(nDisplay);
				nDisplays--;
				nDisplay--;
				continue;
			}
			if (!szDisplay[0].CompareNoCase(pANDLayout->GetTitle()))
			{
				if (cLayout.Copy(pANDLayout)) break;
				continue;
			}
		}
		return((nDisplay < nDisplays) ? TRUE : FALSE);
	}
	return FALSE;
}

BOOL CANDOpenDialog::InitializeLayout(CANDLayout &cLayout) CONST
{
	return((m_cLayout.GetName() == cLayout.GetName()) ? cLayout.Copy(&m_cLayout) : TRUE);
}

BOOL CANDOpenDialog::Check(BOOL bModified) CONST
{
	CANDLayout  cANDLayout;

	return(((IsDlgButtonChecked(IDC_AND_OPEN_MODE_REALTIME) || IsDlgButtonChecked(IDC_AND_OPEN_MODE_HISTORY)) && ((!IsDlgButtonChecked(IDC_AND_OPEN_TYPE_TEMPORARY) && FindLayout(cANDLayout)) || (IsDlgButtonChecked(IDC_AND_OPEN_TYPE_TEMPORARY) && (FindLayout(cANDLayout) || (GetDlgItem(IDC_AND_OPEN_DISPLAY)->GetWindowTextLength() > 0 && CheckAccountPrivilege(PRIVILEGE_AND_TEMPORARYUSE))))) && (IsDlgButtonChecked(IDC_AND_OPEN_MODE_REALTIME) || IsRetrievingModified())) ? TRUE : FALSE);
}

void CANDOpenDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CANDOpenDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CANDOpenDialog::PostNcDestroy()
{
	m_cLayout.RemoveAll();
	m_pPrintJobs.RemoveAll();
	m_nLayoutColors.RemoveAll();
	m_nLayoutColumns.RemoveAll();
	CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CANDOpenDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CANDOpenDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_AND_OPEN_SETTINGS, OnSettings)
	ON_BN_CLICKED(IDC_AND_OPEN_FIND, OnFind)
	ON_BN_CLICKED(IDC_AND_OPEN_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_AND_OPEN_TYPE_NORMAL, OnTypeNormal)
	ON_BN_CLICKED(IDC_AND_OPEN_TYPE_GENERIC, OnTypeGeneric)
	ON_BN_CLICKED(IDC_AND_OPEN_TYPE_TEMPORARY, OnTypeTemporary)
	ON_BN_CLICKED(IDC_AND_OPEN_MODE_REALTIME, OnRealtimeMode)
	ON_BN_CLICKED(IDC_AND_OPEN_MODE_HISTORY, OnHistoryMode)
	ON_BN_CLICKED(IDC_AND_OPEN_HELP, OnHelp)
	ON_CBN_EDITCHANGE(IDC_AND_OPEN_DISPLAY, OnEditchangeTitle)
	ON_CBN_SELCHANGE(IDC_AND_OPEN_DISPLAY, OnSelchangeTitle)
	ON_CBN_DBLCLK(IDC_AND_OPEN_DISPLAY, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDOpenDialog message handlers

BOOL CANDOpenDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	CheckRadioButton(IDC_AND_OPEN_TYPE_NORMAL, IDC_AND_OPEN_TYPE_TEMPORARY, IDC_AND_OPEN_TYPE_NORMAL);
	CheckDlgButton(IDC_AND_OPEN_MODE_REALTIME, TRUE);
	CheckDlgButton(IDC_AND_OPEN_MODE_HISTORY, FALSE);
	GetDlgItem(IDC_AND_OPEN_DETAILS)->EnableWindow();
	GetDlgItem(IDC_AND_OPEN_TYPE)->EnableWindow();
	GetDlgItem(IDC_AND_OPEN_TYPE_NORMAL)->EnableWindow();
	GetDlgItem(IDC_AND_OPEN_TYPE_GENERIC)->EnableWindow();
	GetDlgItem(IDC_AND_OPEN_TYPE_TEMPORARY)->EnableWindow();
	GetDlgItem(IDC_AND_OPEN_MODE)->EnableWindow();
	GetDlgItem(IDC_AND_OPEN_MODE_REALTIME)->EnableWindow();
	GetDlgItem(IDC_AND_OPEN_MODE_HISTORY)->EnableWindow(CheckAccountPrivilege(PRIVILEGE_OFFLINE_OPERATE));
	EnumLayouts();
	return TRUE;
}

void CANDOpenDialog::OnSettings()
{
	ReportEvent((m_dlgSettings.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CANDOpenDialog::OnFind()
{
	INT  nResult;
	CString  szDisplay[2];
	CANDLayout  cANDLayout;

	if ((nResult = m_dlgFindDisplay.Create(this, (IsDlgButtonChecked(IDC_AND_OPEN_TYPE_NORMAL)) ? AND_TYPE_NORMAL : ((IsDlgButtonChecked(IDC_AND_OPEN_TYPE_GENERIC)) ? AND_TYPE_GENERIC : ((IsDlgButtonChecked(IDC_AND_OPEN_TYPE_TEMPORARY)) ? AND_TYPE_TEMPORARY : 0)), cANDLayout)) == IDOK)
	{
		for (szDisplay[0].Format(STRING(IDS_ANDOPENDIALOG_TITLE), (LPCTSTR)cANDLayout.GetName(), (LPCTSTR)cANDLayout.GetTitle()), szDisplay[1].Format(STRING(IDS_ANDOPENDIALOG_SPECIALTITLE), (LPCTSTR)cANDLayout.GetTitle(), (LPCTSTR)cANDLayout.GetName()); cANDLayout.GetTitle().IsEmpty(); )
		{
			szDisplay[0] = szDisplay[1] = cANDLayout.GetName();
			break;
		}
		GetDlgItem(IDC_AND_OPEN_SETTINGS)->EnableWindow((SendDlgItemMessage(IDC_AND_OPEN_DISPLAY, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_AND_OPEN_DISPLAY, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)((IsDlgButtonChecked(IDC_AND_OPEN_TYPE_NORMAL)) ? (LPCTSTR)szDisplay[0] : ((IsDlgButtonChecked(IDC_AND_OPEN_TYPE_GENERIC)) ? (LPCTSTR)szDisplay[1] : (LPCTSTR)cANDLayout.GetTitle())))) >= 0 && (GetMode() != DISPLAY_MODE_REALTIME || !GetParent()->Find(MAKELONG(DISPLAY_TYPE_AND, GetType()), GetMode(), cANDLayout.GetName()))) ? (!IsDlgButtonChecked(IDC_AND_OPEN_TYPE_TEMPORARY) || CheckAccountPrivilege(PRIVILEGE_AND_TEMPORARYUSE)) : FALSE);
		GetDlgItem(IDC_AND_OPEN_DISPLAY)->SetFocus();
	}
	ReportEvent((nResult <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDOpenDialog::OnRemove()
{
	CANDLayout  cANDLayout;
	CHourglassCursor  cCursor;

	if (FindLayout(cANDLayout) && RemoveTemporaryAND(cANDLayout.GetName()))
	{
		SendDlgItemMessage(IDC_AND_OPEN_DISPLAY, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_AND_OPEN_DISPLAY, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cANDLayout.GetName()));
		SendDlgItemMessage(IDC_AND_OPEN_DISPLAY, CB_SETCURSEL, (WPARAM)-1);
	}
	GetDlgItem(IDC_AND_OPEN_SETTINGS)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_OPEN_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_AND_OPEN_DISPLAY)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDOpenDialog::OnEditchangeTitle()
{
	CANDLayout  cANDLayout;

	GetDlgItem(IDC_AND_OPEN_SETTINGS)->EnableWindow((((!IsDlgButtonChecked(IDC_AND_OPEN_TYPE_TEMPORARY) && FindLayout(cANDLayout)) || (IsDlgButtonChecked(IDC_AND_OPEN_TYPE_TEMPORARY) && (FindLayout(cANDLayout) || GetDlgItem(IDC_AND_OPEN_DISPLAY)->GetWindowTextLength() > 0))) && (GetMode() != DISPLAY_MODE_REALTIME || !GetParent()->Find(MAKELONG(DISPLAY_TYPE_AND, GetType()), GetMode(), cANDLayout.GetName()))) ? (!IsDlgButtonChecked(IDC_AND_OPEN_TYPE_TEMPORARY) || CheckAccountPrivilege(PRIVILEGE_AND_TEMPORARYUSE)) : FALSE);
	GetDlgItem(IDC_AND_OPEN_REMOVE)->EnableWindow((IsDlgButtonChecked(IDC_AND_OPEN_TYPE_TEMPORARY) && FindLayout(cANDLayout)) ? CheckAccountPrivilege(PRIVILEGE_AND_TEMPORARYUSE) : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDOpenDialog::OnSelchangeTitle()
{
	CANDLayout  cANDLayout;

	SendDlgItemMessage(IDC_AND_OPEN_DISPLAY, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_AND_OPEN_DISPLAY, CB_GETCURSEL));
	GetDlgItem(IDC_AND_OPEN_SETTINGS)->EnableWindow((FindLayout(cANDLayout) && (GetMode() != DISPLAY_MODE_REALTIME || !GetParent()->Find(MAKELONG(DISPLAY_TYPE_AND, GetType()), GetMode(), cANDLayout.GetName()))) ? (!IsDlgButtonChecked(IDC_AND_OPEN_TYPE_TEMPORARY) || CheckAccountPrivilege(PRIVILEGE_AND_TEMPORARYUSE)) : FALSE);
	GetDlgItem(IDC_AND_OPEN_REMOVE)->EnableWindow((IsDlgButtonChecked(IDC_AND_OPEN_TYPE_TEMPORARY)) ? CheckAccountPrivilege(PRIVILEGE_AND_TEMPORARYUSE) : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDOpenDialog::OnTypeNormal()
{
	EnumLayouts();
	GetDlgItem(IDC_AND_OPEN_DISPLAY)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDOpenDialog::OnTypeGeneric()
{
	EnumLayouts();
	GetDlgItem(IDC_AND_OPEN_DISPLAY)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDOpenDialog::OnTypeTemporary()
{
	EnumLayouts();
	GetDlgItem(IDC_AND_OPEN_DISPLAY)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDOpenDialog::OnRealtimeMode()
{
	CANDLayout  cANDLayout;

	GetDlgItem(IDC_AND_OPEN_SETTINGS)->EnableWindow(((FindLayout(cANDLayout) || IsDlgButtonChecked(IDC_AND_OPEN_TYPE_TEMPORARY)) && (GetMode() != DISPLAY_MODE_REALTIME || !GetParent()->Find(MAKELONG(DISPLAY_TYPE_AND, GetType()), GetMode(), cANDLayout.GetName()))) ? (!IsDlgButtonChecked(IDC_AND_OPEN_TYPE_TEMPORARY) || CheckAccountPrivilege(PRIVILEGE_AND_TEMPORARYUSE)) : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CANDOpenDialog::OnHistoryMode()
{
	INT  nPos;
	CString  szType;
	CString  szTitle;
	CANDLayout  cANDLayout;

	if (IsDlgButtonChecked(IDC_AND_OPEN_TYPE_NORMAL))
	{
		for (szTitle = (FindLayout(cANDLayout)) ? cANDLayout.GetTitle() : STRING(IDS_WINDOW_UNKNOWNTITLE), szType.Format(STRING(IDS_ANDOPENDIALOG_TYPENORMAL), (LPCTSTR)cANDLayout.GetName()), szType = ((nPos = (cANDLayout.GetName().IsEmpty()) ? szType.Find(SPACE) : -1) >= 0) ? szType.Left(nPos) : szType; IsDlgButtonChecked(IDC_AND_OPEN_MODE_HISTORY); )
		{
			ReportEvent((m_dlgRetrievals.Create(this, szTitle, szType) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
			break;
		}
		for (GetDlgItem(IDC_AND_OPEN_SETTINGS)->EnableWindow((FindLayout(cANDLayout) && (GetMode() != DISPLAY_MODE_REALTIME || !GetParent()->Find(MAKELONG(DISPLAY_TYPE_AND, GetType()), GetMode(), cANDLayout.GetName()))) ? TRUE : FALSE); SendDlgItemMessage(IDC_AND_OPEN_DISPLAY, CB_GETCOUNT) > 0; )
		{
			GetDlgItem(IDC_AND_OPEN_DISPLAY)->SetFocus();
			break;
		}
		for (; IsDlgButtonChecked(IDC_AND_OPEN_MODE_REALTIME); )
		{
			GetDlgItem(IDC_AND_OPEN_MODE_REALTIME)->SetFocus();
			break;
		}
		GetDlgItem(IDOK)->EnableWindow(Check());
		return;
	}
	if (IsDlgButtonChecked(IDC_AND_OPEN_TYPE_GENERIC))
	{
		for (szTitle = (FindLayout(cANDLayout)) ? cANDLayout.GetTitle() : STRING(IDS_WINDOW_UNKNOWNTITLE), szType.Format(STRING(IDS_ANDOPENDIALOG_TYPEGENERIC), (LPCTSTR)cANDLayout.GetName()), szType = ((nPos = (cANDLayout.GetName().IsEmpty()) ? szType.Find(SPACE) : -1) >= 0) ? szType.Left(nPos) : szType; IsDlgButtonChecked(IDC_AND_OPEN_MODE_HISTORY); )
		{
			ReportEvent((m_dlgRetrievals.Create(this, szTitle, szType) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
			break;
		}
		for (GetDlgItem(IDC_AND_OPEN_SETTINGS)->EnableWindow((FindLayout(cANDLayout) && (GetMode() != DISPLAY_MODE_REALTIME || !GetParent()->Find(MAKELONG(DISPLAY_TYPE_AND, GetType()), GetMode(), cANDLayout.GetName()))) ? TRUE : FALSE); SendDlgItemMessage(IDC_AND_OPEN_DISPLAY, CB_GETCOUNT) > 0; )
		{
			GetDlgItem(IDC_AND_OPEN_DISPLAY)->SetFocus();
			break;
		}
		for (; IsDlgButtonChecked(IDC_AND_OPEN_MODE_REALTIME); )
		{
			GetDlgItem(IDC_AND_OPEN_MODE_REALTIME)->SetFocus();
			break;
		}
		GetDlgItem(IDOK)->EnableWindow(Check());
		return;
	}
	if (IsDlgButtonChecked(IDC_AND_OPEN_TYPE_TEMPORARY))
	{
		for (szTitle = (FindLayout(cANDLayout)) ? cANDLayout.GetTitle() : STRING(IDS_WINDOW_UNKNOWNTITLE), szType = STRING(IDS_ANDOPENDIALOG_TYPETEMPORARY); IsDlgButtonChecked(IDC_AND_OPEN_MODE_HISTORY); )
		{
			ReportEvent((m_dlgRetrievals.Create(this, szTitle, szType) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
			break;
		}
		for (GetDlgItem(IDC_AND_OPEN_SETTINGS)->EnableWindow((GetMode() != DISPLAY_MODE_REALTIME || !GetParent()->Find(MAKELONG(DISPLAY_TYPE_AND, GetType()), GetMode(), cANDLayout.GetName())) ? CheckAccountPrivilege(PRIVILEGE_AND_TEMPORARYUSE) : FALSE); SendDlgItemMessage(IDC_AND_OPEN_DISPLAY, CB_GETCOUNT) >= 0; )
		{
			GetDlgItem(IDC_AND_OPEN_DISPLAY)->SetFocus();
			break;
		}
		for (; IsDlgButtonChecked(IDC_AND_OPEN_MODE_REALTIME); )
		{
			GetDlgItem(IDC_AND_OPEN_MODE_REALTIME)->SetFocus();
			break;
		}
		GetDlgItem(IDOK)->EnableWindow(Check());
		return;
	}
	CheckDlgButton(IDC_AND_OPEN_MODE_REALTIME, TRUE);
	CheckDlgButton(IDC_AND_OPEN_MODE_HISTORY, FALSE);
	for (GetDlgItem(IDC_AND_OPEN_SETTINGS)->EnableWindow(((FindLayout(cANDLayout) || IsDlgButtonChecked(IDC_AND_OPEN_TYPE_TEMPORARY)) && (GetMode() != DISPLAY_MODE_REALTIME || !GetParent()->Find(MAKELONG(DISPLAY_TYPE_AND, GetType()), GetMode(), cANDLayout.GetName()))) ? (!IsDlgButtonChecked(IDC_AND_OPEN_TYPE_TEMPORARY) || CheckAccountPrivilege(PRIVILEGE_AND_TEMPORARYUSE)) : FALSE); IsDlgButtonChecked(IDC_AND_OPEN_TYPE_TEMPORARY) || SendDlgItemMessage(IDC_AND_OPEN_DISPLAY, CB_GETCOUNT) > 0; )
	{
		GetDlgItem(IDC_AND_OPEN_DISPLAY)->SetFocus();
		break;
	}
	for (; IsDlgButtonChecked(IDC_AND_OPEN_MODE_REALTIME); )
	{
		GetDlgItem(IDC_AND_OPEN_MODE_REALTIME)->SetFocus();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

BOOL CANDOpenDialog::OnCloseSettingsDialog(UINT nCode)
{
	if (nCode == IDOK)
	{
		if (m_dlgSettings.IsLayoutModified())
		{
			m_dlgSettings.GetLayout(m_cLayout, m_nLayoutColumns);
			m_dlgSettings.GetLayoutColors(m_nLayoutColors);
			m_dlgSettings.GetLayoutTitleFont(&m_fntLayoutTitle);
			m_dlgSettings.GetLayoutLabelsFont(&m_fntLayoutLabels);
			m_dlgSettings.GetLayoutItemsFont(&m_fntLayoutItems);
			m_dlgSettings.GetLayoutValuesFont(&m_fntLayoutValues);
			m_dlgSettings.GetLayoutInvalidDataMode(m_bLayoutInvalidData);
			m_dlgSettings.GetLayoutBadDataMode(m_bLayoutBadData);
			m_dlgSettings.GetLayoutToolTipMode(m_bLayoutToolTips);
		}
		if (m_dlgSettings.IsRetrievingModified()) m_dlgSettings.GetRetrieveFileName(m_szRetrieveFileName);
		if (m_dlgSettings.IsPrintingModified()) m_dlgSettings.GetPrintJobs(m_pPrintJobs);
	}
	return TRUE;
}

BOOL CANDOpenDialog::OnCloseRetrieveDialog(UINT nCode)
{
	CANDLayout  cANDLayout;

	if (nCode == IDOK)
	{
		m_dlgRetrievals.GetMode(m_nRetrieveMode);
		m_dlgRetrievals.GetSpeed(m_nRetrieveSpeed);
		m_dlgRetrievals.GetInterval(m_tRetrieveInterval);
		m_dlgRetrievals.GetStartTime(m_tRetrieveStartTime);
		m_dlgRetrievals.GetStopTime(m_tRetrieveStopTime);
	}
	if (nCode != IDOK || !m_nRetrieveMode)
	{
		CheckDlgButton(IDC_AND_OPEN_MODE_REALTIME, TRUE);
		CheckDlgButton(IDC_AND_OPEN_MODE_HISTORY, FALSE);
	}
	return TRUE;
}

void CANDOpenDialog::OnOK()
{
	CANDWnd  *pANDWnd[2];
	CANDLayout  cANDLayout;
	CHourglassCursor  cCursor;

	if ((pANDWnd[0] = GetParent()))
	{
		if (GetMode() == DISPLAY_MODE_REALTIME)
		{
			if ((pANDWnd[1] = (FindLayout(cANDLayout)) ? pANDWnd[0]->Find(MAKELONG(DISPLAY_TYPE_AND, GetType()), GetMode(), cANDLayout.GetName()) : (CANDWnd *)NULL))
			{
				GetDisplayArea()->ActivateDisplay(pANDWnd[1]);
				EndDialog(IDCANCEL);
				return;
			}
		}
		if (!pANDWnd[0]->OnCloseOpenDialog(IDOK))
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

void CANDOpenDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	GetParent()->OnCloseOpenDialog(IDCANCEL);
	CDisplayDialog::OnCancel();
}

BOOL CANDOpenDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_ANDOPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CANDOpenDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_ANDOPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CANDRetrieveThread

IMPLEMENT_DYNCREATE(CANDRetrieveThread, CThread)

CANDRetrieveThread::CANDRetrieveThread() : CThread()
{
	m_nMode = 0;
	m_nSpeed = 0;
	m_tInterval = 0;
	m_tStartTime = 0;
	m_tStopTime = 0;
	m_pbFlag = (LPLONG)NULL;
	m_bInit[0] = (HANDLE)NULL;
	m_bInit[1] = (HANDLE)NULL;
	m_hAction[ANDRETRIEVETHREAD_ACTION_STOP] = (HANDLE)NULL;
	m_hAction[ANDRETRIEVETHREAD_ACTION_AUTOFORWARD] = (HANDLE)NULL;
	m_hAction[ANDRETRIEVETHREAD_ACTION_AUTOBACKWARD] = (HANDLE)NULL;
	m_hAction[ANDRETRIEVETHREAD_ACTION_MANUALFORWARD] = (HANDLE)NULL;
	m_hAction[ANDRETRIEVETHREAD_ACTION_MANUALBACKWARD] = (HANDLE)NULL;
	m_hAction[ANDRETRIEVETHREAD_ACTION_PSEUDOREALTIME] = (HANDLE)NULL;
}

BOOL CANDRetrieveThread::Start(CANDWnd *pParentWnd, HANDLE bInit, HANDLE bContinue, LPCTSTR pszFileName, UINT nMode, UINT nSpeed, CONST CTimeSpan &tInterval, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, LONG *pbFlag, HANDLE bRetrieveStop, HANDLE bRetrieveAutoForward, HANDLE bRetrieveAutoBackward, HANDLE bRetrieveManualForward, HANDLE bRetrieveManualBackward, HANDLE bRetrievePseudoRealtime)
{
	m_nMode = nMode;
	m_nSpeed = nSpeed;
	m_pbFlag = pbFlag;
	m_bInit[0] = bInit;
	m_bInit[1] = bContinue;
	m_tInterval = tInterval;
	m_tStartTime = tStartTime;
	m_tStopTime = tStopTime;
	m_szFileName = pszFileName;
	m_hAction[ANDRETRIEVETHREAD_ACTION_STOP] = bRetrieveStop;
	m_hAction[ANDRETRIEVETHREAD_ACTION_AUTOFORWARD] = bRetrieveAutoForward;
	m_hAction[ANDRETRIEVETHREAD_ACTION_AUTOBACKWARD] = bRetrieveAutoBackward;
	m_hAction[ANDRETRIEVETHREAD_ACTION_MANUALFORWARD] = bRetrieveManualForward;
	m_hAction[ANDRETRIEVETHREAD_ACTION_MANUALBACKWARD] = bRetrieveManualBackward;
	m_hAction[ANDRETRIEVETHREAD_ACTION_PSEUDOREALTIME] = bRetrievePseudoRealtime;
	return((ResetEvent(bInit)) ? CreateThread(pParentWnd, THREAD_PRIORITY_BELOW_NORMAL) : FALSE);
}

BOOL CANDRetrieveThread::Stop()
{
	return((DestroyThread() >= 0) ? TRUE : FALSE);
}

BOOL CANDRetrieveThread::InitializeTMData(CTMParameters &pTMParameters, BOOL bBadData)
{
	return m_cTMEnvironment.Initialize(pTMParameters, bBadData);
}

int CANDRetrieveThread::Run()
{
	UINT  nAction;
	UINT  nResult;
	DWORD  dwResult;
	TIMETAG  tTime;
	CTimeKey  tTimeKey;
	CTimeTag  tTimeTag[2];
	CANDWnd  *pANDWnd = (CANDWnd *)GetThreadInfo();

	StartRetrieving();
	if (m_cTMEnvironment.Create(GetDatabase()))
	{
		if (m_cTMProcessEngine.Open(GetDatabase(), GetAccountSpacecraftName(), GetRetrieveFileName(), &m_cTMEnvironment))
		{
			for (BeginWaitCursor(), pANDWnd->SetRetrieveMode((m_nMode = (m_nMode & (AND_RETRIEVE_AUTOBACKWARD | AND_RETRIEVE_MANUALBACKWARD)) ? ((m_nMode & ~(AND_RETRIEVE_AUTOBACKWARD | AND_RETRIEVE_MANUALBACKWARD | AND_RETRIEVE_STOPPED | AND_RETRIEVE_RELATIVE)) | AND_RETRIEVE_MANUALFORWARD) : (m_nMode & ~(AND_RETRIEVE_STOPPED | AND_RETRIEVE_RELATIVE)))), pANDWnd->Reset(&m_cTMEnvironment), SignalObjectAndWait(m_bInit[0], m_bInit[1], INFINITE, FALSE), nResult = m_cTMProcessEngine.ProcessTMData(GetDatabase(), &m_cTMEnvironment, (tTimeKey = GetRetrieveStartTime())), nAction = 0; (dwResult = Wait(0)) == WAIT_TIMEOUT && !pANDWnd->IsInitialized(); )
			{
				SwitchToThread();
				continue;
			}
			for (; dwResult == WAIT_TIMEOUT; BeginWaitCursor())
			{
				if ((GetRetrieveMode() & AND_RETRIEVE_AUTOFORWARD) && !(GetRetrieveMode() & AND_RETRIEVE_STOPPED))
				{
					for (; (nResult & HISTORYFILE_SUCCESS) && !(GetRetrieveMode() & AND_RETRIEVE_RELATIVE) && (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT && ((!(GetRetrieveMode() & AND_RETRIEVE_EXACTTIME) && !pANDWnd->Update(tTimeKey, &m_cTMEnvironment, nResult)) || ((GetRetrieveMode() & AND_RETRIEVE_EXACTTIME) && tTimeKey < GetRetrieveStartTime())); )
					{
						if (!((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, 0)) & HISTORYFILE_SUCCESS)) break;
						if (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS))
						{
							if (GetRetrieveMode() & AND_RETRIEVE_STOPBYREALTIME)
							{
								pANDWnd->SetMode(DISPLAY_MODE_REALTIME);
								pANDWnd->ProcessRealtimeData();
								pANDWnd->UpdateBars();
								break;
							}
							ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
							pANDWnd->SetRetrieveMode(pANDWnd->GetRetrieveMode() | AND_RETRIEVE_STOPPED);
							pANDWnd->UpdateBars();
							break;
						}
						if ((GetRetrieveMode() & AND_RETRIEVE_STOPBYTIME) && GetRetrieveStopTime() < tTimeKey)
						{
							pANDWnd->SetRetrieveMode(pANDWnd->GetRetrieveMode() | AND_RETRIEVE_STOPPED);
							pANDWnd->UpdateBars();
							break;
						}
					}
					EndWaitCursor();
					if (pANDWnd->GetMode() != DISPLAY_MODE_REALTIME)
					{
						if ((((nResult & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS))) || (GetRetrieveMode() & AND_RETRIEVE_RELATIVE)) && (!(GetRetrieveMode() & AND_RETRIEVE_STOPBYTIME) || GetRetrieveStopTime() >= tTimeKey) && dwResult == WAIT_TIMEOUT)
						{
							if ((!(GetRetrieveMode() & AND_RETRIEVE_RELATIVE) && (!(GetRetrieveMode() & AND_RETRIEVE_EXACTTIME) || pANDWnd->Update(tTimeKey, &m_cTMEnvironment, (nResult = (nResult | HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS) & ~HISTORYFILE_TMUNIT) & (HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS)) || TRUE)) || (GetRetrieveMode() & AND_RETRIEVE_RELATIVE))
							{
								for (; (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 10 * (10 - GetRetrieveSpeed())*(10 - GetRetrieveSpeed()))) == WAIT_TIMEOUT; )
								{
									if (((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, GetRetrieveInterval())) & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)))
									{
										if (!(GetRetrieveMode() & AND_RETRIEVE_STOPBYTIME) || GetRetrieveStopTime() >= tTimeKey)
										{
											pANDWnd->Update(tTimeKey, &m_cTMEnvironment, nResult);
											continue;
										}
									}
									if (nResult & HISTORYFILE_SUCCESS)
									{
										if (GetRetrieveMode() & AND_RETRIEVE_STOPBYREALTIME)
										{
											pANDWnd->SetMode(DISPLAY_MODE_REALTIME);
											pANDWnd->ProcessRealtimeData();
											pANDWnd->UpdateBars();
											break;
										}
										ReportEvent((GetRetrieveMode() & AND_RETRIEVE_STOPBYEND) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING : USER_NOERROR);
										pANDWnd->SetRetrieveMode(pANDWnd->GetRetrieveMode() | AND_RETRIEVE_STOPPED);
										pANDWnd->UpdateBars();
									}
									break;
								}
							}
						}
						if (!(nResult & HISTORYFILE_SUCCESS))
						{
							ReportEvent((nResult == HISTORYFILE_DATA_NONE) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING : ((nResult == HISTORYFILE_OPEN_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_OPEN_FAILURE : ((nResult == HISTORYFILE_WRITE_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_WRITE_FAILURE : ((nResult == HISTORYFILE_READ_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_READ_FAILURE : ((nResult == HISTORYFILE_ERROR) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE : SYSTEM_NOERROR)))));
							pANDWnd->SetRetrieveMode(pANDWnd->GetRetrieveMode() | AND_RETRIEVE_STOPPED);
							pANDWnd->Reset(&m_cTMEnvironment);
							pANDWnd->UpdateBars();
							break;
						}
					}
					if (pANDWnd->GetMode() == DISPLAY_MODE_REALTIME) break;
				}
				if ((GetRetrieveMode() & AND_RETRIEVE_AUTOBACKWARD) && !(GetRetrieveMode() & AND_RETRIEVE_STOPPED))
				{
					if ((nResult & HISTORYFILE_SUCCESS) && (GetRetrieveMode() & AND_RETRIEVE_RELATIVE) && dwResult == WAIT_TIMEOUT)
					{
						for (EndWaitCursor(); (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 10 * (10 - GetRetrieveSpeed())*(10 - GetRetrieveSpeed()))) == WAIT_TIMEOUT; )
						{
							if (((nResult = m_cTMProcessEngine.RewindTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, GetRetrieveInterval())) & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)))
							{
								pANDWnd->Update(tTimeKey, &m_cTMEnvironment, nResult);
								continue;
							}
							break;
						}
					}
					if (nResult & HISTORYFILE_SUCCESS)
					{
						if (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS))
						{
							ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
							pANDWnd->Update(tTimeKey, &m_cTMEnvironment, nResult);
							pANDWnd->SetRetrieveMode(pANDWnd->GetRetrieveMode() | AND_RETRIEVE_STOPPED);
							pANDWnd->UpdateBars();
						}
					}
					else
					{
						ReportEvent((nResult == HISTORYFILE_DATA_NONE) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING : ((nResult == HISTORYFILE_OPEN_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_OPEN_FAILURE : ((nResult == HISTORYFILE_WRITE_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_WRITE_FAILURE : ((nResult == HISTORYFILE_READ_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_READ_FAILURE : ((nResult == HISTORYFILE_ERROR) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE : SYSTEM_NOERROR)))));
						pANDWnd->SetRetrieveMode(pANDWnd->GetRetrieveMode() | AND_RETRIEVE_STOPPED);
						pANDWnd->Reset(&m_cTMEnvironment);
						pANDWnd->UpdateBars();
						EndWaitCursor();
						break;
					}
					EndWaitCursor();
				}
				if ((GetRetrieveMode() & AND_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & AND_RETRIEVE_STOPPED))
				{
					for (; (nResult & HISTORYFILE_SUCCESS) && !(GetRetrieveMode() & AND_RETRIEVE_RELATIVE) && (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT && ((!(GetRetrieveMode() & AND_RETRIEVE_EXACTTIME) && !pANDWnd->Update(tTimeKey, &m_cTMEnvironment, nResult)) || ((GetRetrieveMode() & AND_RETRIEVE_EXACTTIME) && tTimeKey < GetRetrieveStartTime())); )
					{
						if (!((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, 0)) & HISTORYFILE_SUCCESS)) break;
						if (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS))
						{
							if (GetRetrieveMode() & AND_RETRIEVE_STOPBYREALTIME)
							{
								pANDWnd->SetMode(DISPLAY_MODE_REALTIME);
								pANDWnd->ProcessRealtimeData();
								pANDWnd->UpdateBars();
								break;
							}
							ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
							pANDWnd->SetRetrieveMode(pANDWnd->GetRetrieveMode() | AND_RETRIEVE_STOPPED);
							pANDWnd->UpdateBars();
							break;
						}
					}
					EndWaitCursor();
					if (pANDWnd->GetMode() != DISPLAY_MODE_REALTIME)
					{
						if ((((nResult & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS))) || (GetRetrieveMode() & AND_RETRIEVE_RELATIVE)) && dwResult == WAIT_TIMEOUT)
						{
							if ((!(GetRetrieveMode() & AND_RETRIEVE_RELATIVE) && (!(GetRetrieveMode() & AND_RETRIEVE_EXACTTIME) || pANDWnd->Update(tTimeKey, &m_cTMEnvironment, (nResult = (nResult | HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS) & ~HISTORYFILE_TMUNIT) & (HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS)) || TRUE)) || (GetRetrieveMode() & AND_RETRIEVE_RELATIVE))
							{
								for (; (dwResult = (!(GetRetrieveMode() & AND_RETRIEVE_RELATIVE) || nAction != ANDRETRIEVETHREAD_ACTION_MANUALFORWARD) ? Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, INFINITE) : (WAIT_OBJECT_0 + nAction + 1)) == WAIT_OBJECT_0 + ANDRETRIEVETHREAD_ACTION_MANUALFORWARD + 1; EndWaitCursor())
								{
									for (BeginWaitCursor(TRUE); (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT; )
									{
										if (((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, GetRetrieveInterval())) & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)))
										{
											if (pANDWnd->Update(tTimeKey, &m_cTMEnvironment, nResult)) break;
											continue;
										}
										if (nResult & HISTORYFILE_SUCCESS)
										{
											if (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS))
											{
												if (GetRetrieveMode() & AND_RETRIEVE_STOPBYREALTIME)
												{
													pANDWnd->SetMode(DISPLAY_MODE_REALTIME);
													pANDWnd->ProcessRealtimeData();
													pANDWnd->UpdateBars();
													break;
												}
												ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
												pANDWnd->SetRetrieveMode(pANDWnd->GetRetrieveMode() | AND_RETRIEVE_STOPPED);
												pANDWnd->UpdateBars();
											}
										}
										break;
									}
									if (!(nResult & HISTORYFILE_SUCCESS) || (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS)) || pANDWnd->GetMode() == DISPLAY_MODE_REALTIME || dwResult == WAIT_OBJECT_0)
									{
										EndWaitCursor();
										break;
									}
									nAction = 0;
								}
							}
						}
						if (!(nResult & HISTORYFILE_SUCCESS))
						{
							ReportEvent((nResult == HISTORYFILE_DATA_NONE) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING : ((nResult == HISTORYFILE_OPEN_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_OPEN_FAILURE : ((nResult == HISTORYFILE_WRITE_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_WRITE_FAILURE : ((nResult == HISTORYFILE_READ_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_READ_FAILURE : ((nResult == HISTORYFILE_ERROR) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE : SYSTEM_NOERROR)))));
							pANDWnd->SetRetrieveMode(pANDWnd->GetRetrieveMode() | AND_RETRIEVE_STOPPED);
							pANDWnd->Reset(&m_cTMEnvironment);
							pANDWnd->UpdateBars();
							break;
						}
					}
					if (pANDWnd->GetMode() == DISPLAY_MODE_REALTIME) break;
				}
				if ((GetRetrieveMode() & AND_RETRIEVE_MANUALBACKWARD) && !(GetRetrieveMode() & AND_RETRIEVE_STOPPED))
				{
					if ((nResult & HISTORYFILE_SUCCESS) && (GetRetrieveMode() & AND_RETRIEVE_RELATIVE) && dwResult == WAIT_TIMEOUT)
					{
						for (EndWaitCursor(); (dwResult = (nAction != ANDRETRIEVETHREAD_ACTION_MANUALBACKWARD) ? Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, INFINITE) : (WAIT_OBJECT_0 + nAction + 1)) == WAIT_OBJECT_0 + ANDRETRIEVETHREAD_ACTION_MANUALBACKWARD + 1; EndWaitCursor())
						{
							for (BeginWaitCursor(TRUE); (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT; )
							{
								if (((nResult = m_cTMProcessEngine.RewindTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, GetRetrieveInterval())) & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)))
								{
									if (pANDWnd->Update(tTimeKey, &m_cTMEnvironment, nResult)) break;
									continue;
								}
								if (nResult & HISTORYFILE_SUCCESS)
								{
									if (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS))
									{
										ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
										pANDWnd->Update(tTimeKey, &m_cTMEnvironment, nResult);
										pANDWnd->SetRetrieveMode(pANDWnd->GetRetrieveMode() | AND_RETRIEVE_STOPPED);
										pANDWnd->UpdateBars();
									}
								}
								break;
							}
							if (!(nResult & HISTORYFILE_SUCCESS) || (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS)) || dwResult == WAIT_OBJECT_0)
							{
								EndWaitCursor();
								break;
							}
							nAction = 0;
						}
					}
					if (!(nResult & HISTORYFILE_SUCCESS))
					{
						ReportEvent((nResult == HISTORYFILE_DATA_NONE) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING : ((nResult == HISTORYFILE_OPEN_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_OPEN_FAILURE : ((nResult == HISTORYFILE_WRITE_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_WRITE_FAILURE : ((nResult == HISTORYFILE_READ_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_READ_FAILURE : ((nResult == HISTORYFILE_ERROR) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE : SYSTEM_NOERROR)))));
						pANDWnd->SetRetrieveMode(pANDWnd->GetRetrieveMode() | AND_RETRIEVE_STOPPED);
						pANDWnd->Reset(&m_cTMEnvironment);
						pANDWnd->UpdateBars();
						EndWaitCursor();
						break;
					}
					EndWaitCursor();
				}
				if ((GetRetrieveMode() & AND_RETRIEVE_PSEUDOREALTIME) && !(GetRetrieveMode() & AND_RETRIEVE_STOPPED))
				{
					for (; (nResult & HISTORYFILE_SUCCESS) && !(GetRetrieveMode() & AND_RETRIEVE_RELATIVE) && (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT && ((!(GetRetrieveMode() & AND_RETRIEVE_EXACTTIME) && !pANDWnd->Update(tTimeKey, &m_cTMEnvironment, nResult)) || ((GetRetrieveMode() & AND_RETRIEVE_EXACTTIME) && tTimeKey < GetRetrieveStartTime())); )
					{
						if (!((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, 0)) & HISTORYFILE_SUCCESS)) break;
						if (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS))
						{
							if (GetRetrieveMode() & AND_RETRIEVE_STOPBYREALTIME)
							{
								pANDWnd->SetMode(DISPLAY_MODE_REALTIME);
								pANDWnd->ProcessRealtimeData();
								pANDWnd->UpdateBars();
								break;
							}
							ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
							pANDWnd->SetRetrieveMode(pANDWnd->GetRetrieveMode() | AND_RETRIEVE_STOPPED);
							pANDWnd->UpdateBars();
							break;
						}
						if ((GetRetrieveMode() & AND_RETRIEVE_STOPBYTIME) && GetRetrieveStopTime() < tTimeKey)
						{
							pANDWnd->SetRetrieveMode(pANDWnd->GetRetrieveMode() | AND_RETRIEVE_STOPPED);
							pANDWnd->UpdateBars();
							break;
						}
					}
					EndWaitCursor();
					if (pANDWnd->GetMode() != DISPLAY_MODE_REALTIME)
					{
						if ((((nResult & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS))) || (GetRetrieveMode() & AND_RETRIEVE_RELATIVE)) && (!(GetRetrieveMode() & AND_RETRIEVE_STOPBYTIME) || GetRetrieveStopTime() >= tTimeKey) && dwResult == WAIT_TIMEOUT)
						{
							if ((!(GetRetrieveMode() & AND_RETRIEVE_RELATIVE) && (!(GetRetrieveMode() & AND_RETRIEVE_EXACTTIME) || pANDWnd->Update(tTimeKey, &m_cTMEnvironment, (nResult = (nResult | HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS) & ~HISTORYFILE_TMUNIT) & (HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS)) || TRUE)) || (GetRetrieveMode() & AND_RETRIEVE_RELATIVE))
							{
								for (tTimeTag[0] = ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)) ? ((nResult & HISTORYFILE_TMUNIT) ? m_cTMEnvironment.GetTMUnit()->GetTimeTag() : CTimeTag(tTimeKey)) : CTimeTag(tTimeKey), tTimeTag[1] = CTimeTag(), tTime = CTimeTag().GetTime(); (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT; tTime = CTimeTag().GetTime())
								{
									if (((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, 0)) & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)))
									{
										if ((dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, (((nResult & HISTORYFILE_TMUNIT) && tTimeTag[1].GetTime() - tTimeTag[0].GetTime() + m_cTMEnvironment.GetTMUnit()->GetTimeTag().GetTime() > tTime) || ((nResult & HISTORYFILE_TMPARAMETERS) && tTimeTag[1].GetTime() - tTimeTag[0].GetTime() + CTimeTag(tTimeKey).GetTime() > tTime)) ? ((nResult & HISTORYFILE_TMUNIT) ? (DWORD)((tTimeTag[1].GetTime() - tTimeTag[0].GetTime() + m_cTMEnvironment.GetTMUnit()->GetTimeTag().GetTime() - tTime) / 1000) : (DWORD)((tTimeTag[1].GetTime() - tTimeTag[0].GetTime() + CTimeTag(tTimeKey).GetTime() - tTime) / 1000)) : 0)) != WAIT_TIMEOUT) break;
										if ((!(GetRetrieveMode() & AND_RETRIEVE_STOPBYTIME) || GetRetrieveStopTime() >= tTimeKey) && ((nResult & HISTORYFILE_SYNCHRONIZE) || !tTimeTag[0].GetTime()))
										{
											tTimeTag[0] = (nResult & HISTORYFILE_TMUNIT) ? m_cTMEnvironment.GetTMUnit()->GetTimeTag() : CTimeTag(tTimeKey);
											tTimeTag[1] = tTime = CTimeTag().GetTime();
										}
										if (!(GetRetrieveMode() & AND_RETRIEVE_STOPBYTIME) || GetRetrieveStopTime() >= tTimeKey)
										{
											pANDWnd->Update(tTimeKey, &m_cTMEnvironment, nResult);
											continue;
										}
									}
									if (nResult & HISTORYFILE_SUCCESS)
									{
										if (GetRetrieveMode() & AND_RETRIEVE_STOPBYREALTIME)
										{
											pANDWnd->SetMode(DISPLAY_MODE_REALTIME);
											pANDWnd->ProcessRealtimeData();
											pANDWnd->UpdateBars();
											break;
										}
										ReportEvent((GetRetrieveMode() & AND_RETRIEVE_STOPBYEND) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING : USER_NOERROR);
										pANDWnd->SetRetrieveMode(pANDWnd->GetRetrieveMode() | AND_RETRIEVE_STOPPED);
										pANDWnd->UpdateBars();
									}
									break;
								}
							}
						}
						if (!(nResult & HISTORYFILE_SUCCESS))
						{
							ReportEvent((nResult == HISTORYFILE_DATA_NONE) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING : ((nResult == HISTORYFILE_OPEN_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_OPEN_FAILURE : ((nResult == HISTORYFILE_WRITE_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_WRITE_FAILURE : ((nResult == HISTORYFILE_READ_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_READ_FAILURE : ((nResult == HISTORYFILE_ERROR) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE : SYSTEM_NOERROR)))));
							pANDWnd->SetRetrieveMode(pANDWnd->GetRetrieveMode() | AND_RETRIEVE_STOPPED);
							pANDWnd->Reset(&m_cTMEnvironment);
							pANDWnd->UpdateBars();
							break;
						}
					}
					if (pANDWnd->GetMode() == DISPLAY_MODE_REALTIME) break;
				}
				if ((GetRetrieveMode() & AND_RETRIEVE_AUTOFORWARD) || (GetRetrieveMode() & AND_RETRIEVE_AUTOBACKWARD) || (GetRetrieveMode() & AND_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & AND_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & AND_RETRIEVE_PSEUDOREALTIME))
				{
					while ((dwResult = ((dwResult < WAIT_OBJECT_0 + ANDRETRIEVETHREAD_ACTION_AUTOFORWARD + 1 || dwResult > WAIT_OBJECT_0 + ANDRETRIEVETHREAD_ACTION_PSEUDOREALTIME + 1) && dwResult != WAIT_OBJECT_0) ? Wait(m_hAction, ANDRETRIEVETHREAD_ACTION_TYPES, FALSE, INFINITE, FALSE) : dwResult) == WAIT_OBJECT_0 + ANDRETRIEVETHREAD_ACTION_STOP + 1)
					{
						m_nMode = (GetRetrieveMode() & (AND_RETRIEVE_STOPBYTIME | AND_RETRIEVE_STOPBYEND | AND_RETRIEVE_STOPBYREALTIME)) | AND_RETRIEVE_STOPPED | AND_RETRIEVE_RELATIVE;
						m_nMode |= ((GetRetrieveMode() & (AND_RETRIEVE_STOPBYTIME | AND_RETRIEVE_STOPBYEND | AND_RETRIEVE_STOPBYREALTIME)) == 0) ? AND_RETRIEVE_STOPBYREALTIME : 0;
						pANDWnd->SetRetrieveMode(m_nMode);
						pANDWnd->UpdateBars();
					}
					if (dwResult == WAIT_OBJECT_0 + ANDRETRIEVETHREAD_ACTION_AUTOFORWARD + 1)
					{
						m_nMode = (GetRetrieveMode() & (AND_RETRIEVE_STOPBYTIME | AND_RETRIEVE_STOPBYEND | AND_RETRIEVE_STOPBYREALTIME)) | AND_RETRIEVE_AUTOFORWARD | AND_RETRIEVE_RELATIVE;
						m_nMode |= ((GetRetrieveMode() & (AND_RETRIEVE_STOPBYTIME | AND_RETRIEVE_STOPBYEND | AND_RETRIEVE_STOPBYREALTIME)) == 0) ? AND_RETRIEVE_STOPBYREALTIME : 0;
						nAction = ANDRETRIEVETHREAD_ACTION_AUTOFORWARD;
						pANDWnd->SetRetrieveMode(m_nMode);
						pANDWnd->UpdateBars();
						dwResult = WAIT_TIMEOUT;
						continue;
					}
					if (dwResult == WAIT_OBJECT_0 + ANDRETRIEVETHREAD_ACTION_AUTOBACKWARD + 1)
					{
						m_nMode = (GetRetrieveMode() & (AND_RETRIEVE_STOPBYTIME | AND_RETRIEVE_STOPBYEND | AND_RETRIEVE_STOPBYREALTIME)) | AND_RETRIEVE_AUTOBACKWARD | AND_RETRIEVE_RELATIVE;
						m_nMode |= ((GetRetrieveMode() & (AND_RETRIEVE_STOPBYTIME | AND_RETRIEVE_STOPBYEND | AND_RETRIEVE_STOPBYREALTIME)) == 0) ? AND_RETRIEVE_STOPBYEND : 0;
						nAction = ANDRETRIEVETHREAD_ACTION_AUTOBACKWARD;
						pANDWnd->SetRetrieveMode(m_nMode);
						pANDWnd->UpdateBars();
						dwResult = WAIT_TIMEOUT;
						continue;
					}
					if (dwResult == WAIT_OBJECT_0 + ANDRETRIEVETHREAD_ACTION_MANUALFORWARD + 1)
					{
						m_nMode = (GetRetrieveMode() & (AND_RETRIEVE_STOPBYTIME | AND_RETRIEVE_STOPBYEND | AND_RETRIEVE_STOPBYREALTIME)) | AND_RETRIEVE_MANUALFORWARD | AND_RETRIEVE_RELATIVE;
						nAction = ANDRETRIEVETHREAD_ACTION_MANUALFORWARD;
						pANDWnd->SetRetrieveMode(m_nMode);
						pANDWnd->UpdateBars();
						dwResult = WAIT_TIMEOUT;
						continue;
					}
					if (dwResult == WAIT_OBJECT_0 + ANDRETRIEVETHREAD_ACTION_MANUALBACKWARD + 1)
					{
						m_nMode = (GetRetrieveMode() & (AND_RETRIEVE_STOPBYTIME | AND_RETRIEVE_STOPBYEND | AND_RETRIEVE_STOPBYREALTIME)) | AND_RETRIEVE_MANUALBACKWARD | AND_RETRIEVE_RELATIVE;
						nAction = ANDRETRIEVETHREAD_ACTION_MANUALBACKWARD;
						pANDWnd->SetRetrieveMode(m_nMode);
						pANDWnd->UpdateBars();
						dwResult = WAIT_TIMEOUT;
						continue;
					}
					if (dwResult == WAIT_OBJECT_0 + ANDRETRIEVETHREAD_ACTION_PSEUDOREALTIME + 1)
					{
						m_nMode = (GetRetrieveMode() & (AND_RETRIEVE_STOPBYTIME | AND_RETRIEVE_STOPBYEND | AND_RETRIEVE_STOPBYREALTIME)) | AND_RETRIEVE_PSEUDOREALTIME | AND_RETRIEVE_RELATIVE;
						m_nMode |= ((GetRetrieveMode() & (AND_RETRIEVE_STOPBYTIME | AND_RETRIEVE_STOPBYEND | AND_RETRIEVE_STOPBYREALTIME)) == 0) ? AND_RETRIEVE_STOPBYREALTIME : 0;
						nAction = ANDRETRIEVETHREAD_ACTION_PSEUDOREALTIME;
						pANDWnd->SetRetrieveMode(m_nMode);
						pANDWnd->UpdateBars();
						dwResult = WAIT_TIMEOUT;
						continue;
					}
				}
				break;
			}
			m_cTMProcessEngine.Close();
		}
		else
		{
			SignalObjectAndWait(m_bInit[0], m_bInit[1], INFINITE, FALSE);
			ReportEvent(SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE);
		}
		m_cTMEnvironment.Destroy();
	}
	else
	{
		SignalObjectAndWait(m_bInit[0], m_bInit[1], INFINITE, FALSE);
		ReportEvent(SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE);
	}
	StopRetrieving();
	EndWaitCursor();
	return 0;
}

VOID CANDRetrieveThread::StartRetrieving()
{
	InterlockedExchange(m_pbFlag, TRUE);
}

VOID CANDRetrieveThread::StopRetrieving()
{
	InterlockedExchange(m_pbFlag, FALSE);
}

UINT CANDRetrieveThread::GetRetrieveMode() CONST
{
	return((IsThreadActive()) ? m_nMode : 0);
}

UINT CANDRetrieveThread::GetRetrieveSpeed() CONST
{
	return((IsThreadActive()) ? m_nSpeed : 0);
}

CTimeSpan CANDRetrieveThread::GetRetrieveInterval() CONST
{
	return((IsThreadActive()) ? m_tInterval.GetTotalSeconds() : 0);
}

CTimeKey CANDRetrieveThread::GetRetrieveStartTime() CONST
{
	return((IsThreadActive()) ? m_tStartTime : 0);
}

CTimeKey CANDRetrieveThread::GetRetrieveStopTime() CONST
{
	return((IsThreadActive()) ? m_tStopTime : 0);
}

CString CANDRetrieveThread::GetRetrieveFileName() CONST
{
	return((IsThreadActive()) ? (LPCTSTR)m_szFileName : EMPTYSTRING);
}

VOID CANDRetrieveThread::BeginWaitCursor(BOOL bForced)
{
	POINT  ptCursor;
	CANDWnd  *pANDWnd;
	CHourglassCursor  cCursor;

	for (GetCursorPos(&ptCursor), InterlockedExchange(m_pbFlag, MAKELONG(TRUE, ((m_nMode & AND_RETRIEVE_RELATIVE) != AND_RETRIEVE_RELATIVE || bForced) ? TRUE : FALSE)), SetCursorPos(ptCursor.x, ptCursor.y); (pANDWnd = (CANDWnd *)GetThreadInfo()); )
	{
		pANDWnd->UpdateBars();
		break;
	}
}

VOID CANDRetrieveThread::EndWaitCursor()
{
	POINT  ptCursor;
	CANDWnd  *pANDWnd;
	CHourglassCursor  cCursor;

	for (GetCursorPos(&ptCursor), InterlockedExchange(m_pbFlag, LOWORD(*m_pbFlag)), SetCursorPos(ptCursor.x, ptCursor.y); (pANDWnd = (CANDWnd *)GetThreadInfo()); )
	{
		pANDWnd->UpdateBars();
		break;
	}
}

BEGIN_MESSAGE_MAP(CANDRetrieveThread, CThread)
	//{{AFX_MSG_MAP(CANDRetrieveThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDRetrieveThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CANDPrintThread

IMPLEMENT_DYNCREATE(CANDPrintThread, CThread)

BOOL CANDPrintThread::Start(CANDWnd *pParentWnd)
{
	return CreateThread(pParentWnd);
}

BOOL CANDPrintThread::Stop()
{
	return((DestroyThread() >= 0) ? TRUE : FALSE);
}

BOOL CANDPrintThread::SetPrintJobs(CONST CANDPrintJobs &pPrintJobs)
{
	INT  nJob[2][2];
	INT  nJobs[2][2];
	CANDPrintJobInfo  *pJobInfo;
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
			if ((pJobInfo = new CANDPrintJobInfo))
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

BOOL CANDPrintThread::GetPrintJobs(CANDPrintJobs &pPrintJobs) CONST
{
	CByteArray  nPrintInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(((m_pPrintJobs.GetSize() > 0 && pPrintJobs.Copy(&m_pPrintJobs)) || pPrintJobs.Unmap(nPrintInfo)) ? TRUE : FALSE);
}

int CANDPrintThread::Run()
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
	CANDPrintJobInfo  *pJobInfo[2];
	CANDWnd  *pANDWnd = (CANDWnd *)GetThreadInfo();

	for (dwJobResult = 0; Lock(); )
	{
		if (dwJobResult == WAIT_OBJECT_0 + 1 || !dwJobResult)
		{
			for (nJob = 0, nJobs = (INT)m_pPrintJobs.GetSize(); nJob < nJobs; nJob++)
			{
				if ((pJobInfo[0] = m_pPrintJobs.GetAt(nJob)) && (pJobInfo[0]->GetPrintMode() & AND_PRINT_ACTIVE))
				{
					if (pJobInfo[0]->GetPrintAtDailyTime(tJobDailyTime) || pJobInfo[0]->GetPrintAtDailyTime(tJobDailyTime, nJobStopCount) || pJobInfo[0]->GetPrintAtDailyTime(tJobDailyTime, tJobStopTime))
					{
						pJobInfo[0]->SetPrintLastDailyTime(((tJobTime = CTime::GetCurrentTime().GetTime()).GetTime() % SECONDSPERDAY >= tJobDailyTime.GetTotalSeconds()) ? ((SECONDSPERDAY*(tJobTime.GetTime() / SECONDSPERDAY)) + tJobDailyTime.GetTotalSeconds()) : ((SECONDSPERDAY*(tJobTime.GetTime() / SECONDSPERDAY - 1)) + tJobDailyTime.GetTotalSeconds()));
						continue;
					}
				}
			}
		}
		if ((pJobInfo[0] = ((tJobInterval = m_pPrintJobs.Schedule()) == 0) ? m_pPrintJobs.GetAt(0) : (CANDPrintJobInfo *)NULL))
		{
			for (bJobPrint = pANDWnd->Print(pJobInfo[0]); (pJobInfo[0]->GetPrintMode() & AND_PRINT_CLEARCOMMENTS) && bJobPrint; )
			{
				for (nJob = 1, nJobs = (INT)m_pPrintJobs.GetSize(); nJob < nJobs; nJob++)
				{
					if ((pJobInfo[1] = m_pPrintJobs.GetAt(nJob)))
					{
						if (pJobInfo[0]->GetName() == pJobInfo[1]->GetName())
						{
							pJobInfo[1]->SetPrintMode(pJobInfo[0]->GetPrintMode() & ~AND_PRINT_CLEARCOMMENTS);
							pJobInfo[1]->SetComments(EMPTYSTRING);
							break;
						}
					}
				}
				break;
			}
			ReportEvent((!bJobPrint) ? SYSTEM_WARNING_AND_PRINT_FAILURE : SYSTEM_NOERROR);
			m_pPrintJobs.RemoveAt(0);
			delete pJobInfo[0];
		}
		Unlock();
		if ((dwJobResult = Wait(m_cEvent, FALSE, (tJobInterval >= 0) ? (DWORD)(1000 * min(tJobInterval, SECONDSPERDAY)) : INFINITE)) != WAIT_TIMEOUT  &&  dwJobResult != WAIT_OBJECT_0 + 1) break;
	}
	return 0;
}

BEGIN_MESSAGE_MAP(CANDPrintThread, CThread)
	//{{AFX_MSG_MAP(CANDPrintThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDPrintThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CANDToolBar

IMPLEMENT_DYNCREATE(CANDToolBar, CDisplayToolBar)

CANDToolBar::CANDToolBar() : CDisplayToolBar()
{
	return;
}

BEGIN_MESSAGE_MAP(CANDToolBar, CDisplayToolBar)
	//{{AFX_MSG_MAP(CANDToolBar)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDToolBar message handlers


/////////////////////////////////////////////////////////////////////////////
// CANDStatusBar

IMPLEMENT_DYNCREATE(CANDStatusBar, CDisplayStatusBar)

CANDStatusBar::CANDStatusBar() : CDisplayStatusBar()
{
	return;
}

BOOL CANDStatusBar::SetIndicators(CONST UINT *pPanesID, INT nCount)
{
	INT  nIndex;
	CRect  rPane;
	CString  szPane;
	CToolInfo  cToolInfo;
	CDisplayLock  cLock(this);

	if (CDisplayStatusBar::SetIndicators(pPanesID, nCount))
	{
		if (CommandToIndex(ID_AND_STATUSBAR_MESSAGEPANE) >= 0)
		{
			szPane.Format(STRING(IDS_AND_STATUSBAR_UPDATEMESSAGE), (LPCTSTR)CTimeTag().FormatGmt(), (LPCTSTR)CString(CTimeTag().FormatGmt().Right(1), GetDatabase()->GetTMPacketTagLength()), -1, STRING(IDS_AND_STATUSBAR_QUALITYGOOD));
			SetPaneInfo(CommandToIndex(ID_AND_STATUSBAR_MESSAGEPANE), ID_AND_STATUSBAR_MESSAGEPANE, SBPS_NOBORDERS | SBPS_STRETCH, CalcPaneWidth(szPane + STRING(IDS_AND_STATUSBAR_TIMECORRELATIONFLAG)));
		}
		if (!IsWindow(m_wndToolTip.GetSafeHwnd()))
		{
			m_wndToolTip.Create(this, TTS_ALWAYSTIP | TTS_NOPREFIX | TTS_BALLOON);
			SetClassLongPtr(m_wndToolTip.GetSafeHwnd(), GCL_STYLE, GetClassLongPtr(m_wndToolTip.GetSafeHwnd(), GCL_STYLE) | CS_DROPSHADOW);
		}
		if (IsWindow(m_wndToolTip.GetSafeHwnd()))
		{
			if ((nIndex = CommandToIndex(ID_AND_STATUSBAR_MODEPANE)) >= 0)
			{
				for (GetItemRect(nIndex, rPane); !m_wndToolTip.GetToolInfo(cToolInfo, this, ID_AND_STATUSBAR_MODEPANE); )
				{
					m_wndToolTip.AddTool(this, LPSTR_TEXTCALLBACK, rPane, ID_AND_STATUSBAR_MODEPANE);
					break;
				}
			}
			if ((nIndex = CommandToIndex(ID_AND_STATUSBAR_TYPEPANE)) >= 0)
			{
				for (GetItemRect(nIndex, rPane); !m_wndToolTip.GetToolInfo(cToolInfo, this, ID_AND_STATUSBAR_TYPEPANE); )
				{
					m_wndToolTip.AddTool(this, LPSTR_TEXTCALLBACK, rPane, ID_AND_STATUSBAR_TYPEPANE);
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

CANDWnd *CANDStatusBar::GetParent() CONST
{
	return((CANDWnd *)CDisplayStatusBar::GetParent());
}

BEGIN_MESSAGE_MAP(CANDStatusBar, CDisplayStatusBar)
	//{{AFX_MSG_MAP(CANDStatusBar)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipNotify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDStatusBar message handlers

void CANDStatusBar::OnPaint()
{
	INT  nIndex;
	RECT  rPane;
	CToolInfo  cToolInfo;

	for (CDisplayStatusBar::OnPaint(); IsWindow(m_wndToolTip.GetSafeHwnd()); )
	{
		if ((nIndex = CommandToIndex(ID_AND_STATUSBAR_MODEPANE)) >= 0 && nIndex < m_prPanes.GetSize())
		{
			for (m_wndToolTip.GetToolInfo(cToolInfo, this, ID_AND_STATUSBAR_MODEPANE), CopyMemory(&rPane, m_prPanes.GetAt(nIndex), sizeof(RECT)); !EqualRect(&cToolInfo.rect, &rPane); )
			{
				SetRect(&cToolInfo.rect, rPane.left, rPane.top, rPane.right, rPane.bottom);
				m_wndToolTip.SetToolInfo(&cToolInfo);
				break;
			}
		}
		if ((nIndex = CommandToIndex(ID_AND_STATUSBAR_TYPEPANE)) >= 0 && nIndex < m_prPanes.GetSize())
		{
			for (m_wndToolTip.GetToolInfo(cToolInfo, this, ID_AND_STATUSBAR_TYPEPANE), CopyMemory(&rPane, m_prPanes.GetAt(nIndex), sizeof(RECT)); !EqualRect(&cToolInfo.rect, &rPane); )
			{
				SetRect(&cToolInfo.rect, rPane.left, rPane.top, rPane.right, rPane.bottom);
				m_wndToolTip.SetToolInfo(&cToolInfo);
				break;
			}
		}
		break;
	}
}

void CANDStatusBar::OnMouseMove(UINT nFlags, CPoint point)
{
	MSG  sMsg;

	if (IsWindow(m_wndToolTip.GetSafeHwnd()))
	{
		CopyMemory(&sMsg, GetCurrentMessage(), sizeof(MSG));
		m_wndToolTip.RelayEvent(&sMsg);
	}
	CDisplayStatusBar::OnMouseMove(nFlags, point);
}

BOOL CANDStatusBar::OnToolTipNotify(UINT nID, NMHDR *pNotifyInfo, LRESULT *pResult)
{
	TOOLTIPTEXT  *pToolTipInfo = (TOOLTIPTEXT *)pNotifyInfo;

	switch (pNotifyInfo->idFrom)
	{
	case ID_AND_STATUSBAR_MODEPANE:
	{ pToolTipInfo->lpszText = (LPTSTR)STRING(IDS_AND_STATUSBAR_MODEPANE);
	return TRUE;
	}
	case ID_AND_STATUSBAR_TYPEPANE:
	{ pToolTipInfo->lpszText = (LPTSTR)STRING(IDS_AND_STATUSBAR_TYPEPANE);
	return TRUE;
	}
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CANDToolTip

IMPLEMENT_DYNCREATE(CANDToolTip, CDisplayToolTip)

CANDToolTip::CANDToolTip() : CDisplayToolTip()
{
	return;
}

BEGIN_MESSAGE_MAP(CANDToolTip, CDisplayToolTip)
	//{{AFX_MSG_MAP(CANDToolTip)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDToolTip message handlers


/////////////////////////////////////////////////////////////////////////////
// CANDView

IMPLEMENT_DYNCREATE(CANDView, CTextView)

CANDView::CANDView() : CTextView()
{
	m_nLayoutColors.InsertAt(AND_OOLCOLOR_NOLIMIT, VGA_COLOR_GRAY);
	m_nLayoutColors.InsertAt(AND_OOLCOLOR_SOFTLIMIT, VGA_COLOR_RED);
	m_nLayoutColors.InsertAt(AND_OOLCOLOR_HARDLIMIT, VGA_COLOR_LTRED);
	m_nLayoutColors.InsertAt(AND_OOLCOLOR_DELTALIMIT, VGA_COLOR_MAGENTA);
	m_nLayoutColors.InsertAt(AND_OOLCOLOR_CONSISTENCYLIMIT, VGA_COLOR_YELLOW);
	ZeroMemory(&m_lfLayoutDefault[0], sizeof(LOGFONT));
	ZeroMemory(&m_lfLayoutDefault[1], sizeof(LOGFONT));
	ZeroMemory(&m_lfLayoutDefault[2], sizeof(LOGFONT));
	ZeroMemory(&m_lfLayoutDefault[3], sizeof(LOGFONT));
	m_hToolTipCursor = (HCURSOR)NULL;
	m_bLayoutFont = FALSE;
	m_bInvalidDataMode = FALSE;
	m_bBadDataMode = FALSE;
	m_bToolTipMode = TRUE;
}

BOOL CANDView::Create(CWnd *pParentWnd, DWORD dwStyle)
{
	return CTextView::Create(pParentWnd, CRect(0, 0, 0, 0), dwStyle);
}

BOOL CANDView::SetLayout(CONST CANDLayout &cLayout)
{
	return SetLayout(cLayout, AND_TITLEITEMS_DEFAULT);
}
BOOL CANDView::SetLayout(CONST CANDLayout &cLayout, UINT nColumns)
{
	CUIntArray  nColumnItems;

	nColumnItems.Add(AND_TITLEITEM_ID);
	if (nColumns & AND_TITLEITEM_DESCRIPTION) nColumnItems.Add(AND_TITLEITEM_DESCRIPTION);
	if (nColumns & AND_TITLEITEM_VALUE) nColumnItems.Add(AND_TITLEITEM_VALUE);
	if (nColumns & AND_TITLEITEM_UNIT) nColumnItems.Add(AND_TITLEITEM_UNIT);
	if (nColumns & AND_TITLEITEM_CHANGETMUNIT) nColumnItems.Add(AND_TITLEITEM_CHANGETMUNIT);
	if (nColumns & AND_TITLEITEM_CHANGETIME) nColumnItems.Add(AND_TITLEITEM_CHANGETIME);
	if (nColumns & AND_TITLEITEM_UPDATETMUNIT) nColumnItems.Add(AND_TITLEITEM_UPDATETMUNIT);
	if (nColumns & AND_TITLEITEM_UPDATETIME) nColumnItems.Add(AND_TITLEITEM_UPDATETIME);
	if (nColumns & AND_TITLEITEM_EXPECTEDVALUES) nColumnItems.Add(AND_TITLEITEM_EXPECTEDVALUES);
	return SetLayout(cLayout, nColumnItems);
}
BOOL CANDView::SetLayout(CONST CANDLayout &cLayout, CONST CUIntArray &nColumns)
{
	CUIntArray  nWidths;

	return((CalcColumnsWidth(nColumns, nWidths)) ? SetLayout(cLayout, nColumns, nWidths, TRUE) : FALSE);
}
BOOL CANDView::SetLayout(CONST CANDLayout &cLayout, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths, BOOL bAdjust)
{
	INT  nPos;
	INT  nRow;
	INT  nRows;
	INT  nType;
	INT  nIndex[2];
	INT  nCount[2];
	INT  nWidth[2];
	INT  nParameter;
	INT  nParameters;
	INT  nColumnGroup;
	BOOL  bParameter;
	UINT  nColumn;
	LOGFONT  lfFont;
	CTMUnit  cTMUnit;
	CString  szRow[2];
	CStringArray  szRows;
	CStringArray  szColumns;
	CUIntArray  nColumnWidths;
	CUIntArray  nColumnItems[2];
	CUIntArray  nCalTableRefs;
	CUIntArray  nCalValidityRefs;
	CTMParameter  *pTMParameter;
	CTextViewAttribute  *pAttribute;
	CTextViewAttributes  pAttributes;
	CANDLayoutParameter  *pParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CDatabaseTMNumCalTable  *pDatabaseTMNumCalTable;
	CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;
	CTextViewLock  cLock(this);

	if (!IsWindow(GetSafeHwnd()))
	{
		if (LookupColumnsName(nColumns, szColumns) && SetColumns(szColumns, nWidths))
		{
			m_nLayoutColumns.Copy(nColumns);
			m_cLayout.Copy(&cLayout);
			return TRUE;
		}
		return FALSE;
	}
	if ((nType = HIWORD(GetParent()->GetType())) == AND_TYPE_GENERIC)
	{
		for (nIndex[0] = 0, nCount[0] = cLayout.GetColumns(nColumnItems[0]); nIndex[0] < nCount[0]; nIndex[0]++)
		{
			if ((nColumn = nColumnItems[0].GetAt(nIndex[0])) == (UINT)-1) nColumn = AND_TITLEITEMS_DEFAULT;
			if (nColumn & AND_TITLEITEM_ID) nColumnItems[1].Add(AND_TITLEITEM_ID);
			if (nColumn & AND_TITLEITEM_DESCRIPTION) nColumnItems[1].Add(AND_TITLEITEM_DESCRIPTION);
			if (nColumn & AND_TITLEITEM_VALUE) nColumnItems[1].Add(AND_TITLEITEM_VALUE);
			if (nColumn & AND_TITLEITEM_UNIT) nColumnItems[1].Add(AND_TITLEITEM_UNIT);
			if (nColumn & AND_TITLEITEM_CHANGETMUNIT) nColumnItems[1].Add(AND_TITLEITEM_CHANGETMUNIT);
			if (nColumn & AND_TITLEITEM_CHANGETIME) nColumnItems[1].Add(AND_TITLEITEM_CHANGETIME);
			if (nColumn & AND_TITLEITEM_UPDATETMUNIT) nColumnItems[1].Add(AND_TITLEITEM_UPDATETMUNIT);
			if (nColumn & AND_TITLEITEM_UPDATETIME) nColumnItems[1].Add(AND_TITLEITEM_UPDATETIME);
			if (nColumn & AND_TITLEITEM_EXPECTEDVALUES) nColumnItems[1].Add(AND_TITLEITEM_EXPECTEDVALUES);
		}
		if (nColumnItems[1].GetSize() > 0 && (nColumns.GetSize() != nColumnItems[1].GetSize() || memcmp(nColumns.GetData(), nColumnItems[1].GetData(), nColumns.GetSize()*sizeof(UINT)))) return SetLayout(cLayout, nColumnItems[1]);
	}
	for (nParameter = 0, nParameters = (m_cLayout.Copy(&cLayout)) ? (INT)m_cLayout.GetSize() : -1, nColumnWidths.Copy(nWidths), nRows = (nParameters >= 0) ? 0 : -1; nParameter < nParameters; nParameter++)
	{
		if ((pParameter = m_cLayout.GetAt(nParameter)) != (CANDLayoutParameter *)NULL)
		{
			nRow = (pParameter->GetRow() >= 0) ? pParameter->GetRow() : nParameter;
			nRows = max(nRow + 1, nRows);
			continue;
		}
	}
	for (nRow = 0; nRow < nRows; nRow++)
	{
		for (nIndex[0] = 0, nCount[0] = (INT)nColumns.GetSize(), m_nLayoutColumns.Copy(nColumns), szRow[0].Empty(), nParameter = -1; nIndex[0] < nCount[0]; nIndex[0]++)
		{
			if ((pParameter = m_cLayout.GetAt(nParameter)) && ConvertIndexToColumn(nIndex[0], nColumnGroup) && ((pParameter->GetColumn() < 0 && !nColumnGroup && (((pParameter->GetRow() >= 0 && pParameter->GetRow() == nRow) || (pParameter->GetRow() < 0 && nRow == nParameter)))) || (pParameter->GetColumn() == nColumnGroup  &&  pParameter->GetRow() == nRow)))
			{
				if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pParameter->GetName()))) || (nType == AND_TYPE_GENERIC  &&  !pParameter->GetName().IsEmpty()) || pParameter->IsLabel())
				{
					switch (nColumns.GetAt(nIndex[0]))
					{
					case AND_TITLEITEM_ID:
					{ szRow[1] = (!pParameter->IsLabel()) ? pParameter->GetName() : EMPTYSTRING;
					break;
					}
					case AND_TITLEITEM_DESCRIPTION:
					{ szRow[1] = (!pParameter->IsLabel()) ? ((pParameter->GetDescription().IsEmpty()) ? ((pDatabaseTMParameter != (CDatabaseTMParameter *)NULL) ? pDatabaseTMParameter->GetDescription() : EMPTYSTRING) : pParameter->GetDescription()) : pParameter->GetLabel();
					break;
					}
					case AND_TITLEITEM_UNIT:
					{ szRow[1] = (!pParameter->IsLabel()) ? ((pDatabaseTMParameter != (CDatabaseTMParameter *)NULL) ? pDatabaseTMParameter->GetUnit() : EMPTYSTRING) : EMPTYSTRING;
					break;
					}
					case AND_TITLEITEM_EXPECTEDVALUES:
					{ szRow[1] = ((nPos = (!pParameter->IsLabel()) ? pParameter->GetComment().Find(EOL) : -1) >= 0) ? pParameter->GetComment().Mid(nPos + 1) : EMPTYSTRING;
					break;
					}
					default:
					{ szRow[1] = EMPTYSTRING;
					break;
					}
					}
					for (szRow[0] += (nIndex[0] > 0) ? (GetColumnDelimiter() + szRow[1]) : szRow[1], nWidth[0] = CalcColumnWidth(nColumns.GetAt(nIndex[0]), szRow[1], pParameter->IsLabel()), nIndex[1] = (bAdjust && ((!nIndex[0] && nColumnWidths.GetAt(nIndex[0]) < (UINT)nWidth[0]) || (nIndex[0] > 0 && nColumnWidths.GetAt(nIndex[0]) - nColumnWidths.GetAt(nIndex[0] - 1) < (UINT)nWidth[0]))) ? nIndex[0] : nCount[0], nWidth[1] = (nIndex[0] > 0) ? (nColumnWidths.GetAt(nIndex[0]) - nColumnWidths.GetAt(nIndex[0] - 1)) : nColumnWidths.GetAt(nIndex[0]), nCount[1] = nCount[0]; nIndex[1] < nCount[1]; nIndex[1]++)
					{
						nColumnWidths.SetAt(nIndex[1], nColumnWidths.GetAt(nIndex[1]) + nWidth[0] - nWidth[1]);
						continue;
					}
					if ((pAttribute = (nRow >= pAttributes.GetSize() || !pAttributes.GetAt(nRow)) ? new CTextViewAttribute : pAttributes.GetAt(nRow)))
					{
						for (pAttribute->SetColumnFormat(nIndex[0], ((nColumns.GetAt(nIndex[0]) == AND_TITLEITEM_LABELS && pParameter->IsLabel()) || nColumns.GetAt(nIndex[0]) == AND_TITLEITEM_VALUE) ? (pParameter->GetAlignment() | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX) : (DT_LEFT | DT_VCENTER | DT_WORDBREAK | DT_NOPREFIX)), pAttribute->SetColumnColor(nIndex[0], (pParameter->GetColor() == GetSysColor(COLOR_WINDOW)) ? LookupColumnColor(nColumns.GetAt(nIndex[0])) : pParameter->GetColor()), GetLabelsFont(&lfFont, FALSE); pParameter->IsLabel(); )
						{
							pAttribute->SetColumnFont(nIndex[0], &lfFont);
							break;
						}
						pAttributes.SetAtGrow(nRow, pAttribute);
					}
					continue;
				}
				m_cLayout.RemoveAt(nParameter);
				delete pParameter;
			}
			for (nParameter = 0, nParameters = (INT)m_cLayout.GetSize(), bParameter = FALSE; nParameter < nParameters; nParameter++)
			{
				if ((pParameter = m_cLayout.GetAt(nParameter)) && ConvertIndexToColumn(nIndex[0], nColumnGroup))
				{
					if ((pParameter->GetColumn() < 0 && !nColumnGroup && ((pParameter->GetRow() >= 0 && pParameter->GetRow() == nRow) || (pParameter->GetRow() < 0 && nRow == nParameter))) || (pParameter->GetColumn() == nColumnGroup  &&  pParameter->GetRow() == nRow)) break;
					bParameter = (pParameter->GetRow() >= nRow) ? TRUE : bParameter;
				}
			}
			if (nParameter < nParameters)
			{
				nIndex[0]--;
				continue;
			}
			if (bParameter)
			{
				szRow[0] += (nIndex[0] > 0) ? (LPCTSTR)CString(GetColumnDelimiter()) : EMPTYSTRING;
				continue;
			}
			break;
		}
		if (nIndex[0] == nCount[0])
		{
			if ((pAttribute = (nRow >= pAttributes.GetSize() || !pAttributes.GetAt(nRow)) ? new CTextViewAttribute : (CTextViewAttribute *)NULL))
			{
				pAttribute->SetColumnFormat(-1, DT_LEFT | DT_VCENTER | DT_NOPREFIX);
				pAttribute->SetColumnColor(-1, GetSysColor(COLOR_WINDOW));
				pAttributes.SetAtGrow(nRow, pAttribute);
			}
			szRows.InsertAt(nRow, szRow[0]);
			continue;
		}
		break;
	}
	for (nRow = 0, nRows = (nRows >= 0) ? ((LookupColumnsName(nColumns, szColumns) && SetColumns(szColumns, nColumnWidths) && szRows.GetSize() == pAttributes.GetSize() && DeleteAllText(FALSE)) ? (INT)szRows.GetSize() : -1) : -1; nRow < nRows; nRow++)
	{
		InsertText(nRow, szRows.GetAt(nRow), pAttributes.GetAt(nRow), (nRow == nRows - 1) ? TRUE : FALSE);
		continue;
	}
	for (nParameter = 0, nParameters = (INT)m_cLayout.GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pParameter = m_cLayout.GetAt(nParameter)) && !pParameter->IsLabel() && m_pLayoutValues.Find(pParameter->GetName()) < 0)
		{
			if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(pParameter->GetRef())))
			{
				if ((pTMParameter = new CTMParameter))
				{
					pTMParameter->SetTag(pParameter->GetName());
					pTMParameter->SetAttributes((pDatabaseTMParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_FLOATINGPOINT | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_DECIMAL | TMPARAMETER_RADIX_HEXADECIMAL)) | (pParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_FLOATINGPOINT | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_DECIMAL | TMPARAMETER_RADIX_HEXADECIMAL)));
					pTMParameter->SetPastValueSamples((pParameter->GetOccurrence() < 0) ? max(abs(pParameter->GetOccurrence()), pTMParameter->GetPastValueSamples()) : pTMParameter->GetPastValueSamples());
					if (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_NATURE_CONSTANT) pTMParameter->SetRawValue(&cTMUnit, 0, pDatabaseTMParameter->GetConstValue(), TMPARAMETER_STATUS_GOOD | TMPARAMETER_STATUS_NOLIMIT | TMPARAMETER_STATUS_VALID, (pDatabaseTMParameter->GetCalTableRefs(nCalTableRefs, nCalValidityRefs) > 0) ? ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) ? (((pDatabaseTMNumCalTable = GetDatabase()->GetTMNumCalTables()->GetAt(nCalTableRefs.GetAt(0)))) ? (LPCTSTR)pDatabaseTMNumCalTable->GetName() : EMPTYSTRING) : (((pDatabaseTMTxtCalTable = GetDatabase()->GetTMTxtCalTables()->GetAt(nCalTableRefs.GetAt(0)))) ? (LPCTSTR)pDatabaseTMTxtCalTable->GetName() : EMPTYSTRING)) : EMPTYSTRING);
					m_pLayoutValues.Add(pTMParameter);
					continue;
				}
				break;
			}
		}
		if ((pParameter = m_cLayout.GetAt(nParameter)))
		{
			if ((pTMParameter = m_pLayoutValues.GetAt(m_pLayoutValues.Find(pParameter->GetName()))))
			{
				if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(pParameter->GetRef())))
				{
					pTMParameter->SetAttributes((pDatabaseTMParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_FLOATINGPOINT | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_DECIMAL | TMPARAMETER_RADIX_HEXADECIMAL)) | (pParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_FLOATINGPOINT | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_DECIMAL | TMPARAMETER_RADIX_HEXADECIMAL)));
					pTMParameter->SetPastValueSamples((pParameter->GetOccurrence() < 0) ? max(abs(pParameter->GetOccurrence()), pTMParameter->GetPastValueSamples()) : pTMParameter->GetPastValueSamples());
					continue;
				}
			}
		}
	}
	for (nParameter = (nParameter != nParameters) ? (INT)(m_pLayoutValues.GetSize() + 1) : 0, nParameters = (INT)m_pLayoutValues.GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pTMParameter = m_pLayoutValues.GetAt(nParameter)) && m_cLayout.Find(pTMParameter->GetTag()) < 0)
		{
			m_pLayoutValues.RemoveAt(nParameter);
			delete pTMParameter;
			nParameters--;
			nParameter--;
		}
	}
	for (SetItemsFont(&m_wndContentCtrl.m_cFont, !(m_bLayoutFont = TRUE)), SetLabelsFont(&m_cLayoutFont[0], FALSE), SetValuesFont(&m_cLayoutFont[0], (m_bLayoutFont = FALSE)); nParameter == nParameters; )
	{
		SetCurText(0);
		Update();
		return TRUE;
	}
	return FALSE;
}

BOOL CANDView::GetLayout(CANDLayout &cLayout) CONST
{
	CUIntArray  nColumns;

	return GetLayout(cLayout, nColumns);
}
BOOL CANDView::GetLayout(CANDLayout &cLayout, CUIntArray &nColumns) CONST
{
	CUIntArray  nWidths;

	return GetLayout(cLayout, nColumns, nWidths);
}
BOOL CANDView::GetLayout(CANDLayout &cLayout, CUIntArray &nColumns, CUIntArray &nWidths) CONST
{
	INT  nIndex;
	INT  nCount;
	CStringArray  szColumns;
	CTextViewLock  cLock(this);

	for (nIndex = 0, nCount = (cLayout.Copy(&m_cLayout) && GetColumns(szColumns, nWidths)) ? (INT)szColumns.GetSize() : -1, nColumns.RemoveAll(); nIndex < nCount; nIndex++)
	{
		nColumns.Add(LookupColumnName(szColumns.GetAt(nIndex)));
		continue;
	}
	return((nIndex == nCount) ? TRUE : FALSE);
}

BOOL CANDView::SetTitleFont(CFont *pFont, BOOL bDefault)
{
	LOGFONT  lfFont;

	return((pFont->GetLogFont(&lfFont) > 0) ? SetTitleFont(&lfFont, bDefault) : FALSE);
}
BOOL CANDView::SetTitleFont(CONST LOGFONT *plfFont, BOOL bDefault)
{
	BOOL  bRestore;
	CTextViewLock  cLock(this);

	for (bRestore = CanReduceFonts(TRUE), CopyMemory(&m_lfLayoutDefault[0], plfFont, (bDefault) ? sizeof(LOGFONT) : 0); CTextView::SetTitleFont(plfFont); )
	{
		if (bDefault  &&  bRestore) ReduceFonts(bRestore);
		return TRUE;
	}
	return FALSE;
}

BOOL CANDView::GetTitleFont(CFont *pFont, BOOL bDefault) CONST
{
	CTextViewLock  cLock(this);

	return(((bDefault  &&  lstrlen(m_lfLayoutDefault[0].lfFaceName) > 0 && pFont->CreateFontIndirect(&m_lfLayoutDefault[0])) || CTextView::GetTitleFont(pFont)) ? TRUE : FALSE);
}
BOOL CANDView::GetTitleFont(LOGFONT *plfFont, BOOL bDefault) CONST
{
	CTextViewLock  cLock(this);

	CopyMemory(plfFont, &m_lfLayoutDefault[0], (bDefault) ? sizeof(LOGFONT) : 0);
	return(((bDefault  &&  lstrlen(m_lfLayoutDefault[0].lfFaceName) > 0) || CTextView::GetTitleFont(plfFont)) ? TRUE : FALSE);
}

BOOL CANDView::SetLabelsFont(CFont *pFont, BOOL bDefault)
{
	LOGFONT  lfFont;
	CTextViewLock  cLock(this);

	if (!pFont)
	{
		if (GetLabelsFont(&lfFont, bDefault))
		{
			SetLabelsFont(&lfFont, bDefault);
			return TRUE;
		}
		if (GetItemsFont(&lfFont, bDefault))
		{
			lfFont.lfWeight = FW_BOLD;
			lfFont.lfWidth = 0;
			return SetLabelsFont(&lfFont, bDefault);
		}
		return FALSE;
	}
	return((pFont->GetLogFont(&lfFont)) ? SetLabelsFont(&lfFont, bDefault) : FALSE);
}
BOOL CANDView::SetLabelsFont(CONST LOGFONT *plfFont, BOOL bDefault)
{
	INT  nIndex;
	INT  nParameter;
	INT  nParameters;
	BOOL  bRestore;
	CANDLayoutParameter  *pParameter;
	CTextViewLock  cLock(this);

	for (nParameter = 0, nParameters = (INT)m_cLayout.GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pParameter = m_cLayout.GetAt(nParameter)) != (CANDLayoutParameter *)NULL  &&  pParameter->IsLabel())
		{
			for (; ConvertColumnToIndex(pParameter->GetColumn(), AND_TITLEITEM_LABELS, nIndex); )
			{
				SetColumnFont(pParameter->GetRow(), nIndex, plfFont);
				break;
			}
		}
	}
	for (bRestore = CanReduceFonts(TRUE); (!m_cLayoutFont[0].GetSafeHandle() || m_cLayoutFont[0].DeleteObject()) && m_cLayoutFont[0].CreateFontIndirect(plfFont); )
	{
		for (CopyMemory(&m_lfLayoutDefault[1], plfFont, (bDefault) ? sizeof(LOGFONT) : 0); bDefault && bRestore; )
		{
			ReduceFonts(bRestore);
			break;
		}
		RecalcContent();
		return TRUE;
	}
	return FALSE;
}

BOOL CANDView::GetLabelsFont(CFont *pFont, BOOL bDefault) CONST
{
	LOGFONT  lfFont;
	CTextViewLock  cLock(this);

	return((GetLabelsFont(&lfFont, bDefault)) ? pFont->CreateFontIndirect(&lfFont) : FALSE);
}
BOOL CANDView::GetLabelsFont(LOGFONT *plfFont, BOOL bDefault) CONST
{
	CTextViewLock  cLock(this);

	if (((!bDefault || !lstrlen(m_lfLayoutDefault[1].lfFaceName)) && m_cLayoutFont[0].GetSafeHandle() && m_cLayoutFont[0].GetObject(sizeof(LOGFONT), plfFont) > 0) || (bDefault  &&  lstrlen(m_lfLayoutDefault[1].lfFaceName) > 0))
	{
		CopyMemory(plfFont, &m_lfLayoutDefault[1], (bDefault  &&  lstrlen(m_lfLayoutDefault[1].lfFaceName) > 0) ? sizeof(LOGFONT) : 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CANDView::SetItemsFont(CFont *pFont, BOOL bDefault)
{
	LOGFONT  lfFont;

	return((pFont->GetLogFont(&lfFont) > 0) ? SetItemsFont(&lfFont, bDefault) : FALSE);
}
BOOL CANDView::SetItemsFont(CONST LOGFONT *plfFont, BOOL bDefault)
{
	INT  nColumn;
	INT  nColumns;
	BOOL  bRestore;
	CStringArray  szColumns;
	CTextViewLock  cLock(this);

	for (nColumn = 0, nColumns = (GetColumns(szColumns)) ? (INT)szColumns.GetSize() : 0; nColumn < nColumns; nColumn++)
	{
		if (LookupColumnName(szColumns.GetAt(nColumn)) != AND_TITLEITEM_VALUE  &&  LookupColumnName(szColumns.GetAt(nColumn)) != AND_TITLEITEM_EXPECTEDVALUES)
		{
			SetColumnFont(nColumn, plfFont);
			continue;
		}
	}
	for (bRestore = CanReduceFonts(TRUE), CopyMemory(&m_lfLayoutDefault[2], plfFont, (bDefault) ? sizeof(LOGFONT) : 0); CTextView::SetTextFont(plfFont); )
	{
		if (bDefault  &&  bRestore) ReduceFonts(bRestore);
		return TRUE;
	}
	return FALSE;
}

BOOL CANDView::GetItemsFont(CFont *pFont, BOOL bDefault) CONST
{
	CTextViewLock  cLock(this);

	return(((bDefault  &&  lstrlen(m_lfLayoutDefault[2].lfFaceName) > 0 && pFont->CreateFontIndirect(&m_lfLayoutDefault[2])) || CTextView::GetTextFont(pFont)) ? TRUE : FALSE);
}
BOOL CANDView::GetItemsFont(LOGFONT *plfFont, BOOL bDefault) CONST
{
	CTextViewLock  cLock(this);

	CopyMemory(plfFont, &m_lfLayoutDefault[2], (bDefault) ? sizeof(LOGFONT) : 0);
	return(((bDefault  &&  lstrlen(m_lfLayoutDefault[2].lfFaceName) > 0) || CTextView::GetTextFont(plfFont)) ? TRUE : FALSE);
}

BOOL CANDView::SetValuesFont(CFont *pFont, BOOL bDefault)
{
	LOGFONT  lfFont;
	CTextViewLock  cLock(this);

	if (!pFont)
	{
		if (GetValuesFont(&lfFont, bDefault))
		{
			SetValuesFont(&lfFont, bDefault);
			return TRUE;
		}
		if (GetItemsFont(&lfFont, bDefault))
		{
			lfFont.lfWeight = FW_BOLD;
			lfFont.lfWidth = 0;
			return SetValuesFont(&lfFont, bDefault);
		}
		return FALSE;
	}
	return((pFont->GetLogFont(&lfFont)) ? SetValuesFont(&lfFont, bDefault) : FALSE);
}
BOOL CANDView::SetValuesFont(CONST LOGFONT *plfFont, BOOL bDefault)
{
	INT  nColumn;
	INT  nColumns;
	BOOL  bRestore;
	CStringArray  szColumns;
	CTextViewLock  cLock(this);

	for (nColumn = 0, nColumns = (GetColumns(szColumns)) ? (INT)szColumns.GetSize() : 0; nColumn < nColumns; nColumn++)
	{
		if (LookupColumnName(szColumns.GetAt(nColumn)) == AND_TITLEITEM_VALUE || LookupColumnName(szColumns.GetAt(nColumn)) == AND_TITLEITEM_EXPECTEDVALUES)
		{
			SetColumnFont(nColumn, plfFont);
			continue;
		}
	}
	for (bRestore = CanReduceFonts(TRUE); (!m_cLayoutFont[1].GetSafeHandle() || m_cLayoutFont[1].DeleteObject()) && m_cLayoutFont[1].CreateFontIndirect(plfFont); )
	{
		for (CopyMemory(&m_lfLayoutDefault[3], plfFont, (bDefault) ? sizeof(LOGFONT) : 0); bDefault && bRestore; )
		{
			ReduceFonts(bRestore);
			break;
		}
		RecalcContent();
		return TRUE;
	}
	return FALSE;
}

BOOL CANDView::GetValuesFont(CFont *pFont, BOOL bDefault) CONST
{
	LOGFONT  lfFont;
	CTextViewLock  cLock(this);

	return((GetValuesFont(&lfFont, bDefault)) ? pFont->CreateFontIndirect(&lfFont) : FALSE);
}
BOOL CANDView::GetValuesFont(LOGFONT *plfFont, BOOL bDefault) CONST
{
	CTextViewLock  cLock(this);

	if (((!bDefault || !lstrlen(m_lfLayoutDefault[3].lfFaceName)) && m_cLayoutFont[1].GetSafeHandle() && m_cLayoutFont[1].GetObject(sizeof(LOGFONT), plfFont) > 0) || (bDefault  &&  lstrlen(m_lfLayoutDefault[3].lfFaceName) > 0))
	{
		CopyMemory(plfFont, &m_lfLayoutDefault[3], (bDefault  &&  lstrlen(m_lfLayoutDefault[3].lfFaceName) > 0) ? sizeof(LOGFONT) : 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CANDView::SetOolColors(CONST CUIntArray &nColors)
{
	INT  nIndex;
	INT  nCount;
	CTextViewLock  cLock(this);

	for (nIndex = 0, nCount = (INT)nColors.GetSize(); nIndex < nCount; nIndex++)
	{
		m_nLayoutColors.SetAtGrow(nIndex, nColors.GetAt(nIndex));
		continue;
	}
	if (nColors.GetSize() > 0)
	{
		Update();
		return TRUE;
	}
	return FALSE;
}

BOOL CANDView::GetOolColors(CUIntArray &nColors) CONST
{
	CTextViewLock  cLock(this);

	nColors.Copy(m_nLayoutColors);
	return(nColors.GetSize() > 0);
}

BOOL CANDView::EnableInvalidDataMode(BOOL bEnable)
{
	m_bInvalidDataMode = bEnable;
	return TRUE;
}

BOOL CANDView::IsInvalidDataModeEnabled() CONST
{
	return m_bInvalidDataMode;
}

BOOL CANDView::EnableBadDataMode(BOOL bEnable)
{
	m_bBadDataMode = bEnable;
	return TRUE;
}

BOOL CANDView::IsBadDataModeEnabled() CONST
{
	return m_bBadDataMode;
}

BOOL CANDView::EnableToolTipMode(BOOL bEnable)
{
	m_bToolTipMode = bEnable;
	return TRUE;
}

BOOL CANDView::IsToolTipModeEnabled() CONST
{
	return m_bToolTipMode;
}

BOOL CANDView::Initialize(CTMEnvironment *pTMEnvironment)
{
	CTextViewLock  cLock(this);

	return pTMEnvironment->Initialize(m_pLayoutValues, IsBadDataModeEnabled());
}
BOOL CANDView::Initialize(CString &szTag, CTimeTag &tTag)
{
	INT  nMode;
	INT  nParameter;
	INT  nParameters;
	CTMParameter  *pTMParameter;
	CTextViewLock  cLock(this);

	for (nParameter = 0, nParameters = (((nMode = GetParent()->GetMode()) == DISPLAY_MODE_REALTIME && InitializeTMData(m_pLayoutValues, IsBadDataModeEnabled())) || (nMode == DISPLAY_MODE_HISTORY && GetParent()->InitializeTMData(m_pLayoutValues, IsBadDataModeEnabled()))) ? (INT)m_pLayoutValues.GetSize() : -1, szTag.Empty(), tTag = 0, m_bLayoutValues.RemoveAll(), m_nLayoutStatus.RemoveAll(), m_szLayoutTables.RemoveAll(), m_bLayoutValues.SetSize(m_cLayout.GetSize()), m_nLayoutStatus.SetSize(m_cLayout.GetSize()), m_szLayoutTables.SetSize(m_cLayout.GetSize()); nParameter < nParameters; nParameter++)
	{
		if ((pTMParameter = m_pLayoutValues.GetAt(nParameter)) && pTMParameter->IsInitialized() && tTag < pTMParameter->GetLastUpdateTime())
		{
			szTag = pTMParameter->GetLastUpdateTMUnit();
			tTag = pTMParameter->GetLastUpdateTime();
		}
	}
	if (nParameter == nParameters)
	{
		Update();
		return TRUE;
	}
	return FALSE;
}

BOOL CANDView::Update(CTMEnvironment *pTMEnvironment)
{
	INT  nRow;
	INT  nIndex;
	INT  nCount;
	INT  nParameter;
	INT  nParameters;
	UINT  nStatus;
	BOOL  bOutSet;
	BOOL  bUpdate[2];
	CPoint  ptToolTip;
	CString  szText;
	CString  szTitle;
	CString  szValue;
	CString  szCalTable;
	ULONGLONG  nValue;
	CUIntArray  nColumns;
	CStringArray  szColumns;
	CTMParameter  *pTMParameter;
	CANDLayoutParameter  *pParameter;
	CTextViewAttribute  *pAttribute;
	CTextViewLock  cLock(this);

	if (!pTMEnvironment)
	{
		nParameters = (INT)m_cLayout.GetSize();
		m_bLayoutValues.SetSize(0);
		m_nLayoutStatus.SetSize(0);
		m_szLayoutTables.SetSize(0);
		m_bLayoutValues.SetSize(nParameters);
		m_nLayoutStatus.SetSize(nParameters);
		m_szLayoutTables.SetSize(nParameters);
	}
	else
	{
		bUpdate[0] = m_pLayoutValues.Update(GetDatabase(), pTMEnvironment->GetTMUnit(), pTMEnvironment->GetTMParameters(), IsBadDataModeEnabled());
		nParameters = (bUpdate[0]) ? (INT)m_cLayout.GetSize() : -1;
	}
	for (nParameter = 0, bUpdate[0] = bUpdate[1] = FALSE; nParameter < nParameters; nParameter++, bUpdate[0] = FALSE)
	{
		if ((pTMParameter = ((pParameter = m_cLayout.GetAt(nParameter)) && pParameter->GetDigits() >= 0) ? m_pLayoutValues.GetAt(m_pLayoutValues.Find(pParameter->GetName())) : (CTMParameter *)NULL))
		{
			if (nParameter < m_bLayoutValues.GetSize() && (!m_bLayoutValues.GetAt(nParameter) || ((pTMEnvironment->GetTMUnit()->IsValid() && ((pTMParameter->GetLastUpdateTMUnit() == pTMEnvironment->GetTMUnit()->GetTag() && pTMParameter->GetLastUpdateTime() == pTMEnvironment->GetTMUnit()->GetTimeTag()) || (pTMParameter->GetRawValue(pParameter->GetOccurrence(), nValue, nStatus, szCalTable) && (m_nLayoutStatus.GetAt(nParameter) != nStatus || m_szLayoutTables.GetAt(nParameter) != szCalTable)))) || !pTMEnvironment->GetTMUnit()->IsValid())))
			{
				if (ConvertColumnToIndex(pParameter->GetColumn(), AND_TITLEITEM_VALUE, nIndex))
				{
					szColumns.Add((pTMParameter->GetRawValue(pParameter->GetOccurrence(), nValue, nStatus) && pTMParameter->GetValueAsText(GetDatabase(), pParameter->GetOccurrence(), pParameter->GetAttributes(), (pParameter->GetDigits() != 0) ? pParameter->GetDigits() : -1, szValue, bOutSet, FALSE) && (IsBadDataModeEnabled() || (nStatus & TMPARAMETER_STATUS_GOOD))) ? (((nStatus & TMPARAMETER_STATUS_VALID) || IsInvalidDataModeEnabled()) ? ((bOutSet) ? ((pTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) ? (LPCTSTR)(szValue + GetDatabase()->GetTMNumCalTablePointOutsideText()) : (LPCTSTR)((pTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS) ? (LPCTSTR)(szValue + GetDatabase()->GetTMTxtCalTablePointOutsideText()) : (LPCTSTR)szValue)) : (LPCTSTR)szValue) : EMPTYSTRING) : EMPTYSTRING);
					nColumns.Add(nIndex);
				}
				bUpdate[0] = TRUE;
				bUpdate[1] = TRUE;
			}
			if (nParameter < m_bLayoutValues.GetSize() && (!m_bLayoutValues.GetAt(nParameter) || ((pTMEnvironment->GetTMUnit()->IsValid() && ((pTMParameter->GetLastChangeTMUnit() == pTMEnvironment->GetTMUnit()->GetTag() && pTMParameter->GetLastChangeTime() == pTMEnvironment->GetTMUnit()->GetTimeTag()) || (pTMParameter->GetRawValue(pParameter->GetOccurrence(), nValue, nStatus, szCalTable) && (m_nLayoutStatus.GetAt(nParameter) != nStatus || m_szLayoutTables.GetAt(nParameter) != szCalTable)))) || !pTMEnvironment->GetTMUnit()->IsValid())))
			{
				if (ConvertColumnToIndex(pParameter->GetColumn(), AND_TITLEITEM_CHANGETMUNIT, nIndex))
				{
					szColumns.Add(((pTMParameter->GetAttributes() & TMPARAMETER_NATURE_CONSTANT) != TMPARAMETER_NATURE_CONSTANT  &&  pTMParameter->GetRawValue(pParameter->GetOccurrence(), nValue, nStatus)) ? (((nStatus & TMPARAMETER_STATUS_VALID) || IsInvalidDataModeEnabled()) ? (LPCTSTR)pTMParameter->GetLastChangeTMUnit() : EMPTYSTRING) : EMPTYSTRING);
					nColumns.Add(nIndex);
				}
				if (ConvertColumnToIndex(pParameter->GetColumn(), AND_TITLEITEM_CHANGETIME, nIndex))
				{
					szColumns.Add((pTMParameter->IsInitialized() && (pTMParameter->GetAttributes() & TMPARAMETER_NATURE_CONSTANT) != TMPARAMETER_NATURE_CONSTANT  &&  pTMParameter->GetRawValue(pParameter->GetOccurrence(), nValue, nStatus)) ? (((nStatus & TMPARAMETER_STATUS_VALID) || IsInvalidDataModeEnabled()) ? (LPCTSTR)pTMParameter->GetLastChangeTime().FormatGmt() : EMPTYSTRING) : EMPTYSTRING);
					nColumns.Add(nIndex);
				}
			}
			if (nParameter < m_bLayoutValues.GetSize() && (!m_bLayoutValues.GetAt(nParameter) || ((pTMEnvironment->GetTMUnit()->IsValid() && ((pTMParameter->GetLastUpdateTMUnit() == pTMEnvironment->GetTMUnit()->GetTag() && pTMParameter->GetLastUpdateTime() == pTMEnvironment->GetTMUnit()->GetTimeTag()) || (pTMParameter->GetRawValue(pParameter->GetOccurrence(), nValue, nStatus, szCalTable) && (m_nLayoutStatus.GetAt(nParameter) != nStatus || m_szLayoutTables.GetAt(nParameter) != szCalTable)))) || !pTMEnvironment->GetTMUnit()->IsValid())))
			{
				if (ConvertColumnToIndex(pParameter->GetColumn(), AND_TITLEITEM_UPDATETMUNIT, nIndex))
				{
					szColumns.Add(((pTMParameter->GetAttributes() & TMPARAMETER_NATURE_CONSTANT) != TMPARAMETER_NATURE_CONSTANT  &&  pTMParameter->GetRawValue(pParameter->GetOccurrence(), nValue, nStatus)) ? (((nStatus & TMPARAMETER_STATUS_VALID) || IsInvalidDataModeEnabled()) ? (LPCTSTR)pTMParameter->GetLastUpdateTMUnit() : EMPTYSTRING) : EMPTYSTRING);
					nColumns.Add(nIndex);
				}
				if (ConvertColumnToIndex(pParameter->GetColumn(), AND_TITLEITEM_UPDATETIME, nIndex))
				{
					szColumns.Add((pTMParameter->IsInitialized() && (pTMParameter->GetAttributes() & TMPARAMETER_NATURE_CONSTANT) != TMPARAMETER_NATURE_CONSTANT  &&  pTMParameter->GetRawValue(pParameter->GetOccurrence(), nValue, nStatus)) ? (((nStatus & TMPARAMETER_STATUS_VALID) || IsInvalidDataModeEnabled()) ? (LPCTSTR)pTMParameter->GetLastUpdateTime().FormatGmt() : EMPTYSTRING) : EMPTYSTRING);
					nColumns.Add(nIndex);
				}
			}
			for (nIndex = 0, nCount = ((nRow = ((nRow = pParameter->GetRow()) >= 0) ? nRow : nParameter) < (INT)m_wndContentCtrl.m_szContentText.GetSize() && nColumns.GetSize() == szColumns.GetSize()) ? (INT)nColumns.GetSize() : 0; nIndex < nCount; nIndex++)
			{
				if ((pAttribute = m_wndContentCtrl.m_pContentTextAttributes.GetAt(nRow)) && m_nLayoutColumns.GetAt(nColumns.GetAt(nIndex)) == AND_TITLEITEM_VALUE) pAttribute->SetColumnColor(nColumns.GetAt(nIndex), LookupColumnColor(m_nLayoutColumns.GetAt(nColumns.GetAt(nIndex)), (pTMParameter->GetRawValue(pParameter->GetOccurrence(), nValue, nStatus)) ? nStatus : 0));
				SetText(nRow, nColumns.GetAt(nIndex), szColumns.GetAt(nIndex));
			}
			if (bUpdate[0])
			{
				m_bLayoutValues.SetAt(nParameter, (pTMParameter->GetValueCount() > pParameter->GetOccurrence()) ? TRUE : FALSE);
				m_nLayoutStatus.SetAt(nParameter, (pTMParameter->GetRawValue(pParameter->GetOccurrence(), nValue, nStatus, szCalTable)) ? nStatus : TMPARAMETER_STATUS_NONE);
				m_szLayoutTables.SetAt(nParameter, (m_nLayoutStatus.GetAt(nParameter) != TMPARAMETER_STATUS_NONE) ? (LPCTSTR)szCalTable : EMPTYSTRING);
			}
			szColumns.RemoveAll();
			nColumns.RemoveAll();
		}
	}
	if (m_wndToolTip.IsVisibleAtPoint(ptToolTip))
	{
		if ((pParameter = (FindTextFromPoint(ptToolTip, nRow, nIndex, FALSE)) ? FindParameter(nRow, nIndex) : (CANDLayoutParameter *)NULL) && !pParameter->IsLabel())
		{
			for (szTitle = ConstructToolTipTitle(pParameter, LookupColumnName(m_wndHeaderCtrl.m_szColumnsText.GetAt(nIndex))), szText = ConstructToolTipText(pParameter, LookupColumnName(m_wndHeaderCtrl.m_szColumnsText.GetAt(nIndex))); !szTitle.IsEmpty() || !szText.IsEmpty(); )
			{
				m_wndToolTip.Update(szTitle, szText);
				break;
			}
		}
	}
	return((nParameter == nParameters) ? bUpdate[1] : FALSE);
}

VOID CANDView::Reset(CTMEnvironment *pTMEnvironment)
{
	CTextViewLock  cLock(this);

	m_bLayoutValues.RemoveAll();
	m_nLayoutStatus.RemoveAll();
	m_szLayoutTables.RemoveAll();
	m_bLayoutValues.SetSize(m_cLayout.GetSize());
	m_nLayoutStatus.SetSize(m_cLayout.GetSize());
	m_szLayoutTables.SetSize(m_cLayout.GetSize());
	m_pLayoutValues.Reset();
	Update();
}

BOOL CANDView::GetParameterInfo(LPCTSTR pszTag, CTMParameter *pTMParameter) CONST
{
	INT  nIndex;
	CTextViewLock  cLock(this);

	return(((nIndex = m_pLayoutValues.Find(pszTag)) >= 0) ? pTMParameter->Copy(m_pLayoutValues.GetAt(nIndex)) : FALSE);
}

BOOL CANDView::HasParameters() CONST
{
	CTextViewLock  cLock(this);

	return((m_cLayout.GetSize() > 0) ? TRUE : FALSE);
}

VOID CANDView::ReduceFonts(BOOL bRestore)
{
	INT  nColumn;
	INT  nColumns;
	INT  nParameter;
	INT  nParameters;
	INT  nColumnGroup;
	BOOL  bSuccess;
	CFont  *pFont;
	CFont  cFont[4];
	LOGFONT  lfFont[4];
	CUIntArray  nWidths;
	CStringArray  szColumns;
	CANDLayoutParameter  *pParameter;
	CTextViewLock  cLock(this);

	if (!bRestore)
	{
		for (nParameter = 0, nParameters = (INT)m_cLayout.GetSize(), nColumnGroup = 0; nParameter < nParameters; nParameter++)
		{
			if ((pParameter = m_cLayout.GetAt(nParameter)) != (CANDLayoutParameter *)NULL)
			{
				nColumnGroup = max(max(pParameter->GetColumn(), 0) + 1, nColumnGroup);
				continue;
			}
		}
		for (nColumn = 0, nColumns = (INT)m_wndHeaderCtrl.m_szColumnsText.GetSize(); nColumn < nColumns; nColumn++)
		{
			if (LookupColumnName(m_wndHeaderCtrl.m_szColumnsText.GetAt(nColumn)) == AND_TITLEITEM_ID)
			{
				if (nColumnGroup > 0)
				{
					nColumnGroup--;
					continue;
				}
				for (m_wndHeaderCtrl.m_szColumnsText.SetSize(nColumn), m_wndHeaderCtrl.m_nColumnsWidth.SetSize(nColumn), m_wndHeaderCtrl.m_nColumnsFormat.SetSize(nColumn); nColumn < m_wndContentCtrl.m_nColumnsFormat.GetSize(); )
				{
					m_wndContentCtrl.m_nColumnsFormat.SetSize(nColumn);
					m_wndContentCtrl.m_bColumnsFormat.SetSize(nColumn);
					break;
				}
				if (nColumn < m_wndContentCtrl.m_nColumnsColor.GetSize())
				{
					m_wndContentCtrl.m_nColumnsColor.SetSize(nColumn);
					m_wndContentCtrl.m_bColumnsColor.SetSize(nColumn);
				}
				while (nColumn < m_wndContentCtrl.m_pColumnsFont.GetSize())
				{
					if ((pFont = (CFont *)m_wndContentCtrl.m_pColumnsFont.GetAt(m_wndContentCtrl.m_pColumnsFont.GetUpperBound()))) delete pFont;
					m_wndContentCtrl.m_pColumnsFont.RemoveAt(m_wndContentCtrl.m_pColumnsFont.GetUpperBound());
				}
				while (nColumn < m_wndHeaderCtrl.GetItemCount())
				{
					m_wndHeaderCtrl.DeleteItem(m_wndHeaderCtrl.GetItemCount() - 1);
					continue;
				}
				break;
			}
		}
		if (m_wndHeaderCtrl.m_cFont.GetLogFont(&lfFont[0]) > 0 && m_cLayoutFont[0].GetLogFont(&lfFont[1]) > 0 && m_wndContentCtrl.m_cFont.GetLogFont(&lfFont[2]) > 0 && m_cLayoutFont[1].GetLogFont(&lfFont[3]) > 0)
		{
			for (lfFont[0].lfHeight = (9 * lfFont[0].lfHeight) / 10, lfFont[1].lfHeight = (9 * lfFont[1].lfHeight) / 10, lfFont[2].lfHeight = (9 * lfFont[2].lfHeight) / 10, lfFont[3].lfHeight = (9 * lfFont[3].lfHeight) / 10, lfFont[0].lfWidth = lfFont[1].lfWidth = lfFont[2].lfWidth = lfFont[3].lfWidth = 0, lfFont[0].lfOutPrecision = lfFont[1].lfOutPrecision = lfFont[2].lfOutPrecision = lfFont[3].lfOutPrecision = OUT_TT_ONLY_PRECIS; bSuccess = cFont[0].CreateFontIndirect(&lfFont[0]) && cFont[1].CreateFontIndirect(&lfFont[1]) && cFont[2].CreateFontIndirect(&lfFont[2]) && cFont[3].CreateFontIndirect(&lfFont[3]); )
			{
				bSuccess &= m_wndHeaderCtrl.m_cFont.DeleteObject() && m_wndHeaderCtrl.m_cFont.Attach(cFont[0].Detach());
				bSuccess &= m_wndContentCtrl.m_cFont.DeleteObject() && m_wndContentCtrl.m_cFont.Attach(cFont[2].Detach());
				bSuccess &= m_cLayoutFont[0].DeleteObject() && m_cLayoutFont[0].Attach(cFont[1].Detach());
				bSuccess &= m_cLayoutFont[1].DeleteObject() && m_cLayoutFont[1].Attach(cFont[3].Detach());
				break;
			}
			if (bSuccess)
			{
				for (SetTitleFont(&m_wndHeaderCtrl.m_cFont, !(m_bLayoutFont = TRUE)), SetLabelsFont(&m_cLayoutFont[0], FALSE), SetItemsFont(&m_wndContentCtrl.m_cFont, FALSE), SetValuesFont(&m_cLayoutFont[1], FALSE), CalcColumnsWidth(nWidths); GetColumns(szColumns); )
				{
					SetColumns(szColumns, nWidths);
					break;
				}
				m_bLayoutFont = FALSE;
				RecalcContent();
			}
		}
		return;
	}
	for (SetTitleFont(&m_lfLayoutDefault[0], !(m_bLayoutFont = TRUE)), SetLabelsFont(&m_lfLayoutDefault[1], FALSE), SetItemsFont(&m_lfLayoutDefault[2], FALSE), SetValuesFont(&m_lfLayoutDefault[3], FALSE), CalcColumnsWidth(nWidths); GetColumns(szColumns); )
	{
		SetColumns(szColumns, nWidths);
		break;
	}
	m_bLayoutFont = FALSE;
	RecalcContent();
}

BOOL CANDView::CanReduceFonts(BOOL bRestore) CONST
{
	LOGFONT  lfFont[4];
	CTextViewLock  cLock(this);

	return((GetTitleFont(&lfFont[0], FALSE) && GetLabelsFont(&lfFont[1], FALSE) && GetItemsFont(&lfFont[2], FALSE) && GetValuesFont(&lfFont[3], FALSE)) ? ((!bRestore  &&  abs(lfFont[0].lfHeight) > 10 && abs(lfFont[1].lfHeight) > 10 && abs(lfFont[2].lfHeight) > 10 && abs(lfFont[3].lfHeight) > 10) || (bRestore && (memcmp(&m_lfLayoutDefault[0], &lfFont[0], sizeof(LOGFONT)) || memcmp(&m_lfLayoutDefault[1], &lfFont[1], sizeof(LOGFONT)) || memcmp(&m_lfLayoutDefault[2], &lfFont[2], sizeof(LOGFONT)) || memcmp(&m_lfLayoutDefault[3], &lfFont[3], sizeof(LOGFONT))))) : FALSE);
}

BOOL CANDView::GetPrintProperties(CANDLayout &cLayout, CStringArray &szColumns, CStringArray &szContents, CTMParameters &pValues, CUIntArray &nOOLColors, LOGFONT *pTitleFont, LOGFONT *pLabelsFont, CPtrArray &pItemsFonts) CONST
{
	INT  nColumn;
	INT  nColumns;
	LOGFONT  *plfFont;
	CTextViewAttributes  pAttributes;
	CTextViewLock  cLock(this);

	for (nColumn = 0, nColumns = (GetLayout(cLayout) && GetColumns(szColumns) && GetContent(szContents, pAttributes) && GetTitleFont(pTitleFont) && GetLabelsFont(pLabelsFont) && GetOolColors(nOOLColors) && pValues.Copy(&m_pLayoutValues)) ? (INT)szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
	{
		if ((plfFont = (LOGFONT *)GlobalAlloc(GPTR, sizeof(LOGFONT))))
		{
			if (GetColumnFont(nColumn, plfFont))
			{
				pItemsFonts.Add(plfFont);
				continue;
			}
			GlobalFree(plfFont);
		}
		while (--nColumn >= 0) GlobalFree(pItemsFonts.GetAt(nColumn));
		pItemsFonts.RemoveAll();
		break;
	}
	return((nColumn == nColumns) ? TRUE : FALSE);
}

VOID CANDView::DrawContent(CDC *pDC)
{
	if (!m_bLayoutFont)
	{
		CTextView::DrawContent(pDC);
		return;
	}
}

CANDWnd *CANDView::GetParent() CONST
{
	return((CANDWnd *)CTextView::GetParent());
}

CString CANDView::LookupColumnName(UINT nColumn) CONST
{
	if (nColumn == AND_TITLEITEM_ID) return STRING(IDS_AND_TITLEITEM_ID);
	if (nColumn == AND_TITLEITEM_DESCRIPTION) return STRING(IDS_AND_TITLEITEM_DESCRIPTION);
	if (nColumn == AND_TITLEITEM_VALUE) return STRING(IDS_AND_TITLEITEM_VALUE);
	if (nColumn == AND_TITLEITEM_UNIT) return STRING(IDS_AND_TITLEITEM_UNIT);
	if (nColumn == AND_TITLEITEM_CHANGETMUNIT) return STRING(IDS_AND_TITLEITEM_CHANGETMUNIT);
	if (nColumn == AND_TITLEITEM_CHANGETIME) return STRING(IDS_AND_TITLEITEM_CHANGETIME);
	if (nColumn == AND_TITLEITEM_UPDATETMUNIT) return STRING(IDS_AND_TITLEITEM_UPDATETMUNIT);
	if (nColumn == AND_TITLEITEM_UPDATETIME) return STRING(IDS_AND_TITLEITEM_UPDATETIME);
	if (nColumn == AND_TITLEITEM_EXPECTEDVALUES) return STRING(IDS_AND_TITLEITEM_EXPECTEDVALUES);
	return EMPTYSTRING;
}
UINT CANDView::LookupColumnName(LPCTSTR pszColumn) CONST
{
	if (!lstrcmp(pszColumn, STRING(IDS_AND_TITLEITEM_ID))) return AND_TITLEITEM_ID;
	if (!lstrcmp(pszColumn, STRING(IDS_AND_TITLEITEM_DESCRIPTION))) return AND_TITLEITEM_DESCRIPTION;
	if (!lstrcmp(pszColumn, STRING(IDS_AND_TITLEITEM_VALUE))) return AND_TITLEITEM_VALUE;
	if (!lstrcmp(pszColumn, STRING(IDS_AND_TITLEITEM_UNIT))) return AND_TITLEITEM_UNIT;
	if (!lstrcmp(pszColumn, STRING(IDS_AND_TITLEITEM_CHANGETMUNIT))) return AND_TITLEITEM_CHANGETMUNIT;
	if (!lstrcmp(pszColumn, STRING(IDS_AND_TITLEITEM_CHANGETIME))) return AND_TITLEITEM_CHANGETIME;
	if (!lstrcmp(pszColumn, STRING(IDS_AND_TITLEITEM_UPDATETMUNIT))) return AND_TITLEITEM_UPDATETMUNIT;
	if (!lstrcmp(pszColumn, STRING(IDS_AND_TITLEITEM_UPDATETIME))) return AND_TITLEITEM_UPDATETIME;
	if (!lstrcmp(pszColumn, STRING(IDS_AND_TITLEITEM_EXPECTEDVALUES))) return AND_TITLEITEM_EXPECTEDVALUES;
	return 0;
}

INT CANDView::LookupColumnsName(CONST CUIntArray &nColumns, CStringArray &szColumns) CONST
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

COLORREF CANDView::LookupColumnColor(UINT nColumn, BYTE nStatus) CONST
{
	if (nColumn == AND_TITLEITEM_ID) return GetDatabase()->GetANDIDColumnColor();
	if (nColumn == AND_TITLEITEM_DESCRIPTION) return GetDatabase()->GetANDDescriptionColumnColor();
	if (nColumn == AND_TITLEITEM_VALUE && (nStatus & TMPARAMETER_STATUS_NOLIMIT)) return m_nLayoutColors.GetAt(AND_OOLCOLOR_NOLIMIT);
	if (nColumn == AND_TITLEITEM_VALUE && (nStatus & TMPARAMETER_STATUS_SOFTLIMIT)) return m_nLayoutColors.GetAt(AND_OOLCOLOR_SOFTLIMIT);
	if (nColumn == AND_TITLEITEM_VALUE && (nStatus & TMPARAMETER_STATUS_HARDLIMIT)) return m_nLayoutColors.GetAt(AND_OOLCOLOR_HARDLIMIT);
	if (nColumn == AND_TITLEITEM_VALUE && (nStatus & TMPARAMETER_STATUS_DELTALIMIT)) return m_nLayoutColors.GetAt(AND_OOLCOLOR_DELTALIMIT);
	if (nColumn == AND_TITLEITEM_VALUE && (nStatus & TMPARAMETER_STATUS_CONSISTENCYLIMIT)) return m_nLayoutColors.GetAt(AND_OOLCOLOR_CONSISTENCYLIMIT);
	if (nColumn == AND_TITLEITEM_VALUE) return GetDatabase()->GetANDValueColumnColor();
	if (nColumn == AND_TITLEITEM_UNIT) return GetDatabase()->GetANDUnitColumnColor();
	if (nColumn == AND_TITLEITEM_CHANGETMUNIT) return GetDatabase()->GetANDChangeTMUnitColumnColor();
	if (nColumn == AND_TITLEITEM_CHANGETIME) return GetDatabase()->GetANDChangeTimeColumnColor();
	if (nColumn == AND_TITLEITEM_UPDATETMUNIT) return GetDatabase()->GetANDUpdateTMUnitColumnColor();
	if (nColumn == AND_TITLEITEM_UPDATETIME) return GetDatabase()->GetANDUpdateTimeColumnColor();
	if (nColumn == AND_TITLEITEM_EXPECTEDVALUES) return m_nLayoutColors.GetAt(AND_OOLCOLOR_NOLIMIT);
	return GetSysColor(COLOR_WINDOW);
}

INT CANDView::CalcColumnWidth(LPCTSTR pszColumn)
{
	CDC  *pDC;
	INT  nWidth;
	INT  nDxChar;
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
			if ((nDxChar = (pDC->GetTextMetrics(&tmFont) > 0) ? (4 * tmFont.tmAveCharWidth / 3) : 0) > 0)
			{
				nWidth = (nColumn == AND_TITLEITEM_ID) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetANDIDColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == AND_TITLEITEM_DESCRIPTION) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetANDDescriptionColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == AND_TITLEITEM_VALUE) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetANDValueColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == AND_TITLEITEM_UNIT) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetANDUnitColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == AND_TITLEITEM_CHANGETMUNIT) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetANDChangeTMUnitColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == AND_TITLEITEM_UPDATETMUNIT) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetANDUpdateTMUnitColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == AND_TITLEITEM_CHANGETIME) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetANDChangeTimeColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == AND_TITLEITEM_UPDATETIME) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetANDUpdateTimeColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == AND_TITLEITEM_EXPECTEDVALUES) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetANDExpectedValuesColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
			}
			pDC->SelectObject(pOldFont);
		}
		for (szColumn = pszColumn; nColumn == AND_TITLEITEM_VALUE; )
		{
			szColumn = CString(cStringTools.ConvertIntToString(0).GetAt(0), GetDatabase()->GetANDValueColumnCharWidth());
			break;
		}
		for (; nColumn == AND_TITLEITEM_CHANGETIME || nColumn == AND_TITLEITEM_UPDATETIME; )
		{
			szColumn = CTimeTag().FormatGmt();
			break;
		}
		if (nColumn != AND_TITLEITEM_VALUE  &&  nColumn != AND_TITLEITEM_EXPECTEDVALUES)
		{
			if ((pOldFont = pDC->SelectObject(&m_wndContentCtrl.m_cFont)) != (CFont *)NULL)
			{
				nWidth = max(LOWORD(GetTextIndents()) + pDC->GetTextExtent(szColumn).cx + HIWORD(GetTextIndents()), nWidth);
				pDC->SelectObject(pOldFont);
			}
		}
		if (nColumn == AND_TITLEITEM_VALUE || nColumn == AND_TITLEITEM_EXPECTEDVALUES)
		{
			if ((pOldFont = pDC->SelectObject(&m_cLayoutFont[1])) != (CFont *)NULL)
			{
				nWidth = max(LOWORD(GetTextIndents()) + pDC->GetTextExtent(szColumn).cx + HIWORD(GetTextIndents()), nWidth);
				pDC->SelectObject(pOldFont);
			}
		}
		ReleaseDC(pDC);
		return nWidth;
	}
	return 0;
}
INT CANDView::CalcColumnWidth(UINT nColumn, LPCTSTR pszText, BOOL bLabel)
{
	CDC  *pDC;
	INT  nWidth;
	CFont  *pOldFont;

	if ((pDC = GetDC()))
	{
		if (nColumn == AND_TITLEITEM_LABELS  &&  bLabel)
		{
			if ((pOldFont = pDC->SelectObject(&m_cLayoutFont[0])))
			{
				nWidth = LOWORD(GetTextIndents()) + HIWORD(GetTextIndents()) + pDC->GetTextExtent(pszText).cx;
				pDC->SelectObject(pOldFont);
				ReleaseDC(pDC);
				return nWidth;
			}
		}
		if ((nColumn == AND_TITLEITEM_VALUE || nColumn == AND_TITLEITEM_EXPECTEDVALUES) && !bLabel)
		{
			if ((pOldFont = (CFont *)pDC->SelectObject(&m_cLayoutFont[1])) != (CFont *)NULL)
			{
				nWidth = LOWORD(GetTextIndents()) + HIWORD(GetTextIndents()) + pDC->GetTextExtent(pszText).cx;
				pDC->SelectObject(pOldFont);
				ReleaseDC(pDC);
				return nWidth;
			}
		}
		if ((pOldFont = pDC->SelectObject(&m_wndContentCtrl.m_cFont)))
		{
			nWidth = LOWORD(GetTextIndents()) + HIWORD(GetTextIndents()) + pDC->GetTextExtent(pszText).cx;
			pDC->SelectObject(pOldFont);
			ReleaseDC(pDC);
			return nWidth;
		}
		ReleaseDC(pDC);
	}
	return 0;
}

INT CANDView::CalcColumnsWidth(CONST CUIntArray &nColumns, CUIntArray &nWidths)
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
CSize CANDView::CalcColumnsWidth(CUIntArray &nWidths)
{
	CDC  *pDC;
	INT  nItem;
	INT  nItems;
	INT  nWidth;
	INT  nHeight;
	INT  nColumn;
	INT  nColumns;
	CFont  cFont;
	CFont  *pOldFont;
	CSize  sizeColumn;
	CSize  sizeContent;
	CString  szColumnText;
	CStringArray  szColumns;

	if ((pDC = GetDC()))
	{
		for (nColumn = 0, nColumns = (GetColumns(szColumns)) ? (INT)szColumns.GetSize() : 0, sizeContent.cx = sizeContent.cy = 0, nWidths.RemoveAll(); nColumn < nColumns; nColumn++)
		{
			for (nItem = 0, nItems = GetTextCount(), nWidth = CalcColumnWidth(szColumns.GetAt(nColumn)), nHeight = 0; nItem < nItems; nItem++)
			{
				if ((pOldFont = (GetColumnFont(nItem, nColumn, &cFont)) ? pDC->SelectObject(&cFont) : (CFont *)NULL))
				{
					sizeColumn = (GetText(nItem, nColumn, szColumnText)) ? pDC->GetTextExtent(szColumnText) : CSize(0, 0);
					sizeColumn.cx += 2 * GetSystemMetrics(SM_CXEDGE) + m_wndContentCtrl.m_wTextIndent[0] + m_wndContentCtrl.m_wTextIndent[1];
					sizeColumn.cy += m_wndContentCtrl.m_wTextSpacing[0] + m_wndContentCtrl.m_wTextSpacing[1];
					nWidth = max(sizeColumn.cx, nWidth);
					nHeight = nHeight + sizeColumn.cy;
					pDC->SelectObject(pOldFont);
				}
				cFont.DeleteObject();
			}
			for (sizeContent.cx += nWidth, sizeContent.cy = max(nHeight, sizeContent.cy); !nColumn; )
			{
				nWidths.Add(nWidth);
				break;
			}
			if (nColumn > 0)
			{
				nWidths.Add(nWidths.GetAt(nWidths.GetUpperBound()) + nWidth);
				continue;
			}
		}
		ReleaseDC(pDC);
		return sizeContent;
	}
	return CSize(0, 0);
}

BOOL CANDView::ConvertColumnToIndex(INT nColumnGroup, UINT nColumn, INT &nIndex) CONST
{
	INT  nCount[2];

	for (nIndex = 0, nCount[0] = (INT)m_nLayoutColumns.GetSize(), nCount[1] = -1; nIndex < nCount[0]; nIndex++)
	{
		if (((nCount[1] = (m_nLayoutColumns.GetAt(nIndex) == AND_TITLEITEM_ID || !nIndex) ? (nCount[1] + 1) : nCount[1]) == nColumnGroup || nColumnGroup < 0) && nColumn == m_nLayoutColumns.GetAt(nIndex)) break;
		continue;
	}
	return((nIndex < nCount[0]) ? TRUE : FALSE);
}

BOOL CANDView::ConvertIndexToColumn(INT nIndex, INT &nColumnGroup, UINT &nColumn) CONST
{
	INT  nCount;

	for (nIndex = (nIndex >= 0 && nIndex < m_nLayoutColumns.GetSize()) ? nIndex : -1, nColumn = (nIndex >= 0) ? m_nLayoutColumns.GetAt(nIndex) : -1, nCount = -1; nIndex >= 0; nIndex--)
	{
		nCount = (m_nLayoutColumns.GetAt(nIndex) == AND_TITLEITEM_ID || !nIndex) ? (nCount + 1) : nCount;
		continue;
	}
	if (nColumn != (UINT)-1)
	{
		nColumnGroup = nCount;
		return TRUE;
	}
	return FALSE;
}
BOOL CANDView::ConvertIndexToColumn(INT nIndex, INT &nColumnGroup) CONST
{
	UINT  nColumn;

	return ConvertIndexToColumn(nIndex, nColumnGroup, nColumn);
}

CANDLayoutParameter *CANDView::FindParameter(INT nRow, INT nIndex) CONST
{
	INT  nParameter;
	INT  nParameters;
	INT  nColumnGroup;
	CANDLayoutParameter  *pParameter;

	for (nParameter = 0, nParameters = (nRow < m_wndContentCtrl.m_szContentText.GetSize() && ConvertIndexToColumn(nIndex, nColumnGroup)) ? (INT)m_cLayout.GetSize() : -1, pParameter = (CANDLayoutParameter *)NULL; nParameter < nParameters; nParameter++)
	{
		if ((pParameter = m_cLayout.GetAt(nParameter)) && ((pParameter->GetColumn() < 0 && !nColumnGroup && ((pParameter->GetRow() >= 0 && pParameter->GetRow() == nRow) || (pParameter->GetRow() < 0 && nRow == nParameter))) || (pParameter->GetColumn() == nColumnGroup  &&  pParameter->GetRow() == nRow))) break;
		continue;
	}
	return((nParameter < nParameters) ? pParameter : (CANDLayoutParameter *)NULL);
}

CString CANDView::ConstructToolTipTitle(CONST CANDLayoutParameter *pParameter, UINT nTip) CONST
{
	CString  szTitle;

	switch (nTip)
	{
	case AND_TITLEITEM_ID:
	case AND_TITLEITEM_DESCRIPTION:
	case AND_TITLEITEM_VALUE:
	case AND_TITLEITEM_CHANGETMUNIT:
	case AND_TITLEITEM_CHANGETIME:
	case AND_TITLEITEM_UPDATETMUNIT:
	case AND_TITLEITEM_UPDATETIME:
	{ szTitle.Format(STRING(IDS_AND_TOOLTIP_TITLE), (LPCTSTR)pParameter->GetName());
	break;
	}
	case AND_TITLEITEM_UNIT:
	case AND_TITLEITEM_EXPECTEDVALUES: break;
	}
	return((pParameter->GetDigits() >= 0) ? szTitle : EMPTYSTRING);
}

CString CANDView::ConstructToolTipText(CONST CANDLayoutParameter *pParameter, UINT nTip) CONST
{
	INT  nPos;
	INT  nType;
	INT  nIndex;
	UINT  nStatus;
	BOOL  bOutSet;
	CString  szText;
	CString  szType;
	CString  szWidth;
	CString  szStatus;
	CString  szComment;
	CString  szPosition;
	CString  szCalTable;
	CString  szValue[4];
	CString  szValueChange;
	CString  szValueUpdate;
	CString  szValueChangeTime;
	CString  szValueUpdateTime;
	ULONGLONG  nValue;
	CTMParameter  *pTMParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	switch (nTip)
	{
	case AND_TITLEITEM_ID:
	{ if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(pParameter->GetRef())))
	{
		for (szType.Format(STRING(IDS_AND_TOOLTIP_TYPE), CDatabaseEngine::TranslateParameterTypeCode(pDatabaseTMParameter->GetAttributes(), FALSE)); szType.GetLength() < lstrlen(STRING(IDS_AND_TOOLTIP_TYPE)); )
		{
			szType.Empty();
			break;
		}
		szWidth.Format(STRING(IDS_AND_TOOLTIP_WIDTH), pDatabaseTMParameter->GetWidth());
		szPosition.Format(STRING(IDS_AND_TOOLTIP_POSITION), pParameter->GetBytePos(), pParameter->GetBitPos(), pDatabaseTMParameter->GetWidth());
		szText = ((nType = HIWORD(GetParent()->GetType())) == AND_TYPE_NORMAL || nType == AND_TYPE_TEMPORARY || (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_NATURE_CONSTANT) || (pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_NATURE_DERIVED | TMPARAMETER_NATURE_DERIVED_OL | TMPARAMETER_NATURE_DERIVED_SPEL | TMPARAMETER_NATURE_DERIVED_HARDCODED | TMPARAMETER_NATURE_DERIVED_SAVED)) || (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_OBS_MONITOR) != TMPARAMETER_OBS_MONITOR) ? ((!szType.IsEmpty()) ? (szType + EOL + szWidth) : szWidth) : ((!szType.IsEmpty()) ? (szType + EOL + szPosition) : szPosition);
	}
	break;
	}
	case AND_TITLEITEM_DESCRIPTION:
	{ if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(pParameter->GetRef())))
	{
		szText.Format(STRING(IDS_AND_TOOLTIP_DESCRIPTION), ((szComment = ((nPos = pParameter->GetComment().Find(EOL)) >= 0) ? pParameter->GetComment().Left(nPos) : pParameter->GetComment()).GetLength() > 0 && !pDatabaseTMParameter->GetDetails().IsEmpty()) ? (LPCTSTR)(pDatabaseTMParameter->GetDetails() + EOL + szComment) : ((!pDatabaseTMParameter->GetDetails().IsEmpty()) ? (LPCTSTR)pDatabaseTMParameter->GetDetails() : (LPCTSTR)szComment));
		szText = (pDatabaseTMParameter->GetDetails().IsEmpty() && szComment.IsEmpty()) ? STRING(IDS_AND_TOOLTIP_NODESCRIPTION) : szText;
	}
	break;
	}
	case AND_TITLEITEM_VALUE:
	{ if ((pTMParameter = m_pLayoutValues.GetAt(m_pLayoutValues.Find(pParameter->GetName()))))
	{
		if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(pParameter->GetRef())))
		{
			if (pTMParameter->IsInitialized() && pTMParameter->GetRawValue(pParameter->GetOccurrence(), nValue, nStatus, szCalTable))
			{
				if ((pTMParameter->GetAttributes() & TMPARAMETER_CODING_BITPATTERN) || (pTMParameter->GetAttributes() & TMPARAMETER_CODING_INVERSEBITPATTERN))
				{
					pTMParameter->GetValueAsText(GetDatabase(), pParameter->GetOccurrence(), (pTMParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_DECIMAL | TMPARAMETER_RADIX_HEXADECIMAL)) | TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_RADIX_BINARY, (pParameter->GetDigits() != 0) ? pParameter->GetDigits() : -1, szValue[0]);
					szValue[1].Format(STRING(IDS_AND_TOOLTIP_CODEDVALUE), (LPCTSTR)szValue[0], STRING(IDS_AND_TOOLTIP_BITVALUE));
				}
				if ((pTMParameter->GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) || (pTMParameter->GetAttributes() & TMPARAMETER_CODING_COMPLEMENTCOMPLEX))
				{
					pTMParameter->GetValueAsText(GetDatabase(), pParameter->GetOccurrence(), (pTMParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_HEXADECIMAL)) | TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_RADIX_DECIMAL, (pParameter->GetDigits() != 0) ? pParameter->GetDigits() : -1, szValue[0]);
					szValue[1].Format(STRING(IDS_AND_TOOLTIP_CODEDVALUE), (LPCTSTR)szValue[0], (pTMParameter->GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) ? STRING(IDS_AND_TOOLTIP_SIGNEDVALUE) : STRING(IDS_AND_TOOLTIP_COMPLEMENTVALUE));
				}
				if (pTMParameter->GetAttributes() & TMPARAMETER_CODING_UNSIGNEDINTEGER)
				{
					pTMParameter->GetValueAsText(GetDatabase(), pParameter->GetOccurrence(), (pTMParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_HEXADECIMAL)) | TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_RADIX_DECIMAL, (pParameter->GetDigits() != 0) ? pParameter->GetDigits() : -1, szValue[0]);
					szValue[1].Format(STRING(IDS_AND_TOOLTIP_CODEDVALUE), (LPCTSTR)szValue[0], STRING(IDS_AND_TOOLTIP_UNSIGNEDVALUE));
				}
				if (pTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT)
				{
					pTMParameter->GetValueAsText(GetDatabase(), pParameter->GetOccurrence(), (pTMParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_HEXADECIMAL)) | TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_RADIX_DECIMAL, (pParameter->GetDigits() != 0) ? pParameter->GetDigits() : -1, szValue[0]);
					szValue[1].Format(STRING(IDS_AND_TOOLTIP_CODEDVALUE), (LPCTSTR)szValue[0], STRING(IDS_AND_TOOLTIP_FLOATINGVALUE));
				}
				if ((pTMParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_FLOATINGPOINT)) == 0)
				{
					pTMParameter->GetValueAsText(GetDatabase(), pParameter->GetOccurrence(), TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_RADIX_DECIMAL, (pParameter->GetDigits() != 0) ? pParameter->GetDigits() : -1, szValue[0]);
					szValue[1].Format(STRING(IDS_AND_TOOLTIP_CODEDVALUE), (LPCTSTR)szValue[0], STRING(IDS_AND_TOOLTIP_UNSIGNEDVALUE));
				}
				for (szValue[0].Format(STRING(IDS_AND_TOOLTIP_RAWVALUE), nValue), pTMParameter->GetValueAsText(GetDatabase(), pParameter->GetOccurrence(), pTMParameter->GetAttributes(), (pParameter->GetDigits() != 0) ? pParameter->GetDigits() : -1, szValue[3], bOutSet, (pParameter->GetOccurrence() < 0) ? TRUE : FALSE), szValue[2].Format((pTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) ? STRING(IDS_AND_TOOLTIP_CALIBRATEDNUMERICALVALUE) : STRING(IDS_AND_TOOLTIP_CALIBRATEDSTATUSVALUE), (LPCTSTR)(szValue[3] = (bOutSet) ? ((pTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) ? (szValue[3] + GetDatabase()->GetTMNumCalTablePointOutsideText()) : ((pTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS) ? (szValue[3] + GetDatabase()->GetTMTxtCalTablePointOutsideText()) : szValue[3])) : szValue[3]), (LPCTSTR)szCalTable, (bOutSet) ? ((pTMParameter->GetAttributes() & TMPARAMETER_INTERPRETATION_EXTRAPOLATE) ? STRING(IDS_AND_TOOLTIP_EXTRPOLATEDVALUE) : STRING(IDS_AND_TOOLTIP_OUTSETVALUE)) : STRING(IDS_AND_TOOLTIP_INSETVALUE)), szValueChange.Format(STRING(IDS_AND_TOOLTIP_VALUECHANGE), (LPCTSTR)pTMParameter->GetLastChangeTime().FormatGmt(), (LPCTSTR)pTMParameter->GetLastChangeTMUnit()), szValueUpdate.Format(STRING(IDS_AND_TOOLTIP_VALUEUPDATE), (LPCTSTR)pTMParameter->GetLastUpdateTime().FormatGmt(), (LPCTSTR)pTMParameter->GetLastUpdateTMUnit()), szStatus.Format(STRING(IDS_AND_TOOLTIP_STATUS), (nStatus & TMPARAMETER_STATUS_GOOD) ? STRING(IDS_AND_TOOLTIP_GOODQUALITY) : STRING(IDS_AND_TOOLTIP_BADQUALITY), (nStatus & TMPARAMETER_STATUS_SOFTLIMIT) ? STRING(IDS_AND_TOOLTIP_SOFTOOL) : ((nStatus & TMPARAMETER_STATUS_HARDLIMIT) ? STRING(IDS_AND_TOOLTIP_HARDOOL) : ((nStatus & TMPARAMETER_STATUS_DELTALIMIT) ? STRING(IDS_AND_TOOLTIP_DELTAOOL) : ((nStatus & TMPARAMETER_STATUS_CONSISTENCYLIMIT) ? STRING(IDS_AND_TOOLTIP_CONSISTENCYOOL) : STRING(IDS_AND_TOOLTIP_NOOOL)))), (nStatus & TMPARAMETER_STATUS_VALID) ? STRING(IDS_AND_TOOLTIP_VALID) : STRING(IDS_AND_TOOLTIP_INVALID)); pTMParameter->GetAttributes() & TMPARAMETER_NATURE_CONSTANT; )
				{
					for (szValue[3].Format(STRING(IDS_AND_TOOLTIP_RAWTEXT), (LPCTSTR)pDatabaseTMParameter->GetConstValueAsText()); (pTMParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_FLOATINGPOINT)) == 0; )
					{
						szValue[0] = szValue[3];
						break;
					}
					szValueChange.Empty();
					szValueUpdate.Empty();
					szStatus.Empty();
					break;
				}
				if (pParameter->GetOccurrence() > 0)
				{
					szValue[3].Format(STRING(IDS_AND_TOOLTIP_OCCURRENCE), pParameter->GetOccurrence());
					szValue[0] = szValue[3] + EOL + szValue[0];
				}
				if (pParameter->GetOccurrence() < 0)
				{
					szValue[3].Format(STRING(IDS_AND_TOOLTIP_PASTVALUE), -pParameter->GetOccurrence());
					szValue[0] = szValue[3] + EOL + szValue[0];
				}
				szText = (((pTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) || (pTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS)) && lstrlen(szCalTable) > 0) ? ((!szValueChange.IsEmpty() && !szValueUpdate.IsEmpty() && !szStatus.IsEmpty()) ? (szValue[0] + EOL + szValue[1] + EOL + szValue[2] + EOL + szValueChange + EOL + szValueUpdate + EOL + szStatus) : (szValue[0] + EOL + szValue[1] + EOL + szValue[2])) : ((!szValueChange.IsEmpty() && !szValueUpdate.IsEmpty() && !szStatus.IsEmpty()) ? (szValue[0] + EOL + szValue[1] + EOL + szValueChange + EOL + szValueUpdate + EOL + szStatus) : (szValue[0] + EOL + szValue[1]));
				break;
			}
			szText = STRING(IDS_AND_TOOLTIP_NOVALUE);
		}
	}
	break;
	}
	case AND_TITLEITEM_CHANGETMUNIT:
	case AND_TITLEITEM_CHANGETIME:
	{ if ((pTMParameter = m_pLayoutValues.GetAt(m_pLayoutValues.Find(pParameter->GetName()))))
	{
		if ((pTMParameter->GetAttributes() & TMPARAMETER_NATURE_CONSTANT) != TMPARAMETER_NATURE_CONSTANT)
		{
			if ((nIndex = GetDatabase()->GetTMPackets()->Find(pTMParameter->GetLastChangeTMUnit())) >= 0)
			{
				szValueChange.Format(STRING(IDS_AND_TOOLTIP_CHANGETMUNIT), (LPCTSTR)GetDatabase()->GetTMPackets()->GetAt(nIndex)->GetDescription(), (LPCTSTR)pTMParameter->GetLastChangeTMUnit());
				szValueChangeTime.Format(STRING(IDS_AND_TOOLTIP_CHANGETIME), (LPCTSTR)pTMParameter->GetLastChangeTime().FormatGmt(), (LPCTSTR)pTMParameter->GetLastChangeTime().FormatGmt(CString(STRING(IDS_TIMETAG_DATEFORMAT)) + SPACE + STRING(IDS_TIMETAG_TIMEFORMAT)));
				szText = szValueChange + EOL + szValueChangeTime;
				break;
			}
			szText.Format(STRING(IDS_AND_TOOLTIP_CHANGETIME), (LPCTSTR)pTMParameter->GetLastChangeTime().FormatGmt(), (LPCTSTR)pTMParameter->GetLastChangeTime().FormatGmt(CString(STRING(IDS_TIMEKEY_DATEFORMAT)) + SPACE + STRING(IDS_TIMEKEY_TIMEFORMAT)));
		}
	}
	break;
	}
	case AND_TITLEITEM_UPDATETMUNIT:
	case AND_TITLEITEM_UPDATETIME:
	{ if ((pTMParameter = m_pLayoutValues.GetAt(m_pLayoutValues.Find(pParameter->GetName()))))
	{
		if ((pTMParameter->GetAttributes() & TMPARAMETER_NATURE_CONSTANT) != TMPARAMETER_NATURE_CONSTANT)
		{
			if ((nIndex = GetDatabase()->GetTMPackets()->Find(pTMParameter->GetLastUpdateTMUnit())) >= 0)
			{
				szValueUpdate.Format(STRING(IDS_AND_TOOLTIP_UPDATETMUNIT), (LPCTSTR)GetDatabase()->GetTMPackets()->GetAt(nIndex)->GetDescription(), (LPCTSTR)pTMParameter->GetLastUpdateTMUnit());
				szValueUpdateTime.Format(STRING(IDS_AND_TOOLTIP_UPDATETIME), (LPCTSTR)pTMParameter->GetLastUpdateTime().FormatGmt(), (LPCTSTR)pTMParameter->GetLastUpdateTime().FormatGmt(CString(STRING(IDS_TIMETAG_DATEFORMAT)) + SPACE + STRING(IDS_TIMETAG_TIMEFORMAT)));
				szText = szValueUpdate + EOL + szValueUpdateTime;
				break;
			}
			szText.Format(STRING(IDS_AND_TOOLTIP_UPDATETIME), (LPCTSTR)pTMParameter->GetLastUpdateTime().FormatGmt(), (LPCTSTR)pTMParameter->GetLastUpdateTime().FormatGmt(CString(STRING(IDS_TIMEKEY_DATEFORMAT)) + SPACE + STRING(IDS_TIMEKEY_TIMEFORMAT)));
		}
	}
	break;
	}
	case AND_TITLEITEM_UNIT:
	case AND_TITLEITEM_EXPECTEDVALUES: break;
	}
	return((pParameter->GetDigits() >= 0) ? szText : EMPTYSTRING);
}

BOOL CANDView::LoadToolTipCursor()
{
	return(((m_hToolTipCursor = (HCURSOR)LoadImage(GetModuleHandle((LPCTSTR)NULL), MAKEINTRESOURCE(IDC_TOOLTIPCURSOR), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR))) ? TRUE : FALSE);
}

HCURSOR CANDView::GetToolTipCursor() CONST
{
	return((!m_hToolTipCursor) ? (HCURSOR)(DWORD_PTR)GetClassLongPtr(GetSafeHwnd(), GCLP_HCURSOR) : m_hToolTipCursor);
}

BOOL CANDView::FreeToolTipCursor()
{
	if (m_hToolTipCursor)
	{
		DestroyCursor(m_hToolTipCursor);
		m_hToolTipCursor = (HCURSOR)NULL;
		return TRUE;
	}
	return FALSE;
}

VOID CANDView::RecalcLayout()
{
	CWnd  *pWnd;
	CRect  rWnd;
	CRect  rView;

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
		MoveWindow(rView);
	}
	CTextView::RecalcLayout();
}

void CANDView::PostNcDestroy()
{
	m_cLayout.RemoveAll();
	m_szLayoutTables.RemoveAll();
	m_nLayoutColumns.RemoveAll();
	m_nLayoutColors.RemoveAll();
	m_nLayoutStatus.RemoveAll();
	m_bLayoutValues.RemoveAll();
	m_pLayoutValues.RemoveAll();
	CTextView::PostNcDestroy();
}

BOOL CANDView::Lock()
{
	return((IsWindow(GetSafeHwnd())) ? (GetParent()->Lock() && CTextView::Lock()) : CTextView::Lock());
}

BOOL CANDView::Unlock()
{
	return((IsWindow(GetSafeHwnd())) ? (CTextView::Unlock() && GetParent()->Unlock()) : CTextView::Unlock());
}

BEGIN_MESSAGE_MAP(CANDView, CTextView)
	//{{AFX_MSG_MAP(CANDView)
	ON_WM_CREATE()
	ON_WM_SETCURSOR()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDView message handlers

int CANDView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	LOGFONT  lfFont[2];
	CTextViewLock  cLock(this);

	return((CTextView::OnCreate(lpCreateStruct) != -1 && (GetLabelsFont(&lfFont[0]) || SetLabelsFont()) && (GetValuesFont(&lfFont[1]) || SetValuesFont()) && GetTitleFont(&m_lfLayoutDefault[0]) && GetLabelsFont(&m_lfLayoutDefault[1]) && GetItemsFont(&m_lfLayoutDefault[2]) && GetValuesFont(&m_lfLayoutDefault[3]) && LoadToolTipCursor()) ? 0 : -1);
}

BOOL CANDView::OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message)
{
	INT  nRow;
	INT  nColumn;
	LONG  lDataFlag;
	POINT  ptCursor;
	CRect  rContent;
	CANDLayoutParameter  *pParameter;
	CTextViewLock  cLock(this);

	for (GetCursorPos(&ptCursor), m_wndContentCtrl.ScreenToClient(&ptCursor), m_wndContentCtrl.GetClientRect(rContent); rContent.PtInRect(ptCursor); )
	{
		if ((lDataFlag = GetParent()->IsRetrievingData()) && HIWORD(lDataFlag))
		{
			SetCursor(LoadCursor((HINSTANCE)NULL, IDC_WAIT));
			return TRUE;
		}
		if ((pParameter = (IsToolTipModeEnabled() && FindTextFromPoint(ptCursor, nRow, nColumn, FALSE)) ? FindParameter(nRow, nColumn) : (CANDLayoutParameter *)NULL) && pParameter->GetRef() >= 0 && !pParameter->IsLabel())
		{
			switch (m_nLayoutColumns.GetAt(nColumn))
			{
			case AND_TITLEITEM_ID:
			case AND_TITLEITEM_DESCRIPTION:
			case AND_TITLEITEM_VALUE:
			case AND_TITLEITEM_CHANGETMUNIT:
			case AND_TITLEITEM_CHANGETIME:
			case AND_TITLEITEM_UPDATETMUNIT:
			case AND_TITLEITEM_UPDATETIME:
			{ SetCursor(GetToolTipCursor());
			return TRUE;
			}
			case AND_TITLEITEM_UNIT:
			case AND_TITLEITEM_EXPECTEDVALUES: break;
			}
		}
		break;
	}
	return CTextView::OnSetCursor(pWnd, nHitTest, message);
}

BOOL CANDView::OnContentMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	INT  nRow;
	INT  nColumn;
	LONG  lDataFlag;
	CFont  cFont[2];
	CPoint  ptToolTip;
	LOGFONT  lfFont[2];
	CString  szParameter;
	CString  szToolTip[2];
	CANDLayoutParameter  *pParameter;
	CTextViewLock  cLock(this);

	if (message == WM_SETFOCUS)
	{
		SetCurText((GetCurText() >= 0) ? GetCurText() : 0);
		return FALSE;
	}
	if (message == WM_KEYDOWN)
	{
		if (wParam == VK_TAB) GetParent()->SetFocus();
		return FALSE;
	}
	if (message == WM_LBUTTONDBLCLK)
	{
		if (!(lDataFlag = GetParent()->IsRetrievingData()) || !HIWORD(lDataFlag))
		{
			if ((pParameter = (FindTextFromPoint(CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)), nRow, nColumn, FALSE)) ? FindParameter(nRow, nColumn) : (CANDLayoutParameter *)NULL) && !pParameter->IsLabel())
			{
				for (szParameter = pParameter->GetName(), cLock.Release(); !szParameter.IsEmpty(); )
				{
					GetParent()->SetParameterInfo(szParameter);
					break;
				}
				return FALSE;
			}
		}
		return FALSE;
	}
	if (message == WM_RBUTTONDOWN)
	{
		if (!(lDataFlag = GetParent()->IsRetrievingData()) || !HIWORD(lDataFlag))
		{
			if ((pParameter = (IsToolTipModeEnabled() && FindTextFromPoint((ptToolTip = CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))), nRow, nColumn, FALSE)) ? FindParameter(nRow, nColumn) : (CANDLayoutParameter *)NULL) && !pParameter->IsLabel())
			{
				switch (m_nLayoutColumns.GetAt(nColumn))
				{
				case AND_TITLEITEM_ID:
				case AND_TITLEITEM_DESCRIPTION:
				case AND_TITLEITEM_VALUE:
				case AND_TITLEITEM_CHANGETMUNIT:
				case AND_TITLEITEM_CHANGETIME:
				case AND_TITLEITEM_UPDATETMUNIT:
				case AND_TITLEITEM_UPDATETIME:
				{ for (szToolTip[0] = ConstructToolTipTitle(pParameter, m_nLayoutColumns.GetAt(nColumn)), szToolTip[1] = ConstructToolTipText(pParameter, m_nLayoutColumns.GetAt(nColumn)), GetTextFont(&lfFont[0]), GetTextFont(&lfFont[1]), lfFont[0].lfWeight = FW_BOLD, lfFont[1].lfWeight = FW_NORMAL; cFont[0].CreateFontIndirect(&lfFont[0]) && cFont[1].CreateFontIndirect(&lfFont[1]); )
				{
					m_wndToolTip.SetTitleFont(&cFont[0]);
					m_wndToolTip.SetTextFont(&cFont[1]);
					break;
				}
				m_wndToolTip.Create(&m_wndContentCtrl, ptToolTip, szToolTip[0], szToolTip[1]);
				break;
				}
				case AND_TITLEITEM_UNIT:
				case AND_TITLEITEM_EXPECTEDVALUES: break;
				}
			}
		}
		return FALSE;
	}
	if (message == WM_RBUTTONUP)
	{
		m_wndToolTip.Destroy();
		return FALSE;
	}
	return FALSE;
}

void CANDView::OnDestroy()
{
	CTextViewLock  cLock(this);

	FreeToolTipCursor();
	CTextView::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CANDWnd

IMPLEMENT_DYNAMIC(CANDWnd, CDisplayWnd)

CANDWnd::CANDWnd() : CDisplayWnd()
{
	SetType(DISPLAY_TYPE_AND);
	SetRetrieveMode();
	SetRetrieveSpeed();
	SetRetrieveInterval();
	SetRetrieveStartTime();
	SetRetrieveStopTime();
	SetUpdateInfo();
}

BOOL CANDWnd::Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszTitle, PDISPLAYINFO pDefaultInfo, BOOL bDefault)
{
	if (CDisplayWnd::Create(pParentWnd, (!pszTitle) ? STRING(IDS_DISPLAY_TITLE_AND) : pszTitle, pDefaultInfo->rWnd, IDR_ANDFRAME))
	{
		if (SetScope(pDefaultInfo->nScope) && SetMode(pDefaultInfo->nMode) && Customize(bDefault)) return TRUE;
		DestroyWindow();
	}
	return FALSE;
}

BOOL CANDWnd::SetLayout(LPCTSTR pszLayout)
{
	CANDLayout  cLayout;

	return LoadLayout(pszLayout, cLayout) && SetLayout(cLayout);
}
BOOL CANDWnd::SetLayout(CONST CANDLayout &cLayout)
{
	return m_wndView.SetLayout(cLayout);
}
BOOL CANDWnd::SetLayout(LPCTSTR pszLayout, CONST CUIntArray &nColumns)
{
	CANDLayout  cLayout;

	return LoadLayout(pszLayout, cLayout) && SetLayout(cLayout, nColumns);
}
BOOL CANDWnd::SetLayout(CONST CANDLayout &cLayout, CONST CUIntArray &nColumns)
{
	return m_wndView.SetLayout(cLayout, nColumns);
}
BOOL CANDWnd::SetLayout(LPCTSTR pszLayout, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths)
{
	CANDLayout  cLayout;

	return LoadLayout(pszLayout, cLayout) && SetLayout(cLayout, nColumns, nWidths);
}
BOOL CANDWnd::SetLayout(CONST CANDLayout &cLayout, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths)
{
	return m_wndView.SetLayout(cLayout, nColumns, nWidths);
}

BOOL CANDWnd::GetLayout(CString &szLayout) CONST
{
	CANDLayout  cLayout;

	if (GetLayout(cLayout))
	{
		szLayout = cLayout.GetName();
		return TRUE;
	}
	return FALSE;
}
BOOL CANDWnd::GetLayout(CANDLayout &cLayout) CONST
{
	return m_wndView.GetLayout(cLayout);
}
BOOL CANDWnd::GetLayout(CString &szLayout, CUIntArray &nColumns) CONST
{
	CANDLayout  cLayout;

	if (GetLayout(cLayout, nColumns))
	{
		szLayout = cLayout.GetName();
		return TRUE;
	}
	return FALSE;
}
BOOL CANDWnd::GetLayout(CANDLayout &cLayout, CUIntArray &nColumns) CONST
{
	return m_wndView.GetLayout(cLayout, nColumns);
}
BOOL CANDWnd::GetLayout(CString &szLayout, CUIntArray &nColumns, CUIntArray &nWidths) CONST
{
	CANDLayout  cLayout;

	if (GetLayout(cLayout, nColumns, nWidths))
	{
		szLayout = cLayout.GetName();
		return TRUE;
	}
	return FALSE;
}
BOOL CANDWnd::GetLayout(CANDLayout &cLayout, CUIntArray &nColumns, CUIntArray &nWidths) CONST
{
	return m_wndView.GetLayout(cLayout, nColumns, nWidths);
}

BOOL CANDWnd::SetTitleFont(CFont *pFont, BOOL bDefault)
{
	return m_wndView.SetTitleFont(pFont, bDefault);
}
BOOL CANDWnd::SetTitleFont(CONST LOGFONT *plfFont, BOOL bDefault)
{
	return m_wndView.SetTitleFont(plfFont, bDefault);
}

BOOL CANDWnd::GetTitleFont(CFont *pFont, BOOL bDefault) CONST
{
	return m_wndView.GetTitleFont(pFont, bDefault);
}
BOOL CANDWnd::GetTitleFont(LOGFONT *plfFont, BOOL bDefault) CONST
{
	return m_wndView.GetTitleFont(plfFont, bDefault);
}

BOOL CANDWnd::SetLabelsFont(CFont *pFont, BOOL bDefault)
{
	return m_wndView.SetLabelsFont(pFont, bDefault);
}
BOOL CANDWnd::SetLabelsFont(CONST LOGFONT *plfFont, BOOL bDefault)
{
	return m_wndView.SetLabelsFont(plfFont, bDefault);
}

BOOL CANDWnd::GetLabelsFont(CFont *pFont, BOOL bDefault) CONST
{
	return m_wndView.GetLabelsFont(pFont, bDefault);
}
BOOL CANDWnd::GetLabelsFont(LOGFONT *plfFont, BOOL bDefault) CONST
{
	return m_wndView.GetLabelsFont(plfFont, bDefault);
}

BOOL CANDWnd::SetItemsFont(CFont *pFont, BOOL bDefault)
{
	return m_wndView.SetItemsFont(pFont, bDefault);
}
BOOL CANDWnd::SetItemsFont(CONST LOGFONT *plfFont, BOOL bDefault)
{
	return m_wndView.SetItemsFont(plfFont, bDefault);
}

BOOL CANDWnd::GetItemsFont(CFont *pFont, BOOL bDefault) CONST
{
	return m_wndView.GetItemsFont(pFont, bDefault);
}
BOOL CANDWnd::GetItemsFont(LOGFONT *plfFont, BOOL bDefault) CONST
{
	return m_wndView.GetItemsFont(plfFont, bDefault);
}

BOOL CANDWnd::SetValuesFont(CFont *pFont, BOOL bDefault)
{
	return m_wndView.SetValuesFont(pFont, bDefault);
}
BOOL CANDWnd::SetValuesFont(CONST LOGFONT *plfFont, BOOL bDefault)
{
	return m_wndView.SetValuesFont(plfFont, bDefault);
}

BOOL CANDWnd::GetValuesFont(CFont *pFont, BOOL bDefault) CONST
{
	return m_wndView.GetValuesFont(pFont, bDefault);
}
BOOL CANDWnd::GetValuesFont(LOGFONT *plfFont, BOOL bDefault) CONST
{
	return m_wndView.GetValuesFont(plfFont, bDefault);
}

BOOL CANDWnd::SetOolColors(CONST CUIntArray &nColors)
{
	return m_wndView.SetOolColors(nColors);
}

BOOL CANDWnd::GetOolColors(CUIntArray &nColors) CONST
{
	return m_wndView.GetOolColors(nColors);
}

BOOL CANDWnd::EnableInvalidDataMode(BOOL bEnable)
{
	return m_wndView.EnableInvalidDataMode(bEnable);
}

BOOL CANDWnd::IsInvalidDataModeEnabled() CONST
{
	return m_wndView.IsInvalidDataModeEnabled();
}

BOOL CANDWnd::EnableBadDataMode(BOOL bEnable)
{
	return m_wndView.EnableBadDataMode(bEnable);
}

BOOL CANDWnd::IsBadDataModeEnabled() CONST
{
	return m_wndView.IsBadDataModeEnabled();
}

BOOL CANDWnd::EnableToolTipMode(BOOL bEnable)
{
	return m_wndView.EnableToolTipMode(bEnable);
}

BOOL CANDWnd::IsToolTipModeEnabled() CONST
{
	return m_wndView.IsToolTipModeEnabled();
}

BOOL CANDWnd::Start()
{
	if (((GetMode() == DISPLAY_MODE_REALTIME  &&  ProcessRealtimeData()) || (GetMode() == DISPLAY_MODE_HISTORY  &&  StartRetrieveData())) && StartSchedulePrintJobs())
	{
		Initialize(TRUE);
		UpdateAllPanes();
		return TRUE;
	}
	return FALSE;
}

BOOL CANDWnd::Prepare(BOOL bDialog)
{
	INT  nResult;

	if (bDialog)
	{
		if ((nResult = m_dlgOpen.Create(this)) == IDCANCEL || nResult <= 0) MDIDestroy();
		return((nResult == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
	}
	return TRUE;
}

BOOL CANDWnd::Initialize(BOOL bFlag)
{
	return CDisplayWnd::Initialize(bFlag);
}
BOOL CANDWnd::Initialize(CTMEnvironment *pTMEnvironment)
{
	return m_wndView.Initialize(pTMEnvironment);
}
BOOL CANDWnd::Initialize(CString &szTag, CTimeTag &tTag)
{
	return m_wndView.Initialize(szTag, tTag);
}

BOOL CANDWnd::InitializeTMData(UINT nMode)
{
	for (StopRetrieveData(); (nMode == DISPLAY_MODE_REALTIME && SetMode(DISPLAY_MODE_REALTIME) && ProcessRealtimeData()) || (nMode == DISPLAY_MODE_HISTORY && SetMode(DISPLAY_MODE_HISTORY) && StartRetrieveData()); )
	{
		UpdateBars();
		return TRUE;
	}
	return FALSE;
}
BOOL CANDWnd::InitializeTMData(CTMParameters &pTMParameters, BOOL bBadData)
{
	CDisplayWnd  *pDisplayWnd;

	return((GetMode() == DISPLAY_MODE_HISTORY) ? (((pDisplayWnd = GetLink())) ? pDisplayWnd->InitializeTMData(pTMParameters, bBadData) : m_cRetrieveThread.InitializeTMData(pTMParameters, bBadData)) : GetTMService()->InitializeTMData(pTMParameters, bBadData));
}

BOOL CANDWnd::Check() CONST
{
	return CheckAccountPrivilege(PRIVILEGE_AND_USE);
}

VOID CANDWnd::Update()
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
BOOL CANDWnd::Update(CONST CTimeKey &tTimeKey, CTMEnvironment *pTMEnvironment, UINT nFlags)
{
	INT  nLink;
	INT  nLinks;
	CPtrArray  pLinks;
	CANDLayout  cLayout;
	CDisplayWnd  *pDisplayWnd;
	CDisplayLock  cLock(this);

	if (IsInitialized())
	{
		for (nLink = 0, nLinks = GetLinks(pLinks); nLink < nLinks; nLink++)
		{
			if ((pDisplayWnd = (CDisplayWnd *)pLinks.GetAt(nLink)) && pDisplayWnd->IsInitialized())
			{
				pDisplayWnd->Update(tTimeKey, pTMEnvironment, nFlags);
				continue;
			}
		}
		if (GetLayout(cLayout) && !cLayout.GetSize())
		{
			SetUpdateInfo();
			return FALSE;
		}
		for (; GetMode() == DISPLAY_MODE_REALTIME; )
		{
			if (pTMEnvironment->GetTMUnit()->GetTag() != STRING(IDS_TMUNIT_INTERACTIVE) && !pTMEnvironment->GetTMUnit()->IsValid() && !nFlags) return TRUE;
			break;
		}
		if ((((nFlags & HISTORYFILE_SUCCESS) && ((nFlags & HISTORYFILE_TMUNIT) || (nFlags & HISTORYFILE_TMPARAMETERS))) || !nFlags) && m_wndView.Update(pTMEnvironment))
		{
			SetUpdateInfo(pTMEnvironment->GetTMUnit()->GetTag(), (pTMEnvironment->GetTMUnit()->IsValid()) ? pTMEnvironment->GetTMUnit()->GetTimeTag() : CTimeTag(tTimeKey), pTMEnvironment->GetTMUnit()->GetUnitID(), pTMEnvironment->GetTMUnit()->GetQuality());
			return TRUE;
		}
		if ((nFlags & HISTORYFILE_SUCCESS) && !(nFlags & HISTORYFILE_TMUNIT) && !(nFlags & HISTORYFILE_TMPARAMETERS))
		{
			if (GetRetrieveMode() & (AND_RETRIEVE_AUTOBACKWARD | AND_RETRIEVE_MANUALBACKWARD)) Reset(pTMEnvironment);
			return TRUE;
		}
	}
	return FALSE;
}

VOID CANDWnd::Reset(CTMEnvironment *pTMEnvironment)
{
	CDisplayLock  cLock(this);

	if (IsInitialized())
	{
		if (pTMEnvironment != (CTMEnvironment *)NULL) pTMEnvironment->Reset();
		m_wndView.Reset(pTMEnvironment);
		SetUpdateInfo();
	}
}

BOOL CANDWnd::Stop()
{
	Initialize(FALSE);
	StopSchedulePrintJobs();
	StopRetrieveData();
	return TRUE;
}

BOOL CANDWnd::SaveInfo(INT nPage, INT nDisplay, LPCTSTR pszTitle, CONST PDISPLAYINFO pDisplayInfo)
{
	UINT  nMode;
	UINT  nSpeed;
	CString  szFileName;
	LOGFONT  sFontInfo[4][2];
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CUIntArray  nWidths;
	CUIntArray  nColumns;
	CUIntArray  nColors;
	CByteArray  nPrintInfo;
	CANDLayout  cLayout;
	CProfile  cProfile;

	return((CDisplayWnd::SaveInfo(nPage, nDisplay, pszTitle, pDisplayInfo) && GetLayout(cLayout, nColumns, nWidths) && GetTitleFont(&sFontInfo[0][0], FALSE) && GetTitleFont(&sFontInfo[0][1], TRUE) && GetLabelsFont(&sFontInfo[1][0], FALSE) && GetLabelsFont(&sFontInfo[1][1], TRUE) && GetItemsFont(&sFontInfo[2][0], FALSE) && GetItemsFont(&sFontInfo[2][1], TRUE) && GetValuesFont(&sFontInfo[3][0], FALSE) && GetValuesFont(&sFontInfo[3][1], TRUE) && GetOolColors(nColors) && GetRetrieveMode(nMode) && GetRetrieveSpeed(nSpeed) && GetRetrieveInterval(tInterval) && GetRetrieveStartTime(tStartTime) && GetRetrieveStopTime(tStopTime) && GetRetrieveFileName(szFileName) && GetPrintJobs(nPrintInfo) && cProfile.SetANDLayoutName(nPage, nDisplay, cLayout.GetName()) && cProfile.SetANDLayoutInfo(nPage, nDisplay, nColumns, nWidths, nColors, IsInvalidDataModeEnabled(), IsBadDataModeEnabled(), IsToolTipModeEnabled()) && cProfile.SetANDFontsInfo(nPage, nDisplay, &sFontInfo[0][0], &sFontInfo[0][1], &sFontInfo[1][0], &sFontInfo[1][1], &sFontInfo[2][0], &sFontInfo[2][1], &sFontInfo[3][0], &sFontInfo[3][1]) && cProfile.SetANDModeInfo(nPage, nDisplay, nMode, nSpeed, tInterval, tStartTime, tStopTime) && cProfile.SetANDRetrieveFileName(nPage, nDisplay, szFileName) && cProfile.SetANDPrintInfo(nPage, nDisplay, nPrintInfo)) ? TRUE : FALSE);
}

BOOL CANDWnd::LoadInfo(INT nPage, INT nDisplay, CString &szTitle, PDISPLAYINFO pDisplayInfo)
{
	UINT  nMode;
	UINT  nSpeed;
	BOOL  bBadData;
	BOOL  bToolTips;
	BOOL  bInvalidData;
	CString  szName;
	CString  szFileName;
	LOGFONT  sFontInfo[4][2];
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CUIntArray  nColumns;
	CUIntArray  nWidths;
	CUIntArray  nColors;
	CByteArray  nPrintInfo;
	CProfile  cProfile;

	return((CDisplayWnd::LoadInfo(nPage, nDisplay, szTitle, pDisplayInfo) && cProfile.GetANDLayoutName(nPage, nDisplay, szName) && cProfile.GetANDLayoutInfo(nPage, nDisplay, nColumns, nWidths, nColors, bInvalidData, bBadData, bToolTips) && cProfile.GetANDFontsInfo(nPage, nDisplay, &sFontInfo[0][0], &sFontInfo[0][1], &sFontInfo[1][0], &sFontInfo[1][1], &sFontInfo[2][0], &sFontInfo[2][1], &sFontInfo[3][0], &sFontInfo[3][1]) && cProfile.GetANDModeInfo(nPage, nDisplay, nMode, nSpeed, tInterval, tStartTime, tStopTime) && cProfile.GetANDRetrieveFileName(nPage, nDisplay, szFileName) && cProfile.GetANDPrintInfo(nPage, nDisplay, nPrintInfo) && SetLayout(szName, nColumns, nWidths) && SetOolColors(nColors) && EnableInvalidDataMode(bInvalidData) && EnableBadDataMode(bBadData) && EnableToolTipMode(bToolTips) && SetTitleFont(&sFontInfo[0][1], TRUE) && SetTitleFont(&sFontInfo[0][0], FALSE) && SetLabelsFont(&sFontInfo[1][1], TRUE) && SetLabelsFont(&sFontInfo[1][0], FALSE) && SetItemsFont(&sFontInfo[2][1], TRUE) && SetItemsFont(&sFontInfo[2][0], FALSE) && SetValuesFont(&sFontInfo[3][1], TRUE) && SetValuesFont(&sFontInfo[3][0], FALSE) && SetRetrieveMode(nMode) && SetRetrieveSpeed(nSpeed) && SetRetrieveInterval(tInterval) && SetRetrieveStartTime(tStartTime) && SetRetrieveStopTime(tStopTime) && SetRetrieveFileName(szFileName) && SetPrintJobs(nPrintInfo)) ? TRUE : FALSE);
}

BOOL CANDWnd::QueryDefaultInfo(PDISPLAYINFO pDefaultInfo) CONST
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

BOOL CANDWnd::QueryDefaultMenu(CLocaleMenu &cMenu, CImageList &cImages, CUIntArray &nImageIDs) CONST
{
	INT  nIndex;
	INT  nCount;
	INT  iImage;
	UINT  nButtonID;
	UINT  nButtonStyle;
	CBitmap  cBitmap;
	BITMAP  sBitmap;

	for (cImages.DeleteImageList(), nImageIDs.RemoveAll(); cBitmap.LoadBitmap(IDB_ANDFRAMESMALLIMAGES) && cBitmap.GetBitmap(&sBitmap); )
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
	return cMenu.LoadMenu(IDR_ANDFRAME);
}

VOID CANDWnd::ReduceFonts(BOOL bRestore)
{
	m_wndView.ReduceFonts(bRestore);
}

BOOL CANDWnd::CanReduceFonts(BOOL bRestore) CONST
{
	return m_wndView.CanReduceFonts(bRestore);
}

VOID CANDWnd::UpdateSysMenu(CMenu *pMenu)
{
	INT  nItem;
	INT  nItems;

	for (nItem = 0, nItems = pMenu->GetMenuItemCount(); nItem < nItems; nItem++)
	{
		if (pMenu->GetMenuItemID(nItem) == IDM_DISPLAYREDUCEFONTS)
		{
			nItems = -1;
			break;
		}
		if (pMenu->GetMenuItemID(nItem) == SC_CLOSE) break;
	}
	if (nItems >= 0)
	{
		pMenu->InsertMenu(nItem, MF_BYPOSITION | MF_STRING, IDM_DISPLAYREDUCEFONTS, STRING(IDS_DISPLAY_MENU_REDUCEFONTS));
		pMenu->InsertMenu(++nItem, MF_BYPOSITION | MF_STRING, IDM_DISPLAYRESTOREFONTS, STRING(IDS_DISPLAY_MENU_RESTOREFONTS));
		if (++nItem < (INT)pMenu->GetMenuItemCount()) pMenu->InsertMenu(nItem, MF_BYPOSITION | MF_SEPARATOR);
	}
	pMenu->EnableMenuItem(IDM_DISPLAYREDUCEFONTS, (CanReduceFonts(FALSE)) ? (MF_BYCOMMAND | MF_ENABLED) : (MF_BYCOMMAND | MF_DISABLED | MF_GRAYED));
	pMenu->EnableMenuItem(IDM_DISPLAYRESTOREFONTS, (CanReduceFonts(TRUE)) ? (MF_BYCOMMAND | MF_ENABLED) : (MF_BYCOMMAND | MF_DISABLED | MF_GRAYED));
}

VOID CANDWnd::UpdateBars()
{
	CDisplayLock  cLock(this);

	UpdateMessagePane();
	UpdateModePane();
	UpdateTypePane();
}

BOOL CANDWnd::Print(PRINTDLG *pPrintInfo)
{
	INT  nJob;
	INT  nJobs;
	CANDPrintJobs  pJobs;
	CANDPrintJobInfo  *pJobInfo;
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
		if (pJobInfo->GetPrintMode() & AND_PRINT_CLEARCOMMENTS)
		{
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~AND_PRINT_CLEARCOMMENTS);
			pJobInfo->SetComments(EMPTYSTRING);
			SetPrintJobs(pJobs);
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CANDWnd::CanPrint() CONST
{
	return HasLayout();
}

BOOL CANDWnd::ProcessRealtimeData()
{
	INT  nLink;
	INT  nLinks;
	CString  szTag;
	CTimeTag  tTag;
	CPtrArray  pLinks;
	CDisplayWnd  *pDisplayWnd;
	CDisplayLock  cLock(this);

	for (nLink = 0, nLinks = GetLinks(pLinks); nLink < nLinks; nLink++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pLinks.GetAt(nLink)) && pDisplayWnd->IsInitialized())
		{
			pDisplayWnd->InitializeTMData(DISPLAY_MODE_REALTIME);
			continue;
		}
	}
	if (Initialize(szTag, tTag))
	{
		SetUpdateInfo(szTag, tTag, -1, TMUNIT_DATAQUALITY_NONE);
		return TRUE;
	}
	return FALSE;
}

BOOL CANDWnd::StartRetrieveData(UINT nMode, UINT nSpeed, CONST CTimeSpan &tInterval, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime)
{
	SetRetrieveMode(nMode);
	SetRetrieveSpeed(nSpeed);
	SetRetrieveInterval(tInterval);
	SetRetrieveStartTime(tStartTime);
	SetRetrieveStopTime(tStopTime);
	return StartRetrieveData();
}
BOOL CANDWnd::StartRetrieveData()
{
	INT  nLink;
	INT  nLinks;
	CString  szTag;
	CTimeTag  tTag;
	CEvent  bInit[2];
	CPtrArray  pLinks;
	CDisplayWnd  *pDisplayWnd;

	if (GetMode() == DISPLAY_MODE_HISTORY)
	{
		if (GetLink() != (CDisplayWnd *)NULL)
		{
			for (SetRetrieveMode(); Initialize(szTag, tTag); )
			{
				SetUpdateInfo(szTag, tTag, -1, TMUNIT_DATAQUALITY_NONE);
				return TRUE;
			}
			ReportEvent(SYSTEM_WARNING_AND_RETRIEVE_FAILURE);
			return FALSE;
		}
		if (!IsRetrievingData())
		{
			if (m_cRetrieveThread.Start(this, bInit[0], bInit[1], GetRetrieveFileName(), GetRetrieveMode(), GetRetrieveSpeed(), GetRetrieveInterval(), GetRetrieveStartTime(), GetRetrieveStopTime(), &m_bRetrieveFlag, m_cRetrieveStop, m_cRetrieveAutoForward, m_cRetrieveAutoBackward, m_cRetrieveManualForward, m_cRetrieveManualBackward, m_cRetrievePseudoRealtime) && UpdateAllPanes())
			{
				for (WaitForSingleObject(bInit[0], INFINITE); Lock(); )
				{
					for (nLink = 0, nLinks = GetLinks(pLinks); nLink < nLinks; nLink++)
					{
						if ((pDisplayWnd = (CDisplayWnd *)pLinks.GetAt(nLink)) && pDisplayWnd->IsInitialized())
						{
							pDisplayWnd->InitializeTMData(DISPLAY_MODE_HISTORY);
							continue;
						}
					}
					Unlock();
					break;
				}
				if (Initialize(szTag, tTag))
				{
					SetUpdateInfo();
					SetEvent(bInit[1]);
					return TRUE;
				}
				SetEvent(bInit[1]);
			}
			ReportEvent(SYSTEM_WARNING_AND_RETRIEVE_FAILURE);
		}
	}
	return FALSE;
}

LONG CANDWnd::IsRetrievingData() CONST
{
	LONG  bFlag;

	InterlockedExchange(&bFlag, m_bRetrieveFlag);
	return((m_cRetrieveThread.IsThreadActive()) ? bFlag : FALSE);
}

BOOL CANDWnd::RetrieveMoreData(UINT nAction)
{
	if (IsRetrievingData())
	{
		if (nAction == AND_RETRIEVE_STOPPED)
		{
			SetRetrieveMode(GetRetrieveMode() | nAction);
			m_cRetrieveStop.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
		if (nAction == AND_RETRIEVE_AUTOFORWARD)
		{
			SetRetrieveMode((GetRetrieveMode() & (AND_RETRIEVE_EXACTTIME | AND_RETRIEVE_STOPBYTIME | AND_RETRIEVE_STOPBYEND | AND_RETRIEVE_STOPBYREALTIME)) | nAction);
			m_cRetrieveAutoForward.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
		if (nAction == AND_RETRIEVE_AUTOBACKWARD)
		{
			SetRetrieveMode((GetRetrieveMode() & (AND_RETRIEVE_EXACTTIME | AND_RETRIEVE_STOPBYTIME | AND_RETRIEVE_STOPBYEND | AND_RETRIEVE_STOPBYREALTIME)) | nAction);
			m_cRetrieveAutoBackward.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
		if (nAction == AND_RETRIEVE_MANUALFORWARD)
		{
			SetRetrieveMode((GetRetrieveMode() & (AND_RETRIEVE_EXACTTIME | AND_RETRIEVE_STOPBYTIME | AND_RETRIEVE_STOPBYEND | AND_RETRIEVE_STOPBYREALTIME)) | nAction);
			m_cRetrieveManualForward.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
		if (nAction == AND_RETRIEVE_MANUALBACKWARD)
		{
			SetRetrieveMode((GetRetrieveMode() & (AND_RETRIEVE_EXACTTIME | AND_RETRIEVE_STOPBYTIME | AND_RETRIEVE_STOPBYEND | AND_RETRIEVE_STOPBYREALTIME)) | nAction);
			m_cRetrieveManualBackward.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
		if (nAction == AND_RETRIEVE_PSEUDOREALTIME)
		{
			SetRetrieveMode((GetRetrieveMode() & (AND_RETRIEVE_EXACTTIME | AND_RETRIEVE_STOPBYTIME | AND_RETRIEVE_STOPBYEND | AND_RETRIEVE_STOPBYREALTIME)) | nAction);
			m_cRetrievePseudoRealtime.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CANDWnd::StopRetrieveData()
{
	return(((IsRetrievingData() && m_cRetrieveThread.Stop()) || !IsRetrievingData()) ? TRUE : FALSE);
}

BOOL CANDWnd::SetRetrieveMode(UINT nMode)
{
	CDisplayLock  cLock(this);

	m_nRetrieveMode = nMode;
	m_bRetrieveFlag = MAKELONG((nMode) ? LOWORD(m_bRetrieveFlag) : FALSE, (nMode) ? HIWORD(m_bRetrieveFlag) : FALSE);
	return TRUE;
}

BOOL CANDWnd::GetRetrieveMode(UINT &nMode) CONST
{
	nMode = m_nRetrieveMode;
	return TRUE;
}
UINT CANDWnd::GetRetrieveMode() CONST
{
	return m_nRetrieveMode;
}

BOOL CANDWnd::SetRetrieveSpeed(UINT nSpeed)
{
	m_nRetrieveSpeed = nSpeed;
	return TRUE;
}

BOOL CANDWnd::GetRetrieveSpeed(UINT &nSpeed) CONST
{
	nSpeed = m_nRetrieveSpeed;
	return TRUE;
}
UINT CANDWnd::GetRetrieveSpeed() CONST
{
	return m_nRetrieveSpeed;
}

BOOL CANDWnd::SetRetrieveInterval(CONST CTimeSpan &tInterval)
{
	CDisplayLock  cLock(this);

	m_tRetrieveInterval = tInterval;
	return TRUE;
}

BOOL CANDWnd::GetRetrieveInterval(CTimeSpan &tInterval) CONST
{
	CDisplayLock  cLock(this);

	tInterval = m_tRetrieveInterval;
	return TRUE;
}
CTimeSpan CANDWnd::GetRetrieveInterval() CONST
{
	CDisplayLock  cLock(this);

	return m_tRetrieveInterval;
}

BOOL CANDWnd::SetRetrieveStartTime(CONST CTimeKey &tStartTime)
{
	CDisplayLock  cLock(this);

	m_tRetrieveStartTime = tStartTime;
	return TRUE;
}

BOOL CANDWnd::GetRetrieveStartTime(CTimeKey &tStartTime) CONST
{
	CDisplayLock  cLock(this);

	tStartTime = m_tRetrieveStartTime;
	return TRUE;
}
CTimeKey CANDWnd::GetRetrieveStartTime() CONST
{
	CDisplayLock  cLock(this);

	return m_tRetrieveStartTime;
}

BOOL CANDWnd::SetRetrieveStopTime(CONST CTimeKey &tStopTime)
{
	CDisplayLock  cLock(this);

	m_tRetrieveStopTime = tStopTime;
	return TRUE;
}

BOOL CANDWnd::GetRetrieveStopTime(CTimeKey &tStopTime) CONST
{
	CDisplayLock  cLock(this);

	tStopTime = m_tRetrieveStopTime;
	return TRUE;
}
CTimeKey CANDWnd::GetRetrieveStopTime() CONST
{
	CDisplayLock  cLock(this);

	return m_tRetrieveStopTime;
}

BOOL CANDWnd::SetRetrieveFileName(LPCTSTR pszFileName)
{
	CDisplayLock  cLock(this);

	m_szRetrieveFileName = pszFileName;
	return TRUE;
}

BOOL CANDWnd::GetRetrieveFileName(CString &szFileName) CONST
{
	CDisplayLock  cLock(this);

	szFileName = GetRetrieveFileName();
	return TRUE;
}
CString CANDWnd::GetRetrieveFileName() CONST
{
	CString  szFileName;
	CHistoryStoreFile  cFile;
	CHistoryStoreFiles  pFiles;
	CDisplayLock  cLock(this);

	if (GetTMService()->GetTMHistoryFiles(HISTORYFILE_TYPE_RETRIEVE, pFiles) > 0)
	{
		if (pFiles.Find(m_szRetrieveFileName) >= 0)
		{
			szFileName = m_szRetrieveFileName;
			return szFileName;
		}
		if (GetTMService()->GetDefaultTMHistoryFile(HISTORYFILE_TYPE_RETRIEVE, cFile))
		{
			szFileName = cFile.GetFileName();
			return szFileName;
		}
	}
	if (!IsInitialized())
	{
		szFileName = m_szRetrieveFileName;
		return szFileName;
	}
	return EMPTYSTRING;
}

VOID CANDWnd::SetParameterInfo(LPCTSTR pszTag)
{
	ReportEvent((m_dlgParameters.Create(this, pszTag) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

BOOL CANDWnd::GetParameterInfo(LPCTSTR pszTag, CTMParameter *pTMParameter) CONST
{
	return m_wndView.GetParameterInfo(pszTag, pTMParameter);
}

BOOL CANDWnd::SetPrintJobs(CONST CANDPrintJobs &pPrintJobs)
{
	return m_cPrintThread.SetPrintJobs(pPrintJobs);
}

BOOL CANDWnd::GetPrintJobs(CANDPrintJobs &pPrintJobs) CONST
{
	return m_cPrintThread.GetPrintJobs(pPrintJobs);
}

BOOL CANDWnd::Print(CONST CANDPrintJobInfo *pJobInfo, PRINTDLG *pPrintInfo)
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
	LOGFONT  lfFont[2];
	DEVMODE  *pDevMode;
	DEVNAMES  *pDevNames;
	CPtrArray  pItemsFonts;
	CANDLayout  cLayout;
	CUIntArray  nOOLColors;
	CStringArray  szColumns;
	CStringArray  szContents;
	CTMParameters  pValues;
	CPrintProfiles  cPrintProfiles;
	CPrintProfileInfo  *pPrintProfileInfo;

	if ((pPrintProfileInfo = (GetPrintProfiles(cPrintProfiles)) ? cPrintProfiles.GetAt(cPrintProfiles.Find(pJobInfo->GetProfile())) : (CPrintProfileInfo *)NULL) && pPrintProfileInfo->GetPaperInfo(ptPaperSize, rtMargin[0], rtMargin[1], bMetric))
	{
		if (GetPrintProperties(pJobInfo, cLayout, nMode, szTMUnit, tTMUnit, nTMUnit, bQuality, szColumns, szContents, pValues, nOOLColors, &lfFont[0], &lfFont[1], pItemsFonts))
		{
			if (pPrintInfo == (PRINTDLG *)NULL)
			{
				if (CreatePrinterDC(pPrintProfileInfo, cDC))
				{
					if (PrintJob(cDC, pJobInfo, pPrintProfileInfo->GetPrinterName(), 0, 0, rtMargin[0], bMetric, cLayout, nMode, szTMUnit, tTMUnit, nTMUnit, bQuality, szColumns, szContents, pValues, nOOLColors, &lfFont[0], &lfFont[1], pItemsFonts))
					{
						for (; pItemsFonts.GetSize() > 0; pItemsFonts.RemoveAt(pItemsFonts.GetUpperBound()))
						{
							GlobalFree(pItemsFonts.GetAt(pItemsFonts.GetUpperBound()));
							continue;
						}
						cDC.DeleteDC();
						return TRUE;
					}
					cDC.DeleteDC();
				}
				for (; pItemsFonts.GetSize() > 0; pItemsFonts.RemoveAt(pItemsFonts.GetUpperBound()))
				{
					GlobalFree(pItemsFonts.GetAt(pItemsFonts.GetUpperBound()));
					continue;
				}
				return FALSE;
			}
			if ((pDevNames = (DEVNAMES *)GlobalLock(pPrintInfo->hDevNames)))
			{
				if ((pDevMode = (DEVMODE *)GlobalLock(pPrintInfo->hDevMode)))
				{
					if (CreatePrinterDC(pPrintInfo->hDevNames, pPrintInfo->hDevMode, cDC))
					{
						if (PrintJob(cDC, pJobInfo, (LPCTSTR)pDevMode->dmDeviceName, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nFromPage : 0, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nToPage : 0, rtMargin[0], bMetric, cLayout, nMode, szTMUnit, tTMUnit, nTMUnit, bQuality, szColumns, szContents, pValues, nOOLColors, &lfFont[0], &lfFont[1], pItemsFonts))
						{
							for (; pItemsFonts.GetSize() > 0; pItemsFonts.RemoveAt(pItemsFonts.GetUpperBound()))
							{
								GlobalFree(pItemsFonts.GetAt(pItemsFonts.GetUpperBound()));
								continue;
							}
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
			for (; pItemsFonts.GetSize() > 0; pItemsFonts.RemoveAt(pItemsFonts.GetUpperBound()))
			{
				GlobalFree(pItemsFonts.GetAt(pItemsFonts.GetUpperBound()));
				continue;
			}
		}
	}
	return FALSE;
}

CANDWnd *CANDWnd::Find(INT nType, UINT nMode, LPCTSTR pszName) CONST
{
	INT  nDisplay;
	INT  nDisplays;
	CANDWnd  *pANDWnd;
	CANDLayout  cLayout;
	CDisplayWnd  *pDisplayWnd;
	CPtrArray  pDisplays;

	for (nDisplay = 0, nDisplays = GetDisplayArea()->EnumDisplays(pDisplays), pANDWnd = (CANDWnd *)NULL; nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_AND  &&  HIWORD(pDisplayWnd->GetType()) == HIWORD(nType) && pDisplayWnd->GetMode() == nMode)
		{
			if ((pANDWnd = (CANDWnd *)pDisplayWnd)->GetLayout(cLayout) && cLayout.GetName() == pszName) break;
			continue;
		}
	}
	return((nDisplay < nDisplays) ? pANDWnd : (CANDWnd *)NULL);
}

VOID CANDWnd::SetUpdateInfo()
{
	CDisplayLock  cLock(this);

	m_szTMUnit.Empty();
	m_tTMUnit = 0;
	m_nTMUnit = 0;
	m_wTMUnit = TMUNIT_DATAQUALITY_NONE;
	UpdateMessagePane();
}
VOID CANDWnd::SetUpdateInfo(LPCTSTR pszTag, CONST CTimeTag &tTag, UINT nTag, WORD wQuality)
{
	CDisplayLock  cLock(this);

	m_szTMUnit = pszTag;
	m_tTMUnit = tTag;
	m_nTMUnit = nTag;
	m_wTMUnit = wQuality;
	UpdateMessagePane();
}

BOOL CANDWnd::GetUpdateInfo(CString &szTag, CTimeTag &tTag, UINT &nTag, WORD &wQuality) CONST
{
	CDisplayLock  cLock(this);

	szTag = m_szTMUnit;
	tTag = m_tTMUnit;
	nTag = m_nTMUnit;
	wQuality = m_wTMUnit;
	return TRUE;
}

BOOL CANDWnd::CreateToolBar()
{
	if (m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE) && m_wndToolBar.LoadToolBar(IDB_ANDFRAMELARGEIMAGES, 0, IDB_ANDFRAMESMALLIMAGES, TRUE))
	{
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_ANDSETTINGS), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_ANDLINKAGES), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_ANDPARAMETERS), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_ANDRETRIEVALS), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_ANDRETRIEVESTOP), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_ANDRETRIEVESTEPFORWARD), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_ANDRETRIEVESTEPBACKWARD), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_ANDRETRIEVEFORWARD), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_ANDRETRIEVEBACKWARD), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_ANDRETRIEVEPSEUDOREALTIME), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_ANDPRINT), TBBS_DISABLED);
		DockPane(&m_wndToolBar);
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

BOOL CANDWnd::CreateStatusBar()
{
	if (m_wndStatusBar.Create(this, CBRS_BOTTOM | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE) && m_wndStatusBar.SetIndicators(nANDStatusBarIndicators, 1))
	{
		m_wndStatusBar.EnableToolTips();
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

BOOL CANDWnd::CreateView()
{
	if (m_wndView.Create(this, TVS_HEADER | TVS_TOP | TVS_NOSELECTION | TVS_HSCROLL | TVS_VSCROLL | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE))
	{
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

BOOL CANDWnd::Customize(BOOL bDefault)
{
	CString  szTitle;
	LOGFONT  sFontInfo[4];
	CUIntArray  nColumns;
	CUIntArray  nWidths;
	CANDLayout  cLayout;

	if ((!bDefault  &&  GetLayout(cLayout, nColumns, nWidths) && GetTitleFont(&sFontInfo[0], FALSE) && GetLabelsFont(&sFontInfo[1], FALSE) && GetItemsFont(&sFontInfo[2], FALSE) && GetValuesFont(&sFontInfo[3], FALSE) && SetLayout(cLayout, nColumns, nWidths) && SetTitleFont(&sFontInfo[0], FALSE) && SetLabelsFont(&sFontInfo[1], FALSE) && SetItemsFont(&sFontInfo[2], FALSE) && SetValuesFont(&sFontInfo[3], FALSE)) || (bDefault  &&  GetLayout(cLayout) && SetLayout(cLayout)))
	{
		for (szTitle.Format(STRING(IDS_WINDOW_FULLTITLE), STRING(IDS_DISPLAY_TITLE_AND), (!cLayout.GetTitle().IsEmpty()) ? (LPCTSTR)cLayout.GetTitle() : (LPCTSTR)cLayout.GetName()); !bDefault; )
		{
			SetWindowText(szTitle);
			break;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CANDWnd::UpdateAllPanes()
{
	INT  nPane;
	INT  nPanes;

	for (nPane = 0, nPanes = sizeof(nANDStatusBarIndicators) / sizeof(UINT); nPane < nPanes; nPane++)
	{
		if (m_wndStatusBar.CommandToIndex(nANDStatusBarIndicators[nPane]) != nPane) break;
		continue;
	}
	if (nPane < nPanes)
	{
		if (m_wndStatusBar.SetIndicators(nANDStatusBarIndicators, sizeof(nANDStatusBarIndicators) / sizeof(UINT)))
		{
			UpdateBars();
			return TRUE;
		}
		return FALSE;
	}
	UpdateBars();
	return TRUE;
}

VOID CANDWnd::UpdateMessagePane()
{
	UINT  nTag;
	WORD  wQuality;
	CTimeTag  tTag;
	CString  szTag;
	CString  szMessage;

	if (GetUpdateInfo(szTag, tTag, nTag, wQuality))
	{
		szMessage.Format((szTag.IsEmpty()) ? ((tTag > 0) ? STRING(IDS_AND_STATUSBAR_FULLUPDATEMESSAGE) : ((IsRetrievingData() && HIWORD(IsRetrievingData())) ? STRING(IDS_AND_STATUSBAR_RETRIEVEMESSAGE) : STRING(IDS_AND_STATUSBAR_NODATAMESSAGE))) : ((nTag == (UINT)-1) ? STRING(IDS_AND_STATUSBAR_INITUPDATEMESSAGE) : STRING(IDS_AND_STATUSBAR_UPDATEMESSAGE)), (LPCTSTR)tTag.FormatGmt(), (LPCTSTR)szTag, nTag, ((wQuality & (TMUNIT_DATAQUALITY_GOOD | TMUNIT_SEQUENCEQUALITY_GOOD)) == (TMUNIT_DATAQUALITY_GOOD | TMUNIT_SEQUENCEQUALITY_GOOD)) ? ((wQuality & TMUNIT_TIMECORRELATION_BAD) ? (LPCTSTR)(CString(STRING(IDS_AND_STATUSBAR_QUALITYGOOD)) + STRING(IDS_AND_STATUSBAR_TIMECORRELATIONFLAG)) : STRING(IDS_AND_STATUSBAR_QUALITYGOOD)) : ((wQuality & TMUNIT_TIMECORRELATION_BAD) ? (LPCTSTR)(CString(STRING(IDS_AND_STATUSBAR_QUALITYBAD)) + STRING(IDS_AND_STATUSBAR_TIMECORRELATIONFLAG)) : STRING(IDS_AND_STATUSBAR_QUALITYBAD)));
		m_wndStatusBar.SetPaneText(ID_AND_STATUSBAR_MESSAGEPANE, szMessage);
	}
}

VOID CANDWnd::UpdateModePane()
{
	CString  szMode;
	CANDLayout  cLayout;
	CDisplayWnd  *pDisplayWnd;

	for (szMode.Empty(); (pDisplayWnd = (CDisplayWnd *)GetLink()) && GetLayout(cLayout); )
	{
		szMode.Format(STRING(IDS_DISPLAY_MODE_LINK), STRING(IDS_DISPLAY_TITLE_AND), (LPCTSTR)cLayout.GetName());
		break;
	}
	m_wndStatusBar.SetPaneText(ID_AND_STATUSBAR_MODEPANE, (GetMode() == DISPLAY_MODE_HISTORY) ? (((GetRetrieveMode() & AND_RETRIEVE_AUTOFORWARD) && !(GetRetrieveMode() & AND_RETRIEVE_STOPPED)) ? STRING(IDS_AND_STATUSBAR_AUTOFORWARDMODE) : (((GetRetrieveMode() & AND_RETRIEVE_AUTOBACKWARD) && !(GetRetrieveMode() & AND_RETRIEVE_STOPPED)) ? STRING(IDS_AND_STATUSBAR_AUTOBACKWARDMODE) : (((GetRetrieveMode() & AND_RETRIEVE_PSEUDOREALTIME) && !(GetRetrieveMode() & AND_RETRIEVE_STOPPED)) ? STRING(IDS_AND_STATUSBAR_PSEUDOREALTIMEMODE) : ((!szMode.IsEmpty()) ? (STRING(IDS_AND_STATUSBAR_NORMALMODE) + szMode) : STRING(IDS_AND_STATUSBAR_NORMALMODE))))) : ((!szMode.IsEmpty()) ? (STRING(IDS_DISPLAY_MODE_REALTIME) + szMode) : STRING(IDS_DISPLAY_MODE_REALTIME)));
	m_wndToolBar.EnableButton(IDM_ANDRETRIEVESTOP, (IsRetrievingData() && ((GetRetrieveMode() & AND_RETRIEVE_AUTOFORWARD) || (GetRetrieveMode() & AND_RETRIEVE_AUTOBACKWARD) || (GetRetrieveMode() & AND_RETRIEVE_PSEUDOREALTIME) || HIWORD(IsRetrievingData())) && !(GetRetrieveMode() & AND_RETRIEVE_STOPPED)) ? TRUE : FALSE);
	m_wndToolBar.EnableButton(IDM_ANDRETRIEVEFORWARD, (IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & AND_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & AND_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & AND_RETRIEVE_STOPPED))) ? TRUE : FALSE);
	m_wndToolBar.EnableButton(IDM_ANDRETRIEVEBACKWARD, (IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & AND_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & AND_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & AND_RETRIEVE_STOPPED))) ? TRUE : FALSE);
	m_wndToolBar.EnableButton(IDM_ANDRETRIEVESTEPFORWARD, (IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & AND_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & AND_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & AND_RETRIEVE_STOPPED))) ? TRUE : FALSE);
	m_wndToolBar.EnableButton(IDM_ANDRETRIEVESTEPBACKWARD, (IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & AND_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & AND_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & AND_RETRIEVE_STOPPED))) ? TRUE : FALSE);
	m_wndToolBar.EnableButton(IDM_ANDRETRIEVEPSEUDOREALTIME, (IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & AND_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & AND_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & AND_RETRIEVE_STOPPED))) ? TRUE : FALSE);
}

VOID CANDWnd::UpdateTypePane()
{
	CString  szType;
	CString  szLayout;

	switch (HIWORD(GetType()))
	{
	case AND_TYPE_NORMAL:
	case AND_TYPE_GENERIC:
	{ if (GetLayout(szLayout))
	{
		szType.Format((HIWORD(GetType()) == AND_TYPE_NORMAL) ? STRING(IDS_AND_STATUSBAR_TYPENORMAL) : STRING(IDS_AND_STATUSBAR_TYPEGENERIC), (LPCTSTR)szLayout);
		break;
	}
	szType = STRING(IDS_AND_STATUSBAR_TYPENORMAL);
	szType = szType.Left((szType.Find(SPACE) >= 0) ? szType.Find(SPACE) : lstrlen(STRING(IDS_AND_STATUSBAR_TYPENORMAL)));
	break;
	}
	case AND_TYPE_TEMPORARY:
	{ szType = STRING(IDS_AND_STATUSBAR_TYPETEMPORARY);
	break;
	}
	}
	m_wndStatusBar.SetPaneText(ID_AND_STATUSBAR_TYPEPANE, szType);
}

VOID CANDWnd::UpdateData()
{
	UINT  nTag;
	WORD  wQuality;
	CString  szTag[2];
	CTimeTag  tTag[2];
	CDisplayLock  cLock(this);

	if (GetUpdateInfo(szTag[0], tTag[0], nTag, wQuality) && Initialize(szTag[1], tTag[1]))
	{
		SetUpdateInfo(szTag[1], tTag[1], (szTag[0] == szTag[1] && tTag[0] == tTag[1]) ? nTag : -1, (szTag[0] == szTag[1] && tTag[0] == tTag[1]) ? wQuality : TMUNIT_DATAQUALITY_NONE);
		return;
	}
}

BOOL CANDWnd::LoadLayout(LPCTSTR pszLayout, CANDLayout &cLayout)
{
	return((HIWORD(GetType()) != AND_TYPE_NORMAL) ? ((HIWORD(GetType()) != AND_TYPE_GENERIC) ? ((HIWORD(GetType()) == AND_TYPE_TEMPORARY) ? LoadTemporaryAND(pszLayout, cLayout) : FALSE) : GetDatabase()->LoadAND(pszLayout, cLayout, DATABASE_SUBCOMPONENT_AND_GENERIC)) : GetDatabase()->LoadAND(pszLayout, cLayout, DATABASE_SUBCOMPONENT_AND_NORMAL));
}

BOOL CANDWnd::HasLayout() CONST
{
	return m_wndView.HasParameters();
}

BOOL CANDWnd::StartSchedulePrintJobs()
{
	return IsSchedulingPrintJobs() || m_cPrintThread.Start(this);
}

BOOL CANDWnd::IsSchedulingPrintJobs() CONST
{
	return((m_cPrintThread.IsThreadActive()) ? TRUE : FALSE);
}

BOOL CANDWnd::StopSchedulePrintJobs()
{
	return((IsSchedulingPrintJobs() && m_cPrintThread.Stop()) ? TRUE : FALSE);
}

BOOL CANDWnd::SetPrintJobs(CONST CByteArray &nPrintInfo)
{
	CANDPrintJobs  pPrintJobs;

	return((pPrintJobs.Unmap(nPrintInfo)) ? SetPrintJobs(pPrintJobs) : FALSE);
}

BOOL CANDWnd::GetPrintJobs(CByteArray &nPrintInfo) CONST
{
	CANDPrintJobs  pPrintJobs;

	return((GetPrintJobs(pPrintJobs)) ? pPrintJobs.Map(nPrintInfo) : FALSE);
}

BOOL CANDWnd::GetPrintProperties(CONST CANDPrintJobInfo *pJobInfo, CANDLayout &cLayout, UINT &nMode, CString &szTMUnit, CTimeTag &tTMUnit, UINT &nTMUnit, BOOL &bQuality, CStringArray &szColumns, CStringArray &szContents, CTMParameters &pValues, CUIntArray &nOOLColors, LOGFONT *pTitleFont, LOGFONT *pLabelsFont, CPtrArray &pItemsFonts) CONST
{
	INT  nRow;
	INT  nRows;
	INT  nLine;
	INT  nLines;
	INT  nColumn;
	INT  nColumns;
	INT  nParameter;
	INT  nParameters;
	UINT  nPrintMode;
	UINT  nPrintCount;
	UINT  nPrintFormat;
	WORD  wPrintQuality;
	CStringArray  szPrintColumns;
	CANDLayoutParameter  *pParameter;
	CDisplayLock  cLock(this);

	if (((nMode = GetMode()) == DISPLAY_MODE_REALTIME || nMode == DISPLAY_MODE_HISTORY) && GetUpdateInfo(szTMUnit, tTMUnit, nTMUnit, wPrintQuality) && m_wndView.GetPrintProperties(cLayout, szColumns, szContents, pValues, nOOLColors, pTitleFont, pLabelsFont, pItemsFonts))
	{
		if (((!((nPrintMode = pJobInfo->GetPrintMode()) & AND_PRINT_FIRSTSIDE) && !(nPrintMode & AND_PRINT_LASTSIDE)) || pJobInfo->GetPrintBySide(nPrintCount)) && (!(nPrintMode & AND_PRINT_CUSTOMLAYOUT) || pJobInfo->GetPrintFormat(nPrintFormat)))
		{
			for (nParameter = 0, nParameters = (INT)cLayout.GetSize(), nRows = 0, bQuality = ((wPrintQuality & (TMUNIT_DATAQUALITY_GOOD | TMUNIT_SEQUENCEQUALITY_GOOD)) == (TMUNIT_DATAQUALITY_GOOD | TMUNIT_SEQUENCEQUALITY_GOOD)) ? TRUE : FALSE; nParameter < nParameters; nParameter++)
			{
				nRows = ((pParameter = cLayout.GetAt(nParameter))) ? (((nRow = pParameter->GetRow()) >= 0) ? max(nRow + 1, nRows) : max(nParameter + 1, nRows)) : nRows;
				continue;
			}
			if (nPrintMode & AND_PRINT_CUSTOMLAYOUT)
			{
				for (nColumn = 0, nColumns = nPrintFormat, szPrintColumns.Copy(szColumns); nColumn < nColumns; nColumn++)
				{
					for (nParameter = 0, nParameters = (INT)cLayout.GetSize(); nParameter < nParameters; nParameter++)
					{
						if ((pParameter = cLayout.GetAt(nParameter)) != (CANDLayoutParameter *)NULL)
						{
							nRow = ((nRow = pParameter->GetRow()) >= 0) ? nRow : nParameter;
							if (nRow >= nColumn*(nRows / nColumns) + min(nColumn, nRows%nColumns) && nRow < (nColumn + 1)*(nRows / nColumns) + min(nColumn + 1, nRows%nColumns))
							{
								pParameter->SetRow(nRow - nColumn*(nRows / nColumns) - min(nColumn, nRows%nColumns));
								pParameter->SetColumn(nColumn);
							}
						}
					}
					if (nColumn > 0)
					{
						for (nLine = 0, nLines = (INT)((szContents.GetSize() + nColumns - 1) / nColumns), szColumns.Append(szPrintColumns); nLine < nLines; nLine++)
						{
							if ((nRow = (INT)(nLine + nColumn*(szContents.GetSize() / nColumns) + min(nColumn, szContents.GetSize() % nColumns))) < (INT)szContents.GetSize())
							{
								szContents.SetAt(nLine, szContents.GetAt(nLine) + CTextView::GetColumnDelimiter() + szContents.GetAt(nRow));
								continue;
							}
						}
					}
				}
				szContents.SetSize((szContents.GetSize() + nColumns - 1) / nColumns);
			}
			if ((nPrintMode & AND_PRINT_FIRSTSIDE) || (nPrintMode & AND_PRINT_LASTSIDE))
			{
				for (nParameter = 0, nParameters = (INT)cLayout.GetSize(), nRows = 0; nParameter < nParameters; nParameter++)
				{
					nRows = ((pParameter = cLayout.GetAt(nParameter))) ? (((nRow = pParameter->GetRow()) >= 0) ? max(nRow + 1, nRows) : max(nParameter + 1, nRows)) : nRows;
					continue;
				}
				for (nParameter = 0, nParameters = (nPrintCount < (UINT)nRows) ? nParameters : 0; nParameter < nParameters; nParameter++)
				{
					if ((pParameter = cLayout.GetAt(nParameter)) && (((nPrintMode & AND_PRINT_FIRSTSIDE) && ((pParameter->GetRow() >= 0 && pParameter->GetRow() >= (INT)nPrintCount) || (pParameter->GetRow() < 0 && nParameter >= (INT)nPrintCount))) || ((nPrintMode & AND_PRINT_LASTSIDE) && ((pParameter->GetRow() >= 0 && pParameter->GetRow() < nRows - (INT)nPrintCount) || (pParameter->GetRow() < 0 && nParameter < nRows - (INT)nPrintCount)))))
					{
						cLayout.RemoveAt(nParameter);
						delete pParameter;
						nParameters--;
						nParameter--;
						continue;
					}
					if (nPrintMode & AND_PRINT_LASTSIDE)
					{
						if ((pParameter = cLayout.GetAt(nParameter)))
						{
							pParameter->SetRow(pParameter->GetRow() - nRows + (INT)nPrintCount);
							continue;
						}
					}
				}
				if (nPrintCount < (UINT)szContents.GetSize())
				{
					szContents.RemoveAt((nPrintMode & AND_PRINT_FIRSTSIDE) ? nPrintCount : 0, (nPrintMode & AND_PRINT_FIRSTSIDE) ? (szContents.GetSize() - nPrintCount) : 0);
					szContents.RemoveAt(0, (nPrintMode & AND_PRINT_LASTSIDE) ? (szContents.GetSize() - nPrintCount) : 0);
				}
			}
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CANDWnd::StartPrintJob(CDC &cDC)
{
	DOCINFO  sJobInfo;
	CString  szJobTitle;
	CANDLayout  cLayout;

	for (GetLayout(cLayout), sJobInfo.fwType = 0, sJobInfo.cbSize = sizeof(DOCINFO), sJobInfo.lpszDocName = (LPTSTR)EMPTYSTRING, sJobInfo.lpszOutput = (LPCTSTR)NULL, sJobInfo.lpszDatatype = (LPCTSTR)NULL, szJobTitle.Format(STRING(IDS_PRINTJOB_DEFAULTTITLE), (LPCTSTR)GetAppTitle(), (LPCTSTR)GetAccountSpacecraftName(), (LPCTSTR)GetPrintDocSubTitle(cLayout), STRING(IDS_DISPLAY_TITLE_AND)); szJobTitle.GetLength() >= 0; )
	{
		sJobInfo.lpszDocName = (LPTSTR)(LPCTSTR)szJobTitle;
		break;
	}
	return((cDC.StartDoc(&sJobInfo) >= 0) ? TRUE : FALSE);
}

BOOL CANDWnd::PrintJob(CDC &cDC, CONST CANDPrintJobInfo *pJobInfo, LPCTSTR pszPrinterName, INT nFromPage, INT nToPage, CONST RECT &rtMargin, BOOL bMetric, CONST CANDLayout &cLayout, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality, CONST CStringArray &szColumns, CONST CStringArray &szContents, CONST CTMParameters &pValues, CONST CUIntArray &nOOLColors, CONST LOGFONT *pTitleFont, CONST LOGFONT *pLabelsFont, CONST CPtrArray &pItemsFonts)
{
	INT  x;
	INT  y;
	INT  nPage;
	INT  nPages;
	INT  nLine;
	INT  nLines;
	INT  nFont;
	INT  nFonts;
	INT  nBkMode;
	INT  nSpacing;
	INT  nColumn;
	INT  nColumns;
	INT  nParameter;
	INT  nParameters;
	INT  nColumnGroup;
	INT  nHeight[2];
	BOOL  bOverlap;
	BOOL  bOutput;
	UINT  nStatus;
	UINT  nAlignment;
	CPen  cLinePen;
	CPen  *pOldPen;
	CRgn  rgnArea;
	CRect  rArea;
	CRect  rCalc;
	CRect  rClip;
	CRect  rItem;
	CFont  *pOldFont;
	CFont  cFont[AND_PRINTFONTS];
	CSize  sizeText[2];
	CString  szColumn;
	COLORREF  nColor;
	COLORREF  nOldColor;
	CTimeKey  tPrint;
	CPtrArray  pFonts;
	CUIntArray  nTabs;
	TEXTMETRIC  tmFont[2];
	CStringArray  szColumnsText;
	CANDLayoutParameter  *pParameter;

	for (nPage = nPages = 0, ZeroMemory(&tmFont[0], sizeof(TEXTMETRIC)), ZeroMemory(&tmFont[1], sizeof(TEXTMETRIC)); (!nPages || nPage <= nPages) && (nPages > 0 || (nPages = (CalcPrintDocRect(cDC, rtMargin, bMetric) && cDC.GetClipBox(rArea) != ERROR && rgnArea.CreateRectRgnIndirect(rArea) && CalcPrintDocTitleFont(cDC, rArea, cFont[AND_PRINTFONT_TITLE]) && CalcPrintDocSubTitleFont(cDC, rArea, cFont[AND_PRINTFONT_SUBTITLE]) && CalcPrintDocOperatingDetailsFont(cDC, rArea, cFont[AND_PRINTFONT_OPERATINGDETAILS]) && CalcPrintDocOperatingModeFont(cDC, rArea, cFont[AND_PRINTFONT_OPERATINGMODE]) && CalcPrintDocListItemsFonts(cDC, rArea, cLayout, szColumns, szContents, pTitleFont, pLabelsFont, pItemsFonts, cFont[AND_PRINTFONT_LISTITEMSTITLE], cFont[AND_PRINTFONT_LISTITEMSLABELS], pFonts) && CalcPrintDocNoticeFonts(cDC, rArea, cFont[AND_PRINTFONT_NOTICE], cFont[AND_PRINTFONT_LOGO]) && CalcPrintDocFooterFont(cDC, rArea, cFont[AND_PRINTFONT_FOOTER]) && CalcPrintDocTitleWidth(cDC, cLayout, szColumns, szContents, &cFont[AND_PRINTFONT_LISTITEMSTITLE], &cFont[AND_PRINTFONT_LISTITEMSLABELS], pFonts, nTabs) == szColumns.GetSize()) ? nPages : -1) == 0); )
	{
		for (nFont = 0, nFonts = (!nPages) ? (INT)pFonts.GetSize() : 0; nFont < nFonts; nFont++)
		{
			if ((pOldFont = cDC.SelectObject((CFont *)pFonts.GetAt(nFont))) != (CFont *)NULL)
			{
				CopyMemory(&tmFont[0], &tmFont[1], (cDC.GetTextMetrics(&tmFont[1]) && tmFont[0].tmHeight < tmFont[1].tmHeight) ? sizeof(TEXTMETRIC) : 0);
				cDC.SelectObject(pOldFont);
			}
		}
		if (!nPages)
		{
			pFonts.InsertAt(AND_PRINTFONT_TITLE, &cFont[AND_PRINTFONT_TITLE], 1);
			pFonts.InsertAt(AND_PRINTFONT_SUBTITLE, &cFont[AND_PRINTFONT_SUBTITLE], 1);
			pFonts.InsertAt(AND_PRINTFONT_OPERATINGDETAILS, &cFont[AND_PRINTFONT_OPERATINGDETAILS], 1);
			pFonts.InsertAt(AND_PRINTFONT_OPERATINGMODE, &cFont[AND_PRINTFONT_OPERATINGMODE], 1);
			pFonts.InsertAt(AND_PRINTFONT_LISTITEMSTITLE, &cFont[AND_PRINTFONT_LISTITEMSTITLE], 1);
			pFonts.InsertAt(AND_PRINTFONT_LISTITEMSLABELS, &cFont[AND_PRINTFONT_LISTITEMSLABELS], 1);
			pFonts.InsertAt(AND_PRINTFONT_FOOTER, &cFont[AND_PRINTFONT_FOOTER], 1);
			pFonts.InsertAt(AND_PRINTFONT_NOTICE, &cFont[AND_PRINTFONT_NOTICE], 1);
			pFonts.InsertAt(AND_PRINTFONT_LOGO, &cFont[AND_PRINTFONT_LOGO], 1);
		}
		for (nLine = 0, nLines = (INT)szContents.GetSize(), nSpacing = max(tmFont[0].tmHeight / 16, 1), rCalc.SetRectEmpty(), rClip.SetRectEmpty(), bOverlap = FALSE, bOutput = TRUE; (nPages = (tmFont[0].tmHeight > 0) ? nPages : -1) >= 0 && nLine < nLines; nLine++, bOutput = TRUE)
		{
			for (nColumn = 0, nColumns = (INT)szColumns.GetSize(), ExtractPrintDocText(szContents.GetAt(nLine), szColumnsText), nColumnGroup = -1, nHeight[0] = nHeight[1] = 0; nPages >= 0 && nColumn < nColumns; nColumn++, nHeight[1] = 0)
			{
				if (rClip.Height() > 0)
				{
					for (nParameter = 0, nParameters = (INT)cLayout.GetSize(), nColumnGroup = (szColumns.GetAt(nColumn) == STRING(IDS_AND_TITLEITEM_ID)) ? (nColumnGroup + 1) : nColumnGroup; nParameter < nParameters; nParameter++)
					{
						if ((pParameter = cLayout.GetAt(nParameter)) && ((pParameter->GetColumn() < 0 && !nColumnGroup && ((pParameter->GetRow() >= 0 && pParameter->GetRow() == nLine) || (pParameter->GetRow() < 0 && nLine == nParameter))) || (pParameter->GetColumn() == nColumnGroup  &&  pParameter->GetRow() == nLine))) break;
						continue;
					}
					if ((pOldFont = (szColumns.GetAt(nColumn) == STRING(IDS_AND_TITLEITEM_DESCRIPTION) && nParameter < nParameters  &&  pParameter->IsLabel()) ? cDC.SelectObject((CFont *)pFonts.GetAt(AND_PRINTFONT_LISTITEMSLABELS)) : cDC.SelectObject((CFont *)pFonts.GetAt(AND_PRINTFONTS + nColumn % (pFonts.GetSize() - AND_PRINTFONTS)))))
					{
						GetPrintDocParameterAttributes(cLayout, szColumns, pValues, nOOLColors, nLine, nColumn, nAlignment, nStatus, nColor);
						nOldColor = cDC.SetTextColor((cDC.GetDeviceCaps(NUMCOLORS) > 2) ? nColor : cDC.GetTextColor());
						sizeText[0] = (nColumn < szColumnsText.GetSize()) ? cDC.GetTextExtent((szColumn = szColumnsText.GetAt(nColumn) + SPACE)) : cDC.GetTextExtent((szColumn = EMPTYSTRING) + SPACE);
						sizeText[1] = (nColumn < szColumnsText.GetSize()) ? cDC.GetTextExtent(szColumnsText.GetAt(nColumn)) : cDC.GetTextExtent(EMPTYSTRING);
						rCalc.SetRect(rCalc.left, (!nColumn) ? (rCalc.top + nSpacing) : rCalc.top, rCalc.right, (!nColumn) ? (rCalc.top + nSpacing + tmFont[0].tmHeight*((rClip.bottom - (rCalc.top + nSpacing)) / tmFont[0].tmHeight)) : (rCalc.top + tmFont[0].tmHeight*((rClip.bottom - rCalc.top) / tmFont[0].tmHeight)));
						rItem.SetRect((nColumn > 0) ? (rCalc.left + nTabs.GetAt(nColumn - 1)) : rCalc.left, rCalc.top, rCalc.left + nTabs.GetAt(nColumn), rCalc.top + sizeText[0].cy);
						if (nPages > 0 && (nFromPage <= 0 || nToPage <= 0 || nFromPage > nToPage || (nPage >= nFromPage  &&  nPage <= nToPage)))
						{
							cDC.DrawText(szColumn, CRect(rItem.left, rItem.top, rItem.right, rCalc.bottom), nAlignment | DT_NOPREFIX | DT_SINGLELINE);
							if (szColumns.GetAt(nColumn) == STRING(IDS_AND_TITLEITEM_VALUE) && (pJobInfo->GetPrintMode() & AND_PRINT_UNDERLINEOOL) && cDC.GetTextMetrics(&tmFont[1]))
							{
								if ((nStatus & TMPARAMETER_STATUS_SOFTLIMIT) || (nStatus & TMPARAMETER_STATUS_HARDLIMIT) || (nStatus & TMPARAMETER_STATUS_DELTALIMIT) || (nStatus & TMPARAMETER_STATUS_CONSISTENCYLIMIT))
								{
									if (cLinePen.CreatePen(PS_SOLID, tmFont[1].tmDescent / 3, cDC.GetTextColor()))
									{
										if ((pOldPen = cDC.SelectObject(&cLinePen)))
										{
											nBkMode = cDC.SetBkMode(TRANSPARENT);
											cDC.MoveTo((x = (nAlignment == DT_CENTER) ? (rItem.left + (rItem.Width() - sizeText[0].cx) / 2) : ((nAlignment == DT_RIGHT) ? (rItem.right - sizeText[0].cx) : rItem.left)), (y = rItem.bottom - max((2 * tmFont[1].tmDescent) / 3, 1)));
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
						if (cDC.SelectClipRgn(&rgnArea) != ERROR  &&  DrawPrintDocPage(cDC, pJobInfo, tPrint, pszPrinterName, rtMargin, bMetric, cLayout, nMode, pszTMUnit, tTMUnit, nTMUnit, bQuality, szColumns, nOOLColors, pFonts, nTabs, nPages, (nPages > 0 && (nFromPage <= 0 || nToPage <= 0 || nFromPage > nToPage || (nPage >= nFromPage - 1 && nPage < nToPage))) ? (nPage + 1) : 0, rClip) && cDC.IntersectClipRect(rClip) != ERROR)
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
							if (DrawPrintDocPage(cDC, pJobInfo, tPrint, pszPrinterName, rtMargin, bMetric, cLayout, nMode, pszTMUnit, tTMUnit, nTMUnit, bQuality, szColumns, nOOLColors, pFonts, nTabs, 1, 1, rClip))
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

BOOL CANDWnd::EndPrintJob(CDC &cDC)
{
	return((cDC.EndDoc() >= 0) ? TRUE : FALSE);
}

BOOL CANDWnd::DrawPrintDocPage(CDC &cDC, CONST CANDPrintJobInfo *pJobInfo, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, CONST RECT &rtMargin, BOOL bMetric, CONST CANDLayout &cLayout, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality, CONST CStringArray &szColumns, CONST CUIntArray &nOOLColors, CONST CPtrArray &pFonts, CONST CUIntArray &nTabs, INT nPages, INT nPage, LPRECT prClip)
{
	return((CalcPrintDocRect(cDC, rtMargin, bMetric) && cDC.GetClipBox(prClip) != ERROR  &&  DrawPrintDocTitle(cDC, prClip, GetPrintDocTitle(), (CFont *)pFonts.GetAt(AND_PRINTFONT_TITLE), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocSubTitle(cDC, prClip, GetPrintDocSubTitle(cLayout), (CFont *)pFonts.GetAt(AND_PRINTFONT_SUBTITLE), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocOperatingDetails(cDC, prClip, GetPrintDocOperatingDetails(pJobInfo, nMode, pszTMUnit, tTMUnit, nTMUnit, bQuality), (CFont *)pFonts.GetAt(AND_PRINTFONT_OPERATINGDETAILS), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocOperatingMode(cDC, prClip, GetPrintDocOperatingMode(pJobInfo, nOOLColors), nOOLColors, (CFont *)pFonts.GetAt(AND_PRINTFONT_OPERATINGMODE), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocListItemsTitle(cDC, prClip, szColumns, (CFont *)pFonts.GetAt(AND_PRINTFONT_LISTITEMSTITLE), nTabs, (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocNotice(cDC, prClip, GetPrintDocNotice(), (CFont *)pFonts.GetAt(AND_PRINTFONT_NOTICE), (CFont *)pFonts.GetAt(AND_PRINTFONT_LOGO), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocFooter(cDC, prClip, GetPrintDocFooter(tTime, pszPrinterName, nPages, nPage), (CFont *)pFonts.GetAt(AND_PRINTFONT_FOOTER), (nPage <= 0) ? TRUE : FALSE)) ? TRUE : FALSE);
}

BOOL CANDWnd::DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc)
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

BOOL CANDWnd::DrawPrintDocSubTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc)
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

BOOL CANDWnd::DrawPrintDocOperatingDetails(CDC &cDC, LPRECT prClip, LPCTSTR pszComments, CFont *pFont, BOOL bCalc)
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

BOOL CANDWnd::DrawPrintDocOperatingMode(CDC &cDC, LPRECT prClip, LPCTSTR pszMode, CONST CUIntArray &nOOLColors, CFont *pFont, BOOL bCalc)
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
		szToken = szToken.Left((szToken = STRING(IDS_AND_PRINTDOCUMENT_OOLLEGEND)).Find(SPACE));
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

BOOL CANDWnd::DrawPrintDocListItemsTitle(CDC &cDC, LPRECT prClip, CONST CStringArray &szColumns, CFont *pFont, CONST CUIntArray &nTabs, BOOL bCalc)
{
	CSize  rCalc;
	CFont  *pOldFont;
	CString  szItems;

	if ((pOldFont = cDC.SelectObject(pFont)))
	{
		szItems = GetPrintDocListItemsTitle(szColumns);
		rCalc = (!bCalc) ? cDC.TabbedTextOut(prClip->left, prClip->top + cDC.GetTextExtent(szItems, szItems.GetLength()).cy, szItems, (INT)nTabs.GetSize(), (LPINT)nTabs.GetData(), prClip->left) : CSize(nTabs.GetAt(nTabs.GetSize() - 1), cDC.GetTextExtent(szItems, szItems.GetLength()).cy);
		prClip->top += 2 * rCalc.cy;
		cDC.SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CANDWnd::DrawPrintDocNotice(CDC &cDC, LPRECT prClip, LPCTSTR pszNotice, CFont *pFont, CFont *pLogoFont, BOOL bCalc)
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

BOOL CANDWnd::DrawPrintDocFooter(CDC &cDC, LPRECT prClip, LPCTSTR pszFooter, CFont *pFont, BOOL bCalc)
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

CString CANDWnd::GetPrintDocTitle() CONST
{
	CString  szTitle;

	szTitle.Format(STRING(IDS_AND_PRINTDOCUMENT_TITLE), (LPCTSTR)GetAccountSpacecraftName());
	return szTitle;
}

CString CANDWnd::GetPrintDocSubTitle(CONST CANDLayout &cLayout) CONST
{
	return cLayout.GetTitle();
}

CString CANDWnd::GetPrintDocOperatingDetails(CONST CANDPrintJobInfo *pJobInfo, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality) CONST
{
	CString  szMode;
	CString  szUpdate;

	szMode = (nMode == DISPLAY_MODE_REALTIME) ? STRING(IDS_DISPLAY_MODE_REALTIME) : STRING(IDS_DISPLAY_MODE_HISTORY);
	szUpdate.Format((!lstrlen(pszTMUnit)) ? ((tTMUnit > 0) ? STRING(IDS_AND_PRINTDOCUMENT_FULLUPDATECOMMENT) : STRING(IDS_AND_PRINTDOCUMENT_NODATACOMMENT)) : ((nTMUnit == (UINT)-1) ? STRING(IDS_AND_PRINTDOCUMENT_INITUPDATECOMMENT) : STRING(IDS_AND_PRINTDOCUMENT_UPDATECOMMENT)), (LPCTSTR)tTMUnit.FormatGmt(), pszTMUnit, nTMUnit, (bQuality) ? STRING(IDS_AND_PRINTDOCUMENT_QUALITYGOOD) : STRING(IDS_AND_PRINTDOCUMENT_QUALITYBAD));
	return((!pJobInfo->GetComments().IsEmpty()) ? (szUpdate + EOL + szMode + EOL + pJobInfo->GetComments()) : (szUpdate + EOL + szMode));
}

CString CANDWnd::GetPrintDocOperatingMode(CONST CANDPrintJobInfo *pJobInfo, CONST CUIntArray &nOOLColors) CONST
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

	if ((nFlags = pJobInfo->GetPrintFlags()) & AND_PRINT_ATTIME)
	{
		if (pJobInfo->GetPrintAtTime(tTime))
		{
			szInfo.Format(STRING(IDS_AND_PRINTDOCUMENT_PRINTATTIME), (LPCTSTR)tTime.FormatGmt());
			szInfo += EOL;
		}
		if ((pJobInfo->GetPrintAtTime(tTime, tInterval) || pJobInfo->GetPrintAtTime(tTime, tInterval, nStopCount) || pJobInfo->GetPrintAtTime(tTime, tInterval, tStopTime)) && pJobInfo->GetPrintLastTime(tLastTime))
		{
			szInfo.Format(STRING(IDS_AND_PRINTDOCUMENT_PRINTATTIME), (LPCTSTR)CTimeKey(tTime.GetTime() + ((tLastTime.GetTime() - tTime.GetTime()) / tInterval.GetTotalSeconds())*tInterval.GetTotalSeconds()).FormatGmt());
			szInfo += EOL;
		}
	}
	if (nFlags & AND_PRINT_ATDAILYTIME)
	{
		if (pJobInfo->GetPrintAtDailyTime(tDailyTime) || pJobInfo->GetPrintAtDailyTime(tDailyTime, nStopCount) || pJobInfo->GetPrintAtDailyTime(tDailyTime, tStopTime))
		{
			szInfo.Format(STRING(IDS_AND_PRINTDOCUMENT_PRINTATDAILYTIME), (LPCTSTR)CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + tDailyTime.GetTotalSeconds()).FormatGmt(STRING(IDS_TIMEKEY_TIMEFORMAT)));
			szInfo += EOL;
		}
	}
	if (nFlags & AND_PRINT_ATEVENT)
	{
		if (pJobInfo->GetPrintAtEvent(szEvent))
		{
			szInfo.Format(STRING(IDS_AND_PRINTDOCUMENT_PRINTATEVENT), (LPCTSTR)szEvent);
			szInfo += EOL;
		}
	}
	if (!nFlags)
	{
		szInfo = STRING(IDS_AND_PRINTDOCUMENT_DEFAULTTIME);
		szInfo += EOL;
	}
	if ((nMode = pJobInfo->GetPrintMode()) & AND_PRINT_ALL)
	{
		szInfo += STRING(IDS_AND_PRINTDOCUMENT_PRINTALL);
		szInfo += EOL;
	}
	if (((nMode & AND_PRINT_FIRSTSIDE) || (nMode & AND_PRINT_LASTSIDE)) && pJobInfo->GetPrintBySide(nCount))
	{
		szSide.Format((nMode & AND_PRINT_FIRSTSIDE) ? STRING(IDS_AND_PRINTDOCUMENT_PRINTBYFIRSTSIDE) : STRING(IDS_AND_PRINTDOCUMENT_PRINTBYLASTSIDE), nCount);
		szSide = (nCount == 1) ? ((nMode & AND_PRINT_FIRSTSIDE) ? STRING(IDS_AND_PRINTDOCUMENT_PRINTBYFIRSTITEM) : STRING(IDS_AND_PRINTDOCUMENT_PRINTBYLASTITEM)) : (LPCTSTR)szSide;
		szInfo += szSide + EOL;
	}
	if (nMode & AND_PRINT_COLORLEGEND)
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
		szLegend.Format(STRING(IDS_AND_PRINTDOCUMENT_OOLLEGEND), (LPCTSTR)szOOLColors.GetAt(AND_OOLCOLOR_NOLIMIT), (LPCTSTR)szOOLColors.GetAt(AND_OOLCOLOR_SOFTLIMIT), (LPCTSTR)szOOLColors.GetAt(AND_OOLCOLOR_HARDLIMIT), (LPCTSTR)szOOLColors.GetAt(AND_OOLCOLOR_DELTALIMIT), (LPCTSTR)szOOLColors.GetAt(AND_OOLCOLOR_CONSISTENCYLIMIT));
		szInfo += szLegend + EOL;
	}
	return szInfo;
}

CString CANDWnd::GetPrintDocListItemsTitle(CONST CStringArray &szColumns) CONST
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

CString CANDWnd::GetPrintDocNotice() CONST
{
	CVersionInfo  cVersionInfo;

	return cVersionInfo.QueryComments();
}

CString CANDWnd::GetPrintDocFooter(CONST CTimeKey &tTime, LPCTSTR pszPrinterName, INT nPages, INT nPage) CONST
{
	CString  szFooter;

	szFooter.Format(STRING(IDS_AND_PRINTDOCUMENT_FOOTER), (LPCTSTR)tTime.Format(IDS_TIMEKEY_DATEFORMAT), (LPCTSTR)tTime.Format(IDS_TIMEKEY_TIMEFORMAT), pszPrinterName, nPage, nPages);
	return szFooter;
}

BOOL CANDWnd::GetPrintDocParameterAttributes(CONST CANDLayout &cLayout, CONST CStringArray &szColumns, CONST CTMParameters &pValues, CONST CUIntArray &nOOLColors, INT nRow, INT nColumn, UINT &nAlignment, UINT &nStatus, COLORREF &nColor) CONST
{
	INT  nIndex;
	INT  nCount;
	INT  nParameter;
	INT  nParameters;
	INT  nColumnGroup;
	ULONGLONG  nValue;
	CTMParameter  *pTMParameter;
	CANDLayoutParameter  *pParameter;

	for (nIndex = 0, nCount = (INT)min(nColumn + 1, szColumns.GetSize()), nColumnGroup = 0; nIndex < nCount; nIndex++)
	{
		nColumnGroup = (szColumns.GetAt(nIndex) == STRING(IDS_AND_TITLEITEM_ID) && nIndex > 0) ? (nColumnGroup + 1) : nColumnGroup;
		continue;
	}
	for (nParameter = 0, nParameters = (INT)cLayout.GetSize(), nColor = GetSysColor(COLOR_WINDOW), nAlignment = DT_LEFT, nStatus = TMPARAMETER_STATUS_NONE; nParameter < nParameters; nParameter++)
	{
		if ((pParameter = cLayout.GetAt(nParameter)) && ((pParameter->GetColumn() < 0 && !nColumnGroup && ((pParameter->GetRow() >= 0 && pParameter->GetRow() == nRow) || (pParameter->GetRow() < 0 && nRow == nParameter))) || (pParameter->GetColumn() == nColumnGroup  &&  pParameter->GetRow() == nRow)))
		{
			if ((pTMParameter = pValues.GetAt(pValues.Find(pParameter->GetName()))) && pTMParameter->GetRawValue(pParameter->GetOccurrence(), nValue, nStatus))
			{
				if (szColumns.GetAt(nColumn) == STRING(IDS_AND_TITLEITEM_VALUE))
				{
					if (nStatus & TMPARAMETER_STATUS_NOLIMIT)
					{
						nColor = nOOLColors.GetAt(AND_OOLCOLOR_NOLIMIT);
						nAlignment = pParameter->GetAlignment();
						break;
					}
					if (nStatus & TMPARAMETER_STATUS_SOFTLIMIT)
					{
						nColor = nOOLColors.GetAt(AND_OOLCOLOR_SOFTLIMIT);
						nAlignment = pParameter->GetAlignment();
						break;
					}
					if (nStatus & TMPARAMETER_STATUS_HARDLIMIT)
					{
						nColor = nOOLColors.GetAt(AND_OOLCOLOR_HARDLIMIT);
						nAlignment = pParameter->GetAlignment();
						break;
					}
					if (nStatus & TMPARAMETER_STATUS_DELTALIMIT)
					{
						nColor = nOOLColors.GetAt(AND_OOLCOLOR_DELTALIMIT);
						nAlignment = pParameter->GetAlignment();
						break;
					}
					if (nStatus & TMPARAMETER_STATUS_CONSISTENCYLIMIT)
					{
						nColor = nOOLColors.GetAt(AND_OOLCOLOR_CONSISTENCYLIMIT);
						nAlignment = pParameter->GetAlignment();
						break;
					}
				}
			}
			if (pParameter->GetColor() == GetSysColor(COLOR_WINDOW))
			{
				if (szColumns.GetAt(nColumn) == STRING(IDS_AND_TITLEITEM_ID))
				{
					nColor = GetDatabase()->GetANDIDColumnColor();
					nAlignment = DT_LEFT;
					break;
				}
				if (szColumns.GetAt(nColumn) == STRING(IDS_AND_TITLEITEM_DESCRIPTION))
				{
					nColor = GetDatabase()->GetANDDescriptionColumnColor();
					nAlignment = DT_LEFT;
					break;
				}
				if (szColumns.GetAt(nColumn) == STRING(IDS_AND_TITLEITEM_UNIT))
				{
					nColor = GetDatabase()->GetANDUnitColumnColor();
					nAlignment = DT_LEFT;
					break;
				}
				if (szColumns.GetAt(nColumn) == STRING(IDS_AND_TITLEITEM_CHANGETMUNIT))
				{
					nColor = GetDatabase()->GetANDChangeTMUnitColumnColor();
					nAlignment = DT_LEFT;
					break;
				}
				if (szColumns.GetAt(nColumn) == STRING(IDS_AND_TITLEITEM_CHANGETIME))
				{
					nColor = GetDatabase()->GetANDChangeTimeColumnColor();
					nAlignment = DT_LEFT;
					break;
				}
				if (szColumns.GetAt(nColumn) == STRING(IDS_AND_TITLEITEM_UPDATETMUNIT))
				{
					nColor = GetDatabase()->GetANDUpdateTMUnitColumnColor();
					nAlignment = DT_LEFT;
					break;
				}
				if (szColumns.GetAt(nColumn) == STRING(IDS_AND_TITLEITEM_UPDATETIME))
				{
					nColor = GetDatabase()->GetANDUpdateTimeColumnColor();
					nAlignment = DT_LEFT;
					break;
				}
				if (szColumns.GetAt(nColumn) == STRING(IDS_AND_TITLEITEM_EXPECTEDVALUES))
				{
					nColor = GetDatabase()->GetANDExpectedValuesColumnColor();
					nAlignment = DT_LEFT;
					break;
				}
			}
			nColor = pParameter->GetColor();
			nAlignment = pParameter->GetAlignment();
			break;
		}
	}
	return((nParameter < nParameters) ? TRUE : FALSE);
}

INT CANDWnd::ExtractPrintDocText(LPCTSTR pszText, CStringArray &szColumnsText) CONST
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

BOOL CANDWnd::CalcPrintDocTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 48, (INT)((-5.3*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CANDWnd::CalcPrintDocSubTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 64, (INT)((-4.0*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CANDWnd::CalcPrintDocOperatingDetailsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 76, (INT)((-3.3*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CANDWnd::CalcPrintDocOperatingModeFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 76, (INT)((-3.3*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CANDWnd::CalcPrintDocListItemsFonts(CDC &cDC, CONST RECT &rArea, CONST CANDLayout &cLayout, CONST CStringArray &szColumns, CONST CStringArray &szContents, CONST LOGFONT *pTitleFont, CONST LOGFONT *pLabelsFont, CONST CPtrArray &pItemsFonts, CFont &cTitleFont, CFont &cLabelsFont, CPtrArray &cItemsFonts) CONST
{
	INT  nFont;
	INT  nFonts;
	INT  nWidth;
	INT  nHeight;
	CFont  *pFont;
	CFont  cFont[2];
	LOGFONT  lfFont;
	CPtrArray  pFonts;
	CUIntArray  nTabs;

	for (nHeight = max(-(rArea.right - rArea.left) / 64, (INT)((-4.0*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))); nHeight < 0; nHeight++)
	{
		if (cFont[0].CreateFont(nHeight, 0, pTitleFont->lfEscapement, pTitleFont->lfOrientation, FW_BOLD, pTitleFont->lfItalic, pTitleFont->lfUnderline, pTitleFont->lfStrikeOut, pTitleFont->lfCharSet, pTitleFont->lfOutPrecision, pTitleFont->lfClipPrecision, pTitleFont->lfQuality, pTitleFont->lfPitchAndFamily, pTitleFont->lfFaceName))
		{
			if (cFont[1].CreateFont((4 * nHeight) / 5, 0, pLabelsFont->lfEscapement, pLabelsFont->lfOrientation, pLabelsFont->lfWeight, pLabelsFont->lfItalic, pLabelsFont->lfUnderline, pLabelsFont->lfStrikeOut, pLabelsFont->lfCharSet, pLabelsFont->lfOutPrecision, pLabelsFont->lfClipPrecision, pLabelsFont->lfQuality, pLabelsFont->lfPitchAndFamily, pLabelsFont->lfFaceName))
			{
				for (nFont = 0, nFonts = (INT)pItemsFonts.GetSize(); nFont < nFonts; nFont++)
				{
					CopyMemory(&lfFont, pItemsFonts.GetAt(nFont), sizeof(LOGFONT));
					if ((pFont = new CFont) && pFont->CreateFont((4 * nHeight) / 5, 0, lfFont.lfEscapement, lfFont.lfOrientation, lfFont.lfWeight, lfFont.lfItalic, lfFont.lfUnderline, lfFont.lfStrikeOut, lfFont.lfCharSet, lfFont.lfOutPrecision, lfFont.lfClipPrecision, lfFont.lfQuality, lfFont.lfPitchAndFamily, lfFont.lfFaceName))
					{
						pFonts.Add(pFont);
						continue;
					}
					delete pFont;
					break;
				}
				if (nFont == nFonts)
				{
					if (CalcPrintDocTitleWidth(cDC, cLayout, szColumns, szContents, &cFont[0], &cFont[1], pFonts, nTabs) > 0)
					{
						if ((nWidth = nTabs.GetAt(nTabs.GetSize() - 1)) > rArea.right - rArea.left)
						{
							for (nHeight = (nHeight*(rArea.right - rArea.left)) / nWidth - 1; pFonts.GetSize() > 0; )
							{
								if ((pFont = (CFont *)pFonts.GetAt(pFonts.GetUpperBound()))) delete pFont;
								pFonts.RemoveAt(pFonts.GetUpperBound());
							}
							cFont[0].DeleteObject();
							cFont[1].DeleteObject();
							continue;
						}
						cTitleFont.Attach(cFont[0].Detach());
						cLabelsFont.Attach(cFont[1].Detach());
						cItemsFonts.Copy(pFonts);
						break;
					}
				}
				while (pFonts.GetSize() > 0)
				{
					if ((pFont = (CFont *)pFonts.GetAt(pFonts.GetUpperBound()))) delete pFont;
					pFonts.RemoveAt(pFonts.GetUpperBound());
				}
				cFont[1].DeleteObject();
			}
			cFont[0].DeleteObject();
		}
	}
	return((cTitleFont.GetSafeHandle() && cLabelsFont.GetSafeHandle() && cItemsFonts.GetSize() == pItemsFonts.GetSize()) ? TRUE : FALSE);
}

BOOL CANDWnd::CalcPrintDocNoticeFonts(CDC &cDC, CONST RECT &rArea, CFont &cFont, CFont &cLogoFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 96, (INT)((-2.6*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL) && cLogoFont.CreateFont(max(-(rArea.right - rArea.left) / 96, (INT)((-2.6*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, STRING(IDS_FONTFACE_COMPANYLOGO));
}

BOOL CANDWnd::CalcPrintDocFooterFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 80, (INT)((-3.0*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

INT CANDWnd::CalcPrintDocTitleWidth(CDC &cDC, LPCTSTR pszColumn, CFont *pTitleFont) CONST
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
INT CANDWnd::CalcPrintDocTitleWidth(CDC &cDC, CONST CANDLayout &cLayout, CONST CStringArray &szColumns, CONST CStringArray &szContents, CFont *pTitleFont, CFont *pLabelsFont, CONST CPtrArray &pItemsFonts, CUIntArray &nTabs) CONST
{
	INT  nIndex;
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
	if ((pOldFont = cDC.SelectObject(pLabelsFont)))
	{
		if (cDC.GetTextMetrics(&tmFont)) nIndent = max(tmFont.tmAveCharWidth, nIndent);
		cDC.SelectObject(pOldFont);
	}
	for (nColumn = 0, nColumns = (INT)pItemsFonts.GetSize(); nColumn < nColumns; nColumn++)
	{
		if ((pOldFont = cDC.SelectObject((CFont *)pItemsFonts.GetAt(nColumn))) != (CFont *)NULL)
		{
			if (cDC.GetTextMetrics(&tmFont)) nIndent = max(tmFont.tmAveCharWidth, nIndent);
			cDC.SelectObject(pOldFont);
		}
	}
	for (nColumn = 0, nColumns = (INT)szColumns.GetSize(), szLines.Copy(szContents), nIndex = -1; nColumn < nColumns; nColumn++)
	{
		if (szColumns.GetAt(nColumn) == STRING(IDS_AND_TITLEITEM_ID))
		{
			nWidth[0] = CalcPrintDocTitleWidth(cDC, szColumns.GetAt(nColumn), pTitleFont);
			nWidth[1] = CalcPrintDocColumnWidth(cDC, cLayout, ++nIndex, szLines, (CFont *)NULL, (CFont *)pItemsFonts.GetAt(nColumn%pItemsFonts.GetSize()));
			if (nTabs.GetSize() > 0) nTabs.SetAt(nTabs.GetUpperBound(), nTabs.GetAt(nTabs.GetUpperBound()) + 6 * nIndent);
			nTabs.Add((nTabs.GetSize() > 0) ? (2 * nIndent + nTabs.GetAt(nTabs.GetSize() - 1) + max(nWidth[0], nWidth[1])) : (2 * nIndent + max(nWidth[0], nWidth[1])));
		}
		if (szColumns.GetAt(nColumn) == STRING(IDS_AND_TITLEITEM_DESCRIPTION))
		{
			nWidth[0] = CalcPrintDocTitleWidth(cDC, szColumns.GetAt(nColumn), pTitleFont);
			nWidth[1] = CalcPrintDocColumnWidth(cDC, cLayout, nIndex, szLines, pLabelsFont, (CFont *)pItemsFonts.GetAt(nColumn%pItemsFonts.GetSize()));
			nTabs.Add((nTabs.GetSize() > 0) ? (2 * nIndent + nTabs.GetAt(nTabs.GetSize() - 1) + max(nWidth[0], nWidth[1])) : (2 * nIndent + max(nWidth[0], nWidth[1])));
		}
		if (szColumns.GetAt(nColumn) == STRING(IDS_AND_TITLEITEM_VALUE))
		{
			nWidth[0] = CalcPrintDocTitleWidth(cDC, szColumns.GetAt(nColumn), pTitleFont);
			nWidth[1] = CalcPrintDocColumnWidth(cDC, cLayout, nIndex, szLines, (CFont *)NULL, (CFont *)pItemsFonts.GetAt(nColumn%pItemsFonts.GetSize()));
			nTabs.Add((nTabs.GetSize() > 0) ? (2 * nIndent + nTabs.GetAt(nTabs.GetSize() - 1) + max(nWidth[0], nWidth[1])) : (2 * nIndent + max(nWidth[0], nWidth[1])));
		}
		if (szColumns.GetAt(nColumn) == STRING(IDS_AND_TITLEITEM_UNIT))
		{
			nWidth[0] = CalcPrintDocTitleWidth(cDC, szColumns.GetAt(nColumn), pTitleFont);
			nWidth[1] = CalcPrintDocColumnWidth(cDC, cLayout, nIndex, szLines, (CFont *)NULL, (CFont *)pItemsFonts.GetAt(nColumn%pItemsFonts.GetSize()));
			nTabs.Add((nTabs.GetSize() > 0) ? (2 * nIndent + nTabs.GetAt(nTabs.GetSize() - 1) + max(nWidth[0], nWidth[1])) : (2 * nIndent + max(nWidth[0], nWidth[1])));
		}
		if (szColumns.GetAt(nColumn) == STRING(IDS_AND_TITLEITEM_CHANGETMUNIT))
		{
			nWidth[0] = CalcPrintDocTitleWidth(cDC, szColumns.GetAt(nColumn), pTitleFont);
			nWidth[1] = CalcPrintDocColumnWidth(cDC, cLayout, nIndex, szLines, (CFont *)NULL, (CFont *)pItemsFonts.GetAt(nColumn%pItemsFonts.GetSize()));
			nTabs.Add((nTabs.GetSize() > 0) ? (2 * nIndent + nTabs.GetAt(nTabs.GetSize() - 1) + max(nWidth[0], nWidth[1])) : (2 * nIndent + max(nWidth[0], nWidth[1])));
		}
		if (szColumns.GetAt(nColumn) == STRING(IDS_AND_TITLEITEM_CHANGETIME))
		{
			nWidth[0] = CalcPrintDocTitleWidth(cDC, szColumns.GetAt(nColumn), pTitleFont);
			nWidth[1] = CalcPrintDocColumnWidth(cDC, cLayout, nIndex, szLines, (CFont *)NULL, (CFont *)pItemsFonts.GetAt(nColumn%pItemsFonts.GetSize()));
			nTabs.Add((nTabs.GetSize() > 0) ? (2 * nIndent + nTabs.GetAt(nTabs.GetSize() - 1) + max(nWidth[0], nWidth[1])) : (2 * nIndent + max(nWidth[0], nWidth[1])));
		}
		if (szColumns.GetAt(nColumn) == STRING(IDS_AND_TITLEITEM_UPDATETMUNIT))
		{
			nWidth[0] = CalcPrintDocTitleWidth(cDC, szColumns.GetAt(nColumn), pTitleFont);
			nWidth[1] = CalcPrintDocColumnWidth(cDC, cLayout, nIndex, szLines, (CFont *)NULL, (CFont *)pItemsFonts.GetAt(nColumn%pItemsFonts.GetSize()));
			nTabs.Add((nTabs.GetSize() > 0) ? (2 * nIndent + nTabs.GetAt(nTabs.GetSize() - 1) + max(nWidth[0], nWidth[1])) : (2 * nIndent + max(nWidth[0], nWidth[1])));
		}
		if (szColumns.GetAt(nColumn) == STRING(IDS_AND_TITLEITEM_UPDATETIME))
		{
			nWidth[0] = CalcPrintDocTitleWidth(cDC, szColumns.GetAt(nColumn), pTitleFont);
			nWidth[1] = CalcPrintDocColumnWidth(cDC, cLayout, nIndex, szLines, (CFont *)NULL, (CFont *)pItemsFonts.GetAt(nColumn%pItemsFonts.GetSize()));
			nTabs.Add((nTabs.GetSize() > 0) ? (2 * nIndent + nTabs.GetAt(nTabs.GetSize() - 1) + max(nWidth[0], nWidth[1])) : (2 * nIndent + max(nWidth[0], nWidth[1])));
		}
		if (szColumns.GetAt(nColumn) == STRING(IDS_AND_TITLEITEM_EXPECTEDVALUES))
		{
			nWidth[0] = CalcPrintDocTitleWidth(cDC, szColumns.GetAt(nColumn), pTitleFont);
			nWidth[1] = CalcPrintDocColumnWidth(cDC, cLayout, nIndex, szLines, pLabelsFont, (CFont *)pItemsFonts.GetAt(nColumn%pItemsFonts.GetSize()));
			nTabs.Add((nTabs.GetSize() > 0) ? (2 * nIndent + nTabs.GetAt(nTabs.GetSize() - 1) + max(nWidth[0], nWidth[1])) : (2 * nIndent + max(nWidth[0], nWidth[1])));
		}
	}
	if (nTabs.GetSize() > 0)
	{
		nTabs.SetAt(nTabs.GetSize() - 1, nTabs.GetAt(nTabs.GetSize() - 1) - nIndent);
		return((INT)nTabs.GetSize());
	}
	return 0;
}

INT CANDWnd::CalcPrintDocColumnWidth(CDC &cDC, CONST CANDLayout &cLayout, INT nColumn, CStringArray &szContents, CFont *pLabelsFont, CFont *pItemsFont) CONST
{
	INT  nPos;
	INT  nLine;
	INT  nLines;
	INT  nWidth;
	INT  nParameter;
	INT  nParameters;
	CFont  *pOldFont;
	CANDLayoutParameter  *pParameter;

	for (nLine = 0, nLines = (INT)szContents.GetSize(), nWidth = 0; nLine < nLines; nLine++)
	{
		for (nParameter = 0, nParameters = (INT)cLayout.GetSize(); nParameter < nParameters; nParameter++)
		{
			if ((pParameter = cLayout.GetAt(nParameter)) && ((pParameter->GetColumn() < 0 && !nColumn && ((pParameter->GetRow() >= 0 && pParameter->GetRow() == nLine) || (pParameter->GetRow() < 0 && nLine == nParameter))) || (pParameter->GetColumn() == nColumn  &&  pParameter->GetRow() == nLine))) break;
			continue;
		}
		if ((pOldFont = (pParameter->IsLabel() && pLabelsFont != (CFont *)NULL) ? cDC.SelectObject(pLabelsFont) : cDC.SelectObject(pItemsFont)))
		{
			if ((nPos = szContents.GetAt(nLine).Find(CTextView::GetColumnDelimiter())) >= 0)
			{
				nWidth = max(cDC.GetTextExtent(szContents.GetAt(nLine).Left(nPos)).cx, nWidth);
				szContents.SetAt(nLine, szContents.GetAt(nLine).Mid(nPos + 1));
				cDC.SelectObject(pOldFont);
				continue;
			}
			if (szContents.GetAt(nLine).GetLength() > 0)
			{
				nWidth = max(cDC.GetTextExtent(szContents.GetAt(nLine)).cx, nWidth);
				szContents.SetAt(nLine, EMPTYSTRING);
				cDC.SelectObject(pOldFont);
				continue;
			}
			cDC.SelectObject(pOldFont);
		}
	}
	return nWidth;
}

BOOL CANDWnd::CalcPrintDocRect(CDC &cDC, CONST RECT &rtMargin, BOOL bMetric) CONST
{
	CRect  rClip;

	rClip.SetRect(0, 0, cDC.GetDeviceCaps(HORZRES), cDC.GetDeviceCaps(VERTRES));
	rClip.DeflateRect((bMetric) ? (rtMargin.left*cDC.GetDeviceCaps(HORZRES)) / (100 * cDC.GetDeviceCaps(HORZSIZE)) : (rtMargin.left*cDC.GetDeviceCaps(LOGPIXELSX)) / 1000, (bMetric) ? (rtMargin.top*cDC.GetDeviceCaps(VERTRES)) / (100 * cDC.GetDeviceCaps(VERTSIZE)) : (rtMargin.top*cDC.GetDeviceCaps(LOGPIXELSY)) / 1000, (bMetric) ? (rtMargin.right*cDC.GetDeviceCaps(HORZRES)) / (100 * cDC.GetDeviceCaps(HORZSIZE)) : (rtMargin.right*cDC.GetDeviceCaps(LOGPIXELSX)) / 1000, (bMetric) ? (rtMargin.bottom*cDC.GetDeviceCaps(VERTRES)) / (100 * cDC.GetDeviceCaps(VERTSIZE)) : (rtMargin.bottom*cDC.GetDeviceCaps(LOGPIXELSY)) / 1000);
	return((cDC.IntersectClipRect(rClip) != ERROR) ? TRUE : FALSE);
}

BEGIN_MESSAGE_MAP(CANDWnd, CDisplayWnd)
	//{{AFX_MSG_MAP(CANDWnd)
	ON_WM_CREATE()
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_SYSCOMMAND()
	ON_WM_INITMENUPOPUP()
	ON_WM_SETFOCUS()
	ON_WM_DESTROY()
	ON_COMMAND(IDM_ANDSETTINGS, OnSettings)
	ON_COMMAND(IDM_ANDLINKAGES, OnLinkages)
	ON_COMMAND(IDM_ANDPARAMETERS, OnParameters)
	ON_COMMAND(IDM_ANDRETRIEVALS, OnRetrievals)
	ON_COMMAND(IDM_ANDRETRIEVESTOP, OnRetrieveStop)
	ON_COMMAND(IDM_ANDRETRIEVEFORWARD, OnRetrieveAutoForward)
	ON_COMMAND(IDM_ANDRETRIEVEBACKWARD, OnRetrieveAutoBackward)
	ON_COMMAND(IDM_ANDRETRIEVESTEPFORWARD, OnRetrieveManualForward)
	ON_COMMAND(IDM_ANDRETRIEVESTEPBACKWARD, OnRetrieveManualBackward)
	ON_COMMAND(IDM_ANDRETRIEVEPSEUDOREALTIME, OnRetrievePseudoRealtime)
	ON_COMMAND(IDM_ANDPRINT, OnPrint)
	ON_UPDATE_COMMAND_UI(IDM_ANDSETTINGS, OnUpdateSettings)
	ON_UPDATE_COMMAND_UI(IDM_ANDLINKAGES, OnUpdateLinkages)
	ON_UPDATE_COMMAND_UI(IDM_ANDPARAMETERS, OnUpdateParameters)
	ON_UPDATE_COMMAND_UI(IDM_ANDRETRIEVALS, OnUpdateRetrievals)
	ON_UPDATE_COMMAND_UI(IDM_ANDRETRIEVESTOP, OnUpdateRetrieveStop)
	ON_UPDATE_COMMAND_UI(IDM_ANDRETRIEVEFORWARD, OnUpdateRetrieveAutoForward)
	ON_UPDATE_COMMAND_UI(IDM_ANDRETRIEVEBACKWARD, OnUpdateRetrieveAutoBackward)
	ON_UPDATE_COMMAND_UI(IDM_ANDRETRIEVESTEPFORWARD, OnUpdateRetrieveManualForward)
	ON_UPDATE_COMMAND_UI(IDM_ANDRETRIEVESTEPBACKWARD, OnUpdateRetrieveManualBackward)
	ON_UPDATE_COMMAND_UI(IDM_ANDRETRIEVEPSEUDOREALTIME, OnUpdateRetrievePseudoRealtime)
	ON_UPDATE_COMMAND_UI(IDM_ANDPRINT, OnUpdatePrint)
	ON_UPDATE_COMMAND_UI(ID_AND_STATUSBAR_MESSAGEPANE, OnUpdateStatusBarMessagePane)
	ON_UPDATE_COMMAND_UI(ID_AND_STATUSBAR_MODEPANE, OnUpdateStatusBarModePane)
	ON_UPDATE_COMMAND_UI(ID_AND_STATUSBAR_TYPEPANE, OnUpdateStatusBarTypePane)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CANDWnd message handlers

int CANDWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDisplayWnd::OnCreate(lpCreateStruct) != -1)
	{
		for (EnableDocking(CBRS_ALIGN_TOP); CreateToolBar() && CreateStatusBar() && CreateView() && LoadAccelTable(MAKEINTRESOURCE(IDR_ANDFRAME)); )
		{
			UpdateBars();
			return 0;
		}
	}
	return -1;
}

void CANDWnd::OnGetMinMaxInfo(MINMAXINFO *lpMMI)
{
	CRect  rView;
	CRect  rToolBar;
	CRect  rStatusBar;

	for (rView.SetRectEmpty(); IsWindow(m_wndView.GetSafeHwnd()); )
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
	lpMMI->ptMinTrackSize.x = max(lpMMI->ptMinTrackSize.x, 2 * GetSystemMetrics(SM_CXFRAME) + rView.Width());
	lpMMI->ptMinTrackSize.y = max(lpMMI->ptMinTrackSize.y, 2 * (GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYEDGE)) + GetSystemMetrics(SM_CYCAPTION) + rToolBar.Height() + rView.Height() + rStatusBar.Height());
	CDisplayWnd::OnGetMinMaxInfo(lpMMI);
}

void CANDWnd::OnSize(UINT nType, int cx, int cy)
{
	CDisplayWnd::OnSize(nType, cx, cy);
	m_wndView.RecalcLayout();
}

BOOL CANDWnd::OnEraseBkgnd(CDC *pDC)
{
	if (!IsInitialized())
	{
		m_wndToolBar.UpdateWindow();
		m_wndStatusBar.UpdateWindow();
	}
	return TRUE;
}

void CANDWnd::OnSysCommand(UINT nID, LPARAM lParam)
{
	switch (nID)
	{
	case IDM_DISPLAYREDUCEFONTS:
	{ BeginWaitCursor();
	ReduceFonts(FALSE);
	EndWaitCursor();
	break;
	}
	case IDM_DISPLAYRESTOREFONTS:
	{ BeginWaitCursor();
	ReduceFonts(TRUE);
	EndWaitCursor();
	break;
	}
	}
	CDisplayWnd::OnSysCommand(nID, lParam);
}

void CANDWnd::OnInitMenuPopup(CMenu *pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	for (; bSysMenu; )
	{
		UpdateSysMenu(pPopupMenu);
		break;
	}
	CDisplayWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
}

void CANDWnd::OnSetFocus(CWnd *pOldWnd)
{
	if (IsWindow(pOldWnd->GetSafeHwnd()))
	{
		if (m_wndView.IsChild(pOldWnd))
		{
			GetParent()->SetFocus();
			return;
		}
	}
	if (m_wndView.GetTextCount() > 0)
	{
		m_wndView.SetFocus();
		return;
	}
	CDisplayWnd::OnSetFocus(pOldWnd);
}

BOOL CANDWnd::OnCloseOpenDialog(UINT nCode)
{
	UINT  nMode;
	UINT  nSpeed;
	BOOL  bBadData;
	BOOL  bToolTips;
	BOOL  bInvalidData;
	LOGFONT  fntTitle;
	LOGFONT  fntItems;
	LOGFONT  fntLabels;
	LOGFONT  fntValues;
	CString  szFileName;
	CTimeSpan  tInterval;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CUIntArray  nColors;
	CUIntArray  nTitleItems;
	CANDLayout  cLayout;
	CANDPrintJobs  pJobs;

	if (nCode == IDOK)
	{
		for (SetMode(m_dlgOpen.GetMode()), SetType(MAKELONG(DISPLAY_TYPE_AND, m_dlgOpen.GetType())), SetWindowText(m_dlgOpen.GetTitle()); m_dlgOpen.IsLayoutModified(); )
		{
			m_dlgOpen.GetLayout(cLayout, nTitleItems);
			m_dlgOpen.GetLayoutColors(nColors);
			m_dlgOpen.GetLayoutTitleFont(&fntTitle);
			m_dlgOpen.GetLayoutLabelsFont(&fntLabels);
			m_dlgOpen.GetLayoutItemsFont(&fntItems);
			m_dlgOpen.GetLayoutValuesFont(&fntValues);
			m_dlgOpen.GetLayoutInvalidDataMode(bInvalidData);
			m_dlgOpen.GetLayoutBadDataMode(bBadData);
			m_dlgOpen.GetLayoutToolTipMode(bToolTips);
			if ((HIWORD(GetType()) == AND_TYPE_TEMPORARY  &&  !AddTemporaryAND(cLayout.GetName(), cLayout)) || !SetLayout(cLayout, nTitleItems) || !SetTitleFont(&fntTitle) || !SetLabelsFont(&fntLabels) || !SetItemsFont(&fntItems) || !SetValuesFont(&fntValues) || !SetOolColors(nColors) || !EnableInvalidDataMode(bInvalidData) || !EnableBadDataMode(bBadData) || !EnableToolTipMode(bToolTips)) return FALSE;
			break;
		}
		if (!m_dlgOpen.IsLayoutModified())
		{
			m_dlgOpen.GetLayout(cLayout, nTitleItems);
			if ((HIWORD(GetType()) == AND_TYPE_TEMPORARY  &&  !AddTemporaryAND(cLayout.GetName(), cLayout)) || !SetLayout(cLayout, nTitleItems)) return FALSE;
		}
		if (m_dlgOpen.IsRetrievingModified())
		{
			m_dlgOpen.GetRetrieveFileName(szFileName);
			if (!SetRetrieveFileName(szFileName)) return FALSE;
		}
		if (m_dlgOpen.IsPrintingModified())
		{
			m_dlgOpen.GetPrintJobs(pJobs);
			if (!SetPrintJobs(pJobs)) return FALSE;
		}
		if (GetMode() == DISPLAY_MODE_REALTIME)
		{
			UpdateAllPanes();
			return Start();
		}
		if (GetMode() == DISPLAY_MODE_HISTORY)
		{
			m_dlgOpen.GetRetrieveMode(nMode);
			m_dlgOpen.GetRetrieveSpeed(nSpeed);
			m_dlgOpen.GetRetrieveInterval(tInterval);
			m_dlgOpen.GetRetrieveStartTime(tStartTime);
			m_dlgOpen.GetRetrieveStopTime(tStopTime);
			SetRetrieveMode(nMode);
			SetRetrieveSpeed(nSpeed);
			SetRetrieveInterval(tInterval);
			SetRetrieveStartTime(tStartTime);
			SetRetrieveStopTime(tStopTime);
			UpdateAllPanes();
			return Start();
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CANDWnd::OnCloseSettingsDialog(UINT nCode)
{
	BOOL  bBadData;
	BOOL  bToolTips;
	BOOL  bInvalidData;
	CString  szLayout;
	CString  szFileName;
	LOGFONT  fntTitle[2];
	LOGFONT  fntItems[2];
	LOGFONT  fntLabels[2];
	LOGFONT  fntValues[2];
	CUIntArray  nColors;
	CUIntArray  nColumns;
	CANDLayout  cLayout;
	CANDPrintJobs  pJobs;

	if (nCode == IDOK)
	{
		if (m_dlgSettings.IsLayoutModified())
		{
			m_dlgSettings.GetLayout(cLayout, nColumns);
			m_dlgSettings.GetLayoutColors(nColors);
			m_dlgSettings.GetLayoutTitleFont(&fntTitle[0]);
			m_dlgSettings.GetLayoutLabelsFont(&fntLabels[0]);
			m_dlgSettings.GetLayoutItemsFont(&fntItems[0]);
			m_dlgSettings.GetLayoutValuesFont(&fntValues[0]);
			m_dlgSettings.GetLayoutInvalidDataMode(bInvalidData);
			m_dlgSettings.GetLayoutBadDataMode(bBadData);
			m_dlgSettings.GetLayoutToolTipMode(bToolTips);
			if ((HIWORD(GetType()) == AND_TYPE_TEMPORARY  &&  !AddTemporaryAND(cLayout.GetName(), cLayout)) || !SetLayout(cLayout, nColumns) || ((!GetTitleFont(&fntTitle[1]) || !GetLabelsFont(&fntLabels[1]) || !GetItemsFont(&fntItems[1]) || !GetValuesFont(&fntValues[1]) || memcmp(&fntTitle[0], &fntTitle[1], sizeof(LOGFONT)) || memcmp(&fntLabels[0], &fntLabels[1], sizeof(LOGFONT)) || memcmp(&fntItems[0], &fntItems[1], sizeof(LOGFONT)) || memcmp(&fntValues[0], &fntValues[1], sizeof(LOGFONT))) && (!SetTitleFont(&fntTitle[0]) || !SetLabelsFont(&fntLabels[0]) || !SetItemsFont(&fntItems[0]) || !SetValuesFont(&fntValues[0]))) || !SetOolColors(nColors) || !EnableInvalidDataMode(bInvalidData) || !EnableBadDataMode(bBadData) || !EnableToolTipMode(bToolTips)) return FALSE;
		}
		if (m_dlgSettings.IsRetrievingModified())
		{
			m_dlgSettings.GetRetrieveFileName(szFileName);
			if (!SetRetrieveFileName(szFileName)) return FALSE;
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

BOOL CANDWnd::OnCloseRetrieveDialog(UINT nCode)
{
	UINT  nMode[2];
	UINT  nSpeed[2];
	CTimeSpan  tInterval[2];
	CTimeKey  tStartTime[2];
	CTimeKey  tStopTime[2];

	if (nCode == IDOK)
	{
		nMode[0] = GetRetrieveMode();
		nSpeed[0] = GetRetrieveSpeed();
		tInterval[0] = GetRetrieveInterval();
		tStartTime[0] = GetRetrieveStartTime();
		tStopTime[0] = GetRetrieveStopTime();
		for (m_dlgRetrievals.GetMode(nMode[1]); nMode[1]; )
		{
			m_dlgRetrievals.GetSpeed(nSpeed[1]);
			m_dlgRetrievals.GetInterval(tInterval[1]);
			m_dlgRetrievals.GetStartTime(tStartTime[1]);
			m_dlgRetrievals.GetStopTime(tStopTime[1]);
			if (SetMode(DISPLAY_MODE_HISTORY) && (!IsRetrievingData() || StopRetrieveData()) && StartRetrieveData(nMode[1], nSpeed[1], tInterval[1], tStartTime[1], tStopTime[1]))
			{
				UpdateAllPanes();
				return TRUE;
			}
			SetMode((!nMode[0]) ? DISPLAY_MODE_REALTIME : DISPLAY_MODE_HISTORY);
			SetRetrieveMode(nMode[0]);
			SetRetrieveSpeed(nSpeed[0]);
			SetRetrieveInterval(tInterval[0]);
			SetRetrieveStartTime(tStartTime[0]);
			SetRetrieveStopTime(tStopTime[0]);
			UpdateAllPanes();
			return FALSE;
		}
		StopRetrieveData();
		SetRetrieveMode();
		SetRetrieveSpeed();
		SetRetrieveInterval();
		SetRetrieveStartTime();
		SetRetrieveStopTime();
		SetMode(DISPLAY_MODE_REALTIME);
		ProcessRealtimeData();
		UpdateAllPanes();
	}
	return TRUE;
}

void CANDWnd::OnSettings()
{
	CHourglassCursor  cCursor;

	ReportEvent((m_dlgSettings.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CANDWnd::OnLinkages()
{
	CHourglassCursor  cCursor;

	ReportEvent((m_dlgLinkages.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CANDWnd::OnParameters()
{
	CHourglassCursor  cCursor;

	ReportEvent((m_dlgParameters.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CANDWnd::OnRetrievals()
{
	CHourglassCursor  cCursor;

	ReportEvent((m_dlgRetrievals.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CANDWnd::OnRetrieveStop()
{
	RetrieveMoreData(AND_RETRIEVE_STOPPED);
}

void CANDWnd::OnRetrieveAutoForward()
{
	RetrieveMoreData(AND_RETRIEVE_AUTOFORWARD);
}

void CANDWnd::OnRetrieveAutoBackward()
{
	RetrieveMoreData(AND_RETRIEVE_AUTOBACKWARD);
}

void CANDWnd::OnRetrieveManualForward()
{
	RetrieveMoreData(AND_RETRIEVE_MANUALFORWARD);
}

void CANDWnd::OnRetrieveManualBackward()
{
	RetrieveMoreData(AND_RETRIEVE_MANUALBACKWARD);
}

void CANDWnd::OnRetrievePseudoRealtime()
{
	RetrieveMoreData(AND_RETRIEVE_PSEUDOREALTIME);
}

void CANDWnd::OnPrint()
{
	CHourglassCursor  cCursor;

	ReportEvent((!Print()) ? SYSTEM_WARNING_DISPLAY_PRINT_FAILURE : SYSTEM_NOERROR);
}

void CANDWnd::OnDestroy()
{
	CHourglassCursor  cCursor;

	Stop();
	CDisplayWnd::OnDestroy();
}

void CANDWnd::OnUpdateSettings(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsInitialized() && (HIWORD(GetType()) != AND_TYPE_TEMPORARY || CheckAccountPrivilege(PRIVILEGE_AND_TEMPORARYUSE)));
	pCmdUI->SetCheck(IsWindow(m_dlgSettings.GetSafeHwnd()));
}

void CANDWnd::OnUpdateLinkages(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsInitialized() && !GetLink());
	pCmdUI->SetCheck(IsWindow(m_dlgLinkages.GetSafeHwnd()));
}

void CANDWnd::OnUpdateParameters(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsInitialized() && HasLayout()) ? TRUE : FALSE);
	pCmdUI->SetCheck(IsWindow(m_dlgParameters.GetSafeHwnd()));
}

void CANDWnd::OnUpdateRetrievals(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsInitialized()) ? TRUE : FALSE);
	pCmdUI->SetCheck(IsWindow(m_dlgRetrievals.GetSafeHwnd()));
}

void CANDWnd::OnUpdateRetrieveStop(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && ((GetRetrieveMode() & AND_RETRIEVE_AUTOFORWARD) || (GetRetrieveMode() & AND_RETRIEVE_AUTOBACKWARD) || (GetRetrieveMode() & AND_RETRIEVE_PSEUDOREALTIME) || HIWORD(IsRetrievingData())) && !(GetRetrieveMode() & AND_RETRIEVE_STOPPED)) ? TRUE : FALSE);
}

void CANDWnd::OnUpdateRetrieveAutoForward(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & AND_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & AND_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & AND_RETRIEVE_STOPPED))) ? TRUE : FALSE);
}

void CANDWnd::OnUpdateRetrieveAutoBackward(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & AND_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & AND_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & AND_RETRIEVE_STOPPED))) ? TRUE : FALSE);
}

void CANDWnd::OnUpdateRetrieveManualForward(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & AND_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & AND_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & AND_RETRIEVE_STOPPED))) ? TRUE : FALSE);
}

void CANDWnd::OnUpdateRetrieveManualBackward(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & AND_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & AND_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & AND_RETRIEVE_STOPPED))) ? TRUE : FALSE);
}

void CANDWnd::OnUpdateRetrievePseudoRealtime(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & AND_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & AND_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & AND_RETRIEVE_STOPPED))) ? TRUE : FALSE);
}

void CANDWnd::OnUpdatePrint(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsInitialized() && IsDefaultPrinterAvailable() && CanPrint()) ? TRUE : FALSE);
}

void CANDWnd::OnUpdateStatusBarMessagePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CANDWnd::OnUpdateStatusBarModePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CANDWnd::OnUpdateStatusBarTypePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}
