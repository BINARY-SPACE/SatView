// POD.CPP : Parameter Observation Display Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the parameter
// observation display related interface.
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


static UINT BASED_CODE nPODStatusBarIndicators[] = 
{
  ID_POD_STATUSBAR_MESSAGEPANE,
  ID_POD_STATUSBAR_MODEPANE,
  ID_POD_STATUSBAR_TYPEPANE
};



/////////////////////////////////////////////////////////////////////////////
// CPODPrintJobInfo

CPODPrintJobInfo::CPODPrintJobInfo() : CObject()
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

VOID CPODPrintJobInfo::SetName(LPCTSTR pszName)
{
  m_szName = pszName;
}

CString CPODPrintJobInfo::GetName() CONST
{
  return m_szName;
}

VOID CPODPrintJobInfo::SetProfile(LPCTSTR pszProfile)
{
  m_szProfile = pszProfile;
}

CString CPODPrintJobInfo::GetProfile() CONST
{
  return m_szProfile;
}

VOID CPODPrintJobInfo::SetComments(LPCTSTR pszComments)
{
  m_szComments = pszComments;
}

CString CPODPrintJobInfo::GetComments() CONST
{
  return m_szComments;
}

BOOL CPODPrintJobInfo::SetPrintMode(UINT nMode)
{
  m_nPrintMode = nMode;
  return TRUE;
}

UINT CPODPrintJobInfo::GetPrintMode() CONST
{
  return m_nPrintMode;
}

BOOL CPODPrintJobInfo::SetPrintFlags(UINT nFlags)
{
  if (nFlags == POD_PRINT_ATTIME  ||  nFlags == POD_PRINT_ATDAILYTIME  ||  nFlags == POD_PRINT_ATEVENT  ||  !nFlags)
  { m_nPrintFlags = nFlags;
    return TRUE;
  }
  return FALSE;
}

UINT CPODPrintJobInfo::GetPrintFlags() CONST
{
  return m_nPrintFlags;
}

BOOL CPODPrintJobInfo::SetPrintBySide(UINT nCount)
{
  if ((m_nPrintMode & POD_PRINT_FIRSTSIDE) || (m_nPrintMode & POD_PRINT_LASTSIDE))
  { m_nPrintByCount = nCount;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODPrintJobInfo::GetPrintBySide(UINT &nCount) CONST
{
  if ((m_nPrintMode & POD_PRINT_FIRSTSIDE) || (m_nPrintMode & POD_PRINT_LASTSIDE))
  { nCount = m_nPrintByCount;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODPrintJobInfo::SetPrintAtTime(CONST CTimeKey &tTime)
{
  if ((m_nPrintMode & POD_PRINT_ATTIME) &&  !(m_nPrintMode & POD_PRINT_REPEATBYINTERVAL) &&  !(m_nPrintMode & POD_PRINT_REPEATSTOPBYCOUNT) &&  !(m_nPrintMode & POD_PRINT_REPEATSTOPBYTIME))
  { m_tPrintAtTime = tTime;
    m_tRepeatInterval = 0;
    m_tRepeatStopByTime[0] = 0;
    m_nRepeatStopByCount[0] = 0;
    m_tPrintLastTime[0] = 0;
    m_nPrintCount[0] = 0;
    return TRUE;
  }
  return FALSE;
}
BOOL CPODPrintJobInfo::SetPrintAtTime(CONST CTimeKey &tTime,CONST CTimeSpan &tInterval)
{
  if ((m_nPrintMode & POD_PRINT_ATTIME) && (m_nPrintMode & POD_PRINT_REPEATBYINTERVAL) &&  !(m_nPrintMode & POD_PRINT_REPEATSTOPBYCOUNT) &&  !(m_nPrintMode & POD_PRINT_REPEATSTOPBYTIME))
  { m_tPrintAtTime = tTime;
    m_tRepeatInterval = tInterval;
    m_tRepeatStopByTime[0] = 0;
    m_nRepeatStopByCount[0] = 0;
    m_tPrintLastTime[0] = 0;
    m_nPrintCount[0] = 0;
    return TRUE;
  }
  return FALSE;
}
BOOL CPODPrintJobInfo::SetPrintAtTime(CONST CTimeKey &tTime,CONST CTimeSpan &tInterval,UINT nStopCount)
{
  if ((m_nPrintMode & POD_PRINT_ATTIME) && (m_nPrintMode & POD_PRINT_REPEATBYINTERVAL) && (m_nPrintMode & POD_PRINT_REPEATSTOPBYCOUNT) &&  !(m_nPrintMode & POD_PRINT_REPEATSTOPBYTIME))
  { m_tPrintAtTime = tTime;
    m_tRepeatInterval = tInterval;
    m_nRepeatStopByCount[0] = nStopCount;
    m_tRepeatStopByTime[0] = 0;
    m_tPrintLastTime[0] = 0;
    m_nPrintCount[0] = 0;
    return TRUE;
  }
  return FALSE;
}
BOOL CPODPrintJobInfo::SetPrintAtTime(CONST CTimeKey &tTime,CONST CTimeSpan &tInterval,CONST CTimeKey &tStopTime)
{
  if ((m_nPrintMode & POD_PRINT_ATTIME) && (m_nPrintMode & POD_PRINT_REPEATBYINTERVAL) &&  !(m_nPrintMode & POD_PRINT_REPEATSTOPBYCOUNT) && (m_nPrintMode & POD_PRINT_REPEATSTOPBYTIME))
  { m_tPrintAtTime = tTime;
    m_tRepeatInterval = tInterval;
    m_tRepeatStopByTime[0] = tStopTime;
    m_nRepeatStopByCount[0] = 0;
    m_tPrintLastTime[0] = 0;
    m_nPrintCount[0] = 0;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODPrintJobInfo::GetPrintAtTime(CTimeKey &tTime) CONST
{
  if ((m_nPrintMode & POD_PRINT_ATTIME) &&  !(m_nPrintMode & POD_PRINT_REPEATBYINTERVAL) &&  !(m_nPrintMode & POD_PRINT_REPEATSTOPBYCOUNT) &&  !(m_nPrintMode & POD_PRINT_REPEATSTOPBYTIME))
  { tTime = m_tPrintAtTime;
    return TRUE;
  }
  return FALSE;
}
BOOL CPODPrintJobInfo::GetPrintAtTime(CTimeKey &tTime,CTimeSpan &tInterval) CONST
{
  if ((m_nPrintMode & POD_PRINT_ATTIME) && (m_nPrintMode & POD_PRINT_REPEATBYINTERVAL) &&  !(m_nPrintMode & POD_PRINT_REPEATSTOPBYCOUNT) &&  !(m_nPrintMode & POD_PRINT_REPEATSTOPBYTIME))
  { tTime = m_tPrintAtTime;
    tInterval = m_tRepeatInterval;
    return TRUE;
  }
  return FALSE;
}
BOOL CPODPrintJobInfo::GetPrintAtTime(CTimeKey &tTime,CTimeSpan &tInterval,UINT &nStopCount) CONST
{
  if ((m_nPrintMode & POD_PRINT_ATTIME) && (m_nPrintMode & POD_PRINT_REPEATBYINTERVAL) && (m_nPrintMode & POD_PRINT_REPEATSTOPBYCOUNT) &&  !(m_nPrintMode & POD_PRINT_REPEATSTOPBYTIME))
  { tTime = m_tPrintAtTime;
    tInterval = m_tRepeatInterval;
    nStopCount = m_nRepeatStopByCount[0];
    return TRUE;
  }
  return FALSE;
}
BOOL CPODPrintJobInfo::GetPrintAtTime(CTimeKey &tTime,CTimeSpan &tInterval,CTimeKey &tStopTime) CONST
{
  if ((m_nPrintMode & POD_PRINT_ATTIME) && (m_nPrintMode & POD_PRINT_REPEATBYINTERVAL) &&  !(m_nPrintMode & POD_PRINT_REPEATSTOPBYCOUNT) && (m_nPrintMode & POD_PRINT_REPEATSTOPBYTIME))
  { tTime = m_tPrintAtTime;
    tInterval = m_tRepeatInterval;
    tStopTime = m_tRepeatStopByTime[0];
    return TRUE;
  }
  return FALSE;
}

BOOL CPODPrintJobInfo::SetPrintAtDailyTime(CONST CTimeSpan &tTime)
{
  TIMEKEY  tTimeKey;

  if ((m_nPrintMode & POD_PRINT_ATDAILYTIME) &&  !(m_nPrintMode & POD_PRINT_DAILYREPEATSTOPBYCOUNT) &&  !(m_nPrintMode & POD_PRINT_DAILYREPEATSTOPBYTIME))
  { m_tPrintAtDailyTime = tTime;
    m_tRepeatStopByTime[1] = 0;
    m_nRepeatStopByCount[1] = 0;
    m_tPrintLastTime[1] = ((tTimeKey = CTime::GetCurrentTime().GetTime())%SECONDSPERDAY > tTime.GetTotalSeconds()) ? (SECONDSPERDAY*(tTimeKey/SECONDSPERDAY)+tTime.GetTotalSeconds()):0;
    m_nPrintCount[1] = 0;
    return TRUE;
  }
  return FALSE;
}
BOOL CPODPrintJobInfo::SetPrintAtDailyTime(CONST CTimeSpan &tTime,UINT nStopCount)
{
  TIMEKEY  tTimeKey;

  if ((m_nPrintMode & POD_PRINT_ATDAILYTIME) && (m_nPrintMode & POD_PRINT_DAILYREPEATSTOPBYCOUNT) &&  !(m_nPrintMode & POD_PRINT_DAILYREPEATSTOPBYTIME))
  { m_tPrintAtDailyTime = tTime;
    m_nRepeatStopByCount[1] = nStopCount;
    m_tRepeatStopByTime[1] = 0;
    m_tPrintLastTime[1] = ((tTimeKey = CTime::GetCurrentTime().GetTime())%SECONDSPERDAY > tTime.GetTotalSeconds()) ? (SECONDSPERDAY*(tTimeKey/SECONDSPERDAY)+tTime.GetTotalSeconds()):0;
    m_nPrintCount[1] = 0;
    return TRUE;
  }
  return FALSE;
}
BOOL CPODPrintJobInfo::SetPrintAtDailyTime(CONST CTimeSpan &tTime,CONST CTimeKey &tStopTime)
{
  TIMEKEY  tTimeKey;

  if ((m_nPrintMode & POD_PRINT_ATDAILYTIME) &&  !(m_nPrintMode & POD_PRINT_DAILYREPEATSTOPBYCOUNT) && (m_nPrintMode & POD_PRINT_DAILYREPEATSTOPBYTIME))
  { m_tPrintAtDailyTime = tTime;
    m_tRepeatStopByTime[1] = tStopTime;
    m_nRepeatStopByCount[1] = 0;
    m_tPrintLastTime[1] = ((tTimeKey = CTime::GetCurrentTime().GetTime())%SECONDSPERDAY > tTime.GetTotalSeconds()) ? (SECONDSPERDAY*(tTimeKey/SECONDSPERDAY)+tTime.GetTotalSeconds()):0;
    m_nPrintCount[1] = 0;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODPrintJobInfo::GetPrintAtDailyTime(CTimeSpan &tTime) CONST
{
  if ((m_nPrintMode & POD_PRINT_ATDAILYTIME) &&  !(m_nPrintMode & POD_PRINT_DAILYREPEATSTOPBYCOUNT) &&  !(m_nPrintMode & POD_PRINT_DAILYREPEATSTOPBYTIME))
  { tTime = m_tPrintAtDailyTime;
    return TRUE;
  }
  return FALSE;
}
BOOL CPODPrintJobInfo::GetPrintAtDailyTime(CTimeSpan &tTime,UINT &nStopCount) CONST
{
  if ((m_nPrintMode & POD_PRINT_ATDAILYTIME) && (m_nPrintMode & POD_PRINT_DAILYREPEATSTOPBYCOUNT) &&  !(m_nPrintMode & POD_PRINT_DAILYREPEATSTOPBYTIME))
  { tTime = m_tPrintAtDailyTime;
    nStopCount = m_nRepeatStopByCount[1];
    return TRUE;
  }
  return FALSE;
}
BOOL CPODPrintJobInfo::GetPrintAtDailyTime(CTimeSpan &tTime,CTimeKey &tStopTime) CONST
{
  if ((m_nPrintMode & POD_PRINT_ATDAILYTIME) &&  !(m_nPrintMode & POD_PRINT_DAILYREPEATSTOPBYCOUNT) && (m_nPrintMode & POD_PRINT_DAILYREPEATSTOPBYTIME))
  { tTime = m_tPrintAtDailyTime;
    tStopTime = m_tRepeatStopByTime[1];
    return TRUE;
  }
  return FALSE;
}

BOOL CPODPrintJobInfo::SetPrintAtEvent(LPCTSTR pszEvent)
{
  if (m_nPrintMode & POD_PRINT_ATEVENT)
  { m_szEvent = pszEvent;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODPrintJobInfo::GetPrintAtEvent(CString &szEvent) CONST
{
  if (m_nPrintMode & POD_PRINT_ATEVENT)
  { szEvent = m_szEvent;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODPrintJobInfo::SetPrintCount(UINT nCount)
{
  if (m_nPrintMode & POD_PRINT_ATTIME)
  { m_nPrintCount[0] = nCount;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODPrintJobInfo::GetPrintCount(UINT &nCount) CONST
{
  if (m_nPrintMode & POD_PRINT_ATTIME)
  { nCount = m_nPrintCount[0];
    return TRUE;
  }
  return FALSE;
}

BOOL CPODPrintJobInfo::SetPrintDailyCount(UINT nCount)
{
  if (m_nPrintMode & POD_PRINT_ATDAILYTIME)
  { m_nPrintCount[1] = nCount;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODPrintJobInfo::GetPrintDailyCount(UINT &nCount) CONST
{
  if (m_nPrintMode & POD_PRINT_ATDAILYTIME)
  { nCount = m_nPrintCount[1];
    return TRUE;
  }
  return FALSE;
}

BOOL CPODPrintJobInfo::SetPrintLastTime(CONST CTimeKey &tTime)
{
  if (m_nPrintMode & POD_PRINT_ATTIME)
  { m_tPrintLastTime[0] = tTime;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODPrintJobInfo::GetPrintLastTime(CTimeKey &tTime) CONST
{
  if (m_nPrintMode & POD_PRINT_ATTIME) 
  { tTime = m_tPrintLastTime[0];
    return TRUE;
  }
  return FALSE;
}

BOOL CPODPrintJobInfo::SetPrintLastDailyTime(CONST CTimeKey &tTime)
{
  if (m_nPrintMode & POD_PRINT_ATDAILYTIME)
  { m_tPrintLastTime[1] = tTime;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODPrintJobInfo::GetPrintLastDailyTime(CTimeKey &tTime) CONST
{
  if (m_nPrintMode & POD_PRINT_ATDAILYTIME) 
  { tTime = m_tPrintLastTime[1];
    return TRUE;
  }
  return FALSE;
}

VOID CPODPrintJobInfo::Copy(CONST CPODPrintJobInfo *pJobInfo)
{
  m_szName = pJobInfo -> m_szName;
  m_szEvent = pJobInfo -> m_szEvent;
  m_szProfile = pJobInfo -> m_szProfile;
  m_szComments = pJobInfo -> m_szComments;
  m_nPrintMode = pJobInfo -> m_nPrintMode;
  m_nPrintFlags = pJobInfo -> m_nPrintFlags;
  m_nPrintCount[0] = pJobInfo -> m_nPrintCount[0];
  m_nPrintCount[1] = pJobInfo -> m_nPrintCount[1];
  m_nPrintByCount = pJobInfo -> m_nPrintByCount;
  m_tPrintAtTime = pJobInfo -> m_tPrintAtTime;
  m_tPrintAtDailyTime = pJobInfo -> m_tPrintAtDailyTime;
  m_tPrintLastTime[0] = pJobInfo -> m_tPrintLastTime[0];
  m_tPrintLastTime[1] = pJobInfo -> m_tPrintLastTime[1];
  m_tRepeatInterval = pJobInfo -> m_tRepeatInterval;
  m_nRepeatStopByCount[0] = pJobInfo -> m_nRepeatStopByCount[0];
  m_nRepeatStopByCount[1] = pJobInfo -> m_nRepeatStopByCount[1];
  m_tRepeatStopByTime[0] = pJobInfo -> m_tRepeatStopByTime[0];
  m_tRepeatStopByTime[1] = pJobInfo -> m_tRepeatStopByTime[1];
}

BOOL CPODPrintJobInfo::Compare(CONST CPODPrintJobInfo *pJobInfo) CONST
{
  return((pJobInfo -> m_szName == m_szName  &&  pJobInfo -> m_szProfile == m_szProfile  &&  pJobInfo -> m_szComments == m_szComments  &&  pJobInfo -> m_nPrintMode == m_nPrintMode  && ((!(m_nPrintMode & POD_PRINT_FIRSTSIDE) &&  !(m_nPrintMode & POD_PRINT_LASTSIDE)) ||  pJobInfo -> m_nPrintByCount == m_nPrintByCount) && (!(m_nPrintMode & POD_PRINT_ATTIME) ||  pJobInfo -> m_tPrintAtTime == m_tPrintAtTime) && (!(m_nPrintMode & POD_PRINT_ATDAILYTIME) ||  pJobInfo -> m_tPrintAtDailyTime == m_tPrintAtDailyTime) && (!(m_nPrintMode & POD_PRINT_ATEVENT) ||  pJobInfo -> m_szEvent == m_szEvent) && (!(m_nPrintMode & POD_PRINT_REPEATBYINTERVAL) ||  pJobInfo -> m_tRepeatInterval == m_tRepeatInterval) && (!(m_nPrintMode & POD_PRINT_REPEATSTOPBYCOUNT) ||  pJobInfo -> m_nRepeatStopByCount[0] == m_nRepeatStopByCount[0]) && (!(m_nPrintMode & POD_PRINT_REPEATSTOPBYTIME) ||  pJobInfo -> m_tRepeatStopByTime[0] == m_tRepeatStopByTime[0]) && (!(m_nPrintMode & POD_PRINT_DAILYREPEATSTOPBYCOUNT) ||  pJobInfo -> m_nRepeatStopByCount[1] == m_nRepeatStopByCount[1]) && (!(m_nPrintMode & POD_PRINT_DAILYREPEATSTOPBYTIME) ||  pJobInfo -> m_tRepeatStopByTime[1] == m_tRepeatStopByTime[1])) ? TRUE:FALSE);
}

BOOL CPODPrintJobInfo::Map(CByteArray &nInfo) CONST
{
  INT  cbData;
  DATA  sData;

  sData.cbName = (m_szName.GetLength()+1)*sizeof(TCHAR);
  sData.cbEvent = (m_szEvent.GetLength()+1)*sizeof(TCHAR);
  sData.cbProfile = (m_szProfile.GetLength()+1)*sizeof(TCHAR);
  sData.cbComments = (m_szComments.GetLength()+1)*sizeof(TCHAR);
  for (nInfo.SetSize((sData.cbSize=sizeof(DATA)+sData.cbName+sData.cbProfile+sData.cbComments+sData.cbEvent)),sData.nPrintMode = m_nPrintMode,sData.nPrintCount[0] = m_nPrintCount[0],sData.nPrintCount[1] = m_nPrintCount[1],sData.nPrintByCount = m_nPrintByCount,sData.tPrintAtTime = m_tPrintAtTime.GetTime(),sData.tPrintAtDailyTime = m_tPrintAtDailyTime.GetTotalSeconds(),sData.tPrintLastTime[0] = m_tPrintLastTime[0].GetTime(),sData.tPrintLastTime[1] = m_tPrintLastTime[1].GetTime(),sData.tRepeatInterval = m_tRepeatInterval.GetTotalSeconds(),sData.nRepeatStopByCount[0] = m_nRepeatStopByCount[0],sData.nRepeatStopByCount[1] = m_nRepeatStopByCount[1],sData.tRepeatStopByTime[0] = m_tRepeatStopByTime[0].GetTime(),sData.tRepeatStopByTime[1] = m_tRepeatStopByTime[1].GetTime(); nInfo.GetSize() == sData.cbSize; )
  { CopyMemory(nInfo.GetData(),&sData,sizeof(DATA));
    CopyMemory(nInfo.GetData()+(cbData=sizeof(DATA)),(LPCTSTR) m_szName,sData.cbName);
    CopyMemory(nInfo.GetData()+(cbData=cbData+sData.cbName),(LPCTSTR) m_szProfile,sData.cbProfile);
    CopyMemory(nInfo.GetData()+(cbData=cbData+sData.cbProfile),(LPCTSTR) m_szComments,sData.cbComments);
    CopyMemory(nInfo.GetData()+(cbData=cbData+sData.cbComments),(LPCTSTR) m_szEvent,sData.cbEvent);
    return TRUE;
  }
  return FALSE;
}

BOOL CPODPrintJobInfo::Unmap(CONST CByteArray &nInfo)
{
  INT  cbData;
  DATA  sData;

  for (CopyMemory(&sData,nInfo.GetData(),(nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA):0); nInfo.GetSize() >= sizeof(DATA) &&  nInfo.GetSize() == sData.cbSize  &&  sData.cbSize == sizeof(DATA)+sData.cbName+sData.cbProfile+sData.cbComments+sData.cbEvent  &&  sData.cbName > 0  &&  sData.cbProfile > 0  &&  sData.cbComments > 0  &&  sData.cbEvent > 0; )
  { CopyMemory(m_szName.GetBufferSetLength(STRINGCHARS(sData.cbName)),nInfo.GetData()+(cbData=sizeof(DATA)),STRINGBYTES(sData.cbName));
    CopyMemory(m_szProfile.GetBufferSetLength(STRINGCHARS(sData.cbProfile)),nInfo.GetData()+(cbData=cbData+sData.cbName),STRINGBYTES(sData.cbProfile));
    CopyMemory(m_szComments.GetBufferSetLength(STRINGCHARS(sData.cbComments)),nInfo.GetData()+(cbData=cbData+sData.cbProfile),STRINGBYTES(sData.cbComments));
    CopyMemory(m_szEvent.GetBufferSetLength(STRINGCHARS(sData.cbEvent)),nInfo.GetData()+(cbData=cbData+sData.cbComments),STRINGBYTES(sData.cbEvent));
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
// CPODPrintJobs

CPODPrintJobs::CPODPrintJobs() : CPtrArray()
{
  return;
}

CPODPrintJobs::~CPODPrintJobs()
{
  RemoveAll();
}

INT CPODPrintJobs::Add(CPODPrintJobInfo *pJobInfo)
{
  return((INT) CPtrArray::Add(pJobInfo));
}

INT CPODPrintJobs::Find(LPCTSTR pszName) CONST
{
  INT  nJob;
  INT  nJobs;
  CPODPrintJobInfo  *pJobInfo;

  for (nJob = 0,nJobs = (INT) GetSize(); nJob < nJobs; nJob++)
  { if ((pJobInfo = GetAt(nJob)) &&  pJobInfo -> GetName() == pszName) break;
    continue;
  }
  return((nJob < nJobs) ? nJob:-1);
}

CPODPrintJobInfo *CPODPrintJobs::GetAt(INT nIndex) CONST
{
  return((nIndex >= 0  &&  nIndex < GetSize()) ? (CPODPrintJobInfo *) CPtrArray::GetAt(nIndex):(CPODPrintJobInfo *) NULL);
}

CPODPrintJobInfo *CPODPrintJobs::operator[](INT nIndex) CONST
{
  return((nIndex >= 0  &&  nIndex < GetSize()) ? (CPODPrintJobInfo *) CPtrArray::GetAt(nIndex):(CPODPrintJobInfo *) NULL);
}

TIMEKEY CPODPrintJobs::Schedule()
{
  INT  nJob;
  INT  nJobs;
  UINT  nJobMode;
  UINT  nJobPrintCount[2];
  TIMEKEY  tJobPrintTimeout[2];
  CTimeKey  tJobPrintTime[4];
  CTimeSpan  tJobPrintInterval;
  CTimeSpan  tJobPrintDailyTime;
  CPODPrintJobInfo  *pJobInfo[2];

  for (nJob = 0,nJobs = (INT) GetSize(); nJob < nJobs; nJob++)
  { if ((pJobInfo[0] = GetAt(nJob)) != (CPODPrintJobInfo *) NULL)
    { if (((nJobMode = pJobInfo[0] -> GetPrintMode()) & POD_PRINT_ACTIVE) && (((nJobMode & POD_PRINT_ATTIME) &&  pJobInfo[0] -> GetPrintLastTime(tJobPrintTime[1]) && (tJobPrintTime[1] > 0  ||  pJobInfo[0] -> SetPrintLastTime(tJobPrintTime[3]))) || (nJobMode & POD_PRINT_ATDAILYTIME)) &&  
        ((pJobInfo[0] -> GetPrintAtTime(tJobPrintTime[0]) &&  pJobInfo[0] -> GetPrintCount(nJobPrintCount[0]) &&  pJobInfo[0] -> GetPrintLastTime(tJobPrintTime[1]) &&  tJobPrintTime[3] >= tJobPrintTime[0] &&  tJobPrintTime[0] > tJobPrintTime[1] &&  pJobInfo[0] -> SetPrintFlags(POD_PRINT_ATTIME) &&  pJobInfo[0] -> SetPrintCount(nJobPrintCount[0]+1) &&  pJobInfo[0] -> SetPrintLastTime(tJobPrintTime[3])) ||
        (pJobInfo[0] -> GetPrintAtTime(tJobPrintTime[0],tJobPrintInterval) &&  pJobInfo[0] -> GetPrintCount(nJobPrintCount[0]) &&  pJobInfo[0] -> GetPrintLastTime(tJobPrintTime[1]) &&  tJobPrintTime[3] >= tJobPrintTime[0] && (tJobPrintTime[0] > tJobPrintTime[1] || (tJobPrintTime[1].GetTime()-tJobPrintTime[0].GetTime())/tJobPrintInterval.GetTotalSeconds() < (tJobPrintTime[3].GetTime()-tJobPrintTime[0].GetTime())/tJobPrintInterval.GetTotalSeconds()) &&  pJobInfo[0] -> SetPrintFlags(POD_PRINT_ATTIME) &&  pJobInfo[0] -> SetPrintCount(nJobPrintCount[0]+1) &&  pJobInfo[0] -> SetPrintLastTime(tJobPrintTime[3])) ||
        (pJobInfo[0] -> GetPrintAtTime(tJobPrintTime[0],tJobPrintInterval,nJobPrintCount[1]) &&  pJobInfo[0] -> GetPrintCount(nJobPrintCount[0]) &&  pJobInfo[0] -> GetPrintLastTime(tJobPrintTime[1]) &&  tJobPrintTime[3] >= tJobPrintTime[0] && (tJobPrintTime[0] > tJobPrintTime[1] || (tJobPrintTime[1].GetTime()-tJobPrintTime[0].GetTime())/tJobPrintInterval.GetTotalSeconds() < (tJobPrintTime[3].GetTime()-tJobPrintTime[0].GetTime())/tJobPrintInterval.GetTotalSeconds()) &&  nJobPrintCount[0] < nJobPrintCount[1] &&  pJobInfo[0] -> SetPrintFlags(POD_PRINT_ATTIME) &&  pJobInfo[0] -> SetPrintCount(nJobPrintCount[0]+1) &&  pJobInfo[0] -> SetPrintLastTime(tJobPrintTime[3])) ||
        (pJobInfo[0] -> GetPrintAtTime(tJobPrintTime[0],tJobPrintInterval,tJobPrintTime[2]) &&  pJobInfo[0] -> GetPrintCount(nJobPrintCount[0]) &&  pJobInfo[0] -> GetPrintLastTime(tJobPrintTime[1]) &&  tJobPrintTime[3] >= tJobPrintTime[0] && (tJobPrintTime[0] > tJobPrintTime[1] || (tJobPrintTime[1].GetTime()-tJobPrintTime[0].GetTime())/tJobPrintInterval.GetTotalSeconds() < (tJobPrintTime[3].GetTime()-tJobPrintTime[0].GetTime())/tJobPrintInterval.GetTotalSeconds()) &&  tJobPrintTime[3] <= tJobPrintTime[2] &&  pJobInfo[0] -> SetPrintFlags(POD_PRINT_ATTIME) &&  pJobInfo[0] -> SetPrintCount(nJobPrintCount[0]+1) &&  pJobInfo[0] -> SetPrintLastTime(tJobPrintTime[3])) ||
        (pJobInfo[0] -> GetPrintAtDailyTime(tJobPrintDailyTime) &&  pJobInfo[0] -> GetPrintDailyCount(nJobPrintCount[0]) &&  pJobInfo[0] -> GetPrintLastDailyTime(tJobPrintTime[1]) &&  tJobPrintTime[3].GetTime()%SECONDSPERDAY >= tJobPrintDailyTime.GetTotalSeconds() &&  tJobPrintTime[3].GetTime()/SECONDSPERDAY != tJobPrintTime[1].GetTime()/SECONDSPERDAY  &&  pJobInfo[0] -> SetPrintFlags(POD_PRINT_ATDAILYTIME) &&  pJobInfo[0] -> SetPrintDailyCount(nJobPrintCount[0]+1) &&  pJobInfo[0] -> SetPrintLastDailyTime(tJobPrintTime[3])) ||
        (pJobInfo[0] -> GetPrintAtDailyTime(tJobPrintDailyTime,nJobPrintCount[1]) &&  pJobInfo[0] -> GetPrintDailyCount(nJobPrintCount[0]) &&  pJobInfo[0] -> GetPrintLastDailyTime(tJobPrintTime[1]) &&  tJobPrintTime[3].GetTime()%SECONDSPERDAY >= tJobPrintDailyTime.GetTotalSeconds() &&  tJobPrintTime[3].GetTime()/SECONDSPERDAY != tJobPrintTime[1].GetTime()/SECONDSPERDAY  &&  nJobPrintCount[0] < nJobPrintCount[1] &&  pJobInfo[0] -> SetPrintFlags(POD_PRINT_ATDAILYTIME) &&  pJobInfo[0] -> SetPrintDailyCount(nJobPrintCount[0]+1) &&  pJobInfo[0] -> SetPrintLastDailyTime(tJobPrintTime[3])) ||
        (pJobInfo[0] -> GetPrintAtDailyTime(tJobPrintDailyTime,tJobPrintTime[2]) &&  pJobInfo[0] -> GetPrintDailyCount(nJobPrintCount[0]) &&  pJobInfo[0] -> GetPrintLastDailyTime(tJobPrintTime[1]) &&  tJobPrintTime[3].GetTime()%SECONDSPERDAY >= tJobPrintDailyTime.GetTotalSeconds() &&  tJobPrintTime[3].GetTime()/SECONDSPERDAY != tJobPrintTime[1].GetTime()/SECONDSPERDAY  &&  tJobPrintTime[3] <= tJobPrintTime[2] &&  pJobInfo[0] -> SetPrintFlags(POD_PRINT_ATDAILYTIME) &&  pJobInfo[0] -> SetPrintDailyCount(nJobPrintCount[0]+1) &&  pJobInfo[0] -> SetPrintLastDailyTime(tJobPrintTime[3]))))
      { if ((pJobInfo[1] = new CPODPrintJobInfo))
        { pJobInfo[1] -> Copy(pJobInfo[0]);
          InsertAt(0,pJobInfo[1],1);
          if (!pJobInfo[0] -> GetPrintAtTime(tJobPrintTime[0],tJobPrintInterval) &&  !pJobInfo[0] -> GetPrintAtDailyTime(tJobPrintDailyTime) &&
            (!pJobInfo[0] -> GetPrintAtTime(tJobPrintTime[0]) ||  tJobPrintTime[3] >= tJobPrintTime[0]) &&  
            (!pJobInfo[0] -> GetPrintAtTime(tJobPrintTime[0],tJobPrintInterval,nJobPrintCount[1]) ||  !pJobInfo[0] -> GetPrintCount(nJobPrintCount[0]) ||  nJobPrintCount[0] >= nJobPrintCount[1]) &&
            (!pJobInfo[0] -> GetPrintAtTime(tJobPrintTime[0],tJobPrintInterval,tJobPrintTime[2]) ||  tJobPrintTime[0].GetTime()+((tJobPrintTime[3].GetTime()-tJobPrintTime[0].GetTime())/tJobPrintInterval.GetTotalSeconds()+1)*tJobPrintInterval.GetTotalSeconds() > tJobPrintTime[2].GetTime()) &&
            (!pJobInfo[0] -> GetPrintAtDailyTime(tJobPrintDailyTime,nJobPrintCount[1]) ||  !pJobInfo[0] -> GetPrintDailyCount(nJobPrintCount[0]) ||  nJobPrintCount[0] >= nJobPrintCount[1]) &&
            (!pJobInfo[0] -> GetPrintAtDailyTime(tJobPrintDailyTime,tJobPrintTime[2]) ||  tJobPrintTime[0].GetTime()+((tJobPrintTime[3].GetTime()-tJobPrintTime[0].GetTime())/SECONDSPERDAY+1)*SECONDSPERDAY > tJobPrintTime[2].GetTime()))
          { delete pJobInfo[0];
            RemoveAt(nJob+1);
          }
          break;
        }
      }
    }
  }
  if (nJob == nJobs)
  { for (nJob = 0,tJobPrintTimeout[0] = tJobPrintTimeout[1] = -1; nJob < nJobs; nJob++)
    { tJobPrintTimeout[0] = ((pJobInfo[0] = GetAt(nJob)) -> GetPrintAtTime(tJobPrintTime[0]) &&  tJobPrintTime[3] < tJobPrintTime[0]) ? tJobPrintTime[0].GetTime():tJobPrintTimeout[1];
      tJobPrintTimeout[1] = (tJobPrintTimeout[0] > 0  && (tJobPrintTimeout[1] < 0  ||  tJobPrintTimeout[0] < tJobPrintTimeout[1])) ? tJobPrintTimeout[0]:tJobPrintTimeout[1];
      tJobPrintTimeout[0] = (pJobInfo[0] -> GetPrintAtTime(tJobPrintTime[0],tJobPrintInterval)) ? ((tJobPrintTime[3] > tJobPrintTime[0]) ? (tJobPrintTime[0].GetTime()+((tJobPrintTime[3].GetTime()-tJobPrintTime[0].GetTime())/tJobPrintInterval.GetTotalSeconds()+1)*tJobPrintInterval.GetTotalSeconds()):tJobPrintTime[0].GetTime()):tJobPrintTimeout[1];
      tJobPrintTimeout[1] = (tJobPrintTimeout[0] > 0  && (tJobPrintTimeout[1] < 0  ||  tJobPrintTimeout[0] < tJobPrintTimeout[1])) ? tJobPrintTimeout[0]:tJobPrintTimeout[1];
      tJobPrintTimeout[0] = (pJobInfo[0] -> GetPrintAtTime(tJobPrintTime[0],tJobPrintInterval,nJobPrintCount[1]) &&  pJobInfo[0] -> GetPrintCount(nJobPrintCount[0]) &&  nJobPrintCount[0] < nJobPrintCount[1]) ? ((tJobPrintTime[3] > tJobPrintTime[0]) ? (tJobPrintTime[0].GetTime()+((tJobPrintTime[3].GetTime()-tJobPrintTime[0].GetTime())/tJobPrintInterval.GetTotalSeconds()+1)*tJobPrintInterval.GetTotalSeconds()):tJobPrintTime[0].GetTime()):tJobPrintTimeout[1];
      tJobPrintTimeout[1] = (tJobPrintTimeout[0] > 0  && (tJobPrintTimeout[1] < 0  ||  tJobPrintTimeout[0] < tJobPrintTimeout[1])) ? tJobPrintTimeout[0]:tJobPrintTimeout[1];
      tJobPrintTimeout[0] = (pJobInfo[0] -> GetPrintAtTime(tJobPrintTime[0],tJobPrintInterval,tJobPrintTime[2]) && (tJobPrintTime[3] <= tJobPrintTime[0] ||  tJobPrintTime[0].GetTime()+((tJobPrintTime[3].GetTime()-tJobPrintTime[0].GetTime())/tJobPrintInterval.GetTotalSeconds()+1)*tJobPrintInterval.GetTotalSeconds() <= tJobPrintTime[2].GetTime())) ? ((tJobPrintTime[3] > tJobPrintTime[0]) ? (tJobPrintTime[0].GetTime()+((tJobPrintTime[3].GetTime()-tJobPrintTime[0].GetTime())/tJobPrintInterval.GetTotalSeconds()+1)*tJobPrintInterval.GetTotalSeconds()):tJobPrintTime[0].GetTime()):tJobPrintTimeout[1];
      tJobPrintTimeout[1] = (tJobPrintTimeout[0] > 0  && (tJobPrintTimeout[1] < 0  ||  tJobPrintTimeout[0] < tJobPrintTimeout[1])) ? tJobPrintTimeout[0]:tJobPrintTimeout[1];
      tJobPrintTimeout[0] = (pJobInfo[0] -> GetPrintAtDailyTime(tJobPrintDailyTime)) ? ((tJobPrintTime[3].GetTime()%SECONDSPERDAY >= tJobPrintDailyTime.GetTotalSeconds()) ? (SECONDSPERDAY*(tJobPrintTime[3].GetTime()/SECONDSPERDAY+1)+tJobPrintDailyTime.GetTotalSeconds()):(SECONDSPERDAY*(tJobPrintTime[3].GetTime()/SECONDSPERDAY)+tJobPrintDailyTime.GetTotalSeconds())):tJobPrintTimeout[1];
      tJobPrintTimeout[1] = (tJobPrintTimeout[0] > 0  && (tJobPrintTimeout[1] < 0  ||  tJobPrintTimeout[0] < tJobPrintTimeout[1])) ? tJobPrintTimeout[0]:tJobPrintTimeout[1];
      tJobPrintTimeout[0] = (pJobInfo[0] -> GetPrintAtDailyTime(tJobPrintDailyTime,nJobPrintCount[1]) &&  pJobInfo[0] -> GetPrintDailyCount(nJobPrintCount[0]) &&  nJobPrintCount[0] < nJobPrintCount[1]) ? ((tJobPrintTime[3].GetTime()%SECONDSPERDAY >= tJobPrintDailyTime.GetTotalSeconds()) ? (SECONDSPERDAY*(tJobPrintTime[3].GetTime()/SECONDSPERDAY+1)+tJobPrintDailyTime.GetTotalSeconds()):(SECONDSPERDAY*(tJobPrintTime[3].GetTime()/SECONDSPERDAY)+tJobPrintDailyTime.GetTotalSeconds())):tJobPrintTimeout[1];
      tJobPrintTimeout[1] = (tJobPrintTimeout[0] > 0  && (tJobPrintTimeout[1] < 0  ||  tJobPrintTimeout[0] < tJobPrintTimeout[1])) ? tJobPrintTimeout[0]:tJobPrintTimeout[1];
      tJobPrintTimeout[0] = (pJobInfo[0] -> GetPrintAtDailyTime(tJobPrintDailyTime,tJobPrintTime[2]) && ((tJobPrintTime[3].GetTime()%SECONDSPERDAY < tJobPrintDailyTime.GetTotalSeconds() &&  SECONDSPERDAY*(tJobPrintTime[3].GetTime()/SECONDSPERDAY)+tJobPrintDailyTime.GetTotalSeconds() <= tJobPrintTime[2].GetTime()) || (tJobPrintTime[3].GetTime()%SECONDSPERDAY >= tJobPrintDailyTime.GetTotalSeconds() &&  SECONDSPERDAY*(tJobPrintTime[3].GetTime()/SECONDSPERDAY+1)+tJobPrintDailyTime.GetTotalSeconds() <= tJobPrintTime[2].GetTime()))) ? ((tJobPrintTime[3].GetTime()%SECONDSPERDAY >= tJobPrintDailyTime.GetTotalSeconds()) ? (SECONDSPERDAY*(tJobPrintTime[3].GetTime()/SECONDSPERDAY+1)+tJobPrintDailyTime.GetTotalSeconds()):(SECONDSPERDAY*(tJobPrintTime[3].GetTime()/SECONDSPERDAY)+tJobPrintDailyTime.GetTotalSeconds())):tJobPrintTimeout[1];
      tJobPrintTimeout[1] = (tJobPrintTimeout[0] > 0  && (tJobPrintTimeout[1] < 0  ||  tJobPrintTimeout[0] < tJobPrintTimeout[1])) ? tJobPrintTimeout[0]:tJobPrintTimeout[1];
    }
    return((tJobPrintTimeout[1] != (TIMEKEY) -1) ? max(tJobPrintTimeout[1]-tJobPrintTime[3].GetTime(),0):-1);
  }
  return 0;
}

VOID CPODPrintJobs::RemoveAll()
{
  INT  nJob;
  INT  nJobs;

  for (nJob = 0,nJobs = (INT) GetSize(); nJob < nJobs; nJob++)
  { delete GetAt(nJob);
    continue;
  }
  CPtrArray::RemoveAll();
}

BOOL CPODPrintJobs::Copy(CONST CPODPrintJobs *pPrintJobs)
{
  INT  nJob;
  INT  nJobs;
  CPODPrintJobInfo  *pJobInfo;

  for (nJob = 0,nJobs = (INT) pPrintJobs -> GetSize(),RemoveAll(); nJob < nJobs; nJob++)
  { if ((pJobInfo = new CPODPrintJobInfo) != (CPODPrintJobInfo *) NULL)
    { pJobInfo -> Copy(pPrintJobs -> GetAt(nJob));
      InsertAt(nJob,pJobInfo,1);
      continue;
    }
    break;
  }
  return((nJob == nJobs) ? TRUE:FALSE);
}

BOOL CPODPrintJobs::Compare(CONST CPODPrintJobs *pPrintJobs) CONST
{
  INT  nJob[2];
  INT  nJobs[2];

  for (nJob[0] = 0,nJobs[0] = (INT) GetSize(),nJobs[1] = (INT) pPrintJobs -> GetSize(); nJob[0] < nJobs[0]; nJob[0]++)
  { for (nJob[1] = (nJobs[0] != nJobs[1]) ? nJobs[1]:0; nJob[1] < nJobs[1]; nJob[1]++)
    { if (pPrintJobs -> GetAt(nJob[0]) -> Compare(GetAt(nJob[1]))) break;
      continue;
    }
    if (nJob[1] == nJobs[1]) break;
  }
  return((nJob[0] == nJobs[0] &&  nJobs[0] == nJobs[1]) ? TRUE:FALSE);
}

BOOL CPODPrintJobs::Map(CByteArray &nInfo) CONST
{
  INT  nJob;
  INT  nJobs;
  CByteArray  nJobData;
  CPODPrintJobInfo  *pJobInfo;

  for (nJob = 0,nJobs = (INT) GetSize(),nInfo.RemoveAll(); nJob < nJobs; nJob++)
  { if ((pJobInfo = GetAt(nJob)) &&  pJobInfo -> Map(nJobData) &&  nInfo.Append(nJobData) >= 0) continue;
    break;
  }
  return((nJob == nJobs) ? TRUE:FALSE);
}

BOOL CPODPrintJobs::Unmap(CONST CByteArray &nInfo)
{
  INT  cbJob;
  INT  cbJobs;
  CByteArray  nJobData;
  CPODPrintJobInfo  *pJobInfo;

  for (cbJobs = 0,RemoveAll(); cbJobs < nInfo.GetSize(); cbJobs += cbJob)
  { for (CopyMemory(&cbJob,nInfo.GetData()+cbJobs,sizeof(cbJob)),nJobData.SetSize(max(min(cbJob,nInfo.GetSize()-cbJobs),0)); nJobData.GetSize() >= 0; )
    { CopyMemory(nJobData.GetData(),nInfo.GetData()+cbJobs,nJobData.GetSize());
      break;
    }
    if ((pJobInfo = new CPODPrintJobInfo))
    { if (pJobInfo -> Unmap(nJobData) &&  Add(pJobInfo) >= 0) continue;
      delete pJobInfo;
    }
    break;
  }
  if ((pJobInfo = (!GetSize()) ? new CPODPrintJobInfo:(CPODPrintJobInfo *) NULL))
  { for (pJobInfo -> SetName(STRING(IDS_PRINTJOB_DEFAULTNAME)),pJobInfo -> SetProfile(STRING(IDS_PRINTPROFILE_DEFAULTNAME)),pJobInfo -> SetPrintMode(POD_PRINT_ALL); Add(pJobInfo) >= 0; ) return TRUE;
    delete pJobInfo;
    return FALSE;
  }
  return((cbJobs == nInfo.GetSize()) ? TRUE:FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CPODSettingsLayoutPage property page

IMPLEMENT_DYNCREATE(CPODSettingsLayoutPage,CLocalePropertyPage)

CPODSettingsLayoutPage::CPODSettingsLayoutPage() : CLocalePropertyPage(CPODSettingsLayoutPage::IDD)
{
	//{{AFX_DATA_INIT(CPODSettingsLayoutPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CPODSettingsLayoutPage::Initialize()
{
  CPODOpenDialog  *pDialog;

  if (((pDialog = GetParentDialog() -> GetParentDialog()) && (pDialog -> GetLayout(m_cLayout[0]) ||  GetParentDisplay() -> GetLayout(m_cLayout[0])) && (pDialog -> GetLayoutTitleFonts(&m_fntTitle[0][0],&m_fntTitle[0][1],&m_fntTitle[0][2]) ||  GetParentDisplay() -> GetTitleFonts(&m_fntTitle[0][0],&m_fntTitle[0][1],&m_fntTitle[0][2])) && (pDialog -> GetLayoutItemsFonts(&m_fntItems[0][0],&m_fntItems[0][1],&m_fntItems[0][2]) ||  GetParentDisplay() -> GetItemsFonts(&m_fntItems[0][0],&m_fntItems[0][1],&m_fntItems[0][2]))) || (GetParentDisplay() -> GetLayout(m_cLayout[0]) &&  GetParentDisplay() -> GetTitleFonts(&m_fntTitle[0][0],&m_fntTitle[0][1],&m_fntTitle[0][2]) &&  GetParentDisplay() -> GetItemsFonts(&m_fntItems[0][0],&m_fntItems[0][1],&m_fntItems[0][2])))
  { m_bToolTips[0] = m_bToolTips[1] = (!pDialog  ||  !pDialog -> GetLayoutToolTipMode(m_bToolTips[0])) ? GetParentDisplay() -> IsToolTipModeEnabled():m_bToolTips[0];
    CopyMemory(&m_fntTitle[1][0],&m_fntTitle[0][0],sizeof(LOGFONT));
    CopyMemory(&m_fntTitle[1][1],&m_fntTitle[0][1],sizeof(LOGFONT));
    CopyMemory(&m_fntTitle[1][2],&m_fntTitle[0][2],sizeof(LOGFONT));
    CopyMemory(&m_fntItems[1][0],&m_fntItems[0][0],sizeof(LOGFONT));
    CopyMemory(&m_fntItems[1][1],&m_fntItems[0][1],sizeof(LOGFONT));
    CopyMemory(&m_fntItems[1][2],&m_fntItems[0][2],sizeof(LOGFONT));
    m_cLayout[0].SetColumns((m_cLayout[0].GetColumns() != 0) ? m_cLayout[0].GetColumns():POD_TITLEITEMS_DEFAULT);
    m_cLayout[1].Copy(&m_cLayout[0]);
    return TRUE;
  }
  return FALSE;
}

BOOL CPODSettingsLayoutPage::GetLayout(CPODLayout &cLayout) CONST
{
  return((cLayout.Copy(&m_cLayout[0])) ? Check(FALSE):FALSE);
}

BOOL CPODSettingsLayoutPage::GetTitleFonts(LPLOGFONT pDataFont,LPLOGFONT pParametersFont,LPLOGFONT pFunctionsFont) CONST
{
  CopyMemory(pDataFont,&m_fntTitle[0][0],sizeof(LOGFONT));
  CopyMemory(pParametersFont,&m_fntTitle[0][1],sizeof(LOGFONT));
  CopyMemory(pFunctionsFont,&m_fntTitle[0][2],sizeof(LOGFONT));
  return Check(FALSE);
}

BOOL CPODSettingsLayoutPage::GetItemsFonts(LPLOGFONT pDataFont,LPLOGFONT pParametersFont,LPLOGFONT pFunctionsFont) CONST
{
  CopyMemory(pDataFont,&m_fntItems[0][0],sizeof(LOGFONT));
  CopyMemory(pParametersFont,&m_fntItems[0][1],sizeof(LOGFONT));
  CopyMemory(pFunctionsFont,&m_fntItems[0][2],sizeof(LOGFONT));
  return Check(FALSE);
}

BOOL CPODSettingsLayoutPage::GetToolTipMode(BOOL &bEnable) CONST
{
  bEnable = m_bToolTips[0];
  return Check(FALSE);
}

CPODSettingsDialog *CPODSettingsLayoutPage::GetParentDialog() CONST
{
  return((CPODSettingsDialog *) CLocalePropertyPage::GetParent());
}

CPODWnd *CPODSettingsLayoutPage::GetParentDisplay() CONST
{
  return((CPODWnd *) GetParentDialog() -> GetParentDisplay());
}

BOOL CPODSettingsLayoutPage::EnumFunctions()
{
  INT  nFunction;
  INT  nFunctions;

  SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_LIST,CB_RESETCONTENT);
  for (nFunction = 0,nFunctions = MAXPODFUNCTIONS-MINPODFUNCTIONS+1; nFunction < nFunctions; nFunction++)
  { SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_LIST,CB_ADDSTRING,(WPARAM) NULL,(LPARAM) (LPCTSTR) STRING(MINPODFUNCTIONS+nFunction));
    continue;
  }
  if (SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_LIST,CB_GETCOUNT) > 0)
  { SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_LIST,CB_SETCURSEL);
    return TRUE;
  }
  return FALSE;
}

BOOL CPODSettingsLayoutPage::EnumParameters()
{
  INT  nParameter;
  INT  nParameters;
  CString  szParameter;
  CDatabaseTMParameter  *pDatabaseTMParameter;

  SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_LIST,CB_RESETCONTENT);
  for (nParameter = 0,nParameters = (INT) GetDatabase() -> GetTMParameters() -> GetSize(); nParameter < nParameters; nParameter++)
  { if ((pDatabaseTMParameter = GetDatabase() -> GetTMParameters() -> GetAt(nParameter)) != (CDatabaseTMParameter *) NULL)
    { szParameter.Format(STRING(IDS_PODSETTINGS_LAYOUTPAGE_PARAMETERFORMAT),(LPCTSTR) pDatabaseTMParameter -> GetTag(),(LPCTSTR) pDatabaseTMParameter -> GetDescription());
      SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_LIST,CB_ADDSTRING,(WPARAM) NULL,(LPARAM) (LPCTSTR) szParameter);
    }
  }
  if (SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_LIST,CB_GETCOUNT) > 0)
  { SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_LIST,CB_SETCURSEL);
    return TRUE;
  }
  return FALSE;
}

BOOL CPODSettingsLayoutPage::EnumFontLocations()
{
  SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_LOCATION,CB_RESETCONTENT);
  SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_LOCATION,CB_INSERTSTRING,(WPARAM) -1,(LPARAM) STRING(IDS_PODSETTINGS_LAYOUTPAGE_DATAVIEWTITLELOCATION));
  SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_LOCATION,CB_INSERTSTRING,(WPARAM) -1,(LPARAM) STRING(IDS_PODSETTINGS_LAYOUTPAGE_DATAVIEWITEMSLOCATION));
  SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_LOCATION,CB_INSERTSTRING,(WPARAM) -1,(LPARAM) STRING(IDS_PODSETTINGS_LAYOUTPAGE_FUNCTIONSVIEWTITLELOCATION));
  SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_LOCATION,CB_INSERTSTRING,(WPARAM) -1,(LPARAM) STRING(IDS_PODSETTINGS_LAYOUTPAGE_FUNCTIONSVIEWITEMSLOCATION));
  SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_LOCATION,CB_INSERTSTRING,(WPARAM) -1,(LPARAM) STRING(IDS_PODSETTINGS_LAYOUTPAGE_PARAMETERSVIEWTITLELOCATION));
  SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_LOCATION,CB_INSERTSTRING,(WPARAM) -1,(LPARAM) STRING(IDS_PODSETTINGS_LAYOUTPAGE_PARAMETERSVIEWITEMSLOCATION));
  return((SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_LOCATION,CB_SETCURSEL) >= 0) ? TRUE:FALSE);
}

VOID CPODSettingsLayoutPage::ShowLayoutFontDetails()
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

  for (SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_STYLE,CB_RESETCONTENT),SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE,CB_RESETCONTENT),GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_LOCATION) -> GetWindowText(szFontArea),SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_NAMES,CB_SETCURSEL,(WPARAM) SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_NAMES,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) ((szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_DATAVIEWTITLELOCATION)) ? m_fntTitle[0][0].lfFaceName:((szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_DATAVIEWITEMSLOCATION)) ? m_fntItems[0][0].lfFaceName:((szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_FUNCTIONSVIEWTITLELOCATION)) ? m_fntTitle[0][1].lfFaceName:((szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_FUNCTIONSVIEWITEMSLOCATION)) ? m_fntItems[0][1].lfFaceName:((szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_PARAMETERSVIEWTITLELOCATION)) ? m_fntTitle[0][2].lfFaceName:m_fntItems[0][2].lfFaceName))))))); (szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_DATAVIEWTITLELOCATION) &&  cFontTools.EnumerateFont(m_fntTitle[0][0].lfFaceName,szStyles,szSizes,bUnderlined)) || (szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_DATAVIEWITEMSLOCATION) &&  cFontTools.EnumerateFont(m_fntItems[0][0].lfFaceName,szStyles,szSizes,bUnderlined)) || (szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_FUNCTIONSVIEWTITLELOCATION) &&  cFontTools.EnumerateFont(m_fntTitle[0][1].lfFaceName,szStyles,szSizes,bUnderlined)) || (szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_FUNCTIONSVIEWITEMSLOCATION) &&  cFontTools.EnumerateFont(m_fntItems[0][1].lfFaceName,szStyles,szSizes,bUnderlined)) || (szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_PARAMETERSVIEWTITLELOCATION) &&  cFontTools.EnumerateFont(m_fntTitle[0][2].lfFaceName,szStyles,szSizes,bUnderlined)) || (szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_PARAMETERSVIEWITEMSLOCATION) &&  cFontTools.EnumerateFont(m_fntItems[0][2].lfFaceName,szStyles,szSizes,bUnderlined)); )
  { for (nStyle = 0,nStyles = (INT) szStyles.GetSize(); nStyle < nStyles; nStyle++) SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_STYLE,CB_INSERTSTRING,(WPARAM) -1,(LPARAM) (LPCTSTR) szStyles.GetAt(nStyle));
    for (nSize = 0,nSizes = (INT) szSizes.GetSize(); nSize < nSizes; nSize++) SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE,CB_INSERTSTRING,(WPARAM) -1,(LPARAM) (LPCTSTR) szSizes.GetAt(nSize));
    break;
  }
  if (szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_DATAVIEWTITLELOCATION))
  { SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_STYLE,CB_SETCURSEL,(WPARAM) max(SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_STYLE,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) cFontTools.TranslateFontStyle(&m_fntTitle[0][0])),0));
    SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE,CB_SETCURSEL,(WPARAM) max(SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) cFontTools.TranslateFontSize(&m_fntTitle[0][0])),max(SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) cFontTools.TranslateFontSize(&m_fntTitle[1][0])),0)));
  }
  if (szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_DATAVIEWITEMSLOCATION))
  { SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_STYLE,CB_SETCURSEL,(WPARAM) max(SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_STYLE,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) cFontTools.TranslateFontStyle(&m_fntItems[0][0])),0));
    SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE,CB_SETCURSEL,(WPARAM) max(SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) cFontTools.TranslateFontSize(&m_fntItems[0][0])),max(SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) cFontTools.TranslateFontSize(&m_fntItems[1][0])),0)));
  }
  if (szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_FUNCTIONSVIEWTITLELOCATION))
  { SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_STYLE,CB_SETCURSEL,(WPARAM) max(SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_STYLE,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) cFontTools.TranslateFontStyle(&m_fntTitle[0][1])),0));
    SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE,CB_SETCURSEL,(WPARAM) max(SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) cFontTools.TranslateFontSize(&m_fntTitle[0][1])),max(SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) cFontTools.TranslateFontSize(&m_fntTitle[1][1])),0)));
  }
  if (szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_FUNCTIONSVIEWITEMSLOCATION))
  { SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_STYLE,CB_SETCURSEL,(WPARAM) max(SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_STYLE,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) cFontTools.TranslateFontStyle(&m_fntItems[0][1])),0));
    SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE,CB_SETCURSEL,(WPARAM) max(SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) cFontTools.TranslateFontSize(&m_fntItems[0][1])),max(SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) cFontTools.TranslateFontSize(&m_fntItems[1][1])),0)));
  }
  if (szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_PARAMETERSVIEWTITLELOCATION))
  { SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_STYLE,CB_SETCURSEL,(WPARAM) max(SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_STYLE,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) cFontTools.TranslateFontStyle(&m_fntTitle[0][2])),0));
    SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE,CB_SETCURSEL,(WPARAM) max(SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) cFontTools.TranslateFontSize(&m_fntTitle[0][2])),max(SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) cFontTools.TranslateFontSize(&m_fntTitle[1][2])),0)));
  }
  if (szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_PARAMETERSVIEWITEMSLOCATION))
  { SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_STYLE,CB_SETCURSEL,(WPARAM) max(SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_STYLE,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) cFontTools.TranslateFontStyle(&m_fntItems[0][2])),0));
    SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE,CB_SETCURSEL,(WPARAM) max(SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) cFontTools.TranslateFontSize(&m_fntItems[0][2])),max(SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) cFontTools.TranslateFontSize(&m_fntItems[1][2])),0)));
  }
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_STYLE_STATIC) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_STYLE,CB_GETCOUNT) > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_STYLE) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_STYLE,CB_GETCOUNT) > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE_STATIC) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE,CB_GETCOUNT) > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE,CB_GETCOUNT) > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SAMPLE) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_STYLE,CB_GETCOUNT) > 0  &&  SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE,CB_GETCOUNT) > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_STYLE,CB_GETCOUNT) > 0  &&  SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE,CB_GETCOUNT) > 0) ? TRUE:FALSE);
}

VOID CPODSettingsLayoutPage::ShowLayoutFontSample()
{
  CRect  rSampleText;

  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT) -> GetWindowRect(rSampleText);
  ScreenToClient(rSampleText);
  InvalidateRect(rSampleText);
  UpdateWindow();
}

BOOL CPODSettingsLayoutPage::IsModified(BOOL bAll) CONST
{
  CFontTools  cFontTools;

  return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (!m_cLayout[0].Compare(&m_cLayout[1]) ||  lstrcmp(m_fntTitle[0][0].lfFaceName,m_fntTitle[1][0].lfFaceName) || (m_fntTitle[0][0].lfHeight != m_fntTitle[1][0].lfHeight  &&  cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntTitle[0][0])) != cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntTitle[1][0]))) ||  m_fntTitle[0][0].lfWeight != m_fntTitle[1][0].lfWeight  ||  m_fntTitle[0][0].lfItalic != m_fntTitle[1][0].lfItalic  ||  lstrcmp(m_fntTitle[0][1].lfFaceName,m_fntTitle[1][1].lfFaceName) || (m_fntTitle[0][1].lfHeight != m_fntTitle[1][1].lfHeight  &&  cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntTitle[0][1])) != cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntTitle[1][1]))) ||  m_fntTitle[0][1].lfWeight != m_fntTitle[1][1].lfWeight  ||  m_fntTitle[0][1].lfItalic != m_fntTitle[1][1].lfItalic  ||  lstrcmp(m_fntTitle[0][2].lfFaceName,m_fntTitle[1][2].lfFaceName) || (m_fntTitle[0][2].lfHeight != m_fntTitle[1][2].lfHeight  &&  cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntTitle[0][2])) != cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntTitle[1][2]))) ||  m_fntTitle[0][2].lfWeight != m_fntTitle[1][2].lfWeight  ||  m_fntTitle[0][2].lfItalic != m_fntTitle[1][2].lfItalic  ||  lstrcmp(m_fntItems[0][0].lfFaceName,m_fntItems[1][0].lfFaceName) || (m_fntItems[0][0].lfHeight != m_fntItems[1][0].lfHeight  &&  cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntItems[0][0])) != cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntItems[1][0]))) ||  m_fntItems[0][0].lfWeight != m_fntItems[1][0].lfWeight  ||  m_fntItems[0][0].lfItalic != m_fntItems[1][0].lfItalic  ||  lstrcmp(m_fntItems[0][1].lfFaceName,m_fntItems[1][1].lfFaceName) || (m_fntItems[0][1].lfHeight != m_fntItems[1][1].lfHeight  &&  cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntItems[0][1])) != cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntItems[1][1]))) ||  m_fntItems[0][1].lfWeight != m_fntItems[1][1].lfWeight  ||  m_fntItems[0][1].lfItalic != m_fntItems[1][1].lfItalic  ||  lstrcmp(m_fntItems[0][2].lfFaceName,m_fntItems[1][2].lfFaceName) || (m_fntItems[0][2].lfHeight != m_fntItems[1][2].lfHeight  &&  cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntItems[0][2])) != cFontTools.QueryPixels(cFontTools.QueryPoints(&m_fntItems[1][2]))) ||  m_fntItems[0][2].lfWeight != m_fntItems[1][2].lfWeight  ||  m_fntItems[0][2].lfItalic != m_fntItems[1][2].lfItalic  ||  m_bToolTips[0] != m_bToolTips[1]):CLocalePropertyPage::IsModified()):FALSE);
}

BOOL CPODSettingsLayoutPage::Check(BOOL bAll) CONST
{
  return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? ((IsDlgButtonChecked(IDC_PODSETTINGS_LAYOUTPAGE_COLUMNS_TIME) ||  IsDlgButtonChecked(IDC_PODSETTINGS_LAYOUTPAGE_COLUMNS_VALUE) ||  IsDlgButtonChecked(IDC_PODSETTINGS_LAYOUTPAGE_COLUMNS_STATUS) ||  IsDlgButtonChecked(IDC_PODSETTINGS_LAYOUTPAGE_COLUMNS_QUALITY)) &&  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_NAMES) -> GetWindowTextLength() > 0  &&  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_STYLE) -> GetWindowTextLength() > 0  &&  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE) -> GetWindowTextLength() > 0):CLocalePropertyPage::Check()):TRUE);
}

void CPODSettingsLayoutPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPODSettingsLayoutPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPODSettingsLayoutPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CPODSettingsLayoutPage)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_PODSETTINGS_LAYOUTPAGE_COLUMNS_TIME,OnColumnTime)
	ON_BN_CLICKED(IDC_PODSETTINGS_LAYOUTPAGE_COLUMNS_VALUE,OnColumnValue)
	ON_BN_CLICKED(IDC_PODSETTINGS_LAYOUTPAGE_COLUMNS_STATUS,OnColumnStatus)
	ON_BN_CLICKED(IDC_PODSETTINGS_LAYOUTPAGE_COLUMNS_QUALITY,OnColumnQuality)
	ON_BN_CLICKED(IDC_PODSETTINGS_LAYOUTPAGE_COLUMNS_TOOLTIPS,OnShowToolTips)
	ON_BN_CLICKED(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTION_ADD,OnAddFunction)
	ON_BN_CLICKED(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTION_REMOVE,OnRemoveFunction)
	ON_BN_CLICKED(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTION_REMOVEALL,OnRemoveAllFunctions)
	ON_BN_CLICKED(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETER_ADD,OnAddParameter)
	ON_BN_CLICKED(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETER_REMOVE,OnRemoveParameter)
	ON_CBN_EDITCHANGE(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_NAMES,OnEditchangeFontName)
	ON_CBN_SELCHANGE(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_LIST,OnSelchangeFunctionList)
	ON_CBN_SELCHANGE(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_USED,OnSelchangeFunctionUsed)
	ON_CBN_SELCHANGE(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_COLOR,OnSelchangeFunctionColor)
	ON_CBN_SELCHANGE(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_LIST,OnSelchangeParameterList)
	ON_CBN_SELCHANGE(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_USED,OnSelchangeParameterUsed)
	ON_CBN_SELCHANGE(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_COLOR,OnSelchangeParameterColor)
	ON_CBN_SELCHANGE(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_LOCATION,OnSelchangeFontLocation)
	ON_CBN_SELCHANGE(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_NAMES,OnSelchangeFontName)
	ON_CBN_SELCHANGE(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_STYLE,OnSelchangeFontStyle)
	ON_CBN_SELCHANGE(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE,OnSelchangeFontSize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPODSettingsLayoutPage message handlers

BOOL CPODSettingsLayoutPage::OnInitDialog() 
{
  INT  nFunction;
  INT  nFunctions;
  INT  nParameter;
  INT  nParameters;
  CString  szName[2];
  CString  szParameter;
  CStringArray  szFunctions;
  CStringArray  szParameters;
  CDatabaseTMParameter  *pDatabaseTMParameter;
  CHourglassCursor  cCursor;

  CLocalePropertyPage::OnInitDialog();
  CheckDlgButton(IDC_PODSETTINGS_LAYOUTPAGE_COLUMNS_TOOLTIPS,m_bToolTips[0]);
  CheckDlgButton(IDC_PODSETTINGS_LAYOUTPAGE_COLUMNS_TIME,(m_cLayout[0].GetColumns() & POD_TITLEITEM_TIME) ? TRUE:FALSE);
  CheckDlgButton(IDC_PODSETTINGS_LAYOUTPAGE_COLUMNS_VALUE,(m_cLayout[0].GetColumns() & POD_TITLEITEM_VALUE) ? TRUE:FALSE);
  CheckDlgButton(IDC_PODSETTINGS_LAYOUTPAGE_COLUMNS_STATUS,(m_cLayout[0].GetColumns() & POD_TITLEITEM_STATUS) ? TRUE:FALSE);
  CheckDlgButton(IDC_PODSETTINGS_LAYOUTPAGE_COLUMNS_QUALITY,(m_cLayout[0].GetColumns() & POD_TITLEITEM_QUALITY) ? TRUE:FALSE);
  for (nFunction = 0,nFunctions = m_cLayout[0].GetFunctions(szFunctions),EnumFunctions(); nFunction < nFunctions; nFunction++)
  { SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_USED,CB_INSERTSTRING,(WPARAM) -1,(LPARAM) (LPCTSTR) szFunctions.GetAt(nFunction));
    continue;
  }
  for (nParameter = 0,nParameters = m_cLayout[0].GetParameters(szParameters),EnumParameters(),EnumFontLocations(); nParameter < nParameters; nParameter++)
  { if ((pDatabaseTMParameter = GetDatabase() -> GetTMParameters() -> GetAt(GetDatabase() -> GetTMParameters() -> Find(szParameters.GetAt(nParameter)))))
    { szParameter.Format(STRING(IDS_PODSETTINGS_LAYOUTPAGE_PARAMETERFORMAT),(LPCTSTR) pDatabaseTMParameter -> GetTag(),(LPCTSTR) pDatabaseTMParameter -> GetDescription());
      SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_USED,LB_INSERTSTRING,(WPARAM) -1,(LPARAM) (LPCTSTR) szParameter);
    }
  }
  SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_USED,CB_SETCURSEL);
  SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_USED,LB_SETCURSEL);
  SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_COLOR,CCB_SELECTCOLOR,(WPARAM) -1,(m_cLayout[0].GetFunctionsColor() != GetSysColor(COLOR_WINDOW)) ? (LPARAM) m_cLayout[0].GetFunctionsColor():(LPARAM) GetDatabase() -> GetPODFunctionsColor());
  SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_COLOR,CCB_SELECTCOLOR,(WPARAM) -1,(m_cLayout[0].GetParametersColor() != GetSysColor(COLOR_WINDOW)) ? (LPARAM) m_cLayout[0].GetParametersColor():(LPARAM) GetDatabase() -> GetPODParametersColor());
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_LIST) -> GetWindowText(szName[0]);
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_LIST) -> GetWindowText(szName[1]);
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT) -> GetWindowText(m_szFontSampleText);
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT) -> SetWindowText(EMPTYSTRING);
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_DETAILS) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_COLUMNS) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_COLUMNS_TIME) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_COLUMNS_VALUE) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_COLUMNS_STATUS) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_COLUMNS_QUALITY) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_COLUMNS_TOOLTIPS_STATIC) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_COLUMNS_TOOLTIPS) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_STATIC) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_LIST) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_USED) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_USED,CB_GETCOUNT) > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_COLOR) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTION_ADD) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_USED,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) szName[0]) == CB_ERR) ? TRUE:FALSE);
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTION_REMOVE) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_USED,CB_GETCURSEL) >= 0) ? TRUE:FALSE);
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTION_REMOVEALL) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_USED,CB_GETCOUNT) > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_STATIC) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_LIST) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_USED) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_USED,LB_GETCOUNT) > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_COLOR) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETER_ADD) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_USED,LB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) szName[1]) == LB_ERR) ? TRUE:FALSE);
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETER_REMOVE) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_USED,LB_GETCURSEL) >= 0) ? TRUE:FALSE);
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_LOCATION_STATIC) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_LOCATION) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_COMMENT_STATIC) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_NAMES_STATIC) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_NAMES) -> EnableWindow();
  SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_NAMES,FCB_DIR,CF_EFFECTS | CF_SCREENFONTS);
  SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_NAMES,CB_SETCURSEL,(WPARAM) SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_NAMES,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) m_fntTitle[0][0].lfFaceName));
  ShowLayoutFontDetails();
  return TRUE;
}

BOOL CPODSettingsLayoutPage::OnKillActive()
{
  GetParentDialog() -> OnDataExchange(GetSafeHwnd(),m_cLayout[0]);
  return CLocalePropertyPage::OnKillActive();
}

BOOL CPODSettingsLayoutPage::OnDataExchange(CONST CPODLayout &cLayout)
{
  UINT  nColumns;

  for (nColumns = m_cLayout[0].GetColumns(); m_cLayout[0].Copy(&cLayout); )
  { m_cLayout[0].SetColumns(nColumns);
    return TRUE;
  }
  return FALSE;
}

void CPODSettingsLayoutPage::OnPaint()
{
  INT  nBkMode;
  CFont  cFont;
  CFont  *pOldFont;
  CRect  rSampleText;
  CString  szFontArea;
  COLORREF  nOldColor;
  CPaintDC  cDC(this);

  for (GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SAMPLETEXT) -> GetWindowRect(rSampleText),GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_LOCATION) -> GetWindowText(szFontArea),ScreenToClient(rSampleText); cFont.CreateFontIndirect((szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_DATAVIEWTITLELOCATION)) ? &m_fntTitle[0][0]:((szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_DATAVIEWITEMSLOCATION)) ? &m_fntItems[0][0]:((szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_FUNCTIONSVIEWTITLELOCATION)) ? &m_fntTitle[0][1]:((szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_FUNCTIONSVIEWITEMSLOCATION)) ? &m_fntItems[0][1]:((szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_PARAMETERSVIEWTITLELOCATION)) ? &m_fntTitle[0][2]:&m_fntItems[0][2]))))); )
  { if ((pOldFont = cDC.SelectObject(&cFont)))
    { nBkMode = cDC.SetBkMode(TRANSPARENT);
      nOldColor = cDC.SetTextColor((SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_STYLE,CB_GETCOUNT) > 0  &&  SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE,CB_GETCOUNT) > 0) ? GetSysColor(COLOR_WINDOWTEXT):GetSysColor(COLOR_GRAYTEXT));
      cDC.DrawText(m_szFontSampleText,rSampleText,DT_SINGLELINE | DT_CENTER | DT_VCENTER);
      cDC.SetTextColor(nOldColor);
      cDC.SelectObject(pOldFont);
      cDC.SetBkMode(nBkMode);
      ValidateRect(rSampleText);
    }
    cFont.DeleteObject();
    break;
  }
}

void CPODSettingsLayoutPage::OnColumnTime()
{
  m_cLayout[0].SetColumns((IsDlgButtonChecked(IDC_PODSETTINGS_LAYOUTPAGE_COLUMNS_TIME)) ? (m_cLayout[0].GetColumns() | POD_TITLEITEM_TIME):(m_cLayout[0].GetColumns() & ~POD_TITLEITEM_TIME));
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsLayoutPage::OnColumnValue()
{
  m_cLayout[0].SetColumns((IsDlgButtonChecked(IDC_PODSETTINGS_LAYOUTPAGE_COLUMNS_VALUE)) ? (m_cLayout[0].GetColumns() | POD_TITLEITEM_VALUE):(m_cLayout[0].GetColumns() & ~POD_TITLEITEM_VALUE));
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsLayoutPage::OnColumnStatus()
{
  m_cLayout[0].SetColumns((IsDlgButtonChecked(IDC_PODSETTINGS_LAYOUTPAGE_COLUMNS_STATUS)) ? (m_cLayout[0].GetColumns() | POD_TITLEITEM_STATUS):(m_cLayout[0].GetColumns() & ~POD_TITLEITEM_STATUS));
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsLayoutPage::OnColumnQuality()
{
  m_cLayout[0].SetColumns((IsDlgButtonChecked(IDC_PODSETTINGS_LAYOUTPAGE_COLUMNS_QUALITY)) ? (m_cLayout[0].GetColumns() | POD_TITLEITEM_QUALITY):(m_cLayout[0].GetColumns() & ~POD_TITLEITEM_QUALITY));
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsLayoutPage::OnShowToolTips()
{
  m_bToolTips[0] = IsDlgButtonChecked(IDC_PODSETTINGS_LAYOUTPAGE_COLUMNS_TOOLTIPS);
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsLayoutPage::OnAddFunction()
{
  INT  nIndex;
  CString  szFunction;
  CStringArray  szFunctions;
  CHourglassCursor  cCursor;

  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_LIST) -> GetWindowText(szFunction);
  if ((nIndex = (INT) SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_USED,CB_INSERTSTRING,(WPARAM) -1,(LPARAM) (LPCTSTR) szFunction)) >= 0)
  { for (m_cLayout[0].GetFunctions(szFunctions),szFunctions.InsertAt(nIndex,szFunction),m_cLayout[0].SetFunctions(szFunctions); SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_USED,CB_SETCURSEL,nIndex) >= 0; )
    { GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_USED) -> EnableWindow();
      GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTION_ADD) -> EnableWindow(FALSE);
      GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTION_REMOVE) -> EnableWindow();
      GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTION_REMOVEALL) -> EnableWindow();
      break;
    }
  }
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_LIST) -> SetFocus();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsLayoutPage::OnRemoveFunction()
{
  INT  nIndex;
  CStringArray  szFunctions;
  CHourglassCursor  cCursor;

  if (SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_USED,CB_DELETESTRING,(WPARAM) (nIndex=(INT) SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_USED,CB_GETCURSEL))) >= 0)
  { for (m_cLayout[0].GetFunctions(szFunctions),szFunctions.RemoveAt(nIndex),m_cLayout[0].SetFunctions(szFunctions); SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_USED,CB_SETCURSEL) >= 0  ||  !SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_USED,CB_GETCOUNT); )
    { GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_USED) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_USED,CB_GETCOUNT) > 0) ? TRUE:FALSE);
      GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTION_ADD) -> EnableWindow();
      GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTION_REMOVE) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_USED,CB_GETCOUNT) > 0) ? TRUE:FALSE);
      GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTION_REMOVEALL) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_USED,CB_GETCOUNT) > 0) ? TRUE:FALSE);
      break;
    }
  }
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_LIST) -> SetFocus();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsLayoutPage::OnRemoveAllFunctions()
{
  CStringArray  szFunctions;
  CHourglassCursor  cCursor;

  m_cLayout[0].SetFunctions(szFunctions);
  SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_USED,CB_RESETCONTENT);
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_USED) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTION_ADD) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTION_REMOVE) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTION_REMOVEALL) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_LIST) -> SetFocus();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsLayoutPage::OnAddParameter()
{
  INT  nPos;
  INT  nIndex;
  CString  szParameter;
  CStringArray  szParameters;
  CHourglassCursor  cCursor;

  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_LIST) -> GetWindowText(szParameter);
  if ((nIndex = (INT) SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_USED,LB_INSERTSTRING,(WPARAM) -1,(LPARAM) (LPCTSTR) szParameter)) >= 0)
  { for (szParameter = ((nPos = szParameter.Find(SPACE)) > 0) ? szParameter.Left(nPos):szParameter,m_cLayout[0].GetParameters(szParameters),szParameters.InsertAt(nIndex,szParameter),m_cLayout[0].SetParameters(szParameters); SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_USED,LB_SETCURSEL,nIndex) >= 0; )
    { GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_USED) -> EnableWindow();
      GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETER_ADD) -> EnableWindow(FALSE);
      GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETER_REMOVE) -> EnableWindow();
      break;
    }
  }
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_LIST) -> SetFocus();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsLayoutPage::OnRemoveParameter()
{
  INT  nIndex;
  CStringArray  szParameters;
  CHourglassCursor  cCursor;

  if (SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_USED,LB_DELETESTRING,(WPARAM) (nIndex=(INT) SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_USED,LB_GETCURSEL))) >= 0)
  { for (m_cLayout[0].GetParameters(szParameters),szParameters.RemoveAt(nIndex),m_cLayout[0].SetParameters(szParameters); SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_USED,LB_SETCURSEL) >= 0  ||  !SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_USED,LB_GETCOUNT); )
    { GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_USED) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_USED,LB_GETCOUNT) > 0) ? TRUE:FALSE);
      GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETER_ADD) -> EnableWindow();
      GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETER_REMOVE) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_USED,LB_GETCOUNT) > 0) ? TRUE:FALSE);
      break;
    }
  }
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_LIST) -> SetFocus();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsLayoutPage::OnEditchangeFontName()
{
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsLayoutPage::OnSelchangeFunctionList()
{
  CString  szFunction;

  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_LIST) -> GetWindowText(szFunction);
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTION_ADD) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_USED,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) szFunction) == CB_ERR) ? TRUE:FALSE);
}

void CPODSettingsLayoutPage::OnSelchangeFunctionUsed()
{
  CString  szFunction;

  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_USED) -> GetWindowText(szFunction);
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTION_REMOVE) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_LIST,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) szFunction) >= 0) ? TRUE:FALSE);
}

void CPODSettingsLayoutPage::OnSelchangeFunctionColor()
{
  m_cLayout[0].SetFunctionsColor((SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_COLOR,CCB_FINDCOLOR,(WPARAM) -1,(LPARAM) ((m_cLayout[1].GetFunctionsColor() != GetSysColor(COLOR_WINDOW)) ? m_cLayout[1].GetFunctionsColor():GetDatabase() -> GetPODFunctionsColor())) != SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_COLOR,CB_GETCURSEL)) ? (COLORREF) SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_COLOR,CCB_GETCOLOR,(WPARAM) SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FUNCTIONS_COLOR,CB_GETCURSEL)):m_cLayout[1].GetFunctionsColor());
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsLayoutPage::OnSelchangeParameterList()
{
  CString  szParameter;

  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_LIST) -> GetWindowText(szParameter);
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETER_ADD) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_USED,LB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) szParameter) == CB_ERR) ? TRUE:FALSE);
}

void CPODSettingsLayoutPage::OnSelchangeParameterUsed()
{
  GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETER_REMOVE) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_LIST,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) Listbox_GetText(GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_USED),(INT) SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_USED,LB_GETCURSEL))) >= 0) ? TRUE:FALSE);
}

void CPODSettingsLayoutPage::OnSelchangeParameterColor()
{
  m_cLayout[0].SetParametersColor((SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_COLOR,CCB_FINDCOLOR,(WPARAM) -1,(LPARAM) ((m_cLayout[1].GetParametersColor() != GetSysColor(COLOR_WINDOW)) ? m_cLayout[1].GetParametersColor():GetDatabase() -> GetPODParametersColor())) != SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_COLOR,CB_GETCURSEL)) ? (COLORREF) SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_COLOR,CCB_GETCOLOR,(WPARAM) SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_PARAMETERS_COLOR,CB_GETCURSEL)):m_cLayout[1].GetParametersColor());
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsLayoutPage::OnSelchangeFontLocation()
{
  ShowLayoutFontDetails();
  ShowLayoutFontSample();
}

void CPODSettingsLayoutPage::OnSelchangeFontName()
{
  CString  szSize;
  CString  szStyle;
  CString  szFontArea;
  CFontTools  cFontTools;

  for (GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_LOCATION) -> GetWindowText(szFontArea); szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_DATAVIEWTITLELOCATION); )
  { _tcscpy_s(m_fntTitle[0][0].lfFaceName,sizeof(m_fntTitle[0][0].lfFaceName)/sizeof(TCHAR),Combobox_GetText(GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_NAMES),(INT) SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_NAMES,CB_GETCURSEL)));
    ShowLayoutFontDetails();
    break;
  }
  if (szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_DATAVIEWITEMSLOCATION))
  { _tcscpy_s(m_fntItems[0][0].lfFaceName,sizeof(m_fntItems[0][0].lfFaceName)/sizeof(TCHAR),Combobox_GetText(GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_NAMES),(INT) SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_NAMES,CB_GETCURSEL)));
    ShowLayoutFontDetails();
  }
  if (szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_FUNCTIONSVIEWTITLELOCATION))
  { _tcscpy_s(m_fntTitle[0][1].lfFaceName,sizeof(m_fntTitle[0][1].lfFaceName)/sizeof(TCHAR),Combobox_GetText(GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_NAMES),(INT) SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_NAMES,CB_GETCURSEL)));
    ShowLayoutFontDetails();
  }
  if (szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_FUNCTIONSVIEWITEMSLOCATION))
  { _tcscpy_s(m_fntItems[0][1].lfFaceName,sizeof(m_fntItems[0][1].lfFaceName)/sizeof(TCHAR),Combobox_GetText(GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_NAMES),(INT) SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_NAMES,CB_GETCURSEL)));
    ShowLayoutFontDetails();
  }
  if (szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_PARAMETERSVIEWTITLELOCATION))
  { _tcscpy_s(m_fntTitle[0][2].lfFaceName,sizeof(m_fntTitle[0][2].lfFaceName)/sizeof(TCHAR),Combobox_GetText(GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_NAMES),(INT) SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_NAMES,CB_GETCURSEL)));
    ShowLayoutFontDetails();
  }
  if (szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_PARAMETERSVIEWITEMSLOCATION))
  { _tcscpy_s(m_fntItems[0][2].lfFaceName,sizeof(m_fntItems[0][2].lfFaceName)/sizeof(TCHAR),Combobox_GetText(GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_NAMES),(INT) SendDlgItemMessage(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_NAMES,CB_GETCURSEL)));
    ShowLayoutFontDetails();
  }
  if (szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_DATAVIEWTITLELOCATION))
  { GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE) -> GetWindowText(szSize);
    GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_STYLE) -> GetWindowText(szStyle);
    cFontTools.TranslateFontStyle(szStyle,m_fntTitle[0][0].lfWeight,m_fntTitle[0][0].lfItalic);
    cFontTools.TranslateFontSize(szSize,m_fntTitle[0][0].lfHeight);
    cFontTools.EnumerateFontCharacteristics(&m_fntTitle[0][0]);
  }
  if (szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_DATAVIEWITEMSLOCATION))
  { GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE) -> GetWindowText(szSize);
    GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_STYLE) -> GetWindowText(szStyle);
    cFontTools.TranslateFontStyle(szStyle,m_fntItems[0][0].lfWeight,m_fntItems[0][0].lfItalic);
    cFontTools.TranslateFontSize(szSize,m_fntItems[0][0].lfHeight);
    cFontTools.EnumerateFontCharacteristics(&m_fntItems[0][0]);
  }
  if (szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_FUNCTIONSVIEWTITLELOCATION))
  { GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE) -> GetWindowText(szSize);
    GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_STYLE) -> GetWindowText(szStyle);
    cFontTools.TranslateFontStyle(szStyle,m_fntTitle[0][1].lfWeight,m_fntTitle[0][1].lfItalic);
    cFontTools.TranslateFontSize(szSize,m_fntTitle[0][1].lfHeight);
    cFontTools.EnumerateFontCharacteristics(&m_fntTitle[0][1]);
  }
  if (szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_FUNCTIONSVIEWITEMSLOCATION))
  { GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE) -> GetWindowText(szSize);
    GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_STYLE) -> GetWindowText(szStyle);
    cFontTools.TranslateFontStyle(szStyle,m_fntItems[0][1].lfWeight,m_fntItems[0][1].lfItalic);
    cFontTools.TranslateFontSize(szSize,m_fntItems[0][1].lfHeight);
    cFontTools.EnumerateFontCharacteristics(&m_fntItems[0][1]);
  }
  if (szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_PARAMETERSVIEWTITLELOCATION))
  { GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE) -> GetWindowText(szSize);
    GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_STYLE) -> GetWindowText(szStyle);
    cFontTools.TranslateFontStyle(szStyle,m_fntTitle[0][2].lfWeight,m_fntTitle[0][2].lfItalic);
    cFontTools.TranslateFontSize(szSize,m_fntTitle[0][2].lfHeight);
    cFontTools.EnumerateFontCharacteristics(&m_fntTitle[0][2]);
  }
  if (szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_PARAMETERSVIEWITEMSLOCATION))
  { GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE) -> GetWindowText(szSize);
    GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_STYLE) -> GetWindowText(szStyle);
    cFontTools.TranslateFontStyle(szStyle,m_fntItems[0][2].lfWeight,m_fntItems[0][2].lfItalic);
    cFontTools.TranslateFontSize(szSize,m_fntItems[0][2].lfHeight);
    cFontTools.EnumerateFontCharacteristics(&m_fntItems[0][2]);
  }
  ShowLayoutFontSample();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsLayoutPage::OnSelchangeFontStyle()
{
  CString  szStyle;
  CString  szFontArea;
  CFontTools  cFontTools;

  for (GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_LOCATION) -> GetWindowText(szFontArea); szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_DATAVIEWTITLELOCATION); )
  { GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_STYLE) -> GetWindowText(szStyle);
    cFontTools.TranslateFontStyle(szStyle,m_fntTitle[0][0].lfWeight,m_fntTitle[0][0].lfItalic);
    break;
  }
  if (szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_DATAVIEWITEMSLOCATION))
  { GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_STYLE) -> GetWindowText(szStyle);
    cFontTools.TranslateFontStyle(szStyle,m_fntItems[0][0].lfWeight,m_fntItems[0][0].lfItalic);
  }
  if (szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_FUNCTIONSVIEWTITLELOCATION))
  { GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_STYLE) -> GetWindowText(szStyle);
    cFontTools.TranslateFontStyle(szStyle,m_fntTitle[0][1].lfWeight,m_fntTitle[0][1].lfItalic);
  }
  if (szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_FUNCTIONSVIEWITEMSLOCATION))
  { GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_STYLE) -> GetWindowText(szStyle);
    cFontTools.TranslateFontStyle(szStyle,m_fntItems[0][1].lfWeight,m_fntItems[0][1].lfItalic);
  }
  if (szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_PARAMETERSVIEWTITLELOCATION))
  { GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_STYLE) -> GetWindowText(szStyle);
    cFontTools.TranslateFontStyle(szStyle,m_fntTitle[0][2].lfWeight,m_fntTitle[0][2].lfItalic);
  }
  if (szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_PARAMETERSVIEWITEMSLOCATION))
  { GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_STYLE) -> GetWindowText(szStyle);
    cFontTools.TranslateFontStyle(szStyle,m_fntItems[0][2].lfWeight,m_fntItems[0][2].lfItalic);
  }
  ShowLayoutFontSample();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsLayoutPage::OnSelchangeFontSize()
{
  CString  szSize;
  CString  szFontArea;
  CFontTools  cFontTools;

  for (GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_LOCATION) -> GetWindowText(szFontArea); szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_DATAVIEWTITLELOCATION); )
  { GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE) -> GetWindowText(szSize);
    cFontTools.TranslateFontSize(szSize,m_fntTitle[0][0].lfHeight);
    break;
  }
  if (szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_DATAVIEWITEMSLOCATION))
  { GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE) -> GetWindowText(szSize);
    cFontTools.TranslateFontSize(szSize,m_fntItems[0][0].lfHeight);
  }
  if (szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_FUNCTIONSVIEWTITLELOCATION))
  { GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE) -> GetWindowText(szSize);
    cFontTools.TranslateFontSize(szSize,m_fntTitle[0][1].lfHeight);
  }
  if (szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_FUNCTIONSVIEWITEMSLOCATION))
  { GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE) -> GetWindowText(szSize);
    cFontTools.TranslateFontSize(szSize,m_fntItems[0][1].lfHeight);
  }
  if (szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_PARAMETERSVIEWTITLELOCATION))
  { GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE) -> GetWindowText(szSize);
    cFontTools.TranslateFontSize(szSize,m_fntTitle[0][2].lfHeight);
  }
  if (szFontArea == STRING(IDS_PODSETTINGS_LAYOUTPAGE_PARAMETERSVIEWITEMSLOCATION))
  { GetDlgItem(IDC_PODSETTINGS_LAYOUTPAGE_FONTS_SIZE) -> GetWindowText(szSize);
    cFontTools.TranslateFontSize(szSize,m_fntItems[0][2].lfHeight);
  }
  ShowLayoutFontSample();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CPODSettingsContentsPage property page

IMPLEMENT_DYNCREATE(CPODSettingsContentsPage,CLocalePropertyPage)

CPODSettingsContentsPage::CPODSettingsContentsPage() : CLocalePropertyPage(CPODSettingsContentsPage::IDD)
{
	//{{AFX_DATA_INIT(CPODSettingsContentsPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CPODSettingsContentsPage::Initialize()
{
  CPODOpenDialog  *pDialog;

  return((((pDialog = GetParentDialog() -> GetParentDialog()) &&  pDialog -> GetLayout(m_cLayout[0])) ||  GetParentDisplay() -> GetLayout(m_cLayout[0])) ? m_cLayout[1].Copy(&m_cLayout[0]):FALSE);
}

BOOL CPODSettingsContentsPage::GetLayout(CPODLayout &cLayout) CONST
{
  return((cLayout.Copy(&m_cLayout[0])) ? Check(FALSE):FALSE);
}

BOOL CPODSettingsContentsPage::EnumParameters()
{
  INT  nParameter;
  INT  nParameters;
  CString  szParameter;
  CDatabaseTMParameter  *pDatabaseTMParameter;

  SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_PARAMETER,CB_RESETCONTENT);
  for (nParameter = 0,nParameters = (INT) GetDatabase() -> GetTMParameters() -> GetSize(); nParameter < nParameters; nParameter++)
  { if ((pDatabaseTMParameter = GetDatabase() -> GetTMParameters() -> GetAt(nParameter)) != (CDatabaseTMParameter *) NULL)
    { szParameter.Format(STRING(IDS_PODSETTINGS_CONTENTSPAGE_PARAMETERFORMAT),(LPCTSTR) pDatabaseTMParameter -> GetTag(),(LPCTSTR) pDatabaseTMParameter -> GetDescription());
      SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_PARAMETER,CB_ADDSTRING,(WPARAM) NULL,(LPARAM) (LPCTSTR) szParameter);
    }
  }
  if (SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_PARAMETER,CB_GETCOUNT) > 0)
  { SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_PARAMETER,CB_SETCURSEL);
    return TRUE;
  }
  return FALSE;
}

UINT CPODSettingsContentsPage::EnumExpressions()
{
  INT  nExpression;
  INT  nExpressions;
  CPODLayoutExpression  *pExpression;

  SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_STACK,LB_RESETCONTENT);
  for (nExpression = 0,nExpressions = (INT) m_cLayout[0].GetSize(),m_nStackPos[0] = m_nStackPos[1] = 0; nExpression < nExpressions; nExpression++)
  { if ((pExpression = (CPODLayoutExpression *) m_cLayout[0].GetAt(nExpression)) != (CPODLayoutExpression *) NULL)
    { SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_STACK,LB_INSERTSTRING,(WPARAM) -1,(LPARAM) pExpression);
      continue;
    }
  }
  if (SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_STACK,LB_GETCOUNT) > 0)
  { SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_STACK,LB_SETCURSEL);
    return nExpressions;
  }
  return 0;
}

VOID CPODSettingsContentsPage::Key(INT nDigit)
{
  double  fNumber;
  double  fConstant[2];
  CHAR  szConstant[2][32];
  CPODLayoutExpression  *pExpression;

  if ((pExpression = m_cLayout[0].GetAt(m_nStackPos[0]+m_nStackPos[1])))
  {
#ifndef UNICODE
    strcpy_s(szConstant[0],sizeof(szConstant[0])/sizeof(CHAR),STRING(IDS_POD_CONSTANT_PI));
    strcpy_s(szConstant[1],sizeof(szConstant[1])/sizeof(CHAR),STRING(IDS_POD_CONSTANT_E));
#else
    WideCharToMultiByte(CP_ACP,0,STRING(IDS_POD_CONSTANT_PI),-1,szConstant[0],sizeof(szConstant[0])/sizeof(szConstant[0][0]),(LPCSTR) NULL,(LPBOOL) NULL);
    WideCharToMultiByte(CP_ACP,0,STRING(IDS_POD_CONSTANT_E),-1,szConstant[1],sizeof(szConstant[1])/sizeof(szConstant[1][0]),(LPCSTR) NULL,(LPBOOL) NULL);
#endif
    fConstant[0] = atof(szConstant[0]);
    fConstant[1] = atof(szConstant[1]);
    if ((pExpression -> IsNumber() &&  pExpression -> GetNumber() != fConstant[0] &&  pExpression -> GetNumber() != fConstant[1]) ||  pExpression -> IsEmpty())
    { if (TranslateNumber(pExpression,nDigit,fNumber))
      { pExpression -> SetNumber(fNumber,FALSE);
        UpdateStackContents();
      }
      else
      { CAudioDevice::AlertBySound();
        return;
      }
    }
    else
    { if ((pExpression = new CPODLayoutExpression))
      { for (pExpression -> SetNumber((double) nDigit); SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_STACK,LB_INSERTSTRING,m_nStackPos[0]+m_nStackPos[1],(LPARAM) pExpression) == LB_ERR; )
        { CAudioDevice::AlertBySound();
          delete pExpression;
          return;
        }
        SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_STACK,LB_SETCURSEL,m_nStackPos[0]);
        m_cLayout[0].InsertAt(m_nStackPos[0]+m_nStackPos[1],pExpression,1);
      }
      else
      { CAudioDevice::AlertBySound();
        return;
      }
    }
  }
  else
  { if ((pExpression = new CPODLayoutExpression))
    { for (pExpression -> SetNumber((double) nDigit); SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_STACK,LB_INSERTSTRING,m_nStackPos[0]+m_nStackPos[1],(LPARAM) pExpression) == LB_ERR; )
      { CAudioDevice::AlertBySound();
        delete pExpression;
        return;
      }
      SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_STACK,LB_SETCURSEL,m_nStackPos[0]);
      m_cLayout[0].InsertAt(m_nStackPos[0]+m_nStackPos[1],pExpression,1);
    }
    else
    { CAudioDevice::AlertBySound();
      return;
    }
  }
  if (SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_STACK,LB_GETCOUNT) > 0)
  { GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_STACK_STATIC) -> EnableWindow();
    GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_STACK) -> EnableWindow();
    GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_STACK_REMOVE) -> EnableWindow();
    GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_STACK_REMOVEALL) -> EnableWindow();
  }
}
VOID CPODSettingsContentsPage::Key(LPCTSTR pszKey)
{
  CHAR  szConstant[32];
  CPODLayoutExpression  *pExpression;

  if (!lstrcmp(pszKey,STRING(IDS_POD_KEY_POINT)))
  { if ((pExpression = m_cLayout[0].GetAt(m_nStackPos[0]+m_nStackPos[1])))
    { if (pExpression -> IsNumber() &&  pExpression -> GetNumberAsText().Find(pszKey) < 0)
      { pExpression -> SetNumber(pExpression -> GetNumber(),TRUE);
        UpdateStackContents();
      }
      else
      { CAudioDevice::AlertBySound();
        return;
      }
    }
    else
    { CAudioDevice::AlertBySound();
      return;
    }
  }
  if (!lstrcmp(pszKey,STRING(IDS_POD_OPERATOR_DIV)) ||  !lstrcmp(pszKey,STRING(IDS_POD_OPERATOR_MUL)) ||  !lstrcmp(pszKey,STRING(IDS_POD_OPERATOR_SUB)) ||  !lstrcmp(pszKey,STRING(IDS_POD_OPERATOR_ADD)) ||  !lstrcmp(pszKey,STRING(IDS_POD_OPERATOR_CHG)))
  { if ((pExpression = m_cLayout[0].GetAt(m_nStackPos[0]+m_nStackPos[1])) &&  pExpression -> IsEmpty())
    { if (CheckStackContents(CString(pszKey)))
      { pExpression -> SetOperator(pszKey);
        UpdateStackContents();
      }
      else
      { CAudioDevice::AlertBySound();
        return;
      }
    }
    else
    { if (CheckStackContents(pszKey))
      { if ((pExpression = new CPODLayoutExpression))
        { for (pExpression -> SetOperator(CString(pszKey)); SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_STACK,LB_INSERTSTRING,m_nStackPos[0]+m_nStackPos[1],(LPARAM) pExpression) == LB_ERR; )
          { CAudioDevice::AlertBySound();
            delete pExpression;
            return;
          }
          SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_STACK,LB_SETCURSEL,m_nStackPos[0]);
          m_cLayout[0].InsertAt(m_nStackPos[0]+m_nStackPos[1],pExpression,1);
        }
        else
        { CAudioDevice::AlertBySound();
          return;
        }
      }
      else
      { CAudioDevice::AlertBySound();
        return;
      }
    }
  }
  if (!lstrcmp(pszKey,STRING(IDS_POD_MATHFUNCTION_SIN)) ||  !lstrcmp(pszKey,STRING(IDS_POD_MATHFUNCTION_COS)) ||  !lstrcmp(pszKey,STRING(IDS_POD_MATHFUNCTION_TAN)) ||  !lstrcmp(pszKey,STRING(IDS_POD_MATHFUNCTION_ASIN)) ||  !lstrcmp(pszKey,STRING(IDS_POD_MATHFUNCTION_ACOS)) ||  !lstrcmp(pszKey,STRING(IDS_POD_MATHFUNCTION_ATAN)) ||  !lstrcmp(pszKey,STRING(IDS_POD_MATHFUNCTION_ABS)) ||  !lstrcmp(pszKey,STRING(IDS_POD_MATHFUNCTION_INT)) ||  !lstrcmp(pszKey,STRING(IDS_POD_MATHFUNCTION_SQRT)) ||  !lstrcmp(pszKey,STRING(IDS_POD_MATHFUNCTION_POW2)) ||  !lstrcmp(pszKey,STRING(IDS_POD_MATHFUNCTION_POWY)) ||  !lstrcmp(pszKey,STRING(IDS_POD_MATHFUNCTION_LN)) ||  !lstrcmp(pszKey,STRING(IDS_POD_MATHFUNCTION_LOG)) ||  !lstrcmp(pszKey,STRING(IDS_POD_MATHFUNCTION_EXP)))
  { if ((pExpression = m_cLayout[0].GetAt(m_nStackPos[0]+m_nStackPos[1])) &&  pExpression -> IsEmpty())
    { if (CheckStackContents(CString(pszKey)))
      { pExpression -> SetFunction(pszKey);
        UpdateStackContents();
      }
      else
      { CAudioDevice::AlertBySound();
        return;
      }
    }
    else
    { if (CheckStackContents(pszKey))
      { if ((pExpression = new CPODLayoutExpression))
        { for (pExpression -> SetFunction(CString(pszKey)); SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_STACK,LB_INSERTSTRING,m_nStackPos[0]+m_nStackPos[1],(LPARAM) pExpression) == LB_ERR; )
          { CAudioDevice::AlertBySound();
            delete pExpression;
            return;
          }
          SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_STACK,LB_SETCURSEL,m_nStackPos[0]);
          m_cLayout[0].InsertAt(m_nStackPos[0]+m_nStackPos[1],pExpression,1);
        }
        else
        { CAudioDevice::AlertBySound();
          return;
        }
      }
      else
      { CAudioDevice::AlertBySound();
        return;
      }
    }
  }
  if (!lstrcmp(pszKey,STRING(IDS_POD_CONSTANT_PI)) ||  !lstrcmp(pszKey,STRING(IDS_POD_CONSTANT_E)))
  { if ((pExpression = m_cLayout[0].GetAt(m_nStackPos[0]+m_nStackPos[1])) &&  pExpression -> IsEmpty())
    {
#ifndef UNICODE
      strcpy_s(szConstant,sizeof(szConstant)/sizeof(CHAR),pszKey);
#else
      WideCharToMultiByte(CP_ACP,0,pszKey,-1,szConstant,sizeof(szConstant)/sizeof(szConstant[0]),(LPCSTR) NULL,(LPBOOL) NULL);
#endif
      pExpression -> SetNumber(atof(szConstant));
      UpdateStackContents();
    }
    else
    { if ((pExpression = new CPODLayoutExpression))
      {
#ifndef UNICODE
        strcpy_s(szConstant,sizeof(szConstant)/sizeof(CHAR),pszKey);
#else
        WideCharToMultiByte(CP_ACP,0,pszKey,-1,szConstant,sizeof(szConstant)/sizeof(szConstant[0]),(LPCSTR) NULL,(LPBOOL) NULL);
#endif
        pExpression -> SetNumber(atof(szConstant));
        if (SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_STACK,LB_INSERTSTRING,m_nStackPos[0]+m_nStackPos[1],(LPARAM) pExpression) == LB_ERR)
        { CAudioDevice::AlertBySound();
          delete pExpression;
          return;
        }
        SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_STACK,LB_SETCURSEL,m_nStackPos[0]);
        m_cLayout[0].InsertAt(m_nStackPos[0]+m_nStackPos[1],pExpression,1);
      }
      else
      { CAudioDevice::AlertBySound();
        return;
      }
    }
  }
  if (!lstrcmp(pszKey,STRING(IDS_POD_KEY_ENTER)))
  { if ((pExpression = (m_cLayout[0].GetSize() > 0  &&  !m_cLayout[0].GetAt(m_nStackPos[0]+m_nStackPos[1]) -> IsEmpty()) ? new CPODLayoutExpression:(CPODLayoutExpression *) NULL))
    { if (SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_STACK,LB_INSERTSTRING,m_nStackPos[0]+m_nStackPos[1],(LPARAM) pExpression) == LB_ERR)
      { CAudioDevice::AlertBySound();
        delete pExpression;
        return;
      }
      SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_STACK,LB_SETCURSEL,m_nStackPos[0]);
      m_cLayout[0].InsertAt(m_nStackPos[0]+m_nStackPos[1],pExpression,1);
    }
    else
    { CAudioDevice::AlertBySound();
      return;
    }
  }
  if (SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_STACK,LB_GETCOUNT) > 0)
  { GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_STACK_STATIC) -> EnableWindow();
    GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_STACK) -> EnableWindow();
    GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_STACK_REMOVE) -> EnableWindow();
    GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_STACK_REMOVEALL) -> EnableWindow();
  }
}

INT CPODSettingsContentsPage::CheckStackOperands() CONST
{
  INT  nOperands;
  INT  nParameters;
  INT  nExpression;
  INT  nExpressions;
  CPODLayoutExpression  *pExpression;

  for (nExpression = nExpressions = (INT) m_cLayout[0].GetSize(),nOperands = 0,nParameters = 0; nExpression > 0; nExpression--)
  { if ((pExpression = m_cLayout[0].GetAt(nExpression-1)))
    { if (pExpression -> IsParameter() ||  pExpression -> IsNumber())
      { nParameters = (pExpression -> IsParameter()) ? (nParameters+1):nParameters;
        nOperands++;
        continue;
      }
      if (pExpression -> IsFunction())
      { if (!lstrcmp(pExpression -> GetFunction(),STRING(IDS_POD_MATHFUNCTION_POWY)))
        { nOperands--;
          continue;
        }
      }
      if (pExpression -> IsOperator())
      { if (!lstrcmp(pExpression -> GetOperator(),STRING(IDS_POD_OPERATOR_DIV)) ||  !lstrcmp(pExpression -> GetOperator(),STRING(IDS_POD_OPERATOR_MUL)) ||  !lstrcmp(pExpression -> GetOperator(),STRING(IDS_POD_OPERATOR_SUB)) ||  !lstrcmp(pExpression -> GetOperator(),STRING(IDS_POD_OPERATOR_ADD)))
        { nOperands--;
          continue;
        }
      }
    }
  }
  return((nParameters == nExpressions) ? -nOperands:nOperands);
}

BOOL CPODSettingsContentsPage::CheckStackContents(LPCTSTR pszKey) CONST
{
  INT  nOperands;

  for (nOperands = CheckStackOperands(); !lstrcmp(pszKey,STRING(IDS_POD_OPERATOR_DIV)) ||  !lstrcmp(pszKey,STRING(IDS_POD_OPERATOR_MUL)) ||  !lstrcmp(pszKey,STRING(IDS_POD_OPERATOR_SUB)) ||  !lstrcmp(pszKey,STRING(IDS_POD_OPERATOR_ADD)) ||  !lstrcmp(pszKey,STRING(IDS_POD_MATHFUNCTION_POWY)); ) return((abs(nOperands) > 1) ? TRUE:FALSE);
  if (!lstrcmp(pszKey,STRING(IDS_POD_MATHFUNCTION_SIN)) ||  !lstrcmp(pszKey,STRING(IDS_POD_MATHFUNCTION_COS)) ||  !lstrcmp(pszKey,STRING(IDS_POD_MATHFUNCTION_TAN)) ||  !lstrcmp(pszKey,STRING(IDS_POD_MATHFUNCTION_ASIN)) ||  !lstrcmp(pszKey,STRING(IDS_POD_MATHFUNCTION_ACOS)) ||  !lstrcmp(pszKey,STRING(IDS_POD_MATHFUNCTION_ATAN)) ||  !lstrcmp(pszKey,STRING(IDS_POD_MATHFUNCTION_ABS)) ||  !lstrcmp(pszKey,STRING(IDS_POD_MATHFUNCTION_INT)) ||  !lstrcmp(pszKey,STRING(IDS_POD_MATHFUNCTION_SQRT)) ||  !lstrcmp(pszKey,STRING(IDS_POD_MATHFUNCTION_POW2)) ||  !lstrcmp(pszKey,STRING(IDS_POD_MATHFUNCTION_LN)) ||  !lstrcmp(pszKey,STRING(IDS_POD_MATHFUNCTION_LOG)) ||  !lstrcmp(pszKey,STRING(IDS_POD_MATHFUNCTION_EXP)) ||  !lstrcmp(pszKey,STRING(IDS_POD_OPERATOR_CHG))) return((abs(nOperands) > 0) ? TRUE:FALSE);
  return TRUE;
}

VOID CPODSettingsContentsPage::UpdateStackContents()
{
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_STACK) -> Invalidate(FALSE);
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_STACK) -> UpdateWindow();
}

BOOL CPODSettingsContentsPage::TranslateNumber(CPODLayoutExpression *pExpression,INT nDigit,double &fNumber)
{
  double  fResult;
  LPTSTR  pszNumber;
  CString  szNumber;
  CStringTools  cStringTools;

  if (pExpression -> IsEmpty())
  { fNumber = nDigit;
    return TRUE;
  }
  if (pExpression -> IsNumber())
  { for (szNumber = pExpression -> GetNumberAsText()+cStringTools.ConvertIntToString(nDigit),fResult = _tcstod(szNumber,&pszNumber); errno != ERANGE  &&  !lstrlen(pszNumber); )
    { fNumber = fResult;
      return TRUE;
    }
  }
  return FALSE;
}

CPODSettingsDialog *CPODSettingsContentsPage::GetParentDialog() CONST
{
  return((CPODSettingsDialog *) CLocalePropertyPage::GetParent());
}

CPODWnd *CPODSettingsContentsPage::GetParentDisplay() CONST
{
  return((CPODWnd *) GetParentDialog() -> GetParentDisplay());
}

BOOL CPODSettingsContentsPage::PreTranslateMessage(MSG *pMsg)
{
  if (GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_STACK) -> GetSafeHwnd() == pMsg -> hwnd  &&  pMsg -> message == WM_KEYDOWN)
  { for (m_nStackPos[1] = (pMsg -> wParam == VK_DOWN) ? ((SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_STACK,LB_GETCURSEL) == SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_STACK,LB_GETCOUNT)-1) ? min(m_nStackPos[1]+1,1):m_nStackPos[1]):m_nStackPos[1],m_nStackPos[1] = (pMsg -> wParam == VK_UP) ? ((!SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_STACK,LB_GETCURSEL)) ? max(m_nStackPos[1]-1,0):m_nStackPos[1]):m_nStackPos[1]; pMsg -> wParam == VK_DOWN  ||  pMsg -> wParam == VK_UP; )
    { GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_STACK) -> RedrawWindow((LPCRECT) NULL,(CRgn *) NULL,(pMsg -> wParam == VK_UP  &&  m_nStackPos[0] == SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_STACK,LB_GETCOUNT)-1) ? (RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW):(RDW_INVALIDATE | RDW_NOERASE | RDW_UPDATENOW));
      break;
    }
  }
  return CLocalePropertyPage::PreTranslateMessage(pMsg);
}

BOOL CPODSettingsContentsPage::IsModified(BOOL bAll) CONST
{
  return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? !m_cLayout[0].Compare(&m_cLayout[1]):CLocalePropertyPage::IsModified()):FALSE);
}

BOOL CPODSettingsContentsPage::Check(BOOL bAll) CONST
{
  INT  nOperands;
  CPODLayoutExpression  *pExpression;

  return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (((pExpression = m_cLayout[0].GetAt(0)) &&  !pExpression -> IsEmpty() && ((nOperands = CheckStackOperands()) == 1  ||  nOperands < 0)) ||  !m_cLayout[0].GetSize()):CLocalePropertyPage::Check()):TRUE);
}

void CPODSettingsContentsPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPODSettingsContentsPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPODSettingsContentsPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CPODSettingsContentsPage)
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_PODSETTINGS_CONTENTSPAGE_STACK_ADD,OnAddParameter)
	ON_BN_CLICKED(IDC_PODSETTINGS_CONTENTSPAGE_STACK_REMOVE,OnRemoveExpression)
	ON_BN_CLICKED(IDC_PODSETTINGS_CONTENTSPAGE_STACK_REMOVEALL,OnRemoveAllExpressions)
	ON_BN_CLICKED(IDC_PODSETTINGS_CONTENTSPAGE_KEY_0,OnKey0)
	ON_BN_CLICKED(IDC_PODSETTINGS_CONTENTSPAGE_KEY_1,OnKey1)
	ON_BN_CLICKED(IDC_PODSETTINGS_CONTENTSPAGE_KEY_2,OnKey2)
	ON_BN_CLICKED(IDC_PODSETTINGS_CONTENTSPAGE_KEY_3,OnKey3)
	ON_BN_CLICKED(IDC_PODSETTINGS_CONTENTSPAGE_KEY_4,OnKey4)
	ON_BN_CLICKED(IDC_PODSETTINGS_CONTENTSPAGE_KEY_5,OnKey5)
	ON_BN_CLICKED(IDC_PODSETTINGS_CONTENTSPAGE_KEY_6,OnKey6)
	ON_BN_CLICKED(IDC_PODSETTINGS_CONTENTSPAGE_KEY_7,OnKey7)
	ON_BN_CLICKED(IDC_PODSETTINGS_CONTENTSPAGE_KEY_8,OnKey8)
	ON_BN_CLICKED(IDC_PODSETTINGS_CONTENTSPAGE_KEY_9,OnKey9)
	ON_BN_CLICKED(IDC_PODSETTINGS_CONTENTSPAGE_KEY_POINT,OnKeyPoint)
	ON_BN_CLICKED(IDC_PODSETTINGS_CONTENTSPAGE_KEY_DIV,OnKeyDiv)
	ON_BN_CLICKED(IDC_PODSETTINGS_CONTENTSPAGE_KEY_MUL,OnKeyMul)
	ON_BN_CLICKED(IDC_PODSETTINGS_CONTENTSPAGE_KEY_SUB,OnKeySub)
	ON_BN_CLICKED(IDC_PODSETTINGS_CONTENTSPAGE_KEY_ADD,OnKeyAdd)
	ON_BN_CLICKED(IDC_PODSETTINGS_CONTENTSPAGE_KEY_SIGN,OnKeyChg)
	ON_BN_CLICKED(IDC_PODSETTINGS_CONTENTSPAGE_KEY_SIN,OnKeySin)
	ON_BN_CLICKED(IDC_PODSETTINGS_CONTENTSPAGE_KEY_COS,OnKeyCos)
	ON_BN_CLICKED(IDC_PODSETTINGS_CONTENTSPAGE_KEY_TAN,OnKeyTan)
	ON_BN_CLICKED(IDC_PODSETTINGS_CONTENTSPAGE_KEY_ASIN,OnKeyASin)
	ON_BN_CLICKED(IDC_PODSETTINGS_CONTENTSPAGE_KEY_ACOS,OnKeyACos)
	ON_BN_CLICKED(IDC_PODSETTINGS_CONTENTSPAGE_KEY_ATAN,OnKeyATan)
	ON_BN_CLICKED(IDC_PODSETTINGS_CONTENTSPAGE_KEY_ABS,OnKeyAbs)
	ON_BN_CLICKED(IDC_PODSETTINGS_CONTENTSPAGE_KEY_INT,OnKeyInt)
	ON_BN_CLICKED(IDC_PODSETTINGS_CONTENTSPAGE_KEY_SQRT,OnKeySqrt)
	ON_BN_CLICKED(IDC_PODSETTINGS_CONTENTSPAGE_KEY_X2,OnKeyPow2)
	ON_BN_CLICKED(IDC_PODSETTINGS_CONTENTSPAGE_KEY_XY,OnKeyPowY)
	ON_BN_CLICKED(IDC_PODSETTINGS_CONTENTSPAGE_KEY_LN,OnKeyLn)
	ON_BN_CLICKED(IDC_PODSETTINGS_CONTENTSPAGE_KEY_LOG,OnKeyLog)
	ON_BN_CLICKED(IDC_PODSETTINGS_CONTENTSPAGE_KEY_EXP,OnKeyExp)
	ON_BN_CLICKED(IDC_PODSETTINGS_CONTENTSPAGE_KEY_PI,OnKeyPI)
	ON_BN_CLICKED(IDC_PODSETTINGS_CONTENTSPAGE_KEY_E,OnKeyE)
	ON_BN_CLICKED(IDC_PODSETTINGS_CONTENTSPAGE_KEY_ENTER,OnKeyEnter)
	ON_CBN_SELCHANGE(IDC_PODSETTINGS_CONTENTSPAGE_COLOR,OnSelchangeColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPODSettingsContentsPage message handlers

BOOL CPODSettingsContentsPage::OnInitDialog() 
{
  INT  nSample;
  CString  szParameter;
  ULONGLONG  nAttributes;
  CPODLayoutExpression  *pExpression;
  CHourglassCursor  cCursor;

  CLocalePropertyPage::OnInitDialog();
  for (CheckDlgButton(IDC_PODSETTINGS_CONTENTSPAGE_PARAMETER_DEFAULT,TRUE),CheckDlgButton(IDC_PODSETTINGS_CONTENTSPAGE_PARAMETER_CODED,FALSE),nSample = 0; (pExpression = m_cLayout[0].GetAt(0)) &&  pExpression -> GetParameter(szParameter,nSample,nAttributes); )
  { CheckDlgButton(IDC_PODSETTINGS_CONTENTSPAGE_PARAMETER_DEFAULT,((nAttributes & (TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS)) ||  !nAttributes) ? TRUE:FALSE);
    CheckDlgButton(IDC_PODSETTINGS_CONTENTSPAGE_PARAMETER_CODED,(nAttributes & TMPARAMETER_CALIBRATION_NONE) ? TRUE:FALSE);
    break;
  }
  EnumParameters();
  EnumExpressions();
  SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_COLOR,CCB_SELECTCOLOR,(WPARAM) -1,(m_cLayout[0].GetExpressionColor() != GetSysColor(COLOR_WINDOW)) ? (WPARAM) m_cLayout[0].GetExpressionColor():GetDatabase() -> GetPODExpressionColor());
  Spinbox_SetRange(GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_PARAMETER_SAMPLE),PODSETTINGSCONTENTSPAGE_MINIMUMSAMPLE,PODSETTINGSCONTENTSPAGE_MAXIMUMSAMPLE);
  Spinbox_SetPos(GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_PARAMETER_SAMPLE),nSample);
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_DETAILS) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_PARAMETER_STATIC) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_PARAMETER) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_PARAMETER_DEFAULT) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_PARAMETER_CODED) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_PARAMETER_SAMPLE_STATIC) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_PARAMETER_SAMPLE) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_STACK_STATIC) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_STACK,LB_GETCOUNT) > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_STACK) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_STACK,LB_GETCOUNT) > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_COLOR_STATIC) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_COLOR) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_STACK_ADD) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_STACK_REMOVE) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_STACK,LB_GETCURSEL) >= 0) ? TRUE:FALSE);
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_STACK_REMOVEALL) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_STACK,LB_GETCOUNT) > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_KEY_7) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_KEY_8) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_KEY_9) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_KEY_4) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_KEY_5) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_KEY_6) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_KEY_1) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_KEY_2) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_KEY_3) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_KEY_0) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_KEY_SIGN) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_KEY_POINT) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_KEY_DIV) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_KEY_MUL) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_KEY_SUB) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_KEY_ADD) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_KEY_SIN) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_KEY_COS) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_KEY_TAN) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_KEY_ASIN) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_KEY_ACOS) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_KEY_ATAN) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_KEY_ABS) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_KEY_INT) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_KEY_SQRT) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_KEY_X2) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_KEY_XY) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_KEY_LN) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_KEY_LOG) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_KEY_EXP) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_KEY_PI) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_KEY_E) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_KEY_ENTER) -> EnableWindow();
  return TRUE;
}

BOOL CPODSettingsContentsPage::OnSetActive()
{
  EnumExpressions();
  return CLocalePropertyPage::OnSetActive();
}

BOOL CPODSettingsContentsPage::OnKillActive()
{
  GetParentDialog() -> OnDataExchange(GetSafeHwnd(),m_cLayout[0]);
  return CLocalePropertyPage::OnKillActive();
}

BOOL CPODSettingsContentsPage::OnDataExchange(CONST CPODLayout &cLayout)
{
  return m_cLayout[0].Copy(&cLayout);
}

void CPODSettingsContentsPage::OnDrawItem(int nCtlID,LPDRAWITEMSTRUCT lpDrawItemStruct)
{
  CDC  cDC;
  INT  nSample;
  INT  nOldMode;
  RECT  rSample;
  CPen  cCtrlPen;
  CPen  cSymbolPen;
  CPen  *pOldPen;
  CFont  *pOldFont;
  POINT  ptLine[2];
  POINT  ptSymbol[2][3];
  CBrush  cSymbolBrush;
  CBrush  *pOldBrush;
  COLORREF  nOldColor;
  CString  szExpression;
  CString  szParameter[3];
  ULONGLONG  nAttributes;
  CPODLayoutExpression  *pExpression;

  if (nCtlID == IDC_PODSETTINGS_CONTENTSPAGE_STACK)
  { if (cDC.Attach(lpDrawItemStruct -> hDC))
    { if ((pOldFont = cDC.SelectObject(GetFont())))
      { nOldMode = cDC.SetBkMode(TRANSPARENT);
        nOldColor = cDC.SetTextColor(((lpDrawItemStruct -> itemState & ODS_SELECTED) == 0) ? GetSysColor(COLOR_WINDOWTEXT):GetSysColor(COLOR_HIGHLIGHTTEXT));
        if ((pExpression = (CPODLayoutExpression *) SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_STACK,LB_GETITEMDATA,lpDrawItemStruct -> itemID)))
        { for (szParameter[1] = (pExpression -> GetParameter(szParameter[0],nSample,nAttributes)) ? (LPCTSTR) szParameter[0]:EMPTYSTRING,szParameter[1] = (nSample != 0) ? (szParameter[1]+STRING(IDS_PODSETTINGS_CONTENTSPAGE_PARAMETERSAMPLEFLAG)):szParameter[1],szParameter[1] = (nAttributes & TMPARAMETER_CALIBRATION_NONE) ? (szParameter[1]+STRING(IDS_PODSETTINGS_CONTENTSPAGE_PARAMETERVALUEFLAG)):szParameter[1],szParameter[2].Format(szParameter[1],nSample),szExpression = (!pExpression -> IsFunction()) ? ((!pExpression -> IsOperator()) ? ((!pExpression -> IsParameter()) ? ((pExpression -> IsNumber()) ? pExpression -> GetNumberAsText():szExpression):szParameter[2]):pExpression -> GetOperator()):pExpression -> GetFunction(); szExpression.GetLength() > 0; )
          { cDC.FillSolidRect(&lpDrawItemStruct -> rcItem,((lpDrawItemStruct -> itemState & ODS_SELECTED) == 0) ? ((lpDrawItemStruct -> itemID%2 == 0) ? GetSysColor(COLOR_3DFACE):GetSysColor(COLOR_WINDOW)):GetSysColor(COLOR_HIGHLIGHT));
            cDC.DrawText(szExpression,&lpDrawItemStruct -> rcItem,DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            break;
          }
        }
        cDC.SetTextColor(nOldColor);
        cDC.SelectObject(pOldFont);
        cDC.SetBkMode(nOldMode);
      }
      if ((lpDrawItemStruct -> itemAction & ODA_SELECT) && (lpDrawItemStruct -> itemState & ODS_SELECTED))
      { if (m_nStackPos[0] != lpDrawItemStruct -> itemID  &&  m_nStackPos[1] > 0)
        { for ( ; (m_nStackPos[0] = (INT) lpDrawItemStruct -> itemID) >= 0; )
          { GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_STACK) -> RedrawWindow();
            break;
          }
        }
        if (m_nStackPos[0] != lpDrawItemStruct -> itemID)
        { for ( ; (m_nStackPos[0] = (INT) lpDrawItemStruct -> itemID) >= 0; )
          { GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_STACK) -> RedrawWindow((LPCRECT) NULL,(CRgn *) NULL,RDW_INVALIDATE | RDW_NOERASE | RDW_UPDATENOW);
            break;
          }
        }
      }
      if (SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_STACK,LB_GETITEMRECT,min(SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_STACK,LB_GETCOUNT)-1,m_nStackPos[0]+m_nStackPos[1]),(LPARAM) &rSample) >= 0)
      { for (ptLine[0].x = rSample.left,ptLine[0].y = rSample.top,ptLine[1].x = rSample.right,ptLine[1].y = rSample.top; m_nStackPos[0]+m_nStackPos[1] == SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_STACK,LB_GETCOUNT); )
        { ptLine[0].y = rSample.bottom;
          ptLine[1].y = rSample.bottom;
          break;
        }
        if (cCtrlPen.CreatePen(PS_SOLID,PODSETTINGSCONTENTSPAGE_STACKPOSINDICATOR_WIDTH,VGA_COLOR_LTRED))
        { if ((pOldPen = cDC.SelectObject(&cCtrlPen)))
          { cDC.MoveTo(ptLine[0]);
            cDC.LineTo(ptLine[1]);
            cDC.SelectObject(pOldPen);
          }
          cCtrlPen.DeleteObject();
        }
        if (cSymbolPen.CreatePen(PS_SOLID,1,VGA_COLOR_LTRED))
        { if (cSymbolBrush.CreateSolidBrush(VGA_COLOR_LTRED))
          { if ((pOldBrush = cDC.SelectObject(&cSymbolBrush)))
            { if ((pOldPen = cDC.SelectObject(&cSymbolPen)))
              { ptSymbol[0][0].x = ptLine[0].x;
                ptSymbol[0][1].x = ptLine[0].x+3*PODSETTINGSCONTENTSPAGE_STACKPOSINDICATOR_WIDTH;
                ptSymbol[0][2].x = ptLine[0].x;
                ptSymbol[0][0].y = ptLine[0].y-(3*PODSETTINGSCONTENTSPAGE_STACKPOSINDICATOR_WIDTH)/2;
                ptSymbol[0][1].y = ptLine[0].y;
                ptSymbol[0][2].y = ptLine[0].y+(3*PODSETTINGSCONTENTSPAGE_STACKPOSINDICATOR_WIDTH)/2;
                ptSymbol[1][0].x = ptLine[1].x;
                ptSymbol[1][1].x = ptLine[1].x-3*PODSETTINGSCONTENTSPAGE_STACKPOSINDICATOR_WIDTH;
                ptSymbol[1][2].x = ptLine[1].x;
                ptSymbol[1][0].y = ptLine[1].y-(3*PODSETTINGSCONTENTSPAGE_STACKPOSINDICATOR_WIDTH)/2;
                ptSymbol[1][1].y = ptLine[1].y;
                ptSymbol[1][2].y = ptLine[1].y+(3*PODSETTINGSCONTENTSPAGE_STACKPOSINDICATOR_WIDTH)/2;
                cDC.Polygon(ptSymbol[0],sizeof(ptSymbol[0])/sizeof(ptSymbol[0][0]));
                cDC.Polygon(ptSymbol[1],sizeof(ptSymbol[1])/sizeof(ptSymbol[1][0]));
                cDC.SelectObject(pOldPen);
              }
              cDC.SelectObject(pOldBrush);
            }
            cSymbolBrush.DeleteObject();
          }
          cSymbolPen.DeleteObject();
        }
      }
      cDC.Detach();
    }
    return;
  }
  CLocalePropertyPage::OnDrawItem(nCtlID,lpDrawItemStruct);
}

void CPODSettingsContentsPage::OnAddParameter()
{
  CString  szParameter;
  CPODLayoutExpression  *pExpression;
  CHourglassCursor  cCursor;

  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_PARAMETER) -> GetWindowText(szParameter);
  for (szParameter = szParameter.Left(max(szParameter.Find(CString(SPACE)+SPACE),0)); !szParameter.IsEmpty(); )
  { if ((pExpression = m_cLayout[0].GetAt(m_nStackPos[0]+m_nStackPos[1])) &&  pExpression -> IsEmpty())
    { pExpression -> SetParameter(szParameter,(INT) Spinbox_GetPos(GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_PARAMETER_SAMPLE)),(IsDlgButtonChecked(IDC_PODSETTINGS_CONTENTSPAGE_PARAMETER_CODED)) ? (TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_RADIX_DECIMAL):0);
      UpdateStackContents();
      break;
    }
    if ((pExpression = new CPODLayoutExpression))
    { for (pExpression -> SetParameter(szParameter,(INT) Spinbox_GetPos(GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_PARAMETER_SAMPLE)),(IsDlgButtonChecked(IDC_PODSETTINGS_CONTENTSPAGE_PARAMETER_CODED)) ? (TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_RADIX_DECIMAL):0); SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_STACK,LB_INSERTSTRING,m_nStackPos[0]+m_nStackPos[1],(LPARAM) pExpression) < 0; )
      { CAudioDevice::AlertBySound();
        delete pExpression;
        return;
      }
      SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_STACK,LB_SETCURSEL,m_nStackPos[0]);
      GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_STACK_STATIC) -> EnableWindow();
      GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_STACK) -> EnableWindow();
      GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_STACK_REMOVE) -> EnableWindow();
      GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_STACK_REMOVEALL) -> EnableWindow();
      m_cLayout[0].InsertAt(m_nStackPos[0]+m_nStackPos[1],pExpression,1);
    }
    else
    { CAudioDevice::AlertBySound();
      return;
    }
    break;
  }
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_PARAMETER) -> SetFocus();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsContentsPage::OnRemoveExpression()
{
  INT  nIndex;
  CHourglassCursor  cCursor;

  if (SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_STACK,LB_DELETESTRING,(nIndex=m_nStackPos[0])) != LB_ERR)
  { SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_STACK,LB_SETCURSEL,min(SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_STACK,LB_GETCOUNT)-1,m_nStackPos[0]));
    delete m_cLayout[0].GetAt(nIndex);
    m_cLayout[0].RemoveAt(nIndex);
  }
  if (!SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_STACK,LB_GETCOUNT))
  { GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_STACK_STATIC) -> EnableWindow(FALSE);
    GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_STACK) -> EnableWindow(FALSE);
    GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_STACK_REMOVE) -> EnableWindow(FALSE);
    GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_STACK_REMOVEALL) -> EnableWindow(FALSE);
  }
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_PARAMETER) -> SetFocus();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsContentsPage::OnRemoveAllExpressions()
{
  CHourglassCursor  cCursor;

  m_cLayout[0].RemoveAll();
  m_nStackPos[0] = m_nStackPos[1] = 0;
  SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_STACK,LB_RESETCONTENT);
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_STACK_STATIC) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_STACK) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_STACK_REMOVE) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_STACK_REMOVEALL) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_CONTENTSPAGE_PARAMETER) -> SetFocus();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsContentsPage::OnKey0()
{
  Key(0);
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsContentsPage::OnKey1()
{
  Key(1);
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsContentsPage::OnKey2()
{
  Key(2);
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsContentsPage::OnKey3()
{
  Key(3);
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsContentsPage::OnKey4()
{
  Key(4);
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsContentsPage::OnKey5()
{
  Key(5);
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsContentsPage::OnKey6()
{
  Key(6);
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsContentsPage::OnKey7()
{
  Key(7);
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsContentsPage::OnKey8()
{
  Key(8);
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsContentsPage::OnKey9()
{
  Key(9);
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsContentsPage::OnKeyPoint()
{
  Key(STRING(IDS_POD_KEY_POINT));
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsContentsPage::OnKeyDiv()
{
  Key(STRING(IDS_POD_OPERATOR_DIV));
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsContentsPage::OnKeyMul()
{
  Key(STRING(IDS_POD_OPERATOR_MUL));
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsContentsPage::OnKeySub()
{
  Key(STRING(IDS_POD_OPERATOR_SUB));
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsContentsPage::OnKeyAdd()
{
  Key(STRING(IDS_POD_OPERATOR_ADD));
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsContentsPage::OnKeyChg()
{
  Key(STRING(IDS_POD_OPERATOR_CHG));
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsContentsPage::OnKeySin()
{
  Key(STRING(IDS_POD_MATHFUNCTION_SIN));
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsContentsPage::OnKeyCos()
{
  Key(STRING(IDS_POD_MATHFUNCTION_COS));
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsContentsPage::OnKeyTan()
{
  Key(STRING(IDS_POD_MATHFUNCTION_TAN));
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsContentsPage::OnKeyASin()
{
  Key(STRING(IDS_POD_MATHFUNCTION_ASIN));
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsContentsPage::OnKeyACos()
{
  Key(STRING(IDS_POD_MATHFUNCTION_ACOS));
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsContentsPage::OnKeyATan()
{
  Key(STRING(IDS_POD_MATHFUNCTION_ATAN));
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsContentsPage::OnKeyAbs()
{
  Key(STRING(IDS_POD_MATHFUNCTION_ABS));
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsContentsPage::OnKeyInt()
{
  Key(STRING(IDS_POD_MATHFUNCTION_INT));
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsContentsPage::OnKeySqrt()
{
  Key(STRING(IDS_POD_MATHFUNCTION_SQRT));
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsContentsPage::OnKeyPow2()
{
  Key(STRING(IDS_POD_MATHFUNCTION_POW2));
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsContentsPage::OnKeyPowY()
{
  Key(STRING(IDS_POD_MATHFUNCTION_POWY));
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsContentsPage::OnKeyLn()
{
  Key(STRING(IDS_POD_MATHFUNCTION_LN));
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsContentsPage::OnKeyLog()
{
  Key(STRING(IDS_POD_MATHFUNCTION_LOG));
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsContentsPage::OnKeyExp()
{
  Key(STRING(IDS_POD_MATHFUNCTION_EXP));
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsContentsPage::OnKeyPI()
{
  Key(STRING(IDS_POD_CONSTANT_PI));
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsContentsPage::OnKeyE()
{
  Key(STRING(IDS_POD_CONSTANT_E));
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsContentsPage::OnKeyEnter()
{
  Key(STRING(IDS_POD_KEY_ENTER));
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsContentsPage::OnSelchangeColor()
{
  m_cLayout[0].SetExpressionColor((SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_COLOR,CCB_FINDCOLOR,(WPARAM) -1,(LPARAM) ((m_cLayout[1].GetExpressionColor() != GetSysColor(COLOR_WINDOW)) ? m_cLayout[1].GetExpressionColor():GetDatabase() -> GetPODExpressionColor())) != SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_COLOR,CB_GETCURSEL)) ? (COLORREF) SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_COLOR,CCB_GETCOLOR,(WPARAM) SendDlgItemMessage(IDC_PODSETTINGS_CONTENTSPAGE_COLOR,CB_GETCURSEL)):m_cLayout[1].GetExpressionColor());
  GetDlgItem(IDOK) -> EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CPODSettingsFilteringPage property page

IMPLEMENT_DYNCREATE(CPODSettingsFilteringPage,CLocalePropertyPage)

CPODSettingsFilteringPage::CPODSettingsFilteringPage() : CLocalePropertyPage(CPODSettingsFilteringPage::IDD)
{
	//{{AFX_DATA_INIT(CPODSettingsFilteringPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CPODSettingsFilteringPage::Initialize()
{
  CPODOpenDialog  *pDialog;

  if (((pDialog = GetParentDialog() -> GetParentDialog()) && (pDialog -> GetFilterMode(m_nMode[0]) ||  GetParentDisplay() -> GetFilterMode(m_nMode[0])) && (pDialog -> GetFilterLimit(m_nLimit[0]) >= 0  ||  GetParentDisplay() -> GetFilterLimit(m_nLimit[0]) >= 0) && (pDialog -> GetFilterStatus(m_nStatus[0]) >= 0  ||  GetParentDisplay() -> GetFilterStatus(m_nStatus[0]) >= 0) && (pDialog -> GetFilterRange(m_tRange[0][0][0],m_tRange[0][0][1]) >= 0  ||  GetParentDisplay() -> GetFilterRange(m_tRange[0][0][0],m_tRange[0][0][1]) >= 0) && (pDialog -> GetFilterDailyRange(m_tDailyRange[0][0],m_tDailyRange[0][1]) >= 0  ||  GetParentDisplay() -> GetFilterDailyRange(m_tDailyRange[0][0],m_tDailyRange[0][1]) >= 0) && (pDialog -> GetFilterPeriodicalRange(m_tRange[0][1][0],m_tPeriodical[0],m_tRange[0][1][1]) >= 0  ||  GetParentDisplay() -> GetFilterPeriodicalRange(m_tRange[0][1][0],m_tPeriodical[0],m_tRange[0][1][1]) >= 0) && (pDialog -> GetFilterDigits(m_nDigits[0]) ||  GetParentDisplay() -> GetFilterDigits(m_nDigits[0])) && (pDialog -> GetFilterColors(m_nColors[0]) ||  GetParentDisplay() -> GetFilterColors(m_nColors[0]))) || (GetParentDisplay() -> GetFilterMode(m_nMode[0]) &&  GetParentDisplay() -> GetFilterLimit(m_nLimit[0]) >= 0  &&  GetParentDisplay() -> GetFilterStatus(m_nStatus[0]) >= 0  &&  GetParentDisplay() -> GetFilterRange(m_tRange[0][0][0],m_tRange[0][0][1]) >= 0  &&  GetParentDisplay() -> GetFilterDailyRange(m_tDailyRange[0][0],m_tDailyRange[0][1]) >= 0  &&  GetParentDisplay() -> GetFilterPeriodicalRange(m_tRange[0][1][0],m_tPeriodical[0],m_tRange[0][1][1]) >= 0  &&  GetParentDisplay() -> GetFilterDigits(m_nDigits[0]) &&  GetParentDisplay() -> GetFilterColors(m_nColors[0])))
  { m_nLimit[0] = m_nLimit[1] = ((m_nMode[1] = m_nMode[0]) & POD_FILTER_LIMIT) ? m_nLimit[0]:0;
    m_nStatus[0] = m_nStatus[1] = (m_nMode[0] & POD_FILTER_STATUS) ? m_nStatus[0]:0;
    m_tRange[1][0][0] = m_tRange[0][0][0] = (m_nMode[0] & POD_FILTER_RANGE) ? m_tRange[0][0][0]:0;
    m_tRange[1][0][1] = m_tRange[0][0][1] = (m_nMode[0] & POD_FILTER_RANGE) ? m_tRange[0][0][1]:0;
    m_tRange[0][1][0] = m_tRange[1][1][0] = (m_nMode[0] & POD_FILTER_PERIODICALRANGE) ? m_tRange[0][1][0]:0;
    m_tRange[0][1][1] = m_tRange[1][1][1] = (m_nMode[0] & POD_FILTER_PERIODICALRANGE) ? m_tRange[0][1][1]:0;
    m_tPeriodical[0] = m_tPeriodical[1] = (m_nMode[0] & POD_FILTER_PERIODICALRANGE) ? m_tPeriodical[0]:0;
    m_tDailyRange[0][0] = m_tDailyRange[1][0] = (m_nMode[0] & POD_FILTER_DAILYRANGE) ? m_tDailyRange[0][0]:0;
    m_tDailyRange[0][1] = m_tDailyRange[1][1] = (m_nMode[0] & POD_FILTER_DAILYRANGE) ? m_tDailyRange[0][1]:0;
    m_nColors[1].Copy(m_nColors[0]);
    m_nDigits[1] = m_nDigits[0];
    return TRUE;
  }
  return FALSE;
}

BOOL CPODSettingsFilteringPage::GetMode(UINT &nMode) CONST
{
  nMode = m_nMode[0];
  return Check(FALSE);
}

BOOL CPODSettingsFilteringPage::GetLimit(UINT &nLimit) CONST
{
  if (m_nMode[0] & POD_FILTER_LIMIT)
  { nLimit = m_nLimit[0];
    return Check(FALSE);
  }
  return FALSE;
}

BOOL CPODSettingsFilteringPage::GetDigits(UINT &nDigits) CONST
{
  nDigits = m_nDigits[0];
  return Check(FALSE);
}

BOOL CPODSettingsFilteringPage::GetStatus(UINT &nStatus) CONST
{
  if (m_nMode[0] & POD_FILTER_STATUS)
  { nStatus = m_nStatus[0];
    return Check(FALSE);
  }
  return FALSE;
}

BOOL CPODSettingsFilteringPage::GetRange(CTimeKey &tStartTime,CTimeKey &tStopTime) CONST
{
  if (m_nMode[0] & POD_FILTER_RANGE)
  { tStartTime = m_tRange[0][0][0];
    tStopTime = m_tRange[0][0][1];
    return Check(FALSE);
  }
  return FALSE;
}

BOOL CPODSettingsFilteringPage::GetDailyRange(CTimeSpan &tStartTime,CTimeSpan &tStopTime) CONST
{
  if (m_nMode[0] & POD_FILTER_DAILYRANGE)
  { tStartTime = m_tDailyRange[0][0];
    tStopTime = m_tDailyRange[0][1];
    return Check(FALSE);
  }
  return FALSE;
}

BOOL CPODSettingsFilteringPage::GetPeriodicalRange(CTimeKey &tStartTime,CTimeSpan &tInterval,CTimeKey &tStopTime) CONST
{
  if (m_nMode[0] & POD_FILTER_PERIODICALRANGE)
  { tStartTime = m_tRange[0][1][0];
    tStopTime = m_tRange[0][1][1];
    tInterval = m_tPeriodical[0];
    return Check(FALSE);
  }
  return FALSE;
}

BOOL CPODSettingsFilteringPage::GetColors(CUIntArray &nColors) CONST
{
  nColors.Copy(m_nColors[0]);
  return Check(FALSE);
}

CPODSettingsDialog *CPODSettingsFilteringPage::GetParentDialog() CONST
{
  return((CPODSettingsDialog *) CLocalePropertyPage::GetParent());
}

CPODWnd *CPODSettingsFilteringPage::GetParentDisplay() CONST
{
  return((CPODWnd *) GetParentDialog() -> GetParentDisplay());
}

BOOL CPODSettingsFilteringPage::EnumFilterStatus()
{
  return((SendDlgItemMessage(IDC_PODSETTINGS_FILTERINGPAGE_COLORS_STATUS,CB_INSERTSTRING,(WPARAM) -1,(LPARAM) STRING(IDS_PODSETTINGS_FILTERINGPAGE_NOOOL)) >= 0  &&  SendDlgItemMessage(IDC_PODSETTINGS_FILTERINGPAGE_COLORS_STATUS,CB_INSERTSTRING,(WPARAM) -1,(LPARAM) STRING(IDS_PODSETTINGS_FILTERINGPAGE_SOFTOOL)) >= 0  &&  SendDlgItemMessage(IDC_PODSETTINGS_FILTERINGPAGE_COLORS_STATUS,CB_INSERTSTRING,(WPARAM) -1,(LPARAM) STRING(IDS_PODSETTINGS_FILTERINGPAGE_HARDOOL)) >= 0  &&  SendDlgItemMessage(IDC_PODSETTINGS_FILTERINGPAGE_COLORS_STATUS,CB_INSERTSTRING,(WPARAM) -1,(LPARAM) STRING(IDS_PODSETTINGS_FILTERINGPAGE_DELTAOOL)) >= 0  &&  SendDlgItemMessage(IDC_PODSETTINGS_FILTERINGPAGE_COLORS_STATUS,CB_INSERTSTRING,(WPARAM) -1,(LPARAM) STRING(IDS_PODSETTINGS_FILTERINGPAGE_CONSISTENCYOOL)) >= 0) ? TRUE:FALSE);
}

UINT CPODSettingsFilteringPage::GetFilterStatus() CONST
{
  UINT  nStatus;

  nStatus = (IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_NOOOL)) ? TMPARAMETER_STATUS_NOLIMIT:0;
  nStatus |= (IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_SOFTOOL)) ? TMPARAMETER_STATUS_SOFTLIMIT:0;
  nStatus |= (IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_HARDOOL)) ? TMPARAMETER_STATUS_HARDLIMIT:0;
  nStatus |= (IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_DELTAOOL)) ? TMPARAMETER_STATUS_DELTALIMIT:0;
  nStatus |= (IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_CONSISTENCYOOL)) ? TMPARAMETER_STATUS_CONSISTENCYLIMIT:0;
  nStatus |= (IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_VALID)) ? TMPARAMETER_STATUS_VALID:0;
  nStatus |= (IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_INVALID)) ? TMPARAMETER_STATUS_INVALID:0;
  nStatus |= (IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_GOOD)) ? TMPARAMETER_STATUS_GOOD:0;
  nStatus |= (IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_BAD)) ? TMPARAMETER_STATUS_BAD:0;
  return nStatus;
}

VOID CPODSettingsFilteringPage::ShowFilterInfo()
{
  CTimeKey  tTimeKey;

  CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL,(m_nMode[0] & POD_FILTER_RANGE) ? TRUE:FALSE);
  CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DAILY,(m_nMode[0] & POD_FILTER_DAILYRANGE) ? TRUE:FALSE);
  CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL,(m_nMode[0] & POD_FILTER_PERIODICALRANGE) ? TRUE:FALSE);
  CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_START,(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL) &&  m_tRange[0][1][0].GetTime() > 0) ? TRUE:FALSE);
  CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOP,(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL) &&  m_tRange[0][1][1].GetTime() > 0) ? TRUE:FALSE);
  CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_LIMITVALUES,(m_nLimit[0] > 0) ? TRUE:FALSE);
  CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DIGITS,(m_nDigits[0] > 0) ? TRUE:FALSE);
  CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS,(m_nStatus[0] != 0) ? TRUE:FALSE);
  CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_NOOOL,(m_nStatus[0] & TMPARAMETER_STATUS_NOLIMIT) ? TRUE:FALSE);
  CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_SOFTOOL,(m_nStatus[0] & TMPARAMETER_STATUS_SOFTLIMIT) ? TRUE:FALSE);
  CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_HARDOOL,(m_nStatus[0] & TMPARAMETER_STATUS_HARDLIMIT) ? TRUE:FALSE);
  CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_DELTAOOL,(m_nStatus[0] & TMPARAMETER_STATUS_DELTALIMIT) ? TRUE:FALSE);
  CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_CONSISTENCYOOL,(m_nStatus[0] & TMPARAMETER_STATUS_CONSISTENCYLIMIT) ? TRUE:FALSE);
  CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_VALID,(m_nStatus[0] & TMPARAMETER_STATUS_VALID) ? TRUE:FALSE);
  CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_INVALID,(m_nStatus[0] & TMPARAMETER_STATUS_INVALID) ? TRUE:FALSE);
  CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY,(m_nStatus[0] & (TMPARAMETER_STATUS_GOOD | TMPARAMETER_STATUS_BAD)) ? TRUE:FALSE);
  CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_GOOD,(m_nStatus[0] & TMPARAMETER_STATUS_GOOD) ? TRUE:FALSE);
  CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_BAD,(m_nStatus[0] & TMPARAMETER_STATUS_BAD) ? TRUE:FALSE);
  CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_SHOW,(m_nMode[0] & (POD_FILTER_UPDATES | POD_FILTER_CHANGES)) ? TRUE:FALSE);
  CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_SHOW_UPDATES,(m_nMode[0] & POD_FILTER_UPDATES) ? TRUE:FALSE);
  CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_SHOW_CHANGES,(m_nMode[0] & POD_FILTER_CHANGES) ? TRUE:FALSE);
  Timespinbox_SetTime(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STARTTIME),(m_tRange[0][0][0].GetTime() > 0) ? m_tRange[0][0][0]:tTimeKey);
  Timespinbox_SetTime(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STOPTIME),(m_tRange[0][0][1].GetTime() > 0) ? m_tRange[0][0][1]:tTimeKey);
  Timespinbox_SetTime(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STARTTIME),(m_tDailyRange[0][0].GetTotalSeconds() > 0) ? (SECONDSPERDAY*(tTimeKey.GetTime()/SECONDSPERDAY)+m_tDailyRange[0][0].GetTotalSeconds()):tTimeKey);
  Timespinbox_SetTime(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STOPTIME),(m_tDailyRange[0][1].GetTotalSeconds() > 0) ? (SECONDSPERDAY*(tTimeKey.GetTime()/SECONDSPERDAY)+m_tDailyRange[0][1].GetTotalSeconds()):tTimeKey);
  Timespinbox_SetTime(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STARTTIME),(m_tRange[0][1][0].GetTime() > 0) ? m_tRange[0][1][0]:tTimeKey);
  Timespinbox_SetTime(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOPTIME),(m_tRange[0][1][1].GetTime() > 0) ? m_tRange[0][1][1]:tTimeKey);
  Spinbox_SetRange(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_INTERVAL),PODSETTINGSFILTERINGPAGE_MINIMUMINTERVAL,PODSETTINGSFILTERINGPAGE_MAXIMUMINTERVAL);
  Spinbox_SetRange(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_LIMITVALUES_NUMBER),PODSETTINGSFILTERINGPAGE_MINIMUMVALUES,PODSETTINGSFILTERINGPAGE_MAXIMUMVALUES);
  Spinbox_SetRange(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DIGITS_NUMBER),PODSETTINGSFILTERINGPAGE_MINIMUMDIGITS,PODSETTINGSFILTERINGPAGE_MAXIMUMDIGITS);
  Spinbox_SetPos(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_INTERVAL),m_tPeriodical[0].GetTotalMinutes());
  Spinbox_SetPos(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_LIMITVALUES_NUMBER),m_nLimit[0]);
  Spinbox_SetPos(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DIGITS_NUMBER),m_nDigits[0]);
  SendDlgItemMessage(IDC_PODSETTINGS_FILTERINGPAGE_COLORS_COLOR,CCB_SELECTCOLOR,(WPARAM) -1,(m_nColors[0].GetSize() > 0) ? (LPARAM) m_nColors[0].GetAt(0):(LPARAM) VGA_COLOR_GRAY);
  SendDlgItemMessage(IDC_PODSETTINGS_FILTERINGPAGE_COLORS_STATUS,CB_SETCURSEL);
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_DETAILS) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATIC) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STARTTIME) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STATIC) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STOPTIME) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DAILY) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STARTTIME) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DAILY));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STATIC) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DAILY));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STOPTIME) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DAILY));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_INTERVAL) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_INTERVAL_STATIC) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_START) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STARTTIME) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL) &&  IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_START));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOP) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOPTIME) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL) &&  IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOP));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_LIMITVALUES) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_LIMITVALUES_NUMBER) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_LIMITVALUES));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_LIMITVALUES_STATIC) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_LIMITVALUES));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DIGITS) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DIGITS_NUMBER) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DIGITS));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_NOOOL) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_SOFTOOL) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_HARDOOL) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_DELTAOOL) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_CONSISTENCYOOL) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_VALID) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_INVALID) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_GOOD) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_BAD) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_SHOW) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_SHOW_UPDATES) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_SHOW));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_SHOW_CHANGES) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_SHOW));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_COLORS) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_COLORS_STATUS_STATIC) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_COLORS_STATUS) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_COLORS_COLOR_STATIC) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_COLORS_COLOR) -> EnableWindow();
}

BOOL CPODSettingsFilteringPage::IsModified(BOOL bAll) CONST
{
  return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (m_nMode[0] != m_nMode[1] ||  m_nLimit[0] != m_nLimit[1] ||  m_nStatus[0] != m_nStatus[1] ||  m_tRange[0][0][0] != m_tRange[1][0][0] ||  m_tRange[0][0][1] != m_tRange[1][0][1] ||  m_tRange[0][1][0] != m_tRange[1][1][0] ||  m_tRange[0][1][1] != m_tRange[1][1][1] ||  m_tDailyRange[0][0] != m_tDailyRange[1][0] ||  m_tDailyRange[0][1] != m_tDailyRange[1][1] ||  m_tPeriodical[0] != m_tPeriodical[1] ||  m_nDigits[0] != m_nDigits[1] ||  m_nColors[0].GetSize() != m_nColors[1].GetSize() ||  memcmp(m_nColors[0].GetData(),m_nColors[1].GetData(),m_nColors[0].GetSize()*sizeof(UINT))):CLocalePropertyPage::IsModified()):FALSE);
}

BOOL CPODSettingsFilteringPage::Check(BOOL bAll) CONST
{
  return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (!IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS) ||  IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_NOOOL) ||  IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_SOFTOOL) ||  IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_HARDOOL) ||  IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_DELTAOOL) ||  IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_CONSISTENCYOOL)):CLocalePropertyPage::Check()):TRUE);
}

void CPODSettingsFilteringPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPODSettingsFilteringPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CPODSettingsFilteringPage::PostNcDestroy()
{
  m_nColors[0].RemoveAll();
  m_nColors[1].RemoveAll();
  CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CPODSettingsFilteringPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CPODSettingsFilteringPage)
	ON_BN_CLICKED(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL,OnFilterByTime)
	ON_BN_CLICKED(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DAILY,OnFilterByDailyTime)
	ON_BN_CLICKED(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL,OnFilterByPeriodicalTime)
	ON_BN_CLICKED(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_START,OnFilterByPeriodicalStartTime)
	ON_BN_CLICKED(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOP,OnFilterByPeriodicalStopTime)
	ON_BN_CLICKED(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_LIMITVALUES,OnFilterByLimit)
	ON_BN_CLICKED(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DIGITS,OnFilterByDigits)
	ON_BN_CLICKED(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS,OnFilterByStatus)
	ON_BN_CLICKED(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_NOOOL,OnFilterByStatusValue)
	ON_BN_CLICKED(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_SOFTOOL,OnFilterByStatusValue)
	ON_BN_CLICKED(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_HARDOOL,OnFilterByStatusValue)
	ON_BN_CLICKED(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_DELTAOOL,OnFilterByStatusValue)
	ON_BN_CLICKED(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_CONSISTENCYOOL,OnFilterByStatusValue)
	ON_BN_CLICKED(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_VALID,OnFilterByStatusValue)
	ON_BN_CLICKED(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_INVALID,OnFilterByStatusValue)
	ON_BN_CLICKED(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY,OnFilterByQuality)
	ON_BN_CLICKED(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_GOOD,OnFilterByQualityValue)
	ON_BN_CLICKED(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_BAD,OnFilterByQualityValue)
	ON_BN_CLICKED(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_SHOW,OnFilterByShow)
	ON_BN_CLICKED(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_SHOW_UPDATES,OnFilterByShowUpdates)
	ON_BN_CLICKED(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_SHOW_CHANGES,OnFilterByShowChanges)
	ON_CBN_SELCHANGE(IDC_PODSETTINGS_FILTERINGPAGE_COLORS_STATUS,OnSelchangeFilterColorLocation)
	ON_CBN_SELCHANGE(IDC_PODSETTINGS_FILTERINGPAGE_COLORS_COLOR,OnSelchangeFilterColor)
	ON_CONTROL(SBXN_CHANGE,IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_INTERVAL,OnSpinchangeFilterPeriodicalInterval)
	ON_CONTROL(SBXN_CHANGE,IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_LIMITVALUES_NUMBER,OnSpinchangeFilterLimit)
	ON_CONTROL(SBXN_CHANGE,IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DIGITS_NUMBER,OnSpinchangeFilterDigits)
	ON_CONTROL(TSBXN_CHANGE,IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STARTTIME,OnSpinchangeFilterStartTime)
	ON_CONTROL(TSBXN_CHANGE,IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STOPTIME,OnSpinchangeFilterStopTime)
	ON_CONTROL(TSBXN_CHANGE,IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STARTTIME,OnSpinchangeFilterDailyStartTime)
	ON_CONTROL(TSBXN_CHANGE,IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STOPTIME,OnSpinchangeFilterDailyStopTime)
	ON_CONTROL(TSBXN_CHANGE,IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STARTTIME,OnSpinchangeFilterPeriodicalStartTime)
	ON_CONTROL(TSBXN_CHANGE,IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOPTIME,OnSpinchangeFilterPeriodicalStopTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPODSettingsFilteringPage message handlers

BOOL CPODSettingsFilteringPage::OnInitDialog() 
{
  CHourglassCursor  cCursor;

  CLocalePropertyPage::OnInitDialog();
  EnumFilterStatus();
  ShowFilterInfo();
  return TRUE;
}

void CPODSettingsFilteringPage::OnFilterByTime()
{
  CTimeKey  tTimeKey;

  m_nMode[0] = (IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL)) ? (m_nMode[0] | POD_FILTER_RANGE):(m_nMode[0] & ~POD_FILTER_RANGE);
  m_tRange[0][0][0] = (IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL)) ? tTimeKey.GetTime():0;
  m_tRange[0][0][1] = (IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL)) ? (tTimeKey.GetTime()+SECONDSPERMINUTE*PODSETTINGSFILTERINGPAGE_DEFAULTRANGE):0;
  Timespinbox_SetTime(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STARTTIME),(m_tRange[0][0][0].GetTime() > 0) ? m_tRange[0][0][0]:tTimeKey);
  Timespinbox_SetTime(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STOPTIME),(m_tRange[0][0][1].GetTime() > 0) ? m_tRange[0][0][1]:tTimeKey);
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STARTTIME) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STATIC) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STOPTIME) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STARTTIME) -> SetFocus();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsFilteringPage::OnFilterByDailyTime()
{
  CTimeKey  tTimeKey;

  m_nMode[0] = (IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DAILY)) ? (m_nMode[0] | POD_FILTER_DAILYRANGE):(m_nMode[0] & ~POD_FILTER_DAILYRANGE);
  m_tDailyRange[0][0] = (IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DAILY)) ? PODSETTINGSFILTERINGPAGE_DEFAULTDAILYSTARTTIME:0;
  m_tDailyRange[0][1] = (IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DAILY)) ? PODSETTINGSFILTERINGPAGE_DEFAULTDAILYSTOPTIME:0;
  Timespinbox_SetTime(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STARTTIME),CTimeKey(SECONDSPERDAY*(tTimeKey.GetTime()/SECONDSPERDAY)+m_tDailyRange[0][0].GetTotalSeconds()));
  Timespinbox_SetTime(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STOPTIME),CTimeKey(SECONDSPERDAY*(tTimeKey.GetTime()/SECONDSPERDAY)+m_tDailyRange[0][1].GetTotalSeconds()));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STARTTIME) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DAILY));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STATIC) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DAILY));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STOPTIME) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DAILY));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STARTTIME) -> SetFocus();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsFilteringPage::OnFilterByPeriodicalTime()
{
  m_nMode[0] = (IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL)) ? (m_nMode[0] | POD_FILTER_PERIODICALRANGE):(m_nMode[0] & ~POD_FILTER_PERIODICALRANGE);
  m_tPeriodical[0] = (IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL)) ? (SECONDSPERMINUTE*PODSETTINGSFILTERINGPAGE_DEFAULTINTERVAL):0;
  m_tRange[0][1][0] = m_tRange[0][1][1] = (IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL)) ? 0:0;
  Spinbox_SetPos(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_INTERVAL),PODSETTINGSFILTERINGPAGE_DEFAULTINTERVAL);
  CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_START,FALSE);
  CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOP,FALSE);
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_INTERVAL) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_INTERVAL_STATIC) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_START) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STARTTIME) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOP) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOPTIME) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_INTERVAL) -> SetFocus();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsFilteringPage::OnFilterByPeriodicalStartTime()
{
  CTimeKey  tTimeKey;

  m_tRange[0][1][0] = (IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_START)) ? tTimeKey.GetTime():0;
  Timespinbox_SetTime(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STARTTIME),(m_tRange[0][1][0].GetTime() > 0) ? m_tRange[0][1][0]:tTimeKey);
  Timespinbox_SetTime(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOPTIME),(m_tRange[0][1][0] >= m_tRange[0][1][1] &&  m_tRange[0][1][0] > 0) ? (m_tRange[0][1][0].GetTime()+1):((m_tRange[0][1][1].GetTime() > 0) ? m_tRange[0][1][1]:tTimeKey));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STARTTIME) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_START));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STARTTIME) -> SetFocus();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsFilteringPage::OnFilterByPeriodicalStopTime()
{
  CTimeKey  tTimeKey;

  m_tRange[0][1][1] = (IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOP)) ? (tTimeKey.GetTime()+SECONDSPERMINUTE*PODSETTINGSFILTERINGPAGE_DEFAULTRANGE):0;
  Timespinbox_SetTime(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOPTIME),(m_tRange[0][1][1].GetTime() > 0) ? m_tRange[0][1][1]:tTimeKey);
  Timespinbox_SetTime(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STARTTIME),(m_tRange[0][1][0] >= m_tRange[0][1][1] &&  m_tRange[0][1][1] > 0) ? (m_tRange[0][1][1].GetTime()-1):((m_tRange[0][1][0].GetTime() > 0) ? m_tRange[0][1][0]:tTimeKey));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOPTIME) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOP));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOPTIME) -> SetFocus();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsFilteringPage::OnFilterByLimit()
{
  m_nMode[0] = (IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_LIMITVALUES)) ? (m_nMode[0] | POD_FILTER_LIMIT):(m_nMode[0] & ~POD_FILTER_LIMIT);
  m_nLimit[0] = (IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_LIMITVALUES)) ? PODSETTINGSFILTERINGPAGE_DEFAULTVALUES:0;
  Spinbox_SetPos(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_LIMITVALUES_NUMBER),PODSETTINGSFILTERINGPAGE_DEFAULTVALUES);
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_LIMITVALUES_NUMBER) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_LIMITVALUES));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_LIMITVALUES_STATIC) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_LIMITVALUES));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_LIMITVALUES_NUMBER) -> SetFocus();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsFilteringPage::OnFilterByDigits()
{
  m_nDigits[0] = (IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DIGITS)) ? PODSETTINGSFILTERINGPAGE_DEFAULTDIGITS:0;
  Spinbox_SetPos(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DIGITS_NUMBER),PODSETTINGSFILTERINGPAGE_DEFAULTDIGITS);
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DIGITS_NUMBER) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DIGITS));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DIGITS_NUMBER) -> SetFocus();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsFilteringPage::OnFilterByStatus()
{
  m_nMode[0] = (IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS) ||  IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY)) ? (m_nMode[0] | POD_FILTER_STATUS):(m_nMode[0] & ~POD_FILTER_STATUS);
  m_nStatus[0] = (IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS)) ? (TMPARAMETER_STATUS_NOLIMIT | TMPARAMETER_STATUS_VALID | (GetFilterStatus() & (TMPARAMETER_STATUS_GOOD | TMPARAMETER_STATUS_BAD))):(GetFilterStatus() & (TMPARAMETER_STATUS_GOOD | TMPARAMETER_STATUS_BAD));
  CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_NOOOL,IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS));
  CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_SOFTOOL,FALSE);
  CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_HARDOOL,FALSE);
  CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_DELTAOOL,FALSE);
  CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_CONSISTENCYOOL,FALSE);
  CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_INVALID,FALSE);
  CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_VALID,IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_NOOOL) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_SOFTOOL) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_HARDOOL) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_DELTAOOL) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_CONSISTENCYOOL) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_VALID) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_INVALID) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS));
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsFilteringPage::OnFilterByStatusValue()
{
  if ((!IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_NOOOL) &&  !IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_SOFTOOL) &&  !IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_HARDOOL) &&  !IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_DELTAOOL) &&  !IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_CONSISTENCYOOL)) || (!IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_VALID) &&  !IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_INVALID)))
  { CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS,FALSE);
    CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_NOOOL,FALSE);
    CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_SOFTOOL,FALSE);
    CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_HARDOOL,FALSE);
    CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_DELTAOOL,FALSE);
    CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_CONSISTENCYOOL,FALSE);
    CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_VALID,FALSE);
    CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_INVALID,FALSE);
    GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_NOOOL) -> EnableWindow(FALSE);
    GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_SOFTOOL) -> EnableWindow(FALSE);
    GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_HARDOOL) -> EnableWindow(FALSE);
    GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_DELTAOOL) -> EnableWindow(FALSE);
    GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_CONSISTENCYOOL) -> EnableWindow(FALSE);
    GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_VALID) -> EnableWindow(FALSE);
    GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS_INVALID) -> EnableWindow(FALSE);
  }
  m_nStatus[0] = GetFilterStatus();
  m_nMode[0] = (IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS) ||  IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY)) ? (m_nMode[0] | POD_FILTER_STATUS):(m_nMode[0] & ~POD_FILTER_STATUS);
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsFilteringPage::OnFilterByQuality()
{
  m_nMode[0] = (IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS) ||  IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY)) ? (m_nMode[0] | POD_FILTER_STATUS):(m_nMode[0] & ~POD_FILTER_STATUS);
  m_nStatus[0] = (IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY)) ? ((GetFilterStatus() & (TMPARAMETER_STATUS_NOLIMIT | TMPARAMETER_STATUS_SOFTLIMIT | TMPARAMETER_STATUS_HARDLIMIT | TMPARAMETER_STATUS_DELTALIMIT | TMPARAMETER_STATUS_CONSISTENCYLIMIT | TMPARAMETER_STATUS_VALID | TMPARAMETER_STATUS_INVALID)) | TMPARAMETER_STATUS_GOOD):(GetFilterStatus() & (TMPARAMETER_STATUS_NOLIMIT | TMPARAMETER_STATUS_SOFTLIMIT | TMPARAMETER_STATUS_HARDLIMIT | TMPARAMETER_STATUS_DELTALIMIT | TMPARAMETER_STATUS_CONSISTENCYLIMIT | TMPARAMETER_STATUS_VALID | TMPARAMETER_STATUS_INVALID));
  CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_GOOD,IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY));
  CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_BAD,FALSE);
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_GOOD) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_BAD) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY));
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsFilteringPage::OnFilterByQualityValue()
{
  m_nStatus[0] = GetFilterStatus();
  m_nMode[0] = (IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_STATUS) ||  IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_GOOD) ||  IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_BAD)) ? (m_nMode[0] | POD_FILTER_STATUS):(m_nMode[0] & ~POD_FILTER_STATUS);
  CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY,IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_GOOD) ||  IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_BAD));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_GOOD) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY_BAD) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_QUALITY));
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsFilteringPage::OnFilterByShow()
{
  m_nMode[0] = (IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_SHOW)) ? (m_nMode[0] | POD_FILTER_UPDATES):(m_nMode[0] & ~(POD_FILTER_UPDATES | POD_FILTER_CHANGES));
  CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_SHOW_UPDATES,IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_SHOW));
  CheckDlgButton(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_SHOW_CHANGES,FALSE);
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_SHOW_UPDATES) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_SHOW));
  GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_SHOW_CHANGES) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_SHOW));
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsFilteringPage::OnFilterByShowUpdates()
{
  m_nMode[0] = (m_nMode[0] | POD_FILTER_UPDATES) & ~POD_FILTER_CHANGES;
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsFilteringPage::OnFilterByShowChanges()
{
  m_nMode[0] = (m_nMode[0] | POD_FILTER_CHANGES) & ~POD_FILTER_UPDATES;
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsFilteringPage::OnSpinchangeFilterStartTime()
{
  CTimeKey  tStartTime;
  CTimeKey  tStopTime;

  for (tStartTime = Timespinbox_GetTime(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STARTTIME)),tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STOPTIME)); tStartTime >= tStopTime; )
  { Timespinbox_SetTime(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STOPTIME),(tStopTime=tStartTime.GetTime()+1));
    break;
  }
  m_tRange[0][0][0] = tStartTime;
  m_tRange[0][0][1] = tStopTime;
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsFilteringPage::OnSpinchangeFilterStopTime()
{
  CTimeKey  tStartTime;
  CTimeKey  tStopTime;

  for (tStartTime = Timespinbox_GetTime(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STARTTIME)),tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STOPTIME)); tStartTime >= tStopTime; )
  { Timespinbox_SetTime(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_INTERVAL_STARTTIME),(tStartTime=max(tStopTime.GetTime()-1,0)));
    break;
  }
  m_tRange[0][0][0] = tStartTime;
  m_tRange[0][0][1] = tStopTime;
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsFilteringPage::OnSpinchangeFilterDailyStartTime()
{
  m_tDailyRange[0][0] = Timespinbox_GetTime(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STARTTIME)).GetTime()%SECONDSPERDAY;
  m_tDailyRange[0][1] = Timespinbox_GetTime(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STOPTIME)).GetTime()%SECONDSPERDAY;
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsFilteringPage::OnSpinchangeFilterDailyStopTime()
{
  m_tDailyRange[0][0] = Timespinbox_GetTime(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STARTTIME)).GetTime()%SECONDSPERDAY;
  m_tDailyRange[0][1] = Timespinbox_GetTime(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DAILY_STOPTIME)).GetTime()%SECONDSPERDAY;
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsFilteringPage::OnSpinchangeFilterPeriodicalInterval()
{
  for ( ; IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL); )
  { if (IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOP))
    { m_tPeriodical[0] = SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_INTERVAL));
      m_tRange[0][1][1] = (m_tRange[0][1][0]+m_tPeriodical[0] > m_tRange[0][1][1]) ? (m_tRange[0][1][0].GetTime()+m_tPeriodical[0].GetTotalSeconds()):m_tRange[0][1][1].GetTime();
      Timespinbox_SetTime(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOPTIME),m_tRange[0][1][1]);
      break;
    }
    m_tPeriodical[0] = SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_INTERVAL));
    break;
  }
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsFilteringPage::OnSpinchangeFilterPeriodicalStartTime()
{
  CTimeKey  tTime;

  if (IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOP))
  { Timespinbox_SetTime(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOPTIME),m_tRange[0][1][1]);
    m_tRange[0][1][1] = ((tTime = Timespinbox_GetTime(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STARTTIME)))+m_tPeriodical[0].GetTotalSeconds() > m_tRange[0][1][1].GetTime()) ? (tTime.GetTime()+m_tPeriodical[0].GetTotalSeconds()):m_tRange[0][1][1];
    m_tRange[0][1][0] = tTime;
  }
  else
  { tTime = Timespinbox_GetTime(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STARTTIME));
    m_tRange[0][1][0] = tTime;
  }
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsFilteringPage::OnSpinchangeFilterPeriodicalStopTime()
{
  CTimeKey  tTime;

  if (IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_START))
  { Timespinbox_SetTime(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STARTTIME),m_tRange[0][1][0]);
    m_tRange[0][1][0] = ((tTime = Timespinbox_GetTime(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOPTIME))) < m_tRange[0][1][0]+m_tPeriodical[0].GetTotalSeconds()) ? (tTime.GetTime()-m_tPeriodical[0].GetTotalSeconds()):m_tRange[0][1][0];
    m_tRange[0][1][1] = tTime;
  }
  else
  { tTime = Timespinbox_GetTime(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_PERIODICAL_STOPTIME));
    m_tRange[0][1][1] = tTime;
  }
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsFilteringPage::OnSpinchangeFilterLimit()
{
  m_nLimit[0] = (IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_LIMITVALUES)) ? (UINT) Spinbox_GetPos(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_LIMITVALUES_NUMBER)):0;
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsFilteringPage::OnSpinchangeFilterDigits()
{
  m_nDigits[0] = (IsDlgButtonChecked(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DIGITS)) ? (UINT) Spinbox_GetPos(GetDlgItem(IDC_PODSETTINGS_FILTERINGPAGE_OPTIONS_DIGITS_NUMBER)):0;
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsFilteringPage::OnSelchangeFilterColorLocation()
{
  INT  nIndex;

  SendDlgItemMessage(IDC_PODSETTINGS_FILTERINGPAGE_COLORS_COLOR,CCB_SELECTCOLOR,(WPARAM) -1,((nIndex=(INT) SendDlgItemMessage(IDC_PODSETTINGS_FILTERINGPAGE_COLORS_STATUS,CB_GETCURSEL)) < m_nColors[0].GetSize()) ? (LPARAM) m_nColors[0].GetAt(nIndex):(LPARAM) VGA_COLOR_GRAY);
}

void CPODSettingsFilteringPage::OnSelchangeFilterColor()
{
  INT  nIndex;

  for (nIndex = (INT) SendDlgItemMessage(IDC_PODSETTINGS_FILTERINGPAGE_COLORS_STATUS,CB_GETCURSEL); nIndex < m_nColors[0].GetSize(); )
  { m_nColors[0].SetAt(nIndex,(UINT) SendDlgItemMessage(IDC_PODSETTINGS_FILTERINGPAGE_COLORS_COLOR,CCB_GETCOLOR,(WPARAM) SendDlgItemMessage(IDC_PODSETTINGS_FILTERINGPAGE_COLORS_COLOR,CB_GETCURSEL)));
    break;
  }
  GetDlgItem(IDOK) -> EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CPODSettingsRetrievingPage property page

IMPLEMENT_DYNCREATE(CPODSettingsRetrievingPage,CLocalePropertyPage)

CPODSettingsRetrievingPage::CPODSettingsRetrievingPage() : CLocalePropertyPage(CPODSettingsRetrievingPage::IDD)
{
	//{{AFX_DATA_INIT(CPODSettingsRetrievingPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CPODSettingsRetrievingPage::Initialize()
{
  CPODOpenDialog  *pDialog;

  if (((pDialog = GetParentDialog() -> GetParentDialog()) &&  pDialog -> GetRetrieveFileName(m_szFileName[0])) ||  GetParentDisplay() -> GetRetrieveFileName(m_szFileName[0]))
  { m_szFileName[1] = m_szFileName[0];
    return TRUE;
  }
  return FALSE;
}

BOOL CPODSettingsRetrievingPage::GetDataSourceFileName(CString &szFileName) CONST
{
  szFileName = m_szFileName[0];
  return Check(FALSE);
}

CPODSettingsDialog *CPODSettingsRetrievingPage::GetParentDialog() CONST
{
  return((CPODSettingsDialog *) CLocalePropertyPage::GetParent());
}

CPODWnd *CPODSettingsRetrievingPage::GetParentDisplay() CONST
{
  return((CPODWnd *) GetParentDialog() -> GetParentDisplay());
}

VOID CPODSettingsRetrievingPage::EnumDataSources()
{
  INT  nFile;
  INT  nFiles;
  CHistoryStoreFile  cFile;
  CHistoryStoreFiles  pFiles;
  CUIntArray  nOptions;

  for (nFile = 0,nFiles = GetTMService() -> GetTMHistoryFiles(HISTORYFILE_TYPE_RETRIEVE,pFiles),GetTMService() -> GetDefaultTMHistoryFile(HISTORYFILE_TYPE_RETRIEVE,cFile),m_szFileName[0] = (pFiles.Find(m_szFileName[0]) < 0) ? cFile.GetFileName():m_szFileName[0]; nFile < nFiles  || (!nFiles  &&  !nFile  &&  !m_szFileName[0].IsEmpty()); nFile++)
  { SendDlgItemMessage(IDC_PODSETTINGS_RETRIEVINGPAGE_DATASOURCE,CB_INSERTSTRING,(WPARAM) -1,(LPARAM) ((nFiles > 0) ? (LPCTSTR) pFiles.GetAt(nFile) -> GetFileName():(LPCTSTR) m_szFileName[0]));
    continue;
  }
  SendDlgItemMessage(IDC_PODSETTINGS_RETRIEVINGPAGE_DATASOURCE,CB_SETCURSEL,(WPARAM) max(SendDlgItemMessage(IDC_PODSETTINGS_RETRIEVINGPAGE_DATASOURCE,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) m_szFileName[0]),0));
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_DATASOURCE) -> GetWindowText(m_szFileName[0]);
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_DATASOURCE) -> GetWindowText(m_szFileName[1]);
  ShowDataSourceInfo();
}

VOID CPODSettingsRetrievingPage::ShowDataSourceInfo()
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

  if (CheckDataSource(m_szFileName[0],szProduct,szCompany,szTrademark,szSpacecraft,szDataSourceType,szStartTime,szStopTime,szCreationTime,szDataSourceSize))
  { GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT) -> SetWindowText(szProduct);
    GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY) -> SetWindowText(szCompany);
    GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT) -> SetWindowText(szSpacecraft);
    GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE) -> SetWindowText(szDataSourceType);
    GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME) -> SetWindowText(szStartTime);
    GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME) -> SetWindowText(szStopTime);
    GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME) -> SetWindowText(szCreationTime);
    GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE) -> SetWindowText(szDataSourceSize);
  }
  else
  { GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT) -> SetWindowText((szProduct=EMPTYSTRING));
    GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY) -> SetWindowText((szCompany=EMPTYSTRING));
    GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT) -> SetWindowText((szSpacecraft=EMPTYSTRING));
    GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE) -> SetWindowText((szDataSourceType=EMPTYSTRING));
    GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME) -> SetWindowText((szStartTime=EMPTYSTRING));
    GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME) -> SetWindowText((szStopTime=EMPTYSTRING));
    GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME) -> SetWindowText((szCreationTime=EMPTYSTRING));
    GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE) -> SetWindowText((szDataSourceSize=EMPTYSTRING));
  }
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMMENTS) -> EnableWindow(szProduct.IsEmpty());
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMMENTS) -> ShowWindow((szProduct.IsEmpty()) ? SW_SHOWNA:SW_HIDE);
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT_STATIC) -> ShowWindow((!szProduct.IsEmpty()) ? SW_SHOWNA:SW_HIDE);
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT_STATIC) -> EnableWindow(!szProduct.IsEmpty());
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT) -> ShowWindow((!szProduct.IsEmpty()) ? SW_SHOWNA:SW_HIDE);
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_PRODUCT) -> EnableWindow(!szProduct.IsEmpty());
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY_STATIC) -> ShowWindow((!szCompany.IsEmpty()) ? SW_SHOWNA:SW_HIDE);
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY_STATIC) -> EnableWindow(!szCompany.IsEmpty());
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY) -> ShowWindow((!szCompany.IsEmpty()) ? SW_SHOWNA:SW_HIDE);
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_COMPANY) -> EnableWindow(!szCompany.IsEmpty());
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT_STATIC) -> ShowWindow((!szSpacecraft.IsEmpty()) ? SW_SHOWNA:SW_HIDE);
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT_STATIC) -> EnableWindow(!szSpacecraft.IsEmpty());
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT) -> ShowWindow((!szSpacecraft.IsEmpty()) ? SW_SHOWNA:SW_HIDE);
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SPACECRAFT) -> EnableWindow(!szSpacecraft.IsEmpty());
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE_STATIC) -> ShowWindow((!szDataSourceType.IsEmpty()) ? SW_SHOWNA:SW_HIDE);
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE_STATIC) -> EnableWindow(!szDataSourceType.IsEmpty());
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE) -> ShowWindow((!szDataSourceType.IsEmpty()) ? SW_SHOWNA:SW_HIDE);
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TYPE) -> EnableWindow(!szDataSourceType.IsEmpty());
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STATIC) -> ShowWindow((GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME) -> GetWindowTextLength() > 0  &&  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME) -> GetWindowTextLength() > 0) ? SW_SHOWNA:SW_HIDE);
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STATIC) -> EnableWindow((GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME) -> GetWindowTextLength() > 0  &&  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME) -> GetWindowTextLength() > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME) -> ShowWindow((GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME) -> GetWindowTextLength() > 0  &&  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME) -> GetWindowTextLength() > 0) ? SW_SHOWNA:SW_HIDE);
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME) -> EnableWindow((GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME) -> GetWindowTextLength() > 0  &&  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME) -> GetWindowTextLength() > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_TO) -> ShowWindow((GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME) -> GetWindowTextLength() > 0  &&  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME) -> GetWindowTextLength() > 0) ? SW_SHOWNA:SW_HIDE);
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_TO) -> EnableWindow((GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME) -> GetWindowTextLength() > 0  &&  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME) -> GetWindowTextLength() > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME) -> ShowWindow((GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME) -> GetWindowTextLength() > 0  &&  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME) -> GetWindowTextLength() > 0) ? SW_SHOWNA:SW_HIDE);
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME) -> EnableWindow((GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STARTTIME) -> GetWindowTextLength() > 0  &&  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_TIMERANGE_STOPTIME) -> GetWindowTextLength() > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME_STATIC) -> ShowWindow((GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME) -> GetWindowTextLength() > 0) ? SW_SHOWNA:SW_HIDE);
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME_STATIC) -> EnableWindow((GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME) -> GetWindowTextLength() > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME) -> ShowWindow((GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME) -> GetWindowTextLength() > 0) ? SW_SHOWNA:SW_HIDE);
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME) -> EnableWindow((GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_CREATIONTIME) -> GetWindowTextLength() > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE_STATIC) -> ShowWindow((!szDataSourceSize.IsEmpty()) ? SW_SHOWNA:SW_HIDE);
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE_STATIC) -> EnableWindow(!szDataSourceSize.IsEmpty());
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE) -> ShowWindow((!szDataSourceSize.IsEmpty()) ? SW_SHOWNA:SW_HIDE);
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_SOURCEINFO_SIZE) -> EnableWindow(!szDataSourceSize.IsEmpty());
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_INSPECT) -> EnableWindow(!m_szFileName[0].IsEmpty());
}

BOOL CPODSettingsRetrievingPage::CheckDataSource(LPCTSTR pszFileName) CONST
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

  return((CheckDataSource(pszFileName,szProduct,szCompany,szTrademark,szSpacecraft,szDataSourceType,szStartTime,szStopTime,szCreationTime,szDataSourceSize) &&  szSpacecraft == GetAccountSpacecraftName()) ? TRUE:FALSE);
}
BOOL CPODSettingsRetrievingPage::CheckDataSource(LPCTSTR pszFileName,CString &szProduct,CString &szCompany,CString &szTrademark,CString &szSpacecraft,CString &szDataSourceType,CString &szStartTime,CString &szStopTime,CString &szCreationTime,CString &szDataSourceSize) CONST
{
  CTimeKey  tTime;
  DWORDLONG  dwSize;
  CByteArray  nData;
  CFileFindEx  cFileFind;
  CHistoryFile  cHistoryFile;

  if (cFileFind.FindFile(pszFileName))
  { if (cHistoryFile.Open(pszFileName,(LPCTSTR) NULL,HISTORYSTORE_TYPE_TM,CFile::modeRead,TRUE) == HISTORYFILE_SUCCESS)
    { for (cHistoryFile.GetCopyrightProduct(szProduct),cHistoryFile.GetCopyrightCompany(szCompany),cHistoryFile.GetCopyrightTrademark(szTrademark),cHistoryFile.GetSpacecraft(szSpacecraft),cHistoryFile.GetType(szDataSourceType),szStartTime = (cHistoryFile.CLogFile::SeekToFirst() &&  cHistoryFile.CLogFile::Read(tTime,nData)) ? (LPCTSTR) tTime.FormatGmt(STRING(IDS_PODSETTINGS_RETRIEVINGPAGE_SOURCEDATATIMEFORMAT)):EMPTYSTRING,szStopTime = (cHistoryFile.CLogFile::SeekToLast() &&  cHistoryFile.CLogFile::Read(tTime,nData)) ? (LPCTSTR) tTime.FormatGmt(STRING(IDS_PODSETTINGS_RETRIEVINGPAGE_SOURCEDATATIMEFORMAT)):EMPTYSTRING,szCreationTime = (cHistoryFile.GetCopyrightCreationTime(tTime)) ? (LPCTSTR) tTime.FormatGmt(STRING(IDS_PODSETTINGS_RETRIEVINGPAGE_SOURCEDATAFILETIMEFORMAT)):EMPTYSTRING,szDataSourceSize.Format(STRING(IDS_PODSETTINGS_RETRIEVINGPAGE_SOURCEDATASIZEFORMAT),((dwSize = cHistoryFile.CLogFile::GetSize())+512)/1024),szDataSourceSize = FormatDataSourceSize(szDataSourceSize); !szProduct.IsEmpty() &&  !szCompany.IsEmpty() &&  !szTrademark.IsEmpty(); )
      { cHistoryFile.Close();
        cFileFind.Close();
        return TRUE;
      }
      cHistoryFile.Close();
    }
    cFileFind.Close();
  }
  return FALSE;
}

CString CPODSettingsRetrievingPage::FormatDataSourceSize(LPCTSTR pszDataSourceSize) CONST
{
  INT  cbSep;
  CString  szSep;
  CString  szSize;
  CString  szNumber;

  for (szNumber = pszDataSourceSize; (cbSep = GetLocaleInfo(MAKELCID(GetLanguageID(),SORT_DEFAULT),LOCALE_STHOUSAND,(LPTSTR) NULL,0)); )
  { if (GetLocaleInfo(MAKELCID(GetLanguageID(),SORT_DEFAULT),LOCALE_STHOUSAND,szSep.GetBufferSetLength(cbSep-1),cbSep))
    { for (szNumber = szNumber.Left(lstrlen(szNumber)),szSize.Empty(),szSep.ReleaseBuffer(); szNumber.GetLength() > 0  &&  !_istdigit(szNumber[szNumber.GetLength()-1]); )
      { szSize = szNumber.Right(1)+szSize,szNumber = szNumber.Left(szNumber.GetLength()-1);
        continue;
      }
      for ( ; szNumber.GetLength() > 0; szNumber = szNumber.Left(max(szNumber.GetLength()-3,0)))
      { szSize = (_istdigit(szSize[0])) ? (szNumber.Right(min(szNumber.GetLength(),3))+szSep+szSize):(szNumber.Right(min(szNumber.GetLength(),3))+szSize);
        continue;
      }
      return szSize;
    }
    szSep.ReleaseBuffer();
  }
  return szNumber;
}

BOOL CPODSettingsRetrievingPage::IsModified(BOOL bAll) CONST
{
  return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? ((m_szFileName[0].CompareNoCase(m_szFileName[1])) ? TRUE:FALSE):CLocalePropertyPage::IsModified()):FALSE);
}

BOOL CPODSettingsRetrievingPage::Check(BOOL bAll) CONST
{
  return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? (m_szFileName[0].IsEmpty() ||  CheckDataSource(m_szFileName[0])):CLocalePropertyPage::Check()):TRUE);
}

void CPODSettingsRetrievingPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPODSettingsRetrievingPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPODSettingsRetrievingPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CPODSettingsRetrievingPage)
	ON_BN_CLICKED(IDC_PODSETTINGS_RETRIEVINGPAGE_INSPECT,OnInspect)
	ON_CBN_EDITCHANGE(IDC_PODSETTINGS_RETRIEVINGPAGE_DATASOURCE,OnEditchangeFileName)
	ON_CBN_SELCHANGE(IDC_PODSETTINGS_RETRIEVINGPAGE_DATASOURCE,OnSelchangeFileName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPODSettingsRetrievingPage message handlers

BOOL CPODSettingsRetrievingPage::OnInitDialog() 
{
  CHourglassCursor  cCursor;

  CLocalePropertyPage::OnInitDialog();
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_DETAILS) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_DATASOURCE_STATIC) -> EnableWindow();
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_DATASOURCE) -> EnableWindow();
  EnumDataSources();
  return TRUE;
}

BOOL CPODSettingsRetrievingPage::OnSetActive()
{
  ShowDataSourceInfo();
  return CLocalePropertyPage::OnSetActive();
}

void CPODSettingsRetrievingPage::OnInspect()
{
  CHourglassCursor  cCursor;

  ShowDataSourceInfo();
}

void CPODSettingsRetrievingPage::OnEditchangeFileName()
{
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_DATASOURCE) -> GetWindowText(m_szFileName[0]);
  GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_INSPECT) -> EnableWindow(!m_szFileName[0].IsEmpty());
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsRetrievingPage::OnSelchangeFileName()
{
  for (m_szFileName[0] = Combobox_GetText(GetDlgItem(IDC_PODSETTINGS_RETRIEVINGPAGE_DATASOURCE),(INT) SendDlgItemMessage(IDC_PODSETTINGS_RETRIEVINGPAGE_DATASOURCE,CB_GETCURSEL)); !m_szFileName[0].IsEmpty(); )
  { ShowDataSourceInfo();
    break;
  }
  GetDlgItem(IDOK) -> EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CPODSettingsPrintingComments

IMPLEMENT_DYNCREATE(CPODSettingsPrintingComments,CEdit)

BEGIN_MESSAGE_MAP(CPODSettingsPrintingComments, CEdit)
	//{{AFX_MSG_MAP(CPODSettingsPrintingComments)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPODSettingsPrintingComments message handlers

void CPODSettingsPrintingComments::OnKeyDown(UINT nChar,UINT nRepCnt,UINT nFlags) 
{
  if (nChar == VK_TAB)
  { if (!HIBYTE(GetKeyState(VK_SHIFT)))
    { GetParent() -> GetParent() -> GetNextDlgTabItem(GetParent()) -> SetFocus();
      return;
    }
  }
  CEdit::OnKeyDown(nChar,nRepCnt,nFlags);
}


/////////////////////////////////////////////////////////////////////////////
// CPODSettingsPrintingPage property page

IMPLEMENT_DYNCREATE(CPODSettingsPrintingPage,CLocalePropertyPage)

CPODSettingsPrintingPage::CPODSettingsPrintingPage() : CLocalePropertyPage(CPODSettingsPrintingPage::IDD)
{
	//{{AFX_DATA_INIT(CPODSettingsPrintingPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CPODSettingsPrintingPage::Initialize()
{
  CPODOpenDialog  *pDialog;

  return((((pDialog = GetParentDialog() -> GetParentDialog()) &&  pDialog -> GetPrintJobs(m_pJobs[0])) ||  GetParentDisplay() -> GetPrintJobs(m_pJobs[0])) ? m_pJobs[1].Copy(&m_pJobs[0]):FALSE);
}

BOOL CPODSettingsPrintingPage::GetJobs(CPODPrintJobs &pJobs) CONST
{
  return((pJobs.Copy(&m_pJobs[0])) ? Check(FALSE):FALSE);
}

CPODSettingsDialog *CPODSettingsPrintingPage::GetParentDialog() CONST
{
  return((CPODSettingsDialog *) CLocalePropertyPage::GetParent());
}

CPODWnd *CPODSettingsPrintingPage::GetParentDisplay() CONST
{
  return((CPODWnd *) GetParentDialog() -> GetParentDisplay());
}

VOID CPODSettingsPrintingPage::ShowJobInfo()
{
  UINT  nMode;
  UINT  nCount;
  CTimeSpan  tStartTime;
  CTimeSpan  tStopTime;
  CPODPrintJobInfo  *pJobInfo;

  if ((pJobInfo = FindJobInfo()))
  { CheckDlgButton(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL,((nMode = pJobInfo -> GetPrintMode()) & POD_PRINT_ALL) ? TRUE:FALSE);
    CheckDlgButton(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE,((nMode & POD_PRINT_FIRSTSIDE) || (nMode & POD_PRINT_LASTSIDE)) ? TRUE:FALSE);
    CheckDlgButton(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTOPTION_PARAMETERS,(nMode & POD_PRINT_PARAMETERS) ? TRUE:FALSE);
    CheckDlgButton(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTOPTION_FUNCTIONS,(nMode & POD_PRINT_FUNCTIONS) ? TRUE:FALSE);
    CheckDlgButton(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL,(nMode & POD_PRINT_UNDERLINEOOL) ? TRUE:FALSE);
    CheckDlgButton(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND,(nMode & POD_PRINT_COLORLEGEND) ? TRUE:FALSE);
    CheckDlgButton(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS,(nMode & POD_PRINT_CLEARCOMMENTS) ? TRUE:FALSE);
    SendDlgItemMessage(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE,CB_SETCURSEL,(WPARAM) SendDlgItemMessage(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) pJobInfo -> GetProfile()));
    SendDlgItemMessage(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE,TEM_SELECTTEXT,(WPARAM) -1,(nMode & POD_PRINT_FIRSTSIDE) ? (LPARAM) STRING(IDS_PODSETTINGS_PRINTINGPAGE_FIRSTSIDE):((nMode & POD_PRINT_LASTSIDE) ? (LPARAM) STRING(IDS_PODSETTINGS_PRINTINGPAGE_LASTSIDE):(LPARAM) EMPTYSTRING));
    Spinbox_SetPos(GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT),(pJobInfo -> GetPrintBySide(nCount)) ? nCount:0);
    GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT) -> SetWindowText(pJobInfo -> GetComments());
    GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_ADDNAME) -> EnableWindow(FALSE);
    GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_REMOVENAME) -> EnableWindow((pJobInfo -> GetName() != STRING(IDS_PRINTJOB_DEFAULTNAME)) ? TRUE:FALSE);
    GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_REMOVEALLNAMES) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_PRINTINGPAGE_NAME,CB_GETCOUNT) > 1) ? TRUE:FALSE);
    GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES) -> EnableWindow();
    GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE_STATIC) -> EnableWindow();
    GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE) -> EnableWindow();
    GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_OPTIONS) -> EnableWindow();
    GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL) -> EnableWindow();
    GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE) -> EnableWindow();
    GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE));
    GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE_STATIC) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE));
    GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE));
    GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTOPTION_STATIC) -> EnableWindow();
    GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTOPTION_PARAMETERS) -> EnableWindow();
    GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTOPTION_FUNCTIONS) -> EnableWindow();
    GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL) -> EnableWindow();
    GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND) -> EnableWindow();
    GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTS) -> EnableWindow();
    GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT_STATIC) -> EnableWindow();
    GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT) -> EnableWindow();
    GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS) -> EnableWindow(!pJobInfo -> GetComments().IsEmpty());
    return;
  }
  SendDlgItemMessage(IDC_PODSETTINGS_PRINTINGPAGE_NAME,CB_SETCURSEL,(WPARAM) -1);
  SendDlgItemMessage(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE,CB_SETCURSEL,(WPARAM) -1);
  CheckDlgButton(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL,FALSE);
  CheckDlgButton(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE,FALSE);
  CheckDlgButton(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTOPTION_PARAMETERS,FALSE);
  CheckDlgButton(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTOPTION_FUNCTIONS,FALSE);
  CheckDlgButton(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL,FALSE);
  CheckDlgButton(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND,FALSE);
  CheckDlgButton(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS,FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT) -> SetWindowText(EMPTYSTRING);
  GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_ADDNAME) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_REMOVENAME) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_REMOVEALLNAMES) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE_STATIC) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_OPTIONS) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE_STATIC) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTOPTION_STATIC) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTOPTION_PARAMETERS) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTOPTION_FUNCTIONS) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTS) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT_STATIC) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS) -> EnableWindow(FALSE);
}

CPODPrintJobInfo *CPODSettingsPrintingPage::FindJobInfo() CONST
{
  CString  szJobName;

  GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_NAME) -> GetWindowText(szJobName);
  return m_pJobs[0].GetAt(m_pJobs[0].Find(szJobName));
}

BOOL CPODSettingsPrintingPage::IsModified(BOOL bAll) CONST
{
  return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? !m_pJobs[0].Compare(&m_pJobs[1]):CLocalePropertyPage::IsModified()):FALSE);
}

BOOL CPODSettingsPrintingPage::Check(BOOL bAll) CONST
{
  return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? ((GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_NAME) -> GetWindowTextLength() > 0  &&  FindJobInfo()) ? TRUE:FALSE):CLocalePropertyPage::Check()):TRUE);
}

void CPODSettingsPrintingPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPODSettingsPrintingPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CPODSettingsPrintingPage::PostNcDestroy()
{
  m_pJobs[0].RemoveAll();
  m_pJobs[1].RemoveAll();
  CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CPODSettingsPrintingPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CPODSettingsPrintingPage)
	ON_BN_CLICKED(IDC_PODSETTINGS_PRINTINGPAGE_ADDNAME,OnAddName)
	ON_BN_CLICKED(IDC_PODSETTINGS_PRINTINGPAGE_REMOVENAME,OnRemoveName)
	ON_BN_CLICKED(IDC_PODSETTINGS_PRINTINGPAGE_REMOVEALLNAMES,OnRemoveAllNames)
	ON_BN_CLICKED(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL,OnPrintAll)
	ON_BN_CLICKED(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE,OnPrintBySide)
	ON_BN_CLICKED(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTOPTION_PARAMETERS,OnPrintParameters)
	ON_BN_CLICKED(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTOPTION_FUNCTIONS,OnPrintFunctions)
	ON_BN_CLICKED(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL,OnPrintUnderlineOOL)
	ON_BN_CLICKED(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND,OnPrintColorLegend)
	ON_BN_CLICKED(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS,OnResetComments)
	ON_CBN_EDITCHANGE(IDC_PODSETTINGS_PRINTINGPAGE_NAME,OnEditchangeName)
	ON_CBN_SELCHANGE(IDC_PODSETTINGS_PRINTINGPAGE_NAME,OnSelchangeName)
	ON_CBN_SELCHANGE(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE,OnSelchangeProfile)
	ON_EN_CHANGE(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE,OnChangePrintSide)
	ON_EN_CHANGE(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT,OnEditchangeComments)
	ON_CONTROL(SBXN_CHANGE,IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT,OnSpinchangePrintSideCount)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPODSettingsPrintingPage message handlers

BOOL CPODSettingsPrintingPage::OnInitDialog() 
{
  INT  nJob;
  INT  nJobs;
  INT  nProfile;
  INT  nProfiles;
  CStringArray  szProfiles;
  CPODPrintJobInfo  *pJobInfo;
  CHourglassCursor  cCursor;

  for (CLocalePropertyPage::OnInitDialog(); m_wndComments.SubclassWindow(GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT) -> GetSafeHwnd()); )
  { for (nJob = 0,nJobs = (INT) m_pJobs[0].GetSize(); nJob < nJobs; nJob++)
    { if ((pJobInfo = m_pJobs[0].GetAt(nJob)) != (CPODPrintJobInfo *) NULL)
      { SendDlgItemMessage(IDC_PODSETTINGS_PRINTINGPAGE_NAME,CB_ADDSTRING,(WPARAM) NULL,(LPARAM) (LPCTSTR) pJobInfo -> GetName());
        continue;
      }
    }
    for (nProfile = 0,nProfiles = (EnumPrintProfiles(szProfiles)) ? (INT) szProfiles.GetSize():0; nProfile < nProfiles; nProfile++)
    { SendDlgItemMessage(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE,CB_ADDSTRING,(WPARAM) NULL,(LPARAM) (LPCTSTR) szProfiles.GetAt(nProfile));
      continue;
    }
    Spinbox_SetRange(GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT),PODSETTINGSPRINTINGPAGE_OPTIONS_MINIMUMVALUES,PODSETTINGSPRINTINGPAGE_OPTIONS_MAXIMUMVALUES);
    SendDlgItemMessage(IDC_PODSETTINGS_PRINTINGPAGE_NAME,CB_SETCURSEL,(WPARAM) SendDlgItemMessage(IDC_PODSETTINGS_PRINTINGPAGE_NAME,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) STRING(IDS_PRINTJOB_DEFAULTNAME)));
    SendDlgItemMessage(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE,TEM_ADDTEXT,(WPARAM) NULL,(LPARAM) STRING(IDS_PODSETTINGS_PRINTINGPAGE_FIRSTSIDE));
    SendDlgItemMessage(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE,TEM_ADDTEXT,(WPARAM) NULL,(LPARAM) STRING(IDS_PODSETTINGS_PRINTINGPAGE_LASTSIDE));
    GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_DETAILS) -> EnableWindow();
    GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_NAME_STATIC) -> EnableWindow();
    GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_NAME) -> EnableWindow();
    ShowJobInfo();
    break;
  }
  return TRUE;
}

BOOL CPODSettingsPrintingPage::OnSetActive()
{
  ShowJobInfo();
  return CLocalePropertyPage::OnSetActive();
}

BOOL CPODSettingsPrintingPage::OnKillActive()
{
  GetParentDialog() -> OnDataExchange(GetSafeHwnd(),m_pJobs[0]);
  return CLocalePropertyPage::OnKillActive();
}

BOOL CPODSettingsPrintingPage::OnDataExchange(CONST CPODPrintJobs &pJobs)
{
  return m_pJobs[0].Copy(&pJobs);
}

void CPODSettingsPrintingPage::OnEditchangeName()
{
  CString  szJobName;
  CPODPrintJobInfo  *pJobInfo;

  for (GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_NAME) -> GetWindowText(szJobName); (pJobInfo = FindJobInfo()); )
  { ShowJobInfo();
    return;
  }
  GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_ADDNAME) -> EnableWindow((!pJobInfo  &&  szJobName.GetLength() > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_REMOVENAME) -> EnableWindow((pJobInfo != (CPODPrintJobInfo *) NULL  &&  szJobName != STRING(IDS_PRINTJOB_DEFAULTNAME)) ? TRUE:FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_REMOVEALLNAMES) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_PRINTINGPAGE_NAME,CB_GETCOUNT) > 1) ? TRUE:FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS) -> EnableWindow((szJobName != STRING(IDS_PRINTJOB_DEFAULTNAME)) ? TRUE:FALSE);
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsPrintingPage::OnSelchangeName()
{
  SendDlgItemMessage(IDC_PODSETTINGS_PRINTINGPAGE_NAME,CB_SETCURSEL,(WPARAM) SendDlgItemMessage(IDC_PODSETTINGS_PRINTINGPAGE_NAME,CB_GETCURSEL));
  ShowJobInfo();
}

void CPODSettingsPrintingPage::OnAddName()
{
  INT  nIndex;
  UINT  nMode;
  UINT  nCount;
  CString  szJobName;
  CString  szProfile;
  CString  szComments;
  CPODPrintJobInfo  *pJobInfo;
  CHourglassCursor  cCursor;

  for ( ; (pJobInfo = new CPODPrintJobInfo); )
  { GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_NAME) -> GetWindowText(szJobName);
    GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE) -> GetWindowText(szProfile);
    GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT) -> GetWindowText(szComments);
    nMode = (IsDlgButtonChecked(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL)) ? ((pJobInfo -> GetPrintMode() | POD_PRINT_ALL) & ~(POD_PRINT_FIRSTSIDE | POD_PRINT_LASTSIDE)):pJobInfo -> GetPrintMode();
    nMode = (IsDlgButtonChecked(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE)) ? ((!GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE) -> SendMessage(TEM_GETPOS)) ? ((nMode | POD_PRINT_FIRSTSIDE) & ~(POD_PRINT_ALL | POD_PRINT_LASTSIDE)):((nMode | POD_PRINT_LASTSIDE) & ~(POD_PRINT_ALL | POD_PRINT_FIRSTSIDE))):nMode;
    nMode = (IsDlgButtonChecked(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTOPTION_PARAMETERS)) ? (nMode | POD_PRINT_PARAMETERS):nMode;
    nMode = (IsDlgButtonChecked(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTOPTION_FUNCTIONS)) ? (nMode | POD_PRINT_FUNCTIONS):nMode;
    nMode = (IsDlgButtonChecked(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL)) ? (nMode | POD_PRINT_UNDERLINEOOL):nMode;
    nMode = (IsDlgButtonChecked(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND)) ? (nMode | POD_PRINT_COLORLEGEND):nMode;
    nMode = (IsDlgButtonChecked(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)) ? (nMode | POD_PRINT_CLEARCOMMENTS):(nMode & ~POD_PRINT_CLEARCOMMENTS);
    nCount = ((nMode & POD_PRINT_FIRSTSIDE) || (nMode & POD_PRINT_LASTSIDE)) ? (UINT) Spinbox_GetPos(GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)):0;
    if (SendDlgItemMessage(IDC_PODSETTINGS_PRINTINGPAGE_NAME,CB_ADDSTRING,(WPARAM) NULL,(LPARAM) (LPCTSTR) szJobName) >= 0  &&  SendDlgItemMessage(IDC_PODSETTINGS_PRINTINGPAGE_NAME,CB_SETCURSEL,(WPARAM) SendDlgItemMessage(IDC_PODSETTINGS_PRINTINGPAGE_NAME,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) szJobName)) >= 0)
    { for (pJobInfo -> SetName(szJobName),pJobInfo -> SetProfile(szProfile),pJobInfo -> SetComments(szComments),pJobInfo -> SetPrintMode(nMode),pJobInfo -> SetPrintBySide(nCount); (nIndex = m_pJobs[0].Add(pJobInfo)) >= 0; )
      { ShowJobInfo();
        break;
      }
      if (nIndex >= 0) break;
    }
    delete pJobInfo;
    break;
  }
  GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_NAME) -> SetFocus();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsPrintingPage::OnRemoveName()
{
  INT  nJob;
  INT  nJobs;
  CPODPrintJobInfo  *pJobInfo;
  CHourglassCursor  cCursor;

  for (nJob = 0,nJobs = (INT) m_pJobs[0].GetSize(); nJob < nJobs; nJob++)
  { if ((pJobInfo = m_pJobs[0].GetAt(nJob)) &&  pJobInfo == FindJobInfo())
    { if (SendDlgItemMessage(IDC_PODSETTINGS_PRINTINGPAGE_NAME,CB_DELETESTRING,(WPARAM) SendDlgItemMessage(IDC_PODSETTINGS_PRINTINGPAGE_NAME,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) pJobInfo -> GetName())) > 0)
      { m_pJobs[0].RemoveAt(nJob);
        delete pJobInfo;
      }
      break;
    }
  }
  for ( ; SendDlgItemMessage(IDC_PODSETTINGS_PRINTINGPAGE_NAME,CB_SETCURSEL,(WPARAM) SendDlgItemMessage(IDC_PODSETTINGS_PRINTINGPAGE_NAME,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) STRING(IDS_PRINTJOB_DEFAULTNAME))) >= 0; )
  { ShowJobInfo();
    break;
  }
  GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_NAME) -> SetFocus();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsPrintingPage::OnRemoveAllNames()
{
  INT  nJob;
  INT  nJobs;
  CPODPrintJobInfo  *pJobInfo;
  CHourglassCursor  cCursor;

  for (nJob = 0,nJobs = (INT) m_pJobs[0].GetSize(); nJob < nJobs; nJob++)
  { if ((pJobInfo = m_pJobs[0].GetAt(nJob)) &&  pJobInfo -> GetName() != STRING(IDS_PRINTJOB_DEFAULTNAME) &&  SendDlgItemMessage(IDC_PODSETTINGS_PRINTINGPAGE_NAME,CB_DELETESTRING,(WPARAM) SendDlgItemMessage(IDC_PODSETTINGS_PRINTINGPAGE_NAME,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) pJobInfo -> GetName())) > 0)
    { m_pJobs[0].RemoveAt(nJob);
      delete pJobInfo;
      nJobs--;
      nJob--;
    }
  }
  for ( ; SendDlgItemMessage(IDC_PODSETTINGS_PRINTINGPAGE_NAME,CB_SETCURSEL,(WPARAM) SendDlgItemMessage(IDC_PODSETTINGS_PRINTINGPAGE_NAME,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) STRING(IDS_PRINTJOB_DEFAULTNAME))) >= 0; )
  { ShowJobInfo();
    break;
  }
  GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_NAME) -> SetFocus();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsPrintingPage::OnSelchangeProfile()
{
  CString  szProfile;
  CPODPrintJobInfo  *pJobInfo;

  if ((pJobInfo = FindJobInfo()))
  { GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE) -> GetWindowText(szProfile);
    pJobInfo -> SetProfile(szProfile);
  }
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsPrintingPage::OnPrintAll()
{
  CPODPrintJobInfo  *pJobInfo;

  if (!IsDlgButtonChecked(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL))
  { for (CheckDlgButton(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL,TRUE),CheckDlgButton(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE,FALSE),SendDlgItemMessage(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE,TEM_SELECTTEXT,(WPARAM) -1,(LPARAM) EMPTYSTRING); (pJobInfo = FindJobInfo()); )
    { pJobInfo -> SetPrintMode((pJobInfo -> GetPrintMode() | POD_PRINT_ALL) & ~(POD_PRINT_FIRSTSIDE | POD_PRINT_LASTSIDE));
      break;
    }
    GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_ADDNAME) -> EnableWindow((GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_NAME) -> GetWindowTextLength() > 0  &&  SendDlgItemMessage(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE,CB_GETCURSEL) != CB_ERR  &&  !pJobInfo) ? TRUE:FALSE);
    GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE) -> EnableWindow(FALSE);
    GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT) -> EnableWindow(FALSE);
    GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE_STATIC) -> EnableWindow(FALSE);
  }
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsPrintingPage::OnPrintBySide()
{
  CPODPrintJobInfo  *pJobInfo;

  if (!IsDlgButtonChecked(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE))
  { for (CheckDlgButton(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTALL,FALSE),CheckDlgButton(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE,TRUE),SendDlgItemMessage(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE,TEM_SELECTTEXT,(WPARAM) -1,(LPARAM) STRING(IDS_PODSETTINGS_PRINTINGPAGE_LASTSIDE)),Spinbox_SetPos(GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT),PODSETTINGSPRINTINGPAGE_OPTIONS_DEFAULTVALUES); (pJobInfo = FindJobInfo()); )
    { pJobInfo -> SetPrintMode((pJobInfo -> GetPrintMode() | POD_PRINT_LASTSIDE) & ~(POD_PRINT_ALL | POD_PRINT_FIRSTSIDE));
      pJobInfo -> SetPrintBySide(PODSETTINGSPRINTINGPAGE_OPTIONS_DEFAULTVALUES);
      break;
    }
    SendDlgItemMessage(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE,EM_SETSEL,0,(LPARAM) -1);
    GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_ADDNAME) -> EnableWindow((GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_NAME) -> GetWindowTextLength() > 0  &&  SendDlgItemMessage(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PROFILE,CB_GETCURSEL) != CB_ERR  &&  !pJobInfo) ? TRUE:FALSE);
    GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE) -> EnableWindow();
    GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT) -> EnableWindow();
    GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTBYSIDE_STATIC) -> EnableWindow();
    GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE) -> SetFocus();
  }
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsPrintingPage::OnPrintParameters()
{
  UINT  nMode;
  CPODPrintJobInfo  *pJobInfo;

  if ((pJobInfo = FindJobInfo()))
  { nMode = (IsDlgButtonChecked(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTOPTION_PARAMETERS)) ? (pJobInfo -> GetPrintMode() | POD_PRINT_PARAMETERS):(pJobInfo -> GetPrintMode() & ~POD_PRINT_PARAMETERS);
    pJobInfo -> SetPrintMode(nMode);
  }
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsPrintingPage::OnPrintFunctions()
{
  UINT  nMode;
  CPODPrintJobInfo  *pJobInfo;

  if ((pJobInfo = FindJobInfo()))
  { nMode = (IsDlgButtonChecked(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTOPTION_FUNCTIONS)) ? (pJobInfo -> GetPrintMode() | POD_PRINT_FUNCTIONS):(pJobInfo -> GetPrintMode() & ~POD_PRINT_FUNCTIONS);
    pJobInfo -> SetPrintMode(nMode);
  }
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsPrintingPage::OnPrintUnderlineOOL()
{
  UINT  nMode;
  CPODPrintJobInfo  *pJobInfo;

  if ((pJobInfo = FindJobInfo()))
  { nMode = (IsDlgButtonChecked(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_UNDERLINEOOL)) ? (pJobInfo -> GetPrintMode() | POD_PRINT_UNDERLINEOOL):(pJobInfo -> GetPrintMode() & ~POD_PRINT_UNDERLINEOOL);
    pJobInfo -> SetPrintMode(nMode);
  }
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsPrintingPage::OnPrintColorLegend()
{
  UINT  nMode;
  CPODPrintJobInfo  *pJobInfo;

  if ((pJobInfo = FindJobInfo()))
  { nMode = (IsDlgButtonChecked(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_COLORLEGEND)) ? (pJobInfo -> GetPrintMode() | POD_PRINT_COLORLEGEND):(pJobInfo -> GetPrintMode() & ~POD_PRINT_COLORLEGEND);
    pJobInfo -> SetPrintMode(nMode);
  }
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsPrintingPage::OnChangePrintSide()
{
  UINT  nMode;
  CPODPrintJobInfo  *pJobInfo;

  if ((pJobInfo = FindJobInfo()))
  { nMode = (!SendDlgItemMessage(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDE,TEM_GETPOS)) ? ((pJobInfo -> GetPrintMode() | POD_PRINT_FIRSTSIDE) & ~(POD_PRINT_ALL | POD_PRINT_LASTSIDE)):((pJobInfo -> GetPrintMode() | POD_PRINT_LASTSIDE) & ~(POD_PRINT_ALL | POD_PRINT_FIRSTSIDE));
    pJobInfo -> SetPrintMode(nMode);
  }
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsPrintingPage::OnSpinchangePrintSideCount()
{
  CPODPrintJobInfo  *pJobInfo;

  if ((pJobInfo = FindJobInfo())) pJobInfo -> SetPrintBySide((UINT) Spinbox_GetPos(GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_PRINTSIDECOUNT)));
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsPrintingPage::OnEditchangeComments()
{
  CString  szComments;
  CPODPrintJobInfo  *pJobInfo;

  if ((pJobInfo = FindJobInfo()))
  { GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_COMMENTSTEXT) -> GetWindowText(szComments);
    GetDlgItem(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS) -> EnableWindow(!szComments.IsEmpty());
    CheckDlgButton(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS,(!szComments.IsEmpty()) ? IsDlgButtonChecked(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS):FALSE);
    pJobInfo -> SetPrintMode((IsDlgButtonChecked(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)) ? (pJobInfo -> GetPrintMode() | POD_PRINT_CLEARCOMMENTS):(pJobInfo -> GetPrintMode() & ~POD_PRINT_CLEARCOMMENTS));
    pJobInfo -> SetComments(szComments);
  }
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsPrintingPage::OnResetComments()
{
  UINT  nMode;
  CPODPrintJobInfo  *pJobInfo;

  if ((pJobInfo = FindJobInfo()))
  { nMode = (IsDlgButtonChecked(IDC_PODSETTINGS_PRINTINGPAGE_PROPERTIES_CLEARCOMMENTS)) ? (pJobInfo -> GetPrintMode() | POD_PRINT_CLEARCOMMENTS):(pJobInfo -> GetPrintMode() & ~POD_PRINT_CLEARCOMMENTS);
    pJobInfo -> SetPrintMode(nMode);
  }
  GetDlgItem(IDOK) -> EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CPODSettingsPrintJobsPage property page

IMPLEMENT_DYNCREATE(CPODSettingsPrintJobsPage,CLocalePropertyPage)

CPODSettingsPrintJobsPage::CPODSettingsPrintJobsPage() : CLocalePropertyPage(CPODSettingsPrintJobsPage::IDD)
{
	//{{AFX_DATA_INIT(CPODSettingsPrintJobsPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CPODSettingsPrintJobsPage::Initialize()
{
  CPODOpenDialog  *pDialog;

  return((((pDialog = GetParentDialog() -> GetParentDialog()) &&  pDialog -> GetPrintJobs(m_pJobs[0])) ||  GetParentDisplay() -> GetPrintJobs(m_pJobs[0])) ? m_pJobs[1].Copy(&m_pJobs[0]):FALSE);
}

BOOL CPODSettingsPrintJobsPage::GetJobs(CPODPrintJobs &pJobs) CONST
{
  return((pJobs.Copy(&m_pJobs[0])) ? Check(FALSE):FALSE);
}

CPODSettingsDialog *CPODSettingsPrintJobsPage::GetParentDialog() CONST
{
  return((CPODSettingsDialog *) CLocalePropertyPage::GetParent());
}

CPODWnd *CPODSettingsPrintJobsPage::GetParentDisplay() CONST
{
  return((CPODWnd *) GetParentDialog() -> GetParentDisplay());
}

BOOL CPODSettingsPrintJobsPage::EnumJobs()
{
  INT  nJob;
  INT  nJobs;
  UINT  nMode;
  CPODPrintJobInfo  *pJobInfo;

  SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS,LB_RESETCONTENT);
  SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS,LB_RESETCONTENT);
  for (nJob = 0,nJobs = (INT) m_pJobs[0].GetSize(); nJob < nJobs; nJob = nJob+1)
  { if ((pJobInfo = m_pJobs[0].GetAt(nJob)) &&  pJobInfo -> GetName() != STRING(IDS_PRINTJOB_DEFAULTNAME))
    { if (SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS,LB_ADDSTRING,(WPARAM) NULL,(LPARAM) (LPCTSTR) pJobInfo -> GetName()) >= 0)
      { if (((nMode = pJobInfo -> GetPrintMode()) & POD_PRINT_ACTIVE) && ((nMode & POD_PRINT_ATTIME) || (nMode & POD_PRINT_ATDAILYTIME) || (nMode & POD_PRINT_ATEVENT)))
        { if (SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS,LB_ADDSTRING,(WPARAM) NULL,(LPARAM) (LPCTSTR) pJobInfo -> GetName()) == LB_ERR)
          { pJobInfo -> SetPrintMode(nMode & ~(POD_PRINT_ACTIVE | POD_PRINT_ATTIME | POD_PRINT_ATDAILYTIME | POD_PRINT_ATEVENT | POD_PRINT_REPEATBYINTERVAL | POD_PRINT_REPEATSTOPBYCOUNT | POD_PRINT_REPEATSTOPBYTIME | POD_PRINT_DAILYREPEATSTOPBYCOUNT | POD_PRINT_DAILYREPEATSTOPBYTIME));
            continue;
          }
        }
      }
    }
  }
  if (SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS,LB_GETCOUNT) > 0)
  { SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS,LB_SETCURSEL);
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_DETAILS) -> EnableWindow();
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS_STATIC) -> EnableWindow();
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS) -> EnableWindow();
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS,LB_GETCOUNT) > 0) ? TRUE:FALSE);
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS,LB_GETCOUNT) > 0) ? TRUE:FALSE);
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_ADDJOB) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS,LB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) Listbox_GetText(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS),(INT) SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS,LB_GETCURSEL))) == LB_ERR  &&  CheckJobInfo()) ? TRUE:FALSE);
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_REMOVEJOB) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS,LB_GETCURSEL) >= 0) ? TRUE:FALSE);
    ShowJobInfo();
    return TRUE;
  }
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_DETAILS) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS_STATIC) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_ADDJOB) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_REMOVEJOB) -> EnableWindow(FALSE);
  ShowJobInfo();
  return FALSE;
}

BOOL CPODSettingsPrintJobsPage::EnumEvents()
{
  INT  nEvent;
  INT  nEvents;
  CTelemetryEvents  pEvents;
  CTelemetryEventInfo  *pEventInfo;

  for (nEvent = 0,nEvents = (GetTelemetryEvents(pEvents)) ? (INT) pEvents.GetSize():0; nEvent < nEvents; nEvent++)
  { if ((pEventInfo = pEvents.GetAt(nEvent))) SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT,CB_ADDSTRING,(WPARAM) NULL,(LPARAM) (LPCTSTR) pEventInfo -> GetName());
    continue;
  }
  return((SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT,CB_GETCOUNT) > 0) ? TRUE:FALSE);
}

VOID CPODSettingsPrintJobsPage::ShowJobInfo()
{
  UINT  nStopCount;
  CString  szEvent;
  CTimeKey  tTime;
  CTimeKey  tStopTime;
  CTimeSpan  tInterval;
  CTimeSpan  tDailyTime;
  CPODPrintJobInfo  *pJobInfo;

  if ((pJobInfo = FindJobInfo()))
  { Timespinbox_SetTime(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME),(pJobInfo -> GetPrintAtTime(tTime) ||  pJobInfo -> GetPrintAtTime(tTime,tInterval) ||  pJobInfo -> GetPrintAtTime(tTime,tInterval,nStopCount) ||  pJobInfo -> GetPrintAtTime(tTime,tInterval,tStopTime)) ? tTime:CTime::GetCurrentTime().GetTime());
    Timespinbox_SetTime(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME),(pJobInfo -> GetPrintAtDailyTime(tDailyTime) ||  pJobInfo -> GetPrintAtDailyTime(tDailyTime,nStopCount) ||  pJobInfo -> GetPrintAtDailyTime(tDailyTime,tStopTime)) ? CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime()/SECONDSPERDAY)+tDailyTime.GetTotalSeconds()):CTime::GetCurrentTime().GetTime());
    SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT,CB_SETCURSEL,(pJobInfo -> GetPrintAtEvent(szEvent)) ? (WPARAM) SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) szEvent):(WPARAM) -1);
    SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE,(SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) STRING(IDS_PODSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS)) < 0  && (pJobInfo -> GetPrintMode() & POD_PRINT_ATTIME)) ? CB_ADDSTRING:CB_FINDSTRING,(WPARAM) NULL,(LPARAM) STRING(IDS_PODSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS));
    SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE,(SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) STRING(IDS_PODSETTINGS_PRINTJOBSPAGE_DAILYPRINTS)) < 0  && (pJobInfo -> GetPrintMode() & POD_PRINT_ATDAILYTIME)) ? CB_ADDSTRING:CB_FINDSTRING,(WPARAM) NULL,(LPARAM) STRING(IDS_PODSETTINGS_PRINTJOBSPAGE_DAILYPRINTS));
    SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE,CB_SETCURSEL,((pJobInfo -> GetPrintMode() & POD_PRINT_ATTIME) || (pJobInfo -> GetPrintMode() & POD_PRINT_ATDAILYTIME)) ? (WPARAM) SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) ((pJobInfo -> GetPrintMode() & POD_PRINT_ATTIME) ? STRING(IDS_PODSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS):STRING(IDS_PODSETTINGS_PRINTJOBSPAGE_DAILYPRINTS))):(WPARAM) -1);
    CheckDlgButton(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME,(pJobInfo -> GetPrintMode() & POD_PRINT_ATTIME) ? TRUE:FALSE);
    CheckDlgButton(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME,(pJobInfo -> GetPrintMode() & POD_PRINT_ATDAILYTIME) ? TRUE:FALSE);
    CheckDlgButton(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT,(pJobInfo -> GetPrintMode() & POD_PRINT_ATEVENT) ? ((SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT,CB_GETCURSEL) >= 0) ? TRUE:FALSE):FALSE);
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR) -> EnableWindow();
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) -> EnableWindow();
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME));
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME) -> EnableWindow();
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME_STATIC) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT,CB_GETCOUNT) > 0) ? TRUE:FALSE);
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT));
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT_STATIC) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT));
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) ||  IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) ||  IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) ||  IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
    SetJobRepetitionInfo();
    return;
  }
  CheckDlgButton(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME,FALSE);
  CheckDlgButton(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME,FALSE);
  CheckDlgButton(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT,FALSE);
  CheckDlgButton(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME,FALSE);
  CheckDlgButton(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES,FALSE);
  CheckDlgButton(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME,FALSE);
  SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT,CB_SETCURSEL,(WPARAM) -1);
  SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE,CB_SETCURSEL,(WPARAM) -1);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME_STATIC) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT_STATIC) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME) -> EnableWindow(FALSE);
}

BOOL CPODSettingsPrintJobsPage::CheckJobInfo() CONST
{
  UINT  nStopCount;
  CString  szEvent;
  CTimeKey  tTime;
  CTimeKey  tStopTime;
  CTimeSpan  tInterval;
  CTimeSpan  tDailyTime;
  CPODPrintJobInfo  *pJobInfo;

  return(((pJobInfo = FindJobInfo())) ? ((pJobInfo -> GetPrintAtTime(tTime) &&  tTime > CTime::GetCurrentTime()) ||  pJobInfo -> GetPrintAtTime(tTime,tInterval) || (pJobInfo -> GetPrintAtTime(tTime,tInterval,nStopCount) &&  tTime.GetTime()+tInterval.GetTotalSeconds()*(TIMEKEY) nStopCount > CTime::GetCurrentTime().GetTime()) || (pJobInfo -> GetPrintAtTime(tTime,tInterval,tStopTime) &&  tStopTime > CTime::GetCurrentTime()) ||  pJobInfo -> GetPrintAtDailyTime(tDailyTime) ||  pJobInfo -> GetPrintAtDailyTime(tDailyTime,nStopCount) || (pJobInfo -> GetPrintAtDailyTime(tDailyTime,tStopTime) &&  tStopTime > CTime::GetCurrentTime()) ||  pJobInfo -> GetPrintAtEvent(szEvent)):FALSE);
}

CPODPrintJobInfo *CPODSettingsPrintJobsPage::FindJobInfo(BOOL bActive) CONST
{
  INT  nJob;
  INT  nJobs;
  CString  szJobName[2];
  CPODPrintJobInfo  *pJobInfo;

  for (nJob = 0,nJobs = (INT) m_pJobs[0].GetSize(),szJobName[0] = Listbox_GetText(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS),(INT) GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS) -> SendMessage(LB_GETCURSEL)),szJobName[1] = Listbox_GetText(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS),(INT) GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS) -> SendMessage(LB_GETCURSEL)),szJobName[0] = (!bActive) ? szJobName[0]:szJobName[1]; nJob < nJobs; nJob++)
  { if ((pJobInfo = m_pJobs[0].GetAt(nJob)) &&  pJobInfo -> GetName() == szJobName[0]) break;
    continue;
  }
  return((nJob < nJobs) ? pJobInfo:(CPODPrintJobInfo *) NULL);
}

VOID CPODSettingsPrintJobsPage::SetJobRepetitionInfo()
{
  UINT  nStopCount;
  CTimeKey  tTime;
  CTimeKey  tStopTime;
  CTimeSpan  tInterval;
  CTimeSpan  tDailyTime;
  CPODPrintJobInfo  *pJobInfo;

  if ((pJobInfo = FindJobInfo()))
  { Timespinbox_SetTime(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME),((GetJobRepetitionType() == PODSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  pJobInfo -> GetPrintAtTime(tTime,tInterval,tStopTime)) || (GetJobRepetitionType() == PODSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  pJobInfo -> GetPrintAtDailyTime(tDailyTime,tStopTime))) ? tStopTime:CTime::GetCurrentTime().GetTime());
    Spinbox_SetPos(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME),(pJobInfo -> GetPrintAtTime(tTime,tInterval) ||  pJobInfo -> GetPrintAtTime(tTime,tInterval,nStopCount) ||  pJobInfo -> GetPrintAtTime(tTime,tInterval,tStopTime)) ? (tInterval.GetTotalSeconds()/SECONDSPERMINUTE):0);
    Spinbox_SetPos(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES),((GetJobRepetitionType() == PODSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  pJobInfo -> GetPrintAtTime(tTime,tInterval,nStopCount)) || (GetJobRepetitionType() == PODSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  pJobInfo -> GetPrintAtDailyTime(tDailyTime,nStopCount))) ? nStopCount:0);
    CheckDlgButton(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME,(GetJobRepetitionType() == PODSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  && (pJobInfo -> GetPrintMode() & POD_PRINT_REPEATBYINTERVAL)) ? TRUE:FALSE);
    CheckDlgButton(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES,((GetJobRepetitionType() == PODSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  && (pJobInfo -> GetPrintMode() & POD_PRINT_REPEATSTOPBYCOUNT)) || (GetJobRepetitionType() == PODSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  && (pJobInfo -> GetPrintMode() & POD_PRINT_DAILYREPEATSTOPBYCOUNT))) ? TRUE:FALSE);
    CheckDlgButton(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME,((GetJobRepetitionType() == PODSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  && (pJobInfo -> GetPrintMode() & POD_PRINT_REPEATSTOPBYTIME)) || (GetJobRepetitionType() == PODSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  && (pJobInfo -> GetPrintMode() & POD_PRINT_DAILYREPEATSTOPBYTIME))) ? TRUE:FALSE);
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME) -> EnableWindow((GetJobRepetitionType() == PODSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY) ? TRUE:FALSE);
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME) -> EnableWindow(GetJobRepetitionType() == PODSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC) -> EnableWindow(GetJobRepetitionType() == PODSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC) -> EnableWindow((IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) ||  IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && (GetJobRepetitionType() == PODSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  ||  IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)));
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES) -> EnableWindow((IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) ||  IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && (GetJobRepetitionType() == PODSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  ||  IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)));
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES) -> EnableWindow((IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) ||  IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) &&  IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES));
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC) -> EnableWindow((IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) ||  IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) &&  IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES));
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME) -> EnableWindow((IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) ||  IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) && (GetJobRepetitionType() == PODSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  ||  IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)));
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME) -> EnableWindow((IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) ||  IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) &&  IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME));
    return;
  }
  CheckDlgButton(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME,FALSE);
  CheckDlgButton(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES,FALSE);
  CheckDlgButton(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME,FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME) -> EnableWindow(FALSE);
}

UINT CPODSettingsPrintJobsPage::GetJobRepetitionType() CONST
{
  CString  szRepetitionType;

  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE) -> GetWindowText(szRepetitionType);
  return((szRepetitionType == STRING(IDS_PODSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS) ||  szRepetitionType == STRING(IDS_PODSETTINGS_PRINTJOBSPAGE_DAILYPRINTS)) ? ((szRepetitionType == STRING(IDS_PODSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS)) ? PODSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY:PODSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY):0);
}

BOOL CPODSettingsPrintJobsPage::IsModified(BOOL bAll) CONST
{
  return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? !m_pJobs[0].Compare(&m_pJobs[1]):CLocalePropertyPage::IsModified()):FALSE);
}

BOOL CPODSettingsPrintJobsPage::Check(BOOL bAll) CONST
{
  return((IsWindow(GetSafeHwnd())) ? ((!bAll) ? TRUE:CLocalePropertyPage::Check()):TRUE);
}

void CPODSettingsPrintJobsPage::DoDataExchange(CDataExchange *pDX)
{
	CLocalePropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPODSettingsPrintJobsPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CPODSettingsPrintJobsPage::PostNcDestroy()
{
  m_pJobs[0].RemoveAll();
  m_pJobs[1].RemoveAll();
  CLocalePropertyPage::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CPODSettingsPrintJobsPage, CLocalePropertyPage)
	//{{AFX_MSG_MAP(CPODSettingsPrintJobsPage)
	ON_BN_CLICKED(IDC_PODSETTINGS_PRINTJOBSPAGE_ADDJOB,OnAddJob)
	ON_BN_CLICKED(IDC_PODSETTINGS_PRINTJOBSPAGE_REMOVEJOB,OnRemoveJob)
	ON_BN_CLICKED(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME,OnPrintAtTime)
	ON_BN_CLICKED(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME,OnPrintAtDailyTime)
	ON_BN_CLICKED(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT,OnPrintAtEvent)
	ON_BN_CLICKED(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME,OnRepeatByTime)
	ON_BN_CLICKED(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES,OnRepetitionStopByCopies)
	ON_BN_CLICKED(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME,OnRepetitionStopByTime)
	ON_CBN_SELCHANGE(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT,OnSelchangeEvent)
	ON_CBN_SELCHANGE(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE,OnSelchangeRepetitionType)
	ON_LBN_SELCHANGE(IDC_PODSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS,OnSelchangeDefinedJob)
	ON_LBN_SELCHANGE(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS,OnSelchangeActiveJob)
	ON_CONTROL(SBXN_CHANGE,IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME,OnSpinchangeRepeatTime)
	ON_CONTROL(SBXN_CHANGE,IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES,OnSpinchangeRepetitionStopCopies)
	ON_CONTROL(TSBXN_CHANGE,IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME,OnSpinchangePrintTime)
	ON_CONTROL(TSBXN_CHANGE,IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME,OnSpinchangePrintDailyTime)
	ON_CONTROL(TSBXN_CHANGE,IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME,OnSpinchangeRepetitionStopTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPODSettingsPrintJobsPage message handlers

BOOL CPODSettingsPrintJobsPage::OnInitDialog() 
{
  CHourglassCursor  cCursor;

  CLocalePropertyPage::OnInitDialog();
  Spinbox_SetRange(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME),PODSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMINTERVAL,PODSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMINTERVAL);
  Spinbox_SetRange(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES),PODSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES,PODSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES);
  EnumEvents();
  return TRUE;
}

BOOL CPODSettingsPrintJobsPage::OnSetActive()
{
  EnumJobs();
  return CLocalePropertyPage::OnSetActive();
}

BOOL CPODSettingsPrintJobsPage::OnKillActive()
{
  GetParentDialog() -> OnDataExchange(GetSafeHwnd(),m_pJobs[0]);
  return CLocalePropertyPage::OnKillActive();
}

BOOL CPODSettingsPrintJobsPage::OnDataExchange(CONST CPODPrintJobs &pJobs)
{
  return m_pJobs[0].Copy(&pJobs);
}

void CPODSettingsPrintJobsPage::OnAddJob()
{
  CPODPrintJobInfo  *pJobInfo;
  CHourglassCursor  cCursor;

  if ((pJobInfo = FindJobInfo()))
  { pJobInfo -> SetPrintMode(pJobInfo -> GetPrintMode() | POD_PRINT_ACTIVE);
    SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS,LB_ADDSTRING,(WPARAM) NULL,(LPARAM) (LPCTSTR) pJobInfo -> GetName());
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS,LB_GETCOUNT) > 0) ? TRUE:FALSE);
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS,LB_GETCOUNT) > 0) ? TRUE:FALSE);
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_ADDJOB) -> EnableWindow(FALSE);
  }
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS) -> SetFocus();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsPrintJobsPage::OnRemoveJob()
{
  CPODPrintJobInfo  *pJobInfo;
  CHourglassCursor  cCursor;

  if ((pJobInfo = FindJobInfo(TRUE)))
  { for (pJobInfo -> SetPrintMode(pJobInfo -> GetPrintMode() & ~(POD_PRINT_ACTIVE | POD_PRINT_ATTIME | POD_PRINT_ATDAILYTIME | POD_PRINT_ATEVENT | POD_PRINT_REPEATBYINTERVAL | POD_PRINT_REPEATSTOPBYCOUNT | POD_PRINT_REPEATSTOPBYTIME | POD_PRINT_DAILYREPEATSTOPBYCOUNT | POD_PRINT_DAILYREPEATSTOPBYTIME)),SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS,LB_DELETESTRING,(WPARAM) SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS,LB_GETCURSEL)); pJobInfo == FindJobInfo(); )
    { ShowJobInfo();
      break;
    }
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS_STATIC) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS,LB_GETCOUNT) > 0) ? TRUE:FALSE);
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS,LB_GETCOUNT) > 0) ? TRUE:FALSE);
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_REMOVEJOB) -> EnableWindow(FALSE);
  }
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_DEFINEDJOBS) -> SetFocus();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsPrintJobsPage::OnSelchangeDefinedJob()
{
  CPODPrintJobInfo  *pJobInfo;

  ShowJobInfo();
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_ADDJOB) -> EnableWindow(((pJobInfo = FindJobInfo()) &&  SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS,LB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) pJobInfo -> GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE:FALSE);
}

void CPODSettingsPrintJobsPage::OnSelchangeActiveJob()
{
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_REMOVEJOB) -> EnableWindow();
}

void CPODSettingsPrintJobsPage::OnPrintAtTime()
{
  CTimeKey  tTime;
  CPODPrintJobInfo  *pJobInfo;

  if ((pJobInfo = FindJobInfo()))
  { if (IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME))
    { Timespinbox_SetTime(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME),(tTime=CTime::GetCurrentTime().GetTime()+SECONDSPERMINUTE*PODSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL));
      SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE,CB_ADDSTRING,(WPARAM) NULL,(LPARAM) STRING(IDS_PODSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS));
      pJobInfo -> SetPrintMode((pJobInfo -> GetPrintMode() | POD_PRINT_ATTIME) & ~(POD_PRINT_REPEATBYINTERVAL | POD_PRINT_REPEATSTOPBYCOUNT | POD_PRINT_REPEATSTOPBYTIME));
      pJobInfo -> SetPrintAtTime(tTime);
    }
    else
    { SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE,CB_DELETESTRING,(WPARAM) SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) STRING(IDS_PODSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS)));
      pJobInfo -> SetPrintMode(pJobInfo -> GetPrintMode() & ~(POD_PRINT_ATTIME | POD_PRINT_REPEATBYINTERVAL | POD_PRINT_REPEATSTOPBYCOUNT | POD_PRINT_REPEATSTOPBYTIME));
    }
    SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE,CB_SETCURSEL,(IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) ||  IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) ? (WPARAM) SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) ((IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME)) ? STRING(IDS_PODSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS):STRING(IDS_PODSETTINGS_PRINTJOBSPAGE_DAILYPRINTS))):(WPARAM) -1);
    Spinbox_SetRange(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES),(IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME)) ? (PODSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES+1):PODSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES,PODSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES);
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME));
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) ||  IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) ||  IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) ||  IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_ADDJOB) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS,LB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) pJobInfo -> GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE:FALSE);
    SetJobRepetitionInfo();
  }
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME) -> SetFocus();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsPrintJobsPage::OnPrintAtDailyTime()
{
  CTimeKey  tTime;
  CPODPrintJobInfo  *pJobInfo;

  if ((pJobInfo = FindJobInfo()))
  { if (IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME))
    { Timespinbox_SetTime(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME),(tTime=CTime::GetCurrentTime().GetTime()+SECONDSPERMINUTE*PODSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL));
      SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE,CB_ADDSTRING,(WPARAM) NULL,(LPARAM) STRING(IDS_PODSETTINGS_PRINTJOBSPAGE_DAILYPRINTS));
      pJobInfo -> SetPrintMode((pJobInfo -> GetPrintMode() | POD_PRINT_ATDAILYTIME) & ~(POD_PRINT_DAILYREPEATSTOPBYCOUNT | POD_PRINT_DAILYREPEATSTOPBYTIME));
      pJobInfo -> SetPrintAtDailyTime(tTime.GetTime()%SECONDSPERDAY);
    }
    else
    { SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE,CB_DELETESTRING,(WPARAM) SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) STRING(IDS_PODSETTINGS_PRINTJOBSPAGE_DAILYPRINTS)));
      pJobInfo -> SetPrintMode(pJobInfo -> GetPrintMode() & ~(POD_PRINT_ATDAILYTIME | POD_PRINT_DAILYREPEATSTOPBYCOUNT | POD_PRINT_DAILYREPEATSTOPBYTIME));
    }
    SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE,CB_SETCURSEL,(IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) ||  IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) ? (WPARAM) SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) ((IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) ? STRING(IDS_PODSETTINGS_PRINTJOBSPAGE_DAILYPRINTS):STRING(IDS_PODSETTINGS_PRINTJOBSPAGE_NONDAILYPRINTS))):(WPARAM) -1);
    Spinbox_SetRange(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES),(IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME)) ? PODSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES:(PODSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES+1),PODSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES);
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME_STATIC) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITION) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) ||  IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE_STATIC) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) ||  IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONTYPE) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATTIME) ||  IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATDAILYTIME));
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_ADDJOB) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS,LB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) pJobInfo -> GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE:FALSE);
    SetJobRepetitionInfo();
  }
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME) -> SetFocus();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsPrintJobsPage::OnPrintAtEvent()
{
  CString  szEvent;
  CPODPrintJobInfo  *pJobInfo;

  if ((pJobInfo = FindJobInfo()))
  { if (IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT))
    { SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT,CB_SETCURSEL);
      GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT) -> GetWindowText(szEvent);
      pJobInfo -> SetPrintMode(pJobInfo -> GetPrintMode() | POD_PRINT_ATEVENT);
      pJobInfo -> SetPrintAtEvent(szEvent);
    }
    else
    { SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT,CB_SETCURSEL,(WPARAM) -1);
      pJobInfo -> SetPrintMode(pJobInfo -> GetPrintMode() & ~POD_PRINT_ATEVENT);
      pJobInfo -> SetPrintAtEvent(EMPTYSTRING);
    }
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT));
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT_STATIC) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTATEVENT));
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_ADDJOB) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS,LB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) pJobInfo -> GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE:FALSE);
  }
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT) -> SetFocus();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsPrintJobsPage::OnSelchangeEvent()
{
  CString  szEvent;
  CPODPrintJobInfo  *pJobInfo;

  if ((pJobInfo = FindJobInfo()))
  { GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTEVENT) -> GetWindowText(szEvent);
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_ADDJOB) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS,LB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) pJobInfo -> GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE:FALSE);
    pJobInfo -> SetPrintMode(pJobInfo -> GetPrintMode() | POD_PRINT_ATEVENT);
    pJobInfo -> SetPrintAtEvent(szEvent);
  }
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsPrintJobsPage::OnSelchangeRepetitionType()
{
  Spinbox_SetRange(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES),(GetJobRepetitionType() == PODSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY) ? (PODSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES+1):PODSETTINGSPRINTJOBSPAGE_BEHAVIOR_MINIMUMCOPIES,PODSETTINGSPRINTJOBSPAGE_BEHAVIOR_MAXIMUMCOPIES);
  SetJobRepetitionInfo();
}

void CPODSettingsPrintJobsPage::OnRepeatByTime()
{
  CPODPrintJobInfo  *pJobInfo;

  for (CheckDlgButton(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME,!IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME)); IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME); )
  { Spinbox_SetPos(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME),PODSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL);
    break;
  }
  for ( ; (pJobInfo = FindJobInfo()); )
  { if (IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME))
    { pJobInfo -> SetPrintMode((pJobInfo -> GetPrintMode() | POD_PRINT_REPEATBYINTERVAL) & ~(POD_PRINT_REPEATSTOPBYCOUNT | POD_PRINT_REPEATSTOPBYTIME));
      pJobInfo -> SetPrintAtTime(Timespinbox_GetTime(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)),SECONDSPERMINUTE*PODSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTINTERVAL);
      GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_ADDJOB) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS,LB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) pJobInfo -> GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE:FALSE);
      break;
    }
    pJobInfo -> SetPrintMode(pJobInfo -> GetPrintMode() & ~(POD_PRINT_REPEATBYINTERVAL | POD_PRINT_REPEATSTOPBYCOUNT | POD_PRINT_REPEATSTOPBYTIME));
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_ADDJOB) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS,LB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) pJobInfo -> GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE:FALSE);
    break;
  }
  CheckDlgButton(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES,FALSE);
  CheckDlgButton(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME,FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME_STATIC) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOP_STATIC) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATBYTIME));
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME) -> EnableWindow(FALSE);
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME) -> SetFocus();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsPrintJobsPage::OnRepetitionStopByCopies()
{
  CPODPrintJobInfo  *pJobInfo;

  for (CheckDlgButton(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES,!IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)),GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)),GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES)); IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES); )
  { Spinbox_SetPos(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES),PODSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTCOPIES);
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME) -> EnableWindow(FALSE);
    CheckDlgButton(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME,FALSE);
    break;
  }
  for ( ; (pJobInfo = FindJobInfo()); )
  { if (IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES))
    { if (GetJobRepetitionType() == PODSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY)
      { pJobInfo -> SetPrintMode((pJobInfo -> GetPrintMode() | POD_PRINT_REPEATSTOPBYCOUNT) & ~POD_PRINT_REPEATSTOPBYTIME);
        pJobInfo -> SetPrintAtTime(Timespinbox_GetTime(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)),SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)),PODSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTCOPIES);
      }
      if (GetJobRepetitionType() == PODSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY)
      { pJobInfo -> SetPrintMode((pJobInfo -> GetPrintMode() | POD_PRINT_DAILYREPEATSTOPBYCOUNT) & ~POD_PRINT_DAILYREPEATSTOPBYTIME);
        pJobInfo -> SetPrintAtDailyTime(Timespinbox_GetTime(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)).GetTime()%SECONDSPERDAY,PODSETTINGSPRINTJOBSPAGE_BEHAVIOR_DEFAULTCOPIES);
      }
      GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_ADDJOB) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS,LB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) pJobInfo -> GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE:FALSE);
      break;
    }
    pJobInfo -> SetPrintMode((GetJobRepetitionType() == PODSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY) ? (pJobInfo -> GetPrintMode() & ~POD_PRINT_REPEATSTOPBYCOUNT):(pJobInfo -> GetPrintMode() & ~POD_PRINT_DAILYREPEATSTOPBYCOUNT));
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_ADDJOB) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS,LB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) pJobInfo -> GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE:FALSE);
    break;
  }
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES) -> SetFocus();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsPrintJobsPage::OnRepetitionStopByTime()
{
  CTimeKey  tStopTime;
  CPODPrintJobInfo  *pJobInfo;

  for (CheckDlgButton(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME,!IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)),GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME) -> EnableWindow(IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)); IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME); )
  { for (CheckDlgButton(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES,FALSE); GetJobRepetitionType() == PODSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY; )
    { Timespinbox_SetTime(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME),(tStopTime=Timespinbox_GetTime(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)).GetTime()+SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME))));
      break;
    }
    if (GetJobRepetitionType() == PODSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY) Timespinbox_SetTime(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME),(tStopTime=Timespinbox_GetTime(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)).GetTime()+CTimeSpan(1,0,0,0).GetTotalSeconds()));
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES) -> EnableWindow(FALSE);
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYCOPIES_STATIC) -> EnableWindow(FALSE);
    break;
  }
  for ( ; (pJobInfo = FindJobInfo()); )
  { if (IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME))
    { if (GetJobRepetitionType() == PODSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY)
      { pJobInfo -> SetPrintMode((pJobInfo -> GetPrintMode() | POD_PRINT_REPEATSTOPBYTIME) & ~POD_PRINT_REPEATSTOPBYCOUNT);
        pJobInfo -> SetPrintAtTime(Timespinbox_GetTime(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)),SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)),tStopTime);
      }
      if (GetJobRepetitionType() == PODSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY)
      { pJobInfo -> SetPrintMode((pJobInfo -> GetPrintMode() | POD_PRINT_DAILYREPEATSTOPBYTIME) & ~POD_PRINT_DAILYREPEATSTOPBYCOUNT);
        pJobInfo -> SetPrintAtDailyTime(Timespinbox_GetTime(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)).GetTime()%SECONDSPERDAY,tStopTime);
      }
      GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_ADDJOB) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS,LB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) pJobInfo -> GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE:FALSE);
      break;
    }
    pJobInfo -> SetPrintMode((GetJobRepetitionType() == PODSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY) ? (pJobInfo -> GetPrintMode() & ~POD_PRINT_REPEATSTOPBYTIME):(pJobInfo -> GetPrintMode() & ~POD_PRINT_DAILYREPEATSTOPBYTIME));
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_ADDJOB) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS,LB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) pJobInfo -> GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE:FALSE);
    break;
  }
  GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME) -> SetFocus();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsPrintJobsPage::OnSpinchangePrintTime()
{
  UINT  nStopCount;
  CTimeKey  tTime;
  CTimeKey  tStopTime;
  CTimeKey  tPrintTime;
  CTimeKey  tPrintStopTime;
  CTimeSpan  tPrintInterval;
  CPODPrintJobInfo  *pJobInfo;

  if ((pJobInfo = FindJobInfo()))
  { for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)),tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)); pJobInfo -> GetPrintAtTime(tPrintTime); )
    { pJobInfo -> SetPrintAtTime(tTime);
      break;
    }
    if (pJobInfo -> GetPrintAtTime(tPrintTime,tPrintInterval)) pJobInfo -> SetPrintAtTime(tTime,tPrintInterval);
    if (pJobInfo -> GetPrintAtTime(tPrintTime,tPrintInterval,nStopCount)) pJobInfo -> SetPrintAtTime(tTime,tPrintInterval,nStopCount);
    if (pJobInfo -> GetPrintAtTime(tPrintTime,tPrintInterval,tPrintStopTime)) pJobInfo -> SetPrintAtTime(tTime,tPrintInterval,(tTime+tPrintInterval.GetTotalSeconds() > tPrintStopTime.GetTime()) ? CTimeKey(tTime.GetTime()+tPrintInterval.GetTotalSeconds()):tPrintStopTime);
    Timespinbox_SetTime(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME),(GetJobRepetitionType() == PODSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)) ? ((tTime+tPrintInterval.GetTotalSeconds() > tPrintStopTime.GetTime()) ? (tTime.GetTime()+tPrintInterval.GetTotalSeconds()):tPrintStopTime):tStopTime);
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_ADDJOB) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS,LB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) pJobInfo -> GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE:FALSE);
  }
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsPrintJobsPage::OnSpinchangePrintDailyTime()
{
  UINT  nStopCount;
  CTimeKey  tTime;
  CTimeKey  tStopTime;
  CTimeKey  tPrintStopTime;
  CTimeSpan  tPrintTime;
  CPODPrintJobInfo  *pJobInfo;

  if ((pJobInfo = FindJobInfo()))
  { for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTDAILYTIME)),tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)); pJobInfo -> GetPrintAtDailyTime(tPrintTime); )
    { pJobInfo -> SetPrintAtDailyTime(tTime.GetTime()%SECONDSPERDAY);
      break;
    }
    if (pJobInfo -> GetPrintAtDailyTime(tPrintTime,nStopCount)) pJobInfo -> SetPrintAtDailyTime(tTime.GetTime()%SECONDSPERDAY,nStopCount);
    if (pJobInfo -> GetPrintAtDailyTime(tPrintTime,tPrintStopTime)) pJobInfo -> SetPrintAtDailyTime(tTime.GetTime()%SECONDSPERDAY,(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime()/SECONDSPERDAY)+tTime.GetTime()%SECONDSPERDAY > tPrintStopTime.GetTime()) ? CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime()/SECONDSPERDAY+1)+tTime.GetTime()%SECONDSPERDAY):tPrintStopTime);
    Timespinbox_SetTime(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME),(GetJobRepetitionType() == PODSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)) ? ((SECONDSPERDAY*(CTime::GetCurrentTime().GetTime()/SECONDSPERDAY)+tTime.GetTime()%SECONDSPERDAY > tPrintStopTime.GetTime()) ? CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime()/SECONDSPERDAY+1)+tTime.GetTime()%SECONDSPERDAY):tPrintStopTime):tStopTime);
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_ADDJOB) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS,LB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) pJobInfo -> GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE:FALSE);
  }
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsPrintJobsPage::OnSpinchangeRepeatTime()
{
  UINT  nStopCount;
  CTimeKey  tTime;
  CTimeKey  tStopTime;
  CTimeKey  tPrintTime;
  CTimeKey  tPrintStopTime;
  CTimeSpan  tPrintInterval;
  CPODPrintJobInfo  *pJobInfo;

  if ((pJobInfo = FindJobInfo()))
  { for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)),tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)); pJobInfo -> GetPrintAtTime(tPrintTime,tPrintInterval); )
    { pJobInfo -> SetPrintAtTime(tPrintTime,SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)));
      break;
    }
    if (pJobInfo -> GetPrintAtTime(tPrintTime,tPrintInterval,nStopCount)) pJobInfo -> SetPrintAtTime(tPrintTime,SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)),nStopCount);
    if (pJobInfo -> GetPrintAtTime(tPrintTime,tPrintInterval,tPrintStopTime)) pJobInfo -> SetPrintAtTime(tPrintTime,SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)),(tPrintTime.GetTime()+SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)) > tPrintStopTime.GetTime()) ? CTimeKey(tPrintTime.GetTime()+SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME))):tPrintStopTime);
    Timespinbox_SetTime(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME),(GetJobRepetitionType() == PODSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  IsDlgButtonChecked(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPBYTIME)) ? ((tPrintTime.GetTime()+SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME)) > tPrintStopTime.GetTime()) ? CTimeKey(tPrintTime.GetTime()+SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPEATTIME))):tPrintStopTime):tStopTime);
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_ADDJOB) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS,LB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) pJobInfo -> GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE:FALSE);
  }
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsPrintJobsPage::OnSpinchangeRepetitionStopCopies()
{
  UINT  nStopCount;
  UINT  nPrintStopCount;
  CTimeKey  tPrintTime;
  CTimeSpan  tPrintInterval;
  CTimeSpan  tPrintDailyTime;
  CPODPrintJobInfo  *pJobInfo;

  if ((pJobInfo = FindJobInfo()))
  { for (nStopCount = (UINT) Spinbox_GetPos(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPCOPIES)); GetJobRepetitionType() == PODSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  pJobInfo -> GetPrintAtTime(tPrintTime,tPrintInterval,nPrintStopCount); )
    { pJobInfo -> SetPrintAtTime(tPrintTime,tPrintInterval,nStopCount);
      break;
    }
    if (GetJobRepetitionType() == PODSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  pJobInfo -> GetPrintAtDailyTime(tPrintDailyTime,nPrintStopCount)) pJobInfo -> SetPrintAtDailyTime(tPrintDailyTime,nStopCount);
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_ADDJOB) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS,LB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) pJobInfo -> GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE:FALSE);
  }
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODSettingsPrintJobsPage::OnSpinchangeRepetitionStopTime()
{
  CTimeKey  tTime;
  CTimeKey  tTimeKey;
  CTimeKey  tStopTime;
  CTimeKey  tPrintTime;
  CTimeKey  tPrintStopTime;
  CTimeSpan  tPrintInterval;
  CTimeSpan  tPrintDailyTime;
  CPODPrintJobInfo  *pJobInfo;

  if ((pJobInfo = FindJobInfo()))
  { for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_PRINTTIME)),tStopTime = Timespinbox_GetTime(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME)); GetJobRepetitionType() == PODSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_NONDAILY  &&  pJobInfo -> GetPrintAtTime(tPrintTime,tPrintInterval,tPrintStopTime); )
    { if (tTime > tStopTime.GetTime()-tPrintInterval.GetTotalSeconds()) Timespinbox_SetTime(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME),(tStopTime=tTime.GetTime()+tPrintInterval.GetTotalSeconds()));
      pJobInfo -> SetPrintAtTime(tTime,tPrintInterval,tStopTime);
      break;
    }
    if (GetJobRepetitionType() == PODSETTINGSPRINTJOBSPAGE_REPETITIONTYPE_DAILY  &&  pJobInfo -> GetPrintAtDailyTime(tPrintDailyTime,tPrintStopTime))
    { if (SECONDSPERDAY*(tTimeKey.GetTime()/SECONDSPERDAY)+tPrintDailyTime.GetTotalSeconds() > tStopTime.GetTime()) Timespinbox_SetTime(GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_BEHAVIOR_REPETITIONSTOPTIME),(tStopTime=SECONDSPERDAY*(tTimeKey.GetTime()/SECONDSPERDAY)+tPrintDailyTime.GetTotalSeconds()));
      pJobInfo -> SetPrintAtDailyTime(tPrintDailyTime,tStopTime);
    }
    GetDlgItem(IDC_PODSETTINGS_PRINTJOBSPAGE_ADDJOB) -> EnableWindow((SendDlgItemMessage(IDC_PODSETTINGS_PRINTJOBSPAGE_ACTIVEJOBS,LB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) pJobInfo -> GetName()) == LB_ERR  &&  CheckJobInfo()) ? TRUE:FALSE);
  }
  GetDlgItem(IDOK) -> EnableWindow(Check());
}


/////////////////////////////////////////////////////////////////////////////
// CPODSettingsTabCtrl

IMPLEMENT_DYNCREATE(CPODSettingsTabCtrl,CTabCtrl)

BEGIN_MESSAGE_MAP(CPODSettingsTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CPODSettingsTabCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPODSettingsTabCtrl message handlers


/////////////////////////////////////////////////////////////////////////////
// CPODSettingsDialog

IMPLEMENT_DYNCREATE(CPODSettingsDialog,CDisplayPropertySheetDialog)

CPODSettingsDialog::CPODSettingsDialog() : CDisplayPropertySheetDialog()
{
  AddPage(&m_pageLayout);
  AddPage(&m_pageContents);
  AddPage(&m_pageFiltering);
  AddPage(&m_pageRetrieving);
  AddPage(&m_pagePrinting);
  AddPage(&m_pagePrintJobs);
}

BOOL CPODSettingsDialog::GetLayout(CPODLayout &cLayout) CONST
{
  return(((GetActivePage() -> GetSafeHwnd() != m_pageContents.GetSafeHwnd() &&  m_pageLayout.GetLayout(cLayout)) || (GetActivePage() -> GetSafeHwnd() == m_pageContents.GetSafeHwnd() &&  m_pageContents.GetLayout(cLayout))) ? TRUE:FALSE);
}

BOOL CPODSettingsDialog::GetLayoutTitleFonts(LPLOGFONT pDataFont,LPLOGFONT pParametersFont,LPLOGFONT pFunctionsFont) CONST
{
  return m_pageLayout.GetTitleFonts(pDataFont,pParametersFont,pFunctionsFont);
}

BOOL CPODSettingsDialog::GetLayoutItemsFonts(LPLOGFONT pDataFont,LPLOGFONT pParametersFont,LPLOGFONT pFunctionsFont) CONST
{
  return m_pageLayout.GetItemsFonts(pDataFont,pParametersFont,pFunctionsFont);
}

BOOL CPODSettingsDialog::GetLayoutToolTipMode(BOOL &bEnable) CONST
{
  return m_pageLayout.GetToolTipMode(bEnable);
}

BOOL CPODSettingsDialog::IsLayoutModified() CONST
{
  return m_pageLayout.IsModified() ||  m_pageContents.IsModified() ||  m_pageFiltering.IsModified();
}

BOOL CPODSettingsDialog::GetFilterMode(UINT &nMode) CONST
{
  return m_pageFiltering.GetMode(nMode);
}

BOOL CPODSettingsDialog::GetFilterLimit(UINT &nLimit) CONST
{
  return m_pageFiltering.GetLimit(nLimit);
}

BOOL CPODSettingsDialog::GetFilterDigits(UINT &nDigits) CONST
{
  return m_pageFiltering.GetDigits(nDigits);
}

BOOL CPODSettingsDialog::GetFilterStatus(UINT &nStatus) CONST
{
  return m_pageFiltering.GetStatus(nStatus);
}

BOOL CPODSettingsDialog::GetFilterRange(CTimeKey &tStartTime,CTimeKey &tStopTime) CONST
{
  return m_pageFiltering.GetRange(tStartTime,tStopTime);
}

BOOL CPODSettingsDialog::GetFilterDailyRange(CTimeSpan &tStartTime,CTimeSpan &tStopTime) CONST
{
  return m_pageFiltering.GetDailyRange(tStartTime,tStopTime);
}

BOOL CPODSettingsDialog::GetFilterPeriodicalRange(CTimeKey &tStartTime,CTimeSpan &tInterval,CTimeKey &tStopTime) CONST
{
  return m_pageFiltering.GetPeriodicalRange(tStartTime,tInterval,tStopTime);
}

BOOL CPODSettingsDialog::GetFilterColors(CUIntArray &nColors) CONST
{
  return m_pageFiltering.GetColors(nColors);
}

BOOL CPODSettingsDialog::IsFilteringModified() CONST
{
  return m_pageFiltering.IsModified();
}

BOOL CPODSettingsDialog::GetRetrieveFileName(CString &szFileName) CONST
{
  return m_pageRetrieving.GetDataSourceFileName(szFileName);
}

BOOL CPODSettingsDialog::IsRetrievingModified() CONST
{
  return m_pageRetrieving.IsModified();
}

BOOL CPODSettingsDialog::GetPrintJobs(CPODPrintJobs &pPrintJobs) CONST
{
  return(((GetActivePage() -> GetSafeHwnd() != m_pagePrintJobs.GetSafeHwnd() &&  m_pagePrinting.GetJobs(pPrintJobs)) || (GetActivePage() -> GetSafeHwnd() == m_pagePrintJobs.GetSafeHwnd() &&  m_pagePrintJobs.GetJobs(pPrintJobs))) ? TRUE:FALSE);
}

BOOL CPODSettingsDialog::IsPrintingModified() CONST
{
  return m_pagePrinting.IsModified() ||  m_pagePrintJobs.IsModified();
}

CPODOpenDialog *CPODSettingsDialog::GetParentDialog() CONST
{
  return((GetParent() != (CWnd *) GetParentDisplay()) ? (CPODOpenDialog *) GetParent():(CPODOpenDialog *) NULL);
}

CPODWnd *CPODSettingsDialog::GetParentDisplay() CONST
{
  return((CPODWnd *) CDisplayPropertySheetDialog::GetParentDisplay());
}

BEGIN_MESSAGE_MAP(CPODSettingsDialog, CDisplayPropertySheetDialog)
	//{{AFX_MSG_MAP(CPODSettingsDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDHELP,OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPODSettingsDialog message handlers

BOOL CPODSettingsDialog::OnInitDialog() 
{
  INT  nPage;
  INT  nPages;
  CHourglassCursor  cCursor;

  CDisplayPropertySheetDialog::OnInitDialog();
  SetTitle(STRING(IDS_PODSETTINGSDIALOG_TITLE));
  for (nPage = 0,nPages = GetPageCount(),m_wndTabCtrl.SubclassWindow(GetTabControl() -> GetSafeHwnd()); nPage < nPages; nPage++)
  { SetActivePage((nPage+1)%nPages);
    continue;
  }
  m_wndTabCtrl.SetFocus();
  return FALSE;
}

BOOL CPODSettingsDialog::OnNotify(WPARAM wParam,LPARAM lParam,LRESULT *pResult) 
{
  CRect  rTab;
  CPODPrintJobs  pPrintJobs;
  LPNMHDR  pNotifyInfo=(LPNMHDR) lParam;

  if (pNotifyInfo -> code == TCN_SELCHANGING)
  { if (HIBYTE(GetKeyState(VK_RIGHT)) &&  GetActivePage() -> GetSafeHwnd() == m_pagePrinting.GetSafeHwnd() &&  m_pagePrinting.GetJobs(pPrintJobs) &&  pPrintJobs.GetSize() <= 1)
    { CAudioDevice::AlertBySound();
      *pResult = TRUE;
      return TRUE;
    }
    if (HIBYTE(GetKeyState(VK_LBUTTON)))
    { if (GetPrintJobs(pPrintJobs) &&  pPrintJobs.GetSize() <= 1)
      { if (GetTabControl() -> GetItemRect(GetPageIndex(&m_pagePrintJobs),rTab))
        { GetTabControl() -> ClientToScreen(rTab);
          if (rTab.PtInRect(GetCurrentMessage() -> pt))
          { CAudioDevice::AlertBySound();
            *pResult = TRUE;
            return TRUE;
          }
        }
      }
    }
  }
  return CDisplayPropertySheetDialog::OnNotify(wParam,lParam,pResult);
}

BOOL CPODSettingsDialog::OnDataExchange(HWND hPage,CONST CPODLayout &cLayout)
{
  return(((hPage == m_pageLayout.GetSafeHwnd() &&  m_pageContents.OnDataExchange(cLayout)) || (hPage == m_pageContents.GetSafeHwnd() &&  m_pageLayout.OnDataExchange(cLayout))) ? TRUE:FALSE);
}
BOOL CPODSettingsDialog::OnDataExchange(HWND hPage,CONST CPODPrintJobs &pJobs)
{
  return(((hPage == m_pagePrinting.GetSafeHwnd() &&  m_pagePrintJobs.OnDataExchange(pJobs)) || (hPage == m_pagePrintJobs.GetSafeHwnd() &&  m_pagePrinting.OnDataExchange(pJobs))) ? TRUE:FALSE);
}

void CPODSettingsDialog::OnOK()
{
  CHourglassCursor  cCursor;

  ReportEvent(((!GetParentDialog() &&  !GetParentDisplay() -> OnCloseSettingsDialog(IDOK)) || (GetParentDialog() &&  !GetParentDialog() -> OnCloseSettingsDialog(IDOK))) ? SYSTEM_WARNING_POD_SETUP_FAILURE:SYSTEM_NOERROR);
  CDisplayPropertySheetDialog::OnOK();  
}

void CPODSettingsDialog::OnCancel()
{
  CHourglassCursor  cCursor;

  if (!GetParentDialog()) GetParentDisplay() -> OnCloseSettingsDialog(IDCANCEL);
  else  GetParentDialog() -> OnCloseSettingsDialog(IDCANCEL);
  CDisplayPropertySheetDialog::OnCancel();
}

BOOL CPODSettingsDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
  CHourglassCursor  cCursor;

  ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_PODSETTINGSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE:SYSTEM_NOERROR);
  return TRUE;
}

void CPODSettingsDialog::OnHelp()
{
  CHourglassCursor  cCursor;

  ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_PODSETTINGSDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE:SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CPODLinkagesDialog dialog

IMPLEMENT_DYNCREATE(CPODLinkagesDialog,CDisplayDialog)

CPODLinkagesDialog::CPODLinkagesDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CPODLinkagesDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CPODLinkagesDialog::Create(CWnd *pParentWnd)
{
  return CDisplayDialog::Create(pParentWnd,CPODLinkagesDialog::IDD);
}

BOOL CPODLinkagesDialog::Initialize()
{
  GetDisplayArea() -> EnumDisplays(m_pDisplays[0]);
  GetParent() -> GetLinks(m_pDisplays[1]);
  return TRUE;
}

CPODWnd *CPODLinkagesDialog::GetParent() CONST
{
  return((CPODWnd *) CDisplayDialog::GetParent());
}

BOOL CPODLinkagesDialog::EnumDisplays()
{
  INT  nDisplay[2];
  INT  nDisplays[2];
  CString  szDisplay;
  CDisplayWnd  *pDisplayWnd;

  for (nDisplay[0] = 0,nDisplays[0] = (INT) m_pDisplays[0].GetSize(),SendDlgItemMessage(IDC_POD_LINKAGES_DISPLAYS,CB_RESETCONTENT),SendDlgItemMessage(IDC_POD_LINKAGES_LIST,LB_RESETCONTENT); nDisplay[0] < nDisplays[0]; nDisplay[0]++)
  { if ((pDisplayWnd = (CDisplayWnd *) m_pDisplays[0].GetAt(nDisplay[0])) == GetParent() ||  !pDisplayWnd -> IsLinkable())
    { m_pDisplays[0].RemoveAt(nDisplay[0]);
      nDisplays[0]--;
      nDisplay[0]--;
      continue;
    }
    for (nDisplay[1] = 0,nDisplays[1] = (INT) m_pDisplays[1].GetSize(); nDisplay[1] < nDisplays[1]; nDisplay[1]++)
    { if ((pDisplayWnd = (CDisplayWnd *) m_pDisplays[0].GetAt(nDisplay[0])) &&  pDisplayWnd == (CDisplayWnd *) m_pDisplays[1].GetAt(nDisplay[1]))
      { m_pDisplays[0].RemoveAt(nDisplay[0]);
        nDisplays[0]--;
        nDisplay[0]--;
        break;
      }
    }
  }
  for (nDisplay[0] = 0,nDisplays[0] = (INT) m_pDisplays[0].GetSize(); nDisplay[0] < nDisplays[0]; nDisplay[0]++)
  { if ((pDisplayWnd = (CDisplayWnd *) m_pDisplays[0].GetAt(nDisplay[0])) != (CDisplayWnd *) NULL)
    { for (pDisplayWnd -> GetWindowText(szDisplay); SendDlgItemMessage(IDC_POD_LINKAGES_DISPLAYS,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) szDisplay) < 0  &&  !szDisplay.IsEmpty(); )
      { SendDlgItemMessage(IDC_POD_LINKAGES_DISPLAYS,CB_INSERTSTRING,nDisplay[0],(LPARAM) (LPCTSTR) szDisplay);
        break;
      }
    }
  }
  for (nDisplay[1] = 0,nDisplays[1] = (INT) m_pDisplays[1].GetSize(),m_pDisplays[2].Copy(m_pDisplays[1]); nDisplay[1] < nDisplays[1]; nDisplay[1]++)
  { if ((pDisplayWnd = (CDisplayWnd *) m_pDisplays[1].GetAt(nDisplay[1])) != (CDisplayWnd *) NULL)
    { for (pDisplayWnd -> GetWindowText(szDisplay); SendDlgItemMessage(IDC_POD_LINKAGES_LIST,LB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) szDisplay) < 0  &&  !szDisplay.IsEmpty(); )
      { SendDlgItemMessage(IDC_POD_LINKAGES_LIST,LB_INSERTSTRING,nDisplay[1],(LPARAM) (LPCTSTR) szDisplay);
        break;
      }
    }
  }
  SendDlgItemMessage(IDC_POD_LINKAGES_LIST,LB_SETCURSEL);
  SendDlgItemMessage(IDC_POD_LINKAGES_DISPLAYS,CB_SETCURSEL);
  GetDlgItem(IDC_POD_LINKAGES_DISPLAYS_STATIC) -> EnableWindow((SendDlgItemMessage(IDC_POD_LINKAGES_DISPLAYS,CB_GETCOUNT) > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_LINKAGES_DISPLAYS) -> EnableWindow((SendDlgItemMessage(IDC_POD_LINKAGES_DISPLAYS,CB_GETCOUNT) > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_LINKAGES_LIST_STATIC) -> EnableWindow((SendDlgItemMessage(IDC_POD_LINKAGES_LIST,LB_GETCOUNT) > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_LINKAGES_LIST) -> EnableWindow((SendDlgItemMessage(IDC_POD_LINKAGES_LIST,LB_GETCOUNT) > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_LINKAGES_ADD) -> EnableWindow((SendDlgItemMessage(IDC_POD_LINKAGES_DISPLAYS,CB_GETCURSEL) >= 0) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_LINKAGES_REMOVE) -> EnableWindow((SendDlgItemMessage(IDC_POD_LINKAGES_LIST,LB_GETCURSEL) >= 0) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_LINKAGES_REMOVEALL) -> EnableWindow((SendDlgItemMessage(IDC_POD_LINKAGES_LIST,LB_GETCOUNT) > 0) ? TRUE:FALSE);
  return TRUE;
}

INT CPODLinkagesDialog::FindDisplay(LPCTSTR pszName,BOOL bLinked) CONST
{
  INT  nDisplay;
  INT  nDisplays;
  CString  szDisplay;
  CDisplayWnd  *pDisplayWnd;

  for (nDisplay = 0,nDisplays = (INT) m_pDisplays[bLinked].GetSize(); nDisplay < nDisplays; nDisplay++)
  { if ((pDisplayWnd = (CDisplayWnd *) m_pDisplays[bLinked].GetAt(nDisplay)))
    { pDisplayWnd -> GetWindowText(szDisplay);
      if (!szDisplay.Compare(pszName)) break;
    }
  }
  return((nDisplay < nDisplays) ? nDisplay:-1);
}

BOOL CPODLinkagesDialog::IsModified() CONST
{
  INT  nDisplay[2];
  INT  nDisplays[2];

  for (nDisplay[0] = 0,nDisplays[0] = (m_pDisplays[1].GetSize() == m_pDisplays[2].GetSize()) ? (INT) m_pDisplays[1].GetSize():-1; nDisplay[0] < nDisplays[0]; nDisplay[0]++)
  { for (nDisplay[1] = 0,nDisplays[1] = (INT) m_pDisplays[2].GetSize(); nDisplay[1] < nDisplays[1]; nDisplay[1]++)
    { if (m_pDisplays[1].GetAt(nDisplay[0]) == m_pDisplays[2].GetAt(nDisplay[1])) break;
      continue;
    }
    if (nDisplay[1] == nDisplays[1]) break;
  }
  return((nDisplay[0] != nDisplays[0]) ? TRUE:FALSE);
}

BOOL CPODLinkagesDialog::Check(BOOL bModified) CONST
{
  return(!bModified  ||  IsModified());
}

void CPODLinkagesDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPODLinkagesDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CPODLinkagesDialog::PostNcDestroy()
{
  m_pDisplays[0].RemoveAll();
  m_pDisplays[1].RemoveAll();
  m_pDisplays[2].RemoveAll();
  CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CPODLinkagesDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CPODLinkagesDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_POD_LINKAGES_ADD,OnAddDisplay)
	ON_BN_CLICKED(IDC_POD_LINKAGES_REMOVE,OnRemoveLinkedDisplay)
	ON_BN_CLICKED(IDC_POD_LINKAGES_REMOVEALL,OnRemoveAllLinkedDisplays)
	ON_BN_CLICKED(IDC_POD_LINKAGES_HELP,OnHelp)
	ON_LBN_SELCHANGE(IDC_POD_LINKAGES_LIST,OnSelchangeLinkedDisplay)
	ON_CBN_EDITCHANGE(IDC_POD_LINKAGES_DISPLAYS,OnEditchangeDisplay)
	ON_CBN_SELCHANGE(IDC_POD_LINKAGES_DISPLAYS,OnSelchangeDisplay)
	ON_CBN_DBLCLK(IDC_POD_LINKAGES_DISPLAYS,OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPODLinkagesDialog message handlers

BOOL CPODLinkagesDialog::OnInitDialog()
{
  CString  szDisplay;
  CHourglassCursor  cCursor;

  for (CDisplayDialog::OnInitDialog(),GetParent() -> GetWindowText(szDisplay); EnumDisplays(); )
  { GetDlgItem(IDC_POD_LINKAGES_NAME) -> SetWindowText(szDisplay);
    GetDlgItem(IDC_POD_LINKAGES_DETAILS) -> EnableWindow();
    GetDlgItem(IDC_POD_LINKAGES_NAME_STATIC) -> EnableWindow();
    GetDlgItem(IDC_POD_LINKAGES_NAME) -> EnableWindow();
    GetDlgItem(IDC_POD_LINKAGES_DISPLAYS) -> SetFocus();
    return FALSE;
  }
  return TRUE;
}

void CPODLinkagesDialog::OnAddDisplay()
{
  INT  nIndex[2];
  CString  szDisplay;
  CHourglassCursor  cCursor;

  for (GetDlgItem(IDC_POD_LINKAGES_DISPLAYS) -> GetWindowText(szDisplay); (nIndex[0] = FindDisplay(szDisplay)) >= 0; )
  { if ((nIndex[1] = (INT) SendDlgItemMessage(IDC_POD_LINKAGES_LIST,LB_INSERTSTRING,(WPARAM) -1,(LPARAM) (LPCTSTR) szDisplay)) >= 0)
    { for (SendDlgItemMessage(IDC_POD_LINKAGES_LIST,LB_SETCURSEL,nIndex[1]); SendDlgItemMessage(IDC_POD_LINKAGES_DISPLAYS,CB_DELETESTRING,(WPARAM) SendDlgItemMessage(IDC_POD_LINKAGES_DISPLAYS,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) szDisplay)) >= 0; )
      { m_pDisplays[1].Add(m_pDisplays[0].GetAt(nIndex[0]));
        m_pDisplays[0].RemoveAt(nIndex[0]);
        break;
      }
      SendDlgItemMessage(IDC_POD_LINKAGES_DISPLAYS,CB_SETCURSEL);
      GetDlgItem(IDC_POD_LINKAGES_ADD) -> EnableWindow((SendDlgItemMessage(IDC_POD_LINKAGES_DISPLAYS,CB_GETCURSEL) >= 0) ? TRUE:FALSE);
      GetDlgItem(IDC_POD_LINKAGES_REMOVE) -> EnableWindow((SendDlgItemMessage(IDC_POD_LINKAGES_LIST,LB_GETCURSEL) >= 0) ? TRUE:FALSE);
      GetDlgItem(IDC_POD_LINKAGES_REMOVEALL) -> EnableWindow((SendDlgItemMessage(IDC_POD_LINKAGES_LIST,LB_GETCOUNT) > 0) ? TRUE:FALSE);
      GetDlgItem(IDC_POD_LINKAGES_DISPLAYS_STATIC) -> EnableWindow((SendDlgItemMessage(IDC_POD_LINKAGES_DISPLAYS,CB_GETCOUNT) > 0) ? TRUE:FALSE);
      GetDlgItem(IDC_POD_LINKAGES_DISPLAYS) -> EnableWindow((SendDlgItemMessage(IDC_POD_LINKAGES_DISPLAYS,CB_GETCOUNT) > 0) ? TRUE:FALSE);
      GetDlgItem(IDC_POD_LINKAGES_LIST_STATIC) -> EnableWindow((SendDlgItemMessage(IDC_POD_LINKAGES_LIST,LB_GETCOUNT) > 0) ? TRUE:FALSE);
      GetDlgItem(IDC_POD_LINKAGES_LIST) -> EnableWindow((SendDlgItemMessage(IDC_POD_LINKAGES_LIST,LB_GETCOUNT) > 0) ? TRUE:FALSE);
      GetDlgItem(IDC_POD_LINKAGES_LIST) -> SetFocus();
    }
    break;
  }
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODLinkagesDialog::OnRemoveLinkedDisplay()
{
  INT  nIndex[2];
  CString  szDisplay;
  CHourglassCursor  cCursor;

  for (szDisplay = Listbox_GetText(GetDlgItem(IDC_POD_LINKAGES_LIST),(INT) SendDlgItemMessage(IDC_POD_LINKAGES_LIST,LB_GETCURSEL)); (nIndex[0] = FindDisplay(szDisplay,TRUE)) >= 0; )
  { if ((nIndex[1] = (INT) SendDlgItemMessage(IDC_POD_LINKAGES_DISPLAYS,CB_INSERTSTRING,(WPARAM) -1,(LPARAM) (LPCTSTR) szDisplay)) >= 0)
    { for (SendDlgItemMessage(IDC_POD_LINKAGES_DISPLAYS,CB_SETCURSEL,nIndex[1]); SendDlgItemMessage(IDC_POD_LINKAGES_LIST,LB_DELETESTRING,(WPARAM) SendDlgItemMessage(IDC_POD_LINKAGES_LIST,LB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) szDisplay)) >= 0; )
      { m_pDisplays[0].Add(m_pDisplays[1].GetAt(nIndex[0]));
        m_pDisplays[1].RemoveAt(nIndex[0]);
        break;
      }
      SendDlgItemMessage(IDC_POD_LINKAGES_LIST,LB_SETCURSEL);
      GetDlgItem(IDC_POD_LINKAGES_ADD) -> EnableWindow((SendDlgItemMessage(IDC_POD_LINKAGES_DISPLAYS,CB_GETCURSEL) >= 0) ? TRUE:FALSE);
      GetDlgItem(IDC_POD_LINKAGES_REMOVE) -> EnableWindow((SendDlgItemMessage(IDC_POD_LINKAGES_LIST,LB_GETCURSEL) >= 0) ? TRUE:FALSE);
      GetDlgItem(IDC_POD_LINKAGES_REMOVEALL) -> EnableWindow((SendDlgItemMessage(IDC_POD_LINKAGES_LIST,LB_GETCOUNT) > 0) ? TRUE:FALSE);
      GetDlgItem(IDC_POD_LINKAGES_DISPLAYS_STATIC) -> EnableWindow((SendDlgItemMessage(IDC_POD_LINKAGES_DISPLAYS,CB_GETCOUNT) > 0) ? TRUE:FALSE);
      GetDlgItem(IDC_POD_LINKAGES_DISPLAYS) -> EnableWindow((SendDlgItemMessage(IDC_POD_LINKAGES_DISPLAYS,CB_GETCOUNT) > 0) ? TRUE:FALSE);
      GetDlgItem(IDC_POD_LINKAGES_LIST_STATIC) -> EnableWindow((SendDlgItemMessage(IDC_POD_LINKAGES_LIST,LB_GETCOUNT) > 0) ? TRUE:FALSE);
      GetDlgItem(IDC_POD_LINKAGES_LIST) -> EnableWindow((SendDlgItemMessage(IDC_POD_LINKAGES_LIST,LB_GETCOUNT) > 0) ? TRUE:FALSE);
      GetDlgItem(IDC_POD_LINKAGES_DISPLAYS) -> SetFocus();
    }
    break;
  }
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODLinkagesDialog::OnRemoveAllLinkedDisplays()
{
  INT  nDisplay;
  INT  nDisplays;
  CHourglassCursor  cCursor;

  for (nDisplay = 0,nDisplays = (INT) SendDlgItemMessage(IDC_POD_LINKAGES_LIST,LB_GETCOUNT),m_pDisplays[0].Append(m_pDisplays[1]),m_pDisplays[1].RemoveAll(); nDisplay < nDisplays; nDisplay++)
  { if (SendDlgItemMessage(IDC_POD_LINKAGES_DISPLAYS,CB_INSERTSTRING,(WPARAM) -1,(LPARAM) (LPCTSTR) Listbox_GetText(GetDlgItem(IDC_POD_LINKAGES_LIST),nDisplay)) >= 0)
    { SendDlgItemMessage(IDC_POD_LINKAGES_LIST,LB_DELETESTRING,nDisplay);
      nDisplays--;
      nDisplay--;
    }
  }
  SendDlgItemMessage(IDC_POD_LINKAGES_LIST,LB_SETCURSEL);
  SendDlgItemMessage(IDC_POD_LINKAGES_DISPLAYS,CB_SETCURSEL);
  GetDlgItem(IDC_POD_LINKAGES_ADD) -> EnableWindow((SendDlgItemMessage(IDC_POD_LINKAGES_DISPLAYS,CB_GETCURSEL) >= 0) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_LINKAGES_REMOVE) -> EnableWindow((SendDlgItemMessage(IDC_POD_LINKAGES_LIST,LB_GETCURSEL) >= 0) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_LINKAGES_REMOVEALL) -> EnableWindow((SendDlgItemMessage(IDC_POD_LINKAGES_LIST,LB_GETCOUNT) > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_LINKAGES_DISPLAYS_STATIC) -> EnableWindow((SendDlgItemMessage(IDC_POD_LINKAGES_DISPLAYS,CB_GETCOUNT) > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_LINKAGES_DISPLAYS) -> EnableWindow((SendDlgItemMessage(IDC_POD_LINKAGES_DISPLAYS,CB_GETCOUNT) > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_LINKAGES_LIST_STATIC) -> EnableWindow((SendDlgItemMessage(IDC_POD_LINKAGES_LIST,LB_GETCOUNT) > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_LINKAGES_LIST) -> EnableWindow((SendDlgItemMessage(IDC_POD_LINKAGES_LIST,LB_GETCOUNT) > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_LINKAGES_DISPLAYS) -> SetFocus();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODLinkagesDialog::OnEditchangeDisplay()
{
  CString  szDisplay;

  GetDlgItem(IDC_POD_LINKAGES_DISPLAYS) -> GetWindowText(szDisplay);
  GetDlgItem(IDC_POD_LINKAGES_ADD) -> EnableWindow((SendDlgItemMessage(IDC_POD_LINKAGES_DISPLAYS,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) szDisplay) >= 0  &&  SendDlgItemMessage(IDC_POD_LINKAGES_LIST,LB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) szDisplay) < 0) ? TRUE:FALSE);
}

void CPODLinkagesDialog::OnSelchangeDisplay()
{
  GetDlgItem(IDC_POD_LINKAGES_ADD) -> EnableWindow();
}

void CPODLinkagesDialog::OnSelchangeLinkedDisplay()
{
  GetDlgItem(IDC_POD_LINKAGES_REMOVE) -> EnableWindow();
}

void CPODLinkagesDialog::OnOK()
{
  INT  nDisplay[2];
  INT  nDisplays[2];
  CString  szLink;
  CDisplayWnd  *pDisplayWnd[2];
  CHourglassCursor  cCursor;

  for (nDisplay[0] = 0,nDisplays[0] = (INT) m_pDisplays[1].GetSize(); nDisplay[0] < nDisplays[0]; nDisplay[0]++)
  { for (nDisplay[1] = 0,nDisplays[1] = (INT) m_pDisplays[2].GetSize(); nDisplay[1] < nDisplays[1]; nDisplay[1]++)
    { if (m_pDisplays[1].GetAt(nDisplay[0]) == m_pDisplays[2].GetAt(nDisplay[1]))
      { m_pDisplays[1].RemoveAt(nDisplay[0]);
        m_pDisplays[2].RemoveAt(nDisplay[1]);
        nDisplays[0]--;
        nDisplays[1]--;
        nDisplay[0]--;
        nDisplay[1]--;
        break;
      }
    }
  }
  for (nDisplay[0] = 0,nDisplays[0] = (INT) m_pDisplays[1].GetSize(); nDisplay[0] < nDisplays[0]; nDisplay[0]++)
  { if ((pDisplayWnd[0] = (CDisplayWnd *) m_pDisplays[1].GetAt(nDisplay[0])) -> Lock())
    { if ((pDisplayWnd[1] = GetParent()) -> Lock())
      { pDisplayWnd[1] -> GetWindowText(szLink);
        pDisplayWnd[0] -> SetLink(pDisplayWnd[1]);
        pDisplayWnd[0] -> SetLinkByName(szLink);
        pDisplayWnd[1] -> AddLink(pDisplayWnd[0]);
        pDisplayWnd[1] -> Unlock();
      }
      pDisplayWnd[0] -> InitializeTMData(pDisplayWnd[1] -> GetMode());
      pDisplayWnd[0] -> Unlock();
    }
  }
  for (nDisplay[1] = 0,nDisplays[1] = (INT) m_pDisplays[2].GetSize(); nDisplay[1] < nDisplays[1]; nDisplay[1]++)
  { if ((pDisplayWnd[0] = (CDisplayWnd *) m_pDisplays[2].GetAt(nDisplay[1])) -> Lock())
    { if ((pDisplayWnd[1] = GetParent()) -> Lock())
      { pDisplayWnd[0] -> SetLink();
        pDisplayWnd[0] -> SetLinkByName();
        pDisplayWnd[1] -> RemoveLink(pDisplayWnd[0]);
        pDisplayWnd[1] -> Unlock();
      }
      pDisplayWnd[0] -> Unlock();
      pDisplayWnd[0] -> UpdateBars();
    }
  }
  for ( ; nDisplays[0] == 1; )
  { pDisplayWnd[0] -> ActivateFrame(SW_SHOWNORMAL);
    break;
  }
  CDisplayDialog::OnOK();
}

BOOL CPODLinkagesDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
  CHourglassCursor  cCursor;

  ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_PODLINKAGESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE:SYSTEM_NOERROR);
  return TRUE;
}

void CPODLinkagesDialog::OnHelp()
{
  CHourglassCursor  cCursor;

  ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_PODLINKAGESDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE:SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CPODRetrieveDialog dialog

IMPLEMENT_DYNCREATE(CPODRetrieveDialog,CDisplayDialog)

CPODRetrieveDialog::CPODRetrieveDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CPODRetrieveDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CPODRetrieveDialog::Create(CWnd *pParentWnd)
{
  INT  nPos;
  CString  szType;
  CString  szTitle;
  CPODWnd  *pPODWnd;
  CPODLayout  cLayout;
  CPODLayoutExpression  *pExpression;

  if ((pPODWnd = (CPODWnd *) pParentWnd))
  { for (szTitle = (pPODWnd -> GetLayout(cLayout)) ? ((!cLayout.GetTitle().IsEmpty()) ? cLayout.GetTitle():cLayout.GetName()):STRING(IDS_WINDOW_UNKNOWNTITLE); HIWORD(pPODWnd -> GetType()) == POD_TYPE_NORMAL; )
    { if ((pExpression = (cLayout.GetSize() == 1) ? cLayout.GetAt((INT) (cLayout.GetSize()-1)):(CPODLayoutExpression *) NULL) &&  pExpression -> IsParameter())
      { szType.Format(STRING(IDS_PODRETRIEVEDIALOG_TYPENORMAL),(LPCTSTR) pExpression -> GetParameter());
        break;
      }
      szType = STRING(IDS_PODRETRIEVEDIALOG_TYPENORMAL);
      szType = szType.Left(((nPos=szType.Find(SPACE)) >= 0) ? nPos:szType.GetLength());
      break;
    }
    for ( ; HIWORD(pPODWnd -> GetType()) == POD_TYPE_TEMPORARY; )
    { if ((pExpression = (cLayout.GetSize() == 1) ? cLayout.GetAt((INT) (cLayout.GetSize()-1)):(CPODLayoutExpression *) NULL) &&  pExpression -> IsParameter())
      { szType.Format(STRING(IDS_PODRETRIEVEDIALOG_TYPETEMPORARY),(LPCTSTR) pExpression -> GetParameter());
        break;
      }
      szType = STRING(IDS_PODRETRIEVEDIALOG_TYPETEMPORARY);
      szType = szType.Left(((nPos=szType.Find(SPACE)) >= 0) ? nPos:szType.GetLength());
      break;
    }
    return Create(pParentWnd,szTitle,szType);
  }
  return -1;
}
INT CPODRetrieveDialog::Create(CWnd *pParentWnd,LPCTSTR pszTitle,LPCTSTR pszType)
{
  m_szType = pszType;
  m_szTitle = pszTitle;
  return CDisplayDialog::Create(pParentWnd,CPODRetrieveDialog::IDD);
}

BOOL CPODRetrieveDialog::GetMode(UINT &nMode) CONST
{
  nMode = (!IsDlgButtonChecked(IDC_POD_RETRIEVE_REALTIME)) ? ((IsDlgButtonChecked(IDC_POD_RETRIEVE_HISTORY_EXACTTIME)) ? POD_RETRIEVE_EXACTTIME:0):0;
  nMode |= (!IsDlgButtonChecked(IDC_POD_RETRIEVE_REALTIME)) ? ((IsDlgButtonChecked(IDC_POD_RETRIEVE_HISTORY_STOPBYTIME) ||  IsDlgButtonChecked(IDC_POD_RETRIEVE_HISTORY_STOPBYEND) ||  IsDlgButtonChecked(IDC_POD_RETRIEVE_HISTORY_STOPBYREALTIME)) ? ((!IsDlgButtonChecked(IDC_POD_RETRIEVE_HISTORY_STOPBYTIME)) ? ((!IsDlgButtonChecked(IDC_POD_RETRIEVE_HISTORY_STOPBYEND)) ? POD_RETRIEVE_STOPBYREALTIME:POD_RETRIEVE_STOPBYEND):POD_RETRIEVE_STOPBYTIME):0):0;
  nMode |= (!IsDlgButtonChecked(IDC_POD_RETRIEVE_REALTIME)) ? ((IsDlgButtonChecked(IDC_POD_RETRIEVE_HISTORY_AUTOMATIC)) ? POD_RETRIEVE_AUTOFORWARD:((IsDlgButtonChecked(IDC_POD_RETRIEVE_HISTORY_PSEUDOREALTIME)) ? POD_RETRIEVE_PSEUDOREALTIME:POD_RETRIEVE_MANUALFORWARD)):0;
  return TRUE;
}

BOOL CPODRetrieveDialog::GetSpeed(UINT &nSpeed) CONST
{
  nSpeed = (!IsDlgButtonChecked(IDC_POD_RETRIEVE_HISTORY_AUTOMATIC)) ? (UINT) ((GetDlgItem(IDC_POD_RETRIEVE_HISTORY_SPEED) -> SendMessage(TBM_GETRANGEMIN)+GetDlgItem(IDC_POD_RETRIEVE_HISTORY_SPEED) -> SendMessage(TBM_GETRANGEMAX))/2):(UINT) GetDlgItem(IDC_POD_RETRIEVE_HISTORY_SPEED) -> SendMessage(TBM_GETPOS);
  return((IsDlgButtonChecked(IDC_POD_RETRIEVE_HISTORY_AUTOMATIC)) ? TRUE:FALSE);
}

BOOL CPODRetrieveDialog::GetInterval(CTimeSpan &tInterval) CONST
{
  tInterval = (IsDlgButtonChecked(IDC_POD_RETRIEVE_HISTORY_INTERVAL)) ? (SECONDSPERMINUTE*Spinbox_GetPos(GetDlgItem(IDC_POD_RETRIEVE_HISTORY_INTERVALTIME))):0;
  return((IsDlgButtonChecked(IDC_POD_RETRIEVE_HISTORY_INTERVAL)) ? TRUE:FALSE);
}

BOOL CPODRetrieveDialog::GetStartTime(CTimeKey &tTimeKey) CONST
{
  CTimeKey  tTime;

  for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_POD_RETRIEVE_HISTORY_STARTTIME)),tTimeKey = 0; !IsDlgButtonChecked(IDC_POD_RETRIEVE_REALTIME) &&  tTime > 0; )
  { tTimeKey = tTime;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODRetrieveDialog::GetStopTime(CTimeKey &tTimeKey) CONST
{
  CTimeKey  tTime;

  for (tTime = Timespinbox_GetTime(GetDlgItem(IDC_POD_RETRIEVE_HISTORY_STOPTIME)),tTimeKey = 0; IsDlgButtonChecked(IDC_POD_RETRIEVE_HISTORY_STOPBYTIME) &&  tTime > 0; )
  { tTimeKey = tTime;
    return TRUE;
  }
  return FALSE;
}

CPODOpenDialog *CPODRetrieveDialog::GetParentDialog() CONST
{
  return((GetParent() != (CWnd *) GetParentDisplay()) ? (CPODOpenDialog *) GetParent():(CPODOpenDialog *) NULL);
}

CPODWnd *CPODRetrieveDialog::GetParentDisplay() CONST
{
  return((CPODWnd *) CDisplayDialog::GetParentDisplay());
}

BOOL CPODRetrieveDialog::SetRetrieveInfo()
{
  UINT  nMode;
  UINT  nSpeed;
  CTimeKey  tStartTime;
  CTimeKey  tStopTime;
  CTimeSpan  tInterval;

  if (GetRetrieveInfo(nMode,nSpeed,tInterval,tStartTime,tStopTime))
  { Spinbox_SetPos(GetDlgItem(IDC_POD_RETRIEVE_HISTORY_INTERVALTIME),tInterval.GetTotalSeconds()/SECONDSPERMINUTE);
    Timespinbox_SetTime(GetDlgItem(IDC_POD_RETRIEVE_HISTORY_STARTTIME),(tStartTime > 0  ||  GetTMService() -> GetRecentTMHistoryTimeKey(tStartTime)) ? tStartTime:CTime::GetCurrentTime().GetTime());
    Timespinbox_SetTime(GetDlgItem(IDC_POD_RETRIEVE_HISTORY_STOPTIME),(tStopTime.GetTime() > 0) ? tStopTime:CTime::GetCurrentTime().GetTime());
    Timespinbox_SetRange(GetDlgItem(IDC_POD_RETRIEVE_HISTORY_STOPTIME),Timespinbox_GetTime(GetDlgItem(IDC_POD_RETRIEVE_HISTORY_STARTTIME)),MAX_TIMEKEY);
    SendDlgItemMessage(IDC_POD_RETRIEVE_HISTORY_SPEED,TBM_SETPOS,TRUE,(!IsDlgButtonChecked(IDC_POD_RETRIEVE_REALTIME)) ? ((nMode) ? (((nMode & POD_RETRIEVE_AUTOFORWARD) || (nMode & POD_RETRIEVE_AUTOBACKWARD)) ? nSpeed:0):((SendDlgItemMessage(IDC_POD_RETRIEVE_HISTORY_SPEED,TBM_GETRANGEMIN)+SendDlgItemMessage(IDC_POD_RETRIEVE_HISTORY_SPEED,TBM_GETRANGEMAX))/2)):0);
    CheckDlgButton(IDC_POD_RETRIEVE_HISTORY_EXACTTIME,(!IsDlgButtonChecked(IDC_POD_RETRIEVE_REALTIME) && (nMode & POD_RETRIEVE_EXACTTIME)) ? TRUE:FALSE);
    CheckDlgButton(IDC_POD_RETRIEVE_HISTORY_STOPBYTIME,(!IsDlgButtonChecked(IDC_POD_RETRIEVE_REALTIME) && (nMode & POD_RETRIEVE_STOPBYTIME) && (nMode & (POD_RETRIEVE_MANUALFORWARD | POD_RETRIEVE_MANUALBACKWARD)) == 0) ? TRUE:FALSE);
    CheckDlgButton(IDC_POD_RETRIEVE_HISTORY_STOPBYEND,(!IsDlgButtonChecked(IDC_POD_RETRIEVE_REALTIME) && (nMode & POD_RETRIEVE_STOPBYEND) && (nMode & (POD_RETRIEVE_MANUALFORWARD | POD_RETRIEVE_MANUALBACKWARD)) == 0) ? TRUE:FALSE);
    CheckDlgButton(IDC_POD_RETRIEVE_HISTORY_STOPBYREALTIME,(!IsDlgButtonChecked(IDC_POD_RETRIEVE_REALTIME) && (!nMode  || (nMode & POD_RETRIEVE_STOPBYREALTIME))) ? TRUE:FALSE);
    CheckDlgButton(IDC_POD_RETRIEVE_HISTORY_AUTOMATIC,(!IsDlgButtonChecked(IDC_POD_RETRIEVE_REALTIME) && (!nMode  || (nMode & POD_RETRIEVE_AUTOFORWARD) || (nMode & POD_RETRIEVE_AUTOBACKWARD))) ? TRUE:FALSE);
    CheckDlgButton(IDC_POD_RETRIEVE_HISTORY_MANUAL,(!IsDlgButtonChecked(IDC_POD_RETRIEVE_REALTIME) && ((nMode & POD_RETRIEVE_MANUALFORWARD) || (nMode & POD_RETRIEVE_MANUALBACKWARD))) ? TRUE:FALSE);
    CheckDlgButton(IDC_POD_RETRIEVE_HISTORY_PSEUDOREALTIME,(!IsDlgButtonChecked(IDC_POD_RETRIEVE_REALTIME) && (nMode & POD_RETRIEVE_PSEUDOREALTIME)) ? TRUE:FALSE);
    CheckDlgButton(IDC_POD_RETRIEVE_HISTORY_INTERVAL,(!IsDlgButtonChecked(IDC_POD_RETRIEVE_REALTIME) && (nMode & POD_RETRIEVE_PSEUDOREALTIME) == 0  &&  tInterval.GetTotalSeconds() > 0) ? TRUE:FALSE);
    GetDlgItem(IDC_POD_RETRIEVE_HISTORY) -> EnableWindow(!IsDlgButtonChecked(IDC_POD_RETRIEVE_REALTIME));
    GetDlgItem(IDC_POD_RETRIEVE_HISTORY_START_STATIC) -> EnableWindow(!IsDlgButtonChecked(IDC_POD_RETRIEVE_REALTIME));
    GetDlgItem(IDC_POD_RETRIEVE_HISTORY_STARTTIME) -> EnableWindow(!IsDlgButtonChecked(IDC_POD_RETRIEVE_REALTIME));
    GetDlgItem(IDC_POD_RETRIEVE_HISTORY_EXACTTIME) -> EnableWindow(!IsDlgButtonChecked(IDC_POD_RETRIEVE_REALTIME));
    GetDlgItem(IDC_POD_RETRIEVE_HISTORY_STOP_STATIC) -> EnableWindow(!IsDlgButtonChecked(IDC_POD_RETRIEVE_REALTIME));
    GetDlgItem(IDC_POD_RETRIEVE_HISTORY_STOPBYTIME) -> EnableWindow(!IsDlgButtonChecked(IDC_POD_RETRIEVE_REALTIME) &&  !IsDlgButtonChecked(IDC_POD_RETRIEVE_HISTORY_MANUAL));
    GetDlgItem(IDC_POD_RETRIEVE_HISTORY_STOPTIME) -> EnableWindow(!IsDlgButtonChecked(IDC_POD_RETRIEVE_REALTIME) &&  IsDlgButtonChecked(IDC_POD_RETRIEVE_HISTORY_STOPBYTIME));
    GetDlgItem(IDC_POD_RETRIEVE_HISTORY_STOPBYEND) -> EnableWindow(!IsDlgButtonChecked(IDC_POD_RETRIEVE_REALTIME) &&  !IsDlgButtonChecked(IDC_POD_RETRIEVE_HISTORY_MANUAL));
    GetDlgItem(IDC_POD_RETRIEVE_HISTORY_STOPBYREALTIME) -> EnableWindow(!IsDlgButtonChecked(IDC_POD_RETRIEVE_REALTIME));
    GetDlgItem(IDC_POD_RETRIEVE_HISTORY_PLAYBACKMODE) -> EnableWindow(!IsDlgButtonChecked(IDC_POD_RETRIEVE_REALTIME));
    GetDlgItem(IDC_POD_RETRIEVE_HISTORY_AUTOMATIC) -> EnableWindow(!IsDlgButtonChecked(IDC_POD_RETRIEVE_REALTIME));
    GetDlgItem(IDC_POD_RETRIEVE_HISTORY_PSEUDOREALTIME) -> EnableWindow(!IsDlgButtonChecked(IDC_POD_RETRIEVE_REALTIME));
    GetDlgItem(IDC_POD_RETRIEVE_HISTORY_MANUAL) -> EnableWindow(!IsDlgButtonChecked(IDC_POD_RETRIEVE_REALTIME));
    GetDlgItem(IDC_POD_RETRIEVE_HISTORY_SPEED_STATIC) -> EnableWindow(IsDlgButtonChecked(IDC_POD_RETRIEVE_HISTORY_AUTOMATIC));
    GetDlgItem(IDC_POD_RETRIEVE_HISTORY_SPEED) -> EnableWindow(IsDlgButtonChecked(IDC_POD_RETRIEVE_HISTORY_AUTOMATIC));
    GetDlgItem(IDC_POD_RETRIEVE_HISTORY_SLOW) -> EnableWindow(IsDlgButtonChecked(IDC_POD_RETRIEVE_HISTORY_AUTOMATIC));
    GetDlgItem(IDC_POD_RETRIEVE_HISTORY_FAST) -> EnableWindow(IsDlgButtonChecked(IDC_POD_RETRIEVE_HISTORY_AUTOMATIC));
    GetDlgItem(IDC_POD_RETRIEVE_HISTORY_INTERVAL) -> EnableWindow(!IsDlgButtonChecked(IDC_POD_RETRIEVE_REALTIME) &&  !IsDlgButtonChecked(IDC_POD_RETRIEVE_HISTORY_PSEUDOREALTIME));
    GetDlgItem(IDC_POD_RETRIEVE_HISTORY_INTERVALTIME_STATIC) -> EnableWindow(IsDlgButtonChecked(IDC_POD_RETRIEVE_HISTORY_INTERVAL));
    GetDlgItem(IDC_POD_RETRIEVE_HISTORY_INTERVALTIME) -> EnableWindow(IsDlgButtonChecked(IDC_POD_RETRIEVE_HISTORY_INTERVAL));
    return TRUE;
  }
  return FALSE;
}

BOOL CPODRetrieveDialog::GetRetrieveInfo(UINT &nMode,UINT &nSpeed,CTimeSpan &tInterval,CTimeKey &tStartTime,CTimeKey &tStopTime) CONST
{
  CPODWnd  *pPODWnd;
  CPODOpenDialog  *pDialog;

  if ((pDialog = GetParentDialog()))
  { for (pDialog -> GetRetrieveMode(nMode),nSpeed = 0,tInterval = 0,tStartTime = tStopTime = 0; nMode; )
    { pDialog -> GetRetrieveSpeed(nSpeed);
      pDialog -> GetRetrieveInterval(tInterval);
      pDialog -> GetRetrieveStartTime(tStartTime);
      pDialog -> GetRetrieveStopTime(tStopTime);
      break;
    }
    return TRUE;
  }
  if ((pPODWnd = GetParentDisplay()))
  { for (pPODWnd -> GetRetrieveMode(nMode),nSpeed = 0,tInterval = 0,tStartTime = tStopTime = 0; nMode; )
    { pPODWnd -> GetRetrieveSpeed(nSpeed);
      pPODWnd -> GetRetrieveInterval(tInterval);
      pPODWnd -> GetRetrieveStartTime(tStartTime);
      pPODWnd -> GetRetrieveStopTime(tStopTime);
      break;
    }
    return TRUE;
  }
  return FALSE;
}

void CPODRetrieveDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPODRetrieveDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPODRetrieveDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CPODRetrieveDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_POD_RETRIEVE_REALTIME,OnRetrieveRealtime)
	ON_BN_CLICKED(IDC_POD_RETRIEVE_HISTORY_STOPBYTIME,OnRetrieveByTime)
	ON_BN_CLICKED(IDC_POD_RETRIEVE_HISTORY_STOPBYEND,OnRetrieveByEnd)
	ON_BN_CLICKED(IDC_POD_RETRIEVE_HISTORY_STOPBYREALTIME,OnRetrieveByRealtime)
	ON_BN_CLICKED(IDC_POD_RETRIEVE_HISTORY_AUTOMATIC,OnRetrieveAutomatic)
	ON_BN_CLICKED(IDC_POD_RETRIEVE_HISTORY_PSEUDOREALTIME,OnRetrievePseudoRealtime)
	ON_BN_CLICKED(IDC_POD_RETRIEVE_HISTORY_MANUAL,OnRetrieveManual)
	ON_BN_CLICKED(IDC_POD_RETRIEVE_HISTORY_INTERVAL,OnRetrieveInterval)
	ON_BN_CLICKED(IDC_POD_RETRIEVE_HELP,OnHelp)
	ON_CONTROL(TSBXN_CHANGE,IDC_POD_RETRIEVE_HISTORY_STARTTIME,OnSpinchangeRetrieveStartTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPODRetrieveDialog message handlers

BOOL CPODRetrieveDialog::OnInitDialog() 
{
  CHourglassCursor  cCursor;

  for (CDisplayDialog::OnInitDialog(),SendDlgItemMessage(IDC_POD_RETRIEVE_HISTORY_SPEED,TBM_SETRANGE,TRUE,MAKELPARAM(0,10)),Spinbox_SetRange(GetDlgItem(IDC_POD_RETRIEVE_HISTORY_INTERVALTIME),PODRETRIEVEDIALOG_MINIMUMINTERVAL,PODRETRIEVEDIALOG_MAXIMUMINTERVAL),GetDlgItem(IDC_POD_RETRIEVE_TITLE) -> SetWindowText(m_szTitle),GetDlgItem(IDC_POD_RETRIEVE_TYPE) -> SetWindowText(m_szType); SetRetrieveInfo(); )
  { GetDlgItem(IDC_POD_RETRIEVE_DETAILS) -> EnableWindow();
    GetDlgItem(IDC_POD_RETRIEVE_TITLE_STATIC) -> EnableWindow();
    GetDlgItem(IDC_POD_RETRIEVE_TITLE) -> EnableWindow();
    GetDlgItem(IDC_POD_RETRIEVE_TYPE_STATIC) -> EnableWindow();
    GetDlgItem(IDC_POD_RETRIEVE_TYPE) -> EnableWindow();
    GetDlgItem(IDC_POD_RETRIEVE_REALTIME) -> EnableWindow((GetParentDisplay() -> GetMode() == DISPLAY_MODE_HISTORY) ? TRUE:FALSE);
    GetDlgItem(IDC_POD_RETRIEVE_HISTORY_STARTTIME) -> SetFocus();
    GetDlgItem(IDOK) -> EnableWindow();
    return FALSE;
  }
  return TRUE;
}

void CPODRetrieveDialog::OnRetrieveRealtime()
{
  SetRetrieveInfo();
}

void CPODRetrieveDialog::OnRetrieveByTime()
{
  CheckDlgButton(IDC_POD_RETRIEVE_HISTORY_STOPBYTIME,TRUE);
  CheckDlgButton(IDC_POD_RETRIEVE_HISTORY_STOPBYEND,FALSE);
  CheckDlgButton(IDC_POD_RETRIEVE_HISTORY_STOPBYREALTIME,FALSE);
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_STOPTIME) -> EnableWindow();
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_STOPTIME) -> SetFocus();
}

void CPODRetrieveDialog::OnRetrieveByEnd()
{
  CheckDlgButton(IDC_POD_RETRIEVE_HISTORY_STOPBYTIME,FALSE);
  CheckDlgButton(IDC_POD_RETRIEVE_HISTORY_STOPBYEND,TRUE);
  CheckDlgButton(IDC_POD_RETRIEVE_HISTORY_STOPBYREALTIME,FALSE);
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_STOPTIME) -> EnableWindow(FALSE);
}

void CPODRetrieveDialog::OnRetrieveByRealtime()
{
  CheckDlgButton(IDC_POD_RETRIEVE_HISTORY_STOPBYTIME,FALSE);
  CheckDlgButton(IDC_POD_RETRIEVE_HISTORY_STOPBYEND,FALSE);
  CheckDlgButton(IDC_POD_RETRIEVE_HISTORY_STOPBYREALTIME,(IsDlgButtonChecked(IDC_POD_RETRIEVE_HISTORY_MANUAL)) ? !IsDlgButtonChecked(IDC_POD_RETRIEVE_HISTORY_STOPBYREALTIME):TRUE);
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_STOPTIME) -> EnableWindow(FALSE);
}

void CPODRetrieveDialog::OnRetrieveAutomatic()
{
  SendDlgItemMessage(IDC_POD_RETRIEVE_HISTORY_SPEED,TBM_SETPOS,TRUE,(SendDlgItemMessage(IDC_POD_RETRIEVE_HISTORY_SPEED,TBM_GETRANGEMIN)+SendDlgItemMessage(IDC_POD_RETRIEVE_HISTORY_SPEED,TBM_GETRANGEMAX))/2);
  CheckDlgButton(IDC_POD_RETRIEVE_HISTORY_STOPBYTIME,FALSE);
  CheckDlgButton(IDC_POD_RETRIEVE_HISTORY_STOPBYEND,FALSE);
  CheckDlgButton(IDC_POD_RETRIEVE_HISTORY_STOPBYREALTIME,TRUE);
  CheckDlgButton(IDC_POD_RETRIEVE_HISTORY_AUTOMATIC,TRUE);
  CheckDlgButton(IDC_POD_RETRIEVE_HISTORY_PSEUDOREALTIME,FALSE);
  CheckDlgButton(IDC_POD_RETRIEVE_HISTORY_MANUAL,FALSE);
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_STOP_STATIC) -> EnableWindow();
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_STOPBYTIME) -> EnableWindow();
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_STOPTIME) -> EnableWindow(IsDlgButtonChecked(IDC_POD_RETRIEVE_HISTORY_STOPBYTIME));
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_STOPBYEND) -> EnableWindow();
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_STOPBYREALTIME) -> EnableWindow();
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_SPEED_STATIC) -> EnableWindow();
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_SPEED) -> EnableWindow();
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_SLOW) -> EnableWindow();
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_FAST) -> EnableWindow();
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_INTERVAL) -> EnableWindow();
}

void CPODRetrieveDialog::OnRetrievePseudoRealtime()
{
  SendDlgItemMessage(IDC_POD_RETRIEVE_HISTORY_SPEED,TBM_SETPOS,TRUE,0);
  CheckDlgButton(IDC_POD_RETRIEVE_HISTORY_STOPBYTIME,FALSE);
  CheckDlgButton(IDC_POD_RETRIEVE_HISTORY_STOPBYEND,FALSE);
  CheckDlgButton(IDC_POD_RETRIEVE_HISTORY_STOPBYREALTIME,TRUE);
  CheckDlgButton(IDC_POD_RETRIEVE_HISTORY_AUTOMATIC,FALSE);
  CheckDlgButton(IDC_POD_RETRIEVE_HISTORY_PSEUDOREALTIME,TRUE);
  CheckDlgButton(IDC_POD_RETRIEVE_HISTORY_MANUAL,FALSE);
  CheckDlgButton(IDC_POD_RETRIEVE_HISTORY_INTERVAL,FALSE);
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_STOP_STATIC) -> EnableWindow();
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_STOPBYTIME) -> EnableWindow();
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_STOPTIME) -> EnableWindow(IsDlgButtonChecked(IDC_POD_RETRIEVE_HISTORY_STOPBYTIME));
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_STOPBYEND) -> EnableWindow();
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_STOPBYREALTIME) -> EnableWindow();
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_SPEED_STATIC) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_SPEED) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_SLOW) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_FAST) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_INTERVAL) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_INTERVALTIME_STATIC) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_INTERVALTIME) -> EnableWindow(FALSE);
}

void CPODRetrieveDialog::OnRetrieveManual()
{
  SendDlgItemMessage(IDC_POD_RETRIEVE_HISTORY_SPEED,TBM_SETPOS,TRUE,0);
  CheckDlgButton(IDC_POD_RETRIEVE_HISTORY_STOPBYTIME,FALSE);
  CheckDlgButton(IDC_POD_RETRIEVE_HISTORY_STOPBYEND,FALSE);
  CheckDlgButton(IDC_POD_RETRIEVE_HISTORY_STOPBYREALTIME,FALSE);
  CheckDlgButton(IDC_POD_RETRIEVE_HISTORY_AUTOMATIC,FALSE);
  CheckDlgButton(IDC_POD_RETRIEVE_HISTORY_PSEUDOREALTIME,FALSE);
  CheckDlgButton(IDC_POD_RETRIEVE_HISTORY_MANUAL,TRUE);
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_STOP_STATIC) -> EnableWindow();
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_STOPBYTIME) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_STOPTIME) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_STOPBYEND) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_STOPBYREALTIME) -> EnableWindow();
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_SPEED_STATIC) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_SPEED) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_SLOW) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_FAST) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_INTERVAL) -> EnableWindow();
}

void CPODRetrieveDialog::OnRetrieveInterval()
{
  Spinbox_SetPos(GetDlgItem(IDC_POD_RETRIEVE_HISTORY_INTERVALTIME),PODRETRIEVEDIALOG_DEFAULTINTERVAL);
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_INTERVALTIME_STATIC) -> EnableWindow(IsDlgButtonChecked(IDC_POD_RETRIEVE_HISTORY_INTERVAL));
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_INTERVALTIME) -> EnableWindow(IsDlgButtonChecked(IDC_POD_RETRIEVE_HISTORY_INTERVAL));
  GetDlgItem(IDC_POD_RETRIEVE_HISTORY_INTERVALTIME) -> SetFocus();
}

void CPODRetrieveDialog::OnSpinchangeRetrieveStartTime()
{
  Timespinbox_SetRange(GetDlgItem(IDC_POD_RETRIEVE_HISTORY_STOPTIME),Timespinbox_GetTime(GetDlgItem(IDC_POD_RETRIEVE_HISTORY_STARTTIME)),MAX_TIMEKEY);
}

void CPODRetrieveDialog::OnOK()
{
  CPODWnd  *pPODWnd;
  CTimeKey  tTimeKey;
  CPODLayout  cLayout;
  CDisplayWnd  *pDisplayWnd;
  CPODOpenDialog  *pDialog;
  CHourglassCursor  cCursor;

  if ((pDisplayWnd = GetParentDisplay() -> GetLink()))
  { if (GetParentDisplay() -> Lock())
    { GetParentDisplay() -> SetLink();
      GetParentDisplay() -> SetLinkByName();
      GetParentDisplay() -> Unlock();
    }
    if (pDisplayWnd -> Lock())
    { pDisplayWnd -> RemoveLink(GetParentDisplay());
      pDisplayWnd -> Unlock();
    }
  }
  for ( ; !GetParentDialog(); )
  { if (IsDlgButtonChecked(IDC_POD_RETRIEVE_REALTIME))
    { if ((pPODWnd = (GetParentDisplay() -> GetLayout(cLayout)) ? GetParentDisplay() -> Find(GetParentDisplay() -> GetType(),DISPLAY_MODE_REALTIME,cLayout.GetName()):(CPODWnd *) NULL))
      { for (GetDisplayArea() -> ActivateDisplay(pPODWnd); pPODWnd != GetParentDisplay(); )
        { GetParentDisplay() -> PostMessage(WM_CLOSE);
          break;
        }
        EndDialog(IDOK);
        return;
      }
    }
    GetParentDisplay() -> OnCloseRetrieveDialog(IDOK);
    break;
  }
  for ( ; (pDialog = GetParentDialog()); )
  { pDialog -> OnCloseRetrieveDialog(IDOK);
    break;
  }
  for ( ; GetStartTime(tTimeKey); )
  { GetTMService() -> SetRecentTMHistoryTimeKey(tTimeKey);
    break;
  }
  CDisplayDialog::OnOK();
}

void CPODRetrieveDialog::OnCancel()
{
  CHourglassCursor  cCursor;

  if (!GetParentDialog()) GetParentDisplay() -> OnCloseRetrieveDialog(IDCANCEL);
  else  GetParentDialog() -> OnCloseRetrieveDialog(IDCANCEL);
  CDisplayDialog::OnCancel();
}

BOOL CPODRetrieveDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
  CHourglassCursor  cCursor;

  ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_PODRETRIEVEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE:SYSTEM_NOERROR);
  return TRUE;
}

void CPODRetrieveDialog::OnHelp()
{
  CHourglassCursor  cCursor;

  ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_PODRETRIEVEDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE:SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CPODImportDialog dialog

IMPLEMENT_DYNCREATE(CPODImportDialog,CLocaleDialog)

CPODImportDialog::CPODImportDialog(CWnd *pParentWnd) : CLocaleDialog(CPODImportDialog::IDD,pParentWnd)
{
	//{{AFX_DATA_INIT(CPODImportDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CPODImportDialog::Initialize()
{
  EnumTemporaryPODs(m_pDisplays[0]);
  return TRUE;
}

VOID CPODImportDialog::EnumDisplays()
{
  INT  nLayout;
  INT  nLayouts;
  DWORD  cbData;
  CFileEx  cFile;
  CString  szMessage;
  CString  szFileName;
  CByteArray  nFileData;
  CPODLayout  *pPODLayout;

  SendDlgItemMessage(IDC_POD_IMPORT_DIRECTORY,CB_RESETCONTENT);
  GetDlgItem(IDC_POD_IMPORT_FILENAME) -> GetWindowText(szFileName);
  if (cFile.Open(szFileName,CFile::modeRead | CFile::shareExclusive))
  { nFileData.SetSize((cbData=(DWORD) cFile.GetLength()*sizeof(BYTE)));
    if (ReadFile(cFile.m_hFile,nFileData.GetData(),(DWORD) nFileData.GetSize(),&cbData,(LPOVERLAPPED) NULL))
    { for (nLayout = 0,nLayouts = (m_pDisplays[1].Unmap(nFileData)) ? (INT) m_pDisplays[1].GetSize():0; nLayout < nLayouts; nLayout++)
      { if ((pPODLayout = m_pDisplays[1].GetAt(nLayout))) SendDlgItemMessage(IDC_POD_IMPORT_DIRECTORY,CB_INSERTSTRING,nLayout,(LPARAM) (LPCTSTR) pPODLayout -> GetTitle());
        continue;
      }
    }
    else
    { szMessage = STRING(IDS_POD_IMPORT_FILE_FAILURE);
      ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_ERROR,szMessage);
    }
    cFile.Close();
  }
  else
  { szMessage = STRING(IDS_POD_IMPORT_FILE_FAILURE);
    ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_ERROR,szMessage);
  }
  if (SendDlgItemMessage(IDC_POD_IMPORT_DIRECTORY,CB_GETCOUNT) > 0)
  { SendDlgItemMessage(IDC_POD_IMPORT_DIRECTORY,CB_SETCURSEL);
    GetDlgItem(IDC_POD_IMPORT_DIRECTORY_STATIC) -> EnableWindow();
    GetDlgItem(IDC_POD_IMPORT_DIRECTORY) -> EnableWindow();
    return;
  }
  GetDlgItem(IDC_POD_IMPORT_DIRECTORY_STATIC) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_IMPORT_DIRECTORY) -> EnableWindow(FALSE);
}

BOOL CPODImportDialog::Check(BOOL bModified) CONST
{
  return((m_pDisplays[2].GetSize() > 0) ? TRUE:FALSE);
}

void CPODImportDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPODImportDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CPODImportDialog::PostNcDestroy()
{
  m_pDisplays[0].RemoveAll();
  m_pDisplays[1].RemoveAll();
  m_pDisplays[2].RemoveAll();
  CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CPODImportDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CPODImportDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_POD_IMPORT_BROWSE,OnBrowse)
	ON_BN_CLICKED(IDC_POD_IMPORT_INSPECT,OnInspect)
	ON_BN_CLICKED(IDC_POD_IMPORT_ADD,OnAdd)
	ON_BN_CLICKED(IDC_POD_IMPORT_ADDALL,OnAddAll)
	ON_BN_CLICKED(IDC_POD_IMPORT_REMOVE,OnRemove)
	ON_BN_CLICKED(IDC_POD_IMPORT_REMOVEALL,OnRemoveAll)
	ON_BN_CLICKED(IDC_POD_IMPORT_HELP,OnHelp)
	ON_EN_CHANGE(IDC_POD_IMPORT_FILENAME,OnEditchangeFileName)
	ON_CBN_SELCHANGE(IDC_POD_IMPORT_DIRECTORY,OnSelchangeSource)
	ON_LBN_SELCHANGE(IDC_POD_IMPORT_LIST,OnSelchangeDestination)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPODImportDialog message handlers

BOOL CPODImportDialog::OnInitDialog()
{
  CHourglassCursor  cCursor;

  CLocaleDialog::OnInitDialog();
  GetDlgItem(IDC_POD_IMPORT_DETAILS) -> EnableWindow();
  GetDlgItem(IDC_POD_IMPORT_FILENAME_STATIC) -> EnableWindow();
  GetDlgItem(IDC_POD_IMPORT_FILENAME) -> EnableWindow();
  GetDlgItem(IDC_POD_IMPORT_BROWSE) -> EnableWindow();
  GetDlgItem(IDC_POD_IMPORT_DIRECTORY_STATIC) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_IMPORT_DIRECTORY) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_IMPORT_ADD) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_IMPORT_ADDALL) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_IMPORT_ATTENTION) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_IMPORT_ATTENTION_TEXT) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_IMPORT_LIST_STATIC) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_IMPORT_LIST) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_IMPORT_REMOVE) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_IMPORT_REMOVEALL) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_IMPORT_FILENAME) -> SetFocus();
  return FALSE;
}

void CPODImportDialog::OnBrowse()
{
  CString  szFileName;
  CFileBrowseDialog  cFileBrowseDialog(this,IDC_POD_IMPORT_FILENAME,STRING(IDS_FILEBROWSEDIALOG_DATABASEFILEEXTENSION),STRING(IDS_FILEBROWSEDIALOG_DATABASEFILEFILTER));

  if (cFileBrowseDialog.DoModal() == IDOK)
  { GetDlgItem(IDC_POD_IMPORT_FILENAME) -> SetWindowText((szFileName=cFileBrowseDialog.GetPathName()));
    GetDlgItem(IDC_POD_IMPORT_BROWSE) -> ShowWindow((szFileName.IsEmpty()) ? SW_SHOW:SW_HIDE);
    GetDlgItem(IDC_POD_IMPORT_INSPECT) -> ShowWindow((!szFileName.IsEmpty()) ? SW_SHOW:SW_HIDE);
    GetDlgItem(IDC_POD_IMPORT_BROWSE) -> EnableWindow((szFileName.IsEmpty()) ? TRUE:FALSE);
    GetDlgItem(IDC_POD_IMPORT_INSPECT) -> EnableWindow((!szFileName.IsEmpty()) ? TRUE:FALSE);
  }
  SendDlgItemMessage(IDC_POD_IMPORT_FILENAME,EM_SETSEL,0,(LPARAM) -1);
  GetDlgItem(IDC_POD_IMPORT_FILENAME) -> SetFocus();
}

void CPODImportDialog::OnInspect()
{
  INT  nLayout;
  INT  nLayouts;
  CString  szLayout;
  CHourglassCursor  cCursor;

  EnumDisplays();
  for (nLayout = 0,nLayouts = (INT) SendDlgItemMessage(IDC_POD_IMPORT_DIRECTORY,CB_GETCOUNT); nLayout < nLayouts; nLayout++)
  { if (SendDlgItemMessage(IDC_POD_IMPORT_LIST,LB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) (szLayout = Combobox_GetText(GetDlgItem(IDC_POD_IMPORT_DIRECTORY),nLayout))) < 0) break;
    continue;
  }
  GetDlgItem(IDC_POD_IMPORT_DIRECTORY) -> GetWindowText(szLayout);
  GetDlgItem(IDC_POD_IMPORT_ADD) -> EnableWindow((SendDlgItemMessage(IDC_POD_IMPORT_LIST,LB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) szLayout) < 0  &&  !szLayout.IsEmpty()) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_IMPORT_ADDALL) -> EnableWindow((nLayout < nLayouts) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_IMPORT_DIRECTORY) -> SetFocus();
}

void CPODImportDialog::OnAdd()
{
  INT  nLayout;
  INT  nLayouts;
  CString  szLayout;
  CPODLayout  *pLayout[2];
  CHourglassCursor  cCursor;

  GetDlgItem(IDC_POD_IMPORT_DIRECTORY) -> GetWindowText(szLayout);
  if (SendDlgItemMessage(IDC_POD_IMPORT_LIST,LB_ADDSTRING,(WPARAM) NULL,(LPARAM) (LPCTSTR) szLayout) >= 0)
  { if ((pLayout[0] = m_pDisplays[1].GetAt(m_pDisplays[1].Find(szLayout))))
    { if ((pLayout[1] = new CPODLayout))
      { pLayout[1] -> Copy(pLayout[0]);
        if (m_pDisplays[2].Add(pLayout[1]) < 0) delete pLayout[1];
      }
    }
    for (nLayout = 0,nLayouts = (INT) SendDlgItemMessage(IDC_POD_IMPORT_LIST,LB_GETCOUNT); nLayout < nLayouts; nLayout++)
    { if (m_pDisplays[0].Find(Listbox_GetText(GetDlgItem(IDC_POD_IMPORT_LIST),nLayout)) >= 0) break;
      continue;
    }
    SendDlgItemMessage(IDC_POD_IMPORT_LIST,LB_SETCURSEL,(WPARAM) SendDlgItemMessage(IDC_POD_IMPORT_LIST,LB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) szLayout));
    GetDlgItem(IDC_POD_IMPORT_ATTENTION) -> ShowWindow((nLayout < nLayouts) ? SW_SHOW:SW_HIDE);
    GetDlgItem(IDC_POD_IMPORT_ATTENTION_TEXT) -> ShowWindow((nLayout < nLayouts) ? SW_SHOW:SW_HIDE);
    GetDlgItem(IDC_POD_IMPORT_ATTENTION) -> EnableWindow((nLayout < nLayouts) ? TRUE:FALSE);
    GetDlgItem(IDC_POD_IMPORT_ATTENTION_TEXT) -> EnableWindow((nLayout < nLayouts) ? TRUE:FALSE);
    for (nLayout = 0,nLayouts = (INT) SendDlgItemMessage(IDC_POD_IMPORT_DIRECTORY,CB_GETCOUNT); nLayout < nLayouts; nLayout++)
    { if (SendDlgItemMessage(IDC_POD_IMPORT_LIST,LB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) Combobox_GetText(GetDlgItem(IDC_POD_IMPORT_DIRECTORY),nLayout)) < 0) break;
      continue;
    }
    GetDlgItem(IDC_POD_IMPORT_ADD) -> EnableWindow(FALSE);
    GetDlgItem(IDC_POD_IMPORT_ADDALL) -> EnableWindow((nLayout < nLayouts) ? TRUE:FALSE);
    GetDlgItem(IDC_POD_IMPORT_LIST_STATIC) -> EnableWindow();
    GetDlgItem(IDC_POD_IMPORT_LIST) -> EnableWindow();
    GetDlgItem(IDC_POD_IMPORT_REMOVE) -> EnableWindow();
    GetDlgItem(IDC_POD_IMPORT_REMOVEALL) -> EnableWindow();
    GetDlgItem(IDC_POD_IMPORT_DIRECTORY) -> SetFocus();
  }
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODImportDialog::OnAddAll()
{
  INT  nLayout;
  INT  nLayouts;
  CString  szLayout;
  CPODLayout  *pLayout[2];
  CHourglassCursor  cCursor;

  for (nLayout = 0,nLayouts = (INT) SendDlgItemMessage(IDC_POD_IMPORT_DIRECTORY,CB_GETCOUNT); nLayout < nLayouts; nLayout++)
  { if (SendDlgItemMessage(IDC_POD_IMPORT_LIST,LB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) (szLayout = Combobox_GetText(GetDlgItem(IDC_POD_IMPORT_DIRECTORY),nLayout))) < 0)
    { SendDlgItemMessage(IDC_POD_IMPORT_LIST,LB_ADDSTRING,(WPARAM) NULL,(LPARAM) (LPCTSTR) szLayout);
      continue;
    }
  }
  for (nLayout = 0,nLayouts = (INT) m_pDisplays[1].GetSize(); nLayout < nLayouts; nLayout++)
  { if ((pLayout[0] = m_pDisplays[1].GetAt(nLayout)) &&  m_pDisplays[2].Find(pLayout[0] -> GetTitle()) < 0)
    { if ((pLayout[1] = new CPODLayout))
      { pLayout[1] -> Copy(pLayout[0]);
        if (m_pDisplays[2].Add(pLayout[1]) < 0)
        { delete pLayout[1];
          continue;
        }
      }
    }
  }
  for (nLayout = 0,nLayouts = (INT) SendDlgItemMessage(IDC_POD_IMPORT_LIST,LB_GETCOUNT); nLayout < nLayouts; nLayout++)
  { if (m_pDisplays[0].Find((szLayout = Listbox_GetText(GetDlgItem(IDC_POD_IMPORT_LIST),nLayout))) >= 0) break;
    continue;
  }
  GetDlgItem(IDC_POD_IMPORT_ATTENTION) -> ShowWindow((nLayout < nLayouts) ? SW_SHOW:SW_HIDE);
  GetDlgItem(IDC_POD_IMPORT_ATTENTION_TEXT) -> ShowWindow((nLayout < nLayouts) ? SW_SHOW:SW_HIDE);
  GetDlgItem(IDC_POD_IMPORT_ATTENTION) -> EnableWindow((nLayout < nLayouts) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_IMPORT_ATTENTION_TEXT) -> EnableWindow((nLayout < nLayouts) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_IMPORT_LIST_STATIC) -> EnableWindow((SendDlgItemMessage(IDC_POD_IMPORT_LIST,LB_GETCOUNT) > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_IMPORT_LIST) -> EnableWindow((SendDlgItemMessage(IDC_POD_IMPORT_LIST,LB_GETCOUNT) > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_IMPORT_ADD) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_IMPORT_ADDALL) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_IMPORT_REMOVE) -> EnableWindow((SendDlgItemMessage(IDC_POD_IMPORT_LIST,LB_GETCURSEL) >= 0) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_IMPORT_REMOVEALL) -> EnableWindow((SendDlgItemMessage(IDC_POD_IMPORT_LIST,LB_GETCOUNT) > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_IMPORT_DIRECTORY) -> SetFocus();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODImportDialog::OnRemove()
{
  INT  nIndex;
  INT  nLayout;
  INT  nLayouts;
  CString  szLayout;
  CHourglassCursor  cCursor;

  if ((nIndex = m_pDisplays[2].Find(Listbox_GetText(GetDlgItem(IDC_POD_IMPORT_LIST),(INT) SendDlgItemMessage(IDC_POD_IMPORT_LIST,LB_GETCURSEL)))) >= 0)
  { delete m_pDisplays[2].GetAt(nIndex);
    m_pDisplays[2].RemoveAt(nIndex);
  }
  if (SendDlgItemMessage(IDC_POD_IMPORT_LIST,LB_DELETESTRING,(WPARAM) SendDlgItemMessage(IDC_POD_IMPORT_LIST,LB_GETCURSEL)) > 0)
  { for (nLayout = 0,nLayouts = (INT) SendDlgItemMessage(IDC_POD_IMPORT_LIST,LB_GETCOUNT); nLayout < nLayouts; nLayout++)
    { if (m_pDisplays[0].Find((szLayout = Listbox_GetText(GetDlgItem(IDC_POD_IMPORT_LIST),nLayout))) >= 0) break;
      continue;
    }
    SendDlgItemMessage(IDC_POD_IMPORT_LIST,LB_SETCURSEL);
    GetDlgItem(IDC_POD_IMPORT_DIRECTORY) -> GetWindowText(szLayout);
    GetDlgItem(IDC_POD_IMPORT_ATTENTION) -> ShowWindow((nLayout < nLayouts) ? SW_SHOW:SW_HIDE);
    GetDlgItem(IDC_POD_IMPORT_ATTENTION_TEXT) -> ShowWindow((nLayout < nLayouts) ? SW_SHOW:SW_HIDE);
    GetDlgItem(IDC_POD_IMPORT_ATTENTION) -> EnableWindow((nLayout < nLayouts) ? TRUE:FALSE);
    GetDlgItem(IDC_POD_IMPORT_ATTENTION_TEXT) -> EnableWindow((nLayout < nLayouts) ? TRUE:FALSE);
    GetDlgItem(IDC_POD_IMPORT_ADD) -> EnableWindow((SendDlgItemMessage(IDC_POD_IMPORT_LIST,LB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) szLayout) < 0) ? TRUE:FALSE);
    GetDlgItem(IDC_POD_IMPORT_ADDALL) -> EnableWindow((SendDlgItemMessage(IDC_POD_IMPORT_DIRECTORY,CB_GETCOUNT) > 0) ? TRUE:FALSE);
  }
  else
  { GetDlgItem(IDC_POD_IMPORT_ATTENTION) -> ShowWindow(SW_HIDE);
    GetDlgItem(IDC_POD_IMPORT_ATTENTION_TEXT) -> ShowWindow(SW_HIDE);
    GetDlgItem(IDC_POD_IMPORT_ATTENTION) -> EnableWindow(FALSE);
    GetDlgItem(IDC_POD_IMPORT_ATTENTION_TEXT) -> EnableWindow(FALSE);
    GetDlgItem(IDC_POD_IMPORT_LIST_STATIC) -> EnableWindow(FALSE);
    GetDlgItem(IDC_POD_IMPORT_LIST) -> EnableWindow(FALSE);
    GetDlgItem(IDC_POD_IMPORT_ADD) -> EnableWindow((SendDlgItemMessage(IDC_POD_IMPORT_DIRECTORY,CB_GETCURSEL) >= 0) ? TRUE:FALSE);
    GetDlgItem(IDC_POD_IMPORT_ADDALL) -> EnableWindow((SendDlgItemMessage(IDC_POD_IMPORT_DIRECTORY,CB_GETCOUNT) > 0) ? TRUE:FALSE);
    GetDlgItem(IDC_POD_IMPORT_REMOVE) -> EnableWindow(FALSE);
    GetDlgItem(IDC_POD_IMPORT_REMOVEALL) -> EnableWindow(FALSE);
  }
  GetDlgItem(IDC_POD_IMPORT_DIRECTORY) -> SetFocus();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODImportDialog::OnRemoveAll()
{
  CHourglassCursor  cCursor;

  m_pDisplays[2].RemoveAll();
  SendDlgItemMessage(IDC_POD_IMPORT_LIST,LB_RESETCONTENT);
  GetDlgItem(IDC_POD_IMPORT_ATTENTION) -> ShowWindow(SW_HIDE);
  GetDlgItem(IDC_POD_IMPORT_ATTENTION_TEXT) -> ShowWindow(SW_HIDE);
  GetDlgItem(IDC_POD_IMPORT_ATTENTION) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_IMPORT_ATTENTION_TEXT) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_IMPORT_LIST_STATIC) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_IMPORT_LIST) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_IMPORT_ADD) -> EnableWindow((SendDlgItemMessage(IDC_POD_IMPORT_DIRECTORY,CB_GETCURSEL) >= 0) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_IMPORT_ADDALL) -> EnableWindow((SendDlgItemMessage(IDC_POD_IMPORT_DIRECTORY,CB_GETCOUNT) > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_IMPORT_REMOVE) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_IMPORT_REMOVEALL) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_IMPORT_DIRECTORY) -> SetFocus();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODImportDialog::OnEditchangeFileName()
{
  CString  szFileName;

  GetDlgItem(IDC_POD_IMPORT_FILENAME) -> GetWindowText(szFileName);
  GetDlgItem(IDC_POD_IMPORT_BROWSE) -> ShowWindow((szFileName.IsEmpty()) ? SW_SHOW:SW_HIDE);
  GetDlgItem(IDC_POD_IMPORT_INSPECT) -> ShowWindow((!szFileName.IsEmpty()) ? SW_SHOW:SW_HIDE);
  GetDlgItem(IDC_POD_IMPORT_BROWSE) -> EnableWindow((szFileName.IsEmpty()) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_IMPORT_INSPECT) -> EnableWindow((!szFileName.IsEmpty()) ? TRUE:FALSE);
}

void CPODImportDialog::OnSelchangeSource()
{
  CString  szLayout;

  GetDlgItem(IDC_POD_IMPORT_DIRECTORY) -> GetWindowText(szLayout);
  GetDlgItem(IDC_POD_IMPORT_ADD) -> EnableWindow((SendDlgItemMessage(IDC_POD_IMPORT_LIST,LB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) szLayout) < 0) ? TRUE:FALSE);
}

void CPODImportDialog::OnSelchangeDestination()
{
  GetDlgItem(IDC_POD_IMPORT_REMOVE) -> EnableWindow();
}

void CPODImportDialog::OnOK()
{
  INT  nLayout;
  INT  nLayouts;
  CString  szMessage;
  CPODLayout  cLayout;
  CHourglassCursor  cCursor;

  for (nLayout = 0,nLayouts = (INT) m_pDisplays[2].GetSize(); nLayout < nLayouts; nLayout++)
  { if (!cLayout.Copy(m_pDisplays[2].GetAt(nLayout)) ||  !AddTemporaryPOD(cLayout.GetTitle(),cLayout))
    { szMessage.Format(STRING(IDS_POD_IMPORT_FAILURE),(LPCTSTR) cLayout.GetTitle());
      ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_ERROR,szMessage);
    }
  }
  CLocaleDialog::OnOK();
}

BOOL CPODImportDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
  CHourglassCursor  cCursor;

  ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_PODIMPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE:SYSTEM_NOERROR);
  return TRUE;
}

void CPODImportDialog::OnHelp()
{
  CHourglassCursor  cCursor;

  ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_PODIMPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE:SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CPODExportDialog dialog

IMPLEMENT_DYNCREATE(CPODExportDialog,CLocaleDialog)

CPODExportDialog::CPODExportDialog(CWnd *pParentWnd) : CLocaleDialog(CPODExportDialog::IDD,pParentWnd)
{
	//{{AFX_DATA_INIT(CPODExportDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CPODExportDialog::Initialize()
{
  EnumTemporaryPODs(m_pDisplays[0]);
  return TRUE;
}

BOOL CPODExportDialog::EnumDisplays()
{
  INT  nLayout;
  INT  nLayouts;
  CPODLayout  *pPODLayout;

  for (nLayout = 0,nLayouts = (INT) m_pDisplays[0].GetSize(); nLayout < nLayouts; nLayout++)
  { if ((pPODLayout = m_pDisplays[0].GetAt(nLayout))) SendDlgItemMessage(IDC_POD_EXPORT_DIRECTORY,CB_ADDSTRING,(WPARAM) NULL,(LPARAM) (LPCTSTR) pPODLayout -> GetTitle());
    continue;
  }
  if (SendDlgItemMessage(IDC_POD_EXPORT_DIRECTORY,CB_GETCOUNT) > 0)
  { SendDlgItemMessage(IDC_POD_EXPORT_DIRECTORY,CB_SETCURSEL);
    GetDlgItem(IDC_POD_EXPORT_DIRECTORY_STATIC) -> EnableWindow();
    GetDlgItem(IDC_POD_EXPORT_DIRECTORY) -> EnableWindow();
    return TRUE;
  }
  GetDlgItem(IDC_POD_EXPORT_DIRECTORY_STATIC) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_EXPORT_DIRECTORY) -> EnableWindow(FALSE);
  return FALSE;
}

BOOL CPODExportDialog::Check(BOOL bModified) CONST
{
  return((GetDlgItem(IDC_POD_EXPORT_FILENAME) -> GetWindowTextLength() > 0  &&  m_pDisplays[1].GetSize() > 0) ? TRUE:FALSE);
}

void CPODExportDialog::DoDataExchange(CDataExchange *pDX)
{
	CLocaleDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPODExportDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CPODExportDialog::PostNcDestroy()
{
  m_pDisplays[0].RemoveAll();
  m_pDisplays[1].RemoveAll();
  CLocaleDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CPODExportDialog, CLocaleDialog)
	//{{AFX_MSG_MAP(CPODExportDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_POD_EXPORT_ADD,OnAdd)
	ON_BN_CLICKED(IDC_POD_EXPORT_ADDALL,OnAddAll)
	ON_BN_CLICKED(IDC_POD_EXPORT_REMOVE,OnRemove)
	ON_BN_CLICKED(IDC_POD_EXPORT_REMOVEALL,OnRemoveAll)
	ON_BN_CLICKED(IDC_POD_EXPORT_BROWSE,OnBrowse)
	ON_BN_CLICKED(IDC_POD_EXPORT_HELP,OnHelp)
	ON_EN_CHANGE(IDC_POD_EXPORT_FILENAME,OnEditchangeFileName)
	ON_CBN_SELCHANGE(IDC_POD_EXPORT_DIRECTORY,OnSelchangeSource)
	ON_LBN_SELCHANGE(IDC_POD_EXPORT_LIST,OnSelchangeDestination)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPODExportDialog message handlers

BOOL CPODExportDialog::OnInitDialog()
{
  CHourglassCursor  cCursor;

  CLocaleDialog::OnInitDialog();
  GetDlgItem(IDC_POD_EXPORT_DETAILS) -> EnableWindow();
  GetDlgItem(IDC_POD_EXPORT_ADD) -> EnableWindow((EnumDisplays() &&  SendDlgItemMessage(IDC_POD_EXPORT_DIRECTORY,CB_GETCURSEL) >= 0) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_EXPORT_ADDALL) -> EnableWindow((SendDlgItemMessage(IDC_POD_EXPORT_DIRECTORY,CB_GETCOUNT) > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_EXPORT_LIST_STATIC) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_EXPORT_LIST) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_EXPORT_REMOVE) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_EXPORT_REMOVEALL) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_EXPORT_FILENAME_STATIC) -> EnableWindow();
  GetDlgItem(IDC_POD_EXPORT_FILENAME) -> EnableWindow();
  GetDlgItem(IDC_POD_EXPORT_BROWSE) -> EnableWindow();
  GetDlgItem(IDC_POD_EXPORT_DIRECTORY) -> SetFocus();
  return FALSE;
}

void CPODExportDialog::OnAdd()
{
  INT  nLayout;
  INT  nLayouts;
  CString  szLayout;
  CPODLayout  *pLayout[2];
  CHourglassCursor  cCursor;

  GetDlgItem(IDC_POD_EXPORT_DIRECTORY) -> GetWindowText(szLayout);
  if (SendDlgItemMessage(IDC_POD_EXPORT_LIST,LB_ADDSTRING,(WPARAM) NULL,(LPARAM) (LPCTSTR) szLayout) >= 0)
  { if ((pLayout[0] = m_pDisplays[0].GetAt(m_pDisplays[0].Find(szLayout))))
    { if ((pLayout[1] = new CPODLayout))
      { pLayout[1] -> Copy(pLayout[0]);
        if (m_pDisplays[1].Add(pLayout[1]) < 0) delete pLayout[1];
      }
    }
    for (nLayout = 0,nLayouts = (INT) SendDlgItemMessage(IDC_POD_EXPORT_DIRECTORY,CB_GETCOUNT); nLayout < nLayouts; nLayout++)
    { if (SendDlgItemMessage(IDC_POD_EXPORT_LIST,LB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) Combobox_GetText(GetDlgItem(IDC_POD_EXPORT_DIRECTORY),nLayout)) < 0) break;
      continue;
    }
    SendDlgItemMessage(IDC_POD_EXPORT_LIST,LB_SETCURSEL,(WPARAM) SendDlgItemMessage(IDC_POD_EXPORT_LIST,LB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) szLayout));
    GetDlgItem(IDC_POD_EXPORT_ADD) -> EnableWindow(FALSE);
    GetDlgItem(IDC_POD_EXPORT_ADDALL) -> EnableWindow((nLayout < nLayouts) ? TRUE:FALSE);
    GetDlgItem(IDC_POD_EXPORT_LIST_STATIC) -> EnableWindow();
    GetDlgItem(IDC_POD_EXPORT_LIST) -> EnableWindow();
    GetDlgItem(IDC_POD_EXPORT_REMOVE) -> EnableWindow();
    GetDlgItem(IDC_POD_EXPORT_REMOVEALL) -> EnableWindow();
    GetDlgItem(IDC_POD_EXPORT_DIRECTORY) -> SetFocus();
  }
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODExportDialog::OnAddAll()
{
  INT  nLayout;
  INT  nLayouts;
  CString  szLayout;
  CPODLayout  *pLayout[2];
  CHourglassCursor  cCursor;

  for (nLayout = 0,nLayouts = (INT) SendDlgItemMessage(IDC_POD_EXPORT_DIRECTORY,CB_GETCOUNT); nLayout < nLayouts; nLayout++)
  { if (SendDlgItemMessage(IDC_POD_EXPORT_LIST,LB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) (szLayout = Combobox_GetText(GetDlgItem(IDC_POD_EXPORT_DIRECTORY),nLayout))) < 0)
    { SendDlgItemMessage(IDC_POD_EXPORT_LIST,LB_ADDSTRING,(WPARAM) NULL,(LPARAM) (LPCTSTR) szLayout);
      continue;
    }
  }
  for (nLayout = 0,nLayouts = (INT) m_pDisplays[0].GetSize(); nLayout < nLayouts; nLayout++)
  { if ((pLayout[0] = m_pDisplays[0].GetAt(nLayout)) &&  m_pDisplays[1].Find(pLayout[0] -> GetTitle()) < 0)
    { if ((pLayout[1] = new CPODLayout))
      { pLayout[1] -> Copy(pLayout[0]);
        if (m_pDisplays[1].Add(pLayout[1]) < 0)
        { delete pLayout[1];
          continue;
        }
      }
    }
  }
  GetDlgItem(IDC_POD_EXPORT_LIST_STATIC) -> EnableWindow((SendDlgItemMessage(IDC_POD_EXPORT_LIST,LB_GETCOUNT) > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_EXPORT_LIST) -> EnableWindow((SendDlgItemMessage(IDC_POD_EXPORT_LIST,LB_GETCOUNT) > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_EXPORT_ADD) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_EXPORT_ADDALL) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_EXPORT_REMOVE) -> EnableWindow((SendDlgItemMessage(IDC_POD_EXPORT_LIST,LB_GETCURSEL) >= 0) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_EXPORT_REMOVEALL) -> EnableWindow((SendDlgItemMessage(IDC_POD_EXPORT_LIST,LB_GETCOUNT) > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_EXPORT_DIRECTORY) -> SetFocus();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODExportDialog::OnRemove()
{
  INT  nIndex;
  CString  szLayout;
  CHourglassCursor  cCursor;

  if ((nIndex = m_pDisplays[1].Find(Listbox_GetText(GetDlgItem(IDC_POD_EXPORT_LIST),(INT) SendDlgItemMessage(IDC_POD_EXPORT_LIST,LB_GETCURSEL)))) >= 0)
  { delete m_pDisplays[1].GetAt(nIndex);
    m_pDisplays[1].RemoveAt(nIndex);
  }
  if (SendDlgItemMessage(IDC_POD_EXPORT_LIST,LB_DELETESTRING,(WPARAM) SendDlgItemMessage(IDC_POD_EXPORT_LIST,LB_GETCURSEL)) > 0)
  { SendDlgItemMessage(IDC_POD_EXPORT_LIST,LB_SETCURSEL);
    GetDlgItem(IDC_POD_EXPORT_DIRECTORY) -> GetWindowText(szLayout);
    GetDlgItem(IDC_POD_EXPORT_ADD) -> EnableWindow((SendDlgItemMessage(IDC_POD_EXPORT_LIST,LB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) szLayout) < 0) ? TRUE:FALSE);
    GetDlgItem(IDC_POD_EXPORT_ADDALL) -> EnableWindow((SendDlgItemMessage(IDC_POD_EXPORT_DIRECTORY,CB_GETCOUNT) > 0) ? TRUE:FALSE);
  }
  else
  { GetDlgItem(IDC_POD_EXPORT_LIST_STATIC) -> EnableWindow(FALSE);
    GetDlgItem(IDC_POD_EXPORT_LIST) -> EnableWindow(FALSE);
    GetDlgItem(IDC_POD_EXPORT_ADD) -> EnableWindow((SendDlgItemMessage(IDC_POD_EXPORT_DIRECTORY,CB_GETCURSEL) >= 0) ? TRUE:FALSE);
    GetDlgItem(IDC_POD_EXPORT_ADDALL) -> EnableWindow((SendDlgItemMessage(IDC_POD_EXPORT_DIRECTORY,CB_GETCOUNT) > 0) ? TRUE:FALSE);
    GetDlgItem(IDC_POD_EXPORT_REMOVE) -> EnableWindow(FALSE);
    GetDlgItem(IDC_POD_EXPORT_REMOVEALL) -> EnableWindow(FALSE);
  }
  GetDlgItem(IDC_POD_EXPORT_DIRECTORY) -> SetFocus();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODExportDialog::OnRemoveAll()
{
  CHourglassCursor  cCursor;

  m_pDisplays[1].RemoveAll();
  SendDlgItemMessage(IDC_POD_EXPORT_LIST,LB_RESETCONTENT);
  GetDlgItem(IDC_POD_EXPORT_LIST_STATIC) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_EXPORT_LIST) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_EXPORT_ADD) -> EnableWindow((SendDlgItemMessage(IDC_POD_EXPORT_DIRECTORY,CB_GETCURSEL) >= 0) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_EXPORT_ADDALL) -> EnableWindow((SendDlgItemMessage(IDC_POD_EXPORT_DIRECTORY,CB_GETCOUNT) > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_EXPORT_REMOVE) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_EXPORT_REMOVEALL) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_EXPORT_DIRECTORY) -> SetFocus();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODExportDialog::OnBrowse()
{
  CString  szFileName;
  CFileBrowseDialog  cFileBrowseDialog(this,IDC_POD_EXPORT_FILENAME,STRING(IDS_FILEBROWSEDIALOG_DATABASEFILEEXTENSION),STRING(IDS_FILEBROWSEDIALOG_DATABASEFILEFILTER));

  if (cFileBrowseDialog.DoModal() == IDOK)
  { szFileName = cFileBrowseDialog.GetPathName();
    GetDlgItem(IDC_POD_EXPORT_FILENAME) -> SetWindowText(szFileName);
  }
  SendDlgItemMessage(IDC_POD_EXPORT_FILENAME,EM_SETSEL,0,(LPARAM) -1);
  GetDlgItem(IDC_POD_EXPORT_FILENAME) -> SetFocus();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODExportDialog::OnEditchangeFileName()
{
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODExportDialog::OnSelchangeSource()
{
  CString  szLayout;

  GetDlgItem(IDC_POD_EXPORT_DIRECTORY) -> GetWindowText(szLayout);
  GetDlgItem(IDC_POD_EXPORT_ADD) -> EnableWindow((SendDlgItemMessage(IDC_POD_EXPORT_LIST,LB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) szLayout) < 0) ? TRUE:FALSE);
}

void CPODExportDialog::OnSelchangeDestination()
{
  GetDlgItem(IDC_POD_EXPORT_REMOVE) -> EnableWindow();
}

void CPODExportDialog::OnOK()
{
  DWORD  cbData;
  CFileEx  cFile;
  CString  szFileName;
  CByteArray  nFileData;
  CHourglassCursor  cCursor;

  GetDlgItem(IDC_POD_EXPORT_FILENAME) -> GetWindowText(szFileName);
  if (cFile.Open(szFileName,CFile::modeCreate | CFile::modeReadWrite | CFile::shareExclusive))
  { ReportEvent((!WriteFile(cFile.m_hFile,nFileData.GetData(),(m_pDisplays[1].Map(nFileData)) ? (DWORD) nFileData.GetSize():0,&cbData,(LPOVERLAPPED) NULL) ||  !cbData) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_ERROR):0,STRING(IDS_POD_EXPORT_FILE_FAILURE));
    cFile.Close();
  }
  else  ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_ERROR,STRING(IDS_POD_EXPORT_FILE_FAILURE));
  CLocaleDialog::OnOK();
}

BOOL CPODExportDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
  CHourglassCursor  cCursor;

  ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_PODEXPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE:SYSTEM_NOERROR);
  return TRUE;
}

void CPODExportDialog::OnHelp()
{
  CHourglassCursor  cCursor;

  ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_PODEXPORTDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE:SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CPODFindDialog dialog

IMPLEMENT_DYNCREATE(CPODFindDialog,CDisplayDialog)

CPODFindDialog::CPODFindDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CPODFindDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

INT CPODFindDialog::Create(CWnd *pParentWnd,INT nType,CPODLayout &cLayout)
{
  switch ((m_nType = nType))
  { case POD_TYPE_NORMAL:
    { GetDatabase() -> EnumPODs(m_pLayouts[0],FALSE);
      break;
    }
    case POD_TYPE_TEMPORARY:
    { EnumTemporaryPODs(m_pLayouts[0]);
      break;
    }
  }
  if (CDisplayDialog::Create(pParentWnd,CPODFindDialog::IDD) == IDOK  &&  m_pLayouts[1].GetSize() == 1)
  { cLayout.Copy(m_pLayouts[1].GetAt((INT) m_pLayouts[1].GetUpperBound()));
    m_pLayouts[0].RemoveAll();
    m_pLayouts[1].RemoveAll();
    return IDOK;
  }
  m_pLayouts[0].RemoveAll();
  m_pLayouts[1].RemoveAll();
  return IDCANCEL;
}

CPODWnd *CPODFindDialog::GetParent() CONST
{
  return((CPODWnd *) CDisplayDialog::GetParent());
}

BOOL CPODFindDialog::EnumSearchKeys()
{
  SendDlgItemMessage(IDC_POD_FIND_KEY,CB_INSERTSTRING,(WPARAM) -1,(LPARAM) STRING(IDS_PODFINDDIALOG_KEY_PARAMETER));
  SendDlgItemMessage(IDC_POD_FIND_KEY,CB_INSERTSTRING,(WPARAM) -1,(LPARAM) STRING(IDS_PODFINDDIALOG_KEY_DESCRIPTION));
  return((SendDlgItemMessage(IDC_POD_FIND_KEY,CB_SETCURSEL) >= 0) ? TRUE:FALSE);
}

BOOL CPODFindDialog::EnumSearchValues()
{
  INT  nItem;
  INT  nItems;
  CString  szKey;
  CString  szValue;
  CDatabaseTMParameter  *pDatabaseTMParameter;

  GetDlgItem(IDC_POD_FIND_KEY) -> GetWindowText(szKey);
  if (szKey == STRING(IDS_PODFINDDIALOG_KEY_PARAMETER))
  { for (nItem = 0,nItems = (INT) GetDatabase() -> GetTMParameters() -> GetSize(),SendDlgItemMessage(IDC_POD_FIND_VALUE,CB_RESETCONTENT); nItem < nItems; nItem++)
    { if ((pDatabaseTMParameter = (CDatabaseTMParameter *) GetDatabase() -> GetTMParameters() -> GetAt(nItem)) != (CDatabaseTMParameter *) NULL)
      { szValue.Format(STRING(IDS_PODFINDDIALOG_VALUE_FORMAT),(LPCTSTR) pDatabaseTMParameter -> GetTag(),(LPCTSTR) pDatabaseTMParameter -> GetDescription());
        SendDlgItemMessage(IDC_POD_FIND_VALUE,CB_INSERTSTRING,(WPARAM) -1,(LPARAM) (LPCTSTR) szValue);
      }
    }
  }
  if (szKey == STRING(IDS_PODFINDDIALOG_KEY_DESCRIPTION))
  { for (nItem = 0,nItems = (INT) m_szDescriptions.GetSize(),SendDlgItemMessage(IDC_POD_FIND_VALUE,CB_RESETCONTENT); nItem < nItems; nItem++)
    { SendDlgItemMessage(IDC_POD_FIND_VALUE,CB_INSERTSTRING,(WPARAM) -1,(LPARAM) (LPCTSTR) m_szDescriptions.GetAt(nItem));
      continue;
    }
  }
  return((SendDlgItemMessage(IDC_POD_FIND_VALUE,CB_GETCOUNT) >= 0) ? TRUE:FALSE);
}

VOID CPODFindDialog::DoFindByParameter(LPCTSTR pszParameter)
{
  INT  nLayout;
  INT  nLayouts;
  CString  szResult;
  CPODLayout  *pLayout;

  SendDlgItemMessage(IDC_POD_FIND_RESULTS,LB_RESETCONTENT);
  for (nLayout = 0,nLayouts = (m_pLayouts[1].Copy(&m_pLayouts[0])) ? (INT) m_pLayouts[1].GetSize():0; nLayout < nLayouts; nLayout++)
  { if ((pLayout = m_pLayouts[1].GetAt(nLayout)))
    { if (pLayout -> Find(pszParameter) >= 0)
      { if (pLayout -> GetTitle().IsEmpty())
        { SendDlgItemMessage(IDC_POD_FIND_RESULTS,LB_INSERTSTRING,(WPARAM) -1,(LPARAM) (LPCTSTR) pLayout -> GetName());
          continue;
        }
        szResult.Format(STRING(IDS_PODFINDDIALOG_RESULT_FORMAT),(LPCTSTR) pLayout -> GetName(),(LPCTSTR) pLayout -> GetTitle());
        SendDlgItemMessage(IDC_POD_FIND_RESULTS,LB_INSERTSTRING,(WPARAM) -1,(LPARAM) ((m_nType == POD_TYPE_NORMAL) ? (LPCTSTR) szResult:(LPCTSTR) pLayout -> GetTitle()));
      }
    }
  }
  GetDlgItem(IDC_POD_FIND_RESULTS_STATIC) -> EnableWindow((SendDlgItemMessage(IDC_POD_FIND_RESULTS,LB_GETCOUNT) > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_FIND_RESULTS) -> EnableWindow((SendDlgItemMessage(IDC_POD_FIND_RESULTS,LB_GETCOUNT) > 0) ? TRUE:FALSE);
}

VOID CPODFindDialog::DoFindByParameters(CONST CStringArray &szParameters)
{
  INT  nLayout;
  INT  nLayouts;
  INT  nParameter;
  INT  nParameters;
  CString  szResult;
  CPODLayout  *pLayout[2];

  for (nParameter = 0,nParameters = (m_pLayouts[1].Copy(&m_pLayouts[0])) ? (INT) szParameters.GetSize():0; nParameter < nParameters; nParameter += 2)
  { for (nLayout = 0,nLayouts = (!nParameter  ||  szParameters.GetAt(nParameter-1) == STRING(IDS_PODFINDDIALOG_QUERY_AND)) ? (INT) m_pLayouts[1].GetSize():-1; nLayout < nLayouts; nLayout++)
    { if ((pLayout[0] = m_pLayouts[1].GetAt(nLayout)) &&  pLayout[0] -> Find(szParameters.GetAt(nParameter)) < 0)
      { m_pLayouts[1].RemoveAt(nLayout);
        delete pLayout[0];
        nLayouts--;
        nLayout--;
      }
    }
    for (nLayout = 0,nLayouts = (nParameter > 0  &&  szParameters.GetAt(nParameter-1) == STRING(IDS_PODFINDDIALOG_QUERY_OR)) ? (INT) m_pLayouts[0].GetSize():-1; nLayout < nLayouts; nLayout++)
    { if ((pLayout[0] = m_pLayouts[0].GetAt(nLayout)) &&  pLayout[0] -> Find(szParameters.GetAt(nParameter)) >= 0)
      { if ((pLayout[1] = (m_pLayouts[1].Find(pLayout[0] -> GetName()) < 0) ? new CPODLayout:(CPODLayout *) NULL))
        { if (!pLayout[1] -> Copy(pLayout[0]) ||  m_pLayouts[1].Add(pLayout[1]) < 0)
          { delete pLayout[1];
            continue;
          }
        }
      }
    }
  }
  for (SendDlgItemMessage(IDC_POD_FIND_RESULTS,LB_RESETCONTENT); !nParameters; )
  { m_pLayouts[1].RemoveAll();
    break;
  }
  for (nLayout = 0,nLayouts = (INT) m_pLayouts[1].GetSize(); nLayout < nLayouts; nLayout++)
  { if ((pLayout[0] = m_pLayouts[1].GetAt(nLayout)))
    { if (pLayout[0] -> GetTitle().IsEmpty())
      { SendDlgItemMessage(IDC_POD_FIND_RESULTS,LB_INSERTSTRING,(WPARAM) -1,(LPARAM) (LPCTSTR) pLayout[0] -> GetName());
        continue;
      }
      szResult.Format(STRING(IDS_PODFINDDIALOG_RESULT_FORMAT),(LPCTSTR) pLayout[0] -> GetName(),(LPCTSTR) pLayout[0] -> GetTitle());
      SendDlgItemMessage(IDC_POD_FIND_RESULTS,LB_INSERTSTRING,(WPARAM) -1,(LPARAM) ((m_nType == POD_TYPE_NORMAL) ? (LPCTSTR) szResult:(LPCTSTR) pLayout[0] -> GetTitle()));
    }
  }
  GetDlgItem(IDC_POD_FIND_RESULTS_STATIC) -> EnableWindow((SendDlgItemMessage(IDC_POD_FIND_RESULTS,LB_GETCOUNT) > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_FIND_RESULTS) -> EnableWindow((SendDlgItemMessage(IDC_POD_FIND_RESULTS,LB_GETCOUNT) > 0) ? TRUE:FALSE);
}

VOID CPODFindDialog::DoFindByDescription(LPCTSTR pszDescription)
{
  INT  nLayout;
  INT  nLayouts;
  CString  szResult;
  CPODLayout  *pLayout;

  SendDlgItemMessage(IDC_POD_FIND_RESULTS,LB_RESETCONTENT);
  for (nLayout = 0,nLayouts = (m_pLayouts[1].Copy(&m_pLayouts[0])) ? (INT) m_pLayouts[1].GetSize():0; nLayout < nLayouts; nLayout++)
  { if ((pLayout = m_pLayouts[1].GetAt(nLayout)) &&  pLayout -> GetTitle().Find(pszDescription) >= 0)
    { szResult.Format(STRING(IDS_PODFINDDIALOG_RESULT_FORMAT),(LPCTSTR) pLayout -> GetName(),(LPCTSTR) pLayout -> GetTitle());
      SendDlgItemMessage(IDC_POD_FIND_RESULTS,LB_INSERTSTRING,(WPARAM) -1,(LPARAM) ((m_nType == POD_TYPE_NORMAL) ? (LPCTSTR) szResult:(LPCTSTR) pLayout -> GetTitle()));
    }
  }
  GetDlgItem(IDC_POD_FIND_RESULTS_STATIC) -> EnableWindow((SendDlgItemMessage(IDC_POD_FIND_RESULTS,LB_GETCOUNT) > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_FIND_RESULTS) -> EnableWindow((SendDlgItemMessage(IDC_POD_FIND_RESULTS,LB_GETCOUNT) > 0) ? TRUE:FALSE);
}

VOID CPODFindDialog::DoFindByDescriptions(CONST CStringArray &szDescriptions)
{
  INT  nLayout;
  INT  nLayouts;
  INT  nDescription;
  INT  nDescriptions;
  CString  szResult;
  CPODLayout  *pLayout[2];

  for (nDescription = 0,nDescriptions = (m_pLayouts[1].Copy(&m_pLayouts[0])) ? (INT) szDescriptions.GetSize():0; nDescription < nDescriptions; nDescription += 2)
  { for (nLayout = 0,nLayouts = (!nDescription  ||  szDescriptions.GetAt(nDescription-1) == STRING(IDS_PODFINDDIALOG_QUERY_AND)) ? (INT) m_pLayouts[1].GetSize():-1; nLayout < nLayouts; nLayout++)
    { if ((pLayout[0] = m_pLayouts[1].GetAt(nLayout)) &&  pLayout[0] -> GetTitle().Find(szDescriptions.GetAt(nDescription)) < 0)
      { m_pLayouts[1].RemoveAt(nLayout);
        delete pLayout[0];
        nLayouts--;
        nLayout--;
      }
    }
    for (nLayout = 0,nLayouts = (nDescription > 0  &&  szDescriptions.GetAt(nDescription-1) == STRING(IDS_PODFINDDIALOG_QUERY_OR)) ? (INT) m_pLayouts[0].GetSize():-1; nLayout < nLayouts; nLayout++)
    { if ((pLayout[0] = m_pLayouts[0].GetAt(nLayout)) &&  pLayout[0] -> GetTitle().Find(szDescriptions.GetAt(nDescription)) >= 0)
      { if ((pLayout[1] = (m_pLayouts[1].Find(pLayout[0] -> GetName()) < 0) ? new CPODLayout:(CPODLayout *) NULL))
        { if (!pLayout[1] -> Copy(pLayout[0]) ||  m_pLayouts[1].Add(pLayout[1]) < 0)
          { delete pLayout[1];
            continue;
          }
        }
      }
    }
  }
  for (SendDlgItemMessage(IDC_POD_FIND_RESULTS,LB_RESETCONTENT); !nDescriptions; )
  { m_pLayouts[1].RemoveAll();
    break;
  }
  for (nLayout = 0,nLayouts = (INT) m_pLayouts[1].GetSize(); nLayout < nLayouts; nLayout++)
  { if ((pLayout[0] = m_pLayouts[1].GetAt(nLayout)) != (CPODLayout *) NULL)
    { szResult.Format(STRING(IDS_PODFINDDIALOG_RESULT_FORMAT),(LPCTSTR) pLayout[0] -> GetName(),(LPCTSTR) pLayout[0] -> GetTitle());
      SendDlgItemMessage(IDC_POD_FIND_RESULTS,LB_INSERTSTRING,(WPARAM) -1,(LPARAM) ((m_nType == POD_TYPE_NORMAL) ? (LPCTSTR) szResult:(LPCTSTR) pLayout[0] -> GetTitle()));
    }
  }
  GetDlgItem(IDC_POD_FIND_RESULTS_STATIC) -> EnableWindow((SendDlgItemMessage(IDC_POD_FIND_RESULTS,LB_GETCOUNT) > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_FIND_RESULTS) -> EnableWindow((SendDlgItemMessage(IDC_POD_FIND_RESULTS,LB_GETCOUNT) > 0) ? TRUE:FALSE);
}

void CPODFindDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPODFindDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPODFindDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CPODFindDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_POD_FIND_SEARCH,OnSearch)
	ON_BN_CLICKED(IDC_POD_FIND_OPEN,OnOpen)
	ON_BN_CLICKED(IDC_POD_FIND_HELP,OnHelp)
	ON_CBN_EDITCHANGE(IDC_POD_FIND_VALUE,OnEditchangeValue)
	ON_CBN_SELCHANGE(IDC_POD_FIND_KEY,OnSelchangeKey)
	ON_CBN_SELCHANGE(IDC_POD_FIND_VALUE,OnSelchangeValue)
	ON_LBN_DBLCLK(IDC_POD_FIND_RESULTS,OnOpen)
	ON_LBN_SELCHANGE(IDC_POD_FIND_RESULTS,OnSelchangeResult)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPODFindDialog message handlers

BOOL CPODFindDialog::OnInitDialog() 
{
  CHourglassCursor  cCursor;

  CDisplayDialog::OnInitDialog();
  if (EnumSearchKeys() &&  EnumSearchValues())
  { GetDlgItem(IDC_POD_FIND_KEY_STATIC) -> EnableWindow();
    GetDlgItem(IDC_POD_FIND_KEY) -> EnableWindow();
    GetDlgItem(IDC_POD_FIND_VALUE_STATIC) -> EnableWindow();
    GetDlgItem(IDC_POD_FIND_VALUE) -> EnableWindow();
  }
  return TRUE;
}

void CPODFindDialog::OnSearch()
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

  GetDlgItem(IDC_POD_FIND_KEY) -> GetWindowText(szKey);
  GetDlgItem(IDC_POD_FIND_VALUE) -> GetWindowText(szValue);
  if (szKey == STRING(IDS_PODFINDDIALOG_KEY_PARAMETER))
  { if ((nIndex = (INT) SendDlgItemMessage(IDC_POD_FIND_VALUE,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) szValue)) >= 0)
    { if ((pDatabaseTMParameter = GetDatabase() -> GetTMParameters() -> GetAt(nIndex)))
      { DoFindByParameter(pDatabaseTMParameter -> GetTag());
        return;
      }
    }
    if ((pDatabaseTMParameter = GetDatabase() -> GetTMParameters() -> GetAt(GetDatabase() -> GetTMParameters() -> Find(szValue))))
    { DoFindByParameter(pDatabaseTMParameter -> GetTag());
      return;
    }
    for (nPos = 0; nPos < szValue.GetLength(); nPos++)
    { for (szParameter.Empty(); nPos < szValue.GetLength(); nPos++)
      { if (!_istspace(szValue.GetAt(nPos))) break;
        continue;
      }
      if (szValue.GetAt(nPos) != STRINGCHAR(IDS_PODFINDDIALOG_QUERY_QUOTE))
      { nPos = -1;
        break;
      }
      for (nPos++; nPos < szValue.GetLength(); nPos++)
      { if (!_istspace(szValue.GetAt(nPos)) &&  szValue.GetAt(nPos) != STRINGCHAR(IDS_PODFINDDIALOG_QUERY_QUOTE))
        { szParameter += szValue.GetAt(nPos);
          continue;
        }
        break;
      }
      if (szValue.GetAt(nPos) != STRINGCHAR(IDS_PODFINDDIALOG_QUERY_QUOTE))
      { nPos = -1;
        break;
      }
      if ((pDatabaseTMParameter = GetDatabase() -> GetTMParameters() -> GetAt(GetDatabase() -> GetTMParameters() -> Find(szParameter))))
      { for (nPos++,szParameters.Add(szParameter); nPos < szValue.GetLength(); nPos++)
        { if (!_istspace(szValue.GetAt(nPos))) break;
          continue;
        }
        if (szValue.GetAt(nPos) == STRINGCHAR(IDS_PODFINDDIALOG_QUERY_AND) ||  szValue.GetAt(nPos) == STRINGCHAR(IDS_PODFINDDIALOG_QUERY_OR))
        { szParameters.Add(szValue.GetAt(nPos));
          continue;
        }
      }
      break;
    }
    if (nPos >= szValue.GetLength())
    { if (szParameters.GetSize() > 0)
      { DoFindByParameters(szParameters);
        return;
      }
    }
    GetDlgItem(IDC_POD_FIND_VALUE) -> SetFocus();
    CAudioDevice::AlertBySound();
    return;
  }
  if (szKey == STRING(IDS_PODFINDDIALOG_KEY_DESCRIPTION))
  { for (nItem = 0,nItems = (INT) m_szDescriptions.GetSize(); nItem < nItems; nItem++)
    { if (m_szDescriptions.GetAt(nItem) == szValue) break;
      continue;
    }
    for ( ; nItem == nItems; )
    { SendDlgItemMessage(IDC_POD_FIND_VALUE,CB_ADDSTRING,(WPARAM) NULL,(LPARAM) (LPCTSTR) szValue);
      m_szDescriptions.Add(szValue);
      break;
    }
    if ((nPos = szValue.Find(STRING(IDS_PODFINDDIALOG_QUERY_QUOTE))) < 0)
    { DoFindByDescription(szValue);
      return;
    }
    for (nPos = 0; nPos < szValue.GetLength(); nPos++)
    { for (szDescription.Empty(); nPos < szValue.GetLength(); nPos++)
      { if (!_istspace(szValue.GetAt(nPos))) break;
        continue;
      }
      if (szValue.GetAt(nPos) != STRINGCHAR(IDS_PODFINDDIALOG_QUERY_QUOTE))
      { nPos = -1;
        break;
      }
      for (nPos++; nPos < szValue.GetLength(); nPos++)
      { if (!_istspace(szValue.GetAt(nPos)) &&  szValue.GetAt(nPos) != STRINGCHAR(IDS_PODFINDDIALOG_QUERY_QUOTE))
        { szDescription += szValue.GetAt(nPos);
          continue;
        }
        break;
      }
      if (szValue.GetAt(nPos) != STRINGCHAR(IDS_PODFINDDIALOG_QUERY_QUOTE))
      { nPos = -1;
        break;
      }
      for (nPos++,szDescriptions.Add(szDescription); nPos < szValue.GetLength(); nPos++)
      { if (!_istspace(szValue.GetAt(nPos))) break;
        continue;
      }
      if (szValue.GetAt(nPos) == STRINGCHAR(IDS_PODFINDDIALOG_QUERY_AND) ||  szValue.GetAt(nPos) == STRINGCHAR(IDS_PODFINDDIALOG_QUERY_OR))
      { szDescriptions.Add(szValue.GetAt(nPos));
        continue;
      }
      break;
    }
    if (nPos >= szValue.GetLength())
    { if (szDescriptions.GetSize() > 0)
      { DoFindByDescriptions(szDescriptions);
        return;
      }
    }
    GetDlgItem(IDC_POD_FIND_VALUE) -> SetFocus();
    CAudioDevice::AlertBySound();
    return;
  }
}

void CPODFindDialog::OnOpen()
{
  INT  nLayout[2];
  INT  nLayouts[2];
  CString  szTitle[2];
  CPODLayout  *pLayout;
  CHourglassCursor  cCursor;

  for (nLayout[0] = 0,nLayouts[0] = (INT) m_pLayouts[1].GetSize(),szTitle[0] = Listbox_GetText(GetDlgItem(IDC_POD_FIND_RESULTS),(INT) SendDlgItemMessage(IDC_POD_FIND_RESULTS,LB_GETCURSEL)); nLayout[0] < nLayouts[0]; nLayout[0]++)
  { if ((pLayout = m_pLayouts[1].GetAt(nLayout[0])))
    { for ( ; pLayout -> GetTitle().IsEmpty(); )
      { szTitle[1] = pLayout -> GetName();
        break;
      }
      if (!pLayout -> GetTitle().IsEmpty()) szTitle[1].Format(STRING(IDS_PODFINDDIALOG_RESULT_FORMAT),(LPCTSTR) pLayout -> GetName(),(LPCTSTR) pLayout -> GetTitle());
      if ((m_nType == POD_TYPE_NORMAL  &&  szTitle[0] == szTitle[1]) || (m_nType == POD_TYPE_TEMPORARY  &&  szTitle[0] == pLayout -> GetTitle())) break;
    }
  }
  for (nLayout[1] = 0,nLayouts[1] = (nLayout[0] < nLayouts[0]) ? nLayout[0]:nLayouts[0]; nLayout[1] < nLayouts[1]; nLayout[1]++)
  { if ((pLayout = m_pLayouts[1].GetAt(0))) delete pLayout;
    m_pLayouts[1].RemoveAt(0);
  }
  for (nLayout[1] = 1,nLayouts[1] = (nLayout[0] < nLayouts[0]) ? (INT) m_pLayouts[1].GetSize():0; nLayout[1] < nLayouts[1]; nLayout[1]++)
  { if ((pLayout = m_pLayouts[1].GetAt(1))) delete pLayout;
    m_pLayouts[1].RemoveAt(1);
  }
  EndDialog(IDOK);
}

void CPODFindDialog::OnSelchangeKey()
{
  EnumSearchValues();
  GetDlgItem(IDC_POD_FIND_SEARCH) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_FIND_VALUE) -> SetFocus();
}

void CPODFindDialog::OnSelchangeValue()
{
  GetDlgItem(IDC_POD_FIND_SEARCH) -> EnableWindow((SendDlgItemMessage(IDC_POD_FIND_VALUE,CB_GETCURSEL) >= 0) ? TRUE:FALSE);
}

void CPODFindDialog::OnSelchangeResult()
{
  GetDlgItem(IDC_POD_FIND_OPEN) -> EnableWindow();
}

void CPODFindDialog::OnEditchangeValue()
{
  GetDlgItem(IDC_POD_FIND_SEARCH) -> EnableWindow((GetDlgItem(IDC_POD_FIND_VALUE) -> GetWindowTextLength() > 0) ? TRUE:FALSE);
}

void CPODFindDialog::OnOK()
{
  CHourglassCursor  cCursor;

  m_pLayouts[1].RemoveAll();
  CDisplayDialog::OnOK();
}

BOOL CPODFindDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
  CHourglassCursor  cCursor;

  ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_PODFINDDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE:SYSTEM_NOERROR);
  return TRUE;
}

void CPODFindDialog::OnHelp()
{
  CHourglassCursor  cCursor;

  ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_PODFINDDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE:SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CPODOpenDialog dialog

IMPLEMENT_DYNCREATE(CPODOpenDialog,CDisplayDialog)

CPODOpenDialog::CPODOpenDialog() : CDisplayDialog()
{
	//{{AFX_DATA_INIT(CPODOpenDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CPODOpenDialog::Initialize()
{
  m_nFilterMode = 0;
  m_nFilterLimit = 0;
  m_nFilterDigits = 0;
  m_nFilterStatus = 0;
  m_nRetrieveMode = 0;
  m_nRetrieveSpeed = 0;
  m_tRetrieveStartTime = 0;
  m_tRetrieveStopTime = 0;
  m_tRetrieveInterval = 0;
  m_tFilterRange[0][0] = 0;
  m_tFilterRange[0][1] = 0;
  m_tFilterRange[1][0] = 0;
  m_tFilterRange[1][1] = 0;
  m_tFilterDailyRange[0] = 0;
  m_tFilterDailyRange[1] = 0;
  m_tFilterPeriodical = 0;
  m_bLayoutToolTips = FALSE;
  ZeroMemory(&m_fntLayoutTitle[0],sizeof(LOGFONT));
  ZeroMemory(&m_fntLayoutTitle[1],sizeof(LOGFONT));
  ZeroMemory(&m_fntLayoutTitle[2],sizeof(LOGFONT));
  ZeroMemory(&m_fntLayoutItems[0],sizeof(LOGFONT));
  ZeroMemory(&m_fntLayoutItems[1],sizeof(LOGFONT));
  ZeroMemory(&m_fntLayoutItems[2],sizeof(LOGFONT));
  return TRUE;
}

INT CPODOpenDialog::Create(CWnd *pParentWnd)
{
  return CDisplayDialog::Create(pParentWnd,CPODOpenDialog::IDD);
}

CString CPODOpenDialog::GetTitle() CONST
{
  CString  szTitle;
  CPODLayout  cPODLayout;

  if (FindLayout(cPODLayout) || (GetType() == POD_TYPE_TEMPORARY  &&  GetLayout(cPODLayout)))
  { szTitle.Format(STRING(IDS_WINDOW_FULLTITLE),STRING(IDS_DISPLAY_TITLE_POD),(!cPODLayout.GetTitle().IsEmpty()) ? (LPCTSTR) cPODLayout.GetTitle():(LPCTSTR) cPODLayout.GetName());
    return szTitle;
  }
  return STRING(IDS_DISPLAY_TITLE_POD);
}

UINT CPODOpenDialog::GetType() CONST
{
  return((IsDlgButtonChecked(IDC_POD_OPEN_TYPE_NORMAL) ||  IsDlgButtonChecked(IDC_POD_OPEN_TYPE_TEMPORARY)) ? ((IsDlgButtonChecked(IDC_POD_OPEN_TYPE_NORMAL)) ? POD_TYPE_NORMAL:POD_TYPE_TEMPORARY):-1);
}

UINT CPODOpenDialog::GetMode() CONST
{
  return((IsDlgButtonChecked(IDC_POD_OPEN_MODE_REALTIME) ||  IsDlgButtonChecked(IDC_POD_OPEN_MODE_HISTORY)) ? (IsDlgButtonChecked(IDC_POD_OPEN_MODE_REALTIME)*DISPLAY_MODE_REALTIME+IsDlgButtonChecked(IDC_POD_OPEN_MODE_HISTORY)*DISPLAY_MODE_HISTORY):-1);
}

BOOL CPODOpenDialog::GetLayout(CPODLayout &cLayout) CONST
{
  CString  szTitle;

  if (GetType() == POD_TYPE_TEMPORARY  &&  !FindLayout(cLayout))
  { GetDlgItem(IDC_POD_OPEN_DISPLAY) -> GetWindowText(szTitle);
    cLayout.SetColumns((!cLayout.GetColumns()) ? POD_TITLEITEMS_DEFAULT:cLayout.GetColumns());
    cLayout.SetTitle(szTitle);
    cLayout.SetName(szTitle);
    return InitializeLayout(cLayout);
  }
  return((FindLayout(cLayout)) ? InitializeLayout(cLayout):FALSE);
}

BOOL CPODOpenDialog::GetLayoutTitleFonts(LPLOGFONT plfDataFont,LPLOGFONT plfParametersFont,LPLOGFONT plfFunctionsFont) CONST
{
  if (IsLayoutModified())
  { CopyMemory(plfDataFont,&m_fntLayoutTitle[0],sizeof(LOGFONT));
    CopyMemory(plfParametersFont,&m_fntLayoutTitle[1],sizeof(LOGFONT));
    CopyMemory(plfFunctionsFont,&m_fntLayoutTitle[2],sizeof(LOGFONT));
    return TRUE;
  }
  return FALSE;
}

BOOL CPODOpenDialog::GetLayoutItemsFonts(LPLOGFONT plfDataFont,LPLOGFONT plfParametersFont,LPLOGFONT plfFunctionsFont) CONST
{
  if (IsLayoutModified())
  { CopyMemory(plfDataFont,&m_fntLayoutItems[0],sizeof(LOGFONT));
    CopyMemory(plfParametersFont,&m_fntLayoutItems[1],sizeof(LOGFONT));
    CopyMemory(plfFunctionsFont,&m_fntLayoutItems[2],sizeof(LOGFONT));
    return TRUE;
  }
  return FALSE;
}

BOOL CPODOpenDialog::GetLayoutToolTipMode(BOOL &bEnable) CONST
{
  if (IsLayoutModified())
  { bEnable = m_bLayoutToolTips;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODOpenDialog::IsLayoutModified() CONST
{
  CPODLayout  cPODLayout;
  LOGFONT  fntSample={0};

  return((!m_cLayout.Compare(&cPODLayout) ||  memcmp(&m_fntLayoutTitle[0],&fntSample,sizeof(LOGFONT)) ||  memcmp(&m_fntLayoutTitle[1],&fntSample,sizeof(LOGFONT)) ||  memcmp(&m_fntLayoutTitle[2],&fntSample,sizeof(LOGFONT)) ||  memcmp(&m_fntLayoutItems[0],&fntSample,sizeof(LOGFONT)) ||  memcmp(&m_fntLayoutItems[1],&fntSample,sizeof(LOGFONT)) ||  memcmp(&m_fntLayoutItems[2],&fntSample,sizeof(LOGFONT)) ||  m_bLayoutToolTips) ? TRUE:FALSE);
}

BOOL CPODOpenDialog::GetFilterMode(UINT &nMode) CONST
{
  if (IsFilteringModified())
  { nMode = m_nFilterMode;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODOpenDialog::GetFilterLimit(UINT &nLimit) CONST
{
  if (IsFilteringModified())
  { nLimit = m_nFilterLimit;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODOpenDialog::GetFilterDigits(UINT &nDigits) CONST
{
  if (IsFilteringModified())
  { nDigits = m_nFilterDigits;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODOpenDialog::GetFilterStatus(UINT &nStatus) CONST
{
  if (IsFilteringModified())
  { nStatus = m_nFilterStatus;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODOpenDialog::GetFilterRange(CTimeKey &tStartTime,CTimeKey &tStopTime) CONST
{
  if (IsFilteringModified())
  { tStartTime = m_tFilterRange[0][0];
    tStopTime = m_tFilterRange[0][1];
    return TRUE;
  }
  return FALSE;
}

BOOL CPODOpenDialog::GetFilterDailyRange(CTimeSpan &tStartTime,CTimeSpan &tStopTime) CONST
{
  if (IsFilteringModified())
  { tStartTime = m_tFilterDailyRange[0];
    tStopTime = m_tFilterDailyRange[1];
    return TRUE;
  }
  return FALSE;
}

BOOL CPODOpenDialog::GetFilterPeriodicalRange(CTimeKey &tStartTime,CTimeSpan &tInterval,CTimeKey &tStopTime) CONST
{
  if (IsFilteringModified())
  { tStartTime = m_tFilterRange[1][0];
    tStopTime = m_tFilterRange[1][1];
    tInterval = m_tFilterPeriodical;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODOpenDialog::GetFilterColors(CUIntArray &nColors) CONST
{
  if (IsFilteringModified())
  { nColors.Copy(m_nFilterColors);
    return TRUE;
  }
  return FALSE;
}

BOOL CPODOpenDialog::IsFilteringModified() CONST
{
  return((m_nFilterMode  ||  m_nFilterDigits > 0  ||  m_nFilterColors.GetSize() > 0) ? TRUE:FALSE);
}

BOOL CPODOpenDialog::GetRetrieveMode(UINT &nMode) CONST
{
  nMode = m_nRetrieveMode;
  return TRUE;
}

BOOL CPODOpenDialog::GetRetrieveSpeed(UINT &nSpeed) CONST
{
  nSpeed = m_nRetrieveSpeed;
  return((m_nRetrieveMode & POD_RETRIEVE_AUTOFORWARD) ? TRUE:FALSE);
}

BOOL CPODOpenDialog::GetRetrieveInterval(CTimeSpan &tInterval) CONST
{
  tInterval = m_tRetrieveInterval;
  return(((m_nRetrieveMode & POD_RETRIEVE_AUTOFORWARD) || (m_nRetrieveMode & POD_RETRIEVE_MANUALFORWARD)) ? TRUE:FALSE);
}

BOOL CPODOpenDialog::GetRetrieveStartTime(CTimeKey &tTimeKey) CONST
{
  tTimeKey = m_tRetrieveStartTime;
  return(((m_nRetrieveMode & POD_RETRIEVE_AUTOFORWARD) || (m_nRetrieveMode & POD_RETRIEVE_PSEUDOREALTIME) || (m_nRetrieveMode & POD_RETRIEVE_MANUALFORWARD)) ? TRUE:FALSE);
}

BOOL CPODOpenDialog::GetRetrieveStopTime(CTimeKey &tTimeKey) CONST
{
  tTimeKey = m_tRetrieveStopTime;
  return((((m_nRetrieveMode & POD_RETRIEVE_AUTOFORWARD) || (m_nRetrieveMode & POD_RETRIEVE_PSEUDOREALTIME) || (m_nRetrieveMode & POD_RETRIEVE_MANUALFORWARD)) && (m_nRetrieveMode & POD_RETRIEVE_STOPBYTIME)) ? TRUE:FALSE);
}

BOOL CPODOpenDialog::GetRetrieveFileName(CString &szFileName) CONST
{
  szFileName = ((m_nRetrieveMode & POD_RETRIEVE_AUTOFORWARD) || (m_nRetrieveMode & POD_RETRIEVE_PSEUDOREALTIME) || (m_nRetrieveMode & POD_RETRIEVE_MANUALFORWARD)) ? (LPCTSTR) m_szRetrieveFileName:EMPTYSTRING;
  return !szFileName.IsEmpty();
}

BOOL CPODOpenDialog::IsRetrievingModified() CONST
{
  return((m_nRetrieveMode != 0) ? TRUE:FALSE);
}

BOOL CPODOpenDialog::GetPrintJobs(CPODPrintJobs &pPrintJobs) CONST
{
  CByteArray  nPrintInfo;

  return((IsPrintingModified()) ? pPrintJobs.Copy(&m_pPrintJobs):pPrintJobs.Unmap(nPrintInfo));
}

BOOL CPODOpenDialog::IsPrintingModified() CONST
{
  return((m_pPrintJobs.GetSize() > 0) ? TRUE:FALSE);
}

CPODWnd *CPODOpenDialog::GetParent() CONST
{
  return((CPODWnd *) CDisplayDialog::GetParent());
}

VOID CPODOpenDialog::EnumLayouts()
{
  INT  nDisplay;
  INT  nDisplays;
  CString  szDisplay;
  CPODLayout  *pPODLayout;
  CPODLayouts  pPODLayouts;

  for (nDisplay = 0,nDisplays = (IsDlgButtonChecked(IDC_POD_OPEN_TYPE_NORMAL)) ? GetDatabase() -> EnumPODs(pPODLayouts):EnumTemporaryPODs(pPODLayouts),SendDlgItemMessage(IDC_POD_OPEN_DISPLAY,CB_RESETCONTENT); nDisplay < nDisplays; nDisplay++)
  { if ((pPODLayout = pPODLayouts.GetAt(nDisplay)))
    { if (pPODLayout -> GetTitle().IsEmpty())
      { SendDlgItemMessage(IDC_POD_OPEN_DISPLAY,CB_ADDSTRING,(WPARAM) NULL,(LPARAM) (LPCTSTR) pPODLayout -> GetName());
        continue;
      }
      szDisplay.Format(STRING(IDS_PODOPENDIALOG_TITLE),(LPCTSTR) pPODLayout -> GetName(),(LPCTSTR) pPODLayout -> GetTitle());
      SendDlgItemMessage(IDC_POD_OPEN_DISPLAY,CB_ADDSTRING,(WPARAM) NULL,(LPARAM) ((IsDlgButtonChecked(IDC_POD_OPEN_TYPE_NORMAL)) ? (LPCTSTR) szDisplay:(LPCTSTR) pPODLayout -> GetTitle()));
    }
  }
  GetDlgItem(IDC_POD_OPEN_REMOVE) -> ShowWindow((IsDlgButtonChecked(IDC_POD_OPEN_TYPE_TEMPORARY)) ? SW_SHOW:SW_HIDE);
  GetDlgItem(IDC_POD_OPEN_DISPLAY_STATIC) -> EnableWindow((IsDlgButtonChecked(IDC_POD_OPEN_TYPE_TEMPORARY) ||  SendDlgItemMessage(IDC_POD_OPEN_DISPLAY,CB_GETCOUNT) > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_OPEN_DISPLAY) -> EnableWindow((IsDlgButtonChecked(IDC_POD_OPEN_TYPE_TEMPORARY) ||  SendDlgItemMessage(IDC_POD_OPEN_DISPLAY,CB_GETCOUNT) > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_OPEN_FIND) -> EnableWindow((SendDlgItemMessage(IDC_POD_OPEN_DISPLAY,CB_GETCOUNT) > 0) ? TRUE:FALSE);
  GetDlgItem(IDC_POD_OPEN_SETTINGS) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_OPEN_REMOVE) -> EnableWindow(FALSE);
}

BOOL CPODOpenDialog::FindLayout() CONST
{
  CPODLayout  cPODLayout;

  return FindLayout(cPODLayout);
}
BOOL CPODOpenDialog::FindLayout(CPODLayout &cLayout) CONST
{
  INT  nDisplay;
  INT  nDisplays;
  CString  szDisplay[2];
  CPODLayout  *pPODLayout;
  CPODLayouts  pPODLayouts;

  for (GetDlgItem(IDC_POD_OPEN_DISPLAY) -> GetWindowText(szDisplay[0]); IsDlgButtonChecked(IDC_POD_OPEN_TYPE_NORMAL); )
  { for (nDisplay = 0,nDisplays = GetDatabase() -> EnumPODs(pPODLayouts); nDisplay < nDisplays; nDisplay++)
    { if (!(pPODLayout = pPODLayouts.GetAt(nDisplay)))
      { pPODLayouts.RemoveAt(nDisplay);
        nDisplays--;
        nDisplay--;
        continue;
      }
      szDisplay[1].Format(STRING(IDS_PODOPENDIALOG_TITLE),(LPCTSTR) pPODLayout -> GetName(),(LPCTSTR) pPODLayout -> GetTitle());
      if (!szDisplay[0].CompareNoCase(szDisplay[1]) ||  !szDisplay[0].CompareNoCase(pPODLayout -> GetName()) ||  !szDisplay[0].CompareNoCase(pPODLayout -> GetTitle()))
      { if (GetDatabase() -> LoadPOD(pPODLayout -> GetName(),cLayout)) break;
        continue;
      }
    }
    return((nDisplay < nDisplays) ? TRUE:FALSE);
  }
  if (IsDlgButtonChecked(IDC_POD_OPEN_TYPE_TEMPORARY))
  { for (nDisplay = 0,nDisplays = EnumTemporaryPODs(pPODLayouts); nDisplay < nDisplays; nDisplay++)
    { if (!(pPODLayout = pPODLayouts.GetAt(nDisplay)))
      { pPODLayouts.RemoveAt(nDisplay);
        nDisplays--;
        nDisplay--;
        continue;
      }
      if (!szDisplay[0].CompareNoCase(pPODLayout -> GetTitle()))
      { if (cLayout.Copy(pPODLayout)) break;
        continue;
      }
    }
    return((nDisplay < nDisplays) ? TRUE:FALSE);
  }
  return FALSE;
}

BOOL CPODOpenDialog::InitializeLayout(CPODLayout &cLayout) CONST
{
  return((m_cLayout.GetName() == cLayout.GetName()) ? cLayout.Copy(&m_cLayout):TRUE);
}

BOOL CPODOpenDialog::Check(BOOL bModified) CONST
{
  CPODLayout  cPODLayout;

  return(((IsDlgButtonChecked(IDC_POD_OPEN_MODE_REALTIME) ||  IsDlgButtonChecked(IDC_POD_OPEN_MODE_HISTORY)) && ((!IsDlgButtonChecked(IDC_POD_OPEN_TYPE_TEMPORARY) &&  FindLayout(cPODLayout)) || (IsDlgButtonChecked(IDC_POD_OPEN_TYPE_TEMPORARY) && (FindLayout(cPODLayout) || (GetDlgItem(IDC_POD_OPEN_DISPLAY) -> GetWindowTextLength() > 0  &&  CheckAccountPrivilege(PRIVILEGE_POD_TEMPORARYUSE))))) && (IsDlgButtonChecked(IDC_POD_OPEN_MODE_REALTIME) ||  IsRetrievingModified())) ? TRUE:FALSE);
}

void CPODOpenDialog::DoDataExchange(CDataExchange *pDX)
{
	CDisplayDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPODOpenDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void CPODOpenDialog::PostNcDestroy()
{
  m_cLayout.RemoveAll();
  m_pPrintJobs.RemoveAll();
  m_nFilterColors.RemoveAll();
  CDisplayDialog::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CPODOpenDialog, CDisplayDialog)
	//{{AFX_MSG_MAP(CPODOpenDialog)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_POD_OPEN_SETTINGS,OnSettings)
	ON_BN_CLICKED(IDC_POD_OPEN_FIND,OnFind)
	ON_BN_CLICKED(IDC_POD_OPEN_REMOVE,OnRemove)
	ON_BN_CLICKED(IDC_POD_OPEN_TYPE_NORMAL,OnTypeNormal)
	ON_BN_CLICKED(IDC_POD_OPEN_TYPE_TEMPORARY,OnTypeTemporary)
	ON_BN_CLICKED(IDC_POD_OPEN_MODE_REALTIME,OnRealtimeMode)
	ON_BN_CLICKED(IDC_POD_OPEN_MODE_HISTORY,OnHistoryMode)
	ON_BN_CLICKED(IDC_POD_OPEN_HELP,OnHelp)
	ON_CBN_EDITCHANGE(IDC_POD_OPEN_DISPLAY,OnEditchangeTitle)
	ON_CBN_SELCHANGE(IDC_POD_OPEN_DISPLAY,OnSelchangeTitle)
	ON_CBN_DBLCLK(IDC_POD_OPEN_DISPLAY,OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPODOpenDialog message handlers

BOOL CPODOpenDialog::OnInitDialog() 
{
  CHourglassCursor  cCursor;

  CDisplayDialog::OnInitDialog();
  CheckRadioButton(IDC_POD_OPEN_TYPE_NORMAL,IDC_POD_OPEN_TYPE_TEMPORARY,IDC_POD_OPEN_TYPE_NORMAL);
  CheckDlgButton(IDC_POD_OPEN_MODE_REALTIME,TRUE);
  CheckDlgButton(IDC_POD_OPEN_MODE_HISTORY,FALSE);
  GetDlgItem(IDC_POD_OPEN_DETAILS) -> EnableWindow();
  GetDlgItem(IDC_POD_OPEN_TYPE) -> EnableWindow();
  GetDlgItem(IDC_POD_OPEN_TYPE_NORMAL) -> EnableWindow();
  GetDlgItem(IDC_POD_OPEN_TYPE_TEMPORARY) -> EnableWindow();
  GetDlgItem(IDC_POD_OPEN_MODE) -> EnableWindow();
  GetDlgItem(IDC_POD_OPEN_MODE_REALTIME) -> EnableWindow();
  GetDlgItem(IDC_POD_OPEN_MODE_HISTORY) -> EnableWindow(CheckAccountPrivilege(PRIVILEGE_OFFLINE_OPERATE));
  EnumLayouts();
  return TRUE;
}

void CPODOpenDialog::OnSettings()
{
  ReportEvent((m_dlgSettings.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE:SYSTEM_NOERROR);
}

void CPODOpenDialog::OnFind()
{
  INT  nResult;
  CString  szDisplay;
  CPODLayout  cPODLayout;

  if ((nResult = m_dlgFindDisplay.Create(this,(IsDlgButtonChecked(IDC_POD_OPEN_TYPE_NORMAL)) ? POD_TYPE_NORMAL:((IsDlgButtonChecked(IDC_POD_OPEN_TYPE_TEMPORARY)) ? POD_TYPE_TEMPORARY:0),cPODLayout)) == IDOK)
  { for (szDisplay.Format(STRING(IDS_PODOPENDIALOG_TITLE),(LPCTSTR) cPODLayout.GetName(),(LPCTSTR) cPODLayout.GetTitle()); cPODLayout.GetTitle().IsEmpty(); )
    { szDisplay = cPODLayout.GetName();
      break;
    }
    GetDlgItem(IDC_POD_OPEN_SETTINGS) -> EnableWindow((SendDlgItemMessage(IDC_POD_OPEN_DISPLAY,CB_SETCURSEL,(WPARAM) SendDlgItemMessage(IDC_POD_OPEN_DISPLAY,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) ((IsDlgButtonChecked(IDC_POD_OPEN_TYPE_NORMAL)) ? (LPCTSTR) szDisplay:(LPCTSTR) cPODLayout.GetTitle()))) >= 0  && (GetMode() != DISPLAY_MODE_REALTIME  ||  !GetParent() -> Find(MAKELONG(DISPLAY_TYPE_POD,GetType()),GetMode(),cPODLayout.GetName()))) ? (!IsDlgButtonChecked(IDC_POD_OPEN_TYPE_TEMPORARY) ||  CheckAccountPrivilege(PRIVILEGE_POD_TEMPORARYUSE)):FALSE);
    GetDlgItem(IDC_POD_OPEN_DISPLAY) -> SetFocus();
  }
  ReportEvent((nResult <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE:SYSTEM_NOERROR);
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODOpenDialog::OnRemove()
{
  CPODLayout  cPODLayout;
  CHourglassCursor  cCursor;

  if (FindLayout(cPODLayout) &&  RemoveTemporaryPOD(cPODLayout.GetName()))
  { SendDlgItemMessage(IDC_POD_OPEN_DISPLAY,CB_DELETESTRING,(WPARAM) SendDlgItemMessage(IDC_POD_OPEN_DISPLAY,CB_FINDSTRINGEXACT,(WPARAM) -1,(LPARAM) (LPCTSTR) cPODLayout.GetName()));
    SendDlgItemMessage(IDC_POD_OPEN_DISPLAY,CB_SETCURSEL,(WPARAM) -1);
  }
  GetDlgItem(IDC_POD_OPEN_SETTINGS) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_OPEN_REMOVE) -> EnableWindow(FALSE);
  GetDlgItem(IDC_POD_OPEN_DISPLAY) -> SetFocus();
  GetDlgItem(IDOK) -> EnableWindow(FALSE);
}

void CPODOpenDialog::OnEditchangeTitle()
{
  CPODLayout  cPODLayout;

  GetDlgItem(IDC_POD_OPEN_SETTINGS) -> EnableWindow((((!IsDlgButtonChecked(IDC_POD_OPEN_TYPE_TEMPORARY) &&  FindLayout(cPODLayout)) || (IsDlgButtonChecked(IDC_POD_OPEN_TYPE_TEMPORARY) && (FindLayout(cPODLayout) ||  GetDlgItem(IDC_POD_OPEN_DISPLAY) -> GetWindowTextLength() > 0))) && (GetMode() != DISPLAY_MODE_REALTIME  ||  !GetParent() -> Find(MAKELONG(DISPLAY_TYPE_POD,GetType()),GetMode(),cPODLayout.GetName()))) ? (!IsDlgButtonChecked(IDC_POD_OPEN_TYPE_TEMPORARY) ||  CheckAccountPrivilege(PRIVILEGE_POD_TEMPORARYUSE)):FALSE);
  GetDlgItem(IDC_POD_OPEN_REMOVE) -> EnableWindow((IsDlgButtonChecked(IDC_POD_OPEN_TYPE_TEMPORARY) &&  FindLayout(cPODLayout)) ? CheckAccountPrivilege(PRIVILEGE_POD_TEMPORARYUSE):FALSE);
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODOpenDialog::OnSelchangeTitle()
{
  CPODLayout  cPODLayout;

  SendDlgItemMessage(IDC_POD_OPEN_DISPLAY,CB_SETCURSEL,(WPARAM) SendDlgItemMessage(IDC_POD_OPEN_DISPLAY,CB_GETCURSEL));
  GetDlgItem(IDC_POD_OPEN_SETTINGS) -> EnableWindow((FindLayout(cPODLayout) && (GetMode() != DISPLAY_MODE_REALTIME  ||  !GetParent() -> Find(MAKELONG(DISPLAY_TYPE_POD,GetType()),GetMode(),cPODLayout.GetName()))) ? (!IsDlgButtonChecked(IDC_POD_OPEN_TYPE_TEMPORARY) ||  CheckAccountPrivilege(PRIVILEGE_POD_TEMPORARYUSE)):FALSE);
  GetDlgItem(IDC_POD_OPEN_REMOVE) -> EnableWindow((IsDlgButtonChecked(IDC_POD_OPEN_TYPE_TEMPORARY)) ? CheckAccountPrivilege(PRIVILEGE_POD_TEMPORARYUSE):FALSE);
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODOpenDialog::OnTypeNormal()
{
  EnumLayouts();
  GetDlgItem(IDC_POD_OPEN_DISPLAY) -> SetFocus();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODOpenDialog::OnTypeTemporary()
{
  EnumLayouts();
  GetDlgItem(IDC_POD_OPEN_DISPLAY) -> SetFocus();
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODOpenDialog::OnRealtimeMode()
{
  CPODLayout  cPODLayout;

  GetDlgItem(IDC_POD_OPEN_SETTINGS) -> EnableWindow(((FindLayout(cPODLayout) ||  IsDlgButtonChecked(IDC_POD_OPEN_TYPE_TEMPORARY)) && (GetMode() != DISPLAY_MODE_REALTIME  ||  !GetParent() -> Find(MAKELONG(DISPLAY_TYPE_POD,GetType()),GetMode(),cPODLayout.GetName()))) ? (!IsDlgButtonChecked(IDC_POD_OPEN_TYPE_TEMPORARY) ||  CheckAccountPrivilege(PRIVILEGE_POD_TEMPORARYUSE)):FALSE);
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

void CPODOpenDialog::OnHistoryMode()
{
  INT  nPos;
  CString  szType;
  CString  szTitle;
  CPODLayout  cPODLayout;

  if (IsDlgButtonChecked(IDC_POD_OPEN_TYPE_NORMAL))
  { for (szTitle = (FindLayout(cPODLayout)) ? cPODLayout.GetTitle():STRING(IDS_WINDOW_UNKNOWNTITLE),szType.Format(STRING(IDS_PODOPENDIALOG_TYPENORMAL),(LPCTSTR) cPODLayout.GetName()),szType = ((nPos = (cPODLayout.GetName().IsEmpty()) ? szType.Find(SPACE):-1) >= 0) ? szType.Left(nPos):szType; IsDlgButtonChecked(IDC_POD_OPEN_MODE_HISTORY); )
    { ReportEvent((m_dlgRetrievals.Create(this,szTitle,szType) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE:SYSTEM_NOERROR);
      break;
    }
    for (GetDlgItem(IDC_POD_OPEN_SETTINGS) -> EnableWindow((FindLayout(cPODLayout) && (GetMode() != DISPLAY_MODE_REALTIME  ||  !GetParent() -> Find(MAKELONG(DISPLAY_TYPE_POD,GetType()),GetMode(),cPODLayout.GetName()))) ? TRUE:FALSE); SendDlgItemMessage(IDC_POD_OPEN_DISPLAY,CB_GETCOUNT) > 0; )
    { GetDlgItem(IDC_POD_OPEN_DISPLAY) -> SetFocus();
      break;
    }
    for ( ; IsDlgButtonChecked(IDC_POD_OPEN_MODE_REALTIME); )
    { GetDlgItem(IDC_POD_OPEN_MODE_REALTIME) -> SetFocus();
      break;
    }
    GetDlgItem(IDOK) -> EnableWindow(Check());
    return;
  }
  if (IsDlgButtonChecked(IDC_POD_OPEN_TYPE_TEMPORARY))
  { for (szTitle = (FindLayout(cPODLayout)) ? cPODLayout.GetTitle():STRING(IDS_WINDOW_UNKNOWNTITLE),szType = STRING(IDS_PODOPENDIALOG_TYPETEMPORARY); IsDlgButtonChecked(IDC_POD_OPEN_MODE_HISTORY); )
    { ReportEvent((m_dlgRetrievals.Create(this,szTitle,szType) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE:SYSTEM_NOERROR);
      break;
    }
    for (GetDlgItem(IDC_POD_OPEN_SETTINGS) -> EnableWindow((GetMode() != DISPLAY_MODE_REALTIME  ||  !GetParent() -> Find(MAKELONG(DISPLAY_TYPE_POD,GetType()),GetMode(),cPODLayout.GetName())) ? CheckAccountPrivilege(PRIVILEGE_POD_TEMPORARYUSE):FALSE); SendDlgItemMessage(IDC_POD_OPEN_DISPLAY,CB_GETCOUNT) >= 0; )
    { GetDlgItem(IDC_POD_OPEN_DISPLAY) -> SetFocus();
      break;
    }
    for ( ; IsDlgButtonChecked(IDC_POD_OPEN_MODE_REALTIME); )
    { GetDlgItem(IDC_POD_OPEN_MODE_REALTIME) -> SetFocus();
      break;
    }
    GetDlgItem(IDOK) -> EnableWindow(Check());
    return;
  }
  CheckDlgButton(IDC_POD_OPEN_MODE_REALTIME,TRUE);
  CheckDlgButton(IDC_POD_OPEN_MODE_HISTORY,FALSE);
  for (GetDlgItem(IDC_POD_OPEN_SETTINGS) -> EnableWindow(((FindLayout(cPODLayout) ||  IsDlgButtonChecked(IDC_POD_OPEN_TYPE_TEMPORARY)) && (GetMode() != DISPLAY_MODE_REALTIME  ||  !GetParent() -> Find(MAKELONG(DISPLAY_TYPE_POD,GetType()),GetMode(),cPODLayout.GetName()))) ? (!IsDlgButtonChecked(IDC_POD_OPEN_TYPE_TEMPORARY) ||  CheckAccountPrivilege(PRIVILEGE_POD_TEMPORARYUSE)):FALSE); IsDlgButtonChecked(IDC_POD_OPEN_TYPE_TEMPORARY) ||  SendDlgItemMessage(IDC_POD_OPEN_DISPLAY,CB_GETCOUNT) > 0; )
  { GetDlgItem(IDC_POD_OPEN_DISPLAY) -> SetFocus();
    break;
  }
  for ( ; IsDlgButtonChecked(IDC_POD_OPEN_MODE_REALTIME); )
  { GetDlgItem(IDC_POD_OPEN_MODE_REALTIME) -> SetFocus();
    break;
  }
  GetDlgItem(IDOK) -> EnableWindow(Check());
}

BOOL CPODOpenDialog::OnCloseSettingsDialog(UINT nCode)
{
  if (nCode == IDOK)
  { if (m_dlgSettings.IsLayoutModified()) 
    { m_dlgSettings.GetLayout(m_cLayout);
      m_dlgSettings.GetLayoutTitleFonts(&m_fntLayoutTitle[0],&m_fntLayoutTitle[1],&m_fntLayoutTitle[2]);
      m_dlgSettings.GetLayoutItemsFonts(&m_fntLayoutItems[0],&m_fntLayoutItems[1],&m_fntLayoutItems[2]);
      m_dlgSettings.GetLayoutToolTipMode(m_bLayoutToolTips);
    }
    if (m_dlgSettings.IsFilteringModified())
    { m_dlgSettings.GetFilterMode(m_nFilterMode);
      m_dlgSettings.GetFilterLimit(m_nFilterLimit);
      m_dlgSettings.GetFilterDigits(m_nFilterDigits);
      m_dlgSettings.GetFilterStatus(m_nFilterStatus);
      m_dlgSettings.GetFilterRange(m_tFilterRange[0][0],m_tFilterRange[0][1]);
      m_dlgSettings.GetFilterDailyRange(m_tFilterDailyRange[0],m_tFilterDailyRange[1]);
      m_dlgSettings.GetFilterPeriodicalRange(m_tFilterRange[1][0],m_tFilterPeriodical,m_tFilterRange[1][1]);
      m_dlgSettings.GetFilterColors(m_nFilterColors);
    }
    if (m_dlgSettings.IsRetrievingModified()) m_dlgSettings.GetRetrieveFileName(m_szRetrieveFileName);
    if (m_dlgSettings.IsPrintingModified()) m_dlgSettings.GetPrintJobs(m_pPrintJobs);
  }
  return TRUE;
}

BOOL CPODOpenDialog::OnCloseRetrieveDialog(UINT nCode)
{
  CPODLayout  cPODLayout;

  if (nCode == IDOK)
  { m_dlgRetrievals.GetMode(m_nRetrieveMode);
    m_dlgRetrievals.GetSpeed(m_nRetrieveSpeed);
    m_dlgRetrievals.GetInterval(m_tRetrieveInterval);
    m_dlgRetrievals.GetStartTime(m_tRetrieveStartTime);
    m_dlgRetrievals.GetStopTime(m_tRetrieveStopTime);
  }
  if (nCode != IDOK  ||  !m_nRetrieveMode)
  { CheckDlgButton(IDC_POD_OPEN_MODE_REALTIME,TRUE);
    CheckDlgButton(IDC_POD_OPEN_MODE_HISTORY,FALSE);
  }
  return TRUE;
}

void CPODOpenDialog::OnOK()
{
  CPODWnd  *pPODWnd[2];
  CPODLayout  cPODLayout;
  CHourglassCursor  cCursor;

  if ((pPODWnd[0] = GetParent()))
  { if (GetMode() == DISPLAY_MODE_REALTIME)
    { if ((pPODWnd[1] = (FindLayout(cPODLayout)) ? pPODWnd[0] -> Find(MAKELONG(DISPLAY_TYPE_POD,GetType()),GetMode(),cPODLayout.GetName()):(CPODWnd *) NULL))
      { GetDisplayArea() -> ActivateDisplay(pPODWnd[1]);
        EndDialog(IDCANCEL);
        return;
      }
    }
    if (!pPODWnd[0] -> OnCloseOpenDialog(IDOK))
    { EndDialog(-1);
      return;
    }
  }
  else
  { EndDialog(-1);
    return;
  }
  CDisplayDialog::OnOK();
}

void CPODOpenDialog::OnCancel()
{
  CHourglassCursor  cCursor;

  GetParent() -> OnCloseOpenDialog(IDCANCEL);
  CDisplayDialog::OnCancel();
}

BOOL CPODOpenDialog::OnHelpInfo(HELPINFO *pHelpInfo)
{
  CHourglassCursor  cCursor;

  ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_PODOPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE:SYSTEM_NOERROR);
  return TRUE;
}

void CPODOpenDialog::OnHelp()
{
  CHourglassCursor  cCursor;

  ReportEvent((!ShowHelp(STRING(IDS_ONLINEHELP_PODOPENDIALOG_TOPIC))) ? SYSTEM_WARNING_ONLINEHELP_FAILURE:SYSTEM_NOERROR);
}


/////////////////////////////////////////////////////////////////////////////
// CPODRetrieveThread

IMPLEMENT_DYNCREATE(CPODRetrieveThread,CThread)

CPODRetrieveThread::CPODRetrieveThread() : CThread()
{
  m_nMode = 0;
  m_nSpeed = 0;
  m_tInterval = 0;
  m_tStartTime = 0;
  m_tStopTime = 0;
  m_pbFlag = (LPLONG) NULL;
  m_bInit[0] = (HANDLE) NULL;
  m_bInit[1] = (HANDLE) NULL;
  m_hAction[PODRETRIEVETHREAD_ACTION_STOP] = (HANDLE) NULL;
  m_hAction[PODRETRIEVETHREAD_ACTION_AUTOFORWARD] = (HANDLE) NULL;
  m_hAction[PODRETRIEVETHREAD_ACTION_AUTOBACKWARD] = (HANDLE) NULL;
  m_hAction[PODRETRIEVETHREAD_ACTION_MANUALFORWARD] = (HANDLE) NULL;
  m_hAction[PODRETRIEVETHREAD_ACTION_MANUALBACKWARD] = (HANDLE) NULL;
  m_hAction[PODRETRIEVETHREAD_ACTION_PSEUDOREALTIME] = (HANDLE) NULL;
}

BOOL CPODRetrieveThread::Start(CPODWnd *pParentWnd,HANDLE bInit,HANDLE bContinue,LPCTSTR pszFileName,UINT nMode,UINT nSpeed,CONST CTimeSpan &tInterval,CONST CTimeKey &tStartTime,CONST CTimeKey &tStopTime,LONG *pbFlag,HANDLE bRetrieveStop,HANDLE bRetrieveAutoForward,HANDLE bRetrieveAutoBackward,HANDLE bRetrieveManualForward,HANDLE bRetrieveManualBackward,HANDLE bRetrievePseudoRealtime)
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
  m_hAction[PODRETRIEVETHREAD_ACTION_STOP] = bRetrieveStop;
  m_hAction[PODRETRIEVETHREAD_ACTION_AUTOFORWARD] = bRetrieveAutoForward;
  m_hAction[PODRETRIEVETHREAD_ACTION_AUTOBACKWARD] = bRetrieveAutoBackward;
  m_hAction[PODRETRIEVETHREAD_ACTION_MANUALFORWARD] = bRetrieveManualForward;
  m_hAction[PODRETRIEVETHREAD_ACTION_MANUALBACKWARD] = bRetrieveManualBackward;
  m_hAction[PODRETRIEVETHREAD_ACTION_PSEUDOREALTIME] = bRetrievePseudoRealtime;
  return((ResetEvent(bInit)) ? CreateThread(pParentWnd,THREAD_PRIORITY_BELOW_NORMAL):FALSE);
}

BOOL CPODRetrieveThread::Stop()
{
  return((DestroyThread() >= 0) ? TRUE:FALSE);
}

BOOL CPODRetrieveThread::InitializeTMData(CTMParameters &pTMParameters,BOOL bBadData)
{
  return m_cTMEnvironment.Initialize(pTMParameters,bBadData);
}

int CPODRetrieveThread::Run()
{
  UINT  nAction;
  UINT  nResult;
  DWORD  dwResult;
  TIMETAG  tTime;
  CTimeKey  tTimeKey;
  CTimeTag  tTimeTag[2];
  CPODWnd  *pPODWnd=(CPODWnd *) GetThreadInfo();

  StartRetrieving();
  if (m_cTMEnvironment.Create(GetDatabase()))
  { if (m_cTMProcessEngine.Open(GetDatabase(),GetAccountSpacecraftName(),GetRetrieveFileName(),&m_cTMEnvironment))
    { for (BeginWaitCursor(),pPODWnd -> SetRetrieveMode((m_nMode = (m_nMode & (POD_RETRIEVE_AUTOBACKWARD | POD_RETRIEVE_MANUALBACKWARD)) ? ((m_nMode & ~(POD_RETRIEVE_AUTOBACKWARD | POD_RETRIEVE_MANUALBACKWARD | POD_RETRIEVE_STOPPED | POD_RETRIEVE_RELATIVE)) | POD_RETRIEVE_MANUALFORWARD):(m_nMode & ~(POD_RETRIEVE_STOPPED | POD_RETRIEVE_RELATIVE)))),pPODWnd -> Reset(&m_cTMEnvironment),SignalObjectAndWait(m_bInit[0],m_bInit[1],INFINITE,FALSE),nResult = m_cTMProcessEngine.ProcessTMData(GetDatabase(),&m_cTMEnvironment,(tTimeKey=GetRetrieveStartTime())),nAction = 0; (dwResult = Wait(0)) == WAIT_TIMEOUT  &&  !pPODWnd -> IsInitialized(); )
      { SwitchToThread();
        continue;
      }
      for ( ; dwResult == WAIT_TIMEOUT; BeginWaitCursor())
      { if ((GetRetrieveMode() & POD_RETRIEVE_AUTOFORWARD) &&  !(GetRetrieveMode() & POD_RETRIEVE_STOPPED))
        { for ( ; (nResult & HISTORYFILE_SUCCESS) &&  !(GetRetrieveMode() & POD_RETRIEVE_RELATIVE) && (dwResult = Wait(m_hAction,sizeof(m_hAction)/sizeof(HANDLE),FALSE,0,FALSE)) == WAIT_TIMEOUT  && ((!(GetRetrieveMode() & POD_RETRIEVE_EXACTTIME) &&  !pPODWnd -> Update(tTimeKey,&m_cTMEnvironment,nResult)) || ((GetRetrieveMode() & POD_RETRIEVE_EXACTTIME) &&  tTimeKey < GetRetrieveStartTime())); )
          { if (!((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(),&m_cTMEnvironment,tTimeKey,0)) & HISTORYFILE_SUCCESS)) break;
            if (!(nResult & HISTORYFILE_TMUNIT) &&  !(nResult & HISTORYFILE_TMPARAMETERS))
            { if (GetRetrieveMode() & POD_RETRIEVE_STOPBYREALTIME)
              { pPODWnd -> SetMode(DISPLAY_MODE_REALTIME);
                pPODWnd -> ProcessRealtimeData();
                pPODWnd -> UpdateBars();
                break;
              }
              ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
              pPODWnd -> SetRetrieveMode(pPODWnd -> GetRetrieveMode() | POD_RETRIEVE_STOPPED);
              pPODWnd -> UpdateBars();
              break;
            }
            if ((GetRetrieveMode() & POD_RETRIEVE_STOPBYTIME) &&  GetRetrieveStopTime() < tTimeKey)
            { pPODWnd -> SetRetrieveMode(pPODWnd -> GetRetrieveMode() | POD_RETRIEVE_STOPPED);
              pPODWnd -> UpdateBars();
              break;
            }
          }
          EndWaitCursor();
          if (pPODWnd -> GetMode() != DISPLAY_MODE_REALTIME)
          { if ((((nResult & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS))) || (GetRetrieveMode() & POD_RETRIEVE_RELATIVE)) && (!(GetRetrieveMode() & POD_RETRIEVE_STOPBYTIME) ||  GetRetrieveStopTime() >= tTimeKey) &&  dwResult == WAIT_TIMEOUT)
            { if ((!(GetRetrieveMode() & POD_RETRIEVE_RELATIVE) && (!(GetRetrieveMode() & POD_RETRIEVE_EXACTTIME) ||  pPODWnd -> Update(tTimeKey,&m_cTMEnvironment,(nResult = (nResult | HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS) & ~HISTORYFILE_TMUNIT) & (HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS)) ||  TRUE)) || (GetRetrieveMode() & POD_RETRIEVE_RELATIVE))
              { for ( ; (dwResult = Wait(m_hAction,sizeof(m_hAction)/sizeof(HANDLE),FALSE,10*(10-GetRetrieveSpeed())*(10-GetRetrieveSpeed()))) == WAIT_TIMEOUT; )
                { if (((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(),&m_cTMEnvironment,tTimeKey,GetRetrieveInterval())) & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)))
                  { if (!(GetRetrieveMode() & POD_RETRIEVE_STOPBYTIME) ||  GetRetrieveStopTime() >= tTimeKey)
                    { pPODWnd -> Update(tTimeKey,&m_cTMEnvironment,nResult);                     
                      continue;
                    }
                  }
                  if (nResult & HISTORYFILE_SUCCESS)
                  { if (GetRetrieveMode() & POD_RETRIEVE_STOPBYREALTIME)
                    { pPODWnd -> SetMode(DISPLAY_MODE_REALTIME);
                      pPODWnd -> ProcessRealtimeData();
                      pPODWnd -> UpdateBars();
                      break;
                    }
                    ReportEvent((GetRetrieveMode() & POD_RETRIEVE_STOPBYEND) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING:USER_NOERROR);
                    pPODWnd -> SetRetrieveMode(pPODWnd -> GetRetrieveMode() | POD_RETRIEVE_STOPPED);
                    pPODWnd -> UpdateBars();
                  }
                  break;
                }
              }
            }
            if (!(nResult & HISTORYFILE_SUCCESS))
            { ReportEvent((nResult == HISTORYFILE_DATA_NONE) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING:((nResult == HISTORYFILE_OPEN_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_OPEN_FAILURE:((nResult == HISTORYFILE_WRITE_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_WRITE_FAILURE:((nResult == HISTORYFILE_READ_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_READ_FAILURE:((nResult == HISTORYFILE_ERROR) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE:SYSTEM_NOERROR)))));
              pPODWnd -> SetRetrieveMode(pPODWnd -> GetRetrieveMode() | POD_RETRIEVE_STOPPED);
              pPODWnd -> Reset(&m_cTMEnvironment);
              pPODWnd -> UpdateBars();
              break;
            }
          }
          if (pPODWnd -> GetMode() == DISPLAY_MODE_REALTIME) break;
        }
        if ((GetRetrieveMode() & POD_RETRIEVE_AUTOBACKWARD) &&  !(GetRetrieveMode() & POD_RETRIEVE_STOPPED))
        { if ((nResult & HISTORYFILE_SUCCESS) && (GetRetrieveMode() & POD_RETRIEVE_RELATIVE) &&  dwResult == WAIT_TIMEOUT)
          { for (EndWaitCursor(); (dwResult = Wait(m_hAction,sizeof(m_hAction)/sizeof(HANDLE),FALSE,10*(10-GetRetrieveSpeed())*(10-GetRetrieveSpeed()))) == WAIT_TIMEOUT; )
            { if (((nResult = m_cTMProcessEngine.RewindTMData(GetDatabase(),&m_cTMEnvironment,tTimeKey,GetRetrieveInterval())) & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)))
              { pPODWnd -> Update(tTimeKey,&m_cTMEnvironment,nResult);
                continue;
              }
              break;
            }
          }
          if (nResult & HISTORYFILE_SUCCESS)
          { if (!(nResult & HISTORYFILE_TMUNIT) &&  !(nResult & HISTORYFILE_TMPARAMETERS))
            { ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
              pPODWnd -> Update(tTimeKey,&m_cTMEnvironment,nResult);
              pPODWnd -> SetRetrieveMode(pPODWnd -> GetRetrieveMode() | POD_RETRIEVE_STOPPED);
              pPODWnd -> UpdateBars();
            }
          }
          else
          { ReportEvent((nResult == HISTORYFILE_DATA_NONE) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING:((nResult == HISTORYFILE_OPEN_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_OPEN_FAILURE:((nResult == HISTORYFILE_WRITE_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_WRITE_FAILURE:((nResult == HISTORYFILE_READ_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_READ_FAILURE:((nResult == HISTORYFILE_ERROR) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE:SYSTEM_NOERROR)))));
            pPODWnd -> SetRetrieveMode(pPODWnd -> GetRetrieveMode() | POD_RETRIEVE_STOPPED);
            pPODWnd -> Reset(&m_cTMEnvironment);
            pPODWnd -> UpdateBars();
            EndWaitCursor();
            break;
          }
          EndWaitCursor();
        }
        if ((GetRetrieveMode() & POD_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & POD_RETRIEVE_STOPPED))
        { for ( ; (nResult & HISTORYFILE_SUCCESS) &&  !(GetRetrieveMode() & POD_RETRIEVE_RELATIVE) && (dwResult = Wait(m_hAction,sizeof(m_hAction)/sizeof(HANDLE),FALSE,0,FALSE)) == WAIT_TIMEOUT  && ((!(GetRetrieveMode() & POD_RETRIEVE_EXACTTIME) &&  !pPODWnd -> Update(tTimeKey,&m_cTMEnvironment,nResult)) || ((GetRetrieveMode() & POD_RETRIEVE_EXACTTIME) &&  tTimeKey < GetRetrieveStartTime())); )
          { if (!((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(),&m_cTMEnvironment,tTimeKey,0)) & HISTORYFILE_SUCCESS)) break;
            if (!(nResult & HISTORYFILE_TMUNIT) &&  !(nResult & HISTORYFILE_TMPARAMETERS))
            { if (GetRetrieveMode() & POD_RETRIEVE_STOPBYREALTIME)
              { pPODWnd -> SetMode(DISPLAY_MODE_REALTIME);
                pPODWnd -> ProcessRealtimeData();
                pPODWnd -> UpdateBars();
                break;
              }
              ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
              pPODWnd -> SetRetrieveMode(pPODWnd -> GetRetrieveMode() | POD_RETRIEVE_STOPPED);
              pPODWnd -> UpdateBars();
              break;
            }
          }
          EndWaitCursor();
          if (pPODWnd -> GetMode() != DISPLAY_MODE_REALTIME)
          { if ((((nResult & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS))) || (GetRetrieveMode() & POD_RETRIEVE_RELATIVE)) &&  dwResult == WAIT_TIMEOUT)
            { if ((!(GetRetrieveMode() & POD_RETRIEVE_RELATIVE) && (!(GetRetrieveMode() & POD_RETRIEVE_EXACTTIME) ||  pPODWnd -> Update(tTimeKey,&m_cTMEnvironment,(nResult = (nResult | HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS) & ~HISTORYFILE_TMUNIT) & (HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS)) ||  TRUE)) || (GetRetrieveMode() & POD_RETRIEVE_RELATIVE))
              { for ( ; (dwResult = (!(GetRetrieveMode() & POD_RETRIEVE_RELATIVE) ||  nAction != PODRETRIEVETHREAD_ACTION_MANUALFORWARD) ? Wait(m_hAction,sizeof(m_hAction)/sizeof(HANDLE),FALSE,INFINITE):(WAIT_OBJECT_0+nAction+1)) == WAIT_OBJECT_0+PODRETRIEVETHREAD_ACTION_MANUALFORWARD+1; EndWaitCursor())
                { for (BeginWaitCursor(TRUE); (dwResult = Wait(m_hAction,sizeof(m_hAction)/sizeof(HANDLE),FALSE,0,FALSE)) == WAIT_TIMEOUT; )
                  { if (((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(),&m_cTMEnvironment,tTimeKey,GetRetrieveInterval())) & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)))
                    { if (pPODWnd -> Update(tTimeKey,&m_cTMEnvironment,nResult)) break;
                      continue;
                    }
                    if (nResult & HISTORYFILE_SUCCESS)
                    { if (!(nResult & HISTORYFILE_TMUNIT) &&  !(nResult & HISTORYFILE_TMPARAMETERS))
                      { if (GetRetrieveMode() & POD_RETRIEVE_STOPBYREALTIME)
                        { pPODWnd -> SetMode(DISPLAY_MODE_REALTIME);
                          pPODWnd -> ProcessRealtimeData();
                          pPODWnd -> UpdateBars();
                          break;
                        }
                        ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
                        pPODWnd -> SetRetrieveMode(pPODWnd -> GetRetrieveMode() | POD_RETRIEVE_STOPPED);
                        pPODWnd -> UpdateBars();
                      }
                    }
                    break;
                  }
                  if (!(nResult & HISTORYFILE_SUCCESS) || (!(nResult & HISTORYFILE_TMUNIT) &&  !(nResult & HISTORYFILE_TMPARAMETERS)) ||  pPODWnd -> GetMode() == DISPLAY_MODE_REALTIME  ||  dwResult == WAIT_OBJECT_0)
                  { EndWaitCursor();
                    break;
                  }
                  nAction = 0;
                }
              }
            }
            if (!(nResult & HISTORYFILE_SUCCESS))
            { ReportEvent((nResult == HISTORYFILE_DATA_NONE) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING:((nResult == HISTORYFILE_OPEN_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_OPEN_FAILURE:((nResult == HISTORYFILE_WRITE_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_WRITE_FAILURE:((nResult == HISTORYFILE_READ_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_READ_FAILURE:((nResult == HISTORYFILE_ERROR) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE:SYSTEM_NOERROR)))));
              pPODWnd -> SetRetrieveMode(pPODWnd -> GetRetrieveMode() | POD_RETRIEVE_STOPPED);
              pPODWnd -> Reset(&m_cTMEnvironment);
              pPODWnd -> UpdateBars();
              break;
            }
          }
          if (pPODWnd -> GetMode() == DISPLAY_MODE_REALTIME) break;
        }
        if ((GetRetrieveMode() & POD_RETRIEVE_MANUALBACKWARD) &&  !(GetRetrieveMode() & POD_RETRIEVE_STOPPED))
        { if ((nResult & HISTORYFILE_SUCCESS) && (GetRetrieveMode() & POD_RETRIEVE_RELATIVE) &&  dwResult == WAIT_TIMEOUT)
          { for (EndWaitCursor(); (dwResult = (nAction != PODRETRIEVETHREAD_ACTION_MANUALBACKWARD) ? Wait(m_hAction,sizeof(m_hAction)/sizeof(HANDLE),FALSE,INFINITE):(WAIT_OBJECT_0+nAction+1)) == WAIT_OBJECT_0+PODRETRIEVETHREAD_ACTION_MANUALBACKWARD+1; EndWaitCursor())
            { for (BeginWaitCursor(TRUE); (dwResult = Wait(m_hAction,sizeof(m_hAction)/sizeof(HANDLE),FALSE,0,FALSE)) == WAIT_TIMEOUT; )
              { if (((nResult = m_cTMProcessEngine.RewindTMData(GetDatabase(),&m_cTMEnvironment,tTimeKey,GetRetrieveInterval())) & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)))
                { if (pPODWnd -> Update(tTimeKey,&m_cTMEnvironment,nResult)) break;
                  continue;
                }
                if (nResult & HISTORYFILE_SUCCESS)
                { if (!(nResult & HISTORYFILE_TMUNIT) &&  !(nResult & HISTORYFILE_TMPARAMETERS))
                  { ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
                    pPODWnd -> Update(tTimeKey,&m_cTMEnvironment,nResult);
                    pPODWnd -> SetRetrieveMode(pPODWnd -> GetRetrieveMode() | POD_RETRIEVE_STOPPED);
                    pPODWnd -> UpdateBars();
                  }
                }
                break;
              }
              if (!(nResult & HISTORYFILE_SUCCESS) || (!(nResult & HISTORYFILE_TMUNIT) && !(nResult & HISTORYFILE_TMPARAMETERS)) ||  dwResult == WAIT_OBJECT_0)
              { EndWaitCursor();
                break;
              }
              nAction = 0;
            }
          }
          if (!(nResult & HISTORYFILE_SUCCESS))
          { ReportEvent((nResult == HISTORYFILE_DATA_NONE) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING:((nResult == HISTORYFILE_OPEN_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_OPEN_FAILURE:((nResult == HISTORYFILE_WRITE_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_WRITE_FAILURE:((nResult == HISTORYFILE_READ_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_READ_FAILURE:((nResult == HISTORYFILE_ERROR) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE:SYSTEM_NOERROR)))));
            pPODWnd -> SetRetrieveMode(pPODWnd -> GetRetrieveMode() | POD_RETRIEVE_STOPPED);
            pPODWnd -> Reset(&m_cTMEnvironment);
            pPODWnd -> UpdateBars();
            EndWaitCursor();
            break;
          }
          EndWaitCursor();
        }
        if ((GetRetrieveMode() & POD_RETRIEVE_PSEUDOREALTIME) &&  !(GetRetrieveMode() & POD_RETRIEVE_STOPPED))
        { for ( ; (nResult & HISTORYFILE_SUCCESS) &&  !(GetRetrieveMode() & POD_RETRIEVE_RELATIVE) && (dwResult = Wait(m_hAction,sizeof(m_hAction)/sizeof(HANDLE),FALSE,0,FALSE)) == WAIT_TIMEOUT  && ((!(GetRetrieveMode() & POD_RETRIEVE_EXACTTIME) &&  !pPODWnd -> Update(tTimeKey,&m_cTMEnvironment,nResult)) || ((GetRetrieveMode() & POD_RETRIEVE_EXACTTIME) &&  tTimeKey < GetRetrieveStartTime())); )
          { if (!((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(),&m_cTMEnvironment,tTimeKey,0)) & HISTORYFILE_SUCCESS)) break;
            if (!(nResult & HISTORYFILE_TMUNIT) &&  !(nResult & HISTORYFILE_TMPARAMETERS))
            { if (GetRetrieveMode() & POD_RETRIEVE_STOPBYREALTIME)
              { pPODWnd -> SetMode(DISPLAY_MODE_REALTIME);
                pPODWnd -> ProcessRealtimeData();
                pPODWnd -> UpdateBars();
                break;
              }
              ReportEvent(USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING);
              pPODWnd -> SetRetrieveMode(pPODWnd -> GetRetrieveMode() | POD_RETRIEVE_STOPPED);
              pPODWnd -> UpdateBars();
              break;
            }
            if ((GetRetrieveMode() & POD_RETRIEVE_STOPBYTIME) &&  GetRetrieveStopTime() < tTimeKey)
            { pPODWnd -> SetRetrieveMode(pPODWnd -> GetRetrieveMode() | POD_RETRIEVE_STOPPED);
              pPODWnd -> UpdateBars();
              break;
            }
          }
          EndWaitCursor();
          if (pPODWnd -> GetMode() != DISPLAY_MODE_REALTIME)
          { if ((((nResult & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS))) || (GetRetrieveMode() & POD_RETRIEVE_RELATIVE)) && (!(GetRetrieveMode() & POD_RETRIEVE_STOPBYTIME) ||  GetRetrieveStopTime() >= tTimeKey) &&  dwResult == WAIT_TIMEOUT)
            { if ((!(GetRetrieveMode() & POD_RETRIEVE_RELATIVE) && (!(GetRetrieveMode() & POD_RETRIEVE_EXACTTIME) ||  pPODWnd -> Update(tTimeKey,&m_cTMEnvironment,(nResult = (nResult | HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS) & ~HISTORYFILE_TMUNIT) & (HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS)) ||  TRUE)) || (GetRetrieveMode() & POD_RETRIEVE_RELATIVE))
              { for (tTimeTag[0] = ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)) ? ((nResult & HISTORYFILE_TMUNIT) ? m_cTMEnvironment.GetTMUnit() -> GetTimeTag():CTimeTag(tTimeKey)):CTimeTag(tTimeKey),tTimeTag[1] = CTimeTag(),tTime = CTimeTag().GetTime(); (dwResult = Wait(m_hAction,sizeof(m_hAction)/sizeof(HANDLE),FALSE,0,FALSE)) == WAIT_TIMEOUT; tTime = CTimeTag().GetTime())
                { if (((nResult = m_cTMProcessEngine.ReplayTMData(GetDatabase(),&m_cTMEnvironment,tTimeKey,0)) & HISTORYFILE_SUCCESS) && ((nResult & HISTORYFILE_TMUNIT) || (nResult & HISTORYFILE_TMPARAMETERS)))
                  { if ((dwResult = Wait(m_hAction,sizeof(m_hAction)/sizeof(HANDLE),FALSE,(((nResult & HISTORYFILE_TMUNIT) &&  tTimeTag[1].GetTime()-tTimeTag[0].GetTime()+m_cTMEnvironment.GetTMUnit() -> GetTimeTag().GetTime() > tTime) || ((nResult & HISTORYFILE_TMPARAMETERS) &&  tTimeTag[1].GetTime()-tTimeTag[0].GetTime()+CTimeTag(tTimeKey).GetTime() > tTime)) ? ((nResult & HISTORYFILE_TMUNIT) ? (DWORD) ((tTimeTag[1].GetTime()-tTimeTag[0].GetTime()+m_cTMEnvironment.GetTMUnit() -> GetTimeTag().GetTime()-tTime)/1000):(DWORD) ((tTimeTag[1].GetTime()-tTimeTag[0].GetTime()+CTimeTag(tTimeKey).GetTime()-tTime)/1000)):0)) != WAIT_TIMEOUT) break;
                    if ((!(GetRetrieveMode() & POD_RETRIEVE_STOPBYTIME) ||  GetRetrieveStopTime() >= tTimeKey) && ((nResult & HISTORYFILE_SYNCHRONIZE) ||  !tTimeTag[0].GetTime()))
                    { tTimeTag[0] = (nResult & HISTORYFILE_TMUNIT) ? m_cTMEnvironment.GetTMUnit() -> GetTimeTag():CTimeTag(tTimeKey);
                      tTimeTag[1] = tTime = CTimeTag().GetTime();
                    }
                    if (!(GetRetrieveMode() & POD_RETRIEVE_STOPBYTIME) ||  GetRetrieveStopTime() >= tTimeKey)
                    { pPODWnd -> Update(tTimeKey,&m_cTMEnvironment,nResult);
                      continue;
                    }
                  }
                  if (nResult & HISTORYFILE_SUCCESS)
                  { if (GetRetrieveMode() & POD_RETRIEVE_STOPBYREALTIME)
                    { pPODWnd -> SetMode(DISPLAY_MODE_REALTIME);
                      pPODWnd -> ProcessRealtimeData();
                      pPODWnd -> UpdateBars();
                      break;
                    }
                    ReportEvent((GetRetrieveMode() & POD_RETRIEVE_STOPBYEND) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING:USER_NOERROR);
                    pPODWnd -> SetRetrieveMode(pPODWnd -> GetRetrieveMode() | POD_RETRIEVE_STOPPED);
                    pPODWnd -> UpdateBars();
                  }
                  break;
                }
              }
            }
            if (!(nResult & HISTORYFILE_SUCCESS))
            { ReportEvent((nResult == HISTORYFILE_DATA_NONE) ? USER_INFORMATIONAL_TELEMETRYHISTORYFILE_READ_NOTHING:((nResult == HISTORYFILE_OPEN_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_OPEN_FAILURE:((nResult == HISTORYFILE_WRITE_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_WRITE_FAILURE:((nResult == HISTORYFILE_READ_FAILURE) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_READ_FAILURE:((nResult == HISTORYFILE_ERROR) ? SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE:SYSTEM_NOERROR)))));
              pPODWnd -> SetRetrieveMode(pPODWnd -> GetRetrieveMode() | POD_RETRIEVE_STOPPED);
              pPODWnd -> Reset(&m_cTMEnvironment);
              pPODWnd -> UpdateBars();
              break;
            }
          }
          if (pPODWnd -> GetMode() == DISPLAY_MODE_REALTIME) break;
        }
        if ((GetRetrieveMode() & POD_RETRIEVE_AUTOFORWARD) || (GetRetrieveMode() & POD_RETRIEVE_AUTOBACKWARD) || (GetRetrieveMode() & POD_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & POD_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & POD_RETRIEVE_PSEUDOREALTIME))
        { while ((dwResult = ((dwResult < WAIT_OBJECT_0+PODRETRIEVETHREAD_ACTION_AUTOFORWARD+1  ||  dwResult > WAIT_OBJECT_0+PODRETRIEVETHREAD_ACTION_PSEUDOREALTIME+1) &&  dwResult != WAIT_OBJECT_0) ? Wait(m_hAction,PODRETRIEVETHREAD_ACTION_TYPES,FALSE,INFINITE,FALSE):dwResult) == WAIT_OBJECT_0+PODRETRIEVETHREAD_ACTION_STOP+1)
          { m_nMode = (GetRetrieveMode() & (POD_RETRIEVE_STOPBYTIME | POD_RETRIEVE_STOPBYEND | POD_RETRIEVE_STOPBYREALTIME)) | POD_RETRIEVE_STOPPED | POD_RETRIEVE_RELATIVE;
            m_nMode |= ((GetRetrieveMode() & (POD_RETRIEVE_STOPBYTIME | POD_RETRIEVE_STOPBYEND | POD_RETRIEVE_STOPBYREALTIME)) == 0) ? POD_RETRIEVE_STOPBYREALTIME:0;
            pPODWnd -> SetRetrieveMode(m_nMode);
            pPODWnd -> UpdateBars();
          }
          if (dwResult == WAIT_OBJECT_0+PODRETRIEVETHREAD_ACTION_AUTOFORWARD+1)
          { m_nMode = (GetRetrieveMode() & (POD_RETRIEVE_STOPBYTIME | POD_RETRIEVE_STOPBYEND | POD_RETRIEVE_STOPBYREALTIME)) | POD_RETRIEVE_AUTOFORWARD | POD_RETRIEVE_RELATIVE;
            m_nMode |= ((GetRetrieveMode() & (POD_RETRIEVE_STOPBYTIME | POD_RETRIEVE_STOPBYEND | POD_RETRIEVE_STOPBYREALTIME)) == 0) ? POD_RETRIEVE_STOPBYREALTIME:0;
            nAction = PODRETRIEVETHREAD_ACTION_AUTOFORWARD;
            pPODWnd -> SetRetrieveMode(m_nMode);
            pPODWnd -> UpdateBars();
            dwResult = WAIT_TIMEOUT;
            continue;
          }
          if (dwResult == WAIT_OBJECT_0+PODRETRIEVETHREAD_ACTION_AUTOBACKWARD+1)
          { m_nMode = (GetRetrieveMode() & (POD_RETRIEVE_STOPBYTIME | POD_RETRIEVE_STOPBYEND | POD_RETRIEVE_STOPBYREALTIME)) | POD_RETRIEVE_AUTOBACKWARD | POD_RETRIEVE_RELATIVE;
            m_nMode |= ((GetRetrieveMode() & (POD_RETRIEVE_STOPBYTIME | POD_RETRIEVE_STOPBYEND | POD_RETRIEVE_STOPBYREALTIME)) == 0) ? POD_RETRIEVE_STOPBYEND:0;
            nAction = PODRETRIEVETHREAD_ACTION_AUTOBACKWARD;
            pPODWnd -> SetRetrieveMode(m_nMode);
            pPODWnd -> UpdateBars();
            dwResult = WAIT_TIMEOUT;
            continue;
          }
          if (dwResult == WAIT_OBJECT_0+PODRETRIEVETHREAD_ACTION_MANUALFORWARD+1)
          { m_nMode = (GetRetrieveMode() & (POD_RETRIEVE_STOPBYTIME | POD_RETRIEVE_STOPBYEND | POD_RETRIEVE_STOPBYREALTIME)) | POD_RETRIEVE_MANUALFORWARD | POD_RETRIEVE_RELATIVE;
            nAction = PODRETRIEVETHREAD_ACTION_MANUALFORWARD;
            pPODWnd -> SetRetrieveMode(m_nMode);
            pPODWnd -> UpdateBars();
            dwResult = WAIT_TIMEOUT;
            continue;
          }
          if (dwResult == WAIT_OBJECT_0+PODRETRIEVETHREAD_ACTION_MANUALBACKWARD+1)
          { m_nMode = (GetRetrieveMode() & (POD_RETRIEVE_STOPBYTIME | POD_RETRIEVE_STOPBYEND | POD_RETRIEVE_STOPBYREALTIME)) | POD_RETRIEVE_MANUALBACKWARD | POD_RETRIEVE_RELATIVE;
            nAction = PODRETRIEVETHREAD_ACTION_MANUALBACKWARD;
            pPODWnd -> SetRetrieveMode(m_nMode);
            pPODWnd -> UpdateBars();
            dwResult = WAIT_TIMEOUT;
            continue;
          }
          if (dwResult == WAIT_OBJECT_0+PODRETRIEVETHREAD_ACTION_PSEUDOREALTIME+1)
          { m_nMode = (GetRetrieveMode() & (POD_RETRIEVE_STOPBYTIME | POD_RETRIEVE_STOPBYEND | POD_RETRIEVE_STOPBYREALTIME)) | POD_RETRIEVE_PSEUDOREALTIME | POD_RETRIEVE_RELATIVE;
            m_nMode |= ((GetRetrieveMode() & (POD_RETRIEVE_STOPBYTIME | POD_RETRIEVE_STOPBYEND | POD_RETRIEVE_STOPBYREALTIME)) == 0) ? POD_RETRIEVE_STOPBYREALTIME:0;
            nAction = PODRETRIEVETHREAD_ACTION_PSEUDOREALTIME;
            pPODWnd -> SetRetrieveMode(m_nMode);
            pPODWnd -> UpdateBars();
            dwResult = WAIT_TIMEOUT;
            continue;
          }
        }
        break;
      }
      m_cTMProcessEngine.Close();
    }
    else
    { SignalObjectAndWait(m_bInit[0],m_bInit[1],INFINITE,FALSE);
      ReportEvent(SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE);
    }
    m_cTMEnvironment.Destroy();
  }
  else
  { SignalObjectAndWait(m_bInit[0],m_bInit[1],INFINITE,FALSE);
    ReportEvent(SYSTEM_WARNING_TELEMETRYHISTORYFILE_FAILURE);
  }
  StopRetrieving();
  EndWaitCursor();
  return 0;
}

VOID CPODRetrieveThread::StartRetrieving()
{
  InterlockedExchange(m_pbFlag,TRUE);
}

VOID CPODRetrieveThread::StopRetrieving()
{
  InterlockedExchange(m_pbFlag,FALSE);
}

UINT CPODRetrieveThread::GetRetrieveMode() CONST
{
  return((IsThreadActive()) ? m_nMode:0);
}

UINT CPODRetrieveThread::GetRetrieveSpeed() CONST
{
  return((IsThreadActive()) ? m_nSpeed:0);
}

CTimeSpan CPODRetrieveThread::GetRetrieveInterval() CONST
{
  return((IsThreadActive()) ? m_tInterval.GetTotalSeconds():0);
}

CTimeKey CPODRetrieveThread::GetRetrieveStartTime() CONST
{
  return((IsThreadActive()) ? m_tStartTime:0);
}

CTimeKey CPODRetrieveThread::GetRetrieveStopTime() CONST
{
  return((IsThreadActive()) ? m_tStopTime:0);
}

CString CPODRetrieveThread::GetRetrieveFileName() CONST
{
  return((IsThreadActive()) ? (LPCTSTR) m_szFileName:EMPTYSTRING);
}

VOID CPODRetrieveThread::BeginWaitCursor(BOOL bForced)
{
  POINT  ptCursor;
  CPODWnd  *pPODWnd;
  CHourglassCursor  cCursor;

  for (GetCursorPos(&ptCursor),InterlockedExchange(m_pbFlag,MAKELONG(TRUE,((m_nMode & POD_RETRIEVE_RELATIVE) != POD_RETRIEVE_RELATIVE  ||  bForced) ? TRUE:FALSE)),SetCursorPos(ptCursor.x,ptCursor.y); (pPODWnd = (CPODWnd *) GetThreadInfo()); )
  { pPODWnd -> UpdateBars();
    break;
  }
}

VOID CPODRetrieveThread::EndWaitCursor()
{
  POINT  ptCursor;
  CPODWnd  *pPODWnd;
  CHourglassCursor  cCursor;

  for (GetCursorPos(&ptCursor),InterlockedExchange(m_pbFlag,LOWORD(*m_pbFlag)),SetCursorPos(ptCursor.x,ptCursor.y); (pPODWnd = (CPODWnd *) GetThreadInfo()); )
  { pPODWnd -> UpdateBars();
    break;
  }
}

BEGIN_MESSAGE_MAP(CPODRetrieveThread, CThread)
	//{{AFX_MSG_MAP(CPODRetrieveThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPODRetrieveThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CPODPrintThread

IMPLEMENT_DYNCREATE(CPODPrintThread,CThread)

BOOL CPODPrintThread::Start(CPODWnd *pParentWnd)
{
  return CreateThread(pParentWnd);
}

BOOL CPODPrintThread::Stop()
{
  return((DestroyThread() >= 0) ? TRUE:FALSE);
}

BOOL CPODPrintThread::SetPrintJobs(CONST CPODPrintJobs &pPrintJobs)
{
  INT  nJob[2][2];
  INT  nJobs[2][2];
  CPODPrintJobInfo  *pJobInfo;
  CSingleLock  cLock(m_pCriticalSection,TRUE);

  for (nJob[0][0] = 0,nJobs[0][0] = (INT) pPrintJobs.GetSize(); nJob[0][0] < nJobs[0][0]; nJob[0][0]++)
  { for (nJob[0][1] = 0,nJobs[0][1] = (INT) m_pPrintJobs.GetSize(); nJob[0][1] < nJobs[0][1]; nJob[0][1]++)
    { if (pPrintJobs.GetAt(nJob[0][0]) -> GetName() == m_pPrintJobs.GetAt(nJob[0][1]) -> GetName())
      { if (!pPrintJobs.GetAt(nJob[0][0]) -> Compare(m_pPrintJobs.GetAt(nJob[0][1]))) m_pPrintJobs.GetAt(nJob[0][1]) -> Copy(pPrintJobs.GetAt(nJob[0][0]));
        break;
      }
    }
    if (nJob[0][1] == nJobs[0][1])
    { if ((pJobInfo = new CPODPrintJobInfo))
      { pJobInfo -> Copy(pPrintJobs.GetAt(nJob[0][0]));
        m_pPrintJobs.Add(pJobInfo);
        continue;
      }
      break;
    }
  }
  for (nJob[1][0] = 0,nJobs[1][0] = (INT) m_pPrintJobs.GetSize(); nJob[1][0] < nJobs[1][0]; nJob[1][0]++)
  { for (nJob[1][1] = 0,nJobs[1][1] = (INT) pPrintJobs.GetSize(); nJob[1][1] < nJobs[1][1]; nJob[1][1]++)
    { if (pPrintJobs.GetAt(nJob[1][1]) -> GetName() == m_pPrintJobs.GetAt(nJob[1][0]) -> GetName()) break;
      continue;
    }
    if (nJob[1][1] == nJobs[1][1])
    { delete m_pPrintJobs.GetAt(nJob[1][0]);
      m_pPrintJobs.RemoveAt(nJob[1][0]);
      nJobs[1][0]--;
      nJob[1][0]--;
    }
  }
  return((nJob[0][0] == nJobs[0][0] &&  nJob[1][0] == nJobs[1][0]) ? m_cEvent.SetEvent():FALSE);
}

BOOL CPODPrintThread::GetPrintJobs(CPODPrintJobs &pPrintJobs) CONST
{
  CByteArray  nPrintInfo;
  CSingleLock  cLock(m_pCriticalSection,TRUE);

  return(((m_pPrintJobs.GetSize() > 0  &&  pPrintJobs.Copy(&m_pPrintJobs)) ||  pPrintJobs.Unmap(nPrintInfo)) ? TRUE:FALSE);
}

int CPODPrintThread::Run()
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
  CPODPrintJobInfo  *pJobInfo[2];
  CPODWnd  *pPODWnd=(CPODWnd *) GetThreadInfo();

  for (dwJobResult = 0; Lock(); )
  { if (dwJobResult == WAIT_OBJECT_0+1  ||  !dwJobResult)
    { for (nJob = 0,nJobs = (INT) m_pPrintJobs.GetSize(); nJob < nJobs; nJob++)
      { if ((pJobInfo[0] = m_pPrintJobs.GetAt(nJob)) && (pJobInfo[0] -> GetPrintMode() & POD_PRINT_ACTIVE))
        { if (pJobInfo[0] -> GetPrintAtDailyTime(tJobDailyTime) ||  pJobInfo[0] -> GetPrintAtDailyTime(tJobDailyTime,nJobStopCount) ||  pJobInfo[0] -> GetPrintAtDailyTime(tJobDailyTime,tJobStopTime))
          { pJobInfo[0] -> SetPrintLastDailyTime(((tJobTime = CTime::GetCurrentTime().GetTime()).GetTime()%SECONDSPERDAY >= tJobDailyTime.GetTotalSeconds()) ? ((SECONDSPERDAY*(tJobTime.GetTime()/SECONDSPERDAY))+tJobDailyTime.GetTotalSeconds()):((SECONDSPERDAY*(tJobTime.GetTime()/SECONDSPERDAY-1))+tJobDailyTime.GetTotalSeconds()));
            continue;
          }
        }
      }
    }
    if ((pJobInfo[0] = ((tJobInterval = m_pPrintJobs.Schedule()) == 0) ? m_pPrintJobs.GetAt(0):(CPODPrintJobInfo *) NULL))
    { for (bJobPrint = pPODWnd -> Print(pJobInfo[0]); (pJobInfo[0] -> GetPrintMode() & POD_PRINT_CLEARCOMMENTS) &&  bJobPrint; )
      { for (nJob = 1,nJobs = (INT) m_pPrintJobs.GetSize(); nJob < nJobs; nJob++)
        { if ((pJobInfo[1] = m_pPrintJobs.GetAt(nJob)))
          { if (pJobInfo[0] -> GetName() == pJobInfo[1] -> GetName())
            { pJobInfo[1] -> SetPrintMode(pJobInfo[0] -> GetPrintMode() & ~POD_PRINT_CLEARCOMMENTS);
              pJobInfo[1] -> SetComments(EMPTYSTRING);
              break;
            }
          }
        }
        break;
      }
      ReportEvent((!bJobPrint) ? SYSTEM_WARNING_POD_PRINT_FAILURE:SYSTEM_NOERROR);
      m_pPrintJobs.RemoveAt(0);
      delete pJobInfo[0];
    }
    Unlock();
    if ((dwJobResult = Wait(m_cEvent,FALSE,(tJobInterval >= 0) ? (DWORD) (1000*min(tJobInterval,SECONDSPERDAY)):INFINITE)) != WAIT_TIMEOUT  &&  dwJobResult != WAIT_OBJECT_0+1) break;
  }
  return 0;
}

BEGIN_MESSAGE_MAP(CPODPrintThread, CThread)
	//{{AFX_MSG_MAP(CPODPrintThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPODPrintThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CPODToolBar

IMPLEMENT_DYNCREATE(CPODToolBar,CDisplayToolBar)

CPODToolBar::CPODToolBar() : CDisplayToolBar()
{
  return;
}

BEGIN_MESSAGE_MAP(CPODToolBar, CDisplayToolBar)
	//{{AFX_MSG_MAP(CPODToolBar)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPODToolBar message handlers


/////////////////////////////////////////////////////////////////////////////
// CPODStatusBar

IMPLEMENT_DYNCREATE(CPODStatusBar,CDisplayStatusBar)

CPODStatusBar::CPODStatusBar() : CDisplayStatusBar()
{
  return;
}

BOOL CPODStatusBar::SetIndicators(CONST UINT *pPanesID,INT nCount)
{
  INT  nIndex;
  CRect  rPane;
  CString  szPane;
  CToolInfo  cToolInfo;
  CDisplayLock  cLock(this);

  if (CDisplayStatusBar::SetIndicators(pPanesID,nCount))
  { if (CommandToIndex(ID_POD_STATUSBAR_MESSAGEPANE) >= 0)
    { szPane.Format(STRING(IDS_POD_STATUSBAR_UPDATEMESSAGE),(LPCTSTR) CTimeTag().FormatGmt(),(LPCTSTR) CString(CTimeTag().FormatGmt().Right(1),GetDatabase() -> GetTMPacketTagLength()),-1,STRING(IDS_POD_STATUSBAR_QUALITYGOOD));
      SetPaneInfo(CommandToIndex(ID_POD_STATUSBAR_MESSAGEPANE),ID_POD_STATUSBAR_MESSAGEPANE,SBPS_NOBORDERS | SBPS_STRETCH,CalcPaneWidth(szPane+STRING(IDS_POD_STATUSBAR_TIMECORRELATIONFLAG)));
    }
    if (!IsWindow(m_wndToolTip.GetSafeHwnd()))
    { m_wndToolTip.Create(this,TTS_ALWAYSTIP | TTS_NOPREFIX | TTS_BALLOON);
      SetClassLongPtr(m_wndToolTip.GetSafeHwnd(),GCL_STYLE,GetClassLongPtr(m_wndToolTip.GetSafeHwnd(),GCL_STYLE) | CS_DROPSHADOW);
    }
    if (IsWindow(m_wndToolTip.GetSafeHwnd()))
    { if ((nIndex = CommandToIndex(ID_POD_STATUSBAR_MODEPANE)) >= 0)
      { for (GetItemRect(nIndex,rPane); !m_wndToolTip.GetToolInfo(cToolInfo,this,ID_POD_STATUSBAR_MODEPANE); )
        { m_wndToolTip.AddTool(this,LPSTR_TEXTCALLBACK,rPane,ID_POD_STATUSBAR_MODEPANE);
          break;
        }
      }
      if ((nIndex = CommandToIndex(ID_POD_STATUSBAR_TYPEPANE)) >= 0)
      { for (GetItemRect(nIndex,rPane); !m_wndToolTip.GetToolInfo(cToolInfo,this,ID_POD_STATUSBAR_TYPEPANE); )
        { m_wndToolTip.AddTool(this,LPSTR_TEXTCALLBACK,rPane,ID_POD_STATUSBAR_TYPEPANE);
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

CPODWnd *CPODStatusBar::GetParent() CONST
{
  return((CPODWnd *) CDisplayStatusBar::GetParent());
}

BEGIN_MESSAGE_MAP(CPODStatusBar, CDisplayStatusBar)
	//{{AFX_MSG_MAP(CPODStatusBar)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_NOTIFY_EX(TTN_NEEDTEXT,0,OnToolTipNotify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPODStatusBar message handlers

void CPODStatusBar::OnPaint()
{
  INT  nIndex;
  RECT  rPane;
  CToolInfo  cToolInfo;

  for (CDisplayStatusBar::OnPaint(); IsWindow(m_wndToolTip.GetSafeHwnd()); )
  { if ((nIndex = CommandToIndex(ID_POD_STATUSBAR_MODEPANE)) >= 0  &&  nIndex < m_prPanes.GetSize())
    { for (m_wndToolTip.GetToolInfo(cToolInfo,this,ID_POD_STATUSBAR_MODEPANE),CopyMemory(&rPane,m_prPanes.GetAt(nIndex),sizeof(RECT)); !EqualRect(&cToolInfo.rect,&rPane); )
      { SetRect(&cToolInfo.rect,rPane.left,rPane.top,rPane.right,rPane.bottom);
        m_wndToolTip.SetToolInfo(&cToolInfo);
        break;
      }
    }
    if ((nIndex = CommandToIndex(ID_POD_STATUSBAR_TYPEPANE)) >= 0  &&  nIndex < m_prPanes.GetSize())
    { for (m_wndToolTip.GetToolInfo(cToolInfo,this,ID_POD_STATUSBAR_TYPEPANE),CopyMemory(&rPane,m_prPanes.GetAt(nIndex),sizeof(RECT)); !EqualRect(&cToolInfo.rect,&rPane); )
      { SetRect(&cToolInfo.rect,rPane.left,rPane.top,rPane.right,rPane.bottom);
        m_wndToolTip.SetToolInfo(&cToolInfo);
        break;
      }
    }
    break;
  }
}

void CPODStatusBar::OnMouseMove(UINT nFlags,CPoint point)
{
  MSG  sMsg;

  if (IsWindow(m_wndToolTip.GetSafeHwnd()))
  { CopyMemory(&sMsg,GetCurrentMessage(),sizeof(MSG));
    m_wndToolTip.RelayEvent(&sMsg);
  }
  CDisplayStatusBar::OnMouseMove(nFlags,point);
}

BOOL CPODStatusBar::OnToolTipNotify(UINT nID,NMHDR *pNotifyInfo,LRESULT *pResult)
{
  TOOLTIPTEXT  *pToolTipInfo=(TOOLTIPTEXT *) pNotifyInfo;

  switch (pNotifyInfo -> idFrom)
  { case ID_POD_STATUSBAR_MODEPANE:
    { pToolTipInfo -> lpszText = (LPTSTR) STRING(IDS_POD_STATUSBAR_MODEPANE);
      return TRUE;
    }
    case ID_POD_STATUSBAR_TYPEPANE:
    { pToolTipInfo -> lpszText = (LPTSTR) STRING(IDS_POD_STATUSBAR_TYPEPANE);
      return TRUE;
    }
  }
  return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CPODToolTip

IMPLEMENT_DYNCREATE(CPODToolTip,CDisplayToolTip)

CPODToolTip::CPODToolTip() : CDisplayToolTip()
{
  return;
}

BEGIN_MESSAGE_MAP(CPODToolTip, CDisplayToolTip)
	//{{AFX_MSG_MAP(CPODToolTip)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPODToolTip message handlers


/////////////////////////////////////////////////////////////////////////////
// CPODSplitterBarCtrl

IMPLEMENT_DYNCREATE(CPODSplitterBarCtrl,CWnd)

CPODSplitterBarCtrl::CPODSplitterBarCtrl() : CWnd()
{
  m_ptBar[0].x = m_ptBar[0].y = 0;
  m_ptBar[1].x = m_ptBar[1].y = 0;
}

BOOL CPODSplitterBarCtrl::Create(CWnd *pParentWnd,CONST RECT &rect)
{
  return CWnd::CreateEx(0,AfxRegisterWndClass(CS_NOCLOSE),EMPTYSTRING,WS_CHILD | WS_VISIBLE,rect,pParentWnd,0);
}
BOOL CPODSplitterBarCtrl::Create(CWnd *pParentWnd,CONST RECT &rect,CONST POINT &point)
{
  if (CWnd::CreateEx(0,AfxRegisterWndClass(CS_NOCLOSE),EMPTYSTRING,WS_POPUP,rect,pParentWnd,0))
  { ShowWindow(SW_SHOWNA);
    m_ptBar[0] = point;
    m_ptBar[1] = point;
    return TRUE;
  }
  return FALSE;
}

VOID CPODSplitterBarCtrl::Translate(CONST POINT &point)
{
  CRect  rDragBar;

  GetWindowRect(rDragBar);
  MoveWindow(rDragBar.left,rDragBar.top+point.y-m_ptBar[1].y,rDragBar.Width(),rDragBar.Height());
  m_ptBar[1].y = point.y;
  Invalidate(FALSE);
  UpdateWindow();
}

INT CPODSplitterBarCtrl::CalcTranslation(CONST POINT &point) CONST
{
  return point.y-m_ptBar[0].y;
}
INT CPODSplitterBarCtrl::CalcTranslation() CONST
{
  return m_ptBar[1].y-m_ptBar[0].y;
}

void CPODSplitterBarCtrl::PostNcDestroy()
{
  m_ptBar[0].x = m_ptBar[0].y = 0;
  m_ptBar[1].x = m_ptBar[1].y = 0;
  CWnd::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CPODSplitterBarCtrl, CWnd)
	//{{AFX_MSG_MAP(CPODSplitterBarCtrl)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPODSplitterBarCtrl message handlers

BOOL CPODSplitterBarCtrl::OnEraseBkgnd(CDC *pDC)
{
  CDC  cMemDC;
  CPen  cPen;
  CPen  *pOldPen;
  CBitmap  cBitmap;
  CBitmap  *pOldBitmap;
  CRect  rBar;

  for (GetClientRect(rBar); GetStyle() & WS_POPUP; )
  { pDC -> DrawDragRect(rBar,CSize(rBar.Height(),rBar.Height()),(LPCRECT) NULL,CSize(0,0));
    return TRUE;
  }
  if (cMemDC.CreateCompatibleDC(pDC))
  { if (cBitmap.CreateCompatibleBitmap(pDC,rBar.Width(),rBar.Height()))
    { if ((pOldBitmap = cMemDC.SelectObject(&cBitmap)) != (CBitmap *) NULL)
      { if (cPen.CreatePen(PS_SOLID,1,GetSysColor(COLOR_3DSHADOW)))
        { if ((pOldPen = cMemDC.SelectObject(&cPen)) != (CPen *) NULL)
          { cMemDC.FillSolidRect(0,0,rBar.Width(),rBar.Height(),GetSysColor(COLOR_3DFACE));
            cMemDC.MoveTo(0,0);
            cMemDC.LineTo(rBar.Width(),0);
            cMemDC.MoveTo(0,rBar.Height()-1);
            cMemDC.LineTo(rBar.Width(),rBar.Height()-1);
            pDC -> BitBlt(rBar.left,rBar.top,rBar.Width(),rBar.Height(),&cMemDC,0,0,SRCCOPY);
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
// CPODDataView

IMPLEMENT_DYNCREATE(CPODDataView,CTextView)

CPODDataView::CPODDataView() : CTextView()
{
  m_tTag = 0;
  m_bValues = FALSE;
  m_hToolTipCursor = (HCURSOR) NULL;
  m_bToolTipMode = TRUE;
  m_bUpdate = TRUE;
}

BOOL CPODDataView::Create(CWnd *pParentWnd)
{
  CUIntArray  nWidths;
  CStringArray  szColumns;

  if (CTextView::Create(pParentWnd,CRect(0,0,0,0),TVS_HEADER | TVS_TOP | TVS_HSCROLL | TVS_VSCROLL | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE))
  { szColumns.Add(STRING(IDS_POD_DATAHEADER_TIME));
    szColumns.Add(STRING(IDS_POD_DATAHEADER_VALUE));
    szColumns.Add(STRING(IDS_POD_DATAHEADER_STATUS));
    szColumns.Add(STRING(IDS_POD_DATAHEADER_QUALITY));
    return(((!GetColumnCount() &&  CalcColumnWidths(szColumns,nWidths) &&  SetColumns(szColumns,nWidths)) ||  GetColumnCount() > 0) ? TRUE:FALSE);
  }
  return FALSE;
}

BOOL CPODDataView::SetLayout(CONST CPODLayout &cLayout)
{
  CUIntArray  nWidths;
  CTextViewLock  cLock(this);

  return((IsWindow(GetSafeHwnd())) ? (CalcColumnWidths(cLayout,nWidths) &&  SetLayout(cLayout,nWidths)):m_cLayout.Copy(&cLayout));
}
BOOL CPODDataView::SetLayout(CONST CPODLayout &cLayout,CONST CUIntArray &nWidths)
{
  INT  nItem;
  INT  nItems;
  INT  nCount;
  INT  nSample;
  INT  nColumn;
  INT  nColumns;
  INT  nParameter;
  INT  nParameters;
  INT  nExpression;
  INT  nExpressions;
  LOGFONT  lfFont;
  CTMUnit  cTMUnit;
  CString  szParameter;
  ULONGLONG  nAttributes;
  CUIntArray  nTableRefs[2];
  CUIntArray  nColumnWidths;
  CStringArray  szColumns;
  CStringArray  szParameters;
  CTMParameter  *pTMParameter;
  CPODLayoutExpression  *pExpression;
  CDatabaseTMParameter  *pDatabaseTMParameter;
  CDatabaseTMNumCalTable  *pDatabaseTMNumCalTable;
  CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;
  CTextViewLock  cLock(this);

  if (!IsWindow(GetSafeHwnd()))
  { if (LookupColumnNames(cLayout,szColumns) &&  SetColumns(szColumns,nWidths))
    { m_cLayout.Copy(&cLayout);
      return TRUE;
    }
    return FALSE;
  }
  if (!m_cLayout.Compare(&cLayout) ||  !m_pLayoutValues[0].GetSize())
  { if (LookupColumnNames(cLayout,szColumns) > 0  && ((szColumns.GetSize() == nWidths.GetSize() &&  SetColumns(szColumns,nWidths)) || (szColumns.GetSize() != nWidths.GetSize() &&  CalcColumnWidths(szColumns,nColumnWidths) &&  SetColumns(szColumns,nColumnWidths))))
    { for (nExpression = 0,nExpressions = (INT) m_cLayout.GetSize(),nCount = GetTextCount(); (!nExpression  &&  !nExpressions) ||  nExpression < nExpressions; nExpression++)
      { if (m_cLayout.GetSize() != cLayout.GetSize() || (nExpressions > 0  &&  !m_cLayout.GetAt(nExpression) -> Compare(cLayout.GetAt(nExpression))))
        { DeleteAllText();
          DeleteAllValues();
          break;
        }
      }
      if (m_cLayout.Copy(&cLayout))
      { for (nColumn = 0,nColumns = (INT) szColumns.GetSize(); nColumn < nColumns; nColumn++)
        { if (GetTextFont(&lfFont,(LookupColumnName(szColumns.GetAt(nColumn)) == POD_TITLEITEM_VALUE) ? TRUE:FALSE))
          { SetColumnFont(nColumn,&lfFont);
            continue;
          }
        }
        for (nExpression = 0,nExpressions = (INT) m_cLayout.GetSize(); nExpression < nExpressions; nExpression++)
        { if ((pExpression = m_cLayout.GetAt(nExpression)) &&  pExpression -> GetParameter(szParameter,nSample,nAttributes))
          { if ((pDatabaseTMParameter = GetDatabase() -> GetTMParameters() -> GetAt(GetDatabase() -> GetTMParameters() -> Find(szParameter))))
            { if ((pTMParameter = m_pLayoutValues[0].GetAt(m_pLayoutValues[0].Find(szParameter))) != (CTMParameter *) NULL)
              { pTMParameter -> SetAttributes((nAttributes != 0) ? ((pDatabaseTMParameter -> GetAttributes() & ~(TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_DECIMAL | TMPARAMETER_RADIX_HEXADECIMAL)) | nAttributes):pDatabaseTMParameter -> GetAttributes());
                szParameters.Add(szParameter);
                continue;
              }
              if ((pTMParameter = new CTMParameter))
              { pTMParameter -> SetTag(szParameter);
                pTMParameter -> SetAttributes((nAttributes != 0) ? ((pDatabaseTMParameter -> GetAttributes() & ~(TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_DECIMAL | TMPARAMETER_RADIX_HEXADECIMAL)) | nAttributes):pDatabaseTMParameter -> GetAttributes());
                if (pDatabaseTMParameter -> GetAttributes() & TMPARAMETER_NATURE_CONSTANT) pTMParameter -> SetRawValue(&cTMUnit,0,pDatabaseTMParameter -> GetConstValue(),TMPARAMETER_STATUS_GOOD | TMPARAMETER_STATUS_NOLIMIT | TMPARAMETER_STATUS_VALID,(pDatabaseTMParameter -> GetCalTableRefs(nTableRefs[0],nTableRefs[1]) > 0) ? ((pDatabaseTMParameter -> GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) ? (((pDatabaseTMNumCalTable = GetDatabase() -> GetTMNumCalTables() -> GetAt(nTableRefs[0].GetAt(0)))) ? (LPCTSTR) pDatabaseTMNumCalTable -> GetName():EMPTYSTRING):(((pDatabaseTMTxtCalTable = GetDatabase() -> GetTMTxtCalTables() -> GetAt(nTableRefs[0].GetAt(0)))) ? (LPCTSTR) pDatabaseTMTxtCalTable -> GetName():EMPTYSTRING)):EMPTYSTRING);
                m_pLayoutValues[0].Add(pTMParameter);
                szParameters.Add(szParameter);
                continue;
              }
            }
            break;
          }
        }
        for (nParameter = 0,nParameters = (INT) m_pLayoutValues[0].GetSize(); nParameter < nParameters; nParameter++)
        { for (nItem = 0,nItems = (INT) szParameters.GetSize(); nItem < nItems; nItem++)
          { if ((pTMParameter = m_pLayoutValues[0].GetAt(nParameter)))
            { if (pTMParameter -> GetTag() == szParameters.GetAt(nItem)) break;
              continue;
            }
          }
          if (nItem == nItems)
          { delete m_pLayoutValues[0].GetAt(nParameter);
            m_pLayoutValues[0].RemoveAt(nParameter);
            nParameters--;
            nParameter--;
          }
        }
        if (nExpression == nExpressions)
        { if (nCount != GetTextCount())
          { m_pLayoutValues[0].Reset();
            m_pLayoutValues[1].Reset();
            RecalcLayout();
            return TRUE;
          }
          RecalcLayout();
          return m_pLayoutValues[1].Copy(&m_pLayoutValues[0]);
        }
      }
    }
    RecalcLayout();
    return FALSE;
  }
  return TRUE;
}

BOOL CPODDataView::GetLayout(CPODLayout &cLayout) CONST
{
  CTextViewLock  cLock(this);

  return cLayout.Copy(&m_cLayout);
}
BOOL CPODDataView::GetLayout(CPODLayout &cLayout,CUIntArray &nWidths) CONST
{
  CStringArray  szColumns;
  CTextViewLock  cLock(this);

  return((GetColumns(szColumns,nWidths)) ? cLayout.Copy(&m_cLayout):FALSE);
}

BOOL CPODDataView::SetTitleFont(CONST LOGFONT *plfFont)
{
  LOGFONT  lfFont;
  CTextViewLock  cLock(this);

  if (!CTextView::GetTitleFont(&lfFont) ||  memcmp(plfFont,&lfFont,sizeof(LOGFONT)))
  { if (CTextView::SetTitleFont(plfFont))
    { AdjustColumns();
      return TRUE;
    }
    return FALSE;
  }
  return TRUE;
}

BOOL CPODDataView::GetTitleFont(LOGFONT *plfFont) CONST
{
  CTextViewLock  cLock(this);

  return CTextView::GetTitleFont(plfFont);
}

BOOL CPODDataView::SetTextFont(CONST LOGFONT *plfFont)
{
  LOGFONT  lfFont;
  CTextViewLock  cLock(this);

  if (!CTextView::GetTextFont(&lfFont) ||  memcmp(plfFont,&lfFont,sizeof(LOGFONT)))
  { if (CTextView::SetTextFont(plfFont))
    { AdjustColumns();
      return TRUE;
    }
    return FALSE;
  }
  return TRUE;
}

BOOL CPODDataView::GetTextFont(LOGFONT *plfFont,BOOL bValues) CONST
{
  CTextViewLock  cLock(this);

  if (CTextView::GetTextFont(plfFont))
  { plfFont -> lfWeight = (bValues) ? FW_BOLD:plfFont -> lfWeight;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODDataView::EnableToolTipMode(BOOL bEnable)
{
  m_bToolTipMode = bEnable;
  return TRUE;
}

BOOL CPODDataView::IsToolTipModeEnabled() CONST
{
  return m_bToolTipMode;
}

BOOL CPODDataView::SetFilterMode(UINT nMode)
{
  m_nFilterMode = nMode;
  return TRUE;
}

BOOL CPODDataView::GetFilterMode(UINT &nMode) CONST
{
  nMode = m_nFilterMode;
  return TRUE;
}

BOOL CPODDataView::SetFilterLimit(UINT nLimit)
{
  CTextViewLock  cLock(this);

  if (m_nFilterMode & POD_FILTER_LIMIT)
  { m_nFilterLimit = nLimit;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODDataView::GetFilterLimit(UINT &nLimit) CONST
{
  CTextViewLock  cLock(this);

  if (m_nFilterMode & POD_FILTER_LIMIT)
  { nLimit = m_nFilterLimit;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODDataView::SetFilterStatus(UINT nStatus)
{
  CTextViewLock  cLock(this);

  if (m_nFilterMode & POD_FILTER_STATUS)
  { m_nFilterStatus = nStatus;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODDataView::GetFilterStatus(UINT &nStatus) CONST
{
  CTextViewLock  cLock(this);

  if (m_nFilterMode & POD_FILTER_STATUS)
  { nStatus = m_nFilterStatus;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODDataView::SetFilterRange(CONST CTimeKey &tStartTime,CONST CTimeKey &tStopTime)
{
  CTextViewLock  cLock(this);

  if (m_nFilterMode & POD_FILTER_RANGE)
  { m_tFilterRange[0][0] = tStartTime.GetTime();
    m_tFilterRange[0][1] = tStopTime.GetTime();
    return TRUE;
  }
  return FALSE;
}

BOOL CPODDataView::GetFilterRange(CTimeKey &tStartTime,CTimeKey &tStopTime) CONST
{
  CTextViewLock  cLock(this);

  if (m_nFilterMode & POD_FILTER_RANGE)
  { tStartTime = m_tFilterRange[0][0];
    tStopTime = m_tFilterRange[0][1];
    return TRUE;
  }
  return FALSE;
}

BOOL CPODDataView::SetFilterDailyRange(CONST CTimeSpan &tStartTime,CONST CTimeSpan &tStopTime)
{
  CTextViewLock  cLock(this);

  if (m_nFilterMode & POD_FILTER_DAILYRANGE)
  { m_tFilterDailyRange[0] = tStartTime;
    m_tFilterDailyRange[1] = tStopTime;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODDataView::GetFilterDailyRange(CTimeSpan &tStartTime,CTimeSpan &tStopTime) CONST
{
  CTextViewLock  cLock(this);

  if (m_nFilterMode & POD_FILTER_DAILYRANGE)
  { tStartTime = m_tFilterDailyRange[0];
    tStopTime = m_tFilterDailyRange[1];
    return TRUE;
  }
  return FALSE;
}

BOOL CPODDataView::SetFilterPeriodicalRange(CONST CTimeKey &tStartTime,CONST CTimeSpan &tInterval,CONST CTimeKey &tStopTime)
{
  CTextViewLock  cLock(this);

  if (m_nFilterMode & POD_FILTER_PERIODICALRANGE)
  { m_tFilterRange[1][0] = tStartTime;
    m_tFilterRange[1][1] = tStopTime;
    m_tFilterPeriodical = tInterval;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODDataView::GetFilterPeriodicalRange(CTimeKey &tStartTime,CTimeSpan &tInterval,CTimeKey &tStopTime) CONST
{
  CTextViewLock  cLock(this);

  if (m_nFilterMode & POD_FILTER_PERIODICALRANGE)
  { tStartTime = m_tFilterRange[1][0];
    tStopTime = m_tFilterRange[1][1];
    tInterval = m_tFilterPeriodical;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODDataView::SetFilterDigits(UINT nDigits)
{
  m_nFilterDigits = nDigits;
  return TRUE;
}

BOOL CPODDataView::GetFilterDigits(UINT &nDigits) CONST
{
  nDigits = m_nFilterDigits;
  return TRUE;
}

BOOL CPODDataView::SetFilterColors()
{
  CTextViewLock  cLock(this);

  m_nFilterColors.RemoveAll();
  m_nFilterColors.InsertAt(POD_OOLCOLOR_NOLIMIT,VGA_COLOR_GRAY);
  m_nFilterColors.InsertAt(POD_OOLCOLOR_SOFTLIMIT,VGA_COLOR_RED);
  m_nFilterColors.InsertAt(POD_OOLCOLOR_HARDLIMIT,VGA_COLOR_LTRED);
  m_nFilterColors.InsertAt(POD_OOLCOLOR_DELTALIMIT,VGA_COLOR_MAGENTA);
  m_nFilterColors.InsertAt(POD_OOLCOLOR_CONSISTENCYLIMIT,VGA_COLOR_YELLOW);
  return TRUE;
}
BOOL CPODDataView::SetFilterColors(CONST CUIntArray &nColors)
{
  INT  nIndex;
  INT  nCount;
  CTextViewLock  cLock(this);

  for (nIndex = 0,nCount = (INT) nColors.GetSize(); nIndex < nCount; nIndex++)
  { m_nFilterColors.SetAtGrow(nIndex,nColors.GetAt(nIndex));
    continue;
  }
  return(nColors.GetSize() > 0);
}

BOOL CPODDataView::GetFilterColors(CUIntArray &nColors) CONST
{
  CTextViewLock  cLock(this);

  nColors.Copy(m_nFilterColors);
  return(nColors.GetSize() > 0);
}

BOOL CPODDataView::Initialize(CTMEnvironment *pTMEnvironment,BOOL bBadData)
{
  INT  nSample;
  INT  nParameter;
  INT  nParameters;
  INT  nExpression;
  INT  nExpressions;
  CString  szParameter;
  ULONGLONG  nAttributes;
  CUIntArray  nPastSamples;
  CStringArray  szParameters;
  CTMParameter  *pTMParameter;
  CPODLayoutExpression  *pExpression;
  CTextViewLock  cLock(this);

  for (nExpression = 0,nExpressions = (INT) m_cLayout.GetSize(); nExpression < nExpressions; nExpression++)
  { if ((pExpression = m_cLayout.GetAt(nExpression)) &&  pExpression -> GetParameter(szParameter,nSample,nAttributes))
    { for (nParameter = 0,nParameters = (nSample < 0) ? (INT) szParameters.GetSize():-1; nParameter < nParameters; nParameter++)
      { if (!szParameters.GetAt(nParameter).Compare(szParameter) &&  nPastSamples.GetAt(nParameter) < (UINT) abs(nSample))
        { nPastSamples.SetAt(nParameter,abs(nSample));
          break;
        }
        if (!szParameters.GetAt(nParameter).Compare(szParameter)) break;
      }
      if (nParameter == nParameters)
      { szParameters.Add(szParameter);
        nPastSamples.Add(abs(nSample));
      }
    }
  }
  for (nParameter = 0,nParameters = (INT) szParameters.GetSize(),pTMEnvironment -> Initialize(szParameters,nPastSamples); nParameter < nParameters; nParameter++)
  { if ((pTMParameter = m_pLayoutValues[0].GetAt(m_pLayoutValues[0].Find(szParameters.GetAt(nParameter)))))
    { pTMParameter -> SetPastValueSamples(nPastSamples.GetAt(nParameter));
      continue;
    }
  }
  return pTMEnvironment -> Initialize(m_pLayoutValues[0],bBadData);
}
BOOL CPODDataView::Initialize(CString &szTag,CTimeTag &tTag,BOOL bBadData)
{
  INT  nMode;
  INT  nParameter;
  INT  nParameters;
  CTMParameter  *pTMParameter;
  CTextViewLock  cLock(this);

  for (nParameter = 0,nParameters = (m_pLayoutValues[1].Copy(&m_pLayoutValues[0])) ? ((((nMode = GetParent() -> GetMode()) == DISPLAY_MODE_REALTIME  &&  InitializeTMData(m_pLayoutValues[0],bBadData)) || (nMode == DISPLAY_MODE_HISTORY  &&  GetParent() -> InitializeTMData(m_pLayoutValues[0],bBadData))) ? (INT) m_pLayoutValues[0].GetSize():-1):-1,szTag.Empty(),tTag = 0; nParameter < nParameters; nParameter++)
  { if ((pTMParameter = m_pLayoutValues[0].GetAt(nParameter)) &&  pTMParameter -> IsInitialized() &&  tTag < pTMParameter -> GetLastUpdateTime())
    { szTag = pTMParameter -> GetLastUpdateTMUnit();
      tTag = pTMParameter -> GetLastUpdateTime();
    }
  }
  if (nParameter == nParameters)
  { if (!m_pLayoutValues[0].Compare(&m_pLayoutValues[1]))
    { DeleteAllText();
      DeleteAllValues();
    }
    if (!GetTextCount()) Update((CTMEnvironment *) NULL,bBadData);
    return TRUE;
  }
  return FALSE;
}

BOOL CPODDataView::Update(CTMEnvironment *pTMEnvironment,BOOL bBadData)
{
  INT  nIndex;
  INT  nCount;
  INT  nOffset;
  INT  nSample;
  INT  nColumn;
  INT  nColumns;
  INT  nParameter;
  INT  nParameters;
  INT  nExpression;
  INT  nExpressions;
  UINT  nFilterMode;
  UINT  nFilterLimit;
  UINT  nFilterDigits;
  UINT  nFilterStatus[2];
  UINT  nParameterStatus;
  UINT  nExpressionStatus;
  BOOL  bParameterChanges;
  BOOL  bOutsideCalibration;
  BOOL  bExpressionStack;
  double  fParameterValue;
  CString  szParameter;
  CString  szParameterValue;
  CString  szExpressionTag;
  CString  szExpressionText;
  CString  szExpressionValue;
  CString  szExpressionStatus;
  CString  szExpressionQuality;
  CString  szExpressionError;
  COLORREF  nExpressionColor;
  CTimeTag  tExpressionTime;
  CTimeKey  tFilterRange[2][2];
  CTimeSpan  tFilterDailyRange[2];
  CTimeSpan  tFilterInterval;
  ULONGLONG  nAttributes;
  ULONGLONG  nParameterValue;
  CUIntArray  nFilterColors;
  CUIntArray  nPastSamples;
  CFloatArray  fExpressions;
  CStringArray  szColumns;
  CStringArray  szParameters;
  CStringTools  cStringTools;
  CTMParameter  *pTMParameter;
  CTextViewAttribute  cAttribute;
  CPODLayoutExpression  *pExpression;
  CDatabaseTMParameter  *pDatabaseTMParameter;
  CTextViewLock  cLock(this);

  for (nExpression = 0,nExpressions = (INT) m_cLayout.GetSize(),fExpressions.SetSize(m_cLayout.GetSize()),nCount = 0; nExpression < nExpressions; nExpression++)
  { if ((pExpression = m_cLayout.GetAt(nExpression)) &&  pExpression -> GetParameter(szParameter,nSample,nAttributes))
    { for (nParameter = 0,nParameters = (nSample < 0) ? (INT) szParameters.GetSize():-1; nParameter < nParameters; nParameter++)
      { if (!szParameters.GetAt(nParameter).Compare(szParameter) &&  nPastSamples.GetAt(nParameter) < (UINT) abs(nSample))
        { nPastSamples.SetAt(nParameter,abs(nSample));
          break;
        }
        if (!szParameters.GetAt(nParameter).Compare(szParameter)) break;
      }
      if (nParameter == nParameters)
      { szParameters.Add(szParameter);
        nPastSamples.Add(abs(nSample));
      }
      nCount++;
    }
  }
  for (nParameter = 0,nParameters = (INT) szParameters.GetSize(); nParameter < nParameters; nParameter++)
  { if ((pTMParameter = m_pLayoutValues[0].GetAt(m_pLayoutValues[0].Find(szParameters.GetAt(nParameter)))))
    { pTMParameter -> SetPastValueSamples(nPastSamples.GetAt(nParameter));
      continue;
    }
  }
  for (nExpression = 0,nExpressions = ((!pTMEnvironment  || (pTMEnvironment -> Initialize(szParameters,nPastSamples) &&  m_pLayoutValues[0].Update(GetDatabase(),pTMEnvironment -> GetTMUnit(),pTMEnvironment -> GetTMParameters(),bBadData) &&  !m_pLayoutValues[0].Compare(&m_pLayoutValues[1]))) &&  GetFilterMode(nFilterMode) &&  GetFilterDigits(nFilterDigits) &&  GetFilterColors(nFilterColors)) ? (INT) m_cLayout.GetSize():-1,bExpressionStack = (nCount < nExpressions) ? TRUE:FALSE,szExpressionTag.Empty(),tExpressionTime = 0,nExpressionStatus = 0,bParameterChanges = FALSE,nIndex = 0; nExpression < nExpressions; nExpression++)
  { if ((pExpression = m_cLayout.GetAt(nExpressions-nExpression-1)))
    { if (pExpression -> IsNumber())
      { fExpressions[nIndex] = pExpression -> GetNumber();
        nIndex++;
        continue;
      }
      if (pExpression -> IsParameter())
      { if ((pTMParameter = (pExpression -> GetParameter(szParameter,nSample,nAttributes)) ? m_pLayoutValues[0].GetAt(m_pLayoutValues[0].Find(szParameter)):(CTMParameter *) NULL))
        { if (pTMParameter -> GetRawValue(nSample,nParameterValue,nParameterStatus) &&  pTMParameter -> GetValue(GetDatabase(),nSample,pTMParameter -> GetAttributes(),fParameterValue) &&  pTMParameter -> GetValueAsText(GetDatabase(),nSample,pTMParameter -> GetAttributes(),((pTMParameter -> GetAttributes() & TMPARAMETER_CALIBRATION_STATUS) == 0  &&  nFilterDigits > 0) ? nFilterDigits:-1,szParameterValue))
          { for (szExpressionTag = (pTMParameter -> GetLastUpdateTime() > tExpressionTime) ? pTMParameter -> GetLastUpdateTMUnit():szExpressionTag,tExpressionTime = (pTMParameter -> GetLastUpdateTime() > tExpressionTime) ? pTMParameter -> GetLastUpdateTime():tExpressionTime,fExpressions[nIndex] = fParameterValue,nExpressionStatus = (nExpressionStatus != 0) ? (((nExpressionStatus & TMPARAMETER_STATUS_GOOD) && (nParameterStatus & TMPARAMETER_STATUS_BAD)) ? (((nExpressionStatus | TMPARAMETER_STATUS_BAD) & ~TMPARAMETER_STATUS_GOOD) | (nParameterStatus & (TMPARAMETER_STATUS_NOLIMIT | TMPARAMETER_STATUS_SOFTLIMIT | TMPARAMETER_STATUS_HARDLIMIT | TMPARAMETER_STATUS_DELTALIMIT | TMPARAMETER_STATUS_CONSISTENCYLIMIT))):(nExpressionStatus | (nParameterStatus & (TMPARAMETER_STATUS_NOLIMIT | TMPARAMETER_STATUS_SOFTLIMIT | TMPARAMETER_STATUS_HARDLIMIT | TMPARAMETER_STATUS_DELTALIMIT | TMPARAMETER_STATUS_CONSISTENCYLIMIT)))):nParameterStatus,nExpressionStatus = (nExpressionStatus != 0) ? (((nExpressionStatus & TMPARAMETER_STATUS_VALID) && (nParameterStatus & TMPARAMETER_STATUS_INVALID)) ? (((nExpressionStatus | TMPARAMETER_STATUS_INVALID) & ~TMPARAMETER_STATUS_VALID) | (nParameterStatus & (TMPARAMETER_STATUS_NOLIMIT | TMPARAMETER_STATUS_SOFTLIMIT | TMPARAMETER_STATUS_HARDLIMIT | TMPARAMETER_STATUS_DELTALIMIT | TMPARAMETER_STATUS_CONSISTENCYLIMIT))):(nExpressionStatus | (nParameterStatus & (TMPARAMETER_STATUS_NOLIMIT | TMPARAMETER_STATUS_SOFTLIMIT | TMPARAMETER_STATUS_HARDLIMIT | TMPARAMETER_STATUS_DELTALIMIT | TMPARAMETER_STATUS_CONSISTENCYLIMIT)))):nParameterStatus,nExpressionStatus = (nExpressionStatus & (TMPARAMETER_STATUS_SOFTLIMIT | TMPARAMETER_STATUS_HARDLIMIT | TMPARAMETER_STATUS_DELTALIMIT | TMPARAMETER_STATUS_CONSISTENCYLIMIT)) ? (nExpressionStatus & ~TMPARAMETER_STATUS_NOLIMIT):nExpressionStatus; !pTMEnvironment  ||  !pTMEnvironment -> GetTMUnit() -> IsValid() || (pTMEnvironment -> GetTMUnit() -> GetTag() == pTMParameter -> GetLastChangeTMUnit() &&  pTMEnvironment -> GetTMUnit() -> GetTimeTag() == pTMParameter -> GetLastChangeTime()); )
            { bParameterChanges = TRUE;
              break;
            }
            nIndex++;
            continue;
          }
        }
        if (m_pExpressionValues.GetSize() > 0) szExpressionError.Format(STRING(IDS_POD_ERROR_NOEVALUATION),(LPCTSTR) pExpression -> GetParameter());
        break;
      }
      if (pExpression -> IsOperator())
      { if (pExpression -> GetOperator() == STRING(IDS_POD_OPERATOR_DIV))
        { if (fExpressions[nIndex-1] != 0.0  &&  fabs(fExpressions[nIndex-1]) > FLT_EPSILON)
          { fExpressions[(nIndex-1)-1] = fExpressions[(nIndex-1)-1]/fExpressions[nIndex-1];
            nIndex--;
            continue;
          }
          if (fExpressions[nIndex-1] == 0.0)
          { szExpressionError.Format(STRING(IDS_POD_ERROR_DIVISIONBYZERO),nExpressions-nExpression-1);
            break;
          }
          szExpressionError.Format(STRING(IDS_POD_ERROR_OVERFLOW),nExpressions-nExpression-1);
          break;
        }
        if (pExpression -> GetOperator() == STRING(IDS_POD_OPERATOR_MUL))
        { fExpressions[(nIndex-1)-1] *= fExpressions[nIndex-1];
          nIndex--;
          continue;
        }
        if (pExpression -> GetOperator() == STRING(IDS_POD_OPERATOR_SUB))
        { fExpressions[(nIndex-1)-1] = fExpressions[(nIndex-1)-1]-fExpressions[nIndex-1];
          nIndex--;
          continue;
        }
        if (pExpression -> GetOperator() == STRING(IDS_POD_OPERATOR_ADD))
        { fExpressions[(nIndex-1)-1] += fExpressions[nIndex-1];
          nIndex--;
          continue;
        }
        if (pExpression -> GetOperator() == STRING(IDS_POD_OPERATOR_CHG))
        { fExpressions[nIndex-1] = -fExpressions[nIndex-1];
          continue;
        }
      }
      if (pExpression -> IsFunction())
      { if (pExpression -> GetFunction() == STRING(IDS_POD_MATHFUNCTION_SIN))
        { fExpressions[nIndex-1] = sin(fExpressions[nIndex-1]);
          continue;
        }
        if (pExpression -> GetFunction() == STRING(IDS_POD_MATHFUNCTION_COS))
        { fExpressions[nIndex-1] = cos(fExpressions[nIndex-1]);
          continue;
        }
        if (pExpression -> GetFunction() == STRING(IDS_POD_MATHFUNCTION_TAN))
        { if (fabs(fmod(fExpressions[nIndex-1],M_PI))-M_PI/2.0 > FLT_EPSILON)
          { fExpressions[nIndex-1] = tan(fExpressions[nIndex-1]);
            continue;
          }
          szExpressionError.Format(STRING(IDS_POD_ERROR_OVERFLOW),nExpressions-nExpression-1);
          break;
        }
        if (pExpression -> GetFunction() == STRING(IDS_POD_MATHFUNCTION_ASIN))
        { if (fabs(fExpressions[nIndex-1]) <= 1.0)
          { fExpressions[nIndex-1] = asin(fExpressions[nIndex-1]);
            continue;
          }
          szExpressionError.Format(STRING(IDS_POD_ERROR_ILLEGALARGUMENT),nExpressions-nExpression-1);
          break;
        }
        if (pExpression -> GetFunction() == STRING(IDS_POD_MATHFUNCTION_ACOS))
        { if (fabs(fExpressions[nIndex-1]) <= 1.0)
          { fExpressions[nIndex-1] = acos(fExpressions[nIndex-1]);
            continue;
          }
          szExpressionError.Format(STRING(IDS_POD_ERROR_ILLEGALARGUMENT),nExpressions-nExpression-1);
          break;
        }
        if (pExpression -> GetFunction() == STRING(IDS_POD_MATHFUNCTION_ATAN))
        { fExpressions[nIndex-1] = atan(fExpressions[nIndex-1]);
          continue;
        }
        if (pExpression -> GetFunction() == STRING(IDS_POD_MATHFUNCTION_ABS))
        { fExpressions[nIndex-1] = fabs(fExpressions[nIndex-1]);
          continue;
        }
        if (pExpression -> GetFunction() == STRING(IDS_POD_MATHFUNCTION_INT))
        { fExpressions[nIndex-1] = (fExpressions[nIndex-1] >= 0.0) ? floor(fExpressions[nIndex-1]):ceil(fExpressions[nIndex-1]);
          continue;
        }
        if (pExpression -> GetFunction() == STRING(IDS_POD_MATHFUNCTION_SQRT))
        { if (fExpressions[nIndex-1] >= 0.0)
          { fExpressions[nIndex-1] = sqrt(fExpressions[nIndex-1]);
            continue;
          }
          szExpressionError.Format(STRING(IDS_POD_ERROR_ILLEGALARGUMENT),nExpressions-nExpression-1);
          break;
        }
        if (pExpression -> GetFunction() == STRING(IDS_POD_MATHFUNCTION_POW2))
        { fExpressions[nIndex-1] = pow(fExpressions[nIndex-1],2.0);
          continue;
        }
        if (pExpression -> GetFunction() == STRING(IDS_POD_MATHFUNCTION_POWY))
        { fExpressions[(nIndex-1)-1] = pow(fExpressions[(nIndex-1)-1],fExpressions[nIndex-1]);
          nIndex--;
          continue;
        }
        if (pExpression -> GetFunction() == STRING(IDS_POD_MATHFUNCTION_LN))
        { if (fExpressions[nIndex-1] > 0.0)
          { fExpressions[nIndex-1] = log(fExpressions[nIndex-1]);
            continue;
          }
          szExpressionError.Format(STRING(IDS_POD_ERROR_ILLEGALARGUMENT),nExpressions-nExpression-1);
          break;
        }
        if (pExpression -> GetFunction() == STRING(IDS_POD_MATHFUNCTION_LOG))
        { if (fExpressions[nIndex-1] > 0.0)
          { fExpressions[nIndex-1] = log10(fExpressions[nIndex-1]);
            continue;
          }
          szExpressionError.Format(STRING(IDS_POD_ERROR_ILLEGALARGUMENT),nExpressions-nExpression-1);
          break;
        }
        if (pExpression -> GetFunction() == STRING(IDS_POD_MATHFUNCTION_EXP))
        { fExpressions[nIndex-1] = exp(fExpressions[nIndex-1]);
          continue;
        }
      }
    }
  }
  if ((nIndex == 1  ||  !bExpressionStack) &&  nExpression == nExpressions  &&  nExpressions > 0)
  { if (GetFilterRange(tFilterRange[0][0],tFilterRange[0][1]))
    { if (tFilterRange[0][0].GetTime() > tExpressionTime.GetTimeInSeconds() ||  tFilterRange[0][1].GetTime() < tExpressionTime.GetTimeInSeconds())
      { m_pLayoutValues[1].Copy(&m_pLayoutValues[0]);
        return TRUE;
      }
    }
    if (GetFilterDailyRange(tFilterDailyRange[0],tFilterDailyRange[1]))
    { if ((tFilterDailyRange[0] <= tFilterDailyRange[1] && (tFilterDailyRange[0].GetTotalSeconds() > tExpressionTime.GetTimeInSeconds()%SECONDSPERDAY  ||  tFilterDailyRange[1].GetTotalSeconds() < tExpressionTime.GetTimeInSeconds()%SECONDSPERDAY)) || (tFilterDailyRange[0] > tFilterDailyRange[1] &&  tFilterDailyRange[0].GetTotalSeconds() > tExpressionTime.GetTimeInSeconds()%SECONDSPERDAY  &&  tFilterDailyRange[1].GetTotalSeconds() < tExpressionTime.GetTimeInSeconds()%SECONDSPERDAY))
      { m_pLayoutValues[1].Copy(&m_pLayoutValues[0]);
        return TRUE;
      }
    }
    if (GetFilterPeriodicalRange(tFilterRange[1][0],tFilterInterval,tFilterRange[1][1]))
    { if (!tFilterRange[1][0].GetTime() &&  !tFilterRange[1][1].GetTime() && (tExpressionTime.GetTimeInSeconds()/tFilterInterval.GetTotalSeconds())%2)
      { m_pLayoutValues[1].Copy(&m_pLayoutValues[0]);
        return TRUE;
      }
      if (tFilterRange[1][0] > 0  &&  !tFilterRange[1][1].GetTime() && (tFilterRange[1][0].GetTime() > tExpressionTime.GetTimeInSeconds() || ((tExpressionTime.GetTimeInSeconds()-tFilterRange[1][0].GetTime())/tFilterInterval.GetTotalSeconds())%2))
      { m_pLayoutValues[1].Copy(&m_pLayoutValues[0]);
        return TRUE;
      }
      if (tFilterRange[1][0] > 0  &&  tFilterRange[1][1] > 0  && (tFilterRange[1][0].GetTime() > tExpressionTime.GetTimeInSeconds() ||  tFilterRange[1][1].GetTime() < tExpressionTime.GetTimeInSeconds() || ((tExpressionTime.GetTimeInSeconds()-tFilterRange[1][0].GetTime())/tFilterInterval.GetTotalSeconds())%2))
      { m_pLayoutValues[1].Copy(&m_pLayoutValues[0]);
        return TRUE;
      }
    }
    if (GetFilterStatus(nFilterStatus[0]))
    { if ((nFilterStatus[1] = (nFilterStatus[0] & (TMPARAMETER_STATUS_NOLIMIT | TMPARAMETER_STATUS_SOFTLIMIT | TMPARAMETER_STATUS_HARDLIMIT | TMPARAMETER_STATUS_DELTALIMIT | TMPARAMETER_STATUS_CONSISTENCYLIMIT | TMPARAMETER_STATUS_VALID | TMPARAMETER_STATUS_INVALID))) && (nExpressionStatus & (TMPARAMETER_STATUS_NOLIMIT | TMPARAMETER_STATUS_SOFTLIMIT | TMPARAMETER_STATUS_HARDLIMIT | TMPARAMETER_STATUS_DELTALIMIT | TMPARAMETER_STATUS_CONSISTENCYLIMIT | TMPARAMETER_STATUS_VALID | TMPARAMETER_STATUS_INVALID)))
      { if ((nFilterStatus[1] & nExpressionStatus & (TMPARAMETER_STATUS_NOLIMIT | TMPARAMETER_STATUS_SOFTLIMIT | TMPARAMETER_STATUS_HARDLIMIT | TMPARAMETER_STATUS_DELTALIMIT | TMPARAMETER_STATUS_CONSISTENCYLIMIT)) == 0  || (nFilterStatus[1] & nExpressionStatus & (TMPARAMETER_STATUS_VALID | TMPARAMETER_STATUS_INVALID)) == 0)
        { m_pLayoutValues[1].Copy(&m_pLayoutValues[0]);
          return TRUE;
        }
      }
      if ((nFilterStatus[1] = (nFilterStatus[0] & (TMPARAMETER_STATUS_GOOD | TMPARAMETER_STATUS_BAD))))
      { if ((nFilterStatus[1] & nExpressionStatus & (TMPARAMETER_STATUS_GOOD | TMPARAMETER_STATUS_BAD)) == 0)
        { m_pLayoutValues[1].Copy(&m_pLayoutValues[0]);
          return TRUE;
        }
      }
    }
    if ((nFilterMode & POD_FILTER_CHANGES) != POD_FILTER_CHANGES  ||  bParameterChanges)
    { for (nColumn = 0,nColumns = (GetColumns(szColumns)) ? (INT) szColumns.GetSize():0,cAttribute.SetColumnColor(-1,(nExpressionColor=(m_cLayout.GetExpressionColor() == GetSysColor(COLOR_WINDOW)) ? GetDatabase() -> GetPODExpressionColor():m_cLayout.GetExpressionColor())),nOffset = (szColumns.GetSize() > 0  &&  LookupColumnName(szColumns.GetAt(0)) == POD_TITLEITEM_TIME) ? 1:0,nCount = (INT) ((szColumns.GetSize()-nOffset)/nExpressions),szExpressionText.Empty(); nColumn < nColumns; nColumn++)
      { for (nParameter = (nColumn >= nOffset  &&  nCount > 0) ? (nColumn-nOffset)/nCount:0; LookupColumnName(szColumns.GetAt(nColumn)) == POD_TITLEITEM_TIME; )
        { for (szExpressionText = GetColumnDelimiter(); tExpressionTime.GetTime() > 0; )
          { szExpressionText = tExpressionTime.FormatGmt()+szExpressionText;
            break;
          }
          break;
        }
        if (LookupColumnName(szColumns.GetAt(nColumn)) == POD_TITLEITEM_VALUE)
        { for (szExpressionValue = cStringTools.ConvertFloatToString(fExpressions[nIndex-1],(nFilterDigits > 0) ? nFilterDigits:-1),cAttribute.SetColumnColor(nColumn,((nExpressionStatus & TMPARAMETER_STATUS_NOLIMIT) != TMPARAMETER_STATUS_NOLIMIT) ? (((nExpressionStatus & TMPARAMETER_STATUS_SOFTLIMIT) != TMPARAMETER_STATUS_SOFTLIMIT) ? (((nExpressionStatus & TMPARAMETER_STATUS_HARDLIMIT) != TMPARAMETER_STATUS_HARDLIMIT) ? (((nExpressionStatus & TMPARAMETER_STATUS_DELTALIMIT) != TMPARAMETER_STATUS_DELTALIMIT) ? (((nExpressionStatus & TMPARAMETER_STATUS_CONSISTENCYLIMIT) != TMPARAMETER_STATUS_CONSISTENCYLIMIT) ? nExpressionColor:(COLORREF) nFilterColors.GetAt(POD_OOLCOLOR_CONSISTENCYLIMIT)):(COLORREF) nFilterColors.GetAt(POD_OOLCOLOR_DELTALIMIT)):(COLORREF) nFilterColors.GetAt(POD_OOLCOLOR_HARDLIMIT)):(COLORREF) nFilterColors.GetAt(POD_OOLCOLOR_SOFTLIMIT)):(COLORREF) nFilterColors.GetAt(POD_OOLCOLOR_NOLIMIT)); !bExpressionStack; )
          { if ((pTMParameter = ((pExpression = m_cLayout.GetAt(nParameter)) &&  pExpression -> GetParameter(szParameter,nSample,nAttributes)) ? m_pLayoutValues[0].GetAt(m_pLayoutValues[0].Find(szParameter)):(CTMParameter *) NULL) &&  pTMParameter -> GetRawValue(nSample,nParameterValue,nParameterStatus) &&  pTMParameter -> GetValue(GetDatabase(),nSample,pTMParameter -> GetAttributes(),fParameterValue) &&  pTMParameter -> GetValueAsText(GetDatabase(),nSample,pTMParameter -> GetAttributes(),((pTMParameter -> GetAttributes() & TMPARAMETER_CALIBRATION_STATUS) == 0  &&  nFilterDigits > 0) ? nFilterDigits:(((pDatabaseTMParameter=(((pTMParameter -> GetAttributes() & TMPARAMETER_CALIBRATION_NONE) && (pTMParameter -> GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT)) || (pTMParameter -> GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL)) ? GetDatabase() -> GetTMParameters() -> GetAt(GetDatabase() -> GetTMParameters() -> Find(pTMParameter -> GetTag())):(CDatabaseTMParameter *) NULL) &&  pDatabaseTMParameter -> GetDecimalDigits() > 0) ? pDatabaseTMParameter -> GetDecimalDigits():-1),szExpressionValue,bOutsideCalibration,nSample >= 0))
            { for (cAttribute.SetColumnColor(nColumn,((nParameterStatus & TMPARAMETER_STATUS_NOLIMIT) != TMPARAMETER_STATUS_NOLIMIT) ? (((nParameterStatus & TMPARAMETER_STATUS_SOFTLIMIT) != TMPARAMETER_STATUS_SOFTLIMIT) ? (((nParameterStatus & TMPARAMETER_STATUS_HARDLIMIT) != TMPARAMETER_STATUS_HARDLIMIT) ? (((nParameterStatus & TMPARAMETER_STATUS_DELTALIMIT) != TMPARAMETER_STATUS_DELTALIMIT) ? (((nParameterStatus & TMPARAMETER_STATUS_CONSISTENCYLIMIT) != TMPARAMETER_STATUS_CONSISTENCYLIMIT) ? nExpressionColor:(COLORREF) nFilterColors.GetAt(POD_OOLCOLOR_CONSISTENCYLIMIT)):(COLORREF) nFilterColors.GetAt(POD_OOLCOLOR_DELTALIMIT)):(COLORREF) nFilterColors.GetAt(POD_OOLCOLOR_HARDLIMIT)):(COLORREF) nFilterColors.GetAt(POD_OOLCOLOR_SOFTLIMIT)):(COLORREF) nFilterColors.GetAt(POD_OOLCOLOR_NOLIMIT)); bOutsideCalibration; )
              { if (pTMParameter -> GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL)
                { szExpressionValue += GetDatabase() -> GetTMNumCalTablePointOutsideText();
                  break;
                }
                if (pTMParameter -> GetAttributes() & TMPARAMETER_CALIBRATION_STATUS)
                { szExpressionValue += GetDatabase() -> GetTMTxtCalTablePointOutsideText();
                  break;
                }
                break;
              }
              break;
            }
            szExpressionValue.Empty();
            break;
          }
          szExpressionText += szExpressionValue+GetColumnDelimiter();
          continue;
        }
        if (LookupColumnName(szColumns.GetAt(nColumn)) == POD_TITLEITEM_STATUS)
        { for (szExpressionStatus.Format(STRING(IDS_POD_STATUS_FORMAT),(nExpressionStatus & TMPARAMETER_STATUS_NOLIMIT) ? STRING(IDS_POD_STATUS_NOOOL):((nExpressionStatus & TMPARAMETER_STATUS_SOFTLIMIT) ? STRING(IDS_POD_STATUS_SOFTOOL):((nExpressionStatus & TMPARAMETER_STATUS_HARDLIMIT) ? STRING(IDS_POD_STATUS_HARDOOL):((nExpressionStatus & TMPARAMETER_STATUS_DELTALIMIT) ? STRING(IDS_POD_STATUS_DELTAOOL):((nExpressionStatus & TMPARAMETER_STATUS_CONSISTENCYLIMIT) ? STRING(IDS_POD_STATUS_CONSISTENCYOOL):EMPTYSTRING)))),(nExpressionStatus & TMPARAMETER_STATUS_VALID) ? STRING(IDS_POD_STATUS_VALID):((nExpressionStatus & TMPARAMETER_STATUS_INVALID) ? STRING(IDS_POD_STATUS_INVALID):EMPTYSTRING)),szExpressionStatus = (nExpressionStatus & (TMPARAMETER_STATUS_NOLIMIT | TMPARAMETER_STATUS_SOFTLIMIT | TMPARAMETER_STATUS_HARDLIMIT | TMPARAMETER_STATUS_DELTALIMIT | TMPARAMETER_STATUS_CONSISTENCYLIMIT | TMPARAMETER_STATUS_VALID | TMPARAMETER_STATUS_INVALID)) ? (LPCTSTR) szExpressionStatus:EMPTYSTRING; !bExpressionStack; )
          { if ((pTMParameter = ((pExpression = m_cLayout.GetAt(nParameter)) &&  pExpression -> GetParameter(szParameter,nSample,nAttributes)) ? m_pLayoutValues[0].GetAt(m_pLayoutValues[0].Find(szParameter)):(CTMParameter *) NULL) &&  pTMParameter -> GetRawValue(nSample,nParameterValue,nParameterStatus) && (nParameterStatus & (TMPARAMETER_STATUS_NOLIMIT | TMPARAMETER_STATUS_SOFTLIMIT | TMPARAMETER_STATUS_HARDLIMIT | TMPARAMETER_STATUS_DELTALIMIT | TMPARAMETER_STATUS_CONSISTENCYLIMIT | TMPARAMETER_STATUS_VALID | TMPARAMETER_STATUS_INVALID)))
            { szExpressionStatus.Format(STRING(IDS_POD_STATUS_FORMAT),(nParameterStatus & TMPARAMETER_STATUS_NOLIMIT) ? STRING(IDS_POD_STATUS_NOOOL):((nParameterStatus & TMPARAMETER_STATUS_SOFTLIMIT) ? STRING(IDS_POD_STATUS_SOFTOOL):((nParameterStatus & TMPARAMETER_STATUS_HARDLIMIT) ? STRING(IDS_POD_STATUS_HARDOOL):((nParameterStatus & TMPARAMETER_STATUS_DELTALIMIT) ? STRING(IDS_POD_STATUS_DELTAOOL):((nParameterStatus & TMPARAMETER_STATUS_CONSISTENCYLIMIT) ? STRING(IDS_POD_STATUS_CONSISTENCYOOL):EMPTYSTRING)))),(nParameterStatus & TMPARAMETER_STATUS_VALID) ? STRING(IDS_POD_STATUS_VALID):((nParameterStatus & TMPARAMETER_STATUS_INVALID) ? STRING(IDS_POD_STATUS_INVALID):EMPTYSTRING));
              break;
            }
            szExpressionStatus.Empty();
            break;
          }
          szExpressionText += szExpressionStatus+GetColumnDelimiter();
          continue;
        }
        if (LookupColumnName(szColumns.GetAt(nColumn)) == POD_TITLEITEM_QUALITY)
        { for (szExpressionQuality = (nExpressionStatus & (TMPARAMETER_STATUS_GOOD | TMPARAMETER_STATUS_BAD)) ? ((nExpressionStatus & TMPARAMETER_STATUS_GOOD) ? STRING(IDS_POD_QUALITY_GOOD):STRING(IDS_POD_QUALITY_BAD)):EMPTYSTRING; !bExpressionStack; )
          { if ((pTMParameter = ((pExpression = m_cLayout.GetAt(nParameter)) &&  pExpression -> GetParameter(szParameter,nSample,nAttributes)) ? m_pLayoutValues[0].GetAt(m_pLayoutValues[0].Find(szParameter)):(CTMParameter *) NULL) &&  pTMParameter -> GetRawValue(nSample,nParameterValue,nParameterStatus))
            { szExpressionQuality = (nParameterStatus & (TMPARAMETER_STATUS_GOOD | TMPARAMETER_STATUS_BAD)) ? ((nParameterStatus & TMPARAMETER_STATUS_GOOD) ? STRING(IDS_POD_QUALITY_GOOD):STRING(IDS_POD_QUALITY_BAD)):EMPTYSTRING;
              break;
            }
            szExpressionQuality.Empty();
            break;
          }
          szExpressionText += szExpressionQuality+GetColumnDelimiter();
          continue;
        }
      }
      for (SetCurText((m_bUpdate) ? AddText(szExpressionText,&cAttribute):GetCurText()); fExpressions.GetCount() > 1  &&  bExpressionStack; )
      { fExpressions.RemoveAt(1,fExpressions.GetCount()-1);
        break;
      }
      for (SetValues(szExpressionTag,tExpressionTime,fExpressions,(!pTMEnvironment) ? TRUE:FALSE); !bExpressionStack; )
      { UpdateValues(szExpressionTag,tExpressionTime);
        break;
      }
    }
    if ((nFilterLimit = (!GetFilterLimit(nFilterLimit)) ? POD_FILTER_DEFAULTNOLIMIT:nFilterLimit) > 0)
    { while ((nCount = GetTextCount()) > (INT) nFilterLimit)
      { if (DeleteText(0,nCount-nFilterLimit <= 1))
        { DeleteValues(0);
          continue;
        }
        break;
      }
    }
    m_pLayoutValues[1].Copy(&m_pLayoutValues[0]);
    return TRUE;
  }
  if (!szExpressionError.IsEmpty() &&  nExpressions > 0)
  { if (GetFilterRange(tFilterRange[0][0],tFilterRange[0][1]))
    { if (tFilterRange[0][0].GetTime() > tExpressionTime.GetTimeInSeconds() ||  tFilterRange[0][1].GetTime() < tExpressionTime.GetTimeInSeconds())
      { m_pLayoutValues[1].Copy(&m_pLayoutValues[0]);
        return TRUE;
      }
    }
    if (GetFilterDailyRange(tFilterDailyRange[0],tFilterDailyRange[1]))
    { if ((tFilterDailyRange[0] <= tFilterDailyRange[1] && (tFilterDailyRange[0].GetTotalSeconds() > tExpressionTime.GetTimeInSeconds()%SECONDSPERDAY  ||  tFilterDailyRange[1].GetTotalSeconds() < tExpressionTime.GetTimeInSeconds()%SECONDSPERDAY)) || (tFilterDailyRange[0] > tFilterDailyRange[1] &&  tFilterDailyRange[0].GetTotalSeconds() > tExpressionTime.GetTimeInSeconds()%SECONDSPERDAY  &&  tFilterDailyRange[1].GetTotalSeconds() < tExpressionTime.GetTimeInSeconds()%SECONDSPERDAY))
      { m_pLayoutValues[1].Copy(&m_pLayoutValues[0]);
        return TRUE;
      }
    }
    if (GetFilterPeriodicalRange(tFilterRange[1][0],tFilterInterval,tFilterRange[1][1]))
    { if (!tFilterRange[1][0].GetTime() &&  !tFilterRange[1][1].GetTime() && (tExpressionTime.GetTimeInSeconds()/tFilterInterval.GetTotalSeconds())%2)
      { m_pLayoutValues[1].Copy(&m_pLayoutValues[0]);
        return TRUE;
      }
      if (tFilterRange[1][0] > 0  &&  !tFilterRange[1][1].GetTime() && (tFilterRange[1][0].GetTime() > tExpressionTime.GetTimeInSeconds() || ((tExpressionTime.GetTimeInSeconds()-tFilterRange[1][0].GetTime())/tFilterInterval.GetTotalSeconds())%2))
      { m_pLayoutValues[1].Copy(&m_pLayoutValues[0]);
        return TRUE;
      }
      if (tFilterRange[1][0] > 0  &&  tFilterRange[1][1] > 0  && (tFilterRange[1][0].GetTime() > tExpressionTime.GetTimeInSeconds() ||  tFilterRange[1][1].GetTime() < tExpressionTime.GetTimeInSeconds() || ((tExpressionTime.GetTimeInSeconds()-tFilterRange[1][0].GetTime())/tFilterInterval.GetTotalSeconds())%2))
      { m_pLayoutValues[1].Copy(&m_pLayoutValues[0]);
        return TRUE;
      }
    }
    if ((nFilterMode & POD_FILTER_CHANGES) != POD_FILTER_CHANGES  ||  bParameterChanges)
    { for (cAttribute.SetColumnColor(-1,(m_cLayout.GetExpressionColor() == GetSysColor(COLOR_WINDOW)) ? GetDatabase() -> GetPODExpressionColor():m_cLayout.GetExpressionColor()),szExpressionText = (m_cLayout.GetColumns() & POD_TITLEITEM_TIME) ? ((tExpressionTime.GetTime() > 0) ? (LPCTSTR) (tExpressionTime.FormatGmt()+GetColumnDelimiter()):(LPCTSTR) CString(GetColumnDelimiter())):EMPTYSTRING,szExpressionText += (m_cLayout.GetColumns() & POD_TITLEITEM_VALUE) ? (LPCTSTR) szExpressionError:EMPTYSTRING,SetCurText((m_bUpdate) ? AddText(szExpressionText,&cAttribute):GetCurText()); !bExpressionStack; )
      { UpdateValues();
        break;
      }
    }
    if ((nFilterLimit = (!GetFilterLimit(nFilterLimit)) ? POD_FILTER_DEFAULTNOLIMIT:nFilterLimit) > 0)
    { while ((nCount=GetTextCount()) > (INT) nFilterLimit)
      { if (DeleteText(0,nCount-nFilterLimit <= 1))
        { DeleteValues(0);
          continue;
        }
        break;
      }
    }
    m_pLayoutValues[1].Copy(&m_pLayoutValues[0]);
    return TRUE;
  }
  return FALSE;
}

VOID CPODDataView::Reset(CTMEnvironment *pTMEnvironment)
{
  CTextViewLock  cLock(this);

  m_szTag.Empty();
  m_tTag = CTimeTag(0);
  m_fValues.RemoveAll();
  m_bValues = FALSE;
  m_pLayoutValues[0].Reset();
  m_pLayoutValues[1].Reset();
  DeleteAllText();
  DeleteAllValues();
}

BOOL CPODDataView::SetValues(LPCTSTR pszTag,CONST CTimeTag &tTag,CONST CFloatArray &fValues,BOOL bInitialized)
{
  CTextViewLock  cLock(this);

  m_szTag = pszTag;
  m_tTag = tTag;
  m_fValues.Copy(fValues);
  m_bValues = bInitialized;
  return TRUE;
}

BOOL CPODDataView::GetValues(CString &szTag,CTimeTag &tTag,CFloatArray &fValues,BOOL &bInitialized) CONST
{
  CTextViewLock  cLock(this);

  szTag = m_szTag;
  tTag = m_tTag;
  fValues.Copy(m_fValues);
  bInitialized = m_bValues;
  return((!szTag.IsEmpty() &&  tTag != 0  &&  fValues.GetSize() > 0) ? TRUE:FALSE);
}

VOID CPODDataView::UpdateValues(LPCTSTR pszTag,CONST CTimeTag &tTag)
{
  INT  nParameter;
  INT  nParameters;
  CPoint  ptToolTip;
  CString  szText;
  CString  szTitle;
  CTMParameter  *pTMParameter[2];
  CTMParameters  *pTMParameters;
  CPODLayoutExpression  *pExpression;

  if ((pTMParameters = new CTMParameters))
  { for (nParameter = 0,nParameters = (INT) m_cLayout.GetSize(),pTMParameters -> SetSize(nParameters); nParameter < nParameters; nParameter++)
    { if ((pTMParameter[0] = ((pExpression = m_cLayout.GetAt(nParameter))) ? m_pLayoutValues[0].GetAt(m_pLayoutValues[0].Find(pExpression -> GetParameter())):(CTMParameter *) NULL))
      { if ((pTMParameter[1] = new CTMParameter) != (CTMParameter *) NULL)
        { for (pTMParameter[1] -> Copy(pTMParameter[0]); !lstrlen(pszTag) &&  tTag == 0; )
          { pTMParameter[1] -> Reset();
            break;
          }
          pTMParameters -> SetAt(nParameter,pTMParameter[1]);
        }
      }
    }
    m_pExpressionValues.Add(pTMParameters);
  }
  if (m_wndToolTip.IsVisibleAtPoint(ptToolTip))
  { for (szTitle = ConstructToolTipTitle(PointToColumn(ptToolTip)),szText = ConstructToolTipText(PointToRow(ptToolTip),PointToColumn(ptToolTip)); !szTitle.IsEmpty() ||  !szText.IsEmpty(); )
    { m_wndToolTip.Update(szTitle,szText);
      break;
    }
  }
}

VOID CPODDataView::DeleteValues(INT nIndex)
{
  CPoint  ptToolTip;
  CString  szText;
  CString  szTitle;
  CTMParameters  *pTMParameters;

  if ((pTMParameters = (nIndex < m_pExpressionValues.GetSize()) ? (CTMParameters *) m_pExpressionValues.GetAt(nIndex):(CTMParameters *) NULL))
  { m_pExpressionValues.RemoveAt(nIndex);
    delete pTMParameters;
  }
  if (m_wndToolTip.IsVisibleAtPoint(ptToolTip))
  { for (szTitle = ConstructToolTipTitle(PointToColumn(ptToolTip)),szText = ConstructToolTipText(PointToRow(ptToolTip),PointToColumn(ptToolTip)); !szTitle.IsEmpty() ||  !szText.IsEmpty(); )
    { m_wndToolTip.Update(szTitle,szText);
      break;
    }
  }
}

VOID CPODDataView::DeleteAllValues()
{
  INT  nValue;
  INT  nValues;
  CPoint  ptToolTip;
  CString  szText;
  CString  szTitle;
  CTMParameters  *pTMParameters;

  for (nValue = 0,nValues = (INT) m_pExpressionValues.GetSize(),m_szTag.Empty(),m_tTag = 0,m_fValues.RemoveAll(),m_bValues = FALSE; nValue < nValues; nValue++)
  { if ((pTMParameters = (CTMParameters *) m_pExpressionValues.GetAt(nValue))) delete pTMParameters;
    m_pExpressionValues.RemoveAt(nValue);
    nValues--;
    nValue--;
  }
  if (m_wndToolTip.IsVisibleAtPoint(ptToolTip))
  { for (szTitle = ConstructToolTipTitle(PointToColumn(ptToolTip)),szText = ConstructToolTipText(PointToRow(ptToolTip),PointToColumn(ptToolTip)); !szTitle.IsEmpty() ||  !szText.IsEmpty(); )
    { m_wndToolTip.Update(szTitle,szText);
      break;
    }
  }
}

VOID CPODDataView::SetHoldFlag(BOOL bEnable)
{
  m_bUpdate = !bEnable;
}

BOOL CPODDataView::GetHoldFlag() CONST
{
  return !m_bUpdate;
}

BOOL CPODDataView::HasHoldFlag() CONST
{
  return TRUE;
}

BOOL CPODDataView::GetPrintProperties(CPODLayout &cLayout,CStringArray &szColumns,CStringArray &szContents,CTextViewAttributes &pAttributes,CPtrArray &pFonts) CONST
{
  LOGFONT  *plfFont[3];
  CTextViewLock  cLock(this);

  if ((plfFont[0] = (LOGFONT *) GlobalAlloc(GPTR,sizeof(LOGFONT))))
  { if ((plfFont[1] = (LOGFONT *) GlobalAlloc(GPTR,sizeof(LOGFONT))))
    { if ((plfFont[2] = (LOGFONT *) GlobalAlloc(GPTR,sizeof(LOGFONT))))
      { if (GetColumns(szColumns) &&  GetContent(szContents,pAttributes))
        { if (GetTitleFont(plfFont[0]) &&  GetTextFont(plfFont[1]) &&  GetTextFont(plfFont[2],TRUE))
          { if (cLayout.Copy(&m_cLayout))
            { pFonts.Add(plfFont[0]);
              pFonts.Add(plfFont[1]);
              pFonts.Add(plfFont[2]);
              return TRUE;
            }
          }
        }
        GlobalFree(plfFont[2]);
      }
      GlobalFree(plfFont[1]);
    }
    GlobalFree(plfFont[0]);
  }
  return FALSE;
}

BOOL CPODDataView::AdjustColumns()
{
  INT  nColumn;
  INT  nColumns;
  LOGFONT  lfFont;
  CUIntArray  nWidths;
  CStringArray  szColumns;
  CTextViewLock  cLock(this);

  for (nColumn = 0,nColumns = (IsWindow(GetSafeHwnd())) ? ((GetColumns(szColumns,nWidths) &&  CalcColumnWidths(szColumns,nWidths) &&  SetColumns(szColumns,nWidths)) ? (INT) szColumns.GetSize():-1):-1; nColumn < nColumns; nColumn++)
  { if (GetTextFont(&lfFont,!szColumns.GetAt(nColumn).Compare(STRING(IDS_POD_FUNCTIONSHEADER_VALUE))))
    { SetColumnFont(nColumn,&lfFont);
      continue;
    }
  }
  if (nColumns > 0)
  { SetCurText(GetTextCount()-1);
    return TRUE;
  }
  return FALSE;
}

CPODWnd *CPODDataView::GetParent() CONST
{
  return((CPODWnd *) CTextView::GetParent());
}

INT CPODDataView::LookupColumnNames(CONST CPODLayout &cLayout,CStringArray &szColumns) CONST
{
  INT  nColumn;
  INT  nColumns;
  INT  nExpression;
  INT  nExpressions;
  CString  szColumn;
  CStringArray  szColumnGroup;
  CPODLayoutExpression  *pExpression;

  for (nExpression = 0,nExpressions = (INT) cLayout.GetSize(),LookupColumnNames(cLayout.GetColumns(),szColumns); nExpression < nExpressions; nExpression++)
  { if ((pExpression = cLayout.GetAt(nExpression)) &&  !pExpression -> IsParameter()) break;
    continue;
  }
  for (nColumn = 0,nColumns = (nExpression == nExpressions) ? (INT) szColumns.GetSize():0; nColumn < nColumns; nColumn++)
  { if ((szColumn = szColumns.GetAt(nColumn)) != STRING(IDS_POD_DATAHEADER_TIME))
    { szColumnGroup.Add(szColumn);
      continue;
    }
  }
  for (nExpression = (nExpression < nExpressions) ? nExpressions:0; nExpression < nExpressions-1; nExpression++)
  { szColumns.Append(szColumnGroup);
    continue;
  }
  for (nColumn = 0,nColumns = (nColumns > 0) ? (INT) szColumns.GetSize():0,nExpression = 0; nColumn < nColumns; nColumn++)
  { if ((pExpression = (szColumns.GetAt(nColumn) == STRING(IDS_POD_DATAHEADER_VALUE)) ? cLayout.GetAt(nExpression):(CPODLayoutExpression *) NULL))
    { szColumns.SetAt(nColumn,pExpression -> GetParameter()+SPACE+szColumns.GetAt(nColumn));
      nExpression++;
    }
  }
  return((INT) szColumns.GetSize());
}
INT CPODDataView::LookupColumnNames(UINT nColumns,CStringArray &szColumns) CONST
{
  szColumns.RemoveAll();
  if ((nColumns & POD_TITLEITEM_TIME) ||  !nColumns) szColumns.Add(STRING(IDS_POD_DATAHEADER_TIME));
  if ((nColumns & POD_TITLEITEM_VALUE) ||  !nColumns) szColumns.Add(STRING(IDS_POD_DATAHEADER_VALUE));
  if ((nColumns & POD_TITLEITEM_STATUS) ||  !nColumns) szColumns.Add(STRING(IDS_POD_DATAHEADER_STATUS));
  if ((nColumns & POD_TITLEITEM_QUALITY) ||  !nColumns) szColumns.Add(STRING(IDS_POD_DATAHEADER_QUALITY));
  return((INT) szColumns.GetSize());
}

UINT CPODDataView::LookupColumnName(LPCTSTR pszColumn) CONST
{
  CString  szColumn[2];

  if (!lstrcmp(pszColumn,STRING(IDS_POD_DATAHEADER_TIME))) return POD_TITLEITEM_TIME;
  if (!lstrcmp(pszColumn,STRING(IDS_POD_DATAHEADER_VALUE)) || (lstrlen((szColumn[0]=pszColumn)) > lstrlen((szColumn[1]=STRING(IDS_POD_DATAHEADER_VALUE))) &&  szColumn[0].Right(szColumn[1].GetLength()+1) == SPACE+szColumn[1])) return POD_TITLEITEM_VALUE;
  if (!lstrcmp(pszColumn,STRING(IDS_POD_DATAHEADER_STATUS))) return POD_TITLEITEM_STATUS;
  if (!lstrcmp(pszColumn,STRING(IDS_POD_DATAHEADER_QUALITY))) return POD_TITLEITEM_QUALITY;
  return 0;
}

BOOL CPODDataView::CalcColumnWidths(CONST CPODLayout &cLayout,CUIntArray &nWidths)
{
  CStringArray  szColumns;

  return((LookupColumnNames(cLayout,szColumns) > 0) ? CalcColumnWidths(szColumns,nWidths):FALSE);
}
BOOL CPODDataView::CalcColumnWidths(CONST CStringArray &szColumns,CUIntArray &nWidths)
{
  CDC  *pDC;
  INT  nError;
  INT  nErrors;
  INT  nColumn;
  INT  nColumns;
  CFont  cFont[2];
  CFont  *pOldFont;
  LOGFONT  lfFont[2];
  CString  szError;
  CString  szStatus;
  CTimeTag  tTimeTag;
  TEXTMETRIC  tmFont;
  CUIntArray  nColumnWidths;

  if ((pDC = GetDC()))
  { for (nColumn = 0,nColumns = (INT) szColumns.GetSize(),nWidths.RemoveAll(); nColumn < nColumns; nColumn++)
    { if ((pOldFont = (GetTitleFont(&lfFont[0]) &&  cFont[0].CreateFontIndirect(&lfFont[0])) ? pDC -> SelectObject(&cFont[0]):(CFont *) NULL))
      { nColumnWidths.SetAtGrow(nColumn,(nColumn < nColumnWidths.GetSize()) ? max(pDC -> GetTextExtent(szColumns.GetAt(nColumn)).cx,(INT) nColumnWidths.GetAt(nColumn)):pDC -> GetTextExtent(szColumns.GetAt(nColumn)).cx);
        pDC -> SelectObject(pOldFont);
        cFont[0].DeleteObject();
      }
      if (GetTextFont(&lfFont[1],(LookupColumnName(szColumns.GetAt(nColumn)) == POD_TITLEITEM_VALUE) ? TRUE:FALSE))
      { if ((pOldFont = (cFont[1].CreateFontIndirect(&lfFont[1])) ? pDC -> SelectObject(&cFont[1]):(CFont *) NULL))
        { for (pDC -> GetTextMetrics(&tmFont); szColumns.GetAt(nColumn) == STRING(IDS_POD_DATAHEADER_TIME); )
          { nColumnWidths.SetAtGrow(nColumn,(nColumn < nColumnWidths.GetSize()) ? max(pDC -> GetTextExtent(tTimeTag.FormatGmt()).cx,(INT) nColumnWidths.GetAt(nColumn)):pDC -> GetTextExtent(tTimeTag.FormatGmt()).cx);
            nColumnWidths.SetAtGrow(nColumn,(nColumn < nColumnWidths.GetSize()) ? max(GetDatabase() -> GetPODTimeColumnCharWidth()*tmFont.tmAveCharWidth,(INT) nColumnWidths.GetAt(nColumn)):(GetDatabase() -> GetPODTimeColumnCharWidth()*tmFont.tmAveCharWidth));
            break;
          }
          if (LookupColumnName(szColumns.GetAt(nColumn)) == POD_TITLEITEM_VALUE)
          { for (nError = 0,nErrors = MAXPODERRORS-MINPODERRORS+1; nError < nErrors; nError++)
            { szError.Format(STRING(MINPODERRORS+nError),0);
              nColumnWidths.SetAtGrow(nColumn,(nColumn < nColumnWidths.GetSize()) ? max(pDC -> GetTextExtent(szError).cx,(INT) nColumnWidths.GetAt(nColumn)):pDC -> GetTextExtent(szError).cx);
            }
            nColumnWidths.SetAtGrow(nColumn,(nColumn < nColumnWidths.GetSize()) ? max(GetDatabase() -> GetPODValueColumnCharWidth()*tmFont.tmAveCharWidth,(INT) nColumnWidths.GetAt(nColumn)):(GetDatabase() -> GetPODValueColumnCharWidth()*tmFont.tmAveCharWidth));
          }
          if (szColumns.GetAt(nColumn) == STRING(IDS_POD_DATAHEADER_STATUS))
          { szStatus.Format(STRING(IDS_POD_STATUS_FORMAT),STRING(IDS_POD_STATUS_DELTAOOL),STRING(IDS_POD_STATUS_INVALID));
            nColumnWidths.SetAtGrow(nColumn,(nColumn < nColumnWidths.GetSize()) ? max(pDC -> GetTextExtent(szStatus).cx,(INT) nColumnWidths.GetAt(nColumn)):pDC -> GetTextExtent(szStatus).cx);
          }
          if (szColumns.GetAt(nColumn) == STRING(IDS_POD_DATAHEADER_QUALITY)) nColumnWidths.SetAtGrow(nColumn,(nColumn < nColumnWidths.GetSize()) ? max(pDC -> GetTextExtent(STRING(IDS_POD_QUALITY_GOOD)).cx,(INT) nColumnWidths.GetAt(nColumn)):pDC -> GetTextExtent(STRING(IDS_POD_QUALITY_GOOD)).cx);
          pDC -> SelectObject(pOldFont);
        }
        cFont[1].DeleteObject();
      }
      nWidths.SetAtGrow(nColumn,(nColumn > 0) ? (LOWORD(GetTextIndents())+nWidths.GetAt(nColumn-1)+nColumnWidths.GetAt(nColumn)+HIWORD(GetTextIndents())):(LOWORD(GetTextIndents())+nColumnWidths.GetAt(nColumn)+HIWORD(GetTextIndents())));
    }
    ReleaseDC(pDC);
    return TRUE;
  }
  return FALSE;
}
BOOL CPODDataView::CalcColumnWidths(UINT nColumns,CUIntArray &nWidths)
{
  CStringArray  szColumns;

  return((LookupColumnNames(nColumns,szColumns)) ? CalcColumnWidths(szColumns,nWidths):FALSE);
}

INT CPODDataView::FindColumnIndex(LPCTSTR pszColumn) CONST
{
  INT  nColumn;
  INT  nColumns;
  CStringArray  szColumns;

  for (nColumn = 0,nColumns = GetColumns(szColumns); nColumn < nColumns; nColumn++)
  { if (szColumns.GetAt(nColumn) == pszColumn) break;
    continue;
  }
  return((nColumn < nColumns) ? nColumn:-1);
}

UINT CPODDataView::PointToRow(CONST POINT &point) CONST
{
  INT  nRow;
  INT  nColumn;

  return((FindTextFromPoint(point,nRow,nColumn,FALSE) &&  nRow < GetTextCount()) ? nRow:-1);
}

UINT CPODDataView::PointToColumn(CONST POINT &point) CONST
{
  INT  nRow;
  INT  nColumn;

  return((FindTextFromPoint(point,nRow,nColumn,FALSE) &&  nRow < GetTextCount()) ? nColumn:-1);
}

CString CPODDataView::ConstructToolTipTitle(INT nColumn) CONST
{
  INT  nCount;
  INT  nOffset;
  INT  nExpression;
  INT  nExpressions;
  CString  szTitle;
  CStringArray  szColumns;
  CPODLayoutExpression  *pExpression;

  for (nExpression = 0,nExpressions = (INT) m_cLayout.GetSize(),GetColumns(szColumns),nOffset = (szColumns.GetSize() > 0  &&  LookupColumnName(szColumns.GetAt(0)) == POD_TITLEITEM_TIME) ? 1:0,nCount = (nExpressions > 0) ? (INT) ((szColumns.GetSize()-nOffset)/nExpressions):0; nExpression < nExpressions; nExpression++)
  { if ((pExpression = m_cLayout.GetAt(nExpression)) &&  !pExpression -> IsParameter()) break;
    continue;
  }
  if ((pExpression = (nExpression == nExpressions  &&  nExpressions > 0) ? m_cLayout.GetAt(max(nColumn-nOffset,0)/nCount):(CPODLayoutExpression *) NULL))
  { szTitle.Format(STRING(IDS_POD_TOOLTIP_DATATITLE),(LPCTSTR) pExpression -> GetParameter());
    return szTitle;
  }
  return STRING(IDS_POD_TOOLTIP_EXPRESSIONTITLE);
}

CString CPODDataView::ConstructToolTipText(INT nRow,INT nColumn) CONST
{
  INT  nIndex;
  INT  nCount;
  INT  nOffset;
  INT  nSample;
  INT  nExpression;
  INT  nExpressions;
  UINT  nStatus;
  BOOL  bOutSet;
  CString  szText;
  CString  szStatus;
  CString  szCalTable;
  CString  szValue[4];
  CString  szParameter;
  CString  szDescription;
  CString  szValueChange;
  CString  szValueUpdate;
  ULONGLONG  nAttributes;
  ULONGLONG  nValue;
  CStringArray  szColumns;
  CTMParameter  *pTMParameter;
  CTMParameters  *pTMParameters;
  CPODLayoutExpression  *pExpression;
  CDatabaseTMParameter  *pDatabaseTMParameter;

  for (nExpression = 0,nExpressions = (INT) m_cLayout.GetSize(),GetColumns(szColumns),nOffset = (szColumns.GetSize() > 0  &&  LookupColumnName(szColumns.GetAt(0)) == POD_TITLEITEM_TIME) ? 1:0,nCount = (nExpressions > 0) ? (INT) ((szColumns.GetSize()-nOffset)/nExpressions):0; nExpression < nExpressions; nExpression++)
  { if ((pExpression = m_cLayout.GetAt(nExpression)) &&  !pExpression -> IsParameter()) break;
    continue;
  }
  if ((pTMParameter = ((pTMParameters = ((pExpression = (nExpression == nExpressions  &&  nExpressions > 0) ? m_cLayout.GetAt((nIndex=max(nColumn-nOffset,0)/nCount)):(CPODLayoutExpression *) NULL) &&  pExpression -> GetParameter(szParameter,nSample,nAttributes)) ? (CTMParameters *) m_pExpressionValues.GetAt(nRow):(CTMParameters *) NULL)) ? pTMParameters -> GetAt(nIndex):(CTMParameter *) NULL))
  { if ((pDatabaseTMParameter = GetDatabase() -> GetTMParameters() -> GetAt(GetDatabase() -> GetTMParameters() -> Find(szParameter))))
    { if (pTMParameter -> IsInitialized() &&  pTMParameter -> GetRawValue(nSample,nValue,nStatus,szCalTable))
      { if ((pTMParameter -> GetAttributes() & TMPARAMETER_CODING_BITPATTERN) || (pTMParameter -> GetAttributes() & TMPARAMETER_CODING_INVERSEBITPATTERN))
        { pTMParameter -> GetValueAsText(GetDatabase(),nSample,(pTMParameter -> GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_DECIMAL | TMPARAMETER_RADIX_HEXADECIMAL)) | TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_RADIX_BINARY,-1,szValue[0]);
          szValue[1].Format(STRING(IDS_POD_TOOLTIP_CODEDVALUE),(LPCTSTR) szValue[0],STRING(IDS_POD_TOOLTIP_BITVALUE));
        }
        if ((pTMParameter -> GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) || (pTMParameter -> GetAttributes() & TMPARAMETER_CODING_COMPLEMENTCOMPLEX))
        { pTMParameter -> GetValueAsText(GetDatabase(),nSample,(pTMParameter -> GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_HEXADECIMAL)) | TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_RADIX_DECIMAL,-1,szValue[0]);
          szValue[1].Format(STRING(IDS_POD_TOOLTIP_CODEDVALUE),(LPCTSTR) szValue[0],(pTMParameter -> GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) ? STRING(IDS_POD_TOOLTIP_SIGNEDVALUE):STRING(IDS_POD_TOOLTIP_COMPLEMENTVALUE));
        }
        if (pTMParameter -> GetAttributes() & TMPARAMETER_CODING_UNSIGNEDINTEGER)
        { pTMParameter -> GetValueAsText(GetDatabase(),nSample,(pTMParameter -> GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_HEXADECIMAL)) | TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_RADIX_DECIMAL,-1,szValue[0]);
          szValue[1].Format(STRING(IDS_POD_TOOLTIP_CODEDVALUE),(LPCTSTR) szValue[0],STRING(IDS_POD_TOOLTIP_UNSIGNEDVALUE));
        }
        if (pTMParameter -> GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT)
        { pTMParameter -> GetValueAsText(GetDatabase(),nSample,(pTMParameter -> GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_HEXADECIMAL)) | TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_RADIX_DECIMAL,(pDatabaseTMParameter -> GetDecimalDigits() > 0) ? pDatabaseTMParameter -> GetDecimalDigits():-1,szValue[0]);
          szValue[1].Format(STRING(IDS_POD_TOOLTIP_CODEDVALUE),(LPCTSTR) szValue[0],STRING(IDS_POD_TOOLTIP_FLOATINGVALUE));
        }
        if ((pTMParameter -> GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_FLOATINGPOINT)) == 0)
        { pTMParameter -> GetValueAsText(GetDatabase(),nSample,TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_RADIX_DECIMAL,-1,szValue[0]);
          szValue[1].Format(STRING(IDS_POD_TOOLTIP_CODEDVALUE),(LPCTSTR) szValue[0],STRING(IDS_POD_TOOLTIP_UNSIGNEDVALUE));
        }
        for (szValue[0].Format(STRING(IDS_POD_TOOLTIP_RAWVALUE),nValue),szDescription.Format(STRING(IDS_POD_TOOLTIP_DESCRIPTION),(!pDatabaseTMParameter -> GetDetails().IsEmpty()) ? (LPCTSTR) pDatabaseTMParameter -> GetDetails():(LPCTSTR) pExpression -> GetComment()),szDescription = (pDatabaseTMParameter -> GetDetails().IsEmpty() &&  pExpression -> GetComment().IsEmpty()) ? STRING(IDS_POD_TOOLTIP_NODESCRIPTION):szDescription,pTMParameter -> GetValueAsText(GetDatabase(),nSample,pTMParameter -> GetAttributes(),((((pTMParameter -> GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) && (pTMParameter -> GetAttributes() & TMPARAMETER_CALIBRATION_NONE)) || (pTMParameter -> GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL)) &&  pDatabaseTMParameter -> GetDecimalDigits() > 0) ? pDatabaseTMParameter -> GetDecimalDigits():-1,szValue[3],bOutSet,(nSample < 0) ? TRUE:FALSE),szValue[2].Format((pTMParameter -> GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) ? STRING(IDS_POD_TOOLTIP_CALIBRATEDNUMERICALVALUE):STRING(IDS_POD_TOOLTIP_CALIBRATEDSTATUSVALUE),(LPCTSTR) (szValue[3]=(bOutSet) ? ((pTMParameter -> GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) ? (szValue[3]+GetDatabase() -> GetTMNumCalTablePointOutsideText()):((pTMParameter -> GetAttributes() & TMPARAMETER_CALIBRATION_STATUS) ? (szValue[3]+GetDatabase() -> GetTMTxtCalTablePointOutsideText()):szValue[3])):szValue[3]),(LPCTSTR) szCalTable,(bOutSet) ? ((pTMParameter -> GetAttributes() & TMPARAMETER_INTERPRETATION_EXTRAPOLATE) ? STRING(IDS_POD_TOOLTIP_EXTRPOLATEDVALUE):STRING(IDS_POD_TOOLTIP_OUTSETVALUE)):STRING(IDS_POD_TOOLTIP_INSETVALUE)),szValueChange.Format(STRING(IDS_POD_TOOLTIP_VALUECHANGE),(LPCTSTR) pTMParameter -> GetLastChangeTime().FormatGmt(),(LPCTSTR) pTMParameter -> GetLastChangeTMUnit()),szValueUpdate.Format(STRING(IDS_POD_TOOLTIP_VALUEUPDATE),(LPCTSTR) pTMParameter -> GetLastUpdateTime().FormatGmt(),(LPCTSTR) pTMParameter -> GetLastUpdateTMUnit()),szStatus.Format(STRING(IDS_POD_TOOLTIP_STATUS),(nStatus & TMPARAMETER_STATUS_GOOD) ? STRING(IDS_POD_TOOLTIP_GOODQUALITY):STRING(IDS_POD_TOOLTIP_BADQUALITY),(nStatus & TMPARAMETER_STATUS_SOFTLIMIT) ? STRING(IDS_POD_TOOLTIP_SOFTOOL):((nStatus & TMPARAMETER_STATUS_HARDLIMIT) ? STRING(IDS_POD_TOOLTIP_HARDOOL):((nStatus & TMPARAMETER_STATUS_DELTALIMIT) ? STRING(IDS_POD_TOOLTIP_DELTAOOL):((nStatus & TMPARAMETER_STATUS_CONSISTENCYLIMIT) ? STRING(IDS_POD_TOOLTIP_CONSISTENCYOOL):STRING(IDS_POD_TOOLTIP_NOOOL)))),(nStatus & TMPARAMETER_STATUS_VALID) ? STRING(IDS_POD_TOOLTIP_VALID):STRING(IDS_POD_TOOLTIP_INVALID)); pTMParameter -> GetAttributes() & TMPARAMETER_NATURE_CONSTANT; )
        { for (szValue[3].Format(STRING(IDS_POD_TOOLTIP_RAWTEXT),(LPCTSTR) pDatabaseTMParameter -> GetConstValueAsText()); (pTMParameter -> GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_FLOATINGPOINT)) == 0; )
          { szValue[0] = szValue[3];
            break;
          }
          szValueChange.Empty();
          szValueUpdate.Empty();
          szStatus.Empty();
          break;
        }
        if (nSample > 0)
        { szValue[3].Format(STRING(IDS_POD_TOOLTIP_OCCURRENCE),nSample);
          szValue[0] = szValue[3]+EOL+szValue[0];
        }
        if (nSample < 0)
        { szValue[3].Format(STRING(IDS_POD_TOOLTIP_PASTVALUE),-nSample);
          szValue[0] = szValue[3]+EOL+szValue[0];
        }
        return((((pTMParameter -> GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) || (pTMParameter -> GetAttributes() & TMPARAMETER_CALIBRATION_STATUS)) &&  lstrlen(szCalTable) > 0) ? ((!szValueChange.IsEmpty() &&  !szValueUpdate.IsEmpty() &&  !szStatus.IsEmpty()) ? (szDescription+EOL+szValue[0]+EOL+szValue[1]+EOL+szValue[2]+EOL+szValueChange+EOL+szValueUpdate+EOL+szStatus):(szDescription+EOL+szValue[0]+EOL+szValue[1]+EOL+szValue[2])):((!szValueChange.IsEmpty() &&  !szValueUpdate.IsEmpty() &&  !szStatus.IsEmpty()) ? (szDescription+EOL+szValue[0]+EOL+szValue[1]+EOL+szValueChange+EOL+szValueUpdate+EOL+szStatus):(szDescription+EOL+szValue[0]+EOL+szValue[1])));
      }
      return STRING(IDS_POD_TOOLTIP_NOVALUE);
    }
  }
  for (nExpression = 0,nExpressions = (INT) m_cLayout.GetSize(); nExpression < nExpressions; nExpression++)
  { if ((pExpression = m_cLayout.GetAt(nExpression)) &&  pExpression -> GetParameter(szParameter,nSample,nAttributes))
    { if ((pDatabaseTMParameter = GetDatabase() -> GetTMParameters() -> GetAt(GetDatabase() -> GetTMParameters() -> Find(szParameter))))
      { for (szParameter.Format(STRING(IDS_POD_TOOLTIP_OPERANDFORMAT),(LPCTSTR) szParameter,(LPCTSTR) pDatabaseTMParameter -> GetDescription()); !lstrlen(pDatabaseTMParameter -> GetDescription()); )
        { szParameter.Format(STRING(IDS_POD_TOOLTIP_OPERANDDESCRIPTION),(LPCTSTR) szParameter);
          break;
        }
        szText = (!szText.IsEmpty()) ? (szText+EOL+szParameter):szParameter;
      }
    }
  }
  return szText;
}

BOOL CPODDataView::LoadToolTipCursor()
{
  return(((m_hToolTipCursor = (HCURSOR) LoadImage(GetModuleHandle((LPCTSTR) NULL),MAKEINTRESOURCE(IDC_TOOLTIPCURSOR),IMAGE_CURSOR,0,0,LR_DEFAULTCOLOR))) ? TRUE:FALSE);
}

HCURSOR CPODDataView::GetToolTipCursor() CONST
{
  return((!m_hToolTipCursor) ? (HCURSOR) (DWORD_PTR) GetClassLongPtr(GetSafeHwnd(),GCLP_HCURSOR):m_hToolTipCursor); 
}

BOOL CPODDataView::FreeToolTipCursor()
{
  if (m_hToolTipCursor)
  { DestroyCursor(m_hToolTipCursor);
    m_hToolTipCursor = (HCURSOR) NULL;
    return TRUE;
  }
  return FALSE;
}

VOID CPODDataView::RefreshContent()
{
  DeleteAllText();
  DeleteAllValues();
}

void CPODDataView::PostNcDestroy()
{
  INT  nValue;
  INT  nValues;
  CTMParameters  *pTMParameters;

  for (nValue = 0,nValues = (INT) m_pExpressionValues.GetSize(),m_cLayout.RemoveAll(),m_pLayoutValues[0].RemoveAll(),m_pLayoutValues[1].RemoveAll(); nValue < nValues; nValue++)
  { if ((pTMParameters = (CTMParameters *) m_pExpressionValues.GetAt(nValue))) delete pTMParameters;
    m_pExpressionValues.RemoveAt(nValue);
    nValues--;
    nValue--;
  }
  CTextView::PostNcDestroy();
}

BOOL CPODDataView::Lock()
{
  return((IsWindow(GetSafeHwnd())) ? (GetParent() -> Lock() &&  CTextView::Lock()):CTextView::Lock());
}

BOOL CPODDataView::Unlock()
{
  return((IsWindow(GetSafeHwnd())) ? (CTextView::Unlock() &&  GetParent() -> Unlock()):CTextView::Unlock());
}

BEGIN_MESSAGE_MAP(CPODDataView, CTextView)
	//{{AFX_MSG_MAP(CPODDataView)
	ON_WM_CREATE()
	ON_WM_SETCURSOR()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPODDataView message handlers

int CPODDataView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
  CTextViewLock  cLock(this);

  if (CTextView::OnCreate(lpCreateStruct) != -1)
  { LoadToolTipCursor();
    return 0;
  }
  return -1;
}

BOOL CPODDataView::OnSetCursor(CWnd *pWnd,UINT nHitTest,UINT message)
{
  LONG  lDataFlag;
  POINT  ptCursor;
  CRect  rContent;
  CTextViewLock  cLock(this);

  for (GetCursorPos(&ptCursor),m_wndContentCtrl.ScreenToClient(&ptCursor),m_wndContentCtrl.GetClientRect(rContent); rContent.PtInRect(ptCursor); )
  { if ((lDataFlag = GetParent() -> IsRetrievingData()) &&  HIWORD(lDataFlag))
    { SetCursor(LoadCursor((HINSTANCE) NULL,IDC_WAIT));
      return TRUE;
    }
    if (IsToolTipModeEnabled())
    { if (PointToRow(ptCursor) != (UINT) -1  &&  PointToColumn(ptCursor) != (UINT) -1)
      { SetCursor(GetToolTipCursor());
        return TRUE;
      }
    }
    break;
  }
  return CTextView::OnSetCursor(pWnd,nHitTest,message);
}

BOOL CPODDataView::OnContentMessage(UINT message,WPARAM wParam,LPARAM lParam,LRESULT *pResult)
{
  LONG  lDataFlag;
  CFont  cFont[2];
  CPoint  ptToolTip;
  LOGFONT  lfFont[2];
  CString  szToolTip[2];
  CTextViewLock  cLock(this);

  if (message == WM_SETFOCUS)
  { SetCurText((GetCurText() >= 0) ? GetCurText():0);
    return FALSE;
  }
  if (message == WM_KEYDOWN)
  { if (wParam == VK_TAB) GetParent() -> SetFocus();
    return FALSE;
  }
  if (message == WM_RBUTTONDOWN)
  { if (IsToolTipModeEnabled())
    { if (PointToRow((ptToolTip=CPoint(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam)))) != (UINT) -1  &&  PointToColumn(ptToolTip) != (UINT) -1  && (!(lDataFlag = GetParent() -> IsRetrievingData()) ||  !HIWORD(lDataFlag)))
      { for (szToolTip[0] = ConstructToolTipTitle(PointToColumn(ptToolTip)),szToolTip[1] = ConstructToolTipText(PointToRow(ptToolTip),PointToColumn(ptToolTip)),GetTextFont(&lfFont[0]),GetTextFont(&lfFont[1]),lfFont[0].lfWeight = FW_BOLD,lfFont[1].lfWeight = FW_NORMAL; cFont[0].CreateFontIndirect(&lfFont[0]) &&  cFont[1].CreateFontIndirect(&lfFont[1]); )
        { m_wndToolTip.SetTitleFont(&cFont[0]);
          m_wndToolTip.SetTextFont(&cFont[1]);
          break;
        }
        m_wndToolTip.Create(&m_wndContentCtrl,ptToolTip,szToolTip[0],szToolTip[1]);
      }
    }
    return FALSE;
  }
  if (message == WM_RBUTTONUP)
  { m_wndToolTip.Destroy();
    return FALSE;
  }
  return FALSE;
}

void CPODDataView::OnDestroy()
{
  CTextViewLock  cLock(this);

  FreeToolTipCursor();
  CTextView::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CPODParametersView

IMPLEMENT_DYNCREATE(CPODParametersView,CTextView)

CPODParametersView::CPODParametersView() : CTextView()
{
  m_hToolTipCursor = (HCURSOR) NULL;
  m_bToolTipMode = TRUE;
}

BOOL CPODParametersView::Create(CWnd *pParentWnd)
{
  CUIntArray  nWidths;
  CStringArray  szColumns;

  return((CTextView::Create(pParentWnd,CRect(0,0,0,0),TVS_HEADER | TVS_TOP | TVS_HSCROLL | TVS_VSCROLL | TVS_NOSELECTION | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE)) ? ((!GetColumnCount() &&  LookupColumnNames(szColumns) > 0  &&  CalcColumnWidths(szColumns,nWidths) > 0  &&  SetColumns(szColumns,nWidths)) ||  GetColumnCount() > 0):FALSE);
}

BOOL CPODParametersView::SetLayout(CONST CPODLayout &cLayout)
{
  CUIntArray  nWidths;
  CTextViewLock  cLock(this);

  return((IsWindow(GetSafeHwnd())) ? (CalcColumnWidths(nWidths) &&  SetLayout(cLayout,nWidths)):m_cLayout.Copy(&cLayout));
}
BOOL CPODParametersView::SetLayout(CONST CPODLayout &cLayout,CONST CUIntArray &nWidths)
{
  INT  nItem;
  INT  nItems;
  INT  nCount;
  INT  nColumn;
  INT  nColumns;
  INT  nParameter[3];
  INT  nParameters[3];
  LOGFONT  lfFont;
  CTMUnit  cTMUnit;
  CString  szParameter;
  CUIntArray  nRefs[2];
  CUIntArray  nColumnWidths;
  CStringArray  szColumns;
  CStringArray  szParameters[2];
  CTMParameter  *pTMParameter;
  CLongUIntArray  nAttributes[2];
  CTextViewAttribute  cAttribute[2];
  CDatabaseTMParameter  *pDatabaseTMParameter;
  CDatabaseTMNumCalTable  *pDatabaseTMNumCalTable;
  CDatabaseTMTxtCalTable  *pDatabaseTMTxtCalTable;
  CTextViewLock  cLock(this);

  if (!IsWindow(GetSafeHwnd()))
  { if (LookupColumnNames(szColumns) &&  SetColumns(szColumns,nWidths))
    { m_cLayout.Copy(&cLayout);
      return TRUE;
    }
    return FALSE;
  }
  if (!m_cLayout.Compare(&cLayout) ||  !GetTextCount())
  { if (GetColumns(szColumns) && ((szColumns.GetSize() == nWidths.GetSize() &&  SetColumns(szColumns,nWidths)) || (szColumns.GetSize() != nWidths.GetSize() &&  CalcColumnWidths(szColumns,nColumnWidths) &&  SetColumns(szColumns,nColumnWidths))))
    { for (nParameter[0] = 0,nParameters[0] = (m_cLayout.GetParameters(szParameters[0],nAttributes[0]) == cLayout.GetParameters(szParameters[1],nAttributes[1]) &&  GetTextCount() > 0) ? (INT) szParameters[0].GetSize():-1; nParameter[0] < nParameters[0]; nParameter[0]++)
      { if (szParameters[0].GetAt(nParameter[0]) != szParameters[1].GetAt(nParameter[0]) ||  nAttributes[0].GetAt(nParameter[0]) != nAttributes[1].GetAt(nParameter[0])) break;
        continue;
      }
      if (m_cLayout.Copy(&cLayout))
      { for (nColumn = 0,nColumns = (INT) szColumns.GetSize(); nColumn < nColumns; nColumn++)
        { if (!szColumns.GetAt(nColumn).Compare(STRING(IDS_POD_PARAMETERSHEADER_VALUE)) &&  GetTextFont(&lfFont,TRUE))
          { SetColumnFont(nColumn,&lfFont);
            break;
          }
        }
        for (cAttribute[0].SetColumnColor(-1,(m_cLayout.GetParametersColor() == GetSysColor(COLOR_WINDOW)) ? GetDatabase() -> GetPODParametersColor():m_cLayout.GetParametersColor()); nParameter[0] < nParameters[0] ||  nParameters[0] < 0; )
        { for (nParameter[0] = 0,nParameters[0] = (INT) szParameters[1].GetSize(),nCount = GetTextCount(),DeleteAllText((!nParameters[0]) ? TRUE:FALSE); nParameter[0] < nParameters[0]; nParameter[0]++)
          { if ((pDatabaseTMParameter = GetDatabase() -> GetTMParameters() -> GetAt(GetDatabase() -> GetTMParameters() -> Find(szParameters[1].GetAt(nParameter[0])))) != (CDatabaseTMParameter *) NULL)
            { InsertText(nParameter[0],(szParameter = pDatabaseTMParameter -> GetTag()+GetColumnDelimiter()+pDatabaseTMParameter -> GetDescription()+GetColumnDelimiter()+GetColumnDelimiter()+pDatabaseTMParameter -> GetUnit()),&cAttribute[0],nParameter[0] == nParameters[0]-1);
              continue;
            }
            break;
          }
          for ( ; GetTextCount() > 0  &&  nCount > 0; )
          { AdjustColumns();
            break;
          }
          for (nParameter[1] = 0,nParameters[1] = (nParameter[0] == nParameters[0] &&  nParameters[0] >= 0) ? (INT) szParameters[1].GetSize():-1; nParameter[1] < nParameters[1]; nParameter[1]++)
          { if ((pDatabaseTMParameter = GetDatabase() -> GetTMParameters() -> GetAt(GetDatabase() -> GetTMParameters() -> Find(szParameters[1].GetAt(nParameter[1])))))
            { if ((pTMParameter = m_pLayoutValues[0].GetAt(m_pLayoutValues[0].Find(szParameters[1].GetAt(nParameter[1])))) != (CTMParameter *) NULL)
              { pTMParameter -> SetAttributes((nAttributes[1].GetAt(nParameter[1]) != 0) ? ((pDatabaseTMParameter -> GetAttributes() & ~(TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_DECIMAL | TMPARAMETER_RADIX_HEXADECIMAL)) | nAttributes[1].GetAt(nParameter[1])):pDatabaseTMParameter -> GetAttributes());
                continue;
              }
              else
              { if ((pTMParameter = new CTMParameter))
                { pTMParameter -> SetTag(szParameters[1].GetAt(nParameter[1]));
                  pTMParameter -> SetAttributes((nAttributes[1].GetAt(nParameter[1]) != 0) ? ((pDatabaseTMParameter -> GetAttributes() & ~(TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_DECIMAL | TMPARAMETER_RADIX_HEXADECIMAL)) | nAttributes[1].GetAt(nParameter[1])):pDatabaseTMParameter -> GetAttributes());
                  if (pDatabaseTMParameter -> GetAttributes() & TMPARAMETER_NATURE_CONSTANT) pTMParameter -> SetRawValue(&cTMUnit,0,pDatabaseTMParameter -> GetConstValue(),TMPARAMETER_STATUS_GOOD | TMPARAMETER_STATUS_NOLIMIT | TMPARAMETER_STATUS_VALID,(pDatabaseTMParameter -> GetCalTableRefs(nRefs[0],nRefs[1]) > 0) ? ((pDatabaseTMParameter -> GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) ? (((pDatabaseTMNumCalTable = GetDatabase() -> GetTMNumCalTables() -> GetAt(nRefs[0].GetAt(0)))) ? (LPCTSTR) pDatabaseTMNumCalTable -> GetName():EMPTYSTRING):(((pDatabaseTMTxtCalTable = GetDatabase() -> GetTMTxtCalTables() -> GetAt(nRefs[0].GetAt(0)))) ? (LPCTSTR) pDatabaseTMTxtCalTable -> GetName():EMPTYSTRING)):EMPTYSTRING);
                  m_pLayoutValues[0].Add(pTMParameter);
                  continue;
                }
              }
            }
            break;
          }
          for (nParameter[2] = 0,nParameters[2] = (nParameter[1] == nParameters[1] &&  nParameters[1] >= 0) ? (INT) m_pLayoutValues[0].GetSize():-1; nParameter[2] < nParameters[2]; nParameter[2]++)
          { for (nItem = 0,nItems = (INT) szParameters[1].GetSize(); nItem < nItems; nItem++)
            { if ((pTMParameter = m_pLayoutValues[0].GetAt(nParameter[2])))
              { if (pTMParameter -> GetTag() == szParameters[1].GetAt(nItem)) break;
                continue;
              }
            }
            if (nItem == nItems)
            { delete m_pLayoutValues[0].GetAt(nParameter[2]);
              m_pLayoutValues[0].RemoveAt(nParameter[2]);
              nParameters[2]--;
              nParameter[2]--;
            }
          }
          if (nParameter[0] == nParameters[0] &&  nParameter[1] == nParameters[1] &&  nParameter[2] == nParameters[2])
          { for (m_pLayoutValues[1].Copy(&m_pLayoutValues[0]); nCount != GetTextCount(); )
            { m_pLayoutValues[0].Reset();
              m_pLayoutValues[1].Reset();
              break;
            }
            RecalcLayout();
            return TRUE;
          }
          RecalcLayout();
          return FALSE;
        }
        for (nParameter[0] = 0,nParameters[0] = (INT) szParameters[1].GetSize(); nParameter[0] < nParameters[0]; nParameter[0]++)
        { if (GetText(nParameter[0],szParameter,&cAttribute[1]) &&  !cAttribute[0].Compare(&cAttribute[1]))
          { SetText(nParameter[0],szParameter,&cAttribute[0]);
            continue;
          }
        }
        RecalcLayout();
        return TRUE;
      }
    }
    RecalcLayout();
    return FALSE;
  }
  return TRUE;
}

BOOL CPODParametersView::GetLayout(CPODLayout &cLayout) CONST
{
  CTextViewLock  cLock(this);

  return cLayout.Copy(&m_cLayout);
}
BOOL CPODParametersView::GetLayout(CPODLayout &cLayout,CUIntArray &nWidths) CONST
{
  CStringArray  szColumns;
  CTextViewLock  cLock(this);

  return((GetColumns(szColumns,nWidths)) ? cLayout.Copy(&m_cLayout):FALSE);
}

BOOL CPODParametersView::SetTitleFont(CONST LOGFONT *plfFont)
{
  LOGFONT  lfFont;
  CTextViewLock  cLock(this);

  if (!CTextView::GetTitleFont(&lfFont) ||  memcmp(plfFont,&lfFont,sizeof(LOGFONT)))
  { if (CTextView::SetTitleFont(plfFont))
    { AdjustColumns();
      return TRUE;
    }
    return FALSE;
  }
  return TRUE;
}

BOOL CPODParametersView::GetTitleFont(LOGFONT *plfFont) CONST
{
  CTextViewLock  cLock(this);

  return CTextView::GetTitleFont(plfFont);
}

BOOL CPODParametersView::SetTextFont(CONST LOGFONT *plfFont)
{
  LOGFONT  lfFont;
  CTextViewLock  cLock(this);

  if (!CTextView::GetTextFont(&lfFont) ||  memcmp(plfFont,&lfFont,sizeof(LOGFONT)))
  { if (CTextView::SetTextFont(plfFont))
    { AdjustColumns();
      return TRUE;
    }
    return FALSE;
  }
  return TRUE;
}

BOOL CPODParametersView::GetTextFont(LOGFONT *plfFont,BOOL bValues) CONST
{
  CTextViewLock  cLock(this);

  if (CTextView::GetTextFont(plfFont))
  { plfFont -> lfWeight = (bValues) ? FW_BOLD:plfFont -> lfWeight;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODParametersView::EnableToolTipMode(BOOL bEnable)
{
  m_bToolTipMode = bEnable;
  return TRUE;
}

BOOL CPODParametersView::IsToolTipModeEnabled() CONST
{
  return m_bToolTipMode;
}

BOOL CPODParametersView::SetFilterMode(UINT nMode)
{
  m_nFilterMode = nMode;
  return TRUE;
}

BOOL CPODParametersView::GetFilterMode(UINT &nMode) CONST
{
  nMode = m_nFilterMode;
  return TRUE;
}

BOOL CPODParametersView::SetFilterLimit(UINT nLimit)
{
  CTextViewLock  cLock(this);

  if (m_nFilterMode & POD_FILTER_LIMIT)
  { m_nFilterLimit = nLimit;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODParametersView::GetFilterLimit(UINT &nLimit) CONST
{
  CTextViewLock  cLock(this);

  if (m_nFilterMode & POD_FILTER_LIMIT)
  { nLimit = m_nFilterLimit;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODParametersView::SetFilterStatus(UINT nStatus)
{
  CTextViewLock  cLock(this);

  if (m_nFilterMode & POD_FILTER_STATUS)
  { m_nFilterStatus = nStatus;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODParametersView::GetFilterStatus(UINT &nStatus) CONST
{
  CTextViewLock  cLock(this);

  if (m_nFilterMode & POD_FILTER_STATUS)
  { nStatus = m_nFilterStatus;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODParametersView::SetFilterRange(CONST CTimeKey &tStartTime,CONST CTimeKey &tStopTime)
{
  CTextViewLock  cLock(this);

  if (m_nFilterMode & POD_FILTER_RANGE)
  { m_tFilterRange[0][0] = tStartTime.GetTime();
    m_tFilterRange[0][1] = tStopTime.GetTime();
    return TRUE;
  }
  return FALSE;
}

BOOL CPODParametersView::GetFilterRange(CTimeKey &tStartTime,CTimeKey &tStopTime) CONST
{
  CTextViewLock  cLock(this);

  if (m_nFilterMode & POD_FILTER_RANGE)
  { tStartTime = m_tFilterRange[0][0];
    tStopTime = m_tFilterRange[0][1];
    return TRUE;
  }
  return FALSE;
}

BOOL CPODParametersView::SetFilterDailyRange(CONST CTimeSpan &tStartTime,CONST CTimeSpan &tStopTime)
{
  CTextViewLock  cLock(this);

  if (m_nFilterMode & POD_FILTER_DAILYRANGE)
  { m_tFilterDailyRange[0] = tStartTime;
    m_tFilterDailyRange[1] = tStopTime;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODParametersView::GetFilterDailyRange(CTimeSpan &tStartTime,CTimeSpan &tStopTime) CONST
{
  CTextViewLock  cLock(this);

  if (m_nFilterMode & POD_FILTER_DAILYRANGE)
  { tStartTime = m_tFilterDailyRange[0];
    tStopTime = m_tFilterDailyRange[1];
    return TRUE;
  }
  return FALSE;
}

BOOL CPODParametersView::SetFilterPeriodicalRange(CONST CTimeKey &tStartTime,CONST CTimeSpan &tInterval,CONST CTimeKey &tStopTime)
{
  CTextViewLock  cLock(this);

  if (m_nFilterMode & POD_FILTER_PERIODICALRANGE)
  { m_tFilterRange[1][0] = tStartTime;
    m_tFilterRange[1][1] = tStopTime;
    m_tFilterPeriodical = tInterval;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODParametersView::GetFilterPeriodicalRange(CTimeKey &tStartTime,CTimeSpan &tInterval,CTimeKey &tStopTime) CONST
{
  CTextViewLock  cLock(this);

  if (m_nFilterMode & POD_FILTER_PERIODICALRANGE)
  { tStartTime = m_tFilterRange[1][0];
    tStopTime = m_tFilterRange[1][1];
    tInterval = m_tFilterPeriodical;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODParametersView::SetFilterDigits(UINT nDigits)
{
  m_nFilterDigits = nDigits;
  return TRUE;
}

BOOL CPODParametersView::GetFilterDigits(UINT &nDigits) CONST
{
  nDigits = m_nFilterDigits;
  return TRUE;
}

BOOL CPODParametersView::SetFilterColors()
{
  CTextViewLock  cLock(this);

  m_nFilterColors.RemoveAll();
  m_nFilterColors.InsertAt(POD_OOLCOLOR_NOLIMIT,VGA_COLOR_GRAY);
  m_nFilterColors.InsertAt(POD_OOLCOLOR_SOFTLIMIT,VGA_COLOR_RED);
  m_nFilterColors.InsertAt(POD_OOLCOLOR_HARDLIMIT,VGA_COLOR_LTRED);
  m_nFilterColors.InsertAt(POD_OOLCOLOR_DELTALIMIT,VGA_COLOR_MAGENTA);
  m_nFilterColors.InsertAt(POD_OOLCOLOR_CONSISTENCYLIMIT,VGA_COLOR_YELLOW);
  return TRUE;
}
BOOL CPODParametersView::SetFilterColors(CONST CUIntArray &nColors)
{
  CTextViewLock  cLock(this);

  m_nFilterColors.Copy(nColors);
  return TRUE;
}

BOOL CPODParametersView::GetFilterColors(CUIntArray &nColors) CONST
{
  CTextViewLock  cLock(this);

  nColors.Copy(m_nFilterColors);
  return TRUE;
}

BOOL CPODParametersView::Initialize(CTMEnvironment *pTMEnvironment,BOOL bBadData)
{
  CTextViewLock  cLock(this);

  return pTMEnvironment -> Initialize(m_pLayoutValues[0],bBadData);
}
BOOL CPODParametersView::Initialize(CString &szTag,CTimeTag &tTag,BOOL bBadData)
{
  INT  nMode;
  INT  nParameter;
  INT  nParameters;
  CTMParameter  *pTMParameter;
  CTextViewLock  cLock(this);

  for (nParameter = 0,nParameters = (m_pLayoutValues[1].Copy(&m_pLayoutValues[0])) ? ((((nMode = GetParent() -> GetMode()) == DISPLAY_MODE_REALTIME  &&  InitializeTMData(m_pLayoutValues[0],bBadData)) || (nMode == DISPLAY_MODE_HISTORY  &&  GetParent() -> InitializeTMData(m_pLayoutValues[0],bBadData))) ? (INT) m_pLayoutValues[0].GetSize():-1):-1; nParameter < nParameters; nParameter++)
  { if ((pTMParameter = m_pLayoutValues[0].GetAt(nParameter)) &&  pTMParameter -> IsInitialized() &&  tTag < pTMParameter -> GetLastUpdateTime())
    { szTag = pTMParameter -> GetLastUpdateTMUnit();
      tTag = pTMParameter -> GetLastUpdateTime();
    }
  }
  if (nParameter == nParameters)
  { Update((CTMEnvironment *) NULL,bBadData);
    return TRUE;
  }
  return FALSE;
}

BOOL CPODParametersView::Update(CTMEnvironment *pTMEnvironment,BOOL bBadData)
{
  INT  nRow;
  INT  nIndex;
  INT  nColumn;
  INT  nParameter;
  INT  nParameters;
  BOOL  bParameter;
  BOOL  bOutSet;
  UINT  nFilterStatus;
  UINT  nFilterDigits;
  UINT  nParameterStatus;
  CPoint  ptToolTip;
  CString  szToolTip[2];
  CString  szParameterValue;
  ULONGLONG  nParameterValue;
  COLORREF  nFilterColor;
  CUIntArray  nFilterColors;
  CStringArray  szColumns;
  CStringArray  szParameters;
  CTMParameter  *pTMParameter;
  CDatabaseTMParameter  *pDatabaseTMParameter;
  CTextViewAttribute  *pAttribute;
  CTextViewLock  cLock(this);

  for (nParameter = 0,nParameters = (!pTMEnvironment  || (m_pLayoutValues[0].Update(GetDatabase(),pTMEnvironment -> GetTMUnit(),pTMEnvironment -> GetTMParameters(),bBadData) &&  !m_pLayoutValues[0].Compare(&m_pLayoutValues[1]))) ? m_cLayout.GetParameters(szParameters):-1,nColumn = FindColumnIndex(STRING(IDS_POD_PARAMETERSHEADER_VALUE)),bParameter = FALSE; nParameter < nParameters; nParameter++)
  { if ((pTMParameter = m_pLayoutValues[0].GetAt((nIndex=m_pLayoutValues[0].Find(szParameters.GetAt(nParameter))))) && (!pTMEnvironment  ||  !pTMParameter -> Compare(m_pLayoutValues[1].GetAt(nIndex))))
    { if (pTMParameter -> GetRawValue(0,nParameterValue,nParameterStatus) &&  pTMParameter -> GetValueAsText(GetDatabase(),0,pTMParameter -> GetAttributes(),(!(pTMParameter -> GetAttributes() & TMPARAMETER_CALIBRATION_STATUS) &&  GetFilterDigits(nFilterDigits) &&  nFilterDigits > 0) ? nFilterDigits:(((pDatabaseTMParameter=(((pTMParameter -> GetAttributes() & TMPARAMETER_CALIBRATION_NONE) && (pTMParameter -> GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT)) || (pTMParameter -> GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL)) ? GetDatabase() -> GetTMParameters() -> GetAt(GetDatabase() -> GetTMParameters() -> Find(pTMParameter -> GetTag())):(CDatabaseTMParameter *) NULL) &&  pDatabaseTMParameter -> GetDecimalDigits() > 0) ? pDatabaseTMParameter -> GetDecimalDigits():-1),szParameterValue,bOutSet,FALSE))
      { if ((!GetFilterStatus(nFilterStatus) || (nFilterStatus & TMPARAMETER_STATUS_INVALID) || (nParameterStatus & TMPARAMETER_STATUS_VALID)) &&  GetFilterColors(nFilterColors))
        { if ((pAttribute = m_wndContentCtrl.m_pContentTextAttributes.GetAt(nParameter)) != (CTextViewAttribute *) NULL)
          { nFilterColor = (nParameterStatus & TMPARAMETER_STATUS_NOLIMIT) ? nFilterColors.GetAt(POD_OOLCOLOR_NOLIMIT):0;
            nFilterColor = (nParameterStatus & TMPARAMETER_STATUS_SOFTLIMIT) ? nFilterColors.GetAt(POD_OOLCOLOR_SOFTLIMIT):nFilterColor;
            nFilterColor = (nParameterStatus & TMPARAMETER_STATUS_HARDLIMIT) ? nFilterColors.GetAt(POD_OOLCOLOR_HARDLIMIT):nFilterColor;
            nFilterColor = (nParameterStatus & TMPARAMETER_STATUS_DELTALIMIT) ? nFilterColors.GetAt(POD_OOLCOLOR_DELTALIMIT):nFilterColor;
            nFilterColor = (nParameterStatus & TMPARAMETER_STATUS_CONSISTENCYLIMIT) ? nFilterColors.GetAt(POD_OOLCOLOR_CONSISTENCYLIMIT):nFilterColor;
            pAttribute -> SetColumnColor(nColumn,nFilterColor);
          }
          SetText(nParameter,nColumn,(bOutSet) ? ((pTMParameter -> GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) ? (szParameterValue+GetDatabase() -> GetTMNumCalTablePointOutsideText()):((pTMParameter -> GetAttributes() & TMPARAMETER_CALIBRATION_STATUS) ? (szParameterValue+GetDatabase() -> GetTMTxtCalTablePointOutsideText()):szParameterValue)):szParameterValue);
          bParameter = TRUE;
          continue;
        }
      }
      SetText(nParameter,nColumn,EMPTYSTRING);
      bParameter = TRUE;
    }
  }
  if (nParameter == nParameters  &&  nParameters > 0  &&  bParameter)
  { for (m_pLayoutValues[1].Copy(&m_pLayoutValues[0]); m_wndToolTip.IsVisibleAtPoint(ptToolTip); )
    { for (nRow = PointToRow(ptToolTip),nColumn = PointToColumn(ptToolTip),szToolTip[0] = ConstructToolTipTitle(nRow),szToolTip[1] = ConstructToolTipText(nRow,(GetColumns(szColumns) &&  nColumn >= 0  &&  nColumn < szColumns.GetSize()) ? szColumns.GetAt(nColumn):EMPTYSTRING); !szToolTip[0].IsEmpty() ||  !szToolTip[1].IsEmpty(); )
      { m_wndToolTip.Update(szToolTip[0],szToolTip[1]);
        break;
      }
      break;
    }
    return TRUE;
  }
  return FALSE;
}

VOID CPODParametersView::Reset(CTMEnvironment *pTMEnvironment)
{
  CTextViewLock  cLock(this);

  m_pLayoutValues[0].Reset();
  m_pLayoutValues[1].Reset();
  Update();
}

BOOL CPODParametersView::GetPrintProperties(CONST CPODLayout &cLayout,CStringArray &szColumns,CStringArray &szContents,CTextViewAttributes &pAttributes,CTMParameters &pValues,CPtrArray &pFonts) CONST
{
  LOGFONT  *plfFont[3];
  CTextViewLock  cLock(this);

  if (cLayout.Compare(&m_cLayout))
  { if ((plfFont[0] = (LOGFONT *) GlobalAlloc(GPTR,sizeof(LOGFONT))))
    { if ((plfFont[1] = (LOGFONT *) GlobalAlloc(GPTR,sizeof(LOGFONT))))
      { if ((plfFont[2] = (LOGFONT *) GlobalAlloc(GPTR,sizeof(LOGFONT))))
        { if (GetColumns(szColumns) &&  GetContent(szContents,pAttributes))
          { if (GetTitleFont(plfFont[0]) &&  GetTextFont(plfFont[1]) &&  GetTextFont(plfFont[2],TRUE))
            { if (pValues.Copy(&m_pLayoutValues[0]))
              { pFonts.Add(plfFont[0]);
                pFonts.Add(plfFont[1]);
                pFonts.Add(plfFont[2]);
                return TRUE;
              }  
            }
          }
          GlobalFree(plfFont[2]);
        }
        GlobalFree(plfFont[1]);
      }
      GlobalFree(plfFont[0]);
    }
  }
  return FALSE;
}

BOOL CPODParametersView::AdjustColumns()
{
  CDC  *pDC;
  INT  nItem;
  INT  nItems;
  INT  nWidth;
  INT  nColumn;
  INT  nColumns;
  CFont  cFont;
  CFont  *pOldFont;
  CString  szText;
  LOGFONT  lfFont;
  CUIntArray  nWidths[2];
  CStringArray  szColumns;
  CTextViewLock  cLock(this);

  if ((pDC = (IsWindow(GetSafeHwnd())) ? GetDC():(CDC *) NULL))
  { for (nColumn = 0,nColumns = (GetColumns(szColumns) &&  CalcColumnWidths(szColumns,nWidths[0])) ? (INT) szColumns.GetSize():-1; nColumn < nColumns; nColumn++)
    { for ( ; !szColumns.GetAt(nColumn).Compare(STRING(IDS_POD_PARAMETERSHEADER_VALUE)) &&  GetTextFont(&lfFont,TRUE); )
      { SetColumnFont(nColumn,&lfFont);
        break;
      }
      if ((pOldFont = (szColumns.GetAt(nColumn) != STRING(IDS_POD_PARAMETERSHEADER_VALUE) ||  !cFont.CreateFontIndirect(&lfFont)) ? pDC -> SelectObject(&m_wndContentCtrl.m_cFont):pDC -> SelectObject(&cFont)))
      { for (nItem = 0,nItems = GetTextCount(),nWidth = m_wndHeaderCtrl.CalcColumnExtent(szColumns.GetAt(nColumn)).cx; nItem < nItems; nItem++)
        { nWidth = (GetText(nItem,nColumn,szText)) ? max(pDC -> GetTextExtent(szText).cx,nWidth):nWidth;
          continue;
        }
        nWidth = LOWORD(GetTextIndents())+nWidth+HIWORD(GetTextIndents());
        nWidth = (nColumn > 0) ? max((INT) (nWidths[0].GetAt(nColumn)-nWidths[0].GetAt(nColumn-1)),nWidth):max((INT) nWidths[0].GetAt(0),nWidth);
        nWidths[1].SetAtGrow(nColumn,(nColumn > 0) ? (nWidths[1].GetAt(nColumn-1)+nWidth):nWidth);
        pDC -> SelectObject(pOldFont);
        cFont.DeleteObject();
        continue;
      }
      cFont.DeleteObject();
      break;
    }
    if (nColumn == nColumns)
    { if (SetColumns(szColumns,nWidths[1]))
      { ReleaseDC(pDC);
        return TRUE;
      }
    }
    ReleaseDC(pDC);
  }
  return FALSE;
}

CPODWnd *CPODParametersView::GetParent() CONST
{
  return((CPODWnd *) CTextView::GetParent());
}

INT CPODParametersView::LookupColumnNames(CStringArray &szColumns) CONST
{
  szColumns.RemoveAll();
  szColumns.Add(STRING(IDS_POD_PARAMETERSHEADER_ID));
  szColumns.Add(STRING(IDS_POD_PARAMETERSHEADER_DESCRIPTION));
  szColumns.Add(STRING(IDS_POD_PARAMETERSHEADER_VALUE));
  szColumns.Add(STRING(IDS_POD_PARAMETERSHEADER_UNIT));
  return((INT) szColumns.GetSize());
}

BOOL CPODParametersView::CalcColumnWidths(CUIntArray &nWidths)
{
  CStringArray  szColumns;

  return((GetColumns(szColumns)) ? CalcColumnWidths(szColumns,nWidths):FALSE);
}
BOOL CPODParametersView::CalcColumnWidths(CONST CStringArray &szColumns,CUIntArray &nWidths)
{
  CDC  *pDC;
  INT  nColumn;
  INT  nColumns;
  CFont  cFont[2];
  CFont  *pOldFont;
  LOGFONT  lfFont[2];
  TEXTMETRIC  tmFont;
  CUIntArray  nColumnWidths;

  if ((pDC = GetDC()))
  { for (nColumn = 0,nColumns = (INT) szColumns.GetSize(),nWidths.RemoveAll(); nColumn < nColumns; nColumn++)
    { if ((pOldFont = (GetTitleFont(&lfFont[0]) &&  cFont[0].CreateFontIndirect(&lfFont[0])) ? pDC -> SelectObject(&cFont[0]):(CFont *) NULL))
      { nColumnWidths.SetAtGrow(nColumn,(nColumn < nColumnWidths.GetSize()) ? max(pDC -> GetTextExtent(szColumns.GetAt(nColumn)).cx,(INT) nColumnWidths.GetAt(nColumn)):pDC -> GetTextExtent(szColumns.GetAt(nColumn)).cx);
        pDC -> SelectObject(pOldFont);
        cFont[0].DeleteObject();
      }
      if ((pOldFont = (GetTextFont(&lfFont[1],szColumns.GetAt(nColumn) == STRING(IDS_POD_PARAMETERSHEADER_VALUE)) &&  cFont[1].CreateFontIndirect(&lfFont[1])) ? pDC -> SelectObject(&cFont[1]):(CFont *) NULL))
      { for (pDC -> GetTextMetrics(&tmFont); szColumns.GetAt(nColumn) == STRING(IDS_POD_PARAMETERSHEADER_ID); )
        { nColumnWidths.SetAtGrow(nColumn,(nColumn < nColumnWidths.GetSize()) ? max(GetDatabase() -> GetPODIDColumnCharWidth()*tmFont.tmAveCharWidth,(INT) nColumnWidths.GetAt(nColumn)):(GetDatabase() -> GetPODIDColumnCharWidth()*tmFont.tmAveCharWidth));
          break;
        }
        for ( ; szColumns.GetAt(nColumn) == STRING(IDS_POD_PARAMETERSHEADER_DESCRIPTION); )
        { nColumnWidths.SetAtGrow(nColumn,(nColumn < nColumnWidths.GetSize()) ? max(GetDatabase() -> GetPODDescriptionColumnCharWidth()*tmFont.tmAveCharWidth,(INT) nColumnWidths.GetAt(nColumn)):(GetDatabase() -> GetPODDescriptionColumnCharWidth()*tmFont.tmAveCharWidth));
          break;
        }
        for ( ; szColumns.GetAt(nColumn) == STRING(IDS_POD_PARAMETERSHEADER_VALUE); )
        { nColumnWidths.SetAtGrow(nColumn,(nColumn < nColumnWidths.GetSize()) ? max(GetDatabase() -> GetPODValueColumnCharWidth()*tmFont.tmAveCharWidth,(INT) nColumnWidths.GetAt(nColumn)):(GetDatabase() -> GetPODValueColumnCharWidth()*tmFont.tmAveCharWidth));
          break;
        }
        for ( ; szColumns.GetAt(nColumn) == STRING(IDS_POD_PARAMETERSHEADER_UNIT); )
        { nColumnWidths.SetAtGrow(nColumn,(nColumn < nColumnWidths.GetSize()) ? max(GetDatabase() -> GetPODUnitColumnCharWidth()*tmFont.tmAveCharWidth,(INT) nColumnWidths.GetAt(nColumn)):(GetDatabase() -> GetPODUnitColumnCharWidth()*tmFont.tmAveCharWidth));
          break;
        }
        pDC -> SelectObject(pOldFont);
        cFont[1].DeleteObject();
      }
      nWidths.SetAtGrow(nColumn,(nColumn > 0) ? (LOWORD(GetTextIndents())+nWidths.GetAt(nColumn-1)+nColumnWidths.GetAt(nColumn)+HIWORD(GetTextIndents())):(LOWORD(GetTextIndents())+nColumnWidths.GetAt(nColumn)+HIWORD(GetTextIndents())));
    }
    ReleaseDC(pDC);
    return TRUE;
  }
  return FALSE;
}

INT CPODParametersView::FindColumnIndex(LPCTSTR pszColumn) CONST
{
  INT  nColumn;
  INT  nColumns;
  CStringArray  szColumns;

  for (nColumn = 0,nColumns = LookupColumnNames(szColumns); nColumn < nColumns; nColumn++)
  { if (szColumns.GetAt(nColumn) == pszColumn) break;
    continue;
  }
  return((nColumn < nColumns) ? nColumn:-1);
}

UINT CPODParametersView::PointToRow(CONST POINT &point) CONST
{
  INT  nRow;
  INT  nColumn;

  return((FindTextFromPoint(point,nRow,nColumn,FALSE) &&  nRow < GetTextCount()) ? nRow:-1);
}

UINT CPODParametersView::PointToColumn(CONST POINT &point) CONST
{
  INT  nRow;
  INT  nColumn;

  return((FindTextFromPoint(point,nRow,nColumn,FALSE) &&  nRow < GetTextCount()) ? nColumn:-1);
}

CString CPODParametersView::ConstructToolTipTitle(INT nRow) CONST
{
  CString  szTitle;
  CStringArray  szParameters;

  szTitle.Format(STRING(IDS_POD_TOOLTIP_PARAMETERSTITLE),(nRow < m_cLayout.GetParameters(szParameters)) ? (LPCTSTR) szParameters.GetAt(nRow):EMPTYSTRING);
  return szTitle;
}

CString CPODParametersView::ConstructToolTipText(INT nRow,LPCTSTR pszColumn) CONST
{
  UINT  nStatus;
  BOOL  bOutSet;
  CString  szText;
  CString  szType;
  CString  szWidth;
  CString  szStatus;
  CString  szCalTable;
  CString  szValue[4];
  CString  szValueChange;
  CString  szValueUpdate;
  ULONGLONG  nValue;
  CStringArray  szParameters;
  CTMParameter  *pTMParameter;
  CDatabaseTMParameter  *pDatabaseTMParameter;

  if (nRow < m_cLayout.GetParameters(szParameters))
  { if (!lstrcmp(pszColumn,STRING(IDS_POD_PARAMETERSHEADER_ID)))
    { if ((pDatabaseTMParameter = GetDatabase() -> GetTMParameters() -> GetAt(GetDatabase() -> GetTMParameters() -> Find(szParameters.GetAt(nRow)))))
      { for (szType.Format(STRING(IDS_POD_TOOLTIP_TYPE),CDatabaseEngine::TranslateParameterTypeCode(pDatabaseTMParameter -> GetAttributes(),FALSE)); szType.GetLength() < lstrlen(STRING(IDS_POD_TOOLTIP_TYPE)); )
        { szType.Empty();
          break;
        }
        szWidth.Format(STRING(IDS_POD_TOOLTIP_WIDTH),pDatabaseTMParameter -> GetWidth());
        szText = (!szType.IsEmpty()) ? (szType+EOL+szWidth):szWidth;
      }
      return szText;
    }
    if (!lstrcmp(pszColumn,STRING(IDS_POD_PARAMETERSHEADER_DESCRIPTION)))
    { if ((pDatabaseTMParameter = GetDatabase() -> GetTMParameters() -> GetAt(GetDatabase() -> GetTMParameters() -> Find(szParameters.GetAt(nRow)))))
      { szText.Format(STRING(IDS_POD_TOOLTIP_DESCRIPTION),(LPCTSTR) pDatabaseTMParameter -> GetDetails());
        szText = (pDatabaseTMParameter -> GetDetails().IsEmpty()) ? STRING(IDS_POD_TOOLTIP_NODESCRIPTION):szText;
      }
      return szText;
    }
    if (!lstrcmp(pszColumn,STRING(IDS_POD_PARAMETERSHEADER_VALUE)))
    { if ((pTMParameter = m_pLayoutValues[0].GetAt(m_pLayoutValues[0].Find(szParameters.GetAt(nRow)))))
      { if ((pDatabaseTMParameter = GetDatabase() -> GetTMParameters() -> GetAt(GetDatabase() -> GetTMParameters() -> Find(szParameters.GetAt(nRow)))))
        { if (pTMParameter -> IsInitialized() &&  pTMParameter -> GetRawValue(0,nValue,nStatus,szCalTable))
          { if ((pTMParameter -> GetAttributes() & TMPARAMETER_CODING_BITPATTERN) || (pTMParameter -> GetAttributes() & TMPARAMETER_CODING_INVERSEBITPATTERN))
            { pTMParameter -> GetValueAsText(GetDatabase(),0,(pTMParameter -> GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_DECIMAL | TMPARAMETER_RADIX_HEXADECIMAL)) | TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_RADIX_BINARY,-1,szValue[0]);
              szValue[1].Format(STRING(IDS_POD_TOOLTIP_CODEDVALUE),(LPCTSTR) szValue[0],STRING(IDS_POD_TOOLTIP_BITVALUE));
            }
            if ((pTMParameter -> GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) || (pTMParameter -> GetAttributes() & TMPARAMETER_CODING_COMPLEMENTCOMPLEX))
            { pTMParameter -> GetValueAsText(GetDatabase(),0,(pTMParameter -> GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_HEXADECIMAL)) | TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_RADIX_DECIMAL,-1,szValue[0]);
              szValue[1].Format(STRING(IDS_POD_TOOLTIP_CODEDVALUE),(LPCTSTR) szValue[0],(pTMParameter -> GetAttributes() & TMPARAMETER_CODING_SIGNEDINTEGER) ? STRING(IDS_POD_TOOLTIP_SIGNEDVALUE):STRING(IDS_POD_TOOLTIP_COMPLEMENTVALUE));
            }
            if (pTMParameter -> GetAttributes() & TMPARAMETER_CODING_UNSIGNEDINTEGER)
            { pTMParameter -> GetValueAsText(GetDatabase(),0,(pTMParameter -> GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_HEXADECIMAL)) | TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_RADIX_DECIMAL,-1,szValue[0]);
              szValue[1].Format(STRING(IDS_POD_TOOLTIP_CODEDVALUE),(LPCTSTR) szValue[0],STRING(IDS_POD_TOOLTIP_UNSIGNEDVALUE));
            }
            if (pTMParameter -> GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT)
            { pTMParameter -> GetValueAsText(GetDatabase(),0,(pTMParameter -> GetAttributes() & ~(TMPARAMETER_CALIBRATION_NUMERICAL | TMPARAMETER_CALIBRATION_STATUS | TMPARAMETER_RADIX_BINARY | TMPARAMETER_RADIX_OCTAL | TMPARAMETER_RADIX_HEXADECIMAL)) | TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_RADIX_DECIMAL,-1,szValue[0]);
              szValue[1].Format(STRING(IDS_POD_TOOLTIP_CODEDVALUE),(LPCTSTR) szValue[0],STRING(IDS_POD_TOOLTIP_FLOATINGVALUE));
            }
            if ((pTMParameter -> GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_FLOATINGPOINT)) == 0)
            { pTMParameter -> GetValueAsText(GetDatabase(),0,TMPARAMETER_CALIBRATION_NONE | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_RADIX_DECIMAL,-1,szValue[0]);
              szValue[1].Format(STRING(IDS_POD_TOOLTIP_CODEDVALUE),(LPCTSTR) szValue[0],STRING(IDS_POD_TOOLTIP_UNSIGNEDVALUE));
            }
            for (szValue[0].Format(STRING(IDS_POD_TOOLTIP_RAWVALUE),nValue),pTMParameter -> GetValueAsText(GetDatabase(),0,pTMParameter -> GetAttributes(),((((pTMParameter -> GetAttributes() & TMPARAMETER_CODING_FLOATINGPOINT) && (pTMParameter -> GetAttributes() & TMPARAMETER_CALIBRATION_NONE)) || (pTMParameter -> GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL)) &&  pDatabaseTMParameter -> GetDecimalDigits() > 0) ? pDatabaseTMParameter -> GetDecimalDigits():-1,szValue[3],bOutSet,FALSE),szValue[2].Format((pTMParameter -> GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) ? STRING(IDS_POD_TOOLTIP_CALIBRATEDNUMERICALVALUE):STRING(IDS_POD_TOOLTIP_CALIBRATEDSTATUSVALUE),(LPCTSTR) (szValue[3]=(bOutSet) ? ((pTMParameter -> GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) ? (szValue[3]+GetDatabase() -> GetTMNumCalTablePointOutsideText()):((pTMParameter -> GetAttributes() & TMPARAMETER_CALIBRATION_STATUS) ? (szValue[3]+GetDatabase() -> GetTMTxtCalTablePointOutsideText()):szValue[3])):szValue[3]),(LPCTSTR) szCalTable,(bOutSet) ? ((pTMParameter -> GetAttributes() & TMPARAMETER_INTERPRETATION_EXTRAPOLATE) ? STRING(IDS_POD_TOOLTIP_EXTRPOLATEDVALUE):STRING(IDS_POD_TOOLTIP_OUTSETVALUE)):STRING(IDS_POD_TOOLTIP_INSETVALUE)),szValueChange.Format(STRING(IDS_POD_TOOLTIP_VALUECHANGE),(LPCTSTR) pTMParameter -> GetLastChangeTime().FormatGmt(),(LPCTSTR) pTMParameter -> GetLastChangeTMUnit()),szValueUpdate.Format(STRING(IDS_POD_TOOLTIP_VALUEUPDATE),(LPCTSTR) pTMParameter -> GetLastUpdateTime().FormatGmt(),(LPCTSTR) pTMParameter -> GetLastUpdateTMUnit()),szStatus.Format(STRING(IDS_POD_TOOLTIP_STATUS),(nStatus & TMPARAMETER_STATUS_GOOD) ? STRING(IDS_POD_TOOLTIP_GOODQUALITY):STRING(IDS_POD_TOOLTIP_BADQUALITY),(nStatus & TMPARAMETER_STATUS_SOFTLIMIT) ? STRING(IDS_POD_TOOLTIP_SOFTOOL):((nStatus & TMPARAMETER_STATUS_HARDLIMIT) ? STRING(IDS_POD_TOOLTIP_HARDOOL):((nStatus & TMPARAMETER_STATUS_DELTALIMIT) ? STRING(IDS_POD_TOOLTIP_DELTAOOL):((nStatus & TMPARAMETER_STATUS_CONSISTENCYLIMIT) ? STRING(IDS_POD_TOOLTIP_CONSISTENCYOOL):STRING(IDS_POD_TOOLTIP_NOOOL)))),(nStatus & TMPARAMETER_STATUS_VALID) ? STRING(IDS_POD_TOOLTIP_VALID):STRING(IDS_POD_TOOLTIP_INVALID)); pTMParameter -> GetAttributes() & TMPARAMETER_NATURE_CONSTANT; )
            { for (szValue[3].Format(STRING(IDS_POD_TOOLTIP_RAWTEXT),(LPCTSTR) pDatabaseTMParameter -> GetConstValueAsText()); (pTMParameter -> GetAttributes() & (TMPARAMETER_CODING_BITPATTERN | TMPARAMETER_CODING_INVERSEBITPATTERN | TMPARAMETER_CODING_SIGNEDINTEGER | TMPARAMETER_CODING_COMPLEMENTCOMPLEX | TMPARAMETER_CODING_UNSIGNEDINTEGER | TMPARAMETER_CODING_FLOATINGPOINT)) == 0; )
              { szValue[0] = szValue[3];
                break;
              }
              szValueChange.Empty();
              szValueUpdate.Empty();
              szStatus.Empty();
              break;
            }
            szText = (((pTMParameter -> GetAttributes() & TMPARAMETER_CALIBRATION_NUMERICAL) || (pTMParameter -> GetAttributes() & TMPARAMETER_CALIBRATION_STATUS)) &&  lstrlen(szCalTable) > 0) ? ((!szValueChange.IsEmpty() &&  !szValueUpdate.IsEmpty() &&  !szStatus.IsEmpty()) ? (szValue[0]+EOL+szValue[1]+EOL+szValue[2]+EOL+szValueChange+EOL+szValueUpdate+EOL+szStatus):(szValue[0]+EOL+szValue[1]+EOL+szValue[2])):((!szValueChange.IsEmpty() &&  !szValueUpdate.IsEmpty() &&  !szStatus.IsEmpty()) ? (szValue[0]+EOL+szValue[1]+EOL+szValueChange+EOL+szValueUpdate+EOL+szStatus):(szValue[0]+EOL+szValue[1]));
            return szText;
          }
          szText = STRING(IDS_POD_TOOLTIP_NOVALUE);
        }
      }
    }
  }
  return szText;
}

BOOL CPODParametersView::LoadToolTipCursor()
{
  return(((m_hToolTipCursor = (HCURSOR) LoadImage(GetModuleHandle((LPCTSTR) NULL),MAKEINTRESOURCE(IDC_TOOLTIPCURSOR),IMAGE_CURSOR,0,0,LR_DEFAULTCOLOR))) ? TRUE:FALSE);
}

HCURSOR CPODParametersView::GetToolTipCursor() CONST
{
  return((!m_hToolTipCursor) ? (HCURSOR) (DWORD_PTR) GetClassLongPtr(GetSafeHwnd(),GCLP_HCURSOR):m_hToolTipCursor); 
}

BOOL CPODParametersView::FreeToolTipCursor()
{
  if (m_hToolTipCursor)
  { DestroyCursor(m_hToolTipCursor);
    m_hToolTipCursor = (HCURSOR) NULL;
    return TRUE;
  }
  return FALSE;
}

void CPODParametersView::PostNcDestroy()
{
  m_cLayout.RemoveAll();
  m_pLayoutValues[0].RemoveAll();
  m_pLayoutValues[1].RemoveAll();
  CTextView::PostNcDestroy();
}

BOOL CPODParametersView::Lock()
{
  return((IsWindow(GetSafeHwnd())) ? (GetParent() -> Lock() &&  CTextView::Lock()):CTextView::Lock());
}

BOOL CPODParametersView::Unlock()
{
  return((IsWindow(GetSafeHwnd())) ? (CTextView::Unlock() &&  GetParent() -> Unlock()):CTextView::Unlock());
}

BEGIN_MESSAGE_MAP(CPODParametersView, CTextView)
	//{{AFX_MSG_MAP(CPODParametersView)
	ON_WM_CREATE()
	ON_WM_SETCURSOR()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPODParametersView message handlers

int CPODParametersView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
  CTextViewLock  cLock(this);

  if (CTextView::OnCreate(lpCreateStruct) != -1)
  { LoadToolTipCursor();
    return 0;
  }
  return -1;
}

BOOL CPODParametersView::OnSetCursor(CWnd *pWnd,UINT nHitTest,UINT message)
{
  INT  nColumn;
  INT  nColumns;
  LONG  lDataFlag;
  POINT  ptCursor;
  CRect  rContent;
  CString  szColumn;
  CStringArray  szColumns;
  CTextViewLock  cLock(this);

  for (GetCursorPos(&ptCursor),m_wndContentCtrl.ScreenToClient(&ptCursor),m_wndContentCtrl.GetClientRect(rContent); rContent.PtInRect(ptCursor); )
  { if ((lDataFlag = GetParent() -> IsRetrievingData()) &&  HIWORD(lDataFlag))
    { SetCursor(LoadCursor((HINSTANCE) NULL,IDC_WAIT));
      return TRUE;
    }
    for (nColumn = PointToColumn(ptCursor),nColumns = (IsToolTipModeEnabled() &&  GetColumns(szColumns)) ? (INT) szColumns.GetSize():0; (szColumn = (nColumn >= 0  &&  nColumn < nColumns) ? szColumns.GetAt(nColumn):szColumn) == STRING(IDS_POD_PARAMETERSHEADER_ID) ||  szColumn == STRING(IDS_POD_PARAMETERSHEADER_DESCRIPTION) ||  szColumn == STRING(IDS_POD_PARAMETERSHEADER_VALUE); )
    { SetCursor(GetToolTipCursor());
      return TRUE;
    }
    break;
  }
  return CTextView::OnSetCursor(pWnd,nHitTest,message);
}

BOOL CPODParametersView::OnContentMessage(UINT message,WPARAM wParam,LPARAM lParam,LRESULT *pResult)
{
  INT  nRow;
  INT  nColumn;
  CFont  cFont[2];
  CPoint  ptToolTip;
  LOGFONT  lfFont[2];
  CString  szColumn;
  CString  szToolTip[2];
  CStringArray  szColumns;
  CTextViewLock  cLock(this);

  if (message == WM_SETFOCUS)
  { SetCurText((GetCurText() >= 0) ? GetCurText():0);
    return FALSE;
  }
  if (message == WM_KEYDOWN)
  { if (wParam == VK_TAB) GetParent() -> SetFocus();
    return FALSE;
  }
  if (message == WM_RBUTTONDOWN)
  { if (!GetParent() -> IsRetrievingData() ||  !HIWORD(GetParent() -> IsRetrievingData()))
    { for (nRow = PointToRow((ptToolTip=CPoint(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam)))),nColumn = PointToColumn(ptToolTip); (szColumn = (IsToolTipModeEnabled() &&  GetColumns(szColumns) &&  nColumn >= 0  &&  nColumn < szColumns.GetSize()) ? szColumns.GetAt(nColumn):EMPTYSTRING) == STRING(IDS_POD_PARAMETERSHEADER_ID) ||  szColumn == STRING(IDS_POD_PARAMETERSHEADER_DESCRIPTION) ||  szColumn == STRING(IDS_POD_PARAMETERSHEADER_VALUE); )
      { for (szToolTip[0] = ConstructToolTipTitle(nRow),szToolTip[1] = ConstructToolTipText(nRow,szColumn),GetTextFont(&lfFont[0]),GetTextFont(&lfFont[1]),lfFont[0].lfWeight = FW_BOLD,lfFont[1].lfWeight = FW_NORMAL; cFont[0].CreateFontIndirect(&lfFont[0]) &&  cFont[1].CreateFontIndirect(&lfFont[1]); )
        { m_wndToolTip.SetTitleFont(&cFont[0]);
          m_wndToolTip.SetTextFont(&cFont[1]);
          break;
        }
        m_wndToolTip.Create(&m_wndContentCtrl,ptToolTip,szToolTip[0],szToolTip[1]);
        break;
      }
    }
    return FALSE;
  }
  if (message == WM_RBUTTONUP)
  { m_wndToolTip.Destroy();
    return FALSE;
  }
  return FALSE;
}

void CPODParametersView::OnDestroy()
{
  CTextViewLock  cLock(this);

  FreeToolTipCursor();
  CTextView::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CPODFunctionsView

IMPLEMENT_DYNCREATE(CPODFunctionsView,CTextView)

CPODFunctionsView::CPODFunctionsView() : CTextView()
{
  m_tTag = 0;
  m_nValues = 0;
  m_bValues = FALSE;
  m_fValueData[0] = m_fValueData[1] = m_fValueData[2] = m_fValueData[3] = m_fValueData[4] = m_fValueData[5] = m_fValueData[6] = 0.0;
  m_tValueData[0] = m_tValueData[1] = m_tValueData[2] = m_tValueData[3] = m_tValueData[4] = m_tValueData[5] = m_tValueData[6] = 0;
  m_bValueData[0] = m_bValueData[1] = m_bValueData[2] = m_bValueData[3] = m_bValueData[4] = m_bValueData[5] = m_bValueData[6] = FALSE;
  m_hToolTipCursor = (HCURSOR) NULL;
  m_bToolTipMode = TRUE;
  m_szUpdate.Empty();
  m_tUpdate = 0;
  m_bUpdate = TRUE;
}

BOOL CPODFunctionsView::Create(CWnd *pParentWnd)
{
  CUIntArray  nWidths;
  CStringArray  szColumns;

  return((CTextView::Create(pParentWnd,CRect(0,0,0,0),TVS_HEADER | TVS_TOP | TVS_HSCROLL | TVS_VSCROLL | TVS_NOSELECTION | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE)) ? ((!GetColumnCount() &&  LookupColumnNames(szColumns) > 0  &&  CalcColumnWidths(szColumns,nWidths) > 0  &&  SetColumns(szColumns,nWidths)) ||  GetColumnCount() > 0):FALSE);
}

BOOL CPODFunctionsView::SetLayout(CONST CPODLayout &cLayout)
{
  CUIntArray  nWidths;
  CTextViewLock  cLock(this);

  return((IsWindow(GetSafeHwnd())) ? (CalcColumnWidths(nWidths) &&  SetLayout(cLayout,nWidths)):m_cLayout.Copy(&cLayout));
}
BOOL CPODFunctionsView::SetLayout(CONST CPODLayout &cLayout,CONST CUIntArray &nWidths)
{
  INT  nCount;
  INT  nColumn;
  INT  nColumns;
  INT  nFunction;
  INT  nFunctions;
  LOGFONT  lfFont;
  CString  szFunction;
  CUIntArray  nColumnWidths;
  CStringArray  szColumns;
  CStringArray  szFunctions[2];
  CTextViewAttribute  cAttribute[2];
  CTextViewLock  cLock(this);

  if (!IsWindow(GetSafeHwnd()))
  { if (LookupColumnNames(szColumns) &&  SetColumns(szColumns,nWidths))
    { m_cLayout.Copy(&cLayout);
      return TRUE;
    }
    return FALSE;
  }
  if (!m_cLayout.Compare(&cLayout) ||  !GetTextCount())
  { if (GetColumns(szColumns) && ((szColumns.GetSize() == nWidths.GetSize() &&  SetColumns(szColumns,nWidths)) || (szColumns.GetSize() != nWidths.GetSize() &&  CalcColumnWidths(szColumns,nColumnWidths) &&  SetColumns(szColumns,nColumnWidths))))
    { for (nFunction = 0,nFunctions = (m_cLayout.GetFunctions(szFunctions[0]) == cLayout.GetFunctions(szFunctions[1]) &&  GetTextCount() > 0) ? (INT) szFunctions[0].GetSize():-1; nFunction < nFunctions; nFunction++)
      { if (szFunctions[0].GetAt(nFunction) != szFunctions[1].GetAt(nFunction)) break;
        continue;
      }
      if (m_cLayout.Copy(&cLayout))
      { for (nColumn = 0,nColumns = (INT) szColumns.GetSize(); nColumn < nColumns; nColumn++)
        { if (!szColumns.GetAt(nColumn).Compare(STRING(IDS_POD_FUNCTIONSHEADER_VALUE)) &&  GetTextFont(&lfFont,TRUE))
          { SetColumnFont(nColumn,&lfFont);
            break;
          }
        }
        for (cAttribute[0].SetColumnColor(-1,(m_cLayout.GetFunctionsColor() == GetSysColor(COLOR_WINDOW)) ? GetDatabase() -> GetPODFunctionsColor():m_cLayout.GetFunctionsColor()); nFunction < nFunctions  ||  nFunctions < 0; )
        { for (nFunction = 0,nFunctions = (INT) szFunctions[1].GetSize(),nCount = GetTextCount(),DeleteAllText((!nFunctions) ? TRUE:FALSE); nFunction < nFunctions; nFunction++)
          { InsertText(nFunction,szFunctions[1].GetAt(nFunction)+GetColumnDelimiter(),&cAttribute[0],nFunction == nFunctions-1);
            continue;
          }
          for ( ; GetTextCount() > 0  &&  nCount > 0; )
          { AdjustColumns();
            break;
          }
          RecalcLayout();
          return((nFunction == nFunctions) ? TRUE:FALSE);
        }
        for (nFunction = 0,nFunctions = (INT) szFunctions[1].GetSize(); nFunction < nFunctions; nFunction++)
        { if (GetText(nFunction,szFunction,&cAttribute[1]) &&  !cAttribute[0].Compare(&cAttribute[1]))
          { SetText(nFunction,szFunction,&cAttribute[0]);
            continue;
          }
        }
        RecalcLayout();
        return TRUE;
      }
    }
    RecalcLayout();
    return FALSE;
  }
  return TRUE;
}

BOOL CPODFunctionsView::GetLayout(CPODLayout &cLayout) CONST
{
  CTextViewLock  cLock(this);

  return cLayout.Copy(&m_cLayout);
}
BOOL CPODFunctionsView::GetLayout(CPODLayout &cLayout,CUIntArray &nWidths) CONST
{
  CStringArray  szColumns;
  CTextViewLock  cLock(this);

  return((GetColumns(szColumns,nWidths)) ? cLayout.Copy(&m_cLayout):FALSE);
}

BOOL CPODFunctionsView::SetTitleFont(CONST LOGFONT *plfFont)
{
  LOGFONT  lfFont;
  CTextViewLock  cLock(this);

  if (!CTextView::GetTitleFont(&lfFont) ||  memcmp(plfFont,&lfFont,sizeof(LOGFONT)))
  { if (CTextView::SetTitleFont(plfFont))
    { AdjustColumns();
      return TRUE;
    }
    return FALSE;
  }
  return TRUE;
}

BOOL CPODFunctionsView::GetTitleFont(LOGFONT *plfFont) CONST
{
  CTextViewLock  cLock(this);

  return CTextView::GetTitleFont(plfFont);
}

BOOL CPODFunctionsView::SetTextFont(CONST LOGFONT *plfFont)
{
  LOGFONT  lfFont;
  CTextViewLock  cLock(this);

  if (!CTextView::GetTextFont(&lfFont) ||  memcmp(plfFont,&lfFont,sizeof(LOGFONT)))
  { if (CTextView::SetTextFont(plfFont))
    { AdjustColumns();
      return TRUE;
    }
    return FALSE;
  }
  return TRUE;
}

BOOL CPODFunctionsView::GetTextFont(LOGFONT *plfFont,BOOL bValues) CONST
{
  CTextViewLock  cLock(this);

  if (CTextView::GetTextFont(plfFont))
  { plfFont -> lfWeight = (bValues) ? FW_BOLD:plfFont -> lfWeight;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODFunctionsView::EnableToolTipMode(BOOL bEnable)
{
  m_bToolTipMode = bEnable;
  return TRUE;
}

BOOL CPODFunctionsView::IsToolTipModeEnabled() CONST
{
  return m_bToolTipMode;
}

BOOL CPODFunctionsView::SetFilterMode(UINT nMode)
{
  m_nFilterMode = nMode;
  return TRUE;
}

BOOL CPODFunctionsView::GetFilterMode(UINT &nMode) CONST
{
  nMode = m_nFilterMode;
  return TRUE;
}

BOOL CPODFunctionsView::SetFilterLimit(UINT nLimit)
{
  CTextViewLock  cLock(this);

  if (m_nFilterMode & POD_FILTER_LIMIT)
  { m_nFilterLimit = nLimit;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODFunctionsView::GetFilterLimit(UINT &nLimit) CONST
{
  CTextViewLock  cLock(this);

  if (m_nFilterMode & POD_FILTER_LIMIT)
  { nLimit = m_nFilterLimit;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODFunctionsView::SetFilterStatus(UINT nStatus)
{
  CTextViewLock  cLock(this);

  if (m_nFilterMode & POD_FILTER_STATUS)
  { m_nFilterStatus = nStatus;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODFunctionsView::GetFilterStatus(UINT &nStatus) CONST
{
  CTextViewLock  cLock(this);

  if (m_nFilterMode & POD_FILTER_STATUS)
  { nStatus = m_nFilterStatus;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODFunctionsView::SetFilterRange(CONST CTimeKey &tStartTime,CONST CTimeKey &tStopTime)
{
  CTextViewLock  cLock(this);

  if (m_nFilterMode & POD_FILTER_RANGE)
  { m_tFilterRange[0][0] = tStartTime.GetTime();
    m_tFilterRange[0][1] = tStopTime.GetTime();
    return TRUE;
  }
  return FALSE;
}

BOOL CPODFunctionsView::GetFilterRange(CTimeKey &tStartTime,CTimeKey &tStopTime) CONST
{
  CTextViewLock  cLock(this);

  if (m_nFilterMode & POD_FILTER_RANGE)
  { tStartTime = m_tFilterRange[0][0];
    tStopTime = m_tFilterRange[0][1];
    return TRUE;
  }
  return FALSE;
}

BOOL CPODFunctionsView::SetFilterDailyRange(CONST CTimeSpan &tStartTime,CONST CTimeSpan &tStopTime)
{
  CTextViewLock  cLock(this);

  if (m_nFilterMode & POD_FILTER_DAILYRANGE)
  { m_tFilterDailyRange[0] = tStartTime;
    m_tFilterDailyRange[1] = tStopTime;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODFunctionsView::GetFilterDailyRange(CTimeSpan &tStartTime,CTimeSpan &tStopTime) CONST
{
  CTextViewLock  cLock(this);

  if (m_nFilterMode & POD_FILTER_DAILYRANGE)
  { tStartTime = m_tFilterDailyRange[0];
    tStopTime = m_tFilterDailyRange[1];
    return TRUE;
  }
  return FALSE;
}

BOOL CPODFunctionsView::SetFilterPeriodicalRange(CONST CTimeKey &tStartTime,CONST CTimeSpan &tInterval,CONST CTimeKey &tStopTime)
{
  CTextViewLock  cLock(this);

  if (m_nFilterMode & POD_FILTER_PERIODICALRANGE)
  { m_tFilterRange[1][0] = tStartTime;
    m_tFilterRange[1][1] = tStopTime;
    m_tFilterPeriodical = tInterval;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODFunctionsView::GetFilterPeriodicalRange(CTimeKey &tStartTime,CTimeSpan &tInterval,CTimeKey &tStopTime) CONST
{
  CTextViewLock  cLock(this);

  if (m_nFilterMode & POD_FILTER_PERIODICALRANGE)
  { tStartTime = m_tFilterRange[1][0];
    tStopTime = m_tFilterRange[1][1];
    tInterval = m_tFilterPeriodical;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODFunctionsView::SetFilterDigits(UINT nDigits)
{
  m_nFilterDigits = nDigits;
  return TRUE;
}

BOOL CPODFunctionsView::GetFilterDigits(UINT &nDigits) CONST
{
  nDigits = m_nFilterDigits;
  return TRUE;
}

BOOL CPODFunctionsView::SetFilterColors()
{
  CTextViewLock  cLock(this);

  m_nFilterColors.RemoveAll();
  m_nFilterColors.InsertAt(POD_OOLCOLOR_NOLIMIT,VGA_COLOR_GRAY);
  m_nFilterColors.InsertAt(POD_OOLCOLOR_SOFTLIMIT,VGA_COLOR_RED);
  m_nFilterColors.InsertAt(POD_OOLCOLOR_HARDLIMIT,VGA_COLOR_LTRED);
  m_nFilterColors.InsertAt(POD_OOLCOLOR_DELTALIMIT,VGA_COLOR_MAGENTA);
  m_nFilterColors.InsertAt(POD_OOLCOLOR_CONSISTENCYLIMIT,VGA_COLOR_YELLOW);
  return TRUE;
}
BOOL CPODFunctionsView::SetFilterColors(CONST CUIntArray &nColors)
{
  CTextViewLock  cLock(this);

  m_nFilterColors.Copy(nColors);
  return TRUE;
}

BOOL CPODFunctionsView::GetFilterColors(CUIntArray &nColors) CONST
{
  CTextViewLock  cLock(this);

  nColors.Copy(m_nFilterColors);
  return TRUE;
}

BOOL CPODFunctionsView::Initialize(CTMEnvironment *pTMEnvironment,BOOL bBadData)
{
  return TRUE;
}
BOOL CPODFunctionsView::Initialize(CString &szTag,CTimeTag &tTag,BOOL bBadData)
{
  BOOL  bValue;
  CString  szValue;
  CTimeTag  tValue;
  CFloatArray  fValues;
  CTextViewLock  cLock(this);

  if (!GetValues(szValue,tValue,fValues,bValue) ||  bValue)
  { m_fValueData[0] = m_fValueData[1] = m_fValueData[2] = m_fValueData[3] = m_fValueData[4] = m_fValueData[5] = m_fValueData[6] = 0.0;
    m_tValueData[0] = m_tValueData[1] = m_tValueData[2] = m_tValueData[3] = m_tValueData[4] = m_tValueData[5] = m_tValueData[6] = 0;
    m_bValueData[0] = m_bValueData[1] = m_bValueData[2] = m_bValueData[3] = m_bValueData[4] = m_bValueData[5] = m_bValueData[6] = FALSE;
    m_nValues = 0;
    m_tUpdate = 0;
    m_szUpdate.Empty();
  }
  Update((CTMEnvironment *) NULL,bBadData);
  return TRUE;
}

BOOL CPODFunctionsView::Update(CTMEnvironment *pTMEnvironment,BOOL bBadData)
{
  INT  nRow;
  INT  nIndex;
  INT  nValue;
  INT  nValues;
  INT  nColumn;
  INT  nFunction;
  INT  nFunctions;
  BOOL  bExpression;
  UINT  nFilterDigits;
  CPoint  ptToolTip;
  double  fExpressionValue;
  CString  szExpressionTag;
  CString  szToolTip[2];
  COLORREF  nFilterColor;
  CTimeTag  tExpressionTag;
  CUIntArray  nFilterColors;
  CFloatArray  fExpressionValues;
  CStringArray  szColumns;
  CStringArray  szFunctions;
  CStringTools  cStringTools;
  CTextViewAttribute  *pAttribute;
  CTextViewLock  cLock(this);

  for (nValue = 0,nValues = (GetValues(szExpressionTag,tExpressionTag,fExpressionValues,bExpression)) ? (INT) fExpressionValues.GetSize():0; nValue < nValues; nValue++)
  { for (nFunction = 0,nFunctions = (!pTMEnvironment  || (pTMEnvironment -> GetTMUnit() -> IsValid() &&  pTMEnvironment -> GetTMUnit() -> GetTag() == szExpressionTag  &&  pTMEnvironment -> GetTMUnit() -> GetTimeTag() == tExpressionTag) || (m_szUpdate != szExpressionTag  ||  m_tUpdate != tExpressionTag)) ? (MAXPODFUNCTIONS-MINPODFUNCTIONS+1):-1,fExpressionValue = fExpressionValues[nValue]; nFunction < nFunctions; nFunction++)
    { if ((pTMEnvironment != (CTMEnvironment *) NULL  || (m_szUpdate.IsEmpty() &&  m_tUpdate == 0)) &&  m_bUpdate)
      { if (!lstrcmp(STRING(MINPODFUNCTIONS+nFunction),STRING(IDS_POD_FUNCTION_MINIMUM)))
        { if (!m_bValueData[0] ||  m_fValueData[0] > fExpressionValue)
          { m_fValueData[0] = fExpressionValue;
            m_tValueData[0] = tExpressionTag;
            m_bValueData[0] = TRUE;
          }
          continue;
        }
        if (!lstrcmp(STRING(MINPODFUNCTIONS+nFunction),STRING(IDS_POD_FUNCTION_MAXIMUM)))
        { if (!m_bValueData[1] ||  m_fValueData[1] < fExpressionValue)
          { m_fValueData[1] = fExpressionValue;
            m_tValueData[1] = tExpressionTag;
            m_bValueData[1] = TRUE;
          }
          continue;
        }
        if (!lstrcmp(STRING(MINPODFUNCTIONS+nFunction),STRING(IDS_POD_FUNCTION_AVERAGE)))
        { m_fValueData[2] = (m_fValueData[2]*(double) m_nValues+fExpressionValue)/(double) (m_nValues+1);
          m_tValueData[2] = tExpressionTag;
          m_bValueData[2] = TRUE;
          m_nValues = min(m_nValues+1,ULONGLONG_MAX-1);
          continue;
        }
        if (!lstrcmp(STRING(MINPODFUNCTIONS+nFunction),STRING(IDS_POD_FUNCTION_UPDATETIME)))
        { m_fValueData[3] = fExpressionValue;
          m_tValueData[3] = tExpressionTag;
          m_bValueData[3] = TRUE;
          continue;
        }
        if (!lstrcmp(STRING(MINPODFUNCTIONS+nFunction),STRING(IDS_POD_FUNCTION_CHANGETIME)))
        { if (!m_bValueData[4] ||  m_fValueData[4] != fExpressionValue)
          { m_fValueData[4] = fExpressionValue;
            m_tValueData[4] = tExpressionTag;
            m_bValueData[4] = TRUE;
          }
          continue;
        }
      }
    }
    for (nFunction = 0; nFunction < nFunctions; nFunction++)
    { if ((pTMEnvironment != (CTMEnvironment *) NULL  || (m_szUpdate.IsEmpty() &&  m_tUpdate == 0)) &&  m_bUpdate)
      { if (!lstrcmp(STRING(MINPODFUNCTIONS+nFunction),STRING(IDS_POD_FUNCTION_DELTA)))
        { if (m_bValueData[0] &&  m_bValueData[1])
          { m_fValueData[5] = m_fValueData[1]-m_fValueData[0];
            m_tValueData[5] = tExpressionTag;
            m_bValueData[5] = TRUE;
          }
        }
        if (!lstrcmp(STRING(MINPODFUNCTIONS+nFunction),STRING(IDS_POD_FUNCTION_VARIANCE)))
        { if (m_bValueData[2] &&  m_nValues > 0)
          { m_fValueData[6] = (m_fValueData[6]*(double) (m_nValues-1)+(fExpressionValue-m_fValueData[2])*(fExpressionValue-m_fValueData[2]))/(double) m_nValues;
            m_tValueData[6] = tExpressionTag;
            m_bValueData[6] = TRUE;
          }
        }
      }
    }
  }
  if (nValues > 0)
  { for (nFunction = 0,nFunctions = m_cLayout.GetFunctions(szFunctions); nFunction < nFunctions; nFunction++)
    { for (GetFilterColors(nFilterColors),nColumn = FindColumnIndex(STRING(IDS_POD_FUNCTIONSHEADER_VALUE)),nIndex = (lstrcmp(szFunctions.GetAt(nFunction),STRING(IDS_POD_FUNCTION_MINIMUM))) ? ((lstrcmp(szFunctions.GetAt(nFunction),STRING(IDS_POD_FUNCTION_MAXIMUM))) ? ((lstrcmp(szFunctions.GetAt(nFunction),STRING(IDS_POD_FUNCTION_AVERAGE))) ? ((lstrcmp(szFunctions.GetAt(nFunction),STRING(IDS_POD_FUNCTION_UPDATETIME))) ? ((lstrcmp(szFunctions.GetAt(nFunction),STRING(IDS_POD_FUNCTION_CHANGETIME))) ? ((lstrcmp(szFunctions.GetAt(nFunction),STRING(IDS_POD_FUNCTION_DELTA))) ? 6:5):4):3):2):1):0; (pAttribute = m_wndContentCtrl.m_pContentTextAttributes.GetAt(nFunction)); )
      { nFilterColor = nFilterColors.GetAt(POD_OOLCOLOR_NOLIMIT);
        pAttribute -> SetColumnColor(nColumn,nFilterColor);
        break;
      }
      if (m_bUpdate)
      { SetText(nFunction,nColumn,(m_bValueData[nIndex]) ? ((szFunctions.GetAt(nFunction) == STRING(IDS_POD_FUNCTION_UPDATETIME) ||  szFunctions.GetAt(nFunction) == STRING(IDS_POD_FUNCTION_CHANGETIME)) ? ((szFunctions.GetAt(nFunction) == STRING(IDS_POD_FUNCTION_UPDATETIME)) ? ((m_tValueData[3].GetTime() > 0) ? (LPCTSTR) m_tValueData[3].FormatGmt():EMPTYSTRING):((m_tValueData[4].GetTime() > 0) ? (LPCTSTR) m_tValueData[4].FormatGmt():EMPTYSTRING)):cStringTools.ConvertFloatToString(m_fValueData[nIndex],(GetFilterDigits(nFilterDigits) &&  nFilterDigits > 0) ? nFilterDigits:-1)):EMPTYSTRING);
        continue;
      }
    }
    for (m_szUpdate = szExpressionTag,m_tUpdate = tExpressionTag; m_wndToolTip.IsVisibleAtPoint(ptToolTip); )
    { for (nRow = PointToRow(ptToolTip),nColumn = PointToColumn(ptToolTip),szToolTip[0] = ConstructToolTipTitle(nRow),szToolTip[1] = ConstructToolTipText(nRow,(GetColumns(szColumns) &&  nColumn >= 0  &&  nColumn < szColumns.GetSize()) ? szColumns.GetAt(nColumn):EMPTYSTRING); !szToolTip[0].IsEmpty() ||  !szToolTip[1].IsEmpty(); )
      { m_wndToolTip.Update(szToolTip[0],szToolTip[1]);
        break;
      }
      break;
    }
    return TRUE;
  }
  if (!m_nValues)
  { for (nFunction = 0,nFunctions = m_cLayout.GetFunctions(szFunctions),nColumn = FindColumnIndex(STRING(IDS_POD_FUNCTIONSHEADER_VALUE)); nFunction < nFunctions; nFunction++)
    { SetText(nFunction,nColumn,EMPTYSTRING);
      continue;
    }
  }
  return FALSE;
}

VOID CPODFunctionsView::Reset(CTMEnvironment *pTMEnvironment)
{
  CTextViewLock  cLock(this);

  m_szTag.Empty();
  m_tTag = 0;
  m_nValues = 0;
  m_bValues = FALSE;
  m_fValueData[0] = m_fValueData[1] = m_fValueData[2] = m_fValueData[3] = m_fValueData[4] = m_fValueData[5] = m_fValueData[6] = 0.0;
  m_tValueData[0] = m_tValueData[1] = m_tValueData[2] = m_tValueData[3] = m_tValueData[4] = m_tValueData[5] = m_tValueData[6] = 0;
  m_bValueData[0] = m_bValueData[1] = m_bValueData[2] = m_bValueData[3] = m_bValueData[4] = m_bValueData[5] = m_bValueData[6] = FALSE;
  m_szUpdate.Empty();
  m_tUpdate = 0;
  Update();
}

BOOL CPODFunctionsView::SetValues(LPCTSTR pszTag,CONST CTimeTag &tTag,CONST CFloatArray &fValues,BOOL bInitialized)
{
  CTextViewLock  cLock(this);

  m_szTag = pszTag;
  m_tTag = tTag;
  m_fValues.Copy(fValues);
  m_bValues = bInitialized;
  return TRUE;
}

BOOL CPODFunctionsView::GetValues(CString &szTag,CTimeTag &tTag,CFloatArray &fValues,BOOL &bInitialized) CONST
{
  CTextViewLock  cLock(this);

  szTag = m_szTag;
  tTag = m_tTag;
  fValues.Copy(m_fValues);
  bInitialized = m_bValues;
  return((!szTag.IsEmpty() &&  tTag > 0  &&  fValues.GetSize() > 0) ? TRUE:FALSE);
}

VOID CPODFunctionsView::SetHoldFlag(BOOL bEnable)
{
  m_bUpdate = !bEnable;
}

BOOL CPODFunctionsView::GetHoldFlag() CONST
{
  return !m_bUpdate;
}

BOOL CPODFunctionsView::HasHoldFlag() CONST
{
  return TRUE;
}

BOOL CPODFunctionsView::GetPrintProperties(CONST CPODLayout &cLayout,CStringArray &szColumns,CStringArray &szContents,CTextViewAttributes &pAttributes,CPtrArray &pFonts) CONST
{
  LOGFONT  *plfFont[3];
  CTextViewLock  cLock(this);

  if (cLayout.Compare(&m_cLayout))
  { if ((plfFont[0] = (LOGFONT *) GlobalAlloc(GPTR,sizeof(LOGFONT))))
    { if ((plfFont[1] = (LOGFONT *) GlobalAlloc(GPTR,sizeof(LOGFONT))))
      { if ((plfFont[2] = (LOGFONT *) GlobalAlloc(GPTR,sizeof(LOGFONT))))
        { if (GetColumns(szColumns) &&  GetContent(szContents,pAttributes))
          { if (GetTitleFont(plfFont[0]) &&  GetTextFont(plfFont[1]) &&  GetTextFont(plfFont[2],TRUE))
            { pFonts.Add(plfFont[0]);
              pFonts.Add(plfFont[1]);
              pFonts.Add(plfFont[2]);
              return TRUE;
            }
          }
          GlobalFree(plfFont[2]);
        }
        GlobalFree(plfFont[1]);
      }
      GlobalFree(plfFont[0]);
    }
  }
  return FALSE;
}

BOOL CPODFunctionsView::AdjustColumns()
{
  CDC  *pDC;
  INT  nItem;
  INT  nItems;
  INT  nWidth;
  INT  nColumn;
  INT  nColumns;
  CFont  cFont;
  CFont  *pOldFont;
  CString  szText;
  LOGFONT  lfFont;
  CUIntArray  nWidths[2];
  CStringArray  szColumns;
  CTextViewLock  cLock(this);

  if ((pDC = (IsWindow(GetSafeHwnd())) ? GetDC():(CDC *) NULL))
  { for (nColumn = 0,nColumns = (GetColumns(szColumns) &&  CalcColumnWidths(szColumns,nWidths[0])) ? (INT) szColumns.GetSize():-1; nColumn < nColumns; nColumn++)
    { for ( ; !szColumns.GetAt(nColumn).Compare(STRING(IDS_POD_FUNCTIONSHEADER_VALUE)) &&  GetTextFont(&lfFont,TRUE); )
      { SetColumnFont(nColumn,&lfFont);
        break;
      }
      if ((pOldFont = (szColumns.GetAt(nColumn) != STRING(IDS_POD_FUNCTIONSHEADER_VALUE) ||  !cFont.CreateFontIndirect(&lfFont)) ? pDC -> SelectObject(&m_wndContentCtrl.m_cFont):pDC -> SelectObject(&cFont)))
      { for (nItem = 0,nItems = GetTextCount(),nWidth = m_wndHeaderCtrl.CalcColumnExtent(szColumns.GetAt(nColumn)).cx; nItem < nItems; nItem++)
        { nWidth = (GetText(nItem,nColumn,szText)) ? max(pDC -> GetTextExtent(szText).cx,nWidth):nWidth;
          continue;
        }
        nWidth = LOWORD(GetTextIndents())+nWidth+HIWORD(GetTextIndents());
        nWidth = (nColumn > 0) ? max((INT) (nWidths[0].GetAt(nColumn)-nWidths[0].GetAt(nColumn-1)),nWidth):max((INT) nWidths[0].GetAt(0),nWidth);
        nWidths[1].SetAtGrow(nColumn,(nColumn > 0) ? (nWidths[1].GetAt(nColumn-1)+nWidth):nWidth);
        pDC -> SelectObject(pOldFont);
        cFont.DeleteObject();
        continue;
      }
      cFont.DeleteObject();
      break;
    }
    if (nColumn == nColumns)
    { if (SetColumns(szColumns,nWidths[1]))
      { pDC -> SelectObject(pOldFont);
        ReleaseDC(pDC);
        return TRUE;
      }
    }
    ReleaseDC(pDC);
  }
  return FALSE;
}

CPODWnd *CPODFunctionsView::GetParent() CONST
{
  return((CPODWnd *) CTextView::GetParent());
}

INT CPODFunctionsView::LookupColumnNames(CStringArray &szColumns) CONST
{
  szColumns.RemoveAll();
  szColumns.Add(STRING(IDS_POD_FUNCTIONSHEADER_NAME));
  szColumns.Add(STRING(IDS_POD_FUNCTIONSHEADER_VALUE));
  return((INT) szColumns.GetSize());
}

BOOL CPODFunctionsView::CalcColumnWidths(CUIntArray &nWidths)
{
  CStringArray  szColumns;

  return((GetColumns(szColumns)) ? CalcColumnWidths(szColumns,nWidths):FALSE);
}
BOOL CPODFunctionsView::CalcColumnWidths(CONST CStringArray &szColumns,CUIntArray &nWidths)
{
  CDC  *pDC;
  INT  nColumn;
  INT  nColumns;
  INT  nFunction;
  INT  nFunctions;
  CFont  cFont[2];
  CFont  *pOldFont;
  LOGFONT  lfFont[2];
  CTimeTag  tTimeTag;
  TEXTMETRIC  tmFont;
  CUIntArray  nColumnWidths;

  if ((pDC = GetDC()))
  { for (nColumn = 0,nColumns = (INT) szColumns.GetSize(),nWidths.RemoveAll(); nColumn < nColumns; nColumn++)
    { if ((pOldFont = (GetTitleFont(&lfFont[0]) &&  cFont[0].CreateFontIndirect(&lfFont[0])) ? pDC -> SelectObject(&cFont[0]):(CFont *) NULL))
      { nColumnWidths.SetAtGrow(nColumn,(nColumn < nColumnWidths.GetSize()) ? max(pDC -> GetTextExtent(szColumns.GetAt(nColumn)).cx,(INT) nColumnWidths.GetAt(nColumn)):pDC -> GetTextExtent(szColumns.GetAt(nColumn)).cx);
        pDC -> SelectObject(pOldFont);
        cFont[0].DeleteObject();
      }
      if ((pOldFont = (GetTextFont(&lfFont[1],szColumns.GetAt(nColumn) == STRING(IDS_POD_FUNCTIONSHEADER_VALUE)) &&  cFont[1].CreateFontIndirect(&lfFont[1])) ? pDC -> SelectObject(&cFont[1]):(CFont *) NULL))
      { for (nFunction = 0,nFunctions = (szColumns.GetAt(nColumn) == STRING(IDS_POD_FUNCTIONSHEADER_NAME)) ? (MAXPODFUNCTIONS-MINPODFUNCTIONS):-1; nFunction <= nFunctions; nFunction = nFunction+1)
        { nColumnWidths.SetAtGrow(nColumn,(nColumn < nColumnWidths.GetSize()) ? max(pDC -> GetTextExtent(STRING(MINPODFUNCTIONS+nFunction)).cx,(INT) nColumnWidths.GetAt(nColumn)):pDC -> GetTextExtent(STRING(MINPODFUNCTIONS+nFunction)).cx);
          continue;
        }
        if (szColumns.GetAt(nColumn) == STRING(IDS_POD_FUNCTIONSHEADER_VALUE))
        { for (nColumnWidths.SetAtGrow(nColumn,(nColumn < nColumnWidths.GetSize()) ? max(pDC -> GetTextExtent(tTimeTag.FormatGmt()).cx,(INT) nColumnWidths.GetAt(nColumn)):pDC -> GetTextExtent(tTimeTag.FormatGmt()).cx); pDC -> GetTextMetrics(&tmFont); )
          { nColumnWidths.SetAtGrow(nColumn,(nColumn < nColumnWidths.GetSize()) ? max(GetDatabase() -> GetPODValueColumnCharWidth()*tmFont.tmAveCharWidth,(INT) nColumnWidths.GetAt(nColumn)):(GetDatabase() -> GetPODValueColumnCharWidth()*tmFont.tmAveCharWidth));
            break;
          }
        }
        pDC -> SelectObject(pOldFont);
        cFont[1].DeleteObject();
      }
      nWidths.SetAtGrow(nColumn,(nColumn > 0) ? (LOWORD(GetTextIndents())+nWidths.GetAt(nColumn-1)+nColumnWidths.GetAt(nColumn)+HIWORD(GetTextIndents())):(LOWORD(GetTextIndents())+nColumnWidths.GetAt(nColumn)+HIWORD(GetTextIndents())));
    }
    ReleaseDC(pDC);
    return TRUE;
  }
  return FALSE;
}

INT CPODFunctionsView::FindColumnIndex(LPCTSTR pszColumn) CONST
{
  INT  nColumn;
  INT  nColumns;
  CStringArray  szColumns;

  for (nColumn = 0,nColumns = LookupColumnNames(szColumns); nColumn < nColumns; nColumn++)
  { if (szColumns.GetAt(nColumn) == pszColumn) break;
    continue;
  }
  return((nColumn < nColumns) ? nColumn:-1);
}

UINT CPODFunctionsView::PointToRow(CONST POINT &point) CONST
{
  INT  nRow;
  INT  nColumn;

  return((FindTextFromPoint(point,nRow,nColumn,FALSE) &&  nRow < GetTextCount()) ? nRow:-1);
}

UINT CPODFunctionsView::PointToColumn(CONST POINT &point) CONST
{
  INT  nRow;
  INT  nColumn;

  return((FindTextFromPoint(point,nRow,nColumn,FALSE) &&  nRow < GetTextCount()) ? nColumn:-1);
}

CString CPODFunctionsView::ConstructToolTipTitle(INT nRow) CONST
{
  CString  szTitle;
  CStringArray  szFunctions;

  szTitle.Format(STRING(IDS_POD_TOOLTIP_FUNCTIONSTITLE),(nRow < m_cLayout.GetFunctions(szFunctions)) ? (LPCTSTR) szFunctions.GetAt(nRow):EMPTYSTRING);
  return szTitle;
}

CString CPODFunctionsView::ConstructToolTipText(INT nRow,LPCTSTR pszColumn) CONST
{
  CString  szText;
  CString  szTime;
  CString  szValue;
  CString  szResult;
  CStringArray  szFunctions;
  CStringTools  cStringTools;

  if (nRow < m_cLayout.GetFunctions(szFunctions))
  { if (!lstrcmp(pszColumn,STRING(IDS_POD_FUNCTIONSHEADER_NAME)))
    { if (szFunctions.GetAt(nRow) == STRING(IDS_POD_FUNCTION_DELTA))
      { szText = STRING(IDS_POD_FUNCTION_DELTATEXT);
        return szText;
      }
      if (szFunctions.GetAt(nRow) == STRING(IDS_POD_FUNCTION_MINIMUM))
      { szText = STRING(IDS_POD_FUNCTION_MINIMUMTEXT);
        return szText;
      }
      if (szFunctions.GetAt(nRow) == STRING(IDS_POD_FUNCTION_MAXIMUM))
      { szText = STRING(IDS_POD_FUNCTION_MAXIMUMTEXT);
        return szText;
      }
      if (szFunctions.GetAt(nRow) == STRING(IDS_POD_FUNCTION_AVERAGE))
      { szText = STRING(IDS_POD_FUNCTION_AVERAGETEXT);
        return szText;
      }
      if (szFunctions.GetAt(nRow) == STRING(IDS_POD_FUNCTION_VARIANCE))
      { szText = STRING(IDS_POD_FUNCTION_VARIANCETEXT);
        return szText;
      }
      if (szFunctions.GetAt(nRow) == STRING(IDS_POD_FUNCTION_UPDATETIME))
      { szText = STRING(IDS_POD_FUNCTION_UPDATETIMETEXT);
        return szText;
      }
      if (szFunctions.GetAt(nRow) == STRING(IDS_POD_FUNCTION_CHANGETIME))
      { szText = STRING(IDS_POD_FUNCTION_CHANGETIMETEXT);
        return szText;
      }
      return szText;
    }
    if (!lstrcmp(pszColumn,STRING(IDS_POD_FUNCTIONSHEADER_VALUE)))
    { if (szFunctions.GetAt(nRow) == STRING(IDS_POD_FUNCTION_MINIMUM))
      { szValue = cStringTools.ConvertFloatToString(m_fValueData[0]);
        szResult.Format(STRING(IDS_POD_TOOLTIP_UPDATEVALUE),(LPCTSTR) szValue);
        szTime.Format(STRING(IDS_POD_TOOLTIP_UPDATETIME),(LPCTSTR) m_tValueData[0].FormatGmt());
        szText = (m_bValueData[0]) ? ((m_tValueData[0].GetTime() > 0) ? (szResult+EOL+szTime):szResult):szText;
        return szText;
      }
      if (szFunctions.GetAt(nRow) == STRING(IDS_POD_FUNCTION_MAXIMUM))
      { szValue = cStringTools.ConvertFloatToString(m_fValueData[1]);
        szResult.Format(STRING(IDS_POD_TOOLTIP_UPDATEVALUE),(LPCTSTR) szValue);
        szTime.Format(STRING(IDS_POD_TOOLTIP_UPDATETIME),(LPCTSTR) m_tValueData[1].FormatGmt());
        szText = (m_bValueData[1]) ? ((m_tValueData[1].GetTime() > 0) ? (szResult+EOL+szTime):szResult):szText;
        return szText;
      }
      if (szFunctions.GetAt(nRow) == STRING(IDS_POD_FUNCTION_AVERAGE))
      { szValue = cStringTools.ConvertFloatToString(m_fValueData[2]);
        szResult.Format(STRING(IDS_POD_TOOLTIP_UPDATEVALUE),(LPCTSTR) szValue);
        szTime.Format(STRING(IDS_POD_TOOLTIP_UPDATETIME),(LPCTSTR) m_tValueData[2].FormatGmt());
        szText = (m_bValueData[2]) ? ((m_tValueData[2].GetTime() > 0) ? (szResult+EOL+szTime):szResult):szText;
        return szText;
      }
      if (szFunctions.GetAt(nRow) == STRING(IDS_POD_FUNCTION_UPDATETIME))
      { szValue = cStringTools.ConvertFloatToString(m_fValueData[3]);
        szResult.Format(STRING(IDS_POD_TOOLTIP_UPDATEVALUE),(LPCTSTR) szValue);
        szTime.Format(STRING(IDS_POD_TOOLTIP_UPDATETIME),(LPCTSTR) m_tValueData[3].FormatGmt());
        szText = (m_bValueData[3]) ? ((m_tValueData[3].GetTime() > 0) ? (szResult+EOL+szTime):szResult):szText;
        return szText;
      }
      if (szFunctions.GetAt(nRow) == STRING(IDS_POD_FUNCTION_CHANGETIME))
      { szValue = cStringTools.ConvertFloatToString(m_fValueData[4]);
        szResult.Format(STRING(IDS_POD_TOOLTIP_UPDATEVALUE),(LPCTSTR) szValue);
        szTime.Format(STRING(IDS_POD_TOOLTIP_UPDATETIME),(LPCTSTR) m_tValueData[4].FormatGmt());
        szText = (m_bValueData[4]) ? ((m_tValueData[4].GetTime() > 0) ? (szResult+EOL+szTime):szResult):szText;
        return szText;
      }
      if (szFunctions.GetAt(nRow) == STRING(IDS_POD_FUNCTION_DELTA))
      { szValue = cStringTools.ConvertFloatToString(m_fValueData[5]);
        szResult.Format(STRING(IDS_POD_TOOLTIP_UPDATEVALUE),(LPCTSTR) szValue);
        szTime.Format(STRING(IDS_POD_TOOLTIP_UPDATETIME),(LPCTSTR) m_tValueData[5].FormatGmt());
        szText = (m_bValueData[5]) ? ((m_tValueData[5].GetTime() > 0) ? (szResult+EOL+szTime):szResult):szText;
        return szText;
      }
      if (szFunctions.GetAt(nRow) == STRING(IDS_POD_FUNCTION_VARIANCE))
      { szValue = cStringTools.ConvertFloatToString(m_fValueData[6],-1);
        szResult.Format(STRING(IDS_POD_TOOLTIP_UPDATEVALUE),(LPCTSTR) szValue);
        szTime.Format(STRING(IDS_POD_TOOLTIP_UPDATETIME),(LPCTSTR) m_tValueData[6].FormatGmt());
        szText = (m_bValueData[6]) ? ((m_tValueData[6].GetTime() > 0) ? (szResult+EOL+szTime):szResult):szText;
        return szText;
      }
    }
  }
  return szText;
}

BOOL CPODFunctionsView::LoadToolTipCursor()
{
  return(((m_hToolTipCursor = (HCURSOR) LoadImage(GetModuleHandle((LPCTSTR) NULL),MAKEINTRESOURCE(IDC_TOOLTIPCURSOR),IMAGE_CURSOR,0,0,LR_DEFAULTCOLOR))) ? TRUE:FALSE);
}

HCURSOR CPODFunctionsView::GetToolTipCursor() CONST
{
  return((!m_hToolTipCursor) ? (HCURSOR) (DWORD_PTR) GetClassLongPtr(GetSafeHwnd(),GCLP_HCURSOR):m_hToolTipCursor); 
}

BOOL CPODFunctionsView::FreeToolTipCursor()
{
  if (m_hToolTipCursor)
  { DestroyCursor(m_hToolTipCursor);
    m_hToolTipCursor = (HCURSOR) NULL;
    return TRUE;
  }
  return FALSE;
}

void CPODFunctionsView::PostNcDestroy()
{
  m_cLayout.RemoveAll();
  CTextView::PostNcDestroy();
}

BOOL CPODFunctionsView::Lock()
{
  return((IsWindow(GetSafeHwnd())) ? (GetParent() -> Lock() &&  CTextView::Lock()):CTextView::Lock());
}

BOOL CPODFunctionsView::Unlock()
{
  return((IsWindow(GetSafeHwnd())) ? (CTextView::Unlock() &&  GetParent() -> Unlock()):CTextView::Unlock());
}

BEGIN_MESSAGE_MAP(CPODFunctionsView, CTextView)
	//{{AFX_MSG_MAP(CPODFunctionsView)
	ON_WM_CREATE()
	ON_WM_SETCURSOR()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPODFunctionsView message handlers

int CPODFunctionsView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
  CTextViewLock  cLock(this);

  if (CTextView::OnCreate(lpCreateStruct) != -1)
  { LoadToolTipCursor();
    return 0;
  }
  return -1;
}

BOOL CPODFunctionsView::OnSetCursor(CWnd *pWnd,UINT nHitTest,UINT message)
{
  INT  nColumn;
  INT  nColumns;
  LONG  lDataFlag;
  POINT  ptCursor;
  CRect  rContent;
  CString  szColumn;
  CStringArray  szColumns;
  CTextViewLock  cLock(this);

  for (GetCursorPos(&ptCursor),m_wndContentCtrl.ScreenToClient(&ptCursor),m_wndContentCtrl.GetClientRect(rContent); rContent.PtInRect(ptCursor); )
  { if ((lDataFlag = GetParent() -> IsRetrievingData()) &&  HIWORD(lDataFlag))
    { SetCursor(LoadCursor((HINSTANCE) NULL,IDC_WAIT));
      return TRUE;
    }
    for (nColumn = PointToColumn(ptCursor),nColumns = (IsToolTipModeEnabled() &&  GetColumns(szColumns)) ? (INT) szColumns.GetSize():0; (szColumn = (nColumn >= 0  &&  nColumn < nColumns) ? szColumns.GetAt(nColumn):szColumn) == STRING(IDS_POD_FUNCTIONSHEADER_NAME) ||  szColumn == STRING(IDS_POD_FUNCTIONSHEADER_VALUE); )
    { SetCursor(GetToolTipCursor());
      return TRUE;
    }
    break;
  }
  return CTextView::OnSetCursor(pWnd,nHitTest,message);
}

BOOL CPODFunctionsView::OnContentMessage(UINT message,WPARAM wParam,LPARAM lParam,LRESULT *pResult)
{
  INT  nRow;
  INT  nColumn;
  CFont  cFont[2];
  CPoint  ptToolTip;
  LOGFONT  lfFont[2];
  CString  szColumn;
  CString  szToolTip[2];
  CStringArray  szColumns;
  CTextViewLock  cLock(this);

  if (message == WM_SETFOCUS)
  { SetCurText((GetCurText() >= 0) ? GetCurText():0);
    return FALSE;
  }
  if (message == WM_KEYDOWN)
  { if (wParam == VK_TAB) GetParent() -> SetFocus();
    return FALSE;
  }
  if (message == WM_RBUTTONDOWN)
  { if (!GetParent() -> IsRetrievingData() ||  !HIWORD(GetParent() -> IsRetrievingData()))
    { for (nRow = PointToRow((ptToolTip=CPoint(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam)))),nColumn = PointToColumn(ptToolTip); (szColumn = (IsToolTipModeEnabled() &&  GetColumns(szColumns) &&  nColumn >= 0  &&  nColumn < szColumns.GetSize()) ? szColumns.GetAt(nColumn):EMPTYSTRING) == STRING(IDS_POD_FUNCTIONSHEADER_NAME) ||  szColumn == STRING(IDS_POD_FUNCTIONSHEADER_VALUE); )
      { for (szToolTip[0] = ConstructToolTipTitle(nRow),szToolTip[1] = ConstructToolTipText(nRow,szColumn),GetTextFont(&lfFont[0]),GetTextFont(&lfFont[1]),lfFont[0].lfWeight = FW_BOLD,lfFont[1].lfWeight = FW_NORMAL; cFont[0].CreateFontIndirect(&lfFont[0]) &&  cFont[1].CreateFontIndirect(&lfFont[1]); )
        { m_wndToolTip.SetTitleFont(&cFont[0]);
          m_wndToolTip.SetTextFont(&cFont[1]);
          break;
        }
        m_wndToolTip.Create(&m_wndContentCtrl,ptToolTip,szToolTip[0],szToolTip[1]);
        break;
      }
    }
    return FALSE;
  }
  if (message == WM_RBUTTONUP)
  { m_wndToolTip.Destroy();
    return FALSE;
  }
  return FALSE;
}

void CPODFunctionsView::OnDestroy()
{
  CTextViewLock  cLock(this);

  FreeToolTipCursor();
  CTextView::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// CPODWnd

IMPLEMENT_DYNAMIC(CPODWnd,CDisplayWnd)

CPODWnd::CPODWnd() : CDisplayWnd()
{
  SetType(DISPLAY_TYPE_POD);
  InitializeViews();
  SetFilterMode();
  SetFilterLimit();
  SetFilterDigits();
  SetFilterStatus();
  SetFilterColors();
  SetRetrieveMode();
  SetRetrieveSpeed();
  SetRetrieveInterval();
  SetRetrieveStartTime();
  SetRetrieveStopTime();
  SetUpdateInfo();
  SetHoldFlag();
}

BOOL CPODWnd::Create(CMDIFrameWnd *pParentWnd,LPCTSTR pszTitle,PDISPLAYINFO pDefaultInfo,BOOL bDefault) 
{
  if (CDisplayWnd::Create(pParentWnd,(!pszTitle) ? STRING(IDS_DISPLAY_TITLE_POD):pszTitle,pDefaultInfo -> rWnd,IDR_PODFRAME))
  { if (SetScope(pDefaultInfo -> nScope) &&  SetMode(pDefaultInfo -> nMode) &&  Customize(bDefault)) return TRUE;
    DestroyWindow();
  }
  return FALSE;
}

BOOL CPODWnd::SetLayout(LPCTSTR pszLayout)
{
  CPODLayout  cLayout;

  return LoadLayout(pszLayout,cLayout) &&  SetLayout(cLayout);
}
BOOL CPODWnd::SetLayout(CONST CPODLayout &cLayout)
{
  CStringArray  szFunctions;
  CStringArray  szParameters;

  if (m_wndDataView.SetLayout(cLayout) &&  m_wndParametersView.SetLayout(cLayout) &&  m_wndFunctionsView.SetLayout(cLayout))
  { m_bViews[2] = (cLayout.GetFunctions(szFunctions) > 0) ? TRUE:FALSE;
    m_bViews[1] = (cLayout.GetParameters(szParameters) > 0) ? TRUE:FALSE;
    m_bViews[0] = TRUE;
    RepositionViews();
    return TRUE;
  }
  return FALSE;
}
BOOL CPODWnd::SetLayout(LPCTSTR pszLayout,CONST CUIntArray &nDataViewWidths,CONST CUIntArray &nParametersViewWidths,CONST CUIntArray &nFunctionsViewWidths)
{
  CPODLayout  cLayout;

  return LoadLayout(pszLayout,cLayout) &&  SetLayout(cLayout,nDataViewWidths,nParametersViewWidths,nFunctionsViewWidths);
}
BOOL CPODWnd::SetLayout(CONST CPODLayout &cLayout,CONST CUIntArray &nDataViewWidths,CONST CUIntArray &nParametersViewWidths,CONST CUIntArray &nFunctionsViewWidths)
{
  CStringArray  szFunctions;
  CStringArray  szParameters;

  if (m_wndDataView.SetLayout(cLayout,nDataViewWidths) &&  m_wndParametersView.SetLayout(cLayout,nParametersViewWidths) &&  m_wndFunctionsView.SetLayout(cLayout,nFunctionsViewWidths))
  { m_bViews[2] = (cLayout.GetFunctions(szFunctions) > 0) ? TRUE:FALSE;
    m_bViews[1] = (cLayout.GetParameters(szParameters) > 0) ? TRUE:FALSE;
    m_bViews[0] = TRUE;
    RepositionViews();
    return TRUE;
  }
  return FALSE;
}

BOOL CPODWnd::GetLayout(CString &szLayout) CONST
{
  CPODLayout  cLayout;

  if (m_wndDataView.GetLayout(cLayout))
  { szLayout = cLayout.GetName();
    return TRUE;
  }
  return FALSE;
}
BOOL CPODWnd::GetLayout(CPODLayout &cLayout) CONST
{
  return m_wndDataView.GetLayout(cLayout);
}
BOOL CPODWnd::GetLayout(CString &szLayout,CUIntArray &nDataViewWidths,CUIntArray &nParametersViewWidths,CUIntArray &nFunctionsViewWidths) CONST
{
  CPODLayout  cLayout;

  return m_wndDataView.GetLayout(cLayout,nDataViewWidths) &&  m_wndParametersView.GetLayout(cLayout,nParametersViewWidths) &&  m_wndFunctionsView.GetLayout(cLayout,nFunctionsViewWidths) &&  GetLayout(szLayout);
}
BOOL CPODWnd::GetLayout(CPODLayout &cLayout,CUIntArray &nDataViewWidths,CUIntArray &nParametersViewWidths,CUIntArray &nFunctionsViewWidths) CONST
{
  return m_wndDataView.GetLayout(cLayout,nDataViewWidths) &&  m_wndParametersView.GetLayout(cLayout,nParametersViewWidths) &&  m_wndFunctionsView.GetLayout(cLayout,nFunctionsViewWidths);
}

BOOL CPODWnd::SetTitleFonts(CONST LOGFONT *plfDataFont,CONST LOGFONT *plfParametersFont,CONST LOGFONT *plfFunctionsFont)
{
  if (m_wndDataView.SetTitleFont(plfDataFont) &&  m_wndParametersView.SetTitleFont(plfParametersFont) &&  m_wndFunctionsView.SetTitleFont(plfFunctionsFont))
  { RepositionViews();
    return TRUE;
  }
  return FALSE;
}

BOOL CPODWnd::GetTitleFonts(LPLOGFONT plfDataFont,LPLOGFONT plfParametersFont,LPLOGFONT plfFunctionsFont) CONST
{
  return m_wndDataView.GetTitleFont(plfDataFont) &&  m_wndParametersView.GetTitleFont(plfParametersFont) &&  m_wndFunctionsView.GetTitleFont(plfFunctionsFont);
}

BOOL CPODWnd::SetItemsFonts(CONST LOGFONT *plfDataFont,CONST LOGFONT *plfParametersFont,CONST LOGFONT *plfFunctionsFont)
{
  if (m_wndDataView.SetTextFont(plfDataFont) &&  m_wndParametersView.SetTextFont(plfParametersFont) &&  m_wndFunctionsView.SetTextFont(plfFunctionsFont))
  { RepositionViews();
    return TRUE;
  }
  return FALSE;
}

BOOL CPODWnd::GetItemsFonts(LPLOGFONT plfDataFont,LPLOGFONT plfParametersFont,LPLOGFONT plfFunctionsFont) CONST
{
  return m_wndDataView.GetTextFont(plfDataFont) &&  m_wndParametersView.GetTextFont(plfParametersFont) &&  m_wndFunctionsView.GetTextFont(plfFunctionsFont);
}

BOOL CPODWnd::EnableToolTipMode(BOOL bEnable)
{
  return m_wndDataView.EnableToolTipMode(bEnable) &&  m_wndParametersView.EnableToolTipMode(bEnable) &&  m_wndFunctionsView.EnableToolTipMode(bEnable);
}

BOOL CPODWnd::IsToolTipModeEnabled() CONST
{
  return m_wndDataView.IsToolTipModeEnabled() &&  m_wndParametersView.IsToolTipModeEnabled() &&  m_wndFunctionsView.IsToolTipModeEnabled();
}

INT CPODWnd::GetSampleCount() CONST
{
  return m_wndDataView.GetTextCount();
}

BOOL CPODWnd::Start()
{
  if (((GetMode() == DISPLAY_MODE_REALTIME  &&  ProcessRealtimeData()) || (GetMode() == DISPLAY_MODE_HISTORY  &&  StartRetrieveData())) &&  StartSchedulePrintJobs())
  { Initialize(TRUE);
    UpdateAllPanes();
    return TRUE;
  }
  return FALSE;
}

BOOL CPODWnd::Prepare(BOOL bDialog)
{
  INT  nResult;

  if (bDialog)
  { if ((nResult = m_dlgOpen.Create(this)) == IDCANCEL  ||  nResult <= 0) MDIDestroy();
    return((nResult == IDOK  ||  nResult == IDCANCEL) ? TRUE:FALSE);
  }
  return TRUE;
}

BOOL CPODWnd::Initialize(BOOL bFlag)
{
  return CDisplayWnd::Initialize(bFlag);
}
BOOL CPODWnd::Initialize(CTMEnvironment *pTMEnvironment)
{
  UINT  nStatus;
  BOOL  bSuccess;

  for (bSuccess = m_wndDataView.Initialize(pTMEnvironment,((nStatus=(GetFilterStatus(nStatus)) ? nStatus:TMPARAMETER_STATUS_NONE) & TMPARAMETER_STATUS_BAD) ? TRUE:FALSE),bSuccess &= m_wndParametersView.Initialize(pTMEnvironment,(nStatus & TMPARAMETER_STATUS_BAD) ? TRUE:FALSE); m_wndFunctionsView.Initialize(pTMEnvironment,(nStatus & TMPARAMETER_STATUS_BAD) ? TRUE:FALSE); ) return bSuccess;
  return FALSE;
}
BOOL CPODWnd::Initialize(CString &szTag,CTimeTag &tTag)
{
  UINT  nStatus;
  BOOL  bSuccess;

  for (bSuccess = m_wndDataView.Initialize(szTag,tTag,((nStatus=(GetFilterStatus(nStatus)) ? nStatus:TMPARAMETER_STATUS_NONE) & TMPARAMETER_STATUS_BAD) ? TRUE:FALSE),bSuccess &= m_wndParametersView.Initialize(szTag,tTag,(nStatus & TMPARAMETER_STATUS_BAD) ? TRUE:FALSE),UpdateData(FALSE); m_wndFunctionsView.Initialize(szTag,tTag,(nStatus & TMPARAMETER_STATUS_BAD) ? TRUE:FALSE); ) return bSuccess;
  return FALSE;
}

BOOL CPODWnd::InitializeTMData(UINT nMode)
{
  for (StopRetrieveData(); (nMode == DISPLAY_MODE_REALTIME  &&  SetMode(DISPLAY_MODE_REALTIME) &&  ProcessRealtimeData()) || (nMode == DISPLAY_MODE_HISTORY  &&  SetMode(DISPLAY_MODE_HISTORY) &&  StartRetrieveData()); )
  { UpdateBars();
    return TRUE;
  }
  return FALSE;
}
BOOL CPODWnd::InitializeTMData(CTMParameters &pTMParameters,BOOL bBadData)
{
  CDisplayWnd  *pDisplayWnd;

  return((GetMode() == DISPLAY_MODE_HISTORY) ? (((pDisplayWnd = GetLink())) ? pDisplayWnd -> InitializeTMData(pTMParameters,bBadData):m_cRetrieveThread.InitializeTMData(pTMParameters,bBadData)):GetTMService() -> InitializeTMData(pTMParameters,bBadData));
}

BOOL CPODWnd::Check() CONST
{
  return CheckAccountPrivilege(PRIVILEGE_POD_USE);
}

VOID CPODWnd::Update()
{
  if (!Check())
  { ReportEvent(USER_INFORMATIONAL_DISPLAY_ACCESS_VIOLATION);
    DestroyWindow();
    return;
  }
  UpdateAllPanes();
  CDisplayWnd::Update();
}
BOOL CPODWnd::Update(CONST CTimeKey &tTimeKey,CTMEnvironment *pTMEnvironment,UINT nFlags)
{
  INT  nLink;
  INT  nLinks;
  UINT  nStatus;
  BOOL  bUpdate;
  BOOL  bBadData;
  CPtrArray  pLinks;
  CPODLayout  cLayout;
  CDisplayWnd  *pDisplayWnd;
  CDisplayLock  cLock(this);

  if (IsInitialized())
  { for (nLink = 0,nLinks = GetLinks(pLinks); nLink < nLinks; nLink++)
    { if ((pDisplayWnd = (CDisplayWnd *) pLinks.GetAt(nLink)) &&  pDisplayWnd -> IsInitialized())
      { pDisplayWnd -> Update(tTimeKey,pTMEnvironment,nFlags);
        continue;
      }
    }
    if (GetLayout(cLayout) &&  !cLayout.GetSize())
    { SetUpdateInfo();
      return FALSE;
    }
    for ( ; GetMode() == DISPLAY_MODE_REALTIME; )
    { if (pTMEnvironment -> GetTMUnit() -> GetTag() != STRING(IDS_TMUNIT_INTERACTIVE) &&  !pTMEnvironment -> GetTMUnit() -> IsValid() &&  !nFlags) return TRUE;
      break;
    }
    if (((nFlags & HISTORYFILE_SUCCESS) && ((nFlags & HISTORYFILE_TMUNIT) || (nFlags & HISTORYFILE_TMPARAMETERS))) ||  !nFlags)
    { for (bUpdate = m_wndDataView.Update(pTMEnvironment,(bBadData = (GetFilterStatus(nStatus) && (nStatus & TMPARAMETER_STATUS_BAD)) ? TRUE:FALSE)),m_wndParametersView.Update(pTMEnvironment,bBadData),UpdateData(FALSE),m_wndFunctionsView.Update(pTMEnvironment,bBadData); bUpdate; )
      { SetUpdateInfo(pTMEnvironment -> GetTMUnit() -> GetTag(),(pTMEnvironment -> GetTMUnit() -> IsValid()) ? pTMEnvironment -> GetTMUnit() -> GetTimeTag():CTimeTag(tTimeKey),pTMEnvironment -> GetTMUnit() -> GetUnitID(),pTMEnvironment -> GetTMUnit() -> GetQuality());
        return TRUE;
      }
    }
    return(((nFlags & HISTORYFILE_SUCCESS) &&  !(nFlags & HISTORYFILE_TMUNIT) &&  !(nFlags & HISTORYFILE_TMPARAMETERS)) ? TRUE:FALSE);
  }
  return FALSE;
}

VOID CPODWnd::Reset(CTMEnvironment *pTMEnvironment)
{
  CDisplayLock  cLock(this);

  if (IsInitialized())
  { if (pTMEnvironment != (CTMEnvironment *) NULL) pTMEnvironment -> Reset();
    m_wndDataView.Reset(pTMEnvironment);
    m_wndParametersView.Reset(pTMEnvironment);
    m_wndFunctionsView.Reset(pTMEnvironment);
    SetUpdateInfo();
  }
}

BOOL CPODWnd::Stop()
{
  Initialize(FALSE);
  StopSchedulePrintJobs();
  StopRetrieveData();
  return TRUE;
}

BOOL CPODWnd::SaveInfo(INT nPage,INT nDisplay,LPCTSTR pszTitle,CONST PDISPLAYINFO pDisplayInfo)
{
  UINT  nSpeed;
  UINT  nStatus;
  UINT  nDigits;
  UINT  nMode[2];
  UINT  nLimit[2];
  CString  szName;
  LOGFONT  sFontInfo[3][2];
  CTimeKey  tRange[2][2];
  CTimeKey  tStartTime;
  CTimeKey  tStopTime;
  CTimeSpan  tInterval;
  CTimeSpan  tPeriodical;
  CTimeSpan  tDailyRange[2];
  CUIntArray  nWidths[3];
  CUIntArray  nColors;
  CByteArray  nPrintInfo;
  CProfile  cProfile;

  return((CDisplayWnd::SaveInfo(nPage,nDisplay,pszTitle,pDisplayInfo) &&  GetLayout(szName,nWidths[0],nWidths[1],nWidths[2]) &&  GetTitleFonts(&sFontInfo[0][0],&sFontInfo[1][0],&sFontInfo[2][0]) &&  GetItemsFonts(&sFontInfo[0][1],&sFontInfo[1][1],&sFontInfo[2][1]) &&  GetFilterMode(nMode[1]) &&  GetFilterDigits(nDigits) &&  GetFilterColors(nColors) &&  GetRetrieveMode(nMode[0]) &&  GetRetrieveSpeed(nSpeed) &&  GetRetrieveInterval(tInterval) &&  GetRetrieveStartTime(tStartTime) &&  GetRetrieveStopTime(tStopTime) &&  GetPrintJobs(nPrintInfo) &&  cProfile.SetPODLayoutName(nPage,nDisplay,szName) &&  cProfile.SetPODLayoutInfo(nPage,nDisplay,GetViewSize(POD_VIEW_DATA),nWidths[0],GetViewSize(POD_VIEW_PARAMETERS),nWidths[1],GetViewSize(POD_VIEW_FUNCTIONS),nWidths[2],IsToolTipModeEnabled()) &&  cProfile.SetPODFontsInfo(nPage,nDisplay,&sFontInfo[0][0],&sFontInfo[0][1],&sFontInfo[1][0],&sFontInfo[1][1],&sFontInfo[2][0],&sFontInfo[2][1]) &&  cProfile.SetPODFilterInfo(nPage,nDisplay,nMode[1],(GetFilterLimit(nLimit[1])) ? nLimit[1]:0,nDigits,(GetFilterStatus(nStatus)) ? nStatus:0,(GetFilterRange(tRange[0][0],tRange[0][1])) ? tRange[0][0]:0,(GetFilterRange(tRange[0][0],tRange[0][1])) ? tRange[0][1]:0,(GetFilterDailyRange(tDailyRange[0],tDailyRange[1])) ? tDailyRange[0]:0,(GetFilterDailyRange(tDailyRange[0],tDailyRange[1])) ? tDailyRange[1]:0,(GetFilterPeriodicalRange(tRange[1][0],tPeriodical,tRange[1][1])) ? tRange[1][0]:0,(GetFilterPeriodicalRange(tRange[1][0],tPeriodical,tRange[1][1])) ? tPeriodical:0,(GetFilterPeriodicalRange(tRange[1][0],tPeriodical,tRange[1][1])) ? tRange[1][1]:0,nColors) &&  cProfile.SetPODModeInfo(nPage,nDisplay,nMode[0],nSpeed,tInterval,tStartTime,tStopTime) &&  cProfile.SetPODPrintInfo(nPage,nDisplay,nPrintInfo)) ? TRUE:FALSE);
}

BOOL CPODWnd::LoadInfo(INT nPage,INT nDisplay,CString &szTitle,PDISPLAYINFO pDisplayInfo)
{
  UINT  nSpeed;
  UINT  nStatus;
  UINT  nDigits;
  UINT  nMode[2];
  UINT  nLimit[2];
  BOOL  bToolTips;
  CSize  size[3];
  CString  szName;
  LOGFONT  sFontInfo[3][2];
  CTimeKey  tRange[2][2];
  CTimeKey  tStartTime;
  CTimeKey  tStopTime;
  CTimeSpan  tInterval;
  CTimeSpan  tPeriodical;
  CTimeSpan  tDailyRange[2];
  CUIntArray  nWidths[3];
  CUIntArray  nColors;
  CByteArray  nPrintInfo;
  CProfile  cProfile;

  return((CDisplayWnd::LoadInfo(nPage,nDisplay,szTitle,pDisplayInfo) &&  cProfile.GetPODLayoutName(nPage,nDisplay,szName) &&  cProfile.GetPODLayoutInfo(nPage,nDisplay,size[0],nWidths[0],size[1],nWidths[1],size[2],nWidths[2],bToolTips) &&  cProfile.GetPODFontsInfo(nPage,nDisplay,&sFontInfo[0][0],&sFontInfo[0][1],&sFontInfo[1][0],&sFontInfo[1][1],&sFontInfo[2][0],&sFontInfo[2][1]) &&  cProfile.GetPODFilterInfo(nPage,nDisplay,nMode[1],nLimit[1],nDigits,nStatus,tRange[0][0],tRange[0][1],tDailyRange[0],tDailyRange[1],tRange[1][0],tPeriodical,tRange[1][1],nColors) &&  cProfile.GetPODModeInfo(nPage,nDisplay,nMode[0],nSpeed,tInterval,tStartTime,tStopTime) &&  cProfile.GetPODPrintInfo(nPage,nDisplay,nPrintInfo) &&  SetLayout(szName,nWidths[0],nWidths[1],nWidths[2]) &&  SetViewSize(POD_VIEW_DATA,size[0]) &&  SetViewSize(POD_VIEW_PARAMETERS,size[1]) &&  SetViewSize(POD_VIEW_FUNCTIONS,size[2]) &&  EnableToolTipMode(bToolTips) &&  SetTitleFonts(&sFontInfo[0][0],&sFontInfo[1][0],&sFontInfo[2][0]) &&  SetItemsFonts(&sFontInfo[0][1],&sFontInfo[1][1],&sFontInfo[2][1]) &&  SetFilterMode(nMode[1]) &&  SetFilterLimit(nLimit[1]) >= 0  &&  SetFilterStatus(nStatus) >= 0  &&  SetFilterRange(tRange[0][0],tRange[0][1]) >= 0  &&  SetFilterDailyRange(tDailyRange[0],tDailyRange[1]) >= 0  &&  SetFilterPeriodicalRange(tRange[1][0],tPeriodical,tRange[1][1]) >= 0  &&  SetFilterDigits(nDigits) &&  SetFilterColors(nColors) &&  SetRetrieveMode(nMode[0]) &&  SetRetrieveSpeed(nSpeed) &&  SetRetrieveInterval(tInterval) &&  SetRetrieveStartTime(tStartTime) &&  SetRetrieveStopTime(tStopTime) &&  SetPrintJobs(nPrintInfo)) ? TRUE:FALSE);
}

BOOL CPODWnd::QueryDefaultInfo(PDISPLAYINFO pDefaultInfo) CONST
{
  pDefaultInfo -> ptWnd.x = 0;
  pDefaultInfo -> ptWnd.y = 0;
  pDefaultInfo -> nNumber = -1;
  pDefaultInfo -> rWnd = rectDefault;
  pDefaultInfo -> nScope = DISPLAY_SCOPE_LOCAL;
  pDefaultInfo -> nMode = DISPLAY_MODE_HISTORY;
  pDefaultInfo -> pData = (LPVOID) NULL;
  pDefaultInfo -> nShow = SW_SHOWNORMAL;
  pDefaultInfo -> bShow = TRUE;
  return TRUE;
}

BOOL CPODWnd::QueryDefaultMenu(CLocaleMenu &cMenu,CImageList &cImages,CUIntArray &nImageIDs) CONST
{
  INT  nIndex;
  INT  nCount;
  INT  iImage;
  UINT  nButtonID;
  UINT  nButtonStyle;
  CBitmap  cBitmap;
  BITMAP  sBitmap;

  for (cImages.DeleteImageList(),nImageIDs.RemoveAll(); cBitmap.LoadBitmap(IDB_PODFRAMESMALLIMAGES) &&  cBitmap.GetBitmap(&sBitmap); )
  { for (nIndex = 0,nCount = (cImages.Create(sBitmap.bmHeight,sBitmap.bmHeight,ILC_COLOR32,sBitmap.bmWidth/sBitmap.bmHeight,1) &&  cImages.Add(&cBitmap,RGB(0,0,0)) >= 0) ? m_wndToolBar.GetCount():0; nIndex < nCount; nIndex++)
    { for (m_wndToolBar.GetButtonInfo(nIndex,nButtonID,nButtonStyle,iImage); nButtonID != 0  &&  nButtonID != (UINT) -1; )
      { nImageIDs.Add(nButtonID);
        break;
      }
    }
    cBitmap.DeleteObject();
    break;
  }
  return cMenu.LoadMenu(IDR_PODFRAME);
}

VOID CPODWnd::UpdateBars()
{
  CDisplayLock  cLock(this);

  UpdateMessagePane();
  UpdateModePane();
  UpdateTypePane();
}

BOOL CPODWnd::Print(PRINTDLG *pPrintInfo)
{
  INT  nJob;
  INT  nJobs;
  CPODPrintJobs  pJobs;
  CPODPrintJobInfo  *pJobInfo;
  CDisplayLock  cLock(this);

  for (nJob = 0,nJobs = (GetPrintJobs(pJobs)) ? (INT) pJobs.GetSize():0; nJob < nJobs; nJob++)
  { if ((pJobInfo = pJobs.GetAt(nJob)) &&  pJobInfo -> GetName() == STRING(IDS_PRINTJOB_DEFAULTNAME))
    { if (Print(pJobInfo,pPrintInfo)) break;
      continue;
    }
  }
  if (nJob < nJobs)
  { if (pJobInfo -> GetPrintMode() & POD_PRINT_CLEARCOMMENTS)
    { pJobInfo -> SetPrintMode(pJobInfo -> GetPrintMode() & ~POD_PRINT_CLEARCOMMENTS);
      pJobInfo -> SetComments(EMPTYSTRING);
      SetPrintJobs(pJobs);
    }
    return TRUE;
  }
  return FALSE;
}

BOOL CPODWnd::CanPrint() CONST
{
  CPODLayout  cLayout;
  CStringArray  szFunctions;
  CStringArray  szParameters;

  return((GetLayout(cLayout) && (cLayout.GetSize() > 0  ||  cLayout.GetParameters(szParameters) > 0  ||  cLayout.GetFunctions(szFunctions) > 0)) ? TRUE:FALSE);
}

BOOL CPODWnd::SetFilterMode(UINT nMode)
{
  CDisplayLock  cLock(this);

  return((m_wndDataView.SetFilterMode(nMode) &&  m_wndParametersView.SetFilterMode(nMode) &&  m_wndFunctionsView.SetFilterMode(nMode)) ? TRUE:FALSE);
}

BOOL CPODWnd::GetFilterMode(UINT &nMode) CONST
{
  CDisplayLock  cLock(this);

  return m_wndDataView.GetFilterMode(nMode);
}

BOOL CPODWnd::SetFilterLimit(UINT nLimit)
{
  CDisplayLock  cLock(this);

  return((m_wndDataView.SetFilterLimit(nLimit) &&  m_wndParametersView.SetFilterLimit(nLimit) &&  m_wndFunctionsView.SetFilterLimit(nLimit)) ? TRUE:FALSE);
}

BOOL CPODWnd::GetFilterLimit(UINT &nLimit) CONST
{
  CDisplayLock  cLock(this);

  return m_wndDataView.GetFilterLimit(nLimit);
}

BOOL CPODWnd::SetFilterStatus(UINT nStatus)
{
  CDisplayLock  cLock(this);

  return((m_wndDataView.SetFilterStatus(nStatus) &&  m_wndParametersView.SetFilterStatus(nStatus) &&  m_wndFunctionsView.SetFilterStatus(nStatus)) ? TRUE:FALSE);
}

BOOL CPODWnd::GetFilterStatus(UINT &nStatus) CONST
{
  CDisplayLock  cLock(this);

  return m_wndDataView.GetFilterStatus(nStatus);
}

BOOL CPODWnd::SetFilterRange(CONST CTimeKey &tStartTime,CONST CTimeKey &tStopTime)
{
  CDisplayLock  cLock(this);

  return((m_wndDataView.SetFilterRange(tStartTime,tStopTime) &&  m_wndParametersView.SetFilterRange(tStartTime,tStopTime) &&  m_wndFunctionsView.SetFilterRange(tStartTime,tStopTime)) ? TRUE:FALSE);
}

BOOL CPODWnd::GetFilterRange(CTimeKey &tStartTime,CTimeKey &tStopTime) CONST
{
  CDisplayLock  cLock(this);

  return m_wndDataView.GetFilterRange(tStartTime,tStopTime);
}

BOOL CPODWnd::SetFilterDailyRange(CONST CTimeSpan &tStartTime,CONST CTimeSpan &tStopTime)
{
  CDisplayLock  cLock(this);

  return((m_wndDataView.SetFilterDailyRange(tStartTime,tStopTime) &&  m_wndParametersView.SetFilterDailyRange(tStartTime,tStopTime) &&  m_wndFunctionsView.SetFilterDailyRange(tStartTime,tStopTime)) ? TRUE:FALSE);
}

BOOL CPODWnd::GetFilterDailyRange(CTimeSpan &tStartTime,CTimeSpan &tStopTime) CONST
{
  CDisplayLock  cLock(this);

  return m_wndDataView.GetFilterDailyRange(tStartTime,tStopTime);
}

BOOL CPODWnd::SetFilterPeriodicalRange(CONST CTimeKey &tStartTime,CONST CTimeSpan &tInterval,CONST CTimeKey &tStopTime)
{
  CDisplayLock  cLock(this);

  return((m_wndDataView.SetFilterPeriodicalRange(tStartTime,tInterval,tStopTime) &&  m_wndParametersView.SetFilterPeriodicalRange(tStartTime,tInterval,tStopTime) &&  m_wndFunctionsView.SetFilterPeriodicalRange(tStartTime,tInterval,tStopTime)) ? TRUE:FALSE);
}

BOOL CPODWnd::GetFilterPeriodicalRange(CTimeKey &tStartTime,CTimeSpan &tInterval,CTimeKey &tStopTime) CONST
{
  CDisplayLock  cLock(this);

  return m_wndDataView.GetFilterPeriodicalRange(tStartTime,tInterval,tStopTime);
}

BOOL CPODWnd::SetFilterDigits(UINT nDigits)
{
  CDisplayLock  cLock(this);

  return((m_wndDataView.SetFilterDigits(nDigits) &&  m_wndParametersView.SetFilterDigits(nDigits) &&  m_wndFunctionsView.SetFilterDigits(nDigits)) ? TRUE:FALSE);
}

BOOL CPODWnd::GetFilterDigits(UINT &nDigits) CONST
{
  CDisplayLock  cLock(this);

  return m_wndDataView.GetFilterDigits(nDigits);
}

BOOL CPODWnd::SetFilterColors()
{
  CUIntArray  nColors;

  nColors.InsertAt(POD_OOLCOLOR_NOLIMIT,VGA_COLOR_GRAY);
  nColors.InsertAt(POD_OOLCOLOR_SOFTLIMIT,VGA_COLOR_RED);
  nColors.InsertAt(POD_OOLCOLOR_HARDLIMIT,VGA_COLOR_LTRED);
  nColors.InsertAt(POD_OOLCOLOR_DELTALIMIT,VGA_COLOR_MAGENTA);
  nColors.InsertAt(POD_OOLCOLOR_CONSISTENCYLIMIT,VGA_COLOR_YELLOW);
  return SetFilterColors(nColors);
}
BOOL CPODWnd::SetFilterColors(CONST CUIntArray &nColors)
{
  CDisplayLock  cLock(this);

  return((m_wndDataView.SetFilterColors(nColors) &&  m_wndParametersView.SetFilterColors(nColors) &&  m_wndFunctionsView.SetFilterColors(nColors)) ? TRUE:FALSE);
}

BOOL CPODWnd::GetFilterColors(CUIntArray &nColors) CONST
{
  CDisplayLock  cLock(this);

  return m_wndDataView.GetFilterColors(nColors);
}

BOOL CPODWnd::ProcessRealtimeData()
{
  INT  nLink;
  INT  nLinks;
  CString  szTag;
  CTimeTag  tTag;
  CPtrArray  pLinks;
  CDisplayWnd  *pDisplayWnd;
  CDisplayLock  cLock(this);

  for (nLink = 0,nLinks = GetLinks(pLinks); nLink < nLinks; nLink++)
  { if ((pDisplayWnd = (CDisplayWnd *) pLinks.GetAt(nLink)) &&  pDisplayWnd -> IsInitialized())
    { pDisplayWnd -> InitializeTMData(DISPLAY_MODE_REALTIME);
      continue;
    }
  }
  if (Initialize(szTag,tTag))
  { SetUpdateInfo(szTag,tTag,-1,TMUNIT_DATAQUALITY_NONE);
    return TRUE;
  }
  return FALSE;
}

BOOL CPODWnd::StartRetrieveData(UINT nMode,UINT nSpeed,CONST CTimeSpan &tInterval,CONST CTimeKey &tStartTime,CONST CTimeKey &tStopTime)
{
  SetRetrieveMode(nMode);
  SetRetrieveSpeed(nSpeed);
  SetRetrieveInterval(tInterval);
  SetRetrieveStartTime(tStartTime);
  SetRetrieveStopTime(tStopTime);
  return StartRetrieveData();
}
BOOL CPODWnd::StartRetrieveData()
{
  INT  nLink;
  INT  nLinks;
  CString  szTag;
  CTimeTag  tTag;
  CEvent  bInit[2];
  CPtrArray  pLinks;
  CDisplayWnd  *pDisplayWnd;

  if (GetMode() == DISPLAY_MODE_HISTORY)
  { if (GetLink() != (CDisplayWnd *) NULL)
    { for (SetRetrieveMode(); Initialize(szTag,tTag); )
      { SetUpdateInfo(szTag,tTag,-1,TMUNIT_DATAQUALITY_NONE);
        return TRUE;
      }
      ReportEvent(SYSTEM_WARNING_POD_RETRIEVE_FAILURE);
      return FALSE;
    }
    if (!IsRetrievingData())
    { if (m_cRetrieveThread.Start(this,bInit[0],bInit[1],GetRetrieveFileName(),GetRetrieveMode(),GetRetrieveSpeed(),GetRetrieveInterval(),GetRetrieveStartTime(),GetRetrieveStopTime(),&m_bRetrieveFlag,m_cRetrieveStop,m_cRetrieveAutoForward,m_cRetrieveAutoBackward,m_cRetrieveManualForward,m_cRetrieveManualBackward,m_cRetrievePseudoRealtime) &&  UpdateAllPanes())
      { for (WaitForSingleObject(bInit[0],INFINITE); Lock(); )
        { for (nLink = 0,nLinks = GetLinks(pLinks); nLink < nLinks; nLink++)
          { if ((pDisplayWnd = (CDisplayWnd *) pLinks.GetAt(nLink)) &&  pDisplayWnd -> IsInitialized())
            { pDisplayWnd -> InitializeTMData(DISPLAY_MODE_HISTORY);
              continue;
            }
          }
          Unlock();
          break;
        }
        if (Initialize(szTag,tTag))
        { SetUpdateInfo();
          SetEvent(bInit[1]);
          return TRUE;
        }
        SetEvent(bInit[1]);
      }
      ReportEvent(SYSTEM_WARNING_POD_RETRIEVE_FAILURE);
    }
  }
  return FALSE;
}

LONG CPODWnd::IsRetrievingData() CONST
{
  LONG  bFlag;

  InterlockedExchange(&bFlag,m_bRetrieveFlag);
  return((m_cRetrieveThread.IsThreadActive()) ? bFlag:FALSE);
}

BOOL CPODWnd::RetrieveMoreData(UINT nAction)
{
  if (IsRetrievingData())
  { if (nAction == POD_RETRIEVE_STOPPED)
    { SetRetrieveMode(GetRetrieveMode() | nAction);
      m_cRetrieveStop.SetEvent();
      UpdateAllPanes();
      return TRUE;
    }
    if (nAction == POD_RETRIEVE_AUTOFORWARD)
    { SetRetrieveMode((GetRetrieveMode() & (POD_RETRIEVE_EXACTTIME | POD_RETRIEVE_STOPBYTIME | POD_RETRIEVE_STOPBYEND | POD_RETRIEVE_STOPBYREALTIME)) | nAction);
      m_cRetrieveAutoForward.SetEvent();
      UpdateAllPanes();
      return TRUE;
    }
    if (nAction == POD_RETRIEVE_AUTOBACKWARD)
    { SetRetrieveMode((GetRetrieveMode() & (POD_RETRIEVE_EXACTTIME | POD_RETRIEVE_STOPBYTIME | POD_RETRIEVE_STOPBYEND | POD_RETRIEVE_STOPBYREALTIME)) | nAction);
      m_cRetrieveAutoBackward.SetEvent();
      UpdateAllPanes();
      return TRUE;
    }
    if (nAction == POD_RETRIEVE_MANUALFORWARD)
    { SetRetrieveMode((GetRetrieveMode() & (POD_RETRIEVE_EXACTTIME | POD_RETRIEVE_STOPBYTIME | POD_RETRIEVE_STOPBYEND | POD_RETRIEVE_STOPBYREALTIME)) | nAction);
      m_cRetrieveManualForward.SetEvent();
      UpdateAllPanes();
      return TRUE;
    }
    if (nAction == POD_RETRIEVE_MANUALBACKWARD)
    { SetRetrieveMode((GetRetrieveMode() & (POD_RETRIEVE_EXACTTIME | POD_RETRIEVE_STOPBYTIME | POD_RETRIEVE_STOPBYEND | POD_RETRIEVE_STOPBYREALTIME)) | nAction);
      m_cRetrieveManualBackward.SetEvent();
      UpdateAllPanes();
      return TRUE;
    }
    if (nAction == POD_RETRIEVE_PSEUDOREALTIME)
    { SetRetrieveMode((GetRetrieveMode() & (POD_RETRIEVE_EXACTTIME | POD_RETRIEVE_STOPBYTIME | POD_RETRIEVE_STOPBYEND | POD_RETRIEVE_STOPBYREALTIME)) | nAction);
      m_cRetrievePseudoRealtime.SetEvent();
      UpdateAllPanes();
      return TRUE;
    }
  }
  return FALSE;
}

BOOL CPODWnd::StopRetrieveData()
{
  return(((IsRetrievingData() &&  m_cRetrieveThread.Stop()) ||  !IsRetrievingData()) ? TRUE:FALSE);
}

BOOL CPODWnd::SetRetrieveMode(UINT nMode)
{
  CDisplayLock  cLock(this);

  m_nRetrieveMode = nMode;
  m_bRetrieveFlag = MAKELONG((nMode) ? LOWORD(m_bRetrieveFlag):FALSE,(nMode) ? HIWORD(m_bRetrieveFlag):FALSE);
  return TRUE;
}

BOOL CPODWnd::GetRetrieveMode(UINT &nMode) CONST
{
  nMode = m_nRetrieveMode;
  return TRUE;
}
UINT CPODWnd::GetRetrieveMode() CONST
{
  return m_nRetrieveMode;
}

BOOL CPODWnd::SetRetrieveSpeed(UINT nSpeed)
{
  m_nRetrieveSpeed = nSpeed;
  return TRUE;
}

BOOL CPODWnd::GetRetrieveSpeed(UINT &nSpeed) CONST
{
  nSpeed = m_nRetrieveSpeed;
  return TRUE;
}
UINT CPODWnd::GetRetrieveSpeed() CONST
{
  return m_nRetrieveSpeed;
}

BOOL CPODWnd::SetRetrieveInterval(CONST CTimeSpan &tInterval)
{
  CDisplayLock  cLock(this);

  m_tRetrieveInterval = tInterval;
  return TRUE;
}

BOOL CPODWnd::GetRetrieveInterval(CTimeSpan &tInterval) CONST
{
  CDisplayLock  cLock(this);

  tInterval = m_tRetrieveInterval;
  return TRUE;
}
CTimeSpan CPODWnd::GetRetrieveInterval() CONST
{
  CDisplayLock  cLock(this);

  return m_tRetrieveInterval;
}

BOOL CPODWnd::SetRetrieveStartTime(CONST CTimeKey &tStartTime)
{
  CDisplayLock  cLock(this);

  m_tRetrieveStartTime = tStartTime;
  return TRUE;
}

BOOL CPODWnd::GetRetrieveStartTime(CTimeKey &tStartTime) CONST
{
  CDisplayLock  cLock(this);

  tStartTime = m_tRetrieveStartTime;
  return TRUE;
}
CTimeKey CPODWnd::GetRetrieveStartTime() CONST
{
  CDisplayLock  cLock(this);

  return m_tRetrieveStartTime;
}

BOOL CPODWnd::SetRetrieveStopTime(CONST CTimeKey &tStopTime)
{
  CDisplayLock  cLock(this);

  m_tRetrieveStopTime = tStopTime;
  return TRUE;
}

BOOL CPODWnd::GetRetrieveStopTime(CTimeKey &tStopTime) CONST
{
  CDisplayLock  cLock(this);

  tStopTime = m_tRetrieveStopTime;
  return TRUE;
}
CTimeKey CPODWnd::GetRetrieveStopTime() CONST
{
  CDisplayLock  cLock(this);

  return m_tRetrieveStopTime;
}

BOOL CPODWnd::SetRetrieveFileName(LPCTSTR pszFileName)
{
  CDisplayLock  cLock(this);

  m_szRetrieveFileName = pszFileName;
  return TRUE;
}

BOOL CPODWnd::GetRetrieveFileName(CString &szFileName) CONST
{
  CDisplayLock  cLock(this);

  szFileName = GetRetrieveFileName();
  return TRUE;
}
CString CPODWnd::GetRetrieveFileName() CONST
{
  CString  szFileName;
  CHistoryStoreFile  cFile;
  CHistoryStoreFiles  pFiles;
  CDisplayLock  cLock(this);

  if (GetTMService() -> GetTMHistoryFiles(HISTORYFILE_TYPE_RETRIEVE,pFiles) > 0)
  { if (pFiles.Find(m_szRetrieveFileName) >= 0)
    { szFileName = m_szRetrieveFileName;
      return szFileName;
    }
    if (GetTMService() -> GetDefaultTMHistoryFile(HISTORYFILE_TYPE_RETRIEVE,cFile))
    { szFileName = cFile.GetFileName();
      return szFileName;
    }
  }
  if (!IsInitialized())
  { szFileName = m_szRetrieveFileName;
    return szFileName;
  }
  return EMPTYSTRING;
}

BOOL CPODWnd::SetPrintJobs(CONST CPODPrintJobs &pPrintJobs)
{
  return m_cPrintThread.SetPrintJobs(pPrintJobs);
}

BOOL CPODWnd::GetPrintJobs(CPODPrintJobs &pPrintJobs) CONST
{
  return m_cPrintThread.GetPrintJobs(pPrintJobs);
}

BOOL CPODWnd::Print(CONST CPODPrintJobInfo *pJobInfo,PRINTDLG *pPrintInfo)
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
  DEVMODE  *pDevMode;
  DEVNAMES  *pDevNames;
  CPtrArray  pItemsFonts;
  CPODLayout  cLayout;
  CUIntArray  nOOLColors;
  CStringArray  szColumns[3];
  CStringArray  szContents[3];
  CTMParameters  pValues;
  CPrintProfiles  cPrintProfiles;
  CPrintProfileInfo  *pPrintProfileInfo;
  CTextViewAttributes  pAttributes[3];

  if ((pPrintProfileInfo = (GetPrintProfiles(cPrintProfiles)) ? cPrintProfiles.GetAt(cPrintProfiles.Find(pJobInfo -> GetProfile())):(CPrintProfileInfo *) NULL) &&  pPrintProfileInfo -> GetPaperInfo(ptPaperSize,rtMargin[0],rtMargin[1],bMetric))
  { if (GetPrintProperties(pJobInfo,cLayout,nMode,szTMUnit,tTMUnit,nTMUnit,bQuality,szColumns[0],szContents[0],pAttributes[0],szColumns[1],szContents[1],pAttributes[1],szColumns[2],szContents[2],pAttributes[2],pValues,nOOLColors,pItemsFonts))
    { if (pPrintInfo == (PRINTDLG *) NULL)
      { if (CreatePrinterDC(pPrintProfileInfo,cDC))
        { if (PrintJob(cDC,pJobInfo,pPrintProfileInfo -> GetPrinterName(),0,0,rtMargin[0],bMetric,cLayout,nMode,szTMUnit,tTMUnit,nTMUnit,bQuality,szColumns[0],szContents[0],pAttributes[0],szColumns[1],szContents[1],pAttributes[1],szColumns[2],szContents[2],pAttributes[2],pValues,nOOLColors,pItemsFonts))
          { for ( ; pItemsFonts.GetSize() > 0; pItemsFonts.RemoveAt(pItemsFonts.GetUpperBound()))
            { GlobalFree(pItemsFonts.GetAt(pItemsFonts.GetUpperBound()));
              continue;
            }
            cDC.DeleteDC();
            return TRUE;
          }
          cDC.DeleteDC();
        }
        for ( ; pItemsFonts.GetSize() > 0; pItemsFonts.RemoveAt(pItemsFonts.GetUpperBound()))
        { GlobalFree(pItemsFonts.GetAt(pItemsFonts.GetUpperBound()));
          continue;
        }
        return FALSE;
      }
      if ((pDevNames = (DEVNAMES *) GlobalLock(pPrintInfo -> hDevNames)))
      { if ((pDevMode = (DEVMODE *) GlobalLock(pPrintInfo -> hDevMode)))
        { if (CreatePrinterDC(pPrintInfo -> hDevNames,pPrintInfo -> hDevMode,cDC))
          { if (PrintJob(cDC,pJobInfo,(LPCTSTR) pDevMode -> dmDeviceName,(pPrintInfo -> Flags & PD_PAGENUMS) ? pPrintInfo -> nFromPage:0,(pPrintInfo -> Flags & PD_PAGENUMS) ? pPrintInfo -> nToPage:0,rtMargin[0],bMetric,cLayout,nMode,szTMUnit,tTMUnit,nTMUnit,bQuality,szColumns[0],szContents[0],pAttributes[0],szColumns[1],szContents[1],pAttributes[1],szColumns[2],szContents[2],pAttributes[2],pValues,nOOLColors,pItemsFonts))
            { for ( ; pItemsFonts.GetSize() > 0; pItemsFonts.RemoveAt(pItemsFonts.GetUpperBound()))
              { GlobalFree(pItemsFonts.GetAt(pItemsFonts.GetUpperBound()));
                continue;
              }
              GlobalUnlock(pPrintInfo -> hDevNames);
              GlobalUnlock(pPrintInfo -> hDevMode);
              cDC.DeleteDC();
              return TRUE;
            }
            cDC.DeleteDC();
          }
          GlobalUnlock(pPrintInfo -> hDevMode);
        }
        GlobalUnlock(pPrintInfo -> hDevNames);
      }
      for ( ; pItemsFonts.GetSize() > 0; pItemsFonts.RemoveAt(pItemsFonts.GetUpperBound()))
      { GlobalFree(pItemsFonts.GetAt(pItemsFonts.GetUpperBound()));
        continue;
      }
    }
  } 
  return FALSE;
}

CPODWnd *CPODWnd::Find(INT nType,UINT nMode,LPCTSTR pszName) CONST
{
  INT  nDisplay;
  INT  nDisplays;
  CPODWnd  *pPODWnd;
  CPODLayout  cLayout;
  CDisplayWnd  *pDisplayWnd;
  CPtrArray  pDisplays;

  for (nDisplay = 0,nDisplays = GetDisplayArea() -> EnumDisplays(pDisplays),pPODWnd = (CPODWnd *) NULL; nDisplay < nDisplays; nDisplay++)
  { if ((pDisplayWnd = (CDisplayWnd *) pDisplays.GetAt(nDisplay)) &&  LOWORD(pDisplayWnd -> GetType()) == DISPLAY_TYPE_POD  &&  HIWORD(pDisplayWnd -> GetType()) == HIWORD(nType) &&  pDisplayWnd -> GetMode() == nMode)
    { if ((pPODWnd = (CPODWnd *) pDisplayWnd) -> GetLayout(cLayout) &&  cLayout.GetName() == pszName) break;
      continue;
    }
  }
  return((nDisplay < nDisplays) ? pPODWnd:(CPODWnd *) NULL);
}

VOID CPODWnd::SetUpdateInfo()
{
  CDisplayLock  cLock(this);

  m_szTMUnit.Empty();
  m_tTMUnit = 0;
  m_nTMUnit = 0;
  m_wTMUnit = TMUNIT_DATAQUALITY_NONE;
  UpdateMessagePane();
}
VOID CPODWnd::SetUpdateInfo(LPCTSTR pszTag,CONST CTimeTag &tTag,UINT nTag,WORD wQuality)
{
  CDisplayLock  cLock(this);

  m_szTMUnit = pszTag;
  m_tTMUnit = tTag;
  m_nTMUnit = nTag;
  m_wTMUnit = wQuality;
  UpdateMessagePane(); 
}

BOOL CPODWnd::GetUpdateInfo(CString &szTag,CTimeTag &tTag,UINT &nTag,WORD &wQuality) CONST
{
  CDisplayLock  cLock(this);

  szTag = m_szTMUnit;
  tTag = m_tTMUnit;
  nTag = m_nTMUnit;
  wQuality = m_wTMUnit;
  return TRUE;
}

BOOL CPODWnd::CreateToolBar()
{
  if (m_wndToolBar.CreateEx(this,TBSTYLE_FLAT,CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE) &&  m_wndToolBar.LoadToolBar(IDB_PODFRAMELARGEIMAGES,0,IDB_PODFRAMESMALLIMAGES,TRUE))
  { m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_PODSETTINGS),TBBS_DISABLED);
    m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_PODLINKAGES),TBBS_DISABLED);
    m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_PODHOLD),TBBS_DISABLED);
    m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_PODCLEARALL),TBBS_DISABLED);
    m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_PODRETRIEVALS),TBBS_DISABLED);
    m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_PODRETRIEVESTOP),TBBS_DISABLED);
    m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_PODRETRIEVESTEPFORWARD),TBBS_DISABLED);
    m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_PODRETRIEVESTEPBACKWARD),TBBS_DISABLED);
    m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_PODRETRIEVEFORWARD),TBBS_DISABLED);
    m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_PODRETRIEVEBACKWARD),TBBS_DISABLED);
    m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_PODRETRIEVEPSEUDOREALTIME),TBBS_DISABLED);
    m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(IDM_PODPRINT),TBBS_DISABLED);
    DockPane(&m_wndToolBar);
    RecalcLayout();
    return TRUE;
  }
  return FALSE;
}

BOOL CPODWnd::CreateStatusBar()
{
  if (m_wndStatusBar.Create(this,CBRS_BOTTOM | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE) &&  m_wndStatusBar.SetIndicators(nPODStatusBarIndicators,1))
  { m_wndStatusBar.EnableToolTips();
    RecalcLayout();
    return TRUE;
  }
  return FALSE;
}

BOOL CPODWnd::CreateSplitterBars()
{
  return m_wndSplitterBarCtrl[0].Create(this,RepositionViewSplitterBar(TRUE)) &&  m_wndSplitterBarCtrl[1].Create(this,RepositionViewSplitterBar(FALSE));
}

BOOL CPODWnd::CreateViews()
{
  CRect  rView[3];

  if (m_wndDataView.Create(this) &&  m_wndParametersView.Create(this) &&  m_wndFunctionsView.Create(this))
  { if (m_sizeViews[POD_VIEW_DATA].cx > 0  &&  m_sizeViews[POD_VIEW_DATA].cy > 0)
    { for (rView[0] = RepositionView(POD_VIEW_DATA); !rView[0].IsRectEmpty(); )
      { rView[0].SetRect(rView[0].left,rView[0].top,rView[0].right,rView[0].top+m_sizeViews[POD_VIEW_DATA].cy);
        break;
      }
      for (rView[1] = RepositionView(POD_VIEW_PARAMETERS); !rView[1].IsRectEmpty(); )
      { rView[1].SetRect(rView[1].left,(!rView[0].IsRectEmpty()) ? (rView[0].bottom+RepositionViewSplitterBar(TRUE).Height()):rView[1].top,rView[1].right,(!rView[0].IsRectEmpty()) ? (rView[0].bottom+RepositionViewSplitterBar(TRUE).Height()+m_sizeViews[POD_VIEW_PARAMETERS].cy):(rView[1].top+m_sizeViews[POD_VIEW_PARAMETERS].cy));
        break;
      }
      for (rView[2] = RepositionView(POD_VIEW_FUNCTIONS); !rView[2].IsRectEmpty(); )
      { rView[2].SetRect(rView[2].left,(!rView[1].IsRectEmpty()) ? (rView[1].bottom+RepositionViewSplitterBar(FALSE).Height()):((!rView[0].IsRectEmpty()) ? (rView[0].bottom+RepositionViewSplitterBar(TRUE).Height()):rView[2].top),rView[2].right,(!rView[1].IsRectEmpty()) ? (rView[1].bottom+RepositionViewSplitterBar(FALSE).Height()+m_sizeViews[POD_VIEW_FUNCTIONS].cy):((!rView[0].IsRectEmpty()) ? (rView[0].bottom+RepositionViewSplitterBar(TRUE).Height()+m_sizeViews[POD_VIEW_FUNCTIONS].cy):(rView[2].top+m_sizeViews[POD_VIEW_FUNCTIONS].cy)));
        break;
      }
      m_wndDataView.MoveWindow(rView[0]);
      m_wndParametersView.MoveWindow(rView[1]);
      m_wndFunctionsView.MoveWindow(rView[2]);
      return TRUE;
    }
    m_wndDataView.MoveWindow(RepositionView(POD_VIEW_DATA));
    m_wndParametersView.MoveWindow(RepositionView(POD_VIEW_PARAMETERS));
    m_wndFunctionsView.MoveWindow(RepositionView(POD_VIEW_FUNCTIONS));
    return TRUE;
  }
  return FALSE;
}

VOID CPODWnd::InitializeViews()
{
  SetViewSize(POD_VIEW_DATA,CSize(0,0));
  SetViewSize(POD_VIEW_PARAMETERS,CSize(0,0));
  SetViewSize(POD_VIEW_FUNCTIONS,CSize(0,0));
  m_bViews[0] = TRUE;
  m_bViews[1] = FALSE;
  m_bViews[2] = FALSE;
}

CRect CPODWnd::RepositionViews(BOOL bAdjust)
{
  CRect  rWnd[2];
  CRect  rView[3];
  CRect  rToolBar;
  CRect  rStatusBar;

  for (rWnd[0].SetRectEmpty(),rView[0].SetRectEmpty(); IsWindow(m_wndDataView.GetSafeHwnd()); )
  { rView[0].SetRect(0,0,m_wndDataView.GetTrackSize().cx,m_wndDataView.GetTrackSize().cy);
    break;
  }
  for (rView[1].SetRectEmpty(); IsWindow(m_wndParametersView.GetSafeHwnd()); )
  { rView[1].SetRect(0,0,m_wndParametersView.GetTrackSize().cx,m_wndParametersView.GetTrackSize().cy);
    break;
  }
  for (rView[2].SetRectEmpty(); IsWindow(m_wndFunctionsView.GetSafeHwnd()); )
  { rView[2].SetRect(0,0,m_wndFunctionsView.GetTrackSize().cx,m_wndFunctionsView.GetTrackSize().cy);
    break;
  }
  for (rToolBar.SetRectEmpty(); IsWindow(m_wndToolBar.GetSafeHwnd()); )
  { m_wndToolBar.GetWindowRect(rToolBar);
    break;
  }
  for (rStatusBar.SetRectEmpty(); IsWindow(m_wndStatusBar.GetSafeHwnd()); )
  { m_wndStatusBar.GetWindowRect(rStatusBar);
    break;
  }
  if (IsWindow(GetSafeHwnd()))
  { for (rWnd[0].SetRect(0,0,2*GetSystemMetrics(SM_CXFRAME)+rView[0].Width(),2*(GetSystemMetrics(SM_CYFRAME)+GetSystemMetrics(SM_CYEDGE))+GetSystemMetrics(SM_CYCAPTION)+rToolBar.Height()+IsViewVisible(POD_VIEW_DATA)*rView[0].Height()+RepositionViewSplitterBar(TRUE).Height()+IsViewVisible(POD_VIEW_PARAMETERS)*rView[1].Height()+RepositionViewSplitterBar(FALSE).Height()+IsViewVisible(POD_VIEW_FUNCTIONS)*rView[2].Height()+rStatusBar.Height()); bAdjust; )
    { for (GetWindowRect(rWnd[1]),GetParent() -> ScreenToClient(rWnd[1]); rWnd[0].Height() > rWnd[1].Height(); )
      { MoveWindow(rWnd[1].left,rWnd[1].top,rWnd[1].Width(),rWnd[0].Height());
        return rWnd[0];
      }
      m_wndDataView.MoveWindow(RepositionView(POD_VIEW_DATA));
      m_wndSplitterBarCtrl[0].MoveWindow(RepositionViewSplitterBar(TRUE));
      m_wndParametersView.MoveWindow(RepositionView(POD_VIEW_PARAMETERS));
      m_wndSplitterBarCtrl[1].MoveWindow(RepositionViewSplitterBar(FALSE));
      m_wndFunctionsView.MoveWindow(RepositionView(POD_VIEW_FUNCTIONS));
      break;
    }
  }
  return rWnd[0];
}

BOOL CPODWnd::SetViewSize(UINT nView,CONST CSize &size)
{
  if (nView == POD_VIEW_DATA  ||  nView == POD_VIEW_PARAMETERS  ||  nView == POD_VIEW_FUNCTIONS)
  { m_sizeViews[nView] = size;
    return TRUE;
  }
  return FALSE;
}

CSize CPODWnd::GetViewSize(UINT nView) CONST
{
  CRect  rView(0,0,0,0);

  if (nView == POD_VIEW_DATA) m_wndDataView.GetWindowRect(rView);
  if (nView == POD_VIEW_PARAMETERS) m_wndParametersView.GetWindowRect(rView);
  if (nView == POD_VIEW_FUNCTIONS) m_wndFunctionsView.GetWindowRect(rView);
  return CSize(rView.Width(),rView.Height());
}

CRect CPODWnd::RepositionView(UINT nView)
{
  INT  nHeight;
  INT  nOffset;
  CWnd  *pWnd;
  CRect  rWnd;
  CRect  rView[7];

  for (rView[0].SetRectEmpty(); IsWindow(GetSafeHwnd()); )
  { for (pWnd = GetWindow(GW_CHILD),GetClientRect(rView[0]); pWnd != (CWnd *) NULL; pWnd = pWnd -> GetNextWindow())
    { if (pWnd -> GetSafeHwnd() != m_wndDataView.GetSafeHwnd() &&  pWnd -> GetSafeHwnd() != m_wndParametersView.GetSafeHwnd() &&  pWnd -> GetSafeHwnd() != m_wndFunctionsView.GetSafeHwnd())
      { pWnd -> GetWindowRect(rWnd);
        ScreenToClient(rWnd);
        rWnd.left = rView[0].left;
        rWnd.right = rView[0].right;
        rView[0].SubtractRect(rView[0],rWnd);
      }
    }
    if (IsWindow(m_wndDataView.GetSafeHwnd()) &&  IsWindow(m_wndParametersView.GetSafeHwnd()) &&  IsWindow(m_wndFunctionsView.GetSafeHwnd()))
    { for (m_wndDataView.GetWindowRect(rView[1]),m_wndParametersView.GetWindowRect(rView[3]),m_wndFunctionsView.GetWindowRect(rView[5]),rView[2].SetRect(0,0,m_wndDataView.GetTrackSize().cx,m_wndDataView.GetTrackSize().cy),rView[4].SetRect(0,0,m_wndParametersView.GetTrackSize().cx,m_wndParametersView.GetTrackSize().cy),rView[6].SetRect(0,0,m_wndFunctionsView.GetTrackSize().cx,m_wndFunctionsView.GetTrackSize().cy),ScreenToClient(rView[1]),ScreenToClient(rView[3]),ScreenToClient(rView[5]); !IsViewVisible(POD_VIEW_DATA); )
      { rView[1].SetRectEmpty();
        rView[2].SetRectEmpty();
        break;
      }
      if (!IsViewVisible(POD_VIEW_PARAMETERS))
      { rView[3].SetRectEmpty();
        rView[4].SetRectEmpty();
      }
      if (!IsViewVisible(POD_VIEW_FUNCTIONS))
      { rView[5].SetRectEmpty();
        rView[6].SetRectEmpty();
      }
      for (rView[0].DeflateRect(0,rView[1].Height(),0,0),rView[0].DeflateRect(0,rView[3].Height(),0,0),rView[0].DeflateRect(0,rView[5].Height(),0,0); IsViewVisible(POD_VIEW_DATA) &&  rView[1].IsRectEmpty(); )
      { rView[1].SetRect(rView[0].left,rView[0].top,rView[0].right,rView[0].top+rView[2].Height());
        rView[0].DeflateRect(0,rView[2].Height(),0,0);
        break;
      }
      for (rView[0].DeflateRect(0,(IsViewVisible(POD_VIEW_DATA)) ? RepositionViewSplitterBar(TRUE).Height():0,0,0); IsViewVisible(POD_VIEW_PARAMETERS) &&  rView[3].IsRectEmpty(); )
      { rView[3].SetRect(rView[0].left,rView[0].top,rView[0].right,rView[0].top+rView[4].Height());
        rView[0].DeflateRect(0,rView[4].Height(),0,0);
        break;
      }
      for (rView[0].DeflateRect(0,(!IsViewVisible(POD_VIEW_DATA) &&  IsViewVisible(POD_VIEW_PARAMETERS)) ? RepositionViewSplitterBar(TRUE).Height():0,0,0),rView[0].DeflateRect(0,(IsViewVisible(POD_VIEW_DATA) &&  IsViewVisible(POD_VIEW_PARAMETERS)) ? RepositionViewSplitterBar(FALSE).Height():0,0,0); IsViewVisible(POD_VIEW_FUNCTIONS) &&  rView[5].IsRectEmpty(); )
      { rView[5].SetRect(rView[0].left,rView[0].top,rView[0].right,rView[0].top+rView[6].Height());
        rView[0].DeflateRect(0,rView[6].Height(),0,0);
        break;
      }
      if (rView[0].Height() > 0) rView[1].InflateRect(0,0,0,rView[0].Height());
      if (rView[0].Height() < 0  &&  IsViewVisible(POD_VIEW_FUNCTIONS) &&  rView[5].Height() > rView[6].Height())
      { if ((nHeight = rView[5].Height()-rView[6].Height()) >= abs(rView[0].Height()))
        { rView[5].DeflateRect(0,0,0,abs(rView[0].Height()));
          rView[0].InflateRect(0,abs(rView[0].Height()),0,0);
        }
        else
        { rView[5].DeflateRect(0,0,0,nHeight);
          rView[0].InflateRect(0,nHeight,0,0);
        }
      }
      if (rView[0].Height() < 0  &&  IsViewVisible(POD_VIEW_PARAMETERS) &&  rView[3].Height() > rView[4].Height())
      { if ((nHeight = rView[3].Height()-rView[4].Height()) >= abs(rView[0].Height()))
        { rView[5].OffsetRect(0,rView[0].Height());
          rView[3].DeflateRect(0,0,0,abs(rView[0].Height()));
          rView[0].InflateRect(0,abs(rView[0].Height()),0,0);
        }
        else
        { rView[5].OffsetRect(0,-nHeight);
          rView[3].DeflateRect(0,0,0,nHeight);
          rView[0].InflateRect(0,nHeight,0,0);
        }
      }
      if (rView[0].Height() < 0  &&  IsViewVisible(POD_VIEW_DATA) &&  rView[1].Height() > rView[2].Height())
      { if ((nHeight = rView[1].Height()-rView[2].Height()) >= abs(rView[0].Height()))
        { rView[5].OffsetRect(0,rView[0].Height());
          rView[3].OffsetRect(0,rView[0].Height());
          rView[1].DeflateRect(0,0,0,abs(rView[0].Height()));
          rView[0].InflateRect(0,abs(rView[0].Height()),0,0);
        }
        else
        { rView[5].OffsetRect(0,-nHeight);
          rView[3].OffsetRect(0,-nHeight);
          rView[1].DeflateRect(0,0,0,nHeight);
          rView[0].InflateRect(0,nHeight,0,0);
        }
      }
      if (IsViewVisible(POD_VIEW_DATA) &&  IsViewVisible(POD_VIEW_PARAMETERS))
      { nOffset = rView[3].top-(rView[1].bottom+RepositionViewSplitterBar().Height());
        rView[3].OffsetRect(0,-nOffset);
      }
      if (IsViewVisible(POD_VIEW_DATA) &&  !IsViewVisible(POD_VIEW_PARAMETERS) &&  IsViewVisible(POD_VIEW_FUNCTIONS))
      { nOffset = rView[5].top-(rView[1].bottom+RepositionViewSplitterBar().Height());
        rView[5].OffsetRect(0,-nOffset);
      }
      if (IsViewVisible(POD_VIEW_PARAMETERS) &&  IsViewVisible(POD_VIEW_FUNCTIONS))
      { nOffset = rView[5].top-(rView[3].bottom+RepositionViewSplitterBar().Height());
        rView[5].OffsetRect(0,-nOffset);
      }
      switch (nView)
      { case POD_VIEW_DATA:
        { if (IsViewVisible(POD_VIEW_DATA))
          { rView[1].left = rView[0].left;
            rView[1].right = rView[0].right;
            return rView[1];
          }
          break;
        }
        case POD_VIEW_PARAMETERS:
        { if (IsViewVisible(POD_VIEW_PARAMETERS))
          { rView[3].left = rView[0].left;
            rView[3].right = rView[0].right;
            return rView[3];
          }
          break;
        }
        case POD_VIEW_FUNCTIONS:
        { if (IsViewVisible(POD_VIEW_FUNCTIONS))
          { rView[5].left = rView[0].left;
            rView[5].right = rView[0].right;
            return rView[5];
          }
          break;
        }
      }
    }
    break;
  }
  return CRect(0,0,0,0);
}

BOOL CPODWnd::IsViewVisible(UINT nView) CONST
{
  return((nView == POD_VIEW_DATA  ||  nView == POD_VIEW_PARAMETERS  ||  nView == POD_VIEW_FUNCTIONS) ? m_bViews[nView]:FALSE);
}

CRect CPODWnd::RepositionViewSplitterBar(BOOL bUpper) CONST
{
  CRect  rView[4];

  for (GetClientRect(rView[0]); IsWindow(m_wndDataView.GetSafeHwnd()) &&  IsWindow(m_wndParametersView.GetSafeHwnd()) &&  IsWindow(m_wndFunctionsView.GetSafeHwnd()); )
  { m_wndDataView.GetWindowRect(rView[1]);
    m_wndParametersView.GetWindowRect(rView[2]);
    m_wndFunctionsView.GetWindowRect(rView[3]);
    ScreenToClient(rView[1]);
    ScreenToClient(rView[2]);
    ScreenToClient(rView[3]);
    if (bUpper  &&  IsViewVisible(POD_VIEW_DATA) &&  IsViewVisible(POD_VIEW_PARAMETERS)) return CRect(rView[0].left,rView[1].bottom,rView[0].right,rView[1].bottom+2*GetSystemMetrics(SM_CYEDGE));
    if (bUpper  &&  IsViewVisible(POD_VIEW_DATA) &&  IsViewVisible(POD_VIEW_FUNCTIONS)) return CRect(rView[0].left,rView[1].bottom,rView[0].right,rView[1].bottom+2*GetSystemMetrics(SM_CYEDGE));
    if (bUpper  &&  IsViewVisible(POD_VIEW_PARAMETERS) &&  IsViewVisible(POD_VIEW_FUNCTIONS)) return CRect(rView[0].left,rView[2].bottom,rView[0].right,rView[2].bottom+2*GetSystemMetrics(SM_CYEDGE));
    if (!bUpper  &&  IsViewVisible(POD_VIEW_DATA) &&  IsViewVisible(POD_VIEW_PARAMETERS) &&  IsViewVisible(POD_VIEW_FUNCTIONS)) return CRect(rView[0].left,rView[2].bottom,rView[0].right,rView[2].bottom+2*GetSystemMetrics(SM_CYEDGE));
    break;
  }
  return CRect(rView[0].left,rView[0].bottom,rView[0].right,rView[0].bottom);
}

BOOL CPODWnd::Customize(BOOL bDefault)
{
  CString  szName;
  CString  szTitle;
  LOGFONT  sFontInfo[3][2];
  CUIntArray  nWidths[3];
  CPODLayout  cLayout;

  if ((!bDefault  &&  GetLayout(cLayout) &&  GetLayout(szName,nWidths[0],nWidths[1],nWidths[2]) &&  GetTitleFonts(&sFontInfo[0][0],&sFontInfo[1][0],&sFontInfo[2][0]) &&  GetItemsFonts(&sFontInfo[0][1],&sFontInfo[1][1],&sFontInfo[2][1]) &&  SetLayout(szName,nWidths[0],nWidths[1],nWidths[2]) &&  SetTitleFonts(&sFontInfo[0][0],&sFontInfo[1][0],&sFontInfo[2][0]) &&  SetItemsFonts(&sFontInfo[0][1],&sFontInfo[1][1],&sFontInfo[2][1])) ||  bDefault)
  { for (szTitle.Format(STRING(IDS_WINDOW_FULLTITLE),STRING(IDS_DISPLAY_TITLE_POD),(!cLayout.GetTitle().IsEmpty()) ? (LPCTSTR) cLayout.GetTitle():(LPCTSTR) cLayout.GetName()); !bDefault; )
    { SetWindowText(szTitle);
      break;
    }
    return TRUE;
  }
  return FALSE;
}

BOOL CPODWnd::UpdateAllPanes()
{
  INT  nPane;
  INT  nPanes;

  for (nPane = 0,nPanes = sizeof(nPODStatusBarIndicators)/sizeof(UINT); nPane < nPanes; nPane++)
  { if (m_wndStatusBar.CommandToIndex(nPODStatusBarIndicators[nPane]) != nPane) break;
    continue;
  }
  if (nPane < nPanes)
  { if (m_wndStatusBar.SetIndicators(nPODStatusBarIndicators,sizeof(nPODStatusBarIndicators)/sizeof(UINT)))
    { UpdateBars();
      return TRUE;
    }
    return FALSE;
  }
  UpdateBars();
  return TRUE;
}

VOID CPODWnd::UpdateMessagePane()
{
  UINT  nTag;
  WORD  wQuality;
  CTimeTag  tTag;
  CString  szTag;
  CString  szMessage;

  if (GetUpdateInfo(szTag,tTag,nTag,wQuality))
  { szMessage.Format((szTag.IsEmpty()) ? ((tTag > 0) ? STRING(IDS_POD_STATUSBAR_FULLUPDATEMESSAGE):((IsRetrievingData() &&  HIWORD(IsRetrievingData())) ? STRING(IDS_POD_STATUSBAR_RETRIEVEMESSAGE):STRING(IDS_POD_STATUSBAR_NODATAMESSAGE))):((nTag == (UINT) -1) ? STRING(IDS_POD_STATUSBAR_INITUPDATEMESSAGE):STRING(IDS_POD_STATUSBAR_UPDATEMESSAGE)),(LPCTSTR) tTag.FormatGmt(),(LPCTSTR) szTag,nTag,((wQuality & (TMUNIT_DATAQUALITY_GOOD | TMUNIT_SEQUENCEQUALITY_GOOD)) == (TMUNIT_DATAQUALITY_GOOD | TMUNIT_SEQUENCEQUALITY_GOOD)) ? ((wQuality & TMUNIT_TIMECORRELATION_BAD) ? (LPCTSTR) (CString(STRING(IDS_POD_STATUSBAR_QUALITYGOOD))+STRING(IDS_POD_STATUSBAR_TIMECORRELATIONFLAG)):STRING(IDS_POD_STATUSBAR_QUALITYGOOD)):((wQuality & TMUNIT_TIMECORRELATION_BAD) ? (LPCTSTR) (CString(STRING(IDS_POD_STATUSBAR_QUALITYBAD))+STRING(IDS_POD_STATUSBAR_TIMECORRELATIONFLAG)):STRING(IDS_POD_STATUSBAR_QUALITYBAD)));
    m_wndStatusBar.SetPaneText(ID_POD_STATUSBAR_MESSAGEPANE,szMessage);
  }
  m_wndToolBar.EnableButton(IDM_PODCLEARALL,(IsInitialized() &&  m_wndDataView.GetTextCount() > 0) ? TRUE:FALSE);
}

VOID CPODWnd::UpdateModePane()
{
  CString  szMode;
  CPODLayout  cLayout;
  CDisplayWnd  *pDisplayWnd;

  for (szMode.Empty(); (pDisplayWnd = (CDisplayWnd *) GetLink()) &&  GetLayout(cLayout); )
  { szMode.Format(STRING(IDS_DISPLAY_MODE_LINK),STRING(IDS_DISPLAY_TITLE_POD),(LPCTSTR) cLayout.GetName());
    break;
  }
  m_wndStatusBar.SetPaneText(ID_POD_STATUSBAR_MODEPANE,(GetMode() == DISPLAY_MODE_HISTORY) ? (((GetRetrieveMode() & POD_RETRIEVE_AUTOFORWARD) &&  !(GetRetrieveMode() & POD_RETRIEVE_STOPPED)) ? STRING(IDS_POD_STATUSBAR_AUTOFORWARDMODE):(((GetRetrieveMode() & POD_RETRIEVE_AUTOBACKWARD) &&  !(GetRetrieveMode() & POD_RETRIEVE_STOPPED)) ? STRING(IDS_POD_STATUSBAR_AUTOBACKWARDMODE):(((GetRetrieveMode() & POD_RETRIEVE_PSEUDOREALTIME) &&  !(GetRetrieveMode() & POD_RETRIEVE_STOPPED)) ? STRING(IDS_POD_STATUSBAR_PSEUDOREALTIMEMODE):((!szMode.IsEmpty()) ? (STRING(IDS_POD_STATUSBAR_NORMALMODE)+szMode):STRING(IDS_POD_STATUSBAR_NORMALMODE))))):((!szMode.IsEmpty()) ? (STRING(IDS_DISPLAY_MODE_REALTIME)+szMode):STRING(IDS_DISPLAY_MODE_REALTIME)));
  m_wndToolBar.EnableButton(IDM_PODRETRIEVESTOP,(IsRetrievingData() && ((GetRetrieveMode() & POD_RETRIEVE_AUTOFORWARD) || (GetRetrieveMode() & POD_RETRIEVE_AUTOBACKWARD) || (GetRetrieveMode() & POD_RETRIEVE_PSEUDOREALTIME) ||  HIWORD(IsRetrievingData())) &&  !(GetRetrieveMode() & POD_RETRIEVE_STOPPED)) ? TRUE:FALSE);
  m_wndToolBar.EnableButton(IDM_PODRETRIEVEFORWARD,(IsRetrievingData() &&  !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & POD_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & POD_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & POD_RETRIEVE_STOPPED))) ? TRUE:FALSE);
  m_wndToolBar.EnableButton(IDM_PODRETRIEVEBACKWARD,(IsRetrievingData() &&  !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & POD_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & POD_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & POD_RETRIEVE_STOPPED))) ? TRUE:FALSE);
  m_wndToolBar.EnableButton(IDM_PODRETRIEVESTEPFORWARD,(IsRetrievingData() &&  !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & POD_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & POD_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & POD_RETRIEVE_STOPPED))) ? TRUE:FALSE);
  m_wndToolBar.EnableButton(IDM_PODRETRIEVESTEPBACKWARD,(IsRetrievingData() &&  !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & POD_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & POD_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & POD_RETRIEVE_STOPPED))) ? TRUE:FALSE);
  m_wndToolBar.EnableButton(IDM_PODRETRIEVEPSEUDOREALTIME,(IsRetrievingData() &&  !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & POD_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & POD_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & POD_RETRIEVE_STOPPED))) ? TRUE:FALSE);
}

VOID CPODWnd::UpdateTypePane()
{
  CString  szType;
  CPODLayoutExpression  *pExpression;
  CPODLayout  cLayout;

  switch (HIWORD(GetType()))
  { case POD_TYPE_NORMAL:
    { if (GetLayout(cLayout) &&  cLayout.GetSize() == 1)
      { if ((pExpression = cLayout.GetAt((INT) cLayout.GetUpperBound())) -> IsParameter())
        { szType.Format(STRING(IDS_POD_STATUSBAR_TYPENORMAL),(LPCTSTR) pExpression -> GetParameter());
          break;
        }
      }
      szType = STRING(IDS_POD_STATUSBAR_TYPENORMAL);
      szType = szType.Left((szType.Find(SPACE) >= 0) ? szType.Find(SPACE):lstrlen(STRING(IDS_POD_STATUSBAR_TYPENORMAL)));
      break;
    }
    case POD_TYPE_TEMPORARY:
    { if (GetLayout(cLayout) &&  cLayout.GetSize() == 1)
      { if ((pExpression = cLayout.GetAt(0)) -> IsParameter())
        { szType.Format(STRING(IDS_POD_STATUSBAR_TYPETEMPORARY),(LPCTSTR) pExpression -> GetParameter());
          break;
        }
      }
      szType = STRING(IDS_POD_STATUSBAR_TYPETEMPORARY);
      szType = szType.Left((szType.Find(SPACE) >= 0) ? szType.Find(SPACE):lstrlen(STRING(IDS_POD_STATUSBAR_TYPETEMPORARY)));
      break;
    }
  }
  m_wndStatusBar.SetPaneText(ID_POD_STATUSBAR_TYPEPANE,szType);
}

VOID CPODWnd::UpdateData(BOOL bInfo)
{
  UINT  nTag;
  BOOL  bValue;
  WORD  wQuality;
  CString  szTag[2];
  CTimeTag  tTag[2];
  CFloatArray  fValues;
  CDisplayLock  cLock(this);

  if (!bInfo)
  { if (m_wndDataView.GetValues(szTag[0],tTag[0],fValues,bValue)) m_wndFunctionsView.SetValues(szTag[0],tTag[0],fValues,bValue);
    return;
  }
  if (GetUpdateInfo(szTag[0],tTag[0],nTag,wQuality) &&  Initialize(szTag[1],tTag[1]))
  { SetUpdateInfo(szTag[1],tTag[1],(szTag[0] == szTag[1] &&  tTag[0] == tTag[1]) ? nTag:-1,(szTag[0] == szTag[1] &&  tTag[0] == tTag[1]) ? wQuality:TMUNIT_DATAQUALITY_NONE);
    return;
  }
}

BOOL CPODWnd::LoadLayout(LPCTSTR pszLayout,CPODLayout &cLayout)
{
  return((HIWORD(GetType()) != POD_TYPE_NORMAL) ? ((HIWORD(GetType()) == POD_TYPE_TEMPORARY) ? LoadTemporaryPOD(pszLayout,cLayout):FALSE):GetDatabase() -> LoadPOD(pszLayout,cLayout));
}

VOID CPODWnd::SetHoldFlag(BOOL bEnable)
{
  CDisplayLock  cLock(this);

  m_wndDataView.SetHoldFlag(bEnable);
  m_wndFunctionsView.SetHoldFlag(bEnable);
}

BOOL CPODWnd::GetHoldFlag() CONST
{
  CDisplayLock  cLock(this);

  return m_wndDataView.GetHoldFlag() &&  m_wndFunctionsView.GetHoldFlag();
}

BOOL CPODWnd::HasHoldFlag() CONST
{
  CDisplayLock  cLock(this);

  return m_wndDataView.HasHoldFlag() &&  m_wndFunctionsView.HasHoldFlag();
}

BOOL CPODWnd::StartSchedulePrintJobs()
{
  return IsSchedulingPrintJobs() ||  m_cPrintThread.Start(this);
}

BOOL CPODWnd::IsSchedulingPrintJobs() CONST
{
  return((m_cPrintThread.IsThreadActive()) ? TRUE:FALSE);
}

BOOL CPODWnd::StopSchedulePrintJobs()
{
  return((IsSchedulingPrintJobs() &&  m_cPrintThread.Stop()) ? TRUE:FALSE);
}

BOOL CPODWnd::SetPrintJobs(CONST CByteArray &nPrintInfo)
{
  CPODPrintJobs  pPrintJobs;

  return((pPrintJobs.Unmap(nPrintInfo)) ? SetPrintJobs(pPrintJobs):FALSE);
}

BOOL CPODWnd::GetPrintJobs(CByteArray &nPrintInfo) CONST
{
  CPODPrintJobs  pPrintJobs;

  return((GetPrintJobs(pPrintJobs)) ? pPrintJobs.Map(nPrintInfo):FALSE);
}

BOOL CPODWnd::GetPrintProperties(CONST CPODPrintJobInfo *pJobInfo,CPODLayout &cLayout,UINT &nMode,CString &szTMUnit,CTimeTag &tTMUnit,UINT &nTMUnit,BOOL &bQuality,CStringArray &szDataColumns,CStringArray &szDataContents,CTextViewAttributes &pDataAttributes,CStringArray &szParametersColumns,CStringArray &szParametersContents,CTextViewAttributes &pParametersAttributes,CStringArray &szFunctionsColumns,CStringArray &szFunctionsContents,CTextViewAttributes &pFunctionsAttributes,CTMParameters &pValues,CUIntArray &nOOLColors,CPtrArray &pFonts) CONST
{
  INT  nIndex;
  INT  nCount[2];
  UINT  nPrintMode;
  UINT  nPrintCount;
  WORD  wPrintQuality;
  CPtrArray  pDataFonts;
  CPtrArray  pFunctionsFonts;
  CPtrArray  pParametersFonts;
  CTextViewAttribute  *pAttribute;
  CDisplayLock  cLock(this);

  if (((nMode = GetMode()) == DISPLAY_MODE_REALTIME  ||  nMode == DISPLAY_MODE_HISTORY) &&  GetUpdateInfo(szTMUnit,tTMUnit,nTMUnit,wPrintQuality) &&  m_wndDataView.GetPrintProperties(cLayout,szDataColumns,szDataContents,pDataAttributes,pDataFonts) &&  m_wndParametersView.GetPrintProperties(cLayout,szParametersColumns,szParametersContents,pParametersAttributes,pValues,pParametersFonts) &&  m_wndFunctionsView.GetPrintProperties(cLayout,szFunctionsColumns,szFunctionsContents,pFunctionsAttributes,pFunctionsFonts) &&  GetFilterColors(nOOLColors))
  { if ((nPrintMode = (pJobInfo -> GetPrintBySide(nPrintCount)) ? pJobInfo -> GetPrintMode():0) & POD_PRINT_FIRSTSIDE)
    { for (nIndex = ((nCount[0] = (INT) (szDataContents.GetSize()-nPrintCount)) > 0) ? nPrintCount:0,szDataContents.RemoveAt((nCount[0] > 0) ? nPrintCount:0,max(nCount[0],0)),nCount[1] = 0; nCount[1] < nCount[0]; nCount[1]++)
      { if ((pAttribute = pDataAttributes.GetAt(nIndex))) delete pAttribute;
        pDataAttributes.RemoveAt(nIndex);
      }
    }
    if (nPrintMode & POD_PRINT_LASTSIDE)
    { for (nIndex = 0,nCount[1] = 0,nCount[0] = (INT) (szDataContents.GetSize()-nPrintCount),szDataContents.RemoveAt(0,max(nCount[0],0)); nCount[1] < nCount[0]; nCount[1]++)
      { if ((pAttribute = pDataAttributes.GetAt(nIndex))) delete pAttribute;
        pDataAttributes.RemoveAt(nIndex);
      }
    }
    pFonts.Copy(pDataFonts);
    pFonts.Append(pParametersFonts);
    pFonts.Append(pFunctionsFonts);
    bQuality = ((wPrintQuality & (TMUNIT_DATAQUALITY_GOOD | TMUNIT_SEQUENCEQUALITY_GOOD)) == (TMUNIT_DATAQUALITY_GOOD | TMUNIT_SEQUENCEQUALITY_GOOD)) ? TRUE:FALSE;
    return TRUE;
  }
  return FALSE;
}

BOOL CPODWnd::StartPrintJob(CDC &cDC)
{
  DOCINFO  sJobInfo;
  CString  szJobTitle;
  CPODLayout  cLayout;

  for (GetLayout(cLayout),sJobInfo.fwType = 0,sJobInfo.cbSize = sizeof(DOCINFO),sJobInfo.lpszDocName = (LPTSTR) EMPTYSTRING,sJobInfo.lpszOutput = (LPCTSTR) NULL,sJobInfo.lpszDatatype = (LPCTSTR) NULL,szJobTitle.Format(STRING(IDS_PRINTJOB_DEFAULTTITLE),(LPCTSTR) GetAppTitle(),(LPCTSTR) GetAccountSpacecraftName(),(LPCTSTR) GetPrintDocSubTitle(cLayout),STRING(IDS_DISPLAY_TITLE_POD)); szJobTitle.GetLength() >= 0; )
  { sJobInfo.lpszDocName = (LPTSTR) (LPCTSTR) szJobTitle;
    break;
  }
  return((cDC.StartDoc(&sJobInfo) >= 0) ? TRUE:FALSE);
}

BOOL CPODWnd::PrintJob(CDC &cDC,CONST CPODPrintJobInfo *pJobInfo,LPCTSTR pszPrinterName,INT nFromPage,INT nToPage,CONST RECT &rtMargin,BOOL bMetric,CONST CPODLayout &cLayout,UINT nMode,LPCTSTR pszTMUnit,CONST CTimeTag &tTMUnit,UINT nTMUnit,BOOL bQuality,CONST CStringArray &szDataColumns,CONST CStringArray &szDataContents,CONST CTextViewAttributes &pDataAttributes,CONST CStringArray &szParametersColumns,CONST CStringArray &szParametersContents,CONST CTextViewAttributes &pParametersAttributes,CONST CStringArray &szFunctionsColumns,CONST CStringArray &szFunctionsContents,CONST CTextViewAttributes &pFunctionsAttributes,CONST CTMParameters &pValues,CONST CUIntArray &nOOLColors,CONST CPtrArray &pItemFonts)
{
  INT  x;
  INT  y;
  INT  nView;
  INT  nViews;
  INT  nPage;
  INT  nPages;
  INT  nLine;
  INT  nLines;
  INT  nColumn;
  INT  nColumns;
  INT  nFont;
  INT  nFonts;
  INT  nBkMode;
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
  CFont  *pFont;
  CFont  *pOldFont;
  CFont  cFont[POD_PRINTFONTS];
  CSize  sizeText[2];
  CString  szColumn;
  COLORREF  nColor;
  COLORREF  nOldColor;
  CTimeKey  tPrint;
  ULONGLONG  nValue;
  CPtrArray  pFonts;
  TEXTMETRIC  tmFont;
  CUIntArray  nTabs[3];
  CStringArray  szParameters;
  CStringArray  szColumns[3];
  CStringArray  szContents[3];
  CStringArray  szColumnsText;
  CTMParameter  *pTMParameter;
  CTextViewAttribute  *pAttribute;
  CTextViewAttributes  pAttributes[3];

  for (nPage = nPages = 0; (!nPages  ||  nPage <= nPages) && (nPages > 0  || (nPages = (CalcPrintDocRect(cDC,rtMargin,bMetric) &&  cDC.GetClipBox(rArea) != ERROR  &&  rgnArea.CreateRectRgnIndirect(rArea) &&  CalcPrintDocTitleFont(cDC,rArea,cFont[POD_PRINTFONT_TITLE]) &&  CalcPrintDocSubTitleFont(cDC,rArea,cFont[POD_PRINTFONT_SUBTITLE]) &&  CalcPrintDocOperatingDetailsFont(cDC,rArea,cFont[POD_PRINTFONT_OPERATINGDETAILS]) &&  CalcPrintDocOperatingModeFont(cDC,rArea,cFont[POD_PRINTFONT_OPERATINGMODE]) &&  CalcPrintDocListTitleFont(cDC,POD_VIEW_DATA,rArea,cFont[POD_PRINTFONT_DATATITLE]) &&  CalcPrintDocListItemsFonts(cDC,POD_VIEW_DATA,rArea,szDataColumns,szDataContents,(CONST LOGFONT *) pItemFonts.GetAt(POD_PRINTFONT_DATALISTITEMSTITLE-POD_PRINTFONT_DATATITLE-1),(CONST LOGFONT *) pItemFonts.GetAt(POD_PRINTFONT_DATALISTITEMS-POD_PRINTFONT_DATATITLE-1),(CONST LOGFONT *) pItemFonts.GetAt(POD_PRINTFONT_DATALISTVALUES-POD_PRINTFONT_DATATITLE-1),cFont[POD_PRINTFONT_DATALISTITEMSTITLE],cFont[POD_PRINTFONT_DATALISTITEMS],cFont[POD_PRINTFONT_DATALISTVALUES]) &&  CalcPrintDocListTitleFont(cDC,POD_VIEW_PARAMETERS,rArea,cFont[POD_PRINTFONT_PARAMETERSTITLE]) &&  CalcPrintDocListItemsFonts(cDC,POD_VIEW_PARAMETERS,rArea,szParametersColumns,szParametersContents,(CONST LOGFONT *) pItemFonts.GetAt(POD_PRINTFONT_PARAMETERSLISTITEMSTITLE-POD_PRINTFONT_DATATITLE-1-1),(CONST LOGFONT *) pItemFonts.GetAt(POD_PRINTFONT_PARAMETERSLISTITEMS-POD_PRINTFONT_DATATITLE-1-1),(CONST LOGFONT *) pItemFonts.GetAt(POD_PRINTFONT_PARAMETERSLISTVALUES-POD_PRINTFONT_DATATITLE-1-1),cFont[POD_PRINTFONT_PARAMETERSLISTITEMSTITLE],cFont[POD_PRINTFONT_PARAMETERSLISTITEMS],cFont[POD_PRINTFONT_PARAMETERSLISTVALUES]) &&  CalcPrintDocListTitleFont(cDC,POD_VIEW_FUNCTIONS,rArea,cFont[POD_PRINTFONT_FUNCTIONSTITLE]) &&  CalcPrintDocListItemsFonts(cDC,POD_VIEW_FUNCTIONS,rArea,szFunctionsColumns,szFunctionsContents,(CONST LOGFONT *) pItemFonts.GetAt(POD_PRINTFONT_FUNCTIONSLISTITEMSTITLE-POD_PRINTFONT_DATATITLE-1-1-1),(CONST LOGFONT *) pItemFonts.GetAt(POD_PRINTFONT_FUNCTIONSLISTITEMS-POD_PRINTFONT_DATATITLE-1-1-1),(CONST LOGFONT *) pItemFonts.GetAt(POD_PRINTFONT_FUNCTIONSLISTVALUES-POD_PRINTFONT_DATATITLE-1-1-1),cFont[POD_PRINTFONT_FUNCTIONSLISTITEMSTITLE],cFont[POD_PRINTFONT_FUNCTIONSLISTITEMS],cFont[POD_PRINTFONT_FUNCTIONSLISTVALUES]) &&  CalcPrintDocNoticeFonts(cDC,rArea,cFont[POD_PRINTFONT_NOTICE],cFont[POD_PRINTFONT_LOGO]) &&  CalcPrintDocFooterFont(cDC,rArea,cFont[POD_PRINTFONT_FOOTER]) &&  CalcPrintDocTitleWidth(cDC,POD_VIEW_DATA,szDataColumns,szDataContents,&cFont[POD_PRINTFONT_DATALISTITEMSTITLE],&cFont[POD_PRINTFONT_DATALISTITEMS],&cFont[POD_PRINTFONT_DATALISTVALUES],nTabs[POD_VIEW_DATA]) == szDataColumns.GetSize() &&  CalcPrintDocTitleWidth(cDC,POD_VIEW_PARAMETERS,szParametersColumns,szParametersContents,&cFont[POD_PRINTFONT_PARAMETERSLISTITEMSTITLE],&cFont[POD_PRINTFONT_PARAMETERSLISTITEMS],&cFont[POD_PRINTFONT_PARAMETERSLISTVALUES],nTabs[POD_VIEW_PARAMETERS]) == szParametersColumns.GetSize() &&  CalcPrintDocTitleWidth(cDC,POD_VIEW_FUNCTIONS,szFunctionsColumns,szFunctionsContents,&cFont[POD_PRINTFONT_FUNCTIONSLISTITEMSTITLE],&cFont[POD_PRINTFONT_FUNCTIONSLISTITEMS],&cFont[POD_PRINTFONT_FUNCTIONSLISTVALUES],nTabs[POD_VIEW_FUNCTIONS]) == szFunctionsColumns.GetSize()) ? nPages:-1) == 0); )                           
  { for (nFont = 0,nFonts = (!nPages) ? (INT) (sizeof(cFont)/sizeof(cFont[0])):0; nFont < nFonts; nFont++)
    { pFonts.SetAtGrow(nFont,&cFont[nFont]);
      continue;
    }
    for (nView = POD_VIEW_DATA,nViews = POD_VIEW_FUNCTIONS,szColumns[POD_VIEW_DATA].Copy(szDataColumns),szColumns[POD_VIEW_PARAMETERS].Copy(szParametersColumns),szColumns[POD_VIEW_FUNCTIONS].Copy(szFunctionsColumns),szContents[POD_VIEW_DATA].Copy(szDataContents),szContents[POD_VIEW_PARAMETERS].Copy(szParametersContents),szContents[POD_VIEW_FUNCTIONS].Copy(szFunctionsContents),pAttributes[POD_VIEW_DATA].Copy(&pDataAttributes),pAttributes[POD_VIEW_PARAMETERS].Copy(&pParametersAttributes),pAttributes[POD_VIEW_FUNCTIONS].Copy(&pFunctionsAttributes),nSpacing = 0,rCalc.SetRectEmpty(),rClip.SetRectEmpty(),bOverlap = FALSE; nPages >= 0  &&  nView <= nViews; nView++)
    { for (nLine = 0,nLines = (nView == POD_VIEW_DATA  || (nView == POD_VIEW_PARAMETERS  && (pJobInfo -> GetPrintMode() & POD_PRINT_PARAMETERS) &&  cLayout.GetParameters(szParameters) >= 0) || (nView == POD_VIEW_FUNCTIONS  && (pJobInfo -> GetPrintMode() & POD_PRINT_FUNCTIONS))) ? (INT) szContents[nView].GetSize():0,bOutput = TRUE; nPages >= 0  &&  nLine < nLines; nLine++,bOutput = TRUE)
      { for (nColumn = 0,nColumns = (INT) szColumns[nView].GetSize(),ExtractPrintDocText(szContents[nView].GetAt(nLine),szColumnsText),nHeight[0] = nHeight[1] = 0; nPages >= 0  &&  nColumn < nColumns; nColumn = nColumn+1,nHeight[1] = 0)
        { for (pFont = (CFont *) pFonts.GetAt(POD_PRINTFONT_DATALISTITEMS+4*nView); (nView == POD_VIEW_DATA  &&  !lstrcmp(szColumns[nView].GetAt(nColumn),STRING(IDS_POD_DATAHEADER_VALUE))) || (nView == POD_VIEW_PARAMETERS  &&  !lstrcmp(szColumns[nView].GetAt(nColumn),STRING(IDS_POD_PARAMETERSHEADER_VALUE))) || (nView == POD_VIEW_FUNCTIONS  &&  !lstrcmp(szColumns[nView].GetAt(nColumn),STRING(IDS_POD_FUNCTIONSHEADER_VALUE))); )
          { pFont = (CFont *) pFonts.GetAt(POD_PRINTFONT_DATALISTVALUES+4*nView);
            break;
          }
          if (rClip.Height() > 0)
          { if ((pOldFont = cDC.SelectObject(pFont)))
            { if ((nSpacing = (cDC.GetTextMetrics(&tmFont)) ? max(tmFont.tmHeight/16,1):-1) >= 0)
              { for (nColor = (nView == POD_VIEW_DATA) ? cLayout.GetExpressionColor():((nView == POD_VIEW_PARAMETERS) ? cLayout.GetParametersColor():((nView == POD_VIEW_FUNCTIONS) ? cLayout.GetFunctionsColor():cDC.GetTextColor())); (pAttribute = pAttributes[nView].GetAt(nLine)); )
                { pAttribute -> GetColumnColor(nColumn,nColor);
                  break;
                }
                nOldColor = cDC.SetTextColor((cDC.GetDeviceCaps(NUMCOLORS) > 2) ? nColor:cDC.GetTextColor());
                sizeText[0] = (nColumn < szColumnsText.GetSize()) ? cDC.GetTextExtent((szColumn = szColumnsText.GetAt(nColumn)+SPACE)):cDC.GetTextExtent((szColumn = EMPTYSTRING)+SPACE);
                sizeText[1] = (nColumn < szColumnsText.GetSize()) ? cDC.GetTextExtent(szColumnsText.GetAt(nColumn)):cDC.GetTextExtent(EMPTYSTRING);
                rCalc.SetRect(rCalc.left,(!nColumn) ? (rCalc.top+nSpacing):rCalc.top,rCalc.right,(!nColumn) ? (rCalc.top+nSpacing+tmFont.tmHeight*((rClip.bottom-(rCalc.top+nSpacing))/tmFont.tmHeight)):(rCalc.top+tmFont.tmHeight*((rClip.bottom-rCalc.top)/tmFont.tmHeight)));
                rItem.SetRect((nColumn > 0) ? (rCalc.left+nTabs[nView].GetAt(nColumn-1)):rCalc.left,rCalc.top,rCalc.left+nTabs[nView].GetAt(nColumn),rCalc.top+sizeText[0].cy);
                if (nPages > 0  && (nFromPage <= 0  ||  nToPage <= 0  ||  nFromPage > nToPage  || (nPage >= nFromPage  &&  nPage <= nToPage)))
                { cDC.DrawText(szColumn,CRect(rItem.left,rItem.top,rItem.right,rCalc.bottom),DT_LEFT | DT_NOPREFIX | DT_SINGLELINE);
                  if (nView == POD_VIEW_PARAMETERS  &&  szColumns[nView].GetAt(nColumn) == STRING(IDS_POD_PARAMETERSHEADER_VALUE))
                  { if ((pTMParameter = pValues.GetAt(pValues.Find(szParameters.GetAt(nLine)))))
                    { if (pJobInfo -> GetPrintMode() & POD_PRINT_UNDERLINEOOL)
                      { if (pTMParameter -> GetRawValue(0,nValue,nStatus))
                        { if ((nStatus & TMPARAMETER_STATUS_SOFTLIMIT) || (nStatus & TMPARAMETER_STATUS_HARDLIMIT) || (nStatus & TMPARAMETER_STATUS_DELTALIMIT) || (nStatus & TMPARAMETER_STATUS_CONSISTENCYLIMIT)) 
                          { if (cLinePen.CreatePen(PS_SOLID,tmFont.tmDescent/3,cDC.GetTextColor()))
                            { if ((pOldPen = cDC.SelectObject(&cLinePen)))
                              { nBkMode = cDC.SetBkMode(TRANSPARENT);
                                cDC.MoveTo((x=rItem.left),(y=rItem.bottom-max((2*tmFont.tmDescent)/3,1)));
                                cDC.LineTo(x+sizeText[1].cx,y);
                                cDC.SelectObject(pOldPen);
                                cDC.SetBkMode(nBkMode);
                              }
                              cLinePen.DeleteObject();
                            }
                          }
                        }
                      }
                    }
                  }
                }
                nHeight[0] = ((nHeight[1] = rItem.Height()) > nHeight[0]) ? nHeight[1]:nHeight[0];
                cDC.SetTextColor(nOldColor);
                cDC.SelectObject(pOldFont);
              }
              else
              { cDC.SelectObject(pOldFont);
                break;
              }
            }
            else break;
          }
          if (((rCalc.top+nHeight[1] > rCalc.bottom  ||  bOverlap) &&  nColumn == nColumns-1) ||  !rClip.Height())
          { if (nPages > 0  && (nPage == nPages  || (nFromPage > 0  &&  nToPage > 0  &&  nFromPage <= nToPage  &&  nPage == nToPage)))
            { nPages = nPage;
              nLines = nLine;
              nColumns = nColumn;
              break;
            }
            if (bOutput  && (!nPages  || ((!nPage  || (nFromPage > 0  &&  nToPage > 0  &&  nFromPage <= nToPage  && (nPage < nFromPage  ||  nPage > nToPage)) ||  cDC.EndPage() >= 0) && ((nFromPage > 0  &&  nToPage > 0  &&  nFromPage <= nToPage  && (nPage < nFromPage-1  ||  nPage >= nToPage)) || (((((nFromPage <= 0  ||  nToPage <= 0  ||  nFromPage > nToPage) &&  nPage > 0) || (nFromPage > 0  &&  nToPage > 0  &&  nFromPage <= nToPage  &&  nPage != nFromPage-1)) ||  StartPrintJob(cDC)) &&  cDC.StartPage() >= 0)))))
            { if (cDC.SelectClipRgn(&rgnArea) != ERROR  &&  DrawPrintDocPage(cDC,pJobInfo,tPrint,pszPrinterName,rtMargin,bMetric,cLayout,nMode,pszTMUnit,tTMUnit,nTMUnit,bQuality,(nView != POD_VIEW_DATA) ? ((nView != POD_VIEW_PARAMETERS) ? STRING(IDS_POD_TITLEITEM_FUNCTIONS):STRING(IDS_POD_TITLEITEM_PARAMETERS)):STRING(IDS_POD_TITLEITEM_DATA),szColumns[nView],nOOLColors,pFonts,nTabs[nView],nPages,(nPages > 0  && (nFromPage <= 0  ||  nToPage <= 0  ||  nFromPage > nToPage  || (nPage >= nFromPage-1  &&  nPage < nToPage))) ? (nPage+1):0,rClip) &&  cDC.IntersectClipRect(rClip) != ERROR)
              { rCalc.SetRect(rClip.left,rClip.top-rCalc.Height()-nSpacing,rClip.right,rClip.bottom);
                bOverlap = FALSE;
                bOutput = FALSE;
                nColumn = -1;
                nPage++;
                continue;
              }
            }
            break;
          }
          bOverlap = (rCalc.top+nHeight[1] > rCalc.bottom) ? TRUE:bOverlap;
        }
        if (nLine < nLines  &&  nColumn == nColumns)
        { rCalc.DeflateRect(0,nHeight[0],0,0);
          continue;
        }
        break;
      }
      if (nLine == nLines)
      { if (nPage <= nPages  ||  !nPages)
        { if (nView == POD_VIEW_DATA  && (pJobInfo -> GetPrintMode() & POD_PRINT_PARAMETERS) &&  szContents[POD_VIEW_PARAMETERS].GetSize() > 0)
          { if (DrawPrintDocListTitle(cDC,(rItem = rCalc),GetPrintDocListTitle(STRING(IDS_POD_TITLEITEM_PARAMETERS)),&cFont[POD_PRINTFONT_PARAMETERSTITLE],TRUE) &&  DrawPrintDocListItemsTitle(cDC,rItem,szColumns[POD_VIEW_PARAMETERS],&cFont[POD_PRINTFONT_PARAMETERSLISTITEMSTITLE],nTabs[POD_VIEW_PARAMETERS],TRUE) &&  DrawPrintDocListItemsTitle(cDC,rItem,szColumns[POD_VIEW_PARAMETERS],&cFont[POD_PRINTFONT_PARAMETERSLISTITEMSTITLE],nTabs[POD_VIEW_PARAMETERS],TRUE) && (rItem.top > rItem.bottom  || (DrawPrintDocListTitle(cDC,rCalc,GetPrintDocListTitle(STRING(IDS_POD_TITLEITEM_PARAMETERS)),&cFont[POD_PRINTFONT_PARAMETERSTITLE]) &&  DrawPrintDocListItemsTitle(cDC,rCalc,szColumns[POD_VIEW_PARAMETERS],&cFont[POD_PRINTFONT_PARAMETERSLISTITEMSTITLE],nTabs[POD_VIEW_PARAMETERS]))))
            { rCalc.SetRect(rCalc.left,(rItem.top <= rItem.bottom) ? rCalc.top:rClip.bottom,rCalc.right,rClip.bottom);
              continue;
            }
            nPages = -1;
            break;
          }
          if (nView == POD_VIEW_PARAMETERS  && (pJobInfo -> GetPrintMode() & POD_PRINT_FUNCTIONS) &&  szContents[POD_VIEW_FUNCTIONS].GetSize() > 0)
          { if (DrawPrintDocListTitle(cDC,(rItem = rCalc),GetPrintDocListTitle(STRING(IDS_POD_TITLEITEM_FUNCTIONS)),&cFont[POD_PRINTFONT_FUNCTIONSTITLE],TRUE) &&  DrawPrintDocListItemsTitle(cDC,rItem,szColumns[POD_VIEW_FUNCTIONS],&cFont[POD_PRINTFONT_FUNCTIONSLISTITEMSTITLE],nTabs[POD_VIEW_FUNCTIONS],TRUE) &&  DrawPrintDocListItemsTitle(cDC,rItem,szColumns[POD_VIEW_FUNCTIONS],&cFont[POD_PRINTFONT_FUNCTIONSLISTITEMSTITLE],nTabs[POD_VIEW_FUNCTIONS],TRUE) && (rItem.top > rItem.bottom  || (DrawPrintDocListTitle(cDC,rCalc,GetPrintDocListTitle(STRING(IDS_POD_TITLEITEM_FUNCTIONS)),&cFont[POD_PRINTFONT_FUNCTIONSTITLE]) &&  DrawPrintDocListItemsTitle(cDC,rCalc,szColumns[POD_VIEW_FUNCTIONS],&cFont[POD_PRINTFONT_FUNCTIONSLISTITEMSTITLE],nTabs[POD_VIEW_FUNCTIONS]))))
            { rCalc.SetRect(rCalc.left,(rItem.top <= rItem.bottom) ? rCalc.top:rClip.bottom,rCalc.right,rClip.bottom);
              continue;
            }
            nPages = -1;
            break;
          }
          continue;
        }
      }
      break;
    }
    if (nPages >= 0)
    { if (nLine == nLines)
      { if (!szContents[nView].GetSize())
        { if (nFromPage > 0  &&  nToPage > 0  &&  nFromPage <= nToPage  &&  nFromPage > 1)
          { nPages = nPage = 0;
            break; 
          }
          if (StartPrintJob(cDC))
          { if (cDC.StartPage() >= 0)
            { if (DrawPrintDocPage(cDC,pJobInfo,tPrint,pszPrinterName,rtMargin,bMetric,cLayout,nMode,pszTMUnit,tTMUnit,nTMUnit,bQuality,(nView != POD_VIEW_DATA) ? ((nView != POD_VIEW_PARAMETERS) ? STRING(IDS_POD_TITLEITEM_FUNCTIONS):STRING(IDS_POD_TITLEITEM_PARAMETERS)):STRING(IDS_POD_TITLEITEM_DATA),szColumns[nView],nOOLColors,pFonts,nTabs[nView],1,1,rClip))
              { nPages = nPage = 1;
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
        { if (nFromPage <= 0  ||  nToPage <= 0  ||  nFromPage > nToPage  ||  nPage >= nFromPage)
          { nPages = nPage;
            nPage = 0;
            continue;
          }
          nPages = nPage = 0;
        }
      }
      else
      { if (nPages > 0) cDC.AbortDoc();
        nPages = -1;
      }
    }
    break;
  }
  return(((!nPages  || (nPages > 0  && ((nFromPage > 0  &&  nToPage > 0  &&  nFromPage <= nToPage  &&  nPage < nFromPage) || (cDC.EndPage() >= 0  &&  EndPrintJob(cDC))))) &&  nPage == nPages) ? TRUE:FALSE);
}

BOOL CPODWnd::EndPrintJob(CDC &cDC)
{
  return((cDC.EndDoc() >= 0) ? TRUE:FALSE);
}

BOOL CPODWnd::DrawPrintDocPage(CDC &cDC,CONST CPODPrintJobInfo *pJobInfo,CONST CTimeKey &tTime,LPCTSTR pszPrinterName,CONST RECT &rtMargin,BOOL bMetric,CONST CPODLayout &cLayout,UINT nMode,LPCTSTR pszTMUnit,CONST CTimeTag &tTMUnit,UINT nTMUnit,BOOL bQuality,LPCTSTR pszTitle,CONST CStringArray &szColumns,CONST CUIntArray &nOOLColors,CONST CPtrArray &pFonts,CONST CUIntArray &nTabs,INT nPages,INT nPage,LPRECT prClip)
{
  return((CalcPrintDocRect(cDC,rtMargin,bMetric) &&  cDC.GetClipBox(prClip) != ERROR  &&  DrawPrintDocTitle(cDC,prClip,GetPrintDocTitle(),(CFont *) pFonts.GetAt(POD_PRINTFONT_TITLE),(nPage <= 0) ? TRUE:FALSE) &&  DrawPrintDocSubTitle(cDC,prClip,GetPrintDocSubTitle(cLayout),(CFont *) pFonts.GetAt(POD_PRINTFONT_SUBTITLE),(nPage <= 0) ? TRUE:FALSE) &&  DrawPrintDocOperatingDetails(cDC,prClip,GetPrintDocOperatingDetails(pJobInfo,nMode,pszTMUnit,tTMUnit,nTMUnit,bQuality),(CFont *) pFonts.GetAt(POD_PRINTFONT_OPERATINGDETAILS),(nPage <= 0) ? TRUE:FALSE) &&  DrawPrintDocOperatingMode(cDC,prClip,GetPrintDocOperatingMode(pJobInfo,nOOLColors),nOOLColors,(CFont *) pFonts.GetAt(POD_PRINTFONT_OPERATINGMODE),(nPage <= 0) ? TRUE:FALSE) && (lstrcmp(pszTitle,STRING(IDS_POD_TITLEITEM_DATA)) || (DrawPrintDocListTitle(cDC,prClip,GetPrintDocListTitle(pszTitle),(CFont *) pFonts.GetAt(POD_PRINTFONT_DATATITLE),(nPage <= 0) ? TRUE:FALSE) &&  DrawPrintDocListItemsTitle(cDC,prClip,szColumns,(CFont *) pFonts.GetAt(POD_PRINTFONT_DATALISTITEMSTITLE),nTabs,(nPage <= 0) ? TRUE:FALSE))) && (lstrcmp(pszTitle,STRING(IDS_POD_TITLEITEM_PARAMETERS)) || (DrawPrintDocListTitle(cDC,prClip,GetPrintDocListTitle(pszTitle),(CFont *) pFonts.GetAt(POD_PRINTFONT_PARAMETERSTITLE),(nPage <= 0) ? TRUE:FALSE) &&  DrawPrintDocListItemsTitle(cDC,prClip,szColumns,(CFont *) pFonts.GetAt(POD_PRINTFONT_PARAMETERSLISTITEMSTITLE),nTabs,(nPage <= 0) ? TRUE:FALSE))) && (lstrcmp(pszTitle,STRING(IDS_POD_TITLEITEM_FUNCTIONS)) || (DrawPrintDocListTitle(cDC,prClip,GetPrintDocListTitle(pszTitle),(CFont *) pFonts.GetAt(POD_PRINTFONT_FUNCTIONSTITLE),(nPage <= 0) ? TRUE:FALSE) &&  DrawPrintDocListItemsTitle(cDC,prClip,szColumns,(CFont *) pFonts.GetAt(POD_PRINTFONT_FUNCTIONSLISTITEMSTITLE),nTabs,(nPage <= 0) ? TRUE:FALSE))) &&  DrawPrintDocNotice(cDC,prClip,GetPrintDocNotice(),(CFont *) pFonts.GetAt(POD_PRINTFONT_NOTICE),(CFont *) pFonts.GetAt(POD_PRINTFONT_LOGO),(nPage <= 0) ? TRUE:FALSE) &&  DrawPrintDocFooter(cDC,prClip,GetPrintDocFooter(tTime,pszPrinterName,nPages,nPage),(CFont *) pFonts.GetAt(POD_PRINTFONT_FOOTER),(nPage <= 0) ? TRUE:FALSE)) ? TRUE:FALSE);
}

BOOL CPODWnd::DrawPrintDocTitle(CDC &cDC,LPRECT prClip,LPCTSTR pszTitle,CFont *pFont,BOOL bCalc)
{
  CRect  rCalc;
  CFont  *pOldFont;

  if ((pOldFont = cDC.SelectObject(pFont)))
  { cDC.DrawText(pszTitle,(rCalc=CRect(0,0,prClip -> right-prClip -> left,0)),DT_CALCRECT | DT_CENTER | DT_NOPREFIX | DT_SINGLELINE);
    cDC.DrawText(pszTitle,(!bCalc) ? prClip:CRect(0,0,0,0),DT_CENTER | DT_NOPREFIX | DT_SINGLELINE);
    prClip -> top += rCalc.Height();
    cDC.SelectObject(pOldFont);
    return TRUE;
  }
  return FALSE;
}

BOOL CPODWnd::DrawPrintDocSubTitle(CDC &cDC,LPRECT prClip,LPCTSTR pszTitle,CFont *pFont,BOOL bCalc)
{
  CRect  rCalc;
  CFont  *pOldFont;

  if ((pOldFont = cDC.SelectObject(pFont)))
  { cDC.DrawText(pszTitle,(rCalc=CRect(0,0,prClip -> right-prClip -> left,0)),DT_CALCRECT | DT_CENTER | DT_NOPREFIX | DT_SINGLELINE);
    cDC.DrawText(pszTitle,(!bCalc) ? prClip:CRect(0,0,0,0),DT_CENTER | DT_NOPREFIX | DT_SINGLELINE);
    prClip -> top += rCalc.Height();
    cDC.SelectObject(pOldFont);
    return TRUE;
  }
  return FALSE;
}

BOOL CPODWnd::DrawPrintDocOperatingDetails(CDC &cDC,LPRECT prClip,LPCTSTR pszComments,CFont *pFont,BOOL bCalc)
{
  CRect  rCalc;
  CFont  *pOldFont;

  if ((pOldFont = cDC.SelectObject(pFont)))
  { cDC.DrawText(pszComments,(rCalc=CRect(0,0,prClip -> right-prClip -> left,0)),DT_CALCRECT | DT_CENTER | DT_NOPREFIX | DT_WORDBREAK);
    cDC.DrawText(pszComments,(!bCalc) ? prClip:CRect(0,0,0,0),DT_CENTER | DT_NOPREFIX | DT_WORDBREAK);
    prClip -> top += rCalc.Height();
    cDC.SelectObject(pOldFont);
    return TRUE;
  }
  return FALSE;
}

BOOL CPODWnd::DrawPrintDocOperatingMode(CDC &cDC,LPRECT prClip,LPCTSTR pszMode,CONST CUIntArray &nOOLColors,CFont *pFont,BOOL bCalc)
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
  { szToken = szToken.Left((szToken = STRING(IDS_POD_PRINTDOCUMENT_OOLLEGEND)).Find(SPACE));
    szLegend[0] = ((nPos = (szMode = pszMode).Find(szToken)) >= 0) ? (LPCTSTR) szMode.Mid(nPos):EMPTYSTRING;
    cDC.DrawText((szMode=(nPos >= 0) ? szMode.Left(nPos):szMode),(rCalc=CRect(0,0,prClip -> right-prClip -> left,0)),DT_CALCRECT | DT_CENTER | DT_NOPREFIX | DT_WORDBREAK);
    cDC.DrawText(szMode,(!bCalc) ? prClip:CRect(0,0,0,0),DT_CENTER | DT_NOPREFIX | DT_WORDBREAK);
    for (szLegend[1] = szLegend[0]; (nPos = szLegend[1].Find(SPACE+szToken)) >= 0; )
    { for (szLegendPart = SPACE+szToken; --nPos >= 0; )
      { if (szLegend[1][nPos] != SPACE[0])
        { szLegendPart = szLegend[1][nPos]+szLegendPart;
          continue;
        }
        break;
      }
      if (nPos >= 0)
      { szLegendParts.Add(szLegend[1].Left((nPos=nPos+lstrlen(SPACE))));
        szLegendParts.Add(szLegendPart);
        szLegend[1] = szLegend[1].Mid(nPos+szLegendPart.GetLength());
        continue;
      }
      szLegend[0].Empty();
      szLegend[1].Empty();
      szLegendParts.RemoveAll();
      break;
    }
    szLegendParts.Add(szLegend[1]);
    for (nPart = 0,nParts = (INT) szLegendParts.GetSize(),X = prClip -> left+(prClip -> right-prClip -> left-cDC.GetTextExtent(szLegend[0]).cx)/2,Y = prClip -> top+rCalc.Height(),nHeight = 0; nPart < nParts; nPart++,X += cDC.GetTextExtent(szLegendParts.GetAt(nPart-1)).cx)
    { if (cDC.GetDeviceCaps(NUMCOLORS) > 2  &&  nPart%2  &&  nPart/2 < nOOLColors.GetSize())
      { nOldColor = cDC.SetTextColor(nOOLColors.GetAt(nPart/2));
        nHeight = cDC.DrawText(szLegendParts.GetAt(nPart),CRect(X,Y,prClip -> right,prClip -> bottom),DT_LEFT | DT_NOPREFIX | DT_WORDBREAK);
        cDC.SetTextColor(nOldColor);
        continue;
      }
      nHeight = cDC.DrawText(szLegendParts.GetAt(nPart),CRect(X,Y,prClip -> right,prClip -> bottom),DT_LEFT | DT_NOPREFIX | DT_WORDBREAK);
    }
    prClip -> top += rCalc.Height()+nHeight;
    cDC.SelectObject(pOldFont);
    return TRUE;
  }
  return FALSE;
}

BOOL CPODWnd::DrawPrintDocListTitle(CDC &cDC,LPRECT prClip,LPCTSTR pszTitle,CFont *pFont,BOOL bCalc)
{
  CRect  rCalc;
  CFont  *pOldFont;

  if ((pOldFont = cDC.SelectObject(pFont)))
  { cDC.DrawText(pszTitle,(rCalc=CRect(0,0,prClip -> right-prClip -> left,0)),DT_CALCRECT | DT_LEFT | DT_NOPREFIX | DT_WORDBREAK);
    cDC.DrawText(pszTitle,(!bCalc) ? prClip:CRect(0,0,0,0),DT_LEFT | DT_NOPREFIX | DT_WORDBREAK);
    prClip -> top += rCalc.Height();
    cDC.SelectObject(pOldFont);
    return TRUE;
  }
  return FALSE;
}

BOOL CPODWnd::DrawPrintDocListItemsTitle(CDC &cDC,LPRECT prClip,CONST CStringArray &szColumns,CFont *pFont,CONST CUIntArray &nTabs,BOOL bCalc)
{
  CSize  rCalc;
  CFont  *pOldFont;
  CString  szItems;

  if ((pOldFont = cDC.SelectObject(pFont)))
  { szItems = GetPrintDocListItemsTitle(szColumns);
    rCalc = (!bCalc) ? cDC.TabbedTextOut(prClip -> left,prClip -> top+cDC.GetTextExtent(szItems,szItems.GetLength()).cy,szItems,(INT) nTabs.GetSize(),(LPINT) nTabs.GetData(),prClip -> left):CSize(nTabs.GetAt(nTabs.GetSize()-1),cDC.GetTextExtent(szItems,szItems.GetLength()).cy);
    prClip -> top += 2*rCalc.cy;
    cDC.SelectObject(pOldFont);
    return TRUE;
  }
  return FALSE;
}

BOOL CPODWnd::DrawPrintDocNotice(CDC &cDC,LPRECT prClip,LPCTSTR pszNotice,CFont *pFont,CFont *pLogoFont,BOOL bCalc)
{
  INT  nPos;
  CFont  *pOldFont;
  CSize  sizeNotice[3];
  CString  szNotice[3];
  CString  szCopyrightNotice;
  CVersionInfo  cVersionInfo;

  for (szCopyrightNotice = pszNotice,sizeNotice[0].cx = sizeNotice[0].cy = 0,sizeNotice[1].cx = sizeNotice[1].cy = 0; (pOldFont = cDC.SelectObject(pFont)); )
  { szNotice[0] = ((nPos = szCopyrightNotice.Find((szNotice[2]=cVersionInfo.QueryCompanyName()))) >= 0) ? szCopyrightNotice.Left(nPos):szCopyrightNotice;
    szNotice[1] = (nPos >= 0) ? szCopyrightNotice.Mid(nPos+szNotice[2].GetLength()):EMPTYSTRING;
    sizeNotice[0] = cDC.GetTextExtent(szNotice[0]);
    sizeNotice[1] = cDC.GetTextExtent(szNotice[1]);
    cDC.SelectObject(pOldFont);
    break;
  }
  if ((pOldFont = cDC.SelectObject(pLogoFont)))
  { sizeNotice[2] = cDC.GetTextExtent(szNotice[2]);
    cDC.SelectObject(pOldFont);
  }
  if ((pOldFont = (sizeNotice[0].cx > 0  &&  sizeNotice[0].cy > 0  &&  sizeNotice[2].cx > 0  &&  sizeNotice[2].cy > 0) ? cDC.SelectObject(pFont):(CFont *) NULL))
  { cDC.TextOut(prClip -> left,prClip -> bottom-sizeNotice[0].cy,(!bCalc) ? (LPCTSTR) szNotice[0]:EMPTYSTRING);
    cDC.SelectObject(pOldFont);
  }
  if ((pOldFont = (sizeNotice[0].cx > 0  &&  sizeNotice[0].cy > 0  &&  sizeNotice[2].cx > 0  &&  sizeNotice[2].cy > 0) ? cDC.SelectObject(pLogoFont):(CFont *) NULL))
  { cDC.TextOut(prClip -> left+sizeNotice[0].cx,prClip -> bottom-sizeNotice[2].cy,(!bCalc) ? (LPCTSTR) szNotice[2]:EMPTYSTRING);
    cDC.SelectObject(pOldFont);
  }
  if ((pOldFont = (sizeNotice[0].cx > 0  &&  sizeNotice[0].cy > 0  &&  sizeNotice[1].cx > 0  &&  sizeNotice[1].cy > 0) ? cDC.SelectObject(pFont):(CFont *) NULL))
  { cDC.TextOut(prClip -> left+sizeNotice[0].cx+sizeNotice[2].cx,prClip -> bottom-sizeNotice[1].cy,(!bCalc) ? (LPCTSTR) szNotice[1]:EMPTYSTRING);
    cDC.SelectObject(pOldFont);
  }
  if (sizeNotice[0].cx > 0  &&  sizeNotice[0].cy > 0  &&  sizeNotice[2].cx > 0  &&  sizeNotice[2].cy > 0)
  { prClip -> bottom -= max(sizeNotice[0].cy,sizeNotice[2].cy);
    return TRUE;
  }
  return FALSE;
}

BOOL CPODWnd::DrawPrintDocFooter(CDC &cDC,LPRECT prClip,LPCTSTR pszFooter,CFont *pFont,BOOL bCalc)
{
  CRect  rCalc;
  CFont  *pOldFont;

  if ((pOldFont = cDC.SelectObject(pFont)))
  { cDC.DrawText(pszFooter,(rCalc=CRect(0,0,prClip -> right-prClip -> left,0)),DT_CALCRECT | DT_LEFT | DT_NOPREFIX | DT_SINGLELINE);
    cDC.DrawText(pszFooter,(!bCalc) ? prClip:CRect(0,0,0,0),DT_LEFT | DT_BOTTOM | DT_NOPREFIX | DT_SINGLELINE);
    prClip -> bottom -= 3*rCalc.Height();
    cDC.SelectObject(pOldFont);
    return TRUE;
  }
  return FALSE;
}

CString CPODWnd::GetPrintDocTitle() CONST
{
  CString  szTitle;

  szTitle.Format(STRING(IDS_POD_PRINTDOCUMENT_TITLE),(LPCTSTR) GetAccountSpacecraftName());
  return szTitle;
}

CString CPODWnd::GetPrintDocSubTitle(CONST CPODLayout &cLayout) CONST
{
  return cLayout.GetTitle();
}

CString CPODWnd::GetPrintDocOperatingDetails(CONST CPODPrintJobInfo *pJobInfo,UINT nMode,LPCTSTR pszTMUnit,CONST CTimeTag &tTMUnit,UINT nTMUnit,BOOL bQuality) CONST
{
  CString  szMode;
  CString  szUpdate;

  szMode = (nMode == DISPLAY_MODE_REALTIME) ? STRING(IDS_DISPLAY_MODE_REALTIME):STRING(IDS_DISPLAY_MODE_HISTORY);
  szUpdate.Format((!lstrlen(pszTMUnit)) ? ((tTMUnit > 0) ? STRING(IDS_POD_PRINTDOCUMENT_FULLUPDATECOMMENT):STRING(IDS_POD_PRINTDOCUMENT_NODATACOMMENT)):((nTMUnit == (UINT) -1) ? STRING(IDS_POD_PRINTDOCUMENT_INITUPDATECOMMENT):STRING(IDS_POD_PRINTDOCUMENT_UPDATECOMMENT)),(LPCTSTR) tTMUnit.FormatGmt(),pszTMUnit,nTMUnit,(bQuality) ? STRING(IDS_POD_PRINTDOCUMENT_QUALITYGOOD):STRING(IDS_POD_PRINTDOCUMENT_QUALITYBAD));
  return((!pJobInfo -> GetComments().IsEmpty()) ? (szUpdate+EOL+szMode+EOL+pJobInfo -> GetComments()):(szUpdate+EOL+szMode));
}

CString CPODWnd::GetPrintDocOperatingMode(CONST CPODPrintJobInfo *pJobInfo,CONST CUIntArray &nOOLColors) CONST
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

  if ((nFlags = pJobInfo -> GetPrintFlags()) & POD_PRINT_ATTIME)
  { if (pJobInfo -> GetPrintAtTime(tTime))
    { szInfo.Format(STRING(IDS_POD_PRINTDOCUMENT_PRINTATTIME),(LPCTSTR) tTime.FormatGmt());
      szInfo += EOL;
    }
    if ((pJobInfo -> GetPrintAtTime(tTime,tInterval) ||  pJobInfo -> GetPrintAtTime(tTime,tInterval,nStopCount) ||  pJobInfo -> GetPrintAtTime(tTime,tInterval,tStopTime)) &&  pJobInfo -> GetPrintLastTime(tLastTime))
    { szInfo.Format(STRING(IDS_POD_PRINTDOCUMENT_PRINTATTIME),(LPCTSTR) CTimeKey(tTime.GetTime()+((tLastTime.GetTime()-tTime.GetTime())/tInterval.GetTotalSeconds())*tInterval.GetTotalSeconds()).FormatGmt());
      szInfo += EOL;
    }
  }
  if (nFlags & POD_PRINT_ATDAILYTIME)
  { if (pJobInfo -> GetPrintAtDailyTime(tDailyTime) ||  pJobInfo -> GetPrintAtDailyTime(tDailyTime,nStopCount) ||  pJobInfo -> GetPrintAtDailyTime(tDailyTime,tStopTime))
    { szInfo.Format(STRING(IDS_POD_PRINTDOCUMENT_PRINTATDAILYTIME),(LPCTSTR) CTimeKey(SECONDSPERDAY*(CTime::GetCurrentTime().GetTime()/SECONDSPERDAY)+tDailyTime.GetTotalSeconds()).FormatGmt(STRING(IDS_TIMEKEY_TIMEFORMAT)));
      szInfo += EOL;
    }
  }
  if (nFlags & POD_PRINT_ATEVENT)
  { if (pJobInfo -> GetPrintAtEvent(szEvent))
    { szInfo.Format(STRING(IDS_POD_PRINTDOCUMENT_PRINTATEVENT),(LPCTSTR) szEvent);
      szInfo += EOL;
    }
  }
  if (!nFlags)
  { szInfo = STRING(IDS_POD_PRINTDOCUMENT_DEFAULTTIME);
    szInfo += EOL;
  }
  if ((nMode = pJobInfo -> GetPrintMode()) & POD_PRINT_ALL)
  { szInfo += STRING(IDS_POD_PRINTDOCUMENT_PRINTALL);
    szInfo += EOL;
  }
  if (((nMode & POD_PRINT_FIRSTSIDE) || (nMode & POD_PRINT_LASTSIDE)) &&  pJobInfo -> GetPrintBySide(nCount))
  { szSide.Format((nMode & POD_PRINT_FIRSTSIDE) ? STRING(IDS_POD_PRINTDOCUMENT_PRINTBYFIRSTSIDE):STRING(IDS_POD_PRINTDOCUMENT_PRINTBYLASTSIDE),nCount);
    szSide = (nCount == 1) ? ((nMode & POD_PRINT_FIRSTSIDE) ? STRING(IDS_POD_PRINTDOCUMENT_PRINTBYFIRSTITEM):STRING(IDS_POD_PRINTDOCUMENT_PRINTBYLASTITEM)):(LPCTSTR) szSide;
    szInfo += szSide+EOL;
  }
  if (nMode & POD_PRINT_COLORLEGEND)
  { for (nColor = 0; nColor < (UINT) nOOLColors.GetSize(); nColor++)
    { switch (nOOLColors.GetAt(nColor))
      { case VGA_COLOR_BLACK:
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
    szLegend.Format(STRING(IDS_POD_PRINTDOCUMENT_OOLLEGEND),(LPCTSTR) szOOLColors.GetAt(POD_OOLCOLOR_NOLIMIT),(LPCTSTR) szOOLColors.GetAt(POD_OOLCOLOR_SOFTLIMIT),(LPCTSTR) szOOLColors.GetAt(POD_OOLCOLOR_HARDLIMIT),(LPCTSTR) szOOLColors.GetAt(POD_OOLCOLOR_DELTALIMIT),(LPCTSTR) szOOLColors.GetAt(POD_OOLCOLOR_CONSISTENCYLIMIT));
    szInfo += szLegend+EOL;
  }
  return szInfo;
}

CString CPODWnd::GetPrintDocListTitle(LPCTSTR pszTitle) CONST
{
  return CString(EOL)+CString(EOL)+pszTitle;
}

CString CPODWnd::GetPrintDocListItemsTitle(CONST CStringArray &szColumns) CONST
{
  INT  nColumn;
  INT  nColumns;
  CString  szItems;

  for (nColumn = 0,nColumns = (INT) szColumns.GetSize(); nColumn < nColumns; nColumn++)
  { szItems += (nColumn > 0) ? CString(TAB):EMPTYSTRING;
    szItems += szColumns.GetAt(nColumn);
  }
  return szItems;
}

CString CPODWnd::GetPrintDocNotice() CONST
{
  CVersionInfo  cVersionInfo;

  return cVersionInfo.QueryComments();
}

CString CPODWnd::GetPrintDocFooter(CONST CTimeKey &tTime,LPCTSTR pszPrinterName,INT nPages,INT nPage) CONST
{
  CString  szFooter;

  szFooter.Format(STRING(IDS_POD_PRINTDOCUMENT_FOOTER),(LPCTSTR) tTime.Format(IDS_TIMEKEY_DATEFORMAT),(LPCTSTR) tTime.Format(IDS_TIMEKEY_TIMEFORMAT),pszPrinterName,nPage,nPages);
  return szFooter;
}

INT CPODWnd::ExtractPrintDocText(LPCTSTR pszText,CStringArray &szColumnsText) CONST
{
  INT  nPos[2];
  INT  nLength;
  CString  szText;

  for (nPos[0] = 0,nLength = lstrlen(pszText),szColumnsText.RemoveAll(); nPos[0] <= nLength; nPos[0] += ++nPos[1])
  { if ((nPos[1] = (INT) _tcscspn((szText=pszText+nPos[0]),CString(CTextView::GetColumnDelimiter()))) < nLength-nPos[0])
    { szColumnsText.Add((nPos[1] > 0) ? szText.Left(nPos[1]):EMPTYSTRING);
      continue;
    }
    szColumnsText.Add(szText);
    break;
  }
  return((INT) szColumnsText.GetSize());
}

BOOL CPODWnd::CalcPrintDocTitleFont(CDC &cDC,CONST RECT &rArea,CFont &cFont) CONST
{
  return cFont.CreateFont(max(-(rArea.right-rArea.left)/48,(INT) ((-5.3*(double) cDC.GetDeviceCaps(HORZRES))/(double) cDC.GetDeviceCaps(HORZSIZE))),0,0,0,FW_BOLD,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,VARIABLE_PITCH | FF_DONTCARE,(LPCTSTR) NULL);
}

BOOL CPODWnd::CalcPrintDocSubTitleFont(CDC &cDC,CONST RECT &rArea,CFont &cFont) CONST
{
  return cFont.CreateFont(max(-(rArea.right-rArea.left)/64,(INT) ((-4.0*(double) cDC.GetDeviceCaps(HORZRES))/(double) cDC.GetDeviceCaps(HORZSIZE))),0,0,0,FW_BOLD,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,VARIABLE_PITCH | FF_DONTCARE,(LPCTSTR) NULL);
}

BOOL CPODWnd::CalcPrintDocOperatingDetailsFont(CDC &cDC,CONST RECT &rArea,CFont &cFont) CONST
{
  return cFont.CreateFont(max(-(rArea.right-rArea.left)/76,(INT) ((-3.3*(double) cDC.GetDeviceCaps(HORZRES))/(double) cDC.GetDeviceCaps(HORZSIZE))),0,0,0,FW_NORMAL,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,VARIABLE_PITCH | FF_DONTCARE,(LPCTSTR) NULL);
}

BOOL CPODWnd::CalcPrintDocOperatingModeFont(CDC &cDC,CONST RECT &rArea,CFont &cFont) CONST
{
  return cFont.CreateFont(max(-(rArea.right-rArea.left)/76,(INT) ((-3.3*(double) cDC.GetDeviceCaps(HORZRES))/(double) cDC.GetDeviceCaps(HORZSIZE))),0,0,0,FW_NORMAL,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,VARIABLE_PITCH | FF_DONTCARE,(LPCTSTR) NULL);
}

BOOL CPODWnd::CalcPrintDocListTitleFont(CDC &cDC,INT nView,CONST RECT &rArea,CFont &cFont) CONST
{
  return cFont.CreateFont(max(-(rArea.right-rArea.left)/64,(INT) ((-4.0*(double) cDC.GetDeviceCaps(HORZRES))/(double) cDC.GetDeviceCaps(HORZSIZE))),0,0,0,FW_BOLD,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,VARIABLE_PITCH | FF_DONTCARE,(LPCTSTR) NULL);
}

BOOL CPODWnd::CalcPrintDocListItemsFonts(CDC &cDC,INT nView,CONST RECT &rArea,CONST CStringArray &szColumns,CONST CStringArray &szContents,CONST LOGFONT *pTitleFont,CONST LOGFONT *pItemsFont,CONST LOGFONT *pValuesFont,CFont &cTitleFont,CFont &cItemsFont,CFont &cValuesFont) CONST
{
  INT  nWidth;
  INT  nHeight;
  CFont  cFont[3];
  CUIntArray  nTabs;

  for (nHeight = max(-(rArea.right-rArea.left)/64,(INT) ((-4.0*(double) cDC.GetDeviceCaps(HORZRES))/(double) cDC.GetDeviceCaps(HORZSIZE))); nHeight < 0; nHeight++)
  { if (cFont[0].CreateFont(nHeight,0,pTitleFont -> lfEscapement,pTitleFont -> lfOrientation,FW_BOLD,pTitleFont -> lfItalic,pTitleFont -> lfUnderline,pTitleFont -> lfStrikeOut,pTitleFont -> lfCharSet,pTitleFont -> lfOutPrecision,pTitleFont -> lfClipPrecision,pTitleFont -> lfQuality,pTitleFont -> lfPitchAndFamily,pTitleFont -> lfFaceName))
    { if (cFont[1].CreateFont((4*nHeight)/5,0,pItemsFont -> lfEscapement,pItemsFont -> lfOrientation,pItemsFont -> lfWeight,pItemsFont -> lfItalic,pItemsFont -> lfUnderline,pItemsFont -> lfStrikeOut,pItemsFont -> lfCharSet,pItemsFont -> lfOutPrecision,pItemsFont -> lfClipPrecision,pItemsFont -> lfQuality,pItemsFont -> lfPitchAndFamily,pItemsFont -> lfFaceName))
      { if (cFont[2].CreateFont((4*nHeight)/5,0,pValuesFont -> lfEscapement,pValuesFont -> lfOrientation,pValuesFont -> lfWeight,pValuesFont -> lfItalic,pValuesFont -> lfUnderline,pValuesFont -> lfStrikeOut,pValuesFont -> lfCharSet,pValuesFont -> lfOutPrecision,pValuesFont -> lfClipPrecision,pValuesFont -> lfQuality,pValuesFont -> lfPitchAndFamily,pValuesFont -> lfFaceName))
        { if (CalcPrintDocTitleWidth(cDC,nView,szColumns,szContents,&cFont[0],&cFont[1],&cFont[2],nTabs) > 0)
          { if ((nWidth = nTabs.GetAt(nTabs.GetSize()-1)) > rArea.right-rArea.left)
            { nHeight = (nHeight*(rArea.right-rArea.left))/nWidth-1;
              cFont[0].DeleteObject();
              cFont[1].DeleteObject();
              cFont[2].DeleteObject();
              continue;
            }
            cTitleFont.Attach(cFont[0].Detach());
            cItemsFont.Attach(cFont[1].Detach());
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
  return((cTitleFont.GetSafeHandle() &&  cItemsFont.GetSafeHandle() &&  cValuesFont.GetSafeHandle()) ? TRUE:FALSE);
}

BOOL CPODWnd::CalcPrintDocNoticeFonts(CDC &cDC,CONST RECT &rArea,CFont &cFont,CFont &cLogoFont) CONST
{
  return cFont.CreateFont(max(-(rArea.right-rArea.left)/96,(INT) ((-2.6*(double) cDC.GetDeviceCaps(HORZRES))/(double) cDC.GetDeviceCaps(HORZSIZE))),0,0,0,FW_BOLD,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,VARIABLE_PITCH | FF_DONTCARE,(LPCTSTR) NULL) &&  cLogoFont.CreateFont(max(-(rArea.right-rArea.left)/96,(INT) ((-2.6*(double) cDC.GetDeviceCaps(HORZRES))/(double) cDC.GetDeviceCaps(HORZSIZE))),0,0,0,FW_BOLD,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,VARIABLE_PITCH | FF_DONTCARE,STRING(IDS_FONTFACE_COMPANYLOGO));
}

BOOL CPODWnd::CalcPrintDocFooterFont(CDC &cDC,CONST RECT &rArea,CFont &cFont) CONST
{
  return cFont.CreateFont(max(-(rArea.right-rArea.left)/80,(INT) ((-3.0*(double) cDC.GetDeviceCaps(HORZRES))/(double) cDC.GetDeviceCaps(HORZSIZE))),0,0,0,FW_BOLD,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,VARIABLE_PITCH | FF_DONTCARE,(LPCTSTR) NULL);
}

INT CPODWnd::CalcPrintDocTitleWidth(CDC &cDC,INT nView,LPCTSTR pszColumn,CFont *pTitleFont) CONST
{
  INT  nWidth;
  CFont  *pOldFont;

  if ((pOldFont = cDC.SelectObject(pTitleFont)))
  { nWidth = cDC.GetTextExtent(pszColumn,lstrlen(pszColumn)).cx;
    cDC.SelectObject(pOldFont);
    return nWidth;
  }
  return 0;
}
INT CPODWnd::CalcPrintDocTitleWidth(CDC &cDC,INT nView,CONST CStringArray &szColumns,CONST CStringArray &szContents,CFont *pTitleFont,CFont *pItemsFont,CFont *pValuesFont,CUIntArray &nTabs) CONST
{
  INT  nIndent;
  INT  nColumn;
  INT  nColumns;
  INT  nWidth[2];
  CFont  *pOldFont;
  TEXTMETRIC  tmFont;
  CStringArray  szLines;

  for (nIndent = 0,nTabs.RemoveAll(); (pOldFont = cDC.SelectObject(pTitleFont)); )
  { nIndent = (cDC.GetTextMetrics(&tmFont)) ? max(tmFont.tmAveCharWidth,nIndent):nIndent;
    cDC.SelectObject(pOldFont);
    break;
  }
  if ((pOldFont = cDC.SelectObject(pItemsFont)))
  { if (cDC.GetTextMetrics(&tmFont)) nIndent = max(tmFont.tmAveCharWidth,nIndent);
    cDC.SelectObject(pOldFont);
  }
  for (nColumn = 0,nColumns = (INT) szColumns.GetSize(),szLines.Copy(szContents); nColumn < nColumns; nColumn++)
  { nWidth[0] = CalcPrintDocTitleWidth(cDC,nView,szColumns.GetAt(nColumn),pTitleFont);
    nWidth[1] = CalcPrintDocColumnWidth(cDC,nView,szColumns.GetAt(nColumn),szLines,pItemsFont,pValuesFont);
    nTabs.Add((nTabs.GetSize() > 0) ? (2*nIndent+nTabs.GetAt(nTabs.GetSize()-1)+max(nWidth[0],nWidth[1])):(2*nIndent+max(nWidth[0],nWidth[1])));
  }
  if (nTabs.GetSize() > 0)
  { nTabs.SetAt(nTabs.GetSize()-1,nTabs.GetAt(nTabs.GetSize()-1)-nIndent);
    return((INT) nTabs.GetSize());
  }
  return 0;
}

INT CPODWnd::CalcPrintDocColumnWidth(CDC &cDC,INT nView,LPCTSTR pszColumn,CStringArray &szContents,CFont *pItemsFont,CFont *pValuesFont) CONST
{
  INT  nPos;
  INT  nLine;
  INT  nLines;
  INT  nWidth;
  CFont  *pOldFont;

  if ((pOldFont = ((nView == POD_VIEW_DATA  &&  lstrcmp(pszColumn,STRING(IDS_POD_DATAHEADER_VALUE))) || (nView == POD_VIEW_PARAMETERS  &&  lstrcmp(pszColumn,STRING(IDS_POD_PARAMETERSHEADER_VALUE))) || (nView == POD_VIEW_FUNCTIONS  &&  lstrcmp(pszColumn,STRING(IDS_POD_FUNCTIONSHEADER_VALUE)))) ? cDC.SelectObject(pItemsFont):cDC.SelectObject(pValuesFont)))
  { for (nLine = 0,nLines = (INT) szContents.GetSize(),nWidth = 0; nLine < nLines; nLine++)
    { if ((nPos = szContents.GetAt(nLine).Find(CTextView::GetColumnDelimiter())) >= 0)
      { nWidth = max(cDC.GetTextExtent(szContents.GetAt(nLine).Left(nPos)).cx,nWidth);
        szContents.SetAt(nLine,szContents.GetAt(nLine).Mid(nPos+1));
        continue;
      }
      if (szContents.GetAt(nLine).GetLength() > 0)
      { nWidth = max(cDC.GetTextExtent(szContents.GetAt(nLine)).cx,nWidth);
        szContents.SetAt(nLine,EMPTYSTRING);
        continue;
      }
    }
    cDC.SelectObject(pOldFont);
    return nWidth;
  }
  return 0;
}

BOOL CPODWnd::CalcPrintDocRect(CDC &cDC,CONST RECT &rtMargin,BOOL bMetric) CONST
{
  CRect  rClip;

  rClip.SetRect(0,0,cDC.GetDeviceCaps(HORZRES),cDC.GetDeviceCaps(VERTRES));
  rClip.DeflateRect((bMetric) ? (rtMargin.left*cDC.GetDeviceCaps(HORZRES))/(100*cDC.GetDeviceCaps(HORZSIZE)):(rtMargin.left*cDC.GetDeviceCaps(LOGPIXELSX))/1000,(bMetric) ? (rtMargin.top*cDC.GetDeviceCaps(VERTRES))/(100*cDC.GetDeviceCaps(VERTSIZE)):(rtMargin.top*cDC.GetDeviceCaps(LOGPIXELSY))/1000,(bMetric) ? (rtMargin.right*cDC.GetDeviceCaps(HORZRES))/(100*cDC.GetDeviceCaps(HORZSIZE)):(rtMargin.right*cDC.GetDeviceCaps(LOGPIXELSX))/1000,(bMetric) ? (rtMargin.bottom*cDC.GetDeviceCaps(VERTRES))/(100*cDC.GetDeviceCaps(VERTSIZE)):(rtMargin.bottom*cDC.GetDeviceCaps(LOGPIXELSY))/1000);
  return((cDC.IntersectClipRect(rClip) != ERROR) ? TRUE:FALSE);
}

BEGIN_MESSAGE_MAP(CPODWnd, CDisplayWnd)
	//{{AFX_MSG_MAP(CPODWnd)
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
	ON_COMMAND(IDM_PODSETTINGS,OnSettings)
	ON_COMMAND(IDM_PODLINKAGES,OnLinkages)
	ON_COMMAND(IDM_PODHOLD,OnHold)
	ON_COMMAND(IDM_PODCLEARALL,OnClearAll)
	ON_COMMAND(IDM_PODRETRIEVALS,OnRetrievals)
	ON_COMMAND(IDM_PODRETRIEVESTOP,OnRetrieveStop)
	ON_COMMAND(IDM_PODRETRIEVEFORWARD,OnRetrieveAutoForward)
	ON_COMMAND(IDM_PODRETRIEVEBACKWARD,OnRetrieveAutoBackward)
	ON_COMMAND(IDM_PODRETRIEVESTEPFORWARD,OnRetrieveManualForward)
	ON_COMMAND(IDM_PODRETRIEVESTEPBACKWARD,OnRetrieveManualBackward)
	ON_COMMAND(IDM_PODRETRIEVEPSEUDOREALTIME,OnRetrievePseudoRealtime)
	ON_COMMAND(IDM_PODPRINT,OnPrint)
	ON_UPDATE_COMMAND_UI(IDM_PODSETTINGS,OnUpdateSettings)
	ON_UPDATE_COMMAND_UI(IDM_PODLINKAGES,OnUpdateLinkages)
	ON_UPDATE_COMMAND_UI(IDM_PODHOLD,OnUpdateHold)
	ON_UPDATE_COMMAND_UI(IDM_PODCLEARALL,OnUpdateClearAll)
	ON_UPDATE_COMMAND_UI(IDM_PODRETRIEVALS,OnUpdateRetrievals)
	ON_UPDATE_COMMAND_UI(IDM_PODRETRIEVESTOP,OnUpdateRetrieveStop)
	ON_UPDATE_COMMAND_UI(IDM_PODRETRIEVEFORWARD,OnUpdateRetrieveAutoForward)
	ON_UPDATE_COMMAND_UI(IDM_PODRETRIEVEBACKWARD,OnUpdateRetrieveAutoBackward)
	ON_UPDATE_COMMAND_UI(IDM_PODRETRIEVESTEPFORWARD,OnUpdateRetrieveManualForward)
	ON_UPDATE_COMMAND_UI(IDM_PODRETRIEVESTEPBACKWARD,OnUpdateRetrieveManualBackward)
	ON_UPDATE_COMMAND_UI(IDM_PODRETRIEVEPSEUDOREALTIME,OnUpdateRetrievePseudoRealtime)
	ON_UPDATE_COMMAND_UI(IDM_PODPRINT,OnUpdatePrint)
	ON_UPDATE_COMMAND_UI(ID_POD_STATUSBAR_MESSAGEPANE,OnUpdateStatusBarMessagePane)
	ON_UPDATE_COMMAND_UI(ID_POD_STATUSBAR_MODEPANE,OnUpdateStatusBarModePane)
	ON_UPDATE_COMMAND_UI(ID_POD_STATUSBAR_TYPEPANE,OnUpdateStatusBarTypePane)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPODWnd message handlers

int CPODWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
  if (CDisplayWnd::OnCreate(lpCreateStruct) != -1)
  { for (EnableDocking(CBRS_ALIGN_TOP); CreateToolBar() &&  CreateStatusBar() &&  CreateSplitterBars() &&  CreateViews() &&  LoadAccelTable(MAKEINTRESOURCE(IDR_PODFRAME)); )
    { UpdateBars();
      return 0;
    }
  }
  return -1;
}

void CPODWnd::OnGetMinMaxInfo(MINMAXINFO *lpMMI) 
{
  CRect  rWnd;

  rWnd = RepositionViews(FALSE);
  lpMMI -> ptMinTrackSize.x = max(lpMMI -> ptMinTrackSize.x,rWnd.Width());
  lpMMI -> ptMinTrackSize.y = max(lpMMI -> ptMinTrackSize.y,rWnd.Height());
  CDisplayWnd::OnGetMinMaxInfo(lpMMI);
}

void CPODWnd::OnSize(UINT nType,int cx,int cy)
{
  for (CDisplayWnd::OnSize(nType,cx,cy); nType != SIZE_MINIMIZED; )
  { if (IsWindow(m_wndDataView.GetSafeHwnd()) &&  IsWindow(m_wndSplitterBarCtrl[0].GetSafeHwnd()) &&  IsWindow(m_wndParametersView.GetSafeHwnd()) &&  IsWindow(m_wndSplitterBarCtrl[1].GetSafeHwnd()) &&  IsWindow(m_wndFunctionsView.GetSafeHwnd()))
    { m_wndDataView.MoveWindow(RepositionView(POD_VIEW_DATA));
      m_wndSplitterBarCtrl[0].MoveWindow(RepositionViewSplitterBar(TRUE));
      m_wndParametersView.MoveWindow(RepositionView(POD_VIEW_PARAMETERS));
      m_wndSplitterBarCtrl[1].MoveWindow(RepositionViewSplitterBar(FALSE));
      m_wndFunctionsView.MoveWindow(RepositionView(POD_VIEW_FUNCTIONS));
    }
    break;
  }
}

BOOL CPODWnd::OnEraseBkgnd(CDC *pDC)
{
  if (!IsInitialized())
  { m_wndToolBar.UpdateWindow();
    m_wndStatusBar.UpdateWindow();
  }
  return TRUE;
}

void CPODWnd::OnSetFocus(CWnd *pOldWnd)
{
  if (IsWindow(pOldWnd -> GetSafeHwnd()))
  { if (IsViewVisible(POD_VIEW_PARAMETERS) &&  m_wndDataView.IsChild(pOldWnd))
    { if (!RepositionViewSplitterBar(TRUE).IsRectEmpty() &&  !RepositionViewSplitterBar(FALSE).IsRectEmpty())
      { m_wndParametersView.SetFocus();
        return;
      }
      if (!RepositionViewSplitterBar(TRUE).IsRectEmpty())
      { if (IsViewVisible(POD_VIEW_PARAMETERS))
        { m_wndParametersView.SetFocus();
          return;
        }
        if (IsViewVisible(POD_VIEW_FUNCTIONS))
        { m_wndFunctionsView.SetFocus();
          return;
        }
      }
    }
    if (IsViewVisible(POD_VIEW_FUNCTIONS) &&  m_wndParametersView.IsChild(pOldWnd))
    { if (!RepositionViewSplitterBar(TRUE).IsRectEmpty() &&  !RepositionViewSplitterBar(FALSE).IsRectEmpty())
      { m_wndFunctionsView.SetFocus();
        return;
      }
      if (!RepositionViewSplitterBar(TRUE).IsRectEmpty())
      { if (IsViewVisible(POD_VIEW_FUNCTIONS))
        { m_wndFunctionsView.SetFocus();
          return;
        }
      }
    }
    if (!IsChild(pOldWnd))
    { if (m_wndDataView.GetTextCount() > 0)
      { m_wndDataView.SetFocus();
        return;
      }
    }
    GetParent() -> SetFocus();
    return;
  }
  CDisplayWnd::OnSetFocus(pOldWnd);
}

BOOL CPODWnd::OnSetCursor(CWnd *pWnd,UINT nHitTest,UINT message) 
{
  POINT  ptCursor;

  for (GetCursorPos(&ptCursor),ScreenToClient(&ptCursor); RepositionViewSplitterBar(TRUE).PtInRect(ptCursor) ||  RepositionViewSplitterBar(FALSE).PtInRect(ptCursor); )
  { SetCursor(LoadCursor((HINSTANCE) NULL,IDC_SIZENS));
    return TRUE;
  }
  return CDisplayWnd::OnSetCursor(pWnd,nHitTest,message);
}

void CPODWnd::OnParentNotify(UINT message,LPARAM lParam)
{
  CRect  rBar;
  CPoint  ptBar;

  if (message == WM_LBUTTONDOWN)
  { for (rBar = RepositionViewSplitterBar(TRUE),ptBar.x = GET_X_LPARAM(lParam),ptBar.y = GET_Y_LPARAM(lParam); rBar.PtInRect(ptBar); )
    { for (ClientToScreen(rBar),ClientToScreen(&ptBar); m_wndSplitterBarCtrl[2].Create(GetParentFrame(),rBar,ptBar); )
      { m_wndSplitterBarCtrl[2].UpdateWindow();
        SetCapture();
        break;
      }
      break;
    }
    for (rBar = RepositionViewSplitterBar(FALSE); rBar.PtInRect(ptBar); )
    { for (ClientToScreen(rBar),ClientToScreen(&ptBar); m_wndSplitterBarCtrl[2].Create(GetParentFrame(),rBar,ptBar); )
      { m_wndSplitterBarCtrl[2].UpdateWindow();
        SetCapture();
        break;
      }
      break;
    }
  }
  CDisplayWnd::OnParentNotify(message,lParam);
}

void CPODWnd::OnLButtonUp(UINT nFlags,CPoint point)
{
  CRect  rBar[3];
  CRect  rViews[3];

  if (GetCapture() -> GetSafeHwnd() == GetSafeHwnd())
  { rBar[0] = RepositionViewSplitterBar(TRUE);
    rBar[1] = RepositionViewSplitterBar(FALSE);
    m_wndSplitterBarCtrl[2].GetWindowRect(rBar[2]);
    m_wndDataView.GetWindowRect(rViews[0]);
    m_wndParametersView.GetWindowRect(rViews[1]);
    m_wndFunctionsView.GetWindowRect(rViews[2]);
    rBar[2].OffsetRect(0,-m_wndSplitterBarCtrl[2].CalcTranslation());
    ScreenToClient(rBar[2]);
    ScreenToClient(rViews[0]);
    ScreenToClient(rViews[1]);
    ScreenToClient(rViews[2]);
    if (rBar[0].EqualRect(rBar[2]))
    { if (IsViewVisible(POD_VIEW_DATA) &&  IsViewVisible(POD_VIEW_PARAMETERS))
      { m_wndDataView.MoveWindow(rViews[0].left,rViews[0].top,rViews[0].Width(),rViews[0].Height()+m_wndSplitterBarCtrl[2].CalcTranslation());
        m_wndParametersView.MoveWindow(rViews[1].left,rViews[1].top+m_wndSplitterBarCtrl[2].CalcTranslation(),rViews[1].Width(),rViews[1].Height()-m_wndSplitterBarCtrl[2].CalcTranslation());
      }
      if (IsViewVisible(POD_VIEW_DATA) &&  !IsViewVisible(POD_VIEW_PARAMETERS) &&  IsViewVisible(POD_VIEW_FUNCTIONS))
      { m_wndDataView.MoveWindow(rViews[0].left,rViews[0].top,rViews[0].Width(),rViews[0].Height()+m_wndSplitterBarCtrl[2].CalcTranslation());
        m_wndFunctionsView.MoveWindow(rViews[2].left,rViews[2].top+m_wndSplitterBarCtrl[2].CalcTranslation(),rViews[2].Width(),rViews[2].Height()-m_wndSplitterBarCtrl[2].CalcTranslation());
      }
      if (!IsViewVisible(POD_VIEW_DATA) &&  IsViewVisible(POD_VIEW_PARAMETERS) &&  IsViewVisible(POD_VIEW_FUNCTIONS))
      { m_wndParametersView.MoveWindow(rViews[1].left,rViews[1].top,rViews[1].Width(),rViews[1].Height()+m_wndSplitterBarCtrl[2].CalcTranslation());
        m_wndFunctionsView.MoveWindow(rViews[2].left,rViews[2].top+m_wndSplitterBarCtrl[2].CalcTranslation(),rViews[2].Width(),rViews[2].Height()-m_wndSplitterBarCtrl[2].CalcTranslation());
      }
      m_wndSplitterBarCtrl[0].MoveWindow(RepositionViewSplitterBar(TRUE));
    }
    if (rBar[1].EqualRect(rBar[2]))
    { m_wndParametersView.MoveWindow(rViews[1].left,rViews[1].top,rViews[1].Width(),rViews[1].Height()+m_wndSplitterBarCtrl[2].CalcTranslation());
      m_wndFunctionsView.MoveWindow(rViews[2].left,rViews[2].top+m_wndSplitterBarCtrl[2].CalcTranslation(),rViews[2].Width(),rViews[2].Height()-m_wndSplitterBarCtrl[2].CalcTranslation());
      m_wndSplitterBarCtrl[1].MoveWindow(RepositionViewSplitterBar(FALSE));
    }
    m_wndSplitterBarCtrl[2].DestroyWindow();
    ReleaseCapture();
  }
  CDisplayWnd::OnLButtonUp(nFlags,point);
}

void CPODWnd::OnMouseMove(UINT nFlags,CPoint point)
{
  POINT  pt;
  CRect  rBar[3];
  CRect  rViews[3][2];

  if (nFlags & MK_LBUTTON)
  { if (GetCapture() -> GetSafeHwnd() == GetSafeHwnd())
    { for (rBar[0] = RepositionViewSplitterBar(TRUE),rBar[1] = RepositionViewSplitterBar(FALSE),m_wndSplitterBarCtrl[2].GetWindowRect(rBar[2]),m_wndDataView.GetWindowRect(rViews[0][0]),m_wndParametersView.GetWindowRect(rViews[1][0]),m_wndFunctionsView.GetWindowRect(rViews[2][0]),rViews[0][1].SetRect(0,0,m_wndDataView.GetTrackSize().cx,m_wndDataView.GetTrackSize().cy),rViews[1][1].SetRect(0,0,m_wndParametersView.GetTrackSize().cx,m_wndParametersView.GetTrackSize().cy),rViews[2][1].SetRect(0,0,m_wndFunctionsView.GetTrackSize().cx,m_wndFunctionsView.GetTrackSize().cy),rBar[2].OffsetRect(0,-m_wndSplitterBarCtrl[2].CalcTranslation()),ScreenToClient(rBar[2]),pt.x = point.x,pt.y = point.y,ClientToScreen(&pt); rBar[0].EqualRect(rBar[2]); )
      { if (IsViewVisible(POD_VIEW_DATA) &&  IsViewVisible(POD_VIEW_PARAMETERS))
        { if (rViews[0][0].Height()+m_wndSplitterBarCtrl[2].CalcTranslation(pt) >= rViews[0][1].Height() &&  rViews[1][0].Height()-m_wndSplitterBarCtrl[2].CalcTranslation(pt) >= rViews[1][1].Height())
          { m_wndSplitterBarCtrl[2].Translate(pt);
            m_wndSplitterBarCtrl[2].UpdateWindow();
          }
          if (rViews[0][0].Height()+m_wndSplitterBarCtrl[2].CalcTranslation(pt) < rViews[0][1].Height())
          { pt.y += rViews[0][1].Height()-rViews[0][0].Height()-m_wndSplitterBarCtrl[2].CalcTranslation(pt);
            m_wndSplitterBarCtrl[2].Translate(pt);
            m_wndSplitterBarCtrl[2].UpdateWindow();
          }
          if (rViews[1][0].Height()-m_wndSplitterBarCtrl[2].CalcTranslation(pt) < rViews[1][1].Height())
          { pt.y -= rViews[1][1].Height()-rViews[1][0].Height()+m_wndSplitterBarCtrl[2].CalcTranslation(pt);
            m_wndSplitterBarCtrl[2].Translate(pt);
            m_wndSplitterBarCtrl[2].UpdateWindow();
          }
        }
        if (IsViewVisible(POD_VIEW_DATA) &&  !IsViewVisible(POD_VIEW_PARAMETERS) &&  IsViewVisible(POD_VIEW_FUNCTIONS))
        { if (rViews[0][0].Height()+m_wndSplitterBarCtrl[2].CalcTranslation(pt) >= rViews[0][1].Height() &&  rViews[2][0].Height()-m_wndSplitterBarCtrl[2].CalcTranslation(pt) >= rViews[2][1].Height())
          { m_wndSplitterBarCtrl[2].Translate(pt);
            m_wndSplitterBarCtrl[2].UpdateWindow();
          }
          if (rViews[0][0].Height()+m_wndSplitterBarCtrl[2].CalcTranslation(pt) < rViews[0][1].Height())
          { pt.y += rViews[0][1].Height()-rViews[0][0].Height()-m_wndSplitterBarCtrl[2].CalcTranslation(pt);
            m_wndSplitterBarCtrl[2].Translate(pt);
            m_wndSplitterBarCtrl[2].UpdateWindow();
          }
          if (rViews[2][0].Height()-m_wndSplitterBarCtrl[2].CalcTranslation(pt) < rViews[2][1].Height())
          { pt.y -= rViews[2][1].Height()-rViews[2][0].Height()+m_wndSplitterBarCtrl[2].CalcTranslation(pt);
            m_wndSplitterBarCtrl[2].Translate(pt);
            m_wndSplitterBarCtrl[2].UpdateWindow();
          }
        }
        if (!IsViewVisible(POD_VIEW_DATA) &&  IsViewVisible(POD_VIEW_PARAMETERS) &&  IsViewVisible(POD_VIEW_FUNCTIONS))
        { if (rViews[1][0].Height()+m_wndSplitterBarCtrl[2].CalcTranslation(pt) >= rViews[1][1].Height() &&  rViews[2][0].Height()-m_wndSplitterBarCtrl[2].CalcTranslation(pt) >= rViews[2][1].Height())
          { m_wndSplitterBarCtrl[2].Translate(pt);
            m_wndSplitterBarCtrl[2].UpdateWindow();
          }
          if (rViews[1][0].Height()+m_wndSplitterBarCtrl[2].CalcTranslation(pt) < rViews[1][1].Height())
          { pt.y += rViews[1][1].Height()-rViews[1][0].Height()-m_wndSplitterBarCtrl[2].CalcTranslation(pt);
            m_wndSplitterBarCtrl[2].Translate(pt);
            m_wndSplitterBarCtrl[2].UpdateWindow();
          }
          if (rViews[2][0].Height()-m_wndSplitterBarCtrl[2].CalcTranslation(pt) < rViews[2][1].Height())
          { pt.y -= rViews[2][1].Height()-rViews[2][0].Height()+m_wndSplitterBarCtrl[2].CalcTranslation(pt);
            m_wndSplitterBarCtrl[2].Translate(pt);
            m_wndSplitterBarCtrl[2].UpdateWindow();
          }
        }
        break;
      }
      if (rBar[1].EqualRect(rBar[2]))
      { if (rViews[1][0].Height()+m_wndSplitterBarCtrl[2].CalcTranslation(pt) >= rViews[1][1].Height() &&  rViews[2][0].Height()-m_wndSplitterBarCtrl[2].CalcTranslation(pt) >= rViews[2][1].Height())
        { m_wndSplitterBarCtrl[2].Translate(pt);
          m_wndSplitterBarCtrl[2].UpdateWindow();
        }
        if (rViews[1][0].Height()+m_wndSplitterBarCtrl[2].CalcTranslation(pt) < rViews[1][1].Height())
        { pt.y += rViews[1][1].Height()-rViews[1][0].Height()-m_wndSplitterBarCtrl[2].CalcTranslation(pt);
          m_wndSplitterBarCtrl[2].Translate(pt);
          m_wndSplitterBarCtrl[2].UpdateWindow();
        }
        if (rViews[2][0].Height()-m_wndSplitterBarCtrl[2].CalcTranslation(pt) < rViews[2][1].Height())
        { pt.y -= rViews[2][1].Height()-rViews[2][0].Height()+m_wndSplitterBarCtrl[2].CalcTranslation(pt);
          m_wndSplitterBarCtrl[2].Translate(pt);
          m_wndSplitterBarCtrl[2].UpdateWindow();
        }
      }
    }
  }
  CDisplayWnd::OnMouseMove(nFlags,point);
}

BOOL CPODWnd::OnCloseOpenDialog(UINT nCode)
{
  UINT  nMode;
  UINT  nLimit;
  UINT  nSpeed;
  UINT  nDigits;
  UINT  nStatus;
  BOOL  bToolTips;
  CString  szFileName;
  LOGFONT  fntTitle[3];
  LOGFONT  fntItems[3];
  CTimeKey  tStartTime;
  CTimeKey  tStopTime;
  CTimeKey  tRange[2][2];
  CTimeSpan  tDailyRange[2];
  CTimeSpan  tPeriodical;
  CTimeSpan  tInterval;
  CUIntArray  nColors;
  CPODLayout  cLayout[2];
  CPODPrintJobs  pJobs;

  if (nCode == IDOK)
  { for (SetMode(m_dlgOpen.GetMode()),SetType(MAKELONG(DISPLAY_TYPE_POD,m_dlgOpen.GetType())),SetWindowText(m_dlgOpen.GetTitle()); m_dlgOpen.IsLayoutModified(); )
    { m_dlgOpen.GetLayout(cLayout[0]);
      m_dlgOpen.GetLayoutToolTipMode(bToolTips);
      m_dlgOpen.GetLayoutTitleFonts(&fntTitle[0],&fntTitle[1],&fntTitle[2]);
      m_dlgOpen.GetLayoutItemsFonts(&fntItems[0],&fntItems[1],&fntItems[2]);
      if ((HIWORD(GetType()) == POD_TYPE_TEMPORARY  &&  !AddTemporaryPOD(cLayout[0].GetName(),cLayout[0])) ||  !SetLayout(cLayout[0]) ||  !SetTitleFonts(&fntTitle[0],&fntTitle[1],&fntTitle[2]) ||  !SetItemsFonts(&fntItems[0],&fntItems[1],&fntItems[2]) ||  !EnableToolTipMode(bToolTips)) return FALSE;
      break;
    }
    if (!m_dlgOpen.IsLayoutModified())
    { m_dlgOpen.GetLayout(cLayout[0]);
      if ((HIWORD(GetType()) == POD_TYPE_TEMPORARY  &&  !AddTemporaryPOD(cLayout[0].GetName(),cLayout[0])) ||  !SetLayout(cLayout[0])) return FALSE;
    }
    if (m_dlgOpen.IsFilteringModified())
    { m_dlgOpen.GetFilterMode(nMode);
      m_dlgOpen.GetFilterLimit(nLimit);
      m_dlgOpen.GetFilterDigits(nDigits);
      m_dlgOpen.GetFilterStatus(nStatus);
      m_dlgOpen.GetFilterColors(nColors);
      m_dlgOpen.GetFilterRange(tRange[0][0],tRange[0][1]);
      m_dlgOpen.GetFilterDailyRange(tDailyRange[0],tDailyRange[1]);
      m_dlgOpen.GetFilterPeriodicalRange(tRange[1][0],tPeriodical,tRange[1][1]);
      if (!SetFilterMode(nMode) ||  SetFilterLimit(nLimit) < 0  ||  SetFilterStatus(nStatus) < 0  ||  SetFilterRange(tRange[0][0],tRange[0][1]) < 0  ||  SetFilterDailyRange(tDailyRange[0],tDailyRange[1]) < 0  ||  SetFilterPeriodicalRange(tRange[1][0],tPeriodical,tRange[1][1]) < 0  ||  !SetFilterDigits(nDigits) ||  !SetFilterColors(nColors)) return FALSE;
    }
    if (m_dlgOpen.IsRetrievingModified())
    { m_dlgOpen.GetRetrieveFileName(szFileName);
      if (!SetRetrieveFileName(szFileName)) return FALSE;
    }
    if (m_dlgOpen.IsPrintingModified())
    { m_dlgOpen.GetPrintJobs(pJobs);
      if (!SetPrintJobs(pJobs)) return FALSE;
    }
    if (GetMode() == DISPLAY_MODE_REALTIME)
    { UpdateAllPanes();
      return Start();
    }
    if (GetMode() == DISPLAY_MODE_HISTORY)
    { m_dlgOpen.GetRetrieveMode(nMode);
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

BOOL CPODWnd::OnCloseSettingsDialog(UINT nCode)
{
  UINT  nMode;
  UINT  nLimit;
  UINT  nDigits;
  UINT  nStatus;
  BOOL  bToolTips;
  CString  szFileName;
  CString  szLayoutName;
  LOGFONT  fntTitle[3];
  LOGFONT  fntItems[3];
  CTimeKey  tRange[2][2];
  CTimeSpan  tDailyRange[2];
  CTimeSpan  tPeriodical;
  CStringArray  szColumns;
  CUIntArray  nWidths[3];
  CUIntArray  nColors;
  CPODLayout  cLayout;
  CPODPrintJobs  pJobs;

  if (nCode == IDOK)
  { for (GetLayout(szLayoutName,nWidths[0],nWidths[1],nWidths[2]); m_dlgSettings.IsLayoutModified(); )
    { m_dlgSettings.GetLayout(cLayout);
      m_dlgSettings.GetLayoutToolTipMode(bToolTips);
      m_dlgSettings.GetLayoutTitleFonts(&fntTitle[0],&fntTitle[1],&fntTitle[2]);
      m_dlgSettings.GetLayoutItemsFonts(&fntItems[0],&fntItems[1],&fntItems[2]);
      if ((HIWORD(GetType()) == POD_TYPE_TEMPORARY  &&  !AddTemporaryPOD(cLayout.GetName(),cLayout)) ||  !SetLayout(cLayout,nWidths[0],nWidths[1],nWidths[2]) ||  !SetTitleFonts(&fntTitle[0],&fntTitle[1],&fntTitle[2]) ||  !SetItemsFonts(&fntItems[0],&fntItems[1],&fntItems[2]) ||  !EnableToolTipMode(bToolTips)) return FALSE;
      break;
    }
    if (m_dlgSettings.IsFilteringModified())
    { m_dlgSettings.GetFilterMode(nMode);
      m_dlgSettings.GetFilterLimit(nLimit);
      m_dlgSettings.GetFilterDigits(nDigits);
      m_dlgSettings.GetFilterStatus(nStatus);
      m_dlgSettings.GetFilterColors(nColors);
      m_dlgSettings.GetFilterRange(tRange[0][0],tRange[0][1]);
      m_dlgSettings.GetFilterDailyRange(tDailyRange[0],tDailyRange[1]);
      m_dlgSettings.GetFilterPeriodicalRange(tRange[1][0],tPeriodical,tRange[1][1]);
      if (!SetFilterMode(nMode) ||  SetFilterLimit(nLimit) < 0  ||  SetFilterStatus(nStatus) < 0  ||  SetFilterRange(tRange[0][0],tRange[0][1]) < 0  ||  SetFilterDailyRange(tDailyRange[0],tDailyRange[1]) < 0  ||  SetFilterPeriodicalRange(tRange[1][0],tPeriodical,tRange[1][1]) < 0  ||  !SetFilterDigits(nDigits) ||  !SetFilterColors(nColors)) return FALSE;
    }
    if (m_dlgSettings.IsRetrievingModified())
    { m_dlgSettings.GetRetrieveFileName(szFileName);
      if (!SetRetrieveFileName(szFileName)) return FALSE;
    }
    if (m_dlgSettings.IsPrintingModified())
    { m_dlgSettings.GetPrintJobs(pJobs);
      if (!SetPrintJobs(pJobs)) return FALSE;
    }
    UpdateData();
    UpdateAllPanes();
  }
  return TRUE;
}

BOOL CPODWnd::OnCloseRetrieveDialog(UINT nCode)
{
  UINT  nMode[2];
  UINT  nSpeed[2];
  CTimeSpan  tInterval[2];
  CTimeKey  tStartTime[2];
  CTimeKey  tStopTime[2];

  if (nCode == IDOK)
  { nMode[0] = GetRetrieveMode();
    nSpeed[0] = GetRetrieveSpeed();
    tInterval[0] = GetRetrieveInterval();
    tStartTime[0] = GetRetrieveStartTime();
    tStopTime[0] = GetRetrieveStopTime();
    for (m_dlgRetrievals.GetMode(nMode[1]); nMode[1]; )
    { m_dlgRetrievals.GetSpeed(nSpeed[1]);
      m_dlgRetrievals.GetInterval(tInterval[1]);
      m_dlgRetrievals.GetStartTime(tStartTime[1]);
      m_dlgRetrievals.GetStopTime(tStopTime[1]);
      if (SetMode(DISPLAY_MODE_HISTORY) && (!IsRetrievingData() ||  StopRetrieveData()) &&  StartRetrieveData(nMode[1],nSpeed[1],tInterval[1],tStartTime[1],tStopTime[1]))
      { UpdateAllPanes();
        return TRUE;
      }
      SetMode((!nMode[0]) ? DISPLAY_MODE_REALTIME:DISPLAY_MODE_HISTORY);
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

void CPODWnd::OnSettings()
{
  CHourglassCursor  cCursor;

  ReportEvent((m_dlgSettings.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE:SYSTEM_NOERROR);
}

void CPODWnd::OnLinkages()
{
  CHourglassCursor  cCursor;

  ReportEvent((m_dlgLinkages.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE:SYSTEM_NOERROR);
}

void CPODWnd::OnHold()
{
  SetHoldFlag(!GetHoldFlag());
}

void CPODWnd::OnClearAll()
{
  CHourglassCursor  cCursor;

  Reset();
}

void CPODWnd::OnRetrievals()
{
  CHourglassCursor  cCursor;

  ReportEvent((m_dlgRetrievals.Create(this) <= 0) ? SYSTEM_WARNING_DIALOG_OPEN_FAILURE:SYSTEM_NOERROR);
}

void CPODWnd::OnRetrieveStop()
{
  RetrieveMoreData(POD_RETRIEVE_STOPPED);
}

void CPODWnd::OnRetrieveAutoForward()
{
  RetrieveMoreData(POD_RETRIEVE_AUTOFORWARD);
}

void CPODWnd::OnRetrieveAutoBackward()
{
  RetrieveMoreData(POD_RETRIEVE_AUTOBACKWARD);
}

void CPODWnd::OnRetrieveManualForward()
{
  RetrieveMoreData(POD_RETRIEVE_MANUALFORWARD);
}

void CPODWnd::OnRetrieveManualBackward()
{
  RetrieveMoreData(POD_RETRIEVE_MANUALBACKWARD);
}

void CPODWnd::OnRetrievePseudoRealtime()
{
  RetrieveMoreData(POD_RETRIEVE_PSEUDOREALTIME);
}

void CPODWnd::OnPrint()
{
  CHourglassCursor  cCursor;

  ReportEvent((!Print()) ? SYSTEM_WARNING_DISPLAY_PRINT_FAILURE:SYSTEM_NOERROR);
}

void CPODWnd::OnDestroy() 
{
  CHourglassCursor  cCursor;

  Stop();
  CDisplayWnd::OnDestroy();
}

void CPODWnd::OnUpdateSettings(CCmdUI *pCmdUI)
{
  pCmdUI -> Enable(IsInitialized() && (HIWORD(GetType()) != POD_TYPE_TEMPORARY  ||  CheckAccountPrivilege(PRIVILEGE_POD_TEMPORARYUSE)));
  pCmdUI -> SetCheck(IsWindow(m_dlgSettings.GetSafeHwnd()));
}

void CPODWnd::OnUpdateLinkages(CCmdUI *pCmdUI)
{
  pCmdUI -> Enable(IsInitialized() &&  !GetLink());
  pCmdUI -> SetCheck(IsWindow(m_dlgLinkages.GetSafeHwnd()));
}

void CPODWnd::OnUpdateHold(CCmdUI *pCmdUI)
{
  pCmdUI -> Enable(IsInitialized() &&  HasHoldFlag());
  pCmdUI -> SetCheck(GetHoldFlag());
}

void CPODWnd::OnUpdateClearAll(CCmdUI *pCmdUI)
{
  pCmdUI -> Enable((IsInitialized() &&  GetSampleCount() > 0) ? TRUE:FALSE);
}

void CPODWnd::OnUpdateRetrievals(CCmdUI *pCmdUI)
{
  pCmdUI -> Enable((IsInitialized()) ? TRUE:FALSE);
  pCmdUI -> SetCheck(IsWindow(m_dlgRetrievals.GetSafeHwnd()));
}

void CPODWnd::OnUpdateRetrieveStop(CCmdUI *pCmdUI)
{
  pCmdUI -> Enable((IsRetrievingData() && ((GetRetrieveMode() & POD_RETRIEVE_AUTOFORWARD) || (GetRetrieveMode() & POD_RETRIEVE_AUTOBACKWARD) || (GetRetrieveMode() & POD_RETRIEVE_PSEUDOREALTIME) ||  HIWORD(IsRetrievingData())) &&  !(GetRetrieveMode() & POD_RETRIEVE_STOPPED)) ? TRUE:FALSE);
}

void CPODWnd::OnUpdateRetrieveAutoForward(CCmdUI *pCmdUI)
{
  pCmdUI -> Enable((IsRetrievingData() &&  !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & POD_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & POD_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & POD_RETRIEVE_STOPPED))) ? TRUE:FALSE);
}

void CPODWnd::OnUpdateRetrieveAutoBackward(CCmdUI *pCmdUI)
{
  pCmdUI -> Enable((IsRetrievingData() &&  !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & POD_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & POD_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & POD_RETRIEVE_STOPPED))) ? TRUE:FALSE);
}

void CPODWnd::OnUpdateRetrieveManualForward(CCmdUI *pCmdUI)
{
  pCmdUI -> Enable((IsRetrievingData() &&  !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & POD_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & POD_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & POD_RETRIEVE_STOPPED))) ? TRUE:FALSE);
}

void CPODWnd::OnUpdateRetrieveManualBackward(CCmdUI *pCmdUI)
{
  pCmdUI -> Enable((IsRetrievingData() &&  !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & POD_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & POD_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & POD_RETRIEVE_STOPPED))) ? TRUE:FALSE);
}

void CPODWnd::OnUpdateRetrievePseudoRealtime(CCmdUI *pCmdUI)
{
  pCmdUI -> Enable((IsRetrievingData() &&  !HIWORD(IsRetrievingData()) && ((GetRetrieveMode() & POD_RETRIEVE_MANUALFORWARD) || (GetRetrieveMode() & POD_RETRIEVE_MANUALBACKWARD) || (GetRetrieveMode() & POD_RETRIEVE_STOPPED))) ? TRUE:FALSE);
}

void CPODWnd::OnUpdatePrint(CCmdUI *pCmdUI)
{
  pCmdUI -> Enable((IsInitialized() &&  IsDefaultPrinterAvailable() &&  CanPrint()) ? TRUE:FALSE);
}

void CPODWnd::OnUpdateStatusBarMessagePane(CCmdUI *pCmdUI)
{
  pCmdUI -> Enable();
}

void CPODWnd::OnUpdateStatusBarModePane(CCmdUI *pCmdUI)
{
  pCmdUI -> Enable();
}

void CPODWnd::OnUpdateStatusBarTypePane(CCmdUI *pCmdUI)
{
  pCmdUI -> Enable();
}
