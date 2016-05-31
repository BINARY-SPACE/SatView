// MMD.CPP : Mimics Display Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the mimics display
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

#include "MimicsIIDs.h"
#include "MimicsCtlEnum.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static UINT BASED_CODE nMMDStatusBarIndicators[] =
{
	ID_MMD_STATUSBAR_MESSAGEPANE,
	ID_MMD_STATUSBAR_MODEPANE,
	ID_MMD_STATUSBAR_TYPEPANE
};



/////////////////////////////////////////////////////////////////////////////
// CMMDPrintJobInfo

CMMDPrintJobInfo::CMMDPrintJobInfo() : CObject()
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

VOID CMMDPrintJobInfo::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CMMDPrintJobInfo::GetName() CONST
{
	return m_szName;
}

VOID CMMDPrintJobInfo::SetProfile(LPCTSTR pszProfile)
{
	m_szProfile = pszProfile;
}

CString CMMDPrintJobInfo::GetProfile() CONST
{
	return m_szProfile;
}

VOID CMMDPrintJobInfo::SetComments(LPCTSTR pszComments)
{
	m_szComments = pszComments;
}

CString CMMDPrintJobInfo::GetComments() CONST
{
	return m_szComments;
}

BOOL CMMDPrintJobInfo::SetPrintMode(UINT nMode)
{
	m_nPrintMode = nMode;
	return TRUE;
}

UINT CMMDPrintJobInfo::GetPrintMode() CONST
{
	return m_nPrintMode;
}

BOOL CMMDPrintJobInfo::SetPrintFlags(UINT nFlags)
{
	if (nFlags == MMD_PRINT_ATTIME || nFlags == MMD_PRINT_ATDAILYTIME || nFlags == MMD_PRINT_ATEVENT || !nFlags)
	{
		m_nPrintFlags = nFlags;
		return TRUE;
	}
	return FALSE;
}

UINT CMMDPrintJobInfo::GetPrintFlags() CONST
{
	return m_nPrintFlags;
}

BOOL CMMDPrintJobInfo::SetPrintScale(UINT nScale)
{
	if (m_nPrintMode & MMD_PRINT_FIXEDSCALE)
	{
		m_nPrintScale = nScale;
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDPrintJobInfo::GetPrintScale(UINT &nScale) CONST
{
	if (m_nPrintMode & MMD_PRINT_FIXEDSCALE)
	{
		nScale = m_nPrintScale;
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDPrintJobInfo::SetPrintAtTime(CONST CTimeKey &tTime)
{
	if ((m_nPrintMode & MMD_PRINT_ATTIME) && !(m_nPrintMode & MMD_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & MMD_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & MMD_PRINT_REPEATSTOPBYTIME))
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
BOOL CMMDPrintJobInfo::SetPrintAtTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval)
{
	if ((m_nPrintMode & MMD_PRINT_ATTIME) && (m_nPrintMode & MMD_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & MMD_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & MMD_PRINT_REPEATSTOPBYTIME))
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
BOOL CMMDPrintJobInfo::SetPrintAtTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval, UINT nStopCount)
{
	if ((m_nPrintMode & MMD_PRINT_ATTIME) && (m_nPrintMode & MMD_PRINT_REPEATBYINTERVAL) && (m_nPrintMode & MMD_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & MMD_PRINT_REPEATSTOPBYTIME))
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
BOOL CMMDPrintJobInfo::SetPrintAtTime(CONST CTimeKey &tTime, CONST CTimeSpan &tInterval, CONST CTimeKey &tStopTime)
{
	if ((m_nPrintMode & MMD_PRINT_ATTIME) && (m_nPrintMode & MMD_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & MMD_PRINT_REPEATSTOPBYCOUNT) && (m_nPrintMode & MMD_PRINT_REPEATSTOPBYTIME))
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

BOOL CMMDPrintJobInfo::GetPrintAtTime(CTimeKey &tTime) CONST
{
	if ((m_nPrintMode & MMD_PRINT_ATTIME) && !(m_nPrintMode & MMD_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & MMD_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & MMD_PRINT_REPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtTime;
		return TRUE;
	}
	return FALSE;
}
BOOL CMMDPrintJobInfo::GetPrintAtTime(CTimeKey &tTime, CTimeSpan &tInterval) CONST
{
	if ((m_nPrintMode & MMD_PRINT_ATTIME) && (m_nPrintMode & MMD_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & MMD_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & MMD_PRINT_REPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtTime;
		tInterval = m_tRepeatInterval;
		return TRUE;
	}
	return FALSE;
}
BOOL CMMDPrintJobInfo::GetPrintAtTime(CTimeKey &tTime, CTimeSpan &tInterval, UINT &nStopCount) CONST
{
	if ((m_nPrintMode & MMD_PRINT_ATTIME) && (m_nPrintMode & MMD_PRINT_REPEATBYINTERVAL) && (m_nPrintMode & MMD_PRINT_REPEATSTOPBYCOUNT) && !(m_nPrintMode & MMD_PRINT_REPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtTime;
		tInterval = m_tRepeatInterval;
		nStopCount = m_nRepeatStopByCount[0];
		return TRUE;
	}
	return FALSE;
}
BOOL CMMDPrintJobInfo::GetPrintAtTime(CTimeKey &tTime, CTimeSpan &tInterval, CTimeKey &tStopTime) CONST
{
	if ((m_nPrintMode & MMD_PRINT_ATTIME) && (m_nPrintMode & MMD_PRINT_REPEATBYINTERVAL) && !(m_nPrintMode & MMD_PRINT_REPEATSTOPBYCOUNT) && (m_nPrintMode & MMD_PRINT_REPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtTime;
		tInterval = m_tRepeatInterval;
		tStopTime = m_tRepeatStopByTime[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDPrintJobInfo::SetPrintAtDailyTime(CONST CTimeSpan &tTime)
{
	TIMEKEY  tTimeKey;

	if ((m_nPrintMode & MMD_PRINT_ATDAILYTIME) && !(m_nPrintMode & MMD_PRINT_DAILYREPEATSTOPBYCOUNT) && !(m_nPrintMode & MMD_PRINT_DAILYREPEATSTOPBYTIME))
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
BOOL CMMDPrintJobInfo::SetPrintAtDailyTime(CONST CTimeSpan &tTime, UINT nStopCount)
{
	TIMEKEY  tTimeKey;

	if ((m_nPrintMode & MMD_PRINT_ATDAILYTIME) && (m_nPrintMode & MMD_PRINT_DAILYREPEATSTOPBYCOUNT) && !(m_nPrintMode & MMD_PRINT_DAILYREPEATSTOPBYTIME))
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
BOOL CMMDPrintJobInfo::SetPrintAtDailyTime(CONST CTimeSpan &tTime, CONST CTimeKey &tStopTime)
{
	TIMEKEY  tTimeKey;

	if ((m_nPrintMode & MMD_PRINT_ATDAILYTIME) && !(m_nPrintMode & MMD_PRINT_DAILYREPEATSTOPBYCOUNT) && (m_nPrintMode & MMD_PRINT_DAILYREPEATSTOPBYTIME))
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

BOOL CMMDPrintJobInfo::GetPrintAtDailyTime(CTimeSpan &tTime) CONST
{
	if ((m_nPrintMode & MMD_PRINT_ATDAILYTIME) && !(m_nPrintMode & MMD_PRINT_DAILYREPEATSTOPBYCOUNT) && !(m_nPrintMode & MMD_PRINT_DAILYREPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtDailyTime;
		return TRUE;
	}
	return FALSE;
}
BOOL CMMDPrintJobInfo::GetPrintAtDailyTime(CTimeSpan &tTime, UINT &nStopCount) CONST
{
	if ((m_nPrintMode & MMD_PRINT_ATDAILYTIME) && (m_nPrintMode & MMD_PRINT_DAILYREPEATSTOPBYCOUNT) && !(m_nPrintMode & MMD_PRINT_DAILYREPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtDailyTime;
		nStopCount = m_nRepeatStopByCount[1];
		return TRUE;
	}
	return FALSE;
}
BOOL CMMDPrintJobInfo::GetPrintAtDailyTime(CTimeSpan &tTime, CTimeKey &tStopTime) CONST
{
	if ((m_nPrintMode & MMD_PRINT_ATDAILYTIME) && !(m_nPrintMode & MMD_PRINT_DAILYREPEATSTOPBYCOUNT) && (m_nPrintMode & MMD_PRINT_DAILYREPEATSTOPBYTIME))
	{
		tTime = m_tPrintAtDailyTime;
		tStopTime = m_tRepeatStopByTime[1];
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDPrintJobInfo::SetPrintAtEvent(LPCTSTR pszEvent)
{
	if (m_nPrintMode & MMD_PRINT_ATEVENT)
	{
		m_szEvent = pszEvent;
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDPrintJobInfo::GetPrintAtEvent(CString &szEvent) CONST
{
	if (m_nPrintMode & MMD_PRINT_ATEVENT)
	{
		szEvent = m_szEvent;
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDPrintJobInfo::SetPrintCount(UINT nCount)
{
	if (m_nPrintMode & MMD_PRINT_ATTIME)
	{
		m_nPrintCount[0] = nCount;
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDPrintJobInfo::GetPrintCount(UINT &nCount) CONST
{
	if (m_nPrintMode & MMD_PRINT_ATTIME)
	{
		nCount = m_nPrintCount[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDPrintJobInfo::SetPrintDailyCount(UINT nCount)
{
	if (m_nPrintMode & MMD_PRINT_ATDAILYTIME)
	{
		m_nPrintCount[1] = nCount;
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDPrintJobInfo::GetPrintDailyCount(UINT &nCount) CONST
{
	if (m_nPrintMode & MMD_PRINT_ATDAILYTIME)
	{
		nCount = m_nPrintCount[1];
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDPrintJobInfo::SetPrintLastTime(CONST CTimeKey &tTime)
{
	if (m_nPrintMode & MMD_PRINT_ATTIME)
	{
		m_tPrintLastTime[0] = tTime;
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDPrintJobInfo::GetPrintLastTime(CTimeKey &tTime) CONST
{
	if (m_nPrintMode & MMD_PRINT_ATTIME)
	{
		tTime = m_tPrintLastTime[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDPrintJobInfo::SetPrintLastDailyTime(CONST CTimeKey &tTime)
{
	if (m_nPrintMode & MMD_PRINT_ATDAILYTIME)
	{
		m_tPrintLastTime[1] = tTime;
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDPrintJobInfo::GetPrintLastDailyTime(CTimeKey &tTime) CONST
{
	if (m_nPrintMode & MMD_PRINT_ATDAILYTIME)
	{
		tTime = m_tPrintLastTime[1];
		return TRUE;
	}
	return FALSE;
}

VOID CMMDPrintJobInfo::Copy(CONST CMMDPrintJobInfo *pJobInfo)
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

BOOL CMMDPrintJobInfo::Compare(CONST CMMDPrintJobInfo *pJobInfo) CONST
{
	return((pJobInfo->m_szName == m_szName  &&  pJobInfo->m_szProfile == m_szProfile  &&  pJobInfo->m_szComments == m_szComments  &&  pJobInfo->m_nPrintMode == m_nPrintMode && (!(m_nPrintMode & MMD_PRINT_FIXEDSCALE) || pJobInfo->m_nPrintScale == m_nPrintScale) && (!(m_nPrintMode & MMD_PRINT_ATTIME) || pJobInfo->m_tPrintAtTime == m_tPrintAtTime) && (!(m_nPrintMode & MMD_PRINT_ATDAILYTIME) || pJobInfo->m_tPrintAtDailyTime == m_tPrintAtDailyTime) && (!(m_nPrintMode & MMD_PRINT_ATEVENT) || pJobInfo->m_szEvent == m_szEvent) && (!(m_nPrintMode & MMD_PRINT_REPEATBYINTERVAL) || pJobInfo->m_tRepeatInterval == m_tRepeatInterval) && (!(m_nPrintMode & MMD_PRINT_REPEATSTOPBYCOUNT) || pJobInfo->m_nRepeatStopByCount[0] == m_nRepeatStopByCount[0]) && (!(m_nPrintMode & MMD_PRINT_REPEATSTOPBYTIME) || pJobInfo->m_tRepeatStopByTime[0] == m_tRepeatStopByTime[0]) && (!(m_nPrintMode & MMD_PRINT_DAILYREPEATSTOPBYCOUNT) || pJobInfo->m_nRepeatStopByCount[1] == m_nRepeatStopByCount[1]) && (!(m_nPrintMode & MMD_PRINT_DAILYREPEATSTOPBYTIME) || pJobInfo->m_tRepeatStopByTime[1] == m_tRepeatStopByTime[1])) ? TRUE : FALSE);
}

BOOL CMMDPrintJobInfo::Map(CByteArray &nInfo) CONST
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

BOOL CMMDPrintJobInfo::Unmap(CONST CByteArray &nInfo)
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
// CMMDPrintJobs

CMMDPrintJobs::CMMDPrintJobs() : CPtrArray()
{
	return;
}

CMMDPrintJobs::~CMMDPrintJobs()
{
	RemoveAll();
}

INT CMMDPrintJobs::Add(CMMDPrintJobInfo *pJobInfo)
{
	return((INT)CPtrArray::Add(pJobInfo));
}

INT CMMDPrintJobs::Find(LPCTSTR pszName) CONST
{
	INT  nJob;
	INT  nJobs;
	CMMDPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (INT)GetSize(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = GetAt(nJob)) && pJobInfo->GetName() == pszName) break;
		continue;
	}
	return((nJob < nJobs) ? nJob : -1);
}

CMMDPrintJobInfo *CMMDPrintJobs::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CMMDPrintJobInfo *)CPtrArray::GetAt(nIndex) : (CMMDPrintJobInfo *)NULL);
}

CMMDPrintJobInfo *CMMDPrintJobs::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CMMDPrintJobInfo *)CPtrArray::GetAt(nIndex) : (CMMDPrintJobInfo *)NULL);
}

TIMEKEY CMMDPrintJobs::Schedule()
{
	INT  nJob;
	INT  nJobs;
	UINT  nJobMode;
	UINT  nJobPrintCount[2];
	TIMEKEY  tJobPrintTimeout[2];
	CTimeKey  tJobPrintTime[4];
	CTimeSpan  tJobPrintInterval;
	CTimeSpan  tJobPrintDailyTime;
	CMMDPrintJobInfo  *pJobInfo[2];

	for (nJob = 0, nJobs = (INT)GetSize(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo[0] = GetAt(nJob)) != (CMMDPrintJobInfo *)NULL)
		{
			if (((nJobMode = pJobInfo[0]->GetPrintMode()) & MMD_PRINT_ACTIVE) && (((nJobMode & MMD_PRINT_ATTIME) && pJobInfo[0]->GetPrintLastTime(tJobPrintTime[1]) && (tJobPrintTime[1] > 0 || pJobInfo[0]->SetPrintLastTime(tJobPrintTime[3]))) || (nJobMode & MMD_PRINT_ATDAILYTIME)) &&
				((pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0]) && pJobInfo[0]->GetPrintCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastTime(tJobPrintTime[1]) && tJobPrintTime[3] >= tJobPrintTime[0] && tJobPrintTime[0] > tJobPrintTime[1] && pJobInfo[0]->SetPrintFlags(MMD_PRINT_ATTIME) && pJobInfo[0]->SetPrintCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0], tJobPrintInterval) && pJobInfo[0]->GetPrintCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastTime(tJobPrintTime[1]) && tJobPrintTime[3] >= tJobPrintTime[0] && (tJobPrintTime[0] > tJobPrintTime[1] || (tJobPrintTime[1].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds() < (tJobPrintTime[3].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds()) && pJobInfo[0]->SetPrintFlags(MMD_PRINT_ATTIME) && pJobInfo[0]->SetPrintCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0], tJobPrintInterval, nJobPrintCount[1]) && pJobInfo[0]->GetPrintCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastTime(tJobPrintTime[1]) && tJobPrintTime[3] >= tJobPrintTime[0] && (tJobPrintTime[0] > tJobPrintTime[1] || (tJobPrintTime[1].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds() < (tJobPrintTime[3].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds()) && nJobPrintCount[0] < nJobPrintCount[1] && pJobInfo[0]->SetPrintFlags(MMD_PRINT_ATTIME) && pJobInfo[0]->SetPrintCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtTime(tJobPrintTime[0], tJobPrintInterval, tJobPrintTime[2]) && pJobInfo[0]->GetPrintCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastTime(tJobPrintTime[1]) && tJobPrintTime[3] >= tJobPrintTime[0] && (tJobPrintTime[0] > tJobPrintTime[1] || (tJobPrintTime[1].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds() < (tJobPrintTime[3].GetTime() - tJobPrintTime[0].GetTime()) / tJobPrintInterval.GetTotalSeconds()) && tJobPrintTime[3] <= tJobPrintTime[2] && pJobInfo[0]->SetPrintFlags(MMD_PRINT_ATTIME) && pJobInfo[0]->SetPrintCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtDailyTime(tJobPrintDailyTime) && pJobInfo[0]->GetPrintDailyCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastDailyTime(tJobPrintTime[1]) && tJobPrintTime[3].GetTime() % SECONDSPERDAY >= tJobPrintDailyTime.GetTotalSeconds() && tJobPrintTime[3].GetTime() / SECONDSPERDAY != tJobPrintTime[1].GetTime() / SECONDSPERDAY  &&  pJobInfo[0]->SetPrintFlags(MMD_PRINT_ATDAILYTIME) && pJobInfo[0]->SetPrintDailyCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastDailyTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtDailyTime(tJobPrintDailyTime, nJobPrintCount[1]) && pJobInfo[0]->GetPrintDailyCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastDailyTime(tJobPrintTime[1]) && tJobPrintTime[3].GetTime() % SECONDSPERDAY >= tJobPrintDailyTime.GetTotalSeconds() && tJobPrintTime[3].GetTime() / SECONDSPERDAY != tJobPrintTime[1].GetTime() / SECONDSPERDAY  &&  nJobPrintCount[0] < nJobPrintCount[1] && pJobInfo[0]->SetPrintFlags(MMD_PRINT_ATDAILYTIME) && pJobInfo[0]->SetPrintDailyCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastDailyTime(tJobPrintTime[3])) ||
					(pJobInfo[0]->GetPrintAtDailyTime(tJobPrintDailyTime, tJobPrintTime[2]) && pJobInfo[0]->GetPrintDailyCount(nJobPrintCount[0]) && pJobInfo[0]->GetPrintLastDailyTime(tJobPrintTime[1]) && tJobPrintTime[3].GetTime() % SECONDSPERDAY >= tJobPrintDailyTime.GetTotalSeconds() && tJobPrintTime[3].GetTime() / SECONDSPERDAY != tJobPrintTime[1].GetTime() / SECONDSPERDAY  &&  tJobPrintTime[3] <= tJobPrintTime[2] && pJobInfo[0]->SetPrintFlags(MMD_PRINT_ATDAILYTIME) && pJobInfo[0]->SetPrintDailyCount(nJobPrintCount[0] + 1) && pJobInfo[0]->SetPrintLastDailyTime(tJobPrintTime[3]))))
			{
				if ((pJobInfo[1] = new CMMDPrintJobInfo))
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

VOID CMMDPrintJobs::RemoveAll()
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

BOOL CMMDPrintJobs::Copy(CONST CMMDPrintJobs *pPrintJobs)
{
	INT  nJob;
	INT  nJobs;
	CMMDPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (INT)pPrintJobs->GetSize(), RemoveAll(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = new CMMDPrintJobInfo) != (CMMDPrintJobInfo *)NULL)
		{
			pJobInfo->Copy(pPrintJobs->GetAt(nJob));
			InsertAt(nJob, pJobInfo, 1);
			continue;
		}
		break;
	}
	return((nJob == nJobs) ? TRUE : FALSE);
}

BOOL CMMDPrintJobs::Compare(CONST CMMDPrintJobs *pPrintJobs) CONST
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

BOOL CMMDPrintJobs::Map(CByteArray &nInfo) CONST
{
	INT  nJob;
	INT  nJobs;
	CByteArray  nJobData;
	CMMDPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (INT)GetSize(), nInfo.RemoveAll(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = GetAt(nJob)) && pJobInfo->Map(nJobData) && nInfo.Append(nJobData) >= 0) continue;
		break;
	}
	return((nJob == nJobs) ? TRUE : FALSE);
}

BOOL CMMDPrintJobs::Unmap(CONST CByteArray &nInfo)
{
	INT  cbJob;
	INT  cbJobs;
	CByteArray  nJobData;
	CMMDPrintJobInfo  *pJobInfo;

	for (cbJobs = 0, RemoveAll(); cbJobs < nInfo.GetSize(); cbJobs += cbJob)
	{
		for (CopyMemory(&cbJob, nInfo.GetData() + cbJobs, sizeof(cbJob)), nJobData.SetSize(max(min(cbJob, nInfo.GetSize() - cbJobs), 0)); nJobData.GetSize() >= 0; )
		{
			CopyMemory(nJobData.GetData(), nInfo.GetData() + cbJobs, nJobData.GetSize());
			break;
		}
		if ((pJobInfo = new CMMDPrintJobInfo))
		{
			if (pJobInfo->Unmap(nJobData) && Add(pJobInfo) >= 0) continue;
			delete pJobInfo;
		}
		break;
	}
	if ((pJobInfo = (!GetSize()) ? new CMMDPrintJobInfo : (CMMDPrintJobInfo *)NULL))
	{
		for (pJobInfo->SetName(STRING(IDS_PRINTJOB_DEFAULTNAME)), pJobInfo->SetProfile(STRING(IDS_PRINTPROFILE_DEFAULTNAME)), pJobInfo->SetPrintMode(MMD_PRINT_ALIGNDEFAULT | MMD_PRINT_AUTOSCALE); Add(pJobInfo) >= 0; ) return TRUE;
		delete pJobInfo;
		return FALSE;
	}
	return((cbJobs == nInfo.GetSize()) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CMMDSettingsLayoutPage property page

IMPLEMENT_DYNCREATE(CMMDSettingsLayoutPage, CLocalePropertyPage)

CMMDSettingsLayoutPage::CMMDSettingsLayoutPage() : CLocalePropertyPage(CMMDSettingsLayoutPage::IDD)
{
	//{{AFX_DATA_INIT(CMMDSettingsLayoutPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CMMDSettingsLayoutPage::Initialize()
{
	CMMDOpenDialog  *pDialog;

	if (((pDialog = GetParentDialog()->GetParentDialog()) && pDialog->GetLayout(m_cLayout)) || GetParentDisplay()->GetLayout(m_cLayout))
	{
		m_bInvalidData[0] = m_bInvalidData[1] = (!pDialog || !pDialog->GetLayoutInvalidDataMode(m_bInvalidData[0])) ? GetParentDisplay()->IsInvalidDataModeEnabled() : m_bInvalidData[0];
		m_bBadData[0] = m_bBadData[1] = (!pDialog || !pDialog->GetLayoutBadDataMode(m_bBadData[0])) ? GetParentDisplay()->IsBadDataModeEnabled() : m_bBadData[0];
		m_bToolTips[0] = m_bToolTips[1] = (!pDialog || !pDialog->GetLayoutToolTipMode(m_bToolTips[0])) ? GetParentDisplay()->IsToolTipModeEnabled() : m_bToolTips[0];
		m_cLayout.GetImage(m_sizeImage[0], m_nImage[0][0], m_nImage[0][1], m_nImage[0][2], m_nImage[0][3], m_nImageBkgnd[0], m_sizeGrid[0], m_nImageGrid[0], m_bUsedGrid[0]);
		m_sizeGrid[1] = m_sizeGrid[0];
		m_sizeImage[1] = m_sizeImage[0];
		m_nImageGrid[1] = m_nImageGrid[0];
		m_nImageBkgnd[1] = m_nImageBkgnd[0];
		m_nImage[1][0] = m_nImage[0][0];
		m_nImage[1][1] = m_nImage[0][1];
		m_nImage[1][2] = m_nImage[0][2];
		m_nImage[1][3] = m_nImage[0][3];
		m_bUsedGrid[1] = m_bUsedGrid[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDSettingsLayoutPage::GetLayout(CMMDLayout &cLayout) CONST
{
	if (cLayout.Copy(&m_cLayout))
	{
		cLayout.SetImage(m_sizeImage[0], m_nImage[0][0], m_nImage[0][1], m_nImage[0][2], m_nImage[0][3], m_nImageBkgnd[0], m_sizeGrid[0], m_nImageGrid[0], (m_sizeGrid[0].cx  &&  m_sizeGrid[0].cy) ? TRUE : FALSE);
		return Check(FALSE);
	}
	return FALSE;
}

BOOL CMMDSettingsLayoutPage::GetInvalidDataMode(BOOL &bEnable) CONST
{
	bEnable = m_bInvalidData[0];
	return Check(FALSE);
}

BOOL CMMDSettingsLayoutPage::GetBadDataMode(BOOL &bEnable) CONST
{
	bEnable = m_bBadData[0];
	return Check(FALSE);
}

BOOL CMMDSettingsLayoutPage::GetToolTipMode(BOOL &bEnable) CONST
{
	bEnable = m_bToolTips[0];
	return Check(FALSE);
}

CMMDSettingsDialog *CMMDSettingsLayoutPage::GetParentDialog() CONST
{
	return((CMMDSettingsDialog *)CLocalePropertyPage::GetParent());
}

CMMDWnd *CMMDSettingsLayoutPage::GetParentDisplay() CONST
{
	return((CMMDWnd *)GetParentDialog()->GetParentDisplay());
}

VOID CMMDSettingsLayoutPage::ShowProperties()
{
	CByteArray  nCode;
	EDITSTREAM  sStream;

	if (m_cLayout.GetSourceCode(nCode) > 0)
	{
		sStream.dwCookie = (DWORD_PTR)&nCode;
		sStream.pfnCallback = SetCodeCallback;
		SendDlgItemMessage(IDC_MMDSETTINGS_LAYOUTPAGE_SOURCECODE_CONTENTS, EM_STREAMIN, SF_RTF, (LPARAM)&sStream);
	}
	CheckRadioButton(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_DEFAULT, IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED, (m_sizeImage[0].cx <= 0 || m_sizeImage[0].cy <= 0) ? IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_DEFAULT : IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED);
	CheckRadioButton(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_POINTS, IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_LINES, (m_sizeGrid[0].cx > 0 && m_sizeGrid[0].cy > 0) ? IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_POINTS : ((m_sizeGrid[0].cx < 0 && m_sizeGrid[0].cy < 0) ? IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_LINES : -1));
	SendDlgItemMessage(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_BACKGROUND, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nImageBkgnd[0]);
	SendDlgItemMessage(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)m_nImageGrid[0]);
	Spinbox_SetPos(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_HORIZONTALINTERVAL), abs(m_sizeGrid[0].cx));
	Spinbox_SetPos(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_VERTICALINTERVAL), abs(m_sizeGrid[0].cy));
	Spinbox_SetPos(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED_X), m_sizeImage[0].cx);
	Spinbox_SetPos(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED_Y), m_sizeImage[0].cy);
	Spinbox_SetPos(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_LEFT), m_nImage[0][0]);
	Spinbox_SetPos(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_TOP), m_nImage[0][1]);
	Spinbox_SetPos(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_RIGHT), m_nImage[0][2]);
	Spinbox_SetPos(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_BOTTOM), m_nImage[0][3]);
	CheckDlgButton(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_INVALIDDATA, m_bInvalidData[0]);
	CheckDlgButton(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_BADDATA, m_bBadData[0]);
	CheckDlgButton(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_TOOLTIPS, m_bToolTips[0]);
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT)->EnableWindow();
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_DEFAULT)->EnableWindow();
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED)->EnableWindow();
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED_X)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED));
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED));
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED_Y)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED));
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED_UNITS)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED));
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_LEFT_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED));
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_LEFT)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED));
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_TOP_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED));
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_TOP)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED));
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_TOP_PIXELS)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED));
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_RIGHT_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_RIGHT)->EnableWindow();
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_BOTTOM_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_BOTTOM)->EnableWindow();
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_BOTTOM_PIXELS)->EnableWindow();
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_BACKGROUND_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_BACKGROUND)->EnableWindow();
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_POINTS)->EnableWindow();
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_LINES)->EnableWindow();
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_HORIZONTALINTERVAL_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_POINTS) || IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_LINES));
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_HORIZONTALINTERVAL)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_POINTS) || IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_LINES));
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_HORIZONTALINTERVAL_UNITS)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_POINTS) || IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_LINES));
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_VERTICALINTERVAL_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_POINTS) || IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_LINES));
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_VERTICALINTERVAL)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_POINTS) || IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_LINES));
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_VERTICALINTERVAL_UNITS)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_POINTS) || IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_LINES));
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_COLOR_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_POINTS) || IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_LINES));
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_COLOR)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_POINTS) || IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_LINES));
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SHOW)->EnableWindow();
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_INVALIDDATA)->EnableWindow();
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_BADDATA)->EnableWindow();
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_TOOLTIPS)->EnableWindow();
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_SOURCECODE_CONTENTS)->EnableWindow();
}

DWORD CALLBACK CMMDSettingsLayoutPage::SetCodeCallback(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
	LONG  cbCode;
	CByteArray  *pCode = (CByteArray *)dwCookie;
	static LONG  nCode = 0;

	CopyMemory(pbBuff, pCode->GetData() + nCode, (cbCode = (LONG)max(min(pCode->GetSize() - nCode, cb), 0)));
	CopyMemory(pcb, &cbCode, sizeof(LONG));
	nCode = (nCode + cbCode < pCode->GetSize()) ? (nCode + cbCode) : 0;
	return 0;
}

BOOL CMMDSettingsLayoutPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (m_sizeImage[0] != m_sizeImage[1] || m_nImageBkgnd[0] != m_nImageBkgnd[1] || m_nImage[0][0] != m_nImage[1][0] || m_nImage[0][1] != m_nImage[1][1] || m_nImage[0][2] != m_nImage[1][2] || m_nImage[0][3] != m_nImage[1][3] || m_sizeGrid[0] != m_sizeGrid[1] || m_nImageGrid[0] != m_nImageGrid[1] || m_bUsedGrid[0] != m_bUsedGrid[1] || m_bInvalidData[0] != m_bInvalidData[1] || m_bBadData[0] != m_bBadData[1] || m_bToolTips[0] != m_bToolTips[1]) : CLocalePropertyPage::IsModified()) : FALSE);
}

BOOL CMMDSettingsLayoutPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? TRUE : CLocalePropertyPage::Check()) : TRUE);
}

void CMMDSettingsLayoutPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMMDSettingsLayoutPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CMMDSettingsLayoutPage::PostNcDestroy()
{
	m_cCodeFont.DeleteObject();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CMMDSettingsLayoutPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CMMDSettingsLayoutPage)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_DEFAULT, OnDefaultSize)
	ON_BN_CLICKED(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED, OnFixedSize)
	ON_BN_CLICKED(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_POINTS, OnGridPoints)
	ON_BN_CLICKED(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_LINES, OnGridLines)
	ON_BN_CLICKED(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_INVALIDDATA, OnInvalidData)
	ON_BN_CLICKED(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_BADDATA, OnBadData)
	ON_BN_CLICKED(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_TOOLTIPS, OnToolTips)
	ON_CBN_SELCHANGE(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_BACKGROUND, OnSelchangeBackgroundColor)
	ON_CBN_SELCHANGE(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_COLOR, OnSelchangeGridColor)
	ON_CONTROL(SBXN_CHANGE, IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED_X, OnSpinchangeHorizontalSize)
	ON_CONTROL(SBXN_CHANGE, IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED_Y, OnSpinchangeVerticalSize)
	ON_CONTROL(SBXN_CHANGE, IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_LEFT, OnSpinchangeLeftMargin)
	ON_CONTROL(SBXN_CHANGE, IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_RIGHT, OnSpinchangeRightMargin)
	ON_CONTROL(SBXN_CHANGE, IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_TOP, OnSpinchangeTopMargin)
	ON_CONTROL(SBXN_CHANGE, IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_BOTTOM, OnSpinchangeBottomMargin)
	ON_CONTROL(SBXN_CHANGE, IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_HORIZONTALINTERVAL, OnSpinchangeHorizontalGridInterval)
	ON_CONTROL(SBXN_CHANGE, IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_VERTICALINTERVAL, OnSpinchangeVerticalGridInterval)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDSettingsLayoutPage message handlers

int CMMDSettingsLayoutPage::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CFontTools  cFontTools(&m_cCodeFont);

	return CLocalePropertyPage::OnCreate(lpCreateStruct);
}

BOOL CMMDSettingsLayoutPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_SOURCECODE_CONTENTS)->SetFont(&m_cCodeFont);
	Spinbox_SetRange(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED_X), 0, GetSystemMetrics(SM_CXSCREEN));
	Spinbox_SetRange(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED_Y), 0, GetSystemMetrics(SM_CYSCREEN));
	Spinbox_SetRange(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_LEFT), 0, GetSystemMetrics(SM_CXSCREEN));
	Spinbox_SetRange(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_TOP), 0, GetSystemMetrics(SM_CYSCREEN));
	Spinbox_SetRange(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_RIGHT), 0, GetSystemMetrics(SM_CXSCREEN));
	Spinbox_SetRange(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_BOTTOM), 0, GetSystemMetrics(SM_CYSCREEN));
	Spinbox_SetRange(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_HORIZONTALINTERVAL), 2, GetSystemMetrics(SM_CXSCREEN));
	Spinbox_SetRange(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_VERTICALINTERVAL), 2, GetSystemMetrics(SM_CYSCREEN));
	SendDlgItemMessage(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_BACKGROUND, CCB_INSERTCOLOR, 0, (LPARAM)GetSysColor(COLOR_WINDOW));
	SendDlgItemMessage(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_COLOR, CCB_INSERTCOLOR, 0, (LPARAM)GetSysColor(COLOR_WINDOW));
	ShowProperties();
	return TRUE;
}

void CMMDSettingsLayoutPage::OnDefaultSize()
{
	Spinbox_SetPos(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED_X), (m_sizeImage[0].cx = 0));
	Spinbox_SetPos(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED_Y), (m_sizeImage[0].cy = 0));
	Spinbox_SetPos(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_LEFT), (m_nImage[0][0] = 0));
	Spinbox_SetPos(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_TOP), (m_nImage[0][1] = 0));
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED_X)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED_Y)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED_UNITS)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_LEFT_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_LEFT)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_TOP_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_TOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_TOP_PIXELS)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsLayoutPage::OnFixedSize()
{
	Spinbox_SetPos(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED_X), (m_sizeImage[0].cx = ((m_nImage[0][0] = 0) == 0) ? MMDSETTINGSLAYOUTPAGE_DEFAULT_IMAGEWIDTH : 0));
	Spinbox_SetPos(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED_Y), (m_sizeImage[0].cy = ((m_nImage[0][1] = 0) == 0) ? MMDSETTINGSLAYOUTPAGE_DEFAULT_IMAGEHEIGHT : 0));
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED_X)->EnableWindow();
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED_Y)->EnableWindow();
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED_UNITS)->EnableWindow();
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_LEFT_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_LEFT)->EnableWindow();
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_TOP_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_TOP)->EnableWindow();
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_TOP_PIXELS)->EnableWindow();
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED_X)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsLayoutPage::OnGridPoints()
{
	CheckDlgButton(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_LINES, FALSE);
	CheckDlgButton(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_POINTS, !IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_POINTS));
	Spinbox_SetPos(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_HORIZONTALINTERVAL), (m_sizeGrid[0].cx = (IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_POINTS)) ? MMDSETTINGSLAYOUTPAGE_DEFAULT_GRIDINTERVAL : 0));
	Spinbox_SetPos(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_VERTICALINTERVAL), (m_sizeGrid[0].cy = (IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_POINTS)) ? MMDSETTINGSLAYOUTPAGE_DEFAULT_GRIDINTERVAL : 0));
	SendDlgItemMessage(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)(m_nImageGrid[0] = VGA_COLOR_LTGRAY));
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_HORIZONTALINTERVAL_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_POINTS));
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_HORIZONTALINTERVAL)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_POINTS));
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_HORIZONTALINTERVAL_UNITS)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_POINTS));
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_VERTICALINTERVAL_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_POINTS));
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_VERTICALINTERVAL)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_POINTS));
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_VERTICALINTERVAL_UNITS)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_POINTS));
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_COLOR_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_POINTS));
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_COLOR)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_POINTS));
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_HORIZONTALINTERVAL)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsLayoutPage::OnGridLines()
{
	CheckDlgButton(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_POINTS, FALSE);
	CheckDlgButton(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_LINES, !IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_LINES));
	Spinbox_SetPos(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_HORIZONTALINTERVAL), abs((m_sizeGrid[0].cx = (IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_LINES)) ? -MMDSETTINGSLAYOUTPAGE_DEFAULT_GRIDINTERVAL : 0)));
	Spinbox_SetPos(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_VERTICALINTERVAL), abs((m_sizeGrid[0].cy = (IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_LINES)) ? -MMDSETTINGSLAYOUTPAGE_DEFAULT_GRIDINTERVAL : 0)));
	SendDlgItemMessage(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_COLOR, CCB_SELECTCOLOR, (WPARAM)-1, (LPARAM)(m_nImageGrid[0] = VGA_COLOR_LTGRAY));
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_HORIZONTALINTERVAL_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_LINES));
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_HORIZONTALINTERVAL)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_LINES));
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_HORIZONTALINTERVAL_UNITS)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_LINES));
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_VERTICALINTERVAL_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_LINES));
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_VERTICALINTERVAL)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_LINES));
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_VERTICALINTERVAL_UNITS)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_LINES));
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_COLOR_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_LINES));
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_COLOR)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_LINES));
	GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_HORIZONTALINTERVAL)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsLayoutPage::OnInvalidData()
{
	m_bInvalidData[0] = IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_INVALIDDATA);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsLayoutPage::OnBadData()
{
	m_bBadData[0] = IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_BADDATA);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsLayoutPage::OnToolTips()
{
	m_bToolTips[0] = IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_TOOLTIPS);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsLayoutPage::OnSelchangeBackgroundColor()
{
	m_nImageBkgnd[0] = (COLORREF)SendDlgItemMessage(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_BACKGROUND, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_BACKGROUND, CB_GETCURSEL));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsLayoutPage::OnSelchangeGridColor()
{
	m_nImageGrid[0] = (COLORREF)SendDlgItemMessage(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_COLOR, CCB_GETCOLOR, (WPARAM)SendDlgItemMessage(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_COLOR, CB_GETCURSEL));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsLayoutPage::OnSpinchangeHorizontalSize()
{
	m_sizeImage[0].cx = (LONG)Spinbox_GetPos(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED_X));
	Spinbox_SetRange(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_LEFT), 0, m_sizeImage[0].cx);
	Spinbox_SetRange(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_RIGHT), 0, (!m_sizeImage[0].cx) ? GetSystemMetrics(SM_CXSCREEN) : m_sizeImage[0].cx);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsLayoutPage::OnSpinchangeVerticalSize()
{
	m_sizeImage[0].cy = (LONG)Spinbox_GetPos(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_SIZE_FIXED_Y));
	Spinbox_SetRange(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_TOP), 0, m_sizeImage[0].cy);
	Spinbox_SetRange(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_BOTTOM), 0, (!m_sizeImage[0].cy) ? GetSystemMetrics(SM_CYSCREEN) : m_sizeImage[0].cy);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsLayoutPage::OnSpinchangeLeftMargin()
{
	m_nImage[0][0] = (INT)Spinbox_GetPos(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_LEFT));
	Spinbox_SetPos(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_RIGHT), (m_nImage[0][2] = (m_sizeImage[0].cx > 0) ? ((m_sizeImage[0].cx - m_nImage[0][0] - m_nImage[0][2] < 0) ? (m_sizeImage[0].cx - m_nImage[0][0]) : m_nImage[0][2]) : m_nImage[0][2]));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsLayoutPage::OnSpinchangeRightMargin()
{
	m_nImage[0][2] = (INT)Spinbox_GetPos(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_RIGHT));
	Spinbox_SetPos(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_LEFT), (m_nImage[0][0] = (m_sizeImage[0].cx > 0) ? ((m_sizeImage[0].cx - m_nImage[0][2] - m_nImage[0][0] < 0) ? (m_sizeImage[0].cx - m_nImage[0][2]) : m_nImage[0][0]) : m_nImage[0][0]));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsLayoutPage::OnSpinchangeTopMargin()
{
	m_nImage[0][1] = (INT)Spinbox_GetPos(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_TOP));
	Spinbox_SetPos(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_BOTTOM), (m_nImage[0][3] = (m_sizeImage[0].cy > 0) ? ((m_sizeImage[0].cy - m_nImage[0][1] - m_nImage[0][3] < 0) ? (m_sizeImage[0].cy - m_nImage[0][1]) : m_nImage[0][3]) : m_nImage[0][3]));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsLayoutPage::OnSpinchangeBottomMargin()
{
	m_nImage[0][3] = (INT)Spinbox_GetPos(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_BOTTOM));
	Spinbox_SetPos(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_MARGINS_TOP), (m_nImage[0][1] = (m_sizeImage[0].cy > 0) ? ((m_sizeImage[0].cy - m_nImage[0][3] - m_nImage[0][1] < 0) ? (m_sizeImage[0].cy - m_nImage[0][3]) : m_nImage[0][1]) : m_nImage[0][1]));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsLayoutPage::OnSpinchangeHorizontalGridInterval()
{
	INT  nInterval;

	if (IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_POINTS) || IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_LINES))
	{
		nInterval = (INT)Spinbox_GetPos(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_HORIZONTALINTERVAL));
		m_sizeGrid[0].cx = (IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_LINES)) ? -nInterval : nInterval;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsLayoutPage::OnSpinchangeVerticalGridInterval()
{
	INT  nInterval;

	if (IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_POINTS) || IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_LINES))
	{
		nInterval = (INT)Spinbox_GetPos(GetDlgItem(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_VERTICALINTERVAL));
		m_sizeGrid[0].cy = (IsDlgButtonChecked(IDC_MMDSETTINGS_LAYOUTPAGE_FORMAT_GRID_LINES)) ? -nInterval : nInterval;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CMMDSettingsRetrievingPage property page

IMPLEMENT_DYNCREATE(CMMDSettingsRetrievingPage, CLocalePropertyPage)

CMMDSettingsRetrievingPage::CMMDSettingsRetrievingPage() : CLocalePropertyPage(CMMDSettingsRetrievingPage::IDD)
{
	//{{AFX_DATA_INIT(CMMDSettingsRetrievingPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CMMDSettingsRetrievingPage::Initialize()
{
	CMMDOpenDialog  *pDialog;

	if (((pDialog = GetParentDialog()->GetParentDialog()) && pDialog->GetRetrieveFileName(m_szFileName[0])) || GetParentDisplay()->GetRetrieveFileName(m_szFileName[0]))
	{
		m_szFileName[1] = m_szFileName[0];
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDSettingsRetrievingPage::GetDataSourceFileName(CString &szFileName) CONST
{
	szFileName = m_szFileName[0];
	return Check(FALSE);
}

CMMDSettingsDialog *CMMDSettingsRetrievingPage::GetParentDialog() CONST
{
	return((CMMDSettingsDialog *)CLocalePropertyPage::GetParent());
}

CMMDWnd *CMMDSettingsRetrievingPage::GetParentDisplay() CONST
{
	return((CMMDWnd *)GetParentDialog()->GetParentDisplay());
}

VOID CMMDSettingsRetrievingPage::EnumDataSources()
{
	INT  nFile;
	INT  nFiles;
	CHistoryStoreFile  cFile;
	CHistoryStoreFiles  pFiles;
	CUIntArray  nOptions;

	for (nFile = 0, nFiles = GetTMService()->GetTMHistoryFiles(HISTORYFILE_TYPE_RETRIEVE, pFiles), GetTMService()->GetDefaultTMHistoryFile(HISTORYFILE_TYPE_RETRIEVE, cFile), m_szFileName[0] = (pFiles.Find(m_szFileName[0]) < 0) ? cFile.GetFileName() : m_szFileName[0]; nFile < nFiles || (!nFiles && !nFile && !m_szFileName[0].IsEmpty()); nFile++)
	{
		SendDlgItemMessage(IDC_MMDSETTINGS_RETRIEVINGPAGE_DATASOURCE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)((nFiles > 0) ? (LPCTSTR)pFiles.GetAt(nFile)->GetFileName() : (LPCTSTR)m_szFileName[0]));
		continue;
	}
	SendDlgItemMessage(IDC_MMDSETTINGS_RETRIEVINGPAGE_DATASOURCE, CB_SETCURSEL, (WPARAM)max(SendDlgItemMessage(IDC_MMDSETTINGS_RETRIEVINGPAGE_DATASOURCE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)m_szFileName[0]), 0));
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_DATASOURCE)->GetWindowText(m_szFileName[0]);
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_DATASOURCE)->GetWindowText(m_szFileName[1]);
	ShowDataSourceInfo();
}

VOID CMMDSettingsRetrievingPage::ShowDataSourceInfo()
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
		GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT)->SetWindowText(szProduct);
		GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY)->SetWindowText(szCompany);
		GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT)->SetWindowText(szSpacecraft);
		GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE)->SetWindowText(szDataSourceType);
		GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->SetWindowText(szStartTime);
		GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->SetWindowText(szStopTime);
		GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->SetWindowText(szCreationTime);
		GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE)->SetWindowText(szDataSourceSize);
	}
	else
	{
		GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT)->SetWindowText((szProduct = EMPTYSTRING));
		GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY)->SetWindowText((szCompany = EMPTYSTRING));
		GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT)->SetWindowText((szSpacecraft = EMPTYSTRING));
		GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE)->SetWindowText((szDataSourceType = EMPTYSTRING));
		GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->SetWindowText((szStartTime = EMPTYSTRING));
		GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->SetWindowText((szStopTime = EMPTYSTRING));
		GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->SetWindowText((szCreationTime = EMPTYSTRING));
		GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE)->SetWindowText((szDataSourceSize = EMPTYSTRING));
	}
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO)->EnableWindow();
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMMENTS)->EnableWindow(szProduct.IsEmpty());
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMMENTS)->ShowWindow((szProduct.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT_STATIC)->ShowWindow((!szProduct.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT_STATIC)->EnableWindow(!szProduct.IsEmpty());
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT)->ShowWindow((!szProduct.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT)->EnableWindow(!szProduct.IsEmpty());
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY_STATIC)->ShowWindow((!szCompany.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY_STATIC)->EnableWindow(!szCompany.IsEmpty());
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY)->ShowWindow((!szCompany.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY)->EnableWindow(!szCompany.IsEmpty());
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT_STATIC)->ShowWindow((!szSpacecraft.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT_STATIC)->EnableWindow(!szSpacecraft.IsEmpty());
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT)->ShowWindow((!szSpacecraft.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT)->EnableWindow(!szSpacecraft.IsEmpty());
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE_STATIC)->ShowWindow((!szDataSourceType.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE_STATIC)->EnableWindow(!szDataSourceType.IsEmpty());
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE)->ShowWindow((!szDataSourceType.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE)->EnableWindow(!szDataSourceType.IsEmpty());
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STATIC)->ShowWindow((GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STATIC)->EnableWindow((GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->ShowWindow((GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->EnableWindow((GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_TO)->ShowWindow((GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_TO)->EnableWindow((GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->ShowWindow((GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->EnableWindow((GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME)->GetWindowTextLength() > 0 && GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME_STATIC)->ShowWindow((GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME_STATIC)->EnableWindow((GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->ShowWindow((GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->GetWindowTextLength() > 0) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->EnableWindow((GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME)->GetWindowTextLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE_STATIC)->ShowWindow((!szDataSourceSize.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE_STATIC)->EnableWindow(!szDataSourceSize.IsEmpty());
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE)->ShowWindow((!szDataSourceSize.IsEmpty()) ? SW_SHOWNA : SW_HIDE);
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE)->EnableWindow(!szDataSourceSize.IsEmpty());
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_INSPECT)->EnableWindow(!m_szFileName[0].IsEmpty());
}

BOOL CMMDSettingsRetrievingPage::CheckDataSource(LPCTSTR pszFileName) CONST
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
BOOL CMMDSettingsRetrievingPage::CheckDataSource(LPCTSTR pszFileName, CString &szProduct, CString &szCompany, CString &szTrademark, CString &szSpacecraft, CString &szDataSourceType, CString &szStartTime, CString &szStopTime, CString &szCreationTime, CString &szDataSourceSize) CONST
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
			for (cHistoryFile.GetCopyrightProduct(szProduct), cHistoryFile.GetCopyrightCompany(szCompany), cHistoryFile.GetCopyrightTrademark(szTrademark), cHistoryFile.GetSpacecraft(szSpacecraft), cHistoryFile.GetType(szDataSourceType), szStartTime = (cHistoryFile.CLogFile::SeekToFirst() && cHistoryFile.CLogFile::Read(tTime, nData)) ? (LPCTSTR)tTime.FormatGmt(STRING(IDS_MMDSETTINGS_RETRIEVINGPAGE_SOURCEDATATIMEFORMAT)) : EMPTYSTRING, szStopTime = (cHistoryFile.CLogFile::SeekToLast() && cHistoryFile.CLogFile::Read(tTime, nData)) ? (LPCTSTR)tTime.FormatGmt(STRING(IDS_MMDSETTINGS_RETRIEVINGPAGE_SOURCEDATATIMEFORMAT)) : EMPTYSTRING, szCreationTime = (cHistoryFile.GetCopyrightCreationTime(tTime)) ? (LPCTSTR)tTime.FormatGmt(STRING(IDS_MMDSETTINGS_RETRIEVINGPAGE_SOURCEDATAFILETIMEFORMAT)) : EMPTYSTRING, szDataSourceSize.Format(STRING(IDS_MMDSETTINGS_RETRIEVINGPAGE_SOURCEDATASIZEFORMAT), ((dwSize = cHistoryFile.CLogFile::GetSize()) + 512) / 1024), szDataSourceSize = FormatDataSourceSize(szDataSourceSize); !szProduct.IsEmpty() && !szCompany.IsEmpty() && !szTrademark.IsEmpty(); )
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

CString CMMDSettingsRetrievingPage::FormatDataSourceSize(LPCTSTR pszDataSourceSize) CONST
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

BOOL CMMDSettingsRetrievingPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? ((m_szFileName[0].CompareNoCase(m_szFileName[1])) ? TRUE : FALSE) : CLocalePropertyPage::IsModified()) : FALSE);
}

BOOL CMMDSettingsRetrievingPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (m_szFileName[0].IsEmpty() || CheckDataSource(m_szFileName[0])) : CLocalePropertyPage::Check()) : TRUE);
}

void CMMDSettingsRetrievingPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMMDSettingsRetrievingPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMMDSettingsRetrievingPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CMMDSettingsRetrievingPage)
	ON_BN_CLICKED(IDC_MMDSETTINGS_RETRIEVINGPAGE_INSPECT, OnInspect)
	ON_CBN_EDITCHANGE(IDC_MMDSETTINGS_RETRIEVINGPAGE_DATASOURCE, OnEditchangeFileName)
	ON_CBN_SELCHANGE(IDC_MMDSETTINGS_RETRIEVINGPAGE_DATASOURCE, OnSelchangeFileName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDSettingsRetrievingPage message handlers

BOOL CMMDSettingsRetrievingPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_DETAILS)->EnableWindow();
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_DATASOURCE_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_DATASOURCE)->EnableWindow();
	EnumDataSources();
	return TRUE;
}

BOOL CMMDSettingsRetrievingPage::OnSetActive()
{
	ShowDataSourceInfo();
	return CLocalePropertyPage::OnSetActive();
}

void CMMDSettingsRetrievingPage::OnInspect()
{
	CHourglassCursor  cCursor;

	ShowDataSourceInfo();
}

void CMMDSettingsRetrievingPage::OnEditchangeFileName()
{
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_DATASOURCE)->GetWindowText(m_szFileName[0]);
	GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_INSPECT)->EnableWindow(!m_szFileName[0].IsEmpty());
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsRetrievingPage::OnSelchangeFileName()
{
	for (m_szFileName[0] = Combobox_GetText(GetDlgItem(IDC_MMDSETTINGS_RETRIEVINGPAGE_DATASOURCE), (INT)SendDlgItemMessage(IDC_MMDSETTINGS_RETRIEVINGPAGE_DATASOURCE, CB_GETCURSEL)); !m_szFileName[0].IsEmpty(); )
	{
		ShowDataSourceInfo();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CMMDSettingsPrintingComments

IMPLEMENT_DYNCREATE(CMMDSettingsPrintingComments, CEdit)

BEGIN_MESSAGE_MAP(CMMDSettingsPrintingComments, CEdit)
	//{{AFX_MSG_MAP(CMMDSettingsPrintingComments)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDSettingsPrintingComments message handlers

void CMMDSettingsPrintingComments::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
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
// CMMDSettingsPrintingPage property page

IMPLEMENT_DYNCREATE(CMMDSettingsPrintingPage, CLocalePropertyPage)

CMMDSettingsPrintingPage::CMMDSettingsPrintingPage() : CLocalePropertyPage(CMMDSettingsPrintingPage::IDD)
{
	//{{AFX_DATA_INIT(CMMDSettingsPrintingPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CMMDSettingsPrintingPage::Initialize()
{
	CMMDOpenDialog  *pDialog;

	return((((pDialog = GetParentDialog()->GetParentDialog()) && pDialog->GetPrintJobs(m_pJobs[0])) || GetParentDisplay()->GetPrintJobs(m_pJobs[0])) ? m_pJobs[1].Copy(&m_pJobs[0]) : FALSE);
}

BOOL CMMDSettingsPrintingPage::GetJobs(CMMDPrintJobs &pJobs) CONST
{
	return((pJobs.Copy(&m_pJobs[0])) ? Check(FALSE) : FALSE);
}

CMMDSettingsDialog *CMMDSettingsPrintingPage::GetParentDialog() CONST
{
	return((CMMDSettingsDialog *)CLocalePropertyPage::GetParent());
}

CMMDWnd *CMMDSettingsPrintingPage::GetParentDisplay() CONST
{
	return((CMMDWnd *)GetParentDialog()->GetParentDisplay());
}

VOID CMMDSettingsPrintingPage::ShowJobInfo()
{
	UINT  nMode;
	UINT  nScale;
	CMMDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		CheckRadioButton(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_AUTOSCALE, IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE, ((nMode = pJobInfo->GetPrintMode()) & MMD_PRINT_AUTOSCALE) ? IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_AUTOSCALE : IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE);
		CheckDlgButton(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL, (nMode & MMD_PRINT_UNDERLINEOOL) ? TRUE : FALSE);
		CheckDlgButton(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_NOCOLORS, (nMode & MMD_PRINT_NOCOLORS) ? TRUE : FALSE);
		CheckDlgButton(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS, (nMode & MMD_PRINT_CLEARCOMMENTS) ? TRUE : FALSE);
		SendDlgItemMessage(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetProfile()));
		SendDlgItemMessage(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_ALIGNMENT, ALCB_SELECTALIGNMENT, (WPARAM)-1, ((nMode & MMD_PRINT_ALIGNMENT) == MMD_PRINT_ALIGNHLEFTVTOP) ? AL_HLEFTVTOP : (((nMode & MMD_PRINT_ALIGNMENT) == MMD_PRINT_ALIGNHLEFTVCENTER) ? AL_HLEFTVCENTER : (((nMode & MMD_PRINT_ALIGNMENT) == MMD_PRINT_ALIGNHLEFTVBOTTOM) ? AL_HLEFTVBOTTOM : (((nMode & MMD_PRINT_ALIGNMENT) == MMD_PRINT_ALIGNHCENTERVTOP) ? AL_HCENTERVTOP : (((nMode & MMD_PRINT_ALIGNMENT) == MMD_PRINT_ALIGNHCENTERVCENTER) ? AL_HCENTERVCENTER : (((nMode & MMD_PRINT_ALIGNMENT) == MMD_PRINT_ALIGNHCENTERVBOTTOM) ? AL_HCENTERVBOTTOM : (((nMode & MMD_PRINT_ALIGNMENT) == MMD_PRINT_ALIGNHRIGHTVTOP) ? AL_HRIGHTVTOP : (((nMode & MMD_PRINT_ALIGNMENT) == MMD_PRINT_ALIGNHRIGHTVCENTER) ? AL_HRIGHTVCENTER : (((nMode & MMD_PRINT_ALIGNMENT) == MMD_PRINT_ALIGNHRIGHTVBOTTOM) ? AL_HRIGHTVBOTTOM : AL_HCENTERVCENTER)))))))));
		Spinbox_SetPos(GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE_NUMBER), ((nMode & MMD_PRINT_FIXEDSCALE) && pJobInfo->GetPrintScale(nScale)) ? nScale : 0);
		GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->SetWindowText(pJobInfo->GetComments());
		GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_ADDNAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_REMOVENAME)->EnableWindow((pJobInfo->GetName() != STRING(IDS_PRINTJOB_DEFAULTNAME)) ? TRUE : FALSE);
		GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_REMOVEALLNAMES)->EnableWindow((SendDlgItemMessage(IDC_MMDSETTINGS_PRINTINGPAGE_NAME, CB_GETCOUNT) > 1) ? TRUE : FALSE);
		GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES)->EnableWindow();
		GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE_STATIC)->EnableWindow();
		GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE)->EnableWindow();
		GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_OPTIONS)->EnableWindow();
		GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_ALIGNMENT_STATIC)->EnableWindow();
		GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_ALIGNMENT)->EnableWindow();
		GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL)->EnableWindow();
		GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_NOCOLORS)->EnableWindow();
		GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT)->EnableWindow();
		GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_AUTOSCALE)->EnableWindow();
		GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE)->EnableWindow();
		GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE_NUMBER)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE));
		GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE));
		GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTS)->EnableWindow();
		GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT_STATIC)->EnableWindow();
		GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->EnableWindow();
		GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)->EnableWindow(!pJobInfo->GetComments().IsEmpty());
		return;
	}
	SendDlgItemMessage(IDC_MMDSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)-1);
	SendDlgItemMessage(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_SETCURSEL, (WPARAM)-1);
	SendDlgItemMessage(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_ALIGNMENT, CB_SETCURSEL, (WPARAM)-1);
	CheckDlgButton(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL, FALSE);
	CheckDlgButton(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_NOCOLORS, FALSE);
	CheckDlgButton(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_AUTOSCALE, FALSE);
	CheckDlgButton(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE, FALSE);
	CheckDlgButton(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS, FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->SetWindowText(EMPTYSTRING);
	GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_ADDNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_REMOVENAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_REMOVEALLNAMES)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_OPTIONS)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_ALIGNMENT_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_ALIGNMENT)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_NOCOLORS)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_AUTOSCALE)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE_NUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTS)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)->EnableWindow(FALSE);
}

CMMDPrintJobInfo *CMMDSettingsPrintingPage::FindJobInfo() CONST
{
	CString  szJobName;

	GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_NAME)->GetWindowText(szJobName);
	return m_pJobs[0].GetAt(m_pJobs[0].Find(szJobName));
}

BOOL CMMDSettingsPrintingPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? !m_pJobs[0].Compare(&m_pJobs[1]) : CLocalePropertyPage::IsModified()) : FALSE);
}

BOOL CMMDSettingsPrintingPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? ((GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_NAME)->GetWindowTextLength() > 0 && FindJobInfo()) ? TRUE : FALSE) : CLocalePropertyPage::Check()) : TRUE);
}

void CMMDSettingsPrintingPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMMDSettingsPrintingPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CMMDSettingsPrintingPage::PostNcDestroy()
{
	m_pJobs[0].RemoveAll();
	m_pJobs[1].RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CMMDSettingsPrintingPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CMMDSettingsPrintingPage)
	ON_BN_CLICKED(IDC_MMDSETTINGS_PRINTINGPAGE_ADDNAME, OnAddName)
	ON_BN_CLICKED(IDC_MMDSETTINGS_PRINTINGPAGE_REMOVENAME, OnRemoveName)
	ON_BN_CLICKED(IDC_MMDSETTINGS_PRINTINGPAGE_REMOVEALLNAMES, OnRemoveAllNames)
	ON_BN_CLICKED(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL, OnPrintUnderlineOOL)
	ON_BN_CLICKED(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_NOCOLORS, OnPrintNoColors)
	ON_BN_CLICKED(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_AUTOSCALE, OnPrintAutomaticScale)
	ON_BN_CLICKED(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE, OnPrintFixedScale)
	ON_BN_CLICKED(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS, OnResetComments)
	ON_CBN_EDITCHANGE(IDC_MMDSETTINGS_PRINTINGPAGE_NAME, OnEditchangeName)
	ON_CBN_SELCHANGE(IDC_MMDSETTINGS_PRINTINGPAGE_NAME, OnSelchangeName)
	ON_CBN_SELCHANGE(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, OnSelchangeProfile)
	ON_CBN_SELCHANGE(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_ALIGNMENT, OnSelchangePrintAdjustment)
	ON_EN_CHANGE(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT, OnEditchangeComments)
	ON_CONTROL(SBXN_CHANGE, IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE_NUMBER, OnSpinchangePrintFixedScale)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDSettingsPrintingPage message handlers

BOOL CMMDSettingsPrintingPage::OnInitDialog()
{
	INT  nJob;
	INT  nJobs;
	INT  nProfile;
	INT  nProfiles;
	CStringArray  szProfiles;
	CMMDPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	for (CLocalePropertyPage::OnInitDialog(); m_wndComments.SubclassWindow(GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->GetSafeHwnd()); )
	{
		for (nJob = 0, nJobs = (INT)m_pJobs[0].GetSize(); nJob < nJobs; nJob++)
		{
			if ((pJobInfo = m_pJobs[0].GetAt(nJob)) != (CMMDPrintJobInfo *)NULL)
			{
				SendDlgItemMessage(IDC_MMDSETTINGS_PRINTINGPAGE_NAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pJobInfo->GetName());
				continue;
			}
		}
		for (nProfile = 0, nProfiles = (EnumPrintProfiles(szProfiles)) ? (INT)szProfiles.GetSize() : 0; nProfile < nProfiles; nProfile++)
		{
			SendDlgItemMessage(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szProfiles.GetAt(nProfile));
			continue;
		}
		SendDlgItemMessage(IDC_MMDSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_MMDSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_PRINTJOB_DEFAULTNAME)));
		Spinbox_SetRange(GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE_NUMBER), MMDSETTINGSPRINTINGPAGE_MINIMUMSCALE, MMDSETTINGSPRINTINGPAGE_MAXIMUMSCALE);
		GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_DETAILS)->EnableWindow();
		GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_NAME_STATIC)->EnableWindow();
		GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_NAME)->EnableWindow();
		ShowJobInfo();
		break;
	}
	return TRUE;
}

BOOL CMMDSettingsPrintingPage::OnSetActive()
{
	ShowJobInfo();
	return CLocalePropertyPage::OnSetActive();
}

BOOL CMMDSettingsPrintingPage::OnKillActive()
{
	GetParentDialog()->OnDataExchange(GetSafeHwnd(), m_pJobs[0]);
	return CLocalePropertyPage::OnKillActive();
}

BOOL CMMDSettingsPrintingPage::OnDataExchange(CONST CMMDPrintJobs &pJobs)
{
	return m_pJobs[0].Copy(&pJobs);
}

void CMMDSettingsPrintingPage::OnEditchangeName()
{
	CString  szJobName;
	CMMDPrintJobInfo  *pJobInfo;

	for (GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_NAME)->GetWindowText(szJobName); (pJobInfo = FindJobInfo()); )
	{
		ShowJobInfo();
		return;
	}
	GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_ADDNAME)->EnableWindow((!pJobInfo  &&  szJobName.GetLength() > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_REMOVENAME)->EnableWindow((pJobInfo != (CMMDPrintJobInfo *)NULL  &&  szJobName != STRING(IDS_PRINTJOB_DEFAULTNAME)) ? TRUE : FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_REMOVEALLNAMES)->EnableWindow((SendDlgItemMessage(IDC_MMDSETTINGS_PRINTINGPAGE_NAME, CB_GETCOUNT) > 1) ? TRUE : FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)->EnableWindow((szJobName != STRING(IDS_PRINTJOB_DEFAULTNAME)) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsPrintingPage::OnSelchangeName()
{
	SendDlgItemMessage(IDC_MMDSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_MMDSETTINGS_PRINTINGPAGE_NAME, CB_GETCURSEL));
	ShowJobInfo();
}

void CMMDSettingsPrintingPage::OnAddName()
{
	INT  nIndex;
	UINT  nMode;
	UINT  nScale;
	CString  szJobName;
	CString  szProfile;
	CString  szComments;
	CMMDPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	for (; (pJobInfo = new CMMDPrintJobInfo); )
	{
		GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_NAME)->GetWindowText(szJobName);
		GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE)->GetWindowText(szProfile);
		GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->GetWindowText(szComments);
		nMode = (IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_NOCOLORS)) ? (pJobInfo->GetPrintMode() | MMD_PRINT_NOCOLORS) : (pJobInfo->GetPrintMode() & ~MMD_PRINT_NOCOLORS);
		nMode = (IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL)) ? (nMode | MMD_PRINT_UNDERLINEOOL) : (nMode & ~MMD_PRINT_UNDERLINEOOL);
		nMode = (IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_AUTOSCALE)) ? ((nMode | MMD_PRINT_AUTOSCALE) & ~MMD_PRINT_FIXEDSCALE) : nMode;
		nMode = (IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE)) ? ((nMode | MMD_PRINT_FIXEDSCALE) & ~MMD_PRINT_AUTOSCALE) : nMode;
		nMode = (IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)) ? (nMode | MMD_PRINT_CLEARCOMMENTS) : (nMode & ~MMD_PRINT_CLEARCOMMENTS);
		nScale = (IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE)) ? (UINT)Spinbox_GetPos(GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE_NUMBER)) : 0;
		switch (GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_ALIGNMENT)->SendMessage(ALCB_GETALIGNMENT, (WPARAM)GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_ALIGNMENT)->SendMessage(CB_GETCURSEL)))
		{
		case AL_HLEFTVTOP: nMode |= MMD_PRINT_ALIGNHLEFTVTOP; break;
		case AL_HLEFTVCENTER: nMode |= MMD_PRINT_ALIGNHLEFTVCENTER; break;
		case AL_HLEFTVBOTTOM: nMode |= MMD_PRINT_ALIGNHLEFTVBOTTOM; break;
		case AL_HCENTERVTOP: nMode |= MMD_PRINT_ALIGNHCENTERVTOP; break;
		case AL_HCENTERVCENTER: nMode |= MMD_PRINT_ALIGNHCENTERVCENTER; break;
		case AL_HCENTERVBOTTOM: nMode |= MMD_PRINT_ALIGNHCENTERVBOTTOM; break;
		case AL_HRIGHTVTOP: nMode |= MMD_PRINT_ALIGNHRIGHTVTOP; break;
		case AL_HRIGHTVCENTER: nMode |= MMD_PRINT_ALIGNHRIGHTVCENTER; break;
		case AL_HRIGHTVBOTTOM: nMode |= MMD_PRINT_ALIGNHRIGHTVBOTTOM; break;
		default: nMode |= MMD_PRINT_ALIGNDEFAULT; break;
		}
		if (SendDlgItemMessage(IDC_MMDSETTINGS_PRINTINGPAGE_NAME, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szJobName) >= 0 && SendDlgItemMessage(IDC_MMDSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_MMDSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szJobName)) >= 0)
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
	GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsPrintingPage::OnRemoveName()
{
	INT  nJob;
	INT  nJobs;
	CMMDPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	for (nJob = 0, nJobs = (INT)m_pJobs[0].GetSize(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = m_pJobs[0].GetAt(nJob)) && pJobInfo == FindJobInfo())
		{
			if (SendDlgItemMessage(IDC_MMDSETTINGS_PRINTINGPAGE_NAME, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_MMDSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName())) > 0)
			{
				m_pJobs[0].RemoveAt(nJob);
				delete pJobInfo;
			}
			break;
		}
	}
	for (; SendDlgItemMessage(IDC_MMDSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_MMDSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_PRINTJOB_DEFAULTNAME))) >= 0; )
	{
		ShowJobInfo();
		break;
	}
	GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsPrintingPage::OnRemoveAllNames()
{
	INT  nJob;
	INT  nJobs;
	CMMDPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	for (nJob = 0, nJobs = (INT)m_pJobs[0].GetSize(); nJob < nJobs; nJob++)
	{
		if ((pJobInfo = m_pJobs[0].GetAt(nJob)) && pJobInfo->GetName() != STRING(IDS_PRINTJOB_DEFAULTNAME) && SendDlgItemMessage(IDC_MMDSETTINGS_PRINTINGPAGE_NAME, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_MMDSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName())) > 0)
		{
			m_pJobs[0].RemoveAt(nJob);
			delete pJobInfo;
			nJobs--;
			nJob--;
		}
	}
	for (; SendDlgItemMessage(IDC_MMDSETTINGS_PRINTINGPAGE_NAME, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_MMDSETTINGS_PRINTINGPAGE_NAME, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_PRINTJOB_DEFAULTNAME))) >= 0; )
	{
		ShowJobInfo();
		break;
	}
	GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_NAME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsPrintingPage::OnSelchangeProfile()
{
	CString  szProfile;
	CMMDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE)->GetWindowText(szProfile);
		pJobInfo->SetProfile(szProfile);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsPrintingPage::OnPrintUnderlineOOL()
{
	UINT  nMode;
	CMMDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		nMode = (IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL)) ? (pJobInfo->GetPrintMode() | MMD_PRINT_UNDERLINEOOL) : (pJobInfo->GetPrintMode() & ~MMD_PRINT_UNDERLINEOOL);
		pJobInfo->SetPrintMode(nMode);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsPrintingPage::OnPrintNoColors()
{
	UINT  nMode;
	CMMDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		nMode = (IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_NOCOLORS)) ? (pJobInfo->GetPrintMode() | MMD_PRINT_NOCOLORS) : (pJobInfo->GetPrintMode() & ~MMD_PRINT_NOCOLORS);
		pJobInfo->SetPrintMode(nMode);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsPrintingPage::OnPrintAutomaticScale()
{
	CMMDPrintJobInfo  *pJobInfo;

	for (; (pJobInfo = FindJobInfo()); )
	{
		pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | MMD_PRINT_AUTOSCALE) & ~MMD_PRINT_FIXEDSCALE);
		break;
	}
	GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE_NUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsPrintingPage::OnPrintFixedScale()
{
	CMMDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | MMD_PRINT_FIXEDSCALE) & ~MMD_PRINT_AUTOSCALE);
		pJobInfo->SetPrintScale(MMDSETTINGSPRINTINGPAGE_DEFAULTSCALE);
	}
	Spinbox_SetPos(GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE_NUMBER), MMDSETTINGSPRINTINGPAGE_DEFAULTSCALE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE_NUMBER)->EnableWindow();
	GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE_NUMBER)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsPrintingPage::OnSelchangePrintAdjustment()
{
	UINT  nAlignment;
	CMMDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		switch (SendDlgItemMessage(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_ALIGNMENT, ALCB_GETALIGNMENT, (WPARAM)SendDlgItemMessage(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_ALIGNMENT, CB_GETCURSEL)))
		{
		case AL_HLEFTVTOP: nAlignment = MMD_PRINT_ALIGNHLEFTVTOP; break;
		case AL_HLEFTVCENTER: nAlignment = MMD_PRINT_ALIGNHLEFTVCENTER; break;
		case AL_HLEFTVBOTTOM: nAlignment = MMD_PRINT_ALIGNHLEFTVBOTTOM; break;
		case AL_HCENTERVTOP: nAlignment = MMD_PRINT_ALIGNHCENTERVTOP; break;
		case AL_HCENTERVCENTER: nAlignment = MMD_PRINT_ALIGNHCENTERVCENTER; break;
		case AL_HCENTERVBOTTOM: nAlignment = MMD_PRINT_ALIGNHCENTERVBOTTOM; break;
		case AL_HRIGHTVTOP: nAlignment = MMD_PRINT_ALIGNHRIGHTVTOP; break;
		case AL_HRIGHTVCENTER: nAlignment = MMD_PRINT_ALIGNHRIGHTVCENTER; break;
		case AL_HRIGHTVBOTTOM: nAlignment = MMD_PRINT_ALIGNHRIGHTVBOTTOM; break;
		default: nAlignment = MMD_PRINT_ALIGNDEFAULT; break;
		}
		pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() & ~MMD_PRINT_ALIGNMENT) | nAlignment);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsPrintingPage::OnSpinchangePrintFixedScale()
{
	CMMDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo())) pJobInfo->SetPrintScale((UINT)Spinbox_GetPos(GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTLAYOUT_FIXEDSCALE_NUMBER)));
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsPrintingPage::OnEditchangeComments()
{
	CString  szComments;
	CMMDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT)->GetWindowText(szComments);
		GetDlgItem(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)->EnableWindow(!szComments.IsEmpty());
		CheckDlgButton(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS, (!szComments.IsEmpty()) ? IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS) : FALSE);
		pJobInfo->SetPrintMode((IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)) ? (pJobInfo->GetPrintMode() | MMD_PRINT_CLEARCOMMENTS) : (pJobInfo->GetPrintMode() & ~MMD_PRINT_CLEARCOMMENTS));
		pJobInfo->SetComments(szComments);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsPrintingPage::OnResetComments()
{
	UINT  nMode;
	CMMDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		nMode = (IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)) ? (pJobInfo->GetPrintMode() | MMD_PRINT_CLEARCOMMENTS) : (pJobInfo->GetPrintMode() & ~MMD_PRINT_CLEARCOMMENTS);
		pJobInfo->SetPrintMode(nMode);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CMMDSettingsPrintJobsPage property page

IMPLEMENT_DYNCREATE(CMMDSettingsPrintJobsPage, CLocalePropertyPage)

CMMDSettingsPrintJobsPage::CMMDSettingsPrintJobsPage() : CLocalePropertyPage(CMMDSettingsPrintJobsPage::IDD)
{
	//{{AFX_DATA_INIT(CMMDSettingsPrintJobsPage)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CMMDSettingsPrintJobsPage::Initialize()
{
	CMMDOpenDialog  *pDialog;

	return((((pDialog = GetParentDialog()->GetParentDialog()) && pDialog->GetPrintJobs(m_pJobs[0])) || GetParentDisplay()->GetPrintJobs(m_pJobs[0])) ? m_pJobs[1].Copy(&m_pJobs[0]) : FALSE);
}

BOOL CMMDSettingsPrintJobsPage::GetJobs(CMMDPrintJobs &pJobs) CONST
{
	return((pJobs.Copy(&m_pJobs[0])) ? Check(FALSE) : FALSE);
}

CMMDSettingsDialog *CMMDSettingsPrintJobsPage::GetParentDialog() CONST
{
	return((CMMDSettingsDialog *)CLocalePropertyPage::GetParent());
}

CMMDWnd *CMMDSettingsPrintJobsPage::GetParentDisplay() CONST
{
	return((CMMDWnd *)GetParentDialog()->GetParentDisplay());
}

BOOL CMMDSettingsPrintJobsPage::EnumJobs()
{
	INT  nJob;
	INT  nJobs;
	UINT  nMode;
	CMMDPrintJobInfo  *pJobInfo;

	SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, LB_RESETCONTENT);
	SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_RESETCONTENT);
	for (nJob = 0, nJobs = (INT)m_pJobs[0].GetSize(); nJob < nJobs; nJob = nJob + 1)
	{
		if ((pJobInfo = m_pJobs[0].GetAt(nJob)) && pJobInfo->GetName() != STRING(IDS_PRINTJOB_DEFAULTNAME))
		{
			if (SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pJobInfo->GetName()) >= 0)
			{
				if (((nMode = pJobInfo->GetPrintMode()) & MMD_PRINT_ACTIVE) && ((nMode & MMD_PRINT_ATTIME) || (nMode & MMD_PRINT_ATDAILYTIME) || (nMode & MMD_PRINT_ATEVENT)))
				{
					if (SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR)
					{
						pJobInfo->SetPrintMode(nMode & ~(MMD_PRINT_ACTIVE | MMD_PRINT_ATTIME | MMD_PRINT_ATDAILYTIME | MMD_PRINT_ATEVENT | MMD_PRINT_REPEATBYINTERVAL | MMD_PRINT_REPEATSTOPBYCOUNT | MMD_PRINT_REPEATSTOPBYTIME | MMD_PRINT_DAILYREPEATSTOPBYCOUNT | MMD_PRINT_DAILYREPEATSTOPBYTIME));
						continue;
					}
				}
			}
		}
	}
	if (SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, LB_GETCOUNT) > 0)
	{
		SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, LB_SETCURSEL);
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_DETAILS)->EnableWindow();
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS_STATIC)->EnableWindow();
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS)->EnableWindow();
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS)->EnableWindow((SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)Listbox_GetText(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS), (INT)SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, LB_GETCURSEL))) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_REMOVEJOB)->EnableWindow((SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
		ShowJobInfo();
		return TRUE;
	}
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_DETAILS)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_REMOVEJOB)->EnableWindow(FALSE);
	ShowJobInfo();
	return FALSE;
}

BOOL CMMDSettingsPrintJobsPage::EnumEvents()
{
	INT  nEvent;
	INT  nEvents;
	CTelemetryEvents  pEvents;
	CTelemetryEventInfo  *pEventInfo;

	for (nEvent = 0, nEvents = (GetTelemetryEvents(pEvents)) ? (INT)pEvents.GetSize() : 0; nEvent < nEvents; nEvent++)
	{
		if ((pEventInfo = pEvents.GetAt(nEvent))) SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pEventInfo->GetName());
		continue;
	}
	return((SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CMMDSettingsPrintJobsPage::ShowJobInfo()
{
	UINT  nStopCount;
	CString  szEvent;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CTimeSpan  tDailyTime;
	CMMDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		Timespinbox_SetTime(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME), (pJobInfo->GetPrintAtTime(tTime) || pJobInfo->GetPrintAtTime(tTime, tInterval) || pJobInfo->GetPrintAtTime(tTime, tInterval, nStopCount) || pJobInfo->GetPrintAtTime(tTime, tInterval, tStopTime)) ? tTime : CTime::GetCurrentTime().GetTime());
		Timespinbox_SetTime(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME), (pJobInfo->GetPrintAtDailyTime(tDailyTime) || pJobInfo->GetPrintAtDailyTime(tDailyTime, nStopCount) || pJobInfo->GetPrintAtDailyTime(tDailyTime, tStopTime)) ? CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + tDailyTime.GetTotalSeconds()) : CTime::GetCurrentTime().GetTime());
		SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_SETCURSEL, (pJobInfo->GetPrintAtEvent(szEvent)) ? (WPARAM)SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szEvent) : (WPARAM)-1);
		SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, (SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_MMDSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS)) < 0 && (pJobInfo->GetPrintMode() & MMD_PRINT_ATTIME)) ? CB_ADDSTRING : CB_FINDSTRING, (WPARAM)NULL, (LPARAM)STRING(IDS_MMDSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS));
		SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, (SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_MMDSETTINGS_PRINTJOBSPAGE_DAILYPRINTS)) < 0 && (pJobInfo->GetPrintMode() & MMD_PRINT_ATDAILYTIME)) ? CB_ADDSTRING : CB_FINDSTRING, (WPARAM)NULL, (LPARAM)STRING(IDS_MMDSETTINGS_PRINTJOBSPAGE_DAILYPRINTS));
		SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_SETCURSEL, ((pJobInfo->GetPrintMode() & MMD_PRINT_ATTIME) || (pJobInfo->GetPrintMode() & MMD_PRINT_ATDAILYTIME)) ? (WPARAM)SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)((pJobInfo->GetPrintMode() & MMD_PRINT_ATTIME) ? STRING(IDS_MMDSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS) : STRING(IDS_MMDSETTINGS_PRINTJOBSPAGE_DAILYPRINTS))) : (WPARAM)-1);
		CheckDlgButton(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME, (pJobInfo->GetPrintMode() & MMD_PRINT_ATTIME) ? TRUE : FALSE);
		CheckDlgButton(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME, (pJobInfo->GetPrintMode() & MMD_PRINT_ATDAILYTIME) ? TRUE : FALSE);
		CheckDlgButton(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT, (pJobInfo->GetPrintMode() & MMD_PRINT_ATEVENT) ? ((SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_GETCURSEL) >= 0) ? TRUE : FALSE) : FALSE);
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR)->EnableWindow();
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME)->EnableWindow();
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME));
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)->EnableWindow();
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT)->EnableWindow((SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT));
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT));
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		SetJobRepetitionInfo();
		return;
	}
	CheckDlgButton(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME, FALSE);
	CheckDlgButton(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME, FALSE);
	CheckDlgButton(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT, FALSE);
	CheckDlgButton(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME, FALSE);
	CheckDlgButton(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, FALSE);
	CheckDlgButton(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, FALSE);
	SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_SETCURSEL, (WPARAM)-1);
	SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_SETCURSEL, (WPARAM)-1);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow(FALSE);
}

BOOL CMMDSettingsPrintJobsPage::CheckJobInfo() CONST
{
	UINT  nStopCount;
	CString  szEvent;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CTimeSpan  tDailyTime;
	CMMDPrintJobInfo  *pJobInfo;

	return(((pJobInfo = FindJobInfo())) ? ((pJobInfo->GetPrintAtTime(tTime) && tTime > CTime::GetCurrentTime()) || pJobInfo->GetPrintAtTime(tTime, tInterval) || (pJobInfo->GetPrintAtTime(tTime, tInterval, nStopCount) && tTime.GetTime() + tInterval.GetTotalSeconds()*(TIMEKEY)nStopCount > CTime::GetCurrentTime().GetTime()) || (pJobInfo->GetPrintAtTime(tTime, tInterval, tStopTime) && tStopTime > CTime::GetCurrentTime()) || pJobInfo->GetPrintAtDailyTime(tDailyTime) || pJobInfo->GetPrintAtDailyTime(tDailyTime, nStopCount) || (pJobInfo->GetPrintAtDailyTime(tDailyTime, tStopTime) && tStopTime > CTime::GetCurrentTime()) || pJobInfo->GetPrintAtEvent(szEvent)) : FALSE);
}

CMMDPrintJobInfo *CMMDSettingsPrintJobsPage::FindJobInfo(BOOL bActive) CONST
{
	INT  nJob;
	INT  nJobs;
	CString  szJobName[2];
	CMMDPrintJobInfo  *pJobInfo;

	for (nJob = 0, nJobs = (INT)m_pJobs[0].GetSize(), szJobName[0] = Listbox_GetText(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS), (INT)GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS)->SendMessage(LB_GETCURSEL)), szJobName[1] = Listbox_GetText(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS), (INT)GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS)->SendMessage(LB_GETCURSEL)), szJobName[0] = (!bActive) ? szJobName[0] : szJobName[1]; nJob < nJobs; nJob++)
	{
		if ((pJobInfo = m_pJobs[0].GetAt(nJob)) && pJobInfo->GetName() == szJobName[0]) break;
		continue;
	}
	return((nJob < nJobs) ? pJobInfo : (CMMDPrintJobInfo *)NULL);
}

VOID CMMDSettingsPrintJobsPage::SetJobRepetitionInfo()
{
	UINT  nStopCount;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CTimeSpan  tDailyTime;
	CMMDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		Timespinbox_SetTime(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), ((GetJobRepetitionType() == MMDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  pJobInfo->GetPrintAtTime(tTime, tInterval, tStopTime)) || (GetJobRepetitionType() == MMDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  pJobInfo->GetPrintAtDailyTime(tDailyTime, tStopTime))) ? tStopTime : CTime::GetCurrentTime().GetTime());
		Spinbox_SetPos(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME), (pJobInfo->GetPrintAtTime(tTime, tInterval) || pJobInfo->GetPrintAtTime(tTime, tInterval, nStopCount) || pJobInfo->GetPrintAtTime(tTime, tInterval, tStopTime)) ? (tInterval.GetTotalSeconds() / SECONDSPERMINUTE) : 0);
		Spinbox_SetPos(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), ((GetJobRepetitionType() == MMDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  pJobInfo->GetPrintAtTime(tTime, tInterval, nStopCount)) || (GetJobRepetitionType() == MMDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  pJobInfo->GetPrintAtDailyTime(tDailyTime, nStopCount))) ? nStopCount : 0);
		CheckDlgButton(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME, (GetJobRepetitionType() == MMDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY && (pJobInfo->GetPrintMode() & MMD_PRINT_REPEATBYINTERVAL)) ? TRUE : FALSE);
		CheckDlgButton(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, ((GetJobRepetitionType() == MMDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY && (pJobInfo->GetPrintMode() & MMD_PRINT_REPEATSTOPBYCOUNT)) || (GetJobRepetitionType() == MMDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY && (pJobInfo->GetPrintMode() & MMD_PRINT_DAILYREPEATSTOPBYCOUNT))) ? TRUE : FALSE);
		CheckDlgButton(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, ((GetJobRepetitionType() == MMDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY && (pJobInfo->GetPrintMode() & MMD_PRINT_REPEATSTOPBYTIME)) || (GetJobRepetitionType() == MMDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY && (pJobInfo->GetPrintMode() & MMD_PRINT_DAILYREPEATSTOPBYTIME))) ? TRUE : FALSE);
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)->EnableWindow((GetJobRepetitionType() == MMDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY) ? TRUE : FALSE);
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)->EnableWindow(GetJobRepetitionType() == MMDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC)->EnableWindow(GetJobRepetitionType() == MMDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC)->EnableWindow((IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && (GetJobRepetitionType() == MMDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY || IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)));
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)->EnableWindow((IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && (GetJobRepetitionType() == MMDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY || IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)));
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow((IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES));
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow((IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES));
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)->EnableWindow((IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && (GetJobRepetitionType() == MMDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY || IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)));
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow((IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME));
		return;
	}
	CheckDlgButton(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME, FALSE);
	CheckDlgButton(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, FALSE);
	CheckDlgButton(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow(FALSE);
}

UINT CMMDSettingsPrintJobsPage::GetJobRepetitionType() CONST
{
	CString  szRepetitionType;

	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE)->GetWindowText(szRepetitionType);
	return((szRepetitionType == STRING(IDS_MMDSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS) || szRepetitionType == STRING(IDS_MMDSETTINGS_PRINTJOBSPAGE_DAILYPRINTS)) ? ((szRepetitionType == STRING(IDS_MMDSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS)) ? MMDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY : MMDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY) : 0);
}

BOOL CMMDSettingsPrintJobsPage::IsModified(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? !m_pJobs[0].Compare(&m_pJobs[1]) : CLocalePropertyPage::IsModified()) : FALSE);
}

BOOL CMMDSettingsPrintJobsPage::Check(BOOL bAll) CONST
{
	return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? TRUE : CLocalePropertyPage::Check()) : TRUE);
}

void CMMDSettingsPrintJobsPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMMDSettingsPrintJobsPage)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CMMDSettingsPrintJobsPage::PostNcDestroy()
{
	m_pJobs[0].RemoveAll();
	m_pJobs[1].RemoveAll();
	CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CMMDSettingsPrintJobsPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CMMDSettingsPrintJobsPage)
	ON_BN_CLICKED(IDC_MMDSETTINGS_PRINTJOBSPAGE_ADDJOB, OnAddJob)
	ON_BN_CLICKED(IDC_MMDSETTINGS_PRINTJOBSPAGE_REMOVEJOB, OnRemoveJob)
	ON_BN_CLICKED(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME, OnPrintAtTime)
	ON_BN_CLICKED(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME, OnPrintAtDailyTime)
	ON_BN_CLICKED(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT, OnPrintAtEvent)
	ON_BN_CLICKED(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME, OnRepeatByTime)
	ON_BN_CLICKED(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, OnRepetitionStopByCopies)
	ON_BN_CLICKED(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, OnRepetitionStopByTime)
	ON_CBN_SELCHANGE(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, OnSelchangeEvent)
	ON_CBN_SELCHANGE(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, OnSelchangeRepetitionType)
	ON_LBN_SELCHANGE(IDC_MMDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS, OnSelchangeDefinedJob)
	ON_LBN_SELCHANGE(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, OnSelchangeActiveJob)
	ON_CONTROL(SBXN_CHANGE, IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME, OnSpinchangeRepeatTime)
	ON_CONTROL(SBXN_CHANGE, IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES, OnSpinchangeRepetitionStopCopies)
	ON_CONTROL(TSBXN_CHANGE, IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME, OnSpinchangePrintTime)
	ON_CONTROL(TSBXN_CHANGE, IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME, OnSpinchangePrintDailyTime)
	ON_CONTROL(TSBXN_CHANGE, IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME, OnSpinchangeRepetitionStopTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDSettingsPrintJobsPage message handlers

BOOL CMMDSettingsPrintJobsPage::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CLocalePropertyPage::OnInitDialog();
	Spinbox_SetRange(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME), MMDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMINTERVAL, MMDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMINTERVAL);
	Spinbox_SetRange(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), MMDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES, MMDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES);
	EnumEvents();
	return TRUE;
}

BOOL CMMDSettingsPrintJobsPage::OnSetActive()
{
	EnumJobs();
	return CLocalePropertyPage::OnSetActive();
}

BOOL CMMDSettingsPrintJobsPage::OnKillActive()
{
	GetParentDialog()->OnDataExchange(GetSafeHwnd(), m_pJobs[0]);
	return CLocalePropertyPage::OnKillActive();
}

BOOL CMMDSettingsPrintJobsPage::OnDataExchange(CONST CMMDPrintJobs &pJobs)
{
	return m_pJobs[0].Copy(&pJobs);
}

void CMMDSettingsPrintJobsPage::OnAddJob()
{
	CMMDPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	if ((pJobInfo = FindJobInfo()))
	{
		pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() | MMD_PRINT_ACTIVE);
		SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)pJobInfo->GetName());
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS)->EnableWindow((SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow(FALSE);
	}
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsPrintJobsPage::OnRemoveJob()
{
	CMMDPrintJobInfo  *pJobInfo;
	CHourglassCursor  cCursor;

	if ((pJobInfo = FindJobInfo(TRUE)))
	{
		for (pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~(MMD_PRINT_ACTIVE | MMD_PRINT_ATTIME | MMD_PRINT_ATDAILYTIME | MMD_PRINT_ATEVENT | MMD_PRINT_REPEATBYINTERVAL | MMD_PRINT_REPEATSTOPBYCOUNT | MMD_PRINT_REPEATSTOPBYTIME | MMD_PRINT_DAILYREPEATSTOPBYCOUNT | MMD_PRINT_DAILYREPEATSTOPBYTIME)), SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCURSEL)); pJobInfo == FindJobInfo(); )
		{
			ShowJobInfo();
			break;
		}
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS)->EnableWindow((SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_REMOVEJOB)->EnableWindow(FALSE);
	}
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsPrintJobsPage::OnSelchangeDefinedJob()
{
	CMMDPrintJobInfo  *pJobInfo;

	ShowJobInfo();
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow(((pJobInfo = FindJobInfo()) && SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
}

void CMMDSettingsPrintJobsPage::OnSelchangeActiveJob()
{
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_REMOVEJOB)->EnableWindow();
}

void CMMDSettingsPrintJobsPage::OnPrintAtTime()
{
	CTimeKey  tTime;
	CMMDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		if (IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME))
		{
			Timespinbox_SetTime(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME), (tTime = CTime::GetCurrentTime().GetTime() + SECONDSPERMINUTE*MMDSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL));
			SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)STRING(IDS_MMDSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS));
			pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | MMD_PRINT_ATTIME) & ~(MMD_PRINT_REPEATBYINTERVAL | MMD_PRINT_REPEATSTOPBYCOUNT | MMD_PRINT_REPEATSTOPBYTIME));
			pJobInfo->SetPrintAtTime(tTime);
		}
		else
		{
			SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_MMDSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS)));
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~(MMD_PRINT_ATTIME | MMD_PRINT_REPEATBYINTERVAL | MMD_PRINT_REPEATSTOPBYCOUNT | MMD_PRINT_REPEATSTOPBYTIME));
		}
		SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_SETCURSEL, (IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) ? (WPARAM)SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)((IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME)) ? STRING(IDS_MMDSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS) : STRING(IDS_MMDSETTINGS_PRINTJOBSPAGE_DAILYPRINTS))) : (WPARAM)-1);
		Spinbox_SetRange(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), (IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME)) ? (MMDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES + 1) : MMDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES, MMDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES);
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME));
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		SetJobRepetitionInfo();
	}
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsPrintJobsPage::OnPrintAtDailyTime()
{
	CTimeKey  tTime;
	CMMDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		if (IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME))
		{
			Timespinbox_SetTime(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME), (tTime = CTime::GetCurrentTime().GetTime() + SECONDSPERMINUTE*MMDSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL));
			SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)STRING(IDS_MMDSETTINGS_PRINTJOBSPAGE_DAILYPRINTS));
			pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | MMD_PRINT_ATDAILYTIME) & ~(MMD_PRINT_DAILYREPEATSTOPBYCOUNT | MMD_PRINT_DAILYREPEATSTOPBYTIME));
			pJobInfo->SetPrintAtDailyTime(tTime.GetTime() % SECONDSPERDAY);
		}
		else
		{
			SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)STRING(IDS_MMDSETTINGS_PRINTJOBSPAGE_DAILYPRINTS)));
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~(MMD_PRINT_ATDAILYTIME | MMD_PRINT_DAILYREPEATSTOPBYCOUNT | MMD_PRINT_DAILYREPEATSTOPBYTIME));
		}
		SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_SETCURSEL, (IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) ? (WPARAM)SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)((IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) ? STRING(IDS_MMDSETTINGS_PRINTJOBSPAGE_DAILYPRINTS) : STRING(IDS_MMDSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS))) : (WPARAM)-1);
		Spinbox_SetRange(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), (IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) ? MMDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES : (MMDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES + 1), MMDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES);
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) || IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		SetJobRepetitionInfo();
	}
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsPrintJobsPage::OnPrintAtEvent()
{
	CString  szEvent;
	CMMDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		if (IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT))
		{
			SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_SETCURSEL);
			GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT)->GetWindowText(szEvent);
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() | MMD_PRINT_ATEVENT);
			pJobInfo->SetPrintAtEvent(szEvent);
		}
		else
		{
			SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT, CB_SETCURSEL, (WPARAM)-1);
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~MMD_PRINT_ATEVENT);
			pJobInfo->SetPrintAtEvent(EMPTYSTRING);
		}
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT));
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT));
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsPrintJobsPage::OnSelchangeEvent()
{
	CString  szEvent;
	CMMDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT)->GetWindowText(szEvent);
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() | MMD_PRINT_ATEVENT);
		pJobInfo->SetPrintAtEvent(szEvent);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsPrintJobsPage::OnSelchangeRepetitionType()
{
	Spinbox_SetRange(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), (GetJobRepetitionType() == MMDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY) ? (MMDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES + 1) : MMDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES, MMDSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES);
	SetJobRepetitionInfo();
}

void CMMDSettingsPrintJobsPage::OnRepeatByTime()
{
	CMMDPrintJobInfo  *pJobInfo;

	for (CheckDlgButton(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME, !IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)); IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME); )
	{
		Spinbox_SetPos(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME), MMDSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL);
		break;
	}
	for (; (pJobInfo = FindJobInfo()); )
	{
		if (IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME))
		{
			pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | MMD_PRINT_REPEATBYINTERVAL) & ~(MMD_PRINT_REPEATSTOPBYCOUNT | MMD_PRINT_REPEATSTOPBYTIME));
			pJobInfo->SetPrintAtTime(Timespinbox_GetTime(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), SECONDSPERMINUTE*MMDSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL);
			GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
			break;
		}
		pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~(MMD_PRINT_REPEATBYINTERVAL | MMD_PRINT_REPEATSTOPBYCOUNT | MMD_PRINT_REPEATSTOPBYTIME));
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		break;
	}
	CheckDlgButton(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, FALSE);
	CheckDlgButton(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsPrintJobsPage::OnRepetitionStopByCopies()
{
	CMMDPrintJobInfo  *pJobInfo;

	for (CheckDlgButton(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, !IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)), GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)), GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)); IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES); )
	{
		Spinbox_SetPos(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES), MMDSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTCOPIES);
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow(FALSE);
		CheckDlgButton(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, FALSE);
		break;
	}
	for (; (pJobInfo = FindJobInfo()); )
	{
		if (IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES))
		{
			if (GetJobRepetitionType() == MMDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY)
			{
				pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | MMD_PRINT_REPEATSTOPBYCOUNT) & ~MMD_PRINT_REPEATSTOPBYTIME);
				pJobInfo->SetPrintAtTime(Timespinbox_GetTime(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)), MMDSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTCOPIES);
			}
			if (GetJobRepetitionType() == MMDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY)
			{
				pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | MMD_PRINT_DAILYREPEATSTOPBYCOUNT) & ~MMD_PRINT_DAILYREPEATSTOPBYTIME);
				pJobInfo->SetPrintAtDailyTime(Timespinbox_GetTime(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)).GetTime() % SECONDSPERDAY, MMDSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTCOPIES);
			}
			GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
			break;
		}
		pJobInfo->SetPrintMode((GetJobRepetitionType() == MMDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY) ? (pJobInfo->GetPrintMode() & ~MMD_PRINT_REPEATSTOPBYCOUNT) : (pJobInfo->GetPrintMode() & ~MMD_PRINT_DAILYREPEATSTOPBYCOUNT));
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		break;
	}
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsPrintJobsPage::OnRepetitionStopByTime()
{
	CTimeKey  tStopTime;
	CMMDPrintJobInfo  *pJobInfo;

	for (CheckDlgButton(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME, !IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)), GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)); IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME); )
	{
		for (CheckDlgButton(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES, FALSE); GetJobRepetitionType() == MMDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY; )
		{
			Timespinbox_SetTime(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)).GetTime() + SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME))));
			break;
		}
		if (GetJobRepetitionType() == MMDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY) Timespinbox_SetTime(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)).GetTime() + CTimeSpan(1, 0, 0, 0).GetTotalSeconds()));
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)->EnableWindow(FALSE);
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC)->EnableWindow(FALSE);
		break;
	}
	for (; (pJobInfo = FindJobInfo()); )
	{
		if (IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME))
		{
			if (GetJobRepetitionType() == MMDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY)
			{
				pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | MMD_PRINT_REPEATSTOPBYTIME) & ~MMD_PRINT_REPEATSTOPBYCOUNT);
				pJobInfo->SetPrintAtTime(Timespinbox_GetTime(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)), tStopTime);
			}
			if (GetJobRepetitionType() == MMDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY)
			{
				pJobInfo->SetPrintMode((pJobInfo->GetPrintMode() | MMD_PRINT_DAILYREPEATSTOPBYTIME) & ~MMD_PRINT_DAILYREPEATSTOPBYCOUNT);
				pJobInfo->SetPrintAtDailyTime(Timespinbox_GetTime(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)).GetTime() % SECONDSPERDAY, tStopTime);
			}
			GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
			break;
		}
		pJobInfo->SetPrintMode((GetJobRepetitionType() == MMDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY) ? (pJobInfo->GetPrintMode() & ~MMD_PRINT_REPEATSTOPBYTIME) : (pJobInfo->GetPrintMode() & ~MMD_PRINT_DAILYREPEATSTOPBYTIME));
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
		break;
	}
	GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsPrintJobsPage::OnSpinchangePrintTime()
{
	UINT  nStopCount;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeKey  tPrintTime;
	CTimeKey  tPrintStopTime;
	CTimeSpan  tPrintInterval;
	CMMDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)); pJobInfo->GetPrintAtTime(tPrintTime); )
		{
			pJobInfo->SetPrintAtTime(tTime);
			break;
		}
		if (pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval)) pJobInfo->SetPrintAtTime(tTime, tPrintInterval);
		if (pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, nStopCount)) pJobInfo->SetPrintAtTime(tTime, tPrintInterval, nStopCount);
		if (pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, tPrintStopTime)) pJobInfo->SetPrintAtTime(tTime, tPrintInterval, (tTime + tPrintInterval.GetTotalSeconds() > tPrintStopTime.GetTime()) ? CTimeKey(tTime.GetTime() + tPrintInterval.GetTotalSeconds()) : tPrintStopTime);
		Timespinbox_SetTime(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (GetJobRepetitionType() == MMDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)) ? ((tTime + tPrintInterval.GetTotalSeconds() > tPrintStopTime.GetTime()) ? (tTime.GetTime() + tPrintInterval.GetTotalSeconds()) : tPrintStopTime) : tStopTime);
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsPrintJobsPage::OnSpinchangePrintDailyTime()
{
	UINT  nStopCount;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeKey  tPrintStopTime;
	CTimeSpan  tPrintTime;
	CMMDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)), tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)); pJobInfo->GetPrintAtDailyTime(tPrintTime); )
		{
			pJobInfo->SetPrintAtDailyTime(tTime.GetTime() % SECONDSPERDAY);
			break;
		}
		if (pJobInfo->GetPrintAtDailyTime(tPrintTime, nStopCount)) pJobInfo->SetPrintAtDailyTime(tTime.GetTime() % SECONDSPERDAY, nStopCount);
		if (pJobInfo->GetPrintAtDailyTime(tPrintTime, tPrintStopTime)) pJobInfo->SetPrintAtDailyTime(tTime.GetTime() % SECONDSPERDAY, (SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + tTime.GetTime() % SECONDSPERDAY > tPrintStopTime.GetTime()) ? CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY + 1) + tTime.GetTime() % SECONDSPERDAY) : tPrintStopTime);
		Timespinbox_SetTime(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (GetJobRepetitionType() == MMDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)) ? ((SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + tTime.GetTime() % SECONDSPERDAY > tPrintStopTime.GetTime()) ? CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY + 1) + tTime.GetTime() % SECONDSPERDAY) : tPrintStopTime) : tStopTime);
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsPrintJobsPage::OnSpinchangeRepeatTime()
{
	UINT  nStopCount;
	CTimeKey  tTime;
	CTimeKey  tStopTime;
	CTimeKey  tPrintTime;
	CTimeKey  tPrintStopTime;
	CTimeSpan  tPrintInterval;
	CMMDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)); pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval); )
		{
			pJobInfo->SetPrintAtTime(tPrintTime, SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)));
			break;
		}
		if (pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, nStopCount)) pJobInfo->SetPrintAtTime(tPrintTime, SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)), nStopCount);
		if (pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, tPrintStopTime)) pJobInfo->SetPrintAtTime(tPrintTime, SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)), (tPrintTime.GetTime() + SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)) > tPrintStopTime.GetTime()) ? CTimeKey(tPrintTime.GetTime() + SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME))) : tPrintStopTime);
		Timespinbox_SetTime(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (GetJobRepetitionType() == MMDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  IsDlgButtonChecked(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)) ? ((tPrintTime.GetTime() + SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)) > tPrintStopTime.GetTime()) ? CTimeKey(tPrintTime.GetTime() + SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME))) : tPrintStopTime) : tStopTime);
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsPrintJobsPage::OnSpinchangeRepetitionStopCopies()
{
	UINT  nStopCount;
	UINT  nPrintStopCount;
	CTimeKey  tPrintTime;
	CTimeSpan  tPrintInterval;
	CTimeSpan  tPrintDailyTime;
	CMMDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (nStopCount = (UINT)Spinbox_GetPos(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)); GetJobRepetitionType() == MMDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY && pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, nPrintStopCount); )
		{
			pJobInfo->SetPrintAtTime(tPrintTime, tPrintInterval, nStopCount);
			break;
		}
		if (GetJobRepetitionType() == MMDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  pJobInfo->GetPrintAtDailyTime(tPrintDailyTime, nPrintStopCount)) pJobInfo->SetPrintAtDailyTime(tPrintDailyTime, nStopCount);
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDSettingsPrintJobsPage::OnSpinchangeRepetitionStopTime()
{
	CTimeKey  tTime;
	CTimeKey  tTimeKey;
	CTimeKey  tStopTime;
	CTimeKey  tPrintTime;
	CTimeKey  tPrintStopTime;
	CTimeSpan  tPrintInterval;
	CTimeSpan  tPrintDailyTime;
	CMMDPrintJobInfo  *pJobInfo;

	if ((pJobInfo = FindJobInfo()))
	{
		for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)), tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)); GetJobRepetitionType() == MMDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY && pJobInfo->GetPrintAtTime(tPrintTime, tPrintInterval, tPrintStopTime); )
		{
			if (tTime > tStopTime.GetTime() - tPrintInterval.GetTotalSeconds()) Timespinbox_SetTime(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (tStopTime = tTime.GetTime() + tPrintInterval.GetTotalSeconds()));
			pJobInfo->SetPrintAtTime(tTime, tPrintInterval, tStopTime);
			break;
		}
		if (GetJobRepetitionType() == MMDSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  pJobInfo->GetPrintAtDailyTime(tPrintDailyTime, tPrintStopTime))
		{
			if (SECONDSPERDAY*(tTimeKey.GetTime() / SECONDSPERDAY) + tPrintDailyTime.GetTotalSeconds() > tStopTime.GetTime()) Timespinbox_SetTime(GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME), (tStopTime = SECONDSPERDAY*(tTimeKey.GetTime() / SECONDSPERDAY) + tPrintDailyTime.GetTotalSeconds()));
			pJobInfo->SetPrintAtDailyTime(tPrintDailyTime, tStopTime);
		}
		GetDlgItem(IDC_MMDSETTINGS_PRINTJOBSPAGE_ADDJOB)->EnableWindow((SendDlgItemMessage(IDC_MMDSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)pJobInfo->GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE : FALSE);
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CMMDSettingsTabCtrl

IMPLEMENT_DYNCREATE(CMMDSettingsTabCtrl, CTabCtrl)

BEGIN_MESSAGE_MAP(CMMDSettingsTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CMMDSettingsTabCtrl)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDSettingsTabCtrl message handlers


/////////////////////////////////////////////////////////////////////////////
// CMMDSettingsDialog

IMPLEMENT_DYNCREATE(CMMDSettingsDialog, CDisplayPropertySheetDialog)

CMMDSettingsDialog::CMMDSettingsDialog() : CDisplayPropertySheetDialog()
{
	AddPage(&m_pageLayout);
	AddPage(&m_pageRetrieving);
	AddPage(&m_pagePrinting);
	AddPage(&m_pagePrintJobs);
}

BOOL CMMDSettingsDialog::GetLayout(CMMDLayout &cLayout) CONST
{
	return m_pageLayout.GetLayout(cLayout);
}

BOOL CMMDSettingsDialog::GetLayoutInvalidDataMode(BOOL &bEnable) CONST
{
	return m_pageLayout.GetInvalidDataMode(bEnable);
}

BOOL CMMDSettingsDialog::GetLayoutBadDataMode(BOOL &bEnable) CONST
{
	return m_pageLayout.GetBadDataMode(bEnable);
}

BOOL CMMDSettingsDialog::GetLayoutToolTipMode(BOOL &bEnable) CONST
{
	return m_pageLayout.GetToolTipMode(bEnable);
}

BOOL CMMDSettingsDialog::IsLayoutModified() CONST
{
	return m_pageLayout.IsModified();
}

BOOL CMMDSettingsDialog::GetRetrieveFileName(CString &szFileName) CONST
{
	return m_pageRetrieving.GetDataSourceFileName(szFileName);
}

BOOL CMMDSettingsDialog::IsRetrievingModified() CONST
{
	return m_pageRetrieving.IsModified();
}

BOOL CMMDSettingsDialog::GetPrintJobs(CMMDPrintJobs &pPrintJobs) CONST
{
	return(((GetActivePage()->GetSafeHwnd() != m_pagePrintJobs.GetSafeHwnd() && m_pagePrinting.GetJobs(pPrintJobs)) || (GetActivePage()->GetSafeHwnd() == m_pagePrintJobs.GetSafeHwnd() && m_pagePrintJobs.GetJobs(pPrintJobs))) ? TRUE : FALSE);
}

BOOL CMMDSettingsDialog::IsPrintingModified() CONST
{
	return m_pagePrinting.IsModified() || m_pagePrintJobs.IsModified();
}

CMMDOpenDialog *CMMDSettingsDialog::GetParentDialog() CONST
{
	return((GetParent() != (CWnd *)GetParentDisplay()) ? (CMMDOpenDialog *)GetParent() : (CMMDOpenDialog *)NULL);
}

CMMDWnd *CMMDSettingsDialog::GetParentDisplay() CONST
{
	return((CMMDWnd *)CDisplayPropertySheetDialog::GetParentDisplay());
}

BEGIN_MESSAGE_MAP(CMMDSettingsDialog, CDisplayPropertySheetDialog)
	//{{AFX_MSG_MAP(CMMDSettingsDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDHELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDSettingsDialog message handlers

BOOL CMMDSettingsDialog::OnInitDialog()
{
	INT  nPage;
	INT  nPages;
	CHourglassCursor  cCursor;

	CDisplayPropertySheetDialog::OnInitDialog();
	SetTitle(STRING(IDS_MMDSETTINGSDIALOG_TITLE));
	for (nPage = 0, nPages = GetPageCount(), m_wndTabCtrl.SubclassWindow(GetTabControl()->GetSafeHwnd()); nPage < nPages; nPage++)
	{
		SetActivePage((nPage + 1) % nPages);
		continue;
	}
	m_wndTabCtrl.SetFocus();
	return FALSE;
}

BOOL CMMDSettingsDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	CRect  rTab;
	CMMDPrintJobs  pPrintJobs;
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

BOOL CMMDSettingsDialog::OnDataExchange(HWND hPage, CONST CMMDPrintJobs &pJobs)
{
	return(((hPage == m_pagePrinting.GetSafeHwnd() && m_pagePrintJobs.OnDataExchange(pJobs)) || (hPage == m_pagePrintJobs.GetSafeHwnd() && m_pagePrinting.OnDataExchange(pJobs))) ? TRUE : FALSE);
}

void CMMDSettingsDialog::OnOK()
{
	CHourglassCursor  cCursor;

	ReportEvent(((!GetParentDialog() && !GetParentDisplay()->OnCloseSettingsDialog(IDOK)) || (GetParentDialog() && !GetParentDialog()->OnCloseSettingsDialog(IDOK))) ? SYSTEM_WARNING_MMD_SETUP_FAILURE : SYSTEM_NOERROR);
	CDisplayPropertySheetDialog::OnOK();
}

void CMMDSettingsDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	if (!GetParentDialog()) GetParentDisplay()->OnCloseSettingsDialog(IDCANCEL);
	else  GetParentDialog()->OnCloseSettingsDialog(IDCANCEL);
	CDisplayPropertySheetDialog::OnCancel();
}

BOOL CMMDSettingsDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_MMDSETTINGSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CMMDSettingsDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_MMDSETTINGSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CMMDLinkagesDialog dialog

IMPLEMENT_DYNCREATE(CMMDLinkagesDialog, CDisplayDialog)

CMMDLinkagesDialog::CMMDLinkagesDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CMMDLinkagesDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CMMDLinkagesDialog::Create(CWnd *pParentWnd)
{
	return CDisplayDialog::Create(pParentWnd, CMMDLinkagesDialog::IDD);
}

BOOL CMMDLinkagesDialog::Initialize()
{
	GetDisplayArea()->EnumDisplays(m_pDisplays[0]);
	GetParent()->GetLinks(m_pDisplays[1]);
	return TRUE;
}

CMMDWnd *CMMDLinkagesDialog::GetParent() CONST
{
	return((CMMDWnd *)CDisplayDialog::GetParent());
}

BOOL CMMDLinkagesDialog::EnumDisplays()
{
	INT  nDisplay[2];
	INT  nDisplays[2];
	CString  szDisplay;
	CDisplayWnd  *pDisplayWnd;

	for (nDisplay[0] = 0, nDisplays[0] = (INT)m_pDisplays[0].GetSize(), SendDlgItemMessage(IDC_MMD_LINKAGES_DISPLAYS, CB_RESETCONTENT), SendDlgItemMessage(IDC_MMD_LINKAGES_LIST, LB_RESETCONTENT); nDisplay[0] < nDisplays[0]; nDisplay[0]++)
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
			for (pDisplayWnd->GetWindowText(szDisplay); SendDlgItemMessage(IDC_MMD_LINKAGES_DISPLAYS, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szDisplay) < 0 && !szDisplay.IsEmpty(); )
			{
				SendDlgItemMessage(IDC_MMD_LINKAGES_DISPLAYS, CB_INSERTSTRING, nDisplay[0], (LPARAM)(LPCTSTR)szDisplay);
				break;
			}
		}
	}
	for (nDisplay[1] = 0, nDisplays[1] = (INT)m_pDisplays[1].GetSize(), m_pDisplays[2].Copy(m_pDisplays[1]); nDisplay[1] < nDisplays[1]; nDisplay[1]++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)m_pDisplays[1].GetAt(nDisplay[1])) != (CDisplayWnd *)NULL)
		{
			for (pDisplayWnd->GetWindowText(szDisplay); SendDlgItemMessage(IDC_MMD_LINKAGES_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szDisplay) < 0 && !szDisplay.IsEmpty(); )
			{
				SendDlgItemMessage(IDC_MMD_LINKAGES_LIST, LB_INSERTSTRING, nDisplay[1], (LPARAM)(LPCTSTR)szDisplay);
				break;
			}
		}
	}
	SendDlgItemMessage(IDC_MMD_LINKAGES_LIST, LB_SETCURSEL);
	SendDlgItemMessage(IDC_MMD_LINKAGES_DISPLAYS, CB_SETCURSEL);
	GetDlgItem(IDC_MMD_LINKAGES_DISPLAYS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MMD_LINKAGES_DISPLAYS, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_LINKAGES_DISPLAYS)->EnableWindow((SendDlgItemMessage(IDC_MMD_LINKAGES_DISPLAYS, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_LINKAGES_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MMD_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_LINKAGES_LIST)->EnableWindow((SendDlgItemMessage(IDC_MMD_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_LINKAGES_ADD)->EnableWindow((SendDlgItemMessage(IDC_MMD_LINKAGES_DISPLAYS, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_LINKAGES_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_MMD_LINKAGES_LIST, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_LINKAGES_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_MMD_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	return TRUE;
}

INT CMMDLinkagesDialog::FindDisplay(LPCTSTR pszName, BOOL bLinked) CONST
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

BOOL CMMDLinkagesDialog::IsModified() CONST
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

BOOL CMMDLinkagesDialog::Check(BOOL bModified) CONST
{
	return(!bModified || IsModified());
}

void CMMDLinkagesDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMMDLinkagesDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CMMDLinkagesDialog::PostNcDestroy()
{
	m_pDisplays[0].RemoveAll();
	m_pDisplays[1].RemoveAll();
	m_pDisplays[2].RemoveAll();
	CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CMMDLinkagesDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CMMDLinkagesDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_MMD_LINKAGES_ADD, OnAddDisplay)
	ON_BN_CLICKED(IDC_MMD_LINKAGES_REMOVE, OnRemoveLinkedDisplay)
	ON_BN_CLICKED(IDC_MMD_LINKAGES_REMOVEALL, OnRemoveAllLinkedDisplays)
	ON_BN_CLICKED(IDC_MMD_LINKAGES_HELP, OnHelp)
	ON_LBN_SELCHANGE(IDC_MMD_LINKAGES_LIST, OnSelchangeLinkedDisplay)
	ON_CBN_EDITCHANGE(IDC_MMD_LINKAGES_DISPLAYS, OnEditchangeDisplay)
	ON_CBN_SELCHANGE(IDC_MMD_LINKAGES_DISPLAYS, OnSelchangeDisplay)
	ON_CBN_DBLCLK(IDC_MMD_LINKAGES_DISPLAYS, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDLinkagesDialog message handlers

BOOL CMMDLinkagesDialog::OnInitDialog()
{
	CString  szDisplay;
	CHourglassCursor  cCursor;

	for (CDisplayDialog::OnInitDialog(), GetParent()->GetWindowText(szDisplay); EnumDisplays(); )
	{
		GetDlgItem(IDC_MMD_LINKAGES_NAME)->SetWindowText(szDisplay);
		GetDlgItem(IDC_MMD_LINKAGES_DETAILS)->EnableWindow();
		GetDlgItem(IDC_MMD_LINKAGES_NAME_STATIC)->EnableWindow();
		GetDlgItem(IDC_MMD_LINKAGES_NAME)->EnableWindow();
		GetDlgItem(IDC_MMD_LINKAGES_DISPLAYS)->SetFocus();
		return FALSE;
	}
	return TRUE;
}

void CMMDLinkagesDialog::OnAddDisplay()
{
	INT  nIndex[2];
	CString  szDisplay;
	CHourglassCursor  cCursor;

	for (GetDlgItem(IDC_MMD_LINKAGES_DISPLAYS)->GetWindowText(szDisplay); (nIndex[0] = FindDisplay(szDisplay)) >= 0; )
	{
		if ((nIndex[1] = (INT)SendDlgItemMessage(IDC_MMD_LINKAGES_LIST, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szDisplay)) >= 0)
		{
			for (SendDlgItemMessage(IDC_MMD_LINKAGES_LIST, LB_SETCURSEL, nIndex[1]); SendDlgItemMessage(IDC_MMD_LINKAGES_DISPLAYS, CB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_MMD_LINKAGES_DISPLAYS, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szDisplay)) >= 0; )
			{
				m_pDisplays[1].Add(m_pDisplays[0].GetAt(nIndex[0]));
				m_pDisplays[0].RemoveAt(nIndex[0]);
				break;
			}
			SendDlgItemMessage(IDC_MMD_LINKAGES_DISPLAYS, CB_SETCURSEL);
			GetDlgItem(IDC_MMD_LINKAGES_ADD)->EnableWindow((SendDlgItemMessage(IDC_MMD_LINKAGES_DISPLAYS, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
			GetDlgItem(IDC_MMD_LINKAGES_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_MMD_LINKAGES_LIST, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
			GetDlgItem(IDC_MMD_LINKAGES_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_MMD_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_MMD_LINKAGES_DISPLAYS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MMD_LINKAGES_DISPLAYS, CB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_MMD_LINKAGES_DISPLAYS)->EnableWindow((SendDlgItemMessage(IDC_MMD_LINKAGES_DISPLAYS, CB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_MMD_LINKAGES_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MMD_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_MMD_LINKAGES_LIST)->EnableWindow((SendDlgItemMessage(IDC_MMD_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_MMD_LINKAGES_LIST)->SetFocus();
		}
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDLinkagesDialog::OnRemoveLinkedDisplay()
{
	INT  nIndex[2];
	CString  szDisplay;
	CHourglassCursor  cCursor;

	for (szDisplay = Listbox_GetText(GetDlgItem(IDC_MMD_LINKAGES_LIST), (INT)SendDlgItemMessage(IDC_MMD_LINKAGES_LIST, LB_GETCURSEL)); (nIndex[0] = FindDisplay(szDisplay, TRUE)) >= 0; )
	{
		if ((nIndex[1] = (INT)SendDlgItemMessage(IDC_MMD_LINKAGES_DISPLAYS, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szDisplay)) >= 0)
		{
			for (SendDlgItemMessage(IDC_MMD_LINKAGES_DISPLAYS, CB_SETCURSEL, nIndex[1]); SendDlgItemMessage(IDC_MMD_LINKAGES_LIST, LB_DELETESTRING, (WPARAM)SendDlgItemMessage(IDC_MMD_LINKAGES_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szDisplay)) >= 0; )
			{
				m_pDisplays[0].Add(m_pDisplays[1].GetAt(nIndex[0]));
				m_pDisplays[1].RemoveAt(nIndex[0]);
				break;
			}
			SendDlgItemMessage(IDC_MMD_LINKAGES_LIST, LB_SETCURSEL);
			GetDlgItem(IDC_MMD_LINKAGES_ADD)->EnableWindow((SendDlgItemMessage(IDC_MMD_LINKAGES_DISPLAYS, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
			GetDlgItem(IDC_MMD_LINKAGES_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_MMD_LINKAGES_LIST, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
			GetDlgItem(IDC_MMD_LINKAGES_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_MMD_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_MMD_LINKAGES_DISPLAYS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MMD_LINKAGES_DISPLAYS, CB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_MMD_LINKAGES_DISPLAYS)->EnableWindow((SendDlgItemMessage(IDC_MMD_LINKAGES_DISPLAYS, CB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_MMD_LINKAGES_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MMD_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_MMD_LINKAGES_LIST)->EnableWindow((SendDlgItemMessage(IDC_MMD_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
			GetDlgItem(IDC_MMD_LINKAGES_DISPLAYS)->SetFocus();
		}
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDLinkagesDialog::OnRemoveAllLinkedDisplays()
{
	INT  nDisplay;
	INT  nDisplays;
	CHourglassCursor  cCursor;

	for (nDisplay = 0, nDisplays = (INT)SendDlgItemMessage(IDC_MMD_LINKAGES_LIST, LB_GETCOUNT), m_pDisplays[0].Append(m_pDisplays[1]), m_pDisplays[1].RemoveAll(); nDisplay < nDisplays; nDisplay++)
	{
		if (SendDlgItemMessage(IDC_MMD_LINKAGES_DISPLAYS, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)Listbox_GetText(GetDlgItem(IDC_MMD_LINKAGES_LIST), nDisplay)) >= 0)
		{
			SendDlgItemMessage(IDC_MMD_LINKAGES_LIST, LB_DELETESTRING, nDisplay);
			nDisplays--;
			nDisplay--;
		}
	}
	SendDlgItemMessage(IDC_MMD_LINKAGES_LIST, LB_SETCURSEL);
	SendDlgItemMessage(IDC_MMD_LINKAGES_DISPLAYS, CB_SETCURSEL);
	GetDlgItem(IDC_MMD_LINKAGES_ADD)->EnableWindow((SendDlgItemMessage(IDC_MMD_LINKAGES_DISPLAYS, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_LINKAGES_REMOVE)->EnableWindow((SendDlgItemMessage(IDC_MMD_LINKAGES_LIST, LB_GETCURSEL) >= 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_LINKAGES_REMOVEALL)->EnableWindow((SendDlgItemMessage(IDC_MMD_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_LINKAGES_DISPLAYS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MMD_LINKAGES_DISPLAYS, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_LINKAGES_DISPLAYS)->EnableWindow((SendDlgItemMessage(IDC_MMD_LINKAGES_DISPLAYS, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_LINKAGES_LIST_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MMD_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_LINKAGES_LIST)->EnableWindow((SendDlgItemMessage(IDC_MMD_LINKAGES_LIST, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_LINKAGES_DISPLAYS)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDLinkagesDialog::OnEditchangeDisplay()
{
	CString  szDisplay;

	GetDlgItem(IDC_MMD_LINKAGES_DISPLAYS)->GetWindowText(szDisplay);
	GetDlgItem(IDC_MMD_LINKAGES_ADD)->EnableWindow((SendDlgItemMessage(IDC_MMD_LINKAGES_DISPLAYS, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szDisplay) >= 0 && SendDlgItemMessage(IDC_MMD_LINKAGES_LIST, LB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)(LPCTSTR)szDisplay) < 0) ? TRUE : FALSE);
}

void CMMDLinkagesDialog::OnSelchangeDisplay()
{
	GetDlgItem(IDC_MMD_LINKAGES_ADD)->EnableWindow();
}

void CMMDLinkagesDialog::OnSelchangeLinkedDisplay()
{
	GetDlgItem(IDC_MMD_LINKAGES_REMOVE)->EnableWindow();
}

void CMMDLinkagesDialog::OnOK()
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

BOOL CMMDLinkagesDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_MMDLINKAGESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CMMDLinkagesDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_MMDLINKAGESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CMMDRetrieveDialog dialog

IMPLEMENT_DYNCREATE(CMMDRetrieveDialog, CDisplayDialog)

CMMDRetrieveDialog::CMMDRetrieveDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CMMDRetrieveDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CMMDRetrieveDialog::Create(CWnd *pParentWnd)
{
	CString  szType;
	CString  szTitle;
	CMMDWnd  *pMMDWnd;
	CMMDLayout  cLayout;

	if ((pMMDWnd = (CMMDWnd *)pParentWnd))
	{
		for (szTitle = (pMMDWnd->GetLayout(cLayout)) ? ((!cLayout.GetTitle().IsEmpty()) ? cLayout.GetTitle() : cLayout.GetName()) : STRING(IDS_WINDOW_UNKNOWNTITLE); HIWORD(pMMDWnd->GetType()) == MMD_TYPE_NORMAL; )
		{
			szType.Format(STRING(IDS_MMDRETRIEVEDIALOG_TYPENORMAL), (LPCTSTR)cLayout.GetName());
			break;
		}
		return Create(pParentWnd, szTitle, szType);
	}
	return -1;
}
INT CMMDRetrieveDialog::Create(CWnd *pParentWnd, LPCTSTR pszTitle, LPCTSTR pszType)
{
	m_szType = pszType;
	m_szTitle = pszTitle;
	return CDisplayDialog::Create(pParentWnd, CMMDRetrieveDialog::IDD);
}

BOOL CMMDRetrieveDialog::GetMode(UINT &nMode) CONST
{
	nMode = (!IsDlgButtonChecked(IDC_MMD_RETRIEVE_REALTIME)) ? ((IsDlgButtonChecked(IDC_MMD_RETRIEVE_HISTORY_EXACTTIME)) ? MMD_RETRIEVE_EXACTTIME : 0) : 0;
	nMode |= (!IsDlgButtonChecked(IDC_MMD_RETRIEVE_REALTIME)) ? ((IsDlgButtonChecked(IDC_MMD_RETRIEVE_HISTORY_STOPBYTIME) || IsDlgButtonChecked(IDC_MMD_RETRIEVE_HISTORY_STOPBYEND) || IsDlgButtonChecked(IDC_MMD_RETRIEVE_HISTORY_STOPBYREALTIME)) ? ((!IsDlgButtonChecked(IDC_MMD_RETRIEVE_HISTORY_STOPBYTIME)) ? ((!IsDlgButtonChecked(IDC_MMD_RETRIEVE_HISTORY_STOPBYEND)) ? MMD_RETRIEVE_STOPBYREALTIME : MMD_RETRIEVE_STOPBYEND) : MMD_RETRIEVE_STOPBYTIME) : 0) : 0;
	nMode |= (!IsDlgButtonChecked(IDC_MMD_RETRIEVE_REALTIME)) ? ((IsDlgButtonChecked(IDC_MMD_RETRIEVE_HISTORY_AUTOMATIC)) ? MMD_RETRIEVE_AUTOFORWARD : ((IsDlgButtonChecked(IDC_MMD_RETRIEVE_HISTORY_PSEUDOREALTIME)) ? MMD_RETRIEVE_PSEUDOREALTIME : MMD_RETRIEVE_MANUALFORWARD)) : 0;
	return TRUE;
}

BOOL CMMDRetrieveDialog::GetSpeed(UINT &nSpeed) CONST
{
	nSpeed = (!IsDlgButtonChecked(IDC_MMD_RETRIEVE_HISTORY_AUTOMATIC)) ? (UINT)((GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_SPEED)->SendMessage(TBM_GETRANGEMIN) + GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_SPEED)->SendMessage(TBM_GETRANGEMAX)) / 2) : (UINT)GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_SPEED)->SendMessage(TBM_GETPOS);
	return((IsDlgButtonChecked(IDC_MMD_RETRIEVE_HISTORY_AUTOMATIC)) ? TRUE : FALSE);
}

BOOL CMMDRetrieveDialog::GetInterval(CTimeSpan &tInterval) CONST
{
	tInterval = (IsDlgButtonChecked(IDC_MMD_RETRIEVE_HISTORY_INTERVAL)) ? (SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_INTERVALTIME))) : 0;
	return((IsDlgButtonChecked(IDC_MMD_RETRIEVE_HISTORY_INTERVAL)) ? TRUE : FALSE);
}

BOOL CMMDRetrieveDialog::GetStartTime(CTimeKey &tTimeKey) CONST
{
	CTimeKey  tTime;

	for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_STARTTIME)), tTimeKey = 0; !IsDlgButtonChecked(IDC_MMD_RETRIEVE_REALTIME) && tTime > 0; )
	{
		tTimeKey = tTime;
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDRetrieveDialog::GetStopTime(CTimeKey &tTimeKey) CONST
{
	CTimeKey  tTime;

	for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_STOPTIME)), tTimeKey = 0; IsDlgButtonChecked(IDC_MMD_RETRIEVE_HISTORY_STOPBYTIME) && tTime > 0; )
	{
		tTimeKey = tTime;
		return TRUE;
	}
	return FALSE;
}

CMMDOpenDialog *CMMDRetrieveDialog::GetParentDialog() CONST
{
	return((GetParent() != (CWnd *)GetParentDisplay()) ? (CMMDOpenDialog *)GetParent() : (CMMDOpenDialog *)NULL);
}

CMMDWnd *CMMDRetrieveDialog::GetParentDisplay() CONST
{
	return((CMMDWnd *)CDisplayDialog::GetParentDisplay());
}

BOOL CMMDRetrieveDialog::SetRetrieveInfo()
{
	UINT  nMode;
	UINT  nSpeed;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;

	if (GetRetrieveInfo(nMode, nSpeed, tInterval, tStartTime, tStopTime))
	{
		Spinbox_SetPos(GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_INTERVALTIME), tInterval.GetTotalSeconds() / SECONDSPERMINUTE);
		Timespinbox_SetTime(GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_STARTTIME), (tStartTime > 0 || GetTMService()->GetRecentTMHistoryTimeKey(tStartTime)) ? tStartTime : CTime::GetCurrentTime().GetTime());
		Timespinbox_SetTime(GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_STOPTIME), (tStopTime.GetTime() > 0) ? tStopTime : CTime::GetCurrentTime().GetTime());
		Timespinbox_SetRange(GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_STOPTIME), Timespinbox_GetTime(GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_STARTTIME)), MAX_TIMEKEY);
		SendDlgItemMessage(IDC_MMD_RETRIEVE_HISTORY_SPEED, TBM_SETPOS, TRUE, (!IsDlgButtonChecked(IDC_MMD_RETRIEVE_REALTIME)) ? ((nMode) ? (((nMode & MMD_RETRIEVE_AUTOFORWARD) || (nMode & MMD_RETRIEVE_AUTOBACKWARD)) ? nSpeed : 0) : ((SendDlgItemMessage(IDC_MMD_RETRIEVE_HISTORY_SPEED, TBM_GETRANGEMIN) + SendDlgItemMessage(IDC_MMD_RETRIEVE_HISTORY_SPEED, TBM_GETRANGEMAX)) / 2)) : 0);
		CheckDlgButton(IDC_MMD_RETRIEVE_HISTORY_EXACTTIME, (!IsDlgButtonChecked(IDC_MMD_RETRIEVE_REALTIME) && (nMode & MMD_RETRIEVE_EXACTTIME)) ? TRUE : FALSE);
		CheckDlgButton(IDC_MMD_RETRIEVE_HISTORY_STOPBYTIME, (!IsDlgButtonChecked(IDC_MMD_RETRIEVE_REALTIME) && (nMode & MMD_RETRIEVE_STOPBYTIME) && (nMode & (MMD_RETRIEVE_MANUALFORWARD | MMD_RETRIEVE_MANUALBACKWARD)) == 0) ? TRUE : FALSE);
		CheckDlgButton(IDC_MMD_RETRIEVE_HISTORY_STOPBYEND, (!IsDlgButtonChecked(IDC_MMD_RETRIEVE_REALTIME) && (nMode & MMD_RETRIEVE_STOPBYEND) && (nMode & (MMD_RETRIEVE_MANUALFORWARD | MMD_RETRIEVE_MANUALBACKWARD)) == 0) ? TRUE : FALSE);
		CheckDlgButton(IDC_MMD_RETRIEVE_HISTORY_STOPBYREALTIME, (!IsDlgButtonChecked(IDC_MMD_RETRIEVE_REALTIME) && (!nMode || (nMode & MMD_RETRIEVE_STOPBYREALTIME))) ? TRUE : FALSE);
		CheckDlgButton(IDC_MMD_RETRIEVE_HISTORY_AUTOMATIC, (!IsDlgButtonChecked(IDC_MMD_RETRIEVE_REALTIME) && (!nMode || (nMode & MMD_RETRIEVE_AUTOFORWARD) || (nMode & MMD_RETRIEVE_AUTOBACKWARD))) ? TRUE : FALSE);
		CheckDlgButton(IDC_MMD_RETRIEVE_HISTORY_MANUAL, (!IsDlgButtonChecked(IDC_MMD_RETRIEVE_REALTIME) && ((nMode & MMD_RETRIEVE_MANUALFORWARD) || (nMode & MMD_RETRIEVE_MANUALBACKWARD))) ? TRUE : FALSE);
		CheckDlgButton(IDC_MMD_RETRIEVE_HISTORY_PSEUDOREALTIME, (!IsDlgButtonChecked(IDC_MMD_RETRIEVE_REALTIME) && (nMode & MMD_RETRIEVE_PSEUDOREALTIME)) ? TRUE : FALSE);
		CheckDlgButton(IDC_MMD_RETRIEVE_HISTORY_INTERVAL, (!IsDlgButtonChecked(IDC_MMD_RETRIEVE_REALTIME) && (nMode & MMD_RETRIEVE_PSEUDOREALTIME) == 0 && tInterval.GetTotalSeconds() > 0) ? TRUE : FALSE);
		GetDlgItem(IDC_MMD_RETRIEVE_HISTORY)->EnableWindow(!IsDlgButtonChecked(IDC_MMD_RETRIEVE_REALTIME));
		GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_START_STATIC)->EnableWindow(!IsDlgButtonChecked(IDC_MMD_RETRIEVE_REALTIME));
		GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_STARTTIME)->EnableWindow(!IsDlgButtonChecked(IDC_MMD_RETRIEVE_REALTIME));
		GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_EXACTTIME)->EnableWindow(!IsDlgButtonChecked(IDC_MMD_RETRIEVE_REALTIME));
		GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_STOP_STATIC)->EnableWindow(!IsDlgButtonChecked(IDC_MMD_RETRIEVE_REALTIME));
		GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_STOPBYTIME)->EnableWindow(!IsDlgButtonChecked(IDC_MMD_RETRIEVE_REALTIME) && !IsDlgButtonChecked(IDC_MMD_RETRIEVE_HISTORY_MANUAL));
		GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(!IsDlgButtonChecked(IDC_MMD_RETRIEVE_REALTIME) && IsDlgButtonChecked(IDC_MMD_RETRIEVE_HISTORY_STOPBYTIME));
		GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_STOPBYEND)->EnableWindow(!IsDlgButtonChecked(IDC_MMD_RETRIEVE_REALTIME) && !IsDlgButtonChecked(IDC_MMD_RETRIEVE_HISTORY_MANUAL));
		GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_STOPBYREALTIME)->EnableWindow(!IsDlgButtonChecked(IDC_MMD_RETRIEVE_REALTIME));
		GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_PLAYBACKMODE)->EnableWindow(!IsDlgButtonChecked(IDC_MMD_RETRIEVE_REALTIME));
		GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_AUTOMATIC)->EnableWindow(!IsDlgButtonChecked(IDC_MMD_RETRIEVE_REALTIME));
		GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_PSEUDOREALTIME)->EnableWindow(!IsDlgButtonChecked(IDC_MMD_RETRIEVE_REALTIME));
		GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_MANUAL)->EnableWindow(!IsDlgButtonChecked(IDC_MMD_RETRIEVE_REALTIME));
		GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_SPEED_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMD_RETRIEVE_HISTORY_AUTOMATIC));
		GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_SPEED)->EnableWindow(IsDlgButtonChecked(IDC_MMD_RETRIEVE_HISTORY_AUTOMATIC));
		GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_SLOW)->EnableWindow(IsDlgButtonChecked(IDC_MMD_RETRIEVE_HISTORY_AUTOMATIC));
		GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_FAST)->EnableWindow(IsDlgButtonChecked(IDC_MMD_RETRIEVE_HISTORY_AUTOMATIC));
		GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_INTERVAL)->EnableWindow(!IsDlgButtonChecked(IDC_MMD_RETRIEVE_REALTIME) && !IsDlgButtonChecked(IDC_MMD_RETRIEVE_HISTORY_PSEUDOREALTIME));
		GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_INTERVALTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMD_RETRIEVE_HISTORY_INTERVAL));
		GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_INTERVALTIME)->EnableWindow(IsDlgButtonChecked(IDC_MMD_RETRIEVE_HISTORY_INTERVAL));
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDRetrieveDialog::GetRetrieveInfo(UINT &nMode, UINT &nSpeed, CTimeSpan &tInterval, CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	CMMDWnd  *pMMDWnd;
	CMMDOpenDialog  *pDialog;

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
	if ((pMMDWnd = GetParentDisplay()))
	{
		for (pMMDWnd->GetRetrieveMode(nMode), nSpeed = 0, tInterval = 0, tStartTime = tStopTime = 0; nMode; )
		{
			pMMDWnd->GetRetrieveSpeed(nSpeed);
			pMMDWnd->GetRetrieveInterval(tInterval);
			pMMDWnd->GetRetrieveStartTime(tStartTime);
			pMMDWnd->GetRetrieveStopTime(tStopTime);
			break;
		}
		return TRUE;
	}
	return FALSE;
}

void CMMDRetrieveDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMMDRetrieveDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMMDRetrieveDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CMMDRetrieveDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_MMD_RETRIEVE_REALTIME, OnRetrieveRealtime)
	ON_BN_CLICKED(IDC_MMD_RETRIEVE_HISTORY_STOPBYTIME, OnRetrieveByTime)
	ON_BN_CLICKED(IDC_MMD_RETRIEVE_HISTORY_STOPBYEND, OnRetrieveByEnd)
	ON_BN_CLICKED(IDC_MMD_RETRIEVE_HISTORY_STOPBYREALTIME, OnRetrieveByRealtime)
	ON_BN_CLICKED(IDC_MMD_RETRIEVE_HISTORY_AUTOMATIC, OnRetrieveAutomatic)
	ON_BN_CLICKED(IDC_MMD_RETRIEVE_HISTORY_PSEUDOREALTIME, OnRetrievePseudoRealtime)
	ON_BN_CLICKED(IDC_MMD_RETRIEVE_HISTORY_MANUAL, OnRetrieveManual)
	ON_BN_CLICKED(IDC_MMD_RETRIEVE_HISTORY_INTERVAL, OnRetrieveInterval)
	ON_BN_CLICKED(IDC_MMD_RETRIEVE_HELP, OnHelp)
	ON_CONTROL(TSBXN_CHANGE, IDC_MMD_RETRIEVE_HISTORY_STARTTIME, OnSpinchangeRetrieveStartTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDRetrieveDialog message handlers

BOOL CMMDRetrieveDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	for (CDisplayDialog::OnInitDialog(), SendDlgItemMessage(IDC_MMD_RETRIEVE_HISTORY_SPEED, TBM_SETRANGE, TRUE, MAKELPARAM(0, 10)), Spinbox_SetRange(GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_INTERVALTIME), MMDRETRIEVEDIALOG_MINIMUMINTERVAL, MMDRETRIEVEDIALOG_MAXIMUMINTERVAL), GetDlgItem(IDC_MMD_RETRIEVE_TITLE)->SetWindowText(m_szTitle), GetDlgItem(IDC_MMD_RETRIEVE_TYPE)->SetWindowText(m_szType); SetRetrieveInfo(); )
	{
		GetDlgItem(IDC_MMD_RETRIEVE_DETAILS)->EnableWindow();
		GetDlgItem(IDC_MMD_RETRIEVE_TITLE_STATIC)->EnableWindow();
		GetDlgItem(IDC_MMD_RETRIEVE_TITLE)->EnableWindow();
		GetDlgItem(IDC_MMD_RETRIEVE_TYPE_STATIC)->EnableWindow();
		GetDlgItem(IDC_MMD_RETRIEVE_TYPE)->EnableWindow();
		GetDlgItem(IDC_MMD_RETRIEVE_REALTIME)->EnableWindow((GetParentDisplay()->GetMode() == DISPLAY_MODE_HISTORY) ? TRUE : FALSE);
		GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_STARTTIME)->SetFocus();
		GetDlgItem(IDOK)->EnableWindow();
		return FALSE;
	}
	return TRUE;
}

void CMMDRetrieveDialog::OnRetrieveRealtime()
{
	SetRetrieveInfo();
}

void CMMDRetrieveDialog::OnRetrieveByTime()
{
	CheckDlgButton(IDC_MMD_RETRIEVE_HISTORY_STOPBYTIME, TRUE);
	CheckDlgButton(IDC_MMD_RETRIEVE_HISTORY_STOPBYEND, FALSE);
	CheckDlgButton(IDC_MMD_RETRIEVE_HISTORY_STOPBYREALTIME, FALSE);
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_STOPTIME)->EnableWindow();
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_STOPTIME)->SetFocus();
}

void CMMDRetrieveDialog::OnRetrieveByEnd()
{
	CheckDlgButton(IDC_MMD_RETRIEVE_HISTORY_STOPBYTIME, FALSE);
	CheckDlgButton(IDC_MMD_RETRIEVE_HISTORY_STOPBYEND, TRUE);
	CheckDlgButton(IDC_MMD_RETRIEVE_HISTORY_STOPBYREALTIME, FALSE);
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(FALSE);
}

void CMMDRetrieveDialog::OnRetrieveByRealtime()
{
	CheckDlgButton(IDC_MMD_RETRIEVE_HISTORY_STOPBYTIME, FALSE);
	CheckDlgButton(IDC_MMD_RETRIEVE_HISTORY_STOPBYEND, FALSE);
	CheckDlgButton(IDC_MMD_RETRIEVE_HISTORY_STOPBYREALTIME, (IsDlgButtonChecked(IDC_MMD_RETRIEVE_HISTORY_MANUAL)) ? !IsDlgButtonChecked(IDC_MMD_RETRIEVE_HISTORY_STOPBYREALTIME) : TRUE);
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(FALSE);
}

void CMMDRetrieveDialog::OnRetrieveAutomatic()
{
	SendDlgItemMessage(IDC_MMD_RETRIEVE_HISTORY_SPEED, TBM_SETPOS, TRUE, (SendDlgItemMessage(IDC_MMD_RETRIEVE_HISTORY_SPEED, TBM_GETRANGEMIN) + SendDlgItemMessage(IDC_MMD_RETRIEVE_HISTORY_SPEED, TBM_GETRANGEMAX)) / 2);
	CheckDlgButton(IDC_MMD_RETRIEVE_HISTORY_STOPBYTIME, FALSE);
	CheckDlgButton(IDC_MMD_RETRIEVE_HISTORY_STOPBYEND, FALSE);
	CheckDlgButton(IDC_MMD_RETRIEVE_HISTORY_STOPBYREALTIME, TRUE);
	CheckDlgButton(IDC_MMD_RETRIEVE_HISTORY_AUTOMATIC, TRUE);
	CheckDlgButton(IDC_MMD_RETRIEVE_HISTORY_PSEUDOREALTIME, FALSE);
	CheckDlgButton(IDC_MMD_RETRIEVE_HISTORY_MANUAL, FALSE);
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_STOP_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_STOPBYTIME)->EnableWindow();
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_MMD_RETRIEVE_HISTORY_STOPBYTIME));
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_STOPBYEND)->EnableWindow();
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_STOPBYREALTIME)->EnableWindow();
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_SPEED_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_SPEED)->EnableWindow();
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_SLOW)->EnableWindow();
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_FAST)->EnableWindow();
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_INTERVAL)->EnableWindow();
}

void CMMDRetrieveDialog::OnRetrievePseudoRealtime()
{
	SendDlgItemMessage(IDC_MMD_RETRIEVE_HISTORY_SPEED, TBM_SETPOS, TRUE, 0);
	CheckDlgButton(IDC_MMD_RETRIEVE_HISTORY_STOPBYTIME, FALSE);
	CheckDlgButton(IDC_MMD_RETRIEVE_HISTORY_STOPBYEND, FALSE);
	CheckDlgButton(IDC_MMD_RETRIEVE_HISTORY_STOPBYREALTIME, TRUE);
	CheckDlgButton(IDC_MMD_RETRIEVE_HISTORY_AUTOMATIC, FALSE);
	CheckDlgButton(IDC_MMD_RETRIEVE_HISTORY_PSEUDOREALTIME, TRUE);
	CheckDlgButton(IDC_MMD_RETRIEVE_HISTORY_MANUAL, FALSE);
	CheckDlgButton(IDC_MMD_RETRIEVE_HISTORY_INTERVAL, FALSE);
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_STOP_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_STOPBYTIME)->EnableWindow();
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(IsDlgButtonChecked(IDC_MMD_RETRIEVE_HISTORY_STOPBYTIME));
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_STOPBYEND)->EnableWindow();
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_STOPBYREALTIME)->EnableWindow();
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_SPEED_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_SPEED)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_SLOW)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_FAST)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_INTERVAL)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_INTERVALTIME_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_INTERVALTIME)->EnableWindow(FALSE);
}

void CMMDRetrieveDialog::OnRetrieveManual()
{
	SendDlgItemMessage(IDC_MMD_RETRIEVE_HISTORY_SPEED, TBM_SETPOS, TRUE, 0);
	CheckDlgButton(IDC_MMD_RETRIEVE_HISTORY_STOPBYTIME, FALSE);
	CheckDlgButton(IDC_MMD_RETRIEVE_HISTORY_STOPBYEND, FALSE);
	CheckDlgButton(IDC_MMD_RETRIEVE_HISTORY_STOPBYREALTIME, FALSE);
	CheckDlgButton(IDC_MMD_RETRIEVE_HISTORY_AUTOMATIC, FALSE);
	CheckDlgButton(IDC_MMD_RETRIEVE_HISTORY_PSEUDOREALTIME, FALSE);
	CheckDlgButton(IDC_MMD_RETRIEVE_HISTORY_MANUAL, TRUE);
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_STOP_STATIC)->EnableWindow();
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_STOPBYTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_STOPTIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_STOPBYEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_STOPBYREALTIME)->EnableWindow();
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_SPEED_STATIC)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_SPEED)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_SLOW)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_FAST)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_INTERVAL)->EnableWindow();
}

void CMMDRetrieveDialog::OnRetrieveInterval()
{
	Spinbox_SetPos(GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_INTERVALTIME), MMDRETRIEVEDIALOG_DEFAULTINTERVAL);
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_INTERVALTIME_STATIC)->EnableWindow(IsDlgButtonChecked(IDC_MMD_RETRIEVE_HISTORY_INTERVAL));
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_INTERVALTIME)->EnableWindow(IsDlgButtonChecked(IDC_MMD_RETRIEVE_HISTORY_INTERVAL));
	GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_INTERVALTIME)->SetFocus();
}

void CMMDRetrieveDialog::OnSpinchangeRetrieveStartTime()
{
	Timespinbox_SetRange(GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_STOPTIME), Timespinbox_GetTime(GetDlgItem(IDC_MMD_RETRIEVE_HISTORY_STARTTIME)), MAX_TIMEKEY);
}

void CMMDRetrieveDialog::OnOK()
{
	CMMDWnd  *pMMDWnd;
	CTimeKey  tTimeKey;
	CMMDLayout  cLayout;
	CDisplayWnd  *pDisplayWnd;
	CMMDOpenDialog  *pDialog;
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
		if (IsDlgButtonChecked(IDC_MMD_RETRIEVE_REALTIME))
		{
			if ((pMMDWnd = (GetParentDisplay()->GetLayout(cLayout)) ? GetParentDisplay()->Find(GetParentDisplay()->GetType(), DISPLAY_MODE_REALTIME, cLayout.GetName()) : (CMMDWnd *)NULL))
			{
				for (GetDisplayArea()->ActivateDisplay(pMMDWnd); pMMDWnd != GetParentDisplay(); )
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

void CMMDRetrieveDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	if (!GetParentDialog()) GetParentDisplay()->OnCloseRetrieveDialog(IDCANCEL);
	else  GetParentDialog()->OnCloseRetrieveDialog(IDCANCEL);
	CDisplayDialog::OnCancel();
}

BOOL CMMDRetrieveDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_MMDRETRIEVEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CMMDRetrieveDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_MMDRETRIEVEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CMMDFindDialog dialog

IMPLEMENT_DYNCREATE(CMMDFindDialog, CDisplayDialog)

CMMDFindDialog::CMMDFindDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CMMDFindDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CMMDFindDialog::Create(CWnd *pParentWnd, CMMDLayout &cLayout)
{
	for (GetDatabase()->EnumMMDs(m_pLayouts[0], FALSE); CDisplayDialog::Create(pParentWnd, CMMDFindDialog::IDD) == IDOK && m_pLayouts[1].GetSize() == 1; )
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

CMMDWnd *CMMDFindDialog::GetParent() CONST
{
	return((CMMDWnd *)CDisplayDialog::GetParent());
}

BOOL CMMDFindDialog::EnumSearchKeys()
{
	SendDlgItemMessage(IDC_MMD_FIND_KEY, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)STRING(IDS_MMDFINDDIALOG_KEY_DESCRIPTION));
	return((SendDlgItemMessage(IDC_MMD_FIND_KEY, CB_SETCURSEL) >= 0) ? TRUE : FALSE);
}

BOOL CMMDFindDialog::EnumSearchValues()
{
	INT  nItem;
	INT  nItems;
	CString  szKey;

	GetDlgItem(IDC_MMD_FIND_KEY)->GetWindowText(szKey);
	if (szKey == STRING(IDS_MMDFINDDIALOG_KEY_DESCRIPTION))
	{
		for (nItem = 0, nItems = (INT)m_szDescriptions.GetSize(), SendDlgItemMessage(IDC_MMD_FIND_VALUE, CB_RESETCONTENT); nItem < nItems; nItem++)
		{
			SendDlgItemMessage(IDC_MMD_FIND_VALUE, CB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)m_szDescriptions.GetAt(nItem));
			continue;
		}
	}
	return((SendDlgItemMessage(IDC_MMD_FIND_VALUE, CB_GETCOUNT) >= 0) ? TRUE : FALSE);
}

VOID CMMDFindDialog::DoFindByDescription(LPCTSTR pszDescription)
{
	INT  nLayout;
	INT  nLayouts;
	CString  szResult;
	CMMDLayout  *pLayout;

	SendDlgItemMessage(IDC_MMD_FIND_RESULTS, LB_RESETCONTENT);
	for (nLayout = 0, nLayouts = (m_pLayouts[1].Copy(&m_pLayouts[0])) ? (INT)m_pLayouts[1].GetSize() : 0; nLayout < nLayouts; nLayout++)
	{
		if ((pLayout = m_pLayouts[1].GetAt(nLayout)) && pLayout->GetTitle().Find(pszDescription) >= 0)
		{
			szResult.Format(STRING(IDS_MMDFINDDIALOG_RESULT_FORMAT), (LPCTSTR)pLayout->GetName(), (LPCTSTR)pLayout->GetTitle());
			SendDlgItemMessage(IDC_MMD_FIND_RESULTS, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szResult);
		}
	}
	GetDlgItem(IDC_MMD_FIND_RESULTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MMD_FIND_RESULTS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_FIND_RESULTS)->EnableWindow((SendDlgItemMessage(IDC_MMD_FIND_RESULTS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
}

VOID CMMDFindDialog::DoFindByDescriptions(CONST CStringArray &szDescriptions)
{
	INT  nLayout;
	INT  nLayouts;
	INT  nDescription;
	INT  nDescriptions;
	CString  szResult;
	CMMDLayout  *pLayout[2];

	for (nDescription = 0, nDescriptions = (m_pLayouts[1].Copy(&m_pLayouts[0])) ? (INT)szDescriptions.GetSize() : 0; nDescription < nDescriptions; nDescription += 2)
	{
		for (nLayout = 0, nLayouts = (!nDescription || szDescriptions.GetAt(nDescription - 1) == STRING(IDS_MMDFINDDIALOG_QUERY_AND)) ? (INT)m_pLayouts[1].GetSize() : -1; nLayout < nLayouts; nLayout++)
		{
			if ((pLayout[0] = m_pLayouts[1].GetAt(nLayout)) && pLayout[0]->GetTitle().Find(szDescriptions.GetAt(nDescription)) < 0)
			{
				m_pLayouts[1].RemoveAt(nLayout);
				delete pLayout[0];
				nLayouts--;
				nLayout--;
			}
		}
		for (nLayout = 0, nLayouts = (nDescription > 0 && szDescriptions.GetAt(nDescription - 1) == STRING(IDS_MMDFINDDIALOG_QUERY_OR)) ? (INT)m_pLayouts[0].GetSize() : -1; nLayout < nLayouts; nLayout++)
		{
			if ((pLayout[0] = m_pLayouts[0].GetAt(nLayout)) && pLayout[0]->GetTitle().Find(szDescriptions.GetAt(nDescription)) >= 0)
			{
				if ((pLayout[1] = (m_pLayouts[1].Find(pLayout[0]->GetName()) < 0) ? new CMMDLayout : (CMMDLayout *)NULL))
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
	for (SendDlgItemMessage(IDC_MMD_FIND_RESULTS, LB_RESETCONTENT); !nDescriptions; )
	{
		m_pLayouts[1].RemoveAll();
		break;
	}
	for (nLayout = 0, nLayouts = (INT)m_pLayouts[1].GetSize(); nLayout < nLayouts; nLayout++)
	{
		if ((pLayout[0] = m_pLayouts[1].GetAt(nLayout)) != (CMMDLayout *)NULL)
		{
			szResult.Format(STRING(IDS_MMDFINDDIALOG_RESULT_FORMAT), (LPCTSTR)pLayout[0]->GetName(), (LPCTSTR)pLayout[0]->GetTitle());
			SendDlgItemMessage(IDC_MMD_FIND_RESULTS, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)(LPCTSTR)szResult);
		}
	}
	GetDlgItem(IDC_MMD_FIND_RESULTS_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MMD_FIND_RESULTS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_FIND_RESULTS)->EnableWindow((SendDlgItemMessage(IDC_MMD_FIND_RESULTS, LB_GETCOUNT) > 0) ? TRUE : FALSE);
}

void CMMDFindDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMMDFindDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMMDFindDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CMMDFindDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_MMD_FIND_SEARCH, OnSearch)
	ON_BN_CLICKED(IDC_MMD_FIND_OPEN, OnOpen)
	ON_BN_CLICKED(IDC_MMD_FIND_HELP, OnHelp)
	ON_CBN_EDITCHANGE(IDC_MMD_FIND_VALUE, OnEditchangeValue)
	ON_CBN_SELCHANGE(IDC_MMD_FIND_KEY, OnSelchangeKey)
	ON_CBN_SELCHANGE(IDC_MMD_FIND_VALUE, OnSelchangeValue)
	ON_LBN_DBLCLK(IDC_MMD_FIND_RESULTS, OnOpen)
	ON_LBN_SELCHANGE(IDC_MMD_FIND_RESULTS, OnSelchangeResult)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDFindDialog message handlers

BOOL CMMDFindDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	if (EnumSearchKeys() && EnumSearchValues())
	{
		GetDlgItem(IDC_MMD_FIND_KEY_STATIC)->EnableWindow();
		GetDlgItem(IDC_MMD_FIND_KEY)->EnableWindow();
		GetDlgItem(IDC_MMD_FIND_VALUE_STATIC)->EnableWindow();
		GetDlgItem(IDC_MMD_FIND_VALUE)->EnableWindow();
	}
	return TRUE;
}

void CMMDFindDialog::OnSearch()
{
	INT  nPos;
	INT  nItem;
	INT  nItems;
	CString  szKey;
	CString  szValue;
	CString  szParameter;
	CString  szDescription;
	CStringArray  szParameters;
	CStringArray  szDescriptions;
	CHourglassCursor  cCursor;

	GetDlgItem(IDC_MMD_FIND_KEY)->GetWindowText(szKey);
	GetDlgItem(IDC_MMD_FIND_VALUE)->GetWindowText(szValue);
	if (szKey == STRING(IDS_MMDFINDDIALOG_KEY_DESCRIPTION))
	{
		for (nItem = 0, nItems = (INT)m_szDescriptions.GetSize(); nItem < nItems; nItem++)
		{
			if (m_szDescriptions.GetAt(nItem) == szValue) break;
			continue;
		}
		for (; nItem == nItems; )
		{
			SendDlgItemMessage(IDC_MMD_FIND_VALUE, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szValue);
			m_szDescriptions.Add(szValue);
			break;
		}
		if ((nPos = szValue.Find(STRING(IDS_MMDFINDDIALOG_QUERY_QUOTE))) < 0)
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
			if (szValue.GetAt(nPos) != STRINGCHAR(IDS_MMDFINDDIALOG_QUERY_QUOTE))
			{
				nPos = -1;
				break;
			}
			for (nPos = nPos + 1; nPos < szValue.GetLength(); nPos++)
			{
				if (!_istspace(szValue.GetAt(nPos)) && szValue.GetAt(nPos) != STRINGCHAR(IDS_MMDFINDDIALOG_QUERY_QUOTE))
				{
					szDescription += szValue.GetAt(nPos);
					continue;
				}
				break;
			}
			if (szValue.GetAt(nPos) != STRINGCHAR(IDS_MMDFINDDIALOG_QUERY_QUOTE))
			{
				nPos = -1;
				break;
			}
			for (nPos = nPos + 1, szDescriptions.Add(szDescription); nPos < szValue.GetLength(); nPos++)
			{
				if (!_istspace(szValue.GetAt(nPos))) break;
				continue;
			}
			if (szValue.GetAt(nPos) == STRINGCHAR(IDS_MMDFINDDIALOG_QUERY_AND) || szValue.GetAt(nPos) == STRINGCHAR(IDS_MMDFINDDIALOG_QUERY_OR))
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
		GetDlgItem(IDC_MMD_FIND_VALUE)->SetFocus();
		CAudioDevice::AlertBySound();
		return;
	}
}

void CMMDFindDialog::OnOpen()
{
	INT  nLayout[2];
	INT  nLayouts[2];
	CString  szTitle[2];
	CMMDLayout  *pLayout;
	CHourglassCursor  cCursor;

	for (nLayout[0] = 0, nLayouts[0] = (INT)m_pLayouts[1].GetSize(), szTitle[0] = Listbox_GetText(GetDlgItem(IDC_MMD_FIND_RESULTS), (INT)SendDlgItemMessage(IDC_MMD_FIND_RESULTS, LB_GETCURSEL)); nLayout[0] < nLayouts[0]; nLayout[0]++)
	{
		if ((pLayout = m_pLayouts[1].GetAt(nLayout[0])))
		{
			for (; pLayout->GetTitle().IsEmpty(); )
			{
				szTitle[1] = pLayout->GetName();
				break;
			}
			if (!pLayout->GetTitle().IsEmpty()) szTitle[1].Format(STRING(IDS_MMDFINDDIALOG_RESULT_FORMAT), (LPCTSTR)pLayout->GetName(), (LPCTSTR)pLayout->GetTitle());
			if (szTitle[0] == szTitle[1]) break;
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

void CMMDFindDialog::OnSelchangeKey()
{
	EnumSearchValues();
	GetDlgItem(IDC_MMD_FIND_SEARCH)->EnableWindow(FALSE);
	GetDlgItem(IDC_MMD_FIND_VALUE)->SetFocus();
}

void CMMDFindDialog::OnSelchangeValue()
{
	GetDlgItem(IDC_MMD_FIND_SEARCH)->EnableWindow((SendDlgItemMessage(IDC_MMD_FIND_VALUE, CB_GETCURSEL) >= 0) ? TRUE : FALSE);
}

void CMMDFindDialog::OnSelchangeResult()
{
	GetDlgItem(IDC_MMD_FIND_OPEN)->EnableWindow();
}

void CMMDFindDialog::OnEditchangeValue()
{
	GetDlgItem(IDC_MMD_FIND_SEARCH)->EnableWindow((GetDlgItem(IDC_MMD_FIND_VALUE)->GetWindowTextLength() > 0) ? TRUE : FALSE);
}

void CMMDFindDialog::OnOK()
{
	CHourglassCursor  cCursor;

	m_pLayouts[1].RemoveAll();
	CDisplayDialog::OnOK();
}

BOOL CMMDFindDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_MMDFINDDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CMMDFindDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_MMDFINDDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CMMDOpenDialog dialog

IMPLEMENT_DYNCREATE(CMMDOpenDialog, CDisplayDialog)

CMMDOpenDialog::CMMDOpenDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CMMDOpenDialog)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CMMDOpenDialog::Create(CWnd *pParentWnd)
{
	return CDisplayDialog::Create(pParentWnd, CMMDOpenDialog::IDD);
}

BOOL CMMDOpenDialog::Initialize()
{
	m_nRetrieveMode = 0;
	m_nRetrieveSpeed = 0;
	m_tRetrieveStartTime = 0;
	m_tRetrieveStopTime = 0;
	m_tRetrieveInterval = 0;
	m_bLayoutBadData = FALSE;
	m_bLayoutToolTips = FALSE;
	m_bLayoutInvalidData = FALSE;
	return TRUE;
}

CString CMMDOpenDialog::GetTitle() CONST
{
	CString  szTitle;
	CMMDLayout  cMMDLayout;

	if (FindLayout(cMMDLayout))
	{
		szTitle.Format(STRING(IDS_WINDOW_FULLTITLE), STRING(IDS_DISPLAY_TITLE_MMD), (!cMMDLayout.GetTitle().IsEmpty()) ? (LPCTSTR)cMMDLayout.GetTitle() : (LPCTSTR)cMMDLayout.GetName());
		return szTitle;
	}
	return STRING(IDS_DISPLAY_TITLE_MMD);
}

UINT CMMDOpenDialog::GetType() CONST
{
	return((IsDlgButtonChecked(IDC_MMD_OPEN_TYPE_NORMAL)) ? MMD_TYPE_NORMAL : -1);
}

UINT CMMDOpenDialog::GetMode() CONST
{
	return((IsDlgButtonChecked(IDC_MMD_OPEN_MODE_REALTIME) || IsDlgButtonChecked(IDC_MMD_OPEN_MODE_HISTORY)) ? (IsDlgButtonChecked(IDC_MMD_OPEN_MODE_REALTIME)*DISPLAY_MODE_REALTIME + IsDlgButtonChecked(IDC_MMD_OPEN_MODE_HISTORY)*DISPLAY_MODE_HISTORY) : -1);
}

BOOL CMMDOpenDialog::GetLayout(CMMDLayout &cLayout) CONST
{
	return((FindLayout(cLayout)) ? ((cLayout.GetName() == m_cLayout.GetName()) ? cLayout.Copy(&m_cLayout) : TRUE) : FALSE);
}

BOOL CMMDOpenDialog::GetLayoutInvalidDataMode(BOOL &bEnable) CONST
{
	if (IsLayoutModified())
	{
		bEnable = m_bLayoutInvalidData;
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDOpenDialog::GetLayoutBadDataMode(BOOL &bEnable) CONST
{
	if (IsLayoutModified())
	{
		bEnable = m_bLayoutBadData;
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDOpenDialog::GetLayoutToolTipMode(BOOL &bEnable) CONST
{
	if (IsLayoutModified())
	{
		bEnable = m_bLayoutToolTips;
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDOpenDialog::IsLayoutModified() CONST
{
	return !m_cLayout.GetName().IsEmpty() || m_bLayoutInvalidData || m_bLayoutBadData || m_bLayoutToolTips;
}

BOOL CMMDOpenDialog::GetRetrieveMode(UINT &nMode) CONST
{
	nMode = m_nRetrieveMode;
	return TRUE;
}

BOOL CMMDOpenDialog::GetRetrieveSpeed(UINT &nSpeed) CONST
{
	nSpeed = m_nRetrieveSpeed;
	return((m_nRetrieveMode & MMD_RETRIEVE_AUTOFORWARD) ? TRUE : FALSE);
}

BOOL CMMDOpenDialog::GetRetrieveInterval(CTimeSpan &tInterval) CONST
{
	tInterval = m_tRetrieveInterval;
	return(((m_nRetrieveMode & MMD_RETRIEVE_AUTOFORWARD) || (m_nRetrieveMode & MMD_RETRIEVE_MANUALFORWARD)) ? TRUE : FALSE);
}

BOOL CMMDOpenDialog::GetRetrieveStartTime(CTimeKey &tTimeKey) CONST
{
	tTimeKey = m_tRetrieveStartTime;
	return(((m_nRetrieveMode & MMD_RETRIEVE_AUTOFORWARD) || (m_nRetrieveMode & MMD_RETRIEVE_PSEUDOREALTIME) || (m_nRetrieveMode & MMD_RETRIEVE_MANUALFORWARD)) ? TRUE : FALSE);
}

BOOL CMMDOpenDialog::GetRetrieveStopTime(CTimeKey &tTimeKey) CONST
{
	tTimeKey = m_tRetrieveStopTime;
	return((((m_nRetrieveMode & MMD_RETRIEVE_AUTOFORWARD) || (m_nRetrieveMode & MMD_RETRIEVE_PSEUDOREALTIME) || (m_nRetrieveMode & MMD_RETRIEVE_MANUALFORWARD)) && (m_nRetrieveMode & MMD_RETRIEVE_STOPBYTIME)) ? TRUE : FALSE);
}

BOOL CMMDOpenDialog::GetRetrieveFileName(CString &szFileName) CONST
{
	szFileName = ((m_nRetrieveMode & MMD_RETRIEVE_AUTOFORWARD) || (m_nRetrieveMode & MMD_RETRIEVE_PSEUDOREALTIME) || (m_nRetrieveMode & MMD_RETRIEVE_MANUALFORWARD)) ? (LPCTSTR)m_szRetrieveFileName : EMPTYSTRING;
	return !szFileName.IsEmpty();
}

BOOL CMMDOpenDialog::IsRetrievingModified() CONST
{
	return((m_nRetrieveMode != 0) ? TRUE : FALSE);
}

BOOL CMMDOpenDialog::GetPrintJobs(CMMDPrintJobs &pPrintJobs) CONST
{
	CByteArray  nPrintInfo;

	return((IsPrintingModified()) ? pPrintJobs.Copy(&m_pPrintJobs) : pPrintJobs.Unmap(nPrintInfo));
}

BOOL CMMDOpenDialog::IsPrintingModified() CONST
{
	return((m_pPrintJobs.GetSize() > 0) ? TRUE : FALSE);
}

CMMDWnd *CMMDOpenDialog::GetParent() CONST
{
	return((CMMDWnd *)CDisplayDialog::GetParent());
}

VOID CMMDOpenDialog::EnumLayouts()
{
	INT  nDigits;
	INT  nDisplay;
	INT  nDisplays;
	CString  szDisplay;
	CMMDLayout  *pMMDLayout;
	CMMDLayouts  pMMDLayouts;
	CStringTools  cStringTools;

	for (nDisplay = 0, nDisplays = GetDatabase()->EnumMMDs(pMMDLayouts), nDigits = 0; nDisplay < nDisplays; nDisplay++)
	{
		if ((pMMDLayout = pMMDLayouts.GetAt(nDisplay))) nDigits = max(pMMDLayout->GetName().GetLength(), nDigits);
		continue;
	}
	for (nDisplay = 0, nDisplays = (IsDlgButtonChecked(IDC_MMD_OPEN_TYPE_NORMAL)) ? (INT)pMMDLayouts.GetSize() : 0, SendDlgItemMessage(IDC_MMD_OPEN_DISPLAY, CB_RESETCONTENT); nDisplay < nDisplays; nDisplay++)
	{
		if ((pMMDLayout = pMMDLayouts.GetAt(nDisplay)))
		{
			if (pMMDLayout->GetTitle().IsEmpty())
			{
				SendDlgItemMessage(IDC_MMD_OPEN_DISPLAY, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)cStringTools.ConvertUIntToPaddedString(_ttoi(pMMDLayout->GetName()), nDigits));
				continue;
			}
			szDisplay.Format(STRING(IDS_MMDOPENDIALOG_TITLE), (LPCTSTR)cStringTools.ConvertUIntToPaddedString(_ttoi(pMMDLayout->GetName()), nDigits), (LPCTSTR)pMMDLayout->GetTitle());
			SendDlgItemMessage(IDC_MMD_OPEN_DISPLAY, CB_ADDSTRING, (WPARAM)NULL, (LPARAM)(LPCTSTR)szDisplay);
		}
	}
	GetDlgItem(IDC_MMD_OPEN_DISPLAY_STATIC)->EnableWindow((SendDlgItemMessage(IDC_MMD_OPEN_DISPLAY, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_OPEN_DISPLAY)->EnableWindow((SendDlgItemMessage(IDC_MMD_OPEN_DISPLAY, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_OPEN_FIND)->EnableWindow((SendDlgItemMessage(IDC_MMD_OPEN_DISPLAY, CB_GETCOUNT) > 0) ? TRUE : FALSE);
	GetDlgItem(IDC_MMD_OPEN_SETTINGS)->EnableWindow(FALSE);
}

BOOL CMMDOpenDialog::FindLayout() CONST
{
	CMMDLayout  cMMDLayout;

	return FindLayout(cMMDLayout);
}
BOOL CMMDOpenDialog::FindLayout(CMMDLayout &cLayout) CONST
{
	INT  nDigits;
	INT  nDisplay;
	INT  nDisplays;
	CString  szDisplay[2];
	CMMDLayout  *pMMDLayout;
	CMMDLayouts  pMMDLayouts;
	CStringTools  cStringTools;

	GetDlgItem(IDC_MMD_OPEN_DISPLAY)->GetWindowText(szDisplay[0]);
	for (nDisplay = 0, nDisplays = GetDatabase()->EnumMMDs(pMMDLayouts), nDigits = 0; nDisplay < nDisplays; nDisplay++)
	{
		if ((pMMDLayout = pMMDLayouts.GetAt(nDisplay))) nDigits = max(pMMDLayout->GetName().GetLength(), nDigits);
		continue;
	}
	for (nDisplay = 0, nDisplays = (IsDlgButtonChecked(IDC_MMD_OPEN_TYPE_NORMAL)) ? (INT)pMMDLayouts.GetSize() : 0; nDisplay < nDisplays; nDisplay++)
	{
		if (!(pMMDLayout = pMMDLayouts.GetAt(nDisplay)))
		{
			pMMDLayouts.RemoveAt(nDisplay);
			nDisplays--;
			nDisplay--;
			continue;
		}
		szDisplay[1].Format(STRING(IDS_MMDOPENDIALOG_TITLE), (LPCTSTR)cStringTools.ConvertUIntToPaddedString(_ttoi(pMMDLayout->GetName()), nDigits), (LPCTSTR)pMMDLayout->GetTitle());
		if (IsDlgButtonChecked(IDC_MMD_OPEN_TYPE_NORMAL) && (!szDisplay[0].CompareNoCase(szDisplay[1]) || !szDisplay[0].CompareNoCase(cStringTools.ConvertUIntToPaddedString(_ttoi(pMMDLayout->GetName()), nDigits)) || !szDisplay[0].CompareNoCase(pMMDLayout->GetTitle())))
		{
			cLayout.Copy(pMMDLayout);
			break;
		}
	}
	return((nDisplay < nDisplays) ? TRUE : FALSE);
}

BOOL CMMDOpenDialog::Check(BOOL bModified) CONST
{
	CMMDLayout  cMMDLayout;

	return(((IsDlgButtonChecked(IDC_MMD_OPEN_MODE_REALTIME) || IsDlgButtonChecked(IDC_MMD_OPEN_MODE_HISTORY)) && FindLayout(cMMDLayout) && (IsDlgButtonChecked(IDC_MMD_OPEN_MODE_REALTIME) || IsRetrievingModified())) ? TRUE : FALSE);
}

void CMMDOpenDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMMDOpenDialog)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMMDOpenDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CMMDOpenDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_MMD_OPEN_SETTINGS, OnSettings)
	ON_BN_CLICKED(IDC_MMD_OPEN_FIND, OnFind)
	ON_BN_CLICKED(IDC_MMD_OPEN_TYPE_NORMAL, OnTypeNormal)
	ON_BN_CLICKED(IDC_MMD_OPEN_MODE_REALTIME, OnRealtimeMode)
	ON_BN_CLICKED(IDC_MMD_OPEN_MODE_HISTORY, OnHistoryMode)
	ON_BN_CLICKED(IDC_MMD_OPEN_HELP, OnHelp)
	ON_CBN_EDITCHANGE(IDC_MMD_OPEN_DISPLAY, OnEditchangeTitle)
	ON_CBN_SELCHANGE(IDC_MMD_OPEN_DISPLAY, OnSelchangeTitle)
	ON_CBN_DBLCLK(IDC_MMD_OPEN_DISPLAY, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDOpenDialog message handlers

BOOL CMMDOpenDialog::OnInitDialog()
{
	CHourglassCursor  cCursor;

	CDisplayDialog::OnInitDialog();
	CheckRadioButton(IDC_MMD_OPEN_TYPE_NORMAL, IDC_MMD_OPEN_TYPE_NORMAL, IDC_MMD_OPEN_TYPE_NORMAL);
	CheckDlgButton(IDC_MMD_OPEN_MODE_REALTIME, TRUE);
	CheckDlgButton(IDC_MMD_OPEN_MODE_HISTORY, FALSE);
	GetDlgItem(IDC_MMD_OPEN_DETAILS)->EnableWindow();
	GetDlgItem(IDC_MMD_OPEN_TYPE)->EnableWindow();
	GetDlgItem(IDC_MMD_OPEN_TYPE_NORMAL)->EnableWindow();
	GetDlgItem(IDC_MMD_OPEN_MODE)->EnableWindow();
	GetDlgItem(IDC_MMD_OPEN_MODE_REALTIME)->EnableWindow();
	GetDlgItem(IDC_MMD_OPEN_MODE_HISTORY)->EnableWindow(CheckAccountPrivilege(PRIVILEGE_OFFLINE_OPERATE));
	EnumLayouts();
	return TRUE;
}

void CMMDOpenDialog::OnSettings()
{
	ReportEvent((m_dlgSettings.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMMDOpenDialog::OnFind()
{
	INT  nResult;
	CString  szDisplay;
	CMMDLayout  cMMDLayout;

	if ((nResult = m_dlgFindDisplay.Create(this, cMMDLayout)) == IDOK)
	{
		for (szDisplay.Format(STRING(IDS_MMDOPENDIALOG_TITLE), (LPCTSTR)cMMDLayout.GetName(), (LPCTSTR)cMMDLayout.GetTitle()); cMMDLayout.GetTitle().IsEmpty(); )
		{
			szDisplay = cMMDLayout.GetName();
			break;
		}
		GetDlgItem(IDC_MMD_OPEN_SETTINGS)->EnableWindow((SendDlgItemMessage(IDC_MMD_OPEN_DISPLAY, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_MMD_OPEN_DISPLAY, CB_FINDSTRINGEXACT, (WPARAM)-1, (LPARAM)((IsDlgButtonChecked(IDC_MMD_OPEN_TYPE_NORMAL)) ? (LPCTSTR)szDisplay : (LPCTSTR)cMMDLayout.GetTitle()))) >= 0 && (GetMode() != DISPLAY_MODE_REALTIME || !GetParent()->Find(MAKELONG(DISPLAY_TYPE_MMD, GetType()), GetMode(), cMMDLayout.GetName()))) ? TRUE : FALSE);
		GetDlgItem(IDC_MMD_OPEN_DISPLAY)->SetFocus();
	}
	ReportEvent((nResult <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDOpenDialog::OnTypeNormal()
{
	GetDlgItem(IDC_MMD_OPEN_DISPLAY)->SetFocus();
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDOpenDialog::OnEditchangeTitle()
{
	CMMDLayout  cMMDLayout;

	GetDlgItem(IDC_MMD_OPEN_SETTINGS)->EnableWindow((FindLayout(cMMDLayout) && (GetMode() != DISPLAY_MODE_REALTIME || !GetParent()->Find(MAKELONG(DISPLAY_TYPE_MMD, GetType()), GetMode(), cMMDLayout.GetName()))) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDOpenDialog::OnSelchangeTitle()
{
	CMMDLayout  cMMDLayout;

	SendDlgItemMessage(IDC_MMD_OPEN_DISPLAY, CB_SETCURSEL, (WPARAM)SendDlgItemMessage(IDC_MMD_OPEN_DISPLAY, CB_GETCURSEL));
	GetDlgItem(IDC_MMD_OPEN_SETTINGS)->EnableWindow((FindLayout(cMMDLayout) && (GetMode() != DISPLAY_MODE_REALTIME || !GetParent()->Find(MAKELONG(DISPLAY_TYPE_MMD, GetType()), GetMode(), cMMDLayout.GetName()))) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDOpenDialog::OnRealtimeMode()
{
	CMMDLayout  cMMDLayout;

	GetDlgItem(IDC_MMD_OPEN_SETTINGS)->EnableWindow((FindLayout(cMMDLayout) && (GetMode() != DISPLAY_MODE_REALTIME || !GetParent()->Find(MAKELONG(DISPLAY_TYPE_MMD, GetType()), GetMode(), cMMDLayout.GetName()))) ? TRUE : FALSE);
	GetDlgItem(IDOK)->EnableWindow(Check());
}

void CMMDOpenDialog::OnHistoryMode()
{
	INT  nPos;
	CString  szType;
	CString  szTitle;
	CMMDLayout  cMMDLayout;

	if (IsDlgButtonChecked(IDC_MMD_OPEN_TYPE_NORMAL))
	{
		for (szTitle = (FindLayout(cMMDLayout)) ? cMMDLayout.GetTitle() : STRING(IDS_WINDOW_UNKNOWNTITLE), szType.Format(STRING(IDS_MMDOPENDIALOG_TYPENORMAL), (LPCTSTR)cMMDLayout.GetName()), szType = ((nPos = (cMMDLayout.GetName().IsEmpty()) ? szType.Find(SPACE) : -1) >= 0) ? szType.Left(nPos) : szType; IsDlgButtonChecked(IDC_MMD_OPEN_MODE_HISTORY); )
		{
			ReportEvent((m_dlgRetrievals.Create(this, szTitle, szType) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
			break;
		}
		for (GetDlgItem(IDC_MMD_OPEN_SETTINGS)->EnableWindow((FindLayout(cMMDLayout) && (GetMode() != DISPLAY_MODE_REALTIME || !GetParent()->Find(MAKELONG(DISPLAY_TYPE_MMD, GetType()), GetMode(), cMMDLayout.GetName()))) ? TRUE : FALSE); SendDlgItemMessage(IDC_MMD_OPEN_DISPLAY, CB_GETCOUNT) > 0; )
		{
			GetDlgItem(IDC_MMD_OPEN_DISPLAY)->SetFocus();
			break;
		}
		for (; IsDlgButtonChecked(IDC_MMD_OPEN_MODE_REALTIME); )
		{
			GetDlgItem(IDC_MMD_OPEN_MODE_REALTIME)->SetFocus();
			break;
		}
		GetDlgItem(IDOK)->EnableWindow(Check());
		return;
	}
	CheckDlgButton(IDC_MMD_OPEN_MODE_REALTIME, TRUE);
	CheckDlgButton(IDC_MMD_OPEN_MODE_HISTORY, FALSE);
	for (GetDlgItem(IDC_MMD_OPEN_SETTINGS)->EnableWindow((FindLayout(cMMDLayout) && (GetMode() != DISPLAY_MODE_REALTIME || !GetParent()->Find(MAKELONG(DISPLAY_TYPE_MMD, GetType()), GetMode(), cMMDLayout.GetName()))) ? TRUE : FALSE); SendDlgItemMessage(IDC_MMD_OPEN_DISPLAY, CB_GETCOUNT) > 0; )
	{
		GetDlgItem(IDC_MMD_OPEN_DISPLAY)->SetFocus();
		break;
	}
	for (; IsDlgButtonChecked(IDC_MMD_OPEN_MODE_REALTIME); )
	{
		GetDlgItem(IDC_MMD_OPEN_MODE_REALTIME)->SetFocus();
		break;
	}
	GetDlgItem(IDOK)->EnableWindow(Check());
}

BOOL CMMDOpenDialog::OnCloseSettingsDialog(UINT nCode)
{
	if (nCode == IDOK)
	{
		if (m_dlgSettings.IsLayoutModified())
		{
			m_dlgSettings.GetLayout(m_cLayout);
			m_dlgSettings.GetLayoutInvalidDataMode(m_bLayoutInvalidData);
			m_dlgSettings.GetLayoutBadDataMode(m_bLayoutBadData);
			m_dlgSettings.GetLayoutToolTipMode(m_bLayoutToolTips);
		}
		if (m_dlgSettings.IsRetrievingModified()) m_dlgSettings.GetRetrieveFileName(m_szRetrieveFileName);
		if (m_dlgSettings.IsPrintingModified()) m_dlgSettings.GetPrintJobs(m_pPrintJobs);
	}
	return TRUE;
}

BOOL CMMDOpenDialog::OnCloseRetrieveDialog(UINT nCode)
{
	CMMDLayout  cMMDLayout;

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
		CheckDlgButton(IDC_MMD_OPEN_MODE_REALTIME, TRUE);
		CheckDlgButton(IDC_MMD_OPEN_MODE_HISTORY, FALSE);
	}
	return TRUE;
}

void CMMDOpenDialog::OnOK()
{
	CMMDWnd  *pMMDWnd[2];
	CMMDLayout  cMMDLayout;
	CHourglassCursor  cCursor;

	if ((pMMDWnd[0] = GetParent()))
	{
		if (GetMode() == DISPLAY_MODE_REALTIME)
		{
			if ((pMMDWnd[1] = (FindLayout(cMMDLayout)) ? pMMDWnd[0]->Find(MAKELONG(DISPLAY_TYPE_MMD, GetType()), GetMode(), cMMDLayout.GetName()) : (CMMDWnd *)NULL))
			{
				GetDisplayArea()->ActivateDisplay(pMMDWnd[1]);
				EndDialog(IDCANCEL);
				return;
			}
		}
		if (!pMMDWnd[0]->OnCloseOpenDialog(IDOK))
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

void CMMDOpenDialog::OnCancel()
{
	CHourglassCursor  cCursor;

	GetParent()->OnCloseOpenDialog(IDCANCEL);
	CDisplayDialog::OnCancel();
}

BOOL CMMDOpenDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_MMDOPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
	return TRUE;
}

void CMMDOpenDialog::OnHelp()
{
	CHourglassCursor  cCursor;

	ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_MMDOPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE : SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CMMDRetrieveThread

IMPLEMENT_DYNCREATE(CMMDRetrieveThread, CThread)

CMMDRetrieveThread::CMMDRetrieveThread() : CThread()
{
	m_nMode = 0;
	m_nSpeed = 0;
	m_tInterval = 0;
	m_tStartTime = 0;
	m_tStopTime = 0;
	m_pbFlag = (LPLONG)NULL;
	m_bInit[0] = (HANDLE)NULL;
	m_bInit[1] = (HANDLE)NULL;
	m_hAction[MMDRETRIEVETHREAD_ACTION_STOP] = (HANDLE)NULL;
	m_hAction[MMDRETRIEVETHREAD_ACTION_AUTOFORWARD] = (HANDLE)NULL;
	m_hAction[MMDRETRIEVETHREAD_ACTION_AUTOBACKWARD] = (HANDLE)NULL;
	m_hAction[MMDRETRIEVETHREAD_ACTION_MANUALFORWARD] = (HANDLE)NULL;
	m_hAction[MMDRETRIEVETHREAD_ACTION_MANUALBACKWARD] = (HANDLE)NULL;
	m_hAction[MMDRETRIEVETHREAD_ACTION_PSEUDOREALTIME] = (HANDLE)NULL;
}

BOOL CMMDRetrieveThread::Start(CMMDWnd *pParentWnd, HANDLE bInit, HANDLE bContinue, LPCTSTR pszFileName, UINT nMode, UINT nSpeed, CONST CTimeSpan &tInterval, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, LONG *pbFlag, HANDLE bRetrieveStop, HANDLE bRetrieveAutoForward, HANDLE bRetrieveAutoBackward, HANDLE bRetrieveManualForward, HANDLE bRetrieveManualBackward, HANDLE bRetrievePseudoRealtime)
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
	m_hAction[MMDRETRIEVETHREAD_ACTION_STOP] = bRetrieveStop;
	m_hAction[MMDRETRIEVETHREAD_ACTION_AUTOFORWARD] = bRetrieveAutoForward;
	m_hAction[MMDRETRIEVETHREAD_ACTION_AUTOBACKWARD] = bRetrieveAutoBackward;
	m_hAction[MMDRETRIEVETHREAD_ACTION_MANUALFORWARD] = bRetrieveManualForward;
	m_hAction[MMDRETRIEVETHREAD_ACTION_MANUALBACKWARD] = bRetrieveManualBackward;
	m_hAction[MMDRETRIEVETHREAD_ACTION_PSEUDOREALTIME] = bRetrievePseudoRealtime;
	return((ResetEvent(bInit)) ? CreateThread(pParentWnd, THREAD_PRIORITY_BELOW_NORMAL) : FALSE);
}

BOOL CMMDRetrieveThread::Stop()
{
	return((DestroyThread() >= 0) ? TRUE : FALSE);
}

BOOL CMMDRetrieveThread::InitializeTMData(CTMParameters &pTMParameters, BOOL bBadData)
{
	return m_cTMEnvironment.Initialize(pTMParameters, bBadData);
}

BOOL CMMDRetrieveThread::InitInstance()
{
	return AfxOleInit();
}

int CMMDRetrieveThread::Run()
{
	UINT  nAction;
	UINT  nResult;
	DWORD  dwResult;
	TIMETAG  tTime;
	CTimeKey  tTimeKey;
	CTimeTag  tTimeTag[2];
	CMMDWnd  *pMMDWnd = (CMMDWnd *)GetThreadInfo();

	StartRetrieving();
	if (m_cTMEnvironment.Create(GetDatabase()))
	{
		if (m_cTMProcessEngine.Open(GetDatabase(), GetAccountSpacecraftName(), GetRetrieveFileName(), &m_cTMEnvironment))
		{
			for (BeginWaitCursor(), pMMDWnd->SetRetrieveMode((m_nMode = (m_nMode & (MMD_RETRIEVE_AUTOBACKWARD | MMD_RETRIEVE_MANUALBACKWARD)) ? ((m_nMode & ~(MMD_RETRIEVE_AUTOBACKWARD | MMD_RETRIEVE_MANUALBACKWARD | MMD_RETRIEVE_STOPPED | MMD_RETRIEVE_RELATIVE)) | MMD_RETRIEVE_MANUALFORWARD) : (m_nMode & ~(MMD_RETRIEVE_STOPPED | MMD_RETRIEVE_RELATIVE)))), pMMDWnd->Reset(&m_cTMEnvironment), SignalObjectAndWait(m_bInit[0], m_bInit[1], INFINITE, FALSE), nResult = m_cTMProcessEngine.ProcessTMData(GetDatabase(), &m_cTMEnvironment, (tTimeKey = GetRetrieveStartTime())), nAction = 0; (dwResult = Wait(0)) == WAIT_TIMEOUT && !pMMDWnd->IsInitialized(); )
			{
				SwitchToThread();
				continue;
			}
			for (; dwResult == WAIT_TIMEOUT; BeginWaitCursor())
			{
				if ((GetRetrieveMode() & MMD_RETRIEVE_AUTOFORWARD) && !(GetRetrieveMode() & MMD_RETRIEVE_STOPPED))
				{
					for (; (nResult & HISTORYFILE_SUCCESS) && !(GetRetrieveMode() & MMD_RETRIEVE_RELATIVE) && (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT && ((!(GetRetrieveMode() & MMD_RETRIEVE_EXACTTIME) && !pMMDWnd->Update(tTimeKey, &m_cTMEnvironment, nResult)) || ((GetRetrieveMode() & MMD_RETRIEVE_EXACTTIME) && tTimeKey < GetRetrieveStartTime())); )
					{
						if (!((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, 0)) & HISTORYFILE_SUCCESS)) break;
						if (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS))
						{
							if (GetRetrieveMode() & MMD_RETRIEVE_STOPBYREALTIME)
							{
								pMMDWnd->SetMode(DISPLAY_MODE_REALTIME);
								pMMDWnd->ProcessRealtimeData();
								pMMDWnd->UpdateBars();
								break;
							}
							ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
							pMMDWnd->SetRetrieveMode(pMMDWnd->GetRetrieveMode() | MMD_RETRIEVE_STOPPED);
							pMMDWnd->UpdateBars();
							break;
						}
						if ((GetRetrieveMode() & MMD_RETRIEVE_STOPBYTIME) && GetRetrieveStopTime() < tTimeKey)
						{
							pMMDWnd->SetRetrieveMode(pMMDWnd->GetRetrieveMode() | MMD_RETRIEVE_STOPPED);
							pMMDWnd->UpdateBars();
							break;
						}
					}
					EndWaitCursor();
					if (pMMDWnd->GetMode() != DISPLAY_MODE_REALTIME)
					{
						if ((((nResult & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS))) || (GetRetrieveMode() & MMD_RETRIEVE_RELATIVE)) && (!(GetRetrieveMode() & MMD_RETRIEVE_STOPBYTIME) || GetRetrieveStopTime() >= tTimeKey) && dwResult == WAIT_TIMEOUT)
						{
							if ((!(GetRetrieveMode() & MMD_RETRIEVE_RELATIVE) && (!(GetRetrieveMode() & MMD_RETRIEVE_EXACTTIME) || pMMDWnd->Update(tTimeKey, &m_cTMEnvironment, (nResult = (nResult | HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS) & ~HISTORYFILE_TMUNIT) & (HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS)) || TRUE)) || (GetRetrieveMode() & MMD_RETRIEVE_RELATIVE))
							{
								for (; (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 10 * (10 - GetRetrieveSpeed())*(10 - GetRetrieveSpeed()))) == WAIT_TIMEOUT; )
								{
									if (((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, GetRetrieveInterval())) & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)))
									{
										if (!(GetRetrieveMode() & MMD_RETRIEVE_STOPBYTIME) || GetRetrieveStopTime() >= tTimeKey)
										{
											pMMDWnd->Update(tTimeKey, &m_cTMEnvironment, nResult);
											continue;
										}
									}
									if (nResult & HISTORYFILE_SUCCESS)
									{
										if (GetRetrieveMode() & MMD_RETRIEVE_STOPBYREALTIME)
										{
											pMMDWnd->SetMode(DISPLAY_MODE_REALTIME);
											pMMDWnd->ProcessRealtimeData();
											pMMDWnd->UpdateBars();
											break;
										}
										ReportEvent((GetRetrieveMode() & MMD_RETRIEVE_STOPBYEND) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING : USER_NOERROR);
										pMMDWnd->SetRetrieveMode(pMMDWnd->GetRetrieveMode() | MMD_RETRIEVE_STOPPED);
										pMMDWnd->UpdateBars();
									}
									break;
								}
							}
						}
						if (!(nResult & HISTORYFILE_SUCCESS))
						{
							ReportEvent((nResult == HISTORYFILE_DATA_NONE) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING : ((nResult == HISTORYFILE_OPEN_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_OPEN_FAILURE : ((nResult == HISTORYFILE_WRITE_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_WRITE_FAILURE : ((nResult == HISTORYFILE_READ_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_READ_FAILURE : ((nResult == HISTORYFILE_ERROR) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE : SYSTEM_NOERROR)))));
							pMMDWnd->SetRetrieveMode(pMMDWnd->GetRetrieveMode() | MMD_RETRIEVE_STOPPED);
							pMMDWnd->Reset(&m_cTMEnvironment);
							pMMDWnd->UpdateBars();
							break;
						}
					}
					if (pMMDWnd->GetMode() == DISPLAY_MODE_REALTIME) break;
				}
				if ((GetRetrieveMode() & MMD_RETRIEVE_AUTOBACKWARD) && !(GetRetrieveMode() & MMD_RETRIEVE_STOPPED))
				{
					if ((nResult & HISTORYFILE_SUCCESS) && (GetRetrieveMode() & MMD_RETRIEVE_RELATIVE) && dwResult == WAIT_TIMEOUT)
					{
						for (EndWaitCursor(); (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 10 * (10 - GetRetrieveSpeed())*(10 - GetRetrieveSpeed()))) == WAIT_TIMEOUT; )
						{
							if (((nResult = m_cTMProcessEngine.RewindTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, GetRetrieveInterval())) & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)))
							{
								pMMDWnd->Update(tTimeKey, &m_cTMEnvironment, nResult);
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
							pMMDWnd->Update(tTimeKey, &m_cTMEnvironment, nResult);
							pMMDWnd->SetRetrieveMode(pMMDWnd->GetRetrieveMode() | MMD_RETRIEVE_STOPPED);
							pMMDWnd->UpdateBars();
						}
					}
					else
					{
						ReportEvent((nResult == HISTORYFILE_DATA_NONE) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING : ((nResult == HISTORYFILE_OPEN_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_OPEN_FAILURE : ((nResult == HISTORYFILE_WRITE_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_WRITE_FAILURE : ((nResult == HISTORYFILE_READ_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_READ_FAILURE : ((nResult == HISTORYFILE_ERROR) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE : SYSTEM_NOERROR)))));
						pMMDWnd->SetRetrieveMode(pMMDWnd->GetRetrieveMode() | MMD_RETRIEVE_STOPPED);
						pMMDWnd->Reset(&m_cTMEnvironment);
						pMMDWnd->UpdateBars();
						EndWaitCursor();
						break;
					}
					EndWaitCursor();
				}
				if ((GetRetrieveMode() & MMD_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & MMD_RETRIEVE_STOPPED))
				{
					for (; (nResult & HISTORYFILE_SUCCESS) && !(GetRetrieveMode() & MMD_RETRIEVE_RELATIVE) && (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT && ((!(GetRetrieveMode() & MMD_RETRIEVE_EXACTTIME) && !pMMDWnd->Update(tTimeKey, &m_cTMEnvironment, nResult)) || ((GetRetrieveMode() & MMD_RETRIEVE_EXACTTIME) && tTimeKey < GetRetrieveStartTime())); )
					{
						if (!((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, 0)) & HISTORYFILE_SUCCESS)) break;
						if (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS))
						{
							if (GetRetrieveMode() & MMD_RETRIEVE_STOPBYREALTIME)
							{
								pMMDWnd->SetMode(DISPLAY_MODE_REALTIME);
								pMMDWnd->ProcessRealtimeData();
								pMMDWnd->UpdateBars();
								break;
							}
							ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
							pMMDWnd->SetRetrieveMode(pMMDWnd->GetRetrieveMode() | MMD_RETRIEVE_STOPPED);
							pMMDWnd->UpdateBars();
							break;
						}
					}
					EndWaitCursor();
					if (pMMDWnd->GetMode() != DISPLAY_MODE_REALTIME)
					{
						if ((((nResult & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS))) || (GetRetrieveMode() & MMD_RETRIEVE_RELATIVE)) && dwResult == WAIT_TIMEOUT)
						{
							if ((!(GetRetrieveMode() & MMD_RETRIEVE_RELATIVE) && (!(GetRetrieveMode() & MMD_RETRIEVE_EXACTTIME) || pMMDWnd->Update(tTimeKey, &m_cTMEnvironment, (nResult = (nResult | HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS) & ~HISTORYFILE_TMUNIT) & (HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS)) || TRUE)) || (GetRetrieveMode() & MMD_RETRIEVE_RELATIVE))
							{
								for (; (dwResult = (!(GetRetrieveMode() & MMD_RETRIEVE_RELATIVE) || nAction != MMDRETRIEVETHREAD_ACTION_MANUALFORWARD) ? Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, INFINITE) : (WAIT_OBJECT_0 + nAction + 1)) == WAIT_OBJECT_0 + MMDRETRIEVETHREAD_ACTION_MANUALFORWARD + 1; EndWaitCursor())
								{
									for (BeginWaitCursor(TRUE); (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT; )
									{
										if (((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, GetRetrieveInterval())) & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)))
										{
											if (pMMDWnd->Update(tTimeKey, &m_cTMEnvironment, nResult)) break;
											continue;
										}
										if (nResult & HISTORYFILE_SUCCESS)
										{
											if (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS))
											{
												if (GetRetrieveMode() & MMD_RETRIEVE_STOPBYREALTIME)
												{
													pMMDWnd->SetMode(DISPLAY_MODE_REALTIME);
													pMMDWnd->ProcessRealtimeData();
													pMMDWnd->UpdateBars();
													break;
												}
												ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
												pMMDWnd->SetRetrieveMode(pMMDWnd->GetRetrieveMode() | MMD_RETRIEVE_STOPPED);
												pMMDWnd->UpdateBars();
											}
										}
										break;
									}
									if (!(nResult & HISTORYFILE_SUCCESS) || (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS)) || pMMDWnd->GetMode() == DISPLAY_MODE_REALTIME || dwResult == WAIT_OBJECT_0)
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
							pMMDWnd->SetRetrieveMode(pMMDWnd->GetRetrieveMode() | MMD_RETRIEVE_STOPPED);
							pMMDWnd->Reset(&m_cTMEnvironment);
							pMMDWnd->UpdateBars();
							break;
						}
					}
					if (pMMDWnd->GetMode() == DISPLAY_MODE_REALTIME) break;
				}
				if ((GetRetrieveMode() & MMD_RETRIEVE_MANUALBACKWARD) && !(GetRetrieveMode() & MMD_RETRIEVE_STOPPED))
				{
					if ((nResult & HISTORYFILE_SUCCESS) && (GetRetrieveMode() & MMD_RETRIEVE_RELATIVE) && dwResult == WAIT_TIMEOUT)
					{
						for (EndWaitCursor(); (dwResult = (nAction != MMDRETRIEVETHREAD_ACTION_MANUALBACKWARD) ? Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, INFINITE) : (WAIT_OBJECT_0 + nAction + 1)) == WAIT_OBJECT_0 + MMDRETRIEVETHREAD_ACTION_MANUALBACKWARD + 1; EndWaitCursor())
						{
							for (BeginWaitCursor(TRUE); (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT; )
							{
								if (((nResult = m_cTMProcessEngine.RewindTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, GetRetrieveInterval())) & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)))
								{
									if (pMMDWnd->Update(tTimeKey, &m_cTMEnvironment, nResult)) break;
									continue;
								}
								if (nResult & HISTORYFILE_SUCCESS)
								{
									if (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS))
									{
										ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
										pMMDWnd->Update(tTimeKey, &m_cTMEnvironment, nResult);
										pMMDWnd->SetRetrieveMode(pMMDWnd->GetRetrieveMode() | MMD_RETRIEVE_STOPPED);
										pMMDWnd->UpdateBars();
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
						pMMDWnd->SetRetrieveMode(pMMDWnd->GetRetrieveMode() | MMD_RETRIEVE_STOPPED);
						pMMDWnd->Reset(&m_cTMEnvironment);
						pMMDWnd->UpdateBars();
						EndWaitCursor();
						break;
					}
					EndWaitCursor();
				}
				if ((GetRetrieveMode() & MMD_RETRIEVE_PSEUDOREALTIME) && !(GetRetrieveMode() & MMD_RETRIEVE_STOPPED))
				{
					for (; (nResult & HISTORYFILE_SUCCESS) && !(GetRetrieveMode() & MMD_RETRIEVE_RELATIVE) && (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT && ((!(GetRetrieveMode() & MMD_RETRIEVE_EXACTTIME) && !pMMDWnd->Update(tTimeKey, &m_cTMEnvironment, nResult)) || ((GetRetrieveMode() & MMD_RETRIEVE_EXACTTIME) && tTimeKey < GetRetrieveStartTime())); )
					{
						if (!((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, 0)) & HISTORYFILE_SUCCESS)) break;
						if (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS))
						{
							if (GetRetrieveMode() & MMD_RETRIEVE_STOPBYREALTIME)
							{
								pMMDWnd->SetMode(DISPLAY_MODE_REALTIME);
								pMMDWnd->ProcessRealtimeData();
								pMMDWnd->UpdateBars();
								break;
							}
							ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
							pMMDWnd->SetRetrieveMode(pMMDWnd->GetRetrieveMode() | MMD_RETRIEVE_STOPPED);
							pMMDWnd->UpdateBars();
							break;
						}
						if ((GetRetrieveMode() & MMD_RETRIEVE_STOPBYTIME) && GetRetrieveStopTime() < tTimeKey)
						{
							pMMDWnd->SetRetrieveMode(pMMDWnd->GetRetrieveMode() | MMD_RETRIEVE_STOPPED);
							pMMDWnd->UpdateBars();
							break;
						}
					}
					EndWaitCursor();
					if (pMMDWnd->GetMode() != DISPLAY_MODE_REALTIME)
					{
						if ((((nResult & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS))) || (GetRetrieveMode() & MMD_RETRIEVE_RELATIVE)) && (!(GetRetrieveMode() & MMD_RETRIEVE_STOPBYTIME) || GetRetrieveStopTime() >= tTimeKey) && dwResult == WAIT_TIMEOUT)
						{
							if ((!(GetRetrieveMode() & MMD_RETRIEVE_RELATIVE) && (!(GetRetrieveMode() & MMD_RETRIEVE_EXACTTIME) || pMMDWnd->Update(tTimeKey, &m_cTMEnvironment, (nResult = (nResult | HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS) & ~HISTORYFILE_TMUNIT) & (HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS)) || TRUE)) || (GetRetrieveMode() & MMD_RETRIEVE_RELATIVE))
							{
								for (tTimeTag[0] = ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)) ? ((nResult & HISTORYFILE_TMUNIT) ? m_cTMEnvironment.GetTMUnit()->GetTimeTag() : CTimeTag(tTimeKey)) : CTimeTag(tTimeKey), tTimeTag[1] = CTimeTag(), tTime = CTimeTag().GetTime(); (dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, 0, FALSE)) == WAIT_TIMEOUT; tTime = CTimeTag().GetTime())
								{
									if (((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(), &m_cTMEnvironment, tTimeKey, 0)) & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)))
									{
										if ((dwResult = Wait(m_hAction, sizeof(m_hAction) / sizeof(HANDLE), FALSE, (((nResult & HISTORYFILE_TMUNIT) && tTimeTag[1].GetTime() - tTimeTag[0].GetTime() + m_cTMEnvironment.GetTMUnit()->GetTimeTag().GetTime() > tTime) || ((nResult & HISTORYFILE_TMPARAMETERS) && tTimeTag[1].GetTime() - tTimeTag[0].GetTime() + CTimeTag(tTimeKey).GetTime() > tTime)) ? ((nResult & HISTORYFILE_TMUNIT) ? (DWORD)((tTimeTag[1].GetTime() - tTimeTag[0].GetTime() + m_cTMEnvironment.GetTMUnit()->GetTimeTag().GetTime() - tTime) / 1000) : (DWORD)((tTimeTag[1].GetTime() - tTimeTag[0].GetTime() + CTimeTag(tTimeKey).GetTime() - tTime) / 1000)) : 0)) != WAIT_TIMEOUT) break;
										if ((!(GetRetrieveMode() & MMD_RETRIEVE_STOPBYTIME) || GetRetrieveStopTime() >= tTimeKey) && ((nResult & HISTORYFILE_SYNCHRONIZE) || !tTimeTag[0].GetTime()))
										{
											tTimeTag[0] = (nResult & HISTORYFILE_TMUNIT) ? m_cTMEnvironment.GetTMUnit()->GetTimeTag() : CTimeTag(tTimeKey);
											tTimeTag[1] = tTime = CTimeTag().GetTime();
										}
										if (!(GetRetrieveMode() & MMD_RETRIEVE_STOPBYTIME) || GetRetrieveStopTime() >= tTimeKey)
										{
											pMMDWnd->Update(tTimeKey, &m_cTMEnvironment, nResult);
											continue;
										}
									}
									if (nResult & HISTORYFILE_SUCCESS)
									{
										if (GetRetrieveMode() & MMD_RETRIEVE_STOPBYREALTIME)
										{
											pMMDWnd->SetMode(DISPLAY_MODE_REALTIME);
											pMMDWnd->ProcessRealtimeData();
											pMMDWnd->UpdateBars();
											break;
										}
										ReportEvent((GetRetrieveMode() & MMD_RETRIEVE_STOPBYEND) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING : USER_NOERROR);
										pMMDWnd->SetRetrieveMode(pMMDWnd->GetRetrieveMode() | MMD_RETRIEVE_STOPPED);
										pMMDWnd->UpdateBars();
									}
									break;
								}
							}
						}
						if (!(nResult & HISTORYFILE_SUCCESS))
						{
							ReportEvent((nResult == HISTORYFILE_DATA_NONE) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING : ((nResult == HISTORYFILE_OPEN_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_OPEN_FAILURE : ((nResult == HISTORYFILE_WRITE_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_WRITE_FAILURE : ((nResult == HISTORYFILE_READ_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_READ_FAILURE : ((nResult == HISTORYFILE_ERROR) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE : SYSTEM_NOERROR)))));
							pMMDWnd->SetRetrieveMode(pMMDWnd->GetRetrieveMode() | MMD_RETRIEVE_STOPPED);
							pMMDWnd->Reset(&m_cTMEnvironment);
							pMMDWnd->UpdateBars();
							break;
						}
					}
					if (pMMDWnd->GetMode() == DISPLAY_MODE_REALTIME) break;
				}
				if ((GetRetrieveMode() & MMD_RETRIEVE_AUTOFORWARD) || (GetRetrieveMode() & MMD_RETRIEVE_AUTOBACKWARD) || (GetRetrieveMode() & MMD_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & MMD_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & MMD_RETRIEVE_PSEUDOREALTIME))
				{
					while ((dwResult = ((dwResult < WAIT_OBJECT_0 + MMDRETRIEVETHREAD_ACTION_AUTOFORWARD + 1 || dwResult > WAIT_OBJECT_0 + MMDRETRIEVETHREAD_ACTION_PSEUDOREALTIME + 1) && dwResult != WAIT_OBJECT_0) ? Wait(m_hAction, MMDRETRIEVETHREAD_ACTION_TYPES, FALSE, INFINITE, FALSE) : dwResult) == WAIT_OBJECT_0 + MMDRETRIEVETHREAD_ACTION_STOP + 1)
					{
						m_nMode = (GetRetrieveMode() & (MMD_RETRIEVE_STOPBYTIME | MMD_RETRIEVE_STOPBYEND | MMD_RETRIEVE_STOPBYREALTIME)) | MMD_RETRIEVE_STOPPED | MMD_RETRIEVE_RELATIVE;
						m_nMode |= ((GetRetrieveMode() & (MMD_RETRIEVE_STOPBYTIME | MMD_RETRIEVE_STOPBYEND | MMD_RETRIEVE_STOPBYREALTIME)) == 0) ? MMD_RETRIEVE_STOPBYREALTIME : 0;
						pMMDWnd->SetRetrieveMode(m_nMode);
						pMMDWnd->UpdateBars();
					}
					if (dwResult == WAIT_OBJECT_0 + MMDRETRIEVETHREAD_ACTION_AUTOFORWARD + 1)
					{
						m_nMode = (GetRetrieveMode() & (MMD_RETRIEVE_STOPBYTIME | MMD_RETRIEVE_STOPBYEND | MMD_RETRIEVE_STOPBYREALTIME)) | MMD_RETRIEVE_AUTOFORWARD | MMD_RETRIEVE_RELATIVE;
						m_nMode |= ((GetRetrieveMode() & (MMD_RETRIEVE_STOPBYTIME | MMD_RETRIEVE_STOPBYEND | MMD_RETRIEVE_STOPBYREALTIME)) == 0) ? MMD_RETRIEVE_STOPBYREALTIME : 0;
						nAction = MMDRETRIEVETHREAD_ACTION_AUTOFORWARD;
						pMMDWnd->SetRetrieveMode(m_nMode);
						pMMDWnd->UpdateBars();
						dwResult = WAIT_TIMEOUT;
						continue;
					}
					if (dwResult == WAIT_OBJECT_0 + MMDRETRIEVETHREAD_ACTION_AUTOBACKWARD + 1)
					{
						m_nMode = (GetRetrieveMode() & (MMD_RETRIEVE_STOPBYTIME | MMD_RETRIEVE_STOPBYEND | MMD_RETRIEVE_STOPBYREALTIME)) | MMD_RETRIEVE_AUTOBACKWARD | MMD_RETRIEVE_RELATIVE;
						m_nMode |= ((GetRetrieveMode() & (MMD_RETRIEVE_STOPBYTIME | MMD_RETRIEVE_STOPBYEND | MMD_RETRIEVE_STOPBYREALTIME)) == 0) ? MMD_RETRIEVE_STOPBYEND : 0;
						nAction = MMDRETRIEVETHREAD_ACTION_AUTOBACKWARD;
						pMMDWnd->SetRetrieveMode(m_nMode);
						pMMDWnd->UpdateBars();
						dwResult = WAIT_TIMEOUT;
						continue;
					}
					if (dwResult == WAIT_OBJECT_0 + MMDRETRIEVETHREAD_ACTION_MANUALFORWARD + 1)
					{
						m_nMode = (GetRetrieveMode() & (MMD_RETRIEVE_STOPBYTIME | MMD_RETRIEVE_STOPBYEND | MMD_RETRIEVE_STOPBYREALTIME)) | MMD_RETRIEVE_MANUALFORWARD | MMD_RETRIEVE_RELATIVE;
						nAction = MMDRETRIEVETHREAD_ACTION_MANUALFORWARD;
						pMMDWnd->SetRetrieveMode(m_nMode);
						pMMDWnd->UpdateBars();
						dwResult = WAIT_TIMEOUT;
						continue;
					}
					if (dwResult == WAIT_OBJECT_0 + MMDRETRIEVETHREAD_ACTION_MANUALBACKWARD + 1)
					{
						m_nMode = (GetRetrieveMode() & (MMD_RETRIEVE_STOPBYTIME | MMD_RETRIEVE_STOPBYEND | MMD_RETRIEVE_STOPBYREALTIME)) | MMD_RETRIEVE_MANUALBACKWARD | MMD_RETRIEVE_RELATIVE;
						nAction = MMDRETRIEVETHREAD_ACTION_MANUALBACKWARD;
						pMMDWnd->SetRetrieveMode(m_nMode);
						pMMDWnd->UpdateBars();
						dwResult = WAIT_TIMEOUT;
						continue;
					}
					if (dwResult == WAIT_OBJECT_0 + MMDRETRIEVETHREAD_ACTION_PSEUDOREALTIME + 1)
					{
						m_nMode = (GetRetrieveMode() & (MMD_RETRIEVE_STOPBYTIME | MMD_RETRIEVE_STOPBYEND | MMD_RETRIEVE_STOPBYREALTIME)) | MMD_RETRIEVE_PSEUDOREALTIME | MMD_RETRIEVE_RELATIVE;
						m_nMode |= ((GetRetrieveMode() & (MMD_RETRIEVE_STOPBYTIME | MMD_RETRIEVE_STOPBYEND | MMD_RETRIEVE_STOPBYREALTIME)) == 0) ? MMD_RETRIEVE_STOPBYREALTIME : 0;
						nAction = MMDRETRIEVETHREAD_ACTION_PSEUDOREALTIME;
						pMMDWnd->SetRetrieveMode(m_nMode);
						pMMDWnd->UpdateBars();
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

VOID CMMDRetrieveThread::StartRetrieving()
{
	InterlockedExchange(m_pbFlag, TRUE);
}

VOID CMMDRetrieveThread::StopRetrieving()
{
	InterlockedExchange(m_pbFlag, FALSE);
}

UINT CMMDRetrieveThread::GetRetrieveMode() CONST
{
	return((IsThreadActive()) ? m_nMode : 0);
}

UINT CMMDRetrieveThread::GetRetrieveSpeed() CONST
{
	return((IsThreadActive()) ? m_nSpeed : 0);
}

CTimeSpan CMMDRetrieveThread::GetRetrieveInterval() CONST
{
	return((IsThreadActive()) ? m_tInterval.GetTotalSeconds() : 0);
}

CTimeKey CMMDRetrieveThread::GetRetrieveStartTime() CONST
{
	return((IsThreadActive()) ? m_tStartTime : 0);
}

CTimeKey CMMDRetrieveThread::GetRetrieveStopTime() CONST
{
	return((IsThreadActive()) ? m_tStopTime : 0);
}

CString CMMDRetrieveThread::GetRetrieveFileName() CONST
{
	return((IsThreadActive()) ? (LPCTSTR)m_szFileName : EMPTYSTRING);
}

VOID CMMDRetrieveThread::BeginWaitCursor(BOOL bForced)
{
	POINT  ptCursor;
	CMMDWnd  *pMMDWnd;
	CHourglassCursor  cCursor;

	for (GetCursorPos(&ptCursor), InterlockedExchange(m_pbFlag, MAKELONG(TRUE, ((m_nMode & MMD_RETRIEVE_RELATIVE) != MMD_RETRIEVE_RELATIVE || bForced) ? TRUE : FALSE)), SetCursorPos(ptCursor.x, ptCursor.y); (pMMDWnd = (CMMDWnd *)GetThreadInfo()); )
	{
		pMMDWnd->UpdateBars();
		break;
	}
}

VOID CMMDRetrieveThread::EndWaitCursor()
{
	POINT  ptCursor;
	CMMDWnd  *pMMDWnd;
	CHourglassCursor  cCursor;

	for (GetCursorPos(&ptCursor), InterlockedExchange(m_pbFlag, LOWORD(*m_pbFlag)), SetCursorPos(ptCursor.x, ptCursor.y); (pMMDWnd = (CMMDWnd *)GetThreadInfo()); )
	{
		pMMDWnd->UpdateBars();
		break;
	}
}

BEGIN_MESSAGE_MAP(CMMDRetrieveThread, CThread)
	//{{AFX_MSG_MAP(CMMDRetrieveThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDRetrieveThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CMMDPrintThread

IMPLEMENT_DYNCREATE(CMMDPrintThread, CThread)

BOOL CMMDPrintThread::Start(CMMDWnd *pParentWnd)
{
	return CreateThread(pParentWnd);
}

BOOL CMMDPrintThread::Stop()
{
	return((DestroyThread() >= 0) ? TRUE : FALSE);
}

BOOL CMMDPrintThread::SetPrintJobs(CONST CMMDPrintJobs &pPrintJobs)
{
	INT  nJob[2][2];
	INT  nJobs[2][2];
	CMMDPrintJobInfo  *pJobInfo;
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
			if ((pJobInfo = new CMMDPrintJobInfo))
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

BOOL CMMDPrintThread::GetPrintJobs(CMMDPrintJobs &pPrintJobs) CONST
{
	CByteArray  nPrintInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(((m_pPrintJobs.GetSize() > 0 && pPrintJobs.Copy(&m_pPrintJobs)) || pPrintJobs.Unmap(nPrintInfo)) ? TRUE : FALSE);
}

int CMMDPrintThread::Run()
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
	CMMDPrintJobInfo  *pJobInfo[2];
	CMMDWnd  *pMMDWnd = (CMMDWnd *)GetThreadInfo();

	for (dwJobResult = 0; Lock(); )
	{
		if (dwJobResult == WAIT_OBJECT_0 + 1 || !dwJobResult)
		{
			for (nJob = 0, nJobs = (INT)m_pPrintJobs.GetSize(); nJob < nJobs; nJob++)
			{
				if ((pJobInfo[0] = m_pPrintJobs.GetAt(nJob)) && (pJobInfo[0]->GetPrintMode() & MMD_PRINT_ACTIVE))
				{
					if (pJobInfo[0]->GetPrintAtDailyTime(tJobDailyTime) || pJobInfo[0]->GetPrintAtDailyTime(tJobDailyTime, nJobStopCount) || pJobInfo[0]->GetPrintAtDailyTime(tJobDailyTime, tJobStopTime))
					{
						pJobInfo[0]->SetPrintLastDailyTime(((tJobTime = CTime::GetCurrentTime().GetTime()).GetTime() % SECONDSPERDAY >= tJobDailyTime.GetTotalSeconds()) ? ((SECONDSPERDAY*(tJobTime.GetTime() / SECONDSPERDAY)) + tJobDailyTime.GetTotalSeconds()) : ((SECONDSPERDAY*(tJobTime.GetTime() / SECONDSPERDAY - 1)) + tJobDailyTime.GetTotalSeconds()));
						continue;
					}
				}
			}
		}
		if ((pJobInfo[0] = ((tJobInterval = m_pPrintJobs.Schedule()) == 0) ? m_pPrintJobs.GetAt(0) : (CMMDPrintJobInfo *)NULL))
		{
			for (bJobPrint = pMMDWnd->Print(pJobInfo[0]); (pJobInfo[0]->GetPrintMode() & MMD_PRINT_CLEARCOMMENTS) && bJobPrint; )
			{
				for (nJob = 1, nJobs = (INT)m_pPrintJobs.GetSize(); nJob < nJobs; nJob++)
				{
					if ((pJobInfo[1] = m_pPrintJobs.GetAt(nJob)))
					{
						if (pJobInfo[0]->GetName() == pJobInfo[1]->GetName())
						{
							pJobInfo[1]->SetPrintMode(pJobInfo[0]->GetPrintMode() & ~MMD_PRINT_CLEARCOMMENTS);
							pJobInfo[1]->SetComments(EMPTYSTRING);
							break;
						}
					}
				}
				break;
			}
			ReportEvent((!bJobPrint) ? SYSTEM_WARNING_MMD_PRINT_FAILURE : SYSTEM_NOERROR);
			m_pPrintJobs.RemoveAt(0);
			delete pJobInfo[0];
		}
		Unlock();
		if ((dwJobResult = Wait(m_cEvent, FALSE, (tJobInterval >= 0) ? (DWORD)(1000 * min(tJobInterval, SECONDSPERDAY)) : INFINITE)) != WAIT_TIMEOUT  &&  dwJobResult != WAIT_OBJECT_0 + 1) break;
	}
	return 0;
}

BEGIN_MESSAGE_MAP(CMMDPrintThread, CThread)
	//{{AFX_MSG_MAP(CMMDPrintThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDPrintThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CMMDDocument

IMPLEMENT_DYNCREATE(CMMDDocument, COleDocument)

CMMDDocument::CMMDDocument() : COleDocument()
{
	m_bAutoDelete = FALSE;
}

CMMDDocument::~CMMDDocument()
{
	DeleteContents();
}

INT CMMDDocument::EnumItems(CPtrArray &pItems) CONST
{
	pItems.RemoveAll();
	return((EnumItemsInList(this, pItems)) ? (INT)pItems.GetSize() : -1);
}

POSITION CMMDDocument::FindItem(CMimicsClientItem *pItem) CONST
{
	return FindItemInList(this, pItem);
}

CDocItem *CMMDDocument::GetNextItem(POSITION &lPosition) CONST
{
	CDocItem  *pItem;
	CONST CMMDDocument  *pDocument;

	return((!(pItem = (CDocItem *)m_docItemList.GetNext(lPosition))) ? (((pDocument = FindPositionInList(this, lPosition))) ? (CDocItem *)pDocument->m_docItemList.GetNext(lPosition) : (CDocItem *)NULL) : pItem);
}

CDocItem *CMMDDocument::GetPreviousItem(POSITION &lPosition) CONST
{
	CDocItem  *pItem;
	CONST CMMDDocument  *pDocument;

	return((!(pItem = (CDocItem *)m_docItemList.GetPrev(lPosition))) ? (((pDocument = FindPositionInList(this, lPosition))) ? (CDocItem *)pDocument->m_docItemList.GetPrev(lPosition) : (CDocItem *)NULL) : pItem);
}

UINT CMMDDocument::GetItemCount() CONST
{
	return((UINT)m_docItemList.GetCount());
}

POSITION CMMDDocument::GetStartPosition() CONST
{
	return m_docItemList.GetHeadPosition();
}

POSITION CMMDDocument::GetStopPosition() CONST
{
	return m_docItemList.GetTailPosition();
}

BOOL CMMDDocument::SaveModified()
{
	return TRUE;
}

BOOL CMMDDocument::OnNewDocument()
{
	return COleDocument::OnNewDocument();
}

void CMMDDocument::OnCloseDocument()
{
	DeleteContents();
}

BOOL CMMDDocument::CanCloseFrame(CFrameWnd *pFrame)
{
	return TRUE;
}

VOID CMMDDocument::DeleteContents()
{
	POSITION  lPosition;
	CMimicsItem  *pItem;

	for (lPosition = m_docItemList.GetHeadPosition(); lPosition; )
	{
		if ((pItem = (CMimicsItem *)m_docItemList.GetNext(lPosition)))
		{
			pItem->Release();
			pItem->Delete();
		}
	}
	SetModifiedFlag(FALSE);
	COleDocument::DeleteContents();
}

BOOL CMMDDocument::Copy(CONST CMMDDocument *pDocument)
{
	POSITION  lPosition;
	CMimicsItem  *pItem[2];

	for (lPosition = pDocument->m_docItemList.GetHeadPosition(), DeleteContents(); lPosition; )
	{
		if ((pItem[0] = (CMimicsItem *)pDocument->m_docItemList.GetNext(lPosition)))
		{
			if ((pItem[1] = CMimicsItem::AllocateFromItem(pItem[0])))
			{
				if (pItem[1]->Copy(pItem[0]))
				{
					AddItem(pItem[1]);
					continue;
				}
				delete pItem[1];
			}
		}
		lPosition = (POSITION)-1;
		break;
	}
	return((!lPosition) ? TRUE : FALSE);
}

BOOL CMMDDocument::Compare(CONST CMMDDocument *pDocument) CONST
{
	POSITION  lPosition[2];
	CMimicsItem  *pItem;

	for (lPosition[0] = pDocument->m_docItemList.GetHeadPosition(), lPosition[1] = m_docItemList.GetHeadPosition(); pDocument->m_docItemList.GetCount() == m_docItemList.GetCount() && lPosition[0] && lPosition[1]; )
	{
		if ((pItem = (CMimicsItem *)pDocument->m_docItemList.GetNext(lPosition[0])) && pItem->Compare((CMimicsItem *)m_docItemList.GetNext(lPosition[1]))) continue;
		lPosition[0] = pDocument->m_docItemList.GetHeadPosition();
		lPosition[1] = m_docItemList.GetHeadPosition();
		break;
	}
	return((pDocument->m_docItemList.GetCount() == m_docItemList.GetCount()) ? ((!lPosition[0] && !lPosition[1]) ? TRUE : FALSE) : FALSE);
}

BOOL CMMDDocument::Map(CMMDLayout &cLayout) CONST
{
	POSITION  lPosition;
	CMimicsItem  *pItem;
	CMMDLayoutItem  *pLayoutItem;

	for (lPosition = m_docItemList.GetHeadPosition(); lPosition; )
	{
		if ((pItem = (CMimicsItem *)m_docItemList.GetNext(lPosition)))
		{
			if ((pLayoutItem = new CMMDLayoutItem) && pItem->Map(pLayoutItem) && cLayout.Add(pLayoutItem) >= 0) continue;
			delete pLayoutItem;
		}
		lPosition = (POSITION)-1;
		break;
	}
	return((!lPosition) ? TRUE : FALSE);
}

BOOL CMMDDocument::Unmap(CONST CMMDLayout &cLayout)
{
	INT  nItem;
	INT  nItems;
	CMimicsItem  *pItem;
	CMMDLayoutItem  *pLayoutItem;

	for (nItem = 0, nItems = (INT)cLayout.GetSize(), DeleteContents(); nItem < nItems; nItem++)
	{
		if ((pLayoutItem = cLayout.GetAt(nItem)) != (CMMDLayoutItem *)NULL)
		{
			if ((pItem = CMimicsItem::AllocateFromItem(pLayoutItem)))
			{
				if (pItem->Unmap(pLayoutItem))
				{
					AddItem(pItem);
					continue;
				}
				delete pItem;
			}
		}
		break;
	}
	return((nItem == nItems) ? TRUE : FALSE);
}

BOOL CMMDDocument::EnumItemsInList(CONST CMMDDocument *pDocument, CPtrArray &pItems) CONST
{
	POSITION  lPosition;
	CMimicsItem  *pMimicsItem;
	CMimicsGroup  *pMimicsGroup;

	for (lPosition = pDocument->m_docItemList.GetHeadPosition(); lPosition; )
	{
		if ((pMimicsItem = (CMimicsItem *)pDocument->m_docItemList.GetNext(lPosition)))
		{
			if (pMimicsItem->IsKindOf(RUNTIME_CLASS(CMimicsGroup))) EnumItemsInList((pMimicsGroup = (CMimicsGroup *)pMimicsItem)->GetItemList(), pItems);
			pItems.Add(pMimicsItem);
			continue;
		}
		lPosition = (POSITION)-1;
		break;
	}
	return((!lPosition) ? TRUE : FALSE);
}

POSITION CMMDDocument::FindItemInList(CONST CMMDDocument *pDocument, CMimicsClientItem *pItem) CONST
{
	POSITION  lPosition[2];
	CMimicsItem  *pMimicsItem;
	CMimicsGroup  *pMimicsGroup;

	for (lPosition[0] = pDocument->m_docItemList.GetHeadPosition(), lPosition[1] = (POSITION)NULL; lPosition[0]; )
	{
		if ((pMimicsItem = (CMimicsItem *)pDocument->m_docItemList.GetNext(lPosition[0])))
		{
			if (pMimicsItem->IsKindOf(RUNTIME_CLASS(CMimicsGroup)) && pMimicsItem != pItem)
			{
				if ((pMimicsGroup = (CMimicsGroup *)pMimicsItem) != (CMimicsGroup *)NULL)
				{
					if ((lPosition[1] = FindItemInList(pMimicsGroup->GetItemList(), pItem))) break;
					continue;
				}
			}
			if (pMimicsItem == pItem)
			{
				lPosition[1] = pDocument->m_docItemList.Find(pItem);
				break;
			}
			continue;
		}
		break;
	}
	return lPosition[1];
}

CONST CMMDDocument *CMMDDocument::FindPositionInList(CONST CMMDDocument *pDocument, POSITION lPosition) CONST
{
	POSITION  lItemPos;
	CMimicsItem  *pMimicsItem;
	CMimicsGroup  *pMimicsGroup;
	CONST CMMDDocument  *pItemList;

	for (lItemPos = pDocument->m_docItemList.GetHeadPosition(), pItemList = pDocument; lItemPos && lPosition && lItemPos != lPosition; )
	{
		if ((pMimicsItem = (CMimicsItem *)pDocument->m_docItemList.GetNext(lItemPos)))
		{
			if (pMimicsItem->IsKindOf(RUNTIME_CLASS(CMimicsGroup)) && lItemPos != lPosition)
			{
				if ((pMimicsGroup = (CMimicsGroup *)pMimicsItem) != (CMimicsGroup *)NULL)
				{
					if ((pItemList = FindPositionInList(pMimicsGroup->GetItemList(), lPosition)))
					{
						lItemPos = lPosition;
						break;
					}
					continue;
				}
			}
			if (lItemPos == lPosition)
			{
				pItemList = pDocument;
				break;
			}
			continue;
		}
		break;
	}
	return((lItemPos  &&  lItemPos == lPosition) ? pItemList : (CONST CMMDDocument *) NULL);
}

BEGIN_MESSAGE_MAP(CMMDDocument, COleDocument)
	//{{AFX_MSG_MAP(CMMDDocument)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDDocument serialization

void CMMDDocument::Serialize(CArchive &ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMMDDocument commands


////////////////////////////////////////////////////////////////////////////
// CMimicsItemDispatchDriver properties

VOID CMimicsItemDispatchDriver::SetName(LPCTSTR pszName)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_NAME));

	SetProperty(GetDispatchID(szDispatch), VT_BSTR, pszName);
}

CString CMimicsItemDispatchDriver::GetName() CONST
{
	CString  szName;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_NAME));

	GetProperty(GetDispatchID(szDispatch), VT_BSTR, &szName);
	return szName;
}

VOID CMimicsItemDispatchDriver::SetType(LPCTSTR pszType)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_TYPE));

	SetProperty(GetDispatchID(szDispatch), VT_BSTR, pszType);
}

CString CMimicsItemDispatchDriver::GetType() CONST
{
	CString  szType;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_TYPE));

	GetProperty(GetDispatchID(szDispatch), VT_BSTR, &szType);
	return szType;
}

VOID CMimicsItemDispatchDriver::SetToolTipText(LPCTSTR pszText)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_TOOLTIPTEXT));

	SetProperty(GetDispatchID(szDispatch), VT_BSTR, pszText);
}

CString CMimicsItemDispatchDriver::GetToolTipText() CONST
{
	CString  szText;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_TOOLTIPTEXT));

	GetProperty(GetDispatchID(szDispatch), VT_BSTR, &szText);
	return szText;
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsItemDispatchDriver operations

VOID CMimicsItemDispatchDriver::SetInitialSize(CONST SIZE &size)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETINITIALSIZE));
	static BYTE  pParameters[] = VTS_XSIZE_PIXELS VTS_YSIZE_PIXELS;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, size.cx, size.cy);
}

CSize CMimicsItemDispatchDriver::GetInitialSize() CONST
{
	OLE_XSIZE_PIXELS  cx;
	OLE_YSIZE_PIXELS  cy;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETINITIALSIZE));
	static BYTE  pParameters[] = VTS_PXSIZE_PIXELS VTS_PYSIZE_PIXELS;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, &cx, &cy);
	return CSize(cx, cy);
}

VOID CMimicsItemDispatchDriver::Show()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SHOW));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsItemDispatchDriver::Hide()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_HIDE));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

BOOL CMimicsItemDispatchDriver::IsVisible() CONST
{
	BOOL  bVisible;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISVISIBLE));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bVisible, (const BYTE *)NULL);
	return bVisible;
}

BOOL CMimicsItemDispatchDriver::Blink(INT nInterval)
{
	BOOL  bResult;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_BLINK));
	static BYTE  pParameters[] = VTS_I4;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bResult, pParameters, nInterval);
	return bResult;
}

VOID CMimicsItemDispatchDriver::Draw(HDC hDC, CONST RECT *pRect, CONST XFORM *pxForm, BOOL bShape)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_DRAW));
	static BYTE  pParameters[] = VTS_HANDLE VTS_PVARIANT VTS_PVARIANT VTS_BOOL;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, hDC, pRect, pxForm, bShape);
}

COleDispatchDriver *CMimicsItemDispatchDriver::GetDispatchDriver() CONST
{
	return((COleDispatchDriver *) this);
}

DISPID CMimicsItemDispatchDriver::GetDispatchID(OLECHAR FAR *pszMethod) CONST
{
	DISPID  nDispID;

	return((m_lpDispatch != (LPDISPATCH)NULL  &&  m_lpDispatch->GetIDsOfNames(IID_NULL, &pszMethod, 1, GetLanguageID(), &nDispID) == S_OK) ? nDispID : 0);
}


////////////////////////////////////////////////////////////////////////////
// CMimicsLineItemDispatchDriver properties

VOID CMimicsLineItemDispatchDriver::SetStyle(INT nStyle)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nStyle);
}

INT CMimicsLineItemDispatchDriver::GetStyle() CONST
{
	INT  nStyle;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nStyle);
	return nStyle;
}

VOID CMimicsLineItemDispatchDriver::SetColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_COLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsLineItemDispatchDriver::GetColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_COLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsLineItemDispatchDriver::SetThickness(INT nWidth)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_THICKNESS));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nWidth);
}

INT CMimicsLineItemDispatchDriver::GetThickness() CONST
{
	INT  nWidth;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_THICKNESS));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nWidth);
	return nWidth;
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsLineItemDispatchDriver operations

VOID CMimicsLineItemDispatchDriver::Arrow(BOOL bEnable)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ARROW));
	static BYTE  pParameters[] = VTS_BOOL;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, bEnable);
}

VOID CMimicsLineItemDispatchDriver::DoubleArrow(BOOL bEnable)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_DOUBLEARROW));
	static BYTE  pParameters[] = VTS_BOOL;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, bEnable);
}

VOID CMimicsLineItemDispatchDriver::Cross(BOOL bEnable)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_CROSS));
	static BYTE  pParameters[] = VTS_BOOL;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, bEnable);
}

BOOL CMimicsLineItemDispatchDriver::SetCrossPt(double fPt)
{
	BOOL  bResult;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETCROSSPT));
	static BYTE  pParameters[] = VTS_R8;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bResult, pParameters, fPt);
	return bResult;
}

BOOL CMimicsLineItemDispatchDriver::GetCrossPt(double *fPt) CONST
{
	BOOL  bResult;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETCROSSPT));
	static BYTE  pParameters[] = VTS_PR8;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bResult, pParameters, fPt);
	return bResult;
}

BOOL CMimicsLineItemDispatchDriver::IsArrow() CONST
{
	BOOL  bArrow;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISARROW));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bArrow, (const BYTE *)NULL);
	return bArrow;
}

BOOL CMimicsLineItemDispatchDriver::IsDoubleArrow() CONST
{
	BOOL  bDoubleArrow;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISDOUBLEARROW));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bDoubleArrow, (const BYTE *)NULL);
	return bDoubleArrow;
}

BOOL CMimicsLineItemDispatchDriver::IsCross() CONST
{
	BOOL  bCross;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISCROSS));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bCross, (const BYTE *)NULL);
	return bCross;
}

VOID CMimicsLineItemDispatchDriver::Solid()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SOLID));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsLineItemDispatchDriver::Dash()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_DASH));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsLineItemDispatchDriver::Dot()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_DOT));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsLineItemDispatchDriver::DashDot()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_DASHDOT));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsLineItemDispatchDriver::DashDotDot()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_DASHDOTDOT));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

BOOL CMimicsLineItemDispatchDriver::IsSolid() CONST
{
	BOOL  bSolid;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISSOLID));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bSolid, (const BYTE *)NULL);
	return bSolid;
}

BOOL CMimicsLineItemDispatchDriver::IsDashed() CONST
{
	BOOL  bDashed;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISDASHED));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bDashed, (const BYTE *)NULL);
	return bDashed;
}

BOOL CMimicsLineItemDispatchDriver::IsDotted() CONST
{
	BOOL  bDotted;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISDOTTED));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bDotted, (const BYTE *)NULL);
	return bDotted;
}

BOOL CMimicsLineItemDispatchDriver::IsDashDotted() CONST
{
	BOOL  bDashDotted;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISDASHDOTTED));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bDashDotted, (const BYTE *)NULL);
	return bDashDotted;
}

BOOL CMimicsLineItemDispatchDriver::IsDashDotDotted() CONST
{
	BOOL  bDashDotDotted;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISDASHDOTDOTTED));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bDashDotDotted, (const BYTE *)NULL);
	return bDashDotDotted;
}


////////////////////////////////////////////////////////////////////////////
// CMimicsRectangleItemDispatchDriver properties

VOID CMimicsRectangleItemDispatchDriver::SetStyle(INT nStyle)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nStyle);
}

INT CMimicsRectangleItemDispatchDriver::GetStyle() CONST
{
	INT  nStyle;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nStyle);
	return nStyle;
}

VOID CMimicsRectangleItemDispatchDriver::SetBorderSize(INT nSize)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSIZE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nSize);
}

INT CMimicsRectangleItemDispatchDriver::GetBorderSize() CONST
{
	INT  nSize;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSIZE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nSize);
	return nSize;
}

VOID CMimicsRectangleItemDispatchDriver::SetBorderStyle(INT nStyle)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSTYLE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nStyle);
}

INT CMimicsRectangleItemDispatchDriver::GetBorderStyle() CONST
{
	INT  nStyle;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSTYLE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nStyle);
	return nStyle;
}

VOID CMimicsRectangleItemDispatchDriver::SetBorderColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsRectangleItemDispatchDriver::GetBorderColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsRectangleItemDispatchDriver::SetInteriorColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsRectangleItemDispatchDriver::GetInteriorColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsRectangleItemDispatchDriver operations

VOID CMimicsRectangleItemDispatchDriver::SetInteriorHatch(INT nHatch, COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETINTERIORHATCH));
	static BYTE  pParameters[] = VTS_I4 VTS_COLOR;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, nHatch, nColor);
}

BOOL CMimicsRectangleItemDispatchDriver::GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST
{
	BOOL  bHatch;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETINTERIORHATCH));
	static BYTE  pParameters[] = VTS_PI4 VTS_PCOLOR;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bHatch, pParameters, &nHatch, &nColor);
	return bHatch;
}


////////////////////////////////////////////////////////////////////////////
// CMimicsEllipseItemDispatchDriver properties

VOID CMimicsEllipseItemDispatchDriver::SetStyle(INT nStyle)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nStyle);
}

INT CMimicsEllipseItemDispatchDriver::GetStyle() CONST
{
	INT  nStyle;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nStyle);
	return nStyle;
}

VOID CMimicsEllipseItemDispatchDriver::SetBorderSize(INT nSize)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSIZE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nSize);
}

INT CMimicsEllipseItemDispatchDriver::GetBorderSize() CONST
{
	INT  nSize;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSIZE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nSize);
	return nSize;
}

VOID CMimicsEllipseItemDispatchDriver::SetBorderStyle(INT nStyle)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSTYLE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nStyle);
}

INT CMimicsEllipseItemDispatchDriver::GetBorderStyle() CONST
{
	INT  nStyle;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSTYLE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nStyle);
	return nStyle;
}

VOID CMimicsEllipseItemDispatchDriver::SetBorderColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsEllipseItemDispatchDriver::GetBorderColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsEllipseItemDispatchDriver::SetInteriorColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsEllipseItemDispatchDriver::GetInteriorColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsEllipseItemDispatchDriver operations

VOID CMimicsEllipseItemDispatchDriver::SetInteriorHatch(INT nHatch, COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETINTERIORHATCH));
	static BYTE  pParameters[] = VTS_I4 VTS_COLOR;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, nHatch, nColor);
}

BOOL CMimicsEllipseItemDispatchDriver::GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST
{
	BOOL  bHatch;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETINTERIORHATCH));
	static BYTE  pParameters[] = VTS_PI4 VTS_PCOLOR;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bHatch, pParameters, &nHatch, &nColor);
	return bHatch;
}


////////////////////////////////////////////////////////////////////////////
// CMimicsArcItemDispatchDriver properties

VOID CMimicsArcItemDispatchDriver::SetStyle(INT nStyle)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nStyle);
}

INT CMimicsArcItemDispatchDriver::GetStyle() CONST
{
	INT  nStyle;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nStyle);
	return nStyle;
}

VOID CMimicsArcItemDispatchDriver::SetBorderSize(INT nSize)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSIZE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nSize);
}

INT CMimicsArcItemDispatchDriver::GetBorderSize() CONST
{
	INT  nSize;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSIZE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nSize);
	return nSize;
}

VOID CMimicsArcItemDispatchDriver::SetBorderStyle(INT nStyle)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSTYLE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nStyle);
}

INT CMimicsArcItemDispatchDriver::GetBorderStyle() CONST
{
	INT  nStyle;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSTYLE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nStyle);
	return nStyle;
}

VOID CMimicsArcItemDispatchDriver::SetBorderColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsArcItemDispatchDriver::GetBorderColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsArcItemDispatchDriver::SetInteriorColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsArcItemDispatchDriver::GetInteriorColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsArcItemDispatchDriver operations

VOID CMimicsArcItemDispatchDriver::SetInteriorHatch(INT nHatch, COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETINTERIORHATCH));
	static BYTE  pParameters[] = VTS_I4 VTS_COLOR;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, nHatch, nColor);
}

BOOL CMimicsArcItemDispatchDriver::GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST
{
	BOOL  bHatch;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETINTERIORHATCH));
	static BYTE  pParameters[] = VTS_PI4 VTS_PCOLOR;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bHatch, pParameters, &nHatch, &nColor);
	return bHatch;
}

VOID CMimicsArcItemDispatchDriver::SetRadials(double fRadial1, double fRadial2)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETRADIALS));
	static BYTE  pParameters[] = VTS_R8 VTS_R8;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, fRadial1, fRadial2);
}

VOID CMimicsArcItemDispatchDriver::GetRadials(double &fRadial1, double &fRadial2) CONST
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETRADIALS));
	static BYTE  pParameters[] = VTS_PR8 VTS_PR8;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, &fRadial1, &fRadial2);
}


////////////////////////////////////////////////////////////////////////////
// CMimicsTriangleItemDispatchDriver properties

VOID CMimicsTriangleItemDispatchDriver::SetStyle(INT nStyle)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nStyle);
}

INT CMimicsTriangleItemDispatchDriver::GetStyle() CONST
{
	INT  nStyle;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nStyle);
	return nStyle;
}

VOID CMimicsTriangleItemDispatchDriver::SetBorderSize(INT nSize)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSIZE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nSize);
}

INT CMimicsTriangleItemDispatchDriver::GetBorderSize() CONST
{
	INT  nSize;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSIZE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nSize);
	return nSize;
}

VOID CMimicsTriangleItemDispatchDriver::SetBorderStyle(INT nStyle)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSTYLE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nStyle);
}

INT CMimicsTriangleItemDispatchDriver::GetBorderStyle() CONST
{
	INT  nStyle;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERSTYLE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nStyle);
	return nStyle;
}

VOID CMimicsTriangleItemDispatchDriver::SetBorderColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsTriangleItemDispatchDriver::GetBorderColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BORDERCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsTriangleItemDispatchDriver::SetInteriorColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsTriangleItemDispatchDriver::GetInteriorColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsTriangleItemDispatchDriver operations

VOID CMimicsTriangleItemDispatchDriver::SetInteriorHatch(INT nHatch, COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETINTERIORHATCH));
	static BYTE  pParameters[] = VTS_I4 VTS_COLOR;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, nHatch, nColor);
}

BOOL CMimicsTriangleItemDispatchDriver::GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST
{
	BOOL  bHatch;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETINTERIORHATCH));
	static BYTE  pParameters[] = VTS_PI4 VTS_PCOLOR;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bHatch, pParameters, &nHatch, &nColor);
	return bHatch;
}

VOID CMimicsTriangleItemDispatchDriver::SetEdges(double x1, double y1, double x2, double y2, double x3, double y3)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETEDGES));
	static BYTE  pParameters[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_R8;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, x1, y1, x2, y2, x3, y3);
}

VOID CMimicsTriangleItemDispatchDriver::GetEdges(double &x1, double &y1, double &x2, double &y2, double &x3, double &y3) CONST
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETEDGES));
	static BYTE  pParameters[] = VTS_PR8 VTS_PR8 VTS_PR8 VTS_PR8 VTS_PR8 VTS_PR8;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, &x1, &y1, &x2, &y2, &x3, &y3);
}


////////////////////////////////////////////////////////////////////////////
// CMimicsSwitchItemDispatchDriver properties

VOID CMimicsSwitchItemDispatchDriver::SetStyle(INT nStyle)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nStyle);
}

INT CMimicsSwitchItemDispatchDriver::GetStyle() CONST
{
	INT  nStyle;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nStyle);
	return nStyle;
}

VOID CMimicsSwitchItemDispatchDriver::SetColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_COLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsSwitchItemDispatchDriver::GetColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_COLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsSwitchItemDispatchDriver::SetFrameColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_FRAMECOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsSwitchItemDispatchDriver::GetFrameColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_FRAMECOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsSwitchItemDispatchDriver::SetInteriorFrameColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORFRAMECOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsSwitchItemDispatchDriver::GetInteriorFrameColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORFRAMECOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsSwitchItemDispatchDriver::SetCenterColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_CENTERCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsSwitchItemDispatchDriver::GetCenterColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_CENTERCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsSwitchItemDispatchDriver::SetInteriorCenterColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCENTERCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsSwitchItemDispatchDriver::GetInteriorCenterColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_INTERIORCENTERCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsSwitchItemDispatchDriver::SetBarColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BARCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsSwitchItemDispatchDriver::GetBarColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BARCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsSwitchItemDispatchDriver::SetStubsColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STUBSCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsSwitchItemDispatchDriver::GetStubsColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STUBSCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsSwitchItemDispatchDriver::SetThickness(INT nWidth)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_THICKNESS));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nWidth);
}

INT CMimicsSwitchItemDispatchDriver::GetThickness() CONST
{
	INT  nWidth;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_THICKNESS));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nWidth);
	return nWidth;
}

VOID CMimicsSwitchItemDispatchDriver::SetFrameThickness(INT nWidth)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_FRAMETHICKNESS));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nWidth);
}

INT CMimicsSwitchItemDispatchDriver::GetFrameThickness() CONST
{
	INT  nWidth;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_FRAMETHICKNESS));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nWidth);
	return nWidth;
}

VOID CMimicsSwitchItemDispatchDriver::SetCenterThickness(INT nWidth)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_CENTERTHICKNESS));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nWidth);
}

INT CMimicsSwitchItemDispatchDriver::GetCenterThickness() CONST
{
	INT  nWidth;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_CENTERTHICKNESS));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nWidth);
	return nWidth;
}

VOID CMimicsSwitchItemDispatchDriver::SetBarThickness(INT nWidth)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BARTHICKNESS));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nWidth);
}

INT CMimicsSwitchItemDispatchDriver::GetBarThickness() CONST
{
	INT  nWidth;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BARTHICKNESS));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nWidth);
	return nWidth;
}

VOID CMimicsSwitchItemDispatchDriver::SetStubsThickness(INT nWidth)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STUBSTHICKNESS));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nWidth);
}

INT CMimicsSwitchItemDispatchDriver::GetStubsThickness() CONST
{
	INT  nWidth;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STUBSTHICKNESS));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nWidth);
	return nWidth;
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsSwitchItemDispatchDriver operations

VOID CMimicsSwitchItemDispatchDriver::Open()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_OPEN));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

BOOL CMimicsSwitchItemDispatchDriver::IsOpen() CONST
{
	BOOL  bOpen;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISOPEN));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bOpen, (const BYTE *)NULL);
	return bOpen;
}

BOOL CMimicsSwitchItemDispatchDriver::IsClosed() CONST
{
	BOOL  bClosed;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISCLOSED));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bClosed, (const BYTE *)NULL);
	return bClosed;
}

VOID CMimicsSwitchItemDispatchDriver::Close()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_CLOSE));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsSwitchItemDispatchDriver::Pos1()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_POS1));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

BOOL CMimicsSwitchItemDispatchDriver::IsPos1() CONST
{
	INT  nPos;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISPOS1));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_I4, &nPos, (const BYTE *)NULL);
	return((nPos == 0) ? TRUE : FALSE);
}

VOID CMimicsSwitchItemDispatchDriver::Pos2()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_POS2));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

BOOL CMimicsSwitchItemDispatchDriver::IsPos2() CONST
{
	INT  nPos;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISPOS2));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_I4, &nPos, (const BYTE *)NULL);
	return((nPos == 1) ? TRUE : FALSE);
}

VOID CMimicsSwitchItemDispatchDriver::Pos3()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_POS3));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

BOOL CMimicsSwitchItemDispatchDriver::IsPos3() CONST
{
	INT  nPos;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISPOS3));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_I4, &nPos, (const BYTE *)NULL);
	return((nPos == 2) ? TRUE : FALSE);
}

VOID CMimicsSwitchItemDispatchDriver::Broken()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_BROKEN));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

BOOL CMimicsSwitchItemDispatchDriver::IsBroken() CONST
{
	INT  nPos;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISBROKEN));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_I4, &nPos, (const BYTE *)NULL);
	return((nPos == -1) ? TRUE : FALSE);
}


////////////////////////////////////////////////////////////////////////////
// CMimicsTextItemDispatchDriver properties

VOID CMimicsTextItemDispatchDriver::SetText(LPCTSTR pszText)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_TEXT));

	SetProperty(GetDispatchID(szDispatch), VT_BSTR, pszText);
}

CString CMimicsTextItemDispatchDriver::GetText() CONST
{
	CString  szText;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_TEXT));

	GetProperty(GetDispatchID(szDispatch), VT_BSTR, &szText);
	return szText;
}

VOID CMimicsTextItemDispatchDriver::SetMode(INT nMode)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_MODE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nMode);
}

INT CMimicsTextItemDispatchDriver::GetMode() CONST
{
	INT  nMode;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_MODE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nMode);
	return nMode;
}

VOID CMimicsTextItemDispatchDriver::SetColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_COLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsTextItemDispatchDriver::GetColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_COLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

VOID CMimicsTextItemDispatchDriver::SetBackgroundColor(COLORREF nColor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BACKGROUNDCOLOR));

	SetProperty(GetDispatchID(szDispatch), VT_COLOR, nColor);
}

COLORREF CMimicsTextItemDispatchDriver::GetBackgroundColor() CONST
{
	COLORREF  nColor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_BACKGROUNDCOLOR));

	GetProperty(GetDispatchID(szDispatch), VT_COLOR, &nColor);
	return nColor;
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsTextItemDispatchDriver operations

BOOL CMimicsTextItemDispatchDriver::SetFont(CONST LOGFONT *pFont)
{
	BOOL  bFont;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETFONT));
	static BYTE  pParameters[] = VTS_PVARIANT;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bFont, pParameters, pFont);
	return bFont;
}

BOOL CMimicsTextItemDispatchDriver::GetFont(LOGFONT *pFont) CONST
{
	BOOL  bFont;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETFONT));
	static BYTE  pParameters[] = VTS_PVARIANT;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bFont, pParameters, pFont);
	return bFont;
}

VOID CMimicsTextItemDispatchDriver::AlignLeft()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ALIGNLEFT));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsTextItemDispatchDriver::AlignCenter()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ALIGNCENTER));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsTextItemDispatchDriver::AlignRight()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ALIGNRIGHT));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsTextItemDispatchDriver::AlignVertical(BOOL bEnable)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ALIGNVERTICAL));
	static BYTE  pParameters[] = VTS_BOOL;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, bEnable);
}

BOOL CMimicsTextItemDispatchDriver::IsLeftAligned() CONST
{
	BOOL  bAligned;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISLEFTALIGNED));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bAligned, (const BYTE *)NULL);
	return bAligned;
}

BOOL CMimicsTextItemDispatchDriver::IsCenterAligned() CONST
{
	BOOL  bAligned;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISCENTERALIGNED));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bAligned, (const BYTE *)NULL);
	return bAligned;
}

BOOL CMimicsTextItemDispatchDriver::IsRightAligned() CONST
{
	BOOL  bAligned;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISRIGHTALIGNED));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bAligned, (const BYTE *)NULL);
	return bAligned;
}

BOOL CMimicsTextItemDispatchDriver::IsVerticalAligned() CONST
{
	BOOL  bAligned;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISVERTICALALIGNED));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bAligned, (const BYTE *)NULL);
	return bAligned;
}

VOID CMimicsTextItemDispatchDriver::LeftToRightReading()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_LEFTTORIGHTREADING));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

VOID CMimicsTextItemDispatchDriver::TopToBottomReading()
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_TOPTOBOTTOMREADING));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, (const BYTE *)NULL);
}

BOOL CMimicsTextItemDispatchDriver::IsLeftToRightReading() CONST
{
	BOOL  bReading;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISLEFTTORIGHTREADING));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bReading, (const BYTE *)NULL);
	return bReading;
}

BOOL CMimicsTextItemDispatchDriver::IsTopToBottomReading() CONST
{
	BOOL  bReading;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISTOPTOBOTTOMREADING));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bReading, (const BYTE *)NULL);
	return bReading;
}

VOID CMimicsTextItemDispatchDriver::SetTabChars(INT nChars)
{
	static BYTE  pParameters[] = VTS_I4;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETTABCHARS));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, nChars);
}

INT CMimicsTextItemDispatchDriver::GetTabChars() CONST
{
	INT  nChars;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETTABCHARS));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_I4, &nChars, (const BYTE *)NULL);
	return nChars;
}

VOID CMimicsTextItemDispatchDriver::WrapWords(BOOL bEnable)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_WRAPWORDS));
	static BYTE  pParameters[] = VTS_BOOL;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, bEnable);
}

BOOL CMimicsTextItemDispatchDriver::IsWrappingWords() CONST
{
	BOOL  bEnable;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISWRAPPINGWORDS));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bEnable, (const BYTE *)NULL);
	return bEnable;
}

VOID CMimicsTextItemDispatchDriver::SingleLine(BOOL bEnable)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SINGLELINE));
	static BYTE  pParameters[] = VTS_BOOL;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, bEnable);
}

BOOL CMimicsTextItemDispatchDriver::IsSingleLine() CONST
{
	BOOL  bEnable;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_ISSINGLELINE));

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_BOOL, &bEnable, (const BYTE *)NULL);
	return bEnable;
}


////////////////////////////////////////////////////////////////////////////
// CMimicsImageItemDispatchDriver properties

VOID CMimicsImageItemDispatchDriver::SetStyle(INT nStyle)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	SetProperty(GetDispatchID(szDispatch), VT_I4, nStyle);
}

INT CMimicsImageItemDispatchDriver::GetStyle() CONST
{
	INT  nStyle;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_STYLE));

	GetProperty(GetDispatchID(szDispatch), VT_I4, &nStyle);
	return nStyle;
}

VOID CMimicsImageItemDispatchDriver::SetFileName(LPCTSTR pszFileName)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_FILENAME));

	SetProperty(GetDispatchID(szDispatch), VT_BSTR, pszFileName);
}

CString CMimicsImageItemDispatchDriver::GetFileName() CONST
{
	CString  szFileName;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_FILENAME));

	GetProperty(GetDispatchID(szDispatch), VT_BSTR, &szFileName);
	return szFileName;
}

VOID CMimicsImageItemDispatchDriver::SetImageTransparency(BYTE nFactor)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_IMAGETRANSPARENCY));

	SetProperty(GetDispatchID(szDispatch), VT_UI1, nFactor);
}

BYTE CMimicsImageItemDispatchDriver::GetImageTransparency() CONST
{
	BYTE  nFactor;
	_bstr_t  szDispatch(STRING(IDS_MIMICSPROPERTY_IMAGETRANSPARENCY));

	GetProperty(GetDispatchID(szDispatch), VT_UI1, &nFactor);
	return nFactor;
}

/////////////////////////////////////////////////////////////////////////////
// CMimicsImageItemDispatchDriver operations

VOID CMimicsImageItemDispatchDriver::SetImageOrigin(CONST POINT &pt)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETIMAGEORIGIN));
	static BYTE  pParameters[] = VTS_XPOS_PIXELS VTS_YPOS_PIXELS;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, pt.x, pt.y);
}

CPoint CMimicsImageItemDispatchDriver::GetImageOrigin() CONST
{
	OLE_XPOS_PIXELS  nXPos;
	OLE_YPOS_PIXELS  nYPos;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETIMAGEORIGIN));
	static BYTE  pParameters[] = VTS_PXPOS_PIXELS VTS_PYPOS_PIXELS;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, &nXPos, &nYPos);
	return CPoint(nXPos, nYPos);
}

VOID CMimicsImageItemDispatchDriver::SetImageSize(CONST SIZE &size)
{
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_SETIMAGESIZE));
	static BYTE  pParameters[] = VTS_XSIZE_PIXELS VTS_YSIZE_PIXELS;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, size.cx, size.cy);
}

CSize CMimicsImageItemDispatchDriver::GetImageSize() CONST
{
	OLE_XSIZE_PIXELS  cx;
	OLE_YSIZE_PIXELS  cy;
	_bstr_t  szDispatch(STRING(IDS_MIMICSMETHOD_GETIMAGESIZE));
	static BYTE  pParameters[] = VTS_PXSIZE_PIXELS VTS_PYSIZE_PIXELS;

	GetDispatchDriver()->InvokeHelper(GetDispatchID(szDispatch), DISPATCH_METHOD, VT_EMPTY, (void *)NULL, pParameters, &cx, &cy);
	return CSize(cx, cy);
}


////////////////////////////////////////////////////////////////////////////
// CMimicsGroupItemDispatchDriver properties

/////////////////////////////////////////////////////////////////////////////
// CMimicsGroupItemDispatchDriver operations


/////////////////////////////////////////////////////////////////////////////
// CMimicsItem

IMPLEMENT_DYNCREATE(CMimicsItem, CMimicsClientItem)

CMimicsItem::CMimicsItem(CMMDDocument *pContainerDoc) : CMimicsClientItem(pContainerDoc)
{
	m_szName.Empty();
	m_rPosition[0].SetRectEmpty();
	m_rPosition[1].SetRectEmpty();
	m_rPosition[2].SetRectEmpty();
	m_ptCenter[0].x = m_ptCenter[1].x = 0;
	m_ptCenter[0].y = m_ptCenter[1].y = 0;
	m_xForm[0].eM11 = m_xForm[1].eM11 = 1.0;
	m_xForm[0].eM12 = m_xForm[1].eM12 = 0.0;
	m_xForm[0].eM21 = m_xForm[1].eM21 = 0.0;
	m_xForm[0].eM22 = m_xForm[1].eM22 = 1.0;
	m_xForm[0].eDx = m_xForm[1].eDx = 0.0;
	m_xForm[0].eDy = m_xForm[1].eDy = 0.0;
	m_pContainerItem = (CMimicsItem *)NULL;
	m_pImageView = (CView *)NULL;
	m_bVisible = TRUE;
	m_bLocked = FALSE;
}

CMimicsItem::~CMimicsItem()
{
	Release();
}

CMimicsItem *CMimicsItem::Create(CMimicsItem *pItem, CView *pView, CMMDDocument *pDocument)
{
	CMimicsItem  *pMimicsItem;

	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsLineItem)))
	{
		if ((pMimicsItem = new CMimicsLineItem(pDocument)))
		{
			if (pMimicsItem->Copy(pItem) && pMimicsItem->CreateNewItem(CLSID_CMimicsLineCtrl, pView)) return pMimicsItem;
			delete pMimicsItem;
		}
	}
	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsRectangleItem)))
	{
		if ((pMimicsItem = new CMimicsRectangleItem(pDocument)))
		{
			if (pMimicsItem->Copy(pItem) && pMimicsItem->CreateNewItem(CLSID_CMimicsRectangleCtrl, pView)) return pMimicsItem;
			delete pMimicsItem;
		}
	}
	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsEllipseItem)))
	{
		if ((pMimicsItem = new CMimicsEllipseItem(pDocument)))
		{
			if (pMimicsItem->Copy(pItem) && pMimicsItem->CreateNewItem(CLSID_CMimicsEllipseCtrl, pView)) return pMimicsItem;
			delete pMimicsItem;
		}
	}
	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsArcItem)))
	{
		if ((pMimicsItem = new CMimicsArcItem(pDocument)))
		{
			if (pMimicsItem->Copy(pItem) && pMimicsItem->CreateNewItem(CLSID_CMimicsArcCtrl, pView)) return pMimicsItem;
			delete pMimicsItem;
		}
	}
	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsTriangleItem)))
	{
		if ((pMimicsItem = new CMimicsTriangleItem(pDocument)))
		{
			if (pMimicsItem->Copy(pItem) && pMimicsItem->CreateNewItem(CLSID_CMimicsTriangleCtrl, pView)) return pMimicsItem;
			delete pMimicsItem;
		}
	}
	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsSwitchItem)))
	{
		if ((pMimicsItem = new CMimicsSwitchItem(pDocument)))
		{
			if (pMimicsItem->Copy(pItem) && pMimicsItem->CreateNewItem(CLSID_CMimicsSwitchCtrl, pView)) return pMimicsItem;
			delete pMimicsItem;
		}
	}
	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsTextItem)))
	{
		if ((pMimicsItem = new CMimicsTextItem(pDocument)))
		{
			if (pMimicsItem->Copy(pItem) && pMimicsItem->CreateNewItem(CLSID_CMimicsTextCtrl, pView)) return pMimicsItem;
			delete pMimicsItem;
		}
	}
	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsImageItem)))
	{
		if ((pMimicsItem = new CMimicsImageItem(pDocument)))
		{
			if (pMimicsItem->Copy(pItem) && pMimicsItem->CreateNewItem(CLSID_CMimicsImageCtrl, pView)) return pMimicsItem;
			delete pMimicsItem;
		}
	}
	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsGroup)))
	{
		if ((pMimicsItem = new CMimicsGroup(pDocument)))
		{
			if (pMimicsItem->Copy(pItem) && pMimicsItem->CreateNewItem(CLSID_CMimicsGroupCtrl, pView)) return pMimicsItem;
			delete pMimicsItem;
		}
	}
	return((CMimicsItem *)NULL);
}

BOOL CMimicsItem::CreateNewItem(REFCLSID clsid, CView *pView, OLERENDER render, CLIPFORMAT cfFormat, LPFORMATETC lpFormatEtc)
{
	Lock();
	if (CMimicsClientItem::CreateNewItem(clsid, render, cfFormat, lpFormatEtc))
	{
		SetItemClassID(clsid);
		SetItemName();
		SetItemType();
		SetItemSize();
		SetItemCenterPoint();
		SetItemToolTipText();
		SetItemImage(pView);
		SetItemVisibility();
		UpdateProperties();
		SaveItemDefaultState();
		Unlock();
		return TRUE;
	}
	Unlock();
	return FALSE;
}

CMimicsItem *CMimicsItem::AllocateFromItem(CMimicsItem *pItem)
{
	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsLineItem))) return new CMimicsLineItem;
	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsRectangleItem))) return new CMimicsRectangleItem;
	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsEllipseItem))) return new CMimicsEllipseItem;
	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsArcItem))) return new CMimicsArcItem;
	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsTriangleItem))) return new CMimicsTriangleItem;
	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsSwitchItem))) return new CMimicsSwitchItem;
	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsTextItem))) return new CMimicsTextItem;
	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsImageItem))) return new CMimicsImageItem;
	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsGroup))) return new CMimicsGroup;
	return((CMimicsItem *)NULL);
}
CMimicsItem *CMimicsItem::AllocateFromItem(CMMDLayoutItem *pItem)
{
	if (pItem->GetClassID() == CLSID_CMimicsLineCtrl) return new CMimicsLineItem;
	if (pItem->GetClassID() == CLSID_CMimicsRectangleCtrl) return new CMimicsRectangleItem;
	if (pItem->GetClassID() == CLSID_CMimicsEllipseCtrl) return new CMimicsEllipseItem;
	if (pItem->GetClassID() == CLSID_CMimicsArcCtrl) return new CMimicsArcItem;
	if (pItem->GetClassID() == CLSID_CMimicsTriangleCtrl) return new CMimicsTriangleItem;
	if (pItem->GetClassID() == CLSID_CMimicsSwitchCtrl) return new CMimicsSwitchItem;
	if (pItem->GetClassID() == CLSID_CMimicsTextCtrl) return new CMimicsTextItem;
	if (pItem->GetClassID() == CLSID_CMimicsImageCtrl) return new CMimicsImageItem;
	if (pItem->GetClassID() == CLSID_CMimicsGroupCtrl) return new CMimicsGroup;
	return((CMimicsItem *)NULL);
}

CMimicsItem *CMimicsItem::AllocateFromData(CONST CByteArray &nData)
{
	CMMDLayoutItem  cLayoutItem;

	if (cLayoutItem.Unmap(nData))
	{
		if (cLayoutItem.GetClassID() == CLSID_CMimicsLineCtrl) return new CMimicsLineItem;
		if (cLayoutItem.GetClassID() == CLSID_CMimicsRectangleCtrl) return new CMimicsRectangleItem;
		if (cLayoutItem.GetClassID() == CLSID_CMimicsEllipseCtrl) return new CMimicsEllipseItem;
		if (cLayoutItem.GetClassID() == CLSID_CMimicsArcCtrl) return new CMimicsArcItem;
		if (cLayoutItem.GetClassID() == CLSID_CMimicsTriangleCtrl) return new CMimicsTriangleItem;
		if (cLayoutItem.GetClassID() == CLSID_CMimicsSwitchCtrl) return new CMimicsSwitchItem;
		if (cLayoutItem.GetClassID() == CLSID_CMimicsTextCtrl) return new CMimicsTextItem;
		if (cLayoutItem.GetClassID() == CLSID_CMimicsImageCtrl) return new CMimicsImageItem;
		if (cLayoutItem.GetClassID() == CLSID_CMimicsGroupCtrl) return new CMimicsGroup;
	}
	return((CMimicsItem *)NULL);
}

VOID CMimicsItem::SetItemName(LPCTSTR pszName)
{
	CMimicsItemDispatchDriver  cMimicsItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		if (!AfxIsValidString(pszName))
		{
			cMimicsItem.SetName(m_szName);
			return;
		}
	}
	m_szName = pszName;
}

CString CMimicsItem::GetItemName() CONST
{
	CString  szName;
	CMimicsItemDispatchDriver  cMimicsItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		szName = cMimicsItem.GetName();
		return szName;
	}
	return m_szName;
}

VOID CMimicsItem::SetItemClassID(CLSID clsid)
{
	m_clsid = clsid;
}

CLSID CMimicsItem::GetItemClassID() CONST
{
	return m_clsid;
}

VOID CMimicsItem::SetItemType(LPCTSTR pszType)
{
	CMimicsItemDispatchDriver  cMimicsItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsItem.SetType((m_szType = (!AfxIsValidString(pszType)) ? cMimicsItem.GetType() : pszType));
		return;
	}
	m_szType = pszType;
}

CString CMimicsItem::GetItemType() CONST
{
	CString  szType;
	CMimicsItemDispatchDriver  cMimicsItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		szType = cMimicsItem.GetType();
		return szType;
	}
	return m_szType;
}

VOID CMimicsItem::SetItemLink(LPCTSTR pszName)
{
	m_szLink = pszName;
}

CString CMimicsItem::GetItemLink() CONST
{
	return m_szLink;
}

VOID CMimicsItem::SetItemSize(INT cx, INT cy)
{
	SIZE  sizeItem[2];
	CClientDC  cDC(NULL);

	if (GetOleObject() != (LPOLEOBJECT)NULL  &&  GetDocument())
	{
		for (sizeItem[0].cx = (!cx && !cy) ? abs(m_rPosition[0].Width()) : cx, sizeItem[0].cy = (!cx && !cy) ? abs(m_rPosition[0].Height()) : cy, GetCachedExtent(&sizeItem[1]), cDC.HIMETRICtoDP(&sizeItem[1]); (!cx && !cy) || sizeItem[0].cx != sizeItem[1].cx || sizeItem[0].cy != sizeItem[1].cy; )
		{
			cDC.DPtoHIMETRIC(&sizeItem[0]);
			SetExtent(sizeItem[0]);
			break;
		}
	}
}

CSize CMimicsItem::GetItemSize() CONST
{
	CMimicsItemDispatchDriver  cMimicsItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsItem.GetInitialSize() : CSize(0, 0));
}

VOID CMimicsItem::SetItemToolTipText(LPCTSTR pszText)
{
	CMimicsItemDispatchDriver  cMimicsItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		if (!AfxIsValidString(pszText))
		{
			cMimicsItem.SetToolTipText(m_szText);
			return;
		}
	}
	m_szText = pszText;
}

CString CMimicsItem::GetItemToolTipText() CONST
{
	CString  szText;
	CMimicsItemDispatchDriver  cMimicsItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		szText = cMimicsItem.GetToolTipText();
		return szText;
	}
	return m_szText;
}

VOID CMimicsItem::SetItemVisibility(UINT bVisible)
{
	CMimicsItemDispatchDriver  cMimicsItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		if (bVisible == (UINT)-1 && m_bVisible)
		{
			cMimicsItem.Show();
			return;
		}
		if (bVisible == (UINT)-1)
		{
			cMimicsItem.Hide();
			return;
		}
		if (bVisible)
		{
			cMimicsItem.Show();
			return;
		}
		cMimicsItem.Hide();
		return;
	}
	m_bVisible = (bVisible == (UINT)-1) ? m_bVisible : bVisible;
}

BOOL CMimicsItem::GetItemVisibility() CONST
{
	CMimicsItemDispatchDriver  cMimicsItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsItem.IsVisible() : m_bVisible);
}

VOID CMimicsItem::SetItemProperties(CONST CByteArray &nInfo)
{
	m_nInfo.Copy(nInfo);
}

BOOL CMimicsItem::GetItemProperties(CByteArray &nInfo) CONST
{
	nInfo.Copy(m_nInfo);
	return((nInfo.GetSize() > 0) ? TRUE : FALSE);
}

VOID CMimicsItem::SetItemContainer(CMimicsItem *pItem)
{
	m_pContainerItem = pItem;
}

CMimicsItem *CMimicsItem::GetItemContainer() CONST
{
	return m_pContainerItem;
}

VOID CMimicsItem::AdjustItemContainer()
{
	CMimicsItem  *pItem;

	if ((pItem = GetItemContainer()))
	{
		pItem->AdjustItemPosition();
		return;
	}
}

VOID CMimicsItem::SetItemImage(CView *pView)
{
	m_pImageView = pView;
}

CView *CMimicsItem::GetItemImage() CONST
{
	return m_pImageView;
}

VOID CMimicsItem::SetItemPosition(CONST RECT &rect)
{
	CRect  rPosition;

	rPosition = rect;
	rPosition.OffsetRect(GetPosition().CenterPoint() - GetItemPosition().CenterPoint());
	SetPosition(rPosition);
}

CRect CMimicsItem::GetItemPosition() CONST
{
	return m_rPosition[0];
}

VOID CMimicsItem::NormalizeItemPosition(BOOL bUndo)
{
	if (!bUndo)
	{
		DoTransformation(m_ptCenter[0], m_xForm[0], m_rPosition[0]);
		return;
	}
	DoInverseTransformation(m_ptCenter[0], m_xForm[0], m_rPosition[0]);
}

VOID CMimicsItem::AdjustItemPosition()
{
	return;
}
VOID CMimicsItem::AdjustItemPosition(CONST RECT &rect)
{
	m_ptCenter[0].x += (rect.left + rect.right) / 2 - m_rPosition[0].CenterPoint().x;
	m_ptCenter[0].y += (rect.top + rect.bottom) / 2 - m_rPosition[0].CenterPoint().y;
	m_rPosition[0] = rect;
}

VOID CMimicsItem::SetItemDefaultPosition(CONST RECT &rect)
{
	m_rPosition[2] = rect;
}

CRect CMimicsItem::GetItemDefaultPosition() CONST
{
	return m_rPosition[2];
}

VOID CMimicsItem::AdjustItemDefaultPosition()
{
	CRect  rItem;
	CRect  rGroup;
	CMimicsGroup  *pGroup;

	if ((pGroup = (CMimicsGroup *)GetItemContainer()))
	{
		rItem = GetItemPosition();
		rGroup = pGroup->GetItemPosition();
		rItem.OffsetRect(-rGroup.TopLeft());
		rItem.left = (rGroup.Width() > 0) ? ((rItem.left*GetSystemMetrics(SM_CXSCREEN)) / rGroup.Width()) : 0;
		rItem.top = (rGroup.Height() > 0) ? ((rItem.top*GetSystemMetrics(SM_CYSCREEN)) / rGroup.Height()) : 0;
		rItem.right = (rGroup.Width() > 0) ? ((rItem.right*GetSystemMetrics(SM_CXSCREEN)) / rGroup.Width()) : 0;
		rItem.bottom = (rGroup.Height() > 0) ? ((rItem.bottom*GetSystemMetrics(SM_CYSCREEN)) / rGroup.Height()) : 0;
		SetItemDefaultPosition(rItem);
	}
}

VOID CMimicsItem::SetItemCenterPoint()
{
	SetItemCenterPoint(m_rPosition[0].CenterPoint());
}
VOID CMimicsItem::SetItemCenterPoint(CONST POINT &ptCenter)
{
	m_ptCenter[0] = ptCenter;
}

CPoint CMimicsItem::GetItemCenterPoint() CONST
{
	return m_ptCenter[0];
}

VOID CMimicsItem::AdjustItemCenterPoint()
{
	CRect  rPosition;
	CPoint  ptItem[2];

	rPosition = GetItemPosition();
	if (m_ptCenter[0] != rPosition.CenterPoint())
	{
		ptItem[0] = DoTransformation(rPosition.TopLeft());
		ptItem[1] = DoTransformation(rPosition.BottomRight());
		m_ptCenter[0].x = (ptItem[0].x + ptItem[1].x) / 2;
		m_ptCenter[0].y = (ptItem[0].y + ptItem[1].y) / 2;
		rPosition.OffsetRect(m_ptCenter[0] - rPosition.CenterPoint());
		m_rPosition[0] = rPosition;
	}
}

VOID CMimicsItem::SaveItemDefaultState()
{
	m_ptCenter[1] = m_ptCenter[0];
	m_rPosition[1] = m_rPosition[0];
	CopyMemory(&m_xForm[1], &m_xForm[0], sizeof(XFORM));
}

VOID CMimicsItem::LoadItemDefaultState()
{
	m_ptCenter[0] = m_ptCenter[1];
	m_rPosition[0] = m_rPosition[1];
	CopyMemory(&m_xForm[0], &m_xForm[1], sizeof(XFORM));
}

BOOL CMimicsItem::IsItemFlippedOrRotated() CONST
{
	return((m_xForm[0].eM11 != 1.0 || m_xForm[0].eM12 != 0.0 || m_xForm[0].eM21 != 0.0 || m_xForm[0].eM22 != 1.0) ? TRUE : FALSE);
}

BOOL CMimicsItem::IsItemSizeable() CONST
{
	return TRUE;
}

CRect CMimicsItem::CalcItemFrameExtent() CONST
{
	return DoTransformation(GetItemPosition());
}

BOOL CMimicsItem::CalcItemShape(CBitmap *pBitmap)
{
	CDC  cDC;
	CRect  rItem;
	CBitmap  *pOldBitmap;

	if (cDC.CreateCompatibleDC(NULL))
	{
		if (pBitmap->CreateBitmap(rItem.right + 1, (rItem = DoTransformation(GetItemPosition())).bottom + 1, 1, 1, (LPCVOID)NULL))
		{
			if ((pOldBitmap = cDC.SelectObject(pBitmap)))
			{
				Draw(&cDC, TRUE);
				cDC.SelectObject(pOldBitmap);
				cDC.DeleteDC();
				return TRUE;
			}
			pBitmap->DeleteObject();
		}
		cDC.DeleteDC();
	}
	return FALSE;
}

BOOL CMimicsItem::CheckPointOnItem(CONST POINT &ptPosition)
{
	return CheckPointInsideItem(ptPosition);
}

BOOL CMimicsItem::CheckPointInsideItem(CONST POINT &ptPosition)
{
	CDC  cDC;
	CRgn  rgItem;
	CRect  rItem;
	POINT  ptItem[4];
	CBitmap  cBitmap;
	CBitmap  *pOldBitmap;

	if (GetItemVisibility())
	{
		rItem = GetItemPosition();
		rItem.InflateRect((!rItem.Width()) ? (MIMICSITEM_THUMB_SIZE / 2) : 0, 0);
		rItem.InflateRect(0, (!rItem.Height()) ? (MIMICSITEM_THUMB_SIZE / 2) : 0);
		ptItem[0] = DoTransformation(CPoint(rItem.left, rItem.top));
		ptItem[1] = DoTransformation(CPoint(rItem.right, rItem.top));
		ptItem[2] = DoTransformation(CPoint(rItem.right, rItem.bottom));
		ptItem[3] = DoTransformation(CPoint(rItem.left, rItem.bottom));
		if (rgItem.CreatePolygonRgn(ptItem, sizeof(ptItem) / sizeof(POINT), WINDING))
		{
			if (!rgItem.PtInRegion(ptPosition))
			{
				rgItem.DeleteObject();
				return FALSE;
			}
			if (IsInPlaceActive())
			{
				rgItem.DeleteObject();
				return TRUE;
			}
			if (CalcItemShape(&cBitmap))
			{
				if (cDC.CreateCompatibleDC(NULL))
				{
					if ((pOldBitmap = cDC.SelectObject(&cBitmap)))
					{
						if (cDC.GetPixel(ptPosition))
						{
							cDC.SelectObject(pOldBitmap);
							cBitmap.DeleteObject();
							rgItem.DeleteObject();
							cDC.DeleteDC();
							return TRUE;
						}
						cDC.SelectObject(pOldBitmap);
					}
					cDC.DeleteDC();
				}
				cBitmap.DeleteObject();
			}
			rgItem.DeleteObject();
		}
	}
	return FALSE;
}

CRect CMimicsItem::DoTransformation(CONST RECT &rect) CONST
{
	CPoint  ptRect[4];

	ptRect[0] = DoTransformation(CPoint(rect.left, rect.top));
	ptRect[1] = DoTransformation(CPoint(rect.right, rect.top));
	ptRect[2] = DoTransformation(CPoint(rect.right, rect.bottom));
	ptRect[3] = DoTransformation(CPoint(rect.left, rect.bottom));
	return CRect(min(min(min(ptRect[0].x, ptRect[1].x), ptRect[2].x), ptRect[3].x), min(min(min(ptRect[0].y, ptRect[1].y), ptRect[2].y), ptRect[3].y), max(max(max(ptRect[0].x, ptRect[1].x), ptRect[2].x), ptRect[3].x), max(max(max(ptRect[0].y, ptRect[1].y), ptRect[2].y), ptRect[3].y));
}
CPoint CMimicsItem::DoTransformation(CONST POINT &point) CONST
{
	CPoint  pt;
	CMimicsItem  *pGroup;

	pt = CalcTransform((pt = point));
	for (pGroup = GetItemContainer(); pGroup; pGroup = pGroup->GetItemContainer())
	{
		pt = pGroup->CalcTransform(pt);
		continue;
	}
	return pt;
}
VOID CMimicsItem::DoTransformation(XFORM &xForm, CRect &rPosition) CONST
{
	CPoint  ptCenter;

	DoTransformation(this, ptCenter, xForm, rPosition);
}
VOID CMimicsItem::DoTransformation(CPoint &ptCenter, XFORM &xForm, CRect &rPosition) CONST
{
	DoTransformation(this, ptCenter, xForm, rPosition);
}
VOID CMimicsItem::DoTransformation(CONST CMimicsItem *pItem, CPoint &ptCenter, XFORM &xForm, CRect &rPosition) CONST
{
	CSize  ptOffset;
	CMimicsItem  *pGroup;

	rPosition = pItem->GetItemPosition();
	ptCenter = pItem->GetItemCenterPoint();
	CopyMemory(&xForm, &pItem->m_xForm[0], sizeof(XFORM));
	for (pGroup = pItem->GetItemContainer(); pGroup && pGroup != this; pGroup = pGroup->GetItemContainer())
	{
		rPosition.OffsetRect((ptOffset = pGroup->CalcTransform(rPosition.CenterPoint()) - rPosition.CenterPoint()));
		ptCenter.x += ptOffset.cx;
		ptCenter.y += ptOffset.cy;
		CombineTransform(&xForm, &xForm, &pGroup->m_xForm[0]);
	}
}

CPoint CMimicsItem::DoInverseTransformation(CONST POINT &point) CONST
{
	CPoint  pt;
	XFORM  xInvForm;
	CPtrArray  pGroups;
	CMimicsItem  *pGroup;

	for (pGroup = GetItemContainer(); pGroup; pGroup = pGroup->GetItemContainer())
	{
		pGroups.Add(pGroup);
		continue;
	}
	for (pt = point; pGroups.GetSize() > 0; )
	{
		if ((pGroup = (CMimicsItem *)pGroups.GetAt(pGroups.GetUpperBound())))
		{
			pGroup->BuildInverseTransform(xInvForm);
			pt = pGroup->CalcTransform(xInvForm, pt);
		}
		pGroups.RemoveAt(pGroups.GetUpperBound());
	}
	BuildInverseTransform(xInvForm);
	return CalcTransform(xInvForm, pt);
}
VOID CMimicsItem::DoInverseTransformation(XFORM &xForm, CRect &rPosition) CONST
{
	CPoint  ptCenter;

	DoInverseTransformation(this, ptCenter, xForm, rPosition);
}
VOID CMimicsItem::DoInverseTransformation(CPoint &ptCenter, XFORM &xForm, CRect &rPosition) CONST
{
	DoInverseTransformation(this, ptCenter, xForm, rPosition);
}
VOID CMimicsItem::DoInverseTransformation(CONST CMimicsItem *pItem, CPoint &ptCenter, XFORM &xForm, CRect &rPosition) CONST
{
	XFORM  xInvForm;
	CSize  ptOffset;
	CPtrArray  pGroups;
	CMimicsItem  *pGroup;

	rPosition = pItem->GetItemPosition();
	ptCenter = pItem->GetItemCenterPoint();
	CopyMemory(&xForm, &pItem->m_xForm[0], sizeof(XFORM));
	for (pGroup = GetItemContainer(); pGroup; pGroup = pGroup->GetItemContainer())
	{
		pGroups.Add(pGroup);
		continue;
	}
	while (pGroups.GetSize() > 0)
	{
		if ((pGroup = (CMimicsItem *)pGroups.GetAt(pGroups.GetUpperBound())) != this)
		{
			pGroup->BuildInverseTransform(xInvForm);
			CombineTransform(&xForm, &xForm, &xInvForm);
			rPosition.OffsetRect((ptOffset = pGroup->CalcTransform(xInvForm, rPosition.CenterPoint()) - rPosition.CenterPoint()));
			ptCenter.x += ptOffset.cx;
			ptCenter.y += ptOffset.cy;
			pGroups.RemoveAt(pGroups.GetUpperBound());
			continue;
		}
		break;
	}
}

CPoint CMimicsItem::CalcTransform(CONST POINT &point) CONST
{
	return CalcTransform(m_ptCenter[0], m_xForm[0], point);
}
CPoint CMimicsItem::CalcTransform(CONST XFORM &xForm, CONST POINT &point) CONST
{
	return CalcTransform(m_ptCenter[0], xForm, point);
}
CPoint CMimicsItem::CalcTransform(CONST POINT &ptCenter, CONST POINT &point) CONST
{
	return CalcTransform(ptCenter, m_xForm[0], point);
}
CPoint CMimicsItem::CalcTransform(CONST POINT &ptCenter, CONST XFORM &xForm, CONST POINT &point) CONST
{
	POINT  pt;
	XFORM  xTransform;
	CClientDC  cDC(NULL);

	SetGraphicsMode(cDC.GetSafeHdc(), GM_ADVANCED);
	xTransform.eM11 = xForm.eM11;
	xTransform.eM12 = xForm.eM12;
	xTransform.eM21 = xForm.eM21;
	xTransform.eM22 = xForm.eM22;
	xTransform.eDx = (float)ptCenter.x - (float)ptCenter.x*xForm.eM11 - (float)ptCenter.y*xForm.eM21;
	xTransform.eDy = (float)ptCenter.y - (float)ptCenter.x*xForm.eM12 - (float)ptCenter.y*xForm.eM22;
	SetWorldTransform(cDC.GetSafeHdc(), &xTransform);
	pt.x = point.x;
	pt.y = point.y;
	cDC.LPtoDP(&pt, 1);
	return pt;
}
CRect CMimicsItem::CalcTransform(CONST RECT &rect) CONST
{
	return CalcTransform(m_ptCenter[0], m_xForm[0], rect);
}
CRect CMimicsItem::CalcTransform(CONST XFORM &xForm, CONST RECT &rect) CONST
{
	return CalcTransform(m_ptCenter[0], xForm, rect);
}
CRect CMimicsItem::CalcTransform(CONST POINT &ptCenter, CONST RECT &rect) CONST
{
	return CalcTransform(ptCenter, m_xForm[0], rect);
}
CRect CMimicsItem::CalcTransform(CONST POINT &ptCenter, CONST XFORM &xForm, CONST RECT &rect) CONST
{
	CPoint  ptRect[4];

	ptRect[0] = CalcTransform(ptCenter, xForm, CPoint(rect.left, rect.top));
	ptRect[1] = CalcTransform(ptCenter, xForm, CPoint(rect.right, rect.top));
	ptRect[2] = CalcTransform(ptCenter, xForm, CPoint(rect.right, rect.bottom));
	ptRect[3] = CalcTransform(ptCenter, xForm, CPoint(rect.left, rect.bottom));
	return CRect(min(min(min(ptRect[0].x, ptRect[1].x), ptRect[2].x), ptRect[3].x), min(min(min(ptRect[0].y, ptRect[1].y), ptRect[2].y), ptRect[3].y), max(max(max(ptRect[0].x, ptRect[1].x), ptRect[2].x), ptRect[3].x), max(max(max(ptRect[0].y, ptRect[1].y), ptRect[2].y), ptRect[3].y));
}

VOID CMimicsItem::BuildInverseTransform(XFORM &xForm) CONST
{
	float  f;

	f = (m_xForm[0].eM11*m_xForm[0].eM22 - m_xForm[0].eM12*m_xForm[0].eM21 >= 0.0) ? (float) 1.0 : (float)-1.0;
	xForm.eM11 = f*m_xForm[0].eM22;
	xForm.eM22 = f*m_xForm[0].eM11;
	xForm.eM12 = -f*m_xForm[0].eM12;
	xForm.eM21 = -f*m_xForm[0].eM21;
	xForm.eDx = -m_xForm[0].eDx;
	xForm.eDy = -m_xForm[0].eDy;
}

BOOL CMimicsItem::Draw(CDC *pDC, BOOL bShape)
{
	CRect  rItem;
	XFORM  xForm;
	CPoint  ptCenter;
	CMimicsItemDispatchDriver  cMimicsItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		if (cMimicsItem.IsVisible() || bShape)
		{
			DoTransformation(ptCenter, xForm, rItem);
			xForm.eDx = (float)ptCenter.x;
			xForm.eDy = (float)ptCenter.y;
			cMimicsItem.Draw(pDC->GetSafeHdc(), rItem, &xForm, bShape);
			return TRUE;
		}
	}
	return FALSE;
}

VOID CMimicsItem::DrawItem()
{
	CMMDView  *pView;

	if ((pView = (!IsLocked()) ? (CMMDView *)GetItemImage() : (CMMDView *)NULL))
	{
		pView->DrawImage();
		return;
	}
}

VOID CMimicsItem::SetPosition(CONST RECT &rect)
{
	CRect  rItem;
	CRect  rPosition;
	CMimicsGroup  *pGroup;

	Lock();
	rItem = GetPosition();
	rPosition.SetRect(rect.left, rect.top, rect.right, rect.bottom);
	rPosition.OffsetRect(GetItemPosition().CenterPoint() - rItem.CenterPoint());
	if ((!IsItemSizeable() && (abs(rect.right - rect.left) != abs(rItem.Width()) || abs(rect.bottom - rect.top) != abs(rItem.Height()))) || rItem.EqualRect(&rect))
	{
		Unlock();
		return;
	}
	for (rItem.SetRectEmpty(); (pGroup = (CMimicsGroup *)GetItemContainer()); )
	{
		if (pGroup->Lock())
		{
			AdjustItemContainer();
			AdjustItemPosition(rPosition);
			AdjustItemContainer();
			SetItemSize(abs(rect.right - rect.left), abs(rect.bottom - rect.top));
			pGroup->Unlock();
		}
		Unlock();
		break;
	}
	if (!pGroup)
	{
		AdjustItemPosition(rPosition);
		SetItemSize(abs(rect.right - rect.left), abs(rect.bottom - rect.top));
		Unlock();
	}
	DrawItem();
}

CRect CMimicsItem::GetPosition() CONST
{
	CRect  rItem;
	XFORM  xForm;

	DoTransformation(xForm, rItem);
	return rItem;
}

VOID CMimicsItem::FlipHorizontal()
{
	CRect  rItem;
	XFORM  xForm;
	CMimicsGroup  *pGroup;

	Lock();
	AdjustItemContainer();
	AdjustItemCenterPoint();
	for (rItem.SetRectEmpty(); (pGroup = (CMimicsGroup *)GetItemContainer()); )
	{
		if (pGroup->Lock())
		{
			xForm.eM11 = -1.0;
			xForm.eM21 = 0.0;
			xForm.eM12 = 0.0;
			xForm.eM22 = 1.0;
			xForm.eDx = 0.0;
			xForm.eDy = 0.0;
			CombineTransform(&m_xForm[0], &m_xForm[0], &xForm);
			pGroup->Unlock();
		}
		Unlock();
		break;
	}
	if (!pGroup)
	{
		xForm.eM11 = -1.0;
		xForm.eM21 = 0.0;
		xForm.eM12 = 0.0;
		xForm.eM22 = 1.0;
		xForm.eDx = 0.0;
		xForm.eDy = 0.0;
		CombineTransform(&m_xForm[0], &m_xForm[0], &xForm);
		Unlock();
	}
	DrawItem();
}

VOID CMimicsItem::FlipVertical()
{
	CRect  rItem;
	XFORM  xForm;
	CMimicsGroup  *pGroup;

	Lock();
	AdjustItemContainer();
	AdjustItemCenterPoint();
	for (rItem.SetRectEmpty(); (pGroup = (CMimicsGroup *)GetItemContainer()); )
	{
		if (pGroup->Lock())
		{
			xForm.eM11 = 1.0;
			xForm.eM21 = 0.0;
			xForm.eM12 = 0.0;
			xForm.eM22 = -1.0;
			xForm.eDx = 0.0;
			xForm.eDy = 0.0;
			CombineTransform(&m_xForm[0], &m_xForm[0], &xForm);
			pGroup->Unlock();
		}
		Unlock();
		break;
	}
	if (!pGroup)
	{
		xForm.eM11 = 1.0;
		xForm.eM21 = 0.0;
		xForm.eM12 = 0.0;
		xForm.eM22 = -1.0;
		xForm.eDx = 0.0;
		xForm.eDy = 0.0;
		CombineTransform(&m_xForm[0], &m_xForm[0], &xForm);
		Unlock();
	}
	DrawItem();
}

VOID CMimicsItem::Rotate(double fAngle)
{
	CRect  rItem;
	XFORM  xForm;
	CMimicsGroup  *pGroup;

	Lock();
	AdjustItemContainer();
	AdjustItemCenterPoint();
	for (rItem.SetRectEmpty(); (pGroup = (CMimicsGroup *)GetItemContainer()); )
	{
		if (pGroup->Lock())
		{
			fAngle = (fmod(fAngle, 360.0)*2.0*M_PI) / 360.0;
			xForm.eM11 = (float)cos(fAngle);
			xForm.eM21 = (float)sin(fAngle);
			xForm.eM12 = (float)-sin(fAngle);
			xForm.eM22 = (float)cos(fAngle);
			xForm.eDx = xForm.eDy = 0.0;
			CombineTransform(&m_xForm[0], &m_xForm[0], &xForm);
			pGroup->Unlock();
		}
		Unlock();
		break;
	}
	if (!pGroup)
	{
		fAngle = (fmod(fAngle, 360.0)*2.0*M_PI) / 360.0;
		xForm.eM11 = (float)cos(fAngle);
		xForm.eM21 = (float)sin(fAngle);
		xForm.eM12 = (float)-sin(fAngle);
		xForm.eM22 = (float)cos(fAngle);
		xForm.eDx = xForm.eDy = 0.0;
		CombineTransform(&m_xForm[0], &m_xForm[0], &xForm);
		Unlock();
	}
	DrawItem();
}

VOID CMimicsItem::Reset()
{
	Lock();
	SetItemName();
	SetItemType();
	SetItemSize();
	SetItemToolTipText();
	SetItemVisibility();
	LoadItemDefaultState();
	UpdateProperties();
	Unlock();
}

BOOL CMimicsItem::Copy(CONST CMimicsItem *pItem)
{
	m_clsid = pItem->GetItemClassID();
	m_szName = pItem->GetItemName();
	m_szType = pItem->GetItemType();
	m_szLink = pItem->GetItemLink();
	m_szText = pItem->GetItemToolTipText();
	m_bVisible = pItem->GetItemVisibility();
	m_rPosition[0] = pItem->m_rPosition[0];
	m_rPosition[1] = pItem->m_rPosition[1];
	m_rPosition[2] = pItem->m_rPosition[2];
	m_ptCenter[0] = pItem->m_ptCenter[0];
	m_ptCenter[1] = pItem->m_ptCenter[1];
	CopyMemory(&m_xForm[0], &pItem->m_xForm[0], sizeof(XFORM));
	CopyMemory(&m_xForm[1], &pItem->m_xForm[1], sizeof(XFORM));
	m_nInfo.Copy(pItem->m_nInfo);
	return TRUE;
}

BOOL CMimicsItem::Compare(CONST CMimicsItem *pItem) CONST
{
	return((pItem->GetItemClassID() == GetItemClassID() && pItem->GetItemName() == GetItemName() && pItem->GetItemType() == GetItemType() && pItem->GetItemLink() == GetItemLink() && pItem->GetItemToolTipText() == GetItemToolTipText() && pItem->GetItemVisibility() == GetItemVisibility() && pItem->m_rPosition[0] == m_rPosition[0] && pItem->m_rPosition[1] == m_rPosition[1] && pItem->m_rPosition[2] == m_rPosition[2] && pItem->m_ptCenter[0] == m_ptCenter[0] && pItem->m_ptCenter[1] == m_ptCenter[1] && !memcmp(&pItem->m_xForm[0], &m_xForm[0], sizeof(XFORM)) && !memcmp(&pItem->m_xForm[1], &m_xForm[1], sizeof(XFORM)) && pItem->m_nInfo.GetSize() == m_nInfo.GetSize() && !memcmp(pItem->m_nInfo.GetData(), m_nInfo.GetData(), m_nInfo.GetSize())) ? TRUE : FALSE);
}

BOOL CMimicsItem::Map(CMMDLayoutItem *pItem)
{
	if (MapProperties(m_nInfo))
	{
		pItem->SetClassID(GetItemClassID());
		pItem->SetName(GetItemName());
		pItem->SetType(GetItemType());
		pItem->SetLink(GetItemLink());
		pItem->SetPosition(GetItemPosition());
		pItem->SetToolTipText(GetItemToolTipText());
		pItem->SetVisible(GetItemVisibility());
		pItem->SetTransformation(m_xForm[0]);
		pItem->SetProperties(m_nInfo);
		return TRUE;
	}
	return FALSE;
}
BOOL CMimicsItem::Map(CByteArray &nData)
{
	CMMDLayoutItem  cLayoutItem;

	return((Map(&cLayoutItem) && cLayoutItem.Map(nData)) ? TRUE : FALSE);
}

BOOL CMimicsItem::Unmap(CONST CMMDLayoutItem *pItem)
{
	SetItemClassID(pItem->GetClassID());
	SetItemName(pItem->GetName());
	SetItemType(pItem->GetType());
	SetItemLink(pItem->GetLink());
	SetItemPosition(pItem->GetPosition());
	SetItemCenterPoint(pItem->GetPosition().CenterPoint());
	SetItemToolTipText(pItem->GetToolTipText());
	SetItemVisibility(pItem->IsVisible());
	pItem->GetTransformation(m_xForm[0]);
	pItem->GetProperties(m_nInfo);
	return UnmapProperties(m_nInfo);
}
BOOL CMimicsItem::Unmap(CONST CByteArray &nData)
{
	CMMDLayoutItem  cLayoutItem;

	return((cLayoutItem.Unmap(nData) && Unmap(&cLayoutItem)) ? TRUE : FALSE);
}

BOOL CMimicsItem::MapProperties(CByteArray &nInfo)
{
	return TRUE;
}

BOOL CMimicsItem::UnmapProperties(CONST CByteArray &nInfo)
{
	return TRUE;
}

VOID CMimicsItem::UpdateProperties()
{
	return;
}

BOOL CMimicsItem::Lock()
{
	return((InterlockedIncrement(&m_bLocked) > 0) ? TRUE : FALSE);
}

BOOL CMimicsItem::IsLocked() CONST
{
	return((m_bLocked > 0) ? TRUE : FALSE);
}

BOOL CMimicsItem::Unlock()
{
	if (InterlockedDecrement(&m_bLocked) < 0)
	{
		InterlockedIncrement(&m_bLocked);
		return FALSE;
	}
	return TRUE;
}

BEGIN_MESSAGE_MAP(CMimicsItem, CMimicsClientItem)
	//{{AFX_MSG_MAP(CMimicsItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMimicsItem commands

void CMimicsItem::OnChange(OLE_NOTIFICATION wNotification, DWORD dwParam)
{
	for (; wNotification == OLE_CHANGED; )
	{
		DrawItem();
		break;
	}
	CMimicsClientItem::OnChange(wNotification, dwParam);
}


/////////////////////////////////////////////////////////////////////////////
// CMimicsLineItem

IMPLEMENT_DYNCREATE(CMimicsLineItem, CMimicsItem)

CMimicsLineItem::CMimicsLineItem(CMMDDocument *pContainerDoc) : CMimicsItem(pContainerDoc)
{
	SetItemClassID(CLSID_CMimicsLineCtrl);
	SetStyle();
	SetColor();
	SetThickness();
	Cross();
	Arrow();
	DoubleArrow();
	SetCrossPt();
}

VOID CMimicsLineItem::SetStyle(INT nStyle)
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		if (nStyle == PS_SOLID) cMimicsLineItem.Solid();
		if (nStyle == PS_DASH) cMimicsLineItem.Dash();
		if (nStyle == PS_DOT) cMimicsLineItem.Dot();
		if (nStyle == PS_DASHDOT) cMimicsLineItem.DashDot();
		if (nStyle == PS_DASHDOTDOT) cMimicsLineItem.DashDotDot();
		return;
	}
	m_nStyle = nStyle;
}

INT CMimicsLineItem::GetStyle() CONST
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		if (cMimicsLineItem.IsSolid()) return PS_SOLID;
		if (cMimicsLineItem.IsDashed()) return PS_DASH;
		if (cMimicsLineItem.IsDotted()) return PS_DOT;
		if (cMimicsLineItem.IsDashDotted()) return PS_DASHDOT;
		if (cMimicsLineItem.IsDashDotDotted()) return PS_DASHDOTDOT;
	}
	return m_nStyle;
}

VOID CMimicsLineItem::Arrow(BOOL bEnable)
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsLineItem.Arrow(bEnable);
		return;
	}
	m_bArrow[0] = bEnable;
}

VOID CMimicsLineItem::DoubleArrow(BOOL bEnable)
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsLineItem.DoubleArrow(bEnable);
		return;
	}
	m_bArrow[1] = bEnable;
}

VOID CMimicsLineItem::Cross(BOOL bEnable)
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsLineItem.Cross(bEnable);
		return;
	}
	m_bCrossing = bEnable;
}

BOOL CMimicsLineItem::SetCrossPt(double fPt)
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	if (GetOleObject() == (LPOLEOBJECT)NULL)
	{
		m_fPtCross = fPt;
		return TRUE;
	}
	return cMimicsLineItem.SetCrossPt(fPt);
}

BOOL CMimicsLineItem::GetCrossPt(double *fPt) CONST
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	if (GetOleObject() == (LPOLEOBJECT)NULL)
	{
		CopyMemory(fPt, &m_fPtCross, sizeof(double));
		return IsCross();
	}
	return cMimicsLineItem.GetCrossPt(fPt);
}

BOOL CMimicsLineItem::IsArrow() CONST
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsLineItem.IsArrow() : m_bArrow[0]);
}

BOOL CMimicsLineItem::IsDoubleArrow() CONST
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsLineItem.IsDoubleArrow() : m_bArrow[1]);
}

BOOL CMimicsLineItem::IsCross() CONST
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsLineItem.IsCross() : m_bCrossing);
}

VOID CMimicsLineItem::SetColor(COLORREF nColor)
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsLineItem.SetColor(nColor);
		return;
	}
	m_nColor = nColor;
}

COLORREF CMimicsLineItem::GetColor() CONST
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsLineItem.GetColor() : m_nColor);
}

VOID CMimicsLineItem::SetThickness(INT nWidth)
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsLineItem.SetThickness(nWidth);
		return;
	}
	m_nWidth = nWidth;
}

INT CMimicsLineItem::GetThickness() CONST
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsLineItem.GetThickness() : m_nWidth);
}

VOID CMimicsLineItem::Solid()
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsLineItem.Solid();
		return;
	}
	m_nStyle = PS_SOLID;
}

VOID CMimicsLineItem::Dash()
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsLineItem.Dash();
		return;
	}
	m_nStyle = PS_DASH;
}

VOID CMimicsLineItem::Dot()
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsLineItem.Dot();
		return;
	}
	m_nStyle = PS_DOT;
}

VOID CMimicsLineItem::DashDot()
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsLineItem.DashDot();
		return;
	}
	m_nStyle = PS_DASHDOT;
}

VOID CMimicsLineItem::DashDotDot()
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsLineItem.DashDotDot();
		return;
	}
	m_nStyle = PS_DASHDOTDOT;
}

BOOL CMimicsLineItem::IsSolid() CONST
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsLineItem.IsSolid() : ((m_nStyle == PS_SOLID) ? TRUE : FALSE));
}

BOOL CMimicsLineItem::IsDashed() CONST
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsLineItem.IsDashed() : ((m_nStyle == PS_DASH) ? TRUE : FALSE));
}

BOOL CMimicsLineItem::IsDotted() CONST
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsLineItem.IsDotted() : ((m_nStyle == PS_DOT) ? TRUE : FALSE));
}

BOOL CMimicsLineItem::IsDashDotted() CONST
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsLineItem.IsDashDotted() : ((m_nStyle == PS_DASHDOT) ? TRUE : FALSE));
}

BOOL CMimicsLineItem::IsDashDotDotted() CONST
{
	CMimicsLineItemDispatchDriver  cMimicsLineItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsLineItem.IsDashDotDotted() : ((m_nStyle == PS_DASHDOTDOT) ? TRUE : FALSE));
}

INT CMimicsLineItem::CalcItemFrameOutlinePoints(CONST RECT &rect, LPPOINT pPoints, INT nPoints) CONST
{
	INT  dx[2];
	INT  dy[2];
	INT  nWidth;
	CPoint  pt[2];
	CPoint  ptFrame[4];

	if (nPoints > 0)
	{
		pt[0] = DoTransformation(CPoint(rect.left, rect.top));
		pt[1] = DoTransformation(CPoint(rect.right, rect.bottom));
		nWidth = max(GetThickness() / 2 + 1 + 1, MIMICSITEM_THUMB_SIZE / 2);
		if ((dx[0] = pt[1].x - pt[0].x) == 0)
		{
			ptFrame[0].x = pt[0].x - nWidth;
			ptFrame[1].x = pt[0].x + nWidth;
			ptFrame[2].x = pt[1].x + nWidth;
			ptFrame[3].x = pt[1].x - nWidth;
			ptFrame[0].y = pt[0].y;
			ptFrame[1].y = pt[0].y;
			ptFrame[2].y = pt[1].y;
			ptFrame[3].y = pt[1].y;
		}
		if ((dy[0] = pt[1].y - pt[0].y) == 0)
		{
			ptFrame[0].x = (dx[0]) ? pt[0].x : ptFrame[0].x;
			ptFrame[1].x = (dx[0]) ? pt[1].x : ptFrame[1].x;
			ptFrame[2].x = (dx[0]) ? pt[1].x : ptFrame[2].x;
			ptFrame[3].x = (dx[0]) ? pt[0].x : ptFrame[3].x;
			ptFrame[0].y = pt[0].y - nWidth;
			ptFrame[1].y = pt[1].y - nWidth;
			ptFrame[2].y = pt[1].y + nWidth;
			ptFrame[3].y = pt[0].y + nWidth;
		}
		if (dx[0] != 0 && dy[0] != 0)
		{
			dx[1] = (INT)((double)(nWidth + 1) / sqrt(1.0 + ((double)dx[0] * (double)dx[0]) / ((double)dy[0] * (double)dy[0])));
			dy[1] = (INT)((-(double)dx[0] / (double)dy[0] * (double)(nWidth + 1)) / sqrt(1.0 + ((double)dx[0] * (double)dx[0]) / ((double)dy[0] * (double)dy[0])));
			ptFrame[0].x = pt[0].x - dx[1];
			ptFrame[1].x = pt[1].x - dx[1];
			ptFrame[2].x = pt[1].x + dx[1];
			ptFrame[3].x = pt[0].x + dx[1];
			ptFrame[0].y = pt[0].y - dy[1];
			ptFrame[1].y = pt[1].y - dy[1];
			ptFrame[2].y = pt[1].y + dy[1];
			ptFrame[3].y = pt[0].y + dy[1];
		}
		if (nPoints > 0) pPoints[0] = ptFrame[0];
		if (nPoints > 1) pPoints[1] = ptFrame[1];
		if (nPoints > 2) pPoints[2] = ptFrame[2];
		if (nPoints > 3) pPoints[3] = ptFrame[3];
	}
	return((nPoints > 0) ? ((nPoints >= 4) ? min(nPoints, 4) : 0) : 4);
}

BOOL CMimicsLineItem::CheckPointInsideItem(CONST POINT &ptPosition)
{
	CRgn  rgItem;
	POINT  ptItem[4];

	if (GetItemVisibility())
	{
		if (CalcItemFrameOutlinePoints(GetItemPosition(), ptItem, sizeof(ptItem) / sizeof(POINT)) > 0)
		{
			if (rgItem.CreatePolygonRgn(ptItem, sizeof(ptItem) / sizeof(POINT), WINDING))
			{
				if (!rgItem.PtInRegion(ptPosition))
				{
					rgItem.DeleteObject();
					return FALSE;
				}
				rgItem.DeleteObject();
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CMimicsLineItem::Copy(CONST CMimicsItem *pItem)
{
	CMimicsLineItem  *pLineItem = (CMimicsLineItem *)pItem;

	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsLineItem)))
	{
		m_nStyle = pLineItem->GetStyle();
		m_nColor = pLineItem->GetColor();
		m_nWidth = pLineItem->GetThickness();
		m_bCrossing = pLineItem->IsCross();
		m_bArrow[0] = pLineItem->IsArrow();
		m_bArrow[1] = pLineItem->IsDoubleArrow();
		pLineItem->GetCrossPt(&m_fPtCross);
		return CMimicsItem::Copy(pItem);
	}
	return FALSE;
}

BOOL CMimicsLineItem::Compare(CONST CMimicsItem *pItem) CONST
{
	double  fPtCross[2];
	CMimicsLineItem  *pLineItem = (CMimicsLineItem *)pItem;

	return((pItem->IsKindOf(RUNTIME_CLASS(CMimicsLineItem))) ? ((pLineItem->GetStyle() == GetStyle() && pLineItem->GetColor() == GetColor() && pLineItem->GetThickness() == GetThickness() && pLineItem->IsCross() == IsCross() && pLineItem->IsArrow() == IsArrow() && pLineItem->IsDoubleArrow() == IsDoubleArrow() && pLineItem->GetCrossPt(&fPtCross[0]) == GetCrossPt(&fPtCross[1]) && fPtCross[0] == fPtCross[1]) ? CMimicsItem::Compare(pItem) : FALSE) : FALSE);
}

BOOL CMimicsLineItem::MapProperties(CByteArray &nInfo)
{
	DATA  sData;

	sData.nStyle = GetStyle();
	sData.nColor = GetColor();
	sData.nWidth = GetThickness();
	sData.bCrossing = IsCross();
	sData.bArrow[0] = IsArrow();
	sData.bArrow[1] = IsDoubleArrow();
	GetCrossPt(&sData.fPtCross);
	for (nInfo.SetSize(sizeof(DATA)); nInfo.GetSize() == sizeof(DATA); )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		return TRUE;
	}
	return FALSE;
}

BOOL CMimicsLineItem::UnmapProperties(CONST CByteArray &nInfo)
{
	DATA  sData;

	if (nInfo.GetSize() == sizeof(DATA))
	{
		CopyMemory(&sData, nInfo.GetData(), sizeof(DATA));
		m_nStyle = sData.nStyle;
		m_nWidth = sData.nWidth;
		m_nColor = sData.nColor;
		m_bCrossing = sData.bCrossing;
		m_bArrow[0] = sData.bArrow[0];
		m_bArrow[1] = sData.bArrow[1];
		m_fPtCross = sData.fPtCross;
		return TRUE;
	}
	return FALSE;
}

VOID CMimicsLineItem::UpdateProperties()
{
	Lock();
	SetStyle(m_nStyle);
	SetColor(m_nColor);
	SetThickness(m_nWidth);
	Cross(m_bCrossing);
	SetCrossPt(m_fPtCross);
	Arrow(m_bArrow[0]);
	DoubleArrow(m_bArrow[1]);
	Unlock();
}

BEGIN_MESSAGE_MAP(CMimicsLineItem, CMimicsItem)
	//{{AFX_MSG_MAP(CMimicsLineItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMimicsLineItem commands


/////////////////////////////////////////////////////////////////////////////
// CMimicsRectangleItem

IMPLEMENT_DYNCREATE(CMimicsRectangleItem, CMimicsItem)

CMimicsRectangleItem::CMimicsRectangleItem(CMMDDocument *pContainerDoc) : CMimicsItem(pContainerDoc)
{
	SetItemClassID(CLSID_CMimicsRectangleCtrl);
	SetStyle();
	SetBorderSize();
	SetBorderStyle();
	SetBorderColor();
	SetInteriorColor();
	SetInteriorHatch();
}

VOID CMimicsRectangleItem::SetStyle(INT nStyle)
{
	CMimicsRectangleItemDispatchDriver  cMimicsRectangleItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsRectangleItem.SetStyle(nStyle);
		return;
	}
	m_nStyle = nStyle;
}

INT CMimicsRectangleItem::GetStyle() CONST
{
	CMimicsRectangleItemDispatchDriver  cMimicsRectangleItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsRectangleItem.GetStyle() : m_nStyle);
}

VOID CMimicsRectangleItem::SetBorderSize(INT nSize)
{
	CMimicsRectangleItemDispatchDriver  cMimicsRectangleItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsRectangleItem.SetBorderSize(nSize);
		return;
	}
	m_nBorderSize = nSize;
}

INT CMimicsRectangleItem::GetBorderSize() CONST
{
	CMimicsRectangleItemDispatchDriver  cMimicsRectangleItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsRectangleItem.GetBorderSize() : m_nBorderSize);
}

VOID CMimicsRectangleItem::SetBorderStyle(INT nStyle)
{
	CMimicsRectangleItemDispatchDriver  cMimicsRectangleItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsRectangleItem.SetBorderStyle(nStyle);
		return;
	}
	m_nBorderStyle = nStyle;
}

INT CMimicsRectangleItem::GetBorderStyle() CONST
{
	CMimicsRectangleItemDispatchDriver  cMimicsRectangleItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsRectangleItem.GetBorderStyle() : m_nBorderStyle);
}

VOID CMimicsRectangleItem::SetBorderColor(COLORREF nColor)
{
	CMimicsRectangleItemDispatchDriver  cMimicsRectangleItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsRectangleItem.SetBorderColor(nColor);
		return;
	}
	m_nBorderColor = nColor;
}

COLORREF CMimicsRectangleItem::GetBorderColor() CONST
{
	CMimicsRectangleItemDispatchDriver  cMimicsRectangleItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsRectangleItem.GetBorderColor() : m_nBorderColor);
}

VOID CMimicsRectangleItem::SetInteriorColor(COLORREF nColor)
{
	CMimicsRectangleItemDispatchDriver  cMimicsRectangleItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsRectangleItem.SetInteriorColor(nColor);
		return;
	}
	m_nInteriorColor = nColor;
}

COLORREF CMimicsRectangleItem::GetInteriorColor() CONST
{
	CMimicsRectangleItemDispatchDriver  cMimicsRectangleItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsRectangleItem.GetInteriorColor() : m_nInteriorColor);
}

VOID CMimicsRectangleItem::SetInteriorHatch(INT nHatch, COLORREF nColor)
{
	CMimicsRectangleItemDispatchDriver  cMimicsRectangleItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsRectangleItem.SetInteriorHatch(nHatch, nColor);
		return;
	}
	m_nInteriorHatch = nHatch;
	m_nHatchColor = nColor;
}

BOOL CMimicsRectangleItem::GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST
{
	CMimicsRectangleItemDispatchDriver  cMimicsRectangleItem(GetDispatch());

	if (GetOleObject() == (LPOLEOBJECT)NULL)
	{
		nHatch = m_nInteriorHatch;
		nColor = m_nHatchColor;
		return((nHatch >= 0) ? TRUE : FALSE);
	}
	return cMimicsRectangleItem.GetInteriorHatch(nHatch, nColor);
}

BOOL CMimicsRectangleItem::Copy(CONST CMimicsItem *pItem)
{
	CMimicsRectangleItem  *pRectangleItem = (CMimicsRectangleItem *)pItem;

	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsRectangleItem)))
	{
		m_nStyle = pRectangleItem->GetStyle();
		m_nBorderSize = pRectangleItem->GetBorderSize();
		m_nBorderStyle = pRectangleItem->GetBorderStyle();
		m_nBorderColor = pRectangleItem->GetBorderColor();
		m_nInteriorColor = pRectangleItem->GetInteriorColor();
		pRectangleItem->GetInteriorHatch(m_nInteriorHatch, m_nHatchColor);
		return CMimicsItem::Copy(pItem);
	}
	return FALSE;
}

BOOL CMimicsRectangleItem::Compare(CONST CMimicsItem *pItem) CONST
{
	INT  nHatch[2];
	COLORREF  nHatchColor[2];
	CMimicsRectangleItem  *pRectangleItem = (CMimicsRectangleItem *)pItem;

	return((pItem->IsKindOf(RUNTIME_CLASS(CMimicsRectangleItem))) ? ((pRectangleItem->GetStyle() == GetStyle() && pRectangleItem->GetBorderSize() == GetBorderSize() && pRectangleItem->GetBorderStyle() == GetBorderStyle() && pRectangleItem->GetBorderColor() == GetBorderColor() && pRectangleItem->GetInteriorColor() == GetInteriorColor() && pRectangleItem->GetInteriorHatch(nHatch[0], nHatchColor[0]) == GetInteriorHatch(nHatch[1], nHatchColor[1]) && nHatch[0] == nHatch[1] && (nHatch[0] < 0 || nHatchColor[0] == nHatchColor[1])) ? CMimicsItem::Compare(pItem) : FALSE) : FALSE);
}

BOOL CMimicsRectangleItem::MapProperties(CByteArray &nInfo)
{
	DATA  sData;

	sData.nStyle = GetStyle();
	sData.nBorderSize = GetBorderSize();
	sData.nBorderStyle = GetBorderStyle();
	sData.nBorderColor = GetBorderColor();
	sData.nInteriorColor = GetInteriorColor();
	GetInteriorHatch(sData.nInteriorHatch, sData.nHatchColor);
	for (nInfo.SetSize(sizeof(DATA)); nInfo.GetSize() == sizeof(DATA); )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		return TRUE;
	}
	return FALSE;
}

BOOL CMimicsRectangleItem::UnmapProperties(CONST CByteArray &nInfo)
{
	DATA  sData;

	if (nInfo.GetSize() == sizeof(DATA))
	{
		CopyMemory(&sData, nInfo.GetData(), sizeof(DATA));
		m_nInteriorColor = sData.nInteriorColor;
		m_nInteriorHatch = sData.nInteriorHatch;
		m_nHatchColor = sData.nHatchColor;
		m_nBorderStyle = sData.nBorderStyle;
		m_nBorderColor = sData.nBorderColor;
		m_nBorderSize = sData.nBorderSize;
		m_nStyle = sData.nStyle;
		return TRUE;
	}
	return FALSE;
}

VOID CMimicsRectangleItem::UpdateProperties()
{
	Lock();
	SetStyle(m_nStyle);
	SetBorderSize(m_nBorderSize);
	SetBorderStyle(m_nBorderStyle);
	SetBorderColor(m_nBorderColor);
	SetInteriorColor(m_nInteriorColor);
	SetInteriorHatch(m_nInteriorHatch, m_nHatchColor);
	Unlock();
}

BEGIN_MESSAGE_MAP(CMimicsRectangleItem, CMimicsItem)
	//{{AFX_MSG_MAP(CMimicsRectangleItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMimicsRectangleItem commands


/////////////////////////////////////////////////////////////////////////////
// CMimicsEllipseItem

IMPLEMENT_DYNCREATE(CMimicsEllipseItem, CMimicsItem)

CMimicsEllipseItem::CMimicsEllipseItem(CMMDDocument *pContainerDoc) : CMimicsItem(pContainerDoc)
{
	SetItemClassID(CLSID_CMimicsEllipseCtrl);
	SetStyle();
	SetBorderSize();
	SetBorderStyle();
	SetBorderColor();
	SetInteriorColor();
	SetInteriorHatch();
}

VOID CMimicsEllipseItem::SetStyle(INT nStyle)
{
	CMimicsEllipseItemDispatchDriver  cMimicsEllipseItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsEllipseItem.SetStyle(nStyle);
		return;
	}
	m_nStyle = nStyle;
}

INT CMimicsEllipseItem::GetStyle() CONST
{
	CMimicsEllipseItemDispatchDriver  cMimicsEllipseItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsEllipseItem.GetStyle() : m_nStyle);
}

VOID CMimicsEllipseItem::SetBorderSize(INT nSize)
{
	CMimicsEllipseItemDispatchDriver  cMimicsEllipseItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsEllipseItem.SetBorderSize(nSize);
		return;
	}
	m_nBorderSize = nSize;
}

INT CMimicsEllipseItem::GetBorderSize() CONST
{
	CMimicsEllipseItemDispatchDriver  cMimicsEllipseItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsEllipseItem.GetBorderSize() : m_nBorderSize);
}

VOID CMimicsEllipseItem::SetBorderStyle(INT nStyle)
{
	CMimicsEllipseItemDispatchDriver  cMimicsEllipseItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsEllipseItem.SetBorderStyle(nStyle);
		return;
	}
	m_nBorderStyle = nStyle;
}

INT CMimicsEllipseItem::GetBorderStyle() CONST
{
	CMimicsEllipseItemDispatchDriver  cMimicsEllipseItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsEllipseItem.GetBorderStyle() : m_nBorderStyle);
}

VOID CMimicsEllipseItem::SetBorderColor(COLORREF nColor)
{
	CMimicsEllipseItemDispatchDriver  cMimicsEllipseItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsEllipseItem.SetBorderColor(nColor);
		return;
	}
	m_nBorderColor = nColor;
}

COLORREF CMimicsEllipseItem::GetBorderColor() CONST
{
	CMimicsEllipseItemDispatchDriver  cMimicsEllipseItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsEllipseItem.GetBorderColor() : m_nBorderColor);
}

VOID CMimicsEllipseItem::SetInteriorColor(COLORREF nColor)
{
	CMimicsEllipseItemDispatchDriver  cMimicsEllipseItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsEllipseItem.SetInteriorColor(nColor);
		return;
	}
	m_nInteriorColor = nColor;
}

COLORREF CMimicsEllipseItem::GetInteriorColor() CONST
{
	CMimicsEllipseItemDispatchDriver  cMimicsEllipseItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsEllipseItem.GetInteriorColor() : m_nInteriorColor);
}

VOID CMimicsEllipseItem::SetInteriorHatch(INT nHatch, COLORREF nColor)
{
	CMimicsEllipseItemDispatchDriver  cMimicsEllipseItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsEllipseItem.SetInteriorHatch(nHatch, nColor);
		return;
	}
	m_nInteriorHatch = nHatch;
	m_nHatchColor = nColor;
}

BOOL CMimicsEllipseItem::GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST
{
	CMimicsEllipseItemDispatchDriver  cMimicsEllipseItem(GetDispatch());

	if (GetOleObject() == (LPOLEOBJECT)NULL)
	{
		nHatch = m_nInteriorHatch;
		nColor = m_nHatchColor;
		return((nHatch >= 0) ? TRUE : FALSE);
	}
	return cMimicsEllipseItem.GetInteriorHatch(nHatch, nColor);
}

BOOL CMimicsEllipseItem::Copy(CONST CMimicsItem *pItem)
{
	CMimicsEllipseItem  *pEllipseItem = (CMimicsEllipseItem *)pItem;

	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsEllipseItem)))
	{
		m_nStyle = pEllipseItem->GetStyle();
		m_nBorderSize = pEllipseItem->GetBorderSize();
		m_nBorderStyle = pEllipseItem->GetBorderStyle();
		m_nBorderColor = pEllipseItem->GetBorderColor();
		m_nInteriorColor = pEllipseItem->GetInteriorColor();
		pEllipseItem->GetInteriorHatch(m_nInteriorHatch, m_nHatchColor);
		return CMimicsItem::Copy(pItem);
	}
	return FALSE;
}

BOOL CMimicsEllipseItem::Compare(CONST CMimicsItem *pItem) CONST
{
	INT  nHatch[2];
	COLORREF  nHatchColor[2];
	CMimicsEllipseItem  *pEllipseItem = (CMimicsEllipseItem *)pItem;

	return((pItem->IsKindOf(RUNTIME_CLASS(CMimicsEllipseItem))) ? ((pEllipseItem->GetStyle() == GetStyle() && pEllipseItem->GetBorderSize() == GetBorderSize() && pEllipseItem->GetBorderStyle() == GetBorderStyle() && pEllipseItem->GetBorderColor() == GetBorderColor() && pEllipseItem->GetInteriorColor() == GetInteriorColor() && pEllipseItem->GetInteriorHatch(nHatch[0], nHatchColor[0]) == GetInteriorHatch(nHatch[1], nHatchColor[1]) && nHatch[0] == nHatch[1] && (nHatch[0] < 0 || nHatchColor[0] == nHatchColor[1])) ? CMimicsItem::Compare(pItem) : FALSE) : FALSE);
}

BOOL CMimicsEllipseItem::MapProperties(CByteArray &nInfo)
{
	DATA  sData;

	sData.nStyle = GetStyle();
	sData.nBorderSize = GetBorderSize();
	sData.nBorderStyle = GetBorderStyle();
	sData.nBorderColor = GetBorderColor();
	sData.nInteriorColor = GetInteriorColor();
	GetInteriorHatch(sData.nInteriorHatch, sData.nHatchColor);
	for (nInfo.SetSize(sizeof(DATA)); nInfo.GetSize() == sizeof(DATA); )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		return TRUE;
	}
	return FALSE;
}

BOOL CMimicsEllipseItem::UnmapProperties(CONST CByteArray &nInfo)
{
	DATA  sData;

	if (nInfo.GetSize() == sizeof(DATA))
	{
		CopyMemory(&sData, nInfo.GetData(), sizeof(DATA));
		m_nInteriorColor = sData.nInteriorColor;
		m_nInteriorHatch = sData.nInteriorHatch;
		m_nHatchColor = sData.nHatchColor;
		m_nBorderStyle = sData.nBorderStyle;
		m_nBorderColor = sData.nBorderColor;
		m_nBorderSize = sData.nBorderSize;
		m_nStyle = sData.nStyle;
		return TRUE;
	}
	return FALSE;
}

VOID CMimicsEllipseItem::UpdateProperties()
{
	Lock();
	SetStyle(m_nStyle);
	SetBorderSize(m_nBorderSize);
	SetBorderStyle(m_nBorderStyle);
	SetBorderColor(m_nBorderColor);
	SetInteriorColor(m_nInteriorColor);
	SetInteriorHatch(m_nInteriorHatch, m_nHatchColor);
	Unlock();
}

BEGIN_MESSAGE_MAP(CMimicsEllipseItem, CMimicsItem)
	//{{AFX_MSG_MAP(CMimicsEllipseItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMimicsEllipseItem commands


/////////////////////////////////////////////////////////////////////////////
// CMimicsArcItem

IMPLEMENT_DYNCREATE(CMimicsArcItem, CMimicsItem)

CMimicsArcItem::CMimicsArcItem(CMMDDocument *pContainerDoc) : CMimicsItem(pContainerDoc)
{
	SetItemClassID(CLSID_CMimicsArcCtrl);
	SetStyle();
	SetBorderSize();
	SetBorderStyle();
	SetBorderColor();
	SetInteriorColor();
	SetInteriorHatch();
	SetRadials();
}

VOID CMimicsArcItem::SetStyle(INT nStyle)
{
	CMimicsArcItemDispatchDriver  cMimicsArcItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsArcItem.SetStyle(nStyle);
		return;
	}
	m_nStyle = nStyle;
}

INT CMimicsArcItem::GetStyle() CONST
{
	CMimicsArcItemDispatchDriver  cMimicsArcItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsArcItem.GetStyle() : m_nStyle);
}

VOID CMimicsArcItem::SetBorderSize(INT nSize)
{
	CMimicsArcItemDispatchDriver  cMimicsArcItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsArcItem.SetBorderSize(nSize);
		return;
	}
	m_nBorderSize = nSize;
}

INT CMimicsArcItem::GetBorderSize() CONST
{
	CMimicsArcItemDispatchDriver  cMimicsArcItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsArcItem.GetBorderSize() : m_nBorderSize);
}

VOID CMimicsArcItem::SetBorderStyle(INT nStyle)
{
	CMimicsArcItemDispatchDriver  cMimicsArcItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsArcItem.SetBorderStyle(nStyle);
		return;
	}
	m_nBorderStyle = nStyle;
}

INT CMimicsArcItem::GetBorderStyle() CONST
{
	CMimicsArcItemDispatchDriver  cMimicsArcItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsArcItem.GetBorderStyle() : m_nBorderStyle);
}

VOID CMimicsArcItem::SetBorderColor(COLORREF nColor)
{
	CMimicsArcItemDispatchDriver  cMimicsArcItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsArcItem.SetBorderColor(nColor);
		return;
	}
	m_nBorderColor = nColor;
}

COLORREF CMimicsArcItem::GetBorderColor() CONST
{
	CMimicsArcItemDispatchDriver  cMimicsArcItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsArcItem.GetBorderColor() : m_nBorderColor);
}

VOID CMimicsArcItem::SetInteriorColor(COLORREF nColor)
{
	CMimicsArcItemDispatchDriver  cMimicsArcItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsArcItem.SetInteriorColor(nColor);
		return;
	}
	m_nInteriorColor = nColor;
}

COLORREF CMimicsArcItem::GetInteriorColor() CONST
{
	CMimicsArcItemDispatchDriver  cMimicsArcItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsArcItem.GetInteriorColor() : m_nInteriorColor);
}

VOID CMimicsArcItem::SetInteriorHatch(INT nHatch, COLORREF nColor)
{
	CMimicsArcItemDispatchDriver  cMimicsArcItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsArcItem.SetInteriorHatch(nHatch, nColor);
		return;
	}
	m_nInteriorHatch = nHatch;
	m_nHatchColor = nColor;
}

BOOL CMimicsArcItem::GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST
{
	CMimicsArcItemDispatchDriver  cMimicsArcItem(GetDispatch());

	if (GetOleObject() == (LPOLEOBJECT)NULL)
	{
		nHatch = m_nInteriorHatch;
		nColor = m_nHatchColor;
		return((nHatch >= 0) ? TRUE : FALSE);
	}
	return cMimicsArcItem.GetInteriorHatch(nHatch, nColor);
}

VOID CMimicsArcItem::SetRadials(double fRadial1, double fRadial2)
{
	CMimicsArcItemDispatchDriver  cMimicsArcItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL) cMimicsArcItem.SetRadials(fRadial1, fRadial2);
	m_ptRadial[0] = fRadial1;
	m_ptRadial[1] = fRadial2;
}

VOID CMimicsArcItem::GetRadials(double &fRadial1, double &fRadial2) CONST
{
	CMimicsArcItemDispatchDriver  cMimicsArcItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsArcItem.GetRadials(fRadial1, fRadial2);
		return;
	}
	fRadial1 = m_ptRadial[0];
	fRadial2 = m_ptRadial[1];
}

BOOL CMimicsArcItem::Copy(CONST CMimicsItem *pItem)
{
	CMimicsArcItem  *pArcItem = (CMimicsArcItem *)pItem;

	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsArcItem)))
	{
		m_nStyle = pArcItem->GetStyle();
		m_nBorderSize = pArcItem->GetBorderSize();
		m_nBorderStyle = pArcItem->GetBorderStyle();
		m_nBorderColor = pArcItem->GetBorderColor();
		m_nInteriorColor = pArcItem->GetInteriorColor();
		pArcItem->GetInteriorHatch(m_nInteriorHatch, m_nHatchColor);
		m_ptRadial[0] = pArcItem->m_ptRadial[0];
		m_ptRadial[1] = pArcItem->m_ptRadial[1];
		return CMimicsItem::Copy(pItem);
	}
	return FALSE;
}

BOOL CMimicsArcItem::Compare(CONST CMimicsItem *pItem) CONST
{
	INT  nHatch[2];
	COLORREF  nHatchColor[2];
	CMimicsArcItem  *pArcItem = (CMimicsArcItem *)pItem;

	return((pItem->IsKindOf(RUNTIME_CLASS(CMimicsArcItem))) ? ((pArcItem->GetStyle() == GetStyle() && pArcItem->GetBorderSize() == GetBorderSize() && pArcItem->GetBorderStyle() == GetBorderStyle() && pArcItem->GetBorderColor() == GetBorderColor() && pArcItem->GetInteriorColor() == GetInteriorColor() && pArcItem->GetInteriorHatch(nHatch[0], nHatchColor[0]) == GetInteriorHatch(nHatch[1], nHatchColor[1]) && nHatch[0] == nHatch[1] && (nHatch[0] < 0 || nHatchColor[0] == nHatchColor[1]) && pArcItem->m_ptRadial[0] == m_ptRadial[0] && pArcItem->m_ptRadial[1] == m_ptRadial[1]) ? CMimicsItem::Compare(pItem) : FALSE) : FALSE);
}

BOOL CMimicsArcItem::MapProperties(CByteArray &nInfo)
{
	DATA  sData;

	sData.nStyle = GetStyle();
	sData.nBorderSize = GetBorderSize();
	sData.nBorderStyle = GetBorderStyle();
	sData.nBorderColor = GetBorderColor();
	sData.nInteriorColor = GetInteriorColor();
	GetInteriorHatch(sData.nInteriorHatch, sData.nHatchColor);
	GetRadials(sData.ptRadial[0], sData.ptRadial[1]);
	for (nInfo.SetSize(sizeof(DATA)); nInfo.GetSize() == sizeof(DATA); )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		return TRUE;
	}
	return FALSE;
}

BOOL CMimicsArcItem::UnmapProperties(CONST CByteArray &nInfo)
{
	DATA  sData;

	if (nInfo.GetSize() == sizeof(DATA))
	{
		CopyMemory(&sData, nInfo.GetData(), sizeof(DATA));
		m_nInteriorColor = sData.nInteriorColor;
		m_nInteriorHatch = sData.nInteriorHatch;
		m_nHatchColor = sData.nHatchColor;
		m_nBorderStyle = sData.nBorderStyle;
		m_nBorderColor = sData.nBorderColor;
		m_nBorderSize = sData.nBorderSize;
		m_ptRadial[0] = sData.ptRadial[0];
		m_ptRadial[1] = sData.ptRadial[1];
		m_nStyle = sData.nStyle;
		return TRUE;
	}
	return FALSE;
}

VOID CMimicsArcItem::UpdateProperties()
{
	Lock();
	SetStyle(m_nStyle);
	SetBorderSize(m_nBorderSize);
	SetBorderStyle(m_nBorderStyle);
	SetBorderColor(m_nBorderColor);
	SetInteriorColor(m_nInteriorColor);
	SetInteriorHatch(m_nInteriorHatch, m_nHatchColor);
	SetRadials(m_ptRadial[0], m_ptRadial[1]);
	Unlock();
}

BEGIN_MESSAGE_MAP(CMimicsArcItem, CMimicsItem)
	//{{AFX_MSG_MAP(CMimicsArcItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMimicsArcItem commands


/////////////////////////////////////////////////////////////////////////////
// CMimicsTriangleItem

IMPLEMENT_DYNCREATE(CMimicsTriangleItem, CMimicsItem)

CMimicsTriangleItem::CMimicsTriangleItem(CMMDDocument *pContainerDoc) : CMimicsItem(pContainerDoc)
{
	SetItemClassID(CLSID_CMimicsTriangleCtrl);
	SetStyle();
	SetBorderSize();
	SetBorderStyle();
	SetBorderColor();
	SetInteriorColor();
	SetInteriorHatch();
	SetEdges();
}

VOID CMimicsTriangleItem::SetStyle(INT nStyle)
{
	CMimicsTriangleItemDispatchDriver  cMimicsTriangleItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTriangleItem.SetStyle(nStyle);
		return;
	}
	m_nStyle = nStyle;
}

INT CMimicsTriangleItem::GetStyle() CONST
{
	CMimicsTriangleItemDispatchDriver  cMimicsTriangleItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsTriangleItem.GetStyle() : m_nStyle);
}

VOID CMimicsTriangleItem::SetBorderSize(INT nSize)
{
	CMimicsTriangleItemDispatchDriver  cMimicsTriangleItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTriangleItem.SetBorderSize(nSize);
		return;
	}
	m_nBorderSize = nSize;
}

INT CMimicsTriangleItem::GetBorderSize() CONST
{
	CMimicsTriangleItemDispatchDriver  cMimicsTriangleItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsTriangleItem.GetBorderSize() : m_nBorderSize);
}

VOID CMimicsTriangleItem::SetBorderStyle(INT nStyle)
{
	CMimicsTriangleItemDispatchDriver  cMimicsTriangleItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTriangleItem.SetBorderStyle(nStyle);
		return;
	}
	m_nBorderStyle = nStyle;
}

INT CMimicsTriangleItem::GetBorderStyle() CONST
{
	CMimicsTriangleItemDispatchDriver  cMimicsTriangleItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsTriangleItem.GetBorderStyle() : m_nBorderStyle);
}

VOID CMimicsTriangleItem::SetBorderColor(COLORREF nColor)
{
	CMimicsTriangleItemDispatchDriver  cMimicsTriangleItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTriangleItem.SetBorderColor(nColor);
		return;
	}
	m_nBorderColor = nColor;
}

COLORREF CMimicsTriangleItem::GetBorderColor() CONST
{
	CMimicsTriangleItemDispatchDriver  cMimicsTriangleItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsTriangleItem.GetBorderColor() : m_nBorderColor);
}

VOID CMimicsTriangleItem::SetInteriorColor(COLORREF nColor)
{
	CMimicsTriangleItemDispatchDriver  cMimicsTriangleItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTriangleItem.SetInteriorColor(nColor);
		return;
	}
	m_nInteriorColor = nColor;
}

COLORREF CMimicsTriangleItem::GetInteriorColor() CONST
{
	CMimicsTriangleItemDispatchDriver  cMimicsTriangleItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsTriangleItem.GetInteriorColor() : m_nInteriorColor);
}

VOID CMimicsTriangleItem::SetInteriorHatch(INT nHatch, COLORREF nColor)
{
	CMimicsTriangleItemDispatchDriver  cMimicsTriangleItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTriangleItem.SetInteriorHatch(nHatch, nColor);
		return;
	}
	m_nInteriorHatch = nHatch;
	m_nHatchColor = nColor;
}

BOOL CMimicsTriangleItem::GetInteriorHatch(INT &nHatch, COLORREF &nColor) CONST
{
	CMimicsTriangleItemDispatchDriver  cMimicsTriangleItem(GetDispatch());

	if (GetOleObject() == (LPOLEOBJECT)NULL)
	{
		nHatch = m_nInteriorHatch;
		nColor = m_nHatchColor;
		return((nHatch >= 0) ? TRUE : FALSE);
	}
	return cMimicsTriangleItem.GetInteriorHatch(nHatch, nColor);
}

VOID CMimicsTriangleItem::SetEdges(double x1, double y1, double x2, double y2, double x3, double y3)
{
	CMimicsTriangleItemDispatchDriver  cMimicsTriangleItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTriangleItem.SetEdges(x1, y1, x2, y2, x3, y3);
		return;
	}
	m_ptEdges[0][0] = x1;
	m_ptEdges[0][1] = y1;
	m_ptEdges[1][0] = x2;
	m_ptEdges[1][1] = y2;
	m_ptEdges[2][0] = x3;
	m_ptEdges[2][1] = y3;
}

VOID CMimicsTriangleItem::GetEdges(double &x1, double &y1, double &x2, double &y2, double &x3, double &y3) CONST
{
	CMimicsTriangleItemDispatchDriver  cMimicsTriangleItem(GetDispatch());

	if (GetOleObject() == (LPOLEOBJECT)NULL)
	{
		x1 = m_ptEdges[0][0];
		y1 = m_ptEdges[0][1];
		x2 = m_ptEdges[1][0];
		y2 = m_ptEdges[1][1];
		x3 = m_ptEdges[2][0];
		y3 = m_ptEdges[2][1];
		return;
	}
	cMimicsTriangleItem.GetEdges(x1, y1, x2, y2, x3, y3);
}

BOOL CMimicsTriangleItem::Copy(CONST CMimicsItem *pItem)
{
	CMimicsTriangleItem  *pTriangleItem = (CMimicsTriangleItem *)pItem;

	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsTriangleItem)))
	{
		m_nStyle = pTriangleItem->GetStyle();
		m_nBorderSize = pTriangleItem->GetBorderSize();
		m_nBorderStyle = pTriangleItem->GetBorderStyle();
		m_nBorderColor = pTriangleItem->GetBorderColor();
		m_nInteriorColor = pTriangleItem->GetInteriorColor();
		pTriangleItem->GetInteriorHatch(m_nInteriorHatch, m_nHatchColor);
		pTriangleItem->GetEdges(m_ptEdges[0][0], m_ptEdges[0][1], m_ptEdges[1][0], m_ptEdges[1][1], m_ptEdges[2][0], m_ptEdges[2][1]);
		return CMimicsItem::Copy(pItem);
	}
	return FALSE;
}

BOOL CMimicsTriangleItem::Compare(CONST CMimicsItem *pItem) CONST
{
	INT  nHatch[2];
	double  ptEdges[2][3][2];
	COLORREF  nHatchColor[2];
	CMimicsTriangleItem  *pTriangleItem = (CMimicsTriangleItem *)pItem;

	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsTriangleItem)))
	{
		GetEdges(ptEdges[0][0][0], ptEdges[0][0][1], ptEdges[0][1][0], ptEdges[0][1][1], ptEdges[0][2][0], ptEdges[0][2][1]);
		pTriangleItem->GetEdges(ptEdges[1][0][0], ptEdges[1][0][1], ptEdges[1][1][0], ptEdges[1][1][1], ptEdges[1][2][0], ptEdges[1][2][1]);
		return((pTriangleItem->GetStyle() == GetStyle() && pTriangleItem->GetBorderSize() == GetBorderSize() && pTriangleItem->GetBorderStyle() == GetBorderStyle() && pTriangleItem->GetBorderColor() == GetBorderColor() && pTriangleItem->GetInteriorColor() == GetInteriorColor() && pTriangleItem->GetInteriorHatch(nHatch[0], nHatchColor[0]) == GetInteriorHatch(nHatch[1], nHatchColor[1]) && nHatch[0] == nHatch[1] && (nHatch[0] < 0 || nHatchColor[0] == nHatchColor[1]) && ptEdges[0][0][0] == ptEdges[1][0][0] && ptEdges[0][0][1] == ptEdges[1][0][1] && ptEdges[0][1][0] == ptEdges[1][1][0] && ptEdges[0][1][1] == ptEdges[1][1][1] && ptEdges[0][2][0] == ptEdges[1][2][0] && ptEdges[0][2][1] == ptEdges[1][2][1]) ? CMimicsItem::Compare(pItem) : FALSE);
	}
	return FALSE;
}

BOOL CMimicsTriangleItem::MapProperties(CByteArray &nInfo)
{
	DATA  sData;
	double  ptEdges[3][2];

	sData.nStyle = GetStyle();
	sData.nBorderSize = GetBorderSize();
	sData.nBorderStyle = GetBorderStyle();
	sData.nBorderColor = GetBorderColor();
	sData.nInteriorColor = GetInteriorColor();
	GetInteriorHatch(sData.nInteriorHatch, sData.nHatchColor);
	GetEdges(ptEdges[0][0], ptEdges[0][1], ptEdges[1][0], ptEdges[1][1], ptEdges[2][0], ptEdges[2][1]);
	sData.ptEdges[0][0] = ptEdges[0][0];
	sData.ptEdges[0][1] = ptEdges[0][1];
	sData.ptEdges[1][0] = ptEdges[1][0];
	sData.ptEdges[1][1] = ptEdges[1][1];
	sData.ptEdges[2][0] = ptEdges[2][0];
	sData.ptEdges[2][1] = ptEdges[2][1];
	for (nInfo.SetSize(sizeof(DATA)); nInfo.GetSize() == sizeof(DATA); )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		return TRUE;
	}
	return FALSE;
}

BOOL CMimicsTriangleItem::UnmapProperties(CONST CByteArray &nInfo)
{
	DATA  sData;

	if (nInfo.GetSize() == sizeof(DATA))
	{
		CopyMemory(&sData, nInfo.GetData(), sizeof(DATA));
		m_ptEdges[0][0] = sData.ptEdges[0][0];
		m_ptEdges[0][1] = sData.ptEdges[0][1];
		m_ptEdges[1][0] = sData.ptEdges[1][0];
		m_ptEdges[1][1] = sData.ptEdges[1][1];
		m_ptEdges[2][0] = sData.ptEdges[2][0];
		m_ptEdges[2][1] = sData.ptEdges[2][1];
		m_nInteriorColor = sData.nInteriorColor;
		m_nInteriorHatch = sData.nInteriorHatch;
		m_nHatchColor = sData.nHatchColor;
		m_nBorderStyle = sData.nBorderStyle;
		m_nBorderColor = sData.nBorderColor;
		m_nBorderSize = sData.nBorderSize;
		m_nStyle = sData.nStyle;
		return TRUE;
	}
	return FALSE;
}

VOID CMimicsTriangleItem::UpdateProperties()
{
	Lock();
	SetStyle(m_nStyle);
	SetBorderSize(m_nBorderSize);
	SetBorderStyle(m_nBorderStyle);
	SetBorderColor(m_nBorderColor);
	SetInteriorColor(m_nInteriorColor);
	SetInteriorHatch(m_nInteriorHatch, m_nHatchColor);
	SetEdges(m_ptEdges[0][0], m_ptEdges[0][1], m_ptEdges[1][0], m_ptEdges[1][1], m_ptEdges[2][0], m_ptEdges[2][1]);
	Unlock();
}

BEGIN_MESSAGE_MAP(CMimicsTriangleItem, CMimicsItem)
	//{{AFX_MSG_MAP(CMimicsTriangleItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMimicsTriangleItem commands


/////////////////////////////////////////////////////////////////////////////
// CMimicsSwitchItem

IMPLEMENT_DYNCREATE(CMimicsSwitchItem, CMimicsItem)

CMimicsSwitchItem::CMimicsSwitchItem(CMMDDocument *pContainerDoc) : CMimicsItem(pContainerDoc)
{
	SetItemClassID(CLSID_CMimicsSwitchCtrl);
	SetStyle();
	SetColor();
	SetBarColor();
	SetStubsColor();
	SetFrameColor();
	SetCenterColor();
	SetInteriorFrameColor();
	SetInteriorCenterColor();
	SetThickness();
	SetBarThickness();
	SetStubsThickness();
	SetFrameThickness();
	SetCenterThickness();
}

VOID CMimicsSwitchItem::SetStyle(INT nStyle)
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.SetStyle(nStyle);
		return;
	}
	m_nStyle = nStyle;
}

INT CMimicsSwitchItem::GetStyle() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.GetStyle() : m_nStyle);
}

VOID CMimicsSwitchItem::SetColor(COLORREF nColor)
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.SetColor(nColor);
		return;
	}
	m_nColor = nColor;
}

COLORREF CMimicsSwitchItem::GetColor() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.GetColor() : m_nColor);
}

VOID CMimicsSwitchItem::SetFrameColor(COLORREF nColor)
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.SetFrameColor(nColor);
		return;
	}
	m_nFrameColor[0] = nColor;
}

COLORREF CMimicsSwitchItem::GetFrameColor() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.GetFrameColor() : m_nFrameColor[0]);
}

VOID CMimicsSwitchItem::SetInteriorFrameColor(COLORREF nColor)
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.SetInteriorFrameColor(nColor);
		return;
	}
	m_nFrameColor[1] = nColor;
}

COLORREF CMimicsSwitchItem::GetInteriorFrameColor() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.GetInteriorFrameColor() : m_nFrameColor[1]);
}

VOID CMimicsSwitchItem::SetCenterColor(COLORREF nColor)
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.SetCenterColor(nColor);
		return;
	}
	m_nCenterColor[0] = nColor;
}

COLORREF CMimicsSwitchItem::GetCenterColor() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.GetCenterColor() : m_nCenterColor[0]);
}

VOID CMimicsSwitchItem::SetInteriorCenterColor(COLORREF nColor)
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.SetInteriorCenterColor(nColor);
		return;
	}
	m_nCenterColor[1] = nColor;
}

COLORREF CMimicsSwitchItem::GetInteriorCenterColor() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.GetInteriorCenterColor() : m_nCenterColor[1]);
}

VOID CMimicsSwitchItem::SetBarColor(COLORREF nColor)
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.SetBarColor(nColor);
		return;
	}
	m_nBarColor = nColor;
}

COLORREF CMimicsSwitchItem::GetBarColor() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.GetBarColor() : m_nBarColor);
}

VOID CMimicsSwitchItem::SetStubsColor(COLORREF nColor)
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.SetStubsColor(nColor);
		return;
	}
	m_nStubsColor = nColor;
}

COLORREF CMimicsSwitchItem::GetStubsColor() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.GetStubsColor() : m_nStubsColor);
}

VOID CMimicsSwitchItem::SetThickness(INT nWidth)
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.SetThickness(nWidth);
		return;
	}
	m_nWidth = nWidth;
}

INT CMimicsSwitchItem::GetThickness() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.GetThickness() : m_nWidth);
}

VOID CMimicsSwitchItem::SetFrameThickness(INT nWidth)
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.SetFrameThickness(nWidth);
		return;
	}
	m_nFrameWidth = nWidth;
}

INT CMimicsSwitchItem::GetFrameThickness() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.GetFrameThickness() : m_nFrameWidth);
}

VOID CMimicsSwitchItem::SetCenterThickness(INT nWidth)
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.SetCenterThickness(nWidth);
		return;
	}
	m_nCenterWidth = nWidth;
}

INT CMimicsSwitchItem::GetCenterThickness() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.GetCenterThickness() : m_nCenterWidth);
}

VOID CMimicsSwitchItem::SetBarThickness(INT nWidth)
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.SetBarThickness(nWidth);
		return;
	}
	m_nBarWidth = nWidth;
}

INT CMimicsSwitchItem::GetBarThickness() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.GetBarThickness() : m_nBarWidth);
}

VOID CMimicsSwitchItem::SetStubsThickness(INT nWidth)
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.SetStubsThickness(nWidth);
		return;
	}
	m_nStubsWidth = nWidth;
}

INT CMimicsSwitchItem::GetStubsThickness() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.GetStubsThickness() : m_nStubsWidth);
}

VOID CMimicsSwitchItem::Open()
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.Open();
		return;
	}
}

BOOL CMimicsSwitchItem::IsOpen() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.IsOpen() : FALSE);
}

BOOL CMimicsSwitchItem::IsClosed() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.IsClosed() : FALSE);
}

VOID CMimicsSwitchItem::Close()
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.Close();
		return;
	}
}

VOID CMimicsSwitchItem::Pos1()
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.Pos1();
		return;
	}
}

BOOL CMimicsSwitchItem::IsPos1() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.IsPos1() : FALSE);
}

VOID CMimicsSwitchItem::Pos2()
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.Pos2();
		return;
	}
}

BOOL CMimicsSwitchItem::IsPos2() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.IsPos2() : FALSE);
}

VOID CMimicsSwitchItem::Pos3()
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.Pos3();
		return;
	}
}

BOOL CMimicsSwitchItem::IsPos3() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.IsPos3() : FALSE);
}

VOID CMimicsSwitchItem::Broken()
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsSwitchItem.Broken();
		return;
	}
}

BOOL CMimicsSwitchItem::IsBroken() CONST
{
	CMimicsSwitchItemDispatchDriver  cMimicsSwitchItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsSwitchItem.IsBroken() : FALSE);
}

BOOL CMimicsSwitchItem::Copy(CONST CMimicsItem *pItem)
{
	CMimicsSwitchItem  *pSwitchItem = (CMimicsSwitchItem *)pItem;

	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsSwitchItem)))
	{
		m_nStyle = pSwitchItem->GetStyle();
		m_nColor = pSwitchItem->GetColor();
		m_nBarColor = pSwitchItem->GetBarColor();
		m_nStubsColor = pSwitchItem->GetStubsColor();
		m_nFrameColor[0] = pSwitchItem->GetFrameColor();
		m_nCenterColor[0] = pSwitchItem->GetCenterColor();
		m_nFrameColor[1] = pSwitchItem->GetInteriorFrameColor();
		m_nCenterColor[1] = pSwitchItem->GetInteriorCenterColor();
		m_nWidth = pSwitchItem->GetThickness();
		m_nBarWidth = pSwitchItem->GetBarThickness();
		m_nStubsWidth = pSwitchItem->GetStubsThickness();
		m_nFrameWidth = pSwitchItem->GetFrameThickness();
		m_nCenterWidth = pSwitchItem->GetCenterThickness();
		return CMimicsItem::Copy(pItem);
	}
	return FALSE;
}

BOOL CMimicsSwitchItem::Compare(CONST CMimicsItem *pItem) CONST
{
	CMimicsSwitchItem  *pSwitchItem = (CMimicsSwitchItem *)pItem;

	return((pItem->IsKindOf(RUNTIME_CLASS(CMimicsSwitchItem))) ? ((pSwitchItem->GetStyle() == GetStyle() && pSwitchItem->GetColor() == GetColor() && pSwitchItem->GetBarColor() == GetBarColor() && pSwitchItem->GetStubsColor() == GetStubsColor() && pSwitchItem->GetFrameColor() == GetFrameColor() && pSwitchItem->GetInteriorFrameColor() == GetInteriorFrameColor() && pSwitchItem->GetCenterColor() == GetCenterColor() && pSwitchItem->GetInteriorCenterColor() == GetInteriorCenterColor() && pSwitchItem->GetThickness() == GetThickness() && pSwitchItem->GetBarThickness() == GetBarThickness() && pSwitchItem->GetStubsThickness() == GetStubsThickness() && pSwitchItem->GetFrameThickness() == GetFrameThickness() && pSwitchItem->GetCenterThickness() == GetCenterThickness()) ? CMimicsItem::Compare(pItem) : FALSE) : FALSE);
}

BOOL CMimicsSwitchItem::MapProperties(CByteArray &nInfo)
{
	DATA  sData;

	sData.nStyle = GetStyle();
	sData.nColor = GetColor();
	sData.nWidth = GetThickness();
	sData.nBarColor = GetBarColor();
	sData.nBarWidth = GetBarThickness();
	sData.nStubsColor = GetStubsColor();
	sData.nStubsWidth = GetStubsThickness();
	sData.nFrameColor[0] = GetFrameColor();
	sData.nFrameColor[1] = GetInteriorFrameColor();
	sData.nFrameWidth = GetFrameThickness();
	sData.nCenterColor[0] = GetCenterColor();
	sData.nCenterColor[1] = GetInteriorCenterColor();
	sData.nCenterWidth = GetCenterThickness();
	for (nInfo.SetSize(sizeof(DATA)); nInfo.GetSize() == sizeof(DATA); )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		return TRUE;
	}
	return FALSE;
}

BOOL CMimicsSwitchItem::UnmapProperties(CONST CByteArray &nInfo)
{
	DATA  sData;

	if (nInfo.GetSize() == sizeof(DATA))
	{
		CopyMemory(&sData, nInfo.GetData(), sizeof(DATA));
		m_nCenterColor[0] = sData.nCenterColor[0];
		m_nCenterColor[1] = sData.nCenterColor[1];
		m_nCenterWidth = sData.nCenterWidth;
		m_nFrameColor[0] = sData.nFrameColor[0];
		m_nFrameColor[1] = sData.nFrameColor[1];
		m_nFrameWidth = sData.nFrameWidth;
		m_nStubsColor = sData.nStubsColor;
		m_nStubsWidth = sData.nStubsWidth;
		m_nBarColor = sData.nBarColor;
		m_nBarWidth = sData.nBarWidth;
		m_nColor = sData.nColor;
		m_nWidth = sData.nWidth;
		m_nStyle = sData.nStyle;
		return TRUE;
	}
	return FALSE;
}

VOID CMimicsSwitchItem::UpdateProperties()
{
	Lock();
	SetStyle(m_nStyle);
	SetColor(m_nColor);
	SetBarColor(m_nBarColor);
	SetStubsColor(m_nStubsColor);
	SetFrameColor(m_nFrameColor[0]);
	SetCenterColor(m_nCenterColor[0]);
	SetInteriorFrameColor(m_nFrameColor[1]);
	SetInteriorCenterColor(m_nCenterColor[1]);
	SetThickness(m_nWidth);
	SetBarThickness(m_nBarWidth);
	SetStubsThickness(m_nStubsWidth);
	SetFrameThickness(m_nFrameWidth);
	SetCenterThickness(m_nCenterWidth);
	Unlock();
}

BEGIN_MESSAGE_MAP(CMimicsSwitchItem, CMimicsItem)
	//{{AFX_MSG_MAP(CMimicsSwitchItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMimicsSwitchItem commands


/////////////////////////////////////////////////////////////////////////////
// CMimicsTextItem

IMPLEMENT_DYNCREATE(CMimicsTextItem, CMimicsItem)

CMimicsTextItem::CMimicsTextItem(CMMDDocument *pContainerDoc) : CMimicsItem(pContainerDoc)
{
	SetItemClassID(CLSID_CMimicsTextCtrl);
	SetMode();
	SetFont();
	SetColor();
	SetBackgroundColor();
	LeftToRightReading();
	AlignLeft();
	WrapWords();
	SetTabChars();
	SingleLine();
}

VOID CMimicsTextItem::SetText(LPCTSTR pszText)
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTextItem.SetText(pszText);
		return;
	}
	m_szText = pszText;
}

CString CMimicsTextItem::GetText() CONST
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsTextItem.GetText() : m_szText);
}

VOID CMimicsTextItem::SetMode(INT nMode)
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTextItem.SetMode(nMode);
		return;
	}
	m_nMode = nMode;
}

INT CMimicsTextItem::GetMode() CONST
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsTextItem.GetMode() : m_nMode);
}

VOID CMimicsTextItem::SetColor(COLORREF nColor)
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTextItem.SetColor(nColor);
		return;
	}
	m_nColor = nColor;
}

COLORREF CMimicsTextItem::GetColor() CONST
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsTextItem.GetColor() : m_nColor);
}

VOID CMimicsTextItem::SetBackgroundColor(COLORREF nColor)
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTextItem.SetBackgroundColor(nColor);
		return;
	}
	m_nBkColor = nColor;
}

COLORREF CMimicsTextItem::GetBackgroundColor() CONST
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsTextItem.GetBackgroundColor() : m_nBkColor);
}

BOOL CMimicsTextItem::SetFont(CONST LOGFONT *plfFont)
{
	LOGFONT  lfFont;
	CFontTools  cFontTools;
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	for (cFontTools.QueryDefaultFont(&lfFont); !GetOleObject(); )
	{
		CopyMemory(&m_lfFont, (!plfFont) ? &lfFont : plfFont, sizeof(LOGFONT));
		return TRUE;
	}
	return cMimicsTextItem.SetFont((!plfFont) ? &lfFont : plfFont);
}

BOOL CMimicsTextItem::GetFont(LOGFONT *plfFont) CONST
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	if (!GetOleObject())
	{
		CopyMemory(plfFont, &m_lfFont, sizeof(LOGFONT));
		return TRUE;
	}
	return cMimicsTextItem.GetFont(plfFont);
}

VOID CMimicsTextItem::AlignLeft()
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTextItem.AlignLeft();
		return;
	}
	m_nFormat &= ~(DT_CENTER | DT_RIGHT);
	m_nFormat |= DT_LEFT;
}

VOID CMimicsTextItem::AlignCenter()
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTextItem.AlignCenter();
		return;
	}
	m_nFormat &= ~(DT_LEFT | DT_RIGHT);
	m_nFormat |= DT_CENTER;
}

VOID CMimicsTextItem::AlignRight()
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTextItem.AlignRight();
		return;
	}
	m_nFormat &= ~(DT_LEFT | DT_CENTER);
	m_nFormat |= DT_RIGHT;
}

VOID CMimicsTextItem::AlignVertical(BOOL bEnable)
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTextItem.AlignVertical(bEnable);
		return;
	}
	m_nFormat = (!bEnable) ? (m_nFormat & ~DT_VCENTER) : (m_nFormat | DT_VCENTER);
}

BOOL CMimicsTextItem::IsLeftAligned() CONST
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsTextItem.IsLeftAligned() : ((m_nFormat & (DT_CENTER | DT_RIGHT)) ? !TRUE : !FALSE));
}

BOOL CMimicsTextItem::IsCenterAligned() CONST
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsTextItem.IsCenterAligned() : ((m_nFormat & DT_CENTER) ? TRUE : FALSE));
}

BOOL CMimicsTextItem::IsRightAligned() CONST
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsTextItem.IsRightAligned() : ((m_nFormat & DT_RIGHT) ? TRUE : FALSE));
}

BOOL CMimicsTextItem::IsVerticalAligned() CONST
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsTextItem.IsVerticalAligned() : ((m_nFormat & DT_VCENTER) ? TRUE : FALSE));
}

VOID CMimicsTextItem::LeftToRightReading()
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTextItem.LeftToRightReading();
		return;
	}
	m_bReading = FALSE;
}

VOID CMimicsTextItem::TopToBottomReading()
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTextItem.TopToBottomReading();
		return;
	}
	m_bReading = TRUE;
}

BOOL CMimicsTextItem::IsLeftToRightReading() CONST
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsTextItem.IsLeftToRightReading() : !m_bReading);
}

BOOL CMimicsTextItem::IsTopToBottomReading() CONST
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsTextItem.IsTopToBottomReading() : m_bReading);
}

VOID CMimicsTextItem::SetTabChars(INT nChars)
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTextItem.SetTabChars(nChars);
		return;
	}
	m_nTabs = nChars;
}

INT CMimicsTextItem::GetTabChars() CONST
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsTextItem.GetTabChars() : m_nTabs);
}

VOID CMimicsTextItem::WrapWords(BOOL bEnable)
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTextItem.WrapWords(bEnable);
		return;
	}
	m_nFormat = (bEnable) ? (m_nFormat | DT_WORDBREAK) : (m_nFormat & ~DT_WORDBREAK);
}

BOOL CMimicsTextItem::IsWrappingWords() CONST
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsTextItem.IsWrappingWords() : ((m_nFormat & DT_WORDBREAK) ? TRUE : FALSE));
}

VOID CMimicsTextItem::SingleLine(BOOL bEnable)
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsTextItem.SingleLine(bEnable);
		return;
	}
	m_nFormat = (bEnable) ? (m_nFormat | DT_SINGLELINE) : (m_nFormat & ~DT_SINGLELINE);
}

BOOL CMimicsTextItem::IsSingleLine() CONST
{
	CMimicsTextItemDispatchDriver  cMimicsTextItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsTextItem.IsSingleLine() : ((m_nFormat & DT_SINGLELINE) ? TRUE : FALSE));
}

BOOL CMimicsTextItem::Copy(CONST CMimicsItem *pItem)
{
	CMimicsTextItem  *pTextItem = (CMimicsTextItem *)pItem;

	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsTextItem)))
	{
		m_nMode = pTextItem->GetMode();
		m_nTabs = pTextItem->GetTabChars();
		m_szText = pTextItem->GetText();
		m_nColor = pTextItem->GetColor();
		m_nBkColor = pTextItem->GetBackgroundColor();
		m_bReading = pTextItem->IsTopToBottomReading();
		m_nFormat = (pTextItem->IsLeftAligned()) ? DT_LEFT : 0;
		m_nFormat |= (pTextItem->IsRightAligned()) ? DT_RIGHT : m_nFormat;
		m_nFormat |= (pTextItem->IsCenterAligned()) ? DT_CENTER : m_nFormat;
		m_nFormat |= (pTextItem->IsWrappingWords()) ? DT_WORDBREAK : m_nFormat;
		m_nFormat |= (pTextItem->IsSingleLine()) ? DT_SINGLELINE : m_nFormat;
		pTextItem->GetFont(&m_lfFont);
		return CMimicsItem::Copy(pItem);
	}
	return FALSE;
}

BOOL CMimicsTextItem::Compare(CONST CMimicsItem *pItem) CONST
{
	LOGFONT  lfFont;
	CMimicsTextItem  *pTextItem = (CMimicsTextItem *)pItem;

	return((pItem->IsKindOf(RUNTIME_CLASS(CMimicsTextItem))) ? ((pTextItem->GetMode() == GetMode() && pTextItem->GetTabChars() == GetTabChars() && pTextItem->GetText() == GetText() && pTextItem->GetColor() == GetColor() && pTextItem->GetBackgroundColor() == GetBackgroundColor() && pTextItem->IsLeftAligned() == IsLeftAligned() && pTextItem->IsCenterAligned() == IsCenterAligned() && pTextItem->IsRightAligned() == IsRightAligned() && pTextItem->IsLeftToRightReading() == IsLeftToRightReading() && pTextItem->IsTopToBottomReading() == IsTopToBottomReading() && pTextItem->IsWrappingWords() == IsWrappingWords() && pTextItem->IsSingleLine() == IsSingleLine() && pTextItem->GetFont(&lfFont) && !memcmp(&m_lfFont, &lfFont, sizeof(LOGFONT))) ? CMimicsItem::Compare(pItem) : FALSE) : FALSE);
}

BOOL CMimicsTextItem::MapProperties(CByteArray &nInfo)
{
	DATA  sData;

	GetFont(&sData.lfFont);
	sData.nMode = GetMode();
	sData.nTabs = GetTabChars();
	sData.nColor = GetColor();
	sData.nBkColor = GetBackgroundColor();
	sData.bReading = IsTopToBottomReading();
	sData.nFormat = (IsLeftAligned()) ? DT_LEFT : 0;
	sData.nFormat |= (IsRightAligned()) ? DT_RIGHT : sData.nFormat;
	sData.nFormat |= (IsCenterAligned()) ? DT_CENTER : sData.nFormat;
	sData.nFormat |= (IsWrappingWords()) ? DT_WORDBREAK : sData.nFormat;
	sData.nFormat |= (IsSingleLine()) ? DT_SINGLELINE : sData.nFormat;
	sData.cbText = (GetText().GetLength() + 1)*sizeof(TCHAR);
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbText)); nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + sizeof(DATA), (LPCTSTR)GetText(), sData.cbText);
		return TRUE;
	}
	return FALSE;
}

BOOL CMimicsTextItem::UnmapProperties(CONST CByteArray &nInfo)
{
	DATA  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbText && sData.cbText > 0; )
	{
		CopyMemory(m_szText.GetBufferSetLength(STRINGCHARS(sData.cbText)), nInfo.GetData() + sizeof(DATA), STRINGBYTES(sData.cbText));
		CopyMemory(&m_lfFont, &sData.lfFont, sizeof(LOGFONT));
		m_nMode = sData.nMode;
		m_nTabs = sData.nTabs;
		m_nColor = sData.nColor;
		m_nFormat = sData.nFormat;
		m_nBkColor = sData.nBkColor;
		m_bReading = sData.bReading;
		m_szText.ReleaseBuffer();
		return TRUE;
	}
	return FALSE;
}

VOID CMimicsTextItem::UpdateProperties()
{
	Lock();
	SetMode(m_nMode);
	SetText(m_szText);
	SetFont(&m_lfFont);
	SetColor(m_nColor);
	SetBackgroundColor(m_nBkColor);
	if (m_nFormat & ~(DT_CENTER | DT_RIGHT)) AlignLeft();
	if (m_nFormat & DT_CENTER) AlignCenter();
	if (m_nFormat & DT_RIGHT) AlignRight();
	if (m_bReading) TopToBottomReading();
	if (!m_bReading) LeftToRightReading();
	WrapWords((m_nFormat & DT_WORDBREAK) ? TRUE : FALSE);
	SingleLine((m_nFormat & DT_SINGLELINE) ? TRUE : FALSE);
	SetTabChars(m_nTabs);
	Unlock();
}

BEGIN_MESSAGE_MAP(CMimicsTextItem, CMimicsItem)
	//{{AFX_MSG_MAP(CMimicsTextItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMimicsTextItem commands


/////////////////////////////////////////////////////////////////////////////
// CMimicsImageItem

IMPLEMENT_DYNCREATE(CMimicsImageItem, CMimicsItem)

CMimicsImageItem::CMimicsImageItem(CMMDDocument *pContainerDoc) : CMimicsItem(pContainerDoc)
{
	SetItemClassID(CLSID_CMimicsImageCtrl);
	SetStyle();
	SetFileName();
	SetImageOrigin();
	SetImageSize();
	SetImageTransparency();
}

VOID CMimicsImageItem::SetStyle(INT nStyle)
{
	CMimicsImageItemDispatchDriver  cMimicsImageItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsImageItem.SetStyle(nStyle);
		return;
	}
	m_nStyle = nStyle;
}

INT CMimicsImageItem::GetStyle() CONST
{
	CMimicsImageItemDispatchDriver  cMimicsImageItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsImageItem.GetStyle() : m_nStyle);
}

VOID CMimicsImageItem::SetFileName(LPCTSTR pszFileName)
{
	CMimicsImageItemDispatchDriver  cMimicsImageItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsImageItem.SetFileName(pszFileName);
		return;
	}
	m_szFileName = pszFileName;
}

CString CMimicsImageItem::GetFileName() CONST
{
	CMimicsImageItemDispatchDriver  cMimicsImageItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsImageItem.GetFileName() : m_szFileName);
}

VOID CMimicsImageItem::SetImageOrigin(CONST POINT &pt)
{
	CMimicsImageItemDispatchDriver  cMimicsImageItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsImageItem.SetImageOrigin(pt);
		return;
	}
	m_ptImage = pt;
}

CPoint CMimicsImageItem::GetImageOrigin() CONST
{
	CMimicsImageItemDispatchDriver  cMimicsImageItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsImageItem.GetImageOrigin() : m_ptImage);
}

VOID CMimicsImageItem::SetImageSize(CONST SIZE &size)
{
	CMimicsImageItemDispatchDriver  cMimicsImageItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsImageItem.SetImageSize(size);
		return;
	}
	m_sizeImage = size;
}

CSize CMimicsImageItem::GetImageSize() CONST
{
	CMimicsImageItemDispatchDriver  cMimicsImageItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsImageItem.GetImageSize() : m_sizeImage);
}

VOID CMimicsImageItem::SetImageTransparency(BYTE nFactor)
{
	CMimicsImageItemDispatchDriver  cMimicsImageItem(GetDispatch());

	if (GetOleObject() != (LPOLEOBJECT)NULL)
	{
		cMimicsImageItem.SetImageTransparency(nFactor);
		return;
	}
	m_nImageTransparency = nFactor;
}

BYTE CMimicsImageItem::GetImageTransparency() CONST
{
	CMimicsImageItemDispatchDriver  cMimicsImageItem(GetDispatch());

	return((GetOleObject() != (LPOLEOBJECT)NULL) ? cMimicsImageItem.GetImageTransparency() : m_nImageTransparency);
}

BOOL CMimicsImageItem::Copy(CONST CMimicsItem *pItem)
{
	CMimicsImageItem  *pImageItem = (CMimicsImageItem *)pItem;

	if (pItem->IsKindOf(RUNTIME_CLASS(CMimicsImageItem)))
	{
		m_nStyle = pImageItem->GetStyle();
		m_szFileName = pImageItem->GetFileName();
		m_ptImage = pImageItem->GetImageOrigin();
		m_sizeImage = pImageItem->GetImageSize();
		m_nImageTransparency = pImageItem->GetImageTransparency();
		return CMimicsItem::Copy(pItem);
	}
	return FALSE;
}

BOOL CMimicsImageItem::Compare(CONST CMimicsItem *pItem) CONST
{
	CMimicsImageItem  *pImageItem = (CMimicsImageItem *)pItem;

	return((pItem->IsKindOf(RUNTIME_CLASS(CMimicsImageItem))) ? ((pImageItem->GetStyle() == GetStyle() && !pImageItem->GetFileName().CompareNoCase(GetFileName()) && pImageItem->GetImageOrigin() == GetImageOrigin() && pImageItem->GetImageSize() == GetImageSize() && pImageItem->GetImageTransparency() == GetImageTransparency()) ? CMimicsItem::Compare(pItem) : FALSE) : FALSE);
}

BOOL CMimicsImageItem::MapProperties(CByteArray &nInfo)
{
	DATA  sData;

	sData.nStyle = GetStyle();
	sData.ptImage = GetImageOrigin();
	sData.sizeImage = GetImageSize();
	sData.nImageTransparency = GetImageTransparency();
	sData.cbFileName = (GetFileName().GetLength() + 1)*sizeof(TCHAR);
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbFileName)); nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + sizeof(DATA), (LPCTSTR)GetFileName(), sData.cbFileName);
		return TRUE;
	}
	return FALSE;
}

BOOL CMimicsImageItem::UnmapProperties(CONST CByteArray &nInfo)
{
	DATA  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbFileName && sData.cbFileName > 0; )
	{
		CopyMemory(m_szFileName.GetBufferSetLength(STRINGCHARS(sData.cbFileName)), nInfo.GetData() + sizeof(DATA), STRINGBYTES(sData.cbFileName));
		m_nStyle = sData.nStyle;
		m_ptImage = sData.ptImage;
		m_sizeImage = sData.sizeImage;
		m_nImageTransparency = sData.nImageTransparency;
		m_szFileName.ReleaseBuffer();
		return TRUE;
	}
	return FALSE;
}

VOID CMimicsImageItem::UpdateProperties()
{
	Lock();
	SetStyle(m_nStyle);
	SetFileName(m_szFileName);
	SetImageOrigin(m_ptImage);
	SetImageSize(m_sizeImage);
	SetImageTransparency(m_nImageTransparency);
	SetItemVisibility(m_bVisible);
	Unlock();
}

BEGIN_MESSAGE_MAP(CMimicsImageItem, CMimicsItem)
	//{{AFX_MSG_MAP(CMimicsImageItem)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMimicsImageItem commands


/////////////////////////////////////////////////////////////////////////////
// CMimicsGroup

IMPLEMENT_DYNCREATE(CMimicsGroup, CMimicsItem)

CMimicsGroup::CMimicsGroup(CMMDDocument *pContainerDoc) : CMimicsItem(pContainerDoc)
{
	SetItemClassID(CLSID_CMimicsGroupCtrl);
	m_pItemList = new CMMDDocument;
}
CMimicsGroup::CMimicsGroup(LPCTSTR pszName, CMMDDocument *pContainerDoc) : CMimicsItem(pContainerDoc)
{
	SetItemClassID(CLSID_CMimicsGroupCtrl);
	m_pItemList = new CMMDDocument;
	m_szName = pszName;
}

CMimicsGroup::~CMimicsGroup()
{
	POSITION  lPosition;
	CMimicsItem  *pItem;

	for (lPosition = m_pItemList->GetStartPosition(); lPosition; )
	{
		if ((pItem = (CMimicsItem *)m_pItemList->GetNextItem(lPosition)))
		{
			delete pItem;
			continue;
		}
	}
	m_pItemList->SetModifiedFlag(FALSE);
	delete m_pItemList;
}

BOOL CMimicsGroup::CreateNewItem(REFCLSID clsid, CView *pView, OLERENDER render, CLIPFORMAT cfFormat, LPFORMATETC lpFormatEtc)
{
	INT  nCount;
	POSITION  lPosition;
	CMimicsItem  *pItem[2];

	Lock();
	if (CMimicsItem::CreateNewItem(clsid, pView, render, cfFormat, lpFormatEtc))
	{
		for (lPosition = m_pItemList->GetStartPosition(), nCount = m_pItemList->GetItemCount(); lPosition && nCount > 0; nCount--)
		{
			if ((pItem[0] = (CMimicsItem *)m_pItemList->GetNextItem(lPosition)))
			{
				if ((pItem[1] = CMimicsItem::Create(pItem[0], pView, m_pItemList)))
				{
					pItem[1]->SetItemContainer(this);
					pItem[1]->AdjustItemDefaultPosition();
					pItem[1]->SaveItemDefaultState();
					delete pItem[0];
					continue;
				}
			}
			break;
		}
		Unlock();
		return((!nCount) ? TRUE : FALSE);
	}
	Unlock();
	return FALSE;
}

VOID CMimicsGroup::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CMimicsGroup::GetName() CONST
{
	return m_szName;
}

VOID CMimicsGroup::SetItemPosition(CONST RECT &rect)
{
	CRect  rPosition;

	rPosition = rect;
	rPosition.OffsetRect(GetPosition().CenterPoint() - GetItemPosition().CenterPoint());
	SetPosition(rPosition);
}

CRect CMimicsGroup::GetItemPosition() CONST
{
	return m_rPosition[0];
}

VOID CMimicsGroup::NormalizeItemPosition(BOOL bUndo)
{
	POSITION  lPosition;
	CMimicsItem  *pItem;

	if (!bUndo)
	{
		for (lPosition = m_pItemList->GetStartPosition(); lPosition; )
		{
			if ((pItem = (CMimicsItem *)m_pItemList->GetNextItem(lPosition)))
			{
				pItem->NormalizeItemPosition(bUndo);
				continue;
			}
		}
		DoTransformation(m_ptCenter[0], m_xForm[0], m_rPosition[0]);
		return;
	}
	for (lPosition = m_pItemList->GetStartPosition(), DoInverseTransformation(m_ptCenter[0], m_xForm[0], m_rPosition[0]); lPosition; )
	{
		if ((pItem = (CMimicsItem *)m_pItemList->GetNextItem(lPosition)))
		{
			pItem->NormalizeItemPosition(bUndo);
			continue;
		}
	}
}

VOID CMimicsGroup::AdjustItemPosition()
{
	CRect  rItem;
	CRect  rGroup;
	POSITION  lPosition;
	CMimicsItem  *pItem;

	for (lPosition = m_pItemList->GetStartPosition(), rGroup.SetRectEmpty(); lPosition; )
	{
		if ((pItem = (CMimicsItem *)m_pItemList->GetNextItem(lPosition)))
		{
			rItem = pItem->CalcItemFrameExtent();
			if (rGroup.IsRectNull())
			{
				rGroup.left = min(rItem.left, rItem.right);
				rGroup.top = min(rItem.top, rItem.bottom);
				rGroup.right = max(rItem.left, rItem.right);
				rGroup.bottom = max(rItem.top, rItem.bottom);
				continue;
			}
			rGroup.left = min(min(rItem.left, rItem.right), rGroup.left);
			rGroup.top = min(min(rItem.top, rItem.bottom), rGroup.top);
			rGroup.right = max(max(rItem.left, rItem.right), rGroup.right);
			rGroup.bottom = max(max(rItem.top, rItem.bottom), rGroup.bottom);
		}
	}
	for (lPosition = m_pItemList->GetStartPosition(); lPosition; )
	{
		if ((pItem = (CMimicsItem *)m_pItemList->GetNextItem(lPosition)))
		{
			pItem->NormalizeItemPosition();
			continue;
		}
	}
	if (!m_pItemList->GetStartPosition())
	{
		m_rPosition[0].DeflateRect(m_rPosition[0].Width(), m_rPosition[0].Height());
		SetItemSize(rGroup.Width(), rGroup.Height());
		SetItemCenterPoint();
		return;
	}
	m_rPosition[0] = rGroup;
	m_ptCenter[0] = rGroup.CenterPoint();
	m_xForm[0].eM11 = m_xForm[0].eM22 = (float) 1.0;
	m_xForm[0].eM12 = m_xForm[0].eM21 = (float) 0.0;
	m_xForm[0].eDx = m_xForm[0].eDy = (float) 0.0;
	for (lPosition = m_pItemList->GetStartPosition(); lPosition; )
	{
		if ((pItem = (CMimicsItem *)m_pItemList->GetNextItem(lPosition)))
		{
			pItem->NormalizeItemPosition(TRUE);
			pItem->AdjustItemDefaultPosition();
		}
	}
	SetItemSize(rGroup.Width(), rGroup.Height());
	AdjustItemContainer();
}
VOID CMimicsGroup::AdjustItemPosition(CONST RECT &rect)
{
	CRect  rItem;
	CPoint  ptItem;
	POSITION  lPosition;
	CMimicsItem  *pItem;

	if (!m_rPosition[0].EqualRect(&rect))
	{
		if (m_rPosition[0].Width() == rect.right - rect.left &&  m_rPosition[0].Height() == rect.bottom - rect.top)
		{
			for (lPosition = m_pItemList->GetStartPosition(); lPosition; )
			{
				if ((pItem = (CMimicsItem *)m_pItemList->GetNextItem(lPosition)))
				{
					rItem = pItem->GetItemPosition();
					rItem.OffsetRect(rect.left - m_rPosition[0].left, 0);
					rItem.OffsetRect(0, rect.top - m_rPosition[0].top);
					pItem->AdjustItemPosition(rItem);
				}
			}
			m_ptCenter[0].x += (rect.left + rect.right) / 2 - m_rPosition[0].CenterPoint().x;
			m_ptCenter[0].y += (rect.top + rect.bottom) / 2 - m_rPosition[0].CenterPoint().y;
		}
		else
		{
			for (lPosition = m_pItemList->GetStartPosition(); lPosition; )
			{
				if ((pItem = (CMimicsItem *)m_pItemList->GetNextItem(lPosition)))
				{
					rItem = pItem->GetItemDefaultPosition();
					rItem.left = (rItem.left*(rect.right - rect.left)) / GetSystemMetrics(SM_CXSCREEN);
					rItem.top = (rItem.top*(rect.bottom - rect.top)) / GetSystemMetrics(SM_CYSCREEN);
					rItem.right = (rItem.right*(rect.right - rect.left)) / GetSystemMetrics(SM_CXSCREEN);
					rItem.bottom = (rItem.bottom*(rect.bottom - rect.top)) / GetSystemMetrics(SM_CYSCREEN);
					rItem.OffsetRect(rect.left, rect.top);
					pItem->SetItemCenterPoint(rItem.CenterPoint());
					pItem->AdjustItemPosition(rItem);
				}
			}
		}
		m_rPosition[0] = rect;
	}
}

VOID CMimicsGroup::AdjustItemCenterPoint()
{
	CRect  rItem;
	CRect  rPosition;
	CSize  ptOffset;
	CPoint  ptItem[2];
	POSITION  lPosition;
	CMimicsItem  *pItem;

	rPosition = GetItemPosition();
	if (m_ptCenter[0] != rPosition.CenterPoint())
	{
		ptItem[0] = DoTransformation(rPosition.TopLeft());
		ptItem[1] = DoTransformation(rPosition.BottomRight());
		m_ptCenter[0].x = (ptItem[0].x + ptItem[1].x) / 2;
		m_ptCenter[0].y = (ptItem[0].y + ptItem[1].y) / 2;
		ptOffset = m_ptCenter[0] - rPosition.CenterPoint();
		for (lPosition = m_pItemList->GetStartPosition(); lPosition; )
		{
			if ((pItem = (CMimicsItem *)m_pItemList->GetNextItem(lPosition)))
			{
				rItem = pItem->GetItemPosition();
				rItem.OffsetRect(ptOffset.cx, ptOffset.cy);
				pItem->AdjustItemPosition(rItem);
			}
		}
		rPosition.OffsetRect(ptOffset);
		m_rPosition[0] = rPosition;
	}
}

BOOL CMimicsGroup::IsItemSizeable() CONST
{
	POSITION  lPosition;
	CMimicsItem  *pItem;

	for (lPosition = m_pItemList->GetStartPosition(); lPosition; )
	{
		if ((pItem = (CMimicsItem *)m_pItemList->GetNextItem(lPosition)))
		{
			if (pItem->IsItemFlippedOrRotated() || !pItem->IsItemSizeable())
			{
				lPosition = (POSITION)-1;
				break;
			}
		}
	}
	return((!lPosition) ? TRUE : FALSE);
}

VOID CMimicsGroup::AddItem(CMimicsItem *pItem)
{
	for (m_pItemList->AddItem(pItem), pItem->NormalizeItemPosition(), pItem->SetItemContainer(this), pItem->NormalizeItemPosition(TRUE); TRUE; )
	{
		AdjustItemPosition();
		break;
	}
	pItem->SaveItemDefaultState();
	SaveItemDefaultState();
}

VOID CMimicsGroup::RemoveItem(CMimicsItem *pItem)
{
	for (m_pItemList->RemoveItem(pItem), pItem->NormalizeItemPosition(), pItem->SetItemContainer(NULL), pItem->NormalizeItemPosition(TRUE); TRUE; )
	{
		AdjustItemPosition();
		break;
	}
	pItem->SaveItemDefaultState();
	SaveItemDefaultState();
}

CMimicsItem *CMimicsGroup::GetAt(INT nIndex) CONST
{
	INT  nItem;
	POSITION  lPosition;
	CMimicsItem  *pItem;

	for (lPosition = m_pItemList->GetStartPosition(), nItem = 0; lPosition && nIndex >= 0 && nIndex < m_pItemList->m_docItemList.GetCount(); nItem++)
	{
		if ((pItem = (CMimicsItem *)m_pItemList->GetNextItem(lPosition)) && nItem == nIndex) break;
		continue;
	}
	return((nItem == nIndex) ? pItem : (CMimicsItem *)NULL);
}

CMimicsItem *CMimicsGroup::operator[](INT nIndex) CONST
{
	INT  nItem;
	POSITION  lPosition;
	CMimicsItem  *pItem;

	for (lPosition = m_pItemList->GetStartPosition(), nItem = 0; lPosition && nIndex >= 0 && nIndex < m_pItemList->m_docItemList.GetCount(); nItem++)
	{
		if ((pItem = (CMimicsItem *)m_pItemList->GetNextItem(lPosition)) && nItem == nIndex) break;
		continue;
	}
	return((nItem == nIndex) ? pItem : (CMimicsItem *)NULL);
}

CMMDDocument *CMimicsGroup::GetItemList() CONST
{
	return m_pItemList;
}

INT CMimicsGroup::GetItemCount() CONST
{
	return((INT)m_pItemList->m_docItemList.GetCount());
}

VOID CMimicsGroup::RemoveAllItems()
{
	POSITION  lPosition;
	CMimicsItem  *pItem;

	for (lPosition = m_pItemList->GetStartPosition(); lPosition; )
	{
		if ((pItem = (CMimicsItem *)m_pItemList->GetNextItem(lPosition)))
		{
			delete pItem;
			continue;
		}
	}
	m_pItemList->SetModifiedFlag(FALSE);
	AdjustItemPosition();
}

BOOL CMimicsGroup::Draw(CDC *pDC, BOOL bShape)
{
	POSITION  lPosition;
	CMimicsItem  *pItem;

	for (lPosition = (GetItemVisibility()) ? m_pItemList->GetStartPosition() : (POSITION)NULL; lPosition; )
	{
		if ((pItem = (CMimicsItem *)m_pItemList->GetNextItem(lPosition)))
		{
			pItem->Draw(pDC, bShape);
			continue;
		}
	}
	return TRUE;
}

VOID CMimicsGroup::Reset()
{
	POSITION  lPosition;
	CMimicsItem  *pItem;

	Lock();
	for (lPosition = m_pItemList->GetStartPosition(); lPosition; )
	{
		if ((pItem = (CMimicsItem *)m_pItemList->GetNextItem(lPosition)))
		{
			pItem->Reset();
			continue;
		}
	}
	CMimicsItem::Reset();
	Unlock();
}

BOOL CMimicsGroup::CheckPointInsideItem(CONST POINT &ptPosition)
{
	POSITION  lPosition;
	CMimicsItem  *pItem;

	for (lPosition = (GetItemVisibility()) ? m_pItemList->GetStartPosition() : (POSITION)NULL; lPosition; )
	{
		if ((pItem = (CMimicsItem *)m_pItemList->GetNextItem(lPosition)))
		{
			if (pItem->CheckPointOnItem(ptPosition)) return TRUE;
			continue;
		}
	}
	return FALSE;
}

BOOL CMimicsGroup::Copy(CONST CMimicsItem *pItem)
{
	POSITION  lPosition;
	CMimicsItem  *pMimicsItem[2];
	CMimicsGroup  *pMimicsGroup;

	for (lPosition = (pItem->IsKindOf(RUNTIME_CLASS(CMimicsGroup))) ? (pMimicsGroup = (CMimicsGroup *)pItem)->m_pItemList->GetStartPosition() : (POSITION)-1, RemoveAllItems(); lPosition && lPosition != (POSITION)-1; )
	{
		if ((pMimicsItem[0] = (CMimicsItem *)pMimicsGroup->m_pItemList->GetNextItem(lPosition)))
		{
			if ((pMimicsItem[1] = CMimicsItem::AllocateFromItem(pMimicsItem[0])))
			{
				if (pMimicsItem[1]->Copy(pMimicsItem[0]))
				{
					pMimicsItem[1]->SetItemContainer(this);
					m_pItemList->AddItem(pMimicsItem[1]);
					continue;
				}
				delete pMimicsItem[1];
			}
		}
		lPosition = (POSITION)-1;
		break;
	}
	return((!lPosition) ? CMimicsItem::Copy(pItem) : FALSE);
}

BOOL CMimicsGroup::Compare(CONST CMimicsItem *pItem) CONST
{
	POSITION  lPosition[2];
	CMimicsItem  *pMimicsItem[2];
	CMimicsGroup  *pMimicsGroup;

	for (lPosition[0] = (pItem->IsKindOf(RUNTIME_CLASS(CMimicsGroup))) ? (((pMimicsGroup = (CMimicsGroup *)pItem)->GetItemCount() == GetItemCount()) ? pMimicsGroup->m_pItemList->GetStartPosition() : (POSITION)-1) : (POSITION)-1, lPosition[1] = (lPosition[0] && lPosition[0] != (POSITION)-1) ? m_pItemList->GetStartPosition() : (POSITION)-1; lPosition[0] && lPosition[0] != (POSITION)-1 && lPosition[1] && lPosition[1] != (POSITION)-1; )
	{
		if ((pMimicsItem[0] = (CMimicsItem *)pMimicsGroup->m_pItemList->GetNextItem(lPosition[0])))
		{
			if ((pMimicsItem[1] = (CMimicsItem *)m_pItemList->GetNextItem(lPosition[1])))
			{
				if (!pMimicsItem[0]->Compare(pMimicsItem[1]))
				{
					lPosition[0] = lPosition[1] = (POSITION)-1;
					break;
				}
				continue;
			}
		}
		lPosition[0] = lPosition[1] = (POSITION)-1;
		break;
	}
	return((!lPosition[0] && !lPosition[1]) ? CMimicsItem::Compare(pItem) : FALSE);
}

BOOL CMimicsGroup::MapProperties(CByteArray &nInfo)
{
	POSITION  lPosition;
	CByteArray  nItemData;
	CMimicsItem  *pItem;

	for (lPosition = m_pItemList->GetStartPosition(), nInfo.RemoveAll(); lPosition; )
	{
		if ((pItem = (CMimicsItem *)m_pItemList->GetNextItem(lPosition)) && pItem->Map(nItemData) && nInfo.Append(nItemData) >= 0) continue;
		lPosition = (POSITION)-1;
		break;
	}
	return((!lPosition) ? TRUE : FALSE);
}

BOOL CMimicsGroup::UnmapProperties(CONST CByteArray &nInfo)
{
	INT  cbItem;
	INT  cbItems;
	POSITION  lPosition;
	CByteArray  nItemData;
	CMimicsItem  *pItem;

	for (lPosition = m_pItemList->GetStartPosition(); lPosition; )
	{
		if ((pItem = (CMimicsItem *)m_pItemList->GetNextItem(lPosition)))
		{
			m_pItemList->RemoveItem(pItem);
			delete pItem;
		}
	}
	for (cbItems = 0; cbItems < nInfo.GetSize(); cbItems += cbItem)
	{
		for (CopyMemory(&cbItem, nInfo.GetData() + cbItems, sizeof(cbItem)), nItemData.SetSize(max(min(cbItem, nInfo.GetSize() - cbItems), 0)); nItemData.GetSize() >= 0; )
		{
			CopyMemory(nItemData.GetData(), nInfo.GetData() + cbItems, nItemData.GetSize());
			break;
		}
		if ((pItem = CMimicsItem::AllocateFromData(nItemData)))
		{
			if (pItem->Unmap(nItemData))
			{
				pItem->SetItemContainer(this);
				m_pItemList->AddItem(pItem);
				continue;
			}
			delete pItem;
		}
		break;
	}
	return((cbItems == nInfo.GetSize()) ? TRUE : FALSE);
}

BEGIN_MESSAGE_MAP(CMimicsGroup, CMimicsItem)
	//{{AFX_MSG_MAP(CMimicsGroup)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMimicsGroup commands


/////////////////////////////////////////////////////////////////////////////
// CMMDToolBar

IMPLEMENT_DYNCREATE(CMMDToolBar, CDisplayToolBar)

CMMDToolBar::CMMDToolBar() : CDisplayToolBar()
{
	return;
}

BEGIN_MESSAGE_MAP(CMMDToolBar, CDisplayToolBar)
	//{{AFX_MSG_MAP(CMMDToolBar)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDToolBar message handlers


/////////////////////////////////////////////////////////////////////////////
// CMMDStatusBar

IMPLEMENT_DYNCREATE(CMMDStatusBar, CDisplayStatusBar)

CMMDStatusBar::CMMDStatusBar() : CDisplayStatusBar()
{
	return;
}

BOOL CMMDStatusBar::SetIndicators(CONST UINT *pPanesID, INT nCount)
{
	INT  nIndex;
	CRect  rPane;
	CString  szPane;
	CToolInfo  cToolInfo;
	CDisplayLock  cLock(this);

	if (CDisplayStatusBar::SetIndicators(pPanesID, nCount))
	{
		if (CommandToIndex(ID_MMD_STATUSBAR_MESSAGEPANE) >= 0)
		{
			szPane.Format(STRING(IDS_MMD_STATUSBAR_UPDATEMESSAGE), (LPCTSTR)CTimeTag().FormatGmt(), (LPCTSTR)CString(CTimeTag().FormatGmt().Right(1), GetDatabase()->GetTMPacketTagLength()), -1, STRING(IDS_MMD_STATUSBAR_QUALITYGOOD));
			SetPaneInfo(CommandToIndex(ID_MMD_STATUSBAR_MESSAGEPANE), ID_MMD_STATUSBAR_MESSAGEPANE, SBPS_NOBORDERS | SBPS_STRETCH, CalcPaneWidth(szPane + STRING(IDS_MMD_STATUSBAR_TIMECORRELATIONFLAG)));
		}
		if (!IsWindow(m_wndToolTip.GetSafeHwnd()))
		{
			m_wndToolTip.Create(this, TTS_ALWAYSTIP | TTS_NOPREFIX | TTS_BALLOON);
			SetClassLongPtr(m_wndToolTip.GetSafeHwnd(), GCL_STYLE, GetClassLongPtr(m_wndToolTip.GetSafeHwnd(), GCL_STYLE) | CS_DROPSHADOW);
		}
		if (IsWindow(m_wndToolTip.GetSafeHwnd()))
		{
			if ((nIndex = CommandToIndex(ID_MMD_STATUSBAR_MODEPANE)) >= 0)
			{
				for (GetItemRect(nIndex, rPane); !m_wndToolTip.GetToolInfo(cToolInfo, this, ID_MMD_STATUSBAR_MODEPANE); )
				{
					m_wndToolTip.AddTool(this, LPSTR_TEXTCALLBACK, rPane, ID_MMD_STATUSBAR_MODEPANE);
					break;
				}
			}
			if ((nIndex = CommandToIndex(ID_MMD_STATUSBAR_TYPEPANE)) >= 0)
			{
				for (GetItemRect(nIndex, rPane); !m_wndToolTip.GetToolInfo(cToolInfo, this, ID_MMD_STATUSBAR_TYPEPANE); )
				{
					m_wndToolTip.AddTool(this, LPSTR_TEXTCALLBACK, rPane, ID_MMD_STATUSBAR_TYPEPANE);
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

CMMDWnd *CMMDStatusBar::GetParent() CONST
{
	return((CMMDWnd *)CDisplayStatusBar::GetParent());
}

BEGIN_MESSAGE_MAP(CMMDStatusBar, CDisplayStatusBar)
	//{{AFX_MSG_MAP(CMMDStatusBar)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipNotify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDStatusBar message handlers

void CMMDStatusBar::OnPaint()
{
	INT  nIndex;
	RECT  rPane;
	CToolInfo  cToolInfo;

	for (CDisplayStatusBar::OnPaint(); IsWindow(m_wndToolTip.GetSafeHwnd()); )
	{
		if ((nIndex = CommandToIndex(ID_MMD_STATUSBAR_MODEPANE)) >= 0 && nIndex < m_prPanes.GetSize())
		{
			for (m_wndToolTip.GetToolInfo(cToolInfo, this, ID_MMD_STATUSBAR_MODEPANE), CopyMemory(&rPane, m_prPanes.GetAt(nIndex), sizeof(RECT)); !EqualRect(&cToolInfo.rect, &rPane); )
			{
				SetRect(&cToolInfo.rect, rPane.left, rPane.top, rPane.right, rPane.bottom);
				m_wndToolTip.SetToolInfo(&cToolInfo);
				break;
			}
		}
		if ((nIndex = CommandToIndex(ID_MMD_STATUSBAR_TYPEPANE)) >= 0 && nIndex < m_prPanes.GetSize())
		{
			for (m_wndToolTip.GetToolInfo(cToolInfo, this, ID_MMD_STATUSBAR_TYPEPANE), CopyMemory(&rPane, m_prPanes.GetAt(nIndex), sizeof(RECT)); !EqualRect(&cToolInfo.rect, &rPane); )
			{
				SetRect(&cToolInfo.rect, rPane.left, rPane.top, rPane.right, rPane.bottom);
				m_wndToolTip.SetToolInfo(&cToolInfo);
				break;
			}
		}
		break;
	}
}

void CMMDStatusBar::OnMouseMove(UINT nFlags, CPoint point)
{
	MSG  sMsg;

	if (IsWindow(m_wndToolTip.GetSafeHwnd()))
	{
		CopyMemory(&sMsg, GetCurrentMessage(), sizeof(MSG));
		m_wndToolTip.RelayEvent(&sMsg);
	}
	CDisplayStatusBar::OnMouseMove(nFlags, point);
}

BOOL CMMDStatusBar::OnToolTipNotify(UINT nID, NMHDR *pNotifyInfo, LRESULT *pResult)
{
	TOOLTIPTEXT  *pToolTipInfo = (TOOLTIPTEXT *)pNotifyInfo;

	switch (pNotifyInfo->idFrom)
	{
	case ID_MMD_STATUSBAR_MODEPANE:
	{ pToolTipInfo->lpszText = (LPTSTR)STRING(IDS_MMD_STATUSBAR_MODEPANE);
	return TRUE;
	}
	case ID_MMD_STATUSBAR_TYPEPANE:
	{ pToolTipInfo->lpszText = (LPTSTR)STRING(IDS_MMD_STATUSBAR_TYPEPANE);
	return TRUE;
	}
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CMMDToolTip

IMPLEMENT_DYNCREATE(CMMDToolTip, CDisplayToolTip)

CMMDToolTip::CMMDToolTip() : CDisplayToolTip()
{
	return;
}

BEGIN_MESSAGE_MAP(CMMDToolTip, CDisplayToolTip)
	//{{AFX_MSG_MAP(CMMDToolTip)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDToolTip message handlers


/////////////////////////////////////////////////////////////////////////////
// CMMDView

IMPLEMENT_DYNCREATE(CMMDView, CScrollView)

CMMDView::CMMDView() : CScrollView(), CDisplayLockable()
{
	m_nImage[0] = 0;
	m_nImage[1] = 0;
	m_nImage[2] = 0;
	m_nImage[3] = 0;
	m_sizeGrid.cx = 0;
	m_sizeGrid.cy = 0;
	m_sizeImage.cx = 0;
	m_sizeImage.cy = 0;
	m_ptScroll.x = 0;
	m_ptScroll.y = 0;
	m_bItems = FALSE;
	m_bUseGrid = FALSE;
	m_bToolTipMode = TRUE;
	m_bBadDataMode = FALSE;
	m_bInvalidDataMode = FALSE;
	m_nImageGrid = VGA_COLOR_LTGRAY;
	m_nImageBkgnd = GetSysColor(COLOR_WINDOW);
	m_hImageCode = (HINSTANCE)NULL;
	m_hToolTipCursor = (HCURSOR)NULL;
	m_hLinkTipCursor = (HCURSOR)NULL;
	m_pIUnknown = (IUnknown *)NULL;
	m_pDocument = (CMMDDocument *)NULL;
	m_pIClassFactory = (IClassFactory *)NULL;
	m_pIEnumMimicsCtrls = (IEnumMimicsCtrls *)NULL;
	m_pParentWnd = (CWnd *)NULL;
}

BOOL CMMDView::Create(CWnd *pParentWnd)
{
	return CScrollView::Create((LPCTSTR)NULL, EMPTYSTRING, WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE, CRect(0, 0, 0, 0), (m_pParentWnd = pParentWnd), 0);
}

BOOL CMMDView::SetLayout(CONST CMMDLayout &cLayout, CString &szMessage)
{
	INT  nItem;
	INT  nItems;
	CString  szName;
	POSITION  lPosition;
	CMimicsItem  *pItem;
	CMMDDocument  *pDocument;
	CMMDLayoutItem  *pLayoutItem[2];
	CDisplayLock  cLock(this);

	if (IsWindow(GetSafeHwnd()))
	{
		if (!m_pDocument->GetItemCount() || !m_cLayout.Compare(&cLayout))
		{
			for (nItem = 0, nItems = (m_pDocument->GetItemCount() > 0 && m_cLayout.GetName() == cLayout.GetName() && m_cLayout.GetSize() == cLayout.GetSize()) ? (INT)m_cLayout.GetSize() : -1, szName = m_cLayout.GetName(); nItem < nItems; nItem++)
			{
				if ((pLayoutItem[0] = m_cLayout.GetAt(nItem)) != (CMMDLayoutItem *)NULL)
				{
					if ((pLayoutItem[1] = cLayout.GetAt(nItem)) != (CMMDLayoutItem *)NULL)
					{
						if (pLayoutItem[0]->GetName() != pLayoutItem[1]->GetName()) break;
						continue;
					}
				}
			}
			if (nItem == nItems)
			{
				cLayout.GetImage(m_sizeImage, m_nImage[0], m_nImage[1], m_nImage[2], m_nImage[3], m_nImageBkgnd, m_sizeGrid, m_nImageGrid, m_bUseGrid);
				m_cLayout.SetImage(m_sizeImage, m_nImage[0], m_nImage[1], m_nImage[2], m_nImage[3], m_nImageBkgnd, m_sizeGrid, m_nImageGrid, m_bUseGrid);
				AdjustToImageSize(FALSE);
				return TRUE;
			}
			if ((pDocument = new CMMDDocument))
			{
				for (lPosition = (m_cLayout.Copy(&cLayout)) ? ((pDocument->Unmap(cLayout)) ? pDocument->m_docItemList.GetHeadPosition() : (POSITION)NULL) : (POSITION)NULL, m_cLayout.GetImage(m_sizeImage, m_nImage[0], m_nImage[1], m_nImage[2], m_nImage[3], m_nImageBkgnd, m_sizeGrid, m_nImageGrid, m_bUseGrid), FreeLayoutCode(), m_pDocument->DeleteContents(), m_szItemsParameters.RemoveAll(), m_pItemsCode.RemoveAll(), m_pItems.RemoveAll(), m_bItems = FALSE; lPosition; )
				{
					if ((pItem = (CMimicsItem *)pDocument->m_docItemList.GetNext(lPosition)) && CMimicsItem::Create(pItem, this, m_pDocument)) continue;
					lPosition = (POSITION)-1;
					break;
				}
				if (!lPosition)
				{
					if (LoadLayoutCode(szMessage))
					{
						AdjustToImageSize((szName != cLayout.GetName()) ? TRUE : FALSE);
						delete pDocument;
						return TRUE;
					}
				}
				UpdateScrollBars();
				delete pDocument;
			}
			return FALSE;
		}
		return TRUE;
	}
	return m_cLayout.Copy(&cLayout);
}

BOOL CMMDView::GetLayout(CMMDLayout &cLayout) CONST
{
	CDisplayLock  cLock(this);

	return cLayout.Copy(&m_cLayout);
}

BOOL CMMDView::EnableInvalidDataMode(BOOL bEnable)
{
	m_bInvalidDataMode = bEnable;
	return TRUE;
}

BOOL CMMDView::IsInvalidDataModeEnabled() CONST
{
	return m_bInvalidDataMode;
}

BOOL CMMDView::EnableBadDataMode(BOOL bEnable)
{
	m_bBadDataMode = bEnable;
	return TRUE;
}

BOOL CMMDView::IsBadDataModeEnabled() CONST
{
	return m_bBadDataMode;
}

BOOL CMMDView::EnableToolTipMode(BOOL bEnable)
{
	m_bToolTipMode = bEnable;
	return TRUE;
}

BOOL CMMDView::IsToolTipModeEnabled() CONST
{
	return m_bToolTipMode;
}

BOOL CMMDView::Initialize(CTMEnvironment *pTMEnvironment)
{
	INT  nItem;
	INT  nItems;
	BOOL  bSuccess;
	CString  szItem;
	CString  szInit;
	CPtrArray  pItems;
	CPtrArray  pItemsCode;
	CMimicsItem  *pItem;
	CStringArray  szItems;
	CStringArray  szParameters;
	BOOL(__cdecl *pInitialize)(CONST CDatabaseEngine *pDatabase, CTMEnvironment *pTMEnvironment, CONST CStringArray &szItems, CPtrArray &pItems, CStringArray &szParameters);
	CDisplayLock  cLock(this);

	for (nItem = 0, nItems = GetDocument()->EnumItems(pItems); nItem < nItems; nItem++)
	{
		if ((pItem = (CMimicsItem *)pItems.GetAt(nItem)))
		{
			szItem = pItem->GetItemName();
			szItems.Add(szItem);
		}
	}
	if (!m_hImageCode)
	{
		m_szItemsParameters.RemoveAll();
		m_pItemsCode.RemoveAll();
		m_pItems.RemoveAll();
		m_bItems = TRUE;
		return TRUE;
	}
#ifndef UNICODE
	szInit = STRING(IDS_EXPORTINTERFACE_INITIALIZEMIMICSDISPLAY);
#else
	WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_INITIALIZEMIMICSDISPLAY), -1, (LPSTR)szInit.GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_INITIALIZEMIMICSDISPLAY))), lstrlen(STRING(IDS_EXPORTINTERFACE_INITIALIZEMIMICSDISPLAY)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
	szInit.ReleaseBuffer();
#endif
	if ((pInitialize = (BOOL(__cdecl *)(CONST CDatabaseEngine *pDatabase, CTMEnvironment *pTMEnvironment, CONST CStringArray &szItems, CPtrArray &pItems, CStringArray &szParameters)) GetProcAddress(m_hImageCode, (LPCSTR)(LPCTSTR)szInit)))
	{
		for (nItem = 0, nItems = ((bSuccess = (*pInitialize)(GetDatabase(), pTMEnvironment, szItems, pItemsCode, szParameters)) >= 0 && pItems.GetSize() == pItemsCode.GetSize()) ? (INT)pItems.GetSize() : -1; nItem < nItems; nItem++)
		{
			if (!pItemsCode.GetAt(nItem))
			{
				pItemsCode.RemoveAt(nItem);
				pItems.RemoveAt(nItem);
				nItems--;
				nItem--;
			}
		}
		if (nItem == nItems)
		{
			m_szItemsParameters.Copy(szParameters);
			m_pItemsCode.Copy(pItemsCode);
			m_pItems.Copy(pItems);
			m_bItems = TRUE;
			return bSuccess;
		}
	}
	return FALSE;
}
BOOL CMMDView::Initialize(CString &szTag, CTimeTag &tTag)
{
	INT  nMode;
	INT  nIndex;
	INT  nParameter;
	INT  nParameters;
	BOOL  bParameters[2];
	CTMParameter  *pTMParameter;
	CTMParameters  cTMParameters;
	CTMEnvironment  cTMEnvironment;
	CDatabaseTMParameter  *pDatabaseTMParameter;
	CDisplayLock  cLock(this);

	for (nParameter = 0, bParameters[0] = (m_pItems.GetSize() > 0) ? TRUE : FALSE, nParameters = (cTMEnvironment.Create(GetDatabase(), FALSE) && (m_pItems.GetSize() > 0 || (bParameters[0] = Initialize(&cTMEnvironment)) >= 0)) ? (INT)m_szItemsParameters.GetSize() : -1, bParameters[1] = m_bItems; nParameter < nParameters; nParameter++)
	{
		if ((pDatabaseTMParameter = GetDatabase()->GetTMParameters()->GetAt((nIndex = GetDatabase()->GetTMParameters()->Find(m_szItemsParameters.GetAt(nParameter))))))
		{
			if ((pTMParameter = new CTMParameter) != (CTMParameter *)NULL)
			{
				pTMParameter->SetTag(pDatabaseTMParameter->GetTag());
				pTMParameter->SetAttributes(pDatabaseTMParameter->GetAttributes());
				cTMParameters.Add(pTMParameter);
			}
			if ((pTMParameter = new CTMParameter))
			{
				pTMParameter->SetTag(pDatabaseTMParameter->GetTag());
				pTMParameter->SetAttributes(pDatabaseTMParameter->GetAttributes());
				cTMEnvironment.GetTMParameters()->SetAtGrow(nIndex, pTMParameter);
			}
		}
	}
	for (nParameter = 0, nParameters = (nParameters >= 0 && (bParameters[0] || Initialize(&cTMEnvironment))) ? ((((nMode = GetParent()->GetMode()) == DISPLAY_MODE_REALTIME && InitializeTMData(*cTMEnvironment.GetTMParameters(), IsBadDataModeEnabled()) && InitializeTMData(cTMParameters, IsBadDataModeEnabled())) || (nMode == DISPLAY_MODE_HISTORY && GetParent()->InitializeTMData(*cTMEnvironment.GetTMParameters(), IsBadDataModeEnabled()) && GetParent()->InitializeTMData(cTMParameters, IsBadDataModeEnabled()))) ? (INT)cTMParameters.GetSize() : -1) : -1, szTag.Empty(), tTag = 0; nParameter < nParameters; nParameter++)
	{
		if ((pTMParameter = cTMParameters.GetAt(nParameter)) && pTMParameter->IsInitialized() && tTag < pTMParameter->GetLastUpdateTime())
		{
			szTag = pTMParameter->GetLastUpdateTMUnit();
			tTag = pTMParameter->GetLastUpdateTime();
		}
	}
	for (m_bItems = bParameters[1]; nParameter == nParameters; )
	{
		Update(&cTMEnvironment);
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDView::Update(CTMEnvironment *pTMEnvironment)
{
	INT  nItem;
	INT  nItems;
	BOOL  bItems;
	CString  szTag;
	CTimeTag  tTag;
	CMimicsItem  *pItem;
	CMimicsObjectDispatchDriver  *pItemDriver;
	CDisplayLock  cLock(this);

	if (!pTMEnvironment->GetTMUnit()->HasBadData() || IsBadDataModeEnabled())
	{
		for (nItem = 0, nItems = (m_bItems || Initialize(pTMEnvironment)) ? (INT)m_pItems.GetSize() : 0, bItems = FALSE; nItem < nItems; nItem++)
		{
			if ((pItem = (CMimicsItem *)m_pItems.GetAt(nItem)) != (CMimicsItem *)NULL)
			{
				if ((pItemDriver = (CMimicsObjectDispatchDriver *)m_pItemsCode.GetAt(nItem)))
				{
					for (pItem->Lock(), pItemDriver->AttachDispatch(pItem); TRUE; )
					{
						bItems = (pItemDriver->Update(GetDatabase(), pTMEnvironment, IsInvalidDataModeEnabled())) ? TRUE : bItems;
						break;
					}
					pItemDriver->ReleaseDispatch();
					pItem->Unlock();
				}
			}
		}
		if (bItems)
		{
			DrawImage();
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CMMDView::Reset(CTMEnvironment *pTMEnvironment)
{
	POSITION  lPosition;
	CMimicsItem  *pItem;
	CDisplayLock  cLock(this);

	for (lPosition = m_pDocument->m_docItemList.GetHeadPosition(); lPosition; )
	{
		if ((pItem = (CMimicsItem *)m_pDocument->m_docItemList.GetNext(lPosition)))
		{
			pItem->Reset();
			continue;
		}
	}
	Initialize(pTMEnvironment);
	DrawImage();
	return TRUE;
}

VOID CMMDView::DrawImage()
{
	CDC  *pDC;
	CDisplayLock  cLock(this);

	if ((pDC = GetDC()))
	{
		pDC->SetWindowOrg(m_ptScroll);
		DrawImage(pDC);
		ReleaseDC(pDC);
	}
}

BOOL CMMDView::HasImage() CONST
{
	CDisplayLock  cLock(this);

	return((GetDocument()->GetItemCount() > 0) ? TRUE : FALSE);
}

BOOL CMMDView::SetImageSize(CONST SIZE &size)
{
	CDisplayLock  cLock(this);

	SetScrollSizes(MM_TEXT, size);
	return TRUE;
}

BOOL CMMDView::GetImageSize(CSize &size) CONST
{
	CDisplayLock  cLock(this);

	size = GetTotalSize();
	return TRUE;
}

VOID CMMDView::AdjustToImageSize()
{
	CDisplayLock  cLock(this);

	AdjustToImageSize(TRUE);
}

BOOL CMMDView::GetPrintProperties(CMMDLayout &cLayout, CMetaFileDC &cMetaDC) CONST
{
	CMMDView  *pView;
	CClientDC  cDC(NULL);
	CDisplayLock  cLock(this);

	if (GetLayout(cLayout))
	{
		if (cMetaDC.CreateEnhanced(&cDC, (LPCTSTR)NULL, (LPCRECT)NULL, (LPCTSTR)NULL))
		{
			for (cMetaDC.SetAttribDC(cDC.GetSafeHdc()); (pView = (CMMDView *) this); )
			{
				if (pView->DrawImage(&cMetaDC)) return TRUE;
				break;
			}
			DeleteEnhMetaFile(cMetaDC.CloseEnhanced());
		}
	}
	return FALSE;
}

CMMDDocument *CMMDView::GetDocument() CONST
{
	return m_pDocument;
}

CMMDWnd *CMMDView::GetParent() CONST
{
	return((CMMDWnd *)m_pParentWnd);
}

BOOL CMMDView::InstallMimicsCtrlInterface()
{
	if (SUCCEEDED(CoGetClassObject(CLSID_CEnumMimicsCtrls, CLSCTX_INPROC, NULL, IID_IClassFactory, (LPVOID *)&m_pIClassFactory)))
	{
		if (SUCCEEDED(m_pIClassFactory->CreateInstance(NULL, IID_IUnknown, (LPVOID *)&m_pIUnknown)))
		{
			if (SUCCEEDED(m_pIUnknown->QueryInterface(IID_IEnumMimicsCtrls, (LPVOID *)&m_pIEnumMimicsCtrls))) return TRUE;
			m_pIUnknown->Release();
			m_pIUnknown = (IUnknown *)NULL;
		}
		m_pIClassFactory->Release();
		m_pIClassFactory = (IClassFactory *)NULL;
	}
	return FALSE;
}

VOID CMMDView::DestroyMimicsCtrlInterface()
{
	if (m_pIEnumMimicsCtrls != (IEnumMimicsCtrls *)NULL)
	{
		m_pIEnumMimicsCtrls->Release();
		m_pIEnumMimicsCtrls = (IEnumMimicsCtrls *)NULL;
	}
	if (m_pIUnknown != (IUnknown *)NULL)
	{
		m_pIUnknown->Release();
		m_pIUnknown = (IUnknown *)NULL;
	}
	if (m_pIClassFactory != (IClassFactory *)NULL)
	{
		m_pIClassFactory->Release();
		m_pIClassFactory = (IClassFactory *)NULL;
	}
}

BOOL CMMDView::CreateDocument()
{
	return(((m_pDocument = new CMMDDocument)) ? TRUE : FALSE);
}

VOID CMMDView::DestroyDocument()
{
	delete m_pDocument;
	m_pDocument = (CMMDDocument *)NULL;
}

BOOL CMMDView::LoadLayoutCode(CString &szMessage)
{
	INT  nParameter;
	INT  nParameters;
	CString  szCode[2];
	CString  szProcedure;
	CString  szParameter;
	CString  szFileName[2];
	HINSTANCE  hImageCode;
	CFileFindEx  cFileFind[3];
	CStringArray  szParameters;
	CSecurityDescriptor  cSecurityDescriptor;
	BOOL(__cdecl *pInitializeParameters)(CONST CDatabaseEngine *pDatabase, CStringArray &szErrors);

	for (szFileName[0] = GetDatabase()->GetFileName(), szFileName[1] = GetDatabase()->GetUpdateFileName(); (cFileFind[0].FindFile(szFileName[0]) || cFileFind[0].FindFile(szFileName[1])) && !cFileFind[0].FindNextFile(); )
	{
		szCode[0].Format(STRING(IDS_MIMICSDISPLAYCODE_NORMAL_FILENAME), (LPCTSTR)m_cLayout.GetName());
		szCode[1].Format(STRING(IDS_MIMICSDISPLAYCODE_UPDATE_FILENAME), (LPCTSTR)m_cLayout.GetName());
		szCode[0] = cFileFind[0].GetFilePath().Left(cFileFind[0].GetFilePath().GetLength() - cFileFind[0].GetFileName().GetLength()) + szCode[0];
		szCode[1] = cFileFind[0].GetFilePath().Left(cFileFind[0].GetFilePath().GetLength() - cFileFind[0].GetFileName().GetLength()) + szCode[1];
		if (cFileFind[1].FindFile(szCode[1]) && !cFileFind[1].FindNextFile())
		{
			CFileEx::SetAttributes(szCode[0], CFileEx::GetAttributes(szCode[0]) & ~FILE_ATTRIBUTE_READONLY);
			CFileEx::SetAttributes(szCode[1], CFileEx::GetAttributes(szCode[1]) & ~FILE_ATTRIBUTE_READONLY);
			if (CFileEx::Copy(szCode[1], szCode[0]) && cFileFind[2].FindFile(szCode[0]) && !cFileFind[2].FindNextFile())
			{
				if (cSecurityDescriptor.SetRightsOfSystem(FILE_ALL_ACCESS) && cSecurityDescriptor.SetRightsOfAdministrators(FILE_ALL_ACCESS) && (cSecurityDescriptor.SetRightsOfSystemOperators(FILE_GENERIC_READ | FILE_GENERIC_WRITE) || cSecurityDescriptor.SetRightsOfPowerUsers(FILE_GENERIC_READ | FILE_GENERIC_WRITE)) && cSecurityDescriptor.SetRightsOfAuthenticatedUsers(FILE_GENERIC_READ) && cSecurityDescriptor.SetRightsOfEveryone(FILE_GENERIC_READ))
				{
					CSecurity::SecureFile(cFileFind[2].GetFilePath(), cSecurityDescriptor);
					CFileEx::Remove(szCode[1]);
				}
				cFileFind[2].Close();
			}
			CFileEx::SetAttributes(szCode[0], CFileEx::GetAttributes(szCode[0]) | FILE_ATTRIBUTE_READONLY);
			CFileEx::SetAttributes(szCode[1], CFileEx::GetAttributes(szCode[1]) | FILE_ATTRIBUTE_READONLY);
			cFileFind[1].Close();
		}
		if (cFileFind[1].FindFile(szCode[0]) && !cFileFind[1].FindNextFile())
		{
			if ((hImageCode = (!(hImageCode = AfxLoadLibrary(cFileFind[1].GetFileName()))) ? AfxLoadLibrary(szCode[0]) : hImageCode))
			{
#ifndef UNICODE
				szProcedure = STRING(IDS_EXPORTINTERFACE_INITIALIZEMIMICSDISPLAYPARAMETERS);
#else
				WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_INITIALIZEMIMICSDISPLAYPARAMETERS), -1, (LPSTR)szProcedure.GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_INITIALIZEMIMICSDISPLAYPARAMETERS))), lstrlen(STRING(IDS_EXPORTINTERFACE_INITIALIZEMIMICSDISPLAYPARAMETERS)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
				szProcedure.ReleaseBuffer();
#endif
				if ((pInitializeParameters = (BOOL(__cdecl *)(CONST CDatabaseEngine *pDatabase, CStringArray &szErrors)) GetProcAddress(hImageCode, (LPCSTR)(LPCTSTR)szProcedure)))
				{
					for (nParameter = 0, nParameters = (!(*pInitializeParameters)(GetDatabase(), szParameters)) ? (INT)szParameters.GetSize() : 0, szMessage.Format(STRING(IDS_DATABASE_MMD_INITIALIZATION_FAILURE), (LPCTSTR)m_cLayout.GetName()), szMessage = (nParameters > 0) ? (LPCTSTR)szMessage : EMPTYSTRING, m_hImageCode = hImageCode; nParameter < nParameters; nParameter++)
					{
						szParameter.Format((!nParameter) ? STRING(IDS_DATABASE_MMD_PARAMETER_FAILURE) : STRING(IDS_DATABASE_MMD_PARAMETERS_FAILURE), (LPCTSTR)szParameters.GetAt(nParameter));
						szMessage += szParameter;
					}
					cFileFind[1].Close();
					cFileFind[0].Close();
					return TRUE;
				}
				AfxFreeLibrary(hImageCode);
			}
			cFileFind[1].Close();
		}
		cFileFind[0].Close();
		szMessage.Format(STRING(IDS_DATABASE_MMD_NOCODE_FAILURE), (LPCTSTR)m_cLayout.GetName());
		return TRUE;
	}
	return FALSE;
}

VOID CMMDView::FreeLayoutCode()
{
	AfxFreeLibrary(m_hImageCode);
	m_hImageCode = (HINSTANCE)NULL;
}

BOOL CMMDView::LoadToolTipCursor()
{
	return(((m_hToolTipCursor = (HCURSOR)LoadImage(GetModuleHandle((LPCTSTR)NULL), MAKEINTRESOURCE(IDC_TOOLTIPCURSOR), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR))) ? TRUE : FALSE);
}

HCURSOR CMMDView::GetToolTipCursor() CONST
{
	return((!m_hToolTipCursor) ? (HCURSOR)(DWORD_PTR)GetClassLongPtr(GetSafeHwnd(), GCLP_HCURSOR) : m_hToolTipCursor);
}

BOOL CMMDView::FreeToolTipCursor()
{
	if (m_hToolTipCursor)
	{
		DestroyCursor(m_hToolTipCursor);
		m_hToolTipCursor = (HCURSOR)NULL;
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDView::LoadLinkTipCursor()
{
	return(((m_hLinkTipCursor = (HCURSOR)LoadImage(GetModuleHandle((LPCTSTR)NULL), MAKEINTRESOURCE(IDC_LINKTIPCURSOR), IMAGE_CURSOR, 0, 0, LR_DEFAULTCOLOR))) ? TRUE : FALSE);
}

HCURSOR CMMDView::GetLinkTipCursor() CONST
{
	return((!m_hLinkTipCursor) ? (HCURSOR)(DWORD_PTR)GetClassLongPtr(GetSafeHwnd(), GCLP_HCURSOR) : m_hLinkTipCursor);
}

BOOL CMMDView::FreeLinkTipCursor()
{
	if (m_hLinkTipCursor)
	{
		DestroyCursor(m_hLinkTipCursor);
		m_hLinkTipCursor = (HCURSOR)NULL;
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDView::DrawImage(CDC *pDC)
{
	CDC  cDC;
	CDC  *pMemDC;
	INT  nClipRgn;
	CRgn  rgClip;
	CRgn  rgView;
	CRect  rView;
	CRect  rImage;
	CRect  rUpdate;
	CRect  rItem[2];
	CSize  sizeView;
	CSize  sizeImage;
	DWORD  dwDCType;
	CBitmap  bmpImage;
	CBitmap  *pOldBitmap;
	POSITION  lPosition;
	CMimicsItem  *pItem;
	CMMDDocument  *pDocument;

	GetClientRect(rView);
	GetUpdateRect(rUpdate);
	GetImageSize(sizeImage);
	rImage.left = m_ptScroll.x + rView.left;
	rImage.top = m_ptScroll.y + rView.top;
	rImage.right = m_ptScroll.x + rView.right;
	rImage.bottom = m_ptScroll.y + rView.bottom;
	sizeView.cx = max(sizeImage.cx, rView.Width()) + 1;
	sizeView.cy = max(sizeImage.cy, rView.Height()) + 1;
	if ((dwDCType = GetObjectType(pDC->GetSafeHdc())) == OBJ_DC)
	{
		if (!cDC.CreateCompatibleDC(pDC) || !bmpImage.CreateCompatibleBitmap(pDC, sizeView.cx, sizeView.cy))
		{
			bmpImage.DeleteObject();
			cDC.DeleteDC();
			return FALSE;
		}
		if (!(pOldBitmap = cDC.SelectObject(&bmpImage)))
		{
			bmpImage.DeleteObject();
			cDC.DeleteDC();
			return FALSE;
		}
	}
	if (dwDCType == OBJ_DC || dwDCType == OBJ_ENHMETADC)
	{
		DrawBackground((pMemDC = (dwDCType == OBJ_DC) ? &cDC : pDC), 0, 0, (dwDCType == OBJ_DC) ? rImage : CRect(0, 0, sizeImage.cx, sizeImage.cy), (dwDCType == OBJ_DC) ? sizeView : sizeImage);
		if (rgClip.CreateRectRgn((dwDCType == OBJ_DC) ? max(m_nImage[0], m_ptScroll.x) : m_nImage[0], (dwDCType == OBJ_DC) ? max(m_nImage[1], m_ptScroll.y) : m_nImage[1], (dwDCType == OBJ_DC) ? min(sizeImage.cx - m_nImage[2], m_ptScroll.x + sizeImage.cx) : (sizeImage.cx - m_nImage[2]), (dwDCType == OBJ_DC) ? min(sizeImage.cy - m_nImage[3], m_ptScroll.y + sizeImage.cy) : (sizeImage.cy - m_nImage[3])) && rgView.CreateRectRgn(0, 0, 0, 0))
		{
			if ((nClipRgn = GetClipRgn(pMemDC->GetSafeHdc(), (HRGN)rgView.GetSafeHandle())) >= 0)
			{
				if (pMemDC->SelectClipRgn(&rgClip) != ERROR)
				{
					for (lPosition = ((pDocument = GetDocument())) ? pDocument->GetStartPosition() : (POSITION)NULL; lPosition; )
					{
						if ((pItem = (CMimicsItem *)pDocument->GetNextItem(lPosition)))
						{
							if (dwDCType == OBJ_ENHMETADC)
							{
								pItem->Draw(pMemDC);
								continue;
							}
							rItem[0] = pItem->GetItemPosition();
							rItem[0].NormalizeRect();
							rItem[1].SetRect(rItem[0].CenterPoint().x, rItem[0].CenterPoint().y, rItem[0].CenterPoint().x, rItem[0].CenterPoint().y);
							rItem[1].InflateRect(max((3 * rItem[0].Width()) / 4, (3 * rItem[0].Height()) / 4) + 1, max((3 * rItem[0].Width()) / 4, (3 * rItem[0].Height()) / 4) + 1);
							if (rItem[0].IntersectRect(rImage, rItem[1]))
							{
								pItem->Draw(pMemDC);
								continue;
							}
						}
					}
					pMemDC->SelectClipRgn((nClipRgn > 0) ? &rgView : (CRgn *)NULL);
					ValidateRect(rUpdate);
				}
			}
		}
		if (dwDCType == OBJ_ENHMETADC)
		{
			rgClip.DeleteObject();
			rgView.DeleteObject();
			return TRUE;
		}
		if (dwDCType == OBJ_DC)
		{
			pDC->BitBlt(m_ptScroll.x, m_ptScroll.y, rView.Width(), rView.Height(), &cDC, m_ptScroll.x, m_ptScroll.y, SRCCOPY);
			cDC.SelectObject(pOldBitmap);
			bmpImage.DeleteObject();
			rgClip.DeleteObject();
			rgView.DeleteObject();
			cDC.DeleteDC();
		}
		return TRUE;
	}
	return FALSE;
}

VOID CMMDView::DrawBackground(CDC *pDC, INT x, INT y, CONST RECT &rect, CONST SIZE &size)
{
	INT  nGridX;
	INT  nGridY;
	CPen  cGridPen;
	CPen  *pOldPen;
	CRect  rImage;

	for (rImage.IntersectRect((IsRectEmpty(&rect)) ? CRect(x, y, x + size.cx, y + size.cy) : CRect(rect), CRect(x, y, x + size.cx, y + size.cy)), nGridX = (m_bUseGrid && m_sizeGrid.cx > 0 && m_sizeGrid.cy > 0) ? ((rImage.left / m_sizeGrid.cx)*m_sizeGrid.cx) : (rImage.right + 1), pDC->FillSolidRect(rImage.left, rImage.top, rImage.Width(), rImage.Height(), m_nImageBkgnd); nGridX <= rImage.right; nGridX += m_sizeGrid.cx)
	{
		for (nGridY = (rImage.top / m_sizeGrid.cy)*m_sizeGrid.cy; nGridY <= rImage.bottom; nGridY += m_sizeGrid.cy)
		{
			if (rImage.PtInRect(CPoint(nGridX, nGridY)))
			{
				pDC->SetPixelV(nGridX, nGridY, m_nImageGrid);
				continue;
			}
		}
	}
	if (m_bUseGrid)
	{
		if (m_sizeGrid.cx < 0 && m_sizeGrid.cy < 0)
		{
			if (cGridPen.CreatePen(PS_SOLID, 0, m_nImageGrid))
			{
				if ((pOldPen = pDC->SelectObject(&cGridPen)))
				{
					for (nGridX = (rImage.left / m_sizeGrid.cx)*m_sizeGrid.cx; nGridX <= rImage.right; nGridX += abs(m_sizeGrid.cx))
					{
						if (nGridX >= rImage.left)
						{
							pDC->MoveTo(nGridX, rImage.top);
							pDC->LineTo(nGridX, rImage.bottom + 1);
						}
					}
					for (nGridY = (rImage.top / m_sizeGrid.cy)*m_sizeGrid.cy; nGridY <= rImage.bottom; nGridY += abs(m_sizeGrid.cy))
					{
						if (nGridY >= rImage.top)
						{
							pDC->MoveTo(rImage.left, nGridY);
							pDC->LineTo(rImage.right + 1, nGridY);
						}
					}
					pDC->SelectObject(pOldPen);
				}
				cGridPen.DeleteObject();
			}
		}
	}
}

VOID CMMDView::AdjustToImageSize(BOOL bResize)
{
	CSize  sizeImage;

	if (bResize)
	{
		CalcImageSize(sizeImage);
		GetParent()->AdjustToDefaultSize(sizeImage);
		GetParent()->SetWindowPos((CONST CWnd *) NULL, 0, 0, sizeImage.cx, sizeImage.cy, SWP_NOMOVE | SWP_NOZORDER);
	}
	Invalidate(FALSE);
	UpdateScrollBars();
}

VOID CMMDView::CalcImageSize(CSize &size) CONST
{
	for (size = CalcScrollSizes(); !m_sizeImage.cx && !m_sizeImage.cy; )
	{
		size.cx += GetSystemMetrics(SM_CXFRAME);
		size.cy += GetSystemMetrics(SM_CYFRAME);
		break;
	}
}

CSize CMMDView::CalcScrollSizes() CONST
{
	CRect  rView;
	CRect  rPosition;
	CSize  sizeScroll;
	POSITION  lPosition;
	CMimicsItem  *pItem;
	CMMDDocument  *pDocument;

	if ((pDocument = GetDocument()))
	{
		for (lPosition = pDocument->GetStartPosition(), rView.SetRectEmpty(); lPosition; )
		{
			if ((pItem = (CMimicsItem *)pDocument->GetNextItem(lPosition)))
			{
				rPosition = pItem->CalcItemFrameExtent();
				rView.SetRect(min(rPosition.left, rView.left), min(rPosition.top, rView.top), max(rPosition.right + 1, rView.right), max(rPosition.bottom + 1, rView.bottom));
			}
		}
		sizeScroll.cx = max((rView.right + m_nImage[2] < m_sizeImage.cx) ? (rView.right + m_nImage[2]) : rView.right, 0);
		sizeScroll.cy = max((rView.bottom + m_nImage[3] < m_sizeImage.cy) ? (rView.bottom + m_nImage[3]) : rView.bottom, 0);
		return((m_sizeImage.cx > 0 && m_sizeImage.cy > 0) ? m_sizeImage : sizeScroll);
	}
	return CSize(0, 0);
}

VOID CMMDView::UpdateScrollBars()
{
	CSize  sizeImage;

	CalcImageSize(sizeImage);
	SetImageSize(sizeImage);
	m_ptScroll = GetScrollPosition();
	Invalidate(FALSE);
	DrawImage();
}

VOID CMMDView::RecalcLayout()
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
}

void CMMDView::PostNcDestroy()
{
	m_pItems.RemoveAll();
	m_pItemsCode.RemoveAll();
	m_szItemsParameters.RemoveAll();
	CWnd::PostNcDestroy();
}

BOOL CMMDView::Lock()
{
	return((IsWindow(GetSafeHwnd())) ? (GetParent()->Lock() && GetLock()->Lock()) : GetLock()->Lock());
}

BOOL CMMDView::Unlock()
{
	return((IsWindow(GetSafeHwnd())) ? (GetLock()->Unlock() && GetParent()->Unlock()) : GetLock()->Unlock());
}

BEGIN_MESSAGE_MAP(CMMDView, CScrollView)
	//{{AFX_MSG_MAP(CMMDView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDView drawing

void CMMDView::OnDraw(CDC *pDC)
{
	DrawImage(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CMMDView message handlers

int CMMDView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CSize  sizeImage(0, 0);

	if (CWnd::OnCreate(lpCreateStruct) != -1)
	{
		if (InstallMimicsCtrlInterface() && CreateDocument())
		{
			SetImageSize(sizeImage);
			LoadToolTipCursor();
			LoadLinkTipCursor();
			return 0;
		}
	}
	return -1;
}

BOOL CMMDView::OnScrollBy(CSize sizeScroll, BOOL bDoScroll)
{
	BOOL  bScroll;

	bScroll = CScrollView::OnScrollBy(sizeScroll, bDoScroll);
	UpdateScrollBars();
	return bScroll;
}

void CMMDView::OnSize(UINT nType, int cx, int cy)
{
	UpdateScrollBars();
	CScrollView::OnSize(nType, cx, cy);
}

BOOL CMMDView::OnEraseBkgnd(CDC *pDC)
{
	UpdateWindow();
	return TRUE;
}

BOOL CMMDView::OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message)
{
	POINT  ptCursor;
	POSITION  lPosition;
	CMimicsItem  *pItem;
	CMMDDocument  *pDocument;

	GetCursorPos(&ptCursor);
	ScreenToClient(&ptCursor);
	ptCursor.x += GetScrollPos(SB_HORZ);
	ptCursor.y += GetScrollPos(SB_VERT);
	if (GetParent()->IsRetrievingData() && HIWORD(GetParent()->IsRetrievingData()))
	{
		SetCursor(LoadCursor((HINSTANCE)NULL, IDC_WAIT));
		return TRUE;
	}
	if (IsToolTipModeEnabled())
	{
		for (lPosition = ((pDocument = GetDocument())) ? pDocument->GetStopPosition() : (POSITION)NULL; lPosition; )
		{
			if ((pItem = (CMimicsItem *)pDocument->GetPreviousItem(lPosition)) && pItem->GetItemVisibility())
			{
				if (pItem->CheckPointOnItem(ptCursor))
				{
					if (!pItem->GetItemToolTipText().IsEmpty())
					{
						SetCursor(GetToolTipCursor());
						return TRUE;
					}
					break;
				}
			}
		}
	}
	for (lPosition = ((pDocument = GetDocument())) ? pDocument->GetStopPosition() : (POSITION)NULL; lPosition; )
	{
		if ((pItem = (CMimicsItem *)pDocument->GetPreviousItem(lPosition)) && pItem->GetItemVisibility())
		{
			if (pItem->CheckPointOnItem(ptCursor))
			{
				if (!pItem->GetItemLink().IsEmpty())
				{
					SetCursor(GetLinkTipCursor());
					return TRUE;
				}
				break;
			}
		}
	}
	return CScrollView::OnSetCursor(pWnd, nHitTest, message);
}

void CMMDView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	INT  nLink;
	INT  nLinks;
	UINT  nMode;
	POINT  ptCursor;
	CString  szLink;
	CString  szTitle;
	CString  szMessage;
	CMMDWnd  *pMMDWnd;
	POSITION  lPosition;
	CPtrArray  pLinks;
	CMMDLayout  cLayout;
	CMimicsItem  *pItem;
	CMMDDocument  *pDocument;
	CMMDWnd::DISPLAYINFO  sDisplayInfo;
	CHourglassCursor  cCursor;

	if (!GetParent()->IsRetrievingData() || !HIWORD(GetParent()->IsRetrievingData()))
	{
		for (lPosition = ((pDocument = GetDocument())) ? pDocument->GetStopPosition() : (POSITION)NULL, ptCursor.x = point.x + GetScrollPos(SB_HORZ), ptCursor.y = point.y + GetScrollPos(SB_VERT); lPosition; )
		{
			if ((pItem = (CMimicsItem *)pDocument->GetPreviousItem(lPosition)) && pItem->GetItemVisibility() && !pItem->GetItemLink().IsEmpty())
			{
				if (pItem->CheckPointOnItem(ptCursor) == TRUE)
				{
					if ((nMode = GetParent()->GetMode()) == DISPLAY_MODE_REALTIME)
					{
						if ((pMMDWnd = GetParent()->Find(MAKELONG(DISPLAY_TYPE_MMD, MMD_TYPE_NORMAL), nMode, pItem->GetItemLink())))
						{
							GetDisplayArea()->ActivateDisplay(pMMDWnd);
							break;
						}
					}
					if ((pMMDWnd = (CMMDWnd *)GetParent()->GetLink()))
					{
						if (pMMDWnd->GetLayout(cLayout) && cLayout.GetName() == pItem->GetItemLink())
						{
							GetDisplayArea()->ActivateDisplay(pMMDWnd);
							break;
						}
					}
					for (nLink = 0, nLinks = GetParent()->GetLinks(pLinks); nLink < nLinks; nLink++)
					{
						if ((pMMDWnd = (CMMDWnd *)pLinks.GetAt(nLink)) && pMMDWnd->GetLayout(cLayout))
						{
							if (cLayout.GetName() == pItem->GetItemLink())
							{
								GetDisplayArea()->ActivateDisplay(pMMDWnd);
								break;
							}
						}
					}
					if (nLink == nLinks)
					{
						if ((pMMDWnd = new CMMDWnd))
						{
							if (GetDatabase()->LoadMMD(pItem->GetItemLink(), cLayout))
							{
								for (szTitle.Format(STRING(IDS_WINDOW_FULLTITLE), STRING(IDS_DISPLAY_TITLE_MMD), (LPCTSTR)cLayout.GetTitle()); TRUE; )
								{
									sDisplayInfo.rWnd.left = sDisplayInfo.rWnd.top = CW_USEDEFAULT;
									sDisplayInfo.rWnd.right = sDisplayInfo.rWnd.bottom = CW_USEDEFAULT;
									sDisplayInfo.ptWnd.x = sDisplayInfo.ptWnd.y = 0;
									sDisplayInfo.nScope = DISPLAY_SCOPE_LOCAL;
									sDisplayInfo.nMode = nMode;
									sDisplayInfo.nShow = SW_HIDE;
									sDisplayInfo.bShow = TRUE;
									sDisplayInfo.nNumber = -1;
									sDisplayInfo.nOrder = -1;
									break;
								}
								if (pMMDWnd->SetLayout(cLayout, szMessage))
								{
									if (GetDisplayArea()->AddDisplay(pMMDWnd, szTitle, &sDisplayInfo, FALSE))
									{
										for (pMMDWnd->SetType(MAKELONG(DISPLAY_TYPE_MMD, MMD_TYPE_NORMAL)), pMMDWnd->AdjustToDefaultSize(), GetParent()->GetWindowText(szLink); !szLink.IsEmpty(); )
										{
											pMMDWnd->SetLink(GetParent());
											pMMDWnd->SetLinkByName(szLink);
											GetParent()->AddLink(pMMDWnd);
											break;
										}
										if (pMMDWnd->Start())
										{
											pMMDWnd->InitializeTMData(GetParent()->GetMode());
											pMMDWnd->ActivateFrame(SW_SHOWNORMAL);
											break;
										}
										pMMDWnd->DestroyWindow();
									}
									ReportEvent(SYSTEM_WARNING_MMD_OPEN_FAILURE);
									break;
								}
							}
							delete pMMDWnd;
						}
						ReportEvent(SYSTEM_WARNING_MMD_OPEN_FAILURE);
					}
					break;
				}
			}
		}
	}
	CScrollView::OnLButtonDblClk(nFlags, point);
}

void CMMDView::OnRButtonDown(UINT nFlags, CPoint point)
{
	POINT  ptCursor;
	CString  szText;
	CString  szTitle;
	POSITION  lPosition;
	CMimicsItem  *pItem;
	CMMDDocument  *pDocument;

	if (!GetParent()->IsRetrievingData() || !HIWORD(GetParent()->IsRetrievingData()))
	{
		for (lPosition = ((pDocument = (IsToolTipModeEnabled()) ? GetDocument() : (CMMDDocument *)NULL)) ? pDocument->GetStopPosition() : (POSITION)NULL, ptCursor.x = point.x + GetScrollPos(SB_HORZ), ptCursor.y = point.y + GetScrollPos(SB_VERT); lPosition; )
		{
			if ((pItem = (CMimicsItem *)pDocument->GetPreviousItem(lPosition)) && pItem->GetItemVisibility())
			{
				if (pItem->CheckPointOnItem(ptCursor))
				{
					szTitle = pItem->GetItemName();
					szText = pItem->GetItemToolTipText();
					break;
				}
			}
		}
		for (; !szTitle.IsEmpty() && !szText.IsEmpty(); )
		{
			m_wndToolTip.Create(this, point, szTitle, szText);
			break;
		}
	}
	CScrollView::OnRButtonDown(nFlags, point);
}

void CMMDView::OnRButtonUp(UINT nFlags, CPoint point)
{
	m_wndToolTip.Destroy();
	CScrollView::OnRButtonUp(nFlags, point);
}

void CMMDView::OnDestroy()
{
	FreeLayoutCode();
	FreeToolTipCursor();
	FreeLinkTipCursor();
	DestroyDocument();
	DestroyMimicsCtrlInterface();
	CScrollView::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CMMDWnd

IMPLEMENT_DYNAMIC(CMMDWnd, CDisplayWnd)

CMMDWnd::CMMDWnd() : CDisplayWnd()
{
	SetType(DISPLAY_TYPE_MMD);
	SetRetrieveMode();
	SetRetrieveSpeed();
	SetRetrieveInterval();
	SetRetrieveStartTime();
	SetRetrieveStopTime();
	SetUpdateInfo();
}

BOOL CMMDWnd::Create(CMDIFrameWnd *pParentWnd, LPCTSTR pszTitle, PDISPLAYINFO pDefaultInfo, BOOL bDefault)
{
	if (CDisplayWnd::Create(pParentWnd, (!AfxIsValidString(pszTitle)) ? STRING(IDS_DISPLAY_TITLE_MMD) : pszTitle, pDefaultInfo->rWnd, IDR_MMDFRAME))
	{
		if (SetScope(pDefaultInfo->nScope) && SetMode(pDefaultInfo->nMode) && Customize(bDefault)) return TRUE;
		DestroyWindow();
	}
	return FALSE;
}

BOOL CMMDWnd::SetLayout(LPCTSTR pszLayout, CONST SIZE &sizeImage, INT nMarginLeft, INT nMarginTop, INT nMarginRight, INT nMarginBottom, COLORREF nImageBkgnd, CONST SIZE &sizeGrid, COLORREF nImageGrid, BOOL bUseGrid)
{
	CString  szMessage;
	CMMDLayout  cLayout;

	if (LoadLayout(pszLayout, cLayout))
	{
		cLayout.SetImage(sizeImage, nMarginLeft, nMarginTop, nMarginRight, nMarginBottom, nImageBkgnd, sizeGrid, nImageGrid, bUseGrid);
		return SetLayout(cLayout, szMessage);
	}
	return FALSE;
}
BOOL CMMDWnd::SetLayout(CONST CMMDLayout &cLayout, CString &szMessage)
{
	return m_wndView.SetLayout(cLayout, szMessage);
}

BOOL CMMDWnd::GetLayout(CString &szLayout, CSize &sizeImage, INT &nMarginLeft, INT &nMarginTop, INT &nMarginRight, INT &nMarginBottom, COLORREF &nImageBkgnd, CSize &sizeGrid, COLORREF &nImageGrid, BOOL &bUseGrid) CONST
{
	CMMDLayout  cLayout;

	if (m_wndView.GetLayout(cLayout))
	{
		szLayout = cLayout.GetName();
		cLayout.GetImage(sizeImage, nMarginLeft, nMarginTop, nMarginRight, nMarginBottom, nImageBkgnd, sizeGrid, nImageGrid, bUseGrid);
		return TRUE;
	}
	return FALSE;
}
BOOL CMMDWnd::GetLayout(CMMDLayout &cLayout) CONST
{
	return m_wndView.GetLayout(cLayout);
}

BOOL CMMDWnd::EnableInvalidDataMode(BOOL bEnable)
{
	return m_wndView.EnableInvalidDataMode(bEnable);
}

BOOL CMMDWnd::IsInvalidDataModeEnabled() CONST
{
	return m_wndView.IsInvalidDataModeEnabled();
}

BOOL CMMDWnd::EnableBadDataMode(BOOL bEnable)
{
	return m_wndView.EnableBadDataMode(bEnable);
}

BOOL CMMDWnd::IsBadDataModeEnabled() CONST
{
	return m_wndView.IsBadDataModeEnabled();
}

BOOL CMMDWnd::EnableToolTipMode(BOOL bEnable)
{
	return m_wndView.EnableToolTipMode(bEnable);
}

BOOL CMMDWnd::IsToolTipModeEnabled() CONST
{
	return m_wndView.IsToolTipModeEnabled();
}

BOOL CMMDWnd::Start()
{
	if (((GetMode() == DISPLAY_MODE_REALTIME  &&  ProcessRealtimeData()) || (GetMode() == DISPLAY_MODE_HISTORY  &&  StartRetrieveData())) && StartSchedulePrintJobs())
	{
		Initialize(TRUE);
		UpdateAllPanes();
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDWnd::Prepare(BOOL bDialog)
{
	INT  nResult;

	if (bDialog)
	{
		if ((nResult = m_dlgOpen.Create(this)) == IDCANCEL || nResult <= 0) MDIDestroy();
		return((nResult == IDOK || nResult == IDCANCEL) ? TRUE : FALSE);
	}
	return TRUE;
}

BOOL CMMDWnd::Initialize(BOOL bFlag)
{
	return CDisplayWnd::Initialize(bFlag);
}
BOOL CMMDWnd::Initialize(CTMEnvironment *pTMEnvironment)
{
	return m_wndView.Initialize(pTMEnvironment);
}
BOOL CMMDWnd::Initialize(CString &szTag, CTimeTag &tTag)
{
	return m_wndView.Initialize(szTag, tTag);
}

BOOL CMMDWnd::InitializeTMData(UINT nMode)
{
	for (StopRetrieveData(); (nMode == DISPLAY_MODE_REALTIME && SetMode(DISPLAY_MODE_REALTIME) && ProcessRealtimeData()) || (nMode == DISPLAY_MODE_HISTORY && SetMode(DISPLAY_MODE_HISTORY) && StartRetrieveData()); )
	{
		UpdateBars();
		return TRUE;
	}
	return FALSE;
}
BOOL CMMDWnd::InitializeTMData(CTMParameters &pTMParameters, BOOL bBadData)
{
	CDisplayWnd  *pDisplayWnd;

	return((GetMode() == DISPLAY_MODE_HISTORY) ? (((pDisplayWnd = GetLink())) ? pDisplayWnd->InitializeTMData(pTMParameters, bBadData) : m_cRetrieveThread.InitializeTMData(pTMParameters, bBadData)) : GetTMService()->InitializeTMData(pTMParameters, bBadData));
}

BOOL CMMDWnd::Check() CONST
{
	return CheckAccountPrivilege(PRIVILEGE_MMD_USE);
}

VOID CMMDWnd::Update()
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
BOOL CMMDWnd::Update(CONST CTimeKey &tTimeKey, CTMEnvironment *pTMEnvironment, UINT nFlags)
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
			if (GetRetrieveMode() & (MMD_RETRIEVE_AUTOBACKWARD | MMD_RETRIEVE_MANUALBACKWARD)) Reset(pTMEnvironment);
			return TRUE;
		}
	}
	return FALSE;
}

VOID CMMDWnd::Reset(CTMEnvironment *pTMEnvironment)
{
	CDisplayLock  cLock(this);

	if (IsInitialized())
	{
		if (AfxIsValidAddress(pTMEnvironment, sizeof(CTMEnvironment))) pTMEnvironment->Reset();
		m_wndView.Reset(pTMEnvironment);
		SetUpdateInfo();
	}
}

BOOL CMMDWnd::Stop()
{
	Initialize(FALSE);
	StopSchedulePrintJobs();
	StopRetrieveData();
	return TRUE;
}

BOOL CMMDWnd::SaveInfo(INT nPage, INT nDisplay, LPCTSTR pszTitle, CONST PDISPLAYINFO pDisplayInfo)
{
	INT  nTop;
	INT  nLeft;
	INT  nRight;
	INT  nBottom;
	UINT  nMode;
	UINT  nSpeed;
	BOOL  bUseGrid;
	CSize  sizeGrid;
	CSize  sizeImage;
	CString  szName;
	CString  szFileName;
	COLORREF  nColor[2];
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CByteArray  nPrintInfo;
	CProfile  cProfile;

	return((CDisplayWnd::SaveInfo(nPage, nDisplay, pszTitle, pDisplayInfo) && GetLayout(szName, sizeImage, nLeft, nTop, nRight, nBottom, nColor[0], sizeGrid, nColor[1], bUseGrid) && GetRetrieveMode(nMode) && GetRetrieveSpeed(nSpeed) && GetRetrieveInterval(tInterval) && GetRetrieveStartTime(tStartTime) && GetRetrieveStopTime(tStopTime) && GetRetrieveFileName(szFileName) && GetPrintJobs(nPrintInfo) && cProfile.SetMMDLayoutName(nPage, nDisplay, szName) && cProfile.SetMMDLayoutInfo(nPage, nDisplay, sizeImage, nLeft, nTop, nRight, nBottom, nColor[0], sizeGrid, nColor[1], bUseGrid, IsInvalidDataModeEnabled(), IsBadDataModeEnabled(), IsToolTipModeEnabled()) && cProfile.SetMMDModeInfo(nPage, nDisplay, nMode, nSpeed, tInterval, tStartTime, tStopTime) && cProfile.SetMMDRetrieveFileName(nPage, nDisplay, szFileName) && cProfile.SetMMDPrintInfo(nPage, nDisplay, nPrintInfo)) ? TRUE : FALSE);
}

BOOL CMMDWnd::LoadInfo(INT nPage, INT nDisplay, CString &szTitle, PDISPLAYINFO pDisplayInfo)
{
	INT  nTop;
	INT  nLeft;
	INT  nRight;
	INT  nBottom;
	UINT  nMode;
	UINT  nSpeed;
	BOOL  bToolTip;
	BOOL  bUseGrid;
	BOOL  bBadData;
	BOOL  bInvalidData;
	CSize  sizeGrid;
	CSize  sizeImage;
	CString  szName;
	CString  szFileName;
	COLORREF  nColor[2];
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CTimeSpan  tInterval;
	CByteArray  nPrintInfo;
	CProfile  cProfile;

	return((CDisplayWnd::LoadInfo(nPage, nDisplay, szTitle, pDisplayInfo) && cProfile.GetMMDLayoutName(nPage, nDisplay, szName) && cProfile.GetMMDLayoutInfo(nPage, nDisplay, sizeImage, nLeft, nTop, nRight, nBottom, nColor[0], sizeGrid, nColor[1], bUseGrid, bInvalidData, bBadData, bToolTip) && cProfile.GetMMDModeInfo(nPage, nDisplay, nMode, nSpeed, tInterval, tStartTime, tStopTime) && cProfile.GetMMDRetrieveFileName(nPage, nDisplay, szFileName) && cProfile.GetMMDPrintInfo(nPage, nDisplay, nPrintInfo) && SetLayout(szName, sizeImage, nLeft, nTop, nRight, nBottom, nColor[0], sizeGrid, nColor[1], bUseGrid) && EnableInvalidDataMode(bInvalidData) && EnableBadDataMode(bBadData) && EnableToolTipMode(bToolTip) && SetRetrieveMode(nMode) && SetRetrieveSpeed(nSpeed) && SetRetrieveInterval(tInterval) && SetRetrieveStartTime(tStartTime) && SetRetrieveStopTime(tStopTime) && SetRetrieveFileName(szFileName) && SetPrintJobs(nPrintInfo)) ? TRUE : FALSE);
}

BOOL CMMDWnd::QueryDefaultInfo(PDISPLAYINFO pDefaultInfo) CONST
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

BOOL CMMDWnd::QueryDefaultMenu(CLocaleMenu &cMenu, CImageList &cImages, CUIntArray &nImageIDs) CONST
{
	INT  nIndex;
	INT  nCount;
	INT  iImage;
	UINT  nButtonID;
	UINT  nButtonStyle;
	CBitmap  cBitmap;
	BITMAP  sBitmap;

	for (cImages.DeleteImageList(), nImageIDs.RemoveAll(); cBitmap.LoadBitmap(IDB_MMDFRAMESMALLIMAGES) && cBitmap.GetBitmap(&sBitmap); )
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
	return cMenu.LoadMenu(IDR_MMDFRAME);
}

VOID CMMDWnd::UpdateBars()
{
	CDisplayLock  cLock(this);

	UpdateMessagePane();
	UpdateModePane();
	UpdateTypePane();
}

BOOL CMMDWnd::Print(PRINTDLG *pPrintInfo)
{
	INT  nJob;
	INT  nJobs;
	CMMDPrintJobs  pJobs;
	CMMDPrintJobInfo  *pJobInfo;
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
		if (pJobInfo->GetPrintMode() & MMD_PRINT_CLEARCOMMENTS)
		{
			pJobInfo->SetPrintMode(pJobInfo->GetPrintMode() & ~MMD_PRINT_CLEARCOMMENTS);
			pJobInfo->SetComments(EMPTYSTRING);
			SetPrintJobs(pJobs);
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDWnd::CanPrint() CONST
{
	return HasLayout();
}

BOOL CMMDWnd::ProcessRealtimeData()
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

BOOL CMMDWnd::StartRetrieveData(UINT nMode, UINT nSpeed, CONST CTimeSpan &tInterval, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime)
{
	SetRetrieveMode(nMode);
	SetRetrieveSpeed(nSpeed);
	SetRetrieveInterval(tInterval);
	SetRetrieveStartTime(tStartTime);
	SetRetrieveStopTime(tStopTime);
	return StartRetrieveData();
}
BOOL CMMDWnd::StartRetrieveData()
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
			ReportEvent(SYSTEM_WARNING_MMD_RETRIEVE_FAILURE);
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
			ReportEvent(SYSTEM_WARNING_MMD_RETRIEVE_FAILURE);
		}
	}
	return FALSE;
}

LONG CMMDWnd::IsRetrievingData() CONST
{
	LONG  bFlag;

	InterlockedExchange(&bFlag, m_bRetrieveFlag);
	return((m_cRetrieveThread.IsThreadActive()) ? bFlag : FALSE);
}

BOOL CMMDWnd::RetrieveMoreData(UINT nAction)
{
	if (IsRetrievingData())
	{
		if (nAction == MMD_RETRIEVE_STOPPED)
		{
			SetRetrieveMode(GetRetrieveMode() | nAction);
			m_cRetrieveStop.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
		if (nAction == MMD_RETRIEVE_AUTOFORWARD)
		{
			SetRetrieveMode((GetRetrieveMode() & (MMD_RETRIEVE_EXACTTIME | MMD_RETRIEVE_STOPBYTIME | MMD_RETRIEVE_STOPBYEND | MMD_RETRIEVE_STOPBYREALTIME)) | nAction);
			m_cRetrieveAutoForward.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
		if (nAction == MMD_RETRIEVE_AUTOBACKWARD)
		{
			SetRetrieveMode((GetRetrieveMode() & (MMD_RETRIEVE_EXACTTIME | MMD_RETRIEVE_STOPBYTIME | MMD_RETRIEVE_STOPBYEND | MMD_RETRIEVE_STOPBYREALTIME)) | nAction);
			m_cRetrieveAutoBackward.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
		if (nAction == MMD_RETRIEVE_MANUALFORWARD)
		{
			SetRetrieveMode((GetRetrieveMode() & (MMD_RETRIEVE_EXACTTIME | MMD_RETRIEVE_STOPBYTIME | MMD_RETRIEVE_STOPBYEND | MMD_RETRIEVE_STOPBYREALTIME)) | nAction);
			m_cRetrieveManualForward.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
		if (nAction == MMD_RETRIEVE_MANUALBACKWARD)
		{
			SetRetrieveMode((GetRetrieveMode() & (MMD_RETRIEVE_EXACTTIME | MMD_RETRIEVE_STOPBYTIME | MMD_RETRIEVE_STOPBYEND | MMD_RETRIEVE_STOPBYREALTIME)) | nAction);
			m_cRetrieveManualBackward.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
		if (nAction == MMD_RETRIEVE_PSEUDOREALTIME)
		{
			SetRetrieveMode((GetRetrieveMode() & (MMD_RETRIEVE_EXACTTIME | MMD_RETRIEVE_STOPBYTIME | MMD_RETRIEVE_STOPBYEND | MMD_RETRIEVE_STOPBYREALTIME)) | nAction);
			m_cRetrievePseudoRealtime.SetEvent();
			UpdateAllPanes();
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CMMDWnd::StopRetrieveData()
{
	return(((IsRetrievingData() && m_cRetrieveThread.Stop()) || !IsRetrievingData()) ? TRUE : FALSE);
}

BOOL CMMDWnd::SetRetrieveMode(UINT nMode)
{
	CDisplayLock  cLock(this);

	m_nRetrieveMode = nMode;
	m_bRetrieveFlag = MAKELONG((nMode) ? LOWORD(m_bRetrieveFlag) : FALSE, (nMode) ? HIWORD(m_bRetrieveFlag) : FALSE);
	return TRUE;
}

BOOL CMMDWnd::GetRetrieveMode(UINT &nMode) CONST
{
	nMode = m_nRetrieveMode;
	return TRUE;
}
UINT CMMDWnd::GetRetrieveMode() CONST
{
	return m_nRetrieveMode;
}

BOOL CMMDWnd::SetRetrieveSpeed(UINT nSpeed)
{
	m_nRetrieveSpeed = nSpeed;
	return TRUE;
}

BOOL CMMDWnd::GetRetrieveSpeed(UINT &nSpeed) CONST
{
	nSpeed = m_nRetrieveSpeed;
	return TRUE;
}
UINT CMMDWnd::GetRetrieveSpeed() CONST
{
	return m_nRetrieveSpeed;
}

BOOL CMMDWnd::SetRetrieveInterval(CONST CTimeSpan &tInterval)
{
	CDisplayLock  cLock(this);

	m_tRetrieveInterval = tInterval;
	return TRUE;
}

BOOL CMMDWnd::GetRetrieveInterval(CTimeSpan &tInterval) CONST
{
	CDisplayLock  cLock(this);

	tInterval = m_tRetrieveInterval;
	return TRUE;
}
CTimeSpan CMMDWnd::GetRetrieveInterval() CONST
{
	CDisplayLock  cLock(this);

	return m_tRetrieveInterval;
}

BOOL CMMDWnd::SetRetrieveStartTime(CONST CTimeKey &tStartTime)
{
	CDisplayLock  cLock(this);

	m_tRetrieveStartTime = tStartTime;
	return TRUE;
}

BOOL CMMDWnd::GetRetrieveStartTime(CTimeKey &tStartTime) CONST
{
	CDisplayLock  cLock(this);

	tStartTime = m_tRetrieveStartTime;
	return TRUE;
}
CTimeKey CMMDWnd::GetRetrieveStartTime() CONST
{
	CDisplayLock  cLock(this);

	return m_tRetrieveStartTime;
}

BOOL CMMDWnd::SetRetrieveStopTime(CONST CTimeKey &tStopTime)
{
	CDisplayLock  cLock(this);

	m_tRetrieveStopTime = tStopTime;
	return TRUE;
}

BOOL CMMDWnd::GetRetrieveStopTime(CTimeKey &tStopTime) CONST
{
	CDisplayLock  cLock(this);

	tStopTime = m_tRetrieveStopTime;
	return TRUE;
}
CTimeKey CMMDWnd::GetRetrieveStopTime() CONST
{
	CDisplayLock  cLock(this);

	return m_tRetrieveStopTime;
}

BOOL CMMDWnd::SetRetrieveFileName(LPCTSTR pszFileName)
{
	CDisplayLock  cLock(this);

	m_szRetrieveFileName = pszFileName;
	return TRUE;
}

BOOL CMMDWnd::GetRetrieveFileName(CString &szFileName) CONST
{
	CDisplayLock  cLock(this);

	szFileName = GetRetrieveFileName();
	return TRUE;
}
CString CMMDWnd::GetRetrieveFileName() CONST
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

BOOL CMMDWnd::SetPrintJobs(CONST CMMDPrintJobs &pPrintJobs)
{
	return m_cPrintThread.SetPrintJobs(pPrintJobs);
}

BOOL CMMDWnd::GetPrintJobs(CMMDPrintJobs &pPrintJobs) CONST
{
	return m_cPrintThread.GetPrintJobs(pPrintJobs);
}

BOOL CMMDWnd::Print(CONST CMMDPrintJobInfo *pJobInfo, PRINTDLG *pPrintInfo)
{
	CDC  cDC;
	UINT  nMode;
	UINT  nTMUnit;
	BOOL  bMetric;
	BOOL  bQuality;
	RECT  rtMargin[2];
	SIZE  ptPaperSize;
	HANDLE  hDevNames;
	HANDLE  hDevMode;
	CString  szTMUnit;
	CTimeTag  tTMUnit;
	DEVMODE  *pDevMode[2];
	DEVNAMES  *pDevNames[2];
	CMMDLayout  cLayout;
	CMetaFileDC  cMetaDC;
	CPrintProfiles  cPrintProfiles;
	CPrintProfileInfo  *pPrintProfileInfo;

	if ((pPrintProfileInfo = (GetPrintProfiles(cPrintProfiles)) ? cPrintProfiles.GetAt(cPrintProfiles.Find(pJobInfo->GetProfile())) : (CPrintProfileInfo *)NULL) && pPrintProfileInfo->GetPaperInfo(ptPaperSize, rtMargin[0], rtMargin[1], bMetric))
	{
		if (GetPrintProperties(pJobInfo, cLayout, nMode, szTMUnit, tTMUnit, nTMUnit, bQuality, cMetaDC))
		{
			if (!AfxIsValidAddress(pPrintInfo, sizeof(PRINTDLG)))
			{
				if (CreatePrinterDC(pPrintProfileInfo, cDC))
				{
					if (PrintJob(cDC, pJobInfo, pPrintProfileInfo->GetPrinterName(), 0, 0, rtMargin[0], bMetric, cLayout, nMode, szTMUnit, tTMUnit, nTMUnit, bQuality, cMetaDC))
					{
						cDC.DeleteDC();
						return TRUE;
					}
					cDC.DeleteDC();
				}
				DeleteEnhMetaFile(cMetaDC.CloseEnhanced());
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
									for (CopyMemory(pDevNames[1], pDevNames[0], GlobalSize(pPrintInfo->hDevNames)), CopyMemory(pDevMode[1], pDevMode[0], GlobalSize(pPrintInfo->hDevMode)), pDevMode[1]->dmColor = (pJobInfo->GetPrintMode() & MMD_PRINT_NOCOLORS) ? DMCOLOR_MONOCHROME : pDevMode[0]->dmColor; CreatePrinterDC(hDevNames, hDevMode, cDC); )
									{
										if (PrintJob(cDC, pJobInfo, (LPCTSTR)pDevMode[0]->dmDeviceName, pPrintInfo->nFromPage, pPrintInfo->nToPage, rtMargin[0], bMetric, cLayout, nMode, szTMUnit, tTMUnit, nTMUnit, bQuality, cMetaDC))
										{
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
			DeleteEnhMetaFile(cMetaDC.CloseEnhanced());
		}
	}
	return FALSE;
}

CMMDWnd *CMMDWnd::Find(INT nType, UINT nMode, LPCTSTR pszName) CONST
{
	INT  nDisplay;
	INT  nDisplays;
	CMMDWnd  *pMMDWnd;
	CMMDLayout  cLayout;
	CDisplayWnd  *pDisplayWnd;
	CPtrArray  pDisplays;

	for (nDisplay = 0, nDisplays = GetDisplayArea()->EnumDisplays(pDisplays), pMMDWnd = (CMMDWnd *)NULL; nDisplay < nDisplays; nDisplay++)
	{
		if ((pDisplayWnd = (CDisplayWnd *)pDisplays.GetAt(nDisplay)) && LOWORD(pDisplayWnd->GetType()) == DISPLAY_TYPE_MMD  &&  HIWORD(pDisplayWnd->GetType()) == HIWORD(nType) && pDisplayWnd->GetMode() == nMode)
		{
			if ((pMMDWnd = (CMMDWnd *)pDisplayWnd)->GetLayout(cLayout) && cLayout.GetName() == pszName) break;
			continue;
		}
	}
	return((nDisplay < nDisplays) ? pMMDWnd : (CMMDWnd *)NULL);
}

VOID CMMDWnd::AdjustToDefaultSize()
{
	m_wndView.AdjustToImageSize();
}
VOID CMMDWnd::AdjustToDefaultSize(CSize &size)
{
	CRect  rBar[2];
	CRect  rView[2];
	CSize  sizeBorder;

	for (GetWindowRect(rView[0]), GetClientRect(rView[1]), sizeBorder.cx = sizeBorder.cy = rView[0].Width() - rView[1].Width(); IsWindow(m_wndToolBar.GetSafeHwnd());)
	{
		m_wndToolBar.GetWindowRect(rBar[0]);
		size.cy += rBar[0].Height();
		break;
	}
	if (IsWindow(m_wndStatusBar.GetSafeHwnd()))
	{
		m_wndStatusBar.GetWindowRect(rBar[1]);
		size.cy += rBar[1].Height();
	}
	size.cx += sizeBorder.cx;
	size.cy += sizeBorder.cy + GetSystemMetrics(SM_CYCAPTION);
}

VOID CMMDWnd::SetUpdateInfo()
{
	CDisplayLock  cLock(this);

	m_szTMUnit.Empty();
	m_tTMUnit = 0;
	m_nTMUnit = 0;
	m_wTMUnit = TMUNIT_DATAQUALITY_NONE;
	UpdateMessagePane();
}
VOID CMMDWnd::SetUpdateInfo(LPCTSTR pszTag, CONST CTimeTag &tTag, UINT nTag, WORD wQuality)
{
	CDisplayLock  cLock(this);

	m_szTMUnit = pszTag;
	m_tTMUnit = tTag;
	m_nTMUnit = nTag;
	m_wTMUnit = wQuality;
	UpdateMessagePane();
}

BOOL CMMDWnd::GetUpdateInfo(CString &szTag, CTimeTag &tTag, UINT &nTag, WORD &wQuality) CONST
{
	CDisplayLock  cLock(this);

	szTag = m_szTMUnit;
	tTag = m_tTMUnit;
	nTag = m_nTMUnit;
	wQuality = m_wTMUnit;
	return TRUE;
}

BOOL CMMDWnd::CreateToolBar()
{
	if (m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE) && m_wndToolBar.LoadToolBar(IDB_MMDFRAMELARGEIMAGES, 0, IDB_MMDFRAMESMALLIMAGES, TRUE))
	{
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_MMDSETTINGS), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_MMDLINKAGES), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_MMDRETRIEVALS), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_MMDRETRIEVESTOP), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_MMDRETRIEVESTEPFORWARD), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_MMDRETRIEVESTEPBACKWARD), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_MMDRETRIEVEFORWARD), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_MMDRETRIEVEBACKWARD), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_MMDRETRIEVEPSEUDOREALTIME), TBBS_DISABLED);
		m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_MMDPRINT), TBBS_DISABLED);
		DockPane(&m_wndToolBar);
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDWnd::CreateStatusBar()
{
	if (m_wndStatusBar.Create(this, CBRS_BOTTOM | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE) && m_wndStatusBar.SetIndicators(nMMDStatusBarIndicators, 1))
	{
		m_wndStatusBar.EnableToolTips();
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDWnd::CreateView()
{
	if (m_wndView.Create(this))
	{
		RecalcLayout();
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDWnd::Customize(BOOL bDefault)
{
	INT  nImage[4];
	BOOL  bUseGrid;
	CSize  sizeGrid;
	CSize  sizeImage;
	CString  szName;
	CString  szTitle;
	COLORREF  nBackgroundColor;
	COLORREF  nGridColor;
	CMMDLayout  cLayout;

	if ((!bDefault  &&  GetLayout(cLayout) && GetLayout(szName, sizeImage, nImage[0], nImage[1], nImage[2], nImage[3], nBackgroundColor, sizeGrid, nGridColor, bUseGrid) && SetLayout(szName, sizeImage, nImage[0], nImage[1], nImage[2], nImage[3], nBackgroundColor, sizeGrid, nGridColor, bUseGrid)) || bDefault)
	{
		for (szTitle.Format(STRING(IDS_WINDOW_FULLTITLE), STRING(IDS_DISPLAY_TITLE_MMD), (!cLayout.GetTitle().IsEmpty()) ? (LPCTSTR)cLayout.GetTitle() : (LPCTSTR)cLayout.GetName()); !bDefault; )
		{
			SetWindowText(szTitle);
			break;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDWnd::UpdateAllPanes()
{
	INT  nPane;
	INT  nPanes;

	for (nPane = 0, nPanes = sizeof(nMMDStatusBarIndicators) / sizeof(UINT); nPane < nPanes; nPane++)
	{
		if (m_wndStatusBar.CommandToIndex(nMMDStatusBarIndicators[nPane]) != nPane) break;
		continue;
	}
	if (nPane < nPanes)
	{
		if (m_wndStatusBar.SetIndicators(nMMDStatusBarIndicators, sizeof(nMMDStatusBarIndicators) / sizeof(UINT)))
		{
			UpdateBars();
			return TRUE;
		}
		return FALSE;
	}
	UpdateBars();
	return TRUE;
}

VOID CMMDWnd::UpdateMessagePane()
{
	UINT  nTag;
	WORD  wQuality;
	CTimeTag  tTag;
	CString  szTag;
	CString  szMessage;

	if (GetUpdateInfo(szTag, tTag, nTag, wQuality))
	{
		szMessage.Format((szTag.IsEmpty()) ? ((tTag > 0) ? STRING(IDS_MMD_STATUSBAR_FULLUPDATEMESSAGE) : ((IsRetrievingData() && HIWORD(IsRetrievingData())) ? STRING(IDS_MMD_STATUSBAR_RETRIEVEMESSAGE) : STRING(IDS_MMD_STATUSBAR_NODATAMESSAGE))) : ((nTag == (UINT)-1) ? STRING(IDS_MMD_STATUSBAR_INITUPDATEMESSAGE) : STRING(IDS_MMD_STATUSBAR_UPDATEMESSAGE)), (LPCTSTR)tTag.FormatGmt(), (LPCTSTR)szTag, nTag, ((wQuality & (TMUNIT_DATAQUALITY_GOOD | TMUNIT_SEQUENCEQUALITY_GOOD)) == (TMUNIT_DATAQUALITY_GOOD | TMUNIT_SEQUENCEQUALITY_GOOD)) ? ((wQuality & TMUNIT_TIMECORRELATION_BAD) ? (LPCTSTR)(CString(STRING(IDS_MMD_STATUSBAR_QUALITYGOOD)) + STRING(IDS_MMD_STATUSBAR_TIMECORRELATIONFLAG)) : STRING(IDS_MMD_STATUSBAR_QUALITYGOOD)) : ((wQuality & TMUNIT_TIMECORRELATION_BAD) ? (LPCTSTR)(CString(STRING(IDS_MMD_STATUSBAR_QUALITYBAD)) + STRING(IDS_MMD_STATUSBAR_TIMECORRELATIONFLAG)) : STRING(IDS_MMD_STATUSBAR_QUALITYBAD)));
		m_wndStatusBar.SetPaneText(ID_MMD_STATUSBAR_MESSAGEPANE, szMessage);
	}
}

VOID CMMDWnd::UpdateModePane()
{
	CString  szMode;
	CMMDLayout  cLayout;
	CDisplayWnd  *pDisplayWnd;

	for (szMode.Empty(); (pDisplayWnd = (CDisplayWnd *)GetLink()) && GetLayout(cLayout); )
	{
		szMode.Format(STRING(IDS_DISPLAY_MODE_LINK), STRING(IDS_DISPLAY_TITLE_MMD), (LPCTSTR)cLayout.GetName());
		break;
	}
	m_wndStatusBar.SetPaneText(ID_MMD_STATUSBAR_MODEPANE, (GetMode() == DISPLAY_MODE_HISTORY) ? (((GetRetrieveMode() & MMD_RETRIEVE_AUTOFORWARD) && !(GetRetrieveMode() & MMD_RETRIEVE_STOPPED)) ? STRING(IDS_MMD_STATUSBAR_AUTOFORWARDMODE) : (((GetRetrieveMode() & MMD_RETRIEVE_AUTOBACKWARD) && !(GetRetrieveMode() & MMD_RETRIEVE_STOPPED)) ? STRING(IDS_MMD_STATUSBAR_AUTOBACKWARDMODE) : (((GetRetrieveMode() & MMD_RETRIEVE_PSEUDOREALTIME) && !(GetRetrieveMode() & MMD_RETRIEVE_STOPPED)) ? STRING(IDS_MMD_STATUSBAR_PSEUDOREALTIMEMODE) : ((!szMode.IsEmpty()) ? (STRING(IDS_MMD_STATUSBAR_NORMALMODE) + szMode) : STRING(IDS_MMD_STATUSBAR_NORMALMODE))))) : ((!szMode.IsEmpty()) ? (STRING(IDS_DISPLAY_MODE_REALTIME) + szMode) : STRING(IDS_DISPLAY_MODE_REALTIME)));
	m_wndToolBar.EnableButton(IDM_MMDRETRIEVESTOP, (IsRetrievingData() && ((GetRetrieveMode() & MMD_RETRIEVE_AUTOFORWARD) || (GetRetrieveMode() & MMD_RETRIEVE_AUTOBACKWARD) || (GetRetrieveMode() & MMD_RETRIEVE_PSEUDOREALTIME) || HIWORD(IsRetrievingData())) && !(GetRetrieveMode() & MMD_RETRIEVE_STOPPED)) ? TRUE : FALSE);
	m_wndToolBar.EnableButton(IDM_MMDRETRIEVEFORWARD, (IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & MMD_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & MMD_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & MMD_RETRIEVE_STOPPED))) ? TRUE : FALSE);
	m_wndToolBar.EnableButton(IDM_MMDRETRIEVEBACKWARD, (IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & MMD_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & MMD_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & MMD_RETRIEVE_STOPPED))) ? TRUE : FALSE);
	m_wndToolBar.EnableButton(IDM_MMDRETRIEVESTEPFORWARD, (IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & MMD_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & MMD_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & MMD_RETRIEVE_STOPPED))) ? TRUE : FALSE);
	m_wndToolBar.EnableButton(IDM_MMDRETRIEVESTEPBACKWARD, (IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & MMD_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & MMD_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & MMD_RETRIEVE_STOPPED))) ? TRUE : FALSE);
	m_wndToolBar.EnableButton(IDM_MMDRETRIEVEPSEUDOREALTIME, (IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & MMD_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & MMD_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & MMD_RETRIEVE_STOPPED))) ? TRUE : FALSE);
}

VOID CMMDWnd::UpdateTypePane()
{
	CString  szType;
	CMMDLayout  cLayout;

	switch (HIWORD(GetType()))
	{
	case MMD_TYPE_NORMAL:
	{ if (GetLayout(cLayout))
	{
		szType.Format(STRING(IDS_MMD_STATUSBAR_TYPENORMAL), (LPCTSTR)cLayout.GetName());
		break;
	}
	szType = STRING(IDS_MMD_STATUSBAR_TYPENORMAL);
	szType = szType.Left((szType.Find(SPACE) >= 0) ? szType.Find(SPACE) : lstrlen(STRING(IDS_MMD_STATUSBAR_TYPENORMAL)));
	break;
	}
	}
	m_wndStatusBar.SetPaneText(ID_MMD_STATUSBAR_TYPEPANE, szType);
}

VOID CMMDWnd::UpdateData()
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

BOOL CMMDWnd::LoadLayout(LPCTSTR pszLayout, CMMDLayout &cLayout)
{
	return GetDatabase()->LoadMMD(pszLayout, cLayout);
}

BOOL CMMDWnd::HasLayout() CONST
{
	return m_wndView.HasImage();
}

BOOL CMMDWnd::StartSchedulePrintJobs()
{
	return IsSchedulingPrintJobs() || m_cPrintThread.Start(this);
}

BOOL CMMDWnd::IsSchedulingPrintJobs() CONST
{
	return((m_cPrintThread.IsThreadActive()) ? TRUE : FALSE);
}

BOOL CMMDWnd::StopSchedulePrintJobs()
{
	return((IsSchedulingPrintJobs() && m_cPrintThread.Stop()) ? TRUE : FALSE);
}

BOOL CMMDWnd::SetPrintJobs(CONST CByteArray &nPrintInfo)
{
	CMMDPrintJobs  pPrintJobs;

	return((pPrintJobs.Unmap(nPrintInfo)) ? SetPrintJobs(pPrintJobs) : FALSE);
}

BOOL CMMDWnd::GetPrintJobs(CByteArray &nPrintInfo) CONST
{
	CMMDPrintJobs  pPrintJobs;

	return((GetPrintJobs(pPrintJobs)) ? pPrintJobs.Map(nPrintInfo) : FALSE);
}

BOOL CMMDWnd::GetPrintProperties(CONST CMMDPrintJobInfo *pJobInfo, CMMDLayout &cLayout, UINT &nMode, CString &szTMUnit, CTimeTag &tTMUnit, UINT &nTMUnit, BOOL &bQuality, CMetaFileDC &cMetaDC) CONST
{
	WORD  wQuality;
	CDisplayLock  cLock(this);

	if (((nMode = GetMode()) == DISPLAY_MODE_REALTIME || nMode == DISPLAY_MODE_HISTORY) && GetUpdateInfo(szTMUnit, tTMUnit, nTMUnit, wQuality) && m_wndView.GetPrintProperties(cLayout, cMetaDC))
	{
		bQuality = ((wQuality & (TMUNIT_DATAQUALITY_GOOD | TMUNIT_SEQUENCEQUALITY_GOOD)) == (TMUNIT_DATAQUALITY_GOOD | TMUNIT_SEQUENCEQUALITY_GOOD)) ? TRUE : FALSE;
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDWnd::StartPrintJob(CDC &cDC)
{
	DOCINFO  sJobInfo;
	CString  szJobTitle;
	CMMDLayout  cLayout;

	for (GetLayout(cLayout), sJobInfo.fwType = 0, sJobInfo.cbSize = sizeof(DOCINFO), sJobInfo.lpszDocName = (LPTSTR)EMPTYSTRING, sJobInfo.lpszOutput = (LPCTSTR)NULL, sJobInfo.lpszDatatype = (LPCTSTR)NULL, szJobTitle.Format(STRING(IDS_PRINTJOB_DEFAULTTITLE), (LPCTSTR)GetAppTitle(), (LPCTSTR)GetAccountSpacecraftName(), (LPCTSTR)GetPrintDocSubTitle(cLayout), STRING(IDS_DISPLAY_TITLE_MMD)); szJobTitle.GetLength() >= 0; )
	{
		sJobInfo.lpszDocName = (LPTSTR)(LPCTSTR)szJobTitle;
		break;
	}
	return((cDC.StartDoc(&sJobInfo) >= 0 && cDC.StartPage() >= 0) ? TRUE : FALSE);
}

BOOL CMMDWnd::PrintJob(CDC &cDC, CONST CMMDPrintJobInfo *pJobInfo, LPCTSTR pszPrinterName, INT nFromPage, INT nToPage, CONST RECT &rtMargin, BOOL bMetric, CONST CMMDLayout &cLayout, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality, CMetaFileDC &cMetaDC)
{
	UINT  nScale;
	UINT  nAlignment;
	CRect  rArea[3];
	CSize  sizeImage[2];
	CFont  cFont[MMD_PRINTFONTS];
	double  fScale;
	CTimeKey  tPrint;
	CPtrArray  pFonts;
	HENHMETAFILE  hMetaFile;

	if (StartPrintJob(cDC))
	{
		if ((nFromPage < 1 || nToPage > 1) && nFromPage != 0 && nToPage != 0)
		{
			cDC.AbortDoc();
			return TRUE;
		}
		if (m_wndView.GetImageSize(sizeImage[0]))
		{
			if (CalcPrintDocRect(cDC, rtMargin, bMetric) && cDC.GetClipBox(rArea[0]) != ERROR  &&  CalcPrintDocTitleFont(cDC, rArea[0], cFont[MMD_PRINTFONT_TITLE]) && CalcPrintDocSubTitleFont(cDC, rArea[0], cFont[MMD_PRINTFONT_SUBTITLE]) && CalcPrintDocOperatingDetailsFont(cDC, rArea[0], cFont[MMD_PRINTFONT_OPERATINGDETAILS]) && CalcPrintDocOperatingModeFont(cDC, rArea[0], cFont[MMD_PRINTFONT_OPERATINGMODE]) && CalcPrintDocNoticeFonts(cDC, rArea[0], cFont[MMD_PRINTFONT_NOTICE], cFont[MMD_PRINTFONT_LOGO]) && CalcPrintDocFooterFont(cDC, rArea[0], cFont[MMD_PRINTFONT_FOOTER]))
			{
				for (pFonts.SetAtGrow(MMD_PRINTFONT_TITLE, &cFont[MMD_PRINTFONT_TITLE]), pFonts.SetAtGrow(MMD_PRINTFONT_SUBTITLE, &cFont[MMD_PRINTFONT_SUBTITLE]), pFonts.SetAtGrow(MMD_PRINTFONT_OPERATINGDETAILS, &cFont[MMD_PRINTFONT_OPERATINGDETAILS]), pFonts.SetAtGrow(MMD_PRINTFONT_OPERATINGMODE, &cFont[MMD_PRINTFONT_OPERATINGMODE]), pFonts.SetAtGrow(MMD_PRINTFONT_FOOTER, &cFont[MMD_PRINTFONT_FOOTER]), pFonts.SetAtGrow(MMD_PRINTFONT_NOTICE, &cFont[MMD_PRINTFONT_NOTICE]), pFonts.SetAtGrow(MMD_PRINTFONT_LOGO, &cFont[MMD_PRINTFONT_LOGO]); DrawPrintDocPage(cDC, pJobInfo, tPrint, pszPrinterName, cLayout, nMode, pszTMUnit, tTMUnit, nTMUnit, bQuality, pFonts, (rArea[1] = rArea[0]), TRUE); )
				{
					for (fScale = (sizeImage[0].cx > 0 && sizeImage[0].cy > 0) ? (((double)rArea[1].Width() / (double)sizeImage[0].cx <= (double)rArea[1].Height() / (double)sizeImage[0].cy) ? ((double)rArea[1].Width() / (double)sizeImage[0].cx) : ((double)rArea[1].Height() / (double)sizeImage[0].cy)) : 0.0, fScale = (pJobInfo->GetPrintScale(nScale)) ? (fScale*((double)nScale / 100.0)) : fScale, sizeImage[1].cx = (INT)(fScale*sizeImage[0].cx), sizeImage[1].cy = (INT)(fScale*sizeImage[0].cy), rArea[1].SetRect(rArea[0].left, ((nAlignment = pJobInfo->GetPrintMode() & MMD_PRINT_ALIGNMENT) == MMD_PRINT_ALIGNHLEFTVCENTER || nAlignment == MMD_PRINT_ALIGNHCENTERVCENTER || nAlignment == MMD_PRINT_ALIGNHRIGHTVCENTER) ? (rArea[0].top + (rArea[1].Height() - sizeImage[1].cy) / 2) : ((nAlignment == MMD_PRINT_ALIGNHLEFTVBOTTOM || nAlignment == MMD_PRINT_ALIGNHCENTERVBOTTOM || nAlignment == MMD_PRINT_ALIGNHRIGHTVBOTTOM) ? (rArea[0].bottom - (rArea[0].Height() - rArea[1].Height() + sizeImage[1].cy)) : rArea[0].top), rArea[0].right, rArea[0].bottom); DrawPrintDocPage(cDC, pJobInfo, tPrint, pszPrinterName, cLayout, nMode, pszTMUnit, tTMUnit, nTMUnit, bQuality, pFonts, rArea[1]); )
					{
						for (rArea[2].left = (nAlignment == MMD_PRINT_ALIGNHCENTERVTOP || nAlignment == MMD_PRINT_ALIGNHCENTERVCENTER || nAlignment == MMD_PRINT_ALIGNHCENTERVBOTTOM) ? (rArea[1].left + (rArea[1].Width() - sizeImage[1].cx) / 2) : ((nAlignment == MMD_PRINT_ALIGNHRIGHTVTOP || nAlignment == MMD_PRINT_ALIGNHRIGHTVCENTER || nAlignment == MMD_PRINT_ALIGNHRIGHTVBOTTOM) ? (rArea[1].right - sizeImage[1].cx) : rArea[1].left), rArea[2].top = rArea[1].top, rArea[2].right = rArea[2].left + sizeImage[1].cx, rArea[2].bottom = rArea[2].top + sizeImage[1].cy; (hMetaFile = cMetaDC.CloseEnhanced()); )
						{
							cDC.PlayMetaFile(hMetaFile, rArea[2]);
							DeleteEnhMetaFile(hMetaFile);
							EndPrintJob(cDC);
							return TRUE;
						}
						break;
					}
					break;
				}
			}
		}
		cDC.AbortDoc();
	}
	return FALSE;
}

BOOL CMMDWnd::EndPrintJob(CDC &cDC)
{
	return((cDC.EndPage() >= 0 && cDC.EndDoc() >= 0) ? TRUE : FALSE);
}

BOOL CMMDWnd::DrawPrintDocPage(CDC &cDC, CONST CMMDPrintJobInfo *pJobInfo, CONST CTimeKey &tTime, LPCTSTR pszPrinterName, CONST CMMDLayout &cLayout, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality, CONST CPtrArray &pFonts, LPRECT prClip, BOOL bCalc)
{
	UINT  nAlignment;

	return((DrawPrintDocTitle(cDC, prClip, GetPrintDocTitle(), (CFont *)pFonts.GetAt(MMD_PRINTFONT_TITLE), (nAlignment = ((nAlignment = pJobInfo->GetPrintMode() & MMD_PRINT_ALIGNMENT) >= MMD_PRINT_ALIGNHLEFTVTOP  &&  nAlignment <= MMD_PRINT_ALIGNHLEFTVBOTTOM) ? DT_LEFT : ((nAlignment >= MMD_PRINT_ALIGNHRIGHTVTOP  &&  nAlignment <= MMD_PRINT_ALIGNHRIGHTVBOTTOM) ? DT_RIGHT : DT_CENTER)), bCalc) && DrawPrintDocSubTitle(cDC, prClip, GetPrintDocSubTitle(cLayout), (CFont *)pFonts.GetAt(MMD_PRINTFONT_SUBTITLE), nAlignment, bCalc) && DrawPrintDocOperatingDetails(cDC, prClip, GetPrintDocOperatingDetails(pJobInfo, nMode, pszTMUnit, tTMUnit, nTMUnit, bQuality), (CFont *)pFonts.GetAt(MMD_PRINTFONT_OPERATINGDETAILS), nAlignment, bCalc) && DrawPrintDocOperatingMode(cDC, prClip, GetPrintDocOperatingMode(pJobInfo), (CFont *)pFonts.GetAt(MMD_PRINTFONT_OPERATINGMODE), nAlignment, bCalc) && DrawPrintDocNotice(cDC, prClip, GetPrintDocNotice(), (CFont *)pFonts.GetAt(MMD_PRINTFONT_NOTICE), (CFont *)pFonts.GetAt(MMD_PRINTFONT_LOGO), nAlignment, bCalc) && DrawPrintDocFooter(cDC, prClip, GetPrintDocFooter(tTime, pszPrinterName), (CFont *)pFonts.GetAt(MMD_PRINTFONT_FOOTER), nAlignment, bCalc)) ? TRUE : FALSE);
}

BOOL CMMDWnd::DrawPrintDocTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, UINT nAlignment, BOOL bCalc)
{
	CRect  rCalc;
	CFont  *pOldFont;

	if ((pOldFont = cDC.SelectObject(pFont)))
	{
		cDC.DrawText(pszTitle, (rCalc = CRect(0, 0, prClip->right - prClip->left, 0)), DT_CALCRECT | nAlignment | DT_NOPREFIX | DT_SINGLELINE);
		cDC.DrawText(pszTitle, (!bCalc) ? prClip : CRect(0, 0, 0, 0), nAlignment | DT_NOPREFIX | DT_SINGLELINE);
		prClip->top += rCalc.Height();
		cDC.SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDWnd::DrawPrintDocSubTitle(CDC &cDC, LPRECT prClip, LPCTSTR pszTitle, CFont *pFont, UINT nAlignment, BOOL bCalc)
{
	CRect  rCalc;
	CFont  *pOldFont;

	if ((pOldFont = cDC.SelectObject(pFont)))
	{
		cDC.DrawText(pszTitle, (rCalc = CRect(0, 0, prClip->right - prClip->left, 0)), DT_CALCRECT | nAlignment | DT_NOPREFIX | DT_SINGLELINE);
		cDC.DrawText(pszTitle, (!bCalc) ? prClip : CRect(0, 0, 0, 0), nAlignment | DT_NOPREFIX | DT_SINGLELINE);
		prClip->top += rCalc.Height();
		cDC.SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDWnd::DrawPrintDocOperatingDetails(CDC &cDC, LPRECT prClip, LPCTSTR pszComments, CFont *pFont, UINT nAlignment, BOOL bCalc)
{
	CRect  rCalc;
	CFont  *pOldFont;

	if ((pOldFont = cDC.SelectObject(pFont)))
	{
		cDC.DrawText(pszComments, (rCalc = CRect(0, 0, prClip->right - prClip->left, 0)), DT_CALCRECT | nAlignment | DT_NOPREFIX | DT_WORDBREAK);
		cDC.DrawText(pszComments, (!bCalc) ? prClip : CRect(0, 0, 0, 0), nAlignment | DT_NOPREFIX | DT_WORDBREAK);
		prClip->top += rCalc.Height();
		cDC.SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDWnd::DrawPrintDocOperatingMode(CDC &cDC, LPRECT prClip, LPCTSTR pszMode, CFont *pFont, UINT nAlignment, BOOL bCalc)
{
	CRect  rCalc;
	CFont  *pOldFont;

	if ((pOldFont = cDC.SelectObject(pFont)))
	{
		cDC.DrawText(pszMode, (rCalc = CRect(0, 0, prClip->right - prClip->left, 0)), DT_CALCRECT | nAlignment | DT_NOPREFIX | DT_WORDBREAK);
		cDC.DrawText(pszMode, (!bCalc) ? prClip : CRect(0, 0, 0, 0), nAlignment | DT_NOPREFIX | DT_WORDBREAK);
		prClip->top += rCalc.Height();
		cDC.SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDWnd::DrawPrintDocNotice(CDC &cDC, LPRECT prClip, LPCTSTR pszNotice, CFont *pFont, CFont *pLogoFont, UINT nAlignment, BOOL bCalc)
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
		cDC.TextOut((nAlignment == DT_RIGHT) ? (prClip->right - sizeNotice[0].cx - sizeNotice[1].cx - sizeNotice[2].cx) : ((nAlignment == DT_CENTER) ? (prClip->left + (prClip->right - prClip->left - sizeNotice[0].cx - sizeNotice[1].cx - sizeNotice[2].cx) / 2) : prClip->left), prClip->bottom - sizeNotice[0].cy, (!bCalc) ? (LPCTSTR)szNotice[0] : EMPTYSTRING);
		cDC.SelectObject(pOldFont);
	}
	if ((pOldFont = (sizeNotice[0].cx > 0 && sizeNotice[0].cy > 0 && sizeNotice[2].cx > 0 && sizeNotice[2].cy > 0) ? cDC.SelectObject(pLogoFont) : (CFont *)NULL))
	{
		cDC.TextOut((nAlignment == DT_RIGHT) ? (prClip->right - sizeNotice[1].cx - sizeNotice[2].cx) : ((nAlignment == DT_CENTER) ? ((prClip->left + (prClip->right - prClip->left - sizeNotice[0].cx - sizeNotice[1].cx - sizeNotice[2].cx) / 2) + sizeNotice[0].cx) : (prClip->left + sizeNotice[0].cx)), prClip->bottom - sizeNotice[2].cy, (!bCalc) ? (LPCTSTR)szNotice[2] : EMPTYSTRING);
		cDC.SelectObject(pOldFont);
	}
	if ((pOldFont = (sizeNotice[0].cx > 0 && sizeNotice[0].cy > 0 && sizeNotice[1].cx > 0 && sizeNotice[1].cy > 0) ? cDC.SelectObject(pFont) : (CFont *)NULL))
	{
		cDC.TextOut((nAlignment == DT_RIGHT) ? (prClip->right - sizeNotice[1].cx) : ((nAlignment == DT_CENTER) ? ((prClip->left + (prClip->right - prClip->left - sizeNotice[0].cx - sizeNotice[1].cx - sizeNotice[2].cx) / 2) + sizeNotice[0].cx + sizeNotice[2].cx) : (prClip->left + sizeNotice[0].cx + sizeNotice[2].cx)), prClip->bottom - sizeNotice[1].cy, (!bCalc) ? (LPCTSTR)szNotice[1] : EMPTYSTRING);
		cDC.SelectObject(pOldFont);
	}
	if (sizeNotice[0].cx > 0 && sizeNotice[0].cy > 0 && sizeNotice[2].cx > 0 && sizeNotice[2].cy > 0)
	{
		prClip->bottom -= max(sizeNotice[0].cy, sizeNotice[2].cy);
		return TRUE;
	}
	return FALSE;
}

BOOL CMMDWnd::DrawPrintDocFooter(CDC &cDC, LPRECT prClip, LPCTSTR pszFooter, CFont *pFont, UINT nAlignment, BOOL bCalc)
{
	CRect  rCalc;
	CFont  *pOldFont;
	CSize  sizeFooter;

	if ((pOldFont = cDC.SelectObject(pFont)))
	{
		sizeFooter = cDC.GetTextExtent(pszFooter);
		cDC.TextOut((nAlignment == DT_RIGHT) ? (prClip->right - sizeFooter.cx) : ((nAlignment == DT_CENTER) ? (prClip->left + (prClip->right - prClip->left - sizeFooter.cx) / 2) : prClip->left), prClip->bottom - sizeFooter.cy, (!bCalc) ? pszFooter : EMPTYSTRING);
		prClip->bottom -= 3 * sizeFooter.cy;
		cDC.SelectObject(pOldFont);
		return TRUE;
	}
	return FALSE;
}

CString CMMDWnd::GetPrintDocTitle() CONST
{
	CString  szTitle;

	szTitle.Format(STRING(IDS_MMD_PRINTDOCUMENT_TITLE), (LPCTSTR)GetAccountSpacecraftName());
	return szTitle;
}

CString CMMDWnd::GetPrintDocSubTitle(CONST CMMDLayout &cLayout) CONST
{
	return cLayout.GetTitle();
}

CString CMMDWnd::GetPrintDocOperatingDetails(CONST CMMDPrintJobInfo *pJobInfo, UINT nMode, LPCTSTR pszTMUnit, CONST CTimeTag &tTMUnit, UINT nTMUnit, BOOL bQuality) CONST
{
	CString  szMode;
	CString  szUpdate;

	szMode = (nMode == DISPLAY_MODE_REALTIME) ? STRING(IDS_DISPLAY_MODE_REALTIME) : STRING(IDS_DISPLAY_MODE_HISTORY);
	szUpdate.Format((!lstrlen(pszTMUnit)) ? ((tTMUnit > 0) ? STRING(IDS_MMD_PRINTDOCUMENT_FULLUPDATECOMMENT) : STRING(IDS_MMD_PRINTDOCUMENT_NODATACOMMENT)) : ((nTMUnit == (UINT)-1) ? STRING(IDS_MMD_PRINTDOCUMENT_INITUPDATECOMMENT) : STRING(IDS_MMD_PRINTDOCUMENT_UPDATECOMMENT)), (LPCTSTR)tTMUnit.FormatGmt(), pszTMUnit, nTMUnit, (bQuality) ? STRING(IDS_MMD_PRINTDOCUMENT_QUALITYGOOD) : STRING(IDS_MMD_PRINTDOCUMENT_QUALITYBAD));
	return((!pJobInfo->GetComments().IsEmpty()) ? (szUpdate + EOL + szMode + EOL + pJobInfo->GetComments()) : (szUpdate + EOL + szMode));
}

CString CMMDWnd::GetPrintDocOperatingMode(CONST CMMDPrintJobInfo *pJobInfo) CONST
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

	if ((nFlags = pJobInfo->GetPrintFlags()) & MMD_PRINT_ATTIME)
	{
		if (pJobInfo->GetPrintAtTime(tTime))
		{
			szInfo.Format(STRING(IDS_MMD_PRINTDOCUMENT_PRINTATTIME), (LPCTSTR)tTime.FormatGmt());
			szInfo += EOL;
		}
		if ((pJobInfo->GetPrintAtTime(tTime, tInterval) || pJobInfo->GetPrintAtTime(tTime, tInterval, nStopCount) || pJobInfo->GetPrintAtTime(tTime, tInterval, tStopTime)) && pJobInfo->GetPrintLastTime(tLastTime))
		{
			szInfo.Format(STRING(IDS_MMD_PRINTDOCUMENT_PRINTATTIME), (LPCTSTR)CTimeKey(tTime.GetTime() + ((tLastTime.GetTime() - tTime.GetTime()) / tInterval.GetTotalSeconds())*tInterval.GetTotalSeconds()).FormatGmt());
			szInfo += EOL;
		}
	}
	if (nFlags & MMD_PRINT_ATDAILYTIME)
	{
		if (pJobInfo->GetPrintAtDailyTime(tDailyTime) || pJobInfo->GetPrintAtDailyTime(tDailyTime, nStopCount) || pJobInfo->GetPrintAtDailyTime(tDailyTime, tStopTime))
		{
			szInfo.Format(STRING(IDS_MMD_PRINTDOCUMENT_PRINTATDAILYTIME), (LPCTSTR)CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime() / SECONDSPERDAY) + tDailyTime.GetTotalSeconds()).FormatGmt(STRING(IDS_TIMEKEY_TIMEFORMAT)));
			szInfo += EOL;
		}
	}
	if (nFlags & MMD_PRINT_ATEVENT)
	{
		if (pJobInfo->GetPrintAtEvent(szEvent))
		{
			szInfo.Format(STRING(IDS_MMD_PRINTDOCUMENT_PRINTATEVENT), (LPCTSTR)szEvent);
			szInfo += EOL;
		}
	}
	if (!nFlags)
	{
		szInfo = STRING(IDS_MMD_PRINTDOCUMENT_DEFAULTTIME);
		szInfo += EOL;
	}
	return szInfo;
}

CString CMMDWnd::GetPrintDocNotice() CONST
{
	CVersionInfo  cVersionInfo;

	return cVersionInfo.QueryComments();
}

CString CMMDWnd::GetPrintDocFooter(CONST CTimeKey &tTime, LPCTSTR pszPrinterName) CONST
{
	CString  szFooter;

	szFooter.Format(STRING(IDS_MMD_PRINTDOCUMENT_FOOTER), (LPCTSTR)tTime.Format(IDS_TIMEKEY_DATEFORMAT), (LPCTSTR)tTime.Format(IDS_TIMEKEY_TIMEFORMAT), pszPrinterName);
	return szFooter;
}

BOOL CMMDWnd::CalcPrintDocTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 48, (INT)((-5.3*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CMMDWnd::CalcPrintDocSubTitleFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 64, (INT)((-4.0*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CMMDWnd::CalcPrintDocOperatingDetailsFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 76, (INT)((-3.3*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CMMDWnd::CalcPrintDocOperatingModeFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 76, (INT)((-3.3*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CMMDWnd::CalcPrintDocNoticeFonts(CDC &cDC, CONST RECT &rArea, CFont &cFont, CFont &cLogoFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 96, (INT)((-2.6*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL) && cLogoFont.CreateFont(max(-(rArea.right - rArea.left) / 96, (INT)((-2.6*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, STRING(IDS_FONTFACE_COMPANYLOGO));
}

BOOL CMMDWnd::CalcPrintDocFooterFont(CDC &cDC, CONST RECT &rArea, CFont &cFont) CONST
{
	return cFont.CreateFont(max(-(rArea.right - rArea.left) / 80, (INT)((-3.0*(double)cDC.GetDeviceCaps(HORZRES)) / (double)cDC.GetDeviceCaps(HORZSIZE))), 0, 0, 0, FW_BOLD, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE, (LPCTSTR)NULL);
}

BOOL CMMDWnd::CalcPrintDocRect(CDC &cDC, CONST RECT &rtMargin, BOOL bMetric) CONST
{
	CRect  rClip;

	rClip.SetRect(0, 0, cDC.GetDeviceCaps(HORZRES), cDC.GetDeviceCaps(VERTRES));
	rClip.DeflateRect((bMetric) ? (rtMargin.left*cDC.GetDeviceCaps(HORZRES)) / (100 * cDC.GetDeviceCaps(HORZSIZE)) : (rtMargin.left*cDC.GetDeviceCaps(LOGPIXELSX)) / 1000, (bMetric) ? (rtMargin.top*cDC.GetDeviceCaps(VERTRES)) / (100 * cDC.GetDeviceCaps(VERTSIZE)) : (rtMargin.top*cDC.GetDeviceCaps(LOGPIXELSY)) / 1000, (bMetric) ? (rtMargin.right*cDC.GetDeviceCaps(HORZRES)) / (100 * cDC.GetDeviceCaps(HORZSIZE)) : (rtMargin.right*cDC.GetDeviceCaps(LOGPIXELSX)) / 1000, (bMetric) ? (rtMargin.bottom*cDC.GetDeviceCaps(VERTRES)) / (100 * cDC.GetDeviceCaps(VERTSIZE)) : (rtMargin.bottom*cDC.GetDeviceCaps(LOGPIXELSY)) / 1000);
	return((cDC.IntersectClipRect(rClip) != ERROR) ? TRUE : FALSE);
}

BEGIN_MESSAGE_MAP(CMMDWnd, CDisplayWnd)
	//{{AFX_MSG_MAP(CMMDWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_COMMAND(IDM_MMDSETTINGS, OnSettings)
	ON_COMMAND(IDM_MMDLINKAGES, OnLinkages)
	ON_COMMAND(IDM_MMDRETRIEVALS, OnRetrievals)
	ON_COMMAND(IDM_MMDRETRIEVESTOP, OnRetrieveStop)
	ON_COMMAND(IDM_MMDRETRIEVEFORWARD, OnRetrieveAutoForward)
	ON_COMMAND(IDM_MMDRETRIEVEBACKWARD, OnRetrieveAutoBackward)
	ON_COMMAND(IDM_MMDRETRIEVESTEPFORWARD, OnRetrieveManualForward)
	ON_COMMAND(IDM_MMDRETRIEVESTEPBACKWARD, OnRetrieveManualBackward)
	ON_COMMAND(IDM_MMDRETRIEVEPSEUDOREALTIME, OnRetrievePseudoRealtime)
	ON_COMMAND(IDM_MMDPRINT, OnPrint)
	ON_UPDATE_COMMAND_UI(IDM_MMDSETTINGS, OnUpdateSettings)
	ON_UPDATE_COMMAND_UI(IDM_MMDLINKAGES, OnUpdateLinkages)
	ON_UPDATE_COMMAND_UI(IDM_MMDRETRIEVALS, OnUpdateRetrievals)
	ON_UPDATE_COMMAND_UI(IDM_MMDRETRIEVESTOP, OnUpdateRetrieveStop)
	ON_UPDATE_COMMAND_UI(IDM_MMDRETRIEVEFORWARD, OnUpdateRetrieveAutoForward)
	ON_UPDATE_COMMAND_UI(IDM_MMDRETRIEVEBACKWARD, OnUpdateRetrieveAutoBackward)
	ON_UPDATE_COMMAND_UI(IDM_MMDRETRIEVESTEPFORWARD, OnUpdateRetrieveManualForward)
	ON_UPDATE_COMMAND_UI(IDM_MMDRETRIEVESTEPBACKWARD, OnUpdateRetrieveManualBackward)
	ON_UPDATE_COMMAND_UI(IDM_MMDRETRIEVEPSEUDOREALTIME, OnUpdateRetrievePseudoRealtime)
	ON_UPDATE_COMMAND_UI(IDM_MMDPRINT, OnUpdatePrint)
	ON_UPDATE_COMMAND_UI(ID_MMD_STATUSBAR_MESSAGEPANE, OnUpdateStatusBarMessagePane)
	ON_UPDATE_COMMAND_UI(ID_MMD_STATUSBAR_MODEPANE, OnUpdateStatusBarModePane)
	ON_UPDATE_COMMAND_UI(ID_MMD_STATUSBAR_TYPEPANE, OnUpdateStatusBarTypePane)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMMDWnd message handlers

int CMMDWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDisplayWnd::OnCreate(lpCreateStruct) != -1)
	{
		for (EnableDocking(CBRS_ALIGN_TOP); CreateToolBar() && CreateStatusBar() && CreateView() && LoadAccelTable(MAKEINTRESOURCE(IDR_MMDFRAME)); )
		{
			UpdateBars();
			return 0;
		}
	}
	return -1;
}

void CMMDWnd::OnSize(UINT nType, int cx, int cy)
{
	CDisplayWnd::OnSize(nType, cx, cy);
	m_wndView.RecalcLayout();
}

BOOL CMMDWnd::OnEraseBkgnd(CDC *pDC)
{
	if (!IsInitialized())
	{
		m_wndToolBar.UpdateWindow();
		m_wndStatusBar.UpdateWindow();
	}
	return TRUE;
}

BOOL CMMDWnd::OnCloseOpenDialog(UINT nCode)
{
	UINT  nMode;
	UINT  nSpeed;
	INT  nImage[4];
	BOOL  bUseGrid;
	BOOL  bToolTip;
	BOOL  bBadData;
	BOOL  bInvalidData;
	CSize  sizeGrid;
	CSize  sizeImage;
	CString  szMessage;
	CString  szFileName;
	CTimeSpan  tInterval;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	COLORREF  nImageGrid;
	COLORREF  nImageBkgnd;
	CMMDLayout  cLayout[2];
	CMMDPrintJobs  pJobs;

	if (nCode == IDOK)
	{
		for (SetMode(m_dlgOpen.GetMode()), SetType(MAKELONG(DISPLAY_TYPE_MMD, m_dlgOpen.GetType())), SetWindowText(m_dlgOpen.GetTitle()); m_dlgOpen.IsLayoutModified(); )
		{
			m_dlgOpen.GetLayout(cLayout[0]);
			m_dlgOpen.GetLayoutInvalidDataMode(bInvalidData);
			m_dlgOpen.GetLayoutBadDataMode(bBadData);
			m_dlgOpen.GetLayoutToolTipMode(bToolTip);
			if (!LoadLayout(cLayout[0].GetName(), cLayout[1])) return FALSE;
			cLayout[0].GetImage(sizeImage, nImage[0], nImage[1], nImage[2], nImage[3], nImageBkgnd, sizeGrid, nImageGrid, bUseGrid);
			cLayout[1].SetImage(sizeImage, nImage[0], nImage[1], nImage[2], nImage[3], nImageBkgnd, sizeGrid, nImageGrid, bUseGrid);
			if (!SetLayout(cLayout[1], szMessage) || !EnableInvalidDataMode(bInvalidData) || !EnableBadDataMode(bBadData) || !EnableToolTipMode(bToolTip)) return FALSE;
			ReportEvent((!szMessage.IsEmpty()) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL) : 0, szMessage);
			break;
		}
		if (!m_dlgOpen.IsLayoutModified())
		{
			m_dlgOpen.GetLayout(cLayout[0]);
			if (!LoadLayout(cLayout[0].GetName(), cLayout[1]) || !SetLayout(cLayout[1], szMessage)) return FALSE;
			ReportEvent((!szMessage.IsEmpty()) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL) : 0, szMessage);
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

BOOL CMMDWnd::OnCloseSettingsDialog(UINT nCode)
{
	BOOL  bToolTip;
	BOOL  bBadData;
	BOOL  bInvalidData;
	CString  szMessage;
	CString  szFileName;
	CMMDLayout  cLayout;
	CMMDPrintJobs  pJobs;

	if (nCode == IDOK)
	{
		if (m_dlgSettings.IsLayoutModified())
		{
			m_dlgSettings.GetLayout(cLayout);
			m_dlgSettings.GetLayoutInvalidDataMode(bInvalidData);
			m_dlgSettings.GetLayoutBadDataMode(bBadData);
			m_dlgSettings.GetLayoutToolTipMode(bToolTip);
			if (!SetLayout(cLayout, szMessage) || !EnableInvalidDataMode(bInvalidData) || !EnableBadDataMode(bBadData) || !EnableToolTipMode(bToolTip)) return FALSE;
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

BOOL CMMDWnd::OnCloseRetrieveDialog(UINT nCode)
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

void CMMDWnd::OnSettings()
{
	CHourglassCursor  cCursor;

	ReportEvent((m_dlgSettings.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMMDWnd::OnLinkages()
{
	CHourglassCursor  cCursor;

	ReportEvent((m_dlgLinkages.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMMDWnd::OnRetrievals()
{
	CHourglassCursor  cCursor;

	ReportEvent((m_dlgRetrievals.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE : SYSTEM_NOERROR);
}

void CMMDWnd::OnRetrieveStop()
{
	RetrieveMoreData(MMD_RETRIEVE_STOPPED);
}

void CMMDWnd::OnRetrieveAutoForward()
{
	RetrieveMoreData(MMD_RETRIEVE_AUTOFORWARD);
}

void CMMDWnd::OnRetrieveAutoBackward()
{
	RetrieveMoreData(MMD_RETRIEVE_AUTOBACKWARD);
}

void CMMDWnd::OnRetrieveManualForward()
{
	RetrieveMoreData(MMD_RETRIEVE_MANUALFORWARD);
}

void CMMDWnd::OnRetrieveManualBackward()
{
	RetrieveMoreData(MMD_RETRIEVE_MANUALBACKWARD);
}

void CMMDWnd::OnRetrievePseudoRealtime()
{
	RetrieveMoreData(MMD_RETRIEVE_PSEUDOREALTIME);
}

void CMMDWnd::OnPrint()
{
	CHourglassCursor  cCursor;

	ReportEvent((!Print()) ? SYSTEM_WARNING_DISPLAY_PRINT_FAILURE : SYSTEM_NOERROR);
}

void CMMDWnd::OnDestroy()
{
	CHourglassCursor  cCursor;

	Stop();
	CDisplayWnd::OnDestroy();
}

void CMMDWnd::OnUpdateSettings(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsInitialized());
	pCmdUI->SetCheck(IsWindow(m_dlgSettings.GetSafeHwnd()));
}

void CMMDWnd::OnUpdateLinkages(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(IsInitialized() && !GetLink());
	pCmdUI->SetCheck(IsWindow(m_dlgLinkages.GetSafeHwnd()));
}

void CMMDWnd::OnUpdateRetrievals(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsInitialized()) ? TRUE : FALSE);
	pCmdUI->SetCheck(IsWindow(m_dlgRetrievals.GetSafeHwnd()));
}

void CMMDWnd::OnUpdateRetrieveStop(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && ((GetRetrieveMode() & MMD_RETRIEVE_AUTOFORWARD) || (GetRetrieveMode() & MMD_RETRIEVE_AUTOBACKWARD) || (GetRetrieveMode() & MMD_RETRIEVE_PSEUDOREALTIME) || HIWORD(IsRetrievingData())) && !(GetRetrieveMode() & MMD_RETRIEVE_STOPPED)) ? TRUE : FALSE);
}

void CMMDWnd::OnUpdateRetrieveAutoForward(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & MMD_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & MMD_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & MMD_RETRIEVE_STOPPED))) ? TRUE : FALSE);
}

void CMMDWnd::OnUpdateRetrieveAutoBackward(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & MMD_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & MMD_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & MMD_RETRIEVE_STOPPED))) ? TRUE : FALSE);
}

void CMMDWnd::OnUpdateRetrieveManualForward(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & MMD_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & MMD_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & MMD_RETRIEVE_STOPPED))) ? TRUE : FALSE);
}

void CMMDWnd::OnUpdateRetrieveManualBackward(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & MMD_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & MMD_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & MMD_RETRIEVE_STOPPED))) ? TRUE : FALSE);
}

void CMMDWnd::OnUpdateRetrievePseudoRealtime(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsRetrievingData() && !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & MMD_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & MMD_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & MMD_RETRIEVE_STOPPED))) ? TRUE : FALSE);
}

void CMMDWnd::OnUpdatePrint(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((IsInitialized() && IsDefaultPrinterAvailable() && CanPrint()) ? TRUE : FALSE);
}

void CMMDWnd::OnUpdateStatusBarMessagePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CMMDWnd::OnUpdateStatusBarModePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}

void CMMDWnd::OnUpdateStatusBarTypePane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}
