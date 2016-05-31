// HEX.CPP : Hexadecimal Display Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the hexadecimal display
// related interface.
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


static UINT BASED_CODE nHEXStatusBarIndicators[] =
{
	ID_HEX_STATUSBAR_MESSAGEPANE,
	ID_HEX_STATUSBAR_MODEPANE,
	ID_HEX_STATUSBAR_TYPEPANE
};



/////////////////////////////////////////////////////////////////////////////
// CHEXPrintJobInfo

CHEXPrintJobInfo::CHEXPrintJobInfo() : CObject()
{
	m_nPrintMode = 0;
	m_nPrintFlags = 0;
	m_nPrintCount[0] = 0;
	m_nPrintCount[1] = 0;
	m_nPrintByCount[0] = 0;
	m_nPrintByCount[1] = 0;
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

VOID CHEXPrintJobInfo::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CHEXPrintJobInfo::GetName() CONST
{
	return m_szName;
}

VOID CHEXPrintJobInfo::SetProfile(LPCTSTR pszProfile)
{
	m_szProfile = pszProfile;
}

CString CHEXPrintJobInfo::GetProfile() CONST
{
	return m_szProfile;
}

VOID CHEXPrintJobInfo::SetComments(LPCTSTR pszComments)
{
	m_szComments = pszComments;
}

CString CHEXPrintJobInfo::GetComments() CONST
{
	return m_szComments;
}

BOOL CHEXPrintJobInfo::SetPrintMode(UINT nMode)
{
	m_nPrintMode = nMode;
	return TRUE;
}

UINT CHEXPrintJobInfo::GetPrintMode() CONST
{
	return m_nPrintMode;
}

BOOL CHEXPrintJobInfo::SetPrintFlags(UINT nFlags)
{
	if (nFlags == HEX_PRINT_ATTIME || nFlags == HEX_PRINT_ATDAILYTIME || nFlags == HEX_PRINT_ATEVENT || !nFlags)
	{
		m_nPrintFlags = nFlags;
		return TRUE;
	}
	return FALSE;
}

UINT CHEXPrintJobInfo::GetPrintFlags() CONST
{
	return m_nPrintFlags;
}

BOOL CHEXPrintJobInfo::SetPrintBySide(UINT nDataCount, UINT nSpyCount)
{
	if ((m_nPrintMode & HEX_PRINT_FIRSTDATASIDE) || (m_nPrintMode & HEX_PRINT_LASTDATASIDE) || (m_nPrintMode & HEX_PRINT_FIRSTSPYLOCATIONSSIDE) || (m_nPrintMode & HEX_PRINT_LASTSPYLOCATIONSSIDE))
	{
		if ((m_nPrintMode & HEX_PRINT_FIRSTDATASIDE) || (m_nPrintMode & HEX_PRINT_LASTDATASIDE)) m_nPrintByCount[0] = nDataCount;
		if ((m_nPrintMode & HEX_PRINT_FIRSTSPYLOCATIONSSIDE) || (m_nPrintMode & HEX_PRINT_LASTSPYLOCATIONSSIDE)) m_nPrintByCount[1] = nSpyCount;
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXPrintJobInfo::GetPrintBySide(UINT &nDataCount, UINT &nSpyCount) CONST
{
	if (((m_nPrintMode & HEX_PRINT_FIRSTDATASIDE) || (m_nPrintMode & HEX_PRINT_LASTDATASIDE)) && ((m_nPrintMode & HEX_PRINT_FIRSTSPYLOCATIONSSIDE) || (m_nPrintMode & HEX_PRINT_LASTSPYLOCATIONSSIDE)))
	{
		nDataCount = m_nPrintByCount[0];
		nSpyCount = m_nPrintByCount[1];
		return TRUE;
	}
	if ((m_nPrintMode & HEX_PRINT_FIRSTDATASIDE) || (m_nPrintMode & HEX_PRINT_LASTDATASIDE))
	{
		nDataCount = m_nPrintByCount[0];
		nSpyCount = 0;
		return TRUE;
	}
	if ((m_nPrintMode & HEX_PRINT_FIRSTSPYLOCATIONSSIDE) || (m_nPrintMode & HEX_PRINT_LASTSPYLOCATIONSSIDE))
	{
		nSpyCount = m_nPrintByCount[1];
		nDataCount = 0;
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXPrintJobInfo::SetPrintAtTime(CONST CTimeKey &tTime)
{
	if ((m_nPrintMode & HEX_PRINT_ATTIME) && !(m_nPrintMode & HEX_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & HEX_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & HEX_PRINT_REPEATSTOPBYTIME))
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
BOOL CHEXPrintJobInfo::SetPrintAtTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval)
{
	if ((m_nPrintMode & HEX_PRINT_ATTIME) && (m_nPrintMode & HEX_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & HEX_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & HEX_PRINT_REPEATSTOPBYTIME))
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
BOOL CHEXPrintJobInfo::SetPrintAtTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval, UINT nStopCount)
{
	if ((m_nPrintMode & HEX_PRINT_ATTIME) && (m_nPrintMode & HEX_PRINT_REPEATBYINTERVAL) && (m_nPrintMode & HEX_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & HEX_PRINT_REPEATSTOPBYTIME))
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
BOOL CHEXPrintJobInfo::SetPrintAtTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval, CONST CTimeKey &tStopTime)
{
	if ((m_nPrintMode & HEX_PRINT_ATTIME) && (m_nPrintMode & HEX_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & HEX_PRINT_REPEATSTOPBYCOUNT) && (m_nPrintMode & HEX_PRINT_REPEATSTOPBYTIME))
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

BOOL CHEXPrintJobInfo::GetPrintAtTime(CTimeKey &tTime) CONST
{
	if ((m_nPrintMode & HEX_PRINT_ATTIME) && !(m_nPrintMode & HEX_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & HEX_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & HEX_PRINT_REPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtTime;
		return TRUE;
	}
	return FALSE;
}
BOOL CHEXPrintJobInfo::GetPrintAtTime(CTimeKey &tTime, CTimeSpan &tInterval) CONST
{
	if ((m_nPrintMode & HEX_PRINT_ATTIME) && (m_nPrintMode & HEX_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & HEX_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & HEX_PRINT_REPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtTime;
		tInterval = m_tRepeatInterval;
		return TRUE;
	}
	return FALSE;
}
BOOL CHEXPrintJobInfo::GetPrintAtTime(CTimeKey &tTime, CTimeSpan &tInterval, UINT &nStopCount) CONST
{
	if ((m_nPrintMode & HEX_PRINT_ATTIME) && (m_nPrintMode & HEX_PRINT_REPEATBYINTERVAL) && (m_nPrintMode & HEX_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & HEX_PRINT_REPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtTime;
		tInterval = m_tRepeatInterval;
		nStopCount = m_nRepeatStopByCount[0];
		return TRUE;
	}
	return FALSE;
}
BOOL CHEXPrintJobInfo::GetPrintAtTime(CTimeKey &tTime, CTimeSpan &tInterval, CTimeKey &tStopTime) CONST
{
	if ((m_nPrintMode & HEX_PRINT_ATTIME) && (m_nPrintMode & HEX_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & HEX_PRINT_REPEATSTOPBYCOUNT) && (m_nPrintMode & HEX_PRINT_REPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtTime;
		tInterval = m_tRepeatInterval;
		tStopTime = m_tRepeatStopByTime[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXPrintJobInfo::SetPrintAtDailyTime(CONST CTimeSpan &tTime)
{
	TIMEKEY  tTimeKey;

	if ((m_nPrintMode & HEX_PRINT_ATDAILYTIME) && !(m_nPrintMode & HEX_PRINT_DAILYREPEATSTOPBYCOUNT) && !(m_nPrintMode & HEX_PRINT_DAILYREPEATSTOPBYTIME))
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
BOOL CHEXPrintJobInfo::SetPrintAtDailyTime(CONST CTimeSpan &tTime, UINT nStopCount)
{
	TIMEKEY  tTimeKey;

	if ((m_nPrintMode & HEX_PRINT_ATDAILYTIME) && (m_nPrintMode & HEX_PRINT_DAILYREPEATSTOPBYCOUNT) && !(m_nPrintMode & HEX_PRINT_DAILYREPEATSTOPBYTIME))
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
BOOL CHEXPrintJobInfo::SetPrintAtDailyTime(CONST CTimeSpan &tTime, CONST CTimeKey &tStopTime)
{
	TIMEKEY  tTimeKey;

	if ((m_nPrintMode & HEX_PRINT_ATDAILYTIME) && !(m_nPrintMode & HEX_PRINT_DAILYREPEATSTOPBYCOUNT) && (m_nPrintMode & HEX_PRINT_DAILYREPEATSTOPBYTIME))
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

BOOL CHEXPrintJobInfo::GetPrintAtDailyTime(CTimeSpan &tTime) CONST
{
	if ((m_nPrintMode & HEX_PRINT_ATDAILYTIME) && !(m_nPrintMode & HEX_PRINT_DAILYREPEATSTOPBYCOUNT) && !(m_nPrintMode & HEX_PRINT_DAILYREPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtDailyTime;
		return TRUE;
	}
	return FALSE;
}
BOOL CHEXPrintJobInfo::GetPrintAtDailyTime(CTimeSpan &tTime, UINT &nStopCount) CONST
{
	if ((m_nPrintMode & HEX_PRINT_ATDAILYTIME) && (m_nPrintMode & HEX_PRINT_DAILYREPEATSTOPBYCOUNT) && !(m_nPrintMode & HEX_PRINT_DAILYREPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtDailyTime;
		nStopCount = m_nRepeatStopByCount[1];
		return TRUE;
	}
	return FALSE;
}
BOOL CHEXPrintJobInfo::GetPrintAtDailyTime(CTimeSpan &tTime, CTimeKey &tStopTime) CONST
{
	if ((m_nPrintMode & HEX_PRINT_ATDAILYTIME) && !(m_nPrintMode & HEX_PRINT_DAILYREPEATSTOPBYCOUNT) && (m_nPrintMode & HEX_PRINT_DAILYREPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtDailyTime;
		tStopTime = m_tRepeatStopByTime[1];
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXPrintJobInfo::SetPrintAtEvent(LPCTSTR pszEvent)
{
	if (m_nPrintMode & HEX_PRINT_ATEVENT)
	{
		m_szEvent = pszEvent;
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXPrintJobInfo::GetPrintAtEvent(CString &szEvent) CONST
{
	if (m_nPrintMode & HEX_PRINT_ATEVENT)
	{
		szEvent = m_szEvent;
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXPrintJobInfo::SetPrintCount(UINT nCount)
{
	if (m_nPrintMode & HEX_PRINT_ATTIME)
	{
		m_nPrintCount[0] = nCount;
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXPrintJobInfo::GetPrintCount(UINT &nCount) CONST
{
	if (m_nPrintMode & HEX_PRINT_ATTIME)
	{
		nCount = m_nPrintCount[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXPrintJobInfo::SetPrintDailyCount(UINT nCount)
{
	if (m_nPrintMode & HEX_PRINT_ATDAILYTIME)
	{
		m_nPrintCount[1] = nCount;
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXPrintJobInfo::GetPrintDailyCount(UINT &nCount) CONST
{
	if (m_nPrintMode & HEX_PRINT_ATDAILYTIME)
	{
		nCount = m_nPrintCount[1];
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXPrintJobInfo::SetPrintLastTime(CONST CTimeKey &tTime)
{
	if (m_nPrintMode & HEX_PRINT_ATTIME)
	{
		m_tPrintLastTime[0] = tTime;
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXPrintJobInfo::GetPrintLastTime(CTimeKey &tTime) CONST
{
	if (m_nPrintMode & HEX_PRINT_ATTIME)
	{
		tTime = m_tPrintLastTime[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXPrintJobInfo::SetPrintLastDailyTime(CONST CTimeKey &tTime)
{
	if (m_nPrintMode & HEX_PRINT_ATDAILYTIME)
	{
		m_tPrintLastTime[1] = tTime;
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXPrintJobInfo::GetPrintLastDailyTime(CTimeKey &tTime) CONST
{
	if (m_nPrintMode & HEX_PRINT_ATDAILYTIME)
	{
		tTime = m_tPrintLastTime[1];
		return TRUE;
	}
	return FALSE;
}

VOID CHEXPrintJobInfo::Copy(CONST CHEXPrintJobInfo *pJobInfo)
{
	m_szName = pJobInfo->m_szName;
	m_szEvent = pJobInfo->m_szEvent;
	m_szProfile = pJobInfo->m_szProfile;
	m_szComments = pJobInfo->m_szComments;
	m_nPrintMode = pJobInfo->m_nPrintMode;
	m_nPrintFlags = pJobInfo->m_nPrintFlags;
	m_nPrintCount[0] = pJobInfo->m_nPrintCount[0];
	m_nPrintCount[1] = pJobInfo->m_nPrintCount[1];
	m_nPrintByCount[0] = pJobInfo->m_nPrintByCount[0];
	m_nPrintByCount[1] = pJobInfo->m_nPrintByCount[1];
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

BOOL CHEXPrintJobInfo::Compare(CONST CHEXPrintJobInfo *pJobInfo) CONST
{
	return((pJobInfo->m_szName == m_szName  &&  pJobInfo->m_szProfile == m_szProfile  &&  pJobInfo->m_szComments == m_szComments  &&  pJobInfo->m_nPrintMode == m_nPrintMode && ((!(m_nPrintMode & HEX_PRINT_FIRSTDATASIDE) && !(m_nPrintMode & HEX_PRINT_LASTDATASIDE)) || pJobInfo->m_nPrintByCount[0] == m_nPrintByCount[0]) && ((!(m_nPrintMode & HEX_PRINT_FIRSTSPYLOCATIONSSIDE) && !(m_nPrintMode & HEX_PRINT_LASTSPYLOCATIONSSIDE)) || pJobInfo->m_nPrintByCount[1] == m_nPrintByCount[1]) && (!(m_nPrintMode & HEX_PRINT_ATTIME) || pJobInfo->m_tPrintAtTime == m_tPrintAtTime) && (!(m_nPrintMode & HEX_PRINT_ATDAILYTIME) || pJobInfo->m_tPrintAtDailyTime == m_tPrintAtDailyTime) && (!(m_nPrintMode & HEX_PRINT_ATEVENT) || pJobInfo->m_szEvent == m_szEvent) && (!(m_nPrintMode & HEX_PRINT_REPEATBYINTERVAL) || pJobInfo->m_tRepeatInterval == m_tRepeatInterval) && (!(m_nPrintMode & HEX_PRINT_REPEATSTOPBYCOUNT) || pJobInfo->m_nRepeatStopByCount[0] == m_nRepeatStopByCount[0]) && (!(m_nPrintMode & HEX_PRINT_REPEATSTOPBYTIME) || pJobInfo->m_tRepeatStopByTime[0] == m_tRepeatStopByTime[0]) && (!(m_nPrintMode & HEX_PRINT_DAILYREPEATSTOPBYCOUNT) || pJobInfo->m_nRepeatStopByCount[1] == m_nRepeatStopByCount[1]) && (!(m_nPrintMode & HEX_PRINT_DAILYREPEATSTOPBYTIME) || pJobInfo->m_tRepeatStopByTime[1] == m_tRepeatStopByTime[1])) ? TRUE : FALSE);
}

BOOL CHEXPrintJobInfo::Map(CByteArray &nInfo) CONST
{
	INT  cbData;
	DATA  sData;

	sData.cbName = (m_szName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbEvent = (m_szEvent.GetLength() + 1)*sizeof(TCHAR);
	sData.cbProfile = (m_szProfile.GetLength() + 1)*sizeof(TCHAR);
	sData.cbComments = (m_szComments.GetLength() + 1)*sizeof(TCHAR);
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbName + sData.cbProfile + sData.cbComments + sData.cbEvent)), sData.nPrintMode = m_nPrintMode, sData.nPrintCount[0] = m_nPrintCount[0], sData.nPrintCount[1] = m_nPrintCount[1], sData.nPrintByCount[0] = m_nPrintByCount[0], sData.nPrintByCount[1] = m_nPrintByCount[1], sData.tPrintAtTime = m_tPrintAtTime.GetTime(), sData.tPrintAtDailyTime = m_tPrintAtDailyTime.GetTotalSeconds(), sData.tPrintLastTime[0] = m_tPrintLastTime[0].GetTime(), sData.tPrintLastTime[1] = m_tPrintLastTime[1].GetTime(), sData.tRepeatInterval = m_tRepeatInterval.GetTotalSeconds(), sData.nRepeatStopByCount[0] = m_nRepeatStopByCount[0], sData.nRepeatStopByCount[1] = m_nRepeatStopByCount[1], sData.tRepeatStopByTime[0] = m_tRepeatStopByTime[0].GetTime(), sData.tRepeatStopByTime[1] = m_tRepeatStopByTime[1].GetTime(); nInfo.GetSize() == sData.cbSize; )
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

BOOL CHEXPrintJobInfo::Unmap(CONST CByteArray &nInfo)
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
		m_nPrintByCount[0] = sData.nPrintByCount[0];
		m_nPrintByCount[1] = sData.nPrintByCount[1];
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
// CHEXPrintJobs

CHEXPrintJobs::CHEXPrintJobs() : CPtrArray()
{
	return;
}

CHEXPrintJobs::~CHEXPrintJobs()
{
	RemoveAll();
}

INT CHEXPrintJobs::Add(CHEXPrintJobInfo *pJobInfo)
{
	return((INT)CPtrArray::Add(pJobInfo));
}

INT CHEXPrintJobs::Find(LPCTSTR pszName) CONST
{
	INT  nJob;
	INT  nJobs;
	CHEXPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (INT)GetSize(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = GetAt(nJob)) && pJobInfo->GetName() == pszName) break;
		continue;
	}
	return((nJob < nJobs) ? nJob : -1);
}

CHEXPrintJobInfo *CHEXPrintJobs::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CHEXPrintJobInfo *)CPtrArray::GetAt(nIndex) : (CHEXPrintJobInfo *)NULL);
}

CHEXPrintJobInfo *CHEXPrintJobs::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CHEXPrintJobInfo *)CPtrArray::GetAt(nIndex) : (CHEXPrintJobInfo *)NULL);
}

TIMEKEY CHEXPrintJobs::Schedule()
{
	INT  nJob;
	INT  nJobs;
	UINT  nJobMode;
	UINT  nJobPrintCount[2];
	TIMEKEY  tJobPrintTimeout[2];
	CTimeKey  tJobPrintTime[4];
	CTimeSpan  tJobPrintInterval;
	CTimeSpan  tJobPrintDailyTime;
	CHEXPrintJobInfo  *pJobInfo[2];

	for (nJob = 0, nJobs = (INT)GetSize(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo[0] = GetAt(nJob)) != (CHEXPrintJobInfo *)NULL)
		{
			if (((nJobMode = pJobInfo[0]->GetPrintMode()) & HEX_PRINT_ACTIVE) && (((nJobMode & HEX_PRINT_ATTIME) && pJobInfo[0]->GetPrintLastTime(tJobPrintTime[1]) && (tJobPrintTime[1] > 0 || pJobInfo[0]->SetPrintLastTime(tJobPrintTime[3]))) || (nJobMode & HEX_PRINT_ATDAILYTIME)) &&
				((pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0]) && pJobInfo[0]->GetPrintCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastTime(tJobPrintTime[1]) && tJobPrintTime[3] >= tJobPrintTime[0] && tJobPrintTime[0] > tJobPrintTime[1] && pJobInfo[0]->SetPrintFlags(HEX_PRINT_ATTIME) && pJobInfo[0]->SetPrintCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0], tJobPrintInterval) && pJobInfo[0]->GetPrintCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastTime(tJobPrintTime[1]) && tJobPrintTime[3] >= tJobPrintTime[0] && (tJobPrintTime[0] > tJobPrintTime[1] || (tJobPrintTime[1].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds() < (tJobPrintTime[3].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds()) && pJobInfo[0]->SetPrintFlags(HEX_PRINT_ATTIME) && pJobInfo[0]->SetPrintCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0], tJobPrintInterval, nJobPrintCount[1]) && pJobInfo[0]->GetPrintCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastTime(tJobPrintTime[1]) && tJobPrintTime[3] >= tJobPrintTime[0] && (tJobPrintTime[0] > tJobPrintTime[1] || (tJobPrintTime[1].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds() < (tJobPrintTime[3].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds()) && nJobPrintCount[0] < nJobPrintCount[1] && pJobInfo[0]->SetPrintFlags(HEX_PRINT_ATTIME) && pJobInfo[0]->SetPrintCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0], tJobPrintInterval, tJobPrintTime[2]) && pJobInfo[0]->GetPrintCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastTime(tJobPrintTime[1]) && tJobPrintTime[3] >= tJobPrintTime[0] && (tJobPrintTime[0] > tJobPrintTime[1] || (tJobPrintTime[1].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds() < (tJobPrintTime[3].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds()) && tJobPrintTime[3] <= tJobPrintTime[2] && pJobInfo[0]->SetPrintFlags(HEX_PRINT_ATTIME) && pJobInfo[0]->SetPrintCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtDailyTime(tJobPrintDailyTime) && pJobInfo[0]->GetPrintDailyCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastDailyTime(tJobPrintTime[1]) && tJobPrintTime[3].GetTime() % SECONDSPERDAY >= tJobPrintDailyTime.GetTotalSeconds() && tJobPrintTime[3].GetTime() / SECONDSPERDAY != tJobPrintTime[1].GetTime() / SECONDSPERDAY  &&  pJobInfo[0]->SetPrintFlags(HEX_PRINT_ATDAILYTIME) && pJobInfo[0]->SetPrintDailyCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastDailyTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtDailyTime(tJobPrintDailyTime, nJobPrintCount[1]) && pJobInfo[0]->GetPrintDailyCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastDailyTime(tJobPrintTime[1]) && tJobPrintTime[3].GetTime() % SECONDSPERDAY >= tJobPrintDailyTime.GetTotalSeconds() && tJobPrintTime[3].GetTime() / SECONDSPERDAY != tJobPrintTime[1].GetTime() / SECONDSPERDAY  &&  nJobPrintCount[0] < nJobPrintCount[1] && pJobInfo[0]->SetPrintFlags(HEX_PRINT_ATDAILYTIME) && pJobInfo[0]->SetPrintDailyCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastDailyTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtDailyTime(tJobPrintDailyTime, tJobPrintTime[2]) && pJobInfo[0]->GetPrintDailyCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastDailyTime(tJobPrintTime[1]) && tJobPrintTime[3].GetTime() % SECONDSPERDAY >= tJobPrintDailyTime.GetTotalSeconds() && tJobPrintTime[3].GetTime() / SECONDSPERDAY != tJobPrintTime[1].GetTime() / SECONDSPERDAY  &&  tJobPrintTime[3] <= tJobPrintTime[2] && pJobInfo[0]->SetPrintFlags(HEX_PRINT_ATDAILYTIME) && pJobInfo[0]->SetPrintDailyCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastDailyTime(tJobPrintTime[3]))))
			{
				if ((pJobInfo[1] = new CHEXPrintJobInfo))
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

VOID CHEXPrintJobs::RemoveAll()
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

BOOL CHEXPrintJobs::Copy(CONST CHEXPrintJobs *pPrintJobs)
{
	INT  nJob;
	INT  nJobs;
	CHEXPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (INT)pPrintJobs->GetSize(), RemoveAll(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = new CHEXPrintJobInfo) != (CHEXPrintJobInfo *)NULL)
		{
			pJobInfo->Copy(pPrintJobs->GetAt(nJob));
			InsertAt(nJob, pJobInfo, 1);
			continue;
		}
		break;
	}
	return((nJob == nJobs) ? TRUE : FALSE);
}

BOOL CHEXPrintJobs::Compare(CONST CHEXPrintJobs *pPrintJobs) CONST
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

BOOL CHEXPrintJobs::Map(CByteArray &nInfo) CONST
{
	INT  nJob;
	INT  nJobs;
	CByteArray  nJobData;
	CHEXPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (INT)GetSize(), nInfo.RemoveAll(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = GetAt(nJob)) && pJobInfo->Map(nJobData) && nInfo.Append(nJobData) >= 0) continue;
		break;
	}
	return((nJob == nJobs) ? TRUE : FALSE);
}

BOOL CHEXPrintJobs::Unmap(CONST CByteArray &nInfo)
{
	INT  cbJob;
	INT  cbJobs;
	CByteArray  nJobData;
	CHEXPrintJobInfo  *pJobInfo;

	for (cbJobs = 0, RemoveAll(); cbJobs < nInfo.GetSize(); cbJobs += cbJob)
	{
		for (CopyMemory(&cbJob, nInfo.GetData() + cbJobs, sizeof(cbJob)), nJobData.SetSize(max(min(cbJob, nInfo.GetSize() - cbJobs), 0)); nJobData.GetSize() >= 0; )
		{
			CopyMemory(nJobData.GetData(), nInfo.GetData() + cbJobs, nJobData.GetSize());
			break;
		}
		if ((pJobInfo = new CHEXPrintJobInfo))
		{
			if (pJobInfo->Unmap(nJobData) && Add(pJobInfo) >= 0) continue;
			delete pJobInfo;
		}
		break;
	}
	if ((pJobInfo = (!GetSize()) ? new CHEXPrintJobInfo : (CHEXPrintJobInfo *)NULL))
	{
		for (pJobInfo->SetName(STRING(IDS_PRINTJOB_DEFAULTNAME)), pJobInfo->SetProfile(STRING(IDS_PRINTPROFILE_DEFAULTNAME)), pJobInfo->SetPrintMode(HEX_PRINT_ALLDATA); Add(pJobInfo) >= 0; ) return TRUE;
		delete pJobInfo;
		return FALSE;
	}
	return((cbJobs == nInfo.GetSize()) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CHEXSpyLocation

CHEXSpyLocation::CHEXSpyLocation() : CObject()
{
	m_nByte = 0;
	m_nBit = 0;
	m_nLength = 0;
	m_nCoding = HEXSPYLOCATION_CODING_DEFAULT;
	m_nColor[0] = VGA_COLOR_BLACK;
	m_nColor[1] = VGA_COLOR_BLACK;
}

VOID CHEXSpyLocation::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CHEXSpyLocation::GetName() CONST
{
	return m_szName;
}

BOOL CHEXSpyLocation::SetPosition(UINT nByte, UINT nBit, UINT nLength)
{
	if (nBit >= 0 && nBit < 8 && nByte >= 0 && nLength > 0)
	{
		m_nBit = nBit;
		m_nByte = nByte;
		m_nLength = nLength;
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXSpyLocation::GetPosition(UINT &nByte, UINT &nBit, UINT &nLength) CONST
{
	if (m_nBit >= 0 && m_nBit < 8 && m_nByte >= 0 && m_nLength > 0)
	{
		nBit = m_nBit;
		nByte = m_nByte;
		nLength = m_nLength;
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXSpyLocation::SetCoding(UINT nCoding)
{
	if (nCoding == HEXSPYLOCATION_CODING_BINARY || nCoding == HEXSPYLOCATION_CODING_OCTAL || nCoding == HEXSPYLOCATION_CODING_DECIMAL || nCoding == HEXSPYLOCATION_CODING_HEXADECIMAL)
	{
		m_nCoding = nCoding;
		return TRUE;
	}
	return FALSE;
}

UINT CHEXSpyLocation::GetCoding() CONST
{
	return m_nCoding;
}

VOID CHEXSpyLocation::SetDetailsColor(COLORREF nColor)
{
	m_nColor[0] = nColor;
}

COLORREF CHEXSpyLocation::GetDetailsColor() CONST
{
	return m_nColor[0];
}

VOID CHEXSpyLocation::SetValueColor(COLORREF nColor)
{
	m_nColor[1] = nColor;
}

COLORREF CHEXSpyLocation::GetValueColor() CONST
{
	return m_nColor[1];
}

VOID CHEXSpyLocation::Copy(CONST CHEXSpyLocation *pLocation)
{
	m_szName = pLocation->m_szName;
	m_nByte = pLocation->m_nByte;
	m_nBit = pLocation->m_nBit;
	m_nLength = pLocation->m_nLength;
	m_nCoding = pLocation->m_nCoding;
	m_nColor[0] = pLocation->m_nColor[0];
	m_nColor[1] = pLocation->m_nColor[1];
}

BOOL CHEXSpyLocation::Compare(CONST CHEXSpyLocation *pLocation) CONST
{
	return((pLocation->m_szName == m_szName  &&  pLocation->m_nByte == m_nByte  &&  pLocation->m_nBit == m_nBit  &&  pLocation->m_nLength == m_nLength  &&  pLocation->m_nCoding == m_nCoding  &&  pLocation->m_nColor[0] == m_nColor[0] && pLocation->m_nColor[1] == m_nColor[1]) ? TRUE : FALSE);
}

BOOL CHEXSpyLocation::Map(CByteArray &nInfo) CONST
{
	DATA  sData;

	sData.cbName = (m_szName.GetLength() + 1)*sizeof(TCHAR);
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbName)), sData.nByte = m_nByte, sData.nBit = m_nBit, sData.nLength = m_nLength, sData.nCoding = m_nCoding, sData.nColor[0] = m_nColor[0], sData.nColor[1] = m_nColor[1]; nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + sizeof(DATA), (LPCTSTR)m_szName, sData.cbName);
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXSpyLocation::Unmap(CONST CByteArray &nInfo)
{
	DATA  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbName && sData.cbName > 0; )
	{
		CopyMemory(m_szName.GetBufferSetLength(STRINGCHARS(sData.cbName)), nInfo.GetData() + sizeof(DATA), STRINGBYTES(sData.cbName));
		m_nByte = sData.nByte;
		m_nBit = sData.nBit;
		m_nLength = sData.nLength;
		m_nCoding = sData.nCoding;
		m_nColor[0] = sData.nColor[0];
		m_nColor[1] = sData.nColor[1];
		m_szName.ReleaseBuffer();
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CHEXSpyLocations

CHEXSpyLocations::CHEXSpyLocations() : CPtrArray()
{
	return;
}

CHEXSpyLocations::~CHEXSpyLocations()
{
	RemoveAll();
}

INT CHEXSpyLocations::Add(CHEXSpyLocation *pLocation)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pLocation->GetName(), TRUE)) >= 0) InsertAt(nIndex, pLocation, 1);
	return nIndex;
}

INT CHEXSpyLocations::Find(LPCTSTR pszName) CONST
{
	return FindIndex(pszName);
}

CHEXSpyLocation *CHEXSpyLocations::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CHEXSpyLocation *)CPtrArray::GetAt(nIndex) : (CHEXSpyLocation *)NULL);
}

CHEXSpyLocation *CHEXSpyLocations::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CHEXSpyLocation *)CPtrArray::GetAt(nIndex) : (CHEXSpyLocation *)NULL);
}

VOID CHEXSpyLocations::RemoveAll()
{
	INT  nLocation;
	INT  nLocations;

	for (nLocation = 0, nLocations = (INT)GetSize(); nLocation < nLocations; nLocation++)
	{
		delete GetAt(nLocation);
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CHEXSpyLocations::Copy(CONST CHEXSpyLocations *pLocations)
{
	INT  nLocation;
	INT  nLocations;
	CHEXSpyLocation  *pLocation;

	for (nLocation = 0, nLocations = (INT)pLocations->GetSize(), RemoveAll(); nLocation < nLocations; nLocation++)
	{
		if ((pLocation = new CHEXSpyLocation) != (CHEXSpyLocation *)NULL)
		{
			pLocation->Copy(pLocations->GetAt(nLocation));
			InsertAt(nLocation, pLocation, 1);
			continue;
		}
		break;
	}
	return((nLocation == nLocations) ? TRUE : FALSE);
}

BOOL CHEXSpyLocations::Compare(CONST CHEXSpyLocations *pLocations) CONST
{
	INT  nLocation;
	INT  nLocations;

	for (nLocation = 0, nLocations = (pLocations->GetSize() == GetSize()) ? (INT)GetSize() : -1; nLocation < nLocations; nLocation++)
	{
		if (!pLocations->GetAt(nLocation)->Compare(GetAt(nLocation))) break;
		continue;
	}
	return((nLocation == nLocations) ? TRUE : FALSE);
}

BOOL CHEXSpyLocations::Map(CByteArray &nInfo) CONST
{
	INT  nLocation;
	INT  nLocations;
	CByteArray  nLocationData;
	CHEXSpyLocation  *pLocation;

	for (nLocation = 0, nLocations = (INT)GetSize(), nInfo.RemoveAll(); nLocation < nLocations; nLocation++)
	{
		if ((pLocation = GetAt(nLocation)) && pLocation->Map(nLocationData) && nInfo.Append(nLocationData) >= 0) continue;
		break;
	}
	return((nLocation == nLocations) ? TRUE : FALSE);
}

BOOL CHEXSpyLocations::Unmap(CONST CByteArray &nInfo)
{
	INT  cbLocation;
	INT  cbLocations;
	CByteArray  nLocationData;
	CHEXSpyLocation  *pLocation;

	for (cbLocations = 0, RemoveAll(); cbLocations < nInfo.GetSize(); cbLocations += cbLocation)
	{
		for (CopyMemory(&cbLocation, nInfo.GetData() + cbLocations, sizeof(cbLocation)), nLocationData.SetSize(max(min(cbLocation, nInfo.GetSize() - cbLocations), 0)); nLocationData.GetSize() >= 0; )
		{
			CopyMemory(nLocationData.GetData(), nInfo.GetData() + cbLocations, nLocationData.GetSize());
			break;
		}
		if ((pLocation = new CHEXSpyLocation))
		{
			if (pLocation->Unmap(nLocationData) && Add(pLocation) >= 0) continue;
			delete pLocation;
		}
		break;
	}
	return((cbLocations == nInfo.GetSize()) ? TRUE : FALSE);
}

INT CHEXSpyLocations::FindIndex(LPCTSTR pszName, BOOL bInsert) CONST
{
	INT  nIndex;

	for (nIndex = 0; nIndex < GetSize(); nIndex++)
	{
		if (GetAt(nIndex)->GetName() == pszName) break;
		continue;
	}
	return(((!bInsert  &&  nIndex < GetSize()) || (bInsert  &&  nIndex == GetSize())) ? nIndex : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CHEXSettingsLayoutPage property page

IMPLEMENT_DYNCREATE(CHEXSettingsLayoutPage, CLocalePropertyPage)

CHEXSettingsLayoutPage::CHEXSettingsLayoutPage() : CLocalePropertyPage(CHEXSettingsLayoutPage::IDD)
{
	//{{AFX_DATA_INIT(CHEXSettingsLayoutPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CHEXSettingsLayoutPage::Initialize()
{
	CHEXOpenDialog  *pDialog;

	if (((pDialog = GetParentDialog()->GetParentDialog()) && (pDialog->GetLayoutFormat(m_nEnumeration[0][0], m_nEnumeration[0][1], m_nLineLength[0], m_nColors[0]) || GetParentDisplay()->GetLayoutFormat(m_nEnumeration[0][0], m_nEnumeration[0][1], m_nLineLength[0], m_nColors[0])) && (pDialog->GetLayoutTitleFont(&m_fntTitle[0]) || GetParentDisplay()->GetTitleFont(&m_fntTitle[0])) && (pDialog->GetLayoutDataFont(&m_fntData[0]) || GetParentDisplay()->GetDataFont(&m_fntData[0])) && (pDialog->GetLayoutSpyFont(&m_fntSpy[0][0], &m_fntSpy[0][1]) || GetParentDisplay()->GetSpyFont(&m_fntSpy[0][0], &m_fntSpy[0][1]))) || (GetParentDisplay()->GetLayoutFormat(m_nEnumeration[0][0], m_nEnumeration[0][1], m_nLineLength[0], m_nColors[0]) && GetParentDisplay()->GetTitleFont(&m_fntTitle[0]) && GetParentDisplay()->GetDataFont(&m_fntData[0]) && GetParentDisplay()->GetSpyFont(&m_fntSpy[0][0], &m_fntSpy[0][1])))
	{
		m_bBadData[0] = m_bBadData[1] = (!pDialog || !pDialog->GetLayoutBadDataMode(m_bBadData[0])) ? GetParentDisplay()->IsBadDataModeEnabled() : m_bBadData[0];
		CopyMemory(&m_fntTitle[1], &m_fntTitle[0], sizeof(LOGFONT));
		CopyMemory(&m_fntData[1], &m_fntData[0], sizeof(LOGFONT));
		CopyMemory(&m_fntSpy[1][0], &m_fntSpy[0][0], sizeof(LOGFONT));
		CopyMemory(&m_fntSpy[1][1], &m_fntSpy[0][1], sizeof(LOGFONT));
		m_nEnumeration[1][0] = m_nEnumeration[0][0];
		m_nEnumeration[1][1] = m_nEnumeration[0][1];
		m_nLineLength[1] = m_nLineLength[0];
		m_nColors[1].Copy(m_nColors[0]);
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXSettingsLayoutPage::GetFormat(UINT &nHorzEnum, UINT &nVertEnum, UINT &nLineLength, CUIntArray &nColors) CONST
{
	nHorzEnum = m_nEnumeration[0][0];
	nVertEnum = m_nEnumeration[0][1];
	nLineLength = m_nLineLength[0];
	nColors.Copy(m_nColors[0]);
	return Check(FALSE);
}

BOOL CHEXSettingsLayoutPage::GetTitleFont(LPLOGFONT pTitleFont) CONST
{
	CopyMemory(pTitleFont, &m_fntTitle[0], sizeof(LOGFONT));
	return Check(FALSE);
}

BOOL CHEXSettingsLayoutPage::GetDataFont(LPLOGFONT pDataFont) CONST
{
	CopyMemory(pDataFont, &m_fntData[0], sizeof(LOGFONT));
	return Check(FALSE);
}

BOOL CHEXSettingsLayoutPage::GetSpyFont(LPLOGFONT pHeaderFont, LPLOGFONT pLocationsFont) CONST
{
	CopyMemory(pHeaderFont, &m_fntSpy[0][0], sizeof(LOGFONT));
	CopyMemory(pLocationsFont, &m_fntSpy[0][1], sizeof(LOGFONT));
	return Check(FALSE);
}

BOOL CHEXSettingsLayoutPage::GetBadDataMode(BOOL &bEnable) CONST
{
	bEnable = m_bBadData[0];
	return Check(FALSE);
}

CHEXSettingsDialog *CHEXSettingsLayoutPage::GetParentDialog() CONST
{
	return((CHEXSettingsDialog *)CLocalePropertyPage::GetParent());
}

CHEXWnd *CHEXSettingsLayoutPage::GetParentDisplay() CONST
{
	return((CHEXWnd *)GetParentDialog()->GetParentDisplay());
}

VOID CHEXSettingsLayoutPage::ShowLayoutFormatInfo(UINT nType)
{
	Spinbox_SetRange(GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_LINELENGTH), HEXSETTINGSLAYOUTPAGE_LINE_MINIMUMLENGTH, HEXSETTINGSLAYOUTPAGE_LINE_MAXIMUMLENGTH);
	Spinbox_SetRange(GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATELINES_INTERVAL), HEXSETTINGSLAYOUTPAGE_ENUMERATION_MINIMUMINTERVAL, HEXSETTINGSLAYOUTPAGE_ENUMERATION_MAXIMUMINTERVAL);
	Spinbox_SetRange(GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATECOLUMNS_INTERVAL), HEXSETTINGSLAYOUTPAGE_ENUMERATION_MINIMUMINTERVAL, HEXSETTINGSLAYOUTPAGE_ENUMERATION_MAXIMUMINTERVAL);
	Spinbox_SetPos(GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_LINELENGTH), m_nLineLength[0]);
	Spinbox_SetPos(GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATELINES_INTERVAL), m_nEnumeration[0][1]);
	Spinbox_SetPos(GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATECOLUMNS_INTERVAL), m_nEnumeration[0][0]);
	SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_COLORSTEXT, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_COLORSTEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)((nType == HEX_TYPE_NORMAL || nType == HEX_TYPE_STREAM) ? STRING(IDS_HEXSETTINGS_LAYOUTPAGE_RAWDATA) : STRING(IDS_HEXSETTINGS_LAYOUTPAGE_NORMALDATA))));
	SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_COLORS, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nColors[0].GetAt((nType == HEX_TYPE_NORMAL || nType == HEX_TYPE_STREAM) ? HEX_LAYOUTCOLOR_RAWDATA : HEX_LAYOUTCOLOR_NORMALDATA));
	CheckDlgButton(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATELINES, ((nType == HEX_TYPE_NORMAL || nType == HEX_TYPE_STREAM) && m_nEnumeration[0][1] > 0) ? TRUE : FALSE);
	CheckDlgButton(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATECOLUMNS, ((nType == HEX_TYPE_NORMAL || nType == HEX_TYPE_STREAM) && m_nEnumeration[0][0] > 0) ? TRUE : FALSE);
	CheckDlgButton(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_BADDATA, m_bBadData[0]);
	CheckRadioButton(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE, IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SPYAREA_LOCATIONS, IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE);
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_LINELENGTH_PHRASEBEGIN)->EnableWindow((nType == HEX_TYPE_NORMAL || nType == HEX_TYPE_STREAM) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_LINELENGTH)->EnableWindow((nType == HEX_TYPE_NORMAL || nType == HEX_TYPE_STREAM) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_LINELENGTH_PHRASEEND)->EnableWindow((nType == HEX_TYPE_NORMAL || nType == HEX_TYPE_STREAM) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_COLORS_PHRASEBEGIN)->EnableWindow();
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_COLORSTEXT)->EnableWindow();
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_COLORS_PHRASEEND)->EnableWindow();
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_COLORS)->EnableWindow();
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATELINES)->EnableWindow((nType == HEX_TYPE_NORMAL || nType == HEX_TYPE_STREAM) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATELINES_PHRASEBEGIN)->EnableWindow((nType == HEX_TYPE_NORMAL || nType == HEX_TYPE_STREAM) ? IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATELINES) : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATELINES_INTERVAL)->EnableWindow((nType == HEX_TYPE_NORMAL || nType == HEX_TYPE_STREAM) ? IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATELINES) : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATELINES_PHRASEEND)->EnableWindow((nType == HEX_TYPE_NORMAL || nType == HEX_TYPE_STREAM) ? IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATELINES) : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATECOLUMNS)->EnableWindow((nType == HEX_TYPE_NORMAL || nType == HEX_TYPE_STREAM) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATECOLUMNS_PHRASEBEGIN)->EnableWindow((nType == HEX_TYPE_NORMAL || nType == HEX_TYPE_STREAM) ? IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATECOLUMNS) : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATECOLUMNS_INTERVAL)->EnableWindow((nType == HEX_TYPE_NORMAL || nType == HEX_TYPE_STREAM) ? IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATECOLUMNS) : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATECOLUMNS_PHRASEEND)->EnableWindow((nType == HEX_TYPE_NORMAL || nType == HEX_TYPE_STREAM) ? IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATECOLUMNS) : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_BADDATA)->EnableWindow();
}

VOID CHEXSettingsLayoutPage::ShowLayoutFontDetails()
{
	INT  nSize;
	INT  nSizes;
	INT  nStyle;
	INT  nStyles;
	BOOL  bUnderlined;
	CStringArray  szSizes;
	CStringArray  szStyles;
	CFontTools  cFontTools;

	for (SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_RESETCONTENT), SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_RESETCONTENT), SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)((IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE)) ? m_fntTitle[0].lfFaceName : ((IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_DATA)) ? m_fntData[0].lfFaceName : ((IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SPYAREA_HEADER)) ? m_fntSpy[0][0].lfFaceName : m_fntSpy[0][1].lfFaceName))))); (IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE) && cFontTools.EnumerateFont(m_fntTitle[0].lfFaceName, szStyles, szSizes, bUnderlined)) || (IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_DATA) && cFontTools.EnumerateFont(m_fntData[0].lfFaceName, szStyles, szSizes, bUnderlined)) || (IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SPYAREA_HEADER) && cFontTools.EnumerateFont(m_fntSpy[0][0].lfFaceName, szStyles, szSizes, bUnderlined)) || (IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SPYAREA_LOCATIONS) && cFontTools.EnumerateFont(m_fntSpy[0][1].lfFaceName, szStyles, szSizes, bUnderlined)); )
	{
		for (nStyle = 0, nStyles = (INT)szStyles.GetSize(); nStyle < nStyles; nStyle++) SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szStyles.GetAt(nStyle));
		for (nSize = 0, nSizes = (INT)szSizes.GetSize(); nSize < nSizes; nSize++) SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szSizes.GetAt(nSize));
		break;
	}
	if (IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_fntTitle[0])), 0));
		SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntTitle[0])), max(SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntTitle[1])), 0)));
	}
	if (IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_DATA))
	{
		SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_fntData[0])), 0));
		SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntData[0])), max(SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntData[1])), 0)));
	}
	if (IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SPYAREA_HEADER))
	{
		SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_fntSpy[0][0])), 0));
		SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntSpy[0][0])), max(SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntSpy[1][0])), 0)));
	}
	if (IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SPYAREA_LOCATIONS))
	{
		SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_fntSpy[0][1])), 0));
		SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntSpy[0][1])), max(SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntSpy[1][1])), 0)));
	}
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_STYLE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_STYLE)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SIZE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SIZE)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SAMPLE)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CHEXSettingsLayoutPage::ShowLayoutFontSample()
{
	CRect  rSampleText;

	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->GetWindowRect(rSampleText);
	ScreenToClient(rSampleText);
	InvalidateRect(rSampleText);
	UpdateWindow();
}

BOOL CHEXSettingsLayoutPage::IsModified(BOOL bAll) CONST
{
	INT  nColor;
	INT  nColors;
	CFontTools  cFontTools;

	if (IsWindow(GetSafeHwnd()) && !bAll)
	{
		if (m_nLineLength[0] == m_nLineLength[1] && m_nEnumeration[0][0] == m_nEnumeration[1][0] && m_nEnumeration[0][1] == m_nEnumeration[1][1])
		{
			if (!lstrcmp(m_fntTitle[0].lfFaceName, m_fntTitle[1].lfFaceName) && (m_fntTitle[0].lfHeight == m_fntTitle[1].lfHeight || cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntTitle[0])) == cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntTitle[1]))) && m_fntTitle[0].lfWeight == m_fntTitle[1].lfWeight  &&  m_fntTitle[0].lfItalic == m_fntTitle[1].lfItalic  &&  !lstrcmp(m_fntData[0].lfFaceName, m_fntData[1].lfFaceName) && (m_fntData[0].lfHeight == m_fntData[1].lfHeight || cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntData[0])) == cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntData[1]))) && m_fntData[0].lfWeight == m_fntData[1].lfWeight  &&  m_fntData[0].lfItalic == m_fntData[1].lfItalic  &&  !lstrcmp(m_fntSpy[0][0].lfFaceName, m_fntSpy[1][0].lfFaceName) && (m_fntSpy[0][0].lfHeight == m_fntSpy[1][0].lfHeight || cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntSpy[0][0])) == cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntSpy[1][0]))) && m_fntSpy[0][0].lfWeight == m_fntSpy[1][0].lfWeight  &&  m_fntSpy[0][0].lfItalic == m_fntSpy[1][0].lfItalic  &&  !lstrcmp(m_fntSpy[0][1].lfFaceName, m_fntSpy[1][1].lfFaceName) && (m_fntSpy[0][1].lfHeight == m_fntSpy[1][1].lfHeight || cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntSpy[0][1])) == cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntSpy[1][1]))) && m_fntSpy[0][1].lfWeight == m_fntSpy[1][1].lfWeight  &&  m_fntSpy[0][1].lfItalic == m_fntSpy[1][1].lfItalic  &&  m_bBadData[0] == m_bBadData[1])
			{
				for (nColor = 0, nColors = (m_nColors[0].GetSize() == m_nColors[1].GetSize()) ? (INT)m_nColors[0].GetSize() : 0; nColor < nColors; nColor++)
				{
					if (m_nColors[0].GetAt(nColor) != m_nColors[1].GetAt(nColor)) break;
					continue;
				}
				return((nColor < nColors) ? TRUE : FALSE);
			}
		}
		return TRUE;
	}
	return((bAll) ? CLocalePropertyPage::IsModified() : FALSE);
}

BOOL CHEXSettingsLayoutPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_NAMES)->GetWindowTextLength() > 0 && GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowTextLength() > 0 && GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowTextLength() > 0) : CLocalePropertyPage::Check()) : TRUE);
}

void CHEXSettingsLayoutPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHEXSettingsLayoutPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CHEXSettingsLayoutPage::PostNcDestroy()
{
	m_nColors[0].RemoveAll();
	m_nColors[1].RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CHEXSettingsLayoutPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CHEXSettingsLayoutPage)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATELINES, OnEnumerateLines)
	ON_BN_CLICKED(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATECOLUMNS, OnEnumerateColumns)
	ON_BN_CLICKED(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_BADDATA, OnBadData)
	ON_BN_CLICKED(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE, OnTitleFont)
	ON_BN_CLICKED(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_DATA, OnDataFont)
	ON_BN_CLICKED(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SPYAREA_HEADER, OnSpyHeaderFont)
	ON_BN_CLICKED(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SPYAREA_LOCATIONS, OnSpyLocationsFont)
	ON_CBN_EDITCHANGE(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_NAMES, OnEditchangeFontName)
	ON_CBN_SELCHANGE(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_COLORSTEXT, OnSelchangeDataColorText)
	ON_CBN_SELCHANGE(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_COLORS, OnSelchangeDataColor)
	ON_CBN_SELCHANGE(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_NAMES, OnSelchangeFontName)
	ON_CBN_SELCHANGE(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_STYLE, OnSelchangeFontStyle)
	ON_CBN_SELCHANGE(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SIZE, OnSelchangeFontSize)
	ON_CONTROL(SBXN_CHANGE, IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_LINELENGTH, OnSpinchangeLineLength)
	ON_CONTROL(SBXN_CHANGE, IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATELINES_INTERVAL, OnSpinchangeLineEnumeration)
	ON_CONTROL(SBXN_CHANGE, IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATECOLUMNS_INTERVAL, OnSpinchangeColumnEnumeration)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHEXSettingsLayoutPage message handlers

BOOL CHEXSettingsLayoutPage::OnInitDialog()
{
	UINT  nType;
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_COLORSTEXT, ((nType = (GetParentDialog()->GetParentDialog()) ? GetParentDialog()->GetParentDialog()->GetType() : HIWORD(GetParentDisplay()->GetType())) == HEX_TYPE_DUMPS) ? CB_ADDSTRING : CB_SELECTSTRING, (WPARAM)NULL, (LPARAM)STRING(IDS_HEXSETTINGS_LAYOUTPAGE_NORMALDATA));
	SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_COLORSTEXT, (nType == HEX_TYPE_NORMAL || nType == HEX_TYPE_STREAM) ? CB_ADDSTRING : CB_SELECTSTRING, (WPARAM)NULL, (LPARAM)STRING(IDS_HEXSETTINGS_LAYOUTPAGE_RAWDATA));
	SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_COLORSTEXT, (nType == HEX_TYPE_NORMAL || nType == HEX_TYPE_STREAM) ? CB_ADDSTRING : CB_SELECTSTRING, (WPARAM)NULL, (LPARAM)STRING(IDS_HEXSETTINGS_LAYOUTPAGE_ENUMERATIONS));
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->GetWindowText(m_szFontSampleText);
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT)->EnableWindow();
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS)->EnableWindow();
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_STATIC)->EnableWindow();
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE)->EnableWindow();
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_DATA)->EnableWindow();
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SPYAREA_STATIC)->EnableWindow();
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SPYAREA_HEADER)->EnableWindow((nType == HEX_TYPE_NORMAL || nType == HEX_TYPE_STREAM) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SPYAREA_LOCATIONS)->EnableWindow((nType == HEX_TYPE_NORMAL || nType == HEX_TYPE_STREAM) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_CHARACTERISTICS)->EnableWindow();
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_NAMES_STATIC)->EnableWindow();
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_NAMES)->EnableWindow();
	SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_NAMES, FCB_DIR, CF_EFFECTS | CF_SCREENFONTS);
	SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)m_fntTitle[0].lfFaceName));
	ShowLayoutFormatInfo(nType);
	ShowLayoutFontDetails();
	return TRUE;
}

void CHEXSettingsLayoutPage::OnPaint()
{
	INT  nBkMode;
	CFont  cFont;
	CFont  *pOldFont;
	CRect  rSampleText;
	COLORREF  nOldColor;
	CPaintDC  cDC(this);

	for (GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->GetWindowRect(rSampleText), ScreenToClient(rSampleText); cFont.CreateFontIndirect((IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE)) ? &m_fntTitle[0] : ((IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_DATA)) ? &m_fntData[0] : ((IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SPYAREA_HEADER)) ? &m_fntSpy[0][0] : &m_fntSpy[0][1]))); )
	{
		if ((pOldFont = cDC.SelectObject(&cFont)))
		{
			nBkMode = cDC.SetBkMode(TRANSPARENT);
			nOldColor = cDC.SetTextColor((SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? GetSysColor(COLOR_WINDOWTEXT) : GetSysColor(COLOR_GRAYTEXT));
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

void CHEXSettingsLayoutPage::OnEnumerateLines()
{
	m_nEnumeration[0][1] = (IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATELINES)) ? HEXSETTINGSLAYOUTPAGE_ENUMERATION_DEFAULTINTERVAL : 0;
	Spinbox_SetPos(GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATELINES_INTERVAL), HEXSETTINGSLAYOUTPAGE_ENUMERATION_DEFAULTINTERVAL);
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATELINES_PHRASEBEGIN)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATELINES));
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATELINES_INTERVAL)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATELINES));
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATELINES_PHRASEEND)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATELINES));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsLayoutPage::OnEnumerateColumns()
{
	m_nEnumeration[0][0] = (IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATECOLUMNS)) ? HEXSETTINGSLAYOUTPAGE_ENUMERATION_DEFAULTINTERVAL : 0;
	Spinbox_SetPos(GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATECOLUMNS_INTERVAL), HEXSETTINGSLAYOUTPAGE_ENUMERATION_DEFAULTINTERVAL);
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATECOLUMNS_PHRASEBEGIN)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATECOLUMNS));
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATECOLUMNS_INTERVAL)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATECOLUMNS));
	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATECOLUMNS_PHRASEEND)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATECOLUMNS));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsLayoutPage::OnBadData()
{
	m_bBadData[0] = IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_BADDATA);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsLayoutPage::OnTitleFont()
{
	CheckDlgButton(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE, TRUE);
	CheckDlgButton(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_DATA, FALSE);
	CheckDlgButton(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SPYAREA_HEADER, FALSE);
	CheckDlgButton(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SPYAREA_LOCATIONS, FALSE);
	ShowLayoutFontDetails();
	ShowLayoutFontSample();
}

void CHEXSettingsLayoutPage::OnDataFont()
{
	CheckDlgButton(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE, FALSE);
	CheckDlgButton(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_DATA, TRUE);
	CheckDlgButton(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SPYAREA_HEADER, FALSE);
	CheckDlgButton(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SPYAREA_LOCATIONS, FALSE);
	ShowLayoutFontDetails();
	ShowLayoutFontSample();
}

void CHEXSettingsLayoutPage::OnSpyHeaderFont()
{
	CheckDlgButton(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE, FALSE);
	CheckDlgButton(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_DATA, FALSE);
	CheckDlgButton(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SPYAREA_HEADER, TRUE);
	CheckDlgButton(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SPYAREA_LOCATIONS, FALSE);
	ShowLayoutFontDetails();
	ShowLayoutFontSample();
}

void CHEXSettingsLayoutPage::OnSpyLocationsFont()
{
	CheckDlgButton(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE, FALSE);
	CheckDlgButton(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_DATA, FALSE);
	CheckDlgButton(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SPYAREA_HEADER, FALSE);
	CheckDlgButton(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SPYAREA_LOCATIONS, TRUE);
	ShowLayoutFontDetails();
	ShowLayoutFontSample();
}

void CHEXSettingsLayoutPage::OnEditchangeFontName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsLayoutPage::OnSelchangeDataColorText()
{
	CString  szColorsText;

	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_COLORSTEXT)->GetWindowText(szColorsText);
	SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_COLORS, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nColors[0].GetAt((szColorsText != STRING(IDS_HEXSETTINGS_LAYOUTPAGE_NORMALDATA)) ? ((szColorsText != STRING(IDS_HEXSETTINGS_LAYOUTPAGE_RAWDATA)) ? HEX_LAYOUTCOLOR_ENUMERATIONS : HEX_LAYOUTCOLOR_RAWDATA) : HEX_LAYOUTCOLOR_NORMALDATA));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsLayoutPage::OnSelchangeDataColor()
{
	CString  szColorsText;

	GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_COLORSTEXT)->GetWindowText(szColorsText);
	m_nColors[0].SetAt((szColorsText != STRING(IDS_HEXSETTINGS_LAYOUTPAGE_NORMALDATA)) ? ((szColorsText != STRING(IDS_HEXSETTINGS_LAYOUTPAGE_RAWDATA)) ? HEX_LAYOUTCOLOR_ENUMERATIONS : HEX_LAYOUTCOLOR_RAWDATA) : HEX_LAYOUTCOLOR_NORMALDATA, (UINT)SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_COLORS, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_COLORS, CB_GETCURSEL)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsLayoutPage::OnSelchangeFontName()
{
	CString  szSize;
	CString  szStyle;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		_tcscpy_s(m_fntTitle[0].lfFaceName, sizeof(m_fntTitle[0].lfFaceName) / sizeof(TCHAR), Combobox_GetText(GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_NAMES), (INT)SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_GETCURSEL)));
		ShowLayoutFontDetails();
	}
	if (IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_DATA))
	{
		_tcscpy_s(m_fntData[0].lfFaceName, sizeof(m_fntData[0].lfFaceName) / sizeof(TCHAR), Combobox_GetText(GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_NAMES), (INT)SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_GETCURSEL)));
		ShowLayoutFontDetails();
	}
	if (IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SPYAREA_HEADER))
	{
		_tcscpy_s(m_fntSpy[0][0].lfFaceName, sizeof(m_fntSpy[0][0].lfFaceName) / sizeof(TCHAR), Combobox_GetText(GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_NAMES), (INT)SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_GETCURSEL)));
		ShowLayoutFontDetails();
	}
	if (IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SPYAREA_LOCATIONS))
	{
		_tcscpy_s(m_fntSpy[0][1].lfFaceName, sizeof(m_fntSpy[0][1].lfFaceName) / sizeof(TCHAR), Combobox_GetText(GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_NAMES), (INT)SendDlgItemMessage(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_GETCURSEL)));
		ShowLayoutFontDetails();
	}
	if (IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntTitle[0].lfWeight, m_fntTitle[0].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_fntTitle[0].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_fntTitle[0]);
	}
	if (IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_DATA))
	{
		GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntData[0].lfWeight, m_fntData[0].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_fntData[0].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_fntData[0]);
	}
	if (IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SPYAREA_HEADER))
	{
		GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntSpy[0][0].lfWeight, m_fntSpy[0][0].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_fntSpy[0][0].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_fntSpy[0][0]);
	}
	if (IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SPYAREA_LOCATIONS))
	{
		GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntSpy[0][1].lfWeight, m_fntSpy[0][1].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_fntSpy[0][1].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_fntSpy[0][1]);
	}
	ShowLayoutFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsLayoutPage::OnSelchangeFontStyle()
{
	CString  szStyle;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntTitle[0].lfWeight, m_fntTitle[0].lfItalic);
	}
	if (IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_DATA))
	{
		GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntData[0].lfWeight, m_fntData[0].lfItalic);
	}
	if (IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SPYAREA_HEADER))
	{
		GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntSpy[0][0].lfWeight, m_fntSpy[0][0].lfItalic);
	}
	if (IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SPYAREA_LOCATIONS))
	{
		GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntSpy[0][1].lfWeight, m_fntSpy[0][1].lfItalic);
	}
	ShowLayoutFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsLayoutPage::OnSelchangeFontSize()
{
	CString  szSize;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_fntTitle[0].lfHeight);
	}
	if (IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_DATA))
	{
		GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_fntData[0].lfHeight);
	}
	if (IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SPYAREA_HEADER))
	{
		GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_fntSpy[0][0].lfHeight);
	}
	if (IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SPYAREA_LOCATIONS))
	{
		GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_fntSpy[0][1].lfHeight);
	}
	ShowLayoutFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsLayoutPage::OnSpinchangeLineLength()
{
	m_nLineLength[0] = (UINT)Spinbox_GetPos(GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_LINELENGTH));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsLayoutPage::OnSpinchangeLineEnumeration()
{
	m_nEnumeration[0][1] = (IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATELINES)) ? (UINT)Spinbox_GetPos(GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATELINES_INTERVAL)) : 0;
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsLayoutPage::OnSpinchangeColumnEnumeration()
{
	m_nEnumeration[0][0] = (IsDlgButtonChecked(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATECOLUMNS)) ? (UINT)Spinbox_GetPos(GetDlgItem(IDC_HEXSETTINGS_LAYOUTPAGE_FORMAT_ENUMERATECOLUMNS_INTERVAL)) : 0;
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CHEXSettingsContentsPage property page

IMPLEMENT_DYNCREATE(CHEXSettingsContentsPage, CLocalePropertyPage)

CHEXSettingsContentsPage::CHEXSettingsContentsPage() : CLocalePropertyPage(CHEXSettingsContentsPage::IDD)
{
	//{{AFX_DATA_INIT(CHEXSettingsContentsPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CHEXSettingsContentsPage::Initialize()
{
	CHEXOpenDialog  *pDialog;

	return((((pDialog = GetParentDialog()->GetParentDialog()) && pDialog->GetSpyLocations(m_pSpyLocations[0])) || GetParentDisplay()->GetLayoutContents(m_pSpyLocations[0])) ? m_pSpyLocations[1].Copy(&m_pSpyLocations[0]) : FALSE);
}

BOOL CHEXSettingsContentsPage::GetSpyLocations(CHEXSpyLocations &pSpyLocations) CONST
{
	return((pSpyLocations.Copy(&m_pSpyLocations[0])) ? Check(FALSE) : FALSE);
}

CHEXSettingsDialog *CHEXSettingsContentsPage::GetParentDialog() CONST
{
	return((CHEXSettingsDialog *)CLocalePropertyPage::GetParent());
}

CHEXWnd *CHEXSettingsContentsPage::GetParentDisplay() CONST
{
	return((CHEXWnd *)GetParentDialog()->GetParentDisplay());
}

BOOL CHEXSettingsContentsPage::EnumSpyLocations()
{
	INT  nItem;
	INT  nItems;
	INT  nColumn;
	INT  nColumns;
	UINT  nByte;
	UINT  nBit;
	UINT  nLength;
	CString  szItem;
	CStringTools  cStringTools;
	CHEXSpyLocation  *pLocation;

	SendDlgItemMessage(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS, LVM_DELETEALLITEMS);
	for (nItem = 0, nItems = (INT)m_pSpyLocations[0].GetSize(); nItem < nItems; nItem++)
	{
		if ((pLocation = m_pSpyLocations[0].GetAt(nItem)) && pLocation->GetPosition(nByte, nBit, nLength))
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn = nColumn + 1)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_HEXSETTINGS_CONTENTSPAGE_LOCATIONDESCRIPTION); )
				{
					szItem = pLocation->GetName();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_HEXSETTINGS_CONTENTSPAGE_LOCATIONBYTE); )
				{
					szItem = cStringTools.ConvertUIntToString(nByte);
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_HEXSETTINGS_CONTENTSPAGE_LOCATIONBIT); )
				{
					szItem = cStringTools.ConvertUIntToString(nBit);
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_HEXSETTINGS_CONTENTSPAGE_LOCATIONLENGTH); )
				{
					szItem = cStringTools.ConvertUIntToString(nLength);
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS), nItem, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS), nItem, nColumn, szItem);
			}
		}
	}
	Listview_SetCurText(GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS), 0);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return((nItem == nItems) ? TRUE : FALSE);
}

VOID CHEXSettingsContentsPage::SetSpyLocation(CONST CHEXSpyLocation *pLocation)
{
	UINT  nBit;
	UINT  nByte;
	UINT  nLength;
	CStringTools  cStringTools;

	if (pLocation != (CHEXSpyLocation *)NULL)
	{
		CheckDlgButton(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_CODING_HEXADECIMAL, (pLocation->GetCoding() == HEXSPYLOCATION_CODING_HEXADECIMAL) ? TRUE : FALSE);
		CheckDlgButton(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_CODING_DECIMAL, (pLocation->GetCoding() == HEXSPYLOCATION_CODING_DECIMAL) ? TRUE : FALSE);
		CheckDlgButton(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_CODING_OCTAL, (pLocation->GetCoding() == HEXSPYLOCATION_CODING_OCTAL) ? TRUE : FALSE);
		CheckDlgButton(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_CODING_BINARY, (pLocation->GetCoding() == HEXSPYLOCATION_CODING_BINARY) ? TRUE : FALSE);
		GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_POSITION_BYTE)->SetWindowText((pLocation->GetPosition(nByte, nBit, nLength)) ? cStringTools.ConvertUIntToString(nByte) : EMPTYSTRING);
		GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_POSITION_BIT)->SetWindowText((pLocation->GetPosition(nByte, nBit, nLength)) ? cStringTools.ConvertUIntToString(nBit) : EMPTYSTRING);
		GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_POSITION_LENGTH)->SetWindowText((pLocation->GetPosition(nByte, nBit, nLength)) ? cStringTools.ConvertUIntToString(nLength) : EMPTYSTRING);
		GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_DESCRIPTION)->SetWindowText(pLocation->GetName());
		m_nColors[0] = pLocation->GetDetailsColor();
		m_nColors[1] = pLocation->GetValueColor();
	}
	else
	{
		CheckDlgButton(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_CODING_HEXADECIMAL, TRUE);
		CheckDlgButton(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_CODING_DECIMAL, FALSE);
		CheckDlgButton(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_CODING_OCTAL, FALSE);
		CheckDlgButton(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_CODING_BINARY, FALSE);
		GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_POSITION_BYTE)->SetWindowText(EMPTYSTRING);
		GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_POSITION_BIT)->SetWindowText(EMPTYSTRING);
		GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_POSITION_LENGTH)->SetWindowText(EMPTYSTRING);
		GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_DESCRIPTION)->SetWindowText(EMPTYSTRING);
	}
	SendDlgItemMessage(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_COLORTEXT, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_COLORTEXT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_HEXSETTINGS_CONTENTSPAGE_SPYDETAILSCOLOR)));
	SendDlgItemMessage(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nColors[0]);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES)->EnableWindow();
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_CODING)->EnableWindow();
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_CODING_HEXADECIMAL)->EnableWindow();
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_CODING_DECIMAL)->EnableWindow();
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_CODING_OCTAL)->EnableWindow();
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_CODING_BINARY)->EnableWindow();
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_COLORTEXT_STATIC)->EnableWindow();
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_COLORTEXT)->EnableWindow();
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_COLOR_STATIC)->EnableWindow();
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_COLOR)->EnableWindow();
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_POSITION)->EnableWindow();
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_POSITION_BYTE_STATIC)->EnableWindow();
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_POSITION_BYTE)->EnableWindow();
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_POSITION_BIT_STATIC)->EnableWindow();
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_POSITION_BIT)->EnableWindow();
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_POSITION_LENGTH_STATIC)->EnableWindow();
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_POSITION_LENGTH)->EnableWindow();
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_DESCRIPTION_STATIC)->EnableWindow();
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_DESCRIPTION)->EnableWindow();
}

BOOL CHEXSettingsContentsPage::GetSpyLocation(CHEXSpyLocation *pLocation) CONST
{
	CString  szBit;
	CString  szByte;
	CString  szLength;
	CString  szDescription;

	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_POSITION_BYTE)->GetWindowText(szByte);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_POSITION_BIT)->GetWindowText(szBit);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_POSITION_LENGTH)->GetWindowText(szLength);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_DESCRIPTION)->GetWindowText(szDescription);
	if ((IsDlgButtonChecked(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_CODING_HEXADECIMAL) || IsDlgButtonChecked(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_CODING_DECIMAL) || IsDlgButtonChecked(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_CODING_OCTAL) || IsDlgButtonChecked(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_CODING_BINARY)) && GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_COLOR)->SendMessage(CB_GETCURSEL) != CB_ERR  &&  !szDescription.IsEmpty() && !szByte.IsEmpty() && !szBit.IsEmpty() && !szLength.IsEmpty())
	{
		pLocation->SetCoding((IsDlgButtonChecked(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_CODING_HEXADECIMAL)) ? HEXSPYLOCATION_CODING_HEXADECIMAL : ((IsDlgButtonChecked(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_CODING_DECIMAL)) ? HEXSPYLOCATION_CODING_DECIMAL : ((IsDlgButtonChecked(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_CODING_OCTAL)) ? HEXSPYLOCATION_CODING_OCTAL : HEXSPYLOCATION_CODING_BINARY)));
		pLocation->SetPosition(_ttoi(szByte), _ttoi(szBit), _ttoi(szLength));
		pLocation->SetDetailsColor(m_nColors[0]);
		pLocation->SetValueColor(m_nColors[1]);
		pLocation->SetName(szDescription);
		return TRUE;
	}
	return FALSE;
}

CHEXSpyLocation *CHEXSettingsContentsPage::FindSpyLocation() CONST
{
	CString  szDescription;

	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_DESCRIPTION)->GetWindowText(szDescription);
	return m_pSpyLocations[0].GetAt(m_pSpyLocations[0].Find(szDescription));
}

BOOL CHEXSettingsContentsPage::CheckSpyLocation() CONST
{
	CHEXSpyLocation  cLocation;

	return(((FindSpyLocation() && GetSpyLocation(&cLocation) && !cLocation.Compare(FindSpyLocation())) || (!FindSpyLocation() && GetSpyLocation(&cLocation))) ? TRUE : FALSE);
}

INT CHEXSettingsContentsPage::CalcColumnWidth(LPCTSTR pszColumn)
{
	CDC  *pDC;
	CFont  *pOldFont;
	CSize  sizeColumn;

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(GetFont())))
		{
			sizeColumn = pDC->GetTextExtent(pszColumn);
			sizeColumn.cx += 2 * CalcColumnIndent();
			pDC->SelectObject(pOldFont);
			ReleaseDC(pDC);
			return sizeColumn.cx;
		}
		ReleaseDC(pDC);
	}
	return 0;
}

INT CHEXSettingsContentsPage::CalcColumnIndent() CONST
{
	return 3 * GetSystemMetrics(SM_CXEDGE);
}

BOOL CHEXSettingsContentsPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? !m_pSpyLocations[0].Compare(&m_pSpyLocations[1]) : CLocalePropertyPage::IsModified()) : FALSE);
}

BOOL CHEXSettingsContentsPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? TRUE : CLocalePropertyPage::Check()) : TRUE);
}

void CHEXSettingsContentsPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHEXSettingsContentsPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CHEXSettingsContentsPage::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_pSpyLocations[0].RemoveAll();
	m_pSpyLocations[1].RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CHEXSettingsContentsPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CHEXSettingsContentsPage)
	ON_BN_CLICKED(IDC_HEXSETTINGS_CONTENTSPAGE_ADD, OnAddLocation)
	ON_BN_CLICKED(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY, OnModifyLocation)
	ON_BN_CLICKED(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVE, OnRemoveLocation)
	ON_BN_CLICKED(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVEALL, OnRemoveAllLocations)
	ON_BN_CLICKED(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_CODING_HEXADECIMAL, OnCodingHexadecimal)
	ON_BN_CLICKED(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_CODING_DECIMAL, OnCodingDecimal)
	ON_BN_CLICKED(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_CODING_OCTAL, OnCodingOctal)
	ON_BN_CLICKED(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_CODING_BINARY, OnCodingBinary)
	ON_CBN_SELCHANGE(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_COLORTEXT, OnSelchangeColorText)
	ON_CBN_SELCHANGE(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_COLOR, OnSelchangeColor)
	ON_EN_CHANGE(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_POSITION_BYTE, OnEditchangeByte)
	ON_EN_CHANGE(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_POSITION_BIT, OnEditchangeBit)
	ON_EN_CHANGE(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_POSITION_LENGTH, OnEditchangeLength)
	ON_EN_CHANGE(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_DESCRIPTION, OnEditchangeDescription)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHEXSettingsContentsPage message handlers

BOOL CHEXSettingsContentsPage::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHEXSpyLocation  *pLocation;
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	m_szColumns.Add(STRING(IDS_HEXSETTINGS_CONTENTSPAGE_LOCATIONBYTE));
	m_szColumns.Add(STRING(IDS_HEXSETTINGS_CONTENTSPAGE_LOCATIONBIT));
	m_szColumns.Add(STRING(IDS_HEXSETTINGS_CONTENTSPAGE_LOCATIONLENGTH));
	m_szColumns.Add(STRING(IDS_HEXSETTINGS_CONTENTSPAGE_LOCATIONDESCRIPTION));
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS)->GetClientRect(rColumns);
	SendDlgItemMessage(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_POSITION_BIT, EM_LIMITTEXT, 1);
	SendDlgItemMessage(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_POSITION_LENGTH, EM_LIMITTEXT, 2);
	SendDlgItemMessage(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_COLORTEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)STRING(IDS_HEXSETTINGS_CONTENTSPAGE_SPYDETAILSCOLOR));
	SendDlgItemMessage(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_COLORTEXT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)STRING(IDS_HEXSETTINGS_CONTENTSPAGE_SPYVALUECOLOR));
	SendDlgItemMessage(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = CalcColumnWidth(m_szColumns.GetAt(nColumn)); nColumn < nColumns; nWidth = (++nColumn < nColumns - 1) ? CalcColumnWidth(m_szColumns.GetAt(nColumn)) : rColumns.Width())
	{
		Listview_InsertColumn(GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		rColumns.DeflateRect(nWidth, 0, 0, 0);
	}
	for (EnumSpyLocations(), m_nColors[0] = m_nColors[1] = VGA_COLOR_BLACK; (pLocation = m_pSpyLocations[0].GetAt(0)); )
	{
		m_nColors[0] = pLocation->GetDetailsColor();
		m_nColors[1] = pLocation->GetValueColor();
		break;
	}
	SetSpyLocation(pLocation);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->ShowWindow((!FindSpyLocation()) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->EnableWindow((!FindSpyLocation() && CheckSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->ShowWindow((FindSpyLocation()) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow((FindSpyLocation() && CheckSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVE)->EnableWindow((FindSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	return TRUE;
}

BOOL CHEXSettingsContentsPage::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED && (pNotifyListView->uNewState & LVIS_SELECTED))
		{
			SetSpyLocation(m_pSpyLocations[0].GetAt(pNotifyListView->iItem));
			GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->EnableWindow(FALSE);
			GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow(FALSE);
			GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVE)->EnableWindow(TRUE);
			GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVEALL)->EnableWindow(TRUE);
		}
	}
	return CLocalePropertyPage::OnNotify(wParam, lParam, pResult);
}

void CHEXSettingsContentsPage::OnAddLocation()
{
	INT  nIndex;
	INT  nColumn;
	INT  nColumns;
	UINT  nByte;
	UINT  nBit;
	UINT  nLength;
	CString  szItem;
	CStringTools  cStringTools;
	CHEXSpyLocation  *pLocation;
	CHourglassCursor  cCursor;

	if ((pLocation = new CHEXSpyLocation))
	{
		if (GetSpyLocation(pLocation) && pLocation->GetPosition(nByte, nBit, nLength))
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nIndex = m_pSpyLocations[0].Add(pLocation); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_HEXSETTINGS_CONTENTSPAGE_LOCATIONDESCRIPTION); )
				{
					szItem = pLocation->GetName();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_HEXSETTINGS_CONTENTSPAGE_LOCATIONBYTE); )
				{
					szItem = cStringTools.ConvertUIntToString(nByte);
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_HEXSETTINGS_CONTENTSPAGE_LOCATIONBIT); )
				{
					szItem = cStringTools.ConvertUIntToString(nBit);
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_HEXSETTINGS_CONTENTSPAGE_LOCATIONLENGTH); )
				{
					szItem = cStringTools.ConvertUIntToString(nLength);
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS), nIndex, szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS), nIndex, nColumn, szItem);
			}
			Listview_SetCurText(GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS), nIndex);
			GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS_STATIC)->EnableWindow();
			GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS)->EnableWindow();
			GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->EnableWindow(FALSE);
			GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow(FALSE);
			GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVE)->EnableWindow(TRUE);
			GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVEALL)->EnableWindow(TRUE);
			GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS)->SetFocus();
			GetDlgItem(IDOK)->EnableWindow(Check());
			return;
		}
		delete pLocation;
	}
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->ShowWindow((!FindSpyLocation()) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->EnableWindow((!FindSpyLocation() && CheckSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->ShowWindow((FindSpyLocation()) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow((FindSpyLocation() && CheckSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVE)->EnableWindow((FindSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsContentsPage::OnModifyLocation()
{
	INT  nIndex;
	INT  nColumn;
	INT  nColumns;
	UINT  nByte;
	UINT  nBit;
	UINT  nLength;
	CString  szItem;
	CStringTools  cStringTools;
	CHEXSpyLocation  *pLocation;
	CHourglassCursor  cCursor;

	if ((pLocation = FindSpyLocation()))
	{
		if (GetSpyLocation(pLocation) && pLocation->GetPosition(nByte, nBit, nLength))
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nIndex = m_pSpyLocations[0].Find(pLocation->GetName()); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_HEXSETTINGS_CONTENTSPAGE_LOCATIONDESCRIPTION); )
				{
					szItem = pLocation->GetName();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_HEXSETTINGS_CONTENTSPAGE_LOCATIONBYTE); )
				{
					szItem = cStringTools.ConvertUIntToString(nByte);
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_HEXSETTINGS_CONTENTSPAGE_LOCATIONBIT); )
				{
					szItem = cStringTools.ConvertUIntToString(nBit);
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_HEXSETTINGS_CONTENTSPAGE_LOCATIONLENGTH); )
				{
					szItem = cStringTools.ConvertUIntToString(nLength);
					break;
				}
				Listview_SetText(GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS), nIndex, nColumn, szItem);
			}
			Listview_SetCurText(GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS), nIndex);
			GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS_STATIC)->EnableWindow();
			GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS)->EnableWindow();
			GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->EnableWindow(FALSE);
			GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow(FALSE);
			GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVE)->EnableWindow(TRUE);
			GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVEALL)->EnableWindow(TRUE);
			GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS)->SetFocus();
			GetDlgItem(IDOK)->EnableWindow(Check());
			return;
		}
	}
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->ShowWindow((!FindSpyLocation()) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->EnableWindow((!FindSpyLocation() && CheckSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->ShowWindow((FindSpyLocation()) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow((FindSpyLocation() && CheckSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVE)->EnableWindow((FindSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsContentsPage::OnRemoveLocation()
{
	INT  nIndex;
	CHEXSpyLocation  *pLocation;
	CHourglassCursor  cCursor;

	if ((pLocation = FindSpyLocation()))
	{
		if ((nIndex = m_pSpyLocations[0].Find(pLocation->GetName())) >= 0)
		{
			Listview_DeleteText(GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS), nIndex);
			delete m_pSpyLocations[0].GetAt(nIndex);
			m_pSpyLocations[0].RemoveAt(nIndex);
		}
	}
	if (SendDlgItemMessage(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS, LVM_GETITEMCOUNT) > 0)
	{
		Listview_SetCurText(GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS), 0);
		GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->EnableWindow(FALSE);
		GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow(FALSE);
		GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVE)->EnableWindow(TRUE);
		GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVEALL)->EnableWindow(TRUE);
		GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS)->SetFocus();
		GetDlgItem(IDOK)->EnableWindow(Check());
		return;
	}
	for (m_pSpyLocations[0].RemoveAll(), m_nColors[0] = m_nColors[1] = VGA_COLOR_BLACK; !m_pSpyLocations[0].GetSize(); )
	{
		SetSpyLocation();
		break;
	}
	SendDlgItemMessage(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS, LVM_DELETEALLITEMS);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVEALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_DESCRIPTION)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsContentsPage::OnRemoveAllLocations()
{
	CHourglassCursor  cCursor;

	for (m_pSpyLocations[0].RemoveAll(), m_nColors[0] = m_nColors[1] = VGA_COLOR_BLACK; !m_pSpyLocations[0].GetSize(); )
	{
		SetSpyLocation();
		break;
	}
	SendDlgItemMessage(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS, LVM_DELETEALLITEMS);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVEALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_DESCRIPTION)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsContentsPage::OnCodingHexadecimal()
{
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->ShowWindow((!FindSpyLocation()) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->EnableWindow((!FindSpyLocation() && CheckSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->ShowWindow((FindSpyLocation()) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow((FindSpyLocation() && CheckSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVE)->EnableWindow((FindSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsContentsPage::OnCodingDecimal()
{
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->ShowWindow((!FindSpyLocation()) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->EnableWindow((!FindSpyLocation() && CheckSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->ShowWindow((FindSpyLocation()) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow((FindSpyLocation() && CheckSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVE)->EnableWindow((FindSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsContentsPage::OnCodingOctal()
{
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->ShowWindow((!FindSpyLocation()) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->EnableWindow((!FindSpyLocation() && CheckSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->ShowWindow((FindSpyLocation()) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow((FindSpyLocation() && CheckSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVE)->EnableWindow((FindSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsContentsPage::OnCodingBinary()
{
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->ShowWindow((!FindSpyLocation()) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->EnableWindow((!FindSpyLocation() && CheckSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->ShowWindow((FindSpyLocation()) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow((FindSpyLocation() && CheckSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVE)->EnableWindow((FindSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsContentsPage::OnEditchangeByte()
{
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->ShowWindow((!FindSpyLocation()) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->EnableWindow((!FindSpyLocation() && CheckSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->ShowWindow((FindSpyLocation()) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow((FindSpyLocation() && CheckSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVE)->EnableWindow((FindSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsContentsPage::OnEditchangeBit()
{
	CString  szBit;
	CStringTools  cStringTools;

	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_POSITION_BIT)->GetWindowText(szBit);
	if (!szBit.IsEmpty() && (_ttoi(szBit) < HEXSETTINGSCONTENTSPAGE_SPYLOCATION_MINIMUMBIT || _ttoi(szBit) > HEXSETTINGSCONTENTSPAGE_SPYLOCATION_MAXIMUMBIT))
	{
		GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_POSITION_BIT)->SetWindowText(cStringTools.ConvertIntToString((_ttoi(szBit) < HEXSETTINGSCONTENTSPAGE_SPYLOCATION_MINIMUMBIT) ? HEXSETTINGSCONTENTSPAGE_SPYLOCATION_MINIMUMBIT : HEXSETTINGSCONTENTSPAGE_SPYLOCATION_MAXIMUMBIT));
		SendDlgItemMessage(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_POSITION_BIT, EM_SETSEL, 0, (LPARAM)-1);
		GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_POSITION_BIT)->SetFocus();
		CAudioDevice::AlertBySound();
	}
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->ShowWindow((!FindSpyLocation()) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->EnableWindow((!FindSpyLocation() && CheckSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->ShowWindow((FindSpyLocation()) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow((FindSpyLocation() && CheckSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVE)->EnableWindow((FindSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsContentsPage::OnEditchangeLength()
{
	CString  szLength;
	CStringTools  cStringTools;

	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_POSITION_LENGTH)->GetWindowText(szLength);
	if (!szLength.IsEmpty() && (_ttoi(szLength) < HEXSETTINGSCONTENTSPAGE_SPYLOCATION_MINIMUMLENGTH || _ttoi(szLength) > HEXSETTINGSCONTENTSPAGE_SPYLOCATION_MAXIMUMLENGTH))
	{
		GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_POSITION_LENGTH)->SetWindowText(cStringTools.ConvertIntToString((_ttoi(szLength) < HEXSETTINGSCONTENTSPAGE_SPYLOCATION_MINIMUMLENGTH) ? HEXSETTINGSCONTENTSPAGE_SPYLOCATION_MINIMUMLENGTH : HEXSETTINGSCONTENTSPAGE_SPYLOCATION_MAXIMUMLENGTH));
		SendDlgItemMessage(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_POSITION_LENGTH, EM_SETSEL, 0, (LPARAM)-1);
		GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_POSITION_LENGTH)->SetFocus();
		CAudioDevice::AlertBySound();
	}
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->ShowWindow((!FindSpyLocation()) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->EnableWindow((!FindSpyLocation() && CheckSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->ShowWindow((FindSpyLocation()) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow((FindSpyLocation() && CheckSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVE)->EnableWindow((FindSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsContentsPage::OnEditchangeDescription()
{
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->ShowWindow((!FindSpyLocation()) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->EnableWindow((!FindSpyLocation() && CheckSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->ShowWindow((FindSpyLocation()) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow((FindSpyLocation() && CheckSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVE)->EnableWindow((FindSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsContentsPage::OnSelchangeColorText()
{
	CString  szColorText;
	CHEXSpyLocation  *pLocation;

	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_COLORTEXT)->GetWindowText(szColorText);
	SendDlgItemMessage(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)((szColorText == STRING(IDS_HEXSETTINGS_CONTENTSPAGE_SPYDETAILSCOLOR)) ? (((pLocation = FindSpyLocation())) ? (m_nColors[0] = pLocation->GetDetailsColor()) : m_nColors[0]) : (((pLocation = FindSpyLocation())) ? (m_nColors[1] = pLocation->GetValueColor()) : m_nColors[1])));
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->ShowWindow((!FindSpyLocation()) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->EnableWindow((!FindSpyLocation() && CheckSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->ShowWindow((FindSpyLocation()) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow((FindSpyLocation() && CheckSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVE)->EnableWindow((FindSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsContentsPage::OnSelchangeColor()
{
	CString  szColorText;

	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_COLORTEXT)->GetWindowText(szColorText);
	m_nColors[0] = (szColorText == STRING(IDS_HEXSETTINGS_CONTENTSPAGE_SPYDETAILSCOLOR)) ? (COLORREF)SendDlgItemMessage(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_COLOR, CB_GETCURSEL)) : m_nColors[0];
	m_nColors[1] = (szColorText == STRING(IDS_HEXSETTINGS_CONTENTSPAGE_SPYVALUECOLOR)) ? (COLORREF)SendDlgItemMessage(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_HEXSETTINGS_CONTENTSPAGE_PROPERTIES_COLOR, CB_GETCURSEL)) : m_nColors[1];
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->ShowWindow((!FindSpyLocation()) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_ADD)->EnableWindow((!FindSpyLocation() && CheckSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->ShowWindow((FindSpyLocation()) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_MODIFY)->EnableWindow((FindSpyLocation() && CheckSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVE)->EnableWindow((FindSpyLocation()) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_CONTENTSPAGE_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_CONTENTSPAGE_SPYLOCATIONS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CHEXSettingsRetrievingPage property page

IMPLEMENT_DYNCREATE(CHEXSettingsRetrievingPage, CLocalePropertyPage)

CHEXSettingsRetrievingPage::CHEXSettingsRetrievingPage() : CLocalePropertyPage(CHEXSettingsRetrievingPage::IDD)
{
	//{{AFX_DATA_INIT(CHEXSettingsRetrievingPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CHEXSettingsRetrievingPage::Initialize()
{
	CHEXOpenDialog  *pDialog;

	if (((pDialog = GetParentDialog()->GetParentDialog()) && pDialog->GetRetrieveFileName(m_szFileName[0])) || GetParentDisplay()->GetRetrieveFileName(m_szFileName[0]))
	{
		m_szFileName[1] = m_szFileName[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXSettingsRetrievingPage::GetDataSourceFileName(CString &szFileName) CONST
{
	szFileName = m_szFileName[0];
	return Check(FALSE);
}

CHEXSettingsDialog *CHEXSettingsRetrievingPage::GetParentDialog() CONST
{
	return((CHEXSettingsDialog *)CLocalePropertyPage::GetParent());
}

CHEXWnd *CHEXSettingsRetrievingPage::GetParentDisplay() CONST
{
	return((CHEXWnd *)GetParentDialog()->GetParentDisplay());
}

VOID CHEXSettingsRetrievingPage::EnumDataSources()
{
	INT  nFile;
	INT  nFiles;
	CHistoryStoreFile  cFile;
	CHistoryStoreFiles  pFiles;
	CUIntArray  nOptions;

	for (nFile = 0, nFiles = GetTMService()->GetTMHistoryFiles(HISTORYFILE_TYPE_RETRIEVE, pFiles), GetTMService()->GetDefaultTMHistoryFile(HISTORYFILE_TYPE_RETRIEVE, cFile), m_szFileName[0] = (pFiles.Find(m_szFileName[0]) < 0) ? cFile.GetFileName() : m_szFileName[0]; nFile < nFiles || (!nFiles && !nFile && !m_szFileName[0].IsEmpty()); nFile++)
	{
		SendDlgItemMessage(IDC_HEXSETTINGS_RETRIEVINGPAGE_DATASOURCE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)((nFiles > 0) ? (LPCTSTR)pFiles.GetAt(nFile)->GetFileName() : (LPCTSTR)m_szFileName[0]));
		continue;
	}
	SendDlgItemMessage(IDC_HEXSETTINGS_RETRIEVINGPAGE_DATASOURCE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_HEXSETTINGS_RETRIEVINGPAGE_DATASOURCE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)m_szFileName[0]), 0));
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_DATASOURCE)->GetWindowText(m_szFileName[0]);
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_DATASOURCE)->GetWindowText(m_szFileName[1]);
	ShowDataSourceInfo();
}

VOID CHEXSettingsRetrievingPage::ShowDataSourceInfo()
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
		GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT)->SetWindowText(szProduct);
		GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY)->SetWindowText(szCompany);
		GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT)->SetWindowText(szSpacecraft);
		GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE)->SetWindowText(szDataSourceType);
		GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->SetWindowText(szStartTime);
		GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->SetWindowText(szStopTime);
		GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->SetWindowText(szCreationTime);
		GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE)->SetWindowText(szDataSourceSize);
	}
	else
	{
		GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT)->SetWindowText((szProduct = EMPTYSTRING));
		GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY)->SetWindowText((szCompany = EMPTYSTRING));
		GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT)->SetWindowText((szSpacecraft = EMPTYSTRING));
		GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE)->SetWindowText((szDataSourceType = EMPTYSTRING));
		GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->SetWindowText((szStartTime = EMPTYSTRING));
		GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->SetWindowText((szStopTime = EMPTYSTRING));
		GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->SetWindowText((szCreationTime = EMPTYSTRING));
		GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE)->SetWindowText((szDataSourceSize = EMPTYSTRING));
	}
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO)->EnableWindow();
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMMENTS)->EnableWindow(szProduct.IsEmpty());
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMMENTS)->ShowWindow((szProduct.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT_STATIC)->ShowWindow((!szProduct.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT_STATIC)->EnableWindow(!szProduct.IsEmpty());
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT)->ShowWindow((!szProduct.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT)->EnableWindow(!szProduct.IsEmpty());
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY_STATIC)->ShowWindow((!szCompany.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY_STATIC)->EnableWindow(!szCompany.IsEmpty());
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY)->ShowWindow((!szCompany.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY)->EnableWindow(!szCompany.IsEmpty());
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT_STATIC)->ShowWindow((!szSpacecraft.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT_STATIC)->EnableWindow(!szSpacecraft.IsEmpty());
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT)->ShowWindow((!szSpacecraft.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT)->EnableWindow(!szSpacecraft.IsEmpty());
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE_STATIC)->ShowWindow((!szDataSourceType.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE_STATIC)->EnableWindow(!szDataSourceType.IsEmpty());
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE)->ShowWindow((!szDataSourceType.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE)->EnableWindow(!szDataSourceType.IsEmpty());
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STATIC)->ShowWindow((GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STATIC)->EnableWindow((GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->ShowWindow((GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->EnableWindow((GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_TO)->ShowWindow((GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_TO)->EnableWindow((GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->ShowWindow((GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->EnableWindow((GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME_STATIC)->ShowWindow((GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME_STATIC)->EnableWindow((GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->ShowWindow((GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->EnableWindow((GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE_STATIC)->ShowWindow((!szDataSourceSize.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE_STATIC)->EnableWindow(!szDataSourceSize.IsEmpty());
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE)->ShowWindow((!szDataSourceSize.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE)->EnableWindow(!szDataSourceSize.IsEmpty());
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_INSPECT)->EnableWindow(!m_szFileName[0].IsEmpty());
}

BOOL CHEXSettingsRetrievingPage::CheckDataSource(LPCTSTR pszFileName) CONST
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
BOOL CHEXSettingsRetrievingPage::CheckDataSource(LPCTSTR pszFileName, CString &szProduct, CString &szCompany, CString &szTrademark, CString &szSpacecraft, CString &szDataSourceType, CString &szStartTime, CString &szStopTime, CString &szCreationTime, CString &szDataSourceSize) CONST
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
			for (cHistoryFile.GetCopyrightProduct(szProduct), cHistoryFile.GetCopyrightCompany(szCompany), cHistoryFile.GetCopyrightTrademark(szTrademark), cHistoryFile.GetSpacecraft(szSpacecraft), cHistoryFile.GetType(szDataSourceType), szStartTime = (cHistoryFile.CLogFile::SeekToFirst() && cHistoryFile.CLogFile::Read(tTime, nData)) ? (LPCTSTR)tTime.FormatGmt(STRING(IDS_HEXSETTINGS_RETRIEVINGPAGE_SOURCEDATATIMEFORMAT)) : EMPTYSTRING, szStopTime = (cHistoryFile.CLogFile::SeekToLast() && cHistoryFile.CLogFile::Read(tTime, nData)) ? (LPCTSTR)tTime.FormatGmt(STRING(IDS_HEXSETTINGS_RETRIEVINGPAGE_SOURCEDATATIMEFORMAT)) : EMPTYSTRING, szCreationTime = (cHistoryFile.GetCopyrightCreationTime(tTime)) ? (LPCTSTR)tTime.FormatGmt(STRING(IDS_HEXSETTINGS_RETRIEVINGPAGE_SOURCEDATAFILETIMEFORMAT)) : EMPTYSTRING, szDataSourceSize.Format(STRING(IDS_HEXSETTINGS_RETRIEVINGPAGE_SOURCEDATASIZEFORMAT), ((dwSize = cHistoryFile.CLogFile::GetSize()) + 512) / 1024), szDataSourceSize = FormatDataSourceSize(szDataSourceSize); !szProduct.IsEmpty() && !szCompany.IsEmpty() && !szTrademark.IsEmpty(); )
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

CString CHEXSettingsRetrievingPage::FormatDataSourceSize(LPCTSTR pszDataSourceSize) CONST
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

BOOL CHEXSettingsRetrievingPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? ((m_szFileName[0].CompareNoCase(m_szFileName[1])) ? TRUE : FALSE) : CLocalePropertyPage::IsModified()) : FALSE);
}

BOOL CHEXSettingsRetrievingPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (m_szFileName[0].IsEmpty() || CheckDataSource(m_szFileName[0])) : CLocalePropertyPage::Check()) : TRUE);
}

void CHEXSettingsRetrievingPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHEXSettingsRetrievingPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHEXSettingsRetrievingPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CHEXSettingsRetrievingPage)
	ON_BN_CLICKED(IDC_HEXSETTINGS_RETRIEVINGPAGE_INSPECT, OnInspect)
	ON_CBN_EDITCHANGE(IDC_HEXSETTINGS_RETRIEVINGPAGE_DATASOURCE, OnEditchangeFileName)
	ON_CBN_SELCHANGE(IDC_HEXSETTINGS_RETRIEVINGPAGE_DATASOURCE, OnSelchangeFileName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHEXSettingsRetrievingPage message handlers

BOOL CHEXSettingsRetrievingPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_DATASOURCE_STATIC)->EnableWindow();
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_DATASOURCE)->EnableWindow();
	EnumDataSources();
	return TRUE;
}

BOOL CHEXSettingsRetrievingPage::OnSetActive()
{
	ShowDataSourceInfo();
	return CLocalePropertyPage::OnSetActive();
}

void CHEXSettingsRetrievingPage::OnInspect()
{
	CHourglassCursor  cCursor;

	ShowDataSourceInfo();
}

void CHEXSettingsRetrievingPage::OnEditchangeFileName()
{
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_DATASOURCE)->GetWindowText(m_szFileName[0]);
	GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_INSPECT)->EnableWindow(!m_szFileName[0].IsEmpty());
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsRetrievingPage::OnSelchangeFileName()
{
	for (m_szFileName[0] = Combobox_GetText(GetDlgItem(IDC_HEXSETTINGS_RETRIEVINGPAGE_DATASOURCE), (INT)SendDlgItemMessage(IDC_HEXSETTINGS_RETRIEVINGPAGE_DATASOURCE, CB_GETCURSEL)); !m_szFileName[0].IsEmpty(); )
	{
		ShowDataSourceInfo();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CHEXSettingsPrintingComments

IMPLEMENT_DYNCREATE(CHEXSettingsPrintingComments, CEdit)

BEGIN_MESSAGE_MAP(CHEXSettingsPrintingComments, CEdit)
	//{{AFX_MSG_MAP(CHEXSettingsPrintingComments)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHEXSettingsPrintingComments message handlers

void CHEXSettingsPrintingComments::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
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
// CHEXSettingsPrintingPage property page

IMPLEMENT_DYNCREATE(CHEXSettingsPrintingPage, CLocalePropertyPage)

CHEXSettingsPrintingPage::CHEXSettingsPrintingPage() : CLocalePropertyPage(CHEXSettingsPrintingPage::IDD)
{
	//{{AFX_DATA_INIT(CHEXSettingsPrintingPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CHEXSettingsPrintingPage::Initialize()
{
	CHEXOpenDialog  *pDialog;

	return((((pDialog = GetParentDialog()->GetParentDialog()) && pDialog->GetPrintJobs(m_pJobs[0])) || GetParentDisplay()->GetPrintJobs(m_pJobs[0])) ? m_pJobs[1].Copy(&m_pJobs[0]) : FALSE);
}

BOOL CHEXSettingsPrintingPage::GetJobs(CHEXPrintJobs &pJobs) CONST
{
	return((pJobs.Copy(&m_pJobs[0])) ? Check(FALSE) : FALSE);
}

CHEXSettingsDialog *CHEXSettingsPrintingPage::GetParentDialog() CONST
{
	return((CHEXSettingsDialog *)CLocalePropertyPage::GetParent());
}

CHEXWnd *CHEXSettingsPrintingPage::GetParentDisplay() CONST
{
	return((CHEXWnd *)GetParentDialog()->GetParentDisplay());
}

VOID CHEXSettingsPrintingPage::ShowJobInfo()
{
	UINT  nMode;
	UINT  nCount[2];
	CUIntArray  nColumns;
	CHEXPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		m_nPrintOptions[0] = ((((nMode = pJobInfo->GetPrintMode()) & HEX_PRINT_FIRSTDATASIDE) || (nMode & HEX_PRINT_LASTDATASIDE)) && pJobInfo->GetPrintBySide(nCount[0], nCount[1])) ? ((nMode & HEX_PRINT_FIRSTDATASIDE) ? nCount[0] : -(INT)nCount[0]) : 0;
		m_nPrintOptions[1] = (((nMode & HEX_PRINT_FIRSTSPYLOCATIONSSIDE) || (nMode & HEX_PRINT_LASTSPYLOCATIONSSIDE)) && pJobInfo->GetPrintBySide(nCount[0], nCount[1])) ? ((nMode & HEX_PRINT_FIRSTSPYLOCATIONSSIDE) ? nCount[1] : -(INT)nCount[1]) : 0;
		SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CHOICE, (SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CHOICE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_HEXSETTINGS_PRINTINGPAGE_SPYLOCATIONS)) < 0) ? ((nMode & HEX_PRINT_SPYLOCATIONS) ? CB_INSERTSTRING : CB_DELETESTRING) : CB_DELETESTRING, (WPARAM)((SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CHOICE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_HEXSETTINGS_PRINTINGPAGE_SPYLOCATIONS)) >= 0) ? ((!(nMode & HEX_PRINT_SPYLOCATIONS)) ? SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CHOICE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_HEXSETTINGS_PRINTINGPAGE_SPYLOCATIONS)) : -1) : -1), (LPARAM)STRING(IDS_HEXSETTINGS_PRINTINGPAGE_SPYLOCATIONS));
		SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CHOICE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CHOICE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_HEXSETTINGS_PRINTINGPAGE_TELEMETRYDATA)));
		SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetProfile()));
		SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_SELECTTEXT, (WPARAM)-1, ((IsTelemetryDataOptions() && (nMode & HEX_PRINT_FIRSTDATASIDE)) || (IsSpyLocationsOptions() && (nMode & HEX_PRINT_FIRSTSPYLOCATIONSSIDE))) ? (LPARAM)STRING(IDS_HEXSETTINGS_PRINTINGPAGE_FIRSTSIDE) : (((IsTelemetryDataOptions() && (nMode & HEX_PRINT_LASTDATASIDE)) || (IsSpyLocationsOptions() && (nMode & HEX_PRINT_LASTSPYLOCATIONSSIDE))) ? (LPARAM)STRING(IDS_HEXSETTINGS_PRINTINGPAGE_LASTSIDE) : (LPARAM)EMPTYSTRING));
		Spinbox_SetPos(GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT), (pJobInfo->GetPrintBySide(nCount[0], nCount[1])) ? ((IsTelemetryDataOptions()) ? nCount[0] : nCount[1]) : 0);
		CheckDlgButton(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL, ((IsTelemetryDataOptions() && (nMode & HEX_PRINT_ALLDATA)) || (IsSpyLocationsOptions() && (nMode & HEX_PRINT_ALLSPYLOCATIONS))) ? TRUE : FALSE);
		CheckDlgButton(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE, ((IsTelemetryDataOptions() && ((nMode & HEX_PRINT_FIRSTDATASIDE) || (nMode & HEX_PRINT_LASTDATASIDE))) || (IsSpyLocationsOptions() && ((nMode & HEX_PRINT_FIRSTSPYLOCATIONSSIDE) || (nMode & HEX_PRINT_LASTSPYLOCATIONSSIDE)))) ? TRUE : FALSE);
		CheckDlgButton(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_SPYLOCATIONS, (nMode & HEX_PRINT_SPYLOCATIONS) ? TRUE : FALSE);
		CheckDlgButton(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS, (nMode & HEX_PRINT_CLEARCOMMENTS) ? TRUE : FALSE);
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->SetWindowText(pJobInfo->GetComments());
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_ADDNAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_REMOVENAME)->EnableWindow((pJobInfo->GetName() != STRING(IDS_PRINTJOB_DEFAULTNAME)) ? TRUE : FALSE);
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_REMOVEALLNAMES)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_NAME, CB_GETCOUNT) > 1) ? TRUE : FALSE);
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES)->EnableWindow();
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE_STATIC)->EnableWindow();
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE)->EnableWindow();
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_OPTIONS)->EnableWindow();
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CHOICE_STATIC)->EnableWindow();
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CHOICE)->EnableWindow();
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL)->EnableWindow();
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE)->EnableWindow();
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE));
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE));
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE));
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_SPYLOCATIONS)->EnableWindow();
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTS)->EnableWindow();
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT_STATIC)->EnableWindow();
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->EnableWindow();
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)->EnableWindow(!pJobInfo->GetComments().IsEmpty());
		return;
	}
	m_nPrintOptions[0] = 0;
	m_nPrintOptions[1] = 0;
	SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)-1);
	SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_SETCURSEL, (WPARAM)-1);
	SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CHOICE, CB_SETCURSEL, (WPARAM)-1);
	SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_SELECTTEXT, (WPARAM)-1, (LPARAM)EMPTYSTRING);
	CheckDlgButton(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL, FALSE);
	CheckDlgButton(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE, FALSE);
	CheckDlgButton(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_SPYLOCATIONS, FALSE);
	CheckDlgButton(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS, FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_ADDNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_REMOVENAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_REMOVEALLNAMES)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_OPTIONS)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CHOICE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CHOICE)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_SPYLOCATIONS)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTS)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)->EnableWindow(FALSE);
}

CHEXPrintJobInfo *CHEXSettingsPrintingPage::FindJobInfo() CONST
{
	CString  szJobName;

	GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_NAME)->GetWindowText(szJobName);
	return m_pJobs[0].GetAt(m_pJobs[0].Find(szJobName));
}

BOOL CHEXSettingsPrintingPage::IsTelemetryDataOptions() CONST
{
	CString  szChoice;

	GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CHOICE)->GetWindowText(szChoice);
	return((szChoice == STRING(IDS_HEXSETTINGS_PRINTINGPAGE_TELEMETRYDATA)) ? TRUE : FALSE);
}

BOOL CHEXSettingsPrintingPage::IsSpyLocationsOptions() CONST
{
	CString  szChoice;

	GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CHOICE)->GetWindowText(szChoice);
	return((szChoice == STRING(IDS_HEXSETTINGS_PRINTINGPAGE_SPYLOCATIONS)) ? TRUE : FALSE);
}

BOOL CHEXSettingsPrintingPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? !m_pJobs[0].Compare(&m_pJobs[1]) : CLocalePropertyPage::IsModified()) : FALSE);
}

BOOL CHEXSettingsPrintingPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? ((GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_NAME)->GetWindowTextLength() > 0 && FindJobInfo()) ? TRUE : FALSE) : CLocalePropertyPage::Check()) : TRUE);
}

void CHEXSettingsPrintingPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHEXSettingsPrintingPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CHEXSettingsPrintingPage::PostNcDestroy()
{
	m_pJobs[0].RemoveAll();
	m_pJobs[1].RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CHEXSettingsPrintingPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CHEXSettingsPrintingPage)
	ON_BN_CLICKED(IDC_HEXSETTINGS_PRINTINGPAGE_ADDNAME, OnAddName)
	ON_BN_CLICKED(IDC_HEXSETTINGS_PRINTINGPAGE_REMOVENAME, OnRemoveName)
	ON_BN_CLICKED(IDC_HEXSETTINGS_PRINTINGPAGE_REMOVEALLNAMES, OnRemoveAllNames)
	ON_BN_CLICKED(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL, OnPrintAll)
	ON_BN_CLICKED(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE, OnPrintBySide)
	ON_BN_CLICKED(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_SPYLOCATIONS, OnPrintSpyLocations)
	ON_BN_CLICKED(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS, OnResetComments)
	ON_CBN_EDITCHANGE(IDC_HEXSETTINGS_PRINTINGPAGE_NAME, OnEditchangeName)
	ON_CBN_SELCHANGE(IDC_HEXSETTINGS_PRINTINGPAGE_NAME, OnSelchangeName)
	ON_CBN_SELCHANGE(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, OnSelchangeProfile)
	ON_CBN_SELCHANGE(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CHOICE, OnSelchangeChoice)
	ON_EN_CHANGE(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, OnChangePrintSide)
	ON_EN_CHANGE(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT, OnEditchangeComments)
	ON_CONTROL(SBXN_CHANGE, IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT, OnSpinchangePrintSideCount)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHEXSettingsPrintingPage message handlers

BOOL CHEXSettingsPrintingPage::OnInitDialog()
{
	INT  nJob;
	INT  nJobs;
	INT  nProfile;
	INT  nProfiles;
	CStringArray  szProfiles;
	CHEXPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	for (CLocalePropertyPage::OnInitDialog(), SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CHOICE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_HEXSETTINGS_PRINTINGPAGE_TELEMETRYDATA)); m_wndComments.SubclassWindow(GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->GetSafeHwnd()); )
	{
		for (nJob = 0, nJobs = (INT)m_pJobs[0].GetSize(); nJob < nJobs; nJob++)
		{
			if ((pJobInfo = m_pJobs[0].GetAt(nJob)) != (CHEXPrintJobInfo *)NULL)
			{
				SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_NAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pJobInfo->GetName());
				continue;
			}
		}
		for (nProfile = 0, nProfiles = (EnumPrintProfiles(szProfiles)) ? (INT)szProfiles.GetSize() : 0; nProfile < nProfiles; nProfile++)
		{
			SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szProfiles.GetAt(nProfile));
			continue;
		}
		Spinbox_SetRange(GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT), HEXSETTINGSPRINTINGPAGE_OPTIONS_MINIMUMLINES, HEXSETTINGSPRINTINGPAGE_OPTIONS_MAXIMUMLINES);
		SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_PRINTJOB_DEFAULTNAME)));
		SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CHOICE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CHOICE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_HEXSETTINGS_PRINTINGPAGE_TELEMETRYDATA)));
		SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_ADDTEXT, (WPARAM)NULL, (LPARAM)STRING(IDS_HEXSETTINGS_PRINTINGPAGE_FIRSTSIDE));
		SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_ADDTEXT, (WPARAM)NULL, (LPARAM)STRING(IDS_HEXSETTINGS_PRINTINGPAGE_LASTSIDE));
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_DETAILS)->EnableWindow();
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_NAME_STATIC)->EnableWindow();
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_NAME)->EnableWindow();
		ShowJobInfo();
		break;
	}
	return TRUE;
}

BOOL CHEXSettingsPrintingPage::OnSetActive()
{
	ShowJobInfo();
	return CLocalePropertyPage::OnSetActive();
}

BOOL CHEXSettingsPrintingPage::OnKillActive()
{
	GetParentDialog()->OnDataExchange(GetSafeHwnd(), m_pJobs[0]);
	return CLocalePropertyPage::OnKillActive();
}

BOOL CHEXSettingsPrintingPage::OnDataExchange(CONST CHEXPrintJobs &pJobs)
{
	return m_pJobs[0].Copy(&pJobs);
}

void CHEXSettingsPrintingPage::OnEditchangeName()
{
	CString  szJobName;
	CHEXPrintJobInfo  *pJobInfo;

	for (GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_NAME)->GetWindowText(szJobName); (pJobInfo = FindJobInfo()); )
	{
		ShowJobInfo();
		return;
	}
	GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_ADDNAME)->EnableWindow((!pJobInfo  &&  szJobName.GetLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_REMOVENAME)->EnableWindow((pJobInfo != (CHEXPrintJobInfo *)NULL  &&  szJobName != STRING(IDS_PRINTJOB_DEFAULTNAME)) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_REMOVEALLNAMES)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_NAME, CB_GETCOUNT) > 1) ? TRUE : FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)->EnableWindow((szJobName != STRING(IDS_PRINTJOB_DEFAULTNAME)) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsPrintingPage::OnSelchangeName()
{
	SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_NAME, CB_GETCURSEL));
	ShowJobInfo();
}

void CHEXSettingsPrintingPage::OnAddName()
{
	INT  nIndex;
	UINT  nMode;
	CString  szJobName;
	CString  szProfile;
	CString  szComments;
	CHEXPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	for (; (pJobInfo = new CHEXPrintJobInfo); )
	{
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_NAME)->GetWindowText(szJobName);
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE)->GetWindowText(szProfile);
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->GetWindowText(szComments);
		nMode = (!m_nPrintOptions[0]) ? ((pJobInfo->GetPrintMode() & ~(HEX_PRINT_FIRSTDATASIDE | HEX_PRINT_LASTDATASIDE)) | HEX_PRINT_ALLDATA) : ((m_nPrintOptions[0] > 0) ? ((pJobInfo->GetPrintMode() & ~(HEX_PRINT_ALLDATA | HEX_PRINT_LASTDATASIDE)) | HEX_PRINT_FIRSTDATASIDE) : ((pJobInfo->GetPrintMode() & ~(HEX_PRINT_ALLDATA | HEX_PRINT_FIRSTDATASIDE)) | HEX_PRINT_LASTDATASIDE));
		nMode = (IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_SPYLOCATIONS)) ? ((!m_nPrintOptions[1]) ? ((nMode & ~(HEX_PRINT_FIRSTSPYLOCATIONSSIDE | HEX_PRINT_LASTSPYLOCATIONSSIDE)) | HEX_PRINT_SPYLOCATIONS | HEX_PRINT_ALLSPYLOCATIONS) : ((m_nPrintOptions[1] > 0) ? ((nMode & ~(HEX_PRINT_ALLSPYLOCATIONS | HEX_PRINT_LASTSPYLOCATIONSSIDE)) | HEX_PRINT_SPYLOCATIONS | HEX_PRINT_FIRSTSPYLOCATIONSSIDE) : ((nMode & ~(HEX_PRINT_ALLSPYLOCATIONS | HEX_PRINT_FIRSTSPYLOCATIONSSIDE)) | HEX_PRINT_SPYLOCATIONS | HEX_PRINT_LASTSPYLOCATIONSSIDE))) : (nMode & ~(HEX_PRINT_SPYLOCATIONS | HEX_PRINT_FIRSTSPYLOCATIONSSIDE | HEX_PRINT_LASTSPYLOCATIONSSIDE));
		nMode = (IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)) ? (nMode | HEX_PRINT_CLEARCOMMENTS) : (nMode & ~HEX_PRINT_CLEARCOMMENTS);
		if (SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_NAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szJobName) >= 0 && SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szJobName)) >= 0)
		{
			for (pJobInfo->SetName(szJobName), pJobInfo->SetProfile(szProfile), pJobInfo->SetComments(szComments), pJobInfo->SetPrintMode(nMode), pJobInfo->SetPrintBySide(abs(m_nPrintOptions[0]), abs(m_nPrintOptions[1])); (nIndex = m_pJobs[0].Add(pJobInfo)) >= 0; )
			{
				ShowJobInfo();
				break;
			}
			if (nIndex >= 0) break;
		}
		delete pJobInfo;
		break;
	}
	GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsPrintingPage::OnRemoveName()
{
	INT  nJob;
	INT  nJobs;
	CHEXPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	for (nJob = 0, nJobs = (INT)m_pJobs[0].GetSize(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = m_pJobs[0].GetAt(nJob)) && pJobInfo == FindJobInfo())
		{
			if (SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_NAME, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName())) > 0)
			{
				m_pJobs[0].RemoveAt(nJob);
				delete pJobInfo;
			}
			break;
		}
	}
	for (; SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_PRINTJOB_DEFAULTNAME))) >= 0; )
	{
		ShowJobInfo();
		break;
	}
	GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsPrintingPage::OnRemoveAllNames()
{
	INT  nJob;
	INT  nJobs;
	CHEXPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	for (nJob = 0, nJobs = (INT)m_pJobs[0].GetSize(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = m_pJobs[0].GetAt(nJob)) && pJobInfo->GetName() != STRING(IDS_PRINTJOB_DEFAULTNAME) && SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_NAME, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName())) > 0)
		{
			m_pJobs[0].RemoveAt(nJob);
			delete pJobInfo;
			nJobs--;
			nJob--;
		}
	}
	for (; SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_PRINTJOB_DEFAULTNAME))) >= 0; )
	{
		ShowJobInfo();
		break;
	}
	GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsPrintingPage::OnSelchangeProfile()
{
	CString  szProfile;
	CHEXPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE)->GetWindowText(szProfile);
		pJobInfo->SetProfile(szProfile);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsPrintingPage::OnSelchangeChoice()
{
	UINT  nCount[2];
	CHEXPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		pJobInfo->GetPrintBySide(nCount[0], nCount[1]);
		CheckDlgButton(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL, ((IsTelemetryDataOptions() && (pJobInfo->GetPrintMode() & HEX_PRINT_ALLDATA)) || (IsSpyLocationsOptions() && (pJobInfo->GetPrintMode() & HEX_PRINT_ALLSPYLOCATIONS))) ? TRUE : FALSE);
		CheckDlgButton(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE, ((IsTelemetryDataOptions() && ((pJobInfo->GetPrintMode() & HEX_PRINT_FIRSTDATASIDE) || (pJobInfo->GetPrintMode() & HEX_PRINT_LASTDATASIDE))) || (IsSpyLocationsOptions() && ((pJobInfo->GetPrintMode() & HEX_PRINT_FIRSTSPYLOCATIONSSIDE) || (pJobInfo->GetPrintMode() & HEX_PRINT_LASTSPYLOCATIONSSIDE)))) ? TRUE : FALSE);
		SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_SELECTTEXT, (WPARAM)-1, ((IsTelemetryDataOptions() && (pJobInfo->GetPrintMode() & HEX_PRINT_FIRSTDATASIDE)) || (IsSpyLocationsOptions() && (pJobInfo->GetPrintMode() & HEX_PRINT_FIRSTSPYLOCATIONSSIDE))) ? (LPARAM)STRING(IDS_HEXSETTINGS_PRINTINGPAGE_FIRSTSIDE) : (((IsTelemetryDataOptions() && (pJobInfo->GetPrintMode() & HEX_PRINT_LASTDATASIDE)) || (IsSpyLocationsOptions() && (pJobInfo->GetPrintMode() & HEX_PRINT_LASTSPYLOCATIONSSIDE))) ? (LPARAM)STRING(IDS_HEXSETTINGS_PRINTINGPAGE_LASTSIDE) : (LPARAM)EMPTYSTRING));
		Spinbox_SetPos(GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT), (IsTelemetryDataOptions()) ? nCount[0] : nCount[1]);
	}
	else
	{
		CheckDlgButton(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL, ((IsTelemetryDataOptions() && !m_nPrintOptions[0]) || (IsSpyLocationsOptions() && !m_nPrintOptions[1])) ? TRUE : FALSE);
		CheckDlgButton(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE, ((IsTelemetryDataOptions() && m_nPrintOptions[0]) || (IsSpyLocationsOptions() && m_nPrintOptions[1])) ? TRUE : FALSE);
		SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_SELECTTEXT, (WPARAM)-1, ((IsTelemetryDataOptions() && m_nPrintOptions[0] > 0) || (IsSpyLocationsOptions() && m_nPrintOptions[1] > 0)) ? (LPARAM)STRING(IDS_HEXSETTINGS_PRINTINGPAGE_FIRSTSIDE) : (((IsTelemetryDataOptions() && m_nPrintOptions[0] < 0) || (IsSpyLocationsOptions() && m_nPrintOptions[1] < 0)) ? (LPARAM)STRING(IDS_HEXSETTINGS_PRINTINGPAGE_LASTSIDE) : (LPARAM)EMPTYSTRING));
		Spinbox_SetPos(GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT), (IsTelemetryDataOptions()) ? abs(m_nPrintOptions[0]) : abs(m_nPrintOptions[1]));
	}
	GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE));
	GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE));
	GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE));
}

void CHEXSettingsPrintingPage::OnPrintAll()
{
	CHEXPrintJobInfo  *pJobInfo;

	if (!IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL))
	{
		for (CheckDlgButton(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL, TRUE), CheckDlgButton(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE, FALSE), SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_SELECTTEXT, (WPARAM)-1, (LPARAM)EMPTYSTRING), m_nPrintOptions[0] = (!IsTelemetryDataOptions()) ? m_nPrintOptions[0] : 0, m_nPrintOptions[1] = (!IsSpyLocationsOptions()) ? m_nPrintOptions[1] : 0; (pJobInfo = FindJobInfo()); )
		{
			pJobInfo->SetPrintMode((IsTelemetryDataOptions()) ? ((pJobInfo->GetPrintMode() | HEX_PRINT_ALLDATA) & ~(HEX_PRINT_FIRSTDATASIDE | HEX_PRINT_LASTDATASIDE)) : ((pJobInfo->GetPrintMode() | HEX_PRINT_ALLSPYLOCATIONS) & ~(HEX_PRINT_FIRSTSPYLOCATIONSSIDE | HEX_PRINT_LASTSPYLOCATIONSSIDE)));
			break;
		}
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_ADDNAME)->EnableWindow((GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_NAME)->GetWindowTextLength() > 0 && SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_GETCURSEL) != CB_ERR  &&  !pJobInfo) ? TRUE : FALSE);
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE)->EnableWindow(FALSE);
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)->EnableWindow(FALSE);
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE_STATIC)->EnableWindow(FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsPrintingPage::OnPrintBySide()
{
	UINT  nCount[2];
	CHEXPrintJobInfo  *pJobInfo;

	if (!IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE))
	{
		for (CheckDlgButton(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL, FALSE), CheckDlgButton(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE, TRUE), SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_SELECTTEXT, (WPARAM)-1, (LPARAM)STRING(IDS_HEXSETTINGS_PRINTINGPAGE_FIRSTSIDE)), Spinbox_SetPos(GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT), HEXSETTINGSPRINTINGPAGE_OPTIONS_DEFAULTLINES), m_nPrintOptions[0] = (IsTelemetryDataOptions()) ? HEXSETTINGSPRINTINGPAGE_OPTIONS_DEFAULTLINES : m_nPrintOptions[0], m_nPrintOptions[1] = (IsSpyLocationsOptions()) ? HEXSETTINGSPRINTINGPAGE_OPTIONS_DEFAULTLINES : m_nPrintOptions[1]; (pJobInfo = FindJobInfo()) && pJobInfo->GetPrintBySide(nCount[0], nCount[1]) >= 0; )
		{
			pJobInfo->SetPrintMode((IsTelemetryDataOptions()) ? ((pJobInfo->GetPrintMode() | HEX_PRINT_FIRSTDATASIDE) & ~(HEX_PRINT_ALLDATA | HEX_PRINT_LASTDATASIDE)) : ((pJobInfo->GetPrintMode() | HEX_PRINT_FIRSTSPYLOCATIONSSIDE) & ~(HEX_PRINT_ALLSPYLOCATIONS | HEX_PRINT_LASTSPYLOCATIONSSIDE)));
			pJobInfo->SetPrintBySide((IsTelemetryDataOptions()) ? HEXSETTINGSPRINTINGPAGE_OPTIONS_DEFAULTLINES : nCount[0], (IsSpyLocationsOptions()) ? HEXSETTINGSPRINTINGPAGE_OPTIONS_DEFAULTLINES : nCount[1]);
			break;
		}
		SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, EM_SETSEL, 0, (LPARAM)-1);
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_ADDNAME)->EnableWindow((GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_NAME)->GetWindowTextLength() > 0 && SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_GETCURSEL) != CB_ERR  &&  !pJobInfo) ? TRUE : FALSE);
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE)->EnableWindow();
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)->EnableWindow();
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE_STATIC)->EnableWindow();
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE)->SetFocus();
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsPrintingPage::OnPrintSpyLocations()
{
	UINT  nMode;
	UINT  nCount[2];
	CHEXPrintJobInfo  *pJobInfo;

	for (SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CHOICE, (SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CHOICE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_HEXSETTINGS_PRINTINGPAGE_SPYLOCATIONS)) < 0) ? ((IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_SPYLOCATIONS)) ? CB_INSERTSTRING : CB_DELETESTRING) : CB_DELETESTRING, (WPARAM)((SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CHOICE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_HEXSETTINGS_PRINTINGPAGE_SPYLOCATIONS)) >= 0) ? ((!IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_SPYLOCATIONS)) ? SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CHOICE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_HEXSETTINGS_PRINTINGPAGE_SPYLOCATIONS)) : -1) : -1), (LPARAM)STRING(IDS_HEXSETTINGS_PRINTINGPAGE_SPYLOCATIONS)), SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CHOICE, CB_SETCURSEL, (WPARAM)((SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CHOICE, CB_GETCURSEL) < 0) ? SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CHOICE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_HEXSETTINGS_PRINTINGPAGE_TELEMETRYDATA)) : SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CHOICE, CB_GETCURSEL))); (pJobInfo = FindJobInfo()) && pJobInfo->GetPrintBySide(nCount[0], nCount[1]) >= 0; )
	{
		pJobInfo->SetPrintMode((nMode = (IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_SPYLOCATIONS)) ? (pJobInfo->GetPrintMode() | HEX_PRINT_SPYLOCATIONS | HEX_PRINT_ALLSPYLOCATIONS) : (pJobInfo->GetPrintMode() & ~(HEX_PRINT_SPYLOCATIONS | HEX_PRINT_ALLSPYLOCATIONS | HEX_PRINT_FIRSTSPYLOCATIONSSIDE | HEX_PRINT_LASTSPYLOCATIONSSIDE))));
		CheckDlgButton(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL, ((IsTelemetryDataOptions() && (nMode & HEX_PRINT_ALLDATA)) || (IsSpyLocationsOptions() && (nMode & HEX_PRINT_ALLSPYLOCATIONS))) ? TRUE : FALSE);
		CheckDlgButton(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE, ((IsTelemetryDataOptions() && ((nMode & HEX_PRINT_FIRSTDATASIDE) || (nMode & HEX_PRINT_LASTDATASIDE))) || (IsSpyLocationsOptions() && ((nMode & HEX_PRINT_FIRSTSPYLOCATIONSSIDE) || (nMode & HEX_PRINT_LASTSPYLOCATIONSSIDE)))) ? TRUE : FALSE);
		CheckDlgButton(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_SPYLOCATIONS, (IsTelemetryDataOptions()) ? IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_SPYLOCATIONS) : TRUE);
		SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_SELECTTEXT, (WPARAM)-1, ((IsTelemetryDataOptions() && (nMode & HEX_PRINT_FIRSTDATASIDE)) || (IsSpyLocationsOptions() && (nMode & HEX_PRINT_FIRSTSPYLOCATIONSSIDE))) ? (LPARAM)STRING(IDS_HEXSETTINGS_PRINTINGPAGE_FIRSTSIDE) : (((IsTelemetryDataOptions() && (nMode & HEX_PRINT_LASTDATASIDE)) || (IsSpyLocationsOptions() && (nMode & HEX_PRINT_LASTSPYLOCATIONSSIDE))) ? (LPARAM)STRING(IDS_HEXSETTINGS_PRINTINGPAGE_LASTSIDE) : (LPARAM)EMPTYSTRING));
		Spinbox_SetPos(GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT), (IsTelemetryDataOptions()) ? nCount[0] : nCount[1]);
		break;
	}
	if (!pJobInfo)
	{
		CheckDlgButton(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL, ((IsTelemetryDataOptions() && !m_nPrintOptions[0]) || (IsSpyLocationsOptions() && !m_nPrintOptions[1])) ? TRUE : FALSE);
		CheckDlgButton(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE, ((IsTelemetryDataOptions() && m_nPrintOptions[0]) || (IsSpyLocationsOptions() && m_nPrintOptions[1])) ? TRUE : FALSE);
		CheckDlgButton(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_SPYLOCATIONS, (IsTelemetryDataOptions()) ? IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_SPYLOCATIONS) : TRUE);
		SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_SELECTTEXT, (WPARAM)-1, ((IsTelemetryDataOptions() && m_nPrintOptions[0] > 0) || (IsSpyLocationsOptions() && m_nPrintOptions[1] > 0)) ? (LPARAM)STRING(IDS_HEXSETTINGS_PRINTINGPAGE_FIRSTSIDE) : (((IsTelemetryDataOptions() && m_nPrintOptions[0] < 0) || (IsSpyLocationsOptions() && m_nPrintOptions[1] < 0)) ? (LPARAM)STRING(IDS_HEXSETTINGS_PRINTINGPAGE_LASTSIDE) : (LPARAM)EMPTYSTRING));
		Spinbox_SetPos(GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT), (IsTelemetryDataOptions()) ? abs(m_nPrintOptions[0]) : abs(m_nPrintOptions[1]));
	}
	GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE));
	GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE));
	GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsPrintingPage::OnChangePrintSide()
{
	UINT  nMode;
	CHEXPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		nMode = (!SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_GETPOS)) ? ((IsTelemetryDataOptions()) ? ((pJobInfo->GetPrintMode() | HEX_PRINT_FIRSTDATASIDE) & ~(HEX_PRINT_ALLDATA | HEX_PRINT_LASTDATASIDE)) : ((pJobInfo->GetPrintMode() | HEX_PRINT_FIRSTSPYLOCATIONSSIDE) & ~(HEX_PRINT_ALLSPYLOCATIONS | HEX_PRINT_LASTSPYLOCATIONSSIDE))) : ((IsTelemetryDataOptions()) ? ((pJobInfo->GetPrintMode() | HEX_PRINT_LASTDATASIDE) & ~(HEX_PRINT_ALLDATA | HEX_PRINT_FIRSTDATASIDE)) : ((pJobInfo->GetPrintMode() | HEX_PRINT_LASTSPYLOCATIONSSIDE) & ~(HEX_PRINT_ALLSPYLOCATIONS | HEX_PRINT_FIRSTSPYLOCATIONSSIDE)));
		pJobInfo->SetPrintMode(nMode);
	}
	m_nPrintOptions[0] = (IsTelemetryDataOptions()) ? ((!SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_GETPOS)) ? abs(m_nPrintOptions[0]) : -abs(m_nPrintOptions[0])) : m_nPrintOptions[0];
	m_nPrintOptions[1] = (IsSpyLocationsOptions()) ? ((!SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_GETPOS)) ? abs(m_nPrintOptions[1]) : -abs(m_nPrintOptions[1])) : m_nPrintOptions[1];
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsPrintingPage::OnSpinchangePrintSideCount()
{
	UINT  nCount[2];
	CHEXPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		if (pJobInfo->GetPrintBySide(nCount[0], nCount[1]))
		{
			nCount[0] = (IsTelemetryDataOptions()) ? (UINT)Spinbox_GetPos(GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)) : nCount[0];
			nCount[1] = (IsSpyLocationsOptions()) ? (UINT)Spinbox_GetPos(GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)) : nCount[1];
			pJobInfo->SetPrintBySide(nCount[0], nCount[1]);
		}
	}
	m_nPrintOptions[0] = (IsTelemetryDataOptions()) ? ((IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE)) ? ((!SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_GETPOS)) ? (INT)Spinbox_GetPos(GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)) : (INT)(-Spinbox_GetPos(GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)))) : 0) : m_nPrintOptions[0];
	m_nPrintOptions[1] = (IsSpyLocationsOptions()) ? ((IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE)) ? ((!SendDlgItemMessage(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_GETPOS)) ? (INT)Spinbox_GetPos(GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)) : (INT)(-Spinbox_GetPos(GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)))) : 0) : m_nPrintOptions[1];
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsPrintingPage::OnEditchangeComments()
{
	CString  szComments;
	CHEXPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->GetWindowText(szComments);
		GetDlgItem(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)->EnableWindow(!szComments.IsEmpty());
		CheckDlgButton(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS, (!szComments.IsEmpty()) ? IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS) : FALSE);
		pJobInfo->SetPrintMode((IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)) ? (pJobInfo->GetPrintMode() | HEX_PRINT_CLEARCOMMENTS) : (pJobInfo->GetPrintMode() & ~HEX_PRINT_CLEARCOMMENTS));
		pJobInfo->SetComments(szComments);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsPrintingPage::OnResetComments()
{
	UINT  nMode;
	CHEXPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		nMode = (IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)) ? (pJobInfo->GetPrintMode() | HEX_PRINT_CLEARCOMMENTS) : (pJobInfo->GetPrintMode() & ~HEX_PRINT_CLEARCOMMENTS);
		pJobInfo->SetPrintMode(nMode);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CHEXSettingsPrintJobsPage property page

IMPLEMENT_DYNCREATE(CHEXSettingsPrintJobsPage, CLocalePropertyPage)

CHEXSettingsPrintJobsPage::CHEXSettingsPrintJobsPage() : CLocalePropertyPage(CHEXSettingsPrintJobsPage::IDD)
{
	//{{AFX_DATA_INIT(CHEXSettingsPrintJobsPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CHEXSettingsPrintJobsPage::Initialize()
{
	CHEXOpenDialog  *pDialog;

	return((((pDialog = GetParentDialog()->GetParentDialog()) && pDialog->GetPrintJobs(m_pJobs[0])) || GetParentDisplay()->GetPrintJobs(m_pJobs[0])) ? m_pJobs[1].Copy(&m_pJobs[0]) : FALSE);
}

BOOL CHEXSettingsPrintJobsPage::GetJobs(CHEXPrintJobs &pJobs) CONST
{
	return((pJobs.Copy(&m_pJobs[0])) ? Check(FALSE) : FALSE);
}

CHEXSettingsDialog *CHEXSettingsPrintJobsPage::GetParentDialog() CONST
{
	return((CHEXSettingsDialog *)CLocalePropertyPage::GetParent());
}

CHEXWnd *CHEXSettingsPrintJobsPage::GetParentDisplay() CONST
{
	return((CHEXWnd *)GetParentDialog()->GetParentDisplay());
}

BOOL CHEXSettingsPrintJobsPage::EnumJobs()
{
	INT  nJob;
	INT  nJobs;
	UINT  nMode;
	CHEXPrintJobInfo  *pJobInfo;

	SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, LB_RESETCONTENT);
	SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_RESETCONTENT);
	for (nJob = 0, nJobs = (INT)m_pJobs[0].GetSize(); nJob < nJobs; nJob = nJob + 1)
	{
		if ((pJobInfo = m_pJobs[0].GetAt(nJob)) && pJobInfo->GetName() != STRING(IDS_PRINTJOB_DEFAULTNAME))
		{
			if (SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pJobInfo->GetName()) >= 0)
			{
				if (((nMode = pJobInfo->GetPrintMode()) & HEX_PRINT_ACTIVE) && ((nMode & HEX_PRINT_ATTIME) || (nMode & HEX_PRINT_ATDAILYTIME) || (nMode & HEX_PRINT_ATEVENT)))
				{
					if (SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR)
					{
						pJobInfo->SetPrintMode(nMode & ~(HEX_PRINT_ACTIVE | HEX_PRINT_ATTIME | HEX_PRINT_ATDAILYTIME | HEX_PRINT_ATEVENT | HEX_PRINT_REPEATBYINTERVAL | HEX_PRINT_REPEATSTOPBYCOUNT | HEX_PRINT_REPEATSTOPBYTIME | HEX_PRINT_DAILYREPEATSTOPBYCOUNT | HEX_PRINT_DAILYREPEATSTOPBYTIME));
						continue;
					}
				}
			}
		}
	}
	if (SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, LB_GETCOUNT) > 0)
	{
		SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, LB_SETCURSEL);
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_DETAILS)->EnableWindow();
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS_STATIC)->EnableWindow();
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS)->EnableWindow();
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)Listbox_GetText(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS), (INT)SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, LB_GETCURSEL))) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_REMOVEJOB)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
		ShowJobInfo();
		return TRUE;
	}
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_DETAILS)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_REMOVEJOB)->EnableWindow(FALSE);
	ShowJobInfo();
	return FALSE;
}

BOOL CHEXSettingsPrintJobsPage::EnumEvents()
{
	INT  nEvent;
	INT  nEvents;
	CTelemetryEvents  pEvents;
	CTelemetryEventInfo  *pEventInfo;

	for (nEvent = 0, nEvents = (GetTelemetryEvents(pEvents)) ? (INT)pEvents.GetSize() : 0; nEvent < nEvents; nEvent++)
	{
		if ((pEventInfo = pEvents.GetAt(nEvent))) SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pEventInfo->GetName());
		continue;
	}
	return((SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CHEXSettingsPrintJobsPage::ShowJobInfo()
{
	UINT  nStopCount;
	CString  szEvent;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CTimeSpan  tDailyTime;
	CHEXPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		Timespinbox_SetTime(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME), (pJobInfo->GetPrintAtTime(tTime) || pJobInfo->GetPrintAtTime(tTime, tInterval) || pJobInfo->GetPrintAtTime(tTime, tInterval, nStopCount) || pJobInfo->GetPrintAtTime(tTime, tInterval, tStopTime)) ? tTime : CTime::GetCurrentTime().GetTime());
		Timespinbox_SetTime(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME), (pJobInfo->GetPrintAtDailyTime(tDailyTime) || pJobInfo->GetPrintAtDailyTime(tDailyTime, nStopCount) || pJobInfo->GetPrintAtDailyTime(tDailyTime, tStopTime)) ? CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + tDailyTime.GetTotalSeconds()) : CTime::GetCurrentTime().GetTime());
		SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_SETCURSEL, (pJobInfo->GetPrintAtEvent(szEvent)) ? (WPARAM)SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szEvent) : (WPARAM)-1);
		SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, (SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_HEXSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS)) < 0 && (pJobInfo->GetPrintMode() & HEX_PRINT_ATTIME)) ? CB_ADDSTRING : CB_FINDSTRING, (WPARAM)NULL, (LPARAM)STRING(IDS_HEXSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS));
		SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, (SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_HEXSETTINGS_PRINTJOBSPAGE_DAILYPRINTS)) < 0 && (pJobInfo->GetPrintMode() & HEX_PRINT_ATDAILYTIME)) ? CB_ADDSTRING : CB_FINDSTRING, (WPARAM)NULL, (LPARAM)STRING(IDS_HEXSETTINGS_PRINTJOBSPAGE_DAILYPRINTS));
		SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_SETCURSEL, ((pJobInfo->GetPrintMode() & HEX_PRINT_ATTIME) || (pJobInfo->GetPrintMode() & HEX_PRINT_ATDAILYTIME)) ? (WPARAM)SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)((pJobInfo->GetPrintMode() & HEX_PRINT_ATTIME) ? STRING(IDS_HEXSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS) : STRING(IDS_HEXSETTINGS_PRINTJOBSPAGE_DAILYPRINTS))) : (WPARAM)-1);
		CheckDlgButton(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME, (pJobInfo->GetPrintMode() & HEX_PRINT_ATTIME) ? TRUE : FALSE);
		CheckDlgButton(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME, (pJobInfo->GetPrintMode() & HEX_PRINT_ATDAILYTIME) ? TRUE : FALSE);
		CheckDlgButton(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT, (pJobInfo->GetPrintMode() & HEX_PRINT_ATEVENT) ? ((SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_GETCURSEL) >= 0) ? TRUE : FALSE) : FALSE);
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR)->EnableWindow();
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME)->EnableWindow();
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME));
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)->EnableWindow();
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT));
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT));
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		SetJobRepetitionInfo();
		return;
	}
	CheckDlgButton(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME, FALSE);
	CheckDlgButton(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME, FALSE);
	CheckDlgButton(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT, FALSE);
	CheckDlgButton(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME, FALSE);
	CheckDlgButton(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, FALSE);
	CheckDlgButton(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, FALSE);
	SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_SETCURSEL, (WPARAM)-1);
	SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_SETCURSEL, (WPARAM)-1);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow(FALSE);
}

BOOL CHEXSettingsPrintJobsPage::CheckJobInfo() CONST
{
	UINT  nStopCount;
	CString  szEvent;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CTimeSpan  tDailyTime;
	CHEXPrintJobInfo  *pJobInfo;

	return(((pJobInfo = FindJobInfo())) ? ((pJobInfo->GetPrintAtTime(tTime) && tTime > CTime::GetCurrentTime()) || pJobInfo->GetPrintAtTime(tTime, tInterval) || (pJobInfo->GetPrintAtTime(tTime, tInterval, nStopCount) && tTime.GetTime() + tInterval.GetTotalSeconds()*(TIMEKEY)nStopCount > CTime::GetCurrentTime().GetTime()) || (pJobInfo->GetPrintAtTime(tTime, tInterval, tStopTime) && tStopTime > CTime::GetCurrentTime()) || pJobInfo->GetPrintAtDailyTime(tDailyTime) || pJobInfo->GetPrintAtDailyTime(tDailyTime, nStopCount) || (pJobInfo->GetPrintAtDailyTime(tDailyTime, tStopTime) && tStopTime > CTime::GetCurrentTime()) || pJobInfo->GetPrintAtEvent(szEvent)) : FALSE);
}

CHEXPrintJobInfo *CHEXSettingsPrintJobsPage::FindJobInfo(BOOL bActive) CONST
{
	INT  nJob;
	INT  nJobs;
	CString  szJobName[2];
	CHEXPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (INT)m_pJobs[0].GetSize(), szJobName[0] = Listbox_GetText(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS), (INT)GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS)->SendMessage(LB_GETCURSEL)), szJobName[1] = Listbox_GetText(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS), (INT)GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS)->SendMessage(LB_GETCURSEL)), szJobName[0] = (!bActive) ? szJobName[0] : szJobName[1]; nJob < nJobs; nJob++)
	{
		if ((pJobInfo = m_pJobs[0].GetAt(nJob)) && pJobInfo->GetName() == szJobName[0]) break;
		continue;
	}
	return((nJob < nJobs) ? pJobInfo : (CHEXPrintJobInfo *)NULL);
}

VOID CHEXSettingsPrintJobsPage::SetJobRepetitionInfo()
{
	UINT  nStopCount;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CTimeSpan  tDailyTime;
	CHEXPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		Timespinbox_SetTime(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), ((GetJobRepetitionType() == HEXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  pJobInfo->GetPrintAtTime(tTime, tInterval, tStopTime)) || (GetJobRepetitionType() == HEXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  pJobInfo->GetPrintAtDailyTime(tDailyTime, tStopTime))) ? tStopTime : CTime::GetCurrentTime().GetTime());
		Spinbox_SetPos(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME), (pJobInfo->GetPrintAtTime(tTime, tInterval) || pJobInfo->GetPrintAtTime(tTime, tInterval, nStopCount) || pJobInfo->GetPrintAtTime(tTime, tInterval, tStopTime)) ? (tInterval.GetTotalSeconds() / SECONDSPERMINUTE) : 0);
		Spinbox_SetPos(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), ((GetJobRepetitionType() == HEXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  pJobInfo->GetPrintAtTime(tTime, tInterval, nStopCount)) || (GetJobRepetitionType() == HEXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  pJobInfo->GetPrintAtDailyTime(tDailyTime, nStopCount))) ? nStopCount : 0);
		CheckDlgButton(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME, (GetJobRepetitionType() == HEXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY && (pJobInfo->GetPrintMode() & HEX_PRINT_REPEATBYINTERVAL)) ? TRUE : FALSE);
		CheckDlgButton(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, ((GetJobRepetitionType() == HEXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY && (pJobInfo->GetPrintMode() & HEX_PRINT_REPEATSTOPBYCOUNT)) || (GetJobRepetitionType() == HEXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY && (pJobInfo->GetPrintMode() & HEX_PRINT_DAILYREPEATSTOPBYCOUNT))) ? TRUE : FALSE);
		CheckDlgButton(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, ((GetJobRepetitionType() == HEXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY && (pJobInfo->GetPrintMode() & HEX_PRINT_REPEATSTOPBYTIME)) || (GetJobRepetitionType() == HEXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY && (pJobInfo->GetPrintMode() & HEX_PRINT_DAILYREPEATSTOPBYTIME))) ? TRUE : FALSE);
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)->EnableWindow((GetJobRepetitionType() == HEXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY) ? TRUE : FALSE);
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)->EnableWindow(GetJobRepetitionType() == HEXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC)->EnableWindow(GetJobRepetitionType() == HEXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC)->EnableWindow((IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && (GetJobRepetitionType() == HEXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY || IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)));
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)->EnableWindow((IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && (GetJobRepetitionType() == HEXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY || IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)));
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow((IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES));
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow((IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES));
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)->EnableWindow((IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && (GetJobRepetitionType() == HEXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY || IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)));
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow((IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME));
		return;
	}
	CheckDlgButton(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME, FALSE);
	CheckDlgButton(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, FALSE);
	CheckDlgButton(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow(FALSE);
}

UINT CHEXSettingsPrintJobsPage::GetJobRepetitionType() CONST
{
	CString  szRepetitionType;

	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE)->GetWindowText(szRepetitionType);
	return((szRepetitionType == STRING(IDS_HEXSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS) || szRepetitionType == STRING(IDS_HEXSETTINGS_PRINTJOBSPAGE_DAILYPRINTS)) ? ((szRepetitionType == STRING(IDS_HEXSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS)) ? HEXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY : HEXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY) : 0);
}

BOOL CHEXSettingsPrintJobsPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? !m_pJobs[0].Compare(&m_pJobs[1]) : CLocalePropertyPage::IsModified()) : FALSE);
}

BOOL CHEXSettingsPrintJobsPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? TRUE : CLocalePropertyPage::Check()) : TRUE);
}

void CHEXSettingsPrintJobsPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHEXSettingsPrintJobsPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CHEXSettingsPrintJobsPage::PostNcDestroy()
{
	m_pJobs[0].RemoveAll();
	m_pJobs[1].RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CHEXSettingsPrintJobsPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CHEXSettingsPrintJobsPage)
	ON_BN_CLICKED(IDC_HEXSETTINGS_PRINTJOBSPAGE_ADDJOB, OnAddJob)
	ON_BN_CLICKED(IDC_HEXSETTINGS_PRINTJOBSPAGE_REMOVEJOB, OnRemoveJob)
	ON_BN_CLICKED(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME, OnPrintAtTime)
	ON_BN_CLICKED(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME, OnPrintAtDailyTime)
	ON_BN_CLICKED(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT, OnPrintAtEvent)
	ON_BN_CLICKED(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME, OnRepeatByTime)
	ON_BN_CLICKED(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, OnRepetitionStopByCopies)
	ON_BN_CLICKED(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, OnRepetitionStopByTime)
	ON_CBN_SELCHANGE(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, OnSelchangeEvent)
	ON_CBN_SELCHANGE(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, OnSelchangeRepetitionType)
	ON_LBN_SELCHANGE(IDC_HEXSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, OnSelchangeDefinedJob)
	ON_LBN_SELCHANGE(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, OnSelchangeActiveJob)
	ON_CONTROL(SBXN_CHANGE, IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME, OnSpinchangeRepeatTime)
	ON_CONTROL(SBXN_CHANGE, IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES, OnSpinchangeRepetitionStopCopies)
	ON_CONTROL(TSBXN_CHANGE, IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME, OnSpinchangePrintTime)
	ON_CONTROL(TSBXN_CHANGE, IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME, OnSpinchangePrintDailyTime)
	ON_CONTROL(TSBXN_CHANGE, IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME, OnSpinchangeRepetitionStopTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHEXSettingsPrintJobsPage message handlers

BOOL CHEXSettingsPrintJobsPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	Spinbox_SetRange(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME), HEXSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMINTERVAL, HEXSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMINTERVAL);
	Spinbox_SetRange(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), HEXSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES, HEXSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES);
	EnumEvents();
	return TRUE;
}

BOOL CHEXSettingsPrintJobsPage::OnSetActive()
{
	EnumJobs();
	return CLocalePropertyPage::OnSetActive();
}

BOOL CHEXSettingsPrintJobsPage::OnKillActive()
{
	GetParentDialog()->OnDataExchange(GetSafeHwnd(), m_pJobs[0]);
	return CLocalePropertyPage::OnKillActive();
}

BOOL CHEXSettingsPrintJobsPage::OnDataExchange(CONST CHEXPrintJobs &pJobs)
{
	return m_pJobs[0].Copy(&pJobs);
}

void CHEXSettingsPrintJobsPage::OnAddJob()
{
	CHEXPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	if ((pJobInfo = FindJobInfo()))
	{
		pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() | HEX_PRINT_ACTIVE);
		SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pJobInfo->GetName());
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow(FALSE);
	}
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsPrintJobsPage::OnRemoveJob()
{
	CHEXPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	if ((pJobInfo = FindJobInfo(TRUE)))
	{
		for (pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~(HEX_PRINT_ACTIVE | HEX_PRINT_ATTIME | HEX_PRINT_ATDAILYTIME | HEX_PRINT_ATEVENT | HEX_PRINT_REPEATBYINTERVAL | HEX_PRINT_REPEATSTOPBYCOUNT | HEX_PRINT_REPEATSTOPBYTIME | HEX_PRINT_DAILYREPEATSTOPBYCOUNT | HEX_PRINT_DAILYREPEATSTOPBYTIME)), SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCURSEL)); pJobInfo == FindJobInfo(); )
		{
			ShowJobInfo();
			break;
		}
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_REMOVEJOB)->EnableWindow(FALSE);
	}
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsPrintJobsPage::OnSelchangeDefinedJob()
{
	CHEXPrintJobInfo  *pJobInfo;

	ShowJobInfo();
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow(((pJobInfo = FindJobInfo()) && SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
}

void CHEXSettingsPrintJobsPage::OnSelchangeActiveJob()
{
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_REMOVEJOB)->EnableWindow();
}

void CHEXSettingsPrintJobsPage::OnPrintAtTime()
{
	CTimeKey  tTime;
	CHEXPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		if (IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME))
		{
			Timespinbox_SetTime(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME), (tTime = CTime::GetCurrentTime().GetTime() + SECONDSPERMINUTE*HEXSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL));
			SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)STRING(IDS_HEXSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS));
			pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | HEX_PRINT_ATTIME) & ~(HEX_PRINT_REPEATBYINTERVAL | HEX_PRINT_REPEATSTOPBYCOUNT | HEX_PRINT_REPEATSTOPBYTIME));
			pJobInfo->SetPrintAtTime(tTime);
		}
		else
		{
			SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_HEXSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS)));
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~(HEX_PRINT_ATTIME | HEX_PRINT_REPEATBYINTERVAL | HEX_PRINT_REPEATSTOPBYCOUNT | HEX_PRINT_REPEATSTOPBYTIME));
		}
		SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_SETCURSEL, (IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) ? (WPARAM)SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)((IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME)) ? STRING(IDS_HEXSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS) : STRING(IDS_HEXSETTINGS_PRINTJOBSPAGE_DAILYPRINTS))) : (WPARAM)-1);
		Spinbox_SetRange(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), (IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME)) ? (HEXSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES + 1) : HEXSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES, HEXSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES);
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME));
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		SetJobRepetitionInfo();
	}
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsPrintJobsPage::OnPrintAtDailyTime()
{
	CTimeKey  tTime;
	CHEXPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		if (IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME))
		{
			Timespinbox_SetTime(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME), (tTime = CTime::GetCurrentTime().GetTime() + SECONDSPERMINUTE*HEXSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL));
			SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)STRING(IDS_HEXSETTINGS_PRINTJOBSPAGE_DAILYPRINTS));
			pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | HEX_PRINT_ATDAILYTIME) & ~(HEX_PRINT_DAILYREPEATSTOPBYCOUNT | HEX_PRINT_DAILYREPEATSTOPBYTIME));
			pJobInfo->SetPrintAtDailyTime(tTime.GetTime() % SECONDSPERDAY);
		}
		else
		{
			SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_HEXSETTINGS_PRINTJOBSPAGE_DAILYPRINTS)));
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~(HEX_PRINT_ATDAILYTIME | HEX_PRINT_DAILYREPEATSTOPBYCOUNT | HEX_PRINT_DAILYREPEATSTOPBYTIME));
		}
		SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_SETCURSEL, (IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) ? (WPARAM)SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)((IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) ? STRING(IDS_HEXSETTINGS_PRINTJOBSPAGE_DAILYPRINTS) : STRING(IDS_HEXSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS))) : (WPARAM)-1);
		Spinbox_SetRange(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), (IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) ? HEXSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES : (HEXSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES + 1), HEXSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES);
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		SetJobRepetitionInfo();
	}
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsPrintJobsPage::OnPrintAtEvent()
{
	CString  szEvent;
	CHEXPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		if (IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT))
		{
			SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_SETCURSEL);
			GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT)->GetWindowText(szEvent);
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() | HEX_PRINT_ATEVENT);
			pJobInfo->SetPrintAtEvent(szEvent);
		}
		else
		{
			SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_SETCURSEL, (WPARAM)-1);
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~HEX_PRINT_ATEVENT);
			pJobInfo->SetPrintAtEvent(EMPTYSTRING);
		}
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT));
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT));
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsPrintJobsPage::OnSelchangeEvent()
{
	CString  szEvent;
	CHEXPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT)->GetWindowText(szEvent);
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() | HEX_PRINT_ATEVENT);
		pJobInfo->SetPrintAtEvent(szEvent);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsPrintJobsPage::OnSelchangeRepetitionType()
{
	Spinbox_SetRange(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), (GetJobRepetitionType() == HEXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY) ? (HEXSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES + 1) : HEXSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES, HEXSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES);
	SetJobRepetitionInfo();
}

void CHEXSettingsPrintJobsPage::OnRepeatByTime()
{
	CHEXPrintJobInfo  *pJobInfo;

	for (CheckDlgButton(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME, !IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)); IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME); )
	{
		Spinbox_SetPos(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME), HEXSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL);
		break;
	}
	for (; (pJobInfo = FindJobInfo()); )
	{
		if (IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME))
		{
			pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | HEX_PRINT_REPEATBYINTERVAL) & ~(HEX_PRINT_REPEATSTOPBYCOUNT | HEX_PRINT_REPEATSTOPBYTIME));
			pJobInfo->SetPrintAtTime(Timespinbox_GetTime(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), SECONDSPERMINUTE*HEXSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL);
			GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
			break;
		}
		pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~(HEX_PRINT_REPEATBYINTERVAL | HEX_PRINT_REPEATSTOPBYCOUNT | HEX_PRINT_REPEATSTOPBYTIME));
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		break;
	}
	CheckDlgButton(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, FALSE);
	CheckDlgButton(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsPrintJobsPage::OnRepetitionStopByCopies()
{
	CHEXPrintJobInfo  *pJobInfo;

	for (CheckDlgButton(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, !IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)), GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)), GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)); IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES); )
	{
		Spinbox_SetPos(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), HEXSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTCOPIES);
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow(FALSE);
		CheckDlgButton(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, FALSE);
		break;
	}
	for (; (pJobInfo = FindJobInfo()); )
	{
		if (IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES))
		{
			if (GetJobRepetitionType() == HEXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY)
			{
				pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | HEX_PRINT_REPEATSTOPBYCOUNT) & ~HEX_PRINT_REPEATSTOPBYTIME);
				pJobInfo->SetPrintAtTime(Timespinbox_GetTime(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)), HEXSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTCOPIES);
			}
			if (GetJobRepetitionType() == HEXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY)
			{
				pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | HEX_PRINT_DAILYREPEATSTOPBYCOUNT) & ~HEX_PRINT_DAILYREPEATSTOPBYTIME);
				pJobInfo->SetPrintAtDailyTime(Timespinbox_GetTime(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)).GetTime() % SECONDSPERDAY, HEXSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTCOPIES);
			}
			GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
			break;
		}
		pJobInfo->SetPrintMode((GetJobRepetitionType() == HEXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY) ? (pJobInfo->GetPrintMode() & ~HEX_PRINT_REPEATSTOPBYCOUNT) : (pJobInfo->GetPrintMode() & ~HEX_PRINT_DAILYREPEATSTOPBYCOUNT));
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		break;
	}
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsPrintJobsPage::OnRepetitionStopByTime()
{
	CTimeKey  tStopTime;
	CHEXPrintJobInfo  *pJobInfo;

	for (CheckDlgButton(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, !IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)), GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)); IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME); )
	{
		for (CheckDlgButton(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, FALSE); GetJobRepetitionType() == HEXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY; )
		{
			Timespinbox_SetTime(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)).GetTime() + SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME))));
			break;
		}
		if (GetJobRepetitionType() == HEXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY) Timespinbox_SetTime(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)).GetTime() + CTimeSpan(1, 0, 0, 0).GetTotalSeconds()));
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow(FALSE);
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow(FALSE);
		break;
	}
	for (; (pJobInfo = FindJobInfo()); )
	{
		if (IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME))
		{
			if (GetJobRepetitionType() == HEXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY)
			{
				pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | HEX_PRINT_REPEATSTOPBYTIME) & ~HEX_PRINT_REPEATSTOPBYCOUNT);
				pJobInfo->SetPrintAtTime(Timespinbox_GetTime(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)), tStopTime);
			}
			if (GetJobRepetitionType() == HEXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY)
			{
				Timespinbox_GetTime(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME));
				pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | HEX_PRINT_DAILYREPEATSTOPBYTIME) & ~HEX_PRINT_DAILYREPEATSTOPBYCOUNT);
				pJobInfo->SetPrintAtDailyTime(Timespinbox_GetTime(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)).GetTime() % SECONDSPERDAY, tStopTime);
			}
			GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
			break;
		}
		pJobInfo->SetPrintMode((GetJobRepetitionType() == HEXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY) ? (pJobInfo->GetPrintMode() & ~HEX_PRINT_REPEATSTOPBYTIME) : (pJobInfo->GetPrintMode() & ~HEX_PRINT_DAILYREPEATSTOPBYTIME));
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		break;
	}
	GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsPrintJobsPage::OnSpinchangePrintTime()
{
	UINT  nStopCount;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeKey  tPrintTime;
	CTimeKey  tPrintStopTime;
	CTimeSpan  tPrintInterval;
	CHEXPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)); pJobInfo->GetPrintAtTime(tPrintTime); )
		{
			pJobInfo->SetPrintAtTime(tTime);
			break;
		}
		if (pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval)) pJobInfo->SetPrintAtTime(tTime, tPrintInterval);
		if (pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, nStopCount)) pJobInfo->SetPrintAtTime(tTime, tPrintInterval, nStopCount);
		if (pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, tPrintStopTime)) pJobInfo->SetPrintAtTime(tTime, tPrintInterval, (tTime + tPrintInterval.GetTotalSeconds() > tPrintStopTime.GetTime()) ? CTimeKey(tTime.GetTime() + tPrintInterval.GetTotalSeconds()) : tPrintStopTime);
		Timespinbox_SetTime(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (GetJobRepetitionType() == HEXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)) ? ((tTime + tPrintInterval.GetTotalSeconds() > tPrintStopTime.GetTime()) ? (tTime.GetTime() + tPrintInterval.GetTotalSeconds()) : tPrintStopTime) : tStopTime);
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsPrintJobsPage::OnSpinchangePrintDailyTime()
{
	UINT  nStopCount;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeKey  tPrintStopTime;
	CTimeSpan  tPrintTime;
	CHEXPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)), tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)); pJobInfo->GetPrintAtDailyTime(tPrintTime); )
		{
			pJobInfo->SetPrintAtDailyTime(tTime.GetTime() % SECONDSPERDAY);
			break;
		}
		if (pJobInfo->GetPrintAtDailyTime(tPrintTime, nStopCount)) pJobInfo->SetPrintAtDailyTime(tTime.GetTime() % SECONDSPERDAY, nStopCount);
		if (pJobInfo->GetPrintAtDailyTime(tPrintTime, tPrintStopTime)) pJobInfo->SetPrintAtDailyTime(tTime.GetTime() % SECONDSPERDAY, (SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + tTime.GetTime() % SECONDSPERDAY > tPrintStopTime.GetTime()) ? CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY + 1) + tTime.GetTime() % SECONDSPERDAY) : tPrintStopTime);
		Timespinbox_SetTime(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (GetJobRepetitionType() == HEXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)) ? ((SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + tTime.GetTime() % SECONDSPERDAY > tPrintStopTime.GetTime()) ? CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY + 1) + tTime.GetTime() % SECONDSPERDAY) : tPrintStopTime) : tStopTime);
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsPrintJobsPage::OnSpinchangeRepeatTime()
{
	UINT  nStopCount;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeKey  tPrintTime;
	CTimeKey  tPrintStopTime;
	CTimeSpan  tPrintInterval;
	CHEXPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)); pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval); )
		{
			pJobInfo->SetPrintAtTime(tPrintTime, SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)));
			break;
		}
		if (pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, nStopCount)) pJobInfo->SetPrintAtTime(tPrintTime, SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)), nStopCount);
		if (pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, tPrintStopTime)) pJobInfo->SetPrintAtTime(tPrintTime, SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)), (tPrintTime.GetTime() + SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)) > tPrintStopTime.GetTime()) ? CTimeKey(tPrintTime.GetTime() + SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME))) : tPrintStopTime);
		Timespinbox_SetTime(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (GetJobRepetitionType() == HEXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  IsDlgButtonChecked(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)) ? ((tPrintTime.GetTime() + SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)) > tPrintStopTime.GetTime()) ? CTimeKey(tPrintTime.GetTime() + SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME))) : tPrintStopTime) : tStopTime);
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsPrintJobsPage::OnSpinchangeRepetitionStopCopies()
{
	UINT  nStopCount;
	UINT  nPrintStopCount;
	CTimeKey  tPrintTime;
	CTimeSpan  tPrintInterval;
	CTimeSpan  tPrintDailyTime;
	CHEXPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (nStopCount = (UINT)Spinbox_GetPos(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)); GetJobRepetitionType() == HEXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY && pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, nPrintStopCount); )
		{
			pJobInfo->SetPrintAtTime(tPrintTime, tPrintInterval, nStopCount);
			break;
		}
		if (GetJobRepetitionType() == HEXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  pJobInfo->GetPrintAtDailyTime(tPrintDailyTime, nPrintStopCount)) pJobInfo->SetPrintAtDailyTime(tPrintDailyTime, nStopCount);
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXSettingsPrintJobsPage::OnSpinchangeRepetitionStopTime()
{
	CTimeKey  tTime;
	CTimeKey  tTimeKey;
	CTimeKey  tStopTime;
	CTimeKey  tPrintTime;
	CTimeKey  tPrintStopTime;
	CTimeSpan  tPrintInterval;
	CTimeSpan  tPrintDailyTime;
	CHEXPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)); GetJobRepetitionType() == HEXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY && pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, tPrintStopTime); )
		{
			if (tTime > tStopTime.GetTime() - tPrintInterval.GetTotalSeconds()) Timespinbox_SetTime(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (tStopTime = tTime.GetTime() + tPrintInterval.GetTotalSeconds()));
			pJobInfo->SetPrintAtTime(tTime, tPrintInterval, tStopTime);
			break;
		}
		if (GetJobRepetitionType() == HEXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  pJobInfo->GetPrintAtDailyTime(tPrintDailyTime, tPrintStopTime))
		{
			if (SECONDSPERDAY*(tTimeKey.GetTime() / SECONDSPERDAY) + tPrintDailyTime.GetTotalSeconds() > tStopTime.GetTime()) Timespinbox_SetTime(GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (tStopTime = SECONDSPERDAY*(tTimeKey.GetTime() / SECONDSPERDAY) + tPrintDailyTime.GetTotalSeconds()));
			pJobInfo->SetPrintAtDailyTime(tPrintDailyTime, tStopTime);
		}
		GetDlgItem(IDC_HEXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_HEXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CHEXSettingsTabCtrl

IMPLEMENT_DYNCREATE(CHEXSettingsTabCtrl, CTabCtrl)

BEGIN_MESSAGE_MAP(CHEXSettingsTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CHEXSettingsTabCtrl)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHEXSettingsTabCtrl message handlers


/////////////////////////////////////////////////////////////////////////////
// CHEXSettingsDialog

IMPLEMENT_DYNCREATE(CHEXSettingsDialog, CDisplayPropertySheetDialog)

CHEXSettingsDialog::CHEXSettingsDialog() : CDisplayPropertySheetDialog()
{
	AddPage(&m_pageLayout);
	AddPage(&m_pageContents);
	AddPage(&m_pageRetrieving);
	AddPage(&m_pagePrinting);
	AddPage(&m_pagePrintJobs);
}

BOOL CHEXSettingsDialog::GetLayoutFormat(UINT &nHorzEnum, UINT &nVertEnum, UINT &nLineLength, CUIntArray &nColors) CONST
{
	return m_pageLayout.GetFormat(nHorzEnum, nVertEnum, nLineLength, nColors);
}

BOOL CHEXSettingsDialog::GetLayoutTitleFont(LPLOGFONT pTitleFont) CONST
{
	return m_pageLayout.GetTitleFont(pTitleFont);
}

BOOL CHEXSettingsDialog::GetLayoutDataFont(LPLOGFONT pDataFont) CONST
{
	return m_pageLayout.GetDataFont(pDataFont);
}

BOOL CHEXSettingsDialog::GetLayoutSpyFont(LPLOGFONT pHeaderFont, LPLOGFONT pLocationsFont) CONST
{
	return m_pageLayout.GetSpyFont(pHeaderFont, pLocationsFont);
}

BOOL CHEXSettingsDialog::GetLayoutBadDataMode(BOOL &bEnable) CONST
{
	return m_pageLayout.GetBadDataMode(bEnable);
}

BOOL CHEXSettingsDialog::IsLayoutModified() CONST
{
	return m_pageLayout.IsModified();
}

BOOL CHEXSettingsDialog::GetSpyLocations(CHEXSpyLocations &pSpyLocations) CONST
{
	return m_pageContents.GetSpyLocations(pSpyLocations);
}

BOOL CHEXSettingsDialog::IsContentsModified() CONST
{
	return m_pageContents.IsModified();
}

BOOL CHEXSettingsDialog::GetRetrieveFileName(CString &szFileName) CONST
{
	return m_pageRetrieving.GetDataSourceFileName(szFileName);
}

BOOL CHEXSettingsDialog::IsRetrievingModified() CONST
{
	return m_pageRetrieving.IsModified();
}

BOOL CHEXSettingsDialog::GetPrintJobs(CHEXPrintJobs &pPrintJobs) CONST
{
	return(((GetActivePage()->GetSafeHwnd() != m_pagePrintJobs.GetSafeHwnd() && m_pagePrinting.GetJobs(pPrintJobs)) || (GetActivePage()->GetSafeHwnd() == m_pagePrintJobs.GetSafeHwnd() && m_pagePrintJobs.GetJobs(pPrintJobs))) ? TRUE : FALSE);
}

BOOL CHEXSettingsDialog::IsPrintingModified() CONST
{
	return m_pagePrinting.IsModified() || m_pagePrintJobs.IsModified();
}

CHEXOpenDialog *CHEXSettingsDialog::GetParentDialog() CONST
{
	return((GetParent() != (CWnd *)GetParentDisplay()) ? (CHEXOpenDialog *)GetParent() : (CHEXOpenDialog *)NULL);
}

CHEXWnd *CHEXSettingsDialog::GetParentDisplay() CONST
{
	return((CHEXWnd *)CDisplayPropertySheetDialog::GetParentDisplay());
}

BEGIN_MESSAGE_MAP(CHEXSettingsDialog, CDisplayPropertySheetDialog)
	//{{AFX_MSG_MAP(CHEXSettingsDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDHELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHEXSettingsDialog message handlers

BOOL CHEXSettingsDialog::OnInitDialog()
{
	INT  nPage;
	INT  nPages;
	CHourglassCursor  cCursor;

	CDisplayPropertySheetDialog::OnInitDialog();
	SetTitle(STRING(IDS_HEXSETTINGSDIALOG_TITLE));
	for (nPage = 0, nPages = GetPageCount(), m_wndTabCtrl.SubclassWindow(GetTabControl()->GetSafeHwnd()); nPage < nPages; nPage++)
	{
		SetActivePage((nPage + 1) % nPages);
		continue;
	}
	m_wndTabCtrl.SetFocus();
	return FALSE;
}

BOOL CHEXSettingsDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	CRect  rTab;
	CHEXPrintJobs  pPrintJobs;
	LPNMHDR  pNotifyInfo = (LPNMHDR)lParam;

	if (pNotifyInfo->code == TCN_SELCHANGING)
	{
		if (HIBYTE(GetKeyState(VK_LEFT)) && GetActivePage()->GetSafeHwnd() == m_pageRetrieving.GetSafeHwnd() && ((GetParentDialog() && GetParentDialog()->GetType() == HEX_TYPE_DUMPS) || (!GetParentDialog() && HIWORD(GetParentDisplay()->GetType()) == HEX_TYPE_DUMPS)))
		{
			SetActivePage(&m_pageLayout);
			*pResult = TRUE;
			return TRUE;
		}
		if (HIBYTE(GetKeyState(VK_RIGHT)) && GetActivePage()->GetSafeHwnd() == m_pageLayout.GetSafeHwnd() && ((GetParentDialog() && GetParentDialog()->GetType() == HEX_TYPE_DUMPS) || (!GetParentDialog() && HIWORD(GetParentDisplay()->GetType()) == HEX_TYPE_DUMPS)))
		{
			SetActivePage(&m_pageRetrieving);
			*pResult = TRUE;
			return TRUE;
		}
		if (HIBYTE(GetKeyState(VK_RIGHT)) && GetActivePage()->GetSafeHwnd() == m_pagePrinting.GetSafeHwnd() && m_pagePrinting.GetJobs(pPrintJobs) && pPrintJobs.GetSize() <= 1)
		{
			CAudioDevice::AlertBySound();
			*pResult = TRUE;
			return TRUE;
		}
		if (HIBYTE(GetKeyState(VK_LBUTTON)))
		{
			if (((GetParentDialog() && GetParentDialog()->GetType() == HEX_TYPE_DUMPS) || (!GetParentDialog() && HIWORD(GetParentDisplay()->GetType()) == HEX_TYPE_DUMPS)))
			{
				if (GetTabControl()->GetItemRect(GetPageIndex(&m_pageContents), rTab))
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

BOOL CHEXSettingsDialog::OnDataExchange(HWND hPage, CONST CHEXPrintJobs &pJobs)
{
	return(((hPage == m_pagePrinting.GetSafeHwnd() && m_pagePrintJobs.OnDataExchange(pJobs)) || (hPage == m_pagePrintJobs.GetSafeHwnd() && m_pagePrinting.OnDataExchange(pJobs))) ? TRUE : FALSE);
}

void CHEXSettingsDialog::OnOK()
{
	CHourglassCursor  cCursor;

	ReportEvent(((!GetParentDialog() && !GetParentDisplay()->OnCloseSettingsDialog(IDOK)) || (GetParentDialog() && !GetParentDialog()->OnCloseSettingsDialog(IDOK))) ? SYSTEM_WARNING_HEX_SETUP_FAILURE : SYSTEM_NOERROR);
	CDisplayPropertySheetDialog::OnOK();
}

void CHEXSettingsDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	if (!GetParentDialog()) GetParentDisplay()->OnCloseSettingsDialog(IDCANCEL);
	else  GetParentDialog()->OnCloseSettingsDialog(IDCANCEL);
	CDisplayPropertySheetDialog::OnCancel();
}

BOOL CHEXSettingsDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_HEXSETTINGSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CHEXSettingsDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_HEXSETTINGSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CHEXRetrieveDialog dialog

IMPLEMENT_DYNCREATE(CHEXRetrieveDialog, CDisplayDialog)

CHEXRetrieveDialog::CHEXRetrieveDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CHEXRetrieveDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CHEXRetrieveDialog::Create(CWnd *pParentWnd)
{
	CString  szType;
	CString  szTitle;
	CString  szLayout;
	CHEXWnd  *pHEXWnd;
	CDatabaseTMPacket  *pDatabaseTMPacket;

	if ((pHEXWnd = (CHEXWnd *)pParentWnd))
	{
		for (szTitle = (pHEXWnd->GetLayout(szLayout)) ? szLayout : STRING(IDS_WINDOW_UNKNOWNTITLE); HIWORD(pHEXWnd->GetType()) == HEX_TYPE_NORMAL; )
		{
			szTitle = ((pDatabaseTMPacket = GetDatabase()->GetTMPackets()->GetAt(GetDatabase()->GetTMPackets()->Find(szLayout)))) ? pDatabaseTMPacket->GetDescription() : STRING(IDS_WINDOW_UNKNOWNTITLE);
			szType.Format(STRING(IDS_HEXRETRIEVEDIALOG_TYPENORMAL), (LPCTSTR)szLayout);
			break;
		}
		for (; HIWORD(pHEXWnd->GetType()) == HEX_TYPE_STREAM; )
		{
			szType = STRING(IDS_HEXRETRIEVEDIALOG_TYPESTREAM);
			break;
		}
		for (; HIWORD(pHEXWnd->GetType()) == HEX_TYPE_DUMPS; )
		{
			szType = STRING(IDS_HEXRETRIEVEDIALOG_TYPEDUMPS);
			break;
		}
		return Create(pParentWnd, szTitle, szType);
	}
	return -1;
}
INT CHEXRetrieveDialog::Create(CWnd *pParentWnd, LPCTSTR pszTitle, LPCTSTR pszType)
{
	m_szType = pszType;
	m_szTitle = pszTitle;
	return CDisplayDialog::Create(pParentWnd, CHEXRetrieveDialog::IDD);
}

BOOL CHEXRetrieveDialog::GetMode(UINT &nMode) CONST
{
	nMode = (!IsDlgButtonChecked(IDC_HEX_RETRIEVE_REALTIME)) ? ((IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_EXACTTIME)) ? HEX_RETRIEVE_EXACTTIME : 0) : 0;
	nMode |= (!IsDlgButtonChecked(IDC_HEX_RETRIEVE_REALTIME)) ? ((IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_REDODUMPS)) ? HEX_RETRIEVE_REDODUMPS : 0) : 0;
	nMode |= (!IsDlgButtonChecked(IDC_HEX_RETRIEVE_REALTIME)) ? ((IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_ARCHIVEDUMPS)) ? HEX_RETRIEVE_ARCHIVEDUMPS : 0) : 0;
	nMode |= (!IsDlgButtonChecked(IDC_HEX_RETRIEVE_REALTIME)) ? ((IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_NOTIFYDUMPS)) ? HEX_RETRIEVE_NOTIFYDUMPS : 0) : 0;
	nMode |= (!IsDlgButtonChecked(IDC_HEX_RETRIEVE_REALTIME)) ? ((IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_STOPBYTIME) || IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_STOPBYEND) || IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_STOPBYREALTIME)) ? ((!IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_STOPBYTIME)) ? ((!IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_STOPBYEND)) ? HEX_RETRIEVE_STOPBYREALTIME : HEX_RETRIEVE_STOPBYEND) : HEX_RETRIEVE_STOPBYTIME) : 0) : 0;
	nMode |= (!IsDlgButtonChecked(IDC_HEX_RETRIEVE_REALTIME)) ? ((IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_AUTOMATIC)) ? HEX_RETRIEVE_AUTOFORWARD : ((IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_PSEUDOREALTIME)) ? HEX_RETRIEVE_PSEUDOREALTIME : HEX_RETRIEVE_MANUALFORWARD)) : 0;
	return TRUE;
}

BOOL CHEXRetrieveDialog::GetSpeed(UINT &nSpeed) CONST
{
	nSpeed = (!IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_AUTOMATIC)) ? (UINT)((GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_SPEED)->SendMessage(TBM_GETRANGEMIN) + GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_SPEED)->SendMessage(TBM_GETRANGEMAX)) / 2) : (UINT)GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_SPEED)->SendMessage(TBM_GETPOS);
	return((IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_AUTOMATIC)) ? TRUE : FALSE);
}

BOOL CHEXRetrieveDialog::GetInterval(CTimeSpan &tInterval) CONST
{
	tInterval = (IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_INTERVAL)) ? (SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_INTERVALTIME))) : 0;
	return((IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_INTERVAL)) ? TRUE : FALSE);
}

BOOL CHEXRetrieveDialog::GetStartTime(CTimeKey &tTimeKey) CONST
{
	CTimeKey  tTime;

	for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_STARTTIME)), tTimeKey = 0; !IsDlgButtonChecked(IDC_HEX_RETRIEVE_REALTIME) && tTime > 0; )
	{
		tTimeKey = tTime;
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXRetrieveDialog::GetStopTime(CTimeKey &tTimeKey) CONST
{
	CTimeKey  tTime;

	for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_STOPTIME)), tTimeKey = 0; IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_STOPBYTIME) && tTime > 0; )
	{
		tTimeKey = tTime;
		return TRUE;
	}
	return FALSE;
}

CHEXOpenDialog *CHEXRetrieveDialog::GetParentDialog() CONST
{
	return((GetParent() != (CWnd *)GetParentDisplay()) ? (CHEXOpenDialog *)GetParent() : (CHEXOpenDialog *)NULL);
}

CHEXWnd *CHEXRetrieveDialog::GetParentDisplay() CONST
{
	return((CHEXWnd *)CDisplayDialog::GetParentDisplay());
}

BOOL CHEXRetrieveDialog::SetRetrieveInfo()
{
	UINT  nMode;
	UINT  nSpeed;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;

	if (GetRetrieveInfo(nMode, nSpeed, tInterval, tStartTime, tStopTime))
	{
		Spinbox_SetPos(GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_INTERVALTIME), tInterval.GetTotalSeconds() / SECONDSPERMINUTE);
		Timespinbox_SetTime(GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_STARTTIME), (tStartTime > 0 || GetTMService()->GetRecentTMHistoryTimeKey(tStartTime)) ? tStartTime : CTime::GetCurrentTime().GetTime());
		Timespinbox_SetTime(GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_STOPTIME), (tStopTime.GetTime() > 0) ? tStopTime : CTime::GetCurrentTime().GetTime());
		Timespinbox_SetRange(GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_STOPTIME), Timespinbox_GetTime(GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_STARTTIME)), MAX_TIMEKEY);
		SendDlgItemMessage(IDC_HEX_RETRIEVE_HISTORY_SPEED, TBM_SETPOS, TRUE, (!IsDlgButtonChecked(IDC_HEX_RETRIEVE_REALTIME)) ? ((nMode) ? (((nMode & HEX_RETRIEVE_AUTOFORWARD) || (nMode & HEX_RETRIEVE_AUTOBACKWARD)) ? nSpeed : 0) : ((SendDlgItemMessage(IDC_HEX_RETRIEVE_HISTORY_SPEED, TBM_GETRANGEMIN) + SendDlgItemMessage(IDC_HEX_RETRIEVE_HISTORY_SPEED, TBM_GETRANGEMAX)) / 2)) : 0);
		CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_EXACTTIME, (!IsDlgButtonChecked(IDC_HEX_RETRIEVE_REALTIME) && (nMode & HEX_RETRIEVE_EXACTTIME)) ? TRUE : FALSE);
		CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_STOPBYTIME, (!IsDlgButtonChecked(IDC_HEX_RETRIEVE_REALTIME) && (nMode & HEX_RETRIEVE_STOPBYTIME) && (nMode & (HEX_RETRIEVE_MANUALFORWARD | HEX_RETRIEVE_MANUALBACKWARD)) == 0) ? TRUE : FALSE);
		CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_STOPBYEND, (!IsDlgButtonChecked(IDC_HEX_RETRIEVE_REALTIME) && (nMode & HEX_RETRIEVE_STOPBYEND) && (nMode & (HEX_RETRIEVE_MANUALFORWARD | HEX_RETRIEVE_MANUALBACKWARD)) == 0) ? TRUE : FALSE);
		CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_STOPBYREALTIME, (!IsDlgButtonChecked(IDC_HEX_RETRIEVE_REALTIME) && (!nMode || (nMode & HEX_RETRIEVE_STOPBYREALTIME))) ? TRUE : FALSE);
		CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_REDODUMPS, (!IsDlgButtonChecked(IDC_HEX_RETRIEVE_REALTIME) && (nMode & HEX_RETRIEVE_REDODUMPS)) ? TRUE : FALSE);
		CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_ARCHIVEDUMPS, (!IsDlgButtonChecked(IDC_HEX_RETRIEVE_REALTIME) && (nMode & HEX_RETRIEVE_REDODUMPS) && (nMode & HEX_RETRIEVE_ARCHIVEDUMPS)) ? TRUE : FALSE);
		CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_NOTIFYDUMPS, (!IsDlgButtonChecked(IDC_HEX_RETRIEVE_REALTIME) && (nMode & HEX_RETRIEVE_REDODUMPS) && (nMode & HEX_RETRIEVE_NOTIFYDUMPS)) ? TRUE : FALSE);
		CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_AUTOMATIC, (!IsDlgButtonChecked(IDC_HEX_RETRIEVE_REALTIME) && (!nMode || (nMode & HEX_RETRIEVE_AUTOFORWARD) || (nMode & HEX_RETRIEVE_AUTOBACKWARD))) ? TRUE : FALSE);
		CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_MANUAL, (!IsDlgButtonChecked(IDC_HEX_RETRIEVE_REALTIME) && ((nMode & HEX_RETRIEVE_MANUALFORWARD) || (nMode & HEX_RETRIEVE_MANUALBACKWARD))) ? TRUE : FALSE);
		CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_PSEUDOREALTIME, (!IsDlgButtonChecked(IDC_HEX_RETRIEVE_REALTIME) && (nMode & HEX_RETRIEVE_PSEUDOREALTIME)) ? TRUE : FALSE);
		CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_INTERVAL, (!IsDlgButtonChecked(IDC_HEX_RETRIEVE_REALTIME) && (nMode & HEX_RETRIEVE_PSEUDOREALTIME) == 0 && tInterval.GetTotalSeconds() > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_HEX_RETRIEVE_HISTORY)->EnableWindow(!IsDlgButtonChecked(IDC_HEX_RETRIEVE_REALTIME));
		GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_START_STATIC)->EnableWindow(!IsDlgButtonChecked(IDC_HEX_RETRIEVE_REALTIME));
		GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_STARTTIME)->EnableWindow(!IsDlgButtonChecked(IDC_HEX_RETRIEVE_REALTIME));
		GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_EXACTTIME)->EnableWindow(!IsDlgButtonChecked(IDC_HEX_RETRIEVE_REALTIME));
		GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_STOP_STATIC)->EnableWindow(!IsDlgButtonChecked(IDC_HEX_RETRIEVE_REALTIME));
		GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_STOPBYTIME)->EnableWindow(!IsDlgButtonChecked(IDC_HEX_RETRIEVE_REALTIME) && !IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_MANUAL));
		GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(!IsDlgButtonChecked(IDC_HEX_RETRIEVE_REALTIME) && IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_STOPBYTIME));
		GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_STOPBYEND)->EnableWindow(!IsDlgButtonChecked(IDC_HEX_RETRIEVE_REALTIME) && !IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_MANUAL));
		GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_STOPBYREALTIME)->EnableWindow(!IsDlgButtonChecked(IDC_HEX_RETRIEVE_REALTIME));
		GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_REDODUMPS)->EnableWindow((!IsDlgButtonChecked(IDC_HEX_RETRIEVE_REALTIME) && m_szType == STRING(IDS_HEXRETRIEVEDIALOG_TYPEDUMPS)) ? TRUE : FALSE);
		GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_ARCHIVEDUMPS)->EnableWindow(IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_REDODUMPS));
		GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_NOTIFYDUMPS)->EnableWindow(IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_REDODUMPS));
		GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_PLAYBACKMODE)->EnableWindow(!IsDlgButtonChecked(IDC_HEX_RETRIEVE_REALTIME));
		GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_AUTOMATIC)->EnableWindow(!IsDlgButtonChecked(IDC_HEX_RETRIEVE_REALTIME));
		GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_PSEUDOREALTIME)->EnableWindow(!IsDlgButtonChecked(IDC_HEX_RETRIEVE_REALTIME));
		GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_MANUAL)->EnableWindow(!IsDlgButtonChecked(IDC_HEX_RETRIEVE_REALTIME));
		GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_SPEED_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_AUTOMATIC));
		GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_SPEED)->EnableWindow(IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_AUTOMATIC));
		GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_SLOW)->EnableWindow(IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_AUTOMATIC));
		GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_FAST)->EnableWindow(IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_AUTOMATIC));
		GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_INTERVAL)->EnableWindow(!IsDlgButtonChecked(IDC_HEX_RETRIEVE_REALTIME) && !IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_PSEUDOREALTIME));
		GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_INTERVALTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_INTERVAL));
		GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_INTERVALTIME)->EnableWindow(IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_INTERVAL));
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXRetrieveDialog::GetRetrieveInfo(UINT &nMode, UINT &nSpeed, CTimeSpan &tInterval, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	CHEXWnd  *pHEXWnd;
	CHEXOpenDialog  *pDialog;

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
	if ((pHEXWnd = GetParentDisplay()))
	{
		for (pHEXWnd->GetRetrieveMode(nMode), nSpeed = 0, tInterval = 0, tStartTime = tStopTime = 0; nMode; )
		{
			pHEXWnd->GetRetrieveSpeed(nSpeed);
			pHEXWnd->GetRetrieveInterval(tInterval);
			pHEXWnd->GetRetrieveStartTime(tStartTime);
			pHEXWnd->GetRetrieveStopTime(tStopTime);
			break;
		}
		return TRUE;
	}
	return FALSE;
}

void CHEXRetrieveDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHEXRetrieveDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHEXRetrieveDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CHEXRetrieveDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_HEX_RETRIEVE_REALTIME, OnRetrieveRealtime)
	ON_BN_CLICKED(IDC_HEX_RETRIEVE_HISTORY_STOPBYTIME, OnRetrieveByTime)
	ON_BN_CLICKED(IDC_HEX_RETRIEVE_HISTORY_STOPBYEND, OnRetrieveByEnd)
	ON_BN_CLICKED(IDC_HEX_RETRIEVE_HISTORY_STOPBYREALTIME, OnRetrieveByRealtime)
	ON_BN_CLICKED(IDC_HEX_RETRIEVE_HISTORY_AUTOMATIC, OnRetrieveAutomatic)
	ON_BN_CLICKED(IDC_HEX_RETRIEVE_HISTORY_PSEUDOREALTIME, OnRetrievePseudoRealtime)
	ON_BN_CLICKED(IDC_HEX_RETRIEVE_HISTORY_MANUAL, OnRetrieveManual)
	ON_BN_CLICKED(IDC_HEX_RETRIEVE_HISTORY_REDODUMPS, OnRetrieveRedoDumps)
	ON_BN_CLICKED(IDC_HEX_RETRIEVE_HISTORY_INTERVAL, OnRetrieveInterval)
	ON_BN_CLICKED(IDC_HEX_RETRIEVE_HELP, OnHelp)
	ON_CONTROL(TSBXN_CHANGE, IDC_HEX_RETRIEVE_HISTORY_STARTTIME, OnSpinchangeRetrieveStartTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHEXRetrieveDialog message handlers

BOOL CHEXRetrieveDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	for (CDisplayDialog::OnInitDialog(), SendDlgItemMessage(IDC_HEX_RETRIEVE_HISTORY_SPEED, TBM_SETRANGE, TRUE, MAKELPARAM(0, 10)), Spinbox_SetRange(GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_INTERVALTIME), HEXRETRIEVEDIALOG_MINIMUMINTERVAL, HEXRETRIEVEDIALOG_MAXIMUMINTERVAL), GetDlgItem(IDC_HEX_RETRIEVE_TITLE)->SetWindowText(m_szTitle), GetDlgItem(IDC_HEX_RETRIEVE_TYPE)->SetWindowText(m_szType); SetRetrieveInfo(); )
	{
		GetDlgItem(IDC_HEX_RETRIEVE_DETAILS)->EnableWindow();
		GetDlgItem(IDC_HEX_RETRIEVE_TITLE_STATIC)->EnableWindow();
		GetDlgItem(IDC_HEX_RETRIEVE_TITLE)->EnableWindow();
		GetDlgItem(IDC_HEX_RETRIEVE_TYPE_STATIC)->EnableWindow();
		GetDlgItem(IDC_HEX_RETRIEVE_TYPE)->EnableWindow();
		GetDlgItem(IDC_HEX_RETRIEVE_REALTIME)->EnableWindow((GetParentDisplay()->GetMode() == DISPLAY_MODE_HISTORY) ? TRUE : FALSE);
		GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_STARTTIME)->SetFocus();
		GetDlgItem(IDOK)->EnableWindow();
		return FALSE;
	}
	return TRUE;
}

void CHEXRetrieveDialog::OnRetrieveRealtime()
{
	SetRetrieveInfo();
}

void CHEXRetrieveDialog::OnRetrieveByTime()
{
	CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_STOPBYTIME, TRUE);
	CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_STOPBYEND, FALSE);
	CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_STOPBYREALTIME, FALSE);
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_STOPTIME)->EnableWindow();
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_STOPTIME)->SetFocus();
}

void CHEXRetrieveDialog::OnRetrieveByEnd()
{
	CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_STOPBYTIME, FALSE);
	CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_STOPBYEND, TRUE);
	CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_STOPBYREALTIME, FALSE);
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(FALSE);
}

void CHEXRetrieveDialog::OnRetrieveByRealtime()
{
	CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_STOPBYTIME, FALSE);
	CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_STOPBYEND, FALSE);
	CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_STOPBYREALTIME, (IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_MANUAL)) ? !IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_STOPBYREALTIME) : TRUE);
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(FALSE);
}

void CHEXRetrieveDialog::OnRetrieveAutomatic()
{
	SendDlgItemMessage(IDC_HEX_RETRIEVE_HISTORY_SPEED, TBM_SETPOS, TRUE, (SendDlgItemMessage(IDC_HEX_RETRIEVE_HISTORY_SPEED, TBM_GETRANGEMIN) + SendDlgItemMessage(IDC_HEX_RETRIEVE_HISTORY_SPEED, TBM_GETRANGEMAX)) / 2);
	CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_STOPBYTIME, FALSE);
	CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_STOPBYEND, FALSE);
	CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_STOPBYREALTIME, TRUE);
	CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_AUTOMATIC, TRUE);
	CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_PSEUDOREALTIME, FALSE);
	CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_MANUAL, FALSE);
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_STOP_STATIC)->EnableWindow();
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_STOPBYTIME)->EnableWindow();
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_STOPBYTIME));
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_STOPBYEND)->EnableWindow();
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_STOPBYREALTIME)->EnableWindow();
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_SPEED_STATIC)->EnableWindow();
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_SPEED)->EnableWindow();
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_SLOW)->EnableWindow();
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_FAST)->EnableWindow();
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_INTERVAL)->EnableWindow(!IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_REDODUMPS));
}

void CHEXRetrieveDialog::OnRetrievePseudoRealtime()
{
	SendDlgItemMessage(IDC_HEX_RETRIEVE_HISTORY_SPEED, TBM_SETPOS, TRUE, 0);
	CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_STOPBYTIME, FALSE);
	CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_STOPBYEND, FALSE);
	CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_STOPBYREALTIME, TRUE);
	CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_AUTOMATIC, FALSE);
	CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_PSEUDOREALTIME, TRUE);
	CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_MANUAL, FALSE);
	CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_INTERVAL, FALSE);
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_STOP_STATIC)->EnableWindow();
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_STOPBYTIME)->EnableWindow();
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_STOPBYTIME));
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_STOPBYEND)->EnableWindow();
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_STOPBYREALTIME)->EnableWindow();
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_SPEED_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_SPEED)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_SLOW)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_FAST)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_INTERVAL)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_INTERVALTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_INTERVALTIME)->EnableWindow(FALSE);
}

void CHEXRetrieveDialog::OnRetrieveManual()
{
	SendDlgItemMessage(IDC_HEX_RETRIEVE_HISTORY_SPEED, TBM_SETPOS, TRUE, 0);
	CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_STOPBYTIME, FALSE);
	CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_STOPBYEND, FALSE);
	CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_STOPBYREALTIME, FALSE);
	CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_AUTOMATIC, FALSE);
	CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_PSEUDOREALTIME, FALSE);
	CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_MANUAL, TRUE);
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_STOP_STATIC)->EnableWindow();
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_STOPBYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_STOPBYEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_STOPBYREALTIME)->EnableWindow();
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_SPEED_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_SPEED)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_SLOW)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_FAST)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_INTERVAL)->EnableWindow(!IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_REDODUMPS));
}

void CHEXRetrieveDialog::OnRetrieveRedoDumps()
{
	CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_ARCHIVEDUMPS, FALSE);
	CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_NOTIFYDUMPS, FALSE);
	CheckDlgButton(IDC_HEX_RETRIEVE_HISTORY_INTERVAL, FALSE);
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_ARCHIVEDUMPS)->EnableWindow(IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_REDODUMPS));
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_NOTIFYDUMPS)->EnableWindow(IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_REDODUMPS));
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_INTERVAL)->EnableWindow(!IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_REDODUMPS));
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_INTERVALTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_INTERVALTIME)->EnableWindow(FALSE);
}

void CHEXRetrieveDialog::OnRetrieveInterval()
{
	Spinbox_SetPos(GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_INTERVALTIME), HEXRETRIEVEDIALOG_DEFAULTINTERVAL);
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_INTERVALTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_INTERVAL));
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_INTERVALTIME)->EnableWindow(IsDlgButtonChecked(IDC_HEX_RETRIEVE_HISTORY_INTERVAL));
	GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_INTERVALTIME)->SetFocus();
}

void CHEXRetrieveDialog::OnSpinchangeRetrieveStartTime()
{
	Timespinbox_SetRange(GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_STOPTIME), Timespinbox_GetTime(GetDlgItem(IDC_HEX_RETRIEVE_HISTORY_STARTTIME)), MAX_TIMEKEY);
}

void CHEXRetrieveDialog::OnOK()
{
	CHEXWnd  *pHEXWnd;
	CString  szLayout;
	CTimeKey  tTimeKey;
	CDisplayWnd  *pDisplayWnd;
	CHEXOpenDialog  *pDialog;
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
		if (IsDlgButtonChecked(IDC_HEX_RETRIEVE_REALTIME))
		{
			if ((pHEXWnd = (GetParentDisplay()->GetLayout(szLayout)) ? GetParentDisplay()->Find(GetParentDisplay()->GetType(), DISPLAY_MODE_REALTIME, szLayout) : (CHEXWnd *)NULL))
			{
				for (GetDisplayArea()->ActivateDisplay(pHEXWnd); pHEXWnd != GetParentDisplay(); )
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

void CHEXRetrieveDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	if (!GetParentDialog()) GetParentDisplay()->OnCloseRetrieveDialog(IDCANCEL);
	else  GetParentDialog()->OnCloseRetrieveDialog(IDCANCEL);
	CDisplayDialog::OnCancel();
}

BOOL CHEXRetrieveDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_HEXRETRIEVEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CHEXRetrieveDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_HEXRETRIEVEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CHEXFindDialog dialog

IMPLEMENT_DYNCREATE(CHEXFindDialog, CDisplayDialog)

CHEXFindDialog::CHEXFindDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CHEXFindDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CHEXFindDialog::Create(CWnd *pParentWnd, INT nType, CString &szLayout)
{
	INT  nDump;
	INT  nDumps;
	CString  szDump;
	CMemoryDump  *pDump[2];
	CMemoryDumps  pDumps;

	for (m_nType = nType, m_pPackets.RemoveAll(); nType == HEX_TYPE_NORMAL; )
	{
		m_pPackets.Copy(GetDatabase()->GetTMPackets());
		break;
	}
	for (m_pDumps.RemoveAll(); nType == HEX_TYPE_DUMPS; )
	{
		for (nDump = 0, nDumps = (GetMemoryDumpsService()->GetMemoryDumps(pDumps)) ? (INT)pDumps.GetSize() : 0; nDump < nDumps; nDump++)
		{
			if ((pDump[0] = pDumps.GetAt(nDump)) && (pDump[0]->GetArchivingFileFormats() & MEMORYDUMP_FILEFORMAT_NORMAL))
			{
				szDump.Format(STRING(IDS_HEXFINDDIALOG_RESULT_NORMALDUMPFORMAT), (LPCTSTR)pDump[0]->GetName());
				if ((pDump[1] = new CMemoryDump))
				{
					pDump[1]->Copy(pDump[0]);
					pDump[1]->SetName(szDump);
					if (m_pDumps.Add(pDump[1]) < 0) delete pDump[1];
				}
			}
			if (pDump[0]->GetArchivingFileFormats() & MEMORYDUMP_FILEFORMAT_DESCRIPTIVE)
			{
				szDump.Format(STRING(IDS_HEXFINDDIALOG_RESULT_DESCRIPTIVEDUMPFORMAT), (LPCTSTR)pDump[0]->GetName());
				if ((pDump[1] = new CMemoryDump))
				{
					pDump[1]->Copy(pDump[0]);
					pDump[1]->SetName(szDump);
					if (m_pDumps.Add(pDump[1]) < 0) delete pDump[1];
				}
			}
			if (pDump[0]->GetArchivingFileFormats() & MEMORYDUMP_FILEFORMAT_DELIMITED)
			{
				szDump.Format(STRING(IDS_HEXFINDDIALOG_RESULT_DELIMITEDDUMPFORMAT), (LPCTSTR)pDump[0]->GetName());
				if ((pDump[1] = new CMemoryDump))
				{
					pDump[1]->Copy(pDump[0]);
					pDump[1]->SetName(szDump);
					if (m_pDumps.Add(pDump[1]) < 0) delete pDump[1];
				}
			}
		}
		break;
	}
	if (CDisplayDialog::Create(pParentWnd, CHEXFindDialog::IDD) == IDOK)
	{
		if (nType == HEX_TYPE_NORMAL  &&  m_pPackets.GetSize() == 1)
		{
			szLayout.Format(STRING(IDS_HEXFINDDIALOG_RESULT_FORMAT), (LPCTSTR)m_pPackets.GetAt((INT)m_pPackets.GetUpperBound())->GetDescription(), (LPCTSTR)m_pPackets.GetAt((INT)m_pPackets.GetUpperBound())->GetTag());
			return IDOK;
		}
		if (nType == HEX_TYPE_DUMPS  &&  m_pDumps.GetSize() == 1)
		{
			szLayout = m_pDumps.GetAt((INT)m_pDumps.GetUpperBound())->GetName();
			return IDOK;
		}
	}
	return IDCANCEL;
}

CHEXWnd *CHEXFindDialog::GetParent() CONST
{
	return((CHEXWnd *)CDisplayDialog::GetParent());
}

BOOL CHEXFindDialog::EnumSearchKeys()
{
	for (; m_nType == HEX_TYPE_NORMAL; )
	{
		SendDlgItemMessage(IDC_HEX_FIND_KEY, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_HEXFINDDIALOG_KEY_PACKET));
		break;
	}
	for (; m_nType == HEX_TYPE_NORMAL || m_nType == HEX_TYPE_DUMPS; )
	{
		SendDlgItemMessage(IDC_HEX_FIND_KEY, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_HEXFINDDIALOG_KEY_DESCRIPTION));
		break;
	}
	return((SendDlgItemMessage(IDC_HEX_FIND_KEY, CB_SETCURSEL) >= 0) ? TRUE : FALSE);
}

BOOL CHEXFindDialog::EnumSearchValues()
{
	INT  nItem;
	INT  nItems;
	CString  szKey;
	CString  szValue;
	CDatabaseTMPacket  *pDatabaseTMPacket;

	GetDlgItem(IDC_HEX_FIND_KEY)->GetWindowText(szKey);
	if (szKey == STRING(IDS_HEXFINDDIALOG_KEY_PACKET))
	{
		for (nItem = 0, nItems = (INT)GetDatabase()->GetTMPackets()->GetSize(), SendDlgItemMessage(IDC_HEX_FIND_VALUE, CB_RESETCONTENT); nItem < nItems; nItem++)
		{
			if ((pDatabaseTMPacket = (CDatabaseTMPacket *)GetDatabase()->GetTMPackets()->GetAt(nItem)) != (CDatabaseTMPacket *)NULL)
			{
				szValue.Format(STRING(IDS_HEXFINDDIALOG_VALUE_FORMAT), (LPCTSTR)pDatabaseTMPacket->GetTag(), (LPCTSTR)pDatabaseTMPacket->GetDescription());
				SendDlgItemMessage(IDC_HEX_FIND_VALUE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szValue);
			}
		}
	}
	if (szKey == STRING(IDS_HEXFINDDIALOG_KEY_DESCRIPTION))
	{
		for (nItem = 0, nItems = (INT)m_szDescriptions.GetSize(), SendDlgItemMessage(IDC_HEX_FIND_VALUE, CB_RESETCONTENT); nItem < nItems; nItem++)
		{
			SendDlgItemMessage(IDC_HEX_FIND_VALUE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)m_szDescriptions.GetAt(nItem));
			continue;
		}
	}
	return((SendDlgItemMessage(IDC_HEX_FIND_VALUE, CB_GETCOUNT) >= 0) ? TRUE : FALSE);
}

VOID CHEXFindDialog::DoFindByPacket(LPCTSTR pszPacket)
{
	CString  szResult;
	CDatabaseTMPacket  *pDatabaseTMPacket;

	SendDlgItemMessage(IDC_HEX_FIND_RESULTS, LB_RESETCONTENT);
	if ((pDatabaseTMPacket = m_pPackets.GetAt(m_pPackets.Find(pszPacket))))
	{
		szResult.Format(STRING(IDS_HEXFINDDIALOG_RESULT_FORMAT), (LPCTSTR)pDatabaseTMPacket->GetDescription(), (LPCTSTR)pDatabaseTMPacket->GetTag());
		SendDlgItemMessage(IDC_HEX_FIND_RESULTS, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szResult);
	}
	GetDlgItem(IDC_HEX_FIND_RESULTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_HEX_FIND_RESULTS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_HEX_FIND_RESULTS)->EnableWindow((SendDlgItemMessage(IDC_HEX_FIND_RESULTS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CHEXFindDialog::DoFindByPackets(CONST CStringArray &szPackets)
{
	INT  nPacket[2];
	INT  nPackets[2];
	CString  szResult;
	CDatabaseTMPacket  *pDatabaseTMPacket[2];
	CDatabaseTMPackets  pPackets;

	for (nPacket[0] = 0, nPackets[0] = (INT)szPackets.GetSize(), pPackets.Copy(&m_pPackets); nPacket[0] < nPackets[0]; nPacket[0] += 2)
	{
		for (nPacket[1] = 0, nPackets[1] = (!nPacket[0] || szPackets.GetAt(nPacket[0] - 1) == STRING(IDS_HEXFINDDIALOG_QUERY_AND)) ? (INT)pPackets.GetSize() : -1; nPacket[1] < nPackets[1]; nPacket[1]++)
		{
			if ((pDatabaseTMPacket[0] = pPackets.GetAt(nPacket[1])) && pDatabaseTMPacket[0]->GetTag() != szPackets.GetAt(nPacket[0]))
			{
				pPackets.RemoveAt(nPacket[1]);
				delete pDatabaseTMPacket[0];
				nPackets[1]--;
				nPacket[1]--;
			}
		}
		for (nPacket[1] = 0, nPackets[1] = (nPacket[0] > 0 && szPackets.GetAt(nPacket[0] - 1) == STRING(IDS_HEXFINDDIALOG_QUERY_OR)) ? (INT)m_pPackets.GetSize() : -1; nPacket[1] < nPackets[1]; nPacket[1]++)
		{
			if ((pDatabaseTMPacket[0] = m_pPackets.GetAt(nPacket[1])) && pDatabaseTMPacket[0]->GetTag() == szPackets.GetAt(nPacket[0]))
			{
				if ((pDatabaseTMPacket[1] = (pPackets.Find(pDatabaseTMPacket[0]->GetTag()) < 0) ? new CDatabaseTMPacket : (CDatabaseTMPacket *)NULL))
				{
					pDatabaseTMPacket[1]->Copy(pDatabaseTMPacket[0]);
					if (pPackets.Add(pDatabaseTMPacket[1]) < 0)
					{
						delete pDatabaseTMPacket[1];
						continue;
					}
				}
			}
		}
	}
	SendDlgItemMessage(IDC_HEX_FIND_RESULTS, LB_RESETCONTENT);
	for (nPacket[0] = 0, nPackets[0] = (INT)pPackets.GetSize(); nPacket[0] < nPackets[0]; nPacket[0]++)
	{
		if ((pDatabaseTMPacket[0] = (CDatabaseTMPacket *)pPackets.GetAt(nPacket[0])) != (CDatabaseTMPacket *)NULL)
		{
			szResult.Format(STRING(IDS_HEXFINDDIALOG_RESULT_FORMAT), (LPCTSTR)pDatabaseTMPacket[0]->GetDescription(), (LPCTSTR)pDatabaseTMPacket[0]->GetTag());
			SendDlgItemMessage(IDC_HEX_FIND_RESULTS, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szResult);
		}
	}
	GetDlgItem(IDC_HEX_FIND_RESULTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_HEX_FIND_RESULTS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_HEX_FIND_RESULTS)->EnableWindow((SendDlgItemMessage(IDC_HEX_FIND_RESULTS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CHEXFindDialog::DoFindByDescription(LPCTSTR pszDescription)
{
	INT  nDump;
	INT  nDumps;
	INT  nPacket;
	INT  nPackets;
	CString  szResult;
	CMemoryDump  *pDump;
	CDatabaseTMPacket  *pDatabaseTMPacket;

	if (m_nType == HEX_TYPE_NORMAL)
	{
		for (nPacket = 0, nPackets = (INT)m_pPackets.GetSize(), SendDlgItemMessage(IDC_HEX_FIND_RESULTS, LB_RESETCONTENT); nPacket < nPackets; nPacket++)
		{
			if ((pDatabaseTMPacket = m_pPackets.GetAt(nPacket)) != (CDatabaseTMPacket *)NULL  &&  pDatabaseTMPacket->GetDescription().Find(pszDescription) >= 0)
			{
				szResult.Format(STRING(IDS_HEXFINDDIALOG_RESULT_FORMAT), (LPCTSTR)pDatabaseTMPacket->GetDescription(), (LPCTSTR)pDatabaseTMPacket->GetTag());
				SendDlgItemMessage(IDC_HEX_FIND_RESULTS, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szResult);
			}
		}
	}
	if (m_nType == HEX_TYPE_DUMPS)
	{
		for (nDump = 0, nDumps = (INT)m_pDumps.GetSize(), SendDlgItemMessage(IDC_HEX_FIND_RESULTS, LB_RESETCONTENT); nDump < nDumps; nDump++)
		{
			if ((pDump = m_pDumps.GetAt(nDump)) != (CMemoryDump *)NULL  &&  pDump->GetName().Find(pszDescription) >= 0)
			{
				SendDlgItemMessage(IDC_HEX_FIND_RESULTS, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)pDump->GetName());
				continue;
			}
		}
	}
	GetDlgItem(IDC_HEX_FIND_RESULTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_HEX_FIND_RESULTS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_HEX_FIND_RESULTS)->EnableWindow((SendDlgItemMessage(IDC_HEX_FIND_RESULTS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CHEXFindDialog::DoFindByDescriptions(CONST CStringArray &szDescriptions)
{
	INT  nDump;
	INT  nDumps;
	INT  nPacket;
	INT  nPackets;
	INT  nDescription;
	INT  nDescriptions;
	CString  szResult;
	CMemoryDump  *pDump[2];
	CMemoryDumps  pDumps;
	CDatabaseTMPacket  *pDatabaseTMPacket[2];
	CDatabaseTMPackets  pPackets;

	if (m_nType == HEX_TYPE_NORMAL)
	{
		for (nDescription = 0, nDescriptions = (INT)szDescriptions.GetSize(), pPackets.Copy(&m_pPackets); nDescription < nDescriptions; nDescription += 2)
		{
			for (nPacket = 0, nPackets = (!nDescription || szDescriptions.GetAt(nDescription - 1) == STRING(IDS_HEXFINDDIALOG_QUERY_AND)) ? (INT)pPackets.GetSize() : -1; nPacket < nPackets; nPacket++)
			{
				if ((pDatabaseTMPacket[0] = pPackets.GetAt(nPacket)) && pDatabaseTMPacket[0]->GetDescription().Find(szDescriptions.GetAt(nDescription)) < 0)
				{
					pPackets.RemoveAt(nPacket);
					delete pDatabaseTMPacket[0];
					nPackets--;
					nPacket--;
				}
			}
			for (nPacket = 0, nPackets = (nDescription > 0 && szDescriptions.GetAt(nDescription - 1) == STRING(IDS_HEXFINDDIALOG_QUERY_OR)) ? (INT)m_pPackets.GetSize() : -1; nPacket < nPackets; nPacket++)
			{
				if ((pDatabaseTMPacket[0] = m_pPackets.GetAt(nPacket)) && pDatabaseTMPacket[0]->GetDescription().Find(szDescriptions.GetAt(nDescription)) >= 0)
				{
					if ((pDatabaseTMPacket[1] = (pPackets.Find(pDatabaseTMPacket[0]->GetTag()) < 0) ? new CDatabaseTMPacket : (CDatabaseTMPacket *)NULL))
					{
						pDatabaseTMPacket[1]->Copy(pDatabaseTMPacket[0]);
						if (pPackets.Add(pDatabaseTMPacket[1]) < 0)
						{
							delete pDatabaseTMPacket[1];
							continue;
						}
					}
				}
			}
		}
		SendDlgItemMessage(IDC_HEX_FIND_RESULTS, LB_RESETCONTENT);
		for (nPacket = 0, nPackets = (INT)pPackets.GetSize(); nPacket < nPackets; nPacket++)
		{
			if ((pDatabaseTMPacket[0] = (CDatabaseTMPacket *)pPackets.GetAt(nPacket)) != (CDatabaseTMPacket *)NULL)
			{
				szResult.Format(STRING(IDS_HEXFINDDIALOG_RESULT_FORMAT), (LPCTSTR)pDatabaseTMPacket[0]->GetDescription(), (LPCTSTR)pDatabaseTMPacket[0]->GetTag());
				SendDlgItemMessage(IDC_HEX_FIND_RESULTS, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szResult);
			}
		}
	}
	if (m_nType == HEX_TYPE_DUMPS)
	{
		for (nDescription = 0, nDescriptions = (INT)szDescriptions.GetSize(), pDumps.Copy(&m_pDumps); nDescription < nDescriptions; nDescription += 2)
		{
			for (nDump = 0, nDumps = (!nDescription || szDescriptions.GetAt(nDescription - 1) == STRING(IDS_HEXFINDDIALOG_QUERY_AND)) ? (INT)pDumps.GetSize() : -1; nDump < nDumps; nDump++)
			{
				if ((pDump[0] = pDumps.GetAt(nDump)) && pDump[0]->GetName().Find(szDescriptions.GetAt(nDescription)) < 0)
				{
					pDumps.RemoveAt(nDump);
					delete pDump[0];
					nDumps--;
					nDump--;
				}
			}
			for (nDump = 0, nDumps = (nDescription > 0 && szDescriptions.GetAt(nDescription - 1) == STRING(IDS_HEXFINDDIALOG_QUERY_OR)) ? (INT)m_pDumps.GetSize() : -1; nDump < nDumps; nDump++)
			{
				if ((pDump[0] = m_pDumps.GetAt(nDump)) && pDump[0]->GetName().Find(szDescriptions.GetAt(nDescription)) >= 0)
				{
					if ((pDump[1] = (pDumps.Find(pDump[0]->GetName()) < 0) ? new CMemoryDump : (CMemoryDump *)NULL))
					{
						pDump[1]->Copy(pDump[0]);
						if (pDumps.Add(pDump[1]) < 0)
						{
							delete pDump[1];
							continue;
						}
					}
				}
			}
		}
		SendDlgItemMessage(IDC_HEX_FIND_RESULTS, LB_RESETCONTENT);
		for (nDump = 0, nDumps = (INT)pDumps.GetSize(); nDump < nDumps; nDump++)
		{
			if ((pDump[0] = (CMemoryDump *)pDumps.GetAt(nDump)) != (CMemoryDump *)NULL)
			{
				SendDlgItemMessage(IDC_HEX_FIND_RESULTS, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)pDump[0]->GetName());
				continue;
			}
		}
	}
	GetDlgItem(IDC_HEX_FIND_RESULTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_HEX_FIND_RESULTS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_HEX_FIND_RESULTS)->EnableWindow((SendDlgItemMessage(IDC_HEX_FIND_RESULTS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
}

void CHEXFindDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHEXFindDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHEXFindDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CHEXFindDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_HEX_FIND_SEARCH, OnSearch)
	ON_BN_CLICKED(IDC_HEX_FIND_OPEN, OnOpen)
	ON_BN_CLICKED(IDC_HEX_FIND_HELP, OnHelp)
	ON_CBN_EDITCHANGE(IDC_HEX_FIND_VALUE, OnEditchangeValue)
	ON_CBN_SELCHANGE(IDC_HEX_FIND_KEY, OnSelchangeKey)
	ON_CBN_SELCHANGE(IDC_HEX_FIND_VALUE, OnSelchangeValue)
	ON_LBN_DBLCLK(IDC_HEX_FIND_RESULTS, OnOpen)
	ON_LBN_SELCHANGE(IDC_HEX_FIND_RESULTS, OnSelchangeResult)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHEXFindDialog message handlers

BOOL CHEXFindDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	if (EnumSearchKeys() && EnumSearchValues())
	{
		GetDlgItem(IDC_HEX_FIND_KEY_STATIC)->EnableWindow();
		GetDlgItem(IDC_HEX_FIND_KEY)->EnableWindow();
		GetDlgItem(IDC_HEX_FIND_VALUE_STATIC)->EnableWindow();
		GetDlgItem(IDC_HEX_FIND_VALUE)->EnableWindow();
	}
	return TRUE;
}

void CHEXFindDialog::OnSearch()
{
	INT  nPos;
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	CString  szKey;
	CString  szValue;
	CString  szPacket;
	CString  szDescription;
	CStringArray  szPackets;
	CStringArray  szDescriptions;
	CDatabaseTMPacket  *pDatabaseTMPacket;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_HEX_FIND_KEY)->GetWindowText(szKey);
	GetDlgItem(IDC_HEX_FIND_VALUE)->GetWindowText(szValue);
	if (szKey == STRING(IDS_HEXFINDDIALOG_KEY_PACKET))
	{
		if ((nIndex = (INT)SendDlgItemMessage(IDC_HEX_FIND_VALUE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szValue)) >= 0)
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
			if (szValue.GetAt(nPos) != STRINGCHAR(IDS_HEXFINDDIALOG_QUERY_QUOTE))
			{
				nPos = -1;
				break;
			}
			for (nPos++; nPos < szValue.GetLength(); nPos++)
			{
				if (!_istspace(szValue.GetAt(nPos)) && szValue.GetAt(nPos) != STRINGCHAR(IDS_HEXFINDDIALOG_QUERY_QUOTE))
				{
					szPacket += szValue.GetAt(nPos);
					continue;
				}
				break;
			}
			if (szValue.GetAt(nPos) != STRINGCHAR(IDS_HEXFINDDIALOG_QUERY_QUOTE))
			{
				nPos = -1;
				break;
			}
			if ((pDatabaseTMPacket = GetDatabase()->GetTMPackets()->GetAt(GetDatabase()->GetTMPackets()->Find(szPacket))))
			{
				for (nPos++, szPackets.Add(szPacket); nPos < szValue.GetLength(); nPos++)
				{
					if (!_istspace(szValue.GetAt(nPos))) break;
					continue;
				}
				if (szValue.GetAt(nPos) == STRINGCHAR(IDS_HEXFINDDIALOG_QUERY_AND) || szValue.GetAt(nPos) == STRINGCHAR(IDS_HEXFINDDIALOG_QUERY_OR))
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
		GetDlgItem(IDC_HEX_FIND_VALUE)->SetFocus();
		CAudioDevice::AlertBySound();
		return;
	}
	if (szKey == STRING(IDS_HEXFINDDIALOG_KEY_DESCRIPTION))
	{
		for (nItem = 0, nItems = (INT)m_szDescriptions.GetSize(); nItem < nItems; nItem++)
		{
			if (m_szDescriptions.GetAt(nItem) == szValue) break;
			continue;
		}
		for (; nItem == nItems; )
		{
			SendDlgItemMessage(IDC_HEX_FIND_VALUE, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szValue);
			m_szDescriptions.Add(szValue);
			break;
		}
		if ((nPos = szValue.Find(STRING(IDS_HEXFINDDIALOG_QUERY_QUOTE))) < 0)
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
			if (szValue.GetAt(nPos) != STRINGCHAR(IDS_HEXFINDDIALOG_QUERY_QUOTE))
			{
				nPos = -1;
				break;
			}
			for (nPos++; nPos < szValue.GetLength(); nPos++)
			{
				if (!_istspace(szValue.GetAt(nPos)) && szValue.GetAt(nPos) != STRINGCHAR(IDS_HEXFINDDIALOG_QUERY_QUOTE))
				{
					szDescription += szValue.GetAt(nPos);
					continue;
				}
				break;
			}
			if (szValue.GetAt(nPos) != STRINGCHAR(IDS_HEXFINDDIALOG_QUERY_QUOTE))
			{
				nPos = -1;
				break;
			}
			for (nPos++, szDescriptions.Add(szDescription); nPos < szValue.GetLength(); nPos++)
			{
				if (!_istspace(szValue.GetAt(nPos))) break;
				continue;
			}
			if (szValue.GetAt(nPos) == STRINGCHAR(IDS_HEXFINDDIALOG_QUERY_AND) || szValue.GetAt(nPos) == STRINGCHAR(IDS_HEXFINDDIALOG_QUERY_OR))
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
		GetDlgItem(IDC_HEX_FIND_VALUE)->SetFocus();
		CAudioDevice::AlertBySound();
		return;
	}
}

void CHEXFindDialog::OnOpen()
{
	INT  nDump[2];
	INT  nDumps[2];
	INT  nPacket[2];
	INT  nPackets[2];
	CString  szTitle[2];
	CMemoryDump  *pDump;
	CDatabaseTMPacket  *pDatabaseTMPacket;
	CHourglassCursor  cCursor;

	if (m_nType == HEX_TYPE_NORMAL)
	{
		for (nPacket[0] = 0, nPackets[0] = (INT)m_pPackets.GetSize(), szTitle[0] = Listbox_GetText(GetDlgItem(IDC_HEX_FIND_RESULTS), (INT)SendDlgItemMessage(IDC_HEX_FIND_RESULTS, LB_GETCURSEL)); nPacket[0] < nPackets[0]; nPacket[0]++)
		{
			szTitle[1].Format(STRING(IDS_HEXFINDDIALOG_RESULT_FORMAT), (LPCTSTR)m_pPackets.GetAt(nPacket[0])->GetDescription(), (LPCTSTR)m_pPackets.GetAt(nPacket[0])->GetTag());
			if (szTitle[0] == szTitle[1]) break;
		}
		for (nPacket[1] = 0, nPackets[1] = (nPacket[0] < nPackets[0]) ? nPacket[0] : nPackets[0]; nPacket[1] < nPackets[1]; nPacket[1]++)
		{
			if ((pDatabaseTMPacket = m_pPackets.GetAt(0))) delete pDatabaseTMPacket;
			m_pPackets.RemoveAt(0);
		}
		for (nPacket[1] = 1, nPackets[1] = (nPacket[0] < nPackets[0]) ? (INT)m_pPackets.GetSize() : 0; nPacket[1] < nPackets[1]; nPacket[1]++)
		{
			if ((pDatabaseTMPacket = m_pPackets.GetAt(1))) delete pDatabaseTMPacket;
			m_pPackets.RemoveAt(1);
		}
	}
	if (m_nType == HEX_TYPE_DUMPS)
	{
		for (nDump[0] = 0, nDumps[0] = (INT)m_pDumps.GetSize(), szTitle[0] = Listbox_GetText(GetDlgItem(IDC_HEX_FIND_RESULTS), (INT)SendDlgItemMessage(IDC_HEX_FIND_RESULTS, LB_GETCURSEL)); nDump[0] < nDumps[0]; nDump[0]++)
		{
			if (szTitle[0] == m_pDumps.GetAt(nDump[0])->GetName()) break;
			continue;
		}
		for (nDump[1] = 0, nDumps[1] = (nDump[0] < nDumps[0]) ? nDump[0] : nDumps[0]; nDump[1] < nDumps[1]; nDump[1]++)
		{
			if ((pDump = m_pDumps.GetAt(0))) delete pDump;
			m_pDumps.RemoveAt(0);
		}
		for (nDump[1] = 1, nDumps[1] = (nDump[0] < nDumps[0]) ? (INT)m_pDumps.GetSize() : 0; nDump[1] < nDumps[1]; nDump[1]++)
		{
			if ((pDump = m_pDumps.GetAt(1))) delete pDump;
			m_pDumps.RemoveAt(1);
		}
	}
	EndDialog(IDOK);
}

void CHEXFindDialog::OnSelchangeKey()
{
	EnumSearchValues();
	GetDlgItem(IDC_HEX_FIND_SEARCH)->EnableWindow(FALSE);
	GetDlgItem(IDC_HEX_FIND_VALUE)->SetFocus();
}

void CHEXFindDialog::OnSelchangeValue()
{
	GetDlgItem(IDC_HEX_FIND_SEARCH)->EnableWindow((SendDlgItemMessage(IDC_HEX_FIND_VALUE, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
}

void CHEXFindDialog::OnSelchangeResult()
{
	GetDlgItem(IDC_HEX_FIND_OPEN)->EnableWindow();
}

void CHEXFindDialog::OnEditchangeValue()
{
	GetDlgItem(IDC_HEX_FIND_SEARCH)->EnableWindow((GetDlgItem(IDC_HEX_FIND_VALUE)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

void CHEXFindDialog::OnOK()
{
	CHourglassCursor  cCursor;

	m_pDumps.RemoveAll();
	m_pPackets.RemoveAll();
	CDisplayDialog::OnOK();
}

BOOL CHEXFindDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_HEXFINDDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CHEXFindDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_HEXFINDDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CHEXOpenDialog dialog

IMPLEMENT_DYNCREATE(CHEXOpenDialog, CDisplayDialog)

CHEXOpenDialog::CHEXOpenDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CHEXOpenDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CHEXOpenDialog::Initialize()
{
	m_nRetrieveMode = 0;
	m_nRetrieveSpeed = 0;
	m_tRetrieveStartTime = 0;
	m_tRetrieveStopTime = 0;
	m_tRetrieveInterval = 0;
	m_nLayoutEnum[0] = 0;
	m_nLayoutEnum[1] = 0;
	m_nLayoutLineLength = 0;
	m_bLayoutBadData = FALSE;
	ZeroMemory(&m_fntLayoutTitle, sizeof(LOGFONT));
	ZeroMemory(&m_fntLayoutData, sizeof(LOGFONT));
	ZeroMemory(&m_fntLayoutSpy[0], sizeof(LOGFONT));
	ZeroMemory(&m_fntLayoutSpy[1], sizeof(LOGFONT));
	return TRUE;
}

INT CHEXOpenDialog::Create(CWnd *pParentWnd)
{
	return CDisplayDialog::Create(pParentWnd, CHEXOpenDialog::IDD);
}

CString CHEXOpenDialog::GetTitle() CONST
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szDisplay[2];
	CDatabaseTMPacket  *pDatabaseTMPacket;

	if (GetType() == HEX_TYPE_NORMAL)
	{
		GetDlgItem(IDC_HEX_OPEN_DISPLAY)->GetWindowText(szDisplay[0]);
		for (nDisplay = 0, nDisplays = (INT)GetDatabase()->GetTMPackets()->GetSize(); nDisplay < nDisplays; nDisplay++)
		{
			if ((pDatabaseTMPacket = GetDatabase()->GetTMPackets()->GetAt(nDisplay)) != (CDatabaseTMPacket *)NULL)
			{
				szDisplay[1].Format(STRING(IDS_HEXOPENDIALOG_TITLE), (LPCTSTR)pDatabaseTMPacket->GetDescription(), (LPCTSTR)pDatabaseTMPacket->GetTag());
				if (!szDisplay[0].CompareNoCase(szDisplay[1]) || !szDisplay[0].CompareNoCase(pDatabaseTMPacket->GetDescription()) || !szDisplay[0].CompareNoCase(pDatabaseTMPacket->GetTag())) break;
			}
		}
		if (nDisplay < nDisplays)
		{
			szDisplay[0].Format(STRING(IDS_WINDOW_FULLTITLE), STRING(IDS_DISPLAY_TITLE_HEX), (LPCTSTR)pDatabaseTMPacket->GetDescription());
			return szDisplay[0];
		}
	}
	if (GetType() == HEX_TYPE_STREAM)
	{
		szDisplay[0].Format(STRING(IDS_WINDOW_FULLTITLE), STRING(IDS_DISPLAY_TITLE_HEX), STRING(IDS_HEXOPENDIALOG_SPECIALTITLE));
		return szDisplay[0];
	}
	if (GetType() == HEX_TYPE_DUMPS)
	{
		GetDlgItem(IDC_HEX_OPEN_DISPLAY)->GetWindowText(szDisplay[0]);
		szDisplay[1].Format(STRING(IDS_WINDOW_FULLTITLE), STRING(IDS_DISPLAY_TITLE_HEX), (LPCTSTR)szDisplay[0]);
		return szDisplay[1];
	}
	return STRING(IDS_HEXOPENDIALOG_TITLE);
}

UINT CHEXOpenDialog::GetType() CONST
{
	return((IsDlgButtonChecked(IDC_HEX_OPEN_TYPE_NORMAL) || IsDlgButtonChecked(IDC_HEX_OPEN_TYPE_STREAM) || IsDlgButtonChecked(IDC_HEX_OPEN_TYPE_DUMPS)) ? ((IsDlgButtonChecked(IDC_HEX_OPEN_TYPE_NORMAL)) ? HEX_TYPE_NORMAL : ((IsDlgButtonChecked(IDC_HEX_OPEN_TYPE_STREAM)) ? HEX_TYPE_STREAM : HEX_TYPE_DUMPS)) : -1);
}

UINT CHEXOpenDialog::GetMode() CONST
{
	return((IsDlgButtonChecked(IDC_HEX_OPEN_MODE_REALTIME) || IsDlgButtonChecked(IDC_HEX_OPEN_MODE_HISTORY)) ? (IsDlgButtonChecked(IDC_HEX_OPEN_MODE_REALTIME)*DISPLAY_MODE_REALTIME + IsDlgButtonChecked(IDC_HEX_OPEN_MODE_HISTORY)*DISPLAY_MODE_HISTORY) : -1);
}

BOOL CHEXOpenDialog::GetLayout(CString &szLayout, CMemoryDump &cLayout) CONST
{
	INT  nDump;
	INT  nDumps;
	INT  nDisplay;
	INT  nDisplays;
	CString  szDisplay[2];
	CMemoryDump  *pDump;
	CMemoryDumps  pDumps;
	CDatabaseTMPacket  *pDatabaseTMPacket;

	if (GetType() == HEX_TYPE_NORMAL)
	{
		GetDlgItem(IDC_HEX_OPEN_DISPLAY)->GetWindowText(szDisplay[0]);
		for (nDisplay = 0, nDisplays = (INT)GetDatabase()->GetTMPackets()->GetSize(); nDisplay < nDisplays; nDisplay++)
		{
			if ((pDatabaseTMPacket = GetDatabase()->GetTMPackets()->GetAt(nDisplay)) != (CDatabaseTMPacket *)NULL)
			{
				szDisplay[1].Format(STRING(IDS_HEXOPENDIALOG_TITLE), (LPCTSTR)pDatabaseTMPacket->GetDescription(), (LPCTSTR)pDatabaseTMPacket->GetTag());
				if (!szDisplay[0].CompareNoCase(szDisplay[1]) || !szDisplay[0].CompareNoCase(pDatabaseTMPacket->GetDescription()) || !szDisplay[0].CompareNoCase(pDatabaseTMPacket->GetTag())) break;
			}
		}
		if (nDisplay < nDisplays)
		{
			szLayout = pDatabaseTMPacket->GetTag();
			cLayout.Empty();
			return TRUE;
		}
	}
	if (GetType() == HEX_TYPE_STREAM)
	{
		szLayout = STRING(IDS_HEXOPENDIALOG_SPECIALTITLE);
		cLayout.Empty();
		return TRUE;
	}
	if (GetType() == HEX_TYPE_DUMPS)
	{
		GetDlgItem(IDC_HEX_OPEN_DISPLAY)->GetWindowText(szDisplay[0]);
		for (nDump = 0, nDumps = (GetMemoryDumpsService()->GetMemoryDumps(pDumps)) ? (INT)pDumps.GetSize() : -1; nDump < nDumps; nDump++)
		{
			if ((pDump = (CMemoryDump *)pDumps.GetAt(nDump)) != (CMemoryDump *)NULL)
			{
				for (szDisplay[1].Format(STRING(IDS_HEXOPENDIALOG_NORMALDUMP), (LPCTSTR)pDump->GetName()); !szDisplay[0].Compare(szDisplay[1]); )
				{
					pDump->SetArchivingFileFormats(MEMORYDUMP_FILEFORMAT_NORMAL);
					szLayout = szDisplay[0];
					cLayout.Copy(pDump);
					return TRUE;
				}
				for (szDisplay[1].Format(STRING(IDS_HEXOPENDIALOG_DESCRIPTIVEDUMP), (LPCTSTR)pDump->GetName()); !szDisplay[0].Compare(szDisplay[1]); )
				{
					pDump->SetArchivingFileFormats(MEMORYDUMP_FILEFORMAT_DESCRIPTIVE);
					szLayout = szDisplay[0];
					cLayout.Copy(pDump);
					return TRUE;
				}
				for (szDisplay[1].Format(STRING(IDS_HEXOPENDIALOG_DELIMITEDDUMP), (LPCTSTR)pDump->GetName()); !szDisplay[0].Compare(szDisplay[1]); )
				{
					pDump->SetArchivingFileFormats(MEMORYDUMP_FILEFORMAT_DELIMITED);
					szLayout = szDisplay[0];
					cLayout.Copy(pDump);
					return TRUE;
				}
			}
		}
		return((nDump < nDumps) ? TRUE : FALSE);
	}
	return FALSE;
}

BOOL CHEXOpenDialog::GetLayoutFormat(UINT &nHorzEnum, UINT &nVertEnum, UINT &nLineLength, CUIntArray &nColors) CONST
{
	if (IsLayoutModified())
	{
		nHorzEnum = m_nLayoutEnum[0];
		nVertEnum = m_nLayoutEnum[1];
		nLineLength = m_nLayoutLineLength;
		nColors.Copy(m_nLayoutColors);
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXOpenDialog::GetLayoutTitleFont(LPLOGFONT pTitleFont) CONST
{
	if (IsLayoutModified())
	{
		CopyMemory(pTitleFont, &m_fntLayoutTitle, sizeof(LOGFONT));
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXOpenDialog::GetLayoutDataFont(LPLOGFONT pDataFont) CONST
{
	if (IsLayoutModified())
	{
		CopyMemory(pDataFont, &m_fntLayoutData, sizeof(LOGFONT));
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXOpenDialog::GetLayoutSpyFont(LPLOGFONT pHeaderFont, LPLOGFONT pLocationsFont) CONST
{
	if (IsLayoutModified())
	{
		CopyMemory(pHeaderFont, &m_fntLayoutSpy[0], sizeof(LOGFONT));
		CopyMemory(pLocationsFont, &m_fntLayoutSpy[1], sizeof(LOGFONT));
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXOpenDialog::GetLayoutBadDataMode(BOOL &bEnable) CONST
{
	if (IsLayoutModified())
	{
		bEnable = m_bLayoutBadData;
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXOpenDialog::IsLayoutModified() CONST
{
	LOGFONT  fntSample = { 0 };

	return((m_nLayoutEnum[0] > 0 || m_nLayoutEnum[1] > 0 || m_nLayoutLineLength > 0 || m_nLayoutColors.GetSize() > 0 || memcmp(&m_fntLayoutTitle, &fntSample, sizeof(LOGFONT)) || memcmp(&m_fntLayoutData, &fntSample, sizeof(LOGFONT)) || memcmp(&m_fntLayoutSpy[0], &fntSample, sizeof(LOGFONT)) || memcmp(&m_fntLayoutSpy[1], &fntSample, sizeof(LOGFONT)) || m_bLayoutBadData) ? TRUE : FALSE);
}

BOOL CHEXOpenDialog::GetSpyLocations(CHEXSpyLocations &pSpyLocations) CONST
{
	return((IsContentsModified()) ? pSpyLocations.Copy(&m_pSpyLocations) : FALSE);
}

BOOL CHEXOpenDialog::IsContentsModified() CONST
{
	return((m_pSpyLocations.GetSize() > 0) ? TRUE : FALSE);
}

BOOL CHEXOpenDialog::GetRetrieveMode(UINT &nMode) CONST
{
	nMode = m_nRetrieveMode;
	return TRUE;
}

BOOL CHEXOpenDialog::GetRetrieveSpeed(UINT &nSpeed) CONST
{
	nSpeed = m_nRetrieveSpeed;
	return((m_nRetrieveMode & HEX_RETRIEVE_AUTOFORWARD) ? TRUE : FALSE);
}

BOOL CHEXOpenDialog::GetRetrieveInterval(CTimeSpan &tInterval) CONST
{
	tInterval = m_tRetrieveInterval;
	return(((m_nRetrieveMode & HEX_RETRIEVE_AUTOFORWARD) || (m_nRetrieveMode & HEX_RETRIEVE_MANUALFORWARD)) ? TRUE : FALSE);
}

BOOL CHEXOpenDialog::GetRetrieveStartTime(CTimeKey &tTimeKey) CONST
{
	tTimeKey = m_tRetrieveStartTime;
	return(((m_nRetrieveMode & HEX_RETRIEVE_AUTOFORWARD) || (m_nRetrieveMode & HEX_RETRIEVE_PSEUDOREALTIME) || (m_nRetrieveMode & HEX_RETRIEVE_MANUALFORWARD)) ? TRUE : FALSE);
}

BOOL CHEXOpenDialog::GetRetrieveStopTime(CTimeKey &tTimeKey) CONST
{
	tTimeKey = m_tRetrieveStopTime;
	return((((m_nRetrieveMode & HEX_RETRIEVE_AUTOFORWARD) || (m_nRetrieveMode & HEX_RETRIEVE_PSEUDOREALTIME) || (m_nRetrieveMode & HEX_RETRIEVE_MANUALFORWARD)) && (m_nRetrieveMode & HEX_RETRIEVE_STOPBYTIME)) ? TRUE : FALSE);
}

BOOL CHEXOpenDialog::GetRetrieveFileName(CString &szFileName) CONST
{
	szFileName = ((m_nRetrieveMode & HEX_RETRIEVE_AUTOFORWARD) || (m_nRetrieveMode & HEX_RETRIEVE_PSEUDOREALTIME) || (m_nRetrieveMode & HEX_RETRIEVE_MANUALFORWARD)) ? (LPCTSTR)m_szRetrieveFileName : EMPTYSTRING;
	return !szFileName.IsEmpty();
}

BOOL CHEXOpenDialog::IsRetrievingModified() CONST
{
	return((m_nRetrieveMode != 0) ? TRUE : FALSE);
}

BOOL CHEXOpenDialog::GetPrintJobs(CHEXPrintJobs &pPrintJobs) CONST
{
	CByteArray  nPrintInfo;

	return((IsPrintingModified()) ? pPrintJobs.Copy(&m_pPrintJobs) : pPrintJobs.Unmap(nPrintInfo));
}

BOOL CHEXOpenDialog::IsPrintingModified() CONST
{
	return((m_pPrintJobs.GetSize() > 0) ? TRUE : FALSE);
}

CHEXWnd *CHEXOpenDialog::GetParent() CONST
{
	return((CHEXWnd *)CDisplayDialog::GetParent());
}

VOID CHEXOpenDialog::EnumLayouts()
{
	INT  nDisplay;
	INT  nDisplays;
	UINT  nFormats;
	CString  szLayout;
	CString  szDisplay;
	CMemoryDump  *pDump;
	CMemoryDumps  pDumps;
	CDatabaseTMPacket  *pDatabaseTMPacket;

	if (IsDlgButtonChecked(IDC_HEX_OPEN_TYPE_NORMAL) || IsDlgButtonChecked(IDC_HEX_OPEN_TYPE_STREAM))
	{
		for (nDisplay = 0, nDisplays = (IsDlgButtonChecked(IDC_HEX_OPEN_TYPE_NORMAL)) ? (INT)GetDatabase()->GetTMPackets()->GetSize() : 0, SendDlgItemMessage(IDC_HEX_OPEN_DISPLAY, CB_RESETCONTENT); nDisplay < nDisplays; nDisplay++)
		{
			if ((pDatabaseTMPacket = GetDatabase()->GetTMPackets()->GetAt(nDisplay)) != (CDatabaseTMPacket *)NULL)
			{
				szDisplay.Format(STRING(IDS_HEXOPENDIALOG_TITLE), (LPCTSTR)pDatabaseTMPacket->GetDescription(), (LPCTSTR)pDatabaseTMPacket->GetTag());
				SendDlgItemMessage(IDC_HEX_OPEN_DISPLAY, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szDisplay);
			}
		}
	}
	if (IsDlgButtonChecked(IDC_HEX_OPEN_TYPE_DUMPS))
	{
		for (nDisplay = 0, nDisplays = (GetMemoryDumpsService()->GetMemoryDumps(pDumps)) ? (INT)pDumps.GetSize() : 0, SendDlgItemMessage(IDC_HEX_OPEN_DISPLAY, CB_RESETCONTENT); nDisplay < nDisplays; nDisplay++)
		{
			if ((pDump = (CMemoryDump *)pDumps.GetAt(nDisplay)) != (CMemoryDump *)NULL)
			{
				if ((nFormats = pDump->GetArchivingFileFormats()) & MEMORYDUMP_FILEFORMAT_NORMAL)
				{
					szDisplay.Format(STRING(IDS_HEXOPENDIALOG_NORMALDUMP), (LPCTSTR)pDump->GetName());
					SendDlgItemMessage(IDC_HEX_OPEN_DISPLAY, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szDisplay);
				}
				if (nFormats & MEMORYDUMP_FILEFORMAT_DESCRIPTIVE)
				{
					szDisplay.Format(STRING(IDS_HEXOPENDIALOG_DESCRIPTIVEDUMP), (LPCTSTR)pDump->GetName());
					SendDlgItemMessage(IDC_HEX_OPEN_DISPLAY, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szDisplay);
				}
				if (nFormats & MEMORYDUMP_FILEFORMAT_DELIMITED)
				{
					szDisplay.Format(STRING(IDS_HEXOPENDIALOG_DELIMITEDDUMP), (LPCTSTR)pDump->GetName());
					SendDlgItemMessage(IDC_HEX_OPEN_DISPLAY, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szDisplay);
				}
			}
		}
	}
	GetDlgItem(IDC_HEX_OPEN_DISPLAY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_HEX_OPEN_DISPLAY, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_HEX_OPEN_DISPLAY)->EnableWindow((SendDlgItemMessage(IDC_HEX_OPEN_DISPLAY, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_HEX_OPEN_FIND)->EnableWindow((SendDlgItemMessage(IDC_HEX_OPEN_DISPLAY, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_HEX_OPEN_SETTINGS)->EnableWindow((FindLayout(szLayout) && (GetMode() != DISPLAY_MODE_REALTIME || !GetParent()->Find(MAKELONG(DISPLAY_TYPE_HEX, GetType()), GetMode(), szLayout))) ? TRUE : FALSE);
}

BOOL CHEXOpenDialog::FindLayout() CONST
{
	CString  szLayout;

	return FindLayout(szLayout);
}
BOOL CHEXOpenDialog::FindLayout(CString &szLayout) CONST
{
	CMemoryDump  cLayout;

	return GetLayout(szLayout, cLayout);
}

BOOL CHEXOpenDialog::Check(BOOL bModified) CONST
{
	CString  szLayout;

	return(((IsDlgButtonChecked(IDC_HEX_OPEN_MODE_REALTIME) || IsDlgButtonChecked(IDC_HEX_OPEN_MODE_HISTORY)) && FindLayout(szLayout) && (IsDlgButtonChecked(IDC_HEX_OPEN_MODE_REALTIME) || IsRetrievingModified())) ? TRUE : FALSE);
}

void CHEXOpenDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHEXOpenDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CHEXOpenDialog::PostNcDestroy()
{
	m_pPrintJobs.RemoveAll();
	m_pSpyLocations.RemoveAll();
	m_nLayoutColors.RemoveAll();
	CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CHEXOpenDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CHEXOpenDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_HEX_OPEN_SETTINGS, OnSettings)
	ON_BN_CLICKED(IDC_HEX_OPEN_FIND, OnFind)
	ON_BN_CLICKED(IDC_HEX_OPEN_TYPE_NORMAL, OnTypeNormal)
	ON_BN_CLICKED(IDC_HEX_OPEN_TYPE_STREAM, OnTypeStream)
	ON_BN_CLICKED(IDC_HEX_OPEN_TYPE_DUMPS, OnTypeDumps)
	ON_BN_CLICKED(IDC_HEX_OPEN_MODE_REALTIME, OnRealtimeMode)
	ON_BN_CLICKED(IDC_HEX_OPEN_MODE_HISTORY, OnHistoryMode)
	ON_BN_CLICKED(IDC_HEX_OPEN_HELP, OnHelp)
	ON_CBN_EDITCHANGE(IDC_HEX_OPEN_DISPLAY, OnEditchangeTitle)
	ON_CBN_SELCHANGE(IDC_HEX_OPEN_DISPLAY, OnSelchangeTitle)
	ON_CBN_DBLCLK(IDC_HEX_OPEN_DISPLAY, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHEXOpenDialog message handlers

BOOL CHEXOpenDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	CheckRadioButton(IDC_HEX_OPEN_TYPE_NORMAL, IDC_HEX_OPEN_TYPE_DUMPS, IDC_HEX_OPEN_TYPE_NORMAL);
	CheckDlgButton(IDC_HEX_OPEN_MODE_REALTIME, TRUE);
	CheckDlgButton(IDC_HEX_OPEN_MODE_HISTORY, FALSE);
	GetDlgItem(IDC_HEX_OPEN_DETAILS)->EnableWindow();
	GetDlgItem(IDC_HEX_OPEN_TYPE)->EnableWindow();
	GetDlgItem(IDC_HEX_OPEN_TYPE_NORMAL)->EnableWindow();
	GetDlgItem(IDC_HEX_OPEN_TYPE_STREAM)->EnableWindow();
	GetDlgItem(IDC_HEX_OPEN_TYPE_DUMPS)->EnableWindow();
	GetDlgItem(IDC_HEX_OPEN_MODE)->EnableWindow();
	GetDlgItem(IDC_HEX_OPEN_MODE_REALTIME)->EnableWindow();
	GetDlgItem(IDC_HEX_OPEN_MODE_HISTORY)->EnableWindow(CheckAccountPrivilege(PRIVILEGE_OFFLINE_OPERATE));
	EnumLayouts();
	return TRUE;
}

void CHEXOpenDialog::OnSettings()
{
	ReportEvent((m_dlgSettings.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CHEXOpenDialog::OnFind()
{
	INT  nResult;
	CString  szLayout;

	if ((nResult = m_dlgFindDisplay.Create(this, (IsDlgButtonChecked(IDC_HEX_OPEN_TYPE_NORMAL)) ? HEX_TYPE_NORMAL : ((IsDlgButtonChecked(IDC_HEX_OPEN_TYPE_STREAM)) ? HEX_TYPE_STREAM : ((IsDlgButtonChecked(IDC_HEX_OPEN_TYPE_DUMPS)) ? HEX_TYPE_DUMPS : 0)), szLayout)) == IDOK)
	{
		GetDlgItem(IDC_HEX_OPEN_SETTINGS)->EnableWindow((SendDlgItemMessage(IDC_HEX_OPEN_DISPLAY, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_HEX_OPEN_DISPLAY, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szLayout)) >= 0 && (GetMode() != DISPLAY_MODE_REALTIME || !GetParent()->Find(MAKELONG(DISPLAY_TYPE_HEX, GetType()), GetMode(), szLayout))) ? TRUE : FALSE);
		GetDlgItem(IDC_HEX_OPEN_DISPLAY)->SetFocus();
	}
	ReportEvent((nResult <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXOpenDialog::OnEditchangeTitle()
{
	CString  szLayout;

	GetDlgItem(IDC_HEX_OPEN_SETTINGS)->EnableWindow((FindLayout(szLayout) && (GetMode() != DISPLAY_MODE_REALTIME || !GetParent()->Find(MAKELONG(DISPLAY_TYPE_HEX, GetType()), GetMode(), szLayout))) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXOpenDialog::OnSelchangeTitle()
{
	CString  szLayout;

	SendDlgItemMessage(IDC_HEX_OPEN_DISPLAY, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_HEX_OPEN_DISPLAY, CB_GETCURSEL));
	GetDlgItem(IDC_HEX_OPEN_SETTINGS)->EnableWindow((FindLayout(szLayout) && (GetMode() != DISPLAY_MODE_REALTIME || !GetParent()->Find(MAKELONG(DISPLAY_TYPE_HEX, GetType()), GetMode(), szLayout))) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXOpenDialog::OnTypeNormal()
{
	EnumLayouts();
	GetDlgItem(IDC_HEX_OPEN_DISPLAY)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXOpenDialog::OnTypeStream()
{
	EnumLayouts();
	GetDlgItem(IDC_HEX_OPEN_DISPLAY)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXOpenDialog::OnTypeDumps()
{
	EnumLayouts();
	GetDlgItem(IDC_HEX_OPEN_DISPLAY)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXOpenDialog::OnRealtimeMode()
{
	CString  szLayout;

	GetDlgItem(IDC_HEX_OPEN_SETTINGS)->EnableWindow((FindLayout(szLayout) && (GetMode() != DISPLAY_MODE_REALTIME || !GetParent()->Find(MAKELONG(DISPLAY_TYPE_HEX, GetType()), GetMode(), szLayout))) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CHEXOpenDialog::OnHistoryMode()
{
	INT  nPos;
	CString  szType;
	CString  szTitle;
	CString  szLayout;
	CMemoryDump  cLayout;
	CDatabaseTMPacket  *pDatabaseTMPacket;

	if (GetType() == HEX_TYPE_NORMAL)
	{
		for (szTitle = ((pDatabaseTMPacket = (GetLayout(szLayout, cLayout)) ? GetDatabase()->GetTMPackets()->GetAt(GetDatabase()->GetTMPackets()->Find(szLayout)) : (CDatabaseTMPacket *)NULL) && !pDatabaseTMPacket->GetDescription().IsEmpty()) ? pDatabaseTMPacket->GetDescription() : STRING(IDS_WINDOW_UNKNOWNTITLE), szType.Format(STRING(IDS_HEXOPENDIALOG_TYPENORMAL), (LPCTSTR)szLayout), szType = ((nPos = (szLayout.IsEmpty()) ? szType.Find(SPACE) : -1) >= 0) ? szType.Left(nPos) : szType; IsDlgButtonChecked(IDC_HEX_OPEN_MODE_HISTORY); )
		{
			ReportEvent((m_dlgRetrievals.Create(this, szTitle, szType) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
			break;
		}
		for (GetDlgItem(IDC_HEX_OPEN_SETTINGS)->EnableWindow((FindLayout(szLayout) && (GetMode() != DISPLAY_MODE_REALTIME || !GetParent()->Find(MAKELONG(DISPLAY_TYPE_HEX, GetType()), GetMode(), szLayout))) ? TRUE : FALSE); SendDlgItemMessage(IDC_HEX_OPEN_DISPLAY, CB_GETCOUNT) > 0; )
		{
			GetDlgItem(IDC_HEX_OPEN_DISPLAY)->SetFocus();
			break;
		}
		for (; IsDlgButtonChecked(IDC_HEX_OPEN_MODE_REALTIME); )
		{
			GetDlgItem(IDC_HEX_OPEN_MODE_REALTIME)->SetFocus();
			break;
		}
		return;
	}
	if (GetType() == HEX_TYPE_STREAM)
	{
		for (szTitle = (GetLayout(szLayout, cLayout)) ? szLayout : STRING(IDS_WINDOW_UNKNOWNTITLE), szType = STRING(IDS_HEXOPENDIALOG_TYPESTREAM); IsDlgButtonChecked(IDC_HEX_OPEN_MODE_HISTORY); )
		{
			ReportEvent((m_dlgRetrievals.Create(this, szTitle, szType) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
			break;
		}
		for (GetDlgItem(IDC_HEX_OPEN_SETTINGS)->EnableWindow((FindLayout(szLayout) && (GetMode() != DISPLAY_MODE_REALTIME || !GetParent()->Find(MAKELONG(DISPLAY_TYPE_HEX, GetType()), GetMode(), szLayout))) ? TRUE : FALSE); SendDlgItemMessage(IDC_HEX_OPEN_DISPLAY, CB_GETCOUNT) > 0; )
		{
			GetDlgItem(IDC_HEX_OPEN_DISPLAY)->SetFocus();
			break;
		}
		for (; IsDlgButtonChecked(IDC_HEX_OPEN_MODE_REALTIME); )
		{
			GetDlgItem(IDC_HEX_OPEN_MODE_REALTIME)->SetFocus();
			break;
		}
		return;
	}
	if (GetType() == HEX_TYPE_DUMPS)
	{
		for (szTitle = (GetLayout(szLayout, cLayout)) ? szLayout : STRING(IDS_WINDOW_UNKNOWNTITLE), szType = STRING(IDS_HEXOPENDIALOG_TYPEDUMPS); IsDlgButtonChecked(IDC_HEX_OPEN_MODE_HISTORY); )
		{
			ReportEvent((m_dlgRetrievals.Create(this, szTitle, szType) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
			break;
		}
		for (GetDlgItem(IDC_HEX_OPEN_SETTINGS)->EnableWindow((FindLayout(szLayout) && (GetMode() != DISPLAY_MODE_REALTIME || !GetParent()->Find(MAKELONG(DISPLAY_TYPE_HEX, GetType()), GetMode(), szLayout))) ? TRUE : FALSE); SendDlgItemMessage(IDC_HEX_OPEN_DISPLAY, CB_GETCOUNT) > 0; )
		{
			GetDlgItem(IDC_HEX_OPEN_DISPLAY)->SetFocus();
			break;
		}
		for (; IsDlgButtonChecked(IDC_HEX_OPEN_MODE_REALTIME); )
		{
			GetDlgItem(IDC_HEX_OPEN_MODE_REALTIME)->SetFocus();
			break;
		}
		return;
	}
	CheckDlgButton(IDC_HEX_OPEN_MODE_REALTIME, TRUE);
	CheckDlgButton(IDC_HEX_OPEN_MODE_HISTORY, FALSE);
	for (GetDlgItem(IDC_HEX_OPEN_SETTINGS)->EnableWindow((FindLayout(szLayout) && (GetMode() != DISPLAY_MODE_REALTIME || !GetParent()->Find(MAKELONG(DISPLAY_TYPE_HEX, GetType()), GetMode(), szLayout))) ? TRUE : FALSE); SendDlgItemMessage(IDC_HEX_OPEN_DISPLAY, CB_GETCOUNT) > 0; )
	{
		GetDlgItem(IDC_HEX_OPEN_DISPLAY)->SetFocus();
		break;
	}
	for (; IsDlgButtonChecked(IDC_HEX_OPEN_MODE_REALTIME); )
	{
		GetDlgItem(IDC_HEX_OPEN_MODE_REALTIME)->SetFocus();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

BOOL CHEXOpenDialog::OnCloseSettingsDialog(UINT nCode)
{
	if (nCode == IDOK)
	{
		if (m_dlgSettings.IsLayoutModified())
		{
			m_dlgSettings.GetLayoutFormat(m_nLayoutEnum[0], m_nLayoutEnum[1], m_nLayoutLineLength, m_nLayoutColors);
			m_dlgSettings.GetLayoutTitleFont(&m_fntLayoutTitle);
			m_dlgSettings.GetLayoutDataFont(&m_fntLayoutData);
			m_dlgSettings.GetLayoutSpyFont(&m_fntLayoutSpy[0], &m_fntLayoutSpy[1]);
			m_dlgSettings.GetLayoutBadDataMode(m_bLayoutBadData);
		}
		if (m_dlgSettings.IsContentsModified()) m_dlgSettings.GetSpyLocations(m_pSpyLocations);
		if (m_dlgSettings.IsRetrievingModified()) m_dlgSettings.GetRetrieveFileName(m_szRetrieveFileName);
		if (m_dlgSettings.IsPrintingModified()) m_dlgSettings.GetPrintJobs(m_pPrintJobs);
	}
	return TRUE;
}

BOOL CHEXOpenDialog::OnCloseRetrieveDialog(UINT nCode)
{
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
		CheckDlgButton(IDC_HEX_OPEN_MODE_REALTIME, TRUE);
		CheckDlgButton(IDC_HEX_OPEN_MODE_HISTORY, FALSE);
	}
	return TRUE;
}

void CHEXOpenDialog::OnOK()
{
	CString  szLayout;
	CHEXWnd  *pHEXWnd[2];
	CHourglassCursor  cCursor;

	if ((pHEXWnd[0] = GetParent()))
	{
		if (GetMode() == DISPLAY_MODE_REALTIME)
		{
			if ((pHEXWnd[1] = (FindLayout(szLayout)) ? pHEXWnd[0]->Find(MAKELONG(DISPLAY_TYPE_HEX, GetType()), GetMode(), szLayout) : (CHEXWnd *)NULL))
			{
				GetDisplayArea()->ActivateDisplay(pHEXWnd[1]);
				EndDialog(IDCANCEL);
				return;
			}
		}
		if (!pHEXWnd[0]->OnCloseOpenDialog(IDOK))
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

void CHEXOpenDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	GetParent()->OnCloseOpenDialog(IDCANCEL);
	CDisplayDialog::OnCancel();
}

BOOL CHEXOpenDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_HEXOPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CHEXOpenDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_HEXOPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CHEXRetrieveThread

IMPLEMENT_DYNCREATE(CHEXRetrieveThread, CThread)

CHEXRetrieveThread::CHEXRetrieveThread() : CThread()
{
	m_nMode = 0;
	m_nSpeed = 0;
	m_tInterval = 0;
	m_tStartTime = 0;
	m_tStopTime = 0;
	m_bInit = (HANDLE)NULL;
	m_pbFlag = (LPLONG)NULL;
	m_hAction[HEXRETRIEVETHREAD_ACTION_STOP] = (HANDLE)NULL;
	m_hAction[HEXRETRIEVETHREAD_ACTION_AUTOFORWARD] = (HANDLE)NULL;
	m_hAction[HEXRETRIEVETHREAD_ACTION_AUTOBACKWARD] = (HANDLE)NULL;
	m_hAction[HEXRETRIEVETHREAD_ACTION_MANUALFORWARD] = (HANDLE)NULL;
	m_hAction[HEXRETRIEVETHREAD_ACTION_MANUALBACKWARD] = (HANDLE)NULL;
	m_hAction[HEXRETRIEVETHREAD_ACTION_PSEUDOREALTIME] = (HANDLE)NULL;
}

BOOL CHEXRetrieveThread::Start(CHEXWnd *pParentWnd, HANDLE bInit, LPCTSTR pszFileName, UINT nMode, UINT nSpeed, CONST CTimeSpan &tInterval, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, LONG *pbFlag, HANDLE bRetrieveStop, HANDLE bRetrieveAutoForward, HANDLE bRetrieveAutoBackward, HANDLE bRetrieveManualForward, HANDLE bRetrieveManualBackward, HANDLE bRetrievePseudoRealtime)
{
	m_bInit = bInit;
	m_nMode = nMode;
	m_nSpeed = nSpeed;
	m_pbFlag = pbFlag;
	m_tInterval = tInterval;
	m_tStartTime = tStartTime;
	m_tStopTime = tStopTime;
	m_szFileName = pszFileName;
	m_hAction[HEXRETRIEVETHREAD_ACTION_STOP] = bRetrieveStop;
	m_hAction[HEXRETRIEVETHREAD_ACTION_AUTOFORWARD] = bRetrieveAutoForward;
	m_hAction[HEXRETRIEVETHREAD_ACTION_AUTOBACKWARD] = bRetrieveAutoBackward;
	m_hAction[HEXRETRIEVETHREAD_ACTION_MANUALFORWARD] = bRetrieveManualForward;
	m_hAction[HEXRETRIEVETHREAD_ACTION_MANUALBACKWARD] = bRetrieveManualBackward;
	m_hAction[HEXRETRIEVETHREAD_ACTION_PSEUDOREALTIME] = bRetrievePseudoRealtime;
	return((ResetEvent(bInit)) ? CreateThread(pParentWnd, THREAD_PRIORITY_BELOW_NORMAL) : FALSE);
}

BOOL CHEXRetrieveThread::Stop()
{
	return((DestroyThread() >= 0) ? TRUE : FALSE);
}

BOOL CHEXRetrieveThread::InitializeTMUnit(CTMUnit &cTMUnit, BOOL bBadData)
{
	return m_cTMEnvironment.Initialize(cTMUnit, bBadData);
}
BOOL CHEXRetrieveThread::InitializeTMUnit(LPCTSTR pszTag, CTMUnit &cTMUnit, BOOL bBadData)
{
	return m_cTMEnvironment.Initialize(pszTag, cTMUnit, bBadData);
}

BOOL CHEXRetrieveThread::InitializeTMData(CTMParameters &pTMParameters, BOOL bBadData)
{
	return m_cTMEnvironment.Initialize(pTMParameters, bBadData);
}

int CHEXRetrieveThread::Run()
{
	BOOL  bDump;
	UINT  nAction;
	UINT  nResult;
	DWORD  dwResult;
	TIMETAG  tTime;
	CTimeKey  tTimeKey;
	CTimeTag  tTimeTag[2];
	CHEXWnd  *pHEXWnd = (CHEXWnd *)GetThreadInfo();

	StartRetrieving();
	if (m_cTMEnvironment.Create(GetDatabase(), FALSE))
	{
		if ((bDump = (HIWORD(pHEXWnd->GetType()) == HEX_TYPE_DUMPS  &&  !(GetRetrieveMode() & HEX_RETRIEVE_REDODUMPS)) ? TRUE : FALSE) || m_cTMProcessEngine.Open(GetDatabase(), GetAccountSpacecraftName(), GetRetrieveFileName(), &m_cTMEnvironment))
		{
			for (BeginWaitCursor(), pHEXWnd->SetRetrieveMode((m_nMode = (m_nMode & (HEX_RETRIEVE_AUTOBACKWARD | HEX_RETRIEVE_MANUALBACKWARD)) ? ((m_nMode & ~(HEX_RETRIEVE_AUTOBACKWARD | HEX_RETRIEVE_MANUALBACKWARD | HEX_RETRIEVE_STOPPED | HEX_RETRIEVE_RELATIVE)) | HEX_RETRIEVE_MANUALFORWARD) : (m_nMode & ~(HEX_RETRIEVE_STOPPED | HEX_RETRIEVE_RELATIVE)))), pHEXWnd->Reset(&m_cTMEnvironment), SetEvent(m_bInit), nResult = (!bDump) ? m_cTMProcessEngine.ProcessTMData(GetDatabase(), &m_cTMEnvironment, (tTimeKey = GetRetrieveStartTime())) : pHEXWnd->ProcessMemoryDumps((tTimeKey = GetRetrieveStartTime()), 0), nAction = 0; (dwResult = Wait(0)) == WAIT_TIMEOUT && !pHEXWnd->IsInitialized(); )
			{
				SwitchToThread();
				continue;
			}
			for (; dwResult == WAIT_TIMEOUT; BeginWaitCursor())
			{
				if ((GetRetrieveMode() & HEX_RETRIEVE_AUTOFORWARD) && !(GetRetrieveMode() & HEX_RETRIEVE_STOPPED))
				{
					for (; (nResult & HISTORYFILE_SUCCESS) && !(GetRetrieveMode() & HEX_RETRIEVE_RELATIVE) && (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT && ((!(GetRetrieveMode() & HEX_RETRIEVE_EXACTTIME) && !pHEXWnd->Update(tTimeKey, &m_cTMEnvironment, nResult)) || ((GetRetrieveMode() & HEX_RETRIEVE_EXACTTIME) && tTimeKey < GetRetrieveStartTime())); )
					{
						if (!((nResult = (!bDump) ? m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, 0) : pHEXWnd->ProcessMemoryDumps(tTimeKey, 0)) & HISTORYFILE_SUCCESS)) break;
						if (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS))
						{
							if (GetRetrieveMode() & HEX_RETRIEVE_STOPBYREALTIME)
							{
								pHEXWnd->SetMode(DISPLAY_MODE_REALTIME);
								pHEXWnd->ProcessRealtimeData();
								pHEXWnd->UpdateBars();
								break;
							}
							ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
							pHEXWnd->SetRetrieveMode(pHEXWnd->GetRetrieveMode() | HEX_RETRIEVE_STOPPED);
							pHEXWnd->UpdateBars();
							break;
						}
						if ((GetRetrieveMode() & HEX_RETRIEVE_STOPBYTIME) && GetRetrieveStopTime() < tTimeKey)
						{
							pHEXWnd->SetRetrieveMode(pHEXWnd->GetRetrieveMode() | HEX_RETRIEVE_STOPPED);
							pHEXWnd->UpdateBars();
							break;
						}
					}
					EndWaitCursor();
					if (pHEXWnd->GetMode() != DISPLAY_MODE_REALTIME)
					{
						if ((((nResult & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS))) || (GetRetrieveMode() & HEX_RETRIEVE_RELATIVE)) && (!(GetRetrieveMode() & HEX_RETRIEVE_STOPBYTIME) || GetRetrieveStopTime() >= tTimeKey) && dwResult == WAIT_TIMEOUT)
						{
							if ((!(GetRetrieveMode() & HEX_RETRIEVE_RELATIVE) && (!(GetRetrieveMode() & HEX_RETRIEVE_EXACTTIME) || pHEXWnd->Update(tTimeKey, &m_cTMEnvironment, HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS) || TRUE)) || (GetRetrieveMode() & HEX_RETRIEVE_RELATIVE))
							{
								for (; (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 10 * (10 - GetRetrieveSpeed())*(10 - GetRetrieveSpeed()))) == WAIT_TIMEOUT; )
								{
									if (((nResult = (!bDump) ? m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, (HIWORD(pHEXWnd->GetType()) == HEX_TYPE_STREAM) ? -GetRetrieveInterval().GetTotalSeconds() : GetRetrieveInterval().GetTotalSeconds()) : pHEXWnd->ProcessMemoryDumps(tTimeKey, GetRetrieveInterval())) & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)))
									{
										if (!(GetRetrieveMode() & HEX_RETRIEVE_STOPBYTIME) || GetRetrieveStopTime() >= tTimeKey)
										{
											pHEXWnd->Update(tTimeKey, &m_cTMEnvironment, nResult);
											continue;
										}
									}
									if (nResult & HISTORYFILE_SUCCESS)
									{
										if (GetRetrieveMode() & HEX_RETRIEVE_STOPBYREALTIME)
										{
											pHEXWnd->SetMode(DISPLAY_MODE_REALTIME);
											pHEXWnd->ProcessRealtimeData();
											pHEXWnd->UpdateBars();
											break;
										}
										ReportEvent((GetRetrieveMode() & HEX_RETRIEVE_STOPBYEND) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING : USER_NOERROR);
										pHEXWnd->SetRetrieveMode(pHEXWnd->GetRetrieveMode() | HEX_RETRIEVE_STOPPED);
										pHEXWnd->UpdateBars();
									}
									break;
								}
							}
						}
						if (!(nResult & HISTORYFILE_SUCCESS))
						{
							ReportEvent((nResult == HISTORYFILE_DATA_NONE) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING : ((nResult == HISTORYFILE_OPEN_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_OPEN_FAILURE : ((nResult == HISTORYFILE_WRITE_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_WRITE_FAILURE : ((nResult == HISTORYFILE_READ_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_READ_FAILURE : ((nResult == HISTORYFILE_ERROR) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE : SYSTEM_NOERROR)))));
							pHEXWnd->SetRetrieveMode(pHEXWnd->GetRetrieveMode() | HEX_RETRIEVE_STOPPED);
							pHEXWnd->Reset(&m_cTMEnvironment);
							pHEXWnd->UpdateBars();
							break;
						}
					}
					if (pHEXWnd->GetMode() == DISPLAY_MODE_REALTIME) break;
				}
				if ((GetRetrieveMode() & HEX_RETRIEVE_AUTOBACKWARD) && !(GetRetrieveMode() & HEX_RETRIEVE_STOPPED))
				{
					if ((nResult & HISTORYFILE_SUCCESS) && (GetRetrieveMode() & HEX_RETRIEVE_RELATIVE) && dwResult == WAIT_TIMEOUT)
					{
						for (EndWaitCursor(); (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 10 * (10 - GetRetrieveSpeed())*(10 - GetRetrieveSpeed()))) == WAIT_TIMEOUT; )
						{
							if (((nResult = (!bDump) ? m_cTMProcessEngine.RewindTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, (HIWORD(pHEXWnd->GetType()) == HEX_TYPE_STREAM) ? -max(GetRetrieveInterval().GetTotalSeconds(), 1) : GetRetrieveInterval().GetTotalSeconds()) : pHEXWnd->ProcessMemoryDumps(tTimeKey, GetRetrieveInterval())) & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)))
							{
								pHEXWnd->Update(tTimeKey, &m_cTMEnvironment, nResult);
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
							pHEXWnd->Update(tTimeKey, &m_cTMEnvironment, nResult);
							pHEXWnd->SetRetrieveMode(pHEXWnd->GetRetrieveMode() | HEX_RETRIEVE_STOPPED);
							pHEXWnd->UpdateBars();
						}
					}
					else
					{
						ReportEvent((nResult == HISTORYFILE_DATA_NONE) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING : ((nResult == HISTORYFILE_OPEN_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_OPEN_FAILURE : ((nResult == HISTORYFILE_WRITE_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_WRITE_FAILURE : ((nResult == HISTORYFILE_READ_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_READ_FAILURE : ((nResult == HISTORYFILE_ERROR) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE : SYSTEM_NOERROR)))));
						pHEXWnd->SetRetrieveMode(pHEXWnd->GetRetrieveMode() | HEX_RETRIEVE_STOPPED);
						pHEXWnd->Reset(&m_cTMEnvironment);
						pHEXWnd->UpdateBars();
						EndWaitCursor();
						break;
					}
					EndWaitCursor();
				}
				if ((GetRetrieveMode() & HEX_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & HEX_RETRIEVE_STOPPED))
				{
					for (; (nResult & HISTORYFILE_SUCCESS) && !(GetRetrieveMode() & HEX_RETRIEVE_RELATIVE) && (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT && ((!(GetRetrieveMode() & HEX_RETRIEVE_EXACTTIME) && !pHEXWnd->Update(tTimeKey, &m_cTMEnvironment, nResult)) || ((GetRetrieveMode() & HEX_RETRIEVE_EXACTTIME) && tTimeKey < GetRetrieveStartTime())); )
					{
						if (!((nResult = (!bDump) ? m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, 0) : pHEXWnd->ProcessMemoryDumps(tTimeKey, 0)) & HISTORYFILE_SUCCESS)) break;
						if (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS))
						{
							if (GetRetrieveMode() & HEX_RETRIEVE_STOPBYREALTIME)
							{
								pHEXWnd->SetMode(DISPLAY_MODE_REALTIME);
								pHEXWnd->ProcessRealtimeData();
								pHEXWnd->UpdateBars();
								break;
							}
							ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
							pHEXWnd->SetRetrieveMode(pHEXWnd->GetRetrieveMode() | HEX_RETRIEVE_STOPPED);
							pHEXWnd->UpdateBars();
							break;
						}
					}
					EndWaitCursor();
					if (pHEXWnd->GetMode() != DISPLAY_MODE_REALTIME)
					{
						if ((((nResult & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS))) || (GetRetrieveMode() & HEX_RETRIEVE_RELATIVE)) && dwResult == WAIT_TIMEOUT)
						{
							if ((!(GetRetrieveMode() & HEX_RETRIEVE_RELATIVE) && (!(GetRetrieveMode() & HEX_RETRIEVE_EXACTTIME) || pHEXWnd->Update(tTimeKey, &m_cTMEnvironment, HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS) || TRUE)) || (GetRetrieveMode() & HEX_RETRIEVE_RELATIVE))
							{
								for (; (dwResult = (!(GetRetrieveMode() & HEX_RETRIEVE_RELATIVE) || nAction != HEXRETRIEVETHREAD_ACTION_MANUALFORWARD) ? Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, INFINITE) : (WAIT_OBJECT_0 + nAction + 1)) == WAIT_OBJECT_0 + HEXRETRIEVETHREAD_ACTION_MANUALFORWARD + 1; EndWaitCursor())
								{
									for (BeginWaitCursor(TRUE); (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT; )
									{
										if (((nResult = (!bDump) ? m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, (HIWORD(pHEXWnd->GetType()) == HEX_TYPE_STREAM) ? -GetRetrieveInterval().GetTotalSeconds() : GetRetrieveInterval().GetTotalSeconds()) : pHEXWnd->ProcessMemoryDumps(tTimeKey, GetRetrieveInterval())) & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)))
										{
											if (pHEXWnd->Update(tTimeKey, &m_cTMEnvironment, nResult)) break;
											continue;
										}
										if (nResult & HISTORYFILE_SUCCESS)
										{
											if (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS))
											{
												if (GetRetrieveMode() & HEX_RETRIEVE_STOPBYREALTIME)
												{
													pHEXWnd->SetMode(DISPLAY_MODE_REALTIME);
													pHEXWnd->ProcessRealtimeData();
													pHEXWnd->UpdateBars();
													break;
												}
												ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
												pHEXWnd->SetRetrieveMode(pHEXWnd->GetRetrieveMode() | HEX_RETRIEVE_STOPPED);
												pHEXWnd->UpdateBars();
											}
										}
										break;
									}
									if (!(nResult & HISTORYFILE_SUCCESS) || (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS)) || pHEXWnd->GetMode() == DISPLAY_MODE_REALTIME || dwResult == WAIT_OBJECT_0)
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
							pHEXWnd->SetRetrieveMode(pHEXWnd->GetRetrieveMode() | HEX_RETRIEVE_STOPPED);
							pHEXWnd->Reset(&m_cTMEnvironment);
							pHEXWnd->UpdateBars();
							break;
						}
					}
					if (pHEXWnd->GetMode() == DISPLAY_MODE_REALTIME) break;
				}
				if ((GetRetrieveMode() & HEX_RETRIEVE_MANUALBACKWARD) && !(GetRetrieveMode() & HEX_RETRIEVE_STOPPED))
				{
					if ((nResult & HISTORYFILE_SUCCESS) && (GetRetrieveMode() & HEX_RETRIEVE_RELATIVE) && dwResult == WAIT_TIMEOUT)
					{
						for (EndWaitCursor(); (dwResult = (nAction != HEXRETRIEVETHREAD_ACTION_MANUALBACKWARD) ? Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, INFINITE) : (WAIT_OBJECT_0 + nAction + 1)) == WAIT_OBJECT_0 + HEXRETRIEVETHREAD_ACTION_MANUALBACKWARD + 1; EndWaitCursor())
						{
							for (BeginWaitCursor(TRUE); (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT; )
							{
								if (((nResult = (!bDump) ? m_cTMProcessEngine.RewindTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, (HIWORD(pHEXWnd->GetType()) == HEX_TYPE_STREAM) ? -max(GetRetrieveInterval().GetTotalSeconds(), 1) : GetRetrieveInterval().GetTotalSeconds()) : pHEXWnd->ProcessMemoryDumps(tTimeKey, GetRetrieveInterval())) & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)))
								{
									if (pHEXWnd->Update(tTimeKey, &m_cTMEnvironment, nResult)) break;
									continue;
								}
								if (nResult & HISTORYFILE_SUCCESS)
								{
									if (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS))
									{
										ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
										pHEXWnd->Update(tTimeKey, &m_cTMEnvironment, nResult);
										pHEXWnd->SetRetrieveMode(pHEXWnd->GetRetrieveMode() | HEX_RETRIEVE_STOPPED);
										pHEXWnd->UpdateBars();
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
						pHEXWnd->SetRetrieveMode(pHEXWnd->GetRetrieveMode() | HEX_RETRIEVE_STOPPED);
						pHEXWnd->Reset(&m_cTMEnvironment);
						pHEXWnd->UpdateBars();
						EndWaitCursor();
						break;
					}
					EndWaitCursor();
				}
				if ((GetRetrieveMode() & HEX_RETRIEVE_PSEUDOREALTIME) && !(GetRetrieveMode() & HEX_RETRIEVE_STOPPED))
				{
					for (; (nResult & HISTORYFILE_SUCCESS) && !(GetRetrieveMode() & HEX_RETRIEVE_RELATIVE) && (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT && ((!(GetRetrieveMode() & HEX_RETRIEVE_EXACTTIME) && !pHEXWnd->Update(tTimeKey, &m_cTMEnvironment, nResult)) || ((GetRetrieveMode() & HEX_RETRIEVE_EXACTTIME) && tTimeKey < GetRetrieveStartTime())); )
					{
						if (!((nResult = (!bDump) ? m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, 0) : pHEXWnd->ProcessMemoryDumps(tTimeKey, 0)) & HISTORYFILE_SUCCESS)) break;
						if (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS))
						{
							if (GetRetrieveMode() & HEX_RETRIEVE_STOPBYREALTIME)
							{
								pHEXWnd->SetMode(DISPLAY_MODE_REALTIME);
								pHEXWnd->ProcessRealtimeData();
								pHEXWnd->UpdateBars();
								break;
							}
							ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
							pHEXWnd->SetRetrieveMode(pHEXWnd->GetRetrieveMode() | HEX_RETRIEVE_STOPPED);
							pHEXWnd->UpdateBars();
							break;
						}
						if ((GetRetrieveMode() & HEX_RETRIEVE_STOPBYTIME) && GetRetrieveStopTime() < tTimeKey)
						{
							pHEXWnd->SetRetrieveMode(pHEXWnd->GetRetrieveMode() | HEX_RETRIEVE_STOPPED);
							pHEXWnd->UpdateBars();
							break;
						}
					}
					EndWaitCursor();
					if (pHEXWnd->GetMode() != DISPLAY_MODE_REALTIME)
					{
						if ((((nResult & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS))) || (GetRetrieveMode() & HEX_RETRIEVE_RELATIVE)) && (!(GetRetrieveMode() & HEX_RETRIEVE_STOPBYTIME) || GetRetrieveStopTime() >= tTimeKey) && dwResult == WAIT_TIMEOUT)
						{
							if ((!(GetRetrieveMode() & HEX_RETRIEVE_RELATIVE) && (!(GetRetrieveMode() & HEX_RETRIEVE_EXACTTIME) || pHEXWnd->Update(tTimeKey, &m_cTMEnvironment, HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS) || TRUE)) || (GetRetrieveMode() & HEX_RETRIEVE_RELATIVE))
							{
								for (tTimeTag[0] = ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)) ? ((nResult & HISTORYFILE_TMUNIT) ? m_cTMEnvironment.GetTMUnit()->GetTimeTag() : CTimeTag(tTimeKey)) : CTimeTag(tTimeKey), tTimeTag[1] = CTimeTag(), tTime = CTimeTag().GetTime(); (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT; tTime = CTimeTag().GetTime())
								{
									if (((nResult = (!bDump) ? m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, 0) : pHEXWnd->ProcessMemoryDumps(tTimeKey, 0)) & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)))
									{
										if ((dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, (((nResult & HISTORYFILE_TMUNIT) && tTimeTag[1].GetTime() - tTimeTag[0].GetTime() + m_cTMEnvironment.GetTMUnit()->GetTimeTag().GetTime() > tTime) || ((nResult & HISTORYFILE_TMPARAMETERS) && tTimeTag[1].GetTime() - tTimeTag[0].GetTime() + CTimeTag(tTimeKey).GetTime() > tTime)) ? ((nResult & HISTORYFILE_TMUNIT) ? (DWORD)((tTimeTag[1].GetTime() - tTimeTag[0].GetTime() + m_cTMEnvironment.GetTMUnit()->GetTimeTag().GetTime() - tTime) / 1000) : (DWORD)((tTimeTag[1].GetTime() - tTimeTag[0].GetTime() + CTimeTag(tTimeKey).GetTime() - tTime) / 1000)) : 0)) != WAIT_TIMEOUT) break;
										if ((!(GetRetrieveMode() & HEX_RETRIEVE_STOPBYTIME) || GetRetrieveStopTime() >= tTimeKey) && ((nResult & HISTORYFILE_SYNCHRONIZE) || !tTimeTag[0].GetTime()))
										{
											tTimeTag[0] = (nResult & HISTORYFILE_TMUNIT) ? m_cTMEnvironment.GetTMUnit()->GetTimeTag() : CTimeTag(tTimeKey);
											tTimeTag[1] = tTime = CTimeTag().GetTime();
										}
										if (!(GetRetrieveMode() & HEX_RETRIEVE_STOPBYTIME) || GetRetrieveStopTime() >= tTimeKey)
										{
											pHEXWnd->Update(tTimeKey, &m_cTMEnvironment, nResult);
											continue;
										}
									}
									if (nResult & HISTORYFILE_SUCCESS)
									{
										if (GetRetrieveMode() & HEX_RETRIEVE_STOPBYREALTIME)
										{
											pHEXWnd->SetMode(DISPLAY_MODE_REALTIME);
											pHEXWnd->ProcessRealtimeData();
											pHEXWnd->UpdateBars();
											break;
										}
										ReportEvent((GetRetrieveMode() & HEX_RETRIEVE_STOPBYEND) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING : USER_NOERROR);
										pHEXWnd->SetRetrieveMode(pHEXWnd->GetRetrieveMode() | HEX_RETRIEVE_STOPPED);
										pHEXWnd->UpdateBars();
									}
									break;
								}
							}
						}
						if (!(nResult & HISTORYFILE_SUCCESS))
						{
							ReportEvent((nResult == HISTORYFILE_DATA_NONE) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING : ((nResult == HISTORYFILE_OPEN_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_OPEN_FAILURE : ((nResult == HISTORYFILE_WRITE_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_WRITE_FAILURE : ((nResult == HISTORYFILE_READ_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_READ_FAILURE : ((nResult == HISTORYFILE_ERROR) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE : SYSTEM_NOERROR)))));
							pHEXWnd->SetRetrieveMode(pHEXWnd->GetRetrieveMode() | HEX_RETRIEVE_STOPPED);
							pHEXWnd->Reset(&m_cTMEnvironment);
							pHEXWnd->UpdateBars();
							break;
						}
					}
					if (pHEXWnd->GetMode() == DISPLAY_MODE_REALTIME) break;
				}
				if ((GetRetrieveMode() & HEX_RETRIEVE_AUTOFORWARD) || (GetRetrieveMode() & HEX_RETRIEVE_AUTOBACKWARD) || (GetRetrieveMode() & HEX_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & HEX_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & HEX_RETRIEVE_PSEUDOREALTIME))
				{
					while ((dwResult = ((dwResult < WAIT_OBJECT_0 + HEXRETRIEVETHREAD_ACTION_AUTOFORWARD + 1 || dwResult > WAIT_OBJECT_0 + HEXRETRIEVETHREAD_ACTION_PSEUDOREALTIME + 1) && dwResult != WAIT_OBJECT_0) ? Wait(m_hAction, HEXRETRIEVETHREAD_ACTION_TYPES, FALSE, INFINITE, FALSE) : dwResult) == WAIT_OBJECT_0 + HEXRETRIEVETHREAD_ACTION_STOP + 1)
					{
						m_nMode = (GetRetrieveMode() & (HEX_RETRIEVE_STOPBYTIME | HEX_RETRIEVE_STOPBYEND | HEX_RETRIEVE_STOPBYREALTIME | HEX_RETRIEVE_REDODUMPS)) | HEX_RETRIEVE_STOPPED | HEX_RETRIEVE_RELATIVE;
						m_nMode |= ((GetRetrieveMode() & (HEX_RETRIEVE_STOPBYTIME | HEX_RETRIEVE_STOPBYEND | HEX_RETRIEVE_STOPBYREALTIME)) == 0) ? HEX_RETRIEVE_STOPBYREALTIME : 0;
						pHEXWnd->SetRetrieveMode(m_nMode);
						pHEXWnd->UpdateBars();
					}
					if (dwResult == WAIT_OBJECT_0 + HEXRETRIEVETHREAD_ACTION_AUTOFORWARD + 1)
					{
						m_nMode = (GetRetrieveMode() & (HEX_RETRIEVE_STOPBYTIME | HEX_RETRIEVE_STOPBYEND | HEX_RETRIEVE_STOPBYREALTIME | HEX_RETRIEVE_REDODUMPS)) | HEX_RETRIEVE_AUTOFORWARD | HEX_RETRIEVE_RELATIVE;
						m_nMode |= ((GetRetrieveMode() & (HEX_RETRIEVE_STOPBYTIME | HEX_RETRIEVE_STOPBYEND | HEX_RETRIEVE_STOPBYREALTIME)) == 0) ? HEX_RETRIEVE_STOPBYREALTIME : 0;
						nAction = HEXRETRIEVETHREAD_ACTION_AUTOFORWARD;
						pHEXWnd->SetRetrieveMode(m_nMode);
						pHEXWnd->UpdateBars();
						dwResult = WAIT_TIMEOUT;
						continue;
					}
					if (dwResult == WAIT_OBJECT_0 + HEXRETRIEVETHREAD_ACTION_AUTOBACKWARD + 1)
					{
						m_nMode = (GetRetrieveMode() & (HEX_RETRIEVE_STOPBYTIME | HEX_RETRIEVE_STOPBYEND | HEX_RETRIEVE_STOPBYREALTIME)) | HEX_RETRIEVE_AUTOBACKWARD | HEX_RETRIEVE_RELATIVE;
						m_nMode |= ((GetRetrieveMode() & (HEX_RETRIEVE_STOPBYTIME | HEX_RETRIEVE_STOPBYEND | HEX_RETRIEVE_STOPBYREALTIME)) == 0) ? HEX_RETRIEVE_STOPBYEND : 0;
						nAction = HEXRETRIEVETHREAD_ACTION_AUTOBACKWARD;
						pHEXWnd->SetRetrieveMode(m_nMode);
						pHEXWnd->UpdateBars();
						dwResult = WAIT_TIMEOUT;
						continue;
					}
					if (dwResult == WAIT_OBJECT_0 + HEXRETRIEVETHREAD_ACTION_MANUALFORWARD + 1)
					{
						m_nMode = (GetRetrieveMode() & (HEX_RETRIEVE_STOPBYTIME | HEX_RETRIEVE_STOPBYEND | HEX_RETRIEVE_STOPBYREALTIME | HEX_RETRIEVE_REDODUMPS)) | HEX_RETRIEVE_MANUALFORWARD | HEX_RETRIEVE_RELATIVE;
						nAction = HEXRETRIEVETHREAD_ACTION_MANUALFORWARD;
						pHEXWnd->SetRetrieveMode(m_nMode);
						pHEXWnd->UpdateBars();
						dwResult = WAIT_TIMEOUT;
						continue;
					}
					if (dwResult == WAIT_OBJECT_0 + HEXRETRIEVETHREAD_ACTION_MANUALBACKWARD + 1)
					{
						m_nMode = (GetRetrieveMode() & (HEX_RETRIEVE_STOPBYTIME | HEX_RETRIEVE_STOPBYEND | HEX_RETRIEVE_STOPBYREALTIME)) | HEX_RETRIEVE_MANUALBACKWARD | HEX_RETRIEVE_RELATIVE;
						nAction = HEXRETRIEVETHREAD_ACTION_MANUALBACKWARD;
						pHEXWnd->SetRetrieveMode(m_nMode);
						pHEXWnd->UpdateBars();
						dwResult = WAIT_TIMEOUT;
						continue;
					}
					if (dwResult == WAIT_OBJECT_0 + HEXRETRIEVETHREAD_ACTION_PSEUDOREALTIME + 1)
					{
						m_nMode = (GetRetrieveMode() & (HEX_RETRIEVE_STOPBYTIME | HEX_RETRIEVE_STOPBYEND | HEX_RETRIEVE_STOPBYREALTIME | HEX_RETRIEVE_REDODUMPS)) | HEX_RETRIEVE_PSEUDOREALTIME | HEX_RETRIEVE_RELATIVE;
						m_nMode |= ((GetRetrieveMode() & (HEX_RETRIEVE_STOPBYTIME | HEX_RETRIEVE_STOPBYEND | HEX_RETRIEVE_STOPBYREALTIME)) == 0) ? HEX_RETRIEVE_STOPBYREALTIME : 0;
						nAction = HEXRETRIEVETHREAD_ACTION_PSEUDOREALTIME;
						pHEXWnd->SetRetrieveMode(m_nMode);
						pHEXWnd->UpdateBars();
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
			SetEvent(m_bInit);
			ReportEvent(SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE);
		}
		m_cTMEnvironment.Destroy();
	}
	else
	{
		SetEvent(m_bInit);
		ReportEvent(SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE);
	}
	StopRetrieving();
	EndWaitCursor();
	return 0;
}

VOID CHEXRetrieveThread::StartRetrieving()
{
	InterlockedExchange(m_pbFlag, TRUE);
}

VOID CHEXRetrieveThread::StopRetrieving()
{
	InterlockedExchange(m_pbFlag, FALSE);
}

UINT CHEXRetrieveThread::GetRetrieveMode() CONST
{
	return((IsThreadActive()) ? m_nMode : 0);
}

UINT CHEXRetrieveThread::GetRetrieveSpeed() CONST
{
	return((IsThreadActive()) ? m_nSpeed : 0);
}

CTimeSpan CHEXRetrieveThread::GetRetrieveInterval() CONST
{
	return((IsThreadActive()) ? m_tInterval.GetTotalSeconds() : 0);
}

CTimeKey CHEXRetrieveThread::GetRetrieveStartTime() CONST
{
	return((IsThreadActive()) ? m_tStartTime : 0);
}

CTimeKey CHEXRetrieveThread::GetRetrieveStopTime() CONST
{
	return((IsThreadActive()) ? m_tStopTime : 0);
}

CString CHEXRetrieveThread::GetRetrieveFileName() CONST
{
	return((IsThreadActive()) ? (LPCTSTR)m_szFileName : EMPTYSTRING);
}

VOID CHEXRetrieveThread::BeginWaitCursor(BOOL bForced)
{
	POINT  ptCursor;
	CHEXWnd  *pHEXWnd;
	CHourglassCursor  cCursor;

	for (GetCursorPos(&ptCursor), InterlockedExchange(m_pbFlag, MAKELONG(TRUE, ((m_nMode & HEX_RETRIEVE_RELATIVE) != HEX_RETRIEVE_RELATIVE || bForced) ? TRUE : FALSE)), SetCursorPos(ptCursor.x, ptCursor.y); (pHEXWnd = (CHEXWnd *)GetThreadInfo()); )
	{
		pHEXWnd->UpdateBars();
		break;
	}
}

VOID CHEXRetrieveThread::EndWaitCursor()
{
	POINT  ptCursor;
	CHEXWnd  *pHEXWnd;
	CHourglassCursor  cCursor;

	for (GetCursorPos(&ptCursor), InterlockedExchange(m_pbFlag, LOWORD(*m_pbFlag)), SetCursorPos(ptCursor.x, ptCursor.y); (pHEXWnd = (CHEXWnd *)GetThreadInfo()); )
	{
		pHEXWnd->UpdateBars();
		break;
	}
}

BEGIN_MESSAGE_MAP(CHEXRetrieveThread, CThread)
	//{{AFX_MSG_MAP(CHEXRetrieveThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHEXRetrieveThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CHEXPrintThread

IMPLEMENT_DYNCREATE(CHEXPrintThread, CThread)

BOOL CHEXPrintThread::Start(CHEXWnd *pParentWnd)
{
	return CreateThread(pParentWnd);
}

BOOL CHEXPrintThread::Stop()
{
	return((DestroyThread() >= 0) ? TRUE : FALSE);
}

BOOL CHEXPrintThread::SetPrintJobs(CONST CHEXPrintJobs &pPrintJobs)
{
	INT  nJob[2][2];
	INT  nJobs[2][2];
	CHEXPrintJobInfo  *pJobInfo;
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
			if ((pJobInfo = new CHEXPrintJobInfo))
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

BOOL CHEXPrintThread::GetPrintJobs(CHEXPrintJobs &pPrintJobs) CONST
{
	CByteArray  nPrintInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(((m_pPrintJobs.GetSize() > 0 && pPrintJobs.Copy(&m_pPrintJobs)) || pPrintJobs.Unmap(nPrintInfo)) ? TRUE : FALSE);
}

int CHEXPrintThread::Run()
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
	CHEXPrintJobInfo  *pJobInfo[2];
	CHEXWnd  *pHEXWnd = (CHEXWnd *)GetThreadInfo();

	for (dwJobResult = 0; Lock(); )
	{
		if (dwJobResult == WAIT_OBJECT_0 + 1 || !dwJobResult)
		{
			for (nJob = 0, nJobs = (INT)m_pPrintJobs.GetSize(); nJob < nJobs; nJob++)
			{
				if ((pJobInfo[0] = m_pPrintJobs.GetAt(nJob)) && (pJobInfo[0]->GetPrintMode() & HEX_PRINT_ACTIVE))
				{
					if (pJobInfo[0]->GetPrintAtDailyTime(tJobDailyTime) || pJobInfo[0]->GetPrintAtDailyTime(tJobDailyTime, nJobStopCount) || pJobInfo[0]->GetPrintAtDailyTime(tJobDailyTime, tJobStopTime))
					{
						pJobInfo[0]->SetPrintLastDailyTime(((tJobTime = CTime::GetCurrentTime().GetTime()).GetTime() % SECONDSPERDAY >= tJobDailyTime.GetTotalSeconds()) ? ((SECONDSPERDAY*(tJobTime.GetTime() / SECONDSPERDAY)) + tJobDailyTime.GetTotalSeconds()) : ((SECONDSPERDAY*(tJobTime.GetTime() / SECONDSPERDAY - 1)) + tJobDailyTime.GetTotalSeconds()));
						continue;
					}
				}
			}
		}
		if ((pJobInfo[0] = ((tJobInterval = m_pPrintJobs.Schedule()) == 0) ? m_pPrintJobs.GetAt(0) : (CHEXPrintJobInfo *)NULL))
		{
			for (bJobPrint = pHEXWnd->Print(pJobInfo[0]); (pJobInfo[0]->GetPrintMode() & HEX_PRINT_CLEARCOMMENTS) && bJobPrint; )
			{
				for (nJob = 1, nJobs = (INT)m_pPrintJobs.GetSize(); nJob < nJobs; nJob++)
				{
					if ((pJobInfo[1] = m_pPrintJobs.GetAt(nJob)))
					{
						if (pJobInfo[0]->GetName() == pJobInfo[1]->GetName())
						{
							pJobInfo[1]->SetPrintMode(pJobInfo[0]->GetPrintMode() & ~HEX_PRINT_CLEARCOMMENTS);
							pJobInfo[1]->SetComments(EMPTYSTRING);
							break;
						}
					}
				}
				break;
			}
			ReportEvent((!bJobPrint) ? SYSTEM_WARNING_HEX_PRINT_FAILURE : SYSTEM_NOERROR);
			m_pPrintJobs.RemoveAt(0);
			delete pJobInfo[0];
		}
		Unlock();
		if ((dwJobResult = Wait(m_cEvent, FALSE, (tJobInterval >= 0) ? (DWORD)(1000 * min(tJobInterval, SECONDSPERDAY)) : INFINITE)) != WAIT_TIMEOUT  &&  dwJobResult != WAIT_OBJECT_0 + 1) break;
	}
	return 0;
}

BEGIN_MESSAGE_MAP(CHEXPrintThread, CThread)
	//{{AFX_MSG_MAP(CHEXPrintThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHEXPrintThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CHEXToolBar

IMPLEMENT_DYNCREATE(CHEXToolBar, CDisplayToolBar)

CHEXToolBar::CHEXToolBar() : CDisplayToolBar()
{
	return;
}

BEGIN_MESSAGE_MAP(CHEXToolBar, CDisplayToolBar)
	//{{AFX_MSG_MAP(CHEXToolBar)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHEXToolBar message handlers


/////////////////////////////////////////////////////////////////////////////
// CHEXStatusBar

IMPLEMENT_DYNCREATE(CHEXStatusBar, CDisplayStatusBar)

CHEXStatusBar::CHEXStatusBar() : CDisplayStatusBar()
{
	return;
}

BOOL CHEXStatusBar::SetIndicators(CONST UINT *pPanesID, INT nCount)
{
	INT  nIndex;
	CRect  rPane;
	CString  szPane;
	CToolInfo  cToolInfo;
	CDisplayLock  cLock(this);

	if (CDisplayStatusBar::SetIndicators(pPanesID, nCount))
	{
		if (CommandToIndex(ID_HEX_STATUSBAR_MESSAGEPANE) >= 0)
		{
			szPane.Format(STRING(IDS_HEX_STATUSBAR_UPDATEMESSAGE), (LPCTSTR)CTimeTag().FormatGmt(), (LPCTSTR)CString(CTimeTag().FormatGmt().Right(1), GetDatabase()->GetTMPacketTagLength()), -1, STRING(IDS_HEX_STATUSBAR_QUALITYGOOD));
			SetPaneInfo(CommandToIndex(ID_HEX_STATUSBAR_MESSAGEPANE), ID_HEX_STATUSBAR_MESSAGEPANE, SBPS_NOBORDERS | SBPS_STRETCH, CalcPaneWidth(szPane + STRING(IDS_HEX_STATUSBAR_TIMECORRELATIONFLAG)));
		}
		if (!IsWindow(m_wndToolTip.GetSafeHwnd()))
		{
			m_wndToolTip.Create(this, TTS_ALWAYSTIP | TTS_NOPREFIX | TTS_BALLOON);
			SetClassLongPtr(m_wndToolTip.GetSafeHwnd(), GCL_STYLE, GetClassLongPtr(m_wndToolTip.GetSafeHwnd(), GCL_STYLE) | CS_DROPSHADOW);
		}
		if (IsWindow(m_wndToolTip.GetSafeHwnd()))
		{
			if ((nIndex = CommandToIndex(ID_HEX_STATUSBAR_MODEPANE)) >= 0)
			{
				for (GetItemRect(nIndex, rPane); !m_wndToolTip.GetToolInfo(cToolInfo, this, ID_HEX_STATUSBAR_MODEPANE); )
				{
					m_wndToolTip.AddTool(this, LPSTR_TEXTCALLBACK, rPane, ID_HEX_STATUSBAR_MODEPANE);
					break;
				}
			}
			if ((nIndex = CommandToIndex(ID_HEX_STATUSBAR_TYPEPANE)) >= 0)
			{
				for (GetItemRect(nIndex, rPane); !m_wndToolTip.GetToolInfo(cToolInfo, this, ID_HEX_STATUSBAR_TYPEPANE); )
				{
					m_wndToolTip.AddTool(this, LPSTR_TEXTCALLBACK, rPane, ID_HEX_STATUSBAR_TYPEPANE);
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

CHEXWnd *CHEXStatusBar::GetParent() CONST
{
	return((CHEXWnd *)CDisplayStatusBar::GetParent());
}

BEGIN_MESSAGE_MAP(CHEXStatusBar, CDisplayStatusBar)
	//{{AFX_MSG_MAP(CHEXStatusBar)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipNotify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHEXStatusBar message handlers

void CHEXStatusBar::OnPaint()
{
	INT  nIndex;
	RECT  rPane;
	CToolInfo  cToolInfo;

	for (CDisplayStatusBar::OnPaint(); IsWindow(m_wndToolTip.GetSafeHwnd()); )
	{
		if ((nIndex = CommandToIndex(ID_HEX_STATUSBAR_MODEPANE)) >= 0 && nIndex < m_prPanes.GetSize())
		{
			for (m_wndToolTip.GetToolInfo(cToolInfo, this, ID_HEX_STATUSBAR_MODEPANE), CopyMemory(&rPane, m_prPanes.GetAt(nIndex), sizeof(RECT)); !EqualRect(&cToolInfo.rect, &rPane); )
			{
				SetRect(&cToolInfo.rect, rPane.left, rPane.top, rPane.right, rPane.bottom);
				m_wndToolTip.SetToolInfo(&cToolInfo);
				break;
			}
		}
		if ((nIndex = CommandToIndex(ID_HEX_STATUSBAR_TYPEPANE)) >= 0 && nIndex < m_prPanes.GetSize())
		{
			for (m_wndToolTip.GetToolInfo(cToolInfo, this, ID_HEX_STATUSBAR_TYPEPANE), CopyMemory(&rPane, m_prPanes.GetAt(nIndex), sizeof(RECT)); !EqualRect(&cToolInfo.rect, &rPane); )
			{
				SetRect(&cToolInfo.rect, rPane.left, rPane.top, rPane.right, rPane.bottom);
				m_wndToolTip.SetToolInfo(&cToolInfo);
				break;
			}
		}
		break;
	}
}

void CHEXStatusBar::OnMouseMove(UINT nFlags, CPoint point)
{
	MSG  sMsg;

	if (IsWindow(m_wndToolTip.GetSafeHwnd()))
	{
		CopyMemory(&sMsg, GetCurrentMessage(), sizeof(MSG));
		m_wndToolTip.RelayEvent(&sMsg);
	}
	CDisplayStatusBar::OnMouseMove(nFlags, point);
}

BOOL CHEXStatusBar::OnToolTipNotify(UINT nID, NMHDR *pNotifyInfo, LRESULT *pResult)
{
	TOOLTIPTEXT  *pToolTipInfo = (TOOLTIPTEXT *)pNotifyInfo;

	switch (pNotifyInfo->idFrom)
	{
	case ID_HEX_STATUSBAR_MODEPANE:
	{ pToolTipInfo->lpszText = (LPTSTR)STRING(IDS_HEX_STATUSBAR_MODEPANE);
	return TRUE;
	}
	case ID_HEX_STATUSBAR_TYPEPANE:
	{ pToolTipInfo->lpszText = (LPTSTR)STRING(IDS_HEX_STATUSBAR_TYPEPANE);
	return TRUE;
	}
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CHEXSplitterBarCtrl

IMPLEMENT_DYNCREATE(CHEXSplitterBarCtrl, CWnd)

CHEXSplitterBarCtrl::CHEXSplitterBarCtrl() : CWnd()
{
	m_ptBar[0].x = m_ptBar[0].y = 0;
	m_ptBar[1].x = m_ptBar[1].y = 0;
}

BOOL CHEXSplitterBarCtrl::Create(CWnd *pParentWnd, CONST RECT &rect)
{
	return CWnd::CreateEx(0, AfxRegisterWndClass(CS_NOCLOSE), EMPTYSTRING, WS_CHILD | WS_VISIBLE, rect, pParentWnd, 0);
}
BOOL CHEXSplitterBarCtrl::Create(CWnd *pParentWnd, CONST RECT &rect, CONST POINT &point)
{
	if (CWnd::CreateEx(0, AfxRegisterWndClass(CS_NOCLOSE), EMPTYSTRING, WS_POPUP, rect, pParentWnd, 0))
	{
		ShowWindow(SW_SHOWNA);
		m_ptBar[0] = point;
		m_ptBar[1] = point;
		return TRUE;
	}
	return FALSE;
}

VOID CHEXSplitterBarCtrl::Translate(CONST POINT &point)
{
	CRect  rBar;

	GetWindowRect(rBar);
	MoveWindow(rBar.left, rBar.top + point.y - m_ptBar[1].y, rBar.Width(), rBar.Height());
	m_ptBar[1].y = point.y;
	Invalidate(FALSE);
	UpdateWindow();
}

INT CHEXSplitterBarCtrl::CalcTranslation(CONST POINT &point) CONST
{
	return point.y - m_ptBar[0].y;
}
INT CHEXSplitterBarCtrl::CalcTranslation() CONST
{
	return m_ptBar[1].y - m_ptBar[0].y;
}

void CHEXSplitterBarCtrl::PostNcDestroy()
{
	m_ptBar[0].x = m_ptBar[0].y = 0;
	m_ptBar[1].x = m_ptBar[1].y = 0;
	CWnd::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CHEXSplitterBarCtrl, CWnd)
	//{{AFX_MSG_MAP(CHEXSplitterBarCtrl)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHEXSplitterBarCtrl message handlers

BOOL CHEXSplitterBarCtrl::OnEraseBkgnd(CDC *pDC)
{
	CDC  cMemDC;
	CPen  cPen;
	CPen  *pOldPen;
	CBitmap  cBitmap;
	CBitmap  *pOldBitmap;
	CRect  rBar;

	for (GetClientRect(rBar); GetStyle() & WS_POPUP; )
	{
		pDC->DrawDragRect(rBar, CSize(rBar.Height(), rBar.Height()), (LPCRECT)NULL, CSize(0, 0));
		return TRUE;
	}
	if (cMemDC.CreateCompatibleDC(pDC))
	{
		if (cBitmap.CreateCompatibleBitmap(pDC, rBar.Width(), rBar.Height()))
		{
			if ((pOldBitmap = cMemDC.SelectObject(&cBitmap)) != (CBitmap *)NULL)
			{
				if (cPen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DSHADOW)))
				{
					if ((pOldPen = cMemDC.SelectObject(&cPen)) != (CPen *)NULL)
					{
						cMemDC.FillSolidRect(0, 0, rBar.Width(), rBar.Height(), GetSysColor(COLOR_3DFACE));
						cMemDC.MoveTo(0, 0);
						cMemDC.LineTo(rBar.Width(), 0);
						cMemDC.MoveTo(0, rBar.Height() - 1);
						cMemDC.LineTo(rBar.Width(), rBar.Height() - 1);
						pDC->BitBlt(rBar.left, rBar.top, rBar.Width(), rBar.Height(), &cMemDC, 0, 0, SRCCOPY);
						cMemDC.SelectObject(pOldPen);
					}
					cPen.DeleteObject();
				}
				cMemDC.SelectObject(pOldBitmap);
			}
			cBitmap.DeleteObject();
		}
		cMemDC.DeleteDC();
	}
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CHEXDataContainer

IMPLEMENT_DYNCREATE(CHEXDataContainer, CTextView)

CHEXDataContainer::CHEXDataContainer() : CTextView()
{
	return;
}

CHEXDataView *CHEXDataContainer::GetParent() CONST
{
	return((CHEXDataView *)CTextView::GetParent());
}

CHEXWnd *CHEXDataContainer::GetParentDisplay() CONST
{
	CHEXDataView  *pView;

	return(((pView = GetParent())) ? pView->GetParent() : (CHEXWnd *)NULL);
}

BOOL CHEXDataContainer::Lock()
{
	return((IsWindow(GetSafeHwnd())) ? (GetParentDisplay()->Lock() && CTextView::Lock()) : CTextView::Lock());
}

BOOL CHEXDataContainer::Unlock()
{
	return((IsWindow(GetSafeHwnd())) ? (CTextView::Unlock() && GetParentDisplay()->Unlock()) : CTextView::Unlock());
}

BEGIN_MESSAGE_MAP(CHEXDataContainer, CTextView)
	//{{AFX_MSG_MAP(CHEXDataContainer)
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHEXDataContainer message handlers

BOOL CHEXDataContainer::OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message)
{
	LONG  lDataFlag;
	POINT  ptCursor;
	CRect  rContent;
	CTextViewLock  cLock(this);

	for (GetCursorPos(&ptCursor), m_wndContentCtrl.ScreenToClient(&ptCursor), m_wndContentCtrl.GetClientRect(rContent); rContent.PtInRect(ptCursor); )
	{
		if ((lDataFlag = GetParentDisplay()->IsRetrievingData()) && HIWORD(lDataFlag))
		{
			SetCursor(LoadCursor((HINSTANCE)NULL, IDC_WAIT));
			return TRUE;
		}
		break;
	}
	return CTextView::OnSetCursor(pWnd, nHitTest, message);
}

BOOL CHEXDataContainer::OnContentMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
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
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CHEXDataHeaderCtrl

IMPLEMENT_DYNCREATE(CHEXDataHeaderCtrl, CMFCHeaderCtrl)

CHEXDataHeaderCtrl::CHEXDataHeaderCtrl() : CMFCHeaderCtrl()
{
	CFontTools  cFontTools(&m_cFont);

	m_wTextIndent[0] = m_wTextIndent[1] = 0;
	m_wTextSpacing[0] = m_wTextSpacing[1] = 0;
	m_pParentWnd = (CHEXDataView *)NULL;
}

BOOL CHEXDataHeaderCtrl::Create(CHEXDataView *pParentWnd, DWORD dwStyle, UINT nID)
{
	return CMFCHeaderCtrl::Create(dwStyle, CRect(0, 0, 0, 0), pParentWnd, nID);
}

BOOL CHEXDataHeaderCtrl::SetTitle(LPCTSTR pszTitle)
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

CString CHEXDataHeaderCtrl::GetTitle() CONST
{
	return m_szTitle;
}

BOOL CHEXDataHeaderCtrl::SetFont(CFont *pFont)
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
BOOL CHEXDataHeaderCtrl::SetFont(CONST LOGFONT *plfFont)
{
	CFont  cFont;

	return((cFont.CreateFontIndirect(plfFont) && SetFont(&cFont)) ? TRUE : FALSE);
}

BOOL CHEXDataHeaderCtrl::GetFont(CFont *pFont) CONST
{
	LOGFONT  lfFont;

	return(GetFont(&lfFont) && pFont->CreateFontIndirect(&lfFont));
}

BOOL CHEXDataHeaderCtrl::GetFont(LOGFONT *plfFont) CONST
{
	return((m_cFont.GetSafeHandle() != (HGDIOBJ)NULL  &&  m_cFont.GetObject(sizeof(LOGFONT), plfFont) > 0) ? TRUE : FALSE);
}

WORD CHEXDataHeaderCtrl::CalcDefaultIndent() CONST
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

WORD CHEXDataHeaderCtrl::CalcDefaultSpacing() CONST
{
	return GetSystemMetrics(SM_CYEDGE) + GetSystemMetrics(SM_CYBORDER);
}

CHEXDataView *CHEXDataHeaderCtrl::GetParent() CONST
{
	return m_pParentWnd;
}

BEGIN_MESSAGE_MAP(CHEXDataHeaderCtrl, CMFCHeaderCtrl)
	//{{AFX_MSG_MAP(CHEXDataHeaderCtrl)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHEXDataHeaderCtrl message handlers

int CHEXDataHeaderCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMFCHeaderCtrl::OnCreate(lpCreateStruct) != -1)
	{
		m_wTextIndent[0] = m_wTextIndent[1] = CalcDefaultIndent();
		m_wTextSpacing[0] = CalcDefaultSpacing();
		m_wTextSpacing[1] = m_wTextSpacing[0] + 1;
		return 0;
	}
	return -1;
}

BOOL CHEXDataHeaderCtrl::OnEraseBkgnd(CDC *pDC)
{
	UpdateWindow();
	return TRUE;
}

void CHEXDataHeaderCtrl::OnDrawItem(CDC *pDC, int iItem, CRect rect, BOOL bIsPressed, BOOL bIsHighlighted)
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
// CHEXDataView

IMPLEMENT_DYNCREATE(CHEXDataView, CWnd)

CHEXDataView::CHEXDataView() : CWnd()
{
	m_nLayoutColors.InsertAt(HEX_LAYOUTCOLOR_NORMALDATA, VGA_COLOR_GRAY);
	m_nLayoutColors.InsertAt(HEX_LAYOUTCOLOR_RAWDATA, VGA_COLOR_BLUE);
	m_nLayoutColors.InsertAt(HEX_LAYOUTCOLOR_ENUMERATIONS, VGA_COLOR_LTBLUE);
	m_nLayoutLineLength = HEXSETTINGSLAYOUTPAGE_LINE_DEFAULTLENGTH;
	m_nLayoutLineNumbers[0] = 1;
	m_nLayoutLineNumbers[1] = 1;
	m_sizeTrackLayout.cx = 0;
	m_sizeTrackLayout.cy = 0;
	m_bBadDataMode = FALSE;
	m_pwndHeaderCtrl = new CHEXDataHeaderCtrl;
	m_pwndView = new CHEXDataContainer;
	m_pParentWnd = (CWnd *)NULL;
}

CHEXDataView::~CHEXDataView()
{
	delete m_pwndHeaderCtrl;
	delete m_pwndView;
}

BOOL CHEXDataView::Create(CWnd *pParentWnd)
{
	CString  szTitle;

	if (CWnd::Create(AfxRegisterWndClass(CS_NOCLOSE, LoadCursor((HINSTANCE)NULL, IDC_ARROW), GetSysColorBrush(COLOR_WINDOW)), (LPCTSTR)NULL, WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE, CRect(0, 0, 0, 0), (m_pParentWnd = pParentWnd), 0))
	{
		SetTitle(STRING(IDS_HEX_TITLEITEM_DATA));
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXDataView::SetTitle(LPCTSTR pszTitle)
{
	CTextViewLock  cLock(m_pwndView);

	return m_pwndHeaderCtrl->SetTitle(pszTitle);
}

BOOL CHEXDataView::GetTitle(CString &szTitle) CONST
{
	CTextViewLock  cLock(m_pwndView);

	return(!(szTitle = m_pwndHeaderCtrl->GetTitle()).IsEmpty());
}

BOOL CHEXDataView::SetLayout(LPCTSTR pszLayout)
{
	UINT  nType;
	CTextViewLock  cLock(m_pwndView);

	for (m_szLayout = pszLayout, m_cLayout.Empty(); IsWindow(GetSafeHwnd()); )
	{
		SetTitle(((nType = HIWORD(GetParent()->GetType())) == HEX_TYPE_NORMAL || nType == HEX_TYPE_STREAM || !nType) ? STRING(IDS_HEX_TITLEITEM_DATA) : STRING(IDS_HEX_TITLEITEM_DUMP));
		AdjustColumns();
		break;
	}
	return TRUE;
}
BOOL CHEXDataView::SetLayout(LPCTSTR pszLayout, CONST CMemoryDump &cLayout)
{
	UINT  nType;
	CTextViewLock  cLock(m_pwndView);

	for (m_szLayout = pszLayout, m_cLayout.Copy(&cLayout); IsWindow(GetSafeHwnd()); )
	{
		SetTitle(((nType = HIWORD(GetParent()->GetType())) == HEX_TYPE_NORMAL || nType == HEX_TYPE_STREAM || !nType) ? STRING(IDS_HEX_TITLEITEM_DATA) : STRING(IDS_HEX_TITLEITEM_DUMP));
		AdjustColumns();
		break;
	}
	return TRUE;
}

BOOL CHEXDataView::GetLayout(CString &szLayout) CONST
{
	CTextViewLock  cLock(m_pwndView);

	szLayout = (HIWORD(GetParent()->GetType()) != HEX_TYPE_STREAM) ? m_szLayout : STRING(IDS_HEXOPENDIALOG_SPECIALTITLE);
	return TRUE;
}
BOOL CHEXDataView::GetLayout(CString &szLayout, CMemoryDump &cLayout) CONST
{
	UINT  nFormats;
	CMemoryDump  *pDump;
	CMemoryDumps  pDumps;
	CTextViewLock  cLock(m_pwndView);

	if (GetLayout(szLayout))
	{
		if ((pDump = (GetMemoryDumpsService()->GetMemoryDumps(pDumps)) ? pDumps.GetAt(pDumps.Find(m_cLayout.GetName())) : (CMemoryDump *)NULL))
		{
			for (cLayout.Copy(pDump, TRUE); (nFormats = m_cLayout.GetArchivingFileFormats()) >= 0; )
			{
				cLayout.SetArchivingFileFormats(nFormats);
				break;
			}
			return TRUE;
		}
		cLayout.Copy(&m_cLayout, TRUE);
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXDataView::SetLayoutFormat(UINT nHorzEnum, UINT nVertEnum, UINT nLineLength, CONST CUIntArray &nColors)
{
	INT  nItem;
	INT  nItems;
	CTextViewLock  cLock(m_pwndView);

	for (nItem = 0, nItems = (m_nLayoutLineNumbers[0] == nHorzEnum && m_nLayoutLineNumbers[1] == nVertEnum && m_nLayoutLineLength == nLineLength && m_nLayoutColors.GetSize() == nColors.GetSize()) ? (INT)nColors.GetSize() : -1; nItem < nItems; nItem++)
	{
		if (m_nLayoutColors.GetAt(nItem) != nColors.GetAt(nItem)) break;
		continue;
	}
	if (nItem != nItems)
	{
		for (m_nLayoutLineNumbers[0] = nHorzEnum, m_nLayoutLineNumbers[1] = nVertEnum, m_nLayoutLineLength = nLineLength, m_nLayoutColors.Copy(nColors); IsWindow(GetSafeHwnd()); )
		{
			AdjustColumns();
			Update();
			break;
		}
	}
	return TRUE;
}

BOOL CHEXDataView::GetLayoutFormat(UINT &nHorzEnum, UINT &nVertEnum, UINT &nLineLength, CUIntArray &nColors) CONST
{
	CTextViewLock  cLock(m_pwndView);

	nHorzEnum = m_nLayoutLineNumbers[0];
	nVertEnum = m_nLayoutLineNumbers[1];
	nLineLength = m_nLayoutLineLength;
	nColors.Copy(m_nLayoutColors);
	return TRUE;
}

BOOL CHEXDataView::SetTitleFont(CFont *pFont)
{
	LOGFONT  lfFont;

	return((pFont->GetLogFont(&lfFont) > 0) ? SetTitleFont(&lfFont) : FALSE);
}
BOOL CHEXDataView::SetTitleFont(CONST LOGFONT *plfFont)
{
	LOGFONT  lfFont;
	CTextViewLock  cLock(m_pwndView);

	if (!m_pwndHeaderCtrl->GetFont(&lfFont) || memcmp(plfFont, &lfFont, sizeof(LOGFONT)))
	{
		if (m_pwndHeaderCtrl->SetFont(plfFont))
		{
			RecalcLayout();
			return TRUE;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CHEXDataView::GetTitleFont(CFont *pFont) CONST
{
	return m_pwndHeaderCtrl->GetFont(pFont);
}
BOOL CHEXDataView::GetTitleFont(LOGFONT *plfFont) CONST
{
	return m_pwndHeaderCtrl->GetFont(plfFont);
}

BOOL CHEXDataView::SetTextFont(CFont *pFont)
{
	LOGFONT  lfFont;

	return((pFont->GetLogFont(&lfFont) > 0) ? SetTextFont(&lfFont) : FALSE);
}
BOOL CHEXDataView::SetTextFont(CONST LOGFONT *plfFont)
{
	LOGFONT  lfFont;
	CTextViewLock  cLock(m_pwndView);

	if (!m_pwndView->GetTextFont(&lfFont) || memcmp(plfFont, &lfFont, sizeof(LOGFONT)))
	{
		if (m_pwndView->SetTextFont(plfFont))
		{
			AdjustColumns();
			Update();
			return TRUE;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CHEXDataView::GetTextFont(CFont *pFont) CONST
{
	return m_pwndView->GetTextFont(pFont);
}
BOOL CHEXDataView::GetTextFont(LOGFONT *plfFont) CONST
{
	return m_pwndView->GetTextFont(plfFont);
}

BOOL CHEXDataView::EnableBadDataMode(BOOL bEnable)
{
	m_bBadDataMode = bEnable;
	return TRUE;
}

BOOL CHEXDataView::IsBadDataModeEnabled() CONST
{
	return m_bBadDataMode;
}

BOOL CHEXDataView::Initialize(CString &szTag, CTimeTag &tTag, WORD &wQuality)
{
	INT  nType;
	UINT  nFormats;
	CString  szFileName[2];
	CString  szFileExtension;
	CByteArray  nDumpData;
	CFileFindEx  cFileFind;
	CTextViewLock  cLock(m_pwndView);

	if ((nType = HIWORD(GetParent()->GetType())) == HEX_TYPE_NORMAL)
	{
		if ((GetParent()->GetMode() == DISPLAY_MODE_REALTIME  &&  InitializeTMUnit(m_szLayout, m_pLayoutData, IsBadDataModeEnabled())) || (GetParent()->GetMode() == DISPLAY_MODE_HISTORY  &&  GetParent()->InitializeTMData(m_szLayout, m_pLayoutData, IsBadDataModeEnabled())))
		{
			if (ShowRawData(m_pLayoutData) && m_pLayoutData.GetSize() > 0)
			{
				szTag = m_pLayoutData.GetTag();
				tTag = m_pLayoutData.GetTimeTag();
				wQuality = m_pLayoutData.GetQuality();
				Update();
				return TRUE;
			}
		}
		m_pLayoutData.Reset();
		wQuality = TMUNIT_DATAQUALITY_NONE;
		szTag.Empty();
		tTag = 0;
		Update();
		return TRUE;
	}
	if (nType == HEX_TYPE_STREAM)
	{
		if ((GetParent()->GetMode() == DISPLAY_MODE_REALTIME  &&  InitializeTMUnit(m_pLayoutData, IsBadDataModeEnabled())) || (GetParent()->GetMode() == DISPLAY_MODE_HISTORY  &&  GetParent()->InitializeTMData(m_pLayoutData, IsBadDataModeEnabled())))
		{
			if (ShowRawData(m_pLayoutData) && m_pLayoutData.GetSize() > 0)
			{
				szTag = m_pLayoutData.GetTag();
				tTag = m_pLayoutData.GetTimeTag();
				wQuality = m_pLayoutData.GetQuality();
				Update();
				return TRUE;
			}
		}
		m_pLayoutData.Reset();
		wQuality = TMUNIT_DATAQUALITY_NONE;
		szTag.Empty();
		tTag = 0;
		Update();
		return TRUE;
	}
	if (nType == HEX_TYPE_DUMPS)
	{
		if (GetLayout(m_szLayout, m_cLayout))
		{
			for (m_cLayout.GetFileExtension((nFormats = m_cLayout.GetArchivingFileFormats()), szFileExtension), szFileName[1] = GetMemoryDumpsServiceSupport()->GetMemoryDumpSearchFileName((szFileName[0] = m_cLayout.GetFileName()), szFileExtension); GetParent()->GetMode() == DISPLAY_MODE_REALTIME; )
			{
				if (InitializeTMDump(m_cLayout, IsBadDataModeEnabled()))
				{
					szTag = m_cLayout.GetDumpTag();
					tTag = m_cLayout.GetDumpTime();
					wQuality = m_cLayout.GetDumpQuality();
					wQuality = (LOBYTE(wQuality) & MEMORYDUMP_DATAQUALITY_GOOD) ? (WORD)(TMUNIT_DATAQUALITY_GOOD | TMUNIT_SEQUENCEQUALITY_GOOD | ((LOBYTE(wQuality) & MEMORYDUMP_TIMECORRELATION_GOOD) ? TMUNIT_TIMECORRELATION_GOOD : TMUNIT_TIMECORRELATION_BAD)) : (WORD)(TMUNIT_DATAQUALITY_BAD | ((LOBYTE(wQuality) & MEMORYDUMP_TIMECORRELATION_GOOD) ? TMUNIT_TIMECORRELATION_GOOD : TMUNIT_TIMECORRELATION_BAD));
					ShowDumpData(GetMemoryDumpsServiceSupport()->FormatMemoryDumpData(&m_cLayout, nFormats));
					Update();
					return TRUE;
				}
				if (m_cLayout.GetDumpData(nDumpData) > 0)
				{
					Update();
					return FALSE;
				}
				if (cFileFind.FindFile(szFileName[1]))
				{
					while (cFileFind.FindNextFile());
					if (Update(cFileFind.GetFilePath(), szTag, tTag, wQuality))
					{
						cFileFind.Close();
						Update();
						return TRUE;
					}
					cFileFind.Close();
				}
				break;
			}
			m_pwndView->DeleteAllText();
			m_cLayout.SetDumpInfo(MEMORYDUMP_STATUS_EMPTY);
			szTag = m_cLayout.GetDumpTag();
			tTag = m_cLayout.GetDumpTime();
			wQuality = m_cLayout.GetDumpQuality();
			Update();
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CHEXDataView::Update(LPCTSTR pszFileName, CString &szTag, CTimeTag &tTag, WORD &wQuality)
{
	DWORD  cbFile;
	CFileEx  cFile;
	CString  szDump;
	FILETIME  sFileTime[3];
	CByteArray  nDumpData[2];
	CTextViewLock  cLock(m_pwndView);

	if (cFile.Open(pszFileName, CFile::modeRead | CFile::shareDenyNone))
	{
		if (GetFileTime((HANDLE)cFile.m_hFile, &sFileTime[0], &sFileTime[1], &sFileTime[2]))
		{
			nDumpData[0].SetSize((INT_PTR)cFile.GetLength());
			if (nDumpData[0].GetSize() == cFile.GetLength())
			{
				if (ReadFile(cFile.m_hFile, (LPVOID)nDumpData[0].GetData(), (DWORD)nDumpData[0].GetSize(), &cbFile, (LPOVERLAPPED)NULL))
				{
					nDumpData[1].Copy(nDumpData[0]);
					nDumpData[1].Add(0);
					if (nDumpData[0].GetSize() != (INT)strlen((LPCSTR)nDumpData[1].GetData()))
					{
#ifndef UNICODE
						WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)nDumpData[0].GetData(), (INT)(nDumpData[0].GetSize() / sizeof(WCHAR)), szDump.GetBufferSetLength((INT)(nDumpData[0].GetSize() / sizeof(WCHAR))), (INT)(nDumpData[0].GetSize() / sizeof(WCHAR) + 1), (LPCSTR)NULL, (LPBOOL)NULL);
						szDump.ReleaseBuffer();
#else
						CopyMemory(szDump.GetBufferSetLength((INT)(nDumpData[0].GetSize() / sizeof(WCHAR))), nDumpData[0].GetData(), (INT)nDumpData[0].GetSize());
						szDump.ReleaseBuffer();
#endif
					}
					else
					{
#ifndef UNICODE
						CopyMemory(szDump.GetBufferSetLength((INT)(nDumpData[0].GetSize() / sizeof(CHAR))), nDumpData[0].GetData(), nDumpData[0].GetSize());
						szDump.ReleaseBuffer();
#else
						MultiByteToWideChar(CP_ACP, 0, (LPCSTR)nDumpData[0].GetData(), (INT)(nDumpData[0].GetSize() / sizeof(CHAR)), szDump.GetBufferSetLength((INT)(nDumpData[0].GetSize() / sizeof(CHAR))), (INT)(nDumpData[0].GetSize() / sizeof(CHAR) + 1));
						szDump.ReleaseBuffer();
#endif
					}
					if (ShowDumpData(szDump))
					{
						m_cLayout.SetDumpInfo(MEMORYDUMP_STATUS_EMPTY);
						wQuality = m_cLayout.GetDumpQuality();
						szTag = m_cLayout.GetDumpTag();
						tTag = sFileTime[0];
						cFile.Close();
						return TRUE;
					}
				}
			}
		}
		cFile.Close();
	}
	return FALSE;
}
BOOL CHEXDataView::Update(CTMEnvironment *pTMEnvironment)
{
	INT  nType;
	UINT  nStatus;
	WORD  wQuality;
	CString  szDump;
	CTimeTag  tDump;
	CByteArray  nDumpData;
	CMemoryDump  *pDump;
	CTextViewLock  cLock(m_pwndView);

	if (IsInitialized())
	{
		if ((nType = HIWORD(GetParent()->GetType())) == HEX_TYPE_NORMAL || nType == HEX_TYPE_STREAM)
		{
			if (pTMEnvironment != (CTMEnvironment *)NULL)
			{
				if (!pTMEnvironment->GetTMUnit()->IsValid() || !pTMEnvironment->GetTMUnit()->HasBadData() || IsBadDataModeEnabled())
				{
					m_pLayoutData.Copy(pTMEnvironment->GetTMUnit());
					return ShowRawData(m_pLayoutData);
				}
				return FALSE;
			}
			return ShowRawData(m_pLayoutData);
		}
		if (nType == HEX_TYPE_DUMPS)
		{
			if (pTMEnvironment != (CTMEnvironment *)NULL)
			{
				if ((pDump = pTMEnvironment->GetMemoryDumps()->GetAt(pTMEnvironment->GetMemoryDumps()->Find(m_cLayout.GetName()))))
				{
					szDump = pDump->GetDumpTag();
					tDump = pDump->GetDumpTime();
					nStatus = pDump->GetDumpStatus();
					wQuality = pDump->GetDumpQuality();
					pDump->GetDumpData(nDumpData);
					if (nStatus == MEMORYDUMP_STATUS_COMPLETE || nStatus == MEMORYDUMP_STATUS_INCOMPLETE)
					{
						if ((LOBYTE(wQuality) & MEMORYDUMP_DATAQUALITY_GOOD) || IsBadDataModeEnabled())
						{
							if (ShowDumpData(GetMemoryDumpsServiceSupport()->FormatMemoryDumpData(pDump, m_cLayout.GetArchivingFileFormats())))
							{
								for (m_cLayout.SetDumpInfo(MEMORYDUMP_STATUS_EMPTY); m_cLayout.SetDumpInfo(szDump, tDump, nDumpData, (LOBYTE(wQuality) & MEMORYDUMP_DATAQUALITY_GOOD) ? (WORD)(TMUNIT_DATAQUALITY_GOOD | TMUNIT_SEQUENCEQUALITY_GOOD | ((LOBYTE(wQuality) & MEMORYDUMP_TIMECORRELATION_GOOD) ? TMUNIT_TIMECORRELATION_GOOD : TMUNIT_TIMECORRELATION_BAD)) : (WORD)(TMUNIT_DATAQUALITY_BAD | ((LOBYTE(wQuality) & MEMORYDUMP_TIMECORRELATION_GOOD) ? TMUNIT_TIMECORRELATION_GOOD : TMUNIT_TIMECORRELATION_BAD))); )
								{
									m_cLayout.SetDumpInfo(nStatus);
									break;
								}
								return TRUE;
							}
							for (m_cLayout.SetDumpInfo(MEMORYDUMP_STATUS_EMPTY); m_cLayout.SetDumpInfo(szDump, tDump, nDumpData, (LOBYTE(wQuality) & MEMORYDUMP_DATAQUALITY_GOOD) ? (WORD)(TMUNIT_DATAQUALITY_GOOD | TMUNIT_SEQUENCEQUALITY_GOOD | ((LOBYTE(wQuality) & MEMORYDUMP_TIMECORRELATION_GOOD) ? TMUNIT_TIMECORRELATION_GOOD : TMUNIT_TIMECORRELATION_BAD)) : (WORD)(TMUNIT_DATAQUALITY_BAD | ((LOBYTE(wQuality) & MEMORYDUMP_TIMECORRELATION_GOOD) ? TMUNIT_TIMECORRELATION_GOOD : TMUNIT_TIMECORRELATION_BAD))); )
							{
								m_cLayout.SetDumpInfo(nStatus);
								break;
							}
						}
					}
					return FALSE;
				}
			}
			ShowDumpData((LPCTSTR)NULL, pTMEnvironment != (CTMEnvironment *)NULL);
		}
	}
	return FALSE;
}

VOID CHEXDataView::Reset(CTMEnvironment *pTMEnvironment)
{
	CTextViewLock  cLock(m_pwndView);

	m_pLayoutData.Reset();
	m_cLayout.SetDumpInfo(MEMORYDUMP_STATUS_EMPTY);
	Update(pTMEnvironment);
}

BOOL CHEXDataView::IsInitialized() CONST
{
	CTextViewLock  cLock(m_pwndView);

	return((IsWindow(GetSafeHwnd())) ? GetParent()->IsInitialized() : FALSE);
}

BOOL CHEXDataView::IsEmpty() CONST
{
	CTextViewLock  cLock(m_pwndView);

	return((!m_pwndView->GetTextCount()) ? TRUE : FALSE);
}

BOOL CHEXDataView::GetPrintProperties(CString &szTitle, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, LOGFONT *pTitleFont, LOGFONT *pContentsFont) CONST
{
	CTextViewLock  cLock(m_pwndView);

	return((GetTitle(szTitle) && m_pwndView->GetColumns(szColumns) && m_pwndView->GetContent(szContents, pAttributes) && m_pwndView->GetTitleFont(pTitleFont) && m_pwndView->GetTextFont(pContentsFont)) ? TRUE : FALSE);
}

VOID CHEXDataView::SetTrackSize(CONST SIZE &size)
{
	CTextViewLock  cLock(m_pwndView);

	m_sizeTrackLayout = size;
}

CSize CHEXDataView::GetTrackSize() CONST
{
	CTextViewLock  cLock(m_pwndView);

	return m_sizeTrackLayout;
}

BOOL CHEXDataView::AdjustColumns()
{
	CDC  *pDC;
	INT  nType;
	INT  nLine;
	INT  nLines;
	INT  nDigit;
	INT  nWidth;
	INT  nOffset;
	INT  nColumn;
	INT  nColumns;
	CFont  cFont;
	CFont  *pOldFont;
	CString  szLine;
	CString  szDigit;
	CString  szColumn;
	CUIntArray  nWidths[2];
	CStringArray  szDumpText;
	CStringArray  szColumns[2];
	CStringTools  cStringTools;
	CTextViewAttribute  *pAttribute;
	CTextViewAttributes  pAttributes;
	CTextViewLock  cLock(m_pwndView);

	if ((pDC = (IsWindow(GetSafeHwnd())) ? GetDC() : (CDC *)NULL))
	{
		if ((pOldFont = (GetTextFont(&cFont)) ? pDC->SelectObject(&cFont) : (CFont *)NULL))
		{
			if ((nType = HIWORD(GetParent()->GetType())) == HEX_TYPE_NORMAL || nType == HEX_TYPE_STREAM || !nType)
			{
				for (nDigit = 0, nWidth = 0; nDigit < 16; nDigit++)
				{
					szDigit = cStringTools.ConvertIntToString(nDigit, 16);
					nWidth = max(pDC->GetTextExtent(CString(szDigit.GetAt(0), 4)).cx, nWidth);
				}
				for (nColumn = 0, nColumns = (m_nLayoutLineNumbers[1] > 0) ? ((m_nLayoutLineLength + 1) / 2 + 1) : ((m_nLayoutLineLength + 1) / 2); nColumn < nColumns; nColumn++)
				{
					nWidths[0].Add((nColumn > 0) ? (nWidths[0].GetAt(nColumn - 1) + LOWORD(m_pwndView->GetTextIndents()) + 2 * GetSystemMetrics(SM_CXEDGE) + nWidth + HIWORD(m_pwndView->GetTextIndents())) : (2 * GetSystemMetrics(SM_CXEDGE) + LOWORD(m_pwndView->GetTextIndents()) + nWidth + HIWORD(m_pwndView->GetTextIndents())));
					szColumns[0].Add(EMPTYSTRING);
				}
				for (nColumn = 0, nColumns = (m_pwndView->GetColumns(szColumns[1], nWidths[1])) ? ((nWidths[0].GetSize() == nWidths[1].GetSize()) ? (INT)nWidths[0].GetSize() : -1) : -1; nColumn < nColumns; nColumn++)
				{
					if (nWidths[0].GetAt(nColumn) != nWidths[1].GetAt(nColumn)) break;
					continue;
				}
				if (nColumn != nColumns)
				{
					for (nColumn = 0, nColumns = (m_pwndView->SetColumns(szColumns[0], nWidths[0])) ? (INT)nWidths[0].GetSize() : -1; nColumn < nColumns; nColumn++)
					{
						if (m_pwndView->SetColumnFormat(nColumn, (!nColumn  &&  m_nLayoutLineNumbers[1] > 0) ? ((m_pwndView->GetColumnFormat(nColumn) & ~(DT_LEFT | DT_CENTER)) | DT_RIGHT | DT_SINGLELINE) : ((m_pwndView->GetColumnFormat(nColumn) & ~(DT_CENTER | DT_RIGHT)) | DT_LEFT | DT_SINGLELINE))) continue;
						break;
					}
				}
				if (nColumn == nColumns || nColumns < 0)
				{
					for (nColumn = nOffset = (m_nLayoutLineNumbers[1] > 0) ? 1 : 0, nColumns = (nType == HEX_TYPE_NORMAL || nType == HEX_TYPE_STREAM) ? ((m_nLayoutLineNumbers[0] > 0) ? m_pwndView->GetColumnCount() : 0) : 0; nColumn < nColumns; nColumn++)
					{
						if ((nColumn - nOffset) % m_nLayoutLineNumbers[0] == 0 || m_nLayoutLineNumbers[0] == 1)
						{
							szColumn = cStringTools.ConvertIntToString(2 * (nColumn - nOffset));
							szLine += (m_nLayoutLineNumbers[1] > 0 || !szLine.IsEmpty()) ? (CTextView::GetColumnDelimiter() + szColumn) : szColumn;
							continue;
						}
						szLine += (nColumn < nColumns - 1) ? CTextView::GetColumnDelimiter() : EOS;
					}
					if ((pAttribute = new CTextViewAttribute))
					{
						for (pAttribute->SetColumnColor(-1, m_nLayoutColors.GetAt(HEX_LAYOUTCOLOR_ENUMERATIONS)); !nColumns || ((!m_pwndView->GetTextCount() && m_pwndView->InsertText(0, szLine, pAttribute)) || (m_pwndView->GetTextCount() > 0 && m_pwndView->SetText(0, szLine, pAttribute))); )
						{
							pDC->SelectObject(pOldFont);
							delete pAttribute;
							ReleaseDC(pDC);
							return TRUE;
						}
						delete pAttribute;
					}
					pDC->SelectObject(pOldFont);
					ReleaseDC(pDC);
					return FALSE;
				}
			}
			if (nType == HEX_TYPE_DUMPS)
			{
				for (nLine = 0, nLines = (m_pwndView->GetContent(szDumpText, pAttributes)) ? (INT)szDumpText.GetSize() : 0, nWidth = 0; nLine < nLines; nLine++)
				{
					nWidth = max(LOWORD(m_pwndView->GetTextIndents()) + pDC->GetTextExtent(szDumpText.GetAt(nLine)).cx + HIWORD(m_pwndView->GetTextIndents()), nWidth);
					continue;
				}
				for (szColumns[0].InsertAt(0, EMPTYSTRING), nWidths[0].InsertAt(0, nWidth), szColumns[0].SetSize(1), nWidths[0].SetSize(1), m_pwndView->SetColumnFormat(0, (m_pwndView->GetColumnFormat(0) & ~(DT_CENTER | DT_RIGHT)) | DT_LEFT | DT_SINGLELINE); m_pwndView->SetColumns(szColumns[0], nWidths[0]); )
				{
					pDC->SelectObject(pOldFont);
					ReleaseDC(pDC);
					return TRUE;
				}
				return TRUE;

			}
			pDC->SelectObject(pOldFont);
		}
		ReleaseDC(pDC);
	}
	return FALSE;
}

CHEXWnd *CHEXDataView::GetParent() CONST
{
	return((CHEXWnd *)m_pParentWnd);
}

BOOL CHEXDataView::ShowRawData(CONST CTMUnit &cTMUnit)
{
	INT  nByte;
	INT  nLine;
	INT  nBytes;
	INT  nLines;
	INT  nOffset;
	INT  nColumn;
	INT  nColumns;
	BYTE  nValue;
	CString  szByte;
	CString  szLine;
	CStringTools  cStringTools;
	CTextViewAttribute  *pAttribute;

	if ((pAttribute = new CTextViewAttribute))
	{
		for (nColumn = 0, nColumns = m_pwndView->GetColumnCount(); nColumn < nColumns; nColumn++)
		{
			pAttribute->SetColumnColor(nColumn, (!nColumn  &&  m_nLayoutLineNumbers[1] > 0) ? m_nLayoutColors.GetAt(HEX_LAYOUTCOLOR_ENUMERATIONS) : m_nLayoutColors.GetAt(HEX_LAYOUTCOLOR_RAWDATA));
			continue;
		}
		for (nByte = 0, nBytes = (!cTMUnit.GetSize()) ? ((m_nLayoutLineNumbers[0] > 0) ? ((m_pwndView->GetTextCount() - 1)*m_nLayoutLineLength) : (m_pwndView->GetTextCount()*m_nLayoutLineLength)) : cTMUnit.GetSize(), nLine = nOffset = (m_nLayoutLineNumbers[0] > 0) ? 1 : 0, szLine.Empty(); nByte <= nBytes; nByte++)
		{
			if ((nByte%m_nLayoutLineLength == 0 && nByte > 0) || nByte == nBytes)
			{
				if (nLine < m_pwndView->GetTextCount() && !m_pwndView->SetText(nLine, szLine, pAttribute, ((nByte == nBytes  &&  nLine == m_pwndView->GetTextCount() - 1) || !cTMUnit.GetSize()) ? TRUE : FALSE)) break;
				if (nLine > m_pwndView->GetTextCount() - 1 && !m_pwndView->InsertText(nLine, szLine, pAttribute, (nByte == nBytes) ? TRUE : FALSE)) break;
			}
			if (nByte < nBytes)
			{
				if (nByte%m_nLayoutLineLength == 0)
				{
					nLine = (nByte > 0) ? (nLine + 1) : nLine;
					szByte = cStringTools.ConvertIntToString(nLine - nOffset);
					szLine = (m_nLayoutLineNumbers[1] > 0 && ((nLine - nOffset) % m_nLayoutLineNumbers[1] == 0 || m_nLayoutLineNumbers[1] == 1)) ? (LPCTSTR)szByte : EMPTYSTRING;
				}
				if (!cTMUnit.GetData(nByte, nValue))
				{
					szByte = SPACE;
					szByte += SPACE;
					szLine += ((nByte%m_nLayoutLineLength == 0 && m_nLayoutLineNumbers[1] > 0) || (nByte%m_nLayoutLineLength  &&  szLine.GetLength() > szByte.GetLength() && szLine.GetAt(szLine.GetLength() - szByte.GetLength() - 1) != CTextView::GetColumnDelimiter())) ? (CTextView::GetColumnDelimiter() + szByte) : szByte;
					continue;
				}
				szByte = cStringTools.ConvertUIntToPaddedString(nValue, 2, 16);
				szLine += ((nByte%m_nLayoutLineLength == 0 && m_nLayoutLineNumbers[1] > 0) || (nByte%m_nLayoutLineLength  &&  szLine.GetLength() > szByte.GetLength() && szLine.GetAt(szLine.GetLength() - szByte.GetLength() - 1) != CTextView::GetColumnDelimiter())) ? (CTextView::GetColumnDelimiter() + szByte) : szByte;
			}
		}
		for (nLines = m_pwndView->GetTextCount() - 1; nLine < nLines; nLines--)
		{
			if (m_pwndView->DeleteText(nLines, (nLine == nLines - 1) ? TRUE : FALSE)) continue;
			break;
		}
		if (nByte > nBytes)
		{
			delete pAttribute;
			return TRUE;
		}
		delete pAttribute;
	}
	return FALSE;
}

BOOL CHEXDataView::ShowDumpData(LPCTSTR pszDump, BOOL bReset)
{
	INT  nPos;
	INT  nLine;
	INT  nLines;
	INT  nColumn;
	INT  nColumns;
	CString  szLine;
	CStringArray  szLines;
	CTextViewAttribute  *pAttribute;
	CTextViewAttributes  pAttributes;

	if ((pAttribute = new CTextViewAttribute))
	{
		for (nColumn = 0, nColumns = m_pwndView->GetColumnCount(); nColumn < nColumns; nColumn++)
		{
			pAttribute->SetColumnColor(nColumn, m_nLayoutColors.GetAt(HEX_LAYOUTCOLOR_NORMALDATA));
			continue;
		}
		if (!pszDump)
		{
			for (nLine = 0, nLines = (!bReset) ? m_pwndView->GetTextCount() : 0; nLine < nLines; nLine++)
			{
				m_pwndView->GetText(nLine, szLine);
				m_pwndView->SetText(nLine, szLine, pAttribute, (nLine == nLines - 1) ? TRUE : FALSE);
			}
			if (!bReset)
			{
				delete pAttribute;
				AdjustColumns();
				return TRUE;
			}
			m_pwndView->DeleteAllText();
			delete pAttribute;
			AdjustColumns();
			return TRUE;
		}
		for (nLine = 0, szLine = pszDump; !szLine.IsEmpty(); nLine++)
		{
			szLines.Add(((nPos = szLine.Find(CR)) < 0) ? (((nPos = szLine.Find(EOL)) >= 0) ? szLine.Left(nPos) : szLine) : szLine.Left(nPos));
			szLine = (nPos >= 0) ? ((szLine[nPos] == CR) ? ((szLine[++nPos] == EOL) ? (LPCTSTR)szLine.Mid(nPos + 1) : (LPCTSTR)szLine.Mid(nPos)) : (LPCTSTR)szLine.Mid(nPos + 1)) : EMPTYSTRING;
			pAttributes.Add(pAttribute);
		}
		if (m_pwndView->SetContent(szLines, pAttributes))
		{
			pAttributes.CPtrArray::RemoveAll();
			delete pAttribute;
			AdjustColumns();
			return TRUE;
		}
		pAttributes.CPtrArray::RemoveAll();
		delete pAttribute;
		AdjustColumns();
	}
	return FALSE;
}

VOID CHEXDataView::RecalcLayout()
{
	CDC  *pDC;
	CRect  rView;
	CFont  cFont;
	CFont  *pOldFont;
	HDITEM  sHeaderItem;
	TEXTMETRIC  tmFont;
	CTextViewLock  cLock(m_pwndView);

	if ((pDC = (IsWindow(GetSafeHwnd())) ? GetDC() : (CDC *)NULL))
	{
		if ((pOldFont = (GetTitleFont(&cFont)) ? pDC->SelectObject(&cFont) : (CFont *)NULL))
		{
			for (GetClientRect(rView), sHeaderItem.mask = HDI_WIDTH, sHeaderItem.cxy = rView.Width() + GetSystemMetrics(SM_CXEDGE); pDC->GetTextMetrics(&tmFont); )
			{
				for (m_pwndHeaderCtrl->MoveWindow(CRect(rView.left, rView.top, rView.right, rView.top + 2 * (GetSystemMetrics(SM_CYEDGE) + GetSystemMetrics(SM_CYBORDER)) + tmFont.tmHeight)), m_pwndView->MoveWindow(CRect(rView.left, rView.top + 2 * (GetSystemMetrics(SM_CYEDGE) + GetSystemMetrics(SM_CYBORDER)) + tmFont.tmHeight + 1, rView.right, rView.bottom)); m_pwndHeaderCtrl->GetItemCount() > 0; )
				{
					m_pwndHeaderCtrl->SetItem(0, &sHeaderItem);
					break;
				}
				SetTrackSize(CSize(m_pwndView->GetTrackSize().cx, m_pwndView->GetTrackSize().cy + 2 * (GetSystemMetrics(SM_CYEDGE) + GetSystemMetrics(SM_CYBORDER)) + tmFont.tmHeight));
				break;
			}
			pDC->SelectObject(pOldFont);
		}
		ReleaseDC(pDC);
	}
}

BOOL CHEXDataView::Lock()
{
	return m_pwndView->Lock();
}

BOOL CHEXDataView::Unlock()
{
	return m_pwndView->Unlock();
}

void CHEXDataView::PostNcDestroy()
{
	m_cLayout.Empty();
	m_nLayoutColors.RemoveAll();
	CWnd::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CHEXDataView, CWnd)
	//{{AFX_MSG_MAP(CHEXDataView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHEXDataView message handlers

int CHEXDataView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	return((CWnd::OnCreate(lpCreateStruct) != -1 && m_pwndHeaderCtrl->Create(this, CCS_TOP | WS_CHILD | WS_VISIBLE | WS_DISABLED, 0) && m_pwndView->Create(this, CRect(0, 0, 0, 0), TVS_NOSELECTION | TVS_HSCROLL | TVS_VSCROLL | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE)) ? 0 : -1);
}

void CHEXDataView::OnSize(UINT nType, int cx, int cy)
{
	RecalcLayout();
	CWnd::OnSize(nType, cx, cy);
}

void CHEXDataView::OnSetFocus(CWnd *pOldWnd)
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
// CHEXSpyView

IMPLEMENT_DYNCREATE(CHEXSpyView, CTextView)

CHEXSpyView::CHEXSpyView() : CTextView()
{
	m_bBadDataMode = FALSE;
}

BOOL CHEXSpyView::Create(CWnd *pParentWnd)
{
	CStringArray  szColumns;

	if (CTextView::Create(pParentWnd, CRect(0, 0, 0, 0), TVS_HEADER | TVS_TOP | TVS_HSCROLL | TVS_VSCROLL | TVS_NOSELECTION | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE))
	{
		szColumns.Add(STRING(IDS_HEX_SPYHEADER_DESCRIPTION));
		szColumns.Add(STRING(IDS_HEX_SPYHEADER_VALUE));
		szColumns.Add(STRING(IDS_HEX_SPYHEADER_POSITION));
		return SetColumns(szColumns);
	}
	return FALSE;
}

BOOL CHEXSpyView::SetLayout(LPCTSTR pszLayout)
{
	CTextViewLock  cLock(this);

	m_szLayout = pszLayout;
	return TRUE;
}

BOOL CHEXSpyView::GetLayout(CString &szLayout) CONST
{
	CTextViewLock  cLock(this);

	szLayout = m_szLayout;
	return TRUE;
}

BOOL CHEXSpyView::SetLayoutContents(CONST CHEXSpyLocations &pSpyLocations)
{
	INT  nColumn;
	INT  nColumns;
	INT  nLocation;
	INT  nLocations;
	UINT  nPosition[3];
	COLORREF  nColor[2];
	CString  szPosition;
	CString  szDescription;
	CStringArray  szColumns;
	CHEXSpyLocation  *pLocation;
	CTextViewAttribute  *pAttribute;
	CTextViewLock  cLock(this);

	if (!IsWindow(GetSafeHwnd()))
	{
		m_pSpyLocations.Copy(&pSpyLocations);
		return TRUE;
	}
	if (!m_pSpyLocations.Compare(&pSpyLocations) || !GetTextCount())
	{
		for (nLocation = 0, nLocations = (m_pSpyLocations.Copy(&pSpyLocations) && GetColumns(szColumns)) ? (INT)m_pSpyLocations.GetSize() : -1, DeleteAllText(FALSE); nLocation < nLocations; nLocation++)
		{
			if ((pLocation = m_pSpyLocations.GetAt(nLocation)))
			{
				szDescription = pLocation->GetName();
				nColor[0] = pLocation->GetDetailsColor();
				nColor[1] = pLocation->GetValueColor();
				pLocation->GetPosition(nPosition[0], nPosition[1], nPosition[2]);
				if ((pAttribute = new CTextViewAttribute) != (CTextViewAttribute *)NULL)
				{
					for (nColumn = 0, nColumns = (INT)szColumns.GetSize(); nColumn < nColumns; nColumn++)
					{
						pAttribute->SetColumnColor(nColumn, (szColumns.GetAt(nColumn) == STRING(IDS_HEX_SPYHEADER_DESCRIPTION) || szColumns.GetAt(nColumn) == STRING(IDS_HEX_SPYHEADER_POSITION)) ? nColor[0] : nColor[1]);
						continue;
					}
					szPosition.Format(STRING(IDS_HEX_SPYLOCATION_FORMAT), nPosition[0], nPosition[1], nPosition[2]);
					if (InsertText(nLocation, szDescription + GetColumnDelimiter() + GetColumnDelimiter() + szPosition, pAttribute, (nLocation == nLocations - 1) ? TRUE : FALSE))
					{
						delete pAttribute;
						continue;
					}
					delete pAttribute;
				}
			}
			DeleteAllText();
			break;
		}
		if (nLocation == nLocations)
		{
			AdjustColumns();
			SetCurText(0);
			Update();
			return TRUE;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CHEXSpyView::GetLayoutContents(CHEXSpyLocations &pSpyLocations) CONST
{
	CTextViewLock  cLock(this);

	return pSpyLocations.Copy(&m_pSpyLocations);
}

BOOL CHEXSpyView::SetTitleFont(CFont *pFont)
{
	LOGFONT  lfFont;

	return((pFont->GetLogFont(&lfFont) > 0) ? SetTitleFont(&lfFont) : FALSE);
}
BOOL CHEXSpyView::SetTitleFont(CONST LOGFONT *plfFont)
{
	LOGFONT  lfFont;
	CTextViewLock  cLock(this);

	if (!GetTitleFont(&lfFont) || memcmp(plfFont, &lfFont, sizeof(LOGFONT)))
	{
		if (CTextView::SetTitleFont(plfFont))
		{
			AdjustColumns();
			return TRUE;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CHEXSpyView::SetTextFont(CFont *pFont)
{
	LOGFONT  lfFont;

	return((pFont->GetLogFont(&lfFont) > 0) ? SetTextFont(&lfFont) : FALSE);
}
BOOL CHEXSpyView::SetTextFont(CONST LOGFONT *plfFont)
{
	LOGFONT  lfFont;
	CTextViewLock  cLock(this);

	if (!GetTextFont(&lfFont) || memcmp(plfFont, &lfFont, sizeof(LOGFONT)))
	{
		if (CTextView::SetTextFont(plfFont))
		{
			AdjustColumns();
			Update();
			return TRUE;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CHEXSpyView::EnableBadDataMode(BOOL bEnable)
{
	m_bBadDataMode = bEnable;
	return TRUE;
}

BOOL CHEXSpyView::IsBadDataModeEnabled() CONST
{
	return m_bBadDataMode;
}

BOOL CHEXSpyView::Initialize()
{
	INT  nType;
	CTextViewLock  cLock(this);

	if ((nType = HIWORD(GetParent()->GetType())) == HEX_TYPE_NORMAL)
	{
		if (((GetParent()->GetMode() == DISPLAY_MODE_REALTIME  &&  InitializeTMUnit(m_szLayout, m_pLayoutData, IsBadDataModeEnabled())) || (GetParent()->GetMode() == DISPLAY_MODE_HISTORY  &&  GetParent()->InitializeTMData(m_szLayout, m_pLayoutData, IsBadDataModeEnabled()))) && ShowRawData(m_pLayoutData)) return TRUE;
		m_pLayoutData.Reset();
		return TRUE;
	}
	if (nType == HEX_TYPE_STREAM)
	{
		if (((GetParent()->GetMode() == DISPLAY_MODE_REALTIME  &&  InitializeTMUnit(m_pLayoutData, IsBadDataModeEnabled())) || (GetParent()->GetMode() == DISPLAY_MODE_HISTORY  &&  GetParent()->InitializeTMData(m_pLayoutData, IsBadDataModeEnabled()))) && ShowRawData(m_pLayoutData)) return TRUE;
		m_pLayoutData.Reset();
		return TRUE;
	}
	return((nType == HEX_TYPE_DUMPS) ? TRUE : FALSE);
}

BOOL CHEXSpyView::Update(CTMEnvironment *pTMEnvironment)
{
	CTextViewLock  cLock(this);

	if (IsInitialized())
	{
		if (pTMEnvironment != (CTMEnvironment *)NULL)
		{
			if (!pTMEnvironment->GetTMUnit()->IsValid() || !pTMEnvironment->GetTMUnit()->HasBadData() || IsBadDataModeEnabled())
			{
				m_pLayoutData.Copy(pTMEnvironment->GetTMUnit());
				return ShowRawData(m_pLayoutData);
			}
			return FALSE;
		}
		return ShowRawData(m_pLayoutData);
	}
	return FALSE;
}

VOID CHEXSpyView::Reset(CTMEnvironment *pTMEnvironment)
{
	CTextViewLock  cLock(this);

	m_pLayoutData.Reset();
	Update(pTMEnvironment);
}

BOOL CHEXSpyView::IsInitialized() CONST
{
	CTextViewLock  cLock(this);

	return((IsWindow(GetSafeHwnd())) ? GetParent()->IsInitialized() : FALSE);
}

BOOL CHEXSpyView::GetPrintProperties(CString &szTitle, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, LOGFONT *pTitleFont, LOGFONT *pContentsFont) CONST
{
	CTextViewLock  cLock(this);

	if (GetColumns(szColumns) && GetContent(szContents, pAttributes) && GetTitleFont(pTitleFont) && GetTextFont(pContentsFont))
	{
		szTitle = STRING(IDS_HEX_TITLEITEM_SPY);
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXSpyView::AdjustColumns()
{
	CTextViewLock  cLock(this);

	return AdjustColumns(m_pSpyLocations);
}
BOOL CHEXSpyView::AdjustColumns(CONST CHEXSpyLocations &pSpyLocations)
{
	CDC  *pDC;
	INT  nColumn;
	INT  nColumns;
	INT  nLocation;
	INT  nLocations;
	INT  nWidth[3];
	UINT  nPosition[3];
	CFont  *pOldFont;
	CString  szNumber;
	CString  szPosition;
	CUIntArray  nWidths;
	CStringArray  szColumns;
	CStringTools  cStringTools;
	CHEXSpyLocation  *pLocation;
	CTextViewLock  cLock(this);

	if ((pDC = (IsWindow(GetSafeHwnd())) ? GetDC() : (CDC *)NULL))
	{
		if ((pOldFont = pDC->SelectObject(&m_wndHeaderCtrl.m_cFont)))
		{
			for (nColumn = 0, nColumns = (GetColumns(szColumns, nWidths)) ? (INT)szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
			{
				nWidth[0] = (szColumns.GetAt(nColumn) == STRING(IDS_HEX_SPYHEADER_DESCRIPTION) || szColumns.GetAt(nColumn) == STRING(IDS_HEX_SPYHEADER_VALUE)) ? (LOWORD(GetTextIndents()) + 3 * pDC->GetTextExtent(szColumns.GetAt(nColumn)).cx + HIWORD(GetTextIndents())) : (LOWORD(GetTextIndents()) + pDC->GetTextExtent(szColumns.GetAt(nColumn)).cx + HIWORD(GetTextIndents()));
				nWidths.SetAt(nColumn, (nColumn > 0) ? (nWidths.GetAt(nColumn - 1) + nWidth[0]) : nWidth[0]);
			}
			if (nColumn != nColumns)
			{
				szColumns.RemoveAll();
				nWidths.RemoveAll();
			}
			pDC->SelectObject(pOldFont);
		}
		if ((pOldFont = pDC->SelectObject(&m_wndContentCtrl.m_cFont)))
		{
			for (nLocation = 0, nLocations = (nColumn == nColumns) ? (INT)pSpyLocations.GetSize() : -1; nLocation < nLocations; nLocation++)
			{
				for (nColumn = 0, nColumns = ((pLocation = pSpyLocations.GetAt(nLocation))) ? (INT)szColumns.GetSize() : -1, nWidth[2] = 0; nColumn < nColumns; nColumn++)
				{
					if (szColumns.GetAt(nColumn) == STRING(IDS_HEX_SPYHEADER_DESCRIPTION))
					{
						nWidth[0] = 2 * GetSystemMetrics(SM_CXEDGE) + LOWORD(GetTextIndents()) + pDC->GetTextExtent(pLocation->GetName()).cx + HIWORD(GetTextIndents());
						nWidth[1] = (nColumn > 0) ? (nWidth[0] - nWidths.GetAt(nColumn) - nWidth[2] + nWidths.GetAt(nColumn - 1)) : (nWidth[0] - nWidths.GetAt(nColumn));
						nWidths.SetAt(nColumn, (nColumn > 0) ? (nWidths.GetAt(nColumn - 1) + max(nWidth[0], (INT)(nWidths.GetAt(nColumn) + nWidth[2] - nWidths.GetAt(nColumn - 1)))) : max(nWidth[0], (INT)nWidths.GetAt(nColumn)));
						nWidth[2] += (nWidth[1] > 0) ? nWidth[1] : 0;
					}
					if (szColumns.GetAt(nColumn) == STRING(IDS_HEX_SPYHEADER_VALUE))
					{
						if (pLocation->GetPosition(nPosition[0], nPosition[1], nPosition[2]))
						{
							szNumber = cStringTools.ConvertUIntToString((1 << (nPosition[2] - 1)) + (1 << (nPosition[2] - 1)) - 1, pLocation->GetCoding());
							szNumber = (pLocation->GetCoding() == HEXSPYLOCATION_CODING_BINARY) ? CString(cStringTools.ConvertIntToString(0).GetAt(0), szNumber.GetLength()) : szNumber;
							nWidth[0] = 2 * GetSystemMetrics(SM_CXEDGE) + LOWORD(GetTextIndents()) + pDC->GetTextExtent(szNumber).cx + HIWORD(GetTextIndents());
							nWidth[1] = (nColumn > 0) ? (nWidth[0] - nWidths.GetAt(nColumn) - nWidth[2] + nWidths.GetAt(nColumn - 1)) : (nWidth[0] - nWidths.GetAt(nColumn));
							nWidths.SetAt(nColumn, (nColumn > 0) ? (nWidths.GetAt(nColumn - 1) + max(nWidth[0], (INT)(nWidths.GetAt(nColumn) + nWidth[2] - nWidths.GetAt(nColumn - 1)))) : max(nWidth[0], (INT)nWidths.GetAt(nColumn)));
							nWidth[2] += (nWidth[1] > 0) ? nWidth[1] : 0;
						}
					}
					if (szColumns.GetAt(nColumn) == STRING(IDS_HEX_SPYHEADER_POSITION))
					{
						if (pLocation->GetPosition(nPosition[0], nPosition[1], nPosition[2]))
						{
							szPosition.Format(STRING(IDS_HEX_SPYLOCATION_FORMAT), nPosition[0], nPosition[1], nPosition[2]);
							nWidth[0] = 2 * GetSystemMetrics(SM_CXEDGE) + LOWORD(GetTextIndents()) + pDC->GetTextExtent(szPosition).cx + HIWORD(GetTextIndents());
							nWidth[1] = (nColumn > 0) ? (nWidth[0] - nWidths.GetAt(nColumn) - nWidth[2] + nWidths.GetAt(nColumn - 1)) : (nWidth[0] - nWidths.GetAt(nColumn));
							nWidths.SetAt(nColumn, (nColumn > 0) ? (nWidths.GetAt(nColumn - 1) + max(nWidth[0], (INT)(nWidths.GetAt(nColumn) + nWidth[2] - nWidths.GetAt(nColumn - 1)))) : max(nWidth[0], (INT)nWidths.GetAt(nColumn)));
							nWidth[2] += (nWidth[1] > 0) ? nWidth[1] : 0;
						}
					}
				}
				if (nColumn != nColumns) break;
			}
			if (nLocation != nLocations)
			{
				szColumns.RemoveAll();
				nWidths.RemoveAll();
			}
			pDC->SelectObject(pOldFont);
		}
		if (szColumns.GetSize() > 0 && szColumns.GetSize() == nWidths.GetSize())
		{
			if (SetColumns(szColumns, nWidths))
			{
				ReleaseDC(pDC);
				return TRUE;
			}
		}
		ReleaseDC(pDC);
	}
	return FALSE;
}

CHEXWnd *CHEXSpyView::GetParent() CONST
{
	return((CHEXWnd *)CTextView::GetParent());
}

BOOL CHEXSpyView::ShowRawData(CONST CTMUnit &cTMUnit)
{
	INT  nColumn;
	INT  nColumns;
	INT  nLocation;
	INT  nLocations;
	BOOL  bSpyValue;
	UINT  nPosition[3];
	CString  szSpyValue[3];
	ULONGLONG  nSpyValue;
	CStringArray  szColumns;
	CStringTools  cStringTools;
	CHEXSpyLocation  *pLocation;

	for (nColumn = 0, nColumns = (GetColumns(szColumns)) ? (INT)szColumns.GetSize() : -1; nColumn < nColumns; nColumn++)
	{
		if (szColumns.GetAt(nColumn) == STRING(IDS_HEX_SPYHEADER_VALUE)) break;
		continue;
	}
	for (nLocation = 0, nLocations = (nColumn < nColumns) ? (INT)m_pSpyLocations.GetSize() : -1, szSpyValue[0].Empty(), szSpyValue[1].Empty(), szSpyValue[2].Empty(); nLocation < nLocations; nLocation++, szSpyValue[0].Empty(), szSpyValue[1].Empty(), szSpyValue[2].Empty())
	{
		if ((pLocation = m_pSpyLocations.GetAt(nLocation)) && pLocation->GetPosition(nPosition[0], nPosition[1], nPosition[2]))
		{
			bSpyValue = m_pLayoutData.GetData(nPosition[0], nPosition[1], nPosition[2], nSpyValue);
			szSpyValue[0] = cStringTools.ConvertLongUIntToString(nSpyValue, pLocation->GetCoding());
			szSpyValue[1] = cStringTools.ConvertLongUIntToPaddedString(nSpyValue, nPosition[2], pLocation->GetCoding());
			SetText(nLocation, nColumn, (bSpyValue) ? ((pLocation->GetCoding() != HEXSPYLOCATION_CODING_BINARY) ? szSpyValue[0] : szSpyValue[1]) : szSpyValue[2]);
			continue;
		}
		break;
	}
	return((nLocation == nLocations) ? TRUE : FALSE);
}

CString CHEXSpyView::ConvertText(INT nColumn, LPCTSTR pszText, LPCTSTR pszValue) CONST
{
	INT  nPos[2];
	INT  nColumns;
	CString  szText;

	for (szText = pszText, nColumns = nColumn, nPos[0] = 0; nColumns > 0; nColumns--)
	{
		nPos[0] = ((nPos[1] = szText.Mid(nPos[0]).Find(GetColumnDelimiter())) >= 0) ? (nPos[1] + 1) : nPos[0];
		continue;
	}
	return(((nPos[1] = szText.Mid(nPos[0]).Find(GetColumnDelimiter())) >= 0) ? (szText.Left(nPos[0]) + pszValue + szText.Mid(nPos[0] + nPos[1])) : (szText.Left(nPos[0]) + pszValue));
}

void CHEXSpyView::PostNcDestroy()
{
	m_pSpyLocations.RemoveAll();
	CTextView::PostNcDestroy();
}

BOOL CHEXSpyView::Lock()
{
	return((IsWindow(GetSafeHwnd())) ? (GetParent()->Lock() && CTextView::Lock()) : CTextView::Lock());
}

BOOL CHEXSpyView::Unlock()
{
	return((IsWindow(GetSafeHwnd())) ? (CTextView::Unlock() && GetParent()->Unlock()) : CTextView::Unlock());
}

BEGIN_MESSAGE_MAP(CHEXSpyView, CTextView)
	//{{AFX_MSG_MAP(CHEXSpyView)
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHEXSpyView message handlers

BOOL CHEXSpyView::OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message)
{
	LONG  lDataFlag;
	POINT  ptCursor;
	CRect  rContent;
	CTextViewLock  cLock(this);

	for (GetCursorPos(&ptCursor), m_wndContentCtrl.ScreenToClient(&ptCursor), m_wndContentCtrl.GetClientRect(rContent); rContent.PtInRect(ptCursor); )
	{
		if ((lDataFlag = GetParent()->IsRetrievingData()) && HIWORD(lDataFlag))
		{
			SetCursor(LoadCursor((HINSTANCE)NULL, IDC_WAIT));
			return TRUE;
		}
		break;
	}
	return CTextView::OnSetCursor(pWnd, nHitTest, message);
}

BOOL CHEXSpyView::OnContentMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
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
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CHEXWnd

IMPLEMENT_DYNAMIC(CHEXWnd, CDisplayWnd)

CHEXWnd::CHEXWnd() : CDisplayWnd()
{
	SetType(DISPLAY_TYPE_HEX);
	InitializeViews();
	SetRetrieveMode();
	SetRetrieveSpeed();
	SetRetrieveInterval();
	SetRetrieveStartTime();
	SetRetrieveStopTime();
	SetUpdateInfo();
}

BOOL CHEXWnd::Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszTitle, PDISPLAYINFO pDefaultInfo, BOOL bDefault)
{
	if (CDisplayWnd::Create(pParentWnd, (!pszTitle) ? STRING(IDS_DISPLAY_TITLE_HEX) : pszTitle, pDefaultInfo->rWnd, IDR_HEXFRAME))
	{
		if (SetScope(pDefaultInfo->nScope) && SetMode(pDefaultInfo->nMode) && Customize(bDefault)) return TRUE;
		DestroyWindow();
	}
	return FALSE;
}

BOOL CHEXWnd::SetLayout(LPCTSTR pszLayout)
{
	return m_wndDataView.SetLayout(pszLayout) && m_wndSpyView.SetLayout(pszLayout);
}
BOOL CHEXWnd::SetLayout(LPCTSTR pszLayout, CONST CMemoryDump &cLayout)
{
	return m_wndDataView.SetLayout(pszLayout, cLayout) && m_wndSpyView.SetLayout(pszLayout);
}

BOOL CHEXWnd::GetLayout(CString &szLayout) CONST
{
	return m_wndDataView.GetLayout(szLayout);
}
BOOL CHEXWnd::GetLayout(CString &szLayout, CMemoryDump &cLayout) CONST
{
	return m_wndDataView.GetLayout(szLayout, cLayout);
}

BOOL CHEXWnd::SetLayoutContents(CONST CHEXSpyLocations &pSpyLocations)
{
	if (m_wndSpyView.SetLayoutContents(pSpyLocations))
	{
		m_bViews[1] = (pSpyLocations.GetSize() > 0) ? TRUE : FALSE;
		m_bViews[0] = TRUE;
		RepositionViews();
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXWnd::GetLayoutContents(CHEXSpyLocations &pSpyLocations) CONST
{
	return m_wndSpyView.GetLayoutContents(pSpyLocations);
}

BOOL CHEXWnd::SetLayoutFormat(UINT nHorzEnum, UINT nVertEnum, UINT nLineLength, CONST CUIntArray &nColors)
{
	return m_wndDataView.SetLayoutFormat(nHorzEnum, nVertEnum, nLineLength, nColors);
}

BOOL CHEXWnd::GetLayoutFormat(UINT &nHorzEnum, UINT &nVertEnum, UINT &nLineLength, CUIntArray &nColors) CONST
{
	return m_wndDataView.GetLayoutFormat(nHorzEnum, nVertEnum, nLineLength, nColors);
}

BOOL CHEXWnd::SetTitleFont(CFont *pFont)
{
	if (m_wndDataView.SetTitleFont(pFont))
	{
		RepositionViews();
		return TRUE;
	}
	return FALSE;
}
BOOL CHEXWnd::SetTitleFont(CONST LOGFONT *plfFont)
{
	if (m_wndDataView.SetTitleFont(plfFont))
	{
		RepositionViews();
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXWnd::GetTitleFont(CFont *pFont) CONST
{
	return m_wndDataView.GetTitleFont(pFont);
}
BOOL CHEXWnd::GetTitleFont(LOGFONT *plfFont) CONST
{
	return m_wndDataView.GetTitleFont(plfFont);
}

BOOL CHEXWnd::SetDataFont(CFont *pFont)
{
	return m_wndDataView.SetTextFont(pFont);
}
BOOL CHEXWnd::SetDataFont(CONST LOGFONT *plfFont)
{
	return m_wndDataView.SetTextFont(plfFont);
}

BOOL CHEXWnd::GetDataFont(CFont *pFont) CONST
{
	return m_wndDataView.GetTextFont(pFont);
}
BOOL CHEXWnd::GetDataFont(LOGFONT *plfFont) CONST
{
	return m_wndDataView.GetTextFont(plfFont);
}

BOOL CHEXWnd::SetSpyFont(CFont *pHeaderFont, CFont *pLocationsFont)
{
	if (m_wndSpyView.SetTitleFont(pHeaderFont) && m_wndSpyView.SetTextFont(pLocationsFont))
	{
		RepositionViews();
		return TRUE;
	}
	return FALSE;
}
BOOL CHEXWnd::SetSpyFont(CONST LOGFONT *plfHeaderFont, CONST LOGFONT *plfLocationsFont)
{
	if (m_wndSpyView.SetTitleFont(plfHeaderFont) && m_wndSpyView.SetTextFont(plfLocationsFont))
	{
		RepositionViews();
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXWnd::GetSpyFont(CFont *pFont, BOOL bHeader) CONST
{
	return((bHeader) ? m_wndSpyView.GetTitleFont(pFont) : m_wndSpyView.GetTextFont(pFont));
}
BOOL CHEXWnd::GetSpyFont(LOGFONT *plfHeaderFont, LOGFONT *plfLocationsFont) CONST
{
	return m_wndSpyView.GetTitleFont(plfHeaderFont) && m_wndSpyView.GetTextFont(plfLocationsFont);
}

BOOL CHEXWnd::EnableBadDataMode(BOOL bEnable)
{
	return m_wndDataView.EnableBadDataMode(bEnable) && m_wndSpyView.EnableBadDataMode(bEnable);
}

BOOL CHEXWnd::IsBadDataModeEnabled() CONST
{
	return m_wndDataView.IsBadDataModeEnabled();
}

BOOL CHEXWnd::Start()
{
	if (((GetMode() == DISPLAY_MODE_REALTIME  &&  ProcessRealtimeData()) || (GetMode() == DISPLAY_MODE_HISTORY  &&  StartRetrieveData())) && StartSchedulePrintJobs())
	{
		Initialize(TRUE);
		UpdateAllPanes();
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXWnd::Prepare(BOOL bDialog)
{
	INT  nResult;

	if (bDialog)
	{
		if ((nResult = m_dlgOpen.Create(this)) == IDCANCEL || nResult <= 0) MDIDestroy();
		return((nResult == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
	}
	return TRUE;
}

BOOL CHEXWnd::Initialize(BOOL bFlag)
{
	return CDisplayWnd::Initialize(bFlag);
}
BOOL CHEXWnd::Initialize(CTMEnvironment *pTMEnvironment)
{
	return CDisplayWnd::Initialize(pTMEnvironment);
}
BOOL CHEXWnd::Initialize(CString &szTag, CTimeTag &tTag)
{
	return CDisplayWnd::Initialize(szTag, tTag);
}

BOOL CHEXWnd::InitializeTMData(UINT nMode)
{
	for (StopRetrieveData(); (nMode == DISPLAY_MODE_REALTIME && SetMode(DISPLAY_MODE_REALTIME) && ProcessRealtimeData()) || (nMode == DISPLAY_MODE_HISTORY && SetMode(DISPLAY_MODE_HISTORY) && StartRetrieveData()); )
	{
		UpdateBars();
		return TRUE;
	}
	return FALSE;
}
BOOL CHEXWnd::InitializeTMData(CTMUnit &cTMUnit, BOOL bBadData)
{
	return((GetMode() == DISPLAY_MODE_HISTORY) ? ((!GetLink()) ? m_cRetrieveThread.InitializeTMUnit(cTMUnit, bBadData) : FALSE) : FALSE);
}
BOOL CHEXWnd::InitializeTMData(LPCTSTR pszTag, CTMUnit &cTMUnit, BOOL bBadData)
{
	return((GetMode() == DISPLAY_MODE_HISTORY) ? ((!GetLink()) ? m_cRetrieveThread.InitializeTMUnit(pszTag, cTMUnit, bBadData) : FALSE) : FALSE);
}
BOOL CHEXWnd::InitializeTMData(CTMParameters &pTMParameters, BOOL bBadData)
{
	CDisplayWnd  *pDisplayWnd;

	return((GetMode() == DISPLAY_MODE_HISTORY) ? (((pDisplayWnd = GetLink())) ? pDisplayWnd->InitializeTMData(pTMParameters, bBadData) : m_cRetrieveThread.InitializeTMData(pTMParameters, bBadData)) : GetTMService()->InitializeTMData(pTMParameters, bBadData));
}

BOOL CHEXWnd::Check() CONST
{
	return CheckAccountPrivilege(PRIVILEGE_HEX_USE);
}

VOID CHEXWnd::Update()
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
BOOL CHEXWnd::Update(CONST CTimeKey &tTimeKey, CTMEnvironment *pTMEnvironment, UINT nFlags)
{
	UINT  nStatus;
	BOOL  bSearch;
	WORD  wQuality;
	CString  szLayout;
	CString  szName[2];
	CString  szDump[2];
	CTimeTag  tDump[2];
	CByteArray  nDumpData;
	CMemoryDump  *pDump;
	CMemoryDump  cLayout;
	CFileFindEx  cFileFind;
	CDisplayLock  cLock(this);

	if (IsInitialized())
	{
		if (GetMode() != DISPLAY_MODE_REALTIME || pTMEnvironment->GetTMUnit()->IsValid() || nFlags != 0)
		{
			if (HIWORD(GetType()) == HEX_TYPE_NORMAL)
			{
				if ((nFlags & HISTORYFILE_SUCCESS) && (nFlags & HISTORYFILE_TMPARAMETERS))
				{
					if (GetLayout(szLayout) && pTMEnvironment->Initialize(szLayout, *pTMEnvironment->GetTMUnit(), IsBadDataModeEnabled()) && m_wndDataView.Update(pTMEnvironment) && m_wndSpyView.Update(pTMEnvironment))
					{
						SetUpdateInfo(EMPTYSTRING, (pTMEnvironment->GetTMUnit()->IsValid()) ? CTimeTag(tTimeKey) : 0, pTMEnvironment->GetTMUnit()->GetUnitID(), pTMEnvironment->GetTMUnit()->GetQuality());
						return TRUE;
					}
				}
				if (((nFlags & HISTORYFILE_SUCCESS) && (nFlags & HISTORYFILE_TMUNIT)) || !nFlags)
				{
					if (GetLayout(szLayout) && pTMEnvironment->GetTMUnit()->GetTag() == szLayout  &&  m_wndDataView.Update(pTMEnvironment) && m_wndSpyView.Update(pTMEnvironment))
					{
						SetUpdateInfo(pTMEnvironment->GetTMUnit()->GetTag(), (pTMEnvironment->GetTMUnit()->IsValid()) ? pTMEnvironment->GetTMUnit()->GetTimeTag() : 0, pTMEnvironment->GetTMUnit()->GetUnitID(), pTMEnvironment->GetTMUnit()->GetQuality());
						return TRUE;
					}
				}
				if ((nFlags & HISTORYFILE_SUCCESS) && !(nFlags & HISTORYFILE_TMUNIT) && !(nFlags & HISTORYFILE_TMPARAMETERS))
				{
					m_wndDataView.Update(pTMEnvironment);
					m_wndSpyView.Update(pTMEnvironment);
					SetUpdateInfo();
					return TRUE;
				}
				return FALSE;
			}
			if (HIWORD(GetType()) == HEX_TYPE_STREAM)
			{
				if ((nFlags & HISTORYFILE_SUCCESS) && (nFlags & HISTORYFILE_TMPARAMETERS))
				{
					if (pTMEnvironment->Initialize(*pTMEnvironment->GetTMUnit(), IsBadDataModeEnabled()) && m_wndDataView.Update(pTMEnvironment) && m_wndSpyView.Update(pTMEnvironment))
					{
						SetUpdateInfo(EMPTYSTRING, (pTMEnvironment->GetTMUnit()->IsValid()) ? pTMEnvironment->GetTMUnit()->GetTimeTag() : 0, pTMEnvironment->GetTMUnit()->GetUnitID(), pTMEnvironment->GetTMUnit()->GetQuality());
						return TRUE;
					}
				}
				if (((nFlags & HISTORYFILE_SUCCESS) && (nFlags & HISTORYFILE_TMUNIT)) || !nFlags)
				{
					if (m_wndDataView.Update(pTMEnvironment) && m_wndSpyView.Update(pTMEnvironment))
					{
						SetUpdateInfo(pTMEnvironment->GetTMUnit()->GetTag(), (pTMEnvironment->GetTMUnit()->IsValid()) ? pTMEnvironment->GetTMUnit()->GetTimeTag() : 0, pTMEnvironment->GetTMUnit()->GetUnitID(), pTMEnvironment->GetTMUnit()->GetQuality());
						return TRUE;
					}
				}
				if ((nFlags & HISTORYFILE_SUCCESS) && !(nFlags & HISTORYFILE_TMUNIT) && !(nFlags & HISTORYFILE_TMPARAMETERS))
				{
					m_wndDataView.Update(pTMEnvironment);
					m_wndSpyView.Update(pTMEnvironment);
					SetUpdateInfo();
					return TRUE;
				}
				return FALSE;
			}
			if (HIWORD(GetType()) == HEX_TYPE_DUMPS)
			{
				if (GetMode() == DISPLAY_MODE_REALTIME || (GetMode() == DISPLAY_MODE_HISTORY && (GetRetrieveMode() & HEX_RETRIEVE_REDODUMPS)))
				{
					if (GetMode() == DISPLAY_MODE_HISTORY && (((nFlags & HISTORYFILE_SUCCESS) && (nFlags & HISTORYFILE_TMUNIT)) || !nFlags) && pTMEnvironment->GetTMUnit()->IsValid())
					{
						if (GetMemoryDumpsService()->Update(pTMEnvironment, m_pMemoryDumps) == MEMORYDUMPS_SERVICE_ERROR)
						{
							StopRetrieveData();
							UpdateBars();
							return FALSE;
						}
					}
					if (((nFlags & HISTORYFILE_SUCCESS) && (nFlags & HISTORYFILE_TMUNIT)) || !nFlags)
					{
						if ((pDump = (m_wndDataView.GetLayout(szLayout, cLayout)) ? pTMEnvironment->GetMemoryDumps()->GetAt(pTMEnvironment->GetMemoryDumps()->Find(cLayout.GetName())) : (CMemoryDump *)NULL))
						{
							for (szDump[0] = pDump->GetDumpTag(), szDump[1] = cLayout.GetDumpTag(), tDump[0] = pDump->GetDumpTime(), tDump[1] = cLayout.GetDumpTime(), wQuality = pDump->GetDumpQuality(), nStatus = pDump->GetDumpStatus(), pDump->GetDumpData(nDumpData); (szDump[0] != szDump[1] || tDump[0] != tDump[1]) && (nStatus == MEMORYDUMP_STATUS_COMPLETE || nStatus == MEMORYDUMP_STATUS_INCOMPLETE) && m_wndDataView.Update(pTMEnvironment); )
							{
								SetUpdateInfo(szDump[0], tDump[0], -1, (LOBYTE(wQuality) & MEMORYDUMP_DATAQUALITY_GOOD) ? (WORD)(TMUNIT_DATAQUALITY_GOOD | TMUNIT_SEQUENCEQUALITY_GOOD | ((LOBYTE(wQuality) & MEMORYDUMP_TIMECORRELATION_GOOD) ? TMUNIT_TIMECORRELATION_GOOD : TMUNIT_TIMECORRELATION_BAD)) : (WORD)(TMUNIT_DATAQUALITY_BAD | ((LOBYTE(wQuality) & MEMORYDUMP_TIMECORRELATION_GOOD) ? TMUNIT_TIMECORRELATION_GOOD : TMUNIT_TIMECORRELATION_BAD)));
								return TRUE;
							}
							if (nStatus == MEMORYDUMP_STATUS_EMPTY)
							{
								if (szDump[0] != szDump[1] && !nDumpData.GetSize())
								{
									if (!m_wndDataView.IsEmpty() && m_wndDataView.Initialize(szDump[0], tDump[0], wQuality))
									{
										SetUpdateInfo(szDump[0], tDump[0], -1, wQuality);
										return FALSE;
									}
								}
							}
						}
					}
					return FALSE;
				}
				if (GetRetrieveDumpFileName(szName[0]))
				{
					if (cFileFind.FindFile(GetRetrieveDumpSearchFileName()))
					{
						if (((GetRetrieveMode() & HEX_RETRIEVE_AUTOFORWARD) || (GetRetrieveMode() & HEX_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & HEX_RETRIEVE_PSEUDOREALTIME)) && !GetRetrieveDumpStatus())
						{
							while ((bSearch = cFileFind.FindNextFile()))
							{
								if (cFileFind.GetFilePath() >= szName[0])
								{
									if (cFileFind.GetFilePath() != GetRetrieveDumpLastFileName()) break;
									continue;
								}
							}
							if (cFileFind.GetFilePath() >= szName[0])
							{
								if (cFileFind.GetFilePath() != GetRetrieveDumpLastFileName())
								{
									if (m_wndDataView.Update((szName[1] = cFileFind.GetFilePath()), szDump[0], tDump[0], wQuality))
									{
										SetRetrieveDumpFileName((cFileFind.FindNextFile() || bSearch) ? cFileFind.GetFilePath() : szName[1]);
										SetRetrieveDumpLastFileName(szName[1]);
										SetUpdateInfo(szDump[0], tDump[0], -1, wQuality);
										cFileFind.Close();
										return TRUE;
									}
									ReportEvent(SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE);
									StopRetrieveData();
									cFileFind.Close();
									UpdateBars();
									return FALSE;
								}
							}
						}
						if ((GetRetrieveMode() & HEX_RETRIEVE_AUTOBACKWARD) || (GetRetrieveMode() & HEX_RETRIEVE_MANUALBACKWARD))
						{
							for (szName[0] = (GetRetrieveDumpFileName() > GetRetrieveDumpLastFileName() && !GetRetrieveDumpLastFileName().IsEmpty()) ? GetRetrieveDumpLastFileName() : szName[0]; cFileFind.FindNextFile(); )
							{
								if (cFileFind.GetFilePath() < szName[0])
								{
									szName[1] = cFileFind.GetFilePath();
									continue;
								}
								break;
							}
							if ((szName[1] = (cFileFind.GetFilePath() < szName[0] || szName[1].IsEmpty()) ? cFileFind.GetFilePath() : szName[1]) <= szName[0] && szName[1] != GetRetrieveDumpLastFileName())
							{
								if (m_wndDataView.Update(szName[1], szDump[0], tDump[0], wQuality))
								{
									SetUpdateInfo(szDump[0], tDump[0], -1, wQuality);
									SetRetrieveDumpLastFileName(szName[1]);
									SetRetrieveDumpFileName(szName[1]);
									cFileFind.Close();
									return TRUE;
								}
								ReportEvent(SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE);
								StopRetrieveData();
								cFileFind.Close();
								UpdateBars();
								return FALSE;
							}
						}
						cFileFind.Close();
					}
				}
				if ((GetRetrieveMode() & HEX_RETRIEVE_AUTOFORWARD) || (GetRetrieveMode() & HEX_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & HEX_RETRIEVE_PSEUDOREALTIME))
				{
					if (GetRetrieveMode() & HEX_RETRIEVE_STOPBYREALTIME)
					{
						StopRetrieveData();
						SetRetrieveMode();
						SetRetrieveSpeed();
						SetRetrieveInterval();
						SetRetrieveStartTime();
						SetRetrieveStopTime();
						SetMode(DISPLAY_MODE_REALTIME);
						ProcessRealtimeData();
						UpdateBars();
						return TRUE;
					}
				}
				ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
				return TRUE;
			}
			return FALSE;
		}
		return TRUE;
	}
	return FALSE;
}

VOID CHEXWnd::Reset(CTMEnvironment *pTMEnvironment)
{
	CDisplayLock  cLock(this);

	if (IsInitialized())
	{
		if (pTMEnvironment != (CTMEnvironment *)NULL) pTMEnvironment->Reset();
		m_wndDataView.Reset(pTMEnvironment);
		m_wndSpyView.Reset(pTMEnvironment);
		SetUpdateInfo();
	}
}

BOOL CHEXWnd::Stop()
{
	Initialize(FALSE);
	StopSchedulePrintJobs();
	StopRetrieveData();
	return TRUE;
}

BOOL CHEXWnd::SaveInfo(INT nPage, INT nDisplay, LPCTSTR pszTitle, CONST PDISPLAYINFO pDisplayInfo)
{
	UINT  nMode;
	UINT  nSpeed;
	UINT  nLength;
	UINT  nEnum[2];
	CString  szName;
	CString  szFileName;
	LOGFONT  sFontInfo[4];
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CUIntArray  nColors;
	CByteArray  nPrintInfo;
	CByteArray  nContentsData;
	CHEXSpyLocations  pSpyLocations;
	CMemoryDump  cLayout;
	CProfile  cProfile;

	return((CDisplayWnd::SaveInfo(nPage, nDisplay, pszTitle, pDisplayInfo) && GetLayout(szName, cLayout) && GetLayoutFormat(nEnum[0], nEnum[1], nLength, nColors) && GetLayoutContents(pSpyLocations) && GetTitleFont(&sFontInfo[0]) && GetDataFont(&sFontInfo[1]) && GetSpyFont(&sFontInfo[2], &sFontInfo[3]) && GetRetrieveMode(nMode) && GetRetrieveSpeed(nSpeed) && GetRetrieveInterval(tInterval) && GetRetrieveStartTime(tStartTime) && GetRetrieveStopTime(tStopTime) && GetRetrieveFileName(szFileName) && GetPrintJobs(nPrintInfo) && cProfile.SetHEXLayoutName(nPage, nDisplay, szName) && cProfile.SetHEXLayoutInfo(nPage, nDisplay, GetViewSize(HEX_VIEW_DATA), GetViewSize(HEX_VIEW_SPY), nEnum[0], nEnum[1], nLength, nColors, IsBadDataModeEnabled()) && (((HIWORD(GetType()) == HEX_TYPE_NORMAL || HIWORD(GetType()) == HEX_TYPE_STREAM) && pSpyLocations.Map(nContentsData)) || (HIWORD(GetType()) == HEX_TYPE_DUMPS  &&  cLayout.Map(nContentsData))) && cProfile.SetHEXLayoutContents(nPage, nDisplay, nContentsData) && cProfile.SetHEXFontsInfo(nPage, nDisplay, &sFontInfo[0], &sFontInfo[1], &sFontInfo[2], &sFontInfo[3]) && cProfile.SetHEXModeInfo(nPage, nDisplay, nMode, nSpeed, tInterval, tStartTime, tStopTime) && cProfile.SetHEXRetrieveFileName(nPage, nDisplay, szFileName) && cProfile.SetHEXPrintInfo(nPage, nDisplay, nPrintInfo)) ? TRUE : FALSE);
}

BOOL CHEXWnd::LoadInfo(INT nPage, INT nDisplay, CString &szTitle, PDISPLAYINFO pDisplayInfo)
{
	UINT  nMode;
	UINT  nSpeed;
	UINT  nEnum[2];
	UINT  nLength;
	BOOL  bBadData;
	CSize  size[2];
	CString  szName;
	CString  szFileName;
	LOGFONT  sFontInfo[4];
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CUIntArray  nColors;
	CByteArray  nPrintInfo;
	CByteArray  nContentsData;
	CHEXSpyLocations  pSpyLocations;
	CMemoryDump  cLayout;
	CProfile  cProfile;

	return((CDisplayWnd::LoadInfo(nPage, nDisplay, szTitle, pDisplayInfo) && cProfile.GetHEXLayoutName(nPage, nDisplay, szName) && cProfile.GetHEXLayoutInfo(nPage, nDisplay, size[0], size[1], nEnum[0], nEnum[1], nLength, nColors, bBadData) && cProfile.GetHEXLayoutContents(nPage, nDisplay, nContentsData) && cProfile.GetHEXFontsInfo(nPage, nDisplay, &sFontInfo[0], &sFontInfo[1], &sFontInfo[2], &sFontInfo[3]) && cProfile.GetHEXModeInfo(nPage, nDisplay, nMode, nSpeed, tInterval, tStartTime, tStopTime) && cProfile.GetHEXRetrieveFileName(nPage, nDisplay, szFileName) && cProfile.GetHEXPrintInfo(nPage, nDisplay, nPrintInfo) && (((HIWORD(GetType()) == HEX_TYPE_NORMAL || HIWORD(GetType()) == HEX_TYPE_STREAM) && pSpyLocations.Unmap(nContentsData) && SetLayout(szName) && SetLayoutContents(pSpyLocations)) || (HIWORD(GetType()) == HEX_TYPE_DUMPS  &&  cLayout.Unmap(nContentsData) && SetLayout(szName, cLayout))) && SetLayoutFormat(nEnum[0], nEnum[1], nLength, nColors) && SetViewSize(HEX_VIEW_DATA, size[0]) && SetViewSize(HEX_VIEW_SPY, size[1]) && EnableBadDataMode(bBadData) && SetTitleFont(&sFontInfo[0]) && SetDataFont(&sFontInfo[1]) && SetSpyFont(&sFontInfo[2], &sFontInfo[3]) && SetRetrieveMode(nMode) && SetRetrieveSpeed(nSpeed) && SetRetrieveInterval(tInterval) && SetRetrieveStartTime(tStartTime) && SetRetrieveStopTime(tStopTime) && SetRetrieveFileName(szFileName) && SetPrintJobs(nPrintInfo)) ? TRUE : FALSE);
}

BOOL CHEXWnd::QueryDefaultInfo(PDISPLAYINFO pDefaultInfo) CONST
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

BOOL CHEXWnd::QueryDefaultMenu(CLocaleMenu &cMenu, CImageList &cImages, CUIntArray &nImageIDs) CONST
{
	INT  nIndex;
	INT  nCount;
	INT  iImage;
	UINT  nButtonID;
	UINT  nButtonStyle;
	CBitmap  cBitmap;
	BITMAP  sBitmap;

	for (cImages.DeleteImageList(), nImageIDs.RemoveAll(); cBitmap.LoadBitmap(IDB_HEXFRAMESMALLIMAGES) && cBitmap.GetBitmap(&sBitmap); )
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
	return cMenu.LoadMenu(IDR_HEXFRAME);
}

VOID CHEXWnd::UpdateBars()
{
	CDisplayLock  cLock(this);

	UpdateMessagePane();
	UpdateModePane();
	UpdateTypePane();
}

BOOL CHEXWnd::Print(PRINTDLG *pPrintInfo)
{
	INT  nJob;
	INT  nJobs;
	CHEXPrintJobs  pJobs;
	CHEXPrintJobInfo  *pJobInfo;
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
		if (pJobInfo->GetPrintMode() & HEX_PRINT_CLEARCOMMENTS)
		{
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~HEX_PRINT_CLEARCOMMENTS);
			pJobInfo->SetComments(EMPTYSTRING);
			SetPrintJobs(pJobs);
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXWnd::CanPrint() CONST
{
	return TRUE;
}

BOOL CHEXWnd::IsLinkable() CONST
{
	return((HIWORD(GetType()) != HEX_TYPE_DUMPS) ? CDisplayWnd::IsLinkable() : FALSE);
}

BOOL CHEXWnd::ProcessRealtimeData()
{
	CString  szTag;
	CTimeTag  tTag;
	WORD  wQuality;
	CDisplayLock  cLock(this);

	if (m_wndDataView.Initialize(szTag, tTag, wQuality) && m_wndSpyView.Initialize())
	{
		SetUpdateInfo(szTag, tTag, -1, wQuality);
		return TRUE;
	}
	return FALSE;
}

UINT CHEXWnd::ProcessMemoryDumps(CTimeKey &tTimeKey, CONST CTimeSpan &tInterval)
{
	BOOL  bSearch;
	CFileEx  cFile;
	CString  szFileName[4];
	FILETIME  sFileTime[3];
	CTimeKey  tFileTime[1];
	CFileFindEx  cFileFind;
	CDisplayLock  cLock(this);

	if (HIWORD(GetType()) == HEX_TYPE_DUMPS)
	{
		if (GetMode() == DISPLAY_MODE_HISTORY  &&  !(GetRetrieveMode() & HEX_RETRIEVE_REDODUMPS))
		{
			if (GetRetrieveDumpFileName(szFileName[0]) && GetRetrieveDumpLastFileName(szFileName[1]))
			{
				if ((GetRetrieveMode() & HEX_RETRIEVE_AUTOFORWARD) || (GetRetrieveMode() & HEX_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & HEX_RETRIEVE_PSEUDOREALTIME))
				{
					if (cFileFind.FindFile(GetRetrieveDumpSearchFileName()))
					{
						while ((bSearch = cFileFind.FindNextFile()))
						{
							if (cFileFind.GetFilePath() != szFileName[1])
							{
								if (cFile.Open(cFileFind.GetFilePath(), CFile::modeRead | CFile::shareDenyNone))
								{
									if (GetFileTime((HANDLE)cFile.m_hFile, &sFileTime[0], &sFileTime[1], &sFileTime[2]))
									{
										if (CTimeKey(sFileTime[0]) >= tTimeKey.GetTime() + tInterval.GetTotalSeconds())
										{
											cFile.Close();
											break;
										}
									}
									cFile.Close();
								}
							}
						}
						if (cFileFind.GetFilePath() != szFileName[1])
						{
							if (cFile.Open(cFileFind.GetFilePath(), CFile::modeRead | CFile::shareDenyNone))
							{
								if (GetFileTime((HANDLE)cFile.m_hFile, &sFileTime[0], &sFileTime[1], &sFileTime[2]))
								{
									if ((tFileTime[0] = CTimeKey(sFileTime[0])) >= tTimeKey.GetTime() + tInterval.GetTotalSeconds() || !bSearch)
									{
										SetRetrieveDumpFileName(cFileFind.GetFilePath());
										tTimeKey = tFileTime[0];
										cFileFind.Close();
										cFile.Close();
										return((szFileName[1].IsEmpty()) ? (HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS | HISTORYFILE_SYNCHRONIZE) : (HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS));
									}
								}
								cFile.Close();
							}
						}
						SetRetrieveDumpStatus(TRUE);
						cFileFind.Close();
					}
					return HISTORYFILE_SUCCESS;
				}
				if ((GetRetrieveMode() & HEX_RETRIEVE_AUTOBACKWARD) || (GetRetrieveMode() & HEX_RETRIEVE_MANUALBACKWARD))
				{
					if (cFileFind.FindFile(GetRetrieveDumpSearchFileName()))
					{
						for (szFileName[0] = (szFileName[0] > szFileName[1] && !szFileName[1].IsEmpty()) ? szFileName[1] : szFileName[0]; cFileFind.FindNextFile(); )
						{
							if (cFileFind.GetFilePath() < szFileName[0])
							{
								if (cFile.Open(cFileFind.GetFilePath(), CFile::modeRead | CFile::shareDenyNone))
								{
									if (GetFileTime((HANDLE)cFile.m_hFile, &sFileTime[0], &sFileTime[1], &sFileTime[2]))
									{
										if ((tFileTime[0] = CTimeKey(sFileTime[0])) < tTimeKey.GetTime() - tInterval.GetTotalSeconds() || !tInterval.GetTotalSeconds())
										{
											szFileName[2] = cFileFind.GetFilePath();
											cFile.Close();
											continue;
										}
										SetRetrieveDumpFileName((szFileName[3] = cFileFind.GetFilePath()));
										cFile.Close();
										break;
									}
									cFile.Close();
								}
								continue;
							}
							break;
						}
						if ((szFileName[2] = ((cFileFind.GetFilePath() < szFileName[0] && szFileName[3].IsEmpty()) || szFileName[2].IsEmpty()) ? cFileFind.GetFilePath() : szFileName[2]) <= szFileName[0] && szFileName[1] != szFileName[2])
						{
							if (cFile.Open(szFileName[2], CFile::modeRead | CFile::shareDenyNone))
							{
								if (GetFileTime((HANDLE)cFile.m_hFile, &sFileTime[0], &sFileTime[1], &sFileTime[2]))
								{
									tTimeKey = CTimeKey(sFileTime[0]);
									SetRetrieveDumpStatus(FALSE);
									cFileFind.Close();
									cFile.Close();
									return HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS;
								}
								cFile.Close();
							}
							cFileFind.Close();
							return HISTORYFILE_ERROR;
						}
						cFileFind.Close();
					}
					return HISTORYFILE_SUCCESS;
				}
			}
		}
	}
	return HISTORYFILE_ERROR;
}

BOOL CHEXWnd::StartRetrieveData(UINT nMode, UINT nSpeed, CONST CTimeSpan &tInterval, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime)
{
	SetRetrieveMode(nMode);
	SetRetrieveSpeed(nSpeed);
	SetRetrieveInterval(tInterval);
	SetRetrieveStartTime(tStartTime);
	SetRetrieveStopTime(tStopTime);
	return StartRetrieveData();
}
BOOL CHEXWnd::StartRetrieveData()
{
	CEvent  bInit;
	CString  szLayout;
	CMemoryDump  cLayout;
	CMemoryDump  *pDump[2];
	CMemoryDumps  pDumps;

	if (GetMode() == DISPLAY_MODE_HISTORY)
	{
		if (GetLink() != (CDisplayWnd *)NULL)
		{
			for (SetRetrieveMode(); TRUE; )
			{
				SetUpdateInfo(EMPTYSTRING, 0, -1, TMUNIT_DATAQUALITY_NONE);
				break;
			}
			return TRUE;
		}
		if (!IsRetrievingData())
		{
			if (HIWORD(GetType()) != HEX_TYPE_DUMPS || (GetRetrieveMode() & HEX_RETRIEVE_REDODUMPS) || SetRetrieveDumpFileName())
			{
				if (HIWORD(GetType()) == HEX_TYPE_DUMPS)
				{
					if (GetRetrieveMode() & HEX_RETRIEVE_REDODUMPS)
					{
						if ((pDump[0] = (GetMemoryDumpsService()->GetMemoryDumps(pDumps) && GetLayout(szLayout, cLayout)) ? pDumps.GetAt(pDumps.Find(cLayout.GetName())) : (CMemoryDump *)NULL))
						{
							if ((pDump[1] = new CMemoryDump) && pDump[1]->SetDumpInfo(pDump[0], MEMORYDUMP_STATUS_EMPTY))
							{
								if (!(GetRetrieveMode() & HEX_RETRIEVE_ARCHIVEDUMPS))
								{
									pDump[1]->SetArchivingRetentionOptions(0);
									pDump[1]->SetArchivingRetentionByCount(0);
									pDump[1]->SetArchivingRetentionByTime(0);
								}
								if (!(GetRetrieveMode() & HEX_RETRIEVE_NOTIFYDUMPS))
								{
									pDump[1]->SetNotificationsRetentionOptions(0);
									pDump[1]->SetNotificationsRetentionByCount(0);
									pDump[1]->SetNotificationsRetentionByTime(0);
								}
								m_pMemoryDumps.RemoveAll();
								m_pMemoryDumps.Add(pDump[1]);
							}
							else
							{
								SetRetrieveMode(GetRetrieveMode() & ~(HEX_RETRIEVE_REDODUMPS | HEX_RETRIEVE_ARCHIVEDUMPS | HEX_RETRIEVE_NOTIFYDUMPS));
								m_pMemoryDumps.RemoveAll();
								delete pDump[1];
							}
						}
						else
						{
							SetRetrieveMode(GetRetrieveMode() & ~(HEX_RETRIEVE_REDODUMPS | HEX_RETRIEVE_ARCHIVEDUMPS | HEX_RETRIEVE_NOTIFYDUMPS));
							m_pMemoryDumps.RemoveAll();
						}
					}
				}
				if (m_cRetrieveThread.Start(this, bInit, GetRetrieveFileName(), GetRetrieveMode(), GetRetrieveSpeed(), GetRetrieveInterval(), GetRetrieveStartTime(), GetRetrieveStopTime(), &m_bRetrieveFlag, m_cRetrieveStop, m_cRetrieveAutoForward, m_cRetrieveAutoBackward, m_cRetrieveManualForward, m_cRetrieveManualBackward, m_cRetrievePseudoRealtime) && UpdateAllPanes())
				{
					WaitForSingleObject(bInit, INFINITE);
					return TRUE;
				}
				ReportEvent(SYSTEM_WARNING_HEX_RETRIEVE_FAILURE);
				return FALSE;
			}
			ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
			return TRUE;
		}
	}
	return FALSE;
}

LONG CHEXWnd::IsRetrievingData() CONST
{
	LONG  bFlag;

	InterlockedExchange(&bFlag, m_bRetrieveFlag);
	return((m_cRetrieveThread.IsThreadActive()) ? bFlag : FALSE);
}

BOOL CHEXWnd::RetrieveMoreData(UINT nAction)
{
	if (IsRetrievingData())
	{
		if (nAction == HEX_RETRIEVE_STOPPED)
		{
			SetRetrieveMode(GetRetrieveMode() | nAction);
			m_cRetrieveStop.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
		if (nAction == HEX_RETRIEVE_AUTOFORWARD)
		{
			SetRetrieveMode((GetRetrieveMode() & (HEX_RETRIEVE_EXACTTIME | HEX_RETRIEVE_STOPBYTIME | HEX_RETRIEVE_STOPBYEND | HEX_RETRIEVE_STOPBYREALTIME | HEX_RETRIEVE_REDODUMPS)) | nAction);
			m_cRetrieveAutoForward.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
		if (nAction == HEX_RETRIEVE_AUTOBACKWARD)
		{
			SetRetrieveMode((GetRetrieveMode() & (HEX_RETRIEVE_EXACTTIME | HEX_RETRIEVE_STOPBYTIME | HEX_RETRIEVE_STOPBYEND | HEX_RETRIEVE_STOPBYREALTIME)) | nAction);
			m_cRetrieveAutoBackward.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
		if (nAction == HEX_RETRIEVE_MANUALFORWARD)
		{
			SetRetrieveMode((GetRetrieveMode() & (HEX_RETRIEVE_EXACTTIME | HEX_RETRIEVE_STOPBYTIME | HEX_RETRIEVE_STOPBYEND | HEX_RETRIEVE_STOPBYREALTIME | HEX_RETRIEVE_REDODUMPS)) | nAction);
			m_cRetrieveManualForward.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
		if (nAction == HEX_RETRIEVE_MANUALBACKWARD)
		{
			SetRetrieveMode((GetRetrieveMode() & (HEX_RETRIEVE_EXACTTIME | HEX_RETRIEVE_STOPBYTIME | HEX_RETRIEVE_STOPBYEND | HEX_RETRIEVE_STOPBYREALTIME)) | nAction);
			m_cRetrieveManualBackward.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
		if (nAction == HEX_RETRIEVE_PSEUDOREALTIME)
		{
			SetRetrieveMode((GetRetrieveMode() & (HEX_RETRIEVE_EXACTTIME | HEX_RETRIEVE_STOPBYTIME | HEX_RETRIEVE_STOPBYEND | HEX_RETRIEVE_STOPBYREALTIME | HEX_RETRIEVE_REDODUMPS)) | nAction);
			m_cRetrievePseudoRealtime.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CHEXWnd::StopRetrieveData()
{
	return(((IsRetrievingData() && m_cRetrieveThread.Stop()) || !IsRetrievingData()) ? TRUE : FALSE);
}

BOOL CHEXWnd::SetRetrieveMode(UINT nMode)
{
	CDisplayLock  cLock(this);

	m_nRetrieveMode = nMode;
	m_bRetrieveFlag = MAKELONG((nMode) ? LOWORD(m_bRetrieveFlag) : FALSE, (nMode) ? HIWORD(m_bRetrieveFlag) : FALSE);
	return TRUE;
}

BOOL CHEXWnd::GetRetrieveMode(UINT &nMode) CONST
{
	nMode = m_nRetrieveMode;
	return TRUE;
}
UINT CHEXWnd::GetRetrieveMode() CONST
{
	return m_nRetrieveMode;
}

BOOL CHEXWnd::SetRetrieveSpeed(UINT nSpeed)
{
	m_nRetrieveSpeed = nSpeed;
	return TRUE;
}

BOOL CHEXWnd::GetRetrieveSpeed(UINT &nSpeed) CONST
{
	nSpeed = m_nRetrieveSpeed;
	return TRUE;
}
UINT CHEXWnd::GetRetrieveSpeed() CONST
{
	return m_nRetrieveSpeed;
}

BOOL CHEXWnd::SetRetrieveInterval(CONST CTimeSpan &tInterval)
{
	CDisplayLock  cLock(this);

	m_tRetrieveInterval = tInterval;
	return TRUE;
}

BOOL CHEXWnd::GetRetrieveInterval(CTimeSpan &tInterval) CONST
{
	CDisplayLock  cLock(this);

	tInterval = m_tRetrieveInterval;
	return TRUE;
}
CTimeSpan CHEXWnd::GetRetrieveInterval() CONST
{
	CDisplayLock  cLock(this);

	return m_tRetrieveInterval;
}

BOOL CHEXWnd::SetRetrieveStartTime(CONST CTimeKey &tStartTime)
{
	CDisplayLock  cLock(this);

	m_tRetrieveStartTime = tStartTime;
	return TRUE;
}

BOOL CHEXWnd::GetRetrieveStartTime(CTimeKey &tStartTime) CONST
{
	CDisplayLock  cLock(this);

	tStartTime = m_tRetrieveStartTime;
	return TRUE;
}
CTimeKey CHEXWnd::GetRetrieveStartTime() CONST
{
	CDisplayLock  cLock(this);

	return m_tRetrieveStartTime;
}

BOOL CHEXWnd::SetRetrieveStopTime(CONST CTimeKey &tStopTime)
{
	CDisplayLock  cLock(this);

	m_tRetrieveStopTime = tStopTime;
	return TRUE;
}

BOOL CHEXWnd::GetRetrieveStopTime(CTimeKey &tStopTime) CONST
{
	CDisplayLock  cLock(this);

	tStopTime = m_tRetrieveStopTime;
	return TRUE;
}
CTimeKey CHEXWnd::GetRetrieveStopTime() CONST
{
	CDisplayLock  cLock(this);

	return m_tRetrieveStopTime;
}

BOOL CHEXWnd::SetRetrieveFileName(LPCTSTR pszFileName)
{
	CDisplayLock  cLock(this);

	m_szRetrieveFileName = pszFileName;
	return TRUE;
}

BOOL CHEXWnd::GetRetrieveFileName(CString &szFileName) CONST
{
	CDisplayLock  cLock(this);

	szFileName = GetRetrieveFileName();
	return TRUE;
}
CString CHEXWnd::GetRetrieveFileName() CONST
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

BOOL CHEXWnd::SetRetrieveDumpFileName()
{
	BOOL  bFileSearch;
	CString  szLayout;
	CString  szFileName[4];
	CString  szFileExtension;
	CFileFindEx  cFileFind;
	CMemoryDump  cLayout;
	CDisplayLock  cLock(this);

	if (HIWORD(GetType()) == HEX_TYPE_DUMPS)
	{
		if (GetLayout(szLayout, cLayout) && cLayout.GetFileExtension(cLayout.GetArchivingFileFormats(), szFileExtension))
		{
			szFileName[1] = GetMemoryDumpsServiceSupport()->GetMemoryDumpFileName(&cLayout, (szFileName[0] = cLayout.GetFileName()), GetRetrieveStartTime(), szFileExtension);
			szFileName[2] = GetMemoryDumpsServiceSupport()->GetMemoryDumpSearchFileName(szFileName[0], szFileExtension);
			if (cFileFind.FindFile(szFileName[2]))
			{
				while ((bFileSearch = cFileFind.FindNextFile()))
				{
					if (cFileFind.GetFilePath() < szFileName[1])
					{
						szFileName[3] = cFileFind.GetFilePath();
						continue;
					}
					szFileName[3] = (!cFileFind.GetFilePath().CompareNoCase(szFileName[1]) || szFileName[3].IsEmpty()) ? cFileFind.GetFilePath() : szFileName[3];
					break;
				}
				if (!bFileSearch || !szFileName[3].IsEmpty())
				{
					m_szRetrieveDumpFileName[0] = (!bFileSearch) ? cFileFind.GetFilePath() : szFileName[3];
					m_szRetrieveDumpFileName[1] = CString(EMPTYSTRING);
					m_szRetrieveDumpFileName[2] = szFileName[2];
					m_bRetrieveDump = FALSE;
					cFileFind.Close();
					return TRUE;
				}
				cFileFind.Close();
			}
		}
	}
	m_szRetrieveDumpFileName[0].Empty();
	m_szRetrieveDumpFileName[1].Empty();
	m_szRetrieveDumpFileName[2].Empty();
	m_bRetrieveDump = FALSE;
	return FALSE;
}
BOOL CHEXWnd::SetRetrieveDumpFileName(LPCTSTR pszFileName)
{
	CDisplayLock  cLock(this);

	m_szRetrieveDumpFileName[0] = pszFileName;
	return TRUE;
}

BOOL CHEXWnd::GetRetrieveDumpFileName(CString &szFileName) CONST
{
	CDisplayLock  cLock(this);

	szFileName = m_szRetrieveDumpFileName[0];
	return TRUE;
}
CString CHEXWnd::GetRetrieveDumpFileName() CONST
{
	CDisplayLock  cLock(this);

	return m_szRetrieveDumpFileName[0];
}

BOOL CHEXWnd::SetRetrieveDumpLastFileName(LPCTSTR pszFileName)
{
	CDisplayLock  cLock(this);

	m_szRetrieveDumpFileName[1] = pszFileName;
	return TRUE;
}

BOOL CHEXWnd::GetRetrieveDumpLastFileName(CString &szFileName) CONST
{
	CDisplayLock  cLock(this);

	szFileName = m_szRetrieveDumpFileName[1];
	return TRUE;
}
CString CHEXWnd::GetRetrieveDumpLastFileName() CONST
{
	CDisplayLock  cLock(this);

	return m_szRetrieveDumpFileName[1];
}

BOOL CHEXWnd::SetRetrieveDumpSearchFileName(LPCTSTR pszFileName)
{
	CDisplayLock  cLock(this);

	m_szRetrieveDumpFileName[2] = pszFileName;
	return TRUE;
}

BOOL CHEXWnd::GetRetrieveDumpSearchFileName(CString &szFileName) CONST
{
	CDisplayLock  cLock(this);

	szFileName = m_szRetrieveDumpFileName[2];
	return TRUE;
}
CString CHEXWnd::GetRetrieveDumpSearchFileName() CONST
{
	CDisplayLock  cLock(this);

	return m_szRetrieveDumpFileName[2];
}

BOOL CHEXWnd::SetRetrieveDumpStatus(BOOL bStop)
{
	m_bRetrieveDump = bStop;
	return TRUE;
}

BOOL CHEXWnd::GetRetrieveDumpStatus() CONST
{
	return m_bRetrieveDump;
}

BOOL CHEXWnd::SetPrintJobs(CONST CHEXPrintJobs &pPrintJobs)
{
	return m_cPrintThread.SetPrintJobs(pPrintJobs);
}

BOOL CHEXWnd::GetPrintJobs(CHEXPrintJobs &pPrintJobs) CONST
{
	return m_cPrintThread.GetPrintJobs(pPrintJobs);
}

BOOL CHEXWnd::Print(CONST CHEXPrintJobInfo *pJobInfo, PRINTDLG *pPrintInfo)
{
	CDC  cDC;
	UINT  nMode;
	UINT  nTMUnit;
	BOOL  bMetric;
	BOOL  bQuality;
	RECT  rtMargin[2];
	SIZE  ptPaperSize;
	CTimeTag  tTMUnit;
	CString  szTMUnit;
	CString  szLayout;
	CString  szTitle[2];
	LOGFONT  lfFont[2][2];
	DEVMODE  *pDevMode;
	DEVNAMES  *pDevNames;
	CStringArray  szColumns[2];
	CStringArray  szContents[2];
	CPrintProfiles  cPrintProfiles;
	CPrintProfileInfo  *pPrintProfileInfo;
	CTextViewAttributes  pAttributes[2];

	if ((pPrintProfileInfo = (GetPrintProfiles(cPrintProfiles)) ? cPrintProfiles.GetAt(cPrintProfiles.Find(pJobInfo->GetProfile())) : (CPrintProfileInfo *)NULL) && pPrintProfileInfo->GetPaperInfo(ptPaperSize, rtMargin[0], rtMargin[1], bMetric))
	{
		if (GetLayout(szLayout) && GetPrintProperties(pJobInfo, nMode, szTMUnit, tTMUnit, nTMUnit, bQuality, szTitle[0], szTitle[1], szColumns[0], szColumns[1], szContents[0], szContents[1], pAttributes[0], pAttributes[1], &lfFont[0][0], &lfFont[0][1], &lfFont[1][0], &lfFont[1][1]))
		{
			if (pPrintInfo == (PRINTDLG *)NULL)
			{
				if (CreatePrinterDC(pPrintProfileInfo, cDC))
				{
					if (PrintJob(cDC, pJobInfo, pPrintProfileInfo->GetPrinterName(), 0, 0, rtMargin[0], bMetric, szLayout, nMode, szTMUnit, tTMUnit, nTMUnit, bQuality, szTitle[0], szTitle[1], szColumns[0], szColumns[1], szContents[0], szContents[1], pAttributes[0], pAttributes[1], &lfFont[0][0], &lfFont[0][1], &lfFont[1][0], &lfFont[1][1]))
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
						if (PrintJob(cDC, pJobInfo, (LPCTSTR)pDevMode->dmDeviceName, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nFromPage : 0, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nToPage : 0, rtMargin[0], bMetric, szLayout, nMode, szTMUnit, tTMUnit, nTMUnit, bQuality, szTitle[0], szTitle[1], szColumns[0], szColumns[1], szContents[0], szContents[1], pAttributes[0], pAttributes[1], &lfFont[0][0], &lfFont[0][1], &lfFont[1][0], &lfFont[1][1]))
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

CHEXWnd *CHEXWnd::Find(INT nType, UINT nMode, LPCTSTR pszName) CONST
{
	INT  nDisplay;
	INT  nDisplays;
	CHEXWnd  *pHEXWnd;
	CString  szLayout;
	CDisplayWnd  *pDisplayWnd;
	CPtrArray  pDisplays;

	for (nDisplay = 0, nDisplays = GetDisplayArea()->EnumDisplays(pDisplays), pHEXWnd = (CHEXWnd *)NULL; nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_HEX  &&  HIWORD(pDisplayWnd->GetType()) == HIWORD(nType) && pDisplayWnd->GetMode() == nMode)
		{
			if ((pHEXWnd = (CHEXWnd *)pDisplayWnd)->GetLayout(szLayout) && szLayout == pszName) break;
			continue;
		}
	}
	return((nDisplay < nDisplays) ? pHEXWnd : (CHEXWnd *)NULL);
}

VOID CHEXWnd::SetUpdateInfo()
{
	CDisplayLock  cLock(this);

	m_szTMUnit.Empty();
	m_tTMUnit = 0;
	m_nTMUnit = 0;
	m_wTMUnit = TMUNIT_DATAQUALITY_NONE;
	UpdateMessagePane();
}
VOID CHEXWnd::SetUpdateInfo(LPCTSTR pszTag, CONST CTimeTag &tTag, UINT nTag, WORD wQuality)
{
	CDisplayLock  cLock(this);

	m_szTMUnit = pszTag;
	m_tTMUnit = tTag;
	m_nTMUnit = nTag;
	m_wTMUnit = wQuality;
	UpdateMessagePane();
}

BOOL CHEXWnd::GetUpdateInfo(CString &szTag, CTimeTag &tTag, UINT &nTag, WORD &wQuality) CONST
{
	CDisplayLock  cLock(this);

	szTag = m_szTMUnit;
	tTag = m_tTMUnit;
	nTag = m_nTMUnit;
	wQuality = m_wTMUnit;
	return TRUE;
}

BOOL CHEXWnd::CreateToolBar()
{
	if (m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE) && m_wndToolBar.LoadToolBar(IDB_HEXFRAMELARGEIMAGES, 0, IDB_HEXFRAMESMALLIMAGES, TRUE))
	{
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_HEXSETTINGS), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_HEXRETRIEVALS), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_HEXRETRIEVESTOP), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_HEXRETRIEVESTEPFORWARD), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_HEXRETRIEVESTEPBACKWARD), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_HEXRETRIEVEFORWARD), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_HEXRETRIEVEBACKWARD), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_HEXRETRIEVEPSEUDOREALTIME), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_HEXPRINT), TBBS_DISABLED);
		DockPane(&m_wndToolBar);
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXWnd::CreateStatusBar()
{
	if (m_wndStatusBar.Create(this, CBRS_BOTTOM | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE) && m_wndStatusBar.SetIndicators(nHEXStatusBarIndicators, 1))
	{
		m_wndStatusBar.EnableToolTips();
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXWnd::CreateSplitterBar()
{
	return m_wndSplitterBarCtrl[0].Create(this, RepositionViewSplitterBar());
}

BOOL CHEXWnd::CreateViews()
{
	CRect  rView[2];

	if (m_wndDataView.Create(this) && m_wndSpyView.Create(this))
	{
		if (m_sizeViews[HEX_VIEW_DATA].cx > 0 && m_sizeViews[HEX_VIEW_DATA].cy > 0)
		{
			for (rView[0] = RepositionView(HEX_VIEW_DATA); !rView[0].IsRectEmpty(); )
			{
				rView[0].SetRect(rView[0].left, rView[0].top, rView[0].right, rView[0].top + m_sizeViews[HEX_VIEW_DATA].cy);
				break;
			}
			for (rView[1] = RepositionView(HEX_VIEW_SPY); !rView[1].IsRectEmpty(); )
			{
				rView[1].SetRect(rView[1].left, (!rView[0].IsRectEmpty()) ? (rView[0].bottom + RepositionViewSplitterBar().Height()) : rView[1].top, rView[1].right, (!rView[0].IsRectEmpty()) ? (rView[0].bottom + RepositionViewSplitterBar().Height() + m_sizeViews[HEX_VIEW_SPY].cy) : (rView[1].top + m_sizeViews[HEX_VIEW_SPY].cy));
				break;
			}
			m_wndDataView.MoveWindow(rView[0]);
			m_wndSpyView.MoveWindow(rView[1]);
			return TRUE;
		}
		m_wndDataView.MoveWindow(RepositionView(HEX_VIEW_DATA));
		m_wndSpyView.MoveWindow(RepositionView(HEX_VIEW_SPY));
		return m_wndDataView.AdjustColumns() && m_wndSpyView.AdjustColumns();
	}
	return FALSE;
}

VOID CHEXWnd::InitializeViews()
{
	SetViewSize(HEX_VIEW_DATA, CSize(0, 0));
	SetViewSize(HEX_VIEW_SPY, CSize(0, 0));
	m_bViews[0] = TRUE;
	m_bViews[1] = FALSE;
}

CRect CHEXWnd::RepositionViews(BOOL bAdjust)
{
	CRect  rWnd[2];
	CRect  rView[2];
	CRect  rToolBar;
	CRect  rStatusBar;

	for (rWnd[0].SetRectEmpty(), rView[0].SetRectEmpty(); IsWindow(m_wndDataView.GetSafeHwnd()); )
	{
		rView[0].SetRect(0, 0, m_wndDataView.GetTrackSize().cx, m_wndDataView.GetTrackSize().cy);
		break;
	}
	for (rView[1].SetRectEmpty(); IsWindow(m_wndSpyView.GetSafeHwnd()); )
	{
		rView[1].SetRect(0, 0, m_wndSpyView.GetTrackSize().cx, m_wndSpyView.GetTrackSize().cy);
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
		for (rWnd[0].SetRect(0, 0, 2 * GetSystemMetrics(SM_CXFRAME) + rView[0].Width(), 2 * (GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYEDGE)) + GetSystemMetrics(SM_CYCAPTION) + rToolBar.Height() + IsViewVisible(HEX_VIEW_DATA)*rView[0].Height() + RepositionViewSplitterBar().Height() + IsViewVisible(HEX_VIEW_SPY)*rView[1].Height() + rStatusBar.Height()); bAdjust; )
		{
			for (GetWindowRect(rWnd[1]), GetParent()->ScreenToClient(rWnd[1]); rWnd[0].Height() > rWnd[1].Height(); )
			{
				MoveWindow(rWnd[1].left, rWnd[1].top, rWnd[1].Width(), rWnd[0].Height());
				return rWnd[0];
			}
			m_wndDataView.MoveWindow(RepositionView(HEX_VIEW_DATA));
			m_wndSplitterBarCtrl[0].MoveWindow(RepositionViewSplitterBar());
			m_wndSpyView.MoveWindow(RepositionView(HEX_VIEW_SPY));
			break;
		}
	}
	return rWnd[0];
}

BOOL CHEXWnd::SetViewSize(UINT nView, CONST CSize &size)
{
	if (nView == HEX_VIEW_DATA || nView == HEX_VIEW_SPY)
	{
		m_sizeViews[nView] = size;
		return TRUE;
	}
	return FALSE;
}

CSize CHEXWnd::GetViewSize(UINT nView) CONST
{
	CRect  rView(0, 0, 0, 0);

	if (nView == HEX_VIEW_DATA) m_wndDataView.GetWindowRect(rView);
	if (nView == HEX_VIEW_SPY) m_wndSpyView.GetWindowRect(rView);
	return CSize(rView.Width(), rView.Height());
}

CRect CHEXWnd::RepositionView(UINT nView)
{
	INT  nHeight;
	INT  nOffset;
	CWnd  *pWnd;
	CRect  rWnd;
	CRect  rView[5];

	for (rView[0].SetRectEmpty(); IsWindow(GetSafeHwnd()); )
	{
		for (pWnd = GetWindow(GW_CHILD), GetClientRect(rView[0]); pWnd != (CWnd *)NULL; pWnd = pWnd->GetNextWindow())
		{
			if (pWnd->GetSafeHwnd() != m_wndDataView.GetSafeHwnd() && pWnd->GetSafeHwnd() != m_wndSpyView.GetSafeHwnd())
			{
				pWnd->GetWindowRect(rWnd);
				ScreenToClient(rWnd);
				rWnd.left = rView[0].left;
				rWnd.right = rView[0].right;
				rView[0].SubtractRect(rView[0], rWnd);
			}
		}
		if (IsWindow(m_wndDataView.GetSafeHwnd()) && IsWindow(m_wndSpyView.GetSafeHwnd()))
		{
			for (m_wndDataView.GetWindowRect(rView[1]), m_wndSpyView.GetWindowRect(rView[3]), rView[2].SetRect(0, 0, m_wndDataView.GetTrackSize().cx, m_wndDataView.GetTrackSize().cy), rView[4].SetRect(0, 0, m_wndSpyView.GetTrackSize().cx, m_wndSpyView.GetTrackSize().cy), ScreenToClient(rView[1]), ScreenToClient(rView[3]); !IsViewVisible(HEX_VIEW_DATA); )
			{
				rView[1].SetRectEmpty();
				rView[2].SetRectEmpty();
				break;
			}
			if (!IsViewVisible(HEX_VIEW_SPY))
			{
				rView[3].SetRectEmpty();
				rView[4].SetRectEmpty();
			}
			rView[0].DeflateRect(0, rView[1].Height(), 0, 0);
			rView[0].DeflateRect(0, rView[3].Height(), 0, 0);
			if (IsViewVisible(HEX_VIEW_DATA) && rView[1].IsRectEmpty())
			{
				rView[1].SetRect(rView[0].left, rView[0].top, rView[0].right, rView[0].top + rView[2].Height());
				rView[0].DeflateRect(0, rView[2].Height(), 0, 0);
			}
			rView[0].DeflateRect(0, RepositionViewSplitterBar().Height(), 0, 0);
			if (IsViewVisible(HEX_VIEW_SPY) && rView[3].IsRectEmpty())
			{
				rView[3].SetRect(rView[0].left, rView[0].top, rView[0].right, rView[0].top + rView[4].Height());
				rView[0].DeflateRect(0, rView[4].Height(), 0, 0);
			}
			if (rView[0].Height() > 0) rView[1].InflateRect(0, 0, 0, rView[0].Height());
			if (rView[0].Height() < 0 && IsViewVisible(HEX_VIEW_SPY) && rView[3].Height() > rView[4].Height())
			{
				if ((nHeight = rView[3].Height() - rView[4].Height()) >= abs(rView[0].Height()))
				{
					rView[3].DeflateRect(0, 0, 0, abs(rView[0].Height()));
					rView[0].InflateRect(0, abs(rView[0].Height()), 0, 0);
				}
				else
				{
					rView[3].DeflateRect(0, 0, 0, nHeight);
					rView[0].InflateRect(0, nHeight, 0, 0);
				}
			}
			if (rView[0].Height() < 0 && IsViewVisible(POD_VIEW_DATA) && rView[1].Height() > rView[2].Height())
			{
				if ((nHeight = rView[1].Height() - rView[2].Height()) >= abs(rView[0].Height()))
				{
					rView[3].OffsetRect(0, rView[0].Height());
					rView[1].DeflateRect(0, 0, 0, abs(rView[0].Height()));
					rView[0].InflateRect(0, abs(rView[0].Height()), 0, 0);
				}
				else
				{
					rView[3].OffsetRect(0, -nHeight);
					rView[1].DeflateRect(0, 0, 0, nHeight);
					rView[0].InflateRect(0, nHeight, 0, 0);
				}
			}
			if (IsViewVisible(HEX_VIEW_DATA) && IsViewVisible(HEX_VIEW_SPY))
			{
				nOffset = rView[3].top - (rView[1].bottom + RepositionViewSplitterBar().Height());
				rView[3].OffsetRect(0, -nOffset);
			}
			switch (nView)
			{
			case HEX_VIEW_DATA:
			{ if (IsViewVisible(HEX_VIEW_DATA))
			{
				rView[1].left = rView[0].left;
				rView[1].right = rView[0].right;
				return rView[1];
			}
			break;
			}
			case HEX_VIEW_SPY:
			{ if (IsViewVisible(HEX_VIEW_SPY))
			{
				rView[3].left = rView[0].left;
				rView[3].right = rView[0].right;
				return rView[3];
			}
			break;
			}
			}
		}
		break;
	}
	return CRect(0, 0, 0, 0);
}

CRect CHEXWnd::RepositionViewSplitterBar() CONST
{
	CRect  rView[3];

	for (GetClientRect(rView[0]); IsWindow(m_wndDataView.GetSafeHwnd()) && IsWindow(m_wndSpyView.GetSafeHwnd()); )
	{
		m_wndDataView.GetWindowRect(rView[1]);
		m_wndSpyView.GetWindowRect(rView[2]);
		ScreenToClient(rView[1]);
		ScreenToClient(rView[2]);
		return((IsViewVisible(HEX_VIEW_DATA) && IsViewVisible(HEX_VIEW_SPY)) ? CRect(rView[0].left, rView[1].bottom, rView[0].right, rView[1].bottom + 2 * GetSystemMetrics(SM_CYEDGE)) : CRect(rView[0].left, rView[0].bottom, rView[0].right, rView[0].bottom));
	}
	return CRect(rView[0].left, rView[0].bottom, rView[0].right, rView[0].bottom);
}

BOOL CHEXWnd::IsViewVisible(UINT nView) CONST
{
	return((nView == HEX_VIEW_DATA || nView == HEX_VIEW_SPY) ? m_bViews[nView] : FALSE);
}

BOOL CHEXWnd::Customize(BOOL bDefault)
{
	CString  szName;
	LOGFONT  sFontInfo[4];
	CMemoryDump  cLayout;
	CHEXSpyLocations  pSpyLocations;

	return(((!bDefault  &&  GetTitleFont(&sFontInfo[0]) && GetDataFont(&sFontInfo[1]) && GetSpyFont(&sFontInfo[2], &sFontInfo[3]) && SetTitleFont(&sFontInfo[0]) && SetDataFont(&sFontInfo[1]) && SetSpyFont(&sFontInfo[2], &sFontInfo[3]) && ((HIWORD(GetType()) == HEX_TYPE_NORMAL || HIWORD(GetType()) == HEX_TYPE_STREAM) && GetLayout(szName) && GetLayoutContents(pSpyLocations) && SetLayout(szName) && SetLayoutContents(pSpyLocations)) || (HIWORD(GetType()) == HEX_TYPE_DUMPS  &&  GetLayout(szName, cLayout) && SetLayout(szName, cLayout))) || bDefault) ? TRUE : FALSE);
}

BOOL CHEXWnd::UpdateAllPanes()
{
	INT  nPane;
	INT  nPanes;

	for (nPane = 0, nPanes = sizeof(nHEXStatusBarIndicators) / sizeof(UINT); nPane < nPanes; nPane++)
	{
		if (m_wndStatusBar.CommandToIndex(nHEXStatusBarIndicators[nPane]) != nPane) break;
		continue;
	}
	if (nPane < nPanes)
	{
		if (m_wndStatusBar.SetIndicators(nHEXStatusBarIndicators, sizeof(nHEXStatusBarIndicators) / sizeof(UINT)))
		{
			UpdateBars();
			return TRUE;
		}
		return FALSE;
	}
	UpdateBars();
	return TRUE;
}

VOID CHEXWnd::UpdateMessagePane()
{
	UINT  nTag;
	WORD  wQuality;
	CTimeTag  tTag;
	CString  szTag;
	CString  szMessage;
	CStringTools  cStringTools;

	if (GetUpdateInfo(szTag, tTag, nTag, wQuality))
	{
		szMessage.Format((szTag.IsEmpty()) ? ((tTag > 0) ? STRING(IDS_HEX_STATUSBAR_FULLUPDATEMESSAGE) : ((IsRetrievingData() && HIWORD(IsRetrievingData())) ? STRING(IDS_HEX_STATUSBAR_RETRIEVEMESSAGE) : STRING(IDS_HEX_STATUSBAR_NODATAMESSAGE))) : ((nTag == (UINT)-1) ? STRING(IDS_HEX_STATUSBAR_INITUPDATEMESSAGE) : STRING(IDS_HEX_STATUSBAR_UPDATEMESSAGE)), (LPCTSTR)tTag.FormatGmt(), (LPCTSTR)szTag, nTag, ((wQuality & (TMUNIT_DATAQUALITY_GOOD | TMUNIT_SEQUENCEQUALITY_GOOD)) == (TMUNIT_DATAQUALITY_GOOD | TMUNIT_SEQUENCEQUALITY_GOOD)) ? ((wQuality & TMUNIT_TIMECORRELATION_BAD) ? (LPCTSTR)(CString(STRING(IDS_HEX_STATUSBAR_QUALITYGOOD)) + STRING(IDS_HEX_STATUSBAR_TIMECORRELATIONFLAG)) : STRING(IDS_HEX_STATUSBAR_QUALITYGOOD)) : ((wQuality & TMUNIT_TIMECORRELATION_BAD) ? (LPCTSTR)(CString(STRING(IDS_HEX_STATUSBAR_QUALITYBAD)) + STRING(IDS_HEX_STATUSBAR_TIMECORRELATIONFLAG)) : STRING(IDS_HEX_STATUSBAR_QUALITYBAD)));
		m_wndStatusBar.SetPaneText(ID_HEX_STATUSBAR_MESSAGEPANE, (nTag == (UINT)-1 && szMessage.Find(cStringTools.ConvertUIntToString(-1)) >= 0) ? (szMessage.Left(szMessage.Find(cStringTools.ConvertUIntToString(-1))) + szMessage.Mid(szMessage.Find(cStringTools.ConvertUIntToString(-1)) + cStringTools.ConvertUIntToString(-1).GetLength())) : szMessage);
	}
}

VOID CHEXWnd::UpdateModePane()
{
	CString  szMode;
	CString  szLayout;
	CDisplayWnd  *pDisplayWnd;

	for (szMode.Empty(); (pDisplayWnd = (CDisplayWnd *)GetLink()) && GetLayout(szLayout); )
	{
		szMode.Format(STRING(IDS_DISPLAY_MODE_LINK), STRING(IDS_DISPLAY_TITLE_HEX), (LPCTSTR)szLayout);
		break;
	}
	m_wndStatusBar.SetPaneText(ID_HEX_STATUSBAR_MODEPANE, (GetMode() == DISPLAY_MODE_HISTORY) ? (((GetRetrieveMode() & HEX_RETRIEVE_AUTOFORWARD) && !(GetRetrieveMode() & HEX_RETRIEVE_STOPPED)) ? STRING(IDS_HEX_STATUSBAR_AUTOFORWARDMODE) : (((GetRetrieveMode() & HEX_RETRIEVE_AUTOBACKWARD) && !(GetRetrieveMode() & HEX_RETRIEVE_STOPPED)) ? STRING(IDS_HEX_STATUSBAR_AUTOBACKWARDMODE) : (((GetRetrieveMode() & HEX_RETRIEVE_PSEUDOREALTIME) && !(GetRetrieveMode() & HEX_RETRIEVE_STOPPED)) ? STRING(IDS_HEX_STATUSBAR_PSEUDOREALTIMEMODE) : ((!szMode.IsEmpty()) ? (STRING(IDS_HEX_STATUSBAR_NORMALMODE) + szMode) : STRING(IDS_HEX_STATUSBAR_NORMALMODE))))) : ((!szMode.IsEmpty()) ? (STRING(IDS_DISPLAY_MODE_REALTIME) + szMode) : STRING(IDS_DISPLAY_MODE_REALTIME)));
	m_wndToolBar.EnableButton(IDM_HEXRETRIEVESTOP, (IsRetrievingData() && ((GetRetrieveMode() & HEX_RETRIEVE_AUTOFORWARD) || (GetRetrieveMode() & HEX_RETRIEVE_AUTOBACKWARD) || (GetRetrieveMode() & HEX_RETRIEVE_PSEUDOREALTIME) || HIWORD(IsRetrievingData())) && !(GetRetrieveMode() & HEX_RETRIEVE_STOPPED)) ? TRUE : FALSE);
	m_wndToolBar.EnableButton(IDM_HEXRETRIEVEFORWARD, (IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & HEX_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & HEX_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & HEX_RETRIEVE_STOPPED))) ? TRUE : FALSE);
	m_wndToolBar.EnableButton(IDM_HEXRETRIEVEBACKWARD, (IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & HEX_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & HEX_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & HEX_RETRIEVE_STOPPED)) && !(GetRetrieveMode() & HEX_RETRIEVE_REDODUMPS)) ? TRUE : FALSE);
	m_wndToolBar.EnableButton(IDM_HEXRETRIEVESTEPFORWARD, (IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & HEX_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & HEX_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & HEX_RETRIEVE_STOPPED))) ? TRUE : FALSE);
	m_wndToolBar.EnableButton(IDM_HEXRETRIEVESTEPBACKWARD, (IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & HEX_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & HEX_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & HEX_RETRIEVE_STOPPED)) && !(GetRetrieveMode() & HEX_RETRIEVE_REDODUMPS)) ? TRUE : FALSE);
	m_wndToolBar.EnableButton(IDM_HEXRETRIEVEPSEUDOREALTIME, (IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & HEX_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & HEX_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & HEX_RETRIEVE_STOPPED))) ? TRUE : FALSE);
}

VOID CHEXWnd::UpdateTypePane()
{
	CString  szType;
	CString  szLayout;

	switch (HIWORD(GetType()))
	{
	case HEX_TYPE_NORMAL:
	{ if (GetLayout(szLayout))
	{
		szType.Format(STRING(IDS_HEX_STATUSBAR_TYPENORMAL), (LPCTSTR)szLayout);
		break;
	}
	szType = STRING(IDS_HEX_STATUSBAR_TYPENORMAL);
	szType = szType.Left((szType.Find(SPACE) >= 0) ? szType.Find(SPACE) : lstrlen(STRING(IDS_HEX_STATUSBAR_TYPENORMAL)));
	break;
	}
	case HEX_TYPE_STREAM:
	{ szType = STRING(IDS_HEX_STATUSBAR_TYPESTREAM);
	break;
	}
	case HEX_TYPE_DUMPS:
	{ szType = STRING(IDS_HEX_STATUSBAR_TYPEDUMPS);
	break;
	}
	}
	m_wndStatusBar.SetPaneText(ID_HEX_STATUSBAR_TYPEPANE, szType);
}

VOID CHEXWnd::UpdateData()
{
	UINT  nTag;
	WORD  wQuality[2];
	CString  szTag[2];
	CTimeTag  tTag[2];
	CDisplayLock  cLock(this);

	if (GetUpdateInfo(szTag[0], tTag[0], nTag, wQuality[0]))
	{
		if (HIWORD(GetType()) == HEX_TYPE_NORMAL || HIWORD(GetType()) == HEX_TYPE_STREAM)
		{
			if (m_wndDataView.Initialize(szTag[1], tTag[1], wQuality[1]) && m_wndSpyView.Initialize())
			{
				SetUpdateInfo(szTag[1], tTag[1], (szTag[0] == szTag[1] && tTag[0] == tTag[1]) ? nTag : -1, (szTag[0] != szTag[1] || tTag[0] != tTag[1]) ? wQuality[1] : wQuality[0]);
				return;
			}
		}
		if (HIWORD(GetType()) == HEX_TYPE_DUMPS)
		{
			SetUpdateInfo(szTag[0], tTag[0], nTag, wQuality[0]);
			m_wndDataView.Update();
		}
	}
}

BOOL CHEXWnd::StartSchedulePrintJobs()
{
	return IsSchedulingPrintJobs() || m_cPrintThread.Start(this);
}

BOOL CHEXWnd::IsSchedulingPrintJobs() CONST
{
	return((m_cPrintThread.IsThreadActive()) ? TRUE : FALSE);
}

BOOL CHEXWnd::StopSchedulePrintJobs()
{
	return((IsSchedulingPrintJobs() && m_cPrintThread.Stop()) ? TRUE : FALSE);
}

BOOL CHEXWnd::SetPrintJobs(CONST CByteArray &nPrintInfo)
{
	CHEXPrintJobs  pPrintJobs;

	return((pPrintJobs.Unmap(nPrintInfo)) ? SetPrintJobs(pPrintJobs) : FALSE);
}

BOOL CHEXWnd::GetPrintJobs(CByteArray &nPrintInfo) CONST
{
	CHEXPrintJobs  pPrintJobs;

	return((GetPrintJobs(pPrintJobs)) ? pPrintJobs.Map(nPrintInfo) : FALSE);
}

BOOL CHEXWnd::GetPrintProperties(CONST CHEXPrintJobInfo *pJobInfo, UINT &nMode, CString &szTMUnit, CTimeTag &tTMUnit, UINT &nTMUnit, BOOL &bQuality, CString &szDataTitle, CString &szSpyTitle, CStringArray &szDataColumns, CStringArray &szSpyColumns, CStringArray &szDataContents, CStringArray &szSpyContents, CTextViewAttributes &pDataAttributes, CTextViewAttributes &pSpyAttributes, LOGFONT *pDataTitleFont, LOGFONT *pSpyTitleFont, LOGFONT *pDataContentsFont, LOGFONT *pSpyContentsFont) CONST
{
	UINT  nPrintMode;
	UINT  nPrintCount[2];
	WORD  wPrintQuality;
	CDisplayLock  cLock(this);

	if (((nPrintMode = GetMode()) == DISPLAY_MODE_REALTIME || nPrintMode == DISPLAY_MODE_HISTORY) && GetUpdateInfo(szTMUnit, tTMUnit, nTMUnit, wPrintQuality) && m_wndDataView.GetPrintProperties(szDataTitle, szDataColumns, szDataContents, pDataAttributes, pDataTitleFont, pDataContentsFont) && m_wndSpyView.GetPrintProperties(szSpyTitle, szSpyColumns, szSpyContents, pSpyAttributes, pSpyTitleFont, pSpyContentsFont))
	{
		if ((!((nPrintMode = pJobInfo->GetPrintMode()) & HEX_PRINT_FIRSTDATASIDE) && !(nPrintMode & HEX_PRINT_LASTDATASIDE) && !(nPrintMode & HEX_PRINT_FIRSTSPYLOCATIONSSIDE) && !(nPrintMode & HEX_PRINT_LASTSPYLOCATIONSSIDE)) || pJobInfo->GetPrintBySide(nPrintCount[0], nPrintCount[1]))
		{
			if ((nPrintMode & (HEX_PRINT_FIRSTDATASIDE | HEX_PRINT_LASTDATASIDE)) && nPrintCount[0] < (UINT)szDataContents.GetSize())
			{
				szDataContents.RemoveAt((nPrintMode & HEX_PRINT_FIRSTDATASIDE) ? nPrintCount[0] : 0, (nPrintMode & HEX_PRINT_FIRSTDATASIDE) ? (szDataContents.GetSize() - nPrintCount[0]) : 0);
				szDataContents.RemoveAt(0, (nPrintMode & HEX_PRINT_LASTDATASIDE) ? (szDataContents.GetSize() - nPrintCount[0]) : 0);
			}
			if ((nPrintMode & (HEX_PRINT_FIRSTSPYLOCATIONSSIDE | HEX_PRINT_LASTSPYLOCATIONSSIDE)) && nPrintCount[1] < (UINT)szSpyContents.GetSize())
			{
				szSpyContents.RemoveAt((nPrintMode & HEX_PRINT_FIRSTSPYLOCATIONSSIDE) ? nPrintCount[1] : 0, (nPrintMode & HEX_PRINT_FIRSTSPYLOCATIONSSIDE) ? (szSpyContents.GetSize() - nPrintCount[1]) : 0);
				szSpyContents.RemoveAt(0, (nPrintMode & HEX_PRINT_LASTSPYLOCATIONSSIDE) ? (szSpyContents.GetSize() - nPrintCount[1]) : 0);
			}
			bQuality = ((wPrintQuality & (TMUNIT_DATAQUALITY_GOOD | TMUNIT_SEQUENCEQUALITY_GOOD)) == (TMUNIT_DATAQUALITY_GOOD | TMUNIT_SEQUENCEQUALITY_GOOD)) ? TRUE : FALSE;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CHEXWnd::StartPrintJob(CDC &cDC)
{
	DOCINFO  sJobInfo;
	CString  szLayout;
	CString  szJobTitle;

	for (GetLayout(szLayout), sJobInfo.fwType = 0, sJobInfo.cbSize = sizeof(DOCINFO), sJobInfo.lpszDocName = (LPTSTR)EMPTYSTRING, sJobInfo.lpszOutput = (LPCTSTR)NULL, sJobInfo.lpszDatatype = (LPCTSTR)NULL, szJobTitle.Format(STRING(IDS_PRINTJOB_DEFAULTTITLE), (LPCTSTR)GetAppTitle(), (LPCTSTR)GetAccountSpacecraftName(), (LPCTSTR)GetPrintDocSubTitle(szLayout), STRING(IDS_DISPLAY_TITLE_HEX)); szJobTitle.GetLength() >= 0; )
	{
		sJobInfo.lpszDocName = (LPTSTR)(LPCTSTR)szJobTitle;
		break;
	}
	return((cDC.StartDoc(&sJobInfo) >= 0) ? TRUE : FALSE);
}

BOOL CHEXWnd::PrintJob(CDC &cDC, CONST CHEXPrintJobInfo *pJobInfo, LPCTSTR pszPrinterName, INT nFromPage, INT nToPage, CONST RECT &rtMargin, BOOL bMetric, LPCTSTR pszLayout, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality, LPCTSTR pszDataTitle, LPCTSTR pszSpyTitle, CONST CStringArray &szDataColumns, CONST CStringArray &szSpyColumns, CONST CStringArray &szDataContents, CONST CStringArray &szSpyContents, CONST CTextViewAttributes &pDataAttributes, CONST CTextViewAttributes &pSpyAttributes, CONST LOGFONT *pDataTitleFont, CONST LOGFONT *pSpyTitleFont, CONST LOGFONT *pDataContentsFont, CONST LOGFONT *pSpyContentsFont)
{
	INT  nPage;
	INT  nPages;
	INT  nLine;
	INT  nLines;
	INT  nColumn;
	INT  nColumns;
	INT  nSpacing;
	INT  nHeight[2];
	BOOL  bOverlap;
	BOOL  bOutput;
	BOOL  bSpy;
	CRgn  rgnArea;
	CRect  rArea;
	CRect  rCalc;
	CRect  rClip;
	CRect  rItem;
	CFont  *pOldFont;
	CFont  cFont[HEX_PRINTFONTS];
	CString  szColumn;
	COLORREF  nColor;
	COLORREF  nOldColor;
	CTimeKey  tPrint;
	CPtrArray  pFonts;
	CUIntArray  nTabs[2];
	TEXTMETRIC  tmFont[2];
	CStringArray  szColumns;
	CStringArray  szContents;
	CStringArray  szColumnsText;

	for (nPage = nPages = 0, ZeroMemory(&tmFont[0], sizeof(TEXTMETRIC)), ZeroMemory(&tmFont[1], sizeof(TEXTMETRIC)); (!nPages || nPage <= nPages) && (nPages > 0 || (nPages = (CalcPrintDocRect(cDC, rtMargin, bMetric) && cDC.GetClipBox(rArea) != ERROR && rgnArea.CreateRectRgnIndirect(rArea) && CalcPrintDocTitleFont(cDC, rArea, cFont[HEX_PRINTFONT_TITLE]) && CalcPrintDocSubTitleFont(cDC, rArea, cFont[HEX_PRINTFONT_SUBTITLE]) && CalcPrintDocOperatingDetailsFont(cDC, rArea, cFont[HEX_PRINTFONT_OPERATINGDETAILS]) && CalcPrintDocOperatingModeFont(cDC, rArea, cFont[HEX_PRINTFONT_OPERATINGMODE]) && CalcPrintDocListTitleFont(cDC, rArea, cFont[HEX_PRINTFONT_DATATITLE]) && CalcPrintDocListItemsFonts(cDC, rArea, szDataColumns, szDataContents, pDataTitleFont, pDataContentsFont, cFont[HEX_PRINTFONT_DATALISTITEMSTITLE], cFont[HEX_PRINTFONT_DATALISTITEMS]) && CalcPrintDocListTitleFont(cDC, rArea, cFont[HEX_PRINTFONT_SPYTITLE]) && CalcPrintDocListItemsFonts(cDC, rArea, szSpyColumns, szSpyContents, pSpyTitleFont, pSpyContentsFont, cFont[HEX_PRINTFONT_SPYLISTITEMSTITLE], cFont[HEX_PRINTFONT_SPYLISTITEMS]) && CalcPrintDocNoticeFonts(cDC, rArea, cFont[HEX_PRINTFONT_NOTICE], cFont[HEX_PRINTFONT_LOGO]) && CalcPrintDocFooterFont(cDC, rArea, cFont[HEX_PRINTFONT_FOOTER]) && CalcPrintDocTitleWidth(cDC, szDataColumns, szDataContents, &cFont[HEX_PRINTFONT_DATALISTITEMSTITLE], &cFont[HEX_PRINTFONT_DATALISTITEMS], nTabs[0]) == szDataColumns.GetSize() && CalcPrintDocTitleWidth(cDC, szSpyColumns, szSpyContents, &cFont[HEX_PRINTFONT_SPYLISTITEMSTITLE], &cFont[HEX_PRINTFONT_SPYLISTITEMS], nTabs[1]) == szSpyColumns.GetSize()) ? nPages : -1) == 0); )
	{
		for (szColumns.Copy(szDataColumns), szContents.Copy(szDataContents), pFonts.SetAtGrow(HEX_PRINTFONT_TITLE, &cFont[HEX_PRINTFONT_TITLE]), pFonts.SetAtGrow(HEX_PRINTFONT_SUBTITLE, &cFont[HEX_PRINTFONT_SUBTITLE]), pFonts.SetAtGrow(HEX_PRINTFONT_OPERATINGDETAILS, &cFont[HEX_PRINTFONT_OPERATINGDETAILS]), pFonts.SetAtGrow(HEX_PRINTFONT_OPERATINGMODE, &cFont[HEX_PRINTFONT_OPERATINGMODE]), pFonts.SetAtGrow(HEX_PRINTFONT_DATATITLE, &cFont[HEX_PRINTFONT_DATATITLE]), pFonts.SetAtGrow(HEX_PRINTFONT_DATALISTITEMSTITLE, &cFont[HEX_PRINTFONT_DATALISTITEMSTITLE]), pFonts.SetAtGrow(HEX_PRINTFONT_DATALISTITEMS, &cFont[HEX_PRINTFONT_DATALISTITEMS]), pFonts.SetAtGrow(HEX_PRINTFONT_SPYTITLE, &cFont[HEX_PRINTFONT_SPYTITLE]), pFonts.SetAtGrow(HEX_PRINTFONT_SPYLISTITEMSTITLE, &cFont[HEX_PRINTFONT_SPYLISTITEMSTITLE]), pFonts.SetAtGrow(HEX_PRINTFONT_SPYLISTITEMS, &cFont[HEX_PRINTFONT_SPYLISTITEMS]), pFonts.SetAtGrow(HEX_PRINTFONT_FOOTER, &cFont[HEX_PRINTFONT_FOOTER]), pFonts.SetAtGrow(HEX_PRINTFONT_NOTICE, &cFont[HEX_PRINTFONT_NOTICE]), pFonts.SetAtGrow(HEX_PRINTFONT_LOGO, &cFont[HEX_PRINTFONT_LOGO]); (pOldFont = cDC.SelectObject(&cFont[HEX_PRINTFONT_DATALISTITEMS])); )
		{
			cDC.GetTextMetrics(&tmFont[0]);
			cDC.SelectObject(pOldFont);
			break;
		}
		if ((pOldFont = cDC.SelectObject(&cFont[HEX_PRINTFONT_SPYLISTITEMS])))
		{
			cDC.GetTextMetrics(&tmFont[1]);
			cDC.SelectObject(pOldFont);
		}
		for (rCalc.SetRectEmpty(), rClip.SetRectEmpty(), bSpy = FALSE; (nPages = (tmFont[0].tmHeight > 0 && tmFont[1].tmHeight > 0) ? nPages : -1) >= 0; )
		{
			for (nLine = 0, nLines = (INT)szContents.GetSize(), nSpacing = (!bSpy) ? max(tmFont[0].tmHeight / 16, 1) : max(tmFont[1].tmHeight / 16, 1), bOverlap = FALSE, bOutput = TRUE; nPages >= 0 && nLine < nLines; nLine++, bOutput = TRUE)
			{
				for (nColumn = 0, nColumns = (INT)szColumns.GetSize(), ExtractPrintDocText(szContents.GetAt(nLine), szColumnsText), nHeight[0] = nHeight[1] = 0; nPages >= 0 && nColumn < nColumns; nColumn++, nHeight[1] = 0)
				{
					if (rCalc.Height() > 0 && rClip.Height() > 0)
					{
						if ((pOldFont = (!bSpy) ? (CFont *)cDC.SelectObject((CFont *)pFonts.GetAt(HEX_PRINTFONT_DATALISTITEMS)) : (CFont *)cDC.SelectObject((CFont *)pFonts.GetAt(HEX_PRINTFONT_SPYLISTITEMS))))
						{
							nOldColor = cDC.SetTextColor((cDC.GetDeviceCaps(NUMCOLORS) > 2 && ((!bSpy  &&  pDataAttributes.GetAt(nLine)->GetColumnColor(nColumn, nColor)) || (bSpy  &&  pSpyAttributes.GetAt(nLine)->GetColumnColor(nColumn, nColor)))) ? nColor : cDC.GetTextColor());
							rCalc.SetRect(rCalc.left, (!nColumn) ? (rCalc.top + nSpacing) : rCalc.top, rCalc.right, (!nColumn) ? ((!bSpy) ? (rCalc.top + nSpacing + tmFont[0].tmHeight*((rClip.bottom - (rCalc.top + nSpacing)) / tmFont[0].tmHeight)) : (rCalc.top + nSpacing + tmFont[1].tmHeight*((rClip.bottom - (rCalc.top + nSpacing)) / tmFont[1].tmHeight))) : (rCalc.top + tmFont[1].tmHeight*((rClip.bottom - rCalc.top) / tmFont[1].tmHeight)));
							rItem.SetRect((nColumn > 0) ? ((!bSpy) ? (rCalc.left + nTabs[0].GetAt(nColumn - 1)) : (rCalc.left + nTabs[1].GetAt(nColumn - 1))) : rCalc.left, rCalc.top, (!bSpy) ? (rCalc.left + nTabs[0].GetAt(nColumn)) : (rCalc.left + nTabs[1].GetAt(nColumn)), rCalc.top + rClip.Height());
							cDC.DrawText((szColumn = (nColumn < szColumnsText.GetSize()) ? (LPCTSTR)szColumnsText.GetAt(nColumn) : EMPTYSTRING) + SPACE, rItem, DT_CALCRECT | DT_LEFT | DT_NOPREFIX | DT_SINGLELINE);
							cDC.DrawText(szColumn + SPACE, (nPages > 0 && (nFromPage <= 0 || nToPage <= 0 || nFromPage > nToPage || (nPage >= nFromPage  &&  nPage <= nToPage))) ? CRect(rItem.left, rItem.top, rItem.right, rCalc.bottom) : CRect(0, 0, 0, 0), DT_LEFT | DT_NOPREFIX | DT_SINGLELINE);
							nHeight[0] = ((nHeight[1] = rItem.Height()) > nHeight[0]) ? nHeight[1] : nHeight[0];
							cDC.SetTextColor(nOldColor);
							cDC.SelectObject(pOldFont);
						}
						else break;
					}
					if (((rCalc.top + nHeight[1] > rCalc.bottom || bOverlap) && nColumn == nColumns - 1) || !rCalc.Height() || !rClip.Height())
					{
						if (nPages > 0 && (nPage == nPages || (nFromPage > 0 && nToPage > 0 && nFromPage <= nToPage  &&  nPage == nToPage)))
						{
							nColumn = nColumns;
							nLines = nLine;
							nPages = nPage;
							break;
						}
						if (bOutput && (!nPages || ((!nPage || (nFromPage > 0 && nToPage > 0 && nFromPage <= nToPage && (nPage < nFromPage || nPage > nToPage)) || cDC.EndPage() >= 0) && ((nFromPage > 0 && nToPage > 0 && nFromPage <= nToPage && (nPage < nFromPage - 1 || nPage >= nToPage)) || (((((nFromPage <= 0 || nToPage <= 0 || nFromPage > nToPage) && nPage > 0) || (nFromPage > 0 && nToPage > 0 && nFromPage <= nToPage  &&  nPage != nFromPage - 1)) || StartPrintJob(cDC)) && cDC.StartPage() >= 0)))))
						{
							if (cDC.SelectClipRgn(&rgnArea) != ERROR  &&  DrawPrintDocPage(cDC, pJobInfo, tPrint, pszPrinterName, rtMargin, bMetric, pszLayout, nMode, pszTMUnit, tTMUnit, nTMUnit, bQuality, (!bSpy) ? pszDataTitle : pszSpyTitle, szColumns, bSpy, pFonts, (!bSpy) ? nTabs[0] : nTabs[1], nPages, (nPages > 0 && (nFromPage <= 0 || nToPage <= 0 || nFromPage > nToPage || (nPage >= nFromPage - 1 && nPage < nToPage))) ? (nPage + 1) : 0, rClip) && cDC.IntersectClipRect(rClip) != ERROR)
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
			if (nLine == nLines)
			{
				if (nPage <= nPages || !nPages)
				{
					if (!bSpy && (pJobInfo->GetPrintMode() & HEX_PRINT_SPYLOCATIONS) && szSpyContents.GetSize() > 0)
					{
						if (DrawPrintDocSpyTitle(cDC, (rItem = rCalc), GetPrintDocSpyTitle(pszSpyTitle), (CFont *)pFonts.GetAt(HEX_PRINTFONT_SPYTITLE), TRUE) && DrawPrintDocSpyOperatingMode(cDC, rItem, GetPrintDocSpyOperatingMode(pJobInfo), (CFont *)pFonts.GetAt(HEX_PRINTFONT_OPERATINGMODE), TRUE) && DrawPrintDocSpyListItemsTitle(cDC, rItem, szSpyColumns, (CFont *)pFonts.GetAt(HEX_PRINTFONT_SPYLISTITEMSTITLE), nTabs[1], TRUE) && (rItem.top > rItem.bottom || (DrawPrintDocSpyTitle(cDC, rCalc, GetPrintDocSpyTitle(pszSpyTitle), (CFont *)pFonts.GetAt(HEX_PRINTFONT_SPYTITLE)) && DrawPrintDocSpyOperatingMode(cDC, rCalc, GetPrintDocSpyOperatingMode(pJobInfo), (CFont *)pFonts.GetAt(HEX_PRINTFONT_OPERATINGMODE)) && DrawPrintDocSpyListItemsTitle(cDC, rCalc, szSpyColumns, (CFont *)pFonts.GetAt(HEX_PRINTFONT_SPYLISTITEMSTITLE), nTabs[1]))))
						{
							rCalc.SetRect(rCalc.left, (rItem.top <= rItem.bottom) ? rCalc.top : rClip.bottom, rCalc.right, rClip.bottom);
							szColumns.Copy(szSpyColumns);
							szContents.Copy(szSpyContents);
							bSpy = TRUE;
							continue;
						}
						nPages = -1;
					}
				}
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
							if (DrawPrintDocPage(cDC, pJobInfo, tPrint, pszPrinterName, rtMargin, bMetric, pszLayout, nMode, pszTMUnit, tTMUnit, nTMUnit, bQuality, (!bSpy) ? pszDataTitle : pszSpyTitle, szColumns, bSpy, pFonts, (!bSpy) ? nTabs[0] : nTabs[1], 1, 1, rClip))
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

BOOL CHEXWnd::EndPrintJob(CDC &cDC)
{
	return((cDC.EndDoc() >= 0) ? TRUE : FALSE);
}

BOOL CHEXWnd::DrawPrintDocPage(CDC &cDC, CONST CHEXPrintJobInfo *pJobInfo, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, CONST RECT &rtMargin, BOOL bMetric, LPCTSTR pszLayout, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality, LPCTSTR pszTitle, CONST CStringArray &szColumns, BOOL bSpy, CONST CPtrArray &pFonts, CONST CUIntArray &nTabs, INT nPages, INT nPage, LPRECT prClip)
{
	return((CalcPrintDocRect(cDC, rtMargin, bMetric) && cDC.GetClipBox(prClip) != ERROR  &&  DrawPrintDocTitle(cDC, prClip, GetPrintDocTitle(), (CFont *)pFonts.GetAt(HEX_PRINTFONT_TITLE), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocSubTitle(cDC, prClip, GetPrintDocSubTitle(pszLayout), (CFont *)pFonts.GetAt(HEX_PRINTFONT_SUBTITLE), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocOperatingDetails(cDC, prClip, GetPrintDocOperatingDetails(pJobInfo, nMode, pszTMUnit, tTMUnit, nTMUnit, bQuality), (CFont *)pFonts.GetAt(HEX_PRINTFONT_OPERATINGDETAILS), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocOperatingMode(cDC, prClip, GetPrintDocOperatingMode(pJobInfo), (CFont *)pFonts.GetAt(HEX_PRINTFONT_OPERATINGMODE), (nPage <= 0) ? TRUE : FALSE) && (bSpy || DrawPrintDocDataTitle(cDC, prClip, GetPrintDocDataTitle(pszTitle), (CFont *)pFonts.GetAt(HEX_PRINTFONT_DATATITLE), (nPage <= 0) ? TRUE : FALSE)) && (bSpy || DrawPrintDocDataOperatingMode(cDC, prClip, GetPrintDocDataOperatingMode(pJobInfo), (CFont *)pFonts.GetAt(HEX_PRINTFONT_OPERATINGMODE), (nPage <= 0) ? TRUE : FALSE)) && (!bSpy || DrawPrintDocSpyTitle(cDC, prClip, GetPrintDocSpyTitle(pszTitle), (CFont *)pFonts.GetAt(HEX_PRINTFONT_SPYTITLE), (nPage <= 0) ? TRUE : FALSE)) && (!bSpy || DrawPrintDocSpyOperatingMode(cDC, prClip, GetPrintDocSpyOperatingMode(pJobInfo), (CFont *)pFonts.GetAt(HEX_PRINTFONT_OPERATINGMODE), (nPage <= 0) ? TRUE : FALSE)) && (!bSpy || DrawPrintDocSpyListItemsTitle(cDC, prClip, szColumns, (CFont *)pFonts.GetAt(HEX_PRINTFONT_SPYLISTITEMSTITLE), nTabs, (nPage <= 0) ? TRUE : FALSE)) && DrawPrintDocNotice(cDC, prClip, GetPrintDocNotice(), (CFont *)pFonts.GetAt(HEX_PRINTFONT_NOTICE), (CFont *)pFonts.GetAt(HEX_PRINTFONT_LOGO), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocFooter(cDC, prClip, GetPrintDocFooter(tTime, pszPrinterName, nPages, nPage), (CFont *)pFonts.GetAt(HEX_PRINTFONT_FOOTER), (nPage <= 0) ? TRUE : FALSE)) ? TRUE : FALSE);
}

BOOL CHEXWnd::DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc)
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

BOOL CHEXWnd::DrawPrintDocSubTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc)
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

BOOL CHEXWnd::DrawPrintDocOperatingDetails(CDC &cDC, LPRECT prClip, LPCTSTR pszComments, CFont *pFont, BOOL bCalc)
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

BOOL CHEXWnd::DrawPrintDocOperatingMode(CDC &cDC, LPRECT prClip, LPCTSTR pszMode, CFont *pFont, BOOL bCalc)
{
	CRect  rCalc;
	CFont  *pOldFont;

	if ((pOldFont = cDC.SelectObject(pFont)))
	{
		cDC.DrawText(pszMode, (rCalc = CRect(0, 0, prClip->right - prClip->left, 0)), DT_CALCRECT | DT_CENTER | DT_NOPREFIX | DT_WORDBREAK);
		cDC.DrawText(pszMode, (!bCalc) ? prClip : CRect(0, 0, 0, 0), DT_CENTER | DT_NOPREFIX | DT_WORDBREAK);
		prClip->top += rCalc.Height();
		cDC.SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXWnd::DrawPrintDocDataTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc)
{
	CRect  rCalc;
	CFont  *pOldFont;

	if ((pOldFont = cDC.SelectObject(pFont)))
	{
		cDC.DrawText(pszTitle, (rCalc = CRect(0, 0, prClip->right - prClip->left, 0)), DT_CALCRECT | DT_LEFT | DT_NOPREFIX | DT_WORDBREAK);
		cDC.DrawText(pszTitle, (!bCalc) ? prClip : CRect(0, 0, 0, 0), DT_LEFT | DT_NOPREFIX | DT_WORDBREAK);
		prClip->top += rCalc.Height();
		cDC.SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXWnd::DrawPrintDocDataOperatingMode(CDC &cDC, LPRECT prClip, LPCTSTR pszMode, CFont *pFont, BOOL bCalc)
{
	CRect  rCalc;
	CFont  *pOldFont;

	if ((pOldFont = cDC.SelectObject(pFont)))
	{
		cDC.DrawText(pszMode, (rCalc = CRect(0, 0, prClip->right - prClip->left, 0)), DT_CALCRECT | DT_LEFT | DT_NOPREFIX | DT_WORDBREAK);
		cDC.DrawText(pszMode, (!bCalc) ? prClip : CRect(0, 0, 0, 0), DT_LEFT | DT_NOPREFIX | DT_WORDBREAK);
		prClip->top += rCalc.Height();
		cDC.SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXWnd::DrawPrintDocSpyTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc)
{
	CRect  rCalc;
	CFont  *pOldFont;

	if ((pOldFont = cDC.SelectObject(pFont)))
	{
		cDC.DrawText(pszTitle, (rCalc = CRect(0, 0, prClip->right - prClip->left, 0)), DT_CALCRECT | DT_LEFT | DT_NOPREFIX | DT_WORDBREAK);
		cDC.DrawText(pszTitle, (!bCalc) ? prClip : CRect(0, 0, 0, 0), DT_LEFT | DT_NOPREFIX | DT_WORDBREAK);
		prClip->top += rCalc.Height();
		cDC.SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXWnd::DrawPrintDocSpyOperatingMode(CDC &cDC, LPRECT prClip, LPCTSTR pszMode, CFont *pFont, BOOL bCalc)
{
	CRect  rCalc;
	CFont  *pOldFont;

	if ((pOldFont = cDC.SelectObject(pFont)))
	{
		cDC.DrawText(pszMode, (rCalc = CRect(0, 0, prClip->right - prClip->left, 0)), DT_CALCRECT | DT_LEFT | DT_NOPREFIX | DT_WORDBREAK);
		cDC.DrawText(pszMode, (!bCalc) ? prClip : CRect(0, 0, 0, 0), DT_LEFT | DT_NOPREFIX | DT_WORDBREAK);
		prClip->top += rCalc.Height();
		cDC.SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXWnd::DrawPrintDocSpyListItemsTitle(CDC &cDC, LPRECT prClip, CONST CStringArray &szColumns, CFont *pFont, CONST CUIntArray &nTabs, BOOL bCalc)
{
	CSize  rCalc;
	CFont  *pOldFont;
	CString  szItems;

	if ((pOldFont = cDC.SelectObject(pFont)))
	{
		szItems = GetPrintDocSpyListItemsTitle(szColumns);
		rCalc = (!bCalc) ? cDC.TabbedTextOut(prClip->left, prClip->top, szItems, (INT)nTabs.GetSize(), (LPINT)nTabs.GetData(), prClip->left) : CSize(nTabs.GetAt(nTabs.GetSize() - 1), cDC.GetTextExtent(szItems, szItems.GetLength()).cy);
		prClip->top += rCalc.cy;
		cDC.SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CHEXWnd::DrawPrintDocNotice(CDC &cDC, LPRECT prClip, LPCTSTR pszNotice, CFont *pFont, CFont *pLogoFont, BOOL bCalc)
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

BOOL CHEXWnd::DrawPrintDocFooter(CDC &cDC, LPRECT prClip, LPCTSTR pszFooter, CFont *pFont, BOOL bCalc)
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

CString CHEXWnd::GetPrintDocTitle() CONST
{
	CString  szTitle;

	szTitle.Format(STRING(IDS_HEX_PRINTDOCUMENT_TITLE), (LPCTSTR)GetAccountSpacecraftName());
	return szTitle;
}

CString CHEXWnd::GetPrintDocSubTitle(LPCTSTR pszLayout) CONST
{
	CString  szTitle;

	if (GetDatabase()->GetTMPackets()->Find(pszLayout) >= 0)
	{
		szTitle = GetDatabase()->GetTMPackets()->GetAt(GetDatabase()->GetTMPackets()->Find(pszLayout))->GetDescription();
		return szTitle;
	}
	return pszLayout;
}

CString CHEXWnd::GetPrintDocOperatingDetails(CONST CHEXPrintJobInfo *pJobInfo, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality) CONST
{
	CString  szMode;
	CString  szNumber;
	CString  szUpdate;
	CStringTools  cStringTools;

	szNumber = cStringTools.ConvertUIntToString(-1);
	szMode = (nMode == DISPLAY_MODE_REALTIME) ? STRING(IDS_DISPLAY_MODE_REALTIME) : STRING(IDS_DISPLAY_MODE_HISTORY);
	szUpdate.Format((!lstrlen(pszTMUnit)) ? ((tTMUnit > 0) ? STRING(IDS_HEX_PRINTDOCUMENT_FULLUPDATECOMMENT) : STRING(IDS_HEX_PRINTDOCUMENT_NODATACOMMENT)) : ((nTMUnit == (UINT)-1) ? STRING(IDS_HEX_PRINTDOCUMENT_INITUPDATECOMMENT) : STRING(IDS_HEX_PRINTDOCUMENT_UPDATECOMMENT)), (LPCTSTR)tTMUnit.FormatGmt(), pszTMUnit, nTMUnit, (bQuality) ? STRING(IDS_HEX_PRINTDOCUMENT_QUALITYGOOD) : STRING(IDS_HEX_PRINTDOCUMENT_QUALITYBAD));
	szUpdate = (nTMUnit == (UINT)-1 && szUpdate.Find(szNumber) >= 0) ? (szUpdate.Left(szUpdate.Find(szNumber)) + szUpdate.Mid(szUpdate.Find(szNumber) + szNumber.GetLength())) : szUpdate;
	return((!pJobInfo->GetComments().IsEmpty()) ? (szUpdate + EOL + szMode + EOL + pJobInfo->GetComments()) : (szUpdate + EOL + szMode));
}

CString CHEXWnd::GetPrintDocOperatingMode(CONST CHEXPrintJobInfo *pJobInfo) CONST
{
	UINT  nFlags;
	UINT  nStopCount;
	CString  szEvent;
	CString  szInfo;
	CTimeKey  tTime;
	CTimeKey  tLastTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CTimeSpan  tDailyTime;

	if ((nFlags = pJobInfo->GetPrintFlags()) & HEX_PRINT_ATTIME)
	{
		if (pJobInfo->GetPrintAtTime(tTime))
		{
			szInfo.Format(STRING(IDS_HEX_PRINTDOCUMENT_PRINTATTIME), (LPCTSTR)tTime.FormatGmt());
			szInfo += EOL;
		}
		if ((pJobInfo->GetPrintAtTime(tTime, tInterval) || pJobInfo->GetPrintAtTime(tTime, tInterval, nStopCount) || pJobInfo->GetPrintAtTime(tTime, tInterval, tStopTime)) && pJobInfo->GetPrintLastTime(tLastTime))
		{
			szInfo.Format(STRING(IDS_HEX_PRINTDOCUMENT_PRINTATTIME), (LPCTSTR)CTimeKey(tTime.GetTime() + ((tLastTime.GetTime() - tTime.GetTime()) / tInterval.GetTotalSeconds())*tInterval.GetTotalSeconds()).FormatGmt());
			szInfo += EOL;
		}
	}
	if (nFlags & HEX_PRINT_ATDAILYTIME)
	{
		if (pJobInfo->GetPrintAtDailyTime(tDailyTime) || pJobInfo->GetPrintAtDailyTime(tDailyTime, nStopCount) || pJobInfo->GetPrintAtDailyTime(tDailyTime, tStopTime))
		{
			szInfo.Format(STRING(IDS_HEX_PRINTDOCUMENT_PRINTATDAILYTIME), (LPCTSTR)CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + tDailyTime.GetTotalSeconds()).FormatGmt(STRING(IDS_TIMEKEY_TIMEFORMAT)));
			szInfo += EOL;
		}
	}
	if (nFlags & HEX_PRINT_ATEVENT)
	{
		if (pJobInfo->GetPrintAtEvent(szEvent))
		{
			szInfo.Format(STRING(IDS_HEX_PRINTDOCUMENT_PRINTATEVENT), (LPCTSTR)szEvent);
			szInfo += EOL;
		}
	}
	if (!nFlags)
	{
		szInfo = STRING(IDS_HEX_PRINTDOCUMENT_DEFAULTTIME);
		szInfo += EOL;
	}
	return szInfo;
}

CString CHEXWnd::GetPrintDocDataTitle(LPCTSTR pszTitle) CONST
{
	return CString(EOL) + CString(EOL) + pszTitle;
}

CString CHEXWnd::GetPrintDocDataOperatingMode(CONST CHEXPrintJobInfo *pJobInfo) CONST
{
	UINT  nMode;
	UINT  nCount[2];
	CString  szInfo;
	CString  szSide;

	if ((nMode = pJobInfo->GetPrintMode()) & HEX_PRINT_ALLDATA)
	{
		szInfo += STRING(IDS_HEX_PRINTDOCUMENT_PRINTALL);
		szInfo += EOL;
	}
	if (((nMode & HEX_PRINT_FIRSTDATASIDE) || (nMode & HEX_PRINT_LASTDATASIDE)) && pJobInfo->GetPrintBySide(nCount[0], nCount[1]))
	{
		szSide.Format((nMode & HEX_PRINT_FIRSTDATASIDE) ? STRING(IDS_HEX_PRINTDOCUMENT_PRINTBYFIRSTSIDE) : STRING(IDS_HEX_PRINTDOCUMENT_PRINTBYLASTSIDE), nCount[0]);
		szSide = (nCount[0] == 1) ? ((nMode & HEX_PRINT_FIRSTDATASIDE) ? STRING(IDS_HEX_PRINTDOCUMENT_PRINTBYFIRSTITEM) : STRING(IDS_HEX_PRINTDOCUMENT_PRINTBYLASTITEM)) : (LPCTSTR)szSide;
		szInfo += szSide + EOL;
	}
	return szInfo;
}

CString CHEXWnd::GetPrintDocSpyTitle(LPCTSTR pszTitle) CONST
{
	return CString(EOL) + CString(EOL) + pszTitle;
}

CString CHEXWnd::GetPrintDocSpyOperatingMode(CONST CHEXPrintJobInfo *pJobInfo) CONST
{
	UINT  nMode;
	UINT  nCount[2];
	CString  szInfo;
	CString  szSide;

	if ((nMode = pJobInfo->GetPrintMode()) & HEX_PRINT_ALLSPYLOCATIONS)
	{
		szInfo += STRING(IDS_HEX_PRINTDOCUMENT_PRINTALL);
		szInfo += EOL;
	}
	if (((nMode & HEX_PRINT_FIRSTSPYLOCATIONSSIDE) || (nMode & HEX_PRINT_LASTSPYLOCATIONSSIDE)) && pJobInfo->GetPrintBySide(nCount[0], nCount[1]))
	{
		szSide.Format((nMode & HEX_PRINT_FIRSTSPYLOCATIONSSIDE) ? STRING(IDS_HEX_PRINTDOCUMENT_PRINTBYFIRSTSIDE) : STRING(IDS_HEX_PRINTDOCUMENT_PRINTBYLASTSIDE), nCount[1]);
		szSide = (nCount[1] == 1) ? ((nMode & HEX_PRINT_FIRSTSPYLOCATIONSSIDE) ? STRING(IDS_HEX_PRINTDOCUMENT_PRINTBYFIRSTITEM) : STRING(IDS_HEX_PRINTDOCUMENT_PRINTBYLASTITEM)) : (LPCTSTR)szSide;
		szInfo += szSide + EOL;
	}
	return szInfo;
}

CString CHEXWnd::GetPrintDocSpyListItemsTitle(CONST CStringArray &szColumns) CONST
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

CString CHEXWnd::GetPrintDocNotice() CONST
{
	CVersionInfo  cVersionInfo;

	return cVersionInfo.QueryComments();
}

CString CHEXWnd::GetPrintDocFooter(CONST CTimeKey &tTime, LPCTSTR pszPrinterName, INT nPages, INT nPage) CONST
{
	CString  szFooter;

	szFooter.Format(STRING(IDS_HEX_PRINTDOCUMENT_FOOTER), (LPCTSTR)tTime.Format(IDS_TIMEKEY_DATEFORMAT), (LPCTSTR)tTime.Format(IDS_TIMEKEY_TIMEFORMAT), pszPrinterName, nPage, nPages);
	return szFooter;
}

INT CHEXWnd::ExtractPrintDocText(LPCTSTR pszText, CStringArray &szColumnsText) CONST
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

BOOL CHEXWnd::CalcPrintDocTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 48, (INT)((-5.3*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CHEXWnd::CalcPrintDocSubTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 64, (INT)((-4.0*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CHEXWnd::CalcPrintDocOperatingDetailsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 76, (INT)((-3.3*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CHEXWnd::CalcPrintDocOperatingModeFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 76, (INT)((-3.3*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CHEXWnd::CalcPrintDocListTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 64, (INT)((-4.0*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CHEXWnd::CalcPrintDocListItemsFonts(CDC &cDC, CONST RECT &rArea, CONST CStringArray &szColumns, CONST CStringArray &szContents, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont, CFont &cTitleFont, CFont &cItemsFont) CONST
{
	INT  nWidth;
	INT  nHeight;
	CFont  cFont[2];
	CUIntArray  nTabs;

	for (nHeight = max(-(rArea.right - rArea.left) / 64, (INT)((-4.0*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))); nHeight < 0; nHeight++)
	{
		if (cFont[0].CreateFont(nHeight, 0, pTitleFont->lfEscapement, pTitleFont->lfOrientation, FW_BOLD, pTitleFont->lfItalic, pTitleFont->lfUnderline, pTitleFont->lfStrikeOut, pTitleFont->lfCharSet, pTitleFont->lfOutPrecision, pTitleFont->lfClipPrecision, pTitleFont->lfQuality, pTitleFont->lfPitchAndFamily, pTitleFont->lfFaceName))
		{
			if (cFont[1].CreateFont((4 * nHeight) / 5, 0, pItemsFont->lfEscapement, pItemsFont->lfOrientation, pItemsFont->lfWeight, pItemsFont->lfItalic, pItemsFont->lfUnderline, pItemsFont->lfStrikeOut, pItemsFont->lfCharSet, pItemsFont->lfOutPrecision, pItemsFont->lfClipPrecision, pItemsFont->lfQuality, pItemsFont->lfPitchAndFamily, pItemsFont->lfFaceName))
			{
				if (CalcPrintDocTitleWidth(cDC, szColumns, szContents, &cFont[0], &cFont[1], nTabs) > 0)
				{
					if ((nWidth = nTabs.GetAt(nTabs.GetSize() - 1)) > rArea.right - rArea.left)
					{
						nHeight = (nHeight*(rArea.right - rArea.left)) / nWidth - 1;
						cFont[0].DeleteObject();
						cFont[1].DeleteObject();
						continue;
					}
					cTitleFont.Attach(cFont[0].Detach());
					cItemsFont.Attach(cFont[1].Detach());
					break;
				}
				cFont[1].DeleteObject();
			}
			cFont[0].DeleteObject();
		}
	}
	return((cTitleFont.GetSafeHandle() && cItemsFont.GetSafeHandle()) ? TRUE : FALSE);
}

BOOL CHEXWnd::CalcPrintDocNoticeFonts(CDC &cDC, CONST RECT &rArea, CFont &cFont, CFont &cLogoFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 96, (INT)((-2.6*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL) && cLogoFont.CreateFont(max(-(rArea.right - rArea.left) / 96, (INT)((-2.6*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, STRING(IDS_FONTFACE_COMPANYLOGO));
}

BOOL CHEXWnd::CalcPrintDocFooterFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 80, (INT)((-3.0*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

INT CHEXWnd::CalcPrintDocTitleWidth(CDC &cDC, LPCTSTR pszColumn, CFont *pTitleFont) CONST
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
INT CHEXWnd::CalcPrintDocTitleWidth(CDC &cDC, CONST CStringArray &szColumns, CONST CStringArray &szContents, CFont *pTitleFont, CFont *pItemsFont, CUIntArray &nTabs) CONST
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
	if ((pOldFont = cDC.SelectObject(pItemsFont)))
	{
		if (cDC.GetTextMetrics(&tmFont)) nIndent = max(tmFont.tmAveCharWidth, nIndent);
		cDC.SelectObject(pOldFont);
	}
	for (nColumn = 0, nColumns = (INT)szColumns.GetSize(), szLines.Copy(szContents); nColumn < nColumns; nColumn++)
	{
		nWidth[0] = CalcPrintDocTitleWidth(cDC, szColumns.GetAt(nColumn), pTitleFont);
		nWidth[1] = CalcPrintDocColumnWidth(cDC, szLines, pItemsFont);
		nTabs.Add((nTabs.GetSize() > 0) ? (2 * nIndent + nTabs.GetAt(nTabs.GetSize() - 1) + max(nWidth[0], nWidth[1])) : (2 * nIndent + max(nWidth[0], nWidth[1])));
	}
	if (nTabs.GetSize() > 0) nTabs.SetAt(nTabs.GetSize() - 1, nTabs.GetAt(nTabs.GetSize() - 1) - nIndent);
	return((INT)nTabs.GetSize());
}

INT CHEXWnd::CalcPrintDocColumnWidth(CDC &cDC, CStringArray &szContents, CFont *pItemsFont) CONST
{
	INT  nPos;
	INT  nLine;
	INT  nLines;
	INT  nWidth;
	CFont  *pOldFont;

	if ((pOldFont = cDC.SelectObject(pItemsFont)))
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

BOOL CHEXWnd::CalcPrintDocRect(CDC &cDC, CONST RECT &rtMargin, BOOL bMetric) CONST
{
	CRect  rClip;

	rClip.SetRect(0, 0, cDC.GetDeviceCaps(HORZRES), cDC.GetDeviceCaps(VERTRES));
	rClip.DeflateRect((bMetric) ? (rtMargin.left*cDC.GetDeviceCaps(HORZRES)) / (100 * cDC.GetDeviceCaps(HORZSIZE)) : (rtMargin.left*cDC.GetDeviceCaps(LOGPIXELSX)) / 1000, (bMetric) ? (rtMargin.top*cDC.GetDeviceCaps(VERTRES)) / (100 * cDC.GetDeviceCaps(VERTSIZE)) : (rtMargin.top*cDC.GetDeviceCaps(LOGPIXELSY)) / 1000, (bMetric) ? (rtMargin.right*cDC.GetDeviceCaps(HORZRES)) / (100 * cDC.GetDeviceCaps(HORZSIZE)) : (rtMargin.right*cDC.GetDeviceCaps(LOGPIXELSX)) / 1000, (bMetric) ? (rtMargin.bottom*cDC.GetDeviceCaps(VERTRES)) / (100 * cDC.GetDeviceCaps(VERTSIZE)) : (rtMargin.bottom*cDC.GetDeviceCaps(LOGPIXELSY)) / 1000);
	return((cDC.IntersectClipRect(rClip) != ERROR) ? TRUE : FALSE);
}

BEGIN_MESSAGE_MAP(CHEXWnd, CDisplayWnd)
	//{{AFX_MSG_MAP(CHEXWnd)
	ON_WM_CREATE()
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_SETFOCUS()
	ON_WM_SETCURSOR()
	ON_WM_PARENTNOTIFY()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_DESTROY()
	ON_COMMAND(IDM_HEXSETTINGS, OnSettings)
	ON_COMMAND(IDM_HEXRETRIEVALS, OnRetrievals)
	ON_COMMAND(IDM_HEXRETRIEVESTOP, OnRetrieveStop)
	ON_COMMAND(IDM_HEXRETRIEVEFORWARD, OnRetrieveAutoForward)
	ON_COMMAND(IDM_HEXRETRIEVEBACKWARD, OnRetrieveAutoBackward)
	ON_COMMAND(IDM_HEXRETRIEVESTEPFORWARD, OnRetrieveManualForward)
	ON_COMMAND(IDM_HEXRETRIEVESTEPBACKWARD, OnRetrieveManualBackward)
	ON_COMMAND(IDM_HEXRETRIEVEPSEUDOREALTIME, OnRetrievePseudoRealtime)
	ON_COMMAND(IDM_HEXPRINT, OnPrint)
	ON_UPDATE_COMMAND_UI(IDM_HEXSETTINGS, OnUpdateSettings)
	ON_UPDATE_COMMAND_UI(IDM_HEXRETRIEVALS, OnUpdateRetrievals)
	ON_UPDATE_COMMAND_UI(IDM_HEXRETRIEVESTOP, OnUpdateRetrieveStop)
	ON_UPDATE_COMMAND_UI(IDM_HEXRETRIEVEFORWARD, OnUpdateRetrieveAutoForward)
	ON_UPDATE_COMMAND_UI(IDM_HEXRETRIEVEBACKWARD, OnUpdateRetrieveAutoBackward)
	ON_UPDATE_COMMAND_UI(IDM_HEXRETRIEVESTEPFORWARD, OnUpdateRetrieveManualForward)
	ON_UPDATE_COMMAND_UI(IDM_HEXRETRIEVESTEPBACKWARD, OnUpdateRetrieveManualBackward)
	ON_UPDATE_COMMAND_UI(IDM_HEXRETRIEVEPSEUDOREALTIME, OnUpdateRetrievePseudoRealtime)
	ON_UPDATE_COMMAND_UI(IDM_HEXPRINT, OnUpdatePrint)
	ON_UPDATE_COMMAND_UI(ID_HEX_STATUSBAR_MESSAGEPANE, OnUpdateStatusBarMessagePane)
	ON_UPDATE_COMMAND_UI(ID_HEX_STATUSBAR_MODEPANE, OnUpdateStatusBarModePane)
	ON_UPDATE_COMMAND_UI(ID_HEX_STATUSBAR_TYPEPANE, OnUpdateStatusBarTypePane)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHEXWnd message handlers

int CHEXWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDisplayWnd::OnCreate(lpCreateStruct) != -1)
	{
		for (EnableDocking(CBRS_ALIGN_TOP); CreateToolBar() && CreateStatusBar() && CreateSplitterBar() && CreateViews() && LoadAccelTable(MAKEINTRESOURCE(IDR_HEXFRAME)); )
		{
			UpdateBars();
			return 0;
		}
	}
	return -1;
}

void CHEXWnd::OnGetMinMaxInfo(MINMAXINFO *lpMMI)
{
	CRect  rWnd;

	rWnd = RepositionViews(FALSE);
	lpMMI->ptMinTrackSize.x = max(lpMMI->ptMinTrackSize.x, rWnd.Width());
	lpMMI->ptMinTrackSize.y = max(lpMMI->ptMinTrackSize.y, rWnd.Height());
	CDisplayWnd::OnGetMinMaxInfo(lpMMI);
}

void CHEXWnd::OnSize(UINT nType, int cx, int cy)
{
	for (CDisplayWnd::OnSize(nType, cx, cy); nType != SIZE_MINIMIZED; )
	{
		if (IsWindow(m_wndDataView.GetSafeHwnd()) && IsWindow(m_wndSplitterBarCtrl[0].GetSafeHwnd()) && IsWindow(m_wndSpyView.GetSafeHwnd()))
		{
			m_wndDataView.MoveWindow(RepositionView(HEX_VIEW_DATA));
			m_wndSplitterBarCtrl[0].MoveWindow(RepositionViewSplitterBar());
			m_wndSpyView.MoveWindow(RepositionView(HEX_VIEW_SPY));
		}
		break;
	}
}

BOOL CHEXWnd::OnEraseBkgnd(CDC *pDC)
{
	if (!IsInitialized())
	{
		m_wndToolBar.UpdateWindow();
		m_wndStatusBar.UpdateWindow();
	}
	return TRUE;
}

void CHEXWnd::OnSetFocus(CWnd *pOldWnd)
{
	if (IsWindow(pOldWnd->GetSafeHwnd()))
	{
		if (pOldWnd->GetSafeHwnd() == m_wndDataView.GetSafeHwnd())
		{
			if (!RepositionViewSplitterBar().IsRectEmpty())
			{
				m_wndSpyView.SetFocus();
				return;
			}
			GetParent()->SetFocus();
			return;
		}
		if (m_wndSpyView.IsChild(pOldWnd))
		{
			GetParent()->SetFocus();
			return;
		}
		if (!m_wndDataView.IsEmpty())
		{
			m_wndDataView.SetFocus();
			return;
		}
	}
	CDisplayWnd::OnSetFocus(pOldWnd);
}

BOOL CHEXWnd::OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message)
{
	POINT  ptCursor;

	for (GetCursorPos(&ptCursor), ScreenToClient(&ptCursor); RepositionViewSplitterBar().PtInRect(ptCursor); )
	{
		SetCursor(LoadCursor((HINSTANCE)NULL, IDC_SIZENS));
		return TRUE;
	}
	return CDisplayWnd::OnSetCursor(pWnd, nHitTest, message);
}

void CHEXWnd::OnParentNotify(UINT message, LPARAM lParam)
{
	CRect  rBar;
	CPoint  ptBar;

	if (message == WM_LBUTTONDOWN)
	{
		for (rBar = RepositionViewSplitterBar(), ptBar.x = GET_X_LPARAM(lParam), ptBar.y = GET_Y_LPARAM(lParam); rBar.PtInRect(ptBar); )
		{
			for (ClientToScreen(rBar), ClientToScreen(&ptBar); m_wndSplitterBarCtrl[1].Create(GetParentFrame(), rBar, ptBar); )
			{
				m_wndSplitterBarCtrl[1].UpdateWindow();
				SetCapture();
				break;
			}
			break;
		}
	}
	CDisplayWnd::OnParentNotify(message, lParam);
}

void CHEXWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	CRect  rViews[2];

	if (GetCapture()->GetSafeHwnd() == GetSafeHwnd())
	{
		m_wndDataView.GetWindowRect(rViews[0]);
		m_wndSpyView.GetWindowRect(rViews[1]);
		ScreenToClient(rViews[0]);
		ScreenToClient(rViews[1]);
		m_wndDataView.MoveWindow(rViews[0].left, rViews[0].top, rViews[0].Width(), rViews[0].Height() + m_wndSplitterBarCtrl[1].CalcTranslation());
		m_wndSpyView.MoveWindow(rViews[1].left, rViews[1].top + m_wndSplitterBarCtrl[1].CalcTranslation(), rViews[1].Width(), rViews[1].Height() - m_wndSplitterBarCtrl[1].CalcTranslation());
		m_wndSplitterBarCtrl[0].MoveWindow(RepositionViewSplitterBar());
		m_wndSplitterBarCtrl[1].DestroyWindow();
		ReleaseCapture();
	}
	CDisplayWnd::OnLButtonUp(nFlags, point);
}

void CHEXWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	POINT  pt;
	CRect  rViews[2][2];

	if (nFlags & MK_LBUTTON)
	{
		if (GetCapture()->GetSafeHwnd() == GetSafeHwnd())
		{
			for (m_wndDataView.GetWindowRect(rViews[0][0]), m_wndSpyView.GetWindowRect(rViews[1][0]), rViews[0][1].SetRect(0, 0, m_wndDataView.GetTrackSize().cx, m_wndDataView.GetTrackSize().cy), rViews[1][1].SetRect(0, 0, m_wndSpyView.GetTrackSize().cx, m_wndSpyView.GetTrackSize().cy), pt.x = point.x, pt.y = point.y, ClientToScreen(&pt); rViews[0][0].Height() + m_wndSplitterBarCtrl[1].CalcTranslation(pt) >= rViews[0][1].Height() && rViews[1][0].Height() - m_wndSplitterBarCtrl[1].CalcTranslation(pt) >= rViews[1][1].Height(); )
			{
				m_wndSplitterBarCtrl[1].Translate(pt);
				m_wndSplitterBarCtrl[1].UpdateWindow();
				break;
			}
			if (rViews[0][0].Height() + m_wndSplitterBarCtrl[1].CalcTranslation(pt) < rViews[0][1].Height())
			{
				pt.y += rViews[0][1].Height() - rViews[0][0].Height() - m_wndSplitterBarCtrl[1].CalcTranslation(pt);
				m_wndSplitterBarCtrl[1].Translate(pt);
				m_wndSplitterBarCtrl[1].UpdateWindow();
			}
			if (rViews[1][0].Height() - m_wndSplitterBarCtrl[1].CalcTranslation(pt) < rViews[1][1].Height())
			{
				pt.y -= rViews[1][1].Height() - rViews[1][0].Height() + m_wndSplitterBarCtrl[1].CalcTranslation(pt);
				m_wndSplitterBarCtrl[1].Translate(pt);
				m_wndSplitterBarCtrl[1].UpdateWindow();
			}
		}
	}
	CDisplayWnd::OnMouseMove(nFlags, point);
}

BOOL CHEXWnd::OnCloseOpenDialog(UINT nCode)
{
	UINT  nMode;
	UINT  nSpeed;
	UINT  nHorzEnum;
	UINT  nVertEnum;
	UINT  nLineLength;
	BOOL  bBadData;
	CString  szLayout;
	LOGFONT  fntTitle;
	LOGFONT  fntData;
	LOGFONT  fntSpy[2];
	CString  szFileName;
	CTimeSpan  tInterval;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CUIntArray  nColors;
	CMemoryDump  cLayout;
	CHEXPrintJobs  pJobs;
	CHEXSpyLocations  pSpyLocations;

	if (nCode == IDOK)
	{
		for (SetMode(m_dlgOpen.GetMode()), SetType(MAKELONG(DISPLAY_TYPE_HEX, m_dlgOpen.GetType())), SetWindowText(m_dlgOpen.GetTitle()); m_dlgOpen.IsLayoutModified(); )
		{
			m_dlgOpen.GetLayout(szLayout, cLayout);
			m_dlgOpen.GetLayoutFormat(nHorzEnum, nVertEnum, nLineLength, nColors);
			m_dlgOpen.GetLayoutTitleFont(&fntTitle);
			m_dlgOpen.GetLayoutDataFont(&fntData);
			m_dlgOpen.GetLayoutSpyFont(&fntSpy[0], &fntSpy[1]);
			m_dlgOpen.GetLayoutBadDataMode(bBadData);
			m_dlgOpen.GetSpyLocations(pSpyLocations);
			if (!SetLayout(szLayout, cLayout) || !SetLayoutContents(pSpyLocations) || !SetLayoutFormat(nHorzEnum, nVertEnum, nLineLength, nColors) || !SetTitleFont(&fntTitle) || !SetDataFont(&fntData) || !SetSpyFont(&fntSpy[0], &fntSpy[1]) || !EnableBadDataMode(bBadData)) return FALSE;
			break;
		}
		if (!m_dlgOpen.IsLayoutModified())
		{
			m_dlgOpen.GetLayout(szLayout, cLayout);
			m_dlgOpen.GetSpyLocations(pSpyLocations);
			if (!SetLayout(szLayout, cLayout) || !SetLayoutContents(pSpyLocations)) return FALSE;
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

BOOL CHEXWnd::OnCloseSettingsDialog(UINT nCode)
{
	BOOL  bBadData;
	UINT  nHorzEnum;
	UINT  nVertEnum;
	UINT  nLineLength;
	LOGFONT  fntTitle;
	LOGFONT  fntData;
	LOGFONT  fntSpy[2];
	CString  szFileName;
	CUIntArray  nColors;
	CHEXPrintJobs  pJobs;
	CHEXSpyLocations  pSpyLocations;

	if (nCode == IDOK)
	{
		if (m_dlgSettings.IsLayoutModified())
		{
			m_dlgSettings.GetLayoutFormat(nHorzEnum, nVertEnum, nLineLength, nColors);
			m_dlgSettings.GetLayoutTitleFont(&fntTitle);
			m_dlgSettings.GetLayoutDataFont(&fntData);
			m_dlgSettings.GetLayoutSpyFont(&fntSpy[0], &fntSpy[1]);
			m_dlgSettings.GetLayoutBadDataMode(bBadData);
			if (!SetLayoutFormat(nHorzEnum, nVertEnum, nLineLength, nColors) || !SetTitleFont(&fntTitle) || !SetDataFont(&fntData) || !SetSpyFont(&fntSpy[0], &fntSpy[1]) || !EnableBadDataMode(bBadData)) return FALSE;
		}
		if (m_dlgSettings.IsContentsModified())
		{
			m_dlgSettings.GetSpyLocations(pSpyLocations);
			if (!SetLayoutContents(pSpyLocations)) return FALSE;
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

BOOL CHEXWnd::OnCloseRetrieveDialog(UINT nCode)
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

void CHEXWnd::OnSettings()
{
	CHourglassCursor  cCursor;

	ReportEvent((m_dlgSettings.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CHEXWnd::OnRetrievals()
{
	CHourglassCursor  cCursor;

	ReportEvent((m_dlgRetrievals.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CHEXWnd::OnRetrieveStop()
{
	RetrieveMoreData(HEX_RETRIEVE_STOPPED);
}

void CHEXWnd::OnRetrieveAutoForward()
{
	RetrieveMoreData(HEX_RETRIEVE_AUTOFORWARD);
}

void CHEXWnd::OnRetrieveAutoBackward()
{
	RetrieveMoreData(HEX_RETRIEVE_AUTOBACKWARD);
}

void CHEXWnd::OnRetrieveManualForward()
{
	RetrieveMoreData(HEX_RETRIEVE_MANUALFORWARD);
}

void CHEXWnd::OnRetrieveManualBackward()
{
	RetrieveMoreData(HEX_RETRIEVE_MANUALBACKWARD);
}

void CHEXWnd::OnRetrievePseudoRealtime()
{
	RetrieveMoreData(HEX_RETRIEVE_PSEUDOREALTIME);
}

void CHEXWnd::OnPrint()
{
	CHourglassCursor  cCursor;

	ReportEvent((!Print()) ? SYSTEM_WARNING_DISPLAY_PRINT_FAILURE : SYSTEM_NOERROR);
}

void CHEXWnd::OnDestroy()
{
	CHourglassCursor  cCursor;

	Stop();
	CDisplayWnd::OnDestroy();
}

void CHEXWnd::OnUpdateSettings(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsInitialized()) ? TRUE : FALSE);
	pCmdUI->SetCheck(IsWindow(m_dlgSettings.GetSafeHwnd()));
}

void CHEXWnd::OnUpdateRetrievals(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsInitialized()) ? TRUE : FALSE);
	pCmdUI->SetCheck(IsWindow(m_dlgRetrievals.GetSafeHwnd()));
}

void CHEXWnd::OnUpdateRetrieveStop(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && ((GetRetrieveMode() & HEX_RETRIEVE_AUTOFORWARD) || (GetRetrieveMode() & HEX_RETRIEVE_AUTOBACKWARD) || (GetRetrieveMode() & HEX_RETRIEVE_PSEUDOREALTIME) || HIWORD(IsRetrievingData())) && !(GetRetrieveMode() & HEX_RETRIEVE_STOPPED)) ? TRUE : FALSE);
}

void CHEXWnd::OnUpdateRetrieveAutoForward(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & HEX_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & HEX_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & HEX_RETRIEVE_STOPPED))) ? TRUE : FALSE);
}

void CHEXWnd::OnUpdateRetrieveAutoBackward(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & HEX_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & HEX_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & HEX_RETRIEVE_STOPPED)) && !(GetRetrieveMode() & HEX_RETRIEVE_REDODUMPS)) ? TRUE : FALSE);
}

void CHEXWnd::OnUpdateRetrieveManualForward(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & HEX_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & HEX_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & HEX_RETRIEVE_STOPPED))) ? TRUE : FALSE);
}

void CHEXWnd::OnUpdateRetrieveManualBackward(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & HEX_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & HEX_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & HEX_RETRIEVE_STOPPED)) && !(GetRetrieveMode() & HEX_RETRIEVE_REDODUMPS)) ? TRUE : FALSE);
}

void CHEXWnd::OnUpdateRetrievePseudoRealtime(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & HEX_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & HEX_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & HEX_RETRIEVE_STOPPED))) ? TRUE : FALSE);
}

void CHEXWnd::OnUpdatePrint(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsInitialized() && IsDefaultPrinterAvailable() && CanPrint()) ? TRUE : FALSE);
}

void CHEXWnd::OnUpdateStatusBarMessagePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CHEXWnd::OnUpdateStatusBarModePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CHEXWnd::OnUpdateStatusBarTypePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}
