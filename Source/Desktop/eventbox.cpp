// EVENTBOX.CPP : Eventbox Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the eventbox related
// interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1995/05/04 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static UINT BASED_CODE nEventBoxStatusBarIndicators[] =
{
	ID_EVENTBOX_STATUSBAR_ITEMPANE,
	ID_EVENTBOX_STATUSBAR_MODEPANE,
	ID_EVENTBOX_STATUSBAR_SYSTEMPANE,
	ID_EVENTBOX_STATUSBAR_SPACECRAFTPANE,
	ID_EVENTBOX_STATUSBAR_USERPANE
};



/////////////////////////////////////////////////////////////////////////////
// CEventBoxPrintJobInfo

CEventBoxPrintJobInfo::CEventBoxPrintJobInfo() : CObject()
{
	m_nPrintMode = 0;
	m_nPrintFlags = 0;
	m_nPrintCount[0] = 0;
	m_nPrintCount[1] = 0;
	m_nPrintCount[2] = 0;
	m_nPrintByCount = 0;
	m_tPrintByDailyStartTime = 0;
	m_tPrintByDailyStopTime = 0;
	m_tPrintAtTime = 0;
	m_tPrintAtDailyTime = 0;
	m_nPrintAtCount = 0;
	m_tPrintLastTime[0] = 0;
	m_tPrintLastTime[1] = 0;
	m_tRepeatInterval = 0;
	m_nRepeatStopByCount[0] = 0;
	m_nRepeatStopByCount[1] = 0;
	m_tRepeatStopByTime[0] = 0;
	m_tRepeatStopByTime[1] = 0;
}

VOID CEventBoxPrintJobInfo::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CEventBoxPrintJobInfo::GetName() CONST
{
	return m_szName;
}

VOID CEventBoxPrintJobInfo::SetProfile(LPCTSTR pszProfile)
{
	m_szProfile = pszProfile;
}

CString CEventBoxPrintJobInfo::GetProfile() CONST
{
	return m_szProfile;
}

VOID CEventBoxPrintJobInfo::SetComments(LPCTSTR pszComments)
{
	m_szComments = pszComments;
}

CString CEventBoxPrintJobInfo::GetComments() CONST
{
	return m_szComments;
}

BOOL CEventBoxPrintJobInfo::SetPrintMode(UINT nMode)
{
	m_nPrintMode = nMode;
	return TRUE;
}

UINT CEventBoxPrintJobInfo::GetPrintMode() CONST
{
	return m_nPrintMode;
}

BOOL CEventBoxPrintJobInfo::SetPrintFlags(UINT nFlags)
{
	if (nFlags == EVENTBOX_PRINT_ATTIME || nFlags == EVENTBOX_PRINT_ATDAILYTIME || nFlags == EVENTBOX_PRINT_ATCOUNT || !nFlags)
	{
		m_nPrintFlags = nFlags;
		return TRUE;
	}
	return FALSE;
}

UINT CEventBoxPrintJobInfo::GetPrintFlags() CONST
{
	return m_nPrintFlags;
}

BOOL CEventBoxPrintJobInfo::SetPrintBySide(UINT nCount)
{
	if ((m_nPrintMode & EVENTBOX_PRINT_FIRSTSIDE) || (m_nPrintMode & EVENTBOX_PRINT_LASTSIDE))
	{
		m_tPrintByDailyStartTime = 0;
		m_tPrintByDailyStopTime = 0;
		m_nPrintByCount = nCount;
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxPrintJobInfo::GetPrintBySide(UINT &nCount) CONST
{
	if ((m_nPrintMode & EVENTBOX_PRINT_FIRSTSIDE) || (m_nPrintMode & EVENTBOX_PRINT_LASTSIDE))
	{
		nCount = m_nPrintByCount;
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxPrintJobInfo::SetPrintByTime(CONST CTimeSpan &tStartTime, CONST CTimeSpan &tStopTime)
{
	if (m_nPrintMode & EVENTBOX_PRINT_DAILY)
	{
		m_tPrintByDailyStartTime = tStartTime;
		m_tPrintByDailyStopTime = tStopTime;
		m_nPrintByCount = 0;
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxPrintJobInfo::GetPrintByTime(CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST
{
	if (m_nPrintMode & EVENTBOX_PRINT_DAILY)
	{
		tStartTime = m_tPrintByDailyStartTime;
		tStopTime = m_tPrintByDailyStopTime;
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxPrintJobInfo::SetPrintAtTime(CONST CTimeKey &tTime)
{
	if ((m_nPrintMode & EVENTBOX_PRINT_ATTIME) && !(m_nPrintMode & EVENTBOX_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & EVENTBOX_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & EVENTBOX_PRINT_REPEATSTOPBYTIME))
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
BOOL CEventBoxPrintJobInfo::SetPrintAtTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval)
{
	if ((m_nPrintMode & EVENTBOX_PRINT_ATTIME) && (m_nPrintMode & EVENTBOX_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & EVENTBOX_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & EVENTBOX_PRINT_REPEATSTOPBYTIME))
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
BOOL CEventBoxPrintJobInfo::SetPrintAtTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval, UINT nStopCount)
{
	if ((m_nPrintMode & EVENTBOX_PRINT_ATTIME) && (m_nPrintMode & EVENTBOX_PRINT_REPEATBYINTERVAL) && (m_nPrintMode & EVENTBOX_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & EVENTBOX_PRINT_REPEATSTOPBYTIME))
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
BOOL CEventBoxPrintJobInfo::SetPrintAtTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval, CONST CTimeKey &tStopTime)
{
	if ((m_nPrintMode & EVENTBOX_PRINT_ATTIME) && (m_nPrintMode & EVENTBOX_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & EVENTBOX_PRINT_REPEATSTOPBYCOUNT) && (m_nPrintMode & EVENTBOX_PRINT_REPEATSTOPBYTIME))
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

BOOL CEventBoxPrintJobInfo::GetPrintAtTime(CTimeKey &tTime) CONST
{
	if ((m_nPrintMode & EVENTBOX_PRINT_ATTIME) && !(m_nPrintMode & EVENTBOX_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & EVENTBOX_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & EVENTBOX_PRINT_REPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtTime;
		return TRUE;
	}
	return FALSE;
}
BOOL CEventBoxPrintJobInfo::GetPrintAtTime(CTimeKey &tTime, CTimeSpan &tInterval) CONST
{
	if ((m_nPrintMode & EVENTBOX_PRINT_ATTIME) && (m_nPrintMode & EVENTBOX_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & EVENTBOX_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & EVENTBOX_PRINT_REPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtTime;
		tInterval = m_tRepeatInterval;
		return TRUE;
	}
	return FALSE;
}
BOOL CEventBoxPrintJobInfo::GetPrintAtTime(CTimeKey &tTime, CTimeSpan &tInterval, UINT &nStopCount) CONST
{
	if ((m_nPrintMode & EVENTBOX_PRINT_ATTIME) && (m_nPrintMode & EVENTBOX_PRINT_REPEATBYINTERVAL) && (m_nPrintMode & EVENTBOX_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & EVENTBOX_PRINT_REPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtTime;
		tInterval = m_tRepeatInterval;
		nStopCount = m_nRepeatStopByCount[0];
		return TRUE;
	}
	return FALSE;
}
BOOL CEventBoxPrintJobInfo::GetPrintAtTime(CTimeKey &tTime, CTimeSpan &tInterval, CTimeKey &tStopTime) CONST
{
	if ((m_nPrintMode & EVENTBOX_PRINT_ATTIME) && (m_nPrintMode & EVENTBOX_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & EVENTBOX_PRINT_REPEATSTOPBYCOUNT) && (m_nPrintMode & EVENTBOX_PRINT_REPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtTime;
		tInterval = m_tRepeatInterval;
		tStopTime = m_tRepeatStopByTime[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxPrintJobInfo::SetPrintAtDailyTime(CONST CTimeSpan &tTime)
{
	TIMEKEY  tTimeKey;

	if ((m_nPrintMode & EVENTBOX_PRINT_ATDAILYTIME) && !(m_nPrintMode & EVENTBOX_PRINT_DAILYREPEATSTOPBYCOUNT) && !(m_nPrintMode & EVENTBOX_PRINT_DAILYREPEATSTOPBYTIME))
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
BOOL CEventBoxPrintJobInfo::SetPrintAtDailyTime(CONST CTimeSpan &tTime, UINT nStopCount)
{
	TIMEKEY  tTimeKey;

	if ((m_nPrintMode & EVENTBOX_PRINT_ATDAILYTIME) && (m_nPrintMode & EVENTBOX_PRINT_DAILYREPEATSTOPBYCOUNT) && !(m_nPrintMode & EVENTBOX_PRINT_DAILYREPEATSTOPBYTIME))
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
BOOL CEventBoxPrintJobInfo::SetPrintAtDailyTime(CONST CTimeSpan &tTime, CONST CTimeKey &tStopTime)
{
	TIMEKEY  tTimeKey;

	if ((m_nPrintMode & EVENTBOX_PRINT_ATDAILYTIME) && !(m_nPrintMode & EVENTBOX_PRINT_DAILYREPEATSTOPBYCOUNT) && (m_nPrintMode & EVENTBOX_PRINT_DAILYREPEATSTOPBYTIME))
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

BOOL CEventBoxPrintJobInfo::GetPrintAtDailyTime(CTimeSpan &tTime) CONST
{
	if ((m_nPrintMode & EVENTBOX_PRINT_ATDAILYTIME) && !(m_nPrintMode & EVENTBOX_PRINT_DAILYREPEATSTOPBYCOUNT) && !(m_nPrintMode & EVENTBOX_PRINT_DAILYREPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtDailyTime;
		return TRUE;
	}
	return FALSE;
}
BOOL CEventBoxPrintJobInfo::GetPrintAtDailyTime(CTimeSpan &tTime, UINT &nStopCount) CONST
{
	if ((m_nPrintMode & EVENTBOX_PRINT_ATDAILYTIME) && (m_nPrintMode & EVENTBOX_PRINT_DAILYREPEATSTOPBYCOUNT) && !(m_nPrintMode & EVENTBOX_PRINT_DAILYREPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtDailyTime;
		nStopCount = m_nRepeatStopByCount[1];
		return TRUE;
	}
	return FALSE;
}
BOOL CEventBoxPrintJobInfo::GetPrintAtDailyTime(CTimeSpan &tTime, CTimeKey &tStopTime) CONST
{
	if ((m_nPrintMode & EVENTBOX_PRINT_ATDAILYTIME) && !(m_nPrintMode & EVENTBOX_PRINT_DAILYREPEATSTOPBYCOUNT) && (m_nPrintMode & EVENTBOX_PRINT_DAILYREPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtDailyTime;
		tStopTime = m_tRepeatStopByTime[1];
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxPrintJobInfo::SetPrintAtCount(UINT nCount)
{
	if (m_nPrintMode & EVENTBOX_PRINT_ATCOUNT)
	{
		m_nPrintAtCount = nCount;
		m_nPrintCount[2] = 0;
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxPrintJobInfo::GetPrintAtCount(UINT &nCount) CONST
{
	if (m_nPrintMode & EVENTBOX_PRINT_ATCOUNT)
	{
		nCount = m_nPrintAtCount;
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxPrintJobInfo::SetPrintCount(UINT nCount)
{
	if (m_nPrintMode & EVENTBOX_PRINT_ATTIME)
	{
		m_nPrintCount[0] = nCount;
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxPrintJobInfo::GetPrintCount(UINT &nCount) CONST
{
	if (m_nPrintMode & EVENTBOX_PRINT_ATTIME)
	{
		nCount = m_nPrintCount[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxPrintJobInfo::SetPrintDailyCount(UINT nCount)
{
	if (m_nPrintMode & EVENTBOX_PRINT_ATDAILYTIME)
	{
		m_nPrintCount[1] = nCount;
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxPrintJobInfo::GetPrintDailyCount(UINT &nCount) CONST
{
	if (m_nPrintMode & EVENTBOX_PRINT_ATDAILYTIME)
	{
		nCount = m_nPrintCount[1];
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxPrintJobInfo::SetPrintLastCount(UINT nCount)
{
	if (m_nPrintMode & EVENTBOX_PRINT_ATCOUNT)
	{
		m_nPrintCount[2] = nCount;
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxPrintJobInfo::GetPrintLastCount(UINT &nCount) CONST
{
	if (m_nPrintMode & EVENTBOX_PRINT_ATCOUNT)
	{
		nCount = m_nPrintCount[2];
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxPrintJobInfo::SetPrintLastTime(CONST CTimeKey &tTime)
{
	if (m_nPrintMode & EVENTBOX_PRINT_ATTIME)
	{
		m_tPrintLastTime[0] = tTime;
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxPrintJobInfo::GetPrintLastTime(CTimeKey &tTime) CONST
{
	if (m_nPrintMode & EVENTBOX_PRINT_ATTIME)
	{
		tTime = m_tPrintLastTime[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxPrintJobInfo::SetPrintLastDailyTime(CONST CTimeKey &tTime)
{
	if (m_nPrintMode & EVENTBOX_PRINT_ATDAILYTIME)
	{
		m_tPrintLastTime[1] = tTime;
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxPrintJobInfo::GetPrintLastDailyTime(CTimeKey &tTime) CONST
{
	if (m_nPrintMode & EVENTBOX_PRINT_ATDAILYTIME)
	{
		tTime = m_tPrintLastTime[1];
		return TRUE;
	}
	return FALSE;
}

VOID CEventBoxPrintJobInfo::Copy(CONST CEventBoxPrintJobInfo *pJobInfo)
{
	m_szName = pJobInfo->m_szName;
	m_szProfile = pJobInfo->m_szProfile;
	m_szComments = pJobInfo->m_szComments;
	m_nPrintMode = pJobInfo->m_nPrintMode;
	m_nPrintFlags = pJobInfo->m_nPrintFlags;
	m_nPrintCount[0] = pJobInfo->m_nPrintCount[0];
	m_nPrintCount[1] = pJobInfo->m_nPrintCount[1];
	m_nPrintCount[2] = pJobInfo->m_nPrintCount[2];
	m_nPrintByCount = pJobInfo->m_nPrintByCount;
	m_nPrintAtCount = pJobInfo->m_nPrintAtCount;
	m_tPrintByDailyStartTime = pJobInfo->m_tPrintByDailyStartTime;
	m_tPrintByDailyStopTime = pJobInfo->m_tPrintByDailyStopTime;
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

BOOL CEventBoxPrintJobInfo::Compare(CONST CEventBoxPrintJobInfo *pJobInfo) CONST
{
	return((pJobInfo->m_szName == m_szName  &&  pJobInfo->m_szProfile == m_szProfile  &&  pJobInfo->m_szComments == m_szComments  &&  pJobInfo->m_nPrintMode == m_nPrintMode && ((!(m_nPrintMode & EVENTBOX_PRINT_FIRSTSIDE) && !(m_nPrintMode & EVENTBOX_PRINT_LASTSIDE)) || pJobInfo->m_nPrintByCount == m_nPrintByCount) && (!(m_nPrintMode & EVENTBOX_PRINT_DAILY) || (pJobInfo->m_tPrintByDailyStartTime == m_tPrintByDailyStartTime  &&  pJobInfo->m_tPrintByDailyStopTime == m_tPrintByDailyStopTime)) && (!(m_nPrintMode & EVENTBOX_PRINT_ATTIME) || pJobInfo->m_tPrintAtTime == m_tPrintAtTime) && (!(m_nPrintMode & EVENTBOX_PRINT_ATDAILYTIME) || pJobInfo->m_tPrintAtDailyTime == m_tPrintAtDailyTime) && (!(m_nPrintMode & EVENTBOX_PRINT_ATCOUNT) || pJobInfo->m_nPrintAtCount == m_nPrintAtCount) && (!(m_nPrintMode & EVENTBOX_PRINT_REPEATBYINTERVAL) || pJobInfo->m_tRepeatInterval == m_tRepeatInterval) && (!(m_nPrintMode & EVENTBOX_PRINT_REPEATSTOPBYCOUNT) || pJobInfo->m_nRepeatStopByCount[0] == m_nRepeatStopByCount[0]) && (!(m_nPrintMode & EVENTBOX_PRINT_REPEATSTOPBYTIME) || pJobInfo->m_tRepeatStopByTime[0] == m_tRepeatStopByTime[0]) && (!(m_nPrintMode & EVENTBOX_PRINT_DAILYREPEATSTOPBYCOUNT) || pJobInfo->m_nRepeatStopByCount[1] == m_nRepeatStopByCount[1]) && (!(m_nPrintMode & EVENTBOX_PRINT_DAILYREPEATSTOPBYTIME) || pJobInfo->m_tRepeatStopByTime[1] == m_tRepeatStopByTime[1])) ? TRUE : FALSE);
}

BOOL CEventBoxPrintJobInfo::Map(CByteArray &nInfo) CONST
{
	INT  cbData;
	DATA  sData;

	sData.cbName = (m_szName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbProfile = (m_szProfile.GetLength() + 1)*sizeof(TCHAR);
	sData.cbComments = (m_szComments.GetLength() + 1)*sizeof(TCHAR);
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbName + sData.cbProfile + sData.cbComments)), sData.nPrintMode = m_nPrintMode, sData.nPrintCount[0] = m_nPrintCount[0], sData.nPrintCount[1] = m_nPrintCount[1], sData.nPrintCount[2] = m_nPrintCount[2], sData.nPrintByCount = m_nPrintByCount, sData.tPrintByDailyStartTime = m_tPrintByDailyStartTime.GetTotalSeconds(), sData.tPrintByDailyStopTime = m_tPrintByDailyStopTime.GetTotalSeconds(), sData.tPrintAtTime = m_tPrintAtTime.GetTime(), sData.tPrintAtDailyTime = m_tPrintAtDailyTime.GetTotalSeconds(), sData.tPrintLastTime[0] = m_tPrintLastTime[0].GetTime(), sData.tPrintLastTime[1] = m_tPrintLastTime[1].GetTime(), sData.nPrintAtCount = m_nPrintAtCount, sData.tRepeatInterval = m_tRepeatInterval.GetTotalSeconds(), sData.nRepeatStopByCount[0] = m_nRepeatStopByCount[0], sData.nRepeatStopByCount[1] = m_nRepeatStopByCount[1], sData.tRepeatStopByTime[0] = m_tRepeatStopByTime[0].GetTime(), sData.tRepeatStopByTime[1] = m_tRepeatStopByTime[1].GetTime(); nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szName, sData.cbName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbName), (LPCTSTR)m_szProfile, sData.cbProfile);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbProfile), (LPCTSTR)m_szComments, sData.cbComments);
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxPrintJobInfo::Unmap(CONST CByteArray &nInfo)
{
	INT  cbData;
	DATA  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbName + sData.cbProfile + sData.cbComments && sData.cbName > 0 && sData.cbProfile > 0 && sData.cbComments > 0; )
	{
		CopyMemory(m_szName.GetBufferSetLength(STRINGCHARS(sData.cbName)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbName));
		CopyMemory(m_szProfile.GetBufferSetLength(STRINGCHARS(sData.cbProfile)), nInfo.GetData() + (cbData = cbData + sData.cbName), STRINGBYTES(sData.cbProfile));
		CopyMemory(m_szComments.GetBufferSetLength(STRINGCHARS(sData.cbComments)), nInfo.GetData() + (cbData = cbData + sData.cbProfile), STRINGBYTES(sData.cbComments));
		m_nPrintMode = sData.nPrintMode;
		m_nPrintCount[0] = sData.nPrintCount[0];
		m_nPrintCount[1] = sData.nPrintCount[1];
		m_nPrintCount[2] = sData.nPrintCount[2];
		m_nPrintByCount = sData.nPrintByCount;
		m_tPrintByDailyStartTime = sData.tPrintByDailyStartTime;
		m_tPrintByDailyStopTime = sData.tPrintByDailyStopTime;
		m_tPrintAtTime = sData.tPrintAtTime;
		m_tPrintAtDailyTime = sData.tPrintAtDailyTime;
		m_tPrintLastTime[0] = sData.tPrintLastTime[0];
		m_tPrintLastTime[1] = sData.tPrintLastTime[1];
		m_nPrintAtCount = sData.nPrintAtCount;
		m_tRepeatInterval = sData.tRepeatInterval;
		m_nRepeatStopByCount[0] = sData.nRepeatStopByCount[0];
		m_nRepeatStopByCount[1] = sData.nRepeatStopByCount[1];
		m_tRepeatStopByTime[0] = sData.tRepeatStopByTime[0];
		m_tRepeatStopByTime[1] = sData.tRepeatStopByTime[1];
		m_szName.ReleaseBuffer();
		m_szProfile.ReleaseBuffer();
		m_szComments.ReleaseBuffer();
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CEventBoxPrintJobs

CEventBoxPrintJobs::CEventBoxPrintJobs() : CPtrArray()
{
	return;
}

CEventBoxPrintJobs::~CEventBoxPrintJobs()
{
	RemoveAll();
}

INT CEventBoxPrintJobs::Add(CEventBoxPrintJobInfo *pJobInfo)
{
	return((INT)CPtrArray::Add(pJobInfo));
}

INT CEventBoxPrintJobs::Find(LPCTSTR pszName) CONST
{
	INT  nJob;
	INT  nJobs;
	CEventBoxPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (INT)GetSize(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = GetAt(nJob)) && pJobInfo->GetName() == pszName) break;
		continue;
	}
	return((nJob < nJobs) ? nJob : -1);
}

CEventBoxPrintJobInfo *CEventBoxPrintJobs::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CEventBoxPrintJobInfo *)CPtrArray::GetAt(nIndex) : (CEventBoxPrintJobInfo *)NULL);
}

CEventBoxPrintJobInfo *CEventBoxPrintJobs::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CEventBoxPrintJobInfo *)CPtrArray::GetAt(nIndex) : (CEventBoxPrintJobInfo *)NULL);
}

TIMEKEY CEventBoxPrintJobs::Schedule(UINT nCount)
{
	INT  nJob;
	INT  nJobs;
	UINT  nJobMode;
	UINT  nJobCount[2];
	UINT  nJobPrintCount[2];
	TIMEKEY  tJobPrintTimeout[2];
	CTimeKey  tJobPrintTime[4];
	CTimeSpan  tJobPrintInterval;
	CTimeSpan  tJobPrintDailyTime;
	CEventBoxPrintJobInfo  *pJobInfo[2];

	for (nJob = 0, nJobs = (INT)GetSize(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo[0] = GetAt(nJob)) != (CEventBoxPrintJobInfo *)NULL)
		{
			if (((nJobMode = pJobInfo[0]->GetPrintMode()) & EVENTBOX_PRINT_ACTIVE) && (((nJobMode & EVENTBOX_PRINT_ATTIME) && pJobInfo[0]->GetPrintLastTime(tJobPrintTime[1]) && (tJobPrintTime[1] > 0 || pJobInfo[0]->SetPrintLastTime(tJobPrintTime[3]))) || (nJobMode & EVENTBOX_PRINT_ATDAILYTIME) || (nJobMode & EVENTBOX_PRINT_ATCOUNT)) &&
				((pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0]) && pJobInfo[0]->GetPrintCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastTime(tJobPrintTime[1]) && tJobPrintTime[3] >= tJobPrintTime[0] && tJobPrintTime[0] > tJobPrintTime[1] && pJobInfo[0]->SetPrintFlags(EVENTBOX_PRINT_ATTIME) && pJobInfo[0]->SetPrintCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0], tJobPrintInterval) && pJobInfo[0]->GetPrintCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastTime(tJobPrintTime[1]) && tJobPrintTime[3] >= tJobPrintTime[0] && (tJobPrintTime[0] > tJobPrintTime[1] || (tJobPrintTime[1].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds() < (tJobPrintTime[3].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds()) && pJobInfo[0]->SetPrintFlags(EVENTBOX_PRINT_ATTIME) && pJobInfo[0]->SetPrintCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0], tJobPrintInterval, nJobPrintCount[1]) && pJobInfo[0]->GetPrintCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastTime(tJobPrintTime[1]) && tJobPrintTime[3] >= tJobPrintTime[0] && (tJobPrintTime[0] > tJobPrintTime[1] || (tJobPrintTime[1].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds() < (tJobPrintTime[3].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds()) && nJobPrintCount[0] < nJobPrintCount[1] && pJobInfo[0]->SetPrintFlags(EVENTBOX_PRINT_ATTIME) && pJobInfo[0]->SetPrintCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0], tJobPrintInterval, tJobPrintTime[2]) && pJobInfo[0]->GetPrintCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastTime(tJobPrintTime[1]) && tJobPrintTime[3] >= tJobPrintTime[0] && (tJobPrintTime[0] > tJobPrintTime[1] || (tJobPrintTime[1].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds() < (tJobPrintTime[3].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds()) && tJobPrintTime[3] <= tJobPrintTime[2] && pJobInfo[0]->SetPrintFlags(EVENTBOX_PRINT_ATTIME) && pJobInfo[0]->SetPrintCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtDailyTime(tJobPrintDailyTime) && pJobInfo[0]->GetPrintDailyCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastDailyTime(tJobPrintTime[1]) && tJobPrintTime[3].GetTime() % SECONDSPERDAY >= tJobPrintDailyTime.GetTotalSeconds() && tJobPrintTime[3].GetTime() / SECONDSPERDAY != tJobPrintTime[1].GetTime() / SECONDSPERDAY  &&  pJobInfo[0]->SetPrintFlags(EVENTBOX_PRINT_ATDAILYTIME) && pJobInfo[0]->SetPrintDailyCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastDailyTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtDailyTime(tJobPrintDailyTime, nJobPrintCount[1]) && pJobInfo[0]->GetPrintDailyCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastDailyTime(tJobPrintTime[1]) && tJobPrintTime[3].GetTime() % SECONDSPERDAY >= tJobPrintDailyTime.GetTotalSeconds() && tJobPrintTime[3].GetTime() / SECONDSPERDAY != tJobPrintTime[1].GetTime() / SECONDSPERDAY  &&  nJobPrintCount[0] < nJobPrintCount[1] && pJobInfo[0]->SetPrintFlags(EVENTBOX_PRINT_ATDAILYTIME) && pJobInfo[0]->SetPrintDailyCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastDailyTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtDailyTime(tJobPrintDailyTime, tJobPrintTime[2]) && pJobInfo[0]->GetPrintDailyCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastDailyTime(tJobPrintTime[1]) && tJobPrintTime[3].GetTime() % SECONDSPERDAY >= tJobPrintDailyTime.GetTotalSeconds() && tJobPrintTime[3].GetTime() / SECONDSPERDAY != tJobPrintTime[1].GetTime() / SECONDSPERDAY  &&  tJobPrintTime[3] <= tJobPrintTime[2] && pJobInfo[0]->SetPrintFlags(EVENTBOX_PRINT_ATDAILYTIME) && pJobInfo[0]->SetPrintDailyCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastDailyTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtCount(nJobCount[0]) && pJobInfo[0]->GetPrintLastCount(nJobCount[1]) && nCount >= nJobCount[0] && nJobCount[0] > nJobCount[1] && pJobInfo[0]->SetPrintFlags(EVENTBOX_PRINT_ATCOUNT) && pJobInfo[0]->SetPrintLastCount(nCount))))
			{
				if ((pJobInfo[1] = new CEventBoxPrintJobInfo))
				{
					pJobInfo[1]->Copy(pJobInfo[0]);
					InsertAt(0, pJobInfo[1], 1);
					if (!pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0], tJobPrintInterval) && !pJobInfo[0]->GetPrintAtDailyTime(tJobPrintDailyTime) &&
						(!pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0]) || tJobPrintTime[3] >= tJobPrintTime[0]) &&
						(!pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0], tJobPrintInterval, nJobPrintCount[1]) || !pJobInfo[0]->GetPrintCount(nJobPrintCount[0]) || nJobPrintCount[0] >= nJobPrintCount[1]) &&
						(!pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0], tJobPrintInterval, tJobPrintTime[2]) || tJobPrintTime[0].GetTime() + ((tJobPrintTime[3].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds() + 1)*tJobPrintInterval.GetTotalSeconds() > tJobPrintTime[2].GetTime()) &&
						(!pJobInfo[0]->GetPrintAtDailyTime(tJobPrintDailyTime, nJobPrintCount[1]) || !pJobInfo[0]->GetPrintDailyCount(nJobPrintCount[0]) || nJobPrintCount[0] >= nJobPrintCount[1]) &&
						(!pJobInfo[0]->GetPrintAtDailyTime(tJobPrintDailyTime, tJobPrintTime[2]) || tJobPrintTime[0].GetTime() + ((tJobPrintTime[3].GetTime() - tJobPrintTime[0].GetTime()) / SECONDSPERDAY + 1)*SECONDSPERDAY > tJobPrintTime[2].GetTime()) &&
						(!pJobInfo[0]->GetPrintAtCount(nJobCount[0]) || nCount >= nJobCount[0]))
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

VOID CEventBoxPrintJobs::RemoveAll()
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

BOOL CEventBoxPrintJobs::Copy(CONST CEventBoxPrintJobs *pPrintJobs)
{
	INT  nJob;
	INT  nJobs;
	CEventBoxPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (INT)pPrintJobs->GetSize(), RemoveAll(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = new CEventBoxPrintJobInfo) != (CEventBoxPrintJobInfo *)NULL)
		{
			pJobInfo->Copy(pPrintJobs->GetAt(nJob));
			InsertAt(nJob, pJobInfo, 1);
			continue;
		}
		break;
	}
	return((nJob == nJobs) ? TRUE : FALSE);
}

BOOL CEventBoxPrintJobs::Compare(CONST CEventBoxPrintJobs *pPrintJobs) CONST
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

BOOL CEventBoxPrintJobs::Map(CByteArray &nInfo) CONST
{
	INT  nJob;
	INT  nJobs;
	CByteArray  nJobData;
	CEventBoxPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (INT)GetSize(), nInfo.RemoveAll(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = GetAt(nJob)) && pJobInfo->Map(nJobData) && nInfo.Append(nJobData) >= 0) continue;
		break;
	}
	return((nJob == nJobs) ? TRUE : FALSE);
}

BOOL CEventBoxPrintJobs::Unmap(CONST CByteArray &nInfo)
{
	INT  cbJob;
	INT  cbJobs;
	CByteArray  nJobData;
	CEventBoxPrintJobInfo  *pJobInfo;

	for (cbJobs = 0, RemoveAll(); cbJobs < nInfo.GetSize(); cbJobs += cbJob)
	{
		for (CopyMemory(&cbJob, nInfo.GetData() + cbJobs, sizeof(cbJob)), nJobData.SetSize(max(min(cbJob, nInfo.GetSize() - cbJobs), 0)); nJobData.GetSize() >= 0; )
		{
			CopyMemory(nJobData.GetData(), nInfo.GetData() + cbJobs, nJobData.GetSize());
			break;
		}
		if ((pJobInfo = new CEventBoxPrintJobInfo))
		{
			if (pJobInfo->Unmap(nJobData) && Add(pJobInfo) >= 0) continue;
			delete pJobInfo;
		}
		break;
	}
	if ((pJobInfo = (!GetSize()) ? new CEventBoxPrintJobInfo : (CEventBoxPrintJobInfo *)NULL))
	{
		for (pJobInfo->SetName(STRING(IDS_PRINTJOB_DEFAULTNAME)), pJobInfo->SetProfile(STRING(IDS_PRINTPROFILE_DEFAULTNAME)), pJobInfo->SetPrintMode(EVENTBOX_PRINT_ALL); Add(pJobInfo) >= 0; ) return TRUE;
		delete pJobInfo;
		return FALSE;
	}
	return((cbJobs == nInfo.GetSize()) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CEventBoxSettingsLayoutPage property page

IMPLEMENT_DYNCREATE(CEventBoxSettingsLayoutPage, CLocalePropertyPage)

CEventBoxSettingsLayoutPage::CEventBoxSettingsLayoutPage() : CLocalePropertyPage(CEventBoxSettingsLayoutPage::IDD)
{
	//{{AFX_DATA_INIT(CEventBoxSettingsLayoutPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CEventBoxSettingsLayoutPage::Initialize()
{
	CEventBoxOpenDialog  *pDialog;

	if (((pDialog = GetParentDialog()->GetParentDialog()) && (pDialog->GetLayoutTitle(m_nColumns[0]) || GetParentDisplay()->GetTitle(m_nColumns[0])) && (pDialog->GetLayoutTitleFont(&m_fntTitle[0]) || GetParentDisplay()->GetTitleFont(&m_fntTitle[0])) && (pDialog->GetLayoutListFont(&m_fntItems[0]) || GetParentDisplay()->GetItemsFont(&m_fntItems[0]))) || (GetParentDisplay()->GetTitle(m_nColumns[0]) && GetParentDisplay()->GetTitleFont(&m_fntTitle[0]) && GetParentDisplay()->GetItemsFont(&m_fntItems[0])))
	{
		CopyMemory(&m_fntTitle[1], &m_fntTitle[0], sizeof(LOGFONT));
		CopyMemory(&m_fntItems[1], &m_fntItems[0], sizeof(LOGFONT));
		m_nColumns[1] = m_nColumns[0];
		m_bDefault = FALSE;
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxSettingsLayoutPage::GetTitle(UINT &nColumns) CONST
{
	nColumns = m_nColumns[0];
	return Check(FALSE);
}

BOOL CEventBoxSettingsLayoutPage::GetTitleFont(LPLOGFONT pTitleFont) CONST
{
	CopyMemory(pTitleFont, &m_fntTitle[0], sizeof(LOGFONT));
	return Check(FALSE);
}

BOOL CEventBoxSettingsLayoutPage::GetListFont(LPLOGFONT pListFont) CONST
{
	CopyMemory(pListFont, &m_fntItems[0], sizeof(LOGFONT));
	return Check(FALSE);
}

BOOL CEventBoxSettingsLayoutPage::UseAsDefault(BOOL &bDefault) CONST
{
	bDefault = m_bDefault;
	return Check(FALSE);
}

CEventBoxSettingsDialog *CEventBoxSettingsLayoutPage::GetParentDialog() CONST
{
	return((CEventBoxSettingsDialog *)CLocalePropertyPage::GetParent());
}

CEventBoxWnd *CEventBoxSettingsLayoutPage::GetParentDisplay() CONST
{
	return((CEventBoxWnd *)GetParentDialog()->GetParentDisplay());
}

VOID CEventBoxSettingsLayoutPage::ShowLayoutFontDetails()
{
	INT  nSize;
	INT  nSizes;
	INT  nStyle;
	INT  nStyles;
	BOOL  bUnderlined;
	CStringArray  szSizes;
	CStringArray  szStyles;
	CFontTools  cFontTools;

	for (SendDlgItemMessage(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_RESETCONTENT), SendDlgItemMessage(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_RESETCONTENT), SendDlgItemMessage(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)((IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE)) ? m_fntTitle[0].lfFaceName : m_fntItems[0].lfFaceName))); (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE) && cFontTools.EnumerateFont(m_fntTitle[0].lfFaceName, szStyles, szSizes, bUnderlined)) || (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS) && cFontTools.EnumerateFont(m_fntItems[0].lfFaceName, szStyles, szSizes, bUnderlined)); )
	{
		for (nStyle = 0, nStyles = (INT)szStyles.GetSize(); nStyle < nStyles; nStyle++) SendDlgItemMessage(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szStyles.GetAt(nStyle));
		for (nSize = 0, nSizes = (INT)szSizes.GetSize(); nSize < nSizes; nSize++) SendDlgItemMessage(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szSizes.GetAt(nSize));
		break;
	}
	if (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		SendDlgItemMessage(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_fntTitle[0])), 0));
		SendDlgItemMessage(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntTitle[0])), max(SendDlgItemMessage(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntTitle[1])), 0)));
	}
	if (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS))
	{
		SendDlgItemMessage(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_fntItems[0])), 0));
		SendDlgItemMessage(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntItems[0])), max(SendDlgItemMessage(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntItems[1])), 0)));
	}
	GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_STYLE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_STYLE)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_SIZE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_SIZE)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_SAMPLE)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CEventBoxSettingsLayoutPage::ShowLayoutFontSample()
{
	CRect  rSampleText;

	GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->GetWindowRect(rSampleText);
	ScreenToClient(rSampleText);
	InvalidateRect(rSampleText);
	UpdateWindow();
}

BOOL CEventBoxSettingsLayoutPage::CheckPrivilege(UINT nPrivilege) CONST
{
	return((GetParentDisplay()->GetScope() == DISPLAY_SCOPE_GLOBAL) ? CheckAccountPrivilege(nPrivilege) : TRUE);
}

VOID CEventBoxSettingsLayoutPage::AdjustToPrivileges()
{
	BOOL  bCheck;

	AccessControl(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_TIMEITEM, (bCheck = CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE)));
	AccessControl(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_CATEGORYITEM, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_TYPEITEM, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_MESSAGEITEM, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_COMMENTSITEM, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_RECIPIENTSITEM, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_USERITEM, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_NAMES, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_STYLE, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_SIZE, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_DEFAULT, bCheck);
}

BOOL CEventBoxSettingsLayoutPage::IsModified(BOOL bAll) CONST
{
	CFontTools  cFontTools;

	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (m_nColumns[0] != m_nColumns[1] || lstrcmp(m_fntTitle[0].lfFaceName, m_fntTitle[1].lfFaceName) || (m_fntTitle[0].lfHeight != m_fntTitle[1].lfHeight  &&  cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntTitle[0])) != cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntTitle[1]))) || m_fntTitle[0].lfWeight != m_fntTitle[1].lfWeight || m_fntTitle[0].lfItalic != m_fntTitle[1].lfItalic || lstrcmp(m_fntItems[0].lfFaceName, m_fntItems[1].lfFaceName) || (m_fntItems[0].lfHeight != m_fntItems[1].lfHeight  &&  cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntItems[0])) != cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntItems[1]))) || m_fntItems[0].lfWeight != m_fntItems[1].lfWeight || m_fntItems[0].lfItalic != m_fntItems[1].lfItalic || m_bDefault) : CLocalePropertyPage::IsModified()) : FALSE);
}

BOOL CEventBoxSettingsLayoutPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_NAMES)->GetWindowTextLength() > 0 && GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowTextLength() > 0 && GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowTextLength() > 0 && m_nColumns[0] != 0) : CLocalePropertyPage::Check()) : TRUE);
}

void CEventBoxSettingsLayoutPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEventBoxSettingsLayoutPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEventBoxSettingsLayoutPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CEventBoxSettingsLayoutPage)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_TIMEITEM, OnTitleItems)
	ON_BN_CLICKED(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_CATEGORYITEM, OnTitleItems)
	ON_BN_CLICKED(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_TYPEITEM, OnTitleItems)
	ON_BN_CLICKED(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_MESSAGEITEM, OnTitleItems)
	ON_BN_CLICKED(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_COMMENTSITEM, OnTitleItems)
	ON_BN_CLICKED(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_RECIPIENTSITEM, OnTitleItems)
	ON_BN_CLICKED(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_USERITEM, OnTitleItems)
	ON_BN_CLICKED(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE, OnTitleFont)
	ON_BN_CLICKED(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS, OnItemsFont)
	ON_BN_CLICKED(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_DEFAULT, OnUseAsDefault)
	ON_CBN_EDITCHANGE(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_NAMES, OnEditchangeFontName)
	ON_CBN_SELCHANGE(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_NAMES, OnSelchangeFontName)
	ON_CBN_SELCHANGE(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_STYLE, OnSelchangeFontStyle)
	ON_CBN_SELCHANGE(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_SIZE, OnSelchangeFontSize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventBoxSettingsLayoutPage message handlers

BOOL CEventBoxSettingsLayoutPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	CheckRadioButton(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE, IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS, IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE);
	CheckDlgButton(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_TIMEITEM, (m_nColumns[0] & EVENTBOX_TITLEITEM_TIME) ? TRUE : FALSE);
	CheckDlgButton(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_CATEGORYITEM, (m_nColumns[0] & EVENTBOX_TITLEITEM_CATEGORY) ? TRUE : FALSE);
	CheckDlgButton(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_TYPEITEM, (m_nColumns[0] & EVENTBOX_TITLEITEM_TYPE) ? TRUE : FALSE);
	CheckDlgButton(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_MESSAGEITEM, (m_nColumns[0] & EVENTBOX_TITLEITEM_MESSAGE) ? TRUE : FALSE);
	CheckDlgButton(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_COMMENTSITEM, (m_nColumns[0] & EVENTBOX_TITLEITEM_COMMENTS) ? TRUE : FALSE);
	CheckDlgButton(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_RECIPIENTSITEM, (m_nColumns[0] & EVENTBOX_TITLEITEM_RECIPIENTS) ? TRUE : FALSE);
	CheckDlgButton(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_USERITEM, (m_nColumns[0] & EVENTBOX_TITLEITEM_USER) ? TRUE : FALSE);
	CheckDlgButton(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_DEFAULT, m_bDefault);
	GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->GetWindowText(m_szFontSampleText);
	GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT)->EnableWindow();
	GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_TIMEITEM)->EnableWindow();
	GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_CATEGORYITEM)->EnableWindow();
	GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_TYPEITEM)->EnableWindow();
	GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_MESSAGEITEM)->EnableWindow();
	GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_COMMENTSITEM)->EnableWindow();
	GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_RECIPIENTSITEM)->EnableWindow();
	GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_USERITEM)->EnableWindow();
	GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS)->EnableWindow();
	GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_STATIC)->EnableWindow();
	GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE)->EnableWindow();
	GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS)->EnableWindow();
	GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_CHARACTERISTICS)->EnableWindow();
	GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_NAMES_STATIC)->EnableWindow();
	GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_NAMES)->EnableWindow();
	GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_DEFAULT)->EnableWindow();
	SendDlgItemMessage(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_NAMES, FCB_DIR, CF_EFFECTS | CF_SCREENFONTS);
	SendDlgItemMessage(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)m_fntTitle[0].lfFaceName));
	ShowLayoutFontDetails();
	AdjustToPrivileges();
	return TRUE;
}

void CEventBoxSettingsLayoutPage::OnPaint()
{
	INT  nBkMode;
	CFont  cFont;
	CFont  *pOldFont;
	CRect  rSampleText;
	COLORREF  nOldColor;
	CPaintDC  cDC(this);

	for (GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->GetWindowRect(rSampleText), ScreenToClient(rSampleText); cFont.CreateFontIndirect((IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE)) ? &m_fntTitle[0] : &m_fntItems[0]); )
	{
		if ((pOldFont = cDC.SelectObject(&cFont)))
		{
			nBkMode = cDC.SetBkMode(TRANSPARENT);
			nOldColor = cDC.SetTextColor((SendDlgItemMessage(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? GetSysColor(COLOR_WINDOWTEXT) : GetSysColor(COLOR_GRAYTEXT));
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

void CEventBoxSettingsLayoutPage::OnTitleItems()
{
	m_nColumns[0] = 0;
	m_nColumns[0] |= (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_TIMEITEM)) ? EVENTBOX_TITLEITEM_TIME : 0;
	m_nColumns[0] |= (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_CATEGORYITEM)) ? EVENTBOX_TITLEITEM_CATEGORY : 0;
	m_nColumns[0] |= (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_TYPEITEM)) ? EVENTBOX_TITLEITEM_TYPE : 0;
	m_nColumns[0] |= (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_MESSAGEITEM)) ? EVENTBOX_TITLEITEM_MESSAGE : 0;
	m_nColumns[0] |= (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_COMMENTSITEM)) ? EVENTBOX_TITLEITEM_COMMENTS : 0;
	m_nColumns[0] |= (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_RECIPIENTSITEM)) ? EVENTBOX_TITLEITEM_RECIPIENTS : 0;
	m_nColumns[0] |= (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FORMAT_USERITEM)) ? EVENTBOX_TITLEITEM_USER : 0;
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsLayoutPage::OnTitleFont()
{
	ShowLayoutFontDetails();
	ShowLayoutFontSample();
}

void CEventBoxSettingsLayoutPage::OnItemsFont()
{
	ShowLayoutFontDetails();
	ShowLayoutFontSample();
}

void CEventBoxSettingsLayoutPage::OnUseAsDefault()
{
	m_bDefault = IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_DEFAULT);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsLayoutPage::OnEditchangeFontName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsLayoutPage::OnSelchangeFontName()
{
	CString  szSize;
	CString  szStyle;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		_tcscpy_s(m_fntTitle[0].lfFaceName, sizeof(m_fntTitle[0].lfFaceName) / sizeof(TCHAR), Combobox_GetText(GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_NAMES), (INT)SendDlgItemMessage(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_GETCURSEL)));
		ShowLayoutFontDetails();
	}
	if (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS))
	{
		_tcscpy_s(m_fntItems[0].lfFaceName, sizeof(m_fntItems[0].lfFaceName) / sizeof(TCHAR), Combobox_GetText(GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_NAMES), (INT)SendDlgItemMessage(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_GETCURSEL)));
		ShowLayoutFontDetails();
	}
	if (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntTitle[0].lfWeight, m_fntTitle[0].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_fntTitle[0].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_fntTitle[0]);
	}
	if (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS))
	{
		GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntItems[0].lfWeight, m_fntItems[0].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_fntItems[0].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_fntItems[0]);
	}
	ShowLayoutFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsLayoutPage::OnSelchangeFontStyle()
{
	CString  szStyle;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntTitle[0].lfWeight, m_fntTitle[0].lfItalic);
	}
	if (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS))
	{
		GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntItems[0].lfWeight, m_fntItems[0].lfItalic);
	}
	ShowLayoutFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsLayoutPage::OnSelchangeFontSize()
{
	CString  szSize;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_fntTitle[0].lfHeight);
	}
	if (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS))
	{
		GetDlgItem(IDC_EVENTBOXSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_fntItems[0].lfHeight);
	}
	ShowLayoutFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CEventBoxFilterDialog dialog

IMPLEMENT_DYNCREATE(CEventBoxFilterDialog, CDisplayDialog)

CEventBoxFilterDialog::CEventBoxFilterDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CEventBoxFilterDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CEventBoxFilterDialog::Create(CWnd *pParentWnd)
{
	return CDisplayDialog::Create(pParentWnd, CEventBoxFilterDialog::IDD);
}

BOOL CEventBoxFilterDialog::Initialize()
{
	GetParentDialog()->GetBehavior(m_szTypes[0], m_szSubtypes[0]);
	m_szSubtypes[1].Copy(m_szSubtypes[0]);
	m_szTypes[1].Copy(m_szTypes[0]);
	return TRUE;
}

VOID CEventBoxFilterDialog::SetFilterInfo(CONST CStringArray &szTypes, CONST CStringArray &szSubtypes)
{
	m_szTypes[0].Copy(szTypes);
	m_szTypes[1].Copy(szTypes);
	m_szSubtypes[0].Copy(szSubtypes);
	m_szSubtypes[1].Copy(szSubtypes);
}

VOID CEventBoxFilterDialog::GetFilterInfo(CStringArray &szTypes, CStringArray &szSubtypes) CONST
{
	szTypes.Copy(m_szTypes[0]);
	szSubtypes.Copy(m_szSubtypes[0]);
}

CEventBoxSettingsFilteringPage *CEventBoxFilterDialog::GetParentDialog() CONST
{
	return((CEventBoxSettingsFilteringPage *)CDisplayDialog::GetParent());
}

CEventBoxWnd *CEventBoxFilterDialog::GetParentDisplay() CONST
{
	return((CEventBoxWnd *)CDisplayDialog::GetParentDisplay());
}

BOOL CEventBoxFilterDialog::EnumTypes()
{
	INT  nType;
	INT  nTypes;

	for (nType = 0, nTypes = (INT)m_szTypes[0].GetSize(); nType < nTypes; nType++)
	{
		SendDlgItemMessage(IDC_EVENTBOX_FILTER_TYPES, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)m_szTypes[0].GetAt(nType));
		continue;
	}
	return((SendDlgItemMessage(IDC_EVENTBOX_FILTER_TYPES, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CEventBoxFilterDialog::EnumSubtypes()
{
	INT  nSubtype;
	INT  nSubtypes;

	for (nSubtype = 0, nSubtypes = (INT)m_szSubtypes[0].GetSize(); nSubtype < nSubtypes; nSubtype++)
	{
		SendDlgItemMessage(IDC_EVENTBOX_FILTER_SUBTYPES, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)m_szSubtypes[0].GetAt(nSubtype));
		continue;
	}
	return((SendDlgItemMessage(IDC_EVENTBOX_FILTER_SUBTYPES, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CEventBoxFilterDialog::CheckPrivilege(UINT nPrivilege) CONST
{
	return((GetParentDisplay()->GetScope() == DISPLAY_SCOPE_GLOBAL) ? CheckAccountPrivilege(nPrivilege) : TRUE);
}

VOID CEventBoxFilterDialog::AdjustToPrivileges()
{
	BOOL  bCheck;

	AccessControl(IDC_EVENTBOX_FILTER_TYPES, (bCheck = CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE)));
	AccessControl(IDC_EVENTBOX_FILTER_SUBTYPES, bCheck);
}

BOOL CEventBoxFilterDialog::IsModified() CONST
{
	INT  nType[2];
	INT  nTypes[2];
	INT  nSubtype[2];
	INT  nSubtypes[2];

	for (nType[0] = 0, nTypes[0] = (m_szTypes[0].GetSize() == m_szTypes[1].GetSize()) ? (INT)m_szTypes[0].GetSize() : -1; nType[0] < nTypes[0]; nType[0]++)
	{
		for (nType[1] = 0, nTypes[1] = (INT)m_szTypes[1].GetSize(); nType[1] < nTypes[1]; nType[1]++)
		{
			if (m_szTypes[0].GetAt(nType[0]) == m_szTypes[1].GetAt(nType[1])) break;
			continue;
		}
		if (nType[1] == nTypes[1]) break;
	}
	for (nSubtype[0] = 0, nSubtypes[0] = (m_szSubtypes[0].GetSize() == m_szSubtypes[1].GetSize()) ? (INT)m_szSubtypes[0].GetSize() : -1; nSubtype[0] < nSubtypes[0]; nSubtype[0]++)
	{
		for (nSubtype[1] = 0, nSubtypes[1] = (INT)m_szSubtypes[1].GetSize(); nSubtype[1] < nSubtypes[1]; nSubtype[1]++)
		{
			if (m_szSubtypes[0].GetAt(nSubtype[0]) == m_szSubtypes[1].GetAt(nSubtype[1])) break;
			continue;
		}
		if (nSubtype[1] == nSubtypes[1]) break;
	}
	return((nTypes[0] < 0 || nType[0] < nTypes[0] || nSubtypes[0] < 0 || nSubtype[0] < nSubtypes[0]) ? TRUE : FALSE);
}

BOOL CEventBoxFilterDialog::Check(BOOL bModified) CONST
{
	return((m_szTypes[0].GetSize() >= 0) ? (!bModified || IsModified()) : FALSE);
}

void CEventBoxFilterDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEventBoxFilterDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEventBoxFilterDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CEventBoxFilterDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_EVENTBOX_FILTER_TYPE_ADD, OnAddType)
	ON_BN_CLICKED(IDC_EVENTBOX_FILTER_TYPE_REMOVE, OnRemoveType)
	ON_BN_CLICKED(IDC_EVENTBOX_FILTER_TYPE_REMOVEALL, OnRemoveAllTypes)
	ON_BN_CLICKED(IDC_EVENTBOX_FILTER_SUBTYPE_ADD, OnAddSubtype)
	ON_BN_CLICKED(IDC_EVENTBOX_FILTER_SUBTYPE_REMOVE, OnRemoveSubtype)
	ON_BN_CLICKED(IDC_EVENTBOX_FILTER_SUBTYPE_REMOVEALL, OnRemoveAllSubtypes)
	ON_BN_CLICKED(IDC_EVENTBOX_FILTER_HELP, OnHelp)
	ON_CBN_EDITCHANGE(IDC_EVENTBOX_FILTER_TYPES, OnEditchangeType)
	ON_CBN_EDITCHANGE(IDC_EVENTBOX_FILTER_SUBTYPES, OnEditchangeSubtype)
	ON_CBN_SELCHANGE(IDC_EVENTBOX_FILTER_TYPES, OnSelchangeType)
	ON_CBN_SELCHANGE(IDC_EVENTBOX_FILTER_SUBTYPES, OnSelchangeSubtype)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventBoxFilterDialog message handlers

BOOL CEventBoxFilterDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	GetDlgItem(IDC_EVENTBOX_FILTER_DETAILS)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_FILTER_TYPES_STATIC)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_FILTER_TYPES)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_FILTER_TYPE_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOX_FILTER_TYPE_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOX_FILTER_TYPE_REMOVEALL)->EnableWindow((EnumTypes()) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
	GetDlgItem(IDC_EVENTBOX_FILTER_SUBTYPES_STATIC)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_FILTER_SUBTYPES)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_FILTER_SUBTYPE_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOX_FILTER_SUBTYPE_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOX_FILTER_SUBTYPE_REMOVEALL)->EnableWindow((EnumSubtypes()) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
	AdjustToPrivileges();
	return TRUE;
}

void CEventBoxFilterDialog::OnAddType()
{
	INT  nIndex;
	CString  szType;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_EVENTBOX_FILTER_TYPES)->GetWindowText(szType); (nIndex = (INT)SendDlgItemMessage(IDC_EVENTBOX_FILTER_TYPES, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szType)) >= 0; )
	{
		SendDlgItemMessage(IDC_EVENTBOX_FILTER_TYPES, CB_SETCURSEL, nIndex);
		m_szTypes[0].InsertAt(nIndex, szType);
		break;
	}
	GetDlgItem(IDC_EVENTBOX_FILTER_TYPE_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOX_FILTER_TYPE_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_FILTER_TYPES, CB_GETCURSEL) >= 0) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
	GetDlgItem(IDC_EVENTBOX_FILTER_TYPE_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_FILTER_TYPES, CB_GETCOUNT) > 0) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
	GetDlgItem(IDC_EVENTBOX_FILTER_TYPES)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxFilterDialog::OnRemoveType()
{
	INT  nIndex;
	CHourglassCursor  cCursor;

	if ((nIndex = (INT)SendDlgItemMessage(IDC_EVENTBOX_FILTER_TYPES, CB_GETCURSEL)) >= 0)
	{
		for (SendDlgItemMessage(IDC_EVENTBOX_FILTER_TYPES, CB_DELETESTRING, nIndex); nIndex < m_szTypes[0].GetSize(); )
		{
			m_szTypes[0].RemoveAt(nIndex);
			break;
		}
		SendDlgItemMessage(IDC_EVENTBOX_FILTER_TYPES, CB_SETCURSEL);
	}
	GetDlgItem(IDC_EVENTBOX_FILTER_TYPE_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOX_FILTER_TYPE_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_FILTER_TYPES, CB_GETCURSEL) >= 0) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
	GetDlgItem(IDC_EVENTBOX_FILTER_TYPE_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_FILTER_TYPES, CB_GETCOUNT) > 0) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
	GetDlgItem(IDC_EVENTBOX_FILTER_TYPES)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxFilterDialog::OnRemoveAllTypes()
{
	CHourglassCursor  cCursor;

	m_szTypes[0].RemoveAll();
	SendDlgItemMessage(IDC_EVENTBOX_FILTER_TYPES, CB_RESETCONTENT);
	GetDlgItem(IDC_EVENTBOX_FILTER_TYPE_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOX_FILTER_TYPE_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOX_FILTER_TYPE_REMOVEALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOX_FILTER_TYPES)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxFilterDialog::OnAddSubtype()
{
	INT  nIndex;
	CString  szSubtype;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_EVENTBOX_FILTER_SUBTYPES)->GetWindowText(szSubtype); (nIndex = (INT)SendDlgItemMessage(IDC_EVENTBOX_FILTER_SUBTYPES, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szSubtype)) >= 0; )
	{
		SendDlgItemMessage(IDC_EVENTBOX_FILTER_SUBTYPES, CB_SETCURSEL, nIndex);
		m_szSubtypes[0].InsertAt(nIndex, szSubtype);
		break;
	}
	GetDlgItem(IDC_EVENTBOX_FILTER_SUBTYPE_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOX_FILTER_SUBTYPE_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_FILTER_SUBTYPES, CB_GETCURSEL) >= 0) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
	GetDlgItem(IDC_EVENTBOX_FILTER_SUBTYPE_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_FILTER_SUBTYPES, CB_GETCOUNT) > 0) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
	GetDlgItem(IDC_EVENTBOX_FILTER_SUBTYPES)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxFilterDialog::OnRemoveSubtype()
{
	INT  nIndex;
	CHourglassCursor  cCursor;

	if ((nIndex = (INT)SendDlgItemMessage(IDC_EVENTBOX_FILTER_SUBTYPES, CB_GETCURSEL)) >= 0)
	{
		for (SendDlgItemMessage(IDC_EVENTBOX_FILTER_SUBTYPES, CB_DELETESTRING, nIndex); nIndex < m_szSubtypes[0].GetSize(); )
		{
			m_szSubtypes[0].RemoveAt(nIndex);
			break;
		}
		SendDlgItemMessage(IDC_EVENTBOX_FILTER_SUBTYPES, CB_SETCURSEL);
	}
	GetDlgItem(IDC_EVENTBOX_FILTER_SUBTYPE_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOX_FILTER_SUBTYPE_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_FILTER_SUBTYPES, CB_GETCURSEL) >= 0) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
	GetDlgItem(IDC_EVENTBOX_FILTER_SUBTYPE_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_FILTER_SUBTYPES, CB_GETCOUNT) > 0) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
	GetDlgItem(IDC_EVENTBOX_FILTER_SUBTYPES)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxFilterDialog::OnRemoveAllSubtypes()
{
	CHourglassCursor  cCursor;

	m_szSubtypes[0].RemoveAll();
	SendDlgItemMessage(IDC_EVENTBOX_FILTER_SUBTYPES, CB_RESETCONTENT);
	GetDlgItem(IDC_EVENTBOX_FILTER_SUBTYPE_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOX_FILTER_SUBTYPE_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOX_FILTER_SUBTYPE_REMOVEALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOX_FILTER_SUBTYPES)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxFilterDialog::OnSelchangeType()
{
	GetDlgItem(IDC_EVENTBOX_FILTER_TYPE_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_FILTER_TYPES, CB_GETCURSEL) >= 0) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
}

void CEventBoxFilterDialog::OnSelchangeSubtype()
{
	GetDlgItem(IDC_EVENTBOX_FILTER_SUBTYPE_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_FILTER_SUBTYPES, CB_GETCURSEL) >= 0) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
}

void CEventBoxFilterDialog::OnEditchangeType()
{
	CString  szType;

	GetDlgItem(IDC_EVENTBOX_FILTER_TYPES)->GetWindowText(szType);
	GetDlgItem(IDC_EVENTBOX_FILTER_TYPE_ADD)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_FILTER_TYPES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szType) == CB_ERR) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
}

void CEventBoxFilterDialog::OnEditchangeSubtype()
{
	CString  szSubtype;

	GetDlgItem(IDC_EVENTBOX_FILTER_SUBTYPES)->GetWindowText(szSubtype);
	GetDlgItem(IDC_EVENTBOX_FILTER_SUBTYPE_ADD)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_FILTER_SUBTYPES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szSubtype) == CB_ERR) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
}

void CEventBoxFilterDialog::OnOK()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnOK();
}

BOOL CEventBoxFilterDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_EVENTBOXFILTERDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CEventBoxFilterDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_EVENTBOXFILTERDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CEventBoxSettingsFilteringPage property page

IMPLEMENT_DYNCREATE(CEventBoxSettingsFilteringPage, CLocalePropertyPage)

CEventBoxSettingsFilteringPage::CEventBoxSettingsFilteringPage() : CLocalePropertyPage(CEventBoxSettingsFilteringPage::IDD)
{
	//{{AFX_DATA_INIT(CEventBoxSettingsFilteringPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CEventBoxSettingsFilteringPage::Initialize()
{
	CEventBoxOpenDialog  *pDialog;

	if (((pDialog = GetParentDialog()->GetParentDialog()) && (pDialog->GetFilterMode(m_nMode[0]) || GetParentDisplay()->GetFilterMode(m_nMode[0])) && ((m_nMode[0] & EVENTBOX_FILTER_AUTOEVENTS) != EVENTBOX_FILTER_AUTOEVENTS || pDialog->GetFilterBehavior(m_nCount[0]) || GetParentDisplay()->GetFilterBehavior(m_nCount[0])) && (pDialog->GetFilterBehavior(m_szTypes[0], m_szSubtypes[0]) || GetParentDisplay()->GetFilterBehavior(m_szTypes[0], m_szSubtypes[0])) && ((m_nMode[0] & EVENTBOX_FILTER_LIMITBYEVENTS) != EVENTBOX_FILTER_LIMITBYEVENTS || pDialog->GetFilterLimitation(m_nLimit[0]) || GetParentDisplay()->GetFilterLimitation(m_nLimit[0])) && ((m_nMode[0] & EVENTBOX_FILTER_LIMITBYTIME) != EVENTBOX_FILTER_LIMITBYTIME || pDialog->GetFilterLimitation(m_tStartTime[0], m_tStopTime[0]) || GetParentDisplay()->GetFilterLimitation(m_tStartTime[0], m_tStopTime[0])) && (pDialog->GetFilterColors(m_nColors[0]) || GetParentDisplay()->GetFilterColors(m_nColors[0]))) || (GetParentDisplay()->GetFilterMode(m_nMode[0]) && ((m_nMode[0] & EVENTBOX_FILTER_AUTOEVENTS) != EVENTBOX_FILTER_AUTOEVENTS || GetParentDisplay()->GetFilterBehavior(m_nCount[0])) && GetParentDisplay()->GetFilterBehavior(m_szTypes[0], m_szSubtypes[0]) && ((m_nMode[0] & EVENTBOX_FILTER_LIMITBYEVENTS) != EVENTBOX_FILTER_LIMITBYEVENTS || GetParentDisplay()->GetFilterLimitation(m_nLimit[0])) && GetParentDisplay()->GetFilterColors(m_nColors[0])))
	{
		m_szTypes[1].Copy(m_szTypes[0]);
		m_szSubtypes[1].Copy(m_szSubtypes[0]);
		m_tStartTime[1] = m_tStartTime[0];
		m_tStopTime[1] = m_tStopTime[0];
		m_nColors[1].Copy(m_nColors[0]);
		m_nCount[1] = m_nCount[0];
		m_nLimit[1] = m_nLimit[0];
		m_nMode[1] = m_nMode[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxSettingsFilteringPage::GetMode(UINT &nMode) CONST
{
	nMode = m_nMode[0];
	return Check(FALSE);
}

BOOL CEventBoxSettingsFilteringPage::GetBehavior(UINT &nCount) CONST
{
	if (m_nMode[0] & EVENTBOX_FILTER_AUTOEVENTS)
	{
		nCount = m_nCount[0];
		return Check(FALSE);
	}
	return FALSE;
}
BOOL CEventBoxSettingsFilteringPage::GetBehavior(CStringArray &szTypes, CStringArray &szSubtypes) CONST
{
	szTypes.Copy(m_szTypes[0]);
	szSubtypes.Copy(m_szSubtypes[0]);
	return Check(FALSE);
}

BOOL CEventBoxSettingsFilteringPage::GetLimitation(UINT &nLimit) CONST
{
	if (m_nMode[0] & EVENTBOX_FILTER_LIMITBYEVENTS)
	{
		nLimit = m_nLimit[0];
		return Check(FALSE);
	}
	return FALSE;
}
BOOL CEventBoxSettingsFilteringPage::GetLimitation(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	if (m_nMode[0] & EVENTBOX_FILTER_LIMITBYTIME)
	{
		tStartTime = m_tStartTime[0];
		tStopTime = m_tStopTime[0];
		return Check(FALSE);
	}
	return FALSE;
}

BOOL CEventBoxSettingsFilteringPage::GetColors(CUIntArray &nColors) CONST
{
	nColors.Copy(m_nColors[0]);
	return Check(FALSE);
}

CEventBoxSettingsDialog *CEventBoxSettingsFilteringPage::GetParentDialog() CONST
{
	return((CEventBoxSettingsDialog *)CLocalePropertyPage::GetParent());
}

CEventBoxWnd *CEventBoxSettingsFilteringPage::GetParentDisplay() CONST
{
	return((CEventBoxWnd *)GetParentDialog()->GetParentDisplay());
}

BOOL CEventBoxSettingsFilteringPage::CheckPrivilege(UINT nPrivilege) CONST
{
	return((GetParentDisplay()->GetScope() == DISPLAY_SCOPE_GLOBAL) ? CheckAccountPrivilege(nPrivilege) : TRUE);
}

VOID CEventBoxSettingsFilteringPage::AdjustToPrivileges()
{
	BOOL  bCheck;

	AccessControl(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_CATEGORY_SYSTEM, (bCheck = CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE)));
	AccessControl(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_CATEGORY_SPACECRAFT, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_CATEGORY_USER, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_TIME, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_STARTTIME, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_STOPTIME, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_EVENTS, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_EVENTS_COUNT, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOEVENTS, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOEVENTS_COUNT, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_BRINGEVENTS, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_LISTEVENTS, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOACKNOWLEDGE, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_NOTIFY, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_USESOUND, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS_CATEGORY, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS_TYPE, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS_LIST, bCheck);
}

BOOL CEventBoxSettingsFilteringPage::IsModified(BOOL bAll) CONST
{
	INT  nColor;
	INT  nColors;
	INT  nType[2];
	INT  nTypes[2];
	INT  nSubtype[2];
	INT  nSubtypes[2];

	if (IsWindow(GetSafeHwnd()) && !bAll)
	{
		for (nColor = 0, nColors = (m_nMode[0] == m_nMode[1] && m_nLimit[0] == m_nLimit[1] && m_nCount[0] == m_nCount[1] && m_tStartTime[0] == m_tStartTime[1] && m_tStopTime[0] == m_tStopTime[1] && m_nColors[0].GetSize() == m_nColors[1].GetSize()) ? (INT)m_nColors[0].GetSize() : -1; nColor < nColors; nColor++)
		{
			if (m_nColors[0].GetAt(nColor) != m_nColors[1].GetAt(nColor)) break;
			continue;
		}
		for (nType[0] = 0, nTypes[0] = (m_szTypes[0].GetSize() == m_szTypes[1].GetSize()) ? (INT)m_szTypes[0].GetSize() : -1; nType[0] < nTypes[0]; nType[0]++)
		{
			for (nType[1] = 0, nTypes[1] = (INT)m_szTypes[1].GetSize(); nType[1] < nTypes[1]; nType[1]++)
			{
				if (m_szTypes[0].GetAt(nType[0]) == m_szTypes[1].GetAt(nType[1])) break;
				continue;
			}
			if (nType[1] == nTypes[1]) break;
		}
		for (nSubtype[0] = 0, nSubtypes[0] = (m_szSubtypes[0].GetSize() == m_szSubtypes[1].GetSize()) ? (INT)m_szSubtypes[0].GetSize() : -1; nSubtype[0] < nSubtypes[0]; nSubtype[0]++)
		{
			for (nSubtype[1] = 0, nSubtypes[1] = (INT)m_szSubtypes[1].GetSize(); nSubtype[1] < nSubtypes[1]; nSubtype[1]++)
			{
				if (m_szSubtypes[0].GetAt(nSubtype[0]) == m_szSubtypes[1].GetAt(nSubtype[1])) break;
				continue;
			}
			if (nSubtype[1] == nSubtypes[1]) break;
		}
		return((nColors < 0 || nColor < nColors || nTypes[0] < 0 || nType[0] < nTypes[0] || nSubtypes[0] < 0 || nSubtype[0] < nSubtypes[0]) ? TRUE : FALSE);
	}
	return((bAll) ? CLocalePropertyPage::IsModified() : FALSE);
}

BOOL CEventBoxSettingsFilteringPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (m_nMode[0] && (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_CATEGORY_SYSTEM) || IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_CATEGORY_SPACECRAFT) || IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_CATEGORY_USER))) : CLocalePropertyPage::Check()) : TRUE);
}

void CEventBoxSettingsFilteringPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEventBoxSettingsFilteringPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CEventBoxSettingsFilteringPage::PostNcDestroy()
{
	m_nColors[0].RemoveAll();
	m_nColors[1].RemoveAll();
	m_szTypes[0].RemoveAll();
	m_szTypes[1].RemoveAll();
	m_szSubtypes[0].RemoveAll();
	m_szSubtypes[1].RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CEventBoxSettingsFilteringPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CEventBoxSettingsFilteringPage)
	ON_BN_CLICKED(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_CATEGORY_SYSTEM, OnFilterSystem)
	ON_BN_CLICKED(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_CATEGORY_SPACECRAFT, OnFilterSpacecraft)
	ON_BN_CLICKED(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_CATEGORY_USER, OnFilterUser)
	ON_BN_CLICKED(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_TYPES, OnFilterTypes)
	ON_BN_CLICKED(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_TIME, OnLimitByTime)
	ON_BN_CLICKED(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_EVENTS, OnLimitByEvents)
	ON_BN_CLICKED(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOEVENTS, OnBehaviorAutoEvents)
	ON_BN_CLICKED(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_BRINGEVENTS, OnBehaviorBringEvents)
	ON_BN_CLICKED(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_LISTEVENTS, OnBehaviorListEvents)
	ON_BN_CLICKED(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOACKNOWLEDGE, OnBehaviorAutoAcknowledge)
	ON_BN_CLICKED(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_NOTIFY, OnBehaviorNotify)
	ON_BN_CLICKED(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_USESOUND, OnBehaviorUseSound)
	ON_CBN_SELCHANGE(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS_CATEGORY, OnSelchangeColorsCategory)
	ON_CBN_SELCHANGE(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS_TYPE, OnSelchangeColorsType)
	ON_CBN_SELCHANGE(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS_LIST, OnSelchangeColorsList)
	ON_CONTROL(TSBXN_CHANGE, IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_STARTTIME, OnSpinchangeLimitByStartTime)
	ON_CONTROL(TSBXN_CHANGE, IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_STOPTIME, OnSpinchangeLimitByStopTime)
	ON_CONTROL(SBXN_CHANGE, IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_EVENTS_COUNT, OnSpinchangeLimitByEvents)
	ON_CONTROL(SBXN_CHANGE, IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOEVENTS_COUNT, OnSpinchangeBehaviorAutoEvents)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventBoxSettingsFilteringPage message handlers

BOOL CEventBoxSettingsFilteringPage::OnInitDialog()
{
	INT  nType;
	INT  nCategory;
	CEventBoxOpenDialog  *pDialog;
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	for (nCategory = MINLOCALEVENTCATEGORY; nCategory <= MAXLOCALEVENTCATEGORY; nCategory++)
	{
		SendDlgItemMessage(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS_CATEGORY, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(nCategory));
		continue;
	}
	for (nType = MINEVENTTYPE; nType <= MAXEVENTTYPE; nType++)
	{
		if (nType >= MINEVENTTYPE  &&  nType != IDS_EVENTTYPE_SCHEDULED)
		{
			SendDlgItemMessage(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS_TYPE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(nType));
			continue;
		}
	}
	CheckDlgButton(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_CATEGORY_SYSTEM, (m_nMode[0] & EVENTBOX_FILTER_SYSTEM) ? TRUE : FALSE);
	CheckDlgButton(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_CATEGORY_SPACECRAFT, (m_nMode[0] & EVENTBOX_FILTER_SPACECRAFT) ? TRUE : FALSE);
	CheckDlgButton(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_CATEGORY_USER, (m_nMode[0] & EVENTBOX_FILTER_USER) ? TRUE : FALSE);
	CheckDlgButton(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_TIME, (m_nMode[0] & EVENTBOX_FILTER_LIMITBYTIME) ? TRUE : FALSE);
	CheckDlgButton(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_EVENTS, (m_nMode[0] & EVENTBOX_FILTER_LIMITBYEVENTS) ? TRUE : FALSE);
	CheckDlgButton(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOEVENTS, (((GetParentDialog()->GetParentDialog() && GetParentDialog()->GetParentDialog()->GetMode() == DISPLAY_MODE_REALTIME) || (!GetParentDialog()->GetParentDialog() && GetParentDisplay()->GetMode() == DISPLAY_MODE_REALTIME)) && (m_nMode[0] & EVENTBOX_FILTER_AUTOEVENTS)) ? TRUE : FALSE);
	CheckDlgButton(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOACKNOWLEDGE, (((GetParentDialog()->GetParentDialog() && GetParentDialog()->GetParentDialog()->GetMode() == DISPLAY_MODE_REALTIME) || (!GetParentDialog()->GetParentDialog() && GetParentDisplay()->GetMode() == DISPLAY_MODE_REALTIME)) && (m_nMode[0] & EVENTBOX_FILTER_AUTOACKNOWLEDGE)) ? TRUE : FALSE);
	CheckDlgButton(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_NOTIFY, (GetParentDisplay()->GetScope() == DISPLAY_SCOPE_LOCAL && ((GetParentDialog()->GetParentDialog() && GetParentDialog()->GetParentDialog()->GetMode() == DISPLAY_MODE_REALTIME) || (!GetParentDialog()->GetParentDialog() && GetParentDisplay()->GetMode() == DISPLAY_MODE_REALTIME)) && (m_nMode[0] & EVENTBOX_FILTER_NOTIFY)) ? TRUE : FALSE);
	CheckDlgButton(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_BRINGEVENTS, (GetParentDisplay()->GetScope() == DISPLAY_SCOPE_GLOBAL && (m_nMode[0] & EVENTBOX_FILTER_BRINGEVENTS)) ? TRUE : FALSE);
	CheckDlgButton(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_USESOUND, (GetParentDisplay()->GetScope() == DISPLAY_SCOPE_GLOBAL && (m_nMode[0] & EVENTBOX_FILTER_USESOUND)) ? TRUE : FALSE);
	CheckDlgButton(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_LISTEVENTS, (m_nMode[0] & EVENTBOX_FILTER_LISTEVENTS) ? TRUE : FALSE);
	Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_STARTTIME), (m_tStartTime[0].GetTime() > 0) ? m_tStartTime[0] : CTime::GetCurrentTime().GetTime());
	Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_STOPTIME), (m_tStopTime[0].GetTime() > 0) ? m_tStopTime[0] : CTime::GetCurrentTime().GetTime());
	Spinbox_SetRange(GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_EVENTS_COUNT), EVENTBOXSETTINGSFILTERINGPAGE_LIMITATION_MINIMUMEVENTS, EVENTBOXSETTINGSFILTERINGPAGE_LIMITATION_MAXIMUMEVENTS);
	Spinbox_SetRange(GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOEVENTS_COUNT), EVENTBOXSETTINGSFILTERINGPAGE_BEHAVIOR_MINIMUMEVENTS, EVENTBOXSETTINGSFILTERINGPAGE_BEHAVIOR_MAXIMUMEVENTS);
	Spinbox_SetPos(GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_EVENTS_COUNT), m_nLimit[0]);
	Spinbox_SetPos(GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOEVENTS_COUNT), m_nCount[0]);
	SendDlgItemMessage(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS_CATEGORY, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS_CATEGORY, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_EVENTCATEGORY_SYSTEM)));
	SendDlgItemMessage(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS_TYPE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS_TYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_EVENTTYPE_SUCCESS)));
	SendDlgItemMessage(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS_LIST, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nColors[0].GetAt(0));
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_CATEGORIES)->EnableWindow();
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_CATEGORY_SYSTEM)->EnableWindow();
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_CATEGORY_SPACECRAFT)->EnableWindow();
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_CATEGORY_USER)->EnableWindow();
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_TYPES)->EnableWindow();
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_CONTENTS)->EnableWindow();
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_TIME)->EnableWindow();
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_STARTTIME)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_TIME));
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_TOTIME)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_TIME));
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_STOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_TIME));
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_EVENTS)->EnableWindow();
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_EVENTS_COUNT)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_EVENTS));
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_EVENTS_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_EVENTS));
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR)->EnableWindow();
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOEVENTS)->EnableWindow((((pDialog = GetParentDialog()->GetParentDialog()) && pDialog->GetMode() == DISPLAY_MODE_REALTIME) || (!pDialog  &&  GetParentDisplay()->GetMode() == DISPLAY_MODE_REALTIME)) ? TRUE : FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOACKNOWLEDGE)->EnableWindow(((pDialog != (CEventBoxOpenDialog *)NULL  &&  pDialog->GetMode() == DISPLAY_MODE_REALTIME) || (!pDialog  &&  GetParentDisplay()->GetMode() == DISPLAY_MODE_REALTIME)) ? TRUE : FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_NOTIFY)->EnableWindow((GetParentDisplay()->GetScope() == DISPLAY_SCOPE_LOCAL && ((pDialog != (CEventBoxOpenDialog *)NULL  &&  pDialog->GetMode() == DISPLAY_MODE_REALTIME) || (!pDialog  &&  GetParentDisplay()->GetMode() == DISPLAY_MODE_REALTIME))) ? TRUE : FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_BRINGEVENTS)->EnableWindow((GetParentDisplay()->GetScope() == DISPLAY_SCOPE_GLOBAL) ? TRUE : FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_USESOUND)->EnableWindow((GetParentDisplay()->GetScope() == DISPLAY_SCOPE_GLOBAL) ? TRUE : FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOEVENTS_COUNT)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOEVENTS));
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOEVENTS_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOEVENTS));
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_LISTEVENTS)->EnableWindow();
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS)->EnableWindow();
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS_CATEGORY_STATIC)->EnableWindow();
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS_CATEGORY)->EnableWindow();
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS_TYPE_STATIC)->EnableWindow();
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS_TYPE)->EnableWindow();
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS_USE)->EnableWindow();
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS_LIST)->EnableWindow();
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS_TEXT)->EnableWindow();
	AdjustToPrivileges();
	return TRUE;
}

void CEventBoxSettingsFilteringPage::OnFilterSystem()
{
	m_nMode[0] = (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_CATEGORY_SYSTEM)) ? (m_nMode[0] | EVENTBOX_FILTER_SYSTEM) : (m_nMode[0] & ~EVENTBOX_FILTER_SYSTEM);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsFilteringPage::OnFilterSpacecraft()
{
	m_nMode[0] = (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_CATEGORY_SPACECRAFT)) ? (m_nMode[0] | EVENTBOX_FILTER_SPACECRAFT) : (m_nMode[0] & ~EVENTBOX_FILTER_SPACECRAFT);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsFilteringPage::OnFilterUser()
{
	m_nMode[0] = (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_CATEGORY_USER)) ? (m_nMode[0] | EVENTBOX_FILTER_USER) : (m_nMode[0] & ~EVENTBOX_FILTER_USER);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsFilteringPage::OnFilterTypes()
{
	CEventBoxFilterDialog  cFilterDialog;

	for (; cFilterDialog.Create(this) == IDOK; )
	{
		cFilterDialog.GetFilterInfo(m_szTypes[0], m_szSubtypes[0]);
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsFilteringPage::OnLimitByTime()
{
	CTimeKey  tStartTime;
	CTimeKey  tStopTime(tStartTime.GetTime() + EVENTBOXSETTINGSFILTERINGPAGE_LIMITATION_DEFAULTINTERVAL);

	Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_STARTTIME), tStartTime);
	Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_STOPTIME), tStopTime);
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_STARTTIME)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_TIME));
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_TOTIME)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_TIME));
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_STOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_TIME));
	m_nMode[0] = (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_TIME)) ? (m_nMode[0] | EVENTBOX_FILTER_LIMITBYTIME) : (m_nMode[0] & ~EVENTBOX_FILTER_LIMITBYTIME);
	m_tStartTime[0] = (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_TIME)) ? tStartTime : m_tStartTime[1];
	m_tStopTime[0] = (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_TIME)) ? tStopTime : m_tStopTime[1];
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_STARTTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsFilteringPage::OnLimitByEvents()
{
	Spinbox_SetPos(GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_EVENTS_COUNT), EVENTBOXSETTINGSFILTERINGPAGE_LIMITATION_DEFAULTEVENTS);
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_EVENTS_COUNT)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_EVENTS));
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_EVENTS_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_EVENTS));
	m_nMode[0] = (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_EVENTS)) ? (m_nMode[0] | EVENTBOX_FILTER_LIMITBYEVENTS) : (m_nMode[0] & ~EVENTBOX_FILTER_LIMITBYEVENTS);
	m_nLimit[0] = (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_EVENTS)) ? (UINT)Spinbox_GetPos(GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_EVENTS_COUNT)) : m_nLimit[1];
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_EVENTS_COUNT)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsFilteringPage::OnSpinchangeLimitByStartTime()
{
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;

	for (m_tStartTime[0] = tStartTime = Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_STARTTIME)), m_tStopTime[0] = tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_STOPTIME)); tStartTime > tStopTime; )
	{
		Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_STOPTIME), (m_tStopTime[0] = tStartTime));
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsFilteringPage::OnSpinchangeLimitByStopTime()
{
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;

	for (m_tStartTime[0] = tStartTime = Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_STARTTIME)), m_tStopTime[0] = tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_STOPTIME)); tStartTime > tStopTime; )
	{
		Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_STARTTIME), (m_tStartTime[0] = tStopTime));
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsFilteringPage::OnSpinchangeLimitByEvents()
{
	m_nLimit[0] = (UINT)Spinbox_GetPos(GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_LIMITATION_EVENTS_COUNT));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsFilteringPage::OnBehaviorAutoEvents()
{
	Spinbox_SetPos(GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOEVENTS_COUNT), EVENTBOXSETTINGSFILTERINGPAGE_BEHAVIOR_DEFAULTEVENTS);
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOEVENTS_COUNT)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOEVENTS));
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOEVENTS_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOEVENTS));
	m_nMode[0] = (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOEVENTS)) ? (m_nMode[0] | EVENTBOX_FILTER_AUTOEVENTS) : (m_nMode[0] & ~EVENTBOX_FILTER_AUTOEVENTS);
	m_nCount[0] = (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOEVENTS)) ? (UINT)Spinbox_GetPos(GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOEVENTS_COUNT)) : m_nCount[1];
	GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOEVENTS_COUNT)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsFilteringPage::OnBehaviorBringEvents()
{
	m_nMode[0] = (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_BRINGEVENTS)) ? (m_nMode[0] | EVENTBOX_FILTER_BRINGEVENTS) : (m_nMode[0] & ~EVENTBOX_FILTER_BRINGEVENTS);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsFilteringPage::OnBehaviorListEvents()
{
	m_nMode[0] = (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_LISTEVENTS)) ? (m_nMode[0] | EVENTBOX_FILTER_LISTEVENTS) : (m_nMode[0] & ~EVENTBOX_FILTER_LISTEVENTS);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsFilteringPage::OnBehaviorAutoAcknowledge()
{
	m_nMode[0] = (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOACKNOWLEDGE)) ? ((m_nMode[0] | EVENTBOX_FILTER_AUTOACKNOWLEDGE) & ~EVENTBOX_FILTER_NOTIFY) : (m_nMode[0] & ~(EVENTBOX_FILTER_AUTOACKNOWLEDGE | EVENTBOX_FILTER_NOTIFY));
	CheckDlgButton(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_NOTIFY, FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsFilteringPage::OnBehaviorNotify()
{
	m_nMode[0] = (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_NOTIFY)) ? ((m_nMode[0] | EVENTBOX_FILTER_NOTIFY) & ~EVENTBOX_FILTER_AUTOACKNOWLEDGE) : (m_nMode[0] & ~(EVENTBOX_FILTER_AUTOACKNOWLEDGE | EVENTBOX_FILTER_NOTIFY));
	CheckDlgButton(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOACKNOWLEDGE, FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsFilteringPage::OnBehaviorUseSound()
{
	m_nMode[0] = (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_USESOUND)) ? (m_nMode[0] | EVENTBOX_FILTER_USESOUND) : (m_nMode[0] & ~EVENTBOX_FILTER_USESOUND);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsFilteringPage::OnSpinchangeBehaviorAutoEvents()
{
	m_nCount[0] = (UINT)Spinbox_GetPos(GetDlgItem(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOEVENTS_COUNT));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsFilteringPage::OnSelchangeColorsCategory()
{
	SendDlgItemMessage(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS_LIST, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nColors[0].GetAt(SendDlgItemMessage(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS_CATEGORY, CB_GETCURSEL)*(EVENT_TYPES - 1) + SendDlgItemMessage(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS_TYPE, CB_GETCURSEL)));
}

void CEventBoxSettingsFilteringPage::OnSelchangeColorsType()
{
	SendDlgItemMessage(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS_LIST, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nColors[0].GetAt(SendDlgItemMessage(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS_CATEGORY, CB_GETCURSEL)*(EVENT_TYPES - 1) + SendDlgItemMessage(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS_TYPE, CB_GETCURSEL)));
}

void CEventBoxSettingsFilteringPage::OnSelchangeColorsList()
{
	m_nColors[0].SetAt(SendDlgItemMessage(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS_CATEGORY, CB_GETCURSEL)*(EVENT_TYPES - 1) + SendDlgItemMessage(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS_TYPE, CB_GETCURSEL), (UINT)SendDlgItemMessage(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS_LIST, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_EVENTBOXSETTINGS_FILTERINGPAGE_COLORS_LIST, CB_GETCURSEL)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CEventBoxSettingsPrintingComments

IMPLEMENT_DYNCREATE(CEventBoxSettingsPrintingComments, CEdit)

BEGIN_MESSAGE_MAP(CEventBoxSettingsPrintingComments, CEdit)
	//{{AFX_MSG_MAP(CEventBoxSettingsPrintingComments)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventBoxSettingsPrintingComments message handlers

void CEventBoxSettingsPrintingComments::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
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
// CEventBoxSettingsPrintingPage property page

IMPLEMENT_DYNCREATE(CEventBoxSettingsPrintingPage, CLocalePropertyPage)

CEventBoxSettingsPrintingPage::CEventBoxSettingsPrintingPage() : CLocalePropertyPage(CEventBoxSettingsPrintingPage::IDD)
{
	//{{AFX_DATA_INIT(CEventBoxSettingsPrintingPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CEventBoxSettingsPrintingPage::Initialize()
{
	CEventBoxOpenDialog  *pDialog;

	return((((pDialog = GetParentDialog()->GetParentDialog()) && pDialog->GetPrintJobs(m_pJobs[0])) || GetParentDisplay()->GetPrintJobs(m_pJobs[0])) ? m_pJobs[1].Copy(&m_pJobs[0]) : FALSE);
}

BOOL CEventBoxSettingsPrintingPage::GetJobs(CEventBoxPrintJobs &pJobs) CONST
{
	return((pJobs.Copy(&m_pJobs[0])) ? Check(FALSE) : FALSE);
}

CEventBoxSettingsDialog *CEventBoxSettingsPrintingPage::GetParentDialog() CONST
{
	return((CEventBoxSettingsDialog *)CLocalePropertyPage::GetParent());
}

CEventBoxWnd *CEventBoxSettingsPrintingPage::GetParentDisplay() CONST
{
	return((CEventBoxWnd *)GetParentDialog()->GetParentDisplay());
}

VOID CEventBoxSettingsPrintingPage::ShowJobInfo()
{
	UINT  nMode;
	UINT  nCount;
	CTimeSpan  tStartTime;
	CTimeSpan  tStopTime;
	CEventBoxPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL, ((nMode = pJobInfo->GetPrintMode()) & EVENTBOX_PRINT_ALL) ? TRUE : FALSE);
		CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE, ((nMode & EVENTBOX_PRINT_FIRSTSIDE) || (nMode & EVENTBOX_PRINT_LASTSIDE)) ? TRUE : FALSE);
		CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME, (nMode & EVENTBOX_PRINT_DAILY) ? TRUE : FALSE);
		CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS, (nMode & EVENTBOX_PRINT_CLEARCOMMENTS) ? TRUE : FALSE);
		SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetProfile()));
		SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_SELECTTEXT, (WPARAM)-1, (nMode & EVENTBOX_PRINT_FIRSTSIDE) ? (LPARAM)STRING(IDS_EVENTBOXSETTINGS_PRINTINGPAGE_FIRSTSIDE) : ((nMode & EVENTBOX_PRINT_LASTSIDE) ? (LPARAM)STRING(IDS_EVENTBOXSETTINGS_PRINTINGPAGE_LASTSIDE) : (LPARAM)EMPTYSTRING));
		Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTARTTIME), (pJobInfo->GetPrintByTime(tStartTime, tStopTime)) ? CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + tStartTime.GetTotalSeconds() % SECONDSPERDAY) : CTime::GetCurrentTime().GetTime());
		Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTOPTIME), (pJobInfo->GetPrintByTime(tStartTime, tStopTime)) ? CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + tStopTime.GetTotalSeconds() % SECONDSPERDAY) : CTime::GetCurrentTime().GetTime());
		Spinbox_SetPos(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT), (pJobInfo->GetPrintBySide(nCount)) ? nCount : 0);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->SetWindowText(pJobInfo->GetComments());
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_ADDNAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_REMOVENAME)->EnableWindow((pJobInfo->GetName() != STRING(IDS_PRINTJOB_DEFAULTNAME)) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_REMOVEALLNAMES)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_NAME, CB_GETCOUNT) > 1) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES)->EnableWindow();
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE_STATIC)->EnableWindow();
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE)->EnableWindow();
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_OPTIONS)->EnableWindow();
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL)->EnableWindow();
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE)->EnableWindow();
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE));
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE));
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE));
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME)->EnableWindow();
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTARTTIME)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME));
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME));
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME));
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTS)->EnableWindow();
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT_STATIC)->EnableWindow();
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->EnableWindow();
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)->EnableWindow(!pJobInfo->GetComments().IsEmpty());
		return;
	}
	SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)-1);
	SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_SETCURSEL, (WPARAM)-1);
	CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL, FALSE);
	CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE, FALSE);
	CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME, FALSE);
	CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS, FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_ADDNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_REMOVENAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_REMOVEALLNAMES)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_OPTIONS)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTARTTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTOPTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTS)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)->EnableWindow(FALSE);
}

CEventBoxPrintJobInfo *CEventBoxSettingsPrintingPage::FindJobInfo() CONST
{
	CString  szJobName;

	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_NAME)->GetWindowText(szJobName);
	return m_pJobs[0].GetAt(m_pJobs[0].Find(szJobName));
}

BOOL CEventBoxSettingsPrintingPage::CheckPrivilege(UINT nPrivilege) CONST
{
	return((GetParentDisplay()->GetScope() == DISPLAY_SCOPE_GLOBAL) ? CheckAccountPrivilege(nPrivilege) : TRUE);
}

VOID CEventBoxSettingsPrintingPage::AdjustToPrivileges()
{
	BOOL  bCheck;

	AccessControl(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_NAME, (bCheck = CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE)));
	AccessControl(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_ADDNAME, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_REMOVENAME, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_REMOVEALLNAMES, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTARTTIME, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTOPTIME, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS, bCheck);
}

BOOL CEventBoxSettingsPrintingPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? !m_pJobs[0].Compare(&m_pJobs[1]) : CLocalePropertyPage::IsModified()) : FALSE);
}

BOOL CEventBoxSettingsPrintingPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? ((GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_NAME)->GetWindowTextLength() > 0 && FindJobInfo()) ? TRUE : FALSE) : CLocalePropertyPage::Check()) : TRUE);
}

void CEventBoxSettingsPrintingPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEventBoxSettingsPrintingPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CEventBoxSettingsPrintingPage::PostNcDestroy()
{
	m_pJobs[0].RemoveAll();
	m_pJobs[1].RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CEventBoxSettingsPrintingPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CEventBoxSettingsPrintingPage)
	ON_BN_CLICKED(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_ADDNAME, OnAddName)
	ON_BN_CLICKED(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_REMOVENAME, OnRemoveName)
	ON_BN_CLICKED(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_REMOVEALLNAMES, OnRemoveAllNames)
	ON_BN_CLICKED(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL, OnPrintAll)
	ON_BN_CLICKED(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE, OnPrintBySide)
	ON_BN_CLICKED(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME, OnPrintByTime)
	ON_BN_CLICKED(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS, OnResetComments)
	ON_CBN_EDITCHANGE(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_NAME, OnEditchangeName)
	ON_CBN_SELCHANGE(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_NAME, OnSelchangeName)
	ON_CBN_SELCHANGE(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, OnSelchangeProfile)
	ON_EN_CHANGE(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, OnChangePrintSide)
	ON_EN_CHANGE(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT, OnEditchangeComments)
	ON_CONTROL(SBXN_CHANGE, IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT, OnSpinchangePrintSideCount)
	ON_CONTROL(TSBXN_CHANGE, IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTARTTIME, OnSpinchangePrintStartTime)
	ON_CONTROL(TSBXN_CHANGE, IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTOPTIME, OnSpinchangePrintStopTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventBoxSettingsPrintingPage message handlers

BOOL CEventBoxSettingsPrintingPage::OnInitDialog()
{
	INT  nJob;
	INT  nJobs;
	INT  nProfile;
	INT  nProfiles;
	CStringArray  szProfiles;
	CEventBoxPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	for (CLocalePropertyPage::OnInitDialog(); m_wndComments.SubclassWindow(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->GetSafeHwnd()); )
	{
		for (nJob = 0, nJobs = (INT)m_pJobs[0].GetSize(); nJob < nJobs; nJob++)
		{
			if ((pJobInfo = m_pJobs[0].GetAt(nJob)) != (CEventBoxPrintJobInfo *)NULL)
			{
				SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_NAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pJobInfo->GetName());
				continue;
			}
		}
		for (nProfile = 0, nProfiles = (EnumPrintProfiles(szProfiles)) ? (INT)szProfiles.GetSize() : 0; nProfile < nProfiles; nProfile++)
		{
			SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szProfiles.GetAt(nProfile));
			continue;
		}
		Spinbox_SetRange(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT), EVENTBOXSETTINGSPRINTINGPAGE_OPTIONS_MINIMUMEVENTS, EVENTBOXSETTINGSPRINTINGPAGE_OPTIONS_MAXIMUMEVENTS);
		SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_PRINTJOB_DEFAULTNAME)));
		SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_ADDTEXT, (WPARAM)NULL, (LPARAM)STRING(IDS_EVENTBOXSETTINGS_PRINTINGPAGE_FIRSTSIDE));
		SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_ADDTEXT, (WPARAM)NULL, (LPARAM)STRING(IDS_EVENTBOXSETTINGS_PRINTINGPAGE_LASTSIDE));
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_DETAILS)->EnableWindow();
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_NAME_STATIC)->EnableWindow();
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_NAME)->EnableWindow();
		ShowJobInfo();
		break;
	}
	AdjustToPrivileges();
	return TRUE;
}

BOOL CEventBoxSettingsPrintingPage::OnSetActive()
{
	ShowJobInfo();
	return CLocalePropertyPage::OnSetActive();
}

BOOL CEventBoxSettingsPrintingPage::OnKillActive()
{
	GetParentDialog()->OnDataExchange(GetSafeHwnd(), m_pJobs[0]);
	return CLocalePropertyPage::OnKillActive();
}

BOOL CEventBoxSettingsPrintingPage::OnDataExchange(CONST CEventBoxPrintJobs &pJobs)
{
	return m_pJobs[0].Copy(&pJobs);
}

void CEventBoxSettingsPrintingPage::OnEditchangeName()
{
	CString  szJobName;
	CEventBoxPrintJobInfo  *pJobInfo;

	for (GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_NAME)->GetWindowText(szJobName); (pJobInfo = FindJobInfo()); )
	{
		ShowJobInfo();
		return;
	}
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_ADDNAME)->EnableWindow((!pJobInfo  &&  szJobName.GetLength() > 0) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_REMOVENAME)->EnableWindow((pJobInfo != (CEventBoxPrintJobInfo *)NULL  &&  szJobName != STRING(IDS_PRINTJOB_DEFAULTNAME)) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_REMOVEALLNAMES)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_NAME, CB_GETCOUNT) > 1) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)->EnableWindow((szJobName != STRING(IDS_PRINTJOB_DEFAULTNAME)) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsPrintingPage::OnSelchangeName()
{
	SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_NAME, CB_GETCURSEL));
	ShowJobInfo();
}

void CEventBoxSettingsPrintingPage::OnAddName()
{
	INT  nIndex;
	UINT  nMode;
	UINT  nCount;
	CString  szJobName;
	CString  szProfile;
	CString  szComments;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CEventBoxPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	for (; (pJobInfo = new CEventBoxPrintJobInfo); )
	{
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_NAME)->GetWindowText(szJobName);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE)->GetWindowText(szProfile);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->GetWindowText(szComments);
		nMode = (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL)) ? ((pJobInfo->GetPrintMode() | EVENTBOX_PRINT_ALL) & ~(EVENTBOX_PRINT_FIRSTSIDE | EVENTBOX_PRINT_LASTSIDE | EVENTBOX_PRINT_DAILY)) : pJobInfo->GetPrintMode();
		nMode = (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE)) ? ((!GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE)->SendMessage(TEM_GETPOS)) ? ((nMode | EVENTBOX_PRINT_FIRSTSIDE) & ~(EVENTBOX_PRINT_ALL | EVENTBOX_PRINT_LASTSIDE | EVENTBOX_PRINT_DAILY)) : ((nMode | EVENTBOX_PRINT_LASTSIDE) & ~(EVENTBOX_PRINT_ALL | EVENTBOX_PRINT_FIRSTSIDE | EVENTBOX_PRINT_DAILY))) : nMode;
		nMode = (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME)) ? ((nMode | EVENTBOX_PRINT_DAILY) & ~(EVENTBOX_PRINT_ALL | EVENTBOX_PRINT_FIRSTSIDE | EVENTBOX_PRINT_LASTSIDE)) : nMode;
		nMode = (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)) ? (nMode | EVENTBOX_PRINT_CLEARCOMMENTS) : (nMode & ~EVENTBOX_PRINT_CLEARCOMMENTS);
		for (nCount = 0, tStartTime = tStopTime = 0; (nMode & EVENTBOX_PRINT_FIRSTSIDE) || (nMode & EVENTBOX_PRINT_LASTSIDE); )
		{
			nCount = (UINT)Spinbox_GetPos(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT));
			break;
		}
		if (nMode & EVENTBOX_PRINT_DAILY)
		{
			tStartTime = Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTARTTIME));
			tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTOPTIME));
		}
		if (SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_NAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szJobName) >= 0 && SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szJobName)) >= 0)
		{
			for (pJobInfo->SetName(szJobName), pJobInfo->SetProfile(szProfile), pJobInfo->SetComments(szComments), pJobInfo->SetPrintMode(nMode), pJobInfo->SetPrintBySide(nCount), pJobInfo->SetPrintByTime(tStartTime.GetTime() % SECONDSPERDAY, tStopTime.GetTime() % SECONDSPERDAY); (nIndex = m_pJobs[0].Add(pJobInfo)) >= 0; )
			{
				ShowJobInfo();
				break;
			}
			if (nIndex >= 0) break;
		}
		delete pJobInfo;
		break;
	}
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsPrintingPage::OnRemoveName()
{
	INT  nJob;
	INT  nJobs;
	CEventBoxPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	for (nJob = 0, nJobs = (INT)m_pJobs[0].GetSize(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = m_pJobs[0].GetAt(nJob)) && pJobInfo == FindJobInfo())
		{
			if (SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_NAME, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName())) > 0)
			{
				m_pJobs[0].RemoveAt(nJob);
				delete pJobInfo;
			}
			break;
		}
	}
	for (; SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_PRINTJOB_DEFAULTNAME))) >= 0; )
	{
		ShowJobInfo();
		break;
	}
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsPrintingPage::OnRemoveAllNames()
{
	INT  nJob;
	INT  nJobs;
	CEventBoxPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	for (nJob = 0, nJobs = (INT)m_pJobs[0].GetSize(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = m_pJobs[0].GetAt(nJob)) && pJobInfo->GetName() != STRING(IDS_PRINTJOB_DEFAULTNAME) && SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_NAME, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName())) > 0)
		{
			m_pJobs[0].RemoveAt(nJob);
			delete pJobInfo;
			nJobs--;
			nJob--;
		}
	}
	for (; SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_PRINTJOB_DEFAULTNAME))) >= 0; )
	{
		ShowJobInfo();
		break;
	}
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsPrintingPage::OnSelchangeProfile()
{
	CString  szProfile;
	CEventBoxPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE)->GetWindowText(szProfile);
		pJobInfo->SetProfile(szProfile);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsPrintingPage::OnPrintAll()
{
	CEventBoxPrintJobInfo  *pJobInfo;

	if (!IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL))
	{
		for (CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL, TRUE), CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE, FALSE), CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME, FALSE), SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_SELECTTEXT, (WPARAM)-1, (LPARAM)EMPTYSTRING); (pJobInfo = FindJobInfo()); )
		{
			pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | EVENTBOX_PRINT_ALL) & ~(EVENTBOX_PRINT_FIRSTSIDE | EVENTBOX_PRINT_LASTSIDE | EVENTBOX_PRINT_DAILY));
			break;
		}
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_ADDNAME)->EnableWindow((GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_NAME)->GetWindowTextLength() > 0 && SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_GETCURSEL) != CB_ERR  &&  !pJobInfo) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTARTTIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTOPTIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME_STATIC)->EnableWindow(FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsPrintingPage::OnPrintBySide()
{
	CEventBoxPrintJobInfo  *pJobInfo;

	if (!IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE))
	{
		for (CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL, FALSE), CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE, TRUE), CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME, FALSE), SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_SELECTTEXT, (WPARAM)-1, (LPARAM)STRING(IDS_EVENTBOXSETTINGS_PRINTINGPAGE_LASTSIDE)), Spinbox_SetPos(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT), EVENTBOXSETTINGSPRINTINGPAGE_OPTIONS_DEFAULTEVENTS); (pJobInfo = FindJobInfo()); )
		{
			pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | EVENTBOX_PRINT_LASTSIDE) & ~(EVENTBOX_PRINT_ALL | EVENTBOX_PRINT_FIRSTSIDE | EVENTBOX_PRINT_DAILY));
			pJobInfo->SetPrintBySide(EVENTBOXSETTINGSPRINTINGPAGE_OPTIONS_DEFAULTEVENTS);
			break;
		}
		SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, EM_SETSEL, 0, (LPARAM)-1);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_ADDNAME)->EnableWindow((GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_NAME)->GetWindowTextLength() > 0 && SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_GETCURSEL) != CB_ERR  &&  !pJobInfo) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE)->EnableWindow();
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)->EnableWindow();
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE_STATIC)->EnableWindow();
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTARTTIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTOPTIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE)->SetFocus();
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsPrintingPage::OnPrintByTime()
{
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CEventBoxPrintJobInfo  *pJobInfo;

	if (!IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME))
	{
		for (CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL, FALSE), CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE, FALSE), CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME, TRUE), Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTARTTIME), (tStartTime = SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + CTimeSpan(0, 11, 0, 0).GetTotalSeconds())), Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTOPTIME), (tStopTime = tStartTime.GetTime() + EVENTBOXSETTINGSPRINTINGPAGE_OPTIONS_DEFAULTINTERVAL)); (pJobInfo = FindJobInfo()); )
		{
			pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | EVENTBOX_PRINT_DAILY) & ~(EVENTBOX_PRINT_ALL | EVENTBOX_PRINT_FIRSTSIDE | EVENTBOX_PRINT_LASTSIDE));
			pJobInfo->SetPrintByTime(tStartTime.GetTime() % SECONDSPERDAY, tStopTime.GetTime() % SECONDSPERDAY);
			break;
		}
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_ADDNAME)->EnableWindow((GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_NAME)->GetWindowTextLength() > 0 && SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_GETCURSEL) != CB_ERR  &&  !pJobInfo) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTARTTIME)->EnableWindow();
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTOPTIME)->EnableWindow();
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME_STATIC)->EnableWindow();
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTARTTIME)->SetFocus();
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsPrintingPage::OnChangePrintSide()
{
	UINT  nMode;
	CEventBoxPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		nMode = (!SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_GETPOS)) ? ((pJobInfo->GetPrintMode() | EVENTBOX_PRINT_FIRSTSIDE) & ~(EVENTBOX_PRINT_ALL | EVENTBOX_PRINT_LASTSIDE | EVENTBOX_PRINT_DAILY)) : ((pJobInfo->GetPrintMode() | EVENTBOX_PRINT_LASTSIDE) & ~(EVENTBOX_PRINT_ALL | EVENTBOX_PRINT_FIRSTSIDE | EVENTBOX_PRINT_DAILY));
		pJobInfo->SetPrintMode(nMode);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsPrintingPage::OnSpinchangePrintSideCount()
{
	CEventBoxPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo())) pJobInfo->SetPrintBySide((UINT)Spinbox_GetPos(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsPrintingPage::OnSpinchangePrintStartTime()
{
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CEventBoxPrintJobInfo  *pJobInfo;

	for (tStartTime = Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTARTTIME)), tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTOPTIME)); (pJobInfo = FindJobInfo()); )
	{
		pJobInfo->SetPrintByTime(tStartTime.GetTime() % SECONDSPERDAY, (tStartTime > tStopTime) ? (tStartTime.GetTime() % SECONDSPERDAY) : (tStopTime.GetTime() % SECONDSPERDAY));
		break;
	}
	Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTOPTIME), (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME) && tStartTime > tStopTime) ? tStartTime : tStopTime);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsPrintingPage::OnSpinchangePrintStopTime()
{
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CEventBoxPrintJobInfo  *pJobInfo;

	for (tStartTime = Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTARTTIME)), tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTOPTIME)); (pJobInfo = FindJobInfo()); )
	{
		pJobInfo->SetPrintByTime((tStartTime <= tStopTime) ? (tStartTime.GetTime() % SECONDSPERDAY) : (tStopTime.GetTime() % SECONDSPERDAY), tStopTime.GetTime() % SECONDSPERDAY);
		break;
	}
	Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTARTTIME), (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME) && tStartTime > tStopTime) ? tStopTime : tStartTime);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsPrintingPage::OnEditchangeComments()
{
	CString  szComments;
	CEventBoxPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->GetWindowText(szComments);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)->EnableWindow(!szComments.IsEmpty());
		CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS, (!szComments.IsEmpty()) ? IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS) : FALSE);
		pJobInfo->SetPrintMode((IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)) ? (pJobInfo->GetPrintMode() | EVENTBOX_PRINT_CLEARCOMMENTS) : (pJobInfo->GetPrintMode() & ~EVENTBOX_PRINT_CLEARCOMMENTS));
		pJobInfo->SetComments(szComments);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsPrintingPage::OnResetComments()
{
	UINT  nMode;
	CEventBoxPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		nMode = (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)) ? (pJobInfo->GetPrintMode() | EVENTBOX_PRINT_CLEARCOMMENTS) : (pJobInfo->GetPrintMode() & ~EVENTBOX_PRINT_CLEARCOMMENTS);
		pJobInfo->SetPrintMode(nMode);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CEventBoxSettingsPrintJobsPage property page

IMPLEMENT_DYNCREATE(CEventBoxSettingsPrintJobsPage, CLocalePropertyPage)

CEventBoxSettingsPrintJobsPage::CEventBoxSettingsPrintJobsPage() : CLocalePropertyPage(CEventBoxSettingsPrintJobsPage::IDD)
{
	//{{AFX_DATA_INIT(CEventBoxSettingsPrintJobsPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CEventBoxSettingsPrintJobsPage::Initialize()
{
	CEventBoxOpenDialog  *pDialog;

	return((((pDialog = GetParentDialog()->GetParentDialog()) && pDialog->GetPrintJobs(m_pJobs[0])) || GetParentDisplay()->GetPrintJobs(m_pJobs[0])) ? m_pJobs[1].Copy(&m_pJobs[0]) : FALSE);
}

BOOL CEventBoxSettingsPrintJobsPage::GetJobs(CEventBoxPrintJobs &pJobs) CONST
{
	return((pJobs.Copy(&m_pJobs[0])) ? Check(FALSE) : FALSE);
}

CEventBoxSettingsDialog *CEventBoxSettingsPrintJobsPage::GetParentDialog() CONST
{
	return((CEventBoxSettingsDialog *)CLocalePropertyPage::GetParent());
}

CEventBoxWnd *CEventBoxSettingsPrintJobsPage::GetParentDisplay() CONST
{
	return((CEventBoxWnd *)GetParentDialog()->GetParentDisplay());
}

BOOL CEventBoxSettingsPrintJobsPage::EnumJobs()
{
	INT  nJob;
	INT  nJobs;
	UINT  nMode;
	CEventBoxPrintJobInfo  *pJobInfo;

	SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, LB_RESETCONTENT);
	SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_RESETCONTENT);
	for (nJob = 0, nJobs = (INT)m_pJobs[0].GetSize(); nJob < nJobs; nJob = nJob + 1)
	{
		if ((pJobInfo = m_pJobs[0].GetAt(nJob)) && pJobInfo->GetName() != STRING(IDS_PRINTJOB_DEFAULTNAME))
		{
			if (SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pJobInfo->GetName()) >= 0)
			{
				if (((nMode = pJobInfo->GetPrintMode()) & EVENTBOX_PRINT_ACTIVE) && ((nMode & EVENTBOX_PRINT_ATTIME) || (nMode & EVENTBOX_PRINT_ATDAILYTIME) || (nMode & EVENTBOX_PRINT_ATCOUNT)))
				{
					if (SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR)
					{
						pJobInfo->SetPrintMode(nMode & ~(EVENTBOX_PRINT_ACTIVE | EVENTBOX_PRINT_ATTIME | EVENTBOX_PRINT_ATDAILYTIME | EVENTBOX_PRINT_ATCOUNT | EVENTBOX_PRINT_REPEATBYINTERVAL | EVENTBOX_PRINT_REPEATSTOPBYCOUNT | EVENTBOX_PRINT_REPEATSTOPBYTIME | EVENTBOX_PRINT_DAILYREPEATSTOPBYCOUNT | EVENTBOX_PRINT_DAILYREPEATSTOPBYTIME));
						continue;
					}
				}
			}
		}
	}
	if (SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, LB_GETCOUNT) > 0)
	{
		SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, LB_SETCURSEL);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_DETAILS)->EnableWindow();
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS_STATIC)->EnableWindow();
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS)->EnableWindow();
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)Listbox_GetText(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS), (INT)SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, LB_GETCURSEL))) == LB_ERR  &&  CheckJobInfo()) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_REMOVEJOB)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCURSEL) >= 0) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
		ShowJobInfo();
		return TRUE;
	}
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_DETAILS)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_REMOVEJOB)->EnableWindow(FALSE);
	ShowJobInfo();
	return FALSE;
}

VOID CEventBoxSettingsPrintJobsPage::ShowJobInfo()
{
	UINT  nCount;
	UINT  nStopCount;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CTimeSpan  tDailyTime;
	CEventBoxPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME), (pJobInfo->GetPrintAtTime(tTime) || pJobInfo->GetPrintAtTime(tTime, tInterval) || pJobInfo->GetPrintAtTime(tTime, tInterval, nStopCount) || pJobInfo->GetPrintAtTime(tTime, tInterval, tStopTime)) ? tTime : CTime::GetCurrentTime().GetTime());
		Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME), (pJobInfo->GetPrintAtDailyTime(tDailyTime) || pJobInfo->GetPrintAtDailyTime(tDailyTime, nStopCount) || pJobInfo->GetPrintAtDailyTime(tDailyTime, tStopTime)) ? CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + tDailyTime.GetTotalSeconds()) : CTime::GetCurrentTime().GetTime());
		Spinbox_SetPos(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTCOUNT), (pJobInfo->GetPrintAtCount(nCount)) ? nCount : 0);
		SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, (SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_EVENTBOXSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS)) < 0 && (pJobInfo->GetPrintMode() & EVENTBOX_PRINT_ATTIME)) ? CB_ADDSTRING : CB_FINDSTRING, (WPARAM)NULL, (LPARAM)STRING(IDS_EVENTBOXSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS));
		SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, (SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_EVENTBOXSETTINGS_PRINTJOBSPAGE_DAILYPRINTS)) < 0 && (pJobInfo->GetPrintMode() & EVENTBOX_PRINT_ATDAILYTIME)) ? CB_ADDSTRING : CB_FINDSTRING, (WPARAM)NULL, (LPARAM)STRING(IDS_EVENTBOXSETTINGS_PRINTJOBSPAGE_DAILYPRINTS));
		SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_SETCURSEL, ((pJobInfo->GetPrintMode() & EVENTBOX_PRINT_ATTIME) || (pJobInfo->GetPrintMode() & EVENTBOX_PRINT_ATDAILYTIME)) ? (WPARAM)SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)((pJobInfo->GetPrintMode() & EVENTBOX_PRINT_ATTIME) ? STRING(IDS_EVENTBOXSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS) : STRING(IDS_EVENTBOXSETTINGS_PRINTJOBSPAGE_DAILYPRINTS))) : (WPARAM)-1);
		CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME, (pJobInfo->GetPrintMode() & EVENTBOX_PRINT_ATTIME) ? TRUE : FALSE);
		CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME, (pJobInfo->GetPrintMode() & EVENTBOX_PRINT_ATDAILYTIME) ? TRUE : FALSE);
		CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATCOUNT, (pJobInfo->GetPrintMode() & EVENTBOX_PRINT_ATCOUNT) ? TRUE : FALSE);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR)->EnableWindow();
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME)->EnableWindow();
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME));
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)->EnableWindow();
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATCOUNT)->EnableWindow();
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTCOUNT)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATCOUNT));
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATCOUNT_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATCOUNT));
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		SetJobRepetitionInfo();
		return;
	}
	CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME, FALSE);
	CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME, FALSE);
	CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATCOUNT, FALSE);
	CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME, FALSE);
	CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, FALSE);
	CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, FALSE);
	SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_SETCURSEL, (WPARAM)-1);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATCOUNT)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTCOUNT)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATCOUNT_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow(FALSE);
}

BOOL CEventBoxSettingsPrintJobsPage::CheckJobInfo() CONST
{
	UINT  nCount;
	UINT  nStopCount;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CTimeSpan  tDailyTime;
	CEventBoxPrintJobInfo  *pJobInfo;

	return(((pJobInfo = FindJobInfo())) ? ((pJobInfo->GetPrintAtTime(tTime) && tTime > CTime::GetCurrentTime()) || pJobInfo->GetPrintAtTime(tTime, tInterval) || (pJobInfo->GetPrintAtTime(tTime, tInterval, nStopCount) && tTime.GetTime() + tInterval.GetTotalSeconds()*(TIMEKEY)nStopCount > CTime::GetCurrentTime().GetTime()) || (pJobInfo->GetPrintAtTime(tTime, tInterval, tStopTime) && tStopTime > CTime::GetCurrentTime()) || pJobInfo->GetPrintAtDailyTime(tDailyTime) || pJobInfo->GetPrintAtDailyTime(tDailyTime, nStopCount) || (pJobInfo->GetPrintAtDailyTime(tDailyTime, tStopTime) && tStopTime > CTime::GetCurrentTime()) || pJobInfo->GetPrintAtCount(nCount)) : FALSE);
}

CEventBoxPrintJobInfo *CEventBoxSettingsPrintJobsPage::FindJobInfo(BOOL bActive) CONST
{
	INT  nJob;
	INT  nJobs;
	CString  szJobName[2];
	CEventBoxPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (INT)m_pJobs[0].GetSize(), szJobName[0] = Listbox_GetText(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS), (INT)GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS)->SendMessage(LB_GETCURSEL)), szJobName[1] = Listbox_GetText(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS), (INT)GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS)->SendMessage(LB_GETCURSEL)), szJobName[0] = (!bActive) ? szJobName[0] : szJobName[1]; nJob < nJobs; nJob++)
	{
		if ((pJobInfo = m_pJobs[0].GetAt(nJob)) && pJobInfo->GetName() == szJobName[0]) break;
		continue;
	}
	return((nJob < nJobs) ? pJobInfo : (CEventBoxPrintJobInfo *)NULL);
}

VOID CEventBoxSettingsPrintJobsPage::SetJobRepetitionInfo()
{
	UINT  nStopCount;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CTimeSpan  tDailyTime;
	CEventBoxPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), ((GetJobRepetitionType() == EVENTBOXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  pJobInfo->GetPrintAtTime(tTime, tInterval, tStopTime)) || (GetJobRepetitionType() == EVENTBOXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  pJobInfo->GetPrintAtDailyTime(tDailyTime, tStopTime))) ? tStopTime : CTime::GetCurrentTime().GetTime());
		Spinbox_SetPos(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME), (pJobInfo->GetPrintAtTime(tTime, tInterval) || pJobInfo->GetPrintAtTime(tTime, tInterval, nStopCount) || pJobInfo->GetPrintAtTime(tTime, tInterval, tStopTime)) ? (tInterval.GetTotalSeconds() / SECONDSPERMINUTE) : 0);
		Spinbox_SetPos(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), ((GetJobRepetitionType() == EVENTBOXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  pJobInfo->GetPrintAtTime(tTime, tInterval, nStopCount)) || (GetJobRepetitionType() == EVENTBOXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  pJobInfo->GetPrintAtDailyTime(tDailyTime, nStopCount))) ? nStopCount : 0);
		CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME, (GetJobRepetitionType() == EVENTBOXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY && (pJobInfo->GetPrintMode() & EVENTBOX_PRINT_REPEATBYINTERVAL)) ? TRUE : FALSE);
		CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, ((GetJobRepetitionType() == EVENTBOXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY && (pJobInfo->GetPrintMode() & EVENTBOX_PRINT_REPEATSTOPBYCOUNT)) || (GetJobRepetitionType() == EVENTBOXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY && (pJobInfo->GetPrintMode() & EVENTBOX_PRINT_DAILYREPEATSTOPBYCOUNT))) ? TRUE : FALSE);
		CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, ((GetJobRepetitionType() == EVENTBOXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY && (pJobInfo->GetPrintMode() & EVENTBOX_PRINT_REPEATSTOPBYTIME)) || (GetJobRepetitionType() == EVENTBOXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY && (pJobInfo->GetPrintMode() & EVENTBOX_PRINT_DAILYREPEATSTOPBYTIME))) ? TRUE : FALSE);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)->EnableWindow((GetJobRepetitionType() == EVENTBOXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY) ? TRUE : FALSE);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)->EnableWindow(GetJobRepetitionType() == EVENTBOXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC)->EnableWindow(GetJobRepetitionType() == EVENTBOXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC)->EnableWindow((IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && (GetJobRepetitionType() == EVENTBOXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY || IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)));
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)->EnableWindow((IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && (GetJobRepetitionType() == EVENTBOXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY || IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)));
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow((IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES));
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow((IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES));
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)->EnableWindow((IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && (GetJobRepetitionType() == EVENTBOXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY || IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)));
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow((IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME));
		return;
	}
	CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME, FALSE);
	CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, FALSE);
	CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow(FALSE);
}

UINT CEventBoxSettingsPrintJobsPage::GetJobRepetitionType() CONST
{
	CString  szRepetitionType;

	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE)->GetWindowText(szRepetitionType);
	return((szRepetitionType == STRING(IDS_EVENTBOXSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS) || szRepetitionType == STRING(IDS_EVENTBOXSETTINGS_PRINTJOBSPAGE_DAILYPRINTS)) ? ((szRepetitionType == STRING(IDS_EVENTBOXSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS)) ? EVENTBOXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY : EVENTBOXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY) : 0);
}

BOOL CEventBoxSettingsPrintJobsPage::CheckPrivilege(UINT nPrivilege) CONST
{
	return((GetParentDisplay()->GetScope() == DISPLAY_SCOPE_GLOBAL) ? CheckAccountPrivilege(nPrivilege) : TRUE);
}

VOID CEventBoxSettingsPrintJobsPage::AdjustToPrivileges()
{
	BOOL  bCheck;

	AccessControl(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, (bCheck = CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE)));
	AccessControl(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ADDJOB, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_REMOVEJOB, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATCOUNT, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTCOUNT, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, bCheck);
	AccessControl(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME, bCheck);
}

BOOL CEventBoxSettingsPrintJobsPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? !m_pJobs[0].Compare(&m_pJobs[1]) : CLocalePropertyPage::IsModified()) : FALSE);
}

BOOL CEventBoxSettingsPrintJobsPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? TRUE : CLocalePropertyPage::Check()) : TRUE);
}

void CEventBoxSettingsPrintJobsPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEventBoxSettingsPrintJobsPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CEventBoxSettingsPrintJobsPage::PostNcDestroy()
{
	m_pJobs[0].RemoveAll();
	m_pJobs[1].RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CEventBoxSettingsPrintJobsPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CEventBoxSettingsPrintJobsPage)
	ON_BN_CLICKED(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ADDJOB, OnAddJob)
	ON_BN_CLICKED(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_REMOVEJOB, OnRemoveJob)
	ON_BN_CLICKED(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME, OnPrintAtTime)
	ON_BN_CLICKED(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME, OnPrintAtDailyTime)
	ON_BN_CLICKED(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATCOUNT, OnPrintAtCount)
	ON_BN_CLICKED(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME, OnRepeatByTime)
	ON_BN_CLICKED(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, OnRepetitionStopByCopies)
	ON_BN_CLICKED(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, OnRepetitionStopByTime)
	ON_CBN_SELCHANGE(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, OnSelchangeRepetitionType)
	ON_LBN_SELCHANGE(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, OnSelchangeDefinedJob)
	ON_LBN_SELCHANGE(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, OnSelchangeActiveJob)
	ON_CONTROL(SBXN_CHANGE, IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTCOUNT, OnSpinchangePrintCount)
	ON_CONTROL(SBXN_CHANGE, IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME, OnSpinchangeRepeatTime)
	ON_CONTROL(SBXN_CHANGE, IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES, OnSpinchangeRepetitionStopCopies)
	ON_CONTROL(TSBXN_CHANGE, IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME, OnSpinchangePrintTime)
	ON_CONTROL(TSBXN_CHANGE, IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME, OnSpinchangePrintDailyTime)
	ON_CONTROL(TSBXN_CHANGE, IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME, OnSpinchangeRepetitionStopTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventBoxSettingsPrintJobsPage message handlers

BOOL CEventBoxSettingsPrintJobsPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	Spinbox_SetRange(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTCOUNT), EVENTBOXSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES, EVENTBOXSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES);
	Spinbox_SetRange(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME), EVENTBOXSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMINTERVAL, EVENTBOXSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMINTERVAL);
	Spinbox_SetRange(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), EVENTBOXSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES, EVENTBOXSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES);
	AdjustToPrivileges();
	return TRUE;
}

BOOL CEventBoxSettingsPrintJobsPage::OnSetActive()
{
	EnumJobs();
	return CLocalePropertyPage::OnSetActive();
}

BOOL CEventBoxSettingsPrintJobsPage::OnKillActive()
{
	GetParentDialog()->OnDataExchange(GetSafeHwnd(), m_pJobs[0]);
	return CLocalePropertyPage::OnKillActive();
}

BOOL CEventBoxSettingsPrintJobsPage::OnDataExchange(CONST CEventBoxPrintJobs &pJobs)
{
	return m_pJobs[0].Copy(&pJobs);
}

void CEventBoxSettingsPrintJobsPage::OnAddJob()
{
	CEventBoxPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	if ((pJobInfo = FindJobInfo()))
	{
		pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() | EVENTBOX_PRINT_ACTIVE);
		SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pJobInfo->GetName());
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow(FALSE);
	}
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsPrintJobsPage::OnRemoveJob()
{
	CEventBoxPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	if ((pJobInfo = FindJobInfo(TRUE)))
	{
		for (pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~(EVENTBOX_PRINT_ACTIVE | EVENTBOX_PRINT_ATTIME | EVENTBOX_PRINT_ATDAILYTIME | EVENTBOX_PRINT_ATCOUNT | EVENTBOX_PRINT_REPEATBYINTERVAL | EVENTBOX_PRINT_REPEATSTOPBYCOUNT | EVENTBOX_PRINT_REPEATSTOPBYTIME | EVENTBOX_PRINT_DAILYREPEATSTOPBYCOUNT | EVENTBOX_PRINT_DAILYREPEATSTOPBYTIME)), SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCURSEL)); pJobInfo == FindJobInfo(); )
		{
			ShowJobInfo();
			break;
		}
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_REMOVEJOB)->EnableWindow(FALSE);
	}
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsPrintJobsPage::OnSelchangeDefinedJob()
{
	CEventBoxPrintJobInfo  *pJobInfo;

	ShowJobInfo();
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow(((pJobInfo = FindJobInfo()) && SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
}

void CEventBoxSettingsPrintJobsPage::OnSelchangeActiveJob()
{
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_REMOVEJOB)->EnableWindow(CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE));
}

void CEventBoxSettingsPrintJobsPage::OnPrintAtTime()
{
	CTimeKey  tTime;
	CEventBoxPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		if (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME))
		{
			Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME), (tTime = CTime::GetCurrentTime().GetTime() + SECONDSPERMINUTE*EVENTBOXSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL));
			SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)STRING(IDS_EVENTBOXSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS));
			pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | EVENTBOX_PRINT_ATTIME) & ~(EVENTBOX_PRINT_REPEATBYINTERVAL | EVENTBOX_PRINT_REPEATSTOPBYCOUNT | EVENTBOX_PRINT_REPEATSTOPBYTIME));
			pJobInfo->SetPrintAtTime(tTime);
		}
		else
		{
			SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_EVENTBOXSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS)));
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~(EVENTBOX_PRINT_ATTIME | EVENTBOX_PRINT_REPEATBYINTERVAL | EVENTBOX_PRINT_REPEATSTOPBYCOUNT | EVENTBOX_PRINT_REPEATSTOPBYTIME));
		}
		SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_SETCURSEL, (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) ? (WPARAM)SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)((IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME)) ? STRING(IDS_EVENTBOXSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS) : STRING(IDS_EVENTBOXSETTINGS_PRINTJOBSPAGE_DAILYPRINTS))) : (WPARAM)-1);
		Spinbox_SetRange(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME)) ? (EVENTBOXSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES + 1) : EVENTBOXSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES, EVENTBOXSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME));
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
		SetJobRepetitionInfo();
	}
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsPrintJobsPage::OnPrintAtDailyTime()
{
	CTimeKey  tTime;
	CEventBoxPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		if (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME))
		{
			Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME), (tTime = CTime::GetCurrentTime().GetTime() + SECONDSPERMINUTE*EVENTBOXSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL));
			SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)STRING(IDS_EVENTBOXSETTINGS_PRINTJOBSPAGE_DAILYPRINTS));
			pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | EVENTBOX_PRINT_ATDAILYTIME) & ~(EVENTBOX_PRINT_DAILYREPEATSTOPBYCOUNT | EVENTBOX_PRINT_DAILYREPEATSTOPBYTIME));
			pJobInfo->SetPrintAtDailyTime(tTime.GetTime() % SECONDSPERDAY);
		}
		else
		{
			SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_EVENTBOXSETTINGS_PRINTJOBSPAGE_DAILYPRINTS)));
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~(EVENTBOX_PRINT_ATDAILYTIME | EVENTBOX_PRINT_DAILYREPEATSTOPBYCOUNT | EVENTBOX_PRINT_DAILYREPEATSTOPBYTIME));
		}
		SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_SETCURSEL, (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) ? (WPARAM)SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)((IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) ? STRING(IDS_EVENTBOXSETTINGS_PRINTJOBSPAGE_DAILYPRINTS) : STRING(IDS_EVENTBOXSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS))) : (WPARAM)-1);
		Spinbox_SetRange(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) ? EVENTBOXSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES : (EVENTBOXSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES + 1), EVENTBOXSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
		SetJobRepetitionInfo();
	}
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsPrintJobsPage::OnPrintAtCount()
{
	CEventBoxPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		if (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATCOUNT))
		{
			Spinbox_SetPos(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTCOUNT), EVENTBOXSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTCOPIES);
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() | EVENTBOX_PRINT_ATCOUNT);
			pJobInfo->SetPrintAtCount(EVENTBOXSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTCOPIES);
		}
		else  pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~EVENTBOX_PRINT_ATCOUNT);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTCOUNT)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATCOUNT));
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATCOUNT_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATCOUNT));
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
	}
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTCOUNT)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsPrintJobsPage::OnSelchangeRepetitionType()
{
	Spinbox_SetRange(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), (GetJobRepetitionType() == EVENTBOXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY) ? (EVENTBOXSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES + 1) : EVENTBOXSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES, EVENTBOXSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES);
	SetJobRepetitionInfo();
}

void CEventBoxSettingsPrintJobsPage::OnRepeatByTime()
{
	CEventBoxPrintJobInfo  *pJobInfo;

	for (CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME, !IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)); IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME); )
	{
		Spinbox_SetPos(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME), EVENTBOXSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL);
		break;
	}
	for (; (pJobInfo = FindJobInfo()); )
	{
		if (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME))
		{
			pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | EVENTBOX_PRINT_REPEATBYINTERVAL) & ~(EVENTBOX_PRINT_REPEATSTOPBYCOUNT | EVENTBOX_PRINT_REPEATSTOPBYTIME));
			pJobInfo->SetPrintAtTime(Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), SECONDSPERMINUTE*EVENTBOXSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL);
			GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
			break;
		}
		pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~(EVENTBOX_PRINT_REPEATBYINTERVAL | EVENTBOX_PRINT_REPEATSTOPBYCOUNT | EVENTBOX_PRINT_REPEATSTOPBYTIME));
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
		break;
	}
	CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, FALSE);
	CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsPrintJobsPage::OnRepetitionStopByCopies()
{
	CEventBoxPrintJobInfo  *pJobInfo;

	for (CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, !IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)), GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)), GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)); IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES); )
	{
		Spinbox_SetPos(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), EVENTBOXSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTCOPIES);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow(FALSE);
		CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, FALSE);
		break;
	}
	for (; (pJobInfo = FindJobInfo()); )
	{
		if (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES))
		{
			if (GetJobRepetitionType() == EVENTBOXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY)
			{
				pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | EVENTBOX_PRINT_REPEATSTOPBYCOUNT) & ~EVENTBOX_PRINT_REPEATSTOPBYTIME);
				pJobInfo->SetPrintAtTime(Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)), EVENTBOXSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTCOPIES);
			}
			if (GetJobRepetitionType() == EVENTBOXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY)
			{
				pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | EVENTBOX_PRINT_DAILYREPEATSTOPBYCOUNT) & ~EVENTBOX_PRINT_DAILYREPEATSTOPBYTIME);
				pJobInfo->SetPrintAtDailyTime(Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)).GetTime() % SECONDSPERDAY, EVENTBOXSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTCOPIES);
			}
			GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
			break;
		}
		pJobInfo->SetPrintMode((GetJobRepetitionType() == EVENTBOXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY) ? (pJobInfo->GetPrintMode() & ~EVENTBOX_PRINT_REPEATSTOPBYCOUNT) : (pJobInfo->GetPrintMode() & ~EVENTBOX_PRINT_DAILYREPEATSTOPBYCOUNT));
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
		break;
	}
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsPrintJobsPage::OnRepetitionStopByTime()
{
	CTimeKey  tStopTime;
	CEventBoxPrintJobInfo  *pJobInfo;

	for (CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, !IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)), GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)); IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME); )
	{
		for (CheckDlgButton(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, FALSE); GetJobRepetitionType() == EVENTBOXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY; )
		{
			Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)).GetTime() + SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME))));
			break;
		}
		if (GetJobRepetitionType() == EVENTBOXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY) Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)).GetTime() + CTimeSpan(1, 0, 0, 0).GetTotalSeconds()));
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow(FALSE);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow(FALSE);
		break;
	}
	for (; (pJobInfo = FindJobInfo()); )
	{
		if (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME))
		{
			if (GetJobRepetitionType() == EVENTBOXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY)
			{
				pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | EVENTBOX_PRINT_REPEATSTOPBYTIME) & ~EVENTBOX_PRINT_REPEATSTOPBYCOUNT);
				pJobInfo->SetPrintAtTime(Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)), tStopTime);
			}
			if (GetJobRepetitionType() == EVENTBOXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY)
			{
				pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | EVENTBOX_PRINT_DAILYREPEATSTOPBYTIME) & ~EVENTBOX_PRINT_DAILYREPEATSTOPBYCOUNT);
				pJobInfo->SetPrintAtDailyTime(Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)).GetTime() % SECONDSPERDAY, tStopTime);
			}
			GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
			break;
		}
		pJobInfo->SetPrintMode((GetJobRepetitionType() == EVENTBOXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY) ? (pJobInfo->GetPrintMode() & ~EVENTBOX_PRINT_REPEATSTOPBYTIME) : (pJobInfo->GetPrintMode() & ~EVENTBOX_PRINT_DAILYREPEATSTOPBYTIME));
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
		break;
	}
	GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsPrintJobsPage::OnSpinchangePrintTime()
{
	UINT  nStopCount;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeKey  tPrintTime;
	CTimeKey  tPrintStopTime;
	CTimeSpan  tPrintInterval;
	CEventBoxPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)); pJobInfo->GetPrintAtTime(tPrintTime); )
		{
			pJobInfo->SetPrintAtTime(tTime);
			break;
		}
		if (pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval)) pJobInfo->SetPrintAtTime(tTime, tPrintInterval);
		if (pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, nStopCount)) pJobInfo->SetPrintAtTime(tTime, tPrintInterval, nStopCount);
		if (pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, tPrintStopTime)) pJobInfo->SetPrintAtTime(tTime, tPrintInterval, (tTime + tPrintInterval.GetTotalSeconds() > tPrintStopTime.GetTime()) ? (tTime.GetTime() + tPrintInterval.GetTotalSeconds()) : tPrintStopTime);
		Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (GetJobRepetitionType() == EVENTBOXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)) ? ((tTime + tPrintInterval.GetTotalSeconds() > tPrintStopTime.GetTime()) ? (tTime.GetTime() + tPrintInterval.GetTotalSeconds()) : tPrintStopTime.GetTime()) : tStopTime);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsPrintJobsPage::OnSpinchangePrintDailyTime()
{
	UINT  nStopCount;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeKey  tPrintStopTime;
	CTimeSpan  tPrintTime;
	CEventBoxPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)), tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)); pJobInfo->GetPrintAtDailyTime(tPrintTime); )
		{
			pJobInfo->SetPrintAtDailyTime(tTime.GetTime() % SECONDSPERDAY);
			break;
		}
		if (pJobInfo->GetPrintAtDailyTime(tPrintTime, nStopCount)) pJobInfo->SetPrintAtDailyTime(tTime.GetTime() % SECONDSPERDAY, nStopCount);
		if (pJobInfo->GetPrintAtDailyTime(tPrintTime, tPrintStopTime)) pJobInfo->SetPrintAtDailyTime(tTime.GetTime() % SECONDSPERDAY, (SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + tTime.GetTime() % SECONDSPERDAY > tPrintStopTime.GetTime()) ? CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY + 1) + tTime.GetTime() % SECONDSPERDAY) : tPrintStopTime);
		Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (GetJobRepetitionType() == EVENTBOXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)) ? ((SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + tTime.GetTime() % SECONDSPERDAY > tPrintStopTime.GetTime()) ? CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY + 1) + tTime.GetTime() % SECONDSPERDAY) : tPrintStopTime) : tStopTime);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsPrintJobsPage::OnSpinchangePrintCount()
{
	CEventBoxPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		if (IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATCOUNT))
		{
			pJobInfo->SetPrintAtCount((UINT)Spinbox_GetPos(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTCOUNT)));
			GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
		}
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsPrintJobsPage::OnSpinchangeRepeatTime()
{
	UINT  nStopCount;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeKey  tPrintTime;
	CTimeKey  tPrintStopTime;
	CTimeSpan  tPrintInterval;
	CEventBoxPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)); pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval); )
		{
			pJobInfo->SetPrintAtTime(tPrintTime, SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)));
			break;
		}
		if (pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, nStopCount)) pJobInfo->SetPrintAtTime(tPrintTime, SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)), nStopCount);
		if (pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, tPrintStopTime)) pJobInfo->SetPrintAtTime(tPrintTime, SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)), (tPrintTime.GetTime() + SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)) > tPrintStopTime.GetTime()) ? CTimeKey(tPrintTime.GetTime() + SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME))) : tPrintStopTime);
		Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (GetJobRepetitionType() == EVENTBOXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  IsDlgButtonChecked(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)) ? ((tPrintTime.GetTime() + SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)) > tPrintStopTime.GetTime()) ? CTimeKey(tPrintTime.GetTime() + SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME))) : tPrintStopTime) : tStopTime);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsPrintJobsPage::OnSpinchangeRepetitionStopCopies()
{
	UINT  nStopCount;
	UINT  nPrintStopCount;
	CTimeKey  tPrintTime;
	CTimeSpan  tPrintInterval;
	CTimeSpan  tPrintDailyTime;
	CEventBoxPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (nStopCount = (UINT)Spinbox_GetPos(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)); GetJobRepetitionType() == EVENTBOXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY && pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, nPrintStopCount); )
		{
			pJobInfo->SetPrintAtTime(tPrintTime, tPrintInterval, nStopCount);
			break;
		}
		if (GetJobRepetitionType() == EVENTBOXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  pJobInfo->GetPrintAtDailyTime(tPrintDailyTime, nPrintStopCount)) pJobInfo->SetPrintAtDailyTime(tPrintDailyTime, nStopCount);
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE) : FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxSettingsPrintJobsPage::OnSpinchangeRepetitionStopTime()
{
	CTimeKey  tTime;
	CTimeKey  tTimeKey;
	CTimeKey  tStopTime;
	CTimeKey  tPrintTime;
	CTimeKey  tPrintStopTime;
	CTimeSpan  tPrintInterval;
	CTimeSpan  tPrintDailyTime;
	CEventBoxPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)); GetJobRepetitionType() == EVENTBOXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY && pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, tPrintStopTime); )
		{
			if (tTime > tStopTime.GetTime() - tPrintInterval.GetTotalSeconds()) Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (tStopTime = tTime.GetTime() + tPrintInterval.GetTotalSeconds()));
			pJobInfo->SetPrintAtTime(tTime, tPrintInterval, tStopTime);
			break;
		}
		if (GetJobRepetitionType() == EVENTBOXSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  pJobInfo->GetPrintAtDailyTime(tPrintDailyTime, tPrintStopTime))
		{
			if (SECONDSPERDAY*(tTimeKey.GetTime() / SECONDSPERDAY) + tPrintDailyTime.GetTotalSeconds() > tStopTime.GetTime()) Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (tStopTime = SECONDSPERDAY*(tTimeKey.GetTime() / SECONDSPERDAY) + tPrintDailyTime.GetTotalSeconds()));
			pJobInfo->SetPrintAtDailyTime(tPrintDailyTime, tStopTime);
		}
		GetDlgItem(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOXSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CEventBoxSettingsTabCtrl

IMPLEMENT_DYNCREATE(CEventBoxSettingsTabCtrl, CTabCtrl)

BEGIN_MESSAGE_MAP(CEventBoxSettingsTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CEventBoxSettingsTabCtrl)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventBoxSettingsTabCtrl message handlers


/////////////////////////////////////////////////////////////////////////////
// CEventBoxSettingsDialog

IMPLEMENT_DYNCREATE(CEventBoxSettingsDialog, CDisplayPropertySheetDialog)

CEventBoxSettingsDialog::CEventBoxSettingsDialog() : CDisplayPropertySheetDialog()
{
	AddPage(&m_pageLayout);
	AddPage(&m_pageFiltering);
	AddPage(&m_pagePrinting);
	AddPage(&m_pagePrintJobs);
}

BOOL CEventBoxSettingsDialog::GetLayoutTitle(UINT &nColumns) CONST
{
	return m_pageLayout.GetTitle(nColumns);
}

BOOL CEventBoxSettingsDialog::GetLayoutTitleFont(LPLOGFONT pTitleFont) CONST
{
	return m_pageLayout.GetTitleFont(pTitleFont);
}

BOOL CEventBoxSettingsDialog::GetLayoutListFont(LPLOGFONT pListFont) CONST
{
	return m_pageLayout.GetListFont(pListFont);
}

BOOL CEventBoxSettingsDialog::UseLayoutAsDefault(BOOL &bDefault) CONST
{
	return m_pageLayout.UseAsDefault(bDefault);
}

BOOL CEventBoxSettingsDialog::IsLayoutModified() CONST
{
	return m_pageLayout.IsModified();
}

BOOL CEventBoxSettingsDialog::GetFilterMode(UINT &nMode) CONST
{
	return m_pageFiltering.GetMode(nMode);
}

BOOL CEventBoxSettingsDialog::GetFilterBehavior(UINT &nCount) CONST
{
	return m_pageFiltering.GetBehavior(nCount);
}
BOOL CEventBoxSettingsDialog::GetFilterBehavior(CStringArray &szTypes, CStringArray &szSubtypes) CONST
{
	return m_pageFiltering.GetBehavior(szTypes, szSubtypes);
}

BOOL CEventBoxSettingsDialog::GetFilterLimitation(UINT &nLimit) CONST
{
	return m_pageFiltering.GetLimitation(nLimit);
}
BOOL CEventBoxSettingsDialog::GetFilterLimitation(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	return m_pageFiltering.GetLimitation(tStartTime, tStopTime);
}

BOOL CEventBoxSettingsDialog::GetFilterColors(CUIntArray &nColors) CONST
{
	return m_pageFiltering.GetColors(nColors);
}

BOOL CEventBoxSettingsDialog::IsFilteringModified() CONST
{
	return m_pageFiltering.IsModified();
}

BOOL CEventBoxSettingsDialog::GetPrintJobs(CEventBoxPrintJobs &pPrintJobs) CONST
{
	return(((GetActivePage()->GetSafeHwnd() != m_pagePrintJobs.GetSafeHwnd() && m_pagePrinting.GetJobs(pPrintJobs)) || (GetActivePage()->GetSafeHwnd() == m_pagePrintJobs.GetSafeHwnd() && m_pagePrintJobs.GetJobs(pPrintJobs))) ? TRUE : FALSE);
}

BOOL CEventBoxSettingsDialog::IsPrintingModified() CONST
{
	return m_pagePrinting.IsModified() || m_pagePrintJobs.IsModified();
}

CEventBoxOpenDialog *CEventBoxSettingsDialog::GetParentDialog() CONST
{
	return((GetParent() != (CWnd *)GetParentDisplay()) ? (CEventBoxOpenDialog *)GetParent() : (CEventBoxOpenDialog *)NULL);
}

CEventBoxWnd *CEventBoxSettingsDialog::GetParentDisplay() CONST
{
	return((CEventBoxWnd *)CDisplayPropertySheetDialog::GetParentDisplay());
}

BEGIN_MESSAGE_MAP(CEventBoxSettingsDialog, CDisplayPropertySheetDialog)
	//{{AFX_MSG_MAP(CEventBoxSettingsDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDHELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventBoxSettingsDialog message handlers

BOOL CEventBoxSettingsDialog::OnInitDialog()
{
	INT  nPage;
	INT  nPages;
	CHourglassCursor  cCursor;

	CDisplayPropertySheetDialog::OnInitDialog();
	SetTitle(STRING(IDS_EVENTBOXSETTINGSDIALOG_TITLE));
	for (nPage = 0, nPages = GetPageCount(), m_wndTabCtrl.SubclassWindow(GetTabControl()->GetSafeHwnd()); nPage < nPages; nPage++)
	{
		SetActivePage((nPage + 1) % nPages);
		continue;
	}
	m_wndTabCtrl.SetFocus();
	return FALSE;
}

BOOL CEventBoxSettingsDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	CRect  rTab;
	CEventBoxPrintJobs  pPrintJobs;
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

BOOL CEventBoxSettingsDialog::OnDataExchange(HWND hPage, CONST CEventBoxPrintJobs &pJobs)
{
	return(((hPage == m_pagePrinting.GetSafeHwnd() && m_pagePrintJobs.OnDataExchange(pJobs)) || (hPage == m_pagePrintJobs.GetSafeHwnd() && m_pagePrinting.OnDataExchange(pJobs))) ? TRUE : FALSE);
}

void CEventBoxSettingsDialog::OnOK()
{
	CHourglassCursor  cCursor;

	ReportEvent(((!GetParentDialog() && !GetParentDisplay()->OnCloseSettingsDialog(IDOK)) || (GetParentDialog() && !GetParentDialog()->OnCloseSettingsDialog(IDOK))) ? SYSTEM_WARNING_EVENTBOX_SETUP_FAILURE : SYSTEM_NOERROR);
	CDisplayPropertySheetDialog::OnOK();
}

void CEventBoxSettingsDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	if (!GetParentDialog()) GetParentDisplay()->OnCloseSettingsDialog(IDCANCEL);
	else  GetParentDialog()->OnCloseSettingsDialog(IDCANCEL);
	CDisplayPropertySheetDialog::OnCancel();
}

BOOL CEventBoxSettingsDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_EVENTBOXSETTINGSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CEventBoxSettingsDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_EVENTBOXSETTINGSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CEventBoxScheduleInfoDialog dialog

IMPLEMENT_DYNCREATE(CEventBoxScheduleInfoDialog, CDisplayDialog)

CEventBoxScheduleInfoDialog::CEventBoxScheduleInfoDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CEventBoxScheduleInfoDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CEventBoxScheduleInfoDialog::Create(CWnd *pParentWnd, CONST CEventObject *pEvent)
{
	SetScheduleInfo(pEvent);
	return CDisplayDialog::Create(pParentWnd, CEventBoxScheduleInfoDialog::IDD);
}

VOID CEventBoxScheduleInfoDialog::SetScheduleInfo(CONST CEventObject *pEvent)
{
	m_cEvent[0].Copy(pEvent);
	m_cEvent[1].Copy(pEvent);
}

BOOL CEventBoxScheduleInfoDialog::GetScheduleInfo(CEventObject *pEvent) CONST
{
	pEvent->Copy(&m_cEvent[0]);
	return TRUE;
}

CEventBoxScheduleDialog *CEventBoxScheduleInfoDialog::GetParentDialog() CONST
{
	return((CEventBoxScheduleDialog *)CDisplayDialog::GetParent());
}

CEventBoxWnd *CEventBoxScheduleInfoDialog::GetParentDisplay() CONST
{
	return((CEventBoxWnd *)CDisplayDialog::GetParentDisplay());
}

BOOL CEventBoxScheduleInfoDialog::EnumNotifications()
{
	INT  nProfile;
	INT  nProfiles;
	CNotificationProfileInfo  *pProfileInfo;

	SendDlgItemMessage(IDC_EVENTBOX_SCHEDULEINFO_RECIPIENTS_NOTIFICATION, CB_RESETCONTENT);
	SendDlgItemMessage(IDC_EVENTBOX_SCHEDULEINFO_RECIPIENTS_NOTIFICATION, CB_INSERTSTRING, 0, (LPARAM)STRING(IDS_EVENTBOXSCHEDULEDIALOG_NOTIFICATION_NONE));
	for (nProfile = 0, nProfiles = (GetNotificationProfiles(m_pProfiles)) ? (INT)m_pProfiles.GetSize() : 0; nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo = m_pProfiles.GetAt(nProfile))) SendDlgItemMessage(IDC_EVENTBOX_SCHEDULEINFO_RECIPIENTS_NOTIFICATION, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)pProfileInfo->GetName());
		continue;
	}
	return((SendDlgItemMessage(IDC_EVENTBOX_SCHEDULEINFO_RECIPIENTS_NOTIFICATION, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CEventBoxScheduleInfoDialog::EnumRecipients()
{
	INT  nRecipient;
	INT  nRecipients;
	CString  szNotification;
	CStringArray  szRecipients;
	CNotificationProfileInfo  *pProfileInfo;

	SendDlgItemMessage(IDC_EVENTBOX_SCHEDULEINFO_RECIPIENTS_USERS, LB_RESETCONTENT);
	GetDlgItem(IDC_EVENTBOX_SCHEDULEINFO_RECIPIENTS_NOTIFICATION)->GetWindowText(szNotification);
	if ((pProfileInfo = m_pProfiles.GetAt(m_pProfiles.Find(szNotification))) != (CNotificationProfileInfo *)NULL)
	{
		for (nRecipient = 0, nRecipients = pProfileInfo->GetRecipients(szRecipients); nRecipient < nRecipients; nRecipient = nRecipient + 1)
		{
			SendDlgItemMessage(IDC_EVENTBOX_SCHEDULEINFO_RECIPIENTS_USERS, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szRecipients.GetAt(nRecipient));
			continue;
		}
	}
	GetDlgItem(IDC_EVENTBOX_SCHEDULEINFO_RECIPIENTS_USERS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_SCHEDULEINFO_RECIPIENTS_USERS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_EVENTBOX_SCHEDULEINFO_RECIPIENTS_USERS)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_SCHEDULEINFO_RECIPIENTS_USERS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_EVENTBOX_SCHEDULEINFO_RECIPIENTS_USERS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CEventBoxScheduleInfoDialog::IsModified() CONST
{
	UINT  nAlertType[2];
	CString  szNotification[2];

	return((m_cEvent[0].GetComments() != m_cEvent[1].GetComments() || m_cEvent[0].GetProcedure() != m_cEvent[1].GetProcedure() || m_cEvent[0].GetNotification(nAlertType[0], szNotification[0]) != m_cEvent[1].GetNotification(nAlertType[1], szNotification[1]) || nAlertType[0] != nAlertType[1] || szNotification[0] != szNotification[1]) ? TRUE : FALSE);
}

void CEventBoxScheduleInfoDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEventBoxScheduleInfoDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CEventBoxScheduleInfoDialog::PostNcDestroy()
{
	m_pProfiles.RemoveAll();
	CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CEventBoxScheduleInfoDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CEventBoxScheduleInfoDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_EVENTBOX_SCHEDULEINFO_AUTOMATION_PROCEDURE_BROWSE, OnBrowseProcedure)
	ON_BN_CLICKED(IDC_EVENTBOX_SCHEDULEINFO_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_EVENTBOX_SCHEDULEINFO_RECIPIENTS_NOTIFICATION, OnSelchangeNotification)
	ON_EN_CHANGE(IDC_EVENTBOX_SCHEDULEINFO_COMMENTS, OnEditchangeComments)
	ON_EN_CHANGE(IDC_EVENTBOX_SCHEDULEINFO_AUTOMATION_PROCEDURE, OnEditchangeProcedure)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventBoxScheduleInfoDialog message handlers

BOOL CEventBoxScheduleInfoDialog::OnInitDialog()
{
	INT  nIndex;
	UINT  nAlertType;
	CString  szNotification;
	CHourglassCursor  cCursor;

	for (CDisplayDialog::OnInitDialog(); EnumNotifications(); )
	{
		SendDlgItemMessage(IDC_EVENTBOX_SCHEDULEINFO_RECIPIENTS_NOTIFICATION, CB_SETCURSEL, ((nIndex = (m_cEvent[0].GetNotification(nAlertType, szNotification)) ? (INT)SendDlgItemMessage(IDC_EVENTBOX_SCHEDULEINFO_RECIPIENTS_NOTIFICATION, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szNotification) : -1) < 0) ? SendDlgItemMessage(IDC_EVENTBOX_SCHEDULEINFO_RECIPIENTS_NOTIFICATION, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_EVENTBOXSCHEDULEDIALOG_NOTIFICATION_NONE)) : nIndex);
		SendDlgItemMessage(IDC_EVENTBOX_SCHEDULEINFO_RECIPIENTS_USERS, LB_SETCURSEL, (EnumRecipients()) ? 0 : -1);
		GetDlgItem(IDC_EVENTBOX_SCHEDULEINFO_CATEGORY)->SetWindowText(STRING(MINLOCALEVENTCATEGORY + m_cEvent[0].GetCategory() - 1));
		GetDlgItem(IDC_EVENTBOX_SCHEDULEINFO_TYPE)->SetWindowText(m_cEvent[0].GetType());
		GetDlgItem(IDC_EVENTBOX_SCHEDULEINFO_COMMENTS)->SetWindowText(m_cEvent[0].GetComments());
		GetDlgItem(IDC_EVENTBOX_SCHEDULEINFO_AUTOMATION_PROCEDURE)->SetWindowText(m_cEvent[0].GetProcedure());
		GetDlgItem(IDC_EVENTBOX_SCHEDULEINFO_DETAILS)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SCHEDULEINFO_CATEGORY_STATIC)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SCHEDULEINFO_CATEGORY)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SCHEDULEINFO_TYPE_STATIC)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SCHEDULEINFO_TYPE)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SCHEDULEINFO_COMMENTS_STATIC)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SCHEDULEINFO_COMMENTS)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SCHEDULEINFO_RECIPIENTS)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_SCHEDULEINFO_RECIPIENTS_NOTIFICATION, CB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_EVENTBOX_SCHEDULEINFO_RECIPIENTS_NOTIFICATION_STATIC)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_SCHEDULEINFO_RECIPIENTS_NOTIFICATION, CB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_EVENTBOX_SCHEDULEINFO_RECIPIENTS_NOTIFICATION)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_SCHEDULEINFO_RECIPIENTS_NOTIFICATION, CB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_EVENTBOX_SCHEDULEINFO_RECIPIENTS_USERS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_SCHEDULEINFO_RECIPIENTS_NOTIFICATION, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_EVENTBOX_SCHEDULEINFO_RECIPIENTS_USERS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_EVENTBOX_SCHEDULEINFO_RECIPIENTS_USERS)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_SCHEDULEINFO_RECIPIENTS_NOTIFICATION, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_EVENTBOX_SCHEDULEINFO_RECIPIENTS_USERS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_EVENTBOX_SCHEDULEINFO_AUTOMATION)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SCHEDULEINFO_AUTOMATION_PROCEDURE_STATIC)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SCHEDULEINFO_AUTOMATION_PROCEDURE)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SCHEDULEINFO_AUTOMATION_PROCEDURE_BROWSE)->EnableWindow();
		SendDlgItemMessage(IDC_EVENTBOX_SCHEDULEINFO_COMMENTS, EM_SETSEL, 0, (LPARAM)-1);
		GetDlgItem(IDC_EVENTBOX_SCHEDULEINFO_COMMENTS)->SetFocus();
		return FALSE;
	}
	return TRUE;
}

void CEventBoxScheduleInfoDialog::OnBrowseProcedure()
{
	CFileBrowseDialog  cFileBrowseDialog(this, IDC_EVENTBOX_SCHEDULEINFO_AUTOMATION_PROCEDURE, STRING(IDS_FILEBROWSEDIALOG_EXECUTABLEFILEEXTENSION), STRING(IDS_FILEBROWSEDIALOG_EXECUTABLEFILEFILTER));

	if (cFileBrowseDialog.DoModal() == IDOK)
	{
		m_cEvent[0].SetProcedure(cFileBrowseDialog.GetPathName());
		GetDlgItem(IDC_EVENTBOX_SCHEDULEINFO_AUTOMATION_PROCEDURE)->SetWindowText(cFileBrowseDialog.GetPathName());
	}
	SendDlgItemMessage(IDC_EVENTBOX_SCHEDULEINFO_AUTOMATION_PROCEDURE, EM_SETSEL, 0, -1);
	GetDlgItem(IDC_EVENTBOX_SCHEDULEINFO_AUTOMATION_PROCEDURE)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxScheduleInfoDialog::OnEditchangeComments()
{
	CString  szComments;

	GetDlgItem(IDC_EVENTBOX_SCHEDULEINFO_COMMENTS)->GetWindowText(szComments);
	m_cEvent[0].SetComments(szComments);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxScheduleInfoDialog::OnEditchangeProcedure()
{
	CString  szProcedure;

	GetDlgItem(IDC_EVENTBOX_SCHEDULEINFO_AUTOMATION_PROCEDURE)->GetWindowText(szProcedure);
	m_cEvent[0].SetProcedure(szProcedure);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxScheduleInfoDialog::OnSelchangeNotification()
{
	CString  szNotification;
	CStringArray  szRecipients;
	CNotificationProfileInfo  *pProfileInfo;

	GetDlgItem(IDC_EVENTBOX_SCHEDULEINFO_RECIPIENTS_NOTIFICATION)->GetWindowText(szNotification);
	if ((pProfileInfo = m_pProfiles.GetAt(m_pProfiles.Find(szNotification))) && pProfileInfo->GetRecipients(szRecipients) > 0)
	{
		m_cEvent[0].SetNotification(pProfileInfo->GetType(), szNotification);
		m_cEvent[0].SetNotificationRecipients(szRecipients);
	}
	else
	{
		m_cEvent[0].SetNotification(NOTIFICATIONINFO_TYPE_NONE, EMPTYSTRING);
		m_cEvent[0].SetNotificationRecipients(szRecipients);
	}
	EnumRecipients();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxScheduleInfoDialog::OnOK()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnOK();
}

BOOL CEventBoxScheduleInfoDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_EVENTBOXSCHEDULEINFODIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CEventBoxScheduleInfoDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_EVENTBOXSCHEDULEINFODIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CEventBoxScheduleDialog dialog

IMPLEMENT_DYNCREATE(CEventBoxScheduleDialog, CDisplayDialog)

CEventBoxScheduleDialog::CEventBoxScheduleDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CEventBoxScheduleDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CEventBoxScheduleDialog::Create(CWnd *pParentWnd, CONST CEventObject *pEvent)
{
	for (m_cEvent[0].SetCategory(EVENT_CATEGORY_USER), m_cEvent[0].SetType(STRING(IDS_EVENTTYPE_SCHEDULED)), m_cEvent[0].SetUser(GetAccountUserName()), m_cEvent[0].SetMessage(EMPTYSTRING), m_cEvent[0].SetComments(EMPTYSTRING), m_cEvent[0].SetProcedure(EMPTYSTRING), m_cEvent[0].SetNotification(NOTIFICATIONINFO_TYPE_NONE, EMPTYSTRING), m_cEvent[0].SetNotificationRecipients(CStringArray()), m_cEvent[0].SetAudition(AUDIO_NO_SOUND), m_cEvent[0].SetAudioInfo(EMPTYSTRING, 0, 0, 0), m_cEvent[0].SetAuditColor(VGA_COLOR_BLACK), m_cEvent[0].SetAuditTime(CTimeKey(CTime::GetCurrentTime().GetTime() + EVENTBOXSCHEDULEDIALOG_DEFAULTINTERVAL)), m_cEvent[0].SetAuditPeriod(0, 0, 0), m_cEvent[1].Copy(&m_cEvent[0]), m_cEvent[0].Acknowledge(FALSE), m_cEvent[1].Acknowledge(FALSE), m_cEvent[0].Show(), m_cEvent[1].Show(); pEvent != (CONST CEventObject *) NULL; )
	{
		SetScheduleInfo(pEvent);
		break;
	}
	return CDisplayDialog::Create(pParentWnd, CEventBoxScheduleDialog::IDD);
}

VOID CEventBoxScheduleDialog::SetScheduleInfo(CONST CEventObject *pEvent)
{
	m_cEvent[0].Copy(pEvent);
	m_cEvent[1].Copy(pEvent);
}

BOOL CEventBoxScheduleDialog::GetScheduleInfo(CEventObject *pEvent) CONST
{
	pEvent->Copy(&m_cEvent[0]);
	return TRUE;
}

CEventBoxWatchDialog *CEventBoxScheduleDialog::GetParentDialog() CONST
{
	return((GetParent() != (CWnd *)GetParentDisplay()) ? (CEventBoxWatchDialog *)GetParent() : (CEventBoxWatchDialog *)NULL);
}

CEventBoxWnd *CEventBoxScheduleDialog::GetParentDisplay() CONST
{
	return((CEventBoxWnd *)CDisplayDialog::GetParentDisplay());
}

BOOL CEventBoxScheduleDialog::EnumCategories()
{
	INT  nCategory;

	for (nCategory = MINLOCALEVENTCATEGORY; nCategory <= MAXLOCALEVENTCATEGORY; nCategory++)
	{
		SendDlgItemMessage(IDC_EVENTBOX_SCHEDULE_CATEGORY, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(nCategory));
		continue;
	}
	return((SendDlgItemMessage(IDC_EVENTBOX_SCHEDULE_CATEGORY, CB_GETCOUNT) == MAXLOCALEVENTCATEGORY - MINLOCALEVENTCATEGORY + 1 && SendDlgItemMessage(IDC_EVENTBOX_SCHEDULE_CATEGORY, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_EVENTBOX_SCHEDULE_CATEGORY, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_EVENTCATEGORY_USER))) >= 0) ? TRUE : FALSE);
}

BOOL CEventBoxScheduleDialog::EnumTypes()
{
	INT  nType;

	for (nType = MINEVENTTYPE; nType <= MAXEVENTTYPE; nType++)
	{
		SendDlgItemMessage(IDC_EVENTBOX_SCHEDULE_TYPE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(nType));
		continue;
	}
	return((SendDlgItemMessage(IDC_EVENTBOX_SCHEDULE_TYPE, CB_GETCOUNT) == MAXEVENTTYPE - MINEVENTTYPE + 1 && SendDlgItemMessage(IDC_EVENTBOX_SCHEDULE_TYPE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_EVENTBOX_SCHEDULE_TYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_EVENTTYPE_SCHEDULED))) >= 0) ? TRUE : FALSE);
}

BOOL CEventBoxScheduleDialog::EnumAuditions()
{
	INT  nAudition;
	INT  nAuditions;
	CStringArray  szAuditions;

	SendDlgItemMessage(IDC_EVENTBOX_SCHEDULE_AUDITION, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_EVENTBOXSCHEDULEDIALOG_AUDITION_NONE));
	for (nAudition = 0, nAuditions = (EnumAuditionProfiles(szAuditions)) ? (INT)szAuditions.GetSize() : -1; nAudition < nAuditions; nAudition++)
	{
		if (SendDlgItemMessage(IDC_EVENTBOX_SCHEDULE_AUDITION, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szAuditions.GetAt(nAudition)) == CB_ERR)
		{
			SendDlgItemMessage(IDC_EVENTBOX_SCHEDULE_AUDITION, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szAuditions.GetAt(nAudition));
			continue;
		}
	}
	return((SendDlgItemMessage(IDC_EVENTBOX_SCHEDULE_AUDITION, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_EVENTBOXSCHEDULEDIALOG_AUDITION_NONE)) >= 0) ? ((SendDlgItemMessage(IDC_EVENTBOX_SCHEDULE_AUDITION, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_EVENTBOX_SCHEDULE_AUDITION, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_PROFILE_DEFAULTAUDITIONNAME))) >= 0) ? TRUE : ((SendDlgItemMessage(IDC_EVENTBOX_SCHEDULE_AUDITION, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_EVENTBOX_SCHEDULE_AUDITION, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_EVENTBOXSCHEDULEDIALOG_AUDITION_NONE))) >= 0) ? TRUE : FALSE)) : FALSE);
}

CString CEventBoxScheduleDialog::FindAudition(CONST CEventObject *pEvent) CONST
{
	INT  nProfile;
	INT  nProfiles;
	WORD  wVoiceAge[2];
	WORD  wVoiceGender[2];
	DWORD  dwPitch[2];
	DWORD  dwVolume[2];
	DWORD  dwPlayback[2];
	CString  szAudition;
	CString  szAdapter[2];
	CString  szVoiceSpeaker[2];
	CAuditionProfiles  pAuditionProfiles;
	CAuditionProfileInfo  *pAuditionProfileInfo;

	for (nProfile = 0, nProfiles = (GetAuditionProfiles(pAuditionProfiles)) ? (INT)pAuditionProfiles.GetSize() : -1, szAudition = STRING(IDS_EVENTBOXSCHEDULEDIALOG_AUDITION_NONE), m_cEvent[0].GetAudioInfo(szAdapter[0], dwVolume[0], dwPitch[0], dwPlayback[0]), m_cEvent[0].GetAuditVoice(szVoiceSpeaker[0], wVoiceGender[0], wVoiceAge[0]); nProfile < nProfiles; nProfile++)
	{
		if ((pAuditionProfileInfo = pAuditionProfiles.GetAt(nProfile)) != (CAuditionProfileInfo *)NULL)
		{
			pAuditionProfileInfo->GetAdapterInfo(szAdapter[1], dwVolume[1], dwPitch[1], dwPlayback[1]);
			pAuditionProfileInfo->GetVoiceSound(szVoiceSpeaker[1], wVoiceGender[1], wVoiceAge[1]);
			if (m_cEvent[0].GetAudition() == pAuditionProfileInfo->GetAudition() && szAdapter[0] == szAdapter[1] && dwVolume[0] == dwVolume[1] && dwPitch[0] == dwPitch[1] && dwPlayback[0] == dwPlayback[1] && (((m_cEvent[0].GetAudition() & AUDIO_BEEP_SOUND) != AUDIO_BEEP_SOUND || m_cEvent[0].GetAuditBeep() == pAuditionProfileInfo->GetBeepSound()) && ((m_cEvent[0].GetAudition() & AUDIO_WAVE_SOUND) != AUDIO_WAVE_SOUND || m_cEvent[0].GetAuditWave() == pAuditionProfileInfo->GetWaveSound()) && ((m_cEvent[0].GetAudition() & AUDIO_VOICE_SOUND) != AUDIO_VOICE_SOUND || (szVoiceSpeaker[0] == szVoiceSpeaker[1] && wVoiceGender[0] == wVoiceGender[1] && wVoiceAge[0] == wVoiceAge[1]))))
			{
				szAudition = pAuditionProfileInfo->GetName();
				break;
			}
		}
	}
	return((nProfile < nProfiles) ? (LPCTSTR)szAudition : STRING(IDS_EVENTBOXSCHEDULEDIALOG_AUDITION_NONE));
}

BOOL CEventBoxScheduleDialog::IsModified() CONST
{
	return((!m_cEvent[0].Compare(&m_cEvent[1]) || m_cEvent[0].IsAcknowledged() != m_cEvent[1].IsAcknowledged()) ? TRUE : FALSE);
}

BOOL CEventBoxScheduleDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_EVENTBOX_SCHEDULE_TYPE)->GetWindowTextLength() > 0 && GetDlgItem(IDC_EVENTBOX_SCHEDULE_MESSAGE)->GetWindowTextLength() > 0) ? (!bModified || IsModified()) : FALSE);
}

void CEventBoxScheduleDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEventBoxScheduleDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEventBoxScheduleDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CEventBoxScheduleDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEAT, OnRepeat)
	ON_BN_CLICKED(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP, OnRepeatStop)
	ON_BN_CLICKED(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYTIME, OnRepeatStopByTime)
	ON_BN_CLICKED(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYCYCLES, OnRepeatStopByCycles)
	ON_BN_CLICKED(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_AUTOACKNOWLEDGE, OnAutoAcknowledge)
	ON_BN_CLICKED(IDC_EVENTBOX_SCHEDULE_MORE, OnMore)
	ON_BN_CLICKED(IDC_EVENTBOX_SCHEDULE_HELP, OnHelp)
	ON_CBN_EDITCHANGE(IDC_EVENTBOX_SCHEDULE_TYPE, OnEditchangeType)
	ON_CBN_SELCHANGE(IDC_EVENTBOX_SCHEDULE_CATEGORY, OnSelchangeCategory)
	ON_CBN_SELCHANGE(IDC_EVENTBOX_SCHEDULE_TYPE, OnSelchangeType)
	ON_CBN_SELCHANGE(IDC_EVENTBOX_SCHEDULE_AUDITION, OnSelchangeAudition)
	ON_CBN_SELCHANGE(IDC_EVENTBOX_SCHEDULE_COLOR, OnSelchangeColor)
	ON_EN_CHANGE(IDC_EVENTBOX_SCHEDULE_MESSAGE, OnEditchangeMessage)
	ON_CONTROL(SBXN_CHANGE, IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATINTERVAL, OnSpinchangeRepeatInterval)
	ON_CONTROL(SBXN_CHANGE, IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_CYCLES, OnSpinchangeRepeatStopCycles)
	ON_CONTROL(TSBXN_CHANGE, IDC_EVENTBOX_SCHEDULE_OCCURRENCE_TIME, OnSpinchangeTime)
	ON_CONTROL(TSBXN_CHANGE, IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_TIME, OnSpinchangeRepeatStopTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventBoxScheduleDialog message handlers

BOOL CEventBoxScheduleDialog::OnInitDialog()
{
	UINT  nAuditCycles;
	CTimeKey  tAuditStopTime;
	CTimeSpan  tAuditInterval;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	if (EnumCategories() && EnumTypes() && EnumAuditions())
	{
		CheckDlgButton(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEAT, (m_cEvent[0].GetAuditPeriod(tAuditInterval, tAuditStopTime, nAuditCycles)) ? TRUE : FALSE);
		CheckDlgButton(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP, (tAuditInterval > 0 && tAuditStopTime > 0) ? TRUE : FALSE);
		CheckDlgButton(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYTIME, (tAuditInterval > 0 && tAuditStopTime > 0 && !nAuditCycles) ? TRUE : FALSE);
		CheckDlgButton(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYCYCLES, (tAuditInterval > 0 && tAuditStopTime > 0 && nAuditCycles > 0) ? TRUE : FALSE);
		CheckDlgButton(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_AUTOACKNOWLEDGE, m_cEvent[0].IsAcknowledged());
		Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_TIME), m_cEvent[0].GetAuditTime());
		Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_TIME), (tAuditStopTime > 0) ? tAuditStopTime : CTime::GetCurrentTime().GetTime());
		Spinbox_SetRange(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATINTERVAL), EVENTBOXSCHEDULEDIALOG_MINIMUMINTERVAL, EVENTBOXSCHEDULEDIALOG_MAXIMUMINTERVAL);
		Spinbox_SetRange(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_CYCLES), EVENTBOXSCHEDULEDIALOG_MINIMUMCYCLES, EVENTBOXSCHEDULEDIALOG_MAXIMUMCYCLES);
		Spinbox_SetPos(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATINTERVAL), tAuditInterval.GetTotalSeconds());
		Spinbox_SetPos(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_CYCLES), nAuditCycles);
		SendDlgItemMessage(IDC_EVENTBOX_SCHEDULE_CATEGORY, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_EVENTBOX_SCHEDULE_CATEGORY, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(min((UINT)MINLOCALEVENTCATEGORY + m_cEvent[0].GetCategory() - 1, (UINT)MAXLOCALEVENTCATEGORY))));
		SendDlgItemMessage(IDC_EVENTBOX_SCHEDULE_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_cEvent[0].GetAuditColor());
		SendDlgItemMessage(IDC_EVENTBOX_SCHEDULE_AUDITION, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_EVENTBOX_SCHEDULE_AUDITION, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)FindAudition(&m_cEvent[0])));
		GetDlgItem(IDC_EVENTBOX_SCHEDULE_TYPE)->SetWindowText(m_cEvent[0].GetType());
		GetDlgItem(IDC_EVENTBOX_SCHEDULE_MESSAGE)->SetWindowText(m_cEvent[0].GetMessage());
		GetDlgItem(IDC_EVENTBOX_SCHEDULE_DETAILS)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SCHEDULE_MESSAGE_STATIC)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SCHEDULE_MESSAGE)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SCHEDULE_CHARACTERISTICS)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SCHEDULE_CATEGORY_STATIC)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SCHEDULE_CATEGORY)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SCHEDULE_TYPE_STATIC)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SCHEDULE_TYPE)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SCHEDULE_AUDITION_STATIC)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SCHEDULE_AUDITION)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SCHEDULE_COLOR_STATIC)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SCHEDULE_COLOR)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_TIME_STATIC)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_TIME)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEAT)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATINTERVAL)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEAT));
		GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATINTERVAL_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEAT));
		GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEAT));
		GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYTIME)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP));
		GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYCYCLES)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP));
		GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_TIME)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYTIME));
		GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_CYCLES)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYCYCLES));
		GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_CYCLES_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYCYCLES));
		GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_AUTOACKNOWLEDGE)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SCHEDULE_MORE)->EnableWindow();
		SendDlgItemMessage(IDC_EVENTBOX_SCHEDULE_MESSAGE, EM_SETSEL, 0, (LPARAM)-1);
		GetDlgItem(IDC_EVENTBOX_SCHEDULE_MESSAGE)->SetFocus();
		return FALSE;
	}
	return TRUE;
}

void CEventBoxScheduleDialog::OnRepeat()
{
	CheckDlgButton(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP, FALSE);
	CheckDlgButton(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYTIME, FALSE);
	CheckDlgButton(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYCYCLES, FALSE);
	Spinbox_SetPos(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATINTERVAL), EVENTBOXSCHEDULEDIALOG_DEFAULTINTERVAL);
	m_cEvent[0].SetAuditPeriod((IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEAT)) ? Spinbox_GetPos(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATINTERVAL)) : CTimeSpan(0), 0, 0);
	GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATINTERVAL_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEAT));
	GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATINTERVAL)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEAT));
	GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEAT));
	GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_TIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYCYCLES)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_CYCLES_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_CYCLES)->EnableWindow(FALSE);
	GetDlgItem((IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEAT)) ? IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATINTERVAL : IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEAT)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxScheduleDialog::OnRepeatStop()
{
	CTimeKey  tTime;

	CheckDlgButton(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYCYCLES, FALSE);
	CheckDlgButton(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYTIME, IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP));
	Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_TIME), (tTime = Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_TIME)).GetTime() + Spinbox_GetPos(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATINTERVAL))));
	m_cEvent[0].SetAuditPeriod(Spinbox_GetPos(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATINTERVAL)), (IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYTIME)) ? tTime : 0, 0);
	GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYTIME)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP));
	GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYCYCLES)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP));
	GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_TIME)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP));
	GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_CYCLES_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_CYCLES)->EnableWindow(FALSE);
	GetDlgItem((IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYTIME)) ? IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_TIME : IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxScheduleDialog::OnRepeatStopByTime()
{
	CTimeKey  tTime;

	Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_TIME), (tTime = Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_TIME)).GetTime() + Spinbox_GetPos(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATINTERVAL))));
	Spinbox_SetPos(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_CYCLES), EVENTBOXSCHEDULEDIALOG_DEFAULTCYCLES);
	m_cEvent[0].SetAuditPeriod(Spinbox_GetPos(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATINTERVAL)), (IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYTIME)) ? tTime : 0, 0);
	GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_TIME)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYTIME));
	GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_CYCLES_STATIC)->EnableWindow(!IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYTIME));
	GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_CYCLES)->EnableWindow(!IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYTIME));
	GetDlgItem((IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYTIME)) ? IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_TIME : IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxScheduleDialog::OnRepeatStopByCycles()
{
	Spinbox_SetPos(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_CYCLES), EVENTBOXSCHEDULEDIALOG_DEFAULTCYCLES);
	m_cEvent[0].SetAuditPeriod(Spinbox_GetPos(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATINTERVAL)), (IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYCYCLES)) ? CTimeKey(Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_TIME)).GetTime() + Spinbox_GetPos(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_CYCLES))*Spinbox_GetPos(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATINTERVAL))) : CTimeKey(0), (IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYCYCLES)) ? (UINT)Spinbox_GetPos(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_CYCLES)) : 0);
	GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_TIME)->EnableWindow(!IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYCYCLES));
	GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_CYCLES_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYCYCLES));
	GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_CYCLES)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYCYCLES));
	GetDlgItem((IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYCYCLES)) ? IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_CYCLES : IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYCYCLES)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxScheduleDialog::OnEditchangeMessage()
{
	CString  szMessage;

	GetDlgItem(IDC_EVENTBOX_SCHEDULE_MESSAGE)->GetWindowText(szMessage);
	m_cEvent[0].SetMessage(szMessage);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxScheduleDialog::OnEditchangeType()
{
	CString  szType;

	GetDlgItem(IDC_EVENTBOX_SCHEDULE_TYPE)->GetWindowText(szType);
	m_cEvent[0].SetType(szType);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxScheduleDialog::OnSelchangeCategory()
{
	INT  nIndex;

	if ((nIndex = (INT)SendDlgItemMessage(IDC_EVENTBOX_SCHEDULE_CATEGORY, CB_GETCURSEL)) >= 0) m_cEvent[0].SetCategory(FIRSTEVENTCATEGORY << nIndex);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxScheduleDialog::OnSelchangeType()
{
	INT  nIndex;

	if ((nIndex = (INT)SendDlgItemMessage(IDC_EVENTBOX_SCHEDULE_TYPE, CB_GETCURSEL)) >= 0) m_cEvent[0].SetType(Combobox_GetText(GetDlgItem(IDC_EVENTBOX_SCHEDULE_TYPE), nIndex));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxScheduleDialog::OnSelchangeColor()
{
	m_cEvent[0].SetAuditColor((COLORREF)SendDlgItemMessage(IDC_EVENTBOX_SCHEDULE_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_EVENTBOX_SCHEDULE_COLOR, CB_GETCURSEL)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxScheduleDialog::OnSelchangeAudition()
{
	INT  nProfile;
	INT  nProfiles;
	INT  nAudition;
	WORD  wVoiceAge;
	WORD  wVoiceGender;
	DWORD  dwPitch;
	DWORD  dwVolume;
	DWORD  dwPlayback;
	CString  szAdapter;
	CString  szAudition;
	CString  szVoiceSpeaker;
	CAuditionProfiles  pAuditionProfiles;
	CAuditionProfileInfo  *pAuditionProfileInfo;

	GetDlgItem(IDC_EVENTBOX_SCHEDULE_AUDITION)->GetWindowText(szAudition);
	for (nProfile = 0, nProfiles = (GetAuditionProfiles(pAuditionProfiles)) ? (INT)pAuditionProfiles.GetSize() : -1; nProfile < nProfiles; nProfile++)
	{
		if ((pAuditionProfileInfo = pAuditionProfiles.GetAt(nProfile)))
		{
			if (pAuditionProfileInfo->GetName() == szAudition)
			{
				nAudition = pAuditionProfileInfo->GetAudition();
				pAuditionProfileInfo->GetAdapterInfo(szAdapter, dwVolume, dwPitch, dwPlayback);
				pAuditionProfileInfo->GetVoiceSound(szVoiceSpeaker, wVoiceGender, wVoiceAge);
				m_cEvent[0].Acknowledge(FALSE);
				m_cEvent[0].SetAudition(nAudition);
				m_cEvent[0].SetAudioInfo(szAdapter, dwVolume, dwPitch, dwPlayback);
				if (nAudition & AUDIO_BEEP_SOUND) m_cEvent[0].SetAuditBeep(pAuditionProfileInfo->GetBeepSound());
				if (nAudition & AUDIO_WAVE_SOUND) m_cEvent[0].SetAuditWave(pAuditionProfileInfo->GetWaveSound());
				if (nAudition & AUDIO_VOICE_SOUND) m_cEvent[0].SetAuditVoice(szVoiceSpeaker, wVoiceGender, wVoiceAge);
				CheckDlgButton(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_AUTOACKNOWLEDGE, FALSE);
				break;
			}
		}
	}
	for (; szAudition == STRING(IDS_EVENTBOXSCHEDULEDIALOG_AUDITION_NONE); )
	{
		m_cEvent[0].SetAudition(AUDIO_NO_SOUND);
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxScheduleDialog::OnSpinchangeTime()
{
	CTimeKey  tTime[2];

	for (tTime[0] = Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_TIME)), tTime[1] = Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_TIME)); IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEAT) && IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYTIME); )
	{
		Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_TIME), (tTime[0] + Spinbox_GetPos(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATINTERVAL)) > tTime[1]) ? (tTime[0].GetTime() + Spinbox_GetPos(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATINTERVAL))) : tTime[1]);
		break;
	}
	m_cEvent[0].SetAuditPeriod((IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEAT)) ? Spinbox_GetPos(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATINTERVAL)) : 0, (IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP)) ? ((IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYCYCLES)) ? CTimeKey(tTime[0].GetTime() + Spinbox_GetPos(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_CYCLES))*Spinbox_GetPos(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATINTERVAL))) : tTime[1]) : 0, (IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEAT) && IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYCYCLES)) ? (UINT)Spinbox_GetPos(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_CYCLES)) : 0);
	m_cEvent[0].SetAuditTime(tTime[0]);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxScheduleDialog::OnSpinchangeRepeatInterval()
{
	CTimeKey  tTime[2];

	for (tTime[0] = Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_TIME)), tTime[1] = Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_TIME)); IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEAT) && IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYTIME); )
	{
		Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_TIME), (tTime[0] + Spinbox_GetPos(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATINTERVAL)) > tTime[1]) ? (tTime[0].GetTime() + Spinbox_GetPos(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATINTERVAL))) : tTime[1]);
		break;
	}
	m_cEvent[0].SetAuditPeriod(Spinbox_GetPos(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATINTERVAL)), (IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP)) ? ((IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYCYCLES)) ? CTimeKey(tTime[0].GetTime() + Spinbox_GetPos(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_CYCLES))*Spinbox_GetPos(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATINTERVAL))) : tTime[1]) : 0, (IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEAT) && IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYCYCLES)) ? (UINT)Spinbox_GetPos(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_CYCLES)) : 0);
	m_cEvent[0].SetAuditTime(tTime[0]);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxScheduleDialog::OnSpinchangeRepeatStopTime()
{
	CTimeKey  tTime[2];

	for (tTime[0] = Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_TIME)), tTime[1] = Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_TIME)); IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEAT) && IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_BYTIME); )
	{
		Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_TIME), (tTime[0] > tTime[1].GetTime() - Spinbox_GetPos(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATINTERVAL))) ? (tTime[1].GetTime() - Spinbox_GetPos(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATINTERVAL))) : tTime[0]);
		break;
	}
	m_cEvent[0].SetAuditPeriod(Spinbox_GetPos(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATINTERVAL)), tTime[1], 0);
	m_cEvent[0].SetAuditTime(tTime[0]);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxScheduleDialog::OnSpinchangeRepeatStopCycles()
{
	m_cEvent[0].SetAuditPeriod(Spinbox_GetPos(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATINTERVAL)), CTimeKey(Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_TIME)).GetTime() + Spinbox_GetPos(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_CYCLES))*Spinbox_GetPos(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATINTERVAL))), (UINT)Spinbox_GetPos(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_REPEATSTOP_CYCLES)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxScheduleDialog::OnAutoAcknowledge()
{
	m_cEvent[0].Acknowledge(IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_AUTOACKNOWLEDGE));
	m_cEvent[0].SetAudition((IsDlgButtonChecked(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_AUTOACKNOWLEDGE)) ? AUDIO_NO_SOUND : m_cEvent[0].GetAudition());
	SendDlgItemMessage(IDC_EVENTBOX_SCHEDULE_AUDITION, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_EVENTBOX_SCHEDULE_AUDITION, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_EVENTBOXSCHEDULEDIALOG_AUDITION_NONE)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxScheduleDialog::OnMore()
{
	CEventObject  cEvent;
	CEventBoxScheduleInfoDialog  cScheduleInfoDialog;

	if (cScheduleInfoDialog.Create(this, &m_cEvent[0]) == IDOK  &&  cScheduleInfoDialog.GetScheduleInfo(&cEvent)) m_cEvent[0].Copy(&cEvent);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxScheduleDialog::OnOK()
{
	CHourglassCursor  cCursor;

	if (Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_TIME)).GetTime() <= CTime::GetCurrentTime().GetTime())
	{
		GetDlgItem(IDC_EVENTBOX_SCHEDULE_OCCURRENCE_TIME)->SetFocus();
		CAudioDevice::AlertBySound();
		return;
	}
	if (!GetParentDialog()) GetParentDisplay()->OnCloseScheduleDialog(IDOK);
	CDisplayDialog::OnOK();
}

BOOL CEventBoxScheduleDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_EVENTBOXSCHEDULEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CEventBoxScheduleDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_EVENTBOXSCHEDULEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CEventBoxDetailsDialog dialog

IMPLEMENT_DYNCREATE(CEventBoxDetailsDialog, CDisplayDialog)

CEventBoxDetailsDialog::CEventBoxDetailsDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CEventBoxDetailsDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CEventBoxDetailsDialog::Create(CWnd *pParentWnd, CONST CEventObject *pEvent)
{
	SetInfo(pEvent);
	return CDisplayDialog::Create(pParentWnd, CEventBoxDetailsDialog::IDD);
}

VOID CEventBoxDetailsDialog::SetInfo(CONST CEventObject *pEvent)
{
	m_cEvent[0].Copy(pEvent);
	m_cEvent[1].Copy(pEvent);
}

BOOL CEventBoxDetailsDialog::GetInfo(CEventObject *pEvent) CONST
{
	pEvent->Copy(&m_cEvent[0]);
	return TRUE;
}

CEventBoxWatchDialog *CEventBoxDetailsDialog::GetParentDialog() CONST
{
	return((GetParent() != (CWnd *)GetParentDisplay()) ? (CEventBoxWatchDialog *)GetParent() : (CEventBoxWatchDialog *)NULL);
}

CEventBoxWnd *CEventBoxDetailsDialog::GetParentDisplay() CONST
{
	return((CEventBoxWnd *)CDisplayDialog::GetParentDisplay());
}

BOOL CEventBoxDetailsDialog::CheckPrivilege(UINT nPrivilege) CONST
{
	return((GetParentDisplay()->GetScope() == DISPLAY_SCOPE_GLOBAL) ? CheckAccountPrivilege(nPrivilege) : TRUE);
}

void CEventBoxDetailsDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEventBoxDetailsDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEventBoxDetailsDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CEventBoxDetailsDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_EVENTBOX_ITEM_TEXT_MESSAGE, OnMessageText)
	ON_BN_CLICKED(IDC_EVENTBOX_ITEM_TEXT_COMMENTS, OnCommentsText)
	ON_BN_CLICKED(IDC_EVENTBOX_ITEM_ACKNOWLEDGE, OnAcknowledge)
	ON_BN_CLICKED(IDC_EVENTBOX_ITEM_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventBoxDetailsDialog message handlers

BOOL CEventBoxDetailsDialog::OnInitDialog()
{
	INT  nRecipient;
	INT  nRecipients;
	UINT  nAudition;
	UINT  nAlertType;
	UINT  nAuditCycles;
	CString  szNotification;
	CString  szAuditInterval[2];
	CTimeKey  tAuditStopTime;
	CTimeSpan  tAuditInterval;
	CStringArray  szRecipients;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (m_cEvent[0].GetAuditPeriod(tAuditInterval, tAuditStopTime, nAuditCycles), m_cEvent[0].GetNotification(nAlertType, szNotification), m_cEvent[0].GetNotificationRecipients(szRecipients); TRUE; )
	{
		GetDlgItem(IDC_EVENTBOX_ITEM_OCCURRENCE_REPEATINTERVAL)->GetWindowText(szAuditInterval[0]);
		szAuditInterval[1].Format(szAuditInterval[0], tAuditInterval.GetTotalSeconds());
		break;
	}
	CheckRadioButton(IDC_EVENTBOX_ITEM_TEXT_MESSAGE, IDC_EVENTBOX_ITEM_TEXT_COMMENTS, IDC_EVENTBOX_ITEM_TEXT_MESSAGE);
	GetDlgItem(IDC_EVENTBOX_ITEM_CATEGORY)->SetWindowText(STRING(min((UINT)MINLOCALEVENTCATEGORY + m_cEvent[0].GetCategory() - 1, (UINT)MAXLOCALEVENTCATEGORY)));
	GetDlgItem(IDC_EVENTBOX_ITEM_TYPE)->SetWindowText(m_cEvent[0].GetType());
	GetDlgItem(IDC_EVENTBOX_ITEM_USER)->SetWindowText(m_cEvent[0].GetUser());
	GetDlgItem(IDC_EVENTBOX_ITEM_TEXT)->SetWindowText(m_cEvent[0].GetMessage());
	GetDlgItem(IDC_EVENTBOX_ITEM_AUDITION)->SetWindowText(((nAudition = m_cEvent[0].GetAudition()) == AUDIO_NO_SOUND) ? STRING(IDS_EVENTBOXDETAILSDIALOG_AUDITION_NOSOUND) : ((nAudition == AUDIO_STANDARD_SOUND) ? STRING(IDS_EVENTBOXDETAILSDIALOG_AUDITION_STANDARDSOUND) : ((nAudition == AUDIO_BEEP_SOUND) ? STRING(IDS_EVENTBOXDETAILSDIALOG_AUDITION_BEEPSOUND) : ((nAudition == AUDIO_WAVE_SOUND) ? STRING(IDS_EVENTBOXDETAILSDIALOG_AUDITION_WAVESOUND) : ((nAudition == AUDIO_VOICE_SOUND) ? STRING(IDS_EVENTBOXDETAILSDIALOG_AUDITION_VOICESOUND) : STRING(IDS_EVENTBOXDETAILSDIALOG_AUDITION_NOSOUND))))));
	GetDlgItem(IDC_EVENTBOX_ITEM_OCCURRENCE_TIME)->SetWindowText(m_cEvent[0].GetAuditTime().FormatGmt());
	GetDlgItem(IDC_EVENTBOX_ITEM_OCCURRENCE_REPEATSTOP_TIME_STATIC)->ShowWindow((tAuditInterval.GetTotalSeconds() > 0 && tAuditStopTime > 0) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_EVENTBOX_ITEM_OCCURRENCE_REPEATSTOP_TIME)->ShowWindow((tAuditInterval.GetTotalSeconds() > 0 && tAuditStopTime > 0) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_EVENTBOX_ITEM_OCCURRENCE_REPEAT_STATIC)->ShowWindow((tAuditInterval.GetTotalSeconds() > 0) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_EVENTBOX_ITEM_OCCURRENCE_REPEATINTERVAL)->ShowWindow((tAuditInterval.GetTotalSeconds() > 0) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_EVENTBOX_ITEM_OCCURRENCE_NOREPETITION_STATIC)->ShowWindow((!tAuditInterval.GetTotalSeconds()) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_EVENTBOX_ITEM_OCCURRENCE_REPEATSTOP_TIME)->SetWindowText(tAuditStopTime.FormatGmt());
	GetDlgItem(IDC_EVENTBOX_ITEM_OCCURRENCE_REPEATINTERVAL)->SetWindowText(szAuditInterval[1]);
	GetDlgItem(IDC_EVENTBOX_ITEM_RECIPIENTS_NOTIFICATION)->SetWindowText((!szNotification.IsEmpty()) ? (LPCTSTR)szNotification : STRING(IDS_EVENTBOXDETAILSDIALOG_NOTIFICATION_NONE));
	GetDlgItem(IDC_EVENTBOX_ITEM_RECIPIENTS_ALERT)->SetWindowText((nAlertType != NOTIFICATIONINFO_TYPE_NONE) ? ((nAlertType == NOTIFICATIONINFO_TYPE_EMAIL) ? STRING(IDS_EVENTBOXDETAILSDIALOG_NOTIFICATION_EMAIL) : ((nAlertType == NOTIFICATIONINFO_TYPE_FAX) ? STRING(IDS_EVENTBOXDETAILSDIALOG_NOTIFICATION_FAX) : ((nAlertType == NOTIFICATIONINFO_TYPE_PHONECALL) ? STRING(IDS_EVENTBOXDETAILSDIALOG_NOTIFICATION_PHONECALL) : ((nAlertType == NOTIFICATIONINFO_TYPE_PAGERCALL) ? STRING(IDS_EVENTBOXDETAILSDIALOG_NOTIFICATION_PAGERCALL) : ((nAlertType == NOTIFICATIONINFO_TYPE_FTPMESSAGE) ? STRING(IDS_EVENTBOXDETAILSDIALOG_NOTIFICATION_FTPMESSAGE) : ((nAlertType == NOTIFICATIONINFO_TYPE_PRINTERMESSAGE) ? STRING(IDS_EVENTBOXDETAILSDIALOG_NOTIFICATION_PRINTERMESSAGE) : EMPTYSTRING)))))) : EMPTYSTRING);
	GetDlgItem(IDC_EVENTBOX_ITEM_RECIPIENTS_ALERT_STATIC)->ShowWindow((GetDlgItem(IDC_EVENTBOX_ITEM_RECIPIENTS_ALERT)->GetWindowTextLength() > 0) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_EVENTBOX_ITEM_RECIPIENTS_ALERT)->ShowWindow((GetDlgItem(IDC_EVENTBOX_ITEM_RECIPIENTS_ALERT)->GetWindowTextLength() > 0) ? SW_SHOW : SW_HIDE);
	for (nRecipient = 0, nRecipients = (INT)szRecipients.GetSize(), SendDlgItemMessage(IDC_EVENTBOX_ITEM_RECIPIENTS_LIST, LB_RESETCONTENT); nRecipient < nRecipients; nRecipient++)
	{
		SendDlgItemMessage(IDC_EVENTBOX_ITEM_RECIPIENTS_LIST, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szRecipients.GetAt(nRecipient));
		continue;
	}
	GetDlgItem(IDC_EVENTBOX_ITEM_DETAILS)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_ITEM_TEXT_STATIC)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_ITEM_TEXT_MESSAGE)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_ITEM_TEXT_COMMENTS)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_ITEM_TEXT)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_ITEM_CHARACTERISTICS)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_ITEM_CATEGORY_STATIC)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_ITEM_CATEGORY)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_ITEM_TYPE_STATIC)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_ITEM_TYPE)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_ITEM_USER_STATIC)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_ITEM_USER)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_ITEM_AUDITION_STATIC)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_ITEM_AUDITION)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_ITEM_OCCURRENCE)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_ITEM_OCCURRENCE_TIME_STATIC)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_ITEM_OCCURRENCE_TIME)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_ITEM_OCCURRENCE_REPEATSTOP_TIME_STATIC)->EnableWindow((tAuditInterval.GetTotalSeconds() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_EVENTBOX_ITEM_OCCURRENCE_REPEATSTOP_TIME)->EnableWindow((tAuditInterval.GetTotalSeconds() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_EVENTBOX_ITEM_OCCURRENCE_REPEAT_STATIC)->EnableWindow((tAuditInterval.GetTotalSeconds() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_EVENTBOX_ITEM_OCCURRENCE_REPEATINTERVAL)->EnableWindow((tAuditInterval.GetTotalSeconds() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_EVENTBOX_ITEM_OCCURRENCE_NOREPETITION_STATIC)->EnableWindow((!tAuditInterval.GetTotalSeconds()) ? TRUE : FALSE);
	GetDlgItem(IDC_EVENTBOX_ITEM_RECIPIENTS)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_ITEM_RECIPIENTS_NOTIFICATION_STATIC)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_ITEM_RECIPIENTS_NOTIFICATION)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_ITEM_RECIPIENTS_ALERT_STATIC)->EnableWindow((GetDlgItem(IDC_EVENTBOX_ITEM_RECIPIENTS_ALERT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_EVENTBOX_ITEM_RECIPIENTS_ALERT)->EnableWindow((GetDlgItem(IDC_EVENTBOX_ITEM_RECIPIENTS_ALERT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_EVENTBOX_ITEM_RECIPIENTS_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_ITEM_RECIPIENTS_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_EVENTBOX_ITEM_RECIPIENTS_LIST)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_ITEM_RECIPIENTS_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_EVENTBOX_ITEM_ACKNOWLEDGE)->EnableWindow((!m_cEvent[0].IsAcknowledged()) ? CheckPrivilege(PRIVILEGE_EVENTBOX_ACKNOWLEDGE) : FALSE);
	GetDlgItem(IDC_EVENTBOX_ITEM_ACKNOWLEDGE)->SetFocus();
	return FALSE;
}

void CEventBoxDetailsDialog::OnMessageText()
{
	CString  szMessage;

	GetDlgItem(IDC_EVENTBOX_ITEM_TEXT)->SetWindowText((szMessage = m_cEvent[0].GetMessage()));
	GetDlgItem(IDC_EVENTBOX_ITEM_TEXT)->EnableWindow(!szMessage.IsEmpty());
}

void CEventBoxDetailsDialog::OnCommentsText()
{
	CString  szComments;

	GetDlgItem(IDC_EVENTBOX_ITEM_TEXT)->SetWindowText((szComments = m_cEvent[0].GetComments()));
	GetDlgItem(IDC_EVENTBOX_ITEM_TEXT)->EnableWindow(!szComments.IsEmpty());
}

void CEventBoxDetailsDialog::OnAcknowledge()
{
	CEventObject  *pEvent;
	CHourglassCursor  cCursor;

	if (GetParentDisplay()->Lock())
	{
		if (GetParentDisplay()->GetEventList()->Lock())
		{
			for (m_cEvent[0].Acknowledge(); (pEvent = (!GetParentDialog()) ? GetParentDisplay()->GetEventList()->GetAt(GetParentDisplay()->GetEventList()->Find(&m_cEvent[1])) : (CEventObject *)NULL); )
			{
				GetParentDisplay()->AcknowledgeEvent(pEvent);
				break;
			}
			GetParentDisplay()->GetEventList()->Unlock();
		}
		GetParentDisplay()->Unlock();
	}
	GetDlgItem(IDC_EVENTBOX_ITEM_ACKNOWLEDGE)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->SetFocus();
}

void CEventBoxDetailsDialog::OnOK()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnOK();
}

BOOL CEventBoxDetailsDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_EVENTBOXDETAILSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CEventBoxDetailsDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_EVENTBOXDETAILSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CEventBoxWatchClockThread

IMPLEMENT_DYNCREATE(CEventBoxWatchClockThread, CThread)

BOOL CEventBoxWatchClockThread::Start(CDialog *pDlg, CONST CStringArray &szColumns, CEventList *pEventList)
{
	CFont  *pFont;
	LOGFONT  lfFont;

	if ((pFont = pDlg->GetFont()) && pFont->GetLogFont(&lfFont))
	{
		for (; m_cFont.GetSafeHandle(); )
		{
			m_cFont.DeleteObject();
			break;
		}
		if (m_cFont.CreateFontIndirect(&lfFont))
		{
			m_szColumns.Copy(szColumns);
			m_pEventList = pEventList;
			return CreateThread(pDlg);
		}
	}
	return FALSE;
}

BOOL CEventBoxWatchClockThread::Stop()
{
	return((DestroyThread() >= 0) ? TRUE : FALSE);
}

int CEventBoxWatchClockThread::Run()
{
	INT  nItem;
	INT  nItems;
	CTimeKey  tTime;
	CEventList  cEventList;
	CEventObject  *pEvent[4];
	CDialog  *pDlg = (CDialog *)GetThreadInfo();

	do
	{
		if (m_pEventList->Lock())
		{
			if ((pEvent[0] = new CEventObject))
			{
				if (m_pEventList->Schedule(pEvent[0]))
				{
					for (nItem = m_pEventList->GetScheduleIndex(), nItems = (INT)m_pEventList->GetSize(), cEventList.EnableSound(FALSE), cEventList.RemoveAll(); nItem < nItems; nItem++)
					{
						if ((pEvent[1] = ((pEvent[2] = new CEventObject)) ? m_pEventList->GetAt(nItem) : (CEventObject *)NULL))
						{
							for (pEvent[2]->Copy(pEvent[1]); cEventList.Add(pEvent[2], TRUE) < 0; )
							{
								delete pEvent[2];
								break;
							}
						}
					}
					for (tTime = 0, nItems = 0; (pEvent[3] = m_pEventList->GetAt((nItem = m_pEventList->GetScheduleIndex()))); )
					{
						nItems = (INT)(m_pEventList->GetSize() - nItem);
						tTime = pEvent[3]->GetAuditTime();
						break;
					}
					m_pEventList->Unlock();
					DrawTime(pDlg, tTime, nItems);
					UpdateList(pDlg, &cEventList);
					delete pEvent[0];
					continue;
				}
				for (tTime = 0, nItems = 0; (pEvent[3] = m_pEventList->GetAt((nItem = m_pEventList->GetScheduleIndex()))); )
				{
					nItems = (INT)(m_pEventList->GetSize() - nItem);
					tTime = pEvent[3]->GetAuditTime();
					break;
				}
				m_pEventList->Unlock();
				DrawTime(pDlg, tTime, nItems);
				delete pEvent[0];
				continue;
			}
			m_pEventList->Unlock();
		}
	} while (Wait(EVENTBOXWATCH_UPDATE_INTERVAL) == WAIT_TIMEOUT);
	return 0;
}

VOID CEventBoxWatchClockThread::UpdateList(CDialog *pDlg, CEventList *pEventList)
{
	INT  nPos;
	INT  nItem;
	INT  nItems;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CEventObject  *pEvent;

	for (nItem = 0, nItems = (INT)pEventList->GetSize(); nItem < nItems; nItem++)
	{
		if ((pEvent = (CEventObject *)pEventList->GetAt(nItem)) != (CEventObject *)NULL)
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_EVENTBOXWATCHDIALOG_TIME); )
				{
					szItem = pEvent->GetAuditTime().FormatGmt();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_EVENTBOXWATCHDIALOG_MESSAGE); )
				{
					szItem = ((nPos = (szItem = pEvent->GetMessage()).Find(CR)) >= 0) ? (szItem.Left(nPos) + STRING(IDS_EVENTBOXWATCHDIALOG_ELLIPSES)) : szItem;
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_EVENTBOXWATCHDIALOG_USER); )
				{
					szItem = pEvent->GetUser();
					break;
				}
				if (nItem >= pDlg->SendDlgItemMessage(IDC_EVENTBOX_WATCH_LIST, LVM_GETITEMCOUNT) && !nColumns)
				{
					Listview_InsertText(pDlg->GetDlgItem(IDC_EVENTBOX_WATCH_LIST), nItem, szItem);
					continue;
				}
				Listview_SetText(pDlg->GetDlgItem(IDC_EVENTBOX_WATCH_LIST), nItem, nColumn, szItem);
			}
		}
	}
	for (; pDlg->SendDlgItemMessage(IDC_EVENTBOX_WATCH_LIST, LVM_GETITEMCOUNT) > nItems; )
	{
		if (Listview_DeleteText(pDlg->GetDlgItem(IDC_EVENTBOX_WATCH_LIST), (INT)pDlg->SendDlgItemMessage(IDC_EVENTBOX_WATCH_LIST, LVM_GETITEMCOUNT) - 1)) continue;
		break;
	}
	if (nItems > 0)
	{
		Listview_SetCurText(pDlg->GetDlgItem(IDC_EVENTBOX_WATCH_LIST), 0);
		pDlg->GetDlgItem(IDC_EVENTBOX_WATCH_LIST_STATIC)->EnableWindow();
		pDlg->GetDlgItem(IDC_EVENTBOX_WATCH_LIST)->EnableWindow();
		pDlg->GetDlgItem(IDC_EVENTBOX_WATCH_LIST_DETAILS)->EnableWindow();
		pDlg->GetDlgItem(IDC_EVENTBOX_WATCH_LIST_CHANGE)->EnableWindow(CheckAccountPrivilege(PRIVILEGE_EVENTBOX_SCHEDULE));
		pDlg->GetDlgItem(IDC_EVENTBOX_WATCH_LIST_REMOVE)->EnableWindow(CheckAccountPrivilege(PRIVILEGE_EVENTBOX_SCHEDULE));
		pDlg->GetDlgItem(IDC_EVENTBOX_WATCH_LIST_REMOVEALL)->EnableWindow(CheckAccountPrivilege(PRIVILEGE_EVENTBOX_SCHEDULE));
		return;
	}
	pDlg->GetDlgItem(IDC_EVENTBOX_WATCH_LIST_STATIC)->EnableWindow(FALSE);
	pDlg->GetDlgItem(IDC_EVENTBOX_WATCH_LIST)->EnableWindow(FALSE);
	pDlg->GetDlgItem(IDC_EVENTBOX_WATCH_LIST_DETAILS)->EnableWindow(FALSE);
	pDlg->GetDlgItem(IDC_EVENTBOX_WATCH_LIST_CHANGE)->EnableWindow(FALSE);
	pDlg->GetDlgItem(IDC_EVENTBOX_WATCH_LIST_REMOVE)->EnableWindow(FALSE);
	pDlg->GetDlgItem(IDC_EVENTBOX_WATCH_LIST_REMOVEALL)->EnableWindow(FALSE);
	pDlg->GetDlgItem(IDOK)->EnableWindow(FALSE);
}

VOID CEventBoxWatchClockThread::DrawTime(CDialog *pDlg, CONST CTimeKey &tTime, INT nCount)
{
	CDC  *pDC;
	INT  nOldBkColor;
	CFont  *pOldFont;
	CRect  rCount[2];
	CRect  rClock[2];
	CBrush  cBkBrush;
	CString  szCount;
	CString  szClock;
	CTimeKey  tClock;
	CStringTools  cStringTools;

	if ((pDC = pDlg->GetDC()))
	{
		pDlg->GetDlgItem(IDC_EVENTBOX_WATCH_TIME)->GetWindowRect(rClock[0]);
		pDlg->ScreenToClient(rClock[0]);
		if ((pOldFont = pDC->SelectObject(&m_cFont)))
		{
			if (cBkBrush.CreateSysColorBrush(COLOR_3DFACE))
			{
				nOldBkColor = pDC->SetBkColor(GetSysColor(COLOR_3DFACE));
				pDC->DrawText(tClock.FormatGmt(), (rClock[1] = rClock[0]), DT_CALCRECT | DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_NOPREFIX);
				pDC->DrawText(tClock.FormatGmt(), rClock[1], DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_NOPREFIX);
				pDC->ExcludeClipRect(rClock[1].left, rClock[1].top, rClock[1].right, rClock[1].bottom);
				pDC->FillRect(rClock[0], &cBkBrush);
				pDC->SetBkMode(nOldBkColor);
				cBkBrush.DeleteObject();
			}
			pDC->SelectObject(pOldFont);
		}
		pDlg->ReleaseDC(pDC);
	}
	if ((pDC = pDlg->GetDC()))
	{
		pDlg->GetDlgItem(IDC_EVENTBOX_WATCH_COUNT)->GetWindowRect(rCount[0]);
		pDlg->ScreenToClient(rCount[0]);
		if ((pOldFont = pDC->SelectObject(&m_cFont)))
		{
			if (cBkBrush.CreateSysColorBrush(COLOR_3DFACE))
			{
				szCount = cStringTools.ConvertIntToString(nCount);
				nOldBkColor = pDC->SetBkColor(GetSysColor(COLOR_3DFACE));
				pDC->DrawText(szCount, (rCount[1] = rCount[0]), DT_CALCRECT | DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_NOPREFIX);
				pDC->DrawText(szCount, rCount[1], DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_NOPREFIX);
				pDC->ExcludeClipRect(rCount[1].left, rCount[1].top, rCount[1].right, rCount[1].bottom);
				pDC->FillRect(rCount[0], &cBkBrush);
				pDC->SetBkMode(nOldBkColor);
				cBkBrush.DeleteObject();
			}
			pDC->SelectObject(pOldFont);
		}
		pDlg->ReleaseDC(pDC);
	}
	if (CTime::GetCurrentTime() <= tTime  &&  tTime > 0)
	{
		if ((pDC = (CDC *)pDlg->GetDC()) != (CDC *)NULL)
		{
			pDlg->GetDlgItem(IDC_EVENTBOX_WATCH_REMAININGTIME)->GetWindowRect(rClock[0]);
			pDlg->ScreenToClient(rClock[0]);
			if ((pOldFont = pDC->SelectObject(&m_cFont)))
			{
				if (cBkBrush.CreateSysColorBrush(COLOR_3DFACE))
				{
					nOldBkColor = pDC->SetBkColor(GetSysColor(COLOR_3DFACE));
					pDC->DrawText((szClock = CTimeSpan(tTime.GetTime() - CTime::GetCurrentTime().GetTime()).Format(STRING(IDS_TIMEKEY_SPANFORMAT))), (rClock[1] = rClock[0]), DT_CALCRECT | DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_NOPREFIX);
					pDC->DrawText(szClock, rClock[1], DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_NOPREFIX);
					pDC->ExcludeClipRect(rClock[1].left, rClock[1].top, rClock[1].right, rClock[1].bottom);
					pDC->FillRect(rClock[0], &cBkBrush);
					pDC->SetBkMode(nOldBkColor);
					cBkBrush.DeleteObject();
				}
				pDC->SelectObject(pOldFont);
			}
			pDlg->ReleaseDC(pDC);
		}
		if ((pDC = pDlg->GetDC()))
		{
			pDlg->GetDlgItem(IDC_EVENTBOX_WATCH_NEXTTIME)->GetWindowRect(rClock[0]);
			pDlg->ScreenToClient(rClock[0]);
			if ((pOldFont = pDC->SelectObject(&m_cFont)))
			{
				if (cBkBrush.CreateSysColorBrush(COLOR_3DFACE))
				{
					nOldBkColor = pDC->SetBkColor(GetSysColor(COLOR_3DFACE));
					pDC->DrawText((szClock = tTime.FormatGmt()), (rClock[1] = rClock[0]), DT_CALCRECT | DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_NOPREFIX);
					pDC->DrawText(szClock, rClock[1], DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_NOPREFIX);
					pDC->ExcludeClipRect(rClock[1].left, rClock[1].top, rClock[1].right, rClock[1].bottom);
					pDC->FillRect(rClock[0], &cBkBrush);
					pDC->SetBkMode(nOldBkColor);
					cBkBrush.DeleteObject();
				}
				pDC->SelectObject(pOldFont);
			}
			pDlg->ReleaseDC(pDC);
		}
		pDlg->GetDlgItem(IDC_EVENTBOX_WATCH_REMAININGTIME_STATIC)->EnableWindow();
		pDlg->GetDlgItem(IDC_EVENTBOX_WATCH_NEXTTIME_STATIC)->EnableWindow();
		return;
	}
	if ((pDC = pDlg->GetDC()))
	{
		pDlg->GetDlgItem(IDC_EVENTBOX_WATCH_REMAININGTIME)->GetWindowRect(rClock[0]);
		pDlg->ScreenToClient(rClock[0]);
		if (cBkBrush.CreateSysColorBrush(COLOR_3DFACE))
		{
			pDC->FillRect(rClock[0], &cBkBrush);
			cBkBrush.DeleteObject();
		}
		pDlg->ReleaseDC(pDC);
	}
	if ((pDC = pDlg->GetDC()))
	{
		pDlg->GetDlgItem(IDC_EVENTBOX_WATCH_NEXTTIME)->GetWindowRect(rClock[0]);
		pDlg->ScreenToClient(rClock[0]);
		if (cBkBrush.CreateSysColorBrush(COLOR_3DFACE))
		{
			pDC->FillRect(rClock[0], &cBkBrush);
			cBkBrush.DeleteObject();
		}
		pDlg->ReleaseDC(pDC);
	}
	pDlg->GetDlgItem(IDC_EVENTBOX_WATCH_REMAININGTIME_STATIC)->EnableWindow(FALSE);
	pDlg->GetDlgItem(IDC_EVENTBOX_WATCH_NEXTTIME_STATIC)->EnableWindow(FALSE);
}

BEGIN_MESSAGE_MAP(CEventBoxWatchClockThread, CThread)
	//{{AFX_MSG_MAP(CEventBoxWatchClockThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventBoxWatchClockThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CEventBoxWatchDialog dialog

IMPLEMENT_DYNCREATE(CEventBoxWatchDialog, CDisplayDialog)

CEventBoxWatchDialog::CEventBoxWatchDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CEventBoxWatchDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CEventBoxWatchDialog::Create(CWnd *pParentWnd, CEventList *pEventList)
{
	for (m_pEventList[0] = new CEventList, m_pEventList[1] = new CEventList; m_pEventList[0] != (CEventList *)NULL && m_pEventList[1] != (CEventList *)NULL; )
	{
		SetScheduleInfo(pEventList);
		break;
	}
	return CDisplayDialog::Create(pParentWnd, CEventBoxWatchDialog::IDD);
}

BOOL CEventBoxWatchDialog::SetScheduleInfo(CEventList *pEventList)
{
	INT  nItem;
	INT  nItems;
	INT  nIndex[2];
	CEventObject  *pEvent[3];

	if (pEventList->Lock())
	{
		for (nItem = pEventList->GetScheduleIndex(), nItems = (INT)pEventList->GetSize(); nItem < nItems; nItem++)
		{
			if ((pEvent[0] = pEventList->GetAt(nItem)))
			{
				if ((pEvent[1] = new CEventObject))
				{
					if ((pEvent[2] = new CEventObject))
					{
						pEvent[1]->Copy(pEvent[0]);
						pEvent[2]->Copy(pEvent[0]);
						if ((nIndex[0] = m_pEventList[0]->Add(pEvent[1], TRUE)) >= 0)
						{
							if ((nIndex[1] = m_pEventList[1]->Add(pEvent[2], TRUE)) >= 0) continue;
							m_pEventList[0]->Remove(nIndex[0]);
						}
						delete pEvent[2];
					}
					delete pEvent[1];
				}
			}
			break;
		}
		pEventList->Unlock();
		return((nItem == nItems) ? TRUE : FALSE);
	}
	return FALSE;
}

BOOL CEventBoxWatchDialog::GetScheduleInfo(CEventList *pEventList) CONST
{
	INT  nItem[2];
	INT  nItems[2];
	CEventObject  *pEvent[2];

	if (pEventList->Lock())
	{
		if (m_pEventList[0]->Lock())
		{
			for (nItem[0] = pEventList->GetScheduleIndex(), nItems[0] = (INT)pEventList->GetSize(); nItem[0] < nItems[0]; nItem[0]++)
			{
				if ((pEvent[0] = pEventList->GetAt(nItem[0])) && pEventList->Remove(nItem[0]))
				{
					delete pEvent[0];
					nItems[0]--;
					nItem[0]--;
					continue;
				}
				break;
			}
			for (nItem[1] = m_pEventList[0]->GetScheduleIndex(), nItems[1] = (INT)m_pEventList[0]->GetSize(); nItem[1] < nItems[1]; nItem[1]++)
			{
				if ((pEvent[0] = m_pEventList[0]->GetAt(nItem[1])))
				{
					if ((pEvent[1] = new CEventObject))
					{
						pEvent[1]->Copy(pEvent[0]);
						if (pEventList->Add(pEvent[1], TRUE) >= 0) continue;
						delete pEvent[1];
					}
				}
				break;
			}
			if (nItem[0] == nItems[0] && nItem[1] == nItems[1])
			{
				m_pEventList[0]->Unlock();
				pEventList->Unlock();
				return TRUE;
			}
			m_pEventList[0]->Unlock();
		}
		pEventList->Unlock();
	}
	return FALSE;
}

CEventBoxWnd *CEventBoxWatchDialog::GetParent() CONST
{
	return((CEventBoxWnd *)CDisplayDialog::GetParent());
}

VOID CEventBoxWatchDialog::DrawTime(CDC *pDC)
{
	INT  nOldBkColor;
	CFont  *pOldFont;
	CRect  rCount[2];
	CRect  rClock[2];
	CBrush  cBkBrush;
	CString  szCount;
	CString  szClock;
	CTimeKey  tClock;
	CTimeKey  tTimeKey;
	CStringTools  cStringTools;
	CEventObject  *pEvent;

	if (cBkBrush.CreateSysColorBrush(COLOR_3DFACE))
	{
		if ((pOldFont = pDC->SelectObject(GetFont())))
		{
			nOldBkColor = pDC->SetBkColor(GetSysColor(COLOR_3DFACE));
			GetDlgItem(IDC_EVENTBOX_WATCH_TIME)->GetWindowRect(rClock[0]);
			GetDlgItem(IDC_EVENTBOX_WATCH_COUNT)->GetWindowRect(rCount[0]);
			ScreenToClient(rClock[0]);
			ScreenToClient(rCount[0]);
			pDC->DrawText((szClock = tClock.FormatGmt()), (rClock[1] = rClock[0]), DT_CALCRECT | DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_NOPREFIX);
			pDC->DrawText(szClock, rClock[1], DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_NOPREFIX);
			pDC->ExcludeClipRect(rClock[1].left, rClock[1].top, rClock[1].right, rClock[1].bottom);
			pDC->FillRect(rClock[0], &cBkBrush);
			pDC->DrawText((szCount = cStringTools.ConvertIntToString((INT)(m_pEventList[0]->GetSize() - m_pEventList[0]->GetScheduleIndex()))), (rCount[1] = rCount[0]), DT_CALCRECT | DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_NOPREFIX);
			pDC->DrawText(szCount, rCount[1], DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_NOPREFIX);
			pDC->ExcludeClipRect(rCount[1].left, rCount[1].top, rCount[1].right, rCount[1].bottom);
			pDC->FillRect(rCount[0], &cBkBrush);
			if ((pEvent = m_pEventList[0]->GetAt(m_pEventList[0]->GetScheduleIndex())) && (tTimeKey = pEvent->GetAuditTime()) >= CTime::GetCurrentTime())
			{
				GetDlgItem(IDC_EVENTBOX_WATCH_REMAININGTIME)->GetWindowRect(rClock[0]);
				ScreenToClient(rClock[0]);
				pDC->DrawText((szClock = CTimeSpan(tTimeKey.GetTime() - CTime::GetCurrentTime().GetTime()).Format(STRING(IDS_TIMEKEY_SPANFORMAT))), (rClock[1] = rClock[0]), DT_CALCRECT | DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_NOPREFIX);
				pDC->DrawText(szClock, rClock[1], DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_NOPREFIX);
				pDC->ExcludeClipRect(rClock[1].left, rClock[1].top, rClock[1].right, rClock[1].bottom);
				pDC->FillRect(rClock[0], &cBkBrush);
				GetDlgItem(IDC_EVENTBOX_WATCH_NEXTTIME)->GetWindowRect(rClock[0]);
				ScreenToClient(rClock[0]);
				pDC->DrawText((szClock = tTimeKey.FormatGmt()), (rClock[1] = rClock[0]), DT_CALCRECT | DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_NOPREFIX);
				pDC->DrawText(szClock, rClock[1], DT_SINGLELINE | DT_LEFT | DT_VCENTER | DT_NOPREFIX);
				pDC->ExcludeClipRect(rClock[1].left, rClock[1].top, rClock[1].right, rClock[1].bottom);
				pDC->FillRect(rClock[0], &cBkBrush);
			}
			else
			{
				GetDlgItem(IDC_EVENTBOX_WATCH_REMAININGTIME)->GetWindowRect(rClock[0]);
				ScreenToClient(rClock[0]);
				pDC->FillRect(rClock[0], &cBkBrush);
				GetDlgItem(IDC_EVENTBOX_WATCH_NEXTTIME)->GetWindowRect(rClock[0]);
				ScreenToClient(rClock[0]);
				pDC->FillRect(rClock[0], &cBkBrush);
			}
			pDC->SetBkMode(nOldBkColor);
			pDC->SelectObject(pOldFont);
		}
		cBkBrush.DeleteObject();
	}
	GetDlgItem(IDC_EVENTBOX_WATCH_REMAININGTIME_STATIC)->EnableWindow((m_pEventList[0]->GetSize() > m_pEventList[0]->GetScheduleIndex()) ? TRUE : FALSE);
	GetDlgItem(IDC_EVENTBOX_WATCH_NEXTTIME_STATIC)->EnableWindow((m_pEventList[0]->GetSize() > m_pEventList[0]->GetScheduleIndex()) ? TRUE : FALSE);
}

INT CEventBoxWatchDialog::CalcColumnWidth(LPCTSTR pszColumn)
{
	CDC  *pDC;
	INT  nWidth;
	CRect  rList;
	CFont  *pOldFont;
	CTimeKey  tFormat;

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(GetFont())))
		{
			GetDlgItem(IDC_EVENTBOX_WATCH_LIST)->GetClientRect(rList);
			nWidth = 2 * CalcColumnIndent() + pDC->GetTextExtent(tFormat.FormatGmt()).cx;
			nWidth = (lstrcmp(STRING(IDS_EVENTBOXWATCHDIALOG_TIME), pszColumn)) ? ((lstrcmp(STRING(IDS_EVENTBOXWATCHDIALOG_MESSAGE), pszColumn)) ? ((rList.Width() - CalcColumnWidth(STRING(IDS_EVENTBOXWATCHDIALOG_TIME))) / 4) : ((3 * (rList.Width() - CalcColumnWidth(STRING(IDS_EVENTBOXWATCHDIALOG_TIME)))) / 4)) : nWidth;
			pDC->SelectObject(pOldFont);
			ReleaseDC(pDC);
			return nWidth;
		}
		ReleaseDC(pDC);
	}
	return 0;
}

INT CEventBoxWatchDialog::CalcColumnIndent() CONST
{
	return 3 * GetSystemMetrics(SM_CXEDGE);
}

BOOL CEventBoxWatchDialog::CheckPrivilege(UINT nPrivilege) CONST
{
	return((GetParent()->GetScope() == DISPLAY_SCOPE_GLOBAL) ? CheckAccountPrivilege(nPrivilege) : TRUE);
}

BOOL CEventBoxWatchDialog::IsModified() CONST
{
	INT  nItem;
	INT  nItems;
	CEventObject  *pEvent[2];

	if (m_pEventList[0]->Lock())
	{
		if (m_pEventList[1]->Lock())
		{
			for (nItem = m_pEventList[0]->GetScheduleIndex(), nItems = (m_pEventList[0]->GetSize() == m_pEventList[1]->GetSize()) ? (INT)m_pEventList[0]->GetSize() : -1; nItem < nItems; nItem++)
			{
				if ((pEvent[1] = ((pEvent[0] = m_pEventList[0]->GetAt(nItem))) ? m_pEventList[1]->GetAt(nItem) : (CEventObject *)NULL) && pEvent[1]->Compare(pEvent[0])) continue;
				break;
			}
			m_pEventList[0]->Unlock();
			m_pEventList[1]->Unlock();
			return((nItem != nItems) ? TRUE : FALSE);
		}
		m_pEventList[0]->Unlock();
	}
	return FALSE;
}

void CEventBoxWatchDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEventBoxWatchDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CEventBoxWatchDialog::PostNcDestroy()
{
	delete m_pEventList[0];
	delete m_pEventList[1];
	m_szColumns.RemoveAll();
	CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CEventBoxWatchDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CEventBoxWatchDialog)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_EVENTBOX_WATCH_LIST_DETAILS, OnDetails)
	ON_BN_CLICKED(IDC_EVENTBOX_WATCH_LIST_CHANGE, OnChange)
	ON_BN_CLICKED(IDC_EVENTBOX_WATCH_LIST_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_EVENTBOX_WATCH_LIST_REMOVEALL, OnRemoveAll)
	ON_BN_CLICKED(IDC_EVENTBOX_WATCH_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventBoxWatchDialog message handlers

BOOL CEventBoxWatchDialog::OnInitDialog()
{
	INT  nPos;
	INT  nItem;
	INT  nItems;
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CEventObject  *pEvent;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	m_szColumns.Add(STRING(IDS_EVENTBOXWATCHDIALOG_TIME));
	m_szColumns.Add(STRING(IDS_EVENTBOXWATCHDIALOG_MESSAGE));
	m_szColumns.Add(STRING(IDS_EVENTBOXWATCHDIALOG_USER));
	SendDlgItemMessage(IDC_EVENTBOX_WATCH_LIST, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = CalcColumnWidth(m_szColumns.GetAt(nColumn)); nColumn < nColumns; nWidth = (++nColumn < nColumns) ? CalcColumnWidth(m_szColumns.GetAt(nColumn)) : 0)
	{
		Listview_InsertColumn(GetDlgItem(IDC_EVENTBOX_WATCH_LIST), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	if (m_pEventList[0]->Lock())
	{
		for (nItem = m_pEventList[0]->GetScheduleIndex(), nItems = (INT)m_pEventList[0]->GetSize(); nItem < nItems; nItem++)
		{
			for (nColumn = 0, nColumns = ((pEvent = m_pEventList[0]->GetAt(nItem))) ? (INT)m_szColumns.GetSize() : 0; nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_EVENTBOXWATCHDIALOG_TIME); )
				{
					szItem = pEvent->GetAuditTime().FormatGmt();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_EVENTBOXWATCHDIALOG_MESSAGE); )
				{
					szItem = ((nPos = (szItem = pEvent->GetMessage()).Find(CR)) >= 0) ? (szItem.Left(nPos) + STRING(IDS_EVENTBOXWATCHDIALOG_ELLIPSES)) : szItem;
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_EVENTBOXWATCHDIALOG_USER); )
				{
					szItem = pEvent->GetUser();
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_EVENTBOX_WATCH_LIST), nItem - m_pEventList[0]->GetScheduleIndex(), szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_EVENTBOX_WATCH_LIST), nItem - m_pEventList[0]->GetScheduleIndex(), nColumn, szItem);
			}
		}
		m_pEventList[0]->Unlock();
	}
	if (m_cClockThread.Start(this, m_szColumns, m_pEventList[0]))
	{
		Listview_SetCurText(GetDlgItem(IDC_EVENTBOX_WATCH_LIST), 0);
		GetDlgItem(IDC_EVENTBOX_WATCH_DETAILS)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_WATCH_TIME_STATIC)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_WATCH_COUNT_STATIC)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_WATCH_NEXTTIME_STATIC)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_WATCH_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_EVENTBOX_WATCH_REMAININGTIME_STATIC)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_WATCH_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_EVENTBOX_WATCH_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_WATCH_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_EVENTBOX_WATCH_LIST)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_WATCH_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_EVENTBOX_WATCH_LIST_DETAILS)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_WATCH_LIST, LVM_GETITEMCOUNT) > 0) ? CheckPrivilege(PRIVILEGE_EVENTBOX_LOOK) : FALSE);
		GetDlgItem(IDC_EVENTBOX_WATCH_LIST_CHANGE)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_WATCH_LIST, LVM_GETITEMCOUNT) > 0) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SCHEDULE) : FALSE);
		GetDlgItem(IDC_EVENTBOX_WATCH_LIST_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_WATCH_LIST, LVM_GETITEMCOUNT) > 0) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SCHEDULE) : FALSE);
		GetDlgItem(IDC_EVENTBOX_WATCH_LIST_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_WATCH_LIST, LVM_GETITEMCOUNT) > 0) ? CheckPrivilege(PRIVILEGE_EVENTBOX_SCHEDULE) : FALSE);
	}
	return TRUE;
}

void CEventBoxWatchDialog::OnPaint()
{
	CPaintDC  cDC(this);

	if (m_pEventList[0]->Lock())
	{
		DrawTime(&cDC);
		m_pEventList[0]->Unlock();
	}
	CDisplayDialog::OnPaint();
}

BOOL CEventBoxWatchDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_EVENTBOX_WATCH_LIST)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == NM_DBLCLK)
		{
			OnDetails();
			return TRUE;
		}
	}
	return CDisplayDialog::OnNotify(wParam, lParam, pResult);
}

void CEventBoxWatchDialog::OnDetails()
{
	INT  nIndex;
	CEventObject  *pEvent[2];
	CEventBoxDetailsDialog  cDetailsDialog;

	if (m_pEventList[0]->Lock())
	{
		for (; (pEvent[0] = new CEventObject); )
		{
			if ((pEvent[1] = (m_pEventList[0]->GetScheduleIndex() + (nIndex = Listview_GetCurText(GetDlgItem(IDC_EVENTBOX_WATCH_LIST))) < m_pEventList[0]->GetSize()) ? m_pEventList[0]->GetAt(m_pEventList[0]->GetScheduleIndex() + nIndex) : (CEventObject *)NULL))
			{
				for (pEvent[0]->Copy(pEvent[1]), pEvent[0]->Acknowledge(), m_pEventList[0]->Unlock(); cDetailsDialog.Create(this, pEvent[0]) == IDOK; ) break;
				m_pEventList[0]->Lock();
			}
			delete pEvent[0];
			break;
		}
		m_pEventList[0]->Unlock();
	}
	GetDlgItem(IDC_EVENTBOX_WATCH_LIST)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxWatchDialog::OnChange()
{
	INT  nPos;
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	INT  nCount;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CEventObject  *pEvent[3];
	CEventBoxScheduleDialog  cScheduleDialog;

	if (m_pEventList[0]->Lock())
	{
		for (; (pEvent[0] = new CEventObject); )
		{
			if ((pEvent[1] = (m_pEventList[0]->GetScheduleIndex() + ((nIndex = Listview_GetCurText(GetDlgItem(IDC_EVENTBOX_WATCH_LIST)))) < m_pEventList[0]->GetSize()) ? m_pEventList[0]->GetAt(m_pEventList[0]->GetScheduleIndex() + nIndex) : (CEventObject *)NULL))
			{
				for (pEvent[0]->Copy(pEvent[1]), m_pEventList[0]->Unlock(); cScheduleDialog.Create(this, pEvent[0]) == IDOK; )
				{
					for (m_pEventList[0]->Lock(); (pEvent[1] = ((nIndex = (cScheduleDialog.GetScheduleInfo(pEvent[0])) ? m_pEventList[0]->Find(pEvent[1]) : -1) >= 0) ? m_pEventList[0]->GetAt(nIndex) : (CEventObject *)NULL); )
					{
						for (nItem = m_pEventList[0]->GetScheduleIndex(), nItems = (m_pEventList[0]->Remove(nIndex) && m_pEventList[0]->Add(pEvent[0], TRUE) >= 0) ? (INT)m_pEventList[0]->GetSize() : -1; (pEvent[2] = (nItem < nItems) ? m_pEventList[0]->GetAt(nItem) : (CEventObject *)NULL); nItem++)
						{
							for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nCount = (INT)SendDlgItemMessage(IDC_EVENTBOX_WATCH_LIST, LVM_GETITEMCOUNT); nColumn < nColumns; nColumn++)
							{
								for (; m_szColumns.GetAt(nColumn) == STRING(IDS_EVENTBOXWATCHDIALOG_TIME); )
								{
									szItem = pEvent[2]->GetAuditTime().FormatGmt();
									break;
								}
								for (; m_szColumns.GetAt(nColumn) == STRING(IDS_EVENTBOXWATCHDIALOG_MESSAGE); )
								{
									szItem = ((nPos = (szItem = pEvent[2]->GetMessage()).Find(CR)) >= 0) ? (szItem.Left(nPos) + STRING(IDS_EVENTBOXWATCHDIALOG_ELLIPSES)) : szItem;
									break;
								}
								for (; m_szColumns.GetAt(nColumn) == STRING(IDS_EVENTBOXWATCHDIALOG_USER); )
								{
									szItem = pEvent[2]->GetUser();
									break;
								}
								if (nItem - m_pEventList[0]->GetScheduleIndex() >= nCount  &&  !nColumn)
								{
									Listview_InsertText(GetDlgItem(IDC_EVENTBOX_WATCH_LIST), nItem - m_pEventList[0]->GetScheduleIndex(), szItem);
									continue;
								}
								Listview_SetText(GetDlgItem(IDC_EVENTBOX_WATCH_LIST), nItem - m_pEventList[0]->GetScheduleIndex(), nColumn, szItem);
							}
						}
						for (; SendDlgItemMessage(IDC_EVENTBOX_WATCH_LIST, LVM_GETITEMCOUNT) > nItems - m_pEventList[0]->GetScheduleIndex(); )
						{
							if (Listview_DeleteText(GetDlgItem(IDC_EVENTBOX_WATCH_LIST), (INT)SendDlgItemMessage(IDC_EVENTBOX_WATCH_LIST, LVM_GETITEMCOUNT) - 1)) continue;
							break;
						}
						if (nItems >= 0)
						{
							pEvent[0] = (CEventObject *)NULL;
							delete pEvent[1];
						}
						break;
					}
					m_pEventList[0]->Unlock();
					break;
				}
				m_pEventList[0]->Lock();
			}
			delete pEvent[0];
			break;
		}
		m_pEventList[0]->Unlock();
	}
	GetDlgItem(IDC_EVENTBOX_WATCH_LIST)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxWatchDialog::OnRemove()
{
	INT  nIndex[2];
	CEventObject  *pEvent;
	CHourglassCursor  cCursor;

	if (m_pEventList[0]->Lock())
	{
		if ((pEvent = ((nIndex[0] = Listview_GetCurText(GetDlgItem(IDC_EVENTBOX_WATCH_LIST))) >= 0 && (nIndex[1] = m_pEventList[0]->GetScheduleIndex() + nIndex[0]) < m_pEventList[0]->GetSize()) ? m_pEventList[0]->GetAt(nIndex[1]) : (CEventObject *)NULL))
		{
			if (Listview_DeleteText(GetDlgItem(IDC_EVENTBOX_WATCH_LIST), nIndex[0]))
			{
				for (; m_pEventList[0]->Remove(nIndex[1]); )
				{
					delete pEvent;
					break;
				}
				Listview_SetCurText(GetDlgItem(IDC_EVENTBOX_WATCH_LIST), 0);
			}
		}
		m_pEventList[0]->Unlock();
	}
	for (GetDlgItem(IDC_EVENTBOX_WATCH_REMAININGTIME_STATIC)->Invalidate(FALSE), GetDlgItem(IDC_EVENTBOX_WATCH_REMAININGTIME)->Invalidate(FALSE), GetDlgItem(IDC_EVENTBOX_WATCH_NEXTTIME_STATIC)->Invalidate(FALSE), GetDlgItem(IDC_EVENTBOX_WATCH_NEXTTIME)->Invalidate(FALSE); !SendDlgItemMessage(IDC_EVENTBOX_WATCH_LIST, LVM_GETITEMCOUNT); )
	{
		GetDlgItem(IDC_EVENTBOX_WATCH_LIST_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_EVENTBOX_WATCH_LIST)->EnableWindow(FALSE);
		GetDlgItem(IDC_EVENTBOX_WATCH_LIST_DETAILS)->EnableWindow(FALSE);
		GetDlgItem(IDC_EVENTBOX_WATCH_LIST_CHANGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EVENTBOX_WATCH_LIST_REMOVE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EVENTBOX_WATCH_LIST_REMOVEALL)->EnableWindow(FALSE);
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
	GetDlgItem(IDOK)->SetFocus();
}

void CEventBoxWatchDialog::OnRemoveAll()
{
	INT  nItem;
	INT  nItems;
	CEventObject  *pEvent;
	CHourglassCursor  cCursor;

	if (m_pEventList[0]->Lock())
	{
		for (nItem = m_pEventList[0]->GetScheduleIndex(), nItems = (INT)m_pEventList[0]->GetSize(); nItem < nItems; nItem++)
		{
			if ((pEvent = m_pEventList[0]->GetAt(nItem)) && m_pEventList[0]->Remove(nItem))
			{
				delete pEvent;
				nItems--;
				nItem--;
			}
		}
		m_pEventList[0]->Unlock();
	}
	SendDlgItemMessage(IDC_EVENTBOX_WATCH_LIST, LVM_DELETEALLITEMS);
	GetDlgItem(IDC_EVENTBOX_WATCH_REMAININGTIME_STATIC)->Invalidate(FALSE);
	GetDlgItem(IDC_EVENTBOX_WATCH_REMAININGTIME)->Invalidate(FALSE);
	GetDlgItem(IDC_EVENTBOX_WATCH_NEXTTIME_STATIC)->Invalidate(FALSE);
	GetDlgItem(IDC_EVENTBOX_WATCH_NEXTTIME)->Invalidate(FALSE);
	GetDlgItem(IDC_EVENTBOX_WATCH_LIST_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOX_WATCH_LIST)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOX_WATCH_LIST_DETAILS)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOX_WATCH_LIST_CHANGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOX_WATCH_LIST_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOX_WATCH_LIST_REMOVEALL)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
	GetDlgItem(IDOK)->SetFocus();
}

void CEventBoxWatchDialog::OnOK()
{
	CHourglassCursor  cCursor;

	GetParent()->OnCloseWatchDialog(IDOK);
	CDisplayDialog::OnOK();
}

BOOL CEventBoxWatchDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_EVENTBOXWATCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CEventBoxWatchDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_EVENTBOXWATCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}

void CEventBoxWatchDialog::OnDestroy()
{
	m_cClockThread.Stop();
	CDisplayDialog::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CEventBoxAcknowledgeDialog dialog

IMPLEMENT_DYNCREATE(CEventBoxAcknowledgeDialog, CDisplayDialog)

CEventBoxAcknowledgeDialog::CEventBoxAcknowledgeDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CEventBoxAcknowledgeDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CEventBoxAcknowledgeDialog::Create(CWnd *pParentWnd, CEventList *pEventList)
{
	m_pEventList = pEventList;
	return CDisplayDialog::Create(pParentWnd, CEventBoxAcknowledgeDialog::IDD);
}

CEventBoxWnd *CEventBoxAcknowledgeDialog::GetParent() CONST
{
	return((CEventBoxWnd *)CDisplayDialog::GetParent());
}

BOOL CEventBoxAcknowledgeDialog::UpdateList()
{
	INT  nPos;
	INT  nItem;
	INT  nItems;
	INT  nColumn;
	INT  nColumns;
	CString  szItem;
	CEventObject  *pEvent;

	if (m_pEventList->Lock())
	{
		for (nItem = 0, nItems = m_pEventList->GetScheduleIndex(), m_pEvents.RemoveAll(), SendDlgItemMessage(IDC_EVENTBOX_ACKNOWLEDGE_TYPE_RESTRICTLIST, CB_RESETCONTENT), SendDlgItemMessage(IDC_EVENTBOX_ACKNOWLEDGE_USER_RESTRICTLIST, CB_RESETCONTENT); nItem < nItems; nItem++)
		{
			for (nColumn = 0, nColumns = ((pEvent = m_pEventList->GetAt(nItem)) && EnumType(pEvent) && EnumUser(pEvent) && CheckEvent(pEvent)) ? (INT)m_szColumns.GetSize() : 0; nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_EVENTBOXACKNOWLEDGEDIALOG_TIME); )
				{
					szItem = pEvent->GetAuditTime().FormatGmt();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_EVENTBOXACKNOWLEDGEDIALOG_MESSAGE); )
				{
					szItem = ((nPos = (szItem = pEvent->GetMessage()).Find(CR)) >= 0) ? (szItem.Left(nPos) + STRING(IDS_EVENTBOXACKNOWLEDGEDIALOG_ELLIPSES)) : szItem;
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_EVENTBOXACKNOWLEDGEDIALOG_USER); )
				{
					szItem = pEvent->GetUser();
					break;
				}
				if (nItem >= SendDlgItemMessage(IDC_EVENTBOX_ACKNOWLEDGE_LIST, LVM_GETITEMCOUNT) && !nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_LIST), (INT)SendDlgItemMessage(IDC_EVENTBOX_ACKNOWLEDGE_LIST, LVM_GETITEMCOUNT), szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_LIST), (INT)SendDlgItemMessage(IDC_EVENTBOX_ACKNOWLEDGE_LIST, LVM_GETITEMCOUNT) - 1, nColumn, szItem);
			}
			if (nColumns > 0)
			{
				m_pEvents.Add(pEvent);
				continue;
			}
		}
		for (m_szType = (SendDlgItemMessage(IDC_EVENTBOX_ACKNOWLEDGE_TYPE_RESTRICTLIST, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)m_szType) >= 0) ? (LPCTSTR)m_szType : EMPTYSTRING, m_szUser = (SendDlgItemMessage(IDC_EVENTBOX_ACKNOWLEDGE_USER_RESTRICTLIST, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)m_szUser) >= 0) ? (LPCTSTR)m_szUser : EMPTYSTRING; SendDlgItemMessage(IDC_EVENTBOX_ACKNOWLEDGE_LIST, LVM_GETITEMCOUNT) > m_pEvents.GetSize(); )
		{
			if (Listview_DeleteText(GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_LIST), (INT)SendDlgItemMessage(IDC_EVENTBOX_ACKNOWLEDGE_LIST, LVM_GETITEMCOUNT) - 1)) continue;
			break;
		}
		Listview_SetCurText(GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_LIST), 0);
		CheckDlgButton(IDC_EVENTBOX_ACKNOWLEDGE_CATEGORY_SYSTEM, (m_nCategory & EVENTBOXACKNOWLEDGEDIALOG_SYSTEMCATEGORY) ? TRUE : FALSE);
		CheckDlgButton(IDC_EVENTBOX_ACKNOWLEDGE_CATEGORY_SPACECRAFT, (m_nCategory & EVENTBOXACKNOWLEDGEDIALOG_SPACECRAFTCATEGORY) ? TRUE : FALSE);
		CheckDlgButton(IDC_EVENTBOX_ACKNOWLEDGE_CATEGORY_USER, (m_nCategory & EVENTBOXACKNOWLEDGEDIALOG_USERCATEGORY) ? TRUE : FALSE);
		CheckDlgButton(IDC_EVENTBOX_ACKNOWLEDGE_TYPE_ALL, (m_szType.IsEmpty()) ? TRUE : FALSE);
		CheckDlgButton(IDC_EVENTBOX_ACKNOWLEDGE_TYPE_RESTRICT, (!m_szType.IsEmpty()) ? TRUE : FALSE);
		CheckDlgButton(IDC_EVENTBOX_ACKNOWLEDGE_USER_ALL, (m_szUser.IsEmpty()) ? TRUE : FALSE);
		CheckDlgButton(IDC_EVENTBOX_ACKNOWLEDGE_USER_RESTRICT, (!m_szUser.IsEmpty()) ? TRUE : FALSE);
		CheckDlgButton(IDC_EVENTBOX_ACKNOWLEDGE_TIME, (m_tTime[0] == m_tTime[1]) ? TRUE : FALSE);
		CheckDlgButton(IDC_EVENTBOX_ACKNOWLEDGE_TIME_RESTRICT, (m_tTime[0] < m_tTime[1]) ? TRUE : FALSE);
		SendDlgItemMessage(IDC_EVENTBOX_ACKNOWLEDGE_TYPE_RESTRICTLIST, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_EVENTBOX_ACKNOWLEDGE_TYPE_RESTRICTLIST, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)m_szType));
		SendDlgItemMessage(IDC_EVENTBOX_ACKNOWLEDGE_USER_RESTRICTLIST, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_EVENTBOX_ACKNOWLEDGE_USER_RESTRICTLIST, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)m_szUser));
		Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_TIME_RESTRICTSTARTTIME), (m_tTime[0] < m_tTime[1]) ? m_tTime[0] : CTime::GetCurrentTime().GetTime());
		Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_TIME_RESTRICTSTOPTIME), (m_tTime[0] < m_tTime[1]) ? m_tTime[1] : CTime::GetCurrentTime().GetTime());
		GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_DETAILS)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_ACKNOWLEDGE_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_LIST)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_ACKNOWLEDGE_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_LISTUPDATE)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_LISTREMOVE)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_ACKNOWLEDGE_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_LISTREMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_ACKNOWLEDGE_LIST, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_CHARACTERISTICS)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_CATEGORY)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_CATEGORY_SYSTEM)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_CATEGORY_SPACECRAFT)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_CATEGORY_USER)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_TYPE)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_TYPE_ALL)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_TYPE_RESTRICT)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_ACKNOWLEDGE_TYPE_RESTRICTLIST, CB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_TYPE_RESTRICTLIST)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOX_ACKNOWLEDGE_TYPE_RESTRICT));
		GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_USER)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_USER_ALL)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_USER_RESTRICT)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_ACKNOWLEDGE_USER_RESTRICTLIST, CB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_USER_RESTRICTLIST)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOX_ACKNOWLEDGE_USER_RESTRICT));
		GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_TIME)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_TIME_RESTRICT)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_TIME_RESTRICTSTARTTIME)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOX_ACKNOWLEDGE_TIME_RESTRICT));
		GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_TIME_RESTRICT_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOX_ACKNOWLEDGE_TIME_RESTRICT));
		GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_TIME_RESTRICTSTOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOX_ACKNOWLEDGE_TIME_RESTRICT));
		m_pEventList->Unlock();
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxAcknowledgeDialog::EnumType(CONST CEventObject *pEvent)
{
	CString  szType;

	for (; SendDlgItemMessage(IDC_EVENTBOX_ACKNOWLEDGE_TYPE_RESTRICTLIST, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)(szType = pEvent->GetType())) == CB_ERR; )
	{
		SendDlgItemMessage(IDC_EVENTBOX_ACKNOWLEDGE_TYPE_RESTRICTLIST, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szType);
		break;
	}
	return TRUE;
}

BOOL CEventBoxAcknowledgeDialog::EnumUser(CONST CEventObject *pEvent)
{
	CString  szUser;

	for (; SendDlgItemMessage(IDC_EVENTBOX_ACKNOWLEDGE_USER_RESTRICTLIST, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)(szUser = pEvent->GetUser())) == CB_ERR; )
	{
		SendDlgItemMessage(IDC_EVENTBOX_ACKNOWLEDGE_USER_RESTRICTLIST, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szUser);
		break;
	}
	return TRUE;
}

BOOL CEventBoxAcknowledgeDialog::CheckEvent(CONST CEventObject *pEvent) CONST
{
	UINT  nCategory;

	return((!pEvent->IsAcknowledged() && (((nCategory = pEvent->GetCategory()) == EVENT_CATEGORY_SYSTEM && (m_nCategory & EVENTBOXACKNOWLEDGEDIALOG_SYSTEMCATEGORY)) || (nCategory == EVENT_CATEGORY_SPACECRAFT && (m_nCategory & EVENTBOXACKNOWLEDGEDIALOG_SPACECRAFTCATEGORY)) || (nCategory == EVENT_CATEGORY_USER && (m_nCategory & EVENTBOXACKNOWLEDGEDIALOG_USERCATEGORY))) && (m_szType.IsEmpty() || m_szType == pEvent->GetType()) && (m_szUser.IsEmpty() || m_szUser == pEvent->GetUser()) && (m_tTime[0] == m_tTime[1] || (m_tTime[0] <= pEvent->GetAuditTime() && m_tTime[1] >= pEvent->GetAuditTime()))) ? TRUE : FALSE);
}

INT CEventBoxAcknowledgeDialog::CalcColumnWidth(LPCTSTR pszColumn)
{
	CDC  *pDC;
	INT  nWidth;
	CRect  rList;
	CFont  *pOldFont;
	CTimeKey  tFormat;

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(GetFont())))
		{
			GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_LIST)->GetClientRect(rList);
			nWidth = 2 * CalcColumnIndent() + pDC->GetTextExtent(tFormat.FormatGmt()).cx;
			nWidth = (lstrcmp(STRING(IDS_EVENTBOXACKNOWLEDGEDIALOG_TIME), pszColumn)) ? ((lstrcmp(STRING(IDS_EVENTBOXACKNOWLEDGEDIALOG_MESSAGE), pszColumn)) ? ((rList.Width() - CalcColumnWidth(STRING(IDS_EVENTBOXACKNOWLEDGEDIALOG_TIME))) / 4) : ((3 * (rList.Width() - CalcColumnWidth(STRING(IDS_EVENTBOXACKNOWLEDGEDIALOG_TIME)))) / 4)) : nWidth;
			pDC->SelectObject(pOldFont);
			ReleaseDC(pDC);
			return nWidth;
		}
		ReleaseDC(pDC);
	}
	return 0;
}

INT CEventBoxAcknowledgeDialog::CalcColumnIndent() CONST
{
	return 3 * GetSystemMetrics(SM_CXEDGE);
}

BOOL CEventBoxAcknowledgeDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_LIST)->SendMessage(LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
}

void CEventBoxAcknowledgeDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEventBoxAcknowledgeDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CEventBoxAcknowledgeDialog::PostNcDestroy()
{
	m_pEvents.RemoveAll();
	m_szColumns.RemoveAll();
	CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CEventBoxAcknowledgeDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CEventBoxAcknowledgeDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_EVENTBOX_ACKNOWLEDGE_LISTUPDATE, OnListUpdate)
	ON_BN_CLICKED(IDC_EVENTBOX_ACKNOWLEDGE_LISTREMOVE, OnListRemove)
	ON_BN_CLICKED(IDC_EVENTBOX_ACKNOWLEDGE_LISTREMOVEALL, OnListRemoveAll)
	ON_BN_CLICKED(IDC_EVENTBOX_ACKNOWLEDGE_CATEGORY_SYSTEM, OnSystemCategory)
	ON_BN_CLICKED(IDC_EVENTBOX_ACKNOWLEDGE_CATEGORY_SPACECRAFT, OnSpacecraftCategory)
	ON_BN_CLICKED(IDC_EVENTBOX_ACKNOWLEDGE_CATEGORY_USER, OnUserCategory)
	ON_BN_CLICKED(IDC_EVENTBOX_ACKNOWLEDGE_TYPE_ALL, OnTypeAll)
	ON_BN_CLICKED(IDC_EVENTBOX_ACKNOWLEDGE_USER_ALL, OnUserAll)
	ON_BN_CLICKED(IDC_EVENTBOX_ACKNOWLEDGE_TYPE_RESTRICT, OnTypeRestriction)
	ON_BN_CLICKED(IDC_EVENTBOX_ACKNOWLEDGE_USER_RESTRICT, OnUserRestriction)
	ON_BN_CLICKED(IDC_EVENTBOX_ACKNOWLEDGE_TIME_RESTRICT, OnTimeRestriction)
	ON_BN_CLICKED(IDC_EVENTBOX_ACKNOWLEDGE_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_EVENTBOX_ACKNOWLEDGE_TYPE_RESTRICTLIST, OnSelchangeType)
	ON_CBN_SELCHANGE(IDC_EVENTBOX_ACKNOWLEDGE_USER_RESTRICTLIST, OnSelchangeUser)
	ON_CONTROL(TSBXN_CHANGE, IDC_EVENTBOX_ACKNOWLEDGE_TIME_RESTRICTSTARTTIME, OnSpinchangeStartTime)
	ON_CONTROL(TSBXN_CHANGE, IDC_EVENTBOX_ACKNOWLEDGE_TIME_RESTRICTSTOPTIME, OnSpinchangeStopTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventBoxAcknowledgeDialog message handlers

BOOL CEventBoxAcknowledgeDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	m_szColumns.Add(STRING(IDS_EVENTBOXACKNOWLEDGEDIALOG_TIME));
	m_szColumns.Add(STRING(IDS_EVENTBOXACKNOWLEDGEDIALOG_MESSAGE));
	m_szColumns.Add(STRING(IDS_EVENTBOXACKNOWLEDGEDIALOG_USER));
	SendDlgItemMessage(IDC_EVENTBOX_ACKNOWLEDGE_LIST, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = CalcColumnWidth(m_szColumns.GetAt(nColumn)); nColumn < nColumns; nWidth = (++nColumn < nColumns) ? CalcColumnWidth(m_szColumns.GetAt(min(nColumn, nColumns - 1))) : 0)
	{
		Listview_InsertColumn(GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_LIST), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	for (m_nCategory = EVENTBOXACKNOWLEDGEDIALOG_SYSTEMCATEGORY | EVENTBOXACKNOWLEDGEDIALOG_SPACECRAFTCATEGORY | EVENTBOXACKNOWLEDGEDIALOG_USERCATEGORY, m_tTime[0] = m_tTime[1] = 0, m_szType.Empty(), m_szUser.Empty(); UpdateList(); )
	{
		GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_DETAILS)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_LIST)->SetFocus();
		GetDlgItem(IDOK)->EnableWindow(Check());
		return FALSE;
	}
	return TRUE;
}

void CEventBoxAcknowledgeDialog::OnListUpdate()
{
	CHourglassCursor  cCursor;

	UpdateList();
	GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_LIST)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxAcknowledgeDialog::OnListRemove()
{
	INT  nItem;
	INT  nItems;
	CHourglassCursor  cCursor;

	for (nItem = 0, nItems = (INT)SendDlgItemMessage(IDC_EVENTBOX_ACKNOWLEDGE_LIST, LVM_GETITEMCOUNT); nItem < nItems; nItem++)
	{
		if (Listview_IsSelText(GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_LIST), nItem) && Listview_DeleteText(GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_LIST), nItem))
		{
			m_pEvents.RemoveAt(nItem);
			nItems--;
			nItem--;
		}
	}
	if (!SendDlgItemMessage(IDC_EVENTBOX_ACKNOWLEDGE_LIST, LVM_GETITEMCOUNT))
	{
		GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_LIST_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_LIST)->EnableWindow(FALSE);
		GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_LISTREMOVE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_LISTREMOVEALL)->EnableWindow(FALSE);
		GetDlgItem(IDOK)->EnableWindow(Check());
		GetDlgItem(IDCANCEL)->SetFocus();
		return;
	}
	Listview_SetCurText(GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_LIST), 0);
	GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_LIST)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxAcknowledgeDialog::OnListRemoveAll()
{
	CHourglassCursor  cCursor;

	m_pEvents.RemoveAll();
	SendDlgItemMessage(IDC_EVENTBOX_ACKNOWLEDGE_LIST, LVM_DELETEALLITEMS);
	GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_LIST_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_LIST)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_LISTREMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_LISTREMOVEALL)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
	GetDlgItem(IDCANCEL)->SetFocus();
}

void CEventBoxAcknowledgeDialog::OnSystemCategory()
{
	m_nCategory = (IsDlgButtonChecked(IDC_EVENTBOX_ACKNOWLEDGE_CATEGORY_SYSTEM)) ? (m_nCategory | EVENTBOXACKNOWLEDGEDIALOG_SYSTEMCATEGORY) : (m_nCategory & ~EVENTBOXACKNOWLEDGEDIALOG_SYSTEMCATEGORY);
}

void CEventBoxAcknowledgeDialog::OnSpacecraftCategory()
{
	m_nCategory = (IsDlgButtonChecked(IDC_EVENTBOX_ACKNOWLEDGE_CATEGORY_SPACECRAFT)) ? (m_nCategory | EVENTBOXACKNOWLEDGEDIALOG_SPACECRAFTCATEGORY) : (m_nCategory & ~EVENTBOXACKNOWLEDGEDIALOG_SPACECRAFTCATEGORY);
}

void CEventBoxAcknowledgeDialog::OnUserCategory()
{
	m_nCategory = (IsDlgButtonChecked(IDC_EVENTBOX_ACKNOWLEDGE_CATEGORY_USER)) ? (m_nCategory | EVENTBOXACKNOWLEDGEDIALOG_USERCATEGORY) : (m_nCategory & ~EVENTBOXACKNOWLEDGEDIALOG_USERCATEGORY);
}

void CEventBoxAcknowledgeDialog::OnTypeAll()
{
	m_szType.Empty();
	CheckDlgButton(IDC_EVENTBOX_ACKNOWLEDGE_TYPE_ALL, TRUE);
	CheckDlgButton(IDC_EVENTBOX_ACKNOWLEDGE_TYPE_RESTRICT, FALSE);
	SendDlgItemMessage(IDC_EVENTBOX_ACKNOWLEDGE_TYPE_RESTRICTLIST, CB_SETCURSEL, (WPARAM)-1);
	GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_TYPE_RESTRICTLIST)->EnableWindow(FALSE);
}

void CEventBoxAcknowledgeDialog::OnUserAll()
{
	m_szUser.Empty();
	CheckDlgButton(IDC_EVENTBOX_ACKNOWLEDGE_USER_ALL, TRUE);
	CheckDlgButton(IDC_EVENTBOX_ACKNOWLEDGE_USER_RESTRICT, FALSE);
	SendDlgItemMessage(IDC_EVENTBOX_ACKNOWLEDGE_USER_RESTRICTLIST, CB_SETCURSEL, (WPARAM)-1);
	GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_USER_RESTRICTLIST)->EnableWindow(FALSE);
}

void CEventBoxAcknowledgeDialog::OnTypeRestriction()
{
	CheckDlgButton(IDC_EVENTBOX_ACKNOWLEDGE_TYPE_ALL, FALSE);
	CheckDlgButton(IDC_EVENTBOX_ACKNOWLEDGE_TYPE_RESTRICT, TRUE);
	SendDlgItemMessage(IDC_EVENTBOX_ACKNOWLEDGE_TYPE_RESTRICTLIST, CB_SETCURSEL);
	GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_TYPE_RESTRICTLIST)->GetWindowText(m_szType);
	GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_TYPE_RESTRICTLIST)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_TYPE_RESTRICTLIST)->SetFocus();
}

void CEventBoxAcknowledgeDialog::OnUserRestriction()
{
	CheckDlgButton(IDC_EVENTBOX_ACKNOWLEDGE_USER_ALL, FALSE);
	CheckDlgButton(IDC_EVENTBOX_ACKNOWLEDGE_USER_RESTRICT, TRUE);
	SendDlgItemMessage(IDC_EVENTBOX_ACKNOWLEDGE_USER_RESTRICTLIST, CB_SETCURSEL);
	GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_USER_RESTRICTLIST)->GetWindowText(m_szUser);
	GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_USER_RESTRICTLIST)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_USER_RESTRICTLIST)->SetFocus();
}

void CEventBoxAcknowledgeDialog::OnTimeRestriction()
{
	CTimeKey  tTime[2];

	for (Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_TIME_RESTRICTSTARTTIME), (m_tTime[0] = tTime[0] = CTime::GetCurrentTime().GetTime() - EVENTBOXACKNOWLEDGEDIALOG_DEFAULTINTERVAL)), Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_TIME_RESTRICTSTOPTIME), (m_tTime[1] = tTime[1] = tTime[0].GetTime() + EVENTBOXACKNOWLEDGEDIALOG_DEFAULTINTERVAL)); !IsDlgButtonChecked(IDC_EVENTBOX_ACKNOWLEDGE_TIME_RESTRICT); )
	{
		m_tTime[0] = m_tTime[1] = 0;
		break;
	}
	GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_TIME_RESTRICTSTARTTIME)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOX_ACKNOWLEDGE_TIME_RESTRICT));
	GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_TIME_RESTRICT_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOX_ACKNOWLEDGE_TIME_RESTRICT));
	GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_TIME_RESTRICTSTOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOX_ACKNOWLEDGE_TIME_RESTRICT));
	GetDlgItem((IsDlgButtonChecked(IDC_EVENTBOX_ACKNOWLEDGE_TIME_RESTRICT)) ? IDC_EVENTBOX_ACKNOWLEDGE_TIME_RESTRICTSTARTTIME : IDC_EVENTBOX_ACKNOWLEDGE_TIME_RESTRICT)->SetFocus();
}

void CEventBoxAcknowledgeDialog::OnSelchangeType()
{
	GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_TYPE_RESTRICTLIST)->GetWindowText(m_szType);
}

void CEventBoxAcknowledgeDialog::OnSelchangeUser()
{
	GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_USER_RESTRICTLIST)->GetWindowText(m_szUser);
}

void CEventBoxAcknowledgeDialog::OnSpinchangeStartTime()
{
	CTimeKey  tTime[2];

	for (m_tTime[0] = tTime[0] = Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_TIME_RESTRICTSTARTTIME)), m_tTime[1] = tTime[1] = Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_TIME_RESTRICTSTOPTIME)); tTime[0] > tTime[1]; )
	{
		Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_TIME_RESTRICTSTOPTIME), (m_tTime[1] = tTime[0]));
		break;
	}
}

void CEventBoxAcknowledgeDialog::OnSpinchangeStopTime()
{
	CTimeKey  tTime[2];

	for (m_tTime[0] = tTime[0] = Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_TIME_RESTRICTSTARTTIME)), m_tTime[1] = tTime[1] = Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_TIME_RESTRICTSTOPTIME)); tTime[0] > tTime[1]; )
	{
		Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOX_ACKNOWLEDGE_TIME_RESTRICTSTARTTIME), (m_tTime[0] = tTime[1]));
		break;
	}
}

void CEventBoxAcknowledgeDialog::OnOK()
{
	INT  nItem;
	INT  nItems;
	CEventObject  *pEvent;
	CHourglassCursor  cCursor;

	for (nItem = 0, nItems = (INT)m_pEvents.GetSize(); nItem < nItems; nItem++)
	{
		if ((pEvent = (CEventObject *)m_pEvents.GetAt(nItem)))
		{
			GetParent()->AcknowledgeEvent(pEvent);
			continue;
		}
	}
	CDisplayDialog::OnOK();
}

BOOL CEventBoxAcknowledgeDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_EVENTBOXACKNOWLEDGEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CEventBoxAcknowledgeDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_EVENTBOXACKNOWLEDGEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CEventBoxRetrieveDialog dialog

IMPLEMENT_DYNCREATE(CEventBoxRetrieveDialog, CDisplayDialog)

CEventBoxRetrieveDialog::CEventBoxRetrieveDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CEventBoxRetrieveDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CEventBoxRetrieveDialog::Create(CWnd *pParentWnd, LPCTSTR pszComputerName, LPCTSTR pszSpacecraftName, LPCTSTR pszUserName, BOOL bLocal)
{
	INT  nResult;

	for (m_szComputerName = pszComputerName, m_szSpacecraftName = pszSpacecraftName, m_szUserName = pszUserName, m_bLocal = bLocal; (nResult = CDisplayDialog::Create(pParentWnd, CEventBoxRetrieveDialog::IDD)); ) break;
	return nResult;
}

BOOL CEventBoxRetrieveDialog::GetMode(UINT &nMode) CONST
{
	nMode = (!IsDlgButtonChecked(IDC_EVENTBOX_RETRIEVE_REALTIME)) ? ((!IsDlgButtonChecked(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPBYTIME)) ? ((!IsDlgButtonChecked(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPBYEVENTS)) ? EVENTBOX_RETRIEVE_STOPBYEND : EVENTBOX_RETRIEVE_STOPBYEVENTS) : EVENTBOX_RETRIEVE_STOPBYTIME) : 0;
	nMode |= (!IsDlgButtonChecked(IDC_EVENTBOX_RETRIEVE_REALTIME)) ? ((IsDlgButtonChecked(IDC_EVENTBOX_RETRIEVE_HISTORY_ALLATONCE)) ? EVENTBOX_RETRIEVE_ALLATONCE : ((IsDlgButtonChecked(IDC_EVENTBOX_RETRIEVE_HISTORY_PSEUDOREALTIME)) ? EVENTBOX_RETRIEVE_PSEUDOREALTIME : EVENTBOX_RETRIEVE_MANUAL)) : 0;
	return TRUE;
}

BOOL CEventBoxRetrieveDialog::GetLimit(UINT &nCount) CONST
{
	for (nCount = 0; IsDlgButtonChecked(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPBYEVENTS) || IsDlgButtonChecked(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPBYEND); )
	{
		nCount = (IsDlgButtonChecked(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPBYEVENTS)) ? (UINT)Spinbox_GetPos(GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPEVENTS)) : EVENTBOX_FILTER_DEFAULTNOLIMIT;
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxRetrieveDialog::GetStartTime(CTimeKey &tTimeKey) CONST
{
	CTimeKey  tTime;

	for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_STARTTIME)), tTimeKey = 0; !IsDlgButtonChecked(IDC_EVENTBOX_RETRIEVE_REALTIME) && tTime > 0; )
	{
		tTimeKey = tTime;
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxRetrieveDialog::GetStopTime(CTimeKey &tTimeKey) CONST
{
	CTimeKey  tTime;

	for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPTIME)), tTimeKey = 0; IsDlgButtonChecked(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPBYTIME) && tTime > 0; )
	{
		tTimeKey = tTime;
		return TRUE;
	}
	return FALSE;
}

CEventBoxOpenDialog *CEventBoxRetrieveDialog::GetParentDialog() CONST
{
	return((GetParent() != (CWnd *)GetParentDisplay()) ? (CEventBoxOpenDialog *)GetParent() : (CEventBoxOpenDialog *)NULL);
}

CEventBoxWnd *CEventBoxRetrieveDialog::GetParentDisplay() CONST
{
	return((CEventBoxWnd *)CDisplayDialog::GetParentDisplay());
}

BOOL CEventBoxRetrieveDialog::SetRetrieveInfo()
{
	UINT  nMode;
	UINT  nLimit;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;

	if (GetRetrieveInfo(nMode, nLimit, tStartTime, tStopTime))
	{
		Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_STARTTIME), (tStartTime > 0 || GetTMService()->GetRecentTMHistoryTimeKey(tStartTime)) ? tStartTime : CTime::GetCurrentTime().GetTime());
		Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPTIME), (nMode & EVENTBOX_RETRIEVE_STOPBYTIME) ? tStopTime : CTime::GetCurrentTime().GetTime());
		Timespinbox_SetRange(GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPTIME), Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_STARTTIME)), MAX_TIMEKEY);
		Spinbox_SetRange(GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPEVENTS), EVENTBOXRETRIEVEDIALOG_MINIMUMEVENTS, EVENTBOXRETRIEVEDIALOG_MAXIMUMEVENTS);
		Spinbox_SetPos(GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPEVENTS), (nMode & EVENTBOX_RETRIEVE_STOPBYEVENTS) ? nLimit : EVENTBOXRETRIEVEDIALOG_DEFAULTEVENTS);
		CheckDlgButton(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPBYTIME, (!IsDlgButtonChecked(IDC_EVENTBOX_RETRIEVE_REALTIME) && (nMode & EVENTBOX_RETRIEVE_STOPBYTIME)) ? TRUE : FALSE);
		CheckDlgButton(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPBYEVENTS, (!IsDlgButtonChecked(IDC_EVENTBOX_RETRIEVE_REALTIME) && (nMode & (EVENTBOX_RETRIEVE_STOPBYTIME | EVENTBOX_RETRIEVE_STOPBYEND)) == 0) ? TRUE : FALSE);
		CheckDlgButton(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPBYEND, (!IsDlgButtonChecked(IDC_EVENTBOX_RETRIEVE_REALTIME) && (nMode & EVENTBOX_RETRIEVE_STOPBYEND)) ? TRUE : FALSE);
		CheckDlgButton(IDC_EVENTBOX_RETRIEVE_HISTORY_ALLATONCE, (!IsDlgButtonChecked(IDC_EVENTBOX_RETRIEVE_REALTIME) && (nMode & (EVENTBOX_RETRIEVE_PSEUDOREALTIME | EVENTBOX_RETRIEVE_MANUAL)) == 0) ? TRUE : FALSE);
		CheckDlgButton(IDC_EVENTBOX_RETRIEVE_HISTORY_PSEUDOREALTIME, (!IsDlgButtonChecked(IDC_EVENTBOX_RETRIEVE_REALTIME) && (nMode & EVENTBOX_RETRIEVE_PSEUDOREALTIME)) ? TRUE : FALSE);
		CheckDlgButton(IDC_EVENTBOX_RETRIEVE_HISTORY_MANUAL, (!IsDlgButtonChecked(IDC_EVENTBOX_RETRIEVE_REALTIME) && (nMode & EVENTBOX_RETRIEVE_MANUAL)) ? TRUE : FALSE);
		GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY)->EnableWindow(!IsDlgButtonChecked(IDC_EVENTBOX_RETRIEVE_REALTIME));
		GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_START_STATIC)->EnableWindow(!IsDlgButtonChecked(IDC_EVENTBOX_RETRIEVE_REALTIME));
		GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_STARTTIME)->EnableWindow(!IsDlgButtonChecked(IDC_EVENTBOX_RETRIEVE_REALTIME));
		GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_STOP_STATIC)->EnableWindow(!IsDlgButtonChecked(IDC_EVENTBOX_RETRIEVE_REALTIME));
		GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPBYTIME)->EnableWindow(!IsDlgButtonChecked(IDC_EVENTBOX_RETRIEVE_REALTIME));
		GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPBYEVENTS)->EnableWindow(!IsDlgButtonChecked(IDC_EVENTBOX_RETRIEVE_REALTIME));
		GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPBYEND)->EnableWindow(!IsDlgButtonChecked(IDC_EVENTBOX_RETRIEVE_REALTIME));
		GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(!IsDlgButtonChecked(IDC_EVENTBOX_RETRIEVE_REALTIME) && IsDlgButtonChecked(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPBYTIME));
		GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPEVENTS_STATIC)->EnableWindow(!IsDlgButtonChecked(IDC_EVENTBOX_RETRIEVE_REALTIME) && IsDlgButtonChecked(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPBYEVENTS));
		GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPEVENTS)->EnableWindow(!IsDlgButtonChecked(IDC_EVENTBOX_RETRIEVE_REALTIME) && IsDlgButtonChecked(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPBYEVENTS));
		GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_PLAYBACKMODE)->EnableWindow(!IsDlgButtonChecked(IDC_EVENTBOX_RETRIEVE_REALTIME));
		GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_ALLATONCE)->EnableWindow(!IsDlgButtonChecked(IDC_EVENTBOX_RETRIEVE_REALTIME));
		GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_PSEUDOREALTIME)->EnableWindow(!IsDlgButtonChecked(IDC_EVENTBOX_RETRIEVE_REALTIME));
		GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_MANUAL)->EnableWindow(!IsDlgButtonChecked(IDC_EVENTBOX_RETRIEVE_REALTIME));
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxRetrieveDialog::GetRetrieveInfo(UINT &nMode, UINT &nCount, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	CEventBoxWnd  *pEventBoxWnd;
	CEventBoxOpenDialog  *pDialog;

	if ((pDialog = GetParentDialog()))
	{
		for (pDialog->GetRetrieveMode(nMode), nCount = 0, tStartTime = tStopTime = 0; nMode; )
		{
			pDialog->GetRetrieveLimit(nCount);
			pDialog->GetRetrieveStartTime(tStartTime);
			pDialog->GetRetrieveStopTime(tStopTime);
			break;
		}
		return TRUE;
	}
	if ((pEventBoxWnd = GetParentDisplay()))
	{
		for (pEventBoxWnd->GetRetrieveMode(nMode), nCount = 0, tStartTime = tStopTime = 0; nMode; )
		{
			pEventBoxWnd->GetRetrieveLimit(nCount);
			pEventBoxWnd->GetRetrieveStartTime(tStartTime);
			pEventBoxWnd->GetRetrieveStopTime(tStopTime);
			break;
		}
		return TRUE;
	}
	return FALSE;
}

void CEventBoxRetrieveDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEventBoxRetrieveDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEventBoxRetrieveDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CEventBoxRetrieveDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_EVENTBOX_RETRIEVE_REALTIME, OnRetrieveRealtime)
	ON_BN_CLICKED(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPBYTIME, OnRetrieveByTime)
	ON_BN_CLICKED(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPBYEVENTS, OnRetrieveByEvents)
	ON_BN_CLICKED(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPBYEND, OnRetrieveByEnd)
	ON_BN_CLICKED(IDC_EVENTBOX_RETRIEVE_HISTORY_ALLATONCE, OnRetrieveAllAtOnce)
	ON_BN_CLICKED(IDC_EVENTBOX_RETRIEVE_HISTORY_PSEUDOREALTIME, OnRetrievePseudoRealtime)
	ON_BN_CLICKED(IDC_EVENTBOX_RETRIEVE_HISTORY_MANUAL, OnRetrieveManual)
	ON_BN_CLICKED(IDC_EVENTBOX_RETRIEVE_HELP, OnHelp)
	ON_CONTROL(TSBXN_CHANGE, IDC_EVENTBOX_RETRIEVE_HISTORY_STARTTIME, OnSpinchangeRetrieveStartTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventBoxRetrieveDialog message handlers

BOOL CEventBoxRetrieveDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	for (CDisplayDialog::OnInitDialog(), GetDlgItem(IDC_EVENTBOX_RETRIEVE_COMPUTERNAME)->SetWindowText(m_szComputerName), GetDlgItem(IDC_EVENTBOX_RETRIEVE_SPACECRAFTNAME)->SetWindowText(m_szSpacecraftName), GetDlgItem(IDC_EVENTBOX_RETRIEVE_USERNAME)->SetWindowText(m_szUserName); SetRetrieveInfo(); )
	{
		GetDlgItem(IDC_EVENTBOX_RETRIEVE_DETAILS)->EnableWindow((GetDlgItem(IDC_EVENTBOX_RETRIEVE_COMPUTERNAME)->GetWindowTextLength() > 0 || GetDlgItem(IDC_EVENTBOX_RETRIEVE_SPACECRAFTNAME)->GetWindowTextLength() > 0 || GetDlgItem(IDC_EVENTBOX_RETRIEVE_USERNAME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_EVENTBOX_RETRIEVE_COMPUTERNAME_STATIC)->EnableWindow((GetDlgItem(IDC_EVENTBOX_RETRIEVE_COMPUTERNAME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_EVENTBOX_RETRIEVE_COMPUTERNAME)->EnableWindow((GetDlgItem(IDC_EVENTBOX_RETRIEVE_COMPUTERNAME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_EVENTBOX_RETRIEVE_SPACECRAFTNAME_STATIC)->EnableWindow((GetDlgItem(IDC_EVENTBOX_RETRIEVE_SPACECRAFTNAME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_EVENTBOX_RETRIEVE_SPACECRAFTNAME)->EnableWindow((GetDlgItem(IDC_EVENTBOX_RETRIEVE_SPACECRAFTNAME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_EVENTBOX_RETRIEVE_USERNAME_STATIC)->EnableWindow((GetDlgItem(IDC_EVENTBOX_RETRIEVE_USERNAME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_EVENTBOX_RETRIEVE_USERNAME)->EnableWindow((GetDlgItem(IDC_EVENTBOX_RETRIEVE_USERNAME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_EVENTBOX_RETRIEVE_REALTIME)->EnableWindow((GetParentDisplay()->GetMode() == DISPLAY_MODE_HISTORY && (GetAccountComputerName().CompareNoCase(m_szComputerName) || GetAccountSpacecraftName() != m_szSpacecraftName || GetAccountUserName() != m_szUserName || !m_bLocal)) ? TRUE : FALSE);
		GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_STARTTIME)->SetFocus();
		GetDlgItem(IDOK)->EnableWindow();
		return FALSE;
	}
	return TRUE;
}

void CEventBoxRetrieveDialog::OnRetrieveRealtime()
{
	SetRetrieveInfo();
}

void CEventBoxRetrieveDialog::OnRetrieveByTime()
{
	CheckRadioButton(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPBYTIME, IDC_EVENTBOX_RETRIEVE_HISTORY_STOPBYEND, IDC_EVENTBOX_RETRIEVE_HISTORY_STOPBYTIME);
	Timespinbox_SetRange(GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPTIME), Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_STARTTIME)), MAX_TIMEKEY);
	Timespinbox_SetTime(GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPTIME), CTimeKey(CTime::GetCurrentTime().GetTime()));
	GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPTIME)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPEVENTS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPEVENTS)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPTIME)->SetFocus();
}

void CEventBoxRetrieveDialog::OnRetrieveByEvents()
{
	CheckRadioButton(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPBYTIME, IDC_EVENTBOX_RETRIEVE_HISTORY_STOPBYEND, IDC_EVENTBOX_RETRIEVE_HISTORY_STOPBYEVENTS);
	GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPEVENTS_STATIC)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPEVENTS)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPEVENTS)->SetFocus();
}

void CEventBoxRetrieveDialog::OnRetrieveByEnd()
{
	CheckRadioButton(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPBYTIME, IDC_EVENTBOX_RETRIEVE_HISTORY_STOPBYEND, IDC_EVENTBOX_RETRIEVE_HISTORY_STOPBYEND);
	GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPEVENTS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPEVENTS)->EnableWindow(FALSE);
}

void CEventBoxRetrieveDialog::OnRetrieveAllAtOnce()
{
	CheckRadioButton(IDC_EVENTBOX_RETRIEVE_HISTORY_ALLATONCE, IDC_EVENTBOX_RETRIEVE_HISTORY_MANUAL, IDC_EVENTBOX_RETRIEVE_HISTORY_ALLATONCE);
}

void CEventBoxRetrieveDialog::OnRetrievePseudoRealtime()
{
	CheckRadioButton(IDC_EVENTBOX_RETRIEVE_HISTORY_ALLATONCE, IDC_EVENTBOX_RETRIEVE_HISTORY_MANUAL, IDC_EVENTBOX_RETRIEVE_HISTORY_PSEUDOREALTIME);
}

void CEventBoxRetrieveDialog::OnRetrieveManual()
{
	CheckRadioButton(IDC_EVENTBOX_RETRIEVE_HISTORY_ALLATONCE, IDC_EVENTBOX_RETRIEVE_HISTORY_MANUAL, IDC_EVENTBOX_RETRIEVE_HISTORY_MANUAL);
}

void CEventBoxRetrieveDialog::OnSpinchangeRetrieveStartTime()
{
	Timespinbox_SetRange(GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_STOPTIME), Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOX_RETRIEVE_HISTORY_STARTTIME)), MAX_TIMEKEY);
}

void CEventBoxRetrieveDialog::OnOK()
{
	BOOL  bLocal;
	CString  szUserName;
	CString  szComputerName;
	CString  szSpacecraftName;
	CTimeKey  tRetrieveTimeKey;
	CEventBoxWnd  *pEventBoxWnd;
	CEventBoxOpenDialog  *pDialog;
	CHourglassCursor  cCursor;

	for (; !GetParentDialog(); )
	{
		if (IsDlgButtonChecked(IDC_EVENTBOX_RETRIEVE_REALTIME))
		{
			if ((pEventBoxWnd = (GetParentDisplay()->GetAccountName(szComputerName, szSpacecraftName, szUserName, bLocal)) ? GetParentDisplay()->Find(DISPLAY_MODE_REALTIME, szComputerName, szSpacecraftName, szUserName, !bLocal) : (CEventBoxWnd *)NULL))
			{
				for (GetDisplayArea()->ActivateDisplay(pEventBoxWnd); pEventBoxWnd != GetParentDisplay(); )
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
	for (; GetStartTime(tRetrieveTimeKey); )
	{
		GetTMService()->SetRecentTMHistoryTimeKey(tRetrieveTimeKey);
		break;
	}
	CDisplayDialog::OnOK();
}

void CEventBoxRetrieveDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	if (!GetParentDialog()) GetParentDisplay()->OnCloseRetrieveDialog(IDCANCEL);
	else  GetParentDialog()->OnCloseRetrieveDialog(IDCANCEL);
	CDisplayDialog::OnCancel();
}

BOOL CEventBoxRetrieveDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_EVENTBOXRETRIEVEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CEventBoxRetrieveDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_EVENTBOXRETRIEVEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CEventBoxSearchTimeDialog dialog

IMPLEMENT_DYNCREATE(CEventBoxSearchTimeDialog, CDisplayDialog)

CEventBoxSearchTimeDialog::CEventBoxSearchTimeDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CEventBoxSearchTimeDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CEventBoxSearchTimeDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CEventBoxSearchTimeDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CEventBoxWnd *CEventBoxSearchTimeDialog::GetParent() CONST
{
	return((CEventBoxWnd *)CDisplayDialog::GetParent());
}

void CEventBoxSearchTimeDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEventBoxSearchTimeDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEventBoxSearchTimeDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CEventBoxSearchTimeDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_EVENTBOX_SEARCHTIME_FIND, OnFindTime)
	ON_BN_CLICKED(IDC_EVENTBOX_SEARCHTIME_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventBoxSearchTimeDialog message handlers

BOOL CEventBoxSearchTimeDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	CheckDlgButton(IDC_EVENTBOX_SEARCHTIME_ALL, TRUE);
	CheckDlgButton(IDC_EVENTBOX_SEARCHTIME_DIRECTION_DOWN, TRUE);
	GetDlgItem(IDC_EVENTBOX_SEARCHTIME_TIME_STATIC)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_SEARCHTIME_TIME)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_SEARCHTIME_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_SEARCHTIME_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_SEARCHTIME_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_SEARCHTIME_ALL)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_SEARCHTIME_MATCH)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_SEARCHTIME_FIND)->EnableWindow();
	return TRUE;
}

void CEventBoxSearchTimeDialog::OnFindTime()
{
	CHourglassCursor  cCursor;

	if (!GetParent()->SearchEventByTime(Timespinbox_GetTime(GetDlgItem(IDC_EVENTBOX_SEARCHTIME_TIME)), IsDlgButtonChecked(IDC_EVENTBOX_SEARCHTIME_DIRECTION_DOWN), IsDlgButtonChecked(IDC_EVENTBOX_SEARCHTIME_ALL), IsDlgButtonChecked(IDC_EVENTBOX_SEARCHTIME_MATCH)))
	{
		ReportEvent(USER_INFORMATIONAL_EVENTBOX_SEARCH_TIME_NOTHING);
		EndDialog(IDOK);
		return;
	}
	CheckDlgButton(IDC_EVENTBOX_SEARCHTIME_ALL, FALSE);
}

BOOL CEventBoxSearchTimeDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_EVENTBOXSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CEventBoxSearchTimeDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_EVENTBOXSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CEventBoxSearchCategoryDialog dialog

IMPLEMENT_DYNCREATE(CEventBoxSearchCategoryDialog, CDisplayDialog)

CEventBoxSearchCategoryDialog::CEventBoxSearchCategoryDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CEventBoxSearchCategoryDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CEventBoxSearchCategoryDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CEventBoxSearchCategoryDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CEventBoxWnd *CEventBoxSearchCategoryDialog::GetParent() CONST
{
	return((CEventBoxWnd *)CDisplayDialog::GetParent());
}

void CEventBoxSearchCategoryDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEventBoxSearchCategoryDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEventBoxSearchCategoryDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CEventBoxSearchCategoryDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_EVENTBOX_SEARCHCATEGORY_FIND, OnFindCategory)
	ON_BN_CLICKED(IDC_EVENTBOX_SEARCHCATEGORY_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventBoxSearchCategoryDialog message handlers

BOOL CEventBoxSearchCategoryDialog::OnInitDialog()
{
	INT  nCategory;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (nCategory = MINLOCALEVENTCATEGORY; nCategory <= MAXLOCALEVENTCATEGORY; nCategory++)
	{
		SendDlgItemMessage(IDC_EVENTBOX_SEARCHCATEGORY_CATEGORY, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)STRING(nCategory));
		continue;
	}
	if (SendDlgItemMessage(IDC_EVENTBOX_SEARCHCATEGORY_CATEGORY, CB_GETCOUNT) == MAXLOCALEVENTCATEGORY - MINLOCALEVENTCATEGORY + 1)
	{
		SendDlgItemMessage(IDC_EVENTBOX_SEARCHCATEGORY_CATEGORY, CB_SELECTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_EVENTCATEGORY_USER));
		CheckDlgButton(IDC_EVENTBOX_SEARCHCATEGORY_ALL, TRUE);
		CheckDlgButton(IDC_EVENTBOX_SEARCHCATEGORY_DIRECTION_DOWN, TRUE);
		GetDlgItem(IDC_EVENTBOX_SEARCHCATEGORY_CATEGORY_STATIC)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SEARCHCATEGORY_CATEGORY)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SEARCHCATEGORY_DIRECTION)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SEARCHCATEGORY_DIRECTION_UP)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SEARCHCATEGORY_DIRECTION_DOWN)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SEARCHCATEGORY_ALL)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SEARCHCATEGORY_FIND)->EnableWindow();
	}
	return TRUE;
}

void CEventBoxSearchCategoryDialog::OnFindCategory()
{
	UINT  nCategory;
	CHourglassCursor  cCursor;

	for (nCategory = (SendDlgItemMessage(IDC_EVENTBOX_SEARCHCATEGORY_CATEGORY, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_EVENTCATEGORY_SYSTEM)) == SendDlgItemMessage(IDC_EVENTBOX_SEARCHCATEGORY_CATEGORY, CB_GETCURSEL)) ? EVENT_CATEGORY_SYSTEM : 0, nCategory = (SendDlgItemMessage(IDC_EVENTBOX_SEARCHCATEGORY_CATEGORY, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_EVENTCATEGORY_SPACECRAFT)) == SendDlgItemMessage(IDC_EVENTBOX_SEARCHCATEGORY_CATEGORY, CB_GETCURSEL)) ? EVENT_CATEGORY_SPACECRAFT : nCategory, nCategory = (SendDlgItemMessage(IDC_EVENTBOX_SEARCHCATEGORY_CATEGORY, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_EVENTCATEGORY_USER)) == SendDlgItemMessage(IDC_EVENTBOX_SEARCHCATEGORY_CATEGORY, CB_GETCURSEL)) ? EVENT_CATEGORY_USER : nCategory; !GetParent()->SearchEventByCategory(nCategory, IsDlgButtonChecked(IDC_EVENTBOX_SEARCHCATEGORY_DIRECTION_DOWN), IsDlgButtonChecked(IDC_EVENTBOX_SEARCHCATEGORY_ALL)); )
	{
		ReportEvent(USER_INFORMATIONAL_EVENTBOX_SEARCH_CATEGORY_NOTHING);
		EndDialog(IDOK);
		return;
	}
	CheckDlgButton(IDC_EVENTBOX_SEARCHCATEGORY_ALL, FALSE);
}

BOOL CEventBoxSearchCategoryDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_EVENTBOXSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CEventBoxSearchCategoryDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_EVENTBOXSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CEventBoxSearchTypeDialog dialog

IMPLEMENT_DYNCREATE(CEventBoxSearchTypeDialog, CDisplayDialog)

CEventBoxSearchTypeDialog::CEventBoxSearchTypeDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CEventBoxSearchTypeDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CEventBoxSearchTypeDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CEventBoxSearchTypeDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CEventBoxWnd *CEventBoxSearchTypeDialog::GetParent() CONST
{
	return((CEventBoxWnd *)CDisplayDialog::GetParent());
}

void CEventBoxSearchTypeDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEventBoxSearchTypeDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEventBoxSearchTypeDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CEventBoxSearchTypeDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_EVENTBOX_SEARCHTYPE_FIND, OnFindType)
	ON_BN_CLICKED(IDC_EVENTBOX_SEARCHTYPE_HELP, OnHelp)
	ON_CBN_EDITCHANGE(IDC_EVENTBOX_SEARCHTYPE_TYPE, OnEditchangeType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventBoxSearchTypeDialog message handlers

BOOL CEventBoxSearchTypeDialog::OnInitDialog()
{
	INT  nType;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (nType = MINEVENTTYPE; nType <= MAXEVENTTYPE; nType++)
	{
		SendDlgItemMessage(IDC_EVENTBOX_SEARCHTYPE_TYPE, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)STRING(nType));
		continue;
	}
	if (SendDlgItemMessage(IDC_EVENTBOX_SEARCHTYPE_TYPE, CB_GETCOUNT) == MAXEVENTTYPE - MINEVENTTYPE + 1)
	{
		SendDlgItemMessage(IDC_EVENTBOX_SEARCHTYPE_TYPE, CB_SELECTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_EVENTTYPE_SCHEDULED));
		CheckDlgButton(IDC_EVENTBOX_SEARCHTYPE_ALL, TRUE);
		CheckDlgButton(IDC_EVENTBOX_SEARCHTYPE_DIRECTION_DOWN, TRUE);
		GetDlgItem(IDC_EVENTBOX_SEARCHTYPE_TYPE_STATIC)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SEARCHTYPE_TYPE)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SEARCHTYPE_DIRECTION)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SEARCHTYPE_DIRECTION_UP)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SEARCHTYPE_DIRECTION_DOWN)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SEARCHTYPE_ALL)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SEARCHTYPE_CASE)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_SEARCHTYPE_FIND)->EnableWindow();
	}
	return TRUE;
}

void CEventBoxSearchTypeDialog::OnFindType()
{
	CString  szType;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_EVENTBOX_SEARCHTYPE_TYPE)->GetWindowText(szType);
	if (!GetParent()->SearchEventByType(szType, IsDlgButtonChecked(IDC_EVENTBOX_SEARCHTYPE_DIRECTION_DOWN), IsDlgButtonChecked(IDC_EVENTBOX_SEARCHTYPE_ALL), IsDlgButtonChecked(IDC_EVENTBOX_SEARCHTYPE_CASE)))
	{
		ReportEvent(USER_INFORMATIONAL_EVENTBOX_SEARCH_TYPE_NOTHING);
		EndDialog(IDOK);
		return;
	}
	CheckDlgButton(IDC_EVENTBOX_SEARCHTYPE_ALL, FALSE);
}

void CEventBoxSearchTypeDialog::OnEditchangeType()
{
	GetDlgItem(IDC_EVENTBOX_SEARCHTYPE_FIND)->EnableWindow((GetDlgItem(IDC_EVENTBOX_SEARCHTYPE_TYPE)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

BOOL CEventBoxSearchTypeDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_EVENTBOXSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CEventBoxSearchTypeDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_EVENTBOXSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CEventBoxSearchMessageDialog dialog

IMPLEMENT_DYNCREATE(CEventBoxSearchMessageDialog, CDisplayDialog)

CEventBoxSearchMessageDialog::CEventBoxSearchMessageDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CEventBoxSearchMessageDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CEventBoxSearchMessageDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CEventBoxSearchMessageDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CEventBoxWnd *CEventBoxSearchMessageDialog::GetParent() CONST
{
	return((CEventBoxWnd *)CDisplayDialog::GetParent());
}

void CEventBoxSearchMessageDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEventBoxSearchMessageDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEventBoxSearchMessageDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CEventBoxSearchMessageDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_EVENTBOX_SEARCHMESSAGE_FIND, OnFindMessage)
	ON_BN_CLICKED(IDC_EVENTBOX_SEARCHMESSAGE_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_EVENTBOX_SEARCHMESSAGE_MESSAGE, OnSelchangeMessage)
	ON_CBN_EDITCHANGE(IDC_EVENTBOX_SEARCHMESSAGE_MESSAGE, OnEditchangeMessage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventBoxSearchMessageDialog message handlers

BOOL CEventBoxSearchMessageDialog::OnInitDialog()
{
	INT  nItem;
	INT  nItems;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (nItem = 0, nItems = (INT)m_szMessages.GetSize(); nItem < nItems; nItem++)
	{
		SendDlgItemMessage(IDC_EVENTBOX_SEARCHMESSAGE_MESSAGE, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)m_szMessages.GetAt(nItem));
		continue;
	}
	CheckDlgButton(IDC_EVENTBOX_SEARCHMESSAGE_ALL, TRUE);
	CheckDlgButton(IDC_EVENTBOX_SEARCHMESSAGE_DIRECTION_DOWN, TRUE);
	GetDlgItem(IDC_EVENTBOX_SEARCHMESSAGE_MESSAGE_STATIC)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_SEARCHMESSAGE_MESSAGE)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_SEARCHMESSAGE_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_SEARCHMESSAGE_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_SEARCHMESSAGE_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_SEARCHMESSAGE_ALL)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_SEARCHMESSAGE_CASE)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_SEARCHMESSAGE_WORD)->EnableWindow();
	return TRUE;
}

void CEventBoxSearchMessageDialog::OnFindMessage()
{
	CString  szMessage;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_EVENTBOX_SEARCHMESSAGE_MESSAGE)->GetWindowText(szMessage);
	if (SendDlgItemMessage(IDC_EVENTBOX_SEARCHMESSAGE_MESSAGE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szMessage) == CB_ERR)
	{
		SendDlgItemMessage(IDC_EVENTBOX_SEARCHMESSAGE_MESSAGE, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szMessage);
		m_szMessages.Add(szMessage);
	}
	if (!GetParent()->SearchEventByMessage(szMessage, IsDlgButtonChecked(IDC_EVENTBOX_SEARCHMESSAGE_DIRECTION_DOWN), IsDlgButtonChecked(IDC_EVENTBOX_SEARCHMESSAGE_ALL), IsDlgButtonChecked(IDC_EVENTBOX_SEARCHMESSAGE_CASE), IsDlgButtonChecked(IDC_EVENTBOX_SEARCHMESSAGE_WORD)))
	{
		ReportEvent(USER_INFORMATIONAL_EVENTBOX_SEARCH_MESSAGE_NOTHING);
		EndDialog(IDOK);
		return;
	}
	CheckDlgButton(IDC_EVENTBOX_SEARCHMESSAGE_ALL, FALSE);
}

void CEventBoxSearchMessageDialog::OnSelchangeMessage()
{
	GetDlgItem(IDC_EVENTBOX_SEARCHMESSAGE_FIND)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_SEARCHMESSAGE_MESSAGE, CB_GETCURSEL) != CB_ERR) ? TRUE : FALSE);
}

void CEventBoxSearchMessageDialog::OnEditchangeMessage()
{
	GetDlgItem(IDC_EVENTBOX_SEARCHMESSAGE_FIND)->EnableWindow((GetDlgItem(IDC_EVENTBOX_SEARCHMESSAGE_MESSAGE)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

BOOL CEventBoxSearchMessageDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_EVENTBOXSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CEventBoxSearchMessageDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_EVENTBOXSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CEventBoxSearchCommentsDialog dialog

IMPLEMENT_DYNCREATE(CEventBoxSearchCommentsDialog, CDisplayDialog)

CEventBoxSearchCommentsDialog::CEventBoxSearchCommentsDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CEventBoxSearchCommentsDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CEventBoxSearchCommentsDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CEventBoxSearchCommentsDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CEventBoxWnd *CEventBoxSearchCommentsDialog::GetParent() CONST
{
	return((CEventBoxWnd *)CDisplayDialog::GetParent());
}

void CEventBoxSearchCommentsDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEventBoxSearchCommentsDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEventBoxSearchCommentsDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CEventBoxSearchCommentsDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_EVENTBOX_SEARCHCOMMENTS_FIND, OnFindComments)
	ON_BN_CLICKED(IDC_EVENTBOX_SEARCHCOMMENTS_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_EVENTBOX_SEARCHCOMMENTS_COMMENTS, OnSelchangeComments)
	ON_CBN_EDITCHANGE(IDC_EVENTBOX_SEARCHCOMMENTS_COMMENTS, OnEditchangeComments)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventBoxSearchCommentsDialog message handlers

BOOL CEventBoxSearchCommentsDialog::OnInitDialog()
{
	INT  nItem;
	INT  nItems;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (nItem = 0, nItems = (INT)m_szComments.GetSize(); nItem < nItems; nItem++)
	{
		SendDlgItemMessage(IDC_EVENTBOX_SEARCHCOMMENTS_COMMENTS, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)m_szComments.GetAt(nItem));
		continue;
	}
	CheckDlgButton(IDC_EVENTBOX_SEARCHCOMMENTS_ALL, TRUE);
	CheckDlgButton(IDC_EVENTBOX_SEARCHCOMMENTS_DIRECTION_DOWN, TRUE);
	GetDlgItem(IDC_EVENTBOX_SEARCHCOMMENTS_COMMENTS_STATIC)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_SEARCHCOMMENTS_COMMENTS)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_SEARCHCOMMENTS_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_SEARCHCOMMENTS_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_SEARCHCOMMENTS_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_SEARCHCOMMENTS_ALL)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_SEARCHCOMMENTS_CASE)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_SEARCHCOMMENTS_WORD)->EnableWindow();
	return TRUE;
}

void CEventBoxSearchCommentsDialog::OnFindComments()
{
	CString  szComments;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_EVENTBOX_SEARCHCOMMENTS_COMMENTS)->GetWindowText(szComments);
	if (SendDlgItemMessage(IDC_EVENTBOX_SEARCHCOMMENTS_COMMENTS, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szComments) == CB_ERR)
	{
		SendDlgItemMessage(IDC_EVENTBOX_SEARCHCOMMENTS_COMMENTS, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szComments);
		m_szComments.Add(szComments);
	}
	if (!GetParent()->SearchEventByComments(szComments, IsDlgButtonChecked(IDC_EVENTBOX_SEARCHCOMMENTS_DIRECTION_DOWN), IsDlgButtonChecked(IDC_EVENTBOX_SEARCHCOMMENTS_ALL), IsDlgButtonChecked(IDC_EVENTBOX_SEARCHCOMMENTS_CASE), IsDlgButtonChecked(IDC_EVENTBOX_SEARCHCOMMENTS_WORD)))
	{
		ReportEvent(USER_INFORMATIONAL_EVENTBOX_SEARCH_COMMENTS_NOTHING);
		EndDialog(IDOK);
		return;
	}
	CheckDlgButton(IDC_EVENTBOX_SEARCHCOMMENTS_ALL, FALSE);
}

void CEventBoxSearchCommentsDialog::OnSelchangeComments()
{
	GetDlgItem(IDC_EVENTBOX_SEARCHCOMMENTS_FIND)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_SEARCHCOMMENTS_COMMENTS, CB_GETCURSEL) != CB_ERR) ? TRUE : FALSE);
}

void CEventBoxSearchCommentsDialog::OnEditchangeComments()
{
	GetDlgItem(IDC_EVENTBOX_SEARCHCOMMENTS_FIND)->EnableWindow((GetDlgItem(IDC_EVENTBOX_SEARCHCOMMENTS_COMMENTS)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

BOOL CEventBoxSearchCommentsDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_EVENTBOXSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CEventBoxSearchCommentsDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_EVENTBOXSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CEventBoxSearchRecipientsDialog dialog

IMPLEMENT_DYNCREATE(CEventBoxSearchRecipientsDialog, CDisplayDialog)

CEventBoxSearchRecipientsDialog::CEventBoxSearchRecipientsDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CEventBoxSearchRecipientsDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CEventBoxSearchRecipientsDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CEventBoxSearchRecipientsDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CEventBoxWnd *CEventBoxSearchRecipientsDialog::GetParent() CONST
{
	return((CEventBoxWnd *)CDisplayDialog::GetParent());
}

void CEventBoxSearchRecipientsDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEventBoxSearchRecipientsDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEventBoxSearchRecipientsDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CEventBoxSearchRecipientsDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_EVENTBOX_SEARCHRECIPIENTS_FIND, OnFindRecipient)
	ON_BN_CLICKED(IDC_EVENTBOX_SEARCHRECIPIENTS_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_EVENTBOX_SEARCHRECIPIENTS_RECIPIENT, OnSelchangeRecipient)
	ON_CBN_EDITCHANGE(IDC_EVENTBOX_SEARCHRECIPIENTS_RECIPIENT, OnEditchangeRecipient)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventBoxSearchRecipientsDialog message handlers

BOOL CEventBoxSearchRecipientsDialog::OnInitDialog()
{
	INT  nItem;
	INT  nItems;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (nItem = 0, nItems = (INT)m_szRecipients.GetSize(); nItem < nItems; nItem++)
	{
		SendDlgItemMessage(IDC_EVENTBOX_SEARCHRECIPIENTS_RECIPIENT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)m_szRecipients.GetAt(nItem));
		continue;
	}
	CheckDlgButton(IDC_EVENTBOX_SEARCHRECIPIENTS_ALL, TRUE);
	CheckDlgButton(IDC_EVENTBOX_SEARCHRECIPIENTS_DIRECTION_DOWN, TRUE);
	GetDlgItem(IDC_EVENTBOX_SEARCHRECIPIENTS_RECIPIENT_STATIC)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_SEARCHRECIPIENTS_RECIPIENT)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_SEARCHRECIPIENTS_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_SEARCHRECIPIENTS_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_SEARCHRECIPIENTS_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_SEARCHRECIPIENTS_ALL)->EnableWindow();
	return TRUE;
}

void CEventBoxSearchRecipientsDialog::OnFindRecipient()
{
	CString  szRecipient;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_EVENTBOX_SEARCHRECIPIENTS_RECIPIENT)->GetWindowText(szRecipient);
	if (SendDlgItemMessage(IDC_EVENTBOX_SEARCHRECIPIENTS_RECIPIENT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szRecipient) == CB_ERR)
	{
		SendDlgItemMessage(IDC_EVENTBOX_SEARCHRECIPIENTS_RECIPIENT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szRecipient);
		m_szRecipients.Add(szRecipient);
	}
	if (!GetParent()->SearchEventByRecipient(szRecipient, IsDlgButtonChecked(IDC_EVENTBOX_SEARCHRECIPIENTS_DIRECTION_DOWN), IsDlgButtonChecked(IDC_EVENTBOX_SEARCHRECIPIENTS_ALL)))
	{
		ReportEvent(USER_INFORMATIONAL_EVENTBOX_SEARCH_RECIPIENTS_NOTHING);
		EndDialog(IDOK);
		return;
	}
	CheckDlgButton(IDC_EVENTBOX_SEARCHRECIPIENTS_ALL, FALSE);
}

void CEventBoxSearchRecipientsDialog::OnSelchangeRecipient()
{
	GetDlgItem(IDC_EVENTBOX_SEARCHRECIPIENTS_FIND)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_SEARCHRECIPIENTS_RECIPIENT, CB_GETCURSEL) != CB_ERR) ? TRUE : FALSE);
}

void CEventBoxSearchRecipientsDialog::OnEditchangeRecipient()
{
	GetDlgItem(IDC_EVENTBOX_SEARCHRECIPIENTS_FIND)->EnableWindow((GetDlgItem(IDC_EVENTBOX_SEARCHRECIPIENTS_RECIPIENT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

BOOL CEventBoxSearchRecipientsDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_EVENTBOXSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CEventBoxSearchRecipientsDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_EVENTBOXSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CEventBoxSearchUserDialog dialog

IMPLEMENT_DYNCREATE(CEventBoxSearchUserDialog, CDisplayDialog)

CEventBoxSearchUserDialog::CEventBoxSearchUserDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CEventBoxSearchUserDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CEventBoxSearchUserDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, CEventBoxSearchUserDialog::IDD)) = IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

CEventBoxWnd *CEventBoxSearchUserDialog::GetParent() CONST
{
	return((CEventBoxWnd *)CDisplayDialog::GetParent());
}

void CEventBoxSearchUserDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEventBoxSearchUserDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEventBoxSearchUserDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CEventBoxSearchUserDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_EVENTBOX_SEARCHUSER_FIND, OnFindUser)
	ON_BN_CLICKED(IDC_EVENTBOX_SEARCHUSER_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_EVENTBOX_SEARCHUSER_USER, OnSelchangeUser)
	ON_CBN_EDITCHANGE(IDC_EVENTBOX_SEARCHUSER_USER, OnEditchangeUser)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventBoxSearchUserDialog message handlers

BOOL CEventBoxSearchUserDialog::OnInitDialog()
{
	INT  nItem;
	INT  nItems;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (nItem = 0, nItems = (INT)m_szUsers.GetSize(); nItem < nItems; nItem++)
	{
		SendDlgItemMessage(IDC_EVENTBOX_SEARCHUSER_USER, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)m_szUsers.GetAt(nItem));
		continue;
	}
	CheckDlgButton(IDC_EVENTBOX_SEARCHUSER_ALL, TRUE);
	CheckDlgButton(IDC_EVENTBOX_SEARCHUSER_DIRECTION_DOWN, TRUE);
	GetDlgItem(IDC_EVENTBOX_SEARCHUSER_USER_STATIC)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_SEARCHUSER_USER)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_SEARCHUSER_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_SEARCHUSER_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_SEARCHUSER_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_EVENTBOX_SEARCHUSER_ALL)->EnableWindow();
	return TRUE;
}

void CEventBoxSearchUserDialog::OnFindUser()
{
	CString  szUser;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_EVENTBOX_SEARCHUSER_USER)->GetWindowText(szUser);
	if (SendDlgItemMessage(IDC_EVENTBOX_SEARCHUSER_USER, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szUser) == CB_ERR)
	{
		SendDlgItemMessage(IDC_EVENTBOX_SEARCHUSER_USER, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szUser);
		m_szUsers.Add(szUser);
	}
	if (!GetParent()->SearchEventByUser(szUser, IsDlgButtonChecked(IDC_EVENTBOX_SEARCHUSER_DIRECTION_DOWN), IsDlgButtonChecked(IDC_EVENTBOX_SEARCHUSER_ALL)))
	{
		ReportEvent(USER_INFORMATIONAL_EVENTBOX_SEARCH_USER_NOTHING);
		EndDialog(IDOK);
		return;
	}
	CheckDlgButton(IDC_EVENTBOX_SEARCHUSER_ALL, FALSE);
}

void CEventBoxSearchUserDialog::OnSelchangeUser()
{
	GetDlgItem(IDC_EVENTBOX_SEARCHUSER_FIND)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_SEARCHUSER_USER, CB_GETCURSEL) != CB_ERR) ? TRUE : FALSE);
}

void CEventBoxSearchUserDialog::OnEditchangeUser()
{
	GetDlgItem(IDC_EVENTBOX_SEARCHUSER_FIND)->EnableWindow((GetDlgItem(IDC_EVENTBOX_SEARCHUSER_USER)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

BOOL CEventBoxSearchUserDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_EVENTBOXSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CEventBoxSearchUserDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_EVENTBOXSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CEventBoxOpenDialog dialog

IMPLEMENT_DYNCREATE(CEventBoxOpenDialog, CDisplayDialog)

CEventBoxOpenDialog::CEventBoxOpenDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CEventBoxOpenDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CEventBoxOpenDialog::Create(CWnd *pParentWnd)
{
	return CDisplayDialog::Create(pParentWnd, CEventBoxOpenDialog::IDD);
}

BOOL CEventBoxOpenDialog::Initialize()
{
	m_nFilterMode = 0;
	m_nFilterLimit = 0;
	m_nFilterCount = 0;
	m_nRetrieveMode = 0;
	m_nRetrieveLimit = 0;
	m_nLayoutColumns = 0;
	m_bLayoutDefault = FALSE;
	m_tFilterStartTime = 0;
	m_tFilterStopTime = 0;
	m_tRetrieveStartTime = 0;
	m_tRetrieveStopTime = 0;
	ZeroMemory(&m_fntLayoutTitle, sizeof(LOGFONT));
	ZeroMemory(&m_fntLayoutList, sizeof(LOGFONT));
	return TRUE;
}

CString CEventBoxOpenDialog::GetComputerName() CONST
{
	CString  szComputerName;

	GetDlgItem(IDC_EVENTBOX_OPEN_COMPUTERNAME)->GetWindowText(szComputerName);
	return szComputerName;
}

CString CEventBoxOpenDialog::GetSpacecraftName() CONST
{
	CString  szSpacecraftName;

	GetDlgItem(IDC_EVENTBOX_OPEN_SPACECRAFTNAME)->GetWindowText(szSpacecraftName);
	return szSpacecraftName;
}

CString CEventBoxOpenDialog::GetUserName() CONST
{
	CString  szUserName;

	GetDlgItem(IDC_EVENTBOX_OPEN_USERNAME)->GetWindowText(szUserName);
	return szUserName;
}

BOOL CEventBoxOpenDialog::UseGlobal() CONST
{
	return IsDlgButtonChecked(IDC_EVENTBOX_OPEN_GLOBALSPACECRAFTNAME);
}

UINT CEventBoxOpenDialog::GetMode() CONST
{
	return((IsDlgButtonChecked(IDC_EVENTBOX_OPEN_MODE_REALTIME) || IsDlgButtonChecked(IDC_EVENTBOX_OPEN_MODE_HISTORY)) ? (IsDlgButtonChecked(IDC_EVENTBOX_OPEN_MODE_REALTIME)*DISPLAY_MODE_REALTIME + IsDlgButtonChecked(IDC_EVENTBOX_OPEN_MODE_HISTORY)*DISPLAY_MODE_HISTORY) : -1);
}

BOOL CEventBoxOpenDialog::GetLayoutTitle(UINT &nColumns) CONST
{
	if (IsLayoutModified())
	{
		nColumns = m_nLayoutColumns;
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxOpenDialog::GetLayoutTitleFont(LPLOGFONT pTitleFont) CONST
{
	if (IsLayoutModified())
	{
		CopyMemory(pTitleFont, &m_fntLayoutTitle, sizeof(LOGFONT));
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxOpenDialog::GetLayoutListFont(LPLOGFONT pListFont) CONST
{
	if (IsLayoutModified())
	{
		CopyMemory(pListFont, &m_fntLayoutList, sizeof(LOGFONT));
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxOpenDialog::UseLayoutAsDefault() CONST
{
	return m_bLayoutDefault;
}

BOOL CEventBoxOpenDialog::IsLayoutModified() CONST
{
	LOGFONT  fntSample = { 0 };

	return((m_nLayoutColumns != 0 || memcmp(&m_fntLayoutTitle, &fntSample, sizeof(LOGFONT)) || memcmp(&m_fntLayoutList, &fntSample, sizeof(LOGFONT))) ? TRUE : FALSE);
}

BOOL CEventBoxOpenDialog::GetFilterMode(UINT &nMode) CONST
{
	if (IsFilteringModified())
	{
		nMode = (GetMode() == DISPLAY_MODE_HISTORY) ? (m_nFilterMode & ~(EVENTBOX_FILTER_AUTOEVENTS | EVENTBOX_FILTER_BRINGEVENTS | EVENTBOX_FILTER_AUTOACKNOWLEDGE | EVENTBOX_FILTER_NOTIFY | EVENTBOX_FILTER_USESOUND)) : m_nFilterMode;
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxOpenDialog::GetFilterBehavior(UINT &nCount) CONST
{
	if (IsFilteringModified())
	{
		if (m_nFilterMode & EVENTBOX_FILTER_AUTOEVENTS)
		{
			nCount = (GetMode() != DISPLAY_MODE_HISTORY) ? m_nFilterCount : 0;
			return TRUE;
		}
	}
	return FALSE;
}
BOOL CEventBoxOpenDialog::GetFilterBehavior(CStringArray &szTypes, CStringArray &szSubtypes) CONST
{
	if (IsFilteringModified())
	{
		szTypes.Copy(m_szFilterTypes);
		szSubtypes.Copy(m_szFilterSubtypes);
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxOpenDialog::GetFilterLimitation(UINT &nLimit) CONST
{
	if (IsFilteringModified())
	{
		if (m_nFilterMode & EVENTBOX_FILTER_LIMITBYEVENTS)
		{
			nLimit = m_nFilterLimit;
			return TRUE;
		}
	}
	return FALSE;
}
BOOL CEventBoxOpenDialog::GetFilterLimitation(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	if (IsFilteringModified())
	{
		if (m_nFilterMode & EVENTBOX_FILTER_LIMITBYTIME)
		{
			tStartTime = m_tFilterStartTime;
			tStopTime = m_tFilterStopTime;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CEventBoxOpenDialog::GetFilterColors(CUIntArray &nColors) CONST
{
	if (IsFilteringModified())
	{
		nColors.Copy(m_nFilterColors);
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxOpenDialog::IsFilteringModified() CONST
{
	return((m_nFilterMode != 0) ? TRUE : FALSE);
}

BOOL CEventBoxOpenDialog::GetRetrieveMode(UINT &nMode) CONST
{
	nMode = m_nRetrieveMode;
	return TRUE;
}

BOOL CEventBoxOpenDialog::GetRetrieveLimit(UINT &nCount) CONST
{
	nCount = m_nRetrieveLimit;
	return((((m_nRetrieveMode & EVENTBOX_RETRIEVE_ALLATONCE) || (m_nRetrieveMode & EVENTBOX_RETRIEVE_PSEUDOREALTIME) || (m_nRetrieveMode & EVENTBOX_RETRIEVE_MANUAL)) && (m_nRetrieveMode & EVENTBOX_RETRIEVE_STOPBYEVENTS)) ? TRUE : FALSE);
}

BOOL CEventBoxOpenDialog::GetRetrieveStartTime(CTimeKey &tTimeKey) CONST
{
	tTimeKey = m_tRetrieveStartTime;
	return(((m_nRetrieveMode & EVENTBOX_RETRIEVE_ALLATONCE) || (m_nRetrieveMode & EVENTBOX_RETRIEVE_PSEUDOREALTIME) || (m_nRetrieveMode & EVENTBOX_RETRIEVE_MANUAL)) ? TRUE : FALSE);
}

BOOL CEventBoxOpenDialog::GetRetrieveStopTime(CTimeKey &tTimeKey) CONST
{
	tTimeKey = m_tRetrieveStopTime;
	return((((m_nRetrieveMode & EVENTBOX_RETRIEVE_ALLATONCE) || (m_nRetrieveMode & EVENTBOX_RETRIEVE_PSEUDOREALTIME) || (m_nRetrieveMode & EVENTBOX_RETRIEVE_MANUAL)) && (m_nRetrieveMode & EVENTBOX_RETRIEVE_STOPBYTIME)) ? TRUE : FALSE);
}

BOOL CEventBoxOpenDialog::IsRetrievingModified() CONST
{
	return((m_nRetrieveMode != 0) ? TRUE : FALSE);
}

BOOL CEventBoxOpenDialog::GetPrintJobs(CEventBoxPrintJobs &pPrintJobs) CONST
{
	CByteArray  nPrintInfo;

	return((IsPrintingModified()) ? pPrintJobs.Copy(&m_pPrintJobs) : pPrintJobs.Unmap(nPrintInfo));
}

BOOL CEventBoxOpenDialog::IsPrintingModified() CONST
{
	return((m_pPrintJobs.GetSize() > 0) ? TRUE : FALSE);
}

CEventBoxWnd *CEventBoxOpenDialog::GetParent() CONST
{
	return((CEventBoxWnd *)CDisplayDialog::GetParent());
}

BOOL CEventBoxOpenDialog::EnumComputers()
{
	INT  nComputer;
	INT  nComputers;
	CString  szComputer;
	CStringArray  szComputers;
	CComputerToken  cComputerToken;

	for (szComputer = cComputerToken.GetComputerName(), szComputers.Add(szComputer); CheckAccountPrivilege(PRIVILEGE_COMPUTERLOGS_VIEW); )
	{
		GetNetworkBrowseService()->EnumNetworkComputers(szComputers);
		break;
	}
	for (nComputer = 0, nComputers = (INT)szComputers.GetSize(), SendDlgItemMessage(IDC_EVENTBOX_OPEN_COMPUTERNAME, CB_RESETCONTENT); nComputer < nComputers; nComputer++)
	{
		if (CheckAccountPrivilege(PRIVILEGE_EVENTBOX_USE) || CheckAccountPrivilege(PRIVILEGE_COMPUTERLOGS_VIEW) || CheckAccountPrivilege(PRIVILEGE_SPACECRAFTLOGS_VIEW) || CheckAccountPrivilege(PRIVILEGE_USERLOGS_VIEW))
		{
			SendDlgItemMessage(IDC_EVENTBOX_OPEN_COMPUTERNAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szComputers.GetAt(nComputer));
			continue;
		}
	}
	SendDlgItemMessage(IDC_EVENTBOX_OPEN_COMPUTERNAME, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_EVENTBOX_OPEN_COMPUTERNAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szComputer), 0));
	GetDlgItem(IDC_EVENTBOX_OPEN_COMPUTERNAME_STATIC)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_OPEN_COMPUTERNAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_EVENTBOX_OPEN_COMPUTERNAME)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_OPEN_COMPUTERNAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_EVENTBOX_OPEN_COMPUTERNAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

BOOL CEventBoxOpenDialog::EnumSpacecrafts()
{
	INT  nAccount;
	INT  nAccounts;
	CString  szComputerName;
	CString  szSpacecraftName;
	CUserAccounts  cUserAccounts;
	CAccountTokens  pAccountTokens;

	GetDlgItem(IDC_EVENTBOX_OPEN_COMPUTERNAME)->GetWindowText(szComputerName);
	for (nAccount = 0, nAccounts = (cUserAccounts.SetComputerName(szComputerName)) ? cUserAccounts.EnumAccounts(pAccountTokens) : 0, SendDlgItemMessage(IDC_EVENTBOX_OPEN_SPACECRAFTNAME, CB_RESETCONTENT); SendDlgItemMessage(IDC_EVENTBOX_OPEN_COMPUTERNAME, CB_GETCOUNT) > 0 && nAccount < nAccounts; nAccount++)
	{
		if (pAccountTokens.GetAt(nAccount)->GetComputerName() == szComputerName && ((szSpacecraftName = pAccountTokens.GetAt(nAccount)->GetSpacecraftName()) == GetAccountSpacecraftName() || CheckAccountPrivilege(PRIVILEGE_SPACECRAFTLOGS_VIEW)))
		{
			if (SendDlgItemMessage(IDC_EVENTBOX_OPEN_SPACECRAFTNAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szSpacecraftName) == CB_ERR)
			{
				SendDlgItemMessage(IDC_EVENTBOX_OPEN_SPACECRAFTNAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szSpacecraftName);
				continue;
			}
		}
	}
	for (SendDlgItemMessage(IDC_EVENTBOX_OPEN_SPACECRAFTNAME, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_EVENTBOX_OPEN_SPACECRAFTNAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)GetAccountSpacecraftName()), 0)), GetDlgItem(IDC_EVENTBOX_OPEN_SPACECRAFTNAME_STATIC)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_OPEN_SPACECRAFTNAME, CB_GETCOUNT) > 0) ? TRUE : FALSE), GetDlgItem(IDC_EVENTBOX_OPEN_SPACECRAFTNAME)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_OPEN_SPACECRAFTNAME, CB_GETCOUNT) > 0) ? TRUE : FALSE), CheckDlgButton(IDC_EVENTBOX_OPEN_GLOBALSPACECRAFTNAME, (SendDlgItemMessage(IDC_EVENTBOX_OPEN_SPACECRAFTNAME, CB_GETCOUNT) > 0) ? (IsDlgButtonChecked(IDC_EVENTBOX_OPEN_GLOBALSPACECRAFTNAME) || !CheckAccountPrivilege(PRIVILEGE_OFFLINE_OPERATE)) : FALSE), GetDlgItem(IDC_EVENTBOX_OPEN_GLOBALSPACECRAFTNAME)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_OPEN_SPACECRAFTNAME, CB_GETCOUNT) > 0) ? TRUE : FALSE); !nAccounts; )
	{
		SendDlgItemMessage(IDC_EVENTBOX_OPEN_COMPUTERNAME, CB_SETEDITSEL, (WPARAM)NULL, MAKELPARAM(0, -1));
		break;
	}
	return((SendDlgItemMessage(IDC_EVENTBOX_OPEN_SPACECRAFTNAME, CB_GETCOUNT) >= 0) ? TRUE : FALSE);
}

BOOL CEventBoxOpenDialog::EnumUsers()
{
	INT  nAccount;
	INT  nAccounts;
	CString  szUserName;
	CString  szComputerName;
	CString  szSpacecraftName;
	CUserAccounts  cUserAccounts;
	CAccountTokens  pAccountTokens;

	GetDlgItem(IDC_EVENTBOX_OPEN_COMPUTERNAME)->GetWindowText(szComputerName);
	for (nAccount = 0, nAccounts = (cUserAccounts.SetComputerName(szComputerName)) ? cUserAccounts.EnumAccounts(pAccountTokens) : 0, GetDlgItem(IDC_EVENTBOX_OPEN_SPACECRAFTNAME)->GetWindowText(szSpacecraftName), SendDlgItemMessage(IDC_EVENTBOX_OPEN_USERNAME, CB_RESETCONTENT); SendDlgItemMessage(IDC_EVENTBOX_OPEN_COMPUTERNAME, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_EVENTBOX_OPEN_SPACECRAFTNAME, CB_GETCOUNT) > 0 && nAccount < nAccounts; nAccount++)
	{
		if (pAccountTokens.GetAt(nAccount)->GetComputerName() == szComputerName  &&  pAccountTokens.GetAt(nAccount)->GetSpacecraftName() == szSpacecraftName && ((szUserName = pAccountTokens.GetAt(nAccount)->GetUserName()) == GetAccountUserName() || CheckAccountPrivilege(PRIVILEGE_USERLOGS_VIEW)))
		{
			if (SendDlgItemMessage(IDC_EVENTBOX_OPEN_USERNAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szUserName) == CB_ERR)
			{
				SendDlgItemMessage(IDC_EVENTBOX_OPEN_USERNAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szUserName);
				continue;
			}
		}
	}
	SendDlgItemMessage(IDC_EVENTBOX_OPEN_USERNAME, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_EVENTBOX_OPEN_USERNAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)GetAccountUserName()), 0));
	GetDlgItem(IDC_EVENTBOX_OPEN_SETTINGS)->EnableWindow((GetDlgItem(IDC_EVENTBOX_OPEN_COMPUTERNAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_EVENTBOX_OPEN_SPACECRAFTNAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_EVENTBOX_OPEN_USERNAME)->GetWindowTextLength() > 0 && (GetMode() != DISPLAY_MODE_REALTIME || !GetParent()->Find(GetMode(), GetComputerName(), GetSpacecraftName(), GetUserName(), UseGlobal()))) ? TRUE : FALSE);
	GetDlgItem(IDC_EVENTBOX_OPEN_USERNAME_STATIC)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_OPEN_USERNAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_EVENTBOX_OPEN_USERNAME)->EnableWindow((SendDlgItemMessage(IDC_EVENTBOX_OPEN_USERNAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_EVENTBOX_OPEN_USERNAME, CB_GETCOUNT) >= 0) ? TRUE : FALSE);
}

BOOL CEventBoxOpenDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_EVENTBOX_OPEN_COMPUTERNAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_EVENTBOX_OPEN_SPACECRAFTNAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_EVENTBOX_OPEN_USERNAME)->GetWindowTextLength() > 0 && (IsDlgButtonChecked(IDC_EVENTBOX_OPEN_MODE_REALTIME) || (IsDlgButtonChecked(IDC_EVENTBOX_OPEN_MODE_HISTORY) && IsRetrievingModified()))) ? TRUE : FALSE);
}

void CEventBoxOpenDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEventBoxOpenDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CEventBoxOpenDialog::PostNcDestroy()
{
	m_pPrintJobs.RemoveAll();
	m_nFilterColors.RemoveAll();
	m_szFilterTypes.RemoveAll();
	m_szFilterSubtypes.RemoveAll();
	CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CEventBoxOpenDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CEventBoxOpenDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_EVENTBOX_OPEN_CONNECT, OnConnectComputer)
	ON_BN_CLICKED(IDC_EVENTBOX_OPEN_SETTINGS, OnSettings)
	ON_BN_CLICKED(IDC_EVENTBOX_OPEN_GLOBALSPACECRAFTNAME, OnGlobalEventlog)
	ON_BN_CLICKED(IDC_EVENTBOX_OPEN_MODE_REALTIME, OnRealtimeMode)
	ON_BN_CLICKED(IDC_EVENTBOX_OPEN_MODE_HISTORY, OnHistoryMode)
	ON_BN_CLICKED(IDC_EVENTBOX_OPEN_HELP, OnHelp)
	ON_CBN_EDITCHANGE(IDC_EVENTBOX_OPEN_COMPUTERNAME, OnEditchangeComputerName)
	ON_CBN_SELCHANGE(IDC_EVENTBOX_OPEN_COMPUTERNAME, OnSelchangeComputerName)
	ON_CBN_SELCHANGE(IDC_EVENTBOX_OPEN_SPACECRAFTNAME, OnSelchangeSpacecraftName)
	ON_CBN_SELCHANGE(IDC_EVENTBOX_OPEN_USERNAME, OnSelchangeUserName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventBoxOpenDialog message handlers

BOOL CEventBoxOpenDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	if (EnumComputers() && EnumSpacecrafts() && EnumUsers())
	{
		AccessControl(IDC_EVENTBOX_OPEN_GLOBALSPACECRAFTNAME, CheckAccountPrivilege(PRIVILEGE_OFFLINE_OPERATE));
		CheckDlgButton(IDC_EVENTBOX_OPEN_GLOBALSPACECRAFTNAME, !CheckAccountPrivilege(PRIVILEGE_OFFLINE_OPERATE));
		CheckDlgButton(IDC_EVENTBOX_OPEN_MODE_REALTIME, !CheckAccountPrivilege(PRIVILEGE_OFFLINE_OPERATE));
		CheckDlgButton(IDC_EVENTBOX_OPEN_MODE_HISTORY, FALSE);
		GetDlgItem(IDC_EVENTBOX_OPEN_DETAILS)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_OPEN_GLOBALSPACECRAFTNAME)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_OPEN_MODE)->EnableWindow();
		GetDlgItem(IDC_EVENTBOX_OPEN_MODE_REALTIME)->EnableWindow(!CheckAccountPrivilege(PRIVILEGE_OFFLINE_OPERATE));
		GetDlgItem(IDC_EVENTBOX_OPEN_MODE_HISTORY)->EnableWindow(CheckAccountPrivilege(PRIVILEGE_OFFLINE_OPERATE));
		GetDlgItem(IDOK)->EnableWindow(Check());
	}
	return TRUE;
}

void CEventBoxOpenDialog::OnSelchangeComputerName()
{
	CString  szComputer;
	CComputerToken  cComputerToken;

	for (SendDlgItemMessage(IDC_EVENTBOX_OPEN_COMPUTERNAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_EVENTBOX_OPEN_COMPUTERNAME, CB_GETCURSEL)); EnumSpacecrafts() + EnumUsers() > TRUE; )
	{
		GetDlgItem(IDC_EVENTBOX_OPEN_CONNECT)->EnableWindow((cComputerToken.SetComputerName((szComputer = Combobox_GetText(GetDlgItem(IDC_EVENTBOX_OPEN_COMPUTERNAME), (INT)SendDlgItemMessage(IDC_EVENTBOX_OPEN_COMPUTERNAME, CB_GETCURSEL)))) && !szComputer.IsEmpty() && !cComputerToken.IsHost() && SendDlgItemMessage(IDC_EVENTBOX_OPEN_COMPUTERNAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szComputer) < 0) ? CheckAccountPrivilege(PRIVILEGE_COMPUTERLOGS_VIEW) : FALSE);
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxOpenDialog::OnSelchangeSpacecraftName()
{
	EnumUsers();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxOpenDialog::OnSelchangeUserName()
{
	GetDlgItem(IDC_EVENTBOX_OPEN_SETTINGS)->EnableWindow((GetDlgItem(IDC_EVENTBOX_OPEN_COMPUTERNAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_EVENTBOX_OPEN_SPACECRAFTNAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_EVENTBOX_OPEN_USERNAME)->GetWindowTextLength() > 0 && (GetMode() != DISPLAY_MODE_REALTIME || !GetParent()->Find(GetMode(), GetComputerName(), GetSpacecraftName(), GetUserName(), UseGlobal()))) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxOpenDialog::OnEditchangeComputerName()
{
	CString  szComputer;
	CComputerToken  cComputerToken;

	for (GetDlgItem(IDC_EVENTBOX_OPEN_COMPUTERNAME)->GetWindowText(szComputer), GetDlgItem(IDC_EVENTBOX_OPEN_CONNECT)->EnableWindow((cComputerToken.SetComputerName(szComputer) && !szComputer.IsEmpty() && !cComputerToken.IsHost() && SendDlgItemMessage(IDC_EVENTBOX_OPEN_COMPUTERNAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szComputer) < 0) ? CheckAccountPrivilege(PRIVILEGE_COMPUTERLOGS_VIEW) : FALSE); SendDlgItemMessage(IDC_EVENTBOX_OPEN_COMPUTERNAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szComputer) >= 0; )
	{
		EnumSpacecrafts();
		EnumUsers();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxOpenDialog::OnConnectComputer()
{
	CHourglassCursor  cCursor;

	EnumSpacecrafts();
	EnumUsers();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxOpenDialog::OnSettings()
{
	ReportEvent((m_dlgSettings.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CEventBoxOpenDialog::OnGlobalEventlog()
{
	for (GetDlgItem(IDC_EVENTBOX_OPEN_MODE_REALTIME)->EnableWindow(IsDlgButtonChecked(IDC_EVENTBOX_OPEN_GLOBALSPACECRAFTNAME)); !IsDlgButtonChecked(IDC_EVENTBOX_OPEN_GLOBALSPACECRAFTNAME); )
	{
		CheckDlgButton(IDC_EVENTBOX_OPEN_MODE_REALTIME, FALSE);
		CheckDlgButton(IDC_EVENTBOX_OPEN_MODE_HISTORY, TRUE);
		break;
	}
	GetDlgItem(IDC_EVENTBOX_OPEN_SETTINGS)->EnableWindow((GetDlgItem(IDC_EVENTBOX_OPEN_COMPUTERNAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_EVENTBOX_OPEN_SPACECRAFTNAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_EVENTBOX_OPEN_USERNAME)->GetWindowTextLength() > 0 && (GetMode() != DISPLAY_MODE_REALTIME || !GetParent()->Find(GetMode(), GetComputerName(), GetSpacecraftName(), GetUserName(), UseGlobal()))) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxOpenDialog::OnRealtimeMode()
{
	GetDlgItem(IDC_EVENTBOX_OPEN_SETTINGS)->EnableWindow((GetDlgItem(IDC_EVENTBOX_OPEN_COMPUTERNAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_EVENTBOX_OPEN_SPACECRAFTNAME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_EVENTBOX_OPEN_USERNAME)->GetWindowTextLength() > 0 && (GetMode() != DISPLAY_MODE_REALTIME || !GetParent()->Find(GetMode(), GetComputerName(), GetSpacecraftName(), GetUserName(), UseGlobal()))) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CEventBoxOpenDialog::OnHistoryMode()
{
	CString  szUserName;
	CString  szComputerName;
	CString  szSpacecraftName;

	for (GetDlgItem(IDC_EVENTBOX_OPEN_COMPUTERNAME)->GetWindowText(szComputerName), GetDlgItem(IDC_EVENTBOX_OPEN_SPACECRAFTNAME)->GetWindowText(szSpacecraftName), GetDlgItem(IDC_EVENTBOX_OPEN_USERNAME)->GetWindowText(szUserName); IsDlgButtonChecked(IDC_EVENTBOX_OPEN_MODE_HISTORY); )
	{
		for (ReportEvent((m_dlgRetrievals.Create(this, szComputerName, szSpacecraftName, szUserName, !IsDlgButtonChecked(IDC_EVENTBOX_OPEN_GLOBALSPACECRAFTNAME)) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR), GetDlgItem(IDC_EVENTBOX_OPEN_SETTINGS)->EnableWindow((!szComputerName.IsEmpty() && !szSpacecraftName.IsEmpty() && !szUserName.IsEmpty() && (GetMode() != DISPLAY_MODE_REALTIME || !GetParent()->Find(GetMode(), szComputerName, szSpacecraftName, szUserName, UseGlobal()))) ? TRUE : FALSE); SendDlgItemMessage(IDC_EVENTBOX_OPEN_COMPUTERNAME, CB_GETCOUNT) > 0; )
		{
			GetDlgItem(IDC_EVENTBOX_OPEN_COMPUTERNAME)->SetFocus();
			break;
		}
		if (IsDlgButtonChecked(IDC_EVENTBOX_OPEN_MODE_REALTIME))
		{
			GetDlgItem(IDC_EVENTBOX_OPEN_MODE_REALTIME)->EnableWindow();
			GetDlgItem(IDC_EVENTBOX_OPEN_MODE_REALTIME)->SetFocus();
		}
		GetDlgItem(IDOK)->EnableWindow(Check());
		return;
	}
	CheckDlgButton(IDC_EVENTBOX_OPEN_MODE_REALTIME, TRUE);
	CheckDlgButton(IDC_EVENTBOX_OPEN_MODE_HISTORY, FALSE);
	for (GetDlgItem(IDC_EVENTBOX_OPEN_SETTINGS)->EnableWindow((!szComputerName.IsEmpty() && !szSpacecraftName.IsEmpty() && !szUserName.IsEmpty() && (GetMode() != DISPLAY_MODE_REALTIME || !GetParent()->Find(GetMode(), szComputerName, szSpacecraftName, szUserName, UseGlobal()))) ? TRUE : FALSE); SendDlgItemMessage(IDC_EVENTBOX_OPEN_COMPUTERNAME, CB_GETCOUNT) > 0; )
	{
		GetDlgItem(IDC_EVENTBOX_OPEN_COMPUTERNAME)->SetFocus();
		break;
	}
	for (; IsDlgButtonChecked(IDC_EVENTBOX_OPEN_MODE_REALTIME); )
	{
		GetDlgItem(IDC_EVENTBOX_OPEN_MODE_REALTIME)->SetFocus();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

BOOL CEventBoxOpenDialog::OnCloseSettingsDialog(UINT nCode)
{
	if (nCode == IDOK)
	{
		if (m_dlgSettings.IsLayoutModified())
		{
			m_dlgSettings.GetLayoutTitle(m_nLayoutColumns);
			m_dlgSettings.GetLayoutTitleFont(&m_fntLayoutTitle);
			m_dlgSettings.GetLayoutListFont(&m_fntLayoutList);
		}
		if (m_dlgSettings.IsFilteringModified())
		{
			m_dlgSettings.GetFilterMode(m_nFilterMode);
			m_dlgSettings.GetFilterBehavior(m_nFilterCount);
			m_dlgSettings.GetFilterBehavior(m_szFilterTypes, m_szFilterSubtypes);
			m_dlgSettings.GetFilterLimitation(m_nFilterLimit);
			m_dlgSettings.GetFilterLimitation(m_tFilterStartTime, m_tFilterStopTime);
			m_dlgSettings.GetFilterColors(m_nFilterColors);
		}
		if (m_dlgSettings.IsPrintingModified()) m_dlgSettings.GetPrintJobs(m_pPrintJobs);
		m_dlgSettings.UseLayoutAsDefault(m_bLayoutDefault);
	}
	return TRUE;
}

BOOL CEventBoxOpenDialog::OnCloseRetrieveDialog(UINT nCode)
{
	if (nCode == IDOK)
	{
		m_dlgRetrievals.GetMode(m_nRetrieveMode);
		m_dlgRetrievals.GetLimit(m_nRetrieveLimit);
		m_dlgRetrievals.GetStartTime(m_tRetrieveStartTime);
		m_dlgRetrievals.GetStopTime(m_tRetrieveStopTime);
	}
	if (nCode != IDOK || !m_nRetrieveMode)
	{
		CheckDlgButton(IDC_EVENTBOX_OPEN_GLOBALSPACECRAFTNAME, TRUE);
		CheckDlgButton(IDC_EVENTBOX_OPEN_MODE_REALTIME, TRUE);
		CheckDlgButton(IDC_EVENTBOX_OPEN_MODE_HISTORY, FALSE);
	}
	return TRUE;
}

void CEventBoxOpenDialog::OnOK()
{
	CEventBoxWnd  *pEventBoxWnd[2];
	CHourglassCursor  cCursor;

	if ((pEventBoxWnd[0] = GetParent()))
	{
		if (GetMode() == DISPLAY_MODE_REALTIME)
		{
			if ((pEventBoxWnd[1] = pEventBoxWnd[0]->Find(GetMode(), GetComputerName(), GetSpacecraftName(), GetUserName(), UseGlobal())))
			{
				GetDisplayArea()->ActivateDisplay(pEventBoxWnd[1]);
				EndDialog(IDCANCEL);
				return;
			}
		}
		if (!pEventBoxWnd[0]->OnCloseOpenDialog(IDOK))
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

void CEventBoxOpenDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	GetParent()->OnCloseOpenDialog(IDCANCEL);
	CDisplayDialog::OnCancel();
}

BOOL CEventBoxOpenDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_EVENTBOXOPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CEventBoxOpenDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_EVENTBOXOPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CEventScheduleThread

IMPLEMENT_DYNCREATE(CEventScheduleThread, CThread)

BOOL CEventScheduleThread::Start(CEventBoxWnd *pParentWnd, HANDLE hEvent)
{
	m_hEvent = hEvent;
	return CreateThread(pParentWnd);
}

BOOL CEventScheduleThread::Stop()
{
	return((DestroyThread() >= 0) ? TRUE : FALSE);
}

int CEventScheduleThread::Run()
{
	INT  nProcedure;
	INT  nProcedures;
	BOOL  bFlashState[2];
	DWORD  dwWaitCode;
	CString  szMessage;
	CString  szProcedure;
	CTimeKey  tAuditTime;
	STARTUPINFO  sProcess;
	CEventObject  *pEvent;
	CStringArray  szProcedures;
	PROCESS_INFORMATION  sProcessInfo;
	CEventBoxWnd  *pEventBoxWnd = (CEventBoxWnd *)GetThreadInfo();

	for (bFlashState[0] = bFlashState[1] = FALSE, tAuditTime = 0; TRUE; tAuditTime = 0)
	{
		for (pEventBoxWnd->Lock(), pEventBoxWnd->GetEventList()->Lock(), szProcedures.RemoveAll(); (pEvent = new CEventObject); )
		{
			if (pEventBoxWnd->GetEventList()->Schedule(pEvent))
			{
				szProcedure = pEvent->GetProcedure();
				if (pEventBoxWnd->ShowEvent(pEvent))
				{
					if (!szProcedure.IsEmpty()) szProcedures.Add(szProcedure);
					break;
				}
			}
			delete pEvent;
			break;
		}
		for (nProcedure = 0, nProcedures = (INT)szProcedures.GetSize(), ZeroMemory(&sProcess, sizeof(sProcess)), ZeroMemory(&sProcessInfo, sizeof(sProcessInfo)), sProcess.cb = sizeof(sProcess), pEventBoxWnd->GetEventList()->Unlock(), pEventBoxWnd->Unlock(), pEventBoxWnd->FlushAllEvents(); nProcedure < nProcedures; nProcedure++)
		{
			if (!CreateProcess((LPCTSTR)NULL, (LPTSTR)(LPCTSTR)szProcedures.GetAt(nProcedure), (LPSECURITY_ATTRIBUTES)NULL, (LPSECURITY_ATTRIBUTES)NULL, FALSE, 0, (LPVOID)NULL, (LPCTSTR)NULL, &sProcess, &sProcessInfo))
			{
				szMessage.Format(STRING(IDS_EVENTBOX_AUTOMATION_FAILURE), (LPCTSTR)szProcedures.GetAt(nProcedure));
				pEventBoxWnd->ShowEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage, FALSE);
			}
		}
		if (pEventBoxWnd->IsAlerted())
		{
			if (pEventBoxWnd->GetScope() == DISPLAY_SCOPE_GLOBAL  &&  GetMainWnd()->IsIconic())
			{
				pEventBoxWnd->DrawAlertIcon((bFlashState[0] = !bFlashState[0]), TRUE);
				if (Wait(EVENTSCHEDULE_UPDATE_INTERVAL) == WAIT_TIMEOUT) continue;
				break;
			}
			if (bFlashState[0])
			{
				pEventBoxWnd->DrawAlertIcon(FALSE, TRUE);
				bFlashState[0] = FALSE;
			}
			for (; pEventBoxWnd->IsIconic(); )
			{
				pEventBoxWnd->DrawAlertIcon((bFlashState[1] = !bFlashState[1]));
				break;
			}
			if (Wait(EVENTSCHEDULE_UPDATE_INTERVAL) == WAIT_TIMEOUT) continue;
			break;
		}
		if (!pEventBoxWnd->IsAlerted())
		{
			for (; bFlashState[0] == TRUE; )
			{
				pEventBoxWnd->DrawAlertIcon(FALSE, TRUE);
				bFlashState[0] = FALSE;
				break;
			}
			if (bFlashState[1])
			{
				pEventBoxWnd->DrawAlertIcon(FALSE);
				bFlashState[1] = FALSE;
			}
		}
		if (pEventBoxWnd->Lock())
		{
			if (pEventBoxWnd->GetEventList()->Lock())
			{
				for (tAuditTime = ((pEvent = pEventBoxWnd->GetEventList()->GetAt(pEventBoxWnd->GetEventList()->GetScheduleIndex()))) ? pEvent->GetAuditTime() : 0; tAuditTime > 0; )
				{
					tAuditTime += pEventBoxWnd->GetEventList()->GetScheduleOffset().GetTime();
					break;
				}
				tAuditTime = (pEventBoxWnd->CanFlushEvents()) ? ((tAuditTime > 0) ? min(CTimeKey::GetCurrentTime().GetTime() + 1, tAuditTime.GetTime()) : (CTimeKey::GetCurrentTime().GetTime() + 1)) : tAuditTime;
				pEventBoxWnd->GetEventList()->Unlock();
			}
			pEventBoxWnd->Unlock();
		}
		if ((dwWaitCode = Wait(m_hEvent, FALSE, (tAuditTime > 0) ? (DWORD)(1000 * min(max(tAuditTime.GetTime() - CTime::GetCurrentTime().GetTime(), 0), SECONDSPERDAY)) : INFINITE)) != WAIT_TIMEOUT  &&  dwWaitCode != WAIT_OBJECT_0 + 1) break;
	}
	if (bFlashState[0])
	{
		pEventBoxWnd->DrawAlertIcon(FALSE, TRUE);
		bFlashState[0] = FALSE;
	}
	if (bFlashState[1])
	{
		pEventBoxWnd->DrawAlertIcon(FALSE);
		bFlashState[1] = FALSE;
	}
	return 0;
}

BEGIN_MESSAGE_MAP(CEventScheduleThread, CThread)
	//{{AFX_MSG_MAP(CEventScheduleThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventScheduleThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CEventRetrieveThread

IMPLEMENT_DYNCREATE(CEventRetrieveThread, CThread)

CEventRetrieveThread::CEventRetrieveThread() : CThread()
{
	m_nLogs = 0;
	m_nMode = 0;
	m_nLimit = 0;
	m_tStartTime = 0;
	m_tStopTime = 0;
	m_bInit = (HANDLE)NULL;
}

BOOL CEventRetrieveThread::Start(CEventBoxWnd *pParentWnd, HANDLE bInit, UINT nLogs, UINT nMode, UINT nLimit, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, LONG *pbFlag, HANDLE bRetrieve)
{
	m_bInit = bInit;
	m_nLogs = nLogs;
	m_nMode = nMode;
	m_nLimit = nLimit;
	m_pbFlag = pbFlag;
	m_tStartTime = tStartTime;
	m_tStopTime = tStopTime;
	m_bRetrieve = bRetrieve;
	return((ResetEvent(bInit)) ? CreateThread(pParentWnd) : FALSE);
}

BOOL CEventRetrieveThread::Stop()
{
	return((DestroyThread() >= 0) ? TRUE : FALSE);
}

int CEventRetrieveThread::Run()
{
	INT  nItem;
	INT  nItems;
	UINT  nFilterLimit;
	CTimeKey  tFilterTime[2];
	CEventLog  *pEventLog;
	CEventList  cEventList;
	CEventObject  *pEvent;
	CEventBoxWnd  *pEventBoxWnd = (CEventBoxWnd *)GetThreadInfo();

	StartRetrieving();
	for (cEventList.EnableSound(FALSE); (pEventLog = pEventBoxWnd->GetEventLog()); )
	{
		if (pEventLog->Open(GetRetrieveLogs(), CFile::modeRead))
		{
			if ((((GetRetrieveMode() & EVENTBOX_RETRIEVE_STOPBYTIME) && pEventLog->Read(cEventList, (pEventBoxWnd->GetFilterLimitation(tFilterTime[0], tFilterTime[1])) ? CTimeKey(max(tFilterTime[0].GetTime(), GetRetrieveStartTime().GetTime())) : GetRetrieveStartTime(), (pEventBoxWnd->GetFilterLimitation(tFilterTime[0], tFilterTime[1])) ? CTimeKey(min(tFilterTime[1].GetTime(), GetRetrieveStopTime().GetTime())) : GetRetrieveStopTime(), GetRetrieveLogs(), m_hObject)) || ((GetRetrieveMode() & EVENTBOX_RETRIEVE_STOPBYEVENTS) && pEventLog->Read(cEventList, (pEventBoxWnd->GetFilterLimitation(tFilterTime[0], tFilterTime[1])) ? CTimeKey(max(tFilterTime[0].GetTime(), GetRetrieveStartTime().GetTime())) : GetRetrieveStartTime(), -1, GetRetrieveLogs(), m_hObject)) || ((GetRetrieveMode() & EVENTBOX_RETRIEVE_STOPBYEND) && pEventLog->Read(cEventList, (pEventBoxWnd->GetFilterLimitation(tFilterTime[0], tFilterTime[1])) ? CTimeKey(max(tFilterTime[0].GetTime(), GetRetrieveStartTime().GetTime())) : GetRetrieveStartTime(), -1, GetRetrieveLogs(), m_hObject))))
			{
				for (nItem = 0, nItems = (INT)cEventList.GetSize(); nItem < nItems; nItem++)
				{
					if (!(pEvent = cEventList.GetAt(nItem)) || !pEventBoxWnd->DoFilter(pEvent))
					{
						cEventList.Remove(nItem);
						delete pEvent;
						nItems--;
						nItem--;
					}
				}
				if (pEventBoxWnd->GetFilterLimitation(tFilterTime[0], tFilterTime[1]))
				{
					for (nItem = (nItems = (INT)cEventList.GetSize()) - 1; nItem >= 0; nItem--)
					{
						if ((pEvent = cEventList.GetAt(nItem)) && pEvent->GetAuditTime() > tFilterTime[1])
						{
							cEventList.Remove(nItem);
							delete pEvent;
							continue;
						}
						break;
					}
				}
				for (nItem = (nItems = (INT)cEventList.GetSize()) - 1, nFilterLimit = (GetRetrieveMode() & EVENTBOX_RETRIEVE_STOPBYEVENTS) ? ((pEventBoxWnd->GetFilterLimitation(nFilterLimit)) ? min(GetRetrieveLimit(), nFilterLimit) : GetRetrieveLimit()) : ((pEventBoxWnd->GetFilterLimitation(nFilterLimit)) ? nFilterLimit : -1); nItems > (INT)nFilterLimit && nFilterLimit != (UINT)-1; nItems--, nItem--)
				{
					if ((pEvent = cEventList.GetAt(nItem)))
					{
						cEventList.Remove(nItem);
						delete pEvent;
						continue;
					}
					break;
				}
				for (pEventLog->Close(GetRetrieveLogs()); GetRetrieveMode() & EVENTBOX_RETRIEVE_ALLATONCE; )
				{
					ReportEvent(RetrieveAllAtOnce(cEventList));
					break;
				}
				if (GetRetrieveMode() & EVENTBOX_RETRIEVE_MANUAL)
				{
					for (StartRetrieving(TRUE), pEventLog->Close(GetRetrieveLogs()), SetEvent(m_bRetrieve); Wait(m_bRetrieve, FALSE) == WAIT_OBJECT_0 + 1; ResetEvent(m_bRetrieve))
					{
						if (!ReportEvent(RetrieveManual(cEventList))) break;
						continue;
					}
				}
				if (GetRetrieveMode() & EVENTBOX_RETRIEVE_PSEUDOREALTIME) ReportEvent(RetrievePseudoRealtime(cEventList));
			}
			else
			{
				pEventLog->Close(GetRetrieveLogs());
				ReportEvent(SYSTEM_WARNING_EVENTLOG_READ_FAILURE);
			}
		}
		else  ReportEvent(SYSTEM_WARNING_EVENTLOG_OPEN_FAILURE);
		break;
	}
	StopRetrieving((GetRetrieveMode() & EVENTBOX_RETRIEVE_MANUAL) ? TRUE : FALSE);
	pEventBoxWnd->UpdateBars();
	return 0;
}

VOID CEventRetrieveThread::StartRetrieving(BOOL bManual)
{
	POINT  ptCursor;
	CEventBoxWnd  *pEventBoxWnd;

	for (GetCursorPos(&ptCursor), InterlockedExchange(m_pbFlag, (!bManual) ? TRUE : -bManual), SetCursorPos(ptCursor.x, ptCursor.y), SetEvent(m_bInit); (pEventBoxWnd = (CEventBoxWnd *)GetThreadInfo()); )
	{
		pEventBoxWnd->UpdateBars();
		break;
	}
}

VOID CEventRetrieveThread::StopRetrieving(BOOL bManual)
{
	POINT  ptCursor;
	CEventBoxWnd  *pEventBoxWnd;

	for (GetCursorPos(&ptCursor), InterlockedExchange(m_pbFlag, -bManual), SetCursorPos(ptCursor.x, ptCursor.y); (pEventBoxWnd = (CEventBoxWnd *)GetThreadInfo()); )
	{
		pEventBoxWnd->UpdateBars();
		break;
	}
}

EVENT_DESCRIPTOR CEventRetrieveThread::RetrieveAllAtOnce(CEventList &cEventList)
{
	UINT  nCount;
	DWORD  dwWaitCode;
	CEventObject  *pEvent;
	CEventBoxWnd  *pEventBoxWnd = (CEventBoxWnd *)GetThreadInfo();

	if (cEventList.GetSize() > 0)
	{
		for (pEventBoxWnd->GetEventList()->Lock(), pEventBoxWnd->GetEventList()->SetScheduleOffset(0), pEventBoxWnd->GetEventList()->Unlock(), nCount = 0; (dwWaitCode = Wait(0)) == WAIT_TIMEOUT; )
		{
			if ((pEvent = cEventList.GetAt(0)) && cEventList.Remove(0))
			{
				if (!pEventBoxWnd->DoFilter(pEvent))
				{
					delete pEvent;
					continue;
				}
				pEvent->Acknowledge();
				if (pEventBoxWnd->ShowEvent(pEvent, FALSE, FALSE))
				{
					nCount++;
					continue;
				}
				delete pEvent;
			}
			pEventBoxWnd->RefreshAllEvents();
			return((cEventList.GetSize() > 0) ? SYSTEM_WARNING_EVENTLOG_READ_FAILURE : SYSTEM_NOERROR);
		}
		return((dwWaitCode == WAIT_TIMEOUT  &&  !nCount) ? USER_INFORMATIONAL_EVENTLOG_READ_NOTHING : USER_NOERROR);
	}
	return USER_INFORMATIONAL_EVENTLOG_READ_NOTHING;
}

EVENT_DESCRIPTOR CEventRetrieveThread::RetrievePseudoRealtime(CEventList &cEventList)
{
	DWORD  dwWaitCode;
	CTimeKey  tOffset;
	CEventObject  *pEvent;
	CEventBoxWnd  *pEventBoxWnd = (CEventBoxWnd *)GetThreadInfo();

	if (cEventList.GetSize() > 0)
	{
		for (tOffset = 0; (dwWaitCode = Wait(0)) == WAIT_TIMEOUT; )
		{
			if ((pEvent = cEventList.GetAt(0)) && cEventList.Remove(0))
			{
				if (!pEventBoxWnd->DoFilter(pEvent))
				{
					delete pEvent;
					continue;
				}
				for (pEvent->Acknowledge(); tOffset == 0; )
				{
					if (pEventBoxWnd->GetEventList()->Lock())
					{
						pEventBoxWnd->GetEventList()->SetScheduleOffset((tOffset = CTime::GetCurrentTime().GetTime() - pEvent->GetAuditTime().GetTime()));
						pEventBoxWnd->GetEventList()->Unlock();
					}
					break;
				}
				if (pEventBoxWnd->ScheduleEvent(pEvent)) continue;
				delete pEvent;
			}
			return((cEventList.GetSize() > 0) ? SYSTEM_WARNING_EVENTLOG_READ_FAILURE : SYSTEM_NOERROR);
		}
		return((dwWaitCode == WAIT_TIMEOUT  &&  tOffset == 0) ? USER_INFORMATIONAL_EVENTLOG_READ_NOTHING : USER_NOERROR);
	}
	return USER_INFORMATIONAL_EVENTLOG_READ_NOTHING;
}

EVENT_DESCRIPTOR CEventRetrieveThread::RetrieveManual(CEventList &cEventList)
{
	UINT  nCount;
	DWORD  dwWaitCode;
	CEventObject  *pEvent;
	CEventBoxWnd  *pEventBoxWnd = (CEventBoxWnd *)GetThreadInfo();

	if (cEventList.GetSize() > 0)
	{
		for (pEventBoxWnd->GetEventList()->Lock(), pEventBoxWnd->GetEventList()->SetScheduleOffset(0), pEventBoxWnd->GetEventList()->Unlock(), nCount = 0; (dwWaitCode = Wait(0)) == WAIT_TIMEOUT && !nCount; )
		{
			if ((pEvent = cEventList.GetAt(0)) && cEventList.Remove(0))
			{
				if (!pEventBoxWnd->DoFilter(pEvent))
				{
					delete pEvent;
					continue;
				}
				pEvent->Acknowledge();
				if (pEventBoxWnd->ShowEvent(pEvent))
				{
					nCount++;
					continue;
				}
				delete pEvent;
			}
			return((cEventList.GetSize() > 0) ? SYSTEM_WARNING_EVENTLOG_READ_FAILURE : SYSTEM_NOERROR);
		}
		return((dwWaitCode == WAIT_TIMEOUT  &&  !nCount) ? USER_INFORMATIONAL_EVENTLOG_READ_NOTHING : USER_NOERROR);
	}
	return USER_INFORMATIONAL_EVENTLOG_READ_NOTHING;
}

UINT CEventRetrieveThread::GetRetrieveMode() CONST
{
	return((IsThreadActive()) ? m_nMode : 0);
}

UINT CEventRetrieveThread::GetRetrieveLogs() CONST
{
	return((IsThreadActive()) ? m_nLogs : 0);
}

UINT CEventRetrieveThread::GetRetrieveLimit() CONST
{
	return((IsThreadActive()) ? m_nLimit : 0);
}

CTimeKey CEventRetrieveThread::GetRetrieveStartTime() CONST
{
	return((IsThreadActive()) ? m_tStartTime : 0);
}

CTimeKey CEventRetrieveThread::GetRetrieveStopTime() CONST
{
	return((IsThreadActive()) ? m_tStopTime : 0);
}

BEGIN_MESSAGE_MAP(CEventRetrieveThread, CThread)
	//{{AFX_MSG_MAP(CEventRetrieveThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventRetrieveThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CEventWatchThread

IMPLEMENT_DYNCREATE(CEventWatchThread, CThread)

CEventWatchThread::CEventWatchThread() : CThread()
{
	m_nLogs = 0;
	m_bInit = (HANDLE)NULL;
}

BOOL CEventWatchThread::Start(CEventBoxWnd *pParentWnd, HANDLE bInit, UINT nLogs)
{
	m_bInit = bInit;
	m_nLogs = nLogs;
	return((ResetEvent(bInit) && CreateThread(pParentWnd)) ? TRUE : FALSE);
}

BOOL CEventWatchThread::Stop()
{
	return((DestroyThread() >= 0) ? TRUE : FALSE);
}

UINT CEventWatchThread::GetWatchLogs() CONST
{
	return((IsThreadActive()) ? m_nLogs : 0);
}

int CEventWatchThread::Run()
{
	DWORD  nEventLogs;
	DWORD  dwEventLogs;
	LPHANDLE  hEventLogs;
	CEventList  cEventList;
	CEventBoxWnd  *pEventBoxWnd = (CEventBoxWnd *)GetThreadInfo();

	if ((nEventLogs = StartWatching(&hEventLogs)) > 0)
	{
		while ((dwEventLogs = Wait(hEventLogs, nEventLogs, FALSE)) > WAIT_OBJECT_0  &&  dwEventLogs <= WAIT_OBJECT_0 + nEventLogs)
		{
			if (pEventBoxWnd->GetEventLog()->Open(GetWatchLogs(), CFile::modeRead))
			{
				if (pEventBoxWnd->GetEventLog()->Watch(GetWatchLogs(), cEventList))
				{
					pEventBoxWnd->GetEventLog()->Close(GetWatchLogs());
					ReportEvent(Watch(cEventList));
					continue;
				}
				pEventBoxWnd->GetEventLog()->Close(GetWatchLogs());
				ReportEvent(SYSTEM_WARNING_EVENTLOG_READ_FAILURE);
				break;
			}
			ReportEvent(SYSTEM_WARNING_EVENTLOG_OPEN_FAILURE);
			break;
		}
		if (cEventList.Lock())
		{
			cEventList.RemoveAll();
			cEventList.Unlock();
		}
		StopWatching(hEventLogs);
	}
	return 0;
}

INT CEventWatchThread::StartWatching(LPHANDLE *phLogs)
{
	INT  nEventLogs;
	LPHANDLE  hEventLogs;
	CEventBoxWnd  *pEventBoxWnd = (CEventBoxWnd *)GetThreadInfo();

	for (SetEvent(m_bInit); pEventBoxWnd->GetEventLog()->Open(GetWatchLogs(), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite); )
	{
		if ((nEventLogs = pEventBoxWnd->GetEventLog()->BeginWatch(GetWatchLogs())) > 0)
		{
			if ((hEventLogs = (LPHANDLE)GlobalAlloc(GPTR, nEventLogs*sizeof(HANDLE))))
			{
				if (pEventBoxWnd->GetEventLog()->BeginWatch(GetWatchLogs(), hEventLogs, nEventLogs))
				{
					for (pEventBoxWnd->GetEventLog()->Close(GetWatchLogs()), CopyMemory(phLogs, &hEventLogs, sizeof(LPHANDLE)); Wait(0) == WAIT_TIMEOUT && !pEventBoxWnd->IsInitialized(); )
					{
						SwitchToThread();
						continue;
					}
					return nEventLogs;
				}
				GlobalFree(hEventLogs);
			}
		}
		pEventBoxWnd->GetEventLog()->Close(GetWatchLogs());
		break;
	}
	return 0;
}

BOOL CEventWatchThread::StopWatching(LPHANDLE hLogs)
{
	CEventBoxWnd  *pEventBoxWnd = (CEventBoxWnd *)GetThreadInfo();

	if (pEventBoxWnd->GetEventLog()->Open(GetWatchLogs(), CFile::modeRead))
	{
		if (pEventBoxWnd->GetEventLog()->EndWatch(GetWatchLogs()))
		{
			pEventBoxWnd->GetEventLog()->Close(GetWatchLogs());
			GlobalFree(hLogs);
			return TRUE;
		}
		pEventBoxWnd->GetEventLog()->Close(GetWatchLogs());
	}
	return FALSE;
}

EVENT_DESCRIPTOR CEventWatchThread::Watch(CEventList &cEventList)
{
	DWORD  dwWaitCode;
	CEventObject  *pEvent;
	CEventBoxWnd  *pEventBoxWnd = (CEventBoxWnd *)GetThreadInfo();

	if (cEventList.Lock())
	{
		if (cEventList.GetSize() > 0)
		{
			while ((dwWaitCode = Wait(0)) == WAIT_TIMEOUT)
			{
				if ((pEvent = cEventList.GetAt(0)) && cEventList.Remove(0))
				{
					if (pEventBoxWnd->ShowEvent(pEvent)) continue;
					delete pEvent;
				}
				break;
			}
			if (!cEventList.GetSize())
			{
				cEventList.Unlock();
				return SYSTEM_NOERROR;
			}
			cEventList.Unlock();
			return((dwWaitCode == WAIT_TIMEOUT) ? SYSTEM_WARNING_EVENTLOG_READ_FAILURE : SYSTEM_NOERROR);
		}
		cEventList.Unlock();
		return SYSTEM_NOERROR;
	}
	return SYSTEM_WARNING_EVENTLOG_READ_FAILURE;
}

BEGIN_MESSAGE_MAP(CEventWatchThread, CThread)
	//{{AFX_MSG_MAP(CEventWatchThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventWatchThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CEventPrintThread

IMPLEMENT_DYNCREATE(CEventPrintThread, CThread)

BOOL CEventPrintThread::Start(CEventBoxWnd *pParentWnd)
{
	return CreateThread(pParentWnd);
}

BOOL CEventPrintThread::Stop()
{
	return((DestroyThread() >= 0) ? TRUE : FALSE);
}

BOOL CEventPrintThread::SetPrintJobs(CONST CEventBoxPrintJobs &pPrintJobs)
{
	INT  nJob[2][2];
	INT  nJobs[2][2];
	CEventBoxPrintJobInfo  *pJobInfo;
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
			if ((pJobInfo = new CEventBoxPrintJobInfo))
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

BOOL CEventPrintThread::GetPrintJobs(CEventBoxPrintJobs &pPrintJobs) CONST
{
	CByteArray  nPrintInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(((m_pPrintJobs.GetSize() > 0 && pPrintJobs.Copy(&m_pPrintJobs)) || pPrintJobs.Unmap(nPrintInfo)) ? TRUE : FALSE);
}

BOOL CEventPrintThread::Schedule()
{
	return m_cEvent.SetEvent();
}

int CEventPrintThread::Run()
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
	CEventBoxPrintJobInfo  *pJobInfo[2];
	CEventBoxWnd  *pEventBoxWnd = (CEventBoxWnd *)GetThreadInfo();

	for (dwJobResult = 0; Lock(); )
	{
		if (dwJobResult == WAIT_OBJECT_0 + 1 || !dwJobResult)
		{
			for (nJob = 0, nJobs = (INT)m_pPrintJobs.GetSize(); nJob < nJobs; nJob++)
			{
				if ((pJobInfo[0] = m_pPrintJobs.GetAt(nJob)) && (pJobInfo[0]->GetPrintMode() & EVENTBOX_PRINT_ACTIVE))
				{
					if (pJobInfo[0]->GetPrintAtDailyTime(tJobDailyTime) || pJobInfo[0]->GetPrintAtDailyTime(tJobDailyTime, nJobStopCount) || pJobInfo[0]->GetPrintAtDailyTime(tJobDailyTime, tJobStopTime))
					{
						pJobInfo[0]->SetPrintLastDailyTime(((tJobTime = CTime::GetCurrentTime().GetTime()).GetTime() % SECONDSPERDAY >= tJobDailyTime.GetTotalSeconds()) ? ((SECONDSPERDAY*(tJobTime.GetTime() / SECONDSPERDAY)) + tJobDailyTime.GetTotalSeconds()) : ((SECONDSPERDAY*(tJobTime.GetTime() / SECONDSPERDAY - 1)) + tJobDailyTime.GetTotalSeconds()));
						continue;
					}
				}
			}
		}
		if ((pJobInfo[0] = ((tJobInterval = m_pPrintJobs.Schedule(pEventBoxWnd->GetEventCount())) == 0) ? m_pPrintJobs.GetAt(0) : (CEventBoxPrintJobInfo *)NULL))
		{
			for (bJobPrint = pEventBoxWnd->Print(pJobInfo[0]); (pJobInfo[0]->GetPrintMode() & EVENTBOX_PRINT_CLEARCOMMENTS) && bJobPrint; )
			{
				for (nJob = 1, nJobs = (INT)m_pPrintJobs.GetSize(); nJob < nJobs; nJob++)
				{
					if ((pJobInfo[1] = m_pPrintJobs.GetAt(nJob)))
					{
						if (pJobInfo[0]->GetName() == pJobInfo[1]->GetName())
						{
							pJobInfo[1]->SetPrintMode(pJobInfo[0]->GetPrintMode() & ~EVENTBOX_PRINT_CLEARCOMMENTS);
							pJobInfo[1]->SetComments(EMPTYSTRING);
							break;
						}
					}
				}
				break;
			}
			ReportEvent((!bJobPrint) ? SYSTEM_WARNING_EVENTBOX_PRINT_FAILURE : SYSTEM_NOERROR);
			m_pPrintJobs.RemoveAt(0);
			delete pJobInfo[0];
		}
		Unlock();
		if ((dwJobResult = Wait(m_cEvent, FALSE, (tJobInterval >= 0) ? (DWORD)(1000 * min(tJobInterval, SECONDSPERDAY)) : INFINITE)) != WAIT_TIMEOUT  &&  dwJobResult != WAIT_OBJECT_0 + 1) break;
	}
	return 0;
}

BEGIN_MESSAGE_MAP(CEventPrintThread, CThread)
	//{{AFX_MSG_MAP(CEventPrintThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventPrintThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CEventBoxToolBar

IMPLEMENT_DYNCREATE(CEventBoxToolBar, CDisplayToolBar)

CEventBoxToolBar::CEventBoxToolBar() : CDisplayToolBar()
{
	return;
}

BEGIN_MESSAGE_MAP(CEventBoxToolBar, CDisplayToolBar)
	//{{AFX_MSG_MAP(CEventBoxToolBar)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventBoxToolBar message handlers


/////////////////////////////////////////////////////////////////////////////
// CEventBoxStatusBar

IMPLEMENT_DYNCREATE(CEventBoxStatusBar, CDisplayStatusBar)

CEventBoxStatusBar::CEventBoxStatusBar() : CDisplayStatusBar()
{
	return;
}

BOOL CEventBoxStatusBar::SetIndicators(CONST UINT *pPanesID, INT nCount)
{
	INT  nIndex;
	CRect  rPane;
	CString  szPane;
	CToolInfo  cToolInfo;
	CDisplayLock  cLock(this);

	if (CDisplayStatusBar::SetIndicators(pPanesID, nCount))
	{
		if (CommandToIndex(ID_EVENTBOX_STATUSBAR_ITEMPANE) >= 0)
		{
			szPane.Format(STRING(IDS_EVENTBOX_STATUSBAR_EVENTS), EVENTBOX_FILTER_DEFAULTNOLIMIT);
			SetPaneInfo(CommandToIndex(ID_EVENTBOX_STATUSBAR_ITEMPANE), ID_EVENTBOX_STATUSBAR_ITEMPANE, SBPS_NOBORDERS | SBPS_STRETCH, CalcPaneWidth(szPane));
		}
		if (!IsWindow(m_wndToolTip.GetSafeHwnd()))
		{
			m_wndToolTip.Create(this, TTS_ALWAYSTIP | TTS_NOPREFIX | TTS_BALLOON);
			SetClassLongPtr(m_wndToolTip.GetSafeHwnd(), GCL_STYLE, GetClassLongPtr(m_wndToolTip.GetSafeHwnd(), GCL_STYLE) | CS_DROPSHADOW);
		}
		if (IsWindow(m_wndToolTip.GetSafeHwnd()))
		{
			if ((nIndex = CommandToIndex(ID_EVENTBOX_STATUSBAR_MODEPANE)) >= 0)
			{
				for (GetItemRect(nIndex, rPane); !m_wndToolTip.GetToolInfo(cToolInfo, this, ID_EVENTBOX_STATUSBAR_MODEPANE); )
				{
					m_wndToolTip.AddTool(this, LPSTR_TEXTCALLBACK, rPane, ID_EVENTBOX_STATUSBAR_MODEPANE);
					break;
				}
			}
			if ((nIndex = CommandToIndex(ID_EVENTBOX_STATUSBAR_SYSTEMPANE)) >= 0)
			{
				for (GetItemRect(nIndex, rPane); !m_wndToolTip.GetToolInfo(cToolInfo, this, ID_EVENTBOX_STATUSBAR_SYSTEMPANE); )
				{
					m_wndToolTip.AddTool(this, LPSTR_TEXTCALLBACK, rPane, ID_EVENTBOX_STATUSBAR_SYSTEMPANE);
					break;
				}
			}
			if ((nIndex = CommandToIndex(ID_EVENTBOX_STATUSBAR_SPACECRAFTPANE)) >= 0)
			{
				for (GetItemRect(nIndex, rPane); !m_wndToolTip.GetToolInfo(cToolInfo, this, ID_EVENTBOX_STATUSBAR_SPACECRAFTPANE); )
				{
					m_wndToolTip.AddTool(this, LPSTR_TEXTCALLBACK, rPane, ID_EVENTBOX_STATUSBAR_SPACECRAFTPANE);
					break;
				}
			}
			if ((nIndex = CommandToIndex(ID_EVENTBOX_STATUSBAR_USERPANE)) >= 0)
			{
				for (GetItemRect(nIndex, rPane); !m_wndToolTip.GetToolInfo(cToolInfo, this, ID_EVENTBOX_STATUSBAR_USERPANE); )
				{
					m_wndToolTip.AddTool(this, LPSTR_TEXTCALLBACK, rPane, ID_EVENTBOX_STATUSBAR_USERPANE);
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

CEventBoxWnd *CEventBoxStatusBar::GetParent() CONST
{
	return((CEventBoxWnd *)CDisplayStatusBar::GetParent());
}

BEGIN_MESSAGE_MAP(CEventBoxStatusBar, CDisplayStatusBar)
	//{{AFX_MSG_MAP(CEventBoxStatusBar)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipNotify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventBoxStatusBar message handlers

void CEventBoxStatusBar::OnPaint()
{
	INT  nIndex;
	RECT  rPane;
	CToolInfo  cToolInfo;

	for (CDisplayStatusBar::OnPaint(); IsWindow(m_wndToolTip.GetSafeHwnd()); )
	{
		if ((nIndex = CommandToIndex(ID_EVENTBOX_STATUSBAR_MODEPANE)) >= 0 && nIndex < m_prPanes.GetSize())
		{
			for (m_wndToolTip.GetToolInfo(cToolInfo, this, ID_EVENTBOX_STATUSBAR_MODEPANE), CopyMemory(&rPane, m_prPanes.GetAt(nIndex), sizeof(RECT)); !EqualRect(&cToolInfo.rect, &rPane); )
			{
				SetRect(&cToolInfo.rect, rPane.left, rPane.top, rPane.right, rPane.bottom);
				m_wndToolTip.SetToolInfo(&cToolInfo);
				break;
			}
		}
		if ((nIndex = CommandToIndex(ID_EVENTBOX_STATUSBAR_SYSTEMPANE)) >= 0 && nIndex < m_prPanes.GetSize())
		{
			for (m_wndToolTip.GetToolInfo(cToolInfo, this, ID_EVENTBOX_STATUSBAR_SYSTEMPANE), CopyMemory(&rPane, m_prPanes.GetAt(nIndex), sizeof(RECT)); !EqualRect(&cToolInfo.rect, &rPane); )
			{
				SetRect(&cToolInfo.rect, rPane.left, rPane.top, rPane.right, rPane.bottom);
				m_wndToolTip.SetToolInfo(&cToolInfo);
				break;
			}
		}
		if ((nIndex = CommandToIndex(ID_EVENTBOX_STATUSBAR_SPACECRAFTPANE)) >= 0 && nIndex < m_prPanes.GetSize())
		{
			for (m_wndToolTip.GetToolInfo(cToolInfo, this, ID_EVENTBOX_STATUSBAR_SPACECRAFTPANE), CopyMemory(&rPane, m_prPanes.GetAt(nIndex), sizeof(RECT)); !EqualRect(&cToolInfo.rect, &rPane); )
			{
				SetRect(&cToolInfo.rect, rPane.left, rPane.top, rPane.right, rPane.bottom);
				m_wndToolTip.SetToolInfo(&cToolInfo);
				break;
			}
		}
		if ((nIndex = CommandToIndex(ID_EVENTBOX_STATUSBAR_USERPANE)) >= 0 && nIndex < m_prPanes.GetSize())
		{
			for (m_wndToolTip.GetToolInfo(cToolInfo, this, ID_EVENTBOX_STATUSBAR_USERPANE), CopyMemory(&rPane, m_prPanes.GetAt(nIndex), sizeof(RECT)); !EqualRect(&cToolInfo.rect, &rPane); )
			{
				SetRect(&cToolInfo.rect, rPane.left, rPane.top, rPane.right, rPane.bottom);
				m_wndToolTip.SetToolInfo(&cToolInfo);
				break;
			}
		}
		break;
	}
}

void CEventBoxStatusBar::OnMouseMove(UINT nFlags, CPoint point)
{
	MSG  sMsg;

	if (IsWindow(m_wndToolTip.GetSafeHwnd()))
	{
		CopyMemory(&sMsg, GetCurrentMessage(), sizeof(MSG));
		m_wndToolTip.RelayEvent(&sMsg);
	}
	CDisplayStatusBar::OnMouseMove(nFlags, point);
}

BOOL CEventBoxStatusBar::OnToolTipNotify(UINT nID, NMHDR *pNotifyInfo, LRESULT *pResult)
{
	TOOLTIPTEXT  *pToolTipInfo = (TOOLTIPTEXT *)pNotifyInfo;

	switch (pNotifyInfo->idFrom)
	{
	case ID_EVENTBOX_STATUSBAR_MODEPANE:
	{ pToolTipInfo->lpszText = (LPTSTR)STRING(IDS_EVENTBOX_STATUSBAR_MODEPANE);
	return TRUE;
	}
	case ID_EVENTBOX_STATUSBAR_SYSTEMPANE:
	{ pToolTipInfo->lpszText = (LPTSTR)STRING(IDS_EVENTBOX_STATUSBAR_SYSTEMPANE);
	return TRUE;
	}
	case ID_EVENTBOX_STATUSBAR_SPACECRAFTPANE:
	{ pToolTipInfo->lpszText = (LPTSTR)STRING(IDS_EVENTBOX_STATUSBAR_SPACECRAFTPANE);
	return TRUE;
	}
	case ID_EVENTBOX_STATUSBAR_USERPANE:
	{ pToolTipInfo->lpszText = (LPTSTR)STRING(IDS_EVENTBOX_STATUSBAR_USERPANE);
	return TRUE;
	}
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CEventBoxView

IMPLEMENT_DYNCREATE(CEventBoxView, CTextView)

CEventBoxView::CEventBoxView() : CTextView()
{
	m_bSortInverse = FALSE;
}

BOOL CEventBoxView::Create(CWnd *pParentWnd, DWORD dwStyle)
{
	return CTextView::Create(pParentWnd, CRect(0, 0, 0, 0), dwStyle);
}

BOOL CEventBoxView::SetTitle(UINT nColumns)
{
	CUIntArray  nWidths;
	CTextViewLock  cLock(this);

	return((CalcColumnsWidth(nColumns, nWidths)) ? SetTitle(nColumns, nWidths) : FALSE);
}
BOOL CEventBoxView::SetTitle(UINT nColumns, CONST CUIntArray &nWidths)
{
	INT  nIndex;
	INT  nCount;
	INT  nActiveItem;
	INT  nActiveColumn;
	CStringArray  szColumns;
	CTextViewLock  cLock(this);

	for (nActiveItem = m_wndContentCtrl.m_nActiveItem, nActiveColumn = m_wndContentCtrl.m_nActiveColumn; LookupColumnsName(nColumns, szColumns) && SetColumns(szColumns, nWidths); )
	{
		for (nIndex = 0, nCount = (INT)szColumns.GetSize(); nIndex < nCount; nIndex++)
		{
			if (LookupColumnName(szColumns.GetAt(nIndex)) == EVENTBOX_TITLEITEM_MESSAGE)
			{
				SetColumnFormat(nIndex, GetColumnFormat(nIndex) | DT_EXPANDTABS);
				continue;
			}
			if (LookupColumnName(szColumns.GetAt(nIndex)) == EVENTBOX_TITLEITEM_COMMENTS)
			{
				SetColumnFormat(nIndex, GetColumnFormat(nIndex) | DT_EXPANDTABS);
				continue;
			}
		}
		SetCurText(nActiveItem, nActiveColumn);
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxView::GetTitle(UINT &nColumns) CONST
{
	CUIntArray  nWidths;

	return GetTitle(nColumns, nWidths);
}
BOOL CEventBoxView::GetTitle(UINT &nColumns, CUIntArray &nWidths) CONST
{
	INT  nColumn;
	CStringArray  szColumns;

	for (nColumn = (GetColumns(szColumns, nWidths)) ? (INT)szColumns.GetUpperBound() : 0, nColumns = 0; nColumn >= 0; nColumn--)
	{
		nColumns |= LookupColumnName(szColumns.GetAt(nColumn));
		continue;
	}
	return((szColumns.GetSize() == nWidths.GetSize()) ? TRUE : FALSE);
}
BOOL CEventBoxView::GetTitle(CStringArray &szColumns) CONST
{
	return GetColumns(szColumns);
}
BOOL CEventBoxView::GetTitle(CStringArray &szColumns, CUIntArray &nWidths) CONST
{
	return GetColumns(szColumns, nWidths);
}

INT CEventBoxView::AddItem(CEventObject *pEvent, BOOL bRedraw)
{
	INT  nIndex;
	CTextViewAttribute  cAttribute;
	CTextViewLock  cLock(this);

	if ((nIndex = FindIndex(pEvent, TRUE)) >= 0)
	{
		if (InsertText(nIndex, ConstructText(pEvent), ConstructAttribute(pEvent, &cAttribute), bRedraw) >= 0)
		{
			m_pEvents.InsertAt(nIndex, pEvent, 1);
			return nIndex;
		}
	}
	return -1;
}

BOOL CEventBoxView::SetItem(INT nIndex, CEventObject *pEvent, BOOL bRedraw)
{
	CTextViewAttribute  cAttribute;
	CTextViewLock  cLock(this);

	if (SetText(nIndex, ConstructText(pEvent), ConstructAttribute(pEvent, &cAttribute), bRedraw))
	{
		m_pEvents.SetAt(nIndex, pEvent);
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxView::GetItem(INT nIndex, CEventObject *pEvent) CONST
{
	CTextViewLock  cLock(this);

	if (nIndex >= 0 && nIndex < m_pEvents.GetSize())
	{
		pEvent->Copy((CEventObject *)m_pEvents.GetAt(nIndex));
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxView::DeleteItem(CEventObject *pEvent)
{
	INT  nIndex;
	CTextViewLock  cLock(this);

	if ((nIndex = FindIndex(pEvent)) >= 0 && DeleteText(nIndex))
	{
		m_pEvents.RemoveAt(nIndex);
		return TRUE;
	}
	return FALSE;
}

INT CEventBoxView::FindItem(CONST CEventObject *pEvent) CONST
{
	CTextViewLock  cLock(this);

	return FindIndex(pEvent);
}

BOOL CEventBoxView::SetCurItem(CONST CEventObject *pEvent)
{
	INT  nIndex;
	CTextViewLock  cLock(this);

	return(((nIndex = FindIndex(pEvent)) >= 0 && SetCurText(nIndex)) ? TRUE : FALSE);
}

INT CEventBoxView::GetCurItem(CEventObject *pEvent) CONST
{
	INT  nIndex;
	CTextViewLock  cLock(this);

	if ((nIndex = GetCurText()) >= 0 && nIndex < m_pEvents.GetSize())
	{
		pEvent->Copy((CEventObject *)m_pEvents.GetAt(nIndex));
		return nIndex;
	}
	return -1;
}

BOOL CEventBoxView::AcknowledgeItem(CONST CEventObject *pEvent)
{
	INT  nIndex;
	CTextViewLock  cLock(this);

	return(((nIndex = FindIndex(pEvent)) >= 0 && StopTextBlinking(nIndex)) ? TRUE : FALSE);
}

VOID CEventBoxView::CopyItems(UINT nCode)
{
	INT  nPos;
	INT  nItem;
	INT  nItems;
	LPBYTE  pData;
	HGLOBAL  hData;
	CString  szText[2];
	CTextViewLock  cLock(this);

	if (nCode == EVENTBOX_CLIPBOARD_ALLEVENTS)
	{
		for (nItem = 0, nItems = GetTextCount(); nItem < nItems; nItem++)
		{
			if (GetText(nItem, szText[0]))
			{
				if (!szText[1].IsEmpty())
				{
					szText[1] += CR;
					szText[1] += EOL;
				}
				szText[1] += szText[0];
			}
		}
	}
	if (nCode == EVENTBOX_CLIPBOARD_SINGLEEVENT)
	{
		nItem = nItems = GetCurText();
		GetText(nItem, szText[1]);
	}
	if (nCode == EVENTBOX_CLIPBOARD_UPTOEVENT)
	{
		for (nItem = 0, nItems = GetCurText(); nItem <= nItems; nItem++)
		{
			if (GetText(nItem, szText[0]))
			{
				if (!szText[1].IsEmpty())
				{
					szText[1] += CR;
					szText[1] += EOL;
				}
				szText[1] += szText[0];
			}
		}
	}
	if (nCode == EVENTBOX_CLIPBOARD_FROMEVENT)
	{
		for (nItem = GetCurText(), nItems = GetTextCount(); nItem < nItems; nItem++)
		{
			if (GetText(nItem, szText[0]))
			{
				if (!szText[1].IsEmpty())
				{
					szText[1] += CR;
					szText[1] += EOL;
				}
				szText[1] += szText[0];
			}
		}
	}
	while ((nPos = szText[1].Find(GetColumnDelimiter())) >= 0)
	{
		szText[1] = szText[1].Left(nPos) + TAB + szText[1].Mid(nPos + 1);
		continue;
	}
	if (OpenClipboard())
	{
		if (EmptyClipboard())
		{
			if ((hData = GlobalAlloc(GHND, (szText[1].GetLength() + 1)*sizeof(CHAR))))
			{
				if ((pData = (LPBYTE)GlobalLock(hData)))
				{
#ifndef UNICODE
					CopyMemory(pData, (LPCSTR)szText[1], szText[1].GetLength() + 1);
#else
					WideCharToMultiByte(CP_ACP, 0, szText[1], -1, (LPSTR)pData, szText[1].GetLength() + 1, (LPCSTR)NULL, (LPBOOL)NULL);
#endif
					SetClipboardData(CF_TEXT, hData);
					GlobalUnlock(hData);
					CloseClipboard();
					return;
				}
				GlobalFree(hData);
			}
		}
		CloseClipboard();
	}
}

BOOL CEventBoxView::SortItems(BOOL bInverse)
{
	INT  nItem;
	INT  nItems;
	INT  nActiveItem;
	INT  nActiveColumn;
	CPtrArray  pEvents;
	CTextViewLock  cLock(this);

	if (m_bSortInverse != bInverse)
	{
		nActiveItem = m_wndContentCtrl.m_nActiveItem;
		nActiveColumn = m_wndContentCtrl.m_nActiveColumn;
		for (nItem = 0, nItems = (DeleteAllText((!m_pEvents.GetSize()) ? TRUE : FALSE)) ? (INT)m_pEvents.GetSize() : 0, pEvents.Copy(m_pEvents), m_pEvents.RemoveAll(), m_bSortInverse = bInverse; nItem < nItems; nItem++)
		{
			AddItem((CEventObject *)pEvents.GetAt(nItem), (nItem == nItems - 1) ? TRUE : FALSE);
			continue;
		}
		if (nItems > 0) SetCurText(nItems - nActiveItem - 1, nActiveColumn);
	}
	return TRUE;
}

VOID CEventBoxView::RefreshItems(BOOL bSelect)
{
	CTextViewLock  cLock(this);

	SetCurText((bSelect) ? (GetTextCount() - 1) : GetCurText());
	RecalcLayout();
}

BOOL CEventBoxView::DeleteAllItems()
{
	CTextViewLock  cLock(this);

	DeleteAllText();
	m_pEvents.RemoveAll();
	return TRUE;
}

CEventBoxWnd *CEventBoxView::GetParent() CONST
{
	return((CEventBoxWnd *)CTextView::GetParent());
}

CString CEventBoxView::LookupColumnName(UINT nColumn) CONST
{
	if (nColumn == EVENTBOX_TITLEITEM_TIME) return STRING(IDS_EVENTBOX_TITLEITEM_TIME);
	if (nColumn == EVENTBOX_TITLEITEM_CATEGORY) return STRING(IDS_EVENTBOX_TITLEITEM_CATEGORY);
	if (nColumn == EVENTBOX_TITLEITEM_TYPE) return STRING(IDS_EVENTBOX_TITLEITEM_TYPE);
	if (nColumn == EVENTBOX_TITLEITEM_MESSAGE) return STRING(IDS_EVENTBOX_TITLEITEM_MESSAGE);
	if (nColumn == EVENTBOX_TITLEITEM_COMMENTS) return STRING(IDS_EVENTBOX_TITLEITEM_COMMENTS);
	if (nColumn == EVENTBOX_TITLEITEM_RECIPIENTS) return STRING(IDS_EVENTBOX_TITLEITEM_RECIPIENTS);
	if (nColumn == EVENTBOX_TITLEITEM_USER) return STRING(IDS_EVENTBOX_TITLEITEM_USER);
	return EMPTYSTRING;
}
UINT CEventBoxView::LookupColumnName(LPCTSTR pszColumn) CONST
{
	if (!lstrcmp(STRING(IDS_EVENTBOX_TITLEITEM_TIME), pszColumn)) return EVENTBOX_TITLEITEM_TIME;
	if (!lstrcmp(STRING(IDS_EVENTBOX_TITLEITEM_CATEGORY), pszColumn)) return EVENTBOX_TITLEITEM_CATEGORY;
	if (!lstrcmp(STRING(IDS_EVENTBOX_TITLEITEM_TYPE), pszColumn)) return EVENTBOX_TITLEITEM_TYPE;
	if (!lstrcmp(STRING(IDS_EVENTBOX_TITLEITEM_MESSAGE), pszColumn)) return EVENTBOX_TITLEITEM_MESSAGE;
	if (!lstrcmp(STRING(IDS_EVENTBOX_TITLEITEM_COMMENTS), pszColumn)) return EVENTBOX_TITLEITEM_COMMENTS;
	if (!lstrcmp(STRING(IDS_EVENTBOX_TITLEITEM_RECIPIENTS), pszColumn)) return EVENTBOX_TITLEITEM_RECIPIENTS;
	if (!lstrcmp(STRING(IDS_EVENTBOX_TITLEITEM_USER), pszColumn)) return EVENTBOX_TITLEITEM_USER;
	return 0;
}

INT CEventBoxView::LookupColumnsName(UINT nColumns, CStringArray &szColumns) CONST
{
	if (nColumns & EVENTBOX_TITLEITEM_TIME) szColumns.Add(LookupColumnName(EVENTBOX_TITLEITEM_TIME));
	if (nColumns & EVENTBOX_TITLEITEM_CATEGORY) szColumns.Add(LookupColumnName(EVENTBOX_TITLEITEM_CATEGORY));
	if (nColumns & EVENTBOX_TITLEITEM_TYPE) szColumns.Add(LookupColumnName(EVENTBOX_TITLEITEM_TYPE));
	if (nColumns & EVENTBOX_TITLEITEM_MESSAGE) szColumns.Add(LookupColumnName(EVENTBOX_TITLEITEM_MESSAGE));
	if (nColumns & EVENTBOX_TITLEITEM_COMMENTS) szColumns.Add(LookupColumnName(EVENTBOX_TITLEITEM_COMMENTS));
	if (nColumns & EVENTBOX_TITLEITEM_RECIPIENTS) szColumns.Add(LookupColumnName(EVENTBOX_TITLEITEM_RECIPIENTS));
	if (nColumns & EVENTBOX_TITLEITEM_USER) szColumns.Add(LookupColumnName(EVENTBOX_TITLEITEM_USER));
	return((INT)szColumns.GetSize());
}

INT CEventBoxView::CalcColumnWidth(LPCTSTR pszColumn)
{
	CDC  *pDC;
	INT  nWidth;
	CFont  *pOldFont;

	if ((pDC = GetDC()))
	{
		if (LookupColumnName(pszColumn) == 0)
		{
			for (nWidth = 0; (pOldFont = pDC->SelectObject(&m_wndContentCtrl.m_cFont)); )
			{
				nWidth = 2 * GetSystemMetrics(SM_CXEDGE) + LOWORD(GetTextIndents()) + pDC->GetTextExtent(pszColumn).cx + HIWORD(GetTextIndents());
				pDC->SelectObject(pOldFont);
				break;
			}
			ReleaseDC(pDC);
			return nWidth;
		}
		for (nWidth = 0; (pOldFont = pDC->SelectObject(&m_wndHeaderCtrl.m_cFont)); )
		{
			nWidth = 2 * GetSystemMetrics(SM_CXEDGE) + LOWORD(GetTextIndents()) + pDC->GetTextExtent(pszColumn).cx + HIWORD(GetTextIndents());
			pDC->SelectObject(pOldFont);
			break;
		}
		ReleaseDC(pDC);
		return nWidth;
	}
	return 0;
}

INT CEventBoxView::CalcColumnsWidth(UINT nColumns, CUIntArray &nWidths)
{
	INT  nWidth;
	INT  nIndex[2];
	INT  nCount[2];
	CTimeKey  tTime;
	CStringArray  szColumns;

	for (nIndex[0] = 0, nCount[0] = LookupColumnsName(nColumns, szColumns), nWidths.RemoveAll(); nIndex[0] < nCount[0]; nIndex[0]++)
	{
		for (nIndex[1] = 0, nCount[1] = (INT)m_wndHeaderCtrl.m_szColumnsText.GetSize(); nIndex[1] < nCount[1]; nIndex[1]++)
		{
			if (m_wndHeaderCtrl.m_szColumnsText.GetAt(nIndex[1]) == szColumns.GetAt(nIndex[0]))
			{
				nWidth = (nIndex[1] > 0) ? (m_wndHeaderCtrl.m_nColumnsWidth.GetAt(nIndex[1]) - m_wndHeaderCtrl.m_nColumnsWidth.GetAt(nIndex[1] - 1)) : m_wndHeaderCtrl.m_nColumnsWidth.GetAt(nIndex[1]);
				nWidths.Add((nWidths.GetSize() > 0) ? (nWidths.GetAt(nWidths.GetUpperBound()) + nWidth) : nWidth);
				break;
			}
		}
		if (nIndex[1] == nCount[1])
		{
			switch (LookupColumnName(szColumns.GetAt(nIndex[0])))
			{
			case EVENTBOX_TITLEITEM_TIME:
			{ nWidth = max(CalcColumnWidth(tTime.Format()), CalcColumnWidth(szColumns.GetAt(nIndex[0])));
			break;
			}
			case EVENTBOX_TITLEITEM_CATEGORY:
			{ nWidth = max(max(max(CalcColumnWidth(STRING(IDS_EVENTCATEGORY_SYSTEM)), CalcColumnWidth(STRING(IDS_EVENTCATEGORY_SPACECRAFT))), CalcColumnWidth(STRING(IDS_EVENTCATEGORY_USER))), CalcColumnWidth(szColumns.GetAt(nIndex[0])));
			break;
			}
			case EVENTBOX_TITLEITEM_TYPE:
			{ nWidth = max(max(max(max(max(CalcColumnWidth(STRING(IDS_EVENTTYPE_SUCCESS)), CalcColumnWidth(STRING(IDS_EVENTTYPE_INFORMATIONAL))), CalcColumnWidth(STRING(IDS_EVENTTYPE_WARNING))), CalcColumnWidth(STRING(IDS_EVENTTYPE_ERROR))), CalcColumnWidth(STRING(IDS_EVENTTYPE_SCHEDULED))), CalcColumnWidth(szColumns.GetAt(nIndex[0])));
			break;
			}
			case EVENTBOX_TITLEITEM_MESSAGE:
			{ nWidth = max(3 * CalcColumnWidth(tTime.Format()), CalcColumnWidth(szColumns.GetAt(nIndex[0])));
			break;
			}
			case EVENTBOX_TITLEITEM_COMMENTS:
			{ nWidth = max(2 * CalcColumnWidth(tTime.Format()), CalcColumnWidth(szColumns.GetAt(nIndex[0])));
			break;
			}
			case EVENTBOX_TITLEITEM_RECIPIENTS:
			{ nWidth = max(CalcColumnWidth(tTime.Format()), CalcColumnWidth(szColumns.GetAt(nIndex[0])));
			break;
			}
			case EVENTBOX_TITLEITEM_USER:
			{ nWidth = max(CalcColumnWidth(tTime.Format()), CalcColumnWidth(szColumns.GetAt(nIndex[0])));
			break;
			}
			default:
			{ nWidth = 0;
			break;
			}
			}
			nWidths.Add((nWidths.GetSize() > 0) ? (nWidths.GetAt(nWidths.GetUpperBound()) + nWidth) : nWidth);
		}
	}
	return((nCount[0] == nWidths.GetSize()) ? (INT)nWidths.GetSize() : 0);
}

CString CEventBoxView::ConstructText(CONST CEventObject *pEvent) CONST
{
	INT  nColumn;
	INT  nColumns;
	INT  nRecipient;
	INT  nRecipients;
	UINT  nCategory;
	CString  szText[2];
	CStringArray  szRecipients;

	for (nColumn = 0, nColumns = (INT)m_wndHeaderCtrl.m_szColumnsText.GetSize(); nColumn < nColumns; nColumn++)
	{
		switch (LookupColumnName(m_wndHeaderCtrl.m_szColumnsText.GetAt(nColumn)))
		{
		case EVENTBOX_TITLEITEM_TIME:
		{ szText[0] = pEvent->GetAuditTime().FormatGmt();
		break;
		}
		case EVENTBOX_TITLEITEM_CATEGORY:
		{ for (szText[0].Empty(); (nCategory = pEvent->GetCategory()) && nCategory != EVENT_CATEGORY_NONE; )
		{
			szText[0] = (nCategory & EVENT_CATEGORY_SYSTEM) ? STRING(IDS_EVENTCATEGORY_SYSTEM) : szText[0];
			szText[0] = (nCategory & EVENT_CATEGORY_SPACECRAFT) ? STRING(IDS_EVENTCATEGORY_SPACECRAFT) : szText[0];
			szText[0] = (nCategory & EVENT_CATEGORY_USER) ? STRING(IDS_EVENTCATEGORY_USER) : szText[0];
			break;
		}
		break;
		}
		case EVENTBOX_TITLEITEM_TYPE:
		{ szText[0] = pEvent->GetType();
		break;
		}
		case EVENTBOX_TITLEITEM_MESSAGE:
		{ szText[0] = pEvent->GetMessage();
		break;
		}
		case EVENTBOX_TITLEITEM_COMMENTS:
		{ szText[0] = pEvent->GetComments();
		break;
		}
		case EVENTBOX_TITLEITEM_RECIPIENTS:
		{ for (nRecipient = 0, nRecipients = pEvent->GetNotificationRecipients(szRecipients), szText[0].Empty(); nRecipient < nRecipients; nRecipient++)
		{
			szText[0] += (nRecipient > 0) ? (CString(CR) + CString(EOL) + szRecipients.GetAt(nRecipient)) : szRecipients.GetAt(nRecipient);
			continue;
		}
		break;
		}
		case EVENTBOX_TITLEITEM_USER:
		{ szText[0] = pEvent->GetUser();
		break;
		}
		}
		szText[1] += (nColumn > 0) ? (GetColumnDelimiter() + szText[0]) : szText[0];
	}
	return szText[1];
}

CTextViewAttribute *CEventBoxView::ConstructAttribute(CONST CEventObject *pEvent, CTextViewAttribute *pAttribute) CONST
{
	COLORREF  nColor[2];

	for (nColor[0] = (m_wndContentCtrl.m_bColumnsColor.GetSize() > 0 && m_wndContentCtrl.m_bColumnsColor.GetAt(0)) ? m_wndContentCtrl.m_nColumnsColor.GetAt(0) : GetSysColor(COLOR_WINDOWTEXT); ((nColor[1] = pEvent->GetAuditColor()) != nColor[0]) || !pEvent->IsAcknowledged(); )
	{
		pAttribute->SetColumnBlinking(-1, !pEvent->IsAcknowledged());
		pAttribute->SetColumnColor(-1, nColor[1]);
		return pAttribute;
	}
	return((CTextViewAttribute *)NULL);
}

INT CEventBoxView::FindIndex(CONST CEventObject *pEvent, BOOL bInsert) CONST
{
	INT  nIndex;
	INT  nMinIndex;
	INT  nMaxIndex;
	CTimeKey  tTime[2];
	CEventObject  *pEventObject;

	for (nMinIndex = 0, nMaxIndex = (INT)m_pEvents.GetSize(), nIndex = (nMinIndex + nMaxIndex) / 2, tTime[0] = pEvent->GetAuditTime(); nIndex >= 0 && nMinIndex != nMaxIndex; nIndex = (nMinIndex + nMaxIndex) / 2)
	{
		for (tTime[1] = 0; (pEventObject = (CEventObject *)m_pEvents.GetAt(nIndex)); )
		{
			tTime[1] = pEventObject->GetAuditTime();
			break;
		}
		if (tTime[1] > 0)
		{
			if ((!m_bSortInverse && ((!bInsert  &&  tTime[0] > tTime[1]) || (bInsert  &&  tTime[0] >= tTime[1]))) || (m_bSortInverse  &&  tTime[0] < tTime[1]))
			{
				nMinIndex = nIndex + 1;
				continue;
			}
			nMaxIndex = nIndex;
			continue;
		}
		nIndex = -1;
		break;
	}
	for (nMaxIndex = (nIndex >= 0) ? (INT)m_pEvents.GetSize() : -1; !bInsert && nIndex < nMaxIndex; nIndex++)
	{
		if ((pEventObject = (CEventObject *)m_pEvents.GetAt(nIndex)) && (pEventObject == pEvent || pEventObject->GetAuditTime() != tTime[0])) break;
		continue;
	}
	return((nIndex >= 0) ? ((bInsert || (nIndex < nMaxIndex  &&  m_pEvents.GetAt(nIndex) == (LPVOID)pEvent)) ? nIndex : -1) : -1);
}

BOOL CEventBoxView::SetLayoutInfo(INT nIndex, INT nCount, CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo)
{
	CTextViewLock  cLock(this);

	SetScrollInfo(pHorzScrollInfo, pVertScrollInfo);
	SetCurText((nCount != GetTextCount()) ? (GetTextCount() - 1) : nIndex);
	ScrollTo(GetCurText());
	return TRUE;
}

BOOL CEventBoxView::GetLayoutInfo(INT &nIndex, INT &nCount, SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST
{
	CTextViewLock  cLock(this);

	nIndex = GetCurText();
	nCount = GetTextCount();
	GetScrollInfo(pHorzScrollInfo, pVertScrollInfo);
	return TRUE;
}

VOID CEventBoxView::RecalcLayout()
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

VOID CEventBoxView::RefreshContent()
{
	INT  nItem;
	INT  nItems;
	CEventObject  *pEvent;
	CTextViewAttribute  cAttribute;
	CTextViewLock  cLock(this);

	for (nItem = 0, nItems = (INT)m_pEvents.GetSize(); nItem < nItems; nItem++)
	{
		if ((pEvent = (CEventObject *)m_pEvents.GetAt(nItem)))
		{
			SetItem(nItem, pEvent, (nItem == nItems - 1) ? TRUE : FALSE);
			continue;
		}
	}
}

void CEventBoxView::PostNcDestroy()
{
	m_pEvents.RemoveAll();
	CTextView::PostNcDestroy();
}

BOOL CEventBoxView::Lock()
{
	return((IsWindow(GetSafeHwnd())) ? (GetParent()->Lock() && CTextView::Lock()) : CTextView::Lock());
}

BOOL CEventBoxView::Unlock()
{
	return((IsWindow(GetSafeHwnd())) ? (CTextView::Unlock() && GetParent()->Unlock()) : CTextView::Unlock());
}

BEGIN_MESSAGE_MAP(CEventBoxView, CTextView)
	//{{AFX_MSG_MAP(CEventBoxView)
	ON_WM_SETCURSOR()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventBoxView message handlers

BOOL CEventBoxView::OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message)
{
	CTextViewLock  cLock(this);

	if (GetParent()->IsRetrievingEvents() && !GetParent()->IsRetrievingEvents(TRUE))
	{
		SetCursor(LoadCursor((HINSTANCE)NULL, IDC_WAIT));
		return TRUE;
	}
	return CTextView::OnSetCursor(pWnd, nHitTest, message);
}

BOOL CEventBoxView::OnContentMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	CRect  rContent;
	CPoint  ptMenu;
	CLocaleMenu  cMenu;
	CEventObject  cEvent[2];
	CMFCPopupMenu  *pFloatingMenu;
	CTextViewLock  cLock(this);

	if (message == WM_KEYDOWN)
	{
		if (wParam == VK_RETURN)
		{
			if ((GetParent()->GetScope() == DISPLAY_SCOPE_LOCAL || CheckAccountPrivilege(PRIVILEGE_EVENTBOX_LOOK)) && (!GetParent()->IsRetrievingEvents() || GetParent()->IsRetrievingEvents(TRUE)) && GetCurItem(&cEvent[0]) >= 0)
			{
				for (cLock.Release(); !cEvent[0].Compare(&cEvent[1]); )
				{
					GetParent()->ShowEventDetails(&cEvent[0]);
					break;
				}
				return FALSE;
			}
		}
		if (wParam == VK_RIGHT)
		{
			if (HIBYTE(GetKeyState(VK_SHIFT)))
			{
				if (GetParent()->IsRetrievingEvents(TRUE))
				{
					GetParent()->RetrieveMoreEvents();
					return FALSE;
				}
			}
		}
		if (wParam == VK_TAB) GetParent()->SetFocus();
		return FALSE;
	}
	if (message == WM_LBUTTONDBLCLK)
	{
		for (m_wndContentCtrl.GetClientRect(rContent); rContent.PtInRect(CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))); )
		{
			if ((GetParent()->GetScope() == DISPLAY_SCOPE_LOCAL || CheckAccountPrivilege(PRIVILEGE_EVENTBOX_LOOK)) && (!GetParent()->IsRetrievingEvents() || GetParent()->IsRetrievingEvents(TRUE)) && GetCurItem(&cEvent[0]) >= 0)
			{
				for (cLock.Release(); !cEvent[0].Compare(&cEvent[1]); )
				{
					GetParent()->ShowEventDetails(&cEvent[0]);
					break;
				}
			}
			break;
		}
		return FALSE;
	}
	if (message == WM_RBUTTONDOWN)
	{
		for (m_wndContentCtrl.GetClientRect(rContent); rContent.PtInRect((ptMenu = CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)))) && (!GetParent()->IsRetrievingEvents() || GetParent()->IsRetrievingEvents(TRUE)); )
		{
			for (m_wndContentCtrl.ClientToScreen(&ptMenu), cLock.Release(); (pFloatingMenu = (cMenu.LoadMenu(IDR_EVENTBOXFLOATINGMENU)) ? new CMFCPopupMenu : (CMFCPopupMenu *)NULL); )
			{
				pFloatingMenu->Create(GetParentFrame(), ptMenu.x, ptMenu.y, cMenu.Detach());
				break;
			}
			break;
		}
	}
	return FALSE;
}

BOOL CEventBoxView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	CStringArray  szColumns;
	NMHEADER  *pNotifyInfo = (NMHEADER *)lParam;

	if (pNotifyInfo->hdr.code == HDN_ITEMCLICK)
	{
		for (m_szSearchItem = (GetColumns(szColumns) && pNotifyInfo->iItem < szColumns.GetSize()) ? szColumns.GetAt(pNotifyInfo->iItem) : EMPTYSTRING; !m_szSearchItem.IsEmpty(); )
		{
			SetTimer(EVENTBOXVIEW_SEARCH_TIMERID, EVENTBOXVIEW_SEARCH_TIMEOUT, NULL);
			break;
		}
	}
	return CTextView::OnNotify(wParam, lParam, pResult);
}

void CEventBoxView::OnTimer(UINT_PTR nEventID)
{
	if (nEventID == EVENTBOXVIEW_SEARCH_TIMERID)
	{
		for (KillTimer(nEventID); m_szSearchItem == STRING(IDS_EVENTBOX_TITLEITEM_TIME); )
		{
			GetParent()->ShowSearchEventTimeDetails();
			break;
		}
		for (; m_szSearchItem == STRING(IDS_EVENTBOX_TITLEITEM_CATEGORY); )
		{
			GetParent()->ShowSearchEventCategoryDetails();
			break;
		}
		for (; m_szSearchItem == STRING(IDS_EVENTBOX_TITLEITEM_TYPE); )
		{
			GetParent()->ShowSearchEventTypeDetails();
			break;
		}
		for (; m_szSearchItem == STRING(IDS_EVENTBOX_TITLEITEM_MESSAGE); )
		{
			GetParent()->ShowSearchEventMessageDetails();
			break;
		}
		for (; m_szSearchItem == STRING(IDS_EVENTBOX_TITLEITEM_COMMENTS); )
		{
			GetParent()->ShowSearchEventCommentsDetails();
			break;
		}
		for (; m_szSearchItem == STRING(IDS_EVENTBOX_TITLEITEM_USER); )
		{
			GetParent()->ShowSearchEventUserDetails();
			break;
		}
		for (; m_szSearchItem == STRING(IDS_EVENTBOX_TITLEITEM_RECIPIENTS); )
		{
			GetParent()->ShowSearchEventRecipientsDetails();
			break;
		}
		m_szSearchItem.Empty();
	}
	CTextView::OnTimer(nEventID);
}


/////////////////////////////////////////////////////////////////////////////
// CEventBoxWnd

IMPLEMENT_DYNAMIC(CEventBoxWnd, CDisplayWnd)

CEventBoxWnd::CEventBoxWnd() : CDisplayWnd()
{
	for (SetType(DISPLAY_TYPE_EVENTBOX); (m_pEventList = ((m_pEventLog = new CEventLog)) ? new CEventList : (CEventList *)NULL); )
	{
		SetFilterMode();
		SetFilterLimitation();
		SetRetrieveMode();
		SetRetrieveLimit();
		SetRetrieveStartTime();
		SetRetrieveStopTime();
		break;
	}
}

CEventBoxWnd::~CEventBoxWnd()
{
	delete m_pEventList;
	delete m_pEventLog;
}

BOOL CEventBoxWnd::Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszTitle, PDISPLAYINFO pDefaultInfo, BOOL bDefault)
{
	if (CDisplayWnd::Create(pParentWnd, (!pszTitle || (!_tcsstr(pszTitle, STRING(IDS_DISPLAY_TITLE_GLOBALEVENTBOX)) && !_tcsstr(pszTitle, STRING(IDS_DISPLAY_TITLE_EVENTBOX)))) ? ((pDefaultInfo->nScope == DISPLAY_SCOPE_GLOBAL) ? STRING(IDS_DISPLAY_TITLE_GLOBALEVENTBOX) : STRING(IDS_DISPLAY_TITLE_EVENTBOX)) : pszTitle, pDefaultInfo->rWnd, IDR_EVENTBOXFRAME))
	{
		if (SetScope(pDefaultInfo->nScope) && SetMode(pDefaultInfo->nMode) && Customize(bDefault)) return TRUE;
		DestroyWindow();
	}
	return FALSE;
}

BOOL CEventBoxWnd::SetTitle(UINT nColumns)
{
	return m_wndView.SetTitle(nColumns);
}
BOOL CEventBoxWnd::SetTitle(UINT nColumns, CONST CUIntArray &nWidths)
{
	return m_wndView.SetTitle(nColumns, nWidths);
}

BOOL CEventBoxWnd::GetTitle(UINT &nColumns) CONST
{
	return m_wndView.GetTitle(nColumns);
}
BOOL CEventBoxWnd::GetTitle(UINT &nColumns, CUIntArray &nWidths) CONST
{
	return m_wndView.GetTitle(nColumns, nWidths);
}
BOOL CEventBoxWnd::GetTitle(CStringArray &szColumns) CONST
{
	return m_wndView.GetTitle(szColumns);
}
BOOL CEventBoxWnd::GetTitle(CStringArray &szColumns, CUIntArray &nWidths) CONST
{
	return m_wndView.GetTitle(szColumns, nWidths);
}

BOOL CEventBoxWnd::SetTitleFont(CFont *pFont)
{
	return m_wndView.SetTitleFont(pFont);
}
BOOL CEventBoxWnd::SetTitleFont(CONST LOGFONT *plfFont)
{
	return m_wndView.SetTitleFont(plfFont);
}

BOOL CEventBoxWnd::GetTitleFont(CFont *pFont) CONST
{
	return m_wndView.GetTitleFont(pFont);
}
BOOL CEventBoxWnd::GetTitleFont(LOGFONT *plfFont) CONST
{
	return m_wndView.GetTitleFont(plfFont);
}

BOOL CEventBoxWnd::SetItemsFont(CFont *pFont)
{
	return m_wndView.SetTextFont(pFont);
}
BOOL CEventBoxWnd::SetItemsFont(CONST LOGFONT *plfFont)
{
	return m_wndView.SetTextFont(plfFont);
}

BOOL CEventBoxWnd::GetItemsFont(CFont *pFont) CONST
{
	return m_wndView.GetTextFont(pFont);
}
BOOL CEventBoxWnd::GetItemsFont(LOGFONT *plfFont) CONST
{
	return m_wndView.GetTextFont(plfFont);
}

BOOL CEventBoxWnd::Start()
{
	StartWatchEvents();
	StartRetrieveEvents();
	StartScheduleEvents();
	StartSchedulePrintJobs();
	Initialize(TRUE);
	UpdateAllPanes();
	return TRUE;
}

BOOL CEventBoxWnd::Prepare(BOOL bDialog)
{
	INT  nResult;

	if (bDialog)
	{
		if ((nResult = m_dlgOpen.Create(this)) == IDCANCEL || nResult <= 0) MDIDestroy();
		return((nResult == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
	}
	return TRUE;
}

BOOL CEventBoxWnd::Check() CONST
{
	CString  szUserName;
	CString  szComputerName;
	CString  szSpacecraftName;

	return(((GetScope() == DISPLAY_SCOPE_LOCAL  &&  GetAccountName(szComputerName, szSpacecraftName, szUserName) && (!GetAccountComputerName().CompareNoCase(szComputerName) || CheckAccountPrivilege(PRIVILEGE_COMPUTERLOGS_VIEW)) && (GetAccountSpacecraftName() == szSpacecraftName || CheckAccountPrivilege(PRIVILEGE_SPACECRAFTLOGS_VIEW)) && (GetAccountUserName() == szUserName || CheckAccountPrivilege(PRIVILEGE_USERLOGS_VIEW))) || GetScope() == DISPLAY_SCOPE_GLOBAL) ? TRUE : FALSE);
}

VOID CEventBoxWnd::Update()
{
	if (!Check())
	{
		for (ReportEvent((IsWindowVisible()) ? USER_INFORMATIONAL_DISPLAY_ACCESS_VIOLATION : USER_NOERROR); GetScope() == DISPLAY_SCOPE_GLOBAL; )
		{
			ActivateFrame(SW_HIDE);
			return;
		}
		DestroyWindow();
		return;
	}
	UpdateAllPanes();
	CDisplayWnd::Update();
}

BOOL CEventBoxWnd::Stop()
{
	FlushAllEvents();
	Initialize(FALSE);
	StopWatchEvents();
	StopRetrieveEvents();
	StopScheduleEvents();
	StopSchedulePrintJobs();
	return TRUE;
}

BOOL CEventBoxWnd::SaveInfo(INT nPage, INT nDisplay, LPCTSTR pszTitle, CONST PDISPLAYINFO pDisplayInfo)
{
	UINT  nCount;
	UINT  nColumns;
	UINT  nMode[2];
	UINT  nLimit[2];
	BOOL  bLocalLog;
	LOGFONT  sFontInfo[2];
	CString  szFileName[3];
	CTimeKey  tStartTime[2];
	CTimeKey  tStopTime[2];
	CUIntArray  nWidths;
	CUIntArray  nColors;
	CByteArray  nScheduleInfo;
	CByteArray  nPrintInfo;
	CStringArray  szTypes;
	CStringArray  szSubtypes;
	CProfile  cProfile;

	return((CDisplayWnd::SaveInfo(nPage, nDisplay, pszTitle, pDisplayInfo) && ((nPage > 0 && pDisplayInfo->nScope == DISPLAY_SCOPE_GLOBAL) || (GetAccountName(szFileName[0], szFileName[1], szFileName[2], bLocalLog) && GetTitle(nColumns, nWidths) && GetTitleFont(&sFontInfo[0]) && GetItemsFont(&sFontInfo[1]) && GetFilterMode(nMode[1]) && GetFilterBehavior(szTypes, szSubtypes) && GetFilterColors(nColors) && GetRetrieveMode(nMode[0]) && GetRetrieveLimit(nLimit[0]) && GetRetrieveStartTime(tStartTime[0]) && GetRetrieveStopTime(tStopTime[0]) && GetScheduleInfo(nScheduleInfo) && GetPrintJobs(nPrintInfo) && cProfile.SetEventBoxLogName(nPage, nDisplay, szFileName[0], szFileName[1], szFileName[2], bLocalLog) && cProfile.SetEventBoxLayoutInfo(nPage, nDisplay, nColumns, nWidths) && cProfile.SetEventBoxFontsInfo(nPage, nDisplay, &sFontInfo[0], &sFontInfo[1]) && cProfile.SetEventBoxFilterInfo(nPage, nDisplay, nMode[1], (GetFilterLimitation(nLimit[1])) ? nLimit[1] : 0, (GetFilterBehavior(nCount)) ? nCount : 0, (GetFilterLimitation(tStartTime[1], tStopTime[1])) ? tStartTime[1] : 0, (GetFilterLimitation(tStartTime[1], tStopTime[1])) ? tStopTime[1] : 0, szTypes, szSubtypes, nColors) && cProfile.SetEventBoxModeInfo(nPage, nDisplay, nMode[0], nLimit[0], tStartTime[0], tStopTime[0]) && cProfile.SetEventBoxScheduleInfo(nPage, nDisplay, nScheduleInfo) && cProfile.SetEventBoxPrintInfo(nPage, nDisplay, nPrintInfo)))) ? TRUE : FALSE);
}

BOOL CEventBoxWnd::LoadInfo(INT nPage, INT nDisplay, CString &szTitle, PDISPLAYINFO pDisplayInfo)
{
	UINT  nCount;
	UINT  nColumns;
	UINT  nMode[2];
	UINT  nLimit[2];
	BOOL  bLocalLog;
	LOGFONT  sFontInfo[2];
	CString  szFileName[3];
	CTimeKey  tStartTime[2];
	CTimeKey  tStopTime[2];
	CUIntArray  nWidths;
	CUIntArray  nColors;
	CByteArray  nScheduleInfo;
	CByteArray  nPrintInfo;
	CStringArray  szTypes;
	CStringArray  szSubtypes;
	CProfile  cProfile;

	return((CDisplayWnd::LoadInfo(nPage, nDisplay, szTitle, pDisplayInfo) && ((nPage > 0 && pDisplayInfo->nScope == DISPLAY_SCOPE_GLOBAL) || (cProfile.GetEventBoxLogName(nPage, nDisplay, szFileName[0], szFileName[1], szFileName[2], bLocalLog) && cProfile.GetEventBoxLayoutInfo(nPage, nDisplay, nColumns, nWidths) && cProfile.GetEventBoxFontsInfo(nPage, nDisplay, &sFontInfo[0], &sFontInfo[1]) && cProfile.GetEventBoxFilterInfo(nPage, nDisplay, nMode[1], nLimit[1], nCount, tStartTime[1], tStopTime[1], szTypes, szSubtypes, nColors) && cProfile.GetEventBoxModeInfo(nPage, nDisplay, nMode[0], nLimit[0], tStartTime[0], tStopTime[0]) && cProfile.GetEventBoxScheduleInfo(nPage, nDisplay, nScheduleInfo) && cProfile.GetEventBoxPrintInfo(nPage, nDisplay, nPrintInfo) && SetAccountName(szFileName[0], szFileName[1], szFileName[2], bLocalLog) && SetTitle(nColumns, nWidths) && SetTitleFont(&sFontInfo[0]) && SetItemsFont(&sFontInfo[1]) && SetFilterMode(nMode[1]) && SetFilterLimitation(nLimit[1]) >= 0 && SetFilterLimitation(tStartTime[1], tStopTime[1]) >= 0 && SetFilterBehavior(nCount) >= 0 && SetFilterBehavior(szTypes, szSubtypes) && SetFilterColors(nColors) && SetRetrieveMode(nMode[0]) && SetRetrieveLimit(nLimit[0]) && SetRetrieveStartTime(tStartTime[0]) && SetRetrieveStopTime(tStopTime[0]) && SetScheduleInfo(nScheduleInfo) && SetPrintJobs(nPrintInfo)))) ? TRUE : FALSE);
}

BOOL CEventBoxWnd::SetLayoutInfo(LPCVOID pData)
{
	INT  cbData;
	DATA  sData;
	UINT  nColumns;
	CUIntArray  nWidths;
	CDisplayLock  cLock(this);

	if (GetScope() == DISPLAY_SCOPE_GLOBAL)
	{
		for (CopyMemory(&sData, pData, ((cbData = (INT)GlobalSize((HGLOBAL)pData)) >= sizeof(DATA)) ? sizeof(DATA) : 0); cbData >= sizeof(DATA) && sData.cbSize == sizeof(DATA) + sData.cbColumns && sData.cbColumns >= 0; )
		{
			for (nColumns = sData.nColumns, nWidths.SetSize(sData.cbColumns / sizeof(UINT)), CopyMemory(nWidths.GetData(), (LPBYTE)pData + (cbData = sizeof(DATA)), sData.cbColumns); SetLayoutInfo(nColumns, nWidths, &sData.sFont[0], &sData.sFont[1], sData.nIndex, sData.nCount, &sData.sScrollInfo[0], &sData.sScrollInfo[1]); ) return TRUE;
			return FALSE;
		}
		return TRUE;
	}
	return FALSE;
}

INT CEventBoxWnd::GetLayoutInfo(LPVOID *pData) CONST
{
	INT  cbData;
	DATA  sData;
	UINT  nColumns;
	LPVOID  pBlock;
	CUIntArray  nWidths;
	CDisplayLock  cLock(this);

	if (GetScope() == DISPLAY_SCOPE_GLOBAL)
	{
		if (GetLayoutInfo(nColumns, nWidths, &sData.sFont[0], &sData.sFont[1], sData.nIndex, sData.nCount, &sData.sScrollInfo[0], &sData.sScrollInfo[1]))
		{
			for (sData.nColumns = nColumns, sData.cbColumns = (INT)(nWidths.GetSize()*sizeof(UINT)), sData.cbSize = sizeof(DATA) + sData.cbColumns; (pBlock = (pData != (LPVOID *)NULL) ? (LPVOID)GlobalReAlloc(*pData, sData.cbSize, GMEM_MOVEABLE | GMEM_ZEROINIT) : (LPVOID)NULL); )
			{
				CopyMemory(pData, &pBlock, sizeof(LPVOID));
				CopyMemory(pBlock, &sData, sizeof(DATA));
				CopyMemory((LPBYTE)pBlock + (cbData = sizeof(DATA)), nWidths.GetData(), sData.cbColumns);
				break;
			}
			return sData.cbSize;
		}
	}
	return 0;
}

BOOL CEventBoxWnd::QueryDefaultInfo(PDISPLAYINFO pDefaultInfo) CONST
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

BOOL CEventBoxWnd::QueryDefaultMenu(CLocaleMenu &cMenu, CImageList &cImages, CUIntArray &nImageIDs) CONST
{
	INT  nIndex;
	INT  nCount;
	INT  iImage;
	UINT  nButtonID;
	UINT  nButtonStyle;
	CBitmap  cBitmap;
	BITMAP  sBitmap;

	for (cImages.DeleteImageList(), nImageIDs.RemoveAll(); cBitmap.LoadBitmap(IDB_EVENTBOXFRAMESMALLIMAGES) && cBitmap.GetBitmap(&sBitmap); )
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
	return cMenu.LoadMenu(IDR_EVENTBOXFRAME);
}

VOID CEventBoxWnd::UpdateBars()
{
	CDisplayLock  cLock(this);

	UpdateItemPane();
	UpdateModePane();
	UpdateSystemPane();
	UpdateSpacecraftPane();
	UpdateUserPane();
}

BOOL CEventBoxWnd::Print(PRINTDLG *pPrintInfo)
{
	INT  nJob;
	INT  nJobs;
	CEventBoxPrintJobs  pJobs;
	CEventBoxPrintJobInfo  *pJobInfo;
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
		if (pJobInfo->GetPrintMode() & EVENTBOX_PRINT_CLEARCOMMENTS)
		{
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~EVENTBOX_PRINT_CLEARCOMMENTS);
			pJobInfo->SetComments(EMPTYSTRING);
			SetPrintJobs(pJobs);
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxWnd::CanPrint() CONST
{
	return((GetEventCount() > 0) ? TRUE : FALSE);
}

BOOL CEventBoxWnd::IsAlerted() CONST
{
	if (m_pEventList->Lock())
	{
		if (!m_pEventList->IsAcknowledged())
		{
			m_pEventList->Unlock();
			return TRUE;
		}
		m_pEventList->Unlock();
	}
	return FALSE;
}

BOOL CEventBoxWnd::ActivateAccount(BOOL bStart)
{
	return(((GetScope() == DISPLAY_SCOPE_GLOBAL  &&  ActivateAccount(GetAccountComputerName(), GetAccountSpacecraftName(), GetAccountUserName(), TRUE, GetMode())) || (GetScope() == DISPLAY_SCOPE_LOCAL && (bStart || UpdateAllPanes()))) ? TRUE : FALSE);
}
BOOL CEventBoxWnd::ActivateAccount(LPCTSTR pszComputerName, LPCTSTR pszSpacecraftName, LPCTSTR pszUserName, BOOL bLocal, UINT nMode)
{
	return SetAccountName(pszComputerName, pszSpacecraftName, pszUserName, bLocal) && SetMode(nMode) && UpdateAllPanes();
}

BOOL CEventBoxWnd::SetAccountName(LPCTSTR pszComputerName, LPCTSTR pszSpacecraftName, LPCTSTR pszUserName, BOOL bLocal)
{
	return m_pEventLog->SetOwner(pszComputerName, pszSpacecraftName, pszUserName, bLocal);
}

BOOL CEventBoxWnd::GetAccountName(CString &szComputerName, CString &szSpacecraftName, CString &szUserName, BOOL &bLocal) CONST
{
	return m_pEventLog->GetOwner(szComputerName, szSpacecraftName, szUserName, bLocal);
}
BOOL CEventBoxWnd::GetAccountName(CString &szComputerName, CString &szSpacecraftName, CString &szUserName) CONST
{
	return m_pEventLog->GetOwner(szComputerName, szSpacecraftName, szUserName);
}

BOOL CEventBoxWnd::SetFilterMode(UINT nMode)
{
	CDisplayLock  cLock(this);

	if (m_pEventList->Lock())
	{
		m_wndView.SortItems(((m_nFilterMode = nMode) & EVENTBOX_FILTER_LISTEVENTS) ? TRUE : FALSE);
		m_pEventList->EnableSound((nMode & EVENTBOX_FILTER_USESOUND) ? TRUE : FALSE);
		m_pEventList->Unlock();
	}
	return TRUE;
}

BOOL CEventBoxWnd::GetFilterMode(UINT &nMode) CONST
{
	nMode = m_nFilterMode;
	return TRUE;
}

BOOL CEventBoxWnd::SetFilterBehavior(UINT nCount)
{
	CDisplayLock  cLock(this);

	if (m_nFilterMode & EVENTBOX_FILTER_AUTOEVENTS)
	{
		m_nFilterCount = nCount;
		return TRUE;
	}
	return FALSE;
}
BOOL CEventBoxWnd::SetFilterBehavior(CONST CStringArray &szTypes, CONST CStringArray &szSubtypes)
{
	CDisplayLock  cLock(this);

	m_szFilterTypes.Copy(szTypes);
	m_szFilterSubtypes.Copy(szSubtypes);
	return TRUE;
}

BOOL CEventBoxWnd::GetFilterBehavior(UINT &nCount) CONST
{
	CDisplayLock  cLock(this);

	if (m_nFilterMode & EVENTBOX_FILTER_AUTOEVENTS)
	{
		nCount = m_nFilterCount;
		return TRUE;
	}
	return FALSE;
}
BOOL CEventBoxWnd::GetFilterBehavior(CStringArray &szTypes, CStringArray &szSubtypes) CONST
{
	INT  nType;
	INT  nTypes;
	CDisplayLock  cLock(this);

	for (szTypes.Copy(m_szFilterTypes), szSubtypes.Copy(m_szFilterSubtypes); !szTypes.GetSize(); )
	{
		for (nType = 0, nTypes = MAXEVENTTYPE - MINEVENTTYPE; nType <= nTypes; nType++)
		{
			szTypes.Add(STRING(MINEVENTTYPE + nType));
			continue;
		}
		break;
	}
	return TRUE;
}

BOOL CEventBoxWnd::SetFilterLimitation(UINT nLimit)
{
	CDisplayLock  cLock(this);

	if (m_nFilterMode & EVENTBOX_FILTER_LIMITBYEVENTS)
	{
		m_nFilterLimit = nLimit;
		return TRUE;
	}
	return FALSE;
}
BOOL CEventBoxWnd::SetFilterLimitation(CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime)
{
	CDisplayLock  cLock(this);

	if (m_nFilterMode & EVENTBOX_FILTER_LIMITBYTIME)
	{
		m_tFilterStartTime = tStartTime;
		m_tFilterStopTime = tStopTime;
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxWnd::GetFilterLimitation(UINT &nLimit) CONST
{
	CDisplayLock  cLock(this);

	if (m_nFilterMode & EVENTBOX_FILTER_LIMITBYEVENTS)
	{
		nLimit = m_nFilterLimit;
		return TRUE;
	}
	return FALSE;
}
BOOL CEventBoxWnd::GetFilterLimitation(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	CDisplayLock  cLock(this);

	if (m_nFilterMode & EVENTBOX_FILTER_LIMITBYTIME)
	{
		tStartTime = m_tFilterStartTime;
		tStopTime = m_tFilterStopTime;
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxWnd::SetFilterColors(CONST CUIntArray &nColors)
{
	CDisplayLock  cLock(this);

	if (nColors.GetSize() == EVENT_CATEGORIES*(EVENT_TYPES - 1))
	{
		m_nFilterColors.Copy(nColors);
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxWnd::GetFilterColors(CUIntArray &nColors) CONST
{
	INT  nCount;
	CDisplayLock  cLock(this);

	if ((nCount = EVENT_CATEGORIES*(EVENT_TYPES - 1)) == m_nFilterColors.GetSize())
	{
		nColors.Copy(m_nFilterColors);
		return TRUE;
	}
	nColors.InsertAt(0, VGA_COLOR_BLACK, nCount);
	nColors.SetSize(nCount);
	return TRUE;
}

BOOL CEventBoxWnd::DoFilter(CONST CEventObject *pEvent) CONST
{
	INT  nType;
	INT  nTypes;
	INT  nSubtype;
	INT  nSubtypes;
	UINT  nCategory;
	UINT  nFilterMode;
	CTimeKey  tFilterStartTime;
	CTimeKey  tFilterStopTime;
	CStringArray  szSubtypes;
	CStringArray  szTypes;
	CDisplayLock  cLock(this);

	for (nType = 0, nTypes = (GetFilterMode(nFilterMode) && GetFilterBehavior(szTypes, szSubtypes) && ((nCategory = pEvent->GetCategory()) == EVENT_CATEGORY_SYSTEM && (nFilterMode & EVENTBOX_FILTER_SYSTEM)) || (nCategory == EVENT_CATEGORY_SPACECRAFT && (nFilterMode & EVENTBOX_FILTER_SPACECRAFT)) || (nCategory == EVENT_CATEGORY_USER && (nFilterMode & EVENTBOX_FILTER_USER)) && ((GetFilterLimitation(tFilterStartTime, tFilterStopTime) && pEvent->GetAuditTime() >= tFilterStartTime && pEvent->GetAuditTime() <= tFilterStopTime) || (nFilterMode & EVENTBOX_FILTER_LIMITBYTIME) != EVENTBOX_FILTER_LIMITBYTIME)) ? (INT)szTypes.GetSize() : -1; nType < nTypes; nType++)
	{
		if (pEvent->GetType() == szTypes.GetAt(nType)) break;
		continue;
	}
	for (nSubtype = 0, nSubtypes = (INT)szSubtypes.GetSize(); nSubtype < nSubtypes; nSubtype++)
	{
		if (pEvent->GetSubtype() == szSubtypes.GetAt(nSubtype)) break;
		continue;
	}
	return(((!nTypes || nType < nTypes) && (!nSubtypes || nSubtype < nSubtypes)) ? TRUE : FALSE);
}

BOOL CEventBoxWnd::DoFilterBehavior(CEventObject *pEvent, UINT nFlag)
{
	UINT  nFilterMode;
	CEventObject  *pEventObject;
	CDisplayLock  cLock(this);

	if (GetFilterMode(nFilterMode))
	{
		if (nFlag == EVENTBOX_FILTER_AUTOACKNOWLEDGE)
		{
			for (; nFilterMode & EVENTBOX_FILTER_AUTOACKNOWLEDGE; )
			{
				pEvent->Acknowledge();
				break;
			}
			return TRUE;
		}
		if (nFlag == EVENTBOX_FILTER_BRINGEVENTS)
		{
			for (; GetScope() == DISPLAY_SCOPE_GLOBAL; )
			{
				if (!IsZoomed()) SendNotifyMessage(WM_SHOWWINDOW, TRUE, (nFilterMode & EVENTBOX_FILTER_BRINGEVENTS) ? EVENTBOX_FILTER_BRINGEVENTS : -1);
				break;
			}
			return TRUE;
		}
		if (nFlag == EVENTBOX_FILTER_NOTIFY)
		{
			if (GetScope() == DISPLAY_SCOPE_LOCAL)
			{
				if ((nFilterMode & EVENTBOX_FILTER_NOTIFY) && !IsRetrievingEvents())
				{
					if ((pEventObject = new CEventObject(SYSTEM_INFORMATIONAL_EVENT_OCCURRENCE)))
					{
						if (pEvent->GetMessage() == pEventObject->GetMessage())
						{
							delete pEventObject;
							return TRUE;
						}
						pEventObject->SetUser(GetAccountUserName());
						pEventObject->SetAudition(AUDIO_STANDARD_SOUND);
						pEventObject->SetAuditTime(CTime::GetCurrentTime().GetTime());
						pEventObject->SetAuditColor(VGA_COLOR_BLACK);
						pEventObject->Acknowledge(FALSE);
						pEventObject->Show();
						ReportEvent(pEventObject);
						return TRUE;
					}
					return FALSE;
				}
				return(((nFilterMode & EVENTBOX_FILTER_NOTIFY) != EVENTBOX_FILTER_NOTIFY) ? TRUE : FALSE);
			}
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CEventBoxWnd::DoFilterLimit(CEventObject *pEvent)
{
	UINT  nFilterLimit;
	CDisplayLock  cLock(this);

	if (m_pEventList->Lock())
	{
		if (GetFilterLimitation(nFilterLimit))
		{
			if (m_pEventList->GetSize() >= (INT)nFilterLimit)
			{
				if (m_wndView.DeleteItem((pEvent = m_pEventList->GetAt(0))) && m_pEventList->Remove(0))
				{
					m_pEventList->Unlock();
					delete pEvent;
					return TRUE;
				}
				m_pEventList->Unlock();
				return FALSE;
			}
		}
		else
		{
			if (m_pEventList->GetSize() >= EVENTBOX_FILTER_DEFAULTNOLIMIT)
			{
				if (m_wndView.DeleteItem((pEvent = m_pEventList->GetAt(0))) && m_pEventList->Remove(0))
				{
					m_pEventList->Unlock();
					delete pEvent;
					return TRUE;
				}
				m_pEventList->Unlock();
				return FALSE;
			}
		}
		m_pEventList->Unlock();
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxWnd::DoFilterColor(CEventObject *pEvent)
{
	INT  nIndex[2];
	UINT  nCategory;
	CString  szType;
	CUIntArray  nFilterColors;
	CDisplayLock  cLock(this);

	if (GetFilterColors(nFilterColors))
	{
		for (nIndex[0] = ((nCategory = pEvent->GetCategory() & EVENT_CATEGORY_ALL)) ? 0 : -1, nIndex[1] = 0; nIndex[0] >= 0; nIndex[0]++)
		{
			if (nCategory & TRUE) break;
			nCategory >>= 1;
		}
		if (nIndex[0] >= 0)
		{
			if ((szType = pEvent->GetType()) == STRING(IDS_EVENTTYPE_SUCCESS) && pEvent->GetSubtype().IsEmpty())
			{
				pEvent->SetAuditColor(nFilterColors.GetAt(nIndex[0] * (EVENT_TYPES - 1)));
				return TRUE;
			}
			for (nIndex[1]++; szType == STRING(IDS_EVENTTYPE_INFORMATIONAL) && pEvent->GetSubtype().IsEmpty(); )
			{
				pEvent->SetAuditColor(nFilterColors.GetAt(nIndex[0] * (EVENT_TYPES - 1) + nIndex[1]));
				return TRUE;
			}
			for (nIndex[1]++; szType == STRING(IDS_EVENTTYPE_WARNING) && pEvent->GetSubtype().IsEmpty(); )
			{
				pEvent->SetAuditColor(nFilterColors.GetAt(nIndex[0] * (EVENT_TYPES - 1) + nIndex[1]));
				return TRUE;
			}
			for (nIndex[1]++; szType == STRING(IDS_EVENTTYPE_ERROR) && pEvent->GetSubtype().IsEmpty(); )
			{
				pEvent->SetAuditColor(nFilterColors.GetAt(nIndex[0] * (EVENT_TYPES - 1) + nIndex[1]));
				break;
			}
			return TRUE;
		}
		return((!nCategory) ? TRUE : FALSE);
	}
	return FALSE;
}

BOOL CEventBoxWnd::ShowEvent(UINT nFlags, LPCTSTR pszEvent, BOOL bAudition)
{
	CEventObject  *pEvent;

	if ((pEvent = (nFlags & EVENT_CATEGORY_ALL) ? new CEventObject : (CEventObject *)NULL))
	{
		for (pEvent->SetCategory(nFlags & EVENT_CATEGORY_ALL), pEvent->SetType((nFlags & EVENT_TYPE_SUCCESS) ? STRING(IDS_EVENTTYPE_SUCCESS) : ((nFlags & EVENT_TYPE_INFORMATIONAL) ? STRING(IDS_EVENTTYPE_INFORMATIONAL) : ((nFlags & EVENT_TYPE_WARNING) ? STRING(IDS_EVENTTYPE_WARNING) : ((nFlags & EVENT_TYPE_ERROR) ? STRING(IDS_EVENTTYPE_ERROR) : EMPTYSTRING)))), pEvent->SetUser(GetAccountUserName()), pEvent->SetMessage(pszEvent), pEvent->SetAudition((bAudition) ? AUDIO_STANDARD_SOUND : AUDIO_NO_SOUND), pEvent->SetAuditTime(CTime::GetCurrentTime().GetTime()), pEvent->SetAuditColor(VGA_COLOR_BLACK), pEvent->Acknowledge(), pEvent->Show(); !ShowEvent(pEvent); )
		{
			delete pEvent;
			return FALSE;
		}
		return TRUE;
	}
	return(((nFlags & EVENT_CATEGORY_ALL) == 0) ? TRUE : FALSE);
}
BOOL CEventBoxWnd::ShowEvent(CONST EVENT_DESCRIPTOR sEvent, BOOL bAudition)
{
	CEventObject  *pEvent;

	if ((pEvent = (sEvent.Opcode != 0) ? new CEventObject(sEvent) : (CEventObject *)NULL))
	{
		for (pEvent->SetUser(GetAccountUserName()), pEvent->SetAudition((bAudition) ? AUDIO_STANDARD_SOUND : AUDIO_NO_SOUND), pEvent->SetAuditTime(CTime::GetCurrentTime().GetTime()), pEvent->SetAuditColor(VGA_COLOR_BLACK), pEvent->Acknowledge(), pEvent->Show(); ShowEvent(pEvent); ) return TRUE;
		delete pEvent;
	}
	return((!sEvent.Opcode) ? TRUE : FALSE);
}
BOOL CEventBoxWnd::ShowEvent(CEventObject *pEvent, BOOL bSelect, BOOL bRedraw)
{
	INT  nIndex;
	UINT  nCategory;
	CDisplayLock  cLock(this);

	if (m_pEventList->Lock())
	{
		if (GetScope() == DISPLAY_SCOPE_GLOBAL)
		{
			if (DoFilterLimit(pEvent) && DoFilterBehavior(pEvent) && DoFilterColor(pEvent))
			{
				for (nIndex = -1; DoFilter(pEvent) && (nIndex = m_pEventList->Add(pEvent)) >= 0 && ((!bSelect && m_wndView.AddItem(pEvent, bRedraw) >= 0) || (bSelect && m_wndView.SetCurText(m_wndView.AddItem(pEvent, bRedraw)))) && DoFilterBehavior(pEvent, EVENTBOX_FILTER_BRINGEVENTS); )
				{
					if (IsRetrievingEvents())
					{
						m_pEventList->Unlock();
						return TRUE;
					}
					if (m_pEventLog->Open((nCategory = (pEvent->GetCategory() == EVENT_CATEGORY_SYSTEM) ? EVENTLOG_CATEGORY_SYSTEM : ((pEvent->GetCategory() == EVENT_CATEGORY_SPACECRAFT) ? EVENTLOG_CATEGORY_SPACECRAFT : ((pEvent->GetCategory() == EVENT_CATEGORY_USER) ? EVENTLOG_CATEGORY_USER : EVENTLOG_CATEGORY_ALL))), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite, (BOOL)FALSE))
					{
						if (m_pEventLog->Write(pEvent))
						{
							DoEventNotification(pEvent);
							UpdateAlertStatus();
							UpdatePrintStatus();
							UpdateItemPane();
						}
						m_pEventLog->Close(nCategory);
					}
					m_pEventList->Unlock();
					return TRUE;
				}
				if (!DoFilter(pEvent))
				{
					if (!IsRetrievingEvents())
					{
						if (m_pEventLog->Open((nCategory = (pEvent->GetCategory() == EVENT_CATEGORY_SYSTEM) ? EVENTLOG_CATEGORY_SYSTEM : ((pEvent->GetCategory() == EVENT_CATEGORY_SPACECRAFT) ? EVENTLOG_CATEGORY_SPACECRAFT : ((pEvent->GetCategory() == EVENT_CATEGORY_USER) ? EVENTLOG_CATEGORY_USER : EVENTLOG_CATEGORY_ALL))), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite, (BOOL)FALSE))
						{
							if (m_pEventLog->Write(pEvent)) UpdateAlertStatus();
							m_pEventLog->Close(nCategory);
						}
					}
					m_pEventList->Unlock();
					delete pEvent;
					return TRUE;
				}
				m_pEventList->Remove(nIndex);
				m_wndView.DeleteItem(pEvent);
			}
		}
		if (GetScope() == DISPLAY_SCOPE_LOCAL)
		{
			if (DoFilterLimit(pEvent) && DoFilterBehavior(pEvent) && DoFilterColor(pEvent))
			{
				for (nIndex = -1; DoFilter(pEvent) && (nIndex = m_pEventList->Add(pEvent)) >= 0 && ((!bSelect && m_wndView.AddItem(pEvent, bRedraw) >= 0) || (bSelect && m_wndView.SetCurText(m_wndView.AddItem(pEvent, bRedraw)))) && DoFilterBehavior(pEvent, EVENTBOX_FILTER_NOTIFY); )
				{
					for (UpdateAlertStatus(), UpdatePrintStatus(); bRedraw; )
					{
						UpdateItemPane();
						break;
					}
					m_pEventList->Unlock();
					return TRUE;
				}
				if (!DoFilter(pEvent))
				{
					m_pEventList->Unlock();
					delete pEvent;
					return TRUE;
				}
				m_pEventList->Remove(nIndex);
				m_wndView.DeleteItem(pEvent);
			}
		}
		m_pEventList->Unlock();
	}
	m_pEventLog->Report(SYSTEM_WARNING_EVENT_DISPLAY_FAILURE);
	return FALSE;
}

BOOL CEventBoxWnd::SetCurEvent(CONST CEventObject *pEvent)
{
	return m_wndView.SetCurItem(pEvent);
}

INT CEventBoxWnd::GetCurEvent(CEventObject *pEvent) CONST
{
	return m_wndView.GetCurItem(pEvent);
}

BOOL CEventBoxWnd::ScheduleEvent(CEventObject *pEvent)
{
	UINT  nCycles;
	CTimeKey  tTime[2];
	CTimeKey  tTimeKey;
	CTimeSpan  tPeriod;

	if (m_pEventList->Lock())
	{
		for (tTimeKey -= m_pEventList->GetScheduleOffset().GetTime(); (tTime[0] = pEvent->GetAuditTime()) < tTimeKey && pEvent->GetAuditPeriod(tPeriod, tTime[1], nCycles); )
		{
			pEvent->SetAuditTime(tTime[0].GetTime() + ((tTimeKey.GetTime() - tTime[0].GetTime()) / tPeriod.GetTotalSeconds() + 1)*tPeriod.GetTotalSeconds());
			pEvent->SetAuditPeriod(tPeriod, tTime[1], (nCycles > 0) ? (UINT)((tTime[1].GetTime() - tTime[0].GetTime()) / tPeriod.GetTotalSeconds()) : 0);
			break;
		}
		if (pEvent->GetAuditTime() >= tTimeKey && (tTime[1] >= tTimeKey || !tTime[1].GetTime()) && m_pEventList->Add(pEvent, TRUE) >= 0)
		{
			m_cAlertStatus.SetEvent();
			m_pEventList->Unlock();
			return TRUE;
		}
		m_pEventList->Unlock();
	}
	return FALSE;
}

BOOL CEventBoxWnd::AcknowledgeEvent(CEventObject *pEvent)
{
	CDisplayLock  cLock(this);

	if (m_pEventList->Lock())
	{
		m_pEventList->Acknowledge(pEvent);
		m_wndView.AcknowledgeItem(pEvent);
		m_pEventList->Unlock();
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxWnd::AcknowledgeAllEvents()
{
	INT  nItem;
	INT  nItems;
	CEventObject  *pEvent;
	CDisplayLock  cLock(this);

	if (m_pEventList->Lock())
	{
		for (nItem = 0, nItems = (INT)m_pEventList->GetSize(); nItem < nItems; nItem++)
		{
			if ((pEvent = m_pEventList->GetAt(nItem)) && !pEvent->IsAcknowledged())
			{
				m_pEventList->Acknowledge(pEvent);
				m_wndView.AcknowledgeItem(pEvent);
			}
		}
		m_pEventList->Unlock();
		return TRUE;
	}
	return FALSE;
}

VOID CEventBoxWnd::DoEventNotification(CONST CEventObject *pEvent)
{
	UINT  nAlertType;
	CString  szNotification;
	CStringArray  szRecipients;

	for (; pEvent->GetNotification(nAlertType, szNotification) && pEvent->GetNotificationRecipients(szRecipients) >= 0; )
	{
		DoNotification(szNotification, pEvent->GetMessage(), nAlertType, szRecipients);
		break;
	}
}

VOID CEventBoxWnd::FlushAllEvents()
{
	if (GetScope() == DISPLAY_SCOPE_GLOBAL)
	{
		if (m_pEventLog->Open(EVENTLOG_CATEGORY_ALL, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite))
		{
			if (!m_pEventLog->FlushAll()) m_pEventLog->Report(SYSTEM_WARNING_EVENTLOG_WRITE_FAILURE);
			m_pEventLog->Close();
		}
	}
}

BOOL CEventBoxWnd::CanFlushEvents() CONST
{
	if (GetScope() == DISPLAY_SCOPE_GLOBAL)
	{
		if (m_pEventLog->Open(EVENTLOG_CATEGORY_ALL, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite))
		{
			if (m_pEventLog->CanFlush())
			{
				m_pEventLog->Close();
				return TRUE;
			}
			m_pEventLog->Close();
			return FALSE;
		}
		return TRUE;
	}
	return FALSE;
}

VOID CEventBoxWnd::CopyEvents(UINT nCode)
{
	m_wndView.CopyItems(nCode);
}

VOID CEventBoxWnd::RefreshAllEvents(BOOL bSelect)
{
	m_wndView.RefreshItems(bSelect);
}

BOOL CEventBoxWnd::DeleteAllEvents(BOOL bAll)
{
	INT  nItem;
	INT  nItems;
	BOOL  bSound;
	CEventObject  *pEvent;
	CDisplayLock  cLock(this);

	if (m_pEventList->Lock())
	{
		for (nItem = m_pEventList->GetScheduleIndex(), nItems = (bAll) ? (INT)m_pEventList->GetSize() : 0, bSound = m_pEventList->IsSoundEnabled(), m_pEventList->EnableSound(FALSE), m_wndView.DeleteAllItems(); nItem < nItems; nItem++)
		{
			if ((pEvent = m_pEventList->GetAt(nItem)) && m_pEventList->Remove(nItem))
			{
				delete pEvent;
				nItems--;
				nItem--;
			}
		}
		for (nItem = 0, nItems = m_pEventList->GetScheduleIndex(); nItem < nItems; nItem++)
		{
			if ((pEvent = m_pEventList->GetAt(nItem)) && m_pEventList->Remove(nItem))
			{
				delete pEvent;
				nItems--;
				nItem--;
			}
		}
		for (UpdateItemPane(); (!bAll && m_pEventList->GetScheduleIndex() == m_pEventList->GetSize()) || (bAll && !m_pEventList->GetSize()); )
		{
			m_pEventList->EnableSound(bSound);
			m_pEventList->Unlock();
			return TRUE;
		}
		m_pEventList->EnableSound(bSound);
		m_pEventList->Unlock();
	}
	return FALSE;
}

INT CEventBoxWnd::GetEventCount(BOOL bAll) CONST
{
	INT  nCount;

	if (m_pEventList->Lock())
	{
		nCount = (!bAll) ? m_pEventList->GetScheduleIndex() : (INT)m_pEventList->GetSize();
		m_pEventList->Unlock();
		return nCount;
	}
	return 0;
}

BOOL CEventBoxWnd::StartRetrieveEvents(UINT nMode, UINT nLimit, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime)
{
	SetRetrieveMode(nMode);
	SetRetrieveLimit(nLimit);
	SetRetrieveStartTime(tStartTime);
	SetRetrieveStopTime(tStopTime);
	return StartRetrieveEvents();
}
BOOL CEventBoxWnd::StartRetrieveEvents()
{
	CEvent  bInit;

	if (GetScope() == DISPLAY_SCOPE_LOCAL)
	{
		for (StopRetrieveEvents(); GetMode() == DISPLAY_MODE_HISTORY && !GetEventCount(TRUE);)
		{
			if (m_cRetrieveThread.Start(this, bInit, EVENTLOG_CATEGORY_ALL, GetRetrieveMode(), GetRetrieveLimit(), GetRetrieveStartTime(), GetRetrieveStopTime(), &m_bRetrieveFlag, m_cRetrieveManual) && UpdateAllPanes())
			{
				WaitForSingleObject(bInit, INFINITE);
				return TRUE;
			}
			ReportEvent(SYSTEM_WARNING_EVENTLOG_RETRIEVE_FAILURE);
			return FALSE;
		}
	}
	return RetrieveAutoEvents();
}

BOOL CEventBoxWnd::IsRetrievingEvents(BOOL bManual) CONST
{
	return(((m_bRetrieveFlag  &&  !bManual) || (m_bRetrieveFlag == -TRUE  &&  bManual)) ? TRUE : FALSE);
}

BOOL CEventBoxWnd::RetrieveMoreEvents()
{
	return((IsRetrievingEvents(TRUE) && m_cRetrieveManual.SetEvent()) ? TRUE : FALSE);
}

BOOL CEventBoxWnd::RetrieveAutoEvents()
{
	UINT  nIndex;
	UINT  nCount;
	BOOL  bSound;
	BOOL  bLimit;
	CEventList  cEventList;
	CEventObject  *pEvent;
	CDisplayLock  cLock(this);

	if (m_pEventList->Lock())
	{
		if (GetMode() == DISPLAY_MODE_REALTIME)
		{
			if (!IsWatchingEvents() && !GetEventCount())
			{
				for (cEventList.EnableSound(FALSE); m_pEventLog->Open(EVENTLOG_CATEGORY_ALL, CFile::modeRead); )
				{
					if (m_pEventLog->ReadAll(cEventList, EVENTLOG_CATEGORY_ALL))
					{
						for (nIndex = 0, nCount = (UINT)cEventList.GetSize(), m_pEventLog->Close(EVENTLOG_CATEGORY_ALL), bSound = m_pEventList->IsSoundEnabled(), m_pEventList->EnableSound(FALSE), InterlockedExchange(&m_bRetrieveFlag, TRUE), UpdateAllPanes(); nIndex < nCount; nIndex++)
						{
							if ((pEvent = cEventList.GetAt(nIndex)))
							{
								if (DoFilter(pEvent))
								{
									pEvent->Acknowledge();
									continue;
								}
								if (cEventList.Remove(nIndex))
								{
									delete pEvent;
									nIndex--;
									nCount--;
									continue;
								}
							}
							cEventList.RemoveAll();
							break;
						}
						for (nIndex = ((bLimit = GetFilterBehavior(nCount))) ? (UINT)max(cEventList.GetSize() - (INT)nCount, 0) : -1, nCount = (bLimit) ? (UINT)cEventList.GetSize() : 0; nIndex < nCount; nIndex++)
						{
							if ((pEvent = cEventList.GetAt(nIndex)))
							{
								if (ShowEvent(pEvent, FALSE, FALSE))
								{
									cEventList.RemoveAt(nIndex);
									nIndex--;
									nCount--;
								}
							}
						}
						for (RefreshAllEvents(); (!bLimit || !cEventList.GetSize()) && UpdateAllPanes(); )
						{
							InterlockedExchange(&m_bRetrieveFlag, FALSE);
							m_pEventList->EnableSound(bSound);
							m_pEventList->Unlock();
							return TRUE;
						}
						InterlockedExchange(&m_bRetrieveFlag, FALSE);
						m_pEventList->EnableSound(bSound);
						m_pEventList->Unlock();
						return FALSE;
					}
					m_pEventLog->Close();
					break;
				}
				m_pEventList->Unlock();
				return FALSE;
			}
		}
		m_pEventList->Unlock();
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxWnd::StopRetrieveEvents()
{
	return((IsRetrievingEvents()) ? m_cRetrieveThread.Stop() : TRUE);
}

BOOL CEventBoxWnd::SetRetrieveMode(UINT nMode)
{
	CDisplayLock  cLock(this);

	m_bRetrieveFlag = ((m_nRetrieveMode = nMode)) ? ((nMode & EVENTBOX_RETRIEVE_MANUAL) ? -TRUE : TRUE) : FALSE;
	return TRUE;
}

BOOL CEventBoxWnd::GetRetrieveMode(UINT &nMode) CONST
{
	nMode = m_nRetrieveMode;
	return TRUE;
}
UINT CEventBoxWnd::GetRetrieveMode() CONST
{
	return m_nRetrieveMode;
}

BOOL CEventBoxWnd::SetRetrieveLimit(UINT nLimit)
{
	m_nRetrieveLimit = nLimit;
	return TRUE;
}

BOOL CEventBoxWnd::GetRetrieveLimit(UINT &nLimit) CONST
{
	nLimit = m_nRetrieveLimit;
	return TRUE;
}
UINT CEventBoxWnd::GetRetrieveLimit() CONST
{
	return m_nRetrieveLimit;
}

BOOL CEventBoxWnd::SetRetrieveStartTime(TIMEKEY tStartTime)
{
	CDisplayLock  cLock(this);

	m_tRetrieveStartTime = tStartTime;
	return TRUE;
}
BOOL CEventBoxWnd::SetRetrieveStartTime(CONST CTimeKey &tStartTime)
{
	CDisplayLock  cLock(this);

	m_tRetrieveStartTime = tStartTime;
	return TRUE;
}

BOOL CEventBoxWnd::GetRetrieveStartTime(CTimeKey &tStartTime) CONST
{
	CDisplayLock  cLock(this);

	tStartTime = m_tRetrieveStartTime;
	return TRUE;
}
CTimeKey CEventBoxWnd::GetRetrieveStartTime() CONST
{
	CDisplayLock  cLock(this);

	return m_tRetrieveStartTime;
}

BOOL CEventBoxWnd::SetRetrieveStopTime(TIMEKEY tStopTime)
{
	CDisplayLock  cLock(this);

	m_tRetrieveStopTime = tStopTime;
	return TRUE;
}
BOOL CEventBoxWnd::SetRetrieveStopTime(CONST CTimeKey &tStopTime)
{
	CDisplayLock  cLock(this);

	m_tRetrieveStopTime = tStopTime;
	return TRUE;
}

BOOL CEventBoxWnd::GetRetrieveStopTime(CTimeKey &tStopTime) CONST
{
	CDisplayLock  cLock(this);

	tStopTime = m_tRetrieveStopTime;
	return TRUE;
}
CTimeKey CEventBoxWnd::GetRetrieveStopTime() CONST
{
	CDisplayLock  cLock(this);

	return m_tRetrieveStopTime;
}

VOID CEventBoxWnd::ShowEventDetails(CEventObject *pEvent)
{
	ReportEvent((m_dlgDetails.Create(this, pEvent) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

VOID CEventBoxWnd::ShowSearchEventTimeDetails()
{
	ReportEvent((!m_dlgSearchTime.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

VOID CEventBoxWnd::ShowSearchEventCategoryDetails()
{
	ReportEvent((!m_dlgSearchCategory.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

VOID CEventBoxWnd::ShowSearchEventTypeDetails()
{
	ReportEvent((!m_dlgSearchType.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

VOID CEventBoxWnd::ShowSearchEventMessageDetails()
{
	ReportEvent((!m_dlgSearchMessage.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

VOID CEventBoxWnd::ShowSearchEventCommentsDetails()
{
	ReportEvent((!m_dlgSearchComments.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

VOID CEventBoxWnd::ShowSearchEventUserDetails()
{
	ReportEvent((!m_dlgSearchUser.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

VOID CEventBoxWnd::ShowSearchEventRecipientsDetails()
{
	ReportEvent((!m_dlgSearchRecipients.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

BOOL CEventBoxWnd::SearchEventByTime(CONST CTimeKey &tTime, BOOL bDown, BOOL bAll, BOOL bMatch)
{
	INT  nItem;
	INT  nItems;
	BOOL  bSuccess;
	CEventObject  *pEvent[2];
	CDisplayLock  cLock(this);

	if (m_pEventList->Lock())
	{
		if ((pEvent[0] = new CEventObject))
		{
			for (nItem = ((nItem = GetCurEvent(pEvent[0])) >= 0 && !bAll) ? ((!bDown) ? (nItem - 1) : (nItem + 1)) : ((!bDown) ? (m_pEventList->GetScheduleIndex() - 1) : 0), nItems = (bDown) ? m_pEventList->GetScheduleIndex() : 0, bSuccess = FALSE; (bDown && nItem < nItems) || (!bDown && nItem >= nItems); nItem = (bDown) ? (nItem + 1) : (nItem - 1))
			{
				if ((pEvent[1] = m_pEventList->GetAt(nItem)) != (CEventObject *)NULL)
				{
					if (bMatch  &&  pEvent[1]->GetAuditTime() == tTime)
					{
						SetCurEvent(pEvent[1]);
						bSuccess = TRUE;
						break;
					}
					if (!bMatch && (bDown && (pEvent[1]->GetAuditTime() >= tTime || nItem == nItems)) || (!bDown && (pEvent[1]->GetAuditTime() <= tTime || nItem < 0)))
					{
						SetCurEvent(pEvent[1]);
						bSuccess = TRUE;
						break;
					}
				}
			}
			delete pEvent[0];
			m_pEventList->Unlock();
			return bSuccess;
		}
		m_pEventList->Unlock();
	}
	return FALSE;
}

BOOL CEventBoxWnd::SearchEventByCategory(UINT nCategory, BOOL bDown, BOOL bAll)
{
	INT  nItem;
	INT  nItems;
	BOOL  bSuccess;
	CEventObject  *pEvent[2];
	CDisplayLock  cLock(this);

	if (m_pEventList->Lock())
	{
		if ((pEvent[0] = new CEventObject))
		{
			for (nItem = ((nItem = GetCurEvent(pEvent[0])) >= 0 && !bAll) ? ((!bDown) ? (nItem - 1) : (nItem + 1)) : ((!bDown) ? (m_pEventList->GetScheduleIndex() - 1) : 0), nItems = (bDown) ? m_pEventList->GetScheduleIndex() : 0, bSuccess = FALSE; (bDown && nItem < nItems) || (!bDown && nItem >= nItems); nItem = (bDown) ? (nItem + 1) : (nItem - 1))
			{
				if ((pEvent[1] = m_pEventList->GetAt(nItem)))
				{
					if (pEvent[1]->GetCategory() == nCategory)
					{
						SetCurEvent(pEvent[1]);
						bSuccess = TRUE;
						break;
					}
				}
			}
			delete pEvent[0];
			m_pEventList->Unlock();
			return bSuccess;
		}
		m_pEventList->Unlock();
	}
	return FALSE;
}

BOOL CEventBoxWnd::SearchEventByType(LPCTSTR pszType, BOOL bDown, BOOL bAll, BOOL bCase)
{
	INT  nItem;
	INT  nItems;
	BOOL  bSuccess;
	CEventObject  *pEvent[2];
	CDisplayLock  cLock(this);

	if (m_pEventList->Lock())
	{
		if ((pEvent[0] = new CEventObject))
		{
			for (nItem = ((nItem = GetCurEvent(pEvent[0])) >= 0 && !bAll) ? ((!bDown) ? (nItem - 1) : (nItem + 1)) : ((!bDown) ? (m_pEventList->GetScheduleIndex() - 1) : 0), nItems = (bDown) ? m_pEventList->GetScheduleIndex() : 0, bSuccess = FALSE; (bDown && nItem < nItems) || (!bDown && nItem >= nItems); nItem = (bDown) ? (nItem + 1) : (nItem - 1))
			{
				if ((pEvent[1] = m_pEventList->GetAt(nItem)) != (CEventObject *)NULL)
				{
					if ((bCase  &&  !pEvent[1]->GetType().Compare(pszType)))
					{
						SetCurEvent(pEvent[1]);
						bSuccess = TRUE;
						break;
					}
					if ((!bCase  &&  !pEvent[1]->GetType().CompareNoCase(pszType)))
					{
						SetCurEvent(pEvent[1]);
						bSuccess = TRUE;
						break;
					}
				}
			}
			delete pEvent[0];
			m_pEventList->Unlock();
			return bSuccess;
		}
		m_pEventList->Unlock();
	}
	return FALSE;
}

BOOL CEventBoxWnd::SearchEventByMessage(LPCTSTR pszMessage, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord)
{
	INT  nItem;
	INT  nItems;
	BOOL  bSuccess;
	CString  szInfo[2];
	CEventObject  *pEvent[2];
	CDisplayLock  cLock(this);

	if (m_pEventList->Lock())
	{
		if ((pEvent[0] = new CEventObject))
		{
			for (nItem = ((nItem = GetCurEvent(pEvent[0])) >= 0 && !bAll) ? ((!bDown) ? (nItem - 1) : (nItem + 1)) : ((!bDown) ? (m_pEventList->GetScheduleIndex() - 1) : 0), nItems = (bDown) ? m_pEventList->GetScheduleIndex() : 0, szInfo[0] = pszMessage, bSuccess = FALSE; (bDown && nItem < nItems) || (!bDown && nItem >= nItems); nItem = (bDown) ? (nItem + 1) : (nItem - 1))
			{
				if ((pEvent[1] = m_pEventList->GetAt(nItem)) != (CEventObject *)NULL)
				{
					for (szInfo[1] = pEvent[1]->GetMessage(); !bCase; )
					{
						szInfo[0].MakeUpper();
						szInfo[1].MakeUpper();
						break;
					}
					if ((!bWord  &&  szInfo[1].Find(szInfo[0]) >= 0) || (bWord && (!szInfo[1].Find(szInfo[0] + SPACE) || szInfo[1].Find(SPACE + szInfo[0] + SPACE) > 0)))
					{
						SetCurEvent(pEvent[1]);
						bSuccess = TRUE;
						break;
					}
				}
			}
			delete pEvent[0];
			m_pEventList->Unlock();
			return bSuccess;
		}
		m_pEventList->Unlock();
	}
	return FALSE;
}

BOOL CEventBoxWnd::SearchEventByComments(LPCTSTR pszComments, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord)
{
	INT  nItem;
	INT  nItems;
	BOOL  bSuccess;
	CString  szInfo[2];
	CEventObject  *pEvent[2];
	CDisplayLock  cLock(this);

	if (m_pEventList->Lock())
	{
		if ((pEvent[0] = new CEventObject))
		{
			for (nItem = ((nItem = GetCurEvent(pEvent[0])) >= 0 && !bAll) ? ((!bDown) ? (nItem - 1) : (nItem + 1)) : ((!bDown) ? (m_pEventList->GetScheduleIndex() - 1) : 0), nItems = (bDown) ? m_pEventList->GetScheduleIndex() : 0, szInfo[0] = pszComments, bSuccess = FALSE; (bDown && nItem < nItems) || (!bDown && nItem >= nItems); nItem = (bDown) ? (nItem + 1) : (nItem - 1))
			{
				if ((pEvent[1] = m_pEventList->GetAt(nItem)) != (CEventObject *)NULL)
				{
					for (szInfo[1] = pEvent[1]->GetComments(); !bCase; )
					{
						szInfo[0].MakeUpper();
						szInfo[1].MakeUpper();
						break;
					}
					if ((!bWord  &&  szInfo[1].Find(szInfo[0]) >= 0) || (bWord && (!szInfo[1].Find(szInfo[0] + SPACE) || szInfo[1].Find(SPACE + szInfo[0] + SPACE) > 0)))
					{
						SetCurEvent(pEvent[1]);
						bSuccess = TRUE;
						break;
					}
				}
			}
			delete pEvent[0];
			m_pEventList->Unlock();
			return bSuccess;
		}
		m_pEventList->Unlock();
	}
	return FALSE;
}

BOOL CEventBoxWnd::SearchEventByUser(LPCTSTR pszUser, BOOL bDown, BOOL bAll)
{
	INT  nItem;
	INT  nItems;
	BOOL  bSuccess;
	CEventObject  *pEvent[2];
	CDisplayLock  cLock(this);

	if (m_pEventList->Lock())
	{
		if ((pEvent[0] = new CEventObject))
		{
			for (nItem = ((nItem = GetCurEvent(pEvent[0])) >= 0 && !bAll) ? ((!bDown) ? (nItem - 1) : (nItem + 1)) : ((!bDown) ? (m_pEventList->GetScheduleIndex() - 1) : 0), nItems = (bDown) ? m_pEventList->GetScheduleIndex() : 0, bSuccess = FALSE; (bDown && nItem < nItems) || (!bDown && nItem >= nItems); nItem = (bDown) ? (nItem + 1) : (nItem - 1))
			{
				if ((pEvent[1] = m_pEventList->GetAt(nItem)) != (CEventObject *)NULL)
				{
					if (!pEvent[1]->GetUser().CompareNoCase(pszUser))
					{
						SetCurEvent(pEvent[1]);
						bSuccess = TRUE;
						break;
					}
				}
			}
			delete pEvent[0];
			m_pEventList->Unlock();
			return bSuccess;
		}
		m_pEventList->Unlock();
	}
	return FALSE;
}

BOOL CEventBoxWnd::SearchEventByRecipient(LPCTSTR pszRecipient, BOOL bDown, BOOL bAll)
{
	INT  nItem;
	INT  nItems;
	INT  nRecipient;
	INT  nRecipients;
	BOOL  bSuccess;
	CEventObject  *pEvent[2];
	CStringArray  szRecipients;
	CDisplayLock  cLock(this);

	if (m_pEventList->Lock())
	{
		if ((pEvent[0] = new CEventObject))
		{
			for (nItem = ((nItem = GetCurEvent(pEvent[0])) >= 0 && !bAll) ? ((!bDown) ? (nItem - 1) : (nItem + 1)) : ((!bDown) ? (m_pEventList->GetScheduleIndex() - 1) : 0), nItems = (bDown) ? m_pEventList->GetScheduleIndex() : 0, bSuccess = FALSE; (bDown && nItem < nItems) || (!bDown && nItem >= nItems); nItem = (bDown) ? (nItem + 1) : (nItem - 1))
			{
				if ((pEvent[1] = m_pEventList->GetAt(nItem)) && pEvent[1]->GetNotificationRecipients(szRecipients) >= 0)
				{
					for (nRecipient = 0, nRecipients = (INT)szRecipients.GetSize(); nRecipient < nRecipients; nRecipient++)
					{
						if (!szRecipients.GetAt(nRecipient).CompareNoCase(pszRecipient)) break;
						continue;
					}
					if (nRecipient < nRecipients)
					{
						SetCurEvent(pEvent[1]);
						bSuccess = TRUE;
						break;
					}
				}
			}
			delete pEvent[0];
			m_pEventList->Unlock();
			return bSuccess;
		}
		m_pEventList->Unlock();
	}
	return FALSE;
}

BOOL CEventBoxWnd::SetPrintJobs(CONST CEventBoxPrintJobs &pPrintJobs)
{
	return m_cPrintThread.SetPrintJobs(pPrintJobs);
}

BOOL CEventBoxWnd::GetPrintJobs(CEventBoxPrintJobs &pPrintJobs) CONST
{
	return m_cPrintThread.GetPrintJobs(pPrintJobs);
}

BOOL CEventBoxWnd::Print(CONST CEventBoxPrintJobInfo *pJobInfo, PRINTDLG *pPrintInfo)
{
	CDC  cDC;
	BOOL  bMetric;
	UINT  nColumns;
	RECT  rtMargin[2];
	SIZE  ptPaperSize;
	LOGFONT  lfFont[2];
	DEVMODE  *pDevMode;
	DEVNAMES  *pDevNames;
	CEventList  cEventList;
	CPrintProfiles  cPrintProfiles;
	CPrintProfileInfo  *pPrintProfileInfo;

	if ((pPrintProfileInfo = (GetPrintProfiles(cPrintProfiles)) ? cPrintProfiles.GetAt(cPrintProfiles.Find(pJobInfo->GetProfile())) : (CPrintProfileInfo *)NULL) && pPrintProfileInfo->GetPaperInfo(ptPaperSize, rtMargin[0], rtMargin[1], bMetric))
	{
		if (GetPrintProperties(pJobInfo, nColumns, cEventList, &lfFont[0], &lfFont[1]))
		{
			if (pPrintInfo == (PRINTDLG *)NULL)
			{
				if (CreatePrinterDC(pPrintProfileInfo, cDC))
				{
					if (PrintJob(cDC, pJobInfo, pPrintProfileInfo->GetPrinterName(), 0, 0, rtMargin[0], bMetric, nColumns, cEventList, &lfFont[0], &lfFont[1]))
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
						if (PrintJob(cDC, pJobInfo, (LPCTSTR)pDevMode->dmDeviceName, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nFromPage : 0, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nToPage : 0, rtMargin[0], bMetric, nColumns, cEventList, &lfFont[0], &lfFont[1]))
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

CEventBoxWnd *CEventBoxWnd::Find(UINT nMode, LPCTSTR pszComputerName, LPCTSTR pszSpacecraftName, LPCTSTR pszUserName, BOOL bGlobal) CONST
{
	INT  nDisplay;
	INT  nDisplays;
	BOOL  bLocal;
	CString  szUserName;
	CString  szComputerName;
	CString  szSpacecraftName;
	CEventBoxWnd  *pEventBoxWnd;
	CDisplayWnd  *pDisplayWnd;
	CPtrArray  pDisplays;

	for (nDisplay = 0, nDisplays = GetDisplayArea()->EnumDisplays(pDisplays), pEventBoxWnd = (CEventBoxWnd *)NULL; nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_EVENTBOX  &&  pDisplayWnd->GetScope() == DISPLAY_SCOPE_LOCAL  &&  pDisplayWnd->GetMode() == nMode)
		{
			if ((pEventBoxWnd = (CEventBoxWnd *)pDisplayWnd)->GetAccountName(szComputerName, szSpacecraftName, szUserName, bLocal) && szComputerName == pszComputerName  &&  szSpacecraftName == pszSpacecraftName  &&  szUserName == pszUserName  &&  bGlobal == !bLocal) break;
			continue;
		}
	}
	return((nDisplay < nDisplays) ? pEventBoxWnd : (CEventBoxWnd *)NULL);
}

VOID CEventBoxWnd::DrawAlertIcon(BOOL bAlert, BOOL bParent)
{
	CWnd  *pWnd;

	if ((pWnd = (bParent) ? (CWnd *)GetMainWnd() : (CWnd *) this))
	{
		pWnd->SetIcon((!bAlert) ? (HICON)(DWORD_PTR)GetClassLongPtr(pWnd->GetSafeHwnd(), GCLP_HICONSM) : ((bParent) ? m_hAlertIcon[0] : m_hAlertIcon[1]), FALSE);
		return;
	}
}

CEventList *CEventBoxWnd::GetEventList() CONST
{
	return m_pEventList;
}

CEventLog *CEventBoxWnd::GetEventLog() CONST
{
	return m_pEventLog;
}

BOOL CEventBoxWnd::CreateToolBar()
{
	if (m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE) && m_wndToolBar.LoadToolBar(IDB_EVENTBOXFRAMELARGEIMAGES, 0, IDB_EVENTBOXFRAMESMALLIMAGES, TRUE))
	{
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_EVENTBOXSETTINGS), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_EVENTBOXSCHEDULE), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_EVENTBOXWATCH), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_EVENTBOXDETAILS), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_EVENTBOXACKNOWLEDGE), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_EVENTBOXCLEARALL), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_EVENTBOXRETRIEVALS), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_EVENTBOXRETRIEVESTEPFORWARD), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_EVENTBOXPRINT), TBBS_DISABLED);
		DockPane(&m_wndToolBar);
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxWnd::CreateStatusBar()
{
	if (m_wndStatusBar.Create(this, CBRS_BOTTOM | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE) && m_wndStatusBar.SetIndicators(nEventBoxStatusBarIndicators, 1))
	{
		m_wndStatusBar.EnableToolTips();
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxWnd::CreateView()
{
	if (m_wndView.Create(this, TVS_HEADER | TVS_TOP | TVS_BUTTONS | TVS_HSCROLL | TVS_VSCROLL | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE))
	{
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxWnd::Customize(BOOL bDefault)
{
	UINT  nColumns;
	UINT  nFilterMode;
	LOGFONT  sFontInfo[2];
	CUIntArray  nWidths;
	CProfile  cProfile;

	if ((!bDefault  &&  GetTitle(nColumns, nWidths) && GetTitleFont(&sFontInfo[0]) && GetItemsFont(&sFontInfo[1]) && SetTitle(nColumns, nWidths) && SetTitleFont(&sFontInfo[0]) && SetItemsFont(&sFontInfo[1])) || (cProfile.GetEventBoxDefaultLayoutInfo(nColumns) && cProfile.GetEventBoxDefaultFontsInfo(&sFontInfo[0], &sFontInfo[1]) && SetTitle(nColumns) && SetTitleFont(&sFontInfo[0]) && SetItemsFont(&sFontInfo[1])) || SetTitle(EVENTBOX_TITLEITEMS_DEFAULT))
	{
		for (nFilterMode = EVENTBOX_FILTER_DEFAULTMODE & ~EVENTBOX_FILTER_USESOUND; GetScope() == DISPLAY_SCOPE_LOCAL && bDefault; )
		{
			SetFilterMode(nFilterMode);
			break;
		}
		return ActivateAccount(bDefault);
	}
	return FALSE;
}

BOOL CEventBoxWnd::UpdateAllPanes()
{
	INT  nPane;
	INT  nPanes;

	for (nPane = 0, nPanes = sizeof(nEventBoxStatusBarIndicators) / sizeof(UINT); nPane < nPanes; nPane++)
	{
		if (m_wndStatusBar.CommandToIndex(nEventBoxStatusBarIndicators[nPane]) != nPane) break;
		continue;
	}
	if (nPane < nPanes)
	{
		if (m_wndStatusBar.SetIndicators(nEventBoxStatusBarIndicators, sizeof(nEventBoxStatusBarIndicators) / sizeof(UINT)))
		{
			UpdateBars();
			return TRUE;
		}
		return FALSE;
	}
	UpdateBars();
	return TRUE;
}

VOID CEventBoxWnd::UpdateItemPane()
{
	INT  nCount;
	CString  szCount;

	if ((nCount = GetEventCount()) >= 0)
	{
		szCount.Format((!IsRetrievingEvents() || IsRetrievingEvents(TRUE)) ? ((nCount != 1) ? STRING(IDS_EVENTBOX_STATUSBAR_EVENTS) : STRING(IDS_EVENTBOX_STATUSBAR_EVENT)) : STRING(IDS_EVENTBOX_STATUSBAR_RETRIEVEMODE), nCount);
		m_wndStatusBar.SetPaneText(ID_EVENTBOX_STATUSBAR_ITEMPANE, szCount);
	}
	m_wndToolBar.EnableButton(IDM_EVENTBOXDETAILS, (IsInitialized() && (GetScope() == DISPLAY_SCOPE_LOCAL || CheckAccountPrivilege(PRIVILEGE_EVENTBOX_LOOK)) && nCount > 0) ? TRUE : FALSE);
	m_wndToolBar.EnableButton(IDM_EVENTBOXACKNOWLEDGE, (IsInitialized() && (GetScope() == DISPLAY_SCOPE_LOCAL || CheckAccountPrivilege(PRIVILEGE_EVENTBOX_ACKNOWLEDGE)) && GetMode() == DISPLAY_MODE_REALTIME  &&  IsAlerted()) ? TRUE : FALSE);
	m_wndToolBar.EnableButton(IDM_EVENTBOXCLEARALL, (IsInitialized() && (GetScope() == DISPLAY_SCOPE_LOCAL || CheckAccountPrivilege(PRIVILEGE_EVENTBOX_RESET)) && nCount > 0) ? TRUE : FALSE);
	m_wndToolBar.EnableButton(IDM_EVENTBOXPRINT, (IsInitialized() && IsDefaultPrinterAvailable() && CanPrint()) ? TRUE : FALSE);
}

VOID CEventBoxWnd::UpdateModePane()
{
	UINT  nMode;
	CString  szMode;

	szMode = (GetMode() == DISPLAY_MODE_REALTIME) ? STRING(IDS_DISPLAY_MODE_REALTIME) : STRING(IDS_DISPLAY_MODE_HISTORY);
	szMode += (GetMode() == DISPLAY_MODE_HISTORY  &&  GetRetrieveMode(nMode) && ((nMode & EVENTBOX_RETRIEVE_PSEUDOREALTIME) || (nMode & EVENTBOX_RETRIEVE_MANUAL))) ? ((nMode & EVENTBOX_RETRIEVE_PSEUDOREALTIME) ? STRING(IDS_EVENTBOX_STATUSBAR_PSEUDOREALTIMEMODE) : STRING(IDS_EVENTBOX_STATUSBAR_MANUALMODE)) : EMPTYSTRING;
	m_wndStatusBar.SetPaneText(ID_EVENTBOX_STATUSBAR_MODEPANE, szMode);
}

VOID CEventBoxWnd::UpdateSystemPane()
{
	m_wndStatusBar.SetPaneText(ID_EVENTBOX_STATUSBAR_SYSTEMPANE, (LPCTSTR)m_pEventLog->GetComputerName());
}

VOID CEventBoxWnd::UpdateSpacecraftPane()
{
	m_wndStatusBar.SetPaneText(ID_EVENTBOX_STATUSBAR_SPACECRAFTPANE, (LPCTSTR)m_pEventLog->GetSpacecraftName());
}

VOID CEventBoxWnd::UpdateUserPane()
{
	m_wndStatusBar.SetPaneText(ID_EVENTBOX_STATUSBAR_USERPANE, (LPCTSTR)m_pEventLog->GetUserName());
}

BOOL CEventBoxWnd::UpdateAlertStatus()
{
	return m_cAlertStatus.SetEvent();
}

BOOL CEventBoxWnd::UpdatePrintStatus()
{
	return m_cPrintThread.Schedule();
}

BOOL CEventBoxWnd::StartWatchEvents()
{
	CEvent  bInit;

	if (GetScope() == DISPLAY_SCOPE_LOCAL)
	{
		if (GetMode() == DISPLAY_MODE_REALTIME  &&  !IsWatchingEvents())
		{
			if (m_cWatchThread.Start(this, bInit, EVENTLOG_CATEGORY_ALL) && UpdateAllPanes())
			{
				WaitForSingleObject(bInit, INFINITE);
				return TRUE;
			}
			ReportEvent(SYSTEM_WARNING_EVENTLOG_WATCH_FAILURE);
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CEventBoxWnd::IsWatchingEvents() CONST
{
	return((m_cWatchThread.IsThreadActive()) ? TRUE : FALSE);
}

BOOL CEventBoxWnd::StopWatchEvents()
{
	return((IsWatchingEvents() && m_cWatchThread.Stop()) ? TRUE : FALSE);
}

BOOL CEventBoxWnd::StartScheduleEvents()
{
	return IsSchedulingEvents() || m_cScheduleThread.Start(this, m_cAlertStatus);
}

BOOL CEventBoxWnd::IsSchedulingEvents() CONST
{
	return((m_cScheduleThread.IsThreadActive()) ? TRUE : FALSE);
}

BOOL CEventBoxWnd::StopScheduleEvents()
{
	return((IsSchedulingEvents() && m_cScheduleThread.Stop()) ? TRUE : FALSE);
}

BOOL CEventBoxWnd::StartSchedulePrintJobs()
{
	return IsSchedulingPrintJobs() || m_cPrintThread.Start(this);
}

BOOL CEventBoxWnd::IsSchedulingPrintJobs() CONST
{
	return((m_cPrintThread.IsThreadActive()) ? TRUE : FALSE);
}

BOOL CEventBoxWnd::StopSchedulePrintJobs()
{
	return((IsSchedulingPrintJobs() && m_cPrintThread.Stop()) ? TRUE : FALSE);
}

BOOL CEventBoxWnd::SetScheduleInfo(CONST CByteArray &nScheduleInfo)
{
	INT  nItem;
	INT  nItems;
	CEventList  cEventList;
	CEventObject  *pEvent;

	if (GetScope() == DISPLAY_SCOPE_GLOBAL)
	{
		for (nItem = 0, nItems = (cEventList.Unmap(nScheduleInfo)) ? (INT)cEventList.GetSize() : -1, m_pEventList->Lock(); nItem < nItems; nItem++)
		{
			if ((pEvent = cEventList.GetAt(nItem)) != (CEventObject *)NULL)
			{
				for (cEventList.Remove(nItem); !ScheduleEvent(pEvent); )
				{
					delete pEvent;
					break;
				}
				nItems--;
				nItem--;
			}
		}
		m_pEventList->Unlock();
		return((nItem == nItems) ? TRUE : FALSE);
	}
	return TRUE;
}

BOOL CEventBoxWnd::GetScheduleInfo(CByteArray &nScheduleInfo) CONST
{
	if (GetScope() == DISPLAY_SCOPE_GLOBAL)
	{
		for (nScheduleInfo.RemoveAll(); m_pEventList->Lock(); )
		{
			if (m_pEventList->Map(nScheduleInfo, TRUE))
			{
				m_pEventList->Unlock();
				return TRUE;
			}
			m_pEventList->Unlock();
			break;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CEventBoxWnd::SetPrintJobs(CONST CByteArray &nPrintInfo)
{
	CEventBoxPrintJobs  pPrintJobs;

	return((pPrintJobs.Unmap(nPrintInfo)) ? SetPrintJobs(pPrintJobs) : FALSE);
}

BOOL CEventBoxWnd::GetPrintJobs(CByteArray &nPrintInfo) CONST
{
	CEventBoxPrintJobs  pPrintJobs;

	return((GetPrintJobs(pPrintJobs)) ? pPrintJobs.Map(nPrintInfo) : FALSE);
}

BOOL CEventBoxWnd::GetPrintProperties(CONST CEventBoxPrintJobInfo *pJobInfo, UINT &nColumns, CEventList &cEventList, LOGFONT *pTitleFont, LOGFONT *pItemsFont) CONST
{
	INT  nItem;
	INT  nItems;
	UINT  nPrintMode;
	UINT  nPrintLimit;
	CTimeKey  tAuditTime;
	CTimeSpan  tPrintStartTime;
	CTimeSpan  tPrintStopTime;
	CEventObject  *pEvent[2];
	CDisplayLock  cLock(this);

	if (m_pEventList->Lock())
	{
		for (GetTitle(nColumns), GetTitleFont(pTitleFont), GetItemsFont(pItemsFont); (nPrintMode = pJobInfo->GetPrintMode()) & EVENTBOX_PRINT_ALL; )
		{
			for (nItem = 0, nItems = (INT)m_pEventList->GetSize(), cEventList.EnableSound(FALSE); nItem < nItems; nItem++)
			{
				if ((pEvent[0] = m_pEventList->GetAt(nItem)))
				{
					if ((pEvent[1] = new CEventObject))
					{
						pEvent[1]->Copy(pEvent[0]);
						if (cEventList.Add(pEvent[1]) >= 0) continue;
						delete pEvent[1];
					}
				}
				break;
			}
			m_pEventList->Unlock();
			return((nItem == nItems) ? TRUE : FALSE);
		}
		if (((nPrintMode & EVENTBOX_PRINT_FIRSTSIDE) || (nPrintMode & EVENTBOX_PRINT_LASTSIDE)) && pJobInfo->GetPrintBySide(nPrintLimit))
		{
			for (nItem = ((nPrintMode & EVENTBOX_PRINT_FIRSTSIDE) != EVENTBOX_PRINT_FIRSTSIDE) ? (INT)(m_pEventList->GetSize() - 1) : 0, nItems = (!nItem) ? (INT)cEventList.GetSize() : 0, cEventList.EnableSound(FALSE); (((nPrintMode & EVENTBOX_PRINT_FIRSTSIDE) && nItem < nItems) || ((nPrintMode & EVENTBOX_PRINT_FIRSTSIDE) != EVENTBOX_PRINT_FIRSTSIDE && nItem >= nItems)) && cEventList.GetSize() < (INT)nPrintLimit; nItem = (nPrintMode & EVENTBOX_PRINT_FIRSTSIDE) ? (nItem + 1) : (nItem - 1))
			{
				if ((pEvent[0] = m_pEventList->GetAt(nItem)))
				{
					if ((pEvent[1] = new CEventObject))
					{
						pEvent[1]->Copy(pEvent[0]);
						if (cEventList.Add(pEvent[1]) >= 0) continue;
						delete pEvent[1];
					}
				}
				break;
			}
			m_pEventList->Unlock();
			return(((((nPrintMode & EVENTBOX_PRINT_FIRSTSIDE) && nItem == nItems) || ((nPrintMode & EVENTBOX_PRINT_FIRSTSIDE) != EVENTBOX_PRINT_FIRSTSIDE  &&  nItem < 0)) || cEventList.GetSize() == nPrintLimit) ? TRUE : FALSE);
		}
		if ((nPrintMode & EVENTBOX_PRINT_DAILY) && pJobInfo->GetPrintByTime(tPrintStartTime, tPrintStopTime))
		{
			for (nItem = 0, nItems = (INT)m_pEventList->GetSize(), cEventList.EnableSound(FALSE); nItem < nItems; nItem++)
			{
				if ((pEvent[0] = (CEventObject *)m_pEventList->GetAt(nItem)) != (CEventObject *)NULL)
				{
					if ((tAuditTime = pEvent[0]->GetAuditTime()).GetTime() % SECONDSPERDAY >= tPrintStartTime.GetTotalSeconds() && tAuditTime.GetTime() % SECONDSPERDAY <= tPrintStopTime.GetTotalSeconds())
					{
						if ((pEvent[1] = new CEventObject))
						{
							pEvent[1]->Copy(pEvent[0]);
							if (cEventList.Add(pEvent[1]) >= 0) continue;
							delete pEvent[1];
						}
						break;
					}
					continue;
				}
				break;
			}
			m_pEventList->Unlock();
			return((nItem == nItems) ? TRUE : FALSE);
		}
		m_pEventList->Unlock();
	}
	return FALSE;
}

BOOL CEventBoxWnd::StartPrintJob(CDC &cDC)
{
	DOCINFO  sJobInfo;
	CString  szJobTitle[2];

	for (sJobInfo.fwType = 0, sJobInfo.cbSize = sizeof(DOCINFO), sJobInfo.lpszDocName = (LPTSTR)EMPTYSTRING, sJobInfo.lpszOutput = (LPCTSTR)NULL, sJobInfo.lpszDatatype = (LPCTSTR)NULL, GetWindowText(szJobTitle[0]), szJobTitle[1].Format(STRING(IDS_PRINTJOB_DEFAULTTITLE), (LPCTSTR)GetAppTitle(), (LPCTSTR)GetAccountSpacecraftName(), (LPCTSTR)szJobTitle[0], STRING(IDS_DISPLAY_TITLE_EVENTBOX)); szJobTitle[1].GetLength() >= 0; )
	{
		sJobInfo.lpszDocName = (LPTSTR)(LPCTSTR)szJobTitle[1];
		break;
	}
	return((cDC.StartDoc(&sJobInfo) >= 0) ? TRUE : FALSE);
}

BOOL CEventBoxWnd::PrintJob(CDC &cDC, CONST CEventBoxPrintJobInfo *pJobInfo, LPCTSTR pszPrinterName, INT nFromPage, INT nToPage, CONST RECT &rtMargin, BOOL bMetric, UINT nColumns, CONST CEventList &cEventList, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont)
{
	INT  nPage;
	INT  nPages;
	INT  nItem;
	INT  nItems;
	INT  nColumn;
	INT  nHeight;
	INT  nIndent;
	INT  nSpacing;
	INT  nRecipient;
	INT  nRecipients;
	UINT  nCategory;
	BOOL  bOutput;
	CRgn  rgnArea;
	CRect  rArea;
	CRect  rCalc;
	CRect  rClip;
	CRect  rItem;
	CFont  *pOldFont;
	CFont  cFont[EVENTBOX_PRINTFONTS];
	CString  szItemText;
	COLORREF  nOldColor;
	CTimeKey  tPrint;
	CPtrArray  pFonts;
	CUIntArray  nTabs;
	TEXTMETRIC  tmFont;
	CEventObject  *pEvent;
	CStringArray  szRecipients;

	for (nPage = nPages = 0, nSpacing = 0, ZeroMemory(&tmFont, sizeof(TEXTMETRIC)); (!nPages || nPage <= nPages) && (nPages > 0 || (nPages = (CalcPrintDocRect(cDC, rtMargin, bMetric) && cDC.GetClipBox(rArea) != ERROR && rgnArea.CreateRectRgnIndirect(rArea) && CalcPrintDocTitleFont(cDC, rArea, cFont[EVENTBOX_PRINTFONT_TITLE]) && CalcPrintDocDetailsFont(cDC, rArea, cFont[EVENTBOX_PRINTFONT_DETAILS]) && CalcPrintDocCommentsFont(cDC, rArea, cFont[EVENTBOX_PRINTFONT_COMMENTS]) && CalcPrintDocListItemsFonts(cDC, rArea, nColumns, cEventList, pTitleFont, pItemsFont, cFont[EVENTBOX_PRINTFONT_LISTITEMSTITLE], cFont[EVENTBOX_PRINTFONT_LISTITEMS]) && CalcPrintDocNoticeFonts(cDC, rArea, cFont[EVENTBOX_PRINTFONT_NOTICE], cFont[EVENTBOX_PRINTFONT_LOGO]) && CalcPrintDocFooterFont(cDC, rArea, cFont[EVENTBOX_PRINTFONT_FOOTER]) && CalcPrintDocItemsTitleWidth(cDC, rArea, nColumns, cEventList, &cFont[EVENTBOX_PRINTFONT_LISTITEMSTITLE], &cFont[EVENTBOX_PRINTFONT_LISTITEMS], FALSE, nTabs, nIndent) > 0) ? nPages : -1) == 0); )
	{
		for (nItem = 0, nItems = (INT)cEventList.GetSize(), pFonts.SetAtGrow(EVENTBOX_PRINTFONT_TITLE, &cFont[EVENTBOX_PRINTFONT_TITLE]), pFonts.SetAtGrow(EVENTBOX_PRINTFONT_DETAILS, &cFont[EVENTBOX_PRINTFONT_DETAILS]), pFonts.SetAtGrow(EVENTBOX_PRINTFONT_COMMENTS, &cFont[EVENTBOX_PRINTFONT_COMMENTS]), pFonts.SetAtGrow(EVENTBOX_PRINTFONT_LISTITEMSTITLE, &cFont[EVENTBOX_PRINTFONT_LISTITEMSTITLE]), pFonts.SetAtGrow(EVENTBOX_PRINTFONT_LISTITEMS, &cFont[EVENTBOX_PRINTFONT_LISTITEMS]), pFonts.SetAtGrow(EVENTBOX_PRINTFONT_FOOTER, &cFont[EVENTBOX_PRINTFONT_FOOTER]), pFonts.SetAtGrow(EVENTBOX_PRINTFONT_NOTICE, &cFont[EVENTBOX_PRINTFONT_NOTICE]), pFonts.SetAtGrow(EVENTBOX_PRINTFONT_LOGO, &cFont[EVENTBOX_PRINTFONT_LOGO]), nSpacing = 0, rCalc.SetRectEmpty(), rClip.SetRectEmpty(), bOutput = TRUE; nItem < nItems; nItem++, bOutput = TRUE)
		{
			if ((pEvent = cEventList.GetAt(nItem)) != (CEventObject *)NULL)
			{
				for (nColumn = 0, nHeight = 0; TRUE; nColumn = 0, nHeight = 0)
				{
					if (rClip.Height() > 0)
					{
						if ((pOldFont = cDC.SelectObject(&cFont[EVENTBOX_PRINTFONT_LISTITEMS])))
						{
							if ((nSpacing = (cDC.GetTextMetrics(&tmFont)) ? max(tmFont.tmHeight / 10, 1) : -1) >= 0)
							{
								for (nOldColor = cDC.SetTextColor((cDC.GetDeviceCaps(NUMCOLORS) > 2) ? pEvent->GetAuditColor() : cDC.GetTextColor()), rCalc.SetRect((rClip.Height() > 0) ? rCalc.left : 0, (rClip.Height() > 0) ? (rCalc.top + nSpacing) : 0, (rClip.Height() > 0) ? rCalc.right : 0, (rClip.Height() > 0) ? (rCalc.top + nSpacing + tmFont.tmHeight*((rClip.bottom - (rCalc.top + nSpacing)) / tmFont.tmHeight)) : 0); nColumns & EVENTBOX_TITLEITEM_TIME; )
								{
									rItem.SetRect((nColumn > 0) ? (rCalc.left + nTabs.GetAt(nColumn - 1)) : rCalc.left, rCalc.top, rCalc.left + nTabs.GetAt(nColumn), rCalc.top + rClip.Height());
									cDC.DrawText((szItemText = pEvent->GetAuditTime().FormatGmt() + SPACE), rItem, DT_CALCRECT | DT_LEFT | DT_NOPREFIX | DT_SINGLELINE | DT_WORDBREAK);
									cDC.DrawText(szItemText, (nPages > 0 && (nFromPage <= 0 || nToPage <= 0 || nFromPage > nToPage || (nPage >= nFromPage  &&  nPage <= nToPage))) ? CRect(rItem.left, rItem.top, rItem.right, rCalc.bottom) : CRect(0, 0, 0, 0), DT_LEFT | DT_NOPREFIX | DT_SINGLELINE | DT_WORDBREAK);
									nHeight = (!szItemText.IsEmpty()) ? max(rItem.Height(), nHeight) : nHeight;
									nColumn++;
									break;
								}
								if (nColumns & EVENTBOX_TITLEITEM_CATEGORY)
								{
									rItem.SetRect((nColumn > 0) ? (rCalc.left + nTabs.GetAt(nColumn - 1)) : rCalc.left, rCalc.top, rCalc.left + nTabs.GetAt(nColumn), rCalc.top + rClip.Height());
									cDC.DrawText((szItemText = (((nCategory = pEvent->GetCategory()) & EVENT_CATEGORY_SYSTEM) ? STRING(IDS_EVENTCATEGORY_SYSTEM) : ((nCategory & EVENT_CATEGORY_SPACECRAFT) ? STRING(IDS_EVENTCATEGORY_SPACECRAFT) : ((nCategory & EVENT_CATEGORY_USER) ? STRING(IDS_EVENTCATEGORY_USER) : EMPTYSTRING))) + CString(SPACE)), rItem, DT_CALCRECT | DT_LEFT | DT_NOPREFIX | DT_SINGLELINE | DT_WORDBREAK);
									cDC.DrawText(szItemText, (nPages > 0 && (nFromPage <= 0 || nToPage <= 0 || nFromPage > nToPage || (nPage >= nFromPage  &&  nPage <= nToPage))) ? CRect(rItem.left, rItem.top, rItem.right, rCalc.bottom) : CRect(0, 0, 0, 0), DT_LEFT | DT_NOPREFIX | DT_SINGLELINE | DT_WORDBREAK);
									nHeight = (!szItemText.IsEmpty()) ? max(rItem.Height(), nHeight) : nHeight;
									nColumn++;
								}
								if (nColumns & EVENTBOX_TITLEITEM_TYPE)
								{
									rItem.SetRect((nColumn > 0) ? (rCalc.left + nTabs.GetAt(nColumn - 1)) : rCalc.left, rCalc.top, rCalc.left + nTabs.GetAt(nColumn), rCalc.top + rClip.Height());
									cDC.DrawText((szItemText = pEvent->GetType() + SPACE), rItem, DT_CALCRECT | DT_LEFT | DT_NOPREFIX | DT_SINGLELINE | DT_WORDBREAK);
									cDC.DrawText(szItemText, (nPages > 0 && (nFromPage <= 0 || nToPage <= 0 || nFromPage > nToPage || (nPage >= nFromPage  &&  nPage <= nToPage))) ? CRect(rItem.left, rItem.top, rItem.right, rCalc.bottom) : CRect(0, 0, 0, 0), DT_LEFT | DT_NOPREFIX | DT_SINGLELINE | DT_WORDBREAK);
									nHeight = (!szItemText.IsEmpty()) ? max(rItem.Height(), nHeight) : nHeight;
									nColumn++;
								}
								if (nColumns & EVENTBOX_TITLEITEM_MESSAGE)
								{
									rItem.SetRect((nColumn > 0) ? (rCalc.left + nTabs.GetAt(nColumn - 1)) : rCalc.left, rCalc.top, rCalc.left + nTabs.GetAt(nColumn) - 2 * nIndent, rCalc.top + rClip.Height());
									cDC.DrawText((szItemText = pEvent->GetMessage() + SPACE), rItem, DT_CALCRECT | DT_LEFT | DT_NOPREFIX | DT_EXPANDTABS | DT_WORDBREAK);
									cDC.DrawText(szItemText, (nPages > 0 && (nFromPage <= 0 || nToPage <= 0 || nFromPage > nToPage || (nPage >= nFromPage  &&  nPage <= nToPage))) ? CRect(rItem.left, rItem.top, rItem.right, rCalc.bottom) : CRect(0, 0, 0, 0), DT_LEFT | DT_NOPREFIX | DT_EXPANDTABS | DT_WORDBREAK);
									nHeight = (!szItemText.IsEmpty()) ? max(rItem.Height(), nHeight) : nHeight;
									nColumn++;
								}
								if (nColumns & EVENTBOX_TITLEITEM_COMMENTS)
								{
									rItem.SetRect((nColumn > 0) ? (rCalc.left + nTabs.GetAt(nColumn - 1)) : rCalc.left, rCalc.top, rCalc.left + nTabs.GetAt(nColumn) - 2 * nIndent, rCalc.top + rClip.Height());
									cDC.DrawText((szItemText = pEvent->GetComments() + SPACE), rItem, DT_CALCRECT | DT_LEFT | DT_NOPREFIX | DT_EXPANDTABS | DT_WORDBREAK);
									cDC.DrawText(szItemText, (nPages > 0 && (nFromPage <= 0 || nToPage <= 0 || nFromPage > nToPage || (nPage >= nFromPage  &&  nPage <= nToPage))) ? CRect(rItem.left, rItem.top, rItem.right, rCalc.bottom) : CRect(0, 0, 0, 0), DT_LEFT | DT_NOPREFIX | DT_EXPANDTABS | DT_WORDBREAK);
									nHeight = (!szItemText.IsEmpty()) ? max(rItem.Height(), nHeight) : nHeight;
									nColumn++;
								}
								if (nColumns & EVENTBOX_TITLEITEM_RECIPIENTS)
								{
									rItem.SetRect((nColumn > 0) ? (rCalc.left + nTabs.GetAt(nColumn - 1)) : rCalc.left, rCalc.top, rCalc.left + nTabs.GetAt(nColumn), rCalc.top + rClip.Height());
									for (nRecipient = 0, nRecipients = pEvent->GetNotificationRecipients(szRecipients), szItemText.Empty(); nRecipient < nRecipients; nRecipient++)
									{
										szItemText += szRecipients.GetAt(nRecipient) + SPACE;
										szItemText += (nRecipient == nRecipients - 1) ? (LPCTSTR)CString(EOL) : EMPTYSTRING;
									}
									cDC.DrawText(szItemText, rItem, DT_CALCRECT | DT_LEFT | DT_NOPREFIX | DT_WORDBREAK);
									cDC.DrawText(szItemText, (nPages > 0 && (nFromPage <= 0 || nToPage <= 0 || nFromPage > nToPage || (nPage >= nFromPage  &&  nPage <= nToPage))) ? CRect(rItem.left, rItem.top, rItem.right, rCalc.bottom) : CRect(0, 0, 0, 0), DT_LEFT | DT_NOPREFIX | DT_WORDBREAK);
									nHeight = (!szItemText.IsEmpty()) ? max(rItem.Height(), nHeight) : nHeight;
									nColumn++;
								}
								if (nColumns & EVENTBOX_TITLEITEM_USER)
								{
									rItem.SetRect((nColumn > 0) ? (rCalc.left + nTabs.GetAt(nColumn - 1)) : rCalc.left, rCalc.top, rCalc.left + nTabs.GetAt(nColumn), rCalc.top + rClip.Height());
									cDC.DrawText((szItemText = pEvent->GetUser() + SPACE), rItem, DT_CALCRECT | DT_LEFT | DT_NOPREFIX | DT_SINGLELINE | DT_WORDBREAK);
									cDC.DrawText(szItemText, (nPages > 0 && (nFromPage <= 0 || nToPage <= 0 || nFromPage > nToPage || (nPage >= nFromPage  &&  nPage <= nToPage))) ? CRect(rItem.left, rItem.top, rItem.right, rCalc.bottom) : CRect(0, 0, 0, 0), DT_LEFT | DT_NOPREFIX | DT_SINGLELINE | DT_WORDBREAK);
									nHeight = (!szItemText.IsEmpty()) ? max(rItem.Height(), nHeight) : nHeight;
									nColumn++;
								}
								cDC.SetTextColor(nOldColor);
								cDC.SelectObject(pOldFont);
							}
							else
							{
								cDC.SelectObject(pOldFont);
								nColumn = -1;
								break;
							}
						}
						else
						{
							nColumn = -1;
							break;
						}
					}
					if (rCalc.top + nHeight > rCalc.bottom || !rClip.Height())
					{
						if (nPages > 0 && (nPage == nPages || (nFromPage > 0 && nToPage > 0 && nFromPage <= nToPage  &&  nPage == nToPage)))
						{
							nPages = nPage;
							break;
						}
						if (bOutput && (!nPages || ((!nPage || (nFromPage > 0 && nToPage > 0 && nFromPage <= nToPage && (nPage < nFromPage || nPage > nToPage)) || cDC.EndPage() >= 0) && ((nFromPage > 0 && nToPage > 0 && nFromPage <= nToPage && (nPage < nFromPage - 1 || nPage >= nToPage)) || (((((nFromPage <= 0 || nToPage <= 0 || nFromPage > nToPage) && nPage > 0) || (nFromPage > 0 && nToPage > 0 && nFromPage <= nToPage  &&  nPage != nFromPage - 1)) || StartPrintJob(cDC)) && cDC.StartPage() >= 0)))))
						{
							if (cDC.SelectClipRgn(&rgnArea) != ERROR  &&  DrawPrintDocPage(cDC, pJobInfo, tPrint, pszPrinterName, rtMargin, bMetric, nColumns, pFonts, nTabs, nPages, (nPages > 0 && (nFromPage <= 0 || nToPage <= 0 || nFromPage > nToPage || (nPage >= nFromPage - 1 && nPage < nToPage))) ? (nPage + 1) : 0, rClip) && cDC.IntersectClipRect(rClip) != ERROR)
							{
								rCalc.SetRect(rClip.left, rClip.top - rCalc.Height() - nSpacing, rClip.right, rClip.bottom);
								bOutput = FALSE;
								nPage++;
								continue;
							}
						}
						nColumn = -1;
						break;
					}
					rCalc.DeflateRect(0, nHeight, 0, 0);
					break;
				}
				if (nColumn >= 0) continue;
			}
			break;
		}
		if (nPages >= 0)
		{
			if (nItem == nItems)
			{
				if (!cEventList.GetSize())
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
							if (DrawPrintDocPage(cDC, pJobInfo, tPrint, pszPrinterName, rtMargin, bMetric, nColumns, pFonts, nTabs, 1, 1, rClip))
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

BOOL CEventBoxWnd::EndPrintJob(CDC &cDC)
{
	return((cDC.EndDoc() >= 0) ? TRUE : FALSE);
}

BOOL CEventBoxWnd::DrawPrintDocPage(CDC &cDC, CONST CEventBoxPrintJobInfo *pJobInfo, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, CONST RECT &rtMargin, BOOL bMetric, UINT nColumns, CONST CPtrArray &pFonts, CONST CUIntArray &nTabs, INT nPages, INT nPage, LPRECT prClip)
{
	return((CalcPrintDocRect(cDC, rtMargin, bMetric) && cDC.GetClipBox(prClip) != ERROR  &&  DrawPrintDocTitle(cDC, prClip, GetPrintDocTitle(), (CFont *)pFonts.GetAt(EVENTBOX_PRINTFONT_TITLE), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocComments(cDC, prClip, GetPrintDocComments(pJobInfo), (CFont *)pFonts.GetAt(EVENTBOX_PRINTFONT_COMMENTS), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocDetails(cDC, prClip, GetPrintDocDetails(pJobInfo), (CFont *)pFonts.GetAt(EVENTBOX_PRINTFONT_DETAILS), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocListItemsTitle(cDC, prClip, nColumns, (CFont *)pFonts.GetAt(EVENTBOX_PRINTFONT_LISTITEMSTITLE), nTabs, (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocNotice(cDC, prClip, GetPrintDocNotice(), (CFont *)pFonts.GetAt(EVENTBOX_PRINTFONT_NOTICE), (CFont *)pFonts.GetAt(EVENTBOX_PRINTFONT_LOGO), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocFooter(cDC, prClip, GetPrintDocFooter(tTime, pszPrinterName, nPages, nPage), (CFont *)pFonts.GetAt(EVENTBOX_PRINTFONT_FOOTER), (nPage <= 0) ? TRUE : FALSE)) ? TRUE : FALSE);
}

BOOL CEventBoxWnd::DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc)
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

BOOL CEventBoxWnd::DrawPrintDocDetails(CDC &cDC, LPRECT prClip, LPCTSTR pszDetails, CFont *pFont, BOOL bCalc)
{
	CRect  rCalc;
	CFont  *pOldFont;

	if ((pOldFont = cDC.SelectObject(pFont)))
	{
		cDC.DrawText(pszDetails, (rCalc = CRect(0, 0, prClip->right - prClip->left, 0)), DT_CALCRECT | DT_CENTER | DT_NOPREFIX | DT_WORDBREAK);
		cDC.DrawText(pszDetails, (!bCalc) ? prClip : CRect(0, 0, 0, 0), DT_CENTER | DT_NOPREFIX | DT_WORDBREAK);
		prClip->top += rCalc.Height();
		cDC.SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxWnd::DrawPrintDocComments(CDC &cDC, LPRECT prClip, LPCTSTR pszComments, CFont *pFont, BOOL bCalc)
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

BOOL CEventBoxWnd::DrawPrintDocListItemsTitle(CDC &cDC, LPRECT prClip, UINT nColumns, CFont *pFont, CONST CUIntArray &nTabs, BOOL bCalc)
{
	CSize  rCalc;
	CFont  *pOldFont;
	CString  szItems;

	if ((pOldFont = cDC.SelectObject(pFont)))
	{
		szItems = GetPrintDocListItemsTitle(nColumns);
		rCalc = (!bCalc) ? cDC.TabbedTextOut(prClip->left, prClip->top + cDC.GetTextExtent(szItems, szItems.GetLength()).cy, szItems, (INT)nTabs.GetSize(), (LPINT)nTabs.GetData(), prClip->left) : CSize(nTabs.GetAt(nTabs.GetSize() - 1), cDC.GetTextExtent(szItems, szItems.GetLength()).cy);
		prClip->top += 2 * rCalc.cy;
		cDC.SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CEventBoxWnd::DrawPrintDocNotice(CDC &cDC, LPRECT prClip, LPCTSTR pszNotice, CFont *pFont, CFont *pLogoFont, BOOL bCalc)
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

BOOL CEventBoxWnd::DrawPrintDocFooter(CDC &cDC, LPRECT prClip, LPCTSTR pszFooter, CFont *pFont, BOOL bCalc)
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

CString CEventBoxWnd::GetPrintDocTitle() CONST
{
	CString  szTitle;

	szTitle.Format(STRING(IDS_EVENTBOX_PRINTDOCUMENT_TITLE), (LPCTSTR)GetAccountSpacecraftName());
	return szTitle;
}

CString CEventBoxWnd::GetPrintDocDetails(CONST CEventBoxPrintJobInfo *pJobInfo) CONST
{
	UINT  nMode;
	UINT  nFlags;
	UINT  nCount;
	UINT  nStopCount;
	CString  szInfo;
	CString  szSide;
	CString  szTime;
	CTimeKey  tTime;
	CTimeKey  tLastTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CTimeSpan  tDailyTime;
	CTimeSpan  tDailyStartTime;
	CTimeSpan  tDailyStopTime;

	if ((nFlags = pJobInfo->GetPrintFlags()) & EVENTBOX_PRINT_ATTIME)
	{
		if (pJobInfo->GetPrintAtTime(tTime))
		{
			szInfo.Format(STRING(IDS_EVENTBOX_PRINTDOCUMENT_PRINTATTIME), (LPCTSTR)tTime.FormatGmt());
			szInfo += EOL;
		}
		if ((pJobInfo->GetPrintAtTime(tTime, tInterval) || pJobInfo->GetPrintAtTime(tTime, tInterval, nStopCount) || pJobInfo->GetPrintAtTime(tTime, tInterval, tStopTime)) && pJobInfo->GetPrintLastTime(tLastTime))
		{
			szInfo.Format(STRING(IDS_EVENTBOX_PRINTDOCUMENT_PRINTATTIME), (LPCTSTR)CTimeKey(tTime.GetTime() + ((tLastTime.GetTime() - tTime.GetTime()) / tInterval.GetTotalSeconds())*tInterval.GetTotalSeconds()).FormatGmt());
			szInfo += EOL;
		}
	}
	if (nFlags & EVENTBOX_PRINT_ATDAILYTIME)
	{
		if (pJobInfo->GetPrintAtDailyTime(tDailyTime) || pJobInfo->GetPrintAtDailyTime(tDailyTime, nStopCount) || pJobInfo->GetPrintAtDailyTime(tDailyTime, tStopTime))
		{
			szInfo.Format(STRING(IDS_EVENTBOX_PRINTDOCUMENT_PRINTATDAILYTIME), (LPCTSTR)CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + tDailyTime.GetTotalSeconds()).FormatGmt(STRING(IDS_TIMEKEY_TIMEFORMAT)));
			szInfo += EOL;
		}
	}
	if (nFlags & EVENTBOX_PRINT_ATCOUNT)
	{
		if (pJobInfo->GetPrintAtCount(nCount))
		{
			szInfo.Format(STRING(IDS_EVENTBOX_PRINTDOCUMENT_PRINTATCOUNT), nCount);
			szInfo += EOL;
		}
	}
	if (!nFlags)
	{
		szInfo = STRING(IDS_EVENTBOX_PRINTDOCUMENT_DEFAULTTIME);
		szInfo += EOL;
	}
	if ((nMode = pJobInfo->GetPrintMode()) & EVENTBOX_PRINT_ALL) szInfo += STRING(IDS_EVENTBOX_PRINTDOCUMENT_PRINTALL);
	if (((nMode & EVENTBOX_PRINT_FIRSTSIDE) || (nMode & EVENTBOX_PRINT_LASTSIDE)) && pJobInfo->GetPrintBySide(nCount))
	{
		szSide.Format((nMode & EVENTBOX_PRINT_FIRSTSIDE) ? STRING(IDS_EVENTBOX_PRINTDOCUMENT_PRINTBYFIRSTSIDE) : STRING(IDS_EVENTBOX_PRINTDOCUMENT_PRINTBYLASTSIDE), nCount);
		szSide = (nCount == 1) ? ((nMode & EVENTBOX_PRINT_FIRSTSIDE) ? STRING(IDS_EVENTBOX_PRINTDOCUMENT_PRINTBYFIRSTITEM) : STRING(IDS_EVENTBOX_PRINTDOCUMENT_PRINTBYLASTITEM)) : (LPCTSTR)szSide;
		szInfo += szSide;
	}
	if ((nMode & EVENTBOX_PRINT_DAILY) && pJobInfo->GetPrintByTime(tDailyStartTime, tDailyStopTime))
	{
		szTime.Format(STRING(IDS_EVENTBOX_PRINTDOCUMENT_PRINTBYTIME), (LPCTSTR)CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + tDailyStartTime.GetTotalSeconds()).FormatGmt(STRING(IDS_TIMEKEY_TIMEFORMAT)), (LPCTSTR)CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + tDailyStopTime.GetTotalSeconds()).FormatGmt(STRING(IDS_TIMEKEY_TIMEFORMAT)));
		szInfo += szTime;
	}
	return szInfo;
}

CString CEventBoxWnd::GetPrintDocComments(CONST CEventBoxPrintJobInfo *pJobInfo) CONST
{
	return pJobInfo->GetComments();
}

CString CEventBoxWnd::GetPrintDocListItemsTitle(UINT nColumns) CONST
{
	CString  szTitle;

	if (nColumns & EVENTBOX_TITLEITEM_TIME)
	{
		szTitle += (szTitle.GetLength()) ? CString(TAB) : EMPTYSTRING;
		szTitle += STRING(IDS_EVENTBOX_TITLEITEM_TIME);
	}
	if (nColumns & EVENTBOX_TITLEITEM_CATEGORY)
	{
		szTitle += (szTitle.GetLength()) ? CString(TAB) : EMPTYSTRING;
		szTitle += STRING(IDS_EVENTBOX_TITLEITEM_CATEGORY);
	}
	if (nColumns & EVENTBOX_TITLEITEM_TYPE)
	{
		szTitle += (szTitle.GetLength()) ? CString(TAB) : EMPTYSTRING;
		szTitle += STRING(IDS_EVENTBOX_TITLEITEM_TYPE);
	}
	if (nColumns & EVENTBOX_TITLEITEM_MESSAGE)
	{
		szTitle += (szTitle.GetLength()) ? CString(TAB) : EMPTYSTRING;
		szTitle += STRING(IDS_EVENTBOX_TITLEITEM_MESSAGE);
	}
	if (nColumns & EVENTBOX_TITLEITEM_COMMENTS)
	{
		szTitle += (szTitle.GetLength()) ? CString(TAB) : EMPTYSTRING;
		szTitle += STRING(IDS_EVENTBOX_TITLEITEM_COMMENTS);
	}
	if (nColumns & EVENTBOX_TITLEITEM_RECIPIENTS)
	{
		szTitle += (szTitle.GetLength()) ? CString(TAB) : EMPTYSTRING;
		szTitle += STRING(IDS_EVENTBOX_TITLEITEM_RECIPIENTS);
	}
	if (nColumns & EVENTBOX_TITLEITEM_USER)
	{
		szTitle += (szTitle.GetLength()) ? CString(TAB) : EMPTYSTRING;
		szTitle += STRING(IDS_EVENTBOX_TITLEITEM_USER);
	}
	return szTitle;
}

CString CEventBoxWnd::GetPrintDocNotice() CONST
{
	CVersionInfo  cVersionInfo;

	return cVersionInfo.QueryComments();
}

CString CEventBoxWnd::GetPrintDocFooter(CONST CTimeKey &tTime, LPCTSTR pszPrinterName, INT nPages, INT nPage) CONST
{
	CString  szFooter;

	szFooter.Format(STRING(IDS_EVENTBOX_PRINTDOCUMENT_FOOTER), (LPCTSTR)tTime.Format(IDS_TIMEKEY_DATEFORMAT), (LPCTSTR)tTime.Format(IDS_TIMEKEY_TIMEFORMAT), pszPrinterName, nPage, nPages);
	return szFooter;
}

BOOL CEventBoxWnd::CalcPrintDocTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 48, (INT)((-5.3*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CEventBoxWnd::CalcPrintDocDetailsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 76, (INT)((-3.3*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CEventBoxWnd::CalcPrintDocCommentsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 76, (INT)((-3.3*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CEventBoxWnd::CalcPrintDocListItemsFonts(CDC &cDC, CONST RECT &rArea, UINT nColumns, CONST CEventList &cEventList, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont, CFont &cTitleFont, CFont &cItemsFont) CONST
{
	INT  nWidth;
	INT  nHeight;
	INT  nIndent;
	CFont  cFont[2];
	CUIntArray  nTabs;

	for (nHeight = max(-(rArea.right - rArea.left) / 64, (INT)((-4.0*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))); nHeight < 0; nHeight++)
	{
		if (cFont[0].CreateFont(nHeight, 0, pTitleFont->lfEscapement, pTitleFont->lfOrientation, FW_BOLD, pTitleFont->lfItalic, pTitleFont->lfUnderline, pTitleFont->lfStrikeOut, pTitleFont->lfCharSet, pTitleFont->lfOutPrecision, pTitleFont->lfClipPrecision, pTitleFont->lfQuality, pTitleFont->lfPitchAndFamily, pTitleFont->lfFaceName))
		{
			if (cFont[1].CreateFont((4 * nHeight) / 5, 0, pItemsFont->lfEscapement, pItemsFont->lfOrientation, pItemsFont->lfWeight, pItemsFont->lfItalic, pItemsFont->lfUnderline, pItemsFont->lfStrikeOut, pItemsFont->lfCharSet, pItemsFont->lfOutPrecision, pItemsFont->lfClipPrecision, pItemsFont->lfQuality, pItemsFont->lfPitchAndFamily, pItemsFont->lfFaceName))
			{
				if (CalcPrintDocItemsTitleWidth(cDC, rArea, nColumns, cEventList, &cFont[0], &cFont[1], TRUE, nTabs, nIndent) > 0)
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

BOOL CEventBoxWnd::CalcPrintDocNoticeFonts(CDC &cDC, CONST RECT &rArea, CFont &cFont, CFont &cLogoFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 96, (INT)((-2.6*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL) && cLogoFont.CreateFont(max(-(rArea.right - rArea.left) / 96, (INT)((-2.6*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, STRING(IDS_FONTFACE_COMPANYLOGO));
}

BOOL CEventBoxWnd::CalcPrintDocFooterFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 80, (INT)((-3.0*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

INT CEventBoxWnd::CalcPrintDocItemsTitleWidth(CDC &cDC, LPCTSTR pszItem, CFont *pTitleFont) CONST
{
	INT  nWidth;
	CFont  *pOldFont;

	if ((pOldFont = cDC.SelectObject(pTitleFont)))
	{
		nWidth = cDC.GetTextExtent(pszItem, lstrlen(pszItem)).cx;
		cDC.SelectObject(pOldFont);
		return nWidth;
	}
	return 0;
}
INT CEventBoxWnd::CalcPrintDocItemsTitleWidth(CDC &cDC, CONST RECT &rArea, UINT nColumns, CONST CEventList &cEventList, CFont *pTitleFont, CFont *pItemsFont, BOOL bDefault, CUIntArray &nTabs, INT &nIndent) CONST
{
	INT  nTab[2];
	CFont  *pOldFont;
	TEXTMETRIC  tmFont;

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
	if (nColumns & EVENTBOX_TITLEITEM_TIME) nTabs.Add(max(CalcPrintDocItemsTitleWidth(cDC, STRING(IDS_EVENTBOX_TITLEITEM_TIME), pTitleFont), CalcPrintDocTimeItemWidth(cDC, pItemsFont)) + ((nTabs.GetSize() > 0) ? (2 * nIndent + nTabs.GetAt(nTabs.GetSize() - 1)) : 2 * nIndent));
	if (nColumns & EVENTBOX_TITLEITEM_CATEGORY) nTabs.Add(max(CalcPrintDocItemsTitleWidth(cDC, STRING(IDS_EVENTBOX_TITLEITEM_CATEGORY), pTitleFont), CalcPrintDocCategoryItemWidth(cDC, pItemsFont)) + ((nTabs.GetSize() > 0) ? (2 * nIndent + nTabs.GetAt(nTabs.GetSize() - 1)) : 2 * nIndent));
	if (nColumns & EVENTBOX_TITLEITEM_TYPE) nTabs.Add(max(CalcPrintDocItemsTitleWidth(cDC, STRING(IDS_EVENTBOX_TITLEITEM_TYPE), pTitleFont), CalcPrintDocTypeItemWidth(cDC, cEventList, pItemsFont)) + ((nTabs.GetSize() > 0) ? (2 * nIndent + nTabs.GetAt(nTabs.GetSize() - 1)) : 2 * nIndent));
	if (nColumns & EVENTBOX_TITLEITEM_MESSAGE) nTabs.Add(max(CalcPrintDocItemsTitleWidth(cDC, STRING(IDS_EVENTBOX_TITLEITEM_MESSAGE), pTitleFont), CalcPrintDocMessageItemWidth(cDC, pItemsFont)) + (((nTab[0] = (INT)(nTabs.GetSize() - 1)) >= 0) ? (2 * nIndent + nTabs.GetAt(nTab[0])) : 2 * nIndent));
	if (nColumns & EVENTBOX_TITLEITEM_COMMENTS) nTabs.Add(max(CalcPrintDocItemsTitleWidth(cDC, STRING(IDS_EVENTBOX_TITLEITEM_COMMENTS), pTitleFont), CalcPrintDocCommentsItemWidth(cDC, pItemsFont)) + (((nTab[1] = (INT)(nTabs.GetSize() - 1)) > 0) ? (2 * nIndent + nTabs.GetAt(nTab[1])) : 2 * nIndent));
	if (nColumns & EVENTBOX_TITLEITEM_RECIPIENTS) nTabs.Add(max(CalcPrintDocItemsTitleWidth(cDC, STRING(IDS_EVENTBOX_TITLEITEM_RECIPIENTS), pTitleFont), CalcPrintDocRecipientsItemWidth(cDC, cEventList, pItemsFont)) + ((nTabs.GetSize() > 0) ? (2 * nIndent + nTabs.GetAt(nTabs.GetSize() - 1)) : 2 * nIndent));
	if (nColumns & EVENTBOX_TITLEITEM_USER) nTabs.Add(max(CalcPrintDocItemsTitleWidth(cDC, STRING(IDS_EVENTBOX_TITLEITEM_USER), pTitleFont), CalcPrintDocUserItemWidth(cDC, cEventList, pItemsFont)) + ((nTabs.GetSize() > 0) ? (2 * nIndent + nTabs.GetAt(nTabs.GetSize() - 1)) : 2 * nIndent));
	if (nTabs.GetSize() > 0) nTabs.SetAt(nTabs.GetSize() - 1, nTabs.GetAt(nTabs.GetSize() - 1) - nIndent);
	return((INT)nTabs.GetSize());
}

INT CEventBoxWnd::CalcPrintDocTimeItemWidth(CDC &cDC, CFont *pItemsFont) CONST
{
	INT  nWidth;
	CFont  *pOldFont;
	CTimeKey  tTime;

	if ((pOldFont = cDC.SelectObject(pItemsFont)))
	{
		nWidth = cDC.GetTextExtent(tTime.Format(), tTime.Format().GetLength()).cx;
		cDC.SelectObject(pOldFont);
		return nWidth;
	}
	return 0;
}

INT CEventBoxWnd::CalcPrintDocCategoryItemWidth(CDC &cDC, CFont *pItemsFont) CONST
{
	INT  nWidth;
	CFont  *pOldFont;

	if ((pOldFont = cDC.SelectObject(pItemsFont)))
	{
		nWidth = max(max(cDC.GetTextExtent(STRING(IDS_EVENTCATEGORY_SYSTEM), lstrlen(STRING(IDS_EVENTCATEGORY_SYSTEM))).cx, cDC.GetTextExtent(STRING(IDS_EVENTCATEGORY_SPACECRAFT), lstrlen(STRING(IDS_EVENTCATEGORY_SPACECRAFT))).cx), cDC.GetTextExtent(STRING(IDS_EVENTCATEGORY_USER), lstrlen(STRING(IDS_EVENTCATEGORY_USER))).cx);
		cDC.SelectObject(pOldFont);
		return nWidth;
	}
	return 0;
}

INT CEventBoxWnd::CalcPrintDocTypeItemWidth(CDC &cDC, CONST CEventList &cEventList, CFont *pItemsFont) CONST
{
	INT  nItem;
	INT  nItems;
	INT  nWidth;
	CFont  *pOldFont;
	CEventObject  *pEvent;

	if ((pOldFont = cDC.SelectObject(pItemsFont)))
	{
		for (nItem = 0, nItems = (INT)cEventList.GetSize(), nWidth = 0; nItem < nItems; nItem++)
		{
			if ((pEvent = cEventList.GetAt(nItem)) != (CEventObject *)NULL)
			{
				nWidth = max(cDC.GetTextExtent(pEvent->GetType()).cx, nWidth);
				continue;
			}
		}
		cDC.SelectObject(pOldFont);
		return nWidth;
	}
	return 0;
}

INT CEventBoxWnd::CalcPrintDocMessageItemWidth(CDC &cDC, CFont *pItemsFont) CONST
{
	return 5 * CalcPrintDocTimeItemWidth(cDC, pItemsFont);
}

INT CEventBoxWnd::CalcPrintDocCommentsItemWidth(CDC &cDC, CFont *pItemsFont) CONST
{
	return 3 * CalcPrintDocTimeItemWidth(cDC, pItemsFont);
}

INT CEventBoxWnd::CalcPrintDocRecipientsItemWidth(CDC &cDC, CONST CEventList &cEventList, CFont *pItemsFont) CONST
{
	INT  nItem;
	INT  nItems;
	INT  nWidth;
	INT  nRecipient;
	INT  nRecipients;
	CFont  *pOldFont;
	CEventObject  *pEvent;
	CStringArray  szRecipients;

	if ((pOldFont = cDC.SelectObject(pItemsFont)))
	{
		for (nItem = 0, nItems = (INT)cEventList.GetSize(), nWidth = 0; nItem < nItems; nItem++)
		{
			if ((pEvent = cEventList.GetAt(nItem)) && pEvent->GetNotificationRecipients(szRecipients) > 0)
			{
				for (nRecipient = 0, nRecipients = (INT)szRecipients.GetSize(); nRecipient < nRecipients; nRecipient++)
				{
					nWidth = max(cDC.GetTextExtent(szRecipients.GetAt(nRecipient)).cx, nWidth);
					continue;
				}
			}
		}
		cDC.SelectObject(pOldFont);
		return nWidth;
	}
	return 0;
}

INT CEventBoxWnd::CalcPrintDocUserItemWidth(CDC &cDC, CONST CEventList &cEventList, CFont *pItemsFont) CONST
{
	INT  nItem;
	INT  nItems;
	INT  nWidth;
	CFont  *pOldFont;
	CEventObject  *pEvent;

	if ((pOldFont = cDC.SelectObject(pItemsFont)))
	{
		for (nItem = 0, nItems = (INT)cEventList.GetSize(), nWidth = 0; nItem < nItems; nItem++)
		{
			if ((pEvent = cEventList.GetAt(nItem)) != (CEventObject *)NULL)
			{
				nWidth = max(cDC.GetTextExtent(pEvent->GetUser()).cx, nWidth);
				continue;
			}
		}
		cDC.SelectObject(pOldFont);
		return nWidth;
	}
	return 0;
}

BOOL CEventBoxWnd::CalcPrintDocRect(CDC &cDC, CONST RECT &rtMargin, BOOL bMetric) CONST
{
	CRect  rClip;

	rClip.SetRect(0, 0, cDC.GetDeviceCaps(HORZRES), cDC.GetDeviceCaps(VERTRES));
	rClip.DeflateRect((bMetric) ? (rtMargin.left*cDC.GetDeviceCaps(HORZRES)) / (100 * cDC.GetDeviceCaps(HORZSIZE)) : (rtMargin.left*cDC.GetDeviceCaps(LOGPIXELSX)) / 1000, (bMetric) ? (rtMargin.top*cDC.GetDeviceCaps(VERTRES)) / (100 * cDC.GetDeviceCaps(VERTSIZE)) : (rtMargin.top*cDC.GetDeviceCaps(LOGPIXELSY)) / 1000, (bMetric) ? (rtMargin.right*cDC.GetDeviceCaps(HORZRES)) / (100 * cDC.GetDeviceCaps(HORZSIZE)) : (rtMargin.right*cDC.GetDeviceCaps(LOGPIXELSX)) / 1000, (bMetric) ? (rtMargin.bottom*cDC.GetDeviceCaps(VERTRES)) / (100 * cDC.GetDeviceCaps(VERTSIZE)) : (rtMargin.bottom*cDC.GetDeviceCaps(LOGPIXELSY)) / 1000);
	return((cDC.IntersectClipRect(rClip) != ERROR) ? TRUE : FALSE);
}

BOOL CEventBoxWnd::SetLayoutInfo(UINT nColumns, CONST CUIntArray &nWidths, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont, INT nIndex, INT nCount, CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo)
{
	return((m_wndView.SetTitle(nColumns, nWidths) && m_wndView.SetTitleFont(pTitleFont) && m_wndView.SetTextFont(pItemsFont) && m_wndView.SetLayoutInfo(nIndex, nCount, pHorzScrollInfo, pVertScrollInfo)) ? TRUE : FALSE);
}

BOOL CEventBoxWnd::GetLayoutInfo(UINT &nColumns, CUIntArray &nWidths, LOGFONT *pTitleFont, LOGFONT *pItemsFont, INT &nIndex, INT &nCount, SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST
{
	return((m_wndView.GetTitle(nColumns, nWidths) && m_wndView.GetTitleFont(pTitleFont) && m_wndView.GetTextFont(pItemsFont) && m_wndView.GetLayoutInfo(nIndex, nCount, pHorzScrollInfo, pVertScrollInfo)) ? TRUE : FALSE);
}

BOOL CEventBoxWnd::LoadAlertIcons()
{
	return(((m_hAlertIcon[0] = ((m_hAlertIcon[1] = (HICON)LoadImage(GetModuleHandle((LPCTSTR)NULL), MAKEINTRESOURCE(IDI_ALERTBOX), IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR))) ? (HICON)LoadImage(GetModuleHandle((LPCTSTR)NULL), MAKEINTRESOURCE(IDI_MAINFRAMEALERT), IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR) : (HICON)NULL)) ? TRUE : FALSE);
}

VOID CEventBoxWnd::FreeAlertIcons()
{
	if (m_hAlertIcon[0]) DestroyIcon(m_hAlertIcon[0]);
	if (m_hAlertIcon[1]) DestroyIcon(m_hAlertIcon[1]);
	m_hAlertIcon[0] = m_hAlertIcon[1] = (HICON)NULL;
}

BEGIN_MESSAGE_MAP(CEventBoxWnd, CDisplayWnd)
	//{{AFX_MSG_MAP(CEventBoxWnd)
	ON_WM_CREATE()
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_NCPAINT()
	ON_WM_SHOWWINDOW()
	ON_WM_SETFOCUS()
	ON_WM_DESTROY()
	ON_COMMAND(IDM_EVENTBOXSETTINGS, OnSettings)
	ON_COMMAND(IDM_EVENTBOXSCHEDULE, OnSchedule)
	ON_COMMAND(IDM_EVENTBOXWATCH, OnWatch)
	ON_COMMAND(IDM_EVENTBOXDETAILS, OnDetails)
	ON_COMMAND(IDM_EVENTBOXACKNOWLEDGE, OnAcknowledge)
	ON_COMMAND(IDM_EVENTBOXCLEARALL, OnClearAll)
	ON_COMMAND(IDM_EVENTBOXRETRIEVALS, OnRetrievals)
	ON_COMMAND(IDM_EVENTBOXRETRIEVESTEPFORWARD, OnRetrieveManualForward)
	ON_COMMAND(IDM_EVENTBOXPRINT, OnPrint)
	ON_COMMAND(IDM_EVENTBOXALLEVENTS, OnCopyAllEvents)
	ON_COMMAND(IDM_EVENTBOXSINGLEEVENT, OnCopySingleEvent)
	ON_COMMAND(IDM_EVENTBOXUPTOEVENT, OnCopyUpToEvent)
	ON_COMMAND(IDM_EVENTBOXFROMEVENT, OnCopyFromEvent)
	ON_UPDATE_COMMAND_UI(IDM_EVENTBOXSETTINGS, OnUpdateSettings)
	ON_UPDATE_COMMAND_UI(IDM_EVENTBOXSCHEDULE, OnUpdateSchedule)
	ON_UPDATE_COMMAND_UI(IDM_EVENTBOXWATCH, OnUpdateWatch)
	ON_UPDATE_COMMAND_UI(IDM_EVENTBOXDETAILS, OnUpdateDetails)
	ON_UPDATE_COMMAND_UI(IDM_EVENTBOXACKNOWLEDGE, OnUpdateAcknowledge)
	ON_UPDATE_COMMAND_UI(IDM_EVENTBOXCLEARALL, OnUpdateClearAll)
	ON_UPDATE_COMMAND_UI(IDM_EVENTBOXRETRIEVALS, OnUpdateRetrievals)
	ON_UPDATE_COMMAND_UI(IDM_EVENTBOXRETRIEVESTEPFORWARD, OnUpdateRetrieveManualForward)
	ON_UPDATE_COMMAND_UI(IDM_EVENTBOXPRINT, OnUpdatePrint)
	ON_UPDATE_COMMAND_UI(IDM_EVENTBOXALLEVENTS, OnUpdateCopyAllEvents)
	ON_UPDATE_COMMAND_UI(IDM_EVENTBOXSINGLEEVENT, OnUpdateCopySingleEvent)
	ON_UPDATE_COMMAND_UI(IDM_EVENTBOXUPTOEVENT, OnUpdateCopyUpToEvent)
	ON_UPDATE_COMMAND_UI(IDM_EVENTBOXFROMEVENT, OnUpdateCopyFromEvent)
	ON_UPDATE_COMMAND_UI(ID_EVENTBOX_STATUSBAR_ITEMPANE, OnUpdateStatusBarItemPane)
	ON_UPDATE_COMMAND_UI(ID_EVENTBOX_STATUSBAR_MODEPANE, OnUpdateStatusBarModePane)
	ON_UPDATE_COMMAND_UI(ID_EVENTBOX_STATUSBAR_SYSTEMPANE, OnUpdateStatusBarSystemPane)
	ON_UPDATE_COMMAND_UI(ID_EVENTBOX_STATUSBAR_SPACECRAFTPANE, OnUpdateStatusBarSpacecraftPane)
	ON_UPDATE_COMMAND_UI(ID_EVENTBOX_STATUSBAR_USERPANE, OnUpdateStatusBarUserPane)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventBoxWnd message handlers

int CEventBoxWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDisplayWnd::OnCreate(lpCreateStruct) != -1)
	{
		for (EnableDocking(CBRS_ALIGN_TOP); CreateToolBar() && CreateStatusBar() && CreateView() && LoadAccelTable(MAKEINTRESOURCE(IDR_EVENTBOXFRAME)) && LoadAlertIcons(); )
		{
			UpdateBars();
			return 0;
		}
	}
	return -1;
}

void CEventBoxWnd::OnGetMinMaxInfo(MINMAXINFO *lpMMI)
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

void CEventBoxWnd::OnSize(UINT nType, int cx, int cy)
{
	CDisplayWnd::OnSize(nType, cx, cy);
	m_wndView.RecalcLayout();
}

BOOL CEventBoxWnd::OnEraseBkgnd(CDC *pDC)
{
	m_wndToolBar.UpdateWindow();
	m_wndStatusBar.UpdateWindow();
	return TRUE;
}

void CEventBoxWnd::OnNcPaint()
{
	DrawAlertIcon(FALSE);
	CDisplayWnd::OnNcPaint();
}

void CEventBoxWnd::OnShowWindow(BOOL bShow, UINT nStatus)
{
	UINT  nFlags;

	if (bShow)
	{
		if (nStatus == EVENTBOX_FILTER_BRINGEVENTS || nStatus == (UINT)-1)
		{
			if (GetDisplayArea()->GetBehavior(nFlags) && nFlags == 0)
			{
				for (ShowWindow(SW_SHOWNOACTIVATE); nStatus != (UINT)-1; )
				{
					MDIActivate();
					break;
				}
			}
			return;
		}
	}
	CDisplayWnd::OnShowWindow(bShow, nStatus);
}

void CEventBoxWnd::OnSetFocus(CWnd *pOldWnd)
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

BOOL CEventBoxWnd::OnCloseOpenDialog(UINT nCode)
{
	UINT  nMode;
	UINT  nLimit;
	UINT  nCount;
	UINT  nColumns;
	LOGFONT  fntTitle;
	LOGFONT  fntItems;
	CTimeKey  tStartTime[2];
	CTimeKey  tStopTime[2];
	CStringArray  szTypes;
	CStringArray  szSubtypes;
	CEventBoxPrintJobs  pJobs;
	CUIntArray  nColors;
	CProfile  cProfile;

	if (nCode == IDOK)
	{
		if (ActivateAccount(m_dlgOpen.GetComputerName(), m_dlgOpen.GetSpacecraftName(), m_dlgOpen.GetUserName(), !m_dlgOpen.UseGlobal(), m_dlgOpen.GetMode()))
		{
			if (m_dlgOpen.IsLayoutModified())
			{
				m_dlgOpen.GetLayoutTitle(nColumns);
				m_dlgOpen.GetLayoutTitleFont(&fntTitle);
				m_dlgOpen.GetLayoutListFont(&fntItems);
				if (!SetTitle(nColumns) || !SetTitleFont(&fntTitle) || !SetItemsFont(&fntItems)) return FALSE;
			}
			if (m_dlgOpen.UseLayoutAsDefault())
			{
				m_dlgOpen.GetLayoutTitle(nColumns);
				m_dlgOpen.GetLayoutTitleFont(&fntTitle);
				m_dlgOpen.GetLayoutListFont(&fntItems);
				if (!cProfile.SetEventBoxDefaultLayoutInfo(nColumns) || !cProfile.SetEventBoxDefaultFontsInfo(&fntTitle, &fntItems)) return FALSE;
			}
			if (m_dlgOpen.IsFilteringModified())
			{
				m_dlgOpen.GetFilterMode(nMode);
				m_dlgOpen.GetFilterBehavior(nCount);
				m_dlgOpen.GetFilterBehavior(szTypes, szSubtypes);
				m_dlgOpen.GetFilterLimitation(nLimit);
				m_dlgOpen.GetFilterLimitation(tStartTime[0], tStopTime[0]);
				m_dlgOpen.GetFilterColors(nColors);
				if (!SetFilterMode(nMode) || SetFilterBehavior(nCount) < 0 || SetFilterBehavior(szTypes, szSubtypes) < 0 || SetFilterLimitation(nLimit) < 0 || SetFilterLimitation(tStartTime[0], tStopTime[0]) < 0 || !SetFilterColors(nColors)) return FALSE;
			}
			if (m_dlgOpen.IsPrintingModified())
			{
				m_dlgOpen.GetPrintJobs(pJobs);
				if (!SetPrintJobs(pJobs)) return FALSE;
			}
			if (m_dlgOpen.GetMode() == DISPLAY_MODE_REALTIME)
			{
				for (SetMode(m_dlgOpen.GetMode()); RetrieveAutoEvents() && StartWatchEvents(); )
				{
					UpdateAllPanes();
					return Start();
				}
				return FALSE;
			}
			if (m_dlgOpen.GetMode() == DISPLAY_MODE_HISTORY)
			{
				SetMode(m_dlgOpen.GetMode());
				m_dlgOpen.GetRetrieveMode(nMode);
				m_dlgOpen.GetRetrieveLimit(nLimit);
				m_dlgOpen.GetRetrieveStartTime(tStartTime[1]);
				m_dlgOpen.GetRetrieveStopTime(tStopTime[1]);
				SetRetrieveMode(nMode);
				SetRetrieveLimit(nLimit);
				SetRetrieveStartTime(tStartTime[1]);
				SetRetrieveStopTime(tStopTime[1]);
				UpdateAllPanes();
				return Start();
			}
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CEventBoxWnd::OnCloseSettingsDialog(UINT nCode)
{
	UINT  nMode;
	UINT  nLimit;
	UINT  nCount;
	UINT  nColumns;
	BOOL  bDefault;
	LOGFONT  fntTitle;
	LOGFONT  fntItems;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CStringArray  szTypes;
	CStringArray  szSubtypes;
	CEventBoxPrintJobs  pJobs;
	CUIntArray  nColors;
	CProfile  cProfile;

	if (nCode == IDOK)
	{
		if (m_dlgSettings.IsLayoutModified())
		{
			m_dlgSettings.GetLayoutTitle(nColumns);
			m_dlgSettings.GetLayoutTitleFont(&fntTitle);
			m_dlgSettings.GetLayoutListFont(&fntItems);
			if (!SetTitle(nColumns) || !SetTitleFont(&fntTitle) || !SetItemsFont(&fntItems)) return FALSE;
		}
		if (m_dlgSettings.UseLayoutAsDefault(bDefault) && bDefault)
		{
			m_dlgSettings.GetLayoutTitle(nColumns);
			m_dlgSettings.GetLayoutTitleFont(&fntTitle);
			m_dlgSettings.GetLayoutListFont(&fntItems);
			if (!cProfile.SetEventBoxDefaultLayoutInfo(nColumns) || !cProfile.SetEventBoxDefaultFontsInfo(&fntTitle, &fntItems)) return FALSE;
		}
		if (m_dlgSettings.IsFilteringModified())
		{
			m_dlgSettings.GetFilterMode(nMode);
			m_dlgSettings.GetFilterBehavior(nCount);
			m_dlgSettings.GetFilterBehavior(szTypes, szSubtypes);
			m_dlgSettings.GetFilterLimitation(nLimit);
			m_dlgSettings.GetFilterLimitation(tStartTime, tStopTime);
			m_dlgSettings.GetFilterColors(nColors);
			if (!SetFilterMode(nMode) || SetFilterBehavior(nCount) < 0 || SetFilterBehavior(szTypes, szSubtypes) < 0 || SetFilterLimitation(nLimit) < 0 || SetFilterLimitation(tStartTime, tStopTime) < 0 || !SetFilterColors(nColors)) return FALSE;
		}
		if (m_dlgSettings.IsPrintingModified())
		{
			m_dlgSettings.GetPrintJobs(pJobs);
			if (!SetPrintJobs(pJobs)) return FALSE;
		}
		UpdateAllPanes();
	}
	return TRUE;
}

BOOL CEventBoxWnd::OnCloseScheduleDialog(UINT nCode)
{
	CEventObject  *pEvent;

	if (nCode == IDOK)
	{
		if ((pEvent = new CEventObject))
		{
			if (m_dlgSchedule.GetScheduleInfo(pEvent) && ScheduleEvent(pEvent)) return TRUE;
			delete pEvent;
		}
		ReportEvent(SYSTEM_WARNING_EVENT_SCHEDULE_FAILURE);
		return FALSE;
	}
	return TRUE;
}

BOOL CEventBoxWnd::OnCloseWatchDialog(UINT nCode)
{
	if (nCode == IDOK)
	{
		if (m_dlgWatch.GetScheduleInfo(m_pEventList))
		{
			UpdateAlertStatus();
			return TRUE;
		}
		ReportEvent(SYSTEM_WARNING_EVENTLIST_SCHEDULE_FAILURE);
		return FALSE;
	}
	return TRUE;
}

BOOL CEventBoxWnd::OnCloseRetrieveDialog(UINT nCode)
{
	UINT  nMode[2];
	UINT  nLimit[2];
	CTimeKey  tStartTime[2];
	CTimeKey  tStopTime[2];

	if (nCode == IDOK)
	{
		nMode[0] = GetRetrieveMode();
		nLimit[0] = GetRetrieveLimit();
		tStartTime[0] = GetRetrieveStartTime();
		tStopTime[0] = GetRetrieveStopTime();
		for (m_dlgRetrievals.GetMode(nMode[1]); nMode[1]; )
		{
			m_dlgRetrievals.GetLimit(nLimit[1]);
			m_dlgRetrievals.GetStartTime(tStartTime[1]);
			m_dlgRetrievals.GetStopTime(tStopTime[1]);
			if (SetMode(DISPLAY_MODE_HISTORY) && (!IsWatchingEvents() || StopWatchEvents()) && (!IsRetrievingEvents() || StopRetrieveEvents()) && DeleteAllEvents() && StartRetrieveEvents(nMode[1], nLimit[1], tStartTime[1], tStopTime[1]))
			{
				UpdateAllPanes();
				return TRUE;
			}
			SetRetrieveMode(nMode[0]);
			SetRetrieveLimit(nLimit[0]);
			SetRetrieveStartTime(tStartTime[0]);
			SetRetrieveStopTime(tStopTime[0]);
			SetMode((!nMode[0]) ? DISPLAY_MODE_REALTIME : DISPLAY_MODE_HISTORY);
			UpdateAllPanes();
			return FALSE;
		}
		SetRetrieveMode();
		SetRetrieveLimit();
		SetRetrieveStartTime();
		SetRetrieveStopTime();
		if (SetMode(DISPLAY_MODE_REALTIME) && (!IsWatchingEvents() || StopWatchEvents()) && (!IsRetrievingEvents() || StopRetrieveEvents()) && DeleteAllEvents() && StartWatchEvents())
		{
			UpdateAllPanes();
			return TRUE;
		}
		SetRetrieveMode(nMode[0]);
		SetRetrieveLimit(nLimit[0]);
		SetRetrieveStartTime(tStartTime[0]);
		SetRetrieveStopTime(tStopTime[0]);
		SetMode((!nMode[0]) ? DISPLAY_MODE_REALTIME : DISPLAY_MODE_HISTORY);
		UpdateAllPanes();
		return FALSE;
	}
	return TRUE;
}

void CEventBoxWnd::OnSettings()
{
	CHourglassCursor  cCursor;

	ReportEvent((m_dlgSettings.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CEventBoxWnd::OnSchedule()
{
	CHourglassCursor  cCursor;

	ReportEvent((m_dlgSchedule.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CEventBoxWnd::OnWatch()
{
	CHourglassCursor  cCursor;

	ReportEvent((m_dlgWatch.Create(this, m_pEventList) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CEventBoxWnd::OnDetails()
{
	CEventObject  cEvent[2];
	CHourglassCursor  cCursor;

	ReportEvent((m_dlgDetails.Create(this, (GetCurEvent(&cEvent[0]) >= 0) ? &cEvent[0] : &cEvent[1]) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CEventBoxWnd::OnAcknowledge()
{
	CHourglassCursor  cCursor;

	ReportEvent((m_dlgAcknowledge.Create(this, m_pEventList) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CEventBoxWnd::OnClearAll()
{
	CHourglassCursor  cCursor;

	DeleteAllEvents(FALSE);
}

void CEventBoxWnd::OnRetrievals()
{
	BOOL  bLocal;
	CString  szUserName;
	CString  szComputerName;
	CString  szSpacecraftName;
	CHourglassCursor  cCursor;

	GetAccountName(szComputerName, szSpacecraftName, szUserName, bLocal);
	ReportEvent((m_dlgRetrievals.Create(this, szComputerName, szSpacecraftName, szUserName, bLocal) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CEventBoxWnd::OnRetrieveManualForward()
{
	RetrieveMoreEvents();
}

void CEventBoxWnd::OnPrint()
{
	CHourglassCursor  cCursor;

	ReportEvent((!Print()) ? SYSTEM_WARNING_DISPLAY_PRINT_FAILURE : SYSTEM_NOERROR);
}

void CEventBoxWnd::OnCopyAllEvents()
{
	CHourglassCursor  cCursor;

	CopyEvents(EVENTBOX_CLIPBOARD_ALLEVENTS);
}

void CEventBoxWnd::OnCopySingleEvent()
{
	CHourglassCursor  cCursor;

	CopyEvents(EVENTBOX_CLIPBOARD_SINGLEEVENT);
}

void CEventBoxWnd::OnCopyUpToEvent()
{
	CHourglassCursor  cCursor;

	CopyEvents(EVENTBOX_CLIPBOARD_UPTOEVENT);
}

void CEventBoxWnd::OnCopyFromEvent()
{
	CHourglassCursor  cCursor;

	CopyEvents(EVENTBOX_CLIPBOARD_FROMEVENT);
}

void CEventBoxWnd::OnDestroy()
{
	CHourglassCursor  cCursor;

	Stop();
	FreeAlertIcons();
	CDisplayWnd::OnDestroy();
}

void CEventBoxWnd::OnUpdateSettings(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsInitialized() && (GetScope() == DISPLAY_SCOPE_LOCAL || CheckAccountPrivilege(PRIVILEGE_EVENTBOX_SETUPVIEW) || CheckAccountPrivilege(PRIVILEGE_EVENTBOX_SETUPCHANGE))) ? TRUE : FALSE);
	pCmdUI->SetCheck(IsWindow(m_dlgSettings.GetSafeHwnd()));
}

void CEventBoxWnd::OnUpdateSchedule(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsInitialized() && GetScope() == DISPLAY_SCOPE_GLOBAL  &&  CheckAccountPrivilege(PRIVILEGE_EVENTBOX_SCHEDULE)) ? TRUE : FALSE);
	pCmdUI->SetCheck(IsWindow(m_dlgSchedule.GetSafeHwnd()));
}

void CEventBoxWnd::OnUpdateWatch(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsInitialized() && GetScope() == DISPLAY_SCOPE_GLOBAL  &&  CheckAccountPrivilege(PRIVILEGE_EVENTBOX_WATCH)) ? TRUE : FALSE);
	pCmdUI->SetCheck(IsWindow(m_dlgWatch.GetSafeHwnd()));
}

void CEventBoxWnd::OnUpdateDetails(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsInitialized() && (GetScope() == DISPLAY_SCOPE_LOCAL || CheckAccountPrivilege(PRIVILEGE_EVENTBOX_LOOK)) && GetEventCount() > 0) ? TRUE : FALSE);
	pCmdUI->SetCheck(IsWindow(m_dlgDetails.GetSafeHwnd()));
}

void CEventBoxWnd::OnUpdateAcknowledge(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsInitialized() && (GetScope() == DISPLAY_SCOPE_LOCAL || CheckAccountPrivilege(PRIVILEGE_EVENTBOX_ACKNOWLEDGE)) && GetMode() == DISPLAY_MODE_REALTIME  &&  IsAlerted()) ? TRUE : FALSE);
	pCmdUI->SetCheck(IsWindow(m_dlgAcknowledge.GetSafeHwnd()));
}

void CEventBoxWnd::OnUpdateClearAll(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsInitialized() && (GetScope() == DISPLAY_SCOPE_LOCAL || CheckAccountPrivilege(PRIVILEGE_EVENTBOX_RESET)) && GetEventCount() > 0) ? TRUE : FALSE);
}

void CEventBoxWnd::OnUpdateRetrievals(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsInitialized() && GetScope() == DISPLAY_SCOPE_LOCAL) ? TRUE : FALSE);
	pCmdUI->SetCheck(IsWindow(m_dlgRetrievals.GetSafeHwnd()));
}

void CEventBoxWnd::OnUpdateRetrieveManualForward(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsInitialized() && GetScope() == DISPLAY_SCOPE_LOCAL  &&  IsRetrievingEvents(TRUE)) ? TRUE : FALSE);
}

void CEventBoxWnd::OnUpdatePrint(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsInitialized() && IsDefaultPrinterAvailable() && CanPrint()) ? TRUE : FALSE);
}

void CEventBoxWnd::OnUpdateCopyAllEvents(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((GetEventCount() > 0) ? TRUE : FALSE);
}

void CEventBoxWnd::OnUpdateCopySingleEvent(CCmdUI *pCmdUI)
{
	CEventObject  cEvent;

	pCmdUI->Enable((GetEventCount() > 0 && GetCurEvent(&cEvent) >= 0) ? TRUE : FALSE);
}

void CEventBoxWnd::OnUpdateCopyUpToEvent(CCmdUI *pCmdUI)
{
	CEventObject  cEvent;

	pCmdUI->Enable((GetEventCount() > 0 && GetCurEvent(&cEvent) >= 0) ? TRUE : FALSE);
}

void CEventBoxWnd::OnUpdateCopyFromEvent(CCmdUI *pCmdUI)
{
	CEventObject  cEvent;

	pCmdUI->Enable((GetEventCount() > 0 && GetCurEvent(&cEvent) >= 0) ? TRUE : FALSE);
}

void CEventBoxWnd::OnUpdateStatusBarItemPane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CEventBoxWnd::OnUpdateStatusBarModePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CEventBoxWnd::OnUpdateStatusBarSystemPane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CEventBoxWnd::OnUpdateStatusBarSpacecraftPane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CEventBoxWnd::OnUpdateStatusBarUserPane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}
