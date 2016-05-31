// GRD.CPP : Graphic Display Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the graphic display
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


static UINT BASED_CODE nGRDStatusBarIndicators[] =
{
	ID_GRD_STATUSBAR_MESSAGEPANE,
	ID_GRD_STATUSBAR_MODEPANE,
	ID_GRD_STATUSBAR_TYPEPANE
};



/////////////////////////////////////////////////////////////////////////////
// CGRDPrintJobInfo

CGRDPrintJobInfo::CGRDPrintJobInfo() : CObject()
{
	m_nPrintMode = 0;
	m_nPrintFlags = 0;
	m_nPrintScale = 0;
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

VOID CGRDPrintJobInfo::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CGRDPrintJobInfo::GetName() CONST
{
	return m_szName;
}

VOID CGRDPrintJobInfo::SetProfile(LPCTSTR pszProfile)
{
	m_szProfile = pszProfile;
}

CString CGRDPrintJobInfo::GetProfile() CONST
{
	return m_szProfile;
}

VOID CGRDPrintJobInfo::SetComments(LPCTSTR pszComments)
{
	m_szComments = pszComments;
}

CString CGRDPrintJobInfo::GetComments() CONST
{
	return m_szComments;
}

BOOL CGRDPrintJobInfo::SetPrintMode(UINT nMode)
{
	m_nPrintMode = nMode;
	return TRUE;
}

UINT CGRDPrintJobInfo::GetPrintMode() CONST
{
	return m_nPrintMode;
}

BOOL CGRDPrintJobInfo::SetPrintFlags(UINT nFlags)
{
	if (nFlags == GRD_PRINT_ATTIME || nFlags == GRD_PRINT_ATDAILYTIME || nFlags == GRD_PRINT_ATEVENT || !nFlags)
	{
		m_nPrintFlags = nFlags;
		return TRUE;
	}
	return FALSE;
}

UINT CGRDPrintJobInfo::GetPrintFlags() CONST
{
	return m_nPrintFlags;
}

BOOL CGRDPrintJobInfo::SetPrintScale(UINT nScale)
{
	if (m_nPrintMode & GRD_PRINT_FIXEDSCALE)
	{
		m_nPrintScale = nScale;
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDPrintJobInfo::GetPrintScale(UINT &nScale) CONST
{
	if (m_nPrintMode & GRD_PRINT_FIXEDSCALE)
	{
		nScale = m_nPrintScale;
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDPrintJobInfo::SetPrintAtTime(CONST CTimeKey &tTime)
{
	if ((m_nPrintMode & GRD_PRINT_ATTIME) && !(m_nPrintMode & GRD_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & GRD_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & GRD_PRINT_REPEATSTOPBYTIME))
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
BOOL CGRDPrintJobInfo::SetPrintAtTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval)
{
	if ((m_nPrintMode & GRD_PRINT_ATTIME) && (m_nPrintMode & GRD_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & GRD_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & GRD_PRINT_REPEATSTOPBYTIME))
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
BOOL CGRDPrintJobInfo::SetPrintAtTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval, UINT nStopCount)
{
	if ((m_nPrintMode & GRD_PRINT_ATTIME) && (m_nPrintMode & GRD_PRINT_REPEATBYINTERVAL) && (m_nPrintMode & GRD_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & GRD_PRINT_REPEATSTOPBYTIME))
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
BOOL CGRDPrintJobInfo::SetPrintAtTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval, CONST CTimeKey &tStopTime)
{
	if ((m_nPrintMode & GRD_PRINT_ATTIME) && (m_nPrintMode & GRD_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & GRD_PRINT_REPEATSTOPBYCOUNT) && (m_nPrintMode & GRD_PRINT_REPEATSTOPBYTIME))
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

BOOL CGRDPrintJobInfo::GetPrintAtTime(CTimeKey &tTime) CONST
{
	if ((m_nPrintMode & GRD_PRINT_ATTIME) && !(m_nPrintMode & GRD_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & GRD_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & GRD_PRINT_REPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtTime;
		return TRUE;
	}
	return FALSE;
}
BOOL CGRDPrintJobInfo::GetPrintAtTime(CTimeKey &tTime, CTimeSpan &tInterval) CONST
{
	if ((m_nPrintMode & GRD_PRINT_ATTIME) && (m_nPrintMode & GRD_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & GRD_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & GRD_PRINT_REPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtTime;
		tInterval = m_tRepeatInterval;
		return TRUE;
	}
	return FALSE;
}
BOOL CGRDPrintJobInfo::GetPrintAtTime(CTimeKey &tTime, CTimeSpan &tInterval, UINT &nStopCount) CONST
{
	if ((m_nPrintMode & GRD_PRINT_ATTIME) && (m_nPrintMode & GRD_PRINT_REPEATBYINTERVAL) && (m_nPrintMode & GRD_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & GRD_PRINT_REPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtTime;
		tInterval = m_tRepeatInterval;
		nStopCount = m_nRepeatStopByCount[0];
		return TRUE;
	}
	return FALSE;
}
BOOL CGRDPrintJobInfo::GetPrintAtTime(CTimeKey &tTime, CTimeSpan &tInterval, CTimeKey &tStopTime) CONST
{
	if ((m_nPrintMode & GRD_PRINT_ATTIME) && (m_nPrintMode & GRD_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & GRD_PRINT_REPEATSTOPBYCOUNT) && (m_nPrintMode & GRD_PRINT_REPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtTime;
		tInterval = m_tRepeatInterval;
		tStopTime = m_tRepeatStopByTime[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDPrintJobInfo::SetPrintAtDailyTime(CONST CTimeSpan &tTime)
{
	TIMEKEY  tTimeKey;

	if ((m_nPrintMode & GRD_PRINT_ATDAILYTIME) && !(m_nPrintMode & GRD_PRINT_DAILYREPEATSTOPBYCOUNT) && !(m_nPrintMode & GRD_PRINT_DAILYREPEATSTOPBYTIME))
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
BOOL CGRDPrintJobInfo::SetPrintAtDailyTime(CONST CTimeSpan &tTime, UINT nStopCount)
{
	TIMEKEY  tTimeKey;

	if ((m_nPrintMode & GRD_PRINT_ATDAILYTIME) && (m_nPrintMode & GRD_PRINT_DAILYREPEATSTOPBYCOUNT) && !(m_nPrintMode & GRD_PRINT_DAILYREPEATSTOPBYTIME))
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
BOOL CGRDPrintJobInfo::SetPrintAtDailyTime(CONST CTimeSpan &tTime, CONST CTimeKey &tStopTime)
{
	TIMEKEY  tTimeKey;

	if ((m_nPrintMode & GRD_PRINT_ATDAILYTIME) && !(m_nPrintMode & GRD_PRINT_DAILYREPEATSTOPBYCOUNT) && (m_nPrintMode & GRD_PRINT_DAILYREPEATSTOPBYTIME))
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

BOOL CGRDPrintJobInfo::GetPrintAtDailyTime(CTimeSpan &tTime) CONST
{
	if ((m_nPrintMode & GRD_PRINT_ATDAILYTIME) && !(m_nPrintMode & GRD_PRINT_DAILYREPEATSTOPBYCOUNT) && !(m_nPrintMode & GRD_PRINT_DAILYREPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtDailyTime;
		return TRUE;
	}
	return FALSE;
}
BOOL CGRDPrintJobInfo::GetPrintAtDailyTime(CTimeSpan &tTime, UINT &nStopCount) CONST
{
	if ((m_nPrintMode & GRD_PRINT_ATDAILYTIME) && (m_nPrintMode & GRD_PRINT_DAILYREPEATSTOPBYCOUNT) && !(m_nPrintMode & GRD_PRINT_DAILYREPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtDailyTime;
		nStopCount = m_nRepeatStopByCount[1];
		return TRUE;
	}
	return FALSE;
}
BOOL CGRDPrintJobInfo::GetPrintAtDailyTime(CTimeSpan &tTime, CTimeKey &tStopTime) CONST
{
	if ((m_nPrintMode & GRD_PRINT_ATDAILYTIME) && !(m_nPrintMode & GRD_PRINT_DAILYREPEATSTOPBYCOUNT) && (m_nPrintMode & GRD_PRINT_DAILYREPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtDailyTime;
		tStopTime = m_tRepeatStopByTime[1];
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDPrintJobInfo::SetPrintAtEvent(LPCTSTR pszEvent)
{
	if (m_nPrintMode & GRD_PRINT_ATEVENT)
	{
		m_szEvent = pszEvent;
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDPrintJobInfo::GetPrintAtEvent(CString &szEvent) CONST
{
	if (m_nPrintMode & GRD_PRINT_ATEVENT)
	{
		szEvent = m_szEvent;
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDPrintJobInfo::SetPrintCount(UINT nCount)
{
	if (m_nPrintMode & GRD_PRINT_ATTIME)
	{
		m_nPrintCount[0] = nCount;
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDPrintJobInfo::GetPrintCount(UINT &nCount) CONST
{
	if (m_nPrintMode & GRD_PRINT_ATTIME)
	{
		nCount = m_nPrintCount[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDPrintJobInfo::SetPrintDailyCount(UINT nCount)
{
	if (m_nPrintMode & GRD_PRINT_ATDAILYTIME)
	{
		m_nPrintCount[1] = nCount;
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDPrintJobInfo::GetPrintDailyCount(UINT &nCount) CONST
{
	if (m_nPrintMode & GRD_PRINT_ATDAILYTIME)
	{
		nCount = m_nPrintCount[1];
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDPrintJobInfo::SetPrintLastTime(CONST CTimeKey &tTime)
{
	if (m_nPrintMode & GRD_PRINT_ATTIME)
	{
		m_tPrintLastTime[0] = tTime;
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDPrintJobInfo::GetPrintLastTime(CTimeKey &tTime) CONST
{
	if (m_nPrintMode & GRD_PRINT_ATTIME)
	{
		tTime = m_tPrintLastTime[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDPrintJobInfo::SetPrintLastDailyTime(CONST CTimeKey &tTime)
{
	if (m_nPrintMode & GRD_PRINT_ATDAILYTIME)
	{
		m_tPrintLastTime[1] = tTime;
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDPrintJobInfo::GetPrintLastDailyTime(CTimeKey &tTime) CONST
{
	if (m_nPrintMode & GRD_PRINT_ATDAILYTIME)
	{
		tTime = m_tPrintLastTime[1];
		return TRUE;
	}
	return FALSE;
}

VOID CGRDPrintJobInfo::Copy(CONST CGRDPrintJobInfo *pJobInfo)
{
	m_szName = pJobInfo->m_szName;
	m_szEvent = pJobInfo->m_szEvent;
	m_szProfile = pJobInfo->m_szProfile;
	m_szComments = pJobInfo->m_szComments;
	m_nPrintMode = pJobInfo->m_nPrintMode;
	m_nPrintFlags = pJobInfo->m_nPrintFlags;
	m_nPrintScale = pJobInfo->m_nPrintScale;
	m_nPrintCount[0] = pJobInfo->m_nPrintCount[0];
	m_nPrintCount[1] = pJobInfo->m_nPrintCount[1];
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

BOOL CGRDPrintJobInfo::Compare(CONST CGRDPrintJobInfo *pJobInfo) CONST
{
	return((pJobInfo->m_szName == m_szName  &&  pJobInfo->m_szProfile == m_szProfile  &&  pJobInfo->m_szComments == m_szComments  &&  pJobInfo->m_nPrintMode == m_nPrintMode && (!(m_nPrintMode & GRD_PRINT_FIXEDSCALE) || pJobInfo->m_nPrintScale == m_nPrintScale) && (!(m_nPrintMode & GRD_PRINT_ATTIME) || pJobInfo->m_tPrintAtTime == m_tPrintAtTime) && (!(m_nPrintMode & GRD_PRINT_ATDAILYTIME) || pJobInfo->m_tPrintAtDailyTime == m_tPrintAtDailyTime) && (!(m_nPrintMode & GRD_PRINT_ATEVENT) || pJobInfo->m_szEvent == m_szEvent) && (!(m_nPrintMode & GRD_PRINT_REPEATBYINTERVAL) || pJobInfo->m_tRepeatInterval == m_tRepeatInterval) && (!(m_nPrintMode & GRD_PRINT_REPEATSTOPBYCOUNT) || pJobInfo->m_nRepeatStopByCount[0] == m_nRepeatStopByCount[0]) && (!(m_nPrintMode & GRD_PRINT_REPEATSTOPBYTIME) || pJobInfo->m_tRepeatStopByTime[0] == m_tRepeatStopByTime[0]) && (!(m_nPrintMode & GRD_PRINT_DAILYREPEATSTOPBYCOUNT) || pJobInfo->m_nRepeatStopByCount[1] == m_nRepeatStopByCount[1]) && (!(m_nPrintMode & GRD_PRINT_DAILYREPEATSTOPBYTIME) || pJobInfo->m_tRepeatStopByTime[1] == m_tRepeatStopByTime[1])) ? TRUE : FALSE);
}

BOOL CGRDPrintJobInfo::Map(CByteArray &nInfo) CONST
{
	INT  cbData;
	DATA  sData;

	sData.cbName = (m_szName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbEvent = (m_szEvent.GetLength() + 1)*sizeof(TCHAR);
	sData.cbProfile = (m_szProfile.GetLength() + 1)*sizeof(TCHAR);
	sData.cbComments = (m_szComments.GetLength() + 1)*sizeof(TCHAR);
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbName + sData.cbProfile + sData.cbComments + sData.cbEvent)), sData.nPrintMode = m_nPrintMode, sData.nPrintScale = m_nPrintScale, sData.nPrintCount[0] = m_nPrintCount[0], sData.nPrintCount[1] = m_nPrintCount[1], sData.tPrintAtTime = m_tPrintAtTime.GetTime(), sData.tPrintAtDailyTime = m_tPrintAtDailyTime.GetTotalSeconds(), sData.tPrintLastTime[0] = m_tPrintLastTime[0].GetTime(), sData.tPrintLastTime[1] = m_tPrintLastTime[1].GetTime(), sData.tRepeatInterval = m_tRepeatInterval.GetTotalSeconds(), sData.nRepeatStopByCount[0] = m_nRepeatStopByCount[0], sData.nRepeatStopByCount[1] = m_nRepeatStopByCount[1], sData.tRepeatStopByTime[0] = m_tRepeatStopByTime[0].GetTime(), sData.tRepeatStopByTime[1] = m_tRepeatStopByTime[1].GetTime(); nInfo.GetSize() == sData.cbSize; )
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

BOOL CGRDPrintJobInfo::Unmap(CONST CByteArray &nInfo)
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
		m_nPrintScale = sData.nPrintScale;
		m_nPrintCount[0] = sData.nPrintCount[0];
		m_nPrintCount[1] = sData.nPrintCount[1];
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
// CGRDPrintJobs

CGRDPrintJobs::CGRDPrintJobs() : CPtrArray()
{
	return;
}

CGRDPrintJobs::~CGRDPrintJobs()
{
	RemoveAll();
}

INT CGRDPrintJobs::Add(CGRDPrintJobInfo *pJobInfo)
{
	return((INT)CPtrArray::Add(pJobInfo));
}

INT CGRDPrintJobs::Find(LPCTSTR pszName) CONST
{
	INT  nJob;
	INT  nJobs;
	CGRDPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (INT)GetSize(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = GetAt(nJob)) && pJobInfo->GetName() == pszName) break;
		continue;
	}
	return((nJob < nJobs) ? nJob : -1);
}

CGRDPrintJobInfo *CGRDPrintJobs::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CGRDPrintJobInfo *)CPtrArray::GetAt(nIndex) : (CGRDPrintJobInfo *)NULL);
}

CGRDPrintJobInfo *CGRDPrintJobs::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CGRDPrintJobInfo *)CPtrArray::GetAt(nIndex) : (CGRDPrintJobInfo *)NULL);
}

TIMEKEY CGRDPrintJobs::Schedule()
{
	INT  nJob;
	INT  nJobs;
	UINT  nJobMode;
	UINT  nJobPrintCount[2];
	CTimeKey  tJobPrintTime[4];
	CTimeSpan  tJobPrintInterval;
	CTimeSpan  tJobPrintDailyTime;
	TIMEKEY  tJobPrintTimeout[2];
	CGRDPrintJobInfo  *pJobInfo[2];

	for (nJob = 0, nJobs = (INT)GetSize(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo[0] = GetAt(nJob)) != (CGRDPrintJobInfo *)NULL)
		{
			if (((nJobMode = pJobInfo[0]->GetPrintMode()) & GRD_PRINT_ACTIVE) && (((nJobMode & GRD_PRINT_ATTIME) && pJobInfo[0]->GetPrintLastTime(tJobPrintTime[1]) && (tJobPrintTime[1] > 0 || pJobInfo[0]->SetPrintLastTime(tJobPrintTime[3]))) || (nJobMode & GRD_PRINT_ATDAILYTIME)) &&
				((pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0]) && pJobInfo[0]->GetPrintCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastTime(tJobPrintTime[1]) && tJobPrintTime[3] >= tJobPrintTime[0] && tJobPrintTime[0] > tJobPrintTime[1] && pJobInfo[0]->SetPrintFlags(GRD_PRINT_ATTIME) && pJobInfo[0]->SetPrintCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0], tJobPrintInterval) && pJobInfo[0]->GetPrintCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastTime(tJobPrintTime[1]) && tJobPrintTime[3] >= tJobPrintTime[0] && (tJobPrintTime[0] > tJobPrintTime[1] || (tJobPrintTime[1].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds() < (tJobPrintTime[3].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds()) && pJobInfo[0]->SetPrintFlags(GRD_PRINT_ATTIME) && pJobInfo[0]->SetPrintCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0], tJobPrintInterval, nJobPrintCount[1]) && pJobInfo[0]->GetPrintCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastTime(tJobPrintTime[1]) && tJobPrintTime[3] >= tJobPrintTime[0] && (tJobPrintTime[0] > tJobPrintTime[1] || (tJobPrintTime[1].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds() < (tJobPrintTime[3].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds()) && nJobPrintCount[0] < nJobPrintCount[1] && pJobInfo[0]->SetPrintFlags(GRD_PRINT_ATTIME) && pJobInfo[0]->SetPrintCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0], tJobPrintInterval, tJobPrintTime[2]) && pJobInfo[0]->GetPrintCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastTime(tJobPrintTime[1]) && tJobPrintTime[3] >= tJobPrintTime[0] && (tJobPrintTime[0] > tJobPrintTime[1] || (tJobPrintTime[1].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds() < (tJobPrintTime[3].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds()) && tJobPrintTime[3] <= tJobPrintTime[2] && pJobInfo[0]->SetPrintFlags(GRD_PRINT_ATTIME) && pJobInfo[0]->SetPrintCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtDailyTime(tJobPrintDailyTime) && pJobInfo[0]->GetPrintDailyCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastDailyTime(tJobPrintTime[1]) && tJobPrintTime[3].GetTime() % SECONDSPERDAY >= tJobPrintDailyTime.GetTotalSeconds() && tJobPrintTime[3].GetTime() / SECONDSPERDAY != tJobPrintTime[1].GetTime() / SECONDSPERDAY  &&  pJobInfo[0]->SetPrintFlags(GRD_PRINT_ATDAILYTIME) && pJobInfo[0]->SetPrintDailyCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastDailyTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtDailyTime(tJobPrintDailyTime, nJobPrintCount[1]) && pJobInfo[0]->GetPrintDailyCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastDailyTime(tJobPrintTime[1]) && tJobPrintTime[3].GetTime() % SECONDSPERDAY >= tJobPrintDailyTime.GetTotalSeconds() && tJobPrintTime[3].GetTime() / SECONDSPERDAY != tJobPrintTime[1].GetTime() / SECONDSPERDAY  &&  nJobPrintCount[0] < nJobPrintCount[1] && pJobInfo[0]->SetPrintFlags(GRD_PRINT_ATDAILYTIME) && pJobInfo[0]->SetPrintDailyCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastDailyTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtDailyTime(tJobPrintDailyTime, tJobPrintTime[2]) && pJobInfo[0]->GetPrintDailyCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastDailyTime(tJobPrintTime[1]) && tJobPrintTime[3].GetTime() % SECONDSPERDAY >= tJobPrintDailyTime.GetTotalSeconds() && tJobPrintTime[3].GetTime() / SECONDSPERDAY != tJobPrintTime[1].GetTime() / SECONDSPERDAY  &&  tJobPrintTime[3] <= tJobPrintTime[2] && pJobInfo[0]->SetPrintFlags(GRD_PRINT_ATDAILYTIME) && pJobInfo[0]->SetPrintDailyCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastDailyTime(tJobPrintTime[3]))))
			{
				if ((pJobInfo[1] = new CGRDPrintJobInfo))
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

VOID CGRDPrintJobs::RemoveAll()
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

BOOL CGRDPrintJobs::Copy(CONST CGRDPrintJobs *pPrintJobs)
{
	INT  nJob;
	INT  nJobs;
	CGRDPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (INT)pPrintJobs->GetSize(), RemoveAll(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = new CGRDPrintJobInfo) != (CGRDPrintJobInfo *)NULL)
		{
			pJobInfo->Copy(pPrintJobs->GetAt(nJob));
			InsertAt(nJob, pJobInfo, 1);
			continue;
		}
		break;
	}
	return((nJob == nJobs) ? TRUE : FALSE);
}

BOOL CGRDPrintJobs::Compare(CONST CGRDPrintJobs *pPrintJobs) CONST
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

BOOL CGRDPrintJobs::Map(CByteArray &nInfo) CONST
{
	INT  nJob;
	INT  nJobs;
	CByteArray  nJobData;
	CGRDPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (INT)GetSize(), nInfo.RemoveAll(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = GetAt(nJob)) && pJobInfo->Map(nJobData) && nInfo.Append(nJobData) >= 0) continue;
		break;
	}
	return((nJob == nJobs) ? TRUE : FALSE);
}

BOOL CGRDPrintJobs::Unmap(CONST CByteArray &nInfo)
{
	INT  cbJob;
	INT  cbJobs;
	CByteArray  nJobData;
	CGRDPrintJobInfo  *pJobInfo;

	for (cbJobs = 0, RemoveAll(); cbJobs < nInfo.GetSize(); cbJobs += cbJob)
	{
		for (CopyMemory(&cbJob, nInfo.GetData() + cbJobs, sizeof(cbJob)), nJobData.SetSize(max(min(cbJob, nInfo.GetSize() - cbJobs), 0)); nJobData.GetSize() >= 0; )
		{
			CopyMemory(nJobData.GetData(), nInfo.GetData() + cbJobs, nJobData.GetSize());
			break;
		}
		if ((pJobInfo = new CGRDPrintJobInfo))
		{
			if (pJobInfo->Unmap(nJobData) && Add(pJobInfo) >= 0) continue;
			delete pJobInfo;
		}
		break;
	}
	if ((pJobInfo = (!GetSize()) ? new CGRDPrintJobInfo : (CGRDPrintJobInfo *)NULL))
	{
		for (pJobInfo->SetName(STRING(IDS_PRINTJOB_DEFAULTNAME)), pJobInfo->SetProfile(STRING(IDS_PRINTPROFILE_DEFAULTNAME)), pJobInfo->SetPrintMode(GRD_PRINT_AUTOSCALE); Add(pJobInfo) >= 0; ) return TRUE;
		delete pJobInfo;
		return FALSE;
	}
	return((cbJobs == nInfo.GetSize()) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CGRDParameterSample

CGRDParameterSample::CGRDParameterSample() : CTMParameter()
{
	m_ptSample.x = 0;
	m_ptSample.y = 0;
	m_bConnected = FALSE;
}

VOID CGRDParameterSample::SetUpdateTMUnit(LPCTSTR pszTag)
{
	m_szPacket[1] = pszTag;
}

CString CGRDParameterSample::GetUpdateTMUnit() CONST
{
	return m_szPacket[1];
}

VOID CGRDParameterSample::SetUpdateTime(CONST CTimeTag &tTime)
{
	m_tPacket[1] = tTime;
}

CTimeTag CGRDParameterSample::GetUpdateTime() CONST
{
	return m_tPacket[1];
}

VOID CGRDParameterSample::SetPosition(CONST POINT &point)
{
	m_ptSample = point;
}

CPoint CGRDParameterSample::GetPosition() CONST
{
	return m_ptSample;
}

VOID CGRDParameterSample::DoConnect(BOOL bEnable)
{
	m_bConnected = bEnable;
}

BOOL CGRDParameterSample::IsConnected() CONST
{
	return m_bConnected;
}

BOOL CGRDParameterSample::IsDummy() CONST
{
	return((m_szPacket[1] == STRING(IDS_GRD_GRAPHTEXT_UPDATETMUNIT)) ? TRUE : FALSE);
}

BOOL CGRDParameterSample::Copy(CONST CGRDParameterSample *pParameterSample)
{
	m_ptSample = pParameterSample->m_ptSample;
	m_bConnected = pParameterSample->m_bConnected;
	return CTMParameter::Copy(pParameterSample);
}

BOOL CGRDParameterSample::Compare(CONST CGRDParameterSample *pParameterSample) CONST
{
	return((pParameterSample->m_ptSample == m_ptSample  &&  pParameterSample->m_bConnected == m_bConnected) ? CTMParameter::Compare(pParameterSample) : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CGRDParameterSamples

CGRDParameterSamples::CGRDParameterSamples() : CPtrArray()
{
	m_fRange[0] = 0.0;
	m_fRange[1] = 0.0;
	m_tPlot = CTimeTag(0);
	m_bInterruption = FALSE;
	m_bRange = FALSE;
}
CGRDParameterSamples::CGRDParameterSamples(LPCTSTR pszName) : CPtrArray()
{
	m_szName = pszName;
	m_fRange[0] = 0.0;
	m_fRange[1] = 0.0;
	m_tPlot = CTimeTag(0);
	m_bInterruption = FALSE;
	m_bRange = FALSE;
}

CGRDParameterSamples::~CGRDParameterSamples()
{
	RemoveAll();
}

VOID CGRDParameterSamples::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CGRDParameterSamples::GetName() CONST
{
	return m_szName;
}

VOID CGRDParameterSamples::SetRange(double fMinimum, double fMaximum)
{
	m_fRange[0] = fMinimum;
	m_fRange[1] = fMaximum;
	m_bRange = TRUE;
}

BOOL CGRDParameterSamples::GetRange(double &fMinimum, double &fMaximum) CONST
{
	fMinimum = m_fRange[0];
	fMaximum = m_fRange[1];
	return m_bRange;
}

VOID CGRDParameterSamples::SetLastPlotTime(CONST CTimeTag &tTime)
{
	m_tPlot = tTime;
}

CTimeTag CGRDParameterSamples::GetLastPlotTime() CONST
{
	return m_tPlot;
}

VOID CGRDParameterSamples::SetInterruptionFlag(BOOL bEnable)
{
	m_bInterruption = bEnable;
}

BOOL CGRDParameterSamples::GetInterruptionFlag() CONST
{
	return m_bInterruption;
}

INT CGRDParameterSamples::Add(CONST CGRDLayoutParameter *pParameter, CGRDParameterSample *pParameterSample)
{
	INT  nIndex;
	INT  nSample;
	INT  nSamples;
	double  fValue;

	if ((nIndex = FindIndex(pParameterSample, TRUE)) >= 0)
	{
		for (nSample = 0, nSamples = pParameterSample->GetValueCount(); nSample < nSamples; nSample++)
		{
			if (pParameterSample->GetValue(GetDatabase(), nSample, pParameter->GetAttributes(), fValue))
			{
				if (m_fRange[0] > fValue  &&  m_bRange)
				{
					m_fRange[0] = fValue;
					continue;
				}
				if (m_fRange[1] < fValue  &&  m_bRange)
				{
					m_fRange[1] = fValue;
					continue;
				}
				if (!m_bRange)
				{
					m_fRange[0] = fValue;
					m_fRange[1] = fValue;
					m_bRange = TRUE;
				}
			}
		}
		InsertAt(nIndex, pParameterSample, 1);
	}
	return nIndex;
}

INT CGRDParameterSamples::Find(CONST CTimeTag &tTime) CONST
{
	return FindIndex(tTime);
}
INT CGRDParameterSamples::Find(CONST CTimeTag &tTime, CONST POINT &point, CONST SIZE &size) CONST
{
	INT  nIndex;
	CRect  rSample;
	CPoint  ptSample;
	CGRDParameterSample  *pParameterSample;

	for (nIndex = FindIndex(tTime), rSample.SetRect(point.x - size.cx, point.y - size.cy, point.x + size.cx, point.y + size.cy); nIndex >= 0; nIndex--)
	{
		if ((pParameterSample = (CGRDParameterSample *)GetAt(nIndex)) && !pParameterSample->IsDummy())
		{
			if (rSample.PtInRect((ptSample = pParameterSample->GetPosition()))) break;
			if (rSample.left < ptSample.x || rSample.right > ptSample.x)
			{
				nIndex = -1;
				break;
			}
		}
	}
	return nIndex;
}
INT CGRDParameterSamples::Find(CONST CGRDParameterSample *pParameterSample) CONST
{
	return FindIndex(pParameterSample);
}

CGRDParameterSample *CGRDParameterSamples::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CGRDParameterSample *)CPtrArray::GetAt(nIndex) : (CGRDParameterSample *)NULL);
}

CGRDParameterSample *CGRDParameterSamples::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CGRDParameterSample *)CPtrArray::GetAt(nIndex) : (CGRDParameterSample *)NULL);
}

VOID CGRDParameterSamples::RemoveAll()
{
	INT  nParameterSample;
	INT  nParameterSamples;

	for (nParameterSample = 0, nParameterSamples = (INT)GetSize(), m_fRange[0] = m_fRange[1] = 0.0, m_bRange = FALSE, m_tPlot = 0, m_bInterruption = FALSE; nParameterSample < nParameterSamples; nParameterSample++)
	{
		delete GetAt(nParameterSample);
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CGRDParameterSamples::Copy(CONST CGRDParameterSamples *pParameterSamples)
{
	INT  nParameterSample;
	INT  nParameterSamples;
	CGRDParameterSample  *pParameterSample;

	for (nParameterSample = 0, nParameterSamples = (INT)pParameterSamples->GetSize(), RemoveAll(); nParameterSample < nParameterSamples; nParameterSample++)
	{
		if ((pParameterSample = new CGRDParameterSample) != (CGRDParameterSample *)NULL)
		{
			pParameterSample->Copy(pParameterSamples->GetAt(nParameterSample));
			InsertAt(nParameterSample, pParameterSample, 1);
			continue;
		}
		RemoveAll();
		break;
	}
	if (nParameterSample == nParameterSamples)
	{
		m_szName = pParameterSamples->m_szName;
		m_fRange[0] = pParameterSamples->m_fRange[0];
		m_fRange[1] = pParameterSamples->m_fRange[1];
		m_bInterruption = pParameterSamples->m_bInterruption;
		m_bRange = pParameterSamples->m_bRange;
		m_tPlot = pParameterSamples->m_tPlot;
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDParameterSamples::Compare(CONST CGRDParameterSamples *pParameterSamples) CONST
{
	INT  nParameterSample;
	INT  nParameterSamples;

	for (nParameterSample = 0, nParameterSamples = (pParameterSamples->m_szName == m_szName && pParameterSamples->m_fRange[0] == m_fRange[0] && pParameterSamples->m_fRange[1] == m_fRange[1] && pParameterSamples->m_bRange == m_bRange && pParameterSamples->m_tPlot == m_tPlot && pParameterSamples->m_bInterruption == m_bInterruption && pParameterSamples->GetSize() == GetSize()) ? (INT)GetSize() : -1; nParameterSample < nParameterSamples; nParameterSample++)
	{
		if (!pParameterSamples->GetAt(nParameterSample)->Compare(GetAt(nParameterSample))) break;
		continue;
	}
	return((nParameterSample == nParameterSamples) ? TRUE : FALSE);
}

INT CGRDParameterSamples::FindIndex(CONST CGRDParameterSample *pParameterSample, BOOL bInsert) CONST
{
	INT  nIndex;
	INT  nCount;

	if (pParameterSample->IsInitialized())
	{
		if ((nIndex = FindIndex(pParameterSample->GetUpdateTime(), bInsert)) >= 0 && !bInsert)
		{
			for (nCount = (INT)GetSize(); !pParameterSample->Compare(GetAt(nIndex)) && nIndex < nCount; )
			{
				nIndex++;
				continue;
			}
			return((nIndex < nCount) ? nIndex : -1);
		}
		return nIndex;
	}
	return -1;
}
INT CGRDParameterSamples::FindIndex(CONST CTimeTag &tTime, BOOL bInsert) CONST
{
	INT  nIndex;
	INT  nMinIndex;
	INT  nMaxIndex;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex = (nMinIndex + nMaxIndex) / 2)
	{
		if ((!bInsert  &&  tTime > GetAt(nIndex)->GetUpdateTime()) || (bInsert  &&  tTime >= GetAt(nIndex)->GetUpdateTime()))
		{
			nMinIndex = nIndex + 1;
			continue;
		}
		nMaxIndex = nIndex;
	}
	return(((!bInsert  &&  nIndex < GetSize()) || (bInsert  &&  nIndex <= GetSize())) ? nIndex : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CGRDParameterPlots

CGRDParameterPlots::CGRDParameterPlots() : CPtrArray()
{
	m_tRange[0] = 0;
	m_tRange[1] = 0;
	m_bRange = FALSE;
}

CGRDParameterPlots::~CGRDParameterPlots()
{
	RemoveAll();
}

VOID CGRDParameterPlots::SetUpdateRange(CONST CTimeTag &tStartTime, CONST CTimeTag &tStopTime)
{
	for (m_tRange[0] = tStartTime, m_tRange[1] = tStopTime, m_bRange = FALSE; tStartTime <= tStopTime && tStartTime > 0 && tStopTime > 0; )
	{
		m_bRange = TRUE;
		break;
	}
}

BOOL CGRDParameterPlots::GetUpdateRange(CTimeTag &tStartTime, CTimeTag &tStopTime) CONST
{
	tStartTime = m_tRange[0];
	tStopTime = m_tRange[1];
	return m_bRange;
}

INT CGRDParameterPlots::Add(CGRDParameterSamples *pParameterSamples)
{
	return((INT)CPtrArray::Add(pParameterSamples));
}

CGRDParameterSamples *CGRDParameterPlots::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CGRDParameterSamples *)CPtrArray::GetAt(nIndex) : (CGRDParameterSamples *)NULL);
}

CGRDParameterSamples *CGRDParameterPlots::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CGRDParameterSamples *)CPtrArray::GetAt(nIndex) : (CGRDParameterSamples *)NULL);
}

VOID CGRDParameterPlots::RemoveAll()
{
	INT  nPlot;
	INT  nPlots;

	for (nPlot = 0, nPlots = (INT)GetSize(), m_tRange[0] = m_tRange[1] = 0, m_bRange = FALSE; nPlot < nPlots; nPlot++)
	{
		delete GetAt(nPlot);
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CGRDParameterPlots::Copy(CONST CGRDParameterPlots *pPlots)
{
	INT  nPlot;
	INT  nPlots;
	CGRDParameterSamples  *pParameterSamples;

	for (nPlot = 0, nPlots = (INT)pPlots->GetSize(), RemoveAll(); nPlot < nPlots; nPlot++)
	{
		if ((pParameterSamples = new CGRDParameterSamples))
		{
			if (pParameterSamples->Copy(pPlots->GetAt(nPlot)))
			{
				if (Add(pParameterSamples) < 0)
				{
					delete pParameterSamples;
					break;
				}
				continue;
			}
			delete pParameterSamples;
		}
		break;
	}
	if (nPlot == nPlots)
	{
		m_tRange[0] = pPlots->m_tRange[0];
		m_tRange[1] = pPlots->m_tRange[1];
		m_bRange = pPlots->m_bRange;
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDParameterPlots::Compare(CONST CGRDParameterPlots *pPlots) CONST
{
	INT  nPlot;
	INT  nPlots;

	for (nPlot = 0, nPlots = (pPlots->m_tRange[0] == m_tRange[0] && pPlots->m_tRange[1] == m_tRange[1] && pPlots->m_bRange == m_bRange && pPlots->GetSize() == GetSize()) ? (INT)pPlots->GetSize() : -1; nPlot < nPlots; nPlot++)
	{
		if (!pPlots->GetAt(nPlot)->Compare(GetAt(nPlot))) break;
		continue;
	}
	return((nPlot == nPlots) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CGRDMarker

CGRDMarker::CGRDMarker() : CPoint(0, 0)
{
	return;
}
CGRDMarker::CGRDMarker(CONST POINT &pt) : CPoint(pt)
{
	return;
}

VOID CGRDMarker::Copy(CONST CGRDMarker *pMarker)
{
	x = pMarker->x;
	y = pMarker->y;
}

BOOL CGRDMarker::Compare(CONST CGRDMarker *pMarker) CONST
{
	return((pMarker->x == x  &&  pMarker->y == y) ? TRUE : FALSE);
}

BOOL CGRDMarker::Map(CByteArray &nInfo) CONST
{
	DATA  sData;

	for (sData.ptPosition.x = x, sData.ptPosition.y = y, nInfo.SetSize((sData.cbSize = sizeof(DATA))); nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDMarker::Unmap(CONST CByteArray &nInfo)
{
	DATA  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize; )
	{
		x = sData.ptPosition.x;
		y = sData.ptPosition.y;
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CGRDMarkers

CGRDMarkers::CGRDMarkers() : CPtrArray()
{
	return;
}

CGRDMarkers::~CGRDMarkers()
{
	RemoveAll();
}

INT CGRDMarkers::Add(CGRDMarker *pMarker)
{
	INT  nIndex;

	if ((nIndex = FindIndex(CPoint(pMarker->x, pMarker->y), TRUE)) >= 0) InsertAt(nIndex, pMarker, 1);
	return nIndex;
}

INT CGRDMarkers::Find(CONST POINT &pt, INT nScope) CONST
{
	INT  nMarker;
	INT  nMarkers;
	CRect  rMarker;
	CGRDMarker  *pMarker;

	for (nMarker = 0, nMarkers = (nScope > 0) ? (INT)GetSize() : 0, rMarker.SetRect(pt.x - nScope, pt.y - nScope, pt.x + nScope + 1, pt.y + nScope + 1); nMarker < nMarkers; nMarker++)
	{
		if ((pMarker = GetAt(nMarker)) && rMarker.PtInRect(CPoint(pMarker->x, pMarker->y))) break;
		continue;
	}
	return((nScope > 0) ? ((nMarker < nMarkers) ? nMarker : -1) : FindIndex(pt));
}

CGRDMarker *CGRDMarkers::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CGRDMarker *)CPtrArray::GetAt(nIndex) : (CGRDMarker *)NULL);
}

CGRDMarker *CGRDMarkers::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CGRDMarker *)CPtrArray::GetAt(nIndex) : (CGRDMarker *)NULL);
}

VOID CGRDMarkers::RemoveAll()
{
	INT  nMarker;
	INT  nMarkers;

	for (nMarker = 0, nMarkers = (INT)GetSize(); nMarker < nMarkers; nMarker++)
	{
		delete GetAt(nMarker);
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CGRDMarkers::Copy(CONST CGRDMarkers *pMarkers)
{
	INT  nMarker;
	INT  nMarkers;
	CGRDMarker  *pMarker;

	for (nMarker = 0, nMarkers = (INT)pMarkers->GetSize(), RemoveAll(); nMarker < nMarkers; nMarker++)
	{
		if ((pMarker = new CGRDMarker) != (CGRDMarker *)NULL)
		{
			pMarker->Copy(pMarkers->GetAt(nMarker));
			InsertAt(nMarker, pMarker, 1);
			continue;
		}
		break;
	}
	return((nMarker == nMarkers) ? TRUE : FALSE);
}

BOOL CGRDMarkers::Compare(CONST CGRDMarkers *pMarkers) CONST
{
	INT  nMarker;
	INT  nMarkers;

	for (nMarker = 0, nMarkers = (pMarkers->GetSize() == GetSize()) ? (INT)GetSize() : -1; nMarker < nMarkers; nMarker++)
	{
		if (!pMarkers->GetAt(nMarker)->Compare(GetAt(nMarker))) break;
		continue;
	}
	return((nMarker == nMarkers) ? TRUE : FALSE);
}

BOOL CGRDMarkers::Map(CByteArray &nInfo) CONST
{
	INT  nMarker;
	INT  nMarkers;
	CByteArray  nMarkerData;
	CGRDMarker  *pMarker;

	for (nMarker = 0, nMarkers = (INT)GetSize(), nInfo.RemoveAll(); nMarker < nMarkers; nMarker++)
	{
		if ((pMarker = GetAt(nMarker)) && pMarker->Map(nMarkerData) && nInfo.Append(nMarkerData) >= 0) continue;
		break;
	}
	return((nMarker == nMarkers) ? TRUE : FALSE);
}

BOOL CGRDMarkers::Unmap(CONST CByteArray &nInfo)
{
	INT  cbMarker;
	INT  cbMarkers;
	CByteArray  nMarkerData;
	CGRDMarker  *pMarker;

	for (cbMarkers = 0, RemoveAll(); cbMarkers < nInfo.GetSize(); cbMarkers += cbMarker)
	{
		for (CopyMemory(&cbMarker, nInfo.GetData() + cbMarkers, sizeof(cbMarker)), nMarkerData.SetSize(max(min(cbMarker, nInfo.GetSize() - cbMarkers), 0)); nMarkerData.GetSize() >= 0; )
		{
			CopyMemory(nMarkerData.GetData(), nInfo.GetData() + cbMarkers, nMarkerData.GetSize());
			break;
		}
		if ((pMarker = new CGRDMarker))
		{
			if (pMarker->Unmap(nMarkerData) && Add(pMarker) >= 0) continue;
			delete pMarker;
		}
		break;
	}
	return((cbMarkers == nInfo.GetSize()) ? TRUE : FALSE);
}

INT CGRDMarkers::FindIndex(CONST POINT &pt, BOOL bInsert) CONST
{
	INT  nIndex;
	INT  nMinIndex;
	INT  nMaxIndex;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex = (!bInsert) ? nMinIndex : nMaxIndex; nIndex < nMaxIndex; nIndex++)
	{
		if (CGRDMarker(pt).Compare(GetAt(nIndex))) break;
		continue;
	}
	return(((!bInsert  &&  nIndex < nMaxIndex) || (bInsert  &&  nIndex <= nMaxIndex)) ? nIndex : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CGRDSettingsLayoutPage property page

IMPLEMENT_DYNCREATE(CGRDSettingsLayoutPage, CLocalePropertyPage)

CGRDSettingsLayoutPage::CGRDSettingsLayoutPage() : CLocalePropertyPage(CGRDSettingsLayoutPage::IDD)
{
	//{{AFX_DATA_INIT(CGRDSettingsLayoutPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CGRDSettingsLayoutPage::Initialize()
{
	CGRDLayout  cLayout;
	CGRDOpenDialog  *pDialog;

	if (((pDialog = GetParentDialog()->GetParentDialog()) && (pDialog->GetLayout(cLayout, m_nColumns[0]) || GetParentDisplay()->GetLayout(cLayout, m_nColumns[0])) && (pDialog->GetLayoutColors(m_nColors[0]) || GetParentDisplay()->GetOolColors(m_nColors[0])) && (pDialog->GetLayoutTitleFont(&m_fntTitle[0]) || GetParentDisplay()->GetTitleFont(&m_fntTitle[0])) && (pDialog->GetLayoutItemsFont(&m_fntItems[0]) || GetParentDisplay()->GetItemsFont(&m_fntItems[0])) && (pDialog->GetLayoutValuesFont(&m_fntValues[0]) || GetParentDisplay()->GetValuesFont(&m_fntValues[0])) && (pDialog->GetLayoutAxesFont(&m_fntAxes[0]) || GetParentDisplay()->GetAxesFont(&m_fntAxes[0]))) || (GetParentDisplay()->GetLayout(cLayout, m_nColumns[0]) && GetParentDisplay()->GetOolColors(m_nColors[0]) && GetParentDisplay()->GetTitleFont(&m_fntTitle[0]) && GetParentDisplay()->GetItemsFont(&m_fntItems[0]) && GetParentDisplay()->GetValuesFont(&m_fntValues[0]) && GetParentDisplay()->GetAxesFont(&m_fntAxes[0])))
	{
		m_bInvalidData[0] = m_bInvalidData[1] = (!pDialog || !pDialog->GetLayoutInvalidDataMode(m_bInvalidData[0])) ? GetParentDisplay()->IsInvalidDataModeEnabled() : m_bInvalidData[0];
		m_bBadData[0] = m_bBadData[1] = (!pDialog || !pDialog->GetLayoutBadDataMode(m_bBadData[0])) ? GetParentDisplay()->IsBadDataModeEnabled() : m_bBadData[0];
		m_bToolTips[0] = m_bToolTips[1] = (!pDialog || !pDialog->GetLayoutToolTipMode(m_bToolTips[0])) ? GetParentDisplay()->IsToolTipModeEnabled() : m_bToolTips[0];
		CopyMemory(&m_fntTitle[1], &m_fntTitle[0], sizeof(LOGFONT));
		CopyMemory(&m_fntItems[1], &m_fntItems[0], sizeof(LOGFONT));
		CopyMemory(&m_fntValues[1], &m_fntValues[0], sizeof(LOGFONT));
		CopyMemory(&m_fntAxes[1], &m_fntAxes[0], sizeof(LOGFONT));
		m_nColumns[1].Copy(m_nColumns[0]);
		m_nColors[1].Copy(m_nColors[0]);
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDSettingsLayoutPage::GetLayout(CUIntArray &nColumns) CONST
{
	nColumns.Copy(m_nColumns[0]);
	return((nColumns.GetSize() > 0) ? Check(FALSE) : FALSE);
}

BOOL CGRDSettingsLayoutPage::GetColors(CUIntArray &nColors) CONST
{
	nColors.Copy(m_nColors[0]);
	return Check(FALSE);
}

BOOL CGRDSettingsLayoutPage::GetTitleFont(LPLOGFONT pTitleFont) CONST
{
	CopyMemory(pTitleFont, &m_fntTitle[0], sizeof(LOGFONT));
	return Check(FALSE);
}

BOOL CGRDSettingsLayoutPage::GetItemsFont(LPLOGFONT pItemsFont) CONST
{
	CopyMemory(pItemsFont, &m_fntItems[0], sizeof(LOGFONT));
	return Check(FALSE);
}

BOOL CGRDSettingsLayoutPage::GetValuesFont(LPLOGFONT pValuesFont) CONST
{
	CopyMemory(pValuesFont, &m_fntValues[0], sizeof(LOGFONT));
	return Check(FALSE);
}

BOOL CGRDSettingsLayoutPage::GetAxesFont(LPLOGFONT pAxesFont) CONST
{
	CopyMemory(pAxesFont, &m_fntAxes[0], sizeof(LOGFONT));
	return Check(FALSE);
}

BOOL CGRDSettingsLayoutPage::GetInvalidDataMode(BOOL &bEnable) CONST
{
	bEnable = m_bInvalidData[0];
	return Check(FALSE);
}

BOOL CGRDSettingsLayoutPage::GetBadDataMode(BOOL &bEnable) CONST
{
	bEnable = m_bBadData[0];
	return Check(FALSE);
}

BOOL CGRDSettingsLayoutPage::GetToolTipMode(BOOL &bEnable) CONST
{
	bEnable = m_bToolTips[0];
	return Check(FALSE);
}

CGRDSettingsDialog *CGRDSettingsLayoutPage::GetParentDialog() CONST
{
	return((CGRDSettingsDialog *)CLocalePropertyPage::GetParent());
}

CGRDWnd *CGRDSettingsLayoutPage::GetParentDisplay() CONST
{
	return((CGRDWnd *)GetParentDialog()->GetParentDisplay());
}

BOOL CGRDSettingsLayoutPage::EnumLayoutColumns()
{
	INT  nColumn;
	INT  nColumns;
	CStringArray  szColumns;

	szColumns.Add(LookupColumnName(GRD_TITLEITEM_ID));
	szColumns.Add(LookupColumnName(GRD_TITLEITEM_DESCRIPTION));
	szColumns.Add(LookupColumnName(GRD_TITLEITEM_VALUE));
	szColumns.Add(LookupColumnName(GRD_TITLEITEM_UNIT));
	szColumns.Add(LookupColumnName(GRD_TITLEITEM_RANGE));
	szColumns.Add(LookupColumnName(GRD_TITLEITEM_LINE));
	szColumns.Add(LookupColumnName(GRD_TITLEITEM_CHANGETMUNIT));
	szColumns.Add(LookupColumnName(GRD_TITLEITEM_CHANGETIME));
	szColumns.Add(LookupColumnName(GRD_TITLEITEM_UPDATETMUNIT));
	szColumns.Add(LookupColumnName(GRD_TITLEITEM_UPDATETIME));
	for (nColumn = 0, nColumns = (INT)szColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_NAME, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szColumns.GetAt(nColumn));
		continue;
	}
	SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_NAME, CB_SETCURSEL);
	return((nColumn == nColumns) ? TRUE : FALSE);
}

BOOL CGRDSettingsLayoutPage::EnumLayoutColors()
{
	return((SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_COLORS_STATUS, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_GRDSETTINGS_LAYOUTPAGE_NOOOL)) >= 0 && SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_COLORS_STATUS, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_GRDSETTINGS_LAYOUTPAGE_SOFTOOL)) >= 0 && SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_COLORS_STATUS, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_GRDSETTINGS_LAYOUTPAGE_HARDOOL)) >= 0 && SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_COLORS_STATUS, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_GRDSETTINGS_LAYOUTPAGE_DELTAOOL)) >= 0 && SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_COLORS_STATUS, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_GRDSETTINGS_LAYOUTPAGE_CONSISTENCYOOL)) >= 0) ? TRUE : FALSE);
}

BOOL CGRDSettingsLayoutPage::EnumFontLocations()
{
	SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_LOCATION, CB_RESETCONTENT);
	SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_LOCATION, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_GRDSETTINGS_LAYOUTPAGE_TITLELOCATION));
	SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_LOCATION, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_GRDSETTINGS_LAYOUTPAGE_PARAMETERSLOCATION));
	SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_LOCATION, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_GRDSETTINGS_LAYOUTPAGE_VALUESLOCATION));
	SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_LOCATION, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_GRDSETTINGS_LAYOUTPAGE_AXESLOCATION));
	if (SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_LOCATION, CB_GETCOUNT) > 0)
	{
		SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_LOCATION, CB_SETCURSEL);
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDSettingsLayoutPage::ShowLayoutColumns()
{
	INT  nColumn;
	INT  nColumns;

	for (nColumn = 0, nColumns = (INT)m_nColumns[0].GetSize(), SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_VIEW, LVM_DELETEALLITEMS), m_nColumnIndex = 0; nColumn < nColumns; nColumn++)
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
		if ((!nColumn  &&  Listview_InsertText(GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_VIEW), 0, EMPTYSTRING)) || (nColumn > 0 && Listview_SetText(GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_VIEW), 0, nColumn, EMPTYSTRING))) continue;
		break;
	}
	return((nColumn == nColumns) ? SetCurLayoutColumn() : FALSE);
}

VOID CGRDSettingsLayoutPage::ShowLayoutFontDetails()
{
	INT  nSize;
	INT  nSizes;
	INT  nStyle;
	INT  nStyles;
	BOOL  bUnderlined;
	CString  szFontArea;
	CStringArray  szSizes;
	CStringArray  szStyles;
	CFontTools  cFontTools;

	for (SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_RESETCONTENT), SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_RESETCONTENT), GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_LOCATION)->GetWindowText(szFontArea), SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)((szFontArea == STRING(IDS_GRDSETTINGS_LAYOUTPAGE_TITLELOCATION)) ? m_fntTitle[0].lfFaceName : ((szFontArea == STRING(IDS_GRDSETTINGS_LAYOUTPAGE_PARAMETERSLOCATION)) ? m_fntItems[0].lfFaceName : ((szFontArea == STRING(IDS_GRDSETTINGS_LAYOUTPAGE_VALUESLOCATION)) ? m_fntValues[0].lfFaceName : m_fntAxes[0].lfFaceName))))); (szFontArea == STRING(IDS_GRDSETTINGS_LAYOUTPAGE_TITLELOCATION) && cFontTools.EnumerateFont(m_fntTitle[0].lfFaceName, szStyles, szSizes, bUnderlined)) || (szFontArea == STRING(IDS_GRDSETTINGS_LAYOUTPAGE_PARAMETERSLOCATION) && cFontTools.EnumerateFont(m_fntItems[0].lfFaceName, szStyles, szSizes, bUnderlined)) || (szFontArea == STRING(IDS_GRDSETTINGS_LAYOUTPAGE_VALUESLOCATION) && cFontTools.EnumerateFont(m_fntValues[0].lfFaceName, szStyles, szSizes, bUnderlined)) || (szFontArea == STRING(IDS_GRDSETTINGS_LAYOUTPAGE_AXESLOCATION) && cFontTools.EnumerateFont(m_fntAxes[0].lfFaceName, szStyles, szSizes, bUnderlined)); )
	{
		for (nStyle = 0, nStyles = (INT)szStyles.GetSize(); nStyle < nStyles; nStyle++) SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szStyles.GetAt(nStyle));
		for (nSize = 0, nSizes = (INT)szSizes.GetSize(); nSize < nSizes; nSize++) SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szSizes.GetAt(nSize));
		break;
	}
	if (szFontArea == STRING(IDS_GRDSETTINGS_LAYOUTPAGE_TITLELOCATION))
	{
		SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_fntTitle[0])), 0));
		SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntTitle[0])), max(SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntTitle[1])), 0)));
	}
	if (szFontArea == STRING(IDS_GRDSETTINGS_LAYOUTPAGE_PARAMETERSLOCATION))
	{
		SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_fntItems[0])), 0));
		SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntItems[0])), max(SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntItems[1])), 0)));
	}
	if (szFontArea == STRING(IDS_GRDSETTINGS_LAYOUTPAGE_VALUESLOCATION))
	{
		SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_fntValues[0])), 0));
		SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntValues[0])), max(SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntValues[1])), 0)));
	}
	if (szFontArea == STRING(IDS_GRDSETTINGS_LAYOUTPAGE_AXESLOCATION))
	{
		SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontStyle(&m_fntAxes[0])), 0));
		SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntAxes[0])), max(SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cFontTools.TranslateFontSize(&m_fntAxes[1])), 0)));
	}
	GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_STYLE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_STYLE)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SIZE_STATIC)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SIZE)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SAMPLE)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CGRDSettingsLayoutPage::ShowLayoutFontSample()
{
	CRect  rSampleText;

	GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->GetWindowRect(rSampleText);
	ScreenToClient(rSampleText);
	InvalidateRect(rSampleText);
	UpdateWindow();
}

BOOL CGRDSettingsLayoutPage::InsertLayoutColumn(INT nIndex, LPCTSTR pszColumn)
{
	m_szColumns.InsertAt(nIndex, pszColumn);
	m_nColumnIndex = (nIndex <= m_nColumnIndex) ? (INT)min(m_nColumnIndex + 1, m_szColumns.GetSize() - 1) : m_nColumnIndex;
	return Listview_InsertColumn(GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_VIEW), nIndex, m_szColumns.GetAt(nIndex), CalcColumnWidth(pszColumn));
}

BOOL CGRDSettingsLayoutPage::ModifyLayoutColumn(INT nIndex, LPCTSTR pszColumn)
{
	m_szColumns.SetAt(nIndex, pszColumn);
	return Listview_SetColumn(GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_VIEW), nIndex, m_szColumns.GetAt(nIndex), CalcColumnWidth(pszColumn));
}

BOOL CGRDSettingsLayoutPage::RemoveLayoutColumn(INT nIndex)
{
	if (Listview_DeleteColumn(GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_VIEW), nIndex))
	{
		m_nColumnIndex = (nIndex >= m_nColumnIndex) ? ((nIndex > m_nColumnIndex) ? m_nColumnIndex : 0) : max(m_nColumnIndex - 1, 0);
		m_szColumns.RemoveAt(nIndex);
		return SetCurLayoutColumn(m_nColumnIndex);
	}
	return FALSE;
}

BOOL CGRDSettingsLayoutPage::SetCurLayoutColumn(INT nIndex)
{
	if (nIndex < m_nColumns[0].GetSize())
	{
		for (m_szColumns.SetAt(m_nColumnIndex, (m_szColumns.GetAt(m_nColumnIndex).Right(lstrlen(STRING(IDS_GRDSETTINGS_LAYOUTPAGE_COLUMNMARKER))) == STRING(IDS_GRDSETTINGS_LAYOUTPAGE_COLUMNMARKER)) ? (m_szColumns.GetAt(m_nColumnIndex).Left(m_szColumns.GetAt(m_nColumnIndex).GetLength() - lstrlen(STRING(IDS_GRDSETTINGS_LAYOUTPAGE_COLUMNMARKER)))) : m_szColumns.GetAt(m_nColumnIndex)), m_szColumns.SetAt(nIndex, m_szColumns.GetAt(nIndex) + STRING(IDS_GRDSETTINGS_LAYOUTPAGE_COLUMNMARKER)); TRUE; )
		{
			Listview_SetColumn(GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_VIEW), m_nColumnIndex, m_szColumns.GetAt(m_nColumnIndex), CalcColumnWidth(m_szColumns.GetAt(m_nColumnIndex)));
			Listview_SetColumn(GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_VIEW), nIndex, m_szColumns.GetAt(nIndex), CalcColumnWidth(m_szColumns.GetAt((m_nColumnIndex = nIndex))));
			break;
		}
		GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_INSERTBEFORE)->EnableWindow((m_nColumnIndex > 0) ? CheckLayoutColumn() : FALSE);
		GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_INSERTAFTER)->EnableWindow((m_nColumnIndex >= 0) ? CheckLayoutColumn() : FALSE);
		GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_REMOVE)->EnableWindow((m_nColumnIndex > 0) ? TRUE : FALSE);
		return TRUE;
	}
	return FALSE;
}

INT CGRDSettingsLayoutPage::GetCurLayoutColumn() CONST
{
	return m_nColumnIndex;
}

BOOL CGRDSettingsLayoutPage::CheckLayoutColumn() CONST
{
	INT  nColumn;
	INT  nColumns;
	CString  szColumn;

	GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_NAME)->GetWindowText(szColumn);
	for (nColumn = 0, nColumns = (INT)m_nColumns[0].GetSize(); nColumn < nColumns; nColumn++)
	{
		if (m_nColumns[0].GetAt(nColumn) == LookupColumnName(szColumn)) break;
		continue;
	}
	return((nColumn == nColumns) ? TRUE : FALSE);
}

CString CGRDSettingsLayoutPage::LookupColumnName(UINT nColumn) CONST
{
	if (nColumn == GRD_TITLEITEM_ID) return STRING(IDS_GRD_TITLEITEM_ID);
	if (nColumn == GRD_TITLEITEM_DESCRIPTION) return STRING(IDS_GRD_TITLEITEM_DESCRIPTION);
	if (nColumn == GRD_TITLEITEM_VALUE) return STRING(IDS_GRD_TITLEITEM_VALUE);
	if (nColumn == GRD_TITLEITEM_UNIT) return STRING(IDS_GRD_TITLEITEM_UNIT);
	if (nColumn == GRD_TITLEITEM_RANGE) return STRING(IDS_GRD_TITLEITEM_RANGE);
	if (nColumn == GRD_TITLEITEM_LINE) return STRING(IDS_GRD_TITLEITEM_LINE);
	if (nColumn == GRD_TITLEITEM_CHANGETMUNIT) return STRING(IDS_GRD_TITLEITEM_CHANGETMUNIT);
	if (nColumn == GRD_TITLEITEM_CHANGETIME) return STRING(IDS_GRD_TITLEITEM_CHANGETIME);
	if (nColumn == GRD_TITLEITEM_UPDATETMUNIT) return STRING(IDS_GRD_TITLEITEM_UPDATETMUNIT);
	if (nColumn == GRD_TITLEITEM_UPDATETIME) return STRING(IDS_GRD_TITLEITEM_UPDATETIME);
	return EMPTYSTRING;
}
UINT CGRDSettingsLayoutPage::LookupColumnName(LPCTSTR pszColumn) CONST
{
	if (!_tcsncmp(pszColumn, STRING(IDS_GRD_TITLEITEM_ID), lstrlen(STRING(IDS_GRD_TITLEITEM_ID)))) return GRD_TITLEITEM_ID;
	if (!_tcsncmp(pszColumn, STRING(IDS_GRD_TITLEITEM_DESCRIPTION), lstrlen(STRING(IDS_GRD_TITLEITEM_DESCRIPTION)))) return GRD_TITLEITEM_DESCRIPTION;
	if (!_tcsncmp(pszColumn, STRING(IDS_GRD_TITLEITEM_VALUE), lstrlen(STRING(IDS_GRD_TITLEITEM_VALUE)))) return GRD_TITLEITEM_VALUE;
	if (!_tcsncmp(pszColumn, STRING(IDS_GRD_TITLEITEM_UNIT), lstrlen(STRING(IDS_GRD_TITLEITEM_UNIT)))) return GRD_TITLEITEM_UNIT;
	if (!_tcsncmp(pszColumn, STRING(IDS_GRD_TITLEITEM_RANGE), lstrlen(STRING(IDS_GRD_TITLEITEM_RANGE)))) return GRD_TITLEITEM_RANGE;
	if (!_tcsncmp(pszColumn, STRING(IDS_GRD_TITLEITEM_LINE), lstrlen(STRING(IDS_GRD_TITLEITEM_LINE)))) return GRD_TITLEITEM_LINE;
	if (!_tcsncmp(pszColumn, STRING(IDS_GRD_TITLEITEM_CHANGETMUNIT), lstrlen(STRING(IDS_GRD_TITLEITEM_CHANGETMUNIT)))) return GRD_TITLEITEM_CHANGETMUNIT;
	if (!_tcsncmp(pszColumn, STRING(IDS_GRD_TITLEITEM_CHANGETIME), lstrlen(STRING(IDS_GRD_TITLEITEM_CHANGETIME)))) return GRD_TITLEITEM_CHANGETIME;
	if (!_tcsncmp(pszColumn, STRING(IDS_GRD_TITLEITEM_UPDATETMUNIT), lstrlen(STRING(IDS_GRD_TITLEITEM_UPDATETMUNIT)))) return GRD_TITLEITEM_UPDATETMUNIT;
	if (!_tcsncmp(pszColumn, STRING(IDS_GRD_TITLEITEM_UPDATETIME), lstrlen(STRING(IDS_GRD_TITLEITEM_UPDATETIME)))) return GRD_TITLEITEM_UPDATETIME;
	return 0;
}

INT CGRDSettingsLayoutPage::CalcColumnsWidth(CONST CUIntArray &nColumns, CUIntArray &nWidths)
{
	INT  nColIndex;
	INT  nColItems;

	for (nColIndex = 0, nColItems = (INT)nColumns.GetSize(), nWidths.RemoveAll(); nColIndex < nColItems; nColIndex++)
	{
		nWidths.Add((nColIndex > 0) ? (nWidths.GetAt(nColIndex - 1) + CalcColumnWidth(LookupColumnName(nColumns.GetAt(nColIndex)))) : CalcColumnWidth(LookupColumnName(nColumns.GetAt(nColIndex))));
		continue;
	}
	return((nWidths.GetSize() == nColItems) ? nColItems : 0);
}

INT CGRDSettingsLayoutPage::CalcColumnWidth(LPCTSTR pszColumn)
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
				nWidth = ((nColumn = LookupColumnName(pszColumn)) == GRD_TITLEITEM_ID) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetGRDIDColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : 0;
				nWidth = (nColumn == GRD_TITLEITEM_DESCRIPTION) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetGRDDescriptionColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == GRD_TITLEITEM_VALUE) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetGRDValueColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == GRD_TITLEITEM_UNIT) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetGRDUnitColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == GRD_TITLEITEM_RANGE) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetGRDRangeColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == GRD_TITLEITEM_LINE) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetGRDLineColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == GRD_TITLEITEM_CHANGETMUNIT) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetGRDChangeTMUnitColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == GRD_TITLEITEM_CHANGETIME) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetGRDChangeTimeColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == GRD_TITLEITEM_UPDATETMUNIT) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetGRDUpdateTMUnitColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (nColumn == GRD_TITLEITEM_UPDATETIME) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetGRDUpdateTimeColumnCharWidth())*tmFont.tmAveCharWidth, pDC->GetTextExtent(pszColumn).cx)) : nWidth;
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

INT CGRDSettingsLayoutPage::CalcColumnIndent() CONST
{
	return 3 * GetSystemMetrics(SM_CXEDGE);
}

BOOL CGRDSettingsLayoutPage::IsModified(BOOL bAll) CONST
{
	INT  nColumn;
	INT  nColumns;
	CFontTools  cFontTools;

	if (IsWindow(GetSafeHwnd()) && !bAll)
	{
		for (nColumn = 0, nColumns = (m_nColumns[0].GetSize() == m_nColumns[1].GetSize() && !lstrcmp(m_fntTitle[0].lfFaceName, m_fntTitle[1].lfFaceName) && (m_fntTitle[0].lfHeight == m_fntTitle[1].lfHeight || cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntTitle[0])) == cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntTitle[1]))) && m_fntTitle[0].lfWeight == m_fntTitle[1].lfWeight && m_fntTitle[0].lfItalic == m_fntTitle[1].lfItalic && !lstrcmp(m_fntItems[0].lfFaceName, m_fntItems[1].lfFaceName) && (m_fntItems[0].lfHeight == m_fntItems[1].lfHeight || cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntItems[0])) == cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntItems[1]))) && m_fntItems[0].lfWeight == m_fntItems[1].lfWeight && m_fntItems[0].lfItalic == m_fntItems[1].lfItalic && !lstrcmp(m_fntValues[0].lfFaceName, m_fntValues[1].lfFaceName) && (m_fntValues[0].lfHeight == m_fntValues[1].lfHeight || cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntValues[0])) == cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntValues[1]))) && m_fntValues[0].lfWeight == m_fntValues[1].lfWeight && m_fntValues[0].lfItalic == m_fntValues[1].lfItalic && !lstrcmp(m_fntAxes[0].lfFaceName, m_fntAxes[1].lfFaceName) && (m_fntAxes[0].lfHeight == m_fntAxes[1].lfHeight || cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntAxes[0])) == cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntAxes[1]))) && m_fntAxes[0].lfWeight == m_fntAxes[1].lfWeight && m_fntAxes[0].lfItalic == m_fntAxes[1].lfItalic && m_nColors[0].GetSize() == m_nColors[1].GetSize() && !memcmp(m_nColors[0].GetData(), m_nColors[1].GetData(), m_nColors[0].GetSize()*sizeof(UINT)) && m_bInvalidData[0] == m_bInvalidData[1] && m_bBadData[0] == m_bBadData[1] && m_bToolTips[0] == m_bToolTips[1]) ? (INT)m_nColumns[0].GetSize() : -1; nColumn < nColumns; nColumn++)
		{
			if (m_nColumns[0].GetAt(nColumn) != m_nColumns[1].GetAt(nColumn)) break;
			continue;
		}
		return((nColumn != nColumns) ? TRUE : FALSE);
	}
	return((bAll) ? CLocalePropertyPage::IsModified() : FALSE);
}

BOOL CGRDSettingsLayoutPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_NAMES)->GetWindowTextLength() > 0 && GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowTextLength() > 0 && GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowTextLength() > 0) : CLocalePropertyPage::Check()) : TRUE);
}

void CGRDSettingsLayoutPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGRDSettingsLayoutPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CGRDSettingsLayoutPage::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_nColors[0].RemoveAll();
	m_nColors[1].RemoveAll();
	m_nColumns[0].RemoveAll();
	m_nColumns[1].RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CGRDSettingsLayoutPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CGRDSettingsLayoutPage)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_INSERTBEFORE, OnInsertColumnBefore)
	ON_BN_CLICKED(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_INSERTAFTER, OnInsertColumnAfter)
	ON_BN_CLICKED(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_REMOVE, OnRemoveColumn)
	ON_BN_CLICKED(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_INVALIDDATA, OnInvalidData)
	ON_BN_CLICKED(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_BADDATA, OnBadData)
	ON_BN_CLICKED(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_TOOLTIPS, OnToolTips)
	ON_CBN_EDITCHANGE(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_NAMES, OnEditchangeFontName)
	ON_CBN_SELCHANGE(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_NAME, OnSelchangeColumnName)
	ON_CBN_SELCHANGE(IDC_GRDSETTINGS_LAYOUTPAGE_COLORS_STATUS, OnSelchangeColorLocation)
	ON_CBN_SELCHANGE(IDC_GRDSETTINGS_LAYOUTPAGE_COLORS_COLOR, OnSelchangeColor)
	ON_CBN_SELCHANGE(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_LOCATION, OnSelchangeFontLocation)
	ON_CBN_SELCHANGE(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_NAMES, OnSelchangeFontName)
	ON_CBN_SELCHANGE(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_STYLE, OnSelchangeFontStyle)
	ON_CBN_SELCHANGE(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SIZE, OnSelchangeFontSize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDSettingsLayoutPage message handlers

BOOL CGRDSettingsLayoutPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	for (CLocalePropertyPage::OnInitDialog(); EnumLayoutColumns() >= 0 && EnumLayoutColors() >= 0 && EnumFontLocations() >= 0; )
	{
		SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_COLORS_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nColors[0].GetAt(GRD_OOLCOLOR_NOLIMIT));
		SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_COLORS_STATUS, CB_SETCURSEL, GRD_OOLCOLOR_NOLIMIT);
		break;
	}
	CheckDlgButton(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_INVALIDDATA, m_bInvalidData[0]);
	CheckDlgButton(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_BADDATA, m_bBadData[0]);
	CheckDlgButton(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_TOOLTIPS, m_bToolTips[0]);
	GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->GetWindowText(m_szFontSampleText);
	GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_NAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_NAME)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_VIEW)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_SHOWDATA)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_INVALIDDATA)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_BADDATA)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_TOOLTIPS)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_COLORS)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_COLORS_STATUS_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_COLORS_STATUS)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_COLORS_COLOR_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_COLORS_COLOR)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_LOCATION_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_LOCATION)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_COMMENT_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_NAMES_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_NAMES)->EnableWindow();
	SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_NAMES, FCB_DIR, CF_EFFECTS | CF_SCREENFONTS);
	SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)m_fntTitle[0].lfFaceName));
	ShowLayoutFontDetails();
	ShowLayoutColumns();
	return TRUE;
}

void CGRDSettingsLayoutPage::OnPaint()
{
	INT  nBkMode;
	CFont  cFont;
	CFont  *pOldFont;
	CRect  rSampleText;
	CString  szFontArea;
	COLORREF  nOldColor;
	CPaintDC  cDC(this);

	for (GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT)->GetWindowRect(rSampleText), GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_LOCATION)->GetWindowText(szFontArea), ScreenToClient(rSampleText); cFont.CreateFontIndirect((szFontArea == STRING(IDS_GRDSETTINGS_LAYOUTPAGE_TITLELOCATION)) ? &m_fntTitle[0] : ((szFontArea == STRING(IDS_GRDSETTINGS_LAYOUTPAGE_PARAMETERSLOCATION)) ? &m_fntItems[0] : ((szFontArea == STRING(IDS_GRDSETTINGS_LAYOUTPAGE_VALUESLOCATION)) ? &m_fntValues[0] : &m_fntAxes[0]))); )
	{
		if ((pOldFont = cDC.SelectObject(&cFont)))
		{
			nBkMode = cDC.SetBkMode(TRANSPARENT);
			nOldColor = cDC.SetTextColor((SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_STYLE, CB_GETCOUNT) > 0 && SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SIZE, CB_GETCOUNT) > 0) ? GetSysColor(COLOR_WINDOWTEXT) : GetSysColor(COLOR_GRAYTEXT));
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

BOOL CGRDSettingsLayoutPage::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	NMLISTVIEW  *pNotifyInfo = (NMLISTVIEW *)lParam;

	if (pNotifyInfo->hdr.idFrom == IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_VIEW)
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

void CGRDSettingsLayoutPage::OnInsertColumnBefore()
{
	INT  nIndex;
	CString  szColumn;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_NAME)->GetWindowText(szColumn); InsertLayoutColumn((nIndex = m_nColumnIndex), szColumn); )
	{
		m_nColumns[0].InsertAt(nIndex, LookupColumnName(szColumn));
		SetCurLayoutColumn(nIndex);
		break;
	}
	GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsLayoutPage::OnInsertColumnAfter()
{
	INT  nIndex;
	CString  szColumn;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_NAME)->GetWindowText(szColumn); InsertLayoutColumn((nIndex = m_nColumnIndex + 1), szColumn); )
	{
		m_nColumns[0].InsertAt(nIndex, LookupColumnName(szColumn));
		SetCurLayoutColumn(nIndex);
		break;
	}
	GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsLayoutPage::OnRemoveColumn()
{
	INT  nIndex;
	CHourglassCursor  cCursor;

	if (RemoveLayoutColumn((nIndex = m_nColumnIndex)))
	{
		m_nColumns[0].RemoveAt(nIndex);
		SetCurLayoutColumn();
	}
	GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsLayoutPage::OnInvalidData()
{
	m_bInvalidData[0] = IsDlgButtonChecked(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_INVALIDDATA);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsLayoutPage::OnBadData()
{
	m_bBadData[0] = IsDlgButtonChecked(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_BADDATA);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsLayoutPage::OnToolTips()
{
	m_bToolTips[0] = IsDlgButtonChecked(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_TOOLTIPS);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsLayoutPage::OnEditchangeFontName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsLayoutPage::OnSelchangeColumnName()
{
	GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_INSERTBEFORE)->EnableWindow((m_nColumnIndex > 0) ? CheckLayoutColumn() : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_INSERTAFTER)->EnableWindow((m_nColumnIndex >= 0) ? CheckLayoutColumn() : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FORMAT_REMOVE)->EnableWindow((m_nColumnIndex > 0) ? TRUE : FALSE);
}

void CGRDSettingsLayoutPage::OnSelchangeColorLocation()
{
	INT  nIndex;

	SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_COLORS_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, ((nIndex = (INT)SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_COLORS_STATUS, CB_GETCURSEL)) < m_nColors[0].GetSize()) ? (LPARAM)m_nColors[0].GetAt(nIndex) : (LPARAM)VGA_COLOR_BLACK);
}

void CGRDSettingsLayoutPage::OnSelchangeColor()
{
	INT  nIndex;

	for (; (nIndex = (INT)SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_COLORS_STATUS, CB_GETCURSEL)) < m_nColors[0].GetSize(); )
	{
		m_nColors[0].SetAt(nIndex, (UINT)SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_COLORS_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_COLORS_COLOR, CB_GETCURSEL)));
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsLayoutPage::OnSelchangeFontLocation()
{
	ShowLayoutFontDetails();
	ShowLayoutFontSample();
}

void CGRDSettingsLayoutPage::OnSelchangeFontName()
{
	CString  szSize;
	CString  szStyle;
	CString  szFontArea;
	CFontTools  cFontTools;

	for (GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_LOCATION)->GetWindowText(szFontArea); szFontArea == STRING(IDS_GRDSETTINGS_LAYOUTPAGE_TITLELOCATION); )
	{
		_tcscpy_s(m_fntTitle[0].lfFaceName, sizeof(m_fntTitle[0].lfFaceName) / sizeof(TCHAR), Combobox_GetText(GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_NAMES), (INT)SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_GETCURSEL)));
		ShowLayoutFontDetails();
		break;
	}
	if (szFontArea == STRING(IDS_GRDSETTINGS_LAYOUTPAGE_PARAMETERSLOCATION))
	{
		_tcscpy_s(m_fntItems[0].lfFaceName, sizeof(m_fntItems[0].lfFaceName) / sizeof(TCHAR), Combobox_GetText(GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_NAMES), (INT)SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_GETCURSEL)));
		ShowLayoutFontDetails();
	}
	if (szFontArea == STRING(IDS_GRDSETTINGS_LAYOUTPAGE_VALUESLOCATION))
	{
		_tcscpy_s(m_fntValues[0].lfFaceName, sizeof(m_fntValues[0].lfFaceName) / sizeof(TCHAR), Combobox_GetText(GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_NAMES), (INT)SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_GETCURSEL)));
		ShowLayoutFontDetails();
	}
	if (szFontArea == STRING(IDS_GRDSETTINGS_LAYOUTPAGE_AXESLOCATION))
	{
		_tcscpy_s(m_fntAxes[0].lfFaceName, sizeof(m_fntAxes[0].lfFaceName) / sizeof(TCHAR), Combobox_GetText(GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_NAMES), (INT)SendDlgItemMessage(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_NAMES, CB_GETCURSEL)));
		ShowLayoutFontDetails();
	}
	if (szFontArea == STRING(IDS_GRDSETTINGS_LAYOUTPAGE_TITLELOCATION))
	{
		GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntTitle[0].lfWeight, m_fntTitle[0].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_fntTitle[0].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_fntTitle[0]);
	}
	if (szFontArea == STRING(IDS_GRDSETTINGS_LAYOUTPAGE_PARAMETERSLOCATION))
	{
		GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntItems[0].lfWeight, m_fntItems[0].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_fntItems[0].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_fntItems[0]);
	}
	if (szFontArea == STRING(IDS_GRDSETTINGS_LAYOUTPAGE_VALUESLOCATION))
	{
		GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntValues[0].lfWeight, m_fntValues[0].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_fntValues[0].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_fntValues[0]);
	}
	if (szFontArea == STRING(IDS_GRDSETTINGS_LAYOUTPAGE_AXESLOCATION))
	{
		GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntAxes[0].lfWeight, m_fntAxes[0].lfItalic);
		cFontTools.TranslateFontSize(szSize, m_fntAxes[0].lfHeight);
		cFontTools.EnumerateFontCharacteristics(&m_fntAxes[0]);
	}
	ShowLayoutFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsLayoutPage::OnSelchangeFontStyle()
{
	CString  szStyle;
	CString  szFontArea;
	CFontTools  cFontTools;

	for (GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_LOCATION)->GetWindowText(szFontArea); szFontArea == STRING(IDS_GRDSETTINGS_LAYOUTPAGE_TITLELOCATION); )
	{
		GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntTitle[0].lfWeight, m_fntTitle[0].lfItalic);
		break;
	}
	if (szFontArea == STRING(IDS_GRDSETTINGS_LAYOUTPAGE_PARAMETERSLOCATION))
	{
		GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntItems[0].lfWeight, m_fntItems[0].lfItalic);
	}
	if (szFontArea == STRING(IDS_GRDSETTINGS_LAYOUTPAGE_VALUESLOCATION))
	{
		GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntValues[0].lfWeight, m_fntValues[0].lfItalic);
	}
	if (szFontArea == STRING(IDS_GRDSETTINGS_LAYOUTPAGE_AXESLOCATION))
	{
		GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_STYLE)->GetWindowText(szStyle);
		cFontTools.TranslateFontStyle(szStyle, m_fntAxes[0].lfWeight, m_fntAxes[0].lfItalic);
	}
	ShowLayoutFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsLayoutPage::OnSelchangeFontSize()
{
	CString  szSize;
	CString  szFontArea;
	CFontTools  cFontTools;

	for (GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_LOCATION)->GetWindowText(szFontArea); szFontArea == STRING(IDS_GRDSETTINGS_LAYOUTPAGE_TITLELOCATION); )
	{
		GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_fntTitle[0].lfHeight);
		break;
	}
	if (szFontArea == STRING(IDS_GRDSETTINGS_LAYOUTPAGE_PARAMETERSLOCATION))
	{
		GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_fntItems[0].lfHeight);
	}
	if (szFontArea == STRING(IDS_GRDSETTINGS_LAYOUTPAGE_VALUESLOCATION))
	{
		GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_fntValues[0].lfHeight);
	}
	if (szFontArea == STRING(IDS_GRDSETTINGS_LAYOUTPAGE_AXESLOCATION))
	{
		GetDlgItem(IDC_GRDSETTINGS_LAYOUTPAGE_FONTS_SIZE)->GetWindowText(szSize);
		cFontTools.TranslateFontSize(szSize, m_fntAxes[0].lfHeight);
	}
	ShowLayoutFontSample();
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CGRDSettingsChartPage property page

IMPLEMENT_DYNCREATE(CGRDSettingsChartPage, CLocalePropertyPage)

CGRDSettingsChartPage::CGRDSettingsChartPage() : CLocalePropertyPage(CGRDSettingsChartPage::IDD)
{
	//{{AFX_DATA_INIT(CGRDSettingsChartPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CGRDSettingsChartPage::Initialize()
{
	CGRDOpenDialog  *pDialog;

	if (((pDialog = GetParentDialog()->GetParentDialog()) && pDialog->GetLayout(m_cLayout[0])) || GetParentDisplay()->GetLayout(m_cLayout[0]))
	{
		if (m_cLayout[0].GetType() != GRDLAYOUT_TYPE_NORMAL  &&  m_cLayout[0].GetType() != GRDLAYOUT_TYPE_STRIPCHART  &&  m_cLayout[0].GetType() != GRDLAYOUT_TYPE_STACKCHART  &&  m_cLayout[0].GetType() != GRDLAYOUT_TYPE_DIAGRAM)
		{
			m_cLayout[0].SetType(GRDLAYOUT_TYPE_NORMAL);
			m_cLayout[0].SetMode(GRDLAYOUT_MODE_NORMAL | GRDLAYOUT_MODE_OVERWRITE);
			m_cLayout[0].SetDuration(SECONDSPERHOUR);
		}
		return m_cLayout[1].Copy(&m_cLayout[0]);
	}
	return FALSE;
}

BOOL CGRDSettingsChartPage::GetLayout(CGRDLayout &cLayout) CONST
{
	return((cLayout.Copy(&m_cLayout[0])) ? Check(FALSE) : FALSE);
}

CGRDSettingsDialog *CGRDSettingsChartPage::GetParentDialog() CONST
{
	return((CGRDSettingsDialog *)CLocalePropertyPage::GetParent());
}

CGRDWnd *CGRDSettingsChartPage::GetParentDisplay() CONST
{
	return((CGRDWnd *)GetParentDialog()->GetParentDisplay());
}

BOOL CGRDSettingsChartPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? !m_cLayout[0].Compare(&m_cLayout[1]) : CLocalePropertyPage::IsModified()) : FALSE);
}

BOOL CGRDSettingsChartPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? ((!IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_TYPE_DIAGRAM) || m_cLayout[0].GetSize() % 2 == 0) && (Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_DAYS)) > 0 || Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_HOURS)) > 0 || Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_MINUTES)) > 0)) : CLocalePropertyPage::Check()) : TRUE);
}

void CGRDSettingsChartPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGRDSettingsChartPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGRDSettingsChartPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CGRDSettingsChartPage)
	ON_BN_CLICKED(IDC_GRDSETTINGS_CHARTPAGE_TYPE_NORMAL, OnTypeNormal)
	ON_BN_CLICKED(IDC_GRDSETTINGS_CHARTPAGE_TYPE_STRIPCHART, OnTypeStripchart)
	ON_BN_CLICKED(IDC_GRDSETTINGS_CHARTPAGE_TYPE_STACKCHART, OnTypeStackchart)
	ON_BN_CLICKED(IDC_GRDSETTINGS_CHARTPAGE_TYPE_DIAGRAM, OnTypeDiagram)
	ON_BN_CLICKED(IDC_GRDSETTINGS_CHARTPAGE_MODES_PLOTTING_NORMAL, OnPlottingNormal)
	ON_BN_CLICKED(IDC_GRDSETTINGS_CHARTPAGE_MODES_PLOTTING_AREA, OnPlottingArea)
	ON_BN_CLICKED(IDC_GRDSETTINGS_CHARTPAGE_MODES_BEHAVIOR_SCROLL, OnPlottingScroll)
	ON_BN_CLICKED(IDC_GRDSETTINGS_CHARTPAGE_MODES_BEHAVIOR_OVERWRITE, OnPlottingOverwrite)
	ON_BN_CLICKED(IDC_GRDSETTINGS_CHARTPAGE_MODES_BEHAVIOR_RESTART, OnPlottingRestart)
	ON_BN_CLICKED(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_WIDTH_USE, OnGraphWidth)
	ON_BN_CLICKED(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_HEIGHT_USE, OnGraphHeight)
	ON_BN_CLICKED(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_HORIZONTAL, OnHorizontalGrids)
	ON_BN_CLICKED(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_VERTICAL, OnVerticalGrids)
	ON_BN_CLICKED(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_HORIZONTAL, OnHorizontalTicks)
	ON_BN_CLICKED(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_VERTICAL, OnVerticalTicks)
	ON_BN_CLICKED(IDC_GRDSETTINGS_CHARTPAGE_DURATION_INTERVAL, OnDurationInterval)
	ON_CBN_SELCHANGE(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_COLOR, OnSelchangeGridsColor)
	ON_CBN_SELCHANGE(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_COLOR, OnSelchangeTicksColor)
	ON_CBN_SELCHANGE(IDC_GRDSETTINGS_CHARTPAGE_BACKGROUND_COLOR, OnSelchangeBackgroundColor)
	ON_CBN_SELCHANGE(IDC_GRDSETTINGS_CHARTPAGE_LABEL_COLOR, OnSelchangeLabelColor)
	ON_CONTROL(SBXN_CHANGE, IDC_GRDSETTINGS_CHARTPAGE_GRAPH_WIDTH_NUMBER, OnSpinchangeWidth)
	ON_CONTROL(SBXN_CHANGE, IDC_GRDSETTINGS_CHARTPAGE_GRAPH_HEIGHT_NUMBER, OnSpinchangeHeight)
	ON_CONTROL(SBXN_CHANGE, IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_HORIZONTAL_NUMBER, OnSpinchangeHorizontalGrids)
	ON_CONTROL(SBXN_CHANGE, IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_VERTICAL_NUMBER, OnSpinchangeVerticalGrids)
	ON_CONTROL(SBXN_CHANGE, IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_HORIZONTAL_NUMBER, OnSpinchangeHorizontalTicks)
	ON_CONTROL(SBXN_CHANGE, IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_VERTICAL_NUMBER, OnSpinchangeVerticalTicks)
	ON_CONTROL(SBXN_CHANGE, IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_WIDTH, OnSpinchangeGridsWidth)
	ON_CONTROL(SBXN_CHANGE, IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_WIDTH, OnSpinchangeTicksWidth)
	ON_CONTROL(SBXN_CHANGE, IDC_GRDSETTINGS_CHARTPAGE_DURATION_DAYS, OnSpinchangeDurationDays)
	ON_CONTROL(SBXN_CHANGE, IDC_GRDSETTINGS_CHARTPAGE_DURATION_HOURS, OnSpinchangeDurationHours)
	ON_CONTROL(SBXN_CHANGE, IDC_GRDSETTINGS_CHARTPAGE_DURATION_MINUTES, OnSpinchangeDurationMinutes)
	ON_CONTROL(SBXN_CHANGE, IDC_GRDSETTINGS_CHARTPAGE_DURATION_INTERVAL_NUMBER, OnSpinchangeDurationInterval)
	ON_CONTROL(SBXN_CHANGE, IDC_GRDSETTINGS_CHARTPAGE_DURATION_UPDATE_NUMBER, OnSpinchangeUpdateInterval)
	ON_CONTROL(SBXN_KILLFOCUS, IDC_GRDSETTINGS_CHARTPAGE_DURATION_DAYS, OnKillFocusDurationDays)
	ON_CONTROL(SBXN_KILLFOCUS, IDC_GRDSETTINGS_CHARTPAGE_DURATION_HOURS, OnKillFocusDurationHours)
	ON_CONTROL(SBXN_KILLFOCUS, IDC_GRDSETTINGS_CHARTPAGE_DURATION_MINUTES, OnKillFocusDurationMinutes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDSettingsChartPage message handlers

BOOL CGRDSettingsChartPage::OnInitDialog()
{
	INT  nGrids[2];
	INT  nTicks[2];
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	Spinbox_SetRange(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_WIDTH_NUMBER), 1, GetSystemMetrics(SM_CXSCREEN));
	Spinbox_SetRange(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_HEIGHT_NUMBER), 1, GetSystemMetrics(SM_CYSCREEN));
	Spinbox_SetRange(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_HORIZONTAL_NUMBER), GRDSETTINGSCHARTPAGE_MINIMUMGRIDS, GRDSETTINGSCHARTPAGE_MAXIMUMGRIDS);
	Spinbox_SetRange(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_WIDTH), GRDSETTINGSCHARTPAGE_MINIMUMGRIDSWIDTH, GRDSETTINGSCHARTPAGE_MAXIMUMGRIDSWIDTH);
	Spinbox_SetRange(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_VERTICAL_NUMBER), GRDSETTINGSCHARTPAGE_MINIMUMGRIDS, GRDSETTINGSCHARTPAGE_MAXIMUMGRIDS);
	Spinbox_SetRange(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_HORIZONTAL_NUMBER), GRDSETTINGSCHARTPAGE_MINIMUMTICKS, GRDSETTINGSCHARTPAGE_MAXIMUMTICKS);
	Spinbox_SetRange(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_WIDTH), GRDSETTINGSCHARTPAGE_MINIMUMTICKSWIDTH, GRDSETTINGSCHARTPAGE_MAXIMUMTICKSWIDTH);
	Spinbox_SetRange(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_VERTICAL_NUMBER), GRDSETTINGSCHARTPAGE_MINIMUMTICKS, GRDSETTINGSCHARTPAGE_MAXIMUMTICKS);
	Spinbox_SetRange(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_DAYS), (SECONDSPERMINUTE*GRDSETTINGSCHARTPAGE_MINIMUMDURATION) / SECONDSPERDAY, (SECONDSPERMINUTE*GRDSETTINGSCHARTPAGE_MAXIMUMDURATION) / SECONDSPERDAY);
	Spinbox_SetRange(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_HOURS), 0, HOURSPERDAY - 1);
	Spinbox_SetRange(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_MINUTES), 0, MINUTESPERHOUR - 1);
	Spinbox_SetRange(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_INTERVAL_NUMBER), GRDSETTINGSCHARTPAGE_MINIMUMPERCENTAGE, GRDSETTINGSCHARTPAGE_MAXIMUMPERCENTAGE - 1);
	Spinbox_SetRange(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_UPDATE_NUMBER), GRDSETTINGSCHARTPAGE_MINIMUMUPDATE, GRDSETTINGSCHARTPAGE_MAXIMUMUPDATE);
	Spinbox_SetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_WIDTH_NUMBER), m_cLayout[0].GetPlotSize().cx);
	Spinbox_SetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_HEIGHT_NUMBER), m_cLayout[0].GetPlotSize().cy);
	Spinbox_SetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_HORIZONTAL_NUMBER), (m_cLayout[0].GetGrids(nGrids[0], nGrids[1])) ? nGrids[0] : 0);
	Spinbox_SetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_WIDTH), m_cLayout[0].GetGridsWidth());
	Spinbox_SetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_VERTICAL_NUMBER), (m_cLayout[0].GetType() != GRDLAYOUT_TYPE_STRIPCHART) ? ((m_cLayout[0].GetGrids(nGrids[0], nGrids[1])) ? nGrids[1] : 0) : (nGrids[1] = 0));
	Spinbox_SetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_HORIZONTAL_NUMBER), (m_cLayout[0].GetTicks(nTicks[0], nTicks[1])) ? nTicks[0] : 0);
	Spinbox_SetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_WIDTH), m_cLayout[0].GetTicksWidth());
	Spinbox_SetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_VERTICAL_NUMBER), (m_cLayout[0].GetTicks(nTicks[0], nTicks[1])) ? nTicks[1] : 0);
	Spinbox_SetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_DAYS), m_cLayout[0].GetDuration().GetDays());
	Spinbox_SetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_HOURS), m_cLayout[0].GetDuration().GetTotalHours() % HOURSPERDAY);
	Spinbox_SetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_MINUTES), m_cLayout[0].GetDuration().GetTotalMinutes() % SECONDSPERMINUTE);
	Spinbox_SetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_INTERVAL_NUMBER), (100 * m_cLayout[0].GetInterval().GetTotalSeconds()) / max(m_cLayout[0].GetDuration().GetTotalSeconds(), 1));
	Spinbox_SetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_UPDATE_NUMBER), m_cLayout[0].GetUpdateInterval().GetTotalMinutes());
	SendDlgItemMessage(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, m_cLayout[0].GetGridsColor());
	SendDlgItemMessage(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, m_cLayout[0].GetTicksColor());
	SendDlgItemMessage(IDC_GRDSETTINGS_CHARTPAGE_BACKGROUND_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, m_cLayout[0].GetBackgroundColor());
	SendDlgItemMessage(IDC_GRDSETTINGS_CHARTPAGE_LABEL_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, m_cLayout[0].GetLabelColor());
	CheckDlgButton(IDC_GRDSETTINGS_CHARTPAGE_TYPE_NORMAL, (m_cLayout[0].GetType() == GRDLAYOUT_TYPE_NORMAL) ? TRUE : FALSE);
	CheckDlgButton(IDC_GRDSETTINGS_CHARTPAGE_TYPE_STRIPCHART, (m_cLayout[0].GetType() == GRDLAYOUT_TYPE_STRIPCHART) ? TRUE : FALSE);
	CheckDlgButton(IDC_GRDSETTINGS_CHARTPAGE_TYPE_STACKCHART, (m_cLayout[0].GetType() == GRDLAYOUT_TYPE_STACKCHART) ? TRUE : FALSE);
	CheckDlgButton(IDC_GRDSETTINGS_CHARTPAGE_TYPE_DIAGRAM, (m_cLayout[0].GetType() == GRDLAYOUT_TYPE_DIAGRAM) ? TRUE : FALSE);
	CheckDlgButton(IDC_GRDSETTINGS_CHARTPAGE_MODES_PLOTTING_NORMAL, (m_cLayout[0].GetMode() & GRDLAYOUT_MODE_NORMAL) ? TRUE : FALSE);
	CheckDlgButton(IDC_GRDSETTINGS_CHARTPAGE_MODES_PLOTTING_AREA, (m_cLayout[0].GetMode() & GRDLAYOUT_MODE_AREA) ? TRUE : FALSE);
	CheckDlgButton(IDC_GRDSETTINGS_CHARTPAGE_MODES_BEHAVIOR_SCROLL, (m_cLayout[0].GetMode() & GRDLAYOUT_MODE_SCROLL) ? TRUE : FALSE);
	CheckDlgButton(IDC_GRDSETTINGS_CHARTPAGE_MODES_BEHAVIOR_OVERWRITE, (m_cLayout[0].GetMode() & GRDLAYOUT_MODE_OVERWRITE) ? TRUE : FALSE);
	CheckDlgButton(IDC_GRDSETTINGS_CHARTPAGE_MODES_BEHAVIOR_RESTART, (m_cLayout[0].GetMode() & GRDLAYOUT_MODE_RESTART) ? TRUE : FALSE);
	CheckDlgButton(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_WIDTH_USE, (m_cLayout[0].GetPlotSize().cx > 0) ? TRUE : FALSE);
	CheckDlgButton(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_HEIGHT_USE, (m_cLayout[0].GetPlotSize().cy > 0) ? TRUE : FALSE);
	CheckDlgButton(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_HORIZONTAL, (nGrids[0] > 0) ? TRUE : FALSE);
	CheckDlgButton(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_VERTICAL, (nGrids[1] > 0) ? TRUE : FALSE);
	CheckDlgButton(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_HORIZONTAL, (nTicks[0] > 0) ? TRUE : FALSE);
	CheckDlgButton(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_VERTICAL, (nTicks[1] > 0) ? TRUE : FALSE);
	CheckDlgButton(IDC_GRDSETTINGS_CHARTPAGE_DURATION_INTERVAL, (m_cLayout[0].GetInterval().GetTotalSeconds() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_TYPE)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_TYPE_NORMAL)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_TYPE_STRIPCHART)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_TYPE_STACKCHART)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_TYPE_DIAGRAM)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_MODES)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_MODES_PLOTTING)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_MODES_PLOTTING_NORMAL)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_MODES_PLOTTING_AREA)->EnableWindow(!IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_TYPE_DIAGRAM));
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_MODES_BEHAVIOR)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_MODES_BEHAVIOR_SCROLL)->EnableWindow(!IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_TYPE_DIAGRAM));
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_MODES_BEHAVIOR_OVERWRITE)->EnableWindow(!IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_TYPE_DIAGRAM));
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_MODES_BEHAVIOR_RESTART)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_WIDTH)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_WIDTH_USE)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_WIDTH_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_WIDTH_USE));
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_WIDTH_NUMBER)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_WIDTH_USE));
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_HEIGHT)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_HEIGHT_USE)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_HEIGHT_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_HEIGHT_USE));
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_HEIGHT_NUMBER)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_HEIGHT_USE));
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_HORIZONTAL)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_HORIZONTAL_NUMBER)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_HORIZONTAL));
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_WIDTH)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_HORIZONTAL) || IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_VERTICAL));
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_VERTICAL)->EnableWindow(!IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_TYPE_STRIPCHART));
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_VERTICAL_NUMBER)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_VERTICAL));
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_COLOR_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_COLOR)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_HORIZONTAL)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_HORIZONTAL_NUMBER)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_HORIZONTAL));
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_WIDTH)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_HORIZONTAL) || IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_VERTICAL));
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_VERTICAL)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_VERTICAL_NUMBER)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_VERTICAL));
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_COLOR_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_COLOR)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_DAYS_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_DAYS)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_HOURS_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_HOURS)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_MINUTES_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_MINUTES)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_INTERVAL)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_MODES_BEHAVIOR_SCROLL));
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_INTERVAL_NUMBER)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_MODES_BEHAVIOR_SCROLL) && IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_DURATION_INTERVAL));
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_INTERVAL_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_MODES_BEHAVIOR_SCROLL) && IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_DURATION_INTERVAL));
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_UPDATE_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_UPDATE_NUMBER)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_UPDATE_MINUTES_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_COLORS)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_BACKGROUND_COLOR_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_BACKGROUND_COLOR)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_LABEL_COLOR_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_LABEL_COLOR)->EnableWindow();
	return TRUE;
}

BOOL CGRDSettingsChartPage::OnKillActive()
{
	GetParentDialog()->OnDataExchange(GetSafeHwnd(), m_cLayout[0]);
	return CLocalePropertyPage::OnKillActive();
}

BOOL CGRDSettingsChartPage::OnDataExchange(CONST CGRDLayout &cLayout)
{
	return m_cLayout[0].Copy(&cLayout);
}

void CGRDSettingsChartPage::OnTypeNormal()
{
	m_cLayout[0].SetType(GRDLAYOUT_TYPE_NORMAL);
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_MODES_PLOTTING_NORMAL)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_MODES_PLOTTING_AREA)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_MODES_BEHAVIOR_SCROLL)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_MODES_BEHAVIOR_OVERWRITE)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_MODES_BEHAVIOR_RESTART)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_VERTICAL)->EnableWindow();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsChartPage::OnTypeStripchart()
{
	INT  nGrids[2];

	m_cLayout[0].SetType(GRDLAYOUT_TYPE_STRIPCHART);
	m_cLayout[0].GetGrids(nGrids[0], nGrids[1]);
	m_cLayout[0].SetGrids(nGrids[0], 0);
	CheckDlgButton(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_VERTICAL, FALSE);
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_MODES_PLOTTING_NORMAL)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_MODES_PLOTTING_AREA)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_MODES_BEHAVIOR_SCROLL)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_MODES_BEHAVIOR_OVERWRITE)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_MODES_BEHAVIOR_RESTART)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_VERTICAL)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_VERTICAL_NUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsChartPage::OnTypeStackchart()
{
	m_cLayout[0].SetType(GRDLAYOUT_TYPE_STACKCHART);
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_MODES_PLOTTING_NORMAL)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_MODES_PLOTTING_AREA)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_MODES_BEHAVIOR_SCROLL)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_MODES_BEHAVIOR_OVERWRITE)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_MODES_BEHAVIOR_RESTART)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_VERTICAL)->EnableWindow();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsChartPage::OnTypeDiagram()
{
	m_cLayout[0].SetType(GRDLAYOUT_TYPE_DIAGRAM);
	m_cLayout[0].SetMode(GRDLAYOUT_MODE_NORMAL | GRDLAYOUT_MODE_RESTART);
	CheckDlgButton(IDC_GRDSETTINGS_CHARTPAGE_MODES_PLOTTING_NORMAL, TRUE);
	CheckDlgButton(IDC_GRDSETTINGS_CHARTPAGE_MODES_PLOTTING_AREA, FALSE);
	CheckDlgButton(IDC_GRDSETTINGS_CHARTPAGE_MODES_BEHAVIOR_SCROLL, FALSE);
	CheckDlgButton(IDC_GRDSETTINGS_CHARTPAGE_MODES_BEHAVIOR_OVERWRITE, FALSE);
	CheckDlgButton(IDC_GRDSETTINGS_CHARTPAGE_MODES_BEHAVIOR_RESTART, TRUE);
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_MODES_PLOTTING_NORMAL)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_MODES_PLOTTING_AREA)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_MODES_BEHAVIOR_SCROLL)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_MODES_BEHAVIOR_OVERWRITE)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_MODES_BEHAVIOR_RESTART)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_VERTICAL)->EnableWindow();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsChartPage::OnPlottingNormal()
{
	m_cLayout[0].SetMode((m_cLayout[0].GetMode() & ~GRDLAYOUT_MODE_AREA) | GRDLAYOUT_MODE_NORMAL);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsChartPage::OnPlottingArea()
{
	m_cLayout[0].SetMode((m_cLayout[0].GetMode() & ~GRDLAYOUT_MODE_NORMAL) | GRDLAYOUT_MODE_AREA);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsChartPage::OnPlottingScroll()
{
	m_cLayout[0].SetMode((m_cLayout[0].GetMode() & ~(GRDLAYOUT_MODE_OVERWRITE | GRDLAYOUT_MODE_RESTART)) | GRDLAYOUT_MODE_SCROLL);
	m_cLayout[0].SetInterval((IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_MODES_BEHAVIOR_SCROLL)) ? m_cLayout[0].GetInterval() : 0);
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_INTERVAL)->EnableWindow();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsChartPage::OnPlottingOverwrite()
{
	m_cLayout[0].SetMode((m_cLayout[0].GetMode() & ~(GRDLAYOUT_MODE_SCROLL | GRDLAYOUT_MODE_RESTART)) | GRDLAYOUT_MODE_OVERWRITE);
	m_cLayout[0].SetInterval(CTimeSpan(0));
	CheckDlgButton(IDC_GRDSETTINGS_CHARTPAGE_DURATION_INTERVAL, FALSE);
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_INTERVAL)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_INTERVAL_NUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_INTERVAL_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsChartPage::OnPlottingRestart()
{
	m_cLayout[0].SetMode((m_cLayout[0].GetMode() & ~(GRDLAYOUT_MODE_SCROLL | GRDLAYOUT_MODE_OVERWRITE)) | GRDLAYOUT_MODE_RESTART);
	m_cLayout[0].SetInterval(CTimeSpan(0));
	CheckDlgButton(IDC_GRDSETTINGS_CHARTPAGE_DURATION_INTERVAL, FALSE);
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_INTERVAL)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_INTERVAL_NUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_INTERVAL_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsChartPage::OnGraphWidth()
{
	m_cLayout[0].SetPlotSize(CSize((IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_WIDTH_USE)) ? GRDLAYOUT_GRAPH_WIDTH : 0, m_cLayout[0].GetPlotSize().cy));
	Spinbox_SetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_WIDTH_NUMBER), GRDLAYOUT_GRAPH_WIDTH);
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_WIDTH_NUMBER)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_WIDTH_USE));
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_WIDTH_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_WIDTH_USE));
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_WIDTH_NUMBER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsChartPage::OnGraphHeight()
{
	m_cLayout[0].SetPlotSize(CSize(m_cLayout[0].GetPlotSize().cx, (IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_HEIGHT_USE)) ? GRDLAYOUT_GRAPH_HEIGHT : 0));
	Spinbox_SetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_HEIGHT_NUMBER), GRDLAYOUT_GRAPH_HEIGHT);
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_HEIGHT_NUMBER)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_HEIGHT_USE));
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_HEIGHT_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_HEIGHT_USE));
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_HEIGHT_NUMBER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsChartPage::OnHorizontalGrids()
{
	INT  nGrids[2];

	m_cLayout[0].GetGrids(nGrids[0], nGrids[1]);
	m_cLayout[0].SetGrids((IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_HORIZONTAL)) ? GRDSETTINGSCHARTPAGE_DEFAULTGRIDS : 0, nGrids[1]);
	Spinbox_SetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_HORIZONTAL_NUMBER), GRDSETTINGSCHARTPAGE_DEFAULTGRIDS);
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_HORIZONTAL_NUMBER)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_HORIZONTAL));
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_WIDTH)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_HORIZONTAL) || IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_VERTICAL));
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_HORIZONTAL_NUMBER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsChartPage::OnVerticalGrids()
{
	INT  nGrids[2];

	m_cLayout[0].GetGrids(nGrids[0], nGrids[1]);
	m_cLayout[0].SetGrids(nGrids[0], (IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_VERTICAL)) ? GRDSETTINGSCHARTPAGE_DEFAULTGRIDS : 0);
	Spinbox_SetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_VERTICAL_NUMBER), GRDSETTINGSCHARTPAGE_DEFAULTGRIDS);
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_VERTICAL_NUMBER)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_VERTICAL));
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_WIDTH)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_HORIZONTAL) || IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_VERTICAL));
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_VERTICAL_NUMBER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsChartPage::OnHorizontalTicks()
{
	INT  nTicks[2];

	m_cLayout[0].GetTicks(nTicks[0], nTicks[1]);
	m_cLayout[0].SetTicks((IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_HORIZONTAL)) ? GRDSETTINGSCHARTPAGE_DEFAULTTICKS : 0, nTicks[1]);
	Spinbox_SetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_HORIZONTAL_NUMBER), GRDSETTINGSCHARTPAGE_DEFAULTTICKS);
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_HORIZONTAL_NUMBER)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_HORIZONTAL));
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_WIDTH)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_HORIZONTAL) || IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_VERTICAL));
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_HORIZONTAL_NUMBER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsChartPage::OnVerticalTicks()
{
	INT  nTicks[2];

	m_cLayout[0].GetTicks(nTicks[0], nTicks[1]);
	m_cLayout[0].SetTicks(nTicks[0], (IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_VERTICAL)) ? GRDSETTINGSCHARTPAGE_DEFAULTTICKS : 0);
	Spinbox_SetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_VERTICAL_NUMBER), GRDSETTINGSCHARTPAGE_DEFAULTTICKS);
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_VERTICAL_NUMBER)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_VERTICAL));
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_WIDTH)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_HORIZONTAL) || IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_VERTICAL));
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_VERTICAL_NUMBER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsChartPage::OnDurationInterval()
{
	m_cLayout[0].SetInterval((IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_DURATION_INTERVAL)) ? m_cLayout[0].GetDuration() : 0);
	Spinbox_SetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_INTERVAL_NUMBER), GRDSETTINGSCHARTPAGE_DEFAULTPERCENTAGE);
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_INTERVAL_NUMBER)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_DURATION_INTERVAL));
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_INTERVAL_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_CHARTPAGE_DURATION_INTERVAL));
	GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_INTERVAL_NUMBER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsChartPage::OnSelchangeGridsColor()
{
	m_cLayout[0].SetGridsColor((COLORREF)SendDlgItemMessage(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_COLOR, CB_GETCURSEL)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsChartPage::OnSelchangeTicksColor()
{
	m_cLayout[0].SetTicksColor((COLORREF)SendDlgItemMessage(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_COLOR, CB_GETCURSEL)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsChartPage::OnSelchangeBackgroundColor()
{
	m_cLayout[0].SetBackgroundColor((COLORREF)SendDlgItemMessage(IDC_GRDSETTINGS_CHARTPAGE_BACKGROUND_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_GRDSETTINGS_CHARTPAGE_BACKGROUND_COLOR, CB_GETCURSEL)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsChartPage::OnSelchangeLabelColor()
{
	m_cLayout[0].SetLabelColor((COLORREF)SendDlgItemMessage(IDC_GRDSETTINGS_CHARTPAGE_LABEL_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_GRDSETTINGS_CHARTPAGE_LABEL_COLOR, CB_GETCURSEL)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsChartPage::OnSpinchangeWidth()
{
	m_cLayout[0].SetPlotSize(CSize((INT)Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_WIDTH_NUMBER)), m_cLayout[0].GetPlotSize().cy));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsChartPage::OnSpinchangeHeight()
{
	m_cLayout[0].SetPlotSize(CSize(m_cLayout[0].GetPlotSize().cx, (INT)Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_HEIGHT_NUMBER))));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsChartPage::OnSpinchangeHorizontalGrids()
{
	INT  nGrids[2];

	m_cLayout[0].GetGrids(nGrids[0], nGrids[1]);
	m_cLayout[0].SetGrids((INT)Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_HORIZONTAL_NUMBER)), nGrids[1]);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsChartPage::OnSpinchangeVerticalGrids()
{
	INT  nGrids[2];

	m_cLayout[0].GetGrids(nGrids[0], nGrids[1]);
	m_cLayout[0].SetGrids(nGrids[0], (INT)Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_VERTICAL_NUMBER)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsChartPage::OnSpinchangeHorizontalTicks()
{
	INT  nTicks[2];

	m_cLayout[0].GetTicks(nTicks[0], nTicks[1]);
	m_cLayout[0].SetTicks((INT)Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_HORIZONTAL_NUMBER)), nTicks[1]);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsChartPage::OnSpinchangeVerticalTicks()
{
	INT  nTicks[2];

	m_cLayout[0].GetTicks(nTicks[0], nTicks[1]);
	m_cLayout[0].SetTicks(nTicks[0], (INT)Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_VERTICAL_NUMBER)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsChartPage::OnSpinchangeGridsWidth()
{
	m_cLayout[0].SetGridsWidth((INT)Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_GRIDS_WIDTH)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsChartPage::OnSpinchangeTicksWidth()
{
	m_cLayout[0].SetTicksWidth((INT)Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_GRAPH_TICKS_WIDTH)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsChartPage::OnSpinchangeDurationDays()
{
	CTimeSpan  tDuration;
	CTimeSpan  tInterval;

	for (tDuration = m_cLayout[0].GetDuration(), tInterval = m_cLayout[0].GetInterval(); Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_DAYS)) > 0 || Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_HOURS)) > 0 || Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_MINUTES)) > 0; )
	{
		m_cLayout[0].SetDuration(SECONDSPERDAY*Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_DAYS)) + m_cLayout[0].GetDuration().GetTotalSeconds() % SECONDSPERDAY);
		m_cLayout[0].SetInterval((TIMEKEY)((double)m_cLayout[0].GetDuration().GetTotalSeconds()*((double)tInterval.GetTotalSeconds() / (double)tDuration.GetTotalSeconds())));
		m_cLayout[0].SetUpdateInterval(min(SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_UPDATE_NUMBER)), m_cLayout[0].GetDuration().GetTotalSeconds()));
		break;
	}
	Spinbox_SetRange(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_UPDATE_NUMBER), 0, m_cLayout[0].GetDuration().GetTotalMinutes());
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsChartPage::OnSpinchangeDurationHours()
{
	CTimeSpan  tDuration;
	CTimeSpan  tInterval;

	for (tDuration = m_cLayout[0].GetDuration(), tInterval = m_cLayout[0].GetInterval(); Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_DAYS)) > 0 || Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_HOURS)) > 0 || Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_MINUTES)) > 0; )
	{
		m_cLayout[0].SetDuration(SECONDSPERHOUR*Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_HOURS)) + SECONDSPERDAY*m_cLayout[0].GetDuration().GetDays() + m_cLayout[0].GetDuration().GetTotalSeconds() % SECONDSPERHOUR);
		m_cLayout[0].SetInterval((TIMEKEY)((double)m_cLayout[0].GetDuration().GetTotalSeconds()*((double)tInterval.GetTotalSeconds() / (double)tDuration.GetTotalSeconds())));
		m_cLayout[0].SetUpdateInterval(min(SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_UPDATE_NUMBER)), m_cLayout[0].GetDuration().GetTotalSeconds()));
		break;
	}
	Spinbox_SetRange(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_UPDATE_NUMBER), 0, m_cLayout[0].GetDuration().GetTotalMinutes());
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsChartPage::OnSpinchangeDurationMinutes()
{
	CTimeSpan  tDuration;
	CTimeSpan  tInterval;

	for (tDuration = m_cLayout[0].GetDuration(), tInterval = m_cLayout[0].GetInterval(); Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_DAYS)) > 0 || Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_HOURS)) > 0 || Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_MINUTES)) > 0; )
	{
		m_cLayout[0].SetDuration(SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_MINUTES)) + SECONDSPERDAY*m_cLayout[0].GetDuration().GetDays() + SECONDSPERHOUR*m_cLayout[0].GetDuration().GetTotalHours());
		m_cLayout[0].SetInterval((TIMEKEY)((double)m_cLayout[0].GetDuration().GetTotalSeconds()*((double)tInterval.GetTotalSeconds() / (double)tDuration.GetTotalSeconds())));
		m_cLayout[0].SetUpdateInterval(min(SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_UPDATE_NUMBER)), m_cLayout[0].GetDuration().GetTotalSeconds()));
		break;
	}
	Spinbox_SetRange(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_UPDATE_NUMBER), 0, m_cLayout[0].GetDuration().GetTotalMinutes());
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsChartPage::OnSpinchangeDurationInterval()
{
	m_cLayout[0].SetInterval((Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_INTERVAL_NUMBER))*m_cLayout[0].GetDuration().GetTotalSeconds()) / 100);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsChartPage::OnSpinchangeUpdateInterval()
{
	m_cLayout[0].SetUpdateInterval(min(SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_UPDATE_NUMBER)), m_cLayout[0].GetDuration().GetTotalSeconds()));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsChartPage::OnKillFocusDurationDays()
{
	CTimeSpan  tDuration;
	CTimeSpan  tInterval;

	for (tDuration = m_cLayout[0].GetDuration(), tInterval = m_cLayout[0].GetInterval(); !Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_DAYS)) && !Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_HOURS)) && !Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_MINUTES)); )
	{
		Spinbox_SetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_MINUTES), GRDSETTINGSCHARTPAGE_MINIMUMDURATION);
		m_cLayout[0].SetDuration((tDuration = SECONDSPERMINUTE*GRDSETTINGSCHARTPAGE_MINIMUMDURATION));
		m_cLayout[0].SetInterval((Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_INTERVAL_NUMBER))*m_cLayout[0].GetDuration().GetTotalSeconds()) / 100);
		m_cLayout[0].SetUpdateInterval(min(SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_UPDATE_NUMBER)), m_cLayout[0].GetDuration().GetTotalSeconds()));
		break;
	}
	Spinbox_SetRange(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_UPDATE_NUMBER), 0, m_cLayout[0].GetDuration().GetTotalMinutes());
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsChartPage::OnKillFocusDurationHours()
{
	CTimeSpan  tDuration;
	CTimeSpan  tInterval;

	for (tDuration = m_cLayout[0].GetDuration(), tInterval = m_cLayout[0].GetInterval(); !Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_DAYS)) && !Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_HOURS)) && !Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_MINUTES)); )
	{
		Spinbox_SetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_MINUTES), GRDSETTINGSCHARTPAGE_MINIMUMDURATION);
		m_cLayout[0].SetDuration((tDuration = SECONDSPERMINUTE*GRDSETTINGSCHARTPAGE_MINIMUMDURATION));
		m_cLayout[0].SetInterval((Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_INTERVAL_NUMBER))*m_cLayout[0].GetDuration().GetTotalSeconds()) / 100);
		m_cLayout[0].SetUpdateInterval(min(SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_UPDATE_NUMBER)), m_cLayout[0].GetDuration().GetTotalSeconds()));
		break;
	}
	Spinbox_SetRange(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_UPDATE_NUMBER), 0, m_cLayout[0].GetDuration().GetTotalMinutes());
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsChartPage::OnKillFocusDurationMinutes()
{
	CTimeSpan  tDuration;
	CTimeSpan  tInterval;

	for (tDuration = m_cLayout[0].GetDuration(), tInterval = m_cLayout[0].GetInterval(); !Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_DAYS)) && !Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_HOURS)) && !Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_MINUTES)); )
	{
		Spinbox_SetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_MINUTES), GRDSETTINGSCHARTPAGE_MINIMUMDURATION);
		m_cLayout[0].SetDuration((tDuration = SECONDSPERMINUTE*GRDSETTINGSCHARTPAGE_MINIMUMDURATION));
		m_cLayout[0].SetInterval((Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_INTERVAL_NUMBER))*m_cLayout[0].GetDuration().GetTotalSeconds()) / 100);
		m_cLayout[0].SetUpdateInterval(min(SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_UPDATE_NUMBER)), m_cLayout[0].GetDuration().GetTotalSeconds()));
		break;
	}
	Spinbox_SetRange(GetDlgItem(IDC_GRDSETTINGS_CHARTPAGE_DURATION_UPDATE_NUMBER), 0, m_cLayout[0].GetDuration().GetTotalMinutes());
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CGRDSettingsParametersPage property page

IMPLEMENT_DYNCREATE(CGRDSettingsParametersPage, CLocalePropertyPage)

CGRDSettingsParametersPage::CGRDSettingsParametersPage() : CLocalePropertyPage(CGRDSettingsParametersPage::IDD)
{
	//{{AFX_DATA_INIT(CGRDSettingsParametersPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CGRDSettingsParametersPage::Initialize()
{
	CGRDOpenDialog  *pDialog;

	return((((pDialog = GetParentDialog()->GetParentDialog()) && pDialog->GetLayout(m_cLayout[0])) || GetParentDisplay()->GetLayout(m_cLayout[0])) ? m_cLayout[1].Copy(&m_cLayout[0]) : FALSE);
}

BOOL CGRDSettingsParametersPage::GetLayout(CGRDLayout &cLayout) CONST
{
	return((cLayout.Copy(&m_cLayout[0])) ? Check(FALSE) : FALSE);
}

CGRDSettingsDialog *CGRDSettingsParametersPage::GetParentDialog() CONST
{
	return((CGRDSettingsDialog *)CLocalePropertyPage::GetParent());
}

CGRDWnd *CGRDSettingsParametersPage::GetParentDisplay() CONST
{
	return((CGRDWnd *)GetParentDialog()->GetParentDisplay());
}

BOOL CGRDSettingsParametersPage::EnumParameters()
{
	INT  nParameter;
	INT  nParameters;
	CString  szParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	for (nParameter = 0, nParameters = (INT)GetDatabase()->GetTMParameters()->GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(nParameter)) != (CDatabaseTMParameter *)NULL)
		{
			szParameter.Format(STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_PARAMETERFORMAT), (LPCTSTR)pDatabaseTMParameter->GetTag(), (LPCTSTR)pDatabaseTMParameter->GetDescription());
			SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PARAMETER, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szParameter);
		}
	}
	if (SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PARAMETER, CB_GETCOUNT) > 0)
	{
		SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PARAMETER, CB_SETCURSEL);
		EnumValueRanges();
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDSettingsParametersPage::EnumContents()
{
	INT  nItem;
	INT  nItems;
	INT  nColumn;
	INT  nColumns;
	double  fRange[2];
	CString  szItem;
	CStringTools  cStringTools;
	CGRDLayoutParameter  *pParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	for (nItem = 0, nItems = (INT)m_cLayout[0].GetSize(); nItem < nItems; nItem++)
	{
		for (nColumn = 0, nColumns = ((pParameter = m_cLayout[0].GetAt(nItem))) ? (INT)m_szColumns.GetSize() : 0; nColumn < nColumns; nColumn++)
		{
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_TITLEITEM_ID); )
			{
				szItem = pParameter->GetName();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_TITLEITEM_DESCRIPTION); )
			{
				if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pParameter->GetName()))))
				{
					szItem = pDatabaseTMParameter->GetDescription();
					break;
				}
				szItem.Empty();
				break;
			}
			for (; m_szColumns.GetAt(nColumn) == STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_TITLEITEM_RANGE); )
			{
				if (!pParameter->GetRange(fRange[0], fRange[1]))
				{
					szItem.Empty();
					break;
				}
				szItem.Format(STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_RANGEFORMAT), (LPCTSTR)cStringTools.ConvertFloatToString(fRange[0]), (LPCTSTR)cStringTools.ConvertFloatToString(fRange[1]));
				break;
			}
			if (!nColumn)
			{
				Listview_InsertText(GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS), nItem, szItem);
				continue;
			}
			Listview_SetText(GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS), nItem, nColumn, szItem);
		}
	}
	if (SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS, LVM_GETITEMCOUNT) == nItems)
	{
		Listview_SetCurText(GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS), 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDSettingsParametersPage::EnumValueCoding()
{
	return((SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_VALUE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_VALUE_DEFAULT)) >= 0 && SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_VALUE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_VALUE_CODED)) >= 0 && SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_VALUE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_VALUE_BINARY)) >= 0 && SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_VALUE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_VALUE_INVERSE)) >= 0 && SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_VALUE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_VALUE_OCTAL)) >= 0 && SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_VALUE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_VALUE_DECIMAL)) >= 0 && SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_VALUE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_VALUE_HEXADECIMAL)) >= 0) ? TRUE : FALSE);
}

BOOL CGRDSettingsParametersPage::EnumValueRanges()
{
	INT  nPos;
	INT  nPoint;
	INT  nTable;
	INT  nPoints;
	INT  nTables;
	double  fX[2];
	CString  szY;
	CString  szName;
	CString  szRange[2];
	CUIntArray  nTableIDs[2];
	CStringTools  cStringTools;
	CGRDLayoutParameter  *pParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;
	CDatabaseTMTxtCalPoint  *pDatabaseTMTxtCalPoint;

	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PARAMETER)->GetWindowText(szName);
	if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find((szName = ((nPos = szName.Find(CString(SPACE) + CString(SPACE))) >= 0) ? szName.Left(nPos) : szName)))))
	{
		if ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS) == TMPARAMETER_CALIBRATION_STATUS  &&  pDatabaseTMParameter->GetCalTableRefs(nTableIDs[0], nTableIDs[1]) > 0)
		{
			for (nTable = 0, nTables = (INT)nTableIDs[0].GetSize(), SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MINIMUM, CB_RESETCONTENT), SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MAXIMUM, CB_RESETCONTENT); nTable < nTables; nTable++)
			{
				if ((pDatabaseTMTxtCalTable = GetDatabase()->GetTMTxtCalTables()->GetAt(nTableIDs[0].GetAt(nTable))))
				{
					for (nPoint = 0, nPoints = (INT)pDatabaseTMTxtCalTable->GetSize(); nPoint < nPoints; nPoint++)
					{
						if ((pDatabaseTMTxtCalPoint = pDatabaseTMTxtCalTable->GetAt(nPoint)))
						{
							if (pDatabaseTMTxtCalPoint->GetPoint(fX[0], szY))
							{
								szRange[0].Format(STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_VALUE_RANGEFORMAT), (LPCTSTR)szY, (LONGLONG)fX[0]);
								if (SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MINIMUM, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szRange[0]) == CB_ERR) SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MINIMUM, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szRange[0]);
								if (SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MAXIMUM, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szRange[0]) == CB_ERR) SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MAXIMUM, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szRange[0]);
								continue;
							}
							if (pDatabaseTMTxtCalPoint->GetRange(fX[0], fX[1], szY))
							{
								szRange[0].Format(STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_VALUE_RANGEFORMAT), (LPCTSTR)szY, (LONGLONG)fX[0]);
								szRange[1].Format(STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_VALUE_RANGEFORMAT), (LPCTSTR)szY, (LONGLONG)fX[1]);
								if (SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MINIMUM, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szRange[0]) == CB_ERR) SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MINIMUM, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szRange[0]);
								if (SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MAXIMUM, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szRange[1]) == CB_ERR) SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MAXIMUM, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szRange[1]);
								continue;
							}
						}
					}
				}
			}
			if ((pParameter = FindParameter()))
			{
				if (pParameter->GetRange(fX[0], fX[1]))
				{
					GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MINIMUM)->SetWindowText(cStringTools.ConvertFloatToString(fX[0]));
					GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MAXIMUM)->SetWindowText(cStringTools.ConvertFloatToString(fX[1]));
				}
			}
			return TRUE;
		}
	}
	if ((pParameter = FindParameter()))
	{
		if (pParameter->GetRange(fX[0], fX[1]))
		{
			SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MINIMUM, CB_RESETCONTENT);
			SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MAXIMUM, CB_RESETCONTENT);
			GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MINIMUM)->SetWindowText(cStringTools.ConvertFloatToString(fX[0]));
			GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MAXIMUM)->SetWindowText(cStringTools.ConvertFloatToString(fX[1]));
			return TRUE;
		}
	}
	SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MINIMUM, CB_RESETCONTENT);
	SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MAXIMUM, CB_RESETCONTENT);
	return TRUE;
}

BOOL CGRDSettingsParametersPage::EnumLineStyle()
{
	return((SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_STYLE, LSCB_DELETELINESTYLE, (WPARAM)NULL, LS_DASHDOT) >= 0 && SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_STYLE, LSCB_DELETELINESTYLE, (WPARAM)NULL, LS_DASHDOTDOT) >= 0) ? TRUE : FALSE);
}

BOOL CGRDSettingsParametersPage::EnumLineSymbol()
{
	return TRUE;
}

VOID CGRDSettingsParametersPage::SetParameterInfo()
{
	double  fMinimum;
	double  fMaximum;
	CStringTools  cStringTools;
	CGRDLayoutParameter  *pParameter;

	if ((pParameter = FindParameter()))
	{
		if (pParameter->GetRange(fMinimum, fMaximum))
		{
			CheckDlgButton(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_DIGITS, (pParameter->GetDigits() > 0) ? TRUE : FALSE);
			CheckDlgButton(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_OCCURRENCE, (pParameter->GetOccurrence() >= 0) ? TRUE : FALSE);
			SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_VALUE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_VALUE, CB_FINDSTRINGEXACT, (WPARAM)-1, (pParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS)) ? (LPARAM)STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_VALUE_DEFAULT) : ((pParameter->GetAttributes() & (TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_FLOATINGPOINT)) ? (LPARAM)STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_VALUE_CODED) : (((pParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_RADIX_BINARY)) == (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_RADIX_BINARY)) ? (LPARAM)STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_VALUE_BINARY) : (((pParameter->GetAttributes() & (TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_RADIX_BINARY)) == (TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_RADIX_BINARY)) ? (LPARAM)STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_VALUE_INVERSE) : (((pParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_RADIX_OCTAL)) == (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_RADIX_OCTAL)) ? (LPARAM)STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_VALUE_OCTAL) : (((pParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_RADIX_DECIMAL)) == (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_RADIX_DECIMAL)) ? (LPARAM)STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_VALUE_DECIMAL) : (((pParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_RADIX_HEXADECIMAL)) == (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_RADIX_HEXADECIMAL)) ? (LPARAM)STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_VALUE_HEXADECIMAL) : (LPARAM)STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_VALUE_DEFAULT)))))))));
			SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (pParameter->GetColor() == GetSysColor(COLOR_WINDOW)) ? (LPARAM)GetDatabase()->GetGRDIDColumnColor() : (LPARAM)pParameter->GetColor());
			SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_STYLE, LSCB_SELECTLINESTYLE, (WPARAM)-1, (pParameter->GetLineStyle() == GRDLAYOUTPARAMETER_LINESTYLE_SOLID) ? (LPARAM)LS_SOLID : ((pParameter->GetLineStyle() == GRDLAYOUTPARAMETER_LINESTYLE_DOTTED) ? (LPARAM)LS_DOT : ((pParameter->GetLineStyle() == GRDLAYOUTPARAMETER_LINESTYLE_DASHED) ? (LPARAM)LS_DASH : (LPARAM)LS_SOLID)));
			SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_SYMBOL, LSCB_SELECTLINESYMBOL, (WPARAM)-1, (pParameter->GetLineSymbol() == GRDLAYOUTPARAMETER_LINESYMBOL_NONE) ? (LPARAM)LS_NONE : ((pParameter->GetLineSymbol() == GRDLAYOUTPARAMETER_LINESYMBOL_POINT) ? (LPARAM)LS_POINT : ((pParameter->GetLineSymbol() == GRDLAYOUTPARAMETER_LINESYMBOL_STROKE) ? (LPARAM)LS_STROKE : ((pParameter->GetLineSymbol() == GRDLAYOUTPARAMETER_LINESYMBOL_CROSS) ? (LPARAM)LS_CROSS : ((pParameter->GetLineSymbol() == GRDLAYOUTPARAMETER_LINESYMBOL_SQUARE) ? (LPARAM)LS_SQUARE : (LPARAM)LS_NONE)))));
			Spinbox_SetPos(GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_DIGITS_COUNT), (pParameter->GetDigits() > 0) ? pParameter->GetDigits() : GRDSETTINGSPARAMETERSPAGE_DEFAULTVALUEDIGITS);
			Spinbox_SetPos(GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_OCCURRENCE_NUMBER), pParameter->GetOccurrence());
			Spinbox_SetPos(GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_WIDTH), pParameter->GetLineWidth());
			GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MINIMUM)->SetWindowText(cStringTools.ConvertFloatToString(fMinimum));
			GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MAXIMUM)->SetWindowText(cStringTools.ConvertFloatToString(fMaximum));
			GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_COMMENTS)->SetWindowText(pParameter->GetComment());
			GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_DIGITS_COUNT)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_DIGITS));
			GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_OCCURRENCE_NUMBER)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_OCCURRENCE));
			return;
		}
	}
	CheckDlgButton(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_DIGITS, FALSE);
	CheckDlgButton(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_OCCURRENCE, FALSE);
	SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_VALUE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_VALUE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_VALUE_DEFAULT)));
	SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_STYLE, LSCB_SELECTLINESTYLE, (WPARAM)-1, (LPARAM)LS_SOLID);
	SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_SYMBOL, LSCB_SELECTLINESYMBOL, (WPARAM)-1, (LPARAM)LS_NONE);
	SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)RGB_COLOR_BLACK);
	Spinbox_SetPos(GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_WIDTH), GRDSETTINGSPARAMETERSPAGE_DEFAULTLINEWIDTH);
	Spinbox_SetPos(GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_DIGITS_COUNT), GRDSETTINGSPARAMETERSPAGE_DEFAULTVALUEDIGITS);
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MINIMUM)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MAXIMUM)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_COMMENTS)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_DIGITS_COUNT)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_OCCURRENCE_NUMBER)->EnableWindow(FALSE);
}

BOOL CGRDSettingsParametersPage::GetParameterInfo(CString &szName, CString &szComments, ULONGLONG &nAttributes, INT &nOccurrence, INT &nDigits, double &fMinimum, double &fMaximum, INT &nLineWidth, INT &nLineStyle, INT &nLineSymbol, COLORREF &nColor) CONST
{
	INT  nPos;
	INT  nTable;
	INT  nTables;
	INT  nPoint;
	INT  nPoints;
	BOOL  bMinimum;
	BOOL  bMaximum;
	double  fX[2];
	CString  szY;
	CString  szMinimum;
	CString  szMaximum;
	CString  szRange[2];
	CString  szValueCoding;
	CUIntArray  nTableIDs[2];
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;
	CDatabaseTMTxtCalPoint  *pDatabaseTMTxtCalPoint;

	for (GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PARAMETER)->GetWindowText(szName), szComments.Empty(), nAttributes = 0, nOccurrence = 0, nDigits = 0, fMinimum = fMaximum = 0.0, nLineWidth = 0, nLineSymbol = 0, nColor = 0, bMinimum = bMaximum = FALSE; (pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find((szName = ((nPos = szName.Find(CString(SPACE) + CString(SPACE))) >= 0) ? szName.Left(nPos) : szName)))); )
	{
		GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_COMMENTS)->GetWindowText(szComments);
		GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_VALUE)->GetWindowText(szValueCoding);
		GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MINIMUM)->GetWindowText(szMinimum);
		GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MAXIMUM)->GetWindowText(szMaximum);
		nLineWidth = (INT)Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_WIDTH));
		nLineStyle = (GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_STYLE)->SendMessage(LSCB_GETLINESTYLE, (WPARAM)GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_STYLE)->SendMessage(CB_GETCURSEL)) == LS_SOLID) ? GRDLAYOUTPARAMETER_LINESTYLE_SOLID : 0;
		nLineStyle = (GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_STYLE)->SendMessage(LSCB_GETLINESTYLE, (WPARAM)GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_STYLE)->SendMessage(CB_GETCURSEL)) == LS_DOT) ? GRDLAYOUTPARAMETER_LINESTYLE_DOTTED : nLineStyle;
		nLineStyle = (GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_STYLE)->SendMessage(LSCB_GETLINESTYLE, (WPARAM)GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_STYLE)->SendMessage(CB_GETCURSEL)) == LS_DASH) ? GRDLAYOUTPARAMETER_LINESTYLE_DASHED : nLineStyle;
		nLineSymbol = (GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_SYMBOL)->SendMessage(LSCB_GETLINESYMBOL, (WPARAM)GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_SYMBOL)->SendMessage(CB_GETCURSEL)) == LS_NONE) ? GRDLAYOUTPARAMETER_LINESYMBOL_NONE : 0;
		nLineSymbol = (GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_SYMBOL)->SendMessage(LSCB_GETLINESYMBOL, (WPARAM)GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_SYMBOL)->SendMessage(CB_GETCURSEL)) == LS_POINT) ? GRDLAYOUTPARAMETER_LINESYMBOL_POINT : nLineSymbol;
		nLineSymbol = (GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_SYMBOL)->SendMessage(LSCB_GETLINESYMBOL, (WPARAM)GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_SYMBOL)->SendMessage(CB_GETCURSEL)) == LS_STROKE) ? GRDLAYOUTPARAMETER_LINESYMBOL_STROKE : nLineSymbol;
		nLineSymbol = (GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_SYMBOL)->SendMessage(LSCB_GETLINESYMBOL, (WPARAM)GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_SYMBOL)->SendMessage(CB_GETCURSEL)) == LS_CROSS) ? GRDLAYOUTPARAMETER_LINESYMBOL_CROSS : nLineSymbol;
		nLineSymbol = (GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_SYMBOL)->SendMessage(LSCB_GETLINESYMBOL, (WPARAM)GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_SYMBOL)->SendMessage(CB_GETCURSEL)) == LS_SQUARE) ? GRDLAYOUTPARAMETER_LINESYMBOL_SQUARE : nLineSymbol;
		nAttributes = (szValueCoding == STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_VALUE_DEFAULT)) ? pDatabaseTMParameter->GetAttributes() : 0;
		nAttributes = (szValueCoding == STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_VALUE_CODED)) ? ((pDatabaseTMParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS)) | TMPARAMETER_CALIBRATION_NONE) : nAttributes;
		nAttributes = (szValueCoding == STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_VALUE_BINARY)) ? ((pDatabaseTMParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_FLOATINGPOINT)) | TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_RADIX_BINARY) : nAttributes;
		nAttributes = (szValueCoding == STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_VALUE_INVERSE)) ? ((pDatabaseTMParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_FLOATINGPOINT)) | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_RADIX_BINARY) : nAttributes;
		nAttributes = (szValueCoding == STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_VALUE_OCTAL)) ? ((pDatabaseTMParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_FLOATINGPOINT)) | TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_RADIX_OCTAL) : nAttributes;
		nAttributes = (szValueCoding == STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_VALUE_DECIMAL)) ? ((pDatabaseTMParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_FLOATINGPOINT)) | TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_RADIX_DECIMAL) : nAttributes;
		nAttributes = (szValueCoding == STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_VALUE_HEXADECIMAL)) ? ((pDatabaseTMParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_FLOATINGPOINT)) | TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_RADIX_HEXADECIMAL) : nAttributes;
		nDigits = (IsDlgButtonChecked(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_DIGITS)) ? (INT)Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_DIGITS_COUNT)) : 0;
		nOccurrence = (IsDlgButtonChecked(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_OCCURRENCE)) ? (INT)Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_OCCURRENCE_NUMBER)) : -1;
		nColor = (COLORREF)GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_COLOR)->SendMessage(CCB_GETCOLOR, (WPARAM)GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_COLOR)->SendMessage(CB_GETCURSEL));
		if ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS) && pDatabaseTMParameter->GetCalTableRefs(nTableIDs[0], nTableIDs[1]) > 0)
		{
			for (nTable = 0, nTables = (INT)nTableIDs[0].GetSize(); nTable < nTables && (!bMinimum || !bMaximum); nTable++)
			{
				if ((pDatabaseTMTxtCalTable = GetDatabase()->GetTMTxtCalTables()->GetAt(nTableIDs[0].GetAt(nTable))))
				{
					for (nPoint = 0, nPoints = (INT)pDatabaseTMTxtCalTable->GetSize(); nPoint < nPoints; nPoint++)
					{
						if ((pDatabaseTMTxtCalPoint = pDatabaseTMTxtCalTable->GetAt(nPoint)))
						{
							if (pDatabaseTMTxtCalPoint->GetPoint(fX[0], szY))
							{
								for (szRange[0].Format(STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_VALUE_RANGEFORMAT), (LPCTSTR)szY, (LONGLONG)fX[0]); szMinimum == szRange[0]; )
								{
									fMinimum = fX[0];
									bMinimum = TRUE;
									break;
								}
								if (szMaximum == szRange[0])
								{
									fMaximum = fX[0];
									bMaximum = TRUE;
								}
								continue;
							}
							if (pDatabaseTMTxtCalPoint->GetRange(fX[0], fX[1], szY))
							{
								szRange[0].Format(STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_VALUE_RANGEFORMAT), (LPCTSTR)szY, (LONGLONG)fX[0]);
								szRange[1].Format(STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_VALUE_RANGEFORMAT), (LPCTSTR)szY, (LONGLONG)fX[1]);
								if (szMinimum == szRange[0])
								{
									fMinimum = fX[0];
									bMinimum = TRUE;
								}
								if (szMaximum == szRange[1])
								{
									fMaximum = fX[1];
									bMaximum = TRUE;
								}
								continue;
							}
						}
					}
				}
			}
			if (bMinimum  &&  bMaximum)
			{
				if (fMinimum > fMaximum)
				{
					fX[0] = fMaximum;
					fX[1] = fMinimum;
					fMinimum = fX[0];
					fMaximum = fX[1];
				}
			}
		}
		if (!bMinimum || !bMaximum)
		{
			for (fMinimum = (!bMinimum) ? _ttof(szMinimum) : fMinimum, fMaximum = (!bMaximum) ? _ttof(szMaximum) : fMaximum; fMinimum > fMaximum; )
			{
				fX[0] = fMaximum;
				fX[1] = fMinimum;
				fMinimum = fX[0];
				fMaximum = fX[1];
				break;
			}
		}
		return TRUE;
	}
	szName.Empty();
	return FALSE;
}

VOID CGRDSettingsParametersPage::SetCurParameter(INT nIndex)
{
	Listview_SetCurText(GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS), nIndex);
}

INT CGRDSettingsParametersPage::GetCurParameter() CONST
{
	return Listview_GetCurText(GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS));
}

CGRDLayoutParameter *CGRDSettingsParametersPage::FindParameter() CONST
{
	return m_cLayout[0].GetAt(GetCurParameter());
}

BOOL CGRDSettingsParametersPage::CheckParameter(BOOL bModify) CONST
{
	INT  nDigits;
	INT  nLineWidth;
	INT  nLineStyle;
	INT  nLineSymbol;
	INT  nOccurrence;
	BOOL  bParameter;
	double  fMinimum[2];
	double  fMaximum[2];
	COLORREF  nColor;
	CString  szMinimum;
	CString  szMaximum;
	CString  szComments;
	CString  szParameter;
	ULONGLONG  nAttributes;
	CGRDLayoutParameter  *pParameter;

	for (GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MINIMUM)->GetWindowText(szMinimum), GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MAXIMUM)->GetWindowText(szMaximum), GetParameterInfo(szParameter, szComments, nAttributes, nOccurrence, nDigits, fMinimum[0], fMaximum[0], nLineWidth, nLineStyle, nLineSymbol, nColor), bParameter = TRUE; (pParameter = FindParameter()); )
	{
		bParameter = (pParameter->GetComment() != szComments || (pParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT | TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_FLOATINGPOINT | TMPARAMETER_CODING_TEXTSTRING | TMPARAMETER_CODING_TIME | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_DECIMAL | TMPARAMETER_RADIX_HEXADECIMAL)) != (nAttributes & (TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CALIBRATION_TEXT | TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_FLOATINGPOINT | TMPARAMETER_CODING_TEXTSTRING | TMPARAMETER_CODING_TIME | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_DECIMAL | TMPARAMETER_RADIX_HEXADECIMAL)) || pParameter->GetOccurrence() != nOccurrence || pParameter->GetDigits() != nDigits || (!pParameter->GetRange(fMinimum[1], fMaximum[1]) || fMinimum[0] != fMinimum[1] || fMaximum[0] != fMaximum[1]) || pParameter->GetLineWidth() != nLineWidth || pParameter->GetLineStyle() != nLineStyle || pParameter->GetLineSymbol() != nLineSymbol || pParameter->GetColor() != nColor) ? TRUE : FALSE;
		break;
	}
	return((!szParameter.IsEmpty() && !szMinimum.IsEmpty() && !szMaximum.IsEmpty() && fMinimum[0] < fMaximum[0]) ? (bParameter || !bModify) : FALSE);
}

INT CGRDSettingsParametersPage::CalcColumnWidth(LPCTSTR pszColumn)
{
	CDC  *pDC;
	INT  nWidth;
	CFont  *pOldFont;
	TEXTMETRIC  tmFont;

	if ((pDC = GetDC()))
	{
		if ((pOldFont = pDC->SelectObject(GetFont())))
		{
			if (pDC->GetTextMetrics(&tmFont))
			{
				nWidth = (!lstrcmp(pszColumn, STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_TITLEITEM_ID))) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetGRDIDColumnCharWidth() + 1)*(3 * tmFont.tmAveCharWidth / 2), pDC->GetTextExtent(pszColumn).cx)) : 0;
				nWidth = (!lstrcmp(pszColumn, STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_TITLEITEM_DESCRIPTION))) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetGRDDescriptionColumnCharWidth() + 1)*(3 * tmFont.tmAveCharWidth / 2), pDC->GetTextExtent(pszColumn).cx)) : nWidth;
				nWidth = (!lstrcmp(pszColumn, STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_TITLEITEM_RANGE))) ? (2 * CalcColumnIndent() + max((GetDatabase()->GetGRDRangeColumnCharWidth() + 1)*(3 * tmFont.tmAveCharWidth / 2), pDC->GetTextExtent(pszColumn).cx)) : nWidth;
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

INT CGRDSettingsParametersPage::CalcColumnIndent() CONST
{
	return 3 * GetSystemMetrics(SM_CXEDGE);
}

BOOL CGRDSettingsParametersPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? !m_cLayout[0].Compare(&m_cLayout[1]) : CLocalePropertyPage::IsModified()) : FALSE);
}

BOOL CGRDSettingsParametersPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd()) && !bAll) ? (m_cLayout[0].GetType() != GRDLAYOUT_TYPE_DIAGRAM || m_cLayout[0].GetSize() % 2 == 0) : ((bAll) ? CLocalePropertyPage::Check() : TRUE));
}

void CGRDSettingsParametersPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGRDSettingsParametersPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CGRDSettingsParametersPage::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CGRDSettingsParametersPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CGRDSettingsParametersPage)
	ON_BN_CLICKED(IDC_GRDSETTINGS_PARAMETERSPAGE_ADD, OnAddParameter)
	ON_BN_CLICKED(IDC_GRDSETTINGS_PARAMETERSPAGE_MODIFY, OnModifyParameter)
	ON_BN_CLICKED(IDC_GRDSETTINGS_PARAMETERSPAGE_REMOVE, OnRemoveParameter)
	ON_BN_CLICKED(IDC_GRDSETTINGS_PARAMETERSPAGE_REMOVEALL, OnRemoveAllParameters)
	ON_BN_CLICKED(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_DIGITS, OnDigits)
	ON_BN_CLICKED(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_OCCURRENCE, OnOccurrence)
	ON_CBN_EDITCHANGE(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MINIMUM, OnEditchangeMinimum)
	ON_CBN_EDITCHANGE(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MAXIMUM, OnEditchangeMaximum)
	ON_CBN_SELCHANGE(IDC_GRDSETTINGS_PARAMETERSPAGE_PARAMETER, OnSelchangeParameter)
	ON_CBN_SELCHANGE(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_VALUE, OnSelchangeValueCoding)
	ON_CBN_SELCHANGE(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MINIMUM, OnSelchangeMinimum)
	ON_CBN_SELCHANGE(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MAXIMUM, OnSelchangeMaximum)
	ON_CBN_SELCHANGE(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_COLOR, OnSelchangeColor)
	ON_CBN_SELCHANGE(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_STYLE, OnSelchangeLineStyle)
	ON_CBN_SELCHANGE(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_SYMBOL, OnSelchangeLineSymbol)
	ON_CONTROL(SBXN_CHANGE, IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_DIGITS_COUNT, OnSpinchangeDigits)
	ON_CONTROL(SBXN_CHANGE, IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_OCCURRENCE_NUMBER, OnSpinchangeOccurrence)
	ON_CONTROL(SBXN_CHANGE, IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_WIDTH, OnSpinchangeLineWidth)
	ON_EN_CHANGE(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_COMMENTS, OnEditchangeComments)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDSettingsParametersPage message handlers

BOOL CGRDSettingsParametersPage::OnInitDialog()
{
	INT  nColumn;
	INT  nColumns;
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	m_szColumns.Add(STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_TITLEITEM_ID));
	m_szColumns.Add(STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_TITLEITEM_DESCRIPTION));
	m_szColumns.Add(STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_TITLEITEM_RANGE));
	SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_COLOR, CCB_DELETECOLOR, (WPARAM)-1, (LPARAM)VGA_COLOR_BLACK);
	SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_COLOR, CCB_INSERTCOLOR, 0, (LPARAM)RGB_COLOR_BLACK);
	SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	Spinbox_SetRange(GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_DIGITS_COUNT), GRDSETTINGSPARAMETERSPAGE_MINIMUMVALUEDIGITS, GRDSETTINGSPARAMETERSPAGE_MAXIMUMVALUEDIGITS);
	Spinbox_SetRange(GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_OCCURRENCE_NUMBER), GRDSETTINGSPARAMETERSPAGE_MINIMUMVALUEOCCURRENCE, GRDSETTINGSPARAMETERSPAGE_MAXIMUMVALUEOCCURRENCE);
	Spinbox_SetRange(GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_WIDTH), GRDSETTINGSPARAMETERSPAGE_MINIMUMLINEWIDTH, GRDSETTINGSPARAMETERSPAGE_MAXIMUMLINEWIDTH);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), EnumParameters(), EnumValueCoding(), EnumLineStyle(), EnumLineSymbol(); nColumn < nColumns; nColumn++)
	{
		Listview_InsertColumn(GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS), nColumn, m_szColumns.GetAt(nColumn), CalcColumnWidth(m_szColumns.GetAt(nColumn)));
		continue;
	}
	EnumContents();
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PARAMETER_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PARAMETER)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_ADD)->EnableWindow(CheckParameter(FALSE));
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_VALUE_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_VALUE)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_DIGITS)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_DIGITS_COUNT)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_DIGITS));
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_OCCURRENCE)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_OCCURRENCE_NUMBER)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_OCCURRENCE));
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MINIMUM_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MINIMUM)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MAXIMUM_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MAXIMUM)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_COMMENTS_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_COMMENTS)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_COLOR_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_COLOR)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_WIDTH_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_WIDTH)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_WIDTH_PIXELS)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_STYLE_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_STYLE)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_SYMBOL_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_LINE_SYMBOL)->EnableWindow();
	SetParameterInfo();
	return TRUE;
}

BOOL CGRDSettingsParametersPage::OnKillActive()
{
	GetParentDialog()->OnDataExchange(GetSafeHwnd(), m_cLayout[0]);
	return CLocalePropertyPage::OnKillActive();
}

BOOL CGRDSettingsParametersPage::OnDataExchange(CONST CGRDLayout &cLayout)
{
	return m_cLayout[0].Copy(&cLayout);
}

BOOL CGRDSettingsParametersPage::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	INT  nIndex;
	CString  szParameter;
	CGRDLayoutParameter  *pParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;
	NMITEMACTIVATE  *pNotifyListView = (LPNMITEMACTIVATE)lParam;

	if (pNotifyListView->hdr.idFrom == IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS)
	{
		if ((pNotifyListView->hdr.code == NM_CLICK || pNotifyListView->hdr.code == NM_DBLCLK) && pNotifyListView->iItem < 0)
		{
			Listview_SetCurText(GetDlgItem((INT)pNotifyListView->hdr.idFrom), (INT)SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1);
			SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_ENSUREVISIBLE, SendDlgItemMessage((INT)pNotifyListView->hdr.idFrom, LVM_GETITEMCOUNT) - 1, MAKELPARAM(FALSE, 0));
			return TRUE;
		}
		if (pNotifyListView->hdr.code == LVN_ITEMCHANGED && (pNotifyListView->uNewState & LVIS_SELECTED))
		{
			for (SetCurParameter(pNotifyListView->iItem); (pDatabaseTMParameter = ((pParameter = FindParameter())) ? GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pParameter->GetName())) : (CDatabaseTMParameter *)NULL); )
			{
				for (szParameter.Format(STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_PARAMETERFORMAT), (LPCTSTR)pDatabaseTMParameter->GetTag(), (LPCTSTR)pDatabaseTMParameter->GetDescription()); (nIndex = (INT)SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PARAMETER, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szParameter)) >= 0; )
				{
					SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PARAMETER, CB_SETCURSEL, nIndex);
					break;
				}
				break;
			}
			SetParameterInfo();
		}
	}
	return CLocalePropertyPage::OnNotify(wParam, lParam, pResult);
}

void CGRDSettingsParametersPage::OnAddParameter()
{
	INT  nIndex;
	INT  nDigits;
	INT  nColumn;
	INT  nColumns;
	INT  nParameter;
	INT  nParameters;
	INT  nLineWidth;
	INT  nLineStyle;
	INT  nLineSymbol;
	INT  nOccurrence;
	double  fMinimum;
	double  fMaximum;
	COLORREF  nColor;
	CString  szItem;
	CString  szComments;
	CString  szParameter;
	ULONGLONG  nAttributes;
	CStringTools  cStringTools;
	CGRDLayoutParameter  *pParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CHourglassCursor  cCursor;

	if ((pParameter = new CGRDLayoutParameter))
	{
		for (GetParameterInfo(szParameter, szComments, nAttributes, nOccurrence, nDigits, fMinimum, fMaximum, nLineWidth, nLineStyle, nLineSymbol, nColor); (pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt((nIndex = GetDatabase()->GetTMParameters()->Find(szParameter)))); )
		{
			for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), pParameter->SetName(szParameter), pParameter->SetComment(szComments), pParameter->SetAttributes(nAttributes), pParameter->SetOccurrence(nOccurrence), pParameter->SetRange(fMinimum, fMaximum), pParameter->SetDigits(nDigits), pParameter->SetColor(nColor), pParameter->SetLineWidth(nLineWidth), pParameter->SetLineStyle(nLineStyle), pParameter->SetLineSymbol(nLineSymbol), pParameter->SetRef(nIndex), m_cLayout[0].InsertAt(max(GetCurParameter() + 1, 0), pParameter, 1); nColumn < nColumns; nColumn++)
			{
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_TITLEITEM_ID); )
				{
					szItem = pDatabaseTMParameter->GetTag();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_TITLEITEM_DESCRIPTION); )
				{
					szItem = pDatabaseTMParameter->GetDescription();
					break;
				}
				for (; m_szColumns.GetAt(nColumn) == STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_TITLEITEM_RANGE); )
				{
					szItem.Format(STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_RANGEFORMAT), (LPCTSTR)cStringTools.ConvertFloatToString(fMinimum), (LPCTSTR)cStringTools.ConvertFloatToString(fMaximum));
					break;
				}
				if (!nColumn)
				{
					Listview_InsertText(GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS), max(GetCurParameter() + 1, 0), szItem);
					continue;
				}
				Listview_SetText(GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS), max(GetCurParameter() + 1, 0), nColumn, szItem);
			}
			for (nParameter = 0, nParameters = (INT)m_cLayout[0].GetSize(); nParameter < nParameters; nParameter++)
			{
				if ((pParameter = m_cLayout[0].GetAt(nParameter)))
				{
					pParameter->SetPosition(nParameter);
					continue;
				}
			}
			break;
		}
		if (nIndex < 0)
		{
			delete pParameter;
			pParameter = (CGRDLayoutParameter *)NULL;
		}
	}
	Listview_SetCurText(GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS), max(GetCurParameter() + 1, 0));
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_ADD)->EnableWindow(CheckParameter(FALSE));
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_REMOVE)->EnableWindow((Listview_GetCurText(GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS))) ? TRUE : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PARAMETER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsParametersPage::OnModifyParameter()
{
	INT  nDigits;
	INT  nColumn;
	INT  nColumns;
	INT  nLineWidth;
	INT  nLineStyle;
	INT  nLineSymbol;
	INT  nOccurrence;
	double  fMinimum;
	double  fMaximum;
	COLORREF  nColor;
	CString  szItem;
	CString  szComments;
	CString  szParameter;
	ULONGLONG  nAttributes;
	CStringTools  cStringTools;
	CGRDLayoutParameter  *pParameter;
	CHourglassCursor  cCursor;

	if ((pParameter = FindParameter()))
	{
		for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), GetParameterInfo(szParameter, szComments, nAttributes, nOccurrence, nDigits, fMinimum, fMaximum, nLineWidth, nLineStyle, nLineSymbol, nColor), pParameter->SetName(szParameter), pParameter->SetComment(szComments), pParameter->SetAttributes(nAttributes), pParameter->SetOccurrence(nOccurrence), pParameter->SetRange(fMinimum, fMaximum), pParameter->SetDigits(nDigits), pParameter->SetColor(nColor), pParameter->SetLineWidth(nLineWidth), pParameter->SetLineStyle(nLineStyle), pParameter->SetLineSymbol(nLineSymbol); nColumn < nColumns; nColumn++)
		{
			if (m_szColumns.GetAt(nColumn) == STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_TITLEITEM_RANGE))
			{
				szItem.Format(STRING(IDS_GRDSETTINGS_PARAMETERSPAGE_RANGEFORMAT), (LPCTSTR)cStringTools.ConvertFloatToString(fMinimum), (LPCTSTR)cStringTools.ConvertFloatToString(fMaximum));
				Listview_SetText(GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS), max(GetCurParameter(), 0), nColumn, szItem);
				break;
			}
		}
	}
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_ADD)->EnableWindow(CheckParameter(FALSE));
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_REMOVE)->EnableWindow((Listview_GetCurText(GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS))) ? TRUE : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PARAMETER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsParametersPage::OnRemoveParameter()
{
	INT  nIndex;
	INT  nCount;
	INT  nParameter;
	INT  nParameters;
	CGRDLayoutParameter  *pParameter;
	CHourglassCursor  cCursor;

	if (Listview_DeleteText(GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS), (nIndex = GetCurParameter())))
	{
		if ((nCount = (INT)SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS, LVM_GETITEMCOUNT)) > 0)
		{
			delete m_cLayout[0].GetAt(nIndex);
			m_cLayout[0].RemoveAt(nIndex);
			SetCurParameter(0);
		}
		else
		{
			delete m_cLayout[0].GetAt(nIndex);
			m_cLayout[0].RemoveAt(nIndex);
			SetCurParameter(-1);
		}
		for (nParameter = 0, nParameters = (INT)m_cLayout[0].GetSize(); nParameter < nParameters; nParameter++)
		{
			if ((pParameter = m_cLayout[0].GetAt(nParameter)))
			{
				pParameter->SetPosition(nParameter);
				continue;
			}
		}
		SetParameterInfo();
	}
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_ADD)->EnableWindow(CheckParameter(FALSE));
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_REMOVE)->EnableWindow((Listview_GetCurText(GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS))) ? TRUE : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PARAMETER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsParametersPage::OnRemoveAllParameters()
{
	CHourglassCursor  cCursor;

	if (SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS, LVM_DELETEALLITEMS))
	{
		if (!SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS, LVM_GETITEMCOUNT))
		{
			m_cLayout[0].RemoveAll();
			SetCurParameter(-1);
			SetParameterInfo();
		}
	}
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_ADD)->EnableWindow(CheckParameter(FALSE));
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_REMOVE)->EnableWindow((Listview_GetCurText(GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS))) ? TRUE : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_CONTENTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PARAMETER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsParametersPage::OnDigits()
{
	Spinbox_SetPos(GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_DIGITS_COUNT), GRDSETTINGSPARAMETERSPAGE_DEFAULTVALUEDIGITS);
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_DIGITS_COUNT)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_DIGITS));
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_ADD)->EnableWindow(CheckParameter(FALSE));
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_DIGITS_COUNT)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsParametersPage::OnOccurrence()
{
	Spinbox_SetPos(GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_OCCURRENCE_NUMBER), GRDSETTINGSPARAMETERSPAGE_DEFAULTVALUEOCCURRENCE);
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_OCCURRENCE_NUMBER)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_OCCURRENCE));
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_ADD)->EnableWindow(CheckParameter(FALSE));
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_OCCURRENCE_NUMBER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsParametersPage::OnSelchangeParameter()
{
	EnumValueRanges();
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_ADD)->EnableWindow(CheckParameter(FALSE));
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsParametersPage::OnSelchangeValueCoding()
{
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_ADD)->EnableWindow(CheckParameter(FALSE));
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsParametersPage::OnSelchangeMinimum()
{
	SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MINIMUM, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MINIMUM, CB_GETCURSEL));
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_ADD)->EnableWindow(CheckParameter(FALSE));
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsParametersPage::OnSelchangeMaximum()
{
	SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MAXIMUM, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_GRDSETTINGS_PARAMETERSPAGE_PROPERTIES_MAXIMUM, CB_GETCURSEL));
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_ADD)->EnableWindow(CheckParameter(FALSE));
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsParametersPage::OnSelchangeColor()
{
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_ADD)->EnableWindow(CheckParameter(FALSE));
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsParametersPage::OnSelchangeLineStyle()
{
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_ADD)->EnableWindow(CheckParameter(FALSE));
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsParametersPage::OnSelchangeLineSymbol()
{
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_ADD)->EnableWindow(CheckParameter(FALSE));
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsParametersPage::OnSpinchangeDigits()
{
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_ADD)->EnableWindow(CheckParameter(FALSE));
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsParametersPage::OnSpinchangeOccurrence()
{
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_ADD)->EnableWindow(CheckParameter(FALSE));
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsParametersPage::OnSpinchangeLineWidth()
{
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_ADD)->EnableWindow(CheckParameter(FALSE));
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsParametersPage::OnEditchangeMinimum()
{
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_ADD)->EnableWindow(CheckParameter(FALSE));
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsParametersPage::OnEditchangeMaximum()
{
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_ADD)->EnableWindow(CheckParameter(FALSE));
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsParametersPage::OnEditchangeComments()
{
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_ADD)->EnableWindow(CheckParameter(FALSE));
	GetDlgItem(IDC_GRDSETTINGS_PARAMETERSPAGE_MODIFY)->EnableWindow((FindParameter()) ? CheckParameter() : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CGRDSettingsRetrievingPage property page

IMPLEMENT_DYNCREATE(CGRDSettingsRetrievingPage, CLocalePropertyPage)

CGRDSettingsRetrievingPage::CGRDSettingsRetrievingPage() : CLocalePropertyPage(CGRDSettingsRetrievingPage::IDD)
{
	//{{AFX_DATA_INIT(CGRDSettingsRetrievingPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CGRDSettingsRetrievingPage::Initialize()
{
	CGRDOpenDialog  *pDialog;

	if (((pDialog = GetParentDialog()->GetParentDialog()) && pDialog->GetRetrieveFileName(m_szFileName[0])) || GetParentDisplay()->GetRetrieveFileName(m_szFileName[0]))
	{
		m_szFileName[1] = m_szFileName[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDSettingsRetrievingPage::GetDataSourceFileName(CString &szFileName) CONST
{
	szFileName = m_szFileName[0];
	return Check(FALSE);
}

CGRDSettingsDialog *CGRDSettingsRetrievingPage::GetParentDialog() CONST
{
	return((CGRDSettingsDialog *)CLocalePropertyPage::GetParent());
}

CGRDWnd *CGRDSettingsRetrievingPage::GetParentDisplay() CONST
{
	return((CGRDWnd *)GetParentDialog()->GetParentDisplay());
}

VOID CGRDSettingsRetrievingPage::EnumDataSources()
{
	INT  nFile;
	INT  nFiles;
	CHistoryStoreFile  cFile;
	CHistoryStoreFiles  pFiles;
	CUIntArray  nOptions;

	for (nFile = 0, nFiles = GetTMService()->GetTMHistoryFiles(HISTORYFILE_TYPE_RETRIEVE, pFiles), GetTMService()->GetDefaultTMHistoryFile(HISTORYFILE_TYPE_RETRIEVE, cFile), m_szFileName[0] = (pFiles.Find(m_szFileName[0]) < 0) ? cFile.GetFileName() : m_szFileName[0]; nFile < nFiles || (!nFiles && !nFile && !m_szFileName[0].IsEmpty()); nFile++)
	{
		SendDlgItemMessage(IDC_GRDSETTINGS_RETRIEVINGPAGE_DATASOURCE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)((nFiles > 0) ? (LPCTSTR)pFiles.GetAt(nFile)->GetFileName() : (LPCTSTR)m_szFileName[0]));
		continue;
	}
	SendDlgItemMessage(IDC_GRDSETTINGS_RETRIEVINGPAGE_DATASOURCE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_GRDSETTINGS_RETRIEVINGPAGE_DATASOURCE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)m_szFileName[0]), 0));
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_DATASOURCE)->GetWindowText(m_szFileName[0]);
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_DATASOURCE)->GetWindowText(m_szFileName[1]);
	ShowDataSourceInfo();
}

VOID CGRDSettingsRetrievingPage::ShowDataSourceInfo()
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
		GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT)->SetWindowText(szProduct);
		GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY)->SetWindowText(szCompany);
		GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT)->SetWindowText(szSpacecraft);
		GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE)->SetWindowText(szDataSourceType);
		GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->SetWindowText(szStartTime);
		GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->SetWindowText(szStopTime);
		GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->SetWindowText(szCreationTime);
		GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE)->SetWindowText(szDataSourceSize);
	}
	else
	{
		GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT)->SetWindowText((szProduct = EMPTYSTRING));
		GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY)->SetWindowText((szCompany = EMPTYSTRING));
		GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT)->SetWindowText((szSpacecraft = EMPTYSTRING));
		GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE)->SetWindowText((szDataSourceType = EMPTYSTRING));
		GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->SetWindowText((szStartTime = EMPTYSTRING));
		GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->SetWindowText((szStopTime = EMPTYSTRING));
		GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->SetWindowText((szCreationTime = EMPTYSTRING));
		GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE)->SetWindowText((szDataSourceSize = EMPTYSTRING));
	}
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMMENTS)->EnableWindow(szProduct.IsEmpty());
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMMENTS)->ShowWindow((szProduct.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT_STATIC)->ShowWindow((!szProduct.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT_STATIC)->EnableWindow(!szProduct.IsEmpty());
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT)->ShowWindow((!szProduct.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT)->EnableWindow(!szProduct.IsEmpty());
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY_STATIC)->ShowWindow((!szCompany.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY_STATIC)->EnableWindow(!szCompany.IsEmpty());
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY)->ShowWindow((!szCompany.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY)->EnableWindow(!szCompany.IsEmpty());
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT_STATIC)->ShowWindow((!szSpacecraft.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT_STATIC)->EnableWindow(!szSpacecraft.IsEmpty());
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT)->ShowWindow((!szSpacecraft.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT)->EnableWindow(!szSpacecraft.IsEmpty());
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE_STATIC)->ShowWindow((!szDataSourceType.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE_STATIC)->EnableWindow(!szDataSourceType.IsEmpty());
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE)->ShowWindow((!szDataSourceType.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE)->EnableWindow(!szDataSourceType.IsEmpty());
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STATIC)->ShowWindow((GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STATIC)->EnableWindow((GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->ShowWindow((GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->EnableWindow((GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_TO)->ShowWindow((GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_TO)->EnableWindow((GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->ShowWindow((GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->EnableWindow((GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME_STATIC)->ShowWindow((GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME_STATIC)->EnableWindow((GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->ShowWindow((GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->EnableWindow((GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE_STATIC)->ShowWindow((!szDataSourceSize.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE_STATIC)->EnableWindow(!szDataSourceSize.IsEmpty());
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE)->ShowWindow((!szDataSourceSize.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE)->EnableWindow(!szDataSourceSize.IsEmpty());
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_INSPECT)->EnableWindow(!m_szFileName[0].IsEmpty());
}

BOOL CGRDSettingsRetrievingPage::CheckDataSource(LPCTSTR pszFileName) CONST
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
BOOL CGRDSettingsRetrievingPage::CheckDataSource(LPCTSTR pszFileName, CString &szProduct, CString &szCompany, CString &szTrademark, CString &szSpacecraft, CString &szDataSourceType, CString &szStartTime, CString &szStopTime, CString &szCreationTime, CString &szDataSourceSize) CONST
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
			for (cHistoryFile.GetCopyrightProduct(szProduct), cHistoryFile.GetCopyrightCompany(szCompany), cHistoryFile.GetCopyrightTrademark(szTrademark), cHistoryFile.GetSpacecraft(szSpacecraft), cHistoryFile.GetType(szDataSourceType), szStartTime = (cHistoryFile.CLogFile::SeekToFirst() && cHistoryFile.CLogFile::Read(tTime, nData)) ? (LPCTSTR)tTime.FormatGmt(STRING(IDS_GRDSETTINGS_RETRIEVINGPAGE_SOURCEDATATIMEFORMAT)) : EMPTYSTRING, szStopTime = (cHistoryFile.CLogFile::SeekToLast() && cHistoryFile.CLogFile::Read(tTime, nData)) ? (LPCTSTR)tTime.FormatGmt(STRING(IDS_GRDSETTINGS_RETRIEVINGPAGE_SOURCEDATATIMEFORMAT)) : EMPTYSTRING, szCreationTime = (cHistoryFile.GetCopyrightCreationTime(tTime)) ? (LPCTSTR)tTime.FormatGmt(STRING(IDS_GRDSETTINGS_RETRIEVINGPAGE_SOURCEDATAFILETIMEFORMAT)) : EMPTYSTRING, szDataSourceSize.Format(STRING(IDS_GRDSETTINGS_RETRIEVINGPAGE_SOURCEDATASIZEFORMAT), ((dwSize = cHistoryFile.CLogFile::GetSize()) + 512) / 1024), szDataSourceSize = FormatDataSourceSize(szDataSourceSize); !szProduct.IsEmpty() && !szCompany.IsEmpty() && !szTrademark.IsEmpty(); )
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

CString CGRDSettingsRetrievingPage::FormatDataSourceSize(LPCTSTR pszDataSourceSize) CONST
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

BOOL CGRDSettingsRetrievingPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? ((m_szFileName[0].CompareNoCase(m_szFileName[1])) ? TRUE : FALSE) : CLocalePropertyPage::IsModified()) : FALSE);
}

BOOL CGRDSettingsRetrievingPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (m_szFileName[0].IsEmpty() || CheckDataSource(m_szFileName[0])) : CLocalePropertyPage::Check()) : TRUE);
}

void CGRDSettingsRetrievingPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGRDSettingsRetrievingPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGRDSettingsRetrievingPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CGRDSettingsRetrievingPage)
	ON_BN_CLICKED(IDC_GRDSETTINGS_RETRIEVINGPAGE_INSPECT, OnInspect)
	ON_CBN_EDITCHANGE(IDC_GRDSETTINGS_RETRIEVINGPAGE_DATASOURCE, OnEditchangeFileName)
	ON_CBN_SELCHANGE(IDC_GRDSETTINGS_RETRIEVINGPAGE_DATASOURCE, OnSelchangeFileName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDSettingsRetrievingPage message handlers

BOOL CGRDSettingsRetrievingPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_DATASOURCE_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_DATASOURCE)->EnableWindow();
	EnumDataSources();
	return TRUE;
}

BOOL CGRDSettingsRetrievingPage::OnSetActive()
{
	ShowDataSourceInfo();
	return CLocalePropertyPage::OnSetActive();
}

void CGRDSettingsRetrievingPage::OnInspect()
{
	CHourglassCursor  cCursor;

	ShowDataSourceInfo();
}

void CGRDSettingsRetrievingPage::OnEditchangeFileName()
{
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_DATASOURCE)->GetWindowText(m_szFileName[0]);
	GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_INSPECT)->EnableWindow(!m_szFileName[0].IsEmpty());
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsRetrievingPage::OnSelchangeFileName()
{
	for (m_szFileName[0] = Combobox_GetText(GetDlgItem(IDC_GRDSETTINGS_RETRIEVINGPAGE_DATASOURCE), (INT)SendDlgItemMessage(IDC_GRDSETTINGS_RETRIEVINGPAGE_DATASOURCE, CB_GETCURSEL)); !m_szFileName[0].IsEmpty(); )
	{
		ShowDataSourceInfo();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CGRDSettingsPrintingComments

IMPLEMENT_DYNCREATE(CGRDSettingsPrintingComments, CEdit)

BEGIN_MESSAGE_MAP(CGRDSettingsPrintingComments, CEdit)
	//{{AFX_MSG_MAP(CGRDSettingsPrintingComments)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDSettingsPrintingComments message handlers

void CGRDSettingsPrintingComments::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
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
// CGRDSettingsPrintingPage property page

IMPLEMENT_DYNCREATE(CGRDSettingsPrintingPage, CLocalePropertyPage)

CGRDSettingsPrintingPage::CGRDSettingsPrintingPage() : CLocalePropertyPage(CGRDSettingsPrintingPage::IDD)
{
	//{{AFX_DATA_INIT(CGRDSettingsPrintingPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CGRDSettingsPrintingPage::Initialize()
{
	CGRDOpenDialog  *pDialog;

	return((((pDialog = GetParentDialog()->GetParentDialog()) && pDialog->GetPrintJobs(m_pJobs[0])) || GetParentDisplay()->GetPrintJobs(m_pJobs[0])) ? m_pJobs[1].Copy(&m_pJobs[0]) : FALSE);
}

BOOL CGRDSettingsPrintingPage::GetJobs(CGRDPrintJobs &pJobs) CONST
{
	return((pJobs.Copy(&m_pJobs[0])) ? Check(FALSE) : FALSE);
}

CGRDSettingsDialog *CGRDSettingsPrintingPage::GetParentDialog() CONST
{
	return((CGRDSettingsDialog *)CLocalePropertyPage::GetParent());
}

CGRDWnd *CGRDSettingsPrintingPage::GetParentDisplay() CONST
{
	return((CGRDWnd *)GetParentDialog()->GetParentDisplay());
}

VOID CGRDSettingsPrintingPage::ShowJobInfo()
{
	UINT  nMode;
	UINT  nScale;
	CGRDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		CheckRadioButton(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_AUTOSCALE, IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE, ((nMode = pJobInfo->GetPrintMode()) & GRD_PRINT_AUTOSCALE) ? IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_AUTOSCALE : IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE);
		CheckDlgButton(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND, (nMode & GRD_PRINT_COLORLEGEND) ? TRUE : FALSE);
		CheckDlgButton(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL, (nMode & GRD_PRINT_UNDERLINEOOL) ? TRUE : FALSE);
		CheckDlgButton(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_NOCOLORS, (nMode & GRD_PRINT_NOCOLORS) ? TRUE : FALSE);
		CheckDlgButton(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS, (nMode & GRD_PRINT_CLEARCOMMENTS) ? TRUE : FALSE);
		SendDlgItemMessage(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetProfile()));
		Spinbox_SetPos(GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE_NUMBER), ((nMode & GRD_PRINT_FIXEDSCALE) && pJobInfo->GetPrintScale(nScale)) ? nScale : 0);
		GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->SetWindowText(pJobInfo->GetComments());
		GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_ADDNAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_REMOVENAME)->EnableWindow((pJobInfo->GetName() != STRING(IDS_PRINTJOB_DEFAULTNAME)) ? TRUE : FALSE);
		GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_REMOVEALLNAMES)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PRINTINGPAGE_NAME, CB_GETCOUNT) > 1) ? TRUE : FALSE);
		GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES)->EnableWindow();
		GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE_STATIC)->EnableWindow();
		GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE)->EnableWindow();
		GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_OPTIONS)->EnableWindow();
		GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND)->EnableWindow();
		GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL)->EnableWindow();
		GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_NOCOLORS)->EnableWindow();
		GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT)->EnableWindow();
		GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_AUTOSCALE)->EnableWindow();
		GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE)->EnableWindow();
		GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE_NUMBER)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE));
		GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE));
		GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTS)->EnableWindow();
		GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT_STATIC)->EnableWindow();
		GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->EnableWindow();
		GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)->EnableWindow(!pJobInfo->GetComments().IsEmpty());
		return;
	}
	SendDlgItemMessage(IDC_GRDSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)-1);
	SendDlgItemMessage(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_SETCURSEL, (WPARAM)-1);
	CheckDlgButton(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND, FALSE);
	CheckDlgButton(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL, FALSE);
	CheckDlgButton(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_NOCOLORS, FALSE);
	CheckDlgButton(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_AUTOSCALE, FALSE);
	CheckDlgButton(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE, FALSE);
	CheckDlgButton(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS, FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_ADDNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_REMOVENAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_REMOVEALLNAMES)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_OPTIONS)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_NOCOLORS)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_AUTOSCALE)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE_NUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTS)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)->EnableWindow(FALSE);
}

CGRDPrintJobInfo *CGRDSettingsPrintingPage::FindJobInfo() CONST
{
	CString  szJobName;

	GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_NAME)->GetWindowText(szJobName);
	return m_pJobs[0].GetAt(m_pJobs[0].Find(szJobName));
}

BOOL CGRDSettingsPrintingPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? !m_pJobs[0].Compare(&m_pJobs[1]) : CLocalePropertyPage::IsModified()) : FALSE);
}

BOOL CGRDSettingsPrintingPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? ((GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_NAME)->GetWindowTextLength() > 0 && FindJobInfo()) ? TRUE : FALSE) : CLocalePropertyPage::Check()) : TRUE);
}

void CGRDSettingsPrintingPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGRDSettingsPrintingPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CGRDSettingsPrintingPage::PostNcDestroy()
{
	m_pJobs[0].RemoveAll();
	m_pJobs[1].RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CGRDSettingsPrintingPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CGRDSettingsPrintingPage)
	ON_BN_CLICKED(IDC_GRDSETTINGS_PRINTINGPAGE_ADDNAME, OnAddName)
	ON_BN_CLICKED(IDC_GRDSETTINGS_PRINTINGPAGE_REMOVENAME, OnRemoveName)
	ON_BN_CLICKED(IDC_GRDSETTINGS_PRINTINGPAGE_REMOVEALLNAMES, OnRemoveAllNames)
	ON_BN_CLICKED(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND, OnPrintColorLegend)
	ON_BN_CLICKED(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL, OnPrintUnderlineOOL)
	ON_BN_CLICKED(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_NOCOLORS, OnPrintNoColors)
	ON_BN_CLICKED(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_AUTOSCALE, OnPrintAutomaticScale)
	ON_BN_CLICKED(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE, OnPrintFixedScale)
	ON_BN_CLICKED(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS, OnResetComments)
	ON_CBN_EDITCHANGE(IDC_GRDSETTINGS_PRINTINGPAGE_NAME, OnEditchangeName)
	ON_CBN_SELCHANGE(IDC_GRDSETTINGS_PRINTINGPAGE_NAME, OnSelchangeName)
	ON_CBN_SELCHANGE(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, OnSelchangeProfile)
	ON_EN_CHANGE(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT, OnEditchangeComments)
	ON_CONTROL(SBXN_CHANGE, IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE_NUMBER, OnSpinchangePrintFixedScale)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDSettingsPrintingPage message handlers

BOOL CGRDSettingsPrintingPage::OnInitDialog()
{
	INT  nJob;
	INT  nJobs;
	INT  nProfile;
	INT  nProfiles;
	CStringArray  szProfiles;
	CGRDPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	for (CLocalePropertyPage::OnInitDialog(); m_wndComments.SubclassWindow(GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->GetSafeHwnd()); )
	{
		for (nJob = 0, nJobs = (INT)m_pJobs[0].GetSize(); nJob < nJobs; nJob++)
		{
			if ((pJobInfo = m_pJobs[0].GetAt(nJob)) != (CGRDPrintJobInfo *)NULL)
			{
				SendDlgItemMessage(IDC_GRDSETTINGS_PRINTINGPAGE_NAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pJobInfo->GetName());
				continue;
			}
		}
		for (nProfile = 0, nProfiles = (EnumPrintProfiles(szProfiles)) ? (INT)szProfiles.GetSize() : 0; nProfile < nProfiles; nProfile++)
		{
			SendDlgItemMessage(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szProfiles.GetAt(nProfile));
			continue;
		}
		SendDlgItemMessage(IDC_GRDSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_GRDSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_PRINTJOB_DEFAULTNAME)));
		Spinbox_SetRange(GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE_NUMBER), GRDSETTINGSPRINTINGPAGE_MINIMUMSCALE, GRDSETTINGSPRINTINGPAGE_MAXIMUMSCALE);
		GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_DETAILS)->EnableWindow();
		GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_NAME_STATIC)->EnableWindow();
		GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_NAME)->EnableWindow();
		ShowJobInfo();
		break;
	}
	return TRUE;
}

BOOL CGRDSettingsPrintingPage::OnSetActive()
{
	ShowJobInfo();
	return CLocalePropertyPage::OnSetActive();
}

BOOL CGRDSettingsPrintingPage::OnKillActive()
{
	GetParentDialog()->OnDataExchange(GetSafeHwnd(), m_pJobs[0]);
	return CLocalePropertyPage::OnKillActive();
}

BOOL CGRDSettingsPrintingPage::OnDataExchange(CONST CGRDPrintJobs &pJobs)
{
	return m_pJobs[0].Copy(&pJobs);
}

void CGRDSettingsPrintingPage::OnEditchangeName()
{
	CString  szJobName;
	CGRDPrintJobInfo  *pJobInfo;

	for (GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_NAME)->GetWindowText(szJobName); (pJobInfo = FindJobInfo()); )
	{
		ShowJobInfo();
		return;
	}
	GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_ADDNAME)->EnableWindow((!pJobInfo  &&  szJobName.GetLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_REMOVENAME)->EnableWindow((pJobInfo != (CGRDPrintJobInfo *)NULL  &&  szJobName != STRING(IDS_PRINTJOB_DEFAULTNAME)) ? TRUE : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_REMOVEALLNAMES)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PRINTINGPAGE_NAME, CB_GETCOUNT) > 1) ? TRUE : FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)->EnableWindow((szJobName != STRING(IDS_PRINTJOB_DEFAULTNAME)) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsPrintingPage::OnSelchangeName()
{
	SendDlgItemMessage(IDC_GRDSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_GRDSETTINGS_PRINTINGPAGE_NAME, CB_GETCURSEL));
	ShowJobInfo();
}

void CGRDSettingsPrintingPage::OnAddName()
{
	INT  nIndex;
	UINT  nMode;
	UINT  nScale;
	CString  szJobName;
	CString  szProfile;
	CString  szComments;
	CGRDPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	for (; (pJobInfo = new CGRDPrintJobInfo); )
	{
		GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_NAME)->GetWindowText(szJobName);
		GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE)->GetWindowText(szProfile);
		GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->GetWindowText(szComments);
		nMode = (IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_NOCOLORS)) ? (pJobInfo->GetPrintMode() | GRD_PRINT_NOCOLORS) : (pJobInfo->GetPrintMode() & ~GRD_PRINT_NOCOLORS);
		nMode = (IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND)) ? (nMode | GRD_PRINT_COLORLEGEND) : (nMode & ~GRD_PRINT_COLORLEGEND);
		nMode = (IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL)) ? (nMode | GRD_PRINT_UNDERLINEOOL) : (nMode & ~GRD_PRINT_UNDERLINEOOL);
		nMode = (IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_AUTOSCALE)) ? ((nMode | GRD_PRINT_AUTOSCALE) & ~GRD_PRINT_FIXEDSCALE) : nMode;
		nMode = (IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE)) ? ((nMode | GRD_PRINT_FIXEDSCALE) & ~GRD_PRINT_AUTOSCALE) : nMode;
		nMode = (IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)) ? (nMode | GRD_PRINT_CLEARCOMMENTS) : (nMode & ~GRD_PRINT_CLEARCOMMENTS);
		nScale = (IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE)) ? (UINT)Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE_NUMBER)) : 0;
		if (SendDlgItemMessage(IDC_GRDSETTINGS_PRINTINGPAGE_NAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szJobName) >= 0 && SendDlgItemMessage(IDC_GRDSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_GRDSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szJobName)) >= 0)
		{
			for (pJobInfo->SetName(szJobName), pJobInfo->SetProfile(szProfile), pJobInfo->SetComments(szComments), pJobInfo->SetPrintMode(nMode), pJobInfo->SetPrintScale(nScale); (nIndex = m_pJobs[0].Add(pJobInfo)) >= 0; )
			{
				ShowJobInfo();
				break;
			}
			if (nIndex >= 0) break;
		}
		delete pJobInfo;
		break;
	}
	GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsPrintingPage::OnRemoveName()
{
	INT  nJob;
	INT  nJobs;
	CGRDPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	for (nJob = 0, nJobs = (INT)m_pJobs[0].GetSize(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = m_pJobs[0].GetAt(nJob)) && pJobInfo == FindJobInfo())
		{
			if (SendDlgItemMessage(IDC_GRDSETTINGS_PRINTINGPAGE_NAME, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_GRDSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName())) > 0)
			{
				m_pJobs[0].RemoveAt(nJob);
				delete pJobInfo;
			}
			break;
		}
	}
	for (; SendDlgItemMessage(IDC_GRDSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_GRDSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_PRINTJOB_DEFAULTNAME))) >= 0; )
	{
		ShowJobInfo();
		break;
	}
	GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsPrintingPage::OnRemoveAllNames()
{
	INT  nJob;
	INT  nJobs;
	CGRDPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	for (nJob = 0, nJobs = (INT)m_pJobs[0].GetSize(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = m_pJobs[0].GetAt(nJob)) && pJobInfo->GetName() != STRING(IDS_PRINTJOB_DEFAULTNAME) && SendDlgItemMessage(IDC_GRDSETTINGS_PRINTINGPAGE_NAME, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_GRDSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName())) > 0)
		{
			m_pJobs[0].RemoveAt(nJob);
			delete pJobInfo;
			nJobs--;
			nJob--;
		}
	}
	for (; SendDlgItemMessage(IDC_GRDSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_GRDSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_PRINTJOB_DEFAULTNAME))) >= 0; )
	{
		ShowJobInfo();
		break;
	}
	GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsPrintingPage::OnSelchangeProfile()
{
	CString  szProfile;
	CGRDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE)->GetWindowText(szProfile);
		pJobInfo->SetProfile(szProfile);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsPrintingPage::OnPrintColorLegend()
{
	UINT  nMode;
	CGRDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		nMode = (IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND)) ? (pJobInfo->GetPrintMode() | GRD_PRINT_COLORLEGEND) : (pJobInfo->GetPrintMode() & ~GRD_PRINT_COLORLEGEND);
		pJobInfo->SetPrintMode(nMode);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsPrintingPage::OnPrintUnderlineOOL()
{
	UINT  nMode;
	CGRDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		nMode = (IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL)) ? (pJobInfo->GetPrintMode() | GRD_PRINT_UNDERLINEOOL) : (pJobInfo->GetPrintMode() & ~GRD_PRINT_UNDERLINEOOL);
		pJobInfo->SetPrintMode(nMode);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsPrintingPage::OnPrintNoColors()
{
	UINT  nMode;
	CGRDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		nMode = (IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_NOCOLORS)) ? (pJobInfo->GetPrintMode() | GRD_PRINT_NOCOLORS) : (pJobInfo->GetPrintMode() & ~GRD_PRINT_NOCOLORS);
		pJobInfo->SetPrintMode(nMode);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsPrintingPage::OnPrintAutomaticScale()
{
	CGRDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo())) pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | GRD_PRINT_AUTOSCALE) & ~GRD_PRINT_FIXEDSCALE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE_NUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsPrintingPage::OnPrintFixedScale()
{
	CGRDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | GRD_PRINT_FIXEDSCALE) & ~GRD_PRINT_AUTOSCALE);
		pJobInfo->SetPrintScale(GRDSETTINGSPRINTINGPAGE_DEFAULTSCALE);
	}
	Spinbox_SetPos(GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE_NUMBER), GRDSETTINGSPRINTINGPAGE_DEFAULTSCALE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE_NUMBER)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE_NUMBER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsPrintingPage::OnSpinchangePrintFixedScale()
{
	CGRDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo())) pJobInfo->SetPrintScale((UINT)Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE_NUMBER)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsPrintingPage::OnEditchangeComments()
{
	CString  szComments;
	CGRDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->GetWindowText(szComments);
		GetDlgItem(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)->EnableWindow(!szComments.IsEmpty());
		CheckDlgButton(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS, (!szComments.IsEmpty()) ? IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS) : FALSE);
		pJobInfo->SetPrintMode((IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)) ? (pJobInfo->GetPrintMode() | GRD_PRINT_CLEARCOMMENTS) : (pJobInfo->GetPrintMode() & ~GRD_PRINT_CLEARCOMMENTS));
		pJobInfo->SetComments(szComments);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsPrintingPage::OnResetComments()
{
	UINT  nMode;
	CGRDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		nMode = (IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)) ? (pJobInfo->GetPrintMode() | GRD_PRINT_CLEARCOMMENTS) : (pJobInfo->GetPrintMode() & ~GRD_PRINT_CLEARCOMMENTS);
		pJobInfo->SetPrintMode(nMode);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CGRDSettingsPrintJobsPage property page

IMPLEMENT_DYNCREATE(CGRDSettingsPrintJobsPage, CLocalePropertyPage)

CGRDSettingsPrintJobsPage::CGRDSettingsPrintJobsPage() : CLocalePropertyPage(CGRDSettingsPrintJobsPage::IDD)
{
	//{{AFX_DATA_INIT(CGRDSettingsPrintJobsPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CGRDSettingsPrintJobsPage::Initialize()
{
	CGRDOpenDialog  *pDialog;

	return((((pDialog = GetParentDialog()->GetParentDialog()) && pDialog->GetPrintJobs(m_pJobs[0])) || GetParentDisplay()->GetPrintJobs(m_pJobs[0])) ? m_pJobs[1].Copy(&m_pJobs[0]) : FALSE);
}

BOOL CGRDSettingsPrintJobsPage::GetJobs(CGRDPrintJobs &pJobs) CONST
{
	return((pJobs.Copy(&m_pJobs[0])) ? Check(FALSE) : FALSE);
}

CGRDSettingsDialog *CGRDSettingsPrintJobsPage::GetParentDialog() CONST
{
	return((CGRDSettingsDialog *)CLocalePropertyPage::GetParent());
}

CGRDWnd *CGRDSettingsPrintJobsPage::GetParentDisplay() CONST
{
	return((CGRDWnd *)GetParentDialog()->GetParentDisplay());
}

BOOL CGRDSettingsPrintJobsPage::EnumJobs()
{
	INT  nJob;
	INT  nJobs;
	UINT  nMode;
	CGRDPrintJobInfo  *pJobInfo;

	SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, LB_RESETCONTENT);
	SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_RESETCONTENT);
	for (nJob = 0, nJobs = (INT)m_pJobs[0].GetSize(); nJob < nJobs; nJob = nJob + 1)
	{
		if ((pJobInfo = m_pJobs[0].GetAt(nJob)) && pJobInfo->GetName() != STRING(IDS_PRINTJOB_DEFAULTNAME))
		{
			if (SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pJobInfo->GetName()) >= 0)
			{
				if (((nMode = pJobInfo->GetPrintMode()) & GRD_PRINT_ACTIVE) && ((nMode & GRD_PRINT_ATTIME) || (nMode & GRD_PRINT_ATDAILYTIME) || (nMode & GRD_PRINT_ATEVENT) || (nMode & GRD_PRINT_ATEXPIRATION)))
				{
					if (SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR)
					{
						pJobInfo->SetPrintMode(nMode & ~(GRD_PRINT_ACTIVE | GRD_PRINT_ATTIME | GRD_PRINT_ATDAILYTIME | GRD_PRINT_ATEVENT | GRD_PRINT_ATEXPIRATION | GRD_PRINT_REPEATBYINTERVAL | GRD_PRINT_REPEATSTOPBYCOUNT | GRD_PRINT_REPEATSTOPBYTIME | GRD_PRINT_DAILYREPEATSTOPBYCOUNT | GRD_PRINT_DAILYREPEATSTOPBYTIME));
						continue;
					}
				}
			}
		}
	}
	if (SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, LB_GETCOUNT) > 0)
	{
		SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, LB_SETCURSEL);
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_DETAILS)->EnableWindow();
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS_STATIC)->EnableWindow();
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS)->EnableWindow();
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)Listbox_GetText(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS), (INT)SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, LB_GETCURSEL))) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_REMOVEJOB)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
		ShowJobInfo();
		return TRUE;
	}
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_DETAILS)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_REMOVEJOB)->EnableWindow(FALSE);
	ShowJobInfo();
	return FALSE;
}

BOOL CGRDSettingsPrintJobsPage::EnumEvents()
{
	INT  nEvent;
	INT  nEvents;
	CTelemetryEvents  pEvents;
	CTelemetryEventInfo  *pEventInfo;

	for (nEvent = 0, nEvents = (GetTelemetryEvents(pEvents)) ? (INT)pEvents.GetSize() : 0; nEvent < nEvents; nEvent++)
	{
		if ((pEventInfo = pEvents.GetAt(nEvent))) SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pEventInfo->GetName());
		continue;
	}
	return((SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CGRDSettingsPrintJobsPage::ShowJobInfo()
{
	UINT  nStopCount;
	CString  szEvent;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CTimeSpan  tDailyTime;
	CGRDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		Timespinbox_SetTime(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME), (pJobInfo->GetPrintAtTime(tTime) || pJobInfo->GetPrintAtTime(tTime, tInterval) || pJobInfo->GetPrintAtTime(tTime, tInterval, nStopCount) || pJobInfo->GetPrintAtTime(tTime, tInterval, tStopTime)) ? tTime : CTime::GetCurrentTime().GetTime());
		Timespinbox_SetTime(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME), (pJobInfo->GetPrintAtDailyTime(tDailyTime) || pJobInfo->GetPrintAtDailyTime(tDailyTime, nStopCount) || pJobInfo->GetPrintAtDailyTime(tDailyTime, tStopTime)) ? CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + tDailyTime.GetTotalSeconds()) : CTime::GetCurrentTime().GetTime());
		SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_SETCURSEL, (pJobInfo->GetPrintAtEvent(szEvent)) ? (WPARAM)SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szEvent) : (WPARAM)-1);
		SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, (SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_GRDSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS)) < 0 && (pJobInfo->GetPrintMode() & GRD_PRINT_ATTIME)) ? CB_ADDSTRING : CB_FINDSTRING, (WPARAM)NULL, (LPARAM)STRING(IDS_GRDSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS));
		SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, (SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_GRDSETTINGS_PRINTJOBSPAGE_DAILYPRINTS)) < 0 && (pJobInfo->GetPrintMode() & GRD_PRINT_ATDAILYTIME)) ? CB_ADDSTRING : CB_FINDSTRING, (WPARAM)NULL, (LPARAM)STRING(IDS_GRDSETTINGS_PRINTJOBSPAGE_DAILYPRINTS));
		SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_SETCURSEL, ((pJobInfo->GetPrintMode() & GRD_PRINT_ATTIME) || (pJobInfo->GetPrintMode() & GRD_PRINT_ATDAILYTIME)) ? (WPARAM)SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)((pJobInfo->GetPrintMode() & GRD_PRINT_ATTIME) ? STRING(IDS_GRDSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS) : STRING(IDS_GRDSETTINGS_PRINTJOBSPAGE_DAILYPRINTS))) : (WPARAM)-1);
		CheckDlgButton(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME, (pJobInfo->GetPrintMode() & GRD_PRINT_ATTIME) ? TRUE : FALSE);
		CheckDlgButton(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME, (pJobInfo->GetPrintMode() & GRD_PRINT_ATDAILYTIME) ? TRUE : FALSE);
		CheckDlgButton(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT, (pJobInfo->GetPrintMode() & GRD_PRINT_ATEVENT) ? ((SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_GETCURSEL) >= 0) ? TRUE : FALSE) : FALSE);
		CheckDlgButton(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEXPIRATION, (pJobInfo->GetPrintMode() & GRD_PRINT_ATEXPIRATION) ? TRUE : FALSE);
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR)->EnableWindow();
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME)->EnableWindow();
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME));
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)->EnableWindow();
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT));
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT));
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEXPIRATION)->EnableWindow();
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		SetJobRepetitionInfo();
		return;
	}
	CheckDlgButton(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME, FALSE);
	CheckDlgButton(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME, FALSE);
	CheckDlgButton(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT, FALSE);
	CheckDlgButton(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEXPIRATION, FALSE);
	CheckDlgButton(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME, FALSE);
	CheckDlgButton(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, FALSE);
	CheckDlgButton(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, FALSE);
	SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_SETCURSEL, (WPARAM)-1);
	SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_SETCURSEL, (WPARAM)-1);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEXPIRATION)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow(FALSE);
}

BOOL CGRDSettingsPrintJobsPage::CheckJobInfo() CONST
{
	UINT  nStopCount;
	CString  szEvent;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CTimeSpan  tDailyTime;
	CGRDPrintJobInfo  *pJobInfo;

	return(((pJobInfo = FindJobInfo())) ? ((pJobInfo->GetPrintAtTime(tTime) && tTime > CTime::GetCurrentTime()) || pJobInfo->GetPrintAtTime(tTime, tInterval) || (pJobInfo->GetPrintAtTime(tTime, tInterval, nStopCount) && tTime.GetTime() + tInterval.GetTotalSeconds()*(TIMEKEY)nStopCount > CTime::GetCurrentTime().GetTime()) || (pJobInfo->GetPrintAtTime(tTime, tInterval, tStopTime) && tStopTime > CTime::GetCurrentTime()) || pJobInfo->GetPrintAtDailyTime(tDailyTime) || pJobInfo->GetPrintAtDailyTime(tDailyTime, nStopCount) || (pJobInfo->GetPrintAtDailyTime(tDailyTime, tStopTime) && tStopTime > CTime::GetCurrentTime()) || pJobInfo->GetPrintAtEvent(szEvent) || (pJobInfo->GetPrintMode() & GRD_PRINT_ATEXPIRATION)) : FALSE);
}

CGRDPrintJobInfo *CGRDSettingsPrintJobsPage::FindJobInfo(BOOL bActive) CONST
{
	INT  nJob;
	INT  nJobs;
	CString  szJobName[2];
	CGRDPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (INT)m_pJobs[0].GetSize(), szJobName[0] = Listbox_GetText(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS), (INT)GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS)->SendMessage(LB_GETCURSEL)), szJobName[1] = Listbox_GetText(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS), (INT)GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS)->SendMessage(LB_GETCURSEL)), szJobName[0] = (!bActive) ? szJobName[0] : szJobName[1]; nJob < nJobs; nJob++)
	{
		if ((pJobInfo = m_pJobs[0].GetAt(nJob)) && pJobInfo->GetName() == szJobName[0]) break;
		continue;
	}
	return((nJob < nJobs) ? pJobInfo : (CGRDPrintJobInfo *)NULL);
}

VOID CGRDSettingsPrintJobsPage::SetJobRepetitionInfo()
{
	UINT  nStopCount;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CTimeSpan  tDailyTime;
	CGRDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		Timespinbox_SetTime(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), ((GetJobRepetitionType() == GRDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  pJobInfo->GetPrintAtTime(tTime, tInterval, tStopTime)) || (GetJobRepetitionType() == GRDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  pJobInfo->GetPrintAtDailyTime(tDailyTime, tStopTime))) ? tStopTime : CTime::GetCurrentTime().GetTime());
		Spinbox_SetPos(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME), (pJobInfo->GetPrintAtTime(tTime, tInterval) || pJobInfo->GetPrintAtTime(tTime, tInterval, nStopCount) || pJobInfo->GetPrintAtTime(tTime, tInterval, tStopTime)) ? (tInterval.GetTotalSeconds() / SECONDSPERMINUTE) : 0);
		Spinbox_SetPos(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), ((GetJobRepetitionType() == GRDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  pJobInfo->GetPrintAtTime(tTime, tInterval, nStopCount)) || (GetJobRepetitionType() == GRDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  pJobInfo->GetPrintAtDailyTime(tDailyTime, nStopCount))) ? nStopCount : 0);
		CheckDlgButton(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME, (GetJobRepetitionType() == GRDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY && (pJobInfo->GetPrintMode() & GRD_PRINT_REPEATBYINTERVAL)) ? TRUE : FALSE);
		CheckDlgButton(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, ((GetJobRepetitionType() == GRDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY && (pJobInfo->GetPrintMode() & GRD_PRINT_REPEATSTOPBYCOUNT)) || (GetJobRepetitionType() == GRDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY && (pJobInfo->GetPrintMode() & GRD_PRINT_DAILYREPEATSTOPBYCOUNT))) ? TRUE : FALSE);
		CheckDlgButton(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, ((GetJobRepetitionType() == GRDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY && (pJobInfo->GetPrintMode() & GRD_PRINT_REPEATSTOPBYTIME)) || (GetJobRepetitionType() == GRDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY && (pJobInfo->GetPrintMode() & GRD_PRINT_DAILYREPEATSTOPBYTIME))) ? TRUE : FALSE);
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)->EnableWindow((GetJobRepetitionType() == GRDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY) ? TRUE : FALSE);
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)->EnableWindow(GetJobRepetitionType() == GRDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC)->EnableWindow(GetJobRepetitionType() == GRDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC)->EnableWindow((IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && (GetJobRepetitionType() == GRDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY || IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)));
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)->EnableWindow((IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && (GetJobRepetitionType() == GRDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY || IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)));
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow((IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES));
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow((IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES));
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)->EnableWindow((IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && (GetJobRepetitionType() == GRDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY || IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)));
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow((IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME));
		return;
	}
	CheckDlgButton(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME, FALSE);
	CheckDlgButton(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, FALSE);
	CheckDlgButton(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow(FALSE);
}

UINT CGRDSettingsPrintJobsPage::GetJobRepetitionType() CONST
{
	CString  szRepetitionType;

	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE)->GetWindowText(szRepetitionType);
	return((szRepetitionType == STRING(IDS_GRDSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS) || szRepetitionType == STRING(IDS_GRDSETTINGS_PRINTJOBSPAGE_DAILYPRINTS)) ? ((szRepetitionType == STRING(IDS_GRDSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS)) ? GRDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY : GRDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY) : 0);
}

BOOL CGRDSettingsPrintJobsPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? !m_pJobs[0].Compare(&m_pJobs[1]) : CLocalePropertyPage::IsModified()) : FALSE);
}

BOOL CGRDSettingsPrintJobsPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? TRUE : CLocalePropertyPage::Check()) : TRUE);
}

void CGRDSettingsPrintJobsPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGRDSettingsPrintJobsPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CGRDSettingsPrintJobsPage::PostNcDestroy()
{
	m_pJobs[0].RemoveAll();
	m_pJobs[1].RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CGRDSettingsPrintJobsPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CGRDSettingsPrintJobsPage)
	ON_BN_CLICKED(IDC_GRDSETTINGS_PRINTJOBSPAGE_ADDJOB, OnAddJob)
	ON_BN_CLICKED(IDC_GRDSETTINGS_PRINTJOBSPAGE_REMOVEJOB, OnRemoveJob)
	ON_BN_CLICKED(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME, OnPrintAtTime)
	ON_BN_CLICKED(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME, OnPrintAtDailyTime)
	ON_BN_CLICKED(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT, OnPrintAtEvent)
	ON_BN_CLICKED(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEXPIRATION, OnPrintAtExpiration)
	ON_BN_CLICKED(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME, OnRepeatByTime)
	ON_BN_CLICKED(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, OnRepetitionStopByCopies)
	ON_BN_CLICKED(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, OnRepetitionStopByTime)
	ON_CBN_SELCHANGE(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, OnSelchangeEvent)
	ON_CBN_SELCHANGE(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, OnSelchangeRepetitionType)
	ON_LBN_SELCHANGE(IDC_GRDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, OnSelchangeDefinedJob)
	ON_LBN_SELCHANGE(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, OnSelchangeActiveJob)
	ON_CONTROL(SBXN_CHANGE, IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME, OnSpinchangeRepeatTime)
	ON_CONTROL(SBXN_CHANGE, IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES, OnSpinchangeRepetitionStopCopies)
	ON_CONTROL(TSBXN_CHANGE, IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME, OnSpinchangePrintTime)
	ON_CONTROL(TSBXN_CHANGE, IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME, OnSpinchangePrintDailyTime)
	ON_CONTROL(TSBXN_CHANGE, IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME, OnSpinchangeRepetitionStopTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDSettingsPrintJobsPage message handlers

BOOL CGRDSettingsPrintJobsPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	Spinbox_SetRange(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME), GRDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMINTERVAL, GRDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMINTERVAL);
	Spinbox_SetRange(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), GRDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES, GRDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES);
	EnumEvents();
	return TRUE;
}

BOOL CGRDSettingsPrintJobsPage::OnSetActive()
{
	EnumJobs();
	return CLocalePropertyPage::OnSetActive();
}

BOOL CGRDSettingsPrintJobsPage::OnKillActive()
{
	GetParentDialog()->OnDataExchange(GetSafeHwnd(), m_pJobs[0]);
	return CLocalePropertyPage::OnKillActive();
}

BOOL CGRDSettingsPrintJobsPage::OnDataExchange(CONST CGRDPrintJobs &pJobs)
{
	return m_pJobs[0].Copy(&pJobs);
}

void CGRDSettingsPrintJobsPage::OnAddJob()
{
	CGRDPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	if ((pJobInfo = FindJobInfo()))
	{
		pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() | GRD_PRINT_ACTIVE);
		SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pJobInfo->GetName());
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow(FALSE);
	}
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsPrintJobsPage::OnRemoveJob()
{
	CGRDPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	if ((pJobInfo = FindJobInfo(TRUE)))
	{
		for (pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~(GRD_PRINT_ACTIVE | GRD_PRINT_ATTIME | GRD_PRINT_ATDAILYTIME | GRD_PRINT_ATEVENT | GRD_PRINT_ATEXPIRATION | GRD_PRINT_REPEATBYINTERVAL | GRD_PRINT_REPEATSTOPBYCOUNT | GRD_PRINT_REPEATSTOPBYTIME | GRD_PRINT_DAILYREPEATSTOPBYCOUNT | GRD_PRINT_DAILYREPEATSTOPBYTIME)), SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCURSEL)); pJobInfo == FindJobInfo(); )
		{
			ShowJobInfo();
			break;
		}
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_REMOVEJOB)->EnableWindow(FALSE);
	}
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsPrintJobsPage::OnSelchangeDefinedJob()
{
	CGRDPrintJobInfo  *pJobInfo;

	ShowJobInfo();
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow(((pJobInfo = FindJobInfo()) && SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
}

void CGRDSettingsPrintJobsPage::OnSelchangeActiveJob()
{
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_REMOVEJOB)->EnableWindow();
}

void CGRDSettingsPrintJobsPage::OnPrintAtTime()
{
	CTimeKey  tTime;
	CGRDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		if (IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME))
		{
			Timespinbox_SetTime(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME), (tTime = CTime::GetCurrentTime().GetTime() + SECONDSPERMINUTE*GRDSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL));
			SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)STRING(IDS_GRDSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS));
			pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | GRD_PRINT_ATTIME) & ~(GRD_PRINT_REPEATBYINTERVAL | GRD_PRINT_REPEATSTOPBYCOUNT | GRD_PRINT_REPEATSTOPBYTIME));
			pJobInfo->SetPrintAtTime(tTime);
		}
		else
		{
			SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_GRDSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS)));
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~(GRD_PRINT_ATTIME | GRD_PRINT_REPEATBYINTERVAL | GRD_PRINT_REPEATSTOPBYCOUNT | GRD_PRINT_REPEATSTOPBYTIME));
		}
		SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_SETCURSEL, (IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) ? (WPARAM)SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)((IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME)) ? STRING(IDS_GRDSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS) : STRING(IDS_GRDSETTINGS_PRINTJOBSPAGE_DAILYPRINTS))) : (WPARAM)-1);
		Spinbox_SetRange(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), (IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME)) ? (GRDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES + 1) : GRDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES, GRDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES);
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME));
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		SetJobRepetitionInfo();
	}
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsPrintJobsPage::OnPrintAtDailyTime()
{
	CTimeKey  tTime;
	CGRDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		if (IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME))
		{
			Timespinbox_SetTime(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME), (tTime = CTime::GetCurrentTime().GetTime() + SECONDSPERMINUTE*GRDSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL));
			SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)STRING(IDS_GRDSETTINGS_PRINTJOBSPAGE_DAILYPRINTS));
			pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | GRD_PRINT_ATDAILYTIME) & ~(GRD_PRINT_DAILYREPEATSTOPBYCOUNT | GRD_PRINT_DAILYREPEATSTOPBYTIME));
			pJobInfo->SetPrintAtDailyTime(tTime.GetTime() % SECONDSPERDAY);
		}
		else
		{
			SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_GRDSETTINGS_PRINTJOBSPAGE_DAILYPRINTS)));
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~(GRD_PRINT_ATDAILYTIME | GRD_PRINT_DAILYREPEATSTOPBYCOUNT | GRD_PRINT_DAILYREPEATSTOPBYTIME));
		}
		SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_SETCURSEL, (IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) ? (WPARAM)SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)((IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) ? STRING(IDS_GRDSETTINGS_PRINTJOBSPAGE_DAILYPRINTS) : STRING(IDS_GRDSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS))) : (WPARAM)-1);
		Spinbox_SetRange(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), (IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) ? GRDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES : (GRDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES + 1), GRDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES);
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		SetJobRepetitionInfo();
	}
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsPrintJobsPage::OnPrintAtEvent()
{
	CString  szEvent;
	CGRDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		if (IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT))
		{
			SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_SETCURSEL);
			GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT)->GetWindowText(szEvent);
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() | GRD_PRINT_ATEVENT);
			pJobInfo->SetPrintAtEvent(szEvent);
		}
		else
		{
			SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_SETCURSEL, (WPARAM)-1);
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~GRD_PRINT_ATEVENT);
			pJobInfo->SetPrintAtEvent(EMPTYSTRING);
		}
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT));
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT));
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsPrintJobsPage::OnPrintAtExpiration()
{
	UINT  nMode;
	CGRDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		nMode = pJobInfo->GetPrintMode();
		pJobInfo->SetPrintMode((IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEXPIRATION)) ? (nMode | GRD_PRINT_ATEXPIRATION) : (nMode & ~GRD_PRINT_ATEXPIRATION));
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsPrintJobsPage::OnSelchangeEvent()
{
	CString  szEvent;
	CGRDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT)->GetWindowText(szEvent);
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() | GRD_PRINT_ATEVENT);
		pJobInfo->SetPrintAtEvent(szEvent);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsPrintJobsPage::OnSelchangeRepetitionType()
{
	Spinbox_SetRange(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), (GetJobRepetitionType() == GRDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY) ? (GRDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES + 1) : GRDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES, GRDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES);
	SetJobRepetitionInfo();
}

void CGRDSettingsPrintJobsPage::OnRepeatByTime()
{
	CGRDPrintJobInfo  *pJobInfo;

	for (CheckDlgButton(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME, !IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)); IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME); )
	{
		Spinbox_SetPos(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME), GRDSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL);
		break;
	}
	for (; (pJobInfo = FindJobInfo()); )
	{
		if (IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME))
		{
			pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | GRD_PRINT_REPEATBYINTERVAL) & ~(GRD_PRINT_REPEATSTOPBYCOUNT | GRD_PRINT_REPEATSTOPBYTIME));
			pJobInfo->SetPrintAtTime(Timespinbox_GetTime(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), SECONDSPERMINUTE*GRDSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL);
			GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
			break;
		}
		pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~(GRD_PRINT_REPEATBYINTERVAL | GRD_PRINT_REPEATSTOPBYCOUNT | GRD_PRINT_REPEATSTOPBYTIME));
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		break;
	}
	CheckDlgButton(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, FALSE);
	CheckDlgButton(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsPrintJobsPage::OnRepetitionStopByCopies()
{
	CGRDPrintJobInfo  *pJobInfo;

	for (CheckDlgButton(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, !IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)), GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)), GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)); IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES); )
	{
		Spinbox_SetPos(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), GRDSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTCOPIES);
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow(FALSE);
		CheckDlgButton(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, FALSE);
		break;
	}
	for (; (pJobInfo = FindJobInfo()); )
	{
		if (IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES))
		{
			if (GetJobRepetitionType() == GRDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY)
			{
				pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | GRD_PRINT_REPEATSTOPBYCOUNT) & ~GRD_PRINT_REPEATSTOPBYTIME);
				pJobInfo->SetPrintAtTime(Timespinbox_GetTime(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)), GRDSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTCOPIES);
			}
			if (GetJobRepetitionType() == GRDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY)
			{
				pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | GRD_PRINT_DAILYREPEATSTOPBYCOUNT) & ~GRD_PRINT_DAILYREPEATSTOPBYTIME);
				pJobInfo->SetPrintAtDailyTime(Timespinbox_GetTime(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)).GetTime() % SECONDSPERDAY, GRDSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTCOPIES);
			}
			GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
			break;
		}
		pJobInfo->SetPrintMode((GetJobRepetitionType() == GRDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY) ? (pJobInfo->GetPrintMode() & ~GRD_PRINT_REPEATSTOPBYCOUNT) : (pJobInfo->GetPrintMode() & ~GRD_PRINT_DAILYREPEATSTOPBYCOUNT));
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		break;
	}
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsPrintJobsPage::OnRepetitionStopByTime()
{
	CTimeKey  tStopTime;
	CGRDPrintJobInfo  *pJobInfo;

	for (CheckDlgButton(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, !IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)), GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)); IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME); )
	{
		for (CheckDlgButton(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, FALSE); GetJobRepetitionType() == GRDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY; )
		{
			Timespinbox_SetTime(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)).GetTime() + SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME))));
			break;
		}
		if (GetJobRepetitionType() == GRDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY) Timespinbox_SetTime(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)).GetTime() + CTimeSpan(1, 0, 0, 0).GetTotalSeconds()));
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow(FALSE);
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow(FALSE);
		break;
	}
	for (; (pJobInfo = FindJobInfo()); )
	{
		if (IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME))
		{
			if (GetJobRepetitionType() == GRDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY)
			{
				pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | GRD_PRINT_REPEATSTOPBYTIME) & ~GRD_PRINT_REPEATSTOPBYCOUNT);
				pJobInfo->SetPrintAtTime(Timespinbox_GetTime(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)), tStopTime);
			}
			if (GetJobRepetitionType() == GRDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY)
			{
				pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | GRD_PRINT_DAILYREPEATSTOPBYTIME) & ~GRD_PRINT_DAILYREPEATSTOPBYCOUNT);
				pJobInfo->SetPrintAtDailyTime(Timespinbox_GetTime(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)).GetTime() % SECONDSPERDAY, tStopTime);
			}
			GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
			break;
		}
		pJobInfo->SetPrintMode((GetJobRepetitionType() == GRDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY) ? (pJobInfo->GetPrintMode() & ~GRD_PRINT_REPEATSTOPBYTIME) : (pJobInfo->GetPrintMode() & ~GRD_PRINT_DAILYREPEATSTOPBYTIME));
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		break;
	}
	GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsPrintJobsPage::OnSpinchangePrintTime()
{
	UINT  nStopCount;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeKey  tPrintTime;
	CTimeKey  tPrintStopTime;
	CTimeSpan  tPrintInterval;
	CGRDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)); pJobInfo->GetPrintAtTime(tPrintTime); )
		{
			pJobInfo->SetPrintAtTime(tTime);
			break;
		}
		if (pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval)) pJobInfo->SetPrintAtTime(tTime, tPrintInterval);
		if (pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, nStopCount)) pJobInfo->SetPrintAtTime(tTime, tPrintInterval, nStopCount);
		if (pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, tPrintStopTime)) pJobInfo->SetPrintAtTime(tTime, tPrintInterval, (tTime + tPrintInterval.GetTotalSeconds() > tPrintStopTime.GetTime()) ? CTimeKey(tTime.GetTime() + tPrintInterval.GetTotalSeconds()) : tPrintStopTime);
		Timespinbox_SetTime(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (GetJobRepetitionType() == GRDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)) ? ((tTime + tPrintInterval.GetTotalSeconds() > tPrintStopTime.GetTime()) ? (tTime.GetTime() + tPrintInterval.GetTotalSeconds()) : tPrintStopTime) : tStopTime);
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsPrintJobsPage::OnSpinchangePrintDailyTime()
{
	UINT  nStopCount;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeKey  tPrintStopTime;
	CTimeSpan  tPrintTime;
	CGRDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)), tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)); pJobInfo->GetPrintAtDailyTime(tPrintTime); )
		{
			pJobInfo->SetPrintAtDailyTime(tTime.GetTime() % SECONDSPERDAY);
			break;
		}
		if (pJobInfo->GetPrintAtDailyTime(tPrintTime, nStopCount)) pJobInfo->SetPrintAtDailyTime(tTime.GetTime() % SECONDSPERDAY, nStopCount);
		if (pJobInfo->GetPrintAtDailyTime(tPrintTime, tPrintStopTime)) pJobInfo->SetPrintAtDailyTime(tTime.GetTime() % SECONDSPERDAY, (SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + tTime.GetTime() % SECONDSPERDAY > tPrintStopTime.GetTime()) ? CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY + 1) + tTime.GetTime() % SECONDSPERDAY) : tPrintStopTime);
		Timespinbox_SetTime(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (GetJobRepetitionType() == GRDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)) ? ((SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + tTime.GetTime() % SECONDSPERDAY > tPrintStopTime.GetTime()) ? CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY + 1) + tTime.GetTime() % SECONDSPERDAY) : tPrintStopTime) : tStopTime);
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsPrintJobsPage::OnSpinchangeRepeatTime()
{
	UINT  nStopCount;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeKey  tPrintTime;
	CTimeKey  tPrintStopTime;
	CTimeSpan  tPrintInterval;
	CGRDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)); pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval); )
		{
			pJobInfo->SetPrintAtTime(tPrintTime, SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)));
			break;
		}
		if (pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, nStopCount)) pJobInfo->SetPrintAtTime(tPrintTime, SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)), nStopCount);
		if (pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, tPrintStopTime)) pJobInfo->SetPrintAtTime(tPrintTime, SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)), (tPrintTime.GetTime() + SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)) > tPrintStopTime.GetTime()) ? CTimeKey(tPrintTime.GetTime() + SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME))) : tPrintStopTime);
		Timespinbox_SetTime(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (GetJobRepetitionType() == GRDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  IsDlgButtonChecked(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)) ? ((tPrintTime.GetTime() + SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)) > tPrintStopTime.GetTime()) ? CTimeKey(tPrintTime.GetTime() + SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME))) : tPrintStopTime) : tStopTime);
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsPrintJobsPage::OnSpinchangeRepetitionStopCopies()
{
	UINT  nStopCount;
	UINT  nPrintStopCount;
	CTimeKey  tPrintTime;
	CTimeSpan  tPrintInterval;
	CTimeSpan  tPrintDailyTime;
	CGRDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (nStopCount = (UINT)Spinbox_GetPos(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)); GetJobRepetitionType() == GRDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY && pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, nPrintStopCount); )
		{
			pJobInfo->SetPrintAtTime(tPrintTime, tPrintInterval, nStopCount);
			break;
		}
		if (GetJobRepetitionType() == GRDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  pJobInfo->GetPrintAtDailyTime(tPrintDailyTime, nPrintStopCount)) pJobInfo->SetPrintAtDailyTime(tPrintDailyTime, nStopCount);
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDSettingsPrintJobsPage::OnSpinchangeRepetitionStopTime()
{
	CTimeKey  tTime;
	CTimeKey  tTimeKey;
	CTimeKey  tStopTime;
	CTimeKey  tPrintTime;
	CTimeKey  tPrintStopTime;
	CTimeSpan  tPrintInterval;
	CTimeSpan  tPrintDailyTime;
	CGRDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)); GetJobRepetitionType() == GRDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY && pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, tPrintStopTime); )
		{
			if (tTime > tStopTime.GetTime() - tPrintInterval.GetTotalSeconds()) Timespinbox_SetTime(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (tStopTime = tTime.GetTime() + tPrintInterval.GetTotalSeconds()));
			pJobInfo->SetPrintAtTime(tTime, tPrintInterval, tStopTime);
			break;
		}
		if (GetJobRepetitionType() == GRDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  pJobInfo->GetPrintAtDailyTime(tPrintDailyTime, tPrintStopTime))
		{
			if (SECONDSPERDAY*(tTimeKey.GetTime() / SECONDSPERDAY) + tPrintDailyTime.GetTotalSeconds() > tStopTime.GetTime()) Timespinbox_SetTime(GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (tStopTime = SECONDSPERDAY*(tTimeKey.GetTime() / SECONDSPERDAY) + tPrintDailyTime.GetTotalSeconds()));
			pJobInfo->SetPrintAtDailyTime(tPrintDailyTime, tStopTime);
		}
		GetDlgItem(IDC_GRDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_GRDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CGRDSettingsTabCtrl

IMPLEMENT_DYNCREATE(CGRDSettingsTabCtrl, CTabCtrl)

BEGIN_MESSAGE_MAP(CGRDSettingsTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CGRDSettingsTabCtrl)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDSettingsTabCtrl message handlers


/////////////////////////////////////////////////////////////////////////////
// CGRDSettingsDialog

IMPLEMENT_DYNCREATE(CGRDSettingsDialog, CDisplayPropertySheetDialog)

CGRDSettingsDialog::CGRDSettingsDialog() : CDisplayPropertySheetDialog()
{
	AddPage(&m_pageLayout);
	AddPage(&m_pageChart);
	AddPage(&m_pageParameters);
	AddPage(&m_pageRetrieving);
	AddPage(&m_pagePrinting);
	AddPage(&m_pagePrintJobs);
}

BOOL CGRDSettingsDialog::GetLayout(CGRDLayout &cLayout, CUIntArray &nColumns) CONST
{
	return((m_pageLayout.GetLayout(nColumns) && ((GetActivePage()->GetSafeHwnd() != m_pageParameters.GetSafeHwnd() && m_pageChart.GetLayout(cLayout)) || (GetActivePage()->GetSafeHwnd() == m_pageParameters.GetSafeHwnd() && m_pageParameters.GetLayout(cLayout)))) ? TRUE : FALSE);
}

BOOL CGRDSettingsDialog::GetLayoutColors(CUIntArray &nColors) CONST
{
	return m_pageLayout.GetColors(nColors);
}

BOOL CGRDSettingsDialog::GetLayoutTitleFont(LPLOGFONT pTitleFont) CONST
{
	return m_pageLayout.GetTitleFont(pTitleFont);
}

BOOL CGRDSettingsDialog::GetLayoutItemsFont(LPLOGFONT pItemsFont) CONST
{
	return m_pageLayout.GetItemsFont(pItemsFont);
}

BOOL CGRDSettingsDialog::GetLayoutValuesFont(LPLOGFONT pValuesFont) CONST
{
	return m_pageLayout.GetValuesFont(pValuesFont);
}

BOOL CGRDSettingsDialog::GetLayoutAxesFont(LPLOGFONT pAxesFont) CONST
{
	return m_pageLayout.GetAxesFont(pAxesFont);
}

BOOL CGRDSettingsDialog::GetLayoutInvalidDataMode(BOOL &bEnable) CONST
{
	return m_pageLayout.GetInvalidDataMode(bEnable);
}

BOOL CGRDSettingsDialog::GetLayoutBadDataMode(BOOL &bEnable) CONST
{
	return m_pageLayout.GetBadDataMode(bEnable);
}

BOOL CGRDSettingsDialog::GetLayoutToolTipMode(BOOL &bEnable) CONST
{
	return m_pageLayout.GetToolTipMode(bEnable);
}

BOOL CGRDSettingsDialog::IsLayoutModified() CONST
{
	return m_pageLayout.IsModified() || m_pageChart.IsModified() || m_pageParameters.IsModified();
}

BOOL CGRDSettingsDialog::GetRetrieveFileName(CString &szFileName) CONST
{
	return m_pageRetrieving.GetDataSourceFileName(szFileName);
}

BOOL CGRDSettingsDialog::IsRetrievingModified() CONST
{
	return m_pageRetrieving.IsModified();
}

BOOL CGRDSettingsDialog::GetPrintJobs(CGRDPrintJobs &pPrintJobs) CONST
{
	return(((GetActivePage()->GetSafeHwnd() != m_pagePrintJobs.GetSafeHwnd() && m_pagePrinting.GetJobs(pPrintJobs)) || (GetActivePage()->GetSafeHwnd() == m_pagePrintJobs.GetSafeHwnd() && m_pagePrintJobs.GetJobs(pPrintJobs))) ? TRUE : FALSE);
}

BOOL CGRDSettingsDialog::IsPrintingModified() CONST
{
	return m_pagePrinting.IsModified() || m_pagePrintJobs.IsModified();
}

CGRDOpenDialog *CGRDSettingsDialog::GetParentDialog() CONST
{
	return((GetParent() != (CWnd *)GetParentDisplay()) ? (CGRDOpenDialog *)GetParent() : (CGRDOpenDialog *)NULL);
}

CGRDWnd *CGRDSettingsDialog::GetParentDisplay() CONST
{
	return((CGRDWnd *)CDisplayPropertySheetDialog::GetParentDisplay());
}

BOOL CGRDSettingsDialog::CheckLayout(CGRDLayout &cLayout) CONST
{
	CUIntArray  nColumns;

	if (!cLayout.GetType())
	{
		nColumns.Add(GRD_TITLEITEM_ID);
		nColumns.Add(GRD_TITLEITEM_DESCRIPTION);
		nColumns.Add(GRD_TITLEITEM_VALUE);
		nColumns.Add(GRD_TITLEITEM_UNIT);
		nColumns.Add(GRD_TITLEITEM_RANGE);
		nColumns.Add(GRD_TITLEITEM_LINE);
		cLayout.SetColumns(nColumns);
		cLayout.SetType(GRDLAYOUT_TYPE_NORMAL);
		cLayout.SetMode(GRDLAYOUT_MODE_NORMAL | GRDLAYOUT_MODE_OVERWRITE);
		cLayout.SetDuration(SECONDSPERMINUTE*GRDSETTINGSCHARTPAGE_DEFAULTDURATION);
		cLayout.SetInterval(0);
		cLayout.SetUpdateInterval(0);
		cLayout.SetGrids(GRDSETTINGSCHARTPAGE_DEFAULTGRIDS, GRDSETTINGSCHARTPAGE_DEFAULTGRIDS);
		cLayout.SetTicks(0, 0);
		cLayout.SetGridsWidth(GRDSETTINGSCHARTPAGE_DEFAULTGRIDSWIDTH);
		cLayout.SetTicksWidth(GRDSETTINGSCHARTPAGE_DEFAULTTICKSWIDTH);
		cLayout.SetGridsColor(VGA_COLOR_GRAY);
		cLayout.SetTicksColor(VGA_COLOR_GRAY);
		cLayout.SetBackgroundColor(VGA_COLOR_LTGRAY);
		cLayout.SetLabelColor(VGA_COLOR_BLACK);
	}
	return((cLayout.GetType()) ? TRUE : FALSE);
}

BEGIN_MESSAGE_MAP(CGRDSettingsDialog, CDisplayPropertySheetDialog)
	//{{AFX_MSG_MAP(CGRDSettingsDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDHELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDSettingsDialog message handlers

BOOL CGRDSettingsDialog::OnInitDialog()
{
	INT  nPage;
	INT  nPages;
	CHourglassCursor  cCursor;

	CDisplayPropertySheetDialog::OnInitDialog();
	SetTitle(STRING(IDS_GRDSETTINGSDIALOG_TITLE));
	for (nPage = 0, nPages = GetPageCount(), m_wndTabCtrl.SubclassWindow(GetTabControl()->GetSafeHwnd()); nPage < nPages; nPage++)
	{
		SetActivePage((nPage + 1) % nPages);
		continue;
	}
	m_wndTabCtrl.SetFocus();
	return FALSE;
}

BOOL CGRDSettingsDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	CRect  rTab;
	CGRDPrintJobs  pPrintJobs;
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

BOOL CGRDSettingsDialog::OnDataExchange(HWND hPage, CONST CGRDLayout &cLayout)
{
	return(((hPage == m_pageChart.GetSafeHwnd() && m_pageParameters.OnDataExchange(cLayout)) || (hPage == m_pageParameters.GetSafeHwnd() && m_pageChart.OnDataExchange(cLayout))) ? TRUE : FALSE);
}
BOOL CGRDSettingsDialog::OnDataExchange(HWND hPage, CONST CGRDPrintJobs &pJobs)
{
	return(((hPage == m_pagePrinting.GetSafeHwnd() && m_pagePrintJobs.OnDataExchange(pJobs)) || (hPage == m_pagePrintJobs.GetSafeHwnd() && m_pagePrinting.OnDataExchange(pJobs))) ? TRUE : FALSE);
}

void CGRDSettingsDialog::OnOK()
{
	CHourglassCursor  cCursor;

	ReportEvent(((!GetParentDialog() && !GetParentDisplay()->OnCloseSettingsDialog(IDOK)) || (GetParentDialog() && !GetParentDialog()->OnCloseSettingsDialog(IDOK))) ? SYSTEM_WARNING_GRD_SETUP_FAILURE : SYSTEM_NOERROR);
	CDisplayPropertySheetDialog::OnOK();
}

void CGRDSettingsDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	if (!GetParentDialog()) GetParentDisplay()->OnCloseSettingsDialog(IDCANCEL);
	else  GetParentDialog()->OnCloseSettingsDialog(IDCANCEL);
	CDisplayPropertySheetDialog::OnCancel();
}

BOOL CGRDSettingsDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_GRDSETTINGSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CGRDSettingsDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_GRDSETTINGSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CGRDLinkagesDialog dialog

IMPLEMENT_DYNCREATE(CGRDLinkagesDialog, CDisplayDialog)

CGRDLinkagesDialog::CGRDLinkagesDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CGRDLinkagesDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CGRDLinkagesDialog::Create(CWnd *pParentWnd)
{
	return CDisplayDialog::Create(pParentWnd, CGRDLinkagesDialog::IDD);
}

BOOL CGRDLinkagesDialog::Initialize()
{
	GetDisplayArea()->EnumDisplays(m_pDisplays[0]);
	GetParent()->GetLinks(m_pDisplays[1]);
	return TRUE;
}

CGRDWnd *CGRDLinkagesDialog::GetParent() CONST
{
	return((CGRDWnd *)CDisplayDialog::GetParent());
}

BOOL CGRDLinkagesDialog::EnumDisplays()
{
	INT  nDisplay[2];
	INT  nDisplays[2];
	CString  szDisplay;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay[0] = 0, nDisplays[0] = (INT)m_pDisplays[0].GetSize(), SendDlgItemMessage(IDC_GRD_LINKAGES_DISPLAYS, CB_RESETCONTENT), SendDlgItemMessage(IDC_GRD_LINKAGES_LIST, LB_RESETCONTENT); nDisplay[0] < nDisplays[0]; nDisplay[0]++)
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
			for (pDisplayWnd->GetWindowText(szDisplay); SendDlgItemMessage(IDC_GRD_LINKAGES_DISPLAYS, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szDisplay) < 0 && !szDisplay.IsEmpty(); )
			{
				SendDlgItemMessage(IDC_GRD_LINKAGES_DISPLAYS, CB_INSERTSTRING, nDisplay[0], (LPARAM)(LPCTSTR)szDisplay);
				break;
			}
		}
	}
	for (nDisplay[1] = 0, nDisplays[1] = (INT)m_pDisplays[1].GetSize(), m_pDisplays[2].Copy(m_pDisplays[1]); nDisplay[1] < nDisplays[1]; nDisplay[1]++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)m_pDisplays[1].GetAt(nDisplay[1])) != (CDisplayWnd *)NULL)
		{
			for (pDisplayWnd->GetWindowText(szDisplay); SendDlgItemMessage(IDC_GRD_LINKAGES_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szDisplay) < 0 && !szDisplay.IsEmpty(); )
			{
				SendDlgItemMessage(IDC_GRD_LINKAGES_LIST, LB_INSERTSTRING, nDisplay[1], (LPARAM)(LPCTSTR)szDisplay);
				break;
			}
		}
	}
	SendDlgItemMessage(IDC_GRD_LINKAGES_LIST, LB_SETCURSEL);
	SendDlgItemMessage(IDC_GRD_LINKAGES_DISPLAYS, CB_SETCURSEL);
	GetDlgItem(IDC_GRD_LINKAGES_DISPLAYS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_GRD_LINKAGES_DISPLAYS, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_LINKAGES_DISPLAYS)->EnableWindow((SendDlgItemMessage(IDC_GRD_LINKAGES_DISPLAYS, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_LINKAGES_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_GRD_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_LINKAGES_LIST)->EnableWindow((SendDlgItemMessage(IDC_GRD_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_LINKAGES_ADD)->EnableWindow((SendDlgItemMessage(IDC_GRD_LINKAGES_DISPLAYS, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_LINKAGES_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_GRD_LINKAGES_LIST, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_LINKAGES_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_GRD_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	return TRUE;
}

INT CGRDLinkagesDialog::FindDisplay(LPCTSTR pszName, BOOL bLinked) CONST
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

BOOL CGRDLinkagesDialog::IsModified() CONST
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

BOOL CGRDLinkagesDialog::Check(BOOL bModified) CONST
{
	return(!bModified || IsModified());
}

void CGRDLinkagesDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGRDLinkagesDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CGRDLinkagesDialog::PostNcDestroy()
{
	m_pDisplays[0].RemoveAll();
	m_pDisplays[1].RemoveAll();
	m_pDisplays[2].RemoveAll();
	CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CGRDLinkagesDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CGRDLinkagesDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_GRD_LINKAGES_ADD, OnAddDisplay)
	ON_BN_CLICKED(IDC_GRD_LINKAGES_REMOVE, OnRemoveLinkedDisplay)
	ON_BN_CLICKED(IDC_GRD_LINKAGES_REMOVEALL, OnRemoveAllLinkedDisplays)
	ON_BN_CLICKED(IDC_GRD_LINKAGES_HELP, OnHelp)
	ON_LBN_SELCHANGE(IDC_GRD_LINKAGES_LIST, OnSelchangeLinkedDisplay)
	ON_CBN_EDITCHANGE(IDC_GRD_LINKAGES_DISPLAYS, OnEditchangeDisplay)
	ON_CBN_SELCHANGE(IDC_GRD_LINKAGES_DISPLAYS, OnSelchangeDisplay)
	ON_CBN_DBLCLK(IDC_GRD_LINKAGES_DISPLAYS, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDLinkagesDialog message handlers

BOOL CGRDLinkagesDialog::OnInitDialog()
{
	CString  szDisplay;
	CHourglassCursor  cCursor;

	for (CDisplayDialog::OnInitDialog(), GetParent()->GetWindowText(szDisplay); EnumDisplays(); )
	{
		GetDlgItem(IDC_GRD_LINKAGES_NAME)->SetWindowText(szDisplay);
		GetDlgItem(IDC_GRD_LINKAGES_DETAILS)->EnableWindow();
		GetDlgItem(IDC_GRD_LINKAGES_NAME_STATIC)->EnableWindow();
		GetDlgItem(IDC_GRD_LINKAGES_NAME)->EnableWindow();
		GetDlgItem(IDC_GRD_LINKAGES_DISPLAYS)->SetFocus();
		return FALSE;
	}
	return TRUE;
}

void CGRDLinkagesDialog::OnAddDisplay()
{
	INT  nIndex[2];
	CString  szDisplay;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_GRD_LINKAGES_DISPLAYS)->GetWindowText(szDisplay); (nIndex[0] = FindDisplay(szDisplay)) >= 0; )
	{
		if ((nIndex[1] = (INT)SendDlgItemMessage(IDC_GRD_LINKAGES_LIST, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szDisplay)) >= 0)
		{
			for (SendDlgItemMessage(IDC_GRD_LINKAGES_LIST, LB_SETCURSEL, nIndex[1]); SendDlgItemMessage(IDC_GRD_LINKAGES_DISPLAYS, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_GRD_LINKAGES_DISPLAYS, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szDisplay)) >= 0; )
			{
				m_pDisplays[1].Add(m_pDisplays[0].GetAt(nIndex[0]));
				m_pDisplays[0].RemoveAt(nIndex[0]);
				break;
			}
			SendDlgItemMessage(IDC_GRD_LINKAGES_DISPLAYS, CB_SETCURSEL);
			GetDlgItem(IDC_GRD_LINKAGES_ADD)->EnableWindow((SendDlgItemMessage(IDC_GRD_LINKAGES_DISPLAYS, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
			GetDlgItem(IDC_GRD_LINKAGES_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_GRD_LINKAGES_LIST, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
			GetDlgItem(IDC_GRD_LINKAGES_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_GRD_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_GRD_LINKAGES_DISPLAYS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_GRD_LINKAGES_DISPLAYS, CB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_GRD_LINKAGES_DISPLAYS)->EnableWindow((SendDlgItemMessage(IDC_GRD_LINKAGES_DISPLAYS, CB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_GRD_LINKAGES_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_GRD_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_GRD_LINKAGES_LIST)->EnableWindow((SendDlgItemMessage(IDC_GRD_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_GRD_LINKAGES_LIST)->SetFocus();
		}
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDLinkagesDialog::OnRemoveLinkedDisplay()
{
	INT  nIndex[2];
	CString  szDisplay;
	CHourglassCursor  cCursor;

	for (szDisplay = Listbox_GetText(GetDlgItem(IDC_GRD_LINKAGES_LIST), (INT)SendDlgItemMessage(IDC_GRD_LINKAGES_LIST, LB_GETCURSEL)); (nIndex[0] = FindDisplay(szDisplay, TRUE)) >= 0; )
	{
		if ((nIndex[1] = (INT)SendDlgItemMessage(IDC_GRD_LINKAGES_DISPLAYS, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szDisplay)) >= 0)
		{
			for (SendDlgItemMessage(IDC_GRD_LINKAGES_DISPLAYS, CB_SETCURSEL, nIndex[1]); SendDlgItemMessage(IDC_GRD_LINKAGES_LIST, LB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_GRD_LINKAGES_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szDisplay)) >= 0; )
			{
				m_pDisplays[0].Add(m_pDisplays[1].GetAt(nIndex[0]));
				m_pDisplays[1].RemoveAt(nIndex[0]);
				break;
			}
			SendDlgItemMessage(IDC_GRD_LINKAGES_LIST, LB_SETCURSEL);
			GetDlgItem(IDC_GRD_LINKAGES_ADD)->EnableWindow((SendDlgItemMessage(IDC_GRD_LINKAGES_DISPLAYS, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
			GetDlgItem(IDC_GRD_LINKAGES_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_GRD_LINKAGES_LIST, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
			GetDlgItem(IDC_GRD_LINKAGES_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_GRD_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_GRD_LINKAGES_DISPLAYS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_GRD_LINKAGES_DISPLAYS, CB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_GRD_LINKAGES_DISPLAYS)->EnableWindow((SendDlgItemMessage(IDC_GRD_LINKAGES_DISPLAYS, CB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_GRD_LINKAGES_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_GRD_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_GRD_LINKAGES_LIST)->EnableWindow((SendDlgItemMessage(IDC_GRD_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_GRD_LINKAGES_DISPLAYS)->SetFocus();
		}
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDLinkagesDialog::OnRemoveAllLinkedDisplays()
{
	INT  nDisplay;
	INT  nDisplays;
	CHourglassCursor  cCursor;

	for (nDisplay = 0, nDisplays = (INT)SendDlgItemMessage(IDC_GRD_LINKAGES_LIST, LB_GETCOUNT), m_pDisplays[0].Append(m_pDisplays[1]), m_pDisplays[1].RemoveAll(); nDisplay < nDisplays; nDisplay++)
	{
		if (SendDlgItemMessage(IDC_GRD_LINKAGES_DISPLAYS, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)Listbox_GetText(GetDlgItem(IDC_GRD_LINKAGES_LIST), nDisplay)) >= 0)
		{
			SendDlgItemMessage(IDC_GRD_LINKAGES_LIST, LB_DELETESTRING, nDisplay);
			nDisplays--;
			nDisplay--;
		}
	}
	SendDlgItemMessage(IDC_GRD_LINKAGES_LIST, LB_SETCURSEL);
	SendDlgItemMessage(IDC_GRD_LINKAGES_DISPLAYS, CB_SETCURSEL);
	GetDlgItem(IDC_GRD_LINKAGES_ADD)->EnableWindow((SendDlgItemMessage(IDC_GRD_LINKAGES_DISPLAYS, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_LINKAGES_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_GRD_LINKAGES_LIST, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_LINKAGES_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_GRD_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_LINKAGES_DISPLAYS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_GRD_LINKAGES_DISPLAYS, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_LINKAGES_DISPLAYS)->EnableWindow((SendDlgItemMessage(IDC_GRD_LINKAGES_DISPLAYS, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_LINKAGES_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_GRD_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_LINKAGES_LIST)->EnableWindow((SendDlgItemMessage(IDC_GRD_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_LINKAGES_DISPLAYS)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDLinkagesDialog::OnEditchangeDisplay()
{
	CString  szDisplay;

	GetDlgItem(IDC_GRD_LINKAGES_DISPLAYS)->GetWindowText(szDisplay);
	GetDlgItem(IDC_GRD_LINKAGES_ADD)->EnableWindow((SendDlgItemMessage(IDC_GRD_LINKAGES_DISPLAYS, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szDisplay) >= 0 && SendDlgItemMessage(IDC_GRD_LINKAGES_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szDisplay) < 0) ? TRUE : FALSE);
}

void CGRDLinkagesDialog::OnSelchangeDisplay()
{
	GetDlgItem(IDC_GRD_LINKAGES_ADD)->EnableWindow();
}

void CGRDLinkagesDialog::OnSelchangeLinkedDisplay()
{
	GetDlgItem(IDC_GRD_LINKAGES_REMOVE)->EnableWindow();
}

void CGRDLinkagesDialog::OnOK()
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

BOOL CGRDLinkagesDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_GRDLINKAGESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CGRDLinkagesDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_GRDLINKAGESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CGRDParametersCalibrationPage property page

IMPLEMENT_DYNCREATE(CGRDParametersCalibrationPage, CLocalePropertyPage)

CGRDParametersCalibrationPage::CGRDParametersCalibrationPage() : CLocalePropertyPage(CGRDParametersCalibrationPage::IDD)
{
	//{{AFX_DATA_INIT(CGRDParametersCalibrationPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

VOID CGRDParametersCalibrationPage::ShowParameterInfo()
{
	SendDlgItemMessage(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_NAME, CB_RESETCONTENT);
	GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_NAME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_NAME)->EnableWindow(FALSE);
	ShowCalibrationInfo();
}
VOID CGRDParametersCalibrationPage::ShowParameterInfo(CONST CTMParameter *pTMParameter)
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

	for (SendDlgItemMessage(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_NAME, CB_RESETCONTENT), nIndex = -1; (pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pTMParameter->GetTag()))); )
	{
		for (nTable = 0, nTables = pDatabaseTMParameter->GetCalTableRefs(m_nCalTableRefs, m_nCalValidityRefs), szTable = (pTMParameter->GetRawValue(pTMParameter->GetValueCount() - 1, nValue, nStatus, szTable)) ? szTable : EMPTYSTRING; nTable < nTables; nTable++)
		{
			if ((m_nCalTableType = (pDatabaseTMParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS))) == TMPARAMETER_CALIBRATION_NUMERICAL)
			{
				if ((pDatabaseTMNumCalTable = GetDatabase()->GetTMNumCalTables()->GetAt(m_nCalTableRefs.GetAt(nTable))) != (CDatabaseTMNumCalTable *)NULL)
				{
					for (szName.Format(STRING(IDS_GRDPARAMETERS_CALIBRATIONPAGE_TABLE_FORMAT), (LPCTSTR)pDatabaseTMNumCalTable->GetDescription(), (LPCTSTR)pDatabaseTMNumCalTable->GetName()); pDatabaseTMNumCalTable->GetDescription().IsEmpty(); )
					{
						szName = pDatabaseTMNumCalTable->GetName();
						break;
					}
					for (SendDlgItemMessage(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_NAME, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szName); pDatabaseTMNumCalTable->GetName() == szTable; )
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
					for (szName.Format(STRING(IDS_GRDPARAMETERS_CALIBRATIONPAGE_TABLE_FORMAT), (LPCTSTR)pDatabaseTMTxtCalTable->GetDescription(), (LPCTSTR)pDatabaseTMTxtCalTable->GetName()); pDatabaseTMTxtCalTable->GetDescription().IsEmpty(); )
					{
						szName = pDatabaseTMTxtCalTable->GetName();
						break;
					}
					for (SendDlgItemMessage(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_NAME, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szName); pDatabaseTMTxtCalTable->GetName() == szTable; )
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
	m_nCalTableID = (INT)SendDlgItemMessage(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_NAME, CB_SETCURSEL, max(nIndex, 0));
	GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_NAME_STATIC)->EnableWindow((SendDlgItemMessage(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_NAME)->EnableWindow((SendDlgItemMessage(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_NAME, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	ShowCalibrationInfo();
}

VOID CGRDParametersCalibrationPage::ShowCalibrationInfo()
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

	SendDlgItemMessage(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_POINTS, LVM_DELETEALLITEMS);
	if ((nIndex = (INT)SendDlgItemMessage(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_NAME, CB_GETCURSEL)) >= 0 && nIndex < (INT)m_nCalTableRefs.GetSize())
	{
		if ((pDatabaseTMNumCalTable = (m_nCalTableType == TMPARAMETER_CALIBRATION_NUMERICAL) ? GetDatabase()->GetTMNumCalTables()->GetAt(m_nCalTableRefs.GetAt(nIndex)) : (CDatabaseTMNumCalTable *)NULL))
		{
			for (nItem = 0, nItems = (INT)pDatabaseTMNumCalTable->GetSize(); nItem < nItems; nItem++)
			{
				if ((pDatabaseTMNumCalPoint = pDatabaseTMNumCalTable->GetAt(nItem)))
				{
					for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(); nColumn < nColumns; nColumn = nColumn + 1)
					{
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_GRDPARAMETERS_CALIBRATIONPAGE_TITLEITEM_NUMBER); )
						{
							szItem = cStringTools.ConvertIntToString(nItem + 1);
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_GRDPARAMETERS_CALIBRATIONPAGE_TITLEITEM_X); )
						{
							szItem = cStringTools.ConvertFloatToTruncatedString(pDatabaseTMNumCalPoint->GetX());
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_GRDPARAMETERS_CALIBRATIONPAGE_TITLEITEM_Y); )
						{
							szItem = cStringTools.ConvertFloatToString(pDatabaseTMNumCalPoint->GetY());
							break;
						}
						if (!nColumn)
						{
							Listview_InsertText(GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_POINTS), nItem, szItem);
							continue;
						}
						Listview_SetText(GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_POINTS), nItem, nColumn, szItem);
					}
				}
			}
			GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_ID)->SetWindowText(pDatabaseTMNumCalTable->GetName());
			GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_TYPE)->SetWindowText(STRING(IDS_GRDPARAMETERS_CALIBRATIONPAGE_TYPE_NUMERICAL));
			GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_STATUS)->SetWindowText((nIndex == m_nCalTableID) ? STRING(IDS_GRDPARAMETERS_CALIBRATIONPAGE_STATUS_ACTIVE) : STRING(IDS_GRDPARAMETERS_CALIBRATIONPAGE_STATUS_INACTIVE));
			GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_ID_STATIC)->EnableWindow((GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_ID)->EnableWindow((GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_POINTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_POINTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_POINTS)->EnableWindow((SendDlgItemMessage(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_POINTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_TYPE_STATIC)->EnableWindow();
			GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_TYPE)->EnableWindow();
			GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_STATUS_STATIC)->EnableWindow();
			GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_STATUS)->EnableWindow();
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
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_GRDPARAMETERS_CALIBRATIONPAGE_TITLEITEM_NUMBER); )
						{
							szItem = cStringTools.ConvertIntToString(nItem + 1);
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_GRDPARAMETERS_CALIBRATIONPAGE_TITLEITEM_X); )
						{
							if (pDatabaseTMTxtCalPoint->GetRange(fCalPtX, fCalPtY, szCalText) || pDatabaseTMTxtCalPoint->GetPoint(fCalPtX, szCalText))
							{
								for (szCalPtX = szItem = cStringTools.ConvertFloatToTruncatedString(fCalPtX, -1), szCalPtY = cStringTools.ConvertFloatToTruncatedString(fCalPtY, -1); fCalPtX != fCalPtY; )
								{
									szItem.Format(STRING(IDS_GRDPARAMETERS_CALIBRATIONPAGE_POINT_RANGE), (LPCTSTR)szCalPtX, (LPCTSTR)szCalPtY);
									break;
								}
								break;
							}
							szItem.Empty();
							break;
						}
						for (; m_szColumns.GetAt(nColumn) == STRING(IDS_GRDPARAMETERS_CALIBRATIONPAGE_TITLEITEM_Y); )
						{
							szItem = (pDatabaseTMTxtCalPoint->GetPoint(fCalPtX, szCalText) || pDatabaseTMTxtCalPoint->GetRange(fCalPtX, fCalPtY, szCalText)) ? (LPCTSTR)szCalText : EMPTYSTRING;
							break;
						}
						if (!nColumn)
						{
							Listview_InsertText(GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_POINTS), nItem, szItem);
							continue;
						}
						Listview_SetText(GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_POINTS), nItem, nColumn, szItem);
					}
				}
			}
			GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_ID)->SetWindowText(pDatabaseTMTxtCalTable->GetName());
			GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_TYPE)->SetWindowText(STRING(IDS_GRDPARAMETERS_CALIBRATIONPAGE_TYPE_STATUS));
			GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_STATUS)->SetWindowText((nIndex == m_nCalTableID) ? STRING(IDS_GRDPARAMETERS_CALIBRATIONPAGE_STATUS_ACTIVE) : STRING(IDS_GRDPARAMETERS_CALIBRATIONPAGE_STATUS_INACTIVE));
			GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_ID_STATIC)->EnableWindow((GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_ID)->EnableWindow((GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_ID)->GetWindowTextLength() > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_POINTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_POINTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_POINTS)->EnableWindow((SendDlgItemMessage(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_POINTS, LVM_GETITEMCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_TYPE_STATIC)->EnableWindow();
			GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_TYPE)->EnableWindow();
			GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_STATUS_STATIC)->EnableWindow();
			GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_STATUS)->EnableWindow();
			return;
		}
	}
	SendDlgItemMessage(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_POINTS, LVM_DELETEALLITEMS);
	GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_ID)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_TYPE)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_STATUS)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_ID_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_ID)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_TYPE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_TYPE)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_STATUS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_STATUS)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_POINTS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_POINTS)->EnableWindow(FALSE);
}

CGRDParametersFolder *CGRDParametersCalibrationPage::GetParent() CONST
{
	return((CGRDParametersFolder *)CLocalePropertyPage::GetParent());
}

void CGRDParametersCalibrationPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGRDParametersCalibrationPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CGRDParametersCalibrationPage::PostNcDestroy()
{
	m_szColumns.RemoveAll();
	m_nCalTableRefs.RemoveAll();
	m_nCalValidityRefs.RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CGRDParametersCalibrationPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CGRDParametersCalibrationPage)
	ON_CBN_SELCHANGE(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_NAME, OnSelchangeName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDParametersCalibrationPage message handlers

BOOL CGRDParametersCalibrationPage::OnInitDialog()
{
	INT  nWidth;
	INT  nColumn;
	INT  nColumns;
	CRect  rColumns;
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	m_szColumns.Add(STRING(IDS_GRDPARAMETERS_CALIBRATIONPAGE_TITLEITEM_NUMBER));
	m_szColumns.Add(STRING(IDS_GRDPARAMETERS_CALIBRATIONPAGE_TITLEITEM_X));
	m_szColumns.Add(STRING(IDS_GRDPARAMETERS_CALIBRATIONPAGE_TITLEITEM_Y));
	GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_POINTS)->GetClientRect(rColumns);
	SendDlgItemMessage(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_POINTS, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	for (nColumn = 0, nColumns = (INT)m_szColumns.GetSize(), nWidth = rColumns.Width() / 5; nColumn < nColumns; nWidth = (++nColumn < nColumns) ? ((2 * rColumns.Width()) / 5) : nWidth)
	{
		Listview_InsertColumn(GetDlgItem(IDC_GRD_PARAMETERS_CALIBRATIONPAGE_POINTS), nColumn, m_szColumns.GetAt(nColumn), nWidth);
		continue;
	}
	return TRUE;
}

void CGRDParametersCalibrationPage::OnSelchangeName()
{
	ShowCalibrationInfo();
}


/////////////////////////////////////////////////////////////////////////////
// CGRDParametersScalingPage property page

IMPLEMENT_DYNCREATE(CGRDParametersScalingPage, CLocalePropertyPage)

CGRDParametersScalingPage::CGRDParametersScalingPage() : CLocalePropertyPage(CGRDParametersScalingPage::IDD)
{
	//{{AFX_DATA_INIT(CGRDParametersScalingPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CGRDParametersScalingPage::SetParameters(CONST CGRDLayout &cLayout)
{
	for (m_cLayout[0].Copy(&cLayout), m_cLayout[1].Copy(&cLayout), m_nIndex = -1; GetDatabase()->LoadGRD(m_cLayout[0].GetName(), m_cLayout[2]); ) return TRUE;
	return FALSE;
}

BOOL CGRDParametersScalingPage::GetParameters(CGRDLayout &cLayout) CONST
{
	return((cLayout.Copy(&m_cLayout[0])) ? Check(FALSE) : FALSE);
}

VOID CGRDParametersScalingPage::ShowParameterInfo(INT nIndex)
{
	INT  nMargin[2];
	double  fMinimum;
	double  fMaximum;
	CString  szMinimum;
	CString  szMaximum;
	CGRDLayoutParameter  *pParameter;

	if ((pParameter = m_cLayout[0].GetAt((m_nIndex = nIndex))))
	{
		for (pParameter->GetMargin(nMargin[0], nMargin[1]); pParameter->GetRange(fMinimum, fMaximum); )
		{
			ConvertRangeValues(pParameter, fMinimum, fMaximum, szMinimum, szMaximum);
			break;
		}
		CheckDlgButton(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_LOWER, (nMargin[0] >= 0) ? TRUE : FALSE);
		CheckDlgButton(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_UPPER, (nMargin[1] >= 0) ? TRUE : FALSE);
		CheckDlgButton(IDC_GRD_PARAMETERS_SCALINGPAGE_AUTOMATIC, (pParameter->GetAutoScaleDelay() > 0) ? TRUE : FALSE);
		Spinbox_SetPos(GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_LOWER_PERCENT), nMargin[0]);
		Spinbox_SetPos(GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_UPPER_PERCENT), nMargin[1]);
		Spinbox_SetPos(GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_AUTOMATIC_MINUTES), pParameter->GetAutoScaleDelay().GetTotalSeconds() / SECONDSPERMINUTE);
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_LOW)->SetWindowText(szMinimum);
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_HIGH)->SetWindowText(szMaximum);
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_MARGIN_LOW)->SetWindowText(szMinimum);
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_MARGIN_HIGH)->SetWindowText(szMaximum);
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_VALUES_STATIC)->EnableWindow();
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_VALUES_MINIMUM_STATIC)->EnableWindow();
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_VALUES_MINIMUM)->EnableWindow();
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_VALUES_MAXIMUM_STATIC)->EnableWindow();
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_VALUES_MAXIMUM)->EnableWindow();
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_VALUES_REFRESH)->EnableWindow();
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_STATIC)->EnableWindow();
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_LOW_STATIC)->EnableWindow();
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_LOW)->EnableWindow();
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_MARGIN_LOW_STATIC)->EnableWindow();
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_MARGIN_LOW)->EnableWindow();
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_HIGH_STATIC)->EnableWindow();
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_HIGH)->EnableWindow();
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_MARGIN_HIGH_STATIC)->EnableWindow();
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_MARGIN_HIGH)->EnableWindow();
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGINS_STATIC)->EnableWindow();
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_UPPER)->EnableWindow();
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_UPPER_PERCENT)->EnableWindow(IsDlgButtonChecked(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_UPPER));
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_UPPER_PERCENT_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_UPPER));
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_LOWER)->EnableWindow();
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_LOWER_PERCENT)->EnableWindow(IsDlgButtonChecked(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_LOWER));
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_LOWER_PERCENT_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_LOWER));
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_AUTOMATIC)->EnableWindow();
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_AUTOMATIC_MINUTES_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_GRD_PARAMETERS_SCALINGPAGE_AUTOMATIC));
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_AUTOMATIC_MINUTES)->EnableWindow(IsDlgButtonChecked(IDC_GRD_PARAMETERS_SCALINGPAGE_AUTOMATIC));
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_DEFAULT)->EnableWindow(IsModified(nIndex, TRUE));
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RESET)->EnableWindow(IsModified(nIndex, FALSE));
		return;
	}
	CheckDlgButton(IDC_GRD_PARAMETERS_SCALINGPAGE_AUTOMATIC, FALSE);
	CheckDlgButton(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_UPPER, FALSE);
	CheckDlgButton(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_LOWER, FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_VALUES_MINIMUM)->SetWindowText(m_szRange[0]);
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_VALUES_MAXIMUM)->SetWindowText(m_szRange[1]);
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_LOW)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_MARGIN_LOW)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_HIGH)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_MARGIN_HIGH)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_VALUES_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_VALUES_MINIMUM_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_VALUES_MINIMUM)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_VALUES_MAXIMUM_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_VALUES_MAXIMUM)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_VALUES_REFRESH)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_LOW_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_LOW)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_MARGIN_LOW_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_MARGIN_LOW)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_HIGH_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_HIGH)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_MARGIN_HIGH_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_MARGIN_HIGH)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGINS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_UPPER)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_UPPER_PERCENT)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_UPPER_PERCENT_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_LOWER)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_LOWER_PERCENT)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_LOWER_PERCENT_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_AUTOMATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_AUTOMATIC_MINUTES_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_AUTOMATIC_MINUTES)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_DEFAULT)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RESET)->EnableWindow(FALSE);
}
VOID CGRDParametersScalingPage::ShowParameterInfo(CONST CGRDParameterSamples &pParameterSamples, INT nIndex)
{
	double  fMinimum;
	double  fMaximum;
	CString  szMinimum;
	CString  szMaximum;
	CGRDLayoutParameter  *pParameter;

	if ((pParameter = m_cLayout[0].GetAt((m_nIndex = nIndex))))
	{
		for (szMinimum = m_szRange[0], szMaximum = m_szRange[1]; pParameterSamples.GetRange(fMinimum, fMaximum); )
		{
			ConvertRangeValues(pParameter, fMinimum, fMaximum, szMinimum, szMaximum);
			break;
		}
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_VALUES_MINIMUM)->SetWindowText(szMinimum);
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_VALUES_MAXIMUM)->SetWindowText(szMaximum);
		ShowParameterInfo(nIndex);
		return;
	}
	ShowParameterInfo();
}

VOID CGRDParametersScalingPage::RefreshParameterInfo()
{
	INT  nMargin[2];
	double  fPrecision;
	double  fMinimum[2];
	double  fMaximum[2];
	CString  szMinimum[2];
	CString  szMaximum[2];
	CGRDLayoutParameter  *pParameter;

	if ((pParameter = m_cLayout[0].GetAt(m_nIndex)))
	{
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_VALUES_MINIMUM)->GetWindowText(szMinimum[0]);
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_VALUES_MAXIMUM)->GetWindowText(szMaximum[0]);
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_MARGIN_LOW)->GetWindowText(szMinimum[1]);
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_MARGIN_HIGH)->GetWindowText(szMaximum[1]);
		for (nMargin[0] = (INT)Spinbox_GetPos(GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_LOWER_PERCENT)), nMargin[1] = (INT)Spinbox_GetPos(GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_UPPER_PERCENT)); ConvertRangeValues(szMinimum[0], szMaximum[0], fMinimum[0], fMaximum[0]) && fMinimum[0] != fMaximum[0]; )
		{
			fPrecision = (m_cLayout[0].GetType() == GRDLAYOUT_TYPE_DIAGRAM  &&  m_nIndex % 2 == 0) ? ((!m_cLayout[0].GetPlotSize().cx) ? GRDLAYOUT_GRAPH_WIDTH : m_cLayout[0].GetPlotSize().cx) : ((!m_cLayout[0].GetPlotSize().cy) ? GRDLAYOUT_GRAPH_HEIGHT : m_cLayout[0].GetPlotSize().cy);
			fPrecision = pow(10.0, floor(log10(fPrecision)) - floor(log10(fMaximum[0] - fMinimum[0])));
			fMinimum[1] = fMinimum[0] - ((double)max(nMargin[0], 0)*(fMaximum[0] - fMinimum[0])) / 100.0;
			fMaximum[1] = fMaximum[0] + ((double)max(nMargin[1], 0)*(fMaximum[0] - fMinimum[0])) / 100.0;
			fMinimum[1] = floor(fMinimum[1] * fPrecision - 1.0) / fPrecision;
			fMaximum[1] = floor(fMaximum[1] * fPrecision + 1.0) / fPrecision;
			ConvertRangeValues(pParameter, fMinimum[1], fMaximum[1], szMinimum[1], szMaximum[1]);
			break;
		}
		for (GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_MARGIN_LOW)->SetWindowText(szMinimum[1]), GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_MARGIN_HIGH)->SetWindowText(szMaximum[1]); ConvertRangeValues(szMinimum[1], szMaximum[1], fMinimum[1], fMaximum[1]); )
		{
			pParameter->SetRange(fMinimum[1], fMaximum[1]);
			break;
		}
		pParameter->SetMargin((IsDlgButtonChecked(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_LOWER)) ? nMargin[0] : -1, (IsDlgButtonChecked(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_UPPER)) ? nMargin[1] : -1);
		pParameter->SetAutoScaleDelay((IsDlgButtonChecked(IDC_GRD_PARAMETERS_SCALINGPAGE_AUTOMATIC)) ? (SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_AUTOMATIC_MINUTES)) + 1) : 0);
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_DEFAULT)->EnableWindow(IsModified(m_nIndex, TRUE));
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RESET)->EnableWindow(IsModified(m_nIndex, FALSE));
	}
}
VOID CGRDParametersScalingPage::RefreshParameterInfo(CONST CGRDParameterSamples &pParameterSamples, INT nIndex)
{
	double  fMinimum;
	double  fMaximum;
	CString  szMinimum;
	CString  szMaximum;
	CGRDLayoutParameter  *pParameter;

	if ((pParameter = m_cLayout[0].GetAt((m_nIndex = nIndex))))
	{
		for (szMinimum = m_szRange[0], szMaximum = m_szRange[1]; pParameterSamples.GetRange(fMinimum, fMaximum); )
		{
			ConvertRangeValues(pParameter, fMinimum, fMaximum, szMinimum, szMaximum);
			break;
		}
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_VALUES_MINIMUM)->SetWindowText(szMinimum);
		GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_VALUES_MAXIMUM)->SetWindowText(szMaximum);
		RefreshParameterInfo();
	}
}

BOOL CGRDParametersScalingPage::ConvertRangeValues(LPCTSTR pszMinimum, LPCTSTR pszMaximum, double &fMinimum, double &fMaximum) CONST
{
	LPTSTR  pMinimum;
	LPTSTR  pMaximum;

	fMinimum = _tcstod(pszMinimum, &pMinimum);
	fMaximum = _tcstod(pszMaximum, &pMaximum);
	return((_tcsspn(pMinimum, SPACE) == lstrlen(pMinimum) && _tcsspn(pMaximum, SPACE) == lstrlen(pMaximum) && lstrlen(pszMinimum) > 0 && lstrlen(pszMaximum) > 0) ? TRUE : FALSE);
}
VOID CGRDParametersScalingPage::ConvertRangeValues(CONST CGRDLayoutParameter *pParameter, double fMinimum, double fMaximum, CString &szMinimum, CString &szMaximum) CONST
{
	CStringTools  cStringTools;

	if (((pParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS)) && !(pParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT))
	{
		szMinimum = (floor(fMinimum) == fMinimum) ? cStringTools.ConvertLongIntToString((LONGLONG)fMinimum) : cStringTools.ConvertFloatToString(fMinimum);
		szMaximum = (floor(fMaximum) == fMaximum) ? cStringTools.ConvertLongIntToString((LONGLONG)fMaximum) : cStringTools.ConvertFloatToString(fMaximum);
		return;
	}
	szMinimum = cStringTools.ConvertFloatToString(fMinimum);
	szMaximum = cStringTools.ConvertFloatToString(fMaximum);
}

BOOL CGRDParametersScalingPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? IsModified(-1, FALSE) : CLocalePropertyPage::IsModified()) : FALSE);
}
BOOL CGRDParametersScalingPage::IsModified(INT nIndex, BOOL bDefault) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bDefault && ((nIndex < 0 && !m_cLayout[0].Compare(&m_cLayout[1])) || (nIndex >= 0 && nIndex < m_cLayout[0].GetSize() && nIndex < m_cLayout[1].GetSize() && !m_cLayout[0].GetAt(nIndex)->Compare(m_cLayout[1].GetAt(nIndex))))) || (bDefault && ((nIndex < 0 && !m_cLayout[0].Compare(&m_cLayout[2])) || (nIndex >= 0 && nIndex < m_cLayout[0].GetSize() && nIndex < m_cLayout[2].GetSize() && m_cLayout[0].GetAt(nIndex)->GetName() == m_cLayout[2].GetAt(nIndex)->GetName() && !m_cLayout[0].GetAt(nIndex)->Compare(m_cLayout[2].GetAt(nIndex)))))) : FALSE);
}

CGRDParametersFolder *CGRDParametersScalingPage::GetParent() CONST
{
	return((CGRDParametersFolder *)CLocalePropertyPage::GetParent());
}

void CGRDParametersScalingPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGRDParametersScalingPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CGRDParametersScalingPage::PostNcDestroy()
{
	m_szRange[0].Empty();
	m_szRange[1].Empty();
	m_cLayout[0].RemoveAll();
	m_cLayout[1].RemoveAll();
	m_cLayout[2].RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CGRDParametersScalingPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CGRDParametersScalingPage)
	ON_BN_CLICKED(IDC_GRD_PARAMETERS_SCALINGPAGE_VALUES_REFRESH, OnRefresh)
	ON_BN_CLICKED(IDC_GRD_PARAMETERS_SCALINGPAGE_RESET, OnReset)
	ON_BN_CLICKED(IDC_GRD_PARAMETERS_SCALINGPAGE_DEFAULT, OnDefault)
	ON_BN_CLICKED(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_UPPER, OnUpperMargin)
	ON_BN_CLICKED(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_LOWER, OnLowerMargin)
	ON_BN_CLICKED(IDC_GRD_PARAMETERS_SCALINGPAGE_AUTOMATIC, OnAutoscale)
	ON_EN_CHANGE(IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_MARGIN_HIGH, OnEditchangeUpperMargin)
	ON_EN_CHANGE(IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_MARGIN_LOW, OnEditchangeLowerMargin)
	ON_CONTROL(SBXN_CHANGE, IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_UPPER_PERCENT, OnSpinchangeUpperMargin)
	ON_CONTROL(SBXN_CHANGE, IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_LOWER_PERCENT, OnSpinchangeLowerMargin)
	ON_CONTROL(SBXN_CHANGE, IDC_GRD_PARAMETERS_SCALINGPAGE_AUTOMATIC_MINUTES, OnSpinchangeAutoscaleDelay)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDParametersScalingPage message handlers

BOOL CGRDParametersScalingPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	Spinbox_SetRange(GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_UPPER_PERCENT), GRDSCALINGPAGE_MARGIN_MINIMUM, GRDSCALINGPAGE_MARGIN_MAXIMUM);
	Spinbox_SetRange(GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_LOWER_PERCENT), GRDSCALINGPAGE_MARGIN_MINIMUM, GRDSCALINGPAGE_MARGIN_MAXIMUM);
	Spinbox_SetRange(GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_AUTOMATIC_MINUTES), GRDSCALINGPAGE_AUTOSCALEDELAY_MINIMUM, GRDSCALINGPAGE_AUTOSCALEDELAY_MAXIMUM);
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_VALUES_MINIMUM)->GetWindowText(m_szRange[0]);
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_VALUES_MAXIMUM)->GetWindowText(m_szRange[1]);
	return TRUE;
}

void CGRDParametersScalingPage::OnRefresh()
{
	CHourglassCursor  cCursor;

	GetParent()->GetParentDialog()->RefreshParameterInfo();
}

void CGRDParametersScalingPage::OnReset()
{
	CGRDLayoutParameter  *pParameter;
	CHourglassCursor  cCursor;

	if ((pParameter = m_cLayout[0].GetAt(m_nIndex)))
	{
		pParameter->Copy(m_cLayout[1].GetAt(m_nIndex));
		ShowParameterInfo(m_nIndex);
	}
}

void CGRDParametersScalingPage::OnDefault()
{
	CGRDLayoutParameter  *pParameter;
	CHourglassCursor  cCursor;

	if ((pParameter = m_cLayout[0].GetAt(m_nIndex)))
	{
		pParameter->Copy(m_cLayout[2].GetAt(m_nIndex));
		ShowParameterInfo(m_nIndex);
	}
}

void CGRDParametersScalingPage::OnUpperMargin()
{
	if (Spinbox_SetPos(GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_UPPER_PERCENT), GRDSCALINGPAGE_MARGIN_DEFAULT)) RefreshParameterInfo();
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_UPPER_PERCENT)->EnableWindow(IsDlgButtonChecked(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_UPPER));
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_UPPER_PERCENT_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_UPPER));
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_UPPER_PERCENT)->SetFocus();
}

void CGRDParametersScalingPage::OnLowerMargin()
{
	if (Spinbox_SetPos(GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_LOWER_PERCENT), GRDSCALINGPAGE_MARGIN_DEFAULT)) RefreshParameterInfo();
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_LOWER_PERCENT)->EnableWindow(IsDlgButtonChecked(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_LOWER));
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_LOWER_PERCENT_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_LOWER));
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_LOWER_PERCENT)->SetFocus();
}

void CGRDParametersScalingPage::OnAutoscale()
{
	if (Spinbox_SetPos(GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_AUTOMATIC_MINUTES), GRDSCALINGPAGE_AUTOSCALEDELAY_DEFAULT)) RefreshParameterInfo();
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_AUTOMATIC_MINUTES_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_GRD_PARAMETERS_SCALINGPAGE_AUTOMATIC));
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_AUTOMATIC_MINUTES)->EnableWindow(IsDlgButtonChecked(IDC_GRD_PARAMETERS_SCALINGPAGE_AUTOMATIC));
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_AUTOMATIC_MINUTES)->SetFocus();
}

void CGRDParametersScalingPage::OnEditchangeUpperMargin()
{
	double  fMinimum;
	double  fMaximum;
	CString  szMinimum;
	CString  szMaximum;
	CGRDLayoutParameter  *pParameter;

	if ((pParameter = m_cLayout[0].GetAt(m_nIndex)))
	{
		for (GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_MARGIN_LOW)->GetWindowText(szMinimum), GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_MARGIN_HIGH)->GetWindowText(szMaximum); ConvertRangeValues(szMinimum, szMaximum, fMinimum, fMaximum); )
		{
			pParameter->SetRange(fMinimum, fMaximum);
			break;
		}
	}
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_DEFAULT)->EnableWindow(IsModified(m_nIndex, TRUE));
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RESET)->EnableWindow(IsModified(m_nIndex, FALSE));
}

void CGRDParametersScalingPage::OnEditchangeLowerMargin()
{
	double  fMinimum;
	double  fMaximum;
	CString  szMinimum;
	CString  szMaximum;
	CGRDLayoutParameter  *pParameter;

	if ((pParameter = m_cLayout[0].GetAt(m_nIndex)))
	{
		for (GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_MARGIN_LOW)->GetWindowText(szMinimum), GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RANGE_MARGIN_HIGH)->GetWindowText(szMaximum); ConvertRangeValues(szMinimum, szMaximum, fMinimum, fMaximum); )
		{
			pParameter->SetRange(fMinimum, fMaximum);
			break;
		}
	}
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_DEFAULT)->EnableWindow(IsModified(m_nIndex, TRUE));
	GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_RESET)->EnableWindow(IsModified(m_nIndex, FALSE));
}

void CGRDParametersScalingPage::OnSpinchangeUpperMargin()
{
	INT  nMargin[2];

	for (nMargin[0] = (INT)Spinbox_GetPos(GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_LOWER_PERCENT)), nMargin[1] = (INT)Spinbox_GetPos(GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_UPPER_PERCENT)); max(nMargin[0], 0) + max(nMargin[1], 0) > GRDSCALINGPAGE_MARGIN_MAXIMUM; )
	{
		Spinbox_SetPos(GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_UPPER_PERCENT), (nMargin[1] = GRDSCALINGPAGE_MARGIN_MAXIMUM - max(nMargin[0], 0)));
		break;
	}
	RefreshParameterInfo();
}

void CGRDParametersScalingPage::OnSpinchangeLowerMargin()
{
	INT  nMargin[2];

	for (nMargin[0] = (INT)Spinbox_GetPos(GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_LOWER_PERCENT)), nMargin[1] = (INT)Spinbox_GetPos(GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_UPPER_PERCENT)); max(nMargin[0], 0) + max(nMargin[1], 0) > GRDSCALINGPAGE_MARGIN_MAXIMUM; )
	{
		Spinbox_SetPos(GetDlgItem(IDC_GRD_PARAMETERS_SCALINGPAGE_MARGIN_LOWER_PERCENT), (nMargin[0] = GRDSCALINGPAGE_MARGIN_MAXIMUM - max(nMargin[1], 0)));
		break;
	}
	RefreshParameterInfo();
}

void CGRDParametersScalingPage::OnSpinchangeAutoscaleDelay()
{
	RefreshParameterInfo();
}


/////////////////////////////////////////////////////////////////////////////
// CGRDParametersFolderTabCtrl

IMPLEMENT_DYNCREATE(CGRDParametersFolderTabCtrl, CTabCtrl)

CGRDParametersFolder *CGRDParametersFolderTabCtrl::GetParent() CONST
{
	return((CGRDParametersFolder *)CTabCtrl::GetParent());
}

BEGIN_MESSAGE_MAP(CGRDParametersFolderTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CGRDParametersFolderTabCtrl)
	ON_WM_GETDLGCODE()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDParametersFolderTabCtrl message handlers

UINT CGRDParametersFolderTabCtrl::OnGetDlgCode()
{
	return CTabCtrl::OnGetDlgCode() | DLGC_WANTTAB;
}

void CGRDParametersFolderTabCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
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
// CGRDParametersFolder

IMPLEMENT_DYNCREATE(CGRDParametersFolder, CLocalePropertySheetDialog)

CGRDParametersFolder::CGRDParametersFolder() : CLocalePropertySheetDialog()
{
	AddPage(&m_pageCalibration);
	AddPage(&m_pageScaling);
}

BOOL CGRDParametersFolder::Create(CWnd *pParentWnd, CONST RECT &rect)
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

BOOL CGRDParametersFolder::SetParameters(CONST CGRDLayout &cLayout)
{
	return m_pageScaling.SetParameters(cLayout);
}

BOOL CGRDParametersFolder::GetParameters(CGRDLayout &cLayout) CONST
{
	return m_pageScaling.GetParameters(cLayout);
}

VOID CGRDParametersFolder::ShowParameterInfo()
{
	m_pageCalibration.ShowParameterInfo();
	m_pageScaling.ShowParameterInfo();
}
VOID CGRDParametersFolder::ShowParameterInfo(CONST CTMParameter *pTMParameter, CONST CGRDParameterSamples &pParameterSamples, INT nIndex)
{
	m_pageCalibration.ShowParameterInfo(pTMParameter);
	m_pageScaling.ShowParameterInfo(pParameterSamples, nIndex);
}

VOID CGRDParametersFolder::RefreshParameterInfo()
{
	m_pageScaling.RefreshParameterInfo();
}
VOID CGRDParametersFolder::RefreshParameterInfo(CONST CTMParameter *pTMParameter, CONST CGRDParameterSamples &pParameterSamples, INT nIndex)
{
	m_pageScaling.RefreshParameterInfo(pParameterSamples, nIndex);
}

CGRDParametersDialog *CGRDParametersFolder::GetParentDialog() CONST
{
	return((CGRDParametersDialog *)CLocalePropertySheetDialog::GetParent());
}

CGRDWnd *CGRDParametersFolder::GetParentDisplay() CONST
{
	return((CGRDWnd *)GetParentDialog()->GetParent());
}

BEGIN_MESSAGE_MAP(CGRDParametersFolder, CLocalePropertySheetDialog)
	//{{AFX_MSG_MAP(CGRDParametersFolder)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDParametersFolder message handlers

void CGRDParametersFolder::OnSetFocus(CWnd *pOldWnd)
{
	if (IsWindow(m_wndTabCtrl.GetSafeHwnd()))
	{
		m_wndTabCtrl.SetFocus();
		return;
	}
	CLocalePropertySheetDialog::OnSetFocus(pOldWnd);
}


/////////////////////////////////////////////////////////////////////////////
// CGRDParametersDialog dialog

IMPLEMENT_DYNCREATE(CGRDParametersDialog, CDisplayDialog)

CGRDParametersDialog::CGRDParametersDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CGRDParametersDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CGRDParametersDialog::Create(CWnd *pParentWnd)
{
	return Create(pParentWnd, EMPTYSTRING);
}
INT CGRDParametersDialog::Create(CWnd *pParentWnd, LPCTSTR pszParameter)
{
	m_szParameter = pszParameter;
	return CDisplayDialog::Create(pParentWnd, CGRDParametersDialog::IDD);
}

BOOL CGRDParametersDialog::SetParameters(CONST CGRDLayout &cLayout)
{
	return m_wndFolderCtrl.SetParameters(cLayout);
}

BOOL CGRDParametersDialog::GetParameters(CGRDLayout &cLayout) CONST
{
	return m_wndFolderCtrl.GetParameters(cLayout);
}

VOID CGRDParametersDialog::ShowParameterInfo()
{
	INT  nParameter;
	INT  nParameters;
	CString  szParameter[2];
	CTMParameter  cTMParameter;
	CGRDLayoutParameter  *pParameter;
	CGRDParameterSamples  pParameterSamples;
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CGRDLayout  cLayout;

	GetDlgItem(IDC_GRD_PARAMETERS_ITEM)->GetWindowText(szParameter[0]);
	for (nParameter = 0, nParameters = (GetParent()->GetLayout(cLayout)) ? (INT)cLayout.GetSize() : -1; nParameter < nParameters; nParameter++)
	{
		if ((pDatabaseTMParameter = ((pParameter = cLayout.GetAt(nParameter))) ? GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pParameter->GetName())) : (CDatabaseTMParameter *)NULL))
		{
			szParameter[1].Format(STRING(IDS_GRDPARAMETERSDIALOG_PARAMETERFORMAT), (LPCTSTR)pDatabaseTMParameter->GetTag(), (LPCTSTR)pDatabaseTMParameter->GetDescription());
			if (szParameter[0] == szParameter[1]) break;
		}
	}
	for (; (pParameter = (nParameter < nParameters) ? cLayout.GetAt(nParameter) : (CGRDLayoutParameter *)NULL); )
	{
		GetParent()->GetParameterInfo(pParameter->GetName(), nParameter, &cTMParameter, pParameterSamples);
		ShowParameterInfo(&cTMParameter, pParameterSamples, nParameter);
		break;
	}
	for (; (pParameter = (nParameter == nParameters && nParameters > 0) ? cLayout.GetAt(0) : (CGRDLayoutParameter *)NULL); )
	{
		GetParent()->GetParameterInfo(pParameter->GetName(), 0, &cTMParameter, pParameterSamples);
		ShowParameterInfo(&cTMParameter, pParameterSamples, 0);
		break;
	}
	for (; nParameters < 0; )
	{
		m_wndFolderCtrl.ShowParameterInfo();
		break;
	}
}
VOID CGRDParametersDialog::ShowParameterInfo(CONST CTMParameter *pTMParameter, CONST CGRDParameterSamples &pParameterSamples, INT nIndex)
{
	m_wndFolderCtrl.ShowParameterInfo(pTMParameter, pParameterSamples, nIndex);
}

VOID CGRDParametersDialog::RefreshParameterInfo()
{
	INT  nParameter;
	INT  nParameters;
	CString  szParameter[2];
	CTMParameter  cTMParameter;
	CGRDLayoutParameter  *pParameter;
	CGRDParameterSamples  pParameterSamples;
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CGRDLayout  cLayout;

	GetDlgItem(IDC_GRD_PARAMETERS_ITEM)->GetWindowText(szParameter[0]);
	for (nParameter = 0, nParameters = (GetParent()->GetLayout(cLayout)) ? (INT)cLayout.GetSize() : -1; nParameter < nParameters; nParameter++)
	{
		if ((pDatabaseTMParameter = ((pParameter = cLayout.GetAt(nParameter))) ? GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pParameter->GetName())) : (CDatabaseTMParameter *)NULL))
		{
			szParameter[1].Format(STRING(IDS_GRDPARAMETERSDIALOG_PARAMETERFORMAT), (LPCTSTR)pDatabaseTMParameter->GetTag(), (LPCTSTR)pDatabaseTMParameter->GetDescription());
			if (szParameter[0] == szParameter[1]) break;
		}
	}
	for (; (pParameter = (nParameter < nParameters) ? cLayout.GetAt(nParameter) : (CGRDLayoutParameter *)NULL); )
	{
		GetParent()->GetParameterInfo(pParameter->GetName(), nParameter, &cTMParameter, pParameterSamples);
		RefreshParameterInfo(&cTMParameter, pParameterSamples, nParameter);
		break;
	}
	for (; (pParameter = (nParameter == nParameters && nParameters > 0) ? cLayout.GetAt(0) : (CGRDLayoutParameter *)NULL); )
	{
		GetParent()->GetParameterInfo(pParameter->GetName(), 0, &cTMParameter, pParameterSamples);
		RefreshParameterInfo(&cTMParameter, pParameterSamples, 0);
		break;
	}
	for (; nParameters < 0; )
	{
		m_wndFolderCtrl.RefreshParameterInfo();
		break;
	}
}
VOID CGRDParametersDialog::RefreshParameterInfo(CONST CTMParameter *pTMParameter, CONST CGRDParameterSamples &pParameterSamples, INT nIndex)
{
	m_wndFolderCtrl.RefreshParameterInfo(pTMParameter, pParameterSamples, nIndex);
}

CGRDWnd *CGRDParametersDialog::GetParent() CONST
{
	return((CGRDWnd *)CDisplayDialog::GetParent());
}

BOOL CGRDParametersDialog::EnumParameters()
{
	INT  nParameter;
	INT  nParameters;
	CString  szParameter;
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CGRDLayout  cLayout;

	for (nParameter = 0, nParameters = (GetParent()->GetLayout(cLayout)) ? (INT)cLayout.GetSize() : -1; nParameter < nParameters; nParameter++)
	{
		if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(cLayout.GetAt(nParameter)->GetName()))))
		{
			szParameter.Format(STRING(IDS_GRDPARAMETERSDIALOG_PARAMETERFORMAT), (LPCTSTR)pDatabaseTMParameter->GetTag(), (LPCTSTR)pDatabaseTMParameter->GetDescription());
			SendDlgItemMessage(IDC_GRD_PARAMETERS_ITEM, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szParameter);
		}
	}
	SendDlgItemMessage(IDC_GRD_PARAMETERS_ITEM, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_GRD_PARAMETERS_ITEM, CB_FINDSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)m_szParameter), 0));
	GetDlgItem(IDC_GRD_PARAMETERS_DETAILS)->EnableWindow((SendDlgItemMessage(IDC_GRD_PARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_ITEM_STATIC)->EnableWindow((SendDlgItemMessage(IDC_GRD_PARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_PARAMETERS_ITEM)->EnableWindow((SendDlgItemMessage(IDC_GRD_PARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	m_wndFolderCtrl.EnableWindow((SendDlgItemMessage(IDC_GRD_PARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	return((SendDlgItemMessage(IDC_GRD_PARAMETERS_ITEM, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

CRect CGRDParametersDialog::CalcFolderSize() CONST
{
	CRect  rFolder;

	GetDlgItem(IDC_GRD_PARAMETERS_FOLDER)->GetWindowRect(rFolder);
	ScreenToClient(rFolder);
	return rFolder;
}

BOOL CGRDParametersDialog::IsModified() CONST
{
	return m_wndFolderCtrl.IsModified();
}

void CGRDParametersDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGRDParametersDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGRDParametersDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CGRDParametersDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_GRD_PARAMETERS_HELP, OnHelp)
	ON_CBN_SELCHANGE(IDC_GRD_PARAMETERS_ITEM, OnSelchangeParameter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDParametersDialog message handlers

BOOL CGRDParametersDialog::OnInitDialog()
{
	CGRDLayout  cLayout;
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	if (m_wndFolderCtrl.Create(this, CalcFolderSize()) && SetChildSheet(&m_wndFolderCtrl, GetDlgItem(IDC_GRD_PARAMETERS_FOLDER - 1)))
	{
		for (GetParent()->GetLayout(cLayout), SetParameters(cLayout); EnumParameters(); )
		{
			ShowParameterInfo();
			break;
		}
	}
	return TRUE;
}

void CGRDParametersDialog::OnSelchangeParameter()
{
	ShowParameterInfo();
}

void CGRDParametersDialog::OnOK()
{
	CGRDLayout  cLayout;
	CByteArray  nScalingData;
	CHourglassCursor  cCursor;

	if (IsModified())
	{
		for (; GetParameters(cLayout) && cLayout.GetScalingData(nScalingData); )
		{
			GetParent()->SetScalingData(nScalingData);
			break;
		}
	}
	CDisplayDialog::OnOK();
}

void CGRDParametersDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnCancel();
}

BOOL CGRDParametersDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_GRDPARAMETERSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CGRDParametersDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_GRDPARAMETERSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CGRDRetrieveDialog dialog

IMPLEMENT_DYNCREATE(CGRDRetrieveDialog, CDisplayDialog)

CGRDRetrieveDialog::CGRDRetrieveDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CGRDRetrieveDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CGRDRetrieveDialog::Create(CWnd *pParentWnd)
{
	CString  szType;
	CString  szTitle;
	CGRDWnd  *pGRDWnd;
	CGRDLayout  cLayout;

	if ((pGRDWnd = (CGRDWnd *)pParentWnd))
	{
		for (szTitle = (pGRDWnd->GetLayout(cLayout)) ? ((!cLayout.GetTitle().IsEmpty()) ? cLayout.GetTitle() : cLayout.GetName()) : STRING(IDS_WINDOW_UNKNOWNTITLE); HIWORD(pGRDWnd->GetType()) == GRD_TYPE_NORMAL; )
		{
			szType.Format(STRING(IDS_GRDRETRIEVEDIALOG_TYPENORMAL), (LPCTSTR)cLayout.GetName());
			break;
		}
		for (; HIWORD(pGRDWnd->GetType()) == GRD_TYPE_TEMPORARY; )
		{
			szType = STRING(IDS_GRDRETRIEVEDIALOG_TYPETEMPORARY);
			break;
		}
		return Create(pParentWnd, szTitle, szType);
	}
	return -1;
}
INT CGRDRetrieveDialog::Create(CWnd *pParentWnd, LPCTSTR pszTitle, LPCTSTR pszType)
{
	m_szType = pszType;
	m_szTitle = pszTitle;
	return CDisplayDialog::Create(pParentWnd, CGRDRetrieveDialog::IDD);
}

BOOL CGRDRetrieveDialog::GetMode(UINT &nMode) CONST
{
	nMode = (!IsDlgButtonChecked(IDC_GRD_RETRIEVE_REALTIME)) ? ((IsDlgButtonChecked(IDC_GRD_RETRIEVE_HISTORY_EXACTTIME)) ? GRD_RETRIEVE_EXACTTIME : 0) : 0;
	nMode |= (!IsDlgButtonChecked(IDC_GRD_RETRIEVE_REALTIME)) ? ((IsDlgButtonChecked(IDC_GRD_RETRIEVE_HISTORY_STOPBYTIME) || IsDlgButtonChecked(IDC_GRD_RETRIEVE_HISTORY_STOPBYEND) || IsDlgButtonChecked(IDC_GRD_RETRIEVE_HISTORY_STOPBYREALTIME)) ? ((!IsDlgButtonChecked(IDC_GRD_RETRIEVE_HISTORY_STOPBYTIME)) ? ((!IsDlgButtonChecked(IDC_GRD_RETRIEVE_HISTORY_STOPBYEND)) ? GRD_RETRIEVE_STOPBYREALTIME : GRD_RETRIEVE_STOPBYEND) : GRD_RETRIEVE_STOPBYTIME) : 0) : 0;
	nMode |= (!IsDlgButtonChecked(IDC_GRD_RETRIEVE_REALTIME)) ? ((IsDlgButtonChecked(IDC_GRD_RETRIEVE_HISTORY_AUTOMATIC)) ? GRD_RETRIEVE_AUTOFORWARD : ((IsDlgButtonChecked(IDC_GRD_RETRIEVE_HISTORY_PSEUDOREALTIME)) ? GRD_RETRIEVE_PSEUDOREALTIME : GRD_RETRIEVE_MANUALFORWARD)) : 0;
	return TRUE;
}

BOOL CGRDRetrieveDialog::GetSpeed(UINT &nSpeed) CONST
{
	nSpeed = (!IsDlgButtonChecked(IDC_GRD_RETRIEVE_HISTORY_AUTOMATIC)) ? (UINT)((GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_SPEED)->SendMessage(TBM_GETRANGEMIN) + GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_SPEED)->SendMessage(TBM_GETRANGEMAX)) / 2) : (UINT)GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_SPEED)->SendMessage(TBM_GETPOS);
	return((IsDlgButtonChecked(IDC_GRD_RETRIEVE_HISTORY_AUTOMATIC)) ? TRUE : FALSE);
}

BOOL CGRDRetrieveDialog::GetInterval(CTimeSpan &tInterval) CONST
{
	tInterval = (IsDlgButtonChecked(IDC_GRD_RETRIEVE_HISTORY_INTERVAL)) ? (SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_INTERVALTIME))) : 0;
	return((IsDlgButtonChecked(IDC_GRD_RETRIEVE_HISTORY_INTERVAL)) ? TRUE : FALSE);
}

BOOL CGRDRetrieveDialog::GetStartTime(CTimeKey &tTimeKey) CONST
{
	CTimeKey  tTime;

	for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_STARTTIME)), tTimeKey = 0; !IsDlgButtonChecked(IDC_GRD_RETRIEVE_REALTIME) && tTime > 0; )
	{
		tTimeKey = tTime;
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDRetrieveDialog::GetStopTime(CTimeKey &tTimeKey) CONST
{
	CTimeKey  tTime;

	for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_STOPTIME)), tTimeKey = 0; IsDlgButtonChecked(IDC_GRD_RETRIEVE_HISTORY_STOPBYTIME) && tTime > 0; )
	{
		tTimeKey = tTime;
		return TRUE;
	}
	return FALSE;
}

CGRDOpenDialog *CGRDRetrieveDialog::GetParentDialog() CONST
{
	return((GetParent() != (CWnd *)GetParentDisplay()) ? (CGRDOpenDialog *)GetParent() : (CGRDOpenDialog *)NULL);
}

CGRDWnd *CGRDRetrieveDialog::GetParentDisplay() CONST
{
	return((CGRDWnd *)CDisplayDialog::GetParentDisplay());
}

BOOL CGRDRetrieveDialog::SetRetrieveInfo()
{
	UINT  nMode;
	UINT  nSpeed;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;

	if (GetRetrieveInfo(nMode, nSpeed, tInterval, tStartTime, tStopTime))
	{
		Spinbox_SetPos(GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_INTERVALTIME), (tInterval.GetTotalSeconds() / SECONDSPERMINUTE));
		Timespinbox_SetTime(GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_STARTTIME), (tStartTime > 0 || GetTMService()->GetRecentTMHistoryTimeKey(tStartTime)) ? tStartTime : CTime::GetCurrentTime().GetTime());
		Timespinbox_SetTime(GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_STOPTIME), (tStopTime.GetTime() > 0) ? tStopTime : CTime::GetCurrentTime().GetTime());
		Timespinbox_SetRange(GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_STOPTIME), Timespinbox_GetTime(GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_STARTTIME)), MAX_TIMEKEY);
		SendDlgItemMessage(IDC_GRD_RETRIEVE_HISTORY_SPEED, TBM_SETPOS, TRUE, (!IsDlgButtonChecked(IDC_GRD_RETRIEVE_REALTIME)) ? ((nMode) ? ((nMode & GRD_RETRIEVE_AUTOFORWARD) ? nSpeed : 0) : ((SendDlgItemMessage(IDC_GRD_RETRIEVE_HISTORY_SPEED, TBM_GETRANGEMIN) + SendDlgItemMessage(IDC_GRD_RETRIEVE_HISTORY_SPEED, TBM_GETRANGEMAX)) / 2)) : 0);
		CheckDlgButton(IDC_GRD_RETRIEVE_HISTORY_EXACTTIME, (!IsDlgButtonChecked(IDC_GRD_RETRIEVE_REALTIME) && (nMode & GRD_RETRIEVE_EXACTTIME)) ? TRUE : FALSE);
		CheckDlgButton(IDC_GRD_RETRIEVE_HISTORY_STOPBYTIME, (!IsDlgButtonChecked(IDC_GRD_RETRIEVE_REALTIME) && (nMode & GRD_RETRIEVE_STOPBYTIME) && (nMode & GRD_RETRIEVE_MANUALFORWARD) == 0) ? TRUE : FALSE);
		CheckDlgButton(IDC_GRD_RETRIEVE_HISTORY_STOPBYEND, (!IsDlgButtonChecked(IDC_GRD_RETRIEVE_REALTIME) && (nMode & GRD_RETRIEVE_STOPBYEND) && (nMode & GRD_RETRIEVE_MANUALFORWARD) == 0) ? TRUE : FALSE);
		CheckDlgButton(IDC_GRD_RETRIEVE_HISTORY_STOPBYREALTIME, (!IsDlgButtonChecked(IDC_GRD_RETRIEVE_REALTIME) && (!nMode || (nMode & GRD_RETRIEVE_STOPBYREALTIME))) ? TRUE : FALSE);
		CheckDlgButton(IDC_GRD_RETRIEVE_HISTORY_AUTOMATIC, (!IsDlgButtonChecked(IDC_GRD_RETRIEVE_REALTIME) && (!nMode || (nMode & GRD_RETRIEVE_AUTOFORWARD))) ? TRUE : FALSE);
		CheckDlgButton(IDC_GRD_RETRIEVE_HISTORY_MANUAL, (!IsDlgButtonChecked(IDC_GRD_RETRIEVE_REALTIME) && (nMode & GRD_RETRIEVE_MANUALFORWARD)) ? TRUE : FALSE);
		CheckDlgButton(IDC_GRD_RETRIEVE_HISTORY_PSEUDOREALTIME, (!IsDlgButtonChecked(IDC_GRD_RETRIEVE_REALTIME) && (nMode & GRD_RETRIEVE_PSEUDOREALTIME)) ? TRUE : FALSE);
		CheckDlgButton(IDC_GRD_RETRIEVE_HISTORY_INTERVAL, (!IsDlgButtonChecked(IDC_GRD_RETRIEVE_REALTIME) && (nMode & GRD_RETRIEVE_PSEUDOREALTIME) == 0 && tInterval.GetTotalSeconds() > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_GRD_RETRIEVE_HISTORY)->EnableWindow(!IsDlgButtonChecked(IDC_GRD_RETRIEVE_REALTIME));
		GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_START_STATIC)->EnableWindow(!IsDlgButtonChecked(IDC_GRD_RETRIEVE_REALTIME));
		GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_STARTTIME)->EnableWindow(!IsDlgButtonChecked(IDC_GRD_RETRIEVE_REALTIME));
		GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_EXACTTIME)->EnableWindow(!IsDlgButtonChecked(IDC_GRD_RETRIEVE_REALTIME));
		GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_STOP_STATIC)->EnableWindow(!IsDlgButtonChecked(IDC_GRD_RETRIEVE_REALTIME));
		GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_STOPBYTIME)->EnableWindow(!IsDlgButtonChecked(IDC_GRD_RETRIEVE_REALTIME) && !IsDlgButtonChecked(IDC_GRD_RETRIEVE_HISTORY_MANUAL));
		GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(!IsDlgButtonChecked(IDC_GRD_RETRIEVE_REALTIME) && IsDlgButtonChecked(IDC_GRD_RETRIEVE_HISTORY_STOPBYTIME));
		GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_STOPBYEND)->EnableWindow(!IsDlgButtonChecked(IDC_GRD_RETRIEVE_REALTIME) && !IsDlgButtonChecked(IDC_GRD_RETRIEVE_HISTORY_MANUAL));
		GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_STOPBYREALTIME)->EnableWindow(!IsDlgButtonChecked(IDC_GRD_RETRIEVE_REALTIME));
		GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_PLAYBACKMODE)->EnableWindow(!IsDlgButtonChecked(IDC_GRD_RETRIEVE_REALTIME));
		GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_AUTOMATIC)->EnableWindow(!IsDlgButtonChecked(IDC_GRD_RETRIEVE_REALTIME));
		GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_PSEUDOREALTIME)->EnableWindow(!IsDlgButtonChecked(IDC_GRD_RETRIEVE_REALTIME));
		GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_MANUAL)->EnableWindow(!IsDlgButtonChecked(IDC_GRD_RETRIEVE_REALTIME));
		GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_SPEED_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_GRD_RETRIEVE_HISTORY_AUTOMATIC));
		GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_SPEED)->EnableWindow(IsDlgButtonChecked(IDC_GRD_RETRIEVE_HISTORY_AUTOMATIC));
		GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_SLOW)->EnableWindow(IsDlgButtonChecked(IDC_GRD_RETRIEVE_HISTORY_AUTOMATIC));
		GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_FAST)->EnableWindow(IsDlgButtonChecked(IDC_GRD_RETRIEVE_HISTORY_AUTOMATIC));
		GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_INTERVAL)->EnableWindow(!IsDlgButtonChecked(IDC_GRD_RETRIEVE_REALTIME) && !IsDlgButtonChecked(IDC_GRD_RETRIEVE_HISTORY_PSEUDOREALTIME));
		GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_INTERVALTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_GRD_RETRIEVE_HISTORY_INTERVAL));
		GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_INTERVALTIME)->EnableWindow(IsDlgButtonChecked(IDC_GRD_RETRIEVE_HISTORY_INTERVAL));
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDRetrieveDialog::GetRetrieveInfo(UINT &nMode, UINT &nSpeed, CTimeSpan &tInterval, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	CGRDWnd  *pGRDWnd;
	CGRDOpenDialog  *pDialog;

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
	if ((pGRDWnd = GetParentDisplay()))
	{
		for (pGRDWnd->GetRetrieveMode(nMode), nSpeed = 0, tInterval = 0, tStartTime = tStopTime = 0; nMode; )
		{
			pGRDWnd->GetRetrieveSpeed(nSpeed);
			pGRDWnd->GetRetrieveInterval(tInterval);
			pGRDWnd->GetRetrieveStartTime(tStartTime);
			pGRDWnd->GetRetrieveStopTime(tStopTime);
			break;
		}
		return TRUE;
	}
	return FALSE;
}

void CGRDRetrieveDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGRDRetrieveDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGRDRetrieveDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CGRDRetrieveDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_GRD_RETRIEVE_REALTIME, OnRetrieveRealtime)
	ON_BN_CLICKED(IDC_GRD_RETRIEVE_HISTORY_STOPBYTIME, OnRetrieveByTime)
	ON_BN_CLICKED(IDC_GRD_RETRIEVE_HISTORY_STOPBYEND, OnRetrieveByEnd)
	ON_BN_CLICKED(IDC_GRD_RETRIEVE_HISTORY_STOPBYREALTIME, OnRetrieveByRealtime)
	ON_BN_CLICKED(IDC_GRD_RETRIEVE_HISTORY_AUTOMATIC, OnRetrieveAutomatic)
	ON_BN_CLICKED(IDC_GRD_RETRIEVE_HISTORY_PSEUDOREALTIME, OnRetrievePseudoRealtime)
	ON_BN_CLICKED(IDC_GRD_RETRIEVE_HISTORY_MANUAL, OnRetrieveManual)
	ON_BN_CLICKED(IDC_GRD_RETRIEVE_HISTORY_INTERVAL, OnRetrieveInterval)
	ON_BN_CLICKED(IDC_GRD_RETRIEVE_HELP, OnHelp)
	ON_CONTROL(TSBXN_CHANGE, IDC_GRD_RETRIEVE_HISTORY_STARTTIME, OnSpinchangeRetrieveStartTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDRetrieveDialog message handlers

BOOL CGRDRetrieveDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	for (CDisplayDialog::OnInitDialog(), SendDlgItemMessage(IDC_GRD_RETRIEVE_HISTORY_SPEED, TBM_SETRANGE, TRUE, MAKELPARAM(0, 10)), Spinbox_SetRange(GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_INTERVALTIME), GRDRETRIEVEDIALOG_MINIMUMINTERVAL, GRDRETRIEVEDIALOG_MAXIMUMINTERVAL), GetDlgItem(IDC_GRD_RETRIEVE_TITLE)->SetWindowText(m_szTitle), GetDlgItem(IDC_GRD_RETRIEVE_TYPE)->SetWindowText(m_szType); SetRetrieveInfo(); )
	{
		GetDlgItem(IDC_GRD_RETRIEVE_DETAILS)->EnableWindow();
		GetDlgItem(IDC_GRD_RETRIEVE_TITLE_STATIC)->EnableWindow();
		GetDlgItem(IDC_GRD_RETRIEVE_TITLE)->EnableWindow();
		GetDlgItem(IDC_GRD_RETRIEVE_TYPE_STATIC)->EnableWindow();
		GetDlgItem(IDC_GRD_RETRIEVE_TYPE)->EnableWindow();
		GetDlgItem(IDC_GRD_RETRIEVE_REALTIME)->EnableWindow((GetParentDisplay()->GetMode() == DISPLAY_MODE_HISTORY) ? TRUE : FALSE);
		GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_STARTTIME)->SetFocus();
		GetDlgItem(IDOK)->EnableWindow();
		return FALSE;
	}
	return TRUE;
}

void CGRDRetrieveDialog::OnRetrieveRealtime()
{
	SetRetrieveInfo();
}

void CGRDRetrieveDialog::OnRetrieveByTime()
{
	CheckDlgButton(IDC_GRD_RETRIEVE_HISTORY_STOPBYTIME, TRUE);
	CheckDlgButton(IDC_GRD_RETRIEVE_HISTORY_STOPBYEND, FALSE);
	CheckDlgButton(IDC_GRD_RETRIEVE_HISTORY_STOPBYREALTIME, FALSE);
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_STOPTIME)->EnableWindow();
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_STOPTIME)->SetFocus();
}

void CGRDRetrieveDialog::OnRetrieveByEnd()
{
	CheckDlgButton(IDC_GRD_RETRIEVE_HISTORY_STOPBYTIME, FALSE);
	CheckDlgButton(IDC_GRD_RETRIEVE_HISTORY_STOPBYEND, TRUE);
	CheckDlgButton(IDC_GRD_RETRIEVE_HISTORY_STOPBYREALTIME, FALSE);
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(FALSE);
}

void CGRDRetrieveDialog::OnRetrieveByRealtime()
{
	CheckDlgButton(IDC_GRD_RETRIEVE_HISTORY_STOPBYTIME, FALSE);
	CheckDlgButton(IDC_GRD_RETRIEVE_HISTORY_STOPBYEND, FALSE);
	CheckDlgButton(IDC_GRD_RETRIEVE_HISTORY_STOPBYREALTIME, (IsDlgButtonChecked(IDC_GRD_RETRIEVE_HISTORY_MANUAL)) ? !IsDlgButtonChecked(IDC_GRD_RETRIEVE_HISTORY_STOPBYREALTIME) : TRUE);
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(FALSE);
}

void CGRDRetrieveDialog::OnRetrieveAutomatic()
{
	SendDlgItemMessage(IDC_GRD_RETRIEVE_HISTORY_SPEED, TBM_SETPOS, TRUE, (SendDlgItemMessage(IDC_GRD_RETRIEVE_HISTORY_SPEED, TBM_GETRANGEMIN) + SendDlgItemMessage(IDC_GRD_RETRIEVE_HISTORY_SPEED, TBM_GETRANGEMAX)) / 2);
	CheckDlgButton(IDC_GRD_RETRIEVE_HISTORY_STOPBYTIME, FALSE);
	CheckDlgButton(IDC_GRD_RETRIEVE_HISTORY_STOPBYEND, FALSE);
	CheckDlgButton(IDC_GRD_RETRIEVE_HISTORY_STOPBYREALTIME, TRUE);
	CheckDlgButton(IDC_GRD_RETRIEVE_HISTORY_AUTOMATIC, TRUE);
	CheckDlgButton(IDC_GRD_RETRIEVE_HISTORY_PSEUDOREALTIME, FALSE);
	CheckDlgButton(IDC_GRD_RETRIEVE_HISTORY_MANUAL, FALSE);
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_STOP_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_STOPBYTIME)->EnableWindow();
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_GRD_RETRIEVE_HISTORY_STOPBYTIME));
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_STOPBYEND)->EnableWindow();
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_STOPBYREALTIME)->EnableWindow();
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_SPEED_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_SPEED)->EnableWindow();
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_SLOW)->EnableWindow();
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_FAST)->EnableWindow();
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_INTERVAL)->EnableWindow();
}

void CGRDRetrieveDialog::OnRetrievePseudoRealtime()
{
	SendDlgItemMessage(IDC_GRD_RETRIEVE_HISTORY_SPEED, TBM_SETPOS, TRUE, 0);
	CheckDlgButton(IDC_GRD_RETRIEVE_HISTORY_STOPBYTIME, FALSE);
	CheckDlgButton(IDC_GRD_RETRIEVE_HISTORY_STOPBYEND, FALSE);
	CheckDlgButton(IDC_GRD_RETRIEVE_HISTORY_STOPBYREALTIME, TRUE);
	CheckDlgButton(IDC_GRD_RETRIEVE_HISTORY_AUTOMATIC, FALSE);
	CheckDlgButton(IDC_GRD_RETRIEVE_HISTORY_PSEUDOREALTIME, TRUE);
	CheckDlgButton(IDC_GRD_RETRIEVE_HISTORY_MANUAL, FALSE);
	CheckDlgButton(IDC_GRD_RETRIEVE_HISTORY_INTERVAL, FALSE);
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_STOP_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_STOPBYTIME)->EnableWindow();
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_GRD_RETRIEVE_HISTORY_STOPBYTIME));
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_STOPBYEND)->EnableWindow();
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_STOPBYREALTIME)->EnableWindow();
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_SPEED_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_SPEED)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_SLOW)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_FAST)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_INTERVAL)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_INTERVALTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_INTERVALTIME)->EnableWindow(FALSE);
}

void CGRDRetrieveDialog::OnRetrieveManual()
{
	SendDlgItemMessage(IDC_GRD_RETRIEVE_HISTORY_SPEED, TBM_SETPOS, TRUE, 0);
	CheckDlgButton(IDC_GRD_RETRIEVE_HISTORY_STOPBYTIME, FALSE);
	CheckDlgButton(IDC_GRD_RETRIEVE_HISTORY_STOPBYEND, FALSE);
	CheckDlgButton(IDC_GRD_RETRIEVE_HISTORY_STOPBYREALTIME, FALSE);
	CheckDlgButton(IDC_GRD_RETRIEVE_HISTORY_AUTOMATIC, FALSE);
	CheckDlgButton(IDC_GRD_RETRIEVE_HISTORY_PSEUDOREALTIME, FALSE);
	CheckDlgButton(IDC_GRD_RETRIEVE_HISTORY_MANUAL, TRUE);
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_STOP_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_STOPBYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_STOPBYEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_STOPBYREALTIME)->EnableWindow();
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_SPEED_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_SPEED)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_SLOW)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_FAST)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_INTERVAL)->EnableWindow();
}

void CGRDRetrieveDialog::OnRetrieveInterval()
{
	Spinbox_SetPos(GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_INTERVALTIME), GRDRETRIEVEDIALOG_DEFAULTINTERVAL);
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_INTERVALTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_GRD_RETRIEVE_HISTORY_INTERVAL));
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_INTERVALTIME)->EnableWindow(IsDlgButtonChecked(IDC_GRD_RETRIEVE_HISTORY_INTERVAL));
	GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_INTERVALTIME)->SetFocus();
}

void CGRDRetrieveDialog::OnSpinchangeRetrieveStartTime()
{
	Timespinbox_SetRange(GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_STOPTIME), Timespinbox_GetTime(GetDlgItem(IDC_GRD_RETRIEVE_HISTORY_STARTTIME)), MAX_TIMEKEY);
}

void CGRDRetrieveDialog::OnOK()
{
	CGRDWnd  *pGRDWnd;
	CTimeKey  tTimeKey;
	CGRDLayout  cLayout;
	CDisplayWnd  *pDisplayWnd;
	CGRDOpenDialog  *pDialog;
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
		if (IsDlgButtonChecked(IDC_GRD_RETRIEVE_REALTIME))
		{
			if ((pGRDWnd = (GetParentDisplay()->GetLayout(cLayout)) ? GetParentDisplay()->Find(GetParentDisplay()->GetType(), DISPLAY_MODE_REALTIME, cLayout.GetName()) : (CGRDWnd *)NULL))
			{
				for (GetDisplayArea()->ActivateDisplay(pGRDWnd); pGRDWnd != GetParentDisplay(); )
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

void CGRDRetrieveDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	if (!GetParentDialog()) GetParentDisplay()->OnCloseRetrieveDialog(IDCANCEL);
	else  GetParentDialog()->OnCloseRetrieveDialog(IDCANCEL);
	CDisplayDialog::OnCancel();
}

BOOL CGRDRetrieveDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_GRDRETRIEVEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CGRDRetrieveDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_GRDRETRIEVEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CGRDImportDialog dialog

IMPLEMENT_DYNCREATE(CGRDImportDialog, CLocaleDialog)

CGRDImportDialog::CGRDImportDialog(CWnd *pParentWnd) : CLocaleDialog(CGRDImportDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CGRDImportDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CGRDImportDialog::Initialize()
{
	EnumTemporaryGRDs(m_pDisplays[0]);
	return TRUE;
}

VOID CGRDImportDialog::EnumDisplays()
{
	INT  nLayout;
	INT  nLayouts;
	DWORD  cbData;
	CFileEx  cFile;
	CString  szMessage;
	CString  szFileName;
	CByteArray  nFileData;
	CGRDLayout  *pGRDLayout;

	SendDlgItemMessage(IDC_GRD_IMPORT_DIRECTORY, CB_RESETCONTENT);
	GetDlgItem(IDC_GRD_IMPORT_FILENAME)->GetWindowText(szFileName);
	if (cFile.Open(szFileName, CFile::modeRead | CFile::shareExclusive))
	{
		nFileData.SetSize((cbData = (DWORD)cFile.GetLength()*sizeof(BYTE)));
		if (ReadFile(cFile.m_hFile, nFileData.GetData(), (DWORD)nFileData.GetSize(), &cbData, (LPOVERLAPPED)NULL))
		{
			for (nLayout = 0, nLayouts = (m_pDisplays[1].Unmap(nFileData)) ? (INT)m_pDisplays[1].GetSize() : 0; nLayout < nLayouts; nLayout++)
			{
				if ((pGRDLayout = m_pDisplays[1].GetAt(nLayout))) SendDlgItemMessage(IDC_GRD_IMPORT_DIRECTORY, CB_INSERTSTRING, nLayout, (LPARAM)(LPCTSTR)pGRDLayout->GetTitle());
				continue;
			}
		}
		else
		{
			szMessage = STRING(IDS_GRD_IMPORT_FILE_FAILURE);
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_ERROR, szMessage);
		}
		cFile.Close();
	}
	else
	{
		szMessage = STRING(IDS_GRD_IMPORT_FILE_FAILURE);
		ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_ERROR, szMessage);
	}
	if (SendDlgItemMessage(IDC_GRD_IMPORT_DIRECTORY, CB_GETCOUNT) > 0)
	{
		SendDlgItemMessage(IDC_GRD_IMPORT_DIRECTORY, CB_SETCURSEL);
		GetDlgItem(IDC_GRD_IMPORT_DIRECTORY_STATIC)->EnableWindow();
		GetDlgItem(IDC_GRD_IMPORT_DIRECTORY)->EnableWindow();
		return;
	}
	GetDlgItem(IDC_GRD_IMPORT_DIRECTORY_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_IMPORT_DIRECTORY)->EnableWindow(FALSE);
}

BOOL CGRDImportDialog::Check(BOOL bModified) CONST
{
	return((m_pDisplays[2].GetSize() > 0) ? TRUE : FALSE);
}

void CGRDImportDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGRDImportDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CGRDImportDialog::PostNcDestroy()
{
	m_pDisplays[0].RemoveAll();
	m_pDisplays[1].RemoveAll();
	m_pDisplays[2].RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CGRDImportDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CGRDImportDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_GRD_IMPORT_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_GRD_IMPORT_INSPECT, OnInspect)
	ON_BN_CLICKED(IDC_GRD_IMPORT_ADD, OnAdd)
	ON_BN_CLICKED(IDC_GRD_IMPORT_ADDALL, OnAddAll)
	ON_BN_CLICKED(IDC_GRD_IMPORT_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_GRD_IMPORT_REMOVEALL, OnRemoveAll)
	ON_BN_CLICKED(IDC_GRD_IMPORT_HELP, OnHelp)
	ON_EN_CHANGE(IDC_GRD_IMPORT_FILENAME, OnEditchangeFileName)
	ON_CBN_SELCHANGE(IDC_GRD_IMPORT_DIRECTORY, OnSelchangeSource)
	ON_LBN_SELCHANGE(IDC_GRD_IMPORT_LIST, OnSelchangeDestination)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDImportDialog message handlers

BOOL CGRDImportDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_GRD_IMPORT_DETAILS)->EnableWindow();
	GetDlgItem(IDC_GRD_IMPORT_FILENAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRD_IMPORT_FILENAME)->EnableWindow();
	GetDlgItem(IDC_GRD_IMPORT_BROWSE)->EnableWindow();
	GetDlgItem(IDC_GRD_IMPORT_DIRECTORY_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_IMPORT_DIRECTORY)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_IMPORT_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_IMPORT_ADDALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_IMPORT_ATTENTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_IMPORT_ATTENTION_TEXT)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_IMPORT_LIST_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_IMPORT_LIST)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_IMPORT_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_IMPORT_REMOVEALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_IMPORT_FILENAME)->SetFocus();
	return FALSE;
}

void CGRDImportDialog::OnBrowse()
{
	CString  szFileName;
	CFileBrowseDialog  cFileBrowseDialog(this, IDC_GRD_IMPORT_FILENAME, STRING(IDS_FILEBROWSEDIALOG_DATABASEFILEEXTENSION), STRING(IDS_FILEBROWSEDIALOG_DATABASEFILEFILTER));

	if (cFileBrowseDialog.DoModal() == IDOK)
	{
		GetDlgItem(IDC_GRD_IMPORT_FILENAME)->SetWindowText((szFileName = cFileBrowseDialog.GetPathName()));
		GetDlgItem(IDC_GRD_IMPORT_BROWSE)->ShowWindow((szFileName.IsEmpty()) ? SW_SHOW : SW_HIDE);
		GetDlgItem(IDC_GRD_IMPORT_INSPECT)->ShowWindow((!szFileName.IsEmpty()) ? SW_SHOW : SW_HIDE);
		GetDlgItem(IDC_GRD_IMPORT_BROWSE)->EnableWindow((szFileName.IsEmpty()) ? TRUE : FALSE);
		GetDlgItem(IDC_GRD_IMPORT_INSPECT)->EnableWindow((!szFileName.IsEmpty()) ? TRUE : FALSE);
	}
	SendDlgItemMessage(IDC_GRD_IMPORT_FILENAME, EM_SETSEL, 0, (LPARAM)-1);
	GetDlgItem(IDC_GRD_IMPORT_FILENAME)->SetFocus();
}

void CGRDImportDialog::OnInspect()
{
	INT  nLayout;
	INT  nLayouts;
	CString  szLayout;
	CHourglassCursor  cCursor;

	EnumDisplays();
	for (nLayout = 0, nLayouts = (INT)SendDlgItemMessage(IDC_GRD_IMPORT_DIRECTORY, CB_GETCOUNT); nLayout < nLayouts; nLayout++)
	{
		if (SendDlgItemMessage(IDC_GRD_IMPORT_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)Combobox_GetText(GetDlgItem(IDC_GRD_IMPORT_DIRECTORY), nLayout)) < 0) break;
		continue;
	}
	GetDlgItem(IDC_GRD_IMPORT_DIRECTORY)->GetWindowText(szLayout);
	GetDlgItem(IDC_GRD_IMPORT_ADD)->EnableWindow((SendDlgItemMessage(IDC_GRD_IMPORT_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szLayout) < 0 && !szLayout.IsEmpty()) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_IMPORT_ADDALL)->EnableWindow((nLayout < nLayouts) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_IMPORT_DIRECTORY)->SetFocus();
}

void CGRDImportDialog::OnAdd()
{
	INT  nLayout;
	INT  nLayouts;
	CString  szLayout;
	CGRDLayout  *pLayout[2];
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_GRD_IMPORT_DIRECTORY)->GetWindowText(szLayout);
	if (SendDlgItemMessage(IDC_GRD_IMPORT_LIST, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szLayout) >= 0)
	{
		if ((pLayout[0] = m_pDisplays[1].GetAt(m_pDisplays[1].Find(szLayout))))
		{
			if ((pLayout[1] = new CGRDLayout))
			{
				pLayout[1]->Copy(pLayout[0]);
				if (m_pDisplays[2].Add(pLayout[1]) < 0) delete pLayout[1];
			}
		}
		for (nLayout = 0, nLayouts = (INT)SendDlgItemMessage(IDC_GRD_IMPORT_LIST, LB_GETCOUNT); nLayout < nLayouts; nLayout++)
		{
			if (m_pDisplays[0].Find(Listbox_GetText(GetDlgItem(IDC_GRD_IMPORT_LIST), nLayout)) >= 0) break;
			continue;
		}
		SendDlgItemMessage(IDC_GRD_IMPORT_LIST, LB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_GRD_IMPORT_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szLayout));
		GetDlgItem(IDC_GRD_IMPORT_ATTENTION)->ShowWindow((nLayout < nLayouts) ? SW_SHOW : SW_HIDE);
		GetDlgItem(IDC_GRD_IMPORT_ATTENTION_TEXT)->ShowWindow((nLayout < nLayouts) ? SW_SHOW : SW_HIDE);
		GetDlgItem(IDC_GRD_IMPORT_ATTENTION)->EnableWindow((nLayout < nLayouts) ? TRUE : FALSE);
		GetDlgItem(IDC_GRD_IMPORT_ATTENTION_TEXT)->EnableWindow((nLayout < nLayouts) ? TRUE : FALSE);
		for (nLayout = 0, nLayouts = (INT)SendDlgItemMessage(IDC_GRD_IMPORT_DIRECTORY, CB_GETCOUNT); nLayout < nLayouts; nLayout++)
		{
			if (SendDlgItemMessage(IDC_GRD_IMPORT_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)Combobox_GetText(GetDlgItem(IDC_GRD_IMPORT_DIRECTORY), nLayout)) < 0) break;
			continue;
		}
		GetDlgItem(IDC_GRD_IMPORT_ADD)->EnableWindow(FALSE);
		GetDlgItem(IDC_GRD_IMPORT_ADDALL)->EnableWindow((nLayout < nLayouts) ? TRUE : FALSE);
		GetDlgItem(IDC_GRD_IMPORT_LIST_STATIC)->EnableWindow();
		GetDlgItem(IDC_GRD_IMPORT_LIST)->EnableWindow();
		GetDlgItem(IDC_GRD_IMPORT_REMOVE)->EnableWindow();
		GetDlgItem(IDC_GRD_IMPORT_REMOVEALL)->EnableWindow();
		GetDlgItem(IDC_GRD_IMPORT_DIRECTORY)->SetFocus();
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDImportDialog::OnAddAll()
{
	INT  nLayout;
	INT  nLayouts;
	CString  szLayout;
	CGRDLayout  *pLayout[2];
	CHourglassCursor  cCursor;

	for (nLayout = 0, nLayouts = (INT)SendDlgItemMessage(IDC_GRD_IMPORT_DIRECTORY, CB_GETCOUNT); nLayout < nLayouts; nLayout++)
	{
		if (SendDlgItemMessage(IDC_GRD_IMPORT_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)(szLayout = Combobox_GetText(GetDlgItem(IDC_GRD_IMPORT_DIRECTORY), nLayout))) < 0)
		{
			SendDlgItemMessage(IDC_GRD_IMPORT_LIST, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szLayout);
			continue;
		}
	}
	for (nLayout = 0, nLayouts = (INT)m_pDisplays[1].GetSize(); nLayout < nLayouts; nLayout++)
	{
		if ((pLayout[0] = m_pDisplays[1].GetAt(nLayout)) && m_pDisplays[2].Find(pLayout[0]->GetTitle()) < 0)
		{
			if ((pLayout[1] = new CGRDLayout))
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
	for (nLayout = 0, nLayouts = (INT)SendDlgItemMessage(IDC_GRD_IMPORT_LIST, LB_GETCOUNT); nLayout < nLayouts; nLayout++)
	{
		if (m_pDisplays[0].Find((szLayout = Listbox_GetText(GetDlgItem(IDC_GRD_IMPORT_LIST), nLayout))) >= 0) break;
		continue;
	}
	GetDlgItem(IDC_GRD_IMPORT_ATTENTION)->ShowWindow((nLayout < nLayouts) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_GRD_IMPORT_ATTENTION_TEXT)->ShowWindow((nLayout < nLayouts) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_GRD_IMPORT_ATTENTION)->EnableWindow((nLayout < nLayouts) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_IMPORT_ATTENTION_TEXT)->EnableWindow((nLayout < nLayouts) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_IMPORT_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_GRD_IMPORT_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_IMPORT_LIST)->EnableWindow((SendDlgItemMessage(IDC_GRD_IMPORT_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_IMPORT_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_IMPORT_ADDALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_IMPORT_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_GRD_IMPORT_LIST, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_IMPORT_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_GRD_IMPORT_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_IMPORT_DIRECTORY)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDImportDialog::OnRemove()
{
	INT  nIndex;
	INT  nLayout;
	INT  nLayouts;
	CString  szLayout;
	CHourglassCursor  cCursor;

	if ((nIndex = m_pDisplays[2].Find(Listbox_GetText(GetDlgItem(IDC_GRD_IMPORT_LIST), (INT)SendDlgItemMessage(IDC_GRD_IMPORT_LIST, LB_GETCURSEL)))) >= 0)
	{
		delete m_pDisplays[2].GetAt(nIndex);
		m_pDisplays[2].RemoveAt(nIndex);
	}
	if (SendDlgItemMessage(IDC_GRD_IMPORT_LIST, LB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_GRD_IMPORT_LIST, LB_GETCURSEL)) > 0)
	{
		for (nLayout = 0, nLayouts = (INT)SendDlgItemMessage(IDC_GRD_IMPORT_LIST, LB_GETCOUNT); nLayout < nLayouts; nLayout++)
		{
			if (m_pDisplays[0].Find((szLayout = Listbox_GetText(GetDlgItem(IDC_GRD_IMPORT_LIST), nLayout))) >= 0) break;
			continue;
		}
		SendDlgItemMessage(IDC_GRD_IMPORT_LIST, LB_SETCURSEL);
		GetDlgItem(IDC_GRD_IMPORT_DIRECTORY)->GetWindowText(szLayout);
		GetDlgItem(IDC_GRD_IMPORT_ATTENTION)->ShowWindow((nLayout < nLayouts) ? SW_SHOW : SW_HIDE);
		GetDlgItem(IDC_GRD_IMPORT_ATTENTION_TEXT)->ShowWindow((nLayout < nLayouts) ? SW_SHOW : SW_HIDE);
		GetDlgItem(IDC_GRD_IMPORT_ATTENTION)->EnableWindow((nLayout < nLayouts) ? TRUE : FALSE);
		GetDlgItem(IDC_GRD_IMPORT_ATTENTION_TEXT)->EnableWindow((nLayout < nLayouts) ? TRUE : FALSE);
		GetDlgItem(IDC_GRD_IMPORT_ADD)->EnableWindow((SendDlgItemMessage(IDC_GRD_IMPORT_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szLayout) < 0) ? TRUE : FALSE);
		GetDlgItem(IDC_GRD_IMPORT_ADDALL)->EnableWindow((SendDlgItemMessage(IDC_GRD_IMPORT_DIRECTORY, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	}
	else
	{
		GetDlgItem(IDC_GRD_IMPORT_ATTENTION)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_GRD_IMPORT_ATTENTION_TEXT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_GRD_IMPORT_ATTENTION)->EnableWindow(FALSE);
		GetDlgItem(IDC_GRD_IMPORT_ATTENTION_TEXT)->EnableWindow(FALSE);
		GetDlgItem(IDC_GRD_IMPORT_LIST_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_GRD_IMPORT_LIST)->EnableWindow(FALSE);
		GetDlgItem(IDC_GRD_IMPORT_ADD)->EnableWindow((SendDlgItemMessage(IDC_GRD_IMPORT_DIRECTORY, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
		GetDlgItem(IDC_GRD_IMPORT_ADDALL)->EnableWindow((SendDlgItemMessage(IDC_GRD_IMPORT_DIRECTORY, CB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_GRD_IMPORT_REMOVE)->EnableWindow(FALSE);
		GetDlgItem(IDC_GRD_IMPORT_REMOVEALL)->EnableWindow(FALSE);
	}
	GetDlgItem(IDC_GRD_IMPORT_DIRECTORY)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDImportDialog::OnRemoveAll()
{
	CHourglassCursor  cCursor;

	m_pDisplays[2].RemoveAll();
	SendDlgItemMessage(IDC_GRD_IMPORT_LIST, LB_RESETCONTENT);
	GetDlgItem(IDC_GRD_IMPORT_ATTENTION)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_GRD_IMPORT_ATTENTION_TEXT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_GRD_IMPORT_ATTENTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_IMPORT_ATTENTION_TEXT)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_IMPORT_LIST_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_IMPORT_LIST)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_IMPORT_ADD)->EnableWindow((SendDlgItemMessage(IDC_GRD_IMPORT_DIRECTORY, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_IMPORT_ADDALL)->EnableWindow((SendDlgItemMessage(IDC_GRD_IMPORT_DIRECTORY, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_IMPORT_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_IMPORT_REMOVEALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_IMPORT_DIRECTORY)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDImportDialog::OnEditchangeFileName()
{
	CString  szFileName;

	GetDlgItem(IDC_GRD_IMPORT_FILENAME)->GetWindowText(szFileName);
	GetDlgItem(IDC_GRD_IMPORT_BROWSE)->ShowWindow((szFileName.IsEmpty()) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_GRD_IMPORT_INSPECT)->ShowWindow((!szFileName.IsEmpty()) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_GRD_IMPORT_BROWSE)->EnableWindow((szFileName.IsEmpty()) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_IMPORT_INSPECT)->EnableWindow((!szFileName.IsEmpty()) ? TRUE : FALSE);
}

void CGRDImportDialog::OnSelchangeSource()
{
	CString  szLayout;

	GetDlgItem(IDC_GRD_IMPORT_DIRECTORY)->GetWindowText(szLayout);
	GetDlgItem(IDC_GRD_IMPORT_ADD)->EnableWindow((SendDlgItemMessage(IDC_GRD_IMPORT_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szLayout) < 0) ? TRUE : FALSE);
}

void CGRDImportDialog::OnSelchangeDestination()
{
	GetDlgItem(IDC_GRD_IMPORT_REMOVE)->EnableWindow();
}

void CGRDImportDialog::OnOK()
{
	INT  nLayout;
	INT  nLayouts;
	CString  szMessage;
	CGRDLayout  cLayout;
	CHourglassCursor  cCursor;

	for (nLayout = 0, nLayouts = (INT)m_pDisplays[2].GetSize(); nLayout < nLayouts; nLayout++)
	{
		if (!cLayout.Copy(m_pDisplays[2].GetAt(nLayout)) || !AddTemporaryGRD(cLayout.GetTitle(), cLayout))
		{
			szMessage.Format(STRING(IDS_GRD_IMPORT_FAILURE), (LPCTSTR)cLayout.GetTitle());
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_ERROR, szMessage);
		}
	}
	CLocaleDialog::OnOK();
}

BOOL CGRDImportDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_GRDIMPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CGRDImportDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_GRDIMPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CGRDExportDialog dialog

IMPLEMENT_DYNCREATE(CGRDExportDialog, CLocaleDialog)

CGRDExportDialog::CGRDExportDialog(CWnd *pParentWnd) : CLocaleDialog(CGRDExportDialog::IDD, pParentWnd)
{
	//{{AFX_DATA_INIT(CGRDExportDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CGRDExportDialog::Initialize()
{
	EnumTemporaryGRDs(m_pDisplays[0]);
	return TRUE;
}

BOOL CGRDExportDialog::EnumDisplays()
{
	INT  nLayout;
	INT  nLayouts;
	CGRDLayout  *pGRDLayout;

	for (nLayout = 0, nLayouts = (INT)m_pDisplays[0].GetSize(); nLayout < nLayouts; nLayout++)
	{
		if ((pGRDLayout = m_pDisplays[0].GetAt(nLayout))) SendDlgItemMessage(IDC_GRD_EXPORT_DIRECTORY, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pGRDLayout->GetTitle());
		continue;
	}
	if (SendDlgItemMessage(IDC_GRD_EXPORT_DIRECTORY, CB_GETCOUNT) > 0)
	{
		SendDlgItemMessage(IDC_GRD_EXPORT_DIRECTORY, CB_SETCURSEL);
		GetDlgItem(IDC_GRD_EXPORT_DIRECTORY_STATIC)->EnableWindow();
		GetDlgItem(IDC_GRD_EXPORT_DIRECTORY)->EnableWindow();
		return TRUE;
	}
	GetDlgItem(IDC_GRD_EXPORT_DIRECTORY_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_EXPORT_DIRECTORY)->EnableWindow(FALSE);
	return FALSE;
}

BOOL CGRDExportDialog::Check(BOOL bModified) CONST
{
	return((GetDlgItem(IDC_GRD_EXPORT_FILENAME)->GetWindowTextLength() > 0 && m_pDisplays[1].GetSize() > 0) ? TRUE : FALSE);
}

void CGRDExportDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGRDExportDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CGRDExportDialog::PostNcDestroy()
{
	m_pDisplays[0].RemoveAll();
	m_pDisplays[1].RemoveAll();
	CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CGRDExportDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CGRDExportDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_GRD_EXPORT_ADD, OnAdd)
	ON_BN_CLICKED(IDC_GRD_EXPORT_ADDALL, OnAddAll)
	ON_BN_CLICKED(IDC_GRD_EXPORT_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_GRD_EXPORT_REMOVEALL, OnRemoveAll)
	ON_BN_CLICKED(IDC_GRD_EXPORT_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_GRD_EXPORT_HELP, OnHelp)
	ON_EN_CHANGE(IDC_GRD_EXPORT_FILENAME, OnEditchangeFileName)
	ON_CBN_SELCHANGE(IDC_GRD_EXPORT_DIRECTORY, OnSelchangeSource)
	ON_LBN_SELCHANGE(IDC_GRD_EXPORT_LIST, OnSelchangeDestination)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDExportDialog message handlers

BOOL CGRDExportDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocaleDialog::OnInitDialog();
	GetDlgItem(IDC_GRD_EXPORT_DETAILS)->EnableWindow();
	GetDlgItem(IDC_GRD_EXPORT_ADD)->EnableWindow((EnumDisplays() && SendDlgItemMessage(IDC_GRD_EXPORT_DIRECTORY, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_EXPORT_ADDALL)->EnableWindow((SendDlgItemMessage(IDC_GRD_EXPORT_DIRECTORY, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_EXPORT_LIST_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_EXPORT_LIST)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_EXPORT_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_EXPORT_REMOVEALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_EXPORT_FILENAME_STATIC)->EnableWindow();
	GetDlgItem(IDC_GRD_EXPORT_FILENAME)->EnableWindow();
	GetDlgItem(IDC_GRD_EXPORT_BROWSE)->EnableWindow();
	GetDlgItem(IDC_GRD_EXPORT_DIRECTORY)->SetFocus();
	return FALSE;
}

void CGRDExportDialog::OnAdd()
{
	INT  nLayout;
	INT  nLayouts;
	CString  szLayout;
	CGRDLayout  *pLayout[2];
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_GRD_EXPORT_DIRECTORY)->GetWindowText(szLayout);
	if (SendDlgItemMessage(IDC_GRD_EXPORT_LIST, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szLayout) >= 0)
	{
		if ((pLayout[0] = m_pDisplays[0].GetAt(m_pDisplays[0].Find(szLayout))))
		{
			if ((pLayout[1] = new CGRDLayout))
			{
				pLayout[1]->Copy(pLayout[0]);
				if (m_pDisplays[1].Add(pLayout[1]) < 0) delete pLayout[1];
			}
		}
		for (nLayout = 0, nLayouts = (INT)SendDlgItemMessage(IDC_GRD_EXPORT_DIRECTORY, CB_GETCOUNT); nLayout < nLayouts; nLayout++)
		{
			if (SendDlgItemMessage(IDC_GRD_EXPORT_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)Combobox_GetText(GetDlgItem(IDC_GRD_EXPORT_DIRECTORY), nLayout)) < 0) break;
			continue;
		}
		SendDlgItemMessage(IDC_GRD_EXPORT_LIST, LB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_GRD_EXPORT_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szLayout));
		GetDlgItem(IDC_GRD_EXPORT_ADD)->EnableWindow(FALSE);
		GetDlgItem(IDC_GRD_EXPORT_ADDALL)->EnableWindow((nLayout < nLayouts) ? TRUE : FALSE);
		GetDlgItem(IDC_GRD_EXPORT_LIST_STATIC)->EnableWindow();
		GetDlgItem(IDC_GRD_EXPORT_LIST)->EnableWindow();
		GetDlgItem(IDC_GRD_EXPORT_REMOVE)->EnableWindow();
		GetDlgItem(IDC_GRD_EXPORT_REMOVEALL)->EnableWindow();
		GetDlgItem(IDC_GRD_EXPORT_DIRECTORY)->SetFocus();
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDExportDialog::OnAddAll()
{
	INT  nLayout;
	INT  nLayouts;
	CString  szLayout;
	CGRDLayout  *pLayout[2];
	CHourglassCursor  cCursor;

	for (nLayout = 0, nLayouts = (INT)SendDlgItemMessage(IDC_GRD_EXPORT_DIRECTORY, CB_GETCOUNT); nLayout < nLayouts; nLayout++)
	{
		if (SendDlgItemMessage(IDC_GRD_EXPORT_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)(szLayout = Combobox_GetText(GetDlgItem(IDC_GRD_EXPORT_DIRECTORY), nLayout))) < 0)
		{
			SendDlgItemMessage(IDC_GRD_EXPORT_LIST, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szLayout);
			continue;
		}
	}
	for (nLayout = 0, nLayouts = (INT)m_pDisplays[0].GetSize(); nLayout < nLayouts; nLayout++)
	{
		if ((pLayout[0] = m_pDisplays[0].GetAt(nLayout)) && m_pDisplays[1].Find(pLayout[0]->GetTitle()) < 0)
		{
			if ((pLayout[1] = new CGRDLayout))
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
	GetDlgItem(IDC_GRD_EXPORT_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_GRD_EXPORT_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_EXPORT_LIST)->EnableWindow((SendDlgItemMessage(IDC_GRD_EXPORT_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_EXPORT_ADD)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_EXPORT_ADDALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_EXPORT_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_GRD_EXPORT_LIST, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_EXPORT_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_GRD_EXPORT_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_EXPORT_DIRECTORY)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDExportDialog::OnRemove()
{
	INT  nIndex;
	CString  szLayout;
	CHourglassCursor  cCursor;

	if ((nIndex = m_pDisplays[1].Find(Listbox_GetText(GetDlgItem(IDC_GRD_EXPORT_LIST), (INT)SendDlgItemMessage(IDC_GRD_EXPORT_LIST, LB_GETCURSEL)))) >= 0)
	{
		delete m_pDisplays[1].GetAt(nIndex);
		m_pDisplays[1].RemoveAt(nIndex);
	}
	if (SendDlgItemMessage(IDC_GRD_EXPORT_LIST, LB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_GRD_EXPORT_LIST, LB_GETCURSEL)) > 0)
	{
		SendDlgItemMessage(IDC_GRD_EXPORT_LIST, LB_SETCURSEL);
		GetDlgItem(IDC_GRD_EXPORT_DIRECTORY)->GetWindowText(szLayout);
		GetDlgItem(IDC_GRD_EXPORT_ADD)->EnableWindow((SendDlgItemMessage(IDC_GRD_EXPORT_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szLayout) < 0) ? TRUE : FALSE);
		GetDlgItem(IDC_GRD_EXPORT_ADDALL)->EnableWindow((SendDlgItemMessage(IDC_GRD_EXPORT_DIRECTORY, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	}
	else
	{
		GetDlgItem(IDC_GRD_EXPORT_LIST_STATIC)->EnableWindow(FALSE);
		GetDlgItem(IDC_GRD_EXPORT_LIST)->EnableWindow(FALSE);
		GetDlgItem(IDC_GRD_EXPORT_ADD)->EnableWindow((SendDlgItemMessage(IDC_GRD_EXPORT_DIRECTORY, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
		GetDlgItem(IDC_GRD_EXPORT_ADDALL)->EnableWindow((SendDlgItemMessage(IDC_GRD_EXPORT_DIRECTORY, CB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_GRD_EXPORT_REMOVE)->EnableWindow(FALSE);
		GetDlgItem(IDC_GRD_EXPORT_REMOVEALL)->EnableWindow(FALSE);
	}
	GetDlgItem(IDC_GRD_EXPORT_DIRECTORY)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDExportDialog::OnRemoveAll()
{
	CHourglassCursor  cCursor;

	m_pDisplays[1].RemoveAll();
	SendDlgItemMessage(IDC_GRD_EXPORT_LIST, LB_RESETCONTENT);
	GetDlgItem(IDC_GRD_EXPORT_LIST_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_EXPORT_LIST)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_EXPORT_ADD)->EnableWindow((SendDlgItemMessage(IDC_GRD_EXPORT_DIRECTORY, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_EXPORT_ADDALL)->EnableWindow((SendDlgItemMessage(IDC_GRD_EXPORT_DIRECTORY, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_EXPORT_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_EXPORT_REMOVEALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_EXPORT_DIRECTORY)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDExportDialog::OnBrowse()
{
	CString  szFileName;
	CFileBrowseDialog  cFileBrowseDialog(this, IDC_GRD_EXPORT_FILENAME, STRING(IDS_FILEBROWSEDIALOG_DATABASEFILEEXTENSION), STRING(IDS_FILEBROWSEDIALOG_DATABASEFILEFILTER));

	if (cFileBrowseDialog.DoModal() == IDOK)
	{
		szFileName = cFileBrowseDialog.GetPathName();
		GetDlgItem(IDC_GRD_EXPORT_FILENAME)->SetWindowText(szFileName);
	}
	SendDlgItemMessage(IDC_GRD_EXPORT_FILENAME, EM_SETSEL, 0, (LPARAM)-1);
	GetDlgItem(IDC_GRD_EXPORT_FILENAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDExportDialog::OnEditchangeFileName()
{
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDExportDialog::OnSelchangeSource()
{
	CString  szLayout;

	GetDlgItem(IDC_GRD_EXPORT_DIRECTORY)->GetWindowText(szLayout);
	GetDlgItem(IDC_GRD_EXPORT_ADD)->EnableWindow((SendDlgItemMessage(IDC_GRD_EXPORT_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szLayout) < 0) ? TRUE : FALSE);
}

void CGRDExportDialog::OnSelchangeDestination()
{
	GetDlgItem(IDC_GRD_EXPORT_REMOVE)->EnableWindow();
}

void CGRDExportDialog::OnOK()
{
	DWORD  cbData;
	CFileEx  cFile;
	CString  szFileName;
	CByteArray  nFileData;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_GRD_EXPORT_FILENAME)->GetWindowText(szFileName);
	if (cFile.Open(szFileName, CFile::modeCreate | CFile::modeReadWrite | CFile::shareExclusive))
	{
		ReportEvent((!WriteFile(cFile.m_hFile, nFileData.GetData(), (m_pDisplays[1].Map(nFileData)) ? (DWORD)nFileData.GetSize() : 0, &cbData, (LPOVERLAPPED)NULL) || !cbData) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_ERROR) : 0, STRING(IDS_GRD_EXPORT_FILE_FAILURE));
		cFile.Close();
	}
	else  ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_ERROR, STRING(IDS_GRD_EXPORT_FILE_FAILURE));
	CLocaleDialog::OnOK();
}

BOOL CGRDExportDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_GRDEXPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CGRDExportDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_GRDEXPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CGRDFindDialog dialog

IMPLEMENT_DYNCREATE(CGRDFindDialog, CDisplayDialog)

CGRDFindDialog::CGRDFindDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CGRDFindDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CGRDFindDialog::Create(CWnd *pParentWnd, INT nType, CGRDLayout &cLayout)
{
	switch ((m_nType = nType))
	{
	case GRD_TYPE_NORMAL:
	{ GetDatabase()->EnumGRDs(m_pLayouts[0], FALSE);
	break;
	}
	case GRD_TYPE_TEMPORARY:
	{ EnumTemporaryGRDs(m_pLayouts[0]);
	break;
	}
	}
	if (CDisplayDialog::Create(pParentWnd, CGRDFindDialog::IDD) == IDOK  &&  m_pLayouts[1].GetSize() == 1)
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

CGRDWnd *CGRDFindDialog::GetParent() CONST
{
	return((CGRDWnd *)CDisplayDialog::GetParent());
}

BOOL CGRDFindDialog::EnumSearchKeys()
{
	SendDlgItemMessage(IDC_GRD_FIND_KEY, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_GRDFINDDIALOG_KEY_PARAMETER));
	SendDlgItemMessage(IDC_GRD_FIND_KEY, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_GRDFINDDIALOG_KEY_DESCRIPTION));
	return((SendDlgItemMessage(IDC_GRD_FIND_KEY, CB_SETCURSEL) >= 0) ? TRUE : FALSE);
}

BOOL CGRDFindDialog::EnumSearchValues()
{
	INT  nItem;
	INT  nItems;
	CString  szKey;
	CString  szValue;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	GetDlgItem(IDC_GRD_FIND_KEY)->GetWindowText(szKey);
	if (szKey == STRING(IDS_GRDFINDDIALOG_KEY_PARAMETER))
	{
		for (nItem = 0, nItems = (INT)GetDatabase()->GetTMParameters()->GetSize(), SendDlgItemMessage(IDC_GRD_FIND_VALUE, CB_RESETCONTENT); nItem < nItems; nItem++)
		{
			if ((pDatabaseTMParameter = (CDatabaseTMParameter *)GetDatabase()->GetTMParameters()->GetAt(nItem)) != (CDatabaseTMParameter *)NULL)
			{
				szValue.Format(STRING(IDS_GRDFINDDIALOG_VALUE_FORMAT), (LPCTSTR)pDatabaseTMParameter->GetTag(), (LPCTSTR)pDatabaseTMParameter->GetDescription());
				SendDlgItemMessage(IDC_GRD_FIND_VALUE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szValue);
			}
		}
	}
	if (szKey == STRING(IDS_GRDFINDDIALOG_KEY_DESCRIPTION))
	{
		for (nItem = 0, nItems = (INT)m_szDescriptions.GetSize(), SendDlgItemMessage(IDC_GRD_FIND_VALUE, CB_RESETCONTENT); nItem < nItems; nItem++)
		{
			SendDlgItemMessage(IDC_GRD_FIND_VALUE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)m_szDescriptions.GetAt(nItem));
			continue;
		}
	}
	return((SendDlgItemMessage(IDC_GRD_FIND_VALUE, CB_GETCOUNT) >= 0) ? TRUE : FALSE);
}

VOID CGRDFindDialog::DoFindByParameter(LPCTSTR pszParameter)
{
	INT  nLayout;
	INT  nLayouts;
	CString  szResult;
	CGRDLayout  *pLayout;

	SendDlgItemMessage(IDC_GRD_FIND_RESULTS, LB_RESETCONTENT);
	for (nLayout = 0, nLayouts = (m_pLayouts[1].Copy(&m_pLayouts[0])) ? (INT)m_pLayouts[1].GetSize() : 0; nLayout < nLayouts; nLayout++)
	{
		if ((pLayout = m_pLayouts[1].GetAt(nLayout)))
		{
			if (pLayout->Find(pszParameter) >= 0)
			{
				if (pLayout->GetTitle().IsEmpty())
				{
					SendDlgItemMessage(IDC_GRD_FIND_RESULTS, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)pLayout->GetName());
					continue;
				}
				szResult.Format(STRING(IDS_GRDFINDDIALOG_RESULT_FORMAT), (LPCTSTR)pLayout->GetName(), (LPCTSTR)pLayout->GetTitle());
				SendDlgItemMessage(IDC_GRD_FIND_RESULTS, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)((m_nType == GRD_TYPE_NORMAL) ? (LPCTSTR)szResult : (LPCTSTR)pLayout->GetTitle()));
			}
		}
	}
	GetDlgItem(IDC_GRD_FIND_RESULTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_GRD_FIND_RESULTS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_FIND_RESULTS)->EnableWindow((SendDlgItemMessage(IDC_GRD_FIND_RESULTS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CGRDFindDialog::DoFindByParameters(CONST CStringArray &szParameters)
{
	INT  nLayout;
	INT  nLayouts;
	INT  nParameter;
	INT  nParameters;
	CString  szResult;
	CGRDLayout  *pLayout[2];

	for (nParameter = 0, nParameters = (m_pLayouts[1].Copy(&m_pLayouts[0])) ? (INT)szParameters.GetSize() : 0; nParameter < nParameters; nParameter += 2)
	{
		for (nLayout = 0, nLayouts = (!nParameter || szParameters.GetAt(nParameter - 1) == STRING(IDS_GRDFINDDIALOG_QUERY_AND)) ? (INT)m_pLayouts[1].GetSize() : -1; nLayout < nLayouts; nLayout++)
		{
			if ((pLayout[0] = m_pLayouts[1].GetAt(nLayout)) && pLayout[0]->Find(szParameters.GetAt(nParameter)) < 0)
			{
				m_pLayouts[1].RemoveAt(nLayout);
				delete pLayout[0];
				nLayouts--;
				nLayout--;
			}
		}
		for (nLayout = 0, nLayouts = (nParameter > 0 && szParameters.GetAt(nParameter - 1) == STRING(IDS_GRDFINDDIALOG_QUERY_OR)) ? (INT)m_pLayouts[0].GetSize() : -1; nLayout < nLayouts; nLayout++)
		{
			if ((pLayout[0] = m_pLayouts[0].GetAt(nLayout)) && pLayout[0]->Find(szParameters.GetAt(nParameter)) >= 0)
			{
				if ((pLayout[1] = (m_pLayouts[1].Find(pLayout[0]->GetName()) < 0) ? new CGRDLayout : (CGRDLayout *)NULL))
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
	for (SendDlgItemMessage(IDC_GRD_FIND_RESULTS, LB_RESETCONTENT); !nParameters; )
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
				SendDlgItemMessage(IDC_GRD_FIND_RESULTS, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)pLayout[0]->GetName());
				continue;
			}
			szResult.Format(STRING(IDS_GRDFINDDIALOG_RESULT_FORMAT), (LPCTSTR)pLayout[0]->GetName(), (LPCTSTR)pLayout[0]->GetTitle());
			SendDlgItemMessage(IDC_GRD_FIND_RESULTS, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)((m_nType == GRD_TYPE_NORMAL) ? (LPCTSTR)szResult : (LPCTSTR)pLayout[0]->GetTitle()));
		}
	}
	GetDlgItem(IDC_GRD_FIND_RESULTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_GRD_FIND_RESULTS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_FIND_RESULTS)->EnableWindow((SendDlgItemMessage(IDC_GRD_FIND_RESULTS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CGRDFindDialog::DoFindByDescription(LPCTSTR pszDescription)
{
	INT  nLayout;
	INT  nLayouts;
	CString  szResult;
	CGRDLayout  *pLayout;

	SendDlgItemMessage(IDC_GRD_FIND_RESULTS, LB_RESETCONTENT);
	for (nLayout = 0, nLayouts = (m_pLayouts[1].Copy(&m_pLayouts[0])) ? (INT)m_pLayouts[1].GetSize() : 0; nLayout < nLayouts; nLayout++)
	{
		if ((pLayout = m_pLayouts[1].GetAt(nLayout)) && pLayout->GetTitle().Find(pszDescription) >= 0)
		{
			szResult.Format(STRING(IDS_GRDFINDDIALOG_RESULT_FORMAT), (LPCTSTR)pLayout->GetName(), (LPCTSTR)pLayout->GetTitle());
			SendDlgItemMessage(IDC_GRD_FIND_RESULTS, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)((m_nType == GRD_TYPE_NORMAL) ? (LPCTSTR)szResult : (LPCTSTR)pLayout->GetTitle()));
		}
	}
	GetDlgItem(IDC_GRD_FIND_RESULTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_GRD_FIND_RESULTS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_FIND_RESULTS)->EnableWindow((SendDlgItemMessage(IDC_GRD_FIND_RESULTS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CGRDFindDialog::DoFindByDescriptions(CONST CStringArray &szDescriptions)
{
	INT  nLayout;
	INT  nLayouts;
	INT  nDescription;
	INT  nDescriptions;
	CString  szResult;
	CGRDLayout  *pLayout[2];

	for (nDescription = 0, nDescriptions = (m_pLayouts[1].Copy(&m_pLayouts[0])) ? (INT)szDescriptions.GetSize() : 0; nDescription < nDescriptions; nDescription += 2)
	{
		for (nLayout = 0, nLayouts = (!nDescription || szDescriptions.GetAt(nDescription - 1) == STRING(IDS_GRDFINDDIALOG_QUERY_AND)) ? (INT)m_pLayouts[1].GetSize() : -1; nLayout < nLayouts; nLayout++)
		{
			if ((pLayout[0] = m_pLayouts[1].GetAt(nLayout)) && pLayout[0]->GetTitle().Find(szDescriptions.GetAt(nDescription)) < 0)
			{
				m_pLayouts[1].RemoveAt(nLayout);
				delete pLayout[0];
				nLayouts--;
				nLayout--;
			}
		}
		for (nLayout = 0, nLayouts = (nDescription > 0 && szDescriptions.GetAt(nDescription - 1) == STRING(IDS_GRDFINDDIALOG_QUERY_OR)) ? (INT)m_pLayouts[0].GetSize() : -1; nLayout < nLayouts; nLayout++)
		{
			if ((pLayout[0] = m_pLayouts[0].GetAt(nLayout)) && pLayout[0]->GetTitle().Find(szDescriptions.GetAt(nDescription)) >= 0)
			{
				if ((pLayout[1] = (m_pLayouts[1].Find(pLayout[0]->GetName()) < 0) ? new CGRDLayout : (CGRDLayout *)NULL))
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
	for (SendDlgItemMessage(IDC_GRD_FIND_RESULTS, LB_RESETCONTENT); !nDescriptions; )
	{
		m_pLayouts[1].RemoveAll();
		break;
	}
	for (nLayout = 0, nLayouts = (INT)m_pLayouts[1].GetSize(); nLayout < nLayouts; nLayout++)
	{
		if ((pLayout[0] = m_pLayouts[1].GetAt(nLayout)) != (CGRDLayout *)NULL)
		{
			szResult.Format(STRING(IDS_GRDFINDDIALOG_RESULT_FORMAT), (LPCTSTR)pLayout[0]->GetName(), (LPCTSTR)pLayout[0]->GetTitle());
			SendDlgItemMessage(IDC_GRD_FIND_RESULTS, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)((m_nType == GRD_TYPE_NORMAL) ? (LPCTSTR)szResult : (LPCTSTR)pLayout[0]->GetTitle()));
		}
	}
	GetDlgItem(IDC_GRD_FIND_RESULTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_GRD_FIND_RESULTS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_FIND_RESULTS)->EnableWindow((SendDlgItemMessage(IDC_GRD_FIND_RESULTS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
}

void CGRDFindDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGRDFindDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGRDFindDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CGRDFindDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_GRD_FIND_SEARCH, OnSearch)
	ON_BN_CLICKED(IDC_GRD_FIND_OPEN, OnOpen)
	ON_BN_CLICKED(IDC_GRD_FIND_HELP, OnHelp)
	ON_CBN_EDITCHANGE(IDC_GRD_FIND_VALUE, OnEditchangeValue)
	ON_CBN_SELCHANGE(IDC_GRD_FIND_KEY, OnSelchangeKey)
	ON_CBN_SELCHANGE(IDC_GRD_FIND_VALUE, OnSelchangeValue)
	ON_LBN_DBLCLK(IDC_GRD_FIND_RESULTS, OnOpen)
	ON_LBN_SELCHANGE(IDC_GRD_FIND_RESULTS, OnSelchangeResult)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDFindDialog message handlers

BOOL CGRDFindDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	if (EnumSearchKeys() && EnumSearchValues())
	{
		GetDlgItem(IDC_GRD_FIND_KEY_STATIC)->EnableWindow();
		GetDlgItem(IDC_GRD_FIND_KEY)->EnableWindow();
		GetDlgItem(IDC_GRD_FIND_VALUE_STATIC)->EnableWindow();
		GetDlgItem(IDC_GRD_FIND_VALUE)->EnableWindow();
	}
	return TRUE;
}

void CGRDFindDialog::OnSearch()
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

	GetDlgItem(IDC_GRD_FIND_KEY)->GetWindowText(szKey);
	GetDlgItem(IDC_GRD_FIND_VALUE)->GetWindowText(szValue);
	if (szKey == STRING(IDS_GRDFINDDIALOG_KEY_PARAMETER))
	{
		if ((nIndex = (INT)SendDlgItemMessage(IDC_GRD_FIND_VALUE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szValue)) >= 0)
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
			if (szValue.GetAt(nPos) != STRINGCHAR(IDS_GRDFINDDIALOG_QUERY_QUOTE))
			{
				nPos = -1;
				break;
			}
			for (nPos = nPos + 1; nPos < szValue.GetLength(); nPos++)
			{
				if (!_istspace(szValue.GetAt(nPos)) && szValue.GetAt(nPos) != STRINGCHAR(IDS_GRDFINDDIALOG_QUERY_QUOTE))
				{
					szParameter += szValue.GetAt(nPos);
					continue;
				}
				break;
			}
			if (szValue.GetAt(nPos) != STRINGCHAR(IDS_GRDFINDDIALOG_QUERY_QUOTE))
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
				if (szValue.GetAt(nPos) == STRINGCHAR(IDS_GRDFINDDIALOG_QUERY_AND) || szValue.GetAt(nPos) == STRINGCHAR(IDS_GRDFINDDIALOG_QUERY_OR))
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
		GetDlgItem(IDC_GRD_FIND_VALUE)->SetFocus();
		CAudioDevice::AlertBySound();
		return;
	}
	if (szKey == STRING(IDS_GRDFINDDIALOG_KEY_DESCRIPTION))
	{
		for (nItem = 0, nItems = (INT)m_szDescriptions.GetSize(); nItem < nItems; nItem++)
		{
			if (m_szDescriptions.GetAt(nItem) == szValue) break;
			continue;
		}
		for (; nItem == nItems; )
		{
			SendDlgItemMessage(IDC_GRD_FIND_VALUE, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szValue);
			m_szDescriptions.Add(szValue);
			break;
		}
		if ((nPos = szValue.Find(STRING(IDS_GRDFINDDIALOG_QUERY_QUOTE))) < 0)
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
			if (szValue.GetAt(nPos) != STRINGCHAR(IDS_GRDFINDDIALOG_QUERY_QUOTE))
			{
				nPos = -1;
				break;
			}
			for (nPos++; nPos < szValue.GetLength(); nPos++)
			{
				if (!_istspace(szValue.GetAt(nPos)) && szValue.GetAt(nPos) != STRINGCHAR(IDS_GRDFINDDIALOG_QUERY_QUOTE))
				{
					szDescription += szValue.GetAt(nPos);
					continue;
				}
				break;
			}
			if (szValue.GetAt(nPos) != STRINGCHAR(IDS_GRDFINDDIALOG_QUERY_QUOTE))
			{
				nPos = -1;
				break;
			}
			for (nPos++, szDescriptions.Add(szDescription); nPos < szValue.GetLength(); nPos++)
			{
				if (!_istspace(szValue.GetAt(nPos))) break;
				continue;
			}
			if (szValue.GetAt(nPos) == STRINGCHAR(IDS_GRDFINDDIALOG_QUERY_AND) || szValue.GetAt(nPos) == STRINGCHAR(IDS_GRDFINDDIALOG_QUERY_OR))
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
		GetDlgItem(IDC_GRD_FIND_VALUE)->SetFocus();
		CAudioDevice::AlertBySound();
		return;
	}
}

void CGRDFindDialog::OnOpen()
{
	INT  nLayout[2];
	INT  nLayouts[2];
	CString  szTitle[2];
	CGRDLayout  *pLayout;
	CHourglassCursor  cCursor;

	for (nLayout[0] = 0, nLayouts[0] = (INT)m_pLayouts[1].GetSize(), szTitle[0] = Listbox_GetText(GetDlgItem(IDC_GRD_FIND_RESULTS), (INT)SendDlgItemMessage(IDC_GRD_FIND_RESULTS, LB_GETCURSEL)); nLayout[0] < nLayouts[0]; nLayout[0]++)
	{
		if ((pLayout = m_pLayouts[1].GetAt(nLayout[0])))
		{
			for (; pLayout->GetTitle().IsEmpty(); )
			{
				szTitle[1] = pLayout->GetName();
				break;
			}
			if (!pLayout->GetTitle().IsEmpty()) szTitle[1].Format(STRING(IDS_GRDFINDDIALOG_RESULT_FORMAT), (LPCTSTR)pLayout->GetName(), (LPCTSTR)pLayout->GetTitle());
			if ((m_nType == GRD_TYPE_NORMAL  &&  szTitle[0] == szTitle[1]) || (m_nType == GRD_TYPE_TEMPORARY  &&  szTitle[0] == pLayout->GetTitle())) break;
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

void CGRDFindDialog::OnSelchangeKey()
{
	EnumSearchValues();
	GetDlgItem(IDC_GRD_FIND_SEARCH)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_FIND_VALUE)->SetFocus();
}

void CGRDFindDialog::OnSelchangeValue()
{
	GetDlgItem(IDC_GRD_FIND_SEARCH)->EnableWindow((SendDlgItemMessage(IDC_GRD_FIND_VALUE, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
}

void CGRDFindDialog::OnSelchangeResult()
{
	GetDlgItem(IDC_GRD_FIND_OPEN)->EnableWindow();
}

void CGRDFindDialog::OnEditchangeValue()
{
	GetDlgItem(IDC_GRD_FIND_SEARCH)->EnableWindow((GetDlgItem(IDC_GRD_FIND_VALUE)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

void CGRDFindDialog::OnOK()
{
	CHourglassCursor  cCursor;

	m_pLayouts[1].RemoveAll();
	CDisplayDialog::OnOK();
}

BOOL CGRDFindDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_GRDFINDDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CGRDFindDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_GRDFINDDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CGRDOpenDialog dialog

IMPLEMENT_DYNCREATE(CGRDOpenDialog, CDisplayDialog)

CGRDOpenDialog::CGRDOpenDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CGRDOpenDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CGRDOpenDialog::Create(CWnd *pParentWnd)
{
	return CDisplayDialog::Create(pParentWnd, CGRDOpenDialog::IDD);
}

BOOL CGRDOpenDialog::Initialize()
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
	ZeroMemory(&m_fntLayoutValues, sizeof(LOGFONT));
	ZeroMemory(&m_fntLayoutAxes, sizeof(LOGFONT));
	return TRUE;
}

CString CGRDOpenDialog::GetTitle() CONST
{
	CString  szTitle;
	CGRDLayout  cGRDLayout;

	if (FindLayout(cGRDLayout) || (GetType() == GRD_TYPE_TEMPORARY  &&  GetLayout(cGRDLayout)))
	{
		szTitle.Format(STRING(IDS_WINDOW_FULLTITLE), STRING(IDS_DISPLAY_TITLE_GRD), (!cGRDLayout.GetTitle().IsEmpty()) ? (LPCTSTR)cGRDLayout.GetTitle() : (LPCTSTR)cGRDLayout.GetName());
		return szTitle;
	}
	return STRING(IDS_DISPLAY_TITLE_GRD);
}

UINT CGRDOpenDialog::GetType() CONST
{
	return((IsDlgButtonChecked(IDC_GRD_OPEN_TYPE_NORMAL) || IsDlgButtonChecked(IDC_GRD_OPEN_TYPE_TEMPORARY)) ? ((IsDlgButtonChecked(IDC_GRD_OPEN_TYPE_NORMAL)) ? GRD_TYPE_NORMAL : GRD_TYPE_TEMPORARY) : -1);
}

UINT CGRDOpenDialog::GetMode() CONST
{
	return((IsDlgButtonChecked(IDC_GRD_OPEN_MODE_REALTIME) || IsDlgButtonChecked(IDC_GRD_OPEN_MODE_HISTORY)) ? (IsDlgButtonChecked(IDC_GRD_OPEN_MODE_REALTIME)*DISPLAY_MODE_REALTIME + IsDlgButtonChecked(IDC_GRD_OPEN_MODE_HISTORY)*DISPLAY_MODE_HISTORY) : -1);
}

BOOL CGRDOpenDialog::GetLayout(CGRDLayout &cLayout) CONST
{
	CString  szTitle;

	if (GetType() == GRD_TYPE_TEMPORARY  &&  !FindLayout(cLayout))
	{
		GetDlgItem(IDC_GRD_OPEN_DISPLAY)->GetWindowText(szTitle);
		cLayout.SetTitle(szTitle);
		cLayout.SetName(szTitle);
		return InitializeLayout(cLayout);
	}
	return((FindLayout(cLayout)) ? InitializeLayout(cLayout) : FALSE);
}
BOOL CGRDOpenDialog::GetLayout(CGRDLayout &cLayout, CUIntArray &nColumns) CONST
{
	INT  nCol;
	INT  nCols;
	UINT  nColumnItem;
	CUIntArray  nColumnItems[2];

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
		for (nCol = 0, nCols = 1, cLayout.GetColumns(nColumnItems[0]); nCol < nColumnItems[0].GetSize(); nCol++)
		{
			if ((nColumnItem = nColumnItems[0].GetAt(nCol)) == (UINT)-1) nColumnItem = GRD_TITLEITEMS_DEFAULT;
			if (nColumnItem & GRD_TITLEITEM_ID) nColumnItems[1].Add(GRD_TITLEITEM_ID);
			if (nColumnItem & GRD_TITLEITEM_DESCRIPTION) nColumnItems[1].Add(GRD_TITLEITEM_DESCRIPTION);
			if (nColumnItem & GRD_TITLEITEM_VALUE) nColumnItems[1].Add(GRD_TITLEITEM_VALUE);
			if (nColumnItem & GRD_TITLEITEM_UNIT) nColumnItems[1].Add(GRD_TITLEITEM_UNIT);
			if (nColumnItem & GRD_TITLEITEM_RANGE) nColumnItems[1].Add(GRD_TITLEITEM_RANGE);
			if (nColumnItem & GRD_TITLEITEM_LINE) nColumnItems[1].Add(GRD_TITLEITEM_LINE);
			if (nColumnItem & GRD_TITLEITEM_CHANGETMUNIT) nColumnItems[1].Add(GRD_TITLEITEM_CHANGETMUNIT);
			if (nColumnItem & GRD_TITLEITEM_CHANGETIME) nColumnItems[1].Add(GRD_TITLEITEM_CHANGETIME);
			if (nColumnItem & GRD_TITLEITEM_UPDATETMUNIT) nColumnItems[1].Add(GRD_TITLEITEM_UPDATETMUNIT);
			if (nColumnItem & GRD_TITLEITEM_UPDATETIME) nColumnItems[1].Add(GRD_TITLEITEM_UPDATETIME);
		}
		for (nCol = (INT)nColumnItems[0].GetSize(); nCol < nCols; nCol++)
		{
			if (GRD_TITLEITEMS_DEFAULT & GRD_TITLEITEM_ID) nColumnItems[1].Add(GRD_TITLEITEM_ID);
			if (GRD_TITLEITEMS_DEFAULT & GRD_TITLEITEM_DESCRIPTION) nColumnItems[1].Add(GRD_TITLEITEM_DESCRIPTION);
			if (GRD_TITLEITEMS_DEFAULT & GRD_TITLEITEM_VALUE) nColumnItems[1].Add(GRD_TITLEITEM_VALUE);
			if (GRD_TITLEITEMS_DEFAULT & GRD_TITLEITEM_UNIT) nColumnItems[1].Add(GRD_TITLEITEM_UNIT);
			if (GRD_TITLEITEMS_DEFAULT & GRD_TITLEITEM_RANGE) nColumnItems[1].Add(GRD_TITLEITEM_RANGE);
			if (GRD_TITLEITEMS_DEFAULT & GRD_TITLEITEM_LINE) nColumnItems[1].Add(GRD_TITLEITEM_LINE);
			if (GRD_TITLEITEMS_DEFAULT & GRD_TITLEITEM_CHANGETMUNIT) nColumnItems[1].Add(GRD_TITLEITEM_CHANGETMUNIT);
			if (GRD_TITLEITEMS_DEFAULT & GRD_TITLEITEM_CHANGETIME) nColumnItems[1].Add(GRD_TITLEITEM_CHANGETIME);
			if (GRD_TITLEITEMS_DEFAULT & GRD_TITLEITEM_UPDATETMUNIT) nColumnItems[1].Add(GRD_TITLEITEM_UPDATETMUNIT);
			if (GRD_TITLEITEMS_DEFAULT & GRD_TITLEITEM_UPDATETIME) nColumnItems[1].Add(GRD_TITLEITEM_UPDATETIME);
		}
		nColumns.Copy(nColumnItems[1]);
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDOpenDialog::GetLayoutColors(CUIntArray &nColors) CONST
{
	if (IsLayoutModified())
	{
		nColors.Copy(m_nLayoutColors);
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDOpenDialog::GetLayoutTitleFont(LPLOGFONT pTitleFont) CONST
{
	if (IsLayoutModified())
	{
		CopyMemory(pTitleFont, &m_fntLayoutTitle, sizeof(LOGFONT));
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDOpenDialog::GetLayoutItemsFont(LPLOGFONT pItemsFont) CONST
{
	if (IsLayoutModified())
	{
		CopyMemory(pItemsFont, &m_fntLayoutItems, sizeof(LOGFONT));
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDOpenDialog::GetLayoutValuesFont(LPLOGFONT pValuesFont) CONST
{
	if (IsLayoutModified())
	{
		CopyMemory(pValuesFont, &m_fntLayoutValues, sizeof(LOGFONT));
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDOpenDialog::GetLayoutAxesFont(LPLOGFONT pAxesFont) CONST
{
	if (IsLayoutModified())
	{
		CopyMemory(pAxesFont, &m_fntLayoutAxes, sizeof(LOGFONT));
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDOpenDialog::GetLayoutInvalidDataMode(BOOL &bEnable) CONST
{
	if (IsLayoutModified())
	{
		bEnable = m_bLayoutInvalidData;
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDOpenDialog::GetLayoutBadDataMode(BOOL &bEnable) CONST
{
	if (IsLayoutModified())
	{
		bEnable = m_bLayoutBadData;
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDOpenDialog::GetLayoutToolTipMode(BOOL &bEnable) CONST
{
	if (IsLayoutModified())
	{
		bEnable = m_bLayoutToolTips;
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDOpenDialog::IsLayoutModified() CONST
{
	LOGFONT  fntSample = { 0 };
	CGRDLayout  cGRDLayout;

	return((!m_cLayout.Compare(&cGRDLayout) || m_nLayoutColumns.GetSize() > 0 || m_nLayoutColors.GetSize() > 0 || memcmp(&m_fntLayoutTitle, &fntSample, sizeof(LOGFONT)) || memcmp(&m_fntLayoutItems, &fntSample, sizeof(LOGFONT)) || memcmp(&m_fntLayoutValues, &fntSample, sizeof(LOGFONT)) || memcmp(&m_fntLayoutAxes, &fntSample, sizeof(LOGFONT)) || m_bLayoutInvalidData || m_bLayoutBadData || m_bLayoutToolTips) ? TRUE : FALSE);
}

BOOL CGRDOpenDialog::GetRetrieveMode(UINT &nMode) CONST
{
	nMode = m_nRetrieveMode;
	return TRUE;
}

BOOL CGRDOpenDialog::GetRetrieveSpeed(UINT &nSpeed) CONST
{
	nSpeed = m_nRetrieveSpeed;
	return((m_nRetrieveMode & GRD_RETRIEVE_AUTOFORWARD) ? TRUE : FALSE);
}

BOOL CGRDOpenDialog::GetRetrieveInterval(CTimeSpan &tInterval) CONST
{
	tInterval = m_tRetrieveInterval;
	return(((m_nRetrieveMode & GRD_RETRIEVE_AUTOFORWARD) || (m_nRetrieveMode & GRD_RETRIEVE_MANUALFORWARD)) ? TRUE : FALSE);
}

BOOL CGRDOpenDialog::GetRetrieveStartTime(CTimeKey &tTimeKey) CONST
{
	tTimeKey = m_tRetrieveStartTime;
	return(((m_nRetrieveMode & GRD_RETRIEVE_AUTOFORWARD) || (m_nRetrieveMode & GRD_RETRIEVE_PSEUDOREALTIME) || (m_nRetrieveMode & GRD_RETRIEVE_MANUALFORWARD)) ? TRUE : FALSE);
}

BOOL CGRDOpenDialog::GetRetrieveStopTime(CTimeKey &tTimeKey) CONST
{
	tTimeKey = m_tRetrieveStopTime;
	return((((m_nRetrieveMode & GRD_RETRIEVE_AUTOFORWARD) || (m_nRetrieveMode & GRD_RETRIEVE_PSEUDOREALTIME) || (m_nRetrieveMode & GRD_RETRIEVE_MANUALFORWARD)) && (m_nRetrieveMode & GRD_RETRIEVE_STOPBYTIME)) ? TRUE : FALSE);
}

BOOL CGRDOpenDialog::GetRetrieveFileName(CString &szFileName) CONST
{
	szFileName = ((m_nRetrieveMode & GRD_RETRIEVE_AUTOFORWARD) || (m_nRetrieveMode & GRD_RETRIEVE_PSEUDOREALTIME) || (m_nRetrieveMode & GRD_RETRIEVE_MANUALFORWARD)) ? (LPCTSTR)m_szRetrieveFileName : EMPTYSTRING;
	return !szFileName.IsEmpty();
}

BOOL CGRDOpenDialog::IsRetrievingModified() CONST
{
	return((m_nRetrieveMode != 0) ? TRUE : FALSE);
}

BOOL CGRDOpenDialog::GetPrintJobs(CGRDPrintJobs &pPrintJobs) CONST
{
	CByteArray  nPrintInfo;

	return((IsPrintingModified()) ? pPrintJobs.Copy(&m_pPrintJobs) : pPrintJobs.Unmap(nPrintInfo));
}

BOOL CGRDOpenDialog::IsPrintingModified() CONST
{
	return((m_pPrintJobs.GetSize() > 0) ? TRUE : FALSE);
}

CGRDWnd *CGRDOpenDialog::GetParent() CONST
{
	return((CGRDWnd *)CDisplayDialog::GetParent());
}

VOID CGRDOpenDialog::EnumLayouts()
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szDisplay;
	CGRDLayout  *pGRDLayout;
	CGRDLayouts  pGRDLayouts;

	for (nDisplay = 0, nDisplays = (IsDlgButtonChecked(IDC_GRD_OPEN_TYPE_NORMAL)) ? GetDatabase()->EnumGRDs(pGRDLayouts) : EnumTemporaryGRDs(pGRDLayouts), SendDlgItemMessage(IDC_GRD_OPEN_DISPLAY, CB_RESETCONTENT); nDisplay < nDisplays; nDisplay++)
	{
		if ((pGRDLayout = pGRDLayouts.GetAt(nDisplay)))
		{
			if (pGRDLayout->GetTitle().IsEmpty())
			{
				SendDlgItemMessage(IDC_GRD_OPEN_DISPLAY, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pGRDLayout->GetName());
				continue;
			}
			szDisplay.Format(STRING(IDS_GRDOPENDIALOG_TITLE), (LPCTSTR)pGRDLayout->GetName(), (LPCTSTR)pGRDLayout->GetTitle());
			SendDlgItemMessage(IDC_GRD_OPEN_DISPLAY, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)((IsDlgButtonChecked(IDC_GRD_OPEN_TYPE_NORMAL)) ? (LPCTSTR)szDisplay : (LPCTSTR)pGRDLayout->GetTitle()));
		}
	}
	GetDlgItem(IDC_GRD_OPEN_REMOVE)->ShowWindow((IsDlgButtonChecked(IDC_GRD_OPEN_TYPE_TEMPORARY)) ? SW_SHOW : SW_HIDE);
	GetDlgItem(IDC_GRD_OPEN_DISPLAY_STATIC)->EnableWindow((IsDlgButtonChecked(IDC_GRD_OPEN_TYPE_TEMPORARY) || SendDlgItemMessage(IDC_GRD_OPEN_DISPLAY, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_OPEN_DISPLAY)->EnableWindow((IsDlgButtonChecked(IDC_GRD_OPEN_TYPE_TEMPORARY) || SendDlgItemMessage(IDC_GRD_OPEN_DISPLAY, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_OPEN_FIND)->EnableWindow((SendDlgItemMessage(IDC_GRD_OPEN_DISPLAY, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_GRD_OPEN_SETTINGS)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_OPEN_REMOVE)->EnableWindow(FALSE);
}

BOOL CGRDOpenDialog::FindLayout() CONST
{
	CGRDLayout  cGRDLayout;

	return FindLayout(cGRDLayout);
}
BOOL CGRDOpenDialog::FindLayout(CGRDLayout &cLayout) CONST
{
	INT  nDisplay;
	INT  nDisplays;
	CString  szDisplay[2];
	CGRDLayout  *pGRDLayout;
	CGRDLayouts  pGRDLayouts;

	for (GetDlgItem(IDC_GRD_OPEN_DISPLAY)->GetWindowText(szDisplay[0]); IsDlgButtonChecked(IDC_GRD_OPEN_TYPE_NORMAL); )
	{
		for (nDisplay = 0, nDisplays = GetDatabase()->EnumGRDs(pGRDLayouts); nDisplay < nDisplays; nDisplay++)
		{
			if (!(pGRDLayout = pGRDLayouts.GetAt(nDisplay)))
			{
				pGRDLayouts.RemoveAt(nDisplay);
				nDisplays--;
				nDisplay--;
				continue;
			}
			szDisplay[1].Format(STRING(IDS_GRDOPENDIALOG_TITLE), (LPCTSTR)pGRDLayout->GetName(), (LPCTSTR)pGRDLayout->GetTitle());
			if (!szDisplay[0].CompareNoCase(szDisplay[1]) || !szDisplay[0].CompareNoCase(pGRDLayout->GetName()) || !szDisplay[0].CompareNoCase(pGRDLayout->GetTitle()))
			{
				if (GetDatabase()->LoadGRD(pGRDLayout->GetName(), cLayout)) break;
				continue;
			}
		}
		return((nDisplay < nDisplays) ? TRUE : FALSE);
	}
	if (IsDlgButtonChecked(IDC_GRD_OPEN_TYPE_TEMPORARY))
	{
		for (nDisplay = 0, nDisplays = EnumTemporaryGRDs(pGRDLayouts); nDisplay < nDisplays; nDisplay++)
		{
			if (!(pGRDLayout = pGRDLayouts.GetAt(nDisplay)))
			{
				pGRDLayouts.RemoveAt(nDisplay);
				nDisplays--;
				nDisplay--;
				continue;
			}
			if (!szDisplay[0].CompareNoCase(pGRDLayout->GetTitle()))
			{
				if (cLayout.Copy(pGRDLayout)) break;
				continue;
			}
		}
		return((nDisplay < nDisplays) ? TRUE : FALSE);
	}
	return FALSE;
}

BOOL CGRDOpenDialog::InitializeLayout(CGRDLayout &cLayout) CONST
{
	if (m_cLayout.GetName() != cLayout.GetName() || cLayout.Copy(&m_cLayout))
	{
		if (cLayout.GetType() != GRDLAYOUT_TYPE_NORMAL  &&  cLayout.GetType() != GRDLAYOUT_TYPE_STRIPCHART  &&  cLayout.GetType() != GRDLAYOUT_TYPE_STACKCHART  &&  cLayout.GetType() != GRDLAYOUT_TYPE_DIAGRAM)
		{
			cLayout.SetType(GRDLAYOUT_TYPE_NORMAL);
			cLayout.SetMode(GRDLAYOUT_MODE_NORMAL | GRDLAYOUT_MODE_OVERWRITE);
			cLayout.SetDuration(SECONDSPERHOUR);
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDOpenDialog::Check(BOOL bModified) CONST
{
	CGRDLayout  cGRDLayout;

	return(((IsDlgButtonChecked(IDC_GRD_OPEN_MODE_REALTIME) || IsDlgButtonChecked(IDC_GRD_OPEN_MODE_HISTORY)) && ((!IsDlgButtonChecked(IDC_GRD_OPEN_TYPE_TEMPORARY) && FindLayout(cGRDLayout)) || (IsDlgButtonChecked(IDC_GRD_OPEN_TYPE_TEMPORARY) && (FindLayout(cGRDLayout) || (GetDlgItem(IDC_GRD_OPEN_DISPLAY)->GetWindowTextLength() > 0 && CheckAccountPrivilege(PRIVILEGE_GRD_TEMPORARYUSE))))) && (IsDlgButtonChecked(IDC_GRD_OPEN_MODE_REALTIME) || IsRetrievingModified())) ? TRUE : FALSE);
}

void CGRDOpenDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGRDOpenDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CGRDOpenDialog::PostNcDestroy()
{
	m_cLayout.RemoveAll();
	m_pPrintJobs.RemoveAll();
	m_nLayoutColors.RemoveAll();
	m_nLayoutColumns.RemoveAll();
	CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CGRDOpenDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CGRDOpenDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_GRD_OPEN_SETTINGS, OnSettings)
	ON_BN_CLICKED(IDC_GRD_OPEN_FIND, OnFind)
	ON_BN_CLICKED(IDC_GRD_OPEN_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_GRD_OPEN_TYPE_NORMAL, OnTypeNormal)
	ON_BN_CLICKED(IDC_GRD_OPEN_TYPE_TEMPORARY, OnTypeTemporary)
	ON_BN_CLICKED(IDC_GRD_OPEN_MODE_REALTIME, OnRealtimeMode)
	ON_BN_CLICKED(IDC_GRD_OPEN_MODE_HISTORY, OnHistoryMode)
	ON_BN_CLICKED(IDC_GRD_OPEN_HELP, OnHelp)
	ON_CBN_EDITCHANGE(IDC_GRD_OPEN_DISPLAY, OnEditchangeTitle)
	ON_CBN_SELCHANGE(IDC_GRD_OPEN_DISPLAY, OnSelchangeTitle)
	ON_CBN_DBLCLK(IDC_GRD_OPEN_DISPLAY, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDOpenDialog message handlers

BOOL CGRDOpenDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	CheckRadioButton(IDC_GRD_OPEN_TYPE_NORMAL, IDC_GRD_OPEN_TYPE_TEMPORARY, IDC_GRD_OPEN_TYPE_NORMAL);
	CheckDlgButton(IDC_GRD_OPEN_MODE_REALTIME, TRUE);
	CheckDlgButton(IDC_GRD_OPEN_MODE_HISTORY, FALSE);
	GetDlgItem(IDC_GRD_OPEN_DETAILS)->EnableWindow();
	GetDlgItem(IDC_GRD_OPEN_TYPE)->EnableWindow();
	GetDlgItem(IDC_GRD_OPEN_TYPE_NORMAL)->EnableWindow();
	GetDlgItem(IDC_GRD_OPEN_TYPE_TEMPORARY)->EnableWindow();
	GetDlgItem(IDC_GRD_OPEN_MODE)->EnableWindow();
	GetDlgItem(IDC_GRD_OPEN_MODE_REALTIME)->EnableWindow();
	GetDlgItem(IDC_GRD_OPEN_MODE_HISTORY)->EnableWindow(CheckAccountPrivilege(PRIVILEGE_OFFLINE_OPERATE));
	EnumLayouts();
	return TRUE;
}

void CGRDOpenDialog::OnSettings()
{
	ReportEvent((m_dlgSettings.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CGRDOpenDialog::OnFind()
{
	INT  nResult;
	CString  szDisplay;
	CGRDLayout  cGRDLayout;

	if ((nResult = m_dlgFindDisplay.Create(this, (IsDlgButtonChecked(IDC_GRD_OPEN_TYPE_NORMAL)) ? GRD_TYPE_NORMAL : ((IsDlgButtonChecked(IDC_GRD_OPEN_TYPE_TEMPORARY)) ? GRD_TYPE_TEMPORARY : 0), cGRDLayout)) == IDOK)
	{
		for (szDisplay.Format(STRING(IDS_GRDOPENDIALOG_TITLE), (LPCTSTR)cGRDLayout.GetName(), (LPCTSTR)cGRDLayout.GetTitle()); cGRDLayout.GetTitle().IsEmpty(); )
		{
			szDisplay = cGRDLayout.GetName();
			break;
		}
		GetDlgItem(IDC_GRD_OPEN_SETTINGS)->EnableWindow((SendDlgItemMessage(IDC_GRD_OPEN_DISPLAY, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_GRD_OPEN_DISPLAY, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)((IsDlgButtonChecked(IDC_GRD_OPEN_TYPE_NORMAL)) ? (LPCTSTR)szDisplay : (LPCTSTR)cGRDLayout.GetTitle()))) >= 0 && (GetMode() != DISPLAY_MODE_REALTIME || !GetParent()->Find(MAKELONG(DISPLAY_TYPE_GRD, GetType()), GetMode(), cGRDLayout.GetName()))) ? (!IsDlgButtonChecked(IDC_GRD_OPEN_TYPE_TEMPORARY) || CheckAccountPrivilege(PRIVILEGE_GRD_TEMPORARYUSE)) : FALSE);
		GetDlgItem(IDC_GRD_OPEN_DISPLAY)->SetFocus();
	}
	ReportEvent((nResult <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDOpenDialog::OnRemove()
{
	CGRDLayout  cGRDLayout;
	CHourglassCursor  cCursor;

	if (FindLayout(cGRDLayout) && RemoveTemporaryGRD(cGRDLayout.GetName()))
	{
		SendDlgItemMessage(IDC_GRD_OPEN_DISPLAY, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_GRD_OPEN_DISPLAY, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)cGRDLayout.GetName()));
		SendDlgItemMessage(IDC_GRD_OPEN_DISPLAY, CB_SETCURSEL, (WPARAM)-1);
	}
	GetDlgItem(IDC_GRD_OPEN_SETTINGS)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_OPEN_REMOVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_GRD_OPEN_DISPLAY)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(FALSE);
}

void CGRDOpenDialog::OnEditchangeTitle()
{
	CGRDLayout  cGRDLayout;

	GetDlgItem(IDC_GRD_OPEN_SETTINGS)->EnableWindow((((!IsDlgButtonChecked(IDC_GRD_OPEN_TYPE_TEMPORARY) && FindLayout(cGRDLayout)) || (IsDlgButtonChecked(IDC_GRD_OPEN_TYPE_TEMPORARY) && (FindLayout(cGRDLayout) || GetDlgItem(IDC_GRD_OPEN_DISPLAY)->GetWindowTextLength() > 0))) && (GetMode() != DISPLAY_MODE_REALTIME || !GetParent()->Find(MAKELONG(DISPLAY_TYPE_GRD, GetType()), GetMode(), cGRDLayout.GetName()))) ? (!IsDlgButtonChecked(IDC_GRD_OPEN_TYPE_TEMPORARY) || CheckAccountPrivilege(PRIVILEGE_GRD_TEMPORARYUSE)) : FALSE);
	GetDlgItem(IDC_GRD_OPEN_REMOVE)->EnableWindow((IsDlgButtonChecked(IDC_GRD_OPEN_TYPE_TEMPORARY) && FindLayout(cGRDLayout)) ? CheckAccountPrivilege(PRIVILEGE_GRD_TEMPORARYUSE) : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDOpenDialog::OnSelchangeTitle()
{
	CGRDLayout  cGRDLayout;

	SendDlgItemMessage(IDC_GRD_OPEN_DISPLAY, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_GRD_OPEN_DISPLAY, CB_GETCURSEL));
	GetDlgItem(IDC_GRD_OPEN_SETTINGS)->EnableWindow((FindLayout(cGRDLayout) && (GetMode() != DISPLAY_MODE_REALTIME || !GetParent()->Find(MAKELONG(DISPLAY_TYPE_GRD, GetType()), GetMode(), cGRDLayout.GetName()))) ? (!IsDlgButtonChecked(IDC_GRD_OPEN_TYPE_TEMPORARY) || CheckAccountPrivilege(PRIVILEGE_GRD_TEMPORARYUSE)) : FALSE);
	GetDlgItem(IDC_GRD_OPEN_REMOVE)->EnableWindow((IsDlgButtonChecked(IDC_GRD_OPEN_TYPE_TEMPORARY)) ? CheckAccountPrivilege(PRIVILEGE_GRD_TEMPORARYUSE) : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDOpenDialog::OnTypeNormal()
{
	EnumLayouts();
	GetDlgItem(IDC_GRD_OPEN_DISPLAY)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDOpenDialog::OnTypeTemporary()
{
	EnumLayouts();
	GetDlgItem(IDC_GRD_OPEN_DISPLAY)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDOpenDialog::OnRealtimeMode()
{
	CGRDLayout  cGRDLayout;

	GetDlgItem(IDC_GRD_OPEN_SETTINGS)->EnableWindow(((FindLayout(cGRDLayout) || IsDlgButtonChecked(IDC_GRD_OPEN_TYPE_TEMPORARY)) && (GetMode() != DISPLAY_MODE_REALTIME || !GetParent()->Find(MAKELONG(DISPLAY_TYPE_GRD, GetType()), GetMode(), cGRDLayout.GetName()))) ? (!IsDlgButtonChecked(IDC_GRD_OPEN_TYPE_TEMPORARY) || CheckAccountPrivilege(PRIVILEGE_GRD_TEMPORARYUSE)) : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CGRDOpenDialog::OnHistoryMode()
{
	INT  nPos;
	CString  szType;
	CString  szTitle;
	CGRDLayout  cGRDLayout;

	if (IsDlgButtonChecked(IDC_GRD_OPEN_TYPE_NORMAL))
	{
		for (szTitle = (FindLayout(cGRDLayout)) ? cGRDLayout.GetTitle() : STRING(IDS_WINDOW_UNKNOWNTITLE), szType.Format(STRING(IDS_GRDOPENDIALOG_TYPENORMAL), (LPCTSTR)cGRDLayout.GetName()), szType = ((nPos = (cGRDLayout.GetName().IsEmpty()) ? szType.Find(SPACE) : -1) >= 0) ? szType.Left(nPos) : szType; IsDlgButtonChecked(IDC_GRD_OPEN_MODE_HISTORY); )
		{
			ReportEvent((m_dlgRetrievals.Create(this, szTitle, szType) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
			break;
		}
		for (GetDlgItem(IDC_GRD_OPEN_SETTINGS)->EnableWindow((FindLayout(cGRDLayout) && (GetMode() != DISPLAY_MODE_REALTIME || !GetParent()->Find(MAKELONG(DISPLAY_TYPE_GRD, GetType()), GetMode(), cGRDLayout.GetName()))) ? TRUE : FALSE); SendDlgItemMessage(IDC_GRD_OPEN_DISPLAY, CB_GETCOUNT) > 0; )
		{
			GetDlgItem(IDC_GRD_OPEN_DISPLAY)->SetFocus();
			break;
		}
		for (; IsDlgButtonChecked(IDC_GRD_OPEN_MODE_REALTIME); )
		{
			GetDlgItem(IDC_GRD_OPEN_MODE_REALTIME)->SetFocus();
			break;
		}
		GetDlgItem(IDOK)->EnableWindow(Check());
		return;
	}
	if (IsDlgButtonChecked(IDC_GRD_OPEN_TYPE_TEMPORARY))
	{
		for (szTitle = (FindLayout(cGRDLayout)) ? cGRDLayout.GetTitle() : STRING(IDS_WINDOW_UNKNOWNTITLE), szType = STRING(IDS_GRDOPENDIALOG_TYPETEMPORARY); IsDlgButtonChecked(IDC_GRD_OPEN_MODE_HISTORY); )
		{
			ReportEvent((m_dlgRetrievals.Create(this, szTitle, szType) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
			break;
		}
		for (GetDlgItem(IDC_GRD_OPEN_SETTINGS)->EnableWindow((GetMode() != DISPLAY_MODE_REALTIME || !GetParent()->Find(MAKELONG(DISPLAY_TYPE_GRD, GetType()), GetMode(), cGRDLayout.GetName())) ? CheckAccountPrivilege(PRIVILEGE_GRD_TEMPORARYUSE) : FALSE); SendDlgItemMessage(IDC_GRD_OPEN_DISPLAY, CB_GETCOUNT) >= 0; )
		{
			GetDlgItem(IDC_GRD_OPEN_DISPLAY)->SetFocus();
			break;
		}
		for (; IsDlgButtonChecked(IDC_GRD_OPEN_MODE_REALTIME); )
		{
			GetDlgItem(IDC_GRD_OPEN_MODE_REALTIME)->SetFocus();
			break;
		}
		GetDlgItem(IDOK)->EnableWindow(Check());
		return;
	}
	CheckDlgButton(IDC_GRD_OPEN_MODE_REALTIME, TRUE);
	CheckDlgButton(IDC_GRD_OPEN_MODE_HISTORY, FALSE);
	for (GetDlgItem(IDC_GRD_OPEN_SETTINGS)->EnableWindow(((FindLayout(cGRDLayout) || IsDlgButtonChecked(IDC_GRD_OPEN_TYPE_TEMPORARY)) && (GetMode() != DISPLAY_MODE_REALTIME || !GetParent()->Find(MAKELONG(DISPLAY_TYPE_GRD, GetType()), GetMode(), cGRDLayout.GetName()))) ? (!IsDlgButtonChecked(IDC_GRD_OPEN_TYPE_TEMPORARY) || CheckAccountPrivilege(PRIVILEGE_GRD_TEMPORARYUSE)) : FALSE); IsDlgButtonChecked(IDC_GRD_OPEN_TYPE_TEMPORARY) || SendDlgItemMessage(IDC_GRD_OPEN_DISPLAY, CB_GETCOUNT) > 0; )
	{
		GetDlgItem(IDC_GRD_OPEN_DISPLAY)->SetFocus();
		break;
	}
	for (; IsDlgButtonChecked(IDC_GRD_OPEN_MODE_REALTIME); )
	{
		GetDlgItem(IDC_GRD_OPEN_MODE_REALTIME)->SetFocus();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

BOOL CGRDOpenDialog::OnCloseSettingsDialog(UINT nCode)
{
	if (nCode == IDOK)
	{
		if (m_dlgSettings.IsLayoutModified())
		{
			m_dlgSettings.GetLayout(m_cLayout, m_nLayoutColumns);
			m_dlgSettings.GetLayoutColors(m_nLayoutColors);
			m_dlgSettings.GetLayoutTitleFont(&m_fntLayoutTitle);
			m_dlgSettings.GetLayoutItemsFont(&m_fntLayoutItems);
			m_dlgSettings.GetLayoutValuesFont(&m_fntLayoutValues);
			m_dlgSettings.GetLayoutAxesFont(&m_fntLayoutAxes);
			m_dlgSettings.GetLayoutInvalidDataMode(m_bLayoutInvalidData);
			m_dlgSettings.GetLayoutBadDataMode(m_bLayoutBadData);
			m_dlgSettings.GetLayoutToolTipMode(m_bLayoutToolTips);
		}
		if (m_dlgSettings.IsRetrievingModified()) m_dlgSettings.GetRetrieveFileName(m_szRetrieveFileName);
		if (m_dlgSettings.IsPrintingModified()) m_dlgSettings.GetPrintJobs(m_pPrintJobs);
	}
	return TRUE;
}

BOOL CGRDOpenDialog::OnCloseRetrieveDialog(UINT nCode)
{
	CGRDLayout  cGRDLayout;

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
		CheckDlgButton(IDC_GRD_OPEN_MODE_REALTIME, TRUE);
		CheckDlgButton(IDC_GRD_OPEN_MODE_HISTORY, FALSE);
	}
	return TRUE;
}

void CGRDOpenDialog::OnOK()
{
	CGRDWnd  *pGRDWnd[2];
	CGRDLayout  cGRDLayout;
	CHourglassCursor  cCursor;

	if ((pGRDWnd[0] = GetParent()))
	{
		if (GetMode() == DISPLAY_MODE_REALTIME)
		{
			if ((pGRDWnd[1] = (FindLayout(cGRDLayout)) ? pGRDWnd[0]->Find(MAKELONG(DISPLAY_TYPE_GRD, GetType()), GetMode(), cGRDLayout.GetName()) : (CGRDWnd *)NULL))
			{
				GetDisplayArea()->ActivateDisplay(pGRDWnd[1]);
				EndDialog(IDCANCEL);
				return;
			}
		}
		if (!pGRDWnd[0]->OnCloseOpenDialog(IDOK))
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

void CGRDOpenDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	GetParent()->OnCloseOpenDialog(IDCANCEL);
	CDisplayDialog::OnCancel();
}

BOOL CGRDOpenDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_GRDOPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CGRDOpenDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_GRDOPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CGRDRetrieveThread

IMPLEMENT_DYNCREATE(CGRDRetrieveThread, CThread)

CGRDRetrieveThread::CGRDRetrieveThread() : CThread()
{
	m_nMode = 0;
	m_nSpeed = 0;
	m_tInterval = 0;
	m_tStartTime = 0;
	m_tStopTime = 0;
	m_pbFlag = (LPLONG)NULL;
	m_bInit[0] = (HANDLE)NULL;
	m_bInit[1] = (HANDLE)NULL;
	m_hAction[GRDRETRIEVETHREAD_ACTION_STOP] = (HANDLE)NULL;
	m_hAction[GRDRETRIEVETHREAD_ACTION_AUTOFORWARD] = (HANDLE)NULL;
	m_hAction[GRDRETRIEVETHREAD_ACTION_MANUALFORWARD] = (HANDLE)NULL;
	m_hAction[GRDRETRIEVETHREAD_ACTION_PSEUDOREALTIME] = (HANDLE)NULL;
}

BOOL CGRDRetrieveThread::Start(CGRDWnd *pParentWnd, HANDLE bInit, HANDLE bContinue, LPCTSTR pszFileName, UINT nMode, UINT nSpeed, CONST CTimeSpan &tInterval, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, LONG *pbFlag, HANDLE bRetrieveStop, HANDLE bRetrieveAutoForward, HANDLE bRetrieveManualForward, HANDLE bRetrievePseudoRealtime)
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
	m_hAction[GRDRETRIEVETHREAD_ACTION_STOP] = bRetrieveStop;
	m_hAction[GRDRETRIEVETHREAD_ACTION_AUTOFORWARD] = bRetrieveAutoForward;
	m_hAction[GRDRETRIEVETHREAD_ACTION_MANUALFORWARD] = bRetrieveManualForward;
	m_hAction[GRDRETRIEVETHREAD_ACTION_PSEUDOREALTIME] = bRetrievePseudoRealtime;
	return((ResetEvent(bInit)) ? CreateThread(pParentWnd, THREAD_PRIORITY_BELOW_NORMAL) : FALSE);
}

BOOL CGRDRetrieveThread::Stop()
{
	return((DestroyThread() >= 0) ? TRUE : FALSE);
}

BOOL CGRDRetrieveThread::InitializeTMData(CTMParameters &pTMParameters, BOOL bBadData)
{
	return m_cTMEnvironment.Initialize(pTMParameters, bBadData);
}

int CGRDRetrieveThread::Run()
{
	UINT  nAction;
	UINT  nResult;
	DWORD  dwResult;
	TIMETAG  tTime;
	CTimeKey  tTimeKey;
	CTimeTag  tTimeTag[2];
	CGRDWnd  *pGRDWnd = (CGRDWnd *)GetThreadInfo();

	StartRetrieving();
	if (m_cTMEnvironment.Create(GetDatabase()))
	{
		if (m_cTMProcessEngine.Open(GetDatabase(), GetAccountSpacecraftName(), GetRetrieveFileName(), &m_cTMEnvironment))
		{
			for (BeginWaitCursor(), pGRDWnd->SetRetrieveMode((m_nMode = m_nMode & ~(GRD_RETRIEVE_STOPPED | GRD_RETRIEVE_RELATIVE))), pGRDWnd->Reset(&m_cTMEnvironment), SignalObjectAndWait(m_bInit[0], m_bInit[1], INFINITE, FALSE), nResult = m_cTMProcessEngine.ProcessTMData(GetDatabase(), &m_cTMEnvironment, (tTimeKey = GetRetrieveStartTime())), nAction = 0; (dwResult = Wait(0)) == WAIT_TIMEOUT && !pGRDWnd->IsInitialized(); )
			{
				SwitchToThread();
				continue;
			}
			for (; dwResult == WAIT_TIMEOUT; BeginWaitCursor())
			{
				if ((GetRetrieveMode() & GRD_RETRIEVE_AUTOFORWARD) && !(GetRetrieveMode() & GRD_RETRIEVE_STOPPED))
				{
					for (; (nResult & HISTORYFILE_SUCCESS) && !(GetRetrieveMode() & GRD_RETRIEVE_RELATIVE) && (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT && ((!(GetRetrieveMode() & GRD_RETRIEVE_EXACTTIME) && !pGRDWnd->Update(tTimeKey, &m_cTMEnvironment, nResult)) || ((GetRetrieveMode() & GRD_RETRIEVE_EXACTTIME) && tTimeKey < GetRetrieveStartTime())); )
					{
						if (!((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, 0)) & HISTORYFILE_SUCCESS)) break;
						if (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS))
						{
							if (GetRetrieveMode() & GRD_RETRIEVE_STOPBYREALTIME)
							{
								pGRDWnd->SetMode(DISPLAY_MODE_REALTIME);
								pGRDWnd->ProcessRealtimeData();
								pGRDWnd->UpdateBars();
								break;
							}
							ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
							pGRDWnd->SetRetrieveMode(pGRDWnd->GetRetrieveMode() | GRD_RETRIEVE_STOPPED);
							pGRDWnd->UpdateBars();
							break;
						}
						if ((GetRetrieveMode() & GRD_RETRIEVE_STOPBYTIME) && GetRetrieveStopTime() < tTimeKey)
						{
							pGRDWnd->SetRetrieveMode(pGRDWnd->GetRetrieveMode() | GRD_RETRIEVE_STOPPED);
							pGRDWnd->UpdateBars();
							break;
						}
					}
					EndWaitCursor();
					if (pGRDWnd->GetMode() != DISPLAY_MODE_REALTIME)
					{
						if ((((nResult & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS))) || (GetRetrieveMode() & GRD_RETRIEVE_RELATIVE)) && (!(GetRetrieveMode() & GRD_RETRIEVE_STOPBYTIME) || GetRetrieveStopTime() >= tTimeKey) && dwResult == WAIT_TIMEOUT)
						{
							if ((!(GetRetrieveMode() & GRD_RETRIEVE_RELATIVE) && (!(GetRetrieveMode() & GRD_RETRIEVE_EXACTTIME) || pGRDWnd->Update(tTimeKey, &m_cTMEnvironment, (nResult = (nResult | HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS) & ~HISTORYFILE_TMUNIT) & (HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS)) || TRUE)) || (GetRetrieveMode() & GRD_RETRIEVE_RELATIVE))
							{
								for (; (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 10 * (10 - GetRetrieveSpeed())*(10 - GetRetrieveSpeed()))) == WAIT_TIMEOUT; )
								{
									if (((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, GetRetrieveInterval())) & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)))
									{
										if (!(GetRetrieveMode() & GRD_RETRIEVE_STOPBYTIME) || GetRetrieveStopTime() >= tTimeKey)
										{
											pGRDWnd->Update(tTimeKey, &m_cTMEnvironment, nResult);
											continue;
										}
									}
									if (nResult & HISTORYFILE_SUCCESS)
									{
										if (GetRetrieveMode() & GRD_RETRIEVE_STOPBYREALTIME)
										{
											pGRDWnd->SetMode(DISPLAY_MODE_REALTIME);
											pGRDWnd->ProcessRealtimeData();
											pGRDWnd->UpdateBars();
											break;
										}
										ReportEvent((GetRetrieveMode() & GRD_RETRIEVE_STOPBYEND) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING : USER_NOERROR);
										pGRDWnd->SetRetrieveMode(pGRDWnd->GetRetrieveMode() | GRD_RETRIEVE_STOPPED);
										pGRDWnd->UpdateBars();
									}
									break;
								}
							}
						}
						if (!(nResult & HISTORYFILE_SUCCESS))
						{
							ReportEvent((nResult == HISTORYFILE_DATA_NONE) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING : ((nResult == HISTORYFILE_OPEN_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_OPEN_FAILURE : ((nResult == HISTORYFILE_WRITE_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_WRITE_FAILURE : ((nResult == HISTORYFILE_READ_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_READ_FAILURE : ((nResult == HISTORYFILE_ERROR) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE : SYSTEM_NOERROR)))));
							pGRDWnd->SetRetrieveMode(pGRDWnd->GetRetrieveMode() | GRD_RETRIEVE_STOPPED);
							pGRDWnd->Reset(&m_cTMEnvironment);
							pGRDWnd->UpdateBars();
							break;
						}
					}
					if (pGRDWnd->GetMode() == DISPLAY_MODE_REALTIME) break;
				}
				if ((GetRetrieveMode() & GRD_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & GRD_RETRIEVE_STOPPED))
				{
					for (; (nResult & HISTORYFILE_SUCCESS) && !(GetRetrieveMode() & GRD_RETRIEVE_RELATIVE) && (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT && ((!(GetRetrieveMode() & GRD_RETRIEVE_EXACTTIME) && !pGRDWnd->Update(tTimeKey, &m_cTMEnvironment, nResult)) || ((GetRetrieveMode() & GRD_RETRIEVE_EXACTTIME) && tTimeKey < GetRetrieveStartTime())); )
					{
						if (!((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, 0)) & HISTORYFILE_SUCCESS)) break;
						if (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS))
						{
							if (GetRetrieveMode() & GRD_RETRIEVE_STOPBYREALTIME)
							{
								pGRDWnd->SetMode(DISPLAY_MODE_REALTIME);
								pGRDWnd->ProcessRealtimeData();
								pGRDWnd->UpdateBars();
								break;
							}
							ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
							pGRDWnd->SetRetrieveMode(pGRDWnd->GetRetrieveMode() | GRD_RETRIEVE_STOPPED);
							pGRDWnd->UpdateBars();
							break;
						}
					}
					EndWaitCursor();
					if (pGRDWnd->GetMode() != DISPLAY_MODE_REALTIME)
					{
						if ((((nResult & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS))) || (GetRetrieveMode() & GRD_RETRIEVE_RELATIVE)) && dwResult == WAIT_TIMEOUT)
						{
							if ((!(GetRetrieveMode() & GRD_RETRIEVE_RELATIVE) && (!(GetRetrieveMode() & GRD_RETRIEVE_EXACTTIME) || pGRDWnd->Update(tTimeKey, &m_cTMEnvironment, (nResult = (nResult | HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS) & ~HISTORYFILE_TMUNIT) & (HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS)) || TRUE)) || (GetRetrieveMode() & GRD_RETRIEVE_RELATIVE))
							{
								for (; (dwResult = (!(GetRetrieveMode() & GRD_RETRIEVE_RELATIVE) || nAction != GRDRETRIEVETHREAD_ACTION_MANUALFORWARD) ? Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, INFINITE) : (WAIT_OBJECT_0 + nAction + 1)) == WAIT_OBJECT_0 + GRDRETRIEVETHREAD_ACTION_MANUALFORWARD + 1; EndWaitCursor())
								{
									for (BeginWaitCursor(TRUE); (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT; )
									{
										if (((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, GetRetrieveInterval())) & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)))
										{
											if (pGRDWnd->Update(tTimeKey, &m_cTMEnvironment, nResult)) break;
											continue;
										}
										if (nResult & HISTORYFILE_SUCCESS)
										{
											if (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS))
											{
												if (GetRetrieveMode() & GRD_RETRIEVE_STOPBYREALTIME)
												{
													pGRDWnd->SetMode(DISPLAY_MODE_REALTIME);
													pGRDWnd->ProcessRealtimeData();
													pGRDWnd->UpdateBars();
													break;
												}
												ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
												pGRDWnd->SetRetrieveMode(pGRDWnd->GetRetrieveMode() | GRD_RETRIEVE_STOPPED);
												pGRDWnd->UpdateBars();
											}
										}
										break;
									}
									if (!(nResult & HISTORYFILE_SUCCESS) || (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS)) || pGRDWnd->GetMode() == DISPLAY_MODE_REALTIME || dwResult == WAIT_OBJECT_0)
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
							pGRDWnd->SetRetrieveMode(pGRDWnd->GetRetrieveMode() | GRD_RETRIEVE_STOPPED);
							pGRDWnd->Reset(&m_cTMEnvironment);
							pGRDWnd->UpdateBars();
							break;
						}
					}
					if (pGRDWnd->GetMode() == DISPLAY_MODE_REALTIME) break;
				}
				if ((GetRetrieveMode() & GRD_RETRIEVE_PSEUDOREALTIME) && !(GetRetrieveMode() & GRD_RETRIEVE_STOPPED))
				{
					for (; (nResult & HISTORYFILE_SUCCESS) && !(GetRetrieveMode() & GRD_RETRIEVE_RELATIVE) && (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT && ((!(GetRetrieveMode() & GRD_RETRIEVE_EXACTTIME) && !pGRDWnd->Update(tTimeKey, &m_cTMEnvironment, nResult)) || ((GetRetrieveMode() & GRD_RETRIEVE_EXACTTIME) && tTimeKey < GetRetrieveStartTime())); )
					{
						if (!((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, 0)) & HISTORYFILE_SUCCESS)) break;
						if (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS))
						{
							if (GetRetrieveMode() & GRD_RETRIEVE_STOPBYREALTIME)
							{
								pGRDWnd->SetMode(DISPLAY_MODE_REALTIME);
								pGRDWnd->ProcessRealtimeData();
								pGRDWnd->UpdateBars();
								break;
							}
							ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
							pGRDWnd->SetRetrieveMode(pGRDWnd->GetRetrieveMode() | GRD_RETRIEVE_STOPPED);
							pGRDWnd->UpdateBars();
							break;
						}
						if ((GetRetrieveMode() & GRD_RETRIEVE_STOPBYTIME) && GetRetrieveStopTime() < tTimeKey)
						{
							pGRDWnd->SetRetrieveMode(pGRDWnd->GetRetrieveMode() | GRD_RETRIEVE_STOPPED);
							pGRDWnd->UpdateBars();
							break;
						}
					}
					EndWaitCursor();
					if (pGRDWnd->GetMode() != DISPLAY_MODE_REALTIME)
					{
						if ((((nResult & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS))) || (GetRetrieveMode() & GRD_RETRIEVE_RELATIVE)) && (!(GetRetrieveMode() & GRD_RETRIEVE_STOPBYTIME) || GetRetrieveStopTime() >= tTimeKey) && dwResult == WAIT_TIMEOUT)
						{
							if ((!(GetRetrieveMode() & GRD_RETRIEVE_RELATIVE) && (!(GetRetrieveMode() & GRD_RETRIEVE_EXACTTIME) || pGRDWnd->Update(tTimeKey, &m_cTMEnvironment, (nResult = (nResult | HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS) & ~HISTORYFILE_TMUNIT) & (HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS)) || TRUE)) || (GetRetrieveMode() & GRD_RETRIEVE_RELATIVE))
							{
								for (tTimeTag[0] = ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)) ? ((nResult & HISTORYFILE_TMUNIT) ? m_cTMEnvironment.GetTMUnit()->GetTimeTag() : CTimeTag(tTimeKey)) : CTimeTag(tTimeKey), tTimeTag[1] = CTimeTag(), tTime = CTimeTag().GetTime(); (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT; tTime = CTimeTag().GetTime())
								{
									if (((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, 0)) & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)))
									{
										if ((dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, (((nResult & HISTORYFILE_TMUNIT) && tTimeTag[1].GetTime() - tTimeTag[0].GetTime() + m_cTMEnvironment.GetTMUnit()->GetTimeTag().GetTime() > tTime) || ((nResult & HISTORYFILE_TMPARAMETERS) && tTimeTag[1].GetTime() - tTimeTag[0].GetTime() + CTimeTag(tTimeKey).GetTime() > tTime)) ? ((nResult & HISTORYFILE_TMUNIT) ? (DWORD)((tTimeTag[1].GetTime() - tTimeTag[0].GetTime() + m_cTMEnvironment.GetTMUnit()->GetTimeTag().GetTime() - tTime) / 1000) : (DWORD)((tTimeTag[1].GetTime() - tTimeTag[0].GetTime() + CTimeTag(tTimeKey).GetTime() - tTime) / 1000)) : 0)) != WAIT_TIMEOUT) break;
										if ((!(GetRetrieveMode() & GRD_RETRIEVE_STOPBYTIME) || GetRetrieveStopTime() >= tTimeKey) && ((nResult & HISTORYFILE_SYNCHRONIZE) || !tTimeTag[0].GetTime()))
										{
											tTimeTag[0] = (nResult & HISTORYFILE_TMUNIT) ? m_cTMEnvironment.GetTMUnit()->GetTimeTag() : CTimeTag(tTimeKey);
											tTimeTag[1] = tTime = CTimeTag().GetTime();
										}
										if (!(GetRetrieveMode() & GRD_RETRIEVE_STOPBYTIME) || GetRetrieveStopTime() >= tTimeKey)
										{
											pGRDWnd->Update(tTimeKey, &m_cTMEnvironment, nResult);
											continue;
										}
									}
									if (nResult & HISTORYFILE_SUCCESS)
									{
										if (GetRetrieveMode() & GRD_RETRIEVE_STOPBYREALTIME)
										{
											pGRDWnd->SetMode(DISPLAY_MODE_REALTIME);
											pGRDWnd->ProcessRealtimeData();
											pGRDWnd->UpdateBars();
											break;
										}
										ReportEvent((GetRetrieveMode() & GRD_RETRIEVE_STOPBYEND) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING : USER_NOERROR);
										pGRDWnd->SetRetrieveMode(pGRDWnd->GetRetrieveMode() | GRD_RETRIEVE_STOPPED);
										pGRDWnd->UpdateBars();
									}
									break;
								}
							}
						}
						if (!(nResult & HISTORYFILE_SUCCESS))
						{
							ReportEvent((nResult == HISTORYFILE_DATA_NONE) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING : ((nResult == HISTORYFILE_OPEN_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_OPEN_FAILURE : ((nResult == HISTORYFILE_WRITE_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_WRITE_FAILURE : ((nResult == HISTORYFILE_READ_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_READ_FAILURE : ((nResult == HISTORYFILE_ERROR) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE : SYSTEM_NOERROR)))));
							pGRDWnd->SetRetrieveMode(pGRDWnd->GetRetrieveMode() | GRD_RETRIEVE_STOPPED);
							pGRDWnd->Reset(&m_cTMEnvironment);
							pGRDWnd->UpdateBars();
							break;
						}
					}
					if (pGRDWnd->GetMode() == DISPLAY_MODE_REALTIME) break;
				}
				if ((GetRetrieveMode() & GRD_RETRIEVE_AUTOFORWARD) || (GetRetrieveMode() & GRD_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & GRD_RETRIEVE_PSEUDOREALTIME))
				{
					while ((dwResult = ((dwResult < WAIT_OBJECT_0 + GRDRETRIEVETHREAD_ACTION_AUTOFORWARD + 1 || dwResult > WAIT_OBJECT_0 + GRDRETRIEVETHREAD_ACTION_PSEUDOREALTIME + 1) && dwResult != WAIT_OBJECT_0) ? Wait(m_hAction, GRDRETRIEVETHREAD_ACTION_TYPES, FALSE, INFINITE, FALSE) : dwResult) == WAIT_OBJECT_0 + GRDRETRIEVETHREAD_ACTION_STOP + 1)
					{
						m_nMode = (GetRetrieveMode() & (GRD_RETRIEVE_STOPBYTIME | GRD_RETRIEVE_STOPBYEND | GRD_RETRIEVE_STOPBYREALTIME)) | GRD_RETRIEVE_STOPPED | GRD_RETRIEVE_RELATIVE;
						m_nMode |= ((GetRetrieveMode() & (GRD_RETRIEVE_STOPBYTIME | GRD_RETRIEVE_STOPBYEND | GRD_RETRIEVE_STOPBYREALTIME)) == 0) ? GRD_RETRIEVE_STOPBYREALTIME : 0;
						pGRDWnd->SetRetrieveMode(m_nMode);
						pGRDWnd->UpdateBars();
					}
					if (dwResult == WAIT_OBJECT_0 + GRDRETRIEVETHREAD_ACTION_AUTOFORWARD + 1)
					{
						m_nMode = (GetRetrieveMode() & (GRD_RETRIEVE_STOPBYTIME | GRD_RETRIEVE_STOPBYEND | GRD_RETRIEVE_STOPBYREALTIME)) | GRD_RETRIEVE_AUTOFORWARD | GRD_RETRIEVE_RELATIVE;
						m_nMode |= ((GetRetrieveMode() & (GRD_RETRIEVE_STOPBYTIME | GRD_RETRIEVE_STOPBYEND | GRD_RETRIEVE_STOPBYREALTIME)) == 0) ? GRD_RETRIEVE_STOPBYREALTIME : 0;
						nAction = GRDRETRIEVETHREAD_ACTION_AUTOFORWARD;
						pGRDWnd->SetRetrieveMode(m_nMode);
						pGRDWnd->UpdateBars();
						dwResult = WAIT_TIMEOUT;
						continue;
					}
					if (dwResult == WAIT_OBJECT_0 + GRDRETRIEVETHREAD_ACTION_MANUALFORWARD + 1)
					{
						m_nMode = (GetRetrieveMode() & (GRD_RETRIEVE_STOPBYTIME | GRD_RETRIEVE_STOPBYEND | GRD_RETRIEVE_STOPBYREALTIME)) | GRD_RETRIEVE_MANUALFORWARD | GRD_RETRIEVE_RELATIVE;
						nAction = GRDRETRIEVETHREAD_ACTION_MANUALFORWARD;
						pGRDWnd->SetRetrieveMode(m_nMode);
						pGRDWnd->UpdateBars();
						dwResult = WAIT_TIMEOUT;
						continue;
					}
					if (dwResult == WAIT_OBJECT_0 + GRDRETRIEVETHREAD_ACTION_PSEUDOREALTIME + 1)
					{
						m_nMode = (GetRetrieveMode() & (GRD_RETRIEVE_STOPBYTIME | GRD_RETRIEVE_STOPBYEND | GRD_RETRIEVE_STOPBYREALTIME)) | GRD_RETRIEVE_PSEUDOREALTIME | GRD_RETRIEVE_RELATIVE;
						m_nMode |= ((GetRetrieveMode() & (GRD_RETRIEVE_STOPBYTIME | GRD_RETRIEVE_STOPBYEND | GRD_RETRIEVE_STOPBYREALTIME)) == 0) ? GRD_RETRIEVE_STOPBYREALTIME : 0;
						nAction = GRDRETRIEVETHREAD_ACTION_PSEUDOREALTIME;
						pGRDWnd->SetRetrieveMode(m_nMode);
						pGRDWnd->UpdateBars();
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

VOID CGRDRetrieveThread::StartRetrieving()
{
	InterlockedExchange(m_pbFlag, TRUE);
}

VOID CGRDRetrieveThread::StopRetrieving()
{
	InterlockedExchange(m_pbFlag, FALSE);
}

UINT CGRDRetrieveThread::GetRetrieveMode() CONST
{
	return((IsThreadActive()) ? m_nMode : 0);
}

UINT CGRDRetrieveThread::GetRetrieveSpeed() CONST
{
	return((IsThreadActive()) ? m_nSpeed : 0);
}

CTimeSpan CGRDRetrieveThread::GetRetrieveInterval() CONST
{
	return((IsThreadActive()) ? m_tInterval.GetTotalSeconds() : 0);
}

CTimeKey CGRDRetrieveThread::GetRetrieveStartTime() CONST
{
	return((IsThreadActive()) ? m_tStartTime : 0);
}

CTimeKey CGRDRetrieveThread::GetRetrieveStopTime() CONST
{
	return((IsThreadActive()) ? m_tStopTime : 0);
}

CString CGRDRetrieveThread::GetRetrieveFileName() CONST
{
	return((IsThreadActive()) ? (LPCTSTR)m_szFileName : EMPTYSTRING);
}

VOID CGRDRetrieveThread::BeginWaitCursor(BOOL bForced)
{
	POINT  ptCursor;
	CGRDWnd  *pGRDWnd;
	CHourglassCursor  cCursor;

	for (GetCursorPos(&ptCursor), InterlockedExchange(m_pbFlag, MAKELONG(TRUE, ((m_nMode & GRD_RETRIEVE_RELATIVE) != GRD_RETRIEVE_RELATIVE || bForced) ? TRUE : FALSE)), SetCursorPos(ptCursor.x, ptCursor.y); (pGRDWnd = (CGRDWnd *)GetThreadInfo()); )
	{
		pGRDWnd->UpdateBars();
		break;
	}
}

VOID CGRDRetrieveThread::EndWaitCursor()
{
	POINT  ptCursor;
	CGRDWnd  *pGRDWnd;
	CHourglassCursor  cCursor;

	for (GetCursorPos(&ptCursor), InterlockedExchange(m_pbFlag, LOWORD(*m_pbFlag)), SetCursorPos(ptCursor.x, ptCursor.y); (pGRDWnd = (CGRDWnd *)GetThreadInfo()); )
	{
		pGRDWnd->UpdateBars();
		break;
	}
}

BEGIN_MESSAGE_MAP(CGRDRetrieveThread, CThread)
	//{{AFX_MSG_MAP(CGRDRetrieveThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDRetrieveThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CGRDPrintThread

IMPLEMENT_DYNCREATE(CGRDPrintThread, CThread)

BOOL CGRDPrintThread::Start(CGRDWnd *pParentWnd)
{
	return CreateThread(pParentWnd);
}

BOOL CGRDPrintThread::Stop()
{
	return((DestroyThread() >= 0) ? TRUE : FALSE);
}

BOOL CGRDPrintThread::SetPrintJobs(CONST CGRDPrintJobs &pPrintJobs)
{
	INT  nJob[2][2];
	INT  nJobs[2][2];
	CGRDPrintJobInfo  *pJobInfo;
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
			if ((pJobInfo = new CGRDPrintJobInfo))
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

BOOL CGRDPrintThread::GetPrintJobs(CGRDPrintJobs &pPrintJobs) CONST
{
	CByteArray  nPrintInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(((m_pPrintJobs.GetSize() > 0 && pPrintJobs.Copy(&m_pPrintJobs)) || pPrintJobs.Unmap(nPrintInfo)) ? TRUE : FALSE);
}

int CGRDPrintThread::Run()
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
	CGRDPrintJobInfo  *pJobInfo[2];
	CGRDWnd  *pGRDWnd = (CGRDWnd *)GetThreadInfo();

	for (dwJobResult = 0; Lock(); )
	{
		if (dwJobResult == WAIT_OBJECT_0 + 1 || !dwJobResult)
		{
			for (nJob = 0, nJobs = (INT)m_pPrintJobs.GetSize(); nJob < nJobs; nJob++)
			{
				if ((pJobInfo[0] = m_pPrintJobs.GetAt(nJob)) && (pJobInfo[0]->GetPrintMode() & GRD_PRINT_ACTIVE))
				{
					if (pJobInfo[0]->GetPrintAtDailyTime(tJobDailyTime) || pJobInfo[0]->GetPrintAtDailyTime(tJobDailyTime, nJobStopCount) || pJobInfo[0]->GetPrintAtDailyTime(tJobDailyTime, tJobStopTime))
					{
						pJobInfo[0]->SetPrintLastDailyTime(((tJobTime = CTime::GetCurrentTime().GetTime()).GetTime() % SECONDSPERDAY >= tJobDailyTime.GetTotalSeconds()) ? ((SECONDSPERDAY*(tJobTime.GetTime() / SECONDSPERDAY)) + tJobDailyTime.GetTotalSeconds()) : ((SECONDSPERDAY*(tJobTime.GetTime() / SECONDSPERDAY - 1)) + tJobDailyTime.GetTotalSeconds()));
						continue;
					}
				}
			}
		}
		if ((pJobInfo[0] = ((tJobInterval = m_pPrintJobs.Schedule()) == 0) ? m_pPrintJobs.GetAt(0) : (CGRDPrintJobInfo *)NULL))
		{
			for (bJobPrint = pGRDWnd->Print(pJobInfo[0]); (pJobInfo[0]->GetPrintMode() & GRD_PRINT_CLEARCOMMENTS) && bJobPrint; )
			{
				for (nJob = 1, nJobs = (INT)m_pPrintJobs.GetSize(); nJob < nJobs; nJob++)
				{
					if ((pJobInfo[1] = m_pPrintJobs.GetAt(nJob)))
					{
						if (pJobInfo[0]->GetName() == pJobInfo[1]->GetName())
						{
							pJobInfo[1]->SetPrintMode(pJobInfo[0]->GetPrintMode() & ~GRD_PRINT_CLEARCOMMENTS);
							pJobInfo[1]->SetComments(EMPTYSTRING);
							break;
						}
					}
				}
				break;
			}
			ReportEvent((!bJobPrint) ? SYSTEM_WARNING_GRD_PRINT_FAILURE : SYSTEM_NOERROR);
			m_pPrintJobs.RemoveAt(0);
			delete pJobInfo[0];
		}
		Unlock();
		if ((dwJobResult = Wait(m_cEvent, FALSE, (tJobInterval >= 0) ? (DWORD)(1000 * min(tJobInterval, SECONDSPERDAY)) : INFINITE)) != WAIT_TIMEOUT  &&  dwJobResult != WAIT_OBJECT_0 + 1) break;
	}
	return 0;
}

BEGIN_MESSAGE_MAP(CGRDPrintThread, CThread)
	//{{AFX_MSG_MAP(CGRDPrintThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDPrintThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CGRDToolBar

IMPLEMENT_DYNCREATE(CGRDToolBar, CDisplayToolBar)

CGRDToolBar::CGRDToolBar() : CDisplayToolBar()
{
	return;
}

BEGIN_MESSAGE_MAP(CGRDToolBar, CDisplayToolBar)
	//{{AFX_MSG_MAP(CGRDToolBar)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDToolBar message handlers


/////////////////////////////////////////////////////////////////////////////
// CGRDStatusBar

IMPLEMENT_DYNCREATE(CGRDStatusBar, CDisplayStatusBar)

CGRDStatusBar::CGRDStatusBar() : CDisplayStatusBar()
{
	return;
}

BOOL CGRDStatusBar::SetIndicators(CONST UINT *pPanesID, INT nCount)
{
	INT  nIndex;
	CRect  rPane;
	CString  szPane;
	CToolInfo  cToolInfo;
	CDisplayLock  cLock(this);

	if (CDisplayStatusBar::SetIndicators(pPanesID, nCount))
	{
		if (CommandToIndex(ID_GRD_STATUSBAR_MESSAGEPANE) >= 0)
		{
			szPane.Format(STRING(IDS_GRD_STATUSBAR_UPDATEMESSAGE), (LPCTSTR)CTimeTag().FormatGmt(), (LPCTSTR)CString(CTimeTag().FormatGmt().Right(1), GetDatabase()->GetTMPacketTagLength()), -1, STRING(IDS_GRD_STATUSBAR_QUALITYGOOD));
			SetPaneInfo(CommandToIndex(ID_GRD_STATUSBAR_MESSAGEPANE), ID_GRD_STATUSBAR_MESSAGEPANE, SBPS_NOBORDERS | SBPS_STRETCH, CalcPaneWidth(szPane + STRING(IDS_GRD_STATUSBAR_TIMECORRELATIONFLAG)));
		}
		if (!IsWindow(m_wndToolTip.GetSafeHwnd()))
		{
			m_wndToolTip.Create(this, TTS_ALWAYSTIP | TTS_NOPREFIX | TTS_BALLOON);
			SetClassLongPtr(m_wndToolTip.GetSafeHwnd(), GCL_STYLE, GetClassLongPtr(m_wndToolTip.GetSafeHwnd(), GCL_STYLE) | CS_DROPSHADOW);
		}
		if (IsWindow(m_wndToolTip.GetSafeHwnd()))
		{
			if ((nIndex = CommandToIndex(ID_GRD_STATUSBAR_MODEPANE)) >= 0)
			{
				for (GetItemRect(nIndex, rPane); !m_wndToolTip.GetToolInfo(cToolInfo, this, ID_GRD_STATUSBAR_MODEPANE); )
				{
					m_wndToolTip.AddTool(this, LPSTR_TEXTCALLBACK, rPane, ID_GRD_STATUSBAR_MODEPANE);
					break;
				}
			}
			if ((nIndex = CommandToIndex(ID_GRD_STATUSBAR_TYPEPANE)) >= 0)
			{
				for (GetItemRect(nIndex, rPane); !m_wndToolTip.GetToolInfo(cToolInfo, this, ID_GRD_STATUSBAR_TYPEPANE); )
				{
					m_wndToolTip.AddTool(this, LPSTR_TEXTCALLBACK, rPane, ID_GRD_STATUSBAR_TYPEPANE);
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

CGRDWnd *CGRDStatusBar::GetParent() CONST
{
	return((CGRDWnd *)CDisplayStatusBar::GetParent());
}

BEGIN_MESSAGE_MAP(CGRDStatusBar, CDisplayStatusBar)
	//{{AFX_MSG_MAP(CGRDStatusBar)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipNotify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDStatusBar message handlers

void CGRDStatusBar::OnPaint()
{
	INT  nIndex;
	RECT  rPane;
	CToolInfo  cToolInfo;

	for (CDisplayStatusBar::OnPaint(); IsWindow(m_wndToolTip.GetSafeHwnd()); )
	{
		if ((nIndex = CommandToIndex(ID_GRD_STATUSBAR_MODEPANE)) >= 0 && nIndex < m_prPanes.GetSize())
		{
			for (m_wndToolTip.GetToolInfo(cToolInfo, this, ID_GRD_STATUSBAR_MODEPANE), CopyMemory(&rPane, m_prPanes.GetAt(nIndex), sizeof(RECT)); !EqualRect(&cToolInfo.rect, &rPane); )
			{
				SetRect(&cToolInfo.rect, rPane.left, rPane.top, rPane.right, rPane.bottom);
				m_wndToolTip.SetToolInfo(&cToolInfo);
				break;
			}
		}
		if ((nIndex = CommandToIndex(ID_GRD_STATUSBAR_TYPEPANE)) >= 0 && nIndex < m_prPanes.GetSize())
		{
			for (m_wndToolTip.GetToolInfo(cToolInfo, this, ID_GRD_STATUSBAR_TYPEPANE), CopyMemory(&rPane, m_prPanes.GetAt(nIndex), sizeof(RECT)); !EqualRect(&cToolInfo.rect, &rPane); )
			{
				SetRect(&cToolInfo.rect, rPane.left, rPane.top, rPane.right, rPane.bottom);
				m_wndToolTip.SetToolInfo(&cToolInfo);
				break;
			}
		}
		break;
	}
}

void CGRDStatusBar::OnMouseMove(UINT nFlags, CPoint point)
{
	MSG  sMsg;

	if (IsWindow(m_wndToolTip.GetSafeHwnd()))
	{
		CopyMemory(&sMsg, GetCurrentMessage(), sizeof(MSG));
		m_wndToolTip.RelayEvent(&sMsg);
	}
	CDisplayStatusBar::OnMouseMove(nFlags, point);
}

BOOL CGRDStatusBar::OnToolTipNotify(UINT nID, NMHDR *pNotifyInfo, LRESULT *pResult)
{
	TOOLTIPTEXT  *pToolTipInfo = (TOOLTIPTEXT *)pNotifyInfo;

	switch (pNotifyInfo->idFrom)
	{
	case ID_GRD_STATUSBAR_MODEPANE:
	{ pToolTipInfo->lpszText = (LPTSTR)STRING(IDS_GRD_STATUSBAR_MODEPANE);
	return TRUE;
	}
	case ID_GRD_STATUSBAR_TYPEPANE:
	{ pToolTipInfo->lpszText = (LPTSTR)STRING(IDS_GRD_STATUSBAR_TYPEPANE);
	return TRUE;
	}
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CGRDToolTip

IMPLEMENT_DYNCREATE(CGRDToolTip, CDisplayToolTip)

CGRDToolTip::CGRDToolTip() : CDisplayToolTip()
{
	return;
}

BEGIN_MESSAGE_MAP(CGRDToolTip, CDisplayToolTip)
	//{{AFX_MSG_MAP(CGRDToolTip)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDToolTip message handlers


/////////////////////////////////////////////////////////////////////////////
// CGRDRulerTimeTip

IMPLEMENT_DYNCREATE(CGRDRulerTimeTip, CWnd)

CGRDRulerTimeTip::CGRDRulerTimeTip() : CWnd()
{
	CFontTools  cFontTools(&m_cFont);
}

BOOL CGRDRulerTimeTip::Create(CWnd *pParentWnd)
{
	return CWnd::CreateEx(WS_EX_TOPMOST, AfxRegisterWndClass(CS_SAVEBITS | CS_DROPSHADOW | CS_NOCLOSE, (HCURSOR)(DWORD_PTR)GetClassLongPtr(GetSafeHwnd(), GCLP_HCURSOR)), EMPTYSTRING, WS_POPUP | WS_BORDER, 0, 0, 0, 0, pParentWnd->GetSafeHwnd(), (HMENU)NULL);
}

BOOL CGRDRulerTimeTip::Destroy()
{
	if (IsWindow(GetSafeHwnd()))
	{
		DestroyWindow();
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDRulerTimeTip::SetFont(CFont *pFont)
{
	LOGFONT  lfFont;

	return((pFont->GetLogFont(&lfFont) && ((!m_cFont.GetSafeHandle() || m_cFont.DeleteObject()) && m_cFont.CreateFontIndirect(&lfFont))) ? TRUE : FALSE);
}

BOOL CGRDRulerTimeTip::GetFont(CFont *pFont) CONST
{
	LOGFONT  lfFont;

	return((m_cFont.GetObject(sizeof(LOGFONT), &lfFont) > 0 && pFont->CreateFontIndirect(&lfFont)) ? TRUE : FALSE);
}

VOID CGRDRulerTimeTip::SetTabstops(CONST CUIntArray &nTabs)
{
	m_nTabs.Copy(nTabs);
}

INT CGRDRulerTimeTip::GetTabstops(CUIntArray &nTabs) CONST
{
	nTabs.Copy(m_nTabs);
	return((INT)nTabs.GetSize());
}

VOID CGRDRulerTimeTip::SetRange(LPCTSTR pszRange)
{
	m_szRange = pszRange;
}

CString CGRDRulerTimeTip::GetRange() CONST
{
	return m_szRange;
}

VOID CGRDRulerTimeTip::SetDuration(LPCTSTR pszDuration)
{
	m_szDuration = pszDuration;
}

CString CGRDRulerTimeTip::GetDuration() CONST
{
	return m_szDuration;
}

VOID CGRDRulerTimeTip::Update(CONST POINT &point, LPCTSTR pszRange, LPCTSTR pszDuration)
{
	CRect  rToolTip;
	CSize  sizeToolTip;
	CPoint  ptText[2];

	if (IsWindow(GetSafeHwnd()))
	{
		if (GetRange() != pszRange || GetDuration() != pszDuration)
		{
			for (SetRange(pszRange), SetDuration(pszDuration), sizeToolTip = CalcExtent(pszRange, pszDuration, ptText[0], ptText[1]); TRUE; )
			{
				for (MoveWindow(point.x - sizeToolTip.cx / 2, point.y - (5 * sizeToolTip.cy) / 4, sizeToolTip.cx, sizeToolTip.cy); !IsWindowVisible(); )
				{
					ShowWindow(SW_SHOWNA);
					break;
				}
				Invalidate(FALSE);
				UpdateWindow();
				return;
			}
		}
		for (GetWindowRect(rToolTip); rToolTip.CenterPoint() != point; )
		{
			MoveWindow(point.x - rToolTip.Width() / 2, rToolTip.top, rToolTip.Width(), rToolTip.Height());
			return;
		}
	}
}

CSize CGRDRulerTimeTip::CalcExtent(LPCTSTR pszRange, LPCTSTR pszDuration, CPoint &ptRange, CPoint &ptDuration)
{
	CDC  *pDC;
	INT  nPos;
	CRect  rRange;
	CRect  rDuration;
	CSize  sizeDuration;
	CSize  sizeMargin[2];
	CFont  cFont[1];
	CFont  *pOldFont;
	CString  szRange;
	CString  szDuration;
	CUIntArray  nTabs;
	TEXTMETRIC  tmFont;

	if ((pDC = GetDC()))
	{
		GetTabstops(nTabs);
		rRange.SetRectEmpty();
		rDuration.SetRectEmpty();
		sizeMargin[0].cx = sizeMargin[0].cy = 0;
		sizeMargin[1].cx = sizeMargin[1].cy = 0;
		if (lstrlen(pszRange) > 0 || lstrlen(pszDuration) > 0)
		{
			if ((pOldFont = (GetFont(&cFont[0])) ? pDC->SelectObject(&cFont[0]) : (CFont *)NULL))
			{
				if (pDC->GetTextMetrics(&tmFont) > 0)
				{
					for (szRange = pszRange; !szRange.IsEmpty(); )
					{
						if ((nPos = szRange.Find(EOL)) >= 0)
						{
							sizeDuration = pDC->GetTabbedTextExtent(szRange.Left(nPos), (INT)nTabs.GetSize(), (LPINT)nTabs.GetData());
							rRange.right = max(sizeDuration.cx, rRange.right);
							rRange.bottom += tmFont.tmHeight;
							szRange = szRange.Mid(nPos + 1);
							continue;
						}
						sizeDuration = pDC->GetTabbedTextExtent(szRange, (INT)nTabs.GetSize(), (LPINT)nTabs.GetData());
						rRange.right = max(sizeDuration.cx, rRange.right);
						rRange.bottom += tmFont.tmHeight;
						break;
					}
					sizeMargin[0].cx = tmFont.tmAveCharWidth / 2;
					sizeMargin[0].cy = tmFont.tmAveCharWidth / 4;
					for (szDuration = pszDuration; !szDuration.IsEmpty(); )
					{
						if ((nPos = szDuration.Find(EOL)) >= 0)
						{
							sizeDuration = pDC->GetTabbedTextExtent(szDuration.Left(nPos), (INT)nTabs.GetSize(), (LPINT)nTabs.GetData());
							rDuration.right = max(sizeDuration.cx, rDuration.right);
							rDuration.bottom += tmFont.tmHeight;
							szDuration = szDuration.Mid(nPos + 1);
							continue;
						}
						sizeDuration = pDC->GetTabbedTextExtent(szDuration, (INT)nTabs.GetSize(), (LPINT)nTabs.GetData());
						rDuration.right = max(sizeDuration.cx, rDuration.right);
						rDuration.bottom += tmFont.tmHeight;
						break;
					}
					sizeMargin[1].cx = tmFont.tmAveCharWidth / 2;
					sizeMargin[1].cy = tmFont.tmAveCharWidth / 4;
				}
				pDC->SelectObject(pOldFont);
			}
			ptRange.x = max(sizeMargin[0].cx, sizeMargin[1].cx);
			ptRange.y = max(sizeMargin[0].cy, sizeMargin[1].cy);
			ptDuration.x = ptRange.x;
			ptDuration.y = ptRange.y;
			ptDuration.y += rRange.Height();
			ReleaseDC(pDC);
			return CSize(max(rRange.Width(), rDuration.Width()) + 2 * (ptRange.x + 1), rRange.Height() + rDuration.Height() + 2 * (ptRange.y + 1));
		}
		ReleaseDC(pDC);
	}
	return CSize(0, 0);
}

VOID CGRDRulerTimeTip::CalcTabstops(LPCTSTR pszRange, LPCTSTR pszDuration)
{
	CDC  *pDC;
	INT  nPos[2];
	CFont  cFont;
	CFont  *pOldFont;
	CString  szTabstop[2];
	CUIntArray  nTabs;
	TEXTMETRIC  tmFont;

	if ((pDC = GetDC()))
	{
		if ((pOldFont = ((GetFont(&cFont))) ? pDC->SelectObject(&cFont) : (CFont *)NULL))
		{
			for (nPos[0] = CString(pszRange).Find(TAB); nPos[0] >= 0; szTabstop[0] = CString(pszRange).GetAt(nPos[0]--) + szTabstop[0])
			{
				if (CString(pszRange).GetAt(nPos[0]) != EOL) continue;
				break;
			}
			for (nPos[1] = CString(pszDuration).Find(TAB); nPos[1] >= 0; szTabstop[1] = CString(pszDuration).GetAt(nPos[1]--) + szTabstop[1])
			{
				if (CString(pszDuration).GetAt(nPos[1]) != EOL) continue;
				break;
			}
			if (!szTabstop[0].IsEmpty() || !szTabstop[1].IsEmpty())
			{
				nTabs.SetAtGrow(0, max(pDC->GetTextExtent(szTabstop[0]).cx, pDC->GetTextExtent(szTabstop[1]).cx) + 1);
				SetTabstops(nTabs);
			}
			if (!GetTabstops(nTabs))
			{
				if (pDC->GetTextMetrics(&tmFont))
				{
					nTabs.SetAtGrow(0, tmFont.tmMaxCharWidth);
					SetTabstops(nTabs);
				}
			}
			pDC->SelectObject(pOldFont);
		}
		ReleaseDC(pDC);
	}
}

VOID CGRDRulerTimeTip::DrawContent(CDC *pDC)
{
	INT  nPos;
	INT  nBkgndMode;
	CRect  rToolTip;
	CSize  sizeToolTip;
	CSize  sizeToolText;
	CFont  cFont[1];
	CFont  *pOldFont;
	CPoint  ptRange;
	CPoint  ptDuration;
	CBrush  cBkgndBrush;
	CString  szRange;
	CString  szDuration;
	COLORREF  nOldColor;
	TEXTMETRIC  tmFont;
	CUIntArray  nTabs;

	GetTabstops(nTabs);
	GetWindowRect(rToolTip);
	sizeToolTip = CalcExtent(GetRange(), GetDuration(), ptRange, ptDuration);
	if (cBkgndBrush.CreateSysColorBrush(COLOR_INFOBK))
	{
		nBkgndMode = pDC->SetBkMode(TRANSPARENT);
		nOldColor = pDC->SetTextColor(GetSysColor(COLOR_INFOTEXT));
		if ((pOldFont = (GetFont(&cFont[0])) ? pDC->SelectObject(&cFont[0]) : (CFont *)NULL))
		{
			for (szRange = GetRange(); !szRange.IsEmpty(); )
			{
				if ((nPos = szRange.Find(EOL)) >= 0)
				{
					if (pDC->GetTextMetrics(&tmFont))
					{
						sizeToolText = pDC->GetTextExtent(szRange.Left(nPos));
						pDC->FillRect(CRect(ptRange.x, ptRange.y, rToolTip.Width(), ptRange.y + sizeToolText.cy), &cBkgndBrush);
						pDC->TabbedTextOut(ptRange.x, ptRange.y, szRange.Left(nPos), (INT)nTabs.GetSize(), (LPINT)nTabs.GetData(), 0);
						szRange = szRange.Mid(nPos + 1);
						ptRange.y += tmFont.tmHeight;
					}
					continue;
				}
				sizeToolText = pDC->GetTextExtent(szRange);
				pDC->FillRect(CRect(ptRange.x, ptRange.y, rToolTip.Width(), ptRange.y + sizeToolText.cy), &cBkgndBrush);
				pDC->TabbedTextOut(ptRange.x, ptRange.y, szRange, (INT)nTabs.GetSize(), (LPINT)nTabs.GetData(), 0);
				break;
			}
			for (szDuration = GetDuration(); !szDuration.IsEmpty(); )
			{
				if ((nPos = szDuration.Find(EOL)) >= 0)
				{
					if (pDC->GetTextMetrics(&tmFont))
					{
						sizeToolText = pDC->GetTextExtent(szDuration.Left(nPos));
						pDC->FillRect(CRect(ptDuration.x, ptDuration.y, rToolTip.Width(), ptDuration.y + sizeToolText.cy), &cBkgndBrush);
						pDC->TabbedTextOut(ptDuration.x, ptDuration.y, szDuration.Left(nPos), (INT)nTabs.GetSize(), (LPINT)nTabs.GetData(), 0);
						szDuration = szDuration.Mid(nPos + 1);
						ptDuration.y += tmFont.tmHeight;
					}
					continue;
				}
				sizeToolText = pDC->GetTextExtent(szDuration);
				pDC->FillRect(CRect(ptDuration.x, ptDuration.y, rToolTip.Width(), ptDuration.y + sizeToolText.cy), &cBkgndBrush);
				pDC->TabbedTextOut(ptDuration.x, ptDuration.y, szDuration, (INT)nTabs.GetSize(), (LPINT)nTabs.GetData(), 0);
				break;
			}
			pDC->SelectObject(pOldFont);
		}
		pDC->SetTextColor(nOldColor);
		pDC->SetBkMode(nBkgndMode);
	}
}

BEGIN_MESSAGE_MAP(CGRDRulerTimeTip, CWnd)
	//{{AFX_MSG_MAP(CGRDRulerTimeTip)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDRulerTimeTip message handlers

BOOL CGRDRulerTimeTip::OnEraseBkgnd(CDC *pDC)
{
	CRect  rToolTip;
	CBrush  cBkgndBrush;

	for (GetClientRect(rToolTip); cBkgndBrush.CreateSysColorBrush(COLOR_INFOBK); )
	{
		pDC->FillRect(rToolTip, &cBkgndBrush);
		cBkgndBrush.DeleteObject();
		return TRUE;
	}
	return CWnd::OnEraseBkgnd(pDC);
}

void CGRDRulerTimeTip::OnPaint()
{
	CPaintDC  cDC(this);

	DrawContent(&cDC);
}

void CGRDRulerTimeTip::OnDestroy()
{
	m_szRange.Empty();
	m_szDuration.Empty();
	m_nTabs.RemoveAll();
	m_cFont.DeleteObject();
	CWnd::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CGRDRulerTip

IMPLEMENT_DYNCREATE(CGRDRulerTip, CWnd)

CGRDRulerTip::CGRDRulerTip() : CWnd()
{
	CFontTools  cFontTools(&m_cFont);

	m_tTime[0] = 0;
	m_tTime[1] = 0;
	m_ptTime.x = -1;
	m_ptTime.y = -1;
}

BOOL CGRDRulerTip::Create(CWnd *pParentWnd, CONST RECT &rect, CONST CTimeTag &tStartTime, CONST CTimeTag &tStopTime)
{
	CRect  rToolTip(rect);
	CGRDLayoutParameter  cParameter;

	if (SetRange(tStartTime, tStopTime) && rToolTip.Width() > 0)
	{
		for (pParentWnd->ClientToScreen(rToolTip); CWnd::CreateEx(WS_EX_TOPMOST, AfxRegisterWndClass(CS_SAVEBITS | CS_DROPSHADOW | CS_NOCLOSE, (HCURSOR)(DWORD_PTR)GetClassLongPtr(GetSafeHwnd(), GCLP_HCURSOR)), EMPTYSTRING, WS_POPUP | WS_BORDER, rToolTip.left, rToolTip.top, rToolTip.Width(), 0, pParentWnd->GetSafeHwnd(), (HMENU)NULL); )
		{
			pParentWnd->SetCapture();
			ShowWindow(SW_SHOWNA);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CGRDRulerTip::Destroy()
{
	if (IsWindow(GetSafeHwnd()))
	{
		ReleaseCapture();
		DestroyWindow();
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDRulerTip::SetFont(CFont *pFont)
{
	LOGFONT  lfFont;

	return((pFont->GetLogFont(&lfFont) && ((!m_cFont.GetSafeHandle() || m_cFont.DeleteObject()) && m_cFont.CreateFontIndirect(&lfFont))) ? TRUE : FALSE);
}

BOOL CGRDRulerTip::GetFont(CFont *pFont) CONST
{
	LOGFONT  lfFont;

	return((m_cFont.GetObject(sizeof(LOGFONT), &lfFont) > 0 && pFont->CreateFontIndirect(&lfFont)) ? TRUE : FALSE);
}

BOOL CGRDRulerTip::SetTimeTipFont(CFont *pFont)
{
	return m_wndTimeTip.SetFont(pFont);
}

BOOL CGRDRulerTip::GetTimeTipFont(CFont *pFont) CONST
{
	return m_wndTimeTip.GetFont(pFont);
}

BOOL CGRDRulerTip::SetRange(CONST CTimeTag &tStartTime, CONST CTimeTag &tStopTime)
{
	if (tStartTime < tStopTime)
	{
		m_tTime[0] = tStartTime;
		m_tTime[1] = tStopTime;
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDRulerTip::GetRange(CTimeTag &tStartTime, CTimeTag &tStopTime) CONST
{
	return CalcRange(m_ptTime, tStartTime, tStopTime);
}

VOID CGRDRulerTip::Update()
{
	CPoint  ptSlider;

	for (ptSlider = m_ptTime; IsWindow(GetSafeHwnd()); )
	{
		ClientToScreen(&ptSlider);
		break;
	}
	Update(m_tTime[0], m_tTime[1], ptSlider);
}
VOID CGRDRulerTip::Update(CONST CTimeTag &tStartTime, CONST CTimeTag &tStopTime, CONST POINT &point)
{
	CDC  *pDC;
	CDC  cMemDC;
	CPen  cPen[1];
	CPen  *pOldPen;
	CRect  rToolTip;
	CBrush  cBkgndBrush;
	CPoint  ptSlider[2];
	CString  szText[5];
	CBitmap  cBitmap[1];
	CBitmap  *pOldBitmap;
	CTimeTag  tTime[2];

	if (IsWindow(GetSafeHwnd()))
	{
		for (GetClientRect(rToolTip), ptSlider[0] = point, ScreenToClient(&ptSlider[0]), ptSlider[0].y = rToolTip.CenterPoint().y, ptSlider[1] = ptSlider[0], ClientToScreen(&ptSlider[1]), ptSlider[1].y -= rToolTip.Height() / 2, SetRange(tStartTime, tStopTime); ptSlider[0].x < rToolTip.left || ptSlider[0].x > rToolTip.right; )
		{
			ptSlider[0].x = max(ptSlider[0].x, rToolTip.left);
			ptSlider[0].x = min(ptSlider[0].x, rToolTip.right);
			ptSlider[1].x = ptSlider[0].x;
			ptSlider[1].y = ptSlider[0].y - rToolTip.Height() / 2;
			ClientToScreen(&ptSlider[1]);
			break;
		}
		if ((pDC = GetDC()))
		{
			if (cMemDC.CreateCompatibleDC(pDC))
			{
				if (cBitmap[0].CreateCompatibleBitmap(pDC, rToolTip.Width(), rToolTip.Height()))
				{
					if ((pOldBitmap = cMemDC.SelectObject(&cBitmap[0])))
					{
						if (cBkgndBrush.CreateSysColorBrush(COLOR_INFOBK))
						{
							if (cPen[0].CreatePen(PS_SOLID, 1, VGA_COLOR_RED))
							{
								if ((pOldPen = cMemDC.SelectObject(&cPen[0])))
								{
									CalcRange(ptSlider[0], tTime[0], tTime[1]);
									cMemDC.FillRect(rToolTip, &cBkgndBrush);
									DrawContent(&cMemDC);
									cMemDC.MoveTo(ptSlider[0].x, rToolTip.top);
									cMemDC.LineTo(ptSlider[0].x, rToolTip.bottom);
									pDC->BitBlt(0, 0, rToolTip.Width(), rToolTip.Height(), &cMemDC, 0, 0, SRCCOPY);
									szText[0].Format(((tTime[1].GetTime() - tTime[0].GetTime()) / (SECONDSPERDAY*(TIMETAG)1000000) != 1) ? STRING(IDS_GRD_RULERTIP_DURATIONDAYS) : STRING(IDS_GRD_RULERTIP_DURATIONDAY), (tTime[1].GetTime() - tTime[0].GetTime()) / (SECONDSPERDAY*(TIMETAG)1000000));
									szText[1].Format((((tTime[1].GetTime() - tTime[0].GetTime()) % (SECONDSPERDAY*(TIMETAG)1000000)) / (SECONDSPERHOUR*(TIMETAG)1000000) != 1) ? STRING(IDS_GRD_RULERTIP_DURATIONHOURS) : STRING(IDS_GRD_RULERTIP_DURATIONHOUR), ((tTime[1].GetTime() - tTime[0].GetTime()) % (SECONDSPERDAY*(TIMETAG)1000000)) / (SECONDSPERHOUR*(TIMETAG)1000000));
									szText[2].Format((((tTime[1].GetTime() - tTime[0].GetTime()) % (SECONDSPERHOUR*(TIMETAG)1000000)) / (SECONDSPERMINUTE*(TIMETAG)1000000) != 1) ? STRING(IDS_GRD_RULERTIP_DURATIONMINUTES) : STRING(IDS_GRD_RULERTIP_DURATIONMINUTE), ((tTime[1].GetTime() - tTime[0].GetTime()) % (SECONDSPERHOUR*(TIMETAG)1000000)) / (SECONDSPERMINUTE*(TIMETAG)1000000));
									szText[3].Format(STRING(IDS_GRD_RULERTIP_RANGEFORMAT), tTime[0].FormatGmt(STRING(IDS_TIMEKEY_FORMAT)), tTime[1].FormatGmt(STRING(IDS_TIMEKEY_FORMAT)));
									szText[4].Format(STRING(IDS_GRD_RULERTIP_DURATIONFORMAT), (LPCTSTR)szText[0], (LPCTSTR)szText[1], (LPCTSTR)szText[2]);
									m_wndTimeTip.Update(ptSlider[1], szText[3], szText[4]);
									cMemDC.SelectObject(pOldPen);
									m_ptTime = ptSlider[0];
								}
								cPen[0].DeleteObject();
							}
							cBkgndBrush.DeleteObject();
						}
						cMemDC.SelectObject(pOldBitmap);
					}
					cBitmap[0].DeleteObject();
				}
				cMemDC.DeleteDC();
			}
			ReleaseDC(pDC);
		}
	}
}

BOOL CGRDRulerTip::CalcRange(CONST POINT &point, CTimeTag &tStartTime, CTimeTag &tStopTime) CONST
{
	CRect  rToolTip;

	GetClientRect(rToolTip);
	tStartTime = m_tTime[0];
	tStopTime = (rToolTip.Width() > 0) ? (tStartTime.GetTime() + ((max(point.x, rToolTip.left) - rToolTip.left)*(m_tTime[1].GetTime() - m_tTime[0].GetTime())) / rToolTip.Width()) : tStartTime.GetTime();
	return((point.x >= rToolTip.left  &&  point.x <= rToolTip.right) ? TRUE : FALSE);
}

VOID CGRDRulerTip::DrawContent(CDC *pDC)
{
	INT  nTick;
	INT  nTicks;
	INT  nBkMode;
	CPen  cPen[2];
	CPen  *pOldPen;
	CSize  sizeText;
	CRect  rToolTip;
	CFont  cFont[1];
	CFont  *pOldFont;
	LOGFONT  lfFont;
	LOGBRUSH  cPenBrush;

	GetClientRect(rToolTip);
	cPenBrush.lbHatch = 0;
	cPenBrush.lbStyle = BS_SOLID;
	cPenBrush.lbColor = GetSysColor(COLOR_WINDOWTEXT);
	if (cPen[0].CreatePen(PS_SOLID | PS_GEOMETRIC | PS_ENDCAP_FLAT, 1, &cPenBrush))
	{
		if (cPen[1].CreatePen(PS_SOLID | PS_GEOMETRIC | PS_ENDCAP_FLAT, 3, &cPenBrush))
		{
			for (nTick = 0, nTicks = rToolTip.Width() / GRDRULERTIP_TICKSINTERVAL; nTick < nTicks; nTick++)
			{
				if ((pOldPen = (nTick % 10) ? pDC->SelectObject(&cPen[0]) : pDC->SelectObject(&cPen[1])))
				{
					pDC->MoveTo(nTick*GRDRULERTIP_TICKSINTERVAL, (nTick % 10) ? ((nTick % 5) ? (rToolTip.Height() / 4) : ((3 * rToolTip.Height()) / 8)) : (rToolTip.Height() / 2));
					pDC->LineTo(nTick*GRDRULERTIP_TICKSINTERVAL, 0);
					pDC->SelectObject(pOldPen);
				}
			}
			if (!HIBYTE(GetKeyState(VK_CONTROL)))
			{
				if (m_cFont.GetLogFont(&lfFont) > 0)
				{
					for (nBkMode = pDC->SetBkMode(TRANSPARENT), lfFont.lfHeight = rToolTip.Height() / 2, _tcscpy_s(lfFont.lfFaceName, sizeof(lfFont.lfFaceName) / sizeof(TCHAR), EMPTYSTRING); cFont[0].CreateFontIndirect(&lfFont); )
					{
						if ((pOldFont = (CFont *)pDC->SelectObject(&cFont[0])) != (CFont *)NULL)
						{
							sizeText = pDC->GetTextExtent(STRING(IDS_GRD_RULERTIP_ADVICECOMMENT) + CString(SPACE));
							pDC->TextOut(rToolTip.right - sizeText.cx, rToolTip.Height() / 2, STRING(IDS_GRD_RULERTIP_ADVICECOMMENT));
							pDC->SelectObject(pOldFont);
						}
						cFont[0].DeleteObject();
						break;
					}
					pDC->SetBkMode(nBkMode);
				}
			}
			cPen[1].DeleteObject();
		}
		cPen[0].DeleteObject();
	}
}

BEGIN_MESSAGE_MAP(CGRDRulerTip, CWnd)
	//{{AFX_MSG_MAP(CGRDRulerTip)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDRulerTip message handlers

int CGRDRulerTip::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) != -1 && m_wndTimeTip.Create(this))
	{
		MoveWindow(lpCreateStruct->x, lpCreateStruct->y, lpCreateStruct->cx, 3 * GetSystemMetrics(SM_CYHSCROLL) / 2);
		return 0;
	}
	return -1;
}

BOOL CGRDRulerTip::OnEraseBkgnd(CDC *pDC)
{
	CRect  rToolTip;
	CBrush  cBkgndBrush;

	for (GetClientRect(rToolTip); cBkgndBrush.CreateSysColorBrush(COLOR_INFOBK); )
	{
		pDC->FillRect(rToolTip, &cBkgndBrush);
		cBkgndBrush.DeleteObject();
		return TRUE;
	}
	return CWnd::OnEraseBkgnd(pDC);
}

void CGRDRulerTip::OnPaint()
{
	CPaintDC  cDC(this);

	DrawContent(&cDC);
}

void CGRDRulerTip::OnDestroy()
{
	m_wndTimeTip.DestroyWindow();
	m_cFont.DeleteObject();
	CWnd::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CGRDView

IMPLEMENT_DYNCREATE(CGRDView, CTextView)

CGRDView::CGRDView() : CTextView()
{
	m_ptGraph.x = 0;
	m_ptGraph.y = 0;
	m_tGraph[0] = 0;
	m_tGraph[1] = 0;
	m_tGraph[2] = 0;
	m_bGraphUpdate = TRUE;
	m_sizeLayoutFont.cx = 0;
	m_sizeLayoutFont.cy = 0;
	m_nLayoutColors.InsertAt(GRD_OOLCOLOR_NOLIMIT, VGA_COLOR_GRAY);
	m_nLayoutColors.InsertAt(GRD_OOLCOLOR_SOFTLIMIT, VGA_COLOR_RED);
	m_nLayoutColors.InsertAt(GRD_OOLCOLOR_HARDLIMIT, VGA_COLOR_LTRED);
	m_nLayoutColors.InsertAt(GRD_OOLCOLOR_DELTALIMIT, VGA_COLOR_MAGENTA);
	m_nLayoutColors.InsertAt(GRD_OOLCOLOR_CONSISTENCYLIMIT, VGA_COLOR_YELLOW);
	ZeroMemory(&m_lfLayoutDefault[0], sizeof(LOGFONT));
	ZeroMemory(&m_lfLayoutDefault[1], sizeof(LOGFONT));
	ZeroMemory(&m_lfLayoutDefault[2], sizeof(LOGFONT));
	ZeroMemory(&m_lfLayoutDefault[3], sizeof(LOGFONT));
	m_hToolTipCursor = (HCURSOR)NULL;
	m_sizeLayoutDefault.cx = 0;
	m_sizeLayoutDefault.cy = 0;
	m_bLayoutFont = FALSE;
	m_bInvalidDataMode = FALSE;
	m_bBadDataMode = FALSE;
	m_bToolTipMode = TRUE;
}

BOOL CGRDView::Create(CWnd *pParentWnd, DWORD dwStyle)
{
	return CTextView::Create(pParentWnd, CRect(0, 0, 0, 0), dwStyle);
}

BOOL CGRDView::SetLayout(CONST CGRDLayout &cLayout)
{
	return SetLayout(cLayout, GRD_TITLEITEMS_DEFAULT);
}
BOOL CGRDView::SetLayout(CONST CGRDLayout &cLayout, UINT nColumns)
{
	CUIntArray  nColumnItems;

	nColumnItems.Add(GRD_TITLEITEM_ID);
	if (nColumns & GRD_TITLEITEM_DESCRIPTION) nColumnItems.Add(GRD_TITLEITEM_DESCRIPTION);
	if (nColumns & GRD_TITLEITEM_VALUE) nColumnItems.Add(GRD_TITLEITEM_VALUE);
	if (nColumns & GRD_TITLEITEM_UNIT) nColumnItems.Add(GRD_TITLEITEM_UNIT);
	if (nColumns & GRD_TITLEITEM_RANGE) nColumnItems.Add(GRD_TITLEITEM_RANGE);
	if (nColumns & GRD_TITLEITEM_LINE) nColumnItems.Add(GRD_TITLEITEM_LINE);
	if (nColumns & GRD_TITLEITEM_CHANGETMUNIT) nColumnItems.Add(GRD_TITLEITEM_CHANGETMUNIT);
	if (nColumns & GRD_TITLEITEM_CHANGETIME) nColumnItems.Add(GRD_TITLEITEM_CHANGETIME);
	if (nColumns & GRD_TITLEITEM_UPDATETMUNIT) nColumnItems.Add(GRD_TITLEITEM_UPDATETMUNIT);
	if (nColumns & GRD_TITLEITEM_UPDATETIME) nColumnItems.Add(GRD_TITLEITEM_UPDATETIME);
	return SetLayout(cLayout, nColumnItems);
}
BOOL CGRDView::SetLayout(CONST CGRDLayout &cLayout, CONST CUIntArray &nColumns)
{
	CUIntArray  nWidths;

	return((CalcColumnsWidth(nColumns, nWidths)) ? SetLayout(cLayout, nColumns, nWidths, TRUE) : FALSE);
}
BOOL CGRDView::SetLayout(CONST CGRDLayout &cLayout, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths, BOOL bAdjust)
{
	INT  nRow;
	INT  nRows;
	INT  nIndex[2];
	INT  nCount[2];
	INT  nWidth[2];
	INT  nPosition;
	INT  nParameter;
	INT  nParameters;
	double  fMinimum;
	double  fMaximum;
	CTMUnit  cTMUnit;
	CString  szRange;
	CString  szRow[2];
	CString  szMinimum;
	CString  szMaximum;
	CStringArray  szRows;
	CStringArray  szColumns;
	CUIntArray  nColumnWidths;
	CUIntArray  nCalTableRefs;
	CUIntArray  nCalValidityRefs;
	CTMParameter  *pTMParameter;
	CTextViewAttribute  *pAttribute;
	CTextViewAttributes  pAttributes;
	CGRDLayoutParameter  *pParameter;
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
	for (nParameter = 0, nParameters = (m_cLayout.GetType() == cLayout.GetType() && m_cLayout.GetSize() == cLayout.GetSize()) ? (INT)m_cLayout.GetSize() : -1, m_sizeLayoutDefault = (m_cLayout.GetName().IsEmpty() || !CanReduceFonts(TRUE)) ? cLayout.GetPlotSize() : m_sizeLayoutDefault; nParameter < nParameters; nParameter++)
	{
		if (m_cLayout.GetAt(nParameter)->GetName() != cLayout.GetAt(nParameter)->GetName() || m_cLayout.GetAt(nParameter)->GetAttributes() != cLayout.GetAt(nParameter)->GetAttributes()) break;
		continue;
	}
	if (nParameter != nParameters)
	{
		m_wndContentCtrl.m_szContentText.RemoveAll();
		m_wndContentCtrl.m_nContentTextPos.RemoveAll();
		m_wndContentCtrl.m_pContentTextAttributes.RemoveAll();
		m_wndContentCtrl.m_nScrollPos[0] = 0;
		m_wndContentCtrl.m_nScrollPos[1] = 0;
		m_wndContentCtrl.m_nActiveItem = -1;
		m_wndContentCtrl.m_nActiveColumn = -1;
		Reset();
	}
	for (nRow = 0, nRows = (m_cLayout.Copy(&cLayout)) ? (INT)m_cLayout.GetSize() : -1, m_nLayoutSlots.RemoveAll(), nColumnWidths.Copy(nWidths); nRow < nRows; nRow++)
	{
		if ((pDatabaseTMParameter = ((pParameter = m_cLayout.GetAt(nRow))) ? GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(pParameter->GetName())) : (CDatabaseTMParameter *)NULL))
		{
			for (nIndex[0] = 0, nCount[0] = (INT)nColumns.GetSize(), m_nLayoutColumns.Copy(nColumns), szRow[0].Empty(); nIndex[0] < nCount[0]; nIndex[0]++)
			{
				switch (nColumns.GetAt(nIndex[0]))
				{
				case GRD_TITLEITEM_ID:
				{ szRow[1] = pDatabaseTMParameter->GetTag();
				break;
				}
				case GRD_TITLEITEM_DESCRIPTION:
				{ szRow[1] = pDatabaseTMParameter->GetDescription();
				break;
				}
				case GRD_TITLEITEM_UNIT:
				{ szRow[1] = pDatabaseTMParameter->GetUnit();
				break;
				}
				case GRD_TITLEITEM_RANGE:
				{ if (pParameter->GetRange(fMinimum, fMaximum))
				{
					ConvertAxesRangeValues(pParameter, fMinimum, fMaximum, szMinimum, szMaximum);
					szRange.Format(STRING(IDS_GRD_TITLEITEMS_RANGEFORMAT), (LPCTSTR)szMinimum, (LPCTSTR)szMaximum);
					szRow[1] = szRange;
					break;
				}
				}
				default:
				{ szRow[1] = EMPTYSTRING;
				break;
				}
				}
				nWidth[0] = CalcColumnWidth(nColumns.GetAt(nIndex[0]), szRow[1]);
				szRow[0] += (nIndex[0] > 0) ? (GetColumnDelimiter() + szRow[1]) : szRow[1];
				for (nIndex[1] = (bAdjust && ((!nIndex[0] && nColumnWidths.GetAt(nIndex[0]) < (UINT)nWidth[0]) || (nIndex[0] > 0 && nColumnWidths.GetAt(nIndex[0]) - nColumnWidths.GetAt(nIndex[0] - 1) < (UINT)nWidth[0]))) ? nIndex[0] : nCount[0], nWidth[1] = (nIndex[0] > 0) ? (nColumnWidths.GetAt(nIndex[0]) - nColumnWidths.GetAt(nIndex[0] - 1)) : nColumnWidths.GetAt(nIndex[0]), nCount[1] = nCount[0]; nIndex[1] < nCount[1]; nIndex[1]++)
				{
					nColumnWidths.SetAt(nIndex[1], nColumnWidths.GetAt(nIndex[1]) + nWidth[0] - nWidth[1]);
					continue;
				}
				if ((pAttribute = (nRow >= pAttributes.GetSize() || !pAttributes.GetAt(nRow)) ? new CTextViewAttribute : pAttributes.GetAt(nRow)))
				{
					pAttribute->SetColumnFormat(nIndex[0], (nColumns.GetAt(nIndex[0]) == GRD_TITLEITEM_VALUE) ? (DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX) : (DT_LEFT | DT_VCENTER | DT_WORDBREAK | DT_NOPREFIX));
					pAttribute->SetColumnColor(nIndex[0], (pParameter->GetColor() == GetSysColor(COLOR_WINDOW)) ? LookupColumnColor(nColumns.GetAt(nIndex[0])) : pParameter->GetColor());
					pAttributes.SetAtGrow(nRow, pAttribute);
				}
			}
			if (nRow >= pAttributes.GetSize() || !pAttributes.GetAt(nRow))
			{
				if ((pAttribute = new CTextViewAttribute) != (CTextViewAttribute *)NULL)
				{
					pAttribute->SetColumnFormat(-1, DT_LEFT | DT_VCENTER | DT_NOPREFIX);
					pAttribute->SetColumnColor(-1, GetSysColor(COLOR_WINDOW));
					pAttributes.SetAtGrow(nRow, pAttribute);
				}
			}
			szRows.InsertAt(nRow, szRow[0]);
			if ((nPosition = pParameter->GetPosition()) >= 0)
			{
				if (nPosition >= m_nLayoutSlots.GetSize())
				{
					m_nLayoutSlots.SetAtGrow(nPosition, 1);
					continue;
				}
				m_nLayoutSlots.SetAt(nPosition, m_nLayoutSlots.GetAt(nPosition) + 1);
			}
			continue;
		}
		m_cLayout.RemoveAt(nRow);
		nRows--;
		nRow--;
	}
	for (nRow = (INT)szRows.GetSize(), nRows = (nRows >= 0) ? GetTextCount() : -1; nRow < nRows; nRow++)
	{
		DeleteText(nRow, FALSE);
		nRows--;
		nRow--;
	}
	for (nParameter = 0, nParameters = (INT)m_cLayout.GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pParameter = m_cLayout.GetAt(nParameter)) && m_pLayoutValues.Find(pParameter->GetName()) < 0)
		{
			if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(pParameter->GetRef())))
			{
				if ((pTMParameter = new CTMParameter))
				{
					pTMParameter->SetTag(pParameter->GetName());
					pTMParameter->SetAttributes((pDatabaseTMParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_FLOATINGPOINT | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_DECIMAL | TMPARAMETER_RADIX_HEXADECIMAL)) | (pParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_FLOATINGPOINT | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_DECIMAL | TMPARAMETER_RADIX_HEXADECIMAL)));
					if (pDatabaseTMParameter->GetAttributes() & TMPARAMETER_NATURE_CONSTANT) pTMParameter->SetRawValue(&cTMUnit, 0, pDatabaseTMParameter->GetConstValue(), TMPARAMETER_STATUS_GOOD | TMPARAMETER_STATUS_NOLIMIT | TMPARAMETER_STATUS_VALID, (pDatabaseTMParameter->GetCalTableRefs(nCalTableRefs, nCalValidityRefs) > 0) ? ((pDatabaseTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) ? (((pDatabaseTMNumCalTable = GetDatabase()->GetTMNumCalTables()->GetAt(nCalTableRefs.GetAt(0)))) ? (LPCTSTR)pDatabaseTMNumCalTable->GetName() : EMPTYSTRING) : (((pDatabaseTMTxtCalTable = GetDatabase()->GetTMTxtCalTables()->GetAt(nCalTableRefs.GetAt(0)))) ? (LPCTSTR)pDatabaseTMTxtCalTable->GetName() : EMPTYSTRING)) : EMPTYSTRING);
					m_pLayoutValues.Add(pTMParameter);
					continue;
				}
			}
			break;
		}
		if ((pParameter = m_cLayout.GetAt(nParameter)))
		{
			if ((pTMParameter = m_pLayoutValues.GetAt(m_pLayoutValues.Find(pParameter->GetName()))))
			{
				if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(pParameter->GetRef())))
				{
					pTMParameter->SetAttributes((pDatabaseTMParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_FLOATINGPOINT | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_DECIMAL | TMPARAMETER_RADIX_HEXADECIMAL)) | (pParameter->GetAttributes() & (TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_FLOATINGPOINT | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_DECIMAL | TMPARAMETER_RADIX_HEXADECIMAL)));
					continue;
				}
				break;
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
	for (nRow = 0, nRows = (nRows >= 0) ? ((LookupColumnsName(nColumns, szColumns) && SetColumns(szColumns, nColumnWidths) && szRows.GetSize() == pAttributes.GetSize()) ? (INT)szRows.GetSize() : -1) : -1; nRow < nRows; nRow++)
	{
		if ((nRow < GetTextCount() && SetText(nRow, szRows.GetAt(nRow), pAttributes.GetAt(nRow), FALSE)) || (nRow >= GetTextCount() && InsertText(nRow, szRows.GetAt(nRow), pAttributes.GetAt(nRow), FALSE))) continue;
		break;
	}
	for (SetItemsFont(&m_wndContentCtrl.m_cFont, !(m_bLayoutFont = TRUE)), SetValuesFont(&m_cLayoutFont[0], FALSE), SetAxesFont(&m_cLayoutFont[1], (m_bLayoutFont = FALSE)), UpdateGraph(), ReducePlotArea(); nRow == nRows && nParameter == nParameters; )
	{
		Update();
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDView::GetLayout(CGRDLayout &cLayout) CONST
{
	CUIntArray  nColumns;

	return GetLayout(cLayout, nColumns);
}
BOOL CGRDView::GetLayout(CGRDLayout &cLayout, CUIntArray &nColumns) CONST
{
	CUIntArray  nWidths;

	return GetLayout(cLayout, nColumns, nWidths);
}
BOOL CGRDView::GetLayout(CGRDLayout &cLayout, CUIntArray &nColumns, CUIntArray &nWidths) CONST
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

BOOL CGRDView::SetTitleFont(CFont *pFont, BOOL bDefault)
{
	LOGFONT  lfFont;

	return((pFont->GetLogFont(&lfFont) > 0) ? SetTitleFont(&lfFont, bDefault) : FALSE);
}
BOOL CGRDView::SetTitleFont(CONST LOGFONT *plfFont, BOOL bDefault)
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

BOOL CGRDView::GetTitleFont(CFont *pFont, BOOL bDefault) CONST
{
	CTextViewLock  cLock(this);

	return(((bDefault  &&  lstrlen(m_lfLayoutDefault[0].lfFaceName) > 0 && pFont->CreateFontIndirect(&m_lfLayoutDefault[0])) || CTextView::GetTitleFont(pFont)) ? TRUE : FALSE);
}
BOOL CGRDView::GetTitleFont(LOGFONT *plfFont, BOOL bDefault) CONST
{
	CTextViewLock  cLock(this);

	CopyMemory(plfFont, &m_lfLayoutDefault[0], (bDefault) ? sizeof(LOGFONT) : 0);
	return(((bDefault  &&  lstrlen(m_lfLayoutDefault[0].lfFaceName) > 0) || CTextView::GetTitleFont(plfFont)) ? TRUE : FALSE);
}

BOOL CGRDView::SetItemsFont(CFont *pFont, BOOL bDefault)
{
	LOGFONT  lfFont;

	return((pFont->GetLogFont(&lfFont) > 0) ? SetItemsFont(&lfFont, bDefault) : FALSE);
}
BOOL CGRDView::SetItemsFont(CONST LOGFONT *plfFont, BOOL bDefault)
{
	INT  nColumn;
	INT  nColumns;
	BOOL  bRestore;
	CStringArray  szColumns;
	CTextViewLock  cLock(this);

	for (nColumn = 0, nColumns = (GetColumns(szColumns)) ? (INT)szColumns.GetSize() : 0; nColumn < nColumns; nColumn++)
	{
		if (LookupColumnName(szColumns.GetAt(nColumn)) != GRD_TITLEITEM_VALUE)
		{
			SetColumnFont(nColumn, plfFont);
			continue;
		}
	}
	for (bRestore = CanReduceFonts(TRUE), CopyMemory(&m_lfLayoutDefault[1], plfFont, (bDefault) ? sizeof(LOGFONT) : 0); CTextView::SetTextFont(plfFont); )
	{
		if (bDefault  &&  bRestore) ReduceFonts(bRestore);
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDView::GetItemsFont(CFont *pFont, BOOL bDefault) CONST
{
	CTextViewLock  cLock(this);

	return(((bDefault  &&  lstrlen(m_lfLayoutDefault[1].lfFaceName) > 0 && pFont->CreateFontIndirect(&m_lfLayoutDefault[1])) || CTextView::GetTextFont(pFont)) ? TRUE : FALSE);
}
BOOL CGRDView::GetItemsFont(LOGFONT *plfFont, BOOL bDefault) CONST
{
	CTextViewLock  cLock(this);

	CopyMemory(plfFont, &m_lfLayoutDefault[1], (bDefault) ? sizeof(LOGFONT) : 0);
	return(((bDefault  &&  lstrlen(m_lfLayoutDefault[1].lfFaceName) > 0) || CTextView::GetTextFont(plfFont)) ? TRUE : FALSE);
}

BOOL CGRDView::SetValuesFont(CFont *pFont, BOOL bDefault)
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
BOOL CGRDView::SetValuesFont(CONST LOGFONT *plfFont, BOOL bDefault)
{
	INT  nIndex;
	INT  nCount;
	BOOL  bRestore;
	CStringArray  szColumns;
	CTextViewLock  cLock(this);

	for (nIndex = 0, nCount = (GetColumns(szColumns)) ? (INT)szColumns.GetSize() : 0; nIndex < nCount; nIndex++)
	{
		if (LookupColumnName(szColumns.GetAt(nIndex)) == GRD_TITLEITEM_VALUE)
		{
			SetColumnFont(nIndex, plfFont);
			continue;
		}
	}
	for (bRestore = CanReduceFonts(TRUE); (!m_cLayoutFont[0].GetSafeHandle() || m_cLayoutFont[0].DeleteObject()) && m_cLayoutFont[0].CreateFontIndirect(plfFont); )
	{
		for (CopyMemory(&m_lfLayoutDefault[2], plfFont, (bDefault) ? sizeof(LOGFONT) : 0); bDefault && bRestore; )
		{
			ReduceFonts(bRestore);
			break;
		}
		RecalcContent();
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDView::GetValuesFont(CFont *pFont, BOOL bDefault) CONST
{
	LOGFONT  lfFont;
	CTextViewLock  cLock(this);

	return((GetValuesFont(&lfFont, bDefault)) ? pFont->CreateFontIndirect(&lfFont) : FALSE);
}
BOOL CGRDView::GetValuesFont(LOGFONT *plfFont, BOOL bDefault) CONST
{
	CTextViewLock  cLock(this);

	if (((!bDefault || !lstrlen(m_lfLayoutDefault[2].lfFaceName)) && m_cLayoutFont[0].GetSafeHandle() && m_cLayoutFont[0].GetObject(sizeof(LOGFONT), plfFont) > 0) || (bDefault  &&  lstrlen(m_lfLayoutDefault[2].lfFaceName) > 0))
	{
		CopyMemory(plfFont, &m_lfLayoutDefault[2], (bDefault  &&  lstrlen(m_lfLayoutDefault[2].lfFaceName) > 0) ? sizeof(LOGFONT) : 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDView::SetAxesFont(CFont *pFont, BOOL bDefault)
{
	LOGFONT  lfFont;
	CTextViewLock  cLock(this);

	if (!pFont)
	{
		if (GetAxesFont(&lfFont, bDefault))
		{
			SetAxesFont(&lfFont, bDefault);
			return TRUE;
		}
		if (GetItemsFont(&lfFont, bDefault))
		{
			lfFont.lfWeight = FW_REGULAR;
			lfFont.lfWidth = 0;
			return SetAxesFont(&lfFont, bDefault);
		}
		return FALSE;
	}
	return((pFont->GetLogFont(&lfFont)) ? SetAxesFont(&lfFont, bDefault) : FALSE);
}
BOOL CGRDView::SetAxesFont(CONST LOGFONT *plfFont, BOOL bDefault)
{
	BOOL  bRestore;
	CTextViewLock  cLock(this);

	for (bRestore = CanReduceFonts(TRUE); (!m_cLayoutFont[1].GetSafeHandle() || m_cLayoutFont[1].DeleteObject()) && m_cLayoutFont[1].CreateFontIndirect(plfFont); )
	{
		for (CopyMemory(&m_lfLayoutDefault[3], plfFont, (bDefault) ? sizeof(LOGFONT) : 0), m_sizeLayoutFont = CSize(0, CalcAxesSymbolHeight()); bDefault && bRestore; )
		{
			ReduceFonts(bRestore);
			break;
		}
		RecalcContent();
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDView::GetAxesFont(CFont *pFont, BOOL bDefault) CONST
{
	LOGFONT  lfFont;
	CTextViewLock  cLock(this);

	return((GetAxesFont(&lfFont, bDefault)) ? pFont->CreateFontIndirect(&lfFont) : FALSE);
}
BOOL CGRDView::GetAxesFont(LOGFONT *plfFont, BOOL bDefault) CONST
{
	CTextViewLock  cLock(this);

	if (((!bDefault || !lstrlen(m_lfLayoutDefault[3].lfFaceName)) && m_cLayoutFont[1].GetSafeHandle() && m_cLayoutFont[1].GetObject(sizeof(LOGFONT), plfFont) > 0) || (bDefault  &&  lstrlen(m_lfLayoutDefault[3].lfFaceName) > 0))
	{
		CopyMemory(plfFont, &m_lfLayoutDefault[3], (bDefault  &&  lstrlen(m_lfLayoutDefault[3].lfFaceName) > 0) ? sizeof(LOGFONT) : 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDView::SetMarkers(CONST CGRDMarkers &pMarkers)
{
	CTextViewLock  cLock(this);

	return m_pLayoutMarkers.Copy(&pMarkers);
}

BOOL CGRDView::GetMarkers(CGRDMarkers &pMarkers) CONST
{
	CTextViewLock  cLock(this);

	return pMarkers.Copy(&m_pLayoutMarkers);
}

BOOL CGRDView::SetOolColors(CONST CUIntArray &nColors)
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

BOOL CGRDView::GetOolColors(CUIntArray &nColors) CONST
{
	CTextViewLock  cLock(this);

	nColors.Copy(m_nLayoutColors);
	return(nColors.GetSize() > 0);
}

BOOL CGRDView::InitializeScalingData()
{
	INT  nID;
	INT  nIDs;
	INT  nParameter;
	INT  nParameters;
	CGRDLayoutParameter  *pParameter;
	CTextViewLock  cLock(this);

	for (nID = 0, nIDs = (INT)m_nGraphTimerIDs.GetSize(); nID < nIDs; nID++)
	{
		KillTimer(m_nGraphTimerIDs.GetAt(nID));
		m_nGraphTimerIDs.RemoveAt(nID);
		nIDs--;
		nID--;
	}
	for (nParameter = 0, nParameters = (INT)m_cLayout.GetSize(); nParameter < nParameters; nParameter++)
	{
		if ((pParameter = m_cLayout.GetAt(nParameter)) && pParameter->GetAutoScaleDelay().GetTotalSeconds() / SECONDSPERMINUTE > 0)
		{
			if (SetTimer(nParameter, (UINT)(1000 * pParameter->GetAutoScaleDelay().GetTotalSeconds()), NULL) > 0)
			{
				m_nGraphTimerIDs.Add(nParameter);
				continue;
			}
		}
	}
	return TRUE;
}

BOOL CGRDView::SetScalingData(CONST CByteArray &nScalingData)
{
	CTextViewLock  cLock(this);

	if (!IsWindow(GetSafeHwnd()))
	{
		m_cLayout.SetScalingData(nScalingData);
		return TRUE;
	}
	if (m_cLayout.SetScalingData(nScalingData))
	{
		InitializeScalingData();
		UpdateGraphScaling();
		UpdateGraph();
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDView::GetScalingData(CByteArray &nScalingData) CONST
{
	CTextViewLock  cLock(this);

	return m_cLayout.GetScalingData(nScalingData);
}

BOOL CGRDView::EnableInvalidDataMode(BOOL bEnable)
{
	m_bInvalidDataMode = bEnable;
	return TRUE;
}

BOOL CGRDView::IsInvalidDataModeEnabled() CONST
{
	return m_bInvalidDataMode;
}

BOOL CGRDView::EnableBadDataMode(BOOL bEnable)
{
	m_bBadDataMode = bEnable;
	return TRUE;
}

BOOL CGRDView::IsBadDataModeEnabled() CONST
{
	return m_bBadDataMode;
}

BOOL CGRDView::EnableToolTipMode(BOOL bEnable)
{
	m_bToolTipMode = bEnable;
	return TRUE;
}

BOOL CGRDView::IsToolTipModeEnabled() CONST
{
	return m_bToolTipMode;
}

BOOL CGRDView::Initialize(CTMEnvironment *pTMEnvironment)
{
	CTextViewLock  cLock(this);

	return pTMEnvironment->Initialize(m_pLayoutValues, IsBadDataModeEnabled());
}
BOOL CGRDView::Initialize(CString &szTag, CTimeTag &tTag)
{
	INT  nMode;
	INT  nPlot;
	INT  nPlots;
	INT  nSample;
	INT  nSamples;
	INT  nParameter;
	INT  nParameters;
	CTMParameter  *pTMParameter;
	CGRDLayoutParameter  *pParameter;
	CGRDParameterSample  *pParameterSample;
	CGRDParameterSamples  *pParameterSamples;
	CTextViewLock  cLock(this);

	for (nParameter = 0, nParameters = (((nMode = GetParent()->GetMode()) == DISPLAY_MODE_REALTIME && (!m_bGraphUpdate || InitializeTMData(m_pLayoutValues, IsBadDataModeEnabled()))) || (nMode == DISPLAY_MODE_HISTORY && (!m_bGraphUpdate || GetParent()->InitializeTMData(m_pLayoutValues, IsBadDataModeEnabled())))) ? (INT)m_pLayoutValues.GetSize() : -1, szTag.Empty(), tTag = 0, m_bLayoutValues.RemoveAll(), m_nLayoutStatus.RemoveAll(), m_szLayoutTables.RemoveAll(), m_bLayoutValues.SetSize(m_cLayout.GetSize()), m_nLayoutStatus.SetSize(m_cLayout.GetSize()), m_szLayoutTables.SetSize(m_cLayout.GetSize()); nParameter < nParameters; nParameter++)
	{
		if ((pTMParameter = m_pLayoutValues.GetAt(nParameter)) && pTMParameter->IsInitialized() && tTag < pTMParameter->GetLastUpdateTime())
		{
			szTag = pTMParameter->GetLastUpdateTMUnit();
			tTag = pTMParameter->GetLastUpdateTime();
		}
	}
	if (nParameter == nParameters)
	{
		if (szTag.IsEmpty() || !tTag.GetTime() || !m_tGraph[0].GetTime() || !m_tGraph[1].GetTime() || !m_tGraph[2].GetTime() || tTag < m_tGraph[1] || tTag > m_tGraph[2] || !m_cGraphPlots.GetSize())
		{
			for (nPlot = 0, nPlots = (INT)m_cLayout.GetSize(), m_cGraphPlots.RemoveAll(), m_cGraphBits.RemoveAll(); nPlot < nPlots; nPlot = nPlot + 1)
			{
				if ((pTMParameter = ((pParameter = m_cLayout.GetAt(nPlot))) ? m_pLayoutValues.GetAt(m_pLayoutValues.Find(pParameter->GetName())) : (CTMParameter *)NULL))
				{
					if ((pParameterSamples = new CGRDParameterSamples(pTMParameter->GetTag())))
					{
						if (m_cGraphPlots.Add(pParameterSamples) < 0)
						{
							delete pParameterSamples;
							break;
						}
						if (pTMParameter->IsInitialized() && !szTag.IsEmpty() && tTag > 0)
						{
							if (pTMParameter->GetAttributes() & TMPARAMETER_NATURE_CONSTANT)
							{
								if ((pParameterSample = new CGRDParameterSample))
								{
									if (pParameterSample->CTMParameter::Copy(pTMParameter))
									{
										pParameterSample->SetUpdateTime(tTag);
										pParameterSample->SetUpdateTMUnit(STRING(IDS_GRD_GRAPHTEXT_UPDATETMUNIT));
										if (pParameterSamples->Add(pParameter, pParameterSample) >= 0) continue;
									}
									delete pParameterSample;
								}
								break;
							}
							if ((pParameterSample = new CGRDParameterSample))
							{
								if (pParameterSample->CTMParameter::Copy(pTMParameter))
								{
									if (pParameterSample->GetUpdateTime() < tTag)
									{
										pParameterSample->SetUpdateTime(tTag);
										pParameterSample->SetUpdateTMUnit(STRING(IDS_GRD_GRAPHTEXT_UPDATETMUNIT));
									}
									if (pParameterSamples->Add(pParameter, pParameterSample) >= 0) continue;
								}
								delete pParameterSample;
							}
							break;
						}
						continue;
					}
				}
				break;
			}
			if (nPlot < nPlots)
			{
				m_ptGraph.x = 0;
				m_ptGraph.y = 0;
				m_tGraph[0] = 0;
				m_tGraph[1] = 0;
				m_tGraph[2] = 0;
				m_bGraphUpdate = TRUE;
				Update();
				UpdateGraph();
				DrawImage();
				return FALSE;
			}
			for (m_ptGraph.x = m_ptGraph.y = 0, m_tGraph[0] = m_tGraph[1] = m_tGraph[2] = 0, m_bGraphUpdate = TRUE; !szTag.IsEmpty() && tTag > 0; )
			{
				m_tGraph[2] = (m_cLayout.GetInterval().GetTotalSeconds() > 0) ? ((m_tGraph[0] = m_tGraph[1] = tTag).GetTime() + 1000000 * m_cLayout.GetInterval().GetTotalSeconds()) : ((m_tGraph[0] = m_tGraph[1] = tTag).GetTime() + 1000000 * (TIMETAG)m_cLayout.GetDuration().GetTotalSeconds());
				break;
			}
		}
		if ((m_cLayout.GetMode() & GRDLAYOUT_MODE_SCROLL) != GRDLAYOUT_MODE_SCROLL)
		{
			m_ptGraph.x = m_ptGraph.y = 0;
			m_tGraph[0] = m_tGraph[1];
		}
		for (; !szTag.IsEmpty() && tTag > 0; )
		{
			m_tGraph[2] = (m_cLayout.GetInterval().GetTotalSeconds() > 0) ? (m_tGraph[1].GetTime() + 1000000 * m_cLayout.GetInterval().GetTotalSeconds()) : (m_tGraph[1].GetTime() + 1000000 * (TIMETAG)m_cLayout.GetDuration().GetTotalSeconds());
			break;
		}
		if ((m_cLayout.GetMode() & GRDLAYOUT_MODE_SCROLL) || (m_cLayout.GetMode() & GRDLAYOUT_MODE_RESTART))
		{
			for (nPlot = 0, nPlots = (INT)m_cGraphPlots.GetSize(); nPlot < nPlots; nPlot++)
			{
				if ((pParameterSamples = (CGRDParameterSamples *)m_cGraphPlots.GetAt(nPlot)))
				{
					for (nSample = 0, nSamples = (INT)pParameterSamples->GetSize(); nSample < nSamples; nSample++)
					{
						if ((pParameterSample = pParameterSamples->GetAt(nSample)) && pParameterSample->GetUpdateTime() < m_tGraph[1])
						{
							pParameterSamples->RemoveAt(nSample);
							delete pParameterSample;
							nSamples--;
							nSample--;
							continue;
						}
						break;
					}
				}
			}
		}
		Update();
		UpdateGraph();
		DrawImage();
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDView::Update(CTMEnvironment *pTMEnvironment)
{
	INT  nRow;
	INT  nPlot;
	INT  nPlots;
	INT  nIndex;
	INT  nCount;
	INT  nColumn;
	INT  nMargin[2];
	INT  nSample[2];
	INT  nSamples[2];
	INT  nParameter;
	INT  nParameters;
	INT  nOccurrence;
	INT  nOccurrences;
	BOOL  bOccurrence;
	BOOL  bParameters;
	BOOL  bConnected;
	BOOL  bUpdate[4];
	BOOL  bOutSet;
	BOOL  bRange;
	UINT  nStatus;
	double  fMin[2];
	double  fMax[2];
	double  fDigits;
	CPoint  ptToolTip;
	CString  szText;
	CString  szTitle;
	CString  szValue;
	CString  szCalTable;
	CString  szUpdate[2];
	CTimeTag  tUpdate[4];
	CTimeTag  tStartTime;
	CTimeTag  tStopTime;
	CTimeTag  tRange[2];
	CTimeSpan  tInterval;
	CTimeSpan  tDuration;
	ULONGLONG  nValue;
	CByteArray  bPlots;
	CUIntArray  nColumns;
	CStringArray  szColumns;
	CTMParameter  *pTMParameter;
	CTextViewAttribute  *pAttribute;
	CGRDLayoutParameter  *pParameter;
	CGRDParameterSample  *pParameterSample[2];
	CGRDParameterSamples  *pParameterSamples;
	CTextViewLock  cLock(this);

	if (!pTMEnvironment)
	{
		m_bLayoutValues.SetSize(0);
		m_nLayoutStatus.SetSize(0);
		m_szLayoutTables.SetSize(0);
		m_bLayoutValues.SetSize((nParameters = (INT)m_cLayout.GetSize()));
		m_nLayoutStatus.SetSize(nParameters);
		m_szLayoutTables.SetSize(nParameters);
		bParameters = TRUE;
	}
	else
	{
		for (bUpdate[0] = m_pLayoutValues.Update(GetDatabase(), pTMEnvironment->GetTMUnit(), pTMEnvironment->GetTMParameters(), IsBadDataModeEnabled()), nParameters = -1, bParameters = FALSE; bUpdate[0]; )
		{
			nParameters = (INT)m_cLayout.GetSize();
			break;
		}
		if (!m_bGraphUpdate) return bUpdate[0];
	}
	for (nParameter = 0, bPlots.SetSize(max(nParameters, 0)), tUpdate[0] = tUpdate[1] = 0, tUpdate[2] = (!bParameters) ? pTMEnvironment->GetTMUnit()->GetTimeTag() : 0, szUpdate[0] = STRING(IDS_GRD_GRAPHTEXT_UPDATETMUNIT), bUpdate[0] = bUpdate[1] = FALSE; nParameter < nParameters; nParameter++)
	{
		if ((pTMParameter = ((pParameter = m_cLayout.GetAt(nParameter)) != (CGRDLayoutParameter *)NULL) ? m_pLayoutValues.GetAt(m_pLayoutValues.Find(pParameter->GetName())) : (CTMParameter *)NULL))
		{
			for (nOccurrence = (bParameters) ? ((pParameter->GetOccurrence() < 0) ? max(pTMParameter->GetValueCount() - 1, 0) : pParameter->GetOccurrence()) : 0, nOccurrences = (pParameter->GetOccurrence() >= 0) ? (pParameter->GetOccurrence() + 1) : pTMParameter->GetValueCount(), bOccurrence = bUpdate[2] = FALSE; nOccurrence < nOccurrences || !bOccurrence; nOccurrence++, bOccurrence = TRUE)
			{
				if (nParameter < m_bLayoutValues.GetSize() && (!m_bLayoutValues.GetAt(nParameter) || ((pTMEnvironment->GetTMUnit()->IsValid() && ((pTMParameter->GetLastUpdateTMUnit() == pTMEnvironment->GetTMUnit()->GetTag() && pTMParameter->GetLastUpdateTime() == pTMEnvironment->GetTMUnit()->GetTimeTag()) || (pTMParameter->GetRawValue(nOccurrence, nValue, nStatus, szCalTable) && (m_nLayoutStatus.GetAt(nParameter) != nStatus || m_szLayoutTables.GetAt(nParameter) != szCalTable)))) || !pTMEnvironment->GetTMUnit()->IsValid())))
				{
					if (ConvertColumnToIndex(GRD_TITLEITEM_VALUE, nIndex))
					{
						szColumns.Add((pTMParameter->GetRawValue(nOccurrence, nValue, nStatus) && pTMParameter->GetValueAsText(GetDatabase(), nOccurrence, pParameter->GetAttributes(), (pParameter->GetDigits() != 0) ? pParameter->GetDigits() : -1, szValue, bOutSet, FALSE) && (IsBadDataModeEnabled() || (nStatus & TMPARAMETER_STATUS_GOOD))) ? (((nStatus & TMPARAMETER_STATUS_VALID) || IsInvalidDataModeEnabled()) ? ((bOutSet) ? ((pTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) ? (LPCTSTR)(szValue + GetDatabase()->GetTMNumCalTablePointOutsideText()) : (LPCTSTR)((pTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS) ? (LPCTSTR)(szValue + GetDatabase()->GetTMTxtCalTablePointOutsideText()) : (LPCTSTR)szValue)) : (LPCTSTR)szValue) : EMPTYSTRING) : EMPTYSTRING);
						nColumns.Add(nIndex);
					}
					bUpdate[2] = TRUE;
				}
				if (nParameter < m_bLayoutValues.GetSize() && (!m_bLayoutValues.GetAt(nParameter) || ((pTMEnvironment->GetTMUnit()->IsValid() && ((pTMParameter->GetLastChangeTMUnit() == pTMEnvironment->GetTMUnit()->GetTag() && pTMParameter->GetLastChangeTime() == pTMEnvironment->GetTMUnit()->GetTimeTag()) || (pTMParameter->GetRawValue(nOccurrence, nValue, nStatus, szCalTable) && (m_nLayoutStatus.GetAt(nParameter) != nStatus || m_szLayoutTables.GetAt(nParameter) != szCalTable)))) || !pTMEnvironment->GetTMUnit()->IsValid())))
				{
					if (ConvertColumnToIndex(GRD_TITLEITEM_CHANGETMUNIT, nIndex))
					{
						szColumns.Add(((pTMParameter->GetAttributes() & TMPARAMETER_NATURE_CONSTANT) != TMPARAMETER_NATURE_CONSTANT  &&  pTMParameter->GetRawValue(nOccurrence, nValue, nStatus)) ? (((nStatus & TMPARAMETER_STATUS_VALID) || IsInvalidDataModeEnabled()) ? (LPCTSTR)pTMParameter->GetLastChangeTMUnit() : EMPTYSTRING) : EMPTYSTRING);
						nColumns.Add(nIndex);
					}
					if (ConvertColumnToIndex(GRD_TITLEITEM_CHANGETIME, nIndex))
					{
						szColumns.Add((pTMParameter->IsInitialized() && (pTMParameter->GetAttributes() & TMPARAMETER_NATURE_CONSTANT) != TMPARAMETER_NATURE_CONSTANT  &&  pTMParameter->GetRawValue(nOccurrence, nValue, nStatus)) ? (((nStatus & TMPARAMETER_STATUS_VALID) || IsInvalidDataModeEnabled()) ? (LPCTSTR)pTMParameter->GetLastChangeTime().FormatGmt() : EMPTYSTRING) : EMPTYSTRING);
						nColumns.Add(nIndex);
					}
				}
				if (nParameter < m_bLayoutValues.GetSize() && (!m_bLayoutValues.GetAt(nParameter) || ((pTMEnvironment->GetTMUnit()->IsValid() && ((pTMParameter->GetLastUpdateTMUnit() == pTMEnvironment->GetTMUnit()->GetTag() && pTMParameter->GetLastUpdateTime() == pTMEnvironment->GetTMUnit()->GetTimeTag()) || (pTMParameter->GetRawValue(nOccurrence, nValue, nStatus, szCalTable) && (m_nLayoutStatus.GetAt(nParameter) != nStatus || m_szLayoutTables.GetAt(nParameter) != szCalTable)))) || !pTMEnvironment->GetTMUnit()->IsValid())))
				{
					if (ConvertColumnToIndex(GRD_TITLEITEM_UPDATETMUNIT, nIndex))
					{
						szColumns.Add(((pTMParameter->GetAttributes() & TMPARAMETER_NATURE_CONSTANT) != TMPARAMETER_NATURE_CONSTANT  &&  pTMParameter->GetRawValue(nOccurrence, nValue, nStatus)) ? (((nStatus & TMPARAMETER_STATUS_VALID) || IsInvalidDataModeEnabled()) ? (LPCTSTR)pTMParameter->GetLastUpdateTMUnit() : EMPTYSTRING) : EMPTYSTRING);
						nColumns.Add(nIndex);
					}
					if (ConvertColumnToIndex(GRD_TITLEITEM_UPDATETIME, nIndex))
					{
						szColumns.Add((pTMParameter->IsInitialized() && (pTMParameter->GetAttributes() & TMPARAMETER_NATURE_CONSTANT) != TMPARAMETER_NATURE_CONSTANT  &&  pTMParameter->GetRawValue(nOccurrence, nValue, nStatus)) ? (((nStatus & TMPARAMETER_STATUS_VALID) || IsInvalidDataModeEnabled()) ? (LPCTSTR)pTMParameter->GetLastUpdateTime().FormatGmt() : EMPTYSTRING) : EMPTYSTRING);
						nColumns.Add(nIndex);
					}
				}
				for (nIndex = 0, nCount = (nParameter < m_wndContentCtrl.m_szContentText.GetSize() && nColumns.GetSize() == szColumns.GetSize()) ? (INT)nColumns.GetSize() : 0; nIndex < nCount; nIndex++)
				{
					if ((pAttribute = m_wndContentCtrl.m_pContentTextAttributes.GetAt(nParameter)) && m_nLayoutColumns.GetAt(nColumns.GetAt(nIndex)) == GRD_TITLEITEM_VALUE) pAttribute->SetColumnColor(nColumns.GetAt(nIndex), LookupColumnColor(m_nLayoutColumns.GetAt(nColumns.GetAt(nIndex)), (pTMParameter->GetRawValue(nOccurrence, nValue, nStatus)) ? nStatus : 0));
					SetText(nParameter, nColumns.GetAt(nIndex), szColumns.GetAt(nIndex));
				}
				if (bUpdate[2])
				{
					if (pTMParameter->IsInitialized())
					{
						tUpdate[0] = (pTMParameter->GetLastUpdateTime() < tUpdate[0] || !tUpdate[0].GetTime()) ? pTMParameter->GetLastUpdateTime() : tUpdate[0];
						tUpdate[1] = (pTMParameter->GetLastUpdateTime() > tUpdate[1] || !tUpdate[1].GetTime()) ? pTMParameter->GetLastUpdateTime() : tUpdate[1];
						bPlots.SetAt(nParameter, TRUE);
						bUpdate[0] = TRUE;
					}
					m_bLayoutValues.SetAt(nParameter, TRUE);
					m_nLayoutStatus.SetAt(nParameter, (pTMParameter->GetRawValue(nOccurrence, nValue, nStatus, szCalTable)) ? nStatus : TMPARAMETER_STATUS_NONE);
					m_szLayoutTables.SetAt(nParameter, (m_nLayoutStatus.GetAt(nParameter) != TMPARAMETER_STATUS_NONE) ? (LPCTSTR)szCalTable : EMPTYSTRING);
				}
				szColumns.RemoveAll();
				nColumns.RemoveAll();
			}
		}
	}
	if (m_cGraphPlots.GetUpdateRange(tStartTime, tStopTime) && tUpdate[2] > tStopTime)
	{
		if (GetTMService()->CheckTMStreamInterruption(tUpdate[2].GetTime() - tStopTime.GetTime()))
		{
			for (nPlot = 0, nPlots = (INT)m_cGraphPlots.GetSize(); nPlot < nPlots; nPlot = nPlot + 1)
			{
				if ((pParameterSamples = m_cGraphPlots.GetAt(nPlot)) != (CGRDParameterSamples *)NULL)
				{
					if ((pTMParameter = m_pLayoutValues.GetAt(m_pLayoutValues.Find(pParameterSamples->GetName()))))
					{
						if ((pTMParameter->GetAttributes() & TMPARAMETER_NATURE_CONSTANT) != TMPARAMETER_NATURE_CONSTANT)
						{
							pParameterSamples->SetInterruptionFlag(TRUE);
							continue;
						}
					}
				}
			}
		}
	}
	if (nParameter == nParameters)
	{
		if ((!m_tGraph[0].GetTime() || !m_tGraph[1].GetTime() || !m_tGraph[2].GetTime()) && bUpdate[0])
		{
			for (nPlot = 0, nPlots = (INT)m_cGraphPlots.GetSize(); nPlot < nPlots; nPlot = nPlot + 1)
			{
				if ((pParameterSamples = m_cGraphPlots.GetAt(nPlot)) && !pParameterSamples->GetSize())
				{
					if ((pTMParameter = m_pLayoutValues.GetAt(m_pLayoutValues.Find(pParameterSamples->GetName()))))
					{
						if (pTMParameter->GetAttributes() & TMPARAMETER_NATURE_CONSTANT)
						{
							bPlots.SetAt(nPlot, TRUE);
							continue;
						}
					}
				}
			}
			m_tGraph[0] = tUpdate[0];
			m_tGraph[1] = tUpdate[0];
			m_tGraph[2] = (m_cLayout.GetInterval().GetTotalSeconds() > 0) ? (tUpdate[0].GetTime() + 1000000 * m_cLayout.GetInterval().GetTotalSeconds()) : (tUpdate[0].GetTime() + 1000000 * (TIMETAG)m_cLayout.GetDuration().GetTotalSeconds());
		}
		for (nPlot = 0, nPlots = (INT)bPlots.GetSize(), tInterval = m_cLayout.GetUpdateInterval(); nPlot < nPlots; nPlot++)
		{
			if ((pParameterSamples = (bPlots.GetAt(nPlot) && !bParameters) ? m_cGraphPlots.GetAt(nPlot) : (CGRDParameterSamples *)NULL))
			{
				if ((pTMParameter = m_pLayoutValues.GetAt(m_pLayoutValues.Find(pParameterSamples->GetName()))))
				{
					if ((pParameter = (CGRDLayoutParameter *)m_cLayout.GetAt(nPlot)) != (CGRDLayoutParameter *)NULL)
					{
						if ((tInterval > 0 && (pTMParameter->GetLastUpdateTime().GetTimeInSeconds() - pParameterSamples->GetLastPlotTime().GetTimeInSeconds() >= tInterval.GetTotalSeconds() || pParameterSamples->GetInterruptionFlag())) || !tInterval.GetTotalSeconds())
						{
							if ((pParameterSample[0] = new CGRDParameterSample))
							{
								if (pParameterSample[0]->CTMParameter::Copy(pTMParameter))
								{
									if ((nSample[0] = pParameterSamples->Add(pParameter, pParameterSample[0])) >= 0)
									{
										for (nSample[1] = nSample[0] + 1, nSamples[1] = (INT)pParameterSamples->GetSize(), bConnected = (!pParameterSamples->GetInterruptionFlag() && pParameterSamples->GetSize() > 1), tUpdate[3] = pParameterSample[0]->GetLastUpdateTime(); nSample[1] < nSamples[1]; nSample[1]++)
										{
											if ((pParameterSample[1] = (CGRDParameterSample *)pParameterSamples->GetAt(nSample[1])) != (CGRDParameterSample *)NULL)
											{
												for (tUpdate[3] = pParameterSample[1]->GetUpdateTime(), bConnected = (nSample[1] == nSample[0] + 1) ? pParameterSample[1]->IsConnected() : bConnected; pParameterSample[1]->IsDummy(); )
												{
													pParameterSample[1]->CTMParameter::Copy(pParameterSample[0]);
													pParameterSample[1]->SetUpdateTMUnit(szUpdate[0]);
													pParameterSample[1]->SetUpdateTime(tUpdate[3]);
													break;
												}
												pParameterSample[1]->DoConnect((!pParameterSample[1]->IsDummy() || nSample[1] > nSample[0] + 1) ? pParameterSample[1]->IsConnected() : TRUE);
											}
										}
										pParameterSample[0]->DoConnect(bConnected);
										pParameterSamples->SetLastPlotTime(tUpdate[3]);
										pParameterSamples->SetInterruptionFlag((nSample[0] < pParameterSamples->GetSize() - 1) ? pParameterSamples->GetInterruptionFlag() : FALSE);
										tUpdate[0] = min(tUpdate[0], tUpdate[3]);
										tUpdate[1] = max(tUpdate[1], tUpdate[3]);
										bUpdate[1] = TRUE;
										continue;
									}
								}
								delete pParameterSample[0];
							}
						}
					}
				}
			}
			if ((pParameterSamples = (m_cLayout.GetType() != GRDLAYOUT_TYPE_DIAGRAM  &&  !bPlots.GetAt(nPlot) && !bParameters) ? m_cGraphPlots.GetAt(nPlot) : (CGRDParameterSamples *)NULL))
			{
				if ((pTMParameter = m_pLayoutValues.GetAt(m_pLayoutValues.Find(pParameterSamples->GetName()))) && pTMParameter->IsInitialized())
				{
					if ((pParameter = (CGRDLayoutParameter *)m_cLayout.GetAt(nPlot)) != (CGRDLayoutParameter *)NULL)
					{
						if ((tInterval > 0 && (tUpdate[2] >= pParameterSamples->GetLastPlotTime() && tUpdate[2].GetTimeInSeconds() - pParameterSamples->GetLastPlotTime().GetTimeInSeconds() >= tInterval.GetTotalSeconds() || pParameterSamples->GetInterruptionFlag())) || (!tInterval.GetTotalSeconds() && tUpdate[2] >= pParameterSamples->GetLastPlotTime() && tUpdate[2].GetTime() - pParameterSamples->GetLastPlotTime().GetTime() >= (m_tGraph[2].GetTime() - m_tGraph[1].GetTime()) / GetGraphSize().cx))
						{
							if ((pParameterSample[0] = new CGRDParameterSample) != (CGRDParameterSample *)NULL)
							{
								if (pParameterSample[0]->CTMParameter::Copy(pTMParameter))
								{
									pParameterSample[0]->SetUpdateTime(tUpdate[2]);
									pParameterSample[0]->SetUpdateTMUnit(szUpdate[0]);
									if (pParameterSamples->Add(pParameter, pParameterSample[0]) >= 0)
									{
										pParameterSample[0]->DoConnect(!pParameterSamples->GetInterruptionFlag() && pParameterSamples->GetSize() > 1);
										pParameterSamples->SetLastPlotTime(tUpdate[2]);
										pParameterSamples->SetInterruptionFlag(FALSE);
										tUpdate[0] = (tUpdate[0] > tUpdate[2] || !tUpdate[0].GetTime()) ? tUpdate[2] : tUpdate[0];
										tUpdate[1] = (tUpdate[1] < tUpdate[2] || !tUpdate[1].GetTime()) ? tUpdate[2] : tUpdate[1];
										bUpdate[1] = TRUE;
										continue;
									}
								}
								delete pParameterSample[0];
							}
						}
					}
				}
			}
		}
		if (bUpdate[1])
		{
			for (nPlot = 0, nPlots = (INT)m_cGraphPlots.GetSize(), bUpdate[2] = FALSE; nPlot < nPlots; nPlot++)
			{
				if ((pParameter = (CGRDLayoutParameter *)m_cLayout.GetAt(nPlot)) != (CGRDLayoutParameter *)NULL)
				{
					if ((pParameterSamples = (CGRDParameterSamples *)m_cGraphPlots.GetAt(nPlot)) != (CGRDParameterSamples *)NULL)
					{
						if (pParameter->GetAutoScaleDelay() > 0 && !pParameter->GetAutoScaleDelay().GetTotalMinutes() && pParameter->GetRange(fMin[0], fMax[0]) && pParameterSamples->GetRange(fMin[1], fMax[1]) && fMin[1] != fMax[1])
						{
							if (fMin[0] > fMin[1] || fMax[0] < fMax[1])
							{
								pParameter->GetMargin(nMargin[0], nMargin[1]);
								fMin[0] = fMin[1] - ((double)max(nMargin[0], 0)*(fMax[1] - fMin[1])) / 100.0;
								fMax[0] = fMax[1] + ((double)max(nMargin[1], 0)*(fMax[1] - fMin[1])) / 100.0;
								fDigits = (m_cLayout.GetType() == GRDLAYOUT_TYPE_DIAGRAM  &&  nPlot % 2 == 0) ? ((!m_cLayout.GetPlotSize().cx) ? GRDLAYOUT_GRAPH_WIDTH : m_cLayout.GetPlotSize().cx) : ((!m_cLayout.GetPlotSize().cy) ? GRDLAYOUT_GRAPH_HEIGHT : m_cLayout.GetPlotSize().cy);
								fDigits = pow(10.0, floor(log10(fDigits)) - floor(log10(fMax[1] - fMin[1])));
								fMin[0] = floor(fMin[0] * fDigits - 1.0) / fDigits;
								fMax[0] = floor(fMax[0] * fDigits + 1.0) / fDigits;
								pParameter->SetRange(fMin[0], fMax[0]);
								bUpdate[2] = TRUE;
							}
						}
					}
				}
			}
			if (bUpdate[2])
			{
				UpdateGraphScaling();
				UpdateGraph();
				RecalcLayout();
			}
		}
	}
	if (nParameter != nParameters)
	{
		for (nPlot = 0, nPlots = (m_cLayout.GetType() != GRDLAYOUT_TYPE_DIAGRAM && !bParameters) ? (INT)m_cGraphPlots.GetSize() : 0, tInterval = m_cLayout.GetUpdateInterval(); nPlot < nPlots; nPlot++)
		{
			if ((pParameterSamples = (CGRDParameterSamples *)m_cGraphPlots.GetAt(nPlot)) != (CGRDParameterSamples *)NULL)
			{
				if ((pTMParameter = m_pLayoutValues.GetAt(m_pLayoutValues.Find(pParameterSamples->GetName()))) && pTMParameter->IsInitialized())
				{
					if ((pParameter = (CGRDLayoutParameter *)m_cLayout.GetAt(nPlot)) != (CGRDLayoutParameter *)NULL)
					{
						if ((tInterval > 0 && (tUpdate[2] >= pParameterSamples->GetLastPlotTime() && tUpdate[2].GetTimeInSeconds() - pParameterSamples->GetLastPlotTime().GetTimeInSeconds() >= tInterval.GetTotalSeconds() || pParameterSamples->GetInterruptionFlag())) || (!tInterval.GetTotalSeconds() && tUpdate[2] >= pParameterSamples->GetLastPlotTime() && tUpdate[2].GetTime() - pParameterSamples->GetLastPlotTime().GetTime() >= (m_tGraph[2].GetTime() - m_tGraph[1].GetTime()) / GetGraphSize().cx))
						{
							if ((pParameterSample[0] = new CGRDParameterSample) != (CGRDParameterSample *)NULL)
							{
								if (pParameterSample[0]->CTMParameter::Copy(pTMParameter))
								{
									pParameterSample[0]->SetUpdateTime(tUpdate[2]);
									pParameterSample[0]->SetUpdateTMUnit(szUpdate[0]);
									if (pParameterSamples->Add(pParameter, pParameterSample[0]) >= 0)
									{
										pParameterSample[0]->DoConnect(!pParameterSamples->GetInterruptionFlag() && pParameterSamples->GetSize() > 1);
										pParameterSamples->SetLastPlotTime(tUpdate[2]);
										pParameterSamples->SetInterruptionFlag(FALSE);
										tUpdate[0] = tUpdate[2];
										tUpdate[1] = tUpdate[2];
										bUpdate[1] = TRUE;
										continue;
									}
								}
								delete pParameterSample[0];
							}
						}
					}
				}
			}
		}
	}
	for (tUpdate[0] = (tUpdate[0] > 0) ? tUpdate[0] : tUpdate[2], tUpdate[1] = (tUpdate[1] > 0) ? tUpdate[1] : tUpdate[2]; tUpdate[0] > 0 || tUpdate[1] > 0 || tUpdate[2] > 0; )
	{
		m_cGraphPlots.SetUpdateRange(tUpdate[0], (tUpdate[3] = (m_cGraphPlots.GetUpdateRange(tStartTime, tStopTime)) ? max(tUpdate[1], (tUpdate[2] = max(tStopTime, tUpdate[2]))) : max(tUpdate[1], tUpdate[2])));
		break;
	}
	for (; bUpdate[1] || tUpdate[1] < tUpdate[2] || (tStopTime < tUpdate[3] && tStopTime > 0); )
	{
		UpdateGraph(tUpdate[0], min(max(tUpdate[1], tUpdate[2]), m_tGraph[2]));
		break;
	}
	if (!bParameters)
	{
		if (tUpdate[2] >= m_tGraph[2] && m_tGraph[0] > 0)
		{
			if ((m_cLayout.GetMode() & GRDLAYOUT_MODE_OVERWRITE) != GRDLAYOUT_MODE_OVERWRITE)
			{
				if (m_tGraph[2].GetTimeInSeconds() - m_tGraph[0].GetTimeInSeconds() >= m_cLayout.GetDuration().GetTotalSeconds() || (m_cLayout.GetInterval() > 0 && m_tGraph[2].GetTimeInSeconds() - m_tGraph[0].GetTimeInSeconds() >= m_cLayout.GetInterval().GetTotalSeconds()) || m_ptGraph.x >= INT_MAX - GetSystemMetrics(SM_CXSCREEN))
				{
					for (GetParent()->ExecutePrintJobs(); (m_cLayout.GetMode() & GRDLAYOUT_MODE_SCROLL) != GRDLAYOUT_MODE_SCROLL || (m_tGraph[2].GetTimeInSeconds() - m_tGraph[0].GetTimeInSeconds() >= m_cLayout.GetDuration().GetTotalSeconds() && m_cLayout.GetInterval() > 0); )
					{
						for (bRange = m_cGraphPlots.GetUpdateRange(tRange[0], tRange[1]), Reset(), Initialize(szUpdate[1], tUpdate[3]); bRange; )
						{
							RestartGraph(tRange[0], tRange[1]);
							break;
						}
						break;
					}
					if (m_cLayout.GetMode() & GRDLAYOUT_MODE_SCROLL) ScrollGraph(m_tGraph[1], m_tGraph[2], tUpdate[2]);
				}
			}
			else  OverwriteGraph(m_tGraph[1], m_tGraph[2], tUpdate[2]);
		}
	}
	if (m_wndToolTip.IsVisibleAtPoint(ptToolTip))
	{
		if ((pParameter = (FindTextFromPoint(ptToolTip, nRow, nColumn, FALSE)) ? m_cLayout.GetAt(nRow) : (CGRDLayoutParameter *)NULL))
		{
			for (szTitle = ConstructToolTipTitle(pParameter, m_nLayoutColumns.GetAt(nColumn)), szText = ConstructToolTipText(pParameter, pParameter->GetOccurrence(), m_nLayoutColumns.GetAt(nColumn)); !szTitle.IsEmpty() || !szText.IsEmpty(); )
			{
				m_wndToolTip.Update(szTitle, szText);
				break;
			}
		}
	}
	return bUpdate[0];
}

VOID CGRDView::Reset(CTMEnvironment *pTMEnvironment)
{
	CTextViewLock  cLock(this);

	m_ptGraph.x = 0;
	m_ptGraph.y = 0;
	m_tGraph[0] = 0;
	m_tGraph[1] = 0;
	m_tGraph[2] = 0;
	m_bGraphUpdate = TRUE;
	m_cGraphBits.RemoveAll();
	m_cGraphPlots.RemoveAll();
	m_bLayoutValues.RemoveAll();
	m_nLayoutStatus.RemoveAll();
	m_szLayoutTables.RemoveAll();
	m_bLayoutValues.SetSize(m_cLayout.GetSize());
	m_nLayoutStatus.SetSize(m_cLayout.GetSize());
	m_szLayoutTables.SetSize(m_cLayout.GetSize());
	m_pLayoutValues.Reset();
	Update();
}

VOID CGRDView::SetHoldFlag(BOOL bEnable)
{
	m_bGraphUpdate = !bEnable;
}

BOOL CGRDView::GetHoldFlag() CONST
{
	return !m_bGraphUpdate;
}

BOOL CGRDView::HasHoldFlag() CONST
{
	CTextViewLock  cLock(this);

	return((m_cLayout.GetType() != GRDLAYOUT_TYPE_DIAGRAM) ? TRUE : FALSE);
}

BOOL CGRDView::GetParameterInfo(LPCTSTR pszTag, INT nIndex, CTMParameter *pTMParameter, CGRDParameterSamples &pParameterSamples) CONST
{
	INT  nParameter;
	INT  nParameters;
	CGRDParameterSamples  *pSamples;
	CTextViewLock  cLock(this);

	for (nParameter = m_pLayoutValues.Find(pszTag), nParameters = (INT)m_pLayoutValues.GetSize(); nParameter < nParameters && nParameter >= 0; )
	{
		if ((pSamples = m_cGraphPlots.GetAt(nIndex)) != (CGRDParameterSamples *)NULL  &&  pSamples->GetName() == pszTag)
		{
			if (pTMParameter->Copy(m_pLayoutValues.GetAt(nParameter)) && pParameterSamples.Copy(pSamples)) break;
			continue;
		}
	}
	return((nParameter < nParameters) ? TRUE : FALSE);
}

BOOL CGRDView::HasParameters() CONST
{
	CTextViewLock  cLock(this);

	return((m_cLayout.GetSize() > 0) ? TRUE : FALSE);
}

VOID CGRDView::ReduceFonts(BOOL bRestore)
{
	BOOL  bSuccess;
	CFont  cFont[4];
	LOGFONT  lfFont[4];
	CUIntArray  nWidths;
	CStringArray  szColumns;
	CTextViewLock  cLock(this);

	if (!bRestore)
	{
		if (m_wndHeaderCtrl.m_cFont.GetLogFont(&lfFont[0]) > 0 && m_wndContentCtrl.m_cFont.GetLogFont(&lfFont[1]) > 0 && m_cLayoutFont[0].GetLogFont(&lfFont[2]) > 0 && m_cLayoutFont[1].GetLogFont(&lfFont[3]) > 0)
		{
			for (lfFont[0].lfHeight = (9 * lfFont[0].lfHeight) / 10, lfFont[1].lfHeight = (9 * lfFont[1].lfHeight) / 10, lfFont[2].lfHeight = (9 * lfFont[2].lfHeight) / 10, lfFont[3].lfHeight = (9 * lfFont[3].lfHeight) / 10, lfFont[0].lfWidth = lfFont[1].lfWidth = lfFont[2].lfWidth = lfFont[3].lfWidth = 0, lfFont[0].lfOutPrecision = lfFont[1].lfOutPrecision = lfFont[2].lfOutPrecision = lfFont[3].lfOutPrecision = OUT_TT_ONLY_PRECIS; bSuccess = cFont[0].CreateFontIndirect(&lfFont[0]) && cFont[1].CreateFontIndirect(&lfFont[1]) && cFont[2].CreateFontIndirect(&lfFont[2]) && cFont[3].CreateFontIndirect(&lfFont[3]); )
			{
				bSuccess &= m_wndHeaderCtrl.m_cFont.DeleteObject() && m_wndHeaderCtrl.m_cFont.Attach(cFont[0].Detach());
				bSuccess &= m_wndContentCtrl.m_cFont.DeleteObject() && m_wndContentCtrl.m_cFont.Attach(cFont[1].Detach());
				bSuccess &= m_cLayoutFont[0].DeleteObject() && m_cLayoutFont[0].Attach(cFont[2].Detach());
				bSuccess &= m_cLayoutFont[1].DeleteObject() && m_cLayoutFont[1].Attach(cFont[3].Detach());
				break;
			}
			if (bSuccess)
			{
				for (SetTitleFont(&m_wndHeaderCtrl.m_cFont, !(m_bLayoutFont = TRUE)), SetItemsFont(&m_wndContentCtrl.m_cFont, FALSE), SetValuesFont(&m_cLayoutFont[0], FALSE), SetAxesFont(&m_cLayoutFont[1], FALSE), m_cLayout.SetPlotSize(CalcPlotAreaExtent()), UpdateGraph(), CalcColumnsWidth(nWidths); GetColumns(szColumns); )
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
	for (SetTitleFont(&m_lfLayoutDefault[0], !(m_bLayoutFont = TRUE)), SetItemsFont(&m_lfLayoutDefault[1], FALSE), SetValuesFont(&m_lfLayoutDefault[2], FALSE), SetAxesFont(&m_lfLayoutDefault[3], FALSE), m_cLayout.SetPlotSize(m_sizeLayoutDefault), UpdateGraph(), CalcColumnsWidth(nWidths); GetColumns(szColumns); )
	{
		SetColumns(szColumns, nWidths);
		break;
	}
	m_bLayoutFont = FALSE;
	RecalcContent();
}

BOOL CGRDView::CanReduceFonts(BOOL bRestore) CONST
{
	LOGFONT  lfFont[4];
	CTextViewLock  cLock(this);

	return((GetTitleFont(&lfFont[0], FALSE) && GetItemsFont(&lfFont[1], FALSE) && GetValuesFont(&lfFont[2], FALSE) && GetAxesFont(&lfFont[3], FALSE)) ? ((!bRestore  &&  abs(lfFont[0].lfHeight) > 10 && abs(lfFont[1].lfHeight) > 10 && abs(lfFont[2].lfHeight) > 10 && abs(lfFont[3].lfHeight) > 10) || (bRestore && (memcmp(&m_lfLayoutDefault[0], &lfFont[0], sizeof(LOGFONT)) || memcmp(&m_lfLayoutDefault[1], &lfFont[1], sizeof(LOGFONT)) || memcmp(&m_lfLayoutDefault[2], &lfFont[2], sizeof(LOGFONT)) || memcmp(&m_lfLayoutDefault[3], &lfFont[3], sizeof(LOGFONT))))) : FALSE);
}

VOID CGRDView::ReducePlotArea(BOOL bRestore)
{
	CSize  sizePlot[2];
	CTextViewLock  cLock(this);

	if (!bRestore)
	{
		if (CanReduceFonts(TRUE))
		{
			m_cLayout.SetPlotSize(CalcPlotAreaExtent());
			UpdateGraph();
			RecalcLayout();
		}
		return;
	}
	if (m_cLayout.GetPlotSize() != m_sizeLayoutDefault)
	{
		m_cLayout.SetPlotSize(m_sizeLayoutDefault);
		UpdateGraph();
		RecalcLayout();
	}
}

BOOL CGRDView::GetPrintProperties(CGRDLayout &cLayout, CStringArray &szColumns, CStringArray &szContents, CTMParameters &pValues, CUIntArray &nOOLColors, LOGFONT *pTitleFont, CPtrArray &pItemsFonts, CMetaFileDC &cMetaDC, CSize &sizeImage, UINT &nImageIndent) CONST
{
	INT  nColumn;
	INT  nColumns;
	CRect  rImage;
	CRect  rGraph;
	LOGFONT  *plfFont;
	CGRDView  *pView;
	CClientDC  cDC(NULL);
	CTextViewAttributes  pAttributes;
	CTextViewLock  cLock(this);

	if (cMetaDC.CreateEnhanced(&cDC, (LPCTSTR)NULL, (LPCRECT)NULL, (LPCTSTR)NULL))
	{
		for (nColumn = 0, nColumns = (GetLayout(cLayout) && GetColumns(szColumns) && GetContent(szContents, pAttributes) && GetTitleFont(pTitleFont) && GetOolColors(nOOLColors) && pValues.Copy(&m_pLayoutValues)) ? (INT)szColumns.GetSize() : -1, cMetaDC.SetAttribDC(cDC.GetSafeHdc()); nColumn < nColumns; nColumn++)
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
		if (nColumn == nColumns)
		{
			for (rImage = GetImagePosition(), rGraph = GetGraphPosition(), sizeImage.cx = rImage.Width(), sizeImage.cy = rImage.Height(), nImageIndent = rGraph.left - rImage.left; (pView = (CGRDView *) this); )
			{
				pView->DrawGraph(&cMetaDC);
				pView->UpdateGraph(&cMetaDC);
				pView->DrawSlider(&cMetaDC);
				break;
			}
			return TRUE;
		}
		DeleteEnhMetaFile(cMetaDC.CloseEnhanced());
	}
	return FALSE;
}

VOID CGRDView::DrawContent(CDC *pDC)
{
	INT  nItem;
	INT  nItems;
	INT  nColumn;
	INT  nColumns;
	CRect  rText;
	CRect  rImage;
	CRect  rContent;
	CStringArray  szColumns;

	if (!m_bLayoutFont)
	{
		for (m_wndContentCtrl.GetClientRect(rContent), rText = m_wndContentCtrl.CalcTextRect(GetTextCount() - 1), rImage = GetImagePosition(); !rContent.IsRectEmpty(); )
		{
			pDC->FillSolidRect(CRect(min(rText.right + m_wndContentCtrl.m_wTextIndent[1], rContent.right), rContent.top, rContent.right, min(max(rText.bottom + m_wndContentCtrl.m_wTextSpacing[1], rContent.top), rContent.bottom)), GetSysColor(COLOR_WINDOW));
			pDC->FillSolidRect(0, rImage.top - m_wndContentCtrl.m_nScrollPos[1], max(m_wndContentCtrl.m_wTextIndent[0] - m_wndContentCtrl.m_nScrollPos[0], 0), rImage.Height(), GetSysColor(COLOR_WINDOW));
			pDC->FillSolidRect(rImage.right - m_wndContentCtrl.m_nScrollPos[0], rImage.top - m_wndContentCtrl.m_nScrollPos[1], max(rContent.Width() - rImage.right + m_wndContentCtrl.m_nScrollPos[0], 0), rImage.Height(), GetSysColor(COLOR_WINDOW));
			pDC->FillSolidRect(0, rImage.bottom - m_wndContentCtrl.m_nScrollPos[1], rContent.Width(), max(rContent.Height() - rImage.bottom + m_wndContentCtrl.m_nScrollPos[1], 0), GetSysColor(COLOR_WINDOW));
			break;
		}
		for (nItem = FindFirstVisibleText(), nItems = FindLastVisibleText() + 1, nItems = min(GetTextCount() - 1, nItems); nItem >= 0 && nItem <= nItems; nItem++)
		{
			for (nColumn = 0, nColumns = ConvertText(m_wndContentCtrl.m_szContentText.GetAt(nItem), szColumns), nColumns = (INT)m_wndHeaderCtrl.m_szColumnsText.GetSize(); nColumn < nColumns; nColumn++)
			{
				if (LookupColumnName(m_wndHeaderCtrl.m_szColumnsText.GetAt(nColumn)) != GRD_TITLEITEM_LINE) m_wndContentCtrl.DrawText(pDC, nItem, nColumn, (nColumn < szColumns.GetSize()) ? (LPCTSTR)szColumns.GetAt(nColumn) : EMPTYSTRING);
				continue;
			}
		}
		DrawLegend(pDC);
		DrawImage(pDC);
	}
}

CGRDWnd *CGRDView::GetParent() CONST
{
	return((CGRDWnd *)CTextView::GetParent());
}

VOID CGRDView::DrawImage()
{
	CDC  *pDC;

	if ((pDC = m_wndContentCtrl.GetDC()))
	{
		DrawLegend(pDC);
		DrawImage(pDC);
		m_wndContentCtrl.ReleaseDC(pDC);
	}
}
VOID CGRDView::DrawImage(CDC *pDC)
{
	CDC  cDC;
	CRect  rImage;
	CBitmap  cBitmap;
	CBitmap  *pOldBitmap;

	if (cDC.CreateCompatibleDC(pDC))
	{
		for (rImage = GetImagePosition(); cBitmap.CreateCompatibleBitmap(pDC, rImage.Width(), rImage.Height()); )
		{
			if ((pOldBitmap = cDC.SelectObject(&cBitmap)))
			{
				cDC.SetViewportOrg(-rImage.left, -rImage.top);
				DrawGraph(&cDC);
				DrawSlider(&cDC);
				pDC->BitBlt(rImage.left - m_wndContentCtrl.m_nScrollPos[0], rImage.top - m_wndContentCtrl.m_nScrollPos[1], rImage.Width(), rImage.Height(), &cDC, rImage.left, rImage.top, SRCCOPY);
				cDC.SelectObject(pOldBitmap);
			}
			cBitmap.DeleteObject();
			break;
		}
		cDC.DeleteDC();
	}
}

VOID CGRDView::DrawGraph(CDC *pDC)
{
	CDC  cDC[2];
	INT  nXPos;
	INT  nYPos;
	INT  nBkMode;
	INT  nMarker;
	INT  nMarkers;
	INT  nGrid[2];
	INT  nTick[2];
	INT  nGrids[2];
	INT  nTicks[2];
	INT  nParameter;
	INT  nParameters;
	HPEN  hGridsPen;
	HPEN  hTicksPen;
	HPEN  hOldPen;
	CRect  rImage;
	CRect  rGraph;
	CSize  sizeStubs;
	CSize  sizeText[2];
	CSize  sizePlot[2];
	CFont  *pOldFont;
	CPoint  ptMarker;
	double  fMinimum;
	double  fMaximum;
	CString  szMinimum;
	CString  szMaximum;
	CBitmap  cBitmap[2];
	CBitmap  *pOldBitmap[2];
	CTimeKey  tTimeKey[2];
	COLORREF  nColor[1];
	LOGBRUSH  sPenBrush[2];
	CGRDMarker  *pMarker;
	TEXTMETRIC  tmFont[1];
	CByteArray  nGraphBits;
	CUIntArray  nGraphSlots;
	CGRDLayoutParameter  *pParameter;
	CCompressionTools  cCompressionTools;

	for (sPenBrush[0].lbStyle = sPenBrush[1].lbStyle = BS_SOLID, sPenBrush[0].lbColor = m_cLayout.GetGridsColor(), sPenBrush[1].lbColor = m_cLayout.GetTicksColor(), sPenBrush[0].lbHatch = sPenBrush[1].lbHatch = (ULONG_PTR)NULL; (hGridsPen = ExtCreatePen(PS_GEOMETRIC | PS_ENDCAP_FLAT | PS_SOLID, m_cLayout.GetGridsWidth(), &sPenBrush[0], 0, (CONST DWORD *) NULL)); )
	{
		if ((hTicksPen = ExtCreatePen(PS_GEOMETRIC | PS_ENDCAP_FLAT | PS_SOLID, m_cLayout.GetTicksWidth(), &sPenBrush[1], 0, (CONST DWORD *) NULL)))
		{
			pDC->FillSolidRect((rImage = GetImagePosition()), GetSysColor(COLOR_WINDOW));
			pDC->FillSolidRect((rGraph = GetGraphPosition()), m_cLayout.GetBackgroundColor());
			if ((hOldPen = (HPEN)SelectObject(pDC->GetSafeHdc(), hGridsPen)) != (HPEN)NULL)
			{
				for (nGrid[0] = 0, nGrids[0] = (m_cLayout.GetGrids(nGrids[0], nGrids[1])) ? nGrids[0] : 0, sizeStubs = GetAxesStubs(); nGrid[0] < nGrids[0]; nGrid[0]++)
				{
					pDC->MoveTo((nXPos = rGraph.left + ((nGrid[0] * rGraph.Width()) / nGrids[0])), rGraph.top - sizeStubs.cy);
					pDC->LineTo(nXPos, rGraph.bottom + sizeStubs.cy);
				}
				for (nGrid[1] = 0, nGrids[1] = (m_cLayout.GetType() != GRDLAYOUT_TYPE_STRIPCHART) ? ((m_cLayout.GetGrids(nGrids[0], nGrids[1])) ? nGrids[1] : 0) : (INT)m_nLayoutSlots.GetSize(); nGrid[1] < nGrids[1]; nGrid[1]++)
				{
					pDC->MoveTo(rGraph.left - sizeStubs.cx, (nYPos = rGraph.bottom - (nGrid[1] * rGraph.Height()) / nGrids[1]));
					pDC->LineTo(rGraph.right + sizeStubs.cx, nYPos);
				}
				for (nMarker = 0, nMarkers = (m_cLayout.GetType() == GRDLAYOUT_TYPE_DIAGRAM) ? (INT)m_pLayoutMarkers.GetSize() : 0; nMarker < nMarkers; nMarker++)
				{
					if ((pMarker = m_pLayoutMarkers.GetAt(nMarker)))
					{
						sizePlot[0] = m_cLayout.GetPlotSize();
						sizePlot[1].cx = m_sizeLayoutDefault.cx;
						sizePlot[1].cy = m_sizeLayoutDefault.cy;
						sizePlot[0].cx = (!sizePlot[0].cx) ? GRDLAYOUT_GRAPH_WIDTH : sizePlot[0].cx;
						sizePlot[0].cy = (!sizePlot[0].cy) ? GRDLAYOUT_GRAPH_HEIGHT : sizePlot[0].cy;
						sizePlot[1].cx = (!sizePlot[1].cx) ? GRDLAYOUT_GRAPH_WIDTH : sizePlot[1].cx;
						sizePlot[1].cy = (!sizePlot[1].cy) ? GRDLAYOUT_GRAPH_HEIGHT : sizePlot[1].cy;
						ptMarker.x = (pMarker->x*sizePlot[0].cx) / sizePlot[1].cx;
						ptMarker.y = (pMarker->y*sizePlot[0].cy) / sizePlot[1].cy;
						pDC->MoveTo(rGraph.left + ptMarker.x - sizeStubs.cx, rGraph.top + ptMarker.y);
						pDC->LineTo(rGraph.left + ptMarker.x + sizeStubs.cx + 1, rGraph.top + ptMarker.y);
						pDC->MoveTo(rGraph.left + ptMarker.x, rGraph.top + ptMarker.y - sizeStubs.cy);
						pDC->LineTo(rGraph.left + ptMarker.x, rGraph.top + ptMarker.y + sizeStubs.cy + 1);
					}
				}
				SelectObject(pDC->GetSafeHdc(), hOldPen);
			}
			if ((hOldPen = (HPEN)SelectObject(pDC->GetSafeHdc(), hTicksPen)))
			{
				for (nTick[0] = 0, nTicks[0] = (m_cLayout.GetTicks(nTicks[0], nTicks[1])) ? nTicks[0] : 0; nTick[0] < nTicks[0]; nTick[0]++)
				{
					pDC->MoveTo((nXPos = rGraph.left + ((nTick[0] * rGraph.Width()) / nTicks[0])), rGraph.bottom - sizeStubs.cy + 1 + 1);
					pDC->LineTo(nXPos, rGraph.bottom + sizeStubs.cy - 1);
				}
				for (nTick[1] = 0, nTicks[1] = (m_cLayout.GetTicks(nTicks[0], nTicks[1])) ? nTicks[1] : 0; nTick[1] < nTicks[1]; nTick[1]++)
				{
					pDC->MoveTo(rGraph.left - sizeStubs.cx + 1 + 1, (nYPos = rGraph.bottom - (nTick[1] * rGraph.Height()) / nTicks[1]));
					pDC->LineTo(rGraph.left + sizeStubs.cx - 1, nYPos);
				}
				SelectObject(pDC->GetSafeHdc(), hOldPen);
			}
			if ((pOldFont = pDC->SelectObject(&m_cLayoutFont[1])))
			{
				if (pDC->GetTextMetrics(&tmFont[0]) > 0)
				{
					nBkMode = pDC->SetBkMode(TRANSPARENT);
					if (m_cLayout.GetType() == GRDLAYOUT_TYPE_NORMAL || m_cLayout.GetType() == GRDLAYOUT_TYPE_STRIPCHART || m_cLayout.GetType() == GRDLAYOUT_TYPE_STACKCHART)
					{
						nColor[0] = pDC->SetTextColor(m_cLayout.GetLabelColor());
						sizeText[0] = pDC->GetTextExtent(STRING(IDS_GRD_GRAPHTEXT_AXESTIME));
						pDC->TextOut((rGraph.left + rGraph.right - sizeText[0].cx) / 2, rGraph.bottom + GetAxesStubs().cy, STRING(IDS_GRD_GRAPHTEXT_AXESTIME));
						pDC->SetTextColor(nColor[0]);
					}
					if (m_cLayout.GetType() == GRDLAYOUT_TYPE_STRIPCHART)
					{
						for (nParameter = 0, nParameters = (INT)m_cLayout.GetSize(), nGraphSlots.SetSize(m_nLayoutSlots.GetSize()); nParameter < nParameters; nParameter++)
						{
							if ((pParameter = m_cLayout.GetAt(nParameter)) && pParameter->GetPosition() >= 0)
							{
								if (pParameter->GetPosition() < nGraphSlots.GetSize())
								{
									nColor[0] = pDC->SetTextColor((pParameter->GetColor() == GetSysColor(COLOR_WINDOW)) ? GetDatabase()->GetGRDIDColumnColor() : pParameter->GetColor());
									pDC->DrawText(pParameter->GetName(), CRect(rImage.left, max(rGraph.bottom - (((INT)nGraphSlots.GetSize() - pParameter->GetPosition())*rGraph.Height()) / (INT)nGraphSlots.GetSize() + rGraph.Height() / (2 * (INT)m_nLayoutSlots.GetAt(pParameter->GetPosition())*(INT)nGraphSlots.GetSize()) + ((INT)nGraphSlots.GetAt(pParameter->GetPosition())*rGraph.Height()) / ((INT)m_nLayoutSlots.GetAt(pParameter->GetPosition())*(INT)nGraphSlots.GetSize()) - tmFont[0].tmHeight / 2, rGraph.bottom - (((INT)m_nLayoutSlots.GetSize() - pParameter->GetPosition())*rGraph.Height()) / (INT)m_nLayoutSlots.GetSize()), rGraph.left - 1, rGraph.bottom - (((INT)m_nLayoutSlots.GetSize() - pParameter->GetPosition() - 1)*rGraph.Height()) / (INT)m_nLayoutSlots.GetSize()), DT_LEFT | DT_END_ELLIPSIS | DT_SINGLELINE);
									if (pParameter->GetRange(fMinimum, fMaximum) && m_nLayoutSlots.GetAt(pParameter->GetPosition()) == 1 && rGraph.Height() / m_nLayoutSlots.GetSize() >= (INT)(m_nLayoutSlots.GetAt(pParameter->GetPosition()) + 2)*tmFont[0].tmHeight + 2)
									{
										ConvertAxesRangeValues(pParameter, fMinimum, fMaximum, szMinimum, szMaximum);
										pDC->DrawText(szMinimum + SPACE, CRect(rImage.left, rGraph.bottom - (((INT)m_nLayoutSlots.GetSize() - pParameter->GetPosition() - 1)*rGraph.Height()) / (INT)m_nLayoutSlots.GetSize() - tmFont[0].tmHeight - 1, rGraph.left - 1, rGraph.bottom - (((INT)m_nLayoutSlots.GetSize() - pParameter->GetPosition() - 1)*rGraph.Height()) / (INT)m_nLayoutSlots.GetSize() - 1), DT_RIGHT | DT_SINGLELINE);
										pDC->DrawText(szMaximum + SPACE, CRect(rImage.left, rGraph.bottom - (((INT)m_nLayoutSlots.GetSize() - pParameter->GetPosition())*rGraph.Height()) / (INT)m_nLayoutSlots.GetSize() + 1, rGraph.left - 1, rGraph.bottom - (((INT)m_nLayoutSlots.GetSize() - pParameter->GetPosition())*rGraph.Height()) / (INT)m_nLayoutSlots.GetSize() + tmFont[0].tmHeight + 1), DT_RIGHT | DT_SINGLELINE);
									}
									nGraphSlots.SetAt(pParameter->GetPosition(), nGraphSlots.GetAt(pParameter->GetPosition()) + 1);
									pDC->SetTextColor(nColor[0]);
								}
							}
						}
					}
					if (m_cLayout.GetType() == GRDLAYOUT_TYPE_DIAGRAM)
					{
						for (nParameter = 0, nParameters = (INT)m_cLayout.GetSize(); nParameter < nParameters; nParameter += 2)
						{
							if ((pParameter = m_cLayout.GetAt(nParameter)) != (CGRDLayoutParameter *)NULL)
							{
								nColor[0] = pDC->SetTextColor((pParameter->GetColor() == GetSysColor(COLOR_WINDOW)) ? GetDatabase()->GetGRDIDColumnColor() : pParameter->GetColor());
								sizeText[0] = pDC->GetTextExtent(pParameter->GetName());
								sizeText[1] = pDC->GetTextExtent(tTimeKey[0].FormatGmt());
								pDC->TextOut(rGraph.left + sizeText[1].cx + (nParameter / 2 + 1)*((rGraph.Width() - sizeText[0].cx - 2 * sizeText[1].cx) / (nParameters / 2 + 1)), rGraph.bottom + GetAxesStubs().cy, pParameter->GetName());
								pDC->SetTextColor(nColor[0]);
							}
							if ((pParameter = m_cLayout.GetAt(nParameter + 1)))
							{
								nColor[0] = pDC->SetTextColor((pParameter->GetColor() == GetSysColor(COLOR_WINDOW)) ? GetDatabase()->GetGRDIDColumnColor() : pParameter->GetColor());
								sizeText[0] = pDC->GetTextExtent(pParameter->GetName());
								pDC->TextOut(rImage.left, rGraph.bottom - (nParameter / 2 + 1)*(rGraph.Height() / (nParameters / 2 + 1)) - sizeText[0].cy / 2, pParameter->GetName());
								pDC->SetTextColor(nColor[0]);
							}
						}
					}
					tTimeKey[0] = m_tGraph[1].GetTimeInSeconds();
					tTimeKey[1] = m_tGraph[2].GetTimeInSeconds();
					sizeText[1] = pDC->GetTextExtent(tTimeKey[1].FormatGmt());
					if (tTimeKey[0].GetTime() > 0 && tTimeKey[1].GetTime() > 0)
					{
						nColor[0] = pDC->SetTextColor(m_cLayout.GetLabelColor());
						pDC->TextOut(rGraph.left, rGraph.bottom + GetAxesStubs().cy, tTimeKey[0].FormatGmt());
						pDC->TextOut(rGraph.right - sizeText[1].cx, rGraph.bottom + GetAxesStubs().cy, tTimeKey[1].FormatGmt());
						pDC->SetTextColor(nColor[0]);
					}
					pDC->SetBkMode(nBkMode);
				}
				pDC->SelectObject(pOldFont);
			}
			if (GetObjectType(pDC->GetSafeHdc()) == OBJ_ENHMETADC)
			{
				DeleteObject(hTicksPen);
				DeleteObject(hGridsPen);
				return;
			}
			if (m_cGraphBits.GetSize() > 0)
			{
				if (cDC[0].CreateCompatibleDC(pDC))
				{
					if (cDC[1].CreateCompatibleDC(pDC))
					{
						nColor[0] = cDC[0].SetBkColor(RGB(0, 0, 0));
						if (cBitmap[0].CreateCompatibleBitmap(pDC, rGraph.Width(), rGraph.Height()))
						{
							if (cBitmap[1].CreateBitmap(rGraph.Width(), rGraph.Height(), 1, 1, (LPCVOID)NULL))
							{
								if ((pOldBitmap[0] = (CBitmap *)cDC[0].SelectObject(&cBitmap[0])))
								{
									if ((pOldBitmap[1] = (CBitmap *)cDC[1].SelectObject(&cBitmap[1])))
									{
										if (cCompressionTools.Decompress(m_cGraphBits, nGraphBits) && cBitmap[0].SetBitmapBits((DWORD)nGraphBits.GetSize(), nGraphBits.GetData()) > 0)
										{
											cDC[1].BitBlt(0, 0, rGraph.Width(), rGraph.Height(), &cDC[0], 0, 0, SRCCOPY);
											pDC->BitBlt(rGraph.left, rGraph.top, rGraph.Width(), rGraph.Height(), &cDC[1], 0, 0, SRCAND);
											pDC->BitBlt(rGraph.left, rGraph.top, rGraph.Width(), rGraph.Height(), &cDC[0], 0, 0, SRCPAINT);
										}
										cDC[1].SelectObject(pOldBitmap[1]);
									}
									cDC[0].SelectObject(pOldBitmap[0]);
								}
								cBitmap[1].DeleteObject();
							}
							cBitmap[0].DeleteObject();
						}
						cDC[0].SetBkColor(nColor[0]);
						cDC[1].DeleteDC();
					}
					cDC[0].DeleteDC();
				}
			}
			DeleteObject(hTicksPen);
			DeleteObject(hGridsPen);
			return;
		}
		DeleteObject(hGridsPen);
		break;
	}
	pDC->FillSolidRect(GetImagePosition(), GetSysColor(COLOR_WINDOW));
}

VOID CGRDView::DrawLegend(CDC *pDC)
{
	CDC  cDC;
	INT  nColumn;
	INT  nColumns;
	INT  nParameter;
	INT  nParameters;
	HPEN  hLinePen;
	HPEN  hOldPen;
	CRect  rLine;
	CBitmap  cBitmap;
	CBitmap  *pOldBitmap;
	LOGBRUSH  sPenBrush;
	CGRDLayoutParameter  *pParameter;

	if (GetTextCount() > 0)
	{
		for (nColumn = 0, nColumns = (INT)m_nLayoutColumns.GetSize(); nColumn < nColumns; nColumn++)
		{
			if (m_nLayoutColumns.GetAt(nColumn) == GRD_TITLEITEM_LINE) break;
			continue;
		}
		if (nColumn < nColumns)
		{
			if (cDC.CreateCompatibleDC(pDC))
			{
				for (nParameter = 0, nParameters = (INT)m_cLayout.GetSize(); nParameter < nParameters; nParameter++)
				{
					rLine = m_wndContentCtrl.CalcTextRect(nParameter, nColumn);
					rLine.left -= m_wndContentCtrl.m_wTextIndent[0];
					rLine.top -= m_wndContentCtrl.m_wTextSpacing[0];
					rLine.right += m_wndContentCtrl.m_wTextIndent[1];
					rLine.bottom += m_wndContentCtrl.m_wTextSpacing[1];
					if ((pParameter = m_cLayout.GetAt(nParameter)))
					{
						if (cBitmap.CreateCompatibleBitmap(pDC, rLine.Width(), rLine.Height()))
						{
							if ((pOldBitmap = cDC.SelectObject(&cBitmap)))
							{
								sPenBrush.lbStyle = BS_SOLID;
								sPenBrush.lbHatch = (ULONG_PTR)NULL;
								sPenBrush.lbColor = (pParameter->GetColor() == GetSysColor(COLOR_WINDOW)) ? GetDatabase()->GetGRDIDColumnColor() : pParameter->GetColor();
								if ((hLinePen = ExtCreatePen(PS_GEOMETRIC | PS_ENDCAP_FLAT | ((pParameter->GetLineStyle() != GRDLAYOUTPARAMETER_LINESTYLE_DASHED  &&  pParameter->GetLineStyle() != GRDLAYOUTPARAMETER_LINESTYLE_DOTTED) ? PS_SOLID : 0) | ((pParameter->GetLineStyle() == GRDLAYOUTPARAMETER_LINESTYLE_DASHED) ? PS_DASH : 0) | ((pParameter->GetLineStyle() == GRDLAYOUTPARAMETER_LINESTYLE_DOTTED) ? PS_DOT : 0), pParameter->GetLineWidth(), &sPenBrush, 0, (CONST DWORD *) NULL)))
								{
									if ((hOldPen = (HPEN)SelectObject(cDC.GetSafeHdc(), hLinePen)))
									{
										cDC.FillSolidRect(CRect(0, 0, rLine.Width(), rLine.Height()), GetSysColor(COLOR_WINDOW));
										cDC.MoveTo(m_wndContentCtrl.m_wTextIndent[0], rLine.CenterPoint().y - rLine.top);
										cDC.LineTo(m_wndContentCtrl.m_wTextIndent[0] + rLine.Width(), rLine.CenterPoint().y - rLine.top);
										DrawSymbol(&cDC, pParameter->GetLineSymbol(), pParameter->GetLineWidth(), sPenBrush.lbColor, CPoint(rLine.Width() / 4, rLine.CenterPoint().y - rLine.top), FALSE);
										DrawSymbol(&cDC, pParameter->GetLineSymbol(), pParameter->GetLineWidth(), sPenBrush.lbColor, CPoint((3 * rLine.Width()) / 4, rLine.CenterPoint().y - rLine.top), FALSE);
										pDC->BitBlt(rLine.left, rLine.top, rLine.Width(), rLine.Height(), &cDC, 0, 0, SRCCOPY);
										pDC->ExcludeClipRect(rLine.left, rLine.top, rLine.left + rLine.Width(), rLine.top + rLine.Height());
										SelectObject(cDC.GetSafeHdc(), hOldPen);
										cDC.SelectObject(pOldBitmap);
										cBitmap.DeleteObject();
										DeleteObject(hLinePen);
										continue;
									}
									DeleteObject(hLinePen);
								}
								cDC.FillSolidRect(CRect(0, 0, rLine.Width(), rLine.Height()), GetSysColor(COLOR_WINDOW));
								pDC->BitBlt(rLine.left, rLine.top, rLine.Width(), rLine.Height(), &cDC, 0, 0, SRCCOPY);
								pDC->ExcludeClipRect(rLine.left, rLine.top, rLine.left + rLine.Width(), rLine.top + rLine.Height());
								cDC.SelectObject(pOldBitmap);
								cBitmap.DeleteObject();
								continue;
							}
							cBitmap.DeleteObject();
						}
					}
					pDC->FillSolidRect(rLine, GetSysColor(COLOR_WINDOW));
					pDC->ExcludeClipRect(rLine);
				}
				cDC.DeleteDC();
			}
		}
	}
}

VOID CGRDView::DrawSlider(CDC *pDC)
{
	CPen  cPen;
	CPen  *pOldPen;
	CRect  rGraph;
	CRect  rSlider;
	CBrush  cBrush;
	CBrush  *pOldBrush;
	CTimeTag  tRange[2];
	POINT  ptSymbol[2][3];

	if (m_cLayout.GetMode() & GRDLAYOUT_MODE_OVERWRITE)
	{
		if (m_cGraphPlots.GetUpdateRange(tRange[0], tRange[1]))
		{
			if (cBrush.CreateSolidBrush(m_cLayout.GetLabelColor()))
			{
				if (cPen.CreatePen(PS_SOLID, 1, m_cLayout.GetLabelColor()))
				{
					if ((pOldPen = pDC->SelectObject(&cPen)) != (CPen *)NULL)
					{
						if ((pOldBrush = pDC->SelectObject(&cBrush)) != (CBrush *)NULL)
						{
							rGraph.SetRect(GetGraphPosition().TopLeft(), GetGraphPosition().BottomRight());
							rSlider.SetRect((m_tGraph[0] > 0) ? CalcSamplePosition(tRange[1]).x : 0, rGraph.top, (m_tGraph[0] > 0) ? CalcSamplePosition(tRange[1]).x : 0, rGraph.bottom);
							rSlider.SetRect(min(rSlider.left, rGraph.right - rGraph.left), rSlider.top, min(rSlider.left, rGraph.right - rGraph.left), rSlider.bottom);
							ptSymbol[0][0].x = rGraph.left + rSlider.left;
							ptSymbol[1][0].x = rGraph.left + rSlider.left;
							ptSymbol[0][1].x = ptSymbol[0][0].x - GetAxesStubs().cx;
							ptSymbol[0][2].x = ptSymbol[0][0].x + GetAxesStubs().cx;
							ptSymbol[1][1].x = ptSymbol[1][0].x - GetAxesStubs().cx;
							ptSymbol[1][2].x = ptSymbol[1][0].x + GetAxesStubs().cx;
							ptSymbol[0][0].y = rSlider.top;
							ptSymbol[1][0].y = rSlider.bottom;
							ptSymbol[0][1].y = ptSymbol[0][0].y - GetAxesStubs().cy;
							ptSymbol[0][2].y = ptSymbol[0][0].y - GetAxesStubs().cy;
							ptSymbol[1][1].y = ptSymbol[1][0].y + GetAxesStubs().cy;
							ptSymbol[1][2].y = ptSymbol[1][0].y + GetAxesStubs().cy;
							pDC->Polygon(ptSymbol[0], sizeof(ptSymbol[0]) / sizeof(POINT));
							pDC->Polygon(ptSymbol[1], sizeof(ptSymbol[1]) / sizeof(POINT));
							pDC->MoveTo(rGraph.left + rSlider.right, rSlider.top);
							pDC->LineTo(rGraph.left + rSlider.right, rSlider.bottom);
							pDC->SelectObject(pOldBrush);
						}
						pDC->SelectObject(pOldPen);
					}
					cPen.DeleteObject();
				}
				cBrush.DeleteObject();
			}
		}
	}
}

VOID CGRDView::DrawSymbol(CDC *pDC, INT nSymbol, INT nWidth, COLORREF nColor, CONST POINT &pt, BOOL bFirst)
{
	CPen  *pOldPen;
	CPen  cSymbolPen;
	CBrush  *pOldBrush;
	CBrush  cSymbolBrush;

	switch (nSymbol)
	{
	case GRDLAYOUTPARAMETER_LINESYMBOL_STROKE:
	{ if (cSymbolPen.CreatePen(PS_SOLID, 1, nColor))
	{
		if ((pOldPen = pDC->SelectObject(&cSymbolPen)))
		{
			pDC->MoveTo(pt.x, pt.y - nWidth / 2 - 2);
			pDC->LineTo(pt.x, pt.y + (nWidth - 1) / 2 + 2 + 1);
			pDC->SelectObject(pOldPen);
		}
		cSymbolPen.DeleteObject();
	}
	break;
	}
	case GRDLAYOUTPARAMETER_LINESYMBOL_CROSS:
	{ if (cSymbolPen.CreatePen(PS_SOLID, 1, nColor))
	{
		if ((pOldPen = pDC->SelectObject(&cSymbolPen)))
		{
			pDC->MoveTo(pt.x - (nWidth / 2 + 2), pt.y - (nWidth / 2 + 2));
			pDC->LineTo(pt.x, pt.y);
			pDC->MoveTo(pt.x + (nWidth / 2 + 2) - (nWidth + 1) % 2, pt.y - (nWidth / 2 + 2));
			pDC->LineTo(pt.x - (nWidth + 1) % 2, pt.y);
			pDC->MoveTo(pt.x - (nWidth / 2 + 2), pt.y + ((nWidth - 1) / 2 + 2));
			pDC->LineTo(pt.x, pt.y - (nWidth + 1) % 2);
			pDC->MoveTo(pt.x + (nWidth / 2 + 2) - (nWidth + 1) % 2, pt.y + ((nWidth - 1) / 2 + 2));
			pDC->LineTo(pt.x - (nWidth + 1) % 2, pt.y - (nWidth + 1) % 2);
			pDC->SelectObject(pOldPen);
		}
		cSymbolPen.DeleteObject();
	}
	break;
	}
	case GRDLAYOUTPARAMETER_LINESYMBOL_POINT:
	{ if (cSymbolPen.CreatePen(PS_SOLID, 0, nColor))
	{
		if (cSymbolBrush.CreateSolidBrush(nColor))
		{
			if ((pOldPen = pDC->SelectObject(&cSymbolPen)))
			{
				if ((pOldBrush = pDC->SelectObject(&cSymbolBrush)))
				{
					pDC->Ellipse(pt.x - (nWidth + 1), pt.y - (nWidth + 1), pt.x + (nWidth + 1) + 1, pt.y + (nWidth + 1) + nWidth % 2);
					pDC->SelectObject(pOldBrush);
				}
				pDC->SelectObject(pOldPen);
			}
			cSymbolBrush.DeleteObject();
		}
		cSymbolPen.DeleteObject();
	}
	break;
	}
	case GRDLAYOUTPARAMETER_LINESYMBOL_SQUARE:
	{ if (cSymbolPen.CreatePen(PS_SOLID, 0, nColor))
	{
		if (cSymbolBrush.CreateSolidBrush(nColor))
		{
			if ((pOldPen = pDC->SelectObject(&cSymbolPen)))
			{
				if ((pOldBrush = pDC->SelectObject(&cSymbolBrush)))
				{
					pDC->Rectangle(pt.x - nWidth, pt.y - nWidth, pt.x + nWidth + 1, pt.y + nWidth + nWidth % 2);
					pDC->SelectObject(pOldBrush);
				}
				pDC->SelectObject(pOldPen);
			}
			cSymbolBrush.DeleteObject();
		}
		cSymbolPen.DeleteObject();
	}
	break;
	}
	default:
	{ if (bFirst)
	{
		if (cSymbolPen.CreatePen(PS_SOLID, 1, nColor))
		{
			if (cSymbolBrush.CreateSolidBrush(nColor))
			{
				if ((pOldPen = pDC->SelectObject(&cSymbolPen)))
				{
					if ((pOldBrush = pDC->SelectObject(&cSymbolBrush)))
					{
						pDC->Rectangle(pt.x, pt.y - nWidth / 2, pt.x + 1, pt.y + (nWidth + 1) / 2);
						pDC->SelectObject(pOldBrush);
					}
					pDC->SelectObject(pOldPen);
				}
				cSymbolBrush.DeleteObject();
			}
			cSymbolPen.DeleteObject();
		}
	}
	break;
	}
	}
}

VOID CGRDView::DrawSample(CDC *pDC, CONST CGRDLayout &cLayout, INT nPlot, CGRDParameterSample *pParameterSample, CGRDParameterSample *pPreviousSample)
{
	INT  nType;
	INT  nClip;
	INT  nSample;
	INT  nSamples;
	INT  nROPMode;
	INT  nFillMode;
	UINT  nStatus[2];
	HPEN  hOldPen;
	HPEN  hLinePen;
	HRGN  hClipRgn;
	CRgn  rgnClip;
	CRect  rPlot[2];
	POINT  ptArea[4];
	double  fValue[1];
	CPoint  ptValue[3];
	CBrush  cAreaBrush;
	CBrush  *pOldBrush;
	CTimeTag  tRange[2];
	LOGBRUSH  sPenBrush[2];
	ULONGLONG  nValue[2];
	CGRDLayoutParameter  *pParameter;

	if ((pParameter = ((nType = cLayout.GetType()) == GRDLAYOUT_TYPE_NORMAL || nType == GRDLAYOUT_TYPE_STRIPCHART) ? cLayout.GetAt(nPlot) : (CGRDLayoutParameter *)NULL))
	{
		for (nSample = (pParameter->GetOccurrence() >= 0) ? pParameter->GetOccurrence() : 0, nSamples = (pParameter->GetOccurrence() >= 0) ? (nSample + 1) : pParameterSample->GetValueCount(), ptValue[0] = (pPreviousSample != (CGRDParameterSample *)NULL && pPreviousSample->GetRawValue((pParameter->GetOccurrence() < 0) ? (pPreviousSample->GetValueCount() - 1) : pParameter->GetOccurrence(), nValue[0], nStatus[0])) ? pPreviousSample->GetPosition() : CPoint(-1, -1), CreateLinePen(pDC, GetGraphSize(), ((pParameter->GetLineStyle() != GRDLAYOUTPARAMETER_LINESTYLE_DASHED && pParameter->GetLineStyle() != GRDLAYOUTPARAMETER_LINESTYLE_DOTTED) ? PS_SOLID : 0) | ((pParameter->GetLineStyle() == GRDLAYOUTPARAMETER_LINESTYLE_DASHED) ? PS_DASH : 0) | ((pParameter->GetLineStyle() == GRDLAYOUTPARAMETER_LINESTYLE_DOTTED) ? PS_DOT : 0), pParameter->GetLineWidth(), (pParameter->GetColor() == GetSysColor(COLOR_WINDOW)) ? GetDatabase()->GetGRDIDColumnColor() : pParameter->GetColor(), &sPenBrush[0]), sPenBrush[1].lbStyle = BS_SOLID, sPenBrush[1].lbColor = sPenBrush[0].lbColor, sPenBrush[1].lbHatch = (ULONG_PTR)NULL; nSample < nSamples; nSample++, ptValue[0] = ptValue[1], nStatus[0] = nStatus[1], nValue[0] = nValue[1])
		{
			ptValue[1] = (pParameterSample->GetRawValue(nSample, nValue[1], nStatus[1]) && pParameterSample->GetValue(GetDatabase(), nSample, fValue[0])) ? CalcSamplePosition(nPlot, pParameterSample, fValue[0], rPlot[0]) : CPoint(-1, -1);
			ptValue[2] = (((nStatus[0] & TMPARAMETER_STATUS_VALID) || IsInvalidDataModeEnabled()) && ((nStatus[0] & TMPARAMETER_STATUS_GOOD) || IsBadDataModeEnabled()) && ptValue[0].x >= 0) ? ptValue[0] : ptValue[1];
			if (((nStatus[1] & TMPARAMETER_STATUS_VALID) == TMPARAMETER_STATUS_VALID || IsInvalidDataModeEnabled()) && ((nStatus[1] & TMPARAMETER_STATUS_GOOD) == TMPARAMETER_STATUS_GOOD || IsBadDataModeEnabled()))
			{
				for (rPlot[1] = rPlot[0]; (m_cLayout.GetMode() & GRDLAYOUT_MODE_OVERWRITE) && m_cGraphPlots.GetUpdateRange(tRange[0], tRange[1]) && (ptValue[1].x >= ptValue[2].x || (pPreviousSample != (CGRDParameterSample *)NULL && pPreviousSample->GetLastUpdateTime() < tRange[1] - (m_tGraph[2] - m_tGraph[1]))); )
				{
					rPlot[1].SetRect((pParameterSample->GetLastUpdateTime() < m_tGraph[1] && (!pPreviousSample || pPreviousSample->GetLastUpdateTime() >= tRange[1] - (m_tGraph[2] - m_tGraph[1])) && tRange[1] >= m_tGraph[1]) ? (CalcSamplePosition(tRange[1]).x + 1) : rPlot[1].left, rPlot[1].top, (pParameterSample->GetLastUpdateTime() >= m_tGraph[1] && (!pPreviousSample || pPreviousSample->GetLastUpdateTime() >= tRange[1] - (m_tGraph[2] - m_tGraph[1]))) ? (CalcSamplePosition(tRange[1]).x + (pParameter->GetLineWidth() + 1) / 2) : ((pPreviousSample != (CGRDParameterSample *)NULL  &&  pPreviousSample->GetLastUpdateTime() < tRange[1] - (m_tGraph[2] - m_tGraph[1])) ? (CalcSamplePosition(pPreviousSample->GetLastUpdateTime()).x - 1) : rPlot[1].right), rPlot[1].bottom);
					rPlot[1].SetRect(min(rPlot[1].left, rPlot[1].right), rPlot[1].top, min(rPlot[0].right, rPlot[1].right), rPlot[1].bottom);
					break;
				}
				if (rgnClip.CreateRectRgn(rPlot[1].left, rPlot[1].top, rPlot[1].right, rPlot[1].bottom))
				{
					for (; GetObjectType(pDC->GetSafeHdc()) == OBJ_ENHMETADC; )
					{
						rgnClip.OffsetRgn(GetGraphPosition().TopLeft());
						break;
					}
					if ((hClipRgn = (HRGN)CreateRectRgn(0, 0, 0, 0)) != (HRGN)NULL)
					{
						if ((nClip = GetClipRgn(pDC->GetSafeHdc(), hClipRgn)) >= 0)
						{
							if (pDC->SelectClipRgn(&rgnClip) != ERROR)
							{
								if ((cLayout.GetMode() & GRDLAYOUT_MODE_AREA) == GRDLAYOUT_MODE_AREA)
								{
									if ((hLinePen = ExtCreatePen(PS_GEOMETRIC | PS_ENDCAP_FLAT | PS_SOLID, 1, &sPenBrush[1], 0, (CONST DWORD *) NULL)))
									{
										if ((hOldPen = (HPEN)SelectObject(pDC->GetSafeHdc(), hLinePen)))
										{
											if (cAreaBrush.CreateSolidBrush(sPenBrush[1].lbColor))
											{
												if ((pOldBrush = pDC->SelectObject(&cAreaBrush)))
												{
													nFillMode = pDC->SetPolyFillMode(ALTERNATE);
													nROPMode = pDC->SetROP2(R2_MERGEPEN);
													if (ptValue[1].x >= ptValue[2].x)
													{
														ptArea[0].x = ptValue[2].x;
														ptArea[0].y = ptValue[2].y;
														ptArea[1].x = ptValue[1].x;
														ptArea[1].y = ptValue[1].y;
														ptArea[2].x = ptValue[1].x;
														ptArea[3].x = ptValue[2].x;
														ptArea[2].y = ptArea[3].y = rPlot[0].bottom;
														pDC->Polygon(ptArea, sizeof(ptArea) / sizeof(POINT));
													}
													else
													{
														ptArea[0].x = ptValue[2].x;
														ptArea[0].y = ptValue[2].y;
														ptArea[1].x = ptValue[1].x + GetGraphSize().cx;
														ptArea[1].y = ptValue[1].y;
														ptArea[2].x = ptValue[1].x + GetGraphSize().cx;
														ptArea[3].x = ptValue[2].x;
														ptArea[2].y = ptArea[3].y = rPlot[0].bottom;
														pDC->Polygon(ptArea, sizeof(ptArea) / sizeof(POINT));
														ptArea[0].x = ptValue[2].x - GetGraphSize().cx;
														ptArea[0].y = ptValue[2].y;
														ptArea[1].x = ptValue[1].x;
														ptArea[1].y = ptValue[1].y;
														ptArea[2].x = ptValue[1].x;
														ptArea[3].x = ptValue[2].x - GetGraphSize().cx;
														ptArea[2].y = ptArea[3].y = rPlot[0].bottom;
														pDC->Polygon(ptArea, sizeof(ptArea) / sizeof(POINT));
													}
													pDC->SetPolyFillMode(nFillMode);
													pDC->SetROP2(nROPMode);
													pDC->SelectObject(pOldBrush);
												}
												cAreaBrush.DeleteObject();
											}
											SelectObject(pDC->GetSafeHdc(), hOldPen);
										}
										DeleteObject(hLinePen);
									}
								}
								if (ptValue[1] != ptValue[2])
								{
									if ((hLinePen = ExtCreatePen(PS_GEOMETRIC | PS_ENDCAP_FLAT | PS_SOLID, pParameter->GetLineWidth(), &sPenBrush[0], 0, (CONST DWORD *) NULL)))
									{
										if ((hOldPen = (HPEN)SelectObject(pDC->GetSafeHdc(), hLinePen)))
										{
											if (ptValue[1].x >= ptValue[2].x)
											{
												pDC->MoveTo(ptValue[2]);
												pDC->LineTo(ptValue[1]);
											}
											else
											{
												pDC->MoveTo(ptValue[2]);
												pDC->LineTo(ptValue[1].x + GetGraphSize().cx, ptValue[1].y);
												pDC->MoveTo(ptValue[2].x - GetGraphSize().cx, ptValue[2].y);
												pDC->LineTo(ptValue[1]);
											}
											SelectObject(pDC->GetSafeHdc(), hOldPen);
										}
										DeleteObject(hLinePen);
									}
									if (pPreviousSample != (CGRDParameterSample *)NULL) DrawSymbol(pDC, (!pPreviousSample->IsDummy()) ? pParameter->GetLineSymbol() : GRDLAYOUTPARAMETER_LINESYMBOL_NONE, pParameter->GetLineWidth(), sPenBrush[0].lbColor, ptValue[2], FALSE);
								}
								DrawSymbol(pDC, (!pParameterSample->IsDummy()) ? pParameter->GetLineSymbol() : GRDLAYOUTPARAMETER_LINESYMBOL_NONE, pParameter->GetLineWidth(), sPenBrush[0].lbColor, ptValue[1], ptValue[1] == ptValue[2]);
								SelectClipRgn(pDC->GetSafeHdc(), (nClip > 0) ? hClipRgn : (HRGN)NULL);
							}
						}
						DeleteObject(hClipRgn);
					}
					rgnClip.DeleteObject();
				}
			}
			pParameterSample->SetPosition(ptValue[1]);
		}
		DestroyLinePen(&sPenBrush[0]);
	}
}
VOID CGRDView::DrawSample(CDC *pDC, CONST CGRDLayout &cLayout, INT nPlot, CONST CPtrArray &pParameterSamples, CGRDParameterSample *pPreviousSample)
{
	INT  nType;
	INT  nClip;
	INT  nSample;
	INT  nSamples;
	INT  nROPMode;
	INT  nFillMode;
	INT  nParameter;
	INT  nParameters;
	UINT  nStatus[2];
	HPEN  hOldPen;
	HPEN  hLinePen;
	HRGN  hClipRgn;
	CRgn  rgnClip;
	CRect  rPlot[2];
	POINT  ptArea[4];
	double  fValue[1];
	double  fRange[2];
	double  *pValues[2];
	CPoint  ptValue[3];
	CBrush  cAreaBrush;
	CBrush  *pOldBrush;
	CTimeTag  tRange[2];
	LOGBRUSH  sPenBrush[2];
	ULONGLONG  nValue[2];
	CGRDLayoutParameter  *pParameter;
	CGRDParameterSample  *pParameterSample[2];

	if ((nType = cLayout.GetType()) == GRDLAYOUT_TYPE_STACKCHART)
	{
		if ((pParameterSample[0] = (CGRDParameterSample *)pParameterSamples.GetAt(nPlot)))
		{
			if ((pValues[0] = (double *)GlobalAlloc(GPTR, pParameterSamples.GetSize()*sizeof(double))))
			{
				if ((pValues[1] = (double *)GlobalAlloc(GPTR, pParameterSamples.GetSize()*sizeof(double))))
				{
					for (nParameter = 0, nParameters = (INT)pParameterSamples.GetSize(); nParameter < nParameters; nParameter++)
					{
						if ((pParameter = (CGRDLayoutParameter *)cLayout.GetAt(nParameter)) != (CGRDLayoutParameter *)NULL)
						{
							if ((pParameterSample[1] = (CGRDParameterSample *)pParameterSamples.GetAt(nParameter)))
							{
								if (pParameterSample[0]->GetUpdateTime() == pParameterSample[1]->GetUpdateTime())
								{
									for (nSample = (pParameter->GetOccurrence() >= 0) ? pParameter->GetOccurrence() : 0, nSamples = (pParameter->GetOccurrence() >= 0) ? (nSample + 1) : pParameterSample[1]->GetValueCount(); nSample < nSamples; nSample++)
									{
										if (pParameterSample[1]->GetRawValue(nSample, nValue[0], nStatus[0]) && pParameterSample[1]->GetValue(GetDatabase(), nSample, fValue[0]))
										{
											if (((nStatus[0] & TMPARAMETER_STATUS_VALID) || IsInvalidDataModeEnabled()) && ((nStatus[0] & TMPARAMETER_STATUS_GOOD) || IsBadDataModeEnabled()))
											{
												pValues[0][nParameter] = (pParameter->GetOccurrence() < 0 && nSample > 0) ? min(pValues[0][nParameter], fValue[0]) : fValue[0];
												pValues[1][nParameter] = (pParameter->GetOccurrence() < 0 && nSample > 0) ? max(pValues[1][nParameter], fValue[0]) : fValue[0];
												continue;
											}
										}
										if (pParameter->GetRange(fRange[0], fRange[1]))
										{
											if (pParameter->GetOccurrence() == nSample || !nSample)
											{
												pValues[0][nParameter] = fRange[0];
												pValues[1][nParameter] = fRange[0];
											}
											continue;
										}
										pValues[0][nParameter] = pValues[1][nParameter] = 0.0;
									}
									continue;
								}
								if (pParameterSample[0]->GetUpdateTime() > pParameterSample[1]->GetUpdateTime())
								{
									if (pParameterSample[1]->GetRawValue((nSample = (pParameter->GetOccurrence() < 0) ? (pParameterSample[1]->GetValueCount() - 1) : pParameter->GetOccurrence()), nValue[0], nStatus[0]) && pParameterSample[1]->GetValue(GetDatabase(), nSample, fValue[0]))
									{
										if (((nStatus[0] & TMPARAMETER_STATUS_VALID) || IsInvalidDataModeEnabled()) && ((nStatus[0] & TMPARAMETER_STATUS_GOOD) || IsBadDataModeEnabled()))
										{
											pValues[0][nParameter] = fValue[0];
											pValues[1][nParameter] = fValue[0];
											continue;
										}
									}
								}
							}
							if (pParameter->GetRange(fRange[0], fRange[1]))
							{
								pValues[0][nParameter] = fRange[0];
								pValues[1][nParameter] = fRange[0];
								continue;
							}
						}
						pValues[0][nParameter] = pValues[1][nParameter] = 0.0;
					}
					if ((pParameter = cLayout.GetAt(nPlot)))
					{
						for (nSample = (pParameter->GetOccurrence() >= 0) ? pParameter->GetOccurrence() : 0, nSamples = (pParameter->GetOccurrence() >= 0) ? (nSample + 1) : pParameterSample[0]->GetValueCount(), ptValue[0] = (pPreviousSample != (CGRDParameterSample *)NULL && pPreviousSample->GetRawValue((pParameter->GetOccurrence() < 0) ? (pPreviousSample->GetValueCount() - 1) : pParameter->GetOccurrence(), nValue[0], nStatus[0])) ? pPreviousSample->GetPosition() : CPoint(-1, -1), CreateLinePen(pDC, GetGraphSize(), ((pParameter->GetLineStyle() != GRDLAYOUTPARAMETER_LINESTYLE_DASHED && pParameter->GetLineStyle() != GRDLAYOUTPARAMETER_LINESTYLE_DOTTED) ? PS_SOLID : 0) | ((pParameter->GetLineStyle() == GRDLAYOUTPARAMETER_LINESTYLE_DASHED) ? PS_DASH : 0) | ((pParameter->GetLineStyle() == GRDLAYOUTPARAMETER_LINESTYLE_DOTTED) ? PS_DOT : 0), pParameter->GetLineWidth(), (pParameter->GetColor() == GetSysColor(COLOR_WINDOW)) ? GetDatabase()->GetGRDIDColumnColor() : pParameter->GetColor(), &sPenBrush[0]), sPenBrush[1].lbStyle = BS_SOLID, sPenBrush[1].lbColor = sPenBrush[0].lbColor, sPenBrush[1].lbHatch = (ULONG_PTR)NULL; nSample < nSamples; nSample++, ptValue[0] = ptValue[1], nStatus[0] = nStatus[1], nValue[0] = nValue[1])
						{
							ptValue[1] = (pParameterSample[0]->GetRawValue(nSample, nValue[1], nStatus[1]) && pParameterSample[0]->GetValue(GetDatabase(), nSample, fValue[0])) ? CalcSamplePosition(nPlot, pParameterSample[0], pValues[0], pValues[1], fValue[0], rPlot[0]) : CPoint(-1, -1);
							ptValue[2] = (((nStatus[0] & TMPARAMETER_STATUS_VALID) || IsInvalidDataModeEnabled()) && ((nStatus[0] & TMPARAMETER_STATUS_GOOD) || IsBadDataModeEnabled()) && ptValue[0].x >= 0) ? ptValue[0] : ptValue[1];
							if (((nStatus[1] & TMPARAMETER_STATUS_VALID) || IsInvalidDataModeEnabled()) && ((nStatus[1] & TMPARAMETER_STATUS_GOOD) || IsBadDataModeEnabled()))
							{
								for (rPlot[1] = rPlot[0]; (m_cLayout.GetMode() & GRDLAYOUT_MODE_OVERWRITE) && m_cGraphPlots.GetUpdateRange(tRange[0], tRange[1]) && (ptValue[1].x >= ptValue[2].x || (pPreviousSample != (CGRDParameterSample *)NULL && pPreviousSample->GetLastUpdateTime() < tRange[1] - (m_tGraph[2] - m_tGraph[1]))); )
								{
									rPlot[1].SetRect((pParameterSample[0]->GetLastUpdateTime() < m_tGraph[1] && (!pPreviousSample || pPreviousSample->GetLastUpdateTime() >= tRange[1] - (m_tGraph[2] - m_tGraph[1])) && tRange[1] >= m_tGraph[1]) ? (CalcSamplePosition(tRange[1]).x + 1) : rPlot[1].left, rPlot[1].top, (pParameterSample[0]->GetLastUpdateTime() >= m_tGraph[1] && (!pPreviousSample || pPreviousSample->GetLastUpdateTime() >= tRange[1] - (m_tGraph[2] - m_tGraph[1]))) ? (CalcSamplePosition(tRange[1]).x + (pParameter->GetLineWidth() + 1) / 2) : ((pPreviousSample != (CGRDParameterSample *)NULL  &&  pPreviousSample->GetLastUpdateTime() < tRange[1] - (m_tGraph[2] - m_tGraph[1])) ? (CalcSamplePosition(pPreviousSample->GetLastUpdateTime()).x - 1) : rPlot[1].right), rPlot[1].bottom);
									rPlot[1].SetRect(min(rPlot[1].left, rPlot[1].right), rPlot[1].top, min(rPlot[0].right, rPlot[1].right), rPlot[1].bottom);
									break;
								}
								if (rgnClip.CreateRectRgn(rPlot[1].left, rPlot[1].top, rPlot[1].right, rPlot[1].bottom))
								{
									for (; GetObjectType(pDC->GetSafeHdc()) == OBJ_ENHMETADC; )
									{
										rgnClip.OffsetRgn(GetGraphPosition().TopLeft());
										break;
									}
									if ((hClipRgn = (HRGN)CreateRectRgn(0, 0, 0, 0)) != (HRGN)NULL)
									{
										if ((nClip = GetClipRgn(pDC->GetSafeHdc(), hClipRgn)) >= 0)
										{
											if (pDC->SelectClipRgn(&rgnClip) != ERROR)
											{
												if ((cLayout.GetMode() & GRDLAYOUT_MODE_AREA) == GRDLAYOUT_MODE_AREA)
												{
													if ((hLinePen = ExtCreatePen(PS_GEOMETRIC | PS_ENDCAP_FLAT | PS_SOLID, 1, &sPenBrush[1], 0, (CONST DWORD *) NULL)))
													{
														if ((hOldPen = (HPEN)SelectObject(pDC->GetSafeHdc(), hLinePen)))
														{
															if (cAreaBrush.CreateSolidBrush(sPenBrush[1].lbColor))
															{
																if ((pOldBrush = pDC->SelectObject(&cAreaBrush)))
																{
																	nFillMode = pDC->SetPolyFillMode(ALTERNATE);
																	nROPMode = pDC->SetROP2(R2_COPYPEN);
																	if (ptValue[1].x >= ptValue[2].x)
																	{
																		ptArea[0].x = ptValue[2].x;
																		ptArea[0].y = ptValue[2].y;
																		ptArea[1].x = ptValue[1].x;
																		ptArea[1].y = ptValue[1].y;
																		ptArea[2].x = ptValue[1].x;
																		ptArea[3].x = ptValue[2].x;
																		ptArea[2].y = ptArea[3].y = rPlot[0].bottom;
																		pDC->Polygon(ptArea, sizeof(ptArea) / sizeof(POINT));
																	}
																	else
																	{
																		ptArea[0].x = ptValue[2].x;
																		ptArea[0].y = ptValue[2].y;
																		ptArea[1].x = ptValue[1].x + GetGraphSize().cx;
																		ptArea[1].y = ptValue[1].y;
																		ptArea[2].x = ptValue[1].x + GetGraphSize().cx;
																		ptArea[3].x = ptValue[2].x;
																		ptArea[2].y = ptArea[3].y = rPlot[0].bottom;
																		pDC->Polygon(ptArea, sizeof(ptArea) / sizeof(POINT));
																		ptArea[0].x = ptValue[2].x - GetGraphSize().cx;
																		ptArea[0].y = ptValue[2].y;
																		ptArea[1].x = ptValue[1].x;
																		ptArea[1].y = ptValue[1].y;
																		ptArea[2].x = ptValue[1].x;
																		ptArea[3].x = ptValue[2].x - GetGraphSize().cx;
																		ptArea[2].y = ptArea[3].y = rPlot[0].bottom;
																		pDC->Polygon(ptArea, sizeof(ptArea) / sizeof(POINT));
																	}
																	pDC->SetPolyFillMode(nFillMode);
																	pDC->SelectObject(pOldBrush);
																	pDC->SetROP2(nROPMode);
																}
																cAreaBrush.DeleteObject();
															}
															SelectObject(pDC->GetSafeHdc(), hOldPen);
														}
														DeleteObject(hLinePen);
													}
												}
												if (ptValue[1] != ptValue[2])
												{
													if ((hLinePen = ExtCreatePen(PS_GEOMETRIC | PS_ENDCAP_FLAT | PS_SOLID, pParameter->GetLineWidth(), &sPenBrush[0], 0, (CONST DWORD *) NULL)))
													{
														if ((hOldPen = (HPEN)SelectObject(pDC->GetSafeHdc(), hLinePen)))
														{
															if (ptValue[1].x >= ptValue[2].x)
															{
																pDC->MoveTo(ptValue[2]);
																pDC->LineTo(ptValue[1]);
															}
															else
															{
																pDC->MoveTo(ptValue[2]);
																pDC->LineTo(ptValue[1].x + GetGraphSize().cx, ptValue[1].y);
																pDC->MoveTo(ptValue[2].x - GetGraphSize().cx, ptValue[2].y);
																pDC->LineTo(ptValue[1]);
															}
															SelectObject(pDC->GetSafeHdc(), hOldPen);
														}
														DeleteObject(hLinePen);
													}
													if (pPreviousSample != (CGRDParameterSample *)NULL) DrawSymbol(pDC, (!pPreviousSample->IsDummy()) ? pParameter->GetLineSymbol() : GRDLAYOUTPARAMETER_LINESYMBOL_NONE, pParameter->GetLineWidth(), sPenBrush[0].lbColor, ptValue[2], FALSE);
												}
												DrawSymbol(pDC, (!pParameterSample[0]->IsDummy()) ? pParameter->GetLineSymbol() : GRDLAYOUTPARAMETER_LINESYMBOL_NONE, pParameter->GetLineWidth(), sPenBrush[0].lbColor, ptValue[1], ptValue[1] == ptValue[2]);
												SelectClipRgn(pDC->GetSafeHdc(), (nClip > 0) ? hClipRgn : (HRGN)NULL);
											}
										}
										DeleteObject(hClipRgn);
									}
									rgnClip.DeleteObject();
								}
							}
							pParameterSample[0]->SetPosition(ptValue[1]);
						}
						DestroyLinePen(&sPenBrush[0]);
					}
					GlobalFree(pValues[1]);
				}
				GlobalFree(pValues[0]);
			}
		}
	}
}
VOID CGRDView::DrawSample(CDC *pDC, CONST CGRDLayout &cLayout, INT nXPlot, INT nYPlot, CGRDParameterSample *pParameterXSample, CGRDParameterSample *pParameterYSample, CGRDParameterSample *pPreviousXSample, CGRDParameterSample *pPreviousYSample)
{
	INT  nType;
	INT  nClip;
	INT  nSample;
	INT  nSamples;
	INT  nIndex[2];
	INT  nCount[3];
	UINT  nStatus[4];
	HPEN  hOldPen;
	HPEN  hLinePen;
	HRGN  hClipRgn;
	CRgn  rgnClip;
	CRect  rPlot[1];
	double  fValue[2];
	CPoint  ptValue[3];
	LOGBRUSH  sPenBrush;
	ULONGLONG  nValue[4];
	CGRDLayoutParameter  *pParameter[2];

	if ((nType = cLayout.GetType()) == GRDLAYOUT_TYPE_DIAGRAM)
	{
		if ((pParameter[0] = cLayout.GetAt(nXPlot)) != (CGRDLayoutParameter *)NULL)
		{
			if ((pParameter[1] = cLayout.GetAt(nYPlot)) != (CGRDLayoutParameter *)NULL)
			{
				if (pParameterXSample != (CGRDParameterSample *)NULL  &&  pParameterYSample != (CGRDParameterSample *)NULL)
				{
					nCount[0] = (pParameter[0]->GetOccurrence() >= 0) ? min(pParameterXSample->GetValueCount(), 1) : pParameterXSample->GetValueCount();
					nCount[1] = (pParameter[1]->GetOccurrence() >= 0) ? min(pParameterYSample->GetValueCount(), 1) : pParameterYSample->GetValueCount();
					nCount[2] = (pParameterXSample->GetUpdateTime() == pParameterYSample->GetUpdateTime()) ? max(nCount[0], nCount[1]) : 0;
					nCount[2] = (pParameterXSample->GetUpdateTime() > pParameterYSample->GetUpdateTime()) ? max(nCount[0], 1) : nCount[2];
					nCount[2] = (pParameterXSample->GetUpdateTime() < pParameterYSample->GetUpdateTime()) ? max(nCount[1], 1) : nCount[2];
					for (nSample = 0, nSamples = nCount[2], ptValue[0] = (pPreviousXSample != (CGRDParameterSample *)NULL && pPreviousYSample != (CGRDParameterSample *)NULL && pPreviousXSample->GetRawValue((pParameter[0]->GetOccurrence() < 0) ? (pPreviousXSample->GetValueCount() - 1) : pParameter[0]->GetOccurrence(), nValue[0], nStatus[0]) && pPreviousYSample->GetRawValue((pParameter[1]->GetOccurrence() < 0) ? (pPreviousYSample->GetValueCount() - 1) : pParameter[1]->GetOccurrence(), nValue[1], nStatus[1])) ? pPreviousXSample->GetPosition() : CPoint(-1, -1), CreateLinePen(pDC, GetGraphSize(), ((pParameter[0]->GetLineStyle() != GRDLAYOUTPARAMETER_LINESTYLE_DASHED && pParameter[0]->GetLineStyle() != GRDLAYOUTPARAMETER_LINESTYLE_DOTTED) ? PS_SOLID : 0) | ((pParameter[0]->GetLineStyle() == GRDLAYOUTPARAMETER_LINESTYLE_DASHED) ? PS_DASH : 0) | ((pParameter[0]->GetLineStyle() == GRDLAYOUTPARAMETER_LINESTYLE_DOTTED) ? PS_DOT : 0), pParameter[0]->GetLineWidth(), (pParameter[0]->GetColor() == GetSysColor(COLOR_WINDOW)) ? GetDatabase()->GetGRDIDColumnColor() : pParameter[0]->GetColor(), &sPenBrush); nSample < nSamples; nSample++, ptValue[0] = ptValue[1], nStatus[0] = nStatus[2], nStatus[1] = nStatus[3], nValue[0] = nValue[2], nValue[1] = nValue[3])
					{
						ptValue[1] = (pParameterXSample->GetRawValue((nIndex[0] = (nCount[0] > 1) ? min(nSample, pParameterXSample->GetValueCount() - 1) : max(pParameter[0]->GetOccurrence(), 0)), nValue[2], nStatus[2]) && pParameterYSample->GetRawValue((nIndex[1] = (nCount[1] > 1) ? min(nSample, pParameterYSample->GetValueCount() - 1) : max(pParameter[1]->GetOccurrence(), 0)), nValue[3], nStatus[3]) && pParameterXSample->GetValue(GetDatabase(), nIndex[0], fValue[0]) && pParameterYSample->GetValue(GetDatabase(), nIndex[1], fValue[1])) ? CalcSamplePosition(nXPlot, nYPlot, fValue[0], fValue[1], rPlot[0]) : CPoint(-1, -1);
						ptValue[2] = ((((nStatus[0] & TMPARAMETER_STATUS_VALID) && (nStatus[1] & TMPARAMETER_STATUS_VALID)) || IsInvalidDataModeEnabled()) && (((nStatus[0] & TMPARAMETER_STATUS_GOOD) && (nStatus[1] & TMPARAMETER_STATUS_GOOD)) || IsBadDataModeEnabled()) && ptValue[0].x >= 0) ? ptValue[0] : ptValue[1];
						if ((((nStatus[2] & TMPARAMETER_STATUS_VALID) && (nStatus[3] & TMPARAMETER_STATUS_VALID)) || IsInvalidDataModeEnabled()) && (((nStatus[2] & TMPARAMETER_STATUS_GOOD) && (nStatus[3] & TMPARAMETER_STATUS_GOOD)) || IsBadDataModeEnabled()))
						{
							if (rgnClip.CreateRectRgn(rPlot[0].left, rPlot[0].top, rPlot[0].right, rPlot[0].bottom))
							{
								for (; GetObjectType(pDC->GetSafeHdc()) == OBJ_ENHMETADC; )
								{
									rgnClip.OffsetRgn(GetGraphPosition().TopLeft());
									break;
								}
								if ((hClipRgn = (HRGN)CreateRectRgn(0, 0, 0, 0)) != (HRGN)NULL)
								{
									if ((nClip = GetClipRgn(pDC->GetSafeHdc(), hClipRgn)) >= 0)
									{
										if (pDC->SelectClipRgn(&rgnClip) != ERROR)
										{
											if (ptValue[1] != ptValue[2])
											{
												if ((hLinePen = ExtCreatePen(PS_GEOMETRIC | PS_ENDCAP_FLAT | PS_SOLID, pParameter[0]->GetLineWidth(), &sPenBrush, 0, (CONST DWORD *) NULL)))
												{
													if ((hOldPen = (HPEN)SelectObject(pDC->GetSafeHdc(), hLinePen)))
													{
														pDC->MoveTo(ptValue[2]);
														pDC->LineTo(ptValue[1]);
														SelectObject(pDC->GetSafeHdc(), hOldPen);
													}
													DeleteObject(hLinePen);
												}
											}
											DrawSymbol(pDC, (!pParameterXSample->IsDummy()) ? pParameter[0]->GetLineSymbol() : GRDLAYOUTPARAMETER_LINESYMBOL_NONE, pParameter[0]->GetLineWidth(), sPenBrush.lbColor, ptValue[1], ptValue[1] == ptValue[2]);
											SelectClipRgn(pDC->GetSafeHdc(), (nClip > 0) ? hClipRgn : (HRGN)NULL);
										}
									}
									DeleteObject(hClipRgn);
								}
								rgnClip.DeleteObject();
							}
						}
						pParameterXSample->SetPosition(ptValue[1]);
						pParameterYSample->SetPosition(ptValue[1]);
					}
					DestroyLinePen(&sPenBrush);
				}
			}
		}
	}
}

VOID CGRDView::UpdateGraph()
{
	CDC  cDC;
	CRect  rGraph;
	BITMAP  sBitmap;
	CBitmap  cBitmap;
	CBitmap  *pOldBitmap;
	CByteArray  nGraphBits;
	CCompressionTools  cCompressionTools;
	CClientDC  cScreenDC(NULL);

	for (rGraph = GetGraphPosition(); cDC.CreateCompatibleDC(&cScreenDC); )
	{
		if (cBitmap.CreateCompatibleBitmap(&cScreenDC, rGraph.Width(), rGraph.Height()))
		{
			if ((pOldBitmap = (CBitmap *)cDC.SelectObject(&cBitmap)) != (CBitmap *)NULL)
			{
				for (UpdateGraph(&cDC), cBitmap.GetBitmap(&sBitmap), nGraphBits.SetSize((sBitmap.bmWidth*sBitmap.bmHeight*sBitmap.bmBitsPixel) / 8); cBitmap.GetBitmapBits((DWORD)nGraphBits.GetSize(), nGraphBits.GetData()) > 0; )
				{
					if (cCompressionTools.Compress(nGraphBits, m_cGraphBits) > 0)
					{
						cDC.SelectObject(pOldBitmap);
						cBitmap.DeleteObject();
						cDC.DeleteDC();
						return;
					}
					break;
				}
				cDC.SelectObject(pOldBitmap);
			}
			cBitmap.DeleteObject();
		}
		cDC.DeleteDC();
		break;
	}
}
VOID CGRDView::UpdateGraph(CDC *pDC)
{
	INT  nType;
	INT  nPlot;
	INT  nPlots;
	INT  nIndex;
	INT  nSample;
	INT  nSamples;
	INT  nClipRgn;
	HRGN  hOldRgn;
	CRgn  rgnGraph;
	CRect  rGraph;
	CPoint  ptOffset;
	CPoint  ptOrigin;
	CTimeTag  tPlotPosition;
	CPtrArray  pPlotSamples;
	CUIntArray  nPlotPositions;
	CGRDParameterSample  *pParameterSample[3];
	CGRDParameterSamples  *pParameterSamples[2];

	for (nType = m_cLayout.GetType(), rGraph = GetGraphPosition(); rgnGraph.CreateRectRgn(0, 0, rGraph.Width(), rGraph.Height()); )
	{
		if ((hOldRgn = (HRGN)CreateRectRgn(0, 0, 0, 0)) != (HRGN)NULL)
		{
			if ((nClipRgn = GetClipRgn(pDC->GetSafeHdc(), hOldRgn)) >= 0)
			{
				if (GetObjectType(pDC->GetSafeHdc()) == OBJ_ENHMETADC)
				{
					ptOrigin.x = pDC->GetViewportOrg().x;
					ptOrigin.y = pDC->GetViewportOrg().y;
					ptOrigin.Offset(rGraph.left - m_ptGraph.x, rGraph.top - m_ptGraph.y);
					SetViewportOrgEx(pDC->GetSafeHdc(), ptOrigin.x, ptOrigin.y, &ptOffset);
					rgnGraph.OffsetRgn(rGraph.left, rGraph.top);
				}
				else
				{
					ptOrigin = pDC->GetViewportOrg();
					ptOrigin.Offset(-m_ptGraph.x, -m_ptGraph.y);
					SetViewportOrgEx(pDC->GetSafeHdc(), ptOrigin.x, ptOrigin.y, &ptOffset);
				}
				if (pDC->SelectClipRgn(&rgnGraph) != ERROR)
				{
					if (nType == GRDLAYOUT_TYPE_NORMAL || nType == GRDLAYOUT_TYPE_STRIPCHART)
					{
						for (nPlot = 0, nPlots = (INT)m_cGraphPlots.GetSize(); nPlot < nPlots; nPlot++)
						{
							if ((pParameterSamples[0] = m_cGraphPlots.GetAt(nPlot)) != (CGRDParameterSamples *)NULL)
							{
								for (nSample = 0, nSamples = (INT)pParameterSamples[0]->GetSize(); nSample < nSamples; nSample++)
								{
									DrawSample(pDC, m_cLayout, nPlot, pParameterSamples[0]->GetAt(nSample), (pParameterSamples[0]->GetAt(nSample)->IsConnected()) ? pParameterSamples[0]->GetAt(nSample - 1) : (CGRDParameterSample *)NULL);
									continue;
								}
							}
						}
					}
					if (nType == GRDLAYOUT_TYPE_STACKCHART)
					{
						for (pPlotSamples.SetSize(m_cGraphPlots.GetSize()), nPlotPositions.SetSize(m_cGraphPlots.GetSize()), tPlotPosition = 0; TRUE; tPlotPosition = 0)
						{
							for (nPlot = 0, nPlots = (INT)m_cGraphPlots.GetSize(), nIndex = -1; nPlot < nPlots; nPlot++)
							{
								if ((pParameterSamples[0] = m_cGraphPlots.GetAt(nPlot)) != (CGRDParameterSamples *)NULL)
								{
									if ((pParameterSample[0] = pParameterSamples[0]->GetAt(nPlotPositions.GetAt(nPlot))))
									{
										if (pParameterSample[0]->GetUpdateTime() < tPlotPosition || !tPlotPosition.GetTime())
										{
											tPlotPosition = pParameterSample[0]->GetUpdateTime();
											nIndex = nPlot;
										}
									}
								}
							}
							if ((pParameterSamples[0] = m_cGraphPlots.GetAt(nIndex)))
							{
								if ((pParameterSample[0] = pParameterSamples[0]->GetAt(nPlotPositions.GetAt(nIndex))))
								{
									for (nPlot = 0, nPlots = (INT)m_cGraphPlots.GetSize(); nPlot < nPlots; nPlot = nPlot + 1)
									{
										if ((pParameterSamples[1] = m_cGraphPlots.GetAt(nPlot)) != (CGRDParameterSamples *)NULL)
										{
											if ((pParameterSample[1] = pParameterSamples[1]->GetAt((nSample = nPlotPositions.GetAt(nPlot)))) && pParameterSample[1]->GetUpdateTime() <= pParameterSample[0]->GetUpdateTime())
											{
												pPlotSamples.SetAt(nPlot, pParameterSample[1]);
												continue;
											}
											pPlotSamples.SetAt(nPlot, (pParameterSample[1] = (nSample > 0) ? pParameterSamples[1]->GetAt(nSample - 1) : (CGRDParameterSample *)NULL));
											continue;
										}
										pPlotSamples.SetAt(nPlot, (LPVOID)NULL);
									}
									DrawSample(pDC, m_cLayout, nIndex, pPlotSamples, (pParameterSample[0]->IsConnected()) ? pParameterSamples[0]->GetAt(nPlotPositions.GetAt(nIndex) - 1) : (CGRDParameterSample *)NULL);
									nPlotPositions.SetAt(nIndex, nPlotPositions.GetAt(nIndex) + 1);
									continue;
								}
							}
							break;
						}
					}
					if (nType == GRDLAYOUT_TYPE_DIAGRAM)
					{
						for (nPlot = 0, nPlots = (INT)m_cGraphPlots.GetSize(), nPlotPositions.SetSize(nPlots); nPlot < nPlots - 1; nPlot++)
						{
							if ((pParameterSamples[0] = (CGRDParameterSamples *)m_cGraphPlots.GetAt(nPlot)) != (CGRDParameterSamples *)NULL)
							{
								if ((pParameterSamples[1] = (CGRDParameterSamples *)m_cGraphPlots.GetAt(nPlot + 1)) != (CGRDParameterSamples *)NULL)
								{
									for (nSample = 0, nSamples = (INT)(pParameterSamples[0]->GetSize() + pParameterSamples[1]->GetSize()); nSample < nSamples; nSample++)
									{
										if ((pParameterSample[0] = pParameterSamples[0]->GetAt(nPlotPositions.GetAt(nPlot))))
										{
											if ((pParameterSample[1] = pParameterSamples[1]->GetAt(nPlotPositions.GetAt(nPlot + 1))))
											{
												if (pParameterSample[0]->GetUpdateTime() == pParameterSample[1]->GetUpdateTime())
												{
													DrawSample(pDC, m_cLayout, nPlot, nPlot + 1, pParameterSample[0], pParameterSample[1], (pParameterSample[0]->IsConnected() && pParameterSample[1]->IsConnected()) ? pParameterSamples[0]->GetAt(nPlotPositions.GetAt(nPlot) - 1) : (CGRDParameterSample *)NULL, (pParameterSample[0]->IsConnected() && pParameterSample[1]->IsConnected()) ? pParameterSamples[1]->GetAt(nPlotPositions.GetAt(nPlot + 1) - 1) : (CGRDParameterSample *)NULL);
													nPlotPositions.SetAt(nPlot + 1, nPlotPositions.GetAt(nPlot + 1) + 1);
													nPlotPositions.SetAt(nPlot, nPlotPositions.GetAt(nPlot) + 1);
													continue;
												}
												if ((pParameterSample[2] = (pParameterSample[0]->GetUpdateTime() < pParameterSample[1]->GetUpdateTime()) ? pParameterSamples[1]->GetAt(nPlotPositions.GetAt(nPlot + 1) - 1) : (CGRDParameterSample *)NULL))
												{
													DrawSample(pDC, m_cLayout, nPlot, nPlot + 1, pParameterSample[0], pParameterSample[2], (pParameterSample[0]->IsConnected() && pParameterSample[2]->IsConnected()) ? pParameterSamples[0]->GetAt(nPlotPositions.GetAt(nPlot) - 1) : (CGRDParameterSample *)NULL, (pParameterSample[0]->IsConnected() && pParameterSample[2]->IsConnected()) ? pParameterSample[2] : (CGRDParameterSample *)NULL);
													nPlotPositions.SetAt(nPlot, nPlotPositions.GetAt(nPlot) + 1);
													continue;
												}
												if ((pParameterSample[2] = (pParameterSample[0]->GetUpdateTime() > pParameterSample[1]->GetUpdateTime()) ? pParameterSamples[0]->GetAt(nPlotPositions.GetAt(nPlot) - 1) : (CGRDParameterSample *)NULL))
												{
													DrawSample(pDC, m_cLayout, nPlot, nPlot + 1, pParameterSample[2], pParameterSample[1], (pParameterSample[1]->IsConnected() && pParameterSample[2]->IsConnected()) ? pParameterSample[2] : (CGRDParameterSample *)NULL, (pParameterSample[1]->IsConnected() && pParameterSample[2]->IsConnected()) ? pParameterSamples[1]->GetAt(nPlotPositions.GetAt(nPlot + 1) - 1) : (CGRDParameterSample *)NULL);
													nPlotPositions.SetAt(nPlot + 1, nPlotPositions.GetAt(nPlot + 1) + 1);
													continue;
												}
											}
											if ((pParameterSample[1] = (nSample >= pParameterSamples[1]->GetSize()) ? pParameterSamples[1]->GetAt((INT)(pParameterSamples[1]->GetSize() - 1)) : (CGRDParameterSample *)NULL))
											{
												DrawSample(pDC, m_cLayout, nPlot, nPlot + 1, pParameterSample[0], pParameterSample[1], (pParameterSample[0]->IsConnected() && pParameterSample[1]->IsConnected()) ? pParameterSamples[0]->GetAt(nPlotPositions.GetAt(nPlot) - 1) : (CGRDParameterSample *)NULL, (pParameterSample[0]->IsConnected() && pParameterSample[1]->IsConnected()) ? pParameterSample[1] : (CGRDParameterSample *)NULL);
												nPlotPositions.SetAt(nPlot, nPlotPositions.GetAt(nPlot) + 1);
												continue;
											}
										}
										if ((pParameterSample[0] = (nSample >= pParameterSamples[0]->GetSize()) ? pParameterSamples[0]->GetAt((INT)(pParameterSamples[0]->GetSize() - 1)) : (CGRDParameterSample *)NULL))
										{
											if ((pParameterSample[1] = (CGRDParameterSample *)pParameterSamples[1]->GetAt(nPlotPositions.GetAt(nPlot + 1))) != (CGRDParameterSample *)NULL)
											{
												DrawSample(pDC, m_cLayout, nPlot, nPlot + 1, pParameterSample[0], pParameterSample[1], (pParameterSample[0]->IsConnected() && pParameterSample[1]->IsConnected()) ? pParameterSample[0] : (CGRDParameterSample *)NULL, (pParameterSample[0]->IsConnected() && pParameterSample[1]->IsConnected()) ? pParameterSamples[1]->GetAt(nPlotPositions.GetAt(nPlot + 1) - 1) : (CGRDParameterSample *)NULL);
												nPlotPositions.SetAt(nPlot + 1, nPlotPositions.GetAt(nPlot + 1) + 1);
												continue;
											}
										}
										break;
									}
								}
							}
							nPlot = nPlot + 1;
						}
					}
					SelectClipRgn(pDC->GetSafeHdc(), (nClipRgn > 0) ? hOldRgn : (HRGN)NULL);
				}
				SetViewportOrgEx(pDC->GetSafeHdc(), ptOffset.x, ptOffset.y, (LPPOINT)NULL);
			}
			DeleteObject(hOldRgn);
		}
		rgnGraph.DeleteObject();
		break;
	}
}
VOID CGRDView::UpdateGraph(CONST CTimeTag &tStartTime, CONST CTimeTag &tStopTime)
{
	CDC  *pDC;
	CDC  cMemDC;
	INT  nType;
	INT  nPlot;
	INT  nPlots;
	INT  nIndex;
	INT  nSample;
	INT  nSamples;
	BOOL  bFirst;
	CRgn  rgnClip;
	CRgn  rgnContent;
	CRect  rContent;
	CRect  rImage;
	CRect  rGraph;
	CRect  rRange;
	CPoint  pt[3];
	CPoint  ptOffset;
	CBitmap  cBitmap[2];
	CBitmap  *pOldBitmap[2];
	CTimeTag  tPlotRange[2];
	CTimeTag  tPlotPosition;
	CPtrArray  pPlotSamples;
	CByteArray  nGraphBits;
	CByteArray  bPlotPositions;
	CUIntArray  nPlotPositions;
	CGRDParameterSample  *pParameterSample[3];
	CGRDParameterSamples  *pParameterSamples[2];
	CCompressionTools  cCompressionTools;

	if ((pDC = m_wndContentCtrl.GetDC()))
	{
		if (cMemDC.CreateCompatibleDC(pDC))
		{
			if (cBitmap[0].CreateCompatibleBitmap(pDC, rGraph.Width(), (rGraph = GetGraphPosition()).Height()))
			{
				if (rgnClip.CreateRectRgn(0, 0, rGraph.Width(), rGraph.Height()) && cMemDC.SelectClipRgn(&rgnClip) != ERROR)
				{
					if (cCompressionTools.Decompress(m_cGraphBits, nGraphBits) && cBitmap[0].SetBitmapBits((DWORD)nGraphBits.GetSize(), nGraphBits.GetData()))
					{
						if ((pOldBitmap[0] = cMemDC.SelectObject(&cBitmap[0])))
						{
							if (m_cLayout.GetMode() & GRDLAYOUT_MODE_OVERWRITE)
							{
								for (nPlot = 0, nPlots = (m_cGraphPlots.GetUpdateRange(tPlotRange[0], tPlotRange[1])) ? (INT)m_cGraphPlots.GetSize() : 0, tPlotPosition = tPlotRange[1] - (m_tGraph[2] - m_tGraph[1]); nPlot < nPlots; nPlot++)
								{
									if ((pParameterSamples[0] = m_cGraphPlots.GetAt(nPlot)) != (CGRDParameterSamples *)NULL)
									{
										for (nSample = 0, nSamples = (INT)(pParameterSamples[0]->GetSize() - 1); nSample < nSamples; nSample++)
										{
											if ((pParameterSample[0] = pParameterSamples[0]->GetAt(nSample)) && pParameterSample[0]->GetUpdateTime() < tPlotPosition)
											{
												if ((pParameterSample[1] = pParameterSamples[0]->GetAt(nSample + 1)) && pParameterSample[1]->GetUpdateTime() <= tPlotPosition)
												{
													pParameterSamples[0]->RemoveAt(nSample);
													delete pParameterSample[0];
													nSamples--;
													nSample--;
													continue;
												}
											}
											break;
										}
									}
								}
							}
							for (ptOffset = cMemDC.SetViewportOrg(-m_ptGraph.x, -m_ptGraph.y), tPlotRange[0] = tStartTime, tPlotRange[1] = tStopTime; m_cLayout.GetType() != GRDLAYOUT_TYPE_DIAGRAM; )
							{
								for (nPlot = 0, nPlots = (INT)m_cGraphPlots.GetSize(), pt[0].x = pt[0].y = pt[1].x = pt[1].y = -1; nPlot < nPlots; nPlot++)
								{
									if ((pParameterSamples[0] = m_cGraphPlots.GetAt(nPlot)) != (CGRDParameterSamples *)NULL)
									{
										for (nSample = nSamples = (INT)pParameterSamples[0]->GetSize(); nSample > 0; nSample--)
										{
											if ((pParameterSample[0] = pParameterSamples[0]->GetAt(nSample - 1)))
											{
												pt[2] = CalcSamplePosition(pParameterSample[0]->GetUpdateTime());
												if (nSample < pParameterSamples[0]->GetSize() && pt[1].x < pt[2].x)
												{
													cMemDC.BitBlt(pt[2].x, 0, rGraph.Width() - pt[2].x, rGraph.Height(), (CDC *)NULL, 0, 0, BLACKNESS);
													pt[0].x = 0;
													pt[0].y = 0;
												}
												else
												{
													pt[0].x = (pt[0].x >= 0) ? min(pt[0].x, max(pt[2].x, 0)) : max(pt[2].x, 0);
													pt[0].y = (pt[0].y >= 0) ? min(pt[0].y, pt[2].y) : pt[2].y;
													pt[1].x = (pt[1].x >= 0) ? max(pt[1].x, max(pt[2].x, 0)) : max(pt[2].x, 0);
													pt[1].y = (pt[1].y >= 0) ? max(pt[1].y, pt[2].y) : pt[2].y;
												}
												tPlotRange[0] = min(pParameterSample[0]->GetUpdateTime(), tPlotRange[0]);
												tPlotRange[1] = max(pParameterSample[0]->GetUpdateTime(), tPlotRange[1]);
												if (pParameterSample[0]->GetUpdateTime() < tStartTime) break;
											}
										}
									}
								}
								for (tPlotRange[0] = tPlotRange[0].GetTime() - (GRDSETTINGSPARAMETERSPAGE_MAXIMUMLINEWIDTH*(m_tGraph[2].GetTime() - m_tGraph[1].GetTime())) / rGraph.Width(); (m_cLayout.GetMode() & GRDLAYOUT_MODE_SCROLL) != GRDLAYOUT_MODE_SCROLL && pt[0].x >= 0 && pt[0].x <= pt[1].x; )
								{
									cMemDC.BitBlt(pt[0].x, 0, min(pt[1].x - pt[0].x + 1, rGraph.Width() - pt[0].x), rGraph.Height(), (CDC *)NULL, 0, 0, BLACKNESS);
									break;
								}
								break;
							}
							if ((nType = m_cLayout.GetType()) == GRDLAYOUT_TYPE_NORMAL || nType == GRDLAYOUT_TYPE_STRIPCHART)
							{
								for (nPlot = 0, nPlots = (INT)m_cGraphPlots.GetSize(); nPlot < nPlots; nPlot = nPlot + 1)
								{
									if ((pParameterSamples[0] = m_cGraphPlots.GetAt(nPlot)) != (CGRDParameterSamples *)NULL)
									{
										for (nSample = pParameterSamples[0]->Find(tPlotRange[0]), nSample = max(nSample - 1, 0), nSamples = (INT)pParameterSamples[0]->GetSize(), bFirst = TRUE; nSample < nSamples; nSample++)
										{
											if ((pParameterSample[0] = pParameterSamples[0]->GetAt(nSample)) && pParameterSample[0]->GetUpdateTime() <= tPlotRange[1])
											{
												DrawSample(&cMemDC, m_cLayout, nPlot, pParameterSample[0], (!bFirst  &&  pParameterSample[0]->IsConnected()) ? pParameterSamples[0]->GetAt(nSample - 1) : (CGRDParameterSample *)NULL);
												bFirst = FALSE;
												continue;
											}
											break;
										}
									}
								}
							}
							if (nType == GRDLAYOUT_TYPE_STACKCHART)
							{
								for (nPlot = 0, nPlots = (INT)m_cGraphPlots.GetSize(), pPlotSamples.SetSize(m_cGraphPlots.GetSize()), nPlotPositions.SetSize(m_cGraphPlots.GetSize()), bPlotPositions.SetSize(m_cGraphPlots.GetSize()); nPlot < nPlots; nPlot++)
								{
									if ((pParameterSamples[0] = m_cGraphPlots.GetAt(nPlot)) != (CGRDParameterSamples *)NULL)
									{
										nPlotPositions.SetAt(nPlot, pParameterSamples[0]->Find(tPlotRange[0]));
										bPlotPositions.SetAt(nPlot, TRUE);
									}
								}
								for (tPlotPosition = 0; TRUE; tPlotPosition = 0)
								{
									for (nPlot = 0, nPlots = (INT)m_cGraphPlots.GetSize(), nIndex = -1; nPlot < nPlots; nPlot++)
									{
										if ((pParameterSamples[0] = m_cGraphPlots.GetAt(nPlot)) != (CGRDParameterSamples *)NULL)
										{
											if ((pParameterSample[0] = pParameterSamples[0]->GetAt(nPlotPositions.GetAt(nPlot))) && pParameterSample[0]->GetUpdateTime() <= tPlotRange[1])
											{
												if (pParameterSample[0]->GetUpdateTime() < tPlotPosition || !tPlotPosition.GetTime())
												{
													tPlotPosition = pParameterSample[0]->GetUpdateTime();
													nIndex = nPlot;
												}
											}
										}
									}
									if ((pParameterSamples[0] = m_cGraphPlots.GetAt(nIndex)))
									{
										if ((pParameterSample[0] = pParameterSamples[0]->GetAt(nPlotPositions.GetAt(nIndex))))
										{
											for (nPlot = 0, nPlots = (INT)m_cGraphPlots.GetSize(); nPlot < nPlots; nPlot = nPlot + 1)
											{
												if ((pParameterSamples[1] = m_cGraphPlots.GetAt(nPlot)) != (CGRDParameterSamples *)NULL)
												{
													if ((pParameterSample[1] = pParameterSamples[1]->GetAt((nSample = nPlotPositions.GetAt(nPlot)))) && pParameterSample[1]->GetUpdateTime() <= pParameterSample[0]->GetUpdateTime())
													{
														pPlotSamples.SetAt(nPlot, pParameterSample[1]);
														continue;
													}
													pPlotSamples.SetAt(nPlot, (pParameterSample[1] = (nSample > 0) ? pParameterSamples[1]->GetAt(nSample - 1) : (CGRDParameterSample *)NULL));
													continue;
												}
												pPlotSamples.SetAt(nPlot, (LPVOID)NULL);
											}
											DrawSample(&cMemDC, m_cLayout, nIndex, pPlotSamples, (!bPlotPositions.GetAt(nIndex) && pParameterSample[0]->IsConnected()) ? pParameterSamples[0]->GetAt(nPlotPositions.GetAt(nIndex) - 1) : (CGRDParameterSample *)NULL);
											nPlotPositions.SetAt(nIndex, nPlotPositions.GetAt(nIndex) + 1);
											bPlotPositions.SetAt(nIndex, FALSE);
											continue;
										}
									}
									break;
								}
							}
							if (nType == GRDLAYOUT_TYPE_DIAGRAM)
							{
								for (nPlot = 0, nPlots = (INT)m_cGraphPlots.GetSize(), nPlotPositions.SetSize(nPlots); nPlot < nPlots - 1; nPlot++)
								{
									if ((pParameterSamples[0] = (CGRDParameterSamples *)m_cGraphPlots.GetAt(nPlot)) != (CGRDParameterSamples *)NULL)
									{
										if ((pParameterSamples[1] = (CGRDParameterSamples *)m_cGraphPlots.GetAt(nPlot + 1)) != (CGRDParameterSamples *)NULL)
										{
											for (nSample = min(max(pParameterSamples[0]->Find(tPlotRange[0]), 0), max(pParameterSamples[1]->Find(tPlotRange[0]), 0)), nSamples = (INT)(pParameterSamples[0]->GetSize() + pParameterSamples[1]->GetSize()); nSample < nSamples; nSample++)
											{
												if ((pParameterSample[0] = pParameterSamples[0]->GetAt(nPlotPositions.GetAt(nPlot))) && pParameterSample[0]->GetUpdateTime() <= tPlotRange[1])
												{
													if ((pParameterSample[1] = pParameterSamples[1]->GetAt(nPlotPositions.GetAt(nPlot + 1))) && pParameterSample[1]->GetUpdateTime() <= tPlotRange[1])
													{
														if (pParameterSample[0]->GetUpdateTime() == pParameterSample[1]->GetUpdateTime())
														{
															DrawSample(&cMemDC, m_cLayout, nPlot, nPlot + 1, pParameterSample[0], pParameterSample[1], (pParameterSample[0]->IsConnected() && pParameterSample[1]->IsConnected()) ? pParameterSamples[0]->GetAt(nPlotPositions.GetAt(nPlot) - 1) : (CGRDParameterSample *)NULL, (pParameterSample[0]->IsConnected() && pParameterSample[1]->IsConnected()) ? pParameterSamples[1]->GetAt(nPlotPositions.GetAt(nPlot + 1) - 1) : (CGRDParameterSample *)NULL);
															nPlotPositions.SetAt(nPlot + 1, nPlotPositions.GetAt(nPlot + 1) + 1);
															nPlotPositions.SetAt(nPlot, nPlotPositions.GetAt(nPlot) + 1);
															continue;
														}
														if ((pParameterSample[2] = (pParameterSample[0]->GetUpdateTime() < pParameterSample[1]->GetUpdateTime()) ? pParameterSamples[1]->GetAt(nPlotPositions.GetAt(nPlot + 1) - 1) : (CGRDParameterSample *)NULL))
														{
															DrawSample(&cMemDC, m_cLayout, nPlot, nPlot + 1, pParameterSample[0], pParameterSample[2], (pParameterSample[0]->IsConnected() && pParameterSample[2]->IsConnected()) ? pParameterSamples[0]->GetAt(nPlotPositions.GetAt(nPlot) - 1) : (CGRDParameterSample *)NULL, (pParameterSample[0]->IsConnected() && pParameterSample[2]->IsConnected()) ? pParameterSample[2] : (CGRDParameterSample *)NULL);
															nPlotPositions.SetAt(nPlot, nPlotPositions.GetAt(nPlot) + 1);
															continue;
														}
														if ((pParameterSample[2] = (pParameterSample[0]->GetUpdateTime() > pParameterSample[1]->GetUpdateTime()) ? pParameterSamples[0]->GetAt(nPlotPositions.GetAt(nPlot) - 1) : (CGRDParameterSample *)NULL))
														{
															DrawSample(&cMemDC, m_cLayout, nPlot, nPlot + 1, pParameterSample[2], pParameterSample[1], (pParameterSample[1]->IsConnected() && pParameterSample[2]->IsConnected()) ? pParameterSample[2] : (CGRDParameterSample *)NULL, (pParameterSample[1]->IsConnected() && pParameterSample[2]->IsConnected()) ? pParameterSamples[1]->GetAt(nPlotPositions.GetAt(nPlot + 1) - 1) : (CGRDParameterSample *)NULL);
															nPlotPositions.SetAt(nPlot + 1, nPlotPositions.GetAt(nPlot + 1) + 1);
															continue;
														}
													}
													if ((pParameterSample[1] = pParameterSamples[1]->GetAt(nPlotPositions.GetAt(nPlot + 1) - 1)) && pParameterSample[1]->GetUpdateTime() <= tPlotRange[1])
													{
														DrawSample(&cMemDC, m_cLayout, nPlot, nPlot + 1, pParameterSample[0], pParameterSample[1], (pParameterSample[0]->IsConnected() && pParameterSample[1]->IsConnected()) ? pParameterSamples[0]->GetAt(nPlotPositions.GetAt(nPlot) - 1) : (CGRDParameterSample *)NULL, (pParameterSample[0]->IsConnected() && pParameterSample[1]->IsConnected()) ? pParameterSample[1] : (CGRDParameterSample *)NULL);
														nPlotPositions.SetAt(nPlot, nPlotPositions.GetAt(nPlot) + 1);
														continue;
													}
												}
												if ((pParameterSample[0] = pParameterSamples[0]->GetAt(nPlotPositions.GetAt(nPlot) - 1)) && pParameterSample[0]->GetUpdateTime() <= tPlotRange[1])
												{
													if ((pParameterSample[1] = pParameterSamples[1]->GetAt(nPlotPositions.GetAt(nPlot + 1))) && pParameterSample[1]->GetUpdateTime() <= tPlotRange[1])
													{
														DrawSample(&cMemDC, m_cLayout, nPlot, nPlot + 1, pParameterSample[0], pParameterSample[1], (pParameterSample[0]->IsConnected() && pParameterSample[1]->IsConnected()) ? pParameterSample[0] : (CGRDParameterSample *)NULL, (pParameterSample[0]->IsConnected() && pParameterSample[1]->IsConnected()) ? pParameterSamples[1]->GetAt(nPlotPositions.GetAt(nPlot + 1) - 1) : (CGRDParameterSample *)NULL);
														nPlotPositions.SetAt(nPlot + 1, nPlotPositions.GetAt(nPlot + 1) + 1);
														continue;
													}
												}
												break;
											}
										}
									}
									nPlot++;
								}
							}
							for (m_wndContentCtrl.GetClientRect(rContent), rImage = GetImagePosition(), cMemDC.SetViewportOrg(ptOffset), cMemDC.SelectClipRgn((CRgn *)NULL); cBitmap[0].GetBitmapBits((DWORD)nGraphBits.GetSize(), nGraphBits.GetData()) > 0 && cCompressionTools.Compress(nGraphBits, m_cGraphBits); )
							{
								if (cBitmap[1].CreateCompatibleBitmap(&cMemDC, rImage.left + rImage.Width(), rImage.top + rImage.Height()))
								{
									if (rgnContent.CreateRectRgn(rContent.left, rContent.top, rContent.right, rContent.bottom))
									{
										if ((pOldBitmap[1] = cMemDC.SelectObject(&cBitmap[1])))
										{
											if (pDC->SelectClipRgn(&rgnContent, RGN_COPY) != ERROR)
											{
												for (DrawGraph(&cMemDC); m_cLayout.GetMode() & GRDLAYOUT_MODE_OVERWRITE; )
												{
													DrawSlider(&cMemDC);
													break;
												}
												pDC->BitBlt(rImage.left - m_wndContentCtrl.m_nScrollPos[0], rImage.top - m_wndContentCtrl.m_nScrollPos[1], rImage.Width(), rImage.Height(), &cMemDC, rImage.left, rImage.top, SRCCOPY);
												pDC->SelectClipRgn((CRgn *)NULL);
											}
											cMemDC.SelectObject(pOldBitmap[1]);
										}
										rgnContent.DeleteObject();
									}
									cBitmap[1].DeleteObject();
								}
								break;
							}
							cMemDC.SelectObject(pOldBitmap[0]);
						}
					}
					cMemDC.SelectClipRgn((CRgn *)NULL);
					rgnClip.DeleteObject();
				}
				cBitmap[0].DeleteObject();
			}
			cMemDC.DeleteDC();
		}
		m_wndContentCtrl.ReleaseDC(pDC);
	}
}

VOID CGRDView::RestartGraph(CONST CTimeTag &tStartTime, CONST CTimeTag &tStopTime)
{
	m_tGraph[0] = m_tGraph[1] = m_tGraph[0].GetTime() + 1000000 * m_cLayout.GetDuration().GetTotalSeconds()*((tStopTime.GetTime() - m_tGraph[0].GetTime()) / (1000000 * (TIMETAG)m_cLayout.GetDuration().GetTotalSeconds()));
	m_tGraph[2] = (m_cLayout.GetInterval() > 0) ? (m_tGraph[0].GetTime() + 1000000 * m_cLayout.GetInterval().GetTotalSeconds()) : (m_tGraph[0].GetTime() + 1000000 * m_cLayout.GetDuration().GetTotalSeconds());
	m_cGraphPlots.SetUpdateRange(tStartTime, tStopTime);
}

VOID CGRDView::ScrollGraph(CONST CTimeTag &tStartTime, CONST CTimeTag &tStopTime, CONST CTimeTag &tTime)
{
	CDC  *pDC;
	CDC  cMemDC;
	INT  nPlot;
	INT  nPlots;
	INT  nSample;
	INT  nSamples;
	CRgn  rgnClip;
	CRgn  rgnContent;
	CRect  rContent;
	CRect  rClip;
	CRect  rImage;
	CRect  rGraph;
	CPoint  ptOffset;
	CBitmap  cBitmap[2];
	CBitmap  *pOldBitmap[2];
	CTimeTag  tRange[2];
	CTimeTag  tSampleTime;
	CByteArray  nGraphBits;
	CGRDParameterSample  *pParameterSample[2];
	CGRDParameterSamples  *pParameterSamples;
	CCompressionTools  cCompressionTools;

	if (tTime >= tStopTime)
	{
		for (nPlot = 0, nPlots = (INT)m_cGraphPlots.GetSize(), tSampleTime = (tTime.GetTime() - tStopTime.GetTime() <= (tStopTime.GetTime() - tStartTime.GetTime()) / 10) ? (m_tGraph[1].GetTime() + (tStopTime.GetTime() - tStartTime.GetTime()) / 10) : (m_tGraph[1].GetTime() + tTime.GetTime() - tStopTime.GetTime()), ptOffset = CalcSamplePosition(tSampleTime), tRange[0] = tStopTime, tRange[1] = tTime; nPlot < nPlots; nPlot++)
		{
			if ((pParameterSamples = (CGRDParameterSamples *)m_cGraphPlots.GetAt(nPlot)) != (CGRDParameterSamples *)NULL)
			{
				for (nSample = 0, nSamples = (INT)(pParameterSamples->GetSize() - 1); nSample < nSamples; nSample = nSample + 1)
				{
					if ((pParameterSample[0] = pParameterSamples->GetAt(nSample)) && pParameterSample[0]->GetUpdateTime() < tSampleTime)
					{
						if ((pParameterSample[1] = pParameterSamples->GetAt(nSample + 1)) && pParameterSample[1]->GetUpdateTime() <= tSampleTime)
						{
							pParameterSamples->RemoveAt(nSample);
							delete pParameterSample[0];
							nSamples--;
							nSample--;
							continue;
						}
					}
					break;
				}
			}
		}
		if ((pDC = m_wndContentCtrl.GetDC()))
		{
			if (cMemDC.CreateCompatibleDC(pDC))
			{
				if (cBitmap[0].CreateCompatibleBitmap(pDC, rGraph.Width(), (rGraph = GetGraphPosition()).Height()))
				{
					if (rgnClip.CreateRectRgn(0, 0, rGraph.Width(), rGraph.Height()) && cMemDC.SelectClipRgn(&rgnClip) != ERROR)
					{
						if (cCompressionTools.Decompress(m_cGraphBits, nGraphBits) && cBitmap[0].SetBitmapBits((DWORD)nGraphBits.GetSize(), nGraphBits.GetData()))
						{
							if ((pOldBitmap[0] = (CBitmap *)cMemDC.SelectObject(&cBitmap[0])))
							{
								for (rClip = rGraph, rClip.OffsetRect(-rGraph.TopLeft()); TRUE; )
								{
									cMemDC.ScrollDC(m_ptGraph.x - ptOffset.x, 0, rClip, rClip, (CRgn *)NULL, (LPRECT)NULL);
									cMemDC.BitBlt(rClip.right - (ptOffset.x - m_ptGraph.x), rClip.top, ptOffset.x - m_ptGraph.x, rClip.Height(), (CDC *)NULL, 0, 0, BLACKNESS);
									break;
								}
								if (cBitmap[0].GetBitmapBits((DWORD)nGraphBits.GetSize(), nGraphBits.GetData()) > 0 && cCompressionTools.Compress(nGraphBits, m_cGraphBits))
								{
									for (m_wndContentCtrl.GetClientRect(rContent), rImage = GetImagePosition(), cMemDC.SelectClipRgn((CRgn *)NULL); rgnContent.CreateRectRgn(rContent.left, rContent.top, rContent.right, rContent.bottom); )
									{
										if (cBitmap[1].CreateCompatibleBitmap(&cMemDC, rImage.left + rImage.Width(), rImage.top + rImage.Height()))
										{
											if ((pOldBitmap[1] = cMemDC.SelectObject(&cBitmap[1])))
											{
												if (pDC->SelectClipRgn(&rgnContent) != ERROR)
												{
													for (m_ptGraph = ptOffset, m_tGraph[1] = tSampleTime, m_tGraph[2] = (m_cLayout.GetInterval() > 0) ? (tSampleTime.GetTime() + 1000000 * m_cLayout.GetInterval().GetTotalSeconds()) : (tSampleTime.GetTime() + 1000000 * (TIMETAG)m_cLayout.GetDuration().GetTotalSeconds()); m_cLayout.GetDuration() >= 0; )
													{
														DrawGraph(&cMemDC);
														break;
													}
													pDC->BitBlt(rImage.left - m_wndContentCtrl.m_nScrollPos[0], rImage.top - m_wndContentCtrl.m_nScrollPos[1], rImage.Width(), rImage.Height(), &cMemDC, rImage.left, rImage.top, SRCCOPY);
													pDC->SelectClipRgn((CRgn *)NULL);
												}
												cMemDC.SelectObject(pOldBitmap[1]);
											}
											cBitmap[1].DeleteObject();
										}
										rgnContent.DeleteObject();
										break;
									}
								}
								cMemDC.SelectObject(pOldBitmap[0]);
							}
						}
						cMemDC.SelectClipRgn((CRgn *)NULL);
						rgnClip.DeleteObject();
					}
					cBitmap[0].DeleteObject();
				}
				cMemDC.DeleteDC();
			}
			m_wndContentCtrl.ReleaseDC(pDC);
		}
		UpdateGraph(tRange[0], tRange[1]);
	}
}

VOID CGRDView::OverwriteGraph(CONST CTimeTag &tStartTime, CONST CTimeTag &tStopTime, CONST CTimeTag &tTime)
{
	INT  nPlot;
	INT  nPlots;
	INT  nSample;
	INT  nSamples;
	CPtrArray  *pPlots;
	CGRDParameterSample  *pParameterSample;
	CGRDParameterSamples  *pParameterSamples;

	if ((tTime >= tStopTime))
	{
		if ((pPlots = new CPtrArray[m_cGraphPlots.GetSize()]))
		{
			for (nPlot = 0, nPlots = (INT)m_cGraphPlots.GetSize(); nPlot < nPlots; nPlot++)
			{
				if ((pParameterSamples = m_cGraphPlots.GetAt(nPlot)) != (CGRDParameterSamples *)NULL)
				{
					for (nSample = nSamples = (INT)pParameterSamples->GetSize(); nSample > 0; nSample--)
					{
						if ((pParameterSample = pParameterSamples->GetAt(nSample - 1)) && pParameterSample->GetUpdateTime() >= tStopTime)
						{
							pPlots[nPlot].InsertAt(0, pParameterSample, 1);
							pParameterSamples->RemoveAt(nSample - 1);
							nSamples--;
							nSample--;
							continue;
						}
						break;
					}
				}
			}
			for (nPlot = 0, nPlots = (INT)m_cGraphPlots.GetSize(), GetParent()->ExecutePrintJobs(); nPlot < nPlots; nPlot++)
			{
				if ((pParameterSamples = m_cGraphPlots.GetAt(nPlot)) != (CGRDParameterSamples *)NULL)
				{
					for (nSample = 0, nSamples = (INT)pPlots[nPlot].GetSize(); nSample < nSamples; nSample++)
					{
						if ((pParameterSample = (CGRDParameterSample *)pPlots[nPlot].GetAt(nSample)))
						{
							pParameterSamples->Add(m_cLayout.GetAt(nPlot), pParameterSample);
							continue;
						}
					}
				}
			}
		}
		m_tGraph[0] = m_tGraph[1] = tStopTime.GetTime() + (tStopTime.GetTime() - tStartTime.GetTime())*((tTime.GetTime() - tStopTime.GetTime()) / (tStopTime.GetTime() - tStartTime.GetTime()));
		m_tGraph[2] = m_tGraph[1].GetTime() + 1000000 * m_cLayout.GetDuration().GetTotalSeconds();
		UpdateGraph(m_tGraph[1], tTime);
		delete[] pPlots;
	}
}

VOID CGRDView::UpdateGraphScaling()
{
	INT  nColumn;
	INT  nColumns;
	INT  nWidth[2];
	INT  nParameter;
	INT  nParameters;
	double  fMinimum;
	double  fMaximum;
	CString  szRange;
	CString  szMinimum;
	CString  szMaximum;
	CGRDLayoutParameter  *pParameter;

	for (nColumn = 0, nColumns = (INT)m_nLayoutColumns.GetSize(); nColumn < nColumns; nColumn++)
	{
		if (m_nLayoutColumns.GetAt(nColumn) == GRD_TITLEITEM_RANGE) break;
		continue;
	}
	for (nParameter = 0, nParameters = (nColumn < nColumns) ? (INT)m_cLayout.GetSize() : 0, nWidth[0] = 0; nParameter < nParameters; nParameter++)
	{
		if ((pParameter = m_cLayout.GetAt(nParameter)) && pParameter->GetRange(fMinimum, fMaximum))
		{
			ConvertAxesRangeValues(pParameter, fMinimum, fMaximum, szMinimum, szMaximum);
			szRange.Format(STRING(IDS_GRD_TITLEITEMS_RANGEFORMAT), (LPCTSTR)szMinimum, (LPCTSTR)szMaximum);
			SetText(nParameter, nColumn, szRange, FALSE);
			nWidth[1] = CalcColumnWidth(nColumn, szRange);
			nWidth[0] = max(nWidth[0], nWidth[1]);
		}
	}
	for (nWidth[1] = (nColumn < nColumns) ? ((nColumn > 0) ? (nWidth[0] - m_wndHeaderCtrl.m_nColumnsWidth.GetAt(nColumn) + m_wndHeaderCtrl.m_nColumnsWidth.GetAt(nColumn - 1)) : (nWidth[0] - m_wndHeaderCtrl.m_nColumnsWidth.GetAt(nColumn))) : 0; nColumn < nColumns; nColumn++)
	{
		m_wndHeaderCtrl.m_nColumnsWidth.SetAt(nColumn, m_wndHeaderCtrl.m_nColumnsWidth.GetAt(nColumn) + nWidth[1]);
		continue;
	}
}

CPoint CGRDView::GetImageOffset() CONST
{
	return CPoint(m_wndContentCtrl.m_wTextIndent[0], (m_wndContentCtrl.m_nContentTextPos.GetSize() > 0) ? (m_wndContentCtrl.m_nContentTextPos.GetAt(m_wndContentCtrl.m_nContentTextPos.GetUpperBound()) + m_wndContentCtrl.m_wTextSpacing[1]) : m_wndContentCtrl.m_wTextSpacing[1]);
}

CPoint CGRDView::GetGraphOffset() CONST
{
	INT  nType;
	INT  nLine;
	INT  nLines;
	INT  nWidth;
	CPoint  ptOffset;
	double  fMinimum;
	double  fMaximum;
	CString  szMinimum;
	CString  szMaximum;
	CGRDLayoutParameter  *pParameter;

	for (nLine = 0, nLines = ((nType = m_cLayout.GetType()) == GRDLAYOUT_TYPE_STRIPCHART || nType == GRDLAYOUT_TYPE_DIAGRAM) ? (INT)m_cLayout.GetSize() : 0, nWidth = 0, ptOffset = GetImageOffset() + GetAxesStubs(); nLine < nLines; nLine++)
	{
		if ((pParameter = m_cLayout.GetAt(nLine)) && nType == GRDLAYOUT_TYPE_STRIPCHART  &&  pParameter->GetRange(fMinimum, fMaximum))
		{
			ConvertAxesRangeValues(pParameter, fMinimum, fMaximum, szMinimum, szMaximum);
			nWidth += max(CalcAxesSymbolWidth(pParameter->GetName()) - nWidth, 0);
			nWidth += max(CalcAxesSymbolWidth(szMinimum) - nWidth, 0);
			nWidth += max(CalcAxesSymbolWidth(szMaximum) - nWidth, 0);
			continue;
		}
		if ((pParameter = m_cLayout.GetAt(nLine)) && nType == GRDLAYOUT_TYPE_DIAGRAM  &&  nLine % 2)
		{
			nWidth += max(CalcAxesSymbolWidth(pParameter->GetName()) - nWidth, 0);
			continue;
		}
	}
	if (nLines > 0)
	{
		ptOffset.x += nWidth;
		ptOffset.x += GetAxesStubs().cx;
	}
	return ptOffset;
}

CRect CGRDView::GetImagePosition() CONST
{
	CRect  rImage;
	CSize  sizeGraph;
	CPoint  ptOffset[2];

	sizeGraph = GetGraphSize();
	ptOffset[0] = GetImageOffset();
	ptOffset[1] = GetGraphOffset();
	rImage.SetRect(ptOffset[0].x, ptOffset[0].y, ptOffset[1].x + sizeGraph.cx + GetAxesStubs().cx, ptOffset[1].y + sizeGraph.cy + m_sizeLayoutFont.cy + GetAxesStubs().cy);
	rImage.OffsetRect(0, m_wndContentCtrl.m_wTextSpacing[0]);
	return rImage;
}

CRect CGRDView::GetGraphPosition() CONST
{
	CRect  rGraph;
	CSize  sizeGraph;
	CPoint  ptOffset;

	sizeGraph = GetGraphSize();
	ptOffset = GetGraphOffset();
	rGraph.SetRect(ptOffset.x, ptOffset.y, ptOffset.x + sizeGraph.cx, ptOffset.y + sizeGraph.cy);
	rGraph.OffsetRect(0, m_wndContentCtrl.m_wTextSpacing[0]);
	return rGraph;
}

CRect CGRDView::GetLegendPosition() CONST
{
	INT  nColumn;
	INT  nColumns;
	CRect  rColumn[3];

	for (nColumn = 0, nColumns = (m_wndContentCtrl.m_szContentText.GetSize() > 0) ? (INT)m_nLayoutColumns.GetSize() : 0, rColumn[0].SetRectEmpty(); nColumn < nColumns; nColumn++)
	{
		if (m_nLayoutColumns.GetAt(nColumn) == GRD_TITLEITEM_LINE) break;
		continue;
	}
	if (nColumn < nColumns)
	{
		rColumn[1] = m_wndContentCtrl.CalcTextRect(0, nColumn);
		rColumn[2] = m_wndContentCtrl.CalcTextRect((INT)(m_cLayout.GetSize() - 1), nColumn);
		rColumn[0].UnionRect(rColumn[1], rColumn[2]);
	}
	return rColumn[0];
}

CSize CGRDView::GetGraphSize() CONST
{
	CSize  sizeGraph;

	sizeGraph.cx = (m_cLayout.GetPlotSize().cx > 0) ? m_cLayout.GetPlotSize().cx : GRDLAYOUT_GRAPH_WIDTH;
	sizeGraph.cy = (m_cLayout.GetPlotSize().cy > 0) ? m_cLayout.GetPlotSize().cy : GRDLAYOUT_GRAPH_HEIGHT;
	return sizeGraph;
}

CSize CGRDView::GetAxesStubs() CONST
{
	return CSize(m_sizeLayoutFont.cy / 3, m_sizeLayoutFont.cy / 3);
}

BOOL CGRDView::FindSamplePosition(CONST POINT &point) CONST
{
	CGRDParameterSample  cSample;

	return((FindSamplePosition(point, cSample)) ? TRUE : FALSE);
}
CGRDLayoutParameter *CGRDView::FindSamplePosition(CONST POINT &point, CGRDParameterSample &cSample) CONST
{
	INT  nPlot;
	INT  nPlots;
	CRect  rGraph;
	CPoint  ptSample;
	CTimeTag  tSample;
	CTimeTag  tRange[2];
	CGRDLayoutParameter  *pParameter;
	CGRDParameterSample  *pParameterSample;
	CGRDParameterSamples  *pParameterSamples;

	if ((rGraph = GetGraphPosition()).PtInRect(point))
	{
		for (nPlot = 0, nPlots = (INT)m_cGraphPlots.GetSize(), tSample = (m_tGraph[1].GetTime() + ((point.x - rGraph.left)*(m_tGraph[2].GetTime() - m_tGraph[1].GetTime())) / (rGraph.right - rGraph.left)), tSample = ((m_cLayout.GetMode() & GRDLAYOUT_MODE_OVERWRITE) && m_cGraphPlots.GetUpdateRange(tRange[0], tRange[1]) && tSample > tRange[1]) ? (tSample.GetTime() - (m_tGraph[2].GetTime() - m_tGraph[1].GetTime())) : tSample, ptSample = point, ptSample += m_ptGraph - rGraph.TopLeft(); nPlot < nPlots; nPlot++)
		{
			if ((pParameter = (CGRDLayoutParameter *)m_cLayout.GetAt(nPlot)) != (CGRDLayoutParameter *)NULL)
			{
				if ((pParameterSamples = m_cGraphPlots.GetAt(nPlot)) != (CGRDParameterSamples *)NULL)
				{
					if ((pParameterSample = pParameterSamples->GetAt(pParameterSamples->Find(tSample, ptSample, CalcSampleSymbolSize(pParameter->GetLineWidth())))))
					{
						cSample.Copy(pParameterSample);
						return pParameter;
					}
				}
			}
		}
	}
	return((CGRDLayoutParameter *)NULL);
}

BOOL CGRDView::CalcContentExtent(CSize &size) CONST
{
	for (size.cx = 2 * GetImageOffset().x + GetImagePosition().Width(); m_wndHeaderCtrl.m_szColumnsText.GetSize() > 0; )
	{
		size.cx = max((LONG)m_wndHeaderCtrl.m_nColumnsWidth.GetAt(m_wndHeaderCtrl.m_nColumnsWidth.GetUpperBound()), size.cx);
		break;
	}
	size.cy = GetImageOffset().y + GetImagePosition().Height();
	return TRUE;
}

CSize CGRDView::CalcPlotAreaExtent() CONST
{
	CSize  sizePlot[2];
	LOGFONT  lfFont[4];

	for (sizePlot[0].cx = (m_sizeLayoutDefault.cx > 0) ? m_sizeLayoutDefault.cx : GRDLAYOUT_GRAPH_WIDTH, sizePlot[0].cy = (m_sizeLayoutDefault.cy > 0) ? m_sizeLayoutDefault.cy : GRDLAYOUT_GRAPH_HEIGHT, sizePlot[1].cx = (m_wndHeaderCtrl.m_cFont.GetObject(sizeof(LOGFONT), &lfFont[0]) > 0 && m_wndContentCtrl.m_cFont.GetObject(sizeof(LOGFONT), &lfFont[1]) > 0 && m_cLayoutFont[0].GetObject(sizeof(LOGFONT), &lfFont[2]) > 0 && m_cLayoutFont[1].GetObject(sizeof(LOGFONT), &lfFont[3]) > 0) ? ((sizePlot[0].cx*max(max(max(lfFont[3].lfHeight, lfFont[2].lfHeight), lfFont[1].lfHeight), lfFont[0].lfHeight)) / max(max(max(m_lfLayoutDefault[3].lfHeight, m_lfLayoutDefault[2].lfHeight), m_lfLayoutDefault[1].lfHeight), m_lfLayoutDefault[0].lfHeight)) : sizePlot[0].cx, sizePlot[1].cy = (sizePlot[0].cy*sizePlot[1].cx) / sizePlot[0].cx; m_cLayout.GetSize() > 0; )
	{
		if ((m_cLayout.GetType() == GRDLAYOUT_TYPE_NORMAL || m_cLayout.GetType() == GRDLAYOUT_TYPE_STACKCHART) && sizePlot[1].cy < 4 * m_sizeLayoutFont.cy)
		{
			sizePlot[1].cx = (4 * m_sizeLayoutFont.cy*sizePlot[1].cx) / sizePlot[1].cy;
			sizePlot[1].cy = 4 * m_sizeLayoutFont.cy;
		}
		if (m_cLayout.GetType() == GRDLAYOUT_TYPE_STRIPCHART  &&  sizePlot[1].cy < 4 * m_sizeLayoutFont.cy*m_cLayout.GetSize())
		{
			sizePlot[1].cx = (4 * m_sizeLayoutFont.cy*(LONG)m_cLayout.GetSize()*sizePlot[1].cx) / sizePlot[1].cy;
			sizePlot[1].cy = 4 * m_sizeLayoutFont.cy*(LONG)m_cLayout.GetSize();
		}
		if (m_cLayout.GetType() == GRDLAYOUT_TYPE_DIAGRAM  &&  sizePlot[1].cy < 4 * m_sizeLayoutFont.cy*(m_cLayout.GetSize() / 2))
		{
			sizePlot[1].cx = (4 * m_sizeLayoutFont.cy*(LONG)(m_cLayout.GetSize() / 2)*sizePlot[1].cx) / sizePlot[1].cy;
			sizePlot[1].cy = 4 * m_sizeLayoutFont.cy*(LONG)(m_cLayout.GetSize() / 2);
		}
		break;
	}
	return sizePlot[1];
}

CPoint CGRDView::CalcSamplePosition(INT nPlot, CONST CGRDParameterSample *pParameterSample, double fValue, CRect &rPlot) CONST
{
	INT  nType;
	CRect  rGraph;
	CPoint  ptSample;
	double  fRange[2];
	CGRDLayoutParameter  *pParameter;

	if ((nType = m_cLayout.GetType()) == GRDLAYOUT_TYPE_NORMAL)
	{
		if ((pParameter = m_cLayout.GetAt(nPlot)) && pParameter->GetRange(fRange[0], fRange[1]))
		{
			for (rGraph = GetGraphPosition(), rPlot.SetRect(0, 0, rGraph.Width() + 1, rGraph.Height() + 1), ptSample.x = (INT)(rGraph.left + (rGraph.Width()*(pParameterSample->GetUpdateTime().GetTime() - m_tGraph[0].GetTime())) / (m_tGraph[2].GetTime() - m_tGraph[1].GetTime())), ptSample.y = (INT)(rGraph.bottom - (rGraph.Height()*(fValue - fRange[0])) / (fRange[1] - fRange[0])), ptSample.Offset(-rGraph.TopLeft()); (m_cLayout.GetMode() & GRDLAYOUT_MODE_OVERWRITE) && pParameterSample->GetUpdateTime() < m_tGraph[1]; )
			{
				ptSample.x = (INT)((rGraph.Width()*(pParameterSample->GetUpdateTime().GetTime() - (m_tGraph[0].GetTime() - (m_tGraph[2].GetTime() - m_tGraph[1].GetTime())))) / (m_tGraph[2].GetTime() - m_tGraph[1].GetTime()));
				break;
			}
			return ptSample;
		}
	}
	if (nType == GRDLAYOUT_TYPE_STRIPCHART)
	{
		if ((pParameter = m_cLayout.GetAt(nPlot)) && pParameter->GetRange(fRange[0], fRange[1]) && pParameter->GetPosition() >= 0)
		{
			for (rGraph = GetGraphPosition(), rPlot.SetRect(0, rGraph.bottom - (((INT)m_nLayoutSlots.GetSize() - pParameter->GetPosition())*rGraph.Height()) / (INT)m_nLayoutSlots.GetSize() - rGraph.top, rGraph.Width(), rGraph.bottom - (((INT)m_nLayoutSlots.GetSize() - pParameter->GetPosition() - 1)*rGraph.Height()) / (INT)m_nLayoutSlots.GetSize() - rGraph.top), rPlot.InflateRect(0, 0, 1, 1), ptSample.x = (INT)(rGraph.left + (rGraph.Width()*(pParameterSample->GetUpdateTime().GetTime() - m_tGraph[0].GetTime())) / (m_tGraph[2].GetTime() - m_tGraph[1].GetTime())), ptSample.y = (INT)(rGraph.bottom - ((m_nLayoutSlots.GetSize() - pParameter->GetPosition() - 1)*rGraph.Height()) / m_nLayoutSlots.GetSize() - ((fValue - fRange[0])*rGraph.Height()) / ((fRange[1] - fRange[0])*m_nLayoutSlots.GetSize())), ptSample.Offset(-rGraph.TopLeft()); (m_cLayout.GetMode() & GRDLAYOUT_MODE_OVERWRITE) && pParameterSample->GetUpdateTime() < m_tGraph[1]; )
			{
				ptSample.x = (INT)((rGraph.Width()*(pParameterSample->GetUpdateTime().GetTime() - (m_tGraph[0].GetTime() - (m_tGraph[2].GetTime() - m_tGraph[1].GetTime())))) / (m_tGraph[2].GetTime() - m_tGraph[1].GetTime()));
				break;
			}
			return ptSample;
		}
	}
	return CPoint(-1, -1);
}
CPoint CGRDView::CalcSamplePosition(INT nPlot, CONST CGRDParameterSample *pParameterSample, double *pMinValues, double *pMaxValues, double fValue, CRect &rPlot) CONST
{
	INT  nType;
	INT  nIndex;
	CRect  rGraph;
	CPoint  ptSample;
	double  fRange[2];
	CGRDLayoutParameter  *pParameter;

	if ((nType = m_cLayout.GetType()) == GRDLAYOUT_TYPE_STACKCHART)
	{
		for (rGraph = GetGraphPosition(), rPlot.SetRect(0, 0, rGraph.Width() + 1, rGraph.Height() + 1), ptSample.x = ((m_cLayout.GetMode() & GRDLAYOUT_MODE_OVERWRITE) && pParameterSample->GetUpdateTime() < m_tGraph[1]) ? (INT)(rGraph.left + (rGraph.Width()*(pParameterSample->GetUpdateTime().GetTime() - (m_tGraph[0].GetTime() - (m_tGraph[2].GetTime() - m_tGraph[1].GetTime())))) / (m_tGraph[2].GetTime() - m_tGraph[1].GetTime())) : (INT)(rGraph.left + (rGraph.Width()*(pParameterSample->GetUpdateTime().GetTime() - m_tGraph[0].GetTime())) / (m_tGraph[2].GetTime() - m_tGraph[1].GetTime())), ptSample.y = rGraph.bottom, ptSample.Offset(-rGraph.TopLeft()), nIndex = (INT)(m_cLayout.GetSize() - 1); nIndex >= nPlot; nIndex--)
		{
			if ((pParameter = (CGRDLayoutParameter *)m_cLayout.GetAt(nIndex)) != (CGRDLayoutParameter *)NULL  &&  pParameter->GetRange(fRange[0], fRange[1]))
			{
				ptSample.y -= (nIndex != nPlot) ? (INT)((rGraph.Height()*((pMinValues[nIndex] + pMaxValues[nIndex]) / 2.0 - fRange[0])) / (fRange[1] - fRange[0])) : 0;
				ptSample.y -= (nIndex == nPlot) ? (INT)((rGraph.Height()*(fValue - fRange[0])) / (fRange[1] - fRange[0])) : 0;
			}
		}
		return ptSample;
	}
	return CPoint(-1, -1);
}
CPoint CGRDView::CalcSamplePosition(INT nXPlot, INT nYPlot, double fXValue, double fYValue, CRect &rPlot) CONST
{
	INT  nType;
	CRect  rGraph;
	CPoint  ptSample;
	double  fRange[2][2];
	CGRDLayoutParameter  *pParameter[2];

	if ((nType = m_cLayout.GetType()) == GRDLAYOUT_TYPE_DIAGRAM)
	{
		if ((pParameter[0] = m_cLayout.GetAt(nXPlot)) && pParameter[0]->GetRange(fRange[0][0], fRange[0][1]))
		{
			if ((pParameter[1] = m_cLayout.GetAt(nYPlot)) && pParameter[1]->GetRange(fRange[1][0], fRange[1][1]))
			{
				ptSample.x = (INT)((rGraph = GetGraphPosition()).left + (rGraph.Width()*(fXValue - fRange[0][0])) / (fRange[0][1] - fRange[0][0]));
				ptSample.y = (INT)(rGraph.bottom - (rGraph.Height()*(fYValue - fRange[1][0])) / (fRange[1][1] - fRange[1][0]));
				rPlot.SetRect(0, 0, rGraph.Width() + 1, rGraph.Height() + 1);
				ptSample.Offset(-rGraph.TopLeft());
				return ptSample;
			}
		}
	}
	return CPoint(-1, -1);
}
CPoint CGRDView::CalcSamplePosition(CONST CTimeTag &tTime) CONST
{
	CPoint  ptSample;

	if (m_cLayout.GetType() != GRDLAYOUT_TYPE_DIAGRAM)
	{
		for (ptSample = CPoint((INT)((GetGraphSize().cx*(tTime.GetTime() - m_tGraph[0].GetTime())) / (m_tGraph[2].GetTime() - m_tGraph[1].GetTime())), 0); (m_cLayout.GetMode() & GRDLAYOUT_MODE_OVERWRITE) && tTime < m_tGraph[1]; )
		{
			ptSample.x = (INT)((GetGraphSize().cx*(tTime.GetTime() - (m_tGraph[0].GetTime() - (m_tGraph[2].GetTime() - m_tGraph[1].GetTime())))) / (m_tGraph[2].GetTime() - m_tGraph[1].GetTime()));
			break;
		}
		return ptSample;
	}
	return CPoint(-1, -1);
}

CSize CGRDView::CalcSampleSymbolSize(INT nWidth) CONST
{
	return CSize(2 * (nWidth + 1), 2 * (nWidth + 1));
}

INT CGRDView::CalcAxesSymbolWidth(LPCTSTR pszText) CONST
{
	INT  nWidth;
	CFont  cFont;
	CFont  *pOldFont;
	LOGFONT  lfFont;
	CClientDC  cDC(NULL);

	if (m_cLayoutFont[1].GetObject(sizeof(LOGFONT), &lfFont) > 0)
	{
		if ((pOldFont = (cFont.CreateFontIndirect(&lfFont)) ? cDC.SelectObject(&cFont) : (CFont *)NULL))
		{
			nWidth = cDC.GetTextExtent(pszText).cx;
			cDC.SelectObject(pOldFont);
			cFont.DeleteObject();
			return nWidth;
		}
		cFont.DeleteObject();
	}
	return 0;
}

INT CGRDView::CalcAxesSymbolHeight(LPCTSTR pszText) CONST
{
	INT  nHeight;
	CFont  cFont;
	CFont  *pOldFont;
	LOGFONT  lfFont;
	CClientDC  cDC(NULL);

	if (m_cLayoutFont[1].GetObject(sizeof(LOGFONT), &lfFont) > 0)
	{
		if ((pOldFont = (cFont.CreateFontIndirect(&lfFont)) ? cDC.SelectObject(&cFont) : (CFont *)NULL))
		{
			nHeight = cDC.GetTextExtent((!pszText) ? SPACE : pszText).cy;
			cDC.SelectObject(pOldFont);
			cFont.DeleteObject();
			return nHeight;
		}
		cFont.DeleteObject();
	}
	return 0;
}

VOID CGRDView::CreateLinePen(CDC *pDC, CONST SIZE &sizeGraph, INT nStyle, INT nWidth, COLORREF nColor, LOGBRUSH *pBrush)
{
	CDC  cDC;
	HPEN  hPen;
	HPEN  hOldPen;
	CBitmap  cBitmap;
	CBitmap  *pOldBitmap;
	LOGBRUSH  sLogBrush;

	if (nStyle != PS_SOLID)
	{
		for (sLogBrush.lbStyle = BS_SOLID, sLogBrush.lbColor = nColor, sLogBrush.lbHatch = (ULONG_PTR)NULL; cDC.CreateCompatibleDC(pDC); )
		{
			if ((hPen = ExtCreatePen(PS_GEOMETRIC | PS_ENDCAP_FLAT | nStyle, nWidth, &sLogBrush, 0, (CONST DWORD *) NULL)))
			{
				if ((hOldPen = (HPEN)SelectObject(cDC.GetSafeHdc(), hPen)))
				{
					if (cBitmap.CreateCompatibleBitmap(pDC, sizeGraph.cx, nWidth))
					{
						if ((pOldBitmap = cDC.SelectObject(&cBitmap)))
						{
							cDC.MoveTo(0, nWidth / 2);
							cDC.LineTo(sizeGraph.cx, nWidth / 2);
							pBrush->lbStyle = BS_PATTERN;
							pBrush->lbColor = sLogBrush.lbColor;
							pBrush->lbHatch = (ULONG_PTR)cBitmap.GetSafeHandle();
							SelectObject(cDC.GetSafeHdc(), hOldPen);
							cDC.SelectObject(pOldBitmap);
							DeleteObject(hPen);
							cBitmap.Detach();
							cDC.DeleteDC();
							return;
						}
						cBitmap.DeleteObject();
					}
					SelectObject(cDC.GetSafeHdc(), hOldPen);
				}
				DeleteObject(hPen);
			}
			cDC.DeleteDC();
			break;
		}
	}
	pBrush->lbStyle = BS_SOLID;
	pBrush->lbColor = nColor;
	pBrush->lbHatch = (ULONG_PTR)NULL;
}

VOID CGRDView::DestroyLinePen(LOGBRUSH *pBrush)
{
	if (pBrush->lbHatch)
	{
		DeleteObject((HGDIOBJ)pBrush->lbHatch);
		pBrush->lbHatch = (ULONG_PTR)NULL;
	}
}

CString CGRDView::LookupColumnName(UINT nColumn) CONST
{
	if (nColumn == GRD_TITLEITEM_ID) return STRING(IDS_GRD_TITLEITEM_ID);
	if (nColumn == GRD_TITLEITEM_DESCRIPTION) return STRING(IDS_GRD_TITLEITEM_DESCRIPTION);
	if (nColumn == GRD_TITLEITEM_VALUE) return STRING(IDS_GRD_TITLEITEM_VALUE);
	if (nColumn == GRD_TITLEITEM_UNIT) return STRING(IDS_GRD_TITLEITEM_UNIT);
	if (nColumn == GRD_TITLEITEM_RANGE) return STRING(IDS_GRD_TITLEITEM_RANGE);
	if (nColumn == GRD_TITLEITEM_LINE) return STRING(IDS_GRD_TITLEITEM_LINE);
	if (nColumn == GRD_TITLEITEM_CHANGETMUNIT) return STRING(IDS_GRD_TITLEITEM_CHANGETMUNIT);
	if (nColumn == GRD_TITLEITEM_CHANGETIME) return STRING(IDS_GRD_TITLEITEM_CHANGETIME);
	if (nColumn == GRD_TITLEITEM_UPDATETMUNIT) return STRING(IDS_GRD_TITLEITEM_UPDATETMUNIT);
	if (nColumn == GRD_TITLEITEM_UPDATETIME) return STRING(IDS_GRD_TITLEITEM_UPDATETIME);
	return EMPTYSTRING;
}
UINT CGRDView::LookupColumnName(LPCTSTR pszColumn) CONST
{
	if (!lstrcmp(pszColumn, STRING(IDS_GRD_TITLEITEM_ID))) return GRD_TITLEITEM_ID;
	if (!lstrcmp(pszColumn, STRING(IDS_GRD_TITLEITEM_DESCRIPTION))) return GRD_TITLEITEM_DESCRIPTION;
	if (!lstrcmp(pszColumn, STRING(IDS_GRD_TITLEITEM_VALUE))) return GRD_TITLEITEM_VALUE;
	if (!lstrcmp(pszColumn, STRING(IDS_GRD_TITLEITEM_UNIT))) return GRD_TITLEITEM_UNIT;
	if (!lstrcmp(pszColumn, STRING(IDS_GRD_TITLEITEM_RANGE))) return GRD_TITLEITEM_RANGE;
	if (!lstrcmp(pszColumn, STRING(IDS_GRD_TITLEITEM_LINE))) return GRD_TITLEITEM_LINE;
	if (!lstrcmp(pszColumn, STRING(IDS_GRD_TITLEITEM_CHANGETMUNIT))) return GRD_TITLEITEM_CHANGETMUNIT;
	if (!lstrcmp(pszColumn, STRING(IDS_GRD_TITLEITEM_CHANGETIME))) return GRD_TITLEITEM_CHANGETIME;
	if (!lstrcmp(pszColumn, STRING(IDS_GRD_TITLEITEM_UPDATETMUNIT))) return GRD_TITLEITEM_UPDATETMUNIT;
	if (!lstrcmp(pszColumn, STRING(IDS_GRD_TITLEITEM_UPDATETIME))) return GRD_TITLEITEM_UPDATETIME;
	return 0;
}

INT CGRDView::LookupColumnsName(CONST CUIntArray &nColumns, CStringArray &szColumns) CONST
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

COLORREF CGRDView::LookupColumnColor(UINT nColumn, BYTE nStatus) CONST
{
	if (nColumn == GRD_TITLEITEM_ID) return GetDatabase()->GetGRDIDColumnColor();
	if (nColumn == GRD_TITLEITEM_DESCRIPTION) return GetDatabase()->GetGRDDescriptionColumnColor();
	if (nColumn == GRD_TITLEITEM_VALUE && (nStatus & TMPARAMETER_STATUS_NOLIMIT)) return m_nLayoutColors.GetAt(GRD_OOLCOLOR_NOLIMIT);
	if (nColumn == GRD_TITLEITEM_VALUE && (nStatus & TMPARAMETER_STATUS_SOFTLIMIT)) return m_nLayoutColors.GetAt(GRD_OOLCOLOR_SOFTLIMIT);
	if (nColumn == GRD_TITLEITEM_VALUE && (nStatus & TMPARAMETER_STATUS_HARDLIMIT)) return m_nLayoutColors.GetAt(GRD_OOLCOLOR_HARDLIMIT);
	if (nColumn == GRD_TITLEITEM_VALUE && (nStatus & TMPARAMETER_STATUS_DELTALIMIT)) return m_nLayoutColors.GetAt(GRD_OOLCOLOR_DELTALIMIT);
	if (nColumn == GRD_TITLEITEM_VALUE && (nStatus & TMPARAMETER_STATUS_CONSISTENCYLIMIT)) return m_nLayoutColors.GetAt(GRD_OOLCOLOR_CONSISTENCYLIMIT);
	if (nColumn == GRD_TITLEITEM_VALUE) return GetDatabase()->GetGRDValueColumnColor();
	if (nColumn == GRD_TITLEITEM_UNIT) return GetDatabase()->GetGRDUnitColumnColor();
	if (nColumn == GRD_TITLEITEM_RANGE) return GetDatabase()->GetGRDRangeColumnColor();
	if (nColumn == GRD_TITLEITEM_CHANGETMUNIT) return GetDatabase()->GetGRDChangeTMUnitColumnColor();
	if (nColumn == GRD_TITLEITEM_CHANGETIME) return GetDatabase()->GetGRDChangeTimeColumnColor();
	if (nColumn == GRD_TITLEITEM_UPDATETMUNIT) return GetDatabase()->GetGRDUpdateTMUnitColumnColor();
	if (nColumn == GRD_TITLEITEM_UPDATETIME) return GetDatabase()->GetGRDUpdateTimeColumnColor();
	return GetSysColor(COLOR_WINDOW);
}

INT CGRDView::CalcColumnWidth(LPCTSTR pszColumn)
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
				nWidth = (nColumn == GRD_TITLEITEM_ID) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetGRDIDColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == GRD_TITLEITEM_DESCRIPTION) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetGRDDescriptionColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == GRD_TITLEITEM_VALUE) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetGRDValueColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == GRD_TITLEITEM_UNIT) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetGRDUnitColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == GRD_TITLEITEM_RANGE) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetGRDRangeColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == GRD_TITLEITEM_LINE) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetGRDLineColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == GRD_TITLEITEM_CHANGETMUNIT) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetGRDChangeTMUnitColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == GRD_TITLEITEM_UPDATETMUNIT) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetGRDUpdateTMUnitColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == GRD_TITLEITEM_CHANGETIME) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetGRDChangeTimeColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
				nWidth = (nColumn == GRD_TITLEITEM_UPDATETIME) ? max(LOWORD(GetTextIndents()) + GetDatabase()->GetGRDUpdateTimeColumnCharWidth()*nDxChar + HIWORD(GetTextIndents()), nWidth) : nWidth;
			}
			pDC->SelectObject(pOldFont);
		}
		for (szColumn = pszColumn; nColumn == GRD_TITLEITEM_VALUE; )
		{
			szColumn = CString(cStringTools.ConvertIntToString(0).GetAt(0), GetDatabase()->GetGRDValueColumnCharWidth());
			break;
		}
		for (; nColumn == GRD_TITLEITEM_CHANGETIME || nColumn == GRD_TITLEITEM_UPDATETIME; )
		{
			szColumn = CTimeTag().FormatGmt();
			break;
		}
		if (nColumn != GRD_TITLEITEM_VALUE)
		{
			if ((pOldFont = pDC->SelectObject(&m_wndContentCtrl.m_cFont)))
			{
				nWidth = max(LOWORD(GetTextIndents()) + pDC->GetTextExtent(szColumn).cx + HIWORD(GetTextIndents()), nWidth);
				pDC->SelectObject(pOldFont);
			}
		}
		if (nColumn == GRD_TITLEITEM_VALUE)
		{
			if ((pOldFont = pDC->SelectObject(&m_cLayoutFont[0])))
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
INT CGRDView::CalcColumnWidth(UINT nColumn, LPCTSTR pszText)
{
	CDC  *pDC;
	INT  nWidth;
	CFont  *pOldFont;

	if ((pDC = GetDC()))
	{
		if (nColumn == GRD_TITLEITEM_VALUE)
		{
			if ((pOldFont = pDC->SelectObject(&m_cLayoutFont[0])))
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

INT CGRDView::CalcColumnsWidth(CONST CUIntArray &nColumns, CUIntArray &nWidths)
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
CSize CGRDView::CalcColumnsWidth(CUIntArray &nWidths)
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

BOOL CGRDView::ConvertColumnToIndex(UINT nColumn, INT &nIndex) CONST
{
	INT  nCount;

	for (nIndex = 0, nCount = (INT)m_nLayoutColumns.GetSize(); nIndex < nCount; nIndex++)
	{
		if (m_nLayoutColumns.GetAt(nIndex) == nColumn) break;
		continue;
	}
	return((nIndex < nCount) ? TRUE : FALSE);
}

VOID CGRDView::ConvertAxesRangeValues(CONST CGRDLayoutParameter *pParameter, double fMinimum, double fMaximum, CString &szMinimum, CString &szMaximum) CONST
{
	CStringTools  cStringTools;

	if (((pParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NONE) || (pParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS)) && !(pParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT))
	{
		szMinimum = (floor(fMinimum) == fMinimum) ? cStringTools.ConvertLongIntToString((LONGLONG)fMinimum) : cStringTools.ConvertFloatToString(fMinimum);
		szMaximum = (floor(fMaximum) == fMaximum) ? cStringTools.ConvertLongIntToString((LONGLONG)fMaximum) : cStringTools.ConvertFloatToString(fMaximum);
		return;
	}
	szMinimum = cStringTools.ConvertFloatToString(fMinimum);
	szMaximum = cStringTools.ConvertFloatToString(fMaximum);
}

CString CGRDView::ConstructToolTipTitle() CONST
{
	CString  szTitle;

	szTitle.Format(STRING(IDS_GRD_TOOLTIP_GRAPHTITLE), (LPCTSTR)m_cLayout.GetTitle());
	return szTitle;
}
CString CGRDView::ConstructToolTipTitle(CONST CGRDLayoutParameter *pParameter, UINT nTip) CONST
{
	CString  szTitle;

	switch (nTip)
	{
	case GRD_TITLEITEM_ID:
	case GRD_TITLEITEM_DESCRIPTION:
	case GRD_TITLEITEM_VALUE:
	case GRD_TITLEITEM_CHANGETMUNIT:
	case GRD_TITLEITEM_CHANGETIME:
	case GRD_TITLEITEM_UPDATETMUNIT:
	case GRD_TITLEITEM_UPDATETIME:
	{ szTitle.Format(STRING(IDS_GRD_TOOLTIP_TITLE), (LPCTSTR)pParameter->GetName());
	break;
	}
	case GRD_TITLEITEM_UNIT:
	case GRD_TITLEITEM_RANGE:
	case GRD_TITLEITEM_LINE: break;
	}
	return szTitle;
}
CString CGRDView::ConstructToolTipTitle(CONST CGRDLayoutParameter *pParameter) CONST
{
	CString  szTitle;

	szTitle.Format(STRING(IDS_GRD_TOOLTIP_TITLE), (LPCTSTR)pParameter->GetName());
	return szTitle;
}

CString CGRDView::ConstructToolTipText() CONST
{
	CString  szText;
	CString  szType;
	CString  szUpdate[2];
	CString  szDuration[4];

	szType.Format(STRING(IDS_GRD_TOOLTIP_GRAPHTYPE), (m_cLayout.GetType() == GRDLAYOUT_TYPE_NORMAL) ? STRING(IDS_GRD_TOOLTIP_GRAPHTYPENORMAL) : ((m_cLayout.GetType() == GRDLAYOUT_TYPE_STRIPCHART) ? STRING(IDS_GRD_TOOLTIP_GRAPHTYPESTRIPCHART) : ((m_cLayout.GetType() == GRDLAYOUT_TYPE_STACKCHART) ? STRING(IDS_GRD_TOOLTIP_GRAPHTYPESTACKCHART) : ((m_cLayout.GetType() == GRDLAYOUT_TYPE_DIAGRAM) ? STRING(IDS_GRD_TOOLTIP_GRAPHTYPEDIAGRAM) : STRING(IDS_GRD_TOOLTIP_GRAPHTYPENORMAL)))), (m_cLayout.GetMode() & GRDLAYOUT_MODE_NORMAL) ? STRING(IDS_GRD_TOOLTIP_GRAPHMODENORMAL) : ((m_cLayout.GetMode() & GRDLAYOUT_MODE_OVERWRITE) ? STRING(IDS_GRD_TOOLTIP_GRAPHMODEOVERWRITE) : ((m_cLayout.GetMode() & GRDLAYOUT_MODE_SCROLL) ? STRING(IDS_GRD_TOOLTIP_GRAPHMODESCROLL) : STRING(IDS_GRD_TOOLTIP_GRAPHMODENORMAL))));
	szDuration[0].Format((m_cLayout.GetDuration().GetDays() != 1) ? STRING(IDS_GRD_TOOLTIP_GRAPHDURATIONDAYS) : STRING(IDS_GRD_TOOLTIP_GRAPHDURATIONDAY), m_cLayout.GetDuration().GetDays());
	szDuration[1].Format((m_cLayout.GetDuration().GetTotalHours() % HOURSPERDAY != 1) ? STRING(IDS_GRD_TOOLTIP_GRAPHDURATIONHOURS) : STRING(IDS_GRD_TOOLTIP_GRAPHDURATIONHOUR), m_cLayout.GetDuration().GetTotalHours() % HOURSPERDAY);
	szDuration[2].Format((m_cLayout.GetDuration().GetTotalMinutes() % MINUTESPERHOUR != 1) ? STRING(IDS_GRD_TOOLTIP_GRAPHDURATIONMINUTES) : STRING(IDS_GRD_TOOLTIP_GRAPHDURATIONMINUTE), m_cLayout.GetDuration().GetTotalMinutes() % MINUTESPERHOUR);
	szDuration[3].Format(STRING(IDS_GRD_TOOLTIP_GRAPHDURATION), (LPCTSTR)szDuration[0], (LPCTSTR)szDuration[1], (LPCTSTR)szDuration[2]);
	szUpdate[0].Format((m_cLayout.GetUpdateInterval().GetTotalMinutes() != 1) ? STRING(IDS_GRD_TOOLTIP_GRAPHUPDATEMINUTES) : STRING(IDS_GRD_TOOLTIP_GRAPHUPDATEMINUTE), m_cLayout.GetUpdateInterval().GetTotalMinutes());
	szUpdate[1].Format(STRING(IDS_GRD_TOOLTIP_GRAPHUPDATE), (m_cLayout.GetUpdateInterval().GetTotalSeconds() > 0) ? (LPCTSTR)szUpdate[0] : STRING(IDS_GRD_TOOLTIP_GRAPHUPDATEDEFAULT));
	szText = szType + EOL + szDuration[3] + EOL + szUpdate[1];
	return szText;
}
CString CGRDView::ConstructToolTipText(CONST CGRDLayoutParameter *pParameter, INT nOccurrence, UINT nTip) CONST
{
	INT  nPos;
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
	case GRD_TITLEITEM_ID:
	{ if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(pParameter->GetRef())))
	{
		for (szType.Format(STRING(IDS_GRD_TOOLTIP_TYPE), CDatabaseEngine::TranslateParameterTypeCode(pDatabaseTMParameter->GetAttributes(), FALSE)); szType.GetLength() < lstrlen(STRING(IDS_GRD_TOOLTIP_TYPE)); )
		{
			szType.Empty();
			break;
		}
		szWidth.Format(STRING(IDS_GRD_TOOLTIP_WIDTH), pDatabaseTMParameter->GetWidth());
		szPosition.Format(STRING(IDS_GRD_TOOLTIP_POSITION), pParameter->GetPosition());
		szText = (m_cLayout.GetType() != GRDLAYOUT_TYPE_STRIPCHART) ? ((!szType.IsEmpty()) ? (szType + EOL + szWidth) : szWidth) : ((!szType.IsEmpty()) ? (szType + EOL + szWidth + EOL + szPosition) : (szWidth + EOL + szPosition));
	}
	break;
	}
	case GRD_TITLEITEM_DESCRIPTION:
	{ if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(pParameter->GetRef())))
	{
		szText.Format(STRING(IDS_GRD_TOOLTIP_DESCRIPTION), ((szComment = ((nPos = pParameter->GetComment().Find(EOL)) >= 0) ? pParameter->GetComment().Left(nPos) : pParameter->GetComment()).GetLength() > 0 && !pDatabaseTMParameter->GetDetails().IsEmpty()) ? (LPCTSTR)(pDatabaseTMParameter->GetDetails() + EOL + szComment) : ((!pDatabaseTMParameter->GetDetails().IsEmpty()) ? (LPCTSTR)pDatabaseTMParameter->GetDetails() : (LPCTSTR)szComment));
		szText = (pDatabaseTMParameter->GetDetails().IsEmpty() && szComment.IsEmpty()) ? STRING(IDS_GRD_TOOLTIP_NODESCRIPTION) : szText;
	}
	break;
	}
	case GRD_TITLEITEM_VALUE:
	{ if ((pTMParameter = m_pLayoutValues.GetAt(m_pLayoutValues.Find(pParameter->GetName()))))
	{
		if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(pParameter->GetRef())))
		{
			if (pTMParameter->IsInitialized() && pTMParameter->GetRawValue((nOccurrence < 0) ? (pTMParameter->GetValueCount() - 1) : nOccurrence, nValue, nStatus, szCalTable))
			{
				if ((pTMParameter->GetAttributes() & TMPARAMETER_CODING_BITPATTERN) || (pTMParameter->GetAttributes() & TMPARAMETER_CODING_INVERSEBITPATTERN))
				{
					pTMParameter->GetValueAsText(GetDatabase(), (nOccurrence < 0) ? (pTMParameter->GetValueCount() - 1) : nOccurrence, (pTMParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_DECIMAL | TMPARAMETER_RADIX_HEXADECIMAL)) | TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_RADIX_BINARY, (pParameter->GetDigits() != 0) ? pParameter->GetDigits() : -1, szValue[0]);
					szValue[1].Format(STRING(IDS_GRD_TOOLTIP_CODEDVALUE), (LPCTSTR)szValue[0], STRING(IDS_GRD_TOOLTIP_BITVALUE));
				}
				if ((pTMParameter->GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) || (pTMParameter->GetAttributes() & TMPARAMETER_CODING_COMPLEMENTCOMPLEX))
				{
					pTMParameter->GetValueAsText(GetDatabase(), (nOccurrence < 0) ? (pTMParameter->GetValueCount() - 1) : nOccurrence, (pTMParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_HEXADECIMAL)) | TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_RADIX_DECIMAL, (pParameter->GetDigits() != 0) ? pParameter->GetDigits() : -1, szValue[0]);
					szValue[1].Format(STRING(IDS_GRD_TOOLTIP_CODEDVALUE), (LPCTSTR)szValue[0], (pTMParameter->GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) ? STRING(IDS_GRD_TOOLTIP_SIGNEDVALUE) : STRING(IDS_GRD_TOOLTIP_COMPLEMENTVALUE));
				}
				if (pTMParameter->GetAttributes() & TMPARAMETER_CODING_UNSIGNEDINTEGER)
				{
					pTMParameter->GetValueAsText(GetDatabase(), (nOccurrence < 0) ? (pTMParameter->GetValueCount() - 1) : nOccurrence, (pTMParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_HEXADECIMAL)) | TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_RADIX_DECIMAL, (pParameter->GetDigits() != 0) ? pParameter->GetDigits() : -1, szValue[0]);
					szValue[1].Format(STRING(IDS_GRD_TOOLTIP_CODEDVALUE), (LPCTSTR)szValue[0], STRING(IDS_GRD_TOOLTIP_UNSIGNEDVALUE));
				}
				if (pTMParameter->GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT)
				{
					pTMParameter->GetValueAsText(GetDatabase(), (nOccurrence < 0) ? (pTMParameter->GetValueCount() - 1) : nOccurrence, (pTMParameter->GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_HEXADECIMAL)) | TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_RADIX_DECIMAL, (pParameter->GetDigits() != 0) ? pParameter->GetDigits() : -1, szValue[0]);
					szValue[1].Format(STRING(IDS_GRD_TOOLTIP_CODEDVALUE), (LPCTSTR)szValue[0], STRING(IDS_GRD_TOOLTIP_FLOATINGVALUE));
				}
				if ((pTMParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_FLOATINGPOINT)) == 0)
				{
					pTMParameter->GetValueAsText(GetDatabase(), (nOccurrence < 0) ? (pTMParameter->GetValueCount() - 1) : nOccurrence, TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_RADIX_DECIMAL, (pParameter->GetDigits() != 0) ? pParameter->GetDigits() : -1, szValue[0]);
					szValue[1].Format(STRING(IDS_GRD_TOOLTIP_CODEDVALUE), (LPCTSTR)szValue[0], STRING(IDS_GRD_TOOLTIP_UNSIGNEDVALUE));
				}
				for (szValue[0].Format(STRING(IDS_GRD_TOOLTIP_RAWVALUE), nValue), pTMParameter->GetValueAsText(GetDatabase(), (nOccurrence < 0) ? (pTMParameter->GetValueCount() - 1) : nOccurrence, pTMParameter->GetAttributes(), (pParameter->GetDigits() != 0) ? pParameter->GetDigits() : -1, szValue[3], bOutSet, FALSE), szValue[2].Format((pTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) ? STRING(IDS_GRD_TOOLTIP_CALIBRATEDNUMERICALVALUE) : STRING(IDS_GRD_TOOLTIP_CALIBRATEDSTATUSVALUE), (LPCTSTR)(szValue[3] = (bOutSet) ? ((pTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) ? (szValue[3] + GetDatabase()->GetTMNumCalTablePointOutsideText()) : ((pTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS) ? (szValue[3] + GetDatabase()->GetTMTxtCalTablePointOutsideText()) : szValue[3])) : szValue[3]), (LPCTSTR)szCalTable, (bOutSet) ? ((pTMParameter->GetAttributes() & TMPARAMETER_INTERPRETATION_EXTRAPOLATE) ? STRING(IDS_GRD_TOOLTIP_EXTRPOLATEDVALUE) : STRING(IDS_GRD_TOOLTIP_OUTSETVALUE)) : STRING(IDS_GRD_TOOLTIP_INSETVALUE)), szValueChange.Format(STRING(IDS_GRD_TOOLTIP_VALUECHANGE), (LPCTSTR)pTMParameter->GetLastChangeTime().FormatGmt(), (LPCTSTR)pTMParameter->GetLastChangeTMUnit()), szValueUpdate.Format(STRING(IDS_GRD_TOOLTIP_VALUEUPDATE), (LPCTSTR)pTMParameter->GetLastUpdateTime().FormatGmt(), (LPCTSTR)pTMParameter->GetLastUpdateTMUnit()), szStatus.Format(STRING(IDS_GRD_TOOLTIP_STATUS), (nStatus & TMPARAMETER_STATUS_GOOD) ? STRING(IDS_GRD_TOOLTIP_GOODQUALITY) : STRING(IDS_GRD_TOOLTIP_BADQUALITY), (nStatus & TMPARAMETER_STATUS_SOFTLIMIT) ? STRING(IDS_GRD_TOOLTIP_SOFTOOL) : ((nStatus & TMPARAMETER_STATUS_HARDLIMIT) ? STRING(IDS_GRD_TOOLTIP_HARDOOL) : ((nStatus & TMPARAMETER_STATUS_DELTALIMIT) ? STRING(IDS_GRD_TOOLTIP_DELTAOOL) : ((nStatus & TMPARAMETER_STATUS_CONSISTENCYLIMIT) ? STRING(IDS_GRD_TOOLTIP_CONSISTENCYOOL) : STRING(IDS_GRD_TOOLTIP_NOOOL)))), (nStatus & TMPARAMETER_STATUS_VALID) ? STRING(IDS_GRD_TOOLTIP_VALID) : STRING(IDS_GRD_TOOLTIP_INVALID)); pTMParameter->GetAttributes() & TMPARAMETER_NATURE_CONSTANT; )
				{
					for (szValue[3].Format(STRING(IDS_GRD_TOOLTIP_RAWTEXT), (LPCTSTR)pDatabaseTMParameter->GetConstValueAsText()); (pTMParameter->GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_FLOATINGPOINT)) == 0; )
					{
						szValue[0] = szValue[3];
						break;
					}
					szValueChange.Empty();
					szValueUpdate.Empty();
					szStatus.Empty();
					break;
				}
				if (pParameter->GetOccurrence() >= 0)
				{
					szValue[3].Format(STRING(IDS_GRD_TOOLTIP_OCCURRENCE), pParameter->GetOccurrence());
					szValue[0] = szValue[3] + EOL + szValue[0];
				}
				szText = (((pTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) || (pTMParameter->GetAttributes() & TMPARAMETER_CALIBRATION_STATUS)) && lstrlen(szCalTable) > 0) ? ((!szValueChange.IsEmpty() && !szValueUpdate.IsEmpty() && !szStatus.IsEmpty()) ? (szValue[0] + EOL + szValue[1] + EOL + szValue[2] + EOL + szValueChange + EOL + szValueUpdate + EOL + szStatus) : (szValue[0] + EOL + szValue[1] + EOL + szValue[2])) : ((!szValueChange.IsEmpty() && !szValueUpdate.IsEmpty() && !szStatus.IsEmpty()) ? (szValue[0] + EOL + szValue[1] + EOL + szValueChange + EOL + szValueUpdate + EOL + szStatus) : (szValue[0] + EOL + szValue[1]));
				break;
			}
			szText = STRING(IDS_GRD_TOOLTIP_NOVALUE);
		}
	}
	break;
	}
	case GRD_TITLEITEM_UNIT:
	case GRD_TITLEITEM_RANGE:
	case GRD_TITLEITEM_LINE: break;
	case GRD_TITLEITEM_CHANGETMUNIT:
	case GRD_TITLEITEM_CHANGETIME:
	{ if ((pTMParameter = m_pLayoutValues.GetAt(m_pLayoutValues.Find(pParameter->GetName()))))
	{
		if ((pTMParameter->GetAttributes() & TMPARAMETER_NATURE_CONSTANT) != TMPARAMETER_NATURE_CONSTANT)
		{
			if ((nIndex = GetDatabase()->GetTMPackets()->Find(pTMParameter->GetLastChangeTMUnit())) >= 0)
			{
				szValueChange.Format(STRING(IDS_GRD_TOOLTIP_CHANGETMUNIT), (LPCTSTR)GetDatabase()->GetTMPackets()->GetAt(nIndex)->GetDescription(), (LPCTSTR)pTMParameter->GetLastChangeTMUnit());
				szValueChangeTime.Format(STRING(IDS_GRD_TOOLTIP_CHANGETIME), (LPCTSTR)pTMParameter->GetLastChangeTime().FormatGmt(), (LPCTSTR)pTMParameter->GetLastChangeTime().FormatGmt(CString(STRING(IDS_TIMETAG_DATEFORMAT)) + SPACE + STRING(IDS_TIMETAG_TIMEFORMAT)));
				szText = szValueChange + EOL + szValueChangeTime;
				break;
			}
			szText.Format(STRING(IDS_GRD_TOOLTIP_CHANGETIME), (LPCTSTR)pTMParameter->GetLastChangeTime().FormatGmt(), (LPCTSTR)pTMParameter->GetLastChangeTime().FormatGmt(CString(STRING(IDS_TIMEKEY_DATEFORMAT)) + SPACE + STRING(IDS_TIMEKEY_TIMEFORMAT)));
		}
	}
	break;
	}
	case GRD_TITLEITEM_UPDATETMUNIT:
	case GRD_TITLEITEM_UPDATETIME:
	{ if ((pTMParameter = m_pLayoutValues.GetAt(m_pLayoutValues.Find(pParameter->GetName()))))
	{
		if ((pTMParameter->GetAttributes() & TMPARAMETER_NATURE_CONSTANT) != TMPARAMETER_NATURE_CONSTANT)
		{
			if ((nIndex = GetDatabase()->GetTMPackets()->Find(pTMParameter->GetLastUpdateTMUnit())) >= 0)
			{
				szValueUpdate.Format(STRING(IDS_GRD_TOOLTIP_UPDATETMUNIT), (LPCTSTR)GetDatabase()->GetTMPackets()->GetAt(nIndex)->GetDescription(), (LPCTSTR)pTMParameter->GetLastUpdateTMUnit());
				szValueUpdateTime.Format(STRING(IDS_GRD_TOOLTIP_UPDATETIME), (LPCTSTR)pTMParameter->GetLastUpdateTime().FormatGmt(), (LPCTSTR)pTMParameter->GetLastUpdateTime().FormatGmt(CString(STRING(IDS_TIMETAG_DATEFORMAT)) + SPACE + STRING(IDS_TIMETAG_TIMEFORMAT)));
				szText = szValueUpdate + EOL + szValueUpdateTime;
				break;
			}
			szText.Format(STRING(IDS_GRD_TOOLTIP_UPDATETIME), (LPCTSTR)pTMParameter->GetLastUpdateTime().FormatGmt(), (LPCTSTR)pTMParameter->GetLastUpdateTime().FormatGmt(CString(STRING(IDS_TIMEKEY_DATEFORMAT)) + SPACE + STRING(IDS_TIMEKEY_TIMEFORMAT)));
		}
	}
	break;
	}
	}
	return szText;
}
CString CGRDView::ConstructToolTipText(CONST CGRDLayoutParameter *pParameter, CONST CGRDParameterSample &cSample) CONST
{
	INT  nSample;
	UINT  nStatus;
	BOOL  bOutSet;
	CString  szText;
	CString  szStatus;
	CString  szValue[4];
	CString  szCalTable;
	CString  szValueChange;
	CString  szValueUpdate;
	ULONGLONG  nValue;
	CDatabaseTMParameter  *pDatabaseTMParameter;

	if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt(pParameter->GetRef())))
	{
		if (cSample.IsInitialized() && cSample.GetRawValue(((nSample = pParameter->GetOccurrence()) < 0) ? (cSample.GetValueCount() - 1) : nSample, nValue, nStatus, szCalTable))
		{
			if ((cSample.GetAttributes() & TMPARAMETER_CODING_BITPATTERN) || (cSample.GetAttributes() & TMPARAMETER_CODING_INVERSEBITPATTERN))
			{
				cSample.GetValueAsText(GetDatabase(), (nSample < 0) ? (cSample.GetValueCount() - 1) : nSample, (cSample.GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_DECIMAL | TMPARAMETER_RADIX_HEXADECIMAL)) | TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_RADIX_BINARY, (pParameter->GetDigits() != 0) ? pParameter->GetDigits() : -1, szValue[0]);
				szValue[1].Format(STRING(IDS_GRD_TOOLTIP_CODEDVALUE), (LPCTSTR)szValue[0], STRING(IDS_GRD_TOOLTIP_BITVALUE));
			}
			if ((cSample.GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) || (cSample.GetAttributes() & TMPARAMETER_CODING_COMPLEMENTCOMPLEX))
			{
				cSample.GetValueAsText(GetDatabase(), (nSample < 0) ? (cSample.GetValueCount() - 1) : nSample, (cSample.GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_HEXADECIMAL)) | TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_RADIX_DECIMAL, (pParameter->GetDigits() != 0) ? pParameter->GetDigits() : -1, szValue[0]);
				szValue[1].Format(STRING(IDS_GRD_TOOLTIP_CODEDVALUE), (LPCTSTR)szValue[0], (cSample.GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) ? STRING(IDS_GRD_TOOLTIP_SIGNEDVALUE) : STRING(IDS_GRD_TOOLTIP_COMPLEMENTVALUE));
			}
			if (cSample.GetAttributes() & TMPARAMETER_CODING_UNSIGNEDINTEGER)
			{
				cSample.GetValueAsText(GetDatabase(), (nSample < 0) ? (cSample.GetValueCount() - 1) : nSample, (cSample.GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_HEXADECIMAL)) | TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_RADIX_DECIMAL, (pParameter->GetDigits() != 0) ? pParameter->GetDigits() : -1, szValue[0]);
				szValue[1].Format(STRING(IDS_GRD_TOOLTIP_CODEDVALUE), (LPCTSTR)szValue[0], STRING(IDS_GRD_TOOLTIP_UNSIGNEDVALUE));
			}
			if (cSample.GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT)
			{
				cSample.GetValueAsText(GetDatabase(), (nSample < 0) ? (cSample.GetValueCount() - 1) : nSample, (cSample.GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_HEXADECIMAL)) | TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_RADIX_DECIMAL, (pParameter->GetDigits() != 0) ? pParameter->GetDigits() : -1, szValue[0]);
				szValue[1].Format(STRING(IDS_GRD_TOOLTIP_CODEDVALUE), (LPCTSTR)szValue[0], STRING(IDS_GRD_TOOLTIP_FLOATINGVALUE));
			}
			if ((cSample.GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_FLOATINGPOINT)) == 0)
			{
				cSample.GetValueAsText(GetDatabase(), (nSample < 0) ? (cSample.GetValueCount() - 1) : nSample, TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_RADIX_DECIMAL, (pParameter->GetDigits() != 0) ? pParameter->GetDigits() : -1, szValue[0]);
				szValue[1].Format(STRING(IDS_GRD_TOOLTIP_CODEDVALUE), (LPCTSTR)szValue[0], STRING(IDS_GRD_TOOLTIP_UNSIGNEDVALUE));
			}
			for (szValue[0].Format(STRING(IDS_GRD_TOOLTIP_RAWVALUE), nValue), cSample.GetValueAsText(GetDatabase(), (nSample < 0) ? (cSample.GetValueCount() - 1) : nSample, cSample.GetAttributes(), (pParameter->GetDigits() != 0) ? pParameter->GetDigits() : -1, szValue[3], bOutSet, FALSE), szValue[2].Format((cSample.GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) ? STRING(IDS_GRD_TOOLTIP_CALIBRATEDNUMERICALVALUE) : STRING(IDS_GRD_TOOLTIP_CALIBRATEDSTATUSVALUE), (LPCTSTR)(szValue[3] = (bOutSet) ? ((cSample.GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) ? (szValue[3] + GetDatabase()->GetTMNumCalTablePointOutsideText()) : ((cSample.GetAttributes() & TMPARAMETER_CALIBRATION_STATUS) ? (szValue[3] + GetDatabase()->GetTMTxtCalTablePointOutsideText()) : szValue[3])) : szValue[3]), (LPCTSTR)szCalTable, (bOutSet) ? ((cSample.GetAttributes() & TMPARAMETER_INTERPRETATION_EXTRAPOLATE) ? STRING(IDS_GRD_TOOLTIP_EXTRPOLATEDVALUE) : STRING(IDS_GRD_TOOLTIP_OUTSETVALUE)) : STRING(IDS_GRD_TOOLTIP_INSETVALUE)), szValueChange.Format(STRING(IDS_GRD_TOOLTIP_VALUECHANGE), (LPCTSTR)cSample.GetLastChangeTime().FormatGmt(), (LPCTSTR)cSample.GetLastChangeTMUnit()), szValueUpdate.Format(STRING(IDS_GRD_TOOLTIP_VALUEUPDATE), (LPCTSTR)cSample.GetLastUpdateTime().FormatGmt(), (LPCTSTR)cSample.GetLastUpdateTMUnit()), szStatus.Format(STRING(IDS_GRD_TOOLTIP_STATUS), (nStatus & TMPARAMETER_STATUS_GOOD) ? STRING(IDS_GRD_TOOLTIP_GOODQUALITY) : STRING(IDS_GRD_TOOLTIP_BADQUALITY), (nStatus & TMPARAMETER_STATUS_SOFTLIMIT) ? STRING(IDS_GRD_TOOLTIP_SOFTOOL) : ((nStatus & TMPARAMETER_STATUS_HARDLIMIT) ? STRING(IDS_GRD_TOOLTIP_HARDOOL) : ((nStatus & TMPARAMETER_STATUS_DELTALIMIT) ? STRING(IDS_GRD_TOOLTIP_DELTAOOL) : ((nStatus & TMPARAMETER_STATUS_CONSISTENCYLIMIT) ? STRING(IDS_GRD_TOOLTIP_CONSISTENCYOOL) : STRING(IDS_GRD_TOOLTIP_NOOOL)))), (nStatus & TMPARAMETER_STATUS_VALID) ? STRING(IDS_GRD_TOOLTIP_VALID) : STRING(IDS_GRD_TOOLTIP_INVALID)); cSample.GetAttributes() & TMPARAMETER_NATURE_CONSTANT; )
			{
				for (szValue[3].Format(STRING(IDS_GRD_TOOLTIP_RAWTEXT), (LPCTSTR)pDatabaseTMParameter->GetConstValueAsText()); (cSample.GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_FLOATINGPOINT)) == 0; )
				{
					szValue[0] = szValue[3];
					break;
				}
				szValueChange.Empty();
				szValueUpdate.Empty();
				szStatus.Empty();
				break;
			}
			if (pParameter->GetOccurrence() >= 0)
			{
				szValue[3].Format(STRING(IDS_GRD_TOOLTIP_OCCURRENCE), pParameter->GetOccurrence());
				szValue[0] = szValue[3] + EOL + szValue[0];
			}
			szText = (((cSample.GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) || (cSample.GetAttributes() & TMPARAMETER_CALIBRATION_STATUS)) && lstrlen(szCalTable) > 0) ? ((!szValueChange.IsEmpty() && !szValueUpdate.IsEmpty() && !szStatus.IsEmpty()) ? (szValue[0] + EOL + szValue[1] + EOL + szValue[2] + EOL + szValueChange + EOL + szValueUpdate + EOL + szStatus) : (szValue[0] + EOL + szValue[1] + EOL + szValue[2])) : ((!szValueChange.IsEmpty() && !szValueUpdate.IsEmpty() && !szStatus.IsEmpty()) ? (szValue[0] + EOL + szValue[1] + EOL + szValueChange + EOL + szValueUpdate + EOL + szStatus) : (szValue[0] + EOL + szValue[1]));
			return szText;
		}
		szText = STRING(IDS_GRD_TOOLTIP_NOVALUE);
	}
	return szText;
}

BOOL CGRDView::LoadToolTipCursor()
{
	return(((m_hToolTipCursor = (HCURSOR)LoadImage(GetModuleHandle((LPCTSTR)NULL), MAKEINTRESOURCE(IDC_TOOLTIPCURSOR), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR))) ? TRUE : FALSE);
}

HCURSOR CGRDView::GetToolTipCursor() CONST
{
	return((!m_hToolTipCursor) ? (HCURSOR)(DWORD_PTR)GetClassLongPtr(GetSafeHwnd(), GCLP_HCURSOR) : m_hToolTipCursor);
}

BOOL CGRDView::FreeToolTipCursor()
{
	if (m_hToolTipCursor)
	{
		DestroyCursor(m_hToolTipCursor);
		m_hToolTipCursor = (HCURSOR)NULL;
		return TRUE;
	}
	return FALSE;
}

VOID CGRDView::RecalcLayout()
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

void CGRDView::PostNcDestroy()
{
	INT  nID;
	INT  nIDs;

	for (nID = 0, nIDs = (INT)m_nGraphTimerIDs.GetSize(); nID < nIDs; nID++)
	{
		KillTimer(m_nGraphTimerIDs.GetAt(nID));
		m_nGraphTimerIDs.RemoveAt(nID);
		nIDs--;
		nID--;
	}
	m_cLayout.RemoveAll();
	m_szLayoutTables.RemoveAll();
	m_nLayoutColumns.RemoveAll();
	m_pLayoutMarkers.RemoveAll();
	m_nLayoutColors.RemoveAll();
	m_nLayoutStatus.RemoveAll();
	m_bLayoutValues.RemoveAll();
	m_pLayoutValues.RemoveAll();
	m_nLayoutSlots.RemoveAll();
	m_cGraphPlots.RemoveAll();
	m_cGraphBits.RemoveAll();
	CTextView::PostNcDestroy();
}

BOOL CGRDView::Lock()
{
	return((IsWindow(GetSafeHwnd())) ? (GetParent()->Lock() && CTextView::Lock()) : CTextView::Lock());
}

BOOL CGRDView::Unlock()
{
	return((IsWindow(GetSafeHwnd())) ? (CTextView::Unlock() && GetParent()->Unlock()) : CTextView::Unlock());
}

BEGIN_MESSAGE_MAP(CGRDView, CTextView)
	//{{AFX_MSG_MAP(CGRDView)
	ON_WM_CREATE()
	ON_WM_SETCURSOR()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDView message handlers

int CGRDView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	LOGFONT  lfFont[2];
	CTextViewLock  cLock(this);

	return((CTextView::OnCreate(lpCreateStruct) != -1 && (GetValuesFont(&lfFont[0]) || SetValuesFont()) && (GetAxesFont(&lfFont[1]) || SetAxesFont()) && GetTitleFont(&m_lfLayoutDefault[0]) && GetItemsFont(&m_lfLayoutDefault[1]) && GetValuesFont(&m_lfLayoutDefault[2]) && GetAxesFont(&m_lfLayoutDefault[3]) && LoadToolTipCursor()) ? 0 : -1);
}

BOOL CGRDView::OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message)
{
	INT  nRow;
	INT  nColumn;
	LONG  lDataFlag;
	POINT  ptCursor;
	CRect  rContent;
	CGRDLayoutParameter  *pParameter;
	CTextViewLock  cLock(this);

	for (GetCursorPos(&ptCursor), m_wndContentCtrl.ScreenToClient(&ptCursor), m_wndContentCtrl.GetClientRect(rContent); rContent.PtInRect(ptCursor); )
	{
		if ((lDataFlag = GetParent()->IsRetrievingData()) && HIWORD(lDataFlag))
		{
			SetCursor(LoadCursor((HINSTANCE)NULL, IDC_WAIT));
			return TRUE;
		}
		if ((pParameter = (IsToolTipModeEnabled() && FindTextFromPoint(ptCursor, nRow, nColumn, FALSE) && nColumn < m_nLayoutColumns.GetSize()) ? m_cLayout.GetAt(nRow) : (CGRDLayoutParameter *)NULL))
		{
			switch (m_nLayoutColumns.GetAt(nColumn))
			{
			case GRD_TITLEITEM_ID:
			case GRD_TITLEITEM_DESCRIPTION:
			case GRD_TITLEITEM_VALUE:
			case GRD_TITLEITEM_CHANGETMUNIT:
			case GRD_TITLEITEM_CHANGETIME:
			case GRD_TITLEITEM_UPDATETMUNIT:
			case GRD_TITLEITEM_UPDATETIME:
			{ SetCursor(GetToolTipCursor());
			return TRUE;
			break;
			}
			case GRD_TITLEITEM_UNIT:
			case GRD_TITLEITEM_RANGE:
			case GRD_TITLEITEM_LINE: break;
			}
		}
		if (IsToolTipModeEnabled())
		{
			if (m_cLayout.GetType() == GRDLAYOUT_TYPE_NORMAL || m_cLayout.GetType() == GRDLAYOUT_TYPE_STRIPCHART || m_cLayout.GetType() == GRDLAYOUT_TYPE_STACKCHART)
			{
				if (FindSamplePosition(CPoint(ptCursor.x + m_wndContentCtrl.m_nScrollPos[0], ptCursor.y + m_wndContentCtrl.m_nScrollPos[1])))
				{
					SetCursor(GetToolTipCursor());
					return TRUE;
				}
			}
		}
		break;
	}
	return CTextView::OnSetCursor(pWnd, nHitTest, message);
}

BOOL CGRDView::OnContentMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	INT  nRow;
	INT  nPlot;
	INT  nPlots;
	INT  nIndex;
	INT  nColumn;
	INT  nSample;
	INT  nSamples;
	LONG  lDataFlag;
	CRect  rGraph;
	CRect  rSlider;
	CFont  cFont[2];
	CSize  sizePlot[2];
	CPoint  ptSlider;
	CPoint  ptMarker;
	CPoint  ptToolTip;
	double  fInterval[2];
	CString  szParameter;
	CString  szToolTip[2];
	LOGFONT  lfFont[2];
	CTimeTag  tTime[2];
	CTimeTag  tRange[2];
	CTimeSpan  tDuration[2];
	CGRDMarker  *pMarker;
	CGRDLayoutParameter  *pParameter;
	CGRDParameterSample  *pParameterSample;
	CGRDParameterSamples  *pParameterSamples;
	CTextViewLock  cLock(this);

	if (message == WM_SETFOCUS)
	{
		SetCurText((GetCurText() >= 0) ? GetCurText() : 0);
		m_wndContentCtrl.m_bFocused = TRUE;
		return TRUE;
	}
	if (message == WM_KILLFOCUS)
	{
		for (m_wndContentCtrl.m_bFocused = FALSE; m_cLayout.GetType() != GRDLAYOUT_TYPE_DIAGRAM; )
		{
			if (HIBYTE(GetKeyState(VK_LBUTTON))) m_wndRulerTip.Destroy();
			break;
		}
		return TRUE;
	}
	if (message == WM_KEYDOWN)
	{
		if (wParam == VK_SHIFT)
		{
			if (m_cLayout.GetType() != GRDLAYOUT_TYPE_DIAGRAM)
			{
				m_wndRulerTip.Update();
				return FALSE;
			}
		}
		if (wParam == VK_TAB) GetParent()->SetFocus();
		return FALSE;
	}
	if (message == WM_KEYUP)
	{
		if (wParam == VK_SHIFT)
		{
			if (m_cLayout.GetType() != GRDLAYOUT_TYPE_DIAGRAM)
			{
				m_wndRulerTip.Update();
				return FALSE;
			}
		}
		return FALSE;
	}
	if (message == WM_MOUSEMOVE)
	{
		if (IsWindow(m_wndRulerTip.GetSafeHwnd()))
		{
			for (rGraph = GetGraphPosition(), m_wndRulerTip.GetWindowRect(rSlider), m_wndContentCtrl.ScreenToClient(rSlider), rSlider.OffsetRect(m_wndContentCtrl.m_nScrollPos[0], m_wndContentCtrl.m_nScrollPos[1]), ptSlider.x = GET_X_LPARAM(lParam), ptSlider.y = GET_Y_LPARAM(lParam), m_wndContentCtrl.ClientToScreen(&ptSlider); wParam & MK_LBUTTON; )
			{
				m_wndRulerTip.Update(m_tGraph[1].GetTime() + ((rSlider.left - rGraph.left)*(m_tGraph[2].GetTime() - m_tGraph[1].GetTime())) / rGraph.Width(), m_tGraph[2], ptSlider);
				break;
			}
		}
		return FALSE;
	}
	if (message == WM_LBUTTONDOWN)
	{
		if (m_cLayout.GetType() != GRDLAYOUT_TYPE_DIAGRAM)
		{
			for (rGraph = GetGraphPosition(); (wParam & MK_SHIFT) && rGraph.PtInRect(CPoint(GET_X_LPARAM(lParam) + m_wndContentCtrl.m_nScrollPos[0], GET_Y_LPARAM(lParam) + m_wndContentCtrl.m_nScrollPos[1])); )
			{
				m_wndRulerTip.Create(&m_wndContentCtrl, CRect(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), rGraph.right, GET_Y_LPARAM(lParam)), m_tGraph[1].GetTime() + ((GET_X_LPARAM(lParam) + m_wndContentCtrl.m_nScrollPos[0] - rGraph.left)*(m_tGraph[2].GetTime() - m_tGraph[1].GetTime())) / rGraph.Width(), m_tGraph[2]);
				m_wndContentCtrl.SetFocus();
				break;
			}
		}
		for (rGraph = GetGraphPosition(); m_cLayout.GetType() == GRDLAYOUT_TYPE_DIAGRAM; )
		{
			sizePlot[0] = m_cLayout.GetPlotSize();
			sizePlot[1].cx = m_sizeLayoutDefault.cx;
			sizePlot[1].cy = m_sizeLayoutDefault.cy;
			sizePlot[0].cx = (!sizePlot[0].cx) ? GRDLAYOUT_GRAPH_WIDTH : sizePlot[0].cx;
			sizePlot[0].cy = (!sizePlot[0].cy) ? GRDLAYOUT_GRAPH_HEIGHT : sizePlot[0].cy;
			sizePlot[1].cx = (!sizePlot[1].cx) ? GRDLAYOUT_GRAPH_WIDTH : sizePlot[1].cx;
			sizePlot[1].cy = (!sizePlot[1].cy) ? GRDLAYOUT_GRAPH_HEIGHT : sizePlot[1].cy;
			ptMarker.x = ((GET_X_LPARAM(lParam) + m_wndContentCtrl.m_nScrollPos[0] - rGraph.left)*sizePlot[1].cx) / sizePlot[0].cx;
			ptMarker.y = ((GET_Y_LPARAM(lParam) + m_wndContentCtrl.m_nScrollPos[1] - rGraph.top)*sizePlot[1].cy) / sizePlot[0].cy;
			if ((pMarker = m_pLayoutMarkers.GetAt((nIndex = m_pLayoutMarkers.Find(CPoint(ptMarker.x, ptMarker.y), (GetAxesStubs().cx + GetAxesStubs().cy) / 4)))))
			{
				m_pLayoutMarkers.RemoveAt(nIndex);
				delete pMarker;
				DrawImage();
				break;
			}
			if ((wParam & MK_SHIFT) && rGraph.PtInRect(CPoint(GET_X_LPARAM(lParam) + m_wndContentCtrl.m_nScrollPos[0], GET_Y_LPARAM(lParam) + m_wndContentCtrl.m_nScrollPos[1])))
			{
				if ((pMarker = new CGRDMarker(CPoint(ptMarker.x, ptMarker.y))))
				{
					if (m_pLayoutMarkers.Add(pMarker) >= 0)
					{
						DrawImage();
						break;
					}
					delete pMarker;
				}
			}
			DrawImage();
			break;
		}
		return FALSE;
	}
	if (message == WM_LBUTTONUP)
	{
		if (m_cLayout.GetType() != GRDLAYOUT_TYPE_DIAGRAM)
		{
			if ((wParam & MK_SHIFT) && (wParam & MK_CONTROL) && m_wndRulerTip.GetRange(tTime[0], tTime[1]) && (tTime[1].GetTimeInSeconds() - tTime[0].GetTimeInSeconds()) / SECONDSPERMINUTE > 0)
			{
				for (nPlot = 0, nPlots = (INT)m_cGraphPlots.GetSize(); nPlot < nPlots; nPlot = nPlot + 1)
				{
					if ((pParameterSamples = m_cGraphPlots.GetAt(nPlot)) != (CGRDParameterSamples *)NULL)
					{
						for (nSample = 0, nSamples = (INT)pParameterSamples->GetSize(); nSample < nSamples; nSample++)
						{
							if ((pParameterSample = pParameterSamples->GetAt(nSample)) != (CGRDParameterSample *)NULL)
							{
								if (pParameterSample->GetUpdateTime() < tTime[0] || pParameterSample->GetUpdateTime() > tTime[1])
								{
									pParameterSamples->RemoveAt(nSample);
									delete pParameterSample;
									nSamples--;
									nSample--;
								}
							}
						}
					}
				}
				tDuration[0] = m_cLayout.GetDuration().GetTotalSeconds();
				tDuration[1] = tTime[1].GetTimeInSeconds() - tTime[0].GetTimeInSeconds();
				fInterval[0] = (double)tDuration[1].GetTotalSeconds() / (double)tDuration[0].GetTotalSeconds();
				fInterval[1] = (double)m_cLayout.GetInterval().GetTotalSeconds() / (double)tDuration[0].GetTotalSeconds();
				for (m_cLayout.SetDuration(tDuration[1].GetTotalSeconds()), m_cLayout.SetInterval((tDuration[1].GetTotalSeconds()*fInterval[1] >= SECONDSPERMINUTE) ? (TIMEKEY)(tDuration[1].GetTotalSeconds()*fInterval[1]) : 0), m_cLayout.SetUpdateInterval((m_cLayout.GetUpdateInterval().GetTotalSeconds()*fInterval[0] >= SECONDSPERMINUTE) ? (TIMEKEY)(SECONDSPERMINUTE*(INT)((m_cLayout.GetUpdateInterval().GetTotalSeconds()*fInterval[0]) / SECONDSPERMINUTE)) : 0), m_tGraph[0] = m_tGraph[1] = tTime[0], m_tGraph[2] = tTime[1]; m_cGraphPlots.GetUpdateRange(tRange[0], tRange[1]) && tRange[1] >= tTime[1]; )
				{
					SetHoldFlag(TRUE);
					break;
				}
				UpdateGraph();
				DrawImage();
			}
			m_wndRulerTip.Destroy();
		}
		return FALSE;
	}
	if (message == WM_LBUTTONDBLCLK)
	{
		if (!(lDataFlag = GetParent()->IsRetrievingData()) || !HIWORD(lDataFlag))
		{
			if ((pParameter = (FindTextFromPoint(CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)), nRow, nColumn, FALSE)) ? m_cLayout.GetAt(nRow) : (CGRDLayoutParameter *)NULL))
			{
				for (szParameter = pParameter->GetName(), cLock.Release(); !szParameter.IsEmpty(); )
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
			if ((pParameter = (IsToolTipModeEnabled() && FindTextFromPoint((ptToolTip = CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))), nRow, nColumn, FALSE)) ? m_cLayout.GetAt(nRow) : (CGRDLayoutParameter *)NULL))
			{
				switch (m_nLayoutColumns.GetAt(nColumn))
				{
				case GRD_TITLEITEM_ID:
				case GRD_TITLEITEM_DESCRIPTION:
				case GRD_TITLEITEM_VALUE:
				case GRD_TITLEITEM_CHANGETMUNIT:
				case GRD_TITLEITEM_CHANGETIME:
				case GRD_TITLEITEM_UPDATETMUNIT:
				case GRD_TITLEITEM_UPDATETIME:
				{ for (szToolTip[0] = ConstructToolTipTitle(pParameter, m_nLayoutColumns.GetAt(nColumn)), szToolTip[1] = ConstructToolTipText(pParameter, pParameter->GetOccurrence(), m_nLayoutColumns.GetAt(nColumn)), GetTextFont(&lfFont[0]), GetTextFont(&lfFont[1]), lfFont[0].lfWeight = FW_BOLD, lfFont[1].lfWeight = FW_NORMAL; cFont[0].CreateFontIndirect(&lfFont[0]) && cFont[1].CreateFontIndirect(&lfFont[1]); )
				{
					m_wndToolTip.SetTitleFont(&cFont[0]);
					m_wndToolTip.SetTextFont(&cFont[1]);
					break;
				}
				m_wndToolTip.Create(&m_wndContentCtrl, ptToolTip, szToolTip[0], szToolTip[1]);
				break;
				}
				case GRD_TITLEITEM_UNIT:
				case GRD_TITLEITEM_RANGE:
				case GRD_TITLEITEM_LINE: break;
				}
			}
			for (; (pParameterSample = (IsToolTipModeEnabled() && szToolTip[0].IsEmpty() && szToolTip[1].IsEmpty()) ? new CGRDParameterSample : (CGRDParameterSample *)NULL); )
			{
				if ((pParameter = (m_cLayout.GetType() == GRDLAYOUT_TYPE_NORMAL || m_cLayout.GetType() == GRDLAYOUT_TYPE_STRIPCHART || m_cLayout.GetType() == GRDLAYOUT_TYPE_STACKCHART) ? FindSamplePosition(CPoint(GET_X_LPARAM(lParam) + m_wndContentCtrl.m_nScrollPos[0], GET_Y_LPARAM(lParam) + m_wndContentCtrl.m_nScrollPos[1]), *pParameterSample) : (CGRDLayoutParameter *)NULL))
				{
					for (szToolTip[0] = ConstructToolTipTitle(pParameter), szToolTip[1] = ConstructToolTipText(pParameter, *pParameterSample), m_wndContentCtrl.m_cFont.GetLogFont(&lfFont[0]), m_wndContentCtrl.m_cFont.GetLogFont(&lfFont[1]), lfFont[0].lfWeight = FW_BOLD, lfFont[1].lfWeight = FW_NORMAL; cFont[0].CreateFontIndirect(&lfFont[0]) && cFont[1].CreateFontIndirect(&lfFont[1]); )
					{
						m_wndToolTip.SetTitleFont(&cFont[0]);
						m_wndToolTip.SetTextFont(&cFont[1]);
						break;
					}
					m_wndToolTip.Create(&m_wndContentCtrl, CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)), szToolTip[0], szToolTip[1]);
					delete pParameterSample;
					break;
				}
				if (GetGraphPosition().PtInRect(CPoint(GET_X_LPARAM(lParam) + m_wndContentCtrl.m_nScrollPos[0], GET_Y_LPARAM(lParam) + m_wndContentCtrl.m_nScrollPos[1])))
				{
					for (szToolTip[0] = ConstructToolTipTitle(), szToolTip[1] = ConstructToolTipText(), m_wndContentCtrl.m_cFont.GetLogFont(&lfFont[0]), m_wndContentCtrl.m_cFont.GetLogFont(&lfFont[1]), lfFont[0].lfWeight = FW_BOLD, lfFont[1].lfWeight = FW_NORMAL; cFont[0].CreateFontIndirect(&lfFont[0]) && cFont[1].CreateFontIndirect(&lfFont[1]); )
					{
						m_wndToolTip.SetTitleFont(&cFont[0]);
						m_wndToolTip.SetTextFont(&cFont[1]);
						break;
					}
					m_wndToolTip.Create(&m_wndContentCtrl, CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)), szToolTip[0], szToolTip[1]);
				}
				delete pParameterSample;
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

void CGRDView::OnTimer(UINT_PTR nEventID)
{
	INT  nID;
	INT  nIDs;
	INT  nMargin[2];
	INT  nParameter[2];
	INT  nParameters[2];
	BOOL  bGraphUpdate;
	double  fPrecision;
	double  fMinimum[2];
	double  fMaximum[2];
	CGRDLayoutParameter  *pParameter[2];
	CGRDParameterSamples  *pParameterSamples;
	CTextViewLock  cLock(this);

	if (m_cLayout.GetSize() > (INT)nEventID)
	{
		for (nParameter[0] = 0, nParameters[0] = (INT)nEventID; nParameter[0] < nParameters[0]; nParameter[0]++)
		{
			if ((pParameter[0] = ((pParameter[1] = m_cLayout.GetAt((INT)nEventID))) ? m_cLayout.GetAt(nParameter[0]) : (CGRDLayoutParameter *)NULL) && pParameter[1]->GetAutoScaleDelay().GetTotalSeconds() / SECONDSPERMINUTE > 0 && pParameter[0]->GetAutoScaleDelay() == pParameter[1]->GetAutoScaleDelay()) break;
			continue;
		}
		for (nParameter[1] = (nParameter[0] < nParameters[0]) ? (INT)m_cLayout.GetSize() : (INT)nEventID, nParameters[1] = (INT)m_cLayout.GetSize(), bGraphUpdate = FALSE; nParameter[1] < nParameters[1]; nParameter[1]++)
		{
			if ((pParameter[0] = ((pParameter[1] = m_cLayout.GetAt((INT)nEventID))) ? m_cLayout.GetAt(nParameter[1]) : (CGRDLayoutParameter *)NULL) && pParameter[1]->GetAutoScaleDelay().GetTotalSeconds() / SECONDSPERMINUTE > 0 && pParameter[0]->GetAutoScaleDelay() == pParameter[1]->GetAutoScaleDelay())
			{
				if ((pParameterSamples = (CGRDParameterSamples *)m_cGraphPlots.GetAt(nParameter[1])) != (CGRDParameterSamples *)NULL)
				{
					if (pParameter[0]->GetRange(fMinimum[0], fMaximum[0]) && pParameterSamples->GetRange(fMinimum[1], fMaximum[1]) && fMinimum[1] != fMaximum[1])
					{
						if (fMinimum[0] > fMinimum[1] || fMaximum[0] < fMaximum[1])
						{
							pParameter[0]->GetMargin(nMargin[0], nMargin[1]);
							fMinimum[0] = fMinimum[1] - ((double)max(nMargin[0], 0)*(fMaximum[1] - fMinimum[1])) / 100.0;
							fMaximum[0] = fMaximum[1] + ((double)max(nMargin[1], 0)*(fMaximum[1] - fMinimum[1])) / 100.0;
							fPrecision = (m_cLayout.GetType() == GRDLAYOUT_TYPE_DIAGRAM  &&  nParameter[1] % 2 == 0) ? ((!m_cLayout.GetPlotSize().cx) ? GRDLAYOUT_GRAPH_WIDTH : m_cLayout.GetPlotSize().cx) : ((!m_cLayout.GetPlotSize().cy) ? GRDLAYOUT_GRAPH_HEIGHT : m_cLayout.GetPlotSize().cy);
							fPrecision = pow(10.0, floor(log10(fPrecision)) - floor(log10(fMaximum[1] - fMinimum[1])));
							fMinimum[0] = floor(fMinimum[0] * fPrecision - 1.0) / fPrecision;
							fMaximum[0] = floor(fMaximum[0] * fPrecision + 1.0) / fPrecision;
							pParameter[0]->SetRange(fMinimum[0], fMaximum[0]);
							bGraphUpdate = TRUE;
						}
					}
				}
			}
		}
		if (bGraphUpdate)
		{
			UpdateGraphScaling();
			UpdateGraph();
			RecalcLayout();
		}
	}
	else
	{
		for (nID = 0, nIDs = (INT)m_nGraphTimerIDs.GetSize(); nID < nIDs; nID++)
		{
			if (m_nGraphTimerIDs.GetAt(nID) == (UINT)nEventID)
			{
				m_nGraphTimerIDs.RemoveAt(nID);
				KillTimer(nEventID);
				break;
			}
		}
	}
	CTextView::OnTimer(nEventID);
}

void CGRDView::OnDestroy()
{
	CTextViewLock  cLock(this);

	FreeToolTipCursor();
	CTextView::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CGRDWnd

IMPLEMENT_DYNAMIC(CGRDWnd, CDisplayWnd)

CGRDWnd::CGRDWnd() : CDisplayWnd()
{
	SetType(DISPLAY_TYPE_GRD);
	SetRetrieveMode();
	SetRetrieveSpeed();
	SetRetrieveInterval();
	SetRetrieveStartTime();
	SetRetrieveStopTime();
	SetUpdateInfo();
}

BOOL CGRDWnd::Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszTitle, PDISPLAYINFO pDefaultInfo, BOOL bDefault)
{
	if (CDisplayWnd::Create(pParentWnd, (!pszTitle) ? STRING(IDS_DISPLAY_TITLE_GRD) : pszTitle, pDefaultInfo->rWnd, IDR_GRDFRAME))
	{
		if (SetScope(pDefaultInfo->nScope) && SetMode(pDefaultInfo->nMode) && Customize(bDefault)) return TRUE;
		DestroyWindow();
	}
	return FALSE;
}

BOOL CGRDWnd::SetLayout(LPCTSTR pszLayout)
{
	CGRDLayout  cLayout;

	return LoadLayout(pszLayout, cLayout) && SetLayout(cLayout);
}
BOOL CGRDWnd::SetLayout(CONST CGRDLayout &cLayout)
{
	return m_wndView.SetLayout(cLayout);
}
BOOL CGRDWnd::SetLayout(LPCTSTR pszLayout, CONST CUIntArray &nColumns)
{
	CGRDLayout  cLayout;

	return LoadLayout(pszLayout, cLayout) && SetLayout(cLayout, nColumns);
}
BOOL CGRDWnd::SetLayout(CONST CGRDLayout &cLayout, CONST CUIntArray &nColumns)
{
	return m_wndView.SetLayout(cLayout, nColumns);
}
BOOL CGRDWnd::SetLayout(LPCTSTR pszLayout, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths)
{
	CGRDLayout  cLayout;

	return LoadLayout(pszLayout, cLayout) && SetLayout(cLayout, nColumns, nWidths);
}
BOOL CGRDWnd::SetLayout(CONST CGRDLayout &cLayout, CONST CUIntArray &nColumns, CONST CUIntArray &nWidths)
{
	return m_wndView.SetLayout(cLayout, nColumns, nWidths);
}

BOOL CGRDWnd::GetLayout(CString &szLayout) CONST
{
	CGRDLayout  cLayout;

	if (GetLayout(cLayout))
	{
		szLayout = cLayout.GetName();
		return TRUE;
	}
	return FALSE;
}
BOOL CGRDWnd::GetLayout(CGRDLayout &cLayout) CONST
{
	return m_wndView.GetLayout(cLayout);
}
BOOL CGRDWnd::GetLayout(CString &szLayout, CUIntArray &nColumns) CONST
{
	CGRDLayout  cLayout;

	if (GetLayout(cLayout, nColumns))
	{
		szLayout = cLayout.GetName();
		return TRUE;
	}
	return FALSE;
}
BOOL CGRDWnd::GetLayout(CGRDLayout &cLayout, CUIntArray &nColumns) CONST
{
	return m_wndView.GetLayout(cLayout, nColumns);
}
BOOL CGRDWnd::GetLayout(CString &szLayout, CUIntArray &nColumns, CUIntArray &nWidths) CONST
{
	CGRDLayout  cLayout;

	if (GetLayout(cLayout, nColumns, nWidths))
	{
		szLayout = cLayout.GetName();
		return TRUE;
	}
	return FALSE;
}
BOOL CGRDWnd::GetLayout(CGRDLayout &cLayout, CUIntArray &nColumns, CUIntArray &nWidths) CONST
{
	return m_wndView.GetLayout(cLayout, nColumns, nWidths);
}

BOOL CGRDWnd::SetTitleFont(CFont *pFont, BOOL bDefault)
{
	return m_wndView.SetTitleFont(pFont, bDefault);
}
BOOL CGRDWnd::SetTitleFont(CONST LOGFONT *plfFont, BOOL bDefault)
{
	return m_wndView.SetTitleFont(plfFont, bDefault);
}

BOOL CGRDWnd::GetTitleFont(CFont *pFont, BOOL bDefault) CONST
{
	return m_wndView.GetTitleFont(pFont, bDefault);
}
BOOL CGRDWnd::GetTitleFont(LOGFONT *plfFont, BOOL bDefault) CONST
{
	return m_wndView.GetTitleFont(plfFont, bDefault);
}

BOOL CGRDWnd::SetItemsFont(CFont *pFont, BOOL bDefault)
{
	return m_wndView.SetItemsFont(pFont, bDefault);
}
BOOL CGRDWnd::SetItemsFont(CONST LOGFONT *plfFont, BOOL bDefault)
{
	return m_wndView.SetItemsFont(plfFont, bDefault);
}

BOOL CGRDWnd::GetItemsFont(CFont *pFont, BOOL bDefault) CONST
{
	return m_wndView.GetItemsFont(pFont, bDefault);
}
BOOL CGRDWnd::GetItemsFont(LOGFONT *plfFont, BOOL bDefault) CONST
{
	return m_wndView.GetItemsFont(plfFont, bDefault);
}

BOOL CGRDWnd::SetValuesFont(CFont *pFont, BOOL bDefault)
{
	return m_wndView.SetValuesFont(pFont, bDefault);
}
BOOL CGRDWnd::SetValuesFont(CONST LOGFONT *plfFont, BOOL bDefault)
{
	return m_wndView.SetValuesFont(plfFont, bDefault);
}

BOOL CGRDWnd::GetValuesFont(CFont *pFont, BOOL bDefault) CONST
{
	return m_wndView.GetValuesFont(pFont, bDefault);
}
BOOL CGRDWnd::GetValuesFont(LOGFONT *plfFont, BOOL bDefault) CONST
{
	return m_wndView.GetValuesFont(plfFont, bDefault);
}

BOOL CGRDWnd::SetAxesFont(CFont *pFont, BOOL bDefault)
{
	return m_wndView.SetAxesFont(pFont, bDefault);
}
BOOL CGRDWnd::SetAxesFont(CONST LOGFONT *plfFont, BOOL bDefault)
{
	return m_wndView.SetAxesFont(plfFont, bDefault);
}

BOOL CGRDWnd::GetAxesFont(CFont *pFont, BOOL bDefault) CONST
{
	return m_wndView.GetAxesFont(pFont, bDefault);
}
BOOL CGRDWnd::GetAxesFont(LOGFONT *plfFont, BOOL bDefault) CONST
{
	return m_wndView.GetAxesFont(plfFont, bDefault);
}

BOOL CGRDWnd::SetMarkers(CONST CGRDMarkers &pMarkers)
{
	return m_wndView.SetMarkers(pMarkers);
}

BOOL CGRDWnd::GetMarkers(CGRDMarkers &pMarkers) CONST
{
	return m_wndView.GetMarkers(pMarkers);
}

BOOL CGRDWnd::SetOolColors(CONST CUIntArray &nColors)
{
	return m_wndView.SetOolColors(nColors);
}

BOOL CGRDWnd::GetOolColors(CUIntArray &nColors) CONST
{
	return m_wndView.GetOolColors(nColors);
}

BOOL CGRDWnd::SetScalingData(CONST CByteArray &nScalingData)
{
	return m_wndView.SetScalingData(nScalingData);
}

BOOL CGRDWnd::GetScalingData(CByteArray &nScalingData) CONST
{
	return m_wndView.GetScalingData(nScalingData);
}

BOOL CGRDWnd::EnableInvalidDataMode(BOOL bEnable)
{
	return m_wndView.EnableInvalidDataMode(bEnable);
}

BOOL CGRDWnd::IsInvalidDataModeEnabled() CONST
{
	return m_wndView.IsInvalidDataModeEnabled();
}

BOOL CGRDWnd::EnableBadDataMode(BOOL bEnable)
{
	return m_wndView.EnableBadDataMode(bEnable);
}

BOOL CGRDWnd::IsBadDataModeEnabled() CONST
{
	return m_wndView.IsBadDataModeEnabled();
}

BOOL CGRDWnd::EnableToolTipMode(BOOL bEnable)
{
	return m_wndView.EnableToolTipMode(bEnable);
}

BOOL CGRDWnd::IsToolTipModeEnabled() CONST
{
	return m_wndView.IsToolTipModeEnabled();
}

BOOL CGRDWnd::Start()
{
	if (((GetMode() == DISPLAY_MODE_REALTIME  &&  ProcessRealtimeData()) || (GetMode() == DISPLAY_MODE_HISTORY  &&  StartRetrieveData())) && StartSchedulePrintJobs())
	{
		Initialize(TRUE);
		UpdateAllPanes();
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDWnd::Prepare(BOOL bDialog)
{
	INT  nResult;

	if (bDialog)
	{
		if ((nResult = m_dlgOpen.Create(this)) == IDCANCEL || nResult <= 0) MDIDestroy();
		return((nResult == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
	}
	return TRUE;
}

BOOL CGRDWnd::Initialize(BOOL bFlag)
{
	return CDisplayWnd::Initialize(bFlag);
}
BOOL CGRDWnd::Initialize(CTMEnvironment *pTMEnvironment)
{
	return m_wndView.Initialize(pTMEnvironment);
}
BOOL CGRDWnd::Initialize(CString &szTag, CTimeTag &tTag)
{
	if (m_wndView.Initialize(szTag, tTag))
	{
		m_wndView.InitializeScalingData();
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDWnd::InitializeTMData(UINT nMode)
{
	for (StopRetrieveData(); (nMode == DISPLAY_MODE_REALTIME && SetMode(DISPLAY_MODE_REALTIME) && ProcessRealtimeData()) || (nMode == DISPLAY_MODE_HISTORY && SetMode(DISPLAY_MODE_HISTORY) && StartRetrieveData()); )
	{
		UpdateBars();
		return TRUE;
	}
	return FALSE;
}
BOOL CGRDWnd::InitializeTMData(CTMParameters &pTMParameters, BOOL bBadData)
{
	CDisplayWnd  *pDisplayWnd;

	return((GetMode() == DISPLAY_MODE_HISTORY) ? (((pDisplayWnd = GetLink())) ? pDisplayWnd->InitializeTMData(pTMParameters, bBadData) : m_cRetrieveThread.InitializeTMData(pTMParameters, bBadData)) : GetTMService()->InitializeTMData(pTMParameters, bBadData));
}

BOOL CGRDWnd::Check() CONST
{
	return CheckAccountPrivilege(PRIVILEGE_GRD_USE);
}

VOID CGRDWnd::Update()
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
BOOL CGRDWnd::Update(CONST CTimeKey &tTimeKey, CTMEnvironment *pTMEnvironment, UINT nFlags)
{
	INT  nLink;
	INT  nLinks;
	CPtrArray  pLinks;
	CGRDLayout  cLayout;
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
		return(((nFlags & HISTORYFILE_SUCCESS) && !(nFlags & HISTORYFILE_TMUNIT) && !(nFlags & HISTORYFILE_TMPARAMETERS)) ? TRUE : FALSE);
	}
	return FALSE;
}

VOID CGRDWnd::Reset(CTMEnvironment *pTMEnvironment)
{
	CDisplayLock  cLock(this);

	if (IsInitialized())
	{
		if (pTMEnvironment != (CTMEnvironment *)NULL) pTMEnvironment->Reset();
		m_wndView.Reset(pTMEnvironment);
		SetUpdateInfo();
	}
}

BOOL CGRDWnd::Stop()
{
	Initialize(FALSE);
	StopSchedulePrintJobs();
	StopRetrieveData();
	return TRUE;
}

BOOL CGRDWnd::SaveInfo(INT nPage, INT nDisplay, LPCTSTR pszTitle, CONST PDISPLAYINFO pDisplayInfo)
{
	UINT  nMode;
	UINT  nSpeed;
	CString  szFileName;
	LOGFONT  sFontInfo[4][2];
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CUIntArray  nColumns;
	CUIntArray  nWidths;
	CUIntArray  nColors;
	CByteArray  nMarkerData;
	CByteArray  nScalingData;
	CByteArray  nPrintInfo;
	CGRDLayout  cLayout;
	CProfile  cProfile;

	return((CDisplayWnd::SaveInfo(nPage, nDisplay, pszTitle, pDisplayInfo) && GetLayout(cLayout, nColumns, nWidths) && GetMarkerData(nMarkerData) && GetScalingData(nScalingData) && GetOolColors(nColors) && GetTitleFont(&sFontInfo[0][0], FALSE) && GetTitleFont(&sFontInfo[0][1], TRUE) && GetItemsFont(&sFontInfo[1][0], FALSE) && GetItemsFont(&sFontInfo[1][1], TRUE) && GetValuesFont(&sFontInfo[2][0], FALSE) && GetValuesFont(&sFontInfo[2][1], TRUE) && GetAxesFont(&sFontInfo[3][0], FALSE) && GetAxesFont(&sFontInfo[3][1], TRUE) && GetRetrieveMode(nMode) && GetRetrieveSpeed(nSpeed) && GetRetrieveInterval(tInterval) && GetRetrieveStartTime(tStartTime) && GetRetrieveStopTime(tStopTime) && GetRetrieveFileName(szFileName) && GetPrintJobs(nPrintInfo) && cProfile.SetGRDLayoutName(nPage, nDisplay, cLayout.GetName()) && cProfile.SetGRDLayoutInfo(nPage, nDisplay, nColumns, nWidths, nColors, nMarkerData, nScalingData, IsInvalidDataModeEnabled(), IsBadDataModeEnabled(), IsToolTipModeEnabled()) && cProfile.SetGRDFontsInfo(nPage, nDisplay, &sFontInfo[0][0], &sFontInfo[0][1], &sFontInfo[1][0], &sFontInfo[1][1], &sFontInfo[2][0], &sFontInfo[2][1], &sFontInfo[3][0], &sFontInfo[3][1]) && cProfile.SetGRDModeInfo(nPage, nDisplay, nMode, nSpeed, tInterval, tStartTime, tStopTime) && cProfile.SetGRDRetrieveFileName(nPage, nDisplay, szFileName) && cProfile.SetGRDPrintInfo(nPage, nDisplay, nPrintInfo)) ? TRUE : FALSE);
}

BOOL CGRDWnd::LoadInfo(INT nPage, INT nDisplay, CString &szTitle, PDISPLAYINFO pDisplayInfo)
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
	CByteArray  nMarkerData;
	CByteArray  nScalingData;
	CByteArray  nPrintInfo;
	CProfile  cProfile;

	return((CDisplayWnd::LoadInfo(nPage, nDisplay, szTitle, pDisplayInfo) && cProfile.GetGRDLayoutName(nPage, nDisplay, szName) && cProfile.GetGRDLayoutInfo(nPage, nDisplay, nColumns, nWidths, nColors, nMarkerData, nScalingData, bInvalidData, bBadData, bToolTips) && cProfile.GetGRDFontsInfo(nPage, nDisplay, &sFontInfo[0][0], &sFontInfo[0][1], &sFontInfo[1][0], &sFontInfo[1][1], &sFontInfo[2][0], &sFontInfo[2][1], &sFontInfo[3][0], &sFontInfo[3][1]) && cProfile.GetGRDModeInfo(nPage, nDisplay, nMode, nSpeed, tInterval, tStartTime, tStopTime) && cProfile.GetGRDRetrieveFileName(nPage, nDisplay, szFileName) && cProfile.GetGRDPrintInfo(nPage, nDisplay, nPrintInfo) && SetLayout(szName, nColumns, nWidths) && SetMarkerData(nMarkerData) && SetScalingData(nScalingData) && SetOolColors(nColors) && EnableInvalidDataMode(bInvalidData) && EnableBadDataMode(bBadData) && EnableToolTipMode(bToolTips) && SetTitleFont(&sFontInfo[0][1], TRUE) && SetTitleFont(&sFontInfo[0][0], FALSE) && SetItemsFont(&sFontInfo[1][1], TRUE) && SetItemsFont(&sFontInfo[1][0], FALSE) && SetValuesFont(&sFontInfo[2][1], TRUE) && SetValuesFont(&sFontInfo[2][0], FALSE) && SetAxesFont(&sFontInfo[3][1], TRUE) && SetAxesFont(&sFontInfo[3][0], FALSE) && SetRetrieveMode(nMode) && SetRetrieveSpeed(nSpeed) && SetRetrieveInterval(tInterval) && SetRetrieveStartTime(tStartTime) && SetRetrieveStopTime(tStopTime) && SetRetrieveFileName(szFileName) && SetPrintJobs(nPrintInfo)) ? TRUE : FALSE);
}

BOOL CGRDWnd::QueryDefaultInfo(PDISPLAYINFO pDefaultInfo) CONST
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

BOOL CGRDWnd::QueryDefaultMenu(CLocaleMenu &cMenu, CImageList &cImages, CUIntArray &nImageIDs) CONST
{
	INT  nIndex;
	INT  nCount;
	INT  iImage;
	UINT  nButtonID;
	UINT  nButtonStyle;
	CBitmap  cBitmap;
	BITMAP  sBitmap;

	for (cImages.DeleteImageList(), nImageIDs.RemoveAll(); cBitmap.LoadBitmap(IDB_GRDFRAMESMALLIMAGES) && cBitmap.GetBitmap(&sBitmap); )
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
	return cMenu.LoadMenu(IDR_GRDFRAME);
}

VOID CGRDWnd::ReduceFonts(BOOL bRestore)
{
	m_wndView.ReduceFonts(bRestore);
}

BOOL CGRDWnd::CanReduceFonts(BOOL bRestore) CONST
{
	return m_wndView.CanReduceFonts(bRestore);
}

VOID CGRDWnd::ReducePlotArea(BOOL bRestore)
{
	m_wndView.ReducePlotArea(bRestore);
}

VOID CGRDWnd::UpdateSysMenu(CMenu *pMenu)
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

VOID CGRDWnd::UpdateBars()
{
	CDisplayLock  cLock(this);

	UpdateMessagePane();
	UpdateModePane();
	UpdateTypePane();
}

BOOL CGRDWnd::Print(PRINTDLG *pPrintInfo)
{
	INT  nJob;
	INT  nJobs;
	CGRDPrintJobs  pJobs;
	CGRDPrintJobInfo  *pJobInfo;
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
		if (pJobInfo->GetPrintMode() & GRD_PRINT_CLEARCOMMENTS)
		{
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~GRD_PRINT_CLEARCOMMENTS);
			pJobInfo->SetComments(EMPTYSTRING);
			SetPrintJobs(pJobs);
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDWnd::CanPrint() CONST
{
	return HasLayout();
}

BOOL CGRDWnd::ProcessRealtimeData()
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

BOOL CGRDWnd::StartRetrieveData(UINT nMode, UINT nSpeed, CONST CTimeSpan &tInterval, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime)
{
	SetRetrieveMode(nMode);
	SetRetrieveSpeed(nSpeed);
	SetRetrieveInterval(tInterval);
	SetRetrieveStartTime(tStartTime);
	SetRetrieveStopTime(tStopTime);
	return StartRetrieveData();
}
BOOL CGRDWnd::StartRetrieveData()
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
			ReportEvent(SYSTEM_WARNING_GRD_RETRIEVE_FAILURE);
			return FALSE;
		}
		if (!IsRetrievingData())
		{
			if (m_cRetrieveThread.Start(this, bInit[0], bInit[1], GetRetrieveFileName(), GetRetrieveMode(), GetRetrieveSpeed(), GetRetrieveInterval(), GetRetrieveStartTime(), GetRetrieveStopTime(), &m_bRetrieveFlag, m_cRetrieveStop, m_cRetrieveAutoForward, m_cRetrieveManualForward, m_cRetrievePseudoRealtime) && UpdateAllPanes())
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
			ReportEvent(SYSTEM_WARNING_GRD_RETRIEVE_FAILURE);
		}
	}
	return FALSE;
}

LONG CGRDWnd::IsRetrievingData() CONST
{
	LONG  bFlag;

	InterlockedExchange(&bFlag, m_bRetrieveFlag);
	return((m_cRetrieveThread.IsThreadActive()) ? bFlag : FALSE);
}

BOOL CGRDWnd::RetrieveMoreData(UINT nAction)
{
	if (IsRetrievingData())
	{
		if (nAction == GRD_RETRIEVE_STOPPED)
		{
			SetRetrieveMode(GetRetrieveMode() | nAction);
			m_cRetrieveStop.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
		if (nAction == GRD_RETRIEVE_AUTOFORWARD)
		{
			SetRetrieveMode((GetRetrieveMode() & (GRD_RETRIEVE_EXACTTIME | GRD_RETRIEVE_STOPBYTIME | GRD_RETRIEVE_STOPBYEND | GRD_RETRIEVE_STOPBYREALTIME)) | nAction);
			m_cRetrieveAutoForward.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
		if (nAction == GRD_RETRIEVE_MANUALFORWARD)
		{
			SetRetrieveMode((GetRetrieveMode() & (GRD_RETRIEVE_EXACTTIME | GRD_RETRIEVE_STOPBYTIME | GRD_RETRIEVE_STOPBYEND | GRD_RETRIEVE_STOPBYREALTIME)) | nAction);
			m_cRetrieveManualForward.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
		if (nAction == GRD_RETRIEVE_PSEUDOREALTIME)
		{
			SetRetrieveMode((GetRetrieveMode() & (GRD_RETRIEVE_EXACTTIME | GRD_RETRIEVE_STOPBYTIME | GRD_RETRIEVE_STOPBYEND | GRD_RETRIEVE_STOPBYREALTIME)) | nAction);
			m_cRetrievePseudoRealtime.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CGRDWnd::StopRetrieveData()
{
	return(((IsRetrievingData() && m_cRetrieveThread.Stop()) || !IsRetrievingData()) ? TRUE : FALSE);
}

BOOL CGRDWnd::SetRetrieveMode(UINT nMode)
{
	CDisplayLock  cLock(this);

	m_nRetrieveMode = nMode;
	m_bRetrieveFlag = MAKELONG((nMode) ? LOWORD(m_bRetrieveFlag) : FALSE, (nMode) ? HIWORD(m_bRetrieveFlag) : FALSE);
	return TRUE;
}

BOOL CGRDWnd::GetRetrieveMode(UINT &nMode) CONST
{
	nMode = m_nRetrieveMode;
	return TRUE;
}
UINT CGRDWnd::GetRetrieveMode() CONST
{
	return m_nRetrieveMode;
}

BOOL CGRDWnd::SetRetrieveSpeed(UINT nSpeed)
{
	m_nRetrieveSpeed = nSpeed;
	return TRUE;
}

BOOL CGRDWnd::GetRetrieveSpeed(UINT &nSpeed) CONST
{
	nSpeed = m_nRetrieveSpeed;
	return TRUE;
}
UINT CGRDWnd::GetRetrieveSpeed() CONST
{
	return m_nRetrieveSpeed;
}

BOOL CGRDWnd::SetRetrieveInterval(CONST CTimeSpan &tInterval)
{
	CDisplayLock  cLock(this);

	m_tRetrieveInterval = tInterval;
	return TRUE;
}

BOOL CGRDWnd::GetRetrieveInterval(CTimeSpan &tInterval) CONST
{
	CDisplayLock  cLock(this);

	tInterval = m_tRetrieveInterval;
	return TRUE;
}
CTimeSpan CGRDWnd::GetRetrieveInterval() CONST
{
	CDisplayLock  cLock(this);

	return m_tRetrieveInterval;
}

BOOL CGRDWnd::SetRetrieveStartTime(CONST CTimeKey &tStartTime)
{
	CDisplayLock  cLock(this);

	m_tRetrieveStartTime = tStartTime;
	return TRUE;
}

BOOL CGRDWnd::GetRetrieveStartTime(CTimeKey &tStartTime) CONST
{
	CDisplayLock  cLock(this);

	tStartTime = m_tRetrieveStartTime;
	return TRUE;
}
CTimeKey CGRDWnd::GetRetrieveStartTime() CONST
{
	CDisplayLock  cLock(this);

	return m_tRetrieveStartTime;
}

BOOL CGRDWnd::SetRetrieveStopTime(CONST CTimeKey &tStopTime)
{
	CDisplayLock  cLock(this);

	m_tRetrieveStopTime = tStopTime;
	return TRUE;
}

BOOL CGRDWnd::GetRetrieveStopTime(CTimeKey &tStopTime) CONST
{
	CDisplayLock  cLock(this);

	tStopTime = m_tRetrieveStopTime;
	return TRUE;
}
CTimeKey CGRDWnd::GetRetrieveStopTime() CONST
{
	CDisplayLock  cLock(this);

	return m_tRetrieveStopTime;
}

BOOL CGRDWnd::SetRetrieveFileName(LPCTSTR pszFileName)
{
	CDisplayLock  cLock(this);

	m_szRetrieveFileName = pszFileName;
	return TRUE;
}

BOOL CGRDWnd::GetRetrieveFileName(CString &szFileName) CONST
{
	CDisplayLock  cLock(this);

	szFileName = GetRetrieveFileName();
	return TRUE;
}
CString CGRDWnd::GetRetrieveFileName() CONST
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

VOID CGRDWnd::SetParameterInfo(LPCTSTR pszTag)
{
	ReportEvent((m_dlgParameters.Create(this, pszTag) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

BOOL CGRDWnd::GetParameterInfo(LPCTSTR pszTag, INT nIndex, CTMParameter *pTMParameter, CGRDParameterSamples &pParameterSamples) CONST
{
	return m_wndView.GetParameterInfo(pszTag, nIndex, pTMParameter, pParameterSamples);
}

BOOL CGRDWnd::SetPrintJobs(CONST CGRDPrintJobs &pPrintJobs)
{
	return m_cPrintThread.SetPrintJobs(pPrintJobs);
}

BOOL CGRDWnd::GetPrintJobs(CGRDPrintJobs &pPrintJobs) CONST
{
	return m_cPrintThread.GetPrintJobs(pPrintJobs);
}

VOID CGRDWnd::ExecutePrintJobs()
{
	INT  nJob;
	INT  nJobs;
	CGRDPrintJobs  pJobs;
	CGRDPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (GetPrintJobs(pJobs)) ? (INT)pJobs.GetSize() : 0; nJob < nJobs; nJob++)
	{
		if ((pJobInfo = (CGRDPrintJobInfo *)pJobs.GetAt(nJob)) != (CGRDPrintJobInfo *)NULL)
		{
			if ((pJobInfo->GetPrintMode() & GRD_PRINT_ATEXPIRATION) == GRD_PRINT_ATEXPIRATION)
			{
				ReportEvent((!Print(pJobInfo)) ? SYSTEM_WARNING_GRD_PRINT_FAILURE : SYSTEM_NOERROR);
				continue;
			}
		}
	}
}

BOOL CGRDWnd::Print(CONST CGRDPrintJobInfo *pJobInfo, PRINTDLG *pPrintInfo)
{
	CDC  cDC;
	UINT  nMode;
	UINT  nIndent;
	UINT  nTMUnit;
	BOOL  bMetric;
	BOOL  bQuality;
	RECT  rtMargin[2];
	SIZE  ptPaperSize;
	CSize  sizeImage;
	HANDLE  hDevNames;
	HANDLE  hDevMode;
	CString  szTMUnit;
	CTimeTag  tTMUnit;
	LOGFONT  lfFont[1];
	DEVMODE  *pDevMode[2];
	DEVNAMES  *pDevNames[2];
	CPtrArray  pItemsFonts;
	CUIntArray  nOOLColors;
	CGRDLayout  cLayout;
	CMetaFileDC  cMetaDC;
	CStringArray  szColumns;
	CStringArray  szContents;
	CTMParameters  pValues;
	CPrintProfiles  cPrintProfiles;
	CPrintProfileInfo  *pPrintProfileInfo;

	if ((pPrintProfileInfo = (GetPrintProfiles(cPrintProfiles)) ? cPrintProfiles.GetAt(cPrintProfiles.Find(pJobInfo->GetProfile())) : (CPrintProfileInfo *)NULL) && pPrintProfileInfo->GetPaperInfo(ptPaperSize, rtMargin[0], rtMargin[1], bMetric))
	{
		if (GetPrintProperties(pJobInfo, cLayout, nMode, szTMUnit, tTMUnit, nTMUnit, bQuality, szColumns, szContents, pValues, nOOLColors, &lfFont[0], pItemsFonts, cMetaDC, sizeImage, nIndent))
		{
			if (pPrintInfo == (PRINTDLG *)NULL)
			{
				if (CreatePrinterDC(pPrintProfileInfo, cDC))
				{
					if (PrintJob(cDC, pJobInfo, pPrintProfileInfo->GetPrinterName(), 0, 0, rtMargin[0], bMetric, cLayout, nMode, szTMUnit, tTMUnit, nTMUnit, bQuality, szColumns, szContents, pValues, nOOLColors, &lfFont[0], pItemsFonts, cMetaDC, sizeImage, nIndent))
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
				for (DeleteEnhMetaFile(cMetaDC.CloseEnhanced()); pItemsFonts.GetSize() > 0; pItemsFonts.RemoveAt(pItemsFonts.GetUpperBound()))
				{
					GlobalFree(pItemsFonts.GetAt(pItemsFonts.GetUpperBound()));
					continue;
				}
				return FALSE;
			}
			if ((hDevNames = (HANDLE)GlobalAlloc(GHND, GlobalSize(pPrintInfo->hDevNames))))
			{
				if ((hDevMode = (HANDLE)GlobalAlloc(GHND, GlobalSize(pPrintInfo->hDevMode))))
				{
					if ((pDevNames[0] = (DEVNAMES *)GlobalLock(pPrintInfo->hDevNames)))
					{
						if ((pDevMode[0] = (DEVMODE *)GlobalLock(pPrintInfo->hDevMode)))
						{
							if ((pDevNames[1] = (DEVNAMES *)GlobalLock(hDevNames)))
							{
								if ((pDevMode[1] = (DEVMODE *)GlobalLock(hDevMode)))
								{
									for (CopyMemory(pDevNames[1], pDevNames[0], GlobalSize(pPrintInfo->hDevNames)), CopyMemory(pDevMode[1], pDevMode[0], GlobalSize(pPrintInfo->hDevMode)), pDevMode[1]->dmColor = (pJobInfo->GetPrintMode() & GRD_PRINT_NOCOLORS) ? DMCOLOR_MONOCHROME : pDevMode[0]->dmColor; CreatePrinterDC(hDevNames, hDevMode, cDC); )
									{
										if (PrintJob(cDC, pJobInfo, (LPCTSTR)pDevMode[0]->dmDeviceName, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nFromPage : 0, (pPrintInfo->Flags & PD_PAGENUMS) ? pPrintInfo->nToPage : 0, rtMargin[0], bMetric, cLayout, nMode, szTMUnit, tTMUnit, nTMUnit, bQuality, szColumns, szContents, pValues, nOOLColors, &lfFont[0], pItemsFonts, cMetaDC, sizeImage, nIndent))
										{
											for (; pItemsFonts.GetSize() > 0; pItemsFonts.RemoveAt(pItemsFonts.GetUpperBound()))
											{
												GlobalFree(pItemsFonts.GetAt(pItemsFonts.GetUpperBound()));
												continue;
											}
											GlobalUnlock(pPrintInfo->hDevNames);
											GlobalUnlock(pPrintInfo->hDevMode);
											GlobalUnlock(hDevNames);
											GlobalUnlock(hDevMode);
											GlobalFree(hDevNames);
											GlobalFree(hDevMode);
											cDC.DeleteDC();
											return TRUE;
										}
										cDC.DeleteDC();
										break;
									}
									GlobalUnlock(hDevMode);
								}
								GlobalUnlock(hDevNames);
							}
							GlobalUnlock(pPrintInfo->hDevMode);
						}
						GlobalUnlock(pPrintInfo->hDevNames);
					}
					GlobalFree(hDevMode);
				}
				GlobalFree(hDevNames);
			}
			for (DeleteEnhMetaFile(cMetaDC.CloseEnhanced()); pItemsFonts.GetSize() > 0; pItemsFonts.RemoveAt(pItemsFonts.GetUpperBound()))
			{
				GlobalFree(pItemsFonts.GetAt(pItemsFonts.GetUpperBound()));
				continue;
			}
		}
	}
	return FALSE;
}

CGRDWnd *CGRDWnd::Find(INT nType, UINT nMode, LPCTSTR pszName) CONST
{
	INT  nDisplay;
	INT  nDisplays;
	CGRDWnd  *pGRDWnd;
	CGRDLayout  cLayout;
	CDisplayWnd  *pDisplayWnd;
	CPtrArray  pDisplays;

	for (nDisplay = 0, nDisplays = GetDisplayArea()->EnumDisplays(pDisplays), pGRDWnd = (CGRDWnd *)NULL; nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_GRD  &&  HIWORD(pDisplayWnd->GetType()) == HIWORD(nType) && pDisplayWnd->GetMode() == nMode)
		{
			if ((pGRDWnd = (CGRDWnd *)pDisplayWnd)->GetLayout(cLayout) && cLayout.GetName() == pszName) break;
			continue;
		}
	}
	return((nDisplay < nDisplays) ? pGRDWnd : (CGRDWnd *)NULL);
}

VOID CGRDWnd::SetUpdateInfo()
{
	CDisplayLock  cLock(this);

	m_szTMUnit.Empty();
	m_tTMUnit = 0;
	m_nTMUnit = 0;
	m_wTMUnit = TMUNIT_DATAQUALITY_NONE;
	UpdateMessagePane();
}
VOID CGRDWnd::SetUpdateInfo(LPCTSTR pszTag, CONST CTimeTag &tTag, UINT nTag, WORD wQuality)
{
	CDisplayLock  cLock(this);

	m_szTMUnit = pszTag;
	m_tTMUnit = tTag;
	m_nTMUnit = nTag;
	m_wTMUnit = wQuality;
	UpdateMessagePane();
}

BOOL CGRDWnd::GetUpdateInfo(CString &szTag, CTimeTag &tTag, UINT &nTag, WORD &wQuality) CONST
{
	CDisplayLock  cLock(this);

	szTag = m_szTMUnit;
	tTag = m_tTMUnit;
	nTag = m_nTMUnit;
	wQuality = m_wTMUnit;
	return TRUE;
}

BOOL CGRDWnd::CreateToolBar()
{
	if (m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE) && m_wndToolBar.LoadToolBar(IDB_GRDFRAMELARGEIMAGES, 0, IDB_GRDFRAMESMALLIMAGES, TRUE))
	{
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_GRDSETTINGS), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_GRDLINKAGES), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_GRDPARAMETERS), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_GRDHOLD), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_GRDRETRIEVALS), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_GRDRETRIEVESTOP), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_GRDRETRIEVESTEPFORWARD), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_GRDRETRIEVEFORWARD), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_GRDRETRIEVEPSEUDOREALTIME), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_GRDPRINT), TBBS_DISABLED);
		DockPane(&m_wndToolBar);
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDWnd::CreateStatusBar()
{
	if (m_wndStatusBar.Create(this, CBRS_BOTTOM | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE) && m_wndStatusBar.SetIndicators(nGRDStatusBarIndicators, 1))
	{
		m_wndStatusBar.EnableToolTips();
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDWnd::CreateView()
{
	if (m_wndView.Create(this, TVS_HEADER | TVS_TOP | TVS_NOSELECTION | TVS_HSCROLL | TVS_VSCROLL | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE))
	{
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDWnd::Customize(BOOL bDefault)
{
	CString  szTitle;
	LOGFONT  sFontInfo[4];
	CUIntArray  nColumns;
	CUIntArray  nWidths;
	CGRDLayout  cLayout;

	if ((!bDefault  &&  GetLayout(cLayout, nColumns, nWidths) && GetTitleFont(&sFontInfo[0], FALSE) && GetItemsFont(&sFontInfo[1], FALSE) && GetValuesFont(&sFontInfo[2], FALSE) && GetAxesFont(&sFontInfo[3], FALSE) && SetLayout(cLayout, nColumns, nWidths) && SetTitleFont(&sFontInfo[0], FALSE) && SetItemsFont(&sFontInfo[1], FALSE) && SetValuesFont(&sFontInfo[2], FALSE) && SetAxesFont(&sFontInfo[3], FALSE)) || (bDefault  &&  GetLayout(cLayout) && SetLayout(cLayout)))
	{
		for (szTitle.Format(STRING(IDS_WINDOW_FULLTITLE), STRING(IDS_DISPLAY_TITLE_GRD), (!cLayout.GetTitle().IsEmpty()) ? (LPCTSTR)cLayout.GetTitle() : (LPCTSTR)cLayout.GetName()); !bDefault; )
		{
			SetWindowText(szTitle);
			ReducePlotArea();
			break;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDWnd::UpdateAllPanes()
{
	INT  nPane;
	INT  nPanes;

	for (nPane = 0, nPanes = sizeof(nGRDStatusBarIndicators) / sizeof(UINT); nPane < nPanes; nPane++)
	{
		if (m_wndStatusBar.CommandToIndex(nGRDStatusBarIndicators[nPane]) != nPane) break;
		continue;
	}
	if (nPane < nPanes)
	{
		if (m_wndStatusBar.SetIndicators(nGRDStatusBarIndicators, sizeof(nGRDStatusBarIndicators) / sizeof(UINT)))
		{
			UpdateBars();
			return TRUE;
		}
		return FALSE;
	}
	UpdateBars();
	return TRUE;
}

VOID CGRDWnd::UpdateMessagePane()
{
	UINT  nTag;
	WORD  wQuality;
	CTimeTag  tTag;
	CString  szTag;
	CString  szMessage;

	if (GetUpdateInfo(szTag, tTag, nTag, wQuality))
	{
		szMessage.Format((szTag.IsEmpty()) ? ((tTag > 0) ? STRING(IDS_GRD_STATUSBAR_FULLUPDATEMESSAGE) : ((IsRetrievingData() && HIWORD(IsRetrievingData())) ? STRING(IDS_GRD_STATUSBAR_RETRIEVEMESSAGE) : STRING(IDS_GRD_STATUSBAR_NODATAMESSAGE))) : ((nTag == (UINT)-1) ? STRING(IDS_GRD_STATUSBAR_INITUPDATEMESSAGE) : STRING(IDS_GRD_STATUSBAR_UPDATEMESSAGE)), (LPCTSTR)tTag.FormatGmt(), (LPCTSTR)szTag, nTag, ((wQuality & (TMUNIT_DATAQUALITY_GOOD | TMUNIT_SEQUENCEQUALITY_GOOD)) == (TMUNIT_DATAQUALITY_GOOD | TMUNIT_SEQUENCEQUALITY_GOOD)) ? ((wQuality & TMUNIT_TIMECORRELATION_BAD) ? (LPCTSTR)(CString(STRING(IDS_GRD_STATUSBAR_QUALITYGOOD)) + STRING(IDS_GRD_STATUSBAR_TIMECORRELATIONFLAG)) : STRING(IDS_GRD_STATUSBAR_QUALITYGOOD)) : ((wQuality & TMUNIT_TIMECORRELATION_BAD) ? (LPCTSTR)(CString(STRING(IDS_GRD_STATUSBAR_QUALITYBAD)) + STRING(IDS_GRD_STATUSBAR_TIMECORRELATIONFLAG)) : STRING(IDS_GRD_STATUSBAR_QUALITYBAD)));
		m_wndStatusBar.SetPaneText(ID_GRD_STATUSBAR_MESSAGEPANE, szMessage);
	}
}

VOID CGRDWnd::UpdateModePane()
{
	CString  szMode;
	CGRDLayout  cLayout;
	CDisplayWnd  *pDisplayWnd;

	for (szMode.Empty(); (pDisplayWnd = (CDisplayWnd *)GetLink()) && GetLayout(cLayout); )
	{
		szMode.Format(STRING(IDS_DISPLAY_MODE_LINK), STRING(IDS_DISPLAY_TITLE_GRD), (LPCTSTR)cLayout.GetName());
		break;
	}
	m_wndStatusBar.SetPaneText(ID_GRD_STATUSBAR_MODEPANE, (GetMode() == DISPLAY_MODE_HISTORY) ? (((GetRetrieveMode() & GRD_RETRIEVE_AUTOFORWARD) && !(GetRetrieveMode() & GRD_RETRIEVE_STOPPED)) ? STRING(IDS_GRD_STATUSBAR_AUTOFORWARDMODE) : (((GetRetrieveMode() & GRD_RETRIEVE_PSEUDOREALTIME) && !(GetRetrieveMode() & GRD_RETRIEVE_STOPPED)) ? STRING(IDS_GRD_STATUSBAR_PSEUDOREALTIMEMODE) : ((!szMode.IsEmpty()) ? (STRING(IDS_GRD_STATUSBAR_NORMALMODE) + szMode) : STRING(IDS_GRD_STATUSBAR_NORMALMODE)))) : ((!szMode.IsEmpty()) ? (STRING(IDS_DISPLAY_MODE_REALTIME) + szMode) : STRING(IDS_DISPLAY_MODE_REALTIME)));
	m_wndToolBar.EnableButton(IDM_GRDRETRIEVESTOP, (IsRetrievingData() && ((GetRetrieveMode() & GRD_RETRIEVE_AUTOFORWARD) || (GetRetrieveMode() & GRD_RETRIEVE_PSEUDOREALTIME) || HIWORD(IsRetrievingData())) && !(GetRetrieveMode() & GRD_RETRIEVE_STOPPED)) ? TRUE : FALSE);
	m_wndToolBar.EnableButton(IDM_GRDRETRIEVEFORWARD, (IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & GRD_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & GRD_RETRIEVE_STOPPED))) ? TRUE : FALSE);
	m_wndToolBar.EnableButton(IDM_GRDRETRIEVESTEPFORWARD, (IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & GRD_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & GRD_RETRIEVE_STOPPED))) ? TRUE : FALSE);
	m_wndToolBar.EnableButton(IDM_GRDRETRIEVEPSEUDOREALTIME, (IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & GRD_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & GRD_RETRIEVE_STOPPED))) ? TRUE : FALSE);
}

VOID CGRDWnd::UpdateTypePane()
{
	CString  szType;
	CString  szLayout;

	switch (HIWORD(GetType()))
	{
	case GRD_TYPE_NORMAL:
	{ if (GetLayout(szLayout))
	{
		szType.Format(STRING(IDS_GRD_STATUSBAR_TYPENORMAL), (LPCTSTR)szLayout);
		break;
	}
	szType = STRING(IDS_GRD_STATUSBAR_TYPENORMAL);
	szType = szType.Left((szType.Find(SPACE) >= 0) ? szType.Find(SPACE) : lstrlen(STRING(IDS_GRD_STATUSBAR_TYPENORMAL)));
	break;
	}
	case GRD_TYPE_TEMPORARY:
	{ szType = STRING(IDS_GRD_STATUSBAR_TYPETEMPORARY);
	break;
	}
	}
	m_wndStatusBar.SetPaneText(ID_GRD_STATUSBAR_TYPEPANE, szType);
}

VOID CGRDWnd::UpdateData()
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

BOOL CGRDWnd::LoadLayout(LPCTSTR pszLayout, CGRDLayout &cLayout)
{
	return((HIWORD(GetType()) != GRD_TYPE_NORMAL) ? ((HIWORD(GetType()) == GRD_TYPE_TEMPORARY) ? LoadTemporaryGRD(pszLayout, cLayout) : FALSE) : GetDatabase()->LoadGRD(pszLayout, cLayout));
}

BOOL CGRDWnd::HasLayout() CONST
{
	return m_wndView.HasParameters();
}

VOID CGRDWnd::SetHoldFlag(BOOL bEnable)
{
	m_wndView.SetHoldFlag(bEnable);
}

BOOL CGRDWnd::GetHoldFlag() CONST
{
	return m_wndView.GetHoldFlag();
}

BOOL CGRDWnd::HasHoldFlag() CONST
{
	return m_wndView.HasHoldFlag();
}

BOOL CGRDWnd::StartSchedulePrintJobs()
{
	return IsSchedulingPrintJobs() || m_cPrintThread.Start(this);
}

BOOL CGRDWnd::IsSchedulingPrintJobs() CONST
{
	return((m_cPrintThread.IsThreadActive()) ? TRUE : FALSE);
}

BOOL CGRDWnd::StopSchedulePrintJobs()
{
	return((IsSchedulingPrintJobs() && m_cPrintThread.Stop()) ? TRUE : FALSE);
}

BOOL CGRDWnd::SetMarkerData(CONST CByteArray &nMarkerInfo)
{
	CGRDMarkers  pMarkers;

	return((pMarkers.Unmap(nMarkerInfo) && m_wndView.SetMarkers(pMarkers)) ? TRUE : FALSE);
}

BOOL CGRDWnd::GetMarkerData(CByteArray &nMarkerInfo) CONST
{
	CGRDMarkers  pMarkers;

	return((m_wndView.GetMarkers(pMarkers) && pMarkers.Map(nMarkerInfo)) ? TRUE : FALSE);
}

BOOL CGRDWnd::SetPrintJobs(CONST CByteArray &nPrintInfo)
{
	CGRDPrintJobs  pPrintJobs;

	return((pPrintJobs.Unmap(nPrintInfo)) ? SetPrintJobs(pPrintJobs) : FALSE);
}

BOOL CGRDWnd::GetPrintJobs(CByteArray &nPrintInfo) CONST
{
	CGRDPrintJobs  pPrintJobs;

	return((GetPrintJobs(pPrintJobs)) ? pPrintJobs.Map(nPrintInfo) : FALSE);
}

BOOL CGRDWnd::GetPrintProperties(CONST CGRDPrintJobInfo *pJobInfo, CGRDLayout &cLayout, UINT &nMode, CString &szTMUnit, CTimeTag &tTMUnit, UINT &nTMUnit, BOOL &bQuality, CStringArray &szColumns, CStringArray &szContents, CTMParameters &pValues, CUIntArray &nOOLColors, LOGFONT *pTitleFont, CPtrArray &pItemsFonts, CMetaFileDC &cMetaDC, CSize &sizeImage, UINT &nImageIndent) CONST
{
	WORD  wQuality;
	CDisplayLock  cLock(this);

	if (((nMode = GetMode()) == DISPLAY_MODE_REALTIME || nMode == DISPLAY_MODE_HISTORY) && GetUpdateInfo(szTMUnit, tTMUnit, nTMUnit, wQuality) && m_wndView.GetPrintProperties(cLayout, szColumns, szContents, pValues, nOOLColors, pTitleFont, pItemsFonts, cMetaDC, sizeImage, nImageIndent))
	{
		bQuality = ((wQuality & (TMUNIT_DATAQUALITY_GOOD | TMUNIT_SEQUENCEQUALITY_GOOD)) == (TMUNIT_DATAQUALITY_GOOD | TMUNIT_SEQUENCEQUALITY_GOOD)) ? TRUE : FALSE;
		return TRUE;
	}
	return FALSE;
}

BOOL CGRDWnd::StartPrintJob(CDC &cDC)
{
	DOCINFO  sJobInfo;
	CString  szJobTitle;
	CGRDLayout  cLayout;

	for (GetLayout(cLayout), sJobInfo.fwType = 0, sJobInfo.cbSize = sizeof(DOCINFO), sJobInfo.lpszDocName = (LPTSTR)EMPTYSTRING, sJobInfo.lpszOutput = (LPCTSTR)NULL, sJobInfo.lpszDatatype = (LPCTSTR)NULL, szJobTitle.Format(STRING(IDS_PRINTJOB_DEFAULTTITLE), (LPCTSTR)GetAppTitle(), (LPCTSTR)GetAccountSpacecraftName(), (LPCTSTR)GetPrintDocSubTitle(cLayout), STRING(IDS_DISPLAY_TITLE_GRD)); szJobTitle.GetLength() >= 0; )
	{
		sJobInfo.lpszDocName = (LPTSTR)(LPCTSTR)szJobTitle;
		break;
	}
	return((cDC.StartDoc(&sJobInfo) >= 0) ? TRUE : FALSE);
}

BOOL CGRDWnd::PrintJob(CDC &cDC, CONST CGRDPrintJobInfo *pJobInfo, LPCTSTR pszPrinterName, INT nFromPage, INT nToPage, CONST RECT &rtMargin, BOOL bMetric, CONST CGRDLayout &cLayout, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality, CONST CStringArray &szColumns, CONST CStringArray &szContents, CONST CTMParameters &pValues, CONST CUIntArray &nOOLColors, CONST LOGFONT *pTitleFont, CONST CPtrArray &pItemsFonts, CMetaFileDC &cMetaDC, CONST SIZE &sizeImage, UINT nImageIndent)
{
	INT  x;
	INT  y;
	INT  nPage;
	INT  nPages;
	INT  nLine;
	INT  nLines;
	INT  nColumn;
	INT  nColumns;
	INT  nFont;
	INT  nFonts;
	INT  nWidth;
	INT  nHeight[2];
	INT  nSpacing;
	INT  nOffset;
	INT  nBkMode;
	UINT  nScale;
	UINT  nStatus;
	BOOL  bOverlap;
	BOOL  bOutput;
	HPEN  hLinePen;
	HPEN  hOldPen;
	CPen  cLinePen;
	CPen  *pOldPen;
	CRgn  rgnArea;
	CRect  rArea;
	CRect  rCalc;
	CRect  rClip;
	CRect  rItem;
	CRect  rImage;
	CFont  *pOldFont;
	CFont  cFont[GRD_PRINTFONTS];
	CSize  sizeText[2];
	CSize  sizePlot;
	double  fScale;
	CString  szColumn;
	COLORREF  nColor;
	COLORREF  nOldColor;
	LOGBRUSH  sPenBrush;
	CTimeKey  tPrint;
	CPtrArray  pFonts;
	CUIntArray  nTabs;
	TEXTMETRIC  tmFont[2];
	HENHMETAFILE  hMetaFile;
	CStringArray  szColumnsText[2];
	CGRDLayoutParameter  *pParameter;

	for (nPage = nPages = 0, nOffset = 0, nScale = (pJobInfo->GetPrintScale(nScale)) ? nScale : 100, ZeroMemory(&tmFont[0], sizeof(TEXTMETRIC)), ZeroMemory(&tmFont[1], sizeof(TEXTMETRIC)); (!nPages || nPage <= nPages) && (nPages > 0 || (nPages = (CalcPrintDocRect(cDC, rtMargin, bMetric) && cDC.GetClipBox(rArea) != ERROR && rgnArea.CreateRectRgnIndirect(rArea) && CalcPrintDocTitleFont(cDC, rArea, cFont[GRD_PRINTFONT_TITLE]) && CalcPrintDocSubTitleFont(cDC, rArea, cFont[GRD_PRINTFONT_SUBTITLE]) && CalcPrintDocOperatingDetailsFont(cDC, rArea, cFont[GRD_PRINTFONT_OPERATINGDETAILS]) && CalcPrintDocOperatingModeFont(cDC, rArea, cFont[GRD_PRINTFONT_OPERATINGMODE]) && CalcPrintDocListItemsFonts(cDC, rArea, szColumns, szContents, sizeImage, nImageIndent, nScale, pTitleFont, pItemsFonts, cFont[GRD_PRINTFONT_LISTITEMSTITLE], pFonts) && CalcPrintDocNoticeFonts(cDC, rArea, cFont[GRD_PRINTFONT_NOTICE], cFont[GRD_PRINTFONT_LOGO]) && CalcPrintDocFooterFont(cDC, rArea, cFont[GRD_PRINTFONT_FOOTER]) && CalcPrintDocTitleWidth(cDC, szColumns, szContents, &cFont[GRD_PRINTFONT_LISTITEMSTITLE], pFonts, nTabs) == szColumns.GetSize()) ? nPages : -1) == 0); )
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
			pFonts.InsertAt(GRD_PRINTFONT_TITLE, &cFont[GRD_PRINTFONT_TITLE], 1);
			pFonts.InsertAt(GRD_PRINTFONT_SUBTITLE, &cFont[GRD_PRINTFONT_SUBTITLE], 1);
			pFonts.InsertAt(GRD_PRINTFONT_OPERATINGDETAILS, &cFont[GRD_PRINTFONT_OPERATINGDETAILS], 1);
			pFonts.InsertAt(GRD_PRINTFONT_OPERATINGMODE, &cFont[GRD_PRINTFONT_OPERATINGMODE], 1);
			pFonts.InsertAt(GRD_PRINTFONT_LISTITEMSTITLE, &cFont[GRD_PRINTFONT_LISTITEMSTITLE], 1);
			pFonts.InsertAt(GRD_PRINTFONT_FOOTER, &cFont[GRD_PRINTFONT_FOOTER], 1);
			pFonts.InsertAt(GRD_PRINTFONT_NOTICE, &cFont[GRD_PRINTFONT_NOTICE], 1);
			pFonts.InsertAt(GRD_PRINTFONT_LOGO, &cFont[GRD_PRINTFONT_LOGO], 1);
		}
		for (nLine = 0, nLines = (INT)szContents.GetSize(), nSpacing = max(tmFont[0].tmHeight / 16, 1), rCalc.SetRectEmpty(), rClip.SetRectEmpty(), bOverlap = FALSE, bOutput = TRUE; (nPages = (tmFont[0].tmHeight > 0) ? nPages : -1) >= 0 && nLine < nLines; nLine++, bOutput = TRUE)
		{
			for (nColumn = 0, nColumns = (INT)szColumns.GetSize(), ExtractPrintDocText(szContents.GetAt(nLine), szColumnsText[0]), nHeight[0] = nHeight[1] = 0; nPages >= 0 && nColumn < nColumns; nColumn++, nHeight[1] = 0)
			{
				if (rClip.Height() > 0)
				{
					if ((pOldFont = cDC.SelectObject((CFont *)pFonts.GetAt(GRD_PRINTFONTS + nColumn % (pFonts.GetSize() - GRD_PRINTFONTS)))))
					{
						GetPrintDocParameterAttributes(cLayout, szColumns, pValues, nOOLColors, nLine, nColumn, nStatus, nColor);
						nOldColor = cDC.SetTextColor((cDC.GetDeviceCaps(NUMCOLORS) > 2) ? nColor : cDC.GetTextColor());
						sizeText[0] = (nColumn < szColumnsText[0].GetSize()) ? cDC.GetTextExtent((szColumn = szColumnsText[0].GetAt(nColumn) + SPACE)) : cDC.GetTextExtent((szColumn = EMPTYSTRING) + SPACE);
						sizeText[1] = (nColumn < szColumnsText[0].GetSize()) ? cDC.GetTextExtent(szColumnsText[0].GetAt(nColumn)) : cDC.GetTextExtent(EMPTYSTRING);
						rCalc.SetRect(rCalc.left, (!nColumn) ? (rCalc.top + nSpacing) : rCalc.top, rCalc.right, (!nColumn) ? (rCalc.top + nSpacing + tmFont[0].tmHeight*((rClip.bottom - (rCalc.top + nSpacing)) / tmFont[0].tmHeight)) : (rCalc.top + tmFont[0].tmHeight*((rClip.bottom - rCalc.top) / tmFont[0].tmHeight)));
						rItem.SetRect((nColumn > 0) ? (rCalc.left + nOffset + nTabs.GetAt(nColumn - 1)) : (rCalc.left + nOffset), rCalc.top, rCalc.left + nOffset + nTabs.GetAt(nColumn), rCalc.top + sizeText[0].cy);
						if (nPages > 0 && (nFromPage <= 0 || nToPage <= 0 || nFromPage > nToPage || (nPage >= nFromPage  &&  nPage <= nToPage)))
						{
							cDC.DrawText(szColumn, CRect(rItem.left, rItem.top, rItem.right, rCalc.bottom), DT_LEFT | DT_NOPREFIX | DT_SINGLELINE);
							if (szColumns.GetAt(nColumn) == STRING(IDS_GRD_TITLEITEM_VALUE) && (pJobInfo->GetPrintMode() & GRD_PRINT_UNDERLINEOOL) && cDC.GetTextMetrics(&tmFont[1]))
							{
								if ((nStatus & TMPARAMETER_STATUS_SOFTLIMIT) || (nStatus & TMPARAMETER_STATUS_HARDLIMIT) || (nStatus & TMPARAMETER_STATUS_DELTALIMIT) || (nStatus & TMPARAMETER_STATUS_CONSISTENCYLIMIT))
								{
									if (cLinePen.CreatePen(PS_SOLID, tmFont[1].tmDescent / 3, cDC.GetTextColor()))
									{
										if ((pOldPen = cDC.SelectObject(&cLinePen)))
										{
											nBkMode = cDC.SetBkMode(TRANSPARENT);
											cDC.MoveTo((x = rItem.left), (y = rItem.bottom - max((2 * tmFont[1].tmDescent) / 3, 1)));
											cDC.LineTo(x + sizeText[1].cx, y);
											cDC.SelectObject(pOldPen);
											cDC.SetBkMode(nBkMode);
										}
										cLinePen.DeleteObject();
									}
								}
							}
							if (szColumns.GetAt(nColumn) == STRING(IDS_GRD_TITLEITEM_LINE))
							{
								if ((pParameter = cLayout.GetAt(nLine)))
								{
									sPenBrush.lbStyle = BS_SOLID;
									sPenBrush.lbHatch = (ULONG_PTR)NULL;
									sPenBrush.lbColor = (pParameter->GetColor() == GetSysColor(COLOR_WINDOW)) ? GetDatabase()->GetGRDIDColumnColor() : pParameter->GetColor();
									if ((hLinePen = ExtCreatePen(PS_GEOMETRIC | PS_ENDCAP_FLAT | ((pParameter->GetLineStyle() != GRDLAYOUTPARAMETER_LINESTYLE_DASHED  &&  pParameter->GetLineStyle() != GRDLAYOUTPARAMETER_LINESTYLE_DOTTED) ? PS_SOLID : 0) | ((pParameter->GetLineStyle() == GRDLAYOUTPARAMETER_LINESTYLE_DASHED) ? PS_DASH : 0) | ((pParameter->GetLineStyle() == GRDLAYOUTPARAMETER_LINESTYLE_DOTTED) ? PS_DOT : 0), (nWidth = (INT)((double)pParameter->GetLineWidth()*((double)cDC.GetDeviceCaps(HORZRES) / (double)GetSystemMetrics(SM_CXSCREEN))*((double)nScale / 100.0) + 1.0)), &sPenBrush, 0, (CONST DWORD *) NULL)))
									{
										if ((hOldPen = (HPEN)SelectObject(cDC.GetSafeHdc(), hLinePen)))
										{
											cDC.MoveTo(rItem.left, rItem.CenterPoint().y);
											cDC.LineTo(rItem.left + (3 * rItem.Width()) / 4, rItem.CenterPoint().y);
											DrawPrintDocLineSymbol(cDC, pParameter->GetLineSymbol(), nWidth, sPenBrush.lbColor, CPoint(rItem.left + (3 * rItem.Width()) / 16, rItem.CenterPoint().y));
											DrawPrintDocLineSymbol(cDC, pParameter->GetLineSymbol(), nWidth, sPenBrush.lbColor, CPoint(rItem.left + (9 * rItem.Width()) / 16, rItem.CenterPoint().y));
											SelectObject(cDC.GetSafeHdc(), hOldPen);
										}
										DeleteObject(hLinePen);
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
						if (cDC.SelectClipRgn(&rgnArea) != ERROR  &&  DrawPrintDocPage(cDC, pJobInfo, tPrint, pszPrinterName, rtMargin, bMetric, cLayout, nMode, pszTMUnit, tTMUnit, nTMUnit, bQuality, szColumns, nOOLColors, pFonts, nTabs, nOffset, nPages, (nPages > 0 && (nFromPage <= 0 || nToPage <= 0 || nFromPage > nToPage || (nPage >= nFromPage - 1 && nPage < nToPage))) ? (nPage + 1) : 0, rClip) && cDC.IntersectClipRect(rClip) != ERROR)
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
							if (DrawPrintDocPage(cDC, pJobInfo, tPrint, pszPrinterName, rtMargin, bMetric, cLayout, nMode, pszTMUnit, tTMUnit, nTMUnit, bQuality, szColumns, nOOLColors, pFonts, nTabs, nOffset, 1, 1, rClip))
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
						fScale = (sizeImage.cx > 0 && sizeImage.cy > 0) ? (((double)rCalc.Width() / (double)sizeImage.cx <= (double)rCalc.Height() / (double)sizeImage.cy) ? ((double)rCalc.Width() / (double)sizeImage.cx) : ((double)rCalc.Height() / (double)sizeImage.cy)) : 0.0;
						fScale = fScale*((double)nScale / 100.0);
						sizePlot.cx = (INT)(fScale*sizeImage.cx);
						sizePlot.cy = (INT)(fScale*sizeImage.cy);
						nOffset = (rCalc.Width() - sizePlot.cx) / 2 + (INT)(fScale*nImageIndent);
						nPages = ((double)rCalc.Width() / (double)sizeImage.cx > (double)rCalc.Height() / (double)sizeImage.cy  &&  sizePlot.cx < (3 * rCalc.Width()) / 4) ? (nPage + 1) : nPage;
						nPage = 0;
						continue;
					}
					nPages = nPage = 0;
				}
				if (nPages > 0)
				{
					if ((nFromPage <= 0 || nToPage <= 0 || nFromPage > nToPage || nPage < nToPage) && nPage == nPages - 1)
					{
						if (((nFromPage > 0 && nToPage > 0 && nFromPage <= nToPage  &&  nPage < nFromPage) || cDC.EndPage() >= 0) && cDC.StartPage() >= 0)
						{
							if (cDC.SelectClipRgn(&rgnArea) != ERROR  &&  DrawPrintDocPage(cDC, pJobInfo, tPrint, pszPrinterName, rtMargin, bMetric, cLayout, nMode, pszTMUnit, tTMUnit, nTMUnit, bQuality, szColumnsText[1], nOOLColors, pFonts, nTabs, nOffset, nPages, nPage + 1, rClip) && cDC.IntersectClipRect(rClip) != ERROR)
							{
								fScale = (sizeImage.cx > 0 && sizeImage.cy > 0) ? (((double)rClip.Width() / (double)sizeImage.cx <= (double)rClip.Height() / (double)sizeImage.cy) ? ((double)rClip.Width() / (double)sizeImage.cx) : ((double)rClip.Height() / (double)sizeImage.cy)) : 0.0;
								fScale = fScale*((double)nScale / 100.0);
								sizePlot.cx = (INT)(fScale*sizeImage.cx);
								sizePlot.cy = (INT)(fScale*sizeImage.cy);
								rImage.SetRect(rClip.left + (rClip.Width() - sizePlot.cx) / 2, rClip.top, 0, 0);
								rImage.right = rImage.left + sizePlot.cx;
								rImage.bottom = rImage.top + sizePlot.cy;
								if ((hMetaFile = cMetaDC.CloseEnhanced()))
								{
									cDC.PlayMetaFile(hMetaFile, rImage);
									DeleteEnhMetaFile(hMetaFile);
									nPages = nPage = 1;
									break;
								}
							}
						}
					}
					if ((nFromPage <= 0 || nToPage <= 0 || nFromPage > nToPage || nPage <= nToPage) && nPage == nPages)
					{
						fScale = (sizeImage.cx > 0 && sizeImage.cy > 0) ? (((double)rCalc.Width() / (double)sizeImage.cx <= (double)rCalc.Height() / (double)sizeImage.cy) ? ((double)rCalc.Width() / (double)sizeImage.cx) : ((double)rCalc.Height() / (double)sizeImage.cy)) : 0.0;
						fScale = fScale*((double)nScale / 100.0);
						sizePlot.cx = (INT)(fScale*sizeImage.cx);
						sizePlot.cy = (INT)(fScale*sizeImage.cy);
						rImage.SetRect(rCalc.left + (rCalc.Width() - sizePlot.cx) / 2, rCalc.top, 0, 0);
						rImage.right = rImage.left + sizePlot.cx;
						rImage.bottom = rImage.top + sizePlot.cy;
						if ((hMetaFile = cMetaDC.CloseEnhanced()))
						{
							cDC.PlayMetaFile(hMetaFile, rImage);
							DeleteEnhMetaFile(hMetaFile);
							nPages = nPage = 1;
							break;
						}
					}
					if (nFromPage > 0 && nToPage > 0 && nFromPage <= nToPage  &&  nPage < nToPage)
					{
						nPages = 0;
						nPage = 0;
					}
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

BOOL CGRDWnd::EndPrintJob(CDC &cDC)
{
	return((cDC.EndDoc() >= 0) ? TRUE : FALSE);
}

BOOL CGRDWnd::DrawPrintDocPage(CDC &cDC, CONST CGRDPrintJobInfo *pJobInfo, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, CONST RECT &rtMargin, BOOL bMetric, CONST CGRDLayout &cLayout, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality, CONST CStringArray &szColumns, CONST CUIntArray &nOOLColors, CONST CPtrArray &pFonts, CONST CUIntArray &nTabs, INT nTabOffset, INT nPages, INT nPage, LPRECT prClip)
{
	return((CalcPrintDocRect(cDC, rtMargin, bMetric) && cDC.GetClipBox(prClip) != ERROR  &&  DrawPrintDocTitle(cDC, prClip, GetPrintDocTitle(), (CFont *)pFonts.GetAt(GRD_PRINTFONT_TITLE), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocSubTitle(cDC, prClip, GetPrintDocSubTitle(cLayout), (CFont *)pFonts.GetAt(GRD_PRINTFONT_SUBTITLE), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocOperatingDetails(cDC, prClip, GetPrintDocOperatingDetails(pJobInfo, nMode, pszTMUnit, tTMUnit, nTMUnit, bQuality), (CFont *)pFonts.GetAt(GRD_PRINTFONT_OPERATINGDETAILS), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocOperatingMode(cDC, prClip, GetPrintDocOperatingMode(pJobInfo, nOOLColors), nOOLColors, (CFont *)pFonts.GetAt(GRD_PRINTFONT_OPERATINGMODE), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocListItemsTitle(cDC, prClip, szColumns, (CFont *)pFonts.GetAt(GRD_PRINTFONT_LISTITEMSTITLE), nTabs, nTabOffset, (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocNotice(cDC, prClip, GetPrintDocNotice(), (CFont *)pFonts.GetAt(GRD_PRINTFONT_NOTICE), (CFont *)pFonts.GetAt(GRD_PRINTFONT_LOGO), (nPage <= 0) ? TRUE : FALSE) && DrawPrintDocFooter(cDC, prClip, GetPrintDocFooter(tTime, pszPrinterName, nPages, nPage), (CFont *)pFonts.GetAt(GRD_PRINTFONT_FOOTER), (nPage <= 0) ? TRUE : FALSE)) ? TRUE : FALSE);
}

BOOL CGRDWnd::DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc)
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

BOOL CGRDWnd::DrawPrintDocSubTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, BOOL bCalc)
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

BOOL CGRDWnd::DrawPrintDocOperatingDetails(CDC &cDC, LPRECT prClip, LPCTSTR pszComments, CFont *pFont, BOOL bCalc)
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

BOOL CGRDWnd::DrawPrintDocOperatingMode(CDC &cDC, LPRECT prClip, LPCTSTR pszMode, CONST CUIntArray &nOOLColors, CFont *pFont, BOOL bCalc)
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
		szToken = szToken.Left((szToken = STRING(IDS_GRD_PRINTDOCUMENT_OOLLEGEND)).Find(SPACE));
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

BOOL CGRDWnd::DrawPrintDocListItemsTitle(CDC &cDC, LPRECT prClip, CONST CStringArray &szColumns, CFont *pFont, CONST CUIntArray &nTabs, INT nTabOffset, BOOL bCalc)
{
	CSize  rCalc;
	CFont  *pOldFont;
	CString  szItems;

	if ((pOldFont = cDC.SelectObject(pFont)))
	{
		szItems = GetPrintDocListItemsTitle(szColumns);
		rCalc = (!bCalc) ? cDC.TabbedTextOut(prClip->left + nTabOffset, prClip->top, szItems, (INT)nTabs.GetSize(), (LPINT)nTabs.GetData(), prClip->left + nTabOffset) : CSize(nTabs.GetAt(nTabs.GetSize() + nTabOffset - 1), cDC.GetTextExtent(szItems, szItems.GetLength()).cy);
		prClip->top += rCalc.cy;
		cDC.SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

VOID CGRDWnd::DrawPrintDocLineSymbol(CDC &cDC, INT nSymbol, INT nWidth, COLORREF nColor, CONST POINT &pt)
{
	CPen  *pOldPen;
	CPen  cSymbolPen;
	CBrush  *pOldBrush;
	CBrush  cSymbolBrush;

	switch (nSymbol)
	{
	case GRDLAYOUTPARAMETER_LINESYMBOL_STROKE:
	{ if (cSymbolPen.CreatePen(PS_SOLID, nWidth, nColor))
	{
		if ((pOldPen = cDC.SelectObject(&cSymbolPen)))
		{
			cDC.MoveTo(pt.x, pt.y - (3 * nWidth) / 2);
			cDC.LineTo(pt.x, pt.y + (3 * nWidth) / 2 + nWidth % 2);
			cDC.SelectObject(pOldPen);
		}
		cSymbolPen.DeleteObject();
	}
	break;
	}
	case GRDLAYOUTPARAMETER_LINESYMBOL_CROSS:
	{ if (cSymbolPen.CreatePen(PS_SOLID, nWidth, nColor))
	{
		if ((pOldPen = cDC.SelectObject(&cSymbolPen)))
		{
			cDC.MoveTo(pt.x - (3 * nWidth) / 2, pt.y - (3 * nWidth) / 2);
			cDC.LineTo(pt.x, pt.y);
			cDC.MoveTo(pt.x + (3 * nWidth) / 2 - (nWidth + 1) % 2, pt.y - (3 * nWidth) / 2);
			cDC.LineTo(pt.x - (nWidth + 1) % 2, pt.y);
			cDC.MoveTo(pt.x - (3 * nWidth) / 2, pt.y + (3 * nWidth) / 2);
			cDC.LineTo(pt.x, pt.y - (nWidth + 1) % 2);
			cDC.MoveTo(pt.x + (3 * nWidth) / 2 - (nWidth + 1) % 2, pt.y + (3 * nWidth) / 2);
			cDC.LineTo(pt.x - (nWidth + 1) % 2, pt.y - (nWidth + 1) % 2);
			cDC.SelectObject(pOldPen);
		}
		cSymbolPen.DeleteObject();
	}
	break;
	}
	case GRDLAYOUTPARAMETER_LINESYMBOL_POINT:
	{ if (cSymbolPen.CreatePen(PS_SOLID, 0, nColor))
	{
		if (cSymbolBrush.CreateSolidBrush(nColor))
		{
			if ((pOldPen = cDC.SelectObject(&cSymbolPen)))
			{
				if ((pOldBrush = cDC.SelectObject(&cSymbolBrush)))
				{
					cDC.Ellipse(pt.x - 2 * nWidth, pt.y - 2 * nWidth, pt.x + 2 * nWidth + 1, pt.y + 2 * nWidth + nWidth % 2);
					cDC.SelectObject(pOldBrush);
				}
				cDC.SelectObject(pOldPen);
			}
			cSymbolBrush.DeleteObject();
		}
		cSymbolPen.DeleteObject();
	}
	break;
	}
	case GRDLAYOUTPARAMETER_LINESYMBOL_SQUARE:
	{ if (cSymbolPen.CreatePen(PS_SOLID, 0, nColor))
	{
		if (cSymbolBrush.CreateSolidBrush(nColor))
		{
			if ((pOldPen = cDC.SelectObject(&cSymbolPen)))
			{
				if ((pOldBrush = cDC.SelectObject(&cSymbolBrush)))
				{
					cDC.Rectangle(pt.x - (2 * nWidth - 1), pt.y - (2 * nWidth - 1), pt.x + 2 * nWidth, pt.y + (2 * nWidth - 1) + nWidth % 2);
					cDC.SelectObject(pOldBrush);
				}
				cDC.SelectObject(pOldPen);
			}
			cSymbolBrush.DeleteObject();
		}
		cSymbolPen.DeleteObject();
	}
	break;
	}
	}
}

BOOL CGRDWnd::DrawPrintDocNotice(CDC &cDC, LPRECT prClip, LPCTSTR pszNotice, CFont *pFont, CFont *pLogoFont, BOOL bCalc)
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

BOOL CGRDWnd::DrawPrintDocFooter(CDC &cDC, LPRECT prClip, LPCTSTR pszFooter, CFont *pFont, BOOL bCalc)
{
	CRect  rCalc;
	CFont  *pOldFont;

	if ((pOldFont = cDC.SelectObject(pFont)))
	{
		cDC.DrawText(pszFooter, (rCalc = CRect(0, 0, prClip->right - prClip->left, 0)), DT_CALCRECT | DT_LEFT | DT_NOPREFIX | DT_SINGLELINE);
		cDC.DrawText(pszFooter, (!bCalc) ? prClip : CRect(0, 0, 0, 0), DT_LEFT | DT_BOTTOM | DT_NOPREFIX | DT_SINGLELINE);
		prClip->bottom -= rCalc.Height();
		cDC.SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

CString CGRDWnd::GetPrintDocTitle() CONST
{
	CString  szTitle;

	szTitle.Format(STRING(IDS_GRD_PRINTDOCUMENT_TITLE), (LPCTSTR)GetAccountSpacecraftName());
	return szTitle;
}

CString CGRDWnd::GetPrintDocSubTitle(CONST CGRDLayout &cLayout) CONST
{
	return cLayout.GetTitle();
}

CString CGRDWnd::GetPrintDocOperatingDetails(CONST CGRDPrintJobInfo *pJobInfo, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality) CONST
{
	CString  szMode;
	CString  szUpdate;

	szMode = (nMode == DISPLAY_MODE_REALTIME) ? STRING(IDS_DISPLAY_MODE_REALTIME) : STRING(IDS_DISPLAY_MODE_HISTORY);
	szUpdate.Format((!lstrlen(pszTMUnit)) ? ((tTMUnit > 0) ? STRING(IDS_GRD_PRINTDOCUMENT_FULLUPDATECOMMENT) : STRING(IDS_GRD_PRINTDOCUMENT_NODATACOMMENT)) : ((nTMUnit == (UINT)-1) ? STRING(IDS_GRD_PRINTDOCUMENT_INITUPDATECOMMENT) : STRING(IDS_GRD_PRINTDOCUMENT_UPDATECOMMENT)), (LPCTSTR)tTMUnit.FormatGmt(), pszTMUnit, nTMUnit, (bQuality) ? STRING(IDS_GRD_PRINTDOCUMENT_QUALITYGOOD) : STRING(IDS_GRD_PRINTDOCUMENT_QUALITYBAD));
	return((!pJobInfo->GetComments().IsEmpty()) ? (szUpdate + EOL + szMode + EOL + pJobInfo->GetComments()) : (szUpdate + EOL + szMode));
}

CString CGRDWnd::GetPrintDocOperatingMode(CONST CGRDPrintJobInfo *pJobInfo, CONST CUIntArray &nOOLColors) CONST
{
	UINT  nMode;
	UINT  nFlags;
	UINT  nColor;
	UINT  nStopCount;
	CString  szLegend;
	CString  szEvent;
	CString  szInfo;
	CTimeKey  tTime;
	CTimeKey  tLastTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CTimeSpan  tDailyTime;
	CStringArray  szOOLColors;

	if ((nFlags = pJobInfo->GetPrintFlags()) & GRD_PRINT_ATTIME)
	{
		if (pJobInfo->GetPrintAtTime(tTime))
		{
			szInfo.Format(STRING(IDS_GRD_PRINTDOCUMENT_PRINTATTIME), (LPCTSTR)tTime.FormatGmt());
			szInfo += EOL;
		}
		if ((pJobInfo->GetPrintAtTime(tTime, tInterval) || pJobInfo->GetPrintAtTime(tTime, tInterval, nStopCount) || pJobInfo->GetPrintAtTime(tTime, tInterval, tStopTime)) && pJobInfo->GetPrintLastTime(tLastTime))
		{
			szInfo.Format(STRING(IDS_GRD_PRINTDOCUMENT_PRINTATTIME), (LPCTSTR)CTimeKey(tTime.GetTime() + ((tLastTime.GetTime() - tTime.GetTime()) / tInterval.GetTotalSeconds())*tInterval.GetTotalSeconds()).FormatGmt());
			szInfo += EOL;
		}
	}
	if (nFlags & GRD_PRINT_ATDAILYTIME)
	{
		if (pJobInfo->GetPrintAtDailyTime(tDailyTime) || pJobInfo->GetPrintAtDailyTime(tDailyTime, nStopCount) || pJobInfo->GetPrintAtDailyTime(tDailyTime, tStopTime))
		{
			szInfo.Format(STRING(IDS_GRD_PRINTDOCUMENT_PRINTATDAILYTIME), (LPCTSTR)CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + tDailyTime.GetTotalSeconds()).FormatGmt(STRING(IDS_TIMEKEY_TIMEFORMAT)));
			szInfo += EOL;
		}
	}
	if (nFlags & GRD_PRINT_ATEVENT)
	{
		if (pJobInfo->GetPrintAtEvent(szEvent))
		{
			szInfo.Format(STRING(IDS_GRD_PRINTDOCUMENT_PRINTATEVENT), (LPCTSTR)szEvent);
			szInfo += EOL;
		}
	}
	if (nFlags & GRD_PRINT_ATEXPIRATION)
	{
		szInfo = STRING(IDS_GRD_PRINTDOCUMENT_PRINTATEXPIRATION);
		szInfo += EOL;
	}
	if (!nFlags)
	{
		szInfo = STRING(IDS_GRD_PRINTDOCUMENT_DEFAULTTIME);
		szInfo += EOL;
	}
	if ((nMode = pJobInfo->GetPrintMode()) & GRD_PRINT_COLORLEGEND)
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
		szLegend.Format(STRING(IDS_GRD_PRINTDOCUMENT_OOLLEGEND), (LPCTSTR)szOOLColors.GetAt(GRD_OOLCOLOR_NOLIMIT), (LPCTSTR)szOOLColors.GetAt(GRD_OOLCOLOR_SOFTLIMIT), (LPCTSTR)szOOLColors.GetAt(GRD_OOLCOLOR_HARDLIMIT), (LPCTSTR)szOOLColors.GetAt(GRD_OOLCOLOR_DELTALIMIT), (LPCTSTR)szOOLColors.GetAt(GRD_OOLCOLOR_CONSISTENCYLIMIT));
		szInfo += szLegend + EOL;
	}
	return szInfo;
}

CString CGRDWnd::GetPrintDocListItemsTitle(CONST CStringArray &szColumns) CONST
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

CString CGRDWnd::GetPrintDocNotice() CONST
{
	CVersionInfo  cVersionInfo;

	return cVersionInfo.QueryComments();
}

CString CGRDWnd::GetPrintDocFooter(CONST CTimeKey &tTime, LPCTSTR pszPrinterName, INT nPages, INT nPage) CONST
{
	CString  szFooter;

	szFooter.Format(STRING(IDS_GRD_PRINTDOCUMENT_FOOTER), (LPCTSTR)tTime.Format(IDS_TIMEKEY_DATEFORMAT), (LPCTSTR)tTime.Format(IDS_TIMEKEY_TIMEFORMAT), pszPrinterName, nPage, nPages);
	return szFooter;
}

BOOL CGRDWnd::GetPrintDocParameterAttributes(CONST CGRDLayout &cLayout, CONST CStringArray &szColumns, CONST CTMParameters &pValues, CONST CUIntArray &nOOLColors, INT nRow, INT nColumn, UINT &nStatus, COLORREF &nColor) CONST
{
	ULONGLONG  nValue;
	CTMParameter  *pTMParameter;
	CGRDLayoutParameter  *pParameter;

	for (nColor = GetSysColor(COLOR_WINDOW), nStatus = TMPARAMETER_STATUS_NONE; (pParameter = cLayout.GetAt(nRow)); )
	{
		if ((pTMParameter = pValues.GetAt(pValues.Find(pParameter->GetName()))) && pTMParameter->GetRawValue((pParameter->GetOccurrence() < 0) ? (pTMParameter->GetValueCount() - 1) : pParameter->GetOccurrence(), nValue, nStatus))
		{
			if (szColumns.GetAt(nColumn) == STRING(IDS_GRD_TITLEITEM_VALUE))
			{
				if (nStatus & TMPARAMETER_STATUS_NOLIMIT)
				{
					nColor = nOOLColors.GetAt(GRD_OOLCOLOR_NOLIMIT);
					return TRUE;
				}
				if (nStatus & TMPARAMETER_STATUS_SOFTLIMIT)
				{
					nColor = nOOLColors.GetAt(GRD_OOLCOLOR_SOFTLIMIT);
					return TRUE;
				}
				if (nStatus & TMPARAMETER_STATUS_HARDLIMIT)
				{
					nColor = nOOLColors.GetAt(GRD_OOLCOLOR_HARDLIMIT);
					return TRUE;
				}
				if (nStatus & TMPARAMETER_STATUS_DELTALIMIT)
				{
					nColor = nOOLColors.GetAt(GRD_OOLCOLOR_DELTALIMIT);
					return TRUE;
				}
				if (nStatus & TMPARAMETER_STATUS_CONSISTENCYLIMIT)
				{
					nColor = nOOLColors.GetAt(GRD_OOLCOLOR_CONSISTENCYLIMIT);
					break;
				}
			}
		}
		if (pParameter->GetColor() == GetSysColor(COLOR_WINDOW))
		{
			if (szColumns.GetAt(nColumn) == STRING(IDS_GRD_TITLEITEM_ID))
			{
				nColor = GetDatabase()->GetGRDIDColumnColor();
				return TRUE;
			}
			if (szColumns.GetAt(nColumn) == STRING(IDS_GRD_TITLEITEM_DESCRIPTION))
			{
				nColor = GetDatabase()->GetGRDDescriptionColumnColor();
				return TRUE;
			}
			if (szColumns.GetAt(nColumn) == STRING(IDS_GRD_TITLEITEM_UNIT))
			{
				nColor = GetDatabase()->GetGRDUnitColumnColor();
				return TRUE;
			}
			if (szColumns.GetAt(nColumn) == STRING(IDS_GRD_TITLEITEM_RANGE))
			{
				nColor = GetDatabase()->GetGRDRangeColumnColor();
				return TRUE;
			}
			if (szColumns.GetAt(nColumn) == STRING(IDS_GRD_TITLEITEM_LINE))
			{
				nColor = GetSysColor(COLOR_WINDOW);
				return TRUE;
			}
			if (szColumns.GetAt(nColumn) == STRING(IDS_GRD_TITLEITEM_CHANGETMUNIT))
			{
				nColor = GetDatabase()->GetGRDChangeTMUnitColumnColor();
				return TRUE;
			}
			if (szColumns.GetAt(nColumn) == STRING(IDS_GRD_TITLEITEM_CHANGETIME))
			{
				nColor = GetDatabase()->GetGRDChangeTimeColumnColor();
				return TRUE;
			}
			if (szColumns.GetAt(nColumn) == STRING(IDS_GRD_TITLEITEM_UPDATETMUNIT))
			{
				nColor = GetDatabase()->GetGRDUpdateTMUnitColumnColor();
				return TRUE;
			}
			if (szColumns.GetAt(nColumn) == STRING(IDS_GRD_TITLEITEM_UPDATETIME))
			{
				nColor = GetDatabase()->GetGRDUpdateTimeColumnColor();
				return TRUE;
			}
		}
		nColor = pParameter->GetColor();
		return TRUE;
	}
	return FALSE;
}

INT CGRDWnd::ExtractPrintDocText(LPCTSTR pszText, CStringArray &szColumnsText) CONST
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

BOOL CGRDWnd::CalcPrintDocTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 48, (INT)((-5.3*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CGRDWnd::CalcPrintDocSubTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 64, (INT)((-4.0*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CGRDWnd::CalcPrintDocOperatingDetailsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 76, (INT)((-3.3*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CGRDWnd::CalcPrintDocOperatingModeFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 76, (INT)((-3.3*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CGRDWnd::CalcPrintDocListItemsFonts(CDC &cDC, CONST RECT &rArea, CONST CStringArray &szColumns, CONST CStringArray &szContents, CONST SIZE &sizeImage, INT nImageIndent, INT nScale, CONST LOGFONT *pTitleFont, CONST CPtrArray &pItemsFonts, CFont &cTitleFont, CPtrArray &cItemsFonts) CONST
{
	INT  nFont;
	INT  nFonts;
	INT  nWidth;
	INT  nHeight;
	CFont  cFont;
	CFont  *pFont;
	LOGFONT  lfFont;
	CPtrArray  pFonts;
	CUIntArray  nTabs;

	for (nHeight = max(-(rArea.right - rArea.left) / 64, (INT)((-4.0*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))); nHeight < 0; nHeight++)
	{
		if (cFont.CreateFont(nHeight, 0, pTitleFont->lfEscapement, pTitleFont->lfOrientation, FW_BOLD, pTitleFont->lfItalic, pTitleFont->lfUnderline, pTitleFont->lfStrikeOut, pTitleFont->lfCharSet, pTitleFont->lfOutPrecision, pTitleFont->lfClipPrecision, pTitleFont->lfQuality, pTitleFont->lfPitchAndFamily, pTitleFont->lfFaceName))
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
				if (CalcPrintDocTitleWidth(cDC, szColumns, szContents, &cFont, pFonts, nTabs) > 0)
				{
					if ((nWidth = nTabs.GetAt(nTabs.GetSize() - 1)) >= rArea.right - rArea.left)
					{
						for (nHeight = (nHeight*(rArea.right - rArea.left)) / nWidth - 1; pFonts.GetSize() > 0; )
						{
							if ((pFont = (CFont *)pFonts.GetAt(pFonts.GetUpperBound()))) delete pFont;
							pFonts.RemoveAt(pFonts.GetUpperBound());
						}
						cFont.DeleteObject();
						continue;
					}
					cTitleFont.Attach(cFont.Detach());
					cItemsFonts.Copy(pFonts);
					break;
				}
			}
			while (pFonts.GetSize() > 0)
			{
				if ((pFont = (CFont *)pFonts.GetAt(pFonts.GetUpperBound()))) delete pFont;
				pFonts.RemoveAt(pFonts.GetUpperBound());
			}
			cFont.DeleteObject();
		}
	}
	return((cTitleFont.GetSafeHandle() && cItemsFonts.GetSize() == pItemsFonts.GetSize()) ? TRUE : FALSE);
}

BOOL CGRDWnd::CalcPrintDocNoticeFonts(CDC &cDC, CONST RECT &rArea, CFont &cFont, CFont &cLogoFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 96, (INT)((-2.6*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL) && cLogoFont.CreateFont(max(-(rArea.right - rArea.left) / 96, (INT)((-2.6*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, STRING(IDS_FONTFACE_COMPANYLOGO));
}

BOOL CGRDWnd::CalcPrintDocFooterFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 80, (INT)((-3.0*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

INT CGRDWnd::CalcPrintDocTitleWidth(CDC &cDC, LPCTSTR pszColumn, CFont *pTitleFont) CONST
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
INT CGRDWnd::CalcPrintDocTitleWidth(CDC &cDC, CONST CStringArray &szColumns, CONST CStringArray &szContents, CFont *pTitleFont, CONST CPtrArray &pItemsFonts, CUIntArray &nTabs) CONST
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
	for (nColumn = 0, nColumns = (INT)pItemsFonts.GetSize(); nColumn < nColumns; nColumn++)
	{
		if ((pOldFont = cDC.SelectObject((CFont *)pItemsFonts.GetAt(nColumn))) != (CFont *)NULL)
		{
			if (cDC.GetTextMetrics(&tmFont)) nIndent = max(tmFont.tmAveCharWidth, nIndent);
			cDC.SelectObject(pOldFont);
		}
	}
	for (nColumn = 0, nColumns = (INT)szColumns.GetSize(), szLines.Copy(szContents); nColumn < nColumns; nColumn++)
	{
		if (szColumns.GetAt(nColumn) == STRING(IDS_GRD_TITLEITEM_ID))
		{
			nWidth[0] = CalcPrintDocTitleWidth(cDC, szColumns.GetAt(nColumn), pTitleFont);
			nWidth[1] = CalcPrintDocColumnWidth(cDC, szLines, (CFont *)pItemsFonts.GetAt(nColumn%pItemsFonts.GetSize()));
			if (nTabs.GetSize() > 0) nTabs.SetAt(nTabs.GetUpperBound(), nTabs.GetAt(nTabs.GetUpperBound()) + 6 * nIndent);
			nTabs.Add((nTabs.GetSize() > 0) ? (2 * nIndent + nTabs.GetAt(nTabs.GetSize() - 1) + max(nWidth[0], nWidth[1])) : (2 * nIndent + max(nWidth[0], nWidth[1])));
		}
		if (szColumns.GetAt(nColumn) == STRING(IDS_GRD_TITLEITEM_DESCRIPTION))
		{
			nWidth[0] = CalcPrintDocTitleWidth(cDC, szColumns.GetAt(nColumn), pTitleFont);
			nWidth[1] = CalcPrintDocColumnWidth(cDC, szLines, (CFont *)pItemsFonts.GetAt(nColumn%pItemsFonts.GetSize()));
			nTabs.Add((nTabs.GetSize() > 0) ? (6 * nIndent + nTabs.GetAt(nTabs.GetSize() - 1) + max(nWidth[0], nWidth[1])) : (6 * nIndent + max(nWidth[0], nWidth[1])));
		}
		if (szColumns.GetAt(nColumn) == STRING(IDS_GRD_TITLEITEM_VALUE))
		{
			nWidth[0] = CalcPrintDocTitleWidth(cDC, szColumns.GetAt(nColumn), pTitleFont);
			nWidth[1] = CalcPrintDocColumnWidth(cDC, szLines, (CFont *)pItemsFonts.GetAt(nColumn%pItemsFonts.GetSize()));
			nTabs.Add((nTabs.GetSize() > 0) ? (2 * nIndent + nTabs.GetAt(nTabs.GetSize() - 1) + max(nWidth[0], nWidth[1])) : (2 * nIndent + max(nWidth[0], nWidth[1])));
		}
		if (szColumns.GetAt(nColumn) == STRING(IDS_GRD_TITLEITEM_UNIT))
		{
			nWidth[0] = CalcPrintDocTitleWidth(cDC, szColumns.GetAt(nColumn), pTitleFont);
			nWidth[1] = CalcPrintDocColumnWidth(cDC, szLines, (CFont *)pItemsFonts.GetAt(nColumn%pItemsFonts.GetSize()));
			nTabs.Add((nTabs.GetSize() > 0) ? (6 * nIndent + nTabs.GetAt(nTabs.GetSize() - 1) + max(nWidth[0], nWidth[1])) : (6 * nIndent + max(nWidth[0], nWidth[1])));
		}
		if (szColumns.GetAt(nColumn) == STRING(IDS_GRD_TITLEITEM_RANGE))
		{
			nWidth[0] = CalcPrintDocTitleWidth(cDC, szColumns.GetAt(nColumn), pTitleFont);
			nWidth[1] = CalcPrintDocColumnWidth(cDC, szLines, (CFont *)pItemsFonts.GetAt(nColumn%pItemsFonts.GetSize()));
			nTabs.Add((nTabs.GetSize() > 0) ? (6 * nIndent + nTabs.GetAt(nTabs.GetSize() - 1) + max(nWidth[0], nWidth[1])) : (6 * nIndent + max(nWidth[0], nWidth[1])));
		}
		if (szColumns.GetAt(nColumn) == STRING(IDS_GRD_TITLEITEM_LINE))
		{
			nWidth[0] = CalcPrintDocTitleWidth(cDC, szColumns.GetAt(nColumn), pTitleFont);
			nWidth[1] = CalcPrintDocColumnWidth(cDC, szLines, (CFont *)pItemsFonts.GetAt(nColumn%pItemsFonts.GetSize()));
			nTabs.Add((nTabs.GetSize() > 0) ? (2 * nIndent + nTabs.GetAt(nTabs.GetSize() - 1) + (nWidth[1] = max(4 * nWidth[0], nWidth[1]))) : (2 * nIndent + (nWidth[1] = max(4 * nWidth[0], nWidth[1]))));
		}
		if (szColumns.GetAt(nColumn) == STRING(IDS_GRD_TITLEITEM_CHANGETMUNIT))
		{
			nWidth[0] = CalcPrintDocTitleWidth(cDC, szColumns.GetAt(nColumn), pTitleFont);
			nWidth[1] = CalcPrintDocColumnWidth(cDC, szLines, (CFont *)pItemsFonts.GetAt(nColumn%pItemsFonts.GetSize()));
			nTabs.Add((nTabs.GetSize() > 0) ? (2 * nIndent + nTabs.GetAt(nTabs.GetSize() - 1) + max(nWidth[0], nWidth[1])) : (2 * nIndent + max(nWidth[0], nWidth[1])));
		}
		if (szColumns.GetAt(nColumn) == STRING(IDS_GRD_TITLEITEM_CHANGETIME))
		{
			nWidth[0] = CalcPrintDocTitleWidth(cDC, szColumns.GetAt(nColumn), pTitleFont);
			nWidth[1] = CalcPrintDocColumnWidth(cDC, szLines, (CFont *)pItemsFonts.GetAt(nColumn%pItemsFonts.GetSize()));
			nTabs.Add((nTabs.GetSize() > 0) ? (2 * nIndent + nTabs.GetAt(nTabs.GetSize() - 1) + max(nWidth[0], nWidth[1])) : (2 * nIndent + max(nWidth[0], nWidth[1])));
		}
		if (szColumns.GetAt(nColumn) == STRING(IDS_GRD_TITLEITEM_UPDATETMUNIT))
		{
			nWidth[0] = CalcPrintDocTitleWidth(cDC, szColumns.GetAt(nColumn), pTitleFont);
			nWidth[1] = CalcPrintDocColumnWidth(cDC, szLines, (CFont *)pItemsFonts.GetAt(nColumn%pItemsFonts.GetSize()));
			nTabs.Add((nTabs.GetSize() > 0) ? (2 * nIndent + nTabs.GetAt(nTabs.GetSize() - 1) + max(nWidth[0], nWidth[1])) : (2 * nIndent + max(nWidth[0], nWidth[1])));
		}
		if (szColumns.GetAt(nColumn) == STRING(IDS_GRD_TITLEITEM_UPDATETIME))
		{
			nWidth[0] = CalcPrintDocTitleWidth(cDC, szColumns.GetAt(nColumn), pTitleFont);
			nWidth[1] = CalcPrintDocColumnWidth(cDC, szLines, (CFont *)pItemsFonts.GetAt(nColumn%pItemsFonts.GetSize()));
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

INT CGRDWnd::CalcPrintDocColumnWidth(CDC &cDC, CStringArray &szContents, CFont *pItemsFont) CONST
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

BOOL CGRDWnd::CalcPrintDocRect(CDC &cDC, CONST RECT &rtMargin, BOOL bMetric) CONST
{
	CRect  rClip;

	rClip.SetRect(0, 0, cDC.GetDeviceCaps(HORZRES), cDC.GetDeviceCaps(VERTRES));
	rClip.DeflateRect((bMetric) ? (rtMargin.left*cDC.GetDeviceCaps(HORZRES)) / (100 * cDC.GetDeviceCaps(HORZSIZE)) : (rtMargin.left*cDC.GetDeviceCaps(LOGPIXELSX)) / 1000, (bMetric) ? (rtMargin.top*cDC.GetDeviceCaps(VERTRES)) / (100 * cDC.GetDeviceCaps(VERTSIZE)) : (rtMargin.top*cDC.GetDeviceCaps(LOGPIXELSY)) / 1000, (bMetric) ? (rtMargin.right*cDC.GetDeviceCaps(HORZRES)) / (100 * cDC.GetDeviceCaps(HORZSIZE)) : (rtMargin.right*cDC.GetDeviceCaps(LOGPIXELSX)) / 1000, (bMetric) ? (rtMargin.bottom*cDC.GetDeviceCaps(VERTRES)) / (100 * cDC.GetDeviceCaps(VERTSIZE)) : (rtMargin.bottom*cDC.GetDeviceCaps(LOGPIXELSY)) / 1000);
	return((cDC.IntersectClipRect(rClip) != ERROR) ? TRUE : FALSE);
}

BEGIN_MESSAGE_MAP(CGRDWnd, CDisplayWnd)
	//{{AFX_MSG_MAP(CGRDWnd)
	ON_WM_CREATE()
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_SYSCOMMAND()
	ON_WM_INITMENUPOPUP()
	ON_WM_SETFOCUS()
	ON_WM_DESTROY()
	ON_COMMAND(IDM_GRDSETTINGS, OnSettings)
	ON_COMMAND(IDM_GRDLINKAGES, OnLinkages)
	ON_COMMAND(IDM_GRDPARAMETERS, OnParameters)
	ON_COMMAND(IDM_GRDHOLD, OnHold)
	ON_COMMAND(IDM_GRDRETRIEVALS, OnRetrievals)
	ON_COMMAND(IDM_GRDRETRIEVESTOP, OnRetrieveStop)
	ON_COMMAND(IDM_GRDRETRIEVEFORWARD, OnRetrieveAutoForward)
	ON_COMMAND(IDM_GRDRETRIEVESTEPFORWARD, OnRetrieveManualForward)
	ON_COMMAND(IDM_GRDRETRIEVEPSEUDOREALTIME, OnRetrievePseudoRealtime)
	ON_COMMAND(IDM_GRDPRINT, OnPrint)
	ON_UPDATE_COMMAND_UI(IDM_GRDSETTINGS, OnUpdateSettings)
	ON_UPDATE_COMMAND_UI(IDM_GRDLINKAGES, OnUpdateLinkages)
	ON_UPDATE_COMMAND_UI(IDM_GRDPARAMETERS, OnUpdateParameters)
	ON_UPDATE_COMMAND_UI(IDM_GRDHOLD, OnUpdateHold)
	ON_UPDATE_COMMAND_UI(IDM_GRDRETRIEVALS, OnUpdateRetrievals)
	ON_UPDATE_COMMAND_UI(IDM_GRDRETRIEVESTOP, OnUpdateRetrieveStop)
	ON_UPDATE_COMMAND_UI(IDM_GRDRETRIEVEFORWARD, OnUpdateRetrieveAutoForward)
	ON_UPDATE_COMMAND_UI(IDM_GRDRETRIEVESTEPFORWARD, OnUpdateRetrieveManualForward)
	ON_UPDATE_COMMAND_UI(IDM_GRDRETRIEVEPSEUDOREALTIME, OnUpdateRetrievePseudoRealtime)
	ON_UPDATE_COMMAND_UI(IDM_GRDPRINT, OnUpdatePrint)
	ON_UPDATE_COMMAND_UI(ID_GRD_STATUSBAR_MESSAGEPANE, OnUpdateStatusBarMessagePane)
	ON_UPDATE_COMMAND_UI(ID_GRD_STATUSBAR_MODEPANE, OnUpdateStatusBarModePane)
	ON_UPDATE_COMMAND_UI(ID_GRD_STATUSBAR_TYPEPANE, OnUpdateStatusBarTypePane)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGRDWnd message handlers

int CGRDWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDisplayWnd::OnCreate(lpCreateStruct) != -1)
	{
		for (EnableDocking(CBRS_ALIGN_TOP); CreateToolBar() && CreateStatusBar() && CreateView() && LoadAccelTable(MAKEINTRESOURCE(IDR_GRDFRAME)); )
		{
			UpdateBars();
			return 0;
		}
	}
	return -1;
}

void CGRDWnd::OnGetMinMaxInfo(MINMAXINFO *lpMMI)
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

void CGRDWnd::OnSize(UINT nType, int cx, int cy)
{
	CDisplayWnd::OnSize(nType, cx, cy);
	m_wndView.RecalcLayout();
}

BOOL CGRDWnd::OnEraseBkgnd(CDC *pDC)
{
	if (!IsInitialized())
	{
		m_wndToolBar.UpdateWindow();
		m_wndStatusBar.UpdateWindow();
	}
	return TRUE;
}

void CGRDWnd::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGRDWnd::OnInitMenuPopup(CMenu *pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	for (; bSysMenu; )
	{
		UpdateSysMenu(pPopupMenu);
		break;
	}
	CDisplayWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
}

void CGRDWnd::OnSetFocus(CWnd *pOldWnd)
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

BOOL CGRDWnd::OnCloseOpenDialog(UINT nCode)
{
	UINT  nMode;
	UINT  nSpeed;
	BOOL  bBadData;
	BOOL  bToolTips;
	BOOL  bInvalidData;
	LOGFONT  fntTitle;
	LOGFONT  fntItems;
	LOGFONT  fntValues;
	LOGFONT  fntAxes;
	CString  szFileName;
	CTimeSpan  tInterval;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CUIntArray  nColors;
	CUIntArray  nTitleItems;
	CGRDLayout  cLayout;
	CGRDPrintJobs  pJobs;

	if (nCode == IDOK)
	{
		for (SetMode(m_dlgOpen.GetMode()), SetType(MAKELONG(DISPLAY_TYPE_GRD, m_dlgOpen.GetType())), SetWindowText(m_dlgOpen.GetTitle()); m_dlgOpen.IsLayoutModified(); )
		{
			m_dlgOpen.GetLayout(cLayout, nTitleItems);
			m_dlgOpen.GetLayoutColors(nColors);
			m_dlgOpen.GetLayoutTitleFont(&fntTitle);
			m_dlgOpen.GetLayoutItemsFont(&fntItems);
			m_dlgOpen.GetLayoutValuesFont(&fntValues);
			m_dlgOpen.GetLayoutAxesFont(&fntAxes);
			m_dlgOpen.GetLayoutInvalidDataMode(bInvalidData);
			m_dlgOpen.GetLayoutBadDataMode(bBadData);
			m_dlgOpen.GetLayoutToolTipMode(bToolTips);
			if ((HIWORD(GetType()) == GRD_TYPE_TEMPORARY  &&  !AddTemporaryGRD(cLayout.GetName(), cLayout)) || !SetLayout(cLayout, nTitleItems) || !SetTitleFont(&fntTitle) || !SetItemsFont(&fntItems) || !SetValuesFont(&fntValues) || !SetAxesFont(&fntAxes) || !SetOolColors(nColors) || !EnableInvalidDataMode(bInvalidData) || !EnableBadDataMode(bBadData) || !EnableToolTipMode(bToolTips)) return FALSE;
			break;
		}
		if (!m_dlgOpen.IsLayoutModified())
		{
			m_dlgOpen.GetLayout(cLayout);
			if ((HIWORD(GetType()) == GRD_TYPE_TEMPORARY  &&  !AddTemporaryGRD(cLayout.GetName(), cLayout)) || !SetLayout(cLayout)) return FALSE;
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

BOOL CGRDWnd::OnCloseSettingsDialog(UINT nCode)
{
	BOOL  bBadData;
	BOOL  bToolTips;
	BOOL  bInvalidData;
	CString  szLayout;
	CString  szFileName;
	LOGFONT  fntTitle[2];
	LOGFONT  fntItems[2];
	LOGFONT  fntValues[2];
	LOGFONT  fntAxes[2];
	CUIntArray  nColors;
	CUIntArray  nColumns;
	CGRDLayout  cLayout;
	CGRDPrintJobs  pJobs;

	if (nCode == IDOK)
	{
		if (m_dlgSettings.IsLayoutModified())
		{
			m_dlgSettings.GetLayout(cLayout, nColumns);
			m_dlgSettings.GetLayoutColors(nColors);
			m_dlgSettings.GetLayoutTitleFont(&fntTitle[0]);
			m_dlgSettings.GetLayoutItemsFont(&fntItems[0]);
			m_dlgSettings.GetLayoutValuesFont(&fntValues[0]);
			m_dlgSettings.GetLayoutAxesFont(&fntAxes[0]);
			m_dlgSettings.GetLayoutInvalidDataMode(bInvalidData);
			m_dlgSettings.GetLayoutBadDataMode(bBadData);
			m_dlgSettings.GetLayoutToolTipMode(bToolTips);
			if ((HIWORD(GetType()) == GRD_TYPE_TEMPORARY  &&  !AddTemporaryGRD(cLayout.GetName(), cLayout)) || !SetLayout(cLayout, nColumns) || ((!GetTitleFont(&fntTitle[1]) || !GetItemsFont(&fntItems[1]) || !GetValuesFont(&fntValues[1]) || !GetAxesFont(&fntAxes[1]) || memcmp(&fntTitle[0], &fntTitle[1], sizeof(LOGFONT)) || memcmp(&fntItems[0], &fntItems[1], sizeof(LOGFONT)) || memcmp(&fntValues[0], &fntValues[1], sizeof(LOGFONT)) || memcmp(&fntAxes[0], &fntAxes[1], sizeof(LOGFONT))) && (!SetTitleFont(&fntTitle[0]) || !SetItemsFont(&fntItems[0]) || !SetValuesFont(&fntValues[0]) || !SetAxesFont(&fntAxes[0]))) || !SetOolColors(nColors) || !EnableInvalidDataMode(bInvalidData) || !EnableBadDataMode(bBadData) || !EnableToolTipMode(bToolTips)) return FALSE;
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

BOOL CGRDWnd::OnCloseRetrieveDialog(UINT nCode)
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

void CGRDWnd::OnSettings()
{
	CHourglassCursor  cCursor;

	ReportEvent((m_dlgSettings.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CGRDWnd::OnLinkages()
{
	CHourglassCursor  cCursor;

	ReportEvent((m_dlgLinkages.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CGRDWnd::OnParameters()
{
	CHourglassCursor  cCursor;

	ReportEvent((m_dlgParameters.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CGRDWnd::OnHold()
{
	SetHoldFlag(!GetHoldFlag());
}

void CGRDWnd::OnRetrievals()
{
	CHourglassCursor  cCursor;

	ReportEvent((m_dlgRetrievals.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CGRDWnd::OnRetrieveStop()
{
	RetrieveMoreData(GRD_RETRIEVE_STOPPED);
}

void CGRDWnd::OnRetrieveAutoForward()
{
	RetrieveMoreData(GRD_RETRIEVE_AUTOFORWARD);
}

void CGRDWnd::OnRetrieveManualForward()
{
	RetrieveMoreData(GRD_RETRIEVE_MANUALFORWARD);
}

void CGRDWnd::OnRetrievePseudoRealtime()
{
	RetrieveMoreData(GRD_RETRIEVE_PSEUDOREALTIME);
}

void CGRDWnd::OnPrint()
{
	CHourglassCursor  cCursor;

	ReportEvent((!Print()) ? SYSTEM_WARNING_DISPLAY_PRINT_FAILURE : SYSTEM_NOERROR);
}

void CGRDWnd::OnDestroy()
{
	CHourglassCursor  cCursor;

	Stop();
	CDisplayWnd::OnDestroy();
}

void CGRDWnd::OnUpdateSettings(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsInitialized() && (HIWORD(GetType()) != GRD_TYPE_TEMPORARY || CheckAccountPrivilege(PRIVILEGE_GRD_TEMPORARYUSE)));
	pCmdUI->SetCheck(IsWindow(m_dlgSettings.GetSafeHwnd()));
}

void CGRDWnd::OnUpdateLinkages(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsInitialized() && !GetLink());
	pCmdUI->SetCheck(IsWindow(m_dlgLinkages.GetSafeHwnd()));
}

void CGRDWnd::OnUpdateParameters(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsInitialized() && HasLayout()) ? TRUE : FALSE);
	pCmdUI->SetCheck(IsWindow(m_dlgParameters.GetSafeHwnd()));
}

void CGRDWnd::OnUpdateHold(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsInitialized() && HasHoldFlag());
	pCmdUI->SetCheck(GetHoldFlag());
}

void CGRDWnd::OnUpdateRetrievals(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsInitialized()) ? TRUE : FALSE);
	pCmdUI->SetCheck(IsWindow(m_dlgRetrievals.GetSafeHwnd()));
}

void CGRDWnd::OnUpdateRetrieveStop(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && ((GetRetrieveMode() & GRD_RETRIEVE_AUTOFORWARD) || (GetRetrieveMode() & GRD_RETRIEVE_PSEUDOREALTIME) || HIWORD(IsRetrievingData())) && !(GetRetrieveMode() & GRD_RETRIEVE_STOPPED)) ? TRUE : FALSE);
}

void CGRDWnd::OnUpdateRetrieveAutoForward(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & GRD_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & GRD_RETRIEVE_STOPPED))) ? TRUE : FALSE);
}

void CGRDWnd::OnUpdateRetrieveManualForward(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & GRD_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & GRD_RETRIEVE_STOPPED))) ? TRUE : FALSE);
}

void CGRDWnd::OnUpdateRetrievePseudoRealtime(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & GRD_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & GRD_RETRIEVE_STOPPED))) ? TRUE : FALSE);
}

void CGRDWnd::OnUpdatePrint(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsInitialized() && IsDefaultPrinterAvailable() && CanPrint()) ? TRUE : FALSE);
}

void CGRDWnd::OnUpdateStatusBarMessagePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CGRDWnd::OnUpdateStatusBarModePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CGRDWnd::OnUpdateStatusBarTypePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}
