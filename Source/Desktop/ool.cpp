// OOL.CPP : Out-of-limit Display Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the out-of-limit
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


static UINT BASED_CODE nOOLStatusBarIndicators[] =
{
	ID_OOL_STATUSBAR_MESSAGEPANE,
	ID_OOL_STATUSBAR_MODEPANE,
	ID_OOL_STATUSBAR_TYPEPANE
};



/////////////////////////////////////////////////////////////////////////////
// COOLPrintJobInfo

COOLPrintJobInfo::COOLPrintJobInfo() : CObject()
{
	m_nPrintMode = 0;
	m_nPrintFlags = 0;
	m_nPrintCount[0] = 0;
	m_nPrintCount[1] = 0;
	m_nPrintByCount = 0;
	m_tPrintAtTime = 0;
	m_tPrintAtDailyTime = 0;
	m_tPrintByTime[0] = 0;
	m_tPrintByTime[1] = 0;
	m_tPrintLastTime[0] = 0;
	m_tPrintLastTime[1] = 0;
	m_tRepeatInterval = 0;
	m_nRepeatStopByCount[0] = 0;
	m_nRepeatStopByCount[1] = 0;
	m_tRepeatStopByTime[0] = 0;
	m_tRepeatStopByTime[1] = 0;
}

VOID COOLPrintJobInfo::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString COOLPrintJobInfo::GetName() CONST
{
	return m_szName;
}

VOID COOLPrintJobInfo::SetProfile(LPCTSTR pszProfile)
{
	m_szProfile = pszProfile;
}

CString COOLPrintJobInfo::GetProfile() CONST
{
	return m_szProfile;
}

VOID COOLPrintJobInfo::SetComments(LPCTSTR pszComments)
{
	m_szComments = pszComments;
}

CString COOLPrintJobInfo::GetComments() CONST
{
	return m_szComments;
}

BOOL COOLPrintJobInfo::SetPrintMode(UINT nMode)
{
	m_nPrintMode = nMode;
	return TRUE;
}

UINT COOLPrintJobInfo::GetPrintMode() CONST
{
	return m_nPrintMode;
}

BOOL COOLPrintJobInfo::SetPrintFlags(UINT nFlags)
{
	if (nFlags == OOL_PRINT_ATTIME || nFlags == OOL_PRINT_ATDAILYTIME || nFlags == OOL_PRINT_ATEVENT || !nFlags)
	{
		m_nPrintFlags = nFlags;
		return TRUE;
	}
	return FALSE;
}

UINT COOLPrintJobInfo::GetPrintFlags() CONST
{
	return m_nPrintFlags;
}

BOOL COOLPrintJobInfo::SetPrintBySide(UINT nCount)
{
	if ((m_nPrintMode & OOL_PRINT_FIRSTSIDE) || (m_nPrintMode & OOL_PRINT_LASTSIDE))
	{
		m_nPrintByCount = nCount;
		return TRUE;
	}
	return FALSE;
}

BOOL COOLPrintJobInfo::GetPrintBySide(UINT &nCount) CONST
{
	if ((m_nPrintMode & OOL_PRINT_FIRSTSIDE) || (m_nPrintMode & OOL_PRINT_LASTSIDE))
	{
		nCount = m_nPrintByCount;
		return TRUE;
	}
	return FALSE;
}

BOOL COOLPrintJobInfo::SetPrintByTime(CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime)
{
	if (m_nPrintMode & OOL_PRINT_BYTIME)
	{
		m_tPrintByTime[0] = tStartTime;
		m_tPrintByTime[1] = tStopTime;
		return TRUE;
	}
	return FALSE;
}

BOOL COOLPrintJobInfo::GetPrintByTime(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	if (m_nPrintMode & OOL_PRINT_BYTIME)
	{
		tStartTime = m_tPrintByTime[0];
		tStopTime = m_tPrintByTime[1];
		return TRUE;
	}
	return FALSE;
}

BOOL COOLPrintJobInfo::SetPrintAtTime(CONST CTimeKey &tTime)
{
	if ((m_nPrintMode & OOL_PRINT_ATTIME) && !(m_nPrintMode & OOL_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & OOL_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & OOL_PRINT_REPEATSTOPBYTIME))
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
BOOL COOLPrintJobInfo::SetPrintAtTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval)
{
	if ((m_nPrintMode & OOL_PRINT_ATTIME) && (m_nPrintMode & OOL_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & OOL_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & OOL_PRINT_REPEATSTOPBYTIME))
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
BOOL COOLPrintJobInfo::SetPrintAtTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval, UINT nStopCount)
{
	if ((m_nPrintMode & OOL_PRINT_ATTIME) && (m_nPrintMode & OOL_PRINT_REPEATBYINTERVAL) && (m_nPrintMode & OOL_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & OOL_PRINT_REPEATSTOPBYTIME))
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
BOOL COOLPrintJobInfo::SetPrintAtTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval, CONST CTimeKey &tStopTime)
{
	if ((m_nPrintMode & OOL_PRINT_ATTIME) && (m_nPrintMode & OOL_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & OOL_PRINT_REPEATSTOPBYCOUNT) && (m_nPrintMode & OOL_PRINT_REPEATSTOPBYTIME))
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

BOOL COOLPrintJobInfo::GetPrintAtTime(CTimeKey &tTime) CONST
{
	if ((m_nPrintMode & OOL_PRINT_ATTIME) && !(m_nPrintMode & OOL_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & OOL_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & OOL_PRINT_REPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtTime;
		return TRUE;
	}
	return FALSE;
}
BOOL COOLPrintJobInfo::GetPrintAtTime(CTimeKey &tTime, CTimeSpan &tInterval) CONST
{
	if ((m_nPrintMode & OOL_PRINT_ATTIME) && (m_nPrintMode & OOL_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & OOL_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & OOL_PRINT_REPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtTime;
		tInterval = m_tRepeatInterval;
		return TRUE;
	}
	return FALSE;
}
BOOL COOLPrintJobInfo::GetPrintAtTime(CTimeKey &tTime, CTimeSpan &tInterval, UINT &nStopCount) CONST
{
	if ((m_nPrintMode & OOL_PRINT_ATTIME) && (m_nPrintMode & OOL_PRINT_REPEATBYINTERVAL) && (m_nPrintMode & OOL_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & OOL_PRINT_REPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtTime;
		tInterval = m_tRepeatInterval;
		nStopCount = m_nRepeatStopByCount[0];
		return TRUE;
	}
	return FALSE;
}
BOOL COOLPrintJobInfo::GetPrintAtTime(CTimeKey &tTime, CTimeSpan &tInterval, CTimeKey &tStopTime) CONST
{
	if ((m_nPrintMode & OOL_PRINT_ATTIME) && (m_nPrintMode & OOL_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & OOL_PRINT_REPEATSTOPBYCOUNT) && (m_nPrintMode & OOL_PRINT_REPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtTime;
		tInterval = m_tRepeatInterval;
		tStopTime = m_tRepeatStopByTime[0];
		return TRUE;
	}
	return FALSE;
}

BOOL COOLPrintJobInfo::SetPrintAtDailyTime(CONST CTimeSpan &tTime)
{
	TIMEKEY  tTimeKey;

	if ((m_nPrintMode & OOL_PRINT_ATDAILYTIME) && !(m_nPrintMode & OOL_PRINT_DAILYREPEATSTOPBYCOUNT) && !(m_nPrintMode & OOL_PRINT_DAILYREPEATSTOPBYTIME))
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
BOOL COOLPrintJobInfo::SetPrintAtDailyTime(CONST CTimeSpan &tTime, UINT nStopCount)
{
	TIMEKEY  tTimeKey;

	if ((m_nPrintMode & OOL_PRINT_ATDAILYTIME) && (m_nPrintMode & OOL_PRINT_DAILYREPEATSTOPBYCOUNT) && !(m_nPrintMode & OOL_PRINT_DAILYREPEATSTOPBYTIME))
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
BOOL COOLPrintJobInfo::SetPrintAtDailyTime(CONST CTimeSpan &tTime, CONST CTimeKey &tStopTime)
{
	TIMEKEY  tTimeKey;

	if ((m_nPrintMode & OOL_PRINT_ATDAILYTIME) && !(m_nPrintMode & OOL_PRINT_DAILYREPEATSTOPBYCOUNT) && (m_nPrintMode & OOL_PRINT_DAILYREPEATSTOPBYTIME))
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

BOOL COOLPrintJobInfo::GetPrintAtDailyTime(CTimeSpan &tTime) CONST
{
	if ((m_nPrintMode & OOL_PRINT_ATDAILYTIME) && !(m_nPrintMode & OOL_PRINT_DAILYREPEATSTOPBYCOUNT) && !(m_nPrintMode & OOL_PRINT_DAILYREPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtDailyTime;
		return TRUE;
	}
	return FALSE;
}
BOOL COOLPrintJobInfo::GetPrintAtDailyTime(CTimeSpan &tTime, UINT &nStopCount) CONST
{
	if ((m_nPrintMode & OOL_PRINT_ATDAILYTIME) && (m_nPrintMode & OOL_PRINT_DAILYREPEATSTOPBYCOUNT) && !(m_nPrintMode & OOL_PRINT_DAILYREPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtDailyTime;
		nStopCount = m_nRepeatStopByCount[1];
		return TRUE;
	}
	return FALSE;
}
BOOL COOLPrintJobInfo::GetPrintAtDailyTime(CTimeSpan &tTime, CTimeKey &tStopTime) CONST
{
	if ((m_nPrintMode & OOL_PRINT_ATDAILYTIME) && !(m_nPrintMode & OOL_PRINT_DAILYREPEATSTOPBYCOUNT) && (m_nPrintMode & OOL_PRINT_DAILYREPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtDailyTime;
		tStopTime = m_tRepeatStopByTime[1];
		return TRUE;
	}
	return FALSE;
}

BOOL COOLPrintJobInfo::SetPrintAtEvent(LPCTSTR pszEvent)
{
	if (m_nPrintMode & OOL_PRINT_ATEVENT)
	{
		m_szEvent = pszEvent;
		return TRUE;
	}
	return FALSE;
}

BOOL COOLPrintJobInfo::GetPrintAtEvent(CString &szEvent) CONST
{
	if (m_nPrintMode & OOL_PRINT_ATEVENT)
	{
		szEvent = m_szEvent;
		return TRUE;
	}
	return FALSE;
}

BOOL COOLPrintJobInfo::SetPrintCount(UINT nCount)
{
	if (m_nPrintMode & OOL_PRINT_ATTIME)
	{
		m_nPrintCount[0] = nCount;
		return TRUE;
	}
	return FALSE;
}

BOOL COOLPrintJobInfo::GetPrintCount(UINT &nCount) CONST
{
	if (m_nPrintMode & OOL_PRINT_ATTIME)
	{
		nCount = m_nPrintCount[0];
		return TRUE;
	}
	return FALSE;
}

BOOL COOLPrintJobInfo::SetPrintDailyCount(UINT nCount)
{
	if (m_nPrintMode & OOL_PRINT_ATDAILYTIME)
	{
		m_nPrintCount[1] = nCount;
		return TRUE;
	}
	return FALSE;
}

BOOL COOLPrintJobInfo::GetPrintDailyCount(UINT &nCount) CONST
{
	if (m_nPrintMode & OOL_PRINT_ATDAILYTIME)
	{
		nCount = m_nPrintCount[1];
		return TRUE;
	}
	return FALSE;
}

BOOL COOLPrintJobInfo::SetPrintLastTime(CONST CTimeKey &tTime)
{
	if (m_nPrintMode & OOL_PRINT_ATTIME)
	{
		m_tPrintLastTime[0] = tTime;
		return TRUE;
	}
	return FALSE;
}

BOOL COOLPrintJobInfo::GetPrintLastTime(CTimeKey &tTime) CONST
{
	if (m_nPrintMode & OOL_PRINT_ATTIME)
	{
		tTime = m_tPrintLastTime[0];
		return TRUE;
	}
	return FALSE;
}

BOOL COOLPrintJobInfo::SetPrintLastDailyTime(CONST CTimeKey &tTime)
{
	if (m_nPrintMode & OOL_PRINT_ATDAILYTIME)
	{
		m_tPrintLastTime[1] = tTime;
		return TRUE;
	}
	return FALSE;
}

BOOL COOLPrintJobInfo::GetPrintLastDailyTime(CTimeKey &tTime) CONST
{
	if (m_nPrintMode & OOL_PRINT_ATDAILYTIME)
	{
		tTime = m_tPrintLastTime[1];
		return TRUE;
	}
	return FALSE;
}

VOID COOLPrintJobInfo::Copy(CONST COOLPrintJobInfo *pJobInfo)
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
	m_tPrintByTime[0] = pJobInfo->m_tPrintByTime[0];
	m_tPrintByTime[1] = pJobInfo->m_tPrintByTime[1];
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

BOOL COOLPrintJobInfo::Compare(CONST COOLPrintJobInfo *pJobInfo) CONST
{
	return((pJobInfo->m_szName == m_szName  &&  pJobInfo->m_szProfile == m_szProfile  &&  pJobInfo->m_szComments == m_szComments  &&  pJobInfo->m_nPrintMode == m_nPrintMode && ((!(m_nPrintMode & OOL_PRINT_FIRSTSIDE) && !(m_nPrintMode & OOL_PRINT_LASTSIDE)) || pJobInfo->m_nPrintByCount == m_nPrintByCount) && (!(m_nPrintMode & OOL_PRINT_BYTIME) || (pJobInfo->m_tPrintByTime[0] == m_tPrintByTime[0] && pJobInfo->m_tPrintByTime[1] == m_tPrintByTime[1])) && (!(m_nPrintMode & OOL_PRINT_ATTIME) || pJobInfo->m_tPrintAtTime == m_tPrintAtTime) && (!(m_nPrintMode & OOL_PRINT_ATDAILYTIME) || pJobInfo->m_tPrintAtDailyTime == m_tPrintAtDailyTime) && (!(m_nPrintMode & OOL_PRINT_ATEVENT) || pJobInfo->m_szEvent == m_szEvent) && (!(m_nPrintMode & OOL_PRINT_REPEATBYINTERVAL) || pJobInfo->m_tRepeatInterval == m_tRepeatInterval) && (!(m_nPrintMode & OOL_PRINT_REPEATSTOPBYCOUNT) || pJobInfo->m_nRepeatStopByCount[0] == m_nRepeatStopByCount[0]) && (!(m_nPrintMode & OOL_PRINT_REPEATSTOPBYTIME) || pJobInfo->m_tRepeatStopByTime[0] == m_tRepeatStopByTime[0]) && (!(m_nPrintMode & OOL_PRINT_DAILYREPEATSTOPBYCOUNT) || pJobInfo->m_nRepeatStopByCount[1] == m_nRepeatStopByCount[1]) && (!(m_nPrintMode & OOL_PRINT_DAILYREPEATSTOPBYTIME) || pJobInfo->m_tRepeatStopByTime[1] == m_tRepeatStopByTime[1])) ? TRUE : FALSE);
}

BOOL COOLPrintJobInfo::Map(CByteArray &nInfo) CONST
{
	INT  cbData;
	DATA  sData;

	sData.cbName = (m_szName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbEvent = (m_szEvent.GetLength() + 1)*sizeof(TCHAR);
	sData.cbProfile = (m_szProfile.GetLength() + 1)*sizeof(TCHAR);
	sData.cbComments = (m_szComments.GetLength() + 1)*sizeof(TCHAR);
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbName + sData.cbProfile + sData.cbComments + sData.cbEvent)), sData.nPrintMode = m_nPrintMode, sData.nPrintCount[0] = m_nPrintCount[0], sData.nPrintCount[1] = m_nPrintCount[1], sData.nPrintByCount = m_nPrintByCount, sData.tPrintByTime[0] = m_tPrintByTime[0].GetTime(), sData.tPrintByTime[1] = m_tPrintByTime[1].GetTime(), sData.tPrintAtTime = m_tPrintAtTime.GetTime(), sData.tPrintAtDailyTime = m_tPrintAtDailyTime.GetTotalSeconds(), sData.tPrintLastTime[0] = m_tPrintLastTime[0].GetTime(), sData.tPrintLastTime[1] = m_tPrintLastTime[1].GetTime(), sData.tRepeatInterval = m_tRepeatInterval.GetTotalSeconds(), sData.nRepeatStopByCount[0] = m_nRepeatStopByCount[0], sData.nRepeatStopByCount[1] = m_nRepeatStopByCount[1], sData.tRepeatStopByTime[0] = m_tRepeatStopByTime[0].GetTime(), sData.tRepeatStopByTime[1] = m_tRepeatStopByTime[1].GetTime(); nInfo.GetSize() == sData.cbSize; )
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

BOOL COOLPrintJobInfo::Unmap(CONST CByteArray &nInfo)
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
		m_tPrintByTime[0] = sData.tPrintByTime[0];
		m_tPrintByTime[1] = sData.tPrintByTime[1];
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
// COOLPrintJobs

COOLPrintJobs::COOLPrintJobs() : CPtrArray()
{
	return;
}

COOLPrintJobs::~COOLPrintJobs()
{
	RemoveAll();
}

INT COOLPrintJobs::Add(COOLPrintJobInfo *pJobInfo)
{
	return((INT)CPtrArray::Add(pJobInfo));
}

INT COOLPrintJobs::Find(LPCTSTR pszName) CONST
{
	INT  nJob;
	INT  nJobs;
	COOLPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (INT)GetSize(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = GetAt(nJob)) && pJobInfo->GetName() == pszName) break;
		continue;
	}
	return((nJob < nJobs) ? nJob : -1);
}

COOLPrintJobInfo *COOLPrintJobs::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (COOLPrintJobInfo *)CPtrArray::GetAt(nIndex) : (COOLPrintJobInfo *)NULL);
}

COOLPrintJobInfo *COOLPrintJobs::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (COOLPrintJobInfo *)CPtrArray::GetAt(nIndex) : (COOLPrintJobInfo *)NULL);
}

TIMEKEY COOLPrintJobs::Schedule()
{
	INT  nJob;
	INT  nJobs;
	UINT  nJobMode;
	UINT  nJobPrintCount[2];
	TIMEKEY  tJobPrintTimeout[2];
	CTimeKey  tJobPrintTime[4];
	CTimeSpan  tJobPrintInterval;
	CTimeSpan  tJobPrintDailyTime;
	COOLPrintJobInfo  *pJobInfo[2];

	for (nJob = 0, nJobs = (INT)GetSize(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo[0] = GetAt(nJob)) != (COOLPrintJobInfo *)NULL)
		{
			if (((nJobMode = pJobInfo[0]->GetPrintMode()) & OOL_PRINT_ACTIVE) && (((nJobMode & OOL_PRINT_ATTIME) && pJobInfo[0]->GetPrintLastTime(tJobPrintTime[1]) && (tJobPrintTime[1] > 0 || pJobInfo[0]->SetPrintLastTime(tJobPrintTime[3]))) || (nJobMode & OOL_PRINT_ATDAILYTIME)) &&
				((pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0]) && pJobInfo[0]->GetPrintCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastTime(tJobPrintTime[1]) && tJobPrintTime[3] >= tJobPrintTime[0] && tJobPrintTime[0] > tJobPrintTime[1] && pJobInfo[0]->SetPrintFlags(OOL_PRINT_ATTIME) && pJobInfo[0]->SetPrintCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0], tJobPrintInterval) && pJobInfo[0]->GetPrintCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastTime(tJobPrintTime[1]) && tJobPrintTime[3] >= tJobPrintTime[0] && (tJobPrintTime[0] > tJobPrintTime[1] || (tJobPrintTime[1].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds() < (tJobPrintTime[3].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds()) && pJobInfo[0]->SetPrintFlags(OOL_PRINT_ATTIME) && pJobInfo[0]->SetPrintCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0], tJobPrintInterval, nJobPrintCount[1]) && pJobInfo[0]->GetPrintCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastTime(tJobPrintTime[1]) && tJobPrintTime[3] >= tJobPrintTime[0] && (tJobPrintTime[0] > tJobPrintTime[1] || (tJobPrintTime[1].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds() < (tJobPrintTime[3].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds()) && nJobPrintCount[0] < nJobPrintCount[1] && pJobInfo[0]->SetPrintFlags(OOL_PRINT_ATTIME) && pJobInfo[0]->SetPrintCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0], tJobPrintInterval, tJobPrintTime[2]) && pJobInfo[0]->GetPrintCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastTime(tJobPrintTime[1]) && tJobPrintTime[3] >= tJobPrintTime[0] && (tJobPrintTime[0] > tJobPrintTime[1] || (tJobPrintTime[1].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds() < (tJobPrintTime[3].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds()) && tJobPrintTime[3] <= tJobPrintTime[2] && pJobInfo[0]->SetPrintFlags(OOL_PRINT_ATTIME) && pJobInfo[0]->SetPrintCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtDailyTime(tJobPrintDailyTime) && pJobInfo[0]->GetPrintDailyCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastDailyTime(tJobPrintTime[1]) && tJobPrintTime[3].GetTime() % SECONDSPERDAY >= tJobPrintDailyTime.GetTotalSeconds() && tJobPrintTime[3].GetTime() / SECONDSPERDAY != tJobPrintTime[1].GetTime() / SECONDSPERDAY  &&  pJobInfo[0]->SetPrintFlags(OOL_PRINT_ATDAILYTIME) && pJobInfo[0]->SetPrintDailyCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastDailyTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtDailyTime(tJobPrintDailyTime, nJobPrintCount[1]) && pJobInfo[0]->GetPrintDailyCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastDailyTime(tJobPrintTime[1]) && tJobPrintTime[3].GetTime() % SECONDSPERDAY >= tJobPrintDailyTime.GetTotalSeconds() && tJobPrintTime[3].GetTime() / SECONDSPERDAY != tJobPrintTime[1].GetTime() / SECONDSPERDAY  &&  nJobPrintCount[0] < nJobPrintCount[1] && pJobInfo[0]->SetPrintFlags(OOL_PRINT_ATDAILYTIME) && pJobInfo[0]->SetPrintDailyCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastDailyTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtDailyTime(tJobPrintDailyTime, tJobPrintTime[2]) && pJobInfo[0]->GetPrintDailyCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastDailyTime(tJobPrintTime[1]) && tJobPrintTime[3].GetTime() % SECONDSPERDAY >= tJobPrintDailyTime.GetTotalSeconds() && tJobPrintTime[3].GetTime() / SECONDSPERDAY != tJobPrintTime[1].GetTime() / SECONDSPERDAY  &&  tJobPrintTime[3] <= tJobPrintTime[2] && pJobInfo[0]->SetPrintFlags(OOL_PRINT_ATDAILYTIME) && pJobInfo[0]->SetPrintDailyCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastDailyTime(tJobPrintTime[3]))))
			{
				if ((pJobInfo[1] = new COOLPrintJobInfo))
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

VOID COOLPrintJobs::RemoveAll()
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

BOOL COOLPrintJobs::Copy(CONST COOLPrintJobs *pPrintJobs)
{
	INT  nJob;
	INT  nJobs;
	COOLPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (INT)pPrintJobs->GetSize(), RemoveAll(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = new COOLPrintJobInfo) != (COOLPrintJobInfo *)NULL)
		{
			pJobInfo->Copy(pPrintJobs->GetAt(nJob));
			InsertAt(nJob, pJobInfo, 1);
			continue;
		}
		break;
	}
	return((nJob == nJobs) ? TRUE : FALSE);
}

BOOL COOLPrintJobs::Compare(CONST COOLPrintJobs *pPrintJobs) CONST
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

BOOL COOLPrintJobs::Map(CByteArray &nInfo) CONST
{
	INT  nJob;
	INT  nJobs;
	CByteArray  nJobData;
	COOLPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (INT)GetSize(), nInfo.RemoveAll(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = GetAt(nJob)) && pJobInfo->Map(nJobData) && nInfo.Append(nJobData) >= 0) continue;
		break;
	}
	return((nJob == nJobs) ? TRUE : FALSE);
}

BOOL COOLPrintJobs::Unmap(CONST CByteArray &nInfo)
{
	INT  cbJob;
	INT  cbJobs;
	CByteArray  nJobData;
	COOLPrintJobInfo  *pJobInfo;

	for (cbJobs = 0, RemoveAll(); cbJobs < nInfo.GetSize(); cbJobs += cbJob)
	{
		for (CopyMemory(&cbJob, nInfo.GetData() + cbJobs, sizeof(cbJob)), nJobData.SetSize(max(min(cbJob, nInfo.GetSize() - cbJobs), 0)); nJobData.GetSize() >= 0; )
		{
			CopyMemory(nJobData.GetData(), nInfo.GetData() + cbJobs, nJobData.GetSize());
			break;
		}
		if ((pJobInfo = new COOLPrintJobInfo))
		{
			if (pJobInfo->Unmap(nJobData) && Add(pJobInfo) >= 0) continue;
			delete pJobInfo;
		}
		break;
	}
	if ((pJobInfo = (!GetSize()) ? new COOLPrintJobInfo : (COOLPrintJobInfo *)NULL))
	{
		for (pJobInfo->SetName(STRING(IDS_PRINTJOB_DEFAULTNAME)), pJobInfo->SetProfile(STRING(IDS_PRINTPROFILE_DEFAULTNAME)), pJobInfo->SetPrintMode(OOL_PRINT_ALL); Add(pJobInfo) >= 0; ) return TRUE;
		delete pJobInfo;
		return FALSE;
	}
	return((cbJobs == nInfo.GetSize()) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// COOLParameterFilter

COOLParameterFilter::COOLParameterFilter() : CObject()
{
	m_nOptions = OOLPARAMETERFILTER_SHOW_ALLTIME | OOLPARAMETERFILTER_BEHAVIOR_AUTOACKNOWLEDGE | OOLPARAMETERFILTER_BEHAVIOR_AUTOSCROLL;
}

VOID COOLParameterFilter::SetTag(LPCTSTR pszTag)
{
	m_szTag = pszTag;
}

CString COOLParameterFilter::GetTag() CONST
{
	return m_szTag;
}

VOID COOLParameterFilter::SetOptions(UINT nOptions)
{
	m_nOptions = nOptions;
}

UINT COOLParameterFilter::GetOptions() CONST
{
	return m_nOptions;
}

BOOL COOLParameterFilter::SetTimeRange(CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime)
{
	if (m_nOptions & OOLPARAMETERFILTER_SHOW_INTERVAL)
	{
		m_tRange[0] = tStartTime;
		m_tRange[1] = tStopTime;
		return TRUE;
	}
	return FALSE;
}

BOOL COOLParameterFilter::GetTimeRange(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	if (m_nOptions & OOLPARAMETERFILTER_SHOW_INTERVAL)
	{
		tStartTime = m_tRange[0];
		tStopTime = m_tRange[1];
		return TRUE;
	}
	return FALSE;
}

BOOL COOLParameterFilter::SetAudition(LPCTSTR pszAudition)
{
	if (m_nOptions & OOLPARAMETERFILTER_ALERT_AUDITION)
	{
		m_szAudition = pszAudition;
		return TRUE;
	}
	return FALSE;
}

CString COOLParameterFilter::GetAudition() CONST
{
	return((m_nOptions & OOLPARAMETERFILTER_ALERT_AUDITION) ? (LPCTSTR)m_szAudition : EMPTYSTRING);
}

BOOL COOLParameterFilter::SetNotification(LPCTSTR pszNotification)
{
	if (m_nOptions & OOLPARAMETERFILTER_ALERT_NOTIFICATION)
	{
		m_szNotification = pszNotification;
		return TRUE;
	}
	return FALSE;
}

CString COOLParameterFilter::GetNotification() CONST
{
	return((m_nOptions & OOLPARAMETERFILTER_ALERT_NOTIFICATION) ? (LPCTSTR)m_szNotification : EMPTYSTRING);
}

VOID COOLParameterFilter::Copy(CONST COOLParameterFilter *pFilter)
{
	m_szTag = pFilter->m_szTag;
	m_szAudition = pFilter->m_szAudition;
	m_szNotification = pFilter->m_szNotification;
	m_tRange[0] = pFilter->m_tRange[0];
	m_tRange[1] = pFilter->m_tRange[1];
	m_nOptions = pFilter->m_nOptions;
}

BOOL COOLParameterFilter::Compare(CONST COOLParameterFilter *pFilter) CONST
{
	return((pFilter->m_szTag == m_szTag  &&  pFilter->m_nOptions == m_nOptions && (!(m_nOptions & OOLPARAMETERFILTER_SHOW_INTERVAL) || (pFilter->m_tRange[0] == m_tRange[0] && pFilter->m_tRange[1] == m_tRange[1])) && (!(m_nOptions & OOLPARAMETERFILTER_ALERT_AUDITION) || pFilter->m_szAudition == m_szAudition) && (!(m_nOptions & OOLPARAMETERFILTER_ALERT_NOTIFICATION) || pFilter->m_szNotification == m_szNotification)) ? TRUE : FALSE);
}

BOOL COOLParameterFilter::Map(CByteArray &nInfo) CONST
{
	INT  cbData;
	DATA  sData;

	sData.cbTag = (m_szTag.GetLength() + 1)*sizeof(TCHAR);
	sData.cbAudition = (m_szAudition.GetLength() + 1)*sizeof(TCHAR);
	sData.cbNotification = (m_szNotification.GetLength() + 1)*sizeof(TCHAR);
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbTag + sData.cbAudition + sData.cbNotification)), sData.nOptions = m_nOptions, sData.tRange[0] = m_tRange[0].GetTime(), sData.tRange[1] = m_tRange[1].GetTime(); nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szTag, sData.cbTag);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbTag), (LPCTSTR)m_szAudition, sData.cbAudition);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbAudition), (LPCTSTR)m_szNotification, sData.cbNotification);
		return TRUE;
	}
	return FALSE;
}

BOOL COOLParameterFilter::Unmap(CONST CByteArray &nInfo)
{
	INT  cbData;
	DATA  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbTag + sData.cbAudition + sData.cbNotification && sData.cbTag > 0 && sData.cbAudition > 0 && sData.cbNotification > 0; )
	{
		CopyMemory(m_szTag.GetBufferSetLength(STRINGCHARS(sData.cbTag)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbTag));
		CopyMemory(m_szAudition.GetBufferSetLength(STRINGCHARS(sData.cbAudition)), nInfo.GetData() + (cbData = cbData + sData.cbTag), STRINGBYTES(sData.cbAudition));
		CopyMemory(m_szNotification.GetBufferSetLength(STRINGCHARS(sData.cbNotification)), nInfo.GetData() + (cbData = cbData + sData.cbAudition), STRINGBYTES(sData.cbNotification));
		m_nOptions = sData.nOptions;
		m_tRange[0] = sData.tRange[0];
		m_tRange[1] = sData.tRange[1];
		m_szTag.ReleaseBuffer();
		m_szAudition.ReleaseBuffer();
		m_szNotification.ReleaseBuffer();
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// COOLParameterFilters

COOLParameterFilters::COOLParameterFilters() : CPtrArray()
{
	return;
}

COOLParameterFilters::~COOLParameterFilters()
{
	RemoveAll();
}

INT COOLParameterFilters::Add(COOLParameterFilter *pFilter)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pFilter->GetTag(), TRUE)) >= 0) InsertAt(nIndex, pFilter, 1);
	return nIndex;
}

INT COOLParameterFilters::Find(LPCTSTR pszTag) CONST
{
	return FindIndex(pszTag);
}

COOLParameterFilter *COOLParameterFilters::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (COOLParameterFilter *)CPtrArray::GetAt(nIndex) : (COOLParameterFilter *)NULL);
}

COOLParameterFilter *COOLParameterFilters::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (COOLParameterFilter *)CPtrArray::GetAt(nIndex) : (COOLParameterFilter *)NULL);
}

VOID COOLParameterFilters::RemoveAll()
{
	INT  nFilter;
	INT  nFilters;

	for (nFilter = 0, nFilters = (INT)GetSize(); nFilter < nFilters; nFilter++)
	{
		delete GetAt(nFilter);
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL COOLParameterFilters::Copy(CONST COOLParameterFilters *pFilters)
{
	INT  nFilter;
	INT  nFilters;
	COOLParameterFilter  *pFilter;

	for (nFilter = 0, nFilters = (INT)pFilters->GetSize(), RemoveAll(); nFilter < nFilters; nFilter++)
	{
		if ((pFilter = new COOLParameterFilter) != (COOLParameterFilter *)NULL)
		{
			pFilter->Copy(pFilters->GetAt(nFilter));
			InsertAt(nFilter, pFilter, 1);
			continue;
		}
		break;
	}
	return((nFilter == nFilters) ? TRUE : FALSE);
}

BOOL COOLParameterFilters::Compare(CONST COOLParameterFilters *pFilters) CONST
{
	INT  nFilter;
	INT  nFilters;

	for (nFilter = 0, nFilters = (pFilters->GetSize() == GetSize()) ? (INT)GetSize() : -1; nFilter < nFilters; nFilter++)
	{
		if (!pFilters->GetAt(nFilter)->Compare(GetAt(nFilter))) break;
		continue;
	}
	return((nFilter == nFilters) ? TRUE : FALSE);
}

BOOL COOLParameterFilters::Map(CByteArray &nInfo) CONST
{
	INT  nFilter;
	INT  nFilters;
	CByteArray  nFilterData;
	COOLParameterFilter  *pFilter;

	for (nFilter = 0, nFilters = (INT)GetSize(), nInfo.RemoveAll(); nFilter < nFilters; nFilter++)
	{
		if ((pFilter = GetAt(nFilter)) && pFilter->Map(nFilterData) && nInfo.Append(nFilterData) >= 0) continue;
		break;
	}
	return((nFilter == nFilters) ? TRUE : FALSE);
}

BOOL COOLParameterFilters::Unmap(CONST CByteArray &nInfo)
{
	INT  cbFilter;
	INT  cbFilters;
	CByteArray  nFilterData;
	COOLParameterFilter  *pFilter;

	for (cbFilters = 0, RemoveAll(); cbFilters < nInfo.GetSize(); cbFilters += cbFilter)
	{
		for (CopyMemory(&cbFilter, nInfo.GetData() + cbFilters, sizeof(cbFilter)), nFilterData.SetSize(max(min(cbFilter, nInfo.GetSize() - cbFilters), 0)); nFilterData.GetSize() >= 0; )
		{
			CopyMemory(nFilterData.GetData(), nInfo.GetData() + cbFilters, nFilterData.GetSize());
			break;
		}
		if ((pFilter = new COOLParameterFilter))
		{
			if (pFilter->Unmap(nFilterData) && Add(pFilter) >= 0) continue;
			delete pFilter;
		}
		break;
	}
	return((cbFilters == nInfo.GetSize()) ? TRUE : FALSE);
}

INT COOLParameterFilters::FindIndex(LPCTSTR pszTag, BOOL bInsert) CONST
{
	INT  nIndex[2];
	INT  nMinIndex;
	INT  nMaxIndex;
	COOLParameterFilter  *pFilter;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex[0] = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex[0] = (nMinIndex + nMaxIndex) / 2)
	{
		nMinIndex = ((pFilter = GetAt(nIndex[0]))) ? ((nIndex[1] = (pFilter->GetTag() <= pszTag)) ? (nIndex[0] + 1) : nMinIndex) : (nIndex[0] = -1);
		nMaxIndex = (nIndex[0] < 0 || !nIndex[1]) ? nIndex[0] : nMaxIndex;
	}
	return((((!bInsert && (pFilter = GetAt((nIndex[0] = max(nIndex[0] - 1, 0)))) && pFilter->GetTag() == pszTag) || (bInsert && (((pFilter = GetAt(max(nIndex[0] - 1, 0))) && pFilter->GetTag() != pszTag && (pFilter = GetAt((INT)min(nIndex[0], GetUpperBound()))) && pFilter->GetTag() != pszTag) || !GetSize()))) && lstrlen(pszTag) > 0) ? nIndex[0] : -1);
}


/////////////////////////////////////////////////////////////////////////////
// COOLSettingsLayoutPage property page

IMPLEMENT_DYNCREATE(COOLSettingsLayoutPage, CLocalePropertyPage)

COOLSettingsLayoutPage::COOLSettingsLayoutPage() : CLocalePropertyPage(COOLSettingsLayoutPage::IDD)
{
	//{{AFX_DATA_INIT(COOLSettingsLayoutPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL COOLSettingsLayoutPage::Initialize()
{
	CString  szLayout;
	COOLOpenDialog  *pDialog;

	if (((pDialog = GetParentDialog()->GetParentDialog()) && (pDialog->GetLayout(szLayout, m_nColumns[0]) || GetParentDisplay()->GetLayout(szLayout, m_nColumns[0])) && (pDialog->GetLayoutTitleFont(&m_fntTitle[0]) || GetParentDisplay()->GetTitleFont(&m_fntTitle[0])) && (pDialog->GetLayoutItemsFont(&m_fntItems[0]) || GetParentDisplay()->GetItemsFont(&m_fntItems[0]))) || (GetParentDisplay()->GetLayout(szLayout, m_nColumns[0]) && GetParentDisplay()->GetTitleFont(&m_fntTitle[0]) && GetParentDisplay()->GetItemsFont(&m_fntItems[0])))
	{
		m_bInvalidData[0] = m_bInvalidData[1] = (!pDialog || !pDialog->GetLayoutInvalidDataMode(m_bInvalidData[0])) ? GetParentDisplay()->IsInvalidDataModeEnabled() : m_bInvalidData[0];
		m_bBadData[0] = m_bBadData[1] = (!pDialog || !pDialog->GetLayoutBadDataMode(m_bBadData[0])) ? GetParentDisplay()->IsBadDataModeEnabled() : m_bBadData[0];
		m_bToolTips[0] = m_bToolTips[1] = (!pDialog || !pDialog->GetLayoutToolTipMode(m_bToolTips[0])) ? GetParentDisplay()->IsToolTipModeEnabled() : m_bToolTips[0];
		CopyMemory(&m_fntTitle[1], &m_fntTitle[0], sizeof(LOGFONT));
		CopyMemory(&m_fntItems[1], &m_fntItems[0], sizeof(LOGFONT));
		m_nColumns[1].Copy(m_nColumns[0]);
		return TRUE;
	}
	return FALSE;
}

BOOL COOLSettingsLayoutPage::GetLayout(CUIntArray &nColumns) CONST
{
	nColumns.Copy(m_nColumns[0]);
	return((nColumns.GetSize() > 0) ? Check(FALSE) : FALSE);
}

BOOL COOLSettingsLayoutPage::GetTitleFont(LPLOGFONT pTitleFont) CONST
{
	CopyMemory(pTitleFont, &m_fntTitle[0], sizeof(LOGFONT));
	return Check(FALSE);
}

BOOL COOLSettingsLayoutPage::GetItemsFont(LPLOGFONT pItemsFont) CONST
{
	CopyMemory(pItemsFont, &m_fntItems[0], sizeof(LOGFONT));
	return Check(FALSE);
}

BOOL COOLSettingsLayoutPage::GetInvalidDataMode(BOOL &bEnable) CONST
{
	bEnable = m_bInvalidData[0];
	return Check(FALSE);
}

BOOL COOLSettingsLayoutPage::GetBadDataMode(BOOL &bEnable) CONST
{
	bEnable = m_bBadData[0];
	return Check(FALSE);
}

BOOL COOLSettingsLayoutPage::GetToolTipMode(BOOL &bEnable) CONST
{
	bEnable = m_bToolTips[0];
	return Check(FALSE);
}

COOLSettingsDialog *COOLSettingsLayoutPage::GetParentDialog() CONST
{
	return((COOLSettingsDialog *)CLocalePropertyPage::GetParent());
}

COOLWnd *COOLSettingsLayoutPage::GetParentDisplay() CONST
{
	return((COOLWnd *)GetParentDialog()->GetParentDisplay());
}

BOOL COOLSettingsLayoutPage::EnumLayoutColumns()
{
	INT  nColumn;
	INT  nColumns;
	CStringArray  szColumns;

	szColumns.Add(LookupColumnName(OOL_TITLEITEM_ID));
	szColumns.Add(LookupColumnName(OOL_TITLEITEM_DESCRIPTION));
	szColumns.Add(LookupColumnName(OOL_TITLEITEM_VALUE));
	szColumns.Add(LookupColumnName(OOL_TITLEITEM_LIMIT));
	szColumns.Add(LookupColumnName(OOL_TITLEITEM_UNIT));
	szColumns.Add(LookupColumnName(OOL_TITLEITEM_OOLTYPE));
	szColumns.Add(LookupColumnName(OOL_TITLEITEM_OOLTIME));
	szColumns.Add(LookupColumnName(OOL_TITLEITEM_OOLUNIT));
	for (nColumn = 0, nColumns = (INT)szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		SendDlgItemMessage(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_NAME, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szColumns.GetAt(nColumn));
		continue;
	}
	SendDlgItemMessage(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_NAME, CB_SETCURSEL);
	return((nColumn == nColumns) ? TRUE : FALSE);
}

BOOL COOLSettingsLayoutPage::ShowLayoutColumns()
{
	INT  nColumn;
	INT  nColumns;

	for (nColumn = 0, nColumns = (INT)m_nColumns[0].GetSize(), SendDlgItemMessage(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_VIEW, LVM_DELETEALLITEMS), m_nColumnIndex = 0; nColumn < nColumns; nColumn++)
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
		if ((!nColumn  &&  !Listview_InsertText(GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_VIEW), 0, EMPTYSTRING)) || (nColumn > 0 && !Listview_SetText(GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_VIEW), 0, nColumn, EMPTYSTRING))) break;
		continue;
	}
	return((nColumn == nColumns) ? SetCurLayoutColumn() : FALSE);
}

VOID COOLSettingsLayoutPage::ShowLayoutFontDetails()
{
	INT  nSize;
	INT  nSizes;
	INT  nStyle;
	INT  nStyles;
	BOOL  bUnderlined;
	CStringArray  szSizes;
	CStringArray  szStyles;
	CFontTools  cFontTools;

	for (SendDlgItemMessage(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_RESETCONTENT), SendDlgItemMessage(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_RESETCONTENT), SendDlgItemMessage(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)((IsDlgButtonChecked(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE)) ? m_fntTitle[0].lfFaceName : m_fntItems[0].lfFaceName))); (IsDlgButtonChecked(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE) && cFontTools.EnumerateFont(m_fntTitle[0].lfFaceName, szStyles, szSizes, bUnderlined)) || (IsDlgButtonChecked(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS) && cFontTools.EnumerateFont(m_fntItems[0].lfFaceName, szStyles, szSizes, bUnderlined)); )
	{
		for (nStyle = 0, nStyles = (INT)szStyles.GetSize(); nStyle < nStyles; nStyle++) SendDlgItemMessage(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szStyles.GetAt(nStyle));
		for (nSize = 0, nSizes = (INT)szSizes.GetSize(); nSize < nSizes; nSize++) SendDlgItemMessage(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szSizes.GetAt(nSize));
		break;
	}
	if (IsDlgButtonChecked(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		SendDlgItemMessage(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_fntTitle[0])), 0));
		SendDlgItemMessage(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntTitle[0])), max(SendDlgItemMessage(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntTitle[1])), 0)));
	}
	if (IsDlgButtonChecked(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS))
	{
		SendDlgItemMessage(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_fntItems[0])), 0));
		SendDlgItemMessage(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntItems[0])), max(SendDlgItemMessage(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntItems[1])), 0)));
	}
	GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_STYLE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_STYLE)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_SIZE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_SIZE)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_SAMPLE)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID COOLSettingsLayoutPage::ShowLayoutFontSample()
{
	CRect  rSampleText;

	GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->GetWindowRect(rSampleText);
	ScreenToClient(rSampleText);
	InvalidateRect(rSampleText);
	UpdateWindow();
}

BOOL COOLSettingsLayoutPage::InsertLayoutColumn(INT nIndex, LPCTSTR pszColumn)
{
	m_szColumns.InsertAt(nIndex, pszColumn);
	m_nColumnIndex = (nIndex <= m_nColumnIndex) ? (INT)min(m_nColumnIndex + 1, m_szColumns.GetSize() - 1) : m_nColumnIndex;
	return Listview_InsertColumn(GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_VIEW), nIndex, m_szColumns.GetAt(nIndex), CalcColumnWidth(pszColumn));
}

BOOL COOLSettingsLayoutPage::ModifyLayoutColumn(INT nIndex, LPCTSTR pszColumn)
{
	m_szColumns.SetAt(nIndex, pszColumn);
	return Listview_SetColumn(GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_VIEW), nIndex, m_szColumns.GetAt(nIndex), CalcColumnWidth(pszColumn));
}

BOOL COOLSettingsLayoutPage::RemoveLayoutColumn(INT nIndex)
{
	if (Listview_DeleteColumn(GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_VIEW), nIndex))
	{
		m_nColumnIndex = (nIndex >= m_nColumnIndex) ? ((nIndex > m_nColumnIndex) ? m_nColumnIndex : 0) : max(m_nColumnIndex - 1, 0);
		m_szColumns.RemoveAt(nIndex);
		return SetCurLayoutColumn(m_nColumnIndex);
	}
	return FALSE;
}

BOOL COOLSettingsLayoutPage::SetCurLayoutColumn(INT nIndex)
{
	if (nIndex < m_nColumns[0].GetSize())
	{
		for (m_szColumns.SetAt(m_nColumnIndex, (m_szColumns.GetAt(m_nColumnIndex).Right(lstrlen(STRING(IDS_OOLSETTINGS_LAYOUTPAGE_COLUMNMARKER))) == STRING(IDS_OOLSETTINGS_LAYOUTPAGE_COLUMNMARKER)) ? (m_szColumns.GetAt(m_nColumnIndex).Left(m_szColumns.GetAt(m_nColumnIndex).GetLength() - lstrlen(STRING(IDS_OOLSETTINGS_LAYOUTPAGE_COLUMNMARKER)))) : m_szColumns.GetAt(m_nColumnIndex)), m_szColumns.SetAt(nIndex, m_szColumns.GetAt(nIndex) + STRING(IDS_OOLSETTINGS_LAYOUTPAGE_COLUMNMARKER)); TRUE; )
		{
			Listview_SetColumn(GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_VIEW), m_nColumnIndex, m_szColumns.GetAt(m_nColumnIndex), CalcColumnWidth(m_szColumns.GetAt(m_nColumnIndex)));
			Listview_SetColumn(GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_VIEW), nIndex, m_szColumns.GetAt(nIndex), CalcColumnWidth(m_szColumns.GetAt((m_nColumnIndex = nIndex))));
			break;
		}
		GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_INSERTBEFORE)->EnableWindow((m_nColumnIndex > 0) ? CheckLayoutColumn() : FALSE);
		GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_INSERTAFTER)->EnableWindow((m_nColumnIndex >= 0) ? CheckLayoutColumn() : FALSE);
		GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_REMOVE)->EnableWindow((m_nColumnIndex > 0) ? TRUE : FALSE);
		return TRUE;
	}
	return FALSE;
}

INT COOLSettingsLayoutPage::GetCurLayoutColumn() CONST
{
	return m_nColumnIndex;
}

BOOL COOLSettingsLayoutPage::CheckLayoutColumn() CONST
{
	INT  nColumn;
	INT  nColumns;
	CString  szColumn;

	GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_NAME)->GetWindowText(szColumn);
	for (nColumn = 0, nColumns = (INT)m_nColumns[0].GetSize(); nColumn < nColumns; nColumn++)
	{
		if (m_nColumns[0].GetAt(nColumn) == LookupColumnName(szColumn)) break;
		continue;
	}
	return((nColumn == nColumns) ? TRUE : FALSE);
}

CString COOLSettingsLayoutPage::LookupColumnName(UINT nColumn) CONST
{
	if (nColumn == OOL_TITLEITEM_ID) return STRING(IDS_OOL_TITLEITEM_ID);
	if (nColumn == OOL_TITLEITEM_DESCRIPTION) return STRING(IDS_OOL_TITLEITEM_DESCRIPTION);
	if (nColumn == OOL_TITLEITEM_VALUE) return STRING(IDS_OOL_TITLEITEM_VALUE);
	if (nColumn == OOL_TITLEITEM_LIMIT) return STRING(IDS_OOL_TITLEITEM_LIMIT);
	if (nColumn == OOL_TITLEITEM_UNIT) return STRING(IDS_OOL_TITLEITEM_UNIT);
	if (nColumn == OOL_TITLEITEM_OOLTYPE) return STRING(IDS_OOL_TITLEITEM_OOLTYPE);
	if (nColumn == OOL_TITLEITEM_OOLTIME) return STRING(IDS_OOL_TITLEITEM_OOLTIME);
	if (nColumn == OOL_TITLEITEM_OOLUNIT) return STRING(IDS_OOL_TITLEITEM_OOLUNIT);
	return EMPTYSTRING;
}
UINT COOLSettingsLayoutPage::LookupColumnName(LPCTSTR pszColumn) CONST
{
	if (!_tcsncmp(pszColumn, STRING(IDS_OOL_TITLEITEM_ID), lstrlen(STRING(IDS_OOL_TITLEITEM_ID)))) return OOL_TITLEITEM_ID;
	if (!_tcsncmp(pszColumn, STRING(IDS_OOL_TITLEITEM_DESCRIPTION), lstrlen(STRING(IDS_OOL_TITLEITEM_DESCRIPTION)))) return OOL_TITLEITEM_DESCRIPTION;
	if (!_tcsncmp(pszColumn, STRING(IDS_OOL_TITLEITEM_VALUE), lstrlen(STRING(IDS_OOL_TITLEITEM_VALUE)))) return OOL_TITLEITEM_VALUE;
	if (!_tcsncmp(pszColumn, STRING(IDS_OOL_TITLEITEM_LIMIT), lstrlen(STRING(IDS_OOL_TITLEITEM_LIMIT)))) return OOL_TITLEITEM_LIMIT;
	if (!_tcsncmp(pszColumn, STRING(IDS_OOL_TITLEITEM_UNIT), lstrlen(STRING(IDS_OOL_TITLEITEM_UNIT)))) return OOL_TITLEITEM_UNIT;
	if (!_tcsncmp(pszColumn, STRING(IDS_OOL_TITLEITEM_OOLTYPE), lstrlen(STRING(IDS_OOL_TITLEITEM_OOLTYPE)))) return OOL_TITLEITEM_OOLTYPE;
	if (!_tcsncmp(pszColumn, STRING(IDS_OOL_TITLEITEM_OOLTIME), lstrlen(STRING(IDS_OOL_TITLEITEM_OOLTIME)))) return OOL_TITLEITEM_OOLTIME;
	if (!_tcsncmp(pszColumn, STRING(IDS_OOL_TITLEITEM_OOLUNIT), lstrlen(STRING(IDS_OOL_TITLEITEM_OOLUNIT)))) return OOL_TITLEITEM_OOLUNIT;
	return 0;
}

INT COOLSettingsLayoutPage::CalcColumnsWidth(CONST CUIntArray &nColumns, CUIntArray &nWidths)
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

INT COOLSettingsLayoutPage::CalcColumnWidth(LPCTSTR pszColumn)
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
				nWidth = ((nColumn = LookupColumnName(pszColumn)) == OOL_TITLEITEM_ID) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetOOLIDColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : 0;
				nWidth = (nColumn == OOL_TITLEITEM_DESCRIPTION) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetOOLDescriptionColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == OOL_TITLEITEM_VALUE) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetOOLValueColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == OOL_TITLEITEM_LIMIT) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetOOLLimitColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == OOL_TITLEITEM_UNIT) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetOOLUnitColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == OOL_TITLEITEM_OOLTYPE) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetOOLTypeColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == OOL_TITLEITEM_OOLTIME) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetOOLTMTimeColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == OOL_TITLEITEM_OOLUNIT) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetOOLTMUnitColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
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

INT COOLSettingsLayoutPage::CalcColumnIndent() CONST
{
	return 3 * GetSystemMetrics(SM_CXEDGE);
}

BOOL COOLSettingsLayoutPage::IsModified(BOOL bAll) CONST
{
	INT  nColumn;
	INT  nColumns;
	CFontTools  cFontTools;

	if (IsWindow(GetSafeHwnd()) && !bAll)
	{
		for (nColumn = 0, nColumns = (m_nColumns[0].GetSize() == m_nColumns[1].GetSize() && !lstrcmp(m_fntTitle[0].lfFaceName, m_fntTitle[1].lfFaceName) && (m_fntTitle[0].lfHeight == m_fntTitle[1].lfHeight || cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntTitle[0])) == cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntTitle[1]))) && m_fntTitle[0].lfWeight == m_fntTitle[1].lfWeight && m_fntTitle[0].lfItalic == m_fntTitle[1].lfItalic && !lstrcmp(m_fntItems[0].lfFaceName, m_fntItems[1].lfFaceName) && (m_fntItems[0].lfHeight == m_fntItems[1].lfHeight || cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntItems[0])) == cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntItems[1]))) && m_fntItems[0].lfWeight == m_fntItems[1].lfWeight && m_fntItems[0].lfItalic == m_fntItems[1].lfItalic && m_bInvalidData[0] == m_bInvalidData[1] && m_bBadData[0] == m_bBadData[1] && m_bToolTips[0] == m_bToolTips[1]) ? (INT)m_nColumns[0].GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			if (m_nColumns[0].GetAt(nColumn) != m_nColumns[1].GetAt(nColumn)) break;
			continue;
		}
		return((nColumn != nColumns) ? TRUE : FALSE);
	}
	return((bAll) ? CLocalePropertyPage::IsModified() : FALSE);
}

BOOL COOLSettingsLayoutPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_NAMES)->GetWindowTextLength() > 0 && GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowTextLength() > 0 && GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowTextLength() > 0) : CLocalePropertyPage::Check()) : TRUE);
}

void COOLSettingsLayoutPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COOLSettingsLayoutPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void COOLSettingsLayoutPage::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_nColumns[0].RemoveAll();
	m_nColumns[1].RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(COOLSettingsLayoutPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(COOLSettingsLayoutPage)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_INSERTBEFORE, OnInsertColumnBefore)
	ON_BN_CLICKED(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_INSERTAFTER, OnInsertColumnAfter)
	ON_BN_CLICKED(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_REMOVE, OnRemoveColumn)
	ON_BN_CLICKED(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_INVALIDDATA, OnInvalidData)
	ON_BN_CLICKED(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_BADDATA, OnBadData)
	ON_BN_CLICKED(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_TOOLTIPS, OnToolTips)
	ON_BN_CLICKED(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE, OnTitleFont)
	ON_BN_CLICKED(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS, OnItemsFont)
	ON_CBN_EDITCHANGE(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_NAMES, OnEditchangeFontName)
	ON_CBN_SELCHANGE(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_NAME, OnSelchangeColumnName)
	ON_CBN_SELCHANGE(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_NAMES, OnSelchangeFontName)
	ON_CBN_SELCHANGE(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_STYLE, OnSelchangeFontStyle)
	ON_CBN_SELCHANGE(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_SIZE, OnSelchangeFontSize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COOLSettingsLayoutPage message handlers

BOOL COOLSettingsLayoutPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	CheckRadioButton(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE, IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS, IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE);
	CheckDlgButton(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_INVALIDDATA, m_bInvalidData[0]);
	CheckDlgButton(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_BADDATA, m_bBadData[0]);
	CheckDlgButton(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_TOOLTIPS, m_bToolTips[0]);
	GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->GetWindowText(m_szFontSampleText);
	GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT)->EnableWindow();
	GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_NAME)->EnableWindow();
	GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_VIEW)->EnableWindow();
	GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_SHOWDATA)->EnableWindow();
	GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_INVALIDDATA)->EnableWindow();
	GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_BADDATA)->EnableWindow();
	GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_TOOLTIPS)->EnableWindow();
	GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS)->EnableWindow();
	GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_LOCATION_STATIC)->EnableWindow();
	GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE)->EnableWindow();
	GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS)->EnableWindow();
	GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_CHARACTERISTICS)->EnableWindow();
	GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_NAMES_STATIC)->EnableWindow();
	GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_NAMES)->EnableWindow();
	SendDlgItemMessage(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_NAMES, FCB_DIR, CF_EFFECTS | CF_SCREENFONTS);
	SendDlgItemMessage(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)m_fntTitle[0].lfFaceName));
	EnumLayoutColumns();
	ShowLayoutColumns();
	ShowLayoutFontDetails();
	return TRUE;
}

void COOLSettingsLayoutPage::OnPaint()
{
	INT  nBkMode;
	CFont  cFont;
	CFont  *pOldFont;
	CRect  rSampleText;
	COLORREF  nOldColor;
	CPaintDC  cDC(this);

	for (GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->GetWindowRect(rSampleText), ScreenToClient(rSampleText); cFont.CreateFontIndirect((IsDlgButtonChecked(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE)) ? &m_fntTitle[0] : &m_fntItems[0]); )
	{
		if ((pOldFont = cDC.SelectObject(&cFont)))
		{
			nBkMode = cDC.SetBkMode(TRANSPARENT);
			nOldColor = cDC.SetTextColor((SendDlgItemMessage(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? GetSysColor(COLOR_WINDOWTEXT) : GetSysColor(COLOR_GRAYTEXT));
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

BOOL COOLSettingsLayoutPage::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMLISTVIEW  *pNotifyInfo = (NMLISTVIEW *)lParam;

	if (pNotifyInfo->hdr.idFrom == IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_VIEW)
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

void COOLSettingsLayoutPage::OnInsertColumnBefore()
{
	INT  nIndex;
	CString  szColumn;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_NAME)->GetWindowText(szColumn); InsertLayoutColumn((nIndex = m_nColumnIndex), szColumn); )
	{
		m_nColumns[0].InsertAt(nIndex, LookupColumnName(szColumn));
		SetCurLayoutColumn(nIndex);
		break;
	}
	GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsLayoutPage::OnInsertColumnAfter()
{
	INT  nIndex;
	CString  szColumn;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_NAME)->GetWindowText(szColumn); InsertLayoutColumn((nIndex = m_nColumnIndex + 1), szColumn); )
	{
		m_nColumns[0].InsertAt(nIndex, LookupColumnName(szColumn));
		SetCurLayoutColumn(nIndex);
		break;
	}
	GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsLayoutPage::OnRemoveColumn()
{
	INT  nIndex;
	CHourglassCursor  cCursor;

	if (RemoveLayoutColumn((nIndex = m_nColumnIndex)))
	{
		m_nColumns[0].RemoveAt(nIndex);
		SetCurLayoutColumn();
	}
	GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsLayoutPage::OnInvalidData()
{
	m_bInvalidData[0] = IsDlgButtonChecked(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_INVALIDDATA);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsLayoutPage::OnBadData()
{
	m_bBadData[0] = IsDlgButtonChecked(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_BADDATA);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsLayoutPage::OnToolTips()
{
	m_bToolTips[0] = IsDlgButtonChecked(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_TOOLTIPS);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsLayoutPage::OnTitleFont()
{
	ShowLayoutFontDetails();
	ShowLayoutFontSample();
}

void COOLSettingsLayoutPage::OnItemsFont()
{
	ShowLayoutFontDetails();
	ShowLayoutFontSample();
}

void COOLSettingsLayoutPage::OnEditchangeFontName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsLayoutPage::OnSelchangeColumnName()
{
	GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_INSERTBEFORE)->EnableWindow((m_nColumnIndex > 0) ? CheckLayoutColumn() : FALSE);
	GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_INSERTAFTER)->EnableWindow((m_nColumnIndex >= 0) ? CheckLayoutColumn() : FALSE);
	GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FORMAT_REMOVE)->EnableWindow((m_nColumnIndex > 0) ? TRUE : FALSE);
}

void COOLSettingsLayoutPage::OnSelchangeFontName()
{
	CString  szSize;
	CString  szStyle;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		_tcscpy_s(m_fntTitle[0].lfFaceName, sizeof(m_fntTitle[0].lfFaceName) / sizeof(TCHAR), Combobox_GetText(GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_NAMES), (INT)SendDlgItemMessage(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_GETCURSEL)));
		ShowLayoutFontDetails();
	}
	if (IsDlgButtonChecked(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS))
	{
		_tcscpy_s(m_fntItems[0].lfFaceName, sizeof(m_fntItems[0].lfFaceName) / sizeof(TCHAR), Combobox_GetText(GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_NAMES), (INT)SendDlgItemMessage(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_GETCURSEL)));
		ShowLayoutFontDetails();
	}
	if (IsDlgButtonChecked(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntTitle[0].lfWeight, m_fntTitle[0].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_fntTitle[0].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_fntTitle[0]);
	}
	if (IsDlgButtonChecked(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS))
	{
		GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntItems[0].lfWeight, m_fntItems[0].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_fntItems[0].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_fntItems[0]);
	}
	ShowLayoutFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsLayoutPage::OnSelchangeFontStyle()
{
	CString  szStyle;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntTitle[0].lfWeight, m_fntTitle[0].lfItalic);
	}
	if (IsDlgButtonChecked(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS))
	{
		GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntItems[0].lfWeight, m_fntItems[0].lfItalic);
	}
	ShowLayoutFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsLayoutPage::OnSelchangeFontSize()
{
	CString  szSize;
	CFontTools  cFontTools;

	if (IsDlgButtonChecked(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_LOCATION_TITLE))
	{
		GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_fntTitle[0].lfHeight);
	}
	if (IsDlgButtonChecked(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_LOCATION_ITEMS))
	{
		GetDlgItem(IDC_OOLSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_fntItems[0].lfHeight);
	}
	ShowLayoutFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// COOLSettingsFilteringPage property page

IMPLEMENT_DYNCREATE(COOLSettingsFilteringPage, CLocalePropertyPage)

COOLSettingsFilteringPage::COOLSettingsFilteringPage() : CLocalePropertyPage(COOLSettingsFilteringPage::IDD)
{
	//{{AFX_DATA_INIT(COOLSettingsFilteringPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL COOLSettingsFilteringPage::Initialize()
{
	COOLOpenDialog  *pDialog;

	if (((pDialog = GetParentDialog()->GetParentDialog()) && (pDialog->GetParameterFilters(m_pFilters[0]) || GetParentDisplay()->GetParameterFilters(m_pFilters[0])) && (pDialog->GetFilterColors(m_nColors[0]) || GetParentDisplay()->GetFilterColors(m_nColors[0]))) || (GetParentDisplay()->GetParameterFilters(m_pFilters[0]) && GetParentDisplay()->GetFilterColors(m_nColors[0])))
	{
		m_pFilters[1].Copy(&m_pFilters[0]);
		m_nColors[1].Copy(m_nColors[0]);
		return TRUE;
	}
	return FALSE;
}

BOOL COOLSettingsFilteringPage::GetFilters(COOLParameterFilters &pFilters) CONST
{
	return((pFilters.Copy(&m_pFilters[0])) ? Check(FALSE) : FALSE);
}

BOOL COOLSettingsFilteringPage::GetColors(CUIntArray &nColors) CONST
{
	nColors.Copy(m_nColors[0]);
	return Check(FALSE);
}

COOLSettingsDialog *COOLSettingsFilteringPage::GetParentDialog() CONST
{
	return((COOLSettingsDialog *)CLocalePropertyPage::GetParent());
}

COOLWnd *COOLSettingsFilteringPage::GetParentDisplay() CONST
{
	return((COOLWnd *)GetParentDialog()->GetParentDisplay());
}

BOOL COOLSettingsFilteringPage::EnumParameters()
{
	INT  nParameter;
	INT  nParameters;
	CString  szParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETER, CB_RESETCONTENT);
	SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETER, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_OOLSETTINGS_FILTERINGPAGE_PARAMETERSFLAG));
	for (nParameter = 0, nParameters = (INT)GetDatabase()->GetTMParameters()->GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(nParameter)) != (CDatabaseTMParameter *)NULL)
		{
			szParameter.Format(STRING(IDS_OOLSETTINGS_FILTERINGPAGE_PARAMETERSFORMAT), (LPCTSTR)pDatabaseTMParameter->GetTag(), (LPCTSTR)pDatabaseTMParameter->GetDescription());
			SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETER, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szParameter);
		}
	}
	return((SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETER, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

BOOL COOLSettingsFilteringPage::EnumFilters()
{
	INT  nFilter;
	INT  nFilters;
	CString  szFilter;
	COOLParameterFilter  *pFilter;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETERS, LB_RESETCONTENT);
	for (nFilter = 0, nFilters = (INT)m_pFilters[0].GetSize(); nFilter < nFilters; nFilter++)
	{
		if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(m_pFilters[0].GetAt(nFilter)->GetTag()))))
		{
			szFilter.Format(STRING(IDS_OOLSETTINGS_FILTERINGPAGE_PARAMETERSFORMAT), (LPCTSTR)pDatabaseTMParameter->GetTag(), (LPCTSTR)pDatabaseTMParameter->GetDescription());
			SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETERS, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szFilter);
		}
		if ((pFilter = m_pFilters[0].GetAt(nFilter)) && pFilter->GetTag() == STRING(IDS_OOLSETTINGS_FILTERINGPAGE_PARAMETERSFLAG))
		{
			SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETERS, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_OOLSETTINGS_FILTERINGPAGE_PARAMETERSFLAG));
			continue;
		}
	}
	return((SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETERS, LB_GETCOUNT) >= 0) ? TRUE : FALSE);
}

BOOL COOLSettingsFilteringPage::EnumAuditions()
{
	INT  nProfile;
	INT  nProfiles;
	CStringArray  szProfiles;

	SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_AUDITION, CB_RESETCONTENT);
	for (nProfile = 0, nProfiles = (EnumAuditionProfiles(szProfiles)) ? (INT)szProfiles.GetSize() : 0; nProfile < nProfiles; nProfile++)
	{
		SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_AUDITION, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szProfiles.GetAt(nProfile));
		continue;
	}
	SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_AUDITION, CB_INSERTSTRING, 0, (LPARAM)STRING(IDS_OOLSETTINGS_FILTERINGPAGE_NOAUDITION));
	return((SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_AUDITION, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

BOOL COOLSettingsFilteringPage::EnumNotifications()
{
	INT  nProfile;
	INT  nProfiles;
	CNotificationProfiles  pProfiles;
	CNotificationProfileInfo  *pProfileInfo;

	SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_NOTIFICATION, CB_RESETCONTENT);
	SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_NOTIFICATION, CB_INSERTSTRING, 0, (LPARAM)STRING(IDS_OOLSETTINGS_FILTERINGPAGE_NONOTIFICATION));
	for (nProfile = 0, nProfiles = (GetNotificationProfiles(pProfiles)) ? (INT)pProfiles.GetSize() : 0; nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo = (CNotificationProfileInfo *)pProfiles.GetAt(nProfile)) != (CNotificationProfileInfo *)NULL)
		{
			SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_NOTIFICATION, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)pProfileInfo->GetName());
			continue;
		}
	}
	return((SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_NOTIFICATION, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

BOOL COOLSettingsFilteringPage::EnumStatusColors()
{
	return((SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_COLORS_STATUS, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_OOLSETTINGS_FILTERINGPAGE_SOFTOOL)) >= 0 && SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_COLORS_STATUS, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_OOLSETTINGS_FILTERINGPAGE_HARDOOL)) >= 0 && SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_COLORS_STATUS, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_OOLSETTINGS_FILTERINGPAGE_DELTAOOL)) >= 0 && SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_COLORS_STATUS, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_OOLSETTINGS_FILTERINGPAGE_CONSISTENCYOOL)) >= 0) ? TRUE : FALSE);
}

VOID COOLSettingsFilteringPage::SetFilterInfo()
{
	UINT  nType;
	CTimeKey  tTimeKey;
	CTimeKey  tRange[2];
	COOLParameterFilter  *pFilter;

	if ((pFilter = FindFilter()))
	{
		CheckDlgButton(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_ALLTIME, (pFilter->GetOptions() & OOLPARAMETERFILTER_SHOW_ALLTIME) ? TRUE : FALSE);
		CheckDlgButton(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_NEVER, (pFilter->GetOptions() & OOLPARAMETERFILTER_SHOW_NEVER) ? TRUE : FALSE);
		CheckDlgButton(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALTIME, (pFilter->GetOptions() & OOLPARAMETERFILTER_SHOW_INTERVAL) ? TRUE : FALSE);
		CheckDlgButton(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_ALERTASEVENT, ((nType = (GetParentDialog()->GetParentDialog()) ? GetParentDialog()->GetParentDialog()->GetType() : HIWORD(GetParentDisplay()->GetType())) == OOL_TYPE_GLOBAL && (pFilter->GetOptions() & OOLPARAMETERFILTER_BEHAVIOR_EVENT)) ? TRUE : FALSE);
		CheckDlgButton(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_BRINGTOTOP, ((pFilter->GetOptions() & OOLPARAMETERFILTER_BEHAVIOR_BRINGTOTOP) && nType == OOL_TYPE_GLOBAL) ? TRUE : FALSE);
		CheckDlgButton(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOACKNOWLEDGE, (pFilter->GetOptions() & OOLPARAMETERFILTER_BEHAVIOR_AUTOACKNOWLEDGE) ? TRUE : FALSE);
		CheckDlgButton(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_INLIMIT, ((pFilter->GetOptions() & OOLPARAMETERFILTER_BEHAVIOR_INLIMIT) && nType == OOL_TYPE_GLOBAL) ? TRUE : FALSE);
		CheckDlgButton(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_FLASH, (pFilter->GetOptions() & OOLPARAMETERFILTER_BEHAVIOR_FLASH) ? TRUE : FALSE);
		CheckDlgButton(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOSCROLL, (pFilter->GetOptions() & OOLPARAMETERFILTER_BEHAVIOR_AUTOSCROLL) ? TRUE : FALSE);
		Timespinbox_SetTime(GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALSTARTTIME), (pFilter->GetTimeRange(tRange[0], tRange[1])) ? tRange[0] : tTimeKey);
		Timespinbox_SetTime(GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALSTOPTIME), (pFilter->GetTimeRange(tRange[0], tRange[1])) ? tRange[1] : tTimeKey);
		SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_AUDITION, CB_SETCURSEL, (nType == OOL_TYPE_GLOBAL) ? (WPARAM)max(SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_AUDITION, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pFilter->GetAudition()), 0) : (WPARAM)-1);
		SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_NOTIFICATION, CB_SETCURSEL, (nType == OOL_TYPE_GLOBAL) ? (WPARAM)max(SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_NOTIFICATION, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pFilter->GetNotification()), 0) : (WPARAM)-1);
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_OPTIONS)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_ALLTIME)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_NEVER)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALTIME)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALSTARTTIME)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALTIME));
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALTIME));
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALSTOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALTIME));
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_ALERTASEVENT)->EnableWindow((nType == OOL_TYPE_GLOBAL) ? TRUE : FALSE);
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_BRINGTOTOP)->EnableWindow((nType == OOL_TYPE_GLOBAL) ? TRUE : FALSE);
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOACKNOWLEDGE)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_INLIMIT)->EnableWindow((nType == OOL_TYPE_GLOBAL) ? TRUE : FALSE);
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_FLASH)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOSCROLL)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_AUDITION_STATIC)->EnableWindow((nType == OOL_TYPE_GLOBAL) ? TRUE : FALSE);
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_AUDITION)->EnableWindow((nType == OOL_TYPE_GLOBAL) ? TRUE : FALSE);
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_NOTIFICATION_STATIC)->EnableWindow((nType == OOL_TYPE_GLOBAL) ? TRUE : FALSE);
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_NOTIFICATION)->EnableWindow((nType == OOL_TYPE_GLOBAL) ? TRUE : FALSE);
		return;
	}
	if ((pFilter = new COOLParameterFilter))
	{
		CheckDlgButton(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_ALLTIME, (pFilter->GetOptions() & OOLPARAMETERFILTER_SHOW_ALLTIME) ? TRUE : FALSE);
		CheckDlgButton(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_NEVER, (pFilter->GetOptions() & OOLPARAMETERFILTER_SHOW_NEVER) ? TRUE : FALSE);
		CheckDlgButton(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALTIME, (pFilter->GetOptions() & OOLPARAMETERFILTER_SHOW_INTERVAL) ? TRUE : FALSE);
		CheckDlgButton(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_ALERTASEVENT, ((nType = (GetParentDialog()->GetParentDialog()) ? GetParentDialog()->GetParentDialog()->GetType() : HIWORD(GetParentDisplay()->GetType())) == OOL_TYPE_GLOBAL  &&  pFilter->GetOptions() & OOLPARAMETERFILTER_BEHAVIOR_EVENT) ? TRUE : FALSE);
		CheckDlgButton(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_BRINGTOTOP, ((pFilter->GetOptions() & OOLPARAMETERFILTER_BEHAVIOR_BRINGTOTOP) && nType == OOL_TYPE_GLOBAL) ? TRUE : FALSE);
		CheckDlgButton(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOACKNOWLEDGE, (pFilter->GetOptions() & OOLPARAMETERFILTER_BEHAVIOR_AUTOACKNOWLEDGE) ? TRUE : FALSE);
		CheckDlgButton(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_INLIMIT, ((pFilter->GetOptions() & OOLPARAMETERFILTER_BEHAVIOR_INLIMIT) && nType == OOL_TYPE_GLOBAL) ? TRUE : FALSE);
		CheckDlgButton(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_FLASH, (pFilter->GetOptions() & OOLPARAMETERFILTER_BEHAVIOR_FLASH) ? TRUE : FALSE);
		CheckDlgButton(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOSCROLL, (pFilter->GetOptions() & OOLPARAMETERFILTER_BEHAVIOR_AUTOSCROLL) ? TRUE : FALSE);
		Timespinbox_SetTime(GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALSTARTTIME), (pFilter->GetTimeRange(tRange[0], tRange[1])) ? tRange[0] : tTimeKey);
		Timespinbox_SetTime(GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALSTOPTIME), (pFilter->GetTimeRange(tRange[0], tRange[1])) ? tRange[1] : tTimeKey);
		SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_AUDITION, CB_SETCURSEL, (nType == OOL_TYPE_GLOBAL) ? (WPARAM)max(SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_AUDITION, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pFilter->GetAudition()), 0) : (WPARAM)-1);
		SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_NOTIFICATION, CB_SETCURSEL, (nType == OOL_TYPE_GLOBAL) ? (WPARAM)max(SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_NOTIFICATION, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pFilter->GetNotification()), 0) : (WPARAM)-1);
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_OPTIONS)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_ALLTIME)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_NEVER)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALTIME)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALSTARTTIME)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALTIME));
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALTIME));
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALSTOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALTIME));
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_ALERTASEVENT)->EnableWindow((nType == OOL_TYPE_GLOBAL) ? TRUE : FALSE);
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_BRINGTOTOP)->EnableWindow((nType == OOL_TYPE_GLOBAL) ? TRUE : FALSE);
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOACKNOWLEDGE)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_INLIMIT)->EnableWindow((nType == OOL_TYPE_GLOBAL) ? TRUE : FALSE);
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_FLASH)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOSCROLL)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_AUDITION_STATIC)->EnableWindow((nType == OOL_TYPE_GLOBAL) ? TRUE : FALSE);
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_AUDITION)->EnableWindow((nType == OOL_TYPE_GLOBAL) ? TRUE : FALSE);
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_NOTIFICATION_STATIC)->EnableWindow((nType == OOL_TYPE_GLOBAL) ? TRUE : FALSE);
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_NOTIFICATION)->EnableWindow((nType == OOL_TYPE_GLOBAL) ? TRUE : FALSE);
		delete pFilter;
		return;
	}
	CheckDlgButton(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_ALLTIME, FALSE);
	CheckDlgButton(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_NEVER, FALSE);
	CheckDlgButton(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALTIME, FALSE);
	CheckDlgButton(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_ALERTASEVENT, FALSE);
	CheckDlgButton(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_BRINGTOTOP, FALSE);
	CheckDlgButton(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOACKNOWLEDGE, FALSE);
	CheckDlgButton(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_INLIMIT, FALSE);
	CheckDlgButton(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_FLASH, FALSE);
	CheckDlgButton(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOSCROLL, FALSE);
	SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_AUDITION, CB_SETCURSEL, (WPARAM)-1);
	SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_NOTIFICATION, CB_SETCURSEL, (WPARAM)-1);
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_OPTIONS)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_ALLTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_NEVER)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALSTARTTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALSTOPTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_ALERTASEVENT)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_BRINGTOTOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOACKNOWLEDGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_INLIMIT)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_FLASH)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOSCROLL)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_AUDITION_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_AUDITION)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_NOTIFICATION_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_NOTIFICATION)->EnableWindow(FALSE);
}

VOID COOLSettingsFilteringPage::GetFilterInfo(COOLParameterFilter *pFilter) CONST
{
	UINT  nOptions;
	CString  szFilter;
	CString  szAudition;
	CString  szNotification;
	CTimeKey  tRange[2];

	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETER)->GetWindowText(szFilter);
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_AUDITION)->GetWindowText(szAudition);
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_NOTIFICATION)->GetWindowText(szNotification);
	nOptions = (IsDlgButtonChecked(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_ALLTIME)) ? OOLPARAMETERFILTER_SHOW_ALLTIME : 0;
	nOptions |= (IsDlgButtonChecked(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_NEVER)) ? OOLPARAMETERFILTER_SHOW_NEVER : 0;
	nOptions |= (IsDlgButtonChecked(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALTIME)) ? OOLPARAMETERFILTER_SHOW_INTERVAL : 0;
	nOptions |= (IsDlgButtonChecked(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_ALERTASEVENT)) ? OOLPARAMETERFILTER_BEHAVIOR_EVENT : 0;
	nOptions |= (IsDlgButtonChecked(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_BRINGTOTOP)) ? OOLPARAMETERFILTER_BEHAVIOR_BRINGTOTOP : 0;
	nOptions |= (IsDlgButtonChecked(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOACKNOWLEDGE)) ? OOLPARAMETERFILTER_BEHAVIOR_AUTOACKNOWLEDGE : 0;
	nOptions |= (IsDlgButtonChecked(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_INLIMIT)) ? OOLPARAMETERFILTER_BEHAVIOR_INLIMIT : 0;
	nOptions |= (IsDlgButtonChecked(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_FLASH)) ? OOLPARAMETERFILTER_BEHAVIOR_FLASH : 0;
	nOptions |= (IsDlgButtonChecked(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOSCROLL)) ? OOLPARAMETERFILTER_BEHAVIOR_AUTOSCROLL : 0;
	nOptions |= (szAudition != STRING(IDS_OOLSETTINGS_FILTERINGPAGE_NOAUDITION) && !szAudition.IsEmpty()) ? OOLPARAMETERFILTER_ALERT_AUDITION : 0;
	nOptions |= (szNotification != STRING(IDS_OOLSETTINGS_FILTERINGPAGE_NONOTIFICATION) && !szNotification.IsEmpty()) ? OOLPARAMETERFILTER_ALERT_NOTIFICATION : 0;
	szFilter = (szFilter != STRING(IDS_OOLSETTINGS_FILTERINGPAGE_PARAMETERSFLAG) && szFilter.Find(SPACE) >= 0) ? szFilter.Left(szFilter.Find(SPACE)) : szFilter;
	tRange[0] = Timespinbox_GetTime(GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALSTARTTIME));
	tRange[1] = Timespinbox_GetTime(GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALSTOPTIME));
	pFilter->SetTag(szFilter);
	pFilter->SetOptions(nOptions);
	pFilter->SetAudition(szAudition);
	pFilter->SetNotification(szNotification);
	pFilter->SetTimeRange(tRange[0], tRange[1]);
}

COOLParameterFilter *COOLSettingsFilteringPage::FindFilter() CONST
{
	INT  nIndex;

	return(((nIndex = (INT)GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETERS)->SendMessage(LB_GETCURSEL)) >= 0 && nIndex < m_pFilters[0].GetSize()) ? m_pFilters[0].GetAt(nIndex) : (COOLParameterFilter *)NULL);
}

BOOL COOLSettingsFilteringPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (!m_pFilters[0].Compare(&m_pFilters[1]) || memcmp(m_nColors[0].GetData(), m_nColors[1].GetData(), min(m_nColors[0].GetSize(), m_nColors[1].GetSize())*sizeof(UINT))) : CLocalePropertyPage::IsModified()) : FALSE);
}

BOOL COOLSettingsFilteringPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? TRUE : CLocalePropertyPage::Check()) : TRUE);
}

void COOLSettingsFilteringPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COOLSettingsFilteringPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void COOLSettingsFilteringPage::PostNcDestroy()
{
	m_nColors[0].RemoveAll();
	m_nColors[1].RemoveAll();
	m_pFilters[0].RemoveAll();
	m_pFilters[1].RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(COOLSettingsFilteringPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(COOLSettingsFilteringPage)
	ON_BN_CLICKED(IDC_OOLSETTINGS_FILTERINGPAGE_ADD, OnAddFilter)
	ON_BN_CLICKED(IDC_OOLSETTINGS_FILTERINGPAGE_REMOVE, OnRemoveFilter)
	ON_BN_CLICKED(IDC_OOLSETTINGS_FILTERINGPAGE_REMOVEALL, OnRemoveAllFilters)
	ON_BN_CLICKED(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_ALLTIME, OnShowAllTime)
	ON_BN_CLICKED(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_NEVER, OnShowNever)
	ON_BN_CLICKED(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALTIME, OnShowIntervalTime)
	ON_BN_CLICKED(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_ALERTASEVENT, OnBehaviorAsEvent)
	ON_BN_CLICKED(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_BRINGTOTOP, OnBehaviorBringToTop)
	ON_BN_CLICKED(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOACKNOWLEDGE, OnBehaviorAutoacknowledge)
	ON_BN_CLICKED(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_INLIMIT, OnBehaviorInLimit)
	ON_BN_CLICKED(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_FLASH, OnBehaviorFlash)
	ON_BN_CLICKED(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOSCROLL, OnBehaviorAutoscroll)
	ON_CBN_SELCHANGE(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETER, OnSelchangeParameter)
	ON_CBN_SELCHANGE(IDC_OOLSETTINGS_FILTERINGPAGE_AUDITION, OnSelchangeAudition)
	ON_CBN_SELCHANGE(IDC_OOLSETTINGS_FILTERINGPAGE_NOTIFICATION, OnSelchangeNotification)
	ON_CBN_SELCHANGE(IDC_OOLSETTINGS_FILTERINGPAGE_COLORS_STATUS, OnSelchangeColorsStatus)
	ON_CBN_SELCHANGE(IDC_OOLSETTINGS_FILTERINGPAGE_COLORS_COLOR, OnSelchangeColorsColor)
	ON_LBN_SELCHANGE(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETERS, OnSelchangeFilter)
	ON_CONTROL(TSBXN_CHANGE, IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALSTARTTIME, OnSpinchangeIntervalStartTime)
	ON_CONTROL(TSBXN_CHANGE, IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALSTOPTIME, OnSpinchangeIntervalStopTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COOLSettingsFilteringPage message handlers

BOOL COOLSettingsFilteringPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	for (CLocalePropertyPage::OnInitDialog(); EnumParameters() >= 0 && EnumFilters() >= 0 && EnumAuditions() >= 0 && EnumNotifications() >= 0 && EnumStatusColors() >= 0; )
	{
		SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_COLORS_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nColors[0].GetAt(OOL_OOLCOLOR_SOFTLIMIT));
		SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_COLORS_STATUS, CB_SETCURSEL, OOL_OOLCOLOR_SOFTLIMIT);
		SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETER, CB_SETCURSEL);
		SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETERS, LB_SETCURSEL);
		break;
	}
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETER_STATIC)->EnableWindow();
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETER)->EnableWindow();
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETERS)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETERS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_ADD)->EnableWindow((!SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETERS, LB_GETCOUNT)) ? TRUE : FALSE);
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETERS, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETERS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_COLORS_STATUS_STATIC)->EnableWindow();
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_COLORS_STATUS)->EnableWindow();
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_COLORS_COLOR_STATIC)->EnableWindow();
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_COLORS_COLOR)->EnableWindow();
	SetFilterInfo();
	return TRUE;
}

void COOLSettingsFilteringPage::OnAddFilter()
{
	INT  nIndex;
	CString  szParameter;
	COOLParameterFilter  *pFilter;
	CHourglassCursor  cCursor;

	if ((pFilter = new COOLParameterFilter))
	{
		for (GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETER)->GetWindowText(szParameter); (nIndex = (INT)SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETERS, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szParameter)) >= 0; )
		{
			SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETERS, LB_SETCURSEL, nIndex);
			GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETERS)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETERS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_ADD)->EnableWindow(FALSE);
			GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_REMOVE)->EnableWindow();
			GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_REMOVEALL)->EnableWindow();
			m_pFilters[0].InsertAt(nIndex, pFilter, 1);
			GetFilterInfo(pFilter);
			break;
		}
		if (nIndex < 0) delete pFilter;
	}
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsFilteringPage::OnRemoveFilter()
{
	INT  nIndex;
	COOLParameterFilter  *pFilter;
	CHourglassCursor  cCursor;

	if ((nIndex = (INT)SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETERS, LB_GETCURSEL)) >= 0)
	{
		for (SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETERS, LB_DELETESTRING, nIndex), SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETERS, LB_SETCURSEL); (pFilter = m_pFilters[0].GetAt(nIndex)); )
		{
			m_pFilters[0].RemoveAt(nIndex);
			delete pFilter;
			break;
		}
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETERS)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETERS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_ADD)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETERS, LB_GETCURSEL) < 0) ? TRUE : FALSE);
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETERS, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETERS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	}
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsFilteringPage::OnRemoveAllFilters()
{
	CHourglassCursor  cCursor;

	m_pFilters[0].RemoveAll();
	SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETERS, LB_RESETCONTENT);
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETERS)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_ADD)->EnableWindow(TRUE);
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_REMOVEALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsFilteringPage::OnShowAllTime()
{
	UINT  nOptions;
	COOLParameterFilter  *pFilter;

	if ((pFilter = FindFilter()))
	{
		nOptions = (pFilter->GetOptions() & ~(OOLPARAMETERFILTER_SHOW_NEVER | OOLPARAMETERFILTER_SHOW_INTERVAL)) | OOLPARAMETERFILTER_SHOW_ALLTIME;
		pFilter->SetOptions(nOptions);
	}
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALSTARTTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALSTOPTIME)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsFilteringPage::OnShowNever()
{
	UINT  nOptions;
	COOLParameterFilter  *pFilter;

	if ((pFilter = FindFilter()))
	{
		nOptions = (pFilter->GetOptions() & ~(OOLPARAMETERFILTER_SHOW_ALLTIME | OOLPARAMETERFILTER_SHOW_INTERVAL)) | OOLPARAMETERFILTER_SHOW_NEVER;
		pFilter->SetOptions(nOptions);
	}
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALSTARTTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALSTOPTIME)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsFilteringPage::OnShowIntervalTime()
{
	CTimeKey  tTimeKey;
	COOLParameterFilter  *pFilter;

	if ((pFilter = FindFilter()))
	{
		pFilter->SetOptions((pFilter->GetOptions() & ~(OOLPARAMETERFILTER_SHOW_ALLTIME | OOLPARAMETERFILTER_SHOW_NEVER)) | OOLPARAMETERFILTER_SHOW_INTERVAL);
		pFilter->SetTimeRange(tTimeKey, tTimeKey.GetTime() + SECONDSPERMINUTE*OOLSETTINGSFILTERINGPAGE_SHOW_DEFAULTINTERVAL);
	}
	Timespinbox_SetTime(GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALSTARTTIME), tTimeKey);
	Timespinbox_SetTime(GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALSTOPTIME), CTimeKey(tTimeKey.GetTime() + SECONDSPERMINUTE*OOLSETTINGSFILTERINGPAGE_SHOW_DEFAULTINTERVAL));
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALSTARTTIME)->EnableWindow();
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALTIME_STATIC)->EnableWindow();
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALSTOPTIME)->EnableWindow();
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALSTARTTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsFilteringPage::OnBehaviorAsEvent()
{
	UINT  nOptions;
	COOLParameterFilter  *pFilter;

	if ((pFilter = FindFilter()))
	{
		nOptions = (IsDlgButtonChecked(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_ALERTASEVENT)) ? (pFilter->GetOptions() | OOLPARAMETERFILTER_BEHAVIOR_EVENT) : (pFilter->GetOptions() & ~OOLPARAMETERFILTER_BEHAVIOR_EVENT);
		pFilter->SetOptions(nOptions);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsFilteringPage::OnBehaviorBringToTop()
{
	UINT  nOptions;
	COOLParameterFilter  *pFilter;

	if ((pFilter = FindFilter()))
	{
		nOptions = (IsDlgButtonChecked(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_BRINGTOTOP)) ? ((pFilter->GetOptions() & ~OOLPARAMETERFILTER_BEHAVIOR_AUTOACKNOWLEDGE) | OOLPARAMETERFILTER_BEHAVIOR_BRINGTOTOP) : (pFilter->GetOptions() & ~OOLPARAMETERFILTER_BEHAVIOR_BRINGTOTOP);
		pFilter->SetOptions(nOptions);
	}
	CheckDlgButton(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOACKNOWLEDGE, (!IsDlgButtonChecked(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_BRINGTOTOP)) ? IsDlgButtonChecked(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOACKNOWLEDGE) : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsFilteringPage::OnBehaviorAutoacknowledge()
{
	UINT  nOptions;
	COOLParameterFilter  *pFilter;

	if ((pFilter = FindFilter()))
	{
		nOptions = (IsDlgButtonChecked(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOACKNOWLEDGE)) ? ((pFilter->GetOptions() & ~(OOLPARAMETERFILTER_BEHAVIOR_BRINGTOTOP | OOLPARAMETERFILTER_BEHAVIOR_FLASH | OOLPARAMETERFILTER_BEHAVIOR_INLIMIT)) | OOLPARAMETERFILTER_BEHAVIOR_AUTOACKNOWLEDGE) : (pFilter->GetOptions() & ~OOLPARAMETERFILTER_BEHAVIOR_AUTOACKNOWLEDGE);
		pFilter->SetOptions(nOptions);
	}
	if (IsDlgButtonChecked(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOACKNOWLEDGE))
	{
		CheckDlgButton(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_BRINGTOTOP, FALSE);
		CheckDlgButton(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_FLASH, FALSE);
		CheckDlgButton(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_INLIMIT, FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsFilteringPage::OnBehaviorInLimit()
{
	UINT  nOptions;
	COOLParameterFilter  *pFilter;

	if ((pFilter = FindFilter()))
	{
		nOptions = (IsDlgButtonChecked(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_INLIMIT)) ? ((pFilter->GetOptions() & ~OOLPARAMETERFILTER_BEHAVIOR_AUTOACKNOWLEDGE) | OOLPARAMETERFILTER_BEHAVIOR_INLIMIT) : (pFilter->GetOptions() & ~OOLPARAMETERFILTER_BEHAVIOR_INLIMIT);
		pFilter->SetOptions(nOptions);
	}
	CheckDlgButton(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOACKNOWLEDGE, (!IsDlgButtonChecked(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_INLIMIT)) ? IsDlgButtonChecked(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOACKNOWLEDGE) : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsFilteringPage::OnBehaviorFlash()
{
	UINT  nOptions;
	COOLParameterFilter  *pFilter;

	if ((pFilter = FindFilter()))
	{
		nOptions = (IsDlgButtonChecked(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_FLASH)) ? ((pFilter->GetOptions() & ~OOLPARAMETERFILTER_BEHAVIOR_AUTOACKNOWLEDGE) | OOLPARAMETERFILTER_BEHAVIOR_FLASH) : (pFilter->GetOptions() & ~OOLPARAMETERFILTER_BEHAVIOR_FLASH);
		pFilter->SetOptions(nOptions);
	}
	CheckDlgButton(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOACKNOWLEDGE, (!IsDlgButtonChecked(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_FLASH)) ? IsDlgButtonChecked(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOACKNOWLEDGE) : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsFilteringPage::OnBehaviorAutoscroll()
{
	UINT  nOptions;
	COOLParameterFilter  *pFilter;

	if ((pFilter = FindFilter()))
	{
		nOptions = (IsDlgButtonChecked(IDC_OOLSETTINGS_FILTERINGPAGE_BEHAVIOR_AUTOSCROLL)) ? (pFilter->GetOptions() | OOLPARAMETERFILTER_BEHAVIOR_AUTOSCROLL) : (pFilter->GetOptions() & ~OOLPARAMETERFILTER_BEHAVIOR_AUTOSCROLL);
		pFilter->SetOptions(nOptions);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsFilteringPage::OnSelchangeParameter()
{
	CString  szParameter;

	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETER)->GetWindowText(szParameter);
	GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_ADD)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETERS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szParameter) < 0 && SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETERS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)STRING(IDS_OOLSETTINGS_FILTERINGPAGE_PARAMETERSFLAG)) < 0 && (szParameter != STRING(IDS_OOLSETTINGS_FILTERINGPAGE_PARAMETERSFLAG) || !SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_PARAMETERS, LB_GETCOUNT))) ? TRUE : FALSE);
}

void COOLSettingsFilteringPage::OnSelchangeFilter()
{
	SetFilterInfo();
}

void COOLSettingsFilteringPage::OnSelchangeAudition()
{
	CString  szAudition;
	COOLParameterFilter  *pFilter;

	if ((pFilter = FindFilter()))
	{
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_AUDITION)->GetWindowText(szAudition);
		pFilter->SetOptions((szAudition != STRING(IDS_OOLSETTINGS_FILTERINGPAGE_NOAUDITION)) ? (pFilter->GetOptions() | OOLPARAMETERFILTER_ALERT_AUDITION) : (pFilter->GetOptions() & ~OOLPARAMETERFILTER_ALERT_AUDITION));
		pFilter->SetAudition(szAudition);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsFilteringPage::OnSelchangeNotification()
{
	CString  szNotification;
	COOLParameterFilter  *pFilter;

	if ((pFilter = FindFilter()))
	{
		GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_NOTIFICATION)->GetWindowText(szNotification);
		pFilter->SetOptions((szNotification != STRING(IDS_OOLSETTINGS_FILTERINGPAGE_NONOTIFICATION)) ? (pFilter->GetOptions() | OOLPARAMETERFILTER_ALERT_NOTIFICATION) : (pFilter->GetOptions() & ~OOLPARAMETERFILTER_ALERT_NOTIFICATION));
		pFilter->SetNotification(szNotification);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsFilteringPage::OnSelchangeColorsStatus()
{
	SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_COLORS_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nColors[0].GetAt(SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_COLORS_STATUS, CB_GETCURSEL)));
}

void COOLSettingsFilteringPage::OnSelchangeColorsColor()
{
	m_nColors[0].SetAt(SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_COLORS_STATUS, CB_GETCURSEL), (UINT)SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_COLORS_COLOR, CCB_GETCOLOR, SendDlgItemMessage(IDC_OOLSETTINGS_FILTERINGPAGE_COLORS_COLOR, CB_GETCURSEL)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsFilteringPage::OnSpinchangeIntervalStartTime()
{
	CTimeKey  tRange[2];
	COOLParameterFilter  *pFilter;

	for (tRange[0] = Timespinbox_GetTime(GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALSTARTTIME)), tRange[1] = Timespinbox_GetTime(GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALSTOPTIME)); (pFilter = FindFilter()); )
	{
		pFilter->SetTimeRange(tRange[0], (tRange[0] > tRange[1]) ? tRange[0] : tRange[1]);
		break;
	}
	if (tRange[0] > tRange[1]) Timespinbox_SetTime(GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALSTOPTIME), tRange[0]);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsFilteringPage::OnSpinchangeIntervalStopTime()
{
	CTimeKey  tRange[2];
	COOLParameterFilter  *pFilter;

	for (tRange[0] = Timespinbox_GetTime(GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALSTARTTIME)), tRange[1] = Timespinbox_GetTime(GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALSTOPTIME)); (pFilter = FindFilter()); )
	{
		pFilter->SetTimeRange((tRange[0] <= tRange[1]) ? tRange[0] : tRange[1], tRange[1]);
		break;
	}
	if (tRange[0] > tRange[1]) Timespinbox_SetTime(GetDlgItem(IDC_OOLSETTINGS_FILTERINGPAGE_SHOW_INTERVALSTARTTIME), tRange[1]);
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// COOLSettingsRetrievingPage property page

IMPLEMENT_DYNCREATE(COOLSettingsRetrievingPage, CLocalePropertyPage)

COOLSettingsRetrievingPage::COOLSettingsRetrievingPage() : CLocalePropertyPage(COOLSettingsRetrievingPage::IDD)
{
	//{{AFX_DATA_INIT(COOLSettingsRetrievingPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL COOLSettingsRetrievingPage::Initialize()
{
	COOLOpenDialog  *pDialog;

	if (((pDialog = GetParentDialog()->GetParentDialog()) && pDialog->GetRetrieveFileName(m_szFileName[0])) || GetParentDisplay()->GetRetrieveFileName(m_szFileName[0]))
	{
		m_szFileName[1] = m_szFileName[0];
		return TRUE;
	}
	return FALSE;
}

BOOL COOLSettingsRetrievingPage::GetDataSourceFileName(CString &szFileName) CONST
{
	szFileName = m_szFileName[0];
	return Check(FALSE);
}

COOLSettingsDialog *COOLSettingsRetrievingPage::GetParentDialog() CONST
{
	return((COOLSettingsDialog *)CLocalePropertyPage::GetParent());
}

COOLWnd *COOLSettingsRetrievingPage::GetParentDisplay() CONST
{
	return((COOLWnd *)GetParentDialog()->GetParentDisplay());
}

VOID COOLSettingsRetrievingPage::EnumDataSources()
{
	INT  nFile;
	INT  nFiles;
	CHistoryStoreFile  cFile;
	CHistoryStoreFiles  pFiles;
	CUIntArray  nOptions;

	for (nFile = 0, nFiles = GetTMService()->GetTMHistoryFiles(HISTORYFILE_TYPE_RETRIEVE, pFiles), GetTMService()->GetDefaultTMHistoryFile(HISTORYFILE_TYPE_RETRIEVE, cFile), m_szFileName[0] = (pFiles.Find(m_szFileName[0]) < 0) ? cFile.GetFileName() : m_szFileName[0]; nFile < nFiles || (!nFiles && !nFile && !m_szFileName[0].IsEmpty()); nFile++)
	{
		SendDlgItemMessage(IDC_OOLSETTINGS_RETRIEVINGPAGE_DATASOURCE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)((nFiles > 0) ? (LPCTSTR)pFiles.GetAt(nFile)->GetFileName() : (LPCTSTR)m_szFileName[0]));
		continue;
	}
	SendDlgItemMessage(IDC_OOLSETTINGS_RETRIEVINGPAGE_DATASOURCE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_OOLSETTINGS_RETRIEVINGPAGE_DATASOURCE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)m_szFileName[0]), 0));
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_DATASOURCE)->GetWindowText(m_szFileName[0]);
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_DATASOURCE)->GetWindowText(m_szFileName[1]);
	ShowDataSourceInfo();
}

VOID COOLSettingsRetrievingPage::ShowDataSourceInfo()
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
		GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT)->SetWindowText(szProduct);
		GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY)->SetWindowText(szCompany);
		GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT)->SetWindowText(szSpacecraft);
		GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE)->SetWindowText(szDataSourceType);
		GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->SetWindowText(szStartTime);
		GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->SetWindowText(szStopTime);
		GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->SetWindowText(szCreationTime);
		GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE)->SetWindowText(szDataSourceSize);
	}
	else
	{
		GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT)->SetWindowText((szProduct = EMPTYSTRING));
		GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY)->SetWindowText((szCompany = EMPTYSTRING));
		GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT)->SetWindowText((szSpacecraft = EMPTYSTRING));
		GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE)->SetWindowText((szDataSourceType = EMPTYSTRING));
		GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->SetWindowText((szStartTime = EMPTYSTRING));
		GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->SetWindowText((szStopTime = EMPTYSTRING));
		GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->SetWindowText((szCreationTime = EMPTYSTRING));
		GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE)->SetWindowText((szDataSourceSize = EMPTYSTRING));
	}
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO)->EnableWindow();
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMMENTS)->EnableWindow(szProduct.IsEmpty());
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMMENTS)->ShowWindow((szProduct.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT_STATIC)->ShowWindow((!szProduct.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT_STATIC)->EnableWindow(!szProduct.IsEmpty());
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT)->ShowWindow((!szProduct.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT)->EnableWindow(!szProduct.IsEmpty());
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY_STATIC)->ShowWindow((!szCompany.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY_STATIC)->EnableWindow(!szCompany.IsEmpty());
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY)->ShowWindow((!szCompany.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY)->EnableWindow(!szCompany.IsEmpty());
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT_STATIC)->ShowWindow((!szSpacecraft.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT_STATIC)->EnableWindow(!szSpacecraft.IsEmpty());
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT)->ShowWindow((!szSpacecraft.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT)->EnableWindow(!szSpacecraft.IsEmpty());
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE_STATIC)->ShowWindow((!szDataSourceType.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE_STATIC)->EnableWindow(!szDataSourceType.IsEmpty());
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE)->ShowWindow((!szDataSourceType.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE)->EnableWindow(!szDataSourceType.IsEmpty());
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STATIC)->ShowWindow((GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STATIC)->EnableWindow((GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->ShowWindow((GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->EnableWindow((GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_TO)->ShowWindow((GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_TO)->EnableWindow((GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->ShowWindow((GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->EnableWindow((GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME_STATIC)->ShowWindow((GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME_STATIC)->EnableWindow((GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->ShowWindow((GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->EnableWindow((GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE_STATIC)->ShowWindow((!szDataSourceSize.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE_STATIC)->EnableWindow(!szDataSourceSize.IsEmpty());
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE)->ShowWindow((!szDataSourceSize.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE)->EnableWindow(!szDataSourceSize.IsEmpty());
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_INSPECT)->EnableWindow(!m_szFileName[0].IsEmpty());
}

BOOL COOLSettingsRetrievingPage::CheckDataSource(LPCTSTR pszFileName) CONST
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
BOOL COOLSettingsRetrievingPage::CheckDataSource(LPCTSTR pszFileName, CString &szProduct, CString &szCompany, CString &szTrademark, CString &szSpacecraft, CString &szDataSourceType, CString &szStartTime, CString &szStopTime, CString &szCreationTime, CString &szDataSourceSize) CONST
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
			for (cHistoryFile.GetCopyrightProduct(szProduct), cHistoryFile.GetCopyrightCompany(szCompany), cHistoryFile.GetCopyrightTrademark(szTrademark), cHistoryFile.GetSpacecraft(szSpacecraft), cHistoryFile.GetType(szDataSourceType), szStartTime = (cHistoryFile.CLogFile::SeekToFirst() && cHistoryFile.CLogFile::Read(tTime, nData)) ? (LPCTSTR)tTime.FormatGmt(STRING(IDS_OOLSETTINGS_RETRIEVINGPAGE_SOURCEDATATIMEFORMAT)) : EMPTYSTRING, szStopTime = (cHistoryFile.CLogFile::SeekToLast() && cHistoryFile.CLogFile::Read(tTime, nData)) ? (LPCTSTR)tTime.FormatGmt(STRING(IDS_OOLSETTINGS_RETRIEVINGPAGE_SOURCEDATATIMEFORMAT)) : EMPTYSTRING, szCreationTime = (cHistoryFile.GetCopyrightCreationTime(tTime)) ? (LPCTSTR)tTime.FormatGmt(STRING(IDS_OOLSETTINGS_RETRIEVINGPAGE_SOURCEDATAFILETIMEFORMAT)) : EMPTYSTRING, szDataSourceSize.Format(STRING(IDS_OOLSETTINGS_RETRIEVINGPAGE_SOURCEDATASIZEFORMAT), ((dwSize = cHistoryFile.CLogFile::GetSize()) + 512) / 1024), szDataSourceSize = FormatDataSourceSize(szDataSourceSize); !szProduct.IsEmpty() && !szCompany.IsEmpty() && !szTrademark.IsEmpty(); )
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

CString COOLSettingsRetrievingPage::FormatDataSourceSize(LPCTSTR pszDataSourceSize) CONST
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

BOOL COOLSettingsRetrievingPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? ((m_szFileName[0].CompareNoCase(m_szFileName[1])) ? TRUE : FALSE) : CLocalePropertyPage::IsModified()) : FALSE);
}

BOOL COOLSettingsRetrievingPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (m_szFileName[0].IsEmpty() || CheckDataSource(m_szFileName[0])) : CLocalePropertyPage::Check()) : TRUE);
}

void COOLSettingsRetrievingPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COOLSettingsRetrievingPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COOLSettingsRetrievingPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(COOLSettingsRetrievingPage)
	ON_BN_CLICKED(IDC_OOLSETTINGS_RETRIEVINGPAGE_INSPECT, OnInspect)
	ON_CBN_EDITCHANGE(IDC_OOLSETTINGS_RETRIEVINGPAGE_DATASOURCE, OnEditchangeFileName)
	ON_CBN_SELCHANGE(IDC_OOLSETTINGS_RETRIEVINGPAGE_DATASOURCE, OnSelchangeFileName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COOLSettingsRetrievingPage message handlers

BOOL COOLSettingsRetrievingPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_DATASOURCE_STATIC)->EnableWindow();
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_DATASOURCE)->EnableWindow();
	EnumDataSources();
	return TRUE;
}

BOOL COOLSettingsRetrievingPage::OnSetActive()
{
	ShowDataSourceInfo();
	return CLocalePropertyPage::OnSetActive();
}

void COOLSettingsRetrievingPage::OnInspect()
{
	CHourglassCursor  cCursor;

	ShowDataSourceInfo();
}

void COOLSettingsRetrievingPage::OnEditchangeFileName()
{
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_DATASOURCE)->GetWindowText(m_szFileName[0]);
	GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_INSPECT)->EnableWindow(!m_szFileName[0].IsEmpty());
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsRetrievingPage::OnSelchangeFileName()
{
	for (m_szFileName[0] = Combobox_GetText(GetDlgItem(IDC_OOLSETTINGS_RETRIEVINGPAGE_DATASOURCE), (INT)SendDlgItemMessage(IDC_OOLSETTINGS_RETRIEVINGPAGE_DATASOURCE, CB_GETCURSEL)); !m_szFileName[0].IsEmpty(); )
	{
		ShowDataSourceInfo();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// COOLSettingsPrintingComments

IMPLEMENT_DYNCREATE(COOLSettingsPrintingComments, CEdit)

BEGIN_MESSAGE_MAP(COOLSettingsPrintingComments, CEdit)
	//{{AFX_MSG_MAP(COOLSettingsPrintingComments)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COOLSettingsPrintingComments message handlers

void COOLSettingsPrintingComments::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
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
// COOLSettingsPrintingPage property page

IMPLEMENT_DYNCREATE(COOLSettingsPrintingPage, CLocalePropertyPage)

COOLSettingsPrintingPage::COOLSettingsPrintingPage() : CLocalePropertyPage(COOLSettingsPrintingPage::IDD)
{
	//{{AFX_DATA_INIT(COOLSettingsPrintingPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL COOLSettingsPrintingPage::Initialize()
{
	COOLOpenDialog  *pDialog;

	return((((pDialog = GetParentDialog()->GetParentDialog()) && pDialog->GetPrintJobs(m_pJobs[0])) || GetParentDisplay()->GetPrintJobs(m_pJobs[0])) ? m_pJobs[1].Copy(&m_pJobs[0]) : FALSE);
}

BOOL COOLSettingsPrintingPage::GetJobs(COOLPrintJobs &pJobs) CONST
{
	return((pJobs.Copy(&m_pJobs[0])) ? Check(FALSE) : FALSE);
}

COOLSettingsDialog *COOLSettingsPrintingPage::GetParentDialog() CONST
{
	return((COOLSettingsDialog *)CLocalePropertyPage::GetParent());
}

COOLWnd *COOLSettingsPrintingPage::GetParentDisplay() CONST
{
	return((COOLWnd *)GetParentDialog()->GetParentDisplay());
}

VOID COOLSettingsPrintingPage::ShowJobInfo()
{
	UINT  nMode;
	UINT  nCount;
	CTimeKey  tRange[2];
	CTimeSpan  tStartTime;
	CTimeSpan  tStopTime;
	COOLPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		CheckDlgButton(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL, ((nMode = pJobInfo->GetPrintMode()) & OOL_PRINT_ALL) ? TRUE : FALSE);
		CheckDlgButton(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE, ((nMode & OOL_PRINT_FIRSTSIDE) || (nMode & OOL_PRINT_LASTSIDE)) ? TRUE : FALSE);
		CheckDlgButton(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME, (nMode & OOL_PRINT_BYTIME) ? TRUE : FALSE);
		CheckDlgButton(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND, (nMode & OOL_PRINT_COLORLEGEND) ? TRUE : FALSE);
		CheckDlgButton(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS, (nMode & OOL_PRINT_CLEARCOMMENTS) ? TRUE : FALSE);
		SendDlgItemMessage(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetProfile()));
		SendDlgItemMessage(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_SELECTTEXT, (WPARAM)-1, (nMode & OOL_PRINT_FIRSTSIDE) ? (LPARAM)STRING(IDS_OOLSETTINGS_PRINTINGPAGE_FIRSTSIDE) : ((nMode & OOL_PRINT_LASTSIDE) ? (LPARAM)STRING(IDS_OOLSETTINGS_PRINTINGPAGE_LASTSIDE) : (LPARAM)EMPTYSTRING));
		Timespinbox_SetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTARTTIME), (pJobInfo->GetPrintByTime(tRange[0], tRange[1])) ? tRange[0] : CTime::GetCurrentTime().GetTime());
		Timespinbox_SetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTOPTIME), (pJobInfo->GetPrintByTime(tRange[0], tRange[1])) ? tRange[1] : CTime::GetCurrentTime().GetTime());
		Spinbox_SetPos(GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT), (pJobInfo->GetPrintBySide(nCount)) ? nCount : 0);
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->SetWindowText(pJobInfo->GetComments());
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_ADDNAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_REMOVENAME)->EnableWindow((pJobInfo->GetName() != STRING(IDS_PRINTJOB_DEFAULTNAME)) ? TRUE : FALSE);
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_REMOVEALLNAMES)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_PRINTINGPAGE_NAME, CB_GETCOUNT) > 1) ? TRUE : FALSE);
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE_STATIC)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_OPTIONS)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE));
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE));
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE));
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTARTTIME)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME));
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME));
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME));
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTS)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT_STATIC)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)->EnableWindow(!pJobInfo->GetComments().IsEmpty());
		return;
	}
	SendDlgItemMessage(IDC_OOLSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)-1);
	SendDlgItemMessage(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_SETCURSEL, (WPARAM)-1);
	CheckDlgButton(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL, FALSE);
	CheckDlgButton(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE, FALSE);
	CheckDlgButton(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME, FALSE);
	CheckDlgButton(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND, FALSE);
	CheckDlgButton(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS, FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_ADDNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_REMOVENAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_REMOVEALLNAMES)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_OPTIONS)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTARTTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTOPTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTS)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)->EnableWindow(FALSE);
}

COOLPrintJobInfo *COOLSettingsPrintingPage::FindJobInfo() CONST
{
	CString  szJobName;

	GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_NAME)->GetWindowText(szJobName);
	return m_pJobs[0].GetAt(m_pJobs[0].Find(szJobName));
}

BOOL COOLSettingsPrintingPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? !m_pJobs[0].Compare(&m_pJobs[1]) : CLocalePropertyPage::IsModified()) : FALSE);
}

BOOL COOLSettingsPrintingPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? ((GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_NAME)->GetWindowTextLength() > 0 && FindJobInfo()) ? TRUE : FALSE) : CLocalePropertyPage::Check()) : TRUE);
}

void COOLSettingsPrintingPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COOLSettingsPrintingPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void COOLSettingsPrintingPage::PostNcDestroy()
{
	m_pJobs[0].RemoveAll();
	m_pJobs[1].RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(COOLSettingsPrintingPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(COOLSettingsPrintingPage)
	ON_BN_CLICKED(IDC_OOLSETTINGS_PRINTINGPAGE_ADDNAME, OnAddName)
	ON_BN_CLICKED(IDC_OOLSETTINGS_PRINTINGPAGE_REMOVENAME, OnRemoveName)
	ON_BN_CLICKED(IDC_OOLSETTINGS_PRINTINGPAGE_REMOVEALLNAMES, OnRemoveAllNames)
	ON_BN_CLICKED(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL, OnPrintAll)
	ON_BN_CLICKED(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE, OnPrintBySide)
	ON_BN_CLICKED(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME, OnPrintByTime)
	ON_BN_CLICKED(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND, OnPrintColorLegend)
	ON_BN_CLICKED(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS, OnResetComments)
	ON_CBN_EDITCHANGE(IDC_OOLSETTINGS_PRINTINGPAGE_NAME, OnEditchangeName)
	ON_CBN_SELCHANGE(IDC_OOLSETTINGS_PRINTINGPAGE_NAME, OnSelchangeName)
	ON_CBN_SELCHANGE(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, OnSelchangeProfile)
	ON_EN_CHANGE(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, OnChangePrintSide)
	ON_EN_CHANGE(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT, OnEditchangeComments)
	ON_CONTROL(SBXN_CHANGE, IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT, OnSpinchangePrintSideCount)
	ON_CONTROL(TSBXN_CHANGE, IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTARTTIME, OnSpinchangePrintStartTime)
	ON_CONTROL(TSBXN_CHANGE, IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTOPTIME, OnSpinchangePrintStopTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COOLSettingsPrintingPage message handlers

BOOL COOLSettingsPrintingPage::OnInitDialog()
{
	INT  nJob;
	INT  nJobs;
	INT  nProfile;
	INT  nProfiles;
	CStringArray  szProfiles;
	COOLPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	for (CLocalePropertyPage::OnInitDialog(); m_wndComments.SubclassWindow(GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->GetSafeHwnd()); )
	{
		for (nJob = 0, nJobs = (INT)m_pJobs[0].GetSize(); nJob < nJobs; nJob++)
		{
			if ((pJobInfo = m_pJobs[0].GetAt(nJob)) != (COOLPrintJobInfo *)NULL)
			{
				SendDlgItemMessage(IDC_OOLSETTINGS_PRINTINGPAGE_NAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pJobInfo->GetName());
				continue;
			}
		}
		for (nProfile = 0, nProfiles = (EnumPrintProfiles(szProfiles)) ? (INT)szProfiles.GetSize() : 0; nProfile < nProfiles; nProfile++)
		{
			SendDlgItemMessage(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szProfiles.GetAt(nProfile));
			continue;
		}
		Spinbox_SetRange(GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT), OOLSETTINGSPRINTINGPAGE_OPTIONS_MINIMUMOOLS, OOLSETTINGSPRINTINGPAGE_OPTIONS_MAXIMUMOOLS);
		SendDlgItemMessage(IDC_OOLSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_OOLSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_PRINTJOB_DEFAULTNAME)));
		SendDlgItemMessage(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_ADDTEXT, (WPARAM)NULL, (LPARAM)STRING(IDS_OOLSETTINGS_PRINTINGPAGE_FIRSTSIDE));
		SendDlgItemMessage(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_ADDTEXT, (WPARAM)NULL, (LPARAM)STRING(IDS_OOLSETTINGS_PRINTINGPAGE_LASTSIDE));
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_DETAILS)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_NAME_STATIC)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_NAME)->EnableWindow();
		ShowJobInfo();
		break;
	}
	return TRUE;
}

BOOL COOLSettingsPrintingPage::OnSetActive()
{
	ShowJobInfo();
	return CLocalePropertyPage::OnSetActive();
}

BOOL COOLSettingsPrintingPage::OnKillActive()
{
	GetParentDialog()->OnDataExchange(GetSafeHwnd(), m_pJobs[0]);
	return CLocalePropertyPage::OnKillActive();
}

BOOL COOLSettingsPrintingPage::OnDataExchange(CONST COOLPrintJobs &pJobs)
{
	return m_pJobs[0].Copy(&pJobs);
}

void COOLSettingsPrintingPage::OnEditchangeName()
{
	CString  szJobName;
	COOLPrintJobInfo  *pJobInfo;

	for (GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_NAME)->GetWindowText(szJobName); (pJobInfo = FindJobInfo()); )
	{
		ShowJobInfo();
		return;
	}
	GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_ADDNAME)->EnableWindow((!pJobInfo  &&  szJobName.GetLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_REMOVENAME)->EnableWindow((pJobInfo != (COOLPrintJobInfo *)NULL  &&  szJobName != STRING(IDS_PRINTJOB_DEFAULTNAME)) ? TRUE : FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_REMOVEALLNAMES)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_PRINTINGPAGE_NAME, CB_GETCOUNT) > 1) ? TRUE : FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)->EnableWindow((szJobName != STRING(IDS_PRINTJOB_DEFAULTNAME)) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsPrintingPage::OnSelchangeName()
{
	SendDlgItemMessage(IDC_OOLSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_OOLSETTINGS_PRINTINGPAGE_NAME, CB_GETCURSEL));
	ShowJobInfo();
}

void COOLSettingsPrintingPage::OnAddName()
{
	INT  nIndex;
	UINT  nMode;
	UINT  nCount;
	CString  szJobName;
	CString  szProfile;
	CString  szComments;
	CTimeKey  tRange[2];
	COOLPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	for (; (pJobInfo = new COOLPrintJobInfo); )
	{
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_NAME)->GetWindowText(szJobName);
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE)->GetWindowText(szProfile);
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->GetWindowText(szComments);
		nMode = (IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL)) ? ((pJobInfo->GetPrintMode() | OOL_PRINT_ALL) & ~(OOL_PRINT_FIRSTSIDE | OOL_PRINT_LASTSIDE | OOL_PRINT_BYTIME)) : pJobInfo->GetPrintMode();
		nMode = (IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE)) ? ((!GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE)->SendMessage(TEM_GETPOS)) ? ((nMode | OOL_PRINT_FIRSTSIDE) & ~(OOL_PRINT_ALL | OOL_PRINT_LASTSIDE | OOL_PRINT_BYTIME)) : ((nMode | OOL_PRINT_LASTSIDE) & ~(OOL_PRINT_ALL | OOL_PRINT_FIRSTSIDE | OOL_PRINT_BYTIME))) : nMode;
		nMode = (IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME)) ? ((nMode | OOL_PRINT_BYTIME) & ~(OOL_PRINT_ALL | OOL_PRINT_FIRSTSIDE | OOL_PRINT_LASTSIDE)) : nMode;
		nMode = (IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND)) ? (nMode | OOL_PRINT_COLORLEGEND) : nMode;
		nMode = (IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)) ? (nMode | OOL_PRINT_CLEARCOMMENTS) : (nMode & ~OOL_PRINT_CLEARCOMMENTS);
		nCount = ((nMode & OOL_PRINT_FIRSTSIDE) || (nMode & OOL_PRINT_LASTSIDE)) ? (UINT)Spinbox_GetPos(GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)) : 0;
		tRange[0] = (IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME)) ? Timespinbox_GetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTARTTIME)) : 0;
		tRange[1] = (IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME)) ? Timespinbox_GetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTOPTIME)) : 0;
		if (SendDlgItemMessage(IDC_OOLSETTINGS_PRINTINGPAGE_NAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szJobName) >= 0 && SendDlgItemMessage(IDC_OOLSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_OOLSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szJobName)) >= 0)
		{
			for (pJobInfo->SetName(szJobName), pJobInfo->SetProfile(szProfile), pJobInfo->SetComments(szComments), pJobInfo->SetPrintMode(nMode), pJobInfo->SetPrintBySide(nCount), pJobInfo->SetPrintByTime(tRange[0], tRange[1]); (nIndex = m_pJobs[0].Add(pJobInfo)) >= 0; )
			{
				ShowJobInfo();
				break;
			}
			if (nIndex >= 0) break;
		}
		delete pJobInfo;
		break;
	}
	GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsPrintingPage::OnRemoveName()
{
	INT  nJob;
	INT  nJobs;
	COOLPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	for (nJob = 0, nJobs = (INT)m_pJobs[0].GetSize(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = m_pJobs[0].GetAt(nJob)) && pJobInfo == FindJobInfo())
		{
			if (SendDlgItemMessage(IDC_OOLSETTINGS_PRINTINGPAGE_NAME, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_OOLSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName())) > 0)
			{
				m_pJobs[0].RemoveAt(nJob);
				delete pJobInfo;
			}
			break;
		}
	}
	for (; SendDlgItemMessage(IDC_OOLSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_OOLSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_PRINTJOB_DEFAULTNAME))) >= 0; )
	{
		ShowJobInfo();
		break;
	}
	GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsPrintingPage::OnRemoveAllNames()
{
	INT  nJob;
	INT  nJobs;
	COOLPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	for (nJob = 0, nJobs = (INT)m_pJobs[0].GetSize(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = m_pJobs[0].GetAt(nJob)) && pJobInfo->GetName() != STRING(IDS_PRINTJOB_DEFAULTNAME) && SendDlgItemMessage(IDC_OOLSETTINGS_PRINTINGPAGE_NAME, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_OOLSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName())) > 0)
		{
			m_pJobs[0].RemoveAt(nJob);
			delete pJobInfo;
			nJobs--;
			nJob--;
		}
	}
	for (; SendDlgItemMessage(IDC_OOLSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_OOLSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_PRINTJOB_DEFAULTNAME))) >= 0; )
	{
		ShowJobInfo();
		break;
	}
	GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsPrintingPage::OnSelchangeProfile()
{
	CString  szProfile;
	COOLPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE)->GetWindowText(szProfile);
		pJobInfo->SetProfile(szProfile);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsPrintingPage::OnPrintAll()
{
	COOLPrintJobInfo  *pJobInfo;

	if (!IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL))
	{
		for (CheckDlgButton(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL, TRUE), CheckDlgButton(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE, FALSE), CheckDlgButton(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME, FALSE), SendDlgItemMessage(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_SELECTTEXT, (WPARAM)-1, (LPARAM)EMPTYSTRING); (pJobInfo = FindJobInfo()); )
		{
			pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | OOL_PRINT_ALL) & ~(OOL_PRINT_FIRSTSIDE | OOL_PRINT_LASTSIDE | OOL_PRINT_BYTIME));
			break;
		}
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_ADDNAME)->EnableWindow((GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_NAME)->GetWindowTextLength() > 0 && SendDlgItemMessage(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_GETCURSEL) != CB_ERR  &&  !pJobInfo) ? TRUE : FALSE);
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE)->EnableWindow(FALSE);
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)->EnableWindow(FALSE);
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTARTTIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTOPTIME)->EnableWindow(FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsPrintingPage::OnPrintBySide()
{
	COOLPrintJobInfo  *pJobInfo;

	if (!IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE))
	{
		for (CheckDlgButton(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL, FALSE), CheckDlgButton(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE, TRUE), CheckDlgButton(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME, FALSE), SendDlgItemMessage(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_SELECTTEXT, (WPARAM)-1, (LPARAM)STRING(IDS_OOLSETTINGS_PRINTINGPAGE_LASTSIDE)), Spinbox_SetPos(GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT), OOLSETTINGSPRINTINGPAGE_OPTIONS_DEFAULTOOLS); (pJobInfo = FindJobInfo()); )
		{
			pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | OOL_PRINT_LASTSIDE) & ~(OOL_PRINT_ALL | OOL_PRINT_FIRSTSIDE | OOL_PRINT_BYTIME));
			pJobInfo->SetPrintBySide(OOLSETTINGSPRINTINGPAGE_OPTIONS_DEFAULTOOLS);
			break;
		}
		SendDlgItemMessage(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, EM_SETSEL, 0, (LPARAM)-1);
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_ADDNAME)->EnableWindow((GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_NAME)->GetWindowTextLength() > 0 && SendDlgItemMessage(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_GETCURSEL) != CB_ERR  &&  !pJobInfo) ? TRUE : FALSE);
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE_STATIC)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTARTTIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTOPTIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE)->SetFocus();
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsPrintingPage::OnPrintByTime()
{
	CTimeKey  tTimeKey;
	COOLPrintJobInfo  *pJobInfo;

	if (!IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME))
	{
		for (CheckDlgButton(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL, FALSE), CheckDlgButton(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE, FALSE), CheckDlgButton(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME, TRUE), SendDlgItemMessage(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_SELECTTEXT, (WPARAM)-1, (LPARAM)EMPTYSTRING), Timespinbox_SetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTARTTIME), CTimeKey(tTimeKey.GetTime() - SECONDSPERMINUTE*OOLSETTINGSPRINTINGPAGE_OPTIONS_DEFAULTINTERVAL)), Timespinbox_SetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTOPTIME), tTimeKey); (pJobInfo = FindJobInfo()); )
		{
			pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | OOL_PRINT_BYTIME) & ~(OOL_PRINT_ALL | OOL_PRINT_FIRSTSIDE | OOL_PRINT_LASTSIDE));
			pJobInfo->SetPrintByTime(tTimeKey.GetTime() - SECONDSPERMINUTE*OOLSETTINGSPRINTINGPAGE_OPTIONS_DEFAULTINTERVAL, tTimeKey.GetTime());
			break;
		}
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_ADDNAME)->EnableWindow((GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_NAME)->GetWindowTextLength() > 0 && SendDlgItemMessage(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_GETCURSEL) != CB_ERR  &&  !pJobInfo) ? TRUE : FALSE);
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE)->EnableWindow(FALSE);
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)->EnableWindow(FALSE);
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTARTTIME)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYTIME_STATIC)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTOPTIME)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTARTTIME)->SetFocus();
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsPrintingPage::OnPrintColorLegend()
{
	UINT  nMode;
	COOLPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		nMode = (IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND)) ? (pJobInfo->GetPrintMode() | OOL_PRINT_COLORLEGEND) : (pJobInfo->GetPrintMode() & ~OOL_PRINT_COLORLEGEND);
		pJobInfo->SetPrintMode(nMode);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsPrintingPage::OnChangePrintSide()
{
	UINT  nMode;
	COOLPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		nMode = (!SendDlgItemMessage(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE, TEM_GETPOS)) ? ((pJobInfo->GetPrintMode() | OOL_PRINT_FIRSTSIDE) & ~(OOL_PRINT_ALL | OOL_PRINT_LASTSIDE)) : ((pJobInfo->GetPrintMode() | OOL_PRINT_LASTSIDE) & ~(OOL_PRINT_ALL | OOL_PRINT_FIRSTSIDE));
		pJobInfo->SetPrintMode(nMode);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsPrintingPage::OnSpinchangePrintSideCount()
{
	COOLPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo())) pJobInfo->SetPrintBySide((UINT)Spinbox_GetPos(GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsPrintingPage::OnSpinchangePrintStartTime()
{
	CTimeKey  tRange[2];
	COOLPrintJobInfo  *pJobInfo;

	for (tRange[0] = Timespinbox_GetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTARTTIME)), tRange[1] = Timespinbox_GetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTOPTIME)); (pJobInfo = FindJobInfo()); )
	{
		pJobInfo->SetPrintByTime(tRange[0], (tRange[0] >= tRange[1]) ? (tRange[0].GetTime() + 1) : tRange[1]);
		break;
	}
	Timespinbox_SetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTOPTIME), (tRange[0] >= tRange[1]) ? (tRange[0].GetTime() + 1) : tRange[1]);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsPrintingPage::OnSpinchangePrintStopTime()
{
	CTimeKey  tRange[2];
	COOLPrintJobInfo  *pJobInfo;

	for (tRange[0] = Timespinbox_GetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTARTTIME)), tRange[1] = Timespinbox_GetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTOPTIME)); (pJobInfo = FindJobInfo()); )
	{
		pJobInfo->SetPrintByTime((tRange[0] < tRange[1]) ? tRange[0] : (tRange[1].GetTime() - 1), tRange[1]);
		break;
	}
	Timespinbox_SetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSTARTTIME), (tRange[0] >= tRange[1]) ? (tRange[1].GetTime() - 1) : tRange[0]);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsPrintingPage::OnEditchangeComments()
{
	CString  szComments;
	COOLPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->GetWindowText(szComments);
		GetDlgItem(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)->EnableWindow(!szComments.IsEmpty());
		CheckDlgButton(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS, (!szComments.IsEmpty()) ? IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS) : FALSE);
		pJobInfo->SetPrintMode((IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)) ? (pJobInfo->GetPrintMode() | OOL_PRINT_CLEARCOMMENTS) : (pJobInfo->GetPrintMode() & ~OOL_PRINT_CLEARCOMMENTS));
		pJobInfo->SetComments(szComments);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsPrintingPage::OnResetComments()
{
	UINT  nMode;
	COOLPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		nMode = (IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)) ? (pJobInfo->GetPrintMode() | OOL_PRINT_CLEARCOMMENTS) : (pJobInfo->GetPrintMode() & ~OOL_PRINT_CLEARCOMMENTS);
		pJobInfo->SetPrintMode(nMode);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// COOLSettingsPrintJobsPage property page

IMPLEMENT_DYNCREATE(COOLSettingsPrintJobsPage, CLocalePropertyPage)

COOLSettingsPrintJobsPage::COOLSettingsPrintJobsPage() : CLocalePropertyPage(COOLSettingsPrintJobsPage::IDD)
{
	//{{AFX_DATA_INIT(COOLSettingsPrintJobsPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL COOLSettingsPrintJobsPage::Initialize()
{
	COOLOpenDialog  *pDialog;

	return((((pDialog = GetParentDialog()->GetParentDialog()) && pDialog->GetPrintJobs(m_pJobs[0])) || GetParentDisplay()->GetPrintJobs(m_pJobs[0])) ? m_pJobs[1].Copy(&m_pJobs[0]) : FALSE);
}

BOOL COOLSettingsPrintJobsPage::GetJobs(COOLPrintJobs &pJobs) CONST
{
	return((pJobs.Copy(&m_pJobs[0])) ? Check(FALSE) : FALSE);
}

COOLSettingsDialog *COOLSettingsPrintJobsPage::GetParentDialog() CONST
{
	return((COOLSettingsDialog *)CLocalePropertyPage::GetParent());
}

COOLWnd *COOLSettingsPrintJobsPage::GetParentDisplay() CONST
{
	return((COOLWnd *)GetParentDialog()->GetParentDisplay());
}

BOOL COOLSettingsPrintJobsPage::EnumJobs()
{
	INT  nJob;
	INT  nJobs;
	UINT  nMode;
	COOLPrintJobInfo  *pJobInfo;

	SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, LB_RESETCONTENT);
	SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_RESETCONTENT);
	for (nJob = 0, nJobs = (INT)m_pJobs[0].GetSize(); nJob < nJobs; nJob = nJob + 1)
	{
		if ((pJobInfo = m_pJobs[0].GetAt(nJob)) && pJobInfo->GetName() != STRING(IDS_PRINTJOB_DEFAULTNAME))
		{
			if (SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pJobInfo->GetName()) >= 0)
			{
				if (((nMode = pJobInfo->GetPrintMode()) & OOL_PRINT_ACTIVE) && ((nMode & OOL_PRINT_ATTIME) || (nMode & OOL_PRINT_ATDAILYTIME) || (nMode & OOL_PRINT_ATEVENT)))
				{
					if (SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR)
					{
						pJobInfo->SetPrintMode(nMode & ~(OOL_PRINT_ACTIVE | OOL_PRINT_ATTIME | OOL_PRINT_ATDAILYTIME | OOL_PRINT_ATEVENT | OOL_PRINT_REPEATBYINTERVAL | OOL_PRINT_REPEATSTOPBYCOUNT | OOL_PRINT_REPEATSTOPBYTIME | OOL_PRINT_DAILYREPEATSTOPBYCOUNT | OOL_PRINT_DAILYREPEATSTOPBYTIME));
						continue;
					}
				}
			}
		}
	}
	if (SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, LB_GETCOUNT) > 0)
	{
		SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, LB_SETCURSEL);
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_DETAILS)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS_STATIC)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)Listbox_GetText(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS), (INT)SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, LB_GETCURSEL))) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_REMOVEJOB)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
		ShowJobInfo();
		return TRUE;
	}
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_DETAILS)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_REMOVEJOB)->EnableWindow(FALSE);
	ShowJobInfo();
	return FALSE;
}

BOOL COOLSettingsPrintJobsPage::EnumEvents()
{
	INT  nEvent;
	INT  nEvents;
	CTelemetryEvents  pEvents;
	CTelemetryEventInfo  *pEventInfo;

	for (nEvent = 0, nEvents = (GetTelemetryEvents(pEvents)) ? (INT)pEvents.GetSize() : 0; nEvent < nEvents; nEvent++)
	{
		if ((pEventInfo = pEvents.GetAt(nEvent))) SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pEventInfo->GetName());
		continue;
	}
	return((SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID COOLSettingsPrintJobsPage::ShowJobInfo()
{
	UINT  nStopCount;
	CString  szEvent;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CTimeSpan  tDailyTime;
	COOLPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		Timespinbox_SetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME), (pJobInfo->GetPrintAtTime(tTime) || pJobInfo->GetPrintAtTime(tTime, tInterval) || pJobInfo->GetPrintAtTime(tTime, tInterval, nStopCount) || pJobInfo->GetPrintAtTime(tTime, tInterval, tStopTime)) ? tTime : CTime::GetCurrentTime().GetTime());
		Timespinbox_SetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME), (pJobInfo->GetPrintAtDailyTime(tDailyTime) || pJobInfo->GetPrintAtDailyTime(tDailyTime, nStopCount) || pJobInfo->GetPrintAtDailyTime(tDailyTime, tStopTime)) ? CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + tDailyTime.GetTotalSeconds()) : CTime::GetCurrentTime().GetTime());
		SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_SETCURSEL, (pJobInfo->GetPrintAtEvent(szEvent)) ? (WPARAM)SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szEvent) : (WPARAM)-1);
		SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, (SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_OOLSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS)) < 0 && (pJobInfo->GetPrintMode() & OOL_PRINT_ATTIME)) ? CB_ADDSTRING : CB_FINDSTRING, (WPARAM)NULL, (LPARAM)STRING(IDS_OOLSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS));
		SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, (SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_OOLSETTINGS_PRINTJOBSPAGE_DAILYPRINTS)) < 0 && (pJobInfo->GetPrintMode() & OOL_PRINT_ATDAILYTIME)) ? CB_ADDSTRING : CB_FINDSTRING, (WPARAM)NULL, (LPARAM)STRING(IDS_OOLSETTINGS_PRINTJOBSPAGE_DAILYPRINTS));
		SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_SETCURSEL, ((pJobInfo->GetPrintMode() & OOL_PRINT_ATTIME) || (pJobInfo->GetPrintMode() & OOL_PRINT_ATDAILYTIME)) ? (WPARAM)SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)((pJobInfo->GetPrintMode() & OOL_PRINT_ATTIME) ? STRING(IDS_OOLSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS) : STRING(IDS_OOLSETTINGS_PRINTJOBSPAGE_DAILYPRINTS))) : (WPARAM)-1);
		CheckDlgButton(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME, (pJobInfo->GetPrintMode() & OOL_PRINT_ATTIME) ? TRUE : FALSE);
		CheckDlgButton(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME, (pJobInfo->GetPrintMode() & OOL_PRINT_ATDAILYTIME) ? TRUE : FALSE);
		CheckDlgButton(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT, (pJobInfo->GetPrintMode() & OOL_PRINT_ATEVENT) ? ((SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_GETCURSEL) >= 0) ? TRUE : FALSE) : FALSE);
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME));
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)->EnableWindow();
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT));
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT));
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		SetJobRepetitionInfo();
		return;
	}
	CheckDlgButton(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME, FALSE);
	CheckDlgButton(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME, FALSE);
	CheckDlgButton(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT, FALSE);
	CheckDlgButton(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME, FALSE);
	CheckDlgButton(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, FALSE);
	CheckDlgButton(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, FALSE);
	SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_SETCURSEL, (WPARAM)-1);
	SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_SETCURSEL, (WPARAM)-1);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow(FALSE);
}

BOOL COOLSettingsPrintJobsPage::CheckJobInfo() CONST
{
	UINT  nStopCount;
	CString  szEvent;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CTimeSpan  tDailyTime;
	COOLPrintJobInfo  *pJobInfo;

	return(((pJobInfo = FindJobInfo())) ? ((pJobInfo->GetPrintAtTime(tTime) && tTime > CTime::GetCurrentTime()) || pJobInfo->GetPrintAtTime(tTime, tInterval) || (pJobInfo->GetPrintAtTime(tTime, tInterval, nStopCount) && tTime.GetTime() + tInterval.GetTotalSeconds()*(TIMEKEY)nStopCount > CTime::GetCurrentTime().GetTime()) || (pJobInfo->GetPrintAtTime(tTime, tInterval, tStopTime) && tStopTime > CTime::GetCurrentTime()) || pJobInfo->GetPrintAtDailyTime(tDailyTime) || pJobInfo->GetPrintAtDailyTime(tDailyTime, nStopCount) || (pJobInfo->GetPrintAtDailyTime(tDailyTime, tStopTime) && tStopTime > CTime::GetCurrentTime()) || pJobInfo->GetPrintAtEvent(szEvent)) : FALSE);
}

COOLPrintJobInfo *COOLSettingsPrintJobsPage::FindJobInfo(BOOL bActive) CONST
{
	INT  nJob;
	INT  nJobs;
	CString  szJobName[2];
	COOLPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (INT)m_pJobs[0].GetSize(), szJobName[0] = Listbox_GetText(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS), (INT)GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS)->SendMessage(LB_GETCURSEL)), szJobName[1] = Listbox_GetText(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS), (INT)GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS)->SendMessage(LB_GETCURSEL)), szJobName[0] = (!bActive) ? szJobName[0] : szJobName[1]; nJob < nJobs; nJob++)
	{
		if ((pJobInfo = m_pJobs[0].GetAt(nJob)) && pJobInfo->GetName() == szJobName[0]) break;
		continue;
	}
	return((nJob < nJobs) ? pJobInfo : (COOLPrintJobInfo *)NULL);
}

VOID COOLSettingsPrintJobsPage::SetJobRepetitionInfo()
{
	UINT  nStopCount;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CTimeSpan  tDailyTime;
	COOLPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		Timespinbox_SetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), ((GetJobRepetitionType() == OOLSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  pJobInfo->GetPrintAtTime(tTime, tInterval, tStopTime)) || (GetJobRepetitionType() == OOLSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  pJobInfo->GetPrintAtDailyTime(tDailyTime, tStopTime))) ? tStopTime : CTime::GetCurrentTime().GetTime());
		Spinbox_SetPos(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME), (pJobInfo->GetPrintAtTime(tTime, tInterval) || pJobInfo->GetPrintAtTime(tTime, tInterval, nStopCount) || pJobInfo->GetPrintAtTime(tTime, tInterval, tStopTime)) ? (tInterval.GetTotalSeconds() / SECONDSPERMINUTE) : 0);
		Spinbox_SetPos(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), ((GetJobRepetitionType() == OOLSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  pJobInfo->GetPrintAtTime(tTime, tInterval, nStopCount)) || (GetJobRepetitionType() == OOLSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  pJobInfo->GetPrintAtDailyTime(tDailyTime, nStopCount))) ? nStopCount : 0);
		CheckDlgButton(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME, (GetJobRepetitionType() == OOLSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY && (pJobInfo->GetPrintMode() & OOL_PRINT_REPEATBYINTERVAL)) ? TRUE : FALSE);
		CheckDlgButton(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, ((GetJobRepetitionType() == OOLSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY && (pJobInfo->GetPrintMode() & OOL_PRINT_REPEATSTOPBYCOUNT)) || (GetJobRepetitionType() == OOLSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY && (pJobInfo->GetPrintMode() & OOL_PRINT_DAILYREPEATSTOPBYCOUNT))) ? TRUE : FALSE);
		CheckDlgButton(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, ((GetJobRepetitionType() == OOLSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY && (pJobInfo->GetPrintMode() & OOL_PRINT_REPEATSTOPBYTIME)) || (GetJobRepetitionType() == OOLSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY && (pJobInfo->GetPrintMode() & OOL_PRINT_DAILYREPEATSTOPBYTIME))) ? TRUE : FALSE);
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)->EnableWindow((GetJobRepetitionType() == OOLSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY) ? TRUE : FALSE);
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)->EnableWindow(GetJobRepetitionType() == OOLSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC)->EnableWindow(GetJobRepetitionType() == OOLSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC)->EnableWindow((IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && (GetJobRepetitionType() == OOLSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY || IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)));
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)->EnableWindow((IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && (GetJobRepetitionType() == OOLSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY || IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)));
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow((IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES));
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow((IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES));
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)->EnableWindow((IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && (GetJobRepetitionType() == OOLSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY || IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)));
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow((IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME));
		return;
	}
	CheckDlgButton(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME, FALSE);
	CheckDlgButton(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, FALSE);
	CheckDlgButton(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow(FALSE);
}

UINT COOLSettingsPrintJobsPage::GetJobRepetitionType() CONST
{
	CString  szRepetitionType;

	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE)->GetWindowText(szRepetitionType);
	return((szRepetitionType == STRING(IDS_OOLSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS) || szRepetitionType == STRING(IDS_OOLSETTINGS_PRINTJOBSPAGE_DAILYPRINTS)) ? ((szRepetitionType == STRING(IDS_OOLSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS)) ? OOLSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY : OOLSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY) : 0);
}

BOOL COOLSettingsPrintJobsPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? !m_pJobs[0].Compare(&m_pJobs[1]) : CLocalePropertyPage::IsModified()) : FALSE);
}

BOOL COOLSettingsPrintJobsPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? TRUE : CLocalePropertyPage::Check()) : TRUE);
}

void COOLSettingsPrintJobsPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COOLSettingsPrintJobsPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void COOLSettingsPrintJobsPage::PostNcDestroy()
{
	m_pJobs[0].RemoveAll();
	m_pJobs[1].RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(COOLSettingsPrintJobsPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(COOLSettingsPrintJobsPage)
	ON_BN_CLICKED(IDC_OOLSETTINGS_PRINTJOBSPAGE_ADDJOB, OnAddJob)
	ON_BN_CLICKED(IDC_OOLSETTINGS_PRINTJOBSPAGE_REMOVEJOB, OnRemoveJob)
	ON_BN_CLICKED(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME, OnPrintAtTime)
	ON_BN_CLICKED(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME, OnPrintAtDailyTime)
	ON_BN_CLICKED(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT, OnPrintAtEvent)
	ON_BN_CLICKED(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME, OnRepeatByTime)
	ON_BN_CLICKED(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, OnRepetitionStopByCopies)
	ON_BN_CLICKED(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, OnRepetitionStopByTime)
	ON_CBN_SELCHANGE(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, OnSelchangeEvent)
	ON_CBN_SELCHANGE(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, OnSelchangeRepetitionType)
	ON_LBN_SELCHANGE(IDC_OOLSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, OnSelchangeDefinedJob)
	ON_LBN_SELCHANGE(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, OnSelchangeActiveJob)
	ON_CONTROL(SBXN_CHANGE, IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME, OnSpinchangeRepeatTime)
	ON_CONTROL(SBXN_CHANGE, IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES, OnSpinchangeRepetitionStopCopies)
	ON_CONTROL(TSBXN_CHANGE, IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME, OnSpinchangePrintTime)
	ON_CONTROL(TSBXN_CHANGE, IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME, OnSpinchangePrintDailyTime)
	ON_CONTROL(TSBXN_CHANGE, IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME, OnSpinchangeRepetitionStopTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COOLSettingsPrintJobsPage message handlers

BOOL COOLSettingsPrintJobsPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	Spinbox_SetRange(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME), OOLSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMINTERVAL, OOLSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMINTERVAL);
	Spinbox_SetRange(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), OOLSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES, OOLSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES);
	EnumEvents();
	return TRUE;
}

BOOL COOLSettingsPrintJobsPage::OnSetActive()
{
	EnumJobs();
	return CLocalePropertyPage::OnSetActive();
}

BOOL COOLSettingsPrintJobsPage::OnKillActive()
{
	GetParentDialog()->OnDataExchange(GetSafeHwnd(), m_pJobs[0]);
	return CLocalePropertyPage::OnKillActive();
}

BOOL COOLSettingsPrintJobsPage::OnDataExchange(CONST COOLPrintJobs &pJobs)
{
	return m_pJobs[0].Copy(&pJobs);
}

void COOLSettingsPrintJobsPage::OnAddJob()
{
	COOLPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	if ((pJobInfo = FindJobInfo()))
	{
		pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() | OOL_PRINT_ACTIVE);
		SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pJobInfo->GetName());
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow(FALSE);
	}
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsPrintJobsPage::OnRemoveJob()
{
	COOLPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	if ((pJobInfo = FindJobInfo(TRUE)))
	{
		for (pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~(OOL_PRINT_ACTIVE | OOL_PRINT_ATTIME | OOL_PRINT_ATDAILYTIME | OOL_PRINT_ATEVENT | OOL_PRINT_REPEATBYINTERVAL | OOL_PRINT_REPEATSTOPBYCOUNT | OOL_PRINT_REPEATSTOPBYTIME | OOL_PRINT_DAILYREPEATSTOPBYCOUNT | OOL_PRINT_DAILYREPEATSTOPBYTIME)), SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCURSEL)); pJobInfo == FindJobInfo(); )
		{
			ShowJobInfo();
			break;
		}
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_REMOVEJOB)->EnableWindow(FALSE);
	}
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsPrintJobsPage::OnSelchangeDefinedJob()
{
	COOLPrintJobInfo  *pJobInfo;

	ShowJobInfo();
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow(((pJobInfo = FindJobInfo()) && SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
}

void COOLSettingsPrintJobsPage::OnSelchangeActiveJob()
{
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_REMOVEJOB)->EnableWindow();
}

void COOLSettingsPrintJobsPage::OnPrintAtTime()
{
	CTimeKey  tTime;
	COOLPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		if (IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME))
		{
			Timespinbox_SetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME), (tTime = CTime::GetCurrentTime().GetTime() + SECONDSPERMINUTE*OOLSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL));
			SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)STRING(IDS_OOLSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS));
			pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | OOL_PRINT_ATTIME) & ~(OOL_PRINT_REPEATBYINTERVAL | OOL_PRINT_REPEATSTOPBYCOUNT | OOL_PRINT_REPEATSTOPBYTIME));
			pJobInfo->SetPrintAtTime(tTime);
		}
		else
		{
			SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_OOLSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS)));
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~(OOL_PRINT_ATTIME | OOL_PRINT_REPEATBYINTERVAL | OOL_PRINT_REPEATSTOPBYCOUNT | OOL_PRINT_REPEATSTOPBYTIME));
		}
		SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_SETCURSEL, (IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) ? (WPARAM)SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)((IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME)) ? STRING(IDS_OOLSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS) : STRING(IDS_OOLSETTINGS_PRINTJOBSPAGE_DAILYPRINTS))) : (WPARAM)-1);
		Spinbox_SetRange(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), (IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME)) ? (OOLSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES + 1) : OOLSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES, OOLSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES);
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME));
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		SetJobRepetitionInfo();
	}
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsPrintJobsPage::OnPrintAtDailyTime()
{
	CTimeKey  tTime;
	COOLPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		if (IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME))
		{
			Timespinbox_SetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME), (tTime = CTime::GetCurrentTime().GetTime() + SECONDSPERMINUTE*OOLSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL));
			SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)STRING(IDS_OOLSETTINGS_PRINTJOBSPAGE_DAILYPRINTS));
			pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | OOL_PRINT_ATDAILYTIME) & ~(OOL_PRINT_DAILYREPEATSTOPBYCOUNT | OOL_PRINT_DAILYREPEATSTOPBYTIME));
			pJobInfo->SetPrintAtDailyTime(tTime.GetTime() % SECONDSPERDAY);
		}
		else
		{
			SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_OOLSETTINGS_PRINTJOBSPAGE_DAILYPRINTS)));
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~(OOL_PRINT_ATDAILYTIME | OOL_PRINT_DAILYREPEATSTOPBYCOUNT | OOL_PRINT_DAILYREPEATSTOPBYTIME));
		}
		SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_SETCURSEL, (IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) ? (WPARAM)SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)((IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) ? STRING(IDS_OOLSETTINGS_PRINTJOBSPAGE_DAILYPRINTS) : STRING(IDS_OOLSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS))) : (WPARAM)-1);
		Spinbox_SetRange(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), (IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) ? OOLSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES : (OOLSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES + 1), OOLSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES);
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		SetJobRepetitionInfo();
	}
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsPrintJobsPage::OnPrintAtEvent()
{
	CString  szEvent;
	COOLPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		if (IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT))
		{
			SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_SETCURSEL);
			GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT)->GetWindowText(szEvent);
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() | OOL_PRINT_ATEVENT);
			pJobInfo->SetPrintAtEvent(szEvent);
		}
		else
		{
			SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_SETCURSEL, (WPARAM)-1);
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~OOL_PRINT_ATEVENT);
			pJobInfo->SetPrintAtEvent(EMPTYSTRING);
		}
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT));
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT));
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsPrintJobsPage::OnSelchangeEvent()
{
	CString  szEvent;
	COOLPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT)->GetWindowText(szEvent);
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() | OOL_PRINT_ATEVENT);
		pJobInfo->SetPrintAtEvent(szEvent);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsPrintJobsPage::OnSelchangeRepetitionType()
{
	Spinbox_SetRange(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), (GetJobRepetitionType() == OOLSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY) ? (OOLSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES + 1) : OOLSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES, OOLSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES);
	SetJobRepetitionInfo();
}

void COOLSettingsPrintJobsPage::OnRepeatByTime()
{
	COOLPrintJobInfo  *pJobInfo;

	for (CheckDlgButton(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME, !IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)); IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME); )
	{
		Spinbox_SetPos(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME), OOLSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL);
		break;
	}
	for (; (pJobInfo = FindJobInfo()); )
	{
		if (IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME))
		{
			pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | OOL_PRINT_REPEATBYINTERVAL) & ~(OOL_PRINT_REPEATSTOPBYCOUNT | OOL_PRINT_REPEATSTOPBYTIME));
			pJobInfo->SetPrintAtTime(Timespinbox_GetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), SECONDSPERMINUTE*OOLSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL);
			GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
			break;
		}
		pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~(OOL_PRINT_REPEATBYINTERVAL | OOL_PRINT_REPEATSTOPBYCOUNT | OOL_PRINT_REPEATSTOPBYTIME));
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		break;
	}
	CheckDlgButton(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, FALSE);
	CheckDlgButton(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsPrintJobsPage::OnRepetitionStopByCopies()
{
	COOLPrintJobInfo  *pJobInfo;

	for (CheckDlgButton(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, !IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)), GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)), GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)); IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES); )
	{
		Spinbox_SetPos(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), OOLSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTCOPIES);
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow(FALSE);
		CheckDlgButton(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, FALSE);
		break;
	}
	for (; (pJobInfo = FindJobInfo()); )
	{
		if (IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES))
		{
			if (GetJobRepetitionType() == OOLSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY)
			{
				pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | OOL_PRINT_REPEATSTOPBYCOUNT) & ~OOL_PRINT_REPEATSTOPBYTIME);
				pJobInfo->SetPrintAtTime(Timespinbox_GetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)), OOLSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTCOPIES);
			}
			if (GetJobRepetitionType() == OOLSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY)
			{
				pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | OOL_PRINT_DAILYREPEATSTOPBYCOUNT) & ~OOL_PRINT_DAILYREPEATSTOPBYTIME);
				pJobInfo->SetPrintAtDailyTime(Timespinbox_GetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)).GetTime() % SECONDSPERDAY, OOLSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTCOPIES);
			}
			GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
			break;
		}
		pJobInfo->SetPrintMode((GetJobRepetitionType() == OOLSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY) ? (pJobInfo->GetPrintMode() & ~OOL_PRINT_REPEATSTOPBYCOUNT) : (pJobInfo->GetPrintMode() & ~OOL_PRINT_DAILYREPEATSTOPBYCOUNT));
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		break;
	}
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsPrintJobsPage::OnRepetitionStopByTime()
{
	CTimeKey  tStopTime;
	COOLPrintJobInfo  *pJobInfo;

	for (CheckDlgButton(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, !IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)), GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)); IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME); )
	{
		for (CheckDlgButton(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, FALSE); GetJobRepetitionType() == OOLSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY; )
		{
			Timespinbox_SetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)).GetTime() + SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME))));
			break;
		}
		if (GetJobRepetitionType() == OOLSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY) Timespinbox_SetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)).GetTime() + CTimeSpan(1, 0, 0, 0).GetTotalSeconds()));
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow(FALSE);
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow(FALSE);
		break;
	}
	for (; (pJobInfo = FindJobInfo()); )
	{
		if (IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME))
		{
			if (GetJobRepetitionType() == OOLSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY)
			{
				pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | OOL_PRINT_REPEATSTOPBYTIME) & ~OOL_PRINT_REPEATSTOPBYCOUNT);
				pJobInfo->SetPrintAtTime(Timespinbox_GetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)), tStopTime);
			}
			if (GetJobRepetitionType() == OOLSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY)
			{
				pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | OOL_PRINT_DAILYREPEATSTOPBYTIME) & ~OOL_PRINT_DAILYREPEATSTOPBYCOUNT);
				pJobInfo->SetPrintAtDailyTime(Timespinbox_GetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)).GetTime() % SECONDSPERDAY, tStopTime);
			}
			GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
			break;
		}
		pJobInfo->SetPrintMode((GetJobRepetitionType() == OOLSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY) ? (pJobInfo->GetPrintMode() & ~OOL_PRINT_REPEATSTOPBYTIME) : (pJobInfo->GetPrintMode() & ~OOL_PRINT_DAILYREPEATSTOPBYTIME));
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		break;
	}
	GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsPrintJobsPage::OnSpinchangePrintTime()
{
	UINT  nStopCount;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeKey  tPrintTime;
	CTimeKey  tPrintStopTime;
	CTimeSpan  tPrintInterval;
	COOLPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)); pJobInfo->GetPrintAtTime(tPrintTime); )
		{
			pJobInfo->SetPrintAtTime(tTime);
			break;
		}
		if (pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval)) pJobInfo->SetPrintAtTime(tTime, tPrintInterval);
		if (pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, nStopCount)) pJobInfo->SetPrintAtTime(tTime, tPrintInterval, nStopCount);
		if (pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, tPrintStopTime)) pJobInfo->SetPrintAtTime(tTime, tPrintInterval, (tTime + tPrintInterval.GetTotalSeconds() > tPrintStopTime.GetTime()) ? CTimeKey(tTime.GetTime() + tPrintInterval.GetTotalSeconds()) : tPrintStopTime);
		Timespinbox_SetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (GetJobRepetitionType() == OOLSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)) ? ((tTime + tPrintInterval.GetTotalSeconds() > tPrintStopTime.GetTime()) ? (tTime.GetTime() + tPrintInterval.GetTotalSeconds()) : tPrintStopTime) : tStopTime);
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsPrintJobsPage::OnSpinchangePrintDailyTime()
{
	UINT  nStopCount;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeKey  tPrintStopTime;
	CTimeSpan  tPrintTime;
	COOLPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)), tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)); pJobInfo->GetPrintAtDailyTime(tPrintTime); )
		{
			pJobInfo->SetPrintAtDailyTime(tTime.GetTime() % SECONDSPERDAY);
			break;
		}
		if (pJobInfo->GetPrintAtDailyTime(tPrintTime, nStopCount)) pJobInfo->SetPrintAtDailyTime(tTime.GetTime() % SECONDSPERDAY, nStopCount);
		if (pJobInfo->GetPrintAtDailyTime(tPrintTime, tPrintStopTime)) pJobInfo->SetPrintAtDailyTime(tTime.GetTime() % SECONDSPERDAY, (SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + tTime.GetTime() % SECONDSPERDAY > tPrintStopTime.GetTime()) ? CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY + 1) + tTime.GetTime() % SECONDSPERDAY) : tPrintStopTime);
		Timespinbox_SetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (GetJobRepetitionType() == OOLSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)) ? ((SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + tTime.GetTime() % SECONDSPERDAY > tPrintStopTime.GetTime()) ? CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY + 1) + tTime.GetTime() % SECONDSPERDAY) : tPrintStopTime) : tStopTime);
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsPrintJobsPage::OnSpinchangeRepeatTime()
{
	UINT  nStopCount;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeKey  tPrintTime;
	CTimeKey  tPrintStopTime;
	CTimeSpan  tPrintInterval;
	COOLPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)); pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval); )
		{
			pJobInfo->SetPrintAtTime(tPrintTime, SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)));
			break;
		}
		if (pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, nStopCount)) pJobInfo->SetPrintAtTime(tPrintTime, SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)), nStopCount);
		if (pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, tPrintStopTime)) pJobInfo->SetPrintAtTime(tPrintTime, SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)), (tPrintTime.GetTime() + SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)) > tPrintStopTime.GetTime()) ? CTimeKey(tPrintTime.GetTime() + SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME))) : tPrintStopTime);
		Timespinbox_SetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (GetJobRepetitionType() == OOLSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  IsDlgButtonChecked(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)) ? ((tPrintTime.GetTime() + SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)) > tPrintStopTime.GetTime()) ? CTimeKey(tPrintTime.GetTime() + SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME))) : tPrintStopTime) : tStopTime);
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsPrintJobsPage::OnSpinchangeRepetitionStopCopies()
{
	UINT  nStopCount;
	UINT  nPrintStopCount;
	CTimeKey  tPrintTime;
	CTimeSpan  tPrintInterval;
	CTimeSpan  tPrintDailyTime;
	COOLPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (nStopCount = (UINT)Spinbox_GetPos(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)); GetJobRepetitionType() == OOLSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY && pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, nPrintStopCount); )
		{
			pJobInfo->SetPrintAtTime(tPrintTime, tPrintInterval, nStopCount);
			break;
		}
		if (GetJobRepetitionType() == OOLSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  pJobInfo->GetPrintAtDailyTime(tPrintDailyTime, nPrintStopCount)) pJobInfo->SetPrintAtDailyTime(tPrintDailyTime, nStopCount);
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLSettingsPrintJobsPage::OnSpinchangeRepetitionStopTime()
{
	CTimeKey  tTime;
	CTimeKey  tTimeKey;
	CTimeKey  tStopTime;
	CTimeKey  tPrintTime;
	CTimeKey  tPrintStopTime;
	CTimeSpan  tPrintInterval;
	CTimeSpan  tPrintDailyTime;
	COOLPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)); GetJobRepetitionType() == OOLSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY && pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, tPrintStopTime); )
		{
			if (tTime > tStopTime.GetTime() - tPrintInterval.GetTotalSeconds()) Timespinbox_SetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (tStopTime = tTime.GetTime() + tPrintInterval.GetTotalSeconds()));
			pJobInfo->SetPrintAtTime(tTime, tPrintInterval, tStopTime);
			break;
		}
		if (GetJobRepetitionType() == OOLSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  pJobInfo->GetPrintAtDailyTime(tPrintDailyTime, tPrintStopTime))
		{
			if (SECONDSPERDAY*(tTimeKey.GetTime() / SECONDSPERDAY) + tPrintDailyTime.GetTotalSeconds() > tStopTime.GetTime()) Timespinbox_SetTime(GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (tStopTime = SECONDSPERDAY*(tTimeKey.GetTime() / SECONDSPERDAY) + tPrintDailyTime.GetTotalSeconds()));
			pJobInfo->SetPrintAtDailyTime(tPrintDailyTime, tStopTime);
		}
		GetDlgItem(IDC_OOLSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_OOLSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// COOLSettingsTabCtrl

IMPLEMENT_DYNCREATE(COOLSettingsTabCtrl, CTabCtrl)

BEGIN_MESSAGE_MAP(COOLSettingsTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(COOLSettingsTabCtrl)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COOLSettingsTabCtrl message handlers


/////////////////////////////////////////////////////////////////////////////
// COOLSettingsDialog

IMPLEMENT_DYNCREATE(COOLSettingsDialog, CDisplayPropertySheetDialog)

COOLSettingsDialog::COOLSettingsDialog() : CDisplayPropertySheetDialog()
{
	AddPage(&m_pageLayout);
	AddPage(&m_pageFiltering);
	AddPage(&m_pageRetrieving);
	AddPage(&m_pagePrinting);
	AddPage(&m_pagePrintJobs);
}

BOOL COOLSettingsDialog::GetLayout(CUIntArray &nColumns) CONST
{
	return m_pageLayout.GetLayout(nColumns);
}

BOOL COOLSettingsDialog::GetLayoutTitleFont(LPLOGFONT pTitleFont) CONST
{
	return m_pageLayout.GetTitleFont(pTitleFont);
}

BOOL COOLSettingsDialog::GetLayoutItemsFont(LPLOGFONT pItemsFont) CONST
{
	return m_pageLayout.GetItemsFont(pItemsFont);
}

BOOL COOLSettingsDialog::GetLayoutInvalidDataMode(BOOL &bEnable) CONST
{
	return m_pageLayout.GetInvalidDataMode(bEnable);
}

BOOL COOLSettingsDialog::GetLayoutBadDataMode(BOOL &bEnable) CONST
{
	return m_pageLayout.GetBadDataMode(bEnable);
}

BOOL COOLSettingsDialog::GetLayoutToolTipMode(BOOL &bEnable) CONST
{
	return m_pageLayout.GetToolTipMode(bEnable);
}

BOOL COOLSettingsDialog::IsLayoutModified() CONST
{
	return m_pageLayout.IsModified();
}

BOOL COOLSettingsDialog::GetParameterFilters(COOLParameterFilters &pFilters) CONST
{
	return m_pageFiltering.GetFilters(pFilters);
}

BOOL COOLSettingsDialog::GetFilterColors(CUIntArray &nColors) CONST
{
	return m_pageFiltering.GetColors(nColors);
}

BOOL COOLSettingsDialog::IsFilteringModified() CONST
{
	return m_pageFiltering.IsModified();
}

BOOL COOLSettingsDialog::GetRetrieveFileName(CString &szFileName) CONST
{
	return m_pageRetrieving.GetDataSourceFileName(szFileName);
}

BOOL COOLSettingsDialog::IsRetrievingModified() CONST
{
	return m_pageRetrieving.IsModified();
}

BOOL COOLSettingsDialog::GetPrintJobs(COOLPrintJobs &pPrintJobs) CONST
{
	return(((GetActivePage()->GetSafeHwnd() != m_pagePrintJobs.GetSafeHwnd() && m_pagePrinting.GetJobs(pPrintJobs)) || (GetActivePage()->GetSafeHwnd() == m_pagePrintJobs.GetSafeHwnd() && m_pagePrintJobs.GetJobs(pPrintJobs))) ? TRUE : FALSE);
}

BOOL COOLSettingsDialog::IsPrintingModified() CONST
{
	return m_pagePrinting.IsModified() || m_pagePrintJobs.IsModified();
}

COOLOpenDialog *COOLSettingsDialog::GetParentDialog() CONST
{
	return((GetParent() != (CWnd *)GetParentDisplay()) ? (COOLOpenDialog *)GetParent() : (COOLOpenDialog *)NULL);
}

COOLWnd *COOLSettingsDialog::GetParentDisplay() CONST
{
	return((COOLWnd *)CDisplayPropertySheetDialog::GetParentDisplay());
}

BEGIN_MESSAGE_MAP(COOLSettingsDialog, CDisplayPropertySheetDialog)
	//{{AFX_MSG_MAP(COOLSettingsDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDHELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COOLSettingsDialog message handlers

BOOL COOLSettingsDialog::OnInitDialog()
{
	INT  nPage;
	INT  nPages;
	CHourglassCursor  cCursor;

	CDisplayPropertySheetDialog::OnInitDialog();
	SetTitle(STRING(IDS_OOLSETTINGSDIALOG_TITLE));
	for (nPage = 0, nPages = GetPageCount(), m_wndTabCtrl.SubclassWindow(GetTabControl()->GetSafeHwnd()); nPage < nPages; nPage++)
	{
		SetActivePage((nPage + 1) % nPages);
		continue;
	}
	m_wndTabCtrl.SetFocus();
	return FALSE;
}

BOOL COOLSettingsDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	CRect  rTab;
	COOLPrintJobs  pPrintJobs;
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

BOOL COOLSettingsDialog::OnDataExchange(HWND hPage, CONST COOLPrintJobs &pJobs)
{
	return(((hPage == m_pagePrinting.GetSafeHwnd() && m_pagePrintJobs.OnDataExchange(pJobs)) || (hPage == m_pagePrintJobs.GetSafeHwnd() && m_pagePrinting.OnDataExchange(pJobs))) ? TRUE : FALSE);
}

void COOLSettingsDialog::OnOK()
{
	CHourglassCursor  cCursor;

	ReportEvent(((!GetParentDialog() && !GetParentDisplay()->OnCloseSettingsDialog(IDOK)) || (GetParentDialog() && !GetParentDialog()->OnCloseSettingsDialog(IDOK))) ? SYSTEM_WARNING_OOL_SETUP_FAILURE : SYSTEM_NOERROR);
	CDisplayPropertySheetDialog::OnOK();
}

void COOLSettingsDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	if (!GetParentDialog()) GetParentDisplay()->OnCloseSettingsDialog(IDCANCEL);
	else  GetParentDialog()->OnCloseSettingsDialog(IDCANCEL);
	CDisplayPropertySheetDialog::OnCancel();
}

BOOL COOLSettingsDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_OOLSETTINGSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void COOLSettingsDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_OOLSETTINGSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// COOLLinkagesDialog dialog

IMPLEMENT_DYNCREATE(COOLLinkagesDialog, CDisplayDialog)

COOLLinkagesDialog::COOLLinkagesDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(COOLLinkagesDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT COOLLinkagesDialog::Create(CWnd *pParentWnd)
{
	return CDisplayDialog::Create(pParentWnd, COOLLinkagesDialog::IDD);
}

BOOL COOLLinkagesDialog::Initialize()
{
	GetDisplayArea()->EnumDisplays(m_pDisplays[0]);
	GetParent()->GetLinks(m_pDisplays[1]);
	return TRUE;
}

COOLWnd *COOLLinkagesDialog::GetParent() CONST
{
	return((COOLWnd *)CDisplayDialog::GetParent());
}

BOOL COOLLinkagesDialog::EnumDisplays()
{
	INT  nDisplay[2];
	INT  nDisplays[2];
	CString  szDisplay;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay[0] = 0, nDisplays[0] = (INT)m_pDisplays[0].GetSize(), SendDlgItemMessage(IDC_OOL_LINKAGES_DISPLAYS, CB_RESETCONTENT), SendDlgItemMessage(IDC_OOL_LINKAGES_LIST, LB_RESETCONTENT); nDisplay[0] < nDisplays[0]; nDisplay[0]++)
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
			for (pDisplayWnd->GetWindowText(szDisplay); SendDlgItemMessage(IDC_OOL_LINKAGES_DISPLAYS, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szDisplay) < 0 && !szDisplay.IsEmpty(); )
			{
				SendDlgItemMessage(IDC_OOL_LINKAGES_DISPLAYS, CB_INSERTSTRING, nDisplay[0], (LPARAM)(LPCTSTR)szDisplay);
				break;
			}
		}
	}
	for (nDisplay[1] = 0, nDisplays[1] = (INT)m_pDisplays[1].GetSize(), m_pDisplays[2].Copy(m_pDisplays[1]); nDisplay[1] < nDisplays[1]; nDisplay[1]++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)m_pDisplays[1].GetAt(nDisplay[1])) != (CDisplayWnd *)NULL)
		{
			for (pDisplayWnd->GetWindowText(szDisplay); SendDlgItemMessage(IDC_OOL_LINKAGES_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szDisplay) < 0 && !szDisplay.IsEmpty(); )
			{
				SendDlgItemMessage(IDC_OOL_LINKAGES_LIST, LB_INSERTSTRING, nDisplay[1], (LPARAM)(LPCTSTR)szDisplay);
				break;
			}
		}
	}
	SendDlgItemMessage(IDC_OOL_LINKAGES_LIST, LB_SETCURSEL);
	SendDlgItemMessage(IDC_OOL_LINKAGES_DISPLAYS, CB_SETCURSEL);
	GetDlgItem(IDC_OOL_LINKAGES_DISPLAYS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_OOL_LINKAGES_DISPLAYS, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOL_LINKAGES_DISPLAYS)->EnableWindow((SendDlgItemMessage(IDC_OOL_LINKAGES_DISPLAYS, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOL_LINKAGES_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_OOL_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOL_LINKAGES_LIST)->EnableWindow((SendDlgItemMessage(IDC_OOL_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOL_LINKAGES_ADD)->EnableWindow((SendDlgItemMessage(IDC_OOL_LINKAGES_DISPLAYS, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOL_LINKAGES_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_OOL_LINKAGES_LIST, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOL_LINKAGES_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_OOL_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	return TRUE;
}

INT COOLLinkagesDialog::FindDisplay(LPCTSTR pszName, BOOL bLinked) CONST
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

BOOL COOLLinkagesDialog::IsModified() CONST
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

BOOL COOLLinkagesDialog::Check(BOOL bModified) CONST
{
	return(!bModified || IsModified());
}

void COOLLinkagesDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COOLLinkagesDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void COOLLinkagesDialog::PostNcDestroy()
{
	m_pDisplays[0].RemoveAll();
	m_pDisplays[1].RemoveAll();
	m_pDisplays[2].RemoveAll();
	CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(COOLLinkagesDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(COOLLinkagesDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_OOL_LINKAGES_ADD, OnAddDisplay)
	ON_BN_CLICKED(IDC_OOL_LINKAGES_REMOVE, OnRemoveLinkedDisplay)
	ON_BN_CLICKED(IDC_OOL_LINKAGES_REMOVEALL, OnRemoveAllLinkedDisplays)
	ON_BN_CLICKED(IDC_OOL_LINKAGES_HELP, OnHelp)
	ON_LBN_SELCHANGE(IDC_OOL_LINKAGES_LIST, OnSelchangeLinkedDisplay)
	ON_CBN_EDITCHANGE(IDC_OOL_LINKAGES_DISPLAYS, OnEditchangeDisplay)
	ON_CBN_SELCHANGE(IDC_OOL_LINKAGES_DISPLAYS, OnSelchangeDisplay)
	ON_CBN_DBLCLK(IDC_OOL_LINKAGES_DISPLAYS, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COOLLinkagesDialog message handlers

BOOL COOLLinkagesDialog::OnInitDialog()
{
	CString  szDisplay;
	CHourglassCursor  cCursor;

	for (CDisplayDialog::OnInitDialog(), GetParent()->GetWindowText(szDisplay); EnumDisplays(); )
	{
		GetDlgItem(IDC_OOL_LINKAGES_NAME)->SetWindowText(szDisplay);
		GetDlgItem(IDC_OOL_LINKAGES_DETAILS)->EnableWindow();
		GetDlgItem(IDC_OOL_LINKAGES_NAME_STATIC)->EnableWindow();
		GetDlgItem(IDC_OOL_LINKAGES_NAME)->EnableWindow();
		GetDlgItem(IDC_OOL_LINKAGES_DISPLAYS)->SetFocus();
		return FALSE;
	}
	return TRUE;
}

void COOLLinkagesDialog::OnAddDisplay()
{
	INT  nIndex[2];
	CString  szDisplay;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_OOL_LINKAGES_DISPLAYS)->GetWindowText(szDisplay); (nIndex[0] = FindDisplay(szDisplay)) >= 0; )
	{
		if ((nIndex[1] = (INT)SendDlgItemMessage(IDC_OOL_LINKAGES_LIST, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szDisplay)) >= 0)
		{
			for (SendDlgItemMessage(IDC_OOL_LINKAGES_LIST, LB_SETCURSEL, nIndex[1]); SendDlgItemMessage(IDC_OOL_LINKAGES_DISPLAYS, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_OOL_LINKAGES_DISPLAYS, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szDisplay)) >= 0; )
			{
				m_pDisplays[1].Add(m_pDisplays[0].GetAt(nIndex[0]));
				m_pDisplays[0].RemoveAt(nIndex[0]);
				break;
			}
			SendDlgItemMessage(IDC_OOL_LINKAGES_DISPLAYS, CB_SETCURSEL);
			GetDlgItem(IDC_OOL_LINKAGES_ADD)->EnableWindow((SendDlgItemMessage(IDC_OOL_LINKAGES_DISPLAYS, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
			GetDlgItem(IDC_OOL_LINKAGES_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_OOL_LINKAGES_LIST, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
			GetDlgItem(IDC_OOL_LINKAGES_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_OOL_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_OOL_LINKAGES_DISPLAYS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_OOL_LINKAGES_DISPLAYS, CB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_OOL_LINKAGES_DISPLAYS)->EnableWindow((SendDlgItemMessage(IDC_OOL_LINKAGES_DISPLAYS, CB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_OOL_LINKAGES_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_OOL_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_OOL_LINKAGES_LIST)->EnableWindow((SendDlgItemMessage(IDC_OOL_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_OOL_LINKAGES_LIST)->SetFocus();
		}
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLLinkagesDialog::OnRemoveLinkedDisplay()
{
	INT  nIndex[2];
	CString  szDisplay;
	CHourglassCursor  cCursor;

	for (szDisplay = Listbox_GetText(GetDlgItem(IDC_OOL_LINKAGES_LIST), (INT)SendDlgItemMessage(IDC_OOL_LINKAGES_LIST, LB_GETCURSEL)); (nIndex[0] = FindDisplay(szDisplay, TRUE)) >= 0; )
	{
		if ((nIndex[1] = (INT)SendDlgItemMessage(IDC_OOL_LINKAGES_DISPLAYS, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szDisplay)) >= 0)
		{
			for (SendDlgItemMessage(IDC_OOL_LINKAGES_DISPLAYS, CB_SETCURSEL, nIndex[1]); SendDlgItemMessage(IDC_OOL_LINKAGES_LIST, LB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_OOL_LINKAGES_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szDisplay)) >= 0; )
			{
				m_pDisplays[0].Add(m_pDisplays[1].GetAt(nIndex[0]));
				m_pDisplays[1].RemoveAt(nIndex[0]);
				break;
			}
			SendDlgItemMessage(IDC_OOL_LINKAGES_LIST, LB_SETCURSEL);
			GetDlgItem(IDC_OOL_LINKAGES_ADD)->EnableWindow((SendDlgItemMessage(IDC_OOL_LINKAGES_DISPLAYS, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
			GetDlgItem(IDC_OOL_LINKAGES_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_OOL_LINKAGES_LIST, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
			GetDlgItem(IDC_OOL_LINKAGES_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_OOL_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_OOL_LINKAGES_DISPLAYS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_OOL_LINKAGES_DISPLAYS, CB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_OOL_LINKAGES_DISPLAYS)->EnableWindow((SendDlgItemMessage(IDC_OOL_LINKAGES_DISPLAYS, CB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_OOL_LINKAGES_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_OOL_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_OOL_LINKAGES_LIST)->EnableWindow((SendDlgItemMessage(IDC_OOL_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_OOL_LINKAGES_DISPLAYS)->SetFocus();
		}
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLLinkagesDialog::OnRemoveAllLinkedDisplays()
{
	INT  nDisplay;
	INT  nDisplays;
	CHourglassCursor  cCursor;

	for (nDisplay = 0, nDisplays = (INT)SendDlgItemMessage(IDC_OOL_LINKAGES_LIST, LB_GETCOUNT), m_pDisplays[0].Append(m_pDisplays[1]), m_pDisplays[1].RemoveAll(); nDisplay < nDisplays; nDisplay++)
	{
		if (SendDlgItemMessage(IDC_OOL_LINKAGES_DISPLAYS, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)Listbox_GetText(GetDlgItem(IDC_OOL_LINKAGES_LIST), nDisplay)) >= 0)
		{
			SendDlgItemMessage(IDC_OOL_LINKAGES_LIST, LB_DELETESTRING, nDisplay);
			nDisplays--;
			nDisplay--;
		}
	}
	SendDlgItemMessage(IDC_OOL_LINKAGES_LIST, LB_SETCURSEL);
	SendDlgItemMessage(IDC_OOL_LINKAGES_DISPLAYS, CB_SETCURSEL);
	GetDlgItem(IDC_OOL_LINKAGES_ADD)->EnableWindow((SendDlgItemMessage(IDC_OOL_LINKAGES_DISPLAYS, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOL_LINKAGES_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_OOL_LINKAGES_LIST, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOL_LINKAGES_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_OOL_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOL_LINKAGES_DISPLAYS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_OOL_LINKAGES_DISPLAYS, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOL_LINKAGES_DISPLAYS)->EnableWindow((SendDlgItemMessage(IDC_OOL_LINKAGES_DISPLAYS, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOL_LINKAGES_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_OOL_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOL_LINKAGES_LIST)->EnableWindow((SendDlgItemMessage(IDC_OOL_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOL_LINKAGES_DISPLAYS)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLLinkagesDialog::OnEditchangeDisplay()
{
	CString  szDisplay;

	GetDlgItem(IDC_OOL_LINKAGES_DISPLAYS)->GetWindowText(szDisplay);
	GetDlgItem(IDC_OOL_LINKAGES_ADD)->EnableWindow((SendDlgItemMessage(IDC_OOL_LINKAGES_DISPLAYS, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szDisplay) >= 0 && SendDlgItemMessage(IDC_OOL_LINKAGES_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szDisplay) < 0) ? TRUE : FALSE);
}

void COOLLinkagesDialog::OnSelchangeDisplay()
{
	GetDlgItem(IDC_OOL_LINKAGES_ADD)->EnableWindow();
}

void COOLLinkagesDialog::OnSelchangeLinkedDisplay()
{
	GetDlgItem(IDC_OOL_LINKAGES_REMOVE)->EnableWindow();
}

void COOLLinkagesDialog::OnOK()
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

BOOL COOLLinkagesDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_OOLLINKAGESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void COOLLinkagesDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_OOLLINKAGESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// COOLParametersLimitsPage property page

IMPLEMENT_DYNCREATE(COOLParametersLimitsPage, CLocalePropertyPage)

COOLParametersLimitsPage::COOLParametersLimitsPage() : CLocalePropertyPage(COOLParametersLimitsPage::IDD)
{
	//{{AFX_DATA_INIT(COOLParametersLimitsPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

VOID COOLParametersLimitsPage::ShowParameterInfo(CONST COolParameter *pOolParameter)
{
	INT  nTable;
	INT  nTables;
	WORD  wTable;
	WORD  wLimit;
	CString  szUnit;
	CTimeTag  tUnit;
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CDatabaseTMNumOolTable  *pDatabaseTMNumOolTable;
	CDatabaseTMTxtOolTable  *pDatabaseTMTxtOolTable;

	SendDlgItemMessage(IDC_OOL_PARAMETERS_LIMITSPAGE_NAME, CB_RESETCONTENT);
	if ((pDatabaseTMParameter = (pOolParameter != (CONST COolParameter *) NULL) ? GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pOolParameter->GetTag())) : (CDatabaseTMParameter *)NULL))
	{
		for (nTable = 0, nTables = pDatabaseTMParameter->GetOolTableRefs(m_nOolTableRefs, m_nOolValidityRefs); nTable < nTables; nTable = nTable + 1)
		{
			if ((m_nOolTableType = (pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS))) != TMPARAMETER_CALIBRATION_STATUS)
			{
				if ((pDatabaseTMNumOolTable = GetDatabase()->GetTMNumOolTables()->GetAt(m_nOolTableRefs.GetAt(nTable))))
				{
					SendDlgItemMessage(IDC_OOL_PARAMETERS_LIMITSPAGE_NAME, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)pDatabaseTMNumOolTable->GetName());
					continue;
				}
			}
			if (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS)
			{
				if ((pDatabaseTMTxtOolTable = GetDatabase()->GetTMTxtOolTables()->GetAt(m_nOolTableRefs.GetAt(nTable))))
				{
					SendDlgItemMessage(IDC_OOL_PARAMETERS_LIMITSPAGE_NAME, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)pDatabaseTMTxtOolTable->GetName());
					continue;
				}
			}
		}
		if (pOolParameter->GetOolInfo(szUnit, tUnit, wTable, wLimit) && SendDlgItemMessage(IDC_OOL_PARAMETERS_LIMITSPAGE_NAME, CB_SETCURSEL, wTable) == wTable)
		{
			m_nOolTableID = wTable;
			m_nOolLimitID = wLimit;
		}
		else
		{
			SendDlgItemMessage(IDC_OOL_PARAMETERS_LIMITSPAGE_NAME, CB_SETCURSEL);
			m_nOolTableID = 0;
			m_nOolLimitID = -1;
		}
	}
	GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_NAME_STATIC)->EnableWindow((SendDlgItemMessage(IDC_OOL_PARAMETERS_LIMITSPAGE_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_NAME)->EnableWindow((SendDlgItemMessage(IDC_OOL_PARAMETERS_LIMITSPAGE_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	ShowLimitsInfo();
}

VOID COOLParametersLimitsPage::ShowLimitsInfo()
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	INT  nCount;
	INT  nColumn;
	INT  nColumns;
	UINT  nOolType;
	double  fLimitRange[2];
	CString  szItem;
	CString  szTable;
	CString  szLimitDelta;
	CString  szLimitRange[2];
	CStringTools  cStringTools;
	CDatabaseTMNumOolTable  *pDatabaseTMNumOolTable;
	CDatabaseTMNumOolLimit  *pDatabaseTMNumOolLimit;
	CDatabaseTMTxtOolTable  *pDatabaseTMTxtOolTable;
	CDatabaseTMTxtOolLimit  *pDatabaseTMTxtOolLimit;

	SendDlgItemMessage(IDC_OOL_PARAMETERS_LIMITSPAGE_LIMITS, LVM_DELETEALLITEMS);
	if ((nIndex = (INT)SendDlgItemMessage(IDC_OOL_PARAMETERS_LIMITSPAGE_NAME, CB_GETCURSEL)) >= 0 && nIndex < m_nOolTableRefs.GetSize())
	{
		if ((pDatabaseTMNumOolTable = (m_nOolTableType == TMPARAMETER_CALIBRATION_NONE || m_nOolTableType == TMPARAMETER_CALIBRATION_NUMERICAL) ? GetDatabase()->GetTMNumOolTables()->GetAt(m_nOolTableRefs.GetAt(nIndex)) : (CDatabaseTMNumOolTable *)NULL))
		{
			for (nItem = 0, nItems = (INT)pDatabaseTMNumOolTable->GetSize(), szTable = cStringTools.ConvertUIntToPaddedString(m_nOolTableRefs.GetAt(nIndex), (INT)ceil(log10((double)GetDatabase()->GetTMNumOolTables()->GetSize()))), nCount = 0; nItem < nItems; nItem++)
			{
				if ((pDatabaseTMNumOolLimit = pDatabaseTMNumOolTable->GetAt(nItem)) && pDatabaseTMNumOolLimit->GetType() != TMOOLLIMIT_TYPE_STATUSCONSISTENCY  &&  pDatabaseTMNumOolLimit->GetType() != TMOOLLIMIT_TYPE_EVENT)
				{
					for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
					{
						for (szItem.Empty(); m_szColumns.GetAt(nColumn) == STRING(IDS_OOLPARAMETERS_LIMITSPAGE_TITLEITEM_NUMBER); )
						{
							szItem = (nItem == m_nOolLimitID) ? (cStringTools.ConvertIntToString(nCount + 1) + STRING(IDS_OOLPARAMETERS_LIMITSPAGE_LIMIT_FLAG)) : cStringTools.ConvertIntToString(nCount + 1);
							break;
						}
						if (m_szColumns.GetAt(nColumn) == STRING(IDS_OOLPARAMETERS_LIMITSPAGE_TITLEITEM_LIMIT))
						{
							for (; pDatabaseTMNumOolLimit->GetRange(nOolType, fLimitRange[0], fLimitRange[1]); )
							{
								if (!(pDatabaseTMNumOolTable->GetAttributes() & TMOOLTABLE_CODING_FLOATINGPOINT) && (pDatabaseTMNumOolTable->GetAttributes() & TMOOLTABLE_CHECK_RAW))
								{
									if (pDatabaseTMNumOolTable->GetAttributes() & TMOOLTABLE_CODING_SIGNEDINTEGER)
									{
										szLimitRange[0] = cStringTools.ConvertLongIntToString((LONGLONG)fLimitRange[0]);
										szLimitRange[1] = cStringTools.ConvertLongIntToString((LONGLONG)fLimitRange[1]);
									}
									else
									{
										szLimitRange[0] = cStringTools.ConvertLongUIntToString((ULONGLONG)fLimitRange[0]);
										szLimitRange[1] = cStringTools.ConvertLongUIntToString((ULONGLONG)fLimitRange[1]);
									}
								}
								else
								{
									szLimitRange[0] = cStringTools.ConvertFloatToString(fLimitRange[0]);
									szLimitRange[1] = cStringTools.ConvertFloatToString(fLimitRange[1]);
								}
								szItem.Format(STRING(IDS_OOLPARAMETERS_LIMITSPAGE_LIMIT_RANGE), (LPCTSTR)szLimitRange[0], (LPCTSTR)szLimitRange[1]);
								break;
							}
							for (; pDatabaseTMNumOolLimit->GetType() == TMOOLLIMIT_TYPE_DELTA; )
							{
								if (pDatabaseTMNumOolLimit->GetDelta(fLimitRange[0], TRUE) && pDatabaseTMNumOolLimit->GetDelta(fLimitRange[1], FALSE))
								{
									szLimitDelta.Format(STRING(IDS_OOLPARAMETERS_LIMITSPAGE_DELTA_MINMAX_FORMAT), (pDatabaseTMNumOolTable->GetAttributes() & TMOOLTABLE_CHECK_RAW) ? ((pDatabaseTMNumOolTable->GetAttributes() & TMOOLTABLE_CODING_UNSIGNEDINTEGER) ? (LPCTSTR)cStringTools.ConvertLongUIntToString((ULONGLONG)fLimitRange[0]) : ((pDatabaseTMNumOolTable->GetAttributes() & TMOOLTABLE_CODING_SIGNEDINTEGER) ? (LPCTSTR)cStringTools.ConvertLongIntToString((LONGLONG)fLimitRange[0]) : (LPCTSTR)cStringTools.ConvertFloatToString(fLimitRange[0]))) : (LPCTSTR)cStringTools.ConvertFloatToString(fLimitRange[0]), (pDatabaseTMNumOolTable->GetAttributes() & TMOOLTABLE_CHECK_RAW) ? ((pDatabaseTMNumOolTable->GetAttributes() & TMOOLTABLE_CODING_UNSIGNEDINTEGER) ? (LPCTSTR)cStringTools.ConvertLongUIntToString((ULONGLONG)fLimitRange[1]) : ((pDatabaseTMNumOolTable->GetAttributes() & TMOOLTABLE_CODING_SIGNEDINTEGER) ? (LPCTSTR)cStringTools.ConvertLongIntToString((LONGLONG)fLimitRange[1]) : (LPCTSTR)cStringTools.ConvertFloatToString(fLimitRange[1]))) : (LPCTSTR)cStringTools.ConvertFloatToString(fLimitRange[1]));
									szItem = szLimitDelta;
									break;
								}
								if (pDatabaseTMNumOolLimit->GetDelta(fLimitRange[0], TRUE))
								{
									szLimitDelta.Format(STRING(IDS_OOLPARAMETERS_LIMITSPAGE_DELTA_MIN_FORMAT), (pDatabaseTMNumOolTable->GetAttributes() & TMOOLTABLE_CHECK_RAW) ? ((pDatabaseTMNumOolTable->GetAttributes() & TMOOLTABLE_CODING_UNSIGNEDINTEGER) ? (LPCTSTR)cStringTools.ConvertLongUIntToString((ULONGLONG)fLimitRange[0]) : ((pDatabaseTMNumOolTable->GetAttributes() & TMOOLTABLE_CODING_SIGNEDINTEGER) ? (LPCTSTR)cStringTools.ConvertLongIntToString((LONGLONG)fLimitRange[0]) : (LPCTSTR)cStringTools.ConvertFloatToString(fLimitRange[0]))) : (LPCTSTR)cStringTools.ConvertFloatToString(fLimitRange[0]));
									szItem = szLimitDelta;
									break;
								}
								if (pDatabaseTMNumOolLimit->GetDelta(fLimitRange[1], FALSE))
								{
									szLimitDelta.Format(STRING(IDS_OOLPARAMETERS_LIMITSPAGE_DELTA_MAX_FORMAT), (pDatabaseTMNumOolTable->GetAttributes() & TMOOLTABLE_CHECK_RAW) ? ((pDatabaseTMNumOolTable->GetAttributes() & TMOOLTABLE_CODING_UNSIGNEDINTEGER) ? (LPCTSTR)cStringTools.ConvertLongUIntToString((ULONGLONG)fLimitRange[1]) : ((pDatabaseTMNumOolTable->GetAttributes() & TMOOLTABLE_CODING_SIGNEDINTEGER) ? (LPCTSTR)cStringTools.ConvertLongIntToString((LONGLONG)fLimitRange[1]) : (LPCTSTR)cStringTools.ConvertFloatToString(fLimitRange[1]))) : (LPCTSTR)cStringTools.ConvertFloatToString(fLimitRange[1]));
									szItem = szLimitDelta;
								}
								break;
							}
							if (!szItem.IsEmpty())
							{
								szItem += (nOolType == TMOOLLIMIT_TYPE_HARD) ? STRING(IDS_OOLPARAMETERS_LIMITSPAGE_LIMIT_HARD) : EMPTYSTRING;
								szItem += (nOolType == TMOOLLIMIT_TYPE_SOFT) ? STRING(IDS_OOLPARAMETERS_LIMITSPAGE_LIMIT_SOFT) : EMPTYSTRING;
								szItem += (nOolType == TMOOLLIMIT_TYPE_DELTA) ? STRING(IDS_OOLPARAMETERS_LIMITSPAGE_LIMIT_DELTA) : EMPTYSTRING;
							}
						}
						if (!nColumn)
						{
							Listview_InsertText(GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_LIMITS), nCount, szItem);
							nCount++;
							continue;
						}
						Listview_SetText(GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_LIMITS), nCount - 1, nColumn, szItem);
					}
				}
			}
			GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_ID)->SetWindowText(szTable);
			GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_TYPE)->SetWindowText(STRING(IDS_OOLPARAMETERS_LIMITSPAGE_TYPE_NUMERICAL));
			GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_STATUS)->SetWindowText((nIndex == m_nOolTableID) ? STRING(IDS_OOLPARAMETERS_LIMITSPAGE_STATUS_ACTIVE) : STRING(IDS_OOLPARAMETERS_LIMITSPAGE_STATUS_INACTIVE));
			GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_ID_STATIC)->EnableWindow((GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_ID)->EnableWindow((GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_TYPE_STATIC)->EnableWindow();
			GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_TYPE)->EnableWindow();
			GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_STATUS_STATIC)->EnableWindow();
			GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_STATUS)->EnableWindow();
			GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_LIMITS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_OOL_PARAMETERS_LIMITSPAGE_LIMITS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_LIMITS)->EnableWindow((SendDlgItemMessage(IDC_OOL_PARAMETERS_LIMITSPAGE_LIMITS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			return;
		}
		if ((pDatabaseTMTxtOolTable = (m_nOolTableType == TMPARAMETER_CALIBRATION_STATUS) ? GetDatabase()->GetTMTxtOolTables()->GetAt(m_nOolTableRefs.GetAt(nIndex)) : (CDatabaseTMTxtOolTable *)NULL))
		{
			for (nItem = 0, nItems = (INT)pDatabaseTMTxtOolTable->GetSize(), szTable = cStringTools.ConvertUIntToPaddedString(m_nOolTableRefs.GetAt(nIndex), (INT)ceil(log10((double)GetDatabase()->GetTMTxtOolTables()->GetSize()))); nItem < nItems; nItem++)
			{
				if ((pDatabaseTMTxtOolLimit = pDatabaseTMTxtOolTable->GetAt(nItem)))
				{
					for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn++)
					{
						for (szItem.Empty(); m_szColumns.GetAt(nColumn) == STRING(IDS_OOLPARAMETERS_LIMITSPAGE_TITLEITEM_NUMBER); )
						{
							szItem = (nItem == m_nOolLimitID) ? (cStringTools.ConvertIntToString(nItem + 1) + STRING(IDS_OOLPARAMETERS_LIMITSPAGE_LIMIT_FLAG)) : cStringTools.ConvertIntToString(nItem + 1);
							break;
						}
						if (m_szColumns.GetAt(nColumn) == STRING(IDS_OOLPARAMETERS_LIMITSPAGE_TITLEITEM_LIMIT))
						{
							if (pDatabaseTMTxtOolTable->GetAttributes() & TMOOLTABLE_CHECK_RAW)
							{
								if (pDatabaseTMTxtOolLimit->GetLimit(fLimitRange[0]))
								{
									szLimitRange[0] = (pDatabaseTMTxtOolTable->GetAttributes() & TMOOLTABLE_CODING_FLOATINGPOINT) ? cStringTools.ConvertFloatToString(fLimitRange[0]) : EMPTYSTRING;
									szLimitRange[0] = (pDatabaseTMTxtOolTable->GetAttributes() & TMOOLTABLE_CODING_SIGNEDINTEGER) ? cStringTools.ConvertLongIntToString((LONGLONG)fLimitRange[0]) : szLimitRange[0];
									szLimitRange[0] = (szLimitRange[0].IsEmpty()) ? cStringTools.ConvertLongUIntToString((ULONGLONG)fLimitRange[0]) : szLimitRange[0];
									szItem = szLimitRange[0];
								}
								else
								{
									if (pDatabaseTMTxtOolLimit->GetRange(fLimitRange[0], fLimitRange[1]))
									{
										if (!(pDatabaseTMTxtOolTable->GetAttributes() & TMOOLTABLE_CODING_FLOATINGPOINT))
										{
											if (pDatabaseTMTxtOolTable->GetAttributes() & TMOOLTABLE_CODING_SIGNEDINTEGER)
											{
												szLimitRange[0] = cStringTools.ConvertLongIntToString((LONGLONG)fLimitRange[0]);
												szLimitRange[1] = cStringTools.ConvertLongIntToString((LONGLONG)fLimitRange[1]);
											}
											else
											{
												szLimitRange[0] = cStringTools.ConvertLongUIntToString((ULONGLONG)fLimitRange[0]);
												szLimitRange[1] = cStringTools.ConvertLongUIntToString((ULONGLONG)fLimitRange[1]);
											}
										}
										else
										{
											szLimitRange[0] = cStringTools.ConvertFloatToString(fLimitRange[0]);
											szLimitRange[1] = cStringTools.ConvertFloatToString(fLimitRange[1]);
										}
										szItem.Format(STRING(IDS_OOLPARAMETERS_LIMITSPAGE_LIMIT_RANGE), (LPCTSTR)szLimitRange[0], (LPCTSTR)szLimitRange[1]);
									}
								}
							}
							for (; pDatabaseTMTxtOolTable->GetAttributes() & TMOOLTABLE_CHECK_CALIBRATED; )
							{
								if (pDatabaseTMTxtOolLimit->GetLimit(szLimitRange[0]) || (pDatabaseTMTxtOolLimit->GetRange(szLimitRange[0], szLimitRange[1]) && szLimitRange[0] == szLimitRange[1]))
								{
									szItem = szLimitRange[0];
									break;
								}
								szItem.Format(STRING(IDS_OOLPARAMETERS_LIMITSPAGE_LIMIT_RANGE), (LPCTSTR)szLimitRange[0], (LPCTSTR)szLimitRange[1]);
								break;
							}
						}
						if (!nColumn)
						{
							Listview_InsertText(GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_LIMITS), nItem, szItem);
							continue;
						}
						Listview_SetText(GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_LIMITS), nItem, nColumn, szItem);
					}
				}
			}
			GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_ID)->SetWindowText(szTable);
			GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_TYPE)->SetWindowText(STRING(IDS_OOLPARAMETERS_LIMITSPAGE_TYPE_STATUS));
			GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_STATUS)->SetWindowText((nIndex == m_nOolTableID) ? STRING(IDS_OOLPARAMETERS_LIMITSPAGE_STATUS_ACTIVE) : STRING(IDS_OOLPARAMETERS_LIMITSPAGE_STATUS_INACTIVE));
			GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_ID_STATIC)->EnableWindow((GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_ID)->EnableWindow((GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_TYPE_STATIC)->EnableWindow();
			GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_TYPE)->EnableWindow();
			GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_STATUS_STATIC)->EnableWindow();
			GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_STATUS)->EnableWindow();
			GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_LIMITS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_OOL_PARAMETERS_LIMITSPAGE_LIMITS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_LIMITS)->EnableWindow((SendDlgItemMessage(IDC_OOL_PARAMETERS_LIMITSPAGE_LIMITS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			return;
		}
	}
	SendDlgItemMessage(IDC_OOL_PARAMETERS_LIMITSPAGE_LIMITS, LVM_DELETEALLITEMS);
	GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_ID)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_TYPE)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_STATUS)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_ID_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_ID)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_TYPE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_TYPE)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_STATUS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_STATUS)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_LIMITS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_LIMITS)->EnableWindow(FALSE);
}

void COOLParametersLimitsPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COOLParametersLimitsPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void COOLParametersLimitsPage::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_nOolTableRefs.RemoveAll();
	m_nOolValidityRefs.RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(COOLParametersLimitsPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(COOLParametersLimitsPage)
	ON_CBN_SELCHANGE(IDC_OOL_PARAMETERS_LIMITSPAGE_NAME, OnSelchangeName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COOLParametersLimitsPage message handlers

BOOL COOLParametersLimitsPage::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	m_szColumns.Add(STRING(IDS_OOLPARAMETERS_LIMITSPAGE_TITLEITEM_NUMBER));
	m_szColumns.Add(STRING(IDS_OOLPARAMETERS_LIMITSPAGE_TITLEITEM_LIMIT));
	GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_LIMITS)->GetClientRect(rColumns);
	SendDlgItemMessage(IDC_OOL_PARAMETERS_LIMITSPAGE_LIMITS, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = rColumns.Width() / 5; nColumn < nColumns; nWidth = (++nColumn < nColumns) ? ((4 * rColumns.Width()) / 5) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_OOL_PARAMETERS_LIMITSPAGE_LIMITS), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	return TRUE;
}

void COOLParametersLimitsPage::OnSelchangeName()
{
	ShowLimitsInfo();
}


/////////////////////////////////////////////////////////////////////////////
// COOLParametersFolderTabCtrl

IMPLEMENT_DYNCREATE(COOLParametersFolderTabCtrl, CTabCtrl)

COOLParametersFolder *COOLParametersFolderTabCtrl::GetParent() CONST
{
	return((COOLParametersFolder *)CTabCtrl::GetParent());
}

BEGIN_MESSAGE_MAP(COOLParametersFolderTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(COOLParametersFolderTabCtrl)
	ON_WM_GETDLGCODE()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COOLParametersFolderTabCtrl message handlers

UINT COOLParametersFolderTabCtrl::OnGetDlgCode()
{
	return CTabCtrl::OnGetDlgCode() | DLGC_WANTTAB;
}

void COOLParametersFolderTabCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
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
// COOLParametersFolder

IMPLEMENT_DYNCREATE(COOLParametersFolder, CLocalePropertySheetDialog)

COOLParametersFolder::COOLParametersFolder() : CLocalePropertySheetDialog()
{
	AddPage(&m_pageLimits);
}

BOOL COOLParametersFolder::Create(CWnd *pParentWnd, CONST RECT &rect)
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

COOLParametersDialog *COOLParametersFolder::GetParentDialog() CONST
{
	return((COOLParametersDialog *)CLocalePropertySheetDialog::GetParent());
}

COOLWnd *COOLParametersFolder::GetParentDisplay() CONST
{
	return((COOLWnd *)GetParentDialog()->GetParent());
}

VOID COOLParametersFolder::ShowParameterInfo(CONST COolParameter *pOolParameter)
{
	m_pageLimits.ShowParameterInfo(pOolParameter);
}

BEGIN_MESSAGE_MAP(COOLParametersFolder, CLocalePropertySheetDialog)
	//{{AFX_MSG_MAP(COOLParametersFolder)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COOLParametersFolder message handlers

void COOLParametersFolder::OnSetFocus(CWnd *pOldWnd)
{
	if (IsWindow(m_wndTabCtrl.GetSafeHwnd()))
	{
		m_wndTabCtrl.SetFocus();
		return;
	}
	CLocalePropertySheetDialog::OnSetFocus(pOldWnd);
}


/////////////////////////////////////////////////////////////////////////////
// COOLParametersDialog dialog

IMPLEMENT_DYNCREATE(COOLParametersDialog, CDisplayDialog)

COOLParametersDialog::COOLParametersDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(COOLParametersDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT COOLParametersDialog::Create(CWnd *pParentWnd)
{
	return Create(pParentWnd, EMPTYSTRING);
}
INT COOLParametersDialog::Create(CWnd *pParentWnd, LPCTSTR pszParameter)
{
	m_szParameter = pszParameter;
	return CDisplayDialog::Create(pParentWnd, COOLParametersDialog::IDD);
}

COOLWnd *COOLParametersDialog::GetParent() CONST
{
	return((COOLWnd *)CDisplayDialog::GetParent());
}

BOOL COOLParametersDialog::EnumParameters()
{
	INT  nParameter;
	INT  nParameters;
	CString  szParameter;
	COolParameters  pOolParameters;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	for (nParameter = 0, nParameters = GetParent()->GetParameters(pOolParameters); nParameter < nParameters; nParameter++)
	{
		if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pOolParameters.GetAt(nParameter)->GetTag()))))
		{
			szParameter.Format(STRING(IDS_OOLPARAMETERSDIALOG_PARAMETERFORMAT), (LPCTSTR)pDatabaseTMParameter->GetTag(), (LPCTSTR)pDatabaseTMParameter->GetDescription());
			SendDlgItemMessage(IDC_OOL_PARAMETERS_ITEM, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szParameter);
		}
	}
	SendDlgItemMessage(IDC_OOL_PARAMETERS_ITEM, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_OOL_PARAMETERS_ITEM, CB_FINDSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)m_szParameter), 0));
	GetDlgItem(IDC_OOL_PARAMETERS_DETAILS)->EnableWindow((SendDlgItemMessage(IDC_OOL_PARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOL_PARAMETERS_ITEM_STATIC)->EnableWindow((SendDlgItemMessage(IDC_OOL_PARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOL_PARAMETERS_ITEM)->EnableWindow((SendDlgItemMessage(IDC_OOL_PARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	m_wndFolderCtrl.EnableWindow((SendDlgItemMessage(IDC_OOL_PARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_OOL_PARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID COOLParametersDialog::ShowParameterInfo()
{
	INT  nParameter;
	INT  nParameters;
	CString  szParameter[2];
	COolParameter  cOolParameter;
	COolParameters  pOolParameters;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	GetDlgItem(IDC_OOL_PARAMETERS_ITEM)->GetWindowText(szParameter[0]);
	for (nParameter = 0, nParameters = GetParent()->GetParameters(pOolParameters); nParameter < nParameters; nParameter++)
	{
		if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pOolParameters.GetAt(nParameter)->GetTag()))))
		{
			szParameter[1].Format(STRING(IDS_OOLPARAMETERSDIALOG_PARAMETERFORMAT), (LPCTSTR)pDatabaseTMParameter->GetTag(), (LPCTSTR)pDatabaseTMParameter->GetDescription());
			if (szParameter[0] == szParameter[1]) break;
		}
	}
	if (nParameter < nParameters)
	{
		GetParent()->GetParameterInfo(pDatabaseTMParameter->GetTag(), &cOolParameter);
		m_wndFolderCtrl.ShowParameterInfo(&cOolParameter);
		return;
	}
	m_wndFolderCtrl.ShowParameterInfo();
}

CRect COOLParametersDialog::CalcFolderSize() CONST
{
	CRect  rFolder;

	GetDlgItem(IDC_OOL_PARAMETERS_FOLDER)->GetWindowRect(rFolder);
	ScreenToClient(rFolder);
	return rFolder;
}

void COOLParametersDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COOLParametersDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COOLParametersDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(COOLParametersDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_OOL_PARAMETERS_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_OOL_PARAMETERS_ITEM, OnSelchangeParameter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COOLParametersDialog message handlers

BOOL COOLParametersDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	for (CDisplayDialog::OnInitDialog(); m_wndFolderCtrl.Create(this, CalcFolderSize()) && SetChildSheet(&m_wndFolderCtrl, GetDlgItem(IDC_OOL_PARAMETERS_FOLDER - 1)); )
	{
		if (EnumParameters()) ShowParameterInfo();
		break;
	}
	return TRUE;
}

void COOLParametersDialog::OnSelchangeParameter()
{
	ShowParameterInfo();
}

BOOL COOLParametersDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_OOLPARAMETERSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void COOLParametersDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_OOLPARAMETERSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// COOLAcknowledgeDialog dialog

IMPLEMENT_DYNCREATE(COOLAcknowledgeDialog, CDisplayDialog)

COOLAcknowledgeDialog::COOLAcknowledgeDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(COOLAcknowledgeDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT COOLAcknowledgeDialog::Create(CWnd *pParentWnd)
{
	return CDisplayDialog::Create(pParentWnd, COOLAcknowledgeDialog::IDD);
}

BOOL COOLAcknowledgeDialog::Initialize()
{
	GetParent()->GetParameterAlerts(m_pOolParameters, m_pOolAuditions);
	return TRUE;
}

BOOL COOLAcknowledgeDialog::EnumParameters()
{
	INT  nItem;
	INT  nItems;
	INT  nColumn;
	INT  nColumns;
	UINT  nStatus;
	CString  szItem;
	ULONGLONG  nValue;
	COolParameter  *pOolParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	for (nItem = 0, nItems = (INT)m_pOolParameters.GetSize(); nItem < nItems; nItem++)
	{
		for (nColumn = 0, nColumns = ((pOolParameter = m_pOolParameters.GetAt(nItem))) ? (INT)m_szColumns.GetSize() : 0; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_OOLACKNOWLEDGEDIALOG_ID); )
			{
				szItem = pOolParameter->GetTag();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_OOLACKNOWLEDGEDIALOG_DESCRIPTION); )
			{
				if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pOolParameter->GetTag()))))
				{
					szItem = pDatabaseTMParameter->GetDescription();
					break;
				}
				szItem.Empty();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_OOLACKNOWLEDGEDIALOG_OOLTYPE); )
			{
				if (pOolParameter->GetRawValue(pOolParameter->GetValueCount() - 1, nValue, nStatus))
				{
					szItem = (nStatus & TMPARAMETER_STATUS_SOFTLIMIT) ? STRING(IDS_OOLACKNOWLEDGEDIALOG_SOFTOOL) : EMPTYSTRING;
					szItem = (nStatus & TMPARAMETER_STATUS_HARDLIMIT) ? STRING(IDS_OOLACKNOWLEDGEDIALOG_HARDOOL) : (LPCTSTR)szItem;
					szItem = (nStatus & TMPARAMETER_STATUS_DELTALIMIT) ? STRING(IDS_OOLACKNOWLEDGEDIALOG_DELTAOOL) : (LPCTSTR)szItem;
					szItem = (nStatus & TMPARAMETER_STATUS_CONSISTENCYLIMIT) ? STRING(IDS_OOLACKNOWLEDGEDIALOG_CONSISTENCYOOL) : (LPCTSTR)szItem;
					break;
				}
				szItem.Empty();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_OOLACKNOWLEDGEDIALOG_OOLTIME); )
			{
				szItem = pOolParameter->GetOolTime().FormatGmt();
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_OOL_ACKNOWLEDGE_PARAMETERS), nItem, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_OOL_ACKNOWLEDGE_PARAMETERS), nItem, nColumn, szItem);
		}
	}
	Listview_SetCurText(GetDlgItem(IDC_OOL_ACKNOWLEDGE_PARAMETERS), 0);
	return((SendDlgItemMessage(IDC_OOL_ACKNOWLEDGE_PARAMETERS, LVM_GETITEMCOUNT) == m_pOolParameters.GetSize()) ? TRUE : FALSE);
}

BOOL COOLAcknowledgeDialog::EnumAuditions()
{
	INT  nAudition;
	INT  nAuditions;
	CEventObject  *pEvent;

	for (nAudition = 0, nAuditions = (INT)m_pOolAuditions.GetSize(); nAudition < nAuditions; nAudition++)
	{
		if ((pEvent = m_pOolAuditions.GetAt(nAudition))) SendDlgItemMessage(IDC_OOL_ACKNOWLEDGE_AUDITIONS, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)pEvent->GetMessage());
		continue;
	}
	return((SendDlgItemMessage(IDC_OOL_ACKNOWLEDGE_AUDITIONS, LB_GETCOUNT) == m_pOolAuditions.GetSize() && (!SendDlgItemMessage(IDC_OOL_ACKNOWLEDGE_AUDITIONS, LB_GETCOUNT) || SendDlgItemMessage(IDC_OOL_ACKNOWLEDGE_AUDITIONS, LB_SETCURSEL) >= 0)) ? TRUE : FALSE);
}

COOLWnd *COOLAcknowledgeDialog::GetParent() CONST
{
	return((COOLWnd *)CDisplayDialog::GetParent());
}

INT COOLAcknowledgeDialog::CalcColumnWidth(LPCTSTR pszColumn)
{
	CDC  *pDC;
	INT  nWidth;
	CFont  *pOldFont;
	TEXTMETRIC  tmFont;

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(GetFont())))
		{
			if (pDC->GetTextMetrics(&tmFont) > 0)
			{
				nWidth = (!lstrcmp(pszColumn, STRING(IDS_OOLACKNOWLEDGEDIALOG_ID))) ? max(2 * CalcColumnIndent() + GetDatabase()->GetOOLIDColumnCharWidth()*tmFont.tmAveCharWidth, 2 * CalcColumnIndent() + pDC->GetTextExtent(pszColumn).cx) : 0;
				nWidth = (!lstrcmp(pszColumn, STRING(IDS_OOLACKNOWLEDGEDIALOG_DESCRIPTION))) ? max(2 * CalcColumnIndent() + GetDatabase()->GetOOLDescriptionColumnCharWidth()*tmFont.tmAveCharWidth, 2 * CalcColumnIndent() + pDC->GetTextExtent(pszColumn).cx) : nWidth;
				nWidth = (!lstrcmp(pszColumn, STRING(IDS_OOLACKNOWLEDGEDIALOG_OOLTYPE))) ? max(2 * CalcColumnIndent() + GetDatabase()->GetOOLTypeColumnCharWidth()*tmFont.tmAveCharWidth, 2 * CalcColumnIndent() + pDC->GetTextExtent(pszColumn).cx) : nWidth;
				nWidth = (!lstrcmp(pszColumn, STRING(IDS_OOLACKNOWLEDGEDIALOG_OOLTIME))) ? max(2 * CalcColumnIndent() + GetDatabase()->GetOOLTMTimeColumnCharWidth()*tmFont.tmAveCharWidth, 2 * CalcColumnIndent() + pDC->GetTextExtent(pszColumn).cx) : nWidth;
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

INT COOLAcknowledgeDialog::CalcColumnIndent() CONST
{
	return 3 * GetSystemMetrics(SM_CXEDGE);
}

BOOL COOLAcknowledgeDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_OOL_ACKNOWLEDGE_PARAMETERS)->SendMessage(LVM_GETITEMCOUNT) > 0 || GetDlgItem(IDC_OOL_ACKNOWLEDGE_AUDITIONS)->SendMessage(LB_GETCOUNT) > 0) ? TRUE : FALSE);
}

void COOLAcknowledgeDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COOLAcknowledgeDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void COOLAcknowledgeDialog::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_pOolAuditions.RemoveAll();
	m_pOolParameters.RemoveAll();
	CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(COOLAcknowledgeDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(COOLAcknowledgeDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_OOL_ACKNOWLEDGE_PARAMETERS_REMOVE, OnRemoveParameter)
	ON_BN_CLICKED(IDC_OOL_ACKNOWLEDGE_PARAMETERS_REMOVEALL, OnRemoveAllParameters)
	ON_BN_CLICKED(IDC_OOL_ACKNOWLEDGE_AUDITIONS_REMOVE, OnRemoveAudition)
	ON_BN_CLICKED(IDC_OOL_ACKNOWLEDGE_AUDITIONS_REMOVEALL, OnRemoveAllAuditions)
	ON_BN_CLICKED(IDC_OOL_ACKNOWLEDGE_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COOLAcknowledgeDialog message handlers

BOOL COOLAcknowledgeDialog::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	m_szColumns.Add(STRING(IDS_OOLACKNOWLEDGEDIALOG_ID));
	m_szColumns.Add(STRING(IDS_OOLACKNOWLEDGEDIALOG_DESCRIPTION));
	m_szColumns.Add(STRING(IDS_OOLACKNOWLEDGEDIALOG_OOLTYPE));
	m_szColumns.Add(STRING(IDS_OOLACKNOWLEDGEDIALOG_OOLTIME));
	SendDlgItemMessage(IDC_OOL_ACKNOWLEDGE_PARAMETERS, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = CalcColumnWidth(m_szColumns.GetAt(nColumn)); nColumn < nColumns; nWidth = (++nColumn < nColumns) ? CalcColumnWidth(m_szColumns.GetAt(nColumn)) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_OOL_ACKNOWLEDGE_PARAMETERS), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	EnumParameters();
	EnumAuditions();
	GetDlgItem(IDC_OOL_ACKNOWLEDGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_OOL_ACKNOWLEDGE_COMMENT)->EnableWindow();
	GetDlgItem(IDC_OOL_ACKNOWLEDGE_PARAMETERS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_OOL_ACKNOWLEDGE_PARAMETERS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOL_ACKNOWLEDGE_PARAMETERS)->EnableWindow((SendDlgItemMessage(IDC_OOL_ACKNOWLEDGE_PARAMETERS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOL_ACKNOWLEDGE_AUDITIONS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_OOL_ACKNOWLEDGE_AUDITIONS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOL_ACKNOWLEDGE_AUDITIONS)->EnableWindow((SendDlgItemMessage(IDC_OOL_ACKNOWLEDGE_AUDITIONS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOL_ACKNOWLEDGE_PARAMETERS_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_OOL_ACKNOWLEDGE_PARAMETERS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOL_ACKNOWLEDGE_PARAMETERS_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_OOL_ACKNOWLEDGE_PARAMETERS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOL_ACKNOWLEDGE_AUDITIONS_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_OOL_ACKNOWLEDGE_AUDITIONS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOL_ACKNOWLEDGE_AUDITIONS_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_OOL_ACKNOWLEDGE_AUDITIONS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
	return TRUE;
}

void COOLAcknowledgeDialog::OnRemoveParameter()
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	CUIntArray  nItemIDs;
	COolParameter  *pOolParameter;
	CHourglassCursor  cCursor;

	for (nItem = 0, nItems = Listview_GetSelText(GetDlgItem(IDC_OOL_ACKNOWLEDGE_PARAMETERS), nItemIDs); nItem < nItems; nItem++)
	{
		if (Listview_DeleteText(GetDlgItem(IDC_OOL_ACKNOWLEDGE_PARAMETERS), (nIndex = nItemIDs.GetAt(nItem) - nItem)))
		{
			if ((pOolParameter = m_pOolParameters.GetAt(nIndex)))
			{
				m_pOolParameters.RemoveAt(nIndex);
				delete pOolParameter;
				continue;
			}
		}
		break;
	}
	for (Listview_SetCurText(GetDlgItem(IDC_OOL_ACKNOWLEDGE_PARAMETERS), 0); !SendDlgItemMessage(IDC_OOL_ACKNOWLEDGE_PARAMETERS, LVM_GETITEMCOUNT); )
	{
		for (GetDlgItem(IDC_OOL_ACKNOWLEDGE_PARAMETERS_STATIC)->EnableWindow(FALSE), GetDlgItem(IDC_OOL_ACKNOWLEDGE_PARAMETERS)->EnableWindow(FALSE), GetDlgItem(IDC_OOL_ACKNOWLEDGE_PARAMETERS_REMOVE)->EnableWindow(FALSE), GetDlgItem(IDC_OOL_ACKNOWLEDGE_PARAMETERS_REMOVEALL)->EnableWindow(FALSE); !Check(FALSE); )
		{
			GetDlgItem(IDCANCEL)->SetFocus();
			break;
		}
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
	GetDlgItem(IDOK)->SetFocus();
}

void COOLAcknowledgeDialog::OnRemoveAllParameters()
{
	CHourglassCursor  cCursor;

	for (m_pOolParameters.RemoveAll(), SendDlgItemMessage(IDC_OOL_ACKNOWLEDGE_PARAMETERS, LVM_DELETEALLITEMS); !SendDlgItemMessage(IDC_OOL_ACKNOWLEDGE_PARAMETERS, LVM_GETITEMCOUNT); )
	{
		for (GetDlgItem(IDC_OOL_ACKNOWLEDGE_PARAMETERS_STATIC)->EnableWindow(FALSE), GetDlgItem(IDC_OOL_ACKNOWLEDGE_PARAMETERS)->EnableWindow(FALSE), GetDlgItem(IDC_OOL_ACKNOWLEDGE_PARAMETERS_REMOVE)->EnableWindow(FALSE), GetDlgItem(IDC_OOL_ACKNOWLEDGE_PARAMETERS_REMOVEALL)->EnableWindow(FALSE); !Check(FALSE); )
		{
			GetDlgItem(IDCANCEL)->SetFocus();
			break;
		}
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
	GetDlgItem(IDOK)->SetFocus();
}

void COOLAcknowledgeDialog::OnRemoveAudition()
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	CUIntArray  nItemIDs;
	CEventObject  *pEvent;
	CHourglassCursor  cCursor;

	for (nItem = 0, nItems = (INT)SendDlgItemMessage(IDC_OOL_ACKNOWLEDGE_AUDITIONS, LB_GETSELCOUNT), nItemIDs.SetSize(nItems), nItems = (nItems == SendDlgItemMessage(IDC_OOL_ACKNOWLEDGE_AUDITIONS, LB_GETSELITEMS, nItems, (LPARAM)nItemIDs.GetData())) ? nItems : -1; nItem < nItems; nItem++)
	{
		if (SendDlgItemMessage(IDC_OOL_ACKNOWLEDGE_AUDITIONS, LB_DELETESTRING, (nIndex = nItemIDs.GetAt(nItem) - nItem)) >= 0)
		{
			if ((pEvent = m_pOolAuditions.GetAt(nIndex)))
			{
				m_pOolAuditions.RemoveAt(nIndex);
				delete pEvent;
				continue;
			}
		}
		break;
	}
	for (SendDlgItemMessage(IDC_OOL_ACKNOWLEDGE_AUDITIONS, LB_SETCURSEL); !SendDlgItemMessage(IDC_OOL_ACKNOWLEDGE_AUDITIONS, LB_GETCOUNT); )
	{
		for (GetDlgItem(IDC_OOL_ACKNOWLEDGE_AUDITIONS_STATIC)->EnableWindow(FALSE), GetDlgItem(IDC_OOL_ACKNOWLEDGE_AUDITIONS)->EnableWindow(FALSE), GetDlgItem(IDC_OOL_ACKNOWLEDGE_AUDITIONS_REMOVE)->EnableWindow(FALSE), GetDlgItem(IDC_OOL_ACKNOWLEDGE_AUDITIONS_REMOVEALL)->EnableWindow(FALSE); !Check(FALSE); )
		{
			GetDlgItem(IDCANCEL)->SetFocus();
			break;
		}
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
	GetDlgItem(IDOK)->SetFocus();
}

void COOLAcknowledgeDialog::OnRemoveAllAuditions()
{
	CHourglassCursor  cCursor;

	for (m_pOolAuditions.RemoveAll(), SendDlgItemMessage(IDC_OOL_ACKNOWLEDGE_AUDITIONS, LB_RESETCONTENT); !SendDlgItemMessage(IDC_OOL_ACKNOWLEDGE_AUDITIONS, LB_GETCOUNT); )
	{
		for (GetDlgItem(IDC_OOL_ACKNOWLEDGE_AUDITIONS_STATIC)->EnableWindow(FALSE), GetDlgItem(IDC_OOL_ACKNOWLEDGE_AUDITIONS)->EnableWindow(FALSE), GetDlgItem(IDC_OOL_ACKNOWLEDGE_AUDITIONS_REMOVE)->EnableWindow(FALSE), GetDlgItem(IDC_OOL_ACKNOWLEDGE_AUDITIONS_REMOVEALL)->EnableWindow(FALSE); !Check(FALSE); )
		{
			GetDlgItem(IDCANCEL)->SetFocus();
			break;
		}
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
	GetDlgItem(IDOK)->SetFocus();
}

void COOLAcknowledgeDialog::OnOK()
{
	CHourglassCursor  cCursor;

	GetParent()->SetParameterAlerts(m_pOolParameters, m_pOolAuditions);
	CDisplayDialog::OnOK();
}

BOOL COOLAcknowledgeDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_OOLACKNOWLEDGEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void COOLAcknowledgeDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_OOLACKNOWLEDGEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// COOLRetrieveDialog dialog

IMPLEMENT_DYNCREATE(COOLRetrieveDialog, CDisplayDialog)

COOLRetrieveDialog::COOLRetrieveDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(COOLRetrieveDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT COOLRetrieveDialog::Create(CWnd *pParentWnd)
{
	CString  szTitle;
	CString  szLayout;
	COOLWnd  *pOOLWnd;

	if ((pOOLWnd = (COOLWnd *)pParentWnd))
	{
		szTitle = (pOOLWnd->GetLayout(szLayout)) ? szLayout : STRING(IDS_WINDOW_UNKNOWNTITLE);
		return Create(pParentWnd, szTitle);
	}
	return -1;
}
INT COOLRetrieveDialog::Create(CWnd *pParentWnd, LPCTSTR pszTitle)
{
	m_szTitle = pszTitle;
	return CDisplayDialog::Create(pParentWnd, COOLRetrieveDialog::IDD);
}

BOOL COOLRetrieveDialog::GetMode(UINT &nMode) CONST
{
	nMode = (IsDlgButtonChecked(IDC_OOL_RETRIEVE_HISTORY_EXACTTIME)) ? OOL_RETRIEVE_EXACTTIME : 0;
	nMode |= (IsDlgButtonChecked(IDC_OOL_RETRIEVE_HISTORY_STOPBYTIME) || IsDlgButtonChecked(IDC_OOL_RETRIEVE_HISTORY_STOPBYEND)) ? ((!IsDlgButtonChecked(IDC_OOL_RETRIEVE_HISTORY_STOPBYTIME)) ? OOL_RETRIEVE_STOPBYEND : OOL_RETRIEVE_STOPBYTIME) : 0;
	nMode |= (IsDlgButtonChecked(IDC_OOL_RETRIEVE_HISTORY_AUTOMATIC)) ? OOL_RETRIEVE_AUTOFORWARD : ((IsDlgButtonChecked(IDC_OOL_RETRIEVE_HISTORY_PSEUDOREALTIME)) ? OOL_RETRIEVE_PSEUDOREALTIME : OOL_RETRIEVE_MANUALFORWARD);
	return TRUE;
}

BOOL COOLRetrieveDialog::GetSpeed(UINT &nSpeed) CONST
{
	nSpeed = (!IsDlgButtonChecked(IDC_OOL_RETRIEVE_HISTORY_AUTOMATIC)) ? (UINT)((GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_SPEED)->SendMessage(TBM_GETRANGEMIN) + GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_SPEED)->SendMessage(TBM_GETRANGEMAX)) / 2) : (UINT)GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_SPEED)->SendMessage(TBM_GETPOS);
	return((IsDlgButtonChecked(IDC_OOL_RETRIEVE_HISTORY_AUTOMATIC)) ? TRUE : FALSE);
}

BOOL COOLRetrieveDialog::GetInterval(CTimeSpan &tInterval) CONST
{
	tInterval = (IsDlgButtonChecked(IDC_OOL_RETRIEVE_HISTORY_INTERVAL)) ? (SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_INTERVALTIME))) : 0;
	return((IsDlgButtonChecked(IDC_OOL_RETRIEVE_HISTORY_INTERVAL)) ? TRUE : FALSE);
}

BOOL COOLRetrieveDialog::GetStartTime(CTimeKey &tTimeKey) CONST
{
	CTimeKey  tTime;

	for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_STARTTIME)), tTimeKey = 0; tTime > 0; )
	{
		tTimeKey = tTime;
		return TRUE;
	}
	return FALSE;
}

BOOL COOLRetrieveDialog::GetStopTime(CTimeKey &tTimeKey) CONST
{
	CTimeKey  tTime;

	for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_STOPTIME)), tTimeKey = 0; IsDlgButtonChecked(IDC_OOL_RETRIEVE_HISTORY_STOPBYTIME) && tTime > 0; )
	{
		tTimeKey = tTime;
		return TRUE;
	}
	return FALSE;
}

COOLOpenDialog *COOLRetrieveDialog::GetParentDialog() CONST
{
	return((GetParent() != (CWnd *)GetParentDisplay()) ? (COOLOpenDialog *)GetParent() : (COOLOpenDialog *)NULL);
}

COOLWnd *COOLRetrieveDialog::GetParentDisplay() CONST
{
	return((COOLWnd *)CDisplayDialog::GetParentDisplay());
}

BOOL COOLRetrieveDialog::SetRetrieveInfo()
{
	UINT  nMode;
	UINT  nSpeed;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;

	if (GetRetrieveInfo(nMode, nSpeed, tInterval, tStartTime, tStopTime))
	{
		Spinbox_SetPos(GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_INTERVALTIME), tInterval.GetTotalSeconds() / SECONDSPERMINUTE);
		Timespinbox_SetTime(GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_STARTTIME), (tStartTime > 0 || GetTMService()->GetRecentTMHistoryTimeKey(tStartTime)) ? tStartTime : CTime::GetCurrentTime().GetTime());
		Timespinbox_SetTime(GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_STOPTIME), (tStopTime.GetTime() > 0) ? tStopTime : CTime::GetCurrentTime().GetTime());
		Timespinbox_SetRange(GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_STOPTIME), Timespinbox_GetTime(GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_STARTTIME)), MAX_TIMEKEY);
		SendDlgItemMessage(IDC_OOL_RETRIEVE_HISTORY_SPEED, TBM_SETPOS, TRUE, (nMode) ? (((nMode & OOL_RETRIEVE_AUTOFORWARD) || (nMode & OOL_RETRIEVE_AUTOBACKWARD)) ? nSpeed : 0) : ((SendDlgItemMessage(IDC_OOL_RETRIEVE_HISTORY_SPEED, TBM_GETRANGEMIN) + SendDlgItemMessage(IDC_OOL_RETRIEVE_HISTORY_SPEED, TBM_GETRANGEMAX)) / 2));
		CheckDlgButton(IDC_OOL_RETRIEVE_HISTORY_EXACTTIME, (nMode & OOL_RETRIEVE_EXACTTIME) ? TRUE : FALSE);
		CheckDlgButton(IDC_OOL_RETRIEVE_HISTORY_STOPBYTIME, ((nMode & OOL_RETRIEVE_STOPBYTIME) && (nMode & (OOL_RETRIEVE_MANUALFORWARD | OOL_RETRIEVE_MANUALBACKWARD)) == 0) ? TRUE : FALSE);
		CheckDlgButton(IDC_OOL_RETRIEVE_HISTORY_STOPBYEND, ((!nMode || (nMode & OOL_RETRIEVE_STOPBYEND)) && (nMode & (OOL_RETRIEVE_MANUALFORWARD | OOL_RETRIEVE_MANUALBACKWARD)) == 0) ? TRUE : FALSE);
		CheckDlgButton(IDC_OOL_RETRIEVE_HISTORY_AUTOMATIC, (!nMode || (nMode & OOL_RETRIEVE_AUTOFORWARD) || (nMode & OOL_RETRIEVE_AUTOBACKWARD)) ? TRUE : FALSE);
		CheckDlgButton(IDC_OOL_RETRIEVE_HISTORY_MANUAL, ((nMode & OOL_RETRIEVE_MANUALFORWARD) || (nMode & OOL_RETRIEVE_MANUALBACKWARD)) ? TRUE : FALSE);
		CheckDlgButton(IDC_OOL_RETRIEVE_HISTORY_PSEUDOREALTIME, (nMode & OOL_RETRIEVE_PSEUDOREALTIME) ? TRUE : FALSE);
		CheckDlgButton(IDC_OOL_RETRIEVE_HISTORY_INTERVAL, ((nMode & OOL_RETRIEVE_PSEUDOREALTIME) == 0 && tInterval.GetTotalSeconds() > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_OOL_RETRIEVE_HISTORY)->EnableWindow();
		GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_START_STATIC)->EnableWindow();
		GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_STARTTIME)->EnableWindow();
		GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_EXACTTIME)->EnableWindow();
		GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_STOP_STATIC)->EnableWindow(!IsDlgButtonChecked(IDC_OOL_RETRIEVE_HISTORY_MANUAL));
		GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_STOPBYTIME)->EnableWindow(!IsDlgButtonChecked(IDC_OOL_RETRIEVE_HISTORY_MANUAL));
		GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_OOL_RETRIEVE_HISTORY_STOPBYTIME));
		GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_STOPBYEND)->EnableWindow(!IsDlgButtonChecked(IDC_OOL_RETRIEVE_HISTORY_MANUAL));
		GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_PLAYBACKMODE)->EnableWindow();
		GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_AUTOMATIC)->EnableWindow();
		GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_PSEUDOREALTIME)->EnableWindow();
		GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_MANUAL)->EnableWindow();
		GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_SPEED_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_OOL_RETRIEVE_HISTORY_AUTOMATIC));
		GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_SPEED)->EnableWindow(IsDlgButtonChecked(IDC_OOL_RETRIEVE_HISTORY_AUTOMATIC));
		GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_SLOW)->EnableWindow(IsDlgButtonChecked(IDC_OOL_RETRIEVE_HISTORY_AUTOMATIC));
		GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_FAST)->EnableWindow(IsDlgButtonChecked(IDC_OOL_RETRIEVE_HISTORY_AUTOMATIC));
		GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_INTERVAL)->EnableWindow(!IsDlgButtonChecked(IDC_OOL_RETRIEVE_HISTORY_PSEUDOREALTIME));
		GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_INTERVALTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_OOL_RETRIEVE_HISTORY_INTERVAL));
		GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_INTERVALTIME)->EnableWindow(IsDlgButtonChecked(IDC_OOL_RETRIEVE_HISTORY_INTERVAL));
		return TRUE;
	}
	return FALSE;
}

BOOL COOLRetrieveDialog::GetRetrieveInfo(UINT &nMode, UINT &nSpeed, CTimeSpan &tInterval, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	COOLWnd  *pOOLWnd;
	COOLOpenDialog  *pDialog;

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
	if ((pOOLWnd = GetParentDisplay()))
	{
		for (pOOLWnd->GetRetrieveMode(nMode), nSpeed = 0, tInterval = 0, tStartTime = tStopTime = 0; nMode; )
		{
			pOOLWnd->GetRetrieveSpeed(nSpeed);
			pOOLWnd->GetRetrieveInterval(tInterval);
			pOOLWnd->GetRetrieveStartTime(tStartTime);
			pOOLWnd->GetRetrieveStopTime(tStopTime);
			break;
		}
		return TRUE;
	}
	return FALSE;
}

void COOLRetrieveDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COOLRetrieveDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COOLRetrieveDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(COOLRetrieveDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_OOL_RETRIEVE_HISTORY_STOPBYTIME, OnRetrieveByTime)
	ON_BN_CLICKED(IDC_OOL_RETRIEVE_HISTORY_STOPBYEND, OnRetrieveByEnd)
	ON_BN_CLICKED(IDC_OOL_RETRIEVE_HISTORY_AUTOMATIC, OnRetrieveAutomatic)
	ON_BN_CLICKED(IDC_OOL_RETRIEVE_HISTORY_PSEUDOREALTIME, OnRetrievePseudoRealtime)
	ON_BN_CLICKED(IDC_OOL_RETRIEVE_HISTORY_MANUAL, OnRetrieveManual)
	ON_BN_CLICKED(IDC_OOL_RETRIEVE_HISTORY_INTERVAL, OnRetrieveInterval)
	ON_BN_CLICKED(IDC_OOL_RETRIEVE_HELP, OnHelp)
	ON_CONTROL(TSBXN_CHANGE, IDC_OOL_RETRIEVE_HISTORY_STARTTIME, OnSpinchangeRetrieveStartTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COOLRetrieveDialog message handlers

BOOL COOLRetrieveDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	for (CDisplayDialog::OnInitDialog(), SendDlgItemMessage(IDC_OOL_RETRIEVE_HISTORY_SPEED, TBM_SETRANGE, TRUE, MAKELPARAM(0, 10)), Spinbox_SetRange(GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_INTERVALTIME), OOLRETRIEVEDIALOG_MINIMUMINTERVAL, OOLRETRIEVEDIALOG_MAXIMUMINTERVAL), GetDlgItem(IDC_OOL_RETRIEVE_TITLE)->SetWindowText(m_szTitle); SetRetrieveInfo(); )
	{
		GetDlgItem(IDC_OOL_RETRIEVE_DETAILS)->EnableWindow();
		GetDlgItem(IDC_OOL_RETRIEVE_TITLE_STATIC)->EnableWindow();
		GetDlgItem(IDC_OOL_RETRIEVE_TITLE)->EnableWindow();
		GetDlgItem(IDC_OOL_RETRIEVE_TYPE_STATIC)->EnableWindow();
		GetDlgItem(IDC_OOL_RETRIEVE_TYPE)->EnableWindow();
		GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_STARTTIME)->SetFocus();
		GetDlgItem(IDOK)->EnableWindow();
		return FALSE;
	}
	return TRUE;
}

void COOLRetrieveDialog::OnRetrieveByTime()
{
	CheckDlgButton(IDC_OOL_RETRIEVE_HISTORY_STOPBYTIME, TRUE);
	CheckDlgButton(IDC_OOL_RETRIEVE_HISTORY_STOPBYEND, FALSE);
	GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_STOPTIME)->EnableWindow();
	GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_STOPTIME)->SetFocus();
}

void COOLRetrieveDialog::OnRetrieveByEnd()
{
	CheckDlgButton(IDC_OOL_RETRIEVE_HISTORY_STOPBYTIME, FALSE);
	CheckDlgButton(IDC_OOL_RETRIEVE_HISTORY_STOPBYEND, TRUE);
	GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(FALSE);
}

void COOLRetrieveDialog::OnRetrieveAutomatic()
{
	SendDlgItemMessage(IDC_OOL_RETRIEVE_HISTORY_SPEED, TBM_SETPOS, TRUE, (SendDlgItemMessage(IDC_OOL_RETRIEVE_HISTORY_SPEED, TBM_GETRANGEMIN) + SendDlgItemMessage(IDC_OOL_RETRIEVE_HISTORY_SPEED, TBM_GETRANGEMAX)) / 2);
	CheckDlgButton(IDC_OOL_RETRIEVE_HISTORY_STOPBYTIME, FALSE);
	CheckDlgButton(IDC_OOL_RETRIEVE_HISTORY_STOPBYEND, TRUE);
	CheckDlgButton(IDC_OOL_RETRIEVE_HISTORY_AUTOMATIC, TRUE);
	CheckDlgButton(IDC_OOL_RETRIEVE_HISTORY_PSEUDOREALTIME, FALSE);
	CheckDlgButton(IDC_OOL_RETRIEVE_HISTORY_MANUAL, FALSE);
	GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_STOP_STATIC)->EnableWindow();
	GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_STOPBYTIME)->EnableWindow();
	GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_OOL_RETRIEVE_HISTORY_STOPBYTIME));
	GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_STOPBYEND)->EnableWindow();
	GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_SPEED_STATIC)->EnableWindow();
	GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_SPEED)->EnableWindow();
	GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_SLOW)->EnableWindow();
	GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_FAST)->EnableWindow();
	GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_INTERVAL)->EnableWindow();
}

void COOLRetrieveDialog::OnRetrievePseudoRealtime()
{
	SendDlgItemMessage(IDC_OOL_RETRIEVE_HISTORY_SPEED, TBM_SETPOS, TRUE, 0);
	CheckDlgButton(IDC_OOL_RETRIEVE_HISTORY_STOPBYTIME, FALSE);
	CheckDlgButton(IDC_OOL_RETRIEVE_HISTORY_STOPBYEND, TRUE);
	CheckDlgButton(IDC_OOL_RETRIEVE_HISTORY_AUTOMATIC, FALSE);
	CheckDlgButton(IDC_OOL_RETRIEVE_HISTORY_PSEUDOREALTIME, TRUE);
	CheckDlgButton(IDC_OOL_RETRIEVE_HISTORY_MANUAL, FALSE);
	CheckDlgButton(IDC_OOL_RETRIEVE_HISTORY_INTERVAL, FALSE);
	GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_STOP_STATIC)->EnableWindow();
	GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_STOPBYTIME)->EnableWindow();
	GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_OOL_RETRIEVE_HISTORY_STOPBYTIME));
	GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_STOPBYEND)->EnableWindow();
	GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_SPEED_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_SPEED)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_SLOW)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_FAST)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_INTERVAL)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_INTERVALTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_INTERVALTIME)->EnableWindow(FALSE);
}

void COOLRetrieveDialog::OnRetrieveManual()
{
	SendDlgItemMessage(IDC_OOL_RETRIEVE_HISTORY_SPEED, TBM_SETPOS, TRUE, 0);
	CheckDlgButton(IDC_OOL_RETRIEVE_HISTORY_STOPBYTIME, FALSE);
	CheckDlgButton(IDC_OOL_RETRIEVE_HISTORY_STOPBYEND, FALSE);
	CheckDlgButton(IDC_OOL_RETRIEVE_HISTORY_AUTOMATIC, FALSE);
	CheckDlgButton(IDC_OOL_RETRIEVE_HISTORY_PSEUDOREALTIME, FALSE);
	CheckDlgButton(IDC_OOL_RETRIEVE_HISTORY_MANUAL, TRUE);
	GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_STOP_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_STOPBYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_STOPBYEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_SPEED_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_SPEED)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_SLOW)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_FAST)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_INTERVAL)->EnableWindow();
}

void COOLRetrieveDialog::OnRetrieveInterval()
{
	Spinbox_SetPos(GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_INTERVALTIME), OOLRETRIEVEDIALOG_DEFAULTINTERVAL);
	GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_INTERVALTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_OOL_RETRIEVE_HISTORY_INTERVAL));
	GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_INTERVALTIME)->EnableWindow(IsDlgButtonChecked(IDC_OOL_RETRIEVE_HISTORY_INTERVAL));
	GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_INTERVALTIME)->SetFocus();
}

void COOLRetrieveDialog::OnSpinchangeRetrieveStartTime()
{
	Timespinbox_SetRange(GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_STOPTIME), Timespinbox_GetTime(GetDlgItem(IDC_OOL_RETRIEVE_HISTORY_STARTTIME)), MAX_TIMEKEY);
}

void COOLRetrieveDialog::OnOK()
{
	COOLWnd  *pOOLWnd;
	CString  szLayout;
	CTimeKey  tTimeKey;
	CDisplayWnd  *pDisplayWnd;
	COOLOpenDialog  *pDialog;
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
		if (!IsDlgButtonChecked(IDC_OOL_RETRIEVE_HISTORY_AUTOMATIC) && !IsDlgButtonChecked(IDC_OOL_RETRIEVE_HISTORY_PSEUDOREALTIME) && !IsDlgButtonChecked(IDC_OOL_RETRIEVE_HISTORY_MANUAL))
		{
			if ((pOOLWnd = (GetParentDisplay()->GetLayout(szLayout)) ? GetParentDisplay()->Find(GetParentDisplay()->GetType(), DISPLAY_MODE_REALTIME, szLayout) : (COOLWnd *)NULL))
			{
				for (GetDisplayArea()->ActivateDisplay(pOOLWnd); pOOLWnd != GetParentDisplay(); )
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

void COOLRetrieveDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	if (!GetParentDialog()) GetParentDisplay()->OnCloseRetrieveDialog(IDCANCEL);
	else  GetParentDialog()->OnCloseRetrieveDialog(IDCANCEL);
	CDisplayDialog::OnCancel();
}

BOOL COOLRetrieveDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_OOLRETRIEVEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void COOLRetrieveDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_OOLRETRIEVEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// COOLSearchIDDialog dialog

IMPLEMENT_DYNCREATE(COOLSearchIDDialog, CDisplayDialog)

COOLSearchIDDialog::COOLSearchIDDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(COOLSearchIDDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL COOLSearchIDDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, COOLSearchIDDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

COOLWnd *COOLSearchIDDialog::GetParent() CONST
{
	return((COOLWnd *)CDisplayDialog::GetParent());
}

VOID COOLSearchIDDialog::EnumParameters()
{
	INT  nParameter;
	INT  nParameters;
	CString  szParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	for (nParameter = 0, nParameters = (INT)GetDatabase()->GetTMParameters()->GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(nParameter)) != (CDatabaseTMParameter *)NULL)
		{
			szParameter.Format(STRING(IDS_OOLSEARCHIDDIALOG_FORMAT), (LPCTSTR)pDatabaseTMParameter->GetTag(), (LPCTSTR)pDatabaseTMParameter->GetDescription());
			SendDlgItemMessage(IDC_OOL_SEARCHID_ID, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szParameter);
		}
	}
	SendDlgItemMessage(IDC_OOL_SEARCHID_ID, CB_SETCURSEL);
	GetDlgItem(IDC_OOL_SEARCHID_ID_STATIC)->EnableWindow((SendDlgItemMessage(IDC_OOL_SEARCHID_ID, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOL_SEARCHID_ID)->EnableWindow((SendDlgItemMessage(IDC_OOL_SEARCHID_ID, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOL_SEARCHID_FIND)->EnableWindow((SendDlgItemMessage(IDC_OOL_SEARCHID_ID, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
}

void COOLSearchIDDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COOLSearchIDDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COOLSearchIDDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(COOLSearchIDDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_OOL_SEARCHID_FIND, OnFindParameter)
	ON_BN_CLICKED(IDC_OOL_SEARCHID_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COOLSearchIDDialog message handlers

BOOL COOLSearchIDDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	CheckDlgButton(IDC_OOL_SEARCHID_ALL, TRUE);
	CheckDlgButton(IDC_OOL_SEARCHID_DIRECTION_DOWN, TRUE);
	GetDlgItem(IDC_OOL_SEARCHID_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHID_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHID_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHID_ALL)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHID_ID)->SetFocus();
	EnumParameters();
	return TRUE;
}

void COOLSearchIDDialog::OnFindParameter()
{
	INT  nPos;
	CString  szParameter;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_OOL_SEARCHID_ID)->GetWindowText(szParameter);
	if (!GetParent()->SearchParameterByID(((nPos = szParameter.Find(CString(SPACE) + SPACE)) >= 0) ? szParameter.Left(nPos) : szParameter, IsDlgButtonChecked(IDC_OOL_SEARCHID_DIRECTION_DOWN), IsDlgButtonChecked(IDC_OOL_SEARCHID_ALL)))
	{
		ReportEvent(USER_INFORMATIONAL_OOL_SEARCH_ID_NOTHING);
		return;
	}
	CheckDlgButton(IDC_OOL_SEARCHID_ALL, FALSE);
	CDisplayDialog::OnOK();
}

BOOL COOLSearchIDDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_OOLSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void COOLSearchIDDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_OOLSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// COOLSearchDescriptionDialog dialog

IMPLEMENT_DYNCREATE(COOLSearchDescriptionDialog, CDisplayDialog)

COOLSearchDescriptionDialog::COOLSearchDescriptionDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(COOLSearchDescriptionDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL COOLSearchDescriptionDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, COOLSearchDescriptionDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

COOLWnd *COOLSearchDescriptionDialog::GetParent() CONST
{
	return((COOLWnd *)CDisplayDialog::GetParent());
}

void COOLSearchDescriptionDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COOLSearchDescriptionDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COOLSearchDescriptionDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(COOLSearchDescriptionDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_OOL_SEARCHDESCRIPTION_FIND, OnFindDescription)
	ON_BN_CLICKED(IDC_OOL_SEARCHDESCRIPTION_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_OOL_SEARCHDESCRIPTION_DESCRIPTION, OnSelchangeDescription)
	ON_CBN_EDITCHANGE(IDC_OOL_SEARCHDESCRIPTION_DESCRIPTION, OnEditchangeDescription)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COOLSearchDescriptionDialog message handlers

BOOL COOLSearchDescriptionDialog::OnInitDialog()
{
	INT  nItem;
	INT  nItems;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (nItem = 0, nItems = (INT)m_szDescriptions.GetSize(); nItem < nItems; nItem++)
	{
		SendDlgItemMessage(IDC_OOL_SEARCHDESCRIPTION_DESCRIPTION, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)m_szDescriptions.GetAt(nItem));
		continue;
	}
	CheckDlgButton(IDC_OOL_SEARCHDESCRIPTION_ALL, TRUE);
	CheckDlgButton(IDC_OOL_SEARCHDESCRIPTION_DIRECTION_DOWN, TRUE);
	GetDlgItem(IDC_OOL_SEARCHDESCRIPTION_DESCRIPTION_STATIC)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHDESCRIPTION_DESCRIPTION)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHDESCRIPTION_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHDESCRIPTION_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHDESCRIPTION_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHDESCRIPTION_ALL)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHDESCRIPTION_CASE)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHDESCRIPTION_WORD)->EnableWindow();
	return TRUE;
}

void COOLSearchDescriptionDialog::OnFindDescription()
{
	CString  szDescription;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_OOL_SEARCHDESCRIPTION_DESCRIPTION)->GetWindowText(szDescription);
	if (SendDlgItemMessage(IDC_OOL_SEARCHDESCRIPTION_DESCRIPTION, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szDescription) == CB_ERR)
	{
		SendDlgItemMessage(IDC_OOL_SEARCHDESCRIPTION_DESCRIPTION, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szDescription);
		m_szDescriptions.Add(szDescription);
	}
	if (!GetParent()->SearchParameterByDescription(szDescription, IsDlgButtonChecked(IDC_OOL_SEARCHDESCRIPTION_DIRECTION_DOWN), IsDlgButtonChecked(IDC_OOL_SEARCHDESCRIPTION_ALL), IsDlgButtonChecked(IDC_OOL_SEARCHDESCRIPTION_CASE), IsDlgButtonChecked(IDC_OOL_SEARCHDESCRIPTION_WORD)))
	{
		ReportEvent(USER_INFORMATIONAL_OOL_SEARCH_DESCRIPTION_NOTHING);
		EndDialog(IDOK);
		return;
	}
	CheckDlgButton(IDC_OOL_SEARCHDESCRIPTION_ALL, FALSE);
}

void COOLSearchDescriptionDialog::OnSelchangeDescription()
{
	GetDlgItem(IDC_OOL_SEARCHDESCRIPTION_FIND)->EnableWindow((SendDlgItemMessage(IDC_OOL_SEARCHDESCRIPTION_DESCRIPTION, CB_GETCURSEL) != CB_ERR) ? TRUE : FALSE);
}

void COOLSearchDescriptionDialog::OnEditchangeDescription()
{
	GetDlgItem(IDC_OOL_SEARCHDESCRIPTION_FIND)->EnableWindow((GetDlgItem(IDC_OOL_SEARCHDESCRIPTION_DESCRIPTION)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

BOOL COOLSearchDescriptionDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_OOLSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void COOLSearchDescriptionDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_OOLSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// COOLSearchValueDialog dialog

IMPLEMENT_DYNCREATE(COOLSearchValueDialog, CDisplayDialog)

COOLSearchValueDialog::COOLSearchValueDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(COOLSearchValueDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL COOLSearchValueDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, COOLSearchValueDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

COOLWnd *COOLSearchValueDialog::GetParent() CONST
{
	return((COOLWnd *)CDisplayDialog::GetParent());
}

void COOLSearchValueDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COOLSearchValueDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COOLSearchValueDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(COOLSearchValueDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_OOL_SEARCHVALUE_FIND, OnFindValue)
	ON_BN_CLICKED(IDC_OOL_SEARCHVALUE_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_OOL_SEARCHVALUE_VALUE, OnSelchangeValue)
	ON_CBN_EDITCHANGE(IDC_OOL_SEARCHVALUE_VALUE, OnEditchangeValue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COOLSearchValueDialog message handlers

BOOL COOLSearchValueDialog::OnInitDialog()
{
	INT  nItem;
	INT  nItems;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (nItem = 0, nItems = (INT)m_szValues.GetSize(); nItem < nItems; nItem++)
	{
		SendDlgItemMessage(IDC_OOL_SEARCHVALUE_VALUE, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)m_szValues.GetAt(nItem));
		continue;
	}
	CheckDlgButton(IDC_OOL_SEARCHVALUE_ALL, TRUE);
	CheckDlgButton(IDC_OOL_SEARCHVALUE_DIRECTION_DOWN, TRUE);
	GetDlgItem(IDC_OOL_SEARCHVALUE_VALUE_STATIC)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHVALUE_VALUE)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHVALUE_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHVALUE_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHVALUE_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHVALUE_ALL)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHVALUE_CASE)->EnableWindow();
	return TRUE;
}

void COOLSearchValueDialog::OnFindValue()
{
	CString  szValue;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_OOL_SEARCHVALUE_VALUE)->GetWindowText(szValue);
	if (SendDlgItemMessage(IDC_OOL_SEARCHVALUE_VALUE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szValue) == CB_ERR)
	{
		SendDlgItemMessage(IDC_OOL_SEARCHVALUE_VALUE, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szValue);
		m_szValues.Add(szValue);
	}
	if (!GetParent()->SearchParameterByValue(szValue, IsDlgButtonChecked(IDC_OOL_SEARCHVALUE_DIRECTION_DOWN), IsDlgButtonChecked(IDC_OOL_SEARCHVALUE_ALL), IsDlgButtonChecked(IDC_OOL_SEARCHVALUE_CASE)))
	{
		ReportEvent(USER_INFORMATIONAL_OOL_SEARCH_VALUE_NOTHING);
		EndDialog(IDOK);
		return;
	}
	CheckDlgButton(IDC_OOL_SEARCHVALUE_ALL, FALSE);
}

void COOLSearchValueDialog::OnSelchangeValue()
{
	GetDlgItem(IDC_OOL_SEARCHVALUE_FIND)->EnableWindow((SendDlgItemMessage(IDC_OOL_SEARCHVALUE_VALUE, CB_GETCURSEL) != CB_ERR) ? TRUE : FALSE);
}

void COOLSearchValueDialog::OnEditchangeValue()
{
	GetDlgItem(IDC_OOL_SEARCHVALUE_FIND)->EnableWindow((GetDlgItem(IDC_OOL_SEARCHVALUE_VALUE)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

BOOL COOLSearchValueDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_OOLSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void COOLSearchValueDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_OOLSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// COOLSearchLimitDialog dialog

IMPLEMENT_DYNCREATE(COOLSearchLimitDialog, CDisplayDialog)

COOLSearchLimitDialog::COOLSearchLimitDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(COOLSearchLimitDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL COOLSearchLimitDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, COOLSearchLimitDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

COOLWnd *COOLSearchLimitDialog::GetParent() CONST
{
	return((COOLWnd *)CDisplayDialog::GetParent());
}

VOID COOLSearchLimitDialog::EnumLimits()
{
	INT  nLimit;
	INT  nLimits;
	CDatabaseTMNumOolTable  *pDatabaseTMNumOolTable;
	CDatabaseTMTxtOolTable  *pDatabaseTMTxtOolTable;

	for (nLimit = 0, nLimits = (INT)GetDatabase()->GetTMNumOolTables()->GetSize(); nLimit < nLimits; nLimit++)
	{
		if ((pDatabaseTMNumOolTable = GetDatabase()->GetTMNumOolTables()->GetAt(nLimit)))
		{
			if (SendDlgItemMessage(IDC_OOL_SEARCHLIMIT_LIMIT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pDatabaseTMNumOolTable->GetName()) == CB_ERR)
			{
				SendDlgItemMessage(IDC_OOL_SEARCHLIMIT_LIMIT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pDatabaseTMNumOolTable->GetName());
				continue;
			}
		}
	}
	for (nLimit = 0, nLimits = (INT)GetDatabase()->GetTMTxtOolTables()->GetSize(); nLimit < nLimits; nLimit++)
	{
		if ((pDatabaseTMTxtOolTable = GetDatabase()->GetTMTxtOolTables()->GetAt(nLimit)))
		{
			if (SendDlgItemMessage(IDC_OOL_SEARCHLIMIT_LIMIT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pDatabaseTMTxtOolTable->GetName()) == CB_ERR)
			{
				SendDlgItemMessage(IDC_OOL_SEARCHLIMIT_LIMIT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pDatabaseTMTxtOolTable->GetName());
				continue;
			}
		}
	}
	SendDlgItemMessage(IDC_OOL_SEARCHLIMIT_LIMIT, CB_SETCURSEL);
	GetDlgItem(IDC_OOL_SEARCHLIMIT_LIMIT_STATIC)->EnableWindow((SendDlgItemMessage(IDC_OOL_SEARCHLIMIT_LIMIT, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOL_SEARCHLIMIT_LIMIT)->EnableWindow((SendDlgItemMessage(IDC_OOL_SEARCHLIMIT_LIMIT, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOL_SEARCHLIMIT_FIND)->EnableWindow((SendDlgItemMessage(IDC_OOL_SEARCHLIMIT_LIMIT, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
}

void COOLSearchLimitDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COOLSearchLimitDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COOLSearchLimitDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(COOLSearchLimitDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_OOL_SEARCHLIMIT_FIND, OnFindLimit)
	ON_BN_CLICKED(IDC_OOL_SEARCHLIMIT_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COOLSearchLimitDialog message handlers

BOOL COOLSearchLimitDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	CheckDlgButton(IDC_OOL_SEARCHLIMIT_ALL, TRUE);
	CheckDlgButton(IDC_OOL_SEARCHLIMIT_DIRECTION_DOWN, TRUE);
	GetDlgItem(IDC_OOL_SEARCHLIMIT_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHLIMIT_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHLIMIT_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHLIMIT_ALL)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHLIMIT_LIMIT)->SetFocus();
	EnumLimits();
	return TRUE;
}

void COOLSearchLimitDialog::OnFindLimit()
{
	CString  szLimit;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_OOL_SEARCHLIMIT_LIMIT)->GetWindowText(szLimit);
	if (!GetParent()->SearchParameterByLimit(szLimit, IsDlgButtonChecked(IDC_OOL_SEARCHLIMIT_DIRECTION_DOWN), IsDlgButtonChecked(IDC_OOL_SEARCHLIMIT_ALL)))
	{
		ReportEvent(USER_INFORMATIONAL_OOL_SEARCH_LIMIT_NOTHING);
		return;
	}
	CheckDlgButton(IDC_OOL_SEARCHLIMIT_ALL, FALSE);
}

BOOL COOLSearchLimitDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_OOLSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void COOLSearchLimitDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_OOLSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// COOLSearchUnitDialog dialog

IMPLEMENT_DYNCREATE(COOLSearchUnitDialog, CDisplayDialog)

COOLSearchUnitDialog::COOLSearchUnitDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(COOLSearchUnitDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL COOLSearchUnitDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, COOLSearchUnitDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

COOLWnd *COOLSearchUnitDialog::GetParent() CONST
{
	return((COOLWnd *)CDisplayDialog::GetParent());
}

void COOLSearchUnitDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COOLSearchUnitDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COOLSearchUnitDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(COOLSearchUnitDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_OOL_SEARCHUNIT_FIND, OnFindUnit)
	ON_BN_CLICKED(IDC_OOL_SEARCHUNIT_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_OOL_SEARCHUNIT_UNIT, OnSelchangeUnit)
	ON_CBN_EDITCHANGE(IDC_OOL_SEARCHUNIT_UNIT, OnEditchangeUnit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COOLSearchUnitDialog message handlers

BOOL COOLSearchUnitDialog::OnInitDialog()
{
	INT  nItem;
	INT  nItems;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	for (nItem = 0, nItems = (INT)m_szUnits.GetSize(); nItem < nItems; nItem++)
	{
		SendDlgItemMessage(IDC_OOL_SEARCHUNIT_UNIT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)m_szUnits.GetAt(nItem));
		continue;
	}
	CheckDlgButton(IDC_OOL_SEARCHUNIT_ALL, TRUE);
	CheckDlgButton(IDC_OOL_SEARCHUNIT_DIRECTION_DOWN, TRUE);
	GetDlgItem(IDC_OOL_SEARCHUNIT_UNIT_STATIC)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHUNIT_UNIT)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHUNIT_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHUNIT_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHUNIT_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHUNIT_ALL)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHUNIT_CASE)->EnableWindow();
	return TRUE;
}

void COOLSearchUnitDialog::OnFindUnit()
{
	CString  szUnit;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_OOL_SEARCHUNIT_UNIT)->GetWindowText(szUnit);
	if (SendDlgItemMessage(IDC_OOL_SEARCHUNIT_UNIT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szUnit) == CB_ERR)
	{
		SendDlgItemMessage(IDC_OOL_SEARCHUNIT_UNIT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szUnit);
		m_szUnits.Add(szUnit);
	}
	if (!GetParent()->SearchParameterByUnit(szUnit, IsDlgButtonChecked(IDC_OOL_SEARCHUNIT_DIRECTION_DOWN), IsDlgButtonChecked(IDC_OOL_SEARCHUNIT_ALL), IsDlgButtonChecked(IDC_OOL_SEARCHUNIT_CASE)))
	{
		ReportEvent(USER_INFORMATIONAL_OOL_SEARCH_UNIT_NOTHING);
		EndDialog(IDOK);
		return;
	}
	CheckDlgButton(IDC_OOL_SEARCHUNIT_ALL, FALSE);
}

void COOLSearchUnitDialog::OnSelchangeUnit()
{
	GetDlgItem(IDC_OOL_SEARCHUNIT_FIND)->EnableWindow((SendDlgItemMessage(IDC_OOL_SEARCHUNIT_UNIT, CB_GETCURSEL) != CB_ERR) ? TRUE : FALSE);
}

void COOLSearchUnitDialog::OnEditchangeUnit()
{
	GetDlgItem(IDC_OOL_SEARCHUNIT_FIND)->EnableWindow((GetDlgItem(IDC_OOL_SEARCHUNIT_UNIT)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

BOOL COOLSearchUnitDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_OOLSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void COOLSearchUnitDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_OOLSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// COOLSearchOolTypeDialog dialog

IMPLEMENT_DYNCREATE(COOLSearchOolTypeDialog, CDisplayDialog)

COOLSearchOolTypeDialog::COOLSearchOolTypeDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(COOLSearchOolTypeDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL COOLSearchOolTypeDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, COOLSearchOolTypeDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

COOLWnd *COOLSearchOolTypeDialog::GetParent() CONST
{
	return((COOLWnd *)CDisplayDialog::GetParent());
}

VOID COOLSearchOolTypeDialog::EnumOolTypes()
{
	SendDlgItemMessage(IDC_OOL_SEARCHOOLTYPE_TYPE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_OOLSEARCHOOLTYPEDIALOG_SOFTOOL));
	SendDlgItemMessage(IDC_OOL_SEARCHOOLTYPE_TYPE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_OOLSEARCHOOLTYPEDIALOG_HARDOOL));
	SendDlgItemMessage(IDC_OOL_SEARCHOOLTYPE_TYPE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_OOLSEARCHOOLTYPEDIALOG_DELTAOOL));
	SendDlgItemMessage(IDC_OOL_SEARCHOOLTYPE_TYPE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_OOL_SEARCHOOLTYPE_TYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_OOLSEARCHOOLTYPEDIALOG_HARDOOL)));
	GetDlgItem(IDC_OOL_SEARCHOOLTYPE_TYPE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_OOL_SEARCHOOLTYPE_TYPE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOL_SEARCHOOLTYPE_TYPE)->EnableWindow((SendDlgItemMessage(IDC_OOL_SEARCHOOLTYPE_TYPE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOL_SEARCHOOLTYPE_FIND)->EnableWindow((SendDlgItemMessage(IDC_OOL_SEARCHOOLTYPE_TYPE, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
}

void COOLSearchOolTypeDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COOLSearchOolTypeDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COOLSearchOolTypeDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(COOLSearchOolTypeDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_OOL_SEARCHOOLTYPE_FIND, OnFindOolType)
	ON_BN_CLICKED(IDC_OOL_SEARCHOOLTYPE_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COOLSearchOolTypeDialog message handlers

BOOL COOLSearchOolTypeDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	CheckDlgButton(IDC_OOL_SEARCHOOLTYPE_ALL, TRUE);
	CheckDlgButton(IDC_OOL_SEARCHOOLTYPE_DIRECTION_DOWN, TRUE);
	GetDlgItem(IDC_OOL_SEARCHOOLTYPE_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHOOLTYPE_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHOOLTYPE_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHOOLTYPE_ALL)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHOOLTYPE_TYPE)->SetFocus();
	EnumOolTypes();
	return TRUE;
}

void COOLSearchOolTypeDialog::OnFindOolType()
{
	CString  szOolType;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_OOL_SEARCHOOLTYPE_TYPE)->GetWindowText(szOolType);
	if (!GetParent()->SearchParameterByOolType(szOolType, IsDlgButtonChecked(IDC_OOL_SEARCHOOLTYPE_DIRECTION_DOWN), IsDlgButtonChecked(IDC_OOL_SEARCHOOLTYPE_ALL)))
	{
		ReportEvent(USER_INFORMATIONAL_OOL_SEARCH_OOLTYPE_NOTHING);
		return;
	}
	CheckDlgButton(IDC_OOL_SEARCHOOLTYPE_ALL, FALSE);
}

BOOL COOLSearchOolTypeDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_OOLSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void COOLSearchOolTypeDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_OOLSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// COOLSearchOolUnitDialog dialog

IMPLEMENT_DYNCREATE(COOLSearchOolUnitDialog, CDisplayDialog)

COOLSearchOolUnitDialog::COOLSearchOolUnitDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(COOLSearchOolUnitDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL COOLSearchOolUnitDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, COOLSearchOolUnitDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

COOLWnd *COOLSearchOolUnitDialog::GetParent() CONST
{
	return((COOLWnd *)CDisplayDialog::GetParent());
}

VOID COOLSearchOolUnitDialog::EnumOolUnits()
{
	INT  nPacket;
	INT  nPackets;
	CString  szPacket;
	CDatabaseTMPacket  *pDatabaseTMPacket;

	for (nPacket = 0, nPackets = (INT)GetDatabase()->GetTMPackets()->GetSize(); nPacket < nPackets; nPacket++)
	{
		if ((pDatabaseTMPacket = GetDatabase()->GetTMPackets()->GetAt(nPacket)) != (CDatabaseTMPacket *)NULL)
		{
			szPacket.Format(STRING(IDS_OOLSEARCHOOLUNITDIALOG_FORMAT), (LPCTSTR)pDatabaseTMPacket->GetDescription(), (LPCTSTR)pDatabaseTMPacket->GetTag());
			if (SendDlgItemMessage(IDC_OOL_SEARCHOOLUNIT_UNIT, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szPacket) >= 0)
			{
				m_szOolUnits.Add(pDatabaseTMPacket->GetTag());
				continue;
			}
		}
	}
	SendDlgItemMessage(IDC_OOL_SEARCHOOLUNIT_UNIT, CB_SETCURSEL);
	GetDlgItem(IDC_OOL_SEARCHOOLUNIT_UNIT_STATIC)->EnableWindow((SendDlgItemMessage(IDC_OOL_SEARCHOOLUNIT_UNIT, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOL_SEARCHOOLUNIT_UNIT)->EnableWindow((SendDlgItemMessage(IDC_OOL_SEARCHOOLUNIT_UNIT, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_OOL_SEARCHOOLUNIT_FIND)->EnableWindow((SendDlgItemMessage(IDC_OOL_SEARCHOOLUNIT_UNIT, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
}

void COOLSearchOolUnitDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COOLSearchOolUnitDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void COOLSearchOolUnitDialog::PostNcDestroy()
{
	m_szOolUnits.RemoveAll();
	CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(COOLSearchOolUnitDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(COOLSearchOolUnitDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_OOL_SEARCHOOLUNIT_FIND, OnFindOolUnit)
	ON_BN_CLICKED(IDC_OOL_SEARCHOOLUNIT_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COOLSearchOolUnitDialog message handlers

BOOL COOLSearchOolUnitDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	CheckDlgButton(IDC_OOL_SEARCHOOLUNIT_ALL, TRUE);
	CheckDlgButton(IDC_OOL_SEARCHOOLUNIT_DIRECTION_DOWN, TRUE);
	GetDlgItem(IDC_OOL_SEARCHOOLUNIT_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHOOLUNIT_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHOOLUNIT_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHOOLUNIT_ALL)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHOOLUNIT_UNIT)->SetFocus();
	EnumOolUnits();
	return TRUE;
}

void COOLSearchOolUnitDialog::OnFindOolUnit()
{
	CHourglassCursor  cCursor;

	if (!GetParent()->SearchParameterByOolUnit(m_szOolUnits.GetAt(SendDlgItemMessage(IDC_OOL_SEARCHOOLUNIT_UNIT, CB_GETCURSEL)), IsDlgButtonChecked(IDC_OOL_SEARCHOOLUNIT_DIRECTION_DOWN), IsDlgButtonChecked(IDC_OOL_SEARCHOOLUNIT_ALL)))
	{
		ReportEvent(USER_INFORMATIONAL_OOL_SEARCH_OOLUNIT_NOTHING);
		return;
	}
	CheckDlgButton(IDC_OOL_SEARCHOOLUNIT_ALL, FALSE);
}

BOOL COOLSearchOolUnitDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_OOLSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void COOLSearchOolUnitDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_OOLSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// COOLSearchOolTimeDialog dialog

IMPLEMENT_DYNCREATE(COOLSearchOolTimeDialog, CDisplayDialog)

COOLSearchOolTimeDialog::COOLSearchOolTimeDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(COOLSearchOolTimeDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL COOLSearchOolTimeDialog::Create(CWnd *pParentWnd)
{
	INT  nResult;

	return(((nResult = CDisplayDialog::Create(pParentWnd, COOLSearchOolTimeDialog::IDD)) == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
}

COOLWnd *COOLSearchOolTimeDialog::GetParent() CONST
{
	return((COOLWnd *)CDisplayDialog::GetParent());
}

void COOLSearchOolTimeDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COOLSearchOolTimeDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COOLSearchOolTimeDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(COOLSearchOolTimeDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_OOL_SEARCHOOLTIME_FIND, OnFindOolTime)
	ON_BN_CLICKED(IDC_OOL_SEARCHOOLTIME_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COOLSearchOolTimeDialog message handlers

BOOL COOLSearchOolTimeDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	CheckDlgButton(IDC_OOL_SEARCHOOLTIME_ALL, TRUE);
	CheckDlgButton(IDC_OOL_SEARCHOOLTIME_DIRECTION_DOWN, TRUE);
	Timespinbox_SetTime(GetDlgItem(IDC_OOL_SEARCHOOLTIME_TIME), CTimeKey(CTime::GetCurrentTime().GetTime()));
	GetDlgItem(IDC_OOL_SEARCHOOLTIME_TIME_STATIC)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHOOLTIME_TIME)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHOOLTIME_DIRECTION)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHOOLTIME_DIRECTION_UP)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHOOLTIME_DIRECTION_DOWN)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHOOLTIME_ALL)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHOOLTIME_MATCH)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHOOLTIME_FIND)->EnableWindow();
	GetDlgItem(IDC_OOL_SEARCHOOLTIME_TIME)->SetFocus();
	return TRUE;
}

void COOLSearchOolTimeDialog::OnFindOolTime()
{
	CHourglassCursor  cCursor;

	if (!GetParent()->SearchParameterByOolTime(Timespinbox_GetTime(GetDlgItem(IDC_OOL_SEARCHOOLTIME_TIME)), IsDlgButtonChecked(IDC_OOL_SEARCHOOLTIME_DIRECTION_DOWN), IsDlgButtonChecked(IDC_OOL_SEARCHOOLTIME_ALL), IsDlgButtonChecked(IDC_OOL_SEARCHOOLTIME_MATCH)))
	{
		ReportEvent(USER_INFORMATIONAL_OOL_SEARCH_OOLTIME_NOTHING);
		return;
	}
	CheckDlgButton(IDC_OOL_SEARCHOOLTIME_ALL, FALSE);
}

BOOL COOLSearchOolTimeDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_OOLSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void COOLSearchOolTimeDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_OOLSEARCHDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// COOLOpenDialog dialog

IMPLEMENT_DYNCREATE(COOLOpenDialog, CDisplayDialog)

COOLOpenDialog::COOLOpenDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(COOLOpenDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT COOLOpenDialog::Create(CWnd *pParentWnd)
{
	return CDisplayDialog::Create(pParentWnd, COOLOpenDialog::IDD);
}

BOOL COOLOpenDialog::Initialize()
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
	ZeroMemory(&m_fntLayoutItems, sizeof(LOGFONT));
	return TRUE;
}

CString COOLOpenDialog::GetTitle() CONST
{
	CString  szTitle[2];

	if (GetType() == OOL_TYPE_GLOBAL)
	{
		szTitle[0] = STRING(IDS_DISPLAY_TITLE_GLOBALOOL);
		return szTitle[0];
	}
	if (GetType() == OOL_TYPE_NORMAL)
	{
		GetDlgItem(IDC_OOL_OPEN_DISPLAY)->GetWindowText(szTitle[0]);
		szTitle[1].Format(STRING(IDS_WINDOW_FULLTITLE), STRING(IDS_DISPLAY_TITLE_OOL), (LPCTSTR)szTitle[0]);
		return szTitle[1];
	}
	return STRING(IDS_DISPLAY_TITLE_OOL);
}

UINT COOLOpenDialog::GetType() CONST
{
	return((IsDlgButtonChecked(IDC_OOL_OPEN_MODE_REALTIME)) ? OOL_TYPE_GLOBAL : OOL_TYPE_NORMAL);
}

UINT COOLOpenDialog::GetMode() CONST
{
	return((IsDlgButtonChecked(IDC_OOL_OPEN_MODE_REALTIME) || IsDlgButtonChecked(IDC_OOL_OPEN_MODE_HISTORY)) ? (IsDlgButtonChecked(IDC_OOL_OPEN_MODE_REALTIME)*DISPLAY_MODE_REALTIME + IsDlgButtonChecked(IDC_OOL_OPEN_MODE_HISTORY)*DISPLAY_MODE_HISTORY) : -1);
}

BOOL COOLOpenDialog::GetLayout(CString &szLayout) CONST
{
	if (GetType() == OOL_TYPE_GLOBAL)
	{
		szLayout = STRING(IDS_DISPLAY_TITLE_GLOBALOOL);
		return TRUE;
	}
	if (GetType() == OOL_TYPE_NORMAL)
	{
		GetDlgItem(IDC_OOL_OPEN_DISPLAY)->GetWindowText(szLayout);
		return((szLayout.GetLength() > 0) ? TRUE : FALSE);
	}
	return FALSE;
}
BOOL COOLOpenDialog::GetLayout(CString &szLayout, CUIntArray &nColumns) CONST
{
	for (nColumns.RemoveAll(); GetLayout(szLayout); )
	{
		if (m_nLayoutColumns.GetSize() > 0)
		{
			nColumns.Copy(m_nLayoutColumns);
			return TRUE;
		}
		if (OOL_TITLEITEMS_DEFAULT & OOL_TITLEITEM_ID) nColumns.Add(OOL_TITLEITEM_ID);
		if (OOL_TITLEITEMS_DEFAULT & OOL_TITLEITEM_DESCRIPTION) nColumns.Add(OOL_TITLEITEM_DESCRIPTION);
		if (OOL_TITLEITEMS_DEFAULT & OOL_TITLEITEM_VALUE) nColumns.Add(OOL_TITLEITEM_VALUE);
		if (OOL_TITLEITEMS_DEFAULT & OOL_TITLEITEM_LIMIT) nColumns.Add(OOL_TITLEITEM_LIMIT);
		if (OOL_TITLEITEMS_DEFAULT & OOL_TITLEITEM_UNIT) nColumns.Add(OOL_TITLEITEM_UNIT);
		if (OOL_TITLEITEMS_DEFAULT & OOL_TITLEITEM_OOLTYPE) nColumns.Add(OOL_TITLEITEM_OOLTYPE);
		if (OOL_TITLEITEMS_DEFAULT & OOL_TITLEITEM_OOLTIME) nColumns.Add(OOL_TITLEITEM_OOLTIME);
		if (OOL_TITLEITEMS_DEFAULT & OOL_TITLEITEM_OOLUNIT) nColumns.Add(OOL_TITLEITEM_OOLUNIT);
		return TRUE;
	}
	return FALSE;
}

BOOL COOLOpenDialog::GetLayoutTitleFont(LPLOGFONT pTitleFont) CONST
{
	if (IsLayoutModified())
	{
		CopyMemory(pTitleFont, &m_fntLayoutTitle, sizeof(LOGFONT));
		return TRUE;
	}
	return FALSE;
}

BOOL COOLOpenDialog::GetLayoutItemsFont(LPLOGFONT pItemsFont) CONST
{
	if (IsLayoutModified())
	{
		CopyMemory(pItemsFont, &m_fntLayoutItems, sizeof(LOGFONT));
		return TRUE;
	}
	return FALSE;
}

BOOL COOLOpenDialog::GetLayoutInvalidDataMode(BOOL &bEnable) CONST
{
	if (IsLayoutModified())
	{
		bEnable = m_bLayoutInvalidData;
		return TRUE;
	}
	return FALSE;
}

BOOL COOLOpenDialog::GetLayoutBadDataMode(BOOL &bEnable) CONST
{
	if (IsLayoutModified())
	{
		bEnable = m_bLayoutBadData;
		return TRUE;
	}
	return FALSE;
}

BOOL COOLOpenDialog::GetLayoutToolTipMode(BOOL &bEnable) CONST
{
	if (IsLayoutModified())
	{
		bEnable = m_bLayoutToolTips;
		return TRUE;
	}
	return FALSE;
}

BOOL COOLOpenDialog::IsLayoutModified() CONST
{
	LOGFONT  fntSample = { 0 };

	return((m_nLayoutColumns.GetSize() > 0 || memcmp(&m_fntLayoutTitle, &fntSample, sizeof(LOGFONT)) || memcmp(&m_fntLayoutItems, &fntSample, sizeof(LOGFONT)) || m_bLayoutInvalidData || m_bLayoutBadData || m_bLayoutToolTips) ? TRUE : FALSE);
}

BOOL COOLOpenDialog::GetParameterFilters(COOLParameterFilters &pFilters) CONST
{
	return((IsFilteringModified()) ? pFilters.Copy(&m_pParameterFilters) : FALSE);
}

BOOL COOLOpenDialog::GetFilterColors(CUIntArray &nColors) CONST
{
	if (IsFilteringModified())
	{
		nColors.Copy(m_nFilterColors);
		return TRUE;
	}
	return FALSE;
}

BOOL COOLOpenDialog::IsFilteringModified() CONST
{
	return((m_pParameterFilters.GetSize() > 0 || m_nFilterColors.GetSize() > 0) ? TRUE : FALSE);
}

BOOL COOLOpenDialog::GetRetrieveMode(UINT &nMode) CONST
{
	nMode = m_nRetrieveMode;
	return TRUE;
}

BOOL COOLOpenDialog::GetRetrieveSpeed(UINT &nSpeed) CONST
{
	nSpeed = m_nRetrieveSpeed;
	return((m_nRetrieveMode & OOL_RETRIEVE_AUTOFORWARD) ? TRUE : FALSE);
}

BOOL COOLOpenDialog::GetRetrieveInterval(CTimeSpan &tInterval) CONST
{
	tInterval = m_tRetrieveInterval;
	return(((m_nRetrieveMode & OOL_RETRIEVE_AUTOFORWARD) || (m_nRetrieveMode & OOL_RETRIEVE_MANUALFORWARD)) ? TRUE : FALSE);
}

BOOL COOLOpenDialog::GetRetrieveStartTime(CTimeKey &tTimeKey) CONST
{
	tTimeKey = m_tRetrieveStartTime;
	return(((m_nRetrieveMode & OOL_RETRIEVE_AUTOFORWARD) || (m_nRetrieveMode & OOL_RETRIEVE_PSEUDOREALTIME) || (m_nRetrieveMode & OOL_RETRIEVE_MANUALFORWARD)) ? TRUE : FALSE);
}

BOOL COOLOpenDialog::GetRetrieveStopTime(CTimeKey &tTimeKey) CONST
{
	tTimeKey = m_tRetrieveStopTime;
	return((((m_nRetrieveMode & OOL_RETRIEVE_AUTOFORWARD) || (m_nRetrieveMode & OOL_RETRIEVE_PSEUDOREALTIME) || (m_nRetrieveMode & OOL_RETRIEVE_MANUALFORWARD)) && (m_nRetrieveMode & OOL_RETRIEVE_STOPBYTIME)) ? TRUE : FALSE);
}

BOOL COOLOpenDialog::GetRetrieveFileName(CString &szFileName) CONST
{
	szFileName = ((m_nRetrieveMode & OOL_RETRIEVE_AUTOFORWARD) || (m_nRetrieveMode & OOL_RETRIEVE_PSEUDOREALTIME) || (m_nRetrieveMode & OOL_RETRIEVE_MANUALFORWARD)) ? (LPCTSTR)m_szRetrieveFileName : EMPTYSTRING;
	return !szFileName.IsEmpty();
}

BOOL COOLOpenDialog::IsRetrievingModified() CONST
{
	return((m_nRetrieveMode != 0) ? TRUE : FALSE);
}

BOOL COOLOpenDialog::GetPrintJobs(COOLPrintJobs &pPrintJobs) CONST
{
	CByteArray  nPrintInfo;

	return((IsPrintingModified()) ? pPrintJobs.Copy(&m_pPrintJobs) : pPrintJobs.Unmap(nPrintInfo));
}

BOOL COOLOpenDialog::IsPrintingModified() CONST
{
	return((m_pPrintJobs.GetSize() > 0) ? TRUE : FALSE);
}

COOLWnd *COOLOpenDialog::GetParent() CONST
{
	return((COOLWnd *)CDisplayDialog::GetParent());
}

VOID COOLOpenDialog::EnumLayouts()
{
	INT  nLayout;
	INT  nLayouts;
	CString  szTitle;
	CString  szLayout;
	CPtrArray  pLayouts;
	CDisplayWnd  *pDisplayWnd;

	for (nLayout = 0, nLayouts = (IsDlgButtonChecked(IDC_OOL_OPEN_MODE_HISTORY)) ? GetDisplayArea()->EnumDisplays(pLayouts) : 0, SendDlgItemMessage(IDC_OOL_OPEN_DISPLAY, CB_RESETCONTENT); nLayout < nLayouts; nLayout++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pLayouts.GetAt(nLayout)) && LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_OOL  &&  pDisplayWnd->GetScope() == DISPLAY_SCOPE_LOCAL)
		{
			for (szTitle.Format(STRING(IDS_WINDOW_FULLTITLE), STRING(IDS_DISPLAY_TITLE_OOL), EMPTYSTRING), pDisplayWnd->GetWindowText(szLayout); szLayout.Left(szTitle.GetLength()) == szTitle; )
			{
				SendDlgItemMessage(IDC_OOL_OPEN_DISPLAY, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szLayout.Mid(szTitle.GetLength()));
				break;
			}
		}
	}
}

BOOL COOLOpenDialog::Check(BOOL bModified) CONST
{
	CString  szTitle;

	return((GetLayout(szTitle) && (IsDlgButtonChecked(IDC_OOL_OPEN_MODE_REALTIME) || (IsDlgButtonChecked(IDC_OOL_OPEN_MODE_HISTORY) && !szTitle.IsEmpty() && (GetParent()->Find(MAKELONG(DISPLAY_TYPE_OOL, GetType()), GetMode(), szTitle) || IsRetrievingModified())))) ? TRUE : FALSE);
}

void COOLOpenDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COOLOpenDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void COOLOpenDialog::PostNcDestroy()
{
	m_pPrintJobs.RemoveAll();
	m_nFilterColors.RemoveAll();
	m_nLayoutColumns.RemoveAll();
	m_pParameterFilters.RemoveAll();
	CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(COOLOpenDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(COOLOpenDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_OOL_OPEN_SETTINGS, OnSettings)
	ON_BN_CLICKED(IDC_OOL_OPEN_TYPE_NORMAL, OnTypeNormal)
	ON_BN_CLICKED(IDC_OOL_OPEN_MODE_REALTIME, OnRealtimeMode)
	ON_BN_CLICKED(IDC_OOL_OPEN_MODE_HISTORY, OnHistoryMode)
	ON_BN_CLICKED(IDC_OOL_OPEN_HELP, OnHelp)
	ON_CBN_EDITCHANGE(IDC_OOL_OPEN_DISPLAY, OnEditchangeTitle)
	ON_CBN_SELCHANGE(IDC_OOL_OPEN_DISPLAY, OnSelchangeTitle)
	ON_CBN_DBLCLK(IDC_OOL_OPEN_DISPLAY, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COOLOpenDialog message handlers

BOOL COOLOpenDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	CheckRadioButton(IDC_OOL_OPEN_TYPE_NORMAL, IDC_OOL_OPEN_TYPE_NORMAL, IDC_OOL_OPEN_TYPE_NORMAL);
	CheckDlgButton(IDC_OOL_OPEN_MODE_REALTIME, !CheckAccountPrivilege(PRIVILEGE_OFFLINE_OPERATE));
	CheckDlgButton(IDC_OOL_OPEN_MODE_HISTORY, FALSE);
	GetDlgItem(IDC_OOL_OPEN_DETAILS)->EnableWindow();
	GetDlgItem(IDC_OOL_OPEN_DISPLAY_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_OOL_OPEN_MODE_HISTORY));
	GetDlgItem(IDC_OOL_OPEN_DISPLAY)->EnableWindow(IsDlgButtonChecked(IDC_OOL_OPEN_MODE_HISTORY));
	GetDlgItem(IDC_OOL_OPEN_TYPE)->EnableWindow();
	GetDlgItem(IDC_OOL_OPEN_TYPE_NORMAL)->EnableWindow();
	GetDlgItem(IDC_OOL_OPEN_MODE)->EnableWindow();
	GetDlgItem(IDC_OOL_OPEN_MODE_REALTIME)->EnableWindow();
	GetDlgItem(IDC_OOL_OPEN_MODE_HISTORY)->EnableWindow(CheckAccountPrivilege(PRIVILEGE_OFFLINE_OPERATE));
	GetDlgItem(IDOK)->EnableWindow(Check());
	EnumLayouts();
	return TRUE;
}

void COOLOpenDialog::OnSettings()
{
	ReportEvent((m_dlgSettings.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void COOLOpenDialog::OnTypeNormal()
{
	GetDlgItem(IDC_OOL_OPEN_DISPLAY)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLOpenDialog::OnEditchangeTitle()
{
	CString  szTitle;

	GetDlgItem(IDC_OOL_OPEN_DISPLAY)->GetWindowText(szTitle);
	GetDlgItem(IDC_OOL_OPEN_SETTINGS)->EnableWindow((!GetParent()->Find(MAKELONG(DISPLAY_TYPE_OOL, GetType()), GetMode(), szTitle)) ? !szTitle.IsEmpty() : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLOpenDialog::OnSelchangeTitle()
{
	CString  szTitle;

	GetDlgItem(IDC_OOL_OPEN_SETTINGS)->EnableWindow((!GetParent()->Find(MAKELONG(DISPLAY_TYPE_OOL, GetType()), GetMode(), (szTitle = Combobox_GetText(GetDlgItem(IDC_OOL_OPEN_DISPLAY), (INT)SendDlgItemMessage(IDC_OOL_OPEN_DISPLAY, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_OOL_OPEN_DISPLAY, CB_GETCURSEL)))))) ? !szTitle.IsEmpty() : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLOpenDialog::OnRealtimeMode()
{
	SendDlgItemMessage(IDC_OOL_OPEN_DISPLAY, CB_RESETCONTENT);
	GetDlgItem(IDC_OOL_OPEN_DISPLAY_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOL_OPEN_DISPLAY)->EnableWindow(FALSE);
	GetDlgItem(IDC_OOL_OPEN_SETTINGS)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void COOLOpenDialog::OnHistoryMode()
{
	CString  szTitle;

	if (IsDlgButtonChecked(IDC_OOL_OPEN_MODE_HISTORY))
	{
		if (!GetDlgItem(IDC_OOL_OPEN_DISPLAY)->GetWindowTextLength() && !SendDlgItemMessage(IDC_OOL_OPEN_DISPLAY, CB_GETCOUNT))
		{
			GetDlgItem(IDC_OOL_OPEN_DISPLAY_STATIC)->EnableWindow();
			GetDlgItem(IDC_OOL_OPEN_DISPLAY)->EnableWindow();
			GetDlgItem(IDC_OOL_OPEN_SETTINGS)->EnableWindow(FALSE);
			EnumLayouts();
		}
		if (!IsWindow(m_dlgRetrievals.GetSafeHwnd()))
		{
			for (ReportEvent((m_dlgRetrievals.Create(this, (szTitle = (GetLayout(szTitle)) ? szTitle : STRING(IDS_WINDOW_UNKNOWNTITLE))) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR); SendDlgItemMessage(IDC_OOL_OPEN_DISPLAY, CB_GETCOUNT) > 0; )
			{
				GetDlgItem(IDC_OOL_OPEN_DISPLAY)->SetFocus();
				break;
			}
			for (; IsDlgButtonChecked(IDC_OOL_OPEN_MODE_REALTIME); )
			{
				GetDlgItem(IDC_OOL_OPEN_MODE_REALTIME)->SetFocus();
				break;
			}
		}
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

BOOL COOLOpenDialog::OnCloseSettingsDialog(UINT nCode)
{
	if (nCode == IDOK)
	{
		if (m_dlgSettings.IsLayoutModified())
		{
			m_dlgSettings.GetLayout(m_nLayoutColumns);
			m_dlgSettings.GetLayoutTitleFont(&m_fntLayoutTitle);
			m_dlgSettings.GetLayoutItemsFont(&m_fntLayoutItems);
			m_dlgSettings.GetLayoutInvalidDataMode(m_bLayoutInvalidData);
			m_dlgSettings.GetLayoutBadDataMode(m_bLayoutBadData);
			m_dlgSettings.GetLayoutToolTipMode(m_bLayoutToolTips);
		}
		if (m_dlgSettings.IsFilteringModified())
		{
			m_dlgSettings.GetParameterFilters(m_pParameterFilters);
			m_dlgSettings.GetFilterColors(m_nFilterColors);
		}
		if (m_dlgSettings.IsRetrievingModified()) m_dlgSettings.GetRetrieveFileName(m_szRetrieveFileName);
		if (m_dlgSettings.IsPrintingModified()) m_dlgSettings.GetPrintJobs(m_pPrintJobs);
	}
	return TRUE;
}

BOOL COOLOpenDialog::OnCloseRetrieveDialog(UINT nCode)
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
		CheckDlgButton(IDC_OOL_OPEN_MODE_REALTIME, TRUE);
		CheckDlgButton(IDC_OOL_OPEN_MODE_HISTORY, FALSE);
		SendDlgItemMessage(IDC_OOL_OPEN_DISPLAY, CB_RESETCONTENT);
		GetDlgItem(IDC_OOL_OPEN_DISPLAY_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_OOL_OPEN_DISPLAY)->EnableWindow(FALSE);
		GetDlgItem(IDC_OOL_OPEN_SETTINGS)->EnableWindow(FALSE);
	}
	return TRUE;
}

void COOLOpenDialog::OnOK()
{
	CString  szTitle;
	COOLWnd  *pOOLWnd[2];
	CHourglassCursor  cCursor;

	if ((pOOLWnd[0] = GetParent()))
	{
		for (GetLayout(szTitle); (pOOLWnd[1] = pOOLWnd[0]->Find(MAKELONG(DISPLAY_TYPE_OOL, GetType()), GetMode(), szTitle)); )
		{
			GetDisplayArea()->ActivateDisplay(pOOLWnd[1]);
			EndDialog(IDCANCEL);
			return;
		}
		if (!pOOLWnd[0]->OnCloseOpenDialog(IDOK))
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

void COOLOpenDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	GetParent()->OnCloseOpenDialog(IDCANCEL);
	CDisplayDialog::OnCancel();
}

BOOL COOLOpenDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_OOLOPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void COOLOpenDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_OOLOPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// COOLRetrieveThread

IMPLEMENT_DYNCREATE(COOLRetrieveThread, CThread)

COOLRetrieveThread::COOLRetrieveThread() : CThread()
{
	m_nMode = 0;
	m_nSpeed = 0;
	m_tInterval = 0;
	m_tStartTime = 0;
	m_tStopTime = 0;
	m_pbFlag = (LPLONG)NULL;
	m_bInit[0] = (HANDLE)NULL;
	m_bInit[1] = (HANDLE)NULL;
	m_hAction[OOLRETRIEVETHREAD_ACTION_STOP] = (HANDLE)NULL;
	m_hAction[OOLRETRIEVETHREAD_ACTION_AUTOFORWARD] = (HANDLE)NULL;
	m_hAction[OOLRETRIEVETHREAD_ACTION_AUTOBACKWARD] = (HANDLE)NULL;
	m_hAction[OOLRETRIEVETHREAD_ACTION_MANUALFORWARD] = (HANDLE)NULL;
	m_hAction[OOLRETRIEVETHREAD_ACTION_MANUALBACKWARD] = (HANDLE)NULL;
	m_hAction[OOLRETRIEVETHREAD_ACTION_PSEUDOREALTIME] = (HANDLE)NULL;
}

BOOL COOLRetrieveThread::Start(COOLWnd *pParentWnd, HANDLE bInit, HANDLE bContinue, LPCTSTR pszFileName, UINT nMode, UINT nSpeed, CONST CTimeSpan &tInterval, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, LONG *pbFlag, HANDLE bRetrieveStop, HANDLE bRetrieveAutoForward, HANDLE bRetrieveAutoBackward, HANDLE bRetrieveManualForward, HANDLE bRetrieveManualBackward, HANDLE bRetrievePseudoRealtime)
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
	m_hAction[OOLRETRIEVETHREAD_ACTION_STOP] = bRetrieveStop;
	m_hAction[OOLRETRIEVETHREAD_ACTION_AUTOFORWARD] = bRetrieveAutoForward;
	m_hAction[OOLRETRIEVETHREAD_ACTION_AUTOBACKWARD] = bRetrieveAutoBackward;
	m_hAction[OOLRETRIEVETHREAD_ACTION_MANUALFORWARD] = bRetrieveManualForward;
	m_hAction[OOLRETRIEVETHREAD_ACTION_MANUALBACKWARD] = bRetrieveManualBackward;
	m_hAction[OOLRETRIEVETHREAD_ACTION_PSEUDOREALTIME] = bRetrievePseudoRealtime;
	return((ResetEvent(bInit)) ? CreateThread(pParentWnd, THREAD_PRIORITY_BELOW_NORMAL) : FALSE);
}

BOOL COOLRetrieveThread::Stop()
{
	return((DestroyThread() >= 0) ? TRUE : FALSE);
}

BOOL COOLRetrieveThread::InitializeTMData(COolParameters &pOolParameters, BOOL bBadData)
{
	return m_cTMEnvironment.Initialize(pOolParameters, bBadData);
}
BOOL COOLRetrieveThread::InitializeTMData(CTMParameters &pTMParameters, BOOL bBadData)
{
	return m_cTMEnvironment.Initialize(pTMParameters, bBadData);
}

int COOLRetrieveThread::Run()
{
	UINT  nAction;
	UINT  nResult;
	DWORD  dwResult;
	TIMETAG  tTime;
	CTimeKey  tTimeKey;
	CTimeTag  tTimeTag[2];
	COOLWnd  *pOOLWnd = (COOLWnd *)GetThreadInfo();

	StartRetrieving();
	if (m_cTMEnvironment.Create(GetDatabase()))
	{
		if (m_cTMProcessEngine.Open(GetDatabase(), GetAccountSpacecraftName(), GetRetrieveFileName(), &m_cTMEnvironment))
		{
			for (BeginWaitCursor(), pOOLWnd->SetRetrieveMode((m_nMode = (m_nMode & (OOL_RETRIEVE_AUTOBACKWARD | OOL_RETRIEVE_MANUALBACKWARD)) ? ((m_nMode & ~(OOL_RETRIEVE_AUTOBACKWARD | OOL_RETRIEVE_MANUALBACKWARD | OOL_RETRIEVE_STOPPED | OOL_RETRIEVE_RELATIVE)) | OOL_RETRIEVE_MANUALFORWARD) : (m_nMode & ~(OOL_RETRIEVE_STOPPED | OOL_RETRIEVE_RELATIVE)))), pOOLWnd->Reset(&m_cTMEnvironment), SignalObjectAndWait(m_bInit[0], m_bInit[1], INFINITE, FALSE), nResult = m_cTMProcessEngine.ProcessTMData(GetDatabase(), &m_cTMEnvironment, (tTimeKey = GetRetrieveStartTime())), nAction = 0; (dwResult = Wait(0)) == WAIT_TIMEOUT && !pOOLWnd->IsInitialized(); )
			{
				SwitchToThread();
				continue;
			}
			for (; dwResult == WAIT_TIMEOUT; BeginWaitCursor())
			{
				if ((GetRetrieveMode() & OOL_RETRIEVE_AUTOFORWARD) && !(GetRetrieveMode() & OOL_RETRIEVE_STOPPED))
				{
					for (; (nResult & HISTORYFILE_SUCCESS) && !(GetRetrieveMode() & OOL_RETRIEVE_RELATIVE) && (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT && ((!(GetRetrieveMode() & OOL_RETRIEVE_EXACTTIME) && !pOOLWnd->Update(tTimeKey, &m_cTMEnvironment, nResult)) || ((GetRetrieveMode() & OOL_RETRIEVE_EXACTTIME) && tTimeKey < GetRetrieveStartTime())); )
					{
						if (!((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, 0)) & HISTORYFILE_SUCCESS)) break;
						if (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS))
						{
							ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
							pOOLWnd->SetRetrieveMode(pOOLWnd->GetRetrieveMode() | OOL_RETRIEVE_STOPPED);
							pOOLWnd->UpdateBars();
							break;
						}
						if ((GetRetrieveMode() & OOL_RETRIEVE_STOPBYTIME) && GetRetrieveStopTime() < tTimeKey)
						{
							pOOLWnd->SetRetrieveMode(pOOLWnd->GetRetrieveMode() | OOL_RETRIEVE_STOPPED);
							pOOLWnd->UpdateBars();
							break;
						}
					}
					EndWaitCursor();
					if ((((nResult & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS))) || (GetRetrieveMode() & OOL_RETRIEVE_RELATIVE)) && (!(GetRetrieveMode() & OOL_RETRIEVE_STOPBYTIME) || GetRetrieveStopTime() >= tTimeKey) && dwResult == WAIT_TIMEOUT)
					{
						if ((!(GetRetrieveMode() & OOL_RETRIEVE_RELATIVE) && (!(GetRetrieveMode() & OOL_RETRIEVE_EXACTTIME) || pOOLWnd->Update(tTimeKey, &m_cTMEnvironment, (nResult = (nResult | HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS) & ~HISTORYFILE_TMUNIT) & (HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS)) || TRUE)) || (GetRetrieveMode() & OOL_RETRIEVE_RELATIVE))
						{
							for (; (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 10 * (10 - GetRetrieveSpeed())*(10 - GetRetrieveSpeed()))) == WAIT_TIMEOUT; )
							{
								if (((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, GetRetrieveInterval())) & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)))
								{
									if (!(GetRetrieveMode() & OOL_RETRIEVE_STOPBYTIME) || GetRetrieveStopTime() >= tTimeKey)
									{
										pOOLWnd->Update(tTimeKey, &m_cTMEnvironment, nResult);
										continue;
									}
								}
								if (nResult & HISTORYFILE_SUCCESS)
								{
									ReportEvent((GetRetrieveMode() & OOL_RETRIEVE_STOPBYEND) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING : USER_NOERROR);
									pOOLWnd->SetRetrieveMode(pOOLWnd->GetRetrieveMode() | OOL_RETRIEVE_STOPPED);
									pOOLWnd->UpdateBars();
								}
								break;
							}
						}
					}
					if (!(nResult & HISTORYFILE_SUCCESS))
					{
						ReportEvent((nResult == HISTORYFILE_DATA_NONE) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING : ((nResult == HISTORYFILE_OPEN_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_OPEN_FAILURE : ((nResult == HISTORYFILE_WRITE_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_WRITE_FAILURE : ((nResult == HISTORYFILE_READ_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_READ_FAILURE : ((nResult == HISTORYFILE_ERROR) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE : SYSTEM_NOERROR)))));
						pOOLWnd->SetRetrieveMode(pOOLWnd->GetRetrieveMode() | OOL_RETRIEVE_STOPPED);
						pOOLWnd->Reset(&m_cTMEnvironment);
						pOOLWnd->UpdateBars();
						break;
					}
				}
				if ((GetRetrieveMode() & OOL_RETRIEVE_AUTOBACKWARD) && !(GetRetrieveMode() & OOL_RETRIEVE_STOPPED))
				{
					if ((nResult & HISTORYFILE_SUCCESS) && (GetRetrieveMode() & OOL_RETRIEVE_RELATIVE) && dwResult == WAIT_TIMEOUT)
					{
						for (EndWaitCursor(); (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 10 * (10 - GetRetrieveSpeed())*(10 - GetRetrieveSpeed()))) == WAIT_TIMEOUT; )
						{
							if (((nResult = m_cTMProcessEngine.RewindTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, GetRetrieveInterval())) & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)))
							{
								pOOLWnd->Update(tTimeKey, &m_cTMEnvironment, nResult);
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
							pOOLWnd->Update(tTimeKey, &m_cTMEnvironment, nResult);
							pOOLWnd->SetRetrieveMode(pOOLWnd->GetRetrieveMode() | OOL_RETRIEVE_STOPPED);
							pOOLWnd->UpdateBars();
						}
					}
					else
					{
						ReportEvent((nResult == HISTORYFILE_DATA_NONE) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING : ((nResult == HISTORYFILE_OPEN_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_OPEN_FAILURE : ((nResult == HISTORYFILE_WRITE_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_WRITE_FAILURE : ((nResult == HISTORYFILE_READ_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_READ_FAILURE : ((nResult == HISTORYFILE_ERROR) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE : SYSTEM_NOERROR)))));
						pOOLWnd->SetRetrieveMode(pOOLWnd->GetRetrieveMode() | OOL_RETRIEVE_STOPPED);
						pOOLWnd->Reset(&m_cTMEnvironment);
						pOOLWnd->UpdateBars();
						EndWaitCursor();
						break;
					}
					EndWaitCursor();
				}
				if ((GetRetrieveMode() & OOL_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & OOL_RETRIEVE_STOPPED))
				{
					for (; (nResult & HISTORYFILE_SUCCESS) && !(GetRetrieveMode() & OOL_RETRIEVE_RELATIVE) && (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT && ((!(GetRetrieveMode() & OOL_RETRIEVE_EXACTTIME) && !pOOLWnd->Update(tTimeKey, &m_cTMEnvironment, nResult)) || ((GetRetrieveMode() & OOL_RETRIEVE_EXACTTIME) && tTimeKey < GetRetrieveStartTime())); )
					{
						if (!((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, 0)) & HISTORYFILE_SUCCESS)) break;
						if (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS))
						{
							ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
							pOOLWnd->SetRetrieveMode(pOOLWnd->GetRetrieveMode() | OOL_RETRIEVE_STOPPED);
							pOOLWnd->UpdateBars();
							break;
						}
					}
					EndWaitCursor();
					if ((((nResult & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS))) || (GetRetrieveMode() & OOL_RETRIEVE_RELATIVE)) && dwResult == WAIT_TIMEOUT)
					{
						if ((!(GetRetrieveMode() & OOL_RETRIEVE_RELATIVE) && (!(GetRetrieveMode() & OOL_RETRIEVE_EXACTTIME) || pOOLWnd->Update(tTimeKey, &m_cTMEnvironment, (nResult = (nResult | HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS) & ~HISTORYFILE_TMUNIT) & (HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS)) || TRUE)) || (GetRetrieveMode() & OOL_RETRIEVE_RELATIVE))
						{
							for (; (dwResult = (!(GetRetrieveMode() & OOL_RETRIEVE_RELATIVE) || nAction != OOLRETRIEVETHREAD_ACTION_MANUALFORWARD) ? Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, INFINITE) : (WAIT_OBJECT_0 + nAction + 1)) == WAIT_OBJECT_0 + OOLRETRIEVETHREAD_ACTION_MANUALFORWARD + 1; EndWaitCursor())
							{
								for (BeginWaitCursor(TRUE); (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT; )
								{
									if (((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, GetRetrieveInterval())) & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)))
									{
										if (pOOLWnd->Update(tTimeKey, &m_cTMEnvironment, nResult)) break;
										continue;
									}
									if (nResult & HISTORYFILE_SUCCESS)
									{
										if (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS))
										{
											ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
											pOOLWnd->SetRetrieveMode(pOOLWnd->GetRetrieveMode() | OOL_RETRIEVE_STOPPED);
											pOOLWnd->UpdateBars();
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
					}
					if (!(nResult & HISTORYFILE_SUCCESS))
					{
						ReportEvent((nResult == HISTORYFILE_DATA_NONE) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING : ((nResult == HISTORYFILE_OPEN_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_OPEN_FAILURE : ((nResult == HISTORYFILE_WRITE_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_WRITE_FAILURE : ((nResult == HISTORYFILE_READ_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_READ_FAILURE : ((nResult == HISTORYFILE_ERROR) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE : SYSTEM_NOERROR)))));
						pOOLWnd->SetRetrieveMode(pOOLWnd->GetRetrieveMode() | OOL_RETRIEVE_STOPPED);
						pOOLWnd->Reset(&m_cTMEnvironment);
						pOOLWnd->UpdateBars();
						break;
					}
				}
				if ((GetRetrieveMode() & OOL_RETRIEVE_MANUALBACKWARD) && !(GetRetrieveMode() & OOL_RETRIEVE_STOPPED))
				{
					if ((nResult & HISTORYFILE_SUCCESS) && (GetRetrieveMode() & OOL_RETRIEVE_RELATIVE) && dwResult == WAIT_TIMEOUT)
					{
						for (EndWaitCursor(); (dwResult = (nAction != OOLRETRIEVETHREAD_ACTION_MANUALBACKWARD) ? Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, INFINITE) : (WAIT_OBJECT_0 + nAction + 1)) == WAIT_OBJECT_0 + OOLRETRIEVETHREAD_ACTION_MANUALBACKWARD + 1; EndWaitCursor())
						{
							for (BeginWaitCursor(TRUE); (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT; )
							{
								if (((nResult = m_cTMProcessEngine.RewindTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, GetRetrieveInterval())) & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)))
								{
									if (pOOLWnd->Update(tTimeKey, &m_cTMEnvironment, nResult)) break;
									continue;
								}
								if (nResult & HISTORYFILE_SUCCESS)
								{
									if (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS))
									{
										ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
										pOOLWnd->Update(tTimeKey, &m_cTMEnvironment, nResult);
										pOOLWnd->SetRetrieveMode(pOOLWnd->GetRetrieveMode() | OOL_RETRIEVE_STOPPED);
										pOOLWnd->UpdateBars();
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
						pOOLWnd->SetRetrieveMode(pOOLWnd->GetRetrieveMode() | OOL_RETRIEVE_STOPPED);
						pOOLWnd->Reset(&m_cTMEnvironment);
						pOOLWnd->UpdateBars();
						EndWaitCursor();
						break;
					}
					EndWaitCursor();
				}
				if ((GetRetrieveMode() & OOL_RETRIEVE_PSEUDOREALTIME) && !(GetRetrieveMode() & OOL_RETRIEVE_STOPPED))
				{
					for (; (nResult & HISTORYFILE_SUCCESS) && !(GetRetrieveMode() & OOL_RETRIEVE_RELATIVE) && (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT && ((!(GetRetrieveMode() & OOL_RETRIEVE_EXACTTIME) && !pOOLWnd->Update(tTimeKey, &m_cTMEnvironment, nResult)) || ((GetRetrieveMode() & OOL_RETRIEVE_EXACTTIME) && tTimeKey < GetRetrieveStartTime())); )
					{
						if (!((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, 0)) & HISTORYFILE_SUCCESS)) break;
						if (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS))
						{
							ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
							pOOLWnd->SetRetrieveMode(pOOLWnd->GetRetrieveMode() | OOL_RETRIEVE_STOPPED);
							pOOLWnd->UpdateBars();
							break;
						}
						if ((GetRetrieveMode() & OOL_RETRIEVE_STOPBYTIME) && GetRetrieveStopTime() < tTimeKey)
						{
							pOOLWnd->SetRetrieveMode(pOOLWnd->GetRetrieveMode() | OOL_RETRIEVE_STOPPED);
							pOOLWnd->UpdateBars();
							break;
						}
					}
					EndWaitCursor();
					if ((((nResult & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS))) || (GetRetrieveMode() & OOL_RETRIEVE_RELATIVE)) && (!(GetRetrieveMode() & OOL_RETRIEVE_STOPBYTIME) || GetRetrieveStopTime() >= tTimeKey) && dwResult == WAIT_TIMEOUT)
					{
						if ((!(GetRetrieveMode() & OOL_RETRIEVE_RELATIVE) && (!(GetRetrieveMode() & OOL_RETRIEVE_EXACTTIME) || pOOLWnd->Update(tTimeKey, &m_cTMEnvironment, (nResult = (nResult | HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS) & ~HISTORYFILE_TMUNIT) & (HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS)) || TRUE)) || (GetRetrieveMode() & OOL_RETRIEVE_RELATIVE))
						{
							for (tTimeTag[0] = ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)) ? ((nResult & HISTORYFILE_TMUNIT) ? m_cTMEnvironment.GetTMUnit()->GetTimeTag() : CTimeTag(tTimeKey)) : CTimeTag(tTimeKey), tTimeTag[1] = CTimeTag(), tTime = CTimeTag().GetTime(); (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT; tTime = CTimeTag().GetTime())
							{
								if (((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, 0)) & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)))
								{
									if ((dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, (((nResult & HISTORYFILE_TMUNIT) && tTimeTag[1].GetTime() - tTimeTag[0].GetTime() + m_cTMEnvironment.GetTMUnit()->GetTimeTag().GetTime() > tTime) || ((nResult & HISTORYFILE_TMPARAMETERS) && tTimeTag[1].GetTime() - tTimeTag[0].GetTime() + CTimeTag(tTimeKey).GetTime() > tTime)) ? ((nResult & HISTORYFILE_TMUNIT) ? (DWORD)((tTimeTag[1].GetTime() - tTimeTag[0].GetTime() + m_cTMEnvironment.GetTMUnit()->GetTimeTag().GetTime() - tTime) / 1000) : (DWORD)((tTimeTag[1].GetTime() - tTimeTag[0].GetTime() + CTimeTag(tTimeKey).GetTime() - tTime) / 1000)) : 0)) != WAIT_TIMEOUT) break;
									if ((!(GetRetrieveMode() & OOL_RETRIEVE_STOPBYTIME) || GetRetrieveStopTime() >= tTimeKey) && ((nResult & HISTORYFILE_SYNCHRONIZE) || !tTimeTag[0].GetTime()))
									{
										tTimeTag[0] = (nResult & HISTORYFILE_TMUNIT) ? m_cTMEnvironment.GetTMUnit()->GetTimeTag() : CTimeTag(tTimeKey);
										tTimeTag[1] = tTime = CTimeTag().GetTime();
									}
									if (!(GetRetrieveMode() & OOL_RETRIEVE_STOPBYTIME) || GetRetrieveStopTime() >= tTimeKey)
									{
										pOOLWnd->Update(tTimeKey, &m_cTMEnvironment, nResult);
										continue;
									}
								}
								if (nResult & HISTORYFILE_SUCCESS)
								{
									ReportEvent((GetRetrieveMode() & OOL_RETRIEVE_STOPBYEND) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING : USER_NOERROR);
									pOOLWnd->SetRetrieveMode(pOOLWnd->GetRetrieveMode() | OOL_RETRIEVE_STOPPED);
									pOOLWnd->UpdateBars();
								}
								break;
							}
						}
					}
					if (!(nResult & HISTORYFILE_SUCCESS))
					{
						ReportEvent((nResult == HISTORYFILE_DATA_NONE) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING : ((nResult == HISTORYFILE_OPEN_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_OPEN_FAILURE : ((nResult == HISTORYFILE_WRITE_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_WRITE_FAILURE : ((nResult == HISTORYFILE_READ_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_READ_FAILURE : ((nResult == HISTORYFILE_ERROR) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE : SYSTEM_NOERROR)))));
						pOOLWnd->SetRetrieveMode(pOOLWnd->GetRetrieveMode() | OOL_RETRIEVE_STOPPED);
						pOOLWnd->Reset(&m_cTMEnvironment);
						pOOLWnd->UpdateBars();
						break;
					}
				}
				if ((GetRetrieveMode() & OOL_RETRIEVE_AUTOFORWARD) || (GetRetrieveMode() & OOL_RETRIEVE_AUTOBACKWARD) || (GetRetrieveMode() & OOL_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & OOL_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & OOL_RETRIEVE_PSEUDOREALTIME))
				{
					while ((dwResult = ((dwResult < WAIT_OBJECT_0 + OOLRETRIEVETHREAD_ACTION_AUTOFORWARD + 1 || dwResult > WAIT_OBJECT_0 + OOLRETRIEVETHREAD_ACTION_PSEUDOREALTIME + 1) && dwResult != WAIT_OBJECT_0) ? Wait(m_hAction, OOLRETRIEVETHREAD_ACTION_TYPES, FALSE, INFINITE, FALSE) : dwResult) == WAIT_OBJECT_0 + OOLRETRIEVETHREAD_ACTION_STOP + 1)
					{
						m_nMode = (GetRetrieveMode() & (OOL_RETRIEVE_STOPBYTIME | OOL_RETRIEVE_STOPBYEND)) | OOL_RETRIEVE_STOPPED | OOL_RETRIEVE_RELATIVE;
						m_nMode |= ((GetRetrieveMode() & (OOL_RETRIEVE_STOPBYTIME | OOL_RETRIEVE_STOPBYEND)) == 0) ? OOL_RETRIEVE_STOPBYEND : 0;
						pOOLWnd->SetRetrieveMode(m_nMode);
						pOOLWnd->UpdateBars();
					}
					if (dwResult == WAIT_OBJECT_0 + OOLRETRIEVETHREAD_ACTION_AUTOFORWARD + 1)
					{
						m_nMode = (GetRetrieveMode() & (OOL_RETRIEVE_STOPBYTIME | OOL_RETRIEVE_STOPBYEND)) | OOL_RETRIEVE_AUTOFORWARD | OOL_RETRIEVE_RELATIVE;
						m_nMode |= ((GetRetrieveMode() & (OOL_RETRIEVE_STOPBYTIME | OOL_RETRIEVE_STOPBYEND)) == 0) ? OOL_RETRIEVE_STOPBYEND : 0;
						nAction = OOLRETRIEVETHREAD_ACTION_AUTOFORWARD;
						pOOLWnd->SetRetrieveMode(m_nMode);
						pOOLWnd->UpdateBars();
						dwResult = WAIT_TIMEOUT;
						continue;
					}
					if (dwResult == WAIT_OBJECT_0 + OOLRETRIEVETHREAD_ACTION_AUTOBACKWARD + 1)
					{
						m_nMode = (GetRetrieveMode() & (OOL_RETRIEVE_STOPBYTIME | OOL_RETRIEVE_STOPBYEND)) | OOL_RETRIEVE_AUTOBACKWARD | OOL_RETRIEVE_RELATIVE;
						m_nMode |= ((GetRetrieveMode() & (OOL_RETRIEVE_STOPBYTIME | OOL_RETRIEVE_STOPBYEND)) == 0) ? OOL_RETRIEVE_STOPBYEND : 0;
						nAction = OOLRETRIEVETHREAD_ACTION_AUTOBACKWARD;
						pOOLWnd->SetRetrieveMode(m_nMode);
						pOOLWnd->UpdateBars();
						dwResult = WAIT_TIMEOUT;
						continue;
					}
					if (dwResult == WAIT_OBJECT_0 + OOLRETRIEVETHREAD_ACTION_MANUALFORWARD + 1)
					{
						m_nMode = (GetRetrieveMode() & (OOL_RETRIEVE_STOPBYTIME | OOL_RETRIEVE_STOPBYEND)) | OOL_RETRIEVE_MANUALFORWARD | OOL_RETRIEVE_RELATIVE;
						nAction = OOLRETRIEVETHREAD_ACTION_MANUALFORWARD;
						pOOLWnd->SetRetrieveMode(m_nMode);
						pOOLWnd->UpdateBars();
						dwResult = WAIT_TIMEOUT;
						continue;
					}
					if (dwResult == WAIT_OBJECT_0 + OOLRETRIEVETHREAD_ACTION_MANUALBACKWARD + 1)
					{
						m_nMode = (GetRetrieveMode() & (OOL_RETRIEVE_STOPBYTIME | OOL_RETRIEVE_STOPBYEND)) | OOL_RETRIEVE_MANUALBACKWARD | OOL_RETRIEVE_RELATIVE;
						nAction = OOLRETRIEVETHREAD_ACTION_MANUALBACKWARD;
						pOOLWnd->SetRetrieveMode(m_nMode);
						pOOLWnd->UpdateBars();
						dwResult = WAIT_TIMEOUT;
						continue;
					}
					if (dwResult == WAIT_OBJECT_0 + OOLRETRIEVETHREAD_ACTION_PSEUDOREALTIME + 1)
					{
						m_nMode = (GetRetrieveMode() & (OOL_RETRIEVE_STOPBYTIME | OOL_RETRIEVE_STOPBYEND)) | OOL_RETRIEVE_PSEUDOREALTIME | OOL_RETRIEVE_RELATIVE;
						m_nMode |= ((GetRetrieveMode() & (OOL_RETRIEVE_STOPBYTIME | OOL_RETRIEVE_STOPBYEND)) == 0) ? OOL_RETRIEVE_STOPBYEND : 0;
						nAction = OOLRETRIEVETHREAD_ACTION_PSEUDOREALTIME;
						pOOLWnd->SetRetrieveMode(m_nMode);
						pOOLWnd->UpdateBars();
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

VOID COOLRetrieveThread::StartRetrieving()
{
	InterlockedExchange(m_pbFlag, TRUE);
}

VOID COOLRetrieveThread::StopRetrieving()
{
	InterlockedExchange(m_pbFlag, FALSE);
}

UINT COOLRetrieveThread::GetRetrieveMode() CONST
{
	return((IsThreadActive()) ? m_nMode : 0);
}

UINT COOLRetrieveThread::GetRetrieveSpeed() CONST
{
	return((IsThreadActive()) ? m_nSpeed : 0);
}

CTimeSpan COOLRetrieveThread::GetRetrieveInterval() CONST
{
	return((IsThreadActive()) ? m_tInterval.GetTotalSeconds() : 0);
}

CTimeKey COOLRetrieveThread::GetRetrieveStartTime() CONST
{
	return((IsThreadActive()) ? m_tStartTime : 0);
}

CTimeKey COOLRetrieveThread::GetRetrieveStopTime() CONST
{
	return((IsThreadActive()) ? m_tStopTime : 0);
}

CString COOLRetrieveThread::GetRetrieveFileName() CONST
{
	return((IsThreadActive()) ? (LPCTSTR)m_szFileName : EMPTYSTRING);
}

VOID COOLRetrieveThread::BeginWaitCursor(BOOL bForced)
{
	POINT  ptCursor;
	COOLWnd  *pOOLWnd;
	CHourglassCursor  cCursor;

	for (GetCursorPos(&ptCursor), InterlockedExchange(m_pbFlag, MAKELONG(TRUE, ((m_nMode & OOL_RETRIEVE_RELATIVE) != OOL_RETRIEVE_RELATIVE || bForced) ? TRUE : FALSE)), SetCursorPos(ptCursor.x, ptCursor.y); (pOOLWnd = (COOLWnd *)GetThreadInfo()); )
	{
		pOOLWnd->UpdateBars();
		break;
	}
}

VOID COOLRetrieveThread::EndWaitCursor()
{
	POINT  ptCursor;
	COOLWnd  *pOOLWnd;
	CHourglassCursor  cCursor;

	for (GetCursorPos(&ptCursor), InterlockedExchange(m_pbFlag, LOWORD(*m_pbFlag)), SetCursorPos(ptCursor.x, ptCursor.y); (pOOLWnd = (COOLWnd *)GetThreadInfo()); )
	{
		pOOLWnd->UpdateBars();
		break;
	}
}

BEGIN_MESSAGE_MAP(COOLRetrieveThread, CThread)
	//{{AFX_MSG_MAP(COOLRetrieveThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COOLRetrieveThread message handlers


/////////////////////////////////////////////////////////////////////////////
// COOLPrintThread

IMPLEMENT_DYNCREATE(COOLPrintThread, CThread)

BOOL COOLPrintThread::Start(COOLWnd *pParentWnd)
{
	return CreateThread(pParentWnd);
}

BOOL COOLPrintThread::Stop()
{
	return((DestroyThread() >= 0) ? TRUE : FALSE);
}

BOOL COOLPrintThread::SetPrintJobs(CONST COOLPrintJobs &pPrintJobs)
{
	INT  nJob[2][2];
	INT  nJobs[2][2];
	COOLPrintJobInfo  *pJobInfo;
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
			if ((pJobInfo = new COOLPrintJobInfo))
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

BOOL COOLPrintThread::GetPrintJobs(COOLPrintJobs &pPrintJobs) CONST
{
	CByteArray  nPrintInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(((m_pPrintJobs.GetSize() > 0 && pPrintJobs.Copy(&m_pPrintJobs)) || pPrintJobs.Unmap(nPrintInfo)) ? TRUE : FALSE);
}

int COOLPrintThread::Run()
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
	COOLPrintJobInfo  *pJobInfo[2];
	COOLWnd  *pOOLWnd = (COOLWnd *)GetThreadInfo();

	for (dwJobResult = 0; Lock(); )
	{
		if (dwJobResult == WAIT_OBJECT_0 + 1 || !dwJobResult)
		{
			for (nJob = 0, nJobs = (INT)m_pPrintJobs.GetSize(); nJob < nJobs; nJob++)
			{
				if ((pJobInfo[0] = m_pPrintJobs.GetAt(nJob)) && (pJobInfo[0]->GetPrintMode() & OOL_PRINT_ACTIVE))
				{
					if (pJobInfo[0]->GetPrintAtDailyTime(tJobDailyTime) || pJobInfo[0]->GetPrintAtDailyTime(tJobDailyTime, nJobStopCount) || pJobInfo[0]->GetPrintAtDailyTime(tJobDailyTime, tJobStopTime))
					{
						pJobInfo[0]->SetPrintLastDailyTime(((tJobTime = CTime::GetCurrentTime().GetTime()).GetTime() % SECONDSPERDAY >= tJobDailyTime.GetTotalSeconds()) ? ((SECONDSPERDAY*(tJobTime.GetTime() / SECONDSPERDAY)) + tJobDailyTime.GetTotalSeconds()) : ((SECONDSPERDAY*(tJobTime.GetTime() / SECONDSPERDAY - 1)) + tJobDailyTime.GetTotalSeconds()));
						continue;
					}
				}
			}
		}
		if ((pJobInfo[0] = ((tJobInterval = m_pPrintJobs.Schedule()) == 0) ? m_pPrintJobs.GetAt(0) : (COOLPrintJobInfo *)NULL))
		{
			for (bJobPrint = pOOLWnd->Print(pJobInfo[0]); (pJobInfo[0]->GetPrintMode() & OOL_PRINT_CLEARCOMMENTS) && bJobPrint; )
			{
				for (nJob = 1, nJobs = (INT)m_pPrintJobs.GetSize(); nJob < nJobs; nJob++)
				{
					if ((pJobInfo[1] = m_pPrintJobs.GetAt(nJob)))
					{
						if (pJobInfo[0]->GetName() == pJobInfo[1]->GetName())
						{
							pJobInfo[1]->SetPrintMode(pJobInfo[0]->GetPrintMode() & ~OOL_PRINT_CLEARCOMMENTS);
							pJobInfo[1]->SetComments(EMPTYSTRING);
							break;
						}
					}
				}
				break;
			}
			ReportEvent((!bJobPrint) ? SYSTEM_WARNING_OOL_PRINT_FAILURE : SYSTEM_NOERROR);
			m_pPrintJobs.RemoveAt(0);
			delete pJobInfo[0];
		}
		Unlock();
		if ((dwJobResult = Wait(m_cEvent, FALSE, (tJobInterval >= 0) ? (DWORD)(1000 * min(tJobInterval, SECONDSPERDAY)) : INFINITE)) != WAIT_TIMEOUT  &&  dwJobResult != WAIT_OBJECT_0 + 1) break;
	}
	return 0;
}

BEGIN_MESSAGE_MAP(COOLPrintThread, CThread)
	//{{AFX_MSG_MAP(COOLPrintThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COOLPrintThread message handlers


/////////////////////////////////////////////////////////////////////////////
// COOLToolBar

IMPLEMENT_DYNCREATE(COOLToolBar, CDisplayToolBar)

COOLToolBar::COOLToolBar() : CDisplayToolBar()
{
	return;
}

BEGIN_MESSAGE_MAP(COOLToolBar, CDisplayToolBar)
	//{{AFX_MSG_MAP(COOLToolBar)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COOLToolBar message handlers


/////////////////////////////////////////////////////////////////////////////
// COOLStatusBar

IMPLEMENT_DYNCREATE(COOLStatusBar, CDisplayStatusBar)

COOLStatusBar::COOLStatusBar() : CDisplayStatusBar()
{
	return;
}

BOOL COOLStatusBar::SetIndicators(CONST UINT *pPanesID, INT nCount)
{
	INT  nIndex;
	CRect  rPane;
	CString  szPane;
	CToolInfo  cToolInfo;
	CDisplayLock  cLock(this);

	if (CDisplayStatusBar::SetIndicators(pPanesID, nCount))
	{
		if (CommandToIndex(ID_OOL_STATUSBAR_MESSAGEPANE) >= 0)
		{
			szPane.Format(STRING(IDS_OOL_STATUSBAR_UPDATEMESSAGE), (LPCTSTR)CTimeTag().FormatGmt(), (LPCTSTR)CString(CTimeTag().FormatGmt().Right(1), GetDatabase()->GetTMPacketTagLength()), -1, STRING(IDS_OOL_STATUSBAR_QUALITYGOOD));
			SetPaneInfo(CommandToIndex(ID_OOL_STATUSBAR_MESSAGEPANE), ID_OOL_STATUSBAR_MESSAGEPANE, SBPS_NOBORDERS | SBPS_STRETCH, CalcPaneWidth(szPane + STRING(IDS_OOL_STATUSBAR_TIMECORRELATIONFLAG)));
		}
		if (!IsWindow(m_wndToolTip.GetSafeHwnd()))
		{
			m_wndToolTip.Create(this, TTS_ALWAYSTIP | TTS_NOPREFIX | TTS_BALLOON);
			SetClassLongPtr(m_wndToolTip.GetSafeHwnd(), GCL_STYLE, GetClassLongPtr(m_wndToolTip.GetSafeHwnd(), GCL_STYLE) | CS_DROPSHADOW);
		}
		if (IsWindow(m_wndToolTip.GetSafeHwnd()))
		{
			if ((nIndex = CommandToIndex(ID_OOL_STATUSBAR_MODEPANE)) >= 0)
			{
				for (GetItemRect(nIndex, rPane); !m_wndToolTip.GetToolInfo(cToolInfo, this, ID_OOL_STATUSBAR_MODEPANE); )
				{
					m_wndToolTip.AddTool(this, LPSTR_TEXTCALLBACK, rPane, ID_OOL_STATUSBAR_MODEPANE);
					break;
				}
			}
			if ((nIndex = CommandToIndex(ID_OOL_STATUSBAR_TYPEPANE)) >= 0)
			{
				for (GetItemRect(nIndex, rPane); !m_wndToolTip.GetToolInfo(cToolInfo, this, ID_OOL_STATUSBAR_TYPEPANE); )
				{
					m_wndToolTip.AddTool(this, LPSTR_TEXTCALLBACK, rPane, ID_OOL_STATUSBAR_TYPEPANE);
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

COOLWnd *COOLStatusBar::GetParent() CONST
{
	return((COOLWnd *)CDisplayStatusBar::GetParent());
}

BEGIN_MESSAGE_MAP(COOLStatusBar, CDisplayStatusBar)
	//{{AFX_MSG_MAP(COOLStatusBar)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipNotify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COOLStatusBar message handlers

void COOLStatusBar::OnPaint()
{
	INT  nIndex;
	RECT  rPane;
	CToolInfo  cToolInfo;

	for (CDisplayStatusBar::OnPaint(); IsWindow(m_wndToolTip.GetSafeHwnd()); )
	{
		if ((nIndex = CommandToIndex(ID_OOL_STATUSBAR_MODEPANE)) >= 0 && nIndex < m_prPanes.GetSize())
		{
			for (m_wndToolTip.GetToolInfo(cToolInfo, this, ID_OOL_STATUSBAR_MODEPANE), CopyMemory(&rPane, m_prPanes.GetAt(nIndex), sizeof(RECT)); !EqualRect(&cToolInfo.rect, &rPane); )
			{
				SetRect(&cToolInfo.rect, rPane.left, rPane.top, rPane.right, rPane.bottom);
				m_wndToolTip.SetToolInfo(&cToolInfo);
				break;
			}
		}
		if ((nIndex = CommandToIndex(ID_OOL_STATUSBAR_TYPEPANE)) >= 0 && nIndex < m_prPanes.GetSize())
		{
			for (m_wndToolTip.GetToolInfo(cToolInfo, this, ID_OOL_STATUSBAR_TYPEPANE), CopyMemory(&rPane, m_prPanes.GetAt(nIndex), sizeof(RECT)); !EqualRect(&cToolInfo.rect, &rPane); )
			{
				SetRect(&cToolInfo.rect, rPane.left, rPane.top, rPane.right, rPane.bottom);
				m_wndToolTip.SetToolInfo(&cToolInfo);
				break;
			}
		}
		break;
	}
}

void COOLStatusBar::OnMouseMove(UINT nFlags, CPoint point)
{
	MSG  sMsg;

	if (IsWindow(m_wndToolTip.GetSafeHwnd()))
	{
		CopyMemory(&sMsg, GetCurrentMessage(), sizeof(MSG));
		m_wndToolTip.RelayEvent(&sMsg);
	}
	CDisplayStatusBar::OnMouseMove(nFlags, point);
}

BOOL COOLStatusBar::OnToolTipNotify(UINT nID, NMHDR *pNotifyInfo, LRESULT *pResult)
{
	TOOLTIPTEXT  *pToolTipInfo = (TOOLTIPTEXT *)pNotifyInfo;

	switch (pNotifyInfo->idFrom)
	{
	case ID_OOL_STATUSBAR_MODEPANE:
	{ pToolTipInfo->lpszText = (LPTSTR)STRING(IDS_OOL_STATUSBAR_MODEPANE);
	return TRUE;
	}
	case ID_OOL_STATUSBAR_TYPEPANE:
	{ pToolTipInfo->lpszText = (LPTSTR)STRING(IDS_OOL_STATUSBAR_TYPEPANE);
	return TRUE;
	}
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// COOLToolTip

IMPLEMENT_DYNCREATE(COOLToolTip, CDisplayToolTip)

COOLToolTip::COOLToolTip() : CDisplayToolTip()
{
	return;
}

BEGIN_MESSAGE_MAP(COOLToolTip, CDisplayToolTip)
	//{{AFX_MSG_MAP(COOLToolTip)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COOLToolTip message handlers


/////////////////////////////////////////////////////////////////////////////
// COOLView

IMPLEMENT_DYNCREATE(COOLView, CTextView)

COOLView::COOLView() : CTextView()
{
	m_nColors.InsertAt(OOL_OOLCOLOR_SOFTLIMIT, VGA_COLOR_RED);
	m_nColors.InsertAt(OOL_OOLCOLOR_HARDLIMIT, VGA_COLOR_LTRED);
	m_nColors.InsertAt(OOL_OOLCOLOR_DELTALIMIT, VGA_COLOR_MAGENTA);
	m_nColors.InsertAt(OOL_OOLCOLOR_CONSISTENCYLIMIT, VGA_COLOR_YELLOW);
	m_hToolTipCursor = (HCURSOR)NULL;
	m_bInvalidDataMode = FALSE;
	m_bBadDataMode = FALSE;
	m_bToolTipMode = TRUE;
}

BOOL COOLView::Create(CWnd *pParentWnd, DWORD dwStyle)
{
	return CTextView::Create(pParentWnd, CRect(0, 0, 0, 0), dwStyle);
}

BOOL COOLView::SetLayout(LPCTSTR pszLayout)
{
	return SetLayout(pszLayout, OOL_TITLEITEMS_DEFAULT);
}
BOOL COOLView::SetLayout(LPCTSTR pszLayout, UINT nColumns)
{
	CUIntArray  nColumnItems;

	nColumnItems.Add(OOL_TITLEITEM_ID);
	if (nColumns & OOL_TITLEITEM_DESCRIPTION) nColumnItems.Add(OOL_TITLEITEM_DESCRIPTION);
	if (nColumns & OOL_TITLEITEM_VALUE) nColumnItems.Add(OOL_TITLEITEM_VALUE);
	if (nColumns & OOL_TITLEITEM_LIMIT) nColumnItems.Add(OOL_TITLEITEM_LIMIT);
	if (nColumns & OOL_TITLEITEM_UNIT) nColumnItems.Add(OOL_TITLEITEM_UNIT);
	if (nColumns & OOL_TITLEITEM_OOLTYPE) nColumnItems.Add(OOL_TITLEITEM_OOLTYPE);
	if (nColumns & OOL_TITLEITEM_OOLTIME) nColumnItems.Add(OOL_TITLEITEM_OOLTIME);
	if (nColumns & OOL_TITLEITEM_OOLUNIT) nColumnItems.Add(OOL_TITLEITEM_OOLUNIT);
	return SetLayout(pszLayout, nColumnItems);
}
BOOL COOLView::SetLayout(LPCTSTR pszLayout, CONST CUIntArray &nColumns)
{
	CUIntArray  nWidths;

	return((CalcColumnsWidth(nColumns, nWidths)) ? SetLayout(pszLayout, nColumns, nWidths) : FALSE);
}
BOOL COOLView::SetLayout(LPCTSTR pszLayout, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths)
{
	CStringArray  szColumns;
	CTextViewLock  cLock(this);

	if (!IsWindow(GetSafeHwnd()))
	{
		if (LookupColumnsName(nColumns, szColumns) && SetColumns(szColumns, nWidths))
		{
			m_nLayoutColumns.Copy(nColumns);
			m_szLayout = pszLayout;
			return TRUE;
		}
		return FALSE;
	}
	m_szLayout = pszLayout;
	m_nLayoutColumns.Copy(nColumns);
	return(LookupColumnsName(nColumns, szColumns) > 0 && SetColumns(szColumns, nWidths));
}

BOOL COOLView::GetLayout(CString &szLayout) CONST
{
	CUIntArray  nColumns;

	return GetLayout(szLayout, nColumns);
}
BOOL COOLView::GetLayout(CString &szLayout, CUIntArray &nColumns) CONST
{
	CUIntArray  nWidths;

	return GetLayout(szLayout, nColumns, nWidths);
}
BOOL COOLView::GetLayout(CString &szLayout, CUIntArray &nColumns, CUIntArray &nWidths) CONST
{
	INT  nIndex;
	INT  nCount;
	CStringArray  szColumns;
	CTextViewLock  cLock(this);

	for (nIndex = 0, nCount = (GetColumns(szColumns, nWidths)) ? (INT)szColumns.GetSize() : -1, nColumns.RemoveAll(), szLayout = m_szLayout; nIndex < nCount; nIndex++)
	{
		nColumns.Add(LookupColumnName(szColumns.GetAt(nIndex)));
		continue;
	}
	return((nIndex == nCount) ? TRUE : FALSE);
}

BOOL COOLView::SetTitleFont(CFont *pFont)
{
	LOGFONT  lfFont;

	return((pFont->GetLogFont(&lfFont)) ? SetTitleFont(&lfFont) : FALSE);
}
BOOL COOLView::SetTitleFont(CONST LOGFONT *plfFont)
{
	LOGFONT  lfFont;
	CTextViewLock  cLock(this);

	if (!CTextView::GetTitleFont(&lfFont) || memcmp(plfFont, &lfFont, sizeof(LOGFONT)))
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

BOOL COOLView::GetTitleFont(CFont *pFont) CONST
{
	return CTextView::GetTitleFont(pFont);
}
BOOL COOLView::GetTitleFont(LOGFONT *plfFont) CONST
{
	return CTextView::GetTitleFont(plfFont);
}

BOOL COOLView::SetItemsFont(CFont *pFont)
{
	LOGFONT  lfFont;

	return((pFont->GetLogFont(&lfFont)) ? SetItemsFont(&lfFont) : FALSE);
}
BOOL COOLView::SetItemsFont(CONST LOGFONT *plfFont)
{
	LOGFONT  lfFont;
	CTextViewLock  cLock(this);

	if (!CTextView::GetTextFont(&lfFont) || memcmp(plfFont, &lfFont, sizeof(LOGFONT)))
	{
		if (CTextView::SetTextFont(plfFont))
		{
			AdjustColumns();
			return TRUE;
		}
		return FALSE;
	}
	return TRUE;
}

BOOL COOLView::GetItemsFont(CFont *pFont) CONST
{
	return CTextView::GetTextFont(pFont);
}
BOOL COOLView::GetItemsFont(LOGFONT *plfFont) CONST
{
	return CTextView::GetTextFont(plfFont);
}

BOOL COOLView::EnableInvalidDataMode(BOOL bEnable)
{
	m_bInvalidDataMode = bEnable;
	return TRUE;
}

BOOL COOLView::IsInvalidDataModeEnabled() CONST
{
	return m_bInvalidDataMode;
}

BOOL COOLView::EnableBadDataMode(BOOL bEnable)
{
	m_bBadDataMode = bEnable;
	return TRUE;
}

BOOL COOLView::IsBadDataModeEnabled() CONST
{
	return m_bBadDataMode;
}

BOOL COOLView::EnableToolTipMode(BOOL bEnable)
{
	m_bToolTipMode = bEnable;
	return TRUE;
}

BOOL COOLView::IsToolTipModeEnabled() CONST
{
	return m_bToolTipMode;
}

BOOL COOLView::SetFilters(CONST COOLParameterFilters &pFilters)
{
	CTextViewLock  cLock(this);

	return m_pFilters.Copy(&pFilters);
}

BOOL COOLView::GetFilters(COOLParameterFilters &pFilters) CONST
{
	CTextViewLock  cLock(this);

	return pFilters.Copy(&m_pFilters);
}

BOOL COOLView::SetColors(CONST CUIntArray &nColors)
{
	INT  nIndex;
	INT  nCount;
	CTextViewLock  cLock(this);

	for (nIndex = 0, nCount = (INT)nColors.GetSize(); nIndex < nCount; nIndex++)
	{
		m_nColors.SetAtGrow(nIndex, nColors.GetAt(nIndex));
		continue;
	}
	return(nColors.GetSize() > 0);
}

BOOL COOLView::GetColors(CUIntArray &nColors) CONST
{
	CTextViewLock  cLock(this);

	nColors.Copy(m_nColors);
	return(nColors.GetSize() > 0);
}

BOOL COOLView::Initialize(CTMEnvironment *pTMEnvironment)
{
	CTextViewLock  cLock(this);

	return pTMEnvironment->Initialize(m_pParameters[0], IsBadDataModeEnabled());
}
BOOL COOLView::Initialize(CString &szTag, CTimeTag &tTag)
{
	INT  nMode;
	INT  nParameter;
	INT  nParameters;
	COolParameter  *pOolParameter;
	COolParameters  pOolParameters;
	CTextViewLock  cLock(this);

	for (nParameter = 0, nParameters = (((nMode = GetParent()->GetMode()) == DISPLAY_MODE_REALTIME && InitializeTMData(pOolParameters, IsBadDataModeEnabled())) || (nMode == DISPLAY_MODE_HISTORY && GetParent()->InitializeTMData(pOolParameters, IsBadDataModeEnabled()))) ? (INT)pOolParameters.GetSize() : -1, m_bParameters.RemoveAll(), szTag.Empty(), tTag = 0; nParameter < nParameters; nParameter++)
	{
		if ((pOolParameter = pOolParameters.GetAt(nParameter)) && pOolParameter->IsInitialized() && tTag < pOolParameter->GetOolTime())
		{
			szTag = pOolParameter->GetOolTMUnit();
			tTag = pOolParameter->GetOolTime();
		}
		m_bParameters.InsertAt(nParameter, FALSE, 1);
	}
	if (nParameter == nParameters)
	{
		for (nParameter = 0, nParameters = (m_pParameters[0].GetSize() == pOolParameters.GetSize()) ? (INT)pOolParameters.GetSize() : -1; nParameter < nParameters; nParameter++)
		{
			if (m_pParameters[0].GetAt(nParameter)->GetTag() != pOolParameters.GetAt(nParameter)->GetTag() || m_pParameters[0].GetAt(nParameter)->GetOolTMUnit() != pOolParameters.GetAt(nParameter)->GetOolTMUnit() || m_pParameters[0].GetAt(nParameter)->GetOolTime() != pOolParameters.GetAt(nParameter)->GetOolTime()) break;
			continue;
		}
		if (nParameter != nParameters)
		{
			m_pParameters[0].Copy(&pOolParameters);
			m_pParameters[1].RemoveAll();
			m_pParameters[2].RemoveAll();
			DeleteAllText();
		}
		Update();
		return TRUE;
	}
	return FALSE;
}

BOOL COOLView::Update(CTMEnvironment *pTMEnvironment)
{
	INT  nRow;
	INT  nCount;
	INT  nSample;
	INT  nSamples;
	INT  nIndex[2];
	INT  nColumn;
	INT  nColumns;
	INT  nParameter;
	INT  nParameters;
	BOOL  bParameters;
	BOOL  bUpdates;
	BOOL  bOutSet;
	BYTE  nAlert;
	UINT  nStatus;
	UINT  nOolType;
	WORD  wOolInfo[2];
	double  fLimitRange[2];
	CPoint  ptToolTip;
	CString  szOolUnit;
	CString  szLimitDelta;
	CString  szLimitRange[2];
	CString  szParameterStatus;
	CString  szParameter[2];
	CString  szToolTip[2];
	ULONGLONG  nValue;
	CTimeTag  tOolTime;
	CTimeKey  tOolRange[2];
	CPtrArray  pOolParameters[2];
	CUIntArray  nOolTables[2];
	CStringArray  szColumns;
	CStringTools  cStringTools;
	COolParameter  *pOolParameter[2];
	CTextViewAttribute  cAttribute;
	COOLParameterFilter  *pOolParameterFilter;
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CDatabaseTMNumOolTable  *pDatabaseTMNumOolTable;
	CDatabaseTMNumOolLimit  *pDatabaseTMNumOolLimit;
	CDatabaseTMTxtOolTable  *pDatabaseTMTxtOolTable;
	CDatabaseTMTxtOolLimit  *pDatabaseTMTxtOolLimit;
	CTextViewLock  cLock(this);

	for (nParameter = 0, nParameters = ((bParameters = (pTMEnvironment != (CTMEnvironment *)NULL))) ? (INT)pTMEnvironment->GetOolParameters()->GetSize() : 0, bUpdates = FALSE; nParameter < nParameters; nParameter++)
	{
		if ((pOolParameter[0] = pTMEnvironment->GetOolParameters()->GetAt(nParameter)))
		{
			if ((pOolParameter[1] = m_pParameters[0].GetAt((nIndex[0] = m_pParameters[0].Find(pOolParameter[0]->GetTag())))))
			{
				for (nSample = 0, nSamples = (DeleteText(FindParameterIndex(nIndex[0]), FALSE)) ? pOolParameter[0]->GetValueCount() : -1; nSample < nSamples; nSample++)
				{
					if (pOolParameter[0]->GetRawValue(nSample, nValue, nStatus) && (nStatus & (TMPARAMETER_STATUS_SOFTLIMIT | TMPARAMETER_STATUS_HARDLIMIT | TMPARAMETER_STATUS_DELTALIMIT | TMPARAMETER_STATUS_CONSISTENCYLIMIT))) break;
					continue;
				}
				if (nSample == nSamples)
				{
					if ((nIndex[1] = m_pParameters[1].Find(pOolParameter[0]->GetTag())) >= 0)
					{
						delete m_pParameters[1].GetAt(nIndex[1]);
						m_pParameters[1].RemoveAt(nIndex[1]);
					}
					if ((nIndex[1] = m_pParameters[2].Find(pOolParameter[0]->GetTag())) >= 0)
					{
						delete m_pParameters[2].GetAt(nIndex[1]);
						m_pParameters[2].RemoveAt(nIndex[1]);
					}
					pOolParameters[0].Add(pOolParameter[0]);
					bUpdates = TRUE;
				}
				delete m_pParameters[0].GetAt(nIndex[0]);
				m_pParameters[0].RemoveAt(nIndex[0]);
				m_bParameters.RemoveAt(nIndex[0]);
			}
		}
	}
	for (nParameter = 0, nParameters = (bParameters) ? (INT)pTMEnvironment->GetOolParameters()->GetSize() : (INT)m_pParameters[0].GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pOolParameter[0] = (bParameters) ? pTMEnvironment->GetOolParameters()->GetAt(nParameter) : m_pParameters[0].GetAt(nParameter)))
		{
			if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pOolParameter[0]->GetTag()))))
			{
				for (nSample = pOolParameter[0]->GetValueCount() - 1, nAlert = 0; nSample >= 0; nSample--)
				{
					if (pOolParameter[0]->GetRawValue(nSample, nValue, nStatus))
					{
						if (nStatus & (TMPARAMETER_STATUS_SOFTLIMIT | TMPARAMETER_STATUS_HARDLIMIT | TMPARAMETER_STATUS_DELTALIMIT | TMPARAMETER_STATUS_CONSISTENCYLIMIT)) break;
						continue;
					}
				}
				if (nSample >= 0)
				{
					if (bParameters)
					{
						if ((nIndex[0] = m_pParameters[0].Find(pOolParameter[0]->GetTag())) < 0)
						{
							if ((pOolParameter[1] = new COolParameter))
							{
								pOolParameter[1]->Copy(pOolParameter[0]);
								if ((nIndex[0] = m_pParameters[0].Add(pOolParameter[1])) < 0)
								{
									delete pOolParameter[1];
									continue;
								}
								m_bParameters.InsertAt(nIndex[0], FALSE, 1);
							}
							else continue;
						}
						else
						{
							if ((pOolParameter[1] = m_pParameters[0].GetAt(nIndex[0])))
							{
								pOolParameter[1]->Copy(pOolParameter[0]);
								m_bParameters.SetAt(nIndex[0], FALSE);
							}
							else continue;
						}
					}
					if ((pOolParameter[1] = m_pParameters[0].GetAt((nIndex[0] = (!bParameters) ? nParameter : nIndex[0]))))
					{
						if ((pOolParameterFilter = m_pFilters.GetAt(max(m_pFilters.Find(pOolParameter[0]->GetTag()), m_pFilters.Find(STRING(IDS_OOLSETTINGS_FILTERINGPAGE_PARAMETERSFLAG))))))
						{
							if ((pOolParameterFilter->GetOptions() & OOLPARAMETERFILTER_SHOW_NEVER) || ((pOolParameterFilter->GetOptions() & OOLPARAMETERFILTER_SHOW_INTERVAL) && pOolParameterFilter->GetTimeRange(tOolRange[0], tOolRange[1]) && (pOolParameter[0]->GetOolTime().GetTimeInSeconds() < tOolRange[0].GetTime() || pOolParameter[0]->GetOolTime().GetTimeInSeconds() > tOolRange[1].GetTime()))) continue;
							nAlert = pOolParameterFilter->GetOptions() & OOLPARAMETERFILTER_BEHAVIOR_FLASH;
						}
					}
					if (((nStatus & TMPARAMETER_STATUS_VALID) || IsInvalidDataModeEnabled()) && ((nStatus & TMPARAMETER_STATUS_GOOD) || IsBadDataModeEnabled()))
					{
						for (nColumn = 0, nColumns = (INT)m_nLayoutColumns.GetSize(), m_bParameters.SetAt(nIndex[0], TRUE); nColumn < nColumns; nColumn++)
						{
							if (m_nLayoutColumns.GetAt(nColumn) == OOL_TITLEITEM_ID)
							{
								szParameter[0] = (nColumn > 0) ? (szParameter[0] + GetColumnDelimiter() + pDatabaseTMParameter->GetTag()) : pDatabaseTMParameter->GetTag();
								continue;
							}
							if (m_nLayoutColumns.GetAt(nColumn) == OOL_TITLEITEM_DESCRIPTION)
							{
								szParameter[0] = (nColumn > 0) ? (szParameter[0] + GetColumnDelimiter() + pDatabaseTMParameter->GetDescription()) : pDatabaseTMParameter->GetDescription();
								continue;
							}
							if (m_nLayoutColumns.GetAt(nColumn) == OOL_TITLEITEM_VALUE)
							{
								if (pOolParameter[0]->GetOolInfo(szOolUnit, tOolTime, wOolInfo[0], wOolInfo[1]) && pDatabaseTMParameter->GetOolTableRefs(nOolTables[0], nOolTables[1]) > (INT)wOolInfo[0])
								{
									if ((pDatabaseTMNumOolTable = ((pOolParameter[0]->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pOolParameter[0]->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL)) ? GetDatabase()->GetTMNumOolTables()->GetAt(nOolTables[0].GetAt(wOolInfo[0])) : (CDatabaseTMNumOolTable *)NULL))
									{
										if (pOolParameter[0]->GetValueAsText(GetDatabase(), nSample, (pDatabaseTMNumOolTable->GetAttributes() & TMOOLTABLE_CHECK_RAW) ? ((pOolParameter[0]->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS)) | TMPARAMETER_CALIBRATION_NONE) : pOolParameter[0]->GetAttributes(), (pDatabaseTMParameter->GetDecimalDigits() > 0) ? pDatabaseTMParameter->GetDecimalDigits() : -1, szParameter[1], bOutSet, FALSE))
										{
											szParameter[1] += (bOutSet) ? GetDatabase()->GetTMNumCalTablePointOutsideText() : EMPTYSTRING;
											szParameter[0] = (nColumn > 0) ? (szParameter[0] + GetColumnDelimiter() + szParameter[1]) : szParameter[1];
											continue;
										}
										szParameter[0] = (nColumn > 0) ? (szParameter[0] + GetColumnDelimiter()) : szParameter[0];
										continue;
									}
									if ((pDatabaseTMTxtOolTable = (pOolParameter[0]->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS) ? GetDatabase()->GetTMTxtOolTables()->GetAt(nOolTables[0].GetAt(wOolInfo[0])) : (CDatabaseTMTxtOolTable *)NULL))
									{
										if (pOolParameter[0]->GetValueAsText(GetDatabase(), nSample, (pDatabaseTMTxtOolTable->GetAttributes() & TMOOLTABLE_CHECK_RAW) ? ((pOolParameter[0]->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS)) | TMPARAMETER_CALIBRATION_NONE) : pOolParameter[0]->GetAttributes(), szParameter[1], bOutSet, FALSE))
										{
											szParameter[1] += (bOutSet) ? GetDatabase()->GetTMTxtCalTablePointOutsideText() : EMPTYSTRING;
											szParameter[0] = (nColumn > 0) ? (szParameter[0] + GetColumnDelimiter() + szParameter[1]) : szParameter[1];
											continue;
										}
										szParameter[0] = (nColumn > 0) ? (szParameter[0] + GetColumnDelimiter()) : szParameter[0];
										continue;
									}
								}
								if (pOolParameter[0]->GetValueAsText(GetDatabase(), nSample, (((pOolParameter[0]->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pOolParameter[0]->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL)) && pDatabaseTMParameter->GetDecimalDigits() > 0) ? pDatabaseTMParameter->GetDecimalDigits() : -1, szParameter[1], bOutSet, FALSE))
								{
									szParameter[1] += (bOutSet) ? ((pOolParameter[0]->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) ? GetDatabase()->GetTMNumCalTablePointOutsideText() : ((pOolParameter[0]->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS) ? GetDatabase()->GetTMTxtCalTablePointOutsideText() : EMPTYSTRING)) : EMPTYSTRING;
									szParameter[0] = (nColumn > 0) ? (szParameter[0] + GetColumnDelimiter() + szParameter[1]) : szParameter[1];
									continue;
								}
								szParameter[0] = (nColumn > 0) ? (szParameter[0] + GetColumnDelimiter()) : szParameter[0];
								continue;
							}
							if (m_nLayoutColumns.GetAt(nColumn) == OOL_TITLEITEM_LIMIT)
							{
								if (pOolParameter[0]->GetOolInfo(szOolUnit, tOolTime, wOolInfo[0], wOolInfo[1]) && pDatabaseTMParameter->GetOolTableRefs(nOolTables[0], nOolTables[1]) > (INT)wOolInfo[0])
								{
									if ((pDatabaseTMNumOolTable = ((pOolParameter[0]->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pOolParameter[0]->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL)) ? GetDatabase()->GetTMNumOolTables()->GetAt(nOolTables[0].GetAt(wOolInfo[0])) : (CDatabaseTMNumOolTable *)NULL))
									{
										if ((pDatabaseTMNumOolLimit = pDatabaseTMNumOolTable->GetAt(wOolInfo[1])))
										{
											if (pDatabaseTMNumOolLimit->GetRange(nOolType, fLimitRange[0], fLimitRange[1]))
											{
												if (!(pDatabaseTMNumOolTable->GetAttributes() & TMOOLTABLE_CODING_FLOATINGPOINT) && (pDatabaseTMNumOolTable->GetAttributes() & TMOOLTABLE_CHECK_RAW))
												{
													if (pDatabaseTMNumOolTable->GetAttributes() & TMOOLTABLE_CODING_SIGNEDINTEGER)
													{
														szLimitRange[0] = cStringTools.ConvertLongIntToString((LONGLONG)fLimitRange[0]);
														szLimitRange[1] = cStringTools.ConvertLongIntToString((LONGLONG)fLimitRange[1]);
													}
													else
													{
														szLimitRange[0] = cStringTools.ConvertLongUIntToString((ULONGLONG)fLimitRange[0]);
														szLimitRange[1] = cStringTools.ConvertLongUIntToString((ULONGLONG)fLimitRange[1]);
													}
												}
												else
												{
													szLimitRange[0] = cStringTools.ConvertFloatToString(fLimitRange[0]);
													szLimitRange[1] = cStringTools.ConvertFloatToString(fLimitRange[1]);
												}
												szParameter[1].Format(STRING(IDS_OOL_ALERTRANGE_FORMAT), (LPCTSTR)szLimitRange[0], (LPCTSTR)szLimitRange[1]);
												szParameter[0] = (nColumn > 0) ? (szParameter[0] + GetColumnDelimiter() + szParameter[1]) : szParameter[1];
												continue;
											}
											if (pDatabaseTMNumOolLimit->GetType() == TMOOLLIMIT_TYPE_DELTA)
											{
												if (pDatabaseTMNumOolLimit->GetDelta(fLimitRange[0], TRUE) && pDatabaseTMNumOolLimit->GetDelta(fLimitRange[1], FALSE))
												{
													szLimitDelta.Format(STRING(IDS_OOL_ALERTMINMAXDELTA_FORMAT), (pDatabaseTMNumOolTable->GetAttributes() & TMOOLTABLE_CHECK_RAW) ? ((pDatabaseTMNumOolTable->GetAttributes() & TMOOLTABLE_CODING_UNSIGNEDINTEGER) ? (LPCTSTR)cStringTools.ConvertLongUIntToString((ULONGLONG)fLimitRange[0]) : ((pDatabaseTMNumOolTable->GetAttributes() & TMOOLTABLE_CODING_SIGNEDINTEGER) ? (LPCTSTR)cStringTools.ConvertLongIntToString((LONGLONG)fLimitRange[0]) : (LPCTSTR)cStringTools.ConvertFloatToString(fLimitRange[0]))) : (LPCTSTR)cStringTools.ConvertFloatToString(fLimitRange[0]), (pDatabaseTMNumOolTable->GetAttributes() & TMOOLTABLE_CHECK_RAW) ? ((pDatabaseTMNumOolTable->GetAttributes() & TMOOLTABLE_CODING_UNSIGNEDINTEGER) ? (LPCTSTR)cStringTools.ConvertLongUIntToString((ULONGLONG)fLimitRange[1]) : ((pDatabaseTMNumOolTable->GetAttributes() & TMOOLTABLE_CODING_SIGNEDINTEGER) ? (LPCTSTR)cStringTools.ConvertLongIntToString((LONGLONG)fLimitRange[1]) : (LPCTSTR)cStringTools.ConvertFloatToString(fLimitRange[1]))) : (LPCTSTR)cStringTools.ConvertFloatToString(fLimitRange[1]));
													szParameter[0] = (nColumn > 0) ? (szParameter[0] + GetColumnDelimiter() + szLimitDelta) : szLimitDelta;
													continue;
												}
												if (pDatabaseTMNumOolLimit->GetDelta(fLimitRange[0], TRUE))
												{
													szLimitDelta.Format(STRING(IDS_OOL_ALERTMINDELTA_FORMAT), (pDatabaseTMNumOolTable->GetAttributes() & TMOOLTABLE_CHECK_RAW) ? ((pDatabaseTMNumOolTable->GetAttributes() & TMOOLTABLE_CODING_UNSIGNEDINTEGER) ? (LPCTSTR)cStringTools.ConvertLongUIntToString((ULONGLONG)fLimitRange[0]) : ((pDatabaseTMNumOolTable->GetAttributes() & TMOOLTABLE_CODING_SIGNEDINTEGER) ? (LPCTSTR)cStringTools.ConvertLongIntToString((LONGLONG)fLimitRange[0]) : (LPCTSTR)cStringTools.ConvertFloatToString(fLimitRange[0]))) : (LPCTSTR)cStringTools.ConvertFloatToString(fLimitRange[0]));
													szParameter[0] = (nColumn > 0) ? (szParameter[0] + GetColumnDelimiter() + szLimitDelta) : szLimitDelta;
													continue;
												}
												if (pDatabaseTMNumOolLimit->GetDelta(fLimitRange[1], FALSE))
												{
													szLimitDelta.Format(STRING(IDS_OOL_ALERTMAXDELTA_FORMAT), (pDatabaseTMNumOolTable->GetAttributes() & TMOOLTABLE_CHECK_RAW) ? ((pDatabaseTMNumOolTable->GetAttributes() & TMOOLTABLE_CODING_UNSIGNEDINTEGER) ? (LPCTSTR)cStringTools.ConvertLongUIntToString((ULONGLONG)fLimitRange[1]) : ((pDatabaseTMNumOolTable->GetAttributes() & TMOOLTABLE_CODING_SIGNEDINTEGER) ? (LPCTSTR)cStringTools.ConvertLongIntToString((LONGLONG)fLimitRange[1]) : (LPCTSTR)cStringTools.ConvertFloatToString(fLimitRange[1]))) : (LPCTSTR)cStringTools.ConvertFloatToString(fLimitRange[1]));
													szParameter[0] = (nColumn > 0) ? (szParameter[0] + GetColumnDelimiter() + szLimitDelta) : szLimitDelta;
													continue;
												}
											}
										}
									}
									if ((pDatabaseTMTxtOolTable = (pOolParameter[0]->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS) ? GetDatabase()->GetTMTxtOolTables()->GetAt(nOolTables[0].GetAt(wOolInfo[0])) : (CDatabaseTMTxtOolTable *)NULL))
									{
										for (szLimitRange[0].Format(STRING(IDS_OOL_ALERTTABLE_FORMAT), (LPCTSTR)pDatabaseTMTxtOolTable->GetName()); pDatabaseTMTxtOolTable->GetSize() == 1; )
										{
											if ((pDatabaseTMTxtOolLimit = pDatabaseTMTxtOolTable->GetAt((INT)pDatabaseTMTxtOolTable->GetUpperBound())))
											{
												if (pDatabaseTMTxtOolTable->GetAttributes() & TMOOLTABLE_CHECK_RAW)
												{
													if (pDatabaseTMTxtOolLimit->GetLimit(fLimitRange[0]))
													{
														szLimitRange[0] = (pDatabaseTMTxtOolTable->GetAttributes() & TMOOLTABLE_CODING_FLOATINGPOINT) ? (LPCTSTR)cStringTools.ConvertFloatToString(fLimitRange[0]) : EMPTYSTRING;
														szLimitRange[0] = (pDatabaseTMTxtOolTable->GetAttributes() & TMOOLTABLE_CODING_SIGNEDINTEGER) ? cStringTools.ConvertLongIntToString((LONGLONG)fLimitRange[0]) : szLimitRange[0];
														szLimitRange[0] = (szLimitRange[0].IsEmpty()) ? cStringTools.ConvertLongUIntToString((ULONGLONG)fLimitRange[0]) : szLimitRange[0];
														break;
													}
													if (pDatabaseTMTxtOolLimit->GetRange(fLimitRange[0], fLimitRange[1]))
													{
														if (!(pDatabaseTMTxtOolTable->GetAttributes() & TMOOLTABLE_CODING_FLOATINGPOINT))
														{
															if (pDatabaseTMTxtOolTable->GetAttributes() & TMOOLTABLE_CODING_SIGNEDINTEGER)
															{
																szLimitRange[0] = cStringTools.ConvertLongIntToString((LONGLONG)fLimitRange[0]);
																szLimitRange[1] = cStringTools.ConvertLongIntToString((LONGLONG)fLimitRange[1]);
															}
															else
															{
																szLimitRange[0] = cStringTools.ConvertLongUIntToString((ULONGLONG)fLimitRange[0]);
																szLimitRange[1] = cStringTools.ConvertLongUIntToString((ULONGLONG)fLimitRange[1]);
															}
														}
														else
														{
															szLimitRange[0] = cStringTools.ConvertFloatToString(fLimitRange[0]);
															szLimitRange[1] = cStringTools.ConvertFloatToString(fLimitRange[1]);
														}
														szParameter[1].Format(STRING(IDS_OOL_ALERTRANGE_FORMAT), (LPCTSTR)szLimitRange[0], (LPCTSTR)szLimitRange[1]);
														szLimitRange[0] = szParameter[1];
														break;
													}
												}
												if (pDatabaseTMTxtOolTable->GetAttributes() & TMOOLTABLE_CHECK_CALIBRATED)
												{
													if (pDatabaseTMTxtOolLimit->GetLimit(szLimitRange[0])) break;
													if (pDatabaseTMTxtOolLimit->GetRange(szLimitRange[0], szLimitRange[1]))
													{
														szParameter[1].Format(STRING(IDS_OOL_ALERTRANGE_FORMAT), (LPCTSTR)szLimitRange[0], (LPCTSTR)szLimitRange[1]);
														szLimitRange[0] = szParameter[1];
														break;
													}
												}
											}
											szLimitRange[0].Empty();
											break;
										}
										szParameter[0] = (nColumn > 0) ? (szParameter[0] + GetColumnDelimiter() + szLimitRange[0]) : szLimitRange[0];
										continue;
									}
								}
								szParameter[0] = (nColumn > 0) ? (szParameter[0] + GetColumnDelimiter()) : szParameter[0];
								continue;
							}
							if (m_nLayoutColumns.GetAt(nColumn) == OOL_TITLEITEM_UNIT)
							{
								szParameter[0] = (nColumn > 0) ? (szParameter[0] + GetColumnDelimiter() + pDatabaseTMParameter->GetUnit()) : pDatabaseTMParameter->GetUnit();
								continue;
							}
							if (m_nLayoutColumns.GetAt(nColumn) == OOL_TITLEITEM_OOLTYPE)
							{
								szParameterStatus = (nStatus & TMPARAMETER_STATUS_SOFTLIMIT) ? STRING(IDS_OOL_ALERTTYPE_SOFT) : EMPTYSTRING;
								szParameterStatus = (nStatus & TMPARAMETER_STATUS_HARDLIMIT) ? STRING(IDS_OOL_ALERTTYPE_HARD) : (LPCTSTR)szParameterStatus;
								szParameterStatus = (nStatus & TMPARAMETER_STATUS_DELTALIMIT) ? STRING(IDS_OOL_ALERTTYPE_DELTA) : (LPCTSTR)szParameterStatus;
								szParameterStatus = (nStatus & TMPARAMETER_STATUS_CONSISTENCYLIMIT) ? STRING(IDS_OOL_ALERTTYPE_CONSISTENCY) : (LPCTSTR)szParameterStatus;
								szParameter[0] = (nColumn > 0) ? (szParameter[0] + GetColumnDelimiter() + szParameterStatus) : szParameterStatus;
								continue;
							}
							if (m_nLayoutColumns.GetAt(nColumn) == OOL_TITLEITEM_OOLTIME)
							{
								szParameter[0] = (nColumn > 0) ? (szParameter[0] + GetColumnDelimiter() + pOolParameter[0]->GetOolTime().FormatGmt()) : pOolParameter[0]->GetOolTime().FormatGmt();
								continue;
							}
							if (m_nLayoutColumns.GetAt(nColumn) == OOL_TITLEITEM_OOLUNIT)
							{
								szParameter[0] = (nColumn > 0) ? (szParameter[0] + GetColumnDelimiter() + pOolParameter[0]->GetOolTMUnit()) : pOolParameter[0]->GetOolTMUnit();
								continue;
							}
						}
						if ((nAlert & OOLPARAMETERFILTER_BEHAVIOR_FLASH) == OOLPARAMETERFILTER_BEHAVIOR_FLASH  &&  !bParameters)
						{
							if (m_pParameters[1].Find(pOolParameter[0]->GetTag()) < 0 && m_pParameters[2].Find(pOolParameter[0]->GetTag()) < 0)
							{
								if ((pOolParameter[1] = new COolParameter))
								{
									pOolParameter[1]->Copy(pOolParameter[0]);
									if (m_pParameters[1].Add(pOolParameter[1]) < 0) delete pOolParameter[1];
								}
							}
						}
						if ((nAlert & OOLPARAMETERFILTER_BEHAVIOR_FLASH) != OOLPARAMETERFILTER_BEHAVIOR_FLASH  &&  !bParameters)
						{
							if ((nIndex[1] = m_pParameters[1].Find(pOolParameter[0]->GetTag())) >= 0)
							{
								delete m_pParameters[1].GetAt(nIndex[1]);
								m_pParameters[1].RemoveAt(nIndex[1]);
							}
						}
						if (!GetText((nIndex[0] = DetermineParameterIndex(nIndex[0])), szParameter[1]) || szParameter[0] != szParameter[1])
						{
							cAttribute.SetColumnColor(-1, ((nStatus & TMPARAMETER_STATUS_SOFTLIMIT) != TMPARAMETER_STATUS_SOFTLIMIT) ? (((nStatus & TMPARAMETER_STATUS_HARDLIMIT) != TMPARAMETER_STATUS_HARDLIMIT) ? (((nStatus & TMPARAMETER_STATUS_DELTALIMIT) != TMPARAMETER_STATUS_DELTALIMIT) ? ((nStatus & TMPARAMETER_STATUS_CONSISTENCYLIMIT) ? m_nColors.GetAt(OOL_OOLCOLOR_CONSISTENCYLIMIT) : GetSysColor(COLOR_WINDOWTEXT)) : m_nColors.GetAt(OOL_OOLCOLOR_DELTALIMIT)) : m_nColors.GetAt(OOL_OOLCOLOR_HARDLIMIT)) : m_nColors.GetAt(OOL_OOLCOLOR_SOFTLIMIT));
							cAttribute.SetColumnBlinking(-1, (nAlert & OOLPARAMETERFILTER_BEHAVIOR_FLASH) ? !IsAcknowledged(pOolParameter[0]->GetTag()) : FALSE);
							InsertText(nIndex[0], szParameter[0], &cAttribute, FALSE);
							pOolParameters[1].Add(pOolParameter[0]);
							bUpdates = TRUE;
							continue;
						}
						cAttribute.SetColumnColor(-1, ((nStatus & TMPARAMETER_STATUS_SOFTLIMIT) != TMPARAMETER_STATUS_SOFTLIMIT) ? (((nStatus & TMPARAMETER_STATUS_HARDLIMIT) != TMPARAMETER_STATUS_HARDLIMIT) ? (((nStatus & TMPARAMETER_STATUS_DELTALIMIT) != TMPARAMETER_STATUS_DELTALIMIT) ? ((nStatus & TMPARAMETER_STATUS_CONSISTENCYLIMIT) ? m_nColors.GetAt(OOL_OOLCOLOR_CONSISTENCYLIMIT) : GetSysColor(COLOR_WINDOWTEXT)) : m_nColors.GetAt(OOL_OOLCOLOR_DELTALIMIT)) : m_nColors.GetAt(OOL_OOLCOLOR_HARDLIMIT)) : m_nColors.GetAt(OOL_OOLCOLOR_SOFTLIMIT));
						cAttribute.SetColumnBlinking(-1, (nAlert & OOLPARAMETERFILTER_BEHAVIOR_FLASH) ? !IsAcknowledged(pOolParameter[0]->GetTag()) : FALSE);
						SetText(nIndex[0], szParameter[0], &cAttribute, FALSE);
					}
				}
			}
		}
	}
	for (nCount = DetermineParameterIndex((INT)m_pParameters[0].GetSize()); nCount < GetTextCount(); )
	{
		DeleteText(GetTextCount() - 1, FALSE);
		continue;
	}
	if (m_wndToolTip.IsVisibleAtPoint(ptToolTip))
	{
		for (szToolTip[0] = ConstructToolTipTitle((nRow = PointToRow(ptToolTip))), szToolTip[1] = ConstructToolTipText(nRow, m_wndHeaderCtrl.m_szColumnsText.GetAt(PointToColumn(ptToolTip))); !szToolTip[0].IsEmpty() || !szToolTip[1].IsEmpty(); )
		{
			m_wndToolTip.Update(szToolTip[0], szToolTip[1]);
			break;
		}
	}
	if (!bParameters)
	{
		pOolParameters[0].RemoveAll();
		pOolParameters[1].RemoveAll();
	}
	if (nParameter == nParameters  &&  nParameters > 0)
	{
		Alert(pTMEnvironment, pOolParameters[0], pOolParameters[1]);
		RecalcLayout();
		return bUpdates;
	}
	if (nParameters > 0)
	{
		Alert(pTMEnvironment, pOolParameters[0], pOolParameters[1]);
		RecalcLayout();
	}
	return FALSE;
}

VOID COOLView::Reset(CTMEnvironment *pTMEnvironment)
{
	CTextViewLock  cLock(this);

	m_pParameters[0].RemoveAll();
	m_pParameters[1].RemoveAll();
	m_pParameters[2].RemoveAll();
	m_bParameters.RemoveAll();
	DeleteAllText();
}

BOOL COOLView::Acknowledge(LPCTSTR pszParameter)
{
	INT  nIndex;
	CTextViewLock  cLock(this);

	if ((nIndex = m_pParameters[1].Find(pszParameter)) >= 0)
	{
		if (m_pParameters[2].Add(m_pParameters[1].GetAt(nIndex)) >= 0)
		{
			StopTextBlinking(DetermineParameterIndex(m_pParameters[0].Find(pszParameter)));
			m_pParameters[1].RemoveAt(nIndex);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL COOLView::IsAcknowledged(LPCTSTR pszParameter) CONST
{
	CTextViewLock  cLock(this);

	return((m_pParameters[2].Find(pszParameter) >= 0) ? TRUE : FALSE);
}

BOOL COOLView::IsAlerted() CONST
{
	CTextViewLock  cLock(this);

	return((m_pParameters[1].GetSize() > 0 || m_cAuditions.GetSize() > 0) ? TRUE : FALSE);
}

BOOL COOLView::SetParameterAlerts(CONST COolParameters &pOolParameters, CEventList &pOolAuditions)
{
	INT  nParameter;
	INT  nParameters;
	INT  nAudition[2];
	INT  nAuditions[2];
	CEventObject  *pEvent[2];
	COolParameter  *pOolParameter;
	CTextViewLock  cLock(this);

	for (nParameter = 0, nParameters = (INT)pOolParameters.GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pOolParameter = pOolParameters.GetAt(nParameter)))
		{
			Acknowledge(pOolParameter->GetTag());
			continue;
		}
	}
	for (nAudition[0] = 0, nAuditions[0] = (INT)pOolAuditions.GetSize(); nAudition[0] < nAuditions[0]; nAudition[0]++)
	{
		for (nAudition[1] = 0, nAuditions[1] = ((pEvent[0] = pOolAuditions.GetAt(nAudition[0]))) ? (INT)m_cAuditions.GetSize() : 0; nAudition[1] < nAuditions[1]; nAudition[1]++)
		{
			if ((pEvent[1] = m_cAuditions.GetAt(nAudition[1])) && pEvent[0]->Compare(pEvent[1]))
			{
				m_cAuditions.Remove(nAudition[1]);
				delete pEvent[1];
				break;
			}
		}
	}
	return TRUE;
}

BOOL COOLView::GetParameterAlerts(COolParameters &pOolParameters, CEventList &pOolAuditions) CONST
{
	INT  nIndex;
	INT  nAudition;
	INT  nAuditions;
	CEventObject  *pEvent[2];
	CTextViewLock  cLock(this);

	for (nAudition = 0, nAuditions = (INT)m_cAuditions.GetSize(), pOolParameters.Copy(&m_pParameters[1]), pOolAuditions.RemoveAll(), pOolAuditions.EnableSound(FALSE); nAudition < nAuditions; nAudition++)
	{
		if ((pEvent[1] = ((pEvent[0] = m_cAuditions.GetAt(nAudition))) ? new CEventObject : (CEventObject *)NULL))
		{
			for (pEvent[1]->Copy(pEvent[0]); (nIndex = pOolAuditions.Add(pEvent[1])) < 0; )
			{
				delete pEvent[1];
				break;
			}
			if (nIndex >= 0) continue;
		}
		break;
	}
	return((m_pParameters[1].GetSize() == pOolParameters.GetSize() && m_cAuditions.GetSize() == pOolAuditions.GetSize()) ? TRUE : FALSE);
}

BOOL COOLView::GetParameterInfo(LPCTSTR pszTag, COolParameter *pOolParameter) CONST
{
	INT  nIndex;
	CTextViewLock  cLock(this);

	return(((nIndex = m_pParameters[0].Find(pszTag)) >= 0 && pOolParameter->Copy(m_pParameters[0].GetAt(nIndex))) ? TRUE : FALSE);
}
BOOL COOLView::GetParameterInfo(COolParameter *pOolParameter) CONST
{
	INT  nIndex;
	CTextViewLock  cLock(this);

	return(((nIndex = GetCurText()) >= 0 && pOolParameter->Copy(m_pParameters[0].GetAt(DetermineParameterIndex(nIndex, TRUE)))) ? TRUE : FALSE);
}

INT COOLView::GetParameters(COolParameters &pOolParameters) CONST
{
	CTextViewLock  cLock(this);

	return((pOolParameters.Copy(&m_pParameters[0])) ? (INT)pOolParameters.GetSize() : 0);
}

INT COOLView::GetParametersCount() CONST
{
	return GetTextCount();
}

BOOL COOLView::HasParameters() CONST
{
	return((GetTextCount() > 0) ? TRUE : FALSE);
}

BOOL COOLView::SearchParameterByID(LPCTSTR pszID, BOOL bDown, BOOL bAll)
{
	INT  nIndex;
	CTextViewLock  cLock(this);

	if ((nIndex = ((nIndex = m_pParameters[0].Find(pszID)) >= 0 && m_bParameters.GetAt(nIndex)) ? DetermineParameterIndex(nIndex) : -1) >= 0)
	{
		if ((!bAll && ((bDown  &&  nIndex >= GetCurText()) || (!bDown && (nIndex <= GetCurText() || GetCurText() < 0)))) || bAll)
		{
			SetCurText(nIndex);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL COOLView::SearchParameterByDescription(LPCTSTR pszDescription, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord)
{
	INT  nLine;
	INT  nLines;
	INT  nColumn;
	INT  nColumns;
	CString  szText[2];
	CStringArray  szColumns;
	CTextViewLock  cLock(this);

	for (nColumn = 0, nColumns = (GetColumns(szColumns)) ? (INT)szColumns.GetSize() : 0; nColumn < nColumns; nColumn++)
	{
		if (szColumns.GetAt(nColumn) == STRING(IDS_OOL_TITLEITEM_DESCRIPTION)) break;
		continue;
	}
	for (nLine = (!bAll && GetCurText() >= 0) ? ((bDown) ? (GetCurText() + 1) : (GetCurText() - 1)) : ((!bDown) ? (GetTextCount() - 1) : 0), nLines = GetTextCount(), szText[1] = pszDescription; ((bDown && nLine < nLines) || (!bDown && nLine >= 0)); nLine = (bDown) ? (nLine + 1) : (nLine - 1))
	{
		if (GetText(nLine, nColumn, szText[0]))
		{
			if (!bCase  &&  !bWord)
			{
				szText[0].MakeUpper();
				szText[1].MakeUpper();
				if (szText[0].Find(szText[1]) >= 0)
				{
					SetCurText(nLine);
					break;
				}
			}
			if (bCase  &&  !bWord)
			{
				if (szText[0].Find(szText[1]) >= 0)
				{
					SetCurText(nLine);
					break;
				}
			}
			if (!bCase  &&  bWord)
			{
				szText[0].MakeUpper();
				szText[1].MakeUpper();
				if (!szText[0].Find(szText[1] + SPACE) || szText[0].Find(SPACE + szText[1] + SPACE) > 0)
				{
					SetCurText(nLine);
					break;
				}
			}
			if (bCase  &&  bWord)
			{
				if (!szText[0].Find(szText[1] + SPACE) || szText[0].Find(SPACE + szText[1] + SPACE) > 0)
				{
					SetCurText(nLine);
					break;
				}
			}
		}
	}
	return((nLine < nLines  &&  nLine >= 0) ? TRUE : FALSE);
}

BOOL COOLView::SearchParameterByValue(LPCTSTR pszValue, BOOL bDown, BOOL bAll, BOOL bCase)
{
	INT  nLine;
	INT  nLines;
	INT  nColumn;
	INT  nColumns;
	CString  szText[2];
	CStringArray  szColumns;
	CTextViewLock  cLock(this);

	for (nColumn = 0, nColumns = (GetColumns(szColumns)) ? (INT)szColumns.GetSize() : 0; nColumn < nColumns; nColumn++)
	{
		if (szColumns.GetAt(nColumn) == STRING(IDS_OOL_TITLEITEM_VALUE)) break;
		continue;
	}
	for (nLine = (!bAll && GetCurText() >= 0) ? ((bDown) ? (GetCurText() + 1) : (GetCurText() - 1)) : ((!bDown) ? (GetTextCount() - 1) : 0), nLines = GetTextCount(), szText[1] = pszValue; ((bDown && nLine < nLines) || (!bDown && nLine >= 0)); nLine = (bDown) ? (nLine + 1) : (nLine - 1))
	{
		if (GetText(nLine, nColumn, szText[0]))
		{
			if (bCase  &&  szText[0] == szText[1])
			{
				SetCurText(nLine);
				break;
			}
			if (!bCase  &&  !szText[0].CompareNoCase(szText[1]))
			{
				SetCurText(nLine);
				break;
			}
		}
	}
	return((nLine < nLines  &&  nLine >= 0) ? TRUE : FALSE);
}

BOOL COOLView::SearchParameterByLimit(LPCTSTR pszLimit, BOOL bDown, BOOL bAll)
{
	INT  nParameter;
	INT  nParameters;
	WORD  wOolTable;
	WORD  wOolLimit;
	CString  szOolUnit;
	CTimeTag  tOolUnit;
	CUIntArray  nOolTables[2];
	COolParameter  *pOolParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CDatabaseTMNumOolTable  *pDatabaseTMNumOolTable;
	CDatabaseTMTxtOolTable  *pDatabaseTMTxtOolTable;
	CTextViewLock  cLock(this);

	for (nParameter = (!bAll && GetCurText() >= 0) ? ((!bDown) ? (DetermineParameterIndex(GetCurText(), TRUE) - 1) : (DetermineParameterIndex(GetCurText(), TRUE) + 1)) : ((!bDown) ? (INT)(m_pParameters[0].GetSize() - 1) : 0), nParameters = (INT)m_pParameters[0].GetSize(); ((bDown && nParameter < nParameters) || (!bDown && nParameter >= 0)); nParameter = (bDown) ? (nParameter + 1) : (nParameter - 1))
	{
		if ((pOolParameter = (nParameter < m_bParameters.GetSize() && m_bParameters.GetAt(nParameter)) ? m_pParameters[0].GetAt(nParameter) : (COolParameter *)NULL) && pOolParameter->GetOolInfo(szOolUnit, tOolUnit, wOolTable, wOolLimit))
		{
			if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pOolParameter->GetTag()))) && pDatabaseTMParameter->GetOolTableRefs(nOolTables[0], nOolTables[1]) >(INT) wOolTable)
			{
				if ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL))
				{
					if ((pDatabaseTMNumOolTable = GetDatabase()->GetTMNumOolTables()->GetAt(nOolTables[0].GetAt(wOolTable))))
					{
						if (pDatabaseTMNumOolTable->GetName() == pszLimit) break;
						continue;
					}
				}
				if (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS)
				{
					if ((pDatabaseTMTxtOolTable = GetDatabase()->GetTMTxtOolTables()->GetAt(nOolTables[0].GetAt(wOolTable))))
					{
						if (pDatabaseTMTxtOolTable->GetName() == pszLimit) break;
						continue;
					}
				}
			}
		}
	}
	if (nParameter < nParameters  &&  nParameter >= 0)
	{
		SetCurText(DetermineParameterIndex(nParameter));
		return TRUE;
	}
	return FALSE;
}

BOOL COOLView::SearchParameterByUnit(LPCTSTR pszUnit, BOOL bDown, BOOL bAll, BOOL bCase)
{
	INT  nLine;
	INT  nLines;
	INT  nColumn;
	INT  nColumns;
	CString  szText[2];
	CStringArray  szColumns;
	CTextViewLock  cLock(this);

	for (nColumn = 0, nColumns = (GetColumns(szColumns)) ? (INT)szColumns.GetSize() : 0; nColumn < nColumns; nColumn++)
	{
		if (szColumns.GetAt(nColumn) == STRING(IDS_OOL_TITLEITEM_UNIT)) break;
		continue;
	}
	for (nLine = (!bAll && GetCurText() >= 0) ? ((bDown) ? (GetCurText() + 1) : (GetCurText() - 1)) : ((!bDown) ? (GetTextCount() - 1) : 0), nLines = GetTextCount(), szText[1] = pszUnit; ((bDown && nLine < nLines) || (!bDown && nLine >= 0)); nLine = (bDown) ? (nLine + 1) : (nLine - 1))
	{
		if (GetText(nLine, nColumn, szText[0]))
		{
			if (bCase  &&  szText[0] == szText[1])
			{
				SetCurText(nLine);
				break;
			}
			if (!bCase  &&  !szText[0].CompareNoCase(szText[1]))
			{
				SetCurText(nLine);
				break;
			}
		}
	}
	return((nLine < nLines  &&  nLine >= 0) ? TRUE : FALSE);
}

BOOL COOLView::SearchParameterByOolType(LPCTSTR pszOolType, BOOL bDown, BOOL bAll)
{
	INT  nLine;
	INT  nLines;
	INT  nColumn;
	INT  nColumns;
	CString  szText[2];
	CStringArray  szColumns;
	CTextViewLock  cLock(this);

	for (nColumn = 0, nColumns = (GetColumns(szColumns)) ? (INT)szColumns.GetSize() : 0; nColumn < nColumns; nColumn++)
	{
		if (szColumns.GetAt(nColumn) == STRING(IDS_OOL_TITLEITEM_OOLTYPE)) break;
		continue;
	}
	for (nLine = (!bAll && GetCurText() >= 0) ? ((bDown) ? (GetCurText() + 1) : (GetCurText() - 1)) : ((!bDown) ? (GetTextCount() - 1) : 0), nLines = GetTextCount(), szText[1] = pszOolType; ((bDown && nLine < nLines) || (!bDown && nLine >= 0)); nLine = (bDown) ? (nLine + 1) : (nLine - 1))
	{
		if (GetText(nLine, nColumn, szText[0]))
		{
			szText[0].MakeUpper();
			szText[1].MakeUpper();
			if (!szText[1].Find(szText[0]))
			{
				SetCurText(nLine);
				break;
			}
		}
	}
	return((nLine < nLines  &&  nLine >= 0) ? TRUE : FALSE);
}

BOOL COOLView::SearchParameterByOolUnit(LPCTSTR pszOolUnit, BOOL bDown, BOOL bAll)
{
	INT  nLine;
	INT  nLines;
	INT  nColumn;
	INT  nColumns;
	CString  szText[2];
	CStringArray  szColumns;
	CTextViewLock  cLock(this);

	for (nColumn = 0, nColumns = (GetColumns(szColumns)) ? (INT)szColumns.GetSize() : 0; nColumn < nColumns; nColumn++)
	{
		if (szColumns.GetAt(nColumn) == STRING(IDS_OOL_TITLEITEM_OOLUNIT)) break;
		continue;
	}
	for (nLine = (!bAll && GetCurText() >= 0) ? ((bDown) ? (GetCurText() + 1) : (GetCurText() - 1)) : ((!bDown) ? (GetTextCount() - 1) : 0), nLines = GetTextCount(), szText[1] = pszOolUnit; ((bDown && nLine < nLines) || (!bDown && nLine >= 0)); nLine = (bDown) ? (nLine + 1) : (nLine - 1))
	{
		if (GetText(nLine, nColumn, szText[0]))
		{
			if (!szText[0].Compare(szText[1]))
			{
				SetCurText(nLine);
				break;
			}
		}
	}
	return((nLine < nLines  &&  nLine >= 0) ? TRUE : FALSE);
}

BOOL COOLView::SearchParameterByOolTime(CONST CTimeKey &tOolTime, BOOL bDown, BOOL bAll, BOOL bMatch)
{
	INT  nParameter;
	INT  nParameters;
	COolParameter  *pOolParameter;
	CTextViewLock  cLock(this);

	for (nParameter = (!bAll && GetCurText() >= 0) ? ((!bDown) ? (DetermineParameterIndex(GetCurText(), TRUE) - 1) : (DetermineParameterIndex(GetCurText(), TRUE) + 1)) : ((!bDown) ? (INT)(m_pParameters[0].GetSize() - 1) : 0), nParameters = (INT)m_pParameters[0].GetSize(); ((bDown && nParameter < nParameters) || (!bDown && nParameter >= 0)); nParameter = (bDown) ? (nParameter + 1) : (nParameter - 1))
	{
		if ((pOolParameter = (nParameter < m_bParameters.GetSize() && m_bParameters.GetAt(nParameter)) ? (COolParameter *)m_pParameters[0].GetAt(nParameter) : (COolParameter *)NULL))
		{
			if ((bMatch  &&  tOolTime.GetTime() == pOolParameter->GetOolTime().GetTimeInSeconds()) || (!bMatch && ((bDown  &&  tOolTime.GetTime() <= pOolParameter->GetOolTime().GetTimeInSeconds()) || (!bDown  &&  tOolTime.GetTime() >= pOolParameter->GetOolTime().GetTimeInSeconds())))) break;
			continue;
		}
	}
	if (nParameter < nParameters  &&  nParameter >= 0)
	{
		SetCurText(DetermineParameterIndex(nParameter));
		return TRUE;
	}
	return FALSE;
}

BOOL COOLView::GetPrintProperties(CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, COolParameters &pOolParameters, LOGFONT *pTitleFont, LOGFONT *pItemsFont) CONST
{
	INT  nParameter;
	INT  nParameters;
	COolParameter  *pOolParameter;
	CTextViewLock  cLock(this);

	if (GetColumns(szColumns) && GetContent(szContents, pAttributes) && GetTitleFont(pTitleFont) && GetTextFont(pItemsFont))
	{
		for (nParameter = 0, nParameters = (m_pParameters[0].GetSize() == m_bParameters.GetSize()) ? (INT)m_pParameters[0].GetSize() : -1, pOolParameters.RemoveAll(); nParameter < nParameters; nParameter++)
		{
			if ((pOolParameter = (m_bParameters.GetAt(nParameter)) ? (COolParameter *) new COolParameter : (COolParameter *)NULL))
			{
				if (pOolParameter->Copy(m_pParameters[0].GetAt(nParameter)) && pOolParameters.Add(pOolParameter) >= 0) continue;
				delete pOolParameter;
			}
			if (m_bParameters.GetAt(nParameter))
			{
				pOolParameters.RemoveAll();
				break;
			}
		}
		return((nParameter == nParameters) ? TRUE : FALSE);
	}
	return FALSE;
}

COOLWnd *COOLView::GetParent() CONST
{
	return((COOLWnd *)CTextView::GetParent());
}

VOID COOLView::Alert(CONST CTMEnvironment *pTMEnvironment, CONST CPtrArray &pParameters, CONST CPtrArray &pOolParameters)
{
	INT  nIndex;
	INT  nMessage;
	INT  nMessages;
	INT  nParameter;
	INT  nParameters;
	UINT  nStatus;
	WORD  wVoiceAge;
	WORD  wVoiceGender;
	BOOL  bBringToTop;
	BOOL  bAutoScroll;
	DWORD  dwAudio[3];
	CString  szLabels;
	CString  szMessage;
	CString  szAdapter;
	CString  szSpeaker;
	CString  szVoiceText;
	CString  szParameter;
	ULONGLONG  nValue;
	CEventObject  *pEvent;
	CStringArray  szMessages[4];
	CStringArray  szAuditions[7];
	CStringArray  szParameters[12];
	CStringArray  szNotifications[5];
	COolParameter  *pOolParameter[2];
	COOLParameterFilter  *pOolParameterFilter;
	CAuditionProfileInfo  *pAuditionInfo;
	CAuditionProfiles  cAuditionProfiles;

	for (nParameter = 0, nParameters = (INT)pParameters.GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pOolParameter[0] = (COolParameter *)pParameters.GetAt(nParameter)) != (COolParameter *)NULL)
		{
			if ((pOolParameterFilter = m_pFilters.GetAt(max(m_pFilters.Find(pOolParameter[0]->GetTag()), m_pFilters.Find(STRING(IDS_OOLSETTINGS_FILTERINGPAGE_PARAMETERSFLAG))))))
			{
				if (pOolParameterFilter->GetOptions() & OOLPARAMETERFILTER_BEHAVIOR_INLIMIT)
				{
					if (pOolParameterFilter->GetOptions() & OOLPARAMETERFILTER_ALERT_AUDITION)
					{
						szParameters[0].Add(pOolParameter[0]->GetTag());
						szParameters[1].Add(pOolParameter[0]->GetTag());
						szAuditions[1].Add(pOolParameterFilter->GetAudition());
					}
					if (pOolParameterFilter->GetOptions() & OOLPARAMETERFILTER_ALERT_NOTIFICATION)
					{
						for (szParameters[7].Add(pOolParameter[0]->GetTag()), szNotifications[0].Add(pOolParameterFilter->GetNotification()); (pOolParameterFilter->GetOptions() & OOLPARAMETERFILTER_ALERT_AUDITION) != OOLPARAMETERFILTER_ALERT_AUDITION; )
						{
							szParameters[0].Add(pOolParameter[0]->GetTag());
							break;
						}
					}
					if (!(pOolParameterFilter->GetOptions() & OOLPARAMETERFILTER_ALERT_AUDITION) && !(pOolParameterFilter->GetOptions() & OOLPARAMETERFILTER_ALERT_NOTIFICATION))
					{
						szParameters[0].Add(pOolParameter[0]->GetTag());
						continue;
					}
				}
			}
		}
	}
	if ((nParameters = (INT)szParameters[0].GetSize()) == 1)
	{
		szMessage.Format(STRING(IDS_OOL_EVENTALERT_NOOOL), (LPCTSTR)szParameters[0].GetAt(nParameters - 1), (LPCTSTR)pTMEnvironment->GetTMUnit()->GetTimeTag().FormatGmt());
		ReportEvent(EVENT_CATEGORY_SPACECRAFT | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
	}
	if (nParameters > 1)
	{
		for (nParameter = 0, szLabels.Empty(); nParameter < nParameters - 1; nParameter++)
		{
			szLabels += (nParameter > 0) ? (STRING(IDS_OOL_EVENTALERT_SEPARATOR) + szParameters[0].GetAt(nParameter)) : szParameters[0].GetAt(nParameter);
			continue;
		}
		szMessage.Format(STRING(IDS_OOL_EVENTALERT_NOOOLS), (LPCTSTR)szLabels, (LPCTSTR)szParameters[0].GetAt(nParameter), (LPCTSTR)pTMEnvironment->GetTMUnit()->GetTimeTag().FormatGmt());
		ReportEvent(EVENT_CATEGORY_SPACECRAFT | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
	}
	for (nMessage = 0, nParameters = (INT)szParameters[1].GetSize(); nMessage < nParameters; nMessage++)
	{
		for (nParameter = nMessage, nMessages = 0, szLabels.Empty(); nParameter < nParameters; nParameter++)
		{
			if (szAuditions[1].GetAt(nMessage) == szAuditions[1].GetAt(nParameter))
			{
				szLabels += (nMessages > 0) ? (STRING(IDS_OOL_ALERTMESSAGE_SEPARATOR) + szParameters[1].GetAt(nParameter)) : szParameters[1].GetAt(nParameter);
				if (nParameter > nMessage)
				{
					szParameters[1].RemoveAt(nParameter);
					szAuditions[1].RemoveAt(nParameter);
					nParameters--;
					nParameter--;
				}
				nMessages++;
			}
		}
		szMessage.Format((nMessages == 1) ? STRING(IDS_OOL_ALERTMESSAGE_NOOOL) : STRING(IDS_OOL_ALERTMESSAGE_NOOOLS), (LPCTSTR)szLabels, (LPCTSTR)pTMEnvironment->GetTMUnit()->GetTimeTag().FormatGmt());
		szMessages[1].Add(szAuditions[1].GetAt(nMessage));
		szParameters[1].RemoveAt(nMessage);
		szAuditions[1].RemoveAt(nMessage);
		szMessages[0].Add(szMessage);
		nParameters--;
		nMessage--;
	}
	for (nMessage = 0, nParameters = (INT)szParameters[7].GetSize(); nMessage < nParameters; nMessage++)
	{
		for (nParameter = nMessage, nMessages = 0, szLabels.Empty(); nParameter < nParameters; nParameter++)
		{
			if (szNotifications[0].GetAt(nMessage) == szNotifications[0].GetAt(nParameter))
			{
				szLabels += (nMessages > 0) ? (STRING(IDS_OOL_ALERTMESSAGE_SEPARATOR) + szParameters[7].GetAt(nParameter)) : szParameters[7].GetAt(nParameter);
				if (nParameter > nMessage)
				{
					szNotifications[0].RemoveAt(nParameter);
					szParameters[7].RemoveAt(nParameter);
					nParameters--;
					nParameter--;
				}
				nMessages++;
			}
		}
		szMessage.Format((nMessages == 1) ? STRING(IDS_OOL_ALERTMESSAGE_NOOOL) : STRING(IDS_OOL_ALERTMESSAGE_NOOOLS), (LPCTSTR)szLabels, (LPCTSTR)pTMEnvironment->GetTMUnit()->GetTimeTag().FormatGmt());
		szMessages[3].Add(szNotifications[0].GetAt(nMessage));
		szNotifications[0].RemoveAt(nMessage);
		szParameters[7].RemoveAt(nMessage);
		szMessages[2].Add(szMessage);
		nParameters--;
		nMessage--;
	}
	for (nParameter = 0, nParameters = (INT)pOolParameters.GetSize(), bBringToTop = FALSE, bAutoScroll = FALSE; nParameter < nParameters; nParameter++)
	{
		if ((pOolParameter[0] = (COolParameter *)pOolParameters.GetAt(nParameter)) != (COolParameter *)NULL)
		{
			if ((pOolParameterFilter = m_pFilters.GetAt(max(m_pFilters.Find(pOolParameter[0]->GetTag()), m_pFilters.Find(STRING(IDS_OOLSETTINGS_FILTERINGPAGE_PARAMETERSFLAG))))))
			{
				if (pTMEnvironment->GetTMUnit()->GetTag() == pOolParameter[0]->GetOolTMUnit() && pTMEnvironment->GetTMUnit()->GetTimeTag() == pOolParameter[0]->GetOolTime())
				{
					if ((pOolParameterFilter->GetOptions() & OOLPARAMETERFILTER_BEHAVIOR_AUTOACKNOWLEDGE) != OOLPARAMETERFILTER_BEHAVIOR_AUTOACKNOWLEDGE)
					{
						if (pOolParameterFilter->GetOptions() & OOLPARAMETERFILTER_BEHAVIOR_EVENT)
						{
							szParameter = pOolParameter[0]->GetTag();
							szParameters[2].Add(szParameter);
						}
						if (pOolParameterFilter->GetOptions() & OOLPARAMETERFILTER_ALERT_AUDITION)
						{
							if (pOolParameter[0]->GetRawValue(pOolParameter[0]->GetValueCount() - 1, nValue, nStatus))
							{
								if (nStatus & TMPARAMETER_STATUS_HARDLIMIT)
								{
									szParameters[3].Add(pOolParameter[0]->GetTag());
									szAuditions[3].Add(pOolParameterFilter->GetAudition());
								}
								if (nStatus & TMPARAMETER_STATUS_SOFTLIMIT)
								{
									szParameters[4].Add(pOolParameter[0]->GetTag());
									szAuditions[4].Add(pOolParameterFilter->GetAudition());
								}
								if (nStatus & TMPARAMETER_STATUS_DELTALIMIT)
								{
									szParameters[5].Add(pOolParameter[0]->GetTag());
									szAuditions[5].Add(pOolParameterFilter->GetAudition());
								}
								if (nStatus & TMPARAMETER_STATUS_CONSISTENCYLIMIT)
								{
									szParameters[6].Add(pOolParameter[0]->GetTag());
									szAuditions[6].Add(pOolParameterFilter->GetAudition());
								}
							}
						}
						if (pOolParameterFilter->GetOptions() & OOLPARAMETERFILTER_ALERT_NOTIFICATION)
						{
							if (pOolParameter[0]->GetRawValue(pOolParameter[0]->GetValueCount() - 1, nValue, nStatus))
							{
								if (nStatus & TMPARAMETER_STATUS_HARDLIMIT)
								{
									szParameters[8].Add(pOolParameter[0]->GetTag());
									szNotifications[1].Add(pOolParameterFilter->GetNotification());
								}
								if (nStatus & TMPARAMETER_STATUS_SOFTLIMIT)
								{
									szParameters[9].Add(pOolParameter[0]->GetTag());
									szNotifications[2].Add(pOolParameterFilter->GetNotification());
								}
								if (nStatus & TMPARAMETER_STATUS_DELTALIMIT)
								{
									szParameters[10].Add(pOolParameter[0]->GetTag());
									szNotifications[3].Add(pOolParameterFilter->GetNotification());
								}
								if (nStatus & TMPARAMETER_STATUS_CONSISTENCYLIMIT)
								{
									szParameters[11].Add(pOolParameter[0]->GetTag());
									szNotifications[4].Add(pOolParameterFilter->GetNotification());
								}
							}
						}
						bBringToTop = (pOolParameterFilter->GetOptions() & OOLPARAMETERFILTER_BEHAVIOR_BRINGTOTOP) ? TRUE : bBringToTop;
					}
					bAutoScroll = (pOolParameterFilter->GetOptions() & OOLPARAMETERFILTER_BEHAVIOR_AUTOSCROLL) ? TRUE : bAutoScroll;
				}
				if ((pOolParameterFilter->GetOptions() & OOLPARAMETERFILTER_BEHAVIOR_AUTOACKNOWLEDGE) != OOLPARAMETERFILTER_BEHAVIOR_AUTOACKNOWLEDGE)
				{
					if (pOolParameterFilter->GetOptions() & OOLPARAMETERFILTER_BEHAVIOR_FLASH)
					{
						if ((nIndex = m_pParameters[2].Find(pOolParameter[0]->GetTag())) >= 0)
						{
							if (m_pParameters[1].Add(m_pParameters[2].GetAt(nIndex)) >= 0)
							{
								StartTextBlinking(DetermineParameterIndex(m_pParameters[0].Find(pOolParameter[0]->GetTag())));
								m_pParameters[2].RemoveAt(nIndex);
								continue;
							}
						}
						if ((pOolParameter[1] = new COolParameter))
						{
							pOolParameter[1]->Copy(pOolParameter[0]);
							if (m_pParameters[1].Add(pOolParameter[1]) >= 0)
							{
								StartTextBlinking(DetermineParameterIndex(m_pParameters[0].Find(pOolParameter[0]->GetTag())));
								continue;
							}
							delete pOolParameter[1];
						}
					}
				}
			}
			else
			{
				bAutoScroll = (!m_pFilters.GetSize()) ? TRUE : bAutoScroll;
				continue;
			}
		}
	}
	if ((nParameters = (INT)szParameters[2].GetSize()) == 1)
	{
		szMessage.Format(STRING(IDS_OOL_EVENTALERT_ISOOL), (LPCTSTR)szParameters[2].GetAt(nParameters - 1), (LPCTSTR)pTMEnvironment->GetTMUnit()->GetTimeTag().FormatGmt());
		ReportEvent(EVENT_CATEGORY_SPACECRAFT | EVENT_TYPE_WARNING, szMessage, FALSE);
	}
	if (nParameters > 1)
	{
		for (nParameter = 0, szLabels.Empty(); nParameter < nParameters - 1; nParameter++)
		{
			szLabels += (nParameter > 0) ? (STRING(IDS_OOL_EVENTALERT_SEPARATOR) + szParameters[2].GetAt(nParameter)) : szParameters[2].GetAt(nParameter);
			continue;
		}
		szMessage.Format(STRING(IDS_OOL_EVENTALERT_ISOOLS), (LPCTSTR)szLabels, (LPCTSTR)szParameters[2].GetAt(nParameter), (LPCTSTR)pTMEnvironment->GetTMUnit()->GetTimeTag().FormatGmt());
		ReportEvent(EVENT_CATEGORY_SPACECRAFT | EVENT_TYPE_WARNING, szMessage, FALSE);
	}
	for (nMessage = 0, nParameters = (INT)szParameters[3].GetSize(); nMessage < nParameters; nMessage++)
	{
		for (nParameter = nMessage, nMessages = 0, szLabels.Empty(); nParameter < nParameters; nParameter++)
		{
			if (szAuditions[3].GetAt(nMessage) == szAuditions[3].GetAt(nParameter))
			{
				szLabels += (nMessages > 0) ? (STRING(IDS_OOL_ALERTMESSAGE_SEPARATOR) + szParameters[3].GetAt(nParameter)) : szParameters[3].GetAt(nParameter);
				if (nParameter > nMessage)
				{
					szParameters[3].RemoveAt(nParameter);
					szAuditions[3].RemoveAt(nParameter);
					nParameters--;
					nParameter--;
				}
				nMessages++;
			}
		}
		szMessage.Format((nMessages == 1) ? STRING(IDS_OOL_ALERTMESSAGE_HARDOOL) : STRING(IDS_OOL_ALERTMESSAGE_HARDOOLS), (LPCTSTR)szLabels, (LPCTSTR)pTMEnvironment->GetTMUnit()->GetTimeTag().FormatGmt());
		szMessages[1].Add(szAuditions[3].GetAt(nMessage));
		szParameters[3].RemoveAt(nMessage);
		szAuditions[3].RemoveAt(nMessage);
		szMessages[0].Add(szMessage);
		nParameters--;
		nMessage--;
	}
	for (nMessage = 0, nParameters = (INT)szParameters[4].GetSize(); nMessage < nParameters; nMessage++)
	{
		for (nParameter = nMessage, nMessages = 0, szLabels.Empty(); nParameter < nParameters; nParameter++)
		{
			if (szAuditions[4].GetAt(nMessage) == szAuditions[4].GetAt(nParameter))
			{
				szLabels += (nMessages > 0) ? (STRING(IDS_OOL_ALERTMESSAGE_SEPARATOR) + szParameters[4].GetAt(nParameter)) : szParameters[4].GetAt(nParameter);
				if (nParameter > nMessage)
				{
					szParameters[4].RemoveAt(nParameter);
					szAuditions[4].RemoveAt(nParameter);
					nParameters--;
					nParameter--;
				}
				nMessages++;
			}
		}
		szMessage.Format((nMessages == 1) ? STRING(IDS_OOL_ALERTMESSAGE_SOFTOOL) : STRING(IDS_OOL_ALERTMESSAGE_SOFTOOLS), (LPCTSTR)szLabels, (LPCTSTR)pTMEnvironment->GetTMUnit()->GetTimeTag().FormatGmt());
		szMessages[1].Add(szAuditions[4].GetAt(nMessage));
		szParameters[4].RemoveAt(nMessage);
		szAuditions[4].RemoveAt(nMessage);
		szMessages[0].Add(szMessage);
		nParameters--;
		nMessage--;
	}
	for (nMessage = 0, nParameters = (INT)szParameters[5].GetSize(); nMessage < nParameters; nMessage++)
	{
		for (nParameter = nMessage, nMessages = 0, szLabels.Empty(); nParameter < nParameters; nParameter++)
		{
			if (szAuditions[5].GetAt(nMessage) == szAuditions[5].GetAt(nParameter))
			{
				szLabels += (nMessages > 0) ? (STRING(IDS_OOL_ALERTMESSAGE_SEPARATOR) + szParameters[5].GetAt(nParameter)) : szParameters[5].GetAt(nParameter);
				if (nParameter > nMessage)
				{
					szParameters[5].RemoveAt(nParameter);
					szAuditions[5].RemoveAt(nParameter);
					nParameters--;
					nParameter--;
				}
				nMessages++;
			}
		}
		szMessage.Format((nMessages == 1) ? STRING(IDS_OOL_ALERTMESSAGE_DELTAOOL) : STRING(IDS_OOL_ALERTMESSAGE_DELTAOOLS), (LPCTSTR)szLabels, (LPCTSTR)pTMEnvironment->GetTMUnit()->GetTimeTag().FormatGmt());
		szMessages[1].Add(szAuditions[5].GetAt(nMessage));
		szParameters[5].RemoveAt(nMessage);
		szAuditions[5].RemoveAt(nMessage);
		szMessages[0].Add(szMessage);
		nParameters--;
		nMessage--;
	}
	for (nMessage = 0, nParameters = (INT)szParameters[6].GetSize(); nMessage < nParameters; nMessage++)
	{
		for (nParameter = nMessage, nMessages = 0, szLabels.Empty(); nParameter < nParameters; nParameter++)
		{
			if (szAuditions[6].GetAt(nMessage) == szAuditions[6].GetAt(nParameter))
			{
				szLabels += (nMessages > 0) ? (STRING(IDS_OOL_ALERTMESSAGE_SEPARATOR) + szParameters[6].GetAt(nParameter)) : szParameters[6].GetAt(nParameter);
				if (nParameter > nMessage)
				{
					szParameters[6].RemoveAt(nParameter);
					szAuditions[6].RemoveAt(nParameter);
					nParameters--;
					nParameter--;
				}
				nMessages++;
			}
		}
		szMessage.Format((nMessages == 1) ? STRING(IDS_OOL_ALERTMESSAGE_DELTAOOL) : STRING(IDS_OOL_ALERTMESSAGE_DELTAOOLS), (LPCTSTR)szLabels, (LPCTSTR)pTMEnvironment->GetTMUnit()->GetTimeTag().FormatGmt());
		szMessages[1].Add(szAuditions[6].GetAt(nMessage));
		szParameters[6].RemoveAt(nMessage);
		szAuditions[6].RemoveAt(nMessage);
		szMessages[0].Add(szMessage);
		nParameters--;
		nMessage--;
	}
	for (nMessage = 0, nParameters = (INT)szParameters[8].GetSize(); nMessage < nParameters; nMessage++)
	{
		for (nParameter = nMessage, nMessages = 0, szLabels.Empty(); nParameter < nParameters; nParameter++)
		{
			if (szNotifications[1].GetAt(nMessage) == szNotifications[1].GetAt(nParameter))
			{
				szLabels += (nMessages > 0) ? (STRING(IDS_OOL_ALERTMESSAGE_SEPARATOR) + szParameters[8].GetAt(nParameter)) : szParameters[8].GetAt(nParameter);
				if (nParameter > nMessage)
				{
					szParameters[8].RemoveAt(nParameter);
					szNotifications[1].RemoveAt(nParameter);
					nParameters--;
					nParameter--;
				}
				nMessages++;
			}
		}
		szMessage.Format((nMessages == 1) ? STRING(IDS_OOL_ALERTMESSAGE_DELTAOOL) : STRING(IDS_OOL_ALERTMESSAGE_DELTAOOLS), (LPCTSTR)szLabels, (LPCTSTR)pTMEnvironment->GetTMUnit()->GetTimeTag().FormatGmt());
		szMessages[3].Add(szNotifications[1].GetAt(nMessage));
		szParameters[8].RemoveAt(nMessage);
		szNotifications[1].RemoveAt(nMessage);
		szMessages[2].Add(szMessage);
		nParameters--;
		nMessage--;
	}
	for (nMessage = 0, nParameters = (INT)szParameters[9].GetSize(); nMessage < nParameters; nMessage++)
	{
		for (nParameter = nMessage, nMessages = 0, szLabels.Empty(); nParameter < nParameters; nParameter++)
		{
			if (szNotifications[2].GetAt(nMessage) == szNotifications[2].GetAt(nParameter))
			{
				szLabels += (nMessages > 0) ? (STRING(IDS_OOL_ALERTMESSAGE_SEPARATOR) + szParameters[9].GetAt(nParameter)) : szParameters[9].GetAt(nParameter);
				if (nParameter > nMessage)
				{
					szParameters[9].RemoveAt(nParameter);
					szNotifications[2].RemoveAt(nParameter);
					nParameters--;
					nParameter--;
				}
				nMessages++;
			}
		}
		szMessage.Format((nMessages == 1) ? STRING(IDS_OOL_ALERTMESSAGE_DELTAOOL) : STRING(IDS_OOL_ALERTMESSAGE_DELTAOOLS), (LPCTSTR)szLabels, (LPCTSTR)pTMEnvironment->GetTMUnit()->GetTimeTag().FormatGmt());
		szMessages[3].Add(szNotifications[2].GetAt(nMessage));
		szParameters[9].RemoveAt(nMessage);
		szNotifications[2].RemoveAt(nMessage);
		szMessages[2].Add(szMessage);
		nParameters--;
		nMessage--;
	}
	for (nMessage = 0, nParameters = (INT)szParameters[10].GetSize(); nMessage < nParameters; nMessage++)
	{
		for (nParameter = nMessage, nMessages = 0, szLabels.Empty(); nParameter < nParameters; nParameter++)
		{
			if (szNotifications[3].GetAt(nMessage) == szNotifications[3].GetAt(nParameter))
			{
				szLabels += (nMessages > 0) ? (STRING(IDS_OOL_ALERTMESSAGE_SEPARATOR) + szParameters[10].GetAt(nParameter)) : szParameters[10].GetAt(nParameter);
				if (nParameter > nMessage)
				{
					szParameters[10].RemoveAt(nParameter);
					szNotifications[3].RemoveAt(nParameter);
					nParameters--;
					nParameter--;
				}
				nMessages++;
			}
		}
		szMessage.Format((nMessages == 1) ? STRING(IDS_OOL_ALERTMESSAGE_DELTAOOL) : STRING(IDS_OOL_ALERTMESSAGE_DELTAOOLS), (LPCTSTR)szLabels, (LPCTSTR)pTMEnvironment->GetTMUnit()->GetTimeTag().FormatGmt());
		szMessages[3].Add(szNotifications[3].GetAt(nMessage));
		szParameters[10].RemoveAt(nMessage);
		szNotifications[3].RemoveAt(nMessage);
		szMessages[2].Add(szMessage);
		nParameters--;
		nMessage--;
	}
	for (nMessage = 0, nParameters = (INT)szParameters[11].GetSize(); nMessage < nParameters; nMessage++)
	{
		for (nParameter = nMessage, nMessages = 0, szLabels.Empty(); nParameter < nParameters; nParameter++)
		{
			if (szNotifications[4].GetAt(nMessage) == szNotifications[4].GetAt(nParameter))
			{
				szLabels += (nMessages > 0) ? (STRING(IDS_OOL_ALERTMESSAGE_SEPARATOR) + szParameters[11].GetAt(nParameter)) : szParameters[11].GetAt(nParameter);
				if (nParameter > nMessage)
				{
					szParameters[11].RemoveAt(nParameter);
					szNotifications[4].RemoveAt(nParameter);
					nParameters--;
					nParameter--;
				}
				nMessages++;
			}
		}
		szMessage.Format((nMessages == 1) ? STRING(IDS_OOL_ALERTMESSAGE_DELTAOOL) : STRING(IDS_OOL_ALERTMESSAGE_DELTAOOLS), (LPCTSTR)szLabels, (LPCTSTR)pTMEnvironment->GetTMUnit()->GetTimeTag().FormatGmt());
		szMessages[3].Add(szNotifications[4].GetAt(nMessage));
		szParameters[11].RemoveAt(nMessage);
		szNotifications[4].RemoveAt(nMessage);
		szMessages[2].Add(szMessage);
		nParameters--;
		nMessage--;
	}
	if (szMessages[0].GetSize() > 0)
	{
		for (nMessage = 0, nMessages = (GetAuditionProfiles(cAuditionProfiles)) ? (INT)szMessages[0].GetSize() : 0, m_cAuditions.EnableSound(FALSE); nMessage < nMessages; nMessage++)
		{
			if ((pAuditionInfo = cAuditionProfiles.GetAt(cAuditionProfiles.Find(szMessages[1].GetAt(nMessage)))) != (CAuditionProfileInfo *)NULL)
			{
				for (pAuditionInfo->GetVoiceSound(szSpeaker, wVoiceGender, wVoiceAge), pAuditionInfo->GetAdapterInfo(szAdapter, dwAudio[0], dwAudio[1], dwAudio[2]); (pEvent = new CEventObject); )
				{
					pEvent->SetMessage(szMessages[0].GetAt(nMessage));
					pEvent->SetAudition(pAuditionInfo->GetAudition());
					pEvent->SetAudioInfo(szAdapter, dwAudio[0], dwAudio[1], dwAudio[2]);
					pEvent->SetAuditBeep(pAuditionInfo->GetBeepSound());
					pEvent->SetAuditWave(pAuditionInfo->GetWaveSound());
					pEvent->SetAuditVoice(szSpeaker, wVoiceGender, wVoiceAge);
					pEvent->SetAuditTime(CTime::GetCurrentTime().GetTime());
					pEvent->Acknowledge(FALSE);
					if (m_cAuditions.Add(pEvent) >= 0) break;
					delete pEvent;
					break;
				}
			}
		}
		m_cAuditions.EnableSound(TRUE);
	}
	if (szMessages[2].GetSize() > 0)
	{
		for (nMessage = 0, nMessages = (INT)szMessages[2].GetSize(); nMessage < nMessages; nMessage++)
		{
			DoNotification(szMessages[3].GetAt(nMessage), szMessages[2].GetAt(nMessage));
			continue;
		}
	}
	if (bBringToTop)
	{
		GetParent()->SendNotifyMessage(WM_SHOWWINDOW, TRUE, OOLPARAMETERFILTER_BEHAVIOR_BRINGTOTOP);
		return;
	}
	if (bAutoScroll)
	{
		ScrollToBottom();
		return;
	}
}

CString COOLView::LookupColumnName(UINT nColumn) CONST
{
	if (nColumn == OOL_TITLEITEM_ID) return STRING(IDS_OOL_TITLEITEM_ID);
	if (nColumn == OOL_TITLEITEM_DESCRIPTION) return STRING(IDS_OOL_TITLEITEM_DESCRIPTION);
	if (nColumn == OOL_TITLEITEM_VALUE) return STRING(IDS_OOL_TITLEITEM_VALUE);
	if (nColumn == OOL_TITLEITEM_LIMIT) return STRING(IDS_OOL_TITLEITEM_LIMIT);
	if (nColumn == OOL_TITLEITEM_UNIT) return STRING(IDS_OOL_TITLEITEM_UNIT);
	if (nColumn == OOL_TITLEITEM_OOLTYPE) return STRING(IDS_OOL_TITLEITEM_OOLTYPE);
	if (nColumn == OOL_TITLEITEM_OOLTIME) return STRING(IDS_OOL_TITLEITEM_OOLTIME);
	if (nColumn == OOL_TITLEITEM_OOLUNIT) return STRING(IDS_OOL_TITLEITEM_OOLUNIT);
	return EMPTYSTRING;
}
UINT COOLView::LookupColumnName(LPCTSTR pszColumn) CONST
{
	if (!lstrcmp(pszColumn, STRING(IDS_OOL_TITLEITEM_ID))) return OOL_TITLEITEM_ID;
	if (!lstrcmp(pszColumn, STRING(IDS_OOL_TITLEITEM_DESCRIPTION))) return OOL_TITLEITEM_DESCRIPTION;
	if (!lstrcmp(pszColumn, STRING(IDS_OOL_TITLEITEM_VALUE))) return OOL_TITLEITEM_VALUE;
	if (!lstrcmp(pszColumn, STRING(IDS_OOL_TITLEITEM_LIMIT))) return OOL_TITLEITEM_LIMIT;
	if (!lstrcmp(pszColumn, STRING(IDS_OOL_TITLEITEM_UNIT))) return OOL_TITLEITEM_UNIT;
	if (!lstrcmp(pszColumn, STRING(IDS_OOL_TITLEITEM_OOLTYPE))) return OOL_TITLEITEM_OOLTYPE;
	if (!lstrcmp(pszColumn, STRING(IDS_OOL_TITLEITEM_OOLTIME))) return OOL_TITLEITEM_OOLTIME;
	if (!lstrcmp(pszColumn, STRING(IDS_OOL_TITLEITEM_OOLUNIT))) return OOL_TITLEITEM_OOLUNIT;
	return 0;
}

INT COOLView::LookupColumnsName(CONST CUIntArray &nColumns, CStringArray &szColumns) CONST
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

INT COOLView::CalcColumnWidth(LPCTSTR pszColumn)
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
		if ((pOldFont = pDC->SelectObject(&m_wndContentCtrl.m_cFont)))
		{
			if ((nDxChar = (pDC->GetTextMetrics(&tmFont) > 0) ? (4 * tmFont.tmAveCharWidth / 3) : 0) > 0)
			{
				nWidth = (nColumn == OOL_TITLEITEM_ID) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetOOLIDColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == OOL_TITLEITEM_DESCRIPTION) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetOOLDescriptionColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == OOL_TITLEITEM_VALUE) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetOOLValueColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == OOL_TITLEITEM_LIMIT) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetOOLLimitColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == OOL_TITLEITEM_UNIT) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetOOLUnitColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == OOL_TITLEITEM_OOLTYPE) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetOOLTypeColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == OOL_TITLEITEM_OOLTIME) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetOOLTMTimeColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == OOL_TITLEITEM_OOLUNIT) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetOOLTMUnitColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
			}
			pDC->SelectObject(pOldFont);
		}
		for (szColumn = pszColumn; nColumn == OOL_TITLEITEM_VALUE; )
		{
			szColumn = CString(cStringTools.ConvertIntToString(0).GetAt(0), GetDatabase()->GetOOLValueColumnCharWidth());
			break;
		}
		for (; nColumn == OOL_TITLEITEM_OOLTIME; )
		{
			szColumn = CTimeTag().FormatGmt();
			break;
		}
		if ((pOldFont = pDC->SelectObject(&m_wndContentCtrl.m_cFont)))
		{
			nWidth = max(2 * GetSystemMetrics(SM_CXEDGE) + LOWORD(GetTextIndents()) + pDC->GetTextExtent(szColumn).cx + HIWORD(GetTextIndents()), nWidth);
			pDC->SelectObject(pOldFont);
		}
		ReleaseDC(pDC);
		return nWidth;
	}
	return 0;
}

INT COOLView::CalcColumnsWidth(CONST CUIntArray &nColumns, CUIntArray &nWidths)
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

INT COOLView::FindParameterIndex(INT nIndex) CONST
{
	return((nIndex < m_bParameters.GetSize() && m_bParameters.GetAt(nIndex)) ? DetermineParameterIndex(nIndex) : -1);
}

INT COOLView::DetermineParameterIndex(INT nIndex, BOOL bReverse) CONST
{
	INT  nCount;
	INT  nParameter;
	INT  nParameters;

	for (nParameter = 0, nParameters = (INT)m_bParameters.GetSize(), nCount = 0; ((!bReverse && nParameter < nIndex) || (bReverse && nCount <= nIndex)) && nParameter < nParameters; nParameter++)
	{
		nCount = (m_bParameters.GetAt(nParameter)) ? (nCount + 1) : nCount;
		continue;
	}
	return((bReverse) ? (nParameter - 1) : nCount);
}

UINT COOLView::PointToRow(CONST POINT &point) CONST
{
	INT  nRow;
	INT  nColumn;

	return((FindTextFromPoint(point, nRow, nColumn, FALSE) && nRow < GetTextCount()) ? nRow : -1);
}

UINT COOLView::PointToColumn(CONST POINT &point) CONST
{
	INT  nRow;
	INT  nColumn;

	return((FindTextFromPoint(point, nRow, nColumn, FALSE) && nRow < GetTextCount()) ? nColumn : -1);
}

CString COOLView::ConstructToolTipTitle(INT nRow) CONST
{
	CString  szTitle;
	COolParameter  *pOolParameter;

	szTitle.Format(STRING(IDS_OOL_TOOLTIP_TITLE), ((pOolParameter = m_pParameters[0].GetAt(DetermineParameterIndex(nRow, TRUE)))) ? (LPCTSTR)pOolParameter->GetTag() : EMPTYSTRING);
	return((nRow >= 0) ? (LPCTSTR)szTitle : EMPTYSTRING);
}

CString COOLView::ConstructToolTipText(INT nRow, LPCTSTR pszColumn) CONST
{
	INT  nIndex;
	UINT  nStatus;
	BOOL  bOutSet;
	WORD  wOolTable;
	WORD  wOolLimit;
	CString  szText;
	CString  szType;
	CString  szWidth;
	CString  szStatus;
	CString  szOolUnit;
	CString  szOolTime;
	CString  szCalTable;
	CString  szValue[4];
	CString  szValueChange;
	CString  szValueUpdate;
	CTimeTag  tOolUnit;
	ULONGLONG  nValue;
	CUIntArray  nOolTableRefs[2];
	COolParameter  *pOolParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CDatabaseTMNumOolTable  *pDatabaseTMNumOolTable;
	CDatabaseTMTxtOolTable  *pDatabaseTMTxtOolTable;

	if ((pOolParameter = m_pParameters[0].GetAt(DetermineParameterIndex(nRow, TRUE))))
	{
		if (!lstrcmp(pszColumn, STRING(IDS_OOL_TITLEITEM_ID)))
		{
			if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pOolParameter->GetTag()))))
			{
				for (szType.Format(STRING(IDS_OOL_TOOLTIP_TYPE), CDatabaseEngine::TranslateParameterTypeCode(pDatabaseTMParameter->GetAttributes(), FALSE)); szType.GetLength() < lstrlen(STRING(IDS_OOL_TOOLTIP_TYPE)); )
				{
					szType.Empty();
					break;
				}
				szWidth.Format(STRING(IDS_OOL_TOOLTIP_WIDTH), pDatabaseTMParameter->GetWidth());
				szText = (!szType.IsEmpty()) ? (szType + EOL + szWidth) : szWidth;
			}
			return szText;
		}
		if (!lstrcmp(pszColumn, STRING(IDS_OOL_TITLEITEM_DESCRIPTION)))
		{
			if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pOolParameter->GetTag()))))
			{
				szText.Format(STRING(IDS_OOL_TOOLTIP_DESCRIPTION), (LPCTSTR)pDatabaseTMParameter->GetDetails());
				szText = (pDatabaseTMParameter->GetDetails().IsEmpty()) ? STRING(IDS_OOL_TOOLTIP_NODESCRIPTION) : szText;
			}
			return szText;
		}
		if (!lstrcmp(pszColumn, STRING(IDS_OOL_TITLEITEM_VALUE)))
		{
			if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pOolParameter->GetTag()))))
			{
				if (pOolParameter->IsInitialized() && pOolParameter->GetRawValue(0, nValue, nStatus, szCalTable))
				{
					if ((pOolParameter->GetAttributes() & TMPARAMETER_CODING_BITPATTERN) || (pOolParameter->GetAttributes() & TMPARAMETER_CODING_INVERSEBITPATTERN))
					{
						pOolParameter->GetValueAsText(GetDatabase(), 0, (pOolParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_DECIMAL | TMPARAMETER_RADIX_HEXADECIMAL)) | TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_RADIX_BINARY, -1, szValue[0]);
						szValue[1].Format(STRING(IDS_OOL_TOOLTIP_CODEDVALUE), (LPCTSTR)szValue[0], STRING(IDS_OOL_TOOLTIP_BITVALUE));
					}
					if ((pOolParameter->GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) || (pOolParameter->GetAttributes() & TMPARAMETER_CODING_COMPLEMENTCOMPLEX))
					{
						pOolParameter->GetValueAsText(GetDatabase(), 0, (pOolParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_HEXADECIMAL)) | TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_RADIX_DECIMAL, -1, szValue[0]);
						szValue[1].Format(STRING(IDS_OOL_TOOLTIP_CODEDVALUE), (LPCTSTR)szValue[0], (pOolParameter->GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) ? STRING(IDS_OOL_TOOLTIP_SIGNEDVALUE) : STRING(IDS_OOL_TOOLTIP_COMPLEMENTVALUE));
					}
					if (pOolParameter->GetAttributes() & TMPARAMETER_CODING_UNSIGNEDINTEGER)
					{
						pOolParameter->GetValueAsText(GetDatabase(), 0, (pOolParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_HEXADECIMAL)) | TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_RADIX_DECIMAL, -1, szValue[0]);
						szValue[1].Format(STRING(IDS_OOL_TOOLTIP_CODEDVALUE), (LPCTSTR)szValue[0], STRING(IDS_OOL_TOOLTIP_UNSIGNEDVALUE));
					}
					if (pOolParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT)
					{
						pOolParameter->GetValueAsText(GetDatabase(), 0, (pOolParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_HEXADECIMAL)) | TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_RADIX_DECIMAL, (pDatabaseTMParameter->GetDecimalDigits() > 0) ? pDatabaseTMParameter->GetDecimalDigits() : -1, szValue[0]);
						szValue[1].Format(STRING(IDS_OOL_TOOLTIP_CODEDVALUE), (LPCTSTR)szValue[0], STRING(IDS_OOL_TOOLTIP_FLOATINGVALUE));
					}
					if ((pOolParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_FLOATINGPOINT)) == 0)
					{
						pOolParameter->GetValueAsText(GetDatabase(), 0, TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_RADIX_DECIMAL, -1, szValue[0]);
						szValue[1].Format(STRING(IDS_OOL_TOOLTIP_CODEDVALUE), (LPCTSTR)szValue[0], STRING(IDS_OOL_TOOLTIP_UNSIGNEDVALUE));
					}
					for (szValue[0].Format(STRING(IDS_OOL_TOOLTIP_RAWVALUE), nValue), pOolParameter->GetValueAsText(GetDatabase(), 0, pOolParameter->GetAttributes(), ((((pOolParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) && (pOolParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE)) || (pOolParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL)) && pDatabaseTMParameter->GetDecimalDigits() > 0) ? pDatabaseTMParameter->GetDecimalDigits() : -1, szValue[3], bOutSet, FALSE), szValue[2].Format((pOolParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) ? STRING(IDS_OOL_TOOLTIP_CALIBRATEDNUMERICALVALUE) : STRING(IDS_OOL_TOOLTIP_CALIBRATEDSTATUSVALUE), (LPCTSTR)(szValue[3] = (bOutSet) ? ((pOolParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) ? (szValue[3] + GetDatabase()->GetTMNumCalTablePointOutsideText()) : ((pOolParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS) ? (szValue[3] + GetDatabase()->GetTMTxtCalTablePointOutsideText()) : szValue[3])) : szValue[3]), (LPCTSTR)szCalTable, (bOutSet) ? ((pOolParameter->GetAttributes() & TMPARAMETER_INTERPRETATION_EXTRAPOLATE) ? STRING(IDS_OOL_TOOLTIP_EXTRPOLATEDVALUE) : STRING(IDS_OOL_TOOLTIP_OUTSETVALUE)) : STRING(IDS_OOL_TOOLTIP_INSETVALUE)), szValueChange.Format(STRING(IDS_OOL_TOOLTIP_VALUECHANGE), (LPCTSTR)pOolParameter->GetLastChangeTime().FormatGmt(), (LPCTSTR)pOolParameter->GetLastChangeTMUnit()), szValueUpdate.Format(STRING(IDS_OOL_TOOLTIP_VALUEUPDATE), (LPCTSTR)pOolParameter->GetLastUpdateTime().FormatGmt(), (LPCTSTR)pOolParameter->GetLastUpdateTMUnit()), szStatus.Format(STRING(IDS_OOL_TOOLTIP_STATUS), (nStatus & TMPARAMETER_STATUS_GOOD) ? STRING(IDS_OOL_TOOLTIP_GOODQUALITY) : STRING(IDS_OOL_TOOLTIP_BADQUALITY), (nStatus & TMPARAMETER_STATUS_SOFTLIMIT) ? STRING(IDS_OOL_TOOLTIP_SOFTOOL) : ((nStatus & TMPARAMETER_STATUS_HARDLIMIT) ? STRING(IDS_OOL_TOOLTIP_HARDOOL) : ((nStatus & TMPARAMETER_STATUS_DELTALIMIT) ? STRING(IDS_OOL_TOOLTIP_DELTAOOL) : ((nStatus & TMPARAMETER_STATUS_CONSISTENCYLIMIT) ? STRING(IDS_OOL_TOOLTIP_CONSISTENCYOOL) : STRING(IDS_OOL_TOOLTIP_NOOOL)))), (nStatus & TMPARAMETER_STATUS_VALID) ? STRING(IDS_OOL_TOOLTIP_VALID) : STRING(IDS_OOL_TOOLTIP_INVALID)); pOolParameter->GetAttributes() & TMPARAMETER_NATURE_CONSTANT; )
					{
						for (szValue[3].Format(STRING(IDS_OOL_TOOLTIP_RAWTEXT), (LPCTSTR)pDatabaseTMParameter->GetConstValueAsText()); (pOolParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_FLOATINGPOINT)) == 0; )
						{
							szValue[0] = szValue[3];
							break;
						}
						szValueChange.Empty();
						szValueUpdate.Empty();
						szStatus.Empty();
						break;
					}
					szText = (((pOolParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) || (pOolParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS)) && lstrlen(szCalTable) > 0) ? ((!szValueChange.IsEmpty() && !szValueUpdate.IsEmpty() && !szStatus.IsEmpty()) ? (szValue[0] + EOL + szValue[1] + EOL + szValue[2] + EOL + szValueChange + EOL + szValueUpdate + EOL + szStatus) : (szValue[0] + EOL + szValue[1] + EOL + szValue[2])) : ((!szValueChange.IsEmpty() && !szValueUpdate.IsEmpty() && !szStatus.IsEmpty()) ? (szValue[0] + EOL + szValue[1] + EOL + szValueChange + EOL + szValueUpdate + EOL + szStatus) : (szValue[0] + EOL + szValue[1]));
					return szText;
				}
				szText = STRING(IDS_OOL_TOOLTIP_NOVALUE);
			}
			return szText;
		}
		if (!lstrcmp(pszColumn, STRING(IDS_OOL_TITLEITEM_LIMIT)))
		{
			if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pOolParameter->GetTag()))))
			{
				if (pDatabaseTMParameter->GetOolTableRefs(nOolTableRefs[0], nOolTableRefs[1]) && pOolParameter->GetOolInfo(szOolUnit, tOolUnit, wOolTable, wOolLimit) && wOolTable < nOolTableRefs[0].GetSize())
				{
					if ((pDatabaseTMNumOolTable = ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL)) ? GetDatabase()->GetTMNumOolTables()->GetAt(nOolTableRefs[0].GetAt(wOolTable)) : (CDatabaseTMNumOolTable *)NULL))
					{
						szText.Format(STRING(IDS_OOL_TOOLTIP_LIMITS), (LPCTSTR)pDatabaseTMNumOolTable->GetName());
						return szText;
					}
					if ((pDatabaseTMTxtOolTable = (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS) ? GetDatabase()->GetTMTxtOolTables()->GetAt(nOolTableRefs[0].GetAt(wOolTable)) : (CDatabaseTMTxtOolTable *)NULL))
					{
						szText.Format(STRING(IDS_OOL_TOOLTIP_LIMITS), (LPCTSTR)pDatabaseTMTxtOolTable->GetName());
						return szText;
					}
				}
				szText = STRING(IDS_OOL_TOOLTIP_NOLIMITS);
			}
			return szText;
		}
		if (!lstrcmp(pszColumn, STRING(IDS_OOL_TITLEITEM_OOLUNIT)) || !lstrcmp(pszColumn, STRING(IDS_OOL_TITLEITEM_OOLTIME)))
		{
			if ((pOolParameter->GetAttributes() & TMPARAMETER_NATURE_CONSTANT) != TMPARAMETER_NATURE_CONSTANT)
			{
				if ((nIndex = GetDatabase()->GetTMPackets()->Find(pOolParameter->GetOolTMUnit())) >= 0)
				{
					szOolUnit.Format(STRING(IDS_OOL_TOOLTIP_OOLTMUNIT), (LPCTSTR)GetDatabase()->GetTMPackets()->GetAt(nIndex)->GetDescription(), (LPCTSTR)pOolParameter->GetOolTMUnit());
					szOolTime.Format(STRING(IDS_OOL_TOOLTIP_OOLTIME), (LPCTSTR)pOolParameter->GetOolTime().FormatGmt(), (LPCTSTR)pOolParameter->GetOolTime().FormatGmt(CString(STRING(IDS_TIMETAG_DATEFORMAT)) + SPACE + STRING(IDS_TIMETAG_TIMEFORMAT)));
					szText = szOolUnit + EOL + szOolTime;
					return szText;
				}
				szText.Format(STRING(IDS_OOL_TOOLTIP_OOLTIME), (LPCTSTR)pOolParameter->GetOolTime().FormatGmt(), (LPCTSTR)pOolParameter->GetOolTime().FormatGmt(CString(STRING(IDS_TIMEKEY_DATEFORMAT)) + SPACE + STRING(IDS_TIMEKEY_TIMEFORMAT)));
			}
		}
	}
	return szText;
}

BOOL COOLView::LoadToolTipCursor()
{
	return(((m_hToolTipCursor = (HCURSOR)LoadImage(GetModuleHandle((LPCTSTR)NULL), MAKEINTRESOURCE(IDC_TOOLTIPCURSOR), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR))) ? TRUE : FALSE);
}

HCURSOR COOLView::GetToolTipCursor() CONST
{
	return((!m_hToolTipCursor) ? (HCURSOR)(DWORD_PTR)GetClassLongPtr(GetSafeHwnd(), GCLP_HCURSOR) : m_hToolTipCursor);
}

BOOL COOLView::FreeToolTipCursor()
{
	if (m_hToolTipCursor)
	{
		DestroyCursor(m_hToolTipCursor);
		m_hToolTipCursor = (HCURSOR)NULL;
		return TRUE;
	}
	return FALSE;
}

VOID COOLView::AdjustColumns()
{
	CDC  *pDC;
	INT  nLine;
	INT  nLines;
	INT  nIndex;
	INT  nColumn;
	INT  nColumns;
	INT  nWidth[2];
	BOOL  bWidth[1];
	CFont  cFont[2];
	CFont  *pOldFont[2];
	CString  szText[1];
	CUIntArray  nWidths;
	CStringArray  szColumns;
	CStringArray  szContents;
	CTextViewAttributes  pAttributes;

	if ((pDC = (IsWindow(GetSafeHwnd())) ? GetDC() : (CDC *)NULL))
	{
		if ((pOldFont[0] = (GetTitleFont(&cFont[0]) && GetItemsFont(&cFont[1])) ? pDC->SelectObject(&cFont[0]) : (CFont *)NULL))
		{
			for (nColumn = 0, nColumns = (GetColumns(szColumns, nWidths)) ? (INT)szColumns.GetSize() : -1, bWidth[0] = FALSE; nColumn < nColumns; nColumn++)
			{
				nWidth[0] = LOWORD(GetTextIndents()) + HIWORD(GetTextIndents()) + pDC->GetTextExtent(szColumns.GetAt(nColumn)).cx;
				nWidth[0] = max(CalcColumnWidth(szColumns.GetAt(nColumn)), nWidth[0]);
				if ((pOldFont[1] = pDC->SelectObject(&cFont[1])) != (CFont *)NULL)
				{
					for (nLine = 0, nLines = GetTextCount(); nLine < nLines; nLine++)
					{
						if (GetText(nLine, nColumn, szText[0]))
						{
							nWidth[1] = pDC->GetTextExtent(szText[0]).cx;
							nWidth[1] += LOWORD(GetTextIndents()) + HIWORD(GetTextIndents());
							nWidth[0] = max(nWidth[0], nWidth[1]);
						}
					}
					pDC->SelectObject(pOldFont[1]);
				}
				if (!nColumn)
				{
					if (nWidth[0] != (INT)nWidths.GetAt(nColumn))
					{
						for (nIndex = nColumn; nIndex < nColumns; nIndex++)
						{
							nWidths.SetAt(nIndex, nWidths.GetAt(nIndex) + nWidth[0] - nWidths.GetAt(nColumn));
							continue;
						}
						bWidth[0] = TRUE;
					}
					continue;
				}
				if (nWidth[0] != (INT)(nWidths.GetAt(nColumn) - nWidths.GetAt(nColumn - 1)))
				{
					for (nIndex = nColumn; nIndex < nColumns; nIndex++)
					{
						nWidths.SetAt(nIndex, nWidths.GetAt(nIndex) + nWidth[0] - nWidths.GetAt(nColumn) + nWidths.GetAt(nColumn - 1));
						continue;
					}
					bWidth[0] = TRUE;
					continue;
				}
			}
			if (nColumn == nColumns  &&  bWidth[0])
			{
				if (GetContent(szContents, pAttributes) && SetColumns(szColumns, nWidths) && SetContent(szContents, pAttributes))
				{
					pDC->SelectObject(pOldFont[0]);
					ReleaseDC(pDC);
					return;
				}
			}
			pDC->SelectObject(pOldFont[0]);
		}
		ReleaseDC(pDC);
	}
}

BOOL COOLView::SetLayoutInfo(INT nIndex, INT nCount, CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo)
{
	CTextViewLock  cLock(this);

	for (SetScrollInfo(pHorzScrollInfo, pVertScrollInfo); nCount > 0; )
	{
		SetCurText(nIndex);
		ScrollTo(nIndex);
		break;
	}
	return TRUE;
}

BOOL COOLView::GetLayoutInfo(INT &nIndex, INT &nCount, SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST
{
	CTextViewLock  cLock(this);

	nIndex = GetCurText();
	nCount = GetTextCount();
	GetScrollInfo(pHorzScrollInfo, pVertScrollInfo);
	return TRUE;
}

VOID COOLView::RecalcLayout()
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

VOID COOLView::RefreshContent()
{
	CTextViewLock  cLock(this);

	Update();
}

void COOLView::PostNcDestroy()
{
	m_pFilters.RemoveAll();
	m_cAuditions.RemoveAll();
	m_bParameters.RemoveAll();
	m_pParameters[0].RemoveAll();
	m_pParameters[1].RemoveAll();
	m_pParameters[2].RemoveAll();
	m_nLayoutColumns.RemoveAll();
	CTextView::PostNcDestroy();
}

BOOL COOLView::Lock()
{
	return((IsWindow(GetSafeHwnd())) ? (GetParent()->Lock() && CTextView::Lock()) : CTextView::Lock());
}

BOOL COOLView::Unlock()
{
	return((IsWindow(GetSafeHwnd())) ? (CTextView::Unlock() && GetParent()->Unlock()) : CTextView::Unlock());
}

BEGIN_MESSAGE_MAP(COOLView, CTextView)
	//{{AFX_MSG_MAP(COOLView)
	ON_WM_CREATE()
	ON_WM_SETCURSOR()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COOLView message handlers

int COOLView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CTextViewLock  cLock(this);

	if (CTextView::OnCreate(lpCreateStruct) != -1)
	{
		LoadToolTipCursor();
		return 0;
	}
	return -1;
}

BOOL COOLView::OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message)
{
	INT  nColumn;
	INT  nColumns;
	LONG  lDataFlag;
	POINT  ptCursor;
	CRect  rContent;
	CString  szColumn;
	CStringArray  szColumns;
	CTextViewLock  cLock(this);

	for (GetCursorPos(&ptCursor), m_wndContentCtrl.ScreenToClient(&ptCursor), m_wndContentCtrl.GetClientRect(rContent); rContent.PtInRect(ptCursor); )
	{
		if ((lDataFlag = GetParent()->IsRetrievingData()) && HIWORD(lDataFlag))
		{
			SetCursor(LoadCursor((HINSTANCE)NULL, IDC_WAIT));
			return TRUE;
		}
		for (nColumn = PointToColumn(ptCursor), nColumns = (IsToolTipModeEnabled() && GetColumns(szColumns)) ? (INT)szColumns.GetSize() : 0; (szColumn = (nColumn >= 0 && nColumn < nColumns) ? szColumns.GetAt(nColumn) : szColumn) == STRING(IDS_OOL_TITLEITEM_ID) || szColumn == STRING(IDS_OOL_TITLEITEM_DESCRIPTION) || szColumn == STRING(IDS_OOL_TITLEITEM_VALUE) || szColumn == STRING(IDS_OOL_TITLEITEM_LIMIT) || szColumn == STRING(IDS_OOL_TITLEITEM_OOLUNIT) || szColumn == STRING(IDS_OOL_TITLEITEM_OOLTIME); )
		{
			SetCursor(GetToolTipCursor());
			return TRUE;
		}
		break;
	}
	return CTextView::OnSetCursor(pWnd, nHitTest, message);
}

BOOL COOLView::OnContentMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	INT  nRow;
	INT  nColumn;
	LONG  lDataFlag;
	CFont  cFont[2];
	POINT  ptCursor;
	CPoint  ptToolTip;
	LOGFONT  lfFont[2];
	CString  szColumn;
	CString  szParameter;
	CString  szToolTip[2];
	CStringArray  szColumns;
	COolParameter  *pOolParameter;
	CTextViewLock  cLock(this);

	if (message == WM_SETFOCUS)
	{
		SetCurText((GetCurText() >= 0) ? GetCurText() : 0);
		return FALSE;
	}
	if (message == WM_KEYDOWN)
	{
		if (wParam == VK_RETURN)
		{
			if ((nRow = GetCurText()) >= 0)
			{
				if ((pOolParameter = m_pParameters[0].GetAt(DetermineParameterIndex(nRow, TRUE))))
				{
					for (szParameter = pOolParameter->GetTag(), cLock.Release(); !szParameter.IsEmpty(); )
					{
						GetParent()->SetParameterInfo(szParameter);
						break;
					}
					return FALSE;
				}
			}
		}
		if (wParam == VK_TAB) GetParent()->SetFocus();
		return FALSE;
	}
	for (GetCursorPos(&ptCursor), m_wndContentCtrl.ScreenToClient(&ptCursor); message == WM_LBUTTONDOWN; )
	{
		if (!(lDataFlag = GetParent()->IsRetrievingData()) || !HIWORD(lDataFlag))
		{
			if (FindTextFromPoint(ptCursor, nRow, nColumn, FALSE) && nRow == GetCurText())
			{
				*pResult = FALSE;
				SetCurText(-1);
				return TRUE;
			}
		}
		return FALSE;
	}
	if (message == WM_LBUTTONDBLCLK)
	{
		if (!(lDataFlag = GetParent()->IsRetrievingData()) || !HIWORD(lDataFlag))
		{
			if ((pOolParameter = (FindTextFromPoint((ptToolTip = CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))), nRow, nColumn, FALSE)) ? m_pParameters[0].GetAt(DetermineParameterIndex(nRow, TRUE)) : (COolParameter *)NULL))
			{
				for (szParameter = pOolParameter->GetTag(), SetCurText(nRow), cLock.Release(); !szParameter.IsEmpty(); )
				{
					GetParent()->SetParameterInfo(szParameter);
					break;
				}
			}
		}
		return FALSE;
	}
	if (message == WM_RBUTTONDOWN)
	{
		if (!(lDataFlag = GetParent()->IsRetrievingData()) || !HIWORD(lDataFlag))
		{
			for (nRow = PointToRow((ptToolTip = CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)))), nColumn = PointToColumn(ptToolTip); (szColumn = (IsToolTipModeEnabled() && GetColumns(szColumns) && nColumn >= 0 && nColumn < szColumns.GetSize()) ? szColumns.GetAt(nColumn) : EMPTYSTRING) == STRING(IDS_OOL_TITLEITEM_ID) || szColumn == STRING(IDS_OOL_TITLEITEM_DESCRIPTION) || szColumn == STRING(IDS_OOL_TITLEITEM_VALUE) || szColumn == STRING(IDS_OOL_TITLEITEM_LIMIT) || szColumn == STRING(IDS_OOL_TITLEITEM_OOLUNIT) || szColumn == STRING(IDS_OOL_TITLEITEM_OOLTIME); )
			{
				for (szToolTip[0] = ConstructToolTipTitle(nRow), szToolTip[1] = ConstructToolTipText(nRow, szColumn), GetTextFont(&lfFont[0]), GetTextFont(&lfFont[1]), lfFont[0].lfWeight = FW_BOLD, lfFont[1].lfWeight = FW_NORMAL; cFont[0].CreateFontIndirect(&lfFont[0]) && cFont[1].CreateFontIndirect(&lfFont[1]); )
				{
					m_wndToolTip.SetTitleFont(&cFont[0]);
					m_wndToolTip.SetTextFont(&cFont[1]);
					break;
				}
				m_wndToolTip.Create(&m_wndContentCtrl, ptToolTip, szToolTip[0], szToolTip[1]);
				break;
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

BOOL COOLView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	CStringArray  szColumns;
	NMHEADER  *pNotifyInfo = (NMHEADER *)lParam;

	if (pNotifyInfo->hdr.code == HDN_ITEMCLICK)
	{
		for (m_szSearchItem = (GetColumns(szColumns) && pNotifyInfo->iItem < szColumns.GetSize()) ? szColumns.GetAt(pNotifyInfo->iItem) : EMPTYSTRING; !m_szSearchItem.IsEmpty(); )
		{
			SetTimer(OOLVIEW_SEARCH_TIMERID, OOLVIEW_SEARCH_TIMEOUT, NULL);
			break;
		}
	}
	return CTextView::OnNotify(wParam, lParam, pResult);
}

void COOLView::OnTimer(UINT_PTR nEventID)
{
	if (nEventID == OOLVIEW_SEARCH_TIMERID)
	{
		for (KillTimer(nEventID); m_szSearchItem == STRING(IDS_OOL_TITLEITEM_ID); )
		{
			GetParent()->ShowSearchParameterIDDetails();
			break;
		}
		for (; m_szSearchItem == STRING(IDS_OOL_TITLEITEM_DESCRIPTION); )
		{
			GetParent()->ShowSearchParameterDescriptionDetails();
			break;
		}
		for (; m_szSearchItem == STRING(IDS_OOL_TITLEITEM_VALUE); )
		{
			GetParent()->ShowSearchParameterValueDetails();
			break;
		}
		for (; m_szSearchItem == STRING(IDS_OOL_TITLEITEM_LIMIT); )
		{
			GetParent()->ShowSearchParameterLimitDetails();
			break;
		}
		for (; m_szSearchItem == STRING(IDS_OOL_TITLEITEM_UNIT); )
		{
			GetParent()->ShowSearchParameterUnitDetails();
			break;
		}
		for (; m_szSearchItem == STRING(IDS_OOL_TITLEITEM_OOLTYPE); )
		{
			GetParent()->ShowSearchParameterOolTypeDetails();
			break;
		}
		for (; m_szSearchItem == STRING(IDS_OOL_TITLEITEM_OOLUNIT); )
		{
			GetParent()->ShowSearchParameterOolUnitDetails();
			break;
		}
		for (; m_szSearchItem == STRING(IDS_OOL_TITLEITEM_OOLTIME); )
		{
			GetParent()->ShowSearchParameterOolTimeDetails();
			break;
		}
		m_szSearchItem.Empty();
	}
	CTextView::OnTimer(nEventID);
}

void COOLView::OnDestroy()
{
	CTextViewLock  cLock(this);

	FreeToolTipCursor();
	m_cAuditions.EnableSound(FALSE);
	CTextView::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// COOLWnd

IMPLEMENT_DYNAMIC(COOLWnd, CDisplayWnd)

COOLWnd::COOLWnd() : CDisplayWnd()
{
	SetType(DISPLAY_TYPE_OOL);
	SetRetrieveMode();
	SetRetrieveSpeed();
	SetRetrieveInterval();
	SetRetrieveStartTime();
	SetRetrieveStopTime();
	SetUpdateInfo();
}

BOOL COOLWnd::Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszTitle, PDISPLAYINFO pDefaultInfo, BOOL bDefault)
{
	if (CDisplayWnd::Create(pParentWnd, (!pszTitle || (!_tcsstr(pszTitle, STRING(IDS_DISPLAY_TITLE_GLOBALOOL)) && !_tcsstr(pszTitle, STRING(IDS_DISPLAY_TITLE_OOL)))) ? ((pDefaultInfo->nScope == DISPLAY_SCOPE_GLOBAL) ? STRING(IDS_DISPLAY_TITLE_GLOBALOOL) : STRING(IDS_DISPLAY_TITLE_OOL)) : pszTitle, pDefaultInfo->rWnd, IDR_OOLFRAME))
	{
		if (((pDefaultInfo->nScope == DISPLAY_SCOPE_GLOBAL  &&  SetType(MAKELONG(DISPLAY_TYPE_OOL, OOL_TYPE_GLOBAL))) || (pDefaultInfo->nScope == DISPLAY_SCOPE_LOCAL  &&  SetType(MAKELONG(DISPLAY_TYPE_OOL, OOL_TYPE_NORMAL)))) && SetScope(pDefaultInfo->nScope) && SetMode(pDefaultInfo->nMode) && Customize(bDefault)) return TRUE;
		DestroyWindow();
	}
	return FALSE;
}

BOOL COOLWnd::SetLayout(LPCTSTR pszLayout)
{
	return m_wndView.SetLayout(pszLayout);
}
BOOL COOLWnd::SetLayout(LPCTSTR pszLayout, CONST CUIntArray &nColumns)
{
	return m_wndView.SetLayout(pszLayout, nColumns);
}
BOOL COOLWnd::SetLayout(LPCTSTR pszLayout, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths)
{
	return m_wndView.SetLayout(pszLayout, nColumns, nWidths);
}

BOOL COOLWnd::GetLayout(CString &szLayout) CONST
{
	return m_wndView.GetLayout(szLayout);
}
BOOL COOLWnd::GetLayout(CString &szLayout, CUIntArray &nColumns) CONST
{
	return m_wndView.GetLayout(szLayout, nColumns);
}
BOOL COOLWnd::GetLayout(CString &szLayout, CUIntArray &nColumns, CUIntArray &nWidths) CONST
{
	return m_wndView.GetLayout(szLayout, nColumns, nWidths);
}

BOOL COOLWnd::SetTitleFont(CFont *pFont)
{
	return m_wndView.SetTitleFont(pFont);
}
BOOL COOLWnd::SetTitleFont(CONST LOGFONT *plfFont)
{
	return m_wndView.SetTitleFont(plfFont);
}

BOOL COOLWnd::GetTitleFont(CFont *pFont) CONST
{
	return m_wndView.GetTitleFont(pFont);
}
BOOL COOLWnd::GetTitleFont(LOGFONT *plfFont) CONST
{
	return m_wndView.GetTitleFont(plfFont);
}

BOOL COOLWnd::SetItemsFont(CFont *pFont)
{
	return m_wndView.SetItemsFont(pFont);
}
BOOL COOLWnd::SetItemsFont(CONST LOGFONT *plfFont)
{
	return m_wndView.SetItemsFont(plfFont);
}

BOOL COOLWnd::GetItemsFont(CFont *pFont) CONST
{
	return m_wndView.GetItemsFont(pFont);
}
BOOL COOLWnd::GetItemsFont(LOGFONT *plfFont) CONST
{
	return m_wndView.GetItemsFont(plfFont);
}

BOOL COOLWnd::EnableInvalidDataMode(BOOL bEnable)
{
	return m_wndView.EnableInvalidDataMode(bEnable);
}

BOOL COOLWnd::IsInvalidDataModeEnabled() CONST
{
	return m_wndView.IsInvalidDataModeEnabled();
}

BOOL COOLWnd::EnableBadDataMode(BOOL bEnable)
{
	return m_wndView.EnableBadDataMode(bEnable);
}

BOOL COOLWnd::IsBadDataModeEnabled() CONST
{
	return m_wndView.IsBadDataModeEnabled();
}

BOOL COOLWnd::EnableToolTipMode(BOOL bEnable)
{
	return m_wndView.EnableToolTipMode(bEnable);
}

BOOL COOLWnd::IsToolTipModeEnabled() CONST
{
	return m_wndView.IsToolTipModeEnabled();
}

BOOL COOLWnd::SetParameterFilters(CONST COOLParameterFilters &pFilters)
{
	return m_wndView.SetFilters(pFilters);
}

BOOL COOLWnd::GetParameterFilters(COOLParameterFilters &pFilters) CONST
{
	return m_wndView.GetFilters(pFilters);
}

BOOL COOLWnd::SetFilterColors(CONST CUIntArray &nColors)
{
	return m_wndView.SetColors(nColors);
}

BOOL COOLWnd::GetFilterColors(CUIntArray &nColors) CONST
{
	return m_wndView.GetColors(nColors);
}

BOOL COOLWnd::Start()
{
	if (((GetMode() == DISPLAY_MODE_REALTIME  &&  ProcessRealtimeData()) || (GetMode() == DISPLAY_MODE_HISTORY  &&  StartRetrieveData())) && StartSchedulePrintJobs())
	{
		Initialize(TRUE);
		UpdateAllPanes();
		return TRUE;
	}
	return FALSE;
}

BOOL COOLWnd::Prepare(BOOL bDialog)
{
	INT  nResult;

	if (bDialog)
	{
		if ((nResult = m_dlgOpen.Create(this)) == IDCANCEL || nResult <= 0) MDIDestroy();
		return((nResult == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
	}
	return TRUE;
}

BOOL COOLWnd::Initialize(BOOL bFlag)
{
	return CDisplayWnd::Initialize(bFlag);
}
BOOL COOLWnd::Initialize(CTMEnvironment *pTMEnvironment)
{
	return m_wndView.Initialize(pTMEnvironment);
}
BOOL COOLWnd::Initialize(CString &szTag, CTimeTag &tTag)
{
	return m_wndView.Initialize(szTag, tTag);
}

BOOL COOLWnd::InitializeTMData(UINT nMode)
{
	for (StopRetrieveData(); (nMode == DISPLAY_MODE_REALTIME && SetMode(DISPLAY_MODE_REALTIME) && ProcessRealtimeData()) || (nMode == DISPLAY_MODE_HISTORY && SetMode(DISPLAY_MODE_HISTORY) && StartRetrieveData()); )
	{
		UpdateBars();
		return TRUE;
	}
	return FALSE;
}
BOOL COOLWnd::InitializeTMData(COolParameters &pOolParameters, BOOL bBadData)
{
	return((GetMode() == DISPLAY_MODE_HISTORY) ? ((!GetLink()) ? m_cRetrieveThread.InitializeTMData(pOolParameters, bBadData) : FALSE) : FALSE);
}
BOOL COOLWnd::InitializeTMData(CTMParameters &pTMParameters, BOOL bBadData)
{
	CDisplayWnd  *pDisplayWnd;

	return((GetMode() == DISPLAY_MODE_HISTORY) ? (((pDisplayWnd = GetLink())) ? pDisplayWnd->InitializeTMData(pTMParameters, bBadData) : m_cRetrieveThread.InitializeTMData(pTMParameters, bBadData)) : GetTMService()->InitializeTMData(pTMParameters, bBadData));
}

BOOL COOLWnd::Check() CONST
{
	return CheckAccountPrivilege(PRIVILEGE_OOL_USE);
}

VOID COOLWnd::Update()
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
BOOL COOLWnd::Update(CONST CTimeKey &tTimeKey, CTMEnvironment *pTMEnvironment, UINT nFlags)
{
	INT  nLink;
	INT  nLinks;
	CPtrArray  pLinks;
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
			if (GetRetrieveMode() & (OOL_RETRIEVE_AUTOBACKWARD | OOL_RETRIEVE_MANUALBACKWARD)) Reset(pTMEnvironment);
			return TRUE;
		}
	}
	return FALSE;
}

VOID COOLWnd::Reset(CTMEnvironment *pTMEnvironment)
{
	CDisplayLock  cLock(this);

	if (IsInitialized())
	{
		if (pTMEnvironment != (CTMEnvironment *)NULL) pTMEnvironment->Reset();
		m_wndView.Reset(pTMEnvironment);
		SetUpdateInfo();
	}
}

BOOL COOLWnd::Stop()
{
	Initialize(FALSE);
	StopSchedulePrintJobs();
	StopRetrieveData();
	return TRUE;
}

BOOL COOLWnd::SaveInfo(INT nPage, INT nDisplay, LPCTSTR pszTitle, CONST PDISPLAYINFO pDisplayInfo)
{
	UINT  nMode;
	UINT  nSpeed;
	CString  szName;
	CString  szFileName;
	LOGFONT  sFontInfo[2];
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CUIntArray  nColumns;
	CUIntArray  nWidths;
	CByteArray  nFilterInfo;
	CByteArray  nPrintInfo;
	CProfile  cProfile;

	return((CDisplayWnd::SaveInfo(nPage, nDisplay, pszTitle, pDisplayInfo) && ((nPage > 0 && pDisplayInfo->nScope == DISPLAY_SCOPE_GLOBAL) || (GetLayout(szName, nColumns, nWidths) && GetTitleFont(&sFontInfo[0]) && GetItemsFont(&sFontInfo[1]) && GetRetrieveMode(nMode) && GetRetrieveSpeed(nSpeed) && GetRetrieveInterval(tInterval) && GetRetrieveStartTime(tStartTime) && GetRetrieveStopTime(tStopTime) && GetRetrieveFileName(szFileName) && GetParameterFilters(nFilterInfo) && GetPrintJobs(nPrintInfo) && cProfile.SetOOLLayoutName(nPage, nDisplay, szName) && cProfile.SetOOLLayoutInfo(nPage, nDisplay, nColumns, nWidths, IsBadDataModeEnabled(), IsToolTipModeEnabled()) && cProfile.SetOOLFontsInfo(nPage, nDisplay, &sFontInfo[0], &sFontInfo[1]) && cProfile.SetOOLModeInfo(nPage, nDisplay, nMode, nSpeed, tInterval, tStartTime, tStopTime) && cProfile.SetOOLRetrieveFileName(nPage, nDisplay, szFileName) && cProfile.SetOOLFilterInfo(nPage, nDisplay, nFilterInfo) && cProfile.SetOOLPrintInfo(nPage, nDisplay, nPrintInfo)))) ? TRUE : FALSE);
}

BOOL COOLWnd::LoadInfo(INT nPage, INT nDisplay, CString &szTitle, PDISPLAYINFO pDisplayInfo)
{
	UINT  nMode;
	UINT  nSpeed;
	BOOL  bBadData;
	BOOL  bToolTips;
	CString  szName;
	CString  szFileName;
	LOGFONT  sFontInfo[2];
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CUIntArray  nColumns;
	CUIntArray  nWidths;
	CByteArray  nFilterInfo;
	CByteArray  nPrintInfo;
	CProfile  cProfile;

	return((CDisplayWnd::LoadInfo(nPage, nDisplay, szTitle, pDisplayInfo) && ((nPage > 0 && pDisplayInfo->nScope == DISPLAY_SCOPE_GLOBAL) || (cProfile.GetOOLLayoutName(nPage, nDisplay, szName) && cProfile.GetOOLLayoutInfo(nPage, nDisplay, nColumns, nWidths, bBadData, bToolTips) && cProfile.GetOOLFontsInfo(nPage, nDisplay, &sFontInfo[0], &sFontInfo[1]) && cProfile.GetOOLModeInfo(nPage, nDisplay, nMode, nSpeed, tInterval, tStartTime, tStopTime) && cProfile.GetOOLRetrieveFileName(nPage, nDisplay, szFileName) && cProfile.GetOOLFilterInfo(nPage, nDisplay, nFilterInfo) && cProfile.GetOOLPrintInfo(nPage, nDisplay, nPrintInfo) && SetLayout(szName, nColumns, nWidths) && EnableBadDataMode(bBadData) && EnableToolTipMode(bToolTips) && SetTitleFont(&sFontInfo[0]) && SetItemsFont(&sFontInfo[1]) && SetRetrieveMode(nMode) && SetRetrieveSpeed(nSpeed) && SetRetrieveInterval(tInterval) && SetRetrieveStartTime(tStartTime) && SetRetrieveStopTime(tStopTime) && SetRetrieveFileName(szFileName) && SetParameterFilters(nFilterInfo) && SetPrintJobs(nPrintInfo)))) ? TRUE : FALSE);
}

BOOL COOLWnd::SetLayoutInfo(LPCVOID pData)
{
	INT  cbData;
	DATA  sData;
	CUIntArray  nColumns;
	CUIntArray  nWidths;
	CDisplayLock  cLock(this);

	if (GetScope() == DISPLAY_SCOPE_GLOBAL)
	{
		for (CopyMemory(&sData, pData, ((cbData = (INT)GlobalSize((HGLOBAL)pData)) >= sizeof(DATA)) ? sizeof(DATA) : 0); cbData >= sizeof(DATA) && sData.cbSize == sizeof(DATA) + sData.cbColumns[0] + sData.cbColumns[1] && sData.cbColumns[0] >= 0 && sData.cbColumns[1] >= 0; )
		{
			for (nColumns.SetSize(sData.cbColumns[0] / sizeof(UINT)), nWidths.SetSize(sData.cbColumns[1] / sizeof(UINT)), CopyMemory(nColumns.GetData(), (LPBYTE)pData + (cbData = sizeof(DATA)), sData.cbColumns[0]), CopyMemory(nWidths.GetData(), (LPBYTE)pData + (cbData = cbData + sData.cbColumns[0]), sData.cbColumns[1]); SetLayoutInfo(nColumns, nWidths, &sData.sFont[0], &sData.sFont[1], sData.nIndex, sData.nCount, &sData.sScrollInfo[0], &sData.sScrollInfo[1]); ) return TRUE;
			break;
		}
		return FALSE;
	}
	return TRUE;
}

INT COOLWnd::GetLayoutInfo(LPVOID *pData) CONST
{
	INT  cbData;
	DATA  sData;
	LPVOID  pBlock;
	CUIntArray  nColumns;
	CUIntArray  nWidths;
	CDisplayLock  cLock(this);

	if (GetScope() == DISPLAY_SCOPE_GLOBAL)
	{
		if (GetLayoutInfo(nColumns, nWidths, &sData.sFont[0], &sData.sFont[1], sData.nIndex, sData.nCount, &sData.sScrollInfo[0], &sData.sScrollInfo[1]))
		{
			for (sData.cbColumns[0] = (INT)(nColumns.GetSize()*sizeof(UINT)), sData.cbColumns[1] = (INT)(nWidths.GetSize()*sizeof(UINT)), sData.cbSize = sizeof(DATA) + sData.cbColumns[0] + sData.cbColumns[1]; (pBlock = (pData != (LPVOID *)NULL) ? (LPVOID)GlobalReAlloc(*pData, sData.cbSize, GMEM_MOVEABLE | GMEM_ZEROINIT) : (LPVOID)NULL); )
			{
				CopyMemory(pData, &pBlock, sizeof(LPVOID));
				CopyMemory(pBlock, &sData, sizeof(DATA));
				CopyMemory((LPBYTE)pBlock + (cbData = sizeof(DATA)), nColumns.GetData(), sData.cbColumns[0]);
				CopyMemory((LPBYTE)pBlock + (cbData = cbData + sData.cbColumns[0]), nWidths.GetData(), sData.cbColumns[1]);
				break;
			}
			return sData.cbSize;
		}
	}
	return 0;
}

BOOL COOLWnd::QueryDefaultInfo(PDISPLAYINFO pDefaultInfo) CONST
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

BOOL COOLWnd::QueryDefaultMenu(CLocaleMenu &cMenu, CImageList &cImages, CUIntArray &nImageIDs) CONST
{
	INT  nIndex;
	INT  nCount;
	INT  iImage;
	UINT  nButtonID;
	UINT  nButtonStyle;
	CBitmap  cBitmap;
	BITMAP  sBitmap;

	for (cImages.DeleteImageList(), nImageIDs.RemoveAll(); cBitmap.LoadBitmap(IDB_OOLFRAMESMALLIMAGES) && cBitmap.GetBitmap(&sBitmap); )
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
	return cMenu.LoadMenu(IDR_OOLFRAME);
}

BOOL COOLWnd::Print(PRINTDLG *pPrintInfo)
{
	INT  nJob;
	INT  nJobs;
	COOLPrintJobs  pJobs;
	COOLPrintJobInfo  *pJobInfo;
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
		if (pJobInfo->GetPrintMode() & OOL_PRINT_CLEARCOMMENTS)
		{
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~OOL_PRINT_CLEARCOMMENTS);
			pJobInfo->SetComments(EMPTYSTRING);
			SetPrintJobs(pJobs);
		}
		return TRUE;
	}
	return FALSE;
}

BOOL COOLWnd::CanPrint() CONST
{
	return HasParameters();
}

BOOL COOLWnd::IsAlerted() CONST
{
	return m_wndView.IsAlerted();
}

VOID COOLWnd::UpdateBars()
{
	CDisplayLock  cLock(this);

	UpdateMessagePane();
	UpdateModePane();
	UpdateTypePane();
}

BOOL COOLWnd::ProcessRealtimeData()
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

BOOL COOLWnd::StartRetrieveData(UINT nMode, UINT nSpeed, CONST CTimeSpan &tInterval, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime)
{
	SetRetrieveMode(nMode);
	SetRetrieveSpeed(nSpeed);
	SetRetrieveInterval(tInterval);
	SetRetrieveStartTime(tStartTime);
	SetRetrieveStopTime(tStopTime);
	return StartRetrieveData();
}
BOOL COOLWnd::StartRetrieveData()
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
			ReportEvent(SYSTEM_WARNING_OOL_RETRIEVE_FAILURE);
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
			ReportEvent(SYSTEM_WARNING_OOL_RETRIEVE_FAILURE);
		}
	}
	return FALSE;
}

LONG COOLWnd::IsRetrievingData() CONST
{
	LONG  bFlag;

	InterlockedExchange(&bFlag, m_bRetrieveFlag);
	return((m_cRetrieveThread.IsThreadActive()) ? bFlag : FALSE);
}

BOOL COOLWnd::RetrieveMoreData(UINT nAction)
{
	if (IsRetrievingData())
	{
		if (nAction == OOL_RETRIEVE_STOPPED)
		{
			SetRetrieveMode(GetRetrieveMode() | nAction);
			m_cRetrieveStop.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
		if (nAction == OOL_RETRIEVE_AUTOFORWARD)
		{
			SetRetrieveMode((GetRetrieveMode() & (OOL_RETRIEVE_EXACTTIME | OOL_RETRIEVE_STOPBYTIME | OOL_RETRIEVE_STOPBYEND)) | nAction);
			m_cRetrieveAutoForward.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
		if (nAction == OOL_RETRIEVE_AUTOBACKWARD)
		{
			SetRetrieveMode((GetRetrieveMode() & (OOL_RETRIEVE_EXACTTIME | OOL_RETRIEVE_STOPBYTIME | OOL_RETRIEVE_STOPBYEND)) | nAction);
			m_cRetrieveAutoBackward.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
		if (nAction == OOL_RETRIEVE_MANUALFORWARD)
		{
			SetRetrieveMode((GetRetrieveMode() & (OOL_RETRIEVE_EXACTTIME | OOL_RETRIEVE_STOPBYTIME | OOL_RETRIEVE_STOPBYEND)) | nAction);
			m_cRetrieveManualForward.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
		if (nAction == OOL_RETRIEVE_MANUALBACKWARD)
		{
			SetRetrieveMode((GetRetrieveMode() & (OOL_RETRIEVE_EXACTTIME | OOL_RETRIEVE_STOPBYTIME | OOL_RETRIEVE_STOPBYEND)) | nAction);
			m_cRetrieveManualBackward.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
		if (nAction == OOL_RETRIEVE_PSEUDOREALTIME)
		{
			SetRetrieveMode((GetRetrieveMode() & (OOL_RETRIEVE_EXACTTIME | OOL_RETRIEVE_STOPBYTIME | OOL_RETRIEVE_STOPBYEND)) | nAction);
			m_cRetrievePseudoRealtime.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
	}
	return FALSE;
}

BOOL COOLWnd::StopRetrieveData()
{
	return(((IsRetrievingData() && m_cRetrieveThread.Stop()) || !IsRetrievingData()) ? TRUE : FALSE);
}

BOOL COOLWnd::SetRetrieveMode(UINT nMode)
{
	CDisplayLock  cLock(this);

	m_nRetrieveMode = nMode;
	m_bRetrieveFlag = MAKELONG((nMode) ? LOWORD(m_bRetrieveFlag) : FALSE, (nMode) ? HIWORD(m_bRetrieveFlag) : FALSE);
	return TRUE;
}

BOOL COOLWnd::GetRetrieveMode(UINT &nMode) CONST
{
	nMode = m_nRetrieveMode;
	return TRUE;
}
UINT COOLWnd::GetRetrieveMode() CONST
{
	return m_nRetrieveMode;
}

BOOL COOLWnd::SetRetrieveSpeed(UINT nSpeed)
{
	m_nRetrieveSpeed = nSpeed;
	return TRUE;
}

BOOL COOLWnd::GetRetrieveSpeed(UINT &nSpeed) CONST
{
	nSpeed = m_nRetrieveSpeed;
	return TRUE;
}
UINT COOLWnd::GetRetrieveSpeed() CONST
{
	return m_nRetrieveSpeed;
}

BOOL COOLWnd::SetRetrieveInterval(CONST CTimeSpan &tInterval)
{
	CDisplayLock  cLock(this);

	m_tRetrieveInterval = tInterval;
	return TRUE;
}

BOOL COOLWnd::GetRetrieveInterval(CTimeSpan &tInterval) CONST
{
	CDisplayLock  cLock(this);

	tInterval = m_tRetrieveInterval;
	return TRUE;
}
CTimeSpan COOLWnd::GetRetrieveInterval() CONST
{
	CDisplayLock  cLock(this);

	return m_tRetrieveInterval;
}

BOOL COOLWnd::SetRetrieveStartTime(CONST CTimeKey &tStartTime)
{
	CDisplayLock  cLock(this);

	m_tRetrieveStartTime = tStartTime;
	return TRUE;
}

BOOL COOLWnd::GetRetrieveStartTime(CTimeKey &tStartTime) CONST
{
	CDisplayLock  cLock(this);

	tStartTime = m_tRetrieveStartTime;
	return TRUE;
}
CTimeKey COOLWnd::GetRetrieveStartTime() CONST
{
	CDisplayLock  cLock(this);

	return m_tRetrieveStartTime;
}

BOOL COOLWnd::SetRetrieveStopTime(CONST CTimeKey &tStopTime)
{
	CDisplayLock  cLock(this);

	m_tRetrieveStopTime = tStopTime;
	return TRUE;
}

BOOL COOLWnd::GetRetrieveStopTime(CTimeKey &tStopTime) CONST
{
	CDisplayLock  cLock(this);

	tStopTime = m_tRetrieveStopTime;
	return TRUE;
}
CTimeKey COOLWnd::GetRetrieveStopTime() CONST
{
	CDisplayLock  cLock(this);

	return m_tRetrieveStopTime;
}

BOOL COOLWnd::SetRetrieveFileName(LPCTSTR pszFileName)
{
	CDisplayLock  cLock(this);

	m_szRetrieveFileName = pszFileName;
	return TRUE;
}

BOOL COOLWnd::GetRetrieveFileName(CString &szFileName) CONST
{
	CDisplayLock  cLock(this);

	szFileName = GetRetrieveFileName();
	return TRUE;
}
CString COOLWnd::GetRetrieveFileName() CONST
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

VOID COOLWnd::ShowSearchParameterIDDetails()
{
	ReportEvent((!m_dlgSearchID.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

VOID COOLWnd::ShowSearchParameterDescriptionDetails()
{
	ReportEvent((!m_dlgSearchDescription.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

VOID COOLWnd::ShowSearchParameterValueDetails()
{
	ReportEvent((!m_dlgSearchValue.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

VOID COOLWnd::ShowSearchParameterLimitDetails()
{
	ReportEvent((!m_dlgSearchLimit.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

VOID COOLWnd::ShowSearchParameterUnitDetails()
{
	ReportEvent((!m_dlgSearchUnit.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

VOID COOLWnd::ShowSearchParameterOolTypeDetails()
{
	ReportEvent((!m_dlgSearchOolType.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

VOID COOLWnd::ShowSearchParameterOolUnitDetails()
{
	ReportEvent((!m_dlgSearchOolUnit.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

VOID COOLWnd::ShowSearchParameterOolTimeDetails()
{
	ReportEvent((!m_dlgSearchOolTime.Create(this)) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

BOOL COOLWnd::SearchParameterByID(LPCTSTR pszID, BOOL bDown, BOOL bAll)
{
	return m_wndView.SearchParameterByID(pszID, bDown, bAll);
}

BOOL COOLWnd::SearchParameterByDescription(LPCTSTR pszDescription, BOOL bDown, BOOL bAll, BOOL bCase, BOOL bWord)
{
	return m_wndView.SearchParameterByDescription(pszDescription, bDown, bAll, bCase, bWord);
}

BOOL COOLWnd::SearchParameterByValue(LPCTSTR pszValue, BOOL bDown, BOOL bAll, BOOL bCase)
{
	return m_wndView.SearchParameterByValue(pszValue, bDown, bAll, bCase);
}

BOOL COOLWnd::SearchParameterByLimit(LPCTSTR pszLimit, BOOL bDown, BOOL bAll)
{
	return m_wndView.SearchParameterByLimit(pszLimit, bDown, bAll);
}

BOOL COOLWnd::SearchParameterByUnit(LPCTSTR pszUnit, BOOL bDown, BOOL bAll, BOOL bCase)
{
	return m_wndView.SearchParameterByUnit(pszUnit, bDown, bAll, bCase);
}

BOOL COOLWnd::SearchParameterByOolType(LPCTSTR pszOolType, BOOL bDown, BOOL bAll)
{
	return m_wndView.SearchParameterByOolType(pszOolType, bDown, bAll);
}

BOOL COOLWnd::SearchParameterByOolUnit(LPCTSTR pszOolUnit, BOOL bDown, BOOL bAll)
{
	return m_wndView.SearchParameterByOolUnit(pszOolUnit, bDown, bAll);
}

BOOL COOLWnd::SearchParameterByOolTime(CONST CTimeKey &tOolTime, BOOL bDown, BOOL bAll, BOOL bMatch)
{
	return m_wndView.SearchParameterByOolTime(tOolTime, bDown, bAll, bMatch);
}

BOOL COOLWnd::SetParameterAlerts(CONST COolParameters &pOolParameters, CEventList &pOolAuditions)
{
	return m_wndView.SetParameterAlerts(pOolParameters, pOolAuditions);
}

BOOL COOLWnd::GetParameterAlerts(COolParameters &pOolParameters, CEventList &pOolAuditions) CONST
{
	return m_wndView.GetParameterAlerts(pOolParameters, pOolAuditions);
}

VOID COOLWnd::SetParameterInfo(LPCTSTR pszTag)
{
	ReportEvent((m_dlgParameters.Create(this, pszTag) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

BOOL COOLWnd::GetParameterInfo(LPCTSTR pszTag, COolParameter *pOolParameter) CONST
{
	return m_wndView.GetParameterInfo(pszTag, pOolParameter);
}
BOOL COOLWnd::GetParameterInfo(COolParameter *pOolParameter) CONST
{
	return m_wndView.GetParameterInfo(pOolParameter);
}

INT COOLWnd::GetParameters(COolParameters &pOolParameters) CONST
{
	return m_wndView.GetParameters(pOolParameters);
}

INT COOLWnd::GetParametersCount() CONST
{
	return m_wndView.GetParametersCount();
}

BOOL COOLWnd::HasParameters() CONST
{
	return m_wndView.HasParameters();
}

BOOL COOLWnd::SetPrintJobs(CONST COOLPrintJobs &pPrintJobs)
{
	return m_cPrintThread.SetPrintJobs(pPrintJobs);
}

BOOL COOLWnd::GetPrintJobs(COOLPrintJobs &pPrintJobs) CONST
{
	return m_cPrintThread.GetPrintJobs(pPrintJobs);
}

BOOL COOLWnd::Print(CONST COOLPrintJobInfo *pJobInfo, PRINTDLG *pPrintInfo)
{
	CDC  cDC;
	INT  nCount;
	UINT  nMode;
	UINT  nTMUnit;
	BOOL  bMetric;
	BOOL  bQuality;
	RECT  rtMargin[2];
	SIZE  ptPaperSize;
	CTimeTag  tTMUnit;
	CString  szTMUnit;
	CString  szLayout;
	LOGFONT  lfFont[2];
	DEVMODE  *pDevMode;
	DEVNAMES  *pDevNames;
	CUIntArray  nOOLColors;
	CStringArray  szColumns;
	CStringArray  szContents;
	CPrintProfiles  cPrintProfiles;
	CPrintProfileInfo  *pPrintProfileInfo;
	CTextViewAttributes  pAttributes;

	if ((pPrintProfileInfo = (GetPrintProfiles(cPrintProfiles)) ? cPrintProfiles.GetAt(cPrintProfiles.Find(pJobInfo->GetProfile())) : (CPrintProfileInfo *)NULL) && pPrintProfileInfo->GetPaperInfo(ptPaperSize, rtMargin[0], rtMargin[1], bMetric))
	{
		if (GetLayout(szLayout) && GetPrintProperties(pJobInfo, nMode, szTMUnit, tTMUnit, nTMUnit, bQuality, szColumns, szContents, pAttributes, nCount, nOOLColors, &lfFont[0], &lfFont[1]))
		{
			if (pPrintInfo == (PRINTDLG *)NULL)
			{
				if (CreatePrinterDC(pPrintProfileInfo, cDC))
				{
					if (PrintJob(cDC, pJobInfo, pPrintProfileInfo->GetPrinterName(), 0, 0, rtMargin[0], bMetric, szLayout, nMode, szTMUnit, tTMUnit, nTMUnit, bQuality, szColumns, szContents, pAttributes, nCount, nOOLColors, &lfFont[0], &lfFont[1]))
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
						if (PrintJob(cDC, pJobInfo, (LPCTSTR)pDevMode->dmDeviceName, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nFromPage : 0, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nToPage : 0, rtMargin[0], bMetric, szLayout, nMode, szTMUnit, tTMUnit, nTMUnit, bQuality, szColumns, szContents, pAttributes, nCount, nOOLColors, &lfFont[0], &lfFont[1]))
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

COOLWnd *COOLWnd::Find(INT nType, UINT nMode, LPCTSTR pszName) CONST
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szLayout;
	COOLWnd  *pOOLWnd;
	CDisplayWnd  *pDisplayWnd;
	CPtrArray  pDisplays;

	for (nDisplay = 0, nDisplays = GetDisplayArea()->EnumDisplays(pDisplays), pOOLWnd = (COOLWnd *)NULL; nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_OOL  &&  HIWORD(pDisplayWnd->GetType()) == HIWORD(nType) && pDisplayWnd->GetMode() == nMode)
		{
			if ((pOOLWnd = (COOLWnd *)pDisplayWnd)->GetLayout(szLayout) && szLayout == pszName) break;
			continue;
		}
	}
	return((nDisplay < nDisplays) ? pOOLWnd : (COOLWnd *)NULL);
}

VOID COOLWnd::SetUpdateInfo()
{
	CDisplayLock  cLock(this);

	m_szTMUnit.Empty();
	m_tTMUnit = 0;
	m_nTMUnit = 0;
	m_wTMUnit = TMUNIT_DATAQUALITY_NONE;
	UpdateMessagePane();
}
VOID COOLWnd::SetUpdateInfo(LPCTSTR pszTag, CONST CTimeTag &tTag, UINT nTag, WORD wQuality)
{
	CDisplayLock  cLock(this);

	m_szTMUnit = pszTag;
	m_tTMUnit = tTag;
	m_nTMUnit = nTag;
	m_wTMUnit = wQuality;
	UpdateMessagePane();
}

BOOL COOLWnd::GetUpdateInfo(CString &szTag, CTimeTag &tTag, UINT &nTag, WORD &wQuality) CONST
{
	CDisplayLock  cLock(this);

	szTag = m_szTMUnit;
	tTag = m_tTMUnit;
	nTag = m_nTMUnit;
	wQuality = m_wTMUnit;
	return TRUE;
}

BOOL COOLWnd::CreateToolBar()
{
	if (m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE) && m_wndToolBar.LoadToolBar(IDB_OOLFRAMELARGEIMAGES, 0, IDB_OOLFRAMESMALLIMAGES, TRUE))
	{
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_OOLSETTINGS), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_OOLLINKAGES), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_OOLPARAMETERS), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_OOLACKNOWLEDGE), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_OOLRETRIEVALS), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_OOLRETRIEVESTOP), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_OOLRETRIEVESTEPFORWARD), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_OOLRETRIEVESTEPBACKWARD), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_OOLRETRIEVEFORWARD), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_OOLRETRIEVEBACKWARD), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_OOLRETRIEVEPSEUDOREALTIME), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_OOLPRINT), TBBS_DISABLED);
		DockPane(&m_wndToolBar);
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

BOOL COOLWnd::CreateStatusBar()
{
	if (m_wndStatusBar.Create(this, CBRS_BOTTOM | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE) && m_wndStatusBar.SetIndicators(nOOLStatusBarIndicators, 1))
	{
		m_wndStatusBar.EnableToolTips();
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

BOOL COOLWnd::CreateView()
{
	if (m_wndView.Create(this, TVS_HEADER | TVS_TOP | TVS_BUTTONS | TVS_HSCROLL | TVS_VSCROLL | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE))
	{
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

BOOL COOLWnd::Customize(BOOL bDefault)
{
	CString  szName;
	LOGFONT  sFontInfo[2];
	CUIntArray  nColumns;
	CUIntArray  nWidths;

	return(((!bDefault &&  GetLayout(szName, nColumns, nWidths) && GetTitleFont(&sFontInfo[0]) && GetItemsFont(&sFontInfo[1]) && (SetLayout((szName = (HIWORD(GetType()) == OOL_TYPE_GLOBAL) ? STRING(IDS_DISPLAY_TITLE_GLOBALOOL) : (LPCTSTR)szName), nColumns, nWidths) || SetLayout(szName)) && SetTitleFont(&sFontInfo[0]) && SetItemsFont(&sFontInfo[1])) || (bDefault  &&  GetLayout(szName) && SetLayout(szName))) ? TRUE : FALSE);
}

BOOL COOLWnd::UpdateAllPanes()
{
	INT  nPane;
	INT  nPanes;

	for (nPane = 0, nPanes = sizeof(nOOLStatusBarIndicators) / sizeof(UINT); nPane < nPanes; nPane++)
	{
		if (m_wndStatusBar.CommandToIndex(nOOLStatusBarIndicators[nPane]) != nPane) break;
		continue;
	}
	if (nPane < nPanes)
	{
		if (m_wndStatusBar.SetIndicators(nOOLStatusBarIndicators, sizeof(nOOLStatusBarIndicators) / sizeof(UINT)))
		{
			UpdateBars();
			return TRUE;
		}
		return FALSE;
	}
	UpdateBars();
	return TRUE;
}

VOID COOLWnd::UpdateMessagePane()
{
	UINT  nTag;
	UINT  nCount;
	WORD  wQuality;
	CTimeTag  tTag;
	CString  szTag;
	CString  szMessage[2];

	if (GetUpdateInfo(szTag, tTag, nTag, wQuality))
	{
		szMessage[0].Format((szTag.IsEmpty()) ? ((tTag > 0) ? STRING(IDS_OOL_STATUSBAR_FULLUPDATEMESSAGE) : ((IsRetrievingData() && HIWORD(IsRetrievingData())) ? STRING(IDS_OOL_STATUSBAR_RETRIEVEMESSAGE) : STRING(IDS_OOL_STATUSBAR_NODATAMESSAGE))) : ((nTag == (UINT)-1) ? STRING(IDS_OOL_STATUSBAR_INITUPDATEMESSAGE) : STRING(IDS_OOL_STATUSBAR_UPDATEMESSAGE)), (LPCTSTR)tTag.FormatGmt(), (LPCTSTR)szTag, nTag, ((wQuality & (TMUNIT_DATAQUALITY_GOOD | TMUNIT_SEQUENCEQUALITY_GOOD)) == (TMUNIT_DATAQUALITY_GOOD | TMUNIT_SEQUENCEQUALITY_GOOD)) ? ((wQuality & TMUNIT_TIMECORRELATION_BAD) ? (LPCTSTR)(CString(STRING(IDS_OOL_STATUSBAR_QUALITYGOOD)) + STRING(IDS_OOL_STATUSBAR_TIMECORRELATIONFLAG)) : STRING(IDS_OOL_STATUSBAR_QUALITYGOOD)) : ((wQuality & TMUNIT_TIMECORRELATION_BAD) ? (LPCTSTR)(CString(STRING(IDS_OOL_STATUSBAR_QUALITYBAD)) + STRING(IDS_OOL_STATUSBAR_TIMECORRELATIONFLAG)) : STRING(IDS_OOL_STATUSBAR_QUALITYBAD)));
		szMessage[1].Format(((nCount = GetParametersCount()) != 1) ? STRING(IDS_OOL_STATUSBAR_OOLENTRIES) : STRING(IDS_OOL_STATUSBAR_OOLENTRY), nCount);
		m_wndStatusBar.SetPaneText(ID_OOL_STATUSBAR_MESSAGEPANE, (szMessage[0] != STRING(IDS_OOL_STATUSBAR_NODATAMESSAGE) && szMessage[0] != STRING(IDS_OOL_STATUSBAR_RETRIEVEMESSAGE)) ? (szMessage[0] + szMessage[1]) : szMessage[0]);
	}
	m_wndToolBar.EnableButton(IDM_OOLACKNOWLEDGE, (IsInitialized() && IsAlerted()) ? TRUE : FALSE);
}

VOID COOLWnd::UpdateModePane()
{
	CString  szMode;
	CString  szLayout;
	CDisplayWnd  *pDisplayWnd;

	for (szMode.Empty(); (pDisplayWnd = (CDisplayWnd *)GetLink()) && GetLayout(szLayout); )
	{
		szMode.Format(STRING(IDS_DISPLAY_MODE_LINK), STRING(IDS_DISPLAY_TITLE_OOL), (LPCTSTR)szLayout);
		break;
	}
	m_wndStatusBar.SetPaneText(ID_OOL_STATUSBAR_MODEPANE, (GetMode() == DISPLAY_MODE_HISTORY) ? (((GetRetrieveMode() & OOL_RETRIEVE_AUTOFORWARD) && !(GetRetrieveMode() & OOL_RETRIEVE_STOPPED)) ? STRING(IDS_OOL_STATUSBAR_AUTOFORWARDMODE) : (((GetRetrieveMode() & OOL_RETRIEVE_AUTOBACKWARD) && !(GetRetrieveMode() & OOL_RETRIEVE_STOPPED)) ? STRING(IDS_OOL_STATUSBAR_AUTOBACKWARDMODE) : (((GetRetrieveMode() & OOL_RETRIEVE_PSEUDOREALTIME) && !(GetRetrieveMode() & OOL_RETRIEVE_STOPPED)) ? STRING(IDS_OOL_STATUSBAR_PSEUDOREALTIMEMODE) : ((!szMode.IsEmpty()) ? (STRING(IDS_OOL_STATUSBAR_NORMALMODE) + szMode) : STRING(IDS_OOL_STATUSBAR_NORMALMODE))))) : ((!szMode.IsEmpty()) ? (STRING(IDS_DISPLAY_MODE_REALTIME) + szMode) : STRING(IDS_DISPLAY_MODE_REALTIME)));
	m_wndToolBar.EnableButton(IDM_OOLRETRIEVESTOP, (IsRetrievingData() && ((GetRetrieveMode() & OOL_RETRIEVE_AUTOFORWARD) || (GetRetrieveMode() & OOL_RETRIEVE_AUTOBACKWARD) || (GetRetrieveMode() & OOL_RETRIEVE_PSEUDOREALTIME) || HIWORD(IsRetrievingData())) && !(GetRetrieveMode() & OOL_RETRIEVE_STOPPED)) ? TRUE : FALSE);
	m_wndToolBar.EnableButton(IDM_OOLRETRIEVEFORWARD, (IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & OOL_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & OOL_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & OOL_RETRIEVE_STOPPED))) ? TRUE : FALSE);
	m_wndToolBar.EnableButton(IDM_OOLRETRIEVEBACKWARD, (IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & OOL_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & OOL_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & OOL_RETRIEVE_STOPPED))) ? TRUE : FALSE);
	m_wndToolBar.EnableButton(IDM_OOLRETRIEVESTEPFORWARD, (IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & OOL_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & OOL_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & OOL_RETRIEVE_STOPPED))) ? TRUE : FALSE);
	m_wndToolBar.EnableButton(IDM_OOLRETRIEVESTEPBACKWARD, (IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & OOL_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & OOL_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & OOL_RETRIEVE_STOPPED))) ? TRUE : FALSE);
	m_wndToolBar.EnableButton(IDM_OOLRETRIEVEPSEUDOREALTIME, (IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & OOL_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & OOL_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & OOL_RETRIEVE_STOPPED))) ? TRUE : FALSE);
}

VOID COOLWnd::UpdateTypePane()
{
	CString  szType;

	switch (HIWORD(GetType()))
	{
	case OOL_TYPE_GLOBAL:
	{ szType = STRING(IDS_OOL_STATUSBAR_TYPEGLOBAL);
	break;
	}
	case OOL_TYPE_NORMAL:
	{ szType = STRING(IDS_OOL_STATUSBAR_TYPENORMAL);
	break;
	}
	}
	m_wndStatusBar.SetPaneText(ID_OOL_STATUSBAR_TYPEPANE, szType);
}

VOID COOLWnd::UpdateData()
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

BOOL COOLWnd::StartSchedulePrintJobs()
{
	return IsSchedulingPrintJobs() || m_cPrintThread.Start(this);
}

BOOL COOLWnd::IsSchedulingPrintJobs() CONST
{
	return((m_cPrintThread.IsThreadActive()) ? TRUE : FALSE);
}

BOOL COOLWnd::StopSchedulePrintJobs()
{
	return((IsSchedulingPrintJobs() && m_cPrintThread.Stop()) ? TRUE : FALSE);
}

BOOL COOLWnd::SetParameterFilters(CONST CByteArray &nFilterInfo)
{
	COOLParameterFilters  pParameterFilters;

	return((pParameterFilters.Unmap(nFilterInfo)) ? SetParameterFilters(pParameterFilters) : FALSE);
}

BOOL COOLWnd::GetParameterFilters(CByteArray &nFilterInfo) CONST
{
	COOLParameterFilters  pParameterFilters;

	return((GetParameterFilters(pParameterFilters)) ? pParameterFilters.Map(nFilterInfo) : FALSE);
}

BOOL COOLWnd::SetPrintJobs(CONST CByteArray &nPrintInfo)
{
	COOLPrintJobs  pPrintJobs;

	return((pPrintJobs.Unmap(nPrintInfo)) ? SetPrintJobs(pPrintJobs) : FALSE);
}

BOOL COOLWnd::GetPrintJobs(CByteArray &nPrintInfo) CONST
{
	COOLPrintJobs  pPrintJobs;

	return((GetPrintJobs(pPrintJobs)) ? pPrintJobs.Map(nPrintInfo) : FALSE);
}

BOOL COOLWnd::GetPrintProperties(CONST COOLPrintJobInfo *pJobInfo, UINT &nMode, CString &szTMUnit, CTimeTag &tTMUnit, UINT &nTMUnit, BOOL &bQuality, CStringArray &szColumns, CStringArray &szContents, CTextViewAttributes &pAttributes, INT &nOOLCount, CUIntArray &nOOLColors, LOGFONT *pTitleFont, LOGFONT *pItemsFont) CONST
{
	INT  nCount;
	INT  nParameter;
	INT  nParameters;
	UINT  nPrintMode;
	UINT  nPrintCount;
	WORD  wPrintQuality;
	CTimeKey  tPrintStopTime;
	CTimeKey  tPrintStartTime;
	COolParameters  pOolParameters;
	CDisplayLock  cLock(this);

	if (((nMode = GetMode()) == DISPLAY_MODE_REALTIME || nMode == DISPLAY_MODE_HISTORY) && GetUpdateInfo(szTMUnit, tTMUnit, nTMUnit, wPrintQuality) && m_wndView.GetPrintProperties(szColumns, szContents, pAttributes, pOolParameters, pTitleFont, pItemsFont) && GetFilterColors(nOOLColors))
	{
		for (nOOLCount = (INT)pOolParameters.GetSize(); pJobInfo->GetPrintBySide(nPrintCount); )
		{
			if ((nPrintMode = pJobInfo->GetPrintMode()) & OOL_PRINT_FIRSTSIDE)
			{
				nCount = (INT)(szContents.GetSize() - nPrintCount);
				szContents.RemoveAt((nCount > 0) ? nPrintCount : 0, max(nCount, 0));
			}
			if (nPrintMode & OOL_PRINT_LASTSIDE)
			{
				nCount = (INT)(szContents.GetSize() - nPrintCount);
				szContents.RemoveAt(0, max(nCount, 0));
			}
			break;
		}
		if (pJobInfo->GetPrintByTime(tPrintStartTime, tPrintStopTime))
		{
			for (nParameter = 0, nParameters = (szContents.GetSize() == pOolParameters.GetSize() && pAttributes.GetSize() == pOolParameters.GetSize()) ? (INT)pOolParameters.GetSize() : 0; nParameter < nParameters; nParameter++)
			{
				if (tPrintStartTime > pOolParameters.GetAt(nParameter)->GetOolTime().GetTimeInSeconds() || tPrintStopTime < pOolParameters.GetAt(nParameter)->GetOolTime().GetTimeInSeconds())
				{
					delete pOolParameters.GetAt(nParameter);
					delete pAttributes.GetAt(nParameter);
					pOolParameters.RemoveAt(nParameter);
					pAttributes.RemoveAt(nParameter);
					szContents.RemoveAt(nParameter);
					nParameters--;
					nParameter--;
				}
			}
		}
		bQuality = ((wPrintQuality & (TMUNIT_DATAQUALITY_GOOD | TMUNIT_SEQUENCEQUALITY_GOOD)) == (TMUNIT_DATAQUALITY_GOOD | TMUNIT_SEQUENCEQUALITY_GOOD)) ? TRUE : FALSE;
		return TRUE;
	}
	return FALSE;
}

BOOL COOLWnd::StartPrintJob(CDC &cDC)
{
	DOCINFO  sJobInfo;
	CString  szLayout;
	CString  szJobTitle;

	for (GetLayout(szLayout), sJobInfo.fwType = 0, sJobInfo.cbSize = sizeof(DOCINFO), sJobInfo.lpszDocName = (LPTSTR)EMPTYSTRING, sJobInfo.lpszOutput = (LPCTSTR)NULL, sJobInfo.lpszDatatype = (LPCTSTR)NULL, szJobTitle.Format(STRING(IDS_PRINTJOB_DEFAULTTITLE), (LPCTSTR)GetAppTitle(), (LPCTSTR)GetAccountSpacecraftName(), (LPCTSTR)GetPrintDocSubTitle(szLayout), STRING(IDS_DISPLAY_TITLE_OOL)); szJobTitle.GetLength() >= 0; )
	{
		sJobInfo.lpszDocName = (LPTSTR)(LPCTSTR)szJobTitle;
		break;
	}
	return((cDC.StartDoc(&sJobInfo) >= 0) ? TRUE : FALSE);
}

BOOL COOLWnd::PrintJob(CDC &cDC, CONST COOLPrintJobInfo *pJobInfo, LPCTSTR pszPrinterName, INT nFromPage, INT nToPage, CONST RECT &rtMargin, BOOL bMetric, LPCTSTR pszLayout, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality, CONST CStringArray &szColumns, CONST CStringArray &szContents, CONST CTextViewAttributes &pAttributes, INT nOOLCount, CONST CUIntArray &nOOLColors, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont)
{
	INT  nPage;
	INT  nPages;
	INT  nLine;
	INT  nLines;
	INT  nColumn;
	INT  nColumns;
	INT  nFont;
	INT  nFonts;
	INT  nSpacing;
	INT  nHeight[2];
	BOOL  bOverlap;
	BOOL  bOutput;
	CRgn  rgnArea;
	CRect  rArea;
	CRect  rCalc;
	CRect  rClip;
	CRect  rItem;
	CFont  *pOldFont;
	CFont  cFont[OOL_PRINTFONTS];
	CSize  sizeText[2];
	CString  szColumn;
	COLORREF  nColor;
	COLORREF  nOldColor;
	CTimeKey  tPrint;
	CPtrArray  pFonts;
	CUIntArray  nTabs;
	TEXTMETRIC  tmFont;
	CStringArray  szColumnsText;
	CTextViewAttribute  *pAttribute;

	for (nPage = nPages = 0; (!nPages || nPage <= nPages) && (nPages > 0 || (nPages = (CalcPrintDocRect(cDC, rtMargin, bMetric) && cDC.GetClipBox(rArea) != ERROR && rgnArea.CreateRectRgnIndirect(rArea) && CalcPrintDocTitleFont(cDC, rArea, cFont[OOL_PRINTFONT_TITLE]) && CalcPrintDocSubTitleFont(cDC, rArea, cFont[OOL_PRINTFONT_SUBTITLE]) && CalcPrintDocOperatingDetailsFont(cDC, rArea, cFont[OOL_PRINTFONT_OPERATINGDETAILS]) && CalcPrintDocOperatingModeFont(cDC, rArea, cFont[OOL_PRINTFONT_OPERATINGMODE]) && CalcPrintDocListItemsFonts(cDC, rArea, szColumns, szContents, pTitleFont, pItemsFont, cFont[OOL_PRINTFONT_LISTITEMSTITLE], cFont[OOL_PRINTFONT_LISTITEMS]) && CalcPrintDocNoticeFonts(cDC, rArea, cFont[OOL_PRINTFONT_NOTICE], cFont[OOL_PRINTFONT_LOGO]) && CalcPrintDocFooterFont(cDC, rArea, cFont[OOL_PRINTFONT_FOOTER]) && CalcPrintDocTitleWidth(cDC, szColumns, szContents, &cFont[OOL_PRINTFONT_LISTITEMSTITLE], &cFont[OOL_PRINTFONT_LISTITEMS], nTabs) == szColumns.GetSize()) ? nPages : -1) == 0); )
	{
		for (nFont = 0, nFonts = (!nPages) ? (INT)(sizeof(cFont) / sizeof(cFont[0])) : 0; nFont < nFonts; nFont++)
		{
			pFonts.SetAtGrow(nFont, &cFont[nFont]);
			continue;
		}
		for (nLine = 0, nLines = (INT)szContents.GetSize(), nSpacing = 0, rCalc.SetRectEmpty(), rClip.SetRectEmpty(), bOverlap = FALSE, bOutput = TRUE; nPages >= 0 && nLine < nLines; nLine++, bOutput = TRUE)
		{
			for (nColumn = 0, nColumns = (INT)szColumns.GetSize(), ExtractPrintDocText(szContents.GetAt(nLine), szColumnsText), nHeight[0] = nHeight[1] = 0; nPages >= 0 && nColumn < nColumns; nColumn++, nHeight[1] = 0)
			{
				if (rClip.Height() > 0)
				{
					if ((pOldFont = cDC.SelectObject((CFont *)pFonts.GetAt(OOL_PRINTFONT_LISTITEMS))))
					{
						if ((nSpacing = (cDC.GetTextMetrics(&tmFont)) ? max(tmFont.tmHeight / 10, 1) : -1) >= 0)
						{
							nColor = (!(pAttribute = pAttributes.GetAt(nLine)) || !pAttribute->GetColumnColor(nColumn, nColor)) ? cDC.GetTextColor() : nColor;
							nOldColor = cDC.SetTextColor((cDC.GetDeviceCaps(NUMCOLORS) > 2) ? nColor : cDC.GetTextColor());
							sizeText[0] = (nColumn < szColumnsText.GetSize()) ? cDC.GetTextExtent((szColumn = szColumnsText.GetAt(nColumn) + SPACE)) : cDC.GetTextExtent((szColumn = EMPTYSTRING) + SPACE);
							sizeText[1] = (nColumn < szColumnsText.GetSize()) ? cDC.GetTextExtent(szColumnsText.GetAt(nColumn)) : cDC.GetTextExtent(EMPTYSTRING);
							rCalc.SetRect(rCalc.left, (!nColumn) ? (rCalc.top + nSpacing) : rCalc.top, rCalc.right, (!nColumn) ? (rCalc.top + nSpacing + tmFont.tmHeight*((rClip.bottom - (rCalc.top + nSpacing)) / tmFont.tmHeight)) : (rCalc.top + tmFont.tmHeight*((rClip.bottom - rCalc.top) / tmFont.tmHeight)));
							rItem.SetRect((nColumn > 0) ? (rCalc.left + nTabs.GetAt(nColumn - 1)) : rCalc.left, rCalc.top, rCalc.left + nTabs.GetAt(nColumn), rCalc.top + sizeText[0].cy);
							cDC.DrawText(szColumn, (nPages > 0 && (nFromPage <= 0 || nToPage <= 0 || nFromPage > nToPage || (nPage >= nFromPage  &&  nPage <= nToPage))) ? CRect(rItem.left, rItem.top, rItem.right, rCalc.bottom) : CRect(0, 0, 0, 0), DT_LEFT | DT_NOPREFIX | DT_SINGLELINE);
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
						if (cDC.SelectClipRgn(&rgnArea) != ERROR  &&  DrawPrintDocPage(cDC, pJobInfo, tPrint, pszPrinterName, rtMargin, bMetric, pszLayout, nMode, pszTMUnit, tTMUnit, nTMUnit, bQuality, szColumns, nOOLCount, nOOLColors, pFonts, nTabs, nPages, (nPages > 0 && (nFromPage <= 0 || nToPage <= 0 || nFromPage > nToPage || (nPage >= nFromPage - 1 && nPage < nToPage))) ? (nPage + 1) : 0, rClip) && cDC.IntersectClipRect(rClip) != ERROR)
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
							if (DrawPrintDocPage(cDC, pJobInfo, tPrint, pszPrinterName, rtMargin, bMetric, pszLayout, nMode, pszTMUnit, tTMUnit, nTMUnit, bQuality, szColumns, nOOLCount, nOOLColors, pFonts, nTabs, 1, 1, rClip))
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

BOOL COOLWnd::EndPrintJob(CDC &cDC)
{
	return((cDC.EndDoc() >= 0) ? TRUE : FALSE);
}

BOOL COOLWnd::DrawPrintDocPage(CDC &cDC, CONST COOLPrintJobInfo *pJobInfo, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, CONST RECT &rtMargin, BOOL bMetric, LPCTSTR pszLayout, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality, CONST CStringArray &szColumns, INT nOOLCount, CONST CUIntArray &nOOLColors, CONST CPtrArray &pFonts, CONST CUIntArray &nTabs, INT nPages, INT nPage, LPRECT prClip)
{
	return((CalcPrintDocRect(cDC, rtMargin, bMetric) && cDC.GetClipBox(prClip) != ERROR  &&  DrawPrintDocTitle(cDC, prClip, GetPrintDocTitle(), (CFont *)pFonts.GetAt(OOL_PRINTFONT_TITLE), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocSubTitle(cDC, prClip, GetPrintDocSubTitle(pszLayout), (CFont *)pFonts.GetAt(OOL_PRINTFONT_SUBTITLE), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocOperatingDetails(cDC, prClip, GetPrintDocOperatingDetails(pJobInfo, nMode, pszTMUnit, tTMUnit, nTMUnit, bQuality), (CFont *)pFonts.GetAt(OOL_PRINTFONT_OPERATINGDETAILS), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocOperatingMode(cDC, prClip, GetPrintDocOperatingMode(pJobInfo, nOOLCount, nOOLColors), nOOLColors, (CFont *)pFonts.GetAt(OOL_PRINTFONT_OPERATINGMODE), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocListItemsTitle(cDC, prClip, szColumns, (CFont *)pFonts.GetAt(OOL_PRINTFONT_LISTITEMSTITLE), nTabs, (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocNotice(cDC, prClip, GetPrintDocNotice(), (CFont *)pFonts.GetAt(OOL_PRINTFONT_NOTICE), (CFont *)pFonts.GetAt(OOL_PRINTFONT_LOGO), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocFooter(cDC, prClip, GetPrintDocFooter(tTime, pszPrinterName, nPages, nPage), (CFont *)pFonts.GetAt(OOL_PRINTFONT_FOOTER), (nPage <= 0) ? TRUE : FALSE)) ? TRUE : FALSE);
}

BOOL COOLWnd::DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc)
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

BOOL COOLWnd::DrawPrintDocSubTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszLayout, CFont *pFont, BOOL bCalc)
{
	CRect  rCalc;
	CFont  *pOldFont;

	if ((pOldFont = cDC.SelectObject(pFont)))
	{
		cDC.DrawText(pszLayout, (rCalc = CRect(0, 0, prClip->right - prClip->left, 0)), DT_CALCRECT | DT_CENTER | DT_NOPREFIX | DT_SINGLELINE);
		cDC.DrawText(pszLayout, (!bCalc) ? prClip : CRect(0, 0, 0, 0), DT_CENTER | DT_NOPREFIX | DT_SINGLELINE);
		prClip->top += (lstrlen(pszLayout) > 0) ? rCalc.Height() : 0;
		cDC.SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

BOOL COOLWnd::DrawPrintDocOperatingDetails(CDC &cDC, LPRECT prClip, LPCTSTR pszComments, CFont *pFont, BOOL bCalc)
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

BOOL COOLWnd::DrawPrintDocOperatingMode(CDC &cDC, LPRECT prClip, LPCTSTR pszMode, CONST CUIntArray &nOOLColors, CFont *pFont, BOOL bCalc)
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
		szToken = szToken.Left((szToken = STRING(IDS_OOL_PRINTDOCUMENT_OOLLEGEND)).Find(SPACE));
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

BOOL COOLWnd::DrawPrintDocListItemsTitle(CDC &cDC, LPRECT prClip, CONST CStringArray &szColumns, CFont *pFont, CONST CUIntArray &nTabs, BOOL bCalc)
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

BOOL COOLWnd::DrawPrintDocNotice(CDC &cDC, LPRECT prClip, LPCTSTR pszNotice, CFont *pFont, CFont *pLogoFont, BOOL bCalc)
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

BOOL COOLWnd::DrawPrintDocFooter(CDC &cDC, LPRECT prClip, LPCTSTR pszFooter, CFont *pFont, BOOL bCalc)
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

CString COOLWnd::GetPrintDocTitle() CONST
{
	CString  szTitle;

	szTitle.Format(STRING(IDS_OOL_PRINTDOCUMENT_TITLE), (LPCTSTR)GetAccountSpacecraftName());
	return szTitle;
}

CString COOLWnd::GetPrintDocSubTitle(LPCTSTR pszLayout) CONST
{
	return pszLayout;
}

CString COOLWnd::GetPrintDocOperatingDetails(CONST COOLPrintJobInfo *pJobInfo, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality) CONST
{
	CString  szMode;
	CString  szUpdate;

	szMode = (nMode == DISPLAY_MODE_REALTIME) ? STRING(IDS_DISPLAY_MODE_REALTIME) : STRING(IDS_DISPLAY_MODE_HISTORY);
	szUpdate.Format((!lstrlen(pszTMUnit)) ? ((tTMUnit > 0) ? STRING(IDS_OOL_PRINTDOCUMENT_FULLUPDATECOMMENT) : STRING(IDS_OOL_PRINTDOCUMENT_NODATACOMMENT)) : ((nTMUnit == (UINT)-1) ? STRING(IDS_OOL_PRINTDOCUMENT_INITUPDATECOMMENT) : STRING(IDS_OOL_PRINTDOCUMENT_UPDATECOMMENT)), (LPCTSTR)tTMUnit.FormatGmt(), pszTMUnit, nTMUnit, (bQuality) ? STRING(IDS_OOL_PRINTDOCUMENT_QUALITYGOOD) : STRING(IDS_OOL_PRINTDOCUMENT_QUALITYBAD));
	return((!pJobInfo->GetComments().IsEmpty()) ? (szUpdate + EOL + szMode + EOL + pJobInfo->GetComments()) : (szUpdate + EOL + szMode));
}

CString COOLWnd::GetPrintDocOperatingMode(CONST COOLPrintJobInfo *pJobInfo, INT nOOLCount, CONST CUIntArray &nOOLColors) CONST
{
	UINT  nMode;
	UINT  nFlags;
	UINT  nColor;
	UINT  nCount;
	UINT  nStopCount;
	CString  szLegend;
	CString  szFilter;
	CString  szEvent;
	CString  szCount;
	CString  szInfo;
	CString  szSide;
	CTimeKey  tTime;
	CTimeKey  tLastTime;
	CTimeKey  tStopTime;
	CTimeKey  tStartTime;
	CTimeSpan  tInterval;
	CTimeSpan  tDailyTime;
	CStringArray  szOOLColors;

	if ((nFlags = pJobInfo->GetPrintFlags()) & OOL_PRINT_ATTIME)
	{
		if (pJobInfo->GetPrintAtTime(tTime))
		{
			szInfo.Format(STRING(IDS_OOL_PRINTDOCUMENT_PRINTATTIME), (LPCTSTR)tTime.FormatGmt());
			szInfo += EOL;
		}
		if ((pJobInfo->GetPrintAtTime(tTime, tInterval) || pJobInfo->GetPrintAtTime(tTime, tInterval, nStopCount) || pJobInfo->GetPrintAtTime(tTime, tInterval, tStopTime)) && pJobInfo->GetPrintLastTime(tLastTime))
		{
			szInfo.Format(STRING(IDS_OOL_PRINTDOCUMENT_PRINTATTIME), (LPCTSTR)CTimeKey(tTime.GetTime() + ((tLastTime.GetTime() - tTime.GetTime()) / tInterval.GetTotalSeconds())*tInterval.GetTotalSeconds()).FormatGmt());
			szInfo += EOL;
		}
	}
	if (nFlags & OOL_PRINT_ATDAILYTIME)
	{
		if (pJobInfo->GetPrintAtDailyTime(tDailyTime) || pJobInfo->GetPrintAtDailyTime(tDailyTime, nStopCount) || pJobInfo->GetPrintAtDailyTime(tDailyTime, tStopTime))
		{
			szInfo.Format(STRING(IDS_OOL_PRINTDOCUMENT_PRINTATDAILYTIME), (LPCTSTR)CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + tDailyTime.GetTotalSeconds()).FormatGmt(STRING(IDS_TIMEKEY_TIMEFORMAT)));
			szInfo += EOL;
		}
	}
	if (nFlags & OOL_PRINT_ATEVENT)
	{
		if (pJobInfo->GetPrintAtEvent(szEvent))
		{
			szInfo.Format(STRING(IDS_OOL_PRINTDOCUMENT_PRINTATEVENT), (LPCTSTR)szEvent);
			szInfo += EOL;
		}
	}
	if (!nFlags)
	{
		szInfo = STRING(IDS_OOL_PRINTDOCUMENT_DEFAULTTIME);
		szInfo += EOL;
	}
	if (nOOLCount >= 0)
	{
		szCount.Format(STRING(IDS_OOL_PRINTDOCUMENT_PRINTNUMBERTOTAL), nOOLCount);
		szCount = (nOOLCount == 1) ? STRING(IDS_OOL_PRINTDOCUMENT_PRINTSINGLETOTAL) : (LPCTSTR)szCount;
		szInfo += szCount + EOL;
	}
	if ((nMode = pJobInfo->GetPrintMode()) & OOL_PRINT_ALL)
	{
		szInfo += STRING(IDS_OOL_PRINTDOCUMENT_PRINTALL);
		szInfo += EOL;
	}
	if (((nMode & OOL_PRINT_FIRSTSIDE) || (nMode & OOL_PRINT_LASTSIDE)) && pJobInfo->GetPrintBySide(nCount))
	{
		szSide.Format((nMode & OOL_PRINT_FIRSTSIDE) ? STRING(IDS_OOL_PRINTDOCUMENT_PRINTBYFIRSTSIDE) : STRING(IDS_OOL_PRINTDOCUMENT_PRINTBYLASTSIDE), nCount);
		szSide = (nCount == 1) ? ((nMode & OOL_PRINT_FIRSTSIDE) ? STRING(IDS_OOL_PRINTDOCUMENT_PRINTBYFIRSTITEM) : STRING(IDS_OOL_PRINTDOCUMENT_PRINTBYLASTITEM)) : (LPCTSTR)szSide;
		szInfo += szSide + EOL;
	}
	if ((nMode & OOL_PRINT_BYTIME) && pJobInfo->GetPrintByTime(tStartTime, tStopTime))
	{
		szFilter.Format(STRING(IDS_OOL_PRINTDOCUMENT_PRINTBYTIME), (LPCTSTR)tStartTime.FormatGmt(), (LPCTSTR)tStopTime.FormatGmt());
		szInfo += szFilter + EOL;
	}
	if (nMode & OOL_PRINT_COLORLEGEND)
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
		szLegend.Format(STRING(IDS_OOL_PRINTDOCUMENT_OOLLEGEND), (LPCTSTR)szOOLColors.GetAt(OOL_OOLCOLOR_SOFTLIMIT), (LPCTSTR)szOOLColors.GetAt(OOL_OOLCOLOR_HARDLIMIT), (LPCTSTR)szOOLColors.GetAt(OOL_OOLCOLOR_DELTALIMIT), (LPCTSTR)szOOLColors.GetAt(OOL_OOLCOLOR_CONSISTENCYLIMIT));
		szInfo += szLegend + EOL;
	}
	return szInfo;
}

CString COOLWnd::GetPrintDocListItemsTitle(CONST CStringArray &szColumns) CONST
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

CString COOLWnd::GetPrintDocNotice() CONST
{
	CVersionInfo  cVersionInfo;

	return cVersionInfo.QueryComments();
}

CString COOLWnd::GetPrintDocFooter(CONST CTimeKey &tTime, LPCTSTR pszPrinterName, INT nPages, INT nPage) CONST
{
	CString  szFooter;

	szFooter.Format(STRING(IDS_OOL_PRINTDOCUMENT_FOOTER), (LPCTSTR)tTime.Format(IDS_TIMEKEY_DATEFORMAT), (LPCTSTR)tTime.Format(IDS_TIMEKEY_TIMEFORMAT), pszPrinterName, nPage, nPages);
	return szFooter;
}

INT COOLWnd::ExtractPrintDocText(LPCTSTR pszText, CStringArray &szColumnsText) CONST
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

BOOL COOLWnd::CalcPrintDocTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 48, (INT)((-5.3*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL COOLWnd::CalcPrintDocSubTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 64, (INT)((-4.0*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL COOLWnd::CalcPrintDocOperatingDetailsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 76, (INT)((-3.3*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL COOLWnd::CalcPrintDocOperatingModeFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 76, (INT)((-3.3*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL COOLWnd::CalcPrintDocListItemsFonts(CDC &cDC, CONST RECT &rArea, CONST CStringArray &szColumns, CONST CStringArray &szContents, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont, CFont &cTitleFont, CFont &cItemsFont) CONST
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

BOOL COOLWnd::CalcPrintDocNoticeFonts(CDC &cDC, CONST RECT &rArea, CFont &cFont, CFont &cLogoFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 96, (INT)((-2.6*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL) && cLogoFont.CreateFont(max(-(rArea.right - rArea.left) / 96, (INT)((-2.6*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, STRING(IDS_FONTFACE_COMPANYLOGO));
}

BOOL COOLWnd::CalcPrintDocFooterFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 80, (INT)((-3.0*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

INT COOLWnd::CalcPrintDocTitleWidth(CDC &cDC, LPCTSTR pszColumn, CFont *pTitleFont) CONST
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
INT COOLWnd::CalcPrintDocTitleWidth(CDC &cDC, CONST CStringArray &szColumns, CONST CStringArray &szContents, CFont *pTitleFont, CFont *pItemsFont, CUIntArray &nTabs) CONST
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
	if (nTabs.GetSize() > 0)
	{
		nTabs.SetAt(nTabs.GetSize() - 1, nTabs.GetAt(nTabs.GetSize() - 1) - nIndent);
		return((INT)nTabs.GetSize());
	}
	return 0;
}

INT COOLWnd::CalcPrintDocColumnWidth(CDC &cDC, CStringArray &szContents, CFont *pItemsFont) CONST
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

BOOL COOLWnd::CalcPrintDocRect(CDC &cDC, CONST RECT &rtMargin, BOOL bMetric) CONST
{
	CRect  rClip;

	rClip.SetRect(0, 0, cDC.GetDeviceCaps(HORZRES), cDC.GetDeviceCaps(VERTRES));
	rClip.DeflateRect((bMetric) ? (rtMargin.left*cDC.GetDeviceCaps(HORZRES)) / (100 * cDC.GetDeviceCaps(HORZSIZE)) : (rtMargin.left*cDC.GetDeviceCaps(LOGPIXELSX)) / 1000, (bMetric) ? (rtMargin.top*cDC.GetDeviceCaps(VERTRES)) / (100 * cDC.GetDeviceCaps(VERTSIZE)) : (rtMargin.top*cDC.GetDeviceCaps(LOGPIXELSY)) / 1000, (bMetric) ? (rtMargin.right*cDC.GetDeviceCaps(HORZRES)) / (100 * cDC.GetDeviceCaps(HORZSIZE)) : (rtMargin.right*cDC.GetDeviceCaps(LOGPIXELSX)) / 1000, (bMetric) ? (rtMargin.bottom*cDC.GetDeviceCaps(VERTRES)) / (100 * cDC.GetDeviceCaps(VERTSIZE)) : (rtMargin.bottom*cDC.GetDeviceCaps(LOGPIXELSY)) / 1000);
	return((cDC.IntersectClipRect(rClip) != ERROR) ? TRUE : FALSE);
}

BOOL COOLWnd::SetLayoutInfo(CONST CUIntArray &nColumns, CONST CUIntArray &nWidths, CONST LOGFONT *pTitleFont, CONST LOGFONT *pItemsFont, INT nIndex, INT nCount, CONST SCROLLINFO *pHorzScrollInfo, CONST SCROLLINFO *pVertScrollInfo)
{
	CString  szLayout;

	return((GetLayout(szLayout)) ? (m_wndView.SetLayout(szLayout, nColumns, nWidths) && m_wndView.SetTitleFont(pTitleFont) && m_wndView.SetItemsFont(pItemsFont) && m_wndView.SetLayoutInfo(nIndex, nCount, pHorzScrollInfo, pVertScrollInfo)) : FALSE);
}

BOOL COOLWnd::GetLayoutInfo(CUIntArray &nColumns, CUIntArray &nWidths, LOGFONT *pTitleFont, LOGFONT *pItemsFont, INT &nIndex, INT &nCount, SCROLLINFO *pHorzScrollInfo, SCROLLINFO *pVertScrollInfo) CONST
{
	CString  szLayout;

	return((m_wndView.GetLayout(szLayout, nColumns, nWidths) && m_wndView.GetTitleFont(pTitleFont) && m_wndView.GetItemsFont(pItemsFont) && m_wndView.GetLayoutInfo(nIndex, nCount, pHorzScrollInfo, pVertScrollInfo)) ? TRUE : FALSE);
}

BEGIN_MESSAGE_MAP(COOLWnd, CDisplayWnd)
	//{{AFX_MSG_MAP(COOLWnd)
	ON_WM_CREATE()
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()
	ON_WM_SETFOCUS()
	ON_WM_DESTROY()
	ON_COMMAND(IDM_OOLSETTINGS, OnSettings)
	ON_COMMAND(IDM_OOLLINKAGES, OnLinkages)
	ON_COMMAND(IDM_OOLPARAMETERS, OnParameters)
	ON_COMMAND(IDM_OOLACKNOWLEDGE, OnAcknowledge)
	ON_COMMAND(IDM_OOLRETRIEVALS, OnRetrievals)
	ON_COMMAND(IDM_OOLRETRIEVESTOP, OnRetrieveStop)
	ON_COMMAND(IDM_OOLRETRIEVEFORWARD, OnRetrieveAutoForward)
	ON_COMMAND(IDM_OOLRETRIEVEBACKWARD, OnRetrieveAutoBackward)
	ON_COMMAND(IDM_OOLRETRIEVESTEPFORWARD, OnRetrieveManualForward)
	ON_COMMAND(IDM_OOLRETRIEVESTEPBACKWARD, OnRetrieveManualBackward)
	ON_COMMAND(IDM_OOLRETRIEVEPSEUDOREALTIME, OnRetrievePseudoRealtime)
	ON_COMMAND(IDM_OOLPRINT, OnPrint)
	ON_UPDATE_COMMAND_UI(IDM_OOLSETTINGS, OnUpdateSettings)
	ON_UPDATE_COMMAND_UI(IDM_OOLLINKAGES, OnUpdateLinkages)
	ON_UPDATE_COMMAND_UI(IDM_OOLPARAMETERS, OnUpdateParameters)
	ON_UPDATE_COMMAND_UI(IDM_OOLACKNOWLEDGE, OnUpdateAcknowledge)
	ON_UPDATE_COMMAND_UI(IDM_OOLRETRIEVALS, OnUpdateRetrievals)
	ON_UPDATE_COMMAND_UI(IDM_OOLRETRIEVESTOP, OnUpdateRetrieveStop)
	ON_UPDATE_COMMAND_UI(IDM_OOLRETRIEVEFORWARD, OnUpdateRetrieveAutoForward)
	ON_UPDATE_COMMAND_UI(IDM_OOLRETRIEVEBACKWARD, OnUpdateRetrieveAutoBackward)
	ON_UPDATE_COMMAND_UI(IDM_OOLRETRIEVESTEPFORWARD, OnUpdateRetrieveManualForward)
	ON_UPDATE_COMMAND_UI(IDM_OOLRETRIEVESTEPBACKWARD, OnUpdateRetrieveManualBackward)
	ON_UPDATE_COMMAND_UI(IDM_OOLRETRIEVEPSEUDOREALTIME, OnUpdateRetrievePseudoRealtime)
	ON_UPDATE_COMMAND_UI(IDM_OOLPRINT, OnUpdatePrint)
	ON_UPDATE_COMMAND_UI(ID_OOL_STATUSBAR_MESSAGEPANE, OnUpdateStatusBarMessagePane)
	ON_UPDATE_COMMAND_UI(ID_OOL_STATUSBAR_MODEPANE, OnUpdateStatusBarModePane)
	ON_UPDATE_COMMAND_UI(ID_OOL_STATUSBAR_TYPEPANE, OnUpdateStatusBarTypePane)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COOLWnd message handlers

int COOLWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDisplayWnd::OnCreate(lpCreateStruct) != -1)
	{
		for (EnableDocking(CBRS_ALIGN_TOP); CreateToolBar() && CreateStatusBar() && CreateView() && LoadAccelTable(MAKEINTRESOURCE(IDR_OOLFRAME)); )
		{
			UpdateBars();
			return 0;
		}
	}
	return -1;
}

void COOLWnd::OnGetMinMaxInfo(MINMAXINFO *lpMMI)
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

void COOLWnd::OnSize(UINT nType, int cx, int cy)
{
	CDisplayWnd::OnSize(nType, cx, cy);
	m_wndView.RecalcLayout();
}

BOOL COOLWnd::OnEraseBkgnd(CDC *pDC)
{
	m_wndToolBar.UpdateWindow();
	m_wndStatusBar.UpdateWindow();
	return TRUE;
}

void COOLWnd::OnShowWindow(BOOL bShow, UINT nStatus)
{
	UINT  nFlags;

	if (bShow)
	{
		if (nStatus == OOLPARAMETERFILTER_BEHAVIOR_BRINGTOTOP || nStatus == (UINT)-1)
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

void COOLWnd::OnSetFocus(CWnd *pOldWnd)
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

BOOL COOLWnd::OnCloseOpenDialog(UINT nCode)
{
	UINT  nMode;
	UINT  nSpeed;
	BOOL  bBadData;
	BOOL  bToolTips;
	BOOL  bInvalidData;
	LOGFONT  fntTitle;
	LOGFONT  fntItems;
	CString  szLayout;
	CString  szFileName;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CUIntArray  nColumns;
	CUIntArray  nColors;
	COOLPrintJobs  pJobs;
	COOLParameterFilters  pFilters;

	if (nCode == IDOK)
	{
		for (SetMode(m_dlgOpen.GetMode()), SetType(MAKELONG(DISPLAY_TYPE_OOL, m_dlgOpen.GetType())), SetWindowText(m_dlgOpen.GetTitle()); m_dlgOpen.IsLayoutModified(); )
		{
			m_dlgOpen.GetLayout(szLayout, nColumns);
			m_dlgOpen.GetLayoutTitleFont(&fntTitle);
			m_dlgOpen.GetLayoutItemsFont(&fntItems);
			m_dlgOpen.GetLayoutInvalidDataMode(bInvalidData);
			m_dlgOpen.GetLayoutBadDataMode(bBadData);
			m_dlgOpen.GetLayoutToolTipMode(bToolTips);
			if (!SetLayout(szLayout, nColumns) || !SetTitleFont(&fntTitle) || !SetItemsFont(&fntItems) || !EnableInvalidDataMode(bInvalidData) || !EnableBadDataMode(bBadData) || !EnableToolTipMode(bToolTips)) return FALSE;
			break;
		}
		if (!m_dlgOpen.IsLayoutModified())
		{
			m_dlgOpen.GetLayout(szLayout);
			if (!SetLayout(szLayout)) return FALSE;
		}
		if (m_dlgOpen.IsFilteringModified())
		{
			m_dlgOpen.GetParameterFilters(pFilters);
			m_dlgOpen.GetFilterColors(nColors);
			if (!SetParameterFilters(pFilters) || !SetFilterColors(nColors)) return FALSE;
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

BOOL COOLWnd::OnCloseSettingsDialog(UINT nCode)
{
	BOOL  bBadData;
	BOOL  bToolTips;
	BOOL  bInvalidData;
	LOGFONT  fntTitle;
	LOGFONT  fntItems;
	CString  szLayout;
	CString  szFileName;
	CUIntArray  nColors;
	CUIntArray  nColumns;
	COOLPrintJobs  pJobs;
	COOLParameterFilters  pFilters;

	if (nCode == IDOK)
	{
		for (GetLayout(szLayout); m_dlgSettings.IsLayoutModified(); )
		{
			m_dlgSettings.GetLayout(nColumns);
			m_dlgSettings.GetLayoutTitleFont(&fntTitle);
			m_dlgSettings.GetLayoutItemsFont(&fntItems);
			m_dlgSettings.GetLayoutInvalidDataMode(bInvalidData);
			m_dlgSettings.GetLayoutBadDataMode(bBadData);
			m_dlgSettings.GetLayoutToolTipMode(bToolTips);
			if (!SetLayout(szLayout, nColumns) || !SetTitleFont(&fntTitle) || !SetItemsFont(&fntItems) || !EnableInvalidDataMode(bInvalidData) || !EnableBadDataMode(bBadData) || !EnableToolTipMode(bToolTips)) return FALSE;
			break;
		}
		if (m_dlgSettings.IsFilteringModified())
		{
			m_dlgSettings.GetParameterFilters(pFilters);
			m_dlgSettings.GetFilterColors(nColors);
			if (!SetParameterFilters(pFilters) || !SetFilterColors(nColors)) return FALSE;
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

BOOL COOLWnd::OnCloseRetrieveDialog(UINT nCode)
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

void COOLWnd::OnSettings()
{
	CHourglassCursor  cCursor;

	ReportEvent((m_dlgSettings.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void COOLWnd::OnLinkages()
{
	CHourglassCursor  cCursor;

	ReportEvent((m_dlgLinkages.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void COOLWnd::OnParameters()
{
	COolParameter  cOolParameter;
	CHourglassCursor  cCursor;

	ReportEvent((m_dlgParameters.Create(this, (GetParameterInfo(&cOolParameter)) ? (LPCTSTR)cOolParameter.GetTag() : EMPTYSTRING) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void COOLWnd::OnAcknowledge()
{
	ReportEvent((m_dlgAcknowledge.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void COOLWnd::OnRetrievals()
{
	CHourglassCursor  cCursor;

	ReportEvent((m_dlgRetrievals.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void COOLWnd::OnRetrieveStop()
{
	RetrieveMoreData(OOL_RETRIEVE_STOPPED);
}

void COOLWnd::OnRetrieveAutoForward()
{
	RetrieveMoreData(OOL_RETRIEVE_AUTOFORWARD);
}

void COOLWnd::OnRetrieveAutoBackward()
{
	RetrieveMoreData(OOL_RETRIEVE_AUTOBACKWARD);
}

void COOLWnd::OnRetrieveManualForward()
{
	RetrieveMoreData(OOL_RETRIEVE_MANUALFORWARD);
}

void COOLWnd::OnRetrieveManualBackward()
{
	RetrieveMoreData(OOL_RETRIEVE_MANUALBACKWARD);
}

void COOLWnd::OnRetrievePseudoRealtime()
{
	RetrieveMoreData(OOL_RETRIEVE_PSEUDOREALTIME);
}

void COOLWnd::OnPrint()
{
	CHourglassCursor  cCursor;

	ReportEvent((!Print()) ? SYSTEM_WARNING_DISPLAY_PRINT_FAILURE : SYSTEM_NOERROR);
}

void COOLWnd::OnDestroy()
{
	CHourglassCursor  cCursor;

	Stop();
	CDisplayWnd::OnDestroy();
}

void COOLWnd::OnUpdateSettings(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsInitialized());
	pCmdUI->SetCheck(IsWindow(m_dlgSettings.GetSafeHwnd()));
}

void COOLWnd::OnUpdateLinkages(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsInitialized() && GetScope() == DISPLAY_SCOPE_LOCAL  &&  !GetLink());
	pCmdUI->SetCheck(IsWindow(m_dlgLinkages.GetSafeHwnd()));
}

void COOLWnd::OnUpdateParameters(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsInitialized() && HasParameters()) ? TRUE : FALSE);
	pCmdUI->SetCheck(IsWindow(m_dlgParameters.GetSafeHwnd()));
}

void COOLWnd::OnUpdateAcknowledge(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsInitialized() && HasParameters() && IsAlerted()) ? TRUE : FALSE);
	pCmdUI->SetCheck(IsWindow(m_dlgAcknowledge.GetSafeHwnd()));
}

void COOLWnd::OnUpdateRetrievals(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsInitialized() && GetScope() == DISPLAY_SCOPE_LOCAL) ? TRUE : FALSE);
	pCmdUI->SetCheck(IsWindow(m_dlgRetrievals.GetSafeHwnd()));
}

void COOLWnd::OnUpdateRetrieveStop(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && ((GetRetrieveMode() & OOL_RETRIEVE_AUTOFORWARD) || (GetRetrieveMode() & OOL_RETRIEVE_AUTOBACKWARD) || (GetRetrieveMode() & OOL_RETRIEVE_PSEUDOREALTIME) || HIWORD(IsRetrievingData())) && !(GetRetrieveMode() & OOL_RETRIEVE_STOPPED)) ? TRUE : FALSE);
}

void COOLWnd::OnUpdateRetrieveAutoForward(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & OOL_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & OOL_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & OOL_RETRIEVE_STOPPED))) ? TRUE : FALSE);
}

void COOLWnd::OnUpdateRetrieveAutoBackward(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & OOL_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & OOL_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & OOL_RETRIEVE_STOPPED))) ? TRUE : FALSE);
}

void COOLWnd::OnUpdateRetrieveManualForward(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & OOL_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & OOL_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & OOL_RETRIEVE_STOPPED))) ? TRUE : FALSE);
}

void COOLWnd::OnUpdateRetrieveManualBackward(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & OOL_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & OOL_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & OOL_RETRIEVE_STOPPED))) ? TRUE : FALSE);
}

void COOLWnd::OnUpdateRetrievePseudoRealtime(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & OOL_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & OOL_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & OOL_RETRIEVE_STOPPED))) ? TRUE : FALSE);
}

void COOLWnd::OnUpdatePrint(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsInitialized() && IsDefaultPrinterAvailable() && CanPrint()) ? TRUE : FALSE);
}

void COOLWnd::OnUpdateStatusBarMessagePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void COOLWnd::OnUpdateStatusBarModePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void COOLWnd::OnUpdateStatusBarTypePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}
