// ARCHIVE.CPP : Archiving Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the archiving related
// interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1998/06/29 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CArchivesExtractionProfileInfo

CArchivesExtractionProfileInfo::CArchivesExtractionProfileInfo() : CObject()
{
	SetName(STRING(IDS_PROFILE_DEFAULTEXTRACTIONNAME));
	SetRowDelimiter(CString(CString(CR) + CString(EOL)));
	SetColumnDelimiter(STRING(IDS_PROFILE_EXTRACTIONS_DELIMITER_COL_COMMA));
	SetTextDelimiter(STRING(IDS_PROFILE_EXTRACTIONS_DELIMITER_TEXT_DOUBLEQUOTE));
	SetTimeFormat(ARCHIVESEXTRACTIONINFO_TIMEFORMAT_MILLISECONDS);
	SetCharset(ARCHIVESEXTRACTIONINFO_CHARSET_ASCII);
	SetAutomationScriptOptions(0);
	SetTitleOption(TRUE);
	SetTimeRangeMode(0);
	SetExecutionMode(0);
	SetExecutionStatus(0);
	SetExecutionCycle(0);
	SetRangeInterval(0);
	SetLastExecutionTime(0);
	SetFTPAudition(ARCHIVESEXTRACTIONINFO_AUDITION_NONE);
	SetFTPRetryInfo(0, 0);
	SetFTPRetryCount(0);
	SetFTPRetryTime(0);
	SetFTPOption(FALSE);
	SetFTPPort(0);
}

CArchivesExtractionProfileInfo::~CArchivesExtractionProfileInfo()
{
	return;
}

VOID CArchivesExtractionProfileInfo::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CArchivesExtractionProfileInfo::GetName() CONST
{
	return m_szName;
}

VOID CArchivesExtractionProfileInfo::SetSource(LPCTSTR pszFileName)
{
	m_szSource = pszFileName;
}

CString CArchivesExtractionProfileInfo::GetSource() CONST
{
	return m_szSource;
}

VOID CArchivesExtractionProfileInfo::SetFileName(LPCTSTR pszFileName)
{
	m_szFileName = pszFileName;
}

CString CArchivesExtractionProfileInfo::GetFileName() CONST
{
	return m_szFileName;
}

VOID CArchivesExtractionProfileInfo::SetDirectory(LPCTSTR pszDirectory)
{
	m_szDirectory = pszDirectory;
}

CString CArchivesExtractionProfileInfo::GetDirectory() CONST
{
	return m_szDirectory;
}

VOID CArchivesExtractionProfileInfo::SetCharset(UINT nCharset)
{
	if (nCharset == ARCHIVESEXTRACTIONINFO_CHARSET_ASCII || nCharset == ARCHIVESEXTRACTIONINFO_CHARSET_UNICODE)
	{
		m_nCharset = nCharset;
		return;
	}
}

UINT CArchivesExtractionProfileInfo::GetCharset() CONST
{
	return m_nCharset;
}

VOID CArchivesExtractionProfileInfo::SetTimeFormat(UINT nFormat)
{
	m_nTimeFormat = (nFormat == ARCHIVESEXTRACTIONINFO_TIMEFORMAT_NONE || nFormat == ARCHIVESEXTRACTIONINFO_TIMEFORMAT_DEFAULT || nFormat == ARCHIVESEXTRACTIONINFO_TIMEFORMAT_SHORTDEFAULT || nFormat == ARCHIVESEXTRACTIONINFO_TIMEFORMAT_DATETIME || nFormat == ARCHIVESEXTRACTIONINFO_TIMEFORMAT_SHORTDATETIME || nFormat == ARCHIVESEXTRACTIONINFO_TIMEFORMAT_TIME || nFormat == ARCHIVESEXTRACTIONINFO_TIMEFORMAT_SHORTTIME || nFormat == ARCHIVESEXTRACTIONINFO_TIMEFORMAT_MILLISECONDS || nFormat == ARCHIVESEXTRACTIONINFO_TIMEFORMAT_SECONDS) ? nFormat : m_nTimeFormat;
}

UINT CArchivesExtractionProfileInfo::GetTimeFormat() CONST
{
	return m_nTimeFormat;
}

VOID CArchivesExtractionProfileInfo::SetTitleOption(BOOL bEnable)
{
	m_bTitleOption = bEnable;
}

BOOL CArchivesExtractionProfileInfo::GetTitleOption() CONST
{
	return m_bTitleOption;
}

VOID CArchivesExtractionProfileInfo::SetColumnDelimiter(LPCTSTR pszDelimiter)
{
	m_szDelimiters[0] = pszDelimiter;
}

CString CArchivesExtractionProfileInfo::GetColumnDelimiter() CONST
{
	return m_szDelimiters[0];
}

VOID CArchivesExtractionProfileInfo::SetRowDelimiter(LPCTSTR pszDelimiter)
{
	m_szDelimiters[1] = pszDelimiter;
}

CString CArchivesExtractionProfileInfo::GetRowDelimiter() CONST
{
	return m_szDelimiters[1];
}

VOID CArchivesExtractionProfileInfo::SetTextDelimiter(LPCTSTR pszDelimiter)
{
	m_szDelimiters[2] = pszDelimiter;
}

CString CArchivesExtractionProfileInfo::GetTextDelimiter() CONST
{
	return m_szDelimiters[2];
}

VOID CArchivesExtractionProfileInfo::SetParameters(CONST CStringArray &szParameters, CONST CUIntArray &nFormats, CONST CUIntArray &nTriggers)
{
	if (szParameters.GetSize() == nFormats.GetSize() && szParameters.GetSize() == nTriggers.GetSize())
	{
		m_szParameters.Copy(szParameters);
		m_nParameterFormats.Copy(nFormats);
		m_nParameterTriggers.Copy(nTriggers);
	}
}

INT CArchivesExtractionProfileInfo::GetParameters(CStringArray &szParameters, CUIntArray &nFormats, CUIntArray &nTriggers) CONST
{
	szParameters.Copy(m_szParameters);
	nFormats.Copy(m_nParameterFormats);
	nTriggers.Copy(m_nParameterTriggers);
	return((szParameters.GetSize() == nFormats.GetSize() && szParameters.GetSize() == nTriggers.GetSize()) ? (INT)szParameters.GetSize() : -1);
}

VOID CArchivesExtractionProfileInfo::SetTimeRangeMode(UINT nMode)
{
	if (nMode == ARCHIVESEXTRACTIONINFO_RANGE_NORMAL || nMode == ARCHIVESEXTRACTIONINFO_RANGE_DAILY || nMode == ARCHIVESEXTRACTIONINFO_RANGE_COMPLETEINTERVAL || nMode == ARCHIVESEXTRACTIONINFO_RANGE_PARTIALINTERVAL || nMode == ARCHIVESEXTRACTIONINFO_RANGE_TRIGGEREDINTERVAL || !nMode)
	{
		if ((m_nModes[0] = nMode) == 0)
		{
			m_tRange[0] = 0;
			m_tRange[1] = 0;
			m_tDailyRange[0] = 0;
			m_tDailyRange[1] = 0;
			m_tIntervalRange[0] = 0;
			m_tIntervalRange[1] = 0;
		}
	}
}

UINT CArchivesExtractionProfileInfo::GetTimeRangeMode() CONST
{
	return m_nModes[0];
}

VOID CArchivesExtractionProfileInfo::SetTimeRange(CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime)
{
	if (m_nModes[0] == ARCHIVESEXTRACTIONINFO_RANGE_NORMAL)
	{
		if (tStartTime < tStopTime)
		{
			m_tRange[0] = tStartTime;
			m_tRange[1] = tStopTime;
		}
	}
}

BOOL CArchivesExtractionProfileInfo::GetTimeRange(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	if (m_nModes[0] == ARCHIVESEXTRACTIONINFO_RANGE_NORMAL)
	{
		tStartTime = m_tRange[0];
		tStopTime = m_tRange[1];
		return TRUE;
	}
	return FALSE;
}

VOID CArchivesExtractionProfileInfo::SetDailyTimeRange(CONST CTimeSpan &tStartTime, CONST CTimeSpan &tStopTime)
{
	if (m_nModes[0] == ARCHIVESEXTRACTIONINFO_RANGE_DAILY)
	{
		m_tDailyRange[0] = tStartTime;
		m_tDailyRange[1] = tStopTime;
	}
}

BOOL CArchivesExtractionProfileInfo::GetDailyTimeRange(CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST
{
	if (m_nModes[0] == ARCHIVESEXTRACTIONINFO_RANGE_DAILY)
	{
		tStartTime = m_tDailyRange[0];
		tStopTime = m_tDailyRange[1];
		return TRUE;
	}
	return FALSE;
}

VOID CArchivesExtractionProfileInfo::SetPeriodicalInterval(CONST CTimeSpan &tInterval)
{
	if (m_nModes[0] == ARCHIVESEXTRACTIONINFO_RANGE_PARTIALINTERVAL)
	{
		m_tIntervalRange[0] = tInterval;
		return;
	}
}

CTimeSpan CArchivesExtractionProfileInfo::GetPeriodicalInterval() CONST
{
	return((m_nModes[0] == ARCHIVESEXTRACTIONINFO_RANGE_PARTIALINTERVAL) ? m_tIntervalRange[0] : CTimeSpan(0));
}

VOID CArchivesExtractionProfileInfo::SetTriggeredInterval(CONST CTimeSpan &tInterval, BOOL bBefore)
{
	if (m_nModes[0] == ARCHIVESEXTRACTIONINFO_RANGE_TRIGGEREDINTERVAL)
	{
		m_tIntervalRange[0] = (!bBefore) ? tInterval : m_tIntervalRange[0];
		m_tIntervalRange[1] = (bBefore) ? tInterval : m_tIntervalRange[1];
	}
}

CTimeSpan CArchivesExtractionProfileInfo::GetTriggeredInterval(BOOL bBefore) CONST
{
	return((m_nModes[0] == ARCHIVESEXTRACTIONINFO_RANGE_TRIGGEREDINTERVAL) ? ((!bBefore) ? m_tIntervalRange[0] : m_tIntervalRange[1]) : 0);
}

VOID CArchivesExtractionProfileInfo::SetRangeInterval(CONST CTimeSpan &tInterval)
{
	m_tIntervalRange[2] = tInterval;
}

CTimeSpan CArchivesExtractionProfileInfo::GetRangeInterval() CONST
{
	return m_tIntervalRange[2];
}

VOID CArchivesExtractionProfileInfo::SetExecutionMode(UINT nMode)
{
	if (nMode == ARCHIVESEXTRACTIONINFO_EXECUTION_IMMEDIATELY || nMode == ARCHIVESEXTRACTIONINFO_EXECUTION_ATTIME || nMode == ARCHIVESEXTRACTIONINFO_EXECUTION_ATDAILYTIME || nMode == ARCHIVESEXTRACTIONINFO_EXECUTION_ATINTERVAL || nMode == ARCHIVESEXTRACTIONINFO_EXECUTION_ATEVENT || nMode == ARCHIVESEXTRACTIONINFO_EXECUTION_BYSCRIPT || !nMode)
	{
		if ((m_nModes[1] = nMode) == 0)
		{
			m_tExecution[0] = 0;
			m_tExecution[1] = 0;
			m_tExecution[2] = 0;
			m_tDailyExecution = 0;
			m_tIntervalExecution = 0;
		}
	}
}

UINT CArchivesExtractionProfileInfo::GetExecutionMode() CONST
{
	return m_nModes[1];
}

VOID CArchivesExtractionProfileInfo::SetExecutionStatus(UINT nStatus)
{
	m_nStatus = nStatus;
}

UINT CArchivesExtractionProfileInfo::GetExecutionStatus() CONST
{
	return m_nStatus;
}

VOID CArchivesExtractionProfileInfo::SetExecutionCycle(UINT nCycle)
{
	m_nCycleCount = nCycle;
}

UINT CArchivesExtractionProfileInfo::GetExecutionCycle() CONST
{
	return m_nCycleCount;
}

VOID CArchivesExtractionProfileInfo::SetExecutionTime(CONST CTimeKey &tTime)
{
	if (m_nModes[1] == ARCHIVESEXTRACTIONINFO_EXECUTION_ATTIME || m_nModes[1] == ARCHIVESEXTRACTIONINFO_EXECUTION_BYSCRIPT)
	{
		m_tExecution[0] = tTime;
		return;
	}
}

CTimeKey CArchivesExtractionProfileInfo::GetExecutionTime() CONST
{
	return((m_nModes[1] == ARCHIVESEXTRACTIONINFO_EXECUTION_ATTIME || m_nModes[1] == ARCHIVESEXTRACTIONINFO_EXECUTION_BYSCRIPT) ? m_tExecution[0] : CTimeKey(0));
}

VOID CArchivesExtractionProfileInfo::SetDailyExecutionTime(CONST CTimeSpan &tTime)
{
	if (m_nModes[1] == ARCHIVESEXTRACTIONINFO_EXECUTION_ATDAILYTIME)
	{
		m_tDailyExecution = tTime;
		return;
	}
}

CTimeSpan CArchivesExtractionProfileInfo::GetDailyExecutionTime() CONST
{
	return((m_nModes[1] == ARCHIVESEXTRACTIONINFO_EXECUTION_ATDAILYTIME) ? m_tDailyExecution : CTimeSpan(0));
}

VOID CArchivesExtractionProfileInfo::SetPeriodicalExecutionTime(CONST CTimeKey &tStartTime, CONST CTimeSpan &tInterval, CONST CTimeKey &tStopTime)
{
	if (m_nModes[1] == ARCHIVESEXTRACTIONINFO_EXECUTION_ATINTERVAL)
	{
		m_tExecution[1] = tStartTime;
		m_tExecution[2] = tStopTime;
		m_tIntervalExecution = tInterval;
	}
}

BOOL CArchivesExtractionProfileInfo::GetPeriodicalExecutionTime(CTimeKey &tStartTime, CTimeSpan &tInterval, CTimeKey &tStopTime) CONST
{
	if (m_nModes[1] == ARCHIVESEXTRACTIONINFO_EXECUTION_ATINTERVAL)
	{
		tStartTime = m_tExecution[1];
		tStopTime = m_tExecution[2];
		tInterval = m_tIntervalExecution;
		return TRUE;
	}
	return FALSE;
}

VOID CArchivesExtractionProfileInfo::SetTriggeredExecution(LPCTSTR pszEvent)
{
	if (m_nModes[1] == ARCHIVESEXTRACTIONINFO_EXECUTION_ATEVENT)
	{
		m_szExecutionEvent = pszEvent;
		return;
	}
}

CString CArchivesExtractionProfileInfo::GetTriggeredExecution() CONST
{
	return((m_nModes[1] == ARCHIVESEXTRACTIONINFO_EXECUTION_ATEVENT) ? (LPCTSTR)m_szExecutionEvent : EMPTYSTRING);
}

VOID CArchivesExtractionProfileInfo::SetLastExecutionTime(CONST CTimeKey &tTime)
{
	m_tLastExecution = tTime;
}

CTimeKey CArchivesExtractionProfileInfo::GetLastExecutionTime() CONST
{
	return m_tLastExecution;
}

VOID CArchivesExtractionProfileInfo::SetFTPOption(BOOL bEnabled)
{
	m_bFTPOption = bEnabled;
}

BOOL CArchivesExtractionProfileInfo::GetFTPOption() CONST
{
	return m_bFTPOption;
}

VOID CArchivesExtractionProfileInfo::SetFTPLocation(LPCTSTR pszLocation)
{
	m_szFTPLocation = pszLocation;
}

CString CArchivesExtractionProfileInfo::GetFTPLocation() CONST
{
	return m_szFTPLocation;
}

VOID CArchivesExtractionProfileInfo::SetFTPUserName(LPCTSTR pszName)
{
	m_szFTPUserName = pszName;
}

CString CArchivesExtractionProfileInfo::GetFTPUserName() CONST
{
	return m_szFTPUserName;
}

VOID CArchivesExtractionProfileInfo::SetFTPPassword(LPCTSTR pszPassword)
{
	m_szFTPPassword = pszPassword;
}

CString CArchivesExtractionProfileInfo::GetFTPPassword() CONST
{
	return m_szFTPPassword;
}

VOID CArchivesExtractionProfileInfo::SetFTPPort(UINT nPort)
{
	m_nFTPPort = nPort;
}

UINT CArchivesExtractionProfileInfo::GetFTPPort() CONST
{
	return m_nFTPPort;
}

VOID CArchivesExtractionProfileInfo::SetFTPRetryInfo(UINT nRetries, CONST CTimeSpan &tInterval)
{
	m_nFTPRetryCount[0] = nRetries;
	m_tFTPRetryInterval = tInterval;
}

BOOL CArchivesExtractionProfileInfo::GetFTPRetryInfo(UINT &nRetries, CTimeSpan &tInterval) CONST
{
	nRetries = m_nFTPRetryCount[0];
	tInterval = m_tFTPRetryInterval;
	return((nRetries >= 0) ? TRUE : FALSE);
}

VOID CArchivesExtractionProfileInfo::SetFTPRetryTime(CONST CTimeKey &tTime)
{
	m_tFTPRetry = tTime;
}

CTimeKey CArchivesExtractionProfileInfo::GetFTPRetryTime() CONST
{
	return m_tFTPRetry;
}

VOID CArchivesExtractionProfileInfo::SetFTPRetryCount(UINT nCount)
{
	m_nFTPRetryCount[1] = nCount;
}

UINT CArchivesExtractionProfileInfo::GetFTPRetryCount() CONST
{
	return m_nFTPRetryCount[1];
}

VOID CArchivesExtractionProfileInfo::SetFTPAudition(UINT nAudition)
{
	m_nFTPAudition = (nAudition == ARCHIVESEXTRACTIONINFO_AUDITION_NONE || nAudition == ARCHIVESEXTRACTIONINFO_AUDITION_ALL || nAudition == ARCHIVESEXTRACTIONINFO_AUDITION_FAILURES) ? nAudition : m_nFTPAudition;
}

UINT CArchivesExtractionProfileInfo::GetFTPAudition() CONST
{
	return m_nFTPAudition;
}

VOID CArchivesExtractionProfileInfo::SetAutomationScriptName(LPCTSTR pszScript)
{
	m_szAutomationScript = pszScript;
}

CString CArchivesExtractionProfileInfo::GetAutomationScriptName() CONST
{
	return m_szAutomationScript;
}

VOID CArchivesExtractionProfileInfo::SetAutomationScriptOutput(LPCTSTR pszOutput)
{
	m_szAutomationOutput = pszOutput;
}

CString CArchivesExtractionProfileInfo::GetAutomationScriptOutput() CONST
{
	return m_szAutomationOutput;
}

VOID CArchivesExtractionProfileInfo::SetAutomationScriptOptions(UINT nOptions)
{
	m_nAutomationOptions = nOptions;
}

UINT CArchivesExtractionProfileInfo::GetAutomationScriptOptions() CONST
{
	return m_nAutomationOptions;
}

VOID CArchivesExtractionProfileInfo::Copy(CONST CArchivesExtractionProfileInfo *pProfileInfo)
{
	m_szName = pProfileInfo->m_szName;
	m_szSource = pProfileInfo->m_szSource;
	m_szFileName = pProfileInfo->m_szFileName;
	m_szDirectory = pProfileInfo->m_szDirectory;
	m_nModes[0] = pProfileInfo->m_nModes[0];
	m_nModes[1] = pProfileInfo->m_nModes[1];
	m_nStatus = pProfileInfo->m_nStatus;
	m_nCharset = pProfileInfo->m_nCharset;
	m_nTimeFormat = pProfileInfo->m_nTimeFormat;
	m_nCycleCount = pProfileInfo->m_nCycleCount;
	m_bTitleOption = pProfileInfo->m_bTitleOption;
	m_szDelimiters[0] = pProfileInfo->m_szDelimiters[0];
	m_szDelimiters[1] = pProfileInfo->m_szDelimiters[1];
	m_szDelimiters[2] = pProfileInfo->m_szDelimiters[2];
	m_tRange[0] = pProfileInfo->m_tRange[0];
	m_tRange[1] = pProfileInfo->m_tRange[1];
	m_tDailyRange[0] = pProfileInfo->m_tDailyRange[0];
	m_tDailyRange[1] = pProfileInfo->m_tDailyRange[1];
	m_tIntervalRange[0] = pProfileInfo->m_tIntervalRange[0];
	m_tIntervalRange[1] = pProfileInfo->m_tIntervalRange[1];
	m_tIntervalRange[2] = pProfileInfo->m_tIntervalRange[2];
	m_tExecution[0] = pProfileInfo->m_tExecution[0];
	m_tExecution[1] = pProfileInfo->m_tExecution[1];
	m_tExecution[2] = pProfileInfo->m_tExecution[2];
	m_tLastExecution = pProfileInfo->m_tLastExecution;
	m_tDailyExecution = pProfileInfo->m_tDailyExecution;
	m_tIntervalExecution = pProfileInfo->m_tIntervalExecution;
	m_szExecutionEvent = pProfileInfo->m_szExecutionEvent;
	m_szAutomationScript = pProfileInfo->m_szAutomationScript;
	m_szAutomationOutput = pProfileInfo->m_szAutomationOutput;
	m_nAutomationOptions = pProfileInfo->m_nAutomationOptions;
	m_szParameters.Copy(pProfileInfo->m_szParameters);
	m_nParameterFormats.Copy(pProfileInfo->m_nParameterFormats);
	m_nParameterTriggers.Copy(pProfileInfo->m_nParameterTriggers);
	m_szFTPLocation = pProfileInfo->m_szFTPLocation;
	m_szFTPUserName = pProfileInfo->m_szFTPUserName;
	m_szFTPPassword = pProfileInfo->m_szFTPPassword;
	m_tFTPRetryInterval = pProfileInfo->m_tFTPRetryInterval;
	m_nFTPRetryCount[0] = pProfileInfo->m_nFTPRetryCount[0];
	m_nFTPRetryCount[1] = pProfileInfo->m_nFTPRetryCount[1];
	m_nFTPAudition = pProfileInfo->m_nFTPAudition;
	m_bFTPOption = pProfileInfo->m_bFTPOption;
	m_tFTPRetry = pProfileInfo->m_tFTPRetry;
	m_nFTPPort = pProfileInfo->m_nFTPPort;
}

BOOL CArchivesExtractionProfileInfo::Compare(CONST CArchivesExtractionProfileInfo *pProfileInfo) CONST
{
	INT  nParameter[2];
	INT  nParameters[2];

	if (pProfileInfo->m_szName == m_szName  &&  !pProfileInfo->m_szSource.CompareNoCase(m_szSource) && !pProfileInfo->m_szFileName.CompareNoCase(m_szFileName) && !pProfileInfo->m_szDirectory.CompareNoCase(m_szDirectory) && pProfileInfo->m_nCharset == m_nCharset  &&  pProfileInfo->m_nTimeFormat == m_nTimeFormat  &&  pProfileInfo->m_nModes[0] == m_nModes[0] && pProfileInfo->m_nModes[1] == m_nModes[1] && pProfileInfo->m_bTitleOption == m_bTitleOption  &&  pProfileInfo->m_szDelimiters[0] == m_szDelimiters[0] && pProfileInfo->m_szDelimiters[1] == m_szDelimiters[1] && pProfileInfo->m_szDelimiters[2] == m_szDelimiters[2] && (m_nModes[0] != ARCHIVESEXTRACTIONINFO_RANGE_NORMAL || (pProfileInfo->m_tRange[0] == m_tRange[0] && pProfileInfo->m_tRange[1] == m_tRange[1])) && (m_nModes[0] != ARCHIVESEXTRACTIONINFO_RANGE_DAILY || (pProfileInfo->m_tDailyRange[0] == m_tDailyRange[0] && pProfileInfo->m_tDailyRange[1] == m_tDailyRange[1])) && (m_nModes[0] != ARCHIVESEXTRACTIONINFO_RANGE_PARTIALINTERVAL || pProfileInfo->m_tIntervalRange[0] == m_tIntervalRange[0]) && (m_nModes[0] != ARCHIVESEXTRACTIONINFO_RANGE_TRIGGEREDINTERVAL || (pProfileInfo->m_tIntervalRange[0] == m_tIntervalRange[0] && pProfileInfo->m_tIntervalRange[1] == m_tIntervalRange[1])) && pProfileInfo->m_tIntervalRange[2] == m_tIntervalRange[2] && ((m_nModes[1] != ARCHIVESEXTRACTIONINFO_EXECUTION_IMMEDIATELY  &&  m_nModes[1] != ARCHIVESEXTRACTIONINFO_EXECUTION_ATTIME  &&  m_nModes[1] != ARCHIVESEXTRACTIONINFO_EXECUTION_BYSCRIPT) || pProfileInfo->m_tExecution[0] == m_tExecution[0]) && (m_nModes[1] != ARCHIVESEXTRACTIONINFO_EXECUTION_ATDAILYTIME || pProfileInfo->m_tDailyExecution == m_tDailyExecution) && (m_nModes[1] != ARCHIVESEXTRACTIONINFO_EXECUTION_ATINTERVAL || (pProfileInfo->m_tExecution[1] == m_tExecution[1] && pProfileInfo->m_tIntervalExecution == m_tIntervalExecution  &&  pProfileInfo->m_tExecution[2] == m_tExecution[2])) && (m_nModes[1] != ARCHIVESEXTRACTIONINFO_EXECUTION_ATEVENT || pProfileInfo->m_szExecutionEvent == m_szExecutionEvent) && pProfileInfo->m_szAutomationScript == m_szAutomationScript  &&  pProfileInfo->m_szAutomationOutput == m_szAutomationOutput  &&  pProfileInfo->m_nAutomationOptions == m_nAutomationOptions  &&  pProfileInfo->m_bFTPOption == m_bFTPOption  &&  pProfileInfo->m_szFTPLocation == m_szFTPLocation  &&  pProfileInfo->m_szFTPUserName == m_szFTPUserName  &&  pProfileInfo->m_szFTPPassword == m_szFTPPassword  &&  pProfileInfo->m_nFTPPort == m_nFTPPort  &&  pProfileInfo->m_nFTPRetryCount[0] == m_nFTPRetryCount[0] && pProfileInfo->m_tFTPRetryInterval == m_tFTPRetryInterval  &&  pProfileInfo->m_nFTPAudition == m_nFTPAudition)
	{
		for (nParameter[0] = 0, nParameters[0] = (pProfileInfo->m_szParameters.GetSize() == m_szParameters.GetSize() && pProfileInfo->m_nParameterFormats.GetSize() == m_nParameterFormats.GetSize() && pProfileInfo->m_nParameterTriggers.GetSize() == m_nParameterTriggers.GetSize()) ? (INT)m_szParameters.GetSize() : -1; nParameter[0] < nParameters[0]; nParameter[0]++)
		{
			for (nParameter[1] = 0, nParameters[1] = nParameters[0]; nParameter[1] < nParameters[1]; nParameter[1]++)
			{
				if (pProfileInfo->m_szParameters.GetAt(nParameter[0]) == m_szParameters.GetAt(nParameter[1]))
				{
					if (pProfileInfo->m_nParameterFormats.GetAt(nParameter[0]) == m_nParameterFormats.GetAt(nParameter[1]) && pProfileInfo->m_nParameterTriggers.GetAt(nParameter[0]) == m_nParameterTriggers.GetAt(nParameter[1])) break;
					continue;
				}
			}
			if (nParameter[1] == nParameters[1]) break;
		}
		return((nParameter[0] == nParameters[0]) ? TRUE : FALSE);
	}
	return FALSE;
}

BOOL CArchivesExtractionProfileInfo::Map(CByteArray &nInfo) CONST
{
	DATA  sData;
	INT  cbData;
	INT  nParameter;
	INT  nParameters;
	CByteArray  nParameterData;

	sData.cbName = (m_szName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbSource = (m_szSource.GetLength() + 1)*sizeof(TCHAR);
	sData.cbFileName = (m_szFileName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbDirectory = (m_szDirectory.GetLength() + 1)*sizeof(TCHAR);
	sData.cbFTPLocation = (m_szFTPLocation.GetLength() + 1)*sizeof(TCHAR);
	sData.cbFTPUserName = (m_szFTPUserName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbFTPPassword = (m_szFTPPassword.GetLength() + 1)*sizeof(TCHAR);
	sData.cbDelimiters[0] = (m_szDelimiters[0].GetLength() + 1)*sizeof(TCHAR);
	sData.cbDelimiters[1] = (m_szDelimiters[1].GetLength() + 1)*sizeof(TCHAR);
	sData.cbDelimiters[2] = (m_szDelimiters[2].GetLength() + 1)*sizeof(TCHAR);
	sData.cbExecutionEvent = (m_szExecutionEvent.GetLength() + 1)*sizeof(TCHAR);
	sData.cbAutomationScript = (m_szAutomationScript.GetLength() + 1)*sizeof(TCHAR);
	sData.cbAutomationOutput = (m_szAutomationOutput.GetLength() + 1)*sizeof(TCHAR);
	for (nParameter = 0, nParameters = (INT)m_szParameters.GetSize(), sData.cbParameters[0] = 0, sData.cbParameters[1] = (INT)m_nParameterFormats.GetSize()*sizeof(UINT), sData.cbParameters[2] = (INT)m_nParameterTriggers.GetSize()*sizeof(UINT); nParameter < nParameters; nParameter++, sData.cbParameters[0] += cbData)
	{
		nParameterData.SetSize(sData.cbParameters[0] + (cbData = (m_szParameters.GetAt(nParameter).GetLength() + 1)*sizeof(TCHAR)));
		CopyMemory(nParameterData.GetData() + sData.cbParameters[0], (LPCTSTR)m_szParameters.GetAt(nParameter), cbData);
	}
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbName + sData.cbSource + sData.cbFileName + sData.cbDirectory + sData.cbFTPLocation + sData.cbFTPUserName + sData.cbFTPPassword + sData.cbDelimiters[0] + sData.cbDelimiters[1] + sData.cbDelimiters[2] + sData.cbExecutionEvent + sData.cbAutomationScript + sData.cbAutomationOutput + sData.cbParameters[0] + sData.cbParameters[1] + sData.cbParameters[2])), sData.nModes[0] = m_nModes[0], sData.nModes[1] = m_nModes[1], sData.nTimeFormat = m_nTimeFormat, sData.bTitleOption = m_bTitleOption, sData.nCharset = m_nCharset, sData.tRange[0] = m_tRange[0].GetTime(), sData.tRange[1] = m_tRange[1].GetTime(), sData.tDailyRange[0] = m_tDailyRange[0].GetTotalSeconds(), sData.tDailyRange[1] = m_tDailyRange[1].GetTotalSeconds(), sData.tIntervalRange[0] = m_tIntervalRange[0].GetTotalSeconds(), sData.tIntervalRange[1] = m_tIntervalRange[1].GetTotalSeconds(), sData.tIntervalRange[2] = m_tIntervalRange[2].GetTotalSeconds(), sData.tExecution[0] = m_tExecution[0].GetTime(), sData.tExecution[1] = m_tExecution[1].GetTime(), sData.tExecution[2] = m_tExecution[2].GetTime(), sData.tLastExecution = m_tLastExecution.GetTime(), sData.tDailyExecution = m_tDailyExecution.GetTotalSeconds(), sData.tIntervalExecution = m_tIntervalExecution.GetTotalSeconds(), sData.nCycleCount = m_nCycleCount, sData.nFTPPort = m_nFTPPort, sData.nFTPAudition = m_nFTPAudition, sData.tFTPRetry = m_tFTPRetry.GetTime(), sData.nFTPRetryCount[0] = m_nFTPRetryCount[0], sData.nFTPRetryCount[1] = m_nFTPRetryCount[1], sData.tFTPRetryInterval = m_tFTPRetryInterval.GetTotalSeconds(), sData.bFTPOption = m_bFTPOption, sData.nAutomationOptions = m_nAutomationOptions; nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szName, sData.cbName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbName), (LPCTSTR)m_szSource, sData.cbSource);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbSource), (LPCTSTR)m_szFileName, sData.cbFileName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbFileName), (LPCTSTR)m_szDirectory, sData.cbDirectory);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbDirectory), (LPCTSTR)m_szFTPLocation, sData.cbFTPLocation);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbFTPLocation), (LPCTSTR)m_szFTPUserName, sData.cbFTPUserName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbFTPUserName), (LPCTSTR)m_szFTPPassword, sData.cbFTPPassword);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbFTPPassword), (LPCTSTR)m_szDelimiters[0], sData.cbDelimiters[0]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbDelimiters[0]), (LPCTSTR)m_szDelimiters[1], sData.cbDelimiters[1]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbDelimiters[1]), (LPCTSTR)m_szDelimiters[2], sData.cbDelimiters[2]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbDelimiters[2]), (LPCTSTR)m_szExecutionEvent, sData.cbExecutionEvent);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbExecutionEvent), (LPCTSTR)m_szAutomationScript, sData.cbAutomationScript);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbAutomationScript), (LPCTSTR)m_szAutomationOutput, sData.cbAutomationOutput);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbAutomationOutput), nParameterData.GetData(), sData.cbParameters[0]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbParameters[0]), m_nParameterFormats.GetData(), sData.cbParameters[1]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbParameters[1]), m_nParameterTriggers.GetData(), sData.cbParameters[2]);
		return TRUE;
	}
	return FALSE;
}

BOOL CArchivesExtractionProfileInfo::Unmap(CONST CByteArray &nInfo)
{
	DATA  sData;
	INT  cbData;
	INT  cbParameter;
	INT  cbParameters;
	CByteArray  nParameterData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbName + sData.cbSource + sData.cbFileName + sData.cbDirectory + sData.cbFTPLocation + sData.cbFTPUserName + sData.cbFTPPassword + sData.cbDelimiters[0] + sData.cbDelimiters[1] + sData.cbDelimiters[2] + sData.cbExecutionEvent + sData.cbAutomationScript + sData.cbAutomationOutput + sData.cbParameters[0] + sData.cbParameters[1] + sData.cbParameters[2] && sData.cbName > 0 && sData.cbSource > 0 && sData.cbFileName > 0 && sData.cbDirectory > 0 && sData.cbFTPLocation > 0 && sData.cbFTPUserName > 0 && sData.cbFTPPassword > 0 && sData.cbDelimiters[0] > 0 && sData.cbDelimiters[1] > 0 && sData.cbDelimiters[2] > 0 && sData.cbExecutionEvent > 0 && sData.cbAutomationScript > 0 && sData.cbAutomationOutput > 0 && sData.cbParameters[0] >= 0 && sData.cbParameters[1] >= 0 && sData.cbParameters[2] >= 0; )
	{
		CopyMemory(m_szName.GetBufferSetLength(STRINGCHARS(sData.cbName)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbName));
		CopyMemory(m_szSource.GetBufferSetLength(STRINGCHARS(sData.cbSource)), nInfo.GetData() + (cbData = cbData + sData.cbName), STRINGBYTES(sData.cbSource));
		CopyMemory(m_szFileName.GetBufferSetLength(STRINGCHARS(sData.cbFileName)), nInfo.GetData() + (cbData = cbData + sData.cbSource), STRINGBYTES(sData.cbFileName));
		CopyMemory(m_szDirectory.GetBufferSetLength(STRINGCHARS(sData.cbDirectory)), nInfo.GetData() + (cbData = cbData + sData.cbFileName), STRINGBYTES(sData.cbDirectory));
		CopyMemory(m_szFTPLocation.GetBufferSetLength(STRINGCHARS(sData.cbFTPLocation)), nInfo.GetData() + (cbData = cbData + sData.cbDirectory), STRINGBYTES(sData.cbFTPLocation));
		CopyMemory(m_szFTPUserName.GetBufferSetLength(STRINGCHARS(sData.cbFTPUserName)), nInfo.GetData() + (cbData = cbData + sData.cbFTPLocation), STRINGBYTES(sData.cbFTPUserName));
		CopyMemory(m_szFTPPassword.GetBufferSetLength(STRINGCHARS(sData.cbFTPPassword)), nInfo.GetData() + (cbData = cbData + sData.cbFTPUserName), STRINGBYTES(sData.cbFTPPassword));
		CopyMemory(m_szDelimiters[0].GetBufferSetLength(STRINGCHARS(sData.cbDelimiters[0])), nInfo.GetData() + (cbData = cbData + sData.cbFTPPassword), STRINGBYTES(sData.cbDelimiters[0]));
		CopyMemory(m_szDelimiters[1].GetBufferSetLength(STRINGCHARS(sData.cbDelimiters[1])), nInfo.GetData() + (cbData = cbData + sData.cbDelimiters[0]), STRINGBYTES(sData.cbDelimiters[1]));
		CopyMemory(m_szDelimiters[2].GetBufferSetLength(STRINGCHARS(sData.cbDelimiters[2])), nInfo.GetData() + (cbData = cbData + sData.cbDelimiters[1]), STRINGBYTES(sData.cbDelimiters[2]));
		CopyMemory(m_szExecutionEvent.GetBufferSetLength(STRINGCHARS(sData.cbExecutionEvent)), nInfo.GetData() + (cbData = cbData + sData.cbDelimiters[2]), STRINGBYTES(sData.cbExecutionEvent));
		CopyMemory(m_szAutomationScript.GetBufferSetLength(STRINGCHARS(sData.cbAutomationScript)), nInfo.GetData() + (cbData = cbData + sData.cbExecutionEvent), STRINGBYTES(sData.cbAutomationScript));
		CopyMemory(m_szAutomationOutput.GetBufferSetLength(STRINGCHARS(sData.cbAutomationOutput)), nInfo.GetData() + (cbData = cbData + sData.cbAutomationScript), STRINGBYTES(sData.cbAutomationOutput));
		for (nParameterData.SetSize(sData.cbParameters[0]), m_nParameterFormats.SetSize(sData.cbParameters[1] / sizeof(UINT)), m_nParameterTriggers.SetSize(sData.cbParameters[2] / sizeof(UINT)), CopyMemory(nParameterData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbAutomationOutput), sData.cbParameters[0]), CopyMemory(m_nParameterFormats.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbParameters[0]), sData.cbParameters[1]), CopyMemory(m_nParameterTriggers.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbParameters[1]), sData.cbParameters[2]), m_nModes[0] = sData.nModes[0], m_nModes[1] = sData.nModes[1], m_nTimeFormat = sData.nTimeFormat, m_bTitleOption = sData.bTitleOption, m_nCharset = sData.nCharset, m_tRange[0] = sData.tRange[0], m_tRange[1] = sData.tRange[1], m_tDailyRange[0] = sData.tDailyRange[0], m_tDailyRange[1] = sData.tDailyRange[1], m_tIntervalRange[0] = sData.tIntervalRange[0], m_tIntervalRange[1] = sData.tIntervalRange[1], m_tIntervalRange[2] = sData.tIntervalRange[2], m_tExecution[0] = sData.tExecution[0], m_tExecution[1] = sData.tExecution[1], m_tExecution[2] = sData.tExecution[2], m_tLastExecution = sData.tLastExecution, m_tDailyExecution = sData.tDailyExecution, m_tIntervalExecution = sData.tIntervalExecution, m_nCycleCount = sData.nCycleCount, m_nFTPPort = sData.nFTPPort, m_nFTPAudition = sData.nFTPAudition, m_tFTPRetry = sData.tFTPRetry, m_nFTPRetryCount[0] = sData.nFTPRetryCount[0], m_nFTPRetryCount[1] = sData.nFTPRetryCount[1], m_tFTPRetryInterval = sData.tFTPRetryInterval, m_bFTPOption = sData.bFTPOption, m_nAutomationOptions = sData.nAutomationOptions, m_szName.ReleaseBuffer(), m_szSource.ReleaseBuffer(), m_szFileName.ReleaseBuffer(), m_szDirectory.ReleaseBuffer(), m_szFTPLocation.ReleaseBuffer(), m_szFTPUserName.ReleaseBuffer(), m_szFTPPassword.ReleaseBuffer(), m_szDelimiters[0].ReleaseBuffer(), m_szDelimiters[1].ReleaseBuffer(), m_szDelimiters[2].ReleaseBuffer(), m_szExecutionEvent.ReleaseBuffer(), m_szAutomationScript.ReleaseBuffer(), m_szAutomationOutput.ReleaseBuffer(), m_szParameters.RemoveAll(), cbParameter = cbParameters = 0; cbParameters < sData.cbParameters[0]; cbParameters += (cbParameter = (m_szParameters.GetAt(m_szParameters.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR)))
		{
			m_szParameters.Add((LPCTSTR)(nParameterData.GetData() + cbParameters));
			continue;
		}
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CArchivesExtractionProfiles

CArchivesExtractionProfiles::CArchivesExtractionProfiles() : CMutexArray()
{
	return;
}

CArchivesExtractionProfiles::~CArchivesExtractionProfiles()
{
	RemoveAll();
}

INT CArchivesExtractionProfiles::Add(CArchivesExtractionProfileInfo *pProfileInfo)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pProfileInfo->GetName(), TRUE)) >= 0) InsertAt(nIndex, pProfileInfo, 1);
	return nIndex;
}

INT CArchivesExtractionProfiles::Find(LPCTSTR pszName) CONST
{
	return FindIndex(pszName);
}

INT CArchivesExtractionProfiles::Enum(CStringArray &szNames) CONST
{
	INT  nProfile;
	INT  nProfiles;
	CArchivesExtractionProfileInfo  *pProfileInfo;

	for (nProfile = 0, nProfiles = (INT)GetSize(), szNames.RemoveAll(); nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo = GetAt(nProfile)) != (CArchivesExtractionProfileInfo *)NULL)
		{
			szNames.Add(pProfileInfo->GetName());
			continue;
		}
	}
	return((INT)szNames.GetSize());
}

CArchivesExtractionProfileInfo *CArchivesExtractionProfiles::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CArchivesExtractionProfileInfo *)CMutexArray::GetAt(nIndex) : (CArchivesExtractionProfileInfo *)NULL);
}

CArchivesExtractionProfileInfo *CArchivesExtractionProfiles::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CArchivesExtractionProfileInfo *)CMutexArray::GetAt(nIndex) : (CArchivesExtractionProfileInfo *)NULL);
}

VOID CArchivesExtractionProfiles::RemoveAll()
{
	INT  nProfile;
	INT  nProfiles;

	for (nProfile = 0, nProfiles = (INT)GetSize(); nProfile < nProfiles; nProfile++)
	{
		delete GetAt(nProfile);
		continue;
	}
	CMutexArray::RemoveAll();
}

BOOL CArchivesExtractionProfiles::Copy(CONST CArchivesExtractionProfiles *pProfiles)
{
	INT  nProfile;
	INT  nProfiles;
	CArchivesExtractionProfileInfo  *pProfileInfo;

	for (nProfile = 0, nProfiles = (INT)pProfiles->GetSize(), RemoveAll(); nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo = new CArchivesExtractionProfileInfo))
		{
			pProfileInfo->Copy(pProfiles->GetAt(nProfile));
			InsertAt(nProfile, pProfileInfo, 1);
			continue;
		}
		break;
	}
	return((nProfile == nProfiles) ? TRUE : FALSE);
}

BOOL CArchivesExtractionProfiles::Compare(CONST CArchivesExtractionProfiles *pProfiles) CONST
{
	INT  nProfile;
	INT  nProfiles;

	for (nProfile = 0, nProfiles = (pProfiles->GetSize() == GetSize()) ? (INT)GetSize() : -1; nProfile < nProfiles; nProfile++)
	{
		if (!pProfiles->GetAt(nProfile)->Compare(GetAt(nProfile))) break;
		continue;
	}
	return((nProfile == nProfiles) ? TRUE : FALSE);
}

BOOL CArchivesExtractionProfiles::Map(CByteArray &nInfo) CONST
{
	INT  nProfile;
	INT  nProfiles;
	CByteArray  nProfileData;
	CArchivesExtractionProfileInfo  *pProfileInfo;

	for (nProfile = 0, nProfiles = (INT)GetSize(), nInfo.RemoveAll(); nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo = GetAt(nProfile)) && pProfileInfo->Map(nProfileData) && nInfo.Append(nProfileData) >= 0) continue;
		break;
	}
	return((nProfile == nProfiles) ? TRUE : FALSE);
}

BOOL CArchivesExtractionProfiles::Unmap(CONST CByteArray &nInfo)
{
	INT  cbProfile;
	INT  cbProfiles;
	CByteArray  nProfileData;
	CArchivesExtractionProfileInfo  *pProfileInfo;

	for (cbProfiles = 0, RemoveAll(); cbProfiles < nInfo.GetSize(); cbProfiles += cbProfile)
	{
		for (CopyMemory(&cbProfile, nInfo.GetData() + cbProfiles, sizeof(cbProfile)), nProfileData.SetSize(max(min(cbProfile, nInfo.GetSize() - cbProfiles), 0)); nProfileData.GetSize() >= 0; )
		{
			CopyMemory(nProfileData.GetData(), nInfo.GetData() + cbProfiles, nProfileData.GetSize());
			break;
		}
		if ((pProfileInfo = new CArchivesExtractionProfileInfo))
		{
			if (pProfileInfo->Unmap(nProfileData))
			{
				InsertAt(GetSize(), pProfileInfo, 1);
				continue;
			}
			delete pProfileInfo;
		}
		break;
	}
	if ((pProfileInfo = (!nInfo.GetSize()) ? new CArchivesExtractionProfileInfo : (CArchivesExtractionProfileInfo *)NULL))
	{
		for (pProfileInfo->SetName(STRING(IDS_PROFILE_DEFAULTEXTRACTIONNAME)); Add(pProfileInfo) >= 0; ) return TRUE;
		delete pProfileInfo;
		return FALSE;
	}
	return((cbProfiles == nInfo.GetSize()) ? TRUE : FALSE);
}

INT CArchivesExtractionProfiles::FindIndex(LPCTSTR pszName, BOOL bInsert) CONST
{
	INT  nIndex[2];
	INT  nMinIndex;
	INT  nMaxIndex;
	CArchivesExtractionProfileInfo  *pProfileInfo;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex[0] = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex[0] = (nMinIndex + nMaxIndex) / 2)
	{
		nMinIndex = ((pProfileInfo = GetAt(nIndex[0]))) ? ((nIndex[1] = (pProfileInfo->GetName() <= pszName)) ? (nIndex[0] + 1) : nMinIndex) : (nIndex[0] = -1);
		nMaxIndex = (nIndex[0] < 0 || !nIndex[1]) ? nIndex[0] : nMaxIndex;
	}
	return((((!bInsert && (pProfileInfo = GetAt((nIndex[0] = max(nIndex[0] - 1, 0)))) && pProfileInfo->GetName() == pszName) || (bInsert  &&  nIndex[0] >= 0 && nIndex[0] <= GetSize())) && lstrlen(pszName) > 0) ? nIndex[0] : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CHistoryFileExtractionProfileInfo

CHistoryFileExtractionProfileInfo::CHistoryFileExtractionProfileInfo() : CObject()
{
	SetOptions(HISTORYFILEEXTRACTION_OPTION_NONE);
	SetFormatting(HISTORYFILEEXTRACTION_FORMAT_NONE);
	SetGapInterval(0);
	SetUpdateInterval(0);
}

VOID CHistoryFileExtractionProfileInfo::SetFileName(LPCTSTR pszFileName)
{
	m_szFileName = pszFileName;
}

CString CHistoryFileExtractionProfileInfo::GetFileName() CONST
{
	return m_szFileName;
}

VOID CHistoryFileExtractionProfileInfo::SetSources(CONST CStringArray &szSources)
{
	m_szSources.Copy(szSources);
}

INT CHistoryFileExtractionProfileInfo::GetSources(CStringArray &szSources) CONST
{
	szSources.Copy(m_szSources);
	return((INT)szSources.GetSize());
}

VOID CHistoryFileExtractionProfileInfo::SetOptions(UINT nOptions)
{
	m_nOptions[0] = nOptions;
}

UINT CHistoryFileExtractionProfileInfo::GetOptions() CONST
{
	return m_nOptions[0];
}

VOID CHistoryFileExtractionProfileInfo::SetFormatting(UINT nOptions)
{
	m_nOptions[1] = nOptions;
}

UINT CHistoryFileExtractionProfileInfo::GetFormatting() CONST
{
	return m_nOptions[1];
}

VOID CHistoryFileExtractionProfileInfo::SetGapInterval(CONST CTimeSpan &tInterval)
{
	m_tInterval = tInterval;
}

CTimeSpan CHistoryFileExtractionProfileInfo::GetGapInterval() CONST
{
	return m_tInterval;
}

VOID CHistoryFileExtractionProfileInfo::SetUpdateInterval(UINT nInterval)
{
	m_nInterval = nInterval;
}

UINT CHistoryFileExtractionProfileInfo::GetUpdateInterval() CONST
{
	return m_nInterval;
}

BOOL CHistoryFileExtractionProfileInfo::SetStartTime(CONST CTimeKey &tTime)
{
	if (m_nOptions[0] & HISTORYFILEEXTRACTION_OPTION_STARTTIME)
	{
		m_tStartTime = tTime;
		return TRUE;
	}
	return FALSE;
}

CTimeKey CHistoryFileExtractionProfileInfo::GetStartTime() CONST
{
	return((m_nOptions[0] & HISTORYFILEEXTRACTION_OPTION_STARTTIME) ? m_tStartTime : CTimeKey(0));
}

BOOL CHistoryFileExtractionProfileInfo::SetStopTime(CONST CTimeKey &tTime)
{
	if (m_nOptions[0] & HISTORYFILEEXTRACTION_OPTION_STOPTIME)
	{
		m_tStopTime = tTime;
		return TRUE;
	}
	return FALSE;
}

CTimeKey CHistoryFileExtractionProfileInfo::GetStopTime() CONST
{
	return((m_nOptions[0] & HISTORYFILEEXTRACTION_OPTION_STOPTIME) ? m_tStopTime : CTimeKey(0));
}

BOOL CHistoryFileExtractionProfileInfo::SetStopSize(DWORDLONG dwSize)
{
	if (m_nOptions[0] & HISTORYFILEEXTRACTION_OPTION_STOPSIZE)
	{
		m_dwStopSize = dwSize;
		return TRUE;
	}
	return FALSE;
}

DWORDLONG CHistoryFileExtractionProfileInfo::GetStopSize() CONST
{
	return((m_nOptions[0] & HISTORYFILEEXTRACTION_OPTION_STOPSIZE) ? m_dwStopSize : 0);
}

BOOL CHistoryFileExtractionProfileInfo::SetDeniedExecutionTime(CONST CTimeSpan &tStartTime, CONST CTimeSpan &tStopTime)
{
	if ((m_nOptions[0] & HISTORYFILEEXTRACTION_OPTION_EXECUTEOUTSIDETIME) && tStartTime.GetTotalSeconds() % SECONDSPERDAY <= tStopTime.GetTotalSeconds() % SECONDSPERDAY)
	{
		m_tExecution[0] = tStartTime.GetTotalSeconds() % SECONDSPERDAY;
		m_tExecution[1] = tStopTime.GetTotalSeconds() % SECONDSPERDAY;
		return TRUE;
	}
	return FALSE;
}

BOOL CHistoryFileExtractionProfileInfo::GetDeniedExecutionTime(CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST
{
	if (m_nOptions[0] & HISTORYFILEEXTRACTION_OPTION_EXECUTEOUTSIDETIME)
	{
		tStartTime = m_tExecution[0];
		tStopTime = m_tExecution[1];
		return TRUE;
	}
	return FALSE;
}

BOOL CHistoryFileExtractionProfileInfo::SetFilters(CONST CStringArray &szTags)
{
	m_szFilters.Copy(szTags);
	return TRUE;
}

INT CHistoryFileExtractionProfileInfo::GetFilters(CStringArray &szTags) CONST
{
	szTags.Copy(m_szFilters);
	return((INT)szTags.GetSize());
}

BOOL CHistoryFileExtractionProfileInfo::SetFilePrefix(LPCTSTR pszPrefix)
{
	if (m_nOptions[1] & HISTORYFILEEXTRACTION_FORMAT_USESEPARATEFILES)
	{
		m_szFilePrefix = pszPrefix;
		return TRUE;
	}
	return FALSE;
}

CString CHistoryFileExtractionProfileInfo::GetFilePrefix() CONST
{
	return((m_nOptions[1] & HISTORYFILEEXTRACTION_FORMAT_USESEPARATEFILES) ? m_szFilePrefix : EMPTYSTRING);
}

BOOL CHistoryFileExtractionProfileInfo::SetFileExtension(LPCTSTR pszExtension)
{
	if (m_nOptions[1] & HISTORYFILEEXTRACTION_FORMAT_USESEPARATEFILES)
	{
		m_szFileExtension = pszExtension;
		return TRUE;
	}
	return FALSE;
}

CString CHistoryFileExtractionProfileInfo::GetFileExtension() CONST
{
	return((m_nOptions[1] & HISTORYFILEEXTRACTION_FORMAT_USESEPARATEFILES) ? m_szFileExtension : EMPTYSTRING);
}

VOID CHistoryFileExtractionProfileInfo::Copy(CONST CHistoryFileExtractionProfileInfo *pInfo)
{
	m_szFileName = pInfo->m_szFileName;
	m_szFilePrefix = pInfo->m_szFilePrefix;
	m_szFileExtension = pInfo->m_szFileExtension;
	m_nOptions[0] = pInfo->m_nOptions[0];
	m_nOptions[1] = pInfo->m_nOptions[1];
	m_nInterval = pInfo->m_nInterval;
	m_tInterval = pInfo->m_tInterval;
	m_tStartTime = pInfo->m_tStartTime;
	m_tStopTime = pInfo->m_tStopTime;
	m_dwStopSize = pInfo->m_dwStopSize;
	m_tExecution[0] = pInfo->m_tExecution[0];
	m_tExecution[1] = pInfo->m_tExecution[1];
	m_szSources.Copy(pInfo->m_szSources);
	m_szFilters.Copy(pInfo->m_szFilters);
}

BOOL CHistoryFileExtractionProfileInfo::Compare(CONST CHistoryFileExtractionProfileInfo *pInfo) CONST
{
	INT  nSource[2];
	INT  nSources[2];
	INT  nFilter[2];
	INT  nFilters[2];

	for (nSource[0] = 0, nSources[0] = (!pInfo->m_szFileName.CompareNoCase(m_szFileName) && pInfo->m_nOptions[0] == m_nOptions[0] && pInfo->m_nOptions[1] == m_nOptions[1] && pInfo->m_nInterval == m_nInterval && pInfo->m_tInterval == m_tInterval && pInfo->m_szSources.GetSize() == m_szSources.GetSize() && (!(m_nOptions[0] & HISTORYFILEEXTRACTION_OPTION_STARTTIME) || pInfo->m_tStartTime == m_tStartTime) && (!(m_nOptions[0] & HISTORYFILEEXTRACTION_OPTION_STOPTIME) || pInfo->m_tStopTime == m_tStopTime) && (!(m_nOptions[0] & HISTORYFILEEXTRACTION_OPTION_STOPSIZE) || pInfo->m_dwStopSize == m_dwStopSize) && (!(m_nOptions[0] & HISTORYFILEEXTRACTION_OPTION_EXECUTEOUTSIDETIME) || (pInfo->m_tExecution[0] == m_tExecution[0] && pInfo->m_tExecution[1] == m_tExecution[1])) && (!(m_nOptions[1] & HISTORYFILEEXTRACTION_FORMAT_USESEPARATEFILES) || (!_tcscmp(pInfo->m_szFilePrefix, m_szFilePrefix) && !_tcscmp(pInfo->m_szFileExtension, m_szFileExtension)))) ? (INT)pInfo->m_szSources.GetSize() : -1; nSource[0] < nSources[0]; nSource[0]++)
	{
		for (nSource[1] = 0, nSources[1] = (INT)m_szSources.GetSize(); nSource[1] < nSources[1]; nSource[1]++)
		{
			if (!pInfo->m_szSources.GetAt(nSource[0]).CompareNoCase(m_szSources.GetAt(nSource[1]))) break;
			continue;
		}
		if (nSource[1] == nSources[1]) break;
	}
	for (nFilter[0] = 0, nFilters[0] = (nSource == nSources) ? ((m_nOptions[0] & HISTORYFILEEXTRACTION_OPTION_RAW) ? ((pInfo->m_szFilters.GetSize() == m_szFilters.GetSize()) ? (INT)pInfo->m_szFilters.GetSize() : -1) : 0) : 0; nFilter[0] < nFilters[0]; nFilter[0]++)
	{
		for (nFilter[1] = 0, nFilters[1] = (INT)m_szFilters.GetSize(); nFilter[1] < nFilters[1]; nFilter[1]++)
		{
			if (pInfo->m_szFilters.GetAt(nFilter[0]) == m_szFilters.GetAt(nFilter[1])) break;
			continue;
		}
		if (nFilter[1] == nFilters[1]) break;
	}
	return((nSource[0] == nSources[0] && nFilter[0] == nFilters[0]) ? TRUE : FALSE);
}

BOOL CHistoryFileExtractionProfileInfo::Map(CByteArray &nInfo) CONST
{
	DATA  sData;
	INT  cbData;
	INT  nSource;
	INT  nSources;
	INT  nFilter;
	INT  nFilters;
	CByteArray  nSourcesData;
	CByteArray  nFiltersData;

	sData.cbFileName = (m_szFileName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbFilePrefix = (m_szFilePrefix.GetLength() + 1)*sizeof(TCHAR);
	sData.cbFileExtension = (m_szFileExtension.GetLength() + 1)*sizeof(TCHAR);
	for (nSource = 0, nSources = (INT)m_szSources.GetSize(), sData.cbSources = 0; nSource < nSources; nSource++, sData.cbSources += cbData)
	{
		nSourcesData.SetSize(sData.cbSources + (cbData = (m_szSources.GetAt(nSource).GetLength() + 1)*sizeof(TCHAR)));
		CopyMemory(nSourcesData.GetData() + sData.cbSources, (LPCTSTR)m_szSources.GetAt(nSource), cbData);
	}
	for (nFilter = 0, nFilters = (INT)m_szFilters.GetSize(), sData.cbFilters = 0; nFilter < nFilters; nFilter++, sData.cbFilters += cbData)
	{
		nFiltersData.SetSize(sData.cbFilters + (cbData = (m_szFilters.GetAt(nFilter).GetLength() + 1)*sizeof(TCHAR)));
		CopyMemory(nFiltersData.GetData() + sData.cbFilters, (LPCTSTR)m_szFilters.GetAt(nFilter), cbData);
	}
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbFileName + sData.cbFilePrefix + sData.cbFileExtension + sData.cbSources + sData.cbFilters)), sData.nOptions[0] = m_nOptions[0], sData.nOptions[1] = m_nOptions[1], sData.nInterval = m_nInterval, sData.tInterval = m_tInterval.GetTotalSeconds(), sData.dwStopSize = m_dwStopSize, sData.tStartTime = m_tStartTime.GetTime(), sData.tStopTime = m_tStopTime.GetTime(), sData.tExecution[0] = m_tExecution[0].GetTotalSeconds(), sData.tExecution[1] = m_tExecution[1].GetTotalSeconds(); nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szFileName, sData.cbFileName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbFileName), (LPCTSTR)m_szFilePrefix, sData.cbFilePrefix);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbFilePrefix), (LPCTSTR)m_szFileExtension, sData.cbFileExtension);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbFileExtension), nSourcesData.GetData(), sData.cbSources);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbSources), nFiltersData.GetData(), sData.cbFilters);
		return TRUE;
	}
	return FALSE;
}

BOOL CHistoryFileExtractionProfileInfo::Unmap(CONST CByteArray &nInfo)
{
	DATA  sData;
	INT  cbData;
	INT  cbSource;
	INT  cbSources;
	INT  cbFilter;
	INT  cbFilters;
	CByteArray  nSourcesData;
	CByteArray  nFiltersData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbFileName + sData.cbFilePrefix + sData.cbFileExtension + sData.cbSources + sData.cbFilters && sData.cbFileName > 0 && sData.cbFilePrefix > 0 && sData.cbFileExtension > 0 && sData.cbSources >= 0 && sData.cbFilters >= 0; )
	{
		for (CopyMemory(m_szFileName.GetBufferSetLength(STRINGCHARS(sData.cbFileName)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbFileName)), CopyMemory(m_szFilePrefix.GetBufferSetLength(STRINGCHARS(sData.cbFilePrefix)), nInfo.GetData() + (cbData = cbData + sData.cbFileName), STRINGBYTES(sData.cbFilePrefix)), CopyMemory(m_szFileExtension.GetBufferSetLength(STRINGCHARS(sData.cbFileExtension)), nInfo.GetData() + (cbData = cbData + sData.cbFilePrefix), STRINGBYTES(sData.cbFileExtension)), nSourcesData.SetSize(sData.cbSources), CopyMemory(nSourcesData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbFileExtension), sData.cbSources), nFiltersData.SetSize(sData.cbFilters), CopyMemory(nFiltersData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbSources), sData.cbFilters), m_nOptions[0] = sData.nOptions[0], m_nOptions[1] = sData.nOptions[1], m_nInterval = sData.nInterval, m_tInterval = sData.tInterval, m_dwStopSize = sData.dwStopSize, m_tStartTime = sData.tStartTime, m_tStopTime = sData.tStopTime, m_tExecution[0] = sData.tExecution[0], m_tExecution[1] = sData.tExecution[1], m_szFileName.ReleaseBuffer(), m_szFilePrefix.ReleaseBuffer(), m_szFileExtension.ReleaseBuffer(), m_szSources.RemoveAll(), cbSource = cbSources = 0; cbSources < sData.cbSources; cbSources += (cbSource = (m_szSources.GetAt(m_szSources.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR)))
		{
			m_szSources.Add((LPCTSTR)(nSourcesData.GetData() + cbSources));
			continue;
		}
		for (m_szFilters.RemoveAll(), cbFilter = cbFilters = 0; cbFilters < sData.cbFilters; cbFilters += (cbFilter = (m_szFilters.GetAt(m_szFilters.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR)))
		{
			m_szFilters.Add((LPCTSTR)(nFiltersData.GetData() + cbFilters));
			continue;
		}
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CHistoryFileExtractionProfiles

CHistoryFileExtractionProfiles::CHistoryFileExtractionProfiles() : CMutexArray()
{
	return;
}

CHistoryFileExtractionProfiles::~CHistoryFileExtractionProfiles()
{
	RemoveAll();
}

INT CHistoryFileExtractionProfiles::Add(CHistoryFileExtractionProfileInfo *pProfileInfo)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pProfileInfo->GetFileName(), TRUE)) >= 0) InsertAt(nIndex, pProfileInfo, 1);
	return nIndex;
}

INT CHistoryFileExtractionProfiles::Find(LPCTSTR pszName) CONST
{
	return FindIndex(pszName);
}

INT CHistoryFileExtractionProfiles::Enum(CStringArray &szNames) CONST
{
	INT  nProfile;
	INT  nProfiles;
	CHistoryFileExtractionProfileInfo  *pProfileInfo;

	for (nProfile = 0, nProfiles = (INT)GetSize(), szNames.RemoveAll(); nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo = GetAt(nProfile)) != (CHistoryFileExtractionProfileInfo *)NULL)
		{
			szNames.Add(pProfileInfo->GetFileName());
			continue;
		}
	}
	return((INT)szNames.GetSize());
}

CHistoryFileExtractionProfileInfo *CHistoryFileExtractionProfiles::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CHistoryFileExtractionProfileInfo *)CMutexArray::GetAt(nIndex) : (CHistoryFileExtractionProfileInfo *)NULL);
}

CHistoryFileExtractionProfileInfo *CHistoryFileExtractionProfiles::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CHistoryFileExtractionProfileInfo *)CMutexArray::GetAt(nIndex) : (CHistoryFileExtractionProfileInfo *)NULL);
}

VOID CHistoryFileExtractionProfiles::RemoveAll()
{
	INT  nProfile;
	INT  nProfiles;

	for (nProfile = 0, nProfiles = (INT)GetSize(); nProfile < nProfiles; nProfile++)
	{
		delete GetAt(nProfile);
		continue;
	}
	CMutexArray::RemoveAll();
}

BOOL CHistoryFileExtractionProfiles::Copy(CONST CHistoryFileExtractionProfiles *pProfiles)
{
	INT  nProfile;
	INT  nProfiles;
	CHistoryFileExtractionProfileInfo  *pProfileInfo;

	for (nProfile = 0, nProfiles = (INT)pProfiles->GetSize(), RemoveAll(); nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo = new CHistoryFileExtractionProfileInfo))
		{
			pProfileInfo->Copy(pProfiles->GetAt(nProfile));
			InsertAt(nProfile, pProfileInfo, 1);
			continue;
		}
		break;
	}
	return((nProfile == nProfiles) ? TRUE : FALSE);
}

BOOL CHistoryFileExtractionProfiles::Compare(CONST CHistoryFileExtractionProfiles *pProfiles) CONST
{
	INT  nProfile;
	INT  nProfiles;

	for (nProfile = 0, nProfiles = (pProfiles->GetSize() == GetSize()) ? (INT)GetSize() : -1; nProfile < nProfiles; nProfile++)
	{
		if (!pProfiles->GetAt(nProfile)->Compare(GetAt(nProfile))) break;
		continue;
	}
	return((nProfile == nProfiles) ? TRUE : FALSE);
}

BOOL CHistoryFileExtractionProfiles::Map(CByteArray &nInfo) CONST
{
	INT  nProfile;
	INT  nProfiles;
	CByteArray  nProfileData;
	CHistoryFileExtractionProfileInfo  *pProfileInfo;

	for (nProfile = 0, nProfiles = (INT)GetSize(), nInfo.RemoveAll(); nProfile < nProfiles; nProfile++)
	{
		if ((pProfileInfo = GetAt(nProfile)) && pProfileInfo->Map(nProfileData) && nInfo.Append(nProfileData) >= 0) continue;
		break;
	}
	return((nProfile == nProfiles) ? TRUE : FALSE);
}

BOOL CHistoryFileExtractionProfiles::Unmap(CONST CByteArray &nInfo)
{
	INT  cbProfile;
	INT  cbProfiles;
	CByteArray  nProfileData;
	CHistoryFileExtractionProfileInfo  *pProfileInfo;

	for (cbProfiles = 0, RemoveAll(); cbProfiles < nInfo.GetSize(); cbProfiles += cbProfile)
	{
		for (CopyMemory(&cbProfile, nInfo.GetData() + cbProfiles, sizeof(cbProfile)), nProfileData.SetSize(max(min(cbProfile, nInfo.GetSize() - cbProfiles), 0)); nProfileData.GetSize() >= 0; )
		{
			CopyMemory(nProfileData.GetData(), nInfo.GetData() + cbProfiles, nProfileData.GetSize());
			break;
		}
		if ((pProfileInfo = new CHistoryFileExtractionProfileInfo))
		{
			if (pProfileInfo->Unmap(nProfileData))
			{
				InsertAt(GetSize(), pProfileInfo, 1);
				continue;
			}
			delete pProfileInfo;
		}
		break;
	}
	return((cbProfiles == nInfo.GetSize()) ? TRUE : FALSE);
}

INT CHistoryFileExtractionProfiles::FindIndex(LPCTSTR pszName, BOOL bInsert) CONST
{
	INT  nIndex[2];
	INT  nMinIndex;
	INT  nMaxIndex;
	CHistoryFileExtractionProfileInfo  *pProfileInfo;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex[0] = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex[0] = (nMinIndex + nMaxIndex) / 2)
	{
		nMinIndex = ((pProfileInfo = GetAt(nIndex[0]))) ? ((nIndex[1] = (pProfileInfo->GetFileName().CompareNoCase(pszName) <= 0)) ? (nIndex[0] + 1) : nMinIndex) : (nIndex[0] = -1);
		nMaxIndex = (nIndex[0] < 0 || !nIndex[1]) ? nIndex[0] : nMaxIndex;
	}
	return(((!bInsert && (pProfileInfo = GetAt((nIndex[0] = max(nIndex[0] - 1, 0)))) && !pProfileInfo->GetFileName().CompareNoCase(pszName)) || (bInsert  &&  nIndex[0] >= 0 && nIndex[0] <= GetSize())) ? nIndex[0] : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CHistoryFile

CHistoryFile::CHistoryFile() : CLogFile()
{
	m_wInterval = 0;
	m_wSequence = 0;
	m_nRetention = 0;
	m_tRetention = 0;
	m_fRetention = 0;
	m_tRetrieval = 0;
	m_fArchivePosition = 0;
	m_fRetrievePosition = 0;
	m_tFile.dwLowDateTime = 0;
	m_tFile.dwHighDateTime = 0;
	m_nPolicy = LOGFILE_POLICY_NONCYCLICMODE;
	m_bBuffering = FALSE;
	m_bBufferData = FALSE;
	m_bFirstAccess = TRUE;
}

CHistoryFile::~CHistoryFile()
{
	ResetBuffer();
}

UINT CHistoryFile::Open(LPCTSTR pszFileName, LPCTSTR pszSpacecraft, UINT nType, UINT nFlags, BOOL bWait)
{
	UINT  nResult;
	FILETIME  tFile;
	CTimeKey  tTimeKey;
	CFileFindEx  cFileFind;
	CByteArray  nHistoryData;
	HISTORYDATAHEADER  sDataHeader;

	if (TestDirectory(pszFileName))
	{
		if (CLogFile::Open(pszFileName, pszSpacecraft, (nType == HISTORYSTORE_TYPE_TM) ? STRING(IDS_LOGFILETYPE_TMHISTORY) : STRING(IDS_LOGFILETYPE_TCHISTORY), (nType == HISTORYSTORE_TYPE_TM) ? STRING(IDS_LOGFILETYPE_HISTORY) : (LPCTSTR)NULL, nFlags, bWait))
		{
			for (m_bBuffering = FALSE; (IsEmpty() && CheckSecurity(pszFileName) && Reset()) || (SeekToLast() && CLogFile::Read(tTimeKey, nHistoryData) && GetDataHeader(nHistoryData, &sDataHeader)); )
			{
				for (m_fArchivePosition = (!IsEmpty() && !m_fArchivePosition) ? sDataHeader.fPosition[0] : m_fArchivePosition, m_wInterval = (!m_wInterval) ? ((!IsEmpty()) ? sDataHeader.wInterval : HISTORYFILE_DEFAULT_UPDATEINTERVAL) : m_wInterval, m_wSequence = (!m_wSequence) ? ((!IsEmpty()) ? (sDataHeader.wSequence + 1) : (m_wSequence + 1)) : m_wSequence, m_wSequence = (m_wSequence <= m_wInterval) ? m_wSequence : 1, m_bFirstAccess = FALSE; GetTime(&tFile); )
				{
					if (m_tFile.dwLowDateTime || m_tFile.dwHighDateTime)
					{
						if (m_tFile.dwLowDateTime != tFile.dwLowDateTime)
						{
							m_fRetrievePosition = 0;
							m_tRetrieval = 0;
						}
						if (m_tFile.dwHighDateTime != tFile.dwHighDateTime)
						{
							m_fRetrievePosition = 0;
							m_tRetrieval = 0;
						}
					}
					for (m_tFile.dwLowDateTime = tFile.dwLowDateTime, m_tFile.dwHighDateTime = tFile.dwHighDateTime; (nResult = (!IsEmpty() || (nFlags & modeWrite) || (nFlags & modeReadWrite)) ? HISTORYFILE_SUCCESS : HISTORYFILE_DATA_NONE) == HISTORYFILE_DATA_NONE; )
					{
						Close();
						break;
					}
					return nResult;
				}
				break;
			}
			Close();
			return HISTORYFILE_OPEN_FAILURE;
		}
		if (Lock())
		{
			for (m_bBuffering = TRUE; (nResult = ((nFlags & modeWrite) || (nFlags & modeReadWrite)) ? (HISTORYFILE_SUCCESS | HISTORYFILE_BUFFERING) : 0) == (HISTORYFILE_SUCCESS | HISTORYFILE_BUFFERING); )
			{
				if (!m_bFirstAccess) return nResult;
				if (!bWait)
				{
					Unlock();
					return Open(pszFileName, pszSpacecraft, nType, nFlags, TRUE);
				}
				break;
			}
			Unlock();
		}
		return((!cFileFind.FindFile(pszFileName)) ? HISTORYFILE_DATA_NONE : HISTORYFILE_OPEN_FAILURE);
	}
	return HISTORYFILE_OPEN_FAILURE;
}

BOOL CHistoryFile::Reset()
{
	if (IsLocked())
	{
		ResetBuffer();
		m_wSequence = 1;
		m_tRetrieval = 0;
		m_fArchivePosition = 0;
		m_fRetrievePosition = 0;
		return CLogFile::Reset();
	}
	return FALSE;
}

VOID CHistoryFile::Close()
{
	if (IsLocked())
	{
		if (!m_bBuffering)
		{
			CLogFile::Close();
			return;
		}
		m_bBuffering = FALSE;
		Unlock();
	}
}

UINT CHistoryFile::Write(CONST CTMEnvironment *pTMEnvironment)
{
	BOOL  bUpdate;
	LPBYTE  pBufferData;
	CTimeTag  tBufferData;
	CByteArray  nHistoryData[2];
	CCompressionTools  cCompressionTools;
	HISTORYDATAHEADER  sDataHeader;

	if (IsLocked())
	{
		if (!m_bBuffering  &&  m_pBufferData.GetSize() > 0)
		{
			if ((pBufferData = (LPBYTE)m_pBufferData.GetAt(0)))
			{
				for (nHistoryData[0].SetSize(GlobalSize(pBufferData)), CopyMemory(nHistoryData[0].GetData(), pBufferData, nHistoryData[0].GetSize()); GetDataHeader(nHistoryData[0], &sDataHeader); )
				{
					for (sDataHeader.fPosition[0] = (sDataHeader.bUpdate) ? GetPosition() : m_fArchivePosition, sDataHeader.fPosition[1] = m_fArchivePosition, sDataHeader.fPosition[2] = (SeekToLast()) ? GetPosition() : 0, nHistoryData[0].RemoveAt(0, sizeof(sDataHeader)); SetDataHeader(&sDataHeader, nHistoryData[0]); )
					{
						if (CLogFile::Write(m_tBufferData.GetAt(0).GetTimeInSeconds(), nHistoryData[0]))
						{
							m_fArchivePosition = sDataHeader.fPosition[0];
							m_bBufferData = !m_pBufferData.IsEmpty();
							m_pBufferData.RemoveAt(0);
							m_tBufferData.RemoveAt(0);
							GlobalFree(pBufferData);
							return HISTORYFILE_SUCCESS | HISTORYFILE_DATA_MORE;
						}
						return HISTORYFILE_WRITE_FAILURE;
					}
					break;
				}
				GlobalFree(pBufferData);
				m_pBufferData.RemoveAt(0);
				m_tBufferData.RemoveAt(0);
				m_bBufferData = !m_pBufferData.IsEmpty();
				return HISTORYFILE_ERROR;
			}
			m_pBufferData.RemoveAt(0);
			m_tBufferData.RemoveAt(0);
			m_bBufferData = !m_pBufferData.IsEmpty();
			return HISTORYFILE_SUCCESS | HISTORYFILE_DATA_MORE;
		}
		if (m_bBuffering)
		{
			if (pTMEnvironment->GetTMUnit()->IsValid())
			{
				for (sDataHeader.wSequence = min(m_wSequence, m_wInterval), sDataHeader.wInterval = m_wInterval, sDataHeader.bUpdate = (!m_wInterval) ? TRUE : FALSE, sDataHeader.fPosition[0] = sDataHeader.fPosition[1] = sDataHeader.fPosition[2] = 0; pTMEnvironment->MapTMUnit(nHistoryData[0]) && cCompressionTools.Compress(nHistoryData[0], nHistoryData[1]) > 0 && SetDataHeader(&sDataHeader, nHistoryData[1]); )
				{
					for (tBufferData = pTMEnvironment->GetTMUnit()->GetTimeTag(); (pBufferData = (LPBYTE)GlobalAlloc(GPTR, nHistoryData[1].GetSize())); )
					{
						for (CopyMemory(pBufferData, nHistoryData[1].GetData(), nHistoryData[1].GetSize()), m_pBufferData.Add(pBufferData), m_tBufferData.Add(tBufferData), m_bBufferData = TRUE; m_wInterval > 0 && m_wSequence >= m_wInterval; )
						{
							for (sDataHeader.wSequence = sDataHeader.wInterval = m_wInterval, sDataHeader.bUpdate = TRUE; pTMEnvironment->Map(nHistoryData[0], tBufferData) && cCompressionTools.Compress(nHistoryData[0], nHistoryData[1]) > 0 && SetDataHeader(&sDataHeader, nHistoryData[1]); )
							{
								if ((pBufferData = (LPBYTE)GlobalAlloc(GPTR, nHistoryData[1].GetSize())) != (LPBYTE)NULL)
								{
									CopyMemory(pBufferData, nHistoryData[1].GetData(), nHistoryData[1].GetSize());
									m_pBufferData.Add(pBufferData);
									m_tBufferData.Add(tBufferData);
									m_wSequence = 1;
									return HISTORYFILE_SUCCESS;
								}
								break;
							}
							return HISTORYFILE_ERROR;
						}
						m_wSequence = (m_wInterval > 0) ? (m_wSequence + 1) : 0;
						return HISTORYFILE_SUCCESS;
					}
					break;
				}
				return HISTORYFILE_ERROR;
			}
			return HISTORYFILE_SUCCESS;
		}
		if (pTMEnvironment != (CONST CTMEnvironment *) NULL  &&  pTMEnvironment->GetTMUnit()->IsValid())
		{
			for (sDataHeader.wSequence = sDataHeader.wInterval = m_wInterval, sDataHeader.bUpdate = TRUE, sDataHeader.fPosition[0] = GetPosition(), sDataHeader.fPosition[1] = m_fArchivePosition, sDataHeader.fPosition[2] = (SeekToLast()) ? GetPosition() : 0, bUpdate = (IsEmpty() && pTMEnvironment->GetTMUnitCache()->GetSize() > 1) ? (m_wInterval > 0) : FALSE; bUpdate; )
			{
				if (pTMEnvironment->Map(nHistoryData[0], pTMEnvironment->GetTMUnit()->GetTimeTag()) && cCompressionTools.Compress(nHistoryData[0], nHistoryData[1]) > 0 && SetDataHeader(&sDataHeader, nHistoryData[1]) && CLogFile::Write(pTMEnvironment->GetTMUnit()->GetTimeTag().GetTimeInSeconds(), nHistoryData[1]))
				{
					m_fArchivePosition = sDataHeader.fPosition[0];
					m_wSequence = 1;
					break;
				}
				return HISTORYFILE_WRITE_FAILURE;
			}
			for (sDataHeader.wSequence = min(m_wSequence, m_wInterval), sDataHeader.wInterval = m_wInterval, sDataHeader.bUpdate = FALSE, sDataHeader.fPosition[0] = sDataHeader.fPosition[1] = m_fArchivePosition, sDataHeader.fPosition[2] = (SeekToLast()) ? GetPosition() : 0; pTMEnvironment->MapTMUnit(nHistoryData[0]) && cCompressionTools.Compress(nHistoryData[0], nHistoryData[1]) > 0 && SetDataHeader(&sDataHeader, nHistoryData[1]) && CLogFile::Write(pTMEnvironment->GetTMUnit()->GetTimeTag().GetTimeInSeconds(), nHistoryData[1]); )
			{
				for (sDataHeader.wSequence = sDataHeader.wInterval = m_wInterval, sDataHeader.bUpdate = TRUE, sDataHeader.fPosition[0] = GetPosition(), sDataHeader.fPosition[1] = m_fArchivePosition, sDataHeader.fPosition[2] = (SeekToLast()) ? GetPosition() : 0; m_wInterval > 0 && m_wSequence >= m_wInterval && !bUpdate; )
				{
					if (pTMEnvironment->Map(nHistoryData[0], pTMEnvironment->GetTMUnit()->GetTimeTag()) && cCompressionTools.Compress(nHistoryData[0], nHistoryData[1]) > 0 && SetDataHeader(&sDataHeader, nHistoryData[1]) && CLogFile::Write(pTMEnvironment->GetTMUnit()->GetTimeTag().GetTimeInSeconds(), nHistoryData[1]))
					{
						m_fArchivePosition = sDataHeader.fPosition[0];
						m_wSequence = 1;
						return HISTORYFILE_SUCCESS;
					}
					return HISTORYFILE_WRITE_FAILURE;
				}
				m_wSequence = (m_wInterval > 0) ? (m_wSequence + 1) : 0;
				return HISTORYFILE_SUCCESS;
			}
			return HISTORYFILE_WRITE_FAILURE;
		}
		return HISTORYFILE_SUCCESS;
	}
	return HISTORYFILE_ERROR;
}
UINT CHistoryFile::Write(CONST CTCEnvironment *pTCEnvironment)
{
	BOOL  bUpdate;
	LPBYTE  pBufferData;
	CTimeTag  tBufferData;
	CByteArray  nHistoryData[2];
	CCompressionTools  cCompressionTools;
	HISTORYDATAHEADER  sDataHeader;

	if (IsLocked())
	{
		if (!m_bBuffering  &&  m_pBufferData.GetSize() > 0)
		{
			if ((pBufferData = (LPBYTE)m_pBufferData.GetAt(0)))
			{
				for (nHistoryData[0].SetSize(GlobalSize(pBufferData)), CopyMemory(nHistoryData[0].GetData(), pBufferData, nHistoryData[0].GetSize()); GetDataHeader(nHistoryData[0], &sDataHeader); )
				{
					for (sDataHeader.fPosition[0] = (sDataHeader.bUpdate) ? GetPosition() : m_fArchivePosition, sDataHeader.fPosition[1] = m_fArchivePosition, sDataHeader.fPosition[2] = (SeekToLast()) ? GetPosition() : 0, nHistoryData[0].RemoveAt(0, sizeof(sDataHeader)); SetDataHeader(&sDataHeader, nHistoryData[0]); )
					{
						if (CLogFile::Write(m_tBufferData.GetAt(0).GetTimeInSeconds(), nHistoryData[0]))
						{
							m_fArchivePosition = sDataHeader.fPosition[0];
							m_bBufferData = !m_pBufferData.IsEmpty();
							m_pBufferData.RemoveAt(0);
							m_tBufferData.RemoveAt(0);
							GlobalFree(pBufferData);
							return HISTORYFILE_SUCCESS | HISTORYFILE_DATA_MORE;
						}
						return HISTORYFILE_WRITE_FAILURE;
					}
					break;
				}
				GlobalFree(pBufferData);
				m_pBufferData.RemoveAt(0);
				m_tBufferData.RemoveAt(0);
				m_bBufferData = !m_pBufferData.IsEmpty();
				return HISTORYFILE_ERROR;
			}
			m_pBufferData.RemoveAt(0);
			m_tBufferData.RemoveAt(0);
			m_bBufferData = !m_pBufferData.IsEmpty();
			return HISTORYFILE_SUCCESS | HISTORYFILE_DATA_MORE;
		}
		if (m_bBuffering)
		{
			if (pTCEnvironment->GetTCUnit()->IsValid() > 0)
			{
				for (sDataHeader.wSequence = min(m_wSequence, m_wInterval), sDataHeader.wInterval = m_wInterval, sDataHeader.bUpdate = (!m_wInterval) ? TRUE : FALSE, sDataHeader.fPosition[0] = sDataHeader.fPosition[1] = sDataHeader.fPosition[2] = 0; pTCEnvironment->MapTCUnit(nHistoryData[0]) && cCompressionTools.Compress(nHistoryData[0], nHistoryData[1]) > 0 && SetDataHeader(&sDataHeader, nHistoryData[1]); )
				{
					for (tBufferData = pTCEnvironment->GetTCUnit()->GetTimeTag(); (pBufferData = (LPBYTE)GlobalAlloc(GPTR, nHistoryData[1].GetSize())); )
					{
						for (CopyMemory(pBufferData, nHistoryData[1].GetData(), nHistoryData[1].GetSize()), m_pBufferData.Add(pBufferData), m_tBufferData.Add(tBufferData), m_bBufferData = TRUE; m_wInterval > 0 && m_wSequence >= m_wInterval; )
						{
							for (sDataHeader.wSequence = sDataHeader.wInterval = m_wInterval, sDataHeader.bUpdate = TRUE; pTCEnvironment->Map(nHistoryData[0]) && cCompressionTools.Compress(nHistoryData[0], nHistoryData[1]) > 0 && SetDataHeader(&sDataHeader, nHistoryData[1]); )
							{
								if ((pBufferData = (LPBYTE)GlobalAlloc(GPTR, nHistoryData[1].GetSize())) != (LPBYTE)NULL)
								{
									CopyMemory(pBufferData, nHistoryData[1].GetData(), nHistoryData[1].GetSize());
									m_pBufferData.Add(pBufferData);
									m_tBufferData.Add(tBufferData);
									m_wSequence = 1;
									return HISTORYFILE_SUCCESS;
								}
								break;
							}
							return HISTORYFILE_ERROR;
						}
						m_wSequence = (m_wInterval > 0) ? (m_wSequence + 1) : 0;
						return HISTORYFILE_SUCCESS;
					}
					break;
				}
				return HISTORYFILE_ERROR;
			}
			return HISTORYFILE_SUCCESS;
		}
		if (pTCEnvironment != (CONST CTCEnvironment *) NULL  &&  pTCEnvironment->GetTCUnit()->IsValid())
		{
			for (sDataHeader.wSequence = sDataHeader.wInterval = m_wInterval, sDataHeader.bUpdate = TRUE, sDataHeader.fPosition[0] = GetPosition(), sDataHeader.fPosition[1] = m_fArchivePosition, sDataHeader.fPosition[2] = (SeekToLast()) ? GetPosition() : 0, bUpdate = (IsEmpty()) ? (m_wInterval > 0) : FALSE; bUpdate; )
			{
				if (pTCEnvironment->Map(nHistoryData[0]) && cCompressionTools.Compress(nHistoryData[0], nHistoryData[1]) > 0 && SetDataHeader(&sDataHeader, nHistoryData[1]) && CLogFile::Write(pTCEnvironment->GetTCUnit()->GetTimeTag().GetTimeInSeconds(), nHistoryData[1]))
				{
					m_fArchivePosition = sDataHeader.fPosition[0];
					m_wSequence = 1;
					break;
				}
				return HISTORYFILE_WRITE_FAILURE;
			}
			for (sDataHeader.wSequence = min(m_wSequence, m_wInterval), sDataHeader.wInterval = m_wInterval, sDataHeader.bUpdate = FALSE, sDataHeader.fPosition[0] = sDataHeader.fPosition[1] = m_fArchivePosition, sDataHeader.fPosition[2] = (SeekToLast()) ? GetPosition() : 0; pTCEnvironment->MapTCUnit(nHistoryData[0]) && cCompressionTools.Compress(nHistoryData[0], nHistoryData[1]) > 0 && SetDataHeader(&sDataHeader, nHistoryData[1]) && CLogFile::Write(pTCEnvironment->GetTCUnit()->GetTimeTag().GetTimeInSeconds(), nHistoryData[1]); )
			{
				for (sDataHeader.wSequence = sDataHeader.wInterval = m_wInterval, sDataHeader.bUpdate = TRUE, sDataHeader.fPosition[0] = GetPosition(), sDataHeader.fPosition[1] = m_fArchivePosition, sDataHeader.fPosition[2] = (SeekToLast()) ? GetPosition() : 0; m_wInterval > 0 && m_wSequence >= m_wInterval && !bUpdate; )
				{
					if (pTCEnvironment->Map(nHistoryData[0]) && cCompressionTools.Compress(nHistoryData[0], nHistoryData[1]) > 0 && SetDataHeader(&sDataHeader, nHistoryData[1]) && CLogFile::Write(pTCEnvironment->GetTCUnit()->GetTimeTag().GetTimeInSeconds(), nHistoryData[1]))
					{
						m_fArchivePosition = sDataHeader.fPosition[0];
						m_wSequence = 1;
						return HISTORYFILE_SUCCESS;
					}
					return HISTORYFILE_WRITE_FAILURE;
				}
				m_wSequence = (m_wInterval > 0) ? (m_wSequence + 1) : 0;
				return HISTORYFILE_SUCCESS;
			}
			return HISTORYFILE_WRITE_FAILURE;
		}
		return HISTORYFILE_SUCCESS;
	}
	return HISTORYFILE_ERROR;
}

UINT CHistoryFile::Read(CTimeKey &tTimeKey, CTMEnvironment *pTMEnvironment)
{
	CTimeKey  tTime[2];
	CByteArray  nHistoryData[2];
	CCompressionTools  cCompressionTools;
	HISTORYDATAHEADER  sDataHeader = { 0 };

	if (IsLocked())
	{
		if (SeekTo(tTimeKey))
		{
			if (CLogFile::Read(tTime[0], nHistoryData[0]))
			{
				if (GetDataHeader(nHistoryData[0], &sDataHeader))
				{
					if (sDataHeader.bUpdate)
					{
						pTMEnvironment->Reset();
						m_tRetrieval = tTimeKey = tTime[0];
						m_fRetrievePosition = GetPosition();
						nHistoryData[0].RemoveAt(0, sizeof(sDataHeader));
						return((cCompressionTools.Decompress(nHistoryData[0], nHistoryData[1]) && pTMEnvironment->Unmap(nHistoryData[1])) ? (HISTORYFILE_SUCCESS | HISTORYFILE_SYNCHRONIZE | HISTORYFILE_TMPARAMETERS) : HISTORYFILE_READ_FAILURE);
					}
					if (CheckPosition(sDataHeader.fPosition[1]))
					{
						if (SeekPosition(sDataHeader.fPosition[1]))
						{
							if (CLogFile::Read(tTime[1], nHistoryData[0]))
							{
								if (CLogFile::Read(tTime[1], nHistoryData[0]))
								{
									if (GetDataHeader(nHistoryData[0], &sDataHeader))
									{
										if (tTime[0] >= tTime[1])
										{
											pTMEnvironment->Reset();
											m_tRetrieval = tTimeKey = tTime[1];
											m_fRetrievePosition = GetPosition();
											nHistoryData[0].RemoveAt(0, sizeof(sDataHeader));
											return((cCompressionTools.Decompress(nHistoryData[0], nHistoryData[1]) && ((sDataHeader.bUpdate  &&  pTMEnvironment->Unmap(nHistoryData[1])) || (!sDataHeader.bUpdate  &&  pTMEnvironment->UnmapTMUnit(nHistoryData[1])))) ? ((sDataHeader.bUpdate) ? (HISTORYFILE_SUCCESS | HISTORYFILE_SYNCHRONIZE | HISTORYFILE_TMPARAMETERS) : (HISTORYFILE_SUCCESS | HISTORYFILE_SYNCHRONIZE | HISTORYFILE_TMUNIT)) : HISTORYFILE_READ_FAILURE);
										}
										if (SeekToFirst())
										{
											if (CLogFile::Read(tTime[1], nHistoryData[0]))
											{
												if (GetDataHeader(nHistoryData[0], &sDataHeader))
												{
													pTMEnvironment->Reset();
													m_tRetrieval = tTimeKey = tTime[1];
													m_fRetrievePosition = GetPosition();
													nHistoryData[0].RemoveAt(0, sizeof(sDataHeader));
													return((cCompressionTools.Decompress(nHistoryData[0], nHistoryData[1]) && ((sDataHeader.bUpdate  &&  pTMEnvironment->Unmap(nHistoryData[1])) || (!sDataHeader.bUpdate  &&  pTMEnvironment->UnmapTMUnit(nHistoryData[1])))) ? ((sDataHeader.bUpdate) ? (HISTORYFILE_SUCCESS | HISTORYFILE_SYNCHRONIZE | HISTORYFILE_TMPARAMETERS) : (HISTORYFILE_SUCCESS | HISTORYFILE_SYNCHRONIZE | HISTORYFILE_TMUNIT)) : HISTORYFILE_READ_FAILURE);
												}
											}
										}
									}
								}
							}
						}
						m_tRetrieval = 0;
						m_fRetrievePosition = 0;
						pTMEnvironment->Reset();
						return HISTORYFILE_READ_FAILURE;
					}
					if (SeekToFirst())
					{
						if (CLogFile::Read(tTime[1], nHistoryData[0]))
						{
							if (GetDataHeader(nHistoryData[0], &sDataHeader))
							{
								pTMEnvironment->Reset();
								m_tRetrieval = tTimeKey = tTime[1];
								m_fRetrievePosition = GetPosition();
								nHistoryData[0].RemoveAt(0, sizeof(sDataHeader));
								return((cCompressionTools.Decompress(nHistoryData[0], nHistoryData[1]) && ((sDataHeader.bUpdate  &&  pTMEnvironment->Unmap(nHistoryData[1])) || (!sDataHeader.bUpdate  &&  pTMEnvironment->UnmapTMUnit(nHistoryData[1])))) ? ((sDataHeader.bUpdate) ? (HISTORYFILE_SUCCESS | HISTORYFILE_SYNCHRONIZE | HISTORYFILE_TMPARAMETERS) : (HISTORYFILE_SUCCESS | HISTORYFILE_SYNCHRONIZE | HISTORYFILE_TMUNIT)) : HISTORYFILE_READ_FAILURE);
							}
						}
					}
				}
			}
		}
		m_tRetrieval = 0;
		m_fRetrievePosition = 0;
		pTMEnvironment->Reset();
		return HISTORYFILE_READ_FAILURE;
	}
	return HISTORYFILE_ERROR;
}
UINT CHistoryFile::Read(CTimeKey &tTimeKey, CTCEnvironment *pTCEnvironment)
{
	CTimeKey  tTime;
	CByteArray  nHistoryData[2];
	CCompressionTools  cCompressionTools;
	HISTORYDATAHEADER  sDataHeader = { 0 };

	if (IsLocked())
	{
		if (SeekTo(tTimeKey, TRUE))
		{
			if (CLogFile::Read(tTime, nHistoryData[0]))
			{
				if (GetDataHeader(nHistoryData[0], &sDataHeader))
				{
					pTCEnvironment->Reset();
					m_tRetrieval = tTimeKey = tTime;
					m_fRetrievePosition = GetPosition();
					nHistoryData[0].RemoveAt(0, sizeof(sDataHeader));
					return((cCompressionTools.Decompress(nHistoryData[0], nHistoryData[1]) && ((sDataHeader.bUpdate  &&  pTCEnvironment->Unmap(nHistoryData[1])) || (!sDataHeader.bUpdate  &&  pTCEnvironment->UnmapTCUnit(nHistoryData[1])))) ? ((sDataHeader.bUpdate) ? (HISTORYFILE_SUCCESS | HISTORYFILE_SYNCHRONIZE | HISTORYFILE_TCPARAMETERS) : (HISTORYFILE_SUCCESS | HISTORYFILE_SYNCHRONIZE | HISTORYFILE_TCUNIT)) : HISTORYFILE_READ_FAILURE);
				}
			}
		}
		m_tRetrieval = 0;
		m_fRetrievePosition = 0;
		pTCEnvironment->Reset();
		return HISTORYFILE_READ_FAILURE;
	}
	return HISTORYFILE_ERROR;
}

UINT CHistoryFile::ReadNext(CTimeKey &tTimeKey, CONST CTimeSpan &tInterval, CTMEnvironment *pTMEnvironment)
{
	BOOL  bSuccess;
	CTimeKey  tTime;
	TIMEKEY  tTimeInterval;
	CByteArray  nHistoryData[2];
	CCompressionTools  cCompressionTools;
	HISTORYDATAHEADER  sDataHeader = { 0 };

	if (IsLocked())
	{
		if ((tTimeInterval = tInterval.GetTotalSeconds()) != 0)
		{
			if (SeekTo((tTimeInterval >= 0) ? (tTimeKey.GetTime() + tTimeInterval) : (tTimeKey.GetTime() - tTimeInterval)))
			{
				while ((bSuccess = CLogFile::Read(tTime, nHistoryData[0]) && GetDataHeader(nHistoryData[0], &sDataHeader)) && tInterval.GetTotalSeconds() > 0)
				{
					if (sDataHeader.bUpdate || sDataHeader.wSequence > sDataHeader.wInterval)
					{
						bSuccess = (sDataHeader.bUpdate) ? bSuccess : FALSE;
						break;
					}
				}
				if (bSuccess)
				{
					if (m_tRetrieval < tTime)
					{
						pTMEnvironment->Reset();
						m_tRetrieval = tTimeKey = tTime;
						m_fRetrievePosition = GetPosition();
						nHistoryData[0].RemoveAt(0, sizeof(sDataHeader));
						return((cCompressionTools.Decompress(nHistoryData[0], nHistoryData[1]) && ((sDataHeader.bUpdate  &&  pTMEnvironment->Unmap(nHistoryData[1])) || (!sDataHeader.bUpdate  &&  pTMEnvironment->UnmapTMUnit(nHistoryData[1])))) ? ((sDataHeader.bUpdate) ? (HISTORYFILE_SUCCESS | HISTORYFILE_SYNCHRONIZE | HISTORYFILE_TMPARAMETERS) : (HISTORYFILE_SUCCESS | HISTORYFILE_SYNCHRONIZE | HISTORYFILE_TMUNIT)) : HISTORYFILE_READ_FAILURE);
					}
				}
				if (IsEOFPosition(GetPosition())) return HISTORYFILE_SUCCESS;
			}
			m_tRetrieval = 0;
			m_fRetrievePosition = 0;
			pTMEnvironment->Reset();
			return HISTORYFILE_READ_FAILURE;
		}
		if (SeekToFirst())
		{
			if (CLogFile::Read(tTime, nHistoryData[0]) && GetDataHeader(nHistoryData[0], &sDataHeader))
			{
				if (m_tRetrieval < tTime)
				{
					m_fRetrievePosition = 0;
					m_tRetrieval = 0;
				}
			}
		}
		if (!IsEOFPosition(m_fRetrievePosition))
		{
			if (CheckPosition(m_fRetrievePosition))
			{
				if (SeekPosition(m_fRetrievePosition))
				{
					if (CLogFile::Read(tTime, nHistoryData[0]))
					{
						if (GetDataHeader(nHistoryData[0], &sDataHeader))
						{
							m_tRetrieval = tTimeKey = tTime;
							m_fRetrievePosition = GetPosition();
							pTMEnvironment->GetTMUnit()->Reset();
							nHistoryData[0].RemoveAt(0, sizeof(sDataHeader));
							return((sDataHeader.bUpdate || (cCompressionTools.Decompress(nHistoryData[0], nHistoryData[1]) && pTMEnvironment->UnmapTMUnit(nHistoryData[1]))) ? ((sDataHeader.bUpdate) ? (HISTORYFILE_SUCCESS | HISTORYFILE_TMPARAMETERS) : (HISTORYFILE_SUCCESS | HISTORYFILE_TMUNIT)) : HISTORYFILE_READ_FAILURE);
						}
					}
				}
				m_tRetrieval = 0;
				m_fRetrievePosition = 0;
				pTMEnvironment->Reset();
				return HISTORYFILE_READ_FAILURE;
			}
			if (SeekToFirst())
			{
				if (CLogFile::Read(tTime, nHistoryData[0]))
				{
					if (GetDataHeader(nHistoryData[0], &sDataHeader))
					{
						if (m_tRetrieval <= tTime)
						{
							pTMEnvironment->Reset();
							m_tRetrieval = tTimeKey = tTime;
							m_fRetrievePosition = GetPosition();
							nHistoryData[0].RemoveAt(0, sizeof(sDataHeader));
							return((cCompressionTools.Decompress(nHistoryData[0], nHistoryData[1]) && ((sDataHeader.bUpdate  &&  pTMEnvironment->Unmap(nHistoryData[1])) || (!sDataHeader.bUpdate  &&  pTMEnvironment->UnmapTMUnit(nHistoryData[1])))) ? ((sDataHeader.bUpdate) ? (HISTORYFILE_SUCCESS | HISTORYFILE_SYNCHRONIZE | HISTORYFILE_TMPARAMETERS) : (HISTORYFILE_SUCCESS | HISTORYFILE_SYNCHRONIZE | HISTORYFILE_TMUNIT)) : HISTORYFILE_READ_FAILURE);
						}
					}
				}
			}
			m_tRetrieval = 0;
			m_fRetrievePosition = 0;
			pTMEnvironment->Reset();
			return HISTORYFILE_READ_FAILURE;
		}
		return HISTORYFILE_SUCCESS;
	}
	return HISTORYFILE_ERROR;
}
UINT CHistoryFile::ReadNext(CTimeKey &tTimeKey, CTCEnvironment *pTCEnvironment)
{
	CTimeKey  tTime;
	CByteArray  nHistoryData[2];
	CCompressionTools  cCompressionTools;
	HISTORYDATAHEADER  sDataHeader = { 0 };

	if (IsLocked())
	{
		if (SeekToFirst())
		{
			if (CLogFile::Read(tTime, nHistoryData[0]) && GetDataHeader(nHistoryData[0], &sDataHeader))
			{
				if (m_tRetrieval < tTime)
				{
					m_fRetrievePosition = 0;
					m_tRetrieval = 0;
				}
			}
		}
		if (!IsEOFPosition(m_fRetrievePosition))
		{
			if (CheckPosition(m_fRetrievePosition))
			{
				if (SeekPosition(m_fRetrievePosition))
				{
					if (CLogFile::Read(tTime, nHistoryData[0]))
					{
						if (GetDataHeader(nHistoryData[0], &sDataHeader))
						{
							m_tRetrieval = tTimeKey = tTime;
							m_fRetrievePosition = GetPosition();
							pTCEnvironment->GetTCUnit()->Reset();
							nHistoryData[0].RemoveAt(0, sizeof(sDataHeader));
							return((sDataHeader.bUpdate || (cCompressionTools.Decompress(nHistoryData[0], nHistoryData[1]) && pTCEnvironment->UnmapTCUnit(nHistoryData[1]))) ? ((sDataHeader.bUpdate) ? (HISTORYFILE_SUCCESS | HISTORYFILE_TCPARAMETERS) : (HISTORYFILE_SUCCESS | HISTORYFILE_TCUNIT)) : HISTORYFILE_READ_FAILURE);
						}
					}
				}
				m_tRetrieval = 0;
				m_fRetrievePosition = 0;
				pTCEnvironment->Reset();
				return HISTORYFILE_READ_FAILURE;
			}
			if (SeekToFirst())
			{
				if (CLogFile::Read(tTime, nHistoryData[0]))
				{
					if (GetDataHeader(nHistoryData[0], &sDataHeader))
					{
						if (m_tRetrieval <= tTime)
						{
							pTCEnvironment->Reset();
							m_tRetrieval = tTimeKey = tTime;
							m_fRetrievePosition = GetPosition();
							nHistoryData[0].RemoveAt(0, sizeof(sDataHeader));
							return((cCompressionTools.Decompress(nHistoryData[0], nHistoryData[1]) && ((sDataHeader.bUpdate  &&  pTCEnvironment->Unmap(nHistoryData[1])) || (!sDataHeader.bUpdate  &&  pTCEnvironment->UnmapTCUnit(nHistoryData[1])))) ? ((sDataHeader.bUpdate) ? (HISTORYFILE_SUCCESS | HISTORYFILE_SYNCHRONIZE | HISTORYFILE_TCPARAMETERS) : (HISTORYFILE_SUCCESS | HISTORYFILE_SYNCHRONIZE | HISTORYFILE_TCUNIT)) : HISTORYFILE_READ_FAILURE);
						}
					}
				}
			}
			m_tRetrieval = 0;
			m_fRetrievePosition = 0;
			pTCEnvironment->Reset();
			return HISTORYFILE_READ_FAILURE;
		}
		return HISTORYFILE_SUCCESS;
	}
	return HISTORYFILE_ERROR;
}

UINT CHistoryFile::ReadPrev(CTimeKey &tTimeKey, CONST CTimeSpan &tInterval, CTMEnvironment *pTMEnvironment)
{
	CTimeKey  tTime;
	TIMEKEY  tTimeInterval;
	CByteArray  nHistoryData[2];
	CCompressionTools  cCompressionTools;
	HISTORYDATAHEADER  sDataHeader = { 0 };

	if (IsLocked())
	{
		if (tInterval.GetTotalSeconds() == -1)
		{
			if (IsEOFPosition(m_fRetrievePosition))
			{
				if (SeekToLast() && CheckPosition(GetPosition()))
				{
					if (CLogFile::Read(tTime, nHistoryData[0]))
					{
						if (GetDataHeader(nHistoryData[0], &sDataHeader))
						{
							if (CheckPosition(sDataHeader.fPosition[2]))
							{
								if (SeekPosition(sDataHeader.fPosition[2]))
								{
									if (CLogFile::Read(tTime, nHistoryData[0]))
									{
										if (GetDataHeader(nHistoryData[0], &sDataHeader))
										{
											if (!sDataHeader.bUpdate  &&  m_tRetrieval >= tTime)
											{
												pTMEnvironment->Reset();
												m_tRetrieval = tTimeKey = tTime;
												m_fRetrievePosition = GetPosition();
												nHistoryData[0].RemoveAt(0, sizeof(sDataHeader));
												return((cCompressionTools.Decompress(nHistoryData[0], nHistoryData[1]) && pTMEnvironment->UnmapTMUnit(nHistoryData[1])) ? (HISTORYFILE_SUCCESS | HISTORYFILE_SYNCHRONIZE | HISTORYFILE_TMUNIT) : HISTORYFILE_READ_FAILURE);
											}
											if (sDataHeader.bUpdate)
											{
												if (CheckPosition(sDataHeader.fPosition[2]))
												{
													if (SeekPosition(sDataHeader.fPosition[2]))
													{
														if (CLogFile::Read(tTime, nHistoryData[0]))
														{
															if (GetDataHeader(nHistoryData[0], &sDataHeader))
															{
																if (!sDataHeader.bUpdate  &&  m_tRetrieval >= tTime)
																{
																	pTMEnvironment->Reset();
																	m_tRetrieval = tTimeKey = tTime;
																	m_fRetrievePosition = GetPosition();
																	nHistoryData[0].RemoveAt(0, sizeof(sDataHeader));
																	return((cCompressionTools.Decompress(nHistoryData[0], nHistoryData[1]) && pTMEnvironment->UnmapTMUnit(nHistoryData[1])) ? (HISTORYFILE_SUCCESS | HISTORYFILE_SYNCHRONIZE | HISTORYFILE_TMUNIT) : HISTORYFILE_READ_FAILURE);
																}
																if (!sDataHeader.bUpdate)
																{
																	m_tRetrieval = 0;
																	m_fRetrievePosition = 0;
																	pTMEnvironment->Reset();
																	return HISTORYFILE_SUCCESS;
																}
															}
														}
													}
													m_tRetrieval = 0;
													m_fRetrievePosition = 0;
													pTMEnvironment->Reset();
													return HISTORYFILE_READ_FAILURE;
												}
											}
											m_tRetrieval = 0;
											m_fRetrievePosition = 0;
											pTMEnvironment->Reset();
											return HISTORYFILE_SUCCESS;
										}
									}
								}
								m_tRetrieval = 0;
								m_fRetrievePosition = 0;
								pTMEnvironment->Reset();
								return HISTORYFILE_READ_FAILURE;
							}
							m_tRetrieval = 0;
							m_fRetrievePosition = 0;
							pTMEnvironment->Reset();
							return HISTORYFILE_SUCCESS;
						}
					}
				}
				m_tRetrieval = 0;
				m_fRetrievePosition = 0;
				pTMEnvironment->Reset();
				return HISTORYFILE_READ_FAILURE;
			}
			if (CheckPosition(m_fRetrievePosition))
			{
				if (SeekPosition(m_fRetrievePosition))
				{
					if (CLogFile::Read(tTime, nHistoryData[0]))
					{
						if (GetDataHeader(nHistoryData[0], &sDataHeader))
						{
							if (CheckPosition(sDataHeader.fPosition[2]))
							{
								if (SeekPosition(sDataHeader.fPosition[2]))
								{
									if (CLogFile::Read(tTime, nHistoryData[0]))
									{
										if (GetDataHeader(nHistoryData[0], &sDataHeader))
										{
											if (CheckPosition(sDataHeader.fPosition[2]))
											{
												if (SeekPosition(sDataHeader.fPosition[2]))
												{
													if (CLogFile::Read(tTime, nHistoryData[0]))
													{
														if (GetDataHeader(nHistoryData[0], &sDataHeader))
														{
															if (!sDataHeader.bUpdate  &&  m_tRetrieval >= tTime)
															{
																pTMEnvironment->Reset();
																m_tRetrieval = tTimeKey = tTime;
																m_fRetrievePosition = GetPosition();
																nHistoryData[0].RemoveAt(0, sizeof(sDataHeader));
																return((cCompressionTools.Decompress(nHistoryData[0], nHistoryData[1]) && pTMEnvironment->UnmapTMUnit(nHistoryData[1])) ? (HISTORYFILE_SUCCESS | HISTORYFILE_SYNCHRONIZE | HISTORYFILE_TMUNIT) : HISTORYFILE_READ_FAILURE);
															}
															if (sDataHeader.bUpdate)
															{
																if (CheckPosition(sDataHeader.fPosition[2]))
																{
																	if (SeekPosition(sDataHeader.fPosition[2]))
																	{
																		if (CLogFile::Read(tTime, nHistoryData[0]))
																		{
																			if (GetDataHeader(nHistoryData[0], &sDataHeader))
																			{
																				if (!sDataHeader.bUpdate  &&  m_tRetrieval >= tTime)
																				{
																					pTMEnvironment->Reset();
																					m_tRetrieval = tTimeKey = tTime;
																					m_fRetrievePosition = GetPosition();
																					nHistoryData[0].RemoveAt(0, sizeof(sDataHeader));
																					return((cCompressionTools.Decompress(nHistoryData[0], nHistoryData[1]) && pTMEnvironment->UnmapTMUnit(nHistoryData[1])) ? (HISTORYFILE_SUCCESS | HISTORYFILE_SYNCHRONIZE | HISTORYFILE_TMUNIT) : HISTORYFILE_READ_FAILURE);
																				}
																				if (!sDataHeader.bUpdate)
																				{
																					m_tRetrieval = 0;
																					m_fRetrievePosition = 0;
																					pTMEnvironment->Reset();
																					return HISTORYFILE_SUCCESS;
																				}
																			}
																		}
																	}
																	m_tRetrieval = 0;
																	m_fRetrievePosition = 0;
																	pTMEnvironment->Reset();
																	return HISTORYFILE_READ_FAILURE;
																}
															}
															m_tRetrieval = 0;
															m_fRetrievePosition = 0;
															pTMEnvironment->Reset();
															return HISTORYFILE_SUCCESS;
														}
													}
												}
												m_tRetrieval = 0;
												m_fRetrievePosition = 0;
												pTMEnvironment->Reset();
												return HISTORYFILE_READ_FAILURE;
											}
											m_tRetrieval = 0;
											m_fRetrievePosition = 0;
											pTMEnvironment->Reset();
											return HISTORYFILE_SUCCESS;
										}
									}
								}
								m_tRetrieval = 0;
								m_fRetrievePosition = 0;
								pTMEnvironment->Reset();
								return HISTORYFILE_READ_FAILURE;
							}
							m_tRetrieval = 0;
							m_fRetrievePosition = 0;
							pTMEnvironment->Reset();
							return HISTORYFILE_SUCCESS;
						}
					}
				}
				m_tRetrieval = 0;
				m_fRetrievePosition = 0;
				pTMEnvironment->Reset();
				return HISTORYFILE_READ_FAILURE;
			}
			m_tRetrieval = 0;
			m_fRetrievePosition = 0;
			pTMEnvironment->Reset();
			return HISTORYFILE_SUCCESS;
		}
		tTimeInterval = tInterval.GetTotalSeconds();
		tTimeInterval = (tTimeInterval < 0) ? -tTimeInterval : tTimeInterval;
		if (SeekTo(tTimeKey.GetTime() - max(tTimeInterval, 1)))
		{
			if (CheckPosition((m_fRetrievePosition = GetPosition())))
			{
				if (CLogFile::Read(tTime, nHistoryData[0]))
				{
					if (GetDataHeader(nHistoryData[0], &sDataHeader))
					{
						if (tInterval.GetTotalSeconds() < 0)
						{
							if (m_tRetrieval > tTime)
							{
								pTMEnvironment->Reset();
								m_tRetrieval = tTimeKey = tTime;
								m_fRetrievePosition = GetPosition();
								nHistoryData[0].RemoveAt(0, sizeof(sDataHeader));
								return((cCompressionTools.Decompress(nHistoryData[0], nHistoryData[1]) && ((sDataHeader.bUpdate  &&  pTMEnvironment->Unmap(nHistoryData[1])) || (!sDataHeader.bUpdate  &&  pTMEnvironment->UnmapTMUnit(nHistoryData[1])))) ? ((sDataHeader.bUpdate) ? (HISTORYFILE_SUCCESS | HISTORYFILE_SYNCHRONIZE | HISTORYFILE_TMPARAMETERS) : (HISTORYFILE_SUCCESS | HISTORYFILE_SYNCHRONIZE | HISTORYFILE_TMUNIT)) : HISTORYFILE_READ_FAILURE);
							}
						}
						if (CheckPosition(sDataHeader.fPosition[1]))
						{
							if (SeekPosition(sDataHeader.fPosition[1]))
							{
								if (CLogFile::Read(tTime, nHistoryData[0]))
								{
									if (CLogFile::Read(tTime, nHistoryData[0]))
									{
										if (GetDataHeader(nHistoryData[0], &sDataHeader))
										{
											if (sDataHeader.bUpdate  &&  m_tRetrieval > tTime)
											{
												pTMEnvironment->Reset();
												m_tRetrieval = tTimeKey = tTime;
												m_fRetrievePosition = sDataHeader.fPosition[0];
												nHistoryData[0].RemoveAt(0, sizeof(sDataHeader));
												return((cCompressionTools.Decompress(nHistoryData[0], nHistoryData[1]) && pTMEnvironment->Unmap(nHistoryData[1])) ? (HISTORYFILE_SUCCESS | HISTORYFILE_SYNCHRONIZE | HISTORYFILE_TMPARAMETERS) : HISTORYFILE_READ_FAILURE);
											}
											if (SeekToFirst())
											{
												if (CLogFile::Read(tTime, nHistoryData[0]))
												{
													if (GetDataHeader(nHistoryData[0], &sDataHeader))
													{
														if (m_tRetrieval > tTime)
														{
															pTMEnvironment->Reset();
															m_tRetrieval = tTimeKey = tTime;
															m_fRetrievePosition = GetPosition();
															nHistoryData[0].RemoveAt(0, sizeof(sDataHeader));
															return((cCompressionTools.Decompress(nHistoryData[0], nHistoryData[1]) && ((sDataHeader.bUpdate  &&  pTMEnvironment->Unmap(nHistoryData[1])) || (!sDataHeader.bUpdate  &&  pTMEnvironment->UnmapTMUnit(nHistoryData[1])))) ? ((sDataHeader.bUpdate) ? (HISTORYFILE_SUCCESS | HISTORYFILE_SYNCHRONIZE | HISTORYFILE_TMPARAMETERS) : (HISTORYFILE_SUCCESS | HISTORYFILE_SYNCHRONIZE | HISTORYFILE_TMUNIT)) : HISTORYFILE_READ_FAILURE);
														}
														m_tRetrieval = 0;
														m_fRetrievePosition = 0;
														pTMEnvironment->Reset();
														return HISTORYFILE_SUCCESS;
													}
												}
											}
										}
									}
								}
							}
							m_tRetrieval = 0;
							m_fRetrievePosition = 0;
							pTMEnvironment->Reset();
							return HISTORYFILE_READ_FAILURE;
						}
						if (SeekToFirst())
						{
							if (CLogFile::Read(tTime, nHistoryData[0]))
							{
								if (GetDataHeader(nHistoryData[0], &sDataHeader))
								{
									if (m_tRetrieval > tTime)
									{
										pTMEnvironment->Reset();
										m_tRetrieval = tTimeKey = tTime;
										m_fRetrievePosition = GetPosition();
										nHistoryData[0].RemoveAt(0, sizeof(sDataHeader));
										return((cCompressionTools.Decompress(nHistoryData[0], nHistoryData[1]) && ((sDataHeader.bUpdate  &&  pTMEnvironment->Unmap(nHistoryData[1])) || (!sDataHeader.bUpdate  &&  pTMEnvironment->UnmapTMUnit(nHistoryData[1])))) ? ((sDataHeader.bUpdate) ? (HISTORYFILE_SUCCESS | HISTORYFILE_SYNCHRONIZE | HISTORYFILE_TMPARAMETERS) : (HISTORYFILE_SUCCESS | HISTORYFILE_SYNCHRONIZE | HISTORYFILE_TMUNIT)) : HISTORYFILE_READ_FAILURE);
									}
									m_tRetrieval = 0;
									m_fRetrievePosition = 0;
									pTMEnvironment->Reset();
									return HISTORYFILE_SUCCESS;
								}
							}
						}
					}
				}
			}
		}
		m_tRetrieval = 0;
		m_fRetrievePosition = 0;
		pTMEnvironment->Reset();
		return HISTORYFILE_READ_FAILURE;
	}
	return HISTORYFILE_ERROR;
}

BOOL CHistoryFile::Rename(LPCTSTR pszFileName, LPCTSTR pszNewFileName, BOOL bHide)
{
	return CLogFile::Rename(pszFileName, pszNewFileName, bHide);
}

BOOL CHistoryFile::Remove(LPCTSTR pszFileName)
{
	return CLogFile::Remove(pszFileName);
}

BOOL CHistoryFile::SetUpdateInterval(WORD wInterval)
{
	if (IsLocked())
	{
		m_wInterval = wInterval;
		return TRUE;
	}
	return FALSE;
}

BOOL CHistoryFile::GetUpdateInterval(WORD &wInterval) CONST
{
	if (IsLocked())
	{
		wInterval = m_wInterval;
		return TRUE;
	}
	return FALSE;
}

BOOL CHistoryFile::IsBufferEmpty() CONST
{
	return !m_bBufferData;
}

BOOL CHistoryFile::DoBackup(CONST CTMEnvironment *pTMEnvironment, DWORDLONG dwSize) CONST
{
	CByteArray  nHistoryData[4];
	CCompressionTools  cCompressionTools;
	HISTORYDATAHEADER  sDataHeader = { 0 };

	return((pTMEnvironment != (CONST CTMEnvironment *) NULL  &&  !m_pBufferData.GetSize()) ? ((pTMEnvironment->MapTMUnit(nHistoryData[0]) && cCompressionTools.Compress(nHistoryData[0], nHistoryData[1]) > 0 && SetDataHeader(&sDataHeader, nHistoryData[1]) && (!m_wInterval || m_wSequence < m_wInterval || (pTMEnvironment->Map(nHistoryData[2], (pTMEnvironment->GetTMUnit()->IsValid()) ? pTMEnvironment->GetTMUnit()->GetTimeTag() : -1) && cCompressionTools.Compress(nHistoryData[2], nHistoryData[3]) > 0 && SetDataHeader(&sDataHeader, nHistoryData[3])))) ? ((CalculatePosition(CalculatePosition(m_fPosition, (INT)nHistoryData[1].GetSize()), (INT)nHistoryData[3].GetSize()) > dwSize) ? TRUE : FALSE) : FALSE) : ((CalculatePosition(m_fPosition, (m_pBufferData.GetSize() > 0) ? (INT)GlobalSize(m_pBufferData.GetAt(0)) : 0) > dwSize) ? TRUE : FALSE));
}
BOOL CHistoryFile::DoBackup(CONST CTCEnvironment *pTCEnvironment, DWORDLONG dwSize) CONST
{
	CByteArray  nHistoryData[4];
	CCompressionTools  cCompressionTools;
	HISTORYDATAHEADER  sDataHeader = { 0 };

	return((pTCEnvironment != (CONST CTCEnvironment *) NULL  &&  !m_pBufferData.GetSize()) ? ((pTCEnvironment->MapTCUnit(nHistoryData[0]) && cCompressionTools.Compress(nHistoryData[0], nHistoryData[1]) > 0 && SetDataHeader(&sDataHeader, nHistoryData[1]) && (!m_wInterval || m_wSequence < m_wInterval || (pTCEnvironment->Map(nHistoryData[2]) && cCompressionTools.Compress(nHistoryData[2], nHistoryData[3]) > 0 && SetDataHeader(&sDataHeader, nHistoryData[3])))) ? ((CalculatePosition(CalculatePosition(m_fPosition, (INT)nHistoryData[1].GetSize()), (INT)nHistoryData[3].GetSize()) > dwSize) ? TRUE : FALSE) : FALSE) : ((CalculatePosition(m_fPosition, (m_pBufferData.GetSize() > 0) ? (INT)GlobalSize(m_pBufferData.GetAt(0)) : 0) > dwSize) ? TRUE : FALSE));
}

BOOL CHistoryFile::TestDirectory(LPCTSTR pszFileName) CONST
{
	INT  nPos;
	CString  szDrive;
	CString  szFilePath;
	CString  szFileName;
	CString  szFileTitle;
	CFileFindEx  cFileFind;
	CLogicalDrives  cDrives;
	CSecurityDescriptor  cSecurityDescriptor;

	if (cFileFind.FindFile((szFileName = pszFileName)))
	{
		cFileFind.Close();
		return TRUE;
	}
	for (nPos = lstrlen(szFileName), szDrive = cDrives.ExtractDrive(szFileName), ::GetFileTitle(szFileName, szFileTitle.GetBufferSetLength(max(::GetFileTitle(szFileName, (LPTSTR)NULL, 0) - 1, 0)), ::GetFileTitle(szFileName, (LPTSTR)NULL, 0)), szFileTitle.ReleaseBuffer(), nPos -= szFileTitle.GetLength(), szFilePath = (nPos > 0) ? szFileName : EMPTYSTRING; nPos >= 0; nPos--)
	{
		if (!_tcsnicmp(szFileName.Mid(nPos), szFileTitle, szFileTitle.GetLength()))
		{
			if (!_tcsnicmp(szFileName, szDrive, szDrive.GetLength()) && szDrive.GetLength() > 0)
			{
				szFilePath = (nPos > szDrive.GetLength()) ? szFileName.Left(nPos - 1) : EMPTYSTRING;
				break;
			}
			if (!_tcsnicmp(szFileName, szDrive, szDrive.GetLength() - 1) && szDrive.GetLength() > 0)
			{
				szFilePath = (nPos > szDrive.GetLength() - 1) ? szFileName.Left(nPos - 1) : EMPTYSTRING;
				break;
			}
			szFilePath = (nPos > 0 && cDrives.GetPathDelimiter() == szFileName.GetAt(nPos - 1)) ? szFileName.Left(nPos - 1) : szFileName.Left(nPos);
			break;
		}
	}
	if (!szFilePath.IsEmpty())
	{
		if (!cFileFind.FindFile(szFilePath))
		{
			if (SHCreateDirectoryEx((HWND)NULL, CFileEx::TranslateToUNCName(szFilePath), (LPSECURITY_ATTRIBUTES)NULL) == ERROR_SUCCESS)
			{
				if (cSecurityDescriptor.SetRightsOfSystem(GENERIC_ALL | STANDARD_RIGHTS_ALL | SPECIFIC_RIGHTS_ALL, CONTAINER_INHERIT_ACE | OBJECT_INHERIT_ACE) && cSecurityDescriptor.SetRightsOfAdministrators(GENERIC_ALL | STANDARD_RIGHTS_ALL | SPECIFIC_RIGHTS_ALL, CONTAINER_INHERIT_ACE | OBJECT_INHERIT_ACE) && (cSecurityDescriptor.SetRightsOfSystemOperators(GENERIC_READ | GENERIC_WRITE | STANDARD_RIGHTS_READ | STANDARD_RIGHTS_WRITE | SYNCHRONIZE | FILE_LIST_DIRECTORY | FILE_READ_EA | FILE_WRITE_EA | FILE_TRAVERSE | FILE_READ_ATTRIBUTES | FILE_WRITE_ATTRIBUTES, CONTAINER_INHERIT_ACE | OBJECT_INHERIT_ACE) || cSecurityDescriptor.SetRightsOfPowerUsers(GENERIC_READ | GENERIC_WRITE | STANDARD_RIGHTS_READ | STANDARD_RIGHTS_WRITE | SYNCHRONIZE | FILE_LIST_DIRECTORY | FILE_READ_EA | FILE_WRITE_EA | FILE_TRAVERSE | FILE_READ_ATTRIBUTES | FILE_WRITE_ATTRIBUTES, CONTAINER_INHERIT_ACE | OBJECT_INHERIT_ACE)) && cSecurityDescriptor.SetRightsOfAuthenticatedUsers(GENERIC_READ | STANDARD_RIGHTS_READ | SYNCHRONIZE | FILE_LIST_DIRECTORY | FILE_READ_EA | FILE_TRAVERSE | FILE_READ_ATTRIBUTES, CONTAINER_INHERIT_ACE | OBJECT_INHERIT_ACE) && cSecurityDescriptor.SetRightsOfEveryone(GENERIC_READ | STANDARD_RIGHTS_READ | SYNCHRONIZE | FILE_LIST_DIRECTORY | FILE_READ_EA | FILE_TRAVERSE | FILE_READ_ATTRIBUTES, CONTAINER_INHERIT_ACE | OBJECT_INHERIT_ACE))
				{
					CSecurity::SecureDirectory(CFileEx::TranslateToUNCName(szFilePath), cSecurityDescriptor);
					return TRUE;
				}
				RemoveDirectory(CFileEx::TranslateToUNCName(szFilePath));
			}
			return FALSE;
		}
		cFileFind.Close();
	}
	return TRUE;
}

BOOL CHistoryFile::CheckSecurity(LPCTSTR pszFileName) CONST
{
	CSecurityDescriptor  cSecurityDescriptor;

	return((cSecurityDescriptor.SetRightsOfSystem(FILE_ALL_ACCESS) && cSecurityDescriptor.SetRightsOfAdministrators(FILE_ALL_ACCESS) && (cSecurityDescriptor.SetRightsOfSystemOperators(FILE_GENERIC_READ | FILE_GENERIC_WRITE) || cSecurityDescriptor.SetRightsOfPowerUsers(FILE_GENERIC_READ | FILE_GENERIC_WRITE)) && cSecurityDescriptor.SetRightsOfAuthenticatedUsers(FILE_GENERIC_READ) && cSecurityDescriptor.SetRightsOfEveryone(FILE_GENERIC_READ) && CSecurity::SecureFile(CFileEx::TranslateToUNCName(pszFileName), cSecurityDescriptor)) ? TRUE : FALSE);
}

BOOL CHistoryFile::SetDataHeader(CONST PHISTORYDATAHEADER pDataHeader, CByteArray &nData) CONST
{
	CByteArray  nHeaderData;

	for (nHeaderData.SetSize(sizeof(HISTORYDATAHEADER)); nHeaderData.GetSize() == sizeof(HISTORYDATAHEADER); )
	{
		CopyMemory(nHeaderData.GetData(), pDataHeader, sizeof(HISTORYDATAHEADER));
		nData.InsertAt(0, &nHeaderData);
		return TRUE;
	}
	return FALSE;
}

BOOL CHistoryFile::GetDataHeader(CONST CByteArray &nData, PHISTORYDATAHEADER pDataHeader) CONST
{
	if (nData.GetSize() >= sizeof(HISTORYDATAHEADER))
	{
		CopyMemory(pDataHeader, nData.GetData(), sizeof(HISTORYDATAHEADER));
		return TRUE;
	}
	return FALSE;
}

VOID CHistoryFile::ResetBuffer()
{
	INT  nItem;
	INT  nItems;
	LPBYTE  pBufferData;

	for (nItem = 0, nItems = (INT)m_pBufferData.GetSize(); nItem < nItems; nItem++)
	{
		if ((pBufferData = (LPBYTE)m_pBufferData.GetAt(nItem)))
		{
			GlobalFree(pBufferData);
			continue;
		}
	}
	m_pBufferData.RemoveAll();
	m_tBufferData.RemoveAll();
	m_bBufferData = FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CHistoryStoreFile

CHistoryStoreFile::CHistoryStoreFile() : CHistoryFile()
{
	m_nOptions = HISTORYSTORE_OPTION_NONE;
	m_nErrorCode = 0;
	m_nRetries[0] = 0;
	m_nRetries[1] = 0;
	m_wUpdates = 0;
	m_tStartTime = 0;
	m_tStopTime = 0;
	m_tBackupTime = 0;
	m_tDailyStartTime = 0;
	m_tDailyStopTime = 0;
	m_tBackupStartTime = 0;
	m_tBackupStopTime = 0;
	m_tBackupInterval = 0;
	m_dwBackupSize = 0;
	m_dwFileSize = 0;
}

UINT CHistoryStoreFile::Open(LPCTSTR pszFileName, LPCTSTR pszSpacecraft, UINT nType, UINT nFlags, BOOL bWait)
{
	UINT  nResult;

	if ((nResult = CHistoryFile::Open(pszFileName, pszSpacecraft, nType, nFlags, bWait)) == HISTORYFILE_SUCCESS)
	{
		SetMode((GetOptions() & HISTORYSTORE_OPTION_CYCLIC) ? LOGFILE_POLICY_CYCLICMODE : LOGFILE_POLICY_NONCYCLICMODE);
		SetUpdateInterval((GetOptions() & HISTORYSTORE_OPTION_FULLUPDATES) ? GetUpdateInterval() : 0);
		SetRetentionBySize((GetOptions() & HISTORYSTORE_OPTION_LIMITEDSIZE) ? GetFileSize() : 0);
		Compress((GetOptions() & HISTORYSTORE_OPTION_COMPRESSION) ? TRUE : FALSE);
		return((!IsEmpty() || Reset()) ? nResult : HISTORYFILE_ERROR);
	}
	return nResult;
}

VOID CHistoryStoreFile::Close()
{
	CHistoryFile::Close();
}

VOID CHistoryStoreFile::SetFileName(LPCTSTR pszFileName)
{
	m_szName[0] = pszFileName;
}

CString CHistoryStoreFile::GetFileName() CONST
{
	return m_szName[0];
}

VOID CHistoryStoreFile::SetSecondaryFileName(LPCTSTR pszFileName)
{
	m_szName[1] = pszFileName;
}

CString CHistoryStoreFile::GetSecondaryFileName() CONST
{
	return((m_nOptions & HISTORYSTORE_OPTION_SECONDARY) ? (LPCTSTR)m_szName[1] : EMPTYSTRING);
}

VOID CHistoryStoreFile::SetOptions(UINT nOptions)
{
	m_nOptions = nOptions;
}

UINT CHistoryStoreFile::GetOptions() CONST
{
	return m_nOptions;
}

VOID CHistoryStoreFile::SetPeriod(CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime)
{
	m_tStartTime = (tStartTime < tStopTime) ? tStartTime : 0;
	m_tStopTime = (tStartTime < tStopTime) ? tStopTime : 0;
}

BOOL CHistoryStoreFile::GetPeriod(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	if (m_nOptions & HISTORYSTORE_OPTION_LIMITEDUSE)
	{
		tStartTime = m_tStartTime;
		tStopTime = m_tStopTime;
		return TRUE;
	}
	return FALSE;
}

VOID CHistoryStoreFile::SetDailyPeriod(CONST CTimeSpan &tStartTime, CONST CTimeSpan &tStopTime)
{
	m_tDailyStartTime = (tStartTime < tStopTime) ? tStartTime : 0;
	m_tDailyStopTime = (tStartTime < tStopTime) ? tStopTime : 0;
}

BOOL CHistoryStoreFile::GetDailyPeriod(CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST
{
	if (m_nOptions & HISTORYSTORE_OPTION_DAILYUSE)
	{
		tStartTime = m_tDailyStartTime;
		tStopTime = m_tDailyStopTime;
		return TRUE;
	}
	return FALSE;
}

VOID CHistoryStoreFile::SetFileSize(DWORDLONG dwSize)
{
	m_dwFileSize = dwSize;
}

DWORDLONG CHistoryStoreFile::GetFileSize() CONST
{
	return((m_nOptions & HISTORYSTORE_OPTION_LIMITEDSIZE) ? m_dwFileSize : 0);
}

VOID CHistoryStoreFile::SetUpdateInterval(WORD wInterval)
{
	m_wUpdates = m_wInterval = wInterval;
}

WORD CHistoryStoreFile::GetUpdateInterval() CONST
{
	return((m_nOptions & HISTORYSTORE_OPTION_FULLUPDATES) ? m_wUpdates : 0);
}

VOID CHistoryStoreFile::SetBackupFileName(LPCTSTR pszFileName)
{
	m_szTempName = pszFileName;
}

CString CHistoryStoreFile::GetBackupFileName() CONST
{
	return m_szTempName;
}

VOID CHistoryStoreFile::SetBackupDirectory(LPCTSTR pszDirectory)
{
	m_szDirectory = pszDirectory;
}

CString CHistoryStoreFile::GetBackupDirectory() CONST
{
	return m_szDirectory;
}

VOID CHistoryStoreFile::SetBackupSize(DWORDLONG dwSize)
{
	m_dwBackupSize = dwSize;
}

DWORDLONG CHistoryStoreFile::GetBackupSize() CONST
{
	return((m_nOptions & HISTORYSTORE_OPTION_BACKUPBYSIZE) ? m_dwBackupSize : 0);
}

VOID CHistoryStoreFile::SetBackupTime(CONST CTimeKey &tTime)
{
	m_tBackupTime = (tTime > CTime::GetCurrentTime()) ? tTime : 0;
}

BOOL CHistoryStoreFile::GetBackupTime(CTimeKey &tTime) CONST
{
	if (m_nOptions & HISTORYSTORE_OPTION_BACKUPTIME)
	{
		tTime = (m_tBackupTime > CTime::GetCurrentTime()) ? m_tBackupTime : 0;
		return((m_tBackupTime == tTime) ? TRUE : FALSE);
	}
	return FALSE;
}

VOID CHistoryStoreFile::SetBackupDailyPeriod(CONST CTimeSpan &tStartTime, CONST CTimeSpan &tStopTime)
{
	m_tBackupStartTime = (tStartTime < tStopTime) ? tStartTime : 0;
	m_tBackupStopTime = (tStartTime < tStopTime) ? tStopTime : 0;
}

BOOL CHistoryStoreFile::GetBackupDailyPeriod(CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST
{
	if (m_nOptions & HISTORYSTORE_OPTION_BACKUPDAILY)
	{
		tStartTime = m_tBackupStartTime;
		tStopTime = m_tBackupStopTime;
		return TRUE;
	}
	return FALSE;
}

VOID CHistoryStoreFile::SetBackupRetryInfo(UINT nRetries, CONST CTimeSpan &tInterval)
{
	m_nRetries[0] = m_nRetries[1] = nRetries;
	m_tBackupInterval = tInterval;
}

BOOL CHistoryStoreFile::GetBackupRetryInfo(UINT &nRetries, CTimeSpan &tInterval) CONST
{
	if (m_nOptions & HISTORYSTORE_OPTION_BACKUPRETRIES)
	{
		tInterval = m_tBackupInterval;
		nRetries = m_nRetries[0];
		return TRUE;
	}
	return FALSE;
}

VOID CHistoryStoreFile::SetBackupRetryCount(UINT nCount)
{
	m_nRetries[1] = nCount;
}

UINT CHistoryStoreFile::GetBackupRetryCount() CONST
{
	return m_nRetries[1];
}

VOID CHistoryStoreFile::SetErrorCode(UINT nCode)
{
	if ((nCode & HISTORYSTORE_SUCCESS) != HISTORYSTORE_SUCCESS || !m_bBuffering)
	{
		m_nErrorCode = nCode;
		return;
	}
}

UINT CHistoryStoreFile::GetErrorCode() CONST
{
	return m_nErrorCode;
}

UINT CHistoryStoreFile::Update(LPCTSTR pszSpacecraft, UINT nType, CONST CTMEnvironment *pTMEnvironment, BOOL bBackup)
{
	UINT  nError;
	UINT  nResult;
	BOOL  bBuffering;
	CTimeKey  tTime;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CTimeSpan  tDailyStartTime;
	CTimeSpan  tDailyStopTime;

	if ((GetOptions() & HISTORYSTORE_OPTION_USE) || (GetPeriod(tStartTime, tStopTime) && tTime >= tStartTime  &&  tTime <= tStopTime) || (GetDailyPeriod(tDailyStartTime, tDailyStopTime) && tTime.GetTime() % SECONDSPERDAY >= tDailyStartTime.GetTotalSeconds() && tTime.GetTime() % SECONDSPERDAY <= tDailyStopTime.GetTotalSeconds()))
	{
		if ((nResult = (Open(GetFileName(), pszSpacecraft, nType, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite) & HISTORYFILE_SUCCESS) ? HISTORYSTORE_SUCCESS : HISTORYSTORE_FILEOPEN_FAILURE) == HISTORYSTORE_SUCCESS)
		{
			while (!DoBackup(pTMEnvironment, bBackup))
			{
				if ((nError = Write(pTMEnvironment)) & HISTORYFILE_SUCCESS)
				{
					if ((nError & HISTORYFILE_DATA_MORE) != HISTORYFILE_DATA_MORE)
					{
						for (nError = GetErrorCode(), bBuffering = !IsBufferEmpty(); nError != nResult; )
						{
							SetErrorCode(nResult);
							break;
						}
						Close();
						return((GetOptions() & HISTORYSTORE_OPTION_AUDITFAILURES) ? MAKELONG(LOWORD((nResult^nError) & nResult), HIWORD((nResult^nError) & nResult) | ((bBuffering) ? HISTORYSTORE_DATA_BUFFERED : 0)) : MAKELONG((LOWORD(nResult) == HISTORYSTORE_SUCCESS) ? HISTORYSTORE_SUCCESS : HISTORYSTORE_FAILURE, HIWORD((nResult^nError) & nResult) | ((bBuffering) ? HISTORYSTORE_DATA_BUFFERED : 0)));
					}
					continue;
				}
				Close();
				return DoBackup(pszSpacecraft, nType, pTMEnvironment, nResult | HISTORYSTORE_FILEUPDATE_FAILURE);
			}
			for (nResult = MAKELONG(LOWORD(nResult), HIWORD(nResult) | HISTORYSTORE_BACKUP), nError = GetErrorCode(), Close(); nError != nResult; )
			{
				SetErrorCode(nResult);
				break;
			}
			return((GetOptions() & HISTORYSTORE_OPTION_AUDITFAILURES) ? ((nResult^nError) & nResult) : MAKELONG((LOWORD(nResult) == HISTORYSTORE_SUCCESS) ? HISTORYSTORE_SUCCESS : HISTORYSTORE_FAILURE, HIWORD((nResult^nError) & nResult)));
		}
		return DoBackup(pszSpacecraft, nType, pTMEnvironment, nResult);
	}
	SetErrorCode((nResult = HISTORYSTORE_SUCCESS));
	return nResult;
}
UINT CHistoryStoreFile::Update(LPCTSTR pszSpacecraft, UINT nType, CONST CTCEnvironment *pTCEnvironment, BOOL bBackup)
{
	UINT  nError;
	UINT  nResult;
	BOOL  bBuffering;
	CTimeKey  tTime;
	CTimeKey  tStartTime;
	CTimeKey  tStopTime;
	CTimeSpan  tDailyStartTime;
	CTimeSpan  tDailyStopTime;

	if ((GetOptions() & HISTORYSTORE_OPTION_USE) || (GetPeriod(tStartTime, tStopTime) && tTime >= tStartTime  &&  tTime <= tStopTime) || (GetDailyPeriod(tDailyStartTime, tDailyStopTime) && tTime.GetTime() % SECONDSPERDAY >= tDailyStartTime.GetTotalSeconds() && tTime.GetTime() % SECONDSPERDAY <= tDailyStopTime.GetTotalSeconds()))
	{
		if ((nResult = (Open(GetFileName(), pszSpacecraft, nType, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite) & HISTORYFILE_SUCCESS) ? HISTORYSTORE_SUCCESS : HISTORYSTORE_FILEOPEN_FAILURE) == HISTORYSTORE_SUCCESS)
		{
			while (!DoBackup(pTCEnvironment, bBackup))
			{
				if ((nError = Write(pTCEnvironment)) & HISTORYFILE_SUCCESS)
				{
					if ((nError & HISTORYFILE_DATA_MORE) != HISTORYFILE_DATA_MORE)
					{
						for (nError = GetErrorCode(), bBuffering = !IsBufferEmpty(); nError != nResult; )
						{
							SetErrorCode(nResult);
							break;
						}
						Close();
						return((GetOptions() & HISTORYSTORE_OPTION_AUDITFAILURES) ? MAKELONG(LOWORD((nResult^nError) & nResult), HIWORD((nResult^nError) & nResult) | ((bBuffering) ? HISTORYSTORE_DATA_BUFFERED : 0)) : MAKELONG((LOWORD(nResult) == HISTORYSTORE_SUCCESS) ? HISTORYSTORE_SUCCESS : HISTORYSTORE_FAILURE, HIWORD((nResult^nError) & nResult) | ((bBuffering) ? HISTORYSTORE_DATA_BUFFERED : 0)));
					}
					continue;
				}
				Close();
				return DoBackup(pszSpacecraft, nType, pTCEnvironment, nResult | HISTORYSTORE_FILEUPDATE_FAILURE);
			}
			for (nResult = MAKELONG(LOWORD(nResult), HIWORD(nResult) | HISTORYSTORE_BACKUP), nError = GetErrorCode(), Close(); nError != nResult; )
			{
				SetErrorCode(nResult);
				break;
			}
			return((GetOptions() & HISTORYSTORE_OPTION_AUDITFAILURES) ? ((nResult^nError) & nResult) : MAKELONG((LOWORD(nResult) == HISTORYSTORE_SUCCESS) ? HISTORYSTORE_SUCCESS : HISTORYSTORE_FAILURE, HIWORD((nResult^nError) & nResult)));
		}
		return DoBackup(pszSpacecraft, nType, pTCEnvironment, nResult);
	}
	SetErrorCode((nResult = HISTORYSTORE_SUCCESS));
	return nResult;
}
UINT CHistoryStoreFile::Update(LPCTSTR pszSpacecraft, UINT nType, BOOL bBackup, BOOL bFlush)
{
	UINT  nError;
	UINT  nResult;

	for (nResult = HISTORYSTORE_SUCCESS, nError = GetErrorCode(); !IsBufferEmpty(); )
	{
		if ((nError = Open(GetFileName(), pszSpacecraft, nType, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite, bFlush)) == HISTORYFILE_SUCCESS)
		{
			while ((nResult = (DoBackup((CONST CTMEnvironment *) NULL, bBackup)) ? MAKELONG(LOWORD(nResult), HISTORYSTORE_BACKUP) : nResult) == HISTORYSTORE_SUCCESS)
			{
				if (((nError = Write((CONST CTMEnvironment *) NULL)) & HISTORYFILE_SUCCESS) && (nError & HISTORYFILE_DATA_MORE)) continue;
				break;
			}
			if ((LOWORD(nResult) & HISTORYSTORE_SUCCESS) && (HIWORD(nResult) & HISTORYSTORE_BACKUP))
			{
				for (nError = GetErrorCode(); nError != nResult; )
				{
					SetErrorCode(nResult);
					break;
				}
				Close();
				return((GetOptions() & HISTORYSTORE_OPTION_AUDITFAILURES) ? ((nResult^nError) & nResult) : MAKELONG((LOWORD(nResult) == HISTORYSTORE_SUCCESS) ? HISTORYSTORE_SUCCESS : HISTORYSTORE_FAILURE, HIWORD((nResult^nError) & nResult)));
			}
		}
		for (; nError & HISTORYFILE_SUCCESS; )
		{
			Close();
			break;
		}
		for (nResult = (nError & HISTORYFILE_SUCCESS) ? ((nError & HISTORYFILE_BUFFERING) ? MAKELONG(LOWORD(nResult), HIWORD(nResult) | HISTORYSTORE_DATA_BUFFERED) : nResult) : MAKELONG((nError & HISTORYFILE_OPEN_FAILURE) ? HISTORYSTORE_FILEOPEN_FAILURE : HISTORYSTORE_FILEUPDATE_FAILURE, HIWORD(nResult)), nError = GetErrorCode(); nError != nResult; )
		{
			SetErrorCode(nResult);
			break;
		}
		break;
	}
	if (!m_cBackupFile.IsBufferEmpty())
	{
		if ((nError = m_cBackupFile.Open(GetSecondaryFileName(), pszSpacecraft, nType, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite)) == HISTORYFILE_SUCCESS)
		{
			while ((nError = m_cBackupFile.Write((CONST CTMEnvironment *) NULL)) & HISTORYFILE_SUCCESS)
			{
				if (nError & HISTORYFILE_DATA_MORE) continue;
				break;
			}
		}
		for (; nError & HISTORYFILE_SUCCESS; )
		{
			m_cBackupFile.Close();
			break;
		}
		for (nResult = (nError & HISTORYFILE_SUCCESS) ? ((nError & HISTORYFILE_BUFFERING) ? MAKELONG(LOWORD(nResult), HIWORD(nResult) | HISTORYSTORE_DATA_BUFFERED) : nResult) : MAKELONG((nError & HISTORYFILE_OPEN_FAILURE) ? HISTORYSTORE_FILEOPEN_FAILURE : HISTORYSTORE_FILEUPDATE_FAILURE, HIWORD(nResult)), nError = GetErrorCode(); nError != nResult; )
		{
			SetErrorCode(nResult);
			break;
		}
	}
	return((GetOptions() & HISTORYSTORE_OPTION_AUDITFAILURES) ? MAKELONG(LOWORD((nResult^nError) & nResult), HIWORD((nResult^nError) & nResult)) : MAKELONG((LOWORD(nResult) == HISTORYSTORE_SUCCESS) ? HISTORYSTORE_SUCCESS : HISTORYSTORE_FAILURE, HIWORD((nResult^nError) & nResult)));
}

UINT CHistoryStoreFile::DoBackup(LPCTSTR pszSpacecraft, UINT nType, CONST CTMEnvironment *pTMEnvironment, UINT nCode)
{
	UINT  nError;
	UINT  nResult;
	BOOL  bBuffering;

	if ((nResult = nCode) != HISTORYSTORE_SUCCESS)
	{
		if (GetOptions() & HISTORYSTORE_OPTION_SECONDARY)
		{
			if (((nError = m_cBackupFile.Open(GetSecondaryFileName(), pszSpacecraft, nType, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite)) == HISTORYFILE_SUCCESS  &&  m_cBackupFile.SetMode((GetOptions() & HISTORYSTORE_OPTION_CYCLIC) ? LOGFILE_POLICY_CYCLICMODE : LOGFILE_POLICY_NONCYCLICMODE) && m_cBackupFile.SetUpdateInterval((GetOptions() & HISTORYSTORE_OPTION_FULLUPDATES) ? GetUpdateInterval() : 0) && m_cBackupFile.SetRetentionBySize((GetOptions() & HISTORYSTORE_OPTION_LIMITEDSIZE) ? GetFileSize() : 0) && m_cBackupFile.Compress((GetOptions() & HISTORYSTORE_OPTION_COMPRESSION) ? TRUE : FALSE) && (!m_cBackupFile.IsEmpty() || m_cBackupFile.Reset())) || (nError & HISTORYFILE_SUCCESS))
			{
				while ((nError = m_cBackupFile.Write(pTMEnvironment)) & HISTORYFILE_SUCCESS)
				{
					if ((nError & HISTORYFILE_DATA_MORE) != HISTORYFILE_DATA_MORE) break;
					continue;
				}
				for (nResult = MAKELONG(LOWORD(nResult), HIWORD(nResult) | HISTORYSTORE_SECONDARY_USE), nError = GetErrorCode(), bBuffering = !IsBufferEmpty(); nError != nResult; )
				{
					SetErrorCode(nResult);
					break;
				}
				m_cBackupFile.Close();
				return((GetOptions() & HISTORYSTORE_OPTION_AUDITFAILURES) ? MAKELONG(LOWORD((nResult^nError) & nResult), HIWORD((nResult^nError) & nResult) | ((bBuffering) ? HISTORYSTORE_DATA_BUFFERED : 0)) : MAKELONG((LOWORD(nResult) == HISTORYSTORE_SUCCESS) ? HISTORYSTORE_SUCCESS : HISTORYSTORE_FAILURE, HIWORD((nResult^nError) & nResult) | ((bBuffering) ? HISTORYSTORE_DATA_BUFFERED : 0)));
			}
			nError = GetErrorCode();
			SetErrorCode((nResult = nResult | MAKELONG(HISTORYSTORE_SECONDARY_FAILURE, HISTORYSTORE_DATA_LOST)));
			return((GetOptions() & HISTORYSTORE_OPTION_AUDITFAILURES) ? ((nResult^nError) & nResult) : MAKELONG((LOWORD(nResult) == HISTORYSTORE_SUCCESS) ? HISTORYSTORE_SUCCESS : HISTORYSTORE_FAILURE, HIWORD((nResult^nError) & nResult)));
		}
		nResult |= MAKELONG(0, HISTORYSTORE_DATA_LOST);
	}
	for (nError = GetErrorCode(); nError != nResult; )
	{
		SetErrorCode(nResult);
		break;
	}
	return((GetOptions() & HISTORYSTORE_OPTION_AUDITFAILURES) ? ((nResult^nError) & nResult) : (LOWORD(nResult) == HISTORYSTORE_SUCCESS) ? MAKELONG(HISTORYSTORE_SUCCESS, HIWORD((nResult^nError) & nResult)) : MAKELONG(HISTORYSTORE_FAILURE, HIWORD((nResult^nError) & nResult)));
}
UINT CHistoryStoreFile::DoBackup(LPCTSTR pszSpacecraft, UINT nType, CONST CTCEnvironment *pTCEnvironment, UINT nCode)
{
	UINT  nError;
	UINT  nResult;
	BOOL  bBuffering;

	if ((nResult = nCode) != HISTORYSTORE_SUCCESS)
	{
		if (GetOptions() & HISTORYSTORE_OPTION_SECONDARY)
		{
			if (((nError = m_cBackupFile.Open(GetSecondaryFileName(), pszSpacecraft, nType, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite)) == HISTORYFILE_SUCCESS  &&  m_cBackupFile.SetMode((GetOptions() & HISTORYSTORE_OPTION_CYCLIC) ? LOGFILE_POLICY_CYCLICMODE : LOGFILE_POLICY_NONCYCLICMODE) && m_cBackupFile.SetUpdateInterval((GetOptions() & HISTORYSTORE_OPTION_FULLUPDATES) ? GetUpdateInterval() : 0) && m_cBackupFile.SetRetentionBySize((GetOptions() & HISTORYSTORE_OPTION_LIMITEDSIZE) ? GetFileSize() : 0) && m_cBackupFile.Compress((GetOptions() & HISTORYSTORE_OPTION_COMPRESSION) ? TRUE : FALSE) && (!m_cBackupFile.IsEmpty() || m_cBackupFile.Reset())) || (nError & HISTORYFILE_SUCCESS))
			{
				while ((nError = m_cBackupFile.Write(pTCEnvironment)) & HISTORYFILE_SUCCESS)
				{
					if ((nError & HISTORYFILE_DATA_MORE) != HISTORYFILE_DATA_MORE) break;
					continue;
				}
				for (nResult = MAKELONG(LOWORD(nResult), HIWORD(nResult) | HISTORYSTORE_SECONDARY_USE), nError = GetErrorCode(), bBuffering = !IsBufferEmpty(); nError != nResult; )
				{
					SetErrorCode(nResult);
					break;
				}
				m_cBackupFile.Close();
				return((GetOptions() & HISTORYSTORE_OPTION_AUDITFAILURES) ? MAKELONG(LOWORD((nResult^nError) & nResult), HIWORD((nResult^nError) & nResult) | ((bBuffering) ? HISTORYSTORE_DATA_BUFFERED : 0)) : MAKELONG((LOWORD(nResult) == HISTORYSTORE_SUCCESS) ? HISTORYSTORE_SUCCESS : HISTORYSTORE_FAILURE, HIWORD((nResult^nError) & nResult) | ((bBuffering) ? HISTORYSTORE_DATA_BUFFERED : 0)));
			}
			nError = GetErrorCode();
			SetErrorCode((nResult = nResult | MAKELONG(HISTORYSTORE_SECONDARY_FAILURE, HISTORYSTORE_DATA_LOST)));
			return((GetOptions() & HISTORYSTORE_OPTION_AUDITFAILURES) ? ((nResult^nError) & nResult) : MAKELONG((LOWORD(nResult) == HISTORYSTORE_SUCCESS) ? HISTORYSTORE_SUCCESS : HISTORYSTORE_FAILURE, HIWORD((nResult^nError) & nResult)));
		}
		nResult |= MAKELONG(0, HISTORYSTORE_DATA_LOST);
	}
	for (nError = GetErrorCode(); nError != nResult; )
	{
		SetErrorCode(nResult);
		break;
	}
	return((GetOptions() & HISTORYSTORE_OPTION_AUDITFAILURES) ? ((nResult^nError) & nResult) : (LOWORD(nResult) == HISTORYSTORE_SUCCESS) ? MAKELONG(HISTORYSTORE_SUCCESS, HIWORD((nResult^nError) & nResult)) : MAKELONG(HISTORYSTORE_FAILURE, HIWORD((nResult^nError) & nResult)));
}
BOOL CHistoryStoreFile::DoBackup(CONST CTMEnvironment *pTMEnvironment, BOOL bCheck) CONST
{
	return(((GetOptions() & HISTORYSTORE_OPTION_BACKUP) && bCheck) ? ((((GetOptions() & HISTORYSTORE_OPTION_BACKUPBYDEFAULT) && CHistoryFile::DoBackup(pTMEnvironment, GetFileSize())) || ((GetOptions() & HISTORYSTORE_OPTION_BACKUPBYSIZE) && CHistoryFile::DoBackup(pTMEnvironment, GetBackupSize()))) ? TRUE : FALSE) : FALSE);
}
BOOL CHistoryStoreFile::DoBackup(CONST CTCEnvironment *pTCEnvironment, BOOL bCheck) CONST
{
	return(((GetOptions() & HISTORYSTORE_OPTION_BACKUP) && bCheck) ? ((((GetOptions() & HISTORYSTORE_OPTION_BACKUPBYDEFAULT) && CHistoryFile::DoBackup(pTCEnvironment, GetFileSize())) || ((GetOptions() & HISTORYSTORE_OPTION_BACKUPBYSIZE) && CHistoryFile::DoBackup(pTCEnvironment, GetBackupSize()))) ? TRUE : FALSE) : FALSE);
}

VOID CHistoryStoreFile::Copy(CONST CHistoryStoreFile *pFile)
{
	m_nOptions = pFile->m_nOptions;
	m_wUpdates = pFile->m_wUpdates;
	m_szName[0] = pFile->m_szName[0];
	m_szName[1] = pFile->m_szName[1];
	m_szTempName = pFile->m_szTempName;
	m_szDirectory = pFile->m_szDirectory;
	m_nRetries[0] = pFile->m_nRetries[0];
	m_nRetries[1] = pFile->m_nRetries[1];
	m_nErrorCode = pFile->m_nErrorCode;
	m_tStartTime = pFile->m_tStartTime;
	m_tStopTime = pFile->m_tStopTime;
	m_tBackupTime = pFile->m_tBackupTime;
	m_tBackupStartTime = pFile->m_tBackupStartTime;
	m_tBackupStopTime = pFile->m_tBackupStopTime;
	m_tBackupInterval = pFile->m_tBackupInterval;
	m_tDailyStartTime = pFile->m_tDailyStartTime;
	m_tDailyStopTime = pFile->m_tDailyStopTime;
	m_dwFileSize = pFile->m_dwFileSize;
	m_dwBackupSize = pFile->m_dwBackupSize;
}

BOOL CHistoryStoreFile::Compare(CONST CHistoryStoreFile *pFile) CONST
{
	return((pFile->m_nOptions == m_nOptions  &&  !pFile->m_szName[0].CompareNoCase(m_szName[0]) && !pFile->m_szDirectory.CompareNoCase(m_szDirectory) && (!(m_nOptions & HISTORYSTORE_OPTION_SECONDARY) || !pFile->m_szName[1].CompareNoCase(m_szName[1])) && (!(m_nOptions & HISTORYSTORE_OPTION_BACKUP) || (!pFile->m_szTempName.CompareNoCase(m_szTempName) && (!(m_nOptions & HISTORYSTORE_OPTION_BACKUPBYSIZE) || pFile->m_dwBackupSize == m_dwBackupSize) && (!(m_nOptions & HISTORYSTORE_OPTION_BACKUPDAILY) || (pFile->m_tBackupStartTime == m_tBackupStartTime  &&  pFile->m_tBackupStopTime == m_tBackupStopTime)) && (!(m_nOptions & HISTORYSTORE_OPTION_BACKUPTIME) || pFile->m_tBackupTime == m_tBackupTime) && (!(m_nOptions & HISTORYSTORE_OPTION_BACKUPRETRIES) || (pFile->m_nRetries[0] == m_nRetries[0] && pFile->m_nRetries[1] == m_nRetries[1] && pFile->m_tBackupInterval == m_tBackupInterval)))) && (!(m_nOptions & HISTORYSTORE_OPTION_LIMITEDUSE) || (pFile->m_tStartTime == m_tStartTime  &&  pFile->m_tStopTime == m_tStopTime)) && (!(m_nOptions & HISTORYSTORE_OPTION_DAILYUSE) || (pFile->m_tDailyStartTime == m_tDailyStartTime  &&  pFile->m_tDailyStopTime == m_tDailyStopTime)) && (!(m_nOptions & HISTORYSTORE_OPTION_LIMITEDSIZE) || pFile->m_dwFileSize == m_dwFileSize) && (!(m_nOptions & HISTORYSTORE_OPTION_FULLUPDATES) || pFile->m_wUpdates == m_wUpdates) && pFile->m_nErrorCode == m_nErrorCode) ? TRUE : FALSE);
}

BOOL CHistoryStoreFile::Map(CByteArray &nInfo) CONST
{
	INT  cbData;
	DATA  sData;

	sData.cbName[0] = (m_szName[0].GetLength() + 1)*sizeof(TCHAR);
	sData.cbName[1] = (m_szName[1].GetLength() + 1)*sizeof(TCHAR);
	sData.cbTempName = (m_szTempName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbDirectory = (m_szDirectory.GetLength() + 1)*sizeof(TCHAR);
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbName[0] + sData.cbName[1] + sData.cbTempName + sData.cbDirectory)), sData.nOptions = m_nOptions, sData.wUpdates = m_wUpdates, sData.nRetries[0] = m_nRetries[0], sData.nRetries[1] = m_nRetries[1], sData.dwFileSize = m_dwFileSize, sData.dwBackupSize = m_dwBackupSize, sData.tStartTime[0] = m_tStartTime.GetTime(), sData.tStopTime[0] = m_tStopTime.GetTime(), sData.tStartTime[1] = m_tDailyStartTime.GetTotalSeconds(), sData.tStopTime[1] = m_tDailyStopTime.GetTotalSeconds(), sData.tBackupTime = m_tBackupTime.GetTime(), sData.tBackupInterval = m_tBackupInterval.GetTotalSeconds(), sData.tBackupStartTime = m_tBackupStartTime.GetTotalSeconds(), sData.tBackupStopTime = m_tBackupStopTime.GetTotalSeconds(); nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szName[0], sData.cbName[0]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbName[0]), (LPCTSTR)m_szName[1], sData.cbName[1]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbName[1]), (LPCTSTR)m_szTempName, sData.cbTempName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbTempName), (LPCTSTR)m_szDirectory, sData.cbDirectory);
		return TRUE;
	}
	return FALSE;
}

BOOL CHistoryStoreFile::Unmap(CONST CByteArray &nInfo)
{
	INT  cbData;
	DATA  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbName[0] + sData.cbName[1] + sData.cbTempName + sData.cbDirectory && sData.cbName[0] > 0 && sData.cbName[1] > 0 && sData.cbTempName > 0 && sData.cbDirectory > 0; )
	{
		CopyMemory(m_szName[0].GetBufferSetLength(STRINGCHARS(sData.cbName[0])), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbName[0]));
		CopyMemory(m_szName[1].GetBufferSetLength(STRINGCHARS(sData.cbName[1])), nInfo.GetData() + (cbData = cbData + sData.cbName[0]), STRINGBYTES(sData.cbName[1]));
		CopyMemory(m_szTempName.GetBufferSetLength(STRINGCHARS(sData.cbTempName)), nInfo.GetData() + (cbData = cbData + sData.cbName[1]), STRINGBYTES(sData.cbTempName));
		CopyMemory(m_szDirectory.GetBufferSetLength(STRINGCHARS(sData.cbDirectory)), nInfo.GetData() + (cbData = cbData + sData.cbTempName), STRINGBYTES(sData.cbDirectory));
		m_nOptions = sData.nOptions;
		m_wUpdates = sData.wUpdates;
		m_nRetries[0] = sData.nRetries[0];
		m_nRetries[1] = sData.nRetries[1];
		m_dwFileSize = sData.dwFileSize;
		m_dwBackupSize = sData.dwBackupSize;
		m_tStartTime = sData.tStartTime[0];
		m_tStopTime = sData.tStopTime[0];
		m_tDailyStartTime = sData.tStartTime[1];
		m_tDailyStopTime = sData.tStopTime[1];
		m_tBackupTime = sData.tBackupTime;
		m_tBackupInterval = sData.tBackupInterval;
		m_tBackupStartTime = sData.tBackupStartTime;
		m_tBackupStopTime = sData.tBackupStopTime;
		m_szName[0].ReleaseBuffer();
		m_szName[1].ReleaseBuffer();
		m_szTempName.ReleaseBuffer();
		m_szDirectory.ReleaseBuffer();
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CHistoryStoreFiles

CHistoryStoreFiles::CHistoryStoreFiles() : CPtrArray()
{
	return;
}

CHistoryStoreFiles::~CHistoryStoreFiles()
{
	RemoveAll();
}

INT CHistoryStoreFiles::Add(CHistoryStoreFile *pFile)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pFile->GetFileName(), TRUE)) >= 0) InsertAt(nIndex, pFile, 1);
	return nIndex;
}

INT CHistoryStoreFiles::Find(LPCTSTR pszFileName) CONST
{
	return FindIndex(pszFileName);
}

CHistoryStoreFile *CHistoryStoreFiles::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CHistoryStoreFile *)CPtrArray::GetAt(nIndex) : (CHistoryStoreFile *)NULL);
}

CHistoryStoreFile *CHistoryStoreFiles::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CHistoryStoreFile *)CPtrArray::GetAt(nIndex) : (CHistoryStoreFile *)NULL);
}

VOID CHistoryStoreFiles::RemoveAll()
{
	INT  nFile;
	INT  nFiles;

	for (nFile = 0, nFiles = (INT)GetSize(); nFile < nFiles; nFile++)
	{
		delete GetAt(nFile);
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CHistoryStoreFiles::Copy(CONST CHistoryStoreFiles *pFiles)
{
	INT  nFile;
	INT  nFiles;
	CHistoryStoreFile  *pFile;

	for (nFile = 0, nFiles = (INT)pFiles->GetSize(), RemoveAll(); nFile < nFiles; nFile++)
	{
		if ((pFile = new CHistoryStoreFile))
		{
			pFile->Copy(pFiles->GetAt(nFile));
			InsertAt(GetSize(), pFile, 1);
			continue;
		}
		break;
	}
	return((nFile == nFiles) ? TRUE : FALSE);
}

BOOL CHistoryStoreFiles::Compare(CONST CHistoryStoreFiles *pFiles) CONST
{
	INT  nFile[2];
	INT  nFiles[2];

	for (nFile[0] = 0, nFiles[0] = (pFiles->GetSize() == GetSize()) ? (INT)GetSize() : -1; nFile[0] < nFiles[0]; nFile[0]++)
	{
		for (nFile[1] = 0, nFiles[1] = nFiles[0]; nFile[1] < nFiles[1]; nFile[1]++)
		{
			if (pFiles->GetAt(nFile[0])->Compare(GetAt(nFile[1]))) break;
			continue;
		}
		if (nFile[1] == nFiles[1]) break;
	}
	return((nFile[0] == nFiles[0]) ? TRUE : FALSE);
}

BOOL CHistoryStoreFiles::Map(CByteArray &nInfo) CONST
{
	INT  nFile;
	INT  nFiles;
	CByteArray  nFileData;
	CHistoryStoreFile  *pFile;

	for (nFile = 0, nFiles = (INT)GetSize(), nInfo.RemoveAll(); nFile < nFiles; nFile++)
	{
		if ((pFile = GetAt(nFile)) && pFile->Map(nFileData) && nInfo.Append(nFileData) >= 0) continue;
		break;
	}
	return((nFile == nFiles) ? TRUE : FALSE);
}

BOOL CHistoryStoreFiles::Unmap(CONST CByteArray &nInfo)
{
	INT  cbFile;
	INT  cbFiles;
	CByteArray  nFileData;
	CHistoryStoreFile  *pFile;

	for (cbFiles = 0, RemoveAll(); cbFiles < nInfo.GetSize(); cbFiles += cbFile)
	{
		for (CopyMemory(&cbFile, nInfo.GetData() + cbFiles, sizeof(cbFile)), nFileData.SetSize(max(min(cbFile, nInfo.GetSize() - cbFiles), 0)); nFileData.GetSize() >= 0; )
		{
			CopyMemory(nFileData.GetData(), nInfo.GetData() + cbFiles, nFileData.GetSize());
			break;
		}
		if ((pFile = new CHistoryStoreFile))
		{
			if (pFile->Unmap(nFileData) && Add(pFile) >= 0) continue;
			delete pFile;
		}
		break;
	}
	return((cbFiles == nInfo.GetSize()) ? TRUE : FALSE);
}

INT CHistoryStoreFiles::FindIndex(LPCTSTR pszFileName, BOOL bInsert) CONST
{
	INT  nIndex;
	CHistoryStoreFile  *pFile;

	for (nIndex = (bInsert) ? (INT)GetSize() : 0; nIndex < GetSize(); nIndex++)
	{
		if ((pFile = GetAt(nIndex)) && pFile->GetFileName() == pszFileName) break;
		continue;
	}
	return(((!bInsert  &&  nIndex < GetSize()) || (bInsert  &&  nIndex == GetSize())) ? nIndex : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CHistoryStoreOptionInfo

CHistoryStoreOptionInfo::CHistoryStoreOptionInfo() : CObject()
{
	m_nType = HISTORYSTOREOPTION_TYPE_NONE;
	m_szTag.Empty();
	m_tRetention = 0;
}

VOID CHistoryStoreOptionInfo::SetType(UINT nType)
{
	m_nType = nType;
}

UINT CHistoryStoreOptionInfo::GetType() CONST
{
	return m_nType;
}

VOID CHistoryStoreOptionInfo::SetTag(LPCTSTR pszTag)
{
	m_szTag = pszTag;
}

CString CHistoryStoreOptionInfo::GetTag() CONST
{
	return m_szTag;
}

VOID CHistoryStoreOptionInfo::SetRetention(CONST CTimeSpan &tRetention)
{
	m_tRetention = tRetention;
}

CTimeSpan CHistoryStoreOptionInfo::GetRetention() CONST
{
	return m_tRetention;
}

VOID CHistoryStoreOptionInfo::Copy(CONST CHistoryStoreOptionInfo *pOption)
{
	m_nType = pOption->m_nType;
	m_szTag = pOption->m_szTag;
	m_tRetention = pOption->m_tRetention;
}

BOOL CHistoryStoreOptionInfo::Compare(CONST CHistoryStoreOptionInfo *pOption) CONST
{
	return((pOption->m_nType == m_nType  &&  pOption->m_szTag == m_szTag  &&  pOption->m_tRetention == m_tRetention) ? TRUE : FALSE);
}

BOOL CHistoryStoreOptionInfo::Map(CByteArray &nInfo) CONST
{
	DATA  sData;

	sData.cbTag = (m_szTag.GetLength() + 1)*sizeof(TCHAR);
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbTag)), sData.nType = m_nType, sData.tRetention = m_tRetention.GetTotalSeconds(); nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + sizeof(DATA), (LPCTSTR)m_szTag, sData.cbTag);
		return TRUE;
	}
	return FALSE;
}

BOOL CHistoryStoreOptionInfo::Unmap(CONST CByteArray &nInfo)
{
	DATA  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbTag && sData.cbTag > 0; )
	{
		CopyMemory(m_szTag.GetBufferSetLength(STRINGCHARS(sData.cbTag)), nInfo.GetData() + sizeof(DATA), STRINGBYTES(sData.cbTag));
		m_nType = sData.nType;
		m_tRetention = sData.tRetention;
		m_szTag.ReleaseBuffer();
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CHistoryStoreOptions

CHistoryStoreOptions::CHistoryStoreOptions() : CPtrArray()
{
	return;
}

CHistoryStoreOptions::~CHistoryStoreOptions()
{
	RemoveAll();
}

INT CHistoryStoreOptions::Add(CHistoryStoreOptionInfo *pOption)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pOption->GetType(), pOption->GetTag(), TRUE)) >= 0) InsertAt(nIndex, pOption, 1);
	return nIndex;
}

INT CHistoryStoreOptions::Find(UINT nType, LPCTSTR pszTag) CONST
{
	return FindIndex(nType, pszTag);
}

CHistoryStoreOptionInfo *CHistoryStoreOptions::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CHistoryStoreOptionInfo *)CPtrArray::GetAt(nIndex) : (CHistoryStoreOptionInfo *)NULL);
}

CHistoryStoreOptionInfo *CHistoryStoreOptions::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CHistoryStoreOptionInfo *)CPtrArray::GetAt(nIndex) : (CHistoryStoreOptionInfo *)NULL);
}

VOID CHistoryStoreOptions::RemoveAll()
{
	INT  nOption;
	INT  nOptions;

	for (nOption = 0, nOptions = (INT)GetSize(); nOption < nOptions; nOption++)
	{
		delete GetAt(nOption);
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CHistoryStoreOptions::Copy(CONST CHistoryStoreOptions *pOptions)
{
	INT  nOption;
	INT  nOptions;
	CHistoryStoreOptionInfo  *pOptionInfo;

	for (nOption = 0, nOptions = (INT)pOptions->GetSize(), RemoveAll(); nOption < nOptions; nOption++)
	{
		if ((pOptionInfo = new CHistoryStoreOptionInfo))
		{
			pOptionInfo->Copy(pOptions->GetAt(nOption));
			InsertAt(nOption, pOptionInfo, 1);
			continue;
		}
		break;
	}
	return((nOption == nOptions) ? TRUE : FALSE);
}

BOOL CHistoryStoreOptions::Compare(CONST CHistoryStoreOptions *pOptions) CONST
{
	INT  nOption;
	INT  nOptions;

	for (nOption = 0, nOptions = (pOptions->GetSize() == GetSize()) ? (INT)GetSize() : -1; nOption < nOptions; nOption++)
	{
		if (!pOptions->GetAt(nOption)->Compare(GetAt(nOption))) break;
		continue;
	}
	return((nOption == nOptions) ? TRUE : FALSE);
}

BOOL CHistoryStoreOptions::Map(CByteArray &nInfo) CONST
{
	INT  nOption;
	INT  nOptions;
	CByteArray  nOptionData;
	CHistoryStoreOptionInfo  *pOptionInfo;

	for (nOption = 0, nOptions = (INT)GetSize(), nInfo.RemoveAll(); nOption < nOptions; nOption++)
	{
		if ((pOptionInfo = GetAt(nOption)) && pOptionInfo->Map(nOptionData) && nInfo.Append(nOptionData) >= 0) continue;
		break;
	}
	return((nOption == nOptions) ? TRUE : FALSE);
}

BOOL CHistoryStoreOptions::Unmap(CONST CByteArray &nInfo)
{
	INT  cbOption;
	INT  cbOptions;
	CByteArray  nOptionData;
	CHistoryStoreOptionInfo  *pOptionInfo;

	for (cbOptions = 0, RemoveAll(); cbOptions < nInfo.GetSize(); cbOptions += cbOption)
	{
		for (CopyMemory(&cbOption, nInfo.GetData() + cbOptions, sizeof(cbOption)), nOptionData.SetSize(max(min(cbOption, nInfo.GetSize() - cbOptions), 0)); nOptionData.GetSize() >= 0; )
		{
			CopyMemory(nOptionData.GetData(), nInfo.GetData() + cbOptions, nOptionData.GetSize());
			break;
		}
		if ((pOptionInfo = new CHistoryStoreOptionInfo))
		{
			if (pOptionInfo->Unmap(nOptionData) && Add(pOptionInfo) >= 0) continue;
			delete pOptionInfo;
		}
		break;
	}
	return((cbOptions == nInfo.GetSize()) ? TRUE : FALSE);
}

INT CHistoryStoreOptions::FindIndex(UINT nType, LPCTSTR pszTag, BOOL bInsert) CONST
{
	INT  nOption;
	INT  nOptions;
	CHistoryStoreOptionInfo  *pOptionInfo;

	for (nOption = 0, nOptions = (INT)GetSize(); nOption < nOptions; nOption++)
	{
		if ((pOptionInfo = GetAt(nOption)) && pOptionInfo->GetType() == nType  &&  pOptionInfo->GetTag() == pszTag) break;
		continue;
	}
	return(((!bInsert  &&  nOption < nOptions) || (bInsert  &&  nOption == nOptions)) ? nOption : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CHistoryStore

CHistoryStore::CHistoryStore() : CObject()
{
	m_pCriticalSection = new CCriticalSection;
}

CHistoryStore::~CHistoryStore()
{
	Close();
	delete m_pCriticalSection;
}

BOOL CHistoryStore::Open(LPCTSTR pszSpacecraft, UINT nType)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (m_szSpacecraft == pszSpacecraft || m_szSpacecraft.IsEmpty())
	{
		if (lstrlen(m_szSpacecraft = pszSpacecraft))
		{
			m_nType = nType;
			return TRUE;
		}
	}
	return FALSE;
}

VOID CHistoryStore::Close()
{
	INT  nFile;
	INT  nFiles;
	CHistoryStoreFile  *pFile;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nFile = 0, nFiles = (INT)m_pFiles[HISTORYFILE_TYPE_ARCHIVE].GetSize(); nFile < nFiles; nFile++)
	{
		if ((pFile = m_pFiles[HISTORYFILE_TYPE_ARCHIVE].GetAt(nFile)))
		{
			pFile->Update(m_szSpacecraft, TRUE, TRUE);
			continue;
		}
	}
	m_nType = 0;
	m_szSpacecraft.Empty();
	m_szDefaultFiles[0].Empty();
	m_szDefaultFiles[1].Empty();
	m_pFiles[0].RemoveAll();
	m_pFiles[1].RemoveAll();
	m_nBrowseOptions.RemoveAll();
	m_szBrowseDirectories.RemoveAll();
	m_pOptions.RemoveAll();
}

BOOL CHistoryStore::SetHistoryFiles(UINT nType, CONST CHistoryStoreFiles &pFiles)
{
	INT  nFile;
	INT  nFiles;
	CHistoryStoreFile  *pFile;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (nType == HISTORYFILE_TYPE_ARCHIVE || nType == HISTORYFILE_TYPE_RETRIEVE)
	{
		for (nFile = 0, nFiles = (INT)pFiles.GetSize(); nFile < nFiles; nFile++)
		{
			if ((pFile = m_pFiles[nType].GetAt(m_pFiles[nType].Find(pFiles.GetAt(nFile)->GetFileName()))))
			{
				pFile->Copy(pFiles.GetAt(nFile));
				continue;
			}
			if ((pFile = new CHistoryStoreFile))
			{
				pFile->Copy(pFiles.GetAt(nFile));
				if (m_pFiles[nType].Add(pFile) < 0) delete pFile;
				continue;
			}
		}
		for (nFile = 0, nFiles = (m_pFiles[nType].GetSize() > pFiles.GetSize()) ? (INT)m_pFiles[nType].GetSize() : 0; nFile < nFiles; nFile++)
		{
			if ((pFile = pFiles.GetAt(pFiles.Find(m_pFiles[nType].GetAt(nFile)->GetFileName())))) continue;
			delete m_pFiles[nType].GetAt(nFile);
			m_pFiles[nType].RemoveAt(nFile);
			nFiles--;
			nFile--;
		}
		if (m_pFiles[nType].GetSize() == pFiles.GetSize())
		{
			m_szDefaultFiles[nType] = (m_pFiles[nType].Find(m_szDefaultFiles[nType]) >= 0) ? (LPCTSTR)m_szDefaultFiles[nType] : EMPTYSTRING;
			return TRUE;
		}
	}
	return FALSE;
}

INT CHistoryStore::GetHistoryFiles(UINT nType, CHistoryStoreFiles &pFiles) CONST
{
	INT  nPos;
	INT  nFile;
	INT  nFiles;
	INT  nOption;
	INT  nOptions;
	BOOL  bFileFind;
	CString  szFileName;
	CString  szDirectory;
	CString  szDirectories;
	CFileFindEx  cFileFind;
	CHistoryStoreFile  *pFile;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (nType == HISTORYFILE_TYPE_ARCHIVE || nType == HISTORYFILE_TYPE_RETRIEVE)
	{
		for (nFile = 0, nFiles = (pFiles.Copy(&m_pFiles[nType])) ? ((nType == HISTORYFILE_TYPE_RETRIEVE) ? (INT)pFiles.GetSize() : 0) : 0; nFile < nFiles; nFile++)
		{
			if ((pFile = pFiles.GetAt(nFile)) && cFileFind.FindFile(pFile->GetFileName()))
			{
				cFileFind.Close();
				continue;
			}
			delete pFile;
			pFiles.RemoveAt(nFile);
			nFiles--;
			nFile--;
		}
		for (nOption = 0, nOptions = (nType == HISTORYFILE_TYPE_RETRIEVE) ? (INT)m_nBrowseOptions.GetSize() : 0; nOption < nOptions; nOption++)
		{
			for (szDirectories = m_szBrowseDirectories.GetAt(nOption); szDirectories.GetLength() > 0; )
			{
				if ((nPos = szDirectories.Find(STRING(IDS_DIRECTORY_SEPARATOR_DEFAULT))) >= 0)
				{
					szDirectory = szDirectories.Left(nPos);
					szDirectories = szDirectories.Mid(nPos);
				}
				else
				{
					if ((nPos = szDirectories.Find(STRING(IDS_DIRECTORY_SEPARATOR_SPECIAL))) >= 0)
					{
						szDirectory = szDirectories.Left(nPos);
						szDirectories = szDirectories.Mid(nPos);
					}
					else
					{
						szDirectory = szDirectories;
						szDirectories.Empty();
					}
				}
				szFileName = (szDirectory.GetAt(szDirectory.GetLength() - 1) == STRINGCHAR(IDS_FILENAME_ALL)) ? szDirectory.Left(szDirectory.GetLength() - 1) : szDirectory;
				szFileName += STRING(IDS_FILENAME_ALL);
				if (cFileFind.FindFile(szFileName))
				{
					do
					{
						bFileFind = cFileFind.FindNextFile();
						if ((pFile = (!cFileFind.IsDots() && !cFileFind.IsHidden()) ? new CHistoryStoreFile : (CHistoryStoreFile *)NULL))
						{
							if (CheckHistoryFile(cFileFind.GetFilePath(), m_nBrowseOptions.GetAt(nOption), pFile))
							{
								if (pFiles.Find(cFileFind.GetFilePath()) < 0)
								{
									if (pFiles.Add(pFile) < 0) delete pFile;
									continue;
								}
							}
							delete pFile;
						}
					} while (bFileFind);
				}
				if (szDirectories.GetLength() > 0)
				{
					if (szDirectories.Left(lstrlen(STRING(IDS_DIRECTORY_SEPARATOR_DEFAULT))) == STRING(IDS_DIRECTORY_SEPARATOR_DEFAULT))
					{
						szDirectories = szDirectories.Mid(lstrlen(STRING(IDS_DIRECTORY_SEPARATOR_DEFAULT)));
						continue;
					}
					if (szDirectories.Left(lstrlen(STRING(IDS_DIRECTORY_SEPARATOR_SPECIAL))) == STRING(IDS_DIRECTORY_SEPARATOR_SPECIAL))
					{
						szDirectories = szDirectories.Mid(lstrlen(STRING(IDS_DIRECTORY_SEPARATOR_SPECIAL)));
						continue;
					}
					break;
				}
			}
		}
		return((INT)pFiles.GetSize());
	}
	return 0;
}

BOOL CHistoryStore::SetDefaultHistoryFile(UINT nType, CONST CHistoryStoreFile &cFile)
{
	CHistoryStoreFile  *pFile;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (nType == HISTORYFILE_TYPE_ARCHIVE || nType == HISTORYFILE_TYPE_RETRIEVE)
	{
		if ((pFile = m_pFiles[nType].GetAt(m_pFiles[nType].Find(cFile.GetFileName()))))
		{
			m_szDefaultFiles[nType] = cFile.GetFileName();
			pFile->Copy(&cFile);
			return TRUE;
		}
		if (cFile.GetFileName().IsEmpty())
		{
			m_szDefaultFiles[nType].Empty();
			return TRUE;
		}
		if ((pFile = new CHistoryStoreFile))
		{
			for (pFile->Copy(&cFile); m_pFiles[nType].Add(pFile) >= 0; )
			{
				m_szDefaultFiles[nType] = cFile.GetFileName();
				return TRUE;
			}
			delete pFile;
		}
	}
	return FALSE;
}

BOOL CHistoryStore::GetDefaultHistoryFile(UINT nType, CHistoryStoreFile &cFile) CONST
{
	INT  nFile;
	INT  nFiles;
	CHistoryStoreFiles  pFiles;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (nType == HISTORYFILE_TYPE_ARCHIVE || nType == HISTORYFILE_TYPE_RETRIEVE)
	{
		if (GetHistoryFiles(nType, pFiles) > 0 && pFiles.Find(m_szDefaultFiles[nType]) >= 0)
		{
			if (nType == HISTORYFILE_TYPE_ARCHIVE || CheckHistoryFile(pFiles.GetAt(pFiles.Find(m_szDefaultFiles[nType]))->GetFileName(), HISTORYSTORE_OPTION_ANYFILES, pFiles.GetAt(pFiles.Find(m_szDefaultFiles[nType]))))
			{
				cFile.Copy(pFiles.GetAt(pFiles.Find(m_szDefaultFiles[nType])));
				return TRUE;
			}
		}
		for (nFile = 0, nFiles = (pFiles.GetSize() > 0 && pFiles.Find(m_szDefaultFiles[nType]) < 0) ? (INT)pFiles.GetSize() : 0; nFile < nFiles; nFile++)
		{
			if (nType == HISTORYFILE_TYPE_ARCHIVE || CheckHistoryFile(pFiles.GetAt(nFile)->GetFileName(), HISTORYSTORE_OPTION_ANYFILES, pFiles.GetAt(nFile)))
			{
				cFile.Copy(pFiles.GetAt(nFile));
				break;
			}
		}
		return((nFile < nFiles) ? TRUE : FALSE);
	}
	return FALSE;
}

BOOL CHistoryStore::SetOptions(CONST CHistoryStoreOptions &pOptions)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_pOptions.Copy(&pOptions);
}

BOOL CHistoryStore::GetOptions(CHistoryStoreOptions &pOptions) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return pOptions.Copy(&m_pOptions);
}

BOOL CHistoryStore::SetBrowseOptions(CONST CUIntArray &nOptions, CONST CStringArray &szDirectories)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (nOptions.GetSize() == szDirectories.GetSize())
	{
		m_szBrowseDirectories.Copy(szDirectories);
		m_nBrowseOptions.Copy(nOptions);
		return TRUE;
	}
	return FALSE;
}

BOOL CHistoryStore::GetBrowseOptions(CUIntArray &nOptions, CStringArray &szDirectories) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (nOptions.GetSize() == szDirectories.GetSize())
	{
		szDirectories.Copy(m_szBrowseDirectories);
		nOptions.Copy(m_nBrowseOptions);
		return TRUE;
	}
	return FALSE;
}

INT CHistoryStore::Update(CONST CTMEnvironment *pTMEnvironment, CHistoryStoreFiles &pFiles, CUIntArray &nErrors)
{
	INT  nFile;
	INT  nFiles;
	INT  nIndex;
	CHistoryStoreFile  *pFile[2];
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nFile = 0, nFiles = (INT)m_pFiles[HISTORYFILE_TYPE_ARCHIVE].GetSize(), pFiles.RemoveAll(), nErrors.RemoveAll(); nFile < nFiles; nFile++)
	{
		if ((pFile[0] = ((pFile[1] = m_pFiles[HISTORYFILE_TYPE_ARCHIVE].GetAt(nFile))) ? new CHistoryStoreFile : (CHistoryStoreFile *)NULL))
		{
			for (pFile[0]->Copy(pFile[1]); (nIndex = pFiles.Add(pFile[0])) >= 0; )
			{
				nErrors.InsertAt(nIndex, pFile[1]->Update(m_szSpacecraft, m_nType, pTMEnvironment, TRUE));
				break;
			}
			if (nIndex < 0) delete pFile[0];
		}
	}
	return((INT)pFiles.GetSize());
}
INT CHistoryStore::Update(CONST CTCEnvironment *pTCEnvironment, CHistoryStoreFiles &pFiles, CUIntArray &nErrors)
{
	INT  nFile;
	INT  nFiles;
	INT  nIndex;
	CHistoryStoreFile  *pFile[2];
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nFile = 0, nFiles = (INT)m_pFiles[HISTORYFILE_TYPE_ARCHIVE].GetSize(), pFiles.RemoveAll(), nErrors.RemoveAll(); nFile < nFiles; nFile++)
	{
		if ((pFile[0] = ((pFile[1] = m_pFiles[HISTORYFILE_TYPE_ARCHIVE].GetAt(nFile))) ? new CHistoryStoreFile : (CHistoryStoreFile *)NULL))
		{
			for (pFile[0]->Copy(pFile[1]); (nIndex = pFiles.Add(pFile[0])) >= 0; )
			{
				nErrors.InsertAt(nIndex, pFile[1]->Update(m_szSpacecraft, m_nType, pTCEnvironment, TRUE));
				break;
			}
			if (nIndex < 0) delete pFile[0];
		}
	}
	return((INT)pFiles.GetSize());
}
INT CHistoryStore::Update(CHistoryStoreFiles &pFiles, CUIntArray &nErrors)
{
	INT  nFile;
	INT  nFiles;
	INT  nIndex;
	CHistoryStoreFile  *pFile[2];
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nFile = 0, nFiles = (INT)m_pFiles[HISTORYFILE_TYPE_ARCHIVE].GetSize(), pFiles.RemoveAll(), nErrors.RemoveAll(); nFile < nFiles; nFile++)
	{
		if ((pFile[0] = ((pFile[1] = m_pFiles[HISTORYFILE_TYPE_ARCHIVE].GetAt(nFile))) ? new CHistoryStoreFile : (CHistoryStoreFile *)NULL))
		{
			for (pFile[0]->Copy(pFile[1]); (nIndex = pFiles.Add(pFile[0])) >= 0; )
			{
				nErrors.InsertAt(nIndex, pFile[1]->Update(m_szSpacecraft, TRUE));
				break;
			}
			for (; nIndex < 0; )
			{
				delete pFile[0];
				break;
			}
		}
	}
	return((INT)pFiles.GetSize());
}

BOOL CHistoryStore::Map(CByteArray &nInfo) CONST
{
	DATA  sData;
	INT  cbData;
	INT  nDirectory;
	INT  nDirectories;
	CByteArray  nFileData[2];
	CByteArray  nOptionsData;
	CByteArray  nDirectoryData;

	sData.cbSpacecraft = (m_szSpacecraft.GetLength() + 1)*sizeof(TCHAR);
	sData.cbDefaultFiles[0] = (m_szDefaultFiles[0].GetLength() + 1)*sizeof(TCHAR);
	sData.cbDefaultFiles[1] = (m_szDefaultFiles[1].GetLength() + 1)*sizeof(TCHAR);
	sData.cbOptions = (m_pOptions.Map(nOptionsData)) ? (INT)nOptionsData.GetSize() : 0;
	sData.cbFiles[0] = (m_pFiles[0].Map(nFileData[0])) ? (INT)nFileData[0].GetSize() : 0;
	sData.cbFiles[1] = (m_pFiles[1].Map(nFileData[1])) ? (INT)nFileData[1].GetSize() : 0;
	for (nDirectory = 0, nDirectories = (INT)m_szBrowseDirectories.GetSize(), sData.cbBrowseOptions = (INT)m_nBrowseOptions.GetSize()*sizeof(UINT), sData.cbBrowseDirectories = 0; nDirectory < nDirectories; nDirectory++, sData.cbBrowseDirectories += cbData)
	{
		nDirectoryData.SetSize(sData.cbBrowseDirectories + (cbData = (m_szBrowseDirectories.GetAt(nDirectory).GetLength() + 1)*sizeof(TCHAR)));
		CopyMemory(nDirectoryData.GetData() + sData.cbBrowseDirectories, (LPCTSTR)m_szBrowseDirectories.GetAt(nDirectory), cbData);
	}
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbSpacecraft + sData.cbFiles[0] + sData.cbFiles[1] + sData.cbDefaultFiles[0] + sData.cbDefaultFiles[1] + sData.cbBrowseOptions + sData.cbBrowseDirectories + sData.cbOptions)); nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szSpacecraft, sData.cbSpacecraft);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbSpacecraft), nFileData[0].GetData(), sData.cbFiles[0]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbFiles[0]), nFileData[1].GetData(), sData.cbFiles[1]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbFiles[1]), (LPCTSTR)m_szDefaultFiles[0], sData.cbDefaultFiles[0]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbDefaultFiles[0]), (LPCTSTR)m_szDefaultFiles[1], sData.cbDefaultFiles[1]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbDefaultFiles[1]), m_nBrowseOptions.GetData(), sData.cbBrowseOptions);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbBrowseOptions), nDirectoryData.GetData(), sData.cbBrowseDirectories);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbBrowseDirectories), nOptionsData.GetData(), sData.cbOptions);
		return TRUE;
	}
	return FALSE;
}

BOOL CHistoryStore::Unmap(CONST CByteArray &nInfo)
{
	DATA  sData;
	INT  cbData;
	INT  cbDirectory;
	INT  cbDirectories;
	CString  szSpacecraft;
	CByteArray  nFileData[2];
	CByteArray  nOptionsData;
	CByteArray  nDirectoryData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbSpacecraft + sData.cbFiles[0] + sData.cbFiles[1] + sData.cbDefaultFiles[0] + sData.cbDefaultFiles[1] + sData.cbBrowseOptions + sData.cbBrowseDirectories + sData.cbOptions && sData.cbSpacecraft > 0 && sData.cbDefaultFiles[0] > 0 && sData.cbDefaultFiles[1] > 0 && sData.cbFiles[0] >= 0 && sData.cbFiles[1] >= 0 && sData.cbBrowseOptions >= 0 && sData.cbBrowseDirectories >= 0 && sData.cbOptions >= 0; )
	{
		for (nFileData[0].SetSize(sData.cbFiles[0]), nFileData[1].SetSize(sData.cbFiles[1]), nDirectoryData.SetSize(sData.cbBrowseDirectories), m_nBrowseOptions.SetSize(sData.cbBrowseOptions / sizeof(UINT)), nOptionsData.SetSize(sData.cbOptions); nFileData[0].GetSize() == sData.cbFiles[0] && nFileData[1].GetSize() == sData.cbFiles[1] && nDirectoryData.GetSize() == sData.cbBrowseDirectories && m_nBrowseOptions.GetSize() == sData.cbBrowseOptions / sizeof(UINT); )
		{
			CopyMemory(szSpacecraft.GetBufferSetLength(STRINGCHARS(sData.cbSpacecraft)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbSpacecraft));
			CopyMemory(nFileData[0].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbSpacecraft), sData.cbFiles[0]);
			CopyMemory(nFileData[1].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbFiles[0]), sData.cbFiles[1]);
			CopyMemory(m_szDefaultFiles[0].GetBufferSetLength(STRINGCHARS(sData.cbDefaultFiles[0])), nInfo.GetData() + (cbData = cbData + sData.cbFiles[1]), STRINGBYTES(sData.cbDefaultFiles[0]));
			CopyMemory(m_szDefaultFiles[1].GetBufferSetLength(STRINGCHARS(sData.cbDefaultFiles[1])), nInfo.GetData() + (cbData = cbData + sData.cbDefaultFiles[0]), STRINGBYTES(sData.cbDefaultFiles[1]));
			CopyMemory(m_nBrowseOptions.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbDefaultFiles[1]), sData.cbBrowseOptions);
			CopyMemory(nDirectoryData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbBrowseOptions), sData.cbBrowseDirectories);
			CopyMemory(nOptionsData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbBrowseDirectories), sData.cbOptions);
			break;
		}
		for (szSpacecraft.ReleaseBuffer(), m_szDefaultFiles[0].ReleaseBuffer(), m_szDefaultFiles[1].ReleaseBuffer(), m_szBrowseDirectories.RemoveAll(), cbDirectory = cbDirectories = 0; cbDirectories < nDirectoryData.GetSize(); cbDirectories += (cbDirectory = (m_szBrowseDirectories.GetAt(m_szBrowseDirectories.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR)))
		{
			m_szBrowseDirectories.Add((LPCTSTR)(nDirectoryData.GetData() + cbDirectories));
			continue;
		}
		if ((m_szSpacecraft == szSpacecraft || szSpacecraft.IsEmpty()) && m_nBrowseOptions.GetSize() == m_szBrowseDirectories.GetSize() && m_pFiles[0].Unmap(nFileData[0]) && m_pFiles[1].Unmap(nFileData[1]) && m_pOptions.Unmap(nOptionsData)) return TRUE;
		break;
	}
	return((!nInfo.GetSize()) ? TRUE : FALSE);
}

BOOL CHistoryStore::CheckHistoryFile(LPCTSTR pszFileName) CONST
{
	CString  szSpacecraft;
	CHistoryFile  cHistoryFile;

	if (cHistoryFile.Open(pszFileName, m_szSpacecraft, m_nType, CFile::modeRead) == HISTORYFILE_SUCCESS)
	{
		if (cHistoryFile.GetSpacecraft(szSpacecraft) && m_szSpacecraft == szSpacecraft)
		{
			cHistoryFile.Close();
			return TRUE;
		}
		cHistoryFile.Close();
	}
	return FALSE;
}
BOOL CHistoryStore::CheckHistoryFile(LPCTSTR pszFileName, UINT nOption, CHistoryStoreFile *pFile) CONST
{
	UINT  nPolicy;
	WORD  wInterval;
	CString szTitle;
	CTimeKey  tTime;
	DWORDLONG  dwSize;
	CFileFindEx  cFileFind;
	CHistoryFile  cHistoryFile;

	switch (nOption)
	{
	case HISTORYSTORE_OPTION_ANYFILES: break;
	case HISTORYSTORE_OPTION_TIMETAGGEDFILES:
	{ if (cFileFind.FindFile(pszFileName) && !cFileFind.FindNextFile())
	{
		if (tTime.Parse(cFileFind.GetFileTitle(), STRING(IDS_HISTORYFILE_TIMETAGGEDFORMAT)) > 0)
		{
			cFileFind.Close();
			break;
		}
		cFileFind.Close();
	}
	return FALSE;
	break;
	}
	case HISTORYSTORE_OPTION_ENUMERATEDFILES:
	{ if (cFileFind.FindFile(pszFileName) && !cFileFind.FindNextFile())
	{
		szTitle.Format(STRING(IDS_HISTORYFILE_ENUMERATEDFORMAT), (LPCTSTR)m_szSpacecraft, 0);
		if (!_tcsnicmp(cFileFind.GetFileTitle(), szTitle, szTitle.GetLength() - 1))
		{
			cFileFind.Close();
			break;
		}
		cFileFind.Close();
	}
	return FALSE;
	break;
	}
	default:
	{ return FALSE;
	break;
	}
	}
	if (CheckHistoryFile(pszFileName))
	{
		if (cHistoryFile.Open(pszFileName, m_szSpacecraft, m_nType, CFile::modeRead) == HISTORYFILE_SUCCESS)
		{
			if (cHistoryFile.GetPolicy(nPolicy))
			{
				pFile->SetFileName(pszFileName);
				pFile->SetOptions(((nPolicy & LOGFILE_POLICY_CYCLICMODE) ? HISTORYSTORE_OPTION_CYCLIC : HISTORYSTORE_OPTION_NONCYCLIC) | ((nPolicy & LOGFILE_POLICY_RETENTIONBYSIZE) ? HISTORYSTORE_OPTION_LIMITEDSIZE : HISTORYSTORE_OPTION_UNLIMITEDSIZE) | ((cHistoryFile.GetUpdateInterval(wInterval) && wInterval > 0) ? HISTORYSTORE_OPTION_FULLUPDATES : 0));
				pFile->SetUpdateInterval((cHistoryFile.GetUpdateInterval(wInterval)) ? wInterval : 0);
				pFile->SetFileSize((cHistoryFile.GetRetentionBySize(dwSize)) ? dwSize : 0);
				cHistoryFile.Close();
				return TRUE;
			}
			cHistoryFile.Close();
		}
	}
	return FALSE;
}

BOOL CHistoryStore::Lock()
{
	return m_pCriticalSection->Lock();
}

BOOL CHistoryStore::Unlock()
{
	return m_pCriticalSection->Unlock();
}


/////////////////////////////////////////////////////////////////////////////
// CHistoryTMProcessEngine

BOOL CHistoryTMProcessEngine::Open(CONST CDatabaseEngine *pDatabase, LPCTSTR pszName, LPCTSTR pszFileName, CTMEnvironment *pTMEnvironment)
{
	if (CTMProcessEngine::Open(pDatabase, pszName, pTMEnvironment))
	{
		m_szFileName = pszFileName;
		return TRUE;
	}
	return FALSE;
}

VOID CHistoryTMProcessEngine::Close()
{
	m_szFileName.Empty();
	CTMProcessEngine::Close();
}

UINT CHistoryTMProcessEngine::ProcessTMData(CONST CDatabaseEngine *pDatabase, CTMEnvironment *pTMEnvironment, CTimeKey &tTimeKey)
{
	UINT  nCode;
	CTimeKey  tTime;

	if (IsOpen())
	{
		if ((nCode = m_cFile.Open(GetFileName(), GetName(), HISTORYSTORE_TYPE_TM, CFile::modeRead)) & HISTORYFILE_SUCCESS)
		{
			if (((nCode = m_cFile.Read((tTime = tTimeKey), pTMEnvironment)) & HISTORYFILE_SUCCESS) == HISTORYFILE_SUCCESS)
			{
				if (((nCode & HISTORYFILE_TMUNIT) && GetTMProcessEngine()->ProcessTMUnit(pDatabase, pTMEnvironment->GetTMUnit(), pTMEnvironment) >= 0) || (nCode & HISTORYFILE_TMPARAMETERS))
				{
					tTimeKey = tTime;
					m_cFile.Close();
					return nCode;
				}
			}
			m_cFile.Close();
		}
		return nCode;
	}
	return HISTORYFILE_ERROR;
}

UINT CHistoryTMProcessEngine::ReplayTMData(CONST CDatabaseEngine *pDatabase, CTMEnvironment *pTMEnvironment, CTimeKey &tTimeKey, CONST CTimeSpan &tInterval)
{
	UINT  nCode;
	CTimeKey  tTime;

	if (IsOpen())
	{
		if ((nCode = m_cFile.Open(GetFileName(), GetName(), HISTORYSTORE_TYPE_TM, CFile::modeRead)) & HISTORYFILE_SUCCESS)
		{
			if (((nCode = m_cFile.ReadNext((tTime = tTimeKey), tInterval, pTMEnvironment)) & HISTORYFILE_SUCCESS) == HISTORYFILE_SUCCESS)
			{
				if (((nCode & HISTORYFILE_TMUNIT) && GetTMProcessEngine()->ProcessTMUnit(pDatabase, pTMEnvironment->GetTMUnit(), pTMEnvironment) >= 0) || (nCode & HISTORYFILE_TMPARAMETERS))
				{
					tTimeKey = tTime;
					m_cFile.Close();
					return nCode;
				}
			}
			m_cFile.Close();
		}
		return nCode;
	}
	return HISTORYFILE_ERROR;
}

UINT CHistoryTMProcessEngine::RewindTMData(CONST CDatabaseEngine *pDatabase, CTMEnvironment *pTMEnvironment, CTimeKey &tTimeKey, CONST CTimeSpan &tInterval)
{
	UINT  nCode;
	CTimeKey  tTime;

	if (IsOpen())
	{
		if ((nCode = m_cFile.Open(GetFileName(), GetName(), HISTORYSTORE_TYPE_TM, CFile::modeRead)) & HISTORYFILE_SUCCESS)
		{
			if (((nCode = m_cFile.ReadPrev((tTime = tTimeKey), tInterval, pTMEnvironment)) & HISTORYFILE_SUCCESS) == HISTORYFILE_SUCCESS)
			{
				if (((nCode & HISTORYFILE_TMUNIT) && GetTMProcessEngine()->ProcessTMUnit(pDatabase, pTMEnvironment->GetTMUnit(), pTMEnvironment) >= 0) || (nCode & HISTORYFILE_TMPARAMETERS))
				{
					tTimeKey = tTime;
					m_cFile.Close();
					return nCode;
				}
			}
			m_cFile.Close();
		}
		return nCode;
	}
	return HISTORYFILE_ERROR;
}

CString CHistoryTMProcessEngine::GetFileName() CONST
{
	return m_szFileName;
}


/////////////////////////////////////////////////////////////////////////////
// CHistoryTCProcessEngine

BOOL CHistoryTCProcessEngine::Open(CONST CDatabaseEngine *pDatabase, LPCTSTR pszName, LPCTSTR pszFileName, CTCEnvironment *pTCEnvironment)
{
	if (CTCProcessEngine::Open(pDatabase, pszName, pTCEnvironment))
	{
		m_szFileName = pszFileName;
		return TRUE;
	}
	return FALSE;
}

VOID CHistoryTCProcessEngine::Close()
{
	m_szFileName.Empty();
	CTCProcessEngine::Close();
}

UINT CHistoryTCProcessEngine::ProcessTCData(CONST CDatabaseEngine *pDatabase, CTCEnvironment *pTCEnvironment, CTimeKey &tTimeKey)
{
	UINT  nCode;
	CTimeKey  tTime;

	if (IsOpen())
	{
		if ((nCode = m_cFile.Open(GetFileName(), GetName(), HISTORYSTORE_TYPE_TC, CFile::modeRead)) & HISTORYFILE_SUCCESS)
		{
			if ((nCode = m_cFile.Read((tTime = tTimeKey), pTCEnvironment)) & HISTORYFILE_SUCCESS)
			{
				if ((nCode & HISTORYFILE_TCUNIT) || (nCode & HISTORYFILE_TCPARAMETERS))
				{
					tTimeKey = tTime;
					m_cFile.Close();
					return nCode;
				}
			}
			m_cFile.Close();
		}
		return nCode;
	}
	return HISTORYFILE_ERROR;
}

UINT CHistoryTCProcessEngine::ReplayTCData(CONST CDatabaseEngine *pDatabase, CTCEnvironment *pTCEnvironment, CTimeKey &tTimeKey)
{
	UINT  nCode;
	CTimeKey  tTime;

	if (IsOpen())
	{
		if ((nCode = m_cFile.Open(GetFileName(), GetName(), HISTORYSTORE_TYPE_TC, CFile::modeRead)) & HISTORYFILE_SUCCESS)
		{
			if ((nCode = m_cFile.ReadNext((tTime = tTimeKey), pTCEnvironment)) & HISTORYFILE_SUCCESS)
			{
				if ((nCode & HISTORYFILE_TCUNIT) || (nCode & HISTORYFILE_TCPARAMETERS))
				{
					tTimeKey = tTime;
					m_cFile.Close();
					return nCode;
				}
			}
			m_cFile.Close();
		}
		return nCode;
	}
	return HISTORYFILE_ERROR;
}

CString CHistoryTCProcessEngine::GetFileName() CONST
{
	return m_szFileName;
}
