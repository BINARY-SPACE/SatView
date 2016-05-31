// EVENTLOG.CPP : Eventlog Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the eventlog related
// interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 1994/05/23 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CEventLog

CEventLog::CEventLog() : CToken()
{
	SetOwner(GetAccountComputerName(), GetAccountSpacecraftName(), GetAccountUserName());
	m_bBuffering[0] = FALSE;
	m_bBuffering[1] = FALSE;
	m_bBuffering[2] = FALSE;
}
CEventLog::CEventLog(LPCTSTR pszSystemName, LPCTSTR pszSpacecraftName, LPCTSTR pszUserName, BOOL bLocal) : CToken(pszSystemName, pszSpacecraftName, pszUserName)
{
	SetOwner(pszSystemName, pszSpacecraftName, pszUserName, bLocal);
	m_bBuffering[0] = FALSE;
	m_bBuffering[1] = FALSE;
	m_bBuffering[2] = FALSE;
}

BOOL CEventLog::Open(LPCTSTR pszSystemName, LPCTSTR pszSpacecraftName, LPCTSTR pszUserName, UINT nEventLogs, UINT nFlags, UINT bLocal, BOOL bWait)
{
	return CToken::SetOwner(pszSystemName, pszSpacecraftName, pszUserName) && Open(nEventLogs, nFlags, bLocal, bWait);
}
BOOL CEventLog::Open(UINT nEventLogs, UINT nFlags, UINT bLocal, BOOL bWait)
{
	CString  szFileName[3];

	for (; nEventLogs & EVENTLOG_CATEGORY_SYSTEM; )
	{
		if (QuerySystemLogFileName(szFileName[0]) && TestDirectory(szFileName[0]))
		{
			if (m_fSystemLog.Open(szFileName[0], EMPTYSTRING, STRING(IDS_LOGFILETYPE_EVENTLOG), nFlags, bWait))
			{
				if (!m_fSystemLog.IsEmpty() || CheckSecurity(szFileName[0]))
				{
					m_bBuffering[0] = FALSE;
					break;
				}
				m_fSystemLog.Close();
				return FALSE;
			}
			if (m_fSystemLog.Lock())
			{
				if ((nFlags & CFile::modeWrite) || (nFlags & CFile::modeReadWrite))
				{
					m_bBuffering[0] = TRUE;
					break;
				}
				m_fSystemLog.Unlock();
			}
		}
		return FALSE;
	}
	for (m_bLocal = (bLocal != (UINT)-1) ? bLocal : m_bLocal; nEventLogs & EVENTLOG_CATEGORY_SPACECRAFT; )
	{
		if ((m_bLocal  &&  QuerySpacecraftLogFileName(szFileName[1]) && TestDirectory(szFileName[1])) || (!m_bLocal  &&  QueryGlobalSpacecraftLogFileName(szFileName[1])))
		{
			if (m_fSpacecraftLog.Open(szFileName[1], GetSpacecraftName(), STRING(IDS_LOGFILETYPE_EVENTLOG), nFlags, bWait))
			{
				if (!m_fSpacecraftLog.IsEmpty() || CheckSecurity(szFileName[1]))
				{
					m_bBuffering[1] = FALSE;
					break;
				}
				for (m_fSpacecraftLog.Close(); nEventLogs & EVENTLOG_CATEGORY_SYSTEM; )
				{
					if (!m_bBuffering[0])
					{
						m_fSystemLog.Close();
					}
					break;
				}
				return FALSE;
			}
			if (m_fSpacecraftLog.Lock())
			{
				if ((nFlags & CFile::modeWrite) || (nFlags & CFile::modeReadWrite))
				{
					m_bBuffering[1] = TRUE;
					break;
				}
				m_fSpacecraftLog.Unlock();
			}
		}
		if (nEventLogs & EVENTLOG_CATEGORY_SYSTEM)
		{
			if (!m_bBuffering[0])
			{
				m_fSystemLog.Close();
			}
		}
		return FALSE;
	}
	for (; nEventLogs & EVENTLOG_CATEGORY_USER; )
	{
		if (QueryUserLogFileName(szFileName[2]) && TestDirectory(szFileName[2]))
		{
			if (m_fUserLog.Open(szFileName[2], EMPTYSTRING, STRING(IDS_LOGFILETYPE_EVENTLOG), nFlags, bWait))
			{
				if (!m_fUserLog.IsEmpty() || CheckSecurity(szFileName[2]))
				{
					m_bBuffering[2] = FALSE;
					break;
				}
				for (m_fUserLog.Close(); nEventLogs & EVENTLOG_CATEGORY_SPACECRAFT; )
				{
					if (!m_bBuffering[1])
					{
						m_fSpacecraftLog.Close();
					}
					break;
				}
				if (nEventLogs & EVENTLOG_CATEGORY_SYSTEM)
				{
					if (!m_bBuffering[0])
					{
						m_fSystemLog.Close();
					}
				}
				return FALSE;
			}
			if (m_fUserLog.Lock())
			{
				if ((nFlags & CFile::modeWrite) || (nFlags & CFile::modeReadWrite))
				{
					m_bBuffering[2] = TRUE;
					break;
				}
				m_fUserLog.Unlock();
			}
		}
		if (nEventLogs & EVENTLOG_CATEGORY_SPACECRAFT)
		{
			if (!m_bBuffering[1])
			{
				m_fSpacecraftLog.Close();
			}
		}
		if (nEventLogs & EVENTLOG_CATEGORY_SYSTEM)
		{
			if (!m_bBuffering[0])
			{
				m_fSystemLog.Close();
			}
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CEventLog::Compress(UINT nEventLogs, BOOL bCompress)
{
	return(((!(nEventLogs & EVENTLOG_CATEGORY_SYSTEM) || m_fSystemLog.Compress(bCompress)) && (!(nEventLogs & EVENTLOG_CATEGORY_SPACECRAFT) || m_fSpacecraftLog.Compress(bCompress)) && (!(nEventLogs & EVENTLOG_CATEGORY_USER) || m_fUserLog.Compress(bCompress))) ? TRUE : FALSE);
}

BOOL CEventLog::Reset(UINT nEventLogs)
{
	return(((!(nEventLogs & EVENTLOG_CATEGORY_SYSTEM) || m_fSystemLog.Reset()) && (!(nEventLogs & EVENTLOG_CATEGORY_SPACECRAFT) || m_fSpacecraftLog.Reset()) && (!(nEventLogs & EVENTLOG_CATEGORY_USER) || m_fUserLog.Reset())) ? TRUE : FALSE);
}

VOID CEventLog::Close(UINT nEventLogs)
{
	for (; nEventLogs & EVENTLOG_CATEGORY_SYSTEM; )
	{
		if (!m_bBuffering[0])
		{
			m_fSystemLog.Close();
			break;
		}
		m_bBuffering[0] = FALSE;
		m_fSystemLog.Unlock();
		break;
	}
	for (; nEventLogs & EVENTLOG_CATEGORY_SPACECRAFT; )
	{
		if (!m_bBuffering[1])
		{
			m_fSpacecraftLog.Close();
			break;
		}
		m_bBuffering[1] = FALSE;
		m_fSpacecraftLog.Unlock();
		break;
	}
	for (; nEventLogs & EVENTLOG_CATEGORY_USER; )
	{
		if (!m_bBuffering[2])
		{
			m_fUserLog.Close();
			break;
		}
		m_bBuffering[2] = FALSE;
		m_fUserLog.Unlock();
		break;
	}
}

BOOL CEventLog::RegisterSource(LPCTSTR pszSystemLogName, LPCTSTR pszGlobalSpacecraftLogName, LPCTSTR pszSpacecraftLogName, LPCTSTR pszUserLogName)
{
	CString  szSubKey;
	CString  szFileName[4];
	CFileFindEx  cFileFind;
	CRegistry  cRegistry;

	if (!HasOwner() || (cRegistry.SetComputerName(GetComputerName()) && QuerySystemLogSubKey(szSubKey) && (AfxIsValidString(pszSystemLogName) || QuerySystemLogFileName(szFileName[0])) && cRegistry.SetMachineInfo(szSubKey, STRING(IDS_REG_SUBKEYVALUE_SYSTEMEVENTLOGNAME), (szFileName[0] = (AfxIsValidString(pszSystemLogName)) ? pszSystemLogName : (LPCTSTR)szFileName[0])) && TestDirectory(szFileName[0]) && QuerySpacecraftLogSubKey(szSubKey) && (AfxIsValidString(pszGlobalSpacecraftLogName) || QueryGlobalSpacecraftLogFileName(szFileName[1])) && cRegistry.SetMachineInfo(szSubKey, STRING(IDS_REG_SUBKEYVALUE_GLOBALSPACECRAFTEVENTLOGNAME), (szFileName[1] = (AfxIsValidString(pszGlobalSpacecraftLogName)) ? pszGlobalSpacecraftLogName : (LPCTSTR)szFileName[1]) && TestDirectory(szFileName[1]) && QuerySpacecraftLogSubKey(szSubKey) && (AfxIsValidString(pszSpacecraftLogName) || QuerySpacecraftLogFileName(szFileName[2])) && cRegistry.SetMachineInfo(szSubKey, STRING(IDS_REG_SUBKEYVALUE_SPACECRAFTEVENTLOGNAME), (szFileName[2] = (AfxIsValidString(pszSpacecraftLogName)) ? pszSpacecraftLogName : (LPCTSTR)szFileName[2])) && TestDirectory(szFileName[2]) && QueryUserLogSubKey(szSubKey) && (AfxIsValidString(pszUserLogName) || QueryUserLogFileName(szFileName[3])) && cRegistry.SetMachineInfo(szSubKey, STRING(IDS_REG_SUBKEYVALUE_USEREVENTLOGNAME), (szFileName[3] = (AfxIsValidString(pszUserLogName)) ? pszUserLogName : (LPCTSTR)szFileName[3])) && TestDirectory(szFileName[3]))))
	{
		for (; !cFileFind.FindFile(szFileName[0]) && Open(EVENTLOG_CATEGORY_SYSTEM, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite, TRUE); )
		{
			Close(EVENTLOG_CATEGORY_SYSTEM);
			break;
		}
		for (cFileFind.Close(); !cFileFind.FindFile(szFileName[2]) && Open(EVENTLOG_CATEGORY_SPACECRAFT, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite, TRUE); )
		{
			Close(EVENTLOG_CATEGORY_SPACECRAFT);
			break;
		}
		for (cFileFind.Close(); !cFileFind.FindFile(szFileName[3]) && Open(EVENTLOG_CATEGORY_USER, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite, TRUE); )
		{
			Close(EVENTLOG_CATEGORY_USER);
			break;
		}
		for (cFileFind.Close(); !cFileFind.FindFile(szFileName[0]); ) return FALSE;
		for (cFileFind.Close(); !cFileFind.FindFile(szFileName[2]); ) return FALSE;
		for (cFileFind.Close(); !cFileFind.FindFile(szFileName[3]); ) return FALSE;
		cFileFind.Close();
		return TRUE;
	}
	return FALSE;
}

BOOL CEventLog::UnregisterSource(UINT nEventLogs, BOOL bAll)
{
	CString  szSubKey;
	CString  szFileName[3];
	CRegistry  cRegistry;

	return((!bAll || !HasOwner() || (cRegistry.SetComputerName(GetComputerUNCName()) && (!(nEventLogs & EVENTLOG_CATEGORY_SYSTEM) || (QuerySystemLogSubKey(szSubKey) && (!cRegistry.GetMachineInfo(szSubKey, STRING(IDS_REG_SUBKEYVALUE_SYSTEMEVENTLOGNAME), szFileName[0]) || cRegistry.SetMachineInfo(szSubKey, STRING(IDS_REG_SUBKEYVALUE_SYSTEMEVENTLOGNAME))))) && (!(nEventLogs & EVENTLOG_CATEGORY_SPACECRAFT) || (QuerySpacecraftLogSubKey(szSubKey) && (!IsHost() || !cRegistry.GetMachineInfo(szSubKey, STRING(IDS_REG_SUBKEYVALUE_GLOBALSPACECRAFTEVENTLOGNAME), szFileName[1]) || cRegistry.SetMachineInfo(szSubKey, STRING(IDS_REG_SUBKEYVALUE_GLOBALSPACECRAFTEVENTLOGNAME))) && (!cRegistry.GetMachineInfo(szSubKey, STRING(IDS_REG_SUBKEYVALUE_SPACECRAFTEVENTLOGNAME), szFileName[1]) || cRegistry.SetMachineInfo(szSubKey, STRING(IDS_REG_SUBKEYVALUE_SPACECRAFTEVENTLOGNAME))))) && (!(nEventLogs & EVENTLOG_CATEGORY_USER) || (QueryUserLogSubKey(szSubKey) && (!cRegistry.GetMachineInfo(szSubKey, STRING(IDS_REG_SUBKEYVALUE_USEREVENTLOGNAME), szFileName[2]) || cRegistry.SetMachineInfo(szSubKey, STRING(IDS_REG_SUBKEYVALUE_USEREVENTLOGNAME))))))) ? TRUE : FALSE);
}

BOOL CEventLog::SetOwner(CToken *pToken, BOOL bLocal)
{
	m_bLocal = bLocal;
	return CToken::SetOwner(pToken);
}
BOOL CEventLog::SetOwner(LPCTSTR pszSystemName, LPCTSTR pszSpacecraftName, LPCTSTR pszUserName, BOOL bLocal)
{
	m_bLocal = bLocal;
	return CToken::SetOwner(pszSystemName, pszSpacecraftName, pszUserName);
}

BOOL CEventLog::GetOwner(CString &szSystemName, CString &szSpacecraftName, CString &szUserName, BOOL &bLocal) CONST
{
	bLocal = m_bLocal;
	return CToken::GetOwner(szSystemName, szSpacecraftName, szUserName);
}
BOOL CEventLog::GetOwner(CString &szSystemName, CString &szSpacecraftName, CString &szUserName) CONST
{
	return CToken::GetOwner(szSystemName, szSpacecraftName, szUserName);
}

BOOL CEventLog::SetSystemLogMode(UINT nMode)
{
	return m_fSystemLog.SetMode(nMode);
}

BOOL CEventLog::GetSystemLogMode(UINT &nMode) CONST
{
	return m_fSystemLog.GetMode(nMode);
}

BOOL CEventLog::SetSystemLogPolicy(UINT nPolicy)
{
	return m_fSystemLog.SetPolicy(nPolicy);
}

BOOL CEventLog::GetSystemLogPolicy(UINT &nPolicy) CONST
{
	return m_fSystemLog.GetPolicy(nPolicy);
}

BOOL CEventLog::SetSystemLogRetentionByItem(INT nRetention)
{
	return m_fSystemLog.SetRetentionByItem(nRetention);
}

BOOL CEventLog::GetSystemLogRetentionByItem(INT &nRetention) CONST
{
	return m_fSystemLog.GetRetentionByItem(nRetention);
}

BOOL CEventLog::SetSystemLogRetentionBySize(DWORDLONG fRetention)
{
	return m_fSystemLog.SetRetentionBySize(fRetention);
}

BOOL CEventLog::GetSystemLogRetentionBySize(DWORDLONG &fRetention) CONST
{
	return m_fSystemLog.GetRetentionBySize(fRetention);
}

BOOL CEventLog::SetSystemLogRetentionByTime(CONST CTimeSpan &tRetention)
{
	return m_fSystemLog.SetRetentionByTime(tRetention);
}

BOOL CEventLog::GetSystemLogRetentionByTime(CTimeSpan &tRetention) CONST
{
	return m_fSystemLog.GetRetentionByTime(tRetention);
}

BOOL CEventLog::SetSpacecraftLogMode(UINT nMode)
{
	return m_fSpacecraftLog.SetMode(nMode);
}

BOOL CEventLog::GetSpacecraftLogMode(UINT &nMode) CONST
{
	return m_fSpacecraftLog.GetMode(nMode);
}

BOOL CEventLog::SetSpacecraftLogPolicy(UINT nPolicy)
{
	return m_fSpacecraftLog.SetPolicy(nPolicy);
}

BOOL CEventLog::GetSpacecraftLogPolicy(UINT &nPolicy) CONST
{
	return m_fSpacecraftLog.GetPolicy(nPolicy);
}

BOOL CEventLog::SetSpacecraftLogRetentionByItem(INT nRetention)
{
	return m_fSpacecraftLog.SetRetentionByItem(nRetention);
}

BOOL CEventLog::GetSpacecraftLogRetentionByItem(INT &nRetention) CONST
{
	return m_fSpacecraftLog.GetRetentionByItem(nRetention);
}

BOOL CEventLog::SetSpacecraftLogRetentionBySize(DWORDLONG fRetention)
{
	return m_fSpacecraftLog.SetRetentionBySize(fRetention);
}

BOOL CEventLog::GetSpacecraftLogRetentionBySize(DWORDLONG &fRetention) CONST
{
	return m_fSpacecraftLog.GetRetentionBySize(fRetention);
}

BOOL CEventLog::SetSpacecraftLogRetentionByTime(CONST CTimeSpan &tRetention)
{
	return m_fSpacecraftLog.SetRetentionByTime(tRetention);
}

BOOL CEventLog::GetSpacecraftLogRetentionByTime(CTimeSpan &tRetention) CONST
{
	return m_fSpacecraftLog.GetRetentionByTime(tRetention);
}

BOOL CEventLog::SetUserLogMode(UINT nMode)
{
	return m_fUserLog.SetMode(nMode);
}

BOOL CEventLog::GetUserLogMode(UINT &nMode) CONST
{
	return m_fUserLog.GetMode(nMode);
}

BOOL CEventLog::SetUserLogPolicy(UINT nPolicy)
{
	return m_fUserLog.SetPolicy(nPolicy);
}

BOOL CEventLog::GetUserLogPolicy(UINT &nPolicy) CONST
{
	return m_fUserLog.GetPolicy(nPolicy);
}

BOOL CEventLog::SetUserLogRetentionByItem(INT nRetention)
{
	return m_fUserLog.SetRetentionByItem(nRetention);
}

BOOL CEventLog::GetUserLogRetentionByItem(INT &nRetention) CONST
{
	return m_fUserLog.GetRetentionByItem(nRetention);
}

BOOL CEventLog::SetUserLogRetentionBySize(DWORDLONG fRetention)
{
	return m_fUserLog.SetRetentionBySize(fRetention);
}

BOOL CEventLog::GetUserLogRetentionBySize(DWORDLONG &fRetention) CONST
{
	return m_fUserLog.GetRetentionBySize(fRetention);
}

BOOL CEventLog::SetUserLogRetentionByTime(CONST CTimeSpan &tRetention)
{
	return m_fUserLog.SetRetentionByTime(tRetention);
}

BOOL CEventLog::GetUserLogRetentionByTime(CTimeSpan &tRetention) CONST
{
	return m_fUserLog.GetRetentionByTime(tRetention);
}

BOOL CEventLog::Write(CONST EVENT_DESCRIPTOR sEvent)
{
	CEventObject  *pEventObject;

	if ((pEventObject = new CEventObject(sEvent)))
	{
		for (pEventObject->SetUser(GetUserName()), pEventObject->SetAudition(AUDIO_STANDARD_SOUND), pEventObject->SetAuditColor(VGA_COLOR_BLACK), pEventObject->SetAuditTime(CTime::GetCurrentTime().GetTime()), pEventObject->Acknowledge(), pEventObject->Show(); Write(pEventObject); )
		{
			delete pEventObject;
			return TRUE;
		}
		delete pEventObject;
	}
	return FALSE;
}
BOOL CEventLog::Write(CONST CEventObject *pEvent)
{
	INT  nCategory;
	CByteArray  nInfo[2];
	CEventObject  *pEventObject;
	CCompressionTools  cCompressionTools;

	if (pEvent->Map(nInfo[0]) && cCompressionTools.Compress(nInfo[0], nInfo[1]) > 0)
	{
		if (((nCategory = pEvent->GetCategory()) == EVENT_CATEGORY_SYSTEM  &&  m_bBuffering[0]) || (nCategory == EVENT_CATEGORY_SPACECRAFT  &&  m_bBuffering[1]) || (nCategory == EVENT_CATEGORY_USER  &&  m_bBuffering[2]))
		{
			for (m_pBufferData.EnableSound(FALSE); (pEventObject = new CEventObject) != (CEventObject *)NULL; )
			{
				for (pEventObject->Copy(pEvent); m_pBufferData.Add(pEventObject) >= 0; ) return TRUE;
				delete pEventObject;
				break;
			}
			return FALSE;
		}
		return(((nCategory == EVENT_CATEGORY_SYSTEM  &&  FlushAll() && m_fSystemLog.Write(pEvent->GetAuditTime(), nInfo[1])) || (nCategory == EVENT_CATEGORY_SPACECRAFT  &&  FlushAll() && m_fSpacecraftLog.Write(pEvent->GetAuditTime(), nInfo[1])) || (nCategory == EVENT_CATEGORY_USER  &&  FlushAll() && m_fUserLog.Write(pEvent->GetAuditTime(), nInfo[1]))) ? TRUE : FALSE);
	}
	return FALSE;
}

BOOL CEventLog::Read(CEventList &cEventList, CONST CTimeKey &tStartTime, INT nCount, UINT nEventLogs, HANDLE hAbort)
{
	INT  nIndex;
	DWORD  dwResult;
	CTimeKey  tTime;
	CByteArray  nInfo[2];
	CEventList  *pEventList;
	CEventObject  *pEvent;
	CCompressionTools  cCompressionTools;

	if ((pEventList = new CEventList))
	{
		if (nEventLogs & EVENTLOG_CATEGORY_SYSTEM)
		{
			if (m_fSystemLog.SeekTo(tStartTime))
			{
				for (pEventList->EnableSound(FALSE), nIndex = 0; (dwResult = (hAbort != (HANDLE)NULL) ? WaitForSingleObject(hAbort, 0) : WAIT_TIMEOUT) == WAIT_TIMEOUT && (nIndex < nCount || nCount < 0); )
				{
					if (m_fSystemLog.Read(tTime, nInfo[0]))
					{
						if (tTime >= tStartTime.GetTime())
						{
							if ((pEvent = new CEventObject))
							{
								if (cCompressionTools.Decompress(nInfo[0], nInfo[1]) && pEvent->Unmap(nInfo[1]) && pEventList->Add(pEvent) >= 0)
								{
									nIndex++;
									continue;
								}
								delete pEvent;
							}
							dwResult = (DWORD)-1;
							break;
						}
						continue;
					}
					break;
				}
				if (dwResult != WAIT_TIMEOUT)
				{
					delete pEventList;
					return FALSE;
				}
			}
		}
		if (nEventLogs & EVENTLOG_CATEGORY_SPACECRAFT)
		{
			if (m_fSpacecraftLog.SeekTo(tStartTime))
			{
				for (pEventList->EnableSound(FALSE), nIndex = 0; (dwResult = (hAbort != (HANDLE)NULL) ? WaitForSingleObject(hAbort, 0) : WAIT_TIMEOUT) == WAIT_TIMEOUT && (nIndex < nCount || nCount < 0); )
				{
					if (m_fSpacecraftLog.Read(tTime, nInfo[0]))
					{
						if (tTime >= tStartTime.GetTime())
						{
							if ((pEvent = new CEventObject))
							{
								if (cCompressionTools.Decompress(nInfo[0], nInfo[1]) && pEvent->Unmap(nInfo[1]) && pEventList->Add(pEvent) >= 0)
								{
									nIndex++;
									continue;
								}
								delete pEvent;
							}
							dwResult = (DWORD)-1;
							break;
						}
						continue;
					}
					break;
				}
				if (dwResult != WAIT_TIMEOUT)
				{
					delete pEventList;
					return FALSE;
				}
			}
		}
		if (nEventLogs & EVENTLOG_CATEGORY_USER)
		{
			if (m_fUserLog.SeekTo(tStartTime))
			{
				for (pEventList->EnableSound(FALSE), nIndex = 0; (dwResult = (hAbort != (HANDLE)NULL) ? WaitForSingleObject(hAbort, 0) : WAIT_TIMEOUT) == WAIT_TIMEOUT && (nIndex < nCount || nCount < 0); )
				{
					if (m_fUserLog.Read(tTime, nInfo[0]))
					{
						if (tTime >= tStartTime.GetTime())
						{
							if ((pEvent = new CEventObject))
							{
								if (cCompressionTools.Decompress(nInfo[0], nInfo[1]) && pEvent->Unmap(nInfo[1]) && pEventList->Add(pEvent) >= 0)
								{
									nIndex++;
									continue;
								}
								delete pEvent;
							}
							dwResult = (DWORD)-1;
							break;
						}
						continue;
					}
					break;
				}
				if (dwResult != WAIT_TIMEOUT)
				{
					delete pEventList;
					return FALSE;
				}
			}
		}
		if (cEventList.Lock())
		{
			for (cEventList.EnableSound(FALSE); pEventList->GetSize() > nCount && nCount >= 0; )
			{
				if ((pEvent = pEventList->GetAt((nIndex = (INT)pEventList->GetUpperBound()))) && pEventList->Remove(nIndex))
				{
					delete pEvent;
					continue;
				}
				break;
			}
			if (pEventList->GetSize() <= nCount || nCount < 0)
			{
				if (cEventList.Copy(pEventList))
				{
					cEventList.Unlock();
					delete pEventList;
					return TRUE;
				}
			}
			cEventList.Unlock();
		}
		delete pEventList;
	}
	return FALSE;
}
BOOL CEventLog::Read(CEventList &cEventList, CONST CTimeKey &tStartTime, CONST CTimeKey &tEndTime, UINT nEventLogs, HANDLE hAbort)
{
	DWORD  dwResult;
	CTimeKey  tTime;
	CByteArray  nInfo[2];
	CEventObject  *pEvent;
	CCompressionTools  cCompressionTools;

	if (cEventList.Lock())
	{
		if (tStartTime <= tEndTime)
		{
			if (nEventLogs & EVENTLOG_CATEGORY_SYSTEM)
			{
				if (m_fSystemLog.SeekTo(tStartTime))
				{
					for (cEventList.EnableSound(FALSE); (dwResult = (hAbort != (HANDLE)NULL) ? WaitForSingleObject(hAbort, 0) : WAIT_TIMEOUT) == WAIT_TIMEOUT; )
					{
						if (m_fSystemLog.Read(tTime, nInfo[0]))
						{
							if (tTime <= tEndTime.GetTime())
							{
								if (tTime >= tStartTime)
								{
									if ((pEvent = new CEventObject))
									{
										if (cCompressionTools.Decompress(nInfo[0], nInfo[1]) && pEvent->Unmap(nInfo[1]) && cEventList.Add(pEvent) >= 0) continue;
										delete pEvent;
									}
									dwResult = (DWORD)-1;
									break;
								}
								continue;
							}
						}
						break;
					}
					if (dwResult != WAIT_TIMEOUT)
					{
						cEventList.Unlock();
						return FALSE;
					}
				}
			}
			if (nEventLogs & EVENTLOG_CATEGORY_SPACECRAFT)
			{
				if (m_fSpacecraftLog.SeekTo(tStartTime))
				{
					for (cEventList.EnableSound(FALSE); (dwResult = (hAbort != (HANDLE)NULL) ? WaitForSingleObject(hAbort, 0) : WAIT_TIMEOUT) == WAIT_TIMEOUT; )
					{
						if (m_fSpacecraftLog.Read(tTime, nInfo[0]))
						{
							if (tTime <= tEndTime.GetTime())
							{
								if (tTime >= tStartTime)
								{
									if ((pEvent = new CEventObject))
									{
										if (cCompressionTools.Decompress(nInfo[0], nInfo[1]) && pEvent->Unmap(nInfo[1]) && cEventList.Add(pEvent) >= 0) continue;
										delete pEvent;
									}
									dwResult = (DWORD)-1;
									break;
								}
								continue;
							}
						}
						break;
					}
					if (dwResult != WAIT_TIMEOUT)
					{
						cEventList.Unlock();
						return FALSE;
					}
				}
			}
			if (nEventLogs & EVENTLOG_CATEGORY_USER)
			{
				if (m_fUserLog.SeekTo(tStartTime))
				{
					for (cEventList.EnableSound(FALSE); (dwResult = (hAbort != (HANDLE)NULL) ? WaitForSingleObject(hAbort, 0) : WAIT_TIMEOUT) == WAIT_TIMEOUT; )
					{
						if (m_fUserLog.Read(tTime, nInfo[0]))
						{
							if (tTime <= tEndTime.GetTime())
							{
								if (tTime >= tStartTime)
								{
									if ((pEvent = new CEventObject))
									{
										if (cCompressionTools.Decompress(nInfo[0], nInfo[1]) && pEvent->Unmap(nInfo[1]) && cEventList.Add(pEvent) >= 0) continue;
										delete pEvent;
									}
									dwResult = (DWORD)-1;
									break;
								}
								continue;
							}
						}
						break;
					}
					if (dwResult != WAIT_TIMEOUT)
					{
						cEventList.Unlock();
						return FALSE;
					}
				}
			}
			cEventList.Unlock();
			return TRUE;
		}
		cEventList.Unlock();
	}
	return FALSE;
}

BOOL CEventLog::ReadAll(CEventList &cEventList, UINT nEventLogs, HANDLE hAbort)
{
	DWORD  dwResult;
	CTimeKey  tTime;
	CByteArray  nInfo[2];
	CEventList  *pEventList;
	CEventObject  *pEvent;
	CCompressionTools  cCompressionTools;

	if ((pEventList = new CEventList))
	{
		if (nEventLogs & EVENTLOG_CATEGORY_SYSTEM)
		{
			if (m_fSystemLog.SeekToFirst())
			{
				for (pEventList->EnableSound(FALSE); (dwResult = (hAbort != (HANDLE)NULL) ? WaitForSingleObject(hAbort, 0) : WAIT_TIMEOUT) == WAIT_TIMEOUT; )
				{
					if (m_fSystemLog.Read(tTime, nInfo[0]))
					{
						if ((pEvent = new CEventObject))
						{
							if (cCompressionTools.Decompress(nInfo[0], nInfo[1]) && pEvent->Unmap(nInfo[1]) && pEventList->Add(pEvent) >= 0) continue;
							delete pEvent;
						}
						dwResult = (DWORD)-1;
					}
					break;
				}
				if (dwResult != WAIT_TIMEOUT)
				{
					delete pEventList;
					return FALSE;
				}
			}
		}
		if (nEventLogs & EVENTLOG_CATEGORY_SPACECRAFT)
		{
			if (m_fSpacecraftLog.SeekToFirst())
			{
				for (pEventList->EnableSound(FALSE); (dwResult = (hAbort != (HANDLE)NULL) ? WaitForSingleObject(hAbort, 0) : WAIT_TIMEOUT) == WAIT_TIMEOUT; )
				{
					if (m_fSpacecraftLog.Read(tTime, nInfo[0]))
					{
						if ((pEvent = new CEventObject))
						{
							if (cCompressionTools.Decompress(nInfo[0], nInfo[1]) && pEvent->Unmap(nInfo[1]) && pEventList->Add(pEvent) >= 0) continue;
							delete pEvent;
						}
						dwResult = (DWORD)-1;
					}
					break;
				}
				if (dwResult != WAIT_TIMEOUT)
				{
					delete pEventList;
					return FALSE;
				}
			}
		}
		if (nEventLogs & EVENTLOG_CATEGORY_USER)
		{
			if (m_fUserLog.SeekToFirst())
			{
				for (pEventList->EnableSound(FALSE); (dwResult = (hAbort != (HANDLE)NULL) ? WaitForSingleObject(hAbort, 0) : WAIT_TIMEOUT) == WAIT_TIMEOUT; )
				{
					if (m_fUserLog.Read(tTime, nInfo[0]))
					{
						if ((pEvent = new CEventObject))
						{
							if (cCompressionTools.Decompress(nInfo[0], nInfo[1]) && pEvent->Unmap(nInfo[1]) && pEventList->Add(pEvent) >= 0) continue;
							delete pEvent;
						}
						dwResult = (DWORD)-1;
					}
					break;
				}
				if (dwResult != WAIT_TIMEOUT)
				{
					delete pEventList;
					return FALSE;
				}
			}
		}
		if (cEventList.Lock())
		{
			if (cEventList.Copy(pEventList))
			{
				cEventList.Unlock();
				delete pEventList;
				return TRUE;
			}
			cEventList.Unlock();
		}
		delete pEventList;
	}
	return FALSE;
}

BOOL CEventLog::CanFlush() CONST
{
	return((m_fSystemLog.IsLocked() || m_fSpacecraftLog.IsLocked() || m_fUserLog.IsLocked()) ? (m_pBufferData.GetSize() > 0) : FALSE);
}

BOOL CEventLog::FlushAll()
{
	INT  nEvent;
	INT  nEvents;
	BOOL  bFlush;
	UINT  nCategory;
	CByteArray  nInfo[2];
	CEventObject  *pEvent;
	CCompressionTools  cCompressionTools;

	for (nEvent = 0, nEvents = (CanFlush()) ? (INT)m_pBufferData.GetSize() : 0, bFlush = TRUE; nEvent < nEvents; nEvent++)
	{
		if ((pEvent = m_pBufferData.GetAt(nEvent)) && pEvent->Map(nInfo[0]) && cCompressionTools.Compress(nInfo[0], nInfo[1]) > 0)
		{
			if ((((nCategory = pEvent->GetCategory()) == EVENT_CATEGORY_SYSTEM  &&  !m_bBuffering[0] && m_fSystemLog.Write(pEvent->GetAuditTime(), nInfo[1])) || (nCategory == EVENT_CATEGORY_SPACECRAFT  &&  !m_bBuffering[1] && m_fSpacecraftLog.Write(pEvent->GetAuditTime(), nInfo[1])) || (nCategory == EVENT_CATEGORY_USER  &&  !m_bBuffering[2] && m_fUserLog.Write(pEvent->GetAuditTime(), nInfo[1]))))
			{
				m_pBufferData.Remove(nEvent);
				delete pEvent;
				nEvents--;
				nEvent--;
				continue;
			}
			bFlush = ((nCategory == EVENT_CATEGORY_SYSTEM && (!m_fSystemLog.IsLocked() || m_bBuffering[0])) || (nCategory == EVENT_CATEGORY_SPACECRAFT && (!m_fSpacecraftLog.IsLocked() || m_bBuffering[1])) || (nCategory == EVENT_CATEGORY_USER && (!m_fUserLog.IsLocked() || m_bBuffering[2]))) ? bFlush : FALSE;
			continue;
		}
		m_pBufferData.Remove(nEvent);
		bFlush = FALSE;
		delete pEvent;
		nEvents--;
		nEvent--;
	}
	return bFlush;
}

INT CEventLog::BeginWatch(UINT nEventLogs, LPHANDLE phEventLogs, INT nCount)
{
	INT  nEventLogCount[2];
	HANDLE  hEventLogs[EVENTLOG_CATEGORIES];

	for (nEventLogCount[0] = nEventLogCount[1] = 0, nEventLogCount[0] = (nEventLogs & EVENTLOG_CATEGORY_SYSTEM) ? (nEventLogCount[0] + 1) : nEventLogCount[0], nEventLogCount[0] = (nEventLogs & EVENTLOG_CATEGORY_SPACECRAFT) ? (nEventLogCount[0] + 1) : nEventLogCount[0], nEventLogCount[0] = (nEventLogs & EVENTLOG_CATEGORY_USER) ? (nEventLogCount[0] + 1) : nEventLogCount[0]; nEventLogCount[0] <= nCount; )
	{
		if (nEventLogs & EVENTLOG_CATEGORY_SYSTEM)
		{
			hEventLogs[nEventLogCount[1]] = m_fSystemLog.BeginWatch();
			nEventLogCount[1]++;
		}
		if (nEventLogs & EVENTLOG_CATEGORY_SPACECRAFT)
		{
			hEventLogs[nEventLogCount[1]] = m_fSpacecraftLog.BeginWatch();
			nEventLogCount[1]++;
		}
		if (nEventLogs & EVENTLOG_CATEGORY_USER)
		{
			hEventLogs[nEventLogCount[1]] = m_fUserLog.BeginWatch();
			nEventLogCount[1]++;
		}
		for (nEventLogCount[0] = 0; nEventLogCount[0] < nEventLogCount[1]; nEventLogCount[0]++)
		{
			if (!hEventLogs[nEventLogCount[0]])
			{
				nEventLogCount[0] = 0;
				break;
			}
		}
		if (!nEventLogCount[0])
		{
			if (nEventLogs & EVENTLOG_CATEGORY_SYSTEM)
			{
				if (hEventLogs[nEventLogCount[0]]) m_fSystemLog.EndWatch();
				nEventLogCount[0]++;
			}
			if (nEventLogs & EVENTLOG_CATEGORY_SPACECRAFT)
			{
				if (hEventLogs[nEventLogCount[0]]) m_fSpacecraftLog.EndWatch();
				nEventLogCount[0]++;
			}
			if (nEventLogs & EVENTLOG_CATEGORY_USER)
			{
				if (hEventLogs[nEventLogCount[0]]) m_fUserLog.EndWatch();
				nEventLogCount[0]++;
			}
			return 0;
		}
		for (nEventLogCount[0] = 0; nEventLogCount[0] < nEventLogCount[1]; nEventLogCount[0]++)
		{
			phEventLogs[nEventLogCount[0]] = hEventLogs[nEventLogCount[0]];
			continue;
		}
		return nEventLogCount[1];
	}
	return((!nCount) ? nEventLogCount[0] : 0);
}

BOOL CEventLog::Watch(UINT nEventLogs, CEventList &cEventList)
{
	CByteArray  nInfo[2];
	CEventObject  *pEvent;
	CCompressionTools  cCompressionTools;

	if (cEventList.Lock())
	{
		if (nEventLogs & EVENTLOG_CATEGORY_SYSTEM)
		{
			for (cEventList.EnableSound(FALSE); m_fSystemLog.Watch(nInfo[0]); )
			{
				if ((pEvent = new CEventObject) != (CEventObject *)NULL)
				{
					if (cCompressionTools.Decompress(nInfo[0], nInfo[1]) && pEvent->Unmap(nInfo[1]) && cEventList.Add(pEvent) >= 0) continue;
					delete pEvent;
				}
				break;
			}
		}
		if (nEventLogs & EVENTLOG_CATEGORY_SPACECRAFT)
		{
			for (cEventList.EnableSound(FALSE); m_fSpacecraftLog.Watch(nInfo[0]); )
			{
				if ((pEvent = new CEventObject) != (CEventObject *)NULL)
				{
					if (cCompressionTools.Decompress(nInfo[0], nInfo[1]) && pEvent->Unmap(nInfo[1]) && cEventList.Add(pEvent) >= 0) continue;
					delete pEvent;
				}
				break;
			}
		}
		if (nEventLogs & EVENTLOG_CATEGORY_USER)
		{
			for (cEventList.EnableSound(FALSE); m_fUserLog.Watch(nInfo[0]); )
			{
				if ((pEvent = new CEventObject) != (CEventObject *)NULL)
				{
					if (cCompressionTools.Decompress(nInfo[0], nInfo[1]) && pEvent->Unmap(nInfo[1]) && cEventList.Add(pEvent) >= 0) continue;
					delete pEvent;
				}
				break;
			}
		}
		cEventList.Unlock();
		return TRUE;
	}
	return FALSE;
}

BOOL CEventLog::EndWatch(UINT nEventLogs)
{
	return(((!(nEventLogs & EVENTLOG_CATEGORY_SYSTEM) || m_fSystemLog.EndWatch()) && (!(nEventLogs & EVENTLOG_CATEGORY_SPACECRAFT) || m_fSpacecraftLog.EndWatch()) && (!(nEventLogs & EVENTLOG_CATEGORY_USER) || m_fUserLog.EndWatch())) ? TRUE : FALSE);
}

BOOL CEventLog::Report(CONST CEventObject *pEvent)
{
	CStringArray  szArguments;

	for (szArguments.Add(pEvent->GetMessage()); pEvent->GetCategory() == EVENT_CATEGORY_SYSTEM; )
	{
		if (pEvent->GetType() == STRING(IDS_EVENTTYPE_ERROR)) return Report(SYSTEM_ERROR_MESSAGE, szArguments);
		if (pEvent->GetType() == STRING(IDS_EVENTTYPE_WARNING)) return Report(SYSTEM_WARNING_MESSAGE, szArguments);
		return Report(SYSTEM_INFORMATIONAL_MESSAGE, szArguments);
	}
	if (pEvent->GetCategory() == EVENT_CATEGORY_SPACECRAFT)
	{
		if (pEvent->GetType() == STRING(IDS_EVENTTYPE_ERROR)) return Report(SPACECRAFT_ERROR_MESSAGE, szArguments);
		if (pEvent->GetType() == STRING(IDS_EVENTTYPE_WARNING)) return Report(SPACECRAFT_WARNING_MESSAGE, szArguments);
		return Report(SPACECRAFT_INFORMATIONAL_MESSAGE, szArguments);
	}
	if (pEvent->GetCategory() == EVENT_CATEGORY_USER)
	{
		if (pEvent->GetType() == STRING(IDS_EVENTTYPE_ERROR)) return Report(USER_ERROR_MESSAGE, szArguments);
		if (pEvent->GetType() == STRING(IDS_EVENTTYPE_WARNING)) return Report(USER_WARNING_MESSAGE, szArguments);
		return Report(USER_INFORMATIONAL_MESSAGE, szArguments);
	}
	return FALSE;
}
BOOL CEventLog::Report(EVENT_DESCRIPTOR sEvent)
{
	CStringArray  szArguments;

	return Report(sEvent, szArguments);
}
BOOL CEventLog::Report(EVENT_DESCRIPTOR sEvent, CONST CStringArray &szArguments)
{
	INT  nArgument;
	INT  nArguments;
	LPWSTR  *pszArguments;
	CString  szEventMessage;
	REGHANDLE  hEventProvider;
	EVENT_DATA_DESCRIPTOR  *pEventData;

	if (sEvent.Opcode != 0)
	{
		if (EventRegister(&SATVIEW_EVENTLOGPROVIDER, (PENABLECALLBACK)NULL, (PVOID)NULL, &hEventProvider) == ERROR_SUCCESS)
		{
			if ((pEventData = (szArguments.GetSize() > 0) ? (EVENT_DATA_DESCRIPTOR *)GlobalAlloc(GPTR, szArguments.GetSize()*sizeof(EVENT_DATA_DESCRIPTOR)) : (EVENT_DATA_DESCRIPTOR *)NULL))
			{
				if ((pszArguments = (LPWSTR *)GlobalAlloc(GPTR, (szArguments.GetSize()*sizeof(LPCWSTR)))))
				{
					for (nArgument = 0, nArguments = (INT)szArguments.GetSize(); nArgument < nArguments; nArgument++)
					{
						if ((pszArguments[nArgument] = (LPWSTR)GlobalAlloc(GPTR, (szArguments.GetAt(nArgument).GetLength() + 1)*sizeof(WCHAR))))
						{
#ifndef UNICODE
							MultiByteToWideChar(CP_ACP, 0, szArguments.GetAt(nArgument), -1, pszArguments[nArgument], szArguments.GetAt(nArgument).GetLength() + 1);
#else
							wcscpy_s(pszArguments[nArgument], szArguments.GetAt(nArgument).GetLength() + 1, szArguments.GetAt(nArgument));
#endif
							EventDataDescCreate(&pEventData[nArgument], pszArguments[nArgument], (szArguments.GetAt(nArgument).GetLength() + 1)*sizeof(WCHAR));
							continue;
						}
						break;
					}
					if (nArgument == nArguments)
					{
						if (EventWrite(hEventProvider, &sEvent, nArguments, pEventData) == ERROR_SUCCESS)
						{
							for (nArgument--; nArgument >= 0; nArgument--)
							{
								GlobalFree(pszArguments[nArgument]);
								continue;
							}
							EventUnregister(hEventProvider);
							GlobalFree(pszArguments);
							GlobalFree(pEventData);
							return TRUE;
						}
					}
					for (nArgument--; nArgument >= 0; nArgument--)
					{
						GlobalFree(pszArguments[nArgument]);
						continue;
					}
					GlobalFree(pszArguments);
				}
				EventUnregister(hEventProvider);
				GlobalFree(pEventData);
				return FALSE;
			}
			if (!szArguments.GetSize())
			{
				if (EventWrite(hEventProvider, &sEvent, 0, (PEVENT_DATA_DESCRIPTOR)NULL) == ERROR_SUCCESS)
				{
					EventUnregister(hEventProvider);
					return TRUE;
				}
			}
			EventUnregister(hEventProvider);
		}
		return FALSE;
	}
	return TRUE;
}

BOOL CEventLog::QuerySystemLogFileName(CString &szFileName) CONST
{
	INT  nPos;
	CString  szSubKey;
	CString  szLogFile;
	CVersionInfo  cVersionInfo;
	CRegistry  cRegistry;

	if (cRegistry.SetComputerName(GetComputerName()) && QuerySystemLogSubKey(szSubKey))
	{
		if (cRegistry.GetMachineInfo(szSubKey, STRING(IDS_REG_SUBKEYVALUE_SYSTEMEVENTLOGNAME), szLogFile) > 0 || QueryDefaultSystemLogName(szLogFile))
		{
			if (IsHost())
			{
				szFileName = szLogFile;
				return TRUE;
			}
			if ((nPos = szLogFile.Find(STRINGCHAR(IDS_FILENAME_ALL) + cVersionInfo.QueryInternalName() + STRINGCHAR(IDS_FILENAME_ALL))) >= 0)
			{
				szFileName = GetComputerUNCName() + szLogFile.Mid(nPos);
				return TRUE;
			}
			if ((nPos = szLogFile.Find(cVersionInfo.QueryInternalName() + STRINGCHAR(IDS_FILENAME_ALL))) >= 0)
			{
				szFileName = GetComputerUNCName() + STRINGCHAR(IDS_FILENAME_ALL) + szLogFile.Mid(nPos);
				return TRUE;
			}
			szFileName.Format(STRING(IDS_EVENTLOG_SYSTEMFILENAME), (LPCTSTR)GetComputerUNCName(), (LPCTSTR)GetComputerName());
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CEventLog::QueryGlobalSpacecraftLogFileName(CString &szFileName) CONST
{
	INT  nPos;
	CString  szSubKey;
	CString  szLogFile;
	CVersionInfo  cVersionInfo;
	CRegistry  cRegistry;

	if (cRegistry.SetComputerName(GetComputerName()) && QuerySpacecraftLogSubKey(szSubKey))
	{
		if (cRegistry.GetMachineInfo(szSubKey, STRING(IDS_REG_SUBKEYVALUE_GLOBALSPACECRAFTEVENTLOGNAME), szLogFile) > 0 || QueryDefaultSpacecraftLogName(szLogFile))
		{
			if (IsHost())
			{
				szFileName = szLogFile;
				return TRUE;
			}
			if ((nPos = szLogFile.Find(STRINGCHAR(IDS_FILENAME_ALL) + cVersionInfo.QueryInternalName() + STRINGCHAR(IDS_FILENAME_ALL))) >= 0)
			{
				szFileName = GetComputerUNCName() + szLogFile.Mid(nPos);
				return TRUE;
			}
			if ((nPos = szLogFile.Find(cVersionInfo.QueryInternalName() + STRINGCHAR(IDS_FILENAME_ALL))) >= 0)
			{
				szFileName = GetComputerUNCName() + STRINGCHAR(IDS_FILENAME_ALL) + szLogFile.Mid(nPos);
				return TRUE;
			}
			szFileName.Format(STRING(IDS_EVENTLOG_SPACECRAFTFILENAME), (LPCTSTR)GetComputerUNCName(), (LPCTSTR)GetSpacecraftName(), (LPCTSTR)GetSpacecraftName());
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CEventLog::QuerySpacecraftLogFileName(CString &szFileName) CONST
{
	INT  nPos;
	CString  szSubKey;
	CString  szLogFile;
	CVersionInfo  cVersionInfo;
	CRegistry  cRegistry;

	if (cRegistry.SetComputerName(GetComputerName()) && QuerySpacecraftLogSubKey(szSubKey))
	{
		if (cRegistry.GetMachineInfo(szSubKey, STRING(IDS_REG_SUBKEYVALUE_SPACECRAFTEVENTLOGNAME), szLogFile) > 0 || QueryDefaultSpacecraftLogName(szLogFile))
		{
			if (IsHost())
			{
				szFileName = szLogFile;
				return TRUE;
			}
			if ((nPos = szLogFile.Find(STRINGCHAR(IDS_FILENAME_ALL) + cVersionInfo.QueryInternalName() + STRINGCHAR(IDS_FILENAME_ALL))) >= 0)
			{
				szFileName = GetComputerUNCName() + szLogFile.Mid(nPos);
				return TRUE;
			}
			if ((nPos = szLogFile.Find(cVersionInfo.QueryInternalName() + STRINGCHAR(IDS_FILENAME_ALL))) >= 0)
			{
				szFileName = GetComputerUNCName() + STRINGCHAR(IDS_FILENAME_ALL) + szLogFile.Mid(nPos);
				return TRUE;
			}
			szFileName.Format(STRING(IDS_EVENTLOG_SPACECRAFTFILENAME), (LPCTSTR)GetComputerUNCName(), (LPCTSTR)GetSpacecraftName(), (LPCTSTR)GetSpacecraftName());
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CEventLog::QueryUserLogFileName(CString &szFileName) CONST
{
	INT  nPos;
	CString  szSubKey;
	CString  szLogFile;
	CVersionInfo  cVersionInfo;
	CRegistry  cRegistry;

	if (cRegistry.SetComputerName(GetComputerName()) && QueryUserLogSubKey(szSubKey))
	{
		if (cRegistry.GetMachineInfo(szSubKey, STRING(IDS_REG_SUBKEYVALUE_USEREVENTLOGNAME), szLogFile) > 0 || QueryDefaultUserLogName(szLogFile))
		{
			if (IsHost())
			{
				szFileName = szLogFile;
				return TRUE;
			}
			if ((nPos = szLogFile.Find(STRINGCHAR(IDS_FILENAME_ALL) + cVersionInfo.QueryInternalName() + STRINGCHAR(IDS_FILENAME_ALL))) >= 0)
			{
				szFileName = GetComputerUNCName() + szLogFile.Mid(nPos);
				return TRUE;
			}
			if ((nPos = szLogFile.Find(cVersionInfo.QueryInternalName() + STRINGCHAR(IDS_FILENAME_ALL))) >= 0)
			{
				szFileName = GetComputerUNCName() + STRINGCHAR(IDS_FILENAME_ALL) + szLogFile.Mid(nPos);
				return TRUE;
			}
			szFileName.Format(STRING(IDS_EVENTLOG_USERFILENAME), (LPCTSTR)GetComputerUNCName(), (LPCTSTR)GetSpacecraftName(), (LPCTSTR)GetUserName(), (LPCTSTR)GetUserName());
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CEventLog::QuerySystemLogSubKey(CString &szSubKey) CONST
{
	CVersionInfo  cVersionInfo;

	if (HasOwner())
	{
		szSubKey = STRING(IDS_REG_SUBKEYPART_ROOTKEY) + cVersionInfo.QueryCompanyName();
		szSubKey += STRING(IDS_REG_SUBKEYPART_DELIMITER) + cVersionInfo.QueryProductName();
		return TRUE;
	}
	return FALSE;
}

BOOL CEventLog::QuerySpacecraftLogSubKey(CString &szSubKey) CONST
{
	CString  szSystemLogSubKey;

	if (QuerySystemLogSubKey(szSystemLogSubKey))
	{
		szSubKey = szSystemLogSubKey + STRING(IDS_REG_SUBKEYPART_DELIMITER);
		szSubKey += GetSpacecraftName();
		return TRUE;
	}
	return FALSE;
}

BOOL CEventLog::QueryUserLogSubKey(CString &szSubKey) CONST
{
	CString  szSpacecraftLogSubKey;

	if (QuerySpacecraftLogSubKey(szSpacecraftLogSubKey))
	{
		szSubKey = szSpacecraftLogSubKey + STRING(IDS_REG_SUBKEYPART_DELIMITER);
		szSubKey += GetUserName();
		return TRUE;
	}
	return FALSE;
}

BOOL CEventLog::QueryDefaultSystemLogName(CString &szName) CONST
{
	INT  nPos;
	CString  szDirectory;
	CString  szInternalName;
	CModuleToken  cModuleToken;
	CVersionInfo  cVersionInfo;

	if (HasOwner())
	{
		if ((nPos = (szDirectory = cModuleToken.GetModuleFileRoot()).Find((szInternalName = STRINGCHAR(IDS_FILENAME_ALL) + cVersionInfo.QueryInternalName() + STRINGCHAR(IDS_FILENAME_ALL)))) >= 0)
		{
			szName.Format(STRING(IDS_EVENTLOG_SYSTEMFILENAME), (LPCTSTR)szDirectory.Left(nPos + szInternalName.GetLength() - 1), (LPCTSTR)GetComputerName());
			return TRUE;
		}
		if ((nPos = szDirectory.Find((szInternalName = szInternalName.Left(szInternalName.GetLength() - 1)))) >= 0 && nPos + szInternalName.GetLength() == szDirectory.GetLength())
		{
			szName.Format(STRING(IDS_EVENTLOG_SYSTEMFILENAME), (LPCTSTR)szDirectory.Left(nPos + szInternalName.GetLength()), (LPCTSTR)GetComputerName());
			return TRUE;
		}
		szName.Format(STRING(IDS_EVENTLOG_SYSTEMFILENAME), (LPCTSTR)szDirectory, (LPCTSTR)GetComputerName());
		return TRUE;
	}
	return FALSE;
}

BOOL CEventLog::QueryDefaultSpacecraftLogName(CString &szName) CONST
{
	INT  nPos;
	CString  szDirectory;
	CString  szInternalName;
	CModuleToken  cModuleToken;
	CVersionInfo  cVersionInfo;

	if (HasOwner())
	{
		if ((nPos = (szDirectory = cModuleToken.GetModuleFileRoot()).Find((szInternalName = STRINGCHAR(IDS_FILENAME_ALL) + cVersionInfo.QueryInternalName() + STRINGCHAR(IDS_FILENAME_ALL)))) >= 0)
		{
			szName.Format(STRING(IDS_EVENTLOG_SPACECRAFTFILENAME), (LPCTSTR)szDirectory.Left(nPos + szInternalName.GetLength() - 1), (LPCTSTR)GetSpacecraftName(), (LPCTSTR)GetSpacecraftName());
			return TRUE;
		}
		if ((nPos = szDirectory.Find((szInternalName = szInternalName.Left(szInternalName.GetLength() - 1)))) >= 0 && nPos + szInternalName.GetLength() == szDirectory.GetLength())
		{
			szName.Format(STRING(IDS_EVENTLOG_SPACECRAFTFILENAME), (LPCTSTR)szDirectory.Left(nPos + szInternalName.GetLength()), (LPCTSTR)GetSpacecraftName(), (LPCTSTR)GetSpacecraftName());
			return TRUE;
		}
		szName.Format(STRING(IDS_EVENTLOG_SPACECRAFTFILENAME), (LPCTSTR)szDirectory, (LPCTSTR)GetSpacecraftName(), (LPCTSTR)GetSpacecraftName());
		return TRUE;
	}
	return FALSE;
}

BOOL CEventLog::QueryDefaultUserLogName(CString &szName) CONST
{
	INT  nPos;
	CString  szDirectory;
	CString  szInternalName;
	CModuleToken  cModuleToken;
	CVersionInfo  cVersionInfo;

	if (HasOwner())
	{
		if ((nPos = (szDirectory = cModuleToken.GetModuleFileRoot()).Find((szInternalName = STRINGCHAR(IDS_FILENAME_ALL) + cVersionInfo.QueryInternalName() + STRINGCHAR(IDS_FILENAME_ALL)))) >= 0)
		{
			szName.Format(STRING(IDS_EVENTLOG_USERFILENAME), (LPCTSTR)szDirectory.Left(nPos + szInternalName.GetLength() - 1), (LPCTSTR)GetSpacecraftName(), (LPCTSTR)GetUserName(), (LPCTSTR)GetUserName());
			return TRUE;
		}
		if ((nPos = szDirectory.Find((szInternalName = szInternalName.Left(szInternalName.GetLength() - 1)))) >= 0 && nPos + szInternalName.GetLength() == szDirectory.GetLength())
		{
			szName.Format(STRING(IDS_EVENTLOG_USERFILENAME), (LPCTSTR)szDirectory.Left(nPos + szInternalName.GetLength()), (LPCTSTR)GetSpacecraftName(), (LPCTSTR)GetUserName(), (LPCTSTR)GetUserName());
			return TRUE;
		}
		szName.Format(STRING(IDS_EVENTLOG_USERFILENAME), (LPCTSTR)szDirectory, (LPCTSTR)GetSpacecraftName(), (LPCTSTR)GetUserName(), (LPCTSTR)GetUserName());
		return TRUE;
	}
	return FALSE;
}

BOOL CEventLog::TestDirectory(LPCTSTR pszFileName) CONST
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
	for (nPos = lstrlen(szFileName), szDrive = cDrives.ExtractDrive(szFileName), GetFileTitle(szFileName, szFileTitle.GetBufferSetLength(max(GetFileTitle(szFileName, (LPTSTR)NULL, 0) - 1, 0)), ::GetFileTitle(szFileName, (LPTSTR)NULL, 0)), szFileTitle.ReleaseBuffer(), nPos -= szFileTitle.GetLength(), szFilePath = (nPos > 0) ? szFileName : EMPTYSTRING; nPos >= 0; nPos--)
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

BOOL CEventLog::CheckSecurity(LPCTSTR pszFileName) CONST
{
	CSecurityDescriptor  cSecurityDescriptor;

	return((cSecurityDescriptor.SetRightsOfSystem(FILE_ALL_ACCESS) && cSecurityDescriptor.SetRightsOfAdministrators(FILE_ALL_ACCESS) && (cSecurityDescriptor.SetRightsOfSystemOperators(FILE_GENERIC_READ | FILE_GENERIC_WRITE) || cSecurityDescriptor.SetRightsOfPowerUsers(FILE_GENERIC_READ | FILE_GENERIC_WRITE)) && cSecurityDescriptor.SetRightsOfAuthenticatedUsers(FILE_GENERIC_READ) && cSecurityDescriptor.SetRightsOfEveryone(FILE_GENERIC_READ) && CSecurity::SecureFile(CFileEx::TranslateToUNCName(pszFileName), cSecurityDescriptor)) ? TRUE : FALSE);
}
