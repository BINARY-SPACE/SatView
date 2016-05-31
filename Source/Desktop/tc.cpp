// TC.CPP : Telecommand Data Processing Related Interface Definition.
//
// This is a part of the SatView(TM) spacecraft operating system.
// Copyright© 1992-2016 by BINARY SPACE, Switzerland.
// All rights reserved.
//
// This source code contains the definition of the telecommand data
// processing related interface.
//
/**********************************************************************
* Modifications:                                                     *
*====================================================================*
* Date       | Release | Comments                                    *
*------------|---------|---------------------------------------------*
* 2007/04/23 | 1.00.00 | Initial creation. [AW]                      *
**********************************************************************/

#include "SatView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CTCServiceLock

CTCServiceLock::CTCServiceLock(CONST CDisplayWnd *pDisplayWnd)
{
	if ((m_pLockable = (CDisplayLockable *)pDisplayWnd))
	{
		Lock();
		return;
	}
}

CTCServiceLock::~CTCServiceLock()
{
	if (m_pLockable != (CDisplayLockable *)NULL)
	{
		Unlock();
		return;
	}
}

VOID CTCServiceLock::Release()
{
	if (m_pLockable != (CDisplayLockable *)NULL) Unlock();
	m_pLockable = (CDisplayLockable *)NULL;
}

BOOL CTCServiceLock::Lock()
{
	return GetTCService()->Lock() && m_pLockable->Lock();
}

BOOL CTCServiceLock::Unlock()
{
	return m_pLockable->Unlock() && GetTCService()->Unlock();
}


/////////////////////////////////////////////////////////////////////////////
// CTCChainLock

CTCChainLock::CTCChainLock(CONST CThread *pThread)
{
	if ((m_pThread = (CThread *)pThread))
	{
		Lock();
		return;
	}
}

CTCChainLock::~CTCChainLock()
{
	if (m_pThread)
	{
		Unlock();
		return;
	}
}

VOID CTCChainLock::Release()
{
	if (m_pThread) Unlock();
	m_pThread = (CThread *)NULL;
}

BOOL CTCChainLock::Lock()
{
	return m_pThread->Lock();
}

BOOL CTCChainLock::Unlock()
{
	return m_pThread->Unlock();
}


/////////////////////////////////////////////////////////////////////////////
// CTCInterlock

CTCInterlock::CTCInterlock() : CComputerToken()
{
	m_nSourceType = TCINTERLOCK_SOURCETYPE_NONE;
	m_nScope = TCINTERLOCK_SCOPE_NONE;
	m_nStage = TCINTERLOCK_STAGE_NONE;
	m_nState = TCINTERLOCK_STATE_NONE;
}

VOID CTCInterlock::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CTCInterlock::GetName() CONST
{
	return((IsAutomatic()) ? ConstructDefaultName(CComputerToken().GetComputerName(), m_nSourceType, m_nScope, m_nStage) : m_szName);
}

VOID CTCInterlock::SetSourceType(UINT nType)
{
	m_nSourceType = nType;
}

UINT CTCInterlock::GetSourceType() CONST
{
	return m_nSourceType;
}

VOID CTCInterlock::SetScope(UINT nScope)
{
	m_nScope = nScope;
}

UINT CTCInterlock::GetScope() CONST
{
	return m_nScope;
}

VOID CTCInterlock::SetStage(UINT nStage)
{
	m_nStage = nStage;
}

UINT CTCInterlock::GetStage() CONST
{
	return m_nStage;
}

VOID CTCInterlock::SetState(UINT nState)
{
	m_nState = nState;
}

UINT CTCInterlock::GetState() CONST
{
	return m_nState;
}

VOID CTCInterlock::SetReleaseIDs(CONST CUIntArray &nIDs)
{
	m_nReleaseIDs.Copy(nIDs);
}

INT CTCInterlock::GetReleaseIDs(CUIntArray &nIDs) CONST
{
	nIDs.Copy(m_nReleaseIDs);
	return((INT)nIDs.GetSize());
}

BOOL CTCInterlock::IsAutomatic() CONST
{
	return((m_nSourceType != TCINTERLOCK_SOURCETYPE_NONE  &&  m_nScope != TCINTERLOCK_SCOPE_NONE  &&  m_nStage != TCINTERLOCK_STAGE_NONE  &&  m_szName.IsEmpty()) ? TRUE : FALSE);
}

VOID CTCInterlock::Copy(CONST CTCInterlock *pInterlock)
{
	m_szName = pInterlock->m_szName;
	m_szComputerName = pInterlock->m_szComputerName;
	m_nSourceType = pInterlock->m_nSourceType;
	m_nScope = pInterlock->m_nScope;
	m_nStage = pInterlock->m_nStage;
	m_nState = pInterlock->m_nState;
	m_nReleaseIDs.Copy(pInterlock->m_nReleaseIDs);
}

BOOL CTCInterlock::Compare(CONST CTCInterlock *pInterlock) CONST
{
	return((pInterlock->m_szName == m_szName  &&  !pInterlock->m_szComputerName.CompareNoCase(m_szComputerName) && pInterlock->m_nSourceType == m_nSourceType  &&  pInterlock->m_nScope == m_nScope  &&  pInterlock->m_nStage == m_nStage  &&  pInterlock->m_nState == m_nState  &&  pInterlock->m_nReleaseIDs.GetSize() == m_nReleaseIDs.GetSize() && !memcmp(pInterlock->m_nReleaseIDs.GetData(), m_nReleaseIDs.GetData(), m_nReleaseIDs.GetSize()*sizeof(UINT))) ? TRUE : FALSE);
}

BOOL CTCInterlock::Map(CByteArray &nInfo) CONST
{
	INT  cbData;
	DATA  sData;

	sData.cbName = (m_szName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbComputerName = (m_szComputerName.GetLength() + 1)*sizeof(TCHAR);
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbName + sData.cbComputerName)), sData.nSourceType = m_nSourceType, sData.nScope = m_nScope, sData.nStage = m_nStage, sData.nState = m_nState; nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szName, sData.cbName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbName), (LPCTSTR)m_szComputerName, sData.cbComputerName);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCInterlock::Unmap(CONST CByteArray &nInfo)
{
	INT  cbData;
	DATA  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbName + sData.cbComputerName && sData.cbName > 0 && sData.cbComputerName > 0; )
	{
		CopyMemory(m_szName.GetBufferSetLength(STRINGCHARS(sData.cbName)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbName));
		CopyMemory(m_szComputerName.GetBufferSetLength(STRINGCHARS(sData.cbComputerName)), nInfo.GetData() + (cbData = cbData + sData.cbName), STRINGBYTES(sData.cbComputerName));
		m_nSourceType = sData.nSourceType;
		m_nScope = sData.nScope;
		m_nStage = sData.nStage;
		m_nState = sData.nState;
		m_szName.ReleaseBuffer();
		m_szComputerName.ReleaseBuffer();
		return TRUE;
	}
	return FALSE;
}

CString CTCInterlock::ConstructDefaultName(LPCTSTR pszComputerName, UINT nSourceType, UINT nScope, UINT nStage) CONST
{
	CString  szName;
	CString  szSourceType;
	CString  szScope;
	CString  szStage;

	szSourceType = (nSourceType == TCINTERLOCK_SOURCETYPE_MANUALSTACK) ? STRING(IDS_TCINTERLOCK_NAME_SOURCE_MANUALSTACK) : EMPTYSTRING;
	szSourceType = (nSourceType == TCINTERLOCK_SOURCETYPE_AUTOMATICSTACK) ? STRING(IDS_TCINTERLOCK_NAME_SOURCE_AUTOMATICSTACK) : szSourceType;
	szSourceType = (nSourceType == TCINTERLOCK_SOURCETYPE_PROCEDURESMONITOR) ? STRING(IDS_TCINTERLOCK_NAME_SOURCE_PROCEDURESMONITOR) : szSourceType;
	szScope = (nScope == TCINTERLOCK_SCOPE_GLOBAL) ? STRING(IDS_TCINTERLOCK_NAME_SCOPE_GLOBAL) : EMPTYSTRING;
	szScope = (nScope == TCINTERLOCK_SCOPE_LOCAL) ? STRING(IDS_TCINTERLOCK_NAME_SCOPE_LOCAL) : szScope;
	szScope = (nScope == TCINTERLOCK_SCOPE_LOCALNOWAIT) ? STRING(IDS_TCINTERLOCK_NAME_SCOPE_LOCALNOWAIT) : szScope;
	szScope = (nScope == TCINTERLOCK_SCOPE_GLOBALSUBSYSTEM) ? STRING(IDS_TCINTERLOCK_NAME_SCOPE_GLOBALSUBSYSTEM) : szScope;
	szScope = (nScope == TCINTERLOCK_SCOPE_LOCALSUBSYSTEM) ? STRING(IDS_TCINTERLOCK_NAME_SCOPE_LOCALSUBSYSTEM) : szScope;
	szScope = (nScope == TCINTERLOCK_SCOPE_LOCALSUBSYSTEMNOWAIT) ? STRING(IDS_TCINTERLOCK_NAME_SCOPE_LOCALSUBSYSTEMNOWAIT) : szScope;
	szScope = (nScope == TCINTERLOCK_SCOPE_COMMANDS) ? STRING(IDS_TCINTERLOCK_NAME_SCOPE_COMMANDS) : szScope;
	szStage = (nStage == TCINTERLOCK_STAGE_RECEPTION) ? STRING(IDS_TCINTERLOCK_NAME_STAGE_RECEPTION) : EMPTYSTRING;
	szStage = (nStage == TCINTERLOCK_STAGE_TRANSMISSION) ? STRING(IDS_TCINTERLOCK_NAME_STAGE_TRANSMISSION) : szStage;
	szStage = (nStage == TCINTERLOCK_STAGE_ACCEPTANCE) ? STRING(IDS_TCINTERLOCK_NAME_STAGE_ACCEPTANCE) : szStage;
	szStage = (nStage == TCINTERLOCK_STAGE_START) ? STRING(IDS_TCINTERLOCK_NAME_STAGE_START) : szStage;
	szStage = (nStage == TCINTERLOCK_STAGE_PROGRESS) ? STRING(IDS_TCINTERLOCK_NAME_STAGE_PROGRESS) : szStage;
	szStage = (nStage == TCINTERLOCK_STAGE_COMPLETION) ? STRING(IDS_TCINTERLOCK_NAME_STAGE_COMPLETION) : szStage;
	szName.Format(STRING(IDS_TCINTERLOCK_NAME_FORMAT), pszComputerName, (LPCTSTR)szSourceType, (LPCTSTR)szScope, (LPCTSTR)szStage);
	return szName;
}


/////////////////////////////////////////////////////////////////////////////
// CTCInterlocks

CTCInterlocks::CTCInterlocks() : CPtrArray()
{
	return;
}

CTCInterlocks::~CTCInterlocks()
{
	RemoveAll();
}

INT CTCInterlocks::Add(CTCInterlock *pInterlock)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pInterlock->GetComputerName(), pInterlock->GetSourceType(), pInterlock->GetName(), pInterlock->GetScope(), pInterlock->GetStage(), TRUE)) >= 0) InsertAt(nIndex, pInterlock, 1);
	return nIndex;
}

INT CTCInterlocks::Find(UINT nSourceType, LPCTSTR pszName) CONST
{
	CComputerToken  cComputerToken;

	return Find(cComputerToken.GetComputerName(), nSourceType, pszName);
}
INT CTCInterlocks::Find(LPCTSTR pszComputerName, UINT nSourceType, LPCTSTR pszName) CONST
{
	INT  nInterlock;
	INT  nInterlocks;
	CTCInterlock  *pInterlock;

	for (nInterlock = 0, nInterlocks = (INT)GetSize(); nInterlock < nInterlocks; nInterlock++)
	{
		if ((pInterlock = GetAt(nInterlock)) && !pInterlock->GetComputerName().CompareNoCase(pszComputerName) && pInterlock->GetSourceType() == nSourceType  &&  pInterlock->GetName() == pszName) break;
		continue;
	}
	return((nInterlock < nInterlocks) ? nInterlock : -1);
}
INT CTCInterlocks::Find(CONST CTCInterlock *pInterlock) CONST
{
	return FindIndex(pInterlock->GetComputerName(), pInterlock->GetSourceType(), pInterlock->GetName(), pInterlock->GetScope(), pInterlock->GetStage(), FALSE);
}

CTCInterlock *CTCInterlocks::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCInterlock *)CPtrArray::GetAt(nIndex) : (CTCInterlock *)NULL);
}

CTCInterlock *CTCInterlocks::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCInterlock *)CPtrArray::GetAt(nIndex) : (CTCInterlock *)NULL);
}

VOID CTCInterlocks::RemoveAll()
{
	INT  nInterlock;
	INT  nInterlocks;

	for (nInterlock = 0, nInterlocks = (INT)GetSize(); nInterlock < nInterlocks; nInterlock++)
	{
		delete GetAt(nInterlock);
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CTCInterlocks::Copy(CONST CTCInterlocks *pInterlocks)
{
	INT  nInterlock;
	INT  nInterlocks;
	CTCInterlock  *pInterlock;

	for (nInterlock = 0, nInterlocks = (INT)pInterlocks->GetSize(), RemoveAll(); nInterlock < nInterlocks; nInterlock++)
	{
		if ((pInterlock = new CTCInterlock) != (CTCInterlock *)NULL)
		{
			pInterlock->Copy(pInterlocks->GetAt(nInterlock));
			InsertAt(nInterlock, pInterlock, 1);
			continue;
		}
		break;
	}
	return((nInterlock == nInterlocks) ? TRUE : FALSE);
}

BOOL CTCInterlocks::Compare(CONST CTCInterlocks *pInterlocks) CONST
{
	INT  nInterlock;
	INT  nInterlocks;

	for (nInterlock = 0, nInterlocks = (pInterlocks->GetSize() == GetSize()) ? (INT)GetSize() : -1; nInterlock < nInterlocks; nInterlock++)
	{
		if (!pInterlocks->GetAt(nInterlock)->Compare(GetAt(nInterlock))) break;
		continue;
	}
	return((nInterlock == nInterlocks) ? TRUE : FALSE);
}

BOOL CTCInterlocks::Map(CByteArray &nInfo) CONST
{
	INT  nInterlock;
	INT  nInterlocks;
	CByteArray  nInterlockData;
	CTCInterlock  *pInterlock;

	for (nInterlock = 0, nInterlocks = (INT)GetSize(), nInfo.RemoveAll(); nInterlock < nInterlocks; nInterlock++)
	{
		if ((pInterlock = GetAt(nInterlock)) && pInterlock->Map(nInterlockData) && nInfo.Append(nInterlockData) >= 0) continue;
		break;
	}
	return((nInterlock == nInterlocks) ? TRUE : FALSE);
}

BOOL CTCInterlocks::Unmap(CONST CByteArray &nInfo)
{
	INT  cbInterlock;
	INT  cbInterlocks;
	CByteArray  nInterlockData;
	CTCInterlock  *pInterlock;

	for (cbInterlocks = 0, RemoveAll(); cbInterlocks < nInfo.GetSize(); cbInterlocks += cbInterlock)
	{
		for (CopyMemory(&cbInterlock, nInfo.GetData() + cbInterlocks, sizeof(cbInterlock)), nInterlockData.SetSize(max(min(cbInterlock, nInfo.GetSize() - cbInterlocks), 0)); nInterlockData.GetSize() >= 0; )
		{
			CopyMemory(nInterlockData.GetData(), nInfo.GetData() + cbInterlocks, nInterlockData.GetSize());
			break;
		}
		if ((pInterlock = new CTCInterlock))
		{
			if (pInterlock->Unmap(nInterlockData) && Add(pInterlock) >= 0) continue;
			delete pInterlock;
		}
		break;
	}
	return((cbInterlocks == nInfo.GetSize()) ? TRUE : FALSE);
}

INT CTCInterlocks::FindIndex(LPCTSTR pszComputerName, UINT nSourceType, LPCTSTR pszName, UINT nScope, UINT nStage, BOOL bInsert) CONST
{
	INT  nIndex[2];
	INT  nMinIndex;
	INT  nMaxIndex;
	CString  szInterlock;
	CTCInterlock  *pInterlock;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex[0] = (nMinIndex + nMaxIndex) / 2, szInterlock = ConstructSearchName(pszComputerName, nSourceType, pszName, nScope, nStage); nMinIndex != nMaxIndex; nIndex[0] = (nMinIndex + nMaxIndex) / 2)
	{
		nMinIndex = ((pInterlock = GetAt(nIndex[0]))) ? ((nIndex[1] = (ConstructSearchName(pInterlock) <= szInterlock)) ? (nIndex[0] + 1) : nMinIndex) : (nIndex[0] = -1);
		nMaxIndex = (nIndex[0] < 0 || !nIndex[1]) ? nIndex[0] : nMaxIndex;
	}
	return((((!bInsert && (pInterlock = GetAt((nIndex[0] = max(nIndex[0] - 1, 0)))) && ConstructSearchName(pInterlock) == szInterlock) || (bInsert && (((pInterlock = GetAt(max(nIndex[0] - 1, 0))) && ConstructSearchName(pInterlock) != szInterlock && (pInterlock = GetAt((INT)min(nIndex[0], GetUpperBound()))) && ConstructSearchName(pInterlock) != szInterlock) || !GetSize()))) && lstrlen(pszName) > 0) ? nIndex[0] : -1);
}

CString CTCInterlocks::ConstructSearchName(LPCTSTR pszComputerName, UINT nSourceType, LPCTSTR pszName, UINT nScope, UINT nStage) CONST
{
	CTCInterlock  cInterlock;

	for (cInterlock.SetComputerName(pszComputerName), cInterlock.SetSourceType(nSourceType), cInterlock.SetScope(nScope), cInterlock.SetStage(nStage); cInterlock.GetName().Compare(pszName); )
	{
		cInterlock.SetComputerName(cInterlock.GetComputerName() + TAB + pszName);
		break;
	}
	return cInterlock.GetName();
}
CString CTCInterlocks::ConstructSearchName(CONST CTCInterlock *pInterlock) CONST
{
	return ConstructSearchName(pInterlock->GetComputerName(), pInterlock->GetSourceType(), pInterlock->GetName(), pInterlock->GetScope(), pInterlock->GetStage());
}


/////////////////////////////////////////////////////////////////////////////
// CTCItem

TIMETAG  CTCItem::m_tLastKeyID = 0;

CTCItem::CTCItem() : CComputerToken(), CDatabaseTCFunction()
{
	m_nType = 0;
	m_nFlags = 0;
	m_nSourceType = 0;
	m_nQueuedSize = 0;
	m_nMembershipID = -1;
	m_nMembershipSize = 0;
	m_nReleaseBlockID = -1;
	m_tLoadTime = 0;
	m_tArmTime = 0;
	m_tDispatchTime = 0;
	m_tReleaseTime[0] = 0;
	m_tReleaseTime[1] = 0;
	m_tReleaseTime[2] = 0;
	m_tReleaseTimeInterval = 0;
	m_dwReleaseTimeOffset[0] = 0;
	m_dwReleaseTimeOffset[1] = 0;
	m_bReleaseTimeOffset[0] = FALSE;
	m_bReleaseTimeOffset[1] = FALSE;
	m_bReleaseInterlock = FALSE;
	m_tTransmissionTime = 0;
	m_nExecutionMode = 0;
	m_tExecutionTime = 0;
	m_nExecutionOBRT = 0;
	m_bExecutionOBRT = FALSE;
	m_dwExecutionTimeOffset = 0;
	m_bExecutionTimeOffset = FALSE;
	m_bEarlierExecution = FALSE;
	m_tDownloadDumpTime = 0;
	m_tAcknowledgeTime = 0;
	m_tVerificationTime = 0;
	m_nVerificationID = (UINT)-1;
	m_hVerificationModule = (HINSTANCE)NULL;
	m_hVerificationResult[0] = (HANDLE)NULL;
	m_hVerificationResult[1] = (HANDLE)NULL;
	m_nAuthorizationStatus = TCITEM_AUTHORIZATIONSTATUS_NONE;
	m_nResult = TCITEM_RESULT_NONE;
	m_nStatus = TCITEM_STATUS_NONE;
	Initialize(this);
}

VOID CTCItem::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CTCItem::GetName() CONST
{
	return m_szName;
}

VOID CTCItem::SetSourceType(UINT nType)
{
	m_nSourceType = nType;
}

UINT CTCItem::GetSourceType() CONST
{
	return m_nSourceType;
}

VOID CTCItem::SetType(UINT nType)
{
	m_nType = nType;
}

UINT CTCItem::GetType() CONST
{
	return m_nType;
}

VOID CTCItem::SetFlags(UINT nFlags)
{
	m_nFlags = nFlags;
}

UINT CTCItem::GetFlags() CONST
{
	return m_nFlags;
}

VOID CTCItem::SetProperties(CONST CByteArray &nData)
{
	m_nProperties.Copy(nData);
}

BOOL CTCItem::GetProperties(CByteArray &nData) CONST
{
	nData.Copy(m_nProperties);
	return((nData.GetSize() > 0) ? TRUE : FALSE);
}

BOOL CTCItem::SetTCPacket(CONST CDatabaseTCPacket *pPacket)
{
	return m_cPacket.Copy(pPacket);
}
BOOL CTCItem::SetTCPacket(CONST CByteArray &nData)
{
	m_nPacketData.Copy(nData);
	return TRUE;
}

BOOL CTCItem::GetTCPacket(CDatabaseTCPacket *pPacket) CONST
{
	return pPacket->Copy(&m_cPacket);
}
INT CTCItem::GetTCPacket(CByteArray &nData) CONST
{
	nData.Copy(m_nPacketData);
	return((INT)nData.GetSize());
}

VOID CTCItem::SetQueuedSize(UINT nSize)
{
	m_nQueuedSize = nSize;
}

UINT CTCItem::GetQueuedSize() CONST
{
	return m_nQueuedSize;
}

VOID CTCItem::SetMembership(LPCTSTR pszItem)
{
	m_szMembership[0] = pszItem;
}

CString CTCItem::GetMembership() CONST
{
	return m_szMembership[0];
}

VOID CTCItem::SetMembershipDescription(LPCTSTR pszDescription)
{
	m_szMembership[1] = pszDescription;
}

CString CTCItem::GetMembershipDescription() CONST
{
	return m_szMembership[1];
}

BOOL CTCItem::SetMembershipParameters(CONST CDatabaseTCParameters &pParameters)
{
	return m_pParameters.Copy(&pParameters);
}

INT CTCItem::GetMembershipParameters(CDatabaseTCParameters &pParameters) CONST
{
	pParameters.Copy(&m_pParameters);
	return((INT)pParameters.GetSize());
}

VOID CTCItem::SetMembershipID(UINT nID)
{
	m_nMembershipID = nID;
}

UINT CTCItem::GetMembershipID() CONST
{
	return m_nMembershipID;
}

VOID CTCItem::SetMembershipSize(UINT nSize)
{
	m_nMembershipSize = nSize;
}

UINT CTCItem::GetMembershipSize() CONST
{
	return m_nMembershipSize;
}

VOID CTCItem::SetMemoryPatch(LPCTSTR pszPatch)
{
	m_szMemoryPatch = pszPatch;
}

CString CTCItem::GetMemoryPatch() CONST
{
	return m_szMemoryPatch;
}

VOID CTCItem::SetInterlock(LPCTSTR pszInterlock)
{
	m_szInterlock[0] = pszInterlock;
}
VOID CTCItem::SetInterlock(CONST CTCInterlock *pInterlock)
{
	m_cInterlock[0].Copy(pInterlock);
}

CString CTCItem::GetInterlock() CONST
{
	return m_szInterlock[0];
}
BOOL CTCItem::GetInterlock(CTCInterlock *pInterlock) CONST
{
	pInterlock->Copy(&m_cInterlock[0]);
	return !pInterlock->GetName().IsEmpty();
}

VOID CTCItem::SetReleaseInterlock(LPCTSTR pszInterlock, BOOL bSuccess)
{
	m_szInterlock[1] = pszInterlock;
	m_bReleaseInterlock = bSuccess;
}
VOID CTCItem::SetReleaseInterlock(CONST CTCInterlock *pInterlock)
{
	m_cInterlock[1].Copy(pInterlock);
}

BOOL CTCItem::GetReleaseInterlock(CString &szInterlock, BOOL &bSuccess) CONST
{
	szInterlock = m_szInterlock[1];
	bSuccess = m_bReleaseInterlock;
	return !szInterlock.IsEmpty();
}
BOOL CTCItem::GetReleaseInterlock(CTCInterlock *pInterlock) CONST
{
	pInterlock->Copy(&m_cInterlock[1]);
	return !pInterlock->GetName().IsEmpty();
}

VOID CTCItem::SetReleaseBlock(LPCTSTR pszBlock)
{
	m_szReleaseBlock = pszBlock;
}

CString CTCItem::GetReleaseBlock() CONST
{
	return m_szReleaseBlock;
}

VOID CTCItem::SetReleaseBlockID(UINT nID)
{
	m_nReleaseBlockID = nID;
}

UINT CTCItem::GetReleaseBlockID() CONST
{
	return m_nReleaseBlockID;
}

BOOL CTCItem::SetReleaseBlockedItems(CONST CDatabaseTCFunctions &pItems)
{
	return m_pBlockedItems.Copy(&pItems);
}

INT CTCItem::GetReleaseBlockedItems(CDatabaseTCFunctions &pItems) CONST
{
	return((pItems.Copy(&m_pBlockedItems)) ? (INT)pItems.GetSize() : 0);
}

VOID CTCItem::SetReleaseTimeWindow(CONST CTimeTag &tOpenTime)
{
	m_tReleaseTime[0] = tOpenTime;
	m_tReleaseTime[2] = tOpenTime;
	m_tReleaseTime[1] = 0;
	m_tReleaseTimeInterval = 0;
	m_dwReleaseTimeOffset[0] = 0;
	m_dwReleaseTimeOffset[1] = 0;
	m_bReleaseTimeOffset[0] = FALSE;
	m_bReleaseTimeOffset[1] = FALSE;
}
VOID CTCItem::SetReleaseTimeWindow(CONST CTimeTag &tOpenTime, CONST CTimeSpan &tInterval)
{
	m_tReleaseTime[0] = tOpenTime;
	m_tReleaseTime[2] = tOpenTime;
	m_tReleaseTime[1] = 0;
	m_tReleaseTimeInterval = tInterval;
	m_dwReleaseTimeOffset[0] = 0;
	m_dwReleaseTimeOffset[1] = 0;
	m_bReleaseTimeOffset[0] = FALSE;
	m_bReleaseTimeOffset[1] = FALSE;
}
VOID CTCItem::SetReleaseTimeWindow(CONST CTimeTag &tOpenTime, CONST CTimeTag &tCloseTime)
{
	m_tReleaseTime[0] = tOpenTime;
	m_tReleaseTime[1] = tCloseTime;
	m_tReleaseTime[2] = tOpenTime;
	m_tReleaseTimeInterval = 0;
	m_dwReleaseTimeOffset[0] = 0;
	m_dwReleaseTimeOffset[1] = 0;
	m_bReleaseTimeOffset[0] = FALSE;
	m_bReleaseTimeOffset[1] = FALSE;
}
VOID CTCItem::SetReleaseTimeWindow(DWORD dwOffset, BOOL bAfterDispatch)
{
	m_tReleaseTime[0] = 0;
	m_tReleaseTime[1] = 0;
	m_tReleaseTime[2] = 0;
	m_tReleaseTimeInterval = 0;
	m_dwReleaseTimeOffset[0] = (!bAfterDispatch) ? dwOffset : 0;
	m_dwReleaseTimeOffset[1] = (!bAfterDispatch) ? 0 : dwOffset;
	m_bReleaseTimeOffset[0] = (!bAfterDispatch) ? TRUE : FALSE;
	m_bReleaseTimeOffset[1] = (!bAfterDispatch) ? FALSE : TRUE;
}
VOID CTCItem::SetReleaseTimeWindow(DWORD dwOffset, CONST CTimeSpan &tInterval, BOOL bAfterDispatch)
{
	m_tReleaseTime[0] = 0;
	m_tReleaseTime[1] = 0;
	m_tReleaseTime[2] = 0;
	m_tReleaseTimeInterval = tInterval;
	m_dwReleaseTimeOffset[0] = (!bAfterDispatch) ? dwOffset : 0;
	m_dwReleaseTimeOffset[1] = (!bAfterDispatch) ? 0 : dwOffset;
	m_bReleaseTimeOffset[0] = (!bAfterDispatch) ? TRUE : FALSE;
	m_bReleaseTimeOffset[1] = (!bAfterDispatch) ? FALSE : TRUE;
}

BOOL CTCItem::GetReleaseTimeWindow(CTimeTag &tOpenTime, CTimeSpan &tInterval) CONST
{
	tOpenTime = m_tReleaseTime[0];
	tInterval = m_tReleaseTimeInterval;
	return((tOpenTime > 0 || tInterval > 0) ? TRUE : FALSE);
}
BOOL CTCItem::GetReleaseTimeWindow(CTimeTag &tOpenTime, CTimeTag &tCloseTime) CONST
{
	tOpenTime = m_tReleaseTime[0];
	tCloseTime = m_tReleaseTime[1];
	return((tOpenTime > 0 || tCloseTime > 0) ? TRUE : FALSE);
}
BOOL CTCItem::GetReleaseTimeWindow(DWORD &dwOffset, CTimeSpan &tInterval, BOOL &bAfterDispatch) CONST
{
	for (dwOffset = 0, tInterval = 0; m_bReleaseTimeOffset[0]; )
	{
		dwOffset = m_dwReleaseTimeOffset[0];
		tInterval = m_tReleaseTimeInterval;
		bAfterDispatch = FALSE;
		return TRUE;
	}
	if (m_bReleaseTimeOffset[1])
	{
		dwOffset = m_dwReleaseTimeOffset[1];
		tInterval = m_tReleaseTimeInterval;
		bAfterDispatch = TRUE;
		return TRUE;
	}
	return FALSE;
}

VOID CTCItem::SetReleaseIDs(CONST CUIntArray &nIDs)
{
	m_nReleaseIDs.Copy(nIDs);
}

INT CTCItem::GetReleaseIDs(CUIntArray &nIDs) CONST
{
	nIDs.Copy(m_nReleaseIDs);
	return((INT)nIDs.GetSize());
}

VOID CTCItem::SetExecutionTime(CONST CTimeTag &tTime)
{
	m_tExecutionTime = tTime;
}

BOOL CTCItem::GetExecutionTime(CTimeTag &tTime) CONST
{
	return((tTime = m_tExecutionTime) > 0);
}

VOID CTCItem::SetExecutionTimeOffset()
{
	m_dwExecutionTimeOffset = 0;
	m_bExecutionTimeOffset = FALSE;
	m_bEarlierExecution = FALSE;
}
VOID CTCItem::SetExecutionTimeOffset(DWORD dwOffset, BOOL bEarlier)
{
	m_dwExecutionTimeOffset = dwOffset;
	m_bExecutionTimeOffset = TRUE;
	m_bEarlierExecution = bEarlier;
	m_nExecutionOBRT = 0;
	m_bExecutionOBRT = FALSE;
}

BOOL CTCItem::GetExecutionTimeOffset(DWORD &dwOffset, BOOL &bEarlier) CONST
{
	dwOffset = m_dwExecutionTimeOffset;
	bEarlier = m_bEarlierExecution;
	return m_bExecutionTimeOffset;
}

VOID CTCItem::SetExecutionOBRT()
{
	m_nExecutionOBRT = 0;
	m_bExecutionOBRT = FALSE;
}
VOID CTCItem::SetExecutionOBRT(UINT nOBRT)
{
	m_nExecutionOBRT = nOBRT;
	m_bExecutionOBRT = TRUE;
	m_dwExecutionTimeOffset = 0;
	m_bExecutionTimeOffset = FALSE;
	m_bEarlierExecution = FALSE;
}

BOOL CTCItem::GetExecutionOBRT(UINT &nOBRT) CONST
{
	nOBRT = m_nExecutionOBRT;
	return m_bExecutionOBRT;
}

VOID CTCItem::SetExecutionMode(UINT nMode)
{
	m_nExecutionMode = nMode;
}

UINT CTCItem::GetExecutionMode() CONST
{
	return m_nExecutionMode;
}

VOID CTCItem::SetAuthorizationStatus(UINT nStatus)
{
	m_nAuthorizationStatus = nStatus;
}

UINT CTCItem::GetAuthorizationStatus() CONST
{
	return m_nAuthorizationStatus;
}

VOID CTCItem::SetVerificationProcedure(LPCTSTR pszName)
{
	m_szVerificationProcedure = pszName;
}

CString CTCItem::GetVerificationProcedure() CONST
{
	return m_szVerificationProcedure;
}

VOID CTCItem::SetVerificationProcessID(INT nID)
{
	m_nVerificationID = nID;
}

INT CTCItem::GetVerificationProcessID() CONST
{
	return m_nVerificationID;
}

VOID CTCItem::SetVerificationThread(LPCTSTR pszThread)
{
	m_szVerificationThread = pszThread;
}

CString CTCItem::GetVerificationThread() CONST
{
	return m_szVerificationThread;
}

VOID CTCItem::SetVerificationStep(LPCTSTR pszStep)
{
	m_szVerificationStep = pszStep;
}

CString CTCItem::GetVerificationStep() CONST
{
	return m_szVerificationStep;
}

VOID CTCItem::SetVerificationModuleFileName(LPCTSTR pszFileName)
{
	m_szVerificationModuleFileName = pszFileName;
}

CString CTCItem::GetVerificationModuleFileName() CONST
{
	return m_szVerificationModuleFileName;
}

VOID CTCItem::SetVerificationModule(HINSTANCE hModule)
{
	m_hVerificationModule = hModule;
}

HINSTANCE CTCItem::GetVerificationModule() CONST
{
	return m_hVerificationModule;
}

VOID CTCItem::SetVerificationHandles(HANDLE hSuccess, HANDLE hFailure)
{
	m_hVerificationResult[0] = hSuccess;
	m_hVerificationResult[1] = hFailure;
}

BOOL CTCItem::GetVerificationHandles(HANDLE &hSuccess, HANDLE &hFailure) CONST
{
	hSuccess = m_hVerificationResult[0];
	hFailure = m_hVerificationResult[1];
	return((hSuccess != (HANDLE)NULL  &&  hFailure != (HANDLE)NULL) ? TRUE : FALSE);
}

INT CTCItem::EnumVerificationStageIDs(CUIntArray &nStageIDs) CONST
{
	nStageIDs.Copy(m_nVerificationStageIDs[0]);
	return((INT)nStageIDs.GetSize());
}

VOID CTCItem::SetVerificationTimeWindow(UINT nStageID, CONST CTimeSpan &tStartDelay, CONST CTimeSpan &tTimeWindow, CONST CTimeSpan &tUncertainty)
{
	INT  nIndex;
	INT  nCount;

	if (nStageID != MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_ACCEPTANCE) && nStageID != MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_START) && nStageID != MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_PROGRESS) && nStageID != MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_COMPLETION))
	{
		for (nIndex = 0, nCount = (nStageID > 0) ? (INT)m_nVerificationStageIDs[0].GetSize() : 0; nIndex < nCount; nIndex++)
		{
			if (m_nVerificationStageIDs[0].GetAt(nIndex) == nStageID)
			{
				m_tVerificationStageTimeWindows[0].SetAt(nIndex, tStartDelay.GetTotalSeconds());
				m_tVerificationStageTimeWindows[1].SetAt(nIndex, tTimeWindow.GetTotalSeconds());
				m_tVerificationStageTimeWindows[2].SetAt(nIndex, tUncertainty.GetTotalSeconds());
				return;
			}
			if (m_nVerificationStageIDs[0].GetAt(nIndex) > nStageID) break;
		}
		if (nStageID > 0)
		{
			m_nVerificationStageIDs[0].InsertAt(nIndex, nStageID);
			m_tVerificationStageTimeWindows[0].InsertAt(nIndex, CTimeKey(tStartDelay.GetTotalSeconds()));
			m_tVerificationStageTimeWindows[1].InsertAt(nIndex, CTimeKey(tTimeWindow.GetTotalSeconds()));
			m_tVerificationStageTimeWindows[2].InsertAt(nIndex, CTimeKey(tUncertainty.GetTotalSeconds()));
			return;
		}
		m_nVerificationStageIDs[0].RemoveAll();
		m_tVerificationStageTimeWindows[0].RemoveAll();
		m_tVerificationStageTimeWindows[1].RemoveAll();
		m_tVerificationStageTimeWindows[2].RemoveAll();
	}
}

BOOL CTCItem::GetVerificationTimeWindow(UINT nStageID, CTimeSpan &tStartDelay, CTimeSpan &tTimeWindow, CTimeSpan &tUncertainty) CONST
{
	INT  nIndex;
	INT  nCount;

	if (nStageID != MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_ACCEPTANCE) && nStageID != MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_START) && nStageID != MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_PROGRESS) && nStageID != MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_COMPLETION))
	{
		for (nIndex = 0, nCount = (INT)m_nVerificationStageIDs[0].GetSize(), tStartDelay = tTimeWindow = tUncertainty = 0; nIndex < nCount; nIndex++)
		{
			if (m_nVerificationStageIDs[0].GetAt(nIndex) == nStageID)
			{
				tStartDelay = m_tVerificationStageTimeWindows[0].GetAt(nIndex).GetTime();
				tTimeWindow = m_tVerificationStageTimeWindows[1].GetAt(nIndex).GetTime();
				tUncertainty = m_tVerificationStageTimeWindows[2].GetAt(nIndex).GetTime();
				break;
			}
		}
		return((nIndex < nCount) ? TRUE : FALSE);
	}
	return FALSE;
}

CTimeSpan CTCItem::CalcVerificationTimeWindowOffset(UINT nStageID, CONST CTimeSpan &tDefault) CONST
{
	INT  nIndex;
	INT  nCount;
	CTimeSpan  tInterval;
	CTimeSpan  tOffset[3];
	CTimeSpan  tUncertainty;
	CUIntArray  nStageIDs;

	for (nIndex = 0, nCount = EnumVerificationStageIDs(nStageIDs), tOffset[0] = -1; nIndex < nCount; nIndex++)
	{
		if ((((nStageID == MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_ACCEPTANCE) || nStageID == MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_START) || nStageID == MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_PROGRESS) || nStageID == MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_COMPLETION)) && MAKETCEXEVERSTAGEFROMID(nStageID) == MAKETCEXEVERSTAGEFROMID(nStageIDs.GetAt(nIndex))) || nStageID == nStageIDs.GetAt(nIndex) || !nStageID) && GetVerificationTimeWindow(nStageIDs.GetAt(nIndex), tOffset[1], tInterval, tUncertainty))
		{
			tOffset[2] = (tDefault >= 0) ? ((tUncertainty > 0) ? (tOffset[1] + tUncertainty) : (tOffset[1] + tDefault)) : tOffset[1];
			tOffset[0] = (tOffset[0] >= 0) ? min(tOffset[2], tOffset[0]) : tOffset[2];
			if (nStageID == nStageIDs.GetAt(nIndex)) break;
		}
	}
	return max(tOffset[0], 0);
}

CTimeSpan CTCItem::CalcVerificationTimeWindowSize(UINT nStageID, CONST CTimeSpan &tDefault) CONST
{
	INT  nIndex;
	INT  nCount;
	CTimeSpan  tOffset;
	CTimeSpan  tSize[3];
	CTimeSpan  tInterval;
	CTimeSpan  tUncertainty;
	CUIntArray  nStageIDs;

	for (nIndex = 0, nCount = EnumVerificationStageIDs(nStageIDs), tSize[0] = -1; nIndex < nCount; nIndex++)
	{
		if ((((nStageID == MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_ACCEPTANCE) || nStageID == MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_START) || nStageID == MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_PROGRESS) || nStageID == MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_COMPLETION)) && MAKETCEXEVERSTAGEFROMID(nStageID) == MAKETCEXEVERSTAGEFROMID(nStageIDs.GetAt(nIndex))) || nStageID == nStageIDs.GetAt(nIndex) || !nStageID) && GetVerificationTimeWindow(nStageIDs.GetAt(nIndex), tOffset, tInterval, tUncertainty))
		{
			tSize[1] = (tDefault >= 0) ? ((tUncertainty > 0) ? (tInterval + tUncertainty) : (tInterval + tDefault)) : tInterval;
			tSize[0] = (tSize[0] >= 0) ? max(tSize[1], tSize[0]) : tSize[1];
			if (nStageID == nStageIDs.GetAt(nIndex)) break;
		}
	}
	return max(tSize[0], 0);
}

VOID CTCItem::SetVerificationStageState(UINT nStageID, UINT nState, UINT nReason)
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = 0, nCount = (nStageID > 0) ? (INT)m_nVerificationStageIDs[1].GetSize() : 0; nIndex < nCount; nIndex++)
	{
		if ((nStageID == MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_ACCEPTANCE) || nStageID == MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_START) || nStageID == MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_PROGRESS) || nStageID == MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_COMPLETION)) && MAKETCEXEVERSTAGEFROMID(nStageID) == MAKETCEXEVERSTAGEFROMID(m_nVerificationStageIDs[1].GetAt(nIndex)))
		{
			m_nVerificationStageStates[0].SetAt(nIndex, nState);
			m_nVerificationStageStates[1].SetAt(nIndex, nReason);
			continue;
		}
		if (m_nVerificationStageIDs[1].GetAt(nIndex) == nStageID)
		{
			m_nVerificationStageStates[0].SetAt(nIndex, nState);
			m_nVerificationStageStates[1].SetAt(nIndex, nReason);
			return;
		}
		if (m_nVerificationStageIDs[1].GetAt(nIndex) > nStageID) break;
	}
	if (nStageID > 0)
	{
		m_nVerificationStageIDs[1].InsertAt(nIndex, nStageID);
		m_nVerificationStageStates[0].InsertAt(nIndex, nState);
		m_nVerificationStageStates[1].InsertAt(nIndex, nReason);
		return;
	}
	m_nVerificationStageIDs[1].RemoveAll();
	m_nVerificationStageStates[0].RemoveAll();
	m_nVerificationStageStates[1].RemoveAll();
}

BOOL CTCItem::GetVerificationStageState(UINT nStageID, UINT &nState, UINT &nReason) CONST
{
	INT  nIndex;
	INT  nCount;
	BOOL  bState;
	BOOL  bOverall;

	for (nIndex = 0, nCount = (INT)m_nVerificationStageIDs[1].GetSize(), nState = nReason = 0, bOverall = bState = FALSE; nIndex < nCount; nIndex++)
	{
		if (nStageID == MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_ACCEPTANCE) || nStageID == MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_START) || nStageID == MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_PROGRESS) || nStageID == MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_COMPLETION))
		{
			if (MAKETCEXEVERSTAGEFROMID(nStageID) == MAKETCEXEVERSTAGEFROMID(m_nVerificationStageIDs[1].GetAt(nIndex)))
			{
				for (nState |= m_nVerificationStageStates[0].GetAt(nIndex); nState & TCITEM_RESULT_CEV_PASSED; )
				{
					nState = (nState & (TCITEM_RESULT_CEV_FAILED | TCITEM_RESULT_CEV_UNKNOWN | TCITEM_RESULT_CEV_UNVERIFIED)) ? (nState & ~TCITEM_RESULT_CEV_PASSED) : nState;
					break;
				}
				nReason |= m_nVerificationStageStates[1].GetAt(nIndex);
				bState = TRUE;
			}
			bOverall = TRUE;
			continue;
		}
		if (m_nVerificationStageIDs[1].GetAt(nIndex) == nStageID)
		{
			nState = m_nVerificationStageStates[0].GetAt(nIndex);
			nReason = m_nVerificationStageStates[1].GetAt(nIndex);
			break;
		}
	}
	return(((!bOverall  &&  nIndex < nCount) || (bOverall  &&  bState)) ? TRUE : FALSE);
}

VOID CTCItem::SetVerificationStageParameters(UINT nStageID, CONST CStringArray &szParameters)
{
	INT  nIndex;
	INT  nCount;
	INT  nParameter;
	INT  nParameters;

	if (nStageID != MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_ACCEPTANCE) && nStageID != MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_START) && nStageID != MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_PROGRESS) && nStageID != MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_COMPLETION))
	{
		for (nIndex = 0, nCount = (INT)m_nVerificationStageIDs[2].GetSize(); nIndex < nCount; nIndex++)
		{
			if (m_nVerificationStageIDs[2].GetAt(nIndex) == nStageID)
			{
				m_szVerificationStageParameters.RemoveAt(nIndex);
				m_nVerificationStageIDs[2].RemoveAt(nIndex);
				nIndex--;
				nCount--;
				continue;
			}
			if (m_nVerificationStageIDs[2].GetAt(nIndex) > nStageID) break;
		}
		for (nParameter = 0, nParameters = (INT)szParameters.GetSize(); nParameter < nParameters; nParameter++)
		{
			m_szVerificationStageParameters.InsertAt(nIndex + nParameter, szParameters.GetAt(nParameter));
			m_nVerificationStageIDs[2].InsertAt(nIndex + nParameter, nStageID);
		}
	}
}

INT CTCItem::GetVerificationStageParameters(UINT nStageID, CStringArray &szParameters) CONST
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = 0, nCount = (INT)m_nVerificationStageIDs[2].GetSize(), szParameters.RemoveAll(); nIndex < nCount; nIndex++)
	{
		if (((nStageID == MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_ACCEPTANCE) || nStageID == MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_START) || nStageID == MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_PROGRESS) || nStageID == MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_COMPLETION)) && MAKETCEXEVERSTAGEFROMID(nStageID) == MAKETCEXEVERSTAGEFROMID(m_nVerificationStageIDs[2].GetAt(nIndex))) || nStageID == m_nVerificationStageIDs[2].GetAt(nIndex))
		{
			szParameters.Add(m_szVerificationStageParameters.GetAt(nIndex));
			continue;
		}
	}
	return((INT)szParameters.GetSize());
}

VOID CTCItem::SetVerificationStageClosure(UINT nStageID, LPCTSTR pszTag)
{
	INT  nIndex;
	INT  nCount;

	if (nStageID != MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_ACCEPTANCE) && nStageID != MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_START) && nStageID != MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_PROGRESS) && nStageID != MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_COMPLETION))
	{
		for (nIndex = 0, nCount = (nStageID > 0) ? (INT)m_nVerificationStageIDs[3].GetSize() : 0; nIndex < nCount; nIndex++)
		{
			if (m_nVerificationStageIDs[3].GetAt(nIndex) == nStageID)
			{
				m_szVerificationStageClosures.SetAt(nIndex, pszTag);
				return;
			}
			if (m_nVerificationStageIDs[3].GetAt(nIndex) > nStageID) break;
		}
		if (nStageID > 0)
		{
			m_nVerificationStageIDs[3].InsertAt(nIndex, nStageID);
			m_szVerificationStageClosures.InsertAt(nIndex, pszTag);
			return;
		}
		m_nVerificationStageIDs[3].RemoveAll();
		m_szVerificationStageClosures.RemoveAll();
	}
}

CString CTCItem::GetVerificationStageClosure(UINT nStageID) CONST
{
	INT  nIndex;
	INT  nCount;

	if (nStageID != MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_ACCEPTANCE) && nStageID != MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_START) && nStageID != MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_PROGRESS) && nStageID != MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_COMPLETION))
	{
		for (nIndex = 0, nCount = (INT)m_nVerificationStageIDs[3].GetSize(); nIndex < nCount; nIndex++)
		{
			if (m_nVerificationStageIDs[3].GetAt(nIndex) == nStageID) break;
			continue;
		}
		return((nIndex < nCount) ? m_szVerificationStageClosures.GetAt(nIndex) : EMPTYSTRING);
	}
	return EMPTYSTRING;
}

VOID CTCItem::SetLoadTime(CONST CTimeTag &tTime)
{
	m_tLoadTime = tTime;
}

CTimeTag CTCItem::GetLoadTime() CONST
{
	return m_tLoadTime;
}

VOID CTCItem::SetArmTime(CONST CTimeTag &tTime)
{
	m_tArmTime = tTime;
}

CTimeTag CTCItem::GetArmTime() CONST
{
	return m_tArmTime;
}

VOID CTCItem::SetDispatchTime(CONST CTimeTag &tTime)
{
	m_tDispatchTime = tTime;
}

CTimeTag CTCItem::GetDispatchTime() CONST
{
	return m_tDispatchTime;
}

VOID CTCItem::SetReleaseTime(CONST CTimeTag &tTime)
{
	m_tReleaseTime[2] = tTime;
}

CTimeTag CTCItem::GetReleaseTime() CONST
{
	return m_tReleaseTime[2];
}

VOID CTCItem::SetTransmissionTime(CONST CTimeTag &tTime)
{
	m_tTransmissionTime = tTime;
}

CTimeTag CTCItem::GetTransmissionTime() CONST
{
	return m_tTransmissionTime;
}

VOID CTCItem::SetVerificationTime(CONST CTimeTag &tTime)
{
	m_tVerificationTime = tTime;
}

CTimeTag CTCItem::GetVerificationTime() CONST
{
	return m_tVerificationTime;
}

VOID CTCItem::SetDumpTime(CONST CTimeTag &tTime)
{
	m_tDownloadDumpTime = tTime;
}

CTimeTag CTCItem::GetDumpTime() CONST
{
	return m_tDownloadDumpTime;
}

VOID CTCItem::SetAcknowledgeTime(CONST CTimeTag &tTime)
{
	m_tAcknowledgeTime = tTime;
}

CTimeTag CTCItem::GetAcknowledgeTime() CONST
{
	return m_tAcknowledgeTime;
}

VOID CTCItem::SetResult(UINT nResult)
{
	m_nResult = nResult;
}

UINT CTCItem::GetResult() CONST
{
	return m_nResult;
}

VOID CTCItem::SetStatus(UINT nStatus)
{
	m_nStatus = nStatus;
}

UINT CTCItem::GetStatus() CONST
{
	return m_nStatus;
}

BOOL CTCItem::Copy(CONST CTCItem *pItem)
{
	m_szName = pItem->m_szName;
	m_nType = pItem->m_nType;
	m_nFlags = pItem->m_nFlags;
	m_nResult = pItem->m_nResult;
	m_nStatus = pItem->m_nStatus;
	m_nSourceType = pItem->m_nSourceType;
	m_nQueuedSize = pItem->m_nQueuedSize;
	m_nProperties.Copy(pItem->m_nProperties);
	m_szComputerName = pItem->m_szComputerName;
	m_szMembership[0] = pItem->m_szMembership[0];
	m_szMembership[1] = pItem->m_szMembership[1];
	m_nMembershipID = pItem->m_nMembershipID;
	m_nMembershipSize = pItem->m_nMembershipSize;
	m_szReleaseBlock = pItem->m_szReleaseBlock;
	m_nReleaseBlockID = pItem->m_nReleaseBlockID;
	m_pBlockedItems.Copy(&pItem->m_pBlockedItems);
	m_szInterlock[0] = pItem->m_szInterlock[0];
	m_szInterlock[1] = pItem->m_szInterlock[1];
	m_cInterlock[0].Copy(&pItem->m_cInterlock[0]);
	m_cInterlock[1].Copy(&pItem->m_cInterlock[1]);
	m_nPacketData.Copy(pItem->m_nPacketData);
	m_szMemoryPatch = pItem->m_szMemoryPatch;
	m_tKeyID = pItem->m_tKeyID.GetTime();
	m_tLoadTime = pItem->m_tLoadTime.GetTime();
	m_tArmTime = pItem->m_tArmTime.GetTime();
	m_tDispatchTime = pItem->m_tDispatchTime;
	m_tReleaseTime[0] = pItem->m_tReleaseTime[0];
	m_tReleaseTime[1] = pItem->m_tReleaseTime[1];
	m_tReleaseTime[2] = pItem->m_tReleaseTime[2];
	m_tReleaseTimeInterval = pItem->m_tReleaseTimeInterval;
	m_bReleaseTimeOffset[0] = pItem->m_bReleaseTimeOffset[0];
	m_bReleaseTimeOffset[1] = pItem->m_bReleaseTimeOffset[1];
	m_dwReleaseTimeOffset[0] = pItem->m_dwReleaseTimeOffset[0];
	m_dwReleaseTimeOffset[1] = pItem->m_dwReleaseTimeOffset[1];
	m_bReleaseInterlock = pItem->m_bReleaseInterlock;
	m_nReleaseIDs.Copy(pItem->m_nReleaseIDs);
	m_nExecutionMode = pItem->m_nExecutionMode;
	m_tExecutionTime = pItem->m_tExecutionTime;
	m_nExecutionOBRT = pItem->m_nExecutionOBRT;
	m_bExecutionOBRT = pItem->m_bExecutionOBRT;
	m_dwExecutionTimeOffset = pItem->m_dwExecutionTimeOffset;
	m_bExecutionTimeOffset = pItem->m_bExecutionTimeOffset;
	m_bEarlierExecution = pItem->m_bEarlierExecution;
	m_tTransmissionTime = pItem->m_tTransmissionTime;
	m_tDownloadDumpTime = pItem->m_tDownloadDumpTime.GetTime();
	m_tAcknowledgeTime = pItem->m_tAcknowledgeTime.GetTime();
	m_nAuthorizationStatus = pItem->m_nAuthorizationStatus;
	m_szVerificationModuleFileName = pItem->m_szVerificationModuleFileName;
	m_szVerificationProcedure = pItem->m_szVerificationProcedure;
	m_szVerificationThread = pItem->m_szVerificationThread;
	m_szVerificationStep = pItem->m_szVerificationStep;
	m_nVerificationID = pItem->m_nVerificationID;
	m_hVerificationModule = pItem->m_hVerificationModule;
	m_hVerificationResult[0] = pItem->m_hVerificationResult[0];
	m_hVerificationResult[1] = pItem->m_hVerificationResult[1];
	m_tVerificationTime = pItem->m_tVerificationTime.GetTime();
	m_nVerificationStageIDs[0].Copy(pItem->m_nVerificationStageIDs[0]);
	m_nVerificationStageIDs[1].Copy(pItem->m_nVerificationStageIDs[1]);
	m_nVerificationStageIDs[2].Copy(pItem->m_nVerificationStageIDs[2]);
	m_nVerificationStageIDs[3].Copy(pItem->m_nVerificationStageIDs[3]);
	m_tVerificationStageTimeWindows[0].Copy(pItem->m_tVerificationStageTimeWindows[0]);
	m_tVerificationStageTimeWindows[1].Copy(pItem->m_tVerificationStageTimeWindows[1]);
	m_tVerificationStageTimeWindows[2].Copy(pItem->m_tVerificationStageTimeWindows[2]);
	m_szVerificationStageParameters.Copy(pItem->m_szVerificationStageParameters);
	m_nVerificationStageStates[0].Copy(pItem->m_nVerificationStageStates[0]);
	m_nVerificationStageStates[1].Copy(pItem->m_nVerificationStageStates[1]);
	m_szVerificationStageClosures.Copy(pItem->m_szVerificationStageClosures);
	return((m_cPacket.Copy(&pItem->m_cPacket) && m_pParameters.Copy(&pItem->m_pParameters)) ? CDatabaseTCFunction::Copy(pItem) : FALSE);
}

BOOL CTCItem::Compare(CONST CTCItem *pItem) CONST
{
	INT  nClosure;
	INT  nClosures;
	INT  nState[2];
	INT  nStates[2];
	INT  nParameter;
	INT  nParameters;
	INT  nTimeWindow[3];
	INT  nTimeWindows[3];
	CUIntArray  nReleaseIDs[2];

	for (nTimeWindow[0] = 0, nTimeWindows[0] = (pItem->m_szName == m_szName && !pItem->m_szComputerName.CompareNoCase(m_szComputerName) && pItem->m_nSourceType == m_nSourceType && pItem->m_nType == m_nType && pItem->m_nFlags == m_nFlags && pItem->m_nProperties.GetSize() == m_nProperties.GetSize() && !memcmp(pItem->m_nProperties.GetData(), m_nProperties.GetData(), m_nProperties.GetSize()*sizeof(BYTE)) && pItem->m_nQueuedSize == m_nQueuedSize && pItem->m_szMembership[0] == m_szMembership[0] && pItem->m_szMembership[1] == m_szMembership[1] && pItem->m_nMembershipID == m_nMembershipID && pItem->m_nMembershipSize == m_nMembershipSize && pItem->m_szReleaseBlock == m_szReleaseBlock && pItem->m_nReleaseBlockID == m_nReleaseBlockID && pItem->m_pBlockedItems.Compare(&m_pBlockedItems) && pItem->m_szInterlock[0] == m_szInterlock[0] && pItem->m_szInterlock[1] == m_szInterlock[1] && pItem->m_bReleaseInterlock == m_bReleaseInterlock && pItem->m_cInterlock[0].Compare(&m_cInterlock[0]) && pItem->m_cInterlock[1].Compare(&m_cInterlock[1]) && pItem->m_szMemoryPatch == m_szMemoryPatch && pItem->m_cPacket.Compare(&m_cPacket) && pItem->m_pParameters.Compare(&m_pParameters) && pItem->m_tKeyID == m_tKeyID && pItem->m_tLoadTime == m_tLoadTime && pItem->m_tArmTime == m_tArmTime && pItem->m_tDispatchTime == m_tDispatchTime && pItem->m_tReleaseTime[0] == m_tReleaseTime[0] && pItem->m_tReleaseTime[1] == m_tReleaseTime[1] && pItem->m_tReleaseTime[2] == m_tReleaseTime[2] && pItem->m_tReleaseTimeInterval == m_tReleaseTimeInterval && pItem->m_dwReleaseTimeOffset[0] == m_dwReleaseTimeOffset[0] && pItem->m_dwReleaseTimeOffset[1] == m_dwReleaseTimeOffset[1] && pItem->m_bReleaseTimeOffset[0] == m_bReleaseTimeOffset[0] && pItem->m_bReleaseTimeOffset[1] == m_bReleaseTimeOffset[1] && pItem->GetReleaseIDs(nReleaseIDs[0]) == GetReleaseIDs(nReleaseIDs[1]) && !memcmp(nReleaseIDs[0].GetData(), nReleaseIDs[1].GetData(), nReleaseIDs[0].GetSize()*sizeof(UINT)) && pItem->m_tTransmissionTime == m_tTransmissionTime && pItem->m_tExecutionTime == m_tExecutionTime && pItem->m_dwExecutionTimeOffset == m_dwExecutionTimeOffset && pItem->m_bExecutionTimeOffset == m_bExecutionTimeOffset && pItem->m_bEarlierExecution == m_bEarlierExecution && pItem->m_nExecutionOBRT == m_nExecutionOBRT && pItem->m_bExecutionOBRT == m_bExecutionOBRT && pItem->m_nExecutionMode == m_nExecutionMode && pItem->m_tDownloadDumpTime == m_tDownloadDumpTime && pItem->m_tAcknowledgeTime == m_tAcknowledgeTime && pItem->m_nAuthorizationStatus == m_nAuthorizationStatus && !pItem->m_szVerificationModuleFileName.CompareNoCase(m_szVerificationModuleFileName) && pItem->m_szVerificationProcedure == m_szVerificationProcedure && pItem->m_szVerificationThread == m_szVerificationThread && pItem->m_szVerificationStep == m_szVerificationStep && pItem->m_nVerificationID == m_nVerificationID && pItem->m_hVerificationModule == m_hVerificationModule && pItem->m_hVerificationResult[0] == m_hVerificationResult[0] && pItem->m_hVerificationResult[1] == m_hVerificationResult[1] && pItem->m_tVerificationTime == m_tVerificationTime && pItem->m_nVerificationStageIDs[0].GetSize() == m_nVerificationStageIDs[0].GetSize() && !memcmp(pItem->m_nVerificationStageIDs[0].GetData(), m_nVerificationStageIDs[0].GetData(), m_nVerificationStageIDs[0].GetSize()*sizeof(UINT)) && pItem->m_tVerificationStageTimeWindows[0].GetSize() == m_tVerificationStageTimeWindows[0].GetSize() && pItem->m_nPacketData.GetSize() == m_nPacketData.GetSize() && !memcmp(pItem->m_nPacketData.GetData(), m_nPacketData.GetData(), m_nPacketData.GetSize()*sizeof(BYTE)) && pItem->m_nResult == m_nResult && pItem->m_nStatus == m_nStatus) ? (INT)m_tVerificationStageTimeWindows[0].GetSize() : -1; nTimeWindow[0] < nTimeWindows[0]; nTimeWindow[0]++)
	{
		if (pItem->m_tVerificationStageTimeWindows[0].GetAt(nTimeWindow[0]) != m_tVerificationStageTimeWindows[0].GetAt(nTimeWindow[0])) break;
		continue;
	}
	for (nTimeWindow[1] = 0, nTimeWindows[1] = (pItem->m_tVerificationStageTimeWindows[1].GetSize() == m_tVerificationStageTimeWindows[1].GetSize()) ? (INT)m_tVerificationStageTimeWindows[1].GetSize() : -1; nTimeWindow[1] < nTimeWindows[1]; nTimeWindow[1]++)
	{
		if (pItem->m_tVerificationStageTimeWindows[1].GetAt(nTimeWindow[1]) != m_tVerificationStageTimeWindows[1].GetAt(nTimeWindow[1])) break;
		continue;
	}
	for (nTimeWindow[2] = 0, nTimeWindows[2] = (pItem->m_tVerificationStageTimeWindows[2].GetSize() == m_tVerificationStageTimeWindows[2].GetSize()) ? (INT)m_tVerificationStageTimeWindows[2].GetSize() : -1; nTimeWindow[2] < nTimeWindows[2]; nTimeWindow[2]++)
	{
		if (pItem->m_tVerificationStageTimeWindows[2].GetAt(nTimeWindow[2]) != m_tVerificationStageTimeWindows[2].GetAt(nTimeWindow[2])) break;
		continue;
	}
	for (nState[0] = 0, nStates[0] = (pItem->m_nVerificationStageIDs[1].GetSize() == m_nVerificationStageIDs[1].GetSize() && !memcmp(pItem->m_nVerificationStageIDs[1].GetData(), m_nVerificationStageIDs[1].GetData(), m_nVerificationStageIDs[1].GetSize()*sizeof(UINT)) && pItem->m_nVerificationStageStates[0].GetSize() == m_nVerificationStageStates[0].GetSize()) ? (INT)pItem->m_nVerificationStageStates[0].GetSize() : -1; nState[0] < nStates[0]; nState[0]++)
	{
		if (pItem->m_nVerificationStageStates[0].GetAt(nState[0]) != m_nVerificationStageStates[0].GetAt(nState[0])) break;
		continue;
	}
	for (nState[1] = 0, nStates[1] = (pItem->m_nVerificationStageStates[1].GetSize() == m_nVerificationStageStates[1].GetSize()) ? (INT)pItem->m_nVerificationStageStates[1].GetSize() : -1; nState[1] < nStates[1]; nState[1]++)
	{
		if (pItem->m_nVerificationStageStates[1].GetAt(nState[1]) != m_nVerificationStageStates[1].GetAt(nState[1])) break;
		continue;
	}
	for (nParameter = 0, nParameters = (pItem->m_nVerificationStageIDs[2].GetSize() == m_nVerificationStageIDs[2].GetSize() && !memcmp(pItem->m_nVerificationStageIDs[2].GetData(), m_nVerificationStageIDs[2].GetData(), m_nVerificationStageIDs[2].GetSize()*sizeof(UINT)) && pItem->m_szVerificationStageParameters.GetSize() == m_szVerificationStageParameters.GetSize()) ? (INT)m_szVerificationStageParameters.GetSize() : -1; nParameter < nParameters; nParameter++)
	{
		if (pItem->m_szVerificationStageParameters.GetAt(nParameter) != m_szVerificationStageParameters.GetAt(nParameter)) break;
		continue;
	}
	for (nClosure = 0, nClosures = (pItem->m_nVerificationStageIDs[3].GetSize() == m_nVerificationStageIDs[3].GetSize() && !memcmp(pItem->m_nVerificationStageIDs[3].GetData(), m_nVerificationStageIDs[3].GetData(), m_nVerificationStageIDs[3].GetSize()*sizeof(UINT)) && pItem->m_szVerificationStageClosures.GetSize() == m_szVerificationStageClosures.GetSize()) ? (INT)pItem->m_szVerificationStageClosures.GetSize() : -1; nClosure < nClosures; nClosure++)
	{
		if (pItem->m_szVerificationStageClosures.GetAt(nClosure) != m_szVerificationStageClosures.GetAt(nClosure)) break;
		continue;
	}
	return((nTimeWindow[0] == nTimeWindows[0] && nTimeWindow[1] == nTimeWindows[1] && nTimeWindow[2] == nTimeWindows[2] && nParameter == nParameters  &&  nState[0] == nStates[0] && nState[1] == nStates[1] && nClosure == nClosures) ? CDatabaseTCFunction::Compare(pItem) : FALSE);
}

BOOL CTCItem::IsIdentical(CONST CTCItem *pItem) CONST
{
	return((!pItem->GetComputerName().CompareNoCase(m_szComputerName) && pItem->GetSourceType() == m_nSourceType  &&  !pItem->GetName().Compare(m_szName) && !pItem->GetMembership().Compare(m_szMembership[0]) && pItem->GetMembershipID() == m_nMembershipID && (pItem->GetFlags() & (m_nFlags & (TCITEM_EXECUTIONFLAG_IMMEDIATE | TCITEM_EXECUTIONFLAG_TIMETAGGED | TCITEM_EXECUTIONFLAG_1STSTEP | TCITEM_EXECUTIONFLAG_2NDSTEP))) == (m_nFlags & (TCITEM_EXECUTIONFLAG_IMMEDIATE | TCITEM_EXECUTIONFLAG_TIMETAGGED | TCITEM_EXECUTIONFLAG_1STSTEP | TCITEM_EXECUTIONFLAG_2NDSTEP)) && pItem->GetLoadTime() == m_tLoadTime) ? (pItem->m_tKeyID == m_tKeyID) : FALSE);
}

BOOL CTCItem::Map(CByteArray &nInfo, BOOL bAll) CONST
{
	DATA  sData;
	INT  cbData;
	INT  nClosure;
	INT  nClosures;
	INT  nParameter;
	INT  nParameters;
	CByteArray  nPacketData;
	CByteArray  nFunctionData;
	CByteArray  nBlockedItemsData;
	CByteArray  nInterlockData[2];
	CByteArray  nParametersData[2];
	CByteArray  nTimeWindowsData[3];
	CByteArray  nClosuresData;

	sData.cbName = (m_szName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbProperties = (INT)(m_nProperties.GetSize()*sizeof(BYTE));
	sData.cbPacketData = (INT)(m_nPacketData.GetSize()*sizeof(BYTE));
	sData.cbMemoryPatch = (m_szMemoryPatch.GetLength() + 1)*sizeof(TCHAR);
	sData.cbReleaseBlock = (m_szReleaseBlock.GetLength() + 1)*sizeof(TCHAR);
	sData.cbComputerName = (m_szComputerName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbMembership[0] = (m_szMembership[0].GetLength() + 1)*sizeof(TCHAR);
	sData.cbMembership[1] = (m_szMembership[1].GetLength() + 1)*sizeof(TCHAR);
	sData.cbInterlock[0][0] = (m_szInterlock[0].GetLength() + 1)*sizeof(TCHAR);
	sData.cbInterlock[0][1] = (m_szInterlock[1].GetLength() + 1)*sizeof(TCHAR);
	sData.cbInterlock[1][0] = (bAll) ? ((m_cInterlock[0].Map(nInterlockData[0])) ? (INT)nInterlockData[0].GetSize() : -1) : 0;
	sData.cbInterlock[1][1] = (bAll) ? ((m_cInterlock[1].Map(nInterlockData[1])) ? (INT)nInterlockData[1].GetSize() : -1) : 0;
	sData.cbVerificationModuleFileName = (m_szVerificationModuleFileName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbVerificationProcedure = (m_szVerificationProcedure.GetLength() + 1)*sizeof(TCHAR);
	sData.cbVerificationThread = (m_szVerificationThread.GetLength() + 1)*sizeof(TCHAR);
	sData.cbVerificationStep = (m_szVerificationStep.GetLength() + 1)*sizeof(TCHAR);
	sData.cbVerificationStageIDs[0] = (INT)(m_nVerificationStageIDs[0].GetSize()*sizeof(UINT));
	sData.cbVerificationStageIDs[1] = (bAll) ? (INT)(m_nVerificationStageIDs[1].GetSize()*sizeof(UINT)) : 0;
	sData.cbVerificationStageIDs[2] = (bAll) ? (INT)(m_nVerificationStageIDs[2].GetSize()*sizeof(UINT)) : 0;
	sData.cbVerificationStageIDs[3] = (INT)(m_nVerificationStageIDs[3].GetSize()*sizeof(UINT));
	sData.cbVerificationStageTimeWindows[0] = m_tVerificationStageTimeWindows[0].Map(nTimeWindowsData[0]);
	sData.cbVerificationStageTimeWindows[1] = m_tVerificationStageTimeWindows[1].Map(nTimeWindowsData[1]);
	sData.cbVerificationStageTimeWindows[2] = m_tVerificationStageTimeWindows[2].Map(nTimeWindowsData[2]);
	sData.cbVerificationStageStates[0] = (bAll) ? (INT)(m_nVerificationStageStates[0].GetSize()*sizeof(UINT)) : 0;
	sData.cbVerificationStageStates[1] = (bAll) ? (INT)(m_nVerificationStageStates[1].GetSize()*sizeof(UINT)) : 0;
	sData.cbBlockedItems = (m_pBlockedItems.Map(nBlockedItemsData)) ? (INT)nBlockedItemsData.GetSize() : -1;
	sData.cbParameters = (m_pParameters.Map(nParametersData[0])) ? (INT)nParametersData[0].GetSize() : -1;
	sData.cbFunction = (CDatabaseTCFunction::Map(nFunctionData)) ? (INT)nFunctionData.GetSize() : -1;
	sData.cbPacket = (m_cPacket.Map(nPacketData)) ? (INT)nPacketData.GetSize() : -1;
	for (nParameter = 0, nParameters = (bAll) ? (INT)m_szVerificationStageParameters.GetSize() : 0, sData.cbVerificationStageParameters = 0; nParameter < nParameters; nParameter++, sData.cbVerificationStageParameters += cbData)
	{
		nParametersData[1].SetSize(sData.cbVerificationStageParameters + (cbData = (m_szVerificationStageParameters.GetAt(nParameter).GetLength() + 1)*sizeof(TCHAR)));
		CopyMemory(nParametersData[1].GetData() + sData.cbVerificationStageParameters, (LPCTSTR)m_szVerificationStageParameters.GetAt(nParameter), cbData);
	}
	for (nClosure = 0, nClosures = (INT)m_szVerificationStageClosures.GetSize(), sData.cbVerificationStageClosures = 0; nClosure < nClosures; nClosure++, sData.cbVerificationStageClosures += cbData)
	{
		nClosuresData.SetSize(sData.cbVerificationStageClosures + (cbData = (m_szVerificationStageClosures.GetAt(nClosure).GetLength() + 1)*sizeof(TCHAR)));
		CopyMemory(nClosuresData.GetData() + sData.cbVerificationStageClosures, (LPCTSTR)m_szVerificationStageClosures.GetAt(nClosure), cbData);
	}
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbName + sData.cbProperties + sData.cbPacketData + sData.cbComputerName + sData.cbMembership[0] + sData.cbMembership[1] + sData.cbReleaseBlock + max(sData.cbBlockedItems, 0) + sData.cbInterlock[0][0] + sData.cbInterlock[0][1] + max(sData.cbInterlock[1][0], 0) + max(sData.cbInterlock[1][1], 0) + sData.cbMemoryPatch + sData.cbVerificationModuleFileName + sData.cbVerificationProcedure + sData.cbVerificationThread + sData.cbVerificationStep + sData.cbVerificationStageIDs[0] + sData.cbVerificationStageIDs[1] + sData.cbVerificationStageIDs[2] + sData.cbVerificationStageIDs[3] + sData.cbVerificationStageTimeWindows[0] + sData.cbVerificationStageTimeWindows[1] + sData.cbVerificationStageTimeWindows[2] + sData.cbVerificationStageParameters + sData.cbVerificationStageStates[0] + sData.cbVerificationStageStates[1] + sData.cbVerificationStageClosures + max(sData.cbParameters, 0) + max(sData.cbFunction, 0) + max(sData.cbPacket, 0))), sData.nSourceType = m_nSourceType, sData.nType = m_nType, sData.nFlags = m_nFlags, sData.nQueuedSize = m_nQueuedSize, sData.nMembershipID = m_nMembershipID, sData.nMembershipSize = m_nMembershipSize, sData.tKeyID = (bAll) ? m_tKeyID.GetTime() : 0, sData.tLoadTime = (bAll) ? m_tLoadTime.GetTime() : 0, sData.tArmTime = (bAll) ? m_tArmTime.GetTime() : 0, sData.tDispatchTime = (bAll) ? m_tDispatchTime.GetTime() : 0, sData.nReleaseBlockID = m_nReleaseBlockID, sData.bReleaseInterlock = m_bReleaseInterlock, sData.tReleaseTime[0] = m_tReleaseTime[0].GetTime(), sData.tReleaseTime[1] = m_tReleaseTime[1].GetTime(), sData.tReleaseTime[2] = (bAll) ? m_tReleaseTime[2].GetTime() : 0, sData.tReleaseTimeInterval = m_tReleaseTimeInterval.GetTotalSeconds(), sData.dwReleaseTimeOffset[0] = m_dwReleaseTimeOffset[0], sData.dwReleaseTimeOffset[1] = m_dwReleaseTimeOffset[1], sData.bReleaseTimeOffset[0] = m_bReleaseTimeOffset[0], sData.bReleaseTimeOffset[1] = m_bReleaseTimeOffset[1], sData.tTransmissionTime = (bAll) ? m_tTransmissionTime.GetTime() : 0, sData.tExecutionTime = m_tExecutionTime.GetTime(), sData.dwExecutionTimeOffset = m_dwExecutionTimeOffset, sData.bExecutionTimeOffset = m_bExecutionTimeOffset, sData.bEarlierExecution = m_bEarlierExecution, sData.nExecutionOBRT = m_nExecutionOBRT, sData.bExecutionOBRT = m_bExecutionOBRT, sData.nExecutionMode = m_nExecutionMode, sData.tDownloadDumpTime = (bAll) ? m_tDownloadDumpTime.GetTime() : 0, sData.tAcknowledgeTime = (bAll) ? m_tAcknowledgeTime.GetTime() : 0, sData.tVerificationTime = (bAll) ? m_tVerificationTime.GetTime() : 0, sData.nStatus = (bAll) ? m_nStatus : TCITEM_STATUS_NONE, sData.nResult = (bAll) ? m_nResult : TCITEM_RESULT_NONE; nInfo.GetSize() == sData.cbSize && sData.cbBlockedItems >= 0 && sData.cbInterlock[1][0] >= 0 && sData.cbInterlock[1][1] >= 0 && sData.cbParameters >= 0 && sData.cbFunction >= 0 && sData.cbPacket >= 0; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szName, sData.cbName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbName), m_nProperties.GetData(), sData.cbProperties);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbProperties), m_nPacketData.GetData(), sData.cbPacketData);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbPacketData), (LPCTSTR)m_szComputerName, sData.cbComputerName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbComputerName), (LPCTSTR)m_szMembership[0], sData.cbMembership[0]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbMembership[0]), (LPCTSTR)m_szMembership[1], sData.cbMembership[1]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbMembership[1]), (LPCTSTR)m_szReleaseBlock, sData.cbReleaseBlock);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbReleaseBlock), nBlockedItemsData.GetData(), sData.cbBlockedItems);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbBlockedItems), (LPCTSTR)m_szInterlock[0], sData.cbInterlock[0][0]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbInterlock[0][0]), (LPCTSTR)m_szInterlock[1], sData.cbInterlock[0][1]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbInterlock[0][1]), nInterlockData[0].GetData(), sData.cbInterlock[1][0]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbInterlock[1][0]), nInterlockData[1].GetData(), sData.cbInterlock[1][1]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbInterlock[1][1]), (LPCTSTR)m_szMemoryPatch, sData.cbMemoryPatch);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbMemoryPatch), (LPCTSTR)m_szVerificationModuleFileName, sData.cbVerificationModuleFileName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbVerificationModuleFileName), (LPCTSTR)m_szVerificationProcedure, sData.cbVerificationProcedure);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbVerificationProcedure), (LPCTSTR)m_szVerificationThread, sData.cbVerificationThread);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbVerificationThread), (LPCTSTR)m_szVerificationStep, sData.cbVerificationStep);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbVerificationStep), m_nVerificationStageIDs[0].GetData(), sData.cbVerificationStageIDs[0]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbVerificationStageIDs[0]), m_nVerificationStageIDs[1].GetData(), sData.cbVerificationStageIDs[1]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbVerificationStageIDs[1]), m_nVerificationStageIDs[2].GetData(), sData.cbVerificationStageIDs[2]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbVerificationStageIDs[2]), m_nVerificationStageIDs[3].GetData(), sData.cbVerificationStageIDs[3]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbVerificationStageIDs[3]), nTimeWindowsData[0].GetData(), sData.cbVerificationStageTimeWindows[0]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbVerificationStageTimeWindows[0]), nTimeWindowsData[1].GetData(), sData.cbVerificationStageTimeWindows[1]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbVerificationStageTimeWindows[1]), nTimeWindowsData[2].GetData(), sData.cbVerificationStageTimeWindows[2]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbVerificationStageTimeWindows[2]), nParametersData[1].GetData(), sData.cbVerificationStageParameters);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbVerificationStageParameters), m_nVerificationStageStates[0].GetData(), sData.cbVerificationStageStates[0]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbVerificationStageStates[0]), m_nVerificationStageStates[1].GetData(), sData.cbVerificationStageStates[1]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbVerificationStageStates[1]), nClosuresData.GetData(), sData.cbVerificationStageClosures);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbVerificationStageClosures), nParametersData[0].GetData(), sData.cbParameters);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbParameters), nFunctionData.GetData(), sData.cbFunction);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbFunction), nPacketData.GetData(), sData.cbPacket);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCItem::Unmap(CONST CByteArray &nInfo, BOOL bAll)
{
	DATA  sData;
	INT  cbData;
	INT  cbClosure;
	INT  cbClosures;
	INT  cbParameter;
	INT  cbParameters;
	CByteArray  nPacketData;
	CByteArray  nFunctionData;
	CByteArray  nBlockedItemsData;
	CByteArray  nInterlockData[2];
	CByteArray  nParametersData[2];
	CByteArray  nTimeWindowsData[3];
	CByteArray  nClosuresData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbName + sData.cbProperties + sData.cbPacketData + sData.cbComputerName + sData.cbMembership[0] + sData.cbMembership[1] + sData.cbReleaseBlock + sData.cbBlockedItems + sData.cbInterlock[0][0] + sData.cbInterlock[0][1] + sData.cbInterlock[1][0] + sData.cbInterlock[1][1] + sData.cbMemoryPatch + sData.cbVerificationModuleFileName + sData.cbVerificationProcedure + sData.cbVerificationThread + sData.cbVerificationStep + sData.cbVerificationStageIDs[0] + sData.cbVerificationStageIDs[1] + sData.cbVerificationStageIDs[2] + sData.cbVerificationStageIDs[3] + sData.cbVerificationStageTimeWindows[0] + sData.cbVerificationStageTimeWindows[1] + sData.cbVerificationStageTimeWindows[2] + sData.cbVerificationStageParameters + sData.cbVerificationStageStates[0] + sData.cbVerificationStageStates[1] + sData.cbVerificationStageClosures + sData.cbParameters + sData.cbFunction + sData.cbPacket && sData.cbName > 0 && sData.cbProperties >= 0 && sData.cbPacketData >= 0 && sData.cbComputerName > 0 && sData.cbMembership[0] > 0 && sData.cbMembership[1] > 0 && sData.cbReleaseBlock > 0 && sData.cbBlockedItems >= 0 && sData.cbInterlock[0][0] > 0 && sData.cbInterlock[0][1] > 0 && sData.cbInterlock[1][0] >= 0 && sData.cbInterlock[1][1] >= 0 && sData.cbMemoryPatch > 0 && sData.cbVerificationModuleFileName > 0 && sData.cbVerificationProcedure > 0 && sData.cbVerificationThread > 0 && sData.cbVerificationStep > 0 && sData.cbVerificationStageIDs[0] >= 0 && sData.cbVerificationStageIDs[1] >= 0 && sData.cbVerificationStageIDs[2] >= 0 && sData.cbVerificationStageIDs[3] >= 0 && sData.cbVerificationStageTimeWindows[0] >= 0 && sData.cbVerificationStageTimeWindows[1] >= 0 && sData.cbVerificationStageTimeWindows[2] >= 0 && sData.cbVerificationStageParameters >= 0 && sData.cbVerificationStageStates[0] >= 0 && sData.cbVerificationStageStates[1] >= 0 && sData.cbVerificationStageClosures >= 0 && sData.cbParameters >= 0 && sData.cbFunction >= 0 && sData.cbPacket >= 0; )
	{
		for (m_nProperties.SetSize(sData.cbProperties), m_nPacketData.SetSize(sData.cbPacketData), nBlockedItemsData.SetSize(sData.cbBlockedItems), nInterlockData[0].SetSize(sData.cbInterlock[1][0]), nInterlockData[1].SetSize(sData.cbInterlock[1][1]), m_nVerificationStageIDs[0].SetSize(sData.cbVerificationStageIDs[0] / sizeof(UINT)), m_nVerificationStageIDs[1].SetSize(sData.cbVerificationStageIDs[1] / sizeof(UINT)), m_nVerificationStageIDs[2].SetSize(sData.cbVerificationStageIDs[2] / sizeof(UINT)), m_nVerificationStageIDs[3].SetSize(sData.cbVerificationStageIDs[3] / sizeof(UINT)), nTimeWindowsData[0].SetSize(sData.cbVerificationStageTimeWindows[0]), nTimeWindowsData[1].SetSize(sData.cbVerificationStageTimeWindows[1]), nTimeWindowsData[2].SetSize(sData.cbVerificationStageTimeWindows[2]), nParametersData[1].SetSize(sData.cbVerificationStageParameters), m_nVerificationStageStates[0].SetSize(sData.cbVerificationStageStates[0] / sizeof(UINT)), m_nVerificationStageStates[1].SetSize(sData.cbVerificationStageStates[1] / sizeof(UINT)), nClosuresData.SetSize(sData.cbVerificationStageClosures), nParametersData[0].SetSize(sData.cbParameters), nFunctionData.SetSize(sData.cbFunction), nPacketData.SetSize(sData.cbPacket), CopyMemory(m_szName.GetBufferSetLength(STRINGCHARS(sData.cbName)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbName)), CopyMemory(m_nProperties.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbName), sData.cbProperties), CopyMemory(m_nPacketData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbProperties), sData.cbPacketData), CopyMemory(m_szComputerName.GetBufferSetLength(STRINGCHARS(sData.cbComputerName)), nInfo.GetData() + (cbData = cbData + sData.cbPacketData), STRINGBYTES(sData.cbComputerName)), CopyMemory(m_szMembership[0].GetBufferSetLength(STRINGCHARS(sData.cbMembership[0])), nInfo.GetData() + (cbData = cbData + sData.cbComputerName), STRINGBYTES(sData.cbMembership[0])), CopyMemory(m_szMembership[1].GetBufferSetLength(STRINGCHARS(sData.cbMembership[1])), nInfo.GetData() + (cbData = cbData + sData.cbMembership[0]), STRINGBYTES(sData.cbMembership[1])), CopyMemory(m_szReleaseBlock.GetBufferSetLength(STRINGCHARS(sData.cbReleaseBlock)), nInfo.GetData() + (cbData = cbData + sData.cbMembership[1]), STRINGBYTES(sData.cbReleaseBlock)), CopyMemory(nBlockedItemsData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbReleaseBlock), sData.cbBlockedItems), CopyMemory(m_szInterlock[0].GetBufferSetLength(STRINGCHARS(sData.cbInterlock[0][0])), nInfo.GetData() + (cbData = cbData + sData.cbBlockedItems), STRINGBYTES(sData.cbInterlock[0][0])), CopyMemory(m_szInterlock[1].GetBufferSetLength(STRINGCHARS(sData.cbInterlock[0][1])), nInfo.GetData() + (cbData = cbData + sData.cbInterlock[0][0]), STRINGBYTES(sData.cbInterlock[0][1])), CopyMemory(nInterlockData[0].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbInterlock[0][1]), sData.cbInterlock[1][0]), CopyMemory(nInterlockData[1].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbInterlock[1][0]), sData.cbInterlock[1][1]), CopyMemory(m_szMemoryPatch.GetBufferSetLength(STRINGCHARS(sData.cbMemoryPatch)), nInfo.GetData() + (cbData = cbData + sData.cbInterlock[1][1]), STRINGBYTES(sData.cbMemoryPatch)), CopyMemory(m_szVerificationModuleFileName.GetBufferSetLength(STRINGCHARS(sData.cbVerificationModuleFileName)), nInfo.GetData() + (cbData = cbData + sData.cbMemoryPatch), STRINGBYTES(sData.cbVerificationModuleFileName)), CopyMemory(m_szVerificationProcedure.GetBufferSetLength(STRINGCHARS(sData.cbVerificationProcedure)), nInfo.GetData() + (cbData = cbData + sData.cbVerificationModuleFileName), STRINGBYTES(sData.cbVerificationProcedure)), CopyMemory(m_szVerificationThread.GetBufferSetLength(STRINGCHARS(sData.cbVerificationThread)), nInfo.GetData() + (cbData = cbData + sData.cbVerificationProcedure), STRINGBYTES(sData.cbVerificationThread)), CopyMemory(m_szVerificationStep.GetBufferSetLength(STRINGCHARS(sData.cbVerificationStep)), nInfo.GetData() + (cbData = cbData + sData.cbVerificationThread), STRINGBYTES(sData.cbVerificationStep)), CopyMemory(m_nVerificationStageIDs[0].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbVerificationStep), sData.cbVerificationStageIDs[0]), CopyMemory(m_nVerificationStageIDs[1].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbVerificationStageIDs[0]), sData.cbVerificationStageIDs[1]), CopyMemory(m_nVerificationStageIDs[2].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbVerificationStageIDs[1]), sData.cbVerificationStageIDs[2]), CopyMemory(m_nVerificationStageIDs[3].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbVerificationStageIDs[2]), sData.cbVerificationStageIDs[3]), CopyMemory(nTimeWindowsData[0].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbVerificationStageIDs[3]), sData.cbVerificationStageTimeWindows[0]), CopyMemory(nTimeWindowsData[1].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbVerificationStageTimeWindows[0]), sData.cbVerificationStageTimeWindows[1]), CopyMemory(nTimeWindowsData[2].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbVerificationStageTimeWindows[1]), sData.cbVerificationStageTimeWindows[2]), CopyMemory(nParametersData[1].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbVerificationStageTimeWindows[2]), sData.cbVerificationStageParameters), CopyMemory(m_nVerificationStageStates[0].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbVerificationStageParameters), sData.cbVerificationStageStates[0]), CopyMemory(m_nVerificationStageStates[1].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbVerificationStageStates[0]), sData.cbVerificationStageStates[1]), CopyMemory(nClosuresData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbVerificationStageStates[1]), sData.cbVerificationStageClosures), CopyMemory(nParametersData[0].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbVerificationStageClosures), sData.cbParameters), CopyMemory(nFunctionData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbParameters), sData.cbFunction), CopyMemory(nPacketData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbFunction), sData.cbPacket), m_nSourceType = sData.nSourceType, m_nType = sData.nType, m_nFlags = sData.nFlags, m_nQueuedSize = sData.nQueuedSize, m_nMembershipID = sData.nMembershipID, m_nMembershipSize = sData.nMembershipSize, m_tKeyID = (bAll) ? sData.tKeyID : m_tKeyID, m_tLoadTime = (bAll) ? sData.tLoadTime : m_tLoadTime, m_tArmTime = (bAll) ? sData.tArmTime : m_tArmTime, m_tDispatchTime = (bAll) ? sData.tDispatchTime : m_tDispatchTime, m_nReleaseBlockID = sData.nReleaseBlockID, m_bReleaseInterlock = sData.bReleaseInterlock, m_tReleaseTime[0] = m_tReleaseTime[2] = sData.tReleaseTime[0], m_tReleaseTime[1] = sData.tReleaseTime[1], m_tReleaseTime[2] = (bAll) ? sData.tReleaseTime[2] : m_tReleaseTime[2], m_tReleaseTimeInterval = sData.tReleaseTimeInterval, m_dwReleaseTimeOffset[0] = sData.dwReleaseTimeOffset[0], m_dwReleaseTimeOffset[1] = sData.dwReleaseTimeOffset[1], m_bReleaseTimeOffset[0] = sData.bReleaseTimeOffset[0], m_bReleaseTimeOffset[1] = sData.bReleaseTimeOffset[1], m_tTransmissionTime = sData.tTransmissionTime, m_tExecutionTime = sData.tExecutionTime, m_dwExecutionTimeOffset = sData.dwExecutionTimeOffset, m_bExecutionTimeOffset = sData.bExecutionTimeOffset, m_bEarlierExecution = sData.bEarlierExecution, m_nExecutionOBRT = sData.nExecutionOBRT, m_bExecutionOBRT = sData.bExecutionOBRT, m_nExecutionMode = sData.nExecutionMode, m_tVerificationTime = (bAll) ? sData.tVerificationTime : 0, m_tDownloadDumpTime = (bAll) ? sData.tDownloadDumpTime : 0, m_tAcknowledgeTime = (bAll) ? sData.tAcknowledgeTime : 0, m_nStatus = (bAll) ? sData.nStatus : m_nStatus, m_nResult = (bAll) ? sData.nResult : m_nResult, m_szName.ReleaseBuffer(), m_szMembership[0].ReleaseBuffer(), m_szMembership[1].ReleaseBuffer(), m_szReleaseBlock.ReleaseBuffer(), m_szInterlock[0].ReleaseBuffer(), m_szInterlock[1].ReleaseBuffer(), m_szMemoryPatch.ReleaseBuffer(), m_szVerificationProcedure.ReleaseBuffer(), m_szVerificationThread.ReleaseBuffer(), m_szVerificationStep.ReleaseBuffer(), m_szVerificationModuleFileName.ReleaseBuffer(); m_cPacket.Unmap(nPacketData) && m_pParameters.Unmap(nParametersData[0]) && m_pBlockedItems.Unmap(nBlockedItemsData) && (!nInterlockData[0].GetSize() || m_cInterlock[0].Unmap(nInterlockData[0])) && (!nInterlockData[1].GetSize() || m_cInterlock[1].Unmap(nInterlockData[1])) && m_tVerificationStageTimeWindows[0].Unmap(nTimeWindowsData[0]) && m_tVerificationStageTimeWindows[1].Unmap(nTimeWindowsData[1]) && m_tVerificationStageTimeWindows[2].Unmap(nTimeWindowsData[2]) && CDatabaseTCFunction::Unmap(nFunctionData); )
		{
			for (cbParameters = 0, m_szVerificationStageParameters.RemoveAll(); cbParameters < sData.cbVerificationStageParameters; cbParameters += cbParameter)
			{
				m_szVerificationStageParameters.Add((LPCTSTR)(nParametersData[1].GetData() + cbParameters));
				cbParameter = (m_szVerificationStageParameters.GetAt(m_szVerificationStageParameters.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR);
			}
			for (cbClosures = 0, m_szVerificationStageClosures.RemoveAll(); cbClosures < sData.cbVerificationStageClosures; cbClosures += cbClosure)
			{
				m_szVerificationStageClosures.Add((LPCTSTR)(nClosuresData.GetData() + cbClosures));
				cbClosure = (m_szVerificationStageClosures.GetAt(m_szVerificationStageClosures.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR);
			}
			return TRUE;
		}
		break;
	}
	return FALSE;
}

VOID CTCItem::Initialize(CTCItem *pItem)
{
	pItem->m_tKeyID = (pItem->m_tKeyID == m_tLastKeyID) ? (pItem->m_tKeyID + 1) : pItem->m_tKeyID;
	m_tLastKeyID = pItem->m_tKeyID.GetTime();
}


/////////////////////////////////////////////////////////////////////////////
// CTCItems

CTCItems::CTCItems() : CPtrArray()
{
	return;
}

CTCItems::~CTCItems()
{
	RemoveAll();
}

INT CTCItems::Add(CTCItem *pItem)
{
	return((INT)CPtrArray::Add(pItem));
}

INT CTCItems::Find(CONST CTCItem *pItem) CONST
{
	INT  nItem;
	INT  nItems;

	for (nItem = Find(pItem->GetComputerName(), pItem->GetSourceType(), pItem->GetName(), pItem->GetMembership(), pItem->GetMembershipID(), pItem->GetFlags(), pItem->GetLoadTime()), nItems = (nItem >= 0) ? (INT)GetSize() : -1; nItem < nItems; nItem++)
	{
		if (pItem->IsIdentical(GetAt(nItem))) break;
		continue;
	}
	return((nItem < nItems) ? nItem : -1);
}
INT CTCItems::Find(LPCTSTR pszComputer, UINT nSourceType, LPCTSTR pszName, LPCTSTR pszMembership, UINT nMembershipID, ULONGLONG nFlags, CONST CTimeTag &tLoadTime) CONST
{
	INT  nItem;
	INT  nItems;
	CTCItem  *pItem;

	for (nItem = Find(pszMembership, tLoadTime), nItems = (nItem >= 0) ? (INT)GetSize() : -1; nItem < nItems; nItem++)
	{
		if ((pItem = GetAt(nItem)) && !pItem->GetComputerName().Compare(pszComputer) && pItem->GetSourceType() == nSourceType  &&  !pItem->GetName().Compare(pszName) && !pItem->GetMembership().Compare(pszMembership) && pItem->GetMembershipID() == nMembershipID && ((pItem->GetFlags() & (TCITEM_EXECUTIONFLAG_IMMEDIATE | TCITEM_EXECUTIONFLAG_TIMETAGGED | TCITEM_EXECUTIONFLAG_1STSTEP | TCITEM_EXECUTIONFLAG_2NDSTEP)) == (nFlags & (TCITEM_EXECUTIONFLAG_IMMEDIATE | TCITEM_EXECUTIONFLAG_TIMETAGGED | TCITEM_EXECUTIONFLAG_1STSTEP | TCITEM_EXECUTIONFLAG_2NDSTEP)) || nFlags == (ULONGLONG)-1) && pItem->GetLoadTime() == tLoadTime) break;
		continue;
	}
	return((nItem < nItems) ? nItem : -1);
}
INT CTCItems::Find(LPCTSTR pszName, LPCTSTR pszMembership, UINT nMembershipID, ULONGLONG nFlags, CONST CTimeTag &tLoadTime) CONST
{
	INT  nItem;
	INT  nItems;
	CTCItem  *pItem;

	for (nItem = Find(pszMembership, tLoadTime), nItems = (nItem >= 0) ? (INT)GetSize() : -1; nItem < nItems; nItem++)
	{
		if ((pItem = GetAt(nItem)) && !pItem->GetName().Compare(pszName) && !pItem->GetMembership().Compare(pszMembership) && pItem->GetMembershipID() == nMembershipID && ((pItem->GetFlags() & (TCITEM_EXECUTIONFLAG_IMMEDIATE | TCITEM_EXECUTIONFLAG_TIMETAGGED | TCITEM_EXECUTIONFLAG_1STSTEP | TCITEM_EXECUTIONFLAG_2NDSTEP)) == (nFlags & (TCITEM_EXECUTIONFLAG_IMMEDIATE | TCITEM_EXECUTIONFLAG_TIMETAGGED | TCITEM_EXECUTIONFLAG_1STSTEP | TCITEM_EXECUTIONFLAG_2NDSTEP)) || nFlags == (ULONGLONG)-1) && pItem->GetLoadTime() == tLoadTime) break;
		continue;
	}
	return((nItem < nItems) ? nItem : -1);
}
INT CTCItems::Find(LPCTSTR pszMembership, UINT nMembershipID, CONST CTimeTag &tLoadTime) CONST
{
	INT  nItem;
	INT  nItems;
	CTCItem  *pItem;

	for (nItem = Find(pszMembership, tLoadTime), nItems = (nItem >= 0) ? (INT)GetSize() : -1; nItem < nItems; nItem++)
	{
		if ((pItem = GetAt(nItem)) && !pItem->GetMembership().Compare(pszMembership) && pItem->GetMembershipID() == nMembershipID  &&  pItem->GetLoadTime() == tLoadTime) break;
		continue;
	}
	return((nItem < nItems) ? nItem : -1);
}
INT CTCItems::Find(LPCTSTR pszMembership, CONST CTimeTag &tLoadTime) CONST
{
	INT  nItem;
	INT  nItems;
	CTCItem  *pItem;

	for (nItem = 0, nItems = (INT)GetSize(); nItem < nItems; nItem++)
	{
		if ((pItem = GetAt(nItem)) && !pItem->GetMembership().Compare(pszMembership) && pItem->GetLoadTime() == tLoadTime) break;
		continue;
	}
	return((nItem < nItems) ? nItem : -1);
}

INT CTCItems::Collect(INT nIndex, CUIntArray &nItemIDs) CONST
{
	INT  nItem;
	INT  nItems;
	CTCItem  *pItem[3];

	for (nItemIDs.RemoveAll(); (pItem[0] = GetAt(nIndex)); )
	{
		for (nItem = (!pItem[0]->GetMembership().IsEmpty()) ? Find(pItem[0]->GetMembership(), pItem[0]->GetLoadTime()) : -1, nItems = (INT)GetSize(); nItem < nItems && nItem >= 0 && pItem[0]->GetMembershipSize() >(UINT) nItemIDs.GetSize(); nItem++)
		{
			if ((pItem[1] = GetAt(nItem)) && !pItem[0]->GetComputerName().CompareNoCase(pItem[1]->GetComputerName()) && pItem[0]->GetSourceType() == pItem[1]->GetSourceType() && pItem[0]->GetMembership() == pItem[1]->GetMembership() && pItem[0]->GetLoadTime() == pItem[1]->GetLoadTime())
			{
				nItemIDs.Add(nItem);
				continue;
			}
		}
		if (pItem[0]->GetMembership().IsEmpty())
		{
			for (nItem = nIndex; nItem >= 0; nItem--)
			{
				if ((pItem[1] = GetAt(nItem)) && (pItem[1]->GetFlags() & TCITEM_LINKAGEFLAG_GROUPED)) continue;
				if ((pItem[2] = GetAt(nItem - 1)) && (pItem[1]->GetFlags() & TCITEM_LINKAGEFLAG_BLOCKED) && (pItem[2]->GetFlags() & TCITEM_LINKAGEFLAG_BLOCKED)) continue;
				break;
			}
			for (nItem = max(nItem, 0); nItem < nItems; nItem++)
			{
				if ((pItem[1] = GetAt(nItem)) && (pItem[1]->GetFlags() & (TCITEM_LINKAGEFLAG_GROUPED | TCITEM_LINKAGEFLAG_BLOCKED)))
				{
					nItemIDs.Add(nItem);
					continue;
				}
				if ((pItem[2] = GetAt(nItem + 1)) && (pItem[2]->GetFlags() & TCITEM_LINKAGEFLAG_GROUPED))
				{
					nItemIDs.Add(nItem);
					continue;
				}
				if (nItem == nIndex) nItemIDs.Add(nItem);
				break;
			}
		}
		break;
	}
	return((INT)nItemIDs.GetSize());
}
INT CTCItems::Collect(INT nIndex, CPtrArray &pItems) CONST
{
	INT  nItem;
	INT  nItems;
	CTCItem  *pItem;
	CUIntArray  nItemIDs;

	for (nItem = 0, nItems = Collect(nIndex, nItemIDs), pItems.RemoveAll(); nItem < nItems; nItem++)
	{
		if ((pItem = GetAt(nItemIDs.GetAt(nItem))))
		{
			pItems.Add(pItem);
			continue;
		}
	}
	return((INT)pItems.GetSize());
}
INT CTCItems::Collect(INT nIndex, CTCItems &pItems) CONST
{
	INT  nItem;
	INT  nItems;
	CTCItem  *pItem[2];
	CUIntArray  nItemIDs;

	for (nItem = 0, nItems = Collect(nIndex, nItemIDs), pItems.RemoveAll(); nItem < nItems; nItem++)
	{
		if ((pItem[1] = ((pItem[0] = GetAt(nItemIDs.GetAt(nItem)))) ? new CTCItem : (CTCItem *)NULL))
		{
			if (pItem[1]->Copy(pItem[0]) && pItems.Add(pItem[1]) >= 0) continue;
			delete pItem[1];
		}
		pItems.RemoveAll();
		break;
	}
	return((INT)pItems.GetSize());
}

CTCItem *CTCItems::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCItem *)CPtrArray::GetAt(nIndex) : (CTCItem *)NULL);
}

CTCItem *CTCItems::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCItem *)CPtrArray::GetAt(nIndex) : (CTCItem *)NULL);
}

VOID CTCItems::RemoveAll()
{
	INT  nItem;
	INT  nItems;

	for (nItem = 0, nItems = (INT)GetSize(); nItem < nItems; nItem++)
	{
		delete GetAt(nItem);
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CTCItems::Copy(CONST CTCItems *pItems)
{
	INT  nItem;
	INT  nItems;
	CTCItem  *pItem;

	for (nItem = 0, nItems = (INT)pItems->GetSize(), RemoveAll(); nItem < nItems; nItem++)
	{
		if ((pItem = new CTCItem) != (CTCItem *)NULL)
		{
			pItem->Copy(pItems->GetAt(nItem));
			InsertAt(nItem, pItem, 1);
			continue;
		}
		break;
	}
	return((nItem == nItems) ? TRUE : FALSE);
}

BOOL CTCItems::Compare(CONST CTCItems *pItems) CONST
{
	INT  nItem;
	INT  nItems;
	CTCItem  *pItem;

	for (nItem = 0, nItems = (pItems->GetSize() == GetSize()) ? (INT)GetSize() : -1; nItem < nItems; nItem++)
	{
		if ((pItem = pItems->GetAt(nItem)) && pItem->Compare(GetAt(nItem))) continue;
		break;
	}
	return((nItem == nItems) ? TRUE : FALSE);
}

BOOL CTCItems::Map(CByteArray &nInfo, BOOL bAll) CONST
{
	INT  nItem;
	INT  nItems;
	CTCItem  *pItem;
	CByteArray  nItemData;
	CByteArray  nItemsData;
	CCompressionTools  cCompressionTools;

	for (nItem = 0, nItems = (INT)GetSize(), nInfo.RemoveAll(); nItem < nItems; nItem++)
	{
		if ((pItem = GetAt(nItem)) && pItem->Map(nItemData, bAll) && nItemsData.Append(nItemData) >= 0) continue;
		break;
	}
	return((nItem == nItems) ? cCompressionTools.Compress(nItemsData, nInfo) : FALSE);
}

BOOL CTCItems::Unmap(CONST CByteArray &nInfo, BOOL bAll)
{
	INT  cbItem;
	INT  cbItems;
	CTCItem  *pItem;
	CByteArray  nItemData;
	CByteArray  nItemsData;
	CCompressionTools  cCompressionTools;

	for (cbItems = (cCompressionTools.Decompress(nInfo, nItemsData)) ? 0 : -1, RemoveAll(); cbItems >= 0 && cbItems < nItemsData.GetSize(); cbItems += cbItem)
	{
		for (CopyMemory(&cbItem, nItemsData.GetData() + cbItems, sizeof(cbItem)), nItemData.SetSize(max(min(cbItem, nItemsData.GetSize() - cbItems), 0)); nItemData.GetSize() >= 0; )
		{
			CopyMemory(nItemData.GetData(), nItemsData.GetData() + cbItems, nItemData.GetSize());
			break;
		}
		if ((pItem = new CTCItem))
		{
			if (pItem->Unmap(nItemData, bAll) && Add(pItem) >= 0) continue;
			delete pItem;
		}
		break;
	}
	return((cbItems >= 0 && cbItems == nItemsData.GetSize()) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueue

CTCOnBoardBufferQueue::CTCOnBoardBufferQueue() : CTCItems()
{
	m_nAPID = (UINT)-1;
	m_nSubScheduleID = (UINT)-1;
	m_nLimit = 0;
	m_nCount = (UINT)-1;
	m_tTime = 0;
	m_nFlags = TCONBOARDBUFFERQUEUE_FLAG_NONE;
	m_nStatus = TCONBOARDBUFFERQUEUE_STATUS_NONE;
}

VOID CTCOnBoardBufferQueue::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CTCOnBoardBufferQueue::GetName() CONST
{
	return m_szName;
}

VOID CTCOnBoardBufferQueue::SetType(LPCTSTR pszType)
{
	m_szType = pszType;
}

CString CTCOnBoardBufferQueue::GetType() CONST
{
	return m_szType;
}

VOID CTCOnBoardBufferQueue::SetFlags(UINT nFlags)
{
	m_nFlags = nFlags;
}

UINT CTCOnBoardBufferQueue::GetFlags() CONST
{
	return m_nFlags;
}

VOID CTCOnBoardBufferQueue::SetAPID(UINT nAPID)
{
	m_nAPID = nAPID;
}

UINT CTCOnBoardBufferQueue::GetAPID() CONST
{
	return m_nAPID;
}

VOID CTCOnBoardBufferQueue::SetSubScheduleID(UINT nSubScheduleID)
{
	m_nSubScheduleID = nSubScheduleID;
}

UINT CTCOnBoardBufferQueue::GetSubScheduleID() CONST
{
	return m_nSubScheduleID;
}

VOID CTCOnBoardBufferQueue::SetLimit(UINT nLimit)
{
	m_nLimit = nLimit;
}

UINT CTCOnBoardBufferQueue::GetLimit() CONST
{
	return m_nLimit;
}

VOID CTCOnBoardBufferQueue::SetCount(UINT nCount)
{
	m_nCount = nCount;
}

UINT CTCOnBoardBufferQueue::GetCount() CONST
{
	return m_nCount;
}

VOID CTCOnBoardBufferQueue::SetUnit(LPCTSTR pszUnit)
{
	m_szUnit = pszUnit;
}

CString CTCOnBoardBufferQueue::GetUnit() CONST
{
	return m_szUnit;
}

VOID CTCOnBoardBufferQueue::SetTimeout(CONST CTimeSpan &tTimeout)
{
	m_tTimeout = tTimeout;
}

CTimeSpan CTCOnBoardBufferQueue::GetTimeout() CONST
{
	return m_tTimeout;
}

VOID CTCOnBoardBufferQueue::SetUpdateTime(CONST CTimeTag &tTime)
{
	m_tTime = tTime;
}

CTimeTag CTCOnBoardBufferQueue::GetUpdateTime() CONST
{
	return m_tTime;
}

VOID CTCOnBoardBufferQueue::SetStatus(UINT nStatus)
{
	m_nStatus = nStatus;
}

UINT CTCOnBoardBufferQueue::GetStatus() CONST
{
	return m_nStatus;
}

BOOL CTCOnBoardBufferQueue::Alert(UINT nType, UINT nMessage, LPCTSTR pszMessage, BOOL bOverwrite)
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = (!bOverwrite) ? (INT)m_nAlertMessages.GetSize() : 0, nCount = (INT)m_nAlertMessages.GetSize(); nIndex < nCount; nIndex++)
	{
		if (nMessage == m_nAlertMessages.GetAt(nIndex)) break;
		continue;
	}
	if (nType >= TCONBOARDBUFFERQUEUE_ALERTTYPE_INFORMATION  &&  nType <= TCONBOARDBUFFERQUEUE_ALERTTYPE_ERROR)
	{
		m_nAlertTypes.SetAtGrow(nIndex, nType);
		m_nAlertMessages.SetAtGrow(nIndex, nMessage);
		m_szAlertMessages.SetAtGrow(nIndex, pszMessage);
		return TRUE;
	}
	return FALSE;
}
BOOL CTCOnBoardBufferQueue::Alert(UINT nType, UINT nMessage, BOOL bEnable)
{
	INT  nIndex;
	INT  nCount;

	for (nIndex = ((nType != TCONBOARDBUFFERQUEUE_ALERTTYPE_ANY && !bEnable) || nMessage == (UINT)-1) ? (INT)m_nAlertMessages.GetSize() : 0, nCount = (INT)m_nAlertMessages.GetSize(); nIndex < nCount; nIndex++)
	{
		if ((bEnable  &&  nMessage == m_nAlertMessages.GetAt(nIndex)) || (!bEnable  &&  nMessage == m_nAlertMessages.GetAt(nCount - nIndex - 1))) break;
		continue;
	}
	if (nType >= TCONBOARDBUFFERQUEUE_ALERTTYPE_INFORMATION  &&  nType <= TCONBOARDBUFFERQUEUE_ALERTTYPE_ERROR  &&  nMessage != (UINT)-1 && bEnable)
	{
		m_nAlertTypes.SetAtGrow(nIndex, nType);
		m_nAlertMessages.SetAtGrow(nIndex, nMessage);
		m_szAlertMessages.SetAtGrow(nIndex, EMPTYSTRING);
		return TRUE;
	}
	if (!bEnable)
	{
		if (nMessage != (UINT)-1)
		{
			if (nType == TCONBOARDBUFFERQUEUE_ALERTTYPE_ANY  &&  nIndex < nCount)
			{
				m_nAlertTypes.RemoveAt(nCount - nIndex - 1);
				m_nAlertMessages.RemoveAt(nCount - nIndex - 1);
				m_szAlertMessages.RemoveAt(nCount - nIndex - 1);
				return TRUE;
			}
			for (nIndex = 0, nCount = ((nType >= TCONBOARDBUFFERQUEUE_ALERTTYPE_INFORMATION && nType <= TCONBOARDBUFFERQUEUE_ALERTTYPE_ERROR) || nType == TCONBOARDBUFFERQUEUE_ALERTTYPE_NONE) ? (INT)m_nAlertTypes.GetSize() : -1; nIndex < nCount; nIndex++)
			{
				if ((nType == TCONBOARDBUFFERQUEUE_ALERTTYPE_NONE || m_nAlertTypes.GetAt(nIndex) == nType) && m_nAlertMessages.GetAt(nIndex) == nMessage)
				{
					m_nAlertTypes.RemoveAt(nIndex);
					m_nAlertMessages.RemoveAt(nIndex);
					m_szAlertMessages.RemoveAt(nIndex);
					nCount--;
					nIndex--;
				}
			}
			return((nCount >= 0) ? TRUE : FALSE);
		}
		if (nMessage == (UINT)-1)
		{
			if (nType == TCONBOARDBUFFERQUEUE_ALERTTYPE_ANY  &&  nCount > 0)
			{
				m_nAlertTypes.RemoveAt(nCount - 1);
				m_nAlertMessages.RemoveAt(nCount - 1);
				m_szAlertMessages.RemoveAt(nCount - 1);
				return TRUE;
			}
			for (nIndex = 0, nCount = (nType >= TCONBOARDBUFFERQUEUE_ALERTTYPE_INFORMATION && nType <= TCONBOARDBUFFERQUEUE_ALERTTYPE_ERROR) ? (INT)m_nAlertTypes.GetSize() : -1; nIndex < nCount; nIndex++)
			{
				if (m_nAlertTypes.GetAt(nIndex) == nType)
				{
					m_nAlertTypes.RemoveAt(nIndex);
					m_nAlertMessages.RemoveAt(nIndex);
					m_szAlertMessages.RemoveAt(nIndex);
					nCount--;
					nIndex--;
				}
			}
			if (nType == TCONBOARDBUFFERQUEUE_ALERTTYPE_NONE)
			{
				m_nAlertTypes.RemoveAll();
				m_nAlertMessages.RemoveAll();
				m_szAlertMessages.RemoveAll();
				return TRUE;
			}
			return((nCount >= 0) ? TRUE : FALSE);
		}
	}
	return FALSE;
}

UINT CTCOnBoardBufferQueue::IsAlerted(UINT nMessage, CString &szMessage) CONST
{
	INT  nIndex;
	INT  nCount;
	UINT  nType;

	for (nIndex = 0, nCount = (INT)m_nAlertMessages.GetSize(), nType = TCONBOARDBUFFERQUEUE_ALERTTYPE_NONE, szMessage.Empty(); nIndex < nCount; nIndex++)
	{
		if (nMessage != (UINT)-1 && nMessage == m_nAlertMessages.GetAt(nCount - nIndex - 1))
		{
			szMessage = m_szAlertMessages.GetAt(nCount - nIndex - 1);
			break;
		}
		if (nMessage == (UINT)-1 && nType < m_nAlertTypes.GetAt(nCount - nIndex - 1))
		{
			szMessage = m_szAlertMessages.GetAt(nCount - nIndex - 1);
			nType = m_nAlertTypes.GetAt(nCount - nIndex - 1);
		}
	}
	return((nIndex < nCount) ? m_nAlertTypes.GetAt(nCount - nIndex - 1) : nType);
}
UINT CTCOnBoardBufferQueue::IsAlerted(UINT nMessage) CONST
{
	CString  szMessage;

	return IsAlerted(nMessage, szMessage);
}

INT CTCOnBoardBufferQueue::GetAlertCount(UINT nType) CONST
{
	INT  nIndex;
	INT  nCount[2];

	for (nIndex = 0, nCount[0] = (INT)m_nAlertTypes.GetSize(), nCount[1] = 0; nIndex < nCount[0]; nIndex++)
	{
		if (m_nAlertTypes.GetAt(nIndex) == nType || nType == TCONBOARDBUFFERQUEUE_ALERTTYPE_ANY)
		{
			nCount[1]++;
			continue;
		}
	}
	return nCount[1];
}

BOOL CTCOnBoardBufferQueue::Copy(CONST CTCOnBoardBufferQueue *pQueue)
{
	m_szName = pQueue->m_szName;
	m_szType = pQueue->m_szType;
	m_nFlags = pQueue->m_nFlags;
	m_nAPID = pQueue->m_nAPID;
	m_nSubScheduleID = pQueue->m_nSubScheduleID;
	m_nLimit = pQueue->m_nLimit;
	m_nCount = pQueue->m_nCount;
	m_szUnit = pQueue->m_szUnit;
	m_tTime = pQueue->m_tTime;
	m_tTimeout = pQueue->m_tTimeout;
	m_nStatus = pQueue->m_nStatus;
	m_nAlertTypes.Copy(pQueue->m_nAlertTypes);
	m_nAlertMessages.Copy(pQueue->m_nAlertMessages);
	m_szAlertMessages.Copy(pQueue->m_szAlertMessages);
	return CTCItems::Copy(pQueue);
}

BOOL CTCOnBoardBufferQueue::Compare(CONST CTCOnBoardBufferQueue *pQueue) CONST
{
	INT  nMessage;
	INT  nMessages;

	for (nMessage = 0, nMessages = (pQueue->m_szName == m_szName && pQueue->m_szType == m_szType && pQueue->m_nFlags == m_nFlags && pQueue->m_nAPID == m_nAPID && pQueue->m_nSubScheduleID == m_nSubScheduleID && pQueue->m_nLimit == m_nLimit && pQueue->m_nCount == m_nCount && pQueue->m_szUnit == m_szUnit && pQueue->m_tTime == m_tTime && pQueue->m_tTimeout == m_tTimeout && pQueue->m_nStatus == m_nStatus && pQueue->m_nAlertTypes.GetSize() == m_nAlertTypes.GetSize() && pQueue->m_nAlertMessages.GetSize() == m_nAlertMessages.GetSize() && !memcmp(pQueue->m_nAlertTypes.GetData(), m_nAlertTypes.GetData(), m_nAlertTypes.GetSize()*sizeof(UINT)) && !memcmp(pQueue->m_nAlertMessages.GetData(), m_nAlertMessages.GetData(), m_nAlertMessages.GetSize()*sizeof(UINT)) && pQueue->m_szAlertMessages.GetSize() == m_szAlertMessages.GetSize()) ? (INT)m_szAlertMessages.GetSize() : -1; nMessage < nMessages; nMessage++)
	{
		if (pQueue->m_szAlertMessages.GetAt(nMessage) != m_szAlertMessages.GetAt(nMessage)) break;
		continue;
	}
	return((nMessage == nMessages) ? CTCItems::Compare(pQueue) : FALSE);
}

BOOL CTCOnBoardBufferQueue::Map(CByteArray &nInfo) CONST
{
	INT  nAlert;
	INT  nAlerts;
	INT  cbData;
	DATA  sData;
	CByteArray  nItemsData;
	CByteArray  nAlertsData;

	sData.cbName = (m_szName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbType = (m_szType.GetLength() + 1)*sizeof(TCHAR);
	sData.cbUnit = (m_szUnit.GetLength() + 1)*sizeof(TCHAR);
	sData.cbAlerts[0] = (INT)(m_nAlertTypes.GetSize()*sizeof(UINT));
	sData.cbAlerts[1] = (INT)(m_nAlertMessages.GetSize()*sizeof(UINT));
	sData.cbItems = (CTCItems::Map(nItemsData, TRUE)) ? (INT)nItemsData.GetSize() : -1;
	for (nAlert = 0, nAlerts = (INT)m_szAlertMessages.GetSize(), sData.cbAlerts[2] = 0; nAlert < nAlerts; nAlert++, sData.cbAlerts[2] += cbData)
	{
		nAlertsData.SetSize(sData.cbAlerts[2] + (cbData = (m_szAlertMessages.GetAt(nAlert).GetLength() + 1)*sizeof(TCHAR)));
		CopyMemory(nAlertsData.GetData() + sData.cbAlerts[2], (LPCTSTR)m_szAlertMessages.GetAt(nAlert), cbData);
	}
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbName + sData.cbType + sData.cbUnit + max(sData.cbItems, 0) + sData.cbAlerts[0] + sData.cbAlerts[1] + sData.cbAlerts[2])), sData.nFlags = m_nFlags, sData.nAPID = m_nAPID, sData.nSubScheduleID = m_nSubScheduleID, sData.nLimit = m_nLimit, sData.nCount = m_nCount, sData.tTime = m_tTime.GetTime(), sData.tTimeout = m_tTimeout.GetTotalSeconds(), sData.nStatus = m_nStatus; nInfo.GetSize() == sData.cbSize && sData.cbItems >= 0; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szName, sData.cbName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbName), (LPCTSTR)m_szType, sData.cbType);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbType), (LPCTSTR)m_szUnit, sData.cbUnit);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbUnit), nItemsData.GetData(), sData.cbItems);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbItems), m_nAlertTypes.GetData(), sData.cbAlerts[0]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbAlerts[0]), m_nAlertMessages.GetData(), sData.cbAlerts[1]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbAlerts[1]), nAlertsData.GetData(), sData.cbAlerts[2]);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCOnBoardBufferQueue::Unmap(CONST CByteArray &nInfo)
{
	INT  cbAlert;
	INT  cbAlerts;
	INT  cbData;
	DATA  sData;
	CByteArray  nItemsData;
	CByteArray  nAlertsData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbName + sData.cbType + sData.cbUnit + sData.cbItems + sData.cbAlerts[0] + sData.cbAlerts[1] + sData.cbAlerts[2] && sData.cbName > 0 && sData.cbType > 0 && sData.cbUnit > 0 && sData.cbItems >= 0 && sData.cbAlerts[0] >= 0 && sData.cbAlerts[1] >= 0 && sData.cbAlerts[2] >= 0; )
	{
		for (nItemsData.SetSize(sData.cbItems), m_nAlertTypes.SetSize(sData.cbAlerts[0] / sizeof(UINT)), m_nAlertMessages.SetSize(sData.cbAlerts[1] / sizeof(UINT)), nAlertsData.SetSize(sData.cbAlerts[2]), CopyMemory(m_szName.GetBufferSetLength(STRINGCHARS(sData.cbName)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbName)), CopyMemory(m_szType.GetBufferSetLength(STRINGCHARS(sData.cbType)), nInfo.GetData() + (cbData = cbData + sData.cbName), STRINGBYTES(sData.cbType)), CopyMemory(m_szUnit.GetBufferSetLength(STRINGCHARS(sData.cbUnit)), nInfo.GetData() + (cbData = cbData + sData.cbType), STRINGBYTES(sData.cbUnit)), CopyMemory(nItemsData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbUnit), sData.cbItems), CopyMemory(m_nAlertTypes.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbItems), sData.cbAlerts[0]), CopyMemory(m_nAlertMessages.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbAlerts[0]), sData.cbAlerts[1]), CopyMemory(nAlertsData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbAlerts[1]), sData.cbAlerts[2]), m_nFlags = sData.nFlags, m_nAPID = sData.nAPID, m_nSubScheduleID = sData.nSubScheduleID, m_nLimit = sData.nLimit, m_nCount = sData.nCount, m_tTime = sData.tTime, m_tTimeout = sData.tTimeout, m_nStatus = sData.nStatus, RemoveAll(), m_szName.ReleaseBuffer(), m_szType.ReleaseBuffer(), m_szUnit.ReleaseBuffer(), m_szAlertMessages.RemoveAll(), cbAlerts = 0; cbAlerts < nAlertsData.GetSize(); cbAlerts += cbAlert)
		{
			m_szAlertMessages.Add((LPCTSTR)(nAlertsData.GetData() + cbAlerts));
			cbAlert = (m_szAlertMessages.GetAt(m_szAlertMessages.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR);
		}
		return CTCItems::Unmap(nItemsData, TRUE);
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CTCOnBoardBufferQueues

CTCOnBoardBufferQueues::CTCOnBoardBufferQueues() : CPtrArray()
{
	return;
}

CTCOnBoardBufferQueues::~CTCOnBoardBufferQueues()
{
	RemoveAll();
}

INT CTCOnBoardBufferQueues::Add(CTCOnBoardBufferQueue *pQueue)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pQueue->GetType(), pQueue->GetName(), pQueue->GetSubScheduleID(), TRUE)) >= 0) InsertAt(nIndex, pQueue, 1);
	return nIndex;
}

INT CTCOnBoardBufferQueues::Find(LPCTSTR pszType, LPCTSTR pszName, UINT nSubScheduleID) CONST
{
	return FindIndex(pszType, pszName, nSubScheduleID);
}

CTCOnBoardBufferQueue *CTCOnBoardBufferQueues::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCOnBoardBufferQueue *)CPtrArray::GetAt(nIndex) : (CTCOnBoardBufferQueue *)NULL);
}

CTCOnBoardBufferQueue *CTCOnBoardBufferQueues::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCOnBoardBufferQueue *)CPtrArray::GetAt(nIndex) : (CTCOnBoardBufferQueue *)NULL);
}

VOID CTCOnBoardBufferQueues::RemoveAll()
{
	INT  nQueue;
	INT  nQueues;

	for (nQueue = 0, nQueues = (INT)GetSize(); nQueue < nQueues; nQueue++)
	{
		delete GetAt(nQueue);
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CTCOnBoardBufferQueues::Copy(CONST CTCOnBoardBufferQueues *pQueues)
{
	INT  nQueue;
	INT  nQueues;
	CTCOnBoardBufferQueue  *pQueue;

	for (nQueue = 0, nQueues = (INT)pQueues->GetSize(), RemoveAll(); nQueue < nQueues; nQueue++)
	{
		if ((pQueue = new CTCOnBoardBufferQueue) != (CTCOnBoardBufferQueue *)NULL)
		{
			pQueue->Copy(pQueues->GetAt(nQueue));
			InsertAt(nQueue, pQueue, 1);
			continue;
		}
		break;
	}
	return((nQueue == nQueues) ? TRUE : FALSE);
}

BOOL CTCOnBoardBufferQueues::Compare(CONST CTCOnBoardBufferQueues *pQueues) CONST
{
	INT  nQueue;
	INT  nQueues;

	for (nQueue = 0, nQueues = (pQueues->GetSize() == GetSize()) ? (INT)GetSize() : -1; nQueue < nQueues; nQueue++)
	{
		if (!pQueues->GetAt(nQueue)->Compare(GetAt(nQueue))) break;
		continue;
	}
	return((nQueue == nQueues) ? TRUE : FALSE);
}

BOOL CTCOnBoardBufferQueues::Map(CByteArray &nInfo) CONST
{
	INT  nQueue;
	INT  nQueues;
	CByteArray  nQueueData;
	CTCOnBoardBufferQueue  *pQueue;

	for (nQueue = 0, nQueues = (INT)GetSize(), nInfo.RemoveAll(); nQueue < nQueues; nQueue++)
	{
		if ((pQueue = GetAt(nQueue)) && pQueue->Map(nQueueData) && nInfo.Append(nQueueData) >= 0) continue;
		break;
	}
	return((nQueue == nQueues) ? TRUE : FALSE);
}

BOOL CTCOnBoardBufferQueues::Unmap(CONST CByteArray &nInfo)
{
	INT  cbQueue;
	INT  cbQueues;
	CByteArray  nQueueData;
	CTCOnBoardBufferQueue  *pQueue;

	for (cbQueues = 0, RemoveAll(); cbQueues < nInfo.GetSize(); cbQueues += cbQueue)
	{
		for (CopyMemory(&cbQueue, nInfo.GetData() + cbQueues, sizeof(cbQueue)), nQueueData.SetSize(max(min(cbQueue, nInfo.GetSize() - cbQueues), 0)); nQueueData.GetSize() >= 0; )
		{
			CopyMemory(nQueueData.GetData(), nInfo.GetData() + cbQueues, nQueueData.GetSize());
			break;
		}
		if ((pQueue = new CTCOnBoardBufferQueue))
		{
			if (pQueue->Unmap(nQueueData) && Add(pQueue) >= 0) continue;
			delete pQueue;
		}
		break;
	}
	return((cbQueues == nInfo.GetSize()) ? TRUE : FALSE);
}

INT CTCOnBoardBufferQueues::FindIndex(LPCTSTR pszType, LPCTSTR pszName, UINT nSubScheduleID, BOOL bInsert) CONST
{
	INT  nIndex;
	INT  nCount;
	CString  szQueue;
	CStringTools  cStringTools;
	CTCOnBoardBufferQueue  *pQueue;

	for (nIndex = 0, nCount = (INT)GetSize(), szQueue = pszType + CString(TAB) + pszName + CString(TAB) + cStringTools.ConvertIntToString(nSubScheduleID); nIndex < nCount; nIndex++)
	{
		if ((pQueue = GetAt(nIndex)) && szQueue == pQueue->GetType() + TAB + pQueue->GetName() + TAB + cStringTools.ConvertIntToString(pQueue->GetSubScheduleID())) break;
		continue;
	}
	return((((!bInsert  &&  nIndex < nCount) || (bInsert  &&  nIndex == nCount)) && lstrlen(pszName) > 0) ? nIndex : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CTCUplinkDevice

UINT CTCUplinkDevice::m_nDeviceStatus;
BOOL CTCUplinkDevice::m_bDeviceStatus;

CTCUplinkDevice::CTCUplinkDevice() : CIODevice()
{
	m_szIODeviceStatus = STRING(IDS_TELECOMMANDUPLINKDEVICE_STATUS_NOTREADY);
	m_nIODeviceStatus = IODEVICE_STATUS_ERROR | IODEVICE_STATUS_NOTCONNECTED | IODEVICE_STATUS_ONLINE;
	m_nCommandHandlerState = TCSERVICE_COMMANDHANDLERSTATE_NONE;
	m_nScheduleOptions = TELECOMMANDUPLINKDEVICE_SCHEDULE_ALWAYS;
	m_nBackupOptions = TELECOMMANDUPLINKDEVICE_BACKUP_USEANYDEVICE;
	m_nDeviceStatus = 0;
	m_bDeviceStatus = FALSE;
	m_tScheduleStartTime = 0;
	m_tScheduleStopTime = 0;
	m_tDailyStartTime = 0;
	m_tDailyStopTime = 0;
	m_tPeriodicStartTime = 0;
	m_tPeriodicInterval[0] = 0;
	m_tPeriodicInterval[1] = 0;
	m_nBackupRetry[0] = 0;
	m_nBackupRetry[1] = 0;
	m_tBackupTimeout = 0;
}
CTCUplinkDevice::CTCUplinkDevice(CTCUplinkDevice *pDevice) : CIODevice()
{
	Copy(pDevice);
}

BOOL CTCUplinkDevice::Initialize(UINT nFlags, CONST CTimeSpan &tDataDrop, CONST CTimeSpan &tDataDelay, IODEVICESTATUSPROCEDURE pStatusProcedure, IODEVICEMESSAGEPROCEDURE pMessageProcedure)
{
	return CIODevice::Initialize(nFlags, tDataDrop, tDataDelay, UpdateDeviceStatus, TrackDeviceDataStatus, ShowDeviceMessage);
}

VOID CTCUplinkDevice::SetCommandHandler(LPCTSTR pszComputer)
{
	m_szCommandHandler = pszComputer;
}

CString CTCUplinkDevice::GetCommandHandler() CONST
{
	return m_szCommandHandler;
}

VOID CTCUplinkDevice::SetCommandHandlerState(UINT nState)
{
	m_nCommandHandlerState = nState;
}

UINT CTCUplinkDevice::GetCommandHandlerState() CONST
{
	return m_nCommandHandlerState;
}

VOID CTCUplinkDevice::SetScheduleOptions(UINT nOptions)
{
	m_nScheduleOptions = nOptions;
}

UINT CTCUplinkDevice::GetScheduleOptions() CONST
{
	return m_nScheduleOptions;
}

VOID CTCUplinkDevice::SetScheduleDaily(CONST CTimeSpan &tStartTime, CONST CTimeSpan &tStopTime)
{
	m_tDailyStartTime = (tStartTime < tStopTime) ? tStartTime : 0;
	m_tDailyStopTime = (tStartTime < tStopTime) ? tStopTime : 0;
}

BOOL CTCUplinkDevice::GetScheduleDaily(CTimeSpan &tStartTime, CTimeSpan &tStopTime) CONST
{
	if (m_nScheduleOptions & TELECOMMANDUPLINKDEVICE_SCHEDULE_DAILY)
	{
		tStartTime = m_tDailyStartTime;
		tStopTime = m_tDailyStopTime;
		return TRUE;
	}
	return FALSE;
}

VOID CTCUplinkDevice::SetScheduleInterval(CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime)
{
	m_tScheduleStartTime = (tStartTime < tStopTime) ? tStartTime : 0;
	m_tScheduleStopTime = (tStartTime < tStopTime) ? tStopTime : 0;
}

BOOL CTCUplinkDevice::GetScheduleInterval(CTimeKey &tStartTime, CTimeKey &tStopTime) CONST
{
	if (m_nScheduleOptions & TELECOMMANDUPLINKDEVICE_SCHEDULE_INTERVAL)
	{
		tStartTime = m_tScheduleStartTime;
		tStopTime = m_tScheduleStopTime;
		return TRUE;
	}
	return FALSE;
}

VOID CTCUplinkDevice::SetSchedulePeriodic(CONST CTimeKey &tStartTime, CONST CTimeSpan &tPeriod, CONST CTimeSpan &tInterval)
{
	m_tPeriodicStartTime = tStartTime;
	m_tPeriodicInterval[0] = tPeriod;
	m_tPeriodicInterval[1] = tInterval;
}

BOOL CTCUplinkDevice::GetSchedulePeriodic(CTimeKey &tStartTime, CTimeSpan &tPeriod, CTimeSpan &tInterval) CONST
{
	if (m_nScheduleOptions & TELECOMMANDUPLINKDEVICE_SCHEDULE_PERIODIC)
	{
		tStartTime = m_tPeriodicStartTime;
		tPeriod = m_tPeriodicInterval[0];
		tInterval = m_tPeriodicInterval[1];
		return TRUE;
	}
	return FALSE;
}

VOID CTCUplinkDevice::SetBackupDevice(LPCTSTR pszDevice)
{
	m_szBackupDevice = pszDevice;
}

BOOL CTCUplinkDevice::GetBackupDevice(CString &szDevice) CONST
{
	if (m_nBackupOptions & TELECOMMANDUPLINKDEVICE_BACKUP_USEDEVICE)
	{
		szDevice = m_szBackupDevice;
		return TRUE;
	}
	return FALSE;
}

VOID CTCUplinkDevice::SetBackupOptions(UINT nOptions)
{
	m_nBackupOptions = nOptions;
}

UINT CTCUplinkDevice::GetBackupOptions() CONST
{
	return m_nBackupOptions;
}

VOID CTCUplinkDevice::SetBackupRetries(UINT nRetries)
{
	m_nBackupRetry[0] = nRetries;
	m_nBackupRetry[1] = 0;
}

BOOL CTCUplinkDevice::GetBackupRetries(UINT &nRetries) CONST
{
	if (m_nBackupOptions & TELECOMMANDUPLINKDEVICE_BACKUP_RETRIES)
	{
		nRetries = m_nBackupRetry[0];
		return TRUE;
	}
	return FALSE;
}

VOID CTCUplinkDevice::SetBackupRetryCount(UINT nCount)
{
	m_nBackupRetry[1] = nCount;
}

BOOL CTCUplinkDevice::GetBackupRetryCount(UINT &nCount) CONST
{
	if (m_nBackupOptions & TELECOMMANDUPLINKDEVICE_BACKUP_RETRIES)
	{
		nCount = m_nBackupRetry[1];
		return TRUE;
	}
	return FALSE;
}

VOID CTCUplinkDevice::SetBackupTimeout(CONST CTimeSpan &tTimeout)
{
	m_tBackupTimeout = tTimeout;
}

BOOL CTCUplinkDevice::GetBackupTimeout(CTimeSpan &tTimeout) CONST
{
	return(((tTimeout = m_tBackupTimeout) >= 0) ? TRUE : FALSE);
}

CString CTCUplinkDevice::GetToolTipText() CONST
{
	CString  szDetails;
	CTCUplinkDevice  cDevice;

	for (cDevice.Copy(this); cDevice.Open(); )
	{
		szDetails = cDevice.GetDetails();
		cDevice.Close();
		return szDetails;
	}
	szDetails.Format(STRING(IDS_TELECOMMANDUPLINKDEVICE_TOOLTIPTEXT_FORMAT), (LPCTSTR)GetCommandHandler());
	return((!GetCommandHandler().IsEmpty()) ? szDetails : EMPTYSTRING);
}

BOOL CTCUplinkDevice::IsStandBy(CTimeSpan &tPeriod) CONST
{
	UINT  nOptions;
	CTimeKey  tTime;
	CTimeKey  tRange[2];
	CTimeKey  tStartTime;
	CTimeSpan  tDaily[2];
	CTimeSpan  tInterval[2];

	if (((nOptions = GetScheduleOptions()) & TELECOMMANDUPLINKDEVICE_SCHEDULE_DISABLED) != TELECOMMANDUPLINKDEVICE_SCHEDULE_DISABLED)
	{
		if (nOptions & TELEMETRYPROVIDERDEVICE_SCHEDULE_ALWAYS)
		{
			tPeriod = SECONDSPERDAY;
			return TRUE;
		}
		if (nOptions & TELECOMMANDUPLINKDEVICE_SCHEDULE_DAILY)
		{
			if (GetScheduleDaily(tDaily[0], tDaily[1]) && tTime.GetTime() % SECONDSPERDAY >= tDaily[0].GetTotalSeconds() && tTime.GetTime() % SECONDSPERDAY <= tDaily[1].GetTotalSeconds())
			{
				tPeriod = tDaily[1].GetTotalSeconds() - tTime.GetTime() % SECONDSPERDAY;
				return TRUE;
			}
		}
		if (nOptions & TELECOMMANDUPLINKDEVICE_SCHEDULE_INTERVAL)
		{
			if (GetScheduleInterval(tRange[0], tRange[1]) && tTime >= tRange[0] && tTime <= tRange[1])
			{
				tPeriod = min(tRange[1].GetTime() - tTime.GetTime(), SECONDSPERDAY);
				return TRUE;
			}
		}
		if (nOptions & TELECOMMANDUPLINKDEVICE_SCHEDULE_PERIODIC)
		{
			if (GetSchedulePeriodic(tStartTime, tInterval[0], tInterval[1]) && tTime >= tStartTime && (tTime.GetTime() - tStartTime.GetTime()) % (tInterval[0].GetTotalSeconds() + tInterval[1].GetTotalSeconds()) < tInterval[0].GetTotalSeconds())
			{
				tPeriod = min(tInterval[0].GetTotalSeconds() - (tTime.GetTime() - tStartTime.GetTime()) % (tInterval[0].GetTotalSeconds() + tInterval[1].GetTotalSeconds()), SECONDSPERDAY);
				return TRUE;
			}
		}
	}
	tPeriod = 0;
	return FALSE;
}
BOOL CTCUplinkDevice::IsStandBy() CONST
{
	CTimeSpan  tPeriod;

	return IsStandBy(tPeriod);
}

BOOL CTCUplinkDevice::Copy(CONST CTCUplinkDevice *pDevice)
{
	m_szCommandHandler = pDevice->m_szCommandHandler;
	m_nCommandHandlerState = pDevice->m_nCommandHandlerState;
	m_nScheduleOptions = pDevice->m_nScheduleOptions;
	m_tScheduleStartTime = pDevice->m_tScheduleStartTime;
	m_tScheduleStopTime = pDevice->m_tScheduleStopTime;
	m_tDailyStartTime = pDevice->m_tDailyStartTime;
	m_tDailyStopTime = pDevice->m_tDailyStopTime;
	m_tPeriodicStartTime = pDevice->m_tPeriodicStartTime;
	m_tPeriodicInterval[0] = pDevice->m_tPeriodicInterval[0];
	m_tPeriodicInterval[1] = pDevice->m_tPeriodicInterval[1];
	m_szBackupDevice = pDevice->m_szBackupDevice;
	m_nBackupOptions = pDevice->m_nBackupOptions;
	m_nBackupRetry[0] = pDevice->m_nBackupRetry[0];
	m_nBackupRetry[1] = pDevice->m_nBackupRetry[1];
	m_tBackupTimeout = pDevice->m_tBackupTimeout;
	return CIODevice::Copy(pDevice);
}

BOOL CTCUplinkDevice::Compare(CONST CTCUplinkDevice *pDevice) CONST
{
	return((!pDevice->m_szCommandHandler.CompareNoCase(m_szCommandHandler) && pDevice->m_nCommandHandlerState == m_nCommandHandlerState  &&  pDevice->m_nScheduleOptions == m_nScheduleOptions && (!(m_nScheduleOptions & TELECOMMANDUPLINKDEVICE_SCHEDULE_DAILY) || (pDevice->m_tDailyStartTime == m_tDailyStartTime  &&  pDevice->m_tDailyStopTime == m_tDailyStopTime)) && (!(m_nScheduleOptions & TELECOMMANDUPLINKDEVICE_SCHEDULE_INTERVAL) || (pDevice->m_tScheduleStartTime == m_tScheduleStartTime  &&  pDevice->m_tScheduleStopTime == m_tScheduleStopTime)) && (!(m_nScheduleOptions & TELECOMMANDUPLINKDEVICE_SCHEDULE_PERIODIC) || (pDevice->m_tPeriodicStartTime == m_tPeriodicStartTime  &&  pDevice->m_tPeriodicInterval[0] == m_tPeriodicInterval[0] && pDevice->m_tPeriodicInterval[1] == m_tPeriodicInterval[1])) && pDevice->m_nBackupOptions == m_nBackupOptions && (!(m_nBackupOptions & TELECOMMANDUPLINKDEVICE_BACKUP_USEDEVICE) || pDevice->m_szBackupDevice == m_szBackupDevice) && (!(m_nBackupOptions & TELECOMMANDUPLINKDEVICE_BACKUP_RETRIES) || pDevice->m_nBackupRetry[0] == m_nBackupRetry[0]) && pDevice->m_tBackupTimeout == m_tBackupTimeout) ? CIODevice::Compare(pDevice) : FALSE);
}

BOOL CTCUplinkDevice::Map(CByteArray &nInfo) CONST
{
	INT  cbData;
	DATA  sData;
	CByteArray  nDeviceData;

	sData.cbBackupDevice = (m_szBackupDevice.GetLength() + 1)*sizeof(TCHAR);
	sData.cbDevice = (CIODevice::Map(nDeviceData)) ? (INT)nDeviceData.GetSize() : -1;
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + max(sData.cbDevice, 0) + sData.cbBackupDevice)), sData.nScheduleOptions = m_nScheduleOptions, sData.tScheduleStartTime = m_tScheduleStartTime.GetTime(), sData.tScheduleStopTime = m_tScheduleStopTime.GetTime(), sData.tDailyStartTime = m_tDailyStartTime.GetTotalSeconds(), sData.tDailyStopTime = m_tDailyStopTime.GetTotalSeconds(), sData.tPeriodicStartTime = m_tPeriodicStartTime.GetTime(), sData.tPeriodicInterval[0] = m_tPeriodicInterval[0].GetTotalSeconds(), sData.tPeriodicInterval[1] = m_tPeriodicInterval[1].GetTotalSeconds(), sData.nBackupOptions = m_nBackupOptions, sData.nBackupRetry[0] = m_nBackupRetry[0], sData.nBackupRetry[1] = m_nBackupRetry[1], sData.tBackupTimeout = m_tBackupTimeout.GetTotalSeconds(); nInfo.GetSize() == sData.cbSize && sData.cbDevice >= 0; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szBackupDevice, sData.cbBackupDevice);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbBackupDevice), nDeviceData.GetData(), sData.cbDevice);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCUplinkDevice::Unmap(CONST CByteArray &nInfo)
{
	INT  cbData;
	DATA  sData;
	CByteArray  nDeviceData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbDevice + sData.cbBackupDevice && sData.cbDevice > 0 && sData.cbBackupDevice > 0; )
	{
		for (nDeviceData.SetSize(sData.cbDevice), CopyMemory(m_szBackupDevice.GetBufferSetLength(STRINGCHARS(sData.cbBackupDevice)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbBackupDevice)), CopyMemory(nDeviceData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbBackupDevice), sData.cbDevice), m_nScheduleOptions = sData.nScheduleOptions, m_tScheduleStartTime = sData.tScheduleStartTime, m_tScheduleStopTime = sData.tScheduleStopTime, m_tDailyStartTime = sData.tDailyStartTime, m_tDailyStopTime = sData.tDailyStopTime, m_tPeriodicStartTime = sData.tPeriodicStartTime, m_tPeriodicInterval[0] = sData.tPeriodicInterval[0], m_tPeriodicInterval[1] = sData.tPeriodicInterval[1], m_nBackupOptions = sData.nBackupOptions, m_nBackupRetry[0] = sData.nBackupRetry[0], m_nBackupRetry[1] = sData.nBackupRetry[1], m_tBackupTimeout = sData.tBackupTimeout, m_szBackupDevice.ReleaseBuffer(); CIODevice::Unmap(nDeviceData); ) return TRUE;
		break;
	}
	return FALSE;
}

VOID CALLBACK CTCUplinkDevice::TrackDeviceDataStatus(INT nDataID, UINT nStatus, BOOL bSuccess)
{
	GetTCService()->Update(nDataID, nStatus, bSuccess);
}

VOID CALLBACK CTCUplinkDevice::UpdateDeviceStatus(LPCTSTR pszStatus, UINT nStatus)
{
	HWND  hWnd;
	BOOL  bDeviceStatus;
	CTCUplinkDevice  cDevice;

	for (bDeviceStatus = FALSE; GetTCService()->GetActiveTCUplinkDevice(&cDevice); )
	{
		if (cDevice.GetStatus() != pszStatus || cDevice.GetStatusIndication() != nStatus)
		{
			cDevice.SetStatus(pszStatus);
			cDevice.SetStatusIndication(nStatus);
			GetTCService()->SetActiveTCUplinkDevice(&cDevice);
			bDeviceStatus = TRUE;
		}
		break;
	}
	if ((hWnd = FindWindow(STRING(IDS_SCREENSAVER_WINDOWCLASS_NAME), (LPCTSTR)NULL)))
	{
		if (!m_bDeviceStatus || bDeviceStatus) SendNotifyMessage(hWnd, WM_USER, MAKEWPARAM(0, MAKEWORD(TRUE, (nStatus & IODEVICE_STATUS_GOOD) ? TRUE : FALSE)), (LPARAM)NULL);
		m_bDeviceStatus = TRUE;
		return;
	}
	m_bDeviceStatus = FALSE;
}

VOID CALLBACK CTCUplinkDevice::ShowDeviceMessage(LPCTSTR pszMessage, UINT nMessageType)
{
	ReportEvent(EVENT_CATEGORY_SYSTEM | nMessageType, pszMessage, FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTCUplinkDevices

CTCUplinkDevices::CTCUplinkDevices() : CIODevices()
{
	return;
}

CTCUplinkDevices::~CTCUplinkDevices()
{
	RemoveAll();
}

INT CTCUplinkDevices::EnumDevices(UINT nFlags)
{
	INT  nDevice;
	INT  nDevices;
	CFileFindEx  cFileFind;
	CTCUplinkDevice  *pDevice;
	TCHAR  szFileName[MAX_PATH];

	if (GetModuleFileName((HMODULE)NULL, szFileName, sizeof(szFileName) / sizeof(TCHAR)) > 0)
	{
		for (m_szDevicePathNames[0].RemoveAll(), m_szDevicePathNames[1].RemoveAll(); cFileFind.FindFile(szFileName) && !cFileFind.FindNextFile(); )
		{
			EnumDevices(nFlags, cFileFind.GetRoot());
			cFileFind.Close();
			break;
		}
		for (nDevice = 0, nDevices = (INT)GetSize(); nDevice < nDevices; nDevice++)
		{
			if ((pDevice = GetAt(nDevice)))
			{
				if (pDevice->Open())
				{
					if (pDevice->GetCapabilities() & IODEVICE_SERVICE_TC)
					{
						pDevice->Close();
						continue;
					}
					pDevice->Close();
				}
			}
			RemoveAt(nDevice);
			delete pDevice;
			nDevices--;
			nDevice--;
		}
	}
	return((INT)GetSize());
}

INT CTCUplinkDevices::EnumStandByDevices(CTCUplinkDevices &pDevices) CONST
{
	INT  nDevice;
	INT  nDevices;
	CTCUplinkDevice  *pDevice;

	for (nDevice = 0, nDevices = (pDevices.Copy(this)) ? (INT)pDevices.GetSize() : 0; nDevice < nDevices; nDevice++)
	{
		if ((pDevice = pDevices.GetAt(nDevice)) && pDevice->IsStandBy()) continue;
		pDevices.RemoveAt(nDevice);
		delete pDevice;
		nDevices--;
		nDevice--;
	}
	return((INT)pDevices.GetSize());
}

INT CTCUplinkDevices::EnumBackupDevices(CONST CTCUplinkDevice *pDevice, CTCUplinkDevices &pDevices) CONST
{
	INT  nIndex;
	INT  nCount;
	CString  szDevice;

	if (pDevice->GetBackupOptions() & (TELECOMMANDUPLINKDEVICE_BACKUP_CONTINOUSLY | TELECOMMANDUPLINKDEVICE_BACKUP_RETRIES))
	{
		pDevices.RemoveAll();
		return 0;
	}
	if ((nIndex = (EnumStandByDevices(pDevices) > 0) ? pDevices.Find(pDevice->GetDeviceBrand(), pDevice->GetDeviceName()) : -1) >= 0)
	{
		delete pDevices.GetAt(nIndex);
		pDevices.RemoveAt(nIndex);
	}
	for (nIndex = 0, nCount = ((pDevice->GetBackupOptions() & TELECOMMANDUPLINKDEVICE_BACKUP_USEDEVICE) && pDevice->GetBackupDevice(szDevice) && pDevices.Find(pDevice->GetDeviceBrand(), szDevice)) ? (INT)pDevices.GetSize() : 0; nIndex < nCount; nIndex++)
	{
		if (GetAt(nIndex)->GetDeviceName() != pDevice->GetDeviceName())
		{
			delete pDevices.GetAt(nIndex);
			pDevices.RemoveAt(nIndex);
			nCount--;
			nIndex--;
		}
	}
	return((INT)pDevices.GetSize());
}

BOOL CTCUplinkDevices::HasAvailableDevices(BOOL bSupported) CONST
{
	INT  nDevice;
	INT  nDevices;
	CTCUplinkDevice  *pDevice;

	for (nDevice = 0, nDevices = (INT)GetSize(); nDevice < nDevices; nDevice++)
	{
		if ((pDevice = GetAt(nDevice)) && !pDevice->GetDeviceName().IsEmpty()) break;
		continue;
	}
	return(((!bSupported  &&  nDevice < nDevices) || (bSupported  &&  nDevices > 0)) ? TRUE : FALSE);
}

BOOL CTCUplinkDevices::SetActiveDevice(CONST CTCUplinkDevice *pDevice)
{
	INT  nIndex;

	if ((nIndex = Find(pDevice->GetDeviceBrand(), pDevice->GetDeviceName())) >= 0)
	{
		if (pDevice == GetAt(nIndex) || GetAt(nIndex)->Copy(pDevice))
		{
			m_szDevice[0] = ConstructFullName(pDevice);
			return TRUE;
		}
		return FALSE;
	}
	return((m_cDevice.Copy(pDevice)) ? !pDevice->GetCommandHandler().IsEmpty() : FALSE);
}

BOOL CTCUplinkDevices::GetActiveDevice(CTCUplinkDevice *pDevice) CONST
{
	INT  nDevice;
	INT  nDevices;

	for (nDevice = 0, nDevices = (INT)GetSize(); nDevice < nDevices; nDevice++)
	{
		if (m_szDevice[0] == ConstructFullName(GetAt(nDevice)))
		{
			pDevice->Copy(GetAt(nDevice));
			break;
		}
	}
	return((nDevice < nDevices || (pDevice->Copy(&m_cDevice) && !pDevice->GetCommandHandler().IsEmpty())) ? TRUE : FALSE);
}

BOOL CTCUplinkDevices::SetDefaultDevice(CONST CTCUplinkDevice *pDevice)
{
	INT  nIndex;
	CTCUplinkDevice  cDevice;

	if ((nIndex = Find(pDevice->GetDeviceBrand(), pDevice->GetDeviceName())) >= 0)
	{
		m_szDevice[1] = ConstructFullName(pDevice);
		return(cDevice.Copy(pDevice) && GetAt(nIndex)->Copy(&cDevice));
	}
	return FALSE;
}

BOOL CTCUplinkDevices::GetDefaultDevice(CTCUplinkDevice *pDevice) CONST
{
	INT  nDevice;
	INT  nDevices;

	for (nDevice = 0, nDevices = (INT)GetSize(); nDevice < nDevices; nDevice++)
	{
		if (m_szDevice[1] == ConstructFullName(GetAt(nDevice)))
		{
			pDevice->Copy(GetAt(nDevice));
			break;
		}
	}
	return((nDevice < nDevices) ? TRUE : FALSE);
}

CString CTCUplinkDevices::GetActiveDeviceBrand() CONST
{
	CTCUplinkDevice  cDevice;

	return((GetActiveDevice(&cDevice)) ? cDevice.GetDeviceBrand() : EMPTYSTRING);
}

CString CTCUplinkDevices::GetActiveDeviceName() CONST
{
	CTCUplinkDevice  cDevice;

	return((GetActiveDevice(&cDevice)) ? cDevice.GetDeviceName() : EMPTYSTRING);
}

CString CTCUplinkDevices::GetDefaultDeviceBrand() CONST
{
	CTCUplinkDevice  cDevice;

	return((GetDefaultDevice(&cDevice)) ? cDevice.GetDeviceBrand() : EMPTYSTRING);
}

CString CTCUplinkDevices::GetDefaultDeviceName() CONST
{
	CTCUplinkDevice  cDevice;

	return((GetDefaultDevice(&cDevice)) ? cDevice.GetDeviceName() : EMPTYSTRING);
}

CTCUplinkDevice *CTCUplinkDevices::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCUplinkDevice *)CPtrArray::GetAt(nIndex) : (CTCUplinkDevice *)NULL);
}

CTCUplinkDevice *CTCUplinkDevices::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCUplinkDevice *)CPtrArray::GetAt(nIndex) : (CTCUplinkDevice *)NULL);
}

VOID CTCUplinkDevices::RemoveAll()
{
	INT  nDevice;
	INT  nDevices;

	for (nDevice = 0, nDevices = (INT)GetSize(), m_szDevicePathNames[0].RemoveAll(), m_szDevicePathNames[1].RemoveAll(); nDevice < nDevices; nDevice++)
	{
		delete GetAt(nDevice);
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CTCUplinkDevices::Copy(CONST CTCUplinkDevices *pDevices, BOOL bAll)
{
	INT  nDevice;
	INT  nDevices;
	CTCUplinkDevice  *pDevice;

	if (bAll)
	{
		m_szDevice[0] = pDevices->m_szDevice[0];
		m_szDevice[1] = pDevices->m_szDevice[1];
		m_szDevicePathNames[0].Copy(pDevices->m_szDevicePathNames[0]);
		m_szDevicePathNames[1].Copy(pDevices->m_szDevicePathNames[1]);
	}
	for (nDevice = 0, nDevices = (INT)pDevices->GetSize(), RemoveAll(); nDevice < nDevices; nDevice++)
	{
		if ((pDevice = new CTCUplinkDevice))
		{
			pDevice->Copy(pDevices->GetAt(nDevice));
			InsertAt(nDevice, pDevice, 1);
			continue;
		}
		break;
	}
	return((nDevice == nDevices) ? TRUE : FALSE);
}

BOOL CTCUplinkDevices::Compare(CONST CTCUplinkDevices *pDevices, BOOL bAll) CONST
{
	INT  nDevice;
	INT  nDevices;
	INT  nModule[2];
	INT  nModules[2];
	CTCUplinkDevice  *pDevice;

	for (nDevice = 0, nDevices = ((!bAll || (pDevices->m_szDevice[0] == m_szDevice[0] && pDevices->m_szDevice[1] == m_szDevice[1])) && pDevices->GetSize() == GetSize()) ? (INT)GetSize() : -1; nDevice < nDevices; nDevice++)
	{
		if ((pDevice = pDevices->GetAt(nDevice)) && Find(pDevice->GetDeviceBrand(), pDevice->GetDeviceName()) >= 0 && pDevice->Compare(GetAt(Find(pDevice->GetDeviceBrand(), pDevice->GetDeviceName())))) continue;
		break;
	}
	for (nModule[0] = 0, nModules[0] = (bAll) ? ((pDevices->m_szDevicePathNames[0].GetSize() == m_szDevicePathNames[0].GetSize()) ? (INT)m_szDevicePathNames[0].GetSize() : -1) : 0; nModule[0] < nModules[0]; nModule[0]++)
	{
		if (pDevices->m_szDevicePathNames[0].GetAt(nModule[0]).CompareNoCase(m_szDevicePathNames[0].GetAt(nModule[0]))) break;
		continue;
	}
	for (nModule[1] = 0, nModules[1] = (bAll) ? ((pDevices->m_szDevicePathNames[1].GetSize() == m_szDevicePathNames[1].GetSize()) ? (INT)m_szDevicePathNames[1].GetSize() : -1) : 0; nModule[1] < nModules[1]; nModule[1]++)
	{
		if (pDevices->m_szDevicePathNames[1].GetAt(nModule[1]).CompareNoCase(m_szDevicePathNames[1].GetAt(nModule[1]))) break;
		continue;
	}
	return((nDevice == nDevices  &&  nModule[0] == nModules[0] && nModule[1] == nModules[1]) ? TRUE : FALSE);
}

BOOL CTCUplinkDevices::Map(CByteArray &nInfo) CONST
{
	DATA  sData;
	INT  cbData;
	INT  nDevice;
	INT  nDevices;
	CByteArray  nDevicesData[2];
	CTCUplinkDevice  *pDevice;

	sData.cbDevice[0] = (m_szDevice[0].GetLength() + 1)*sizeof(TCHAR);
	sData.cbDevice[1] = (m_szDevice[1].GetLength() + 1)*sizeof(TCHAR);
	for (nDevice = 0, nDevices = (INT)GetSize(); nDevice < nDevices; nDevice++)
	{
		if ((pDevice = GetAt(nDevice)) && pDevice->Map(nDevicesData[1]) && nDevicesData[0].Append(nDevicesData[1]) >= 0) continue;
		break;
	}
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbDevice[0] + sData.cbDevice[1] + (sData.cbDevicesData = (INT)nDevicesData[0].GetSize()*sizeof(BYTE)))); nInfo.GetSize() == sData.cbSize && nDevice == nDevices; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szDevice[0], sData.cbDevice[0]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbDevice[0]), (LPCTSTR)m_szDevice[1], sData.cbDevice[1]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbDevice[1]), nDevicesData[0].GetData(), sData.cbDevicesData);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCUplinkDevices::Unmap(CONST CByteArray &nInfo)
{
	DATA  sData;
	INT  cbData;
	INT  cbDevice;
	INT  cbDevices;
	CByteArray  nDevicesData[2];
	CTCUplinkDevice  *pDevice;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbDevice[0] + sData.cbDevice[1] + sData.cbDevicesData && sData.cbDevice[0] > 0 && sData.cbDevice[1] > 0 && sData.cbDevicesData >= 0; )
	{
		for (nDevicesData[0].SetSize(sData.cbDevicesData), CopyMemory(m_szDevice[0].GetBufferSetLength(STRINGCHARS(sData.cbDevice[0])), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbDevice[0])), CopyMemory(m_szDevice[1].GetBufferSetLength(STRINGCHARS(sData.cbDevice[1])), nInfo.GetData() + (cbData = cbData + sData.cbDevice[0]), STRINGBYTES(sData.cbDevice[1])), CopyMemory(nDevicesData[0].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbDevice[1]), sData.cbDevicesData), m_szDevice[0].ReleaseBuffer(), m_szDevice[1].ReleaseBuffer(), RemoveAll(), cbDevices = 0; cbDevices < (INT)nDevicesData[0].GetSize(); cbDevices += cbDevice)
		{
			for (CopyMemory(&cbDevice, nDevicesData[0].GetData() + cbDevices, sizeof(cbDevice)), nDevicesData[1].SetSize(max(min(cbDevice, nDevicesData[0].GetSize() - cbDevices), 0)); nDevicesData[1].GetSize() >= 0; )
			{
				CopyMemory(nDevicesData[1].GetData(), nDevicesData[0].GetData() + cbDevices, nDevicesData[1].GetSize());
				break;
			}
			if ((pDevice = new CTCUplinkDevice))
			{
				if (pDevice->Unmap(nDevicesData[1]) && Add(pDevice) >= 0) continue;
				delete pDevice;
			}
			break;
		}
		return((cbDevices == sData.cbDevicesData) ? TRUE : FALSE);
	}
	return FALSE;
}

VOID CTCUplinkDevices::EnumDevices(UINT nFlags, LPCTSTR pszDirectory)
{
	BOOL  bFound;
	CFileFind  cFileFind;

	if (cFileFind.FindFile(CString(pszDirectory) + STRING(IDS_FILENAME_ALL)))
	{
		for (bFound = cFileFind.FindNextFile(); TRUE; bFound = cFileFind.FindNextFile())
		{
			if (!cFileFind.IsDots())
			{
				if (!cFileFind.IsDirectory())
				{
					if (!cFileFind.GetFileName().Right(cFileFind.GetFileName().GetLength() - cFileFind.GetFileTitle().GetLength()).CompareNoCase(CString(STRING(IDS_FILENAME_DLL)).Mid(lstrlen(STRING(IDS_FILENAME_DLL)) / 2 - 1))) EnumDevices(nFlags, cFileFind.GetRoot(), cFileFind.GetFileName());
					if (bFound) continue;
					break;
				}
				EnumDevices(nFlags, cFileFind.GetFilePath());
			}
			if (!bFound) break;
		}
		cFileFind.Close();
	}
}
VOID CTCUplinkDevices::EnumDevices(UINT nFlags, LPCTSTR pszDirectory, LPCTSTR pszFileName)
{
	INT  nIndex;
	INT  nCount;
	INT  nDevice[2];
	INT  nDevices[2];
	LPTSTR  *pIODevices;
	CString  szFileName;
	CString  szIODevices;
	HINSTANCE  hIODevices;
	CTCUplinkDevice  *pDevice[2];
	INT(*pEnumDevices)(LPTSTR *ppszProducts, INT nCount);

	for (szFileName = pszDirectory, szFileName += pszFileName; ((pDevice[0] = GetAt((INT)GetUpperBound())) && pDevice[0]->GetDeviceModule().CompareNoCase(szFileName) != 0) || !GetSize(); )
	{
		for (nIndex = 0, nCount = (INT)m_szDevicePathNames[1].GetSize(); nIndex < nCount; nIndex++)
		{
			if (!m_szDevicePathNames[1].GetAt(nIndex).CompareNoCase(szFileName)) break;
			continue;
		}
		if (nIndex == nCount)
		{
			if ((hIODevices = AfxLoadLibrary(szFileName)))
			{
#ifndef UNICODE
				szIODevices = STRING(IDS_EXPORTINTERFACE_ENUMIODEVICEPRODUCTS);
#else
				WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_ENUMIODEVICEPRODUCTS), -1, (LPSTR)szIODevices.GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_ENUMIODEVICEPRODUCTS))), lstrlen(STRING(IDS_EXPORTINTERFACE_ENUMIODEVICEPRODUCTS)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
				szIODevices.ReleaseBuffer();
#endif
				if ((pEnumDevices = (INT(__cdecl *)(LPTSTR *ppszProducts, INT nCount)) GetProcAddress(hIODevices, (LPCSTR)(LPCTSTR)szIODevices)))
				{
					if ((nDevices[0] = (*pEnumDevices)((LPTSTR *)NULL, 0)) > 0)
					{
						if ((pIODevices = (LPTSTR *)GlobalAlloc(GPTR, nDevices[0] * sizeof(LPTSTR))))
						{
							for (nDevice[0] = 0, nDevices[0] = (*pEnumDevices)(pIODevices, nDevices[0]); nDevice[0] < nDevices[0]; nDevice[0]++)
							{
								for (nDevice[1] = 0, nDevices[1] = (INT)GetSize(); nDevice[1] < nDevices[1]; nDevice[1] = nDevice[1] + 1)
								{
									if ((pDevice[0] = GetAt(nDevice[1])) && !pDevice[0]->GetDeviceBrand().CompareNoCase(pIODevices[nDevice[0]]))
									{
										pDevice[0]->SetDeviceModule(szFileName);
										continue;
									}
								}
								for (nDevice[1] = 0; nDevice[1] < nDevices[1]; nDevice[1]++)
								{
									if ((pDevice[0] = GetAt(nDevice[1])) && !pDevice[0]->GetDeviceBrand().CompareNoCase(pIODevices[nDevice[0]])) break;
									continue;
								}
								for (; nDevice[1] == nDevices[1]; )
								{
									if ((pDevice[1] = new CTCUplinkDevice))
									{
										if (pDevice[1]->Open(szFileName, pIODevices[nDevice[0]]))
										{
											if (pDevice[1]->GetCapabilities() & IODEVICE_SERVICE_TC)
											{
												pDevice[1]->SetDeviceName(EMPTYSTRING);
												pDevice[1]->SetDeviceModule(szFileName);
												if (pDevice[1]->Initialize(nFlags) && Add(pDevice[1]) >= 0)
												{
													m_szDevicePathNames[0].Add(szFileName);
													pDevice[1]->Close();
													break;
												}
											}
											pDevice[1]->Close();
										}
										delete pDevice[1];
									}
									break;
								}
								for (nIndex = 0, nCount = (nDevice[1] < nDevices[1]) ? (INT)m_szDevicePathNames[0].GetSize() : -1; nIndex < nCount; nIndex++)
								{
									if (!m_szDevicePathNames[0].GetAt(nIndex).CompareNoCase(szFileName)) break;
									continue;
								}
								if (nIndex == nCount)
								{
									m_szDevicePathNames[0].Add(szFileName);
									continue;
								}
							}
							for (nDevice[0] = 0; nDevice[0] < nDevices[0]; nDevice[0]++)
							{
								GlobalFree(pIODevices[nDevice[0]]);
								continue;
							}
							GlobalFree(pIODevices);
						}
					}
				}
				m_szDevicePathNames[1].Add(szFileName);
				AfxFreeLibrary(hIODevices);
			}
		}
		break;
	}
}


/////////////////////////////////////////////////////////////////////////////
// CTCLogEntry

CTCLogEntry::CTCLogEntry() : CComputerToken()
{
	m_tTime = 0;
}

VOID CTCLogEntry::SetName(LPCTSTR pszName)
{
	m_szName = pszName;
}

CString CTCLogEntry::GetName() CONST
{
	return m_szName;
}

VOID CTCLogEntry::SetDescription(LPCTSTR pszDescription)
{
	m_szDescription = pszDescription;
}

CString CTCLogEntry::GetDescription() CONST
{
	return m_szDescription;
}

VOID CTCLogEntry::SetActivity(LPCTSTR pszActivity)
{
	m_szActivity = pszActivity;
}

CString CTCLogEntry::GetActivity() CONST
{
	return m_szActivity;
}

VOID CTCLogEntry::SetUser(LPCTSTR pszUser)
{
	m_szUser = pszUser;
}

CString CTCLogEntry::GetUser() CONST
{
	return m_szUser;
}

VOID CTCLogEntry::SetTime(CONST CTimeKey &tTime)
{
	m_tTime = tTime;
}

CTimeKey CTCLogEntry::GetTime() CONST
{
	return m_tTime;
}

VOID CTCLogEntry::Copy(CONST CTCLogEntry *pEntry)
{
	m_szName = pEntry->m_szName;
	m_szComputerName = pEntry->m_szComputerName;
	m_szDescription = pEntry->m_szDescription;
	m_szActivity = pEntry->m_szActivity;
	m_szUser = pEntry->m_szUser;
	m_tTime = pEntry->m_tTime;
}

BOOL CTCLogEntry::Compare(CONST CTCLogEntry *pEntry) CONST
{
	return((pEntry->m_szName == m_szName  &&  !pEntry->m_szComputerName.CompareNoCase(m_szComputerName) && pEntry->m_szDescription == m_szDescription  &&  pEntry->m_szActivity == m_szActivity  &&  pEntry->m_szUser == m_szUser  &&  pEntry->m_tTime == m_tTime) ? TRUE : FALSE);
}

BOOL CTCLogEntry::Map(CByteArray &nInfo) CONST
{
	INT  cbData;
	DATA  sData;

	sData.cbName = (m_szName.GetLength() + 1)*sizeof(TCHAR);
	sData.cbUser = (m_szUser.GetLength() + 1)*sizeof(TCHAR);
	sData.cbActivity = (m_szActivity.GetLength() + 1)*sizeof(TCHAR);
	sData.cbDescription = (m_szDescription.GetLength() + 1)*sizeof(TCHAR);
	sData.cbComputerName = (m_szComputerName.GetLength() + 1)*sizeof(TCHAR);
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbName + sData.cbComputerName + sData.cbDescription + sData.cbActivity + sData.cbUser)), sData.tTime = m_tTime.GetTime(); nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szName, sData.cbName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbName), (LPCTSTR)m_szComputerName, sData.cbComputerName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbComputerName), (LPCTSTR)m_szDescription, sData.cbDescription);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbDescription), (LPCTSTR)m_szActivity, sData.cbActivity);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbActivity), (LPCTSTR)m_szUser, sData.cbUser);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCLogEntry::Unmap(CONST CByteArray &nInfo)
{
	INT  cbData;
	DATA  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbName + sData.cbComputerName + sData.cbDescription + sData.cbActivity + sData.cbUser && sData.cbName > 0 && sData.cbComputerName > 0 && sData.cbDescription > 0 && sData.cbActivity > 0 && sData.cbUser > 0; )
	{
		CopyMemory(m_szName.GetBufferSetLength(STRINGCHARS(sData.cbName)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbName));
		CopyMemory(m_szComputerName.GetBufferSetLength(STRINGCHARS(sData.cbComputerName)), nInfo.GetData() + (cbData = cbData + sData.cbName), STRINGBYTES(sData.cbComputerName));
		CopyMemory(m_szDescription.GetBufferSetLength(STRINGCHARS(sData.cbDescription)), nInfo.GetData() + (cbData = cbData + sData.cbComputerName), STRINGBYTES(sData.cbDescription));
		CopyMemory(m_szActivity.GetBufferSetLength(STRINGCHARS(sData.cbActivity)), nInfo.GetData() + (cbData = cbData + sData.cbDescription), STRINGBYTES(sData.cbActivity));
		CopyMemory(m_szUser.GetBufferSetLength(STRINGCHARS(sData.cbUser)), nInfo.GetData() + (cbData = cbData + sData.cbActivity), STRINGBYTES(sData.cbUser));
		m_tTime = sData.tTime;
		m_szName.ReleaseBuffer();
		m_szComputerName.ReleaseBuffer();
		m_szDescription.ReleaseBuffer();
		m_szActivity.ReleaseBuffer();
		m_szUser.ReleaseBuffer();
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CTCLogEntries

CTCLogEntries::CTCLogEntries() : CPtrArray()
{
	return;
}

CTCLogEntries::~CTCLogEntries()
{
	RemoveAll();
}

INT CTCLogEntries::Add(CTCLogEntry *pEntry)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pEntry->GetTime(), TRUE)) >= 0) InsertAt(nIndex, pEntry, 1);
	return nIndex;
}

INT CTCLogEntries::Find(CONST CTCLogEntry *pEntry) CONST
{
	INT  nEntry;
	INT  nEntries;

	for (nEntry = FindIndex(pEntry->GetTime()), nEntries = (INT)GetSize(); nEntry < nEntries && nEntry >= 0; nEntry++)
	{
		if (pEntry->GetTime() == GetAt(nEntry)->GetTime())
		{
			if (!pEntry->Compare(GetAt(nEntry))) continue;
			return nEntry;
		}
		break;
	}
	return -1;
}

CTCLogEntry *CTCLogEntries::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCLogEntry *)CPtrArray::GetAt(nIndex) : (CTCLogEntry *)NULL);
}

CTCLogEntry *CTCLogEntries::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCLogEntry *)CPtrArray::GetAt(nIndex) : (CTCLogEntry *)NULL);
}

VOID CTCLogEntries::RemoveAll()
{
	INT  nEntry;
	INT  nEntries;
	CTCLogEntry  *pEntry;

	for (nEntry = 0, nEntries = (INT)GetSize(); nEntry < nEntries; nEntry++)
	{
		if ((pEntry = GetAt(nEntry)))
		{
			delete pEntry;
			continue;
		}
	}
	CPtrArray::RemoveAll();
}

BOOL CTCLogEntries::Copy(CONST CTCLogEntries *pEntries)
{
	INT  nEntry;
	INT  nEntries;
	CTCLogEntry  *pEntry;

	for (nEntry = 0, nEntries = (INT)pEntries->GetSize(), RemoveAll(); nEntry < nEntries; nEntry++)
	{
		if ((pEntry = new CTCLogEntry) != (CTCLogEntry *)NULL)
		{
			pEntry->Copy(pEntries->GetAt(nEntry));
			InsertAt(nEntry, pEntry, 1);
			continue;
		}
		break;
	}
	return((nEntry == nEntries) ? TRUE : FALSE);
}

BOOL CTCLogEntries::Compare(CONST CTCLogEntries *pEntries) CONST
{
	INT  nEntry;
	INT  nEntries;
	CTCLogEntry  *pEntry;

	for (nEntry = 0, nEntries = (pEntries->GetSize() == GetSize()) ? (INT)pEntries->GetSize() : -1; nEntry < nEntries; nEntry++)
	{
		if ((pEntry = pEntries->GetAt(nEntry)) && pEntry->Compare(GetAt(nEntry))) continue;
		break;
	}
	return((nEntry == nEntries) ? TRUE : FALSE);
}

BOOL CTCLogEntries::Map(CByteArray &nInfo) CONST
{
	INT  nEntry;
	INT  nEntries;
	CByteArray  nEntryData;
	CTCLogEntry  *pEntry;

	for (nEntry = 0, nEntries = (INT)GetSize(), nInfo.RemoveAll(); nEntry < nEntries; nEntry++)
	{
		if ((pEntry = GetAt(nEntry)) && pEntry->Map(nEntryData) && nInfo.Append(nEntryData) >= 0) continue;
		break;
	}
	return((nEntry == nEntries) ? TRUE : FALSE);
}

BOOL CTCLogEntries::Unmap(CONST CByteArray &nInfo)
{
	INT  cbEntry;
	INT  cbEntries;
	CByteArray  nEntryData;
	CTCLogEntry  *pEntry;

	for (cbEntries = 0, RemoveAll(); cbEntries < nInfo.GetSize(); cbEntries += cbEntry)
	{
		for (CopyMemory(&cbEntry, nInfo.GetData() + cbEntries, sizeof(cbEntry)), nEntryData.SetSize(max(min(cbEntry, nInfo.GetSize() - cbEntries), 0)); nEntryData.GetSize() >= 0; )
		{
			CopyMemory(nEntryData.GetData(), nInfo.GetData() + cbEntries, nEntryData.GetSize());
			break;
		}
		if ((pEntry = new CTCLogEntry))
		{
			if (pEntry->Unmap(nEntryData) && Add(pEntry) >= 0) continue;
			delete pEntry;
		}
		break;
	}
	return((cbEntries == nInfo.GetSize()) ? TRUE : FALSE);
}

INT CTCLogEntries::FindIndex(CONST CTimeKey &tTime, BOOL bInsert) CONST
{
	INT  nIndex;
	INT  nMinIndex;
	INT  nMaxIndex;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex = (nMinIndex + nMaxIndex) / 2)
	{
		if ((!bInsert  &&  tTime > GetAt(nIndex)->GetTime()) || (bInsert  &&  tTime >= GetAt(nIndex)->GetTime()))
		{
			nMinIndex = nIndex + 1;
			continue;
		}
		nMaxIndex = nIndex;
	}
	return(((!bInsert  &&  nIndex < GetSize()) || (bInsert  &&  nIndex <= GetSize())) ? nIndex : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcessCommandSourceInfo

CTCProcessCommandSourceInfo::CTCProcessCommandSourceInfo() : CComputerToken()
{
	m_nSourceType = 0;
	m_nTelecommandingMode = 0;
	m_nTelecommandingState = 0;
	m_nTelecommandingFlags = 0;
	m_bTelecommandingInterlockMode = FALSE;
	m_bTelecommandingReleaseWaitMode = FALSE;
	m_bTelecommandingAutoRejectionMode = FALSE;
	m_tDefaultReleaseTimeWindow = 0;
	m_tDispatchTimeWindow = 0;
}

VOID CTCProcessCommandSourceInfo::SetSourceType(UINT nType)
{
	m_nSourceType = nType;
}

UINT CTCProcessCommandSourceInfo::GetSourceType() CONST
{
	return m_nSourceType;
}

VOID CTCProcessCommandSourceInfo::SetTelecommandingMode(UINT nMode)
{
	m_nTelecommandingMode = nMode;
}

UINT CTCProcessCommandSourceInfo::GetTelecommandingMode() CONST
{
	return m_nTelecommandingMode;
}

VOID CTCProcessCommandSourceInfo::SetTelecommandingState(UINT nState)
{
	m_nTelecommandingState = nState;
}

UINT CTCProcessCommandSourceInfo::GetTelecommandingState() CONST
{
	return m_nTelecommandingState;
}

VOID CTCProcessCommandSourceInfo::SetTelecommandingChecks(UINT nFlags)
{
	m_nTelecommandingFlags = nFlags;
}

UINT CTCProcessCommandSourceInfo::GetTelecommandingChecks() CONST
{
	return m_nTelecommandingFlags;
}

VOID CTCProcessCommandSourceInfo::EnableTelecommandingInterlockMode(BOOL bEnable)
{
	m_bTelecommandingInterlockMode = bEnable;
}

BOOL CTCProcessCommandSourceInfo::IsTelecommandingInterlockModeEnabled() CONST
{
	return m_bTelecommandingInterlockMode;
}

VOID CTCProcessCommandSourceInfo::EnableTelecommandingReleaseWaitMode(BOOL bEnable)
{
	m_bTelecommandingReleaseWaitMode = bEnable;
}

BOOL CTCProcessCommandSourceInfo::IsTelecommandingReleaseWaitModeEnabled() CONST
{
	return m_bTelecommandingReleaseWaitMode;
}

VOID CTCProcessCommandSourceInfo::EnableTelecommandingAutoRejectionMode(BOOL bEnable)
{
	m_bTelecommandingAutoRejectionMode = bEnable;
}

BOOL CTCProcessCommandSourceInfo::IsTelecommandingAutoRejectionModeEnabled() CONST
{
	return m_bTelecommandingAutoRejectionMode;
}

VOID CTCProcessCommandSourceInfo::SetSubSystemChecks(CONST CUIntArray &nSubSystemIDs, CONST CStringArray &szEnablingEvents, CONST CStringArray &szDisablingEvents, CONST CUIntArray &nStatus)
{
	INT  nSubSystem;
	INT  nSubSystems;

	for (nSubSystem = 0, nSubSystems = (INT)nSubSystemIDs.GetSize(), m_nSubSystemIDs.Copy(nSubSystemIDs), m_szSubSystemEvents[0].Copy(szEnablingEvents), m_szSubSystemEvents[1].Copy(szDisablingEvents); nSubSystem < nSubSystems; nSubSystem++)
	{
		m_nSubSystemStatus.SetAtGrow(nSubSystem, MAKEWORD(LOBYTE(nStatus.GetAt(nSubSystem)), (IsHost()) ? ((LOBYTE(nStatus.GetAt(nSubSystem))) ? !GetTMService()->CheckTelemetryEvent(szDisablingEvents.GetAt(nSubSystem)) : FALSE) : HIBYTE(nStatus.GetAt(nSubSystem))));
		continue;
	}
}

INT CTCProcessCommandSourceInfo::GetSubSystemChecks(CUIntArray &nSubSystemIDs, CStringArray &szEnablingEvents, CStringArray &szDisablingEvents, CUIntArray &nStatus) CONST
{
	nSubSystemIDs.Copy(m_nSubSystemIDs);
	szEnablingEvents.Copy(m_szSubSystemEvents[0]);
	szDisablingEvents.Copy(m_szSubSystemEvents[1]);
	nStatus.Copy(m_nSubSystemStatus);
	return((INT)nSubSystemIDs.GetSize());
}

VOID CTCProcessCommandSourceInfo::SetDefaultReleaseTimeWindow(CONST CTimeSpan &tTimeWindow)
{
	m_tDefaultReleaseTimeWindow = tTimeWindow;
}

CTimeSpan CTCProcessCommandSourceInfo::GetDefaultReleaseTimeWindow() CONST
{
	return m_tDefaultReleaseTimeWindow;
}

VOID CTCProcessCommandSourceInfo::SetDispatchTimeWindow(CONST CTimeSpan &tTimeWindow)
{
	m_tDispatchTimeWindow = tTimeWindow;
}

CTimeSpan CTCProcessCommandSourceInfo::GetDispatchTimeWindow() CONST
{
	return m_tDispatchTimeWindow;
}

BOOL CTCProcessCommandSourceInfo::Update(LPCTSTR pszEvent)
{
	INT  nSubSystem;
	INT  nSubSystems;
	BOOL  bSubSystems;

	for (nSubSystem = 0, nSubSystems = (INT)m_nSubSystemIDs.GetSize(), bSubSystems = FALSE; nSubSystem < nSubSystems; nSubSystem++)
	{
		if (((!m_szSubSystemEvents[0].GetAt(nSubSystem).Compare(pszEvent) && !HIBYTE(m_nSubSystemStatus.GetAt(nSubSystem))) || (!m_szSubSystemEvents[1].GetAt(nSubSystem).Compare(pszEvent) && HIBYTE(m_nSubSystemStatus.GetAt(nSubSystem)))) && LOBYTE(m_nSubSystemStatus.GetAt(nSubSystem)))
		{
			m_nSubSystemStatus.SetAt(nSubSystem, MAKEWORD(LOBYTE(m_nSubSystemStatus.GetAt(nSubSystem)), !HIBYTE(m_nSubSystemStatus.GetAt(nSubSystem))));
			bSubSystems = TRUE;
		}
	}
	return bSubSystems;
}

VOID CTCProcessCommandSourceInfo::Copy(CONST CTCProcessCommandSourceInfo *pCommandSourceInfo)
{
	m_szComputerName = pCommandSourceInfo->m_szComputerName;
	m_nSourceType = pCommandSourceInfo->m_nSourceType;
	m_nTelecommandingMode = pCommandSourceInfo->m_nTelecommandingMode;
	m_nTelecommandingState = pCommandSourceInfo->m_nTelecommandingState;
	m_nTelecommandingFlags = pCommandSourceInfo->m_nTelecommandingFlags;
	m_bTelecommandingInterlockMode = pCommandSourceInfo->m_bTelecommandingInterlockMode;
	m_bTelecommandingReleaseWaitMode = pCommandSourceInfo->m_bTelecommandingReleaseWaitMode;
	m_bTelecommandingAutoRejectionMode = pCommandSourceInfo->m_bTelecommandingAutoRejectionMode;
	m_tDefaultReleaseTimeWindow = pCommandSourceInfo->m_tDefaultReleaseTimeWindow;
	m_tDispatchTimeWindow = pCommandSourceInfo->m_tDispatchTimeWindow;
	m_nSubSystemIDs.Copy(pCommandSourceInfo->m_nSubSystemIDs);
	m_szSubSystemEvents[0].Copy(pCommandSourceInfo->m_szSubSystemEvents[0]);
	m_szSubSystemEvents[1].Copy(pCommandSourceInfo->m_szSubSystemEvents[1]);
	m_nSubSystemStatus.Copy(pCommandSourceInfo->m_nSubSystemStatus);
}

BOOL CTCProcessCommandSourceInfo::Compare(CONST CTCProcessCommandSourceInfo *pCommandSourceInfo) CONST
{
	INT  nSubSystem[2];
	INT  nSubSystems[2];

	for (nSubSystem[0] = 0, nSubSystems[0] = (!pCommandSourceInfo->m_szComputerName.CompareNoCase(m_szComputerName) && pCommandSourceInfo->m_nSourceType == m_nSourceType && pCommandSourceInfo->m_nTelecommandingMode == m_nTelecommandingMode && pCommandSourceInfo->m_nTelecommandingState == m_nTelecommandingState && pCommandSourceInfo->m_nTelecommandingFlags == m_nTelecommandingFlags && pCommandSourceInfo->m_bTelecommandingInterlockMode == m_bTelecommandingInterlockMode && pCommandSourceInfo->m_bTelecommandingReleaseWaitMode == m_bTelecommandingReleaseWaitMode && pCommandSourceInfo->m_bTelecommandingAutoRejectionMode == m_bTelecommandingAutoRejectionMode && pCommandSourceInfo->m_tDefaultReleaseTimeWindow == m_tDefaultReleaseTimeWindow && pCommandSourceInfo->m_tDispatchTimeWindow == m_tDispatchTimeWindow && pCommandSourceInfo->m_nSubSystemIDs.GetSize() == m_nSubSystemIDs.GetSize() && pCommandSourceInfo->m_szSubSystemEvents[0].GetSize() == m_szSubSystemEvents[0].GetSize() && pCommandSourceInfo->m_szSubSystemEvents[1].GetSize() == m_szSubSystemEvents[1].GetSize() && pCommandSourceInfo->m_nSubSystemStatus.GetSize() == m_nSubSystemStatus.GetSize()) ? (INT)pCommandSourceInfo->m_nSubSystemIDs.GetSize() : -1; nSubSystem[0] < nSubSystems[0]; nSubSystem[0]++)
	{
		for (nSubSystem[1] = 0, nSubSystems[1] = (INT)m_nSubSystemIDs.GetSize(); nSubSystem[1] < nSubSystems[1]; nSubSystem[1]++)
		{
			if (pCommandSourceInfo->m_nSubSystemIDs.GetAt(nSubSystem[0]) == m_nSubSystemIDs.GetAt(nSubSystem[1]))
			{
				if (pCommandSourceInfo->m_szSubSystemEvents[0].GetAt(nSubSystem[0]).Compare(m_szSubSystemEvents[0].GetAt(nSubSystem[1]))) continue;
				if (pCommandSourceInfo->m_szSubSystemEvents[1].GetAt(nSubSystem[0]).Compare(m_szSubSystemEvents[1].GetAt(nSubSystem[1]))) continue;
				if (pCommandSourceInfo->m_nSubSystemStatus.GetAt(nSubSystem[0]) != m_nSubSystemStatus.GetAt(nSubSystem[1])) continue;
				break;
			}
		}
		if (nSubSystem[1] == nSubSystems[1]) break;
	}
	return((nSubSystem[0] == nSubSystems[0]) ? TRUE : FALSE);
}

BOOL CTCProcessCommandSourceInfo::Map(CByteArray &nInfo) CONST
{
	DATA  sData;
	INT  cbData;
	INT  nSubSystem;
	INT  nSubSystems;
	CByteArray  nSubSystemEventsData[2];

	for (nSubSystem = 0, nSubSystems = (INT)m_nSubSystemIDs.GetSize(), sData.cbComputerName = (m_szComputerName.GetLength() + 1)*sizeof(TCHAR), sData.cbSubSystemIDs = (INT)(m_nSubSystemIDs.GetSize()*sizeof(UINT)), sData.cbSubSystemStatus = (INT)(m_nSubSystemStatus.GetSize()*sizeof(UINT)), sData.cbSubSystemEvents[0] = sData.cbSubSystemEvents[1] = 0; nSubSystem < nSubSystems; nSubSystem++)
	{
		nSubSystemEventsData[0].SetSize(sData.cbSubSystemEvents[0] + (m_szSubSystemEvents[0].GetAt(nSubSystem).GetLength() + 1)*sizeof(TCHAR));
		nSubSystemEventsData[1].SetSize(sData.cbSubSystemEvents[1] + (m_szSubSystemEvents[1].GetAt(nSubSystem).GetLength() + 1)*sizeof(TCHAR));
		CopyMemory(nSubSystemEventsData[0].GetData() + sData.cbSubSystemEvents[0], (LPCTSTR)m_szSubSystemEvents[0].GetAt(nSubSystem), (m_szSubSystemEvents[0].GetAt(nSubSystem).GetLength() + 1)*sizeof(TCHAR));
		CopyMemory(nSubSystemEventsData[1].GetData() + sData.cbSubSystemEvents[1], (LPCTSTR)m_szSubSystemEvents[1].GetAt(nSubSystem), (m_szSubSystemEvents[1].GetAt(nSubSystem).GetLength() + 1)*sizeof(TCHAR));
		sData.cbSubSystemEvents[0] += (m_szSubSystemEvents[0].GetAt(nSubSystem).GetLength() + 1)*sizeof(TCHAR);
		sData.cbSubSystemEvents[1] += (m_szSubSystemEvents[1].GetAt(nSubSystem).GetLength() + 1)*sizeof(TCHAR);
	}
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + sData.cbComputerName + sData.cbSubSystemIDs + sData.cbSubSystemEvents[0] + sData.cbSubSystemEvents[1] + sData.cbSubSystemStatus)), sData.nSourceType = m_nSourceType, sData.nTelecommandingMode = m_nTelecommandingMode, sData.nTelecommandingState = m_nTelecommandingState, sData.nTelecommandingFlags = m_nTelecommandingFlags, sData.bTelecommandingInterlockMode = m_bTelecommandingInterlockMode, sData.bTelecommandingReleaseWaitMode = m_bTelecommandingReleaseWaitMode, sData.bTelecommandingAutoRejectionMode = m_bTelecommandingAutoRejectionMode, sData.tDefaultReleaseTimeWindow = m_tDefaultReleaseTimeWindow.GetTotalSeconds(), sData.tDispatchTimeWindow = m_tDispatchTimeWindow.GetTotalSeconds(); nInfo.GetSize() == sData.cbSize; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), (LPCTSTR)m_szComputerName, sData.cbComputerName);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbComputerName), m_nSubSystemIDs.GetData(), sData.cbSubSystemIDs);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbSubSystemIDs), nSubSystemEventsData[0].GetData(), sData.cbSubSystemEvents[0]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbSubSystemEvents[0]), nSubSystemEventsData[1].GetData(), sData.cbSubSystemEvents[1]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbSubSystemEvents[1]), m_nSubSystemStatus.GetData(), sData.cbSubSystemStatus);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcessCommandSourceInfo::Unmap(CONST CByteArray &nInfo)
{
	DATA  sData;
	INT  cbData;
	INT  cbSubSystem;
	INT  cbSubSystems;
	CByteArray  nSubSystemEventsData[2];

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbComputerName + sData.cbSubSystemIDs + sData.cbSubSystemEvents[0] + sData.cbSubSystemEvents[1] + sData.cbSubSystemStatus && sData.cbComputerName > 0 && sData.cbSubSystemIDs >= 0 && sData.cbSubSystemEvents[0] >= 0 && sData.cbSubSystemEvents[1] >= 0 && sData.cbSubSystemStatus >= 0; )
	{
		for (m_nSubSystemIDs.SetSize(sData.cbSubSystemIDs / sizeof(UINT)), nSubSystemEventsData[0].SetSize(sData.cbSubSystemEvents[0]), nSubSystemEventsData[1].SetSize(sData.cbSubSystemEvents[1]), m_nSubSystemStatus.SetSize(sData.cbSubSystemStatus / sizeof(UINT)), CopyMemory(m_szComputerName.GetBufferSetLength(STRINGCHARS(sData.cbComputerName)), nInfo.GetData() + (cbData = sizeof(DATA)), STRINGBYTES(sData.cbComputerName)), CopyMemory(m_nSubSystemIDs.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbComputerName), sData.cbSubSystemIDs), CopyMemory(nSubSystemEventsData[0].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbSubSystemIDs), sData.cbSubSystemEvents[0]), CopyMemory(nSubSystemEventsData[1].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbSubSystemEvents[0]), sData.cbSubSystemEvents[1]), CopyMemory(m_nSubSystemStatus.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbSubSystemEvents[1]), sData.cbSubSystemStatus), m_nSourceType = sData.nSourceType, m_nTelecommandingMode = sData.nTelecommandingMode, m_nTelecommandingState = sData.nTelecommandingState, m_nTelecommandingFlags = sData.nTelecommandingFlags, m_bTelecommandingInterlockMode = sData.bTelecommandingInterlockMode, m_bTelecommandingReleaseWaitMode = sData.bTelecommandingReleaseWaitMode, m_bTelecommandingAutoRejectionMode = sData.bTelecommandingAutoRejectionMode, m_tDefaultReleaseTimeWindow = sData.tDefaultReleaseTimeWindow, m_tDispatchTimeWindow = sData.tDispatchTimeWindow, m_szComputerName.ReleaseBuffer(), m_szSubSystemEvents[0].RemoveAll(), cbSubSystem = cbSubSystems = 0; cbSubSystems < sData.cbSubSystemEvents[0]; cbSubSystems += cbSubSystem)
		{
			m_szSubSystemEvents[0].Add((LPCTSTR)(nSubSystemEventsData[0].GetData() + cbSubSystems));
			cbSubSystem = (m_szSubSystemEvents[0].GetAt(m_szSubSystemEvents[0].GetUpperBound()).GetLength() + 1)*sizeof(TCHAR);
		}
		for (m_szSubSystemEvents[1].RemoveAll(), cbSubSystem = cbSubSystems = 0; cbSubSystems < sData.cbSubSystemEvents[1]; cbSubSystems += cbSubSystem)
		{
			m_szSubSystemEvents[1].Add((LPCTSTR)(nSubSystemEventsData[1].GetData() + cbSubSystems));
			cbSubSystem = (m_szSubSystemEvents[1].GetAt(m_szSubSystemEvents[1].GetUpperBound()).GetLength() + 1)*sizeof(TCHAR);
		}
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcessCommandSources

CTCProcessCommandSources::CTCProcessCommandSources() : CPtrArray()
{
	return;
}

CTCProcessCommandSources::~CTCProcessCommandSources()
{
	RemoveAll();
}

INT CTCProcessCommandSources::Add(CTCProcessCommandSourceInfo *pCommandSourceInfo)
{
	INT  nIndex;

	if ((nIndex = FindIndex(pCommandSourceInfo->GetComputerName(), pCommandSourceInfo->GetSourceType(), TRUE)) >= 0) InsertAt(nIndex, pCommandSourceInfo, 1);
	return nIndex;
}

INT CTCProcessCommandSources::Find(LPCTSTR pszComputerName, UINT nSourceType) CONST
{
	return FindIndex(pszComputerName, nSourceType);
}

CTCProcessCommandSourceInfo *CTCProcessCommandSources::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCProcessCommandSourceInfo *)CPtrArray::GetAt(nIndex) : (CTCProcessCommandSourceInfo *)NULL);
}

CTCProcessCommandSourceInfo *CTCProcessCommandSources::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCProcessCommandSourceInfo *)CPtrArray::GetAt(nIndex) : (CTCProcessCommandSourceInfo *)NULL);
}

VOID CTCProcessCommandSources::RemoveAll()
{
	INT  nCommandSource;
	INT  nCommandSources;

	for (nCommandSource = 0, nCommandSources = (INT)GetSize(); nCommandSource < nCommandSources; nCommandSource++)
	{
		delete GetAt(nCommandSource);
		continue;
	}
	CPtrArray::RemoveAll();
}

BOOL CTCProcessCommandSources::Copy(CONST CTCProcessCommandSources *pCommandSources)
{
	INT  nCommandSource;
	INT  nCommandSources;
	CTCProcessCommandSourceInfo  *pCommandSourceInfo;

	for (nCommandSource = 0, nCommandSources = (INT)pCommandSources->GetSize(), RemoveAll(); nCommandSource < nCommandSources; nCommandSource++)
	{
		if ((pCommandSourceInfo = new CTCProcessCommandSourceInfo) != (CTCProcessCommandSourceInfo *)NULL)
		{
			pCommandSourceInfo->Copy(pCommandSources->GetAt(nCommandSource));
			InsertAt(nCommandSource, pCommandSourceInfo, 1);
			continue;
		}
		break;
	}
	return((nCommandSource == nCommandSources) ? TRUE : FALSE);
}

BOOL CTCProcessCommandSources::Compare(CONST CTCProcessCommandSources *pCommandSources) CONST
{
	INT  nCommandSource;
	INT  nCommandSources;

	for (nCommandSource = 0, nCommandSources = (pCommandSources->GetSize() == GetSize()) ? (INT)GetSize() : -1; nCommandSource < nCommandSources; nCommandSource++)
	{
		if (!pCommandSources->GetAt(nCommandSource)->Compare(GetAt(nCommandSource))) break;
		continue;
	}
	return((nCommandSource == nCommandSources) ? TRUE : FALSE);
}

BOOL CTCProcessCommandSources::Map(CByteArray &nInfo) CONST
{
	INT  nCommandSource;
	INT  nCommandSources;
	CByteArray  nCommandSourceData;
	CTCProcessCommandSourceInfo  *pCommandSourceInfo;

	for (nCommandSource = 0, nCommandSources = (INT)GetSize(), nInfo.RemoveAll(); nCommandSource < nCommandSources; nCommandSource++)
	{
		if ((pCommandSourceInfo = GetAt(nCommandSource)) && pCommandSourceInfo->Map(nCommandSourceData) && nInfo.Append(nCommandSourceData) >= 0) continue;
		break;
	}
	return((nCommandSource == nCommandSources) ? TRUE : FALSE);
}

BOOL CTCProcessCommandSources::Unmap(CONST CByteArray &nInfo)
{
	INT  cbCommandSource;
	INT  cbCommandSources;
	CByteArray  nCommandSourceData;
	CTCProcessCommandSourceInfo  *pCommandSourceInfo;

	for (cbCommandSources = 0, RemoveAll(); cbCommandSources < nInfo.GetSize(); cbCommandSources += cbCommandSource)
	{
		for (CopyMemory(&cbCommandSource, nInfo.GetData() + cbCommandSources, sizeof(cbCommandSource)), nCommandSourceData.SetSize(max(min(cbCommandSource, nInfo.GetSize() - cbCommandSources), 0)); nCommandSourceData.GetSize() >= 0; )
		{
			CopyMemory(nCommandSourceData.GetData(), nInfo.GetData() + cbCommandSources, nCommandSourceData.GetSize());
			break;
		}
		if ((pCommandSourceInfo = new CTCProcessCommandSourceInfo))
		{
			if (pCommandSourceInfo->Unmap(nCommandSourceData) && Add(pCommandSourceInfo) >= 0) continue;
			delete pCommandSourceInfo;
		}
		break;
	}
	return((cbCommandSources == nInfo.GetSize()) ? TRUE : FALSE);
}

INT CTCProcessCommandSources::FindIndex(LPCTSTR pszComputerName, UINT nSourceType, BOOL bInsert) CONST
{
	INT  nIndex[2];
	INT  nMinIndex;
	INT  nMaxIndex;
	CString  szCommandSource;
	CTCProcessCommandSourceInfo  *pCommandSourceInfo;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex[0] = (nMinIndex + nMaxIndex) / 2, szCommandSource = ConstructSearchName(pszComputerName, nSourceType); nMinIndex != nMaxIndex; nIndex[0] = (nMinIndex + nMaxIndex) / 2)
	{
		nMinIndex = ((pCommandSourceInfo = GetAt(nIndex[0]))) ? ((nIndex[1] = (ConstructSearchName(pCommandSourceInfo) <= szCommandSource)) ? (nIndex[0] + 1) : nMinIndex) : (nIndex[0] = -1);
		nMaxIndex = (nIndex[0] < 0 || !nIndex[1]) ? nIndex[0] : nMaxIndex;
	}
	return(((!bInsert && (pCommandSourceInfo = GetAt((nIndex[0] = max(nIndex[0] - 1, 0)))) && ConstructSearchName(pCommandSourceInfo) == szCommandSource) || (bInsert && (((pCommandSourceInfo = GetAt(max(nIndex[0] - 1, 0))) && ConstructSearchName(pCommandSourceInfo) != szCommandSource && (pCommandSourceInfo = GetAt((INT)min(nIndex[0], GetUpperBound()))) && ConstructSearchName(pCommandSourceInfo) != szCommandSource) || !GetSize()))) ? nIndex[0] : -1);
}

CString CTCProcessCommandSources::ConstructSearchName(LPCTSTR pszComputerName, UINT nSourceType) CONST
{
	CStringTools  cStringTools;

	return CString(pszComputerName) + TAB + cStringTools.ConvertUIntToString(nSourceType);
}
CString CTCProcessCommandSources::ConstructSearchName(CONST CTCProcessCommandSourceInfo *pCommandSourceInfo) CONST
{
	return ConstructSearchName(pCommandSourceInfo->GetComputerName(), pCommandSourceInfo->GetSourceType());
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceMessageHeader

CTCProcessInterfaceMessageHeader::CTCProcessInterfaceMessageHeader() : CObject()
{
	m_sHeader.nMessageID = 0;
	m_sHeader.nMessageLength[0] = 0;
	m_sHeader.nMessageLength[1] = 0;
	m_sHeader.nMessageLength[2] = 0;
	m_sHeader.nVersion = TCPI_VERSION;
}
CTCProcessInterfaceMessageHeader::CTCProcessInterfaceMessageHeader(BYTE nID, UINT nLength) : CObject()
{
	SetMessageID(nID);
	SetMessageLength(nLength);
	SetVersion(TCPI_VERSION);
}

BOOL CTCProcessInterfaceMessageHeader::SetMessageID(BYTE nID)
{
	if (nID == TCPI_ANNOUNCECOMMANDHANDLERREQUEST || nID == TCPI_ANNOUNCECOMMANDHANDLERRESPONSE || nID == TCPI_SETCOMMANDHANDLERCONFIGURATIONREQUEST || nID == TCPI_SETCOMMANDHANDLERCONFIGURATIONRESPONSE || nID == TCPI_GETCOMMANDHANDLERCONFIGURATIONREQUEST || nID == TCPI_GETCOMMANDHANDLERCONFIGURATIONRESPONSE || nID == TCPI_REGISTERCOMMANDSOURCESREQUEST || nID == TCPI_REGISTERCOMMANDSOURCESRESPONSE || nID == TCPI_UPDATECOMMANDSOURCESREQUEST || nID == TCPI_UPDATECOMMANDSOURCESRESPONSE || nID == TCPI_UPDATECOMMANDSOURCESCONTENTSREQUEST || nID == TCPI_UPDATECOMMANDSOURCESCONTENTSRESPONSE || nID == TCPI_UPDATECOMMANDUPLINKDEVICESTATE || nID == TCPI_DISPATCHTELECOMMANDSREQUEST || nID == TCPI_DISPATCHTELECOMMANDSRESPONSE || nID == TCPI_RELEASETELECOMMANDSREQUEST || nID == TCPI_RELEASETELECOMMANDSRESPONSE || nID == TCPI_EXECUTETELECOMMANDREQUEST || nID == TCPI_EXECUTETELECOMMANDRESPONSE || nID == TCPI_ACKNOWLEDGETELECOMMANDSREQUEST || nID == TCPI_ACKNOWLEDGETELECOMMANDSRESPONSE || nID == TCPI_DISCARDTELECOMMANDSREQUEST || nID == TCPI_DISCARDTELECOMMANDSRESPONSE)
	{
		m_sHeader.nMessageID = nID;
		return TRUE;
	}
	return FALSE;
}

BYTE CTCProcessInterfaceMessageHeader::GetMessageID() CONST
{
	return m_sHeader.nMessageID;
}

BOOL CTCProcessInterfaceMessageHeader::SetMessageLength(UINT nLength)
{
	if (nLength >= sizeof(TCPIMESSAGEHEADER) - TCPI_MESSAGEIDLENGTH)
	{
		CopyMemory(m_sHeader.nMessageLength, &nLength, sizeof(m_sHeader.nMessageLength));
		return TRUE;
	}
	return FALSE;
}

UINT CTCProcessInterfaceMessageHeader::GetMessageLength() CONST
{
	UINT  nLength;

	CopyMemory(&(nLength = 0), m_sHeader.nMessageLength, sizeof(m_sHeader.nMessageLength));
	return nLength;
}

BOOL CTCProcessInterfaceMessageHeader::SetVersion(UINT nVersion)
{
	if (nVersion == TCPI_VERSION)
	{
		m_sHeader.nVersion = nVersion;
		return TRUE;
	}
	return FALSE;
}

UINT CTCProcessInterfaceMessageHeader::GetVersion() CONST
{
	return m_sHeader.nVersion;
}

BOOL CTCProcessInterfaceMessageHeader::Map(CByteArray &nInfo) CONST
{
	for (nInfo.SetSize(max(nInfo.GetSize(), sizeof(TCPIMESSAGEHEADER))); nInfo.GetSize() >= sizeof(TCPIMESSAGEHEADER); )
	{
		CopyMemory(nInfo.GetData(), &m_sHeader, sizeof(TCPIMESSAGEHEADER));
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceMessageHeader::Unmap(CONST CByteArray &nInfo)
{
	if (nInfo.GetSize() >= sizeof(TCPIMESSAGEHEADER))
	{
		CopyMemory(&m_sHeader, nInfo.GetData(), sizeof(TCPIMESSAGEHEADER));
		return TRUE;
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceAnnounceCommandHandlerRequest

CTCProcessInterfaceAnnounceCommandHandlerRequest::CTCProcessInterfaceAnnounceCommandHandlerRequest() : CTCProcessInterfaceMessageHeader(TCPI_ANNOUNCECOMMANDHANDLERREQUEST, sizeof(TCPIMESSAGEHEADER) - TCPI_MESSAGEIDLENGTH)
{
	m_bExclusive = TRUE;
}

BOOL CTCProcessInterfaceAnnounceCommandHandlerRequest::SetCommandHandler(LPCTSTR pszCommandHandler, BOOL bExclusive)
{
	for (m_szCommandHandler = pszCommandHandler, m_bExclusive = bExclusive; TRUE; )
	{
		SetMessageLength(sizeof(TCPIANNOUNCECOMMANDHANDLERREQUEST) - TCPI_MESSAGEIDLENGTH + (m_szCommandHandler.GetLength() + 1)*sizeof(TCHAR));
		break;
	}
	return((lstrlen(pszCommandHandler) > 0) ? TRUE : FALSE);
}

CString CTCProcessInterfaceAnnounceCommandHandlerRequest::GetCommandHandler() CONST
{
	return m_szCommandHandler;
}

BOOL CTCProcessInterfaceAnnounceCommandHandlerRequest::IsExclusiveCommandHandler() CONST
{
	return m_bExclusive;
}

BOOL CTCProcessInterfaceAnnounceCommandHandlerRequest::Map(CByteArray &nInfo) CONST
{
	TCPIANNOUNCECOMMANDHANDLERREQUEST  sData;

	for (CopyMemory(&sData.sHeader, &m_sHeader, sizeof(sData.sHeader)), sData.cbCommandHandler = (m_szCommandHandler.GetLength() + 1)*sizeof(TCHAR), sData.bExclusive = m_bExclusive, nInfo.SetSize(sizeof(TCPIANNOUNCECOMMANDHANDLERREQUEST) + sData.cbCommandHandler); nInfo.GetSize() == sizeof(TCPIANNOUNCECOMMANDHANDLERREQUEST) + sData.cbCommandHandler; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(TCPIANNOUNCECOMMANDHANDLERREQUEST));
		CopyMemory(nInfo.GetData() + sizeof(TCPIANNOUNCECOMMANDHANDLERREQUEST), (LPCTSTR)m_szCommandHandler, sData.cbCommandHandler);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceAnnounceCommandHandlerRequest::Unmap(CONST CByteArray &nInfo)
{
	TCPIANNOUNCECOMMANDHANDLERREQUEST  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(TCPIANNOUNCECOMMANDHANDLERREQUEST)) ? sizeof(TCPIANNOUNCECOMMANDHANDLERREQUEST) : 0); nInfo.GetSize() == sizeof(TCPIANNOUNCECOMMANDHANDLERREQUEST) + sData.cbCommandHandler && sData.cbCommandHandler > 0; )
	{
		for (CopyMemory(&m_sHeader, &sData.sHeader, sizeof(TCPIMESSAGEHEADER)), CopyMemory(m_szCommandHandler.GetBufferSetLength(STRINGCHARS(sData.cbCommandHandler)), nInfo.GetData() + sizeof(TCPIANNOUNCECOMMANDHANDLERREQUEST), STRINGBYTES(sData.cbCommandHandler)), m_bExclusive = sData.bExclusive, m_szCommandHandler.ReleaseBuffer(); Check(sData.cbCommandHandler); ) return TRUE;
		break;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceAnnounceCommandHandlerRequest::Check(INT cbData) CONST
{
	return((GetMessageID() == TCPI_ANNOUNCECOMMANDHANDLERREQUEST  &&  GetMessageLength() == sizeof(TCPIANNOUNCECOMMANDHANDLERREQUEST) - TCPI_MESSAGEIDLENGTH + cbData  &&  GetVersion() == TCPI_VERSION) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceAnnounceCommandHandlerResponse

CTCProcessInterfaceAnnounceCommandHandlerResponse::CTCProcessInterfaceAnnounceCommandHandlerResponse() : CTCProcessInterfaceMessageHeader(TCPI_ANNOUNCECOMMANDHANDLERRESPONSE, sizeof(TCPIMESSAGEHEADER) - TCPI_MESSAGEIDLENGTH)
{
	m_bExclusive = TRUE;
}

BOOL CTCProcessInterfaceAnnounceCommandHandlerResponse::SetCommandHandler(LPCTSTR pszCommandHandler, BOOL bExclusive)
{
	for (m_szCommandHandler = pszCommandHandler, m_bExclusive = bExclusive; TRUE; )
	{
		SetMessageLength(sizeof(TCPIANNOUNCECOMMANDHANDLERRESPONSE) - TCPI_MESSAGEIDLENGTH + (m_szCommandHandler.GetLength() + 1)*sizeof(TCHAR));
		break;
	}
	return((lstrlen(pszCommandHandler) > 0) ? TRUE : FALSE);
}

CString CTCProcessInterfaceAnnounceCommandHandlerResponse::GetCommandHandler() CONST
{
	return m_szCommandHandler;
}

BOOL CTCProcessInterfaceAnnounceCommandHandlerResponse::IsExclusiveCommandHandler() CONST
{
	return m_bExclusive;
}

BOOL CTCProcessInterfaceAnnounceCommandHandlerResponse::Map(CByteArray &nInfo) CONST
{
	TCPIANNOUNCECOMMANDHANDLERRESPONSE  sData;

	for (CopyMemory(&sData.sHeader, &m_sHeader, sizeof(sData.sHeader)), sData.cbCommandHandler = (m_szCommandHandler.GetLength() + 1)*sizeof(TCHAR), sData.bExclusive = m_bExclusive, nInfo.SetSize(sizeof(TCPIANNOUNCECOMMANDHANDLERRESPONSE) + sData.cbCommandHandler); nInfo.GetSize() == sizeof(TCPIANNOUNCECOMMANDHANDLERRESPONSE) + sData.cbCommandHandler; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(TCPIANNOUNCECOMMANDHANDLERRESPONSE));
		CopyMemory(nInfo.GetData() + sizeof(TCPIANNOUNCECOMMANDHANDLERRESPONSE), (LPCTSTR)m_szCommandHandler, sData.cbCommandHandler);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceAnnounceCommandHandlerResponse::Unmap(CONST CByteArray &nInfo)
{
	TCPIANNOUNCECOMMANDHANDLERRESPONSE  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(TCPIANNOUNCECOMMANDHANDLERRESPONSE)) ? sizeof(TCPIANNOUNCECOMMANDHANDLERRESPONSE) : 0); nInfo.GetSize() == sizeof(TCPIANNOUNCECOMMANDHANDLERRESPONSE) + sData.cbCommandHandler && sData.cbCommandHandler > 0; )
	{
		for (CopyMemory(&m_sHeader, &sData.sHeader, sizeof(TCPIMESSAGEHEADER)), CopyMemory(m_szCommandHandler.GetBufferSetLength(STRINGCHARS(sData.cbCommandHandler)), nInfo.GetData() + sizeof(TCPIANNOUNCECOMMANDHANDLERRESPONSE), STRINGBYTES(sData.cbCommandHandler)), m_bExclusive = sData.bExclusive, m_szCommandHandler.ReleaseBuffer(); Check(sData.cbCommandHandler); ) return TRUE;
		break;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceAnnounceCommandHandlerResponse::Check(INT cbData) CONST
{
	return((GetMessageID() == TCPI_ANNOUNCECOMMANDHANDLERRESPONSE  &&  GetMessageLength() == sizeof(TCPIANNOUNCECOMMANDHANDLERRESPONSE) - TCPI_MESSAGEIDLENGTH + cbData  &&  GetVersion() == TCPI_VERSION) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceSetCommandHandlerConfigurationRequest

CTCProcessInterfaceSetCommandHandlerConfigurationRequest::CTCProcessInterfaceSetCommandHandlerConfigurationRequest() : CTCProcessInterfaceMessageHeader(TCPI_SETCOMMANDHANDLERCONFIGURATIONREQUEST, sizeof(TCPIMESSAGEHEADER) - TCPI_MESSAGEIDLENGTH)
{
	m_nTelecommandingMode = 0;
	m_nTelecommandingState = 0;
	m_nTelecommandingFlags = 0;
	m_bTelecommandingInterlockMode = FALSE;
	m_bTelecommandingReleaseWaitMode = FALSE;
	m_bTelecommandingAutoRejectionMode = FALSE;
	m_tVerificationUncertaintyTimeWindow = 0;
	m_tMaximumExecutionTimePeriod = 0;
	m_tMaximumTimeCheckPeriod = 0;
	m_tDefaultReleaseTimeWindow = 0;
	m_bUpdate = FALSE;
}

BOOL CTCProcessInterfaceSetCommandHandlerConfigurationRequest::SetConfiguration(CONST CTCProcessCommandSources &pCommandSources, UINT nTelecommandingMode, UINT nTelecommandingState, UINT nTelecommandingFlags, BOOL bTelecommandingInterlockMode, BOOL bTelecommandingReleaseWaitMode, BOOL bTelecommandingAutoRejectionMode, CONST CTimeSpan &tVerificationUncertaintyTimeWindow, CONST CTimeSpan &tMaximumExecutionTimePeriod, CONST CTimeSpan &tMaximumTimeCheckPeriod, CONST CTimeSpan &tDefaultReleaseTimeWindow, CONST CHistoryStoreFiles &pHistoryArchivalFiles, CONST CHistoryStoreFiles &pHistoryRetrievalFiles, LPCTSTR pszDefaultHistoryFileName)
{
	CByteArray  nCommandSourcesData;
	CByteArray  nHistoryFilesData[2];

	m_nTelecommandingMode = nTelecommandingMode;
	m_nTelecommandingState = nTelecommandingState;
	m_nTelecommandingFlags = nTelecommandingFlags;
	m_bTelecommandingInterlockMode = bTelecommandingInterlockMode;
	m_bTelecommandingReleaseWaitMode = bTelecommandingReleaseWaitMode;
	m_bTelecommandingAutoRejectionMode = bTelecommandingAutoRejectionMode;
	m_tMaximumTimeCheckPeriod = tMaximumTimeCheckPeriod.GetTotalSeconds();
	m_tMaximumExecutionTimePeriod = tMaximumExecutionTimePeriod.GetTotalSeconds();
	m_tDefaultReleaseTimeWindow = tDefaultReleaseTimeWindow.GetTotalSeconds();
	m_tVerificationUncertaintyTimeWindow = tVerificationUncertaintyTimeWindow.GetTotalSeconds();
	m_szDefaultHistoryFileName = pszDefaultHistoryFileName;
	return((m_pCommandSources.Copy(&pCommandSources) && m_pHistoryFiles[0].Copy(&pHistoryArchivalFiles) && m_pHistoryFiles[1].Copy(&pHistoryRetrievalFiles) && m_pCommandSources.Map(nCommandSourcesData) && m_pHistoryFiles[0].Map(nHistoryFilesData[0]) && m_pHistoryFiles[1].Map(nHistoryFilesData[1])) ? SetMessageLength(sizeof(TCPISETCOMMANDHANDLERCONFIGURATIONREQUEST) - TCPI_MESSAGEIDLENGTH + (UINT)nCommandSourcesData.GetSize() + (UINT)nHistoryFilesData[0].GetSize() + (UINT)nHistoryFilesData[1].GetSize() + (m_szDefaultHistoryFileName.GetLength() + 1)*sizeof(TCHAR)) : FALSE);
}

BOOL CTCProcessInterfaceSetCommandHandlerConfigurationRequest::GetConfiguration(CTCProcessCommandSources &pCommandSources, UINT &nTelecommandingMode, UINT &nTelecommandingState, UINT &nTelecommandingFlags, BOOL &bTelecommandingInterlockMode, BOOL &bTelecommandingReleaseWaitMode, BOOL &bTelecommandingAutoRejectionMode, CTimeSpan &tVerificationUncertaintyTimeWindow, CTimeSpan &tMaximumExecutionTimePeriod, CTimeSpan &tMaximumTimeCheckPeriod, CTimeSpan &tDefaultReleaseTimeWindow, CHistoryStoreFiles &pHistoryArchivalFiles, CHistoryStoreFiles &pHistoryRetrievalFiles, CString &szDefaultHistoryFileName) CONST
{
	nTelecommandingMode = m_nTelecommandingMode;
	nTelecommandingState = m_nTelecommandingState;
	nTelecommandingFlags = m_nTelecommandingFlags;
	bTelecommandingInterlockMode = m_bTelecommandingInterlockMode;
	bTelecommandingReleaseWaitMode = m_bTelecommandingReleaseWaitMode;
	bTelecommandingAutoRejectionMode = m_bTelecommandingAutoRejectionMode;
	tMaximumTimeCheckPeriod = m_tMaximumTimeCheckPeriod.GetTotalSeconds();
	tMaximumExecutionTimePeriod = m_tMaximumExecutionTimePeriod.GetTotalSeconds();
	tDefaultReleaseTimeWindow = m_tDefaultReleaseTimeWindow.GetTotalSeconds();
	tVerificationUncertaintyTimeWindow = m_tVerificationUncertaintyTimeWindow.GetTotalSeconds();
	szDefaultHistoryFileName = m_szDefaultHistoryFileName;
	return((pCommandSources.Copy(&m_pCommandSources) && pHistoryArchivalFiles.Copy(&m_pHistoryFiles[0]) && pHistoryRetrievalFiles.Copy(&m_pHistoryFiles[1])) ? TRUE : FALSE);
}

BOOL CTCProcessInterfaceSetCommandHandlerConfigurationRequest::EnableUpdateFlag(BOOL bEnable)
{
	m_bUpdate = bEnable;
	return TRUE;
}

BOOL CTCProcessInterfaceSetCommandHandlerConfigurationRequest::IsUpdateFlagEnabled() CONST
{
	return m_bUpdate;
}

BOOL CTCProcessInterfaceSetCommandHandlerConfigurationRequest::Reset()
{
	for (m_pCommandSources.RemoveAll(), m_nTelecommandingMode = 0, m_nTelecommandingState = 0, m_nTelecommandingFlags = 0, m_bTelecommandingInterlockMode = FALSE, m_bTelecommandingReleaseWaitMode = FALSE, m_bTelecommandingAutoRejectionMode = FALSE, m_tVerificationUncertaintyTimeWindow = 0, m_tMaximumExecutionTimePeriod = 0, m_tMaximumTimeCheckPeriod = 0, m_tDefaultReleaseTimeWindow = 0, m_pHistoryFiles[0].RemoveAll(), m_pHistoryFiles[1].RemoveAll(), m_szDefaultHistoryFileName.Empty(), m_bUpdate = FALSE; SetMessageLength(sizeof(TCPISETCOMMANDHANDLERCONFIGURATIONREQUEST) - TCPI_MESSAGEIDLENGTH); ) return TRUE;
	return FALSE;
}

BOOL CTCProcessInterfaceSetCommandHandlerConfigurationRequest::Map(CByteArray &nInfo) CONST
{
	INT  cbData;
	CByteArray  nCommandSourcesData;
	CByteArray  nHistoryFilesData[2];
	TCPISETCOMMANDHANDLERCONFIGURATIONREQUEST  sData;

	for (CopyMemory(&sData.sHeader, &m_sHeader, sizeof(sData.sHeader)), sData.cbCommandSources = (m_pCommandSources.Map(nCommandSourcesData)) ? (INT)nCommandSourcesData.GetSize() : -1, sData.cbHistoryFiles[0] = (m_pHistoryFiles[0].Map(nHistoryFilesData[0])) ? (INT)nHistoryFilesData[0].GetSize() : -1, sData.cbHistoryFiles[1] = (m_pHistoryFiles[1].Map(nHistoryFilesData[1])) ? (INT)nHistoryFilesData[1].GetSize() : -1, sData.cbDefaultHistoryFileName = (m_szDefaultHistoryFileName.GetLength() + 1)*sizeof(TCHAR), sData.nTelecommandingMode = m_nTelecommandingMode, sData.nTelecommandingState = m_nTelecommandingState, sData.nTelecommandingFlags = m_nTelecommandingFlags, sData.bTelecommandingInterlockMode = m_bTelecommandingInterlockMode, sData.bTelecommandingReleaseWaitMode = m_bTelecommandingReleaseWaitMode, sData.bTelecommandingAutoRejectionMode = m_bTelecommandingAutoRejectionMode, sData.tVerificationUncertaintyTimeWindow = m_tVerificationUncertaintyTimeWindow.GetTotalSeconds(), sData.tMaximumExecutionTimePeriod = m_tMaximumExecutionTimePeriod.GetTotalSeconds(), sData.tMaximumTimeCheckPeriod = m_tMaximumTimeCheckPeriod.GetTotalSeconds(), sData.tDefaultReleaseTimeWindow = m_tDefaultReleaseTimeWindow.GetTotalSeconds(), sData.bUpdate = m_bUpdate, nInfo.SetSize(sizeof(TCPISETCOMMANDHANDLERCONFIGURATIONREQUEST) + max(sData.cbCommandSources, 0) + max(sData.cbHistoryFiles[0], 0) + max(sData.cbHistoryFiles[1], 0) + sData.cbDefaultHistoryFileName); nInfo.GetSize() == sizeof(TCPISETCOMMANDHANDLERCONFIGURATIONREQUEST) + sData.cbCommandSources + sData.cbHistoryFiles[0] + sData.cbHistoryFiles[1] + sData.cbDefaultHistoryFileName; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(TCPISETCOMMANDHANDLERCONFIGURATIONREQUEST));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(TCPISETCOMMANDHANDLERCONFIGURATIONREQUEST)), nCommandSourcesData.GetData(), sData.cbCommandSources);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbCommandSources), nHistoryFilesData[0].GetData(), sData.cbHistoryFiles[0]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbHistoryFiles[0]), nHistoryFilesData[1].GetData(), sData.cbHistoryFiles[1]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbHistoryFiles[1]), (LPCTSTR)m_szDefaultHistoryFileName, sData.cbDefaultHistoryFileName);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceSetCommandHandlerConfigurationRequest::Unmap(CONST CByteArray &nInfo)
{
	INT  cbData;
	CByteArray  nCommandSourcesData;
	CByteArray  nHistoryFilesData[2];
	TCPISETCOMMANDHANDLERCONFIGURATIONREQUEST  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(TCPISETCOMMANDHANDLERCONFIGURATIONREQUEST)) ? sizeof(TCPISETCOMMANDHANDLERCONFIGURATIONREQUEST) : 0); nInfo.GetSize() == sizeof(TCPISETCOMMANDHANDLERCONFIGURATIONREQUEST) + sData.cbCommandSources + sData.cbHistoryFiles[0] + sData.cbHistoryFiles[1] + sData.cbDefaultHistoryFileName && sData.cbCommandSources >= 0 && sData.cbHistoryFiles[0] >= 0 && sData.cbHistoryFiles[1] >= 0 && sData.cbDefaultHistoryFileName > 0; )
	{
		for (CopyMemory(&m_sHeader, &sData.sHeader, sizeof(TCPIMESSAGEHEADER)), nCommandSourcesData.SetSize(sData.cbCommandSources), nHistoryFilesData[0].SetSize(sData.cbHistoryFiles[0]), nHistoryFilesData[1].SetSize(sData.cbHistoryFiles[1]), CopyMemory(nCommandSourcesData.GetData(), nInfo.GetData() + (cbData = sizeof(TCPISETCOMMANDHANDLERCONFIGURATIONREQUEST)), sData.cbCommandSources), CopyMemory(nHistoryFilesData[0].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbCommandSources), sData.cbHistoryFiles[0]), CopyMemory(nHistoryFilesData[1].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbHistoryFiles[0]), sData.cbHistoryFiles[1]), CopyMemory(m_szDefaultHistoryFileName.GetBufferSetLength(STRINGCHARS(sData.cbDefaultHistoryFileName)), nInfo.GetData() + (cbData = cbData + sData.cbHistoryFiles[1]), STRINGBYTES(sData.cbDefaultHistoryFileName)), m_nTelecommandingMode = sData.nTelecommandingMode, m_nTelecommandingState = sData.nTelecommandingState, m_nTelecommandingFlags = sData.nTelecommandingFlags, m_bTelecommandingInterlockMode = sData.bTelecommandingInterlockMode, m_bTelecommandingReleaseWaitMode = sData.bTelecommandingReleaseWaitMode, m_bTelecommandingAutoRejectionMode = sData.bTelecommandingAutoRejectionMode, m_tVerificationUncertaintyTimeWindow = sData.tVerificationUncertaintyTimeWindow, m_tMaximumExecutionTimePeriod = sData.tMaximumExecutionTimePeriod, m_tMaximumTimeCheckPeriod = sData.tMaximumTimeCheckPeriod, m_tDefaultReleaseTimeWindow = sData.tDefaultReleaseTimeWindow, m_szDefaultHistoryFileName.ReleaseBuffer(), m_bUpdate = sData.bUpdate; m_pCommandSources.Unmap(nCommandSourcesData) && m_pHistoryFiles[0].Unmap(nHistoryFilesData[0]) && m_pHistoryFiles[1].Unmap(nHistoryFilesData[1]); ) return Check(sData.cbCommandSources + sData.cbHistoryFiles[0] + sData.cbHistoryFiles[1] + sData.cbDefaultHistoryFileName);
		break;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceSetCommandHandlerConfigurationRequest::Check(INT cbData) CONST
{
	return((GetMessageID() == TCPI_SETCOMMANDHANDLERCONFIGURATIONREQUEST  &&  GetMessageLength() == sizeof(TCPISETCOMMANDHANDLERCONFIGURATIONREQUEST) - TCPI_MESSAGEIDLENGTH + cbData  &&  GetVersion() == TCPI_VERSION) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceSetCommandHandlerConfigurationResponse

CTCProcessInterfaceSetCommandHandlerConfigurationResponse::CTCProcessInterfaceSetCommandHandlerConfigurationResponse() : CTCProcessInterfaceMessageHeader(TCPI_SETCOMMANDHANDLERCONFIGURATIONRESPONSE, sizeof(TCPISETCOMMANDHANDLERCONFIGURATIONRESPONSE) - TCPI_MESSAGEIDLENGTH)
{
	m_bResult = FALSE;
}

BOOL CTCProcessInterfaceSetCommandHandlerConfigurationResponse::SetResult(BOOL bSuccess)
{
	m_bResult = bSuccess;
	return TRUE;
}

BOOL CTCProcessInterfaceSetCommandHandlerConfigurationResponse::GetResult() CONST
{
	return m_bResult;
}

BOOL CTCProcessInterfaceSetCommandHandlerConfigurationResponse::Map(CByteArray &nInfo) CONST
{
	TCPISETCOMMANDHANDLERCONFIGURATIONRESPONSE  sData;

	for (CopyMemory(&sData.sHeader, &m_sHeader, sizeof(sData.sHeader)), sData.bResult = m_bResult, nInfo.SetSize(sizeof(TCPISETCOMMANDHANDLERCONFIGURATIONRESPONSE)); nInfo.GetSize() == sizeof(TCPISETCOMMANDHANDLERCONFIGURATIONRESPONSE); )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(TCPISETCOMMANDHANDLERCONFIGURATIONRESPONSE));
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceSetCommandHandlerConfigurationResponse::Unmap(CONST CByteArray &nInfo)
{
	TCPISETCOMMANDHANDLERCONFIGURATIONRESPONSE  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(TCPISETCOMMANDHANDLERCONFIGURATIONRESPONSE)) ? sizeof(TCPISETCOMMANDHANDLERCONFIGURATIONRESPONSE) : 0); nInfo.GetSize() == sizeof(TCPISETCOMMANDHANDLERCONFIGURATIONRESPONSE); )
	{
		CopyMemory(&m_sHeader, &sData.sHeader, sizeof(TCPIMESSAGEHEADER));
		m_bResult = sData.bResult;
		return Check();
	}
	return FALSE;
}

BOOL CTCProcessInterfaceSetCommandHandlerConfigurationResponse::Check() CONST
{
	return((GetMessageID() == TCPI_SETCOMMANDHANDLERCONFIGURATIONRESPONSE  &&  GetMessageLength() == sizeof(TCPISETCOMMANDHANDLERCONFIGURATIONRESPONSE) - TCPI_MESSAGEIDLENGTH  &&  GetVersion() == TCPI_VERSION) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceGetCommandHandlerConfigurationRequest

CTCProcessInterfaceGetCommandHandlerConfigurationRequest::CTCProcessInterfaceGetCommandHandlerConfigurationRequest() : CTCProcessInterfaceMessageHeader(TCPI_GETCOMMANDHANDLERCONFIGURATIONREQUEST, sizeof(TCPIGETCOMMANDHANDLERCONFIGURATIONREQUEST) - TCPI_MESSAGEIDLENGTH)
{
	m_bUpdate = FALSE;
}

BOOL CTCProcessInterfaceGetCommandHandlerConfigurationRequest::EnableUpdateFlag(BOOL bEnable)
{
	m_bUpdate = bEnable;
	return TRUE;
}

BOOL CTCProcessInterfaceGetCommandHandlerConfigurationRequest::IsUpdateFlagEnabled() CONST
{
	return m_bUpdate;
}

BOOL CTCProcessInterfaceGetCommandHandlerConfigurationRequest::Reset()
{
	m_bUpdate = FALSE;
	return TRUE;
}

BOOL CTCProcessInterfaceGetCommandHandlerConfigurationRequest::Map(CByteArray &nInfo) CONST
{
	TCPIGETCOMMANDHANDLERCONFIGURATIONREQUEST  sData;

	for (CopyMemory(&sData.sHeader, &m_sHeader, sizeof(sData.sHeader)), sData.bUpdate = m_bUpdate, nInfo.SetSize(sizeof(TCPIGETCOMMANDHANDLERCONFIGURATIONREQUEST)); nInfo.GetSize() == sizeof(TCPIGETCOMMANDHANDLERCONFIGURATIONREQUEST); )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(TCPIGETCOMMANDHANDLERCONFIGURATIONREQUEST));
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceGetCommandHandlerConfigurationRequest::Unmap(CONST CByteArray &nInfo)
{
	TCPIGETCOMMANDHANDLERCONFIGURATIONREQUEST  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(TCPIGETCOMMANDHANDLERCONFIGURATIONREQUEST)) ? sizeof(TCPIGETCOMMANDHANDLERCONFIGURATIONREQUEST) : 0); nInfo.GetSize() == sizeof(TCPIGETCOMMANDHANDLERCONFIGURATIONREQUEST); )
	{
		CopyMemory(&m_sHeader, &sData.sHeader, sizeof(TCPIMESSAGEHEADER));
		m_bUpdate = sData.bUpdate;
		return Check();
	}
	return FALSE;
}

BOOL CTCProcessInterfaceGetCommandHandlerConfigurationRequest::Check() CONST
{
	return((GetMessageID() == TCPI_GETCOMMANDHANDLERCONFIGURATIONREQUEST  &&  GetMessageLength() == sizeof(TCPIGETCOMMANDHANDLERCONFIGURATIONREQUEST) - TCPI_MESSAGEIDLENGTH  &&  GetVersion() == TCPI_VERSION) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceGetCommandHandlerConfigurationResponse

CTCProcessInterfaceGetCommandHandlerConfigurationResponse::CTCProcessInterfaceGetCommandHandlerConfigurationResponse() : CTCProcessInterfaceMessageHeader(TCPI_GETCOMMANDHANDLERCONFIGURATIONRESPONSE, sizeof(TCPIMESSAGEHEADER) - TCPI_MESSAGEIDLENGTH)
{
	m_nTelecommandingMode = 0;
	m_nTelecommandingState = 0;
	m_nTelecommandingFlags = 0;
	m_bTelecommandingInterlockMode = FALSE;
	m_bTelecommandingReleaseWaitMode = FALSE;
	m_bTelecommandingAutoRejectionMode = FALSE;
	m_tVerificationUncertaintyTimeWindow = 0;
	m_tMaximumExecutionTimePeriod = 0;
	m_tMaximumTimeCheckPeriod = 0;
	m_tDefaultReleaseTimeWindow = 0;
	m_bUpdate = FALSE;
}

BOOL CTCProcessInterfaceGetCommandHandlerConfigurationResponse::SetConfiguration(CONST CTCProcessCommandSources &pCommandSources, UINT nTelecommandingMode, UINT nTelecommandingState, UINT nTelecommandingFlags, BOOL bTelecommandingInterlockMode, BOOL bTelecommandingReleaseWaitMode, BOOL bTelecommandingAutoRejectionMode, CONST CTimeSpan &tVerificationUncertaintyTimeWindow, CONST CTimeSpan &tMaximumExecutionTimePeriod, CONST CTimeSpan &tMaximumTimeCheckPeriod, CONST CTimeSpan &tDefaultReleaseTimeWindow, CONST CTCItems &pItems, CONST CTCInterlocks &pInterlocks, CONST CHistoryStoreFiles &pHistoryArchivalFiles, CONST CHistoryStoreFiles &pHistoryRetrievalFiles, LPCTSTR pszDefaultHistoryFileName)
{
	CByteArray  nItemsData;
	CByteArray  nInterlocksData;
	CByteArray  nCommandSourcesData;
	CByteArray  nHistoryFilesData[2];

	m_nTelecommandingMode = nTelecommandingMode;
	m_nTelecommandingState = nTelecommandingState;
	m_nTelecommandingFlags = nTelecommandingFlags;
	m_bTelecommandingInterlockMode = bTelecommandingInterlockMode;
	m_bTelecommandingReleaseWaitMode = bTelecommandingReleaseWaitMode;
	m_bTelecommandingAutoRejectionMode = bTelecommandingAutoRejectionMode;
	m_tMaximumTimeCheckPeriod = tMaximumTimeCheckPeriod.GetTotalSeconds();
	m_tMaximumExecutionTimePeriod = tMaximumExecutionTimePeriod.GetTotalSeconds();
	m_tDefaultReleaseTimeWindow = tDefaultReleaseTimeWindow.GetTotalSeconds();
	m_tVerificationUncertaintyTimeWindow = tVerificationUncertaintyTimeWindow.GetTotalSeconds();
	m_szDefaultHistoryFileName = pszDefaultHistoryFileName;
	return((m_pCommandSources.Copy(&pCommandSources) && m_pItems.Copy(&pItems) && m_pInterlocks.Copy(&pInterlocks) && m_pHistoryFiles[0].Copy(&pHistoryArchivalFiles) && m_pHistoryFiles[1].Copy(&pHistoryRetrievalFiles) && m_pCommandSources.Map(nCommandSourcesData) && m_pItems.Map(nItemsData, TRUE) && m_pInterlocks.Map(nInterlocksData) && m_pHistoryFiles[0].Map(nHistoryFilesData[0]) && m_pHistoryFiles[1].Map(nHistoryFilesData[1])) ? SetMessageLength(sizeof(TCPIGETCOMMANDHANDLERCONFIGURATIONRESPONSE) - TCPI_MESSAGEIDLENGTH + (UINT)nCommandSourcesData.GetSize() + (UINT)nItemsData.GetSize() + (UINT)nInterlocksData.GetSize() + (UINT)nHistoryFilesData[0].GetSize() + (UINT)nHistoryFilesData[1].GetSize() + (m_szDefaultHistoryFileName.GetLength() + 1)*sizeof(TCHAR)) : FALSE);
}

BOOL CTCProcessInterfaceGetCommandHandlerConfigurationResponse::GetConfiguration(CTCProcessCommandSources &pCommandSources, UINT &nTelecommandingMode, UINT &nTelecommandingState, UINT &nTelecommandingFlags, BOOL &bTelecommandingInterlockMode, BOOL &bTelecommandingReleaseWaitMode, BOOL &bTelecommandingAutoRejectionMode, CTimeSpan &tVerificationUncertaintyTimeWindow, CTimeSpan &tMaximumExecutionTimePeriod, CTimeSpan &tMaximumTimeCheckPeriod, CTimeSpan &tDefaultReleaseTimeWindow, CTCItems &pItems, CTCInterlocks &pInterlocks, CHistoryStoreFiles &pHistoryArchivalFiles, CHistoryStoreFiles &pHistoryRetrievalFiles, CString &szDefaultHistoryFileName) CONST
{
	nTelecommandingMode = m_nTelecommandingMode;
	nTelecommandingState = m_nTelecommandingState;
	nTelecommandingFlags = m_nTelecommandingFlags;
	bTelecommandingInterlockMode = m_bTelecommandingInterlockMode;
	bTelecommandingReleaseWaitMode = m_bTelecommandingReleaseWaitMode;
	bTelecommandingAutoRejectionMode = m_bTelecommandingAutoRejectionMode;
	tMaximumTimeCheckPeriod = m_tMaximumTimeCheckPeriod.GetTotalSeconds();
	tMaximumExecutionTimePeriod = m_tMaximumExecutionTimePeriod.GetTotalSeconds();
	tDefaultReleaseTimeWindow = m_tDefaultReleaseTimeWindow.GetTotalSeconds();
	tVerificationUncertaintyTimeWindow = m_tVerificationUncertaintyTimeWindow.GetTotalSeconds();
	szDefaultHistoryFileName = m_szDefaultHistoryFileName;
	return((pCommandSources.Copy(&m_pCommandSources) && pItems.Copy(&m_pItems) && pInterlocks.Copy(&m_pInterlocks) && pHistoryArchivalFiles.Copy(&m_pHistoryFiles[0]) && pHistoryRetrievalFiles.Copy(&m_pHistoryFiles[1])) ? TRUE : FALSE);
}

BOOL CTCProcessInterfaceGetCommandHandlerConfigurationResponse::EnableUpdateFlag(BOOL bEnable)
{
	m_bUpdate = bEnable;
	return TRUE;
}

BOOL CTCProcessInterfaceGetCommandHandlerConfigurationResponse::IsUpdateFlagEnabled() CONST
{
	return m_bUpdate;
}

BOOL CTCProcessInterfaceGetCommandHandlerConfigurationResponse::Map(CByteArray &nInfo) CONST
{
	INT  cbData;
	CByteArray  nItemsData;
	CByteArray  nInterlocksData;
	CByteArray  nCommandSourcesData;
	CByteArray  nHistoryFilesData[2];
	TCPIGETCOMMANDHANDLERCONFIGURATIONRESPONSE  sData;

	for (CopyMemory(&sData.sHeader, &m_sHeader, sizeof(sData.sHeader)), sData.cbCommandSources = (m_pCommandSources.Map(nCommandSourcesData)) ? (INT)nCommandSourcesData.GetSize() : -1, sData.cbItems = (m_pItems.Map(nItemsData, TRUE)) ? (INT)nItemsData.GetSize() : -1, sData.cbInterlocks = (m_pInterlocks.Map(nInterlocksData)) ? (INT)nInterlocksData.GetSize() : -1, sData.cbHistoryFiles[0] = (m_pHistoryFiles[0].Map(nHistoryFilesData[0])) ? (INT)nHistoryFilesData[0].GetSize() : -1, sData.cbHistoryFiles[1] = (m_pHistoryFiles[1].Map(nHistoryFilesData[1])) ? (INT)nHistoryFilesData[1].GetSize() : -1, sData.cbDefaultHistoryFileName = (m_szDefaultHistoryFileName.GetLength() + 1)*sizeof(TCHAR), sData.nTelecommandingMode = m_nTelecommandingMode, sData.nTelecommandingState = m_nTelecommandingState, sData.nTelecommandingFlags = m_nTelecommandingFlags, sData.bTelecommandingInterlockMode = m_bTelecommandingInterlockMode, sData.bTelecommandingReleaseWaitMode = m_bTelecommandingReleaseWaitMode, sData.bTelecommandingAutoRejectionMode = m_bTelecommandingAutoRejectionMode, sData.tVerificationUncertaintyTimeWindow = m_tVerificationUncertaintyTimeWindow.GetTotalSeconds(), sData.tMaximumExecutionTimePeriod = m_tMaximumExecutionTimePeriod.GetTotalSeconds(), sData.tMaximumTimeCheckPeriod = m_tMaximumTimeCheckPeriod.GetTotalSeconds(), sData.tDefaultReleaseTimeWindow = m_tDefaultReleaseTimeWindow.GetTotalSeconds(), sData.bUpdate = m_bUpdate, nInfo.SetSize(sizeof(TCPIGETCOMMANDHANDLERCONFIGURATIONRESPONSE) + max(sData.cbCommandSources, 0) + max(sData.cbItems, 0) + max(sData.cbInterlocks, 0) + max(sData.cbHistoryFiles[0], 0) + max(sData.cbHistoryFiles[1], 0) + sData.cbDefaultHistoryFileName); nInfo.GetSize() == sizeof(TCPIGETCOMMANDHANDLERCONFIGURATIONRESPONSE) + sData.cbCommandSources + sData.cbItems + sData.cbInterlocks + sData.cbHistoryFiles[0] + sData.cbHistoryFiles[1] + sData.cbDefaultHistoryFileName; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(TCPIGETCOMMANDHANDLERCONFIGURATIONRESPONSE));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(TCPIGETCOMMANDHANDLERCONFIGURATIONRESPONSE)), nCommandSourcesData.GetData(), sData.cbCommandSources);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbCommandSources), nItemsData.GetData(), sData.cbItems);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbItems), nInterlocksData.GetData(), sData.cbInterlocks);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbInterlocks), nHistoryFilesData[0].GetData(), sData.cbHistoryFiles[0]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbHistoryFiles[0]), nHistoryFilesData[1].GetData(), sData.cbHistoryFiles[1]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbHistoryFiles[1]), (LPCTSTR)m_szDefaultHistoryFileName, sData.cbDefaultHistoryFileName);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceGetCommandHandlerConfigurationResponse::Unmap(CONST CByteArray &nInfo)
{
	INT  cbData;
	CByteArray  nItemsData;
	CByteArray  nInterlocksData;
	CByteArray  nCommandSourcesData;
	CByteArray  nHistoryFilesData[2];
	TCPIGETCOMMANDHANDLERCONFIGURATIONRESPONSE  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(TCPIGETCOMMANDHANDLERCONFIGURATIONRESPONSE)) ? sizeof(TCPIGETCOMMANDHANDLERCONFIGURATIONRESPONSE) : 0); nInfo.GetSize() == sizeof(TCPIGETCOMMANDHANDLERCONFIGURATIONRESPONSE) + sData.cbCommandSources + sData.cbItems + sData.cbInterlocks + sData.cbHistoryFiles[0] + sData.cbHistoryFiles[1] + sData.cbDefaultHistoryFileName && sData.cbCommandSources >= 0 && sData.cbItems >= 0 && sData.cbInterlocks >= 0 && sData.cbHistoryFiles[0] >= 0 && sData.cbHistoryFiles[1] >= 0 && sData.cbDefaultHistoryFileName > 0; )
	{
		for (CopyMemory(&m_sHeader, &sData.sHeader, sizeof(TCPIMESSAGEHEADER)), nCommandSourcesData.SetSize(sData.cbCommandSources), nItemsData.SetSize(sData.cbItems), nInterlocksData.SetSize(sData.cbInterlocks), nHistoryFilesData[0].SetSize(sData.cbHistoryFiles[0]), nHistoryFilesData[1].SetSize(sData.cbHistoryFiles[1]), CopyMemory(nCommandSourcesData.GetData(), nInfo.GetData() + (cbData = sizeof(TCPIGETCOMMANDHANDLERCONFIGURATIONRESPONSE)), sData.cbCommandSources), CopyMemory(nItemsData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbCommandSources), sData.cbItems), CopyMemory(nInterlocksData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbItems), sData.cbInterlocks), CopyMemory(nHistoryFilesData[0].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbInterlocks), sData.cbHistoryFiles[0]), CopyMemory(nHistoryFilesData[1].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbHistoryFiles[0]), sData.cbHistoryFiles[1]), CopyMemory(m_szDefaultHistoryFileName.GetBufferSetLength(STRINGCHARS(sData.cbDefaultHistoryFileName)), nInfo.GetData() + (cbData = cbData + sData.cbHistoryFiles[1]), STRINGBYTES(sData.cbDefaultHistoryFileName)), m_nTelecommandingMode = sData.nTelecommandingMode, m_nTelecommandingState = sData.nTelecommandingState, m_nTelecommandingFlags = sData.nTelecommandingFlags, m_bTelecommandingInterlockMode = sData.bTelecommandingInterlockMode, m_bTelecommandingReleaseWaitMode = sData.bTelecommandingReleaseWaitMode, m_bTelecommandingAutoRejectionMode = sData.bTelecommandingAutoRejectionMode, m_tVerificationUncertaintyTimeWindow = sData.tVerificationUncertaintyTimeWindow, m_tMaximumExecutionTimePeriod = sData.tMaximumExecutionTimePeriod, m_tMaximumTimeCheckPeriod = sData.tMaximumTimeCheckPeriod, m_tDefaultReleaseTimeWindow = sData.tDefaultReleaseTimeWindow, m_szDefaultHistoryFileName.ReleaseBuffer(), m_bUpdate = sData.bUpdate; m_pCommandSources.Unmap(nCommandSourcesData) && m_pItems.Unmap(nItemsData, TRUE) && m_pInterlocks.Unmap(nInterlocksData) && m_pHistoryFiles[0].Unmap(nHistoryFilesData[0]) && m_pHistoryFiles[1].Unmap(nHistoryFilesData[1]); ) return Check(sData.cbCommandSources + sData.cbItems + sData.cbInterlocks + sData.cbHistoryFiles[0] + sData.cbHistoryFiles[1] + sData.cbDefaultHistoryFileName);
		break;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceGetCommandHandlerConfigurationResponse::Check(INT cbData) CONST
{
	return((GetMessageID() == TCPI_GETCOMMANDHANDLERCONFIGURATIONRESPONSE  &&  GetMessageLength() == sizeof(TCPIGETCOMMANDHANDLERCONFIGURATIONRESPONSE) - TCPI_MESSAGEIDLENGTH + cbData  &&  GetVersion() == TCPI_VERSION) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceRegisterCommandSourcesRequest

CTCProcessInterfaceRegisterCommandSourcesRequest::CTCProcessInterfaceRegisterCommandSourcesRequest() : CTCProcessInterfaceMessageHeader(TCPI_REGISTERCOMMANDSOURCESREQUEST, sizeof(TCPIMESSAGEHEADER) - TCPI_MESSAGEIDLENGTH)
{
	return;
}

BOOL CTCProcessInterfaceRegisterCommandSourcesRequest::SetCommandSources(CONST CTCProcessCommandSources &pCommandSources)
{
	CByteArray  nCommandSourcesData;

	if (m_pCommandSources.Copy(&pCommandSources) && m_pCommandSources.Map(nCommandSourcesData))
	{
		if (SetMessageLength(sizeof(TCPIREGISTERCOMMANDSOURCESREQUEST) - TCPI_MESSAGEIDLENGTH + (UINT)nCommandSourcesData.GetSize()))
		{
			m_pInterlocks.RemoveAll();
			m_pItems[0].RemoveAll();
			m_pItems[1].RemoveAll();
			m_pQueues.RemoveAll();
			return TRUE;
		}
	}
	return FALSE;
}
BOOL CTCProcessInterfaceRegisterCommandSourcesRequest::SetCommandSources(CONST CTCProcessCommandSources &pCommandSources, CONST CTCItems &pItems, CONST CTCItems &pHistoricalItems, CONST CTCInterlocks &pInterlocks, CONST CTCOnBoardBufferQueues &pQueues)
{
	CByteArray  nQueuesData;
	CByteArray  nItemsData[2];
	CByteArray  nInterlocksData;
	CByteArray  nCommandSourcesData;

	return((m_pCommandSources.Copy(&pCommandSources) && m_pItems[0].Copy(&pItems) && m_pItems[1].Copy(&pHistoricalItems) && m_pInterlocks.Copy(&pInterlocks) && m_pQueues.Copy(&pQueues) && m_pCommandSources.Map(nCommandSourcesData) && m_pItems[0].Map(nItemsData[0], TRUE) && m_pItems[1].Map(nItemsData[1], TRUE) && m_pInterlocks.Map(nInterlocksData) && m_pQueues.Map(nQueuesData)) ? SetMessageLength(sizeof(TCPIREGISTERCOMMANDSOURCESREQUEST) - TCPI_MESSAGEIDLENGTH + (UINT)nCommandSourcesData.GetSize() + (UINT)nItemsData[0].GetSize() + (UINT)nItemsData[1].GetSize() + (UINT)nInterlocksData.GetSize() + (UINT)nQueuesData.GetSize()) : FALSE);
}

BOOL CTCProcessInterfaceRegisterCommandSourcesRequest::GetCommandSources(CTCProcessCommandSources &pCommandSources) CONST
{
	return pCommandSources.Copy(&m_pCommandSources);
}
BOOL CTCProcessInterfaceRegisterCommandSourcesRequest::GetCommandSources(CTCProcessCommandSources &pCommandSources, CTCItems &pItems, CTCItems &pHistoricalItems, CTCInterlocks &pInterlocks, CTCOnBoardBufferQueues &pQueues) CONST
{
	return((pCommandSources.Copy(&m_pCommandSources) && pItems.Copy(&m_pItems[0]) && pHistoricalItems.Copy(&m_pItems[1]) && pInterlocks.Copy(&m_pInterlocks) && pQueues.Copy(&m_pQueues)) ? (pItems.GetSize() > 0 || pInterlocks.GetSize() > 0) : FALSE);
}

BOOL CTCProcessInterfaceRegisterCommandSourcesRequest::Reset()
{
	for (m_pCommandSources.RemoveAll(), m_pItems[0].RemoveAll(), m_pItems[1].RemoveAll(), m_pInterlocks.RemoveAll(), m_pQueues.RemoveAll(); SetMessageLength(sizeof(TCPIREGISTERCOMMANDSOURCESREQUEST) - TCPI_MESSAGEIDLENGTH); ) return TRUE;
	return FALSE;
}

BOOL CTCProcessInterfaceRegisterCommandSourcesRequest::Map(CByteArray &nInfo) CONST
{
	INT  cbData;
	CByteArray  nQueuesData;
	CByteArray  nItemsData[2];
	CByteArray  nInterlocksData;
	CByteArray  nCommandSourcesData;
	TCPIREGISTERCOMMANDSOURCESREQUEST  sData;

	for (CopyMemory(&sData.sHeader, &m_sHeader, sizeof(sData.sHeader)), sData.cbCommandSources = (m_pCommandSources.Map(nCommandSourcesData)) ? (INT)nCommandSourcesData.GetSize() : -1, sData.cbItems[0] = (m_pItems[0].Map(nItemsData[0], TRUE)) ? (INT)nItemsData[0].GetSize() : -1, sData.cbItems[1] = (m_pItems[1].Map(nItemsData[1], TRUE)) ? (INT)nItemsData[1].GetSize() : -1, sData.cbInterlocks = (m_pInterlocks.Map(nInterlocksData)) ? (INT)nInterlocksData.GetSize() : -1, sData.cbQueues = (m_pQueues.Map(nQueuesData)) ? (INT)nQueuesData.GetSize() : -1, nInfo.SetSize(sizeof(TCPIREGISTERCOMMANDSOURCESREQUEST) + max(sData.cbCommandSources, 0) + max(sData.cbItems[0], 0) + max(sData.cbItems[1], 0) + max(sData.cbInterlocks, 0) + max(sData.cbQueues, 0)); nInfo.GetSize() == sizeof(TCPIREGISTERCOMMANDSOURCESREQUEST) + sData.cbCommandSources + sData.cbItems[0] + sData.cbItems[1] + sData.cbInterlocks + sData.cbQueues; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(TCPIREGISTERCOMMANDSOURCESREQUEST));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(TCPIREGISTERCOMMANDSOURCESREQUEST)), nCommandSourcesData.GetData(), sData.cbCommandSources);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbCommandSources), nItemsData[0].GetData(), sData.cbItems[0]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbItems[0]), nItemsData[1].GetData(), sData.cbItems[1]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbItems[1]), nInterlocksData.GetData(), sData.cbInterlocks);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbInterlocks), nQueuesData.GetData(), sData.cbQueues);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceRegisterCommandSourcesRequest::Unmap(CONST CByteArray &nInfo)
{
	INT  cbData;
	CByteArray  nQueuesData;
	CByteArray  nItemsData[2];
	CByteArray  nInterlocksData;
	CByteArray  nCommandSourcesData;
	TCPIREGISTERCOMMANDSOURCESREQUEST  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(TCPIREGISTERCOMMANDSOURCESREQUEST)) ? sizeof(TCPIREGISTERCOMMANDSOURCESREQUEST) : 0); nInfo.GetSize() == sizeof(TCPIREGISTERCOMMANDSOURCESREQUEST) + sData.cbCommandSources + sData.cbItems[0] + sData.cbItems[1] + sData.cbInterlocks + sData.cbQueues && sData.cbCommandSources >= 0 && sData.cbItems[0] >= 0 && sData.cbItems[1] >= 0 && sData.cbInterlocks >= 0 && sData.cbQueues >= 0; )
	{
		for (CopyMemory(&m_sHeader, &sData.sHeader, sizeof(TCPIMESSAGEHEADER)), nCommandSourcesData.SetSize(sData.cbCommandSources), nItemsData[0].SetSize(sData.cbItems[0]), nItemsData[1].SetSize(sData.cbItems[1]), nInterlocksData.SetSize(sData.cbInterlocks), nQueuesData.SetSize(sData.cbQueues), CopyMemory(nCommandSourcesData.GetData(), nInfo.GetData() + (cbData = sizeof(TCPIREGISTERCOMMANDSOURCESREQUEST)), sData.cbCommandSources), CopyMemory(nItemsData[0].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbCommandSources), sData.cbItems[0]), CopyMemory(nItemsData[1].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbItems[0]), sData.cbItems[1]), CopyMemory(nInterlocksData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbItems[1]), sData.cbInterlocks), CopyMemory(nQueuesData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbInterlocks), sData.cbQueues); m_pCommandSources.Unmap(nCommandSourcesData) && m_pItems[0].Unmap(nItemsData[0], TRUE) && m_pItems[1].Unmap(nItemsData[1], TRUE) && m_pInterlocks.Unmap(nInterlocksData) && m_pQueues.Unmap(nQueuesData); ) return Check(sData.cbCommandSources + sData.cbItems[0] + sData.cbItems[1] + sData.cbInterlocks + sData.cbQueues);
		break;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceRegisterCommandSourcesRequest::Check(INT cbData) CONST
{
	return((GetMessageID() == TCPI_REGISTERCOMMANDSOURCESREQUEST  &&  GetMessageLength() == sizeof(TCPIREGISTERCOMMANDSOURCESREQUEST) - TCPI_MESSAGEIDLENGTH + cbData  &&  GetVersion() == TCPI_VERSION) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceRegisterCommandSourcesResponse

CTCProcessInterfaceRegisterCommandSourcesResponse::CTCProcessInterfaceRegisterCommandSourcesResponse() : CTCProcessInterfaceMessageHeader(TCPI_REGISTERCOMMANDSOURCESRESPONSE, sizeof(TCPIMESSAGEHEADER) - TCPI_MESSAGEIDLENGTH)
{
	return;
}

BOOL CTCProcessInterfaceRegisterCommandSourcesResponse::SetCommandSources(CONST CTCProcessCommandSources &pCommandSources)
{
	CByteArray  nDeviceData;
	CByteArray  nQueuesData;
	CByteArray  nItemsData[2];
	CByteArray  nInterlocksData;
	CByteArray  nCommandSourcesData;

	return((m_pCommandSources.Copy(&pCommandSources) && m_pCommandSources.Map(nCommandSourcesData) && m_cDevice.Map(nDeviceData) && m_pItems[0].Map(nItemsData[0], TRUE) && m_pItems[1].Map(nItemsData[1], TRUE) && m_pInterlocks.Map(nInterlocksData) && m_pQueues.Map(nQueuesData)) ? SetMessageLength(sizeof(TCPIREGISTERCOMMANDSOURCESRESPONSE) - TCPI_MESSAGEIDLENGTH + (UINT)nCommandSourcesData.GetSize() + (UINT)nDeviceData.GetSize() + (UINT)nItemsData[0].GetSize() + (UINT)nItemsData[1].GetSize() + (UINT)nInterlocksData.GetSize() + (UINT)nQueuesData.GetSize()) : FALSE);
}

INT CTCProcessInterfaceRegisterCommandSourcesResponse::GetCommandSources(CTCProcessCommandSources &pCommandSources) CONST
{
	return((pCommandSources.Copy(&m_pCommandSources)) ? (INT)pCommandSources.GetSize() : -1);
}

BOOL CTCProcessInterfaceRegisterCommandSourcesResponse::SetCommandingDevice(CONST CTCUplinkDevice *pDevice)
{
	CByteArray  nDeviceData;
	CByteArray  nQueuesData;
	CByteArray  nItemsData[2];
	CByteArray  nInterlocksData;
	CByteArray  nCommandSourcesData;

	return((m_cDevice.Copy(pDevice) && m_pCommandSources.Map(nCommandSourcesData) && m_cDevice.Map(nDeviceData) && m_pItems[0].Map(nItemsData[0], TRUE) && m_pItems[1].Map(nItemsData[1], TRUE) && m_pInterlocks.Map(nInterlocksData) && m_pQueues.Map(nQueuesData)) ? SetMessageLength(sizeof(TCPIREGISTERCOMMANDSOURCESRESPONSE) - TCPI_MESSAGEIDLENGTH + (UINT)nCommandSourcesData.GetSize() + (UINT)nDeviceData.GetSize() + (UINT)nItemsData[0].GetSize() + (UINT)nItemsData[1].GetSize() + (UINT)nInterlocksData.GetSize() + (UINT)nQueuesData.GetSize()) : FALSE);
}

BOOL CTCProcessInterfaceRegisterCommandSourcesResponse::GetCommandingDevice(CTCUplinkDevice *pDevice) CONST
{
	return pDevice->Copy(&m_cDevice);
}

BOOL CTCProcessInterfaceRegisterCommandSourcesResponse::SetTelecommands(CONST CTCItems &pItems, CONST CTCItems &pHistoricalItems)
{
	CByteArray  nDeviceData;
	CByteArray  nQueuesData;
	CByteArray  nItemsData[2];
	CByteArray  nInterlocksData;
	CByteArray  nCommandSourcesData;

	return((m_pItems[0].Copy(&pItems) && m_pItems[1].Copy(&pHistoricalItems) && m_pCommandSources.Map(nCommandSourcesData) && m_cDevice.Map(nDeviceData) && m_pItems[0].Map(nItemsData[0], TRUE) && m_pItems[1].Map(nItemsData[1], TRUE) && m_pInterlocks.Map(nInterlocksData) && m_pQueues.Map(nQueuesData)) ? SetMessageLength(sizeof(TCPIREGISTERCOMMANDSOURCESRESPONSE) - TCPI_MESSAGEIDLENGTH + (UINT)nCommandSourcesData.GetSize() + (UINT)nDeviceData.GetSize() + (UINT)nItemsData[0].GetSize() + (UINT)nItemsData[1].GetSize() + (UINT)nInterlocksData.GetSize() + (UINT)nQueuesData.GetSize()) : FALSE);
}

BOOL CTCProcessInterfaceRegisterCommandSourcesResponse::GetTelecommands(CTCItems &pItems, CTCItems &pHistoricalItems) CONST
{
	return((pItems.Copy(&m_pItems[0]) && pHistoricalItems.Copy(&m_pItems[1])) ? TRUE : FALSE);
}

BOOL CTCProcessInterfaceRegisterCommandSourcesResponse::SetTCInterlocks(CONST CTCInterlocks &pInterlocks)
{
	CByteArray  nDeviceData;
	CByteArray  nQueuesData;
	CByteArray  nItemsData[2];
	CByteArray  nInterlocksData;
	CByteArray  nCommandSourcesData;

	return((m_pInterlocks.Copy(&pInterlocks) && m_pCommandSources.Map(nCommandSourcesData) && m_cDevice.Map(nDeviceData) && m_pItems[0].Map(nItemsData[0], TRUE) && m_pItems[1].Map(nItemsData[1], TRUE) && m_pInterlocks.Map(nInterlocksData) && m_pQueues.Map(nQueuesData)) ? SetMessageLength(sizeof(TCPIREGISTERCOMMANDSOURCESRESPONSE) - TCPI_MESSAGEIDLENGTH + (UINT)nCommandSourcesData.GetSize() + (UINT)nDeviceData.GetSize() + (UINT)nItemsData[0].GetSize() + (UINT)nItemsData[1].GetSize() + (UINT)nInterlocksData.GetSize() + (UINT)nQueuesData.GetSize()) : FALSE);
}

INT CTCProcessInterfaceRegisterCommandSourcesResponse::GetTCInterlocks(CTCInterlocks &pInterlocks) CONST
{
	return((pInterlocks.Copy(&m_pInterlocks)) ? (INT)pInterlocks.GetSize() : -1);
}

BOOL CTCProcessInterfaceRegisterCommandSourcesResponse::SetTCOnBoardBufferQueues(CONST CTCOnBoardBufferQueues &pQueues)
{
	CByteArray  nDeviceData;
	CByteArray  nQueuesData;
	CByteArray  nItemsData[2];
	CByteArray  nInterlocksData;
	CByteArray  nCommandSourcesData;

	return((m_pQueues.Copy(&pQueues) && m_pCommandSources.Map(nCommandSourcesData) && m_cDevice.Map(nDeviceData) && m_pItems[0].Map(nItemsData[0], TRUE) && m_pItems[1].Map(nItemsData[1], TRUE) && m_pInterlocks.Map(nInterlocksData) && m_pQueues.Map(nQueuesData)) ? SetMessageLength(sizeof(TCPIREGISTERCOMMANDSOURCESRESPONSE) - TCPI_MESSAGEIDLENGTH + (UINT)nCommandSourcesData.GetSize() + (UINT)nDeviceData.GetSize() + (UINT)nItemsData[0].GetSize() + (UINT)nItemsData[1].GetSize() + (UINT)nInterlocksData.GetSize() + (UINT)nQueuesData.GetSize()) : FALSE);
}

INT CTCProcessInterfaceRegisterCommandSourcesResponse::GetTCOnBoardBufferQueues(CTCOnBoardBufferQueues &pQueues) CONST
{
	return((pQueues.Copy(&m_pQueues)) ? (INT)pQueues.GetSize() : -1);
}

BOOL CTCProcessInterfaceRegisterCommandSourcesResponse::Map(CByteArray &nInfo) CONST
{
	INT  cbData;
	CByteArray  nDeviceData;
	CByteArray  nQueuesData;
	CByteArray  nItemsData[2];
	CByteArray  nInterlocksData;
	CByteArray  nCommandSourcesData;
	TCPIREGISTERCOMMANDSOURCESRESPONSE  sData;

	for (CopyMemory(&sData.sHeader, &m_sHeader, sizeof(sData.sHeader)), sData.cbCommandSources = (m_pCommandSources.Map(nCommandSourcesData)) ? (INT)nCommandSourcesData.GetSize() : -1, sData.cbDevice = (m_cDevice.Map(nDeviceData)) ? (INT)nDeviceData.GetSize() : -1, sData.cbItems[0] = (m_pItems[0].Map(nItemsData[0], TRUE)) ? (INT)nItemsData[0].GetSize() : -1, sData.cbItems[1] = (m_pItems[1].Map(nItemsData[1], TRUE)) ? (INT)nItemsData[1].GetSize() : -1, sData.cbInterlocks = (m_pInterlocks.Map(nInterlocksData)) ? (INT)nInterlocksData.GetSize() : -1, sData.cbQueues = (m_pQueues.Map(nQueuesData)) ? (INT)nQueuesData.GetSize() : -1, nInfo.SetSize(sizeof(TCPIREGISTERCOMMANDSOURCESRESPONSE) + max(sData.cbCommandSources, 0) + max(sData.cbDevice, 0) + max(sData.cbItems[0], 0) + max(sData.cbItems[1], 0) + max(sData.cbInterlocks, 0) + max(sData.cbQueues, 0)); nInfo.GetSize() == sizeof(TCPIREGISTERCOMMANDSOURCESRESPONSE) + sData.cbCommandSources + sData.cbDevice + sData.cbItems[0] + sData.cbItems[1] + sData.cbInterlocks + sData.cbQueues; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(TCPIREGISTERCOMMANDSOURCESRESPONSE));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(TCPIREGISTERCOMMANDSOURCESRESPONSE)), nCommandSourcesData.GetData(), sData.cbCommandSources);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbCommandSources), nDeviceData.GetData(), sData.cbDevice);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbDevice), nItemsData[0].GetData(), sData.cbItems[0]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbItems[0]), nItemsData[1].GetData(), sData.cbItems[1]);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbItems[1]), nInterlocksData.GetData(), sData.cbInterlocks);
		CopyMemory(nInfo.GetData() + (cbData = cbData + sData.cbInterlocks), nQueuesData.GetData(), sData.cbQueues);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceRegisterCommandSourcesResponse::Unmap(CONST CByteArray &nInfo)
{
	INT  cbData;
	CByteArray  nDeviceData;
	CByteArray  nQueuesData;
	CByteArray  nItemsData[2];
	CByteArray  nInterlocksData;
	CByteArray  nCommandSourcesData;
	TCPIREGISTERCOMMANDSOURCESRESPONSE  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(TCPIREGISTERCOMMANDSOURCESRESPONSE)) ? sizeof(TCPIREGISTERCOMMANDSOURCESRESPONSE) : 0); nInfo.GetSize() == sizeof(TCPIREGISTERCOMMANDSOURCESRESPONSE) + sData.cbCommandSources + sData.cbDevice + sData.cbItems[0] + sData.cbItems[1] + sData.cbInterlocks + sData.cbQueues && sData.cbCommandSources >= 0 && sData.cbDevice >= 0 && sData.cbItems[0] >= 0 && sData.cbItems[1] >= 0 && sData.cbInterlocks >= 0 && sData.cbQueues >= 0; )
	{
		for (CopyMemory(&m_sHeader, &sData.sHeader, sizeof(TCPIMESSAGEHEADER)), nCommandSourcesData.SetSize(sData.cbCommandSources), nDeviceData.SetSize(sData.cbDevice), nItemsData[0].SetSize(sData.cbItems[0]), nItemsData[1].SetSize(sData.cbItems[1]), nInterlocksData.SetSize(sData.cbInterlocks), nQueuesData.SetSize(sData.cbQueues), CopyMemory(nCommandSourcesData.GetData(), nInfo.GetData() + (cbData = sizeof(TCPIREGISTERCOMMANDSOURCESRESPONSE)), sData.cbCommandSources), CopyMemory(nDeviceData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbCommandSources), sData.cbDevice), CopyMemory(nItemsData[0].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbDevice), sData.cbItems[0]), CopyMemory(nItemsData[1].GetData(), nInfo.GetData() + (cbData = cbData + sData.cbItems[0]), sData.cbItems[1]), CopyMemory(nInterlocksData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbItems[1]), sData.cbInterlocks), CopyMemory(nQueuesData.GetData(), nInfo.GetData() + (cbData = cbData + sData.cbInterlocks), sData.cbQueues); m_pCommandSources.Unmap(nCommandSourcesData) && m_cDevice.Unmap(nDeviceData) && m_pItems[0].Unmap(nItemsData[0], TRUE) && m_pItems[1].Unmap(nItemsData[1], TRUE) && m_pInterlocks.Unmap(nInterlocksData) && m_pQueues.Unmap(nQueuesData); ) return Check(sData.cbCommandSources + sData.cbDevice + sData.cbItems[0] + sData.cbItems[1] + sData.cbInterlocks + sData.cbQueues);
		break;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceRegisterCommandSourcesResponse::Check(INT cbData) CONST
{
	return((GetMessageID() == TCPI_REGISTERCOMMANDSOURCESRESPONSE  &&  GetMessageLength() == sizeof(TCPIREGISTERCOMMANDSOURCESRESPONSE) - TCPI_MESSAGEIDLENGTH + cbData  &&  GetVersion() == TCPI_VERSION) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceUpdateCommandSourcesRequest

CTCProcessInterfaceUpdateCommandSourcesRequest::CTCProcessInterfaceUpdateCommandSourcesRequest() : CTCProcessInterfaceMessageHeader(TCPI_UPDATECOMMANDSOURCESREQUEST, sizeof(TCPIMESSAGEHEADER) - TCPI_MESSAGEIDLENGTH)
{
	return;
}

BOOL CTCProcessInterfaceUpdateCommandSourcesRequest::SetCommandSources(CONST CTCProcessCommandSources &pCommandSources)
{
	CByteArray  nCommandSourcesData;

	return((m_pCommandSources.Copy(&pCommandSources) && m_pCommandSources.Map(nCommandSourcesData)) ? SetMessageLength(sizeof(TCPIUPDATECOMMANDSOURCESREQUEST) - TCPI_MESSAGEIDLENGTH + (UINT)nCommandSourcesData.GetSize()) : FALSE);
}

INT CTCProcessInterfaceUpdateCommandSourcesRequest::GetCommandSources(CTCProcessCommandSources &pCommandSources) CONST
{
	return((pCommandSources.Copy(&m_pCommandSources)) ? (INT)pCommandSources.GetSize() : -1);
}

BOOL CTCProcessInterfaceUpdateCommandSourcesRequest::Reset()
{
	m_pCommandSources.RemoveAll();
	return SetMessageLength(sizeof(TCPIUPDATECOMMANDSOURCESREQUEST) - TCPI_MESSAGEIDLENGTH);
}

BOOL CTCProcessInterfaceUpdateCommandSourcesRequest::Map(CByteArray &nInfo) CONST
{
	CByteArray  nCommandSourcesData;
	TCPIUPDATECOMMANDSOURCESREQUEST  sData;

	for (CopyMemory(&sData.sHeader, &m_sHeader, sizeof(sData.sHeader)), sData.cbCommandSources = (m_pCommandSources.Map(nCommandSourcesData)) ? (INT)nCommandSourcesData.GetSize() : -1, nInfo.SetSize(sizeof(TCPIUPDATECOMMANDSOURCESREQUEST) + max(sData.cbCommandSources, 0)); nInfo.GetSize() == sizeof(TCPIUPDATECOMMANDSOURCESREQUEST) + sData.cbCommandSources; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(TCPIUPDATECOMMANDSOURCESREQUEST));
		CopyMemory(nInfo.GetData() + sizeof(TCPIUPDATECOMMANDSOURCESREQUEST), nCommandSourcesData.GetData(), sData.cbCommandSources);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceUpdateCommandSourcesRequest::Unmap(CONST CByteArray &nInfo)
{
	CByteArray  nCommandSourcesData;
	TCPIUPDATECOMMANDSOURCESREQUEST  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(TCPIUPDATECOMMANDSOURCESREQUEST)) ? sizeof(TCPIUPDATECOMMANDSOURCESREQUEST) : 0); nInfo.GetSize() == sizeof(TCPIUPDATECOMMANDSOURCESREQUEST) + sData.cbCommandSources && sData.cbCommandSources >= 0; )
	{
		for (CopyMemory(&m_sHeader, &sData.sHeader, sizeof(TCPIMESSAGEHEADER)), nCommandSourcesData.SetSize(sData.cbCommandSources), CopyMemory(nCommandSourcesData.GetData(), nInfo.GetData() + sizeof(TCPIUPDATECOMMANDSOURCESREQUEST), sData.cbCommandSources); m_pCommandSources.Unmap(nCommandSourcesData); ) return Check(sData.cbCommandSources);
		break;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceUpdateCommandSourcesRequest::Check(INT cbData) CONST
{
	return((GetMessageID() == TCPI_UPDATECOMMANDSOURCESREQUEST  &&  GetMessageLength() == sizeof(TCPIUPDATECOMMANDSOURCESREQUEST) - TCPI_MESSAGEIDLENGTH + cbData  &&  GetVersion() == TCPI_VERSION) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceUpdateCommandSourcesResponse

CTCProcessInterfaceUpdateCommandSourcesResponse::CTCProcessInterfaceUpdateCommandSourcesResponse() : CTCProcessInterfaceMessageHeader(TCPI_UPDATECOMMANDSOURCESRESPONSE, sizeof(TCPIMESSAGEHEADER) - TCPI_MESSAGEIDLENGTH)
{
	return;
}

BOOL CTCProcessInterfaceUpdateCommandSourcesResponse::SetCommandSources(CONST CTCProcessCommandSources &pCommandSources)
{
	CByteArray  nCommandSourcesData;

	return((m_pCommandSources.Copy(&pCommandSources) && m_pCommandSources.Map(nCommandSourcesData)) ? SetMessageLength(sizeof(TCPIUPDATECOMMANDSOURCESRESPONSE) - TCPI_MESSAGEIDLENGTH + (UINT)nCommandSourcesData.GetSize()) : FALSE);
}

INT CTCProcessInterfaceUpdateCommandSourcesResponse::GetCommandSources(CTCProcessCommandSources &pCommandSources) CONST
{
	return((pCommandSources.Copy(&m_pCommandSources)) ? (INT)pCommandSources.GetSize() : -1);
}

BOOL CTCProcessInterfaceUpdateCommandSourcesResponse::Map(CByteArray &nInfo) CONST
{
	CByteArray  nCommandSourcesData;
	TCPIUPDATECOMMANDSOURCESRESPONSE  sData;

	for (CopyMemory(&sData.sHeader, &m_sHeader, sizeof(sData.sHeader)), sData.cbCommandSources = (m_pCommandSources.Map(nCommandSourcesData)) ? (INT)nCommandSourcesData.GetSize() : -1, nInfo.SetSize(sizeof(TCPIUPDATECOMMANDSOURCESRESPONSE) + max(sData.cbCommandSources, 0)); nInfo.GetSize() == sizeof(TCPIUPDATECOMMANDSOURCESRESPONSE) + sData.cbCommandSources; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(TCPIUPDATECOMMANDSOURCESRESPONSE));
		CopyMemory(nInfo.GetData() + sizeof(TCPIUPDATECOMMANDSOURCESRESPONSE), nCommandSourcesData.GetData(), sData.cbCommandSources);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceUpdateCommandSourcesResponse::Unmap(CONST CByteArray &nInfo)
{
	CByteArray  nCommandSourcesData;
	TCPIUPDATECOMMANDSOURCESRESPONSE  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(TCPIUPDATECOMMANDSOURCESRESPONSE)) ? sizeof(TCPIUPDATECOMMANDSOURCESRESPONSE) : 0); nInfo.GetSize() == sizeof(TCPIUPDATECOMMANDSOURCESRESPONSE) + sData.cbCommandSources && sData.cbCommandSources >= 0; )
	{
		for (CopyMemory(&m_sHeader, &sData.sHeader, sizeof(TCPIMESSAGEHEADER)), nCommandSourcesData.SetSize(sData.cbCommandSources), CopyMemory(nCommandSourcesData.GetData(), nInfo.GetData() + sizeof(TCPIUPDATECOMMANDSOURCESRESPONSE), sData.cbCommandSources); m_pCommandSources.Unmap(nCommandSourcesData); ) return Check(sData.cbCommandSources);
		break;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceUpdateCommandSourcesResponse::Check(INT cbData) CONST
{
	return((GetMessageID() == TCPI_UPDATECOMMANDSOURCESRESPONSE  &&  GetMessageLength() == sizeof(TCPIUPDATECOMMANDSOURCESRESPONSE) - TCPI_MESSAGEIDLENGTH + cbData  &&  GetVersion() == TCPI_VERSION) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceUpdateCommandSourcesContentsRequest

CTCProcessInterfaceUpdateCommandSourcesContentsRequest::CTCProcessInterfaceUpdateCommandSourcesContentsRequest() : CTCProcessInterfaceMessageHeader(TCPI_UPDATECOMMANDSOURCESCONTENTSREQUEST, sizeof(TCPIMESSAGEHEADER) - TCPI_MESSAGEIDLENGTH)
{
	m_bItems[0] = FALSE;
	m_bItems[1] = FALSE;
	m_bQueues[0] = FALSE;
	m_bQueues[1] = FALSE;
	m_bInterlocks[0] = FALSE;
	m_bInterlocks[1] = FALSE;
	m_bAcknowledgment = FALSE;
}

BOOL CTCProcessInterfaceUpdateCommandSourcesContentsRequest::SetTelecommands(CONST CTCItems &pItems, BOOL bAll)
{
	CByteArray  nItemsData;
	CByteArray  nQueuesData;
	CByteArray  nInterlocksData;

	if (m_pItems.Copy(&pItems) && m_pItems.Map(nItemsData, TRUE) && m_pInterlocks.Map(nInterlocksData) && m_pQueues.Map(nQueuesData))
	{
		if (SetMessageLength(sizeof(TCPIUPDATECOMMANDSOURCESCONTENTSREQUEST) - TCPI_MESSAGEIDLENGTH + (UINT)nItemsData.GetSize() + (UINT)nInterlocksData.GetSize() + (UINT)nQueuesData.GetSize()))
		{
			m_bItems[0] = TRUE;
			m_bItems[1] = bAll;
			return TRUE;
		}
	}
	return FALSE;
}

INT CTCProcessInterfaceUpdateCommandSourcesContentsRequest::GetTelecommands(CTCItems &pItems, BOOL &bAll) CONST
{
	if (m_bItems[0] && pItems.Copy(&m_pItems))
	{
		bAll = m_bItems[1];
		return((INT)pItems.GetSize());
	}
	return -1;
}

BOOL CTCProcessInterfaceUpdateCommandSourcesContentsRequest::SetTCInterlocks(CONST CTCInterlocks &pInterlocks, BOOL bAll)
{
	CByteArray  nItemsData;
	CByteArray  nQueuesData;
	CByteArray  nInterlocksData;

	if (m_pInterlocks.Copy(&pInterlocks) && m_pItems.Map(nItemsData, TRUE) && m_pInterlocks.Map(nInterlocksData) && m_pQueues.Map(nQueuesData))
	{
		if (SetMessageLength(sizeof(TCPIUPDATECOMMANDSOURCESCONTENTSREQUEST) - TCPI_MESSAGEIDLENGTH + (UINT)nItemsData.GetSize() + (UINT)nInterlocksData.GetSize() + (UINT)nQueuesData.GetSize()))
		{
			m_bInterlocks[0] = TRUE;
			m_bInterlocks[1] = bAll;
			return TRUE;
		}
	}
	return FALSE;
}

INT CTCProcessInterfaceUpdateCommandSourcesContentsRequest::GetTCInterlocks(CTCInterlocks &pInterlocks, BOOL &bAll) CONST
{
	if (m_bInterlocks[0] && pInterlocks.Copy(&m_pInterlocks))
	{
		bAll = m_bInterlocks[1];
		return((INT)pInterlocks.GetSize());
	}
	return -1;
}

BOOL CTCProcessInterfaceUpdateCommandSourcesContentsRequest::SetTCOnBoardBufferQueues(CONST CTCOnBoardBufferQueues &pQueues, BOOL bAll)
{
	CByteArray  nItemsData;
	CByteArray  nQueuesData;
	CByteArray  nInterlocksData;

	if (m_pQueues.Copy(&pQueues) && m_pItems.Map(nItemsData, TRUE) && m_pInterlocks.Map(nInterlocksData) && m_pQueues.Map(nQueuesData))
	{
		if (SetMessageLength(sizeof(TCPIUPDATECOMMANDSOURCESCONTENTSREQUEST) - TCPI_MESSAGEIDLENGTH + (UINT)nItemsData.GetSize() + (UINT)nInterlocksData.GetSize() + (UINT)nQueuesData.GetSize()))
		{
			m_bQueues[0] = TRUE;
			m_bQueues[1] = bAll;
			return TRUE;
		}
	}
	return FALSE;
}

INT CTCProcessInterfaceUpdateCommandSourcesContentsRequest::GetTCOnBoardBufferQueues(CTCOnBoardBufferQueues &pQueues, BOOL &bAll) CONST
{
	if (m_bQueues[0] && pQueues.Copy(&m_pQueues))
	{
		bAll = m_bQueues[1];
		return((INT)pQueues.GetSize());
	}
	return -1;
}

BOOL CTCProcessInterfaceUpdateCommandSourcesContentsRequest::EnableAcknowledgment(BOOL bEnable)
{
	m_bAcknowledgment = bEnable;
	return TRUE;
}

BOOL CTCProcessInterfaceUpdateCommandSourcesContentsRequest::IsAcknowledgmentEnabled() CONST
{
	return m_bAcknowledgment;
}

BOOL CTCProcessInterfaceUpdateCommandSourcesContentsRequest::Reset()
{
	for (m_pItems.RemoveAll(), m_pInterlocks.RemoveAll(), m_pQueues.RemoveAll(), m_bItems[0] = m_bItems[1] = FALSE, m_bInterlocks[0] = m_bInterlocks[1] = FALSE, m_bQueues[0] = m_bQueues[1] = FALSE, m_bAcknowledgment = FALSE; SetMessageLength(sizeof(TCPIUPDATECOMMANDSOURCESCONTENTSREQUEST) - TCPI_MESSAGEIDLENGTH); ) return TRUE;
	return FALSE;
}

BOOL CTCProcessInterfaceUpdateCommandSourcesContentsRequest::Map(CByteArray &nInfo) CONST
{
	CByteArray  nItemsData;
	CByteArray  nQueuesData;
	CByteArray  nInterlocksData;
	TCPIUPDATECOMMANDSOURCESCONTENTSREQUEST  sData;

	for (CopyMemory(&sData.sHeader, &m_sHeader, sizeof(sData.sHeader)), sData.cbItems = (m_pItems.Map(nItemsData, TRUE)) ? (INT)nItemsData.GetSize() : -1, sData.cbInterlocks = (m_pInterlocks.Map(nInterlocksData)) ? (INT)nInterlocksData.GetSize() : -1, sData.cbQueues = (m_pQueues.Map(nQueuesData)) ? (INT)nQueuesData.GetSize() : -1, sData.bItems[0] = m_bItems[0], sData.bItems[1] = m_bItems[1], sData.bInterlocks[0] = m_bInterlocks[0], sData.bInterlocks[1] = m_bInterlocks[1], sData.bQueues[0] = m_bQueues[0], sData.bQueues[1] = m_bQueues[1], sData.bAcknowledgment = m_bAcknowledgment, nInfo.SetSize(sizeof(TCPIUPDATECOMMANDSOURCESCONTENTSREQUEST) + max(sData.cbItems, 0) + max(sData.cbInterlocks, 0) + max(sData.cbQueues, 0)); nInfo.GetSize() == sizeof(TCPIUPDATECOMMANDSOURCESCONTENTSREQUEST) + sData.cbItems + sData.cbInterlocks + sData.cbQueues; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(TCPIUPDATECOMMANDSOURCESCONTENTSREQUEST));
		CopyMemory(nInfo.GetData() + sizeof(TCPIUPDATECOMMANDSOURCESCONTENTSREQUEST), nItemsData.GetData(), sData.cbItems);
		CopyMemory(nInfo.GetData() + sizeof(TCPIUPDATECOMMANDSOURCESCONTENTSREQUEST) + sData.cbItems, nInterlocksData.GetData(), sData.cbInterlocks);
		CopyMemory(nInfo.GetData() + sizeof(TCPIUPDATECOMMANDSOURCESCONTENTSREQUEST) + sData.cbItems + sData.cbInterlocks, nQueuesData.GetData(), sData.cbQueues);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceUpdateCommandSourcesContentsRequest::Unmap(CONST CByteArray &nInfo)
{
	CByteArray  nItemsData;
	CByteArray  nQueuesData;
	CByteArray  nInterlocksData;
	TCPIUPDATECOMMANDSOURCESCONTENTSREQUEST  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(TCPIUPDATECOMMANDSOURCESCONTENTSREQUEST)) ? sizeof(TCPIUPDATECOMMANDSOURCESCONTENTSREQUEST) : 0); nInfo.GetSize() == sizeof(TCPIUPDATECOMMANDSOURCESCONTENTSREQUEST) + sData.cbItems + sData.cbInterlocks + sData.cbQueues && sData.cbItems >= 0 && sData.cbInterlocks >= 0 && sData.cbQueues >= 0; )
	{
		for (CopyMemory(&m_sHeader, &sData.sHeader, sizeof(TCPIMESSAGEHEADER)), nItemsData.SetSize(sData.cbItems), nInterlocksData.SetSize(sData.cbInterlocks), nQueuesData.SetSize(sData.cbQueues), CopyMemory(nItemsData.GetData(), nInfo.GetData() + sizeof(TCPIUPDATECOMMANDSOURCESCONTENTSREQUEST), sData.cbItems), CopyMemory(nInterlocksData.GetData(), nInfo.GetData() + sizeof(TCPIUPDATECOMMANDSOURCESCONTENTSREQUEST) + sData.cbItems, sData.cbInterlocks), CopyMemory(nQueuesData.GetData(), nInfo.GetData() + sizeof(TCPIUPDATECOMMANDSOURCESCONTENTSREQUEST) + sData.cbItems + sData.cbInterlocks, sData.cbQueues), m_bItems[0] = sData.bItems[0], m_bItems[1] = sData.bItems[1], m_bInterlocks[0] = sData.bInterlocks[0], m_bInterlocks[1] = sData.bInterlocks[1], m_bQueues[0] = sData.bQueues[0], m_bQueues[1] = sData.bQueues[1], m_bAcknowledgment = sData.bAcknowledgment; m_pItems.Unmap(nItemsData, TRUE) && m_pInterlocks.Unmap(nInterlocksData) && m_pQueues.Unmap(nQueuesData); ) return Check(sData.cbItems + sData.cbInterlocks + sData.cbQueues);
		break;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceUpdateCommandSourcesContentsRequest::Check(INT cbData) CONST
{
	return((GetMessageID() == TCPI_UPDATECOMMANDSOURCESCONTENTSREQUEST  &&  GetMessageLength() == sizeof(TCPIUPDATECOMMANDSOURCESCONTENTSREQUEST) - TCPI_MESSAGEIDLENGTH + cbData  &&  GetVersion() == TCPI_VERSION) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceUpdateCommandSourcesContentsResponse

CTCProcessInterfaceUpdateCommandSourcesContentsResponse::CTCProcessInterfaceUpdateCommandSourcesContentsResponse() : CTCProcessInterfaceMessageHeader(TCPI_UPDATECOMMANDSOURCESCONTENTSRESPONSE, sizeof(TCPIUPDATECOMMANDSOURCESCONTENTSRESPONSE) - TCPI_MESSAGEIDLENGTH)
{
	m_bResult = FALSE;
}

BOOL CTCProcessInterfaceUpdateCommandSourcesContentsResponse::SetResult(BOOL bSuccess)
{
	m_bResult = bSuccess;
	return TRUE;
}

BOOL CTCProcessInterfaceUpdateCommandSourcesContentsResponse::GetResult() CONST
{
	return m_bResult;
}

BOOL CTCProcessInterfaceUpdateCommandSourcesContentsResponse::Map(CByteArray &nInfo) CONST
{
	TCPIUPDATECOMMANDSOURCESCONTENTSRESPONSE  sData;

	for (CopyMemory(&sData.sHeader, &m_sHeader, sizeof(sData.sHeader)), sData.bResult = m_bResult, nInfo.SetSize(sizeof(TCPIUPDATECOMMANDSOURCESCONTENTSRESPONSE)); nInfo.GetSize() == sizeof(TCPIUPDATECOMMANDSOURCESCONTENTSRESPONSE); )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(TCPIUPDATECOMMANDSOURCESCONTENTSRESPONSE));
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceUpdateCommandSourcesContentsResponse::Unmap(CONST CByteArray &nInfo)
{
	TCPIUPDATECOMMANDSOURCESCONTENTSRESPONSE  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(TCPIUPDATECOMMANDSOURCESCONTENTSRESPONSE)) ? sizeof(TCPIUPDATECOMMANDSOURCESCONTENTSRESPONSE) : 0); nInfo.GetSize() == sizeof(TCPIUPDATECOMMANDSOURCESCONTENTSRESPONSE); )
	{
		CopyMemory(&m_sHeader, &sData.sHeader, sizeof(TCPIMESSAGEHEADER));
		m_bResult = sData.bResult;
		return Check();
	}
	return FALSE;
}

BOOL CTCProcessInterfaceUpdateCommandSourcesContentsResponse::Check() CONST
{
	return((GetMessageID() == TCPI_UPDATECOMMANDSOURCESCONTENTSRESPONSE  &&  GetMessageLength() == sizeof(TCPIUPDATECOMMANDSOURCESCONTENTSRESPONSE) - TCPI_MESSAGEIDLENGTH  &&  GetVersion() == TCPI_VERSION) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceUpdateCommandUplinkDeviceState

CTCProcessInterfaceUpdateCommandUplinkDeviceState::CTCProcessInterfaceUpdateCommandUplinkDeviceState() : CTCProcessInterfaceMessageHeader(TCPI_UPDATECOMMANDUPLINKDEVICESTATE, sizeof(TCPIMESSAGEHEADER) - TCPI_MESSAGEIDLENGTH)
{
	return;
}

BOOL CTCProcessInterfaceUpdateCommandUplinkDeviceState::SetCommandingDevice(CONST CTCUplinkDevice *pDevice)
{
	CByteArray  nDeviceData;

	return((m_cDevice.Copy(pDevice) && pDevice->Map(nDeviceData)) ? SetMessageLength(sizeof(TCPIUPDATECOMMANDUPLINKDEVICESTATE) - TCPI_MESSAGEIDLENGTH + (UINT)nDeviceData.GetSize()) : FALSE);
}

BOOL CTCProcessInterfaceUpdateCommandUplinkDeviceState::GetCommandingDevice(CTCUplinkDevice *pDevice) CONST
{
	return pDevice->Copy(&m_cDevice);
}

BOOL CTCProcessInterfaceUpdateCommandUplinkDeviceState::Reset()
{
	CTCUplinkDevice  cDevice;

	m_cDevice.Copy(&cDevice);
	return SetMessageLength(sizeof(TCPIUPDATECOMMANDUPLINKDEVICESTATE) - TCPI_MESSAGEIDLENGTH);
}

BOOL CTCProcessInterfaceUpdateCommandUplinkDeviceState::Map(CByteArray &nInfo) CONST
{
	CByteArray  nDeviceData;
	TCPIUPDATECOMMANDUPLINKDEVICESTATE  sData;

	for (CopyMemory(&sData.sHeader, &m_sHeader, sizeof(sData.sHeader)), sData.cbDevice = (m_cDevice.Map(nDeviceData)) ? (INT)nDeviceData.GetSize() : -1, nInfo.SetSize(sizeof(TCPIUPDATECOMMANDUPLINKDEVICESTATE) + max(sData.cbDevice, 0)); nInfo.GetSize() == sizeof(TCPIUPDATECOMMANDUPLINKDEVICESTATE) + sData.cbDevice; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(TCPIUPDATECOMMANDUPLINKDEVICESTATE));
		CopyMemory(nInfo.GetData() + sizeof(TCPIUPDATECOMMANDUPLINKDEVICESTATE), nDeviceData.GetData(), sData.cbDevice);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceUpdateCommandUplinkDeviceState::Unmap(CONST CByteArray &nInfo)
{
	CByteArray  nDeviceData;
	TCPIUPDATECOMMANDUPLINKDEVICESTATE  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(TCPIUPDATECOMMANDUPLINKDEVICESTATE)) ? sizeof(TCPIUPDATECOMMANDUPLINKDEVICESTATE) : 0); nInfo.GetSize() == sizeof(TCPIUPDATECOMMANDUPLINKDEVICESTATE) + sData.cbDevice && sData.cbDevice >= 0; )
	{
		for (CopyMemory(&m_sHeader, &sData.sHeader, sizeof(TCPIMESSAGEHEADER)), nDeviceData.SetSize(sData.cbDevice), CopyMemory(nDeviceData.GetData(), nInfo.GetData() + sizeof(TCPIUPDATECOMMANDUPLINKDEVICESTATE), sData.cbDevice); m_cDevice.Unmap(nDeviceData); ) return Check(sData.cbDevice);
		break;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceUpdateCommandUplinkDeviceState::Check(INT cbData) CONST
{
	return((GetMessageID() == TCPI_UPDATECOMMANDUPLINKDEVICESTATE  &&  GetMessageLength() == sizeof(TCPIUPDATECOMMANDUPLINKDEVICESTATE) - TCPI_MESSAGEIDLENGTH + cbData  &&  GetVersion() == TCPI_VERSION) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceDispatchTelecommandsRequest

CTCProcessInterfaceDispatchTelecommandsRequest::CTCProcessInterfaceDispatchTelecommandsRequest() : CTCProcessInterfaceMessageHeader(TCPI_DISPATCHTELECOMMANDSREQUEST, sizeof(TCPIMESSAGEHEADER) - TCPI_MESSAGEIDLENGTH)
{
	m_bUndo = FALSE;
	m_bAcknowledgment = FALSE;
}

BOOL CTCProcessInterfaceDispatchTelecommandsRequest::SetTelecommands(CONST CTCItems &pItems, BOOL bUndo)
{
	CByteArray  nItemsData;

	m_bUndo = bUndo;
	return((m_pItems.Copy(&pItems) && pItems.Map(nItemsData, TRUE)) ? SetMessageLength(sizeof(TCPIDISPATCHTELECOMMANDSREQUEST) - TCPI_MESSAGEIDLENGTH + (UINT)nItemsData.GetSize()) : FALSE);
}

INT CTCProcessInterfaceDispatchTelecommandsRequest::GetTelecommands(CTCItems &pItems, BOOL &bUndo) CONST
{
	bUndo = m_bUndo;
	return((pItems.Copy(&m_pItems)) ? (INT)pItems.GetSize() : -1);
}

BOOL CTCProcessInterfaceDispatchTelecommandsRequest::EnableAcknowledgment(BOOL bEnable)
{
	m_bAcknowledgment = bEnable;
	return TRUE;
}

BOOL CTCProcessInterfaceDispatchTelecommandsRequest::IsAcknowledgmentEnabled() CONST
{
	return m_bAcknowledgment;
}

BOOL CTCProcessInterfaceDispatchTelecommandsRequest::Reset()
{
	for (m_pItems.RemoveAll(), m_bUndo = FALSE, m_bAcknowledgment = FALSE; SetMessageLength(sizeof(TCPIDISPATCHTELECOMMANDSREQUEST) - TCPI_MESSAGEIDLENGTH); ) return TRUE;
	return FALSE;
}

BOOL CTCProcessInterfaceDispatchTelecommandsRequest::Map(CByteArray &nInfo) CONST
{
	CByteArray  nItemsData;
	TCPIDISPATCHTELECOMMANDSREQUEST  sData;

	for (CopyMemory(&sData.sHeader, &m_sHeader, sizeof(sData.sHeader)), sData.cbItems = (m_pItems.Map(nItemsData, TRUE)) ? (INT)nItemsData.GetSize() : -1, sData.bUndo = m_bUndo, sData.bAcknowledgment = m_bAcknowledgment, nInfo.SetSize(sizeof(TCPIDISPATCHTELECOMMANDSREQUEST) + max(sData.cbItems, 0)); nInfo.GetSize() == sizeof(TCPIDISPATCHTELECOMMANDSREQUEST) + sData.cbItems; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(TCPIDISPATCHTELECOMMANDSREQUEST));
		CopyMemory(nInfo.GetData() + sizeof(TCPIDISPATCHTELECOMMANDSREQUEST), nItemsData.GetData(), sData.cbItems);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceDispatchTelecommandsRequest::Unmap(CONST CByteArray &nInfo)
{
	CByteArray  nItemsData;
	TCPIDISPATCHTELECOMMANDSREQUEST  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(TCPIDISPATCHTELECOMMANDSREQUEST)) ? sizeof(TCPIDISPATCHTELECOMMANDSREQUEST) : 0); nInfo.GetSize() == sizeof(TCPIDISPATCHTELECOMMANDSREQUEST) + sData.cbItems && sData.cbItems >= 0; )
	{
		for (CopyMemory(&m_sHeader, &sData.sHeader, sizeof(TCPIMESSAGEHEADER)), nItemsData.SetSize(sData.cbItems), CopyMemory(nItemsData.GetData(), nInfo.GetData() + sizeof(TCPIDISPATCHTELECOMMANDSREQUEST), sData.cbItems), m_bUndo = sData.bUndo, m_bAcknowledgment = sData.bAcknowledgment; m_pItems.Unmap(nItemsData, TRUE); ) return Check(sData.cbItems);
		break;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceDispatchTelecommandsRequest::Check(INT cbData) CONST
{
	return((GetMessageID() == TCPI_DISPATCHTELECOMMANDSREQUEST  &&  GetMessageLength() == sizeof(TCPIDISPATCHTELECOMMANDSREQUEST) - TCPI_MESSAGEIDLENGTH + cbData  &&  GetVersion() == TCPI_VERSION) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceDispatchTelecommandsResponse

CTCProcessInterfaceDispatchTelecommandsResponse::CTCProcessInterfaceDispatchTelecommandsResponse() : CTCProcessInterfaceMessageHeader(TCPI_DISPATCHTELECOMMANDSRESPONSE, sizeof(TCPIDISPATCHTELECOMMANDSRESPONSE) - TCPI_MESSAGEIDLENGTH)
{
	m_bResult = FALSE;
}

BOOL CTCProcessInterfaceDispatchTelecommandsResponse::SetResult(BOOL bSuccess)
{
	m_bResult = bSuccess;
	return TRUE;
}

BOOL CTCProcessInterfaceDispatchTelecommandsResponse::GetResult() CONST
{
	return m_bResult;
}

BOOL CTCProcessInterfaceDispatchTelecommandsResponse::Map(CByteArray &nInfo) CONST
{
	TCPIDISPATCHTELECOMMANDSRESPONSE  sData;

	for (CopyMemory(&sData.sHeader, &m_sHeader, sizeof(sData.sHeader)), sData.bResult = m_bResult, nInfo.SetSize(sizeof(TCPIDISPATCHTELECOMMANDSRESPONSE)); nInfo.GetSize() == sizeof(TCPIDISPATCHTELECOMMANDSRESPONSE); )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(TCPIDISPATCHTELECOMMANDSRESPONSE));
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceDispatchTelecommandsResponse::Unmap(CONST CByteArray &nInfo)
{
	TCPIDISPATCHTELECOMMANDSRESPONSE  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(TCPIDISPATCHTELECOMMANDSRESPONSE)) ? sizeof(TCPIDISPATCHTELECOMMANDSRESPONSE) : 0); nInfo.GetSize() == sizeof(TCPIDISPATCHTELECOMMANDSRESPONSE); )
	{
		CopyMemory(&m_sHeader, &sData.sHeader, sizeof(TCPIMESSAGEHEADER));
		m_bResult = sData.bResult;
		return Check();
	}
	return FALSE;
}

BOOL CTCProcessInterfaceDispatchTelecommandsResponse::Check() CONST
{
	return((GetMessageID() == TCPI_DISPATCHTELECOMMANDSRESPONSE  &&  GetMessageLength() == sizeof(TCPIDISPATCHTELECOMMANDSRESPONSE) - TCPI_MESSAGEIDLENGTH  &&  GetVersion() == TCPI_VERSION) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceReleaseTelecommandsRequest

CTCProcessInterfaceReleaseTelecommandsRequest::CTCProcessInterfaceReleaseTelecommandsRequest() : CTCProcessInterfaceMessageHeader(TCPI_RELEASETELECOMMANDSREQUEST, sizeof(TCPIMESSAGEHEADER) - TCPI_MESSAGEIDLENGTH)
{
	m_bAcknowledgment = FALSE;
}

BOOL CTCProcessInterfaceReleaseTelecommandsRequest::SetTelecommands(CONST CTCItems &pItems)
{
	CByteArray  nItemsData;

	return((m_pItems.Copy(&pItems) && pItems.Map(nItemsData, TRUE)) ? SetMessageLength(sizeof(TCPIRELEASETELECOMMANDSREQUEST) - TCPI_MESSAGEIDLENGTH + (UINT)nItemsData.GetSize()) : FALSE);
}

INT CTCProcessInterfaceReleaseTelecommandsRequest::GetTelecommands(CTCItems &pItems) CONST
{
	return((pItems.Copy(&m_pItems)) ? (INT)pItems.GetSize() : -1);
}

BOOL CTCProcessInterfaceReleaseTelecommandsRequest::EnableAcknowledgment(BOOL bEnable)
{
	m_bAcknowledgment = bEnable;
	return TRUE;
}

BOOL CTCProcessInterfaceReleaseTelecommandsRequest::IsAcknowledgmentEnabled() CONST
{
	return m_bAcknowledgment;
}

BOOL CTCProcessInterfaceReleaseTelecommandsRequest::Reset()
{
	m_pItems.RemoveAll();
	m_bAcknowledgment = FALSE;
	return SetMessageLength(sizeof(TCPIRELEASETELECOMMANDSREQUEST) - TCPI_MESSAGEIDLENGTH);
}

BOOL CTCProcessInterfaceReleaseTelecommandsRequest::Map(CByteArray &nInfo) CONST
{
	CByteArray  nItemsData;
	TCPIRELEASETELECOMMANDSREQUEST  sData;

	for (CopyMemory(&sData.sHeader, &m_sHeader, sizeof(sData.sHeader)), sData.cbItems = (m_pItems.Map(nItemsData, TRUE)) ? (INT)nItemsData.GetSize() : -1, sData.bAcknowledgment = m_bAcknowledgment, nInfo.SetSize(sizeof(TCPIRELEASETELECOMMANDSREQUEST) + max(sData.cbItems, 0)); nInfo.GetSize() == sizeof(TCPIRELEASETELECOMMANDSREQUEST) + sData.cbItems; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(TCPIRELEASETELECOMMANDSREQUEST));
		CopyMemory(nInfo.GetData() + sizeof(TCPIRELEASETELECOMMANDSREQUEST), nItemsData.GetData(), sData.cbItems);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceReleaseTelecommandsRequest::Unmap(CONST CByteArray &nInfo)
{
	CByteArray  nItemsData;
	TCPIRELEASETELECOMMANDSREQUEST  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(TCPIRELEASETELECOMMANDSREQUEST)) ? sizeof(TCPIRELEASETELECOMMANDSREQUEST) : 0); nInfo.GetSize() == sizeof(TCPIRELEASETELECOMMANDSREQUEST) + sData.cbItems && sData.cbItems >= 0; )
	{
		for (CopyMemory(&m_sHeader, &sData.sHeader, sizeof(TCPIMESSAGEHEADER)), nItemsData.SetSize(sData.cbItems), CopyMemory(nItemsData.GetData(), nInfo.GetData() + sizeof(TCPIRELEASETELECOMMANDSREQUEST), sData.cbItems), m_bAcknowledgment = sData.bAcknowledgment; m_pItems.Unmap(nItemsData, TRUE); ) return Check(sData.cbItems);
		break;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceReleaseTelecommandsRequest::Check(INT cbData) CONST
{
	return((GetMessageID() == TCPI_RELEASETELECOMMANDSREQUEST  &&  GetMessageLength() == sizeof(TCPIRELEASETELECOMMANDSREQUEST) - TCPI_MESSAGEIDLENGTH + cbData  &&  GetVersion() == TCPI_VERSION) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceReleaseTelecommandsResponse

CTCProcessInterfaceReleaseTelecommandsResponse::CTCProcessInterfaceReleaseTelecommandsResponse() : CTCProcessInterfaceMessageHeader(TCPI_RELEASETELECOMMANDSRESPONSE, sizeof(TCPIRELEASETELECOMMANDSRESPONSE) - TCPI_MESSAGEIDLENGTH)
{
	m_bResult = FALSE;
}

BOOL CTCProcessInterfaceReleaseTelecommandsResponse::SetResult(BOOL bSuccess)
{
	m_bResult = bSuccess;
	return TRUE;
}

BOOL CTCProcessInterfaceReleaseTelecommandsResponse::GetResult() CONST
{
	return m_bResult;
}

BOOL CTCProcessInterfaceReleaseTelecommandsResponse::Map(CByteArray &nInfo) CONST
{
	TCPIRELEASETELECOMMANDSRESPONSE  sData;

	for (CopyMemory(&sData.sHeader, &m_sHeader, sizeof(sData.sHeader)), sData.bResult = m_bResult, nInfo.SetSize(sizeof(TCPIRELEASETELECOMMANDSRESPONSE)); nInfo.GetSize() == sizeof(TCPIRELEASETELECOMMANDSRESPONSE); )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(TCPIRELEASETELECOMMANDSRESPONSE));
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceReleaseTelecommandsResponse::Unmap(CONST CByteArray &nInfo)
{
	TCPIRELEASETELECOMMANDSRESPONSE  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(TCPIRELEASETELECOMMANDSRESPONSE)) ? sizeof(TCPIRELEASETELECOMMANDSRESPONSE) : 0); nInfo.GetSize() == sizeof(TCPIRELEASETELECOMMANDSRESPONSE); )
	{
		CopyMemory(&m_sHeader, &sData.sHeader, sizeof(TCPIMESSAGEHEADER));
		m_bResult = sData.bResult;
		return Check();
	}
	return FALSE;
}

BOOL CTCProcessInterfaceReleaseTelecommandsResponse::Check() CONST
{
	return((GetMessageID() == TCPI_RELEASETELECOMMANDSRESPONSE  &&  GetMessageLength() == sizeof(TCPIRELEASETELECOMMANDSRESPONSE) - TCPI_MESSAGEIDLENGTH  &&  GetVersion() == TCPI_VERSION) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceExecuteTelecommandRequest

CTCProcessInterfaceExecuteTelecommandRequest::CTCProcessInterfaceExecuteTelecommandRequest() : CTCProcessInterfaceMessageHeader(TCPI_EXECUTETELECOMMANDREQUEST, sizeof(TCPIMESSAGEHEADER) - TCPI_MESSAGEIDLENGTH)
{
	m_bAcknowledgment = FALSE;
}

BOOL CTCProcessInterfaceExecuteTelecommandRequest::SetTelecommand(CONST CTCItem *pItem)
{
	CByteArray  nItemData;

	return((m_cItem.Copy(pItem) && m_cItem.Map(nItemData, TRUE)) ? SetMessageLength(sizeof(TCPIEXECUTETELECOMMANDREQUEST) - TCPI_MESSAGEIDLENGTH + (UINT)nItemData.GetSize()) : FALSE);
}

BOOL CTCProcessInterfaceExecuteTelecommandRequest::GetTelecommand(CTCItem *pItem) CONST
{
	return pItem->Copy(&m_cItem);
}

BOOL CTCProcessInterfaceExecuteTelecommandRequest::EnableAcknowledgment(BOOL bEnable)
{
	m_bAcknowledgment = bEnable;
	return TRUE;
}

BOOL CTCProcessInterfaceExecuteTelecommandRequest::IsAcknowledgmentEnabled() CONST
{
	return m_bAcknowledgment;
}

BOOL CTCProcessInterfaceExecuteTelecommandRequest::Reset()
{
	CTCItem  cItem;

	m_cItem.Copy(&cItem);
	m_bAcknowledgment = FALSE;
	return SetMessageLength(sizeof(TCPIEXECUTETELECOMMANDREQUEST) - TCPI_MESSAGEIDLENGTH);
}

BOOL CTCProcessInterfaceExecuteTelecommandRequest::Map(CByteArray &nInfo) CONST
{
	CByteArray  nItemData;
	TCPIEXECUTETELECOMMANDREQUEST  sData;

	for (CopyMemory(&sData.sHeader, &m_sHeader, sizeof(sData.sHeader)), sData.cbItem = (m_cItem.Map(nItemData, TRUE)) ? (INT)nItemData.GetSize() : -1, sData.bAcknowledgment = m_bAcknowledgment, nInfo.SetSize(sizeof(TCPIEXECUTETELECOMMANDREQUEST) + max(sData.cbItem, 0)); nInfo.GetSize() == sizeof(TCPIEXECUTETELECOMMANDREQUEST) + sData.cbItem; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(TCPIEXECUTETELECOMMANDREQUEST));
		CopyMemory(nInfo.GetData() + sizeof(TCPIEXECUTETELECOMMANDREQUEST), nItemData.GetData(), sData.cbItem);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceExecuteTelecommandRequest::Unmap(CONST CByteArray &nInfo)
{
	CByteArray  nItemData;
	TCPIEXECUTETELECOMMANDREQUEST  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(TCPIEXECUTETELECOMMANDREQUEST)) ? sizeof(TCPIEXECUTETELECOMMANDREQUEST) : 0); nInfo.GetSize() == sizeof(TCPIEXECUTETELECOMMANDREQUEST) + sData.cbItem && sData.cbItem >= 0; )
	{
		for (CopyMemory(&m_sHeader, &sData.sHeader, sizeof(TCPIMESSAGEHEADER)), nItemData.SetSize(sData.cbItem), CopyMemory(nItemData.GetData(), nInfo.GetData() + sizeof(TCPIEXECUTETELECOMMANDREQUEST), sData.cbItem), m_bAcknowledgment = sData.bAcknowledgment; m_cItem.Unmap(nItemData, TRUE); ) return Check(sData.cbItem);
		break;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceExecuteTelecommandRequest::Check(INT cbData) CONST
{
	return((GetMessageID() == TCPI_EXECUTETELECOMMANDREQUEST  &&  GetMessageLength() == sizeof(TCPIEXECUTETELECOMMANDREQUEST) - TCPI_MESSAGEIDLENGTH + cbData  &&  GetVersion() == TCPI_VERSION) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceExecuteTelecommandResponse

CTCProcessInterfaceExecuteTelecommandResponse::CTCProcessInterfaceExecuteTelecommandResponse() : CTCProcessInterfaceMessageHeader(TCPI_EXECUTETELECOMMANDRESPONSE, sizeof(TCPIEXECUTETELECOMMANDRESPONSE) - TCPI_MESSAGEIDLENGTH)
{
	m_bResult = FALSE;
}

BOOL CTCProcessInterfaceExecuteTelecommandResponse::SetResult(BOOL bSuccess)
{
	m_bResult = bSuccess;
	return TRUE;
}

BOOL CTCProcessInterfaceExecuteTelecommandResponse::GetResult() CONST
{
	return m_bResult;
}

BOOL CTCProcessInterfaceExecuteTelecommandResponse::Map(CByteArray &nInfo) CONST
{
	TCPIEXECUTETELECOMMANDRESPONSE  sData;

	for (CopyMemory(&sData.sHeader, &m_sHeader, sizeof(sData.sHeader)), sData.bResult = m_bResult, nInfo.SetSize(sizeof(TCPIEXECUTETELECOMMANDRESPONSE)); nInfo.GetSize() == sizeof(TCPIEXECUTETELECOMMANDRESPONSE); )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(TCPIEXECUTETELECOMMANDRESPONSE));
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceExecuteTelecommandResponse::Unmap(CONST CByteArray &nInfo)
{
	TCPIEXECUTETELECOMMANDRESPONSE  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(TCPIEXECUTETELECOMMANDRESPONSE)) ? sizeof(TCPIEXECUTETELECOMMANDRESPONSE) : 0); nInfo.GetSize() == sizeof(TCPIEXECUTETELECOMMANDRESPONSE); )
	{
		CopyMemory(&m_sHeader, &sData.sHeader, sizeof(TCPIMESSAGEHEADER));
		m_bResult = sData.bResult;
		return Check();
	}
	return FALSE;
}

BOOL CTCProcessInterfaceExecuteTelecommandResponse::Check() CONST
{
	return((GetMessageID() == TCPI_EXECUTETELECOMMANDRESPONSE  &&  GetMessageLength() == sizeof(TCPIEXECUTETELECOMMANDRESPONSE) - TCPI_MESSAGEIDLENGTH  &&  GetVersion() == TCPI_VERSION) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceAcknowledgeTelecommandsRequest

CTCProcessInterfaceAcknowledgeTelecommandsRequest::CTCProcessInterfaceAcknowledgeTelecommandsRequest() : CTCProcessInterfaceMessageHeader(TCPI_ACKNOWLEDGETELECOMMANDSREQUEST, sizeof(TCPIMESSAGEHEADER) - TCPI_MESSAGEIDLENGTH)
{
	m_bAcknowledgment = FALSE;
}

BOOL CTCProcessInterfaceAcknowledgeTelecommandsRequest::SetTelecommands(CONST CTCItems &pItems)
{
	CByteArray  nItemsData;

	return((m_pItems.Copy(&pItems) && pItems.Map(nItemsData, TRUE)) ? SetMessageLength(sizeof(TCPIACKNOWLEDGETELECOMMANDSREQUEST) - TCPI_MESSAGEIDLENGTH + (UINT)nItemsData.GetSize()) : FALSE);
}

INT CTCProcessInterfaceAcknowledgeTelecommandsRequest::GetTelecommands(CTCItems &pItems) CONST
{
	return((pItems.Copy(&m_pItems)) ? (INT)pItems.GetSize() : -1);
}

BOOL CTCProcessInterfaceAcknowledgeTelecommandsRequest::EnableAcknowledgment(BOOL bEnable)
{
	m_bAcknowledgment = bEnable;
	return TRUE;
}

BOOL CTCProcessInterfaceAcknowledgeTelecommandsRequest::IsAcknowledgmentEnabled() CONST
{
	return m_bAcknowledgment;
}

BOOL CTCProcessInterfaceAcknowledgeTelecommandsRequest::Reset()
{
	m_pItems.RemoveAll();
	m_bAcknowledgment = FALSE;
	return SetMessageLength(sizeof(TCPIACKNOWLEDGETELECOMMANDSREQUEST) - TCPI_MESSAGEIDLENGTH);
}

BOOL CTCProcessInterfaceAcknowledgeTelecommandsRequest::Map(CByteArray &nInfo) CONST
{
	CByteArray  nItemsData;
	TCPIACKNOWLEDGETELECOMMANDSREQUEST  sData;

	for (CopyMemory(&sData.sHeader, &m_sHeader, sizeof(sData.sHeader)), sData.cbItems = (m_pItems.Map(nItemsData, TRUE)) ? (INT)nItemsData.GetSize() : -1, sData.bAcknowledgment = m_bAcknowledgment, nInfo.SetSize(sizeof(TCPIACKNOWLEDGETELECOMMANDSREQUEST) + max(sData.cbItems, 0)); nInfo.GetSize() == sizeof(TCPIACKNOWLEDGETELECOMMANDSREQUEST) + sData.cbItems; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(TCPIACKNOWLEDGETELECOMMANDSREQUEST));
		CopyMemory(nInfo.GetData() + sizeof(TCPIACKNOWLEDGETELECOMMANDSREQUEST), nItemsData.GetData(), sData.cbItems);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceAcknowledgeTelecommandsRequest::Unmap(CONST CByteArray &nInfo)
{
	CByteArray  nItemsData;
	TCPIACKNOWLEDGETELECOMMANDSREQUEST  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(TCPIACKNOWLEDGETELECOMMANDSREQUEST)) ? sizeof(TCPIACKNOWLEDGETELECOMMANDSREQUEST) : 0); nInfo.GetSize() == sizeof(TCPIACKNOWLEDGETELECOMMANDSREQUEST) + sData.cbItems && sData.cbItems >= 0; )
	{
		for (CopyMemory(&m_sHeader, &sData.sHeader, sizeof(TCPIMESSAGEHEADER)), nItemsData.SetSize(sData.cbItems), CopyMemory(nItemsData.GetData(), nInfo.GetData() + sizeof(TCPIACKNOWLEDGETELECOMMANDSREQUEST), sData.cbItems), m_bAcknowledgment = sData.bAcknowledgment; m_pItems.Unmap(nItemsData, TRUE); ) return Check(sData.cbItems);
		break;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceAcknowledgeTelecommandsRequest::Check(INT cbData) CONST
{
	return((GetMessageID() == TCPI_ACKNOWLEDGETELECOMMANDSREQUEST  &&  GetMessageLength() == sizeof(TCPIACKNOWLEDGETELECOMMANDSREQUEST) - TCPI_MESSAGEIDLENGTH + cbData  &&  GetVersion() == TCPI_VERSION) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceAcknowledgeTelecommandsResponse

CTCProcessInterfaceAcknowledgeTelecommandsResponse::CTCProcessInterfaceAcknowledgeTelecommandsResponse() : CTCProcessInterfaceMessageHeader(TCPI_ACKNOWLEDGETELECOMMANDSRESPONSE, sizeof(TCPIACKNOWLEDGETELECOMMANDSRESPONSE) - TCPI_MESSAGEIDLENGTH)
{
	m_bResult = FALSE;
}

BOOL CTCProcessInterfaceAcknowledgeTelecommandsResponse::SetResult(BOOL bSuccess)
{
	m_bResult = bSuccess;
	return TRUE;
}

BOOL CTCProcessInterfaceAcknowledgeTelecommandsResponse::GetResult() CONST
{
	return m_bResult;
}

BOOL CTCProcessInterfaceAcknowledgeTelecommandsResponse::Map(CByteArray &nInfo) CONST
{
	TCPIACKNOWLEDGETELECOMMANDSRESPONSE  sData;

	for (CopyMemory(&sData.sHeader, &m_sHeader, sizeof(sData.sHeader)), sData.bResult = m_bResult, nInfo.SetSize(sizeof(TCPIACKNOWLEDGETELECOMMANDSRESPONSE)); nInfo.GetSize() == sizeof(TCPIACKNOWLEDGETELECOMMANDSRESPONSE); )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(TCPIACKNOWLEDGETELECOMMANDSRESPONSE));
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceAcknowledgeTelecommandsResponse::Unmap(CONST CByteArray &nInfo)
{
	TCPIACKNOWLEDGETELECOMMANDSRESPONSE  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(TCPIACKNOWLEDGETELECOMMANDSRESPONSE)) ? sizeof(TCPIACKNOWLEDGETELECOMMANDSRESPONSE) : 0); nInfo.GetSize() == sizeof(TCPIACKNOWLEDGETELECOMMANDSRESPONSE); )
	{
		CopyMemory(&m_sHeader, &sData.sHeader, sizeof(TCPIMESSAGEHEADER));
		m_bResult = sData.bResult;
		return Check();
	}
	return FALSE;
}

BOOL CTCProcessInterfaceAcknowledgeTelecommandsResponse::Check() CONST
{
	return((GetMessageID() == TCPI_ACKNOWLEDGETELECOMMANDSRESPONSE  &&  GetMessageLength() == sizeof(TCPIACKNOWLEDGETELECOMMANDSRESPONSE) - TCPI_MESSAGEIDLENGTH  &&  GetVersion() == TCPI_VERSION) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceDiscardTelecommandsRequest

CTCProcessInterfaceDiscardTelecommandsRequest::CTCProcessInterfaceDiscardTelecommandsRequest() : CTCProcessInterfaceMessageHeader(TCPI_DISCARDTELECOMMANDSREQUEST, sizeof(TCPIMESSAGEHEADER) - TCPI_MESSAGEIDLENGTH)
{
	m_bAcknowledgment = FALSE;
}

BOOL CTCProcessInterfaceDiscardTelecommandsRequest::SetTelecommands(CONST CTCItems &pItems)
{
	CByteArray  nItemsData;

	return((m_pItems.Copy(&pItems) && pItems.Map(nItemsData, TRUE)) ? SetMessageLength(sizeof(TCPIDISCARDTELECOMMANDSREQUEST) - TCPI_MESSAGEIDLENGTH + (UINT)nItemsData.GetSize()) : FALSE);
}

INT CTCProcessInterfaceDiscardTelecommandsRequest::GetTelecommands(CTCItems &pItems) CONST
{
	return((pItems.Copy(&m_pItems)) ? (INT)pItems.GetSize() : -1);
}

BOOL CTCProcessInterfaceDiscardTelecommandsRequest::EnableAcknowledgment(BOOL bEnable)
{
	m_bAcknowledgment = bEnable;
	return TRUE;
}

BOOL CTCProcessInterfaceDiscardTelecommandsRequest::IsAcknowledgmentEnabled() CONST
{
	return m_bAcknowledgment;
}

BOOL CTCProcessInterfaceDiscardTelecommandsRequest::Reset()
{
	m_pItems.RemoveAll();
	m_bAcknowledgment = FALSE;
	return SetMessageLength(sizeof(TCPIDISCARDTELECOMMANDSREQUEST) - TCPI_MESSAGEIDLENGTH);
}

BOOL CTCProcessInterfaceDiscardTelecommandsRequest::Map(CByteArray &nInfo) CONST
{
	CByteArray  nItemsData;
	TCPIDISCARDTELECOMMANDSREQUEST  sData;

	for (CopyMemory(&sData.sHeader, &m_sHeader, sizeof(sData.sHeader)), sData.cbItems = (m_pItems.Map(nItemsData, TRUE)) ? (INT)nItemsData.GetSize() : -1, sData.bAcknowledgment = m_bAcknowledgment, nInfo.SetSize(sizeof(TCPIDISCARDTELECOMMANDSREQUEST) + max(sData.cbItems, 0)); nInfo.GetSize() == sizeof(TCPIDISCARDTELECOMMANDSREQUEST) + sData.cbItems; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(TCPIDISCARDTELECOMMANDSREQUEST));
		CopyMemory(nInfo.GetData() + sizeof(TCPIDISCARDTELECOMMANDSREQUEST), nItemsData.GetData(), sData.cbItems);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceDiscardTelecommandsRequest::Unmap(CONST CByteArray &nInfo)
{
	CByteArray  nItemsData;
	TCPIDISCARDTELECOMMANDSREQUEST  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(TCPIDISCARDTELECOMMANDSREQUEST)) ? sizeof(TCPIDISCARDTELECOMMANDSREQUEST) : 0); nInfo.GetSize() == sizeof(TCPIDISCARDTELECOMMANDSREQUEST) + sData.cbItems && sData.cbItems >= 0; )
	{
		for (CopyMemory(&m_sHeader, &sData.sHeader, sizeof(TCPIMESSAGEHEADER)), nItemsData.SetSize(sData.cbItems), CopyMemory(nItemsData.GetData(), nInfo.GetData() + sizeof(TCPIDISCARDTELECOMMANDSREQUEST), sData.cbItems), m_bAcknowledgment = sData.bAcknowledgment; m_pItems.Unmap(nItemsData, TRUE); ) return Check(sData.cbItems);
		break;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceDiscardTelecommandsRequest::Check(INT cbData) CONST
{
	return((GetMessageID() == TCPI_DISCARDTELECOMMANDSREQUEST  &&  GetMessageLength() == sizeof(TCPIDISCARDTELECOMMANDSREQUEST) - TCPI_MESSAGEIDLENGTH + cbData  &&  GetVersion() == TCPI_VERSION) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceDiscardTelecommandsResponse

CTCProcessInterfaceDiscardTelecommandsResponse::CTCProcessInterfaceDiscardTelecommandsResponse() : CTCProcessInterfaceMessageHeader(TCPI_DISCARDTELECOMMANDSRESPONSE, sizeof(TCPIDISCARDTELECOMMANDSRESPONSE) - TCPI_MESSAGEIDLENGTH)
{
	m_bResult = FALSE;
}

BOOL CTCProcessInterfaceDiscardTelecommandsResponse::SetResult(BOOL bSuccess)
{
	m_bResult = bSuccess;
	return TRUE;
}

BOOL CTCProcessInterfaceDiscardTelecommandsResponse::GetResult() CONST
{
	return m_bResult;
}

BOOL CTCProcessInterfaceDiscardTelecommandsResponse::Map(CByteArray &nInfo) CONST
{
	TCPIDISCARDTELECOMMANDSRESPONSE  sData;

	for (CopyMemory(&sData.sHeader, &m_sHeader, sizeof(sData.sHeader)), sData.bResult = m_bResult, nInfo.SetSize(sizeof(TCPIDISCARDTELECOMMANDSRESPONSE)); nInfo.GetSize() == sizeof(TCPIDISCARDTELECOMMANDSRESPONSE); )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(TCPIDISCARDTELECOMMANDSRESPONSE));
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceDiscardTelecommandsResponse::Unmap(CONST CByteArray &nInfo)
{
	TCPIDISCARDTELECOMMANDSRESPONSE  sData;

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(TCPIDISCARDTELECOMMANDSRESPONSE)) ? sizeof(TCPIDISCARDTELECOMMANDSRESPONSE) : 0); nInfo.GetSize() == sizeof(TCPIDISCARDTELECOMMANDSRESPONSE); )
	{
		CopyMemory(&m_sHeader, &sData.sHeader, sizeof(TCPIMESSAGEHEADER));
		m_bResult = sData.bResult;
		return Check();
	}
	return FALSE;
}

BOOL CTCProcessInterfaceDiscardTelecommandsResponse::Check() CONST
{
	return((GetMessageID() == TCPI_DISCARDTELECOMMANDSRESPONSE  &&  GetMessageLength() == sizeof(TCPIDISCARDTELECOMMANDSRESPONSE) - TCPI_MESSAGEIDLENGTH  &&  GetVersion() == TCPI_VERSION) ? TRUE : FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceSocket

IMPLEMENT_DYNCREATE(CTCProcessInterfaceSocket, CSocket)

CTCProcessInterfaceSocket::CTCProcessInterfaceSocket(CTCProcessInterfaceThread *pThread) : CSocket()
{
	m_nFlags = TCSERVICE_COMMANDINTERFACE_NOUPDATE;
	m_hIOData = (HANDLE)NULL;
	m_nTimerID = 0;
	m_tTimeout = 0;
	m_pTCProcessInterfaceThread = pThread;
}

CTCProcessInterfaceSocket::~CTCProcessInterfaceSocket()
{
	Close();
}

BOOL CTCProcessInterfaceSocket::Open(CTCProcessInterfaceThread *pThread, UINT nPort, HANDLE hAbort)
{
	for (Close(), m_pTCProcessInterfaceThread = pThread, m_hIOData = hAbort; Create(nPort); )
	{
		if (nPort == 0 || Listen()) return TRUE;
		Close(TRUE);
		break;
	}
	return FALSE;
}

void CTCProcessInterfaceSocket::Close(BOOL bDetach)
{
	CTCProcessInterfaceThread  *pThread;

	for (CAsyncSocket::Close(), m_szComputer.Empty(), m_nData[0].RemoveAll(), m_nData[1].RemoveAll(); m_nTimerID != 0; )
	{
		KillTimer((HWND)NULL, m_nTimerID);
		m_nTimerID = 0;
		break;
	}
	if ((pThread = m_pTCProcessInterfaceThread))
	{
		for (m_pTCProcessInterfaceThread = (CTCProcessInterfaceThread *)NULL; !bDetach; )
		{
			pThread->UpdateCommandSources();
			break;
		}
	}
}

VOID CTCProcessInterfaceSocket::Connect(LPCTSTR pszComputer)
{
	m_szComputer = pszComputer;
}
BOOL CTCProcessInterfaceSocket::Connect(LPCTSTR pszComputer, UINT nPort, CONST CTimeSpan &tTimeout)
{
	if ((m_nTimerID = SetTimer((HWND)NULL, TCPROCESSINTERFACESOCKET_CONNECTION_TIMERID, (UINT)max(1000 * tTimeout.GetTotalSeconds(), TCPROCESSINTERFACESOCKET_CONNECTION_TIMEOUT), NULL)))
	{
		if (CSocket::Connect(pszComputer, nPort))
		{
			m_szComputer = pszComputer;
			return TRUE;
		}
		KillTimer((HWND)NULL, m_nTimerID);
		m_nTimerID = 0;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceSocket::IsConnected(CString &szComputer) CONST
{
	szComputer = m_szComputer;
	return IsConnected();
}
BOOL CTCProcessInterfaceSocket::IsConnected() CONST
{
	return !m_szComputer.IsEmpty();
}

BOOL CTCProcessInterfaceSocket::Send(CONST CByteArray &nData)
{
	INT  cbData[2];
	CTimeKey  tData;
	CONST BYTE  *pData;
	HANDLE  hData[1] = { m_hIOData };

	for (pData = nData.GetData(), cbData[0] = 0; cbData[0] < (INT)nData.GetSize(); cbData[0] += cbData[1])
	{
		while ((cbData[1] = CAsyncSocket::Send(pData + cbData[0], (INT)(nData.GetSize() - cbData[0]))) == SOCKET_ERROR)
		{
			if (GetLastError() == WSAEWOULDBLOCK  &&  CTime::GetCurrentTime().GetTime() - tData.GetTime() <= m_tTimeout.GetTotalSeconds() && Wait(hData, sizeof(hData) / sizeof(HANDLE), 0) == WAIT_TIMEOUT) continue;
			break;
		}
		if (cbData[1] == SOCKET_ERROR) break;
	}
	return((cbData[0] == (INT)nData.GetSize()) ? TRUE : FALSE);
}

INT CTCProcessInterfaceSocket::SendAndReceive(CByteArray &nData, CONST CTimeSpan &tInterval)
{
	HANDLE  hData[2] = { m_cIOData,m_hIOData };

	if (Send(nData))
	{
		for (nData.RemoveAll(), m_cIOData.ResetEvent(); Wait(hData, sizeof(hData) / sizeof(HANDLE), (DWORD)(1000 * tInterval.GetTotalSeconds())) == WAIT_OBJECT_0 + 1; ) return Receive(nData);
		return 0;
	}
	return SOCKET_ERROR;
}

INT CTCProcessInterfaceSocket::Receive(CByteArray &nData)
{
	nData.Copy(m_nData[1]);
	m_nData[1].RemoveAll();
	return((INT)nData.GetSize());
}

BOOL CTCProcessInterfaceSocket::SetCommandSources(CONST CTCProcessCommandSources &pCommandSources)
{
	return m_pCommandSources.Copy(&pCommandSources);
}

BOOL CTCProcessInterfaceSocket::GetCommandSources(CTCProcessCommandSources &pCommandSources) CONST
{
	return pCommandSources.Copy(&m_pCommandSources);
}

VOID CTCProcessInterfaceSocket::SetFlags(UINT nFlags)
{
	m_nFlags = nFlags;
}

UINT CTCProcessInterfaceSocket::GetFlags() CONST
{
	return m_nFlags;
}

DWORD CTCProcessInterfaceSocket::Wait(LPHANDLE hEvents, INT nCount, DWORD dwTimeout)
{
	return((m_pTCProcessInterfaceThread) ? ((m_pTCProcessInterfaceThread->GetThreadID() == GetCurrentThreadId()) ? m_pTCProcessInterfaceThread->Wait(hEvents, nCount, FALSE, dwTimeout, FALSE) : WaitForMultipleObjects(nCount, hEvents, FALSE, dwTimeout)) : (DWORD)-1);
}

/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceSocket member functions

BOOL CTCProcessInterfaceSocket::OnMessagePending()
{
	MSG  sMsg;

	while (PeekMessage(&sMsg, (HWND)NULL, WM_TIMER, WM_TIMER, PM_REMOVE))
	{
		if (m_nTimerID == (UINT_PTR)sMsg.wParam)
		{
			for (; !IsConnected(); )
			{
				CancelBlockingCall();
				break;
			}
			KillTimer((HWND)NULL, m_nTimerID);
			m_nTimerID = 0;
			continue;
		}
		if (!AfxPreTranslateMessage(&sMsg))
		{
			TranslateMessage(&sMsg);
			DispatchMessage(&sMsg);
		}
	}
	return CSocket::OnMessagePending();
}

void CTCProcessInterfaceSocket::OnAccept(int nErrorCode)
{
	CTCProcessInterfaceSocket  *pSocket;

	if ((pSocket = new CTCProcessInterfaceSocket(m_pTCProcessInterfaceThread)))
	{
		for (pSocket->m_hIOData = m_hIOData; Accept(*pSocket) && m_pTCProcessInterfaceThread->AddClient(pSocket); ) return;
		pSocket->Close(TRUE);
		delete pSocket;
	}
}

void CTCProcessInterfaceSocket::OnReceive(int nErrorCode)
{
	INT  cbData;
	UINT  nMode;
	UINT  nState;
	UINT  nFlags;
	BOOL  bAll;
	BOOL  bUndo;
	BOOL  bUpdate;
	BOOL  bMode[3];
	CTCItem  cItem;
	CString  szFileName;
	CTCItems  pItems[2];
	CByteArray  nData[2];
	CTimeSpan  tTimeWindow[2];
	CTimeSpan  tTimePeriod[2];
	CTCInterlocks  pInterlocks;
	CTCUplinkDevice  cDevice;
	CTCOnBoardBufferQueues  pQueues;
	CHistoryStoreFiles  pHistoryFiles[2];
	CTCProcessCommandSources  pCommandSources;
	CTCProcessInterfaceMessageHeader  cMessageHeader;
	CTCProcessInterfaceExecuteTelecommandRequest  cExecuteTelecommandRequestMessage;
	CTCProcessInterfaceExecuteTelecommandResponse   cExecuteTelecommandResponseMessage;
	CTCProcessInterfaceReleaseTelecommandsRequest  cReleaseTelecommandsRequestMessage;
	CTCProcessInterfaceReleaseTelecommandsResponse   cReleaseTelecommandsResponseMessage;
	CTCProcessInterfaceDiscardTelecommandsRequest  cDiscardTelecommandsRequestMessage;
	CTCProcessInterfaceDiscardTelecommandsResponse   cDiscardTelecommandsResponseMessage;
	CTCProcessInterfaceDispatchTelecommandsRequest  cDispatchTelecommandsRequestMessage;
	CTCProcessInterfaceDispatchTelecommandsResponse   cDispatchTelecommandsResponseMessage;
	CTCProcessInterfaceAcknowledgeTelecommandsRequest  cAcknowledgeTelecommandsRequestMessage;
	CTCProcessInterfaceAcknowledgeTelecommandsResponse   cAcknowledgeTelecommandsResponseMessage;
	CTCProcessInterfaceUpdateCommandSourcesRequest  cUpdateCommandSourcesRequestMessage;
	CTCProcessInterfaceUpdateCommandSourcesResponse  cUpdateCommandSourcesResponseMessage;
	CTCProcessInterfaceRegisterCommandSourcesRequest  cRegisterCommandSourcesRequestMessage;
	CTCProcessInterfaceRegisterCommandSourcesResponse  cRegisterCommandSourcesResponseMessage;
	CTCProcessInterfaceUpdateCommandSourcesContentsRequest  cUpdateCommandSourcesContentsRequestMessage;
	CTCProcessInterfaceUpdateCommandSourcesContentsResponse   cUpdateCommandSourcesContentsResponseMessage;
	CTCProcessInterfaceSetCommandHandlerConfigurationRequest  cSetCommandHandlerConfigurationRequestMessage;
	CTCProcessInterfaceSetCommandHandlerConfigurationResponse  cSetCommandHandlerConfigurationResponseMessage;
	CTCProcessInterfaceGetCommandHandlerConfigurationRequest  cGetCommandHandlerConfigurationRequestMessage;
	CTCProcessInterfaceGetCommandHandlerConfigurationResponse  cGetCommandHandlerConfigurationResponseMessage;
	CTCProcessInterfaceUpdateCommandUplinkDeviceState  cUpdateCommandUplinkDeviceStateMessage;

	for (nData[0].SetSize((m_nData[0].GetSize() < sizeof(CTCProcessInterfaceMessageHeader::TCPIMESSAGEHEADER)) ? (sizeof(CTCProcessInterfaceMessageHeader::TCPIMESSAGEHEADER) - m_nData[0].GetSize()) : 0); cMessageHeader.Unmap(m_nData[0]); )
	{
		nData[0].SetSize(max((INT)(TCPI_MESSAGEIDLENGTH + cMessageHeader.GetMessageLength() - m_nData[0].GetSize()), 0));
		break;
	}
	if (!nData[0].GetSize())
	{
		m_nData[0].RemoveAll();
		return;
	}
	switch ((cbData = CSocket::Receive(nData[0].GetData(), (INT)nData[0].GetSize())))
	{
	case 0:
	case SOCKET_ERROR:
	{ Close();
	break;
	}
	default:
	{ for (nData[0].SetSize(cbData), m_nData[0].Append(nData[0]); cMessageHeader.Unmap(m_nData[0]); )
	{
		if (m_nData[0].GetSize() == TCPI_MESSAGEIDLENGTH + cMessageHeader.GetMessageLength())
		{
			if (cMessageHeader.GetMessageID() == TCPI_SETCOMMANDHANDLERCONFIGURATIONREQUEST)
			{
				for (; cSetCommandHandlerConfigurationResponseMessage.SetResult(cSetCommandHandlerConfigurationRequestMessage.Unmap(m_nData[0]) && cSetCommandHandlerConfigurationRequestMessage.GetConfiguration(pCommandSources, nMode, nState, nFlags, bMode[0], bMode[1], bMode[2], tTimeWindow[0], tTimePeriod[0], tTimePeriod[1], tTimeWindow[1], pHistoryFiles[0], pHistoryFiles[1], szFileName) && m_pTCProcessInterfaceThread->SetCommandHandlerConfiguration(m_szComputer, pCommandSources, nMode, nState, nFlags, bMode[0], bMode[1], bMode[2], tTimeWindow[0], tTimePeriod[0], tTimePeriod[1], tTimeWindow[1], pHistoryFiles[0], pHistoryFiles[1], szFileName, cSetCommandHandlerConfigurationRequestMessage.IsUpdateFlagEnabled())) && cSetCommandHandlerConfigurationResponseMessage.Map(nData[1]) && Send(nData[1]); )
				{
					nData[1].RemoveAll();
					break;
				}
			}
			if (cMessageHeader.GetMessageID() == TCPI_SETCOMMANDHANDLERCONFIGURATIONRESPONSE)
			{
				m_nData[1].Copy(m_nData[0]);
				m_cIOData.SetEvent();
			}
			if (cMessageHeader.GetMessageID() == TCPI_GETCOMMANDHANDLERCONFIGURATIONREQUEST)
			{
				for (; cGetCommandHandlerConfigurationRequestMessage.Unmap(m_nData[0]) && m_pTCProcessInterfaceThread->GetCommandHandlerConfiguration(m_szComputer, pCommandSources, nMode, nState, nFlags, bMode[0], bMode[1], bMode[2], tTimeWindow[0], tTimePeriod[0], tTimePeriod[1], tTimeWindow[1], pItems[0], pInterlocks, pHistoryFiles[0], pHistoryFiles[1], szFileName, (bUpdate = cGetCommandHandlerConfigurationRequestMessage.IsUpdateFlagEnabled())) && cGetCommandHandlerConfigurationResponseMessage.SetConfiguration(pCommandSources, nMode, nState, nFlags, bMode[0], bMode[1], bMode[2], tTimeWindow[0], tTimePeriod[0], tTimePeriod[1], tTimeWindow[1], pItems[0], pInterlocks, pHistoryFiles[0], pHistoryFiles[1], szFileName) && cGetCommandHandlerConfigurationResponseMessage.EnableUpdateFlag(bUpdate) && cGetCommandHandlerConfigurationResponseMessage.Map(nData[1]) && Send(nData[1]); )
				{
					nData[1].RemoveAll();
					break;
				}
			}
			if (cMessageHeader.GetMessageID() == TCPI_GETCOMMANDHANDLERCONFIGURATIONRESPONSE)
			{
				m_nData[1].Copy(m_nData[0]);
				m_cIOData.SetEvent();
			}
			if (cMessageHeader.GetMessageID() == TCPI_REGISTERCOMMANDSOURCESREQUEST)
			{
				for (; cRegisterCommandSourcesRequestMessage.Unmap(m_nData[0]); )
				{
					if (cRegisterCommandSourcesRequestMessage.GetCommandSources(pCommandSources, pItems[0], pItems[1], pInterlocks, pQueues))
					{
						for (m_pTCProcessInterfaceThread->GetCommandHandlerState(&cDevice); m_pTCProcessInterfaceThread->UpdateCommandSources(pCommandSources) && cRegisterCommandSourcesResponseMessage.SetCommandSources(pCommandSources) && cRegisterCommandSourcesResponseMessage.SetCommandingDevice(&cDevice) && cRegisterCommandSourcesResponseMessage.SetTelecommands(pItems[0], pItems[1]) && cRegisterCommandSourcesResponseMessage.SetTCInterlocks(pInterlocks) && cRegisterCommandSourcesResponseMessage.SetTCOnBoardBufferQueues(pQueues) && cRegisterCommandSourcesResponseMessage.Map(nData[1]) && Send(nData[1]); )
						{
							for (SetCommandSources(pCommandSources); m_pTCProcessInterfaceThread->SetCommandHandlerContents(pItems[0], pItems[1], pInterlocks, pQueues); ) break;
							break;
						}
						break;
					}
					if (cRegisterCommandSourcesRequestMessage.GetCommandSources(pCommandSources))
					{
						for (m_pTCProcessInterfaceThread->GetCommandHandlerState(&cDevice); m_pTCProcessInterfaceThread->UpdateCommandSources(pCommandSources, pItems[0], pItems[1], pInterlocks, pQueues) && cRegisterCommandSourcesResponseMessage.SetCommandSources(pCommandSources) && cRegisterCommandSourcesResponseMessage.SetCommandingDevice(&cDevice) && cRegisterCommandSourcesResponseMessage.SetTelecommands(pItems[0], pItems[1]) && cRegisterCommandSourcesResponseMessage.SetTCInterlocks(pInterlocks) && cRegisterCommandSourcesResponseMessage.SetTCOnBoardBufferQueues(pQueues) && cRegisterCommandSourcesResponseMessage.Map(nData[1]) && Send(nData[1]); )
						{
							SetCommandSources(pCommandSources);
							break;
						}
					}
					break;
				}
			}
			if (cMessageHeader.GetMessageID() == TCPI_REGISTERCOMMANDSOURCESRESPONSE)
			{
				m_nData[1].Copy(m_nData[0]);
				m_cIOData.SetEvent();
			}
			if (cMessageHeader.GetMessageID() == TCPI_UPDATECOMMANDSOURCESREQUEST)
			{
				if (cUpdateCommandSourcesRequestMessage.Unmap(m_nData[0]) && cUpdateCommandSourcesRequestMessage.GetCommandSources(pCommandSources) >= 0)
				{
					if (m_pTCProcessInterfaceThread->UpdateCommandSources(pCommandSources, FALSE) && cUpdateCommandSourcesResponseMessage.SetCommandSources(pCommandSources) && cUpdateCommandSourcesResponseMessage.Map(nData[1]) && Send(nData[1]))
					{
						m_pTCProcessInterfaceThread->UpdateCommandSources(m_szComputer, pCommandSources);
						SetCommandSources(pCommandSources);
					}
				}
			}
			if (cMessageHeader.GetMessageID() == TCPI_UPDATECOMMANDSOURCESRESPONSE)
			{
				if (cUpdateCommandSourcesResponseMessage.Unmap(m_nData[0]) && cUpdateCommandSourcesResponseMessage.GetCommandSources(pCommandSources) >= 0)
				{
					m_pTCProcessInterfaceThread->UpdateCommandSources(m_szComputer, pCommandSources);
					SetCommandSources(pCommandSources);
				}
			}
			if (cMessageHeader.GetMessageID() == TCPI_UPDATECOMMANDSOURCESCONTENTSREQUEST)
			{
				for (; cUpdateCommandSourcesContentsResponseMessage.SetResult(cUpdateCommandSourcesContentsRequestMessage.Unmap(m_nData[0]) && (cUpdateCommandSourcesContentsRequestMessage.GetTelecommands(pItems[0], bAll) < 0 || m_pTCProcessInterfaceThread->UpdateTelecommands(m_szComputer, pItems[0], bAll)) && (cUpdateCommandSourcesContentsRequestMessage.GetTCInterlocks(pInterlocks, bAll) < 0 || m_pTCProcessInterfaceThread->UpdateTCInterlocks(m_szComputer, pInterlocks, bAll)) && (cUpdateCommandSourcesContentsRequestMessage.GetTCOnBoardBufferQueues(pQueues, bAll) < 0 || m_pTCProcessInterfaceThread->UpdateTCOnBoardBufferQueues(m_szComputer, pQueues, bAll)) && (!cUpdateCommandSourcesContentsRequestMessage.IsAcknowledgmentEnabled() || (cUpdateCommandSourcesContentsResponseMessage.Map(nData[1]) && Send(nData[1])))); )
				{
					nData[1].RemoveAll();
					break;
				}
			}
			if (cMessageHeader.GetMessageID() == TCPI_UPDATECOMMANDSOURCESCONTENTSRESPONSE)
			{
				m_nData[1].Copy(m_nData[0]);
				m_cIOData.SetEvent();
			}
			if (cMessageHeader.GetMessageID() == TCPI_UPDATECOMMANDUPLINKDEVICESTATE)
			{
				for (; cUpdateCommandUplinkDeviceStateMessage.Unmap(m_nData[0]) && cUpdateCommandUplinkDeviceStateMessage.GetCommandingDevice(&cDevice); )
				{
					m_pTCProcessInterfaceThread->SetCommandHandlerState(&cDevice);
					break;
				}
			}
			if (cMessageHeader.GetMessageID() == TCPI_DISPATCHTELECOMMANDSREQUEST)
			{
				for (; cDispatchTelecommandsResponseMessage.SetResult(cDispatchTelecommandsRequestMessage.Unmap(m_nData[0]) && cDispatchTelecommandsRequestMessage.GetTelecommands(pItems[0], bUndo) && m_pTCProcessInterfaceThread->DispatchTelecommands(pItems[0], bUndo)) && (!cDispatchTelecommandsRequestMessage.IsAcknowledgmentEnabled() || (cDispatchTelecommandsResponseMessage.Map(nData[1]) && Send(nData[1]))); )
				{
					nData[1].RemoveAll();
					break;
				}
			}
			if (cMessageHeader.GetMessageID() == TCPI_DISPATCHTELECOMMANDSRESPONSE)
			{
				m_nData[1].Copy(m_nData[0]);
				m_cIOData.SetEvent();
			}
			if (cMessageHeader.GetMessageID() == TCPI_RELEASETELECOMMANDSREQUEST)
			{
				for (; cReleaseTelecommandsResponseMessage.SetResult(cReleaseTelecommandsRequestMessage.Unmap(m_nData[0]) && cReleaseTelecommandsRequestMessage.GetTelecommands(pItems[0]) && m_pTCProcessInterfaceThread->ReleaseTelecommands(pItems[0])) && (!cReleaseTelecommandsRequestMessage.IsAcknowledgmentEnabled() || (cReleaseTelecommandsResponseMessage.Map(nData[1]) && Send(nData[1]))); )
				{
					nData[1].RemoveAll();
					break;
				}
			}
			if (cMessageHeader.GetMessageID() == TCPI_RELEASETELECOMMANDSRESPONSE)
			{
				m_nData[1].Copy(m_nData[0]);
				m_cIOData.SetEvent();
			}
			if (cMessageHeader.GetMessageID() == TCPI_EXECUTETELECOMMANDREQUEST)
			{
				for (; cExecuteTelecommandResponseMessage.SetResult(cExecuteTelecommandRequestMessage.Unmap(m_nData[0]) && cExecuteTelecommandRequestMessage.GetTelecommand(&cItem) && m_pTCProcessInterfaceThread->ExecuteTelecommand(m_szComputer, &cItem)) && (!cExecuteTelecommandRequestMessage.IsAcknowledgmentEnabled() || (cExecuteTelecommandResponseMessage.Map(nData[1]) && Send(nData[1]))); )
				{
					nData[1].RemoveAll();
					break;
				}
			}
			if (cMessageHeader.GetMessageID() == TCPI_EXECUTETELECOMMANDRESPONSE)
			{
				m_nData[1].Copy(m_nData[0]);
				m_cIOData.SetEvent();
			}
			if (cMessageHeader.GetMessageID() == TCPI_ACKNOWLEDGETELECOMMANDSREQUEST)
			{
				for (; cAcknowledgeTelecommandsResponseMessage.SetResult(cAcknowledgeTelecommandsRequestMessage.Unmap(m_nData[0]) && cAcknowledgeTelecommandsRequestMessage.GetTelecommands(pItems[0]) && m_pTCProcessInterfaceThread->AcknowledgeTelecommands(pItems[0])) && (!cAcknowledgeTelecommandsRequestMessage.IsAcknowledgmentEnabled() || (cAcknowledgeTelecommandsResponseMessage.Map(nData[1]) && Send(nData[1]))); )
				{
					nData[1].RemoveAll();
					break;
				}
			}
			if (cMessageHeader.GetMessageID() == TCPI_ACKNOWLEDGETELECOMMANDSRESPONSE)
			{
				m_nData[1].Copy(m_nData[0]);
				m_cIOData.SetEvent();
			}
			if (cMessageHeader.GetMessageID() == TCPI_DISCARDTELECOMMANDSREQUEST)
			{
				for (; cDiscardTelecommandsResponseMessage.SetResult(cDiscardTelecommandsRequestMessage.Unmap(m_nData[0]) && cDiscardTelecommandsRequestMessage.GetTelecommands(pItems[0]) && m_pTCProcessInterfaceThread->DiscardTelecommands(pItems[0])) && (!cDiscardTelecommandsRequestMessage.IsAcknowledgmentEnabled() || (cDiscardTelecommandsResponseMessage.Map(nData[1]) && Send(nData[1]))); )
				{
					nData[1].RemoveAll();
					break;
				}
			}
			if (cMessageHeader.GetMessageID() == TCPI_DISCARDTELECOMMANDSRESPONSE)
			{
				m_nData[1].Copy(m_nData[0]);
				m_cIOData.SetEvent();
			}
			m_nData[0].RemoveAll();
			break;
		}
		for (nData[0].SetSize(max((INT)(TCPI_MESSAGEIDLENGTH + cMessageHeader.GetMessageLength() - m_nData[0].GetSize()), 0)); (cbData = (nData[0].GetSize() > 0) ? CSocket::Receive(nData[0].GetData(), (INT)nData[0].GetSize()) : 0) > 0; )
		{
			nData[0].SetSize((INT_PTR)cbData);
			m_nData[0].Append(nData[0]);
			break;
		}
		if (!cbData)
		{
			m_nData[0].RemoveAll();
			break;
		}
	}
	break;
	}
	}
}

void CTCProcessInterfaceSocket::OnClose(int nErrorCode)
{
	if (m_pTCProcessInterfaceThread) m_pTCProcessInterfaceThread->UpdateCommandSources(this);
	Close();
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceSockets

CTCProcessInterfaceSockets::CTCProcessInterfaceSockets() : CPtrArray()
{
	return;
}

CTCProcessInterfaceSockets::~CTCProcessInterfaceSockets()
{
	RemoveAll();
}

INT CTCProcessInterfaceSockets::Add(CTCProcessInterfaceSocket *pSocket)
{
	INT  nIndex;
	CString  szComputer;

	if ((nIndex = (pSocket->IsConnected(szComputer)) ? FindIndex(szComputer, TRUE) : -1) >= 0) CPtrArray::InsertAt(nIndex, pSocket, 1);
	return nIndex;
}

INT CTCProcessInterfaceSockets::Find(LPCTSTR pszComputer) CONST
{
	return FindIndex(pszComputer);
}

CTCProcessInterfaceSocket *CTCProcessInterfaceSockets::GetAt(INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCProcessInterfaceSocket *)CPtrArray::GetAt(nIndex) : (CTCProcessInterfaceSocket *)NULL);
}

CTCProcessInterfaceSocket *CTCProcessInterfaceSockets::operator[](INT nIndex) CONST
{
	return((nIndex >= 0 && nIndex < GetSize()) ? (CTCProcessInterfaceSocket *)CPtrArray::GetAt(nIndex) : (CTCProcessInterfaceSocket *)NULL);
}

VOID CTCProcessInterfaceSockets::RemoveAll()
{
	INT  nSocket;
	INT  nSockets;
	CTCProcessInterfaceSocket  *pSocket;

	for (nSocket = 0, nSockets = (INT)GetSize(); nSocket < nSockets; nSocket++)
	{
		if ((pSocket = GetAt(nSocket)))
		{
			pSocket->Close(TRUE);
			delete pSocket;
			continue;
		}
	}
	CPtrArray::RemoveAll();
}

INT CTCProcessInterfaceSockets::FindIndex(LPCTSTR pszComputer, BOOL bInsert) CONST
{
	INT  nIndex[2];
	INT  nMinIndex;
	INT  nMaxIndex;
	CString  szComputer;
	CTCProcessInterfaceSocket  *pSocket;

	for (nMinIndex = 0, nMaxIndex = (INT)GetSize(), nIndex[0] = (nMinIndex + nMaxIndex) / 2; nMinIndex != nMaxIndex; nIndex[0] = (nMinIndex + nMaxIndex) / 2)
	{
		nMinIndex = ((pSocket = GetAt(nIndex[0])) && pSocket->IsConnected(szComputer)) ? ((nIndex[1] = (szComputer.CompareNoCase(pszComputer) <= 0) ? (nIndex[0] + 1) : nMinIndex)) : (nIndex[0] = -1);
		nMaxIndex = (nIndex[0] < 0 || !nIndex[1]) ? nIndex[0] : nMaxIndex;
	}
	return(((!bInsert && (pSocket = GetAt((nIndex[0] = max(nIndex[0] - 1, 0)))) && pSocket->IsConnected(szComputer) && !szComputer.CompareNoCase(pszComputer)) || (bInsert && (((pSocket = GetAt(max(nIndex[0] - 1, 0))) && pSocket->IsConnected(szComputer) && szComputer.CompareNoCase(pszComputer) && (pSocket = GetAt((INT)min(nIndex[0], GetUpperBound()))) && pSocket->IsConnected(szComputer) && szComputer.CompareNoCase(pszComputer)) || !GetSize()))) ? nIndex[0] : -1);
}


/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfacePipeThread

IMPLEMENT_DYNAMIC(CTCProcessInterfacePipeThread, CThread)

CTCProcessInterfacePipeThread::CTCProcessInterfacePipeThread() : CThread()
{
	m_hPipe = (HANDLE)NULL;
	m_hEvent = (HANDLE)NULL;
	m_pTCProcessInterfaceThread = (CTCProcessInterfaceThread *)NULL;
}

BOOL CTCProcessInterfacePipeThread::Start(CTCProcessInterfaceThread *pThread, LPCTSTR pszCommandHandler, BOOL bExclusive)
{
	for (Stop(), m_pTCProcessInterfaceThread = pThread, m_szCommandHandler = pszCommandHandler, m_bExclusive = bExclusive; CreateThread((LPVOID)NULL, THREAD_PRIORITY_ABOVE_NORMAL); ) return TRUE;
	return FALSE;
}

BOOL CTCProcessInterfacePipeThread::Stop()
{
	return((DestroyThread() >= 0) ? TRUE : FALSE);
}

BOOL CTCProcessInterfacePipeThread::InitInstance()
{
	return(((m_hPipe = ((m_hEvent = CreateEvent((LPSECURITY_ATTRIBUTES)NULL, TRUE, FALSE, (LPCTSTR)NULL))) ? CreateNamedPipe(STRING(IDS_TELECOMMANDPROCESSINTERFACE_PIPE_NAME), PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, 1, 0, 0, NMPWAIT_USE_DEFAULT_WAIT, (LPSECURITY_ATTRIBUTES)NULL) : (HANDLE)NULL)) ? TRUE : FALSE);
}

int CTCProcessInterfacePipeThread::ExitInstance()
{
	if (m_hPipe != (HANDLE)NULL)
	{
		CloseHandle(m_hPipe);
		m_hPipe = (HANDLE)NULL;
	}
	if (m_hEvent != (HANDLE)NULL)
	{
		CloseHandle(m_hEvent);
		m_hEvent = (HANDLE)NULL;
	}
	return CThread::ExitInstance();
}

BOOL CTCProcessInterfacePipeThread::TransactMessage(CONST CByteArray &nOutData, CByteArray &nInData)
{
	DWORD  cbData[2];

	for (nInData.SetSize(10 * nOutData.GetSize()); ReadFile(m_hPipe, nInData.GetData(), (DWORD)nInData.GetSize(), &cbData[0], (LPOVERLAPPED)NULL); )
	{
		nInData.SetSize(cbData[0]);
		break;
	}
	return((WriteFile(m_hPipe, nOutData.GetData(), (DWORD)nOutData.GetSize(), &cbData[1], (LPOVERLAPPED)NULL)) ? (cbData[0] == nInData.GetSize() && cbData[1] == nOutData.GetSize()) : FALSE);
}

int CTCProcessInterfacePipeThread::Run()
{
	CByteArray  nMessageData[2];
	CTCProcessInterfaceAnnounceCommandHandlerRequest  cAnnounceCommandHandlerRequestMessage;
	CTCProcessInterfaceAnnounceCommandHandlerResponse  cAnnounceCommandHandlerResponseMessage;
	OVERLAPPED  sOverlapped = { 0 };

	for (cAnnounceCommandHandlerResponseMessage.SetCommandHandler(m_szCommandHandler, m_bExclusive), cAnnounceCommandHandlerResponseMessage.Map(nMessageData[0]), sOverlapped.hEvent = m_hEvent; ConnectNamedPipe(m_hPipe, &sOverlapped) || (GetLastError() == ERROR_PIPE_CONNECTED && SetEvent(sOverlapped.hEvent)) || GetLastError() == ERROR_IO_PENDING; )
	{
		while (Wait(sOverlapped.hEvent, FALSE, INFINITE) == WAIT_OBJECT_0 + 1)
		{
			if (TransactMessage(nMessageData[0], nMessageData[1]))
			{
				for (; cAnnounceCommandHandlerRequestMessage.Unmap(nMessageData[1]); )
				{
					m_pTCProcessInterfaceThread->UpdateCommandHandler(cAnnounceCommandHandlerRequestMessage.GetCommandHandler(), cAnnounceCommandHandlerRequestMessage.IsExclusiveCommandHandler());
					break;
				}
			}
			for (FlushFileBuffers(m_hPipe), DisconnectNamedPipe(m_hPipe); TRUE; )
			{
				ResetEvent(sOverlapped.hEvent);
				break;
			}
			if (!ConnectNamedPipe(m_hPipe, &sOverlapped) && GetLastError() != ERROR_PIPE_CONNECTED  &&  GetLastError() != ERROR_IO_PENDING) break;
		}
		break;
	}
	return ExitInstance();
}

BEGIN_MESSAGE_MAP(CTCProcessInterfacePipeThread, CThread)
	//{{AFX_MSG_MAP(CTCProcessInterfacePipeThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfacePipeThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceThread

IMPLEMENT_DYNAMIC(CTCProcessInterfaceThread, CThread)

CTCProcessInterfaceThread::CTCProcessInterfaceThread(CTCProcessThread *pThread) : CThread()
{
	m_pTCProcessThread = pThread;
	m_hCommandHandlerWnd = (HWND)NULL;
	m_nCommandHandlerPort = TCSERVICE_COMMANDINTERFACE_DEFAULTPORT;
	m_tCommandHandlerTimeout = TCSERVICE_COMMANDINTERFACE_DEFAULTTIMEOUT;
	m_nCommandHandlerBufferSize = TCSERVICE_COMMANDINTERFACE_DEFAULTBUFFERSIZE;
	m_nCommandHandlerTelecommandingMode = 0;
	m_nCommandHandlerTelecommandingState = 0;
	m_nCommandHandlerTelecommandingFlags = 0;
	m_bCommandHandlerTelecommandingInterlockMode = TRUE;
	m_bCommandHandlerTelecommandingReleaseWaitMode = FALSE;
	m_bCommandHandlerTelecommandingAutoRejectionMode = FALSE;
	m_tCommandHandlerTimeWindow[0] = TCSERVICE_COMMANDHANDLERTIMEWINDOW_VERIFICATIONUNCERTAINTYINTERVAL;
	m_tCommandHandlerTimeWindow[1] = TCSERVICE_COMMANDHANDLERTIMEWINDOW_DEFAULTRELEASEINTERVAL;
	m_bCommandHandlerExclusive = TRUE;
	m_bCommandHandlerUpdate = FALSE;
	m_nCommandHandlerTimerID[0] = 0;
	m_nCommandHandlerTimerID[1] = 0;
	m_nCommandHandlerTimerID[2] = 0;
	m_nCommandHandlerOptions = 0;
	m_bCommandHandler[0] = TRUE;
	m_bCommandHandler[1] = TRUE;
	m_bCommandHandler[2] = FALSE;
	m_bCommand[0] = FALSE;
	m_bCommand[1] = FALSE;
	m_bCommand[2] = FALSE;
	m_bCommand[3] = FALSE;
}

BOOL CTCProcessInterfaceThread::Start()
{
	return CreateThread((LPVOID)NULL, THREAD_PRIORITY_ABOVE_NORMAL);
}

BOOL CTCProcessInterfaceThread::Stop()
{
	m_bCommandHandler[2] = FALSE;
	m_szCommandHandler[2].Empty();
	m_cCommandHandlerThread.Stop();
	return((DestroyThread() >= 0) ? TRUE : FALSE);
}

BOOL CTCProcessInterfaceThread::InitInstance()
{
	return AfxSocketInit();
}

int CTCProcessInterfaceThread::ExitInstance()
{
	for (UpdateCommandSources(), m_pClientSockets.RemoveAll(), m_cSocket.Close(); m_nCommandHandlerTimerID[0] != 0; )
	{
		KillTimer((HWND)NULL, m_nCommandHandlerTimerID[0]);
		m_nCommandHandlerTimerID[0] = 0;
		break;
	}
	if (m_nCommandHandlerTimerID[1] != 0)
	{
		KillTimer((HWND)NULL, m_nCommandHandlerTimerID[1]);
		m_nCommandHandlerTimerID[1] = 0;
	}
	return CThread::ExitInstance();
}

BOOL CTCProcessInterfaceThread::Update(CONST CTCItems &pReleaseItems, CONST CTCItems &pVerificationItems, CONST CTCItems &pInterlockItems, CONST CTCInterlocks &pInterlocks)
{
	INT  nItem;
	INT  nItems;
	INT  nCount;
	INT  nClient;
	INT  nClients;
	BOOL  bClients;
	CTCItem  *pItem[2];
	CTCItems  pItems[2];
	CByteArray  nMessageData;
	CTCProcessInterfaceSocket  *pSocket;
	CTCProcessInterfaceUpdateCommandSourcesContentsRequest  cUpdateCommandSourcesContentsRequest;
	CTCChainLock  cLock(this);

	for (nItem = 0, nItems = (pItems[0].Copy(&pVerificationItems) && pItems[1].Copy(&pReleaseItems)) ? (INT)pItems[1].GetSize() : 0; nItem < nItems; nItem++)
	{
		pItems[0].InsertAt(pItems[0].GetSize(), pItems[1].GetAt(nItem), 1);
		pItems[1].RemoveAt(nItem);
		nItems--;
		nItem--;
	}
	for (nItem = 0, nItems = (INT)pInterlockItems.GetSize(), nCount = 0; nItem < nItems; nItem++)
	{
		if ((pItem[1] = ((pItem[0] = pInterlockItems.GetAt(nItem))) ? pItems[0].GetAt(pItems[0].Find(pItem[0])) : (CTCItem *)NULL))
		{
			pItem[1]->Copy(pItem[0]);
			nCount++;
			continue;
		}
		if ((pItem[0] = pInterlockItems.GetAt(nItem)))
		{
			if ((pItem[1] = new CTCItem))
			{
				pItem[1]->Copy(pItem[0]);
				pItems[0].InsertAt(pItems[0].GetSize(), pItem[1], 1);
			}
		}
	}
	if ((pItems[0].GetSize() > 0 && pItems[0].GetSize() == pReleaseItems.GetSize() + pVerificationItems.GetSize() + pInterlockItems.GetSize() - nCount) || pInterlocks.GetSize() > 0)
	{
		if ((!pItems[0].GetSize() || cUpdateCommandSourcesContentsRequest.SetTelecommands(pItems[0], FALSE)) && (!pInterlocks.GetSize() || cUpdateCommandSourcesContentsRequest.SetTCInterlocks(pInterlocks, FALSE)) && cUpdateCommandSourcesContentsRequest.EnableAcknowledgment(FALSE) && cUpdateCommandSourcesContentsRequest.Map(nMessageData))
		{
			for (nClient = 0, nClients = (INT)m_pClientSockets.GetSize(), bClients = FALSE; nClient < nClients; nClient++)
			{
				if ((pSocket = m_pClientSockets.GetAt(nClient)) != (CTCProcessInterfaceSocket *)NULL  &&  pSocket->IsConnected())
				{
					if ((pSocket->GetFlags() & (TCSERVICE_COMMANDINTERFACE_TELECOMMANDSUPDATE | TCSERVICE_COMMANDINTERFACE_INTERLOCKSUPDATE)) == 0 && pSocket->Send(nMessageData)) continue;
					pSocket->SetFlags(pSocket->GetFlags() | TCSERVICE_COMMANDINTERFACE_TELECOMMANDSUPDATE | TCSERVICE_COMMANDINTERFACE_INTERLOCKSUPDATE);
					bClients = TRUE;
				}
			}
			if (pItems[0].GetSize() > 0) UpdateTelecommands(EMPTYSTRING, pItems[0], FALSE);
			if (pInterlocks.GetSize() > 0) UpdateTCInterlocks(EMPTYSTRING, pInterlocks, FALSE);
			if (bClients) UpdateCommandingClients();
			return TRUE;
		}
	}
	return FALSE;
}
BOOL CTCProcessInterfaceThread::Update(LPCTSTR pszEvent)
{
	INT  nCommandSource;
	INT  nCommandSources;
	BOOL  bCommandSources;
	CTCProcessCommandSources  pCommandSources;
	CTCProcessCommandSourceInfo  *pCommandSourceInfo;
	CTCChainLock  cLock(this);

	for (nCommandSource = 0, nCommandSources = (m_cSocket.GetCommandSources(pCommandSources)) ? (INT)pCommandSources.GetSize() : 0, bCommandSources = FALSE; nCommandSource < nCommandSources; nCommandSource++)
	{
		if ((pCommandSourceInfo = pCommandSources.GetAt(nCommandSource)) != (CTCProcessCommandSourceInfo *)NULL)
		{
			bCommandSources = pCommandSourceInfo->Update(pszEvent) || bCommandSources;
			continue;
		}
	}
	for (; bCommandSources; )
	{
		if (m_bCommandHandler[2])
		{
			if (m_cSocket.SetCommandSources(pCommandSources)) return TRUE;
			break;
		}
		if (SetCommandSources(pCommandSources)) return TRUE;
		break;
	}
	return !bCommandSources;
}
BOOL CTCProcessInterfaceThread::Update()
{
	return m_cUpdate.SetEvent();
}

BOOL CTCProcessInterfaceThread::AddClient(CTCProcessInterfaceSocket *pSocket)
{
	INT  nPos;
	INT  cbAddress;
	INT  nClient[2];
	INT  nClients[2];
	UINT  nClientPort;
	CString  szClient;
	CString  szAddress;
	CString  szMessage[2];
	IN_ADDR  sClientAddress;
	SOCKADDR_IN  sAddress;
	CTimeKey  tConnectTime;
	CTCChainLock  cLock(this);

	if (pSocket->GetPeerName((SOCKADDR *)&sAddress, &(cbAddress = sizeof(sAddress))))
	{
		for (nClient[0] = 0, nClients[0] = (INT)m_szCommandHandlerClients[0].GetSize(); nClient[0] < nClients[0]; nClient[0]++)
		{
			if ((nPos = m_szCommandHandlerClients[0].GetAt(nClient[0]).Find(EOL)) >= 0)
			{
#ifndef UNICODE
				szAddress = m_szCommandHandlerClients[0].GetAt(nClient[0]).Mid(nPos + 1);
#else
				WideCharToMultiByte(CP_ACP, 0, m_szCommandHandlerClients[0].GetAt(nClient[0]).Mid(nPos + 1), -1, (LPSTR)szAddress.GetBufferSetLength(m_szCommandHandlerClients[0].GetAt(nClient[0]).Mid(nPos + 1).GetLength()), m_szCommandHandlerClients[0].GetAt(nClient[0]).Mid(nPos + 1).GetLength() + 1, (LPCSTR)NULL, (LPBOOL)NULL);
				szAddress.ReleaseBuffer();
#endif
				if (InetPton(AF_INET, szAddress, &sClientAddress) > 0 && sClientAddress.S_un.S_addr == sAddress.sin_addr.S_un.S_addr)
				{
					szClient = m_szCommandHandlerClients[0].GetAt(nClient[0]).Left(nPos);
					break;
				}
			}
		}
		for (pSocket->Connect((szClient = (szClient.IsEmpty()) ? STRING(IDS_TELECOMMANDPROCESSINTERFACE_SECURITY_ANONYMOUSUSER) : szClient)), szClient.MakeUpper(), nClient[0] = (nClient[0] == nClients[0] && nClients[0] > 0 && !m_szCommandHandlerClients[0].GetAt(nClients[0] - 1).GetLength() && (m_nCommandHandlerAccessCodes.GetAt(nClients[0] - 1) & TCSERVICE_COMMANDINTERFACE_UNLIMITEDACCESS)) ? (nClients[0] - 1) : nClient[0], szAddress = (pSocket->GetPeerName(szAddress, nClientPort)) ? szAddress : szAddress; nClient[0] < nClients[0]; )
		{
			if ((m_nCommandHandlerAccessCodes.GetAt(nClient[0]) & TCSERVICE_COMMANDINTERFACE_NOACCESS) != TCSERVICE_COMMANDINTERFACE_NOACCESS && ((m_nCommandHandlerAccessCodes.GetAt(nClient[0]) & TCSERVICE_COMMANDINTERFACE_LIMITEDACCESS) != TCSERVICE_COMMANDINTERFACE_LIMITEDACCESS || (tConnectTime >= m_tCommandHandlerStartTimes.GetAt(nClient[0]) && tConnectTime < m_tCommandHandlerStopTimes.GetAt(nClient[0]))))
			{
				for (nClient[1] = 0, nClients[1] = (INT)m_szCommandHandlerClients[1].GetSize(); nClient[1] < nClients[1]; nClient[1]++)
				{
					if (!m_szCommandHandlerClients[0].GetAt(nClient[0]).CompareNoCase(m_szCommandHandlerClients[1].GetAt(nClient[1])))
					{
						m_szCommandHandlerClients[1].RemoveAt(nClient[1]);
						break;
					}
				}
				if (m_pClientSockets.Add(pSocket) >= 0)
				{
					for (szMessage[0].Format(STRING(IDS_TELECOMMANDPROCESSINTERFACE_SECURITY_LOGIN), (LPCTSTR)szClient, (LPCTSTR)szAddress), szMessage[1].Format(STRING(IDS_TELECOMMANDPROCESSINTERFACE_SECURITY_ANONYMOUSLOGIN), (LPCTSTR)szAddress); m_nCommandHandlerAccessCodes.GetAt(nClient[0]) & TCSERVICE_COMMANDINTERFACE_AUDITACCESS; )
					{
						ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, (szClient.CompareNoCase(STRING(IDS_TELECOMMANDPROCESSINTERFACE_SECURITY_ANONYMOUSUSER))) ? szMessage[0] : szMessage[1], FALSE);
						break;
					}
					return TRUE;
				}
				break;
			}
			for (nClient[1] = 0, nClients[1] = (INT)m_szCommandHandlerClients[1].GetSize(); nClient[1] < nClients[1]; nClient[1]++)
			{
				if (!m_szCommandHandlerClients[0].GetAt(nClient[0]).CompareNoCase(m_szCommandHandlerClients[1].GetAt(nClient[1]))) break;
				continue;
			}
			for (szMessage[0].Format(STRING(IDS_TELECOMMANDPROCESSINTERFACE_SECURITY_ACCESSVIOLATION), (LPCTSTR)szClient, (LPCTSTR)szAddress), szMessage[1].Format(STRING(IDS_TELECOMMANDPROCESSINTERFACE_SECURITY_ACCESSVIOLATION), (LPCTSTR)szAddress); (m_nCommandHandlerAccessCodes.GetAt(nClient[0]) & TCSERVICE_COMMANDINTERFACE_AUDITACCESS) && nClient[1] == nClients[1]; )
			{
				ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, (szClient.CompareNoCase(STRING(IDS_TELECOMMANDPROCESSINTERFACE_SECURITY_ANONYMOUSUSER))) ? szMessage[0] : szMessage[1], FALSE);
				m_szCommandHandlerClients[1].Add(m_szCommandHandlerClients[0].GetAt(nClient[0]));
				break;
			}
			break;
		}
	}
	return FALSE;
}

BOOL CTCProcessInterfaceThread::RemoveClient(INT nIndex)
{
	CTCProcessInterfaceSocket  *pSocket;
	CTCChainLock  cLock(this);

	if ((pSocket = m_pClientSockets.GetAt(nIndex)))
	{
		for (m_pClientSockets.RemoveAt(nIndex); pSocket->IsConnected(); )
		{
			pSocket->Close(TRUE);
			break;
		}
		delete pSocket;
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceThread::SetCommandHandlerConfiguration(LPCTSTR pszPreferredCommandHandler, LPCTSTR pszBackupCommandHandler, BOOL bSelfCommandHandler, BOOL bAnyCommandHandler, BOOL bExclusiveCommandHandler, UINT nCommandHandlerOptions, UINT nCommandHandlerPort, UINT nCommandHandlerBufferSize, CONST CTimeSpan &tCommandHandlerTimeout, CONST CStringArray &szCommandHandlerClients, CONST CUIntArray &nCommandHandlerAccessCodes, CONST CTimeKeyArray &tCommandHandlerStartTimes, CONST CTimeKeyArray &tCommandHandlerStopTimes)
{
	INT  nClient[2];
	INT  nClients[2];
	CTCChainLock  cLock(this);

	for (m_szCommandHandler[0] = pszPreferredCommandHandler, m_szCommandHandler[1] = pszBackupCommandHandler, m_nCommandHandlerBufferSize = nCommandHandlerBufferSize, m_tCommandHandlerTimeout = tCommandHandlerTimeout, m_nCommandHandlerOptions = nCommandHandlerOptions, m_bCommandHandlerExclusive = bExclusiveCommandHandler, m_bCommandHandler[0] = bSelfCommandHandler, m_bCommandHandler[1] = bAnyCommandHandler; m_nCommandHandlerPort != nCommandHandlerPort; )
	{
		m_nCommandHandlerPort = nCommandHandlerPort;
		m_bCommand[0] = TRUE;
		break;
	}
	for (nClient[0] = 0, nClients[0] = (INT)m_szCommandHandlerClients[1].GetSize(), m_szCommandHandlerClients[0].Copy(szCommandHandlerClients), m_nCommandHandlerAccessCodes.Copy(nCommandHandlerAccessCodes), m_tCommandHandlerStartTimes.Copy(tCommandHandlerStartTimes), m_tCommandHandlerStopTimes.Copy(tCommandHandlerStopTimes), m_bCommand[1] = TRUE; nClient[0] < nClients[0]; nClient[0]++)
	{
		for (nClient[1] = 0, nClients[1] = (INT)szCommandHandlerClients.GetSize(); nClient[1] < nClients[1]; nClient[1] = nClient[1] + 1)
		{
			if (!m_szCommandHandlerClients[1].GetAt(nClient[0]).CompareNoCase(szCommandHandlerClients.GetAt(nClient[1]))) break;
			continue;
		}
		if (nClient[1] == nClients[1])
		{
			m_szCommandHandlerClients[1].RemoveAt(nClient[0]);
			nClients[0]--;
			nClient[0]--;
		}
	}
	Update();
	return TRUE;
}
BOOL CTCProcessInterfaceThread::SetCommandHandlerConfiguration(UINT nTelecommandingMode, UINT nTelecommandingState, UINT nTelecommandingFlags, BOOL bTelecommandingInterlockMode, BOOL bTelecommandingReleaseWaitMode, BOOL bTelecommandingAutoRejectionMode, CONST CTimeSpan &tVerificationUncertaintyTimeWindow, CONST CTimeSpan &tDefaultReleaseTimeWindow, CONST CHistoryStoreFiles &pHistoryArchivalFiles, CONST CHistoryStoreFiles &pHistoryRetrievalFiles, LPCTSTR pszDefaultHistoryFileName)
{
	CTCChainLock  cLock(this);

	m_nCommandHandlerTelecommandingMode = nTelecommandingMode;
	m_nCommandHandlerTelecommandingState = nTelecommandingState;
	m_nCommandHandlerTelecommandingFlags = nTelecommandingFlags;
	m_bCommandHandlerTelecommandingInterlockMode = bTelecommandingInterlockMode;
	m_bCommandHandlerTelecommandingReleaseWaitMode = bTelecommandingReleaseWaitMode;
	m_bCommandHandlerTelecommandingAutoRejectionMode = bTelecommandingAutoRejectionMode;
	m_tCommandHandlerTimeWindow[0] = tVerificationUncertaintyTimeWindow;
	m_tCommandHandlerTimeWindow[1] = tDefaultReleaseTimeWindow;
	m_pCommandHandlerFiles[0].Copy(&pHistoryArchivalFiles);
	m_pCommandHandlerFiles[1].Copy(&pHistoryRetrievalFiles);
	m_szCommandHandlerFileName = pszDefaultHistoryFileName;
	return TRUE;
}
BOOL CTCProcessInterfaceThread::SetCommandHandlerConfiguration(CONST CTCProcessCommandSources &pCommandSources, UINT nTelecommandingMode, UINT nTelecommandingState, UINT nTelecommandingFlags, BOOL bTelecommandingInterlockMode, BOOL bTelecommandingReleaseWaitMode, BOOL bTelecommandingAutoRejectionMode, CONST CTimeSpan &tVerificationUncertaintyTimeWindow, CONST CTimeSpan &tMaximumExecutionTimePeriod, CONST CTimeSpan &tMaximumTimeCheckPeriod, CONST CTimeSpan &tDefaultReleaseTimeWindow, CONST CHistoryStoreFiles &pHistoryArchivalFiles, CONST CHistoryStoreFiles &pHistoryRetrievalFiles, LPCTSTR pszDefaultHistoryFileName, BOOL bUpdate)
{
	CComputerToken  cComputerToken;
	CTCChainLock  cLock(this);

	for (m_hCommandHandlerWnd = (HWND)NULL, m_nCommandHandlerTimerID[2] = 0; SetCommandHandlerConfiguration(cComputerToken.GetComputerName(), pCommandSources, nTelecommandingMode, nTelecommandingState, nTelecommandingFlags, bTelecommandingInterlockMode, bTelecommandingReleaseWaitMode, bTelecommandingAutoRejectionMode, tVerificationUncertaintyTimeWindow, tMaximumExecutionTimePeriod, tMaximumTimeCheckPeriod, tDefaultReleaseTimeWindow, pHistoryArchivalFiles, pHistoryRetrievalFiles, pszDefaultHistoryFileName, bUpdate); ) return TRUE;
	return FALSE;
}
BOOL CTCProcessInterfaceThread::SetCommandHandlerConfiguration(LPCTSTR pszOriginator, CONST CTCProcessCommandSources &pCommandSources, UINT nTelecommandingMode, UINT nTelecommandingState, UINT nTelecommandingFlags, BOOL bTelecommandingInterlockMode, BOOL bTelecommandingReleaseWaitMode, BOOL bTelecommandingAutoRejectionMode, CONST CTimeSpan &tVerificationUncertaintyTimeWindow, CONST CTimeSpan &tMaximumExecutionTimePeriod, CONST CTimeSpan &tMaximumTimeCheckPeriod, CONST CTimeSpan &tDefaultReleaseTimeWindow, CONST CHistoryStoreFiles &pHistoryArchivalFiles, CONST CHistoryStoreFiles &pHistoryRetrievalFiles, LPCTSTR pszDefaultHistoryFileName, BOOL bUpdate)
{
	INT  nClient[2];
	INT  nClients[2];
	INT  nCommandSource;
	INT  nCommandSources;
	BOOL  bCommandSources;
	CTimeSpan  tOffset[2][2];
	CByteArray  nMessageData;
	CComputerToken  cComputerToken;
	CHistoryStoreFile  cDefaultHistoryFile;
	CTCProcessInterfaceSocket  *pSocket;
	CTCProcessCommandSources  pServerCommandSources;
	CTCProcessCommandSources  pClientCommandSources;
	CTCProcessCommandSources  pBackupCommandSources;
	CTCProcessCommandSourceInfo  *pCommandSourceInfo[2];
	CTCProcessInterfaceSetCommandHandlerConfigurationRequest  cSetCommandHandlerConfigurationRequestMessage;
	CTCProcessInterfaceSetCommandHandlerConfigurationResponse  cSetCommandHandlerConfigurationResponseMessage;
	CTCChainLock  cLock(this);

	if (m_bCommandHandler[2])
	{
		if ((pSocket = m_pClientSockets.GetAt(m_pClientSockets.Find(pszOriginator))))
		{
			if (pSocket->GetFlags() & TCSERVICE_COMMANDINTERFACE_CONFIGURATIONUPDATE)
			{
				pSocket->SetFlags(pSocket->GetFlags() & ~TCSERVICE_COMMANDINTERFACE_CONFIGURATIONUPDATE);
				m_bCommandHandlerUpdate = FALSE;
			}
			pSocket->SetFlags(pSocket->GetFlags() & ~TCSERVICE_COMMANDINTERFACE_HOTLINKUPDATE);
		}
		for (nClient[0] = 0, nClients[0] = (m_bCommandHandlerUpdate) ? (INT)m_pClientSockets.GetSize() : 0; nClient[0] < nClients[0]; nClient[0]++)
		{
			if ((pSocket = m_pClientSockets.GetAt(nClient[0])) && (pSocket->GetFlags() & TCSERVICE_COMMANDINTERFACE_CONFIGURATIONUPDATE)) break;
			continue;
		}
		for (; nClient[0] == nClients[0] || !nClients[0]; )
		{
			m_bCommandHandlerUpdate = (cComputerToken.GetComputerName().CompareNoCase(pszOriginator)) ? m_bCommandHandlerUpdate : FALSE;
			break;
		}
		if (bUpdate)
		{
			for (nCommandSource = 0, nCommandSources = (m_cSocket.GetCommandSources(pServerCommandSources)) ? (INT)pServerCommandSources.GetSize() : 0, bCommandSources = FALSE; nCommandSource < nCommandSources; nCommandSource++)
			{
				if ((pCommandSourceInfo[1] = ((pCommandSourceInfo[0] = pServerCommandSources.GetAt(nCommandSource))) ? pCommandSources.GetAt(pCommandSources.Find(pCommandSourceInfo[0]->GetComputerName(), pCommandSourceInfo[0]->GetSourceType())) : (CTCProcessCommandSourceInfo *)NULL))
				{
					for (; (m_nCommandHandlerTelecommandingState & TCSERVICE_COMMANDSOURCESTATE_DISABLED) != (nTelecommandingState & TCSERVICE_COMMANDSOURCESTATE_DISABLED); )
					{
						for (nClient[1] = 0, nClients[1] = ((nTelecommandingState & TCSERVICE_COMMANDSOURCESTATE_DISABLED) && pCommandSourceInfo[0]->GetSourceType() == TCSERVICE_COMMANDSOURCETYPE_MANUALSTACK) ? (INT)m_szCommandClients[0].GetSize() : 0, pCommandSourceInfo[1]->SetTelecommandingState((nTelecommandingState & TCSERVICE_COMMANDSOURCESTATE_DISABLED) ? (pCommandSourceInfo[1]->GetTelecommandingState() | TCSERVICE_COMMANDSOURCESTATE_DISABLED) : (pCommandSourceInfo[1]->GetTelecommandingState() & ~TCSERVICE_COMMANDSOURCESTATE_DISABLED)); nClient[1] < nClients[1]; nClient[1]++)
						{
							if (!m_szCommandClients[0].GetAt(nClient[1]).CompareNoCase(pCommandSourceInfo[0]->GetComputerName()))
							{
								m_szCommandClients[0].RemoveAt(nClient[1]);
								break;
							}
						}
						for (nClient[1] = 0, nClients[1] = ((nTelecommandingState & TCSERVICE_COMMANDSOURCESTATE_DISABLED) && pCommandSourceInfo[0]->GetSourceType() == TCSERVICE_COMMANDSOURCETYPE_AUTOMATICSTACK) ? (INT)m_szCommandClients[1].GetSize() : 0; nClient[1] < nClients[1]; nClient[1]++)
						{
							if (!m_szCommandClients[1].GetAt(nClient[1]).CompareNoCase(pCommandSourceInfo[0]->GetComputerName()))
							{
								m_szCommandClients[1].RemoveAt(nClient[1]);
								break;
							}
						}
						break;
					}
					for (; m_nCommandHandlerTelecommandingFlags != nTelecommandingFlags; )
					{
						pCommandSourceInfo[1]->SetTelecommandingChecks((pCommandSourceInfo[1]->GetSourceType() == TCSERVICE_COMMANDSOURCETYPE_PROCEDURESMONITOR) ? (nTelecommandingFlags & (TCSERVICE_COMMANDSOURCEFLAGS_PEV_OVERRIDE | TCSERVICE_COMMANDSOURCEFLAGS_CEV_OVERRIDE | TCSERVICE_COMMANDSOURCEFLAGS_PEV_DISABLE | TCSERVICE_COMMANDSOURCEFLAGS_CEV_DISABLE)) : nTelecommandingFlags);
						break;
					}
					for (; pCommandSourceInfo[1]->GetSourceType() != TCSERVICE_COMMANDSOURCETYPE_PROCEDURESMONITOR && m_bCommandHandlerTelecommandingInterlockMode != bTelecommandingInterlockMode; )
					{
						pCommandSourceInfo[1]->EnableTelecommandingInterlockMode(bTelecommandingInterlockMode);
						break;
					}
					for (; m_bCommandHandlerTelecommandingReleaseWaitMode != bTelecommandingReleaseWaitMode; )
					{
						pCommandSourceInfo[1]->EnableTelecommandingReleaseWaitMode(bTelecommandingReleaseWaitMode);
						break;
					}
					for (; pCommandSourceInfo[1]->GetSourceType() != TCSERVICE_COMMANDSOURCETYPE_PROCEDURESMONITOR && m_bCommandHandlerTelecommandingAutoRejectionMode != bTelecommandingAutoRejectionMode; )
					{
						pCommandSourceInfo[1]->EnableTelecommandingAutoRejectionMode(bTelecommandingAutoRejectionMode);
						break;
					}
					for (; pCommandSourceInfo[1]->GetSourceType() != TCSERVICE_COMMANDSOURCETYPE_PROCEDURESMONITOR && m_tCommandHandlerTimeWindow[1] != tDefaultReleaseTimeWindow; )
					{
						pCommandSourceInfo[1]->SetDefaultReleaseTimeWindow(tDefaultReleaseTimeWindow);
						break;
					}
					if (!pCommandSourceInfo[0]->Compare(pCommandSourceInfo[1]))
					{
						pCommandSourceInfo[0]->Copy(pCommandSourceInfo[1]);
						bCommandSources = TRUE;
					}
				}
			}
			for (GetCommandSources(pBackupCommandSources); bCommandSources && UpdateCommandSources(pServerCommandSources, FALSE); )
			{
				for (SetCommandSources(pszOriginator, pServerCommandSources); !cComputerToken.GetComputerName().CompareNoCase(pszOriginator); )
				{
					UpdateCommandSources(pszOriginator, pServerCommandSources);
					break;
				}
				UpdateCommandSources(pBackupCommandSources, pCommandSources);
				break;
			}
			for (nClient[0] = 0, nClients[0] = (INT)m_pClientSockets.GetSize(); nClient[0] < nClients[0]; nClient[0]++)
			{
				if ((pSocket = m_pClientSockets.GetAt(nClient[0])) && pSocket->IsConnected() && pSocket->GetCommandSources(pClientCommandSources))
				{
					for (nCommandSource = 0, nCommandSources = (INT)pClientCommandSources.GetSize(), bCommandSources = FALSE; nCommandSource < nCommandSources; nCommandSource++)
					{
						if ((pCommandSourceInfo[1] = ((pCommandSourceInfo[0] = pClientCommandSources.GetAt(nCommandSource))) ? pCommandSources.GetAt(pCommandSources.Find(pCommandSourceInfo[0]->GetComputerName(), pCommandSourceInfo[0]->GetSourceType())) : (CTCProcessCommandSourceInfo *)NULL))
						{
							if ((m_nCommandHandlerTelecommandingState & TCSERVICE_COMMANDSOURCESTATE_DISABLED) != (nTelecommandingState & TCSERVICE_COMMANDSOURCESTATE_DISABLED))
							{
								for (nClient[1] = 0, nClients[1] = ((nTelecommandingState & TCSERVICE_COMMANDSOURCESTATE_DISABLED) && pCommandSourceInfo[0]->GetSourceType() == TCSERVICE_COMMANDSOURCETYPE_MANUALSTACK) ? (INT)m_szCommandClients[0].GetSize() : 0, pCommandSourceInfo[1]->SetTelecommandingState((nTelecommandingState & TCSERVICE_COMMANDSOURCESTATE_DISABLED) ? (pCommandSourceInfo[1]->GetTelecommandingState() | TCSERVICE_COMMANDSOURCESTATE_DISABLED) : (pCommandSourceInfo[1]->GetTelecommandingState() & ~TCSERVICE_COMMANDSOURCESTATE_DISABLED)); nClient[1] < nClients[1]; nClient[1]++)
								{
									if (!m_szCommandClients[0].GetAt(nClient[1]).CompareNoCase(pCommandSourceInfo[0]->GetComputerName()))
									{
										m_szCommandClients[0].RemoveAt(nClient[1]);
										break;
									}
								}
								for (nClient[1] = 0, nClients[1] = ((nTelecommandingState & TCSERVICE_COMMANDSOURCESTATE_DISABLED) && pCommandSourceInfo[0]->GetSourceType() == TCSERVICE_COMMANDSOURCETYPE_AUTOMATICSTACK) ? (INT)m_szCommandClients[1].GetSize() : 0; nClient[1] < nClients[1]; nClient[1]++)
								{
									if (!m_szCommandClients[1].GetAt(nClient[1]).CompareNoCase(pCommandSourceInfo[0]->GetComputerName()))
									{
										m_szCommandClients[1].RemoveAt(nClient[1]);
										break;
									}
								}
							}
							for (; m_nCommandHandlerTelecommandingFlags != nTelecommandingFlags; )
							{
								pCommandSourceInfo[1]->SetTelecommandingChecks((pCommandSourceInfo[1]->GetSourceType() == TCSERVICE_COMMANDSOURCETYPE_PROCEDURESMONITOR) ? (nTelecommandingFlags & (TCSERVICE_COMMANDSOURCEFLAGS_PEV_OVERRIDE | TCSERVICE_COMMANDSOURCEFLAGS_CEV_OVERRIDE | TCSERVICE_COMMANDSOURCEFLAGS_PEV_DISABLE | TCSERVICE_COMMANDSOURCEFLAGS_CEV_DISABLE)) : nTelecommandingFlags);
								break;
							}
							for (; pCommandSourceInfo[1]->GetSourceType() != TCSERVICE_COMMANDSOURCETYPE_PROCEDURESMONITOR && m_bCommandHandlerTelecommandingInterlockMode != bTelecommandingInterlockMode; )
							{
								pCommandSourceInfo[1]->EnableTelecommandingInterlockMode(bTelecommandingInterlockMode);
								break;
							}
							for (; m_bCommandHandlerTelecommandingReleaseWaitMode != bTelecommandingReleaseWaitMode; )
							{
								pCommandSourceInfo[1]->EnableTelecommandingReleaseWaitMode(bTelecommandingReleaseWaitMode);
								break;
							}
							for (; pCommandSourceInfo[1]->GetSourceType() != TCSERVICE_COMMANDSOURCETYPE_PROCEDURESMONITOR && m_bCommandHandlerTelecommandingAutoRejectionMode != bTelecommandingAutoRejectionMode; )
							{
								pCommandSourceInfo[1]->EnableTelecommandingAutoRejectionMode(bTelecommandingAutoRejectionMode);
								break;
							}
							for (; pCommandSourceInfo[1]->GetSourceType() != TCSERVICE_COMMANDSOURCETYPE_PROCEDURESMONITOR && m_tCommandHandlerTimeWindow[1] != tDefaultReleaseTimeWindow; )
							{
								pCommandSourceInfo[1]->SetDefaultReleaseTimeWindow(tDefaultReleaseTimeWindow);
								break;
							}
							if (!pCommandSourceInfo[0]->Compare(pCommandSourceInfo[1]))
							{
								pCommandSourceInfo[0]->Copy(pCommandSourceInfo[1]);
								bCommandSources = TRUE;
							}
						}
					}
					for (GetCommandSources(pBackupCommandSources); bCommandSources && UpdateCommandSources(pClientCommandSources, FALSE); )
					{
						for (SetCommandSources(pszOriginator, pClientCommandSources); !cComputerToken.GetComputerName().CompareNoCase(pszOriginator); )
						{
							UpdateCommandSources(pszOriginator, pClientCommandSources);
							break;
						}
						UpdateCommandSources(pBackupCommandSources, pCommandSources);
						break;
					}
				}
			}
			for (m_nCommandHandlerTelecommandingMode = nTelecommandingMode, m_nCommandHandlerTelecommandingState = nTelecommandingState, m_nCommandHandlerTelecommandingFlags = nTelecommandingFlags, m_bCommandHandlerTelecommandingInterlockMode = bTelecommandingInterlockMode, m_bCommandHandlerTelecommandingReleaseWaitMode = bTelecommandingReleaseWaitMode, m_bCommandHandlerTelecommandingAutoRejectionMode = bTelecommandingAutoRejectionMode, m_tCommandHandlerTimeWindow[0] = tVerificationUncertaintyTimeWindow, m_tCommandHandlerTimeWindow[1] = tDefaultReleaseTimeWindow, m_pCommandHandlerFiles[0].Copy(&pHistoryArchivalFiles), m_pCommandHandlerFiles[1].Copy(&pHistoryRetrievalFiles), m_szCommandHandlerFileName = pszDefaultHistoryFileName; m_pTCProcessThread->GetTCFunctionExecutionTimeOffsets(tOffset[0][0], tOffset[0][1]) && m_pTCProcessThread->GetTCFunctionParameterTimeOffsets(tOffset[1][0], tOffset[1][1]); )
			{
				m_pTCProcessThread->SetTCFunctionExecutionTimeOffsets(tOffset[0][0], tMaximumExecutionTimePeriod);
				m_pTCProcessThread->SetTCFunctionParameterTimeOffsets(tOffset[1][0], tMaximumTimeCheckPeriod);
				break;
			}
			for (GetTCService()->SetTCHistoryFiles(HISTORYFILE_TYPE_ARCHIVE, pHistoryArchivalFiles), GetTCService()->SetTCHistoryFiles(HISTORYFILE_TYPE_RETRIEVE, pHistoryRetrievalFiles); pHistoryRetrievalFiles.Find(pszDefaultHistoryFileName) >= 0; )
			{
				cDefaultHistoryFile.Copy(pHistoryRetrievalFiles.GetAt(pHistoryRetrievalFiles.Find(pszDefaultHistoryFileName)));
				GetTCService()->SetDefaultTCHistoryFile(HISTORYFILE_TYPE_RETRIEVE, cDefaultHistoryFile);
				break;
			}
		}
		return TRUE;
	}
	if (cSetCommandHandlerConfigurationRequestMessage.SetConfiguration(pCommandSources, nTelecommandingMode, nTelecommandingState, nTelecommandingFlags, bTelecommandingInterlockMode, bTelecommandingReleaseWaitMode, bTelecommandingAutoRejectionMode, tVerificationUncertaintyTimeWindow, tMaximumExecutionTimePeriod, tMaximumTimeCheckPeriod, tDefaultReleaseTimeWindow, pHistoryArchivalFiles, pHistoryRetrievalFiles, pszDefaultHistoryFileName) && cSetCommandHandlerConfigurationRequestMessage.EnableUpdateFlag(bUpdate) && cSetCommandHandlerConfigurationRequestMessage.Map(nMessageData) && m_cSocket.Send(nMessageData))
	{
		for (GetTCService()->SetTCHistoryFiles(HISTORYFILE_TYPE_ARCHIVE, pHistoryArchivalFiles), GetTCService()->SetTCHistoryFiles(HISTORYFILE_TYPE_RETRIEVE, pHistoryRetrievalFiles); pHistoryRetrievalFiles.Find(pszDefaultHistoryFileName) >= 0; )
		{
			cDefaultHistoryFile.Copy(pHistoryRetrievalFiles.GetAt(pHistoryRetrievalFiles.Find(pszDefaultHistoryFileName)));
			GetTCService()->SetDefaultTCHistoryFile(HISTORYFILE_TYPE_RETRIEVE, cDefaultHistoryFile);
			break;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceThread::GetCommandHandlerConfiguration(CString &szPreferredCommandHandler, CString &szBackupCommandHandler, BOOL &bSelfCommandHandler, BOOL &bAnyCommandHandler, BOOL &bExclusiveCommandHandler, UINT &nCommandHandlerOptions, UINT &nCommandHandlerPort, UINT &nCommandHandlerBufferSize, CTimeSpan &tCommandHandlerTimeout, CStringArray &szCommandHandlerClients, CUIntArray &nCommandHandlerAccessCodes, CTimeKeyArray &tCommandHandlerStartTimes, CTimeKeyArray &tCommandHandlerStopTimes) CONST
{
	CTCChainLock  cLock(this);

	szPreferredCommandHandler = m_szCommandHandler[0];
	szBackupCommandHandler = m_szCommandHandler[1];
	nCommandHandlerPort = m_nCommandHandlerPort;
	tCommandHandlerTimeout = m_tCommandHandlerTimeout;
	nCommandHandlerOptions = m_nCommandHandlerOptions;
	nCommandHandlerBufferSize = m_nCommandHandlerBufferSize;
	szCommandHandlerClients.Copy(m_szCommandHandlerClients[0]);
	nCommandHandlerAccessCodes.Copy(m_nCommandHandlerAccessCodes);
	tCommandHandlerStartTimes.Copy(m_tCommandHandlerStartTimes);
	tCommandHandlerStopTimes.Copy(m_tCommandHandlerStopTimes);
	bExclusiveCommandHandler = m_bCommandHandlerExclusive;
	bSelfCommandHandler = m_bCommandHandler[0];
	bAnyCommandHandler = m_bCommandHandler[1];
	return TRUE;
}
BOOL CTCProcessInterfaceThread::GetCommandHandlerConfiguration(UINT &nTelecommandingMode, UINT &nTelecommandingState, UINT &nTelecommandingFlags, BOOL &bTelecommandingInterlockMode, BOOL &bTelecommandingReleaseWaitMode, BOOL &bTelecommandingAutoRejectionMode, CTimeSpan &tVerificationUncertaintyTimeWindow, CTimeSpan &tDefaultReleaseTimeWindow, CHistoryStoreFiles &pHistoryArchivalFiles, CHistoryStoreFiles &pHistoryRetrievalFiles, CString &szDefaultHistoryFileName) CONST
{
	CTCChainLock  cLock(this);

	nTelecommandingMode = m_nCommandHandlerTelecommandingMode;
	nTelecommandingState = m_nCommandHandlerTelecommandingState;
	nTelecommandingFlags = m_nCommandHandlerTelecommandingFlags;
	bTelecommandingInterlockMode = m_bCommandHandlerTelecommandingInterlockMode;
	bTelecommandingReleaseWaitMode = m_bCommandHandlerTelecommandingReleaseWaitMode;
	bTelecommandingAutoRejectionMode = m_bCommandHandlerTelecommandingAutoRejectionMode;
	tVerificationUncertaintyTimeWindow = m_tCommandHandlerTimeWindow[0];
	tDefaultReleaseTimeWindow = m_tCommandHandlerTimeWindow[1];
	pHistoryArchivalFiles.Copy(&m_pCommandHandlerFiles[0]);
	pHistoryRetrievalFiles.Copy(&m_pCommandHandlerFiles[1]);
	szDefaultHistoryFileName = m_szCommandHandlerFileName;
	return TRUE;
}
BOOL CTCProcessInterfaceThread::GetCommandHandlerConfiguration(CTCProcessCommandSources &pCommandSources, UINT &nTelecommandingMode, UINT &nTelecommandingState, UINT &nTelecommandingFlags, BOOL &bTelecommandingInterlockMode, BOOL &bTelecommandingReleaseWaitMode, BOOL &bTelecommandingAutoRejectionMode, CTimeSpan &tVerificationUncertaintyTimeWindow, CTimeSpan &tMaximumExecutionTimePeriod, CTimeSpan &tMaximumTimeCheckPeriod, CTimeSpan &tDefaultReleaseTimeWindow, CTCItems &pItems, CTCInterlocks &pInterlocks, CHistoryStoreFiles &pHistoryArchivalFiles, CHistoryStoreFiles &pHistoryRetrievalFiles, CString &szDefaultHistoryFileName, HWND hUpdateWnd, UINT_PTR nUpdateTimerID, BOOL &bUpdate)
{
	CComputerToken  cComputerToken;
	CTCChainLock  cLock(this);

	if (GetCommandHandlerConfiguration(cComputerToken.GetComputerName(), pCommandSources, nTelecommandingMode, nTelecommandingState, nTelecommandingFlags, bTelecommandingInterlockMode, bTelecommandingReleaseWaitMode, bTelecommandingAutoRejectionMode, tVerificationUncertaintyTimeWindow, tMaximumExecutionTimePeriod, tMaximumTimeCheckPeriod, tDefaultReleaseTimeWindow, pItems, pInterlocks, pHistoryArchivalFiles, pHistoryRetrievalFiles, szDefaultHistoryFileName, bUpdate))
	{
		m_nCommandHandlerTimerID[2] = nUpdateTimerID;
		m_hCommandHandlerWnd = hUpdateWnd;
		return TRUE;
	}
	return FALSE;
}
BOOL CTCProcessInterfaceThread::GetCommandHandlerConfiguration(LPCTSTR pszOriginator, CTCProcessCommandSources &pCommandSources, UINT &nTelecommandingMode, UINT &nTelecommandingState, UINT &nTelecommandingFlags, BOOL &bTelecommandingInterlockMode, BOOL &bTelecommandingReleaseWaitMode, BOOL &bTelecommandingAutoRejectionMode, CTimeSpan &tVerificationUncertaintyTimeWindow, CTimeSpan &tMaximumExecutionTimePeriod, CTimeSpan &tMaximumTimeCheckPeriod, CTimeSpan &tDefaultReleaseTimeWindow, CTCItems &pItems, CTCInterlocks &pInterlocks, CHistoryStoreFiles &pHistoryArchivalFiles, CHistoryStoreFiles &pHistoryRetrievalFiles, CString &szDefaultHistoryFileName, BOOL &bUpdate)
{
	INT  nClient;
	INT  nClients;
	INT  nCommandSource;
	INT  nCommandSources;
	CString  szComputer;
	CTimeSpan  tOffset[2];
	CByteArray  nMessageData;
	CTCUplinkDevice  cDevice;
	CComputerToken  cComputerToken;
	CTCOnBoardBufferQueues  pQueues;
	CTCProcessInterfaceSocket  *pSocket;
	CTCProcessCommandSources  pServerCommandSources;
	CTCProcessCommandSources  pClientCommandSources;
	CTCProcessCommandSourceInfo  *pCommandSourceInfo[2];
	CTCProcessInterfaceGetCommandHandlerConfigurationRequest  cGetCommandHandlerConfigurationRequestMessage;
	CTCProcessInterfaceGetCommandHandlerConfigurationResponse  cGetCommandHandlerConfigurationResponseMessage;
	CTCChainLock  cLock(this);

	if (m_bCommandHandler[2])
	{
		for (nClient = 0, nClients = (INT)m_pClientSockets.GetSize(), pCommandSources.RemoveAll(); nClient < nClients; nClient++)
		{
			if ((pSocket = m_pClientSockets.GetAt(nClient)) != (CTCProcessInterfaceSocket *)NULL  &&  pSocket->IsConnected(szComputer) && pSocket->GetCommandSources(pClientCommandSources))
			{
				for (nCommandSource = 0, nCommandSources = (INT)pClientCommandSources.GetSize(); nCommandSource < nCommandSources; nCommandSource++)
				{
					if ((pCommandSourceInfo[0] = pClientCommandSources.GetAt(nCommandSource)))
					{
						if ((pCommandSourceInfo[1] = new CTCProcessCommandSourceInfo))
						{
							pCommandSourceInfo[1]->Copy(pCommandSourceInfo[0]);
							if (pCommandSources.Add(pCommandSourceInfo[1]) >= 0) continue;
							delete pCommandSourceInfo[1];
						}
					}
					break;
				}
				if (nCommandSource == nCommandSources) continue;
			}
			break;
		}
		for (nCommandSource = 0, nCommandSources = (m_cSocket.GetCommandSources(pServerCommandSources)) ? (INT)pServerCommandSources.GetSize() : -1; nCommandSource < nCommandSources; nCommandSource++)
		{
			if ((pCommandSourceInfo[0] = pServerCommandSources.GetAt(nCommandSource)))
			{
				if ((pCommandSourceInfo[1] = new CTCProcessCommandSourceInfo))
				{
					pCommandSourceInfo[1]->Copy(pCommandSourceInfo[0]);
					if (pCommandSources.Add(pCommandSourceInfo[1]) >= 0) continue;
					delete pCommandSourceInfo[1];
				}
			}
			break;
		}
		if (GetCommandHandlerContents(pItems, pInterlocks, pQueues) && nClient == nClients  &&  nCommandSource == nCommandSources)
		{
			for (nTelecommandingMode = m_nCommandHandlerTelecommandingMode, nTelecommandingState = m_nCommandHandlerTelecommandingState, nTelecommandingFlags = m_nCommandHandlerTelecommandingFlags, bTelecommandingInterlockMode = m_bCommandHandlerTelecommandingInterlockMode, bTelecommandingReleaseWaitMode = m_bCommandHandlerTelecommandingReleaseWaitMode, bTelecommandingAutoRejectionMode = m_bCommandHandlerTelecommandingAutoRejectionMode, tVerificationUncertaintyTimeWindow = m_tCommandHandlerTimeWindow[0], tDefaultReleaseTimeWindow = m_tCommandHandlerTimeWindow[1], m_pTCProcessThread->GetTCFunctionExecutionTimeOffsets(tOffset[0], tMaximumExecutionTimePeriod), m_pTCProcessThread->GetTCFunctionParameterTimeOffsets(tOffset[1], tMaximumTimeCheckPeriod), pHistoryArchivalFiles.Copy(&m_pCommandHandlerFiles[0]), pHistoryRetrievalFiles.Copy(&m_pCommandHandlerFiles[1]), szDefaultHistoryFileName = m_szCommandHandlerFileName, bUpdate = (!m_bCommandHandlerUpdate && bUpdate) ? TRUE : FALSE, m_bCommandHandlerUpdate = m_bCommandHandlerUpdate || bUpdate; (pSocket = m_pClientSockets.GetAt(m_pClientSockets.Find(pszOriginator))); )
			{
				pSocket->SetFlags(((bUpdate) ? (pSocket->GetFlags() | TCSERVICE_COMMANDINTERFACE_CONFIGURATIONUPDATE) : (pSocket->GetFlags() & ~TCSERVICE_COMMANDINTERFACE_CONFIGURATIONUPDATE)) | TCSERVICE_COMMANDINTERFACE_HOTLINKUPDATE);
				break;
			}
			return TRUE;
		}
		return FALSE;
	}
	for (GetCommandHandlerState(&cDevice); cDevice.GetCommandHandlerState() & TCSERVICE_COMMANDHANDLERSTATE_LINK_GOOD; )
	{
		if (cGetCommandHandlerConfigurationRequestMessage.EnableUpdateFlag(bUpdate) && cGetCommandHandlerConfigurationRequestMessage.Map(nMessageData) && m_cSocket.SendAndReceive(nMessageData, m_tCommandHandlerTimeout) > 0 && cGetCommandHandlerConfigurationResponseMessage.Unmap(nMessageData) && cGetCommandHandlerConfigurationResponseMessage.GetConfiguration(pCommandSources, nTelecommandingMode, nTelecommandingState, nTelecommandingFlags, bTelecommandingInterlockMode, bTelecommandingReleaseWaitMode, bTelecommandingAutoRejectionMode, tVerificationUncertaintyTimeWindow, tMaximumExecutionTimePeriod, tMaximumTimeCheckPeriod, tDefaultReleaseTimeWindow, pItems, pInterlocks, pHistoryArchivalFiles, pHistoryRetrievalFiles, szDefaultHistoryFileName))
		{
			bUpdate = cGetCommandHandlerConfigurationResponseMessage.IsUpdateFlagEnabled();
			return TRUE;
		}
		break;
	}
	if (m_cSocket.GetCommandSources(pCommandSources))
	{
		if (GetCommandHandlerContents(pItems, pInterlocks, pQueues))
		{
			nTelecommandingMode = m_nCommandHandlerTelecommandingMode;
			nTelecommandingState = m_nCommandHandlerTelecommandingState;
			nTelecommandingFlags = m_nCommandHandlerTelecommandingFlags;
			bTelecommandingInterlockMode = m_bCommandHandlerTelecommandingInterlockMode;
			bTelecommandingReleaseWaitMode = m_bCommandHandlerTelecommandingReleaseWaitMode;
			bTelecommandingAutoRejectionMode = m_bCommandHandlerTelecommandingAutoRejectionMode;
			m_pTCProcessThread->GetTCFunctionExecutionTimeOffsets(tOffset[0], tMaximumExecutionTimePeriod);
			m_pTCProcessThread->GetTCFunctionParameterTimeOffsets(tOffset[1], tMaximumTimeCheckPeriod);
			tVerificationUncertaintyTimeWindow = m_tCommandHandlerTimeWindow[0];
			tDefaultReleaseTimeWindow = m_tCommandHandlerTimeWindow[1];
			pHistoryArchivalFiles.Copy(&m_pCommandHandlerFiles[0]);
			pHistoryRetrievalFiles.Copy(&m_pCommandHandlerFiles[1]);
			szDefaultHistoryFileName = m_szCommandHandlerFileName;
			bUpdate = FALSE;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CTCProcessInterfaceThread::SetCommandHandlerContents(CONST CTCItems &pItems, CONST CTCItems &pHistoricalItems, CONST CTCInterlocks &pInterlocks, CONST CTCOnBoardBufferQueues &pQueues)
{
	CTCChainLock  cLock(this);

	if (m_bCommandHandler[2])
	{
		if (m_pTCProcessThread->SetCommandHandlerContents(pItems, pHistoricalItems, pInterlocks, pQueues))
		{
			UpdateCommandHandler(TCSERVICE_COMMANDINTERFACE_TELECOMMANDSUPDATE | TCSERVICE_COMMANDINTERFACE_INTERLOCKSUPDATE | TCSERVICE_COMMANDINTERFACE_QUEUESUPDATE);
			UpdateCommandHandler(pItems, pInterlocks);
			return TRUE;
		}
		return FALSE;
	}
	UpdateCommandHandler(pItems, pInterlocks);
	return TRUE;
}
BOOL CTCProcessInterfaceThread::SetCommandHandlerContents(CONST CTCItems &pItems, CONST CTCInterlocks &pInterlocks, CONST CTCOnBoardBufferQueues &pQueues)
{
	CTCChainLock  cLock(this);

	if (m_bCommandHandler[2])
	{
		if (m_pTCProcessThread->SetCommandHandlerContents(pItems, pInterlocks, pQueues))
		{
			UpdateCommandHandler(TCSERVICE_COMMANDINTERFACE_TELECOMMANDSUPDATE | TCSERVICE_COMMANDINTERFACE_INTERLOCKSUPDATE | TCSERVICE_COMMANDINTERFACE_QUEUESUPDATE);
			UpdateCommandHandler(pItems, pInterlocks);
			return TRUE;
		}
		return FALSE;
	}
	UpdateCommandHandler(pItems, pInterlocks);
	return TRUE;
}

BOOL CTCProcessInterfaceThread::GetCommandHandlerContents(CTCItems &pItems, CTCItems &pHistoricalItems, CTCInterlocks &pInterlocks, CTCOnBoardBufferQueues &pQueues, BOOL bAny) CONST
{
	CTCChainLock  cLock(this);

	if (m_bCommandHandler[2] || bAny)
	{
		if (m_pTCProcessThread->GetCommandHandlerContents(pItems, pHistoricalItems, pInterlocks, pQueues, bAny)) return TRUE;
		return FALSE;
	}
	pItems.RemoveAll();
	pHistoricalItems.RemoveAll();
	pInterlocks.RemoveAll();
	pQueues.RemoveAll();
	return TRUE;
}
BOOL CTCProcessInterfaceThread::GetCommandHandlerContents(CTCItems &pItems, CTCInterlocks &pInterlocks, CTCOnBoardBufferQueues &pQueues, BOOL bAny) CONST
{
	CTCChainLock  cLock(this);

	if (m_bCommandHandler[2] || bAny)
	{
		if (m_pTCProcessThread->GetCommandHandlerContents(pItems, pInterlocks, pQueues, bAny)) return TRUE;
		return FALSE;
	}
	return((pItems.Copy(&m_pCommandHandlerItems) && pInterlocks.Copy(&m_pCommandHandlerInterlocks) && pQueues.Copy(&m_pCommandHandlerQueues)) ? TRUE : FALSE);
}

BOOL CTCProcessInterfaceThread::SetCommandHandlerState(CONST CTCUplinkDevice *pDevice)
{
	CTCChainLock  cLock(this);

	for (m_pTCProcessThread->SetCommandHandlerState(pDevice); m_bCommandHandler[2]; )
	{
		UpdateCommandingState(pDevice);
		break;
	}
	return TRUE;
}
BOOL CTCProcessInterfaceThread::SetCommandHandlerState(LPCTSTR pszCommandHandler, UINT nState)
{
	CTCUplinkDevice  cDevice;
	CTCChainLock  cLock(this);

	for (GetCommandHandlerState(&cDevice); cDevice.GetCommandHandler().CompareNoCase(pszCommandHandler) || (cDevice.GetCommandHandlerState() & nState) != nState; )
	{
		if (nState & TCSERVICE_COMMANDHANDLERSTATE_RUNNING) m_nCommandHandlerTelecommandingState = (m_nCommandHandlerTelecommandingState & ~TCSERVICE_COMMANDHANDLERSTATE_STOPPED) | TCSERVICE_COMMANDHANDLERSTATE_RUNNING;
		if (nState & TCSERVICE_COMMANDHANDLERSTATE_STOPPED) m_nCommandHandlerTelecommandingState = (m_nCommandHandlerTelecommandingState & ~TCSERVICE_COMMANDHANDLERSTATE_RUNNING) | TCSERVICE_COMMANDHANDLERSTATE_STOPPED;
		if (nState & TCSERVICE_COMMANDHANDLERSTATE_ENABLED) m_nCommandHandlerTelecommandingState = (m_nCommandHandlerTelecommandingState & ~TCSERVICE_COMMANDHANDLERSTATE_DISABLED) | TCSERVICE_COMMANDHANDLERSTATE_ENABLED;
		if (nState & TCSERVICE_COMMANDHANDLERSTATE_DISABLED)  m_nCommandHandlerTelecommandingState = (m_nCommandHandlerTelecommandingState & ~TCSERVICE_COMMANDHANDLERSTATE_ENABLED) | TCSERVICE_COMMANDHANDLERSTATE_DISABLED;
		if (nState & TCSERVICE_COMMANDHANDLERSTATE_LINK_GOOD) m_nCommandHandlerTelecommandingState = (m_nCommandHandlerTelecommandingState & ~TCSERVICE_COMMANDHANDLERSTATE_LINK_BAD) | TCSERVICE_COMMANDHANDLERSTATE_LINK_GOOD;
		if (nState & TCSERVICE_COMMANDHANDLERSTATE_LINK_BAD) m_nCommandHandlerTelecommandingState = (m_nCommandHandlerTelecommandingState & ~TCSERVICE_COMMANDHANDLERSTATE_LINK_GOOD) | TCSERVICE_COMMANDHANDLERSTATE_LINK_BAD;
		if (nState & TCSERVICE_COMMANDHANDLERSTATE_FRONTENDLINK_GOOD) m_nCommandHandlerTelecommandingState = (m_nCommandHandlerTelecommandingState & ~TCSERVICE_COMMANDHANDLERSTATE_FRONTENDLINK_BAD) | TCSERVICE_COMMANDHANDLERSTATE_FRONTENDLINK_GOOD;
		if (nState & TCSERVICE_COMMANDHANDLERSTATE_FRONTENDLINK_BAD) m_nCommandHandlerTelecommandingState = (m_nCommandHandlerTelecommandingState & ~TCSERVICE_COMMANDHANDLERSTATE_FRONTENDLINK_GOOD) | TCSERVICE_COMMANDHANDLERSTATE_FRONTENDLINK_BAD;
		if (nState & TCSERVICE_COMMANDHANDLERSTATE_FRONTEND_OK) m_nCommandHandlerTelecommandingState = (m_nCommandHandlerTelecommandingState & ~TCSERVICE_COMMANDHANDLERSTATE_FRONTEND_NOTOK) | TCSERVICE_COMMANDHANDLERSTATE_FRONTEND_OK;
		if (nState & TCSERVICE_COMMANDHANDLERSTATE_FRONTEND_NOTOK) m_nCommandHandlerTelecommandingState = (m_nCommandHandlerTelecommandingState & ~TCSERVICE_COMMANDHANDLERSTATE_FRONTEND_OK) | TCSERVICE_COMMANDHANDLERSTATE_FRONTEND_NOTOK;
		cDevice.SetCommandHandlerState(m_nCommandHandlerTelecommandingState);
		cDevice.SetCommandHandler(pszCommandHandler);
		return SetCommandHandlerState(&cDevice);
	}
	return TRUE;
}
BOOL CTCProcessInterfaceThread::SetCommandHandlerState(UINT nState)
{
	CTCUplinkDevice  cDevice;
	CTCChainLock  cLock(this);

	return((GetCommandHandlerState(&cDevice)) ? (((cDevice.GetCommandHandlerState() & nState) != nState) ? SetCommandHandlerState(cDevice.GetCommandHandler(), nState) : TRUE) : FALSE);
}

BOOL CTCProcessInterfaceThread::GetCommandHandlerState(CTCUplinkDevice *pDevice) CONST
{
	CTCChainLock  cLock(this);

	return m_pTCProcessThread->GetCommandHandlerState(pDevice);
}

BOOL CTCProcessInterfaceThread::SetCommandHandlerVerificationUncertaintyTimeWindow(CONST CTimeSpan &tTimeWindow)
{
	CTCChainLock  cLock(this);

	m_tCommandHandlerTimeWindow[0] = tTimeWindow;
	return TRUE;
}

BOOL CTCProcessInterfaceThread::GetCommandHandlerVerificationUncertaintyTimeWindow(CTimeSpan &tTimeWindow) CONST
{
	CTCChainLock  cLock(this);

	tTimeWindow = m_tCommandHandlerTimeWindow[0];
	return TRUE;
}

BOOL CTCProcessInterfaceThread::SetCommandHandlerDefaultReleaseTimeWindow(CONST CTimeSpan &tTimeWindow)
{
	CTCChainLock  cLock(this);

	m_tCommandHandlerTimeWindow[1] = tTimeWindow;
	return TRUE;
}

BOOL CTCProcessInterfaceThread::GetCommandHandlerDefaultReleaseTimeWindow(CTimeSpan &tTimeWindow) CONST
{
	CTCChainLock  cLock(this);

	tTimeWindow = m_tCommandHandlerTimeWindow[1];
	return TRUE;
}

BOOL CTCProcessInterfaceThread::SetCommandHandlerOptions(UINT nOptions)
{
	CTCChainLock  cLock(this);

	m_nCommandHandlerOptions = nOptions;
	return TRUE;
}

UINT CTCProcessInterfaceThread::GetCommandHandlerOptions() CONST
{
	CTCChainLock  cLock(this);

	return m_nCommandHandlerOptions;
}

BOOL CTCProcessInterfaceThread::UpdateCommandHandler(LPCTSTR pszCommandHandler, BOOL bExclusive)
{
	CTCChainLock  cLock(this);

	if (m_bCommandHandler[2])
	{
		if ((m_szCommandHandler[2].CompareNoCase(pszCommandHandler) >= 0 && (m_bCommandHandlerExclusive == bExclusive)) || (!m_bCommandHandlerExclusive  &&  bExclusive))
		{
			SetCommandHandlerState(TCSERVICE_COMMANDHANDLERSTATE_STOPPED);
			m_szCommandHandler[2] = pszCommandHandler;
			m_bCommandHandler[2] = FALSE;
			m_bCommand[2] = TRUE;
			Update();
			return TRUE;
		}
	}
	return FALSE;
}
BOOL CTCProcessInterfaceThread::UpdateCommandHandler(CONST CTCItems &pItems, CONST CTCInterlocks &pInterlocks)
{
	CTCChainLock  cLock(this);

	for (m_pCommandHandlerItems.Copy(&pItems), m_pCommandHandlerInterlocks.Copy(&pInterlocks); !IsWindow(m_hCommandHandlerWnd) || SetTimer(m_hCommandHandlerWnd, m_nCommandHandlerTimerID[2], 0, NULL); ) return TRUE;
	return FALSE;
}
BOOL CTCProcessInterfaceThread::UpdateCommandHandler(CONST CTCItems &pItems)
{
	CTCChainLock  cLock(this);

	for (m_pCommandHandlerItems.Copy(&pItems); !IsWindow(m_hCommandHandlerWnd) || SetTimer(m_hCommandHandlerWnd, m_nCommandHandlerTimerID[2], 0, NULL); ) return TRUE;
	return FALSE;
}
BOOL CTCProcessInterfaceThread::UpdateCommandHandler(CONST CTCInterlocks &pInterlocks)
{
	CTCChainLock  cLock(this);

	for (m_pCommandHandlerInterlocks.Copy(&pInterlocks); !IsWindow(m_hCommandHandlerWnd) || SetTimer(m_hCommandHandlerWnd, m_nCommandHandlerTimerID[2], 0, NULL); ) return TRUE;
	return FALSE;
}
BOOL CTCProcessInterfaceThread::UpdateCommandHandler(UINT nFlags, BOOL bAll)
{
	INT  nClient;
	INT  nClients;
	BOOL  bClients;
	CTCItems  pItems;
	CByteArray  nMessageData;
	CTCInterlocks  pInterlocks;
	CTCOnBoardBufferQueues  pQueues;
	CTCProcessInterfaceSocket  *pSocket;
	CTCProcessInterfaceUpdateCommandSourcesContentsRequest  cUpdateCommandSourcesContentsRequestMessage;
	CTCChainLock  cLock(this);

	if (m_bCommandHandler[2])
	{
		for (nClient = 0, nClients = (INT)m_pClientSockets.GetSize(), bClients = FALSE; nClient < nClients; nClient++)
		{
			if ((!nClient && ((nFlags & TCSERVICE_COMMANDINTERFACE_TELECOMMANDSUPDATE) || (nFlags & TCSERVICE_COMMANDINTERFACE_INTERLOCKSUPDATE) || (nFlags & TCSERVICE_COMMANDINTERFACE_QUEUESUPDATE)) && GetCommandHandlerContents(pItems, pInterlocks, pQueues) && ((nFlags & TCSERVICE_COMMANDINTERFACE_TELECOMMANDSUPDATE) != TCSERVICE_COMMANDINTERFACE_TELECOMMANDSUPDATE || cUpdateCommandSourcesContentsRequestMessage.SetTelecommands(pItems)) && ((nFlags & TCSERVICE_COMMANDINTERFACE_INTERLOCKSUPDATE) != TCSERVICE_COMMANDINTERFACE_INTERLOCKSUPDATE || cUpdateCommandSourcesContentsRequestMessage.SetTCInterlocks(pInterlocks)) && ((nFlags & TCSERVICE_COMMANDINTERFACE_QUEUESUPDATE) != TCSERVICE_COMMANDINTERFACE_QUEUESUPDATE || cUpdateCommandSourcesContentsRequestMessage.SetTCOnBoardBufferQueues(pQueues)) && cUpdateCommandSourcesContentsRequestMessage.EnableAcknowledgment(FALSE) && cUpdateCommandSourcesContentsRequestMessage.Map(nMessageData)) || nClient > 0)
			{
				for (; (pSocket = m_pClientSockets.GetAt(nClient)) && ((pSocket->GetFlags() & TCSERVICE_COMMANDINTERFACE_HOTLINKUPDATE) || bAll); )
				{
					pSocket->SetFlags(((bClients = (!pSocket->Send(nMessageData)) ? TRUE : bClients)) ? (pSocket->GetFlags() | nFlags) : pSocket->GetFlags());
					break;
				}
				continue;
			}
			break;
		}
		if (GetCommandHandlerContents(pItems, pInterlocks, pQueues))
		{
			if (nFlags & TCSERVICE_COMMANDINTERFACE_TELECOMMANDSUPDATE) UpdateTelecommands(EMPTYSTRING, pItems);
			if (nFlags & TCSERVICE_COMMANDINTERFACE_INTERLOCKSUPDATE) UpdateTCInterlocks(EMPTYSTRING, pInterlocks);
			if (nFlags & TCSERVICE_COMMANDINTERFACE_QUEUESUPDATE) UpdateTCOnBoardBufferQueues(EMPTYSTRING, pQueues);
		}
		if (bClients) UpdateCommandingClients();
		return((nClient == nClients) ? TRUE : FALSE);
	}
	return FALSE;
}

BOOL CTCProcessInterfaceThread::IsCommandHandler() CONST
{
	CTCChainLock  cLock(this);

	return m_bCommandHandler[2];
}

BOOL CTCProcessInterfaceThread::SetCommandSources(CONST CTCProcessCommandSources &pCommandSources, BOOL bUpdate)
{
	CComputerToken  cComputerToken;

	return SetCommandSources(cComputerToken.GetComputerName(), pCommandSources, bUpdate);
}
BOOL CTCProcessInterfaceThread::SetCommandSources(LPCTSTR pszOriginator, CONST CTCProcessCommandSources &pCommandSources, BOOL bUpdate)
{
	INT  nClient[2];
	INT  nClients[2];
	INT  nCommandSource;
	INT  nCommandSources;
	CUIntArray  nClientIDs;
	CByteArray  nMessageData;
	CComputerToken  cComputerToken;
	CTCProcessInterfaceSocket  *pSocket;
	CTCProcessCommandSources  pHostCommandSources;
	CTCProcessCommandSources  pClientCommandSources;
	CTCProcessCommandSources  pBackupCommandSources;
	CTCProcessCommandSourceInfo  *pCommandSourceInfo[2];
	CTCProcessInterfaceUpdateCommandSourcesRequest  cUpdateCommandSourcesRequestMessage;
	CTCChainLock  cLock(this);

	for (nCommandSource = 0, nCommandSources = (INT)pCommandSources.GetSize(); nCommandSource < nCommandSources; nCommandSource++)
	{
		if ((pCommandSourceInfo[0] = pCommandSources.GetAt(nCommandSource)) && pCommandSourceInfo[0]->IsHost())
		{
			if ((pCommandSourceInfo[1] = new CTCProcessCommandSourceInfo))
			{
				pCommandSourceInfo[1]->Copy(pCommandSourceInfo[0]);
				if (pHostCommandSources.Add(pCommandSourceInfo[1]) >= 0) continue;
				delete pCommandSourceInfo[1];
			}
			break;
		}
	}
	for (; !m_bCommandHandler[2]; )
	{
		if (m_szCommandHandler[2].IsEmpty())
		{
			if (m_cSocket.SetCommandSources(pHostCommandSources))
			{
				m_bCommand[1] = TRUE;
				Update();
				return TRUE;
			}
			break;
		}
		for (; m_cSocket.SetCommandSources(pHostCommandSources); )
		{
			if (cUpdateCommandSourcesRequestMessage.SetCommandSources(pHostCommandSources) && cUpdateCommandSourcesRequestMessage.Map(nMessageData) && m_cSocket.Send(nMessageData)) return TRUE;
			break;
		}
		break;
	}
	if (m_bCommandHandler[2])
	{
		for (GetCommandSources(pBackupCommandSources); cComputerToken.GetComputerName().CompareNoCase(pszOriginator) || UpdateCommandSources(pHostCommandSources, bUpdate); )
		{
			for (nCommandSource = 0, nCommandSources = (pHostCommandSources.GetSize() > 0 && m_cSocket.SetCommandSources(pHostCommandSources)) ? (INT)pHostCommandSources.GetSize() : -1; nCommandSource < nCommandSources; nCommandSource++)
			{
				if ((pCommandSourceInfo[1] = ((pCommandSourceInfo[0] = pHostCommandSources.GetAt(nCommandSource))) ? pCommandSources.GetAt(pCommandSources.Find(pCommandSourceInfo[0]->GetComputerName(), pCommandSourceInfo[0]->GetSourceType())) : (CTCProcessCommandSourceInfo *)NULL))
				{
					pCommandSourceInfo[1]->Copy(pCommandSourceInfo[0]);
					continue;
				}
			}
			if (nCommandSources > 0)
			{
				UpdateCommandSources((cComputerToken.GetComputerName().CompareNoCase(pszOriginator)) ? pszOriginator : EMPTYSTRING, pHostCommandSources);
				UpdateCommandSources(pBackupCommandSources, pCommandSources);
			}
			for (nCommandSource = 0, nCommandSources = (INT)pCommandSources.GetSize(); nCommandSource < nCommandSources; nCommandSource++)
			{
				for (nClient[0] = 0, nClients[0] = ((pCommandSourceInfo[0] = pCommandSources.GetAt(nCommandSource)) && !pCommandSourceInfo[0]->IsHost()) ? (INT)m_pClientSockets.GetSize() : 0; nClient[0] < nClients[0]; nClient[0]++)
				{
					if ((pCommandSourceInfo[1] = ((pSocket = m_pClientSockets.GetAt(nClient[0])) && pSocket->GetCommandSources(pClientCommandSources)) ? pClientCommandSources.GetAt(pClientCommandSources.Find(pCommandSourceInfo[0]->GetComputerName(), pCommandSourceInfo[0]->GetSourceType())) : (CTCProcessCommandSourceInfo *)NULL))
					{
						for (nClient[1] = 0, nClients[1] = (INT)nClientIDs.GetSize(), pCommandSourceInfo[1]->Copy(pCommandSourceInfo[0]), pSocket->SetCommandSources(pClientCommandSources); nClient[1] < nClients[1]; nClient[1]++)
						{
							if (nClientIDs.GetAt(nClient[1]) == nClient[0]) break;
							continue;
						}
						if (nClient[1] == nClients[1])
						{
							nClientIDs.Add(nClient[0]);
							continue;
						}
					}
				}
			}
			for (nClient[0] = 0, nClients[0] = (INT)nClientIDs.GetSize(), nClients[1] = 0; nClient[0] < nClients[0]; nClient[0]++)
			{
				if ((pSocket = m_pClientSockets.GetAt(nClientIDs.GetAt(nClient[0]))) && pSocket->GetCommandSources(pClientCommandSources))
				{
					if (cUpdateCommandSourcesRequestMessage.SetCommandSources(pClientCommandSources) && cUpdateCommandSourcesRequestMessage.Map(nMessageData) && pSocket->Send(nMessageData))
					{
						nClients[1]++;
						continue;
					}
				}
			}
			for (m_pTCProcessThread->Update(); nCommandSource == nCommandSources && nClients[0] == nClients[1]; ) return TRUE;
			break;
		}
	}
	return FALSE;
}

BOOL CTCProcessInterfaceThread::GetCommandSources(CTCProcessCommandSources &pCommandSources) CONST
{
	INT  nClient;
	INT  nClients;
	INT  nCommandSource;
	INT  nCommandSources;
	CTCProcessInterfaceSocket  *pSocket;
	CTCProcessCommandSources  pClientCommandSources;
	CTCProcessCommandSourceInfo  *pCommandSourceInfo[2];
	CTCChainLock  cLock(this);

	for (nClient = 0, nClients = (m_cSocket.GetCommandSources(pCommandSources)) ? (INT)m_pClientSockets.GetSize() : -1; nClient < nClients; nClient++)
	{
		if ((pSocket = m_pClientSockets.GetAt(nClient)) != (CTCProcessInterfaceSocket *)NULL  &&  pSocket->GetCommandSources(pClientCommandSources))
		{
			for (nCommandSource = 0, nCommandSources = (INT)pClientCommandSources.GetSize(); nCommandSource < nCommandSources; nCommandSource++)
			{
				if ((pCommandSourceInfo[0] = pClientCommandSources.GetAt(nCommandSource)))
				{
					if ((pCommandSourceInfo[1] = new CTCProcessCommandSourceInfo))
					{
						pCommandSourceInfo[1]->Copy(pCommandSourceInfo[0]);
						if (pCommandSources.Add(pCommandSourceInfo[1]) >= 0) continue;
						delete pCommandSourceInfo[1];
					}
				}
				break;
			}
			if (nCommandSource == nCommandSources) continue;
		}
		break;
	}
	return((nClient == nClients) ? TRUE : FALSE);
}

BOOL CTCProcessInterfaceThread::UpdateCommandSources()
{
	INT  nClient[3];
	INT  nClients[3];
	CString  szClient;
	CComputerToken  cComputerToken;
	CTCProcessInterfaceSocket  *pSocket;
	CTCProcessCommandSources  pCommandSources;
	CTCProcessCommandSourceInfo  *pCommandSourceInfo;
	CTCChainLock  cLock(this);

	if (!m_bCommandHandler[2])
	{
		SetCommandHandlerState(TCSERVICE_COMMANDHANDLERSTATE_LINK_BAD);
		m_szCommandHandler[2].Empty();
		m_bCommandHandler[2] = FALSE;
		m_bCommand[1] = TRUE;
		Update();
		return TRUE;
	}
	if (IsShuttingDown())
	{
		SetCommandHandlerState(TCSERVICE_COMMANDHANDLERSTATE_LINK_BAD);
		m_bCommandHandlerUpdate = FALSE;
	}
	for (nClient[0] = 0, nClients[0] = (!IsShuttingDown()) ? (INT)m_pClientSockets.GetSize() : -1; nClient[0] < nClients[0]; nClient[0]++)
	{
		if ((pSocket = m_pClientSockets.GetAt(nClient[0])) && !pSocket->IsConnected() && pSocket->GetCommandSources(pCommandSources))
		{
			if ((pCommandSourceInfo = ((pCommandSourceInfo = pCommandSources.GetAt((INT)(pCommandSources.GetSize() - 1)))) ? pCommandSources.GetAt(pCommandSources.Find(pCommandSourceInfo->GetComputerName(), TCSERVICE_COMMANDSOURCETYPE_MANUALSTACK)) : (CTCProcessCommandSourceInfo *)NULL))
			{
				if (pCommandSourceInfo->GetTelecommandingMode() & TCSERVICE_COMMANDSOURCEMODE_MASTERMANUAL) break;
				continue;
			}
		}
	}
	if (nClient[0] != nClients[0])
	{
		for (nClient[1] = 0, nClients[1] = (IsShuttingDown()) ? (INT)m_pClientSockets.GetSize() : 0; nClient[1] < nClients[1]; nClient[1]++)
		{
			if ((pSocket = m_pClientSockets.GetAt(nClient[1])) && pSocket->IsConnected(szClient) && pSocket->GetCommandSources(pCommandSources))
			{
				if ((pCommandSourceInfo = pCommandSources.GetAt(pCommandSources.Find(szClient, TCSERVICE_COMMANDSOURCETYPE_MANUALSTACK))))
				{
					if (pCommandSourceInfo->GetTelecommandingMode() & TCSERVICE_COMMANDSOURCEMODE_MASTERMANUAL)
					{
						pCommandSourceInfo->SetTelecommandingMode(TCSERVICE_COMMANDSOURCEMODE_DEFAULT);
						SetCommandSources(cComputerToken.GetComputerName(), pCommandSources);
						break;
					}
				}
			}
		}
		for (nClient[1] = 0, nClients[1] = (INT)m_szCommandClients[0].GetSize(); nClient[1] < nClients[1]; nClient[1]++)
		{
			if (((pSocket = m_pClientSockets.GetAt(m_pClientSockets.Find(m_szCommandClients[0].GetAt(nClient[1])))) && pSocket->IsConnected(szClient) && pSocket->GetCommandSources(pCommandSources)) || (!m_szCommandClients[0].GetAt(nClient[1]).CompareNoCase((szClient = cComputerToken.GetComputerName())) && m_cSocket.GetCommandSources(pCommandSources)))
			{
				if ((pCommandSourceInfo = pCommandSources.GetAt(pCommandSources.Find(szClient, TCSERVICE_COMMANDSOURCETYPE_MANUALSTACK))) != (CTCProcessCommandSourceInfo *)NULL)
				{
					for (pCommandSourceInfo->SetTelecommandingState(pCommandSourceInfo->GetTelecommandingState() & ~TCSERVICE_COMMANDSOURCESTATE_DISABLED); m_szCommandClients[0].GetAt(nClient[1]).CompareNoCase(cComputerToken.GetComputerName()); )
					{
						pSocket->SetCommandSources(pCommandSources);
						break;
					}
					if (!m_szCommandClients[0].GetAt(nClient[1]).CompareNoCase(cComputerToken.GetComputerName())) m_cSocket.SetCommandSources(pCommandSources);
				}
			}
		}
		for (nClient[1] = 0, nClients[1] = (INT)m_szCommandClients[1].GetSize(); nClient[1] < nClients[1]; nClient[1]++)
		{
			if (((pSocket = m_pClientSockets.GetAt(m_pClientSockets.Find(m_szCommandClients[1].GetAt(nClient[1])))) && pSocket->IsConnected(szClient) && pSocket->GetCommandSources(pCommandSources)) || (!m_szCommandClients[1].GetAt(nClient[1]).CompareNoCase((szClient = cComputerToken.GetComputerName())) && m_cSocket.GetCommandSources(pCommandSources)))
			{
				if ((pCommandSourceInfo = pCommandSources.GetAt(pCommandSources.Find(szClient, TCSERVICE_COMMANDSOURCETYPE_AUTOMATICSTACK))) != (CTCProcessCommandSourceInfo *)NULL)
				{
					for (pCommandSourceInfo->SetTelecommandingState(pCommandSourceInfo->GetTelecommandingState() & ~TCSERVICE_COMMANDSOURCESTATE_DISABLED); m_szCommandClients[1].GetAt(nClient[1]).CompareNoCase(cComputerToken.GetComputerName()); )
					{
						pSocket->SetCommandSources(pCommandSources);
						break;
					}
					if (!m_szCommandClients[1].GetAt(nClient[1]).CompareNoCase(cComputerToken.GetComputerName())) m_cSocket.SetCommandSources(pCommandSources);
				}
			}
		}
		for (nClient[1] = 0, nClients[1] = (INT)m_szCommandClients[0].GetSize(); nClient[1] < nClients[1]; nClient[1]++)
		{
			if (((pSocket = m_pClientSockets.GetAt(m_pClientSockets.Find(m_szCommandClients[0].GetAt(nClient[1])))) && pSocket->IsConnected() && pSocket->GetCommandSources(pCommandSources)) || (!m_szCommandClients[0].GetAt(nClient[1]).CompareNoCase(cComputerToken.GetComputerName()) && m_cSocket.GetCommandSources(pCommandSources)))
			{
				for (nClient[2] = 0, nClients[2] = (INT)m_szCommandClients[1].GetSize(); nClient[2] < nClients[2]; nClient[2]++)
				{
					if (!m_szCommandClients[0].GetAt(nClient[1]).CompareNoCase(m_szCommandClients[1].GetAt(nClient[2])))
					{
						m_szCommandClients[1].RemoveAt(nClient[2]);
						break;
					}
				}
				SetCommandSources(cComputerToken.GetComputerName(), pCommandSources);
			}
			m_szCommandClients[0].RemoveAt(nClient[1]);
			nClients[1]--;
			nClient[1]--;
		}
		for (nClient[1] = 0, nClients[1] = (INT)m_szCommandClients[1].GetSize(); nClient[1] < nClients[1]; nClient[1]++)
		{
			if (((pSocket = m_pClientSockets.GetAt(m_pClientSockets.Find(m_szCommandClients[1].GetAt(nClient[1])))) && pSocket->IsConnected() && pSocket->GetCommandSources(pCommandSources)) || (!m_szCommandClients[1].GetAt(nClient[1]).CompareNoCase(cComputerToken.GetComputerName()) && m_cSocket.GetCommandSources(pCommandSources))) SetCommandSources(cComputerToken.GetComputerName(), pCommandSources);
			m_szCommandClients[1].RemoveAt(nClient[1]);
			nClients[1]--;
			nClient[1]--;
		}
	}
	for (nClient[0] = 0, nClients[0] = (INT)m_pClientSockets.GetSize(); nClient[0] < nClients[0]; nClient[0]++)
	{
		if ((pSocket = m_pClientSockets.GetAt(nClient[0])) != (CTCProcessInterfaceSocket *)NULL  &&  !pSocket->IsConnected())
		{
			m_bCommandHandlerUpdate = ((pSocket->GetFlags() & TCSERVICE_COMMANDINTERFACE_CONFIGURATIONUPDATE) != TCSERVICE_COMMANDINTERFACE_CONFIGURATIONUPDATE) ? m_bCommandHandlerUpdate : FALSE;
			RemoveClient(nClient[0]);
			nClients[0]--;
			nClient[0]--;
		}
	}
	return TRUE;
}
BOOL CTCProcessInterfaceThread::UpdateCommandSources(CTCProcessInterfaceSocket *pSocket)
{
	INT  nPos;
	UINT  nPort;
	UINT  nClient;
	UINT  nClients;
	CString  szClient[2];
	CString  szAddress[2];
	CString  szMessage[2];
	CTCChainLock  cLock(this);

	if (pSocket->IsConnected(szClient[0]) && pSocket->GetPeerName(szAddress[0], nPort))
	{
		for (nClient = 0, nClients = (UINT)m_szCommandHandlerClients[0].GetSize(); nClient < nClients; nClient++)
		{
			if ((nPos = m_szCommandHandlerClients[0].GetAt(nClient).Find(EOL)) >= 0)
			{
				szClient[1] = m_szCommandHandlerClients[0].GetAt(nClient).Left(nPos);
				szAddress[1] = m_szCommandHandlerClients[0].GetAt(nClient).Mid(nPos + 1);
				if (!szClient[0].CompareNoCase(szClient[1]) || !szAddress[0].Compare(szAddress[1])) break;
				continue;
			}
			if (!m_szCommandHandlerClients[0].GetAt(nClient).CompareNoCase(szClient[0])) break;
		}
		for (szClient[0].MakeUpper(); nClient == nClients && nClients > 0 && !m_szCommandHandlerClients[0].GetAt(nClients - 1).GetLength(); )
		{
			nClient = nClients - 1;
			break;
		}
		if (nClient < nClients)
		{
			if ((m_nCommandHandlerAccessCodes.GetAt(nClient) & TCSERVICE_COMMANDINTERFACE_AUDITACCESS) && m_bCommandHandler[2])
			{
				szMessage[0].Format(STRING(IDS_TELECOMMANDPROCESSINTERFACE_SECURITY_LOGOUT), (LPCTSTR)szClient[0], (LPCTSTR)szAddress[0]);
				szMessage[1].Format(STRING(IDS_TELECOMMANDPROCESSINTERFACE_SECURITY_ANONYMOUSLOGOUT), (LPCTSTR)szAddress[0]);
				ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, (szClient[0].CompareNoCase(STRING(IDS_TELECOMMANDPROCESSINTERFACE_SECURITY_ANONYMOUSUSER))) ? szMessage[0] : szMessage[1], FALSE);
			}
			return TRUE;
		}
	}
	return FALSE;
}
BOOL CTCProcessInterfaceThread::UpdateCommandSources(CONST CTCProcessCommandSources &pCommandSources)
{
	CComputerToken  cComputerToken;

	return UpdateCommandSources(cComputerToken.GetComputerName(), pCommandSources);
}
BOOL CTCProcessInterfaceThread::UpdateCommandSources(CONST CTCProcessCommandSources &pCommandSources, CONST CTCItems &pItems, CONST CTCItems &pHistoricalItems, CONST CTCInterlocks &pInterlocks, CONST CTCOnBoardBufferQueues &pQueues)
{
	CComputerToken  cComputerToken;

	return UpdateCommandSources(cComputerToken.GetComputerName(), pCommandSources, pItems, pHistoricalItems, pInterlocks, pQueues);
}
BOOL CTCProcessInterfaceThread::UpdateCommandSources(CTCProcessCommandSources &pCommandSources, BOOL bUpdate)
{
	INT  nClient[3];
	INT  nClients[3];
	INT  nCommandSource;
	INT  nCommandSources;
	CString  szClient;
	CComputerToken  cComputerToken;
	CTCProcessInterfaceSocket  *pSocket[2];
	CTCProcessCommandSources  pServerCommandSources;
	CTCProcessCommandSources  pClientCommandSources[2];
	CTCProcessCommandSourceInfo  *pCommandSourceInfo[3];
	CTCChainLock  cLock(this);

	if (m_bCommandHandler[2])
	{
		for (; (pCommandSourceInfo[0] = ((pCommandSourceInfo[0] = pCommandSources.GetAt((INT)(pCommandSources.GetSize() - 1)))) ? pCommandSources.GetAt(pCommandSources.Find(pCommandSourceInfo[0]->GetComputerName(), TCSERVICE_COMMANDSOURCETYPE_MANUALSTACK)) : (CTCProcessCommandSourceInfo *)NULL); )
		{
			for (; ((pSocket[0] = (pCommandSourceInfo[0]->GetTelecommandingMode() & TCSERVICE_COMMANDSOURCEMODE_MASTERMANUAL) ? m_pClientSockets.GetAt(m_pClientSockets.Find(pCommandSourceInfo[0]->GetComputerName())) : (CTCProcessInterfaceSocket *)NULL) && pSocket[0]->GetCommandSources(pClientCommandSources[0])) || ((pCommandSourceInfo[0]->GetTelecommandingMode() & TCSERVICE_COMMANDSOURCEMODE_MASTERMANUAL) && pCommandSourceInfo[0]->IsHost() && m_cSocket.GetCommandSources(pClientCommandSources[0])); )
			{
				if ((pCommandSourceInfo[1] = pClientCommandSources[0].GetAt(pClientCommandSources[0].Find(pCommandSourceInfo[0]->GetComputerName(), TCSERVICE_COMMANDSOURCETYPE_MANUALSTACK))) && (pCommandSourceInfo[1]->GetTelecommandingMode() & TCSERVICE_COMMANDSOURCEMODE_MASTERMANUAL) != TCSERVICE_COMMANDSOURCEMODE_MASTERMANUAL)
				{
					if ((pCommandSourceInfo[2] = (m_cSocket.GetCommandSources(pServerCommandSources)) ? pServerCommandSources.GetAt(pServerCommandSources.Find(cComputerToken.GetComputerName(), TCSERVICE_COMMANDSOURCETYPE_MANUALSTACK)) : (CTCProcessCommandSourceInfo *)NULL))
					{
						if ((pCommandSourceInfo[2]->GetTelecommandingMode() & TCSERVICE_COMMANDSOURCEMODE_MASTERMANUAL) != TCSERVICE_COMMANDSOURCEMODE_MASTERMANUAL)
						{
							for (nClient[0] = 0, nClients[0] = (INT)m_pClientSockets.GetSize(); nClient[0] < nClients[0]; nClient[0]++)
							{
								if ((pSocket[1] = m_pClientSockets.GetAt(nClient[0])) && pSocket[1]->IsConnected(szClient))
								{
									if ((pCommandSourceInfo[2] = (pSocket[1]->GetCommandSources(pClientCommandSources[1])) ? pClientCommandSources[1].GetAt(pClientCommandSources[1].Find(szClient, TCSERVICE_COMMANDSOURCETYPE_MANUALSTACK)) : (CTCProcessCommandSourceInfo *)NULL) && (pCommandSourceInfo[2]->GetTelecommandingMode() & TCSERVICE_COMMANDSOURCEMODE_MASTERMANUAL)) break;
									continue;
								}
							}
							for (nClient[1] = 0, nClients[1] = (nClient[0] == nClients[0]) ? nClients[0] : -1; nClient[1] < nClients[1]; nClient[1]++)
							{
								if ((pSocket[1] = m_pClientSockets.GetAt(nClient[1])) && pSocket[1]->IsConnected(szClient) && pCommandSourceInfo[0]->GetComputerName().CompareNoCase(szClient))
								{
									if ((pCommandSourceInfo[2] = (pSocket[1]->GetCommandSources(pClientCommandSources[1])) ? pClientCommandSources[1].GetAt(pClientCommandSources[1].Find(szClient, TCSERVICE_COMMANDSOURCETYPE_MANUALSTACK)) : (CTCProcessCommandSourceInfo *)NULL))
									{
										for (nClient[2] = 0, nClients[2] = ((pCommandSourceInfo[2]->GetTelecommandingState() & TCSERVICE_COMMANDSOURCESTATE_DISABLED) != TCSERVICE_COMMANDSOURCESTATE_DISABLED) ? (INT)m_szCommandClients[0].GetSize() : -1, pCommandSourceInfo[2]->SetTelecommandingState(pCommandSourceInfo[2]->GetTelecommandingState() | TCSERVICE_COMMANDSOURCESTATE_DISABLED); nClient[2] < nClients[2]; nClient[2]++)
										{
											if (!m_szCommandClients[0].GetAt(nClient[2]).CompareNoCase(szClient)) break;
											continue;
										}
										if (nClient[2] == nClients[2]) m_szCommandClients[0].Add(szClient);
									}
									if ((pCommandSourceInfo[2] = pClientCommandSources[1].GetAt(pClientCommandSources[1].Find(szClient, TCSERVICE_COMMANDSOURCETYPE_AUTOMATICSTACK))))
									{
										for (nClient[2] = 0, nClients[2] = ((pCommandSourceInfo[2]->GetTelecommandingState() & TCSERVICE_COMMANDSOURCESTATE_DISABLED) != TCSERVICE_COMMANDSOURCESTATE_DISABLED) ? (INT)m_szCommandClients[1].GetSize() : -1, pCommandSourceInfo[2]->SetTelecommandingState(pCommandSourceInfo[2]->GetTelecommandingState() | TCSERVICE_COMMANDSOURCESTATE_DISABLED); nClient[2] < nClients[2]; nClient[2]++)
										{
											if (!m_szCommandClients[1].GetAt(nClient[2]).CompareNoCase(szClient)) break;
											continue;
										}
										if (nClient[2] == nClients[2]) m_szCommandClients[1].Add(szClient);
									}
									if ((m_szCommandClients[0].GetSize() > 0 && m_szCommandClients[0].GetAt(m_szCommandClients[0].GetUpperBound()) == szClient) || (m_szCommandClients[1].GetSize() > 0 && m_szCommandClients[1].GetAt(m_szCommandClients[1].GetUpperBound()) == szClient)) SetCommandSources(pCommandSourceInfo[0]->GetComputerName(), pClientCommandSources[1]);
								}
								if (nClient[1] == nClients[1] - 1)
								{
									if ((pCommandSourceInfo[2] = pServerCommandSources.GetAt(pServerCommandSources.Find((szClient = cComputerToken.GetComputerName()), TCSERVICE_COMMANDSOURCETYPE_MANUALSTACK))) && !pCommandSourceInfo[0]->IsHost())
									{
										for (nClient[2] = 0, nClients[2] = ((pCommandSourceInfo[2]->GetTelecommandingState() & TCSERVICE_COMMANDSOURCESTATE_DISABLED) != TCSERVICE_COMMANDSOURCESTATE_DISABLED) ? (INT)m_szCommandClients[0].GetSize() : -1, pCommandSourceInfo[2]->SetTelecommandingState(pCommandSourceInfo[2]->GetTelecommandingState() | TCSERVICE_COMMANDSOURCESTATE_DISABLED); nClient[2] < nClients[2]; nClient[2]++)
										{
											if (!m_szCommandClients[0].GetAt(nClient[2]).CompareNoCase(szClient)) break;
											continue;
										}
										if (nClient[2] == nClients[2]) m_szCommandClients[0].Add(szClient);
									}
									if ((pCommandSourceInfo[2] = pServerCommandSources.GetAt(pServerCommandSources.Find(szClient, TCSERVICE_COMMANDSOURCETYPE_AUTOMATICSTACK))) && !pCommandSourceInfo[0]->IsHost())
									{
										for (nClient[2] = 0, nClients[2] = ((pCommandSourceInfo[2]->GetTelecommandingState() & TCSERVICE_COMMANDSOURCESTATE_DISABLED) != TCSERVICE_COMMANDSOURCESTATE_DISABLED) ? (INT)m_szCommandClients[1].GetSize() : -1, pCommandSourceInfo[2]->SetTelecommandingState(pCommandSourceInfo[2]->GetTelecommandingState() | TCSERVICE_COMMANDSOURCESTATE_DISABLED); nClient[2] < nClients[2]; nClient[2]++)
										{
											if (!m_szCommandClients[1].GetAt(nClient[2]).CompareNoCase(szClient)) break;
											continue;
										}
										if (nClient[2] == nClients[2]) m_szCommandClients[1].Add(szClient);
									}
									if ((m_szCommandClients[0].GetSize() > 0 && m_szCommandClients[0].GetAt(m_szCommandClients[0].GetUpperBound()) == szClient) || (m_szCommandClients[1].GetSize() > 0 && m_szCommandClients[1].GetAt(m_szCommandClients[1].GetUpperBound()) == szClient)) SetCommandSources(pCommandSourceInfo[0]->GetComputerName(), pServerCommandSources);
								}
							}
							if (nClient[1] == nClients[1]) break;
						}
					}
					pCommandSourceInfo[0]->SetTelecommandingMode(pCommandSourceInfo[1]->GetTelecommandingMode());
				}
				break;
			}
			if (((pSocket[0] = ((pCommandSourceInfo[0]->GetTelecommandingMode() & TCSERVICE_COMMANDSOURCEMODE_MASTERMANUAL) != TCSERVICE_COMMANDSOURCEMODE_MASTERMANUAL) ? m_pClientSockets.GetAt(m_pClientSockets.Find(pCommandSourceInfo[0]->GetComputerName())) : (CTCProcessInterfaceSocket *)NULL) && pSocket[0]->GetCommandSources(pClientCommandSources[0])) || ((pCommandSourceInfo[0]->GetTelecommandingMode() & TCSERVICE_COMMANDSOURCEMODE_MASTERMANUAL) != TCSERVICE_COMMANDSOURCEMODE_MASTERMANUAL  &&  pCommandSourceInfo[0]->IsHost() && m_cSocket.GetCommandSources(pClientCommandSources[0])))
			{
				if ((pCommandSourceInfo[1] = pClientCommandSources[0].GetAt(pClientCommandSources[0].Find(pCommandSourceInfo[0]->GetComputerName(), TCSERVICE_COMMANDSOURCETYPE_MANUALSTACK))))
				{
					if (pCommandSourceInfo[1]->GetTelecommandingMode() & TCSERVICE_COMMANDSOURCEMODE_MASTERMANUAL)
					{
						for (nClient[0] = 0, nClients[0] = (INT)m_szCommandClients[0].GetSize(); nClient[0] < nClients[0]; nClient[0]++)
						{
							if (((pSocket[1] = m_pClientSockets.GetAt(m_pClientSockets.Find(m_szCommandClients[0].GetAt(nClient[0])))) && pSocket[1]->IsConnected(szClient) && pSocket[1]->GetCommandSources(pClientCommandSources[1])) || (!m_szCommandClients[0].GetAt(nClient[0]).CompareNoCase((szClient = cComputerToken.GetComputerName())) && m_cSocket.GetCommandSources(pClientCommandSources[1])))
							{
								if ((pCommandSourceInfo[2] = pClientCommandSources[1].GetAt(pClientCommandSources[1].Find(szClient, TCSERVICE_COMMANDSOURCETYPE_MANUALSTACK))) != (CTCProcessCommandSourceInfo *)NULL)
								{
									for (pCommandSourceInfo[2]->SetTelecommandingState(pCommandSourceInfo[2]->GetTelecommandingState() & ~TCSERVICE_COMMANDSOURCESTATE_DISABLED); m_szCommandClients[0].GetAt(nClient[0]).CompareNoCase(cComputerToken.GetComputerName()); )
									{
										pSocket[1]->SetCommandSources(pClientCommandSources[1]);
										break;
									}
									if (!m_szCommandClients[0].GetAt(nClient[0]).CompareNoCase(cComputerToken.GetComputerName())) m_cSocket.SetCommandSources(pClientCommandSources[1]);
								}
							}
						}
						for (nClient[0] = 0, nClients[0] = (INT)m_szCommandClients[1].GetSize(); nClient[0] < nClients[0]; nClient[0]++)
						{
							if (((pSocket[1] = m_pClientSockets.GetAt(m_pClientSockets.Find(m_szCommandClients[1].GetAt(nClient[0])))) && pSocket[1]->IsConnected(szClient) && pSocket[1]->GetCommandSources(pClientCommandSources[1])) || (!m_szCommandClients[1].GetAt(nClient[0]).CompareNoCase((szClient = cComputerToken.GetComputerName())) && m_cSocket.GetCommandSources(pClientCommandSources[1])))
							{
								if ((pCommandSourceInfo[2] = pClientCommandSources[1].GetAt(pClientCommandSources[1].Find(szClient, TCSERVICE_COMMANDSOURCETYPE_AUTOMATICSTACK))) != (CTCProcessCommandSourceInfo *)NULL)
								{
									for (pCommandSourceInfo[2]->SetTelecommandingState(pCommandSourceInfo[2]->GetTelecommandingState() & ~TCSERVICE_COMMANDSOURCESTATE_DISABLED); m_szCommandClients[1].GetAt(nClient[0]).CompareNoCase(cComputerToken.GetComputerName()); )
									{
										pSocket[1]->SetCommandSources(pClientCommandSources[1]);
										break;
									}
									if (!m_szCommandClients[1].GetAt(nClient[0]).CompareNoCase(cComputerToken.GetComputerName())) m_cSocket.SetCommandSources(pClientCommandSources[1]);
								}
							}
						}
						for (nClient[0] = 0, nClients[0] = (INT)m_szCommandClients[0].GetSize(); nClient[0] < nClients[0]; nClient[0]++)
						{
							if (((pSocket[1] = m_pClientSockets.GetAt(m_pClientSockets.Find(m_szCommandClients[0].GetAt(nClient[0])))) && pSocket[1]->IsConnected() && pSocket[1]->GetCommandSources(pClientCommandSources[1])) || (!m_szCommandClients[0].GetAt(nClient[0]).CompareNoCase(cComputerToken.GetComputerName()) && m_cSocket.GetCommandSources(pClientCommandSources[1])))
							{
								for (nClient[1] = 0, nClients[1] = (INT)m_szCommandClients[1].GetSize(); nClient[1] < nClients[1]; nClient[1]++)
								{
									if (!m_szCommandClients[0].GetAt(nClient[0]).CompareNoCase(m_szCommandClients[1].GetAt(nClient[1])))
									{
										m_szCommandClients[1].RemoveAt(nClient[1]);
										break;
									}
								}
								SetCommandSources(pCommandSourceInfo[0]->GetComputerName(), pClientCommandSources[1]);
							}
							m_szCommandClients[0].RemoveAt(nClient[0]);
							nClients[0]--;
							nClient[0]--;
						}
						for (nClient[0] = 0, nClients[0] = (INT)m_szCommandClients[1].GetSize(); nClient[0] < nClients[0]; nClient[0]++)
						{
							if (((pSocket[1] = m_pClientSockets.GetAt(m_pClientSockets.Find(m_szCommandClients[1].GetAt(nClient[0])))) && pSocket[1]->IsConnected() && pSocket[1]->GetCommandSources(pClientCommandSources[1])) || (!m_szCommandClients[1].GetAt(nClient[0]).CompareNoCase(cComputerToken.GetComputerName()) && m_cSocket.GetCommandSources(pClientCommandSources[1]))) SetCommandSources(pCommandSourceInfo[0]->GetComputerName(), pClientCommandSources[1]);
							m_szCommandClients[1].RemoveAt(nClient[0]);
							nClients[0]--;
							nClient[0]--;
						}
					}
				}
			}
			if (((pSocket[0] = ((pCommandSourceInfo[0]->GetTelecommandingState() & TCSERVICE_COMMANDSOURCESTATE_DISABLED) != TCSERVICE_COMMANDSOURCESTATE_DISABLED) ? m_pClientSockets.GetAt(m_pClientSockets.Find(pCommandSourceInfo[0]->GetComputerName())) : (CTCProcessInterfaceSocket *)NULL) && pSocket[0]->GetCommandSources(pClientCommandSources[0])) || ((pCommandSourceInfo[0]->GetTelecommandingState() & TCSERVICE_COMMANDSOURCESTATE_DISABLED) != TCSERVICE_COMMANDSOURCESTATE_DISABLED  &&  pCommandSourceInfo[0]->IsHost() && m_cSocket.GetCommandSources(pClientCommandSources[0])))
			{
				if ((pCommandSourceInfo[2] = (m_cSocket.GetCommandSources(pServerCommandSources)) ? pServerCommandSources.GetAt(pServerCommandSources.Find(cComputerToken.GetComputerName(), TCSERVICE_COMMANDSOURCETYPE_MANUALSTACK)) : (CTCProcessCommandSourceInfo *)NULL))
				{
					if ((pCommandSourceInfo[2]->GetTelecommandingMode() & TCSERVICE_COMMANDSOURCEMODE_MASTERMANUAL) != TCSERVICE_COMMANDSOURCEMODE_MASTERMANUAL || !pCommandSourceInfo[0]->GetComputerName().CompareNoCase(pCommandSourceInfo[2]->GetComputerName()))
					{
						for (nClient[0] = 0, nClients[0] = (INT)m_pClientSockets.GetSize(); nClient[0] < nClients[0]; nClient[0]++)
						{
							if ((pSocket[1] = m_pClientSockets.GetAt(nClient[0])) && pSocket[1]->IsConnected(szClient))
							{
								if ((pCommandSourceInfo[2] = (pSocket[1]->GetCommandSources(pClientCommandSources[1])) ? pClientCommandSources[1].GetAt(pClientCommandSources[1].Find(szClient, TCSERVICE_COMMANDSOURCETYPE_MANUALSTACK)) : (CTCProcessCommandSourceInfo *)NULL) && (pCommandSourceInfo[2]->GetTelecommandingMode() & TCSERVICE_COMMANDSOURCEMODE_MASTERMANUAL) && pCommandSourceInfo[0]->GetComputerName().CompareNoCase(pCommandSourceInfo[2]->GetComputerName())) break;
								continue;
							}
						}
						if (nClient[0] == nClients[0]) break;
					}
				}
				for (nClient[0] = 0, nClients[0] = (INT)m_szCommandClients[0].GetSize(), pCommandSourceInfo[0]->SetTelecommandingState(((pCommandSourceInfo[1] = pClientCommandSources[0].GetAt(pClientCommandSources[0].Find(pCommandSourceInfo[0]->GetComputerName(), TCSERVICE_COMMANDSOURCETYPE_MANUALSTACK)))) ? (pCommandSourceInfo[1]->GetTelecommandingState() | TCSERVICE_COMMANDSOURCESTATE_DISABLED) : (pCommandSourceInfo[0]->GetTelecommandingState() | TCSERVICE_COMMANDSOURCESTATE_DISABLED)); nClient[0] < nClients[0]; nClient[0]++)
				{
					if (!m_szCommandClients[0].GetAt(nClient[0]).CompareNoCase(pCommandSourceInfo[0]->GetComputerName())) break;
					continue;
				}
				if (nClient[0] == nClients[0]) m_szCommandClients[0].Add(pCommandSourceInfo[0]->GetComputerName());
			}
			break;
		}
		for (; (pCommandSourceInfo[0] = ((pCommandSourceInfo[0] = pCommandSources.GetAt((INT)(pCommandSources.GetSize() - 1)))) ? pCommandSources.GetAt(pCommandSources.Find(pCommandSourceInfo[0]->GetComputerName(), TCSERVICE_COMMANDSOURCETYPE_AUTOMATICSTACK)) : (CTCProcessCommandSourceInfo *)NULL); )
		{
			if (((pSocket[0] = ((pCommandSourceInfo[0]->GetTelecommandingState() & TCSERVICE_COMMANDSOURCESTATE_DISABLED) != TCSERVICE_COMMANDSOURCESTATE_DISABLED) ? m_pClientSockets.GetAt(m_pClientSockets.Find(pCommandSourceInfo[0]->GetComputerName())) : (CTCProcessInterfaceSocket *)NULL) && pSocket[0]->GetCommandSources(pClientCommandSources[0])) || ((pCommandSourceInfo[0]->GetTelecommandingState() & TCSERVICE_COMMANDSOURCESTATE_DISABLED) != TCSERVICE_COMMANDSOURCESTATE_DISABLED  &&  pCommandSourceInfo[0]->IsHost() && m_cSocket.GetCommandSources(pClientCommandSources[0])))
			{
				if ((pCommandSourceInfo[2] = (m_cSocket.GetCommandSources(pServerCommandSources)) ? pServerCommandSources.GetAt(pServerCommandSources.Find(cComputerToken.GetComputerName(), TCSERVICE_COMMANDSOURCETYPE_MANUALSTACK)) : (CTCProcessCommandSourceInfo *)NULL))
				{
					if ((pCommandSourceInfo[2]->GetTelecommandingMode() & TCSERVICE_COMMANDSOURCEMODE_MASTERMANUAL) != TCSERVICE_COMMANDSOURCEMODE_MASTERMANUAL || !pCommandSourceInfo[0]->GetComputerName().CompareNoCase(pCommandSourceInfo[2]->GetComputerName()))
					{
						for (nClient[0] = 0, nClients[0] = (INT)m_pClientSockets.GetSize(); nClient[0] < nClients[0]; nClient[0]++)
						{
							if ((pSocket[1] = m_pClientSockets.GetAt(nClient[0])) && pSocket[1]->IsConnected(szClient))
							{
								if ((pCommandSourceInfo[2] = (pSocket[1]->GetCommandSources(pClientCommandSources[1])) ? pClientCommandSources[1].GetAt(pClientCommandSources[1].Find(szClient, TCSERVICE_COMMANDSOURCETYPE_MANUALSTACK)) : (CTCProcessCommandSourceInfo *)NULL) && (pCommandSourceInfo[2]->GetTelecommandingMode() & TCSERVICE_COMMANDSOURCEMODE_MASTERMANUAL) && pCommandSourceInfo[0]->GetComputerName().CompareNoCase(pCommandSourceInfo[2]->GetComputerName())) break;
								continue;
							}
						}
						if (nClient[0] == nClients[0]) break;
					}
				}
				for (nClient[0] = 0, nClients[0] = (INT)m_szCommandClients[1].GetSize(), pCommandSourceInfo[0]->SetTelecommandingState(((pCommandSourceInfo[1] = pClientCommandSources[0].GetAt(pClientCommandSources[0].Find(pCommandSourceInfo[0]->GetComputerName(), TCSERVICE_COMMANDSOURCETYPE_AUTOMATICSTACK)))) ? (pCommandSourceInfo[1]->GetTelecommandingState() | TCSERVICE_COMMANDSOURCESTATE_DISABLED) : (pCommandSourceInfo[0]->GetTelecommandingState() | TCSERVICE_COMMANDSOURCESTATE_DISABLED)); nClient[0] < nClients[0]; nClient[0]++)
				{
					if (!m_szCommandClients[1].GetAt(nClient[0]).CompareNoCase(pCommandSourceInfo[0]->GetComputerName())) break;
					continue;
				}
				if (nClient[0] == nClients[0]) m_szCommandClients[1].Add(pCommandSourceInfo[0]->GetComputerName());
			}
			break;
		}
		for (nCommandSource = 0, nCommandSources = (bUpdate) ? (INT)pCommandSources.GetSize() : 0; nCommandSource < nCommandSources; nCommandSource++)
		{
			if ((pCommandSourceInfo[0] = pCommandSources.GetAt(nCommandSource)) != (CTCProcessCommandSourceInfo *)NULL)
			{
				for (pCommandSourceInfo[0]->SetTelecommandingState((m_nCommandHandlerTelecommandingState & TCSERVICE_COMMANDHANDLERSTATE_DISABLED) ? (pCommandSourceInfo[0]->GetTelecommandingState() | TCSERVICE_COMMANDSOURCESTATE_DISABLED) : (pCommandSourceInfo[0]->GetTelecommandingState() & ~TCSERVICE_COMMANDSOURCESTATE_DISABLED)), pCommandSourceInfo[0]->SetTelecommandingChecks(m_nCommandHandlerTelecommandingFlags), pCommandSourceInfo[0]->EnableTelecommandingReleaseWaitMode(m_bCommandHandlerTelecommandingReleaseWaitMode); pCommandSourceInfo[0]->GetSourceType() == TCSERVICE_COMMANDSOURCETYPE_MANUALSTACK; )
				{
					pCommandSourceInfo[0]->EnableTelecommandingAutoRejectionMode(m_bCommandHandlerTelecommandingAutoRejectionMode);
					break;
				}
				if (pCommandSourceInfo[0]->GetSourceType() != TCSERVICE_COMMANDSOURCETYPE_PROCEDURESMONITOR) pCommandSourceInfo[0]->EnableTelecommandingInterlockMode(m_bCommandHandlerTelecommandingInterlockMode);
			}
		}
	}
	return TRUE;
}
BOOL CTCProcessInterfaceThread::UpdateCommandSources(CTCProcessCommandSources &pCommandSources, CTCItems &pItems, CTCItems &pHistoricalItems, CTCInterlocks &pInterlocks, CTCOnBoardBufferQueues &pQueues, BOOL bUpdate)
{
	INT  nItem;
	INT  nItems;
	INT  nInterlock;
	INT  nInterlocks;
	CTCItem  *pItem;
	CTCInterlock  *pInterlock;
	CTCProcessCommandSourceInfo  *pCommandSourceInfo;
	CTCChainLock  cLock(this);

	if ((pCommandSourceInfo = (GetCommandHandlerContents(pItems, pHistoricalItems, pInterlocks, pQueues) && UpdateCommandSources(pCommandSources, bUpdate)) ? pCommandSources.GetAt((INT)(pCommandSources.GetSize() - 1)) : (CTCProcessCommandSourceInfo *)NULL))
	{
		for (nItem = 0, nItems = (INT)pItems.GetSize(); nItem < nItems; nItem++)
		{
			if ((pItem = pItems.GetAt(nItem)) != (CTCItem *)NULL)
			{
				if (pItem->GetComputerName().CompareNoCase(pCommandSourceInfo->GetComputerName()) && pItem->GetStatus() < TCITEM_STATUS_RELEASED)
				{
					pItems.RemoveAt(nItem);
					delete pItem;
					nItems--;
					nItem--;
				}
			}
		}
		for (nInterlock = 0, nInterlocks = (INT)pInterlocks.GetSize(); nInterlock < nInterlocks; nInterlock++)
		{
			if ((pInterlock = pInterlocks.GetAt(nInterlock)) && TCINTERLOCKSCOPEFROMCODE(pInterlock->GetScope()) != TCINTERLOCK_SCOPE_GLOBAL  &&  pInterlock->GetComputerName().CompareNoCase(pCommandSourceInfo->GetComputerName()))
			{
				pInterlocks.RemoveAt(nInterlock);
				delete pInterlock;
				nInterlocks--;
				nInterlock--;
			}
		}
		return TRUE;
	}
	return FALSE;
}
BOOL CTCProcessInterfaceThread::UpdateCommandSources(LPCTSTR pszOriginator, CONST CTCProcessCommandSources &pCommandSources)
{
	CTCChainLock  cLock(this);

	return m_pTCProcessThread->UpdateCommandSources(pszOriginator, pCommandSources);
}
BOOL CTCProcessInterfaceThread::UpdateCommandSources(LPCTSTR pszOriginator, CONST CTCProcessCommandSources &pCommandSources, CONST CTCItems &pItems, CONST CTCItems &pHistoricalItems, CONST CTCInterlocks &pInterlocks, CONST CTCOnBoardBufferQueues &pQueues)
{
	CTCChainLock  cLock(this);

	return m_pTCProcessThread->UpdateCommandSources(pszOriginator, pCommandSources, pItems, pHistoricalItems, pInterlocks, pQueues);
}

BOOL CTCProcessInterfaceThread::DispatchTelecommands(CONST CTCItems &pItems, BOOL bUndo)
{
	CByteArray  nMessageData;
	CTCProcessInterfaceDispatchTelecommandsRequest  cDispatchTelecommandsRequestMessage;
	CTCChainLock  cLock(this);

	return((!m_bCommandHandler[2]) ? (cDispatchTelecommandsRequestMessage.SetTelecommands(pItems, bUndo) && cDispatchTelecommandsRequestMessage.EnableAcknowledgment(FALSE) && cDispatchTelecommandsRequestMessage.Map(nMessageData) && m_cSocket.Send(nMessageData)) : m_pTCProcessThread->DispatchTelecommands(pItems, bUndo));
}

BOOL CTCProcessInterfaceThread::ReleaseTelecommands(CONST CTCItems &pItems)
{
	INT  nItem;
	INT  nItems;
	INT  nClient;
	INT  nClients;
	CString  szClient;
	CTCItem  *pCommandItem[2];
	CTCItems  pCommandItems[2];
	CByteArray  nMessageData;
	CTCProcessInterfaceSocket  *pSocket;
	CTCProcessInterfaceReleaseTelecommandsRequest  cReleaseTelecommandsRequestMessage;
	CTCChainLock  cLock(this);

	if (m_bCommandHandler[2])
	{
		for (nClient = 0, nClients = (pCommandItems[0].Copy(&pItems)) ? (INT)m_pClientSockets.GetSize() : -1; nClient < nClients && pCommandItems[0].GetSize() > 0; nClient++)
		{
			if ((pSocket = m_pClientSockets.GetAt(nClient)) != (CTCProcessInterfaceSocket *)NULL  &&  pSocket->IsConnected(szClient))
			{
				for (nItem = 0, nItems = (INT)pCommandItems[0].GetSize(), pCommandItems[1].RemoveAll(); nItem < nItems; nItem++)
				{
					if ((pCommandItem[0] = pCommandItems[0].GetAt(nItem)))
					{
						if ((pCommandItem[1] = new CTCItem))
						{
							if (!pCommandItem[0]->GetComputerName().CompareNoCase(szClient) || pCommandItem[0]->GetStatus() >= TCITEM_STATUS_RELEASED)
							{
								if (pCommandItem[1]->Copy(pCommandItem[0]) && pCommandItems[1].Add(pCommandItem[1]) >= 0)
								{
									pCommandItems[0].RemoveAt(nItem);
									delete pCommandItem[0];
									nItems--;
									nItem--;
									continue;
								}
								delete pCommandItem[1];
								break;
							}
							delete pCommandItem[1];
							continue;
						}
					}
					break;
				}
				if (nItem < nItems || (pCommandItems[1].GetSize() > 0 && (!cReleaseTelecommandsRequestMessage.SetTelecommands(pCommandItems[1]) || !cReleaseTelecommandsRequestMessage.EnableAcknowledgment(FALSE) || !cReleaseTelecommandsRequestMessage.Map(nMessageData) || !pSocket->Send(nMessageData))))
				{
					pSocket->SetFlags(pSocket->GetFlags() | TCSERVICE_COMMANDINTERFACE_TELECOMMANDSUPDATE);
					UpdateCommandingClients();
				}
			}
		}
		return((nClient == nClients) ? TRUE : FALSE);
	}
	return m_pTCProcessThread->ReleaseTelecommands(pItems);
}

BOOL CTCProcessInterfaceThread::UpdateTelecommands(CONST CTCItems &pItems, BOOL bAll)
{
	INT  nItem;
	INT  nItems;
	INT  nClient;
	INT  nClients;
	CString  szClient;
	CTCItem  *pCommandItem[2];
	CTCItems  pCommandItems;
	CByteArray  nMessageData;
	CTCProcessInterfaceSocket  *pSocket;
	CTCProcessInterfaceUpdateCommandSourcesContentsRequest  cUpdateCommandSourcesContentsRequestMessage;
	CTCChainLock  cLock(this);

	if (m_bCommandHandler[2])
	{
		for (nClient = 0, nClients = (INT)m_pClientSockets.GetSize(); nClient < nClients; nClient++)
		{
			if ((pSocket = m_pClientSockets.GetAt(nClient)) != (CTCProcessInterfaceSocket *)NULL  &&  pSocket->IsConnected(szClient))
			{
				for (nItem = 0, nItems = (INT)pItems.GetSize(), pCommandItems.RemoveAll(); nItem < nItems; nItem++)
				{
					if ((pCommandItem[0] = pItems.GetAt(nItem)))
					{
						if ((pCommandItem[1] = new CTCItem))
						{
							if (!pCommandItem[0]->GetComputerName().CompareNoCase(szClient) || pCommandItem[0]->GetStatus() >= TCITEM_STATUS_RELEASED)
							{
								if (pCommandItem[1]->Copy(pCommandItem[0]) && pCommandItems.Add(pCommandItem[1]) >= 0) continue;
								delete pCommandItem[1];
								break;
							}
							delete pCommandItem[1];
							continue;
						}
						break;
					}
				}
				if (nItem == nItems)
				{
					if (((bAll || pCommandItems.GetSize() > 0) && cUpdateCommandSourcesContentsRequestMessage.SetTelecommands(pCommandItems, bAll) && cUpdateCommandSourcesContentsRequestMessage.EnableAcknowledgment(FALSE) && cUpdateCommandSourcesContentsRequestMessage.Map(nMessageData) && pSocket->Send(nMessageData)) || (!bAll  &&  !pCommandItems.GetSize()))
					{
						cUpdateCommandSourcesContentsRequestMessage.Reset();
						continue;
					}
					cUpdateCommandSourcesContentsRequestMessage.Reset();
				}
				pSocket->SetFlags(pSocket->GetFlags() | TCSERVICE_COMMANDINTERFACE_TELECOMMANDSUPDATE);
				UpdateCommandingClients();
			}
		}
		if (pItems.GetSize() > 0 || bAll) UpdateTelecommands(EMPTYSTRING, pItems, bAll);
		if (!bAll) UpdateCommandHandler(TCSERVICE_COMMANDINTERFACE_TELECOMMANDSUPDATE);
		return((nClient == nClients) ? TRUE : FALSE);
	}
	return FALSE;
}
BOOL CTCProcessInterfaceThread::UpdateTelecommands(LPCTSTR pszOriginator, CONST CTCItems &pItems, BOOL bAll)
{
	CTCChainLock  cLock(this);

	for (; m_bCommandHandler[2] && lstrlen(pszOriginator) > 0; )
	{
		UpdateTelecommands(pItems, bAll);
		break;
	}
	for (m_pTCProcessThread->UpdateTelecommands(pszOriginator, pItems, bAll); bAll; )
	{
		UpdateCommandHandler(pItems);
		break;
	}
	return TRUE;
}

BOOL CTCProcessInterfaceThread::AcknowledgeTelecommands(CONST CTCItems &pItems)
{
	CByteArray  nMessageData;
	CTCProcessInterfaceAcknowledgeTelecommandsRequest  cAcknowledgeTelecommandsRequestMessage;
	CTCChainLock  cLock(this);

	return((!m_bCommandHandler[2]) ? (cAcknowledgeTelecommandsRequestMessage.SetTelecommands(pItems) && cAcknowledgeTelecommandsRequestMessage.EnableAcknowledgment(FALSE) && cAcknowledgeTelecommandsRequestMessage.Map(nMessageData) && m_cSocket.Send(nMessageData)) : m_pTCProcessThread->AcknowledgeTelecommands(pItems));
}

BOOL CTCProcessInterfaceThread::DiscardTelecommands(CONST CTCItems &pItems)
{
	CByteArray  nMessageData;
	CTCProcessInterfaceDiscardTelecommandsRequest  cDiscardTelecommandsRequestMessage;
	CTCChainLock  cLock(this);

	return((!m_bCommandHandler[2]) ? (cDiscardTelecommandsRequestMessage.SetTelecommands(pItems) && cDiscardTelecommandsRequestMessage.EnableAcknowledgment(FALSE) && cDiscardTelecommandsRequestMessage.Map(nMessageData) && m_cSocket.Send(nMessageData)) : m_pTCProcessThread->DiscardTelecommands(pItems));
}

BOOL CTCProcessInterfaceThread::ExecuteTelecommand(CONST CTCItem *pItem)
{
	INT  nClient;
	INT  nClients;
	CString  szClient;
	CByteArray  nMessageData;
	CTCProcessInterfaceSocket  *pSocket;
	CTCProcessInterfaceExecuteTelecommandRequest  cExecuteTelecommandRequestMessage;
	CTCProcessInterfaceExecuteTelecommandResponse  cExecuteTelecommandResponseMessage;
	CTCChainLock  cLock(this);

	if (m_bCommandHandler[2])
	{
		for (nClient = 0, nClients = (INT)m_pClientSockets.GetSize(); nClient < nClients; nClient++)
		{
			if ((pSocket = m_pClientSockets.GetAt(nClient)) && pSocket->IsConnected(szClient) && !pItem->GetComputerName().CompareNoCase(szClient))
			{
				if (cExecuteTelecommandRequestMessage.SetTelecommand(pItem) && cExecuteTelecommandRequestMessage.EnableAcknowledgment() && cExecuteTelecommandRequestMessage.Map(nMessageData) && pSocket->SendAndReceive(nMessageData, m_tCommandHandlerTimeout) > 0 && cExecuteTelecommandResponseMessage.Unmap(nMessageData) && cExecuteTelecommandResponseMessage.GetResult()) break;
				continue;
			}
		}
		return((nClient < nClients) ? TRUE : FALSE);
	}
	return(cExecuteTelecommandRequestMessage.SetTelecommand(pItem) && cExecuteTelecommandRequestMessage.EnableAcknowledgment() && cExecuteTelecommandRequestMessage.Map(nMessageData) && m_cSocket.SendAndReceive(nMessageData, m_tCommandHandlerTimeout) > 0 && cExecuteTelecommandResponseMessage.Unmap(nMessageData) && cExecuteTelecommandResponseMessage.GetResult());
}
BOOL CTCProcessInterfaceThread::ExecuteTelecommand(LPCTSTR pszOriginator, CONST CTCItem *pItem)
{
	CTCChainLock  cLock(this);

	return m_pTCProcessThread->ExecuteTelecommand(pszOriginator, pItem);
}

BOOL CTCProcessInterfaceThread::UpdateTCInterlocks(CONST CTCInterlocks &pInterlocks, BOOL bAll)
{
	INT  nClient;
	INT  nClients;
	INT  nInterlock;
	INT  nInterlocks;
	CString  szClient;
	CByteArray  nMessageData;
	CTCInterlock  *pCommandInterlock[2];
	CTCInterlocks  pCommandInterlocks;
	CTCProcessInterfaceSocket  *pSocket;
	CTCProcessInterfaceUpdateCommandSourcesContentsRequest  cUpdateCommandSourcesContentsRequestMessage;
	CTCChainLock  cLock(this);

	if (m_bCommandHandler[2])
	{
		for (nClient = 0, nClients = (INT)m_pClientSockets.GetSize(); nClient < nClients; nClient++)
		{
			if ((pSocket = m_pClientSockets.GetAt(nClient)) != (CTCProcessInterfaceSocket *)NULL  &&  pSocket->IsConnected(szClient))
			{
				for (nInterlock = 0, nInterlocks = (INT)pInterlocks.GetSize(), pCommandInterlocks.RemoveAll(); nInterlock < nInterlocks; nInterlock++)
				{
					if ((pCommandInterlock[0] = pInterlocks.GetAt(nInterlock)) && ((TCINTERLOCKSCOPEFROMCODE(pCommandInterlock[0]->GetScope()) == TCINTERLOCK_SCOPE_GLOBAL) || !pCommandInterlock[0]->GetComputerName().CompareNoCase(szClient) || bAll))
					{
						if ((pCommandInterlock[1] = new CTCInterlock))
						{
							pCommandInterlock[1]->Copy(pCommandInterlock[0]);
							if (pCommandInterlocks.Add(pCommandInterlock[1]) >= 0) continue;
							delete pCommandInterlock[1];
						}
						break;
					}
				}
				if (nInterlock == nInterlocks)
				{
					if (((bAll || pCommandInterlocks.GetSize() > 0) && cUpdateCommandSourcesContentsRequestMessage.SetTCInterlocks(pCommandInterlocks, bAll) && cUpdateCommandSourcesContentsRequestMessage.EnableAcknowledgment(FALSE) && cUpdateCommandSourcesContentsRequestMessage.Map(nMessageData) && pSocket->Send(nMessageData)) || (!bAll  &&  !pCommandInterlocks.GetSize()))
					{
						cUpdateCommandSourcesContentsRequestMessage.Reset();
						continue;
					}
					cUpdateCommandSourcesContentsRequestMessage.Reset();
				}
				pSocket->SetFlags(pSocket->GetFlags() | TCSERVICE_COMMANDINTERFACE_INTERLOCKSUPDATE);
				UpdateCommandingClients();
			}
		}
		if (pInterlocks.GetSize() > 0 || bAll) UpdateTCInterlocks(EMPTYSTRING, pInterlocks, bAll);
		if (!bAll) UpdateCommandHandler(TCSERVICE_COMMANDINTERFACE_INTERLOCKSUPDATE);
		return((nClient == nClients) ? TRUE : FALSE);
	}
	if (m_cSocket.IsConnected())
	{
		if (cUpdateCommandSourcesContentsRequestMessage.SetTCInterlocks(pInterlocks, bAll) && cUpdateCommandSourcesContentsRequestMessage.EnableAcknowledgment(FALSE) && cUpdateCommandSourcesContentsRequestMessage.Map(nMessageData) && m_cSocket.Send(nMessageData))
		{
			if (pInterlocks.GetSize() >= 0 && bAll) UpdateCommandHandler(pInterlocks);
			return TRUE;
		}
		m_cSocket.SetFlags(m_cSocket.GetFlags() | TCSERVICE_COMMANDINTERFACE_INTERLOCKSUPDATE);
		UpdateCommandingClients();
	}
	if (bAll) UpdateCommandHandler(pInterlocks);
	return FALSE;
}
BOOL CTCProcessInterfaceThread::UpdateTCInterlocks(LPCTSTR pszOriginator, CONST CTCInterlocks &pInterlocks, BOOL bAll)
{
	CTCChainLock  cLock(this);

	for (; m_bCommandHandler[2] && lstrlen(pszOriginator) > 0; )
	{
		UpdateTCInterlocks(pInterlocks, bAll);
		break;
	}
	for (m_pTCProcessThread->UpdateTCInterlocks(pszOriginator, pInterlocks, bAll); bAll; )
	{
		UpdateCommandHandler(pInterlocks);
		break;
	}
	return TRUE;
}

BOOL CTCProcessInterfaceThread::UpdateTCOnBoardBufferQueues(CONST CTCOnBoardBufferQueues &pQueues, BOOL bAll)
{
	INT  nClient;
	INT  nClients;
	CByteArray  nMessageData;
	CTCProcessInterfaceSocket  *pSocket;
	CTCProcessInterfaceUpdateCommandSourcesContentsRequest  cUpdateCommandSourcesContentsRequestMessage;
	CTCChainLock  cLock(this);

	if (m_bCommandHandler[2])
	{
		for (nClient = 0, nClients = (INT)m_pClientSockets.GetSize(); nClient < nClients; nClient++)
		{
			if ((pSocket = m_pClientSockets.GetAt(nClient)) != (CTCProcessInterfaceSocket *)NULL  &&  pSocket->IsConnected())
			{
				if (cUpdateCommandSourcesContentsRequestMessage.SetTCOnBoardBufferQueues(pQueues, bAll) && cUpdateCommandSourcesContentsRequestMessage.EnableAcknowledgment(FALSE) && cUpdateCommandSourcesContentsRequestMessage.Map(nMessageData) && pSocket->Send(nMessageData))
				{
					cUpdateCommandSourcesContentsRequestMessage.Reset();
					continue;
				}
				pSocket->SetFlags(pSocket->GetFlags() | TCSERVICE_COMMANDINTERFACE_QUEUESUPDATE);
				cUpdateCommandSourcesContentsRequestMessage.Reset();
				UpdateCommandingClients();
			}
		}
		for (UpdateTCOnBoardBufferQueues(EMPTYSTRING, pQueues, bAll); !bAll; )
		{
			UpdateCommandHandler(TCSERVICE_COMMANDINTERFACE_QUEUESUPDATE);
			break;
		}
		return TRUE;
	}
	if (m_cSocket.IsConnected())
	{
		if (cUpdateCommandSourcesContentsRequestMessage.SetTCOnBoardBufferQueues(pQueues, bAll) && cUpdateCommandSourcesContentsRequestMessage.EnableAcknowledgment(FALSE) && cUpdateCommandSourcesContentsRequestMessage.Map(nMessageData) && m_cSocket.Send(nMessageData)) return TRUE;
		m_cSocket.SetFlags(m_cSocket.GetFlags() | TCSERVICE_COMMANDINTERFACE_QUEUESUPDATE);
		UpdateCommandingClients();
	}
	return FALSE;
}
BOOL CTCProcessInterfaceThread::UpdateTCOnBoardBufferQueues(LPCTSTR pszOriginator, CONST CTCOnBoardBufferQueues &pQueues, BOOL bAll)
{
	CTCChainLock  cLock(this);

	for (; m_bCommandHandler[2] && lstrlen(pszOriginator) > 0; )
	{
		UpdateTCOnBoardBufferQueues(pQueues, bAll);
		break;
	}
	m_pTCProcessThread->UpdateTCOnBoardBufferQueues(pszOriginator, pQueues, bAll);
	return TRUE;
}

BOOL CTCProcessInterfaceThread::AnnounceCommandHandler(LPCTSTR pszComputer, LPCTSTR pszCommandHandler, BOOL bExclusive, CONST CTimeSpan &tTimeout)
{
	DWORD  cbData;
	CString  szName;
	CByteArray  nMessageData[2];
	CComputerToken  cComputerToken;
	CTCProcessInterfaceAnnounceCommandHandlerRequest  cAnnounceCommandHandlerRequestMessage;
	CTCProcessInterfaceAnnounceCommandHandlerResponse  cAnnounceCommandHandlerResponseMessage;

	for (szName.Format(STRING(IDS_TELECOMMANDPROCESSINTERFACE_PIPE_REMOTENAME), pszComputer), cAnnounceCommandHandlerRequestMessage.SetCommandHandler(pszCommandHandler, bExclusive), cAnnounceCommandHandlerRequestMessage.Map(nMessageData[0]), nMessageData[1].SetSize(10 * nMessageData[0].GetSize()); cComputerToken.GetComputerName().CompareNoCase(pszComputer) && CallNamedPipe(szName, nMessageData[0].GetData(), (DWORD)nMessageData[0].GetSize(), nMessageData[1].GetData(), (DWORD)nMessageData[1].GetSize(), &cbData, (DWORD)(1000 * tTimeout.GetTotalSeconds())); )
	{
		for (nMessageData[1].SetSize(cbData); cAnnounceCommandHandlerResponseMessage.Unmap(nMessageData[1]); ) return UpdateCommandHandler(cAnnounceCommandHandlerResponseMessage.GetCommandHandler(), cAnnounceCommandHandlerResponseMessage.IsExclusiveCommandHandler());
		break;
	}
	return FALSE;
}

BOOL CTCProcessInterfaceThread::RegisterCommandSources(LPCTSTR pszComputer, UINT nPort, CONST CTimeSpan &tTimeout, CTCProcessCommandSources &pCommandSources)
{
	CTCItems  pItems[2];
	CByteArray  nMessageData;
	CTCInterlocks  pInterlocks;
	CTCUplinkDevice  cDevice;
	CTCOnBoardBufferQueues  pQueues;
	CTCProcessInterfaceRegisterCommandSourcesRequest  cRegisterCommandSourcesRequestMessage;
	CTCProcessInterfaceRegisterCommandSourcesResponse  cRegisterCommandSourcesResponseMessage;

	if (m_cSocket.Open(this, 0, m_hObject))
	{
		if (m_cSocket.Connect(pszComputer, nPort, tTimeout))
		{
			if (GetCommandHandlerContents(pItems[0], pItems[1], pInterlocks, pQueues, TRUE) && cRegisterCommandSourcesRequestMessage.SetCommandSources(pCommandSources, pItems[0], pItems[1], pInterlocks, pQueues) && cRegisterCommandSourcesRequestMessage.Map(nMessageData) && m_cSocket.SendAndReceive(nMessageData, tTimeout) > 0 && cRegisterCommandSourcesResponseMessage.Unmap(nMessageData) && cRegisterCommandSourcesResponseMessage.GetCommandSources(pCommandSources) >= 0 && cRegisterCommandSourcesResponseMessage.GetCommandingDevice(&cDevice) && cRegisterCommandSourcesResponseMessage.GetTelecommands(pItems[0], pItems[1]) >= 0 && cRegisterCommandSourcesResponseMessage.GetTCInterlocks(pInterlocks) >= 0 && cRegisterCommandSourcesResponseMessage.GetTCOnBoardBufferQueues(pQueues) >= 0)
			{
				for (m_cSocket.SetCommandSources(pCommandSources); UpdateCommandSources(pCommandSources, pItems[0], pItems[1], pInterlocks, pQueues); )
				{
					if (SetCommandHandlerState(&cDevice) && SetCommandHandlerState(pszComputer, TCSERVICE_COMMANDHANDLERSTATE_LINK_GOOD)) return TRUE;
					break;
				}
			}
			m_cSocket.Close(TRUE);
			return FALSE;
		}
		m_cSocket.Close(TRUE);
	}
	return((Wait(TCPROCESSINTERFACETHREAD_CLIENTS_TIMEOUT) == WAIT_OBJECT_0 + 1) ? TRUE : FALSE);
}

BOOL CTCProcessInterfaceThread::UpdateCommandSources(CONST CTCProcessCommandSources &pBackupCommandSources, CONST CTCProcessCommandSources &pCommandSources)
{
	INT  nClient;
	INT  nClients;
	CTCProcessCommandSources  pCommandSourceCollection;
	CTCProcessCommandSourceInfo  *pCommandSourceInfo[3];

	for (nClient = 0, nClients = (GetCommandSources(pCommandSourceCollection)) ? (INT)pCommandSourceCollection.GetSize() : -1; nClient < nClients; nClient++)
	{
		if ((pCommandSourceInfo[1] = ((pCommandSourceInfo[0] = pCommandSourceCollection.GetAt(nClient))) ? pBackupCommandSources.GetAt(pBackupCommandSources.Find(pCommandSourceInfo[0]->GetComputerName(), pCommandSourceInfo[0]->GetSourceType())) : (CTCProcessCommandSourceInfo *)NULL))
		{
			if ((pCommandSourceInfo[0]->GetTelecommandingState() & TCSERVICE_COMMANDSOURCESTATE_DISABLED) != (pCommandSourceInfo[1]->GetTelecommandingState() & TCSERVICE_COMMANDSOURCESTATE_DISABLED))
			{
				if ((pCommandSourceInfo[2] = pCommandSources.GetAt(pCommandSources.Find(pCommandSourceInfo[0]->GetComputerName(), pCommandSourceInfo[0]->GetSourceType()))))
				{
					pCommandSourceInfo[2]->SetTelecommandingState((pCommandSourceInfo[2]->GetTelecommandingState() & ~TCSERVICE_COMMANDSOURCESTATE_DISABLED) | (pCommandSourceInfo[0]->GetTelecommandingState() & TCSERVICE_COMMANDSOURCESTATE_DISABLED));
					continue;
				}
			}
		}
	}
	return((nClient == nClients) ? TRUE : FALSE);
}

BOOL CTCProcessInterfaceThread::UpdateCommandingState(CONST CTCUplinkDevice *pDevice)
{
	INT  nCount;
	INT  nClient;
	INT  nClients;
	CByteArray  nMessageData;
	CTCProcessInterfaceSocket  *pSocket;
	CTCProcessInterfaceUpdateCommandUplinkDeviceState  cUpdateCommandUplinkDeviceStateMessage;

	for (nClient = 0, nClients = (cUpdateCommandUplinkDeviceStateMessage.SetCommandingDevice(pDevice) && cUpdateCommandUplinkDeviceStateMessage.Map(nMessageData)) ? (INT)m_pClientSockets.GetSize() : -1, nCount = 0; nClient < nClients; nClient++)
	{
		if ((pSocket = m_pClientSockets.GetAt(nClient)))
		{
			nCount = (pSocket->Send(nMessageData)) ? (nCount + 1) : nCount;
			continue;
		}
	}
	return((nClient == nClients  &&  nCount == nClients) ? TRUE : FALSE);
}

BOOL CTCProcessInterfaceThread::UpdateCommandingClients()
{
	if (!m_bCommand[3])
	{
		m_bCommand[3] = TRUE;
		return Update();
	}
	return TRUE;
}

BOOL CTCProcessInterfaceThread::IsShuttingDown() CONST
{
	return((WaitForSingleObject(m_hObject, 0) != WAIT_TIMEOUT) ? TRUE : FALSE);
}

int CTCProcessInterfaceThread::Run()
{
	UINT  nPort;
	UINT  nComputer;
	UINT  nComputers;
	BOOL  bExchange;
	BOOL  bExclusive;
	BOOL  bHandler[3];
	CString  szHandler[3];
	DWORD  dwResult;
	DWORD  dwTimeout;
	CTCItems  pItems;
	CTimeSpan  tTimeout;
	CByteArray  nData;
	CStringArray  szComputers;
	CTCInterlocks  pInterlocks;
	CComputerToken  cComputerToken;
	CTCOnBoardBufferQueues  pQueues;
	CTCProcessCommandSources  pCommandSources;

	for (dwTimeout = 0; (dwResult = Wait(m_cUpdate, FALSE, dwTimeout)) == WAIT_OBJECT_0 + 1 || dwResult == WAIT_TIMEOUT; )
	{
		for (Lock(); m_bCommand[0]; )
		{
			if (!m_bCommandHandler[2])
			{
				m_szCommandHandler[2].Empty();
				m_bCommand[0] = FALSE;
				m_bCommand[1] = TRUE;
				m_cSocket.Close();
				break;
			}
			if (m_bCommandHandler[2])
			{
				m_cSocket.Open(this, m_nCommandHandlerPort, m_hObject);
				m_pClientSockets.RemoveAll();
				m_bCommand[0] = FALSE;
			}
			break;
		}
		if (m_bCommand[1] || m_bCommand[2])
		{
			for (m_cSocket.GetCommandSources(pCommandSources), szHandler[0] = m_szCommandHandler[0], szHandler[1] = m_szCommandHandler[1], szHandler[2] = m_szCommandHandler[2], bHandler[0] = m_bCommandHandler[0], bHandler[1] = m_bCommandHandler[1], bHandler[2] = m_bCommandHandler[2], bExclusive = m_bCommandHandlerExclusive, bExchange = m_bCommand[2], nPort = m_nCommandHandlerPort, tTimeout = m_tCommandHandlerTimeout; m_bCommand[1]; )
			{
				m_nCommandHandlerTimerID[0] = SetTimer((HWND)NULL, TCPROCESSINTERFACETHREAD_UPDATECLIENTS_TIMERID, 0, NULL);
				break;
			}
			m_bCommand[1] = FALSE;
			m_bCommand[2] = FALSE;
		}
		if (m_bCommand[3])
		{
			m_nCommandHandlerTimerID[1] = SetTimer((HWND)NULL, TCPROCESSINTERFACETHREAD_UPDATECOMMANDS_TIMERID, 0, NULL);
			m_bCommand[3] = FALSE;
		}
		for (Unlock(); pCommandSources.GetSize() > 0; )
		{
			if ((szHandler[0].CompareNoCase(szHandler[2]) && szHandler[1].CompareNoCase(szHandler[2]) && !szHandler[0].IsEmpty() && !szHandler[1].IsEmpty()) || (!szHandler[2].CompareNoCase(cComputerToken.GetComputerName()) && !bHandler[0]) || (szHandler[2].CompareNoCase(cComputerToken.GetComputerName()) && !szHandler[2].IsEmpty() && !bHandler[1]) || (szHandler[2].IsEmpty() && (bHandler[0] || bHandler[1])) || (!szHandler[2].IsEmpty() && bExchange))
			{
				for (SetCommandHandlerState(TCSERVICE_COMMANDHANDLERSTATE_STOPPED | TCSERVICE_COMMANDHANDLERSTATE_LINK_BAD), m_cCommandHandlerThread.Stop(), m_cSocket.Close(), m_pClientSockets.RemoveAll(); !szHandler[2].IsEmpty() && bExchange; )
				{
					if (RegisterCommandSources(szHandler[2], nPort, tTimeout, pCommandSources)) break;
					szHandler[2].Empty();
					break;
				}
				if (szHandler[2].IsEmpty() || !bExchange)
				{
					if (szHandler[0].CompareNoCase(cComputerToken.GetComputerName()) && !szHandler[0].IsEmpty() && !IsShuttingDown())
					{
						if (RegisterCommandSources(szHandler[0], nPort, tTimeout, pCommandSources))
						{
							szHandler[2] = szHandler[0];
							break;
						}
						szHandler[2].Empty();
					}
					if (szHandler[1].CompareNoCase(cComputerToken.GetComputerName()) && !szHandler[1].IsEmpty() && !IsShuttingDown())
					{
						if (RegisterCommandSources(szHandler[1], nPort, tTimeout, pCommandSources))
						{
							szHandler[2] = szHandler[1];
							break;
						}
						szHandler[2].Empty();
					}
					for (nComputer = 0, nComputers = (bHandler[1]) ? GetNetworkBrowseService()->EnumNetworkComputers(szComputers) : 0; nComputer < nComputers; nComputer++)
					{
						if (szComputers.GetAt(nComputer).CompareNoCase(cComputerToken.GetComputerName()) && szComputers.GetAt(nComputer).CompareNoCase(szHandler[0]) && szComputers.GetAt(nComputer).CompareNoCase(szHandler[1]) && !IsShuttingDown())
						{
							if (RegisterCommandSources(szComputers.GetAt(nComputer), nPort, tTimeout, pCommandSources))
							{
								szHandler[2] = szComputers.GetAt(nComputer);
								break;
							}
							szHandler[2].Empty();
						}
					}
					if (nComputer == nComputers)
					{
						if (!szHandler[0].CompareNoCase(cComputerToken.GetComputerName()) || !szHandler[1].CompareNoCase(cComputerToken.GetComputerName()) || bHandler[0])
						{
							szHandler[2] = cComputerToken.GetComputerName();
							break;
						}
						szHandler[2].Empty();
					}
				}
			}
			break;
		}
		for (Lock(), dwTimeout = (!pCommandSources.GetSize() || !szHandler[2].IsEmpty() || (!bHandler[0] && !bHandler[1])) ? INFINITE : (1000 * TCSERVICE_COMMANDINTERFACE_MINIMUMTIMEOUT); m_szCommandHandler[2].CompareNoCase(szHandler[2]) && pCommandSources.GetSize() > 0; )
		{
			if (szHandler[2].IsEmpty())
			{
				m_cCommandHandlerThread.Stop();
				m_szCommandHandler[2].Empty();
				m_bCommandHandler[2] = FALSE;
				pCommandSources.RemoveAll();
				m_bCommand[1] = TRUE;
				m_cSocket.Close();
				break;
			}
			if (!szHandler[2].CompareNoCase(cComputerToken.GetComputerName()))
			{
				if (m_cCommandHandlerThread.Start(this, szHandler[2], bExclusive))
				{
					for (nComputer = 0, nComputers = GetNetworkBrowseService()->EnumNetworkComputers(szComputers), m_szCommandHandler[2] = szHandler[2], m_bCommandHandler[2] = TRUE, Unlock(); nComputer < nComputers; nComputer++)
					{
						if (AnnounceCommandHandler(szComputers.GetAt(nComputer), szHandler[2], bExclusive, TCSERVICE_COMMANDINTERFACE_MINIMUMTIMEOUT))
						{
							m_cCommandHandlerThread.Stop();
							break;
						}
					}
					Lock();
					if (nComputer == nComputers)
					{
						if (m_cSocket.Open(this, m_nCommandHandlerPort, m_hObject))
						{
							for (SetCommandHandlerState(szHandler[2], TCSERVICE_COMMANDHANDLERSTATE_RUNNING | TCSERVICE_COMMANDHANDLERSTATE_LINK_GOOD); SetCommandSources(pCommandSources, TRUE); )
							{
								for (UpdateCommandSources(pCommandSources); GetCommandHandlerContents(pItems, pInterlocks, pQueues); )
								{
									if (pItems.GetSize() > 0) UpdateTelecommands(EMPTYSTRING, pItems);
									if (pInterlocks.GetSize() > 0) UpdateTCInterlocks(EMPTYSTRING, pInterlocks);
									break;
								}
								break;
							}
							pCommandSources.RemoveAll();
							break;
						}
						m_cCommandHandlerThread.Stop();
					}
					m_szCommandHandler[2].Empty();
					m_bCommandHandler[2] = FALSE;
				}
				SetCommandHandlerState(TCSERVICE_COMMANDHANDLERSTATE_STOPPED);
				pCommandSources.RemoveAll();
				m_bCommand[1] = TRUE;
				dwTimeout = 0;
				break;
			}
			SetCommandHandlerState(szHandler[2], TCSERVICE_COMMANDHANDLERSTATE_STOPPED | TCSERVICE_COMMANDHANDLERSTATE_LINK_GOOD);
			m_cSocket.SetCommandSources(pCommandSources);
			m_szCommandHandler[2] = szHandler[2];
			m_bCommandHandler[2] = FALSE;
			m_cCommandHandlerThread.Stop();
			pCommandSources.RemoveAll();
			break;
		}
		Unlock();
	}
	return ExitInstance();
}

BOOL CTCProcessInterfaceThread::PreTranslateMessage(MSG *pMsg)
{
	INT  nItem;
	INT  nItems;
	INT  nCount;
	INT  nClient[2];
	INT  nClients[2];
	INT  nInterlock;
	INT  nInterlocks;
	CString  szClient;
	CTCItem  *pItem[2];
	CTCItems  pItems[2];
	CTimeKey  tTime[2];
	CByteArray  nMessageData;
	CTCInterlock  *pInterlock[2];
	CTCInterlocks  pInterlocks[2];
	CTCOnBoardBufferQueues  pQueues;
	CTCProcessInterfaceSocket  *pSocket;
	CTCProcessInterfaceUpdateCommandSourcesContentsRequest  cUpdateCommandSourcesContentsRequestMessage;
	CTCProcessInterfaceUpdateCommandSourcesContentsResponse  cUpdateCommandSourcesContentsResponseMessage;

	if (pMsg->message == WM_TIMER)
	{
		if (pMsg->wParam == m_nCommandHandlerTimerID[0])
		{
			for (Lock(), nClient[0] = 0, nClients[0] = (INT)m_szCommandHandlerClients[0].GetSize(), tTime[0] = 0, KillTimer((HWND)NULL, m_nCommandHandlerTimerID[0]), m_nCommandHandlerTimerID[0] = 0; nClient[0] < nClients[0]; nClient[0]++)
			{
				if (m_szCommandHandlerClients[0].GetAt(nClient[0]).GetLength() > 0 && (m_nCommandHandlerAccessCodes.GetAt(nClient[0]) & TCSERVICE_COMMANDINTERFACE_LIMITEDACCESS))
				{
					if ((pSocket = (m_tCommandHandlerStopTimes.GetAt(nClient[0]) <= tTime[1]) ? m_pClientSockets.GetAt(nClient[0]) : (CTCProcessInterfaceSocket *)NULL))
					{
						if (pSocket->IsConnected())
						{
							pSocket->Close();
							continue;
						}
					}
					if (m_tCommandHandlerStopTimes.GetAt(nClient[0]) > tTime[1])
					{
						tTime[0] = max(m_tCommandHandlerStopTimes.GetAt(nClient[0]), tTime[0]);
						continue;
					}
				}
			}
			for (nClient[0] = 0, nClients[0] = (INT)m_pClientSockets.GetSize(); nClient[0] < nClients[0]; nClient[0]++)
			{
				if ((pSocket = m_pClientSockets.GetAt(nClient[0])) != (CTCProcessInterfaceSocket *)NULL  &&  pSocket->IsConnected(szClient))
				{
					for (nClient[1] = 0, nClients[1] = (INT)m_szCommandHandlerClients[0].GetSize(); nClient[1] < nClients[1]; nClient[1]++)
					{
						if (!m_szCommandHandlerClients[0].GetAt(nClient[1]).CompareNoCase(szClient))
						{
							if (m_nCommandHandlerAccessCodes.GetAt(nClient[1]) & TCSERVICE_COMMANDINTERFACE_NOACCESS)
							{
								pSocket->Close();
								break;
							}
							if ((m_nCommandHandlerAccessCodes.GetAt(nClient[1]) & TCSERVICE_COMMANDINTERFACE_LIMITEDACCESS) && tTime[1] >= m_tCommandHandlerStopTimes.GetAt(nClient[1]))
							{
								pSocket->Close();
								break;
							}
						}
					}
					if (nClient[1] == nClients[1] && (!nClients[1] || m_szCommandHandlerClients[0].GetAt(nClients[1] - 1).GetLength() > 0))
					{
						pSocket->Close();
						continue;
					}
				}
			}
			m_nCommandHandlerTimerID[0] = (tTime[0] > 0) ? SetTimer((HWND)NULL, TCPROCESSINTERFACETHREAD_UPDATECLIENTS_TIMERID, (DWORD)(1000 * min(tTime[0].GetTime() - tTime[1].GetTime(), SECONDSPERDAY)), NULL) : 0;
			Unlock();
			return TRUE;
		}
		if (pMsg->wParam == m_nCommandHandlerTimerID[1])
		{
			for (KillTimer((HWND)NULL, m_nCommandHandlerTimerID[1]), m_nCommandHandlerTimerID[1] = 0; m_bCommandHandler[2]; )
			{
				for (nClient[0] = 0, nClients[0] = (GetCommandHandlerContents(pItems[0], pInterlocks[0], pQueues)) ? (INT)m_pClientSockets.GetSize() : -1, nCount = 0; nClient[0] < nClients[0]; nClient[0]++)
				{
					if ((pSocket = m_pClientSockets.GetAt(nClient[0])) && pSocket->IsConnected(szClient) && (pSocket->GetFlags() & (TCSERVICE_COMMANDINTERFACE_TELECOMMANDSUPDATE | TCSERVICE_COMMANDINTERFACE_INTERLOCKSUPDATE)))
					{
						if ((pSocket->GetFlags() & TCSERVICE_COMMANDINTERFACE_HOTLINKUPDATE) != TCSERVICE_COMMANDINTERFACE_HOTLINKUPDATE)
						{
							if (pSocket->GetFlags() & TCSERVICE_COMMANDINTERFACE_TELECOMMANDSUPDATE)
							{
								for (nItem = 0, nItems = (INT)pItems[0].GetSize(), pItems[1].RemoveAll(); nItem < nItems; nItem++)
								{
									if ((pItem[0] = pItems[0].GetAt(nItem)))
									{
										if ((pItem[1] = new CTCItem))
										{
											if (!pItem[0]->GetComputerName().CompareNoCase(szClient) || pItem[0]->GetStatus() >= TCITEM_STATUS_RELEASED)
											{
												if (pItem[1]->Copy(pItem[0]) && pItems[1].Add(pItem[1]) >= 0) continue;
												delete pItem[1];
												break;
											}
											delete pItem[1];
											continue;
										}
										break;
									}
								}
								if (nItem != nItems) break;
							}
							if (pSocket->GetFlags() & TCSERVICE_COMMANDINTERFACE_INTERLOCKSUPDATE)
							{
								for (nInterlock = 0, nInterlocks = (INT)pInterlocks[0].GetSize(), pInterlocks[1].RemoveAll(); nInterlock < nInterlocks; nInterlock++)
								{
									if ((pInterlock[0] = pInterlocks[0].GetAt(nInterlock)) && (TCINTERLOCKSCOPEFROMCODE(pInterlock[0]->GetScope()) == TCINTERLOCK_SCOPE_GLOBAL || !pInterlock[0]->GetComputerName().CompareNoCase(szClient)))
									{
										if ((pInterlock[1] = new CTCInterlock))
										{
											pInterlock[1]->Copy(pInterlock[0]);
											if (pInterlocks[1].Add(pInterlock[1]) >= 0) continue;
											delete pInterlock[1];
										}
										break;
									}
								}
								if (nItem != nItems) break;
							}
						}
						if (((pSocket->GetFlags() & TCSERVICE_COMMANDINTERFACE_TELECOMMANDSUPDATE) != TCSERVICE_COMMANDINTERFACE_TELECOMMANDSUPDATE || cUpdateCommandSourcesContentsRequestMessage.SetTelecommands((pSocket->GetFlags() & TCSERVICE_COMMANDINTERFACE_HOTLINKUPDATE) ? pItems[0] : pItems[1])) && ((pSocket->GetFlags() & TCSERVICE_COMMANDINTERFACE_INTERLOCKSUPDATE) != TCSERVICE_COMMANDINTERFACE_INTERLOCKSUPDATE || cUpdateCommandSourcesContentsRequestMessage.SetTCInterlocks((pSocket->GetFlags() & TCSERVICE_COMMANDINTERFACE_HOTLINKUPDATE) ? pInterlocks[0] : pInterlocks[1])) && cUpdateCommandSourcesContentsRequestMessage.EnableAcknowledgment() && cUpdateCommandSourcesContentsRequestMessage.Map(nMessageData) && pSocket->SendAndReceive(nMessageData, m_tCommandHandlerTimeout) > 0)
						{
							if (cUpdateCommandSourcesContentsResponseMessage.Unmap(nMessageData) && cUpdateCommandSourcesContentsResponseMessage.GetResult())
							{
								pSocket->SetFlags(pSocket->GetFlags() & ~(TCSERVICE_COMMANDINTERFACE_TELECOMMANDSUPDATE | TCSERVICE_COMMANDINTERFACE_INTERLOCKSUPDATE));
								cUpdateCommandSourcesContentsRequestMessage.Reset();
								continue;
							}
						}
						cUpdateCommandSourcesContentsRequestMessage.Reset();
						nCount++;
					}
				}
				m_nCommandHandlerTimerID[1] = (nClient[0] < nClients[0] || nCount > 0) ? SetTimer((HWND)NULL, TCPROCESSINTERFACETHREAD_UPDATECOMMANDS_TIMERID, TCPROCESSINTERFACETHREAD_UPDATECOMMANDS_TIMEOUT, NULL) : 0;
				return TRUE;
			}
			if (m_cSocket.IsConnected())
			{
				if (m_cSocket.GetFlags() & TCSERVICE_COMMANDINTERFACE_INTERLOCKSUPDATE)
				{
					if (m_pTCProcessThread->GetTCInterlocks(pInterlocks[0]) && cUpdateCommandSourcesContentsRequestMessage.SetTCInterlocks(pInterlocks[0]) && cUpdateCommandSourcesContentsRequestMessage.EnableAcknowledgment() && cUpdateCommandSourcesContentsRequestMessage.Map(nMessageData) && m_cSocket.SendAndReceive(nMessageData, m_tCommandHandlerTimeout) > 0)
					{
						if (cUpdateCommandSourcesContentsResponseMessage.Unmap(nMessageData) && cUpdateCommandSourcesContentsResponseMessage.GetResult())
						{
							m_cSocket.SetFlags(m_cSocket.GetFlags() & ~TCSERVICE_COMMANDINTERFACE_INTERLOCKSUPDATE);
							return TRUE;
						}
					}
					m_nCommandHandlerTimerID[1] = SetTimer((HWND)NULL, TCPROCESSINTERFACETHREAD_UPDATECOMMANDS_TIMERID, TCPROCESSINTERFACETHREAD_UPDATECOMMANDS_TIMEOUT, NULL);
				}
			}
			return TRUE;
		}
	}
	return CThread::PreTranslateMessage(pMsg);
}

BOOL CTCProcessInterfaceThread::Lock()
{
	return((m_pTCProcessThread) ? (m_pTCProcessThread->Lock() && CThread::Lock()) : CThread::Lock());
}

BOOL CTCProcessInterfaceThread::Unlock()
{
	return((m_pTCProcessThread) ? (CThread::Unlock() && m_pTCProcessThread->Unlock()) : CThread::Unlock());
}

BEGIN_MESSAGE_MAP(CTCProcessInterfaceThread, CThread)
	//{{AFX_MSG_MAP(CTCProcessInterfaceThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcessInterfaceThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CTCProcessReleaseThread

IMPLEMENT_DYNAMIC(CTCProcessReleaseThread, CThread)

CTCProcessReleaseThread::CTCProcessReleaseThread(CTCProcessThread *pThread) : CThread()
{
	m_nState = TCSERVICE_COMMANDHANDLERSTATE_NONE;
	m_pTCProcessThread = pThread;
}

BOOL CTCProcessReleaseThread::Start()
{
	return CreateThread((LPVOID)NULL, THREAD_PRIORITY_ABOVE_NORMAL);
}

BOOL CTCProcessReleaseThread::Stop()
{
	return((DestroyThread() >= 0) ? TRUE : FALSE);
}

BOOL CTCProcessReleaseThread::InitInstance()
{
	return((AfxSocketInit()) ? m_cSocket.Create() : FALSE);
}

int CTCProcessReleaseThread::ExitInstance()
{
	m_cSocket.Close();
	return CThread::ExitInstance();
}

BOOL CTCProcessReleaseThread::SetState(UINT nState)
{
	CTCChainLock  cLock(this);

	if (m_nState != nState)
	{
		m_nState = nState;
		Update();
	}
	return TRUE;
}

UINT CTCProcessReleaseThread::GetState() CONST
{
	CTCChainLock  cLock(this);

	return m_nState;
}

BOOL CTCProcessReleaseThread::Update(CONST CTCProcessEngine *pTCProcessEngine, CONST CTCEnvironment *pTCEnvironment, CONST CTMEnvironment *pTMEnvironment, CONST CTCItems &pItems, CONST CTCInterlocks &pInterlocks, BOOL bRemove)
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	INT  nCount;
	BOOL  bUpdate;
	BOOL  bSuccess;
	BOOL  bAfterDispatch;
	DWORD  dwReleaseOffset;
	CTCItem  *pItem[4];
	CString  szInterlock[2];
	CTimeTag  tReleaseTime[2];
	CTimeSpan  tReleaseInterval;
	CTCInterlock  *pInterlock[2];
	CTCChainLock  cLock(this);

	for (nItem = 0, nItems = (!bRemove) ? (INT)pItems.GetSize() : 0, bUpdate = TRUE; nItem < nItems; nItem++)
	{
		if ((pItem[0] = pItems.GetAt(nItem)) && pItem[0]->GetStatus() == TCITEM_STATUS_DISPATCHED)
		{
			if ((pItem[1] = m_pItems.GetAt((nIndex = m_pItems.Find(pItem[0])))))
			{
				m_pItems.RemoveAt(nIndex);
				delete pItem[1];
			}
			for (nIndex = 0, nCount = (INT)m_pItems.GetSize(); nIndex < nCount; nIndex++)
			{
				if ((pItem[1] = m_pItems.GetAt(nIndex)) && pItem[0]->GetReleaseTime() < pItem[1]->GetReleaseTime()) break;
				continue;
			}
			if ((pItem[1] = new CTCItem))
			{
				if (pItem[1]->Copy(pItem[0]))
				{
					for (CheckPreTransmissionValidationCondition(pItem[1]), CheckPreExecutionVerificationCondition(pTCProcessEngine, pTMEnvironment, pItem[1]), m_pItems.InsertAt(nIndex, pItem[1], 1); (pItem[2] = pItems.GetAt(nItem + 1)); nItem++, nIndex++)
					{
						if (((pItem[2]->GetFlags() & TCITEM_LINKAGEFLAG_BLOCKED) && pItem[2]->GetReleaseBlockID() > 0) || (pItem[2]->GetFlags() & TCITEM_LINKAGEFLAG_GROUPED))
						{
							if (pItem[1]->GetReleaseTime() == pItem[2]->GetReleaseTime())
							{
								if ((pItem[1] = new CTCItem))
								{
									if (pItem[1]->Copy(pItem[2]))
									{
										CheckPreTransmissionValidationCondition(pItem[1]);
										CheckPreExecutionVerificationCondition(pTCProcessEngine, pTMEnvironment, pItem[1]);
										m_pItems.InsertAt(nIndex + 1, pItem[1], 1);
										continue;
									}
									delete pItem[1];
								}
								bUpdate = FALSE;
								break;
							}
							if ((pItem[3] = m_pItems.GetAt(nIndex + 1)))
							{
								if ((pItem[2]->GetReleaseTime() > pItem[3]->GetReleaseTime() && ((pItem[3]->GetReleaseTimeWindow(tReleaseTime[0], tReleaseInterval) && tReleaseInterval > 0 && pItem[2]->GetReleaseTime() <= tReleaseTime[0].GetTime() + 1000000 * tReleaseInterval.GetTotalSeconds()) || (pItem[3]->GetReleaseTimeWindow(tReleaseTime[0], tReleaseTime[1]) && (pItem[2]->GetReleaseTime() <= tReleaseTime[1] || tReleaseTime[1] == 0)) || (pItem[3]->GetReleaseTimeWindow(dwReleaseOffset, tReleaseInterval, bAfterDispatch) && (pItem[2]->GetReleaseTime() <= pItem[3]->GetReleaseTime() + 1000000 * tReleaseInterval.GetTotalSeconds() || tReleaseInterval == 0)))) || pItem[2]->GetReleaseTime() <= pItem[3]->GetReleaseTime())
								{
									if ((pItem[1] = new CTCItem))
									{
										if (pItem[1]->Copy(pItem[2]))
										{
											m_pItems.InsertAt(nIndex + 1, pItem[1], 1);
											continue;
										}
										delete pItem[1];
									}
								}
								bUpdate = FALSE;
								break;
							}
						}
						break;
					}
					continue;
				}
				delete pItem[1];
			}
		}
		bUpdate = FALSE;
		break;
	}
	for (nItem = 0, nItems = (!bRemove && bUpdate) ? (INT)pItems.GetSize() : 0; nItem < nItems; nItem++)
	{
		if ((pItem[0] = pItems.GetAt(nItem)) && pItem[0]->GetStatus() == TCITEM_STATUS_DISPATCHED)
		{
			if ((pItem[1] = m_pItems.GetAt(m_pItems.Find(pItem[0]))) != (CTCItem *)NULL)
			{
				if ((pInterlock[0] = pInterlocks.GetAt(pInterlocks.Find(pItem[1]->GetComputerName(), pItem[1]->GetSourceType(), (szInterlock[0] = pItem[1]->GetInterlock())))))
				{
					pItem[1]->SetInterlock(pInterlock[0]);
					szInterlock[0].Empty();
				}
				if ((pInterlock[1] = (pItem[1]->GetReleaseInterlock(szInterlock[1], bSuccess)) ? pInterlocks.GetAt(pInterlocks.Find(pItem[1]->GetComputerName(), pItem[1]->GetSourceType(), szInterlock[1])) : (CTCInterlock *)NULL))
				{
					pItem[1]->SetReleaseInterlock(pInterlock[1]);
					szInterlock[1].Empty();
				}
				if (!szInterlock[0].IsEmpty()) pItem[1]->SetInterlock(EMPTYSTRING);
				if (!szInterlock[1].IsEmpty()) pItem[1]->SetReleaseInterlock(EMPTYSTRING);
				continue;
			}
		}
		bUpdate = FALSE;
		break;
	}
	for (nItem = 0, nItems = (bRemove || !bUpdate) ? (INT)pItems.GetSize() : 0; nItem < nItems; nItem++)
	{
		if ((pItem[1] = ((pItem[0] = pItems.GetAt(nItem))) ? m_pItems.GetAt((nIndex = m_pItems.Find(pItem[0]))) : (CTCItem *)NULL))
		{
			m_pItems.RemoveAt(nIndex);
			delete pItem[1];
			continue;
		}
		bUpdate = FALSE;
	}
	Update();
	return bUpdate;
}
BOOL CTCProcessReleaseThread::Update(CONST CTCProcessEngine *pTCProcessEngine, CONST CTCEnvironment *pTCEnvironment, CONST CTMEnvironment *pTMEnvironment, CONST CTCInterlocks &pTCInterlocks, CTCItems &pItems)
{
	INT  nItem;
	INT  nItems;
	INT  nCount;
	CTCItem  *pItem[2];
	CTCChainLock  cLock(this);

	for (nItem = 0, nItems = (INT)m_pItems.GetSize(), pItems.Copy(&m_pItems); nItem < nItems; nItem++)
	{
		if ((pItem[0] = m_pItems.GetAt(nItem)))
		{
			CheckPreTransmissionValidationCondition(pItem[0]);
			CheckPreExecutionVerificationCondition(pTCProcessEngine, pTMEnvironment, pItem[0]);
		}
	}
	for (nItem = 0, nCount = 0; nItem < nItems; nItem++)
	{
		if ((pItem[1] = ((pItem[0] = m_pItems.GetAt(nItem))) ? pItems.GetAt(nItem - nCount) : (CTCItem *)NULL))
		{
			if (pItem[0]->GetResult() == pItem[1]->GetResult())
			{
				pItems.RemoveAt(nItem - nCount);
				delete pItem[1];
				nCount++;
				continue;
			}
			pItem[1]->SetResult(pItem[0]->GetResult());
		}
	}
	Update();
	return TRUE;
}
BOOL CTCProcessReleaseThread::Update(CONST CTCProcessEngine *pTCProcessEngine, CONST CTCEnvironment *pTCEnvironment, CONST CTMEnvironment *pTMEnvironment, CONST CTCInterlocks &pTCInterlocks)
{
	CTCItems  pItems;

	return Update(pTCProcessEngine, pTCEnvironment, pTMEnvironment, pTCInterlocks, pItems);
}
BOOL CTCProcessReleaseThread::Update(CONST CTCItems &pReleaseItems, CONST CTCInterlocks &pInterlocks, CTCItems &pItems)
{
	INT  nItem;
	INT  nItems;
	INT  nCount;
	INT  nInterlock;
	INT  nInterlocks;
	BOOL  bInterlock;
	CTCItem  *pItem[2];
	CString  szInterlock;
	CTCInterlock  *pInterlock;
	CDatabaseTCPacket  cPacket;
	CTCChainLock  cLock(this);

	for (nItem = 0, nItems = (INT)pReleaseItems.GetSize(); nItem < nItems; nItem++)
	{
		if ((pItem[1] = ((pItem[0] = pReleaseItems.GetAt(nItem))) ? m_pItems.GetAt(m_pItems.Find(pItem[0])) : (CTCItem *)NULL))
		{
			pItem[1]->Copy(pItem[0]);
			continue;
		}
	}
	for (nItem = 0, nItems = (INT)m_pItems.GetSize(), pItems.Copy(&m_pItems); nItem < nItems; nItem++)
	{
		if ((pItem[0] = m_pItems.GetAt(nItem)) && (pItem[0]->GetResult() & TCITEM_RESULT_PTV_FAIL) != TCITEM_RESULT_PTV_FAIL  &&  pReleaseItems.Find(pItem[0]) < 0)
		{
			for (nInterlock = 0, nInterlocks = (INT)pInterlocks.GetSize(); nInterlock < nInterlocks; nInterlock++)
			{
				if ((pInterlock = pInterlocks.GetAt(nInterlock)) != (CTCInterlock *)NULL)
				{
					if (TCINTERLOCKSCOPEFROMCODE(pInterlock->GetScope()) == TCINTERLOCK_SCOPE_GLOBAL)
					{
						if (pInterlock->GetState() != TCINTERLOCK_STATE_SUCCESS)
						{
							pItem[0]->SetResult((pItem[0]->GetResult() & ~TCITEM_RESULT_PTV_GO) | TCITEM_RESULT_PTV_WAIT | TCITEM_FAILURE_PTV_INTERLOCK);
							break;
						}
						continue;
					}
					if (TCINTERLOCKSCOPEFROMCODE(pInterlock->GetScope()) == TCINTERLOCK_SCOPE_LOCAL)
					{
						if (pInterlock->GetState() != TCINTERLOCK_STATE_SUCCESS  &&  !pItem[0]->GetComputerName().CompareNoCase(pInterlock->GetComputerName()) && pItem[0]->GetSourceType() == pInterlock->GetSourceType())
						{
							pItem[0]->SetResult((pItem[0]->GetResult() & ~TCITEM_RESULT_PTV_GO) | TCITEM_RESULT_PTV_WAIT | TCITEM_FAILURE_PTV_INTERLOCK);
							break;
						}
						continue;
					}
					if (TCINTERLOCKSCOPEFROMCODE(pInterlock->GetScope()) == TCINTERLOCK_SCOPE_LOCALSUBSYSTEM)
					{
						if (pInterlock->GetState() != TCINTERLOCK_STATE_SUCCESS  &&  pItem[0]->GetTCPacket(&cPacket) && cPacket.GetAPID() == TCINTERLOCKAPIDFROMCODE(pInterlock->GetScope()))
						{
							pItem[0]->SetResult((pItem[0]->GetResult() & ~TCITEM_RESULT_PTV_GO) | TCITEM_RESULT_PTV_WAIT | TCITEM_FAILURE_PTV_INTERLOCK);
							break;
						}
						continue;
					}
				}
			}
			if ((pInterlock = (pItem[0]->GetReleaseInterlock(szInterlock, bInterlock)) ? pInterlocks.GetAt(pInterlocks.Find(pItem[0]->GetComputerName(), pItem[0]->GetSourceType(), szInterlock)) : (CTCInterlock *)NULL))
			{
				if ((bInterlock  &&  pInterlock->GetState() == TCINTERLOCK_STATE_SUCCESS) || (!bInterlock  &&  pInterlock->GetState() == TCINTERLOCK_STATE_FAILURE))
				{
					if ((pItem[0]->GetResult() & (TCITEM_RESULT_PTV_WAIT | TCITEM_FAILURE_PTV_INTERLOCK)) == (TCITEM_RESULT_PTV_WAIT | TCITEM_FAILURE_PTV_INTERLOCK) && nInterlock == nInterlocks)
					{
						for (pItem[0]->SetResult(pItem[0]->GetResult() & ~TCITEM_FAILURE_PTV_INTERLOCK); (pItem[0]->GetResult() & (TCITEM_FAILURE_PTV_UPLINK | TCITEM_FAILURE_PTV_RELEASETIMEWINDOW | TCITEM_FAILURE_PTV_EXECUTIONTIME | TCITEM_FAILURE_PTV_INTERLOCK)) == 0; )
						{
							pItem[0]->SetResult((pItem[0]->GetResult() & ~TCITEM_RESULT_PTV_WAIT) | TCITEM_RESULT_PTV_GO);
							break;
						}
					}
				}
				pItem[0]->SetReleaseInterlock(pInterlock);
				pItem[0]->SetResult((pItem[0]->GetResult() & ~TCITEM_RESULT_PTV_GO) | TCITEM_RESULT_PTV_WAIT | TCITEM_FAILURE_PTV_INTERLOCK);
				continue;
			}
			if (nInterlock == nInterlocks)
			{
				for (pItem[0]->SetResult(pItem[0]->GetResult() & ~TCITEM_FAILURE_PTV_INTERLOCK); (pItem[0]->GetResult() & (TCITEM_FAILURE_PTV_UPLINK | TCITEM_FAILURE_PTV_RELEASETIMEWINDOW | TCITEM_FAILURE_PTV_EXECUTIONTIME | TCITEM_FAILURE_PTV_INTERLOCK)) == 0; )
				{
					pItem[0]->SetResult((pItem[0]->GetResult() & ~TCITEM_RESULT_PTV_WAIT) | TCITEM_RESULT_PTV_GO);
					break;
				}
			}
		}
	}
	for (nItem = 0, nCount = 0; nItem < nItems; nItem++)
	{
		if ((pItem[1] = ((pItem[0] = m_pItems.GetAt(nItem))) ? pItems.GetAt(nItem - nCount) : (CTCItem *)NULL))
		{
			if (pItem[0]->GetResult() == pItem[1]->GetResult())
			{
				pItems.RemoveAt(nItem - nCount);
				delete pItem[1];
				nCount++;
				continue;
			}
			pItem[1]->SetResult(pItem[0]->GetResult());
		}
	}
	Update();
	return TRUE;
}
BOOL CTCProcessReleaseThread::Update(CONST CTCInterlocks &pInterlocks, CTCItems &pItems)
{
	CTCItems  pReleaseItems;

	return Update(pReleaseItems, pInterlocks, pItems);
}
BOOL CTCProcessReleaseThread::Update(CONST CTCInterlocks &pInterlocks)
{
	CTCItems  pItems;

	return Update(pInterlocks, pItems);
}
BOOL CTCProcessReleaseThread::Update(UINT nState, CTCItems &pItems)
{
	INT  nItem;
	INT  nItems;
	INT  nCount;
	CTCItem  *pItem[2];
	CTCChainLock  cLock(this);

	for (nItem = 0, nItems = (INT)m_pItems.GetSize(), pItems.Copy(&m_pItems); nItem < nItems; nItem++)
	{
		if ((pItem[0] = m_pItems.GetAt(nItem)) && (pItem[0]->GetResult() & TCITEM_RESULT_PTV_FAIL) != TCITEM_RESULT_PTV_FAIL)
		{
			if ((nState & (TCSERVICE_COMMANDHANDLERSTATE_LINK_GOOD | TCSERVICE_COMMANDHANDLERSTATE_FRONTENDLINK_GOOD | TCSERVICE_COMMANDHANDLERSTATE_FRONTEND_OK)) == (TCSERVICE_COMMANDHANDLERSTATE_LINK_GOOD | TCSERVICE_COMMANDHANDLERSTATE_FRONTENDLINK_GOOD | TCSERVICE_COMMANDHANDLERSTATE_FRONTEND_OK))
			{
				if ((pItem[0]->GetResult() & TCITEM_FAILURE_PTV_UPLINK) == TCITEM_FAILURE_PTV_UPLINK)
				{
					for (pItem[0]->SetResult(pItem[0]->GetResult() & ~TCITEM_FAILURE_PTV_UPLINK); (pItem[0]->GetResult() & (TCITEM_FAILURE_PTV_UPLINK | TCITEM_FAILURE_PTV_RELEASETIMEWINDOW | TCITEM_FAILURE_PTV_EXECUTIONTIME | TCITEM_FAILURE_PTV_INTERLOCK | TCITEM_FAILURE_PTV_SUBSYSTEM | TCITEM_FAILURE_PTV_ONBOARDBUFFER)) == 0; )
					{
						pItem[0]->SetResult((pItem[0]->GetResult() & ~TCITEM_RESULT_PTV_WAIT) | TCITEM_RESULT_PTV_GO);
						break;
					}
				}
				continue;
			}
			pItem[0]->SetResult((pItem[0]->GetResult() & ~TCITEM_RESULT_PTV_GO) | TCITEM_RESULT_PTV_WAIT | TCITEM_FAILURE_PTV_UPLINK);
		}
	}
	for (nItem = 0, nCount = 0; nItem < nItems; nItem++)
	{
		if ((pItem[1] = ((pItem[0] = m_pItems.GetAt(nItem))) ? pItems.GetAt(nItem - nCount) : (CTCItem *)NULL))
		{
			if (pItem[0]->GetResult() == pItem[1]->GetResult())
			{
				pItems.RemoveAt(nItem - nCount);
				delete pItem[1];
				nCount++;
				continue;
			}
			pItem[1]->SetResult(pItem[0]->GetResult());
		}
	}
	Update();
	return TRUE;
}
BOOL CTCProcessReleaseThread::Update(UINT nState)
{
	CTCItems  pItems;

	return Update(nState, pItems);
}
BOOL CTCProcessReleaseThread::Update()
{
	return m_bUpdate.SetEvent();
}

BOOL CTCProcessReleaseThread::Reset()
{
	CTCChainLock  cLock(this);

	m_pItems.RemoveAll();
	return Update();
}

BOOL CTCProcessReleaseThread::IsEmpty() CONST
{
	CTCChainLock  cLock(this);

	return((!m_pItems.GetSize()) ? TRUE : FALSE);
}

BOOL CTCProcessReleaseThread::SetContents(CONST CTCItems &pItems)
{
	CTCChainLock  cLock(this);

	if (m_pItems.Copy(&pItems))
	{
		Update();
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcessReleaseThread::GetContents(CTCItems &pItems) CONST
{
	CTCChainLock  cLock(this);

	return pItems.Copy(&m_pItems);
}

VOID CTCProcessReleaseThread::CheckPreTransmissionValidationCondition(CTCItem *pItem) CONST
{
	BOOL  bForced;
	BOOL  bCheck[10];
	BOOL  bAfterDispatch;
	BOOL  bEarlierExecution;
	UINT  nExecutionOBRT;
	DWORD  dwReleaseOffset;
	DWORD  dwExecutionOffset;
	CTimeTag  tExecutionTime;
	CTimeTag  tReleaseTime[3];
	CTimeSpan  tReleaseInterval;
	CTimeSpan  tExecutionOffset[2];
	CTCUplinkDevice  cDevice;

	for (bForced = ((m_pTCProcessThread->GetCommandSourceTelecommandingChecks(pItem->GetComputerName(), pItem->GetSourceType()) & (TCSERVICE_COMMANDSOURCEFLAGS_PTV_OVERRIDE | TCSERVICE_COMMANDSOURCEFLAGS_PTV_DISABLE)) || (pItem->GetFlags() & (TCITEM_CHECKFLAG_OVERRIDEPTV | TCITEM_CHECKFLAG_DISABLEPTV))) ? TRUE : FALSE, bCheck[0] = /*(GetTCService() -> GetActiveTCUplinkDevice(&cDevice) && (cDevice.GetStatusIndication() & (TCSERVICE_COMMANDHANDLERSTATE_FRONTENDLINK_GOOD | TCSERVICE_COMMANDHANDLERSTATE_FRONTEND_OK)) == (TCSERVICE_COMMANDHANDLERSTATE_FRONTENDLINK_GOOD | TCSERVICE_COMMANDHANDLERSTATE_FRONTEND_OK) && (cDevice.GetCommandHandlerState() & TCSERVICE_COMMANDHANDLERSTATE_LINK_GOOD)) ? TRUE:FALSE*/ TRUE, bCheck[1] = ((pItem->GetReleaseTimeWindow(tReleaseTime[0], tReleaseInterval) && pItem->GetReleaseTime() <= tReleaseTime[2] && tReleaseInterval > 0 && (pItem->GetReleaseTime().GetTime() + 1000000 * tReleaseInterval.GetTotalSeconds() >= tReleaseTime[2].GetTime() || (tReleaseTime[0] == 0 && !pItem->GetReleaseTimeWindow(dwReleaseOffset, tReleaseInterval, bAfterDispatch)))) || (pItem->GetReleaseTimeWindow(tReleaseTime[0], tReleaseTime[1]) && pItem->GetReleaseTime() <= tReleaseTime[2] && tReleaseTime[0] <= tReleaseTime[1] && tReleaseTime[1] >= tReleaseTime[2]) || (pItem->GetReleaseTimeWindow(dwReleaseOffset, tReleaseInterval, bAfterDispatch) && pItem->GetReleaseTime() <= tReleaseTime[2] && (pItem->GetReleaseTime().GetTime() + 1000000 * tReleaseInterval.GetTotalSeconds() >= tReleaseTime[2].GetTime() || tReleaseInterval == 0 || bAfterDispatch)) || (pItem->GetReleaseTimeWindow(tReleaseTime[0], tReleaseInterval) && pItem->GetReleaseTimeWindow(tReleaseTime[0], tReleaseTime[1]) && tReleaseInterval == 0 && tReleaseTime[1] == 0 && tReleaseTime[0] <= tReleaseTime[2]) || (!pItem->GetReleaseTimeWindow(tReleaseTime[0], tReleaseInterval) && !pItem->GetReleaseTimeWindow(tReleaseTime[0], tReleaseTime[1]) && !pItem->GetReleaseTimeWindow(dwReleaseOffset, tReleaseInterval, bAfterDispatch))) ? TRUE : FALSE, bCheck[2] = (((!pItem->GetExecutionTime(tExecutionTime) && !pItem->GetExecutionTimeOffset(dwExecutionOffset, bEarlierExecution)) || (m_pTCProcessThread->GetTCFunctionExecutionTimeOffsets(tExecutionOffset[0], tExecutionOffset[1]) && ((pItem->GetExecutionTime(tExecutionTime) && tExecutionTime >= tReleaseTime[2].GetTime() + 1000000 * tExecutionOffset[0].GetTotalSeconds() && tExecutionTime <= tReleaseTime[2].GetTime() + 1000000 * tExecutionOffset[1].GetTotalSeconds()) || pItem->GetExecutionTimeOffset(dwExecutionOffset, bEarlierExecution)) && GetTMService()->CheckTMStreamCorrelation())) && (!pItem->GetExecutionOBRT(nExecutionOBRT) || (m_pTCProcessThread->GetTCFunctionExecutionTimeOffsets(tExecutionOffset[0], tExecutionOffset[1]) && m_pTCProcessThread->ConvertOBRTToTime(nExecutionOBRT, tExecutionTime) && tExecutionTime >= tReleaseTime[2].GetTime() + 1000000 * tExecutionOffset[0].GetTotalSeconds() && tExecutionTime <= tReleaseTime[2].GetTime() + 1000000 * tExecutionOffset[1].GetTotalSeconds()))) ? TRUE : FALSE, bCheck[3] = (m_pTCProcessThread->CheckTCInterlock(pItem) || !m_pTCProcessThread->IsCommandSourceTelecommandingInterlockModeEnabled(pItem->GetComputerName(), pItem->GetSourceType()) || bForced) ? TRUE : FALSE, bCheck[4] = (m_pTCProcessThread->IsCommandSourceSubSystemEnabled(pItem->GetComputerName(), pItem->GetSourceType(), pItem) || bForced) ? TRUE : FALSE, bCheck[5] = ((pItem->GetResult() & TCITEM_FAILURE_PTV_ONBOARDBUFFER) != TCITEM_FAILURE_PTV_ONBOARDBUFFER || bForced) ? TRUE : FALSE, bCheck[6] = (m_pTCProcessThread->IsCommandSourceTelecommandingReleaseWaitModeEnabled(pItem->GetComputerName(), pItem->GetSourceType()) || !bCheck[5]) ? TRUE : FALSE, bCheck[7] = (abs((INT)(tReleaseTime[2].GetTimeInSeconds() - pItem->GetReleaseTime().GetTimeInSeconds())) <= 1 || pItem->GetReleaseTime() == 0) ? TRUE : FALSE, bCheck[8] = (m_pTCProcessThread->GetCommandSourceTelecommandingState(pItem->GetComputerName(), pItem->GetSourceType()) & TCSERVICE_COMMANDSOURCESTATE_DEFAULT) ? TRUE : FALSE; (bCheck[9] = bCheck[0] && (bCheck[1] && (bCheck[6] || bCheck[7])) && bCheck[2] && bCheck[3] && bCheck[4] && bCheck[5] && bCheck[8]); )
	{
		pItem->SetResult((pItem->GetResult() & ~(TCITEM_RESULT_PTV_WAIT | TCITEM_FAILURE_PTV_UPLINK | TCITEM_FAILURE_PTV_RELEASETIMEWINDOW | TCITEM_FAILURE_PTV_EXECUTIONTIME | TCITEM_FAILURE_PTV_INTERLOCK | TCITEM_FAILURE_PTV_SUBSYSTEM | TCITEM_FAILURE_PTV_ONBOARDBUFFER)) | TCITEM_RESULT_PTV_GO);
		break;
	}
	if (!bCheck[9])
	{
		pItem->SetResult((((!bCheck[1] || (!bCheck[6] && !bCheck[7])) && (!pItem->GetReleaseTimeWindow(dwReleaseOffset, tReleaseInterval, bAfterDispatch) || pItem->GetReleaseTime().GetTime() > 0 || bAfterDispatch) && pItem->GetReleaseTime() < tReleaseTime[2]) || !bCheck[2]) ? ((pItem->GetResult() & ~(TCITEM_RESULT_PTV_GO | TCITEM_RESULT_PTV_WAIT)) | TCITEM_RESULT_PTV_FAIL) : ((pItem->GetResult() & ~(TCITEM_RESULT_PTV_GO | TCITEM_RESULT_PTV_FAIL)) | TCITEM_RESULT_PTV_WAIT));
		pItem->SetResult((!bCheck[0]) ? (pItem->GetResult() | TCITEM_FAILURE_PTV_UPLINK) : (pItem->GetResult() & ~TCITEM_FAILURE_PTV_UPLINK));
		pItem->SetResult((!bCheck[1]) ? (pItem->GetResult() | TCITEM_FAILURE_PTV_RELEASETIMEWINDOW) : (pItem->GetResult() & ~TCITEM_FAILURE_PTV_RELEASETIMEWINDOW));
		pItem->SetResult((!bCheck[2]) ? (pItem->GetResult() | TCITEM_FAILURE_PTV_EXECUTIONTIME) : (pItem->GetResult() & ~TCITEM_FAILURE_PTV_EXECUTIONTIME));
		pItem->SetResult((!bCheck[3]) ? (pItem->GetResult() | TCITEM_FAILURE_PTV_INTERLOCK) : (pItem->GetResult() & ~TCITEM_FAILURE_PTV_INTERLOCK));
		pItem->SetResult((!bCheck[4]) ? (pItem->GetResult() | TCITEM_FAILURE_PTV_SUBSYSTEM) : (pItem->GetResult() & ~TCITEM_FAILURE_PTV_SUBSYSTEM));
	}
}

VOID CTCProcessReleaseThread::CheckPreExecutionVerificationCondition(CONST CTCProcessEngine *pTCProcessEngine, CONST CTMEnvironment *pTMEnvironment, CTCItem *pItem) CONST
{
	INT  nElement;
	INT  nElements;
	INT  nParameter;
	INT  nParameters;
	BOOL  bEarlierExecution;
	UINT  nExecutionOBRT;
	DWORD  dwExecutionOffset;
	CTimeTag  tExecutionTime;
	CStringArray  szParameters;
	CDatabaseTCPacket  cPacket;
	CDatabaseTCFunctionElement  *pFunctionElement;
	CDatabaseTCPacketParameter  *pPacketParameter;

	if (pItem->GetSourceType() == TCITEM_SOURCETYPE_MANUALSTACK || pItem->GetSourceType() == TCITEM_SOURCETYPE_AUTOMATICSTACK)
	{
		if ((pItem->GetFlags() & (TCITEM_CHECKFLAG_OVERRIDEPEV | TCITEM_CHECKFLAG_DISABLEPEV)) == 0 && (m_pTCProcessThread->GetCommandSourceTelecommandingChecks(pItem->GetComputerName(), pItem->GetSourceType()) & (TCSERVICE_COMMANDSOURCEFLAGS_PEV_OVERRIDE | TCSERVICE_COMMANDSOURCEFLAGS_PEV_DISABLE)) == 0)
		{
			for (pItem->SetResult(pItem->GetResult() & ~(TCITEM_FAILURE_PEV_TELEMETRY | TCITEM_FAILURE_PEV_CORRELATION | TCITEM_FAILURE_PEV_2NDSTEP | TCITEM_FAILURE_PEV_PARAMETERS)); (pItem->GetFlags() & TCITEM_EXECUTIONFLAG_2NDSTEP) && !m_pTCProcessThread->CheckTCOnBoardBufferQueue(pItem); )
			{
				pItem->SetResult(pItem->GetResult() | TCITEM_FAILURE_PEV_2NDSTEP);
				break;
			}
			if (pItem->GetPreExeGroupRef() >= 0 && !pItem->GetExecutionTime(tExecutionTime) && !pItem->GetExecutionOBRT(nExecutionOBRT))
			{
				if (!pTCProcessEngine->CheckTCFunctionPreexecutionParameterGroup(GetDatabase(), pTMEnvironment, pItem->GetPreExeGroupRef(), szParameters))
				{
					pItem->SetVerificationStageParameters(TCVERIFICATIONSTAGE_NONE, szParameters);
					pItem->SetResult(pItem->GetResult() | TCITEM_FAILURE_PEV_PARAMETERS);
				}
				if (GetTMService()->CheckTMStreamInterruption()) pItem->SetResult(pItem->GetResult() | TCITEM_FAILURE_PEV_TELEMETRY);
			}
			for (nElement = 0, nElements = ((!pItem->GetExecutionTime(tExecutionTime) || pItem->GetExecutionTimeOffset(dwExecutionOffset, bEarlierExecution)) && !pItem->GetExecutionOBRT(nExecutionOBRT)) ? (INT)pItem->GetSize() : -1; nElement < nElements; nElement++)
			{
				if ((pFunctionElement = pItem->GetAt(nElement)) && (pFunctionElement->GetAttributes() & TCPARAMETER_CODING_TIME)) break;
				continue;
			}
			for (nParameter = 0, nParameters = (nElement == nElements) ? ((pItem->GetTCPacket(&cPacket)) ? (INT)cPacket.GetSize() : 0) : -1; nParameter < nParameters; nParameter++)
			{
				if ((pPacketParameter = cPacket.GetAt(nParameter)) && (pPacketParameter->GetAttributes() & TCPARAMETER_CODING_TIME)) break;
				continue;
			}
			if ((nElement != nElements || nParameter != nParameters) && !GetTMService()->CheckTMStreamCorrelation()) pItem->SetResult(pItem->GetResult() | TCITEM_FAILURE_PEV_CORRELATION);
			if (pItem->GetResult() & (TCITEM_FAILURE_PEV_TELEMETRY | TCITEM_FAILURE_PEV_CORRELATION | TCITEM_FAILURE_PEV_2NDSTEP | TCITEM_FAILURE_PEV_PARAMETERS))
			{
				pItem->SetResult((pItem->GetResult() & ~TCITEM_RESULT_PEV_GO) | TCITEM_RESULT_PEV_NOGO);
				return;
			}
		}
		pItem->SetVerificationStageParameters(TCVERIFICATIONSTAGE_NONE, szParameters);
		pItem->SetResult((pItem->GetResult() & ~(TCITEM_RESULT_PEV_NOGO | TCITEM_FAILURE_PEV_TELEMETRY | TCITEM_FAILURE_PEV_CORRELATION | TCITEM_FAILURE_PEV_2NDSTEP | TCITEM_FAILURE_PEV_PARAMETERS)) | TCITEM_RESULT_PEV_GO);
		return;
	}
	if (pItem->GetSourceType() == TCITEM_SOURCETYPE_PROCEDURESMONITOR)
	{
		if ((pItem->GetFlags() & (TCITEM_CHECKFLAG_OVERRIDEPEV | TCITEM_CHECKFLAG_DISABLEPEV)) == 0 && (m_pTCProcessThread->GetCommandSourceTelecommandingChecks(pItem->GetComputerName(), pItem->GetSourceType()) & (TCSERVICE_COMMANDSOURCEFLAGS_PEV_OVERRIDE | TCSERVICE_COMMANDSOURCEFLAGS_PEV_DISABLE)) == 0)
		{
			for (pItem->SetResult(pItem->GetResult() & ~(TCITEM_FAILURE_PEV_TELEMETRY | TCITEM_FAILURE_PEV_CORRELATION | TCITEM_FAILURE_PEV_2NDSTEP | TCITEM_FAILURE_PEV_PARAMETERS)); (pItem->GetFlags() & TCITEM_EXECUTIONFLAG_2NDSTEP) && !m_pTCProcessThread->CheckTCOnBoardBufferQueue(pItem); )
			{
				pItem->SetResult(pItem->GetResult() | TCITEM_FAILURE_PEV_2NDSTEP);
				break;
			}
			if (pItem->GetPreExeGroupRef() >= 0 && !pItem->GetExecutionTime(tExecutionTime) && !pItem->GetExecutionOBRT(nExecutionOBRT))
			{
				if (!CheckPreExecutionVerificationCondition(pItem, szParameters))
				{
					pItem->SetVerificationStageParameters(TCVERIFICATIONSTAGE_NONE, szParameters);
					pItem->SetResult(pItem->GetResult() | TCITEM_FAILURE_PEV_PARAMETERS);
				}
				if (GetTMService()->CheckTMStreamInterruption()) pItem->SetResult(pItem->GetResult() | TCITEM_FAILURE_PEV_TELEMETRY);
			}
			for (nElement = 0, nElements = (!pItem->GetExecutionTime(tExecutionTime) && !pItem->GetExecutionOBRT(nExecutionOBRT)) ? (INT)pItem->GetSize() : -1; nElement < nElements; nElement++)
			{
				if ((pFunctionElement = pItem->GetAt(nElement)) && (pFunctionElement->GetAttributes() & TCPARAMETER_CODING_TIME)) break;
				continue;
			}
			for (nParameter = 0, nParameters = (nElement == nElements) ? ((pItem->GetTCPacket(&cPacket)) ? (INT)cPacket.GetSize() : 0) : -1; nParameter < nParameters; nParameter++)
			{
				if ((pPacketParameter = cPacket.GetAt(nParameter)) && (pPacketParameter->GetAttributes() & TCPARAMETER_CODING_TIME)) break;
				continue;
			}
			if ((nElement != nElements || nParameter != nParameters) && !GetTMService()->CheckTMStreamCorrelation()) pItem->SetResult(pItem->GetResult() | TCITEM_FAILURE_PEV_CORRELATION);
			if (pItem->GetResult() & (TCITEM_FAILURE_PEV_TELEMETRY | TCITEM_FAILURE_PEV_CORRELATION | TCITEM_FAILURE_PEV_2NDSTEP | TCITEM_FAILURE_PEV_PARAMETERS))
			{
				pItem->SetResult((pItem->GetResult() & ~TCITEM_RESULT_PEV_GO) | TCITEM_RESULT_PEV_NOGO);
				return;
			}
			if (pItem->GetResult() & (TCITEM_FAILURE_PEV_TELEMETRY | TCITEM_FAILURE_PEV_CORRELATION | TCITEM_FAILURE_PEV_2NDSTEP | TCITEM_FAILURE_PEV_PARAMETERS))
			{
				pItem->SetResult((pItem->GetResult() & ~TCITEM_RESULT_PEV_GO) | TCITEM_RESULT_PEV_NOGO);
				return;
			}
		}
		pItem->SetVerificationStageParameters(TCVERIFICATIONSTAGE_NONE, szParameters);
		pItem->SetResult((pItem->GetResult() & ~(TCITEM_RESULT_PEV_NOGO | TCITEM_FAILURE_PEV_TELEMETRY | TCITEM_FAILURE_PEV_CORRELATION | TCITEM_FAILURE_PEV_2NDSTEP | TCITEM_FAILURE_PEV_PARAMETERS)) | TCITEM_RESULT_PEV_GO);
		return;
	}
}
BOOL CTCProcessReleaseThread::CheckPreExecutionVerificationCondition(CONST CTCItem *pItem, CStringArray &szParameters) CONST
{
	CString  szProcedure;
	BOOL(__cdecl *pCheckThreadTCFunctionPreexecutionExpression)(INT nID, LPCTSTR pszThread, LPCTSTR pszStep, INT nEntry, CStringArray &szParameters);

#ifndef UNICODE
	szProcedure = STRING(IDS_EXPORTINTERFACE_CHECKTCPROCEDUREFUNCTIONPREEXECUTIONCONDITION);
#else
	WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_CHECKTCPROCEDUREFUNCTIONPREEXECUTIONCONDITION), -1, (LPSTR)szProcedure.GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_CHECKTCPROCEDUREFUNCTIONPREEXECUTIONCONDITION))), lstrlen(STRING(IDS_EXPORTINTERFACE_CHECKTCPROCEDUREFUNCTIONPREEXECUTIONCONDITION)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
	szProcedure.ReleaseBuffer();
#endif
	if ((pCheckThreadTCFunctionPreexecutionExpression = (BOOL(__cdecl *)(INT nID, LPCTSTR pszThread, LPCTSTR pszStep, INT nEntry, CStringArray &szParameters)) GetProcAddress(pItem->GetVerificationModule(), (LPCSTR)(LPCTSTR)szProcedure)) != (BOOL(__cdecl *)(INT nID, LPCTSTR pszThread, LPCTSTR pszStep, INT nEntry, CStringArray &szParameters)) NULL) return (*pCheckThreadTCFunctionPreexecutionExpression)(pItem->GetVerificationProcessID(), pItem->GetVerificationThread(), pItem->GetVerificationStep(), (pItem->GetMembershipID() != (UINT)-1) ? (pItem->GetMembershipID() + 1) : -1, szParameters);
	return FALSE;
}

int CTCProcessReleaseThread::Run()
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	INT  nCount;
	BOOL  bAfterDispatch;
	UINT  nExecutionOBRT;
	DWORD  dwReleaseOffset;
	DWORD  dwTimeout;
	DWORD  dwWaitCode;
	CTCItem  *pItem[3];
	CTCItems  pItems;
	CTimeTag  tExecutionTime;
	CTimeTag  tReleaseTime[3];
	CTimeSpan  tReleaseInterval;
	CUIntArray  nItemIDs;

	do
	{
		for (dwTimeout = INFINITE; Lock(); )
		{
			for (nIndex = 0, nCount = (GetTMService()->CheckTMStreamInterruption()) ? (INT)m_pItems.GetSize() : 0; nIndex < nCount; nIndex++)
			{
				if ((pItem[0] = m_pItems.GetAt(nIndex)) && pItem[0]->GetPreExeGroupRef() >= 0 && !pItem[0]->GetExecutionTime(tExecutionTime) && !pItem[0]->GetExecutionOBRT(nExecutionOBRT) && (pItem[0]->GetResult() & TCITEM_RESULT_PEV_GO) && (m_pTCProcessThread->GetCommandSourceTelecommandingChecks(pItem[0]->GetComputerName(), pItem[0]->GetSourceType()) & (TCSERVICE_COMMANDSOURCEFLAGS_PEV_OVERRIDE | TCSERVICE_COMMANDSOURCEFLAGS_PEV_DISABLE)) == 0 && (pItem[0]->GetFlags() & (TCITEM_CHECKFLAG_OVERRIDEPEV | TCITEM_CHECKFLAG_DISABLEPEV)) == 0)
				{
					pItem[0]->SetResult((pItem[0]->GetResult() & ~TCITEM_RESULT_PEV_GO) | TCITEM_RESULT_PEV_NOGO);
					continue;
				}
			}
			for (nIndex = 0, nCount = (INT)m_pItems.GetSize(), m_pTCProcessThread->CheckTCOnBoardBufferQueues(m_pItems), pItems.RemoveAll(); nIndex < nCount; nIndex++)
			{
				if ((pItem[0] = m_pItems.GetAt(nIndex)) && pItem[0]->GetAuthorizationStatus() == TCITEM_AUTHORIZATIONSTATUS_DENIED)
				{
					if ((pItem[1] = new CTCItem))
					{
						if (pItem[1]->Copy(pItem[0]))
						{
							for (CheckPreTransmissionValidationCondition(pItem[1]), pItem[1]->SetStatus(TCITEM_STATUS_NOTRELEASED); pItem[1]->GetResult() & (TCITEM_RESULT_PTV_GO | TCITEM_RESULT_PTV_WAIT); )
							{
								pItem[1]->SetResult((pItem[1]->GetResult() & ~(TCITEM_RESULT_PTV_WAIT | TCITEM_FAILURE_PTV_UPLINK | TCITEM_FAILURE_PTV_RELEASETIMEWINDOW | TCITEM_FAILURE_PTV_INTERLOCK | TCITEM_FAILURE_PTV_SUBSYSTEM | TCITEM_FAILURE_PTV_ONBOARDBUFFER)) | TCITEM_RESULT_PTV_FAIL);
								break;
							}
							pItems.InsertAt(pItems.GetSize(), pItem[1], 1);
							continue;
						}
						delete pItem[1];
					}
				}
			}
			for (nIndex = 0; (pItem[0] = (m_nState & TCSERVICE_COMMANDHANDLERSTATE_RUNNING) ? m_pItems.GetAt(nIndex) : (CTCItem *)NULL); )
			{
				if (pItem[0]->GetAuthorizationStatus() == TCITEM_AUTHORIZATIONSTATUS_DENIED)
				{
					nIndex++;
					continue;
				}
				if ((tReleaseTime[0] = CTimeTag().GetTime()) < pItem[0]->GetReleaseTime().GetTime())
				{
					dwTimeout = (DWORD)((pItem[0]->GetReleaseTime().GetTime() - tReleaseTime[0].GetTime()) / 1000);
					dwTimeout = min(1000 * SECONDSPERDAY, dwTimeout);
					break;
				}
				for (nItem = nIndex + 1, nItems = (INT)m_pItems.GetSize(), nCount = nItem - nIndex; nItem < nItems; nItem++)
				{
					if ((pItem[1] = m_pItems.GetAt(nItem)) && !pItem[0]->GetComputerName().CompareNoCase(pItem[1]->GetComputerName()) && pItem[0]->GetSourceType() == pItem[1]->GetSourceType() && pItem[0]->GetMembership() == pItem[1]->GetMembership() && (((pItem[0]->GetFlags() & TCITEM_LINKAGEFLAG_BLOCKED) && (pItem[1]->GetFlags() & TCITEM_LINKAGEFLAG_BLOCKED) && pItem[1]->GetReleaseBlockID() > 0) || (pItem[1]->GetFlags() & TCITEM_LINKAGEFLAG_GROUPED)) && pItem[0]->GetLoadTime() == pItem[1]->GetLoadTime())
					{
						nCount++;
						continue;
					}
					break;
				}
				for (nItem = nIndex, nItems = nItem + nCount; nItem < nItems; nItem++)
				{
					if ((pItem[1] = m_pItems.GetAt(nItem))) CheckPreTransmissionValidationCondition(pItem[1]);
					continue;
				}
				for (nItem = nIndex, nItems = nItem + nCount; nItem < nItems; nItem++)
				{
					if ((pItem[1] = m_pItems.GetAt(nItem)) && (pItem[1]->GetResult() & (TCITEM_RESULT_PTV_GO | TCITEM_RESULT_PEV_GO)) == (TCITEM_RESULT_PTV_GO | TCITEM_RESULT_PEV_GO)) continue;
					break;
				}
				if ((m_nState & TCSERVICE_COMMANDHANDLERSTATE_RUNNING) && nItem == nItems)
				{
					for (nItem = nIndex; nItem < nItems; nItem++)
					{
						if ((pItem[1] = m_pItems.GetAt(nItem)))
						{
							if ((pItem[2] = new CTCItem))
							{
								if (pItem[2]->Copy(pItem[1]) && pItems.Add(pItem[2]) >= 0) continue;
								delete pItem[2];
							}
						}
						pItems.RemoveAll();
						break;
					}
					if (nItem == nItems)
					{
						dwTimeout = 0;
						break;
					}
				}
				for (nItem = nIndex; nItem < nItems; nItem++)
				{
					if ((pItem[1] = m_pItems.GetAt(nItem)))
					{
						if (pItem[1]->GetReleaseTime() <= tReleaseTime[0].GetTime())
						{
							if (m_pTCProcessThread->IsCommandSourceTelecommandingReleaseWaitModeEnabled(pItem[1]->GetComputerName(), pItem[1]->GetSourceType()) || (pItem[1]->GetFlags() & TCITEM_EXECUTIONFLAG_TIMETAGGED))
							{
								if (pItem[1]->GetReleaseTimeWindow(tReleaseTime[1], tReleaseInterval) && tReleaseInterval.GetTotalSeconds() > 0)
								{
									if (tReleaseTime[1] > 0 && tReleaseTime[1].GetTime() + 1000000 * tReleaseInterval.GetTotalSeconds() > tReleaseTime[0].GetTime())
									{
										dwTimeout = (dwTimeout != INFINITE) ? min((DWORD)((tReleaseTime[1].GetTime() + 1000000 * tReleaseInterval.GetTotalSeconds() - tReleaseTime[0].GetTime()) / 1000), dwTimeout) : (DWORD)((tReleaseTime[1].GetTime() + 1000000 * tReleaseInterval.GetTotalSeconds() - tReleaseTime[0].GetTime()) / 1000);
										continue;
									}
									if (tReleaseTime[1] == 0)
									{
										if (pItem[1]->GetReleaseTime() > 0 && pItem[1]->GetReleaseTime().GetTime() + 1000000 * tReleaseInterval.GetTotalSeconds() > tReleaseTime[0].GetTime())
										{
											dwTimeout = (dwTimeout != INFINITE) ? min((DWORD)((pItem[1]->GetReleaseTime().GetTime() + 1000000 * tReleaseInterval.GetTotalSeconds() - tReleaseTime[0].GetTime()) / 1000), dwTimeout) : (DWORD)((pItem[1]->GetReleaseTime().GetTime() + 1000000 * tReleaseInterval.GetTotalSeconds() - tReleaseTime[0].GetTime()) / 1000);
											continue;
										}
										if (pItem[1]->GetReleaseTime() == 0 && pItem[1]->GetDispatchTime() > 0 && pItem[1]->GetDispatchTime().GetTime() + 1000000 * tReleaseInterval.GetTotalSeconds() > tReleaseTime[0].GetTime())
										{
											dwTimeout = (dwTimeout != INFINITE) ? min((DWORD)((pItem[1]->GetDispatchTime().GetTime() + 1000000 * tReleaseInterval.GetTotalSeconds() - tReleaseTime[0].GetTime()) / 1000), dwTimeout) : (DWORD)((pItem[1]->GetDispatchTime().GetTime() + 1000000 * tReleaseInterval.GetTotalSeconds() - tReleaseTime[0].GetTime()) / 1000);
											continue;
										}
									}
									pItem[1]->SetResult((pItem[1]->GetResult() & ~TCITEM_RESULT_PTV_WAIT) | (TCITEM_RESULT_PTV_FAIL | TCITEM_FAILURE_PTV_RELEASETIMEWINDOW));
									break;
								}
								if (pItem[1]->GetReleaseTimeWindow(tReleaseTime[1], tReleaseTime[2]) && tReleaseTime[2] > 0)
								{
									if (tReleaseTime[2].GetTime() > tReleaseTime[0].GetTime())
									{
										dwTimeout = (dwTimeout != INFINITE) ? min((DWORD)((tReleaseTime[2].GetTime() - tReleaseTime[0].GetTime()) / 1000), dwTimeout) : (DWORD)((tReleaseTime[2].GetTime() - tReleaseTime[0].GetTime()) / 1000);
										continue;
									}
									pItem[1]->SetResult((pItem[1]->GetResult() & ~TCITEM_RESULT_PTV_WAIT) | (TCITEM_RESULT_PTV_FAIL | TCITEM_FAILURE_PTV_RELEASETIMEWINDOW));
									break;
								}
								if (pItem[1]->GetReleaseTimeWindow(dwReleaseOffset, tReleaseInterval, bAfterDispatch) && tReleaseInterval > 0)
								{
									if (pItem[1]->GetReleaseTime() > 0 && pItem[1]->GetReleaseTime().GetTime() + 1000000 * tReleaseInterval.GetTotalSeconds() > tReleaseTime[0].GetTime())
									{
										dwTimeout = (dwTimeout != INFINITE) ? min((DWORD)((pItem[1]->GetReleaseTime().GetTime() + 1000000 * tReleaseInterval.GetTotalSeconds() - tReleaseTime[0].GetTime()) / 1000), dwTimeout) : (DWORD)((pItem[1]->GetReleaseTime().GetTime() + 1000000 * tReleaseInterval.GetTotalSeconds() - tReleaseTime[0].GetTime()) / 1000);
										continue;
									}
									if (pItem[1]->GetReleaseTime() == 0 && pItem[1]->GetDispatchTime() > 0 && pItem[1]->GetDispatchTime().GetTime() + 1000000 * tReleaseInterval.GetTotalSeconds() > tReleaseTime[0].GetTime())
									{
										dwTimeout = (dwTimeout != INFINITE) ? min((DWORD)((pItem[1]->GetDispatchTime().GetTime() + 1000000 * tReleaseInterval.GetTotalSeconds() - tReleaseTime[0].GetTime()) / 1000), dwTimeout) : (DWORD)((pItem[1]->GetDispatchTime().GetTime() + 1000000 * tReleaseInterval.GetTotalSeconds() - tReleaseTime[0].GetTime()) / 1000);
										continue;
									}
									pItem[1]->SetResult((pItem[1]->GetResult() & ~TCITEM_RESULT_PTV_WAIT) | (TCITEM_RESULT_PTV_FAIL | TCITEM_FAILURE_PTV_RELEASETIMEWINDOW));
									break;
								}
								if (pItem[1]->GetReleaseTime() > 0 && pItem[1]->GetReleaseTime().GetTime() + 1000000 * (tReleaseInterval = m_pTCProcessThread->GetDefaultReleaseTimeWindow(pItem[1]->GetComputerName(), pItem[1]->GetSourceType())).GetTotalSeconds() > tReleaseTime[0].GetTime())
								{
									dwTimeout = (dwTimeout != INFINITE) ? min((DWORD)((pItem[1]->GetReleaseTime().GetTime() + 1000000 * tReleaseInterval.GetTotalSeconds() - tReleaseTime[0].GetTime()) / 1000), dwTimeout) : (DWORD)((pItem[1]->GetReleaseTime().GetTime() + 1000000 * tReleaseInterval.GetTotalSeconds() - tReleaseTime[0].GetTime()) / 1000);
									continue;
								}
								if (pItem[1]->GetReleaseTime() == 0 && pItem[1]->GetDispatchTime() > 0 && pItem[1]->GetDispatchTime().GetTime() + 1000000 * (tReleaseInterval = m_pTCProcessThread->GetDefaultReleaseTimeWindow(pItem[1]->GetComputerName(), pItem[1]->GetSourceType())).GetTotalSeconds() > tReleaseTime[0].GetTime())
								{
									dwTimeout = (dwTimeout != INFINITE) ? min((DWORD)((pItem[1]->GetDispatchTime().GetTime() + 1000000 * tReleaseInterval.GetTotalSeconds() - tReleaseTime[0].GetTime()) / 1000), dwTimeout) : (DWORD)((pItem[1]->GetDispatchTime().GetTime() + 1000000 * tReleaseInterval.GetTotalSeconds() - tReleaseTime[0].GetTime()) / 1000);
									continue;
								}
								pItem[1]->SetResult((pItem[1]->GetResult() & ~TCITEM_RESULT_PTV_WAIT) | (TCITEM_RESULT_PTV_FAIL | TCITEM_FAILURE_PTV_RELEASETIMEWINDOW));
							}
							break;
						}
						dwTimeout = (dwTimeout != INFINITE) ? (DWORD)min(min((pItem[1]->GetReleaseTime().GetTime() - tReleaseTime[0].GetTime()) / 1000, dwTimeout), 1000 * (TIMETAG)SECONDSPERDAY) : (DWORD)min((pItem[1]->GetReleaseTime().GetTime() - tReleaseTime[0].GetTime()) / 1000, 1000 * (TIMETAG)SECONDSPERDAY);
					}
					nItem = nItems;
					break;
				}
				if (nItem < nItems)
				{
					for (nItem = 0, nItems = m_pItems.Collect(nIndex, nItemIDs); nItem < nItems; nItem++)
					{
						if ((pItem[1] = m_pItems.GetAt(nItemIDs.GetAt(nItem))))
						{
							for (; nIndex != (INT)nItemIDs.GetAt(nItem); )
							{
								CheckPreTransmissionValidationCondition(pItem[1]);
								break;
							}
							for (; pItem[1]->GetResult() & TCITEM_RESULT_PTV_WAIT; )
							{
								pItem[1]->SetResult((pItem[1]->GetResult() & ~TCITEM_RESULT_PTV_WAIT) | TCITEM_RESULT_PTV_FAIL);
								break;
							}
							if ((pItem[2] = new CTCItem))
							{
								if (pItem[2]->Copy(pItem[1]) && pItems.Add(pItem[2]) >= 0)
								{
									pItem[1]->SetStatus((nIndex != (INT)nItemIDs.GetAt(nItem)) ? TCITEM_STATUS_NOTRELEASED : TCITEM_STATUS_FAILEDRELEASE);
									pItem[2]->SetStatus((nIndex != (INT)nItemIDs.GetAt(nItem)) ? TCITEM_STATUS_NOTRELEASED : TCITEM_STATUS_FAILEDRELEASE);
									continue;
								}
								delete pItem[2];
							}
						}
						break;
					}
					dwTimeout = 0;
					break;
				}
				nIndex += nCount;
				continue;
			}
			for (nItem = 0, nItems = (INT)pItems.GetSize(); nItem < nItems; nItem++)
			{
				if ((pItem[0] = pItems.GetAt(nItem)) != (CTCItem *)NULL)
				{
					for (pItem[0]->SetFlags((m_pTCProcessThread->GetCommandSourceTelecommandingChecks(pItem[0]->GetComputerName(), pItem[0]->GetSourceType()) & (TCSERVICE_COMMANDSOURCEFLAGS_PTV_OVERRIDE | TCSERVICE_COMMANDSOURCEFLAGS_PTV_DISABLE | TCSERVICE_COMMANDSOURCEFLAGS_PEV_OVERRIDE | TCSERVICE_COMMANDSOURCEFLAGS_PEV_DISABLE | TCSERVICE_COMMANDSOURCEFLAGS_CEV_OVERRIDE | TCSERVICE_COMMANDSOURCEFLAGS_CEV_DISABLE)) | pItem[0]->GetFlags()); (pItem[0]->GetFlags() & (TCITEM_CHECKFLAG_OVERRIDEPTV | TCITEM_CHECKFLAG_DISABLEPTV)) == (TCITEM_CHECKFLAG_OVERRIDEPTV | TCITEM_CHECKFLAG_DISABLEPTV) || ((pItem[0]->GetFlags() & (TCITEM_CHECKFLAG_OVERRIDEPTV | TCITEM_CHECKFLAG_DISABLEPTV)) == 0 && !m_pTCProcessThread->IsCommandSourceTelecommandingInterlockModeEnabled(pItem[0]->GetComputerName(), pItem[0]->GetSourceType())); )
					{
						pItem[0]->SetFlags((pItem[0]->GetFlags() & ~TCITEM_CHECKFLAG_OVERRIDEPTV) | TCITEM_CHECKFLAG_DISABLEPTV);
						break;
					}
					if ((pItem[0]->GetFlags() & (TCITEM_CHECKFLAG_OVERRIDEPEV | TCITEM_CHECKFLAG_DISABLEPEV)) == (TCITEM_CHECKFLAG_OVERRIDEPEV | TCITEM_CHECKFLAG_DISABLEPEV)) pItem[0]->SetFlags((pItem[0]->GetFlags() & ~TCITEM_CHECKFLAG_OVERRIDEPEV) | TCITEM_CHECKFLAG_DISABLEPEV);
					if ((pItem[0]->GetFlags() & (TCITEM_CHECKFLAG_OVERRIDECEV | TCITEM_CHECKFLAG_DISABLECEV)) == (TCITEM_CHECKFLAG_OVERRIDECEV | TCITEM_CHECKFLAG_DISABLECEV)) pItem[0]->SetFlags((pItem[0]->GetFlags() & ~TCITEM_CHECKFLAG_OVERRIDECEV) | TCITEM_CHECKFLAG_DISABLECEV);
				}
			}
			Unlock();
			break;
		}
		for (; (nItems = (INT)pItems.GetSize()) > 0; )
		{
			m_pTCProcessThread->ReleaseTelecommands(pItems);
			break;
		}
		for (Lock(), nItem = 0; nItem < nItems; nItem++)
		{
			if ((pItem[0] = pItems.GetAt(nItem)))
			{
				if ((pItem[1] = m_pItems.GetAt((nIndex = m_pItems.Find(pItem[0])))))
				{
					m_pItems.RemoveAt(nIndex);
					delete pItem[1];
				}
			}
		}
		m_pTCProcessThread->CheckTCOnBoardBufferQueues(m_pItems);
		Unlock();
	} while ((dwWaitCode = Wait(m_bUpdate, FALSE, dwTimeout)) == WAIT_OBJECT_0 + 1 || dwWaitCode == WAIT_TIMEOUT);
	return ExitInstance();
}

BOOL CTCProcessReleaseThread::Lock()
{
	return((m_pTCProcessThread) ? (m_pTCProcessThread->Lock() && CThread::Lock()) : CThread::Lock());
}

BOOL CTCProcessReleaseThread::Unlock()
{
	return((m_pTCProcessThread) ? (CThread::Unlock() && m_pTCProcessThread->Unlock()) : CThread::Unlock());
}

BEGIN_MESSAGE_MAP(CTCProcessReleaseThread, CThread)
	//{{AFX_MSG_MAP(CTCProcessReleaseThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcessReleaseThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CTCProcessVerificationThread

IMPLEMENT_DYNAMIC(CTCProcessVerificationThread, CThread)

CTCProcessVerificationThread::CTCProcessVerificationThread(CTCProcessThread *pThread) : CThread()
{
	m_nState = TCSERVICE_COMMANDHANDLERSTATE_NONE;
	m_pTCProcessThread = pThread;
}

BOOL CTCProcessVerificationThread::Start()
{
	return CreateThread((LPVOID)NULL, THREAD_PRIORITY_ABOVE_NORMAL);
}

BOOL CTCProcessVerificationThread::Stop()
{
	return((DestroyThread() >= 0) ? TRUE : FALSE);
}

BOOL CTCProcessVerificationThread::InitInstance()
{
	return((AfxSocketInit()) ? m_cSocket.Create() : FALSE);
}

int CTCProcessVerificationThread::ExitInstance()
{
	m_cSocket.Close();
	return CThread::ExitInstance();
}

BOOL CTCProcessVerificationThread::SetState(UINT nState)
{
	CTCChainLock  cLock(this);

	if (m_nState != nState)
	{
		m_nState = nState;
		Update();
		return TRUE;
	}
	return FALSE;
}

UINT CTCProcessVerificationThread::GetState() CONST
{
	CTCChainLock  cLock(this);

	return m_nState;
}

BOOL CTCProcessVerificationThread::Update(CONST CTCItems &pItems, BOOL bRemove)
{
	INT  nIndex;
	INT  nItem[2];
	INT  nItems[2];
	BOOL  bUpdate;
	CTCItem  *pItem[3];
	CTimeTag  tExecutionTime;
	CTimeTag  tVerificationTime[2];
	CTCChainLock  cLock(this);

	for (nItem[0] = 0, nItems[0] = (!bRemove) ? (INT)pItems.GetSize() : 0, bUpdate = TRUE; nItem[0] < nItems[0]; nItem[0]++)
	{
		if ((pItem[0] = pItems.GetAt(nItem[0])) && (pItem[0]->GetStatus() == TCITEM_STATUS_RELEASED || pItem[0]->GetStatus() == TCITEM_STATUS_SENT || pItem[0]->GetStatus() == TCITEM_STATUS_UPLINKED))
		{
			if ((pItem[1] = m_pItems.GetAt((nIndex = m_pItems.Find(pItem[0])))))
			{
				m_pItems.RemoveAt(nIndex);
				delete pItem[1];
			}
			if ((pItem[1] = new CTCItem))
			{
				if (pItem[1]->Copy(pItem[0]))
				{
					for (nItem[1] = 0, nItems[1] = (INT)m_pItems.GetSize(), tVerificationTime[0] = (pItem[1]->GetExecutionTime(tExecutionTime)) ? tExecutionTime : ((pItem[1]->GetReleaseTime() > 0) ? pItem[1]->GetReleaseTime() : tVerificationTime[1]), pItem[1]->SetVerificationTime(tVerificationTime[0].GetTime() + 1000000 * pItem[1]->CalcVerificationTimeWindowOffset(0).GetTotalSeconds()), pItem[1]->SetResult(pItem[1]->GetResult() & ~(TCITEM_RESULT_CEV_IDLE | TCITEM_RESULT_CEV_PENDING | TCITEM_RESULT_CEV_PASSED | TCITEM_RESULT_CEV_FAILED | TCITEM_RESULT_CEV_UNKNOWN | TCITEM_RESULT_CEV_UNVERIFIED)); nItem[1] < nItems[1]; nItem[1]++)
					{
						if ((pItem[2] = m_pItems.GetAt(nItem[1])) && pItem[1]->GetVerificationTime() < pItem[2]->GetVerificationTime()) break;
						continue;
					}
					InitExecutionVerificationData(pItem[1]);
					m_pItems.InsertAt(nItem[1], pItem[1], 1);
					continue;
				}
				delete pItem[1];
			}
			bUpdate = FALSE;
			break;
		}
	}
	for (nItem[1] = 0, nItems[1] = (bRemove || !bUpdate) ? (INT)pItems.GetSize() : 0; nItem[1] < nItems[1]; nItem[1]++)
	{
		if ((pItem[1] = ((pItem[0] = pItems.GetAt(nItem[1]))) ? m_pItems.GetAt((nIndex = m_pItems.Find(pItem[0]))) : (CTCItem *)NULL))
		{
			m_pItems.RemoveAt(nIndex);
			delete pItem[1];
			continue;
		}
		bUpdate = FALSE;
	}
	Update();
	return bUpdate;
}
BOOL CTCProcessVerificationThread::Update(CONST CTCProcessEngine *pTCProcessEngine, CONST CTCEnvironment *pTCEnvironment, CONST CTMEnvironment *pTMEnvironment, CONST CTCInterlocks &pTCInterlocks, CTCItems &pItems, CTCInterlocks &pInterlocks)
{
	INT  nItem;
	INT  nItems;
	INT  nCount;
	INT  nStage;
	INT  nStages;
	INT  nInterlock;
	INT  nInterlocks;
	BOOL  bStage;
	UINT  nState;
	UINT  nReason;
	UINT  nStageID;
	CTCItem  *pItem[2];
	CTimeTag  tExecutionTime;
	CTimeSpan  tTimeWindow[3];
	CUIntArray  nStageIDs;
	CStringArray  szParameters;
	CTCInterlock  *pInterlock[2];
	CTCChainLock  cLock(this);

	for (nItem = 0, nItems = (INT)m_pItems.GetSize(), pItems.Copy(&m_pItems), pInterlocks.Copy(&pTCInterlocks); nItem < nItems; nItem++)
	{
		if ((pItem[0] = m_pItems.GetAt(nItem)) && pItem[0]->EnumVerificationStageIDs(nStageIDs) > 0)
		{
			for (tTimeWindow[0] = pItem[0]->CalcVerificationTimeWindowSize(0, (m_pTCProcessThread->GetCommandHandlerVerificationUncertaintyTimeWindow(tTimeWindow[1])) ? tTimeWindow[1] : 0); pItem[0]->GetExecutionTime(tExecutionTime); )
			{
				CheckPreExecutionVerificationCondition(pTCProcessEngine, pTMEnvironment, pItem[0]);
				break;
			}
			if (pItem[0]->GetResult() & TCITEM_RESULT_CEV_PENDING)
			{
				if (pTMEnvironment->GetTMUnit()->GetTimeTag().GetTime() > pItem[0]->GetVerificationTime().GetTime() + 1000000 * tTimeWindow[0].GetTotalSeconds())
				{
					for (nStage = 0, nStages = (INT)nStageIDs.GetSize(); nStage < nStages; nStage++)
					{
						if (CheckExecutionVerificationTimeWindowClosure(pTMEnvironment, pItem[0], nStageIDs.GetAt(nStage)))
						{
							if (pItem[0]->GetVerificationStageState(nStageIDs.GetAt(nStage), nState, nReason)) pItem[0]->SetVerificationStageState(nStageIDs.GetAt(nStage), (nReason & TCITEM_FAILURE_CEV_PARAMETERS) ? TCITEM_RESULT_CEV_FAILED : TCITEM_RESULT_CEV_UNKNOWN, nReason);
							continue;
						}
					}
					for (nStage = 0; nStage < nStages; nStage++)
					{
						if (!pItem[0]->GetVerificationStageState(nStageIDs.GetAt(nStage), nState, nReason) || (nState & (TCITEM_RESULT_CEV_PASSED | TCITEM_RESULT_CEV_FAILED | TCITEM_RESULT_CEV_UNKNOWN | TCITEM_RESULT_CEV_UNVERIFIED))) continue;
						break;
					}
					pItem[0]->SetResult((nStage == nStages) ? ((pItem[0]->GetResult() & ~TCITEM_RESULT_CEV_PENDING) | TCITEM_RESULT_CEV_UNVERIFIED) : pItem[0]->GetResult());
					continue;
				}
				for (nStage = 0, nStages = (INT)nStageIDs.GetSize(), bStage = (pItem[0]->GetResult() & TCITEM_RESULT_PEV_GO) ? TRUE : FALSE; nStage < nStages; nStage++)
				{
					for (tTimeWindow[2] = pItem[0]->CalcVerificationTimeWindowOffset((nStageID = nStageIDs.GetAt(nStage)), tTimeWindow[1]) - pItem[0]->CalcVerificationTimeWindowOffset(nStageID), nState = TCITEM_RESULT_NONE, nReason = 0; !pItem[0]->GetVerificationStageState(nStageID, nState, nReason) || nState == TCITEM_RESULT_CEV_IDLE || nState == TCITEM_RESULT_CEV_PENDING; )
					{
						if (pTMEnvironment->GetTMUnit()->GetTimeTag().GetTime() > pItem[0]->GetVerificationTime().GetTime() + 1000000 * pItem[0]->CalcVerificationTimeWindowSize(nStageID, tTimeWindow[1]).GetTotalSeconds())
						{
							for (CheckExecutionVerificationCondition(pTCProcessEngine, pTMEnvironment, pItem[0], nStageID, 0, tTimeWindow[2], szParameters), pItem[0]->SetVerificationStageState(nStageID, (nState = (szParameters.GetSize() > 0) ? TCITEM_RESULT_CEV_FAILED : TCITEM_RESULT_CEV_UNKNOWN), (szParameters.GetSize() > 0) ? TCITEM_FAILURE_CEV_PARAMETERS : 0), pItem[0]->SetVerificationStageParameters(nStageID, szParameters); (pInterlock[0] = (nState == TCITEM_RESULT_CEV_FAILED) ? pTCInterlocks.GetAt(pTCInterlocks.Find(pItem[0]->GetComputerName(), pItem[0]->GetSourceType(), pItem[0]->GetInterlock())) : (CTCInterlock *)NULL) && ((pInterlock[0]->GetStage() == TCINTERLOCK_STAGE_ACCEPTANCE && MAKETCEXEVERSTAGEFROMID(nStageID) == TCEXEVERSTAGE_TYPE_ACCEPTANCE) || (pInterlock[0]->GetStage() == TCINTERLOCK_STAGE_START && MAKETCEXEVERSTAGEFROMID(nStageID) == TCEXEVERSTAGE_TYPE_START) || (pInterlock[0]->GetStage() == TCINTERLOCK_STAGE_PROGRESS && MAKETCEXEVERSTAGEFROMID(nStageID) == TCEXEVERSTAGE_TYPE_PROGRESS) || (pInterlock[0]->GetStage() == TCINTERLOCK_STAGE_COMPLETION && MAKETCEXEVERSTAGEFROMID(nStageID) == TCEXEVERSTAGE_TYPE_COMPLETION)); )
							{
								pInterlock[0]->SetState(TCINTERLOCK_STATE_FAILURE);
								break;
							}
							break;
						}
						if (pTMEnvironment->GetTMUnit()->GetTimeTag() >= pItem[0]->GetVerificationTime().GetTime())
						{
							if (bStage  &&  CheckExecutionVerificationCondition(pTCProcessEngine, pTMEnvironment, pItem[0], nStageID, pItem[0]->GetVerificationTime().GetTime() + 1000000 * tTimeWindow[2].GetTotalSeconds(), tTimeWindow[2], szParameters))
							{
								for (pItem[0]->SetVerificationStageState(nStageID, TCITEM_RESULT_CEV_PASSED), pItem[0]->SetVerificationStageParameters(nStageID, szParameters); (pInterlock[0] = pTCInterlocks.GetAt(pTCInterlocks.Find(pItem[0]->GetComputerName(), pItem[0]->GetSourceType(), pItem[0]->GetInterlock()))) && ((pInterlock[0]->GetStage() == TCINTERLOCK_STAGE_ACCEPTANCE && MAKETCEXEVERSTAGEFROMID(nStageID) == TCEXEVERSTAGE_TYPE_ACCEPTANCE) || (pInterlock[0]->GetStage() == TCINTERLOCK_STAGE_START && MAKETCEXEVERSTAGEFROMID(nStageID) == TCEXEVERSTAGE_TYPE_START) || (pInterlock[0]->GetStage() == TCINTERLOCK_STAGE_PROGRESS && MAKETCEXEVERSTAGEFROMID(nStageID) == TCEXEVERSTAGE_TYPE_PROGRESS) || (pInterlock[0]->GetStage() == TCINTERLOCK_STAGE_COMPLETION && MAKETCEXEVERSTAGEFROMID(nStageID) == TCEXEVERSTAGE_TYPE_COMPLETION)); )
								{
									pInterlock[0]->SetState(TCINTERLOCK_STATE_SUCCESS);
									break;
								}
								break;
							}
							for (pItem[0]->SetVerificationStageState(nStageID, (nState = (szParameters.GetSize() > 0 && bStage) ? TCITEM_RESULT_CEV_FAILED : TCITEM_RESULT_CEV_PENDING), (szParameters.GetSize() > 0 && bStage) ? TCITEM_FAILURE_CEV_PARAMETERS : 0); bStage; )
							{
								pItem[0]->SetVerificationStageParameters(nStageID, szParameters);
								break;
							}
							if (nState == TCITEM_RESULT_CEV_PENDING)
							{
								if ((pInterlock[0] = pTCInterlocks.GetAt(pTCInterlocks.Find(pItem[0]->GetComputerName(), pItem[0]->GetSourceType(), pItem[0]->GetInterlock()))) && (pInterlock[0]->GetScope() == TCINTERLOCK_SCOPE_LOCALNOWAIT || pInterlock[0]->GetScope() == TCINTERLOCK_SCOPE_LOCALSUBSYSTEMNOWAIT))
								{
									if ((pInterlock[0]->GetStage() == TCINTERLOCK_STAGE_ACCEPTANCE  &&  MAKETCEXEVERSTAGEFROMID(nStageID) == TCEXEVERSTAGE_TYPE_ACCEPTANCE) || (pInterlock[0]->GetStage() == TCINTERLOCK_STAGE_START  &&  MAKETCEXEVERSTAGEFROMID(nStageID) == TCEXEVERSTAGE_TYPE_START) || (pInterlock[0]->GetStage() == TCINTERLOCK_STAGE_PROGRESS  &&  MAKETCEXEVERSTAGEFROMID(nStageID) == TCEXEVERSTAGE_TYPE_PROGRESS) || (pInterlock[0]->GetStage() == TCINTERLOCK_STAGE_COMPLETION  &&  MAKETCEXEVERSTAGEFROMID(nStageID) == TCEXEVERSTAGE_TYPE_COMPLETION))
									{
										pItem[0]->SetVerificationStageState(nStageID, TCITEM_RESULT_CEV_PASSED);
										break;
									}
								}
							}
							if ((pInterlock[0] = (nState == TCITEM_RESULT_CEV_FAILED) ? pTCInterlocks.GetAt(pTCInterlocks.Find(pItem[0]->GetComputerName(), pItem[0]->GetSourceType(), pItem[0]->GetInterlock())) : (CTCInterlock *)NULL) && ((pInterlock[0]->GetStage() == TCINTERLOCK_STAGE_ACCEPTANCE  &&  MAKETCEXEVERSTAGEFROMID(nStageID) == TCEXEVERSTAGE_TYPE_ACCEPTANCE) || (pInterlock[0]->GetStage() == TCINTERLOCK_STAGE_START  &&  MAKETCEXEVERSTAGEFROMID(nStageID) == TCEXEVERSTAGE_TYPE_START) || (pInterlock[0]->GetStage() == TCINTERLOCK_STAGE_PROGRESS  &&  MAKETCEXEVERSTAGEFROMID(nStageID) == TCEXEVERSTAGE_TYPE_PROGRESS) || (pInterlock[0]->GetStage() == TCINTERLOCK_STAGE_COMPLETION  &&  MAKETCEXEVERSTAGEFROMID(nStageID) == TCEXEVERSTAGE_TYPE_COMPLETION))) pInterlock[0]->SetState(TCINTERLOCK_STATE_FAILURE);
						}
						break;
					}
					if (!(bStage = (pItem[0]->GetVerificationStageState(nStageID, nState, nReason) && nState != TCITEM_RESULT_CEV_IDLE  &&  nState != TCITEM_RESULT_CEV_PENDING) ? bStage : FALSE)) break;
				}
				for (nStage = 0, nStages = (bStage) ? nStages : -1; nStage < nStages; nStage++)
				{
					if (!pItem[0]->GetVerificationStageState(nStageIDs.GetAt(nStage), nState, nReason) || nState != TCITEM_RESULT_CEV_PASSED) break;
					continue;
				}
				if (nStage == nStages)
				{
					pItem[0]->SetResult((pItem[0]->GetResult() & ~TCITEM_RESULT_CEV_PENDING) | TCITEM_RESULT_CEV_PASSED);
					continue;
				}
				for (nStage = 0; nStage < nStages; nStage++)
				{
					if (pItem[0]->GetVerificationStageState(nStageIDs.GetAt(nStage), nState, nReason) && nState == TCITEM_RESULT_CEV_FAILED) break;
					continue;
				}
				if (nStage < nStages)
				{
					pItem[0]->SetResult((pItem[0]->GetResult() & ~TCITEM_RESULT_CEV_PENDING) | TCITEM_RESULT_CEV_FAILED);
					continue;
				}
			}
		}
	}
	for (nItem = 0, nItems = (INT)m_pItems.GetSize(), nCount = 0; nItem < nItems; nItem++)
	{
		if ((pItem[1] = ((pItem[0] = m_pItems.GetAt(nItem))) ? pItems.GetAt(nItem - nCount) : (CTCItem *)NULL))
		{
			if (pItem[0]->Compare(pItem[1]))
			{
				pItems.RemoveAt(nItem - nCount);
				delete pItem[1];
				nCount++;
				continue;
			}
			pItem[1]->Copy(pItem[0]);
		}
	}
	for (nInterlock = 0, nInterlocks = (INT)pTCInterlocks.GetSize(), nCount = 0; nInterlock < nInterlocks; nInterlock++)
	{
		if ((pInterlock[1] = ((pInterlock[0] = pTCInterlocks.GetAt(nInterlock))) ? pInterlocks.GetAt(nInterlock - nCount) : (CTCInterlock *)NULL))
		{
			if (pInterlock[0]->Compare(pInterlock[1]))
			{
				pInterlocks.RemoveAt(nInterlock - nCount);
				delete pInterlock[1];
				nCount++;
				continue;
			}
			pInterlock[1]->Copy(pInterlock[0]);
		}
	}
	if (pItems.GetSize() > 0) Update();
	return(nItems >= 0 && nInterlocks >= 0);
}
VOID CTCProcessVerificationThread::Update(INT nDataID, UINT nStatus, BOOL bSuccess)
{
	INT  nID;
	INT  nIDs;
	INT  nItem;
	INT  nItems;
	CTCItem  *pItem;
	CTimeTag  tTransmissionTime;
	CUIntArray  nReleaseIDs;
	CTCChainLock  cLock(this);

	for (nItem = 0, nItems = (INT)m_pItems.GetSize(); nItem < nItems; nItem++)
	{
		if ((pItem = m_pItems.GetAt(nItem)) && pItem->GetReleaseIDs(nReleaseIDs) > 0)
		{
			for (nID = 0, nIDs = (INT)nReleaseIDs.GetSize(); nID < nIDs; nID++)
			{
				if (nDataID == nReleaseIDs.GetAt(nID)) break;
				continue;
			}
			if (nID < nIDs)
			{
				if ((nStatus & (IODEVICE_DATASTATUS_SENT | IODEVICE_DATASTATUS_PROCESSED)) == IODEVICE_DATASTATUS_SENT)
				{
					pItem->SetStatus((bSuccess) ? TCITEM_STATUS_SENT : TCITEM_STATUS_FAILEDSEND);
					Update();
					break;
				}
				if ((nStatus & (IODEVICE_DATASTATUS_SENT | IODEVICE_DATASTATUS_PROCESSED)) == IODEVICE_DATASTATUS_PROCESSED)
				{
					pItem->SetTransmissionTime((bSuccess) ? tTransmissionTime.GetTime() : -tTransmissionTime.GetTime());
					pItem->SetStatus((bSuccess) ? TCITEM_STATUS_UPLINKED : TCITEM_STATUS_FAILEDUPLINK);
					Update();
				}
				break;
			}
		}
	}
}
BOOL CTCProcessVerificationThread::Update()
{
	return m_bUpdate.SetEvent();
}

BOOL CTCProcessVerificationThread::Acknowledge(CONST CTCItems &pItems)
{
	INT  nItem;
	INT  nItems;
	INT  nStage;
	INT  nStages;
	BOOL  bItems;
	UINT  nState;
	UINT  nReason;
	CTCItem  *pItem[2];
	CTimeTag  tAcknowledgeTime;
	CUIntArray  nStageIDs;
	CTCChainLock  cLock(this);

	for (nItem = 0, nItems = (INT)pItems.GetSize(), bItems = FALSE; nItem < nItems; nItem++)
	{
		if ((pItem[1] = ((pItem[0] = pItems.GetAt(nItem))) ? m_pItems.GetAt(m_pItems.Find(pItem[0])) : (CTCItem *)NULL) && (pItem[1]->GetResult() & TCITEM_RESULT_CEV_UNKNOWN))
		{
			for (nStage = 0, nStages = pItem[1]->EnumVerificationStageIDs(nStageIDs), pItem[0]->SetFlags(pItem[0]->GetFlags() | TCITEM_ACKNOWLEDGEFLAG_ALL), pItem[1]->SetFlags(pItem[1]->GetFlags() | TCITEM_ACKNOWLEDGEFLAG_ALL), pItem[1]->SetResult((pItem[1]->GetResult() & ~TCITEM_RESULT_CEV_UNKNOWN) | TCITEM_RESULT_CEV_UNVERIFIED), pItem[0]->SetAcknowledgeTime(tAcknowledgeTime), pItem[1]->SetAcknowledgeTime(tAcknowledgeTime), bItems = TRUE; nStage < nStages; nStage++)
			{
				if (pItem[1]->GetVerificationStageState(nStageIDs.GetAt(nStage), nState, nReason) && (nState & TCITEM_RESULT_CEV_UNKNOWN))
				{
					pItem[1]->SetVerificationStageState(nStageIDs.GetAt(nStage), TCITEM_RESULT_CEV_UNVERIFIED, nReason);
					continue;
				}
			}
			continue;
		}
		if ((pItem[0] = pItems.GetAt(nItem)))
		{
			pItem[0]->SetFlags(pItem[0]->GetFlags() & ~TCITEM_ACKNOWLEDGEFLAG_ALL);
			pItem[0]->SetAcknowledgeTime(tAcknowledgeTime);
		}
	}
	if (bItems) Update();
	return TRUE;
}

BOOL CTCProcessVerificationThread::Discard(CONST CTCItems &pItems)
{
	INT  nItem;
	INT  nItems;
	BOOL  bItems;
	CTCItem  *pItem[2];
	CTCChainLock  cLock(this);

	for (nItem = 0, nItems = (INT)pItems.GetSize(), bItems = FALSE; nItem < nItems; nItem++)
	{
		if ((pItem[1] = ((pItem[0] = pItems.GetAt(nItem))) ? m_pItems.GetAt(m_pItems.Find(pItem[0])) : (CTCItem *)NULL) && (pItem[1]->GetResult() & (TCITEM_RESULT_CEV_IDLE | TCITEM_RESULT_CEV_PENDING | TCITEM_RESULT_CEV_UNKNOWN)))
		{
			pItem[1]->SetResult((pItem[1]->GetResult() & ~(TCITEM_RESULT_CEV_IDLE | TCITEM_RESULT_CEV_PENDING | TCITEM_RESULT_CEV_UNKNOWN)) | TCITEM_RESULT_CEV_UNVERIFIED);
			bItems = TRUE;
		}
	}
	if (bItems) Update();
	return TRUE;
}

BOOL CTCProcessVerificationThread::Reset()
{
	CTCChainLock  cLock(this);

	m_pItems.RemoveAll();
	Update();
	return TRUE;
}

BOOL CTCProcessVerificationThread::IsEmpty() CONST
{
	CTCChainLock  cLock(this);

	return((!m_pItems.GetSize()) ? TRUE : FALSE);
}

BOOL CTCProcessVerificationThread::SetContents(CONST CTCItems &pItems)
{
	CTCChainLock  cLock(this);

	if (m_pItems.Copy(&pItems))
	{
		Update();
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcessVerificationThread::GetContents(CTCItems &pItems) CONST
{
	CTCChainLock  cLock(this);

	return pItems.Copy(&m_pItems);
}

VOID CTCProcessVerificationThread::InitExecutionVerificationData(CTCItem *pItem) CONST
{
	INT  nStage;
	INT  nStages;
	INT  nParameter;
	INT  nParameters;
	BOOL  bParameter;
	UINT  nStageID;
	CString  szClosure;
	CUIntArray  nStageIDs;
	CTimeSpan  tStageTimeWindow[3];
	CDatabaseTCExeVerGroup  *pGroup;
	CDatabaseTCExeVerGroupParameter  *pGroupParameter;

	if ((pGroup = (pItem->CalcVerificationTimeWindowSize() == 0) ? GetDatabase()->GetTCExeVerGroups()->GetAt(pItem->GetExeVerGroupRef()) : (CDatabaseTCExeVerGroup *)NULL))
	{
		for (nParameter = 0, nParameters = (INT)pGroup->GetSize(); nParameter < nParameters; nParameter++)
		{
			if ((pGroupParameter = pGroup->GetAt(nParameter)) != (CDatabaseTCExeVerGroupParameter *)NULL)
			{
				for (nStage = 0, nStages = (INT)nStageIDs.GetSize(), nStageID = MAKETCEXEVERSTAGEID(pGroupParameter->GetStage(), pGroupParameter->GetStep()); nStage < nStages; nStage++)
				{
					if (nStageIDs.GetAt(nStage) == nStageID) break;
					if (nStageIDs.GetAt(nStage) > nStageID)
					{
						nStageIDs.InsertAt(nStage, nStageID);
						break;
					}
				}
				if (nStage == nStages)
				{
					nStageIDs.InsertAt(nStage, nStageID);
					continue;
				}
			}
		}
		for (nStage = 0, nStages = (INT)nStageIDs.GetSize(); nStage < nStages; nStage++)
		{
			for (nParameter = 0, bParameter = FALSE; nParameter < nParameters; nParameter++)
			{
				if ((pGroupParameter = pGroup->GetAt(nParameter)) && nStageIDs.GetAt(nStage) == MAKETCEXEVERSTAGEID(pGroupParameter->GetStage(), pGroupParameter->GetStep()))
				{
					tStageTimeWindow[0] = (bParameter) ? min(pGroupParameter->GetTimeWindowOffset(), tStageTimeWindow[0]) : pGroupParameter->GetTimeWindowOffset();
					tStageTimeWindow[1] = (bParameter) ? max(pGroupParameter->GetTimeWindowInterval(), tStageTimeWindow[1]) : pGroupParameter->GetTimeWindowInterval();
					tStageTimeWindow[2] = (bParameter) ? max(pGroupParameter->GetTimeWindowUncertainty(), tStageTimeWindow[2]) : pGroupParameter->GetTimeWindowUncertainty();
					szClosure = (!pGroupParameter->GetTimeWindowClosurePacket().IsEmpty()) ? pGroupParameter->GetTimeWindowClosurePacket() : szClosure;
					bParameter = TRUE;
				}
			}
			if (nParameters > 0)
			{
				pItem->SetVerificationTimeWindow(nStageIDs.GetAt(nStage), tStageTimeWindow[0], tStageTimeWindow[1], tStageTimeWindow[2]);
				pItem->SetVerificationStageClosure(nStageIDs.GetAt(nStage), szClosure);
			}
		}
	}
}

VOID CTCProcessVerificationThread::CheckPreExecutionVerificationCondition(CONST CTCProcessEngine *pTCProcessEngine, CONST CTMEnvironment *pTMEnvironment, CTCItem *pItem) CONST
{
	CStringArray  szParameters;

	if (pItem->GetSourceType() == TCITEM_SOURCETYPE_MANUALSTACK || pItem->GetSourceType() == TCITEM_SOURCETYPE_AUTOMATICSTACK)
	{
		if ((pItem->GetFlags() & (TCITEM_CHECKFLAG_OVERRIDEPEV | TCITEM_CHECKFLAG_DISABLEPEV)) == 0 && (m_pTCProcessThread->GetCommandSourceTelecommandingChecks(pItem->GetComputerName(), pItem->GetSourceType()) & (TCSERVICE_COMMANDSOURCEFLAGS_PEV_OVERRIDE | TCSERVICE_COMMANDSOURCEFLAGS_PEV_DISABLE)) == 0)
		{
			for (pItem->SetResult(pItem->GetResult() & ~(TCITEM_FAILURE_PEV_TELEMETRY | TCITEM_FAILURE_PEV_PARAMETERS)); pItem->GetPreExeGroupRef() >= 0; )
			{
				if (!pTCProcessEngine->CheckTCFunctionPreexecutionParameterGroup(GetDatabase(), pTMEnvironment, pItem->GetPreExeGroupRef(), szParameters))
				{
					pItem->SetVerificationStageParameters(TCVERIFICATIONSTAGE_NONE, szParameters);
					pItem->SetResult(pItem->GetResult() | TCITEM_FAILURE_PEV_PARAMETERS);
				}
				if (GetTMService()->CheckTMStreamInterruption()) pItem->SetResult(pItem->GetResult() | TCITEM_FAILURE_PEV_TELEMETRY);
				break;
			}
			if (pItem->GetResult() & (TCITEM_FAILURE_PEV_TELEMETRY | TCITEM_FAILURE_PEV_CORRELATION | TCITEM_FAILURE_PEV_2NDSTEP | TCITEM_FAILURE_PEV_PARAMETERS))
			{
				pItem->SetResult((pItem->GetResult() & ~TCITEM_RESULT_PEV_GO) | TCITEM_RESULT_PEV_NOGO);
				return;
			}
		}
		pItem->SetVerificationStageParameters(TCVERIFICATIONSTAGE_NONE, szParameters);
		pItem->SetResult((pItem->GetResult() & ~(TCITEM_RESULT_PEV_NOGO | TCITEM_FAILURE_PEV_TELEMETRY | TCITEM_FAILURE_PEV_CORRELATION | TCITEM_FAILURE_PEV_2NDSTEP | TCITEM_FAILURE_PEV_PARAMETERS)) | TCITEM_RESULT_PEV_GO);
		return;
	}
	if (pItem->GetSourceType() == TCITEM_SOURCETYPE_PROCEDURESMONITOR)
	{
		if ((pItem->GetFlags() & (TCITEM_CHECKFLAG_OVERRIDEPEV | TCITEM_CHECKFLAG_DISABLEPEV)) == 0 && (m_pTCProcessThread->GetCommandSourceTelecommandingChecks(pItem->GetComputerName(), pItem->GetSourceType()) & (TCSERVICE_COMMANDSOURCEFLAGS_PEV_OVERRIDE | TCSERVICE_COMMANDSOURCEFLAGS_PEV_DISABLE)) == 0)
		{
			for (pItem->SetResult(pItem->GetResult() & ~(TCITEM_FAILURE_PEV_TELEMETRY | TCITEM_FAILURE_PEV_PARAMETERS)); pItem->GetPreExeGroupRef() >= 0; )
			{
				if (!CheckPreExecutionVerificationCondition(pItem, szParameters))
				{
					pItem->SetVerificationStageParameters(TCVERIFICATIONSTAGE_NONE, szParameters);
					pItem->SetResult(pItem->GetResult() | TCITEM_FAILURE_PEV_PARAMETERS);
				}
				if (GetTMService()->CheckTMStreamInterruption()) pItem->SetResult(pItem->GetResult() | TCITEM_FAILURE_PEV_TELEMETRY);
				break;
			}
			if (pItem->GetResult() & (TCITEM_FAILURE_PEV_TELEMETRY | TCITEM_FAILURE_PEV_CORRELATION | TCITEM_FAILURE_PEV_2NDSTEP | TCITEM_FAILURE_PEV_PARAMETERS))
			{
				pItem->SetResult((pItem->GetResult() & ~TCITEM_RESULT_PEV_GO) | TCITEM_RESULT_PEV_NOGO);
				return;
			}
		}
		pItem->SetVerificationStageParameters(TCVERIFICATIONSTAGE_NONE, szParameters);
		pItem->SetResult((pItem->GetResult() & ~(TCITEM_RESULT_PEV_NOGO | TCITEM_FAILURE_PEV_TELEMETRY | TCITEM_FAILURE_PEV_CORRELATION | TCITEM_FAILURE_PEV_2NDSTEP | TCITEM_FAILURE_PEV_PARAMETERS)) | TCITEM_RESULT_PEV_GO);
		return;
	}
}
BOOL CTCProcessVerificationThread::CheckPreExecutionVerificationCondition(CONST CTCItem *pItem, CStringArray &szParameters) CONST
{
	CString  szProcedure;
	BOOL(__cdecl *pCheckThreadTCFunctionPreexecutionExpression)(INT nID, LPCTSTR pszThread, LPCTSTR pszStep, INT nEntry, CStringArray &szParameters);

#ifndef UNICODE
	szProcedure = STRING(IDS_EXPORTINTERFACE_CHECKTCPROCEDUREFUNCTIONPREEXECUTIONCONDITION);
#else
	WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_CHECKTCPROCEDUREFUNCTIONPREEXECUTIONCONDITION), -1, (LPSTR)szProcedure.GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_CHECKTCPROCEDUREFUNCTIONPREEXECUTIONCONDITION))), lstrlen(STRING(IDS_EXPORTINTERFACE_CHECKTCPROCEDUREFUNCTIONPREEXECUTIONCONDITION)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
	szProcedure.ReleaseBuffer();
#endif
	if ((pCheckThreadTCFunctionPreexecutionExpression = (BOOL(__cdecl *)(INT nID, LPCTSTR pszThread, LPCTSTR pszStep, INT nEntry, CStringArray &szParameters)) GetProcAddress(pItem->GetVerificationModule(), (LPCSTR)(LPCTSTR)szProcedure))) return (*pCheckThreadTCFunctionPreexecutionExpression)(pItem->GetVerificationProcessID(), pItem->GetVerificationThread(), pItem->GetVerificationStep(), (pItem->GetMembershipID() != (UINT)-1) ? (pItem->GetMembershipID() + 1) : -1, szParameters);
	return FALSE;
}

BOOL CTCProcessVerificationThread::CheckExecutionVerificationCondition(CONST CTCProcessEngine *pTCProcessEngine, CONST CTMEnvironment *pTMEnvironment, CONST CTCItem *pItem, UINT nStageID, CONST CTimeTag &tStageStart, CONST CTimeSpan &tUncertainty, CStringArray &szParameters) CONST
{
	return((pItem->GetSourceType() == TCITEM_SOURCETYPE_MANUALSTACK || pItem->GetSourceType() == TCITEM_SOURCETYPE_AUTOMATICSTACK) ? pTCProcessEngine->CheckTCFunctionExecutionParameterGroup(GetDatabase(), pTMEnvironment, pItem, pItem->GetExeVerGroupRef(), nStageID, tStageStart, tUncertainty, szParameters) : ((pItem->GetSourceType() == TCITEM_SOURCETYPE_PROCEDURESMONITOR) ? ((pItem->GetExeVerGroupRef() >= 0) ? CheckExecutionVerificationCondition(pItem, nStageID, tStageStart, tUncertainty, szParameters) : TRUE) : FALSE));
}
BOOL CTCProcessVerificationThread::CheckExecutionVerificationCondition(CONST CTCItem *pItem, UINT nStageID, CONST CTimeTag &tStageStart, CONST CTimeSpan &tUncertainty, CStringArray &szParameters) CONST
{
	CString  szProcedure;
	BOOL(__cdecl *pCheckThreadTCFunctionExecutionExpression)(INT nID, LPCTSTR pszThread, LPCTSTR pszStep, INT nEntry, CONST CDatabaseTCFunction *pDatabaseTCFunction, UINT nStageID, CONST CTimeTag &tStageStart, CONST CTimeSpan &tUncertainty, CStringArray &szParameters);

#ifndef UNICODE
	szProcedure = STRING(IDS_EXPORTINTERFACE_CHECKTCPROCEDUREFUNCTIONEXECUTIONCONDITION);
#else
	WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_CHECKTCPROCEDUREFUNCTIONEXECUTIONCONDITION), -1, (LPSTR)szProcedure.GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_CHECKTCPROCEDUREFUNCTIONEXECUTIONCONDITION))), lstrlen(STRING(IDS_EXPORTINTERFACE_CHECKTCPROCEDUREFUNCTIONEXECUTIONCONDITION)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
	szProcedure.ReleaseBuffer();
#endif
	if ((pCheckThreadTCFunctionExecutionExpression = (BOOL(__cdecl *)(INT nID, LPCTSTR pszThread, LPCTSTR pszStep, INT nEntry, CONST CDatabaseTCFunction *pDatabaseTCFunction, UINT nStageID, CONST CTimeTag &tStageStart, CONST CTimeSpan &tUncertainty, CStringArray &szParameters)) GetProcAddress(pItem->GetVerificationModule(), (LPCSTR)(LPCTSTR)szProcedure))) return((*pCheckThreadTCFunctionExecutionExpression)(pItem->GetVerificationProcessID(), pItem->GetVerificationThread(), pItem->GetVerificationStep(), (pItem->GetMembershipID() != (UINT)-1) ? (pItem->GetMembershipID() + 1) : -1, pItem, nStageID, tStageStart, tUncertainty, szParameters));
	return FALSE;
}

BOOL CTCProcessVerificationThread::CheckExecutionVerificationTimeWindowClosure(CONST CTMEnvironment *pTMEnvironment, CONST CTCItem *pItem, UINT nStageID) CONST
{
	INT  nStage;
	INT  nStages;
	CString  szTag;
	CUIntArray  nStageIDs;

	if (nStageID == MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_ACCEPTANCE) || nStageID == MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_START) || nStageID == MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_PROGRESS) || nStageID == MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_COMPLETION))
	{
		for (nStage = 0, nStages = pItem->EnumVerificationStageIDs(nStageIDs); nStage < nStages; nStage++)
		{
			if (MAKETCEXEVERSTAGEFROMID(nStageID) == MAKETCEXEVERSTAGEFROMID(nStageIDs.GetAt(nStage)))
			{
				if (CheckExecutionVerificationTimeWindowClosure(pTMEnvironment, pItem, nStageIDs.GetAt(nStage))) break;
				continue;
			}
		}
		return((nStage < nStages) ? TRUE : FALSE);
	}
	return(((szTag = pItem->GetVerificationStageClosure(nStageID)).IsEmpty() || pTMEnvironment->GetTMUnit()->GetTag() == szTag) ? TRUE : FALSE);
}
BOOL CTCProcessVerificationThread::CheckExecutionVerificationTimeWindowClosure(CONST CTCItem *pItem, UINT nStageID) CONST
{
	INT  nStage;
	INT  nStages;
	CUIntArray  nStageIDs;

	if (nStageID == MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_ACCEPTANCE) || nStageID == MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_START) || nStageID == MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_PROGRESS) || nStageID == MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_COMPLETION))
	{
		for (nStage = 0, nStages = pItem->EnumVerificationStageIDs(nStageIDs); nStage < nStages; nStage++)
		{
			if (MAKETCEXEVERSTAGEFROMID(nStageID) == MAKETCEXEVERSTAGEFROMID(nStageIDs.GetAt(nStage)))
			{
				if (CheckExecutionVerificationTimeWindowClosure(pItem, nStageIDs.GetAt(nStage))) break;
				continue;
			}
		}
		return((nStage < nStages) ? TRUE : FALSE);
	}
	return pItem->GetVerificationStageClosure(nStageID).IsEmpty();
}

int CTCProcessVerificationThread::Run()
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	INT  nCount;
	INT  nStage;
	INT  nStages;
	UINT  nState;
	UINT  nReason;
	BOOL  bFailure;
	BOOL  bStage[4];
	DWORD  dwTimeout;
	DWORD  dwWaitCode;
	HANDLE  hResult[2];
	CTCItem  *pItem[2];
	CTCItems  pItems;
	CTimeTag  tExecutionTime;
	CTimeTag  tVerificationTime;
	CTimeSpan  tTimeWindow[2];
	CUIntArray  nStageIDs;

	do
	{
		for (dwTimeout = INFINITE, tTimeWindow[0] = (m_pTCProcessThread->GetCommandHandlerVerificationUncertaintyTimeWindow(tTimeWindow[0])) ? tTimeWindow[0] : 0, tVerificationTime = CTimeTag(), pItems.RemoveAll(); Lock(); )
		{
			for (nItem = 0, nItems = ((m_nState & TCSERVICE_COMMANDHANDLERSTATE_RUNNING) && pItems.Copy(&m_pItems)) ? (INT)m_pItems.GetSize() : 0; nItem < nItems; nItem++)
			{
				if ((pItem[0] = m_pItems.GetAt(nItem)))
				{
					for (tTimeWindow[1] = pItem[0]->CalcVerificationTimeWindowSize(0, tTimeWindow[0]); (pItem[0]->GetResult() & (TCITEM_RESULT_CEV_IDLE | TCITEM_RESULT_CEV_PENDING | TCITEM_RESULT_CEV_PASSED | TCITEM_RESULT_CEV_FAILED | TCITEM_RESULT_CEV_UNKNOWN | TCITEM_RESULT_CEV_UNVERIFIED)) == 0; )
					{
						pItem[0]->SetResult((pItem[0]->GetType() != TCITEM_TYPE_PROCEDURE && ((pItem[0]->GetExeVerGroupRef() >= 0 && (pItem[0]->GetFlags() & (TCITEM_CHECKFLAG_OVERRIDECEV | TCITEM_CHECKFLAG_DISABLECEV)) == 0 && (m_pTCProcessThread->GetCommandSourceTelecommandingChecks(pItem[0]->GetComputerName(), pItem[0]->GetSourceType()) & (TCSERVICE_COMMANDSOURCEFLAGS_CEV_OVERRIDE | TCSERVICE_COMMANDSOURCEFLAGS_CEV_DISABLE)) == 0) || (pItem[0]->GetExecutionTime(tExecutionTime) && tExecutionTime > tVerificationTime))) ? (pItem[0]->GetResult() | TCITEM_RESULT_CEV_IDLE) : (pItem[0]->GetResult() | TCITEM_RESULT_CEV_PASSED));
						break;
					}
					if (pItem[0]->GetResult() & TCITEM_RESULT_CEV_IDLE)
					{
						if (pItem[0]->GetExecutionTime(tExecutionTime))
						{
							if (tExecutionTime <= tVerificationTime)
							{
								if (pItem[0]->GetExeVerGroupRef() < 0 || (pItem[0]->GetFlags() & (TCITEM_CHECKFLAG_OVERRIDECEV | TCITEM_CHECKFLAG_DISABLECEV)) || (m_pTCProcessThread->GetCommandSourceTelecommandingChecks(pItem[0]->GetComputerName(), pItem[0]->GetSourceType()) & (TCSERVICE_COMMANDSOURCEFLAGS_CEV_OVERRIDE | TCSERVICE_COMMANDSOURCEFLAGS_CEV_DISABLE)))
								{
									pItem[0]->SetResult((pItem[0]->GetResult() & ~TCITEM_RESULT_CEV_IDLE) | TCITEM_RESULT_CEV_PASSED);
									continue;
								}
							}
							for (dwTimeout = (tExecutionTime > tVerificationTime) ? ((dwTimeout != INFINITE) ? min((DWORD)min((tExecutionTime.GetTime() - tVerificationTime.GetTime()) / 1000, 1000 * SECONDSPERDAY), dwTimeout) : (DWORD)min((tExecutionTime.GetTime() - tVerificationTime.GetTime()) / 1000, 1000 * SECONDSPERDAY)) : dwTimeout; GetTMService()->CheckTMStreamInterruption() && pItem[0]->GetPreExeGroupRef() >= 0 && (pItem[0]->GetResult() & TCITEM_RESULT_PEV_GO) && (m_pTCProcessThread->GetCommandSourceTelecommandingChecks(pItem[0]->GetComputerName(), pItem[0]->GetSourceType()) & (TCSERVICE_COMMANDSOURCEFLAGS_PEV_OVERRIDE | TCSERVICE_COMMANDSOURCEFLAGS_PEV_DISABLE)) == 0 && (pItem[0]->GetFlags() & (TCITEM_CHECKFLAG_OVERRIDEPEV | TCITEM_CHECKFLAG_DISABLEPEV)) == 0; )
							{
								pItem[0]->SetResult((pItem[0]->GetResult() & ~TCITEM_RESULT_PEV_GO) | TCITEM_RESULT_PEV_NOGO);
								break;
							}
						}
						if (pItem[0]->GetVerificationTime() > tVerificationTime)
						{
							for (dwTimeout = (dwTimeout != INFINITE) ? min((DWORD)min((pItem[0]->GetVerificationTime().GetTime() - tVerificationTime.GetTime()) / 1000, 1000 * SECONDSPERDAY), dwTimeout) : (DWORD)min((pItem[0]->GetVerificationTime().GetTime() - tVerificationTime.GetTime()) / 1000, 1000 * SECONDSPERDAY); GetTMService()->CheckTMStreamInterruption() && pItem[0]->GetPreExeGroupRef() >= 0 && (pItem[0]->GetResult() & TCITEM_RESULT_PEV_GO) && (m_pTCProcessThread->GetCommandSourceTelecommandingChecks(pItem[0]->GetComputerName(), pItem[0]->GetSourceType()) & (TCSERVICE_COMMANDSOURCEFLAGS_PEV_OVERRIDE | TCSERVICE_COMMANDSOURCEFLAGS_PEV_DISABLE)) == 0 && (pItem[0]->GetFlags() & (TCITEM_CHECKFLAG_OVERRIDEPEV | TCITEM_CHECKFLAG_DISABLEPEV)) == 0; )
							{
								pItem[0]->SetResult((pItem[0]->GetResult() & ~TCITEM_RESULT_PEV_GO) | TCITEM_RESULT_PEV_NOGO);
								break;
							}
							continue;
						}
						if (pItem[0]->GetVerificationTime().GetTime() + 1000000 * tTimeWindow[1].GetTotalSeconds() >= tVerificationTime.GetTime())
						{
							dwTimeout = (dwTimeout != INFINITE) ? min((DWORD)min((pItem[0]->GetVerificationTime().GetTime() + 1000000 * tTimeWindow[1].GetTotalSeconds() - tVerificationTime.GetTime()) / 1000, 1000 * SECONDSPERDAY), dwTimeout) : (DWORD)min((pItem[0]->GetVerificationTime().GetTime() + 1000000 * tTimeWindow[1].GetTotalSeconds() - tVerificationTime.GetTime()) / 1000, 1000 * SECONDSPERDAY);
							pItem[0]->SetResult((pItem[0]->GetResult() & ~TCITEM_RESULT_CEV_IDLE) | TCITEM_RESULT_CEV_PENDING);
							continue;
						}
					}
					if (pItem[0]->GetResult() & TCITEM_RESULT_CEV_PENDING)
					{
						if (pItem[0]->GetVerificationTime().GetTime() + 1000000 * tTimeWindow[1].GetTotalSeconds() >= tVerificationTime.GetTime())
						{
							dwTimeout = (dwTimeout != INFINITE) ? min((DWORD)min((pItem[0]->GetVerificationTime().GetTime() + 1000000 * tTimeWindow[1].GetTotalSeconds() - tVerificationTime.GetTime()) / 1000, 1000 * SECONDSPERDAY), dwTimeout) : (DWORD)min((pItem[0]->GetVerificationTime().GetTime() + 1000000 * tTimeWindow[1].GetTotalSeconds() - tVerificationTime.GetTime()) / 1000, 1000 * SECONDSPERDAY);
							continue;
						}
					}
					if ((pItem[0]->GetResult() & (TCITEM_RESULT_CEV_IDLE | TCITEM_RESULT_CEV_PENDING)) && pItem[0]->GetVerificationTime().GetTime() + 1000000 * tTimeWindow[1].GetTotalSeconds() < tVerificationTime.GetTime())
					{
						for (nStage = 0, nStages = pItem[0]->EnumVerificationStageIDs(nStageIDs), bStage[0] = bStage[1] = bStage[2] = bStage[3] = FALSE, bFailure = FALSE; nStage < nStages; nStage++)
						{
							for (bStage[(nIndex = (MAKETCEXEVERSTAGEFROMID(nStageIDs.GetAt(nStage)) != TCVERIFICATIONSTAGE_ACCEPTANCE) ? ((MAKETCEXEVERSTAGEFROMID(nStageIDs.GetAt(nStage)) != TCVERIFICATIONSTAGE_START) ? ((MAKETCEXEVERSTAGEFROMID(nStageIDs.GetAt(nStage)) != TCVERIFICATIONSTAGE_PROGRESS) ? 3 : 2) : 1) : 0)] |= pItem[0]->GetVerificationStageState(nStageIDs.GetAt(nStage), nState, nReason); (nState == TCITEM_RESULT_CEV_IDLE || nState == TCITEM_RESULT_CEV_PENDING) && CheckExecutionVerificationTimeWindowClosure(pItem[0], MAKETCEXEVEROVERALLSTAGEID(MAKETCEXEVERSTAGEFROMID(nStageIDs.GetAt(nStage)))); )
							{
								pItem[0]->SetVerificationStageState(nStageIDs.GetAt(nStage), (nReason & TCITEM_FAILURE_CEV_PARAMETERS) ? TCITEM_RESULT_CEV_UNVERIFIED : TCITEM_RESULT_CEV_UNKNOWN, nReason);
								bFailure = (nReason & TCITEM_FAILURE_CEV_PARAMETERS) ? TRUE : bFailure;
								bStage[nIndex] = FALSE;
								break;
							}
							if (bStage[nIndex] && (nState == TCITEM_RESULT_CEV_PASSED || nState == TCITEM_RESULT_CEV_FAILED || nState == TCITEM_RESULT_CEV_UNVERIFIED))
							{
								bFailure = (nReason & TCITEM_FAILURE_CEV_PARAMETERS) ? TRUE : bFailure;
								bStage[nIndex] = FALSE;
							}
						}
						pItem[0]->SetResult((!bStage[0] && !bStage[1] && !bStage[2] && !bStage[3]) ? ((bFailure) ? ((pItem[0]->GetResult() & ~(TCITEM_RESULT_CEV_IDLE | TCITEM_RESULT_CEV_PENDING)) | TCITEM_RESULT_CEV_UNVERIFIED) : ((pItem[0]->GetResult() & ~(TCITEM_RESULT_CEV_IDLE | TCITEM_RESULT_CEV_PENDING)) | TCITEM_RESULT_CEV_UNKNOWN)) : pItem[0]->GetResult());
					}
					continue;
				}
				if ((pItem[0] = m_pItems.GetAt(nItem))) pItem[0]->SetResult((pItem[0]->GetExeVerGroupRef() < 0) ? ((pItem[0]->GetResult() & ~(TCITEM_RESULT_CEV_IDLE | TCITEM_RESULT_CEV_PENDING | TCITEM_RESULT_CEV_FAILED | TCITEM_RESULT_CEV_UNKNOWN | TCITEM_RESULT_CEV_UNVERIFIED)) | TCITEM_RESULT_CEV_PASSED) : ((pItem[0]->GetResult() & ~(TCITEM_RESULT_CEV_IDLE | TCITEM_RESULT_CEV_PENDING | TCITEM_RESULT_CEV_PASSED | TCITEM_RESULT_CEV_FAILED | TCITEM_RESULT_CEV_UNKNOWN)) | TCITEM_RESULT_CEV_UNVERIFIED));
			}
			for (nItem = 0, nCount = 0; nItem < nItems; nItem++)
			{
				if ((pItem[1] = ((pItem[0] = m_pItems.GetAt(nItem))) ? pItems.GetAt(nItem - nCount) : (CTCItem *)NULL))
				{
					if (pItem[0]->Compare(pItem[1]) && (pItem[0]->GetResult() & (TCITEM_RESULT_CEV_PASSED | TCITEM_RESULT_CEV_FAILED | TCITEM_RESULT_CEV_UNVERIFIED)) == 0)
					{
						if (pItem[0]->GetStatus() == TCITEM_STATUS_RELEASED || pItem[0]->GetStatus() == TCITEM_STATUS_EXECUTED)
						{
							pItems.RemoveAt(nItem - nCount);
							delete pItem[1];
							nCount++;
						}
						continue;
					}
					for (pItem[1]->Copy(pItem[0]); (pItem[1]->GetResult() & (TCITEM_RESULT_CEV_PASSED | TCITEM_RESULT_CEV_FAILED | TCITEM_RESULT_CEV_UNVERIFIED)) && pItem[1]->GetVerificationHandles(hResult[0], hResult[1]); )
					{
						SetEvent((pItem[1]->GetResult() & TCITEM_RESULT_CEV_PASSED) ? hResult[0] : hResult[1]);
						break;
					}
				}
			}
			Unlock();
			break;
		}
		if (pItems.GetSize() > 0)
		{
			for (Lock(), nItem = 0, nItems = (INT)m_pItems.GetSize(), m_pTCProcessThread->UpdateTelecommands(pItems, FALSE); nItem < nItems; nItem++)
			{
				if ((pItem[0] = m_pItems.GetAt(nItem)))
				{
					if (pItem[0]->GetExeVerGroupRef() >= 0)
					{
						if (pItem[0]->GetResult() & (TCITEM_RESULT_CEV_PASSED | TCITEM_RESULT_CEV_FAILED | TCITEM_RESULT_CEV_UNVERIFIED))
						{
							m_pItems.RemoveAt(nItem);
							delete pItem[0];
							nItems--;
							nItem--;
							continue;
						}
						pItem[0]->SetFlags(pItem[0]->GetFlags() & ~TCITEM_ACKNOWLEDGEFLAG_ALL);
						continue;
					}
					if (pItem[0]->GetStatus() == TCITEM_STATUS_UPLINKED || pItem[0]->GetStatus() == TCITEM_STATUS_FAILEDUPLINK || pItem[0]->GetVerificationTime().GetTimeInSeconds() + 1000000 * (pItem[0]->CalcVerificationTimeWindowOffset(0, tTimeWindow[0]).GetTotalSeconds() - pItem[0]->CalcVerificationTimeWindowOffset(0).GetTotalSeconds()) < tVerificationTime.GetTimeInSeconds())
					{
						m_pItems.RemoveAt(nItem);
						delete pItem[0];
						nItems--;
						nItem--;
						continue;
					}
					pItem[0]->SetFlags(pItem[0]->GetFlags() & ~TCITEM_ACKNOWLEDGEFLAG_ALL);
				}
			}
			Unlock();
		}
	} while ((dwWaitCode = Wait(m_bUpdate, FALSE, dwTimeout)) == WAIT_OBJECT_0 + 1 || dwWaitCode == WAIT_TIMEOUT);
	return ExitInstance();
}

BOOL CTCProcessVerificationThread::Lock()
{
	return((m_pTCProcessThread) ? (m_pTCProcessThread->Lock() && CThread::Lock()) : CThread::Lock());
}

BOOL CTCProcessVerificationThread::Unlock()
{
	return((m_pTCProcessThread) ? (CThread::Unlock() && m_pTCProcessThread->Unlock()) : CThread::Unlock());
}

BEGIN_MESSAGE_MAP(CTCProcessVerificationThread, CThread)
	//{{AFX_MSG_MAP(CTCProcessVerificationThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcessVerificationThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CTCProcessThread

IMPLEMENT_DYNCREATE(CTCProcessThread, CThread)

CTCProcessThread::CTCProcessThread() : CThread()
{
	m_pTCEnvironment = new CTCEnvironment;
	m_pTCProcessEngine = new CTCProcessEngine;
	m_pTCReleaseThread = new CTCProcessReleaseThread(this);
	m_pTCInterfaceThread = new CTCProcessInterfaceThread(this);
	m_pTCVerificationThread = new CTCProcessVerificationThread(this);
	m_pTMEnvironment = (CTMEnvironment *)NULL;
	m_pTCManualStackWnd = (CTCManualStackWnd *)NULL;
	m_pTCAutomaticStackWnd = (CTCAutomaticStackWnd *)NULL;
	m_pTCProceduresMonitorWnd = (CTCProceduresMonitorWnd *)NULL;
	m_pTCDiagnosticsOversamplingDumpWnd = (CTCDiagnosticsOversamplingDumpWnd *)NULL;
	m_pTCOnBoardBufferQueuesWnd = (CTCOnBoardBufferQueuesWnd *)NULL;
	m_pTCOnBoardMemoryImagesWnd = (CTCOnBoardMemoryImagesWnd *)NULL;
	m_pTCHistoryWnd = (CTCHistoryWnd *)NULL;
	m_nCommandUpdateTimerID = 0;
	m_nArchiveBufferTimerID = 0;
	m_bArchiveBufferFlash = FALSE;
	m_hUpdate = (HANDLE)NULL;
	m_bUpdate = FALSE;
	m_bTestMode = FALSE;
}

CTCProcessThread::~CTCProcessThread()
{
	delete m_pTCReleaseThread;
	delete m_pTCInterfaceThread;
	delete m_pTCVerificationThread;
	delete m_pTCProcessEngine;
	delete m_pTCEnvironment;
}

BOOL CTCProcessThread::Start(LPCTSTR pszName)
{
	if (m_pTCEnvironment->Create(GetDatabase()))
	{
		if (m_pTCProcessEngine->Open(GetDatabase(), pszName, m_pTCEnvironment))
		{
			if (CThread::CreateThread((LPVOID)NULL, THREAD_PRIORITY_ABOVE_NORMAL))
			{
				for (InitializeData(); m_pTCInterfaceThread->Start() && m_pTCReleaseThread->Start() && m_pTCVerificationThread->Start(); )
				{
					ReportEvent((!StartDisplay(DISPLAY_TYPE_TCMANUALSTACK)) ? SYSTEM_WARNING_TCMANUALSTACK_START_FAILURE : SYSTEM_NOERROR);
					ReportEvent((!StartDisplay(DISPLAY_TYPE_TCAUTOMATICSTACK)) ? SYSTEM_WARNING_TCAUTOMATICSTACK_START_FAILURE : SYSTEM_NOERROR);
					ReportEvent((!StartDisplay(DISPLAY_TYPE_TCPROCEDURESMONITOR)) ? SYSTEM_WARNING_TCPROCEDURESMONITOR_START_FAILURE : SYSTEM_NOERROR);
					ReportEvent((!StartDisplay(DISPLAY_TYPE_TCDIAGNOSTICSOVERSAMPLINGDUMP)) ? SYSTEM_WARNING_TCDIAGNOSTICSOVERSAMPLINGDUMP_START_FAILURE : SYSTEM_NOERROR);
					ReportEvent((!StartDisplay(DISPLAY_TYPE_TCONBOARDBUFFERQUEUES)) ? SYSTEM_WARNING_TCONBOARDBUFFERQUEUES_START_FAILURE : SYSTEM_NOERROR);
					ReportEvent((!StartDisplay(DISPLAY_TYPE_TCONBOARDMEMORYIMAGES)) ? SYSTEM_WARNING_TCONBOARDMEMORYIMAGES_START_FAILURE : SYSTEM_NOERROR);
					ReportEvent((!StartDisplay(DISPLAY_TYPE_TCHISTORY)) ? SYSTEM_WARNING_TCHISTORY_START_FAILURE : SYSTEM_NOERROR);
					Initialize();
					return TRUE;
				}
				m_pTCReleaseThread->Stop();
				m_pTCInterfaceThread->Stop();
				m_pTCVerificationThread->Stop();
				DestroyThread();
			}
			m_pTCProcessEngine->Close();
		}
		m_pTCEnvironment->Destroy();
	}
	ReportEvent(SYSTEM_WARNING_TELECOMMANDSERVICE_GENERAL_FAILURE);
	ReportEvent(SYSTEM_WARNING_TCMANUALSTACK_NOT_AVAILABLE);
	ReportEvent(SYSTEM_WARNING_TCAUTOMATICSTACK_NOT_AVAILABLE);
	ReportEvent(SYSTEM_WARNING_TCPROCEDURESMONITOR_NOT_AVAILABLE);
	ReportEvent(SYSTEM_WARNING_TCDIAGNOSTICSOVERSAMPLINGDUMP_NOT_AVAILABLE);
	ReportEvent(SYSTEM_WARNING_TCONBOARDBUFFERQUEUES_NOT_AVAILABLE);
	ReportEvent(SYSTEM_WARNING_TCONBOARDMEMORYIMAGES_NOT_AVAILABLE);
	ReportEvent(SYSTEM_WARNING_TCHISTORY_NOT_AVAILABLE);
	return FALSE;
}

BOOL CTCProcessThread::Suspend()
{
	return FALSE;
}

BOOL CTCProcessThread::IsSuspended() CONST
{
	return FALSE;
}

BOOL CTCProcessThread::Resume()
{
	return FALSE;
}

VOID CTCProcessThread::Stop()
{
	INT  nIndex;
	INT  nCount;

	for (m_pTCReleaseThread->Stop(), m_pTCVerificationThread->Stop(); !StopDisplay(DISPLAY_TYPE_TCMANUALSTACK); )
	{
		ReportEvent(SYSTEM_WARNING_TCMANUALSTACK_STOP_FAILURE);
		break;
	}
	if (!StopDisplay(DISPLAY_TYPE_TCAUTOMATICSTACK)) ReportEvent(SYSTEM_WARNING_TCAUTOMATICSTACK_STOP_FAILURE);
	if (!StopDisplay(DISPLAY_TYPE_TCPROCEDURESMONITOR)) ReportEvent(SYSTEM_WARNING_TCPROCEDURESMONITOR_STOP_FAILURE);
	if (!StopDisplay(DISPLAY_TYPE_TCDIAGNOSTICSOVERSAMPLINGDUMP)) ReportEvent(SYSTEM_WARNING_TCDIAGNOSTICSOVERSAMPLINGDUMP_STOP_FAILURE);
	if (!StopDisplay(DISPLAY_TYPE_TCONBOARDBUFFERQUEUES)) ReportEvent(SYSTEM_WARNING_TCONBOARDBUFFERQUEUES_STOP_FAILURE);
	if (!StopDisplay(DISPLAY_TYPE_TCONBOARDMEMORYIMAGES)) ReportEvent(SYSTEM_WARNING_TCONBOARDMEMORYIMAGES_STOP_FAILURE);
	if (!StopDisplay(DISPLAY_TYPE_TCHISTORY)) ReportEvent(SYSTEM_WARNING_TCHISTORY_STOP_FAILURE);
	for (Lock(), nIndex = 0, nCount = (INT)m_nTCModuleIDs.GetSize(); nIndex < nCount; nIndex++)
	{
		m_pTCEnvironment->FreeTCProcedure(m_nTCModuleIDs.GetAt(nIndex));
		m_nTCModuleIDs.RemoveAt(nIndex);
		m_pTCModules.RemoveAt(nIndex);
		nIndex--;
		nCount--;
	}
	if (m_nCommandUpdateTimerID != 0)
	{
		KillTimer((HWND)NULL, m_nCommandUpdateTimerID);
		m_nCommandUpdateTimerID = 0;
	}
	if (m_nArchiveBufferTimerID != 0)
	{
		KillTimer((HWND)NULL, m_nArchiveBufferTimerID);
		m_nArchiveBufferTimerID = 0;
	}
	for (Uninitialize(), Unlock(), m_pTCInterfaceThread->Stop(); Lock(); )
	{
		m_pTCEnvironment->Destroy();
		m_pTCProcessEngine->Close();
		Unlock();
		break;
	}
	DestroyThread();
}

BOOL CTCProcessThread::Initialize(CTMEnvironment *pTMEnvironment)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	m_pTMEnvironment = pTMEnvironment;
	m_pTCDevices.EnumDevices();
	return TRUE;
}
BOOL CTCProcessThread::Initialize(CTCParameters &pTCParameters)
{
	return m_pTCEnvironment->Initialize(pTCParameters);
}
BOOL CTCProcessThread::Initialize(CONST CTCItem *pItem, CTCEnvironment *pTCEnvironment)
{
	CTCUnit  *pTCUnit;
	CTimeTag  tTimeTag;
	CTCPacket  cTCPacket;
	CByteArray  nData[3];
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (pItem->Map(nData[0], TRUE))
	{
		if ((pTCUnit = pTCEnvironment->GetTCUnit()))
		{
			if (pItem->GetTCPacket(nData[1]) > 0 && cTCPacket.Unmap(nData[1]))
			{
				pTCUnit->SetTag(cTCPacket.GetTag());
				pTCUnit->SetTimeTag(tTimeTag.GetTime());
				pTCUnit->SetData(nData[0], TRUE);
				pTCUnit->SetData(nData[1], FALSE);
				return TRUE;
			}
			pTCUnit->SetTag(SPACE);
			pTCUnit->SetTimeTag(tTimeTag.GetTime());
			pTCUnit->SetData(nData[0], TRUE);
			pTCUnit->SetData(nData[2], FALSE);
			return TRUE;
		}
	}
	return FALSE;
}
BOOL CTCProcessThread::Initialize(CONST CTCEnvironment *pTCEnvironment, CTCItem *pItem)
{
	CByteArray  nData[2];
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (pTCEnvironment->GetTCUnit()->GetData(nData[0], TRUE), pTCEnvironment->GetTCUnit()->GetData(nData[1], FALSE); pItem->Unmap(nData[0], TRUE); )
	{
		pItem->SetTCPacket(nData[1]);
		return TRUE;
	}
	return FALSE;
}

VOID CTCProcessThread::Update(CONST CTMProcessEngine *pTMProcessEngine, CONST CTMEnvironment *pTMEnvironment)
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	INT  nCount;
	INT  nQueue;
	INT  nQueues;
	INT  nParameter;
	INT  nParameters;
	INT  cbQueuedSize;
	UINT  nSubScheduleID;
	UINT  nStageID;
	UINT  nOBRT;
	CString  szName;
	CString  szType;
	CTimeTag  tOBRT;
	CTCItem  *pItem[2];
	CTCItems  pItems[3];
	CTimeTag  tLoadTime;
	CTimeTag  tUpdateTime;
	CTimeTag  tExecutionTime[2];
	CTimeSpan  tStageTimeWindow[3];
	CTCPacket  cTCPacket[2];
	CPtrArray  pQueues;
	CUIntArray  nCounts;
	CUIntArray  nStatus;
	CUIntArray  nSubScheduleIDs;
	CByteArray  nPacketData[2];
	CStringArray  szTypes;
	CStringArray  szNames;
	CTCInterlocks  pInterlocks;
	CTimeTagArray  tUpdateTimes;
	CDatabaseTCPacket  cPacket;
	CDatabaseTCFunction  cFunction;
	CDatabaseTCFunctions  pBlockedItems;
	CTCOnBoardBufferQueue  *pQueue;
	CDatabaseTCExeVerGroup  *pGroup;
	CDatabaseTCExeVerGroupParameter  *pGroupParameter;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (UpdateCommandLinkControlWord(pTMProcessEngine->GetCommandLinkControlWord()); pTMProcessEngine->GetTimeCorrelation(pTMEnvironment, tOBRT, nOBRT); )
	{
		m_pTCProcessEngine->SetTimeCorrelation(m_pTCEnvironment, tOBRT, nOBRT);
		break;
	}
	if (IsCommandHandler())
	{
		for (nItem = 0, nItems = (INT)m_nTCModuleIDs.GetSize(); nItem < nItems; nItem++)
		{
			Update((HINSTANCE)m_pTCModules.GetAt(nItem), m_nTCModuleIDs.GetAt(nItem), pTMEnvironment);
			continue;
		}
		for (m_pTCReleaseThread->Update(m_pTCProcessEngine, m_pTCEnvironment, pTMEnvironment, m_pTCInterlocks, pItems[0]), m_pTCVerificationThread->Update(m_pTCProcessEngine, m_pTCEnvironment, pTMEnvironment, m_pTCInterlocks, pItems[1], pInterlocks), m_pTCReleaseThread->Update(m_pTCInterlocks, pItems[2]), m_pTCInterfaceThread->Update(pItems[0], pItems[1], pItems[2], pInterlocks); m_pTCManualStackWnd; )
		{
			m_pTCManualStackWnd->UpdateTelecommands(pTMEnvironment);
			break;
		}
		if (m_pTCAutomaticStackWnd) m_pTCAutomaticStackWnd->UpdateTelecommands(pTMEnvironment);
	}
	for (; m_pTCProceduresMonitorWnd; )
	{
		m_pTCProceduresMonitorWnd->UpdateMonitoring(pTMEnvironment);
		break;
	}
	for (nItem = 0, nItems = (INT)pItems[1].GetSize(); nItem < nItems; nItem++)
	{
		if ((pQueue = ((pItem[0] = pItems[1].GetAt(nItem)) && pItem[0]->GetTCPacket(nPacketData[0]) > 0 && cTCPacket[0].Unmap(nPacketData[0]) && FindTCOnBoardBufferQueue(&cTCPacket[0], szType, szName, nSubScheduleID)) ? m_pTCOnBoardBufferQueues.GetAt(m_pTCOnBoardBufferQueues.Find(szType, szName, nSubScheduleID)) : (CTCOnBoardBufferQueue *)NULL))
		{
			if ((pItem[1] = pQueue->GetAt(pQueue->Find(pItem[0]))) != (CTCItem *)NULL)
			{
				for (cbQueuedSize = pItem[1]->GetQueuedSize(); pItem[1]->Copy(pItem[0]); )
				{
					pItem[1]->SetQueuedSize(cbQueuedSize);
					break;
				}
				pQueues.Add(pQueue);
			}
		}
	}
	for (nQueue = 0, nQueues = m_pTCProcessEngine->UpdateTCOnBoardBufferQueues(GetDatabase(), pTMEnvironment, szTypes, szNames, nSubScheduleIDs, nCounts, tUpdateTimes, nStatus); nQueue < nQueues; nQueue++)
	{
		if ((pQueue = m_pTCOnBoardBufferQueues.GetAt(m_pTCOnBoardBufferQueues.Find(szTypes.GetAt(nQueue), szNames.GetAt(nQueue), nSubScheduleIDs.GetAt(nQueue)))) != (CTCOnBoardBufferQueue *)NULL)
		{
			for (nItem = 0, nItems = (INT)pQueue->GetSize(), pQueue->SetCount((nCounts.GetAt(nQueue) != (UINT)-1) ? nCounts.GetAt(nQueue) : pQueue->GetCount()), pQueue->SetUpdateTime((nCounts.GetAt(nQueue) != (UINT)-1 && nStatus.GetAt(nQueue) != (UINT)-1) ? tUpdateTimes.GetAt(nQueue) : pQueue->GetUpdateTime()), pQueue->SetStatus((nStatus.GetAt(nQueue) != (UINT)-1) ? ((nStatus.GetAt(nQueue)) ? TCONBOARDBUFFERQUEUE_STATUS_ENABLED : TCONBOARDBUFFERQUEUE_STATUS_DISABLED) : pQueue->GetStatus()), nCount = 0; nItem < nItems; nItem++)
			{
				if ((pItem[0] = pQueue->GetAt(nItem)))
				{
					nCount += pItem[0]->GetQueuedSize();
					continue;
				}
			}
			for (; (pQueue->GetCount() != (UINT)-1 || nCount > 0) && pQueue->GetCount() != nCount; )
			{
				pQueue->Alert(TCONBOARDBUFFERQUEUE_ALERTTYPE_WARNING, 0, STRING(IDS_TELECOMMANDONBOARDBUFFERQUEUE_MESSAGE_SYNCHRONIZATIONWARNING));
				break;
			}
			pQueues.Add(pQueue);
		}
	}
	if ((pQueue = (m_pTCProcessEngine->DecodeTCOnBoardBufferQueueDump(GetDatabase(), pTMEnvironment, szType, szName, nSubScheduleID, &cTCPacket[0])) ? m_pTCOnBoardBufferQueues.GetAt(m_pTCOnBoardBufferQueues.Find(szType, szName, nSubScheduleID)) : (CTCOnBoardBufferQueue *)NULL))
	{
		for (nItem = 0, nItems = (INT)pQueue->GetSize(), pItems[0].RemoveAll(); nItem < nItems; nItem++)
		{
			if ((pItem[0] = pQueue->GetAt(nItem)) && pItem[0]->GetTCPacket(nPacketData[0]) > 0)
			{
				if (cTCPacket[1].Unmap(nPacketData[0]) && cTCPacket[0].Compare(&cTCPacket[1]))
				{
					pItem[0]->SetFlags(pItem[0]->GetFlags() | TCITEM_DUMPFLAG_SYNCHRONIZED);
					pItem[0]->SetDumpTime(pTMEnvironment->GetTMUnit()->GetTimeTag());
					break;
				}
			}
		}
		for (; nItem == nItems; )
		{
			if ((pItem[0] = new CTCItem))
			{
				if (m_pTCProcessEngine->DecodeTCOnBoardBufferQueueDump(GetDatabase(), pTMEnvironment, m_pTCEnvironment, &cTCPacket[0], &cFunction, pBlockedItems, &cPacket, tExecutionTime[0]))
				{
					if (pItem[0]->CDatabaseTCFunction::Copy(&cFunction) && pItem[0]->SetReleaseBlockedItems(pBlockedItems) && pItem[0]->SetTCPacket(&cPacket))
					{
						if (cFunction.GetAttributes() & TCFUNCTION_EXETYPE_IMMEDIATE)
						{
							pItem[0]->SetFlags(TCITEM_EXECUTIONFLAG_IMMEDIATE);
							pItem[0]->SetExecutionTime(0);
						}
						if (cFunction.GetAttributes() & TCFUNCTION_EXETYPE_TIMETAG)
						{
							pItem[0]->SetFlags(TCITEM_EXECUTIONFLAG_TIMETAGGED);
							pItem[0]->SetExecutionTime(tExecutionTime[0]);
						}
						if (cFunction.GetAttributes() & (TCFUNCTION_EXETYPE_FIRSTSTEP | TCFUNCTION_EXETYPE_SECONDSTEP))
						{
							pItem[0]->SetFlags((cFunction.GetAttributes() & TCFUNCTION_EXETYPE_FIRSTSTEP) ? TCITEM_EXECUTIONFLAG_1STSTEP : TCITEM_EXECUTIONFLAG_2NDSTEP);
							pItem[0]->SetExecutionTime(0);
						}
						for (pItem[0]->SetName(cFunction.GetName()), pItem[0]->SetSourceType(TCITEM_SOURCETYPE_ALLSOURCES), pItem[0]->SetType(TCITEM_TYPE_FUNCTION), pItem[0]->SetFlags((pBlockedItems.GetSize() > 0) ? (pItem[0]->GetFlags() | TCITEM_LINKAGEFLAG_BLOCKED | TCITEM_DUMPFLAG_NOTSYNCHRONIZED) : (pItem[0]->GetFlags() | TCITEM_DUMPFLAG_NOTSYNCHRONIZED)), pItem[0]->SetReleaseBlockID((pItem[0]->GetFlags() & TCITEM_LINKAGEFLAG_BLOCKED) ? 0 : -1), cTCPacket[0].Map(nPacketData[0]), pItem[0]->SetTCPacket(nPacketData[0]), pItem[0]->SetQueuedSize(m_pTCProcessEngine->CalculateTCOnBoardBufferQueueEntry(&cTCPacket[0])), pItem[0]->SetLoadTime(tLoadTime), pItem[0]->SetDumpTime(pTMEnvironment->GetTMUnit()->GetTimeTag()), pItem[0]->SetVerificationTime(tExecutionTime[0]), pItem[0]->SetResult(TCITEM_RESULT_PTV_GO | TCITEM_RESULT_PEV_GO | TCITEM_RESULT_CEV_IDLE), pItem[0]->SetStatus(TCITEM_STATUS_RELEASED), pQueue->SetCount((pQueue->GetCount() != (UINT)-1) ? (pQueue->GetCount() + pItem[0]->GetQueuedSize()) : pItem[0]->GetQueuedSize()); (pGroup = GetDatabase()->GetTCExeVerGroups()->GetAt(pItem[0]->GetExeVerGroupRef())); )
						{
							for (nParameter = 0, nParameters = (INT)pGroup->GetSize(); nParameter < nParameters; nParameter++)
							{
								if ((pGroupParameter = pGroup->GetAt(nParameter)) != (CDatabaseTCExeVerGroupParameter *)NULL)
								{
									if (!pItem[0]->GetVerificationTimeWindow((nStageID = MAKETCEXEVERSTAGEID(pGroupParameter->GetStage(), pGroupParameter->GetStep())), tStageTimeWindow[0], tStageTimeWindow[1], tStageTimeWindow[2]))
									{
										pItem[0]->SetVerificationTimeWindow(nStageID, pGroupParameter->GetTimeWindowOffset(), pGroupParameter->GetTimeWindowInterval(), pGroupParameter->GetTimeWindowUncertainty());
										continue;
									}
									pItem[0]->SetVerificationTimeWindow(nStageID, min(pGroupParameter->GetTimeWindowOffset(), tStageTimeWindow[0]), max(pGroupParameter->GetTimeWindowInterval(), tStageTimeWindow[1]), max(pGroupParameter->GetTimeWindowUncertainty(), tStageTimeWindow[2]));
								}
							}
							break;
						}
						for (nItem = 0; nItem < nItems; nItem++)
						{
							if ((pItem[1] = pQueue->GetAt(nItem)))
							{
								if (!pItem[1]->GetExecutionTime(tExecutionTime[1]) || tExecutionTime[0] > tExecutionTime[1]) break;
								continue;
							}
						}
						for (pQueue->InsertAt(nItem, pItem[0], 1); (pItem[1] = (IsCommandHandler()) ? new CTCItem : (CTCItem *)NULL); )
						{
							if (pItem[1]->Copy(pItem[0]) && pItems[0].Add(pItem[1]) >= 0)
							{
								m_pTCVerificationThread->Update(pItems[0]);
								break;
							}
							delete pItem[1];
							break;
						}
						break;
					}
				}
				delete pItem[0];
			}
			pQueue->Alert(TCONBOARDBUFFERQUEUE_ALERTTYPE_ERROR, 0, STRING(IDS_TELECOMMANDONBOARDBUFFERQUEUE_MESSAGE_SYNCHRONIZATIONFAILURE));
			break;
		}
		pQueues.Add(pQueue);
	}
	for (nQueue = 0, nQueues = (m_pTCProcessEngine->Get1stStepTCData(pTMEnvironment, nPacketData[0])) ? (INT)m_pTCOnBoardBufferQueues.GetSize() : 0; nQueue < nQueues; nQueue++)
	{
		if ((pQueue = m_pTCOnBoardBufferQueues.GetAt(nQueue)) && pQueue->GetTimeout() > 0)
		{
			for (nItem = 0, nItems = (INT)pQueue->GetSize(); nItem < nItems; nItem++)
			{
				if ((pItem[0] = pQueue->GetAt(nItem)) && (pItem[0]->GetFlags() & TCITEM_EXECUTIONFLAG_1STSTEP))
				{
					if (pItem[0]->GetTCPacket(nPacketData[1]) && cTCPacket[0].Unmap(nPacketData[1]) && cTCPacket[0].GetData(nPacketData[1]) == nPacketData[0].GetSize() && !memcmp(nPacketData[0].GetData(), nPacketData[1].GetData(), nPacketData[0].GetSize()))
					{
						pQueue->SetCount((pItem[0]->GetQueuedSize() <= pQueue->GetCount()) ? (pQueue->GetCount() - pItem[0]->GetQueuedSize()) : 0);
						pQueue->SetUpdateTime(tUpdateTime);
						pQueue->RemoveAt(nItem);
						pQueues.Add(pQueue);
						delete pItem[0];
						break;
					}
				}
			}
		}
	}
	for (nQueue = 0, nQueues = (INT)pQueues.GetSize(); nQueue < nQueues; nQueue++)
	{
		for (nIndex = nQueue + 1, nCount = nQueues; nIndex < nCount; nIndex++)
		{
			if (pQueues.GetAt(nQueue) == pQueues.GetAt(nIndex))
			{
				pQueues.RemoveAt(nIndex);
				nQueues--;
				nIndex--;
				nCount--;
			}
		}
	}
	for (UpdateQueues(pQueues); m_pTCOnBoardMemoryImagesWnd; )
	{
		m_pTCOnBoardMemoryImagesWnd->UpdateMonitoring(pTMEnvironment);
		break;
	}
}
VOID CTCProcessThread::Update(INT nDataID, UINT nStatus, BOOL bSuccess)
{
	INT  nID;
	INT  nIDs;
	INT  nInterlock;
	INT  nInterlocks;
	CUIntArray  nReleaseIDs;
	CTCInterlock  *pInterlock;
	CTCInterlocks  pInterlocks;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nInterlock = 0, nInterlocks = (INT)m_pTCInterlocks.GetSize(); nInterlock < nInterlocks; nInterlock++)
	{
		if ((pInterlock = m_pTCInterlocks.GetAt(nInterlock)) && ((pInterlock->GetStage() == TCINTERLOCK_STAGE_RECEPTION && (nStatus & (IODEVICE_DATASTATUS_SENT | IODEVICE_DATASTATUS_PROCESSED)) == IODEVICE_DATASTATUS_SENT) || (pInterlock->GetStage() == TCINTERLOCK_STAGE_TRANSMISSION && (nStatus & (IODEVICE_DATASTATUS_SENT | IODEVICE_DATASTATUS_PROCESSED)) == IODEVICE_DATASTATUS_PROCESSED)))
		{
			for (nID = 0, nIDs = pInterlock->GetReleaseIDs(nReleaseIDs); nID < nIDs; nID++)
			{
				if (nDataID == nReleaseIDs.GetAt(nID)) break;
				continue;
			}
			if (nID < nIDs)
			{
				for (nReleaseIDs.RemoveAt(nID); !nReleaseIDs.GetSize(); )
				{
					pInterlock->SetState((bSuccess) ? TCINTERLOCK_STATE_SUCCESS : TCINTERLOCK_STATE_FAILURE);
					break;
				}
				pInterlock->SetReleaseIDs(nReleaseIDs);
			}
		}
	}
	if (pInterlocks.Copy(&m_pTCInterlocks)) UpdateTCInterlocks(pInterlocks);
	m_pTCVerificationThread->Update(nDataID, nStatus, bSuccess);
}
VOID CTCProcessThread::Update(LPCTSTR pszEvent)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (m_pTCInterfaceThread->Update(pszEvent); IsCommandHandler(); )
	{
		m_pTCReleaseThread->Update();
		break;
	}
	if (m_pTCManualStackWnd) m_pTCManualStackWnd->UpdateTelecommanding(pszEvent);
	if (m_pTCAutomaticStackWnd) m_pTCAutomaticStackWnd->UpdateTelecommanding(pszEvent);
	if (m_pTCProceduresMonitorWnd) m_pTCProceduresMonitorWnd->UpdateMonitoring(pszEvent);
}
BOOL CTCProcessThread::Update()
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (m_cCommandUpdateEvent.SetEvent(); m_pTCReleaseThread; )
	{
		m_pTCReleaseThread->Update();
		break;
	}
	if (m_pTCVerificationThread) m_pTCVerificationThread->Update();
	return m_cUpdate[0].SetEvent();
}

INT CTCProcessThread::EnumTCSubSystems(CStringArray &szSubSystems, BOOL bAll) CONST
{
	return m_pTCProcessEngine->EnumSubSystems(szSubSystems, bAll);
}

UINT CTCProcessThread::TranslateTCSubSystemToID(LPCTSTR pszSubSystem) CONST
{
	return m_pTCProcessEngine->TranslateSubSystemToID(pszSubSystem);
}

CString CTCProcessThread::TranslateIDToTCSubSystem(UINT nSubSystemID) CONST
{
	return m_pTCProcessEngine->TranslateIDToSubSystem(nSubSystemID);
}

BOOL CTCProcessThread::SetTCUplinkDevices(CONST CTCUplinkDevices &pDevices)
{
	CTCUplinkDevice  cDevice[2];
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (m_pTCDevices.Copy(&pDevices))
	{
		for (m_pTCDevices.EnumDevices(), GetDevice(&cDevice[0]), m_pTCDevices.GetActiveDevice(&cDevice[1]); cDevice[0].GetDeviceBrand() == cDevice[1].GetDeviceBrand() && cDevice[0].GetDeviceName() == cDevice[1].GetDeviceName(); )
		{
			UpdateTelecommandStatus();
			break;
		}
		return Update();
	}
	return FALSE;
}

INT CTCProcessThread::GetTCUplinkDevices(CTCUplinkDevices &pDevices) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return pDevices.Copy(&m_pTCDevices);
}

BOOL CTCProcessThread::HasTCUplinkDevices(BOOL bSupported) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_pTCDevices.HasAvailableDevices(bSupported);
}

BOOL CTCProcessThread::SetActiveTCUplinkDevice(CONST CTCUplinkDevice *pDevice)
{
	CTCItems  pItems;
	CTCUplinkDevice  cDevice;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (m_pTCDevices.SetActiveDevice(pDevice))
	{
		for (GetDevice(&cDevice); pDevice->GetDeviceBrand() == cDevice.GetDeviceBrand() && pDevice->GetDeviceName() == cDevice.GetDeviceName(); )
		{
			for (UpdateTelecommandStatus(pDevice); IsCommandHandler(); )
			{
				for (m_pTCReleaseThread->Update(pDevice->GetCommandHandlerState(), pItems); pItems.GetSize() > 0; )
				{
					m_pTCInterfaceThread->UpdateTelecommands(pItems, FALSE);
					break;
				}
				break;
			}
			if (m_pTCManualStackWnd) m_pTCManualStackWnd->SetTelecommandingUplinkState(pDevice->GetCommandHandlerState());
			if (m_pTCAutomaticStackWnd) m_pTCAutomaticStackWnd->SetTelecommandingUplinkState(pDevice->GetCommandHandlerState());
			if (m_pTCProceduresMonitorWnd) m_pTCProceduresMonitorWnd->SetTelecommandingUplinkState(pDevice->GetCommandHandlerState());
			break;
		}
		return Update();
	}
	return FALSE;
}

BOOL CTCProcessThread::GetActiveTCUplinkDevice(CTCUplinkDevice *pDevice) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_pTCDevices.GetActiveDevice(pDevice);
}

BOOL CTCProcessThread::StopActiveTCUplinkDevice(HANDLE hDevice)
{
	for (m_cUpdate[1].ResetEvent(), m_hUpdate = hDevice, m_bUpdate = TRUE; Update(); )
	{
		Wait(m_cUpdate[1], FALSE);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcessThread::UpdateTCDisplays(BOOL bProcessData)
{
	BOOL  bUpdate;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	bUpdate = (bProcessData) ? StartDisplay(DISPLAY_TYPE_TCMANUALSTACK, FALSE) : StopDisplay(DISPLAY_TYPE_TCMANUALSTACK);
	bUpdate &= (bProcessData) ? StartDisplay(DISPLAY_TYPE_TCAUTOMATICSTACK, FALSE) : StopDisplay(DISPLAY_TYPE_TCAUTOMATICSTACK);
	bUpdate &= (bProcessData) ? StartDisplay(DISPLAY_TYPE_TCPROCEDURESMONITOR, FALSE) : StopDisplay(DISPLAY_TYPE_TCPROCEDURESMONITOR);
	bUpdate &= (bProcessData) ? StartDisplay(DISPLAY_TYPE_TCDIAGNOSTICSOVERSAMPLINGDUMP, FALSE) : StopDisplay(DISPLAY_TYPE_TCDIAGNOSTICSOVERSAMPLINGDUMP);
	bUpdate &= (bProcessData) ? StartDisplay(DISPLAY_TYPE_TCONBOARDBUFFERQUEUES, FALSE) : StopDisplay(DISPLAY_TYPE_TCONBOARDBUFFERQUEUES);
	bUpdate &= (bProcessData) ? StartDisplay(DISPLAY_TYPE_TCONBOARDMEMORYIMAGES, FALSE) : StopDisplay(DISPLAY_TYPE_TCONBOARDMEMORYIMAGES);
	bUpdate &= (bProcessData) ? StartDisplay(DISPLAY_TYPE_TCHISTORY, FALSE) : StopDisplay(DISPLAY_TYPE_TCHISTORY);
	return bUpdate;
}

BOOL CTCProcessThread::UpdateTCParameters(CONST CTCParameters &pTCParameters)
{
	INT  nParameter;
	INT  nParameters;
	CTCParameter  *pTCParameter[2];

	if (m_pTCEnvironment->Lock())
	{
		for (nParameter = 0, nParameters = (INT)pTCParameters.GetSize(); nParameter < nParameters; nParameter++)
		{
			if ((pTCParameter[1] = ((pTCParameter[0] = pTCParameters.GetAt(nParameter))) ? m_pTCEnvironment->GetTCParameters()->GetAt(m_pTCEnvironment->GetTCParameters()->Find(pTCParameter[0]->GetTag())) : (CTCParameter *)NULL))
			{
				pTCParameter[1]->Update(pTCParameter[0]);
				continue;
			}
		}
		m_pTCEnvironment->Unlock();
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcessThread::ResetTCParameters()
{
	if (m_pTCEnvironment->Lock())
	{
		m_pTCEnvironment->GetTCParameters()->Reset();
		m_pTCEnvironment->Unlock();
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcessThread::SetCommandHandlerConfiguration(LPCTSTR pszPreferredCommandHandler, LPCTSTR pszBackupCommandHandler, BOOL bSelfCommandHandler, BOOL bAnyCommandHandler, BOOL bExclusiveCommandHandler, UINT nCommandHandlerOptions, UINT nCommandHandlerPort, UINT nCommandHandlerBufferSize, CONST CTimeSpan &tCommandHandlerTimeout, CONST CStringArray &szCommandHandlerClients, CONST CUIntArray &nCommandHandlerAccessCodes, CONST CTimeKeyArray &tCommandHandlerStartTimes, CONST CTimeKeyArray &tCommandHandlerStopTimes)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_pTCInterfaceThread->SetCommandHandlerConfiguration(pszPreferredCommandHandler, pszBackupCommandHandler, bSelfCommandHandler, bAnyCommandHandler, bExclusiveCommandHandler, nCommandHandlerOptions, nCommandHandlerPort, nCommandHandlerBufferSize, tCommandHandlerTimeout, szCommandHandlerClients, nCommandHandlerAccessCodes, tCommandHandlerStartTimes, tCommandHandlerStopTimes);
}
BOOL CTCProcessThread::SetCommandHandlerConfiguration(UINT nTelecommandingMode, UINT nTelecommandingState, UINT nTelecommandingFlags, BOOL bTelecommandingInterlockMode, BOOL bTelecommandingReleaseWaitMode, BOOL bTelecommandingAutoRejectionMode, CONST CTimeSpan &tVerificationUncertaintyTimeWindow, CONST CTimeSpan &tMaximumExecutionTimePeriod, CONST CTimeSpan &tMaximumTimeCheckPeriod, CONST CTimeSpan &tDefaultReleaseTimeWindow, CONST CHistoryStoreFiles &pHistoryArchivalFiles, CONST CHistoryStoreFiles &pHistoryRetrievalFiles, LPCTSTR pszDefaultHistoryFileName)
{
	CTimeSpan  tTimeOffset[2][2];
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (m_pTCInterfaceThread->SetCommandHandlerConfiguration(nTelecommandingMode, nTelecommandingState, nTelecommandingFlags, bTelecommandingInterlockMode, bTelecommandingReleaseWaitMode, bTelecommandingAutoRejectionMode, tVerificationUncertaintyTimeWindow, tDefaultReleaseTimeWindow, pHistoryArchivalFiles, pHistoryRetrievalFiles, pszDefaultHistoryFileName))
	{
		if (GetTCFunctionExecutionTimeOffsets(tTimeOffset[0][0], tTimeOffset[0][1])) SetTCFunctionExecutionTimeOffsets(tTimeOffset[0][0], tMaximumExecutionTimePeriod);
		if (GetTCFunctionParameterTimeOffsets(tTimeOffset[1][0], tTimeOffset[1][1])) SetTCFunctionParameterTimeOffsets(tTimeOffset[1][0], tMaximumTimeCheckPeriod);
		return TRUE;
	}
	return FALSE;
}
BOOL CTCProcessThread::SetCommandHandlerConfiguration(CONST CTCProcessCommandSources &pCommandSources, UINT nTelecommandingMode, UINT nTelecommandingState, UINT nTelecommandingFlags, BOOL bTelecommandingInterlockMode, BOOL bTelecommandingReleaseWaitMode, BOOL bTelecommandingAutoRejectionMode, CONST CTimeSpan &tVerificationUncertaintyTimeWindow, CONST CTimeSpan &tMaximumExecutionTimePeriod, CONST CTimeSpan &tMaximumTimeCheckPeriod, CONST CTimeSpan &tDefaultReleaseTimeWindow, CONST CHistoryStoreFiles &pHistoryArchivalFiles, CONST CHistoryStoreFiles &pHistoryRetrievalFiles, LPCTSTR pszDefaultHistoryFileName, BOOL bUpdate)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_pTCInterfaceThread->SetCommandHandlerConfiguration(pCommandSources, nTelecommandingMode, nTelecommandingState, nTelecommandingFlags, bTelecommandingInterlockMode, bTelecommandingReleaseWaitMode, bTelecommandingAutoRejectionMode, tVerificationUncertaintyTimeWindow, tMaximumExecutionTimePeriod, tMaximumTimeCheckPeriod, tDefaultReleaseTimeWindow, pHistoryArchivalFiles, pHistoryRetrievalFiles, pszDefaultHistoryFileName, bUpdate);
}

BOOL CTCProcessThread::GetCommandHandlerConfiguration(CString &szPreferredCommandHandler, CString &szBackupCommandHandler, BOOL &bSelfCommandHandler, BOOL &bAnyCommandHandler, BOOL &bExclusiveCommandHandler, UINT &nCommandHandlerOptions, UINT &nCommandHandlerPort, UINT &nCommandHandlerBufferSize, CTimeSpan &tCommandHandlerTimeout, CStringArray &szCommandHandlerClients, CUIntArray &nCommandHandlerAccessCodes, CTimeKeyArray &tCommandHandlerStartTimes, CTimeKeyArray &tCommandHandlerStopTimes) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_pTCInterfaceThread->GetCommandHandlerConfiguration(szPreferredCommandHandler, szBackupCommandHandler, bSelfCommandHandler, bAnyCommandHandler, bExclusiveCommandHandler, nCommandHandlerOptions, nCommandHandlerPort, nCommandHandlerBufferSize, tCommandHandlerTimeout, szCommandHandlerClients, nCommandHandlerAccessCodes, tCommandHandlerStartTimes, tCommandHandlerStopTimes);
}
BOOL CTCProcessThread::GetCommandHandlerConfiguration(UINT &nTelecommandingMode, UINT &nTelecommandingState, UINT &nTelecommandingFlags, BOOL &bTelecommandingInterlockMode, BOOL &bTelecommandingReleaseWaitMode, BOOL &bTelecommandingAutoRejectionMode, CTimeSpan &tVerificationUncertaintyTimeWindow, CTimeSpan &tMaximumExecutionTimePeriod, CTimeSpan &tMaximumTimeCheckPeriod, CTimeSpan &tDefaultReleaseTimeWindow, CHistoryStoreFiles &pHistoryArchivalFiles, CHistoryStoreFiles &pHistoryRetrievalFiles, CString &szDefaultHistoryFileName) CONST
{
	CTimeSpan  tTimeOffset[2][2];
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (m_pTCInterfaceThread->GetCommandHandlerConfiguration(nTelecommandingMode, nTelecommandingState, nTelecommandingFlags, bTelecommandingInterlockMode, bTelecommandingReleaseWaitMode, bTelecommandingAutoRejectionMode, tVerificationUncertaintyTimeWindow, tDefaultReleaseTimeWindow, pHistoryArchivalFiles, pHistoryRetrievalFiles, szDefaultHistoryFileName))
	{
		for (tMaximumExecutionTimePeriod = 0; GetTCFunctionExecutionTimeOffsets(tTimeOffset[0][0], tTimeOffset[0][1]); )
		{
			tMaximumExecutionTimePeriod = tTimeOffset[0][1];
			break;
		}
		for (tMaximumTimeCheckPeriod = 0; GetTCFunctionParameterTimeOffsets(tTimeOffset[1][0], tTimeOffset[1][1]); )
		{
			tMaximumTimeCheckPeriod = tTimeOffset[1][1];
			break;
		}
		return TRUE;
	}
	return FALSE;
}
BOOL CTCProcessThread::GetCommandHandlerConfiguration(CTCProcessCommandSources &pCommandSources, UINT &nTelecommandingMode, UINT &nTelecommandingState, UINT &nTelecommandingFlags, BOOL &bTelecommandingInterlockMode, BOOL &bTelecommandingReleaseWaitMode, BOOL &bTelecommandingAutoRejectionMode, CTimeSpan &tVerificationUncertaintyTimeWindow, CTimeSpan &tMaximumExecutionTimePeriod, CTimeSpan &tMaximumTimeCheckPeriod, CTimeSpan &tDefaultReleaseTimeWindow, CTCItems &pItems, CTCInterlocks &pInterlocks, CHistoryStoreFiles &pHistoryArchivalFiles, CHistoryStoreFiles &pHistoryRetrievalFiles, CString &szDefaultHistoryFileName, HWND hUpdateWnd, UINT_PTR nUpdateTimerID, BOOL &bUpdate)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_pTCInterfaceThread->GetCommandHandlerConfiguration(pCommandSources, nTelecommandingMode, nTelecommandingState, nTelecommandingFlags, bTelecommandingInterlockMode, bTelecommandingReleaseWaitMode, bTelecommandingAutoRejectionMode, tVerificationUncertaintyTimeWindow, tMaximumExecutionTimePeriod, tMaximumTimeCheckPeriod, tDefaultReleaseTimeWindow, pItems, pInterlocks, pHistoryArchivalFiles, pHistoryRetrievalFiles, szDefaultHistoryFileName, hUpdateWnd, nUpdateTimerID, bUpdate);
}

BOOL CTCProcessThread::SetCommandHandlerContents(CONST CTCItems &pItems, CONST CTCItems &pHistoricalItems, CONST CTCInterlocks &pInterlocks, CONST CTCOnBoardBufferQueues &pQueues)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (SetCommandHandlerContents(pItems, pInterlocks, pQueues))
	{
		if (m_pTCManualStackWnd) m_pTCManualStackWnd->UpdateTelecommands(pItems, TRUE);
		if (m_pTCAutomaticStackWnd) m_pTCAutomaticStackWnd->UpdateTelecommands(pItems, TRUE);
		if (m_pTCOnBoardBufferQueuesWnd) m_pTCOnBoardBufferQueuesWnd->UpdateMonitoring(pQueues);
		if (m_pTCOnBoardMemoryImagesWnd) m_pTCOnBoardMemoryImagesWnd->UpdateMonitoring(pItems);
		if (m_pTCHistoryWnd) m_pTCHistoryWnd->SetTelecommands(pHistoricalItems);
		return TRUE;
	}
	return FALSE;
}
BOOL CTCProcessThread::SetCommandHandlerContents(CONST CTCItems &pItems, CONST CTCInterlocks &pInterlocks, CONST CTCOnBoardBufferQueues &pQueues)
{
	BOOL  bSuccess;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	bSuccess = SetCommandHandlerContents(pItems);
	bSuccess &= SetCommandHandlerContents(pItems, pInterlocks);
	bSuccess &= SetCommandHandlerContents(pQueues);
	return bSuccess;
}
BOOL CTCProcessThread::SetCommandHandlerContents(CONST CTCItems &pItems)
{
	INT  nID;
	INT  nItem[4];
	INT  nItems[4];
	CTCItem  *pCommandItem[2];
	CTCItems  pCommandItems[2];
	HINSTANCE  hCommandModule;
	CPtrArray  hCommandEvents;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nItem[0] = 0, nItems[0] = (pCommandItems[0].Copy(&pItems)) ? (INT)pItems.GetSize() : -1; nItem[0] < nItems[0]; nItem[0]++)
	{
		if ((pCommandItem[0] = pCommandItems[0].GetAt(nItem[0])) && pCommandItem[0]->GetStatus() != TCITEM_STATUS_DISPATCHED)
		{
			pCommandItems[0].RemoveAt(nItem[0]);
			delete pCommandItem[0];
			nItems[0]--;
			nItem[0]--;
		}
	}
	for (nItem[1] = 0, nItems[1] = (pCommandItems[1].Copy(&pItems)) ? (INT)pItems.GetSize() : -1; nItem[1] < nItems[1]; nItem[1]++)
	{
		if ((pCommandItem[1] = pCommandItems[1].GetAt(nItem[1])) && pCommandItem[1]->GetStatus() != TCITEM_STATUS_RELEASED  &&  pCommandItem[1]->GetStatus() != TCITEM_STATUS_SENT  &&  pCommandItem[1]->GetStatus() != TCITEM_STATUS_UPLINKED)
		{
			pCommandItems[1].RemoveAt(nItem[1]);
			delete pCommandItem[1];
			nItems[1]--;
			nItem[1]--;
		}
	}
	for (nItem[2] = 0, nItems[2] = sizeof(pCommandItems) / sizeof(pCommandItems[0]); nItem[2] < nItems[2]; nItem[2]++)
	{
		for (nItem[3] = 0, nItems[3] = (INT)pCommandItems[nItem[2]].GetSize(); nItem[3] < nItems[3]; nItem[3] = nItem[3] + 1)
		{
			if ((pCommandItem[0] = pCommandItems[nItem[2]].GetAt(nItem[3])) && pCommandItem[0]->GetSourceType() == TCITEM_SOURCETYPE_PROCEDURESMONITOR  &&  !pCommandItem[0]->GetVerificationModule())
			{
				for (m_pTMEnvironment->Lock(); (nID = m_pTCEnvironment->LoadTCProcedure(GetDatabase(), pCommandItem[0]->GetVerificationModuleFileName(), pCommandItem[0]->GetVerificationProcedure(), hCommandModule, hCommandEvents)) >= 0; )
				{
					Initialize(hCommandModule, pCommandItem[0]->GetVerificationProcedure(), nID, hCommandEvents, m_pTMEnvironment, pCommandItem[0]);
					m_pTCModules.Add(hCommandModule);
					m_nTCModuleIDs.Add(nID);
					break;
				}
				m_pTMEnvironment->Unlock();
			}
		}
	}
	return((nItem[0] == nItems[0] && nItem[1] == nItems[1]) ? (m_pTCReleaseThread->SetContents(pCommandItems[0]) && m_pTCVerificationThread->SetContents(pCommandItems[1])) : FALSE);
}
BOOL CTCProcessThread::SetCommandHandlerContents(CONST CTCItems &pItems, CONST CTCInterlocks &pInterlocks)
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	INT  nInterlock;
	INT  nInterlocks;
	CTCItem  *pItem;
	CTCInterlock  *pInterlock[2];
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nInterlock = 0, nInterlocks = (INT)pInterlocks.GetSize(); nInterlock < nInterlocks; nInterlock++)
	{
		if ((pInterlock[0] = pInterlocks.GetAt(nInterlock)))
		{
			if (pInterlock[0]->GetState() == TCINTERLOCK_STATE_PENDING)
			{
				for (nItem = 0, nItems = (INT)pItems.GetSize(); nItem < nItems; nItem++)
				{
					if ((pInterlock[1] = ((pItem = pItems.GetAt(nItem))) ? pInterlocks.GetAt((nIndex = pInterlocks.Find(pItem->GetComputerName(), pItem->GetSourceType(), pItem->GetInterlock()))) : (CTCInterlock *)NULL))
					{
						if (pInterlock[0]->GetName() == pInterlock[1]->GetName()) break;
						continue;
					}
				}
				if (nItem == nItems || !nItems) continue;
			}
			if ((pInterlock[1] = m_pTCInterlocks.GetAt(m_pTCInterlocks.Find(pInterlock[0]->GetComputerName(), pInterlock[0]->GetSourceType(), pInterlock[0]->GetName()))))
			{
				pInterlock[1]->Copy(pInterlock[0]);
				continue;
			}
			if ((pInterlock[1] = new CTCInterlock))
			{
				pInterlock[1]->Copy(pInterlock[0]);
				if (m_pTCInterlocks.Add(pInterlock[1]) >= 0) continue;
				delete pInterlock[1];
			}
		}
		break;
	}
	return((nInterlock == nInterlocks) ? TRUE : FALSE);
}
BOOL CTCProcessThread::SetCommandHandlerContents(CONST CTCOnBoardBufferQueues &pQueues)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_pTCOnBoardBufferQueues.Copy(&pQueues);
}

BOOL CTCProcessThread::GetCommandHandlerContents(CTCItems &pItems, CTCItems &pHistoricalItems, CTCInterlocks &pInterlocks, CTCOnBoardBufferQueues &pQueues, BOOL bAny) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (GetCommandHandlerContents(pItems, pInterlocks, pQueues, bAny))
	{
		if (m_pTCHistoryWnd) m_pTCHistoryWnd->GetTelecommands(pHistoricalItems);
		return TRUE;
	}
	return FALSE;
}
BOOL CTCProcessThread::GetCommandHandlerContents(CTCItems &pItems, CTCInterlocks &pInterlocks, CTCOnBoardBufferQueues &pQueues, BOOL bAny) CONST
{
	INT  nItem;
	INT  nItems;
	CTCItem  *pCommandItem[3];
	CTCItems  pCommandItems[2];
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (IsCommandHandler() || bAny)
	{
		if (m_pTCReleaseThread->GetContents(pCommandItems[0]) && m_pTCVerificationThread->GetContents(pCommandItems[1]) && pInterlocks.Copy(&m_pTCInterlocks) && pQueues.Copy(&m_pTCOnBoardBufferQueues))
		{
			for (nItem = 0, nItems = (pItems.Copy(&pCommandItems[1])) ? (INT)pCommandItems[0].GetSize() : -1; nItem < nItems; nItem++)
			{
				if ((pCommandItem[0] = pCommandItems[0].GetAt(nItem)))
				{
					if ((pCommandItem[1] = new CTCItem) != (CTCItem *)NULL)
					{
						if (pCommandItems[1].Find(pCommandItem[0]) < 0 && (pCommandItem[0]->GetReleaseBlockID() == (UINT)-1 || ((pCommandItem[2] = pCommandItems[0].GetAt(nItem - pCommandItem[0]->GetReleaseBlockID())) && pCommandItem[0]->GetReleaseBlock() == pCommandItem[2]->GetReleaseBlock() && !pCommandItem[2]->GetReleaseBlockID())))
						{
							if (pCommandItem[1]->Copy(pCommandItem[0]) && pItems.Add(pCommandItem[1]) >= 0) continue;
							delete pCommandItem[1];
							break;
						}
						delete pCommandItem[1];
						continue;
					}
				}
				break;
			}
			return((nItem == nItems) ? TRUE : FALSE);
		}
		return FALSE;
	}
	return m_pTCInterfaceThread->GetCommandHandlerContents(pItems, pInterlocks, pQueues);
}
BOOL CTCProcessThread::GetCommandHandlerContents(CTCItems &pItems) CONST
{
	CTCInterlocks  pInterlocks;
	CTCOnBoardBufferQueues  pQueues;

	return GetCommandHandlerContents(pItems, pInterlocks, pQueues);
}
BOOL CTCProcessThread::GetCommandHandlerContents(CTCInterlocks &pInterlocks) CONST
{
	CTCItems  pItems;
	CTCOnBoardBufferQueues  pQueues;

	return GetCommandHandlerContents(pItems, pInterlocks, pQueues);
}
BOOL CTCProcessThread::GetCommandHandlerContents(CTCOnBoardBufferQueues &pQueues) CONST
{
	CTCItems  pItems;
	CTCInterlocks  pInterlocks;

	return GetCommandHandlerContents(pItems, pInterlocks, pQueues);
}

BOOL CTCProcessThread::SetCommandHandlerState(CONST CTCUplinkDevice *pDevice)
{
	CTCItems  pItems;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (SetActiveTCUplinkDevice(pDevice); IsCommandHandler(); )
	{
		for (SetCommandHandlerState(pDevice->GetCommandHandlerState()), m_pTCReleaseThread->Update(pDevice->GetCommandHandlerState(), pItems); pItems.GetSize() > 0; )
		{
			m_pTCInterfaceThread->UpdateTelecommands(pItems, FALSE);
			break;
		}
		break;
	}
	return TRUE;
}
BOOL CTCProcessThread::SetCommandHandlerState(UINT nState)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(m_pTCReleaseThread->SetState(nState) && m_pTCVerificationThread->SetState(nState));
}

BOOL CTCProcessThread::GetCommandHandlerState(CTCUplinkDevice *pDevice) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return GetActiveTCUplinkDevice(pDevice);
}
UINT CTCProcessThread::GetCommandHandlerState() CONST
{
	UINT  nOptions;
	UINT  nState[2];
	CTCUplinkDevice  cDevice;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (GetCommandHandlerState(&cDevice), nState[0] = (IsCommandHandler()) ? ((m_pTCReleaseThread->IsEmpty() && m_pTCVerificationThread->IsEmpty()) ? (cDevice.GetCommandHandlerState() | TCSERVICE_COMMANDHANDLERSTATE_EMPTY) : cDevice.GetCommandHandlerState()) : TCSERVICE_COMMANDHANDLERSTATE_EMPTY; m_pTCManualStackWnd; )
	{
		nState[1] = ((m_pTCManualStackWnd->GetTelecommandingState() & TCMANUALSTACK_STATE_EMPTY) || (m_pTCManualStackWnd->GetMiscellaneousOptions(nOptions) && (nOptions & TCMANUALSTACK_OPTION_ALWAYSALLOWEXIT))) ? (nState[0] | TCSERVICE_COMMANDHANDLERSTATE_EMPTY) : (nState[0] & ~TCSERVICE_COMMANDHANDLERSTATE_EMPTY);
		nState[0] &= nState[1];
		break;
	}
	if (m_pTCAutomaticStackWnd)
	{
		nState[1] = ((m_pTCAutomaticStackWnd->GetTelecommandingState() & TCAUTOMATICSTACK_STATE_EMPTY) || (m_pTCAutomaticStackWnd->GetMiscellaneousOptions(nOptions) && (nOptions & TCAUTOMATICSTACK_OPTION_ALWAYSALLOWEXIT))) ? (nState[0] | TCSERVICE_COMMANDHANDLERSTATE_EMPTY) : (nState[0] & ~TCSERVICE_COMMANDHANDLERSTATE_EMPTY);
		nState[0] &= nState[1];
	}
	if (m_pTCProceduresMonitorWnd) nState[0] &= (m_pTCProceduresMonitorWnd->GetTelecommandingState() & TCPROCEDURESMONITOR_STATE_IDLE) ? (nState[0] | TCSERVICE_COMMANDHANDLERSTATE_EMPTY) : (nState[0] & ~TCSERVICE_COMMANDHANDLERSTATE_EMPTY);
	return nState[0];
}

BOOL CTCProcessThread::SetCommandHandlerVerificationUncertaintyTimeWindow(CONST CTimeSpan &tTimeWindow)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_pTCInterfaceThread->SetCommandHandlerVerificationUncertaintyTimeWindow(tTimeWindow);
}

BOOL CTCProcessThread::GetCommandHandlerVerificationUncertaintyTimeWindow(CTimeSpan &tTimeWindow) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_pTCInterfaceThread->GetCommandHandlerVerificationUncertaintyTimeWindow(tTimeWindow);
}

BOOL CTCProcessThread::SetCommandHandlerDefaultReleaseTimeWindow(CONST CTimeSpan &tTimeWindow)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_pTCInterfaceThread->SetCommandHandlerDefaultReleaseTimeWindow(tTimeWindow);
}

BOOL CTCProcessThread::GetCommandHandlerDefaultReleaseTimeWindow(CTimeSpan &tTimeWindow) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_pTCInterfaceThread->GetCommandHandlerDefaultReleaseTimeWindow(tTimeWindow);
}

BOOL CTCProcessThread::SetCommandHandlerOptions(UINT nOptions)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_pTCInterfaceThread->SetCommandHandlerOptions(nOptions);
}

UINT CTCProcessThread::GetCommandHandlerOptions() CONST
{
	UINT  nOptions[2];
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nOptions[0] = (IsCommandHandler()) ? m_pTCInterfaceThread->GetCommandHandlerOptions() : TCSERVICE_COMMANDHANDLEROPTION_ALWAYSALLOWEXIT; m_pTCManualStackWnd != (CTCManualStackWnd *)NULL && m_pTCManualStackWnd->GetMiscellaneousOptions(nOptions[1]); )
	{
		nOptions[0] &= ((m_pTCManualStackWnd->GetTelecommandingState() & TCMANUALSTACK_STATE_EMPTY) || (nOptions[1] & TCMANUALSTACK_OPTION_ALWAYSALLOWEXIT)) ? (nOptions[0] | TCSERVICE_COMMANDHANDLEROPTION_ALWAYSALLOWEXIT) : (nOptions[0] & ~TCSERVICE_COMMANDHANDLEROPTION_ALWAYSALLOWEXIT);
		break;
	}
	nOptions[0] &= (m_pTCAutomaticStackWnd != (CTCAutomaticStackWnd *)NULL  &&  m_pTCAutomaticStackWnd->GetMiscellaneousOptions(nOptions[1])) ? (((m_pTCAutomaticStackWnd->GetTelecommandingState() & TCAUTOMATICSTACK_STATE_EMPTY) || (nOptions[1] & TCAUTOMATICSTACK_OPTION_ALWAYSALLOWEXIT)) ? (nOptions[0] | TCSERVICE_COMMANDHANDLEROPTION_ALWAYSALLOWEXIT) : (nOptions[0] & ~TCSERVICE_COMMANDHANDLEROPTION_ALWAYSALLOWEXIT)) : nOptions[0];
	nOptions[0] &= (m_pTCProceduresMonitorWnd) ? ((m_pTCProceduresMonitorWnd->GetTelecommandingState() & TCPROCEDURESMONITOR_STATE_IDLE) ? (nOptions[0] | TCSERVICE_COMMANDHANDLEROPTION_ALWAYSALLOWEXIT) : nOptions[0]) : nOptions[0];
	return nOptions[0];
}

BOOL CTCProcessThread::IsCommandHandler() CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_pTCInterfaceThread->IsCommandHandler();
}

BOOL CTCProcessThread::SetCommandSources(CONST CTCProcessCommandSources &pCommandSources)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_pTCInterfaceThread->SetCommandSources(pCommandSources);
}

BOOL CTCProcessThread::GetCommandSources(CTCProcessCommandSources &pCommandSources) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_pTCInterfaceThread->GetCommandSources(pCommandSources);
}

BOOL CTCProcessThread::UpdateCommandSources(LPCTSTR pszOriginator, CONST CTCProcessCommandSources &pCommandSources)
{
	INT  nCommandSource;
	INT  nCommandSources;
	BOOL  bCommandSource;
	CTCProcessCommandSourceInfo  *pCommandSourceInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nCommandSource = 0, nCommandSources = (INT)pCommandSources.GetSize(), bCommandSource = FALSE; nCommandSource < nCommandSources; nCommandSource++)
	{
		if ((pCommandSourceInfo = pCommandSources.GetAt(nCommandSource)) != (CTCProcessCommandSourceInfo *)NULL  &&  pCommandSourceInfo->IsHost())
		{
			if (m_pTCManualStackWnd != (CTCManualStackWnd *)NULL  &&  pCommandSourceInfo->GetSourceType() == TCSERVICE_COMMANDSOURCETYPE_MANUALSTACK)
			{
				m_pTCManualStackWnd->UpdateTelecommanding(pszOriginator, pCommandSourceInfo);
				bCommandSource = TRUE;
			}
			if (m_pTCAutomaticStackWnd != (CTCAutomaticStackWnd *)NULL  &&  pCommandSourceInfo->GetSourceType() == TCSERVICE_COMMANDSOURCETYPE_AUTOMATICSTACK)
			{
				m_pTCAutomaticStackWnd->UpdateTelecommanding(pszOriginator, pCommandSourceInfo);
				bCommandSource = TRUE;
			}
			if (m_pTCProceduresMonitorWnd != (CTCProceduresMonitorWnd *)NULL  &&  pCommandSourceInfo->GetSourceType() == TCSERVICE_COMMANDSOURCETYPE_PROCEDURESMONITOR)
			{
				m_pTCProceduresMonitorWnd->UpdateMonitoring(pszOriginator, pCommandSourceInfo);
				bCommandSource = TRUE;
			}
		}
	}
	if (IsCommandHandler())
	{
		m_pTCReleaseThread->Update();
		m_pTCVerificationThread->Update();
	}
	return bCommandSource;
}
BOOL CTCProcessThread::UpdateCommandSources(LPCTSTR pszOriginator, CONST CTCProcessCommandSources &pCommandSources, CONST CTCItems &pItems, CONST CTCItems &pHistoricalItems, CONST CTCInterlocks &pInterlocks, CONST CTCOnBoardBufferQueues &pQueues)
{
	INT  nIndex;
	INT  nCount;
	INT  nInterlock;
	INT  nInterlocks;
	INT  nCommandSource;
	INT  nCommandSources;
	BOOL  bCommandSource;
	CTCInterlock  *pCommandInterlock[2];
	CTCInterlocks  pCommandInterlocks;
	CTCProcessCommandSourceInfo  *pCommandSourceInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nIndex = 0, nCount = (INT)m_nTCModuleIDs.GetSize(), m_pTCReleaseThread->Reset(), m_pTCVerificationThread->Reset(); nIndex < nCount; nIndex++)
	{
		m_pTCEnvironment->FreeTCProcedure(m_nTCModuleIDs.GetAt(nIndex));
		m_nTCModuleIDs.RemoveAt(nIndex);
		m_pTCModules.RemoveAt(nIndex);
		nIndex--;
		nCount--;
	}
	for (nInterlock = 0, nInterlocks = (pCommandInterlocks.Copy(&m_pTCInterlocks)) ? (INT)pInterlocks.GetSize() : 0; nInterlock < nInterlocks; nInterlock++)
	{
		if ((pCommandInterlock[1] = ((pCommandInterlock[0] = pInterlocks.GetAt(nInterlock))) ? m_pTCInterlocks.GetAt(m_pTCInterlocks.Find(pCommandInterlock[0]->GetComputerName(), pCommandInterlock[0]->GetSourceType(), pCommandInterlock[0]->GetName())) : (CTCInterlock *)NULL))
		{
			if ((nIndex = pCommandInterlocks.Find(pCommandInterlock[0]->GetComputerName(), pCommandInterlock[0]->GetSourceType(), pCommandInterlock[0]->GetName())) >= 0)
			{
				delete pCommandInterlocks.GetAt(nIndex);
				pCommandInterlocks.RemoveAt(nIndex);
			}
			pCommandInterlock[1]->Copy(pCommandInterlock[0]);
			continue;
		}
		if ((pCommandInterlock[0] = pInterlocks.GetAt(nInterlock)))
		{
			if ((pCommandInterlock[1] = new CTCInterlock))
			{
				pCommandInterlock[1]->Copy(pCommandInterlock[0]);
				if (m_pTCInterlocks.Add(pCommandInterlock[1]) >= 0) continue;
				delete pCommandInterlock[1];
			}
		}
	}
	for (nCommandSource = 0, nCommandSources = (INT)pCommandSources.GetSize(), bCommandSource = FALSE; nCommandSource < nCommandSources; nCommandSource++)
	{
		if ((pCommandSourceInfo = pCommandSources.GetAt(nCommandSource)) != (CTCProcessCommandSourceInfo *)NULL  &&  pCommandSourceInfo->IsHost())
		{
			if (m_pTCManualStackWnd != (CTCManualStackWnd *)NULL  &&  pCommandSourceInfo->GetSourceType() == TCSERVICE_COMMANDSOURCETYPE_MANUALSTACK)
			{
				m_pTCManualStackWnd->UpdateTelecommanding(pszOriginator, pCommandSourceInfo);
				m_pTCManualStackWnd->UpdateTelecommands(pItems, TRUE);
				bCommandSource = TRUE;
			}
			if (m_pTCAutomaticStackWnd != (CTCAutomaticStackWnd *)NULL  &&  pCommandSourceInfo->GetSourceType() == TCSERVICE_COMMANDSOURCETYPE_AUTOMATICSTACK)
			{
				m_pTCAutomaticStackWnd->UpdateTelecommanding(pszOriginator, pCommandSourceInfo);
				m_pTCAutomaticStackWnd->UpdateTelecommands(pItems, TRUE);
				bCommandSource = TRUE;
			}
			if (m_pTCProceduresMonitorWnd != (CTCProceduresMonitorWnd *)NULL  &&  pCommandSourceInfo->GetSourceType() == TCSERVICE_COMMANDSOURCETYPE_PROCEDURESMONITOR)
			{
				m_pTCProceduresMonitorWnd->UpdateMonitoring(pszOriginator, pCommandSourceInfo);
				bCommandSource = TRUE;
			}
			if (m_pTCOnBoardMemoryImagesWnd)
			{
				m_pTCOnBoardMemoryImagesWnd->UpdateMonitoring(pItems, TRUE);
				bCommandSource = TRUE;
			}
		}
	}
	for (m_pTCOnBoardBufferQueues.Copy(&pQueues); m_pTCHistoryWnd; )
	{
		m_pTCHistoryWnd->SetTelecommands(pHistoricalItems);
		break;
	}
	for (UpdateTCInterlocks(pCommandInterlocks, FALSE); IsCommandHandler(); )
	{
		m_pTCReleaseThread->Update();
		m_pTCVerificationThread->Update();
		break;
	}
	return bCommandSource;
}

BOOL CTCProcessThread::SetCommandSourceTelecommandingMode(LPCTSTR pszComputerName, UINT nSourceType, UINT nMode)
{
	CTCProcessCommandSources  pCommandSources;
	CTCProcessCommandSourceInfo  *pCommandSourceInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (; (pCommandSourceInfo = (GetCommandSources(pCommandSources)) ? pCommandSources.GetAt(pCommandSources.Find(pszComputerName, nSourceType)) : (CTCProcessCommandSourceInfo *)NULL); )
	{
		for (pCommandSourceInfo->SetTelecommandingMode(nMode); SetCommandSources(pCommandSources); ) return TRUE;
		break;
	}
	return FALSE;
}

UINT CTCProcessThread::GetCommandSourceTelecommandingMode(LPCTSTR pszComputerName, UINT nSourceType) CONST
{
	CTCProcessCommandSources  pCommandSources;
	CTCProcessCommandSourceInfo  *pCommandSourceInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(((pCommandSourceInfo = (GetCommandSources(pCommandSources)) ? pCommandSources.GetAt(pCommandSources.Find(pszComputerName, nSourceType)) : (CTCProcessCommandSourceInfo *)NULL)) ? pCommandSourceInfo->GetTelecommandingMode() : 0);
}

BOOL CTCProcessThread::SetCommandSourceTelecommandingState(LPCTSTR pszComputerName, UINT nSourceType, UINT nState)
{
	CTCProcessCommandSources  pCommandSources;
	CTCProcessCommandSourceInfo  *pCommandSourceInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (; (pCommandSourceInfo = (GetCommandSources(pCommandSources)) ? pCommandSources.GetAt(pCommandSources.Find(pszComputerName, nSourceType)) : (CTCProcessCommandSourceInfo *)NULL); )
	{
		for (pCommandSourceInfo->SetTelecommandingState(nState); SetCommandSources(pCommandSources); ) return TRUE;
		break;
	}
	return FALSE;
}

UINT CTCProcessThread::GetCommandSourceTelecommandingState(LPCTSTR pszComputerName, UINT nSourceType) CONST
{
	CTCProcessCommandSources  pCommandSources;
	CTCProcessCommandSourceInfo  *pCommandSourceInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(((pCommandSourceInfo = (GetCommandSources(pCommandSources)) ? pCommandSources.GetAt(pCommandSources.Find(pszComputerName, nSourceType)) : (CTCProcessCommandSourceInfo *)NULL)) ? pCommandSourceInfo->GetTelecommandingState() : 0);
}

BOOL CTCProcessThread::SetCommandSourceTelecommandingChecks(LPCTSTR pszComputerName, UINT nSourceType, UINT nFlags)
{
	CTCProcessCommandSources  pCommandSources;
	CTCProcessCommandSourceInfo  *pCommandSourceInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (; (pCommandSourceInfo = (GetCommandSources(pCommandSources)) ? pCommandSources.GetAt(pCommandSources.Find(pszComputerName, nSourceType)) : (CTCProcessCommandSourceInfo *)NULL); )
	{
		for (pCommandSourceInfo->SetTelecommandingChecks(nFlags); SetCommandSources(pCommandSources); ) return TRUE;
		break;
	}
	return FALSE;
}

UINT CTCProcessThread::GetCommandSourceTelecommandingChecks(LPCTSTR pszComputerName, UINT nSourceType) CONST
{
	CTCProcessCommandSources  pCommandSources;
	CTCProcessCommandSourceInfo  *pCommandSourceInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(((pCommandSourceInfo = (GetCommandSources(pCommandSources)) ? pCommandSources.GetAt(pCommandSources.Find(pszComputerName, nSourceType)) : (CTCProcessCommandSourceInfo *)NULL)) ? pCommandSourceInfo->GetTelecommandingChecks() : 0);
}

BOOL CTCProcessThread::EnableCommandSourceTelecommandingInterlockMode(LPCTSTR pszComputerName, UINT nSourceType, BOOL bEnable)
{
	CTCProcessCommandSources  pCommandSources;
	CTCProcessCommandSourceInfo  *pCommandSourceInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (; (pCommandSourceInfo = (GetCommandSources(pCommandSources)) ? pCommandSources.GetAt(pCommandSources.Find(pszComputerName, nSourceType)) : (CTCProcessCommandSourceInfo *)NULL); )
	{
		for (pCommandSourceInfo->EnableTelecommandingInterlockMode(bEnable); SetCommandSources(pCommandSources); ) return TRUE;
		break;
	}
	return FALSE;
}

BOOL CTCProcessThread::IsCommandSourceTelecommandingInterlockModeEnabled(LPCTSTR pszComputerName, UINT nSourceType) CONST
{
	CTCProcessCommandSources  pCommandSources;
	CTCProcessCommandSourceInfo  *pCommandSourceInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(((pCommandSourceInfo = (GetCommandSources(pCommandSources)) ? pCommandSources.GetAt(pCommandSources.Find(pszComputerName, nSourceType)) : (CTCProcessCommandSourceInfo *)NULL)) ? pCommandSourceInfo->IsTelecommandingInterlockModeEnabled() : FALSE);
}

BOOL CTCProcessThread::EnableCommandSourceTelecommandingReleaseWaitMode(LPCTSTR pszComputerName, UINT nSourceType, BOOL bEnable)
{
	CTCProcessCommandSources  pCommandSources;
	CTCProcessCommandSourceInfo  *pCommandSourceInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (; (pCommandSourceInfo = (GetCommandSources(pCommandSources)) ? pCommandSources.GetAt(pCommandSources.Find(pszComputerName, nSourceType)) : (CTCProcessCommandSourceInfo *)NULL); )
	{
		for (pCommandSourceInfo->EnableTelecommandingReleaseWaitMode(bEnable); SetCommandSources(pCommandSources); ) return TRUE;
		break;
	}
	return FALSE;
}

BOOL CTCProcessThread::IsCommandSourceTelecommandingReleaseWaitModeEnabled(LPCTSTR pszComputerName, UINT nSourceType) CONST
{
	CTCProcessCommandSources  pCommandSources;
	CTCProcessCommandSourceInfo  *pCommandSourceInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(((pCommandSourceInfo = (GetCommandSources(pCommandSources)) ? pCommandSources.GetAt(pCommandSources.Find(pszComputerName, nSourceType)) : (CTCProcessCommandSourceInfo *)NULL)) ? pCommandSourceInfo->IsTelecommandingReleaseWaitModeEnabled() : 0);
}

BOOL CTCProcessThread::EnableCommandSourceTelecommandingAutoRejectionMode(LPCTSTR pszComputerName, UINT nSourceType, BOOL bEnable)
{
	CTCProcessCommandSources  pCommandSources;
	CTCProcessCommandSourceInfo  *pCommandSourceInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (; (pCommandSourceInfo = (GetCommandSources(pCommandSources)) ? pCommandSources.GetAt(pCommandSources.Find(pszComputerName, nSourceType)) : (CTCProcessCommandSourceInfo *)NULL); )
	{
		for (pCommandSourceInfo->EnableTelecommandingAutoRejectionMode(bEnable); SetCommandSources(pCommandSources); ) return TRUE;
		break;
	}
	return FALSE;
}

BOOL CTCProcessThread::IsCommandSourceTelecommandingAutoRejectionModeEnabled(LPCTSTR pszComputerName, UINT nSourceType) CONST
{
	CTCProcessCommandSources  pCommandSources;
	CTCProcessCommandSourceInfo  *pCommandSourceInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(((pCommandSourceInfo = (GetCommandSources(pCommandSources)) ? pCommandSources.GetAt(pCommandSources.Find(pszComputerName, nSourceType)) : (CTCProcessCommandSourceInfo *)NULL)) ? pCommandSourceInfo->IsTelecommandingAutoRejectionModeEnabled() : FALSE);
}

BOOL CTCProcessThread::SetCommandSourceSubSystemChecks(LPCTSTR pszComputerName, UINT nSourceType, CONST CUIntArray &nSubSystemIDs, CONST CStringArray &szEnablingEvents, CONST CStringArray &szDisablingEvents, CONST CUIntArray &nStatus)
{
	CTCProcessCommandSources  pCommandSources;
	CTCProcessCommandSourceInfo  *pCommandSourceInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (; (pCommandSourceInfo = (GetCommandSources(pCommandSources)) ? pCommandSources.GetAt(pCommandSources.Find(pszComputerName, nSourceType)) : (CTCProcessCommandSourceInfo *)NULL); )
	{
		for (pCommandSourceInfo->SetSubSystemChecks(nSubSystemIDs, szEnablingEvents, szDisablingEvents, nStatus); SetCommandSources(pCommandSources); ) return TRUE;
		break;
	}
	return FALSE;
}

BOOL CTCProcessThread::GetCommandSourceSubSystemChecks(LPCTSTR pszComputerName, UINT nSourceType, CUIntArray &nSubSystemIDs, CStringArray &szEnablingEvents, CStringArray &szDisablingEvents, CUIntArray &nStatus) CONST
{
	CTCProcessCommandSources  pCommandSources;
	CTCProcessCommandSourceInfo  *pCommandSourceInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(((pCommandSourceInfo = (GetCommandSources(pCommandSources)) ? pCommandSources.GetAt(pCommandSources.Find(pszComputerName, nSourceType)) : (CTCProcessCommandSourceInfo *)NULL)) ? (pCommandSourceInfo->GetSubSystemChecks(nSubSystemIDs, szEnablingEvents, szDisablingEvents, nStatus) > 0) : FALSE);
}

BOOL CTCProcessThread::IsCommandSourceSubSystemEnabled(LPCTSTR pszComputerName, UINT nSourceType, CONST CTCItem *pItem) CONST
{
	INT  nSubSystem;
	INT  nSubSystems;
	CUIntArray  nSubSystemIDs;
	CUIntArray  nSubSystemStatus;
	CStringArray  szSubSystemEvents[2];
	CDatabaseTCPacket  cSubSystemPacket;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nSubSystem = 0, nSubSystems = (GetCommandSourceSubSystemChecks(pszComputerName, nSourceType, nSubSystemIDs, szSubSystemEvents[0], szSubSystemEvents[1], nSubSystemStatus) >= 0 && pItem->GetType() != TCAUTOMATICSTACKITEM_TYPE_PROCEDURE && pItem->GetTCPacket(&cSubSystemPacket)) ? (INT)nSubSystemIDs.GetSize() : 0; nSubSystem < nSubSystems; nSubSystem++)
	{
		if (nSubSystemIDs.GetAt(nSubSystem) == cSubSystemPacket.GetAPID())
		{
			if (!LOBYTE(nSubSystemStatus.GetAt(nSubSystem))) break;
			if (!HIBYTE(nSubSystemStatus.GetAt(nSubSystem))) break;
			return TRUE;
		}
	}
	return((nSubSystem == nSubSystems) ? TRUE : FALSE);
}

BOOL CTCProcessThread::SetDefaultReleaseTimeWindow(LPCTSTR pszComputerName, UINT nSourceType, CONST CTimeSpan &tTimeWindow)
{
	CTCProcessCommandSources  pCommandSources;
	CTCProcessCommandSourceInfo  *pCommandSourceInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (; (pCommandSourceInfo = (GetCommandSources(pCommandSources)) ? pCommandSources.GetAt(pCommandSources.Find(pszComputerName, nSourceType)) : (CTCProcessCommandSourceInfo *)NULL); )
	{
		for (pCommandSourceInfo->SetDefaultReleaseTimeWindow(tTimeWindow); SetCommandSources(pCommandSources); ) return TRUE;
		break;
	}
	return FALSE;
}

CTimeSpan CTCProcessThread::GetDefaultReleaseTimeWindow(LPCTSTR pszComputerName, UINT nSourceType) CONST
{
	CTCProcessCommandSources  pCommandSources;
	CTCProcessCommandSourceInfo  *pCommandSourceInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(((pCommandSourceInfo = (GetCommandSources(pCommandSources)) ? pCommandSources.GetAt(pCommandSources.Find(pszComputerName, nSourceType)) : (CTCProcessCommandSourceInfo *)NULL)) ? pCommandSourceInfo->GetDefaultReleaseTimeWindow() : 0);
}

BOOL CTCProcessThread::SetDispatchTimeWindow(LPCTSTR pszComputerName, UINT nSourceType, CONST CTimeSpan &tTimeWindow)
{
	CTCProcessCommandSources  pCommandSources;
	CTCProcessCommandSourceInfo  *pCommandSourceInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (; (pCommandSourceInfo = (GetCommandSources(pCommandSources)) ? pCommandSources.GetAt(pCommandSources.Find(pszComputerName, nSourceType)) : (CTCProcessCommandSourceInfo *)NULL); )
	{
		for (pCommandSourceInfo->SetDispatchTimeWindow(tTimeWindow); SetCommandSources(pCommandSources); ) return TRUE;
		break;
	}
	return FALSE;
}

CTimeSpan CTCProcessThread::GetDispatchTimeWindow(LPCTSTR pszComputerName, UINT nSourceType) CONST
{
	CTCProcessCommandSources  pCommandSources;
	CTCProcessCommandSourceInfo  *pCommandSourceInfo;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return(((pCommandSourceInfo = (GetCommandSources(pCommandSources)) ? pCommandSources.GetAt(pCommandSources.Find(pszComputerName, nSourceType)) : (CTCProcessCommandSourceInfo *)NULL)) ? pCommandSourceInfo->GetDispatchTimeWindow() : 0);
}

BOOL CTCProcessThread::AuthorizeTelecommands(CTCItems &pItems)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return((m_pTCProceduresMonitorWnd) ? m_pTCProceduresMonitorWnd->AuthorizeTelecommands(pItems) : FALSE);
}

BOOL CTCProcessThread::LoadTelecommands(CONST CTCItems &pItems)
{
	INT  nItem;
	INT  nItems;
	CTCItem  *pStackItem[2];
	CTCItems  pStackItems[2];
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nItem = 0, nItems = (INT)pItems.GetSize(); nItem < nItems; nItem++)
	{
		if ((pStackItem[1] = ((pStackItem[0] = pItems.GetAt(nItem))) ? new CTCItem : (CTCItem *)NULL))
		{
			if (pStackItem[1]->Copy(pStackItem[0]) && ((pStackItem[1]->GetSourceType() == TCITEM_SOURCETYPE_MANUALSTACK  &&  pStackItems[0].Add(pStackItem[1]) >= 0) || (pStackItem[1]->GetSourceType() == TCITEM_SOURCETYPE_AUTOMATICSTACK  &&  pStackItems[1].Add(pStackItem[1]) >= 0))) continue;
			delete pStackItem[1];
		}
		break;
	}
	return((nItem == nItems && ((m_pTCManualStackWnd != (CTCManualStackWnd *)NULL  &&  pStackItems[0].GetSize() > 0 && m_pTCManualStackWnd->LoadTelecommands(pStackItems[0])) || !pStackItems[0].GetSize()) && ((m_pTCAutomaticStackWnd != (CTCAutomaticStackWnd *)NULL  &&  pStackItems[1].GetSize() > 0 && m_pTCAutomaticStackWnd->LoadTelecommands(pStackItems[1])) || !pStackItems[1].GetSize())) ? TRUE : FALSE);
}

BOOL CTCProcessThread::DispatchTelecommands(CONST CTCItems &pItems, BOOL bUndo)
{
	INT  nID;
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	INT  nCount;
	BOOL  bUpdate;
	CTCItem  *pItem;
	HINSTANCE  hModule;
	CPtrArray  hEvents;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (IsCommandHandler())
	{
		for (nItem = 0, nItems = (!bUndo) ? (INT)pItems.GetSize() : 0; nItem < nItems; nItem++)
		{
			if ((pItem = pItems.GetAt(nItem)) && pItem->GetSourceType() == TCITEM_SOURCETYPE_PROCEDURESMONITOR  &&  !pItem->GetVerificationModule())
			{
				for (m_pTMEnvironment->Lock(); (nID = m_pTCEnvironment->LoadTCProcedure(GetDatabase(), pItem->GetVerificationModuleFileName(), pItem->GetVerificationProcedure(), hModule, hEvents)) >= 0; )
				{
					Initialize(hModule, pItem->GetVerificationProcedure(), nID, hEvents, m_pTMEnvironment, pItem);
					m_pTCModules.Add(hModule);
					m_nTCModuleIDs.Add(nID);
					break;
				}
				m_pTMEnvironment->Unlock();
			}
		}
		for (nItem = 0, nItems = (bUndo) ? (INT)pItems.GetSize() : 0; nItem < nItems; nItem++)
		{
			if ((pItem = pItems.GetAt(nItem)) && pItem->GetSourceType() == TCITEM_SOURCETYPE_PROCEDURESMONITOR)
			{
				for (nIndex = 0, nCount = (INT)m_nTCModuleIDs.GetSize(); nIndex < nCount; nIndex++)
				{
					if (m_nTCModuleIDs.GetAt(nIndex) == (UINT)pItem->GetVerificationProcessID())
					{
						m_pTCEnvironment->FreeTCProcedure(pItem->GetVerificationProcessID());
						m_nTCModuleIDs.RemoveAt(nIndex);
						m_pTCModules.RemoveAt(nIndex);
						break;
					}
				}
			}
		}
		for (bUpdate = TRUE; m_pTMEnvironment->Lock(); )
		{
			bUpdate &= m_pTCReleaseThread->Update(m_pTCProcessEngine, m_pTCEnvironment, m_pTMEnvironment, pItems, m_pTCInterlocks, bUndo);
			m_pTMEnvironment->Unlock();
			break;
		}
		m_pTCInterfaceThread->UpdateCommandHandler(TCSERVICE_COMMANDINTERFACE_TELECOMMANDSUPDATE, TRUE);
		return bUpdate;
	}
	return m_pTCInterfaceThread->DispatchTelecommands(pItems, bUndo);
}

BOOL CTCProcessThread::ReleaseTelecommands(CONST CTCItems &pItems)
{
	INT  nIndex;
	INT  nCount;
	INT  nItem[2];
	INT  nItems[2];
	INT  nReleaseID;
	INT  nInterlock;
	INT  nInterlocks;
	INT  nCommandSource;
	INT  nCommandSources;
	INT  nTransferFrame;
	INT  nTransferFrames;
	BOOL  bBlocked;
	BOOL  bInterlocks;
	UINT  nExecutionOBRT;
	LPBYTE  pProcessInfo;
	HANDLE  hResults[2];
	CTCItem  *pItem[2];
	CTCItems  pInterlockItems;
	CTimeTag  tExecutionTime;
	CTCPacket  *pTCPacket;
	CPtrArray  pTCPackets[2];
	CPtrArray  pTCPacketInfo;
	CByteArray  nTCPacketData;
	CByteArray  nProcessInfo[2];
	CUIntArray  nReleaseIDs;
	CTCInterlock  *pInterlock[2];
	CDatabaseTCPacket  *pPacket[2];
	CDatabaseTCPackets  pPackets;
	CDatabaseTCFunction  *pFunction[2];
	CDatabaseTCFunctions  pFunctions;
	CDatabaseTCFunctions  pBlockedItems;
	CTCProcessCommandSourceInfo  *pCommandSourceInfo;
	CTCProcessCommandSources  pCommandSources;
	CTCTransferFrames  pTCTransferFrames;
	CTCTransferFrame  *pTCTransferFrame;

	for (nItem[0] = 0, nItems[0] = (IsCommandHandler() && GetProcessData(nProcessInfo[0])) ? (INT)pItems.GetSize() : 0; nItem[0] < nItems[0]; nItem[0]++)
	{
		if ((pItem[0] = pItems.GetAt(nItem[0])))
		{
			if (pItem[0]->GetType() == TCITEM_TYPE_FUNCTION)
			{
				if (pItem[0]->GetStatus() != TCITEM_STATUS_NOTRELEASED  &&  pItem[0]->GetStatus() != TCITEM_STATUS_FAILEDRELEASE)
				{
					for (pBlockedItems.RemoveAll(); pItem[0]->GetExecutionOBRT(nExecutionOBRT) && ConvertOBRTToTime(nExecutionOBRT, tExecutionTime); )
					{
						pItem[0]->SetExecutionTime(tExecutionTime);
						break;
					}
					if ((pPacket[0] = new CDatabaseTCPacket))
					{
						if ((!pItem[0]->GetExecutionOBRT(nExecutionOBRT) || pItem[0]->GetExecutionTime(tExecutionTime)) && pItem[0]->GetTCPacket(pPacket[0]))
						{
							if (InitializeTCPacket(pItem[0], pPacket[0]) && GenerateTCPackets(pItem[0], pPacket[0], pItem[0]->GetMemoryPatch(), pItem[0]->GetExecutionTime(tExecutionTime), FALSE, (bBlocked = ((pItem[0]->GetFlags() & TCITEM_LINKAGEFLAG_BLOCKED) && pItem[0]->GetReleaseBlockID() > 0) ? TRUE : FALSE), FALSE, pFunctions, pPackets))
							{
								for (nItem[1] = 0, nItems[1] = (INT)pPackets.GetSize(); nItem[1] < nItems[1]; nItem[1]++)
								{
									if ((pFunction[0] = pFunctions.GetAt(nItem[1])))
									{
										if ((pPacket[1] = pPackets.GetAt(nItem[1])))
										{
											if ((pTCPacket = (!bBlocked) ? new CTCPacket : (CTCPacket *)NULL))
											{
												if (InitializeTCPacket(pItem[0], pFunction[0], pPacket[1], nItem[1]) && InitializeTCPacket(pFunction[0], pPacket[1], pTCPacket, tExecutionTime, (pItem[0]->GetReleaseBlockID() == 0) ? TRUE : FALSE) && pTCPacket->Map(nTCPacketData))
												{
													if ((pProcessInfo = (GetProcessData(nProcessInfo[1])) ? (LPBYTE)GlobalAlloc(GPTR, nProcessInfo[1].GetSize()*sizeof(BYTE)) : (LPBYTE)NULL))
													{
														CopyMemory(pProcessInfo, nProcessInfo[1].GetData(), nProcessInfo[1].GetSize());
														pItem[0]->CDatabaseTCFunction::Copy(pFunction[0]);
														pItem[0]->SetTCPacket(nTCPacketData);
														pItem[0]->SetTCPacket(pPacket[1]);
														pTCPackets[0].Add(pTCPacket);
														pTCPackets[1].Add(pItem[0]);
														pTCPacketInfo.Add(pProcessInfo);
														continue;
													}
												}
												delete pTCPacket;
											}
											if ((pTCPacket = (bBlocked  &&  pTCPackets[0].GetSize() > 0) ? (CTCPacket *)pTCPackets[0].GetAt(pTCPackets[0].GetUpperBound()) : (CTCPacket *)NULL))
											{
												if (CollectTCPacket(pFunction[0], pTCPacket, pItem[0]->GetReleaseBlockID()) && pTCPacket->Map(nTCPacketData))
												{
													if ((pItem[1] = pItems.GetAt(nItem[0] - pItem[0]->GetReleaseBlockID())) && pItem[1]->GetReleaseBlockedItems(pBlockedItems) >= 0)
													{
														if ((pFunction[1] = new CDatabaseTCFunction))
														{
															if (pFunction[1]->Copy(pFunction[0]))
															{
																pBlockedItems.InsertAt(pBlockedItems.GetSize(), pFunction[1], 1);
																pItem[1]->SetReleaseBlockedItems(pBlockedItems);
																pItem[1]->SetTCPacket(nTCPacketData);
																continue;
															}
															delete pFunction[1];
														}
													}
												}
											}
										}
									}
									break;
								}
								if (nItem[1] == nItems[1])
								{
									delete pPacket[0];
									continue;
								}
							}
						}
						delete pPacket[0];
					}
					pItem[0]->SetResult((pItem[0]->GetResult() & ~(TCITEM_RESULT_PTV_GO | TCITEM_RESULT_PTV_WAIT)) | (TCITEM_RESULT_PTV_FAIL | TCITEM_FAILURE_PTV_ENCODING));
					pItem[0]->SetStatus(TCITEM_STATUS_NOTRELEASED);
				}
			}
			if (pItem[0]->GetType() == TCITEM_TYPE_PROCEDURE)
			{
				if (pItem[0]->GetStatus() != TCITEM_STATUS_NOTEXECUTED  &&  pItem[0]->GetStatus() != TCITEM_STATUS_FAILEDEXECUTION)
				{
					if (pItem[0]->GetSourceType() == TCITEM_SOURCETYPE_MANUALSTACK || pItem[0]->GetSourceType() == TCITEM_SOURCETYPE_AUTOMATICSTACK || pItem[0]->GetSourceType() == TCITEM_SOURCETYPE_PROCEDURESMONITOR)
					{
						for (Lock(); (pItem[0]->IsHost() && m_pTCProceduresMonitorWnd != (CTCProceduresMonitorWnd *)NULL && m_pTCProceduresMonitorWnd->UpdateProcedure(pItem[0])) || (!pItem[0]->IsHost() && ExecuteTelecommand(pItem[0])); )
						{
							pTCPackets[0].Add(NULL);
							pTCPackets[1].Add(NULL);
							pTCPacketInfo.Add(NULL);
							pItem[0]->SetStatus(TCITEM_STATUS_EXECUTED);
							break;
						}
						if (pItem[0]->GetStatus() == TCITEM_STATUS_EXECUTED)
						{
							Unlock();
							continue;
						}
						Unlock();
					}
					pItem[0]->SetResult((pItem[0]->GetResult() & ~(TCITEM_RESULT_PTV_GO | TCITEM_RESULT_PTV_WAIT)) | TCITEM_RESULT_PTV_FAIL);
					pItem[0]->SetStatus(TCITEM_STATUS_FAILEDEXECUTION);
				}
			}
		}
		break;
	}
	if (nItem[0] < nItems[0])
	{
		for (; nItem[0] > 0; nItem[0]--)
		{
			if ((pTCPacket = (nItem[0] <= pTCPackets[0].GetSize()) ? (CTCPacket *)pTCPackets[0].GetAt(nItem[0] - 1) : (CTCPacket *)NULL))
			{
				if ((pProcessInfo = (LPBYTE)pTCPacketInfo.GetAt(nItem[0] - 1)))
				{
					GlobalFree(pProcessInfo);
					delete pTCPacket;
					continue;
				}
				delete pTCPacket;
			}
		}
		for (; nItem[0] < nItems[0]; nItem[0]++)
		{
			if ((pItem[0] = pItems.GetAt(nItem[0])))
			{
				if (pItem[0]->GetStatus() != TCITEM_STATUS_NOTRELEASED  &&  pItem[0]->GetStatus() != TCITEM_STATUS_FAILEDRELEASE)
				{
					pItem[0]->SetResult((pItem[0]->GetResult() & ~(TCITEM_RESULT_PTV_GO | TCITEM_RESULT_PTV_WAIT)) | TCITEM_RESULT_PTV_FAIL);
					pItem[0]->SetStatus(TCITEM_STATUS_NOTRELEASED);
				}
			}
		}
		pTCPackets[0].RemoveAll();
		pTCPackets[1].RemoveAll();
		pTCPacketInfo.RemoveAll();
		SetProcessData(nProcessInfo[0]);
	}
	if (Lock())
	{
		if (IsCommandHandler())
		{
			for (nItem[0] = 0, nItems[0] = (INT)pTCPackets[0].GetSize(); nItem[0] < nItems[0]; nItem[0]++)
			{
				if ((pTCPacket = ((pItem[0] = ((pProcessInfo = (LPBYTE)pTCPacketInfo.GetAt(nItem[0]))) ? (CTCItem *)pTCPackets[1].GetAt(nItem[0]) : (CTCItem *)NULL)) ? (CTCPacket *)pTCPackets[0].GetAt(nItem[0]) : (CTCPacket *)NULL) && !pTCPacket->IsControlFrame() && !pTCPacket->IsControlSegment())
				{
					for (pTCPacket->SetTimeTag(CTimeTag()), nReleaseIDs.RemoveAll(); m_pTCProcessEngine->DetectTCServiceLevel() == TCSERVICELEVEL_TRANSFERFRAMES && m_pTCProcessEngine->GenerateTCTransferFrames(GetDatabase(), pTCPacket, pProcessInfo, pTCTransferFrames); )
					{
						for (nTransferFrame = 0, nTransferFrames = (INT)pTCTransferFrames.GetSize(); nTransferFrame < nTransferFrames; nTransferFrame++)
						{
							if ((pTCTransferFrame = pTCTransferFrames.GetAt(nTransferFrame)))
							{
								if ((nReleaseID = m_cTCDevice.Send(*pTCTransferFrame)) >= 0)
								{
									nReleaseIDs.Add(nReleaseID);
									continue;
								}
							}
							break;
						}
						if (nTransferFrame == nTransferFrames)
						{
							UpdateProcessData(pProcessInfo);
							break;
						}
						nReleaseIDs.RemoveAll();
						break;
					}
					if (m_pTCProcessEngine->DetectTCServiceLevel() == TCSERVICELEVEL_PACKETS)
					{
						if ((nReleaseID = m_cTCDevice.Send(*pTCPacket)) >= 0)
						{
							nReleaseIDs.Add(nReleaseID);
							UpdateProcessData(pProcessInfo);
						}
					}
					if (nReleaseIDs.GetSize() > 0)
					{
						for (nItem[1] = (pItem[0]->GetFlags() & TCITEM_LINKAGEFLAG_BLOCKED) ? pItems.Find(pItem[0]) : -1, nItems[1] = (INT)pItems.GetSize(), pItem[0]->SetReleaseIDs(nReleaseIDs), pItem[0]->SetReleaseTime(pTCPacket->GetTimeTag()), pItem[0]->SetStatus(TCITEM_STATUS_RELEASED), nCount = 0; nItem[1] < nItems[1]; nItem[1]++)
						{
							if ((pItem[1] = pItems.GetAt(nItem[1])) && pItem[0]->GetReleaseBlock() == pItem[1]->GetReleaseBlock() && pItem[0]->GetReleaseBlockID() + nCount == pItem[1]->GetReleaseBlockID())
							{
								pItem[1]->SetReleaseTime(pTCPacket->GetTimeTag());
								pItem[1]->SetStatus(TCITEM_STATUS_RELEASED);
								nCount++;
								continue;
							}
							break;
						}
						continue;
					}
				}
				if ((pItem[0] = (CTCItem *)pTCPackets[1].GetAt(nItem[0])))
				{
					for (nCommandSource = 0, nCommandSources = (GetCommandSources(pCommandSources)) ? (INT)pCommandSources.GetSize() : 0; nCommandSource < nCommandSources; nCommandSource++)
					{
						if ((pCommandSourceInfo = pCommandSources.GetAt(nCommandSource)) && (pItem[0]->GetComputerName().CompareNoCase(pCommandSourceInfo->GetComputerName()) || pItem[0]->GetSourceType() != pCommandSourceInfo->GetSourceType()))
						{
							pCommandSourceInfo->SetTelecommandingState(pCommandSourceInfo->GetTelecommandingState() | TCSERVICE_COMMANDSOURCESTATE_DISABLED);
							continue;
						}
					}
					if (nCommandSource == nCommandSources  &&  nCommandSources > 0) SetCommandSources(pCommandSources);
				}
				for (nItem[1] = nItem[0], nItems[1] = nItems[0]; nItem[1] < nItems[1]; nItem[1]++)
				{
					if ((pItem[1] = (CTCItem *)pTCPackets[1].GetAt(nItem[1])) != (CTCItem *)NULL)
					{
						pItem[1]->SetStatus((pItem[1]->GetStatus() < TCITEM_STATUS_NOTRELEASED) ? TCITEM_STATUS_NOTRELEASED : pItem[1]->GetStatus());
						continue;
					}
				}
				break;
			}
			for (nItem[0] = 0, nItems[0] = (INT)pItems.GetSize(); nItem[0] < nItems[0]; nItem[0]++)
			{
				if ((pItem[0] = pItems.GetAt(nItem[0])) && (pItem[0]->GetType() == TCITEM_TYPE_PROCEDURE || pItem[0]->GetStatus() == TCITEM_STATUS_NOTRELEASED || pItem[0]->GetStatus() == TCITEM_STATUS_FAILEDRELEASE))
				{
					if (pItem[0]->GetSourceType() == TCITEM_SOURCETYPE_PROCEDURESMONITOR && (pItem[0]->GetStatus() == TCITEM_STATUS_NOTRELEASED || pItem[0]->GetStatus() == TCITEM_STATUS_FAILEDRELEASE))
					{
						for (nIndex = 0, nCount = (INT)m_nTCModuleIDs.GetSize(); nIndex < nCount; nIndex++)
						{
							if (m_nTCModuleIDs.GetAt(nIndex) == (UINT)pItem[0]->GetVerificationProcessID())
							{
								m_pTCEnvironment->FreeTCProcedure(pItem[0]->GetVerificationProcessID());
								m_nTCModuleIDs.RemoveAt(nIndex);
								m_pTCModules.RemoveAt(nIndex);
								break;
							}
						}
						for (pItem[0]->SetReleaseTime(-pItem[0]->GetReleaseTime().GetTime()); pItem[0]->GetVerificationHandles(hResults[0], hResults[1]); )
						{
							SetEvent(hResults[1]);
							break;
						}
						continue;
					}
					if (pItem[0]->GetStatus() != TCITEM_STATUS_RELEASED) pItem[0]->SetReleaseTime(-pItem[0]->GetReleaseTime().GetTime());
				}
			}
			for (nItem[0] = 0, nItems[0] = (INT)pItems.GetSize(), bInterlocks = FALSE; nItem[0] < nItems[0]; nItem[0]++)
			{
				if ((pInterlock[0] = ((pItem[0] = pItems.GetAt(nItem[0]))) ? m_pTCInterlocks.GetAt(m_pTCInterlocks.Find(pItem[0]->GetComputerName(), pItem[0]->GetSourceType(), pItem[0]->GetInterlock())) : (CTCInterlock *)NULL))
				{
					if (pInterlock[0]->GetStage() != TCINTERLOCK_STAGE_RECEPTION  &&  pInterlock[0]->GetStage() != TCINTERLOCK_STAGE_TRANSMISSION)
					{
						if (pItem[0]->GetFlags() & TCITEM_CHECKFLAG_DISABLECEV)
						{
							pInterlock[0]->SetState(TCINTERLOCK_STATE_IDLE);
							bInterlocks = TRUE;
							continue;
						}
						if (pItem[0]->GetFlags() & TCITEM_CHECKFLAG_OVERRIDECEV)
						{
							pInterlock[0]->SetState(TCINTERLOCK_STATE_SUCCESS);
							bInterlocks = TRUE;
							continue;
						}
						if (GetCommandSourceTelecommandingChecks(pItem[0]->GetComputerName(), pItem[0]->GetSourceType()) & TCITEM_CHECKFLAG_DISABLECEV)
						{
							pInterlock[0]->SetState(TCINTERLOCK_STATE_IDLE);
							bInterlocks = TRUE;
							continue;
						}
						if (GetCommandSourceTelecommandingChecks(pItem[0]->GetComputerName(), pItem[0]->GetSourceType()) & TCITEM_CHECKFLAG_OVERRIDECEV)
						{
							pInterlock[0]->SetState(TCINTERLOCK_STATE_SUCCESS);
							bInterlocks = TRUE;
							continue;
						}
						if (pItem[0]->GetExeVerGroupRef() >= 0)
						{
							pInterlock[0]->SetState(TCINTERLOCK_STATE_PENDING);
							bInterlocks = TRUE;
						}
						continue;
					}
					if ((pItem[0]->GetStatus() == TCITEM_STATUS_RELEASED  &&  pInterlock[0]->GetState() != TCINTERLOCK_STATE_PENDING) || ((pItem[0]->GetStatus() == TCITEM_STATUS_NOTRELEASED || pItem[0]->GetStatus() == TCITEM_STATUS_FAILEDRELEASE) && pInterlock[0]->GetState() != TCINTERLOCK_STATE_FAILURE))
					{
						for (pInterlock[0]->SetState((pItem[0]->GetStatus() == TCITEM_STATUS_RELEASED) ? TCINTERLOCK_STATE_PENDING : TCINTERLOCK_STATE_FAILURE); pItem[0]->GetReleaseIDs(nReleaseIDs) > 0; )
						{
							pInterlock[0]->SetReleaseIDs(nReleaseIDs);
							break;
						}
						bInterlocks = TRUE;
					}
				}
			}
			if ((nInterlocks = (INT)m_pTCInterlocks.GetSize()) > 0)
			{
				for (nInterlock = 0, GetCommandHandlerContents(pInterlockItems); nInterlock < nInterlocks; nInterlock++)
				{
					if ((pInterlock[0] = m_pTCInterlocks.GetAt(nInterlock)) && pInterlock[0]->GetState() == TCINTERLOCK_STATE_PENDING)
					{
						for (nItem[1] = 0, nItems[1] = (INT)pInterlockItems.GetSize(); nItem[1] < nItems[1]; nItem[1]++)
						{
							if ((pInterlock[1] = ((pItem[1] = pInterlockItems.GetAt(nItem[1]))) ? m_pTCInterlocks.GetAt(m_pTCInterlocks.Find(pItem[1]->GetComputerName(), pItem[1]->GetSourceType(), pItem[1]->GetInterlock())) : (CTCInterlock *)NULL) && pInterlock[0]->GetName() == pInterlock[1]->GetName()) break;
							continue;
						}
						if (nItem[1] == nItems[1])
						{
							pInterlock[0]->SetState(TCINTERLOCK_STATE_IDLE);
							bInterlocks = TRUE;
						}
					}
				}
			}
			for (m_pTCReleaseThread->Update(pItems, m_pTCInterlocks, pInterlockItems), m_pTCInterfaceThread->ReleaseTelecommands(pItems), m_pTCVerificationThread->Update(pItems); bInterlocks; )
			{
				for (m_pTCInterfaceThread->UpdateTCInterlocks(m_pTCInterlocks); pInterlockItems.GetSize() > 0; )
				{
					m_pTCInterfaceThread->UpdateTelecommands(pInterlockItems, FALSE);
					break;
				}
				break;
			}
			for (; pItems.GetSize() > 0 || bInterlocks; )
			{
				m_pTCInterfaceThread->UpdateCommandHandler(((pItems.GetSize() > 0) ? TCSERVICE_COMMANDINTERFACE_TELECOMMANDSUPDATE : 0) | ((bInterlocks) ? TCSERVICE_COMMANDINTERFACE_INTERLOCKSUPDATE : 0));
				break;
			}
			for (nItem[0] = 0, nItems[0] = (INT)pTCPackets[0].GetSize(); nItem[0] < nItems[0]; nItem[0]++)
			{
				if ((pTCPacket = (CTCPacket *)pTCPackets[0].GetAt(nItem[0])))
				{
					if ((pProcessInfo = (LPBYTE)pTCPacketInfo.GetAt(nItem[0])))
					{
						GlobalFree(pProcessInfo);
						delete pTCPacket;
						continue;
					}
					delete pTCPacket;
				}
			}
			UpdateArchives(pItems);
		}
		if (pItems.GetSize() > 0)
		{
			if (m_pTCManualStackWnd) m_pTCManualStackWnd->UpdateTelecommands(pItems);
			if (m_pTCAutomaticStackWnd) m_pTCAutomaticStackWnd->UpdateTelecommands(pItems);
			if (m_pTCOnBoardMemoryImagesWnd) m_pTCOnBoardMemoryImagesWnd->UpdateMonitoring(pItems);
			if (m_pTCHistoryWnd) m_pTCHistoryWnd->UpdateTelecommands(pItems);
			Unlock();
			return TRUE;
		}
		Unlock();
	}
	return FALSE;
}

BOOL CTCProcessThread::UpdateTelecommands(CONST CTCItems &pItems, BOOL bAll)
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	INT  nCount;
	INT  nInterlock;
	INT  nInterlocks;
	BOOL  bInterlocks;
	UINT  nState;
	UINT  nReason;
	CTCItem  *pItem;
	CTCItems  pInterlockItems;
	CTCInterlock  *pInterlock[2];
	CComputerToken  cComputerToken;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (UpdateTelecommands(cComputerToken.GetComputerName(), pItems, bAll); IsCommandHandler(); )
	{
		for (nItem = 0, nItems = (INT)pItems.GetSize(), m_pTCInterfaceThread->UpdateTelecommands(pItems, bAll); nItem < nItems; nItem++)
		{
			if ((pItem = pItems.GetAt(nItem)) && pItem->GetSourceType() == TCITEM_SOURCETYPE_PROCEDURESMONITOR  &&  pItem->GetVerificationModule() != (HINSTANCE)NULL)
			{
				if (((pItem->GetStatus() == TCITEM_STATUS_RELEASED || pItem->GetStatus() == TCITEM_STATUS_SENT || pItem->GetStatus() == TCITEM_STATUS_UPLINKED) && (pItem->GetResult() & (TCITEM_RESULT_CEV_PASSED | TCITEM_RESULT_CEV_FAILED | TCITEM_RESULT_CEV_UNVERIFIED))) || pItem->GetStatus() == TCITEM_STATUS_NOTRELEASED || pItem->GetStatus() == TCITEM_STATUS_FAILEDRELEASE || pItem->GetStatus() == TCITEM_STATUS_FAILEDSEND || pItem->GetStatus() == TCITEM_STATUS_FAILEDUPLINK)
				{
					for (nIndex = 0, nCount = (INT)m_nTCModuleIDs.GetSize(); nIndex < nCount; nIndex++)
					{
						if (m_nTCModuleIDs.GetAt(nIndex) == (UINT)pItem->GetVerificationProcessID())
						{
							m_pTCEnvironment->FreeTCProcedure(pItem->GetVerificationProcessID());
							m_nTCModuleIDs.RemoveAt(nIndex);
							m_pTCModules.RemoveAt(nIndex);
							break;
						}
					}
				}
			}
		}
		for (nItem = 0, bInterlocks = FALSE; nItem < nItems; nItem++)
		{
			if ((pInterlock[0] = ((pItem = pItems.GetAt(nItem)) && (pItem->GetStatus() == TCITEM_STATUS_RELEASED || pItem->GetStatus() == TCITEM_STATUS_SENT || pItem->GetStatus() == TCITEM_STATUS_UPLINKED)) ? m_pTCInterlocks.GetAt(m_pTCInterlocks.Find(pItem->GetComputerName(), pItem->GetSourceType(), pItem->GetInterlock())) : (CTCInterlock *)NULL))
			{
				for (nState = 0; (pInterlock[0]->GetStage() == TCINTERLOCK_STAGE_ACCEPTANCE && ((pItem->GetVerificationStageState(MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_ACCEPTANCE), nState, nReason) && (nState == TCITEM_RESULT_CEV_PASSED || nState == TCITEM_RESULT_CEV_FAILED || nState == TCITEM_RESULT_CEV_UNVERIFIED)) || (!pItem->GetVerificationStageState(MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_ACCEPTANCE), nState, nReason) && (pItem->GetResult() & TCITEM_RESULT_CEV_UNVERIFIED)))) || (pInterlock[0]->GetStage() == TCINTERLOCK_STAGE_START && ((pItem->GetVerificationStageState(MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_START), nState, nReason) && (nState == TCITEM_RESULT_CEV_PASSED || nState == TCITEM_RESULT_CEV_FAILED || nState == TCITEM_RESULT_CEV_UNVERIFIED)) || (!pItem->GetVerificationStageState(MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_START), nState, nReason) && (pItem->GetResult() & TCITEM_RESULT_CEV_UNVERIFIED)))) || (pInterlock[0]->GetStage() == TCINTERLOCK_STAGE_PROGRESS && ((pItem->GetVerificationStageState(MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_PROGRESS), nState, nReason) && (nState == TCITEM_RESULT_CEV_PASSED || nState == TCITEM_RESULT_CEV_FAILED || nState == TCITEM_RESULT_CEV_UNVERIFIED)) || (!pItem->GetVerificationStageState(MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_PROGRESS), nState, nReason) && (pItem->GetResult() & TCITEM_RESULT_CEV_UNVERIFIED)))) || (pInterlock[0]->GetStage() == TCINTERLOCK_STAGE_COMPLETION && ((pItem->GetVerificationStageState(MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_COMPLETION), nState, nReason) && (nState == TCITEM_RESULT_CEV_PASSED || nState == TCITEM_RESULT_CEV_FAILED || nState == TCITEM_RESULT_CEV_UNVERIFIED)) || (!pItem->GetVerificationStageState(MAKETCEXEVEROVERALLSTAGEID(TCVERIFICATIONSTAGE_COMPLETION), nState, nReason) && (pItem->GetResult() & TCITEM_RESULT_CEV_UNVERIFIED)))); )
				{
					pInterlock[0]->SetState((nState & TCITEM_RESULT_CEV_PASSED) ? TCINTERLOCK_STATE_SUCCESS : TCINTERLOCK_STATE_FAILURE);
					bInterlocks = TRUE;
					break;
				}
			}
		}
		if ((nInterlocks = (INT)m_pTCInterlocks.GetSize()) > 0)
		{
			for (nInterlock = 0, GetCommandHandlerContents(pInterlockItems); nInterlock < nInterlocks; nInterlock++)
			{
				if ((pInterlock[0] = m_pTCInterlocks.GetAt(nInterlock)) && pInterlock[0]->GetState() == TCINTERLOCK_STATE_PENDING)
				{
					for (nItem = 0, nItems = (INT)pInterlockItems.GetSize(); nItem < nItems; nItem++)
					{
						if ((pInterlock[1] = ((pItem = pInterlockItems.GetAt(nItem))) ? m_pTCInterlocks.GetAt(m_pTCInterlocks.Find(pItem->GetComputerName(), pItem->GetSourceType(), pItem->GetInterlock())) : (CTCInterlock *)NULL) && pInterlock[0]->GetName() == pInterlock[1]->GetName()) break;
						continue;
					}
					if (nItem == nItems)
					{
						pInterlock[0]->SetState(TCINTERLOCK_STATE_IDLE);
						bInterlocks = TRUE;
					}
				}
			}
		}
		if (bInterlocks)
		{
			for (m_pTCReleaseThread->Update(m_pTCInterlocks, pInterlockItems), m_pTCInterfaceThread->UpdateTCInterlocks(m_pTCInterlocks); pInterlockItems.GetSize() > 0; )
			{
				m_pTCInterfaceThread->UpdateTelecommands(pInterlockItems, FALSE);
				break;
			}
			m_pTCInterfaceThread->UpdateCommandHandler(TCSERVICE_COMMANDINTERFACE_INTERLOCKSUPDATE);
		}
		if (!bAll)
		{
			UpdateArchives(pItems);
			return TRUE;
		}
		break;
	}
	return TRUE;
}
VOID CTCProcessThread::UpdateTelecommands(LPCTSTR pszOriginator, CONST CTCItems &pItems, BOOL bAll)
{
	INT  nItem[2];
	INT  nItems[2];
	INT  cbQueuedSize;
	UINT  nSubScheduleID;
	UINT  nBlockOffset;
	UINT  nBlockBytes;
	CString  szType;
	CString  szName;
	CTCItem  *pItem[2];
	CTimeTag  tTime[2];
	CPtrArray  pQueues;
	CTCPacket  cTCPacket[2];
	CUIntArray  nBlockSizes;
	CByteArray  nPacketData[2];
	CTimeTagArray  tBlockTimes;
	CTCOnBoardBufferQueue  *pQueue;
	CDatabaseTCFunctions  pBlockedItems;
	COversamplingParameters  pOversamplingParameters;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (; IsCommandHandler() && lstrlen(pszOriginator) > 0 && bAll; )
	{
		SetCommandHandlerContents(pItems);
		break;
	}
	for (nItem[0] = 0, nItems[0] = (INT)pItems.GetSize(); nItem[0] < nItems[0]; nItem[0]++)
	{
		if ((pItem[0] = pItems.GetAt(nItem[0])) && (pItem[0]->GetStatus() == TCITEM_STATUS_RELEASED || pItem[0]->GetStatus() == TCITEM_STATUS_SENT || pItem[0]->GetStatus() == TCITEM_STATUS_UPLINKED))
		{
			if ((!pItem[0]->GetExecutionTime(tTime[0]) || tTime[0] <= tTime[1]) && (pItem[0]->GetResult() & TCITEM_RESULT_PEV_GO))
			{
				if (DecodeTCDiagnosticsOversamplingDump(pItem[0], pOversamplingParameters))
				{
					m_pTMEnvironment->Initialize(pOversamplingParameters);
					continue;
				}
			}
		}
	}
	for (nItem[0] = 0; nItem[0] < nItems[0]; nItem[0]++)
	{
		if ((pItem[0] = pItems.GetAt(nItem[0])) && (pItem[0]->GetStatus() == TCITEM_STATUS_RELEASED || pItem[0]->GetStatus() == TCITEM_STATUS_SENT || pItem[0]->GetStatus() == TCITEM_STATUS_UPLINKED) && pItem[0]->GetTCPacket(nPacketData[0]) > 0 && cTCPacket[0].Unmap(nPacketData[0]))
		{
			if ((pQueue = (FindTCOnBoardBufferQueue(&cTCPacket[0], szType, szName, nSubScheduleID)) ? m_pTCOnBoardBufferQueues.GetAt(m_pTCOnBoardBufferQueues.Find(szType, szName, nSubScheduleID)) : (CTCOnBoardBufferQueue *)NULL))
			{
				for (nItem[1] = 0, nItems[1] = (INT)pQueue->GetSize(); nItem[1] < nItems[1]; nItem[1]++)
				{
					if ((pItem[1] = pQueue->GetAt(nItem[1])) && pItem[1]->GetTCPacket(nPacketData[1]) > 0 && cTCPacket[1].Unmap(nPacketData[1]))
					{
						if (cTCPacket[0].GetAPID() == cTCPacket[1].GetAPID() && cTCPacket[0].GetTCID() == cTCPacket[1].GetTCID() && cTCPacket[0].GetSequenceCount() == cTCPacket[1].GetSequenceCount()) break;
						continue;
					}
				}
				if (nItem[1] < nItems[1])
				{
					if ((pItem[1] = pQueue->GetAt(nItem[1])))
					{
						if (((pItem[0]->GetResult() & (TCITEM_RESULT_CEV_PASSED | TCITEM_RESULT_CEV_UNKNOWN)) && cTCPacket[1].GetTCType() != TCPACKET_TCTYPE_FIRSTSTEP && (!pItem[1]->GetExecutionTime(tTime[0]) || tTime[0] <= tTime[1])) || (pItem[0]->GetResult() & (TCITEM_RESULT_CEV_FAILED | TCITEM_RESULT_CEV_UNVERIFIED)))
						{
							pQueue->SetCount((pItem[1]->GetQueuedSize() <= pQueue->GetCount() && pQueue->GetCount() != (UINT)-1) ? (pQueue->GetCount() - pItem[1]->GetQueuedSize()) : 0);
							pQueue->SetUpdateTime(tTime[1]);
							pQueue->RemoveAt(nItem[1]);
							pQueues.Add(pQueue);
							delete pItem[1];
							continue;
						}
						for (cbQueuedSize = pItem[1]->GetQueuedSize(), pItem[1]->GetExecutionTime(tTime[0]); pItem[1]->Copy(pItem[0]); )
						{
							pItem[1]->SetQueuedSize(cbQueuedSize);
							pItem[1]->SetExecutionTime(tTime[0]);
							break;
						}
						pQueues.Add(pQueue);
					}
					continue;
				}
				if ((pItem[0]->GetResult() & (TCITEM_RESULT_CEV_IDLE | TCITEM_RESULT_CEV_PENDING | TCITEM_RESULT_CEV_PASSED | TCITEM_RESULT_CEV_FAILED | TCITEM_RESULT_CEV_UNKNOWN | TCITEM_RESULT_CEV_UNVERIFIED)) == 0)
				{
					for (pItem[0]->GetReleaseBlockedItems(pBlockedItems); ExpandTCOnBoardBufferQueueEntry(&cTCPacket[0], nBlockOffset, nBlockBytes, nBlockSizes, tBlockTimes); )
					{
						if (nBlockSizes.GetSize() == 1)
						{
							if ((pItem[1] = new CTCItem))
							{
								if (pItem[1]->Copy(pItem[0]) && pQueue->Add(pItem[1]) >= 0)
								{
									for (pItem[1]->SetQueuedSize(nBlockSizes.GetAt(nBlockSizes.GetUpperBound())); (tTime[0] = (!pItem[1]->GetExecutionTime(tTime[0])) ? tBlockTimes.GetAt((INT)tBlockTimes.GetUpperBound()) : 0) > 0; )
									{
										pItem[1]->SetExecutionTime(tTime[0]);
										break;
									}
									pQueue->SetCount((pQueue->GetCount() != (UINT)-1) ? (pQueue->GetCount() + pItem[1]->GetQueuedSize()) : pItem[1]->GetQueuedSize());
									pQueue->SetUpdateTime(tTime[1]);
									pQueues.Add(pQueue);
									break;
								}
								delete pItem[1];
							}
							pQueue->Alert(TCONBOARDBUFFERQUEUE_ALERTTYPE_ERROR, 0, STRING(IDS_TELECOMMANDONBOARDBUFFERQUEUE_MESSAGE_UPDATEFAILURE));
							break;
						}
						for (nItem[1] = 0, nItems[1] = (pBlockedItems.GetSize() == nBlockSizes.GetSize()) ? (INT)pBlockedItems.GetSize() : -1, cTCPacket[0].GetData(nPacketData[0]); nItem[1] < nItems[1]; nItem[1]++)
						{
							for (nPacketData[1].SetSize(min(nBlockBytes*nBlockSizes.GetAt(nItem[1]), nPacketData[0].GetSize() - nBlockBytes*nBlockOffset)); nBlockBytes*nBlockOffset < (UINT)nPacketData[0].GetSize(); )
							{
								CopyMemory(nPacketData[1].GetData(), nPacketData[0].GetData() + nBlockBytes*nBlockOffset, nPacketData[1].GetSize());
								break;
							}
							if ((pItem[1] = new CTCItem))
							{
								if (pItem[1]->CDatabaseTCFunction::Copy(pBlockedItems.GetAt(nItem[1])) && pItem[1]->SetTCPacket(nPacketData[1]) && pQueue->Add(pItem[1]) >= 0)
								{
									for (pItem[1]->SetQueuedSize(nBlockSizes.GetAt(nItem[1])), nBlockOffset += nBlockSizes.GetAt(nItem[1]); (tTime[0] = tBlockTimes.GetAt((INT)tBlockTimes.GetUpperBound())) > 0; )
									{
										pItem[1]->SetExecutionTime(tTime[0]);
										break;
									}
									pQueue->SetCount((pQueue->GetCount() != (UINT)-1) ? (pQueue->GetCount() + pItem[1]->GetQueuedSize()) : pItem[1]->GetQueuedSize());
									continue;
								}
								delete pItem[1];
							}
							pQueue->Alert(TCONBOARDBUFFERQUEUE_ALERTTYPE_ERROR, 0, STRING(IDS_TELECOMMANDONBOARDBUFFERQUEUE_MESSAGE_UPDATEFAILURE));
							break;
						}
						if (nItems[1] > 0)
						{
							pQueue->SetUpdateTime(tTime[1]);
							pQueues.Add(pQueue);
						}
						break;
					}
				}
			}
		}
	}
	for (UpdateQueues(pQueues); m_pTCManualStackWnd; )
	{
		m_pTCManualStackWnd->UpdateTelecommands(pItems, bAll);
		break;
	}
	if (m_pTCAutomaticStackWnd) m_pTCAutomaticStackWnd->UpdateTelecommands(pItems, bAll);
	if (m_pTCOnBoardMemoryImagesWnd) m_pTCOnBoardMemoryImagesWnd->UpdateMonitoring(pItems);
	if (m_pTCHistoryWnd) m_pTCHistoryWnd->UpdateTelecommands(pItems);
}

BOOL CTCProcessThread::AcknowledgeTelecommands(CONST CTCItems &pItems)
{
	INT  nItem;
	INT  nItems;
	CTCItem  *pItem;
	CTCItems  pAcknowledgeItems;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (IsCommandHandler())
	{
		for (nItem = 0, nItems = (m_pTCVerificationThread->Acknowledge(pItems) && pAcknowledgeItems.Copy(&pItems)) ? (INT)pAcknowledgeItems.GetSize() : -1; nItem < nItems; nItem++)
		{
			if ((pItem = pAcknowledgeItems.GetAt(nItem)) && (pItem->GetFlags() & TCITEM_ACKNOWLEDGEFLAG_ALL) != TCITEM_ACKNOWLEDGEFLAG_ALL)
			{
				pItem->SetFlags(pItem->GetFlags() | TCITEM_ACKNOWLEDGEFLAG_ALL);
				continue;
			}
			pAcknowledgeItems.RemoveAt(nItem);
			delete pItem;
			nItems--;
			nItem--;
		}
		if (pAcknowledgeItems.GetSize() > 0) UpdateTelecommands(pAcknowledgeItems, FALSE);
		return((nItem == nItems) ? TRUE : FALSE);
	}
	return m_pTCInterfaceThread->AcknowledgeTelecommands(pItems);
}

BOOL CTCProcessThread::DiscardTelecommands(CONST CTCItems &pItems)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return((IsCommandHandler()) ? m_pTCVerificationThread->Discard(pItems) : m_pTCInterfaceThread->DiscardTelecommands(pItems));
}

BOOL CTCProcessThread::ExecuteTelecommand(CONST CTCItem *pItem)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_pTCInterfaceThread->ExecuteTelecommand(pItem);
}
BOOL CTCProcessThread::ExecuteTelecommand(LPCTSTR pszOriginator, CONST CTCItem *pItem)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return((m_pTCProceduresMonitorWnd) ? m_pTCProceduresMonitorWnd->UpdateProcedure(pItem) : FALSE);
}

BOOL CTCProcessThread::GenerateTCPackets(CONST CDatabaseTCFunction *pFunction, CONST CDatabaseTCPacket *pPacket, LPCTSTR pszMemoryPatch, BOOL bTimeTagged, BOOL b2ndStep, BOOL bBlocked, BOOL bExample, CDatabaseTCFunctions &pFunctions, CDatabaseTCPackets &pPackets) CONST
{
	if (m_pTMEnvironment->Lock())
	{
		if (m_pTCEnvironment->Lock())
		{
			if (m_pTCProcessEngine->GenerateTCPackets(GetDatabase(), pFunction, pPacket, m_pTMEnvironment, m_pTCEnvironment, pszMemoryPatch, bTimeTagged, b2ndStep, bBlocked, bExample, pFunctions, pPackets))
			{
				m_pTCEnvironment->Unlock();
				m_pTMEnvironment->Unlock();
				return TRUE;
			}
			m_pTCEnvironment->Unlock();
		}
		m_pTMEnvironment->Unlock();
	}
	return FALSE;
}

BOOL CTCProcessThread::InitializeTCPacket(CONST CDatabaseTCFunction *pFunction, CONST CDatabaseTCPacket *pPacket, CTCPacket *pTCPacket, CONST CTimeTag &tExecutionTime, BOOL bBlocked, BOOL bExample) CONST
{
	if (m_pTMEnvironment->Lock())
	{
		if (m_pTCEnvironment->Lock())
		{
			if (m_pTCProcessEngine->InitializeTCPacket(GetDatabase(), m_pTMEnvironment, m_pTCEnvironment, pFunction, pPacket, pTCPacket, tExecutionTime, bBlocked, bExample))
			{
				m_pTCEnvironment->Unlock();
				m_pTMEnvironment->Unlock();
				return TRUE;
			}
			m_pTCEnvironment->Unlock();
		}
		m_pTMEnvironment->Unlock();
	}
	return FALSE;
}
BOOL CTCProcessThread::InitializeTCPacket(CTCItem *pItem, CDatabaseTCPacket *pPacket) CONST
{
	CString  szProcedure;
	CString  szMemoryPatch;
	BOOL(__cdecl *pInitThreadTCFunction)(INT nID, LPCTSTR pszThread, LPCTSTR pszStep, INT nEntry, BOOL bExpanded, CDatabaseTCFunction *pTCFunction, CDatabaseTCPacket *pTCPacket, CString &szMemoryPatch);

	if (pItem->GetSourceType() == TCITEM_SOURCETYPE_PROCEDURESMONITOR)
	{
#ifndef UNICODE
		szProcedure = STRING(IDS_EXPORTINTERFACE_INITIALIZETCPROCEDUREFUNCTIONPARAMETERS);
#else
		WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_INITIALIZETCPROCEDUREFUNCTIONPARAMETERS), -1, (LPSTR)szProcedure.GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_INITIALIZETCPROCEDUREFUNCTIONPARAMETERS))), lstrlen(STRING(IDS_EXPORTINTERFACE_INITIALIZETCPROCEDUREFUNCTIONPARAMETERS)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
		szProcedure.ReleaseBuffer();
#endif
		if ((pInitThreadTCFunction = (BOOL(__cdecl *)(INT nID, LPCTSTR pszThread, LPCTSTR pszStep, INT nEntry, BOOL bExpanded, CDatabaseTCFunction *pTCFunction, CDatabaseTCPacket *pTCPacket, CString &szMemoryPatch)) GetProcAddress(pItem->GetVerificationModule(), (LPCSTR)(LPCTSTR)szProcedure)))
		{
			if ((*pInitThreadTCFunction)(pItem->GetVerificationProcessID(), pItem->GetVerificationThread(), pItem->GetVerificationStep(), (pItem->GetMembershipID() != (UINT)-1) ? (pItem->GetMembershipID() + 1) : -1, FALSE, pItem, pPacket, szMemoryPatch))
			{
				pItem->SetMemoryPatch(szMemoryPatch);
				return TRUE;
			}
		}
		return FALSE;
	}
	return TRUE;
}
BOOL CTCProcessThread::InitializeTCPacket(CONST CTCItem *pItem, CDatabaseTCFunction *pFunction, CDatabaseTCPacket *pPacket, INT nSubEntry) CONST
{
	CString  szProcedure;
	CString  szMemoryPatch;
	BOOL(__cdecl *pInitThreadTCFunction)(INT nID, LPCTSTR pszThread, LPCTSTR pszStep, INT nEntry, BOOL bExpanded, CDatabaseTCFunction *pTCFunction, CDatabaseTCPacket *pTCPacket, CString &szMemoryPatch);

	if (pItem->GetSourceType() == TCITEM_SOURCETYPE_PROCEDURESMONITOR)
	{
		if (!nSubEntry)
		{
#ifndef UNICODE
			szProcedure = STRING(IDS_EXPORTINTERFACE_INITIALIZETCPROCEDUREFUNCTIONPARAMETERS);
#else
			WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_INITIALIZETCPROCEDUREFUNCTIONPARAMETERS), -1, (LPSTR)szProcedure.GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_INITIALIZETCPROCEDUREFUNCTIONPARAMETERS))), lstrlen(STRING(IDS_EXPORTINTERFACE_INITIALIZETCPROCEDUREFUNCTIONPARAMETERS)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
			szProcedure.ReleaseBuffer();
#endif
			return(((pInitThreadTCFunction = (BOOL(__cdecl *)(INT nID, LPCTSTR pszThread, LPCTSTR pszStep, INT nEntry, BOOL bExpanded, CDatabaseTCFunction *pTCFunction, CDatabaseTCPacket *pTCPacket, CString &szMemoryPatch)) GetProcAddress(pItem->GetVerificationModule(), (LPCSTR)(LPCTSTR)szProcedure))) ? (*pInitThreadTCFunction)(pItem->GetVerificationProcessID(), pItem->GetVerificationThread(), pItem->GetVerificationStep(), (pItem->GetMembershipID() != (UINT)-1) ? (pItem->GetMembershipID() + 1) : -1, TRUE, pFunction, pPacket, szMemoryPatch) : FALSE);
		}
	}
	return TRUE;
}

BOOL CTCProcessThread::CollectTCPacket(CDatabaseTCFunction *pFunction, CTCPacket *pTCPacket, INT nBlockID) CONST
{
	return m_pTCProcessEngine->CollectTCPacket(GetDatabase(), m_pTMEnvironment, pFunction, pTCPacket, nBlockID);
}

BOOL CTCProcessThread::DecodeTCPacket(CONST CTCPacket *pTCPacket, CDatabaseTCFunction *pDatabaseTCFunction, CDatabaseTCFunctions &pDatabaseBlockedTCFunctions, CDatabaseTCPacket *pDatabaseTCPacket) CONST
{
	if (m_pTCEnvironment->Lock())
	{
		if (m_pTCProcessEngine->DecodeTCPacket(GetDatabase(), m_pTCEnvironment, pTCPacket, pDatabaseTCFunction, pDatabaseBlockedTCFunctions, pDatabaseTCPacket))
		{
			m_pTCEnvironment->Unlock();
			return TRUE;
		}
		m_pTCEnvironment->Unlock();
	}
	return FALSE;
}

BOOL CTCProcessThread::CheckTCFunctionExecutionTime(CONST CDatabaseTCFunction *pDatabaseTCFunction, CONST CDatabaseTCPacket *pDatabaseTCPacket, CONST CTimeTag &tExecutionTime) CONST
{
	return m_pTCProcessEngine->CheckTCFunctionExecutionTime(pDatabaseTCFunction, pDatabaseTCPacket, tExecutionTime);
}

BOOL CTCProcessThread::SetTCFunctionExecutionTimeOffsets(CONST CTimeSpan &tMin, CONST CTimeSpan &tMax)
{
	return m_pTCProcessEngine->SetTCFunctionExecutionTimeOffsets(tMin, tMax);
}

BOOL CTCProcessThread::GetTCFunctionExecutionTimeOffsets(CTimeSpan &tMin, CTimeSpan &tMax) CONST
{
	return m_pTCProcessEngine->GetTCFunctionExecutionTimeOffsets(tMin, tMax);
}

BOOL CTCProcessThread::SetTCFunctionParameterTimeOffsets(CONST CTimeSpan &tMin, CONST CTimeSpan &tMax)
{
	return m_pTCProcessEngine->SetTCFunctionParameterTimeOffsets(tMin, tMax);
}

BOOL CTCProcessThread::GetTCFunctionParameterTimeOffsets(CTimeSpan &tMin, CTimeSpan &tMax) CONST
{
	return m_pTCProcessEngine->GetTCFunctionParameterTimeOffsets(tMin, tMax);
}

BOOL CTCProcessThread::ConvertTCParameterValue(LPCTSTR pszTag, ULONGLONG nAttributes, LPCTSTR pszValue, ULONGLONG &nValue) CONST
{
	return m_pTCProcessEngine->ConvertTCParameterValue(GetDatabase(), pszTag, nAttributes, pszValue, nValue);
}
BOOL CTCProcessThread::ConvertTCParameterValue(CONST CDatabaseTCParameter *pDatabaseTCParameter, ULONGLONG &nValue) CONST
{
	return m_pTCProcessEngine->ConvertTCParameterValue(GetDatabase(), pDatabaseTCParameter, nValue);
}

BOOL CTCProcessThread::CheckTCParameterOolStatus(CONST CDatabaseTCParameter *pParameter, UINT &nOolStatus) CONST
{
	CTimeTag  tTime[2];
	ULONGLONG  nValue;
	CTimeSpan  tMinOffset;
	CTimeSpan  tMaxOffset;
	CTCParameter  *pTCParameter;
	CDatabaseTCParameter  cParameter;

	if (m_pTCEnvironment->Lock())
	{
		for (nOolStatus = TCPARAMETER_STATUS_NONE; !pParameter->GetConstValueAsText().IsEmpty(); )
		{
			if ((pParameter->GetAttributes() & TCPARAMETER_CODING_TIME) || GetDatabase()->TranslateTCParameterConstTime(pParameter->GetAttributes(), pParameter->GetConstValueAsText()) > 0)
			{
				nOolStatus = ((tTime[0] = GetDatabase()->TranslateTCParameterConstTime(pParameter->GetAttributes(), pParameter->GetConstValueAsText())) <= 0 || !GetTCFunctionParameterTimeOffsets(tMinOffset, tMaxOffset) || tTime[0].GetTimeInSeconds() < tTime[1].GetTimeInSeconds() + tMinOffset.GetTotalSeconds() || tTime[0].GetTimeInSeconds() > tTime[1].GetTimeInSeconds() + tMaxOffset.GetTotalSeconds()) ? TCPARAMETER_STATUS_TIMELIMIT : TCPARAMETER_STATUS_NOLIMIT;
				m_pTCEnvironment->Unlock();
				return TRUE;
			}
			if ((pTCParameter = m_pTCEnvironment->GetTCParameters()->GetAt(m_pTCEnvironment->GetTCParameters()->Find(pParameter->GetTag()))))
			{
				for (nOolStatus = TCPARAMETER_STATUS_VALUELIMIT; m_pTCProcessEngine->ConvertTCParameterValue(GetDatabase(), pParameter, nValue); )
				{
					nOolStatus = m_pTCProcessEngine->CheckTCParameterOolStatus(GetDatabase(), pParameter, pTCParameter, nValue);
					break;
				}
				m_pTCEnvironment->Unlock();
				return TRUE;
			}
			if ((pTCParameter = (cParameter.Copy(pParameter)) ? new CTCParameter : (CTCParameter *)NULL))
			{
				for (pTCParameter->SetTag(pParameter->GetTag()), pTCParameter->SetAttributes(((pParameter->GetAttributes() & (TCPARAMETER_VTYPE_RAW | TCPARAMETER_VTYPE_CALIBRATED | TCPARAMETER_VTYPE_CUSTOM)) != TCPARAMETER_VTYPE_CALIBRATED) ? ((pParameter->GetAttributes() & ~(TCPARAMETER_VTYPE_CALIBRATED | TCPARAMETER_VTYPE_CUSTOM | TCPARAMETER_CALIBRATION_NUMERICAL | TCPARAMETER_CALIBRATION_STATUS | TCPARAMETER_CALIBRATION_ENABLED)) | TCPARAMETER_VTYPE_RAW | TCPARAMETER_CALIBRATION_NONE) : pParameter->GetAttributes()), cParameter.SetAttributes(pTCParameter->GetAttributes()), nOolStatus = TCPARAMETER_STATUS_VALUELIMIT; m_pTCProcessEngine->ConvertTCParameterValue(GetDatabase(), &cParameter, nValue); )
				{
					nOolStatus = m_pTCProcessEngine->CheckTCParameterOolStatus(GetDatabase(), &cParameter, pTCParameter, nValue);
					break;
				}
				delete pTCParameter;
				break;
			}
			m_pTCEnvironment->Unlock();
			return FALSE;
		}
		m_pTCEnvironment->Unlock();
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcessThread::CheckTCFunctionElementOolStatus(CONST CDatabaseTCFunctionElement *pFunctionElement, UINT &nOolStatus) CONST
{
	CTimeTag  tTime[2];
	ULONGLONG  nValue;
	CTimeSpan  tMinOffset;
	CTimeSpan  tMaxOffset;
	CTCParameter  *pTCParameter;
	CDatabaseTCParameter  *pParameter[2];

	if (m_pTCEnvironment->Lock())
	{
		for (nOolStatus = TCPARAMETER_STATUS_NONE; (pFunctionElement->GetAttributes() & TCPARAMETER_CODING_TIME) || GetDatabase()->TranslateTCFunctionElementConstTime(pFunctionElement->GetAttributes(), pFunctionElement->GetConstValueAsText()) > 0; )
		{
			nOolStatus = (!pFunctionElement->GetConstValueAsText().IsEmpty()) ? (((tTime[0] = GetDatabase()->TranslateTCFunctionElementConstTime(pFunctionElement->GetAttributes(), pFunctionElement->GetConstValueAsText())) <= 0 || !GetTCFunctionParameterTimeOffsets(tMinOffset, tMaxOffset) || tTime[0].GetTimeInSeconds() < tTime[1].GetTimeInSeconds() + tMinOffset.GetTotalSeconds() || tTime[0].GetTimeInSeconds() > tTime[1].GetTimeInSeconds() + tMaxOffset.GetTotalSeconds()) ? TCPARAMETER_STATUS_TIMELIMIT : TCPARAMETER_STATUS_NOLIMIT) : TCPARAMETER_STATUS_NONE;
			m_pTCEnvironment->Unlock();
			return TRUE;
		}
		if ((pParameter[0] = new CDatabaseTCParameter))
		{
			if ((pTCParameter = ((pParameter[1] = GetDatabase()->GetTCParameters()->GetAt(pFunctionElement->GetRef())) && (pParameter[1]->GetAttributes() & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME)) == (pFunctionElement->GetAttributes() & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME)) && !pFunctionElement->GetConstValueAsText().IsEmpty()) ? m_pTCEnvironment->GetTCParameters()->GetAt(pFunctionElement->GetRef()) : (CTCParameter *)NULL) && pParameter[0]->Copy(pParameter[1]))
			{
				for (pParameter[0]->SetAttributes(pFunctionElement->GetAttributes()), pParameter[0]->SetConstValueAsText(pFunctionElement->GetConstValueAsText()), nOolStatus = TCPARAMETER_STATUS_VALUELIMIT; m_pTCProcessEngine->ConvertTCParameterValue(GetDatabase(), pParameter[0], nValue); )
				{
					nOolStatus = (pFunctionElement->GetWidth() == 8 * sizeof(nValue) || nValue < ((ULONGLONG)1) << pFunctionElement->GetWidth()) ? m_pTCProcessEngine->CheckTCParameterOolStatus(GetDatabase(), pParameter[0], pTCParameter, nValue) : TCPARAMETER_STATUS_VALUELIMIT;
					break;
				}
			}
			delete pParameter[0];
			m_pTCEnvironment->Unlock();
			return TRUE;
		}
		m_pTCEnvironment->Unlock();
	}
	return FALSE;
}

BOOL CTCProcessThread::CheckTCPacketParameterOolStatus(CONST CDatabaseTCPacketParameter *pPacketParameter, UINT &nOolStatus) CONST
{
	CTimeTag  tTime[2];
	ULONGLONG  nValue;
	CTimeSpan  tMinOffset;
	CTimeSpan  tMaxOffset;
	CTCParameter  *pTCParameter;
	CDatabaseTCParameter  *pParameter[2];

	if (m_pTCEnvironment->Lock())
	{
		for (nOolStatus = TCPARAMETER_STATUS_NONE; (pPacketParameter->GetAttributes() & TCPARAMETER_CODING_TIME) || GetDatabase()->TranslateTCPacketParameterConstTime(pPacketParameter->GetAttributes(), pPacketParameter->GetConstValueAsText()) > 0; )
		{
			nOolStatus = (!pPacketParameter->GetConstValueAsText().IsEmpty()) ? (((tTime[0] = GetDatabase()->TranslateTCPacketParameterConstTime(pPacketParameter->GetAttributes(), pPacketParameter->GetConstValueAsText())) <= 0 || !GetTCFunctionParameterTimeOffsets(tMinOffset, tMaxOffset) || tTime[0].GetTimeInSeconds() < tTime[1].GetTimeInSeconds() + tMinOffset.GetTotalSeconds() || tTime[0].GetTimeInSeconds() > tTime[1].GetTimeInSeconds() + tMaxOffset.GetTotalSeconds()) ? TCPARAMETER_STATUS_TIMELIMIT : TCPARAMETER_STATUS_NOLIMIT) : TCPARAMETER_STATUS_NONE;
			m_pTCEnvironment->Unlock();
			return TRUE;
		}
		if ((pParameter[0] = new CDatabaseTCParameter))
		{
			if ((pTCParameter = ((pParameter[1] = GetDatabase()->GetTCParameters()->GetAt(pPacketParameter->GetRef())) && (pParameter[1]->GetAttributes() & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME)) == (pPacketParameter->GetAttributes() & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME)) && !pPacketParameter->GetConstValueAsText().IsEmpty()) ? m_pTCEnvironment->GetTCParameters()->GetAt(pPacketParameter->GetRef()) : (CTCParameter *)NULL) && pParameter[0]->Copy(pParameter[1]))
			{
				for (pParameter[0]->SetAttributes(pPacketParameter->GetAttributes()), pParameter[0]->SetConstValueAsText(pPacketParameter->GetConstValueAsText()), nOolStatus = TCPARAMETER_STATUS_VALUELIMIT; m_pTCProcessEngine->ConvertTCParameterValue(GetDatabase(), pParameter[0], nValue); )
				{
					nOolStatus = (pPacketParameter->GetWidth() == 8 * sizeof(nValue) || nValue < ((ULONGLONG)1) << pPacketParameter->GetWidth()) ? m_pTCProcessEngine->CheckTCParameterOolStatus(GetDatabase(), pParameter[0], pTCParameter, nValue) : TCPARAMETER_STATUS_VALUELIMIT;
					break;
				}
			}
			delete pParameter[0];
			m_pTCEnvironment->Unlock();
			return TRUE;
		}
		m_pTCEnvironment->Unlock();
	}
	return FALSE;
}

BOOL CTCProcessThread::CheckTCProcedureArgumentOolStatus(CONST CDatabaseTCProcedureArgument *pArgument, UINT &nOolStatus) CONST
{
	INT  nIndex;
	CTimeTag  tTime[2];
	ULONGLONG  nValue;
	CTimeSpan  tMinOffset;
	CTimeSpan  tMaxOffset;
	CTCParameter  *pTCParameter;
	CDatabaseTCParameter  *pParameter;

	if (m_pTCEnvironment->Lock())
	{
		for (nOolStatus = TCPARAMETER_STATUS_NONE; pArgument->GetAttributes() & TCPARAMETER_CODING_TIME; )
		{
			nOolStatus = (!pArgument->GetConstValueAsText().IsEmpty()) ? (((tTime[0] = GetDatabase()->TranslateTCParameterConstTime(pArgument->GetAttributes(), pArgument->GetConstValueAsText())) <= 0 || !GetTCFunctionParameterTimeOffsets(tMinOffset, tMaxOffset) || tTime[0].GetTimeInSeconds() < tTime[1].GetTimeInSeconds() + tMinOffset.GetTotalSeconds() || tTime[0].GetTimeInSeconds() > tTime[1].GetTimeInSeconds() + tMaxOffset.GetTotalSeconds()) ? TCPARAMETER_STATUS_TIMELIMIT : TCPARAMETER_STATUS_NOLIMIT) : TCPARAMETER_STATUS_NONE;
			m_pTCEnvironment->Unlock();
			return TRUE;
		}
		if ((pTCParameter = ((pParameter = GetDatabase()->GetTCParameters()->GetAt((nIndex = GetDatabase()->GetTCParameters()->Find(pArgument->GetTag())))) && (pParameter->GetAttributes() & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME)) == (pArgument->GetAttributes() & (TCPARAMETER_CODING_BITPATTERN | TCPARAMETER_CODING_UNSIGNEDINTEGER | TCPARAMETER_CODING_SIGNEDINTEGER | TCPARAMETER_CODING_FLOATINGPOINT | TCPARAMETER_CODING_TIME)) && !pArgument->GetConstValueAsText().IsEmpty()) ? m_pTCEnvironment->GetTCParameters()->GetAt(nIndex) : (CTCParameter *)NULL))
		{
			nOolStatus = (m_pTCProcessEngine->ConvertTCParameterValue(GetDatabase(), pArgument, nValue)) ? m_pTCProcessEngine->CheckTCParameterOolStatus(GetDatabase(), pParameter, pTCParameter, nValue) : TCPARAMETER_STATUS_VALUELIMIT;
			m_pTCEnvironment->Unlock();
			return TRUE;
		}
		m_pTCEnvironment->Unlock();
	}
	return FALSE;
}

BOOL CTCProcessThread::CheckTCFunctionPreexecutionParameterGroup(INT nGroupID, CStringArray &szParameters) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (m_pTMEnvironment->Lock())
	{
		if (m_pTMEnvironment->GetType() != DATABASE_TYPE_NONE)
		{
			if (m_pTCProcessEngine->CheckTCFunctionPreexecutionParameterGroup(GetDatabase(), m_pTMEnvironment, nGroupID, szParameters))
			{
				m_pTMEnvironment->Unlock();
				return TRUE;
			}
		}
		m_pTMEnvironment->Unlock();
	}
	return FALSE;
}

BOOL CTCProcessThread::CheckTCFunctionExecutionParameterGroup(CONST CTCItem *pItem, INT nGroupID, INT nStageID, CONST CTimeTag &tStageStart, CONST CTimeSpan &tUncertainty, CStringArray &szParameters) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if (m_pTMEnvironment->Lock())
	{
		if (m_pTMEnvironment->GetType() != DATABASE_TYPE_NONE)
		{
			if (m_pTCProcessEngine->CheckTCFunctionExecutionParameterGroup(GetDatabase(), m_pTMEnvironment, pItem, nGroupID, nStageID, tStageStart, tUncertainty, szParameters))
			{
				m_pTMEnvironment->Unlock();
				return TRUE;
			}
		}
		m_pTMEnvironment->Unlock();
	}
	return FALSE;
}

BOOL CTCProcessThread::SetTCInterlocks(CONST CTCInterlocks &pInterlocks)
{
	INT  nInterlock[2];
	INT  nInterlocks[2];
	CTCInterlock  *pCommandInterlock[2];
	CTCInterlocks  pCommandInterlocks;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nInterlock[0] = 0, nInterlocks[0] = (INT)pInterlocks.GetSize(); nInterlock[0] < nInterlocks[0]; nInterlock[0]++)
	{
		if ((pCommandInterlock[1] = ((pCommandInterlock[0] = pInterlocks.GetAt(nInterlock[0]))) ? m_pTCInterlocks.GetAt(m_pTCInterlocks.Find(pCommandInterlock[0]->GetComputerName(), pCommandInterlock[0]->GetSourceType(), pCommandInterlock[0]->GetName())) : (CTCInterlock *)NULL))
		{
			if (pCommandInterlock[1]->GetState() != TCINTERLOCK_STATE_PENDING)
			{
				if (!pCommandInterlock[1]->Compare(pCommandInterlock[0]))
				{
					pCommandInterlock[1]->Copy(pCommandInterlock[0]);
					pCommandInterlock[1]->SetState(TCINTERLOCK_STATE_IDLE);
				}
			}
			continue;
		}
		if ((pCommandInterlock[0] = pInterlocks.GetAt(nInterlock[0])))
		{
			if ((pCommandInterlock[1] = new CTCInterlock))
			{
				pCommandInterlock[1]->Copy(pCommandInterlock[0]);
				pCommandInterlock[1]->SetState(TCINTERLOCK_STATE_IDLE);
				if (m_pTCInterlocks.Add(pCommandInterlock[1]) >= 0) continue;
				delete pCommandInterlock[1];
			}
		}
		break;
	}
	for (nInterlock[1] = 0, nInterlocks[1] = (INT)m_pTCInterlocks.GetSize(); nInterlock[1] < nInterlocks[1]; nInterlock[1]++)
	{
		if ((pCommandInterlock[0] = m_pTCInterlocks.GetAt(nInterlock[1])) && pInterlocks.Find(pCommandInterlock[0]->GetComputerName(), pCommandInterlock[0]->GetSourceType(), pCommandInterlock[0]->GetName()) < 0)
		{
			if (pCommandInterlock[0]->GetState() == TCINTERLOCK_STATE_IDLE)
			{
				m_pTCInterlocks.RemoveAt(nInterlock[1]);
				delete pCommandInterlock[0];
				nInterlocks[1]--;
				nInterlock[1]--;
			}
		}
	}
	if (nInterlock[0] == nInterlocks[0])
	{
		if (pCommandInterlocks.Copy(&m_pTCInterlocks))
		{
			UpdateTCInterlocks(pCommandInterlocks);
			return TRUE;
		}
	}
	return FALSE;
}
BOOL CTCProcessThread::SetTCInterlocks(UINT nSourceType, CONST CTCInterlocks &pInterlocks)
{
	INT  nInterlock[2];
	INT  nInterlocks[2];
	CTCInterlock  *pCommandInterlock[2];
	CTCInterlocks  pCommandInterlocks;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nInterlock[0] = 0, nInterlocks[0] = (INT)pInterlocks.GetSize(); nInterlock[0] < nInterlocks[0]; nInterlock[0]++)
	{
		if ((pCommandInterlock[0] = pInterlocks.GetAt(nInterlock[0])) && (TCINTERLOCKSCOPEFROMCODE(pCommandInterlock[0]->GetScope()) == TCINTERLOCK_SCOPE_GLOBAL || pCommandInterlock[0]->IsHost()) && (pCommandInterlock[0]->GetSourceType() & nSourceType))
		{
			if ((pCommandInterlock[1] = m_pTCInterlocks.GetAt(m_pTCInterlocks.Find(pCommandInterlock[0]->GetComputerName(), pCommandInterlock[0]->GetSourceType(), pCommandInterlock[0]->GetName()))))
			{
				if (pCommandInterlock[1]->GetState() == TCINTERLOCK_STATE_IDLE)
				{
					if (!pCommandInterlock[1]->Compare(pCommandInterlock[0]))
					{
						pCommandInterlock[1]->Copy(pCommandInterlock[0]);
						pCommandInterlock[1]->SetState(TCINTERLOCK_STATE_IDLE);
					}
					continue;
				}
				if (pCommandInterlock[0]->GetScope() == pCommandInterlock[1]->GetScope() && pCommandInterlock[0]->GetStage() == pCommandInterlock[1]->GetStage() && pCommandInterlock[0]->GetState() == TCINTERLOCK_STATE_IDLE  &&  pCommandInterlock[0]->GetState() != pCommandInterlock[1]->GetState()) pCommandInterlock[1]->SetState(TCINTERLOCK_STATE_IDLE);
				continue;
			}
			if ((pCommandInterlock[1] = new CTCInterlock))
			{
				pCommandInterlock[1]->Copy(pCommandInterlock[0]);
				pCommandInterlock[1]->SetState(TCINTERLOCK_STATE_IDLE);
				if (m_pTCInterlocks.Add(pCommandInterlock[1]) >= 0) continue;
				delete pCommandInterlock[1];
			}
		}
		break;
	}
	for (nInterlock[1] = 0, nInterlocks[1] = (INT)m_pTCInterlocks.GetSize(); nInterlock[1] < nInterlocks[1]; nInterlock[1]++)
	{
		if ((pCommandInterlock[0] = m_pTCInterlocks.GetAt(nInterlock[1])) && (TCINTERLOCKSCOPEFROMCODE(pCommandInterlock[0]->GetScope()) == TCINTERLOCK_SCOPE_GLOBAL || pCommandInterlock[0]->IsHost()) && (pCommandInterlock[0]->GetSourceType() & nSourceType) && pInterlocks.Find(pCommandInterlock[0]->GetComputerName(), pCommandInterlock[0]->GetSourceType(), pCommandInterlock[0]->GetName()) < 0)
		{
			if (pCommandInterlock[0]->GetState() == TCINTERLOCK_STATE_IDLE)
			{
				m_pTCInterlocks.RemoveAt(nInterlock[1]);
				delete pCommandInterlock[0];
				nInterlocks[1]--;
				nInterlock[1]--;
			}
		}
	}
	if (nInterlock[0] == nInterlocks[0])
	{
		if (pCommandInterlocks.Copy(&m_pTCInterlocks))
		{
			UpdateTCInterlocks(pCommandInterlocks);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CTCProcessThread::GetTCInterlocks(CTCInterlocks &pInterlocks) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return pInterlocks.Copy(&m_pTCInterlocks);
}
BOOL CTCProcessThread::GetTCInterlocks(UINT nSourceType, CTCInterlocks &pInterlocks) CONST
{
	INT  nInterlock;
	INT  nInterlocks;
	CTCInterlock  *pInterlock[2];
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nInterlock = 0, nInterlocks = (INT)m_pTCInterlocks.GetSize(), pInterlocks.RemoveAll(); nInterlock < nInterlocks; nInterlock++)
	{
		if ((pInterlock[0] = m_pTCInterlocks.GetAt(nInterlock)) && (TCINTERLOCKSCOPEFROMCODE(pInterlock[0]->GetScope()) == TCINTERLOCK_SCOPE_GLOBAL || pInterlock[0]->IsHost()) && (pInterlock[0]->GetSourceType() & nSourceType))
		{
			if ((pInterlock[1] = new CTCInterlock))
			{
				pInterlock[1]->Copy(pInterlock[0]);
				if (pInterlocks.Add(pInterlock[1]) >= 0) continue;
				delete pInterlock[1];
			}
			break;
		}
	}
	return((nInterlock == nInterlocks) ? TRUE : FALSE);
}

BOOL CTCProcessThread::UpdateTCInterlocks(CONST CTCInterlocks &pInterlocks, BOOL bAll)
{
	CComputerToken  cComputerToken;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	UpdateTCInterlocks(cComputerToken.GetComputerName(), pInterlocks, bAll);
	m_pTCInterfaceThread->UpdateTCInterlocks(pInterlocks, bAll);
	return TRUE;
}
VOID CTCProcessThread::UpdateTCInterlocks(LPCTSTR pszOriginator, CONST CTCInterlocks &pInterlocks, BOOL bAll)
{
	INT  nInterlock;
	INT  nInterlocks;
	CTCInterlock  *pInterlock[2];
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nInterlock = 0, nInterlocks = (((bAll && !IsCommandHandler() && m_pTCInterlocks.Copy(&pInterlocks)) || IsCommandHandler() || !bAll) && lstrlen(pszOriginator) > 0) ? (INT)((IsCommandHandler() || !bAll)*pInterlocks.GetSize()) : -1; nInterlock < nInterlocks; nInterlock++)
	{
		if ((pInterlock[1] = ((pInterlock[0] = pInterlocks.GetAt(nInterlock))) ? m_pTCInterlocks.GetAt(m_pTCInterlocks.Find(pInterlock[0]->GetComputerName(), pInterlock[0]->GetSourceType(), pInterlock[0]->GetName())) : (CTCInterlock *)NULL))
		{
			if (!IsCommandHandler() || pInterlock[1]->GetState() != TCINTERLOCK_STATE_PENDING) pInterlock[1]->Copy(pInterlock[0]);
			continue;
		}
		if ((pInterlock[1] = new CTCInterlock))
		{
			pInterlock[1]->Copy(pInterlock[0]);
			if (m_pTCInterlocks.Add(pInterlock[1]) >= 0) continue;
			delete pInterlock[1];
		}
		break;
	}
	for (nInterlock = 0, nInterlocks = (bAll && m_pTCInterlocks.GetSize() > pInterlocks.GetSize() && lstrlen(pszOriginator) > 0) ? (INT)m_pTCInterlocks.GetSize() : 0; nInterlock < nInterlocks; nInterlock++)
	{
		if ((pInterlock[0] = m_pTCInterlocks.GetAt(nInterlock)) && pInterlocks.Find(pInterlock[0]->GetComputerName(), pInterlock[0]->GetSourceType(), pInterlock[0]->GetName()) < 0)
		{
			m_pTCInterlocks.RemoveAt(nInterlock);
			delete pInterlock[0];
			nInterlocks--;
			nInterlock--;
		}
	}
	if (m_pTCManualStackWnd) m_pTCManualStackWnd->UpdateTelecommandInterlocks(m_pTCInterlocks);
	if (m_pTCAutomaticStackWnd) m_pTCAutomaticStackWnd->UpdateTelecommandInterlocks(m_pTCInterlocks);
	Update();
}

BOOL CTCProcessThread::CheckTCInterlocks(UINT nSourceType, UINT nState) CONST
{
	INT  nInterlock;
	INT  nInterlocks;
	CTCInterlock  *pInterlock;
	CTCInterlocks  pInterlocks;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nInterlock = 0, nInterlocks = ((nSourceType == TCSERVICE_COMMANDSOURCETYPE_ALL && GetTCInterlocks(pInterlocks)) || (nSourceType != TCSERVICE_COMMANDSOURCETYPE_ALL && GetTCInterlocks(nSourceType, pInterlocks))) ? (INT)pInterlocks.GetSize() : 0; nInterlock < nInterlocks; nInterlock++)
	{
		if ((pInterlock = pInterlocks.GetAt(nInterlock)) && pInterlock->GetState() == nState) break;
		continue;
	}
	return((nInterlock < nInterlocks) ? TRUE : FALSE);
}

BOOL CTCProcessThread::CheckTCInterlock(UINT nSourceType, LPCTSTR pszInterlock, UINT &nState) CONST
{
	CTCInterlock  *pInterlock;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pInterlock = m_pTCInterlocks.GetAt(m_pTCInterlocks.Find(nSourceType, pszInterlock))))
	{
		nState = pInterlock->GetState();
		return TRUE;
	}
	return FALSE;
}
BOOL CTCProcessThread::CheckTCInterlock(UINT nSourceType, LPCTSTR pszInterlock, UINT &nScope, UINT &nStage, UINT &nState) CONST
{
	CTCInterlock  *pInterlock;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pInterlock = m_pTCInterlocks.GetAt(m_pTCInterlocks.Find(nSourceType, pszInterlock))))
	{
		nScope = pInterlock->GetScope();
		nStage = pInterlock->GetStage();
		nState = pInterlock->GetState();
		return TRUE;
	}
	return FALSE;
}
BOOL CTCProcessThread::CheckTCInterlock(CONST CTCItem *pItem) CONST
{
	INT  nInterlock;
	INT  nInterlocks;
	BOOL  bInterlock;
	CString  szInterlock;
	CTCInterlock  *pInterlock;
	CDatabaseTCPacket  cPacket;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nInterlock = 0, nInterlocks = (INT)m_pTCInterlocks.GetSize(); nInterlock < nInterlocks; nInterlock++)
	{
		if ((pInterlock = (CTCInterlock *)m_pTCInterlocks.GetAt(nInterlock)) != (CTCInterlock *)NULL)
		{
			if (pInterlock->GetState() == TCINTERLOCK_STATE_PENDING || pInterlock->GetState() == TCINTERLOCK_STATE_FAILURE)
			{
				if (!pItem->GetComputerName().CompareNoCase(pInterlock->GetComputerName()) && pItem->GetSourceType() == pInterlock->GetSourceType())
				{
					if (TCINTERLOCKSCOPEFROMCODE(pInterlock->GetScope()) == TCINTERLOCK_SCOPE_LOCALSUBSYSTEM  &&  pItem->GetTCPacket(&cPacket) && cPacket.GetAPID() == TCINTERLOCKAPIDFROMCODE(pInterlock->GetScope())) break;
					if (TCINTERLOCKSCOPEFROMCODE(pInterlock->GetScope()) == TCINTERLOCK_SCOPE_LOCAL) break;
				}
				if (TCINTERLOCKSCOPEFROMCODE(pInterlock->GetScope()) == TCINTERLOCK_SCOPE_GLOBAL) break;
			}
		}
	}
	if (nInterlock == nInterlocks)
	{
		if ((pInterlock = (pItem->GetReleaseInterlock(szInterlock, bInterlock)) ? m_pTCInterlocks.GetAt(m_pTCInterlocks.Find(pItem->GetComputerName(), pItem->GetSourceType(), szInterlock)) : (CTCInterlock *)NULL) && TCINTERLOCKSCOPEFROMCODE(pInterlock->GetScope()) == TCINTERLOCK_SCOPE_COMMANDS) return(((bInterlock  &&  pInterlock->GetState() == TCINTERLOCK_STATE_SUCCESS) || (!bInterlock  &&  pInterlock->GetState() == TCINTERLOCK_STATE_FAILURE)) ? TRUE : FALSE);
		return TRUE;
	}
	return FALSE;
}

INT CTCProcessThread::EnumTCDiagnosticsOversamplingDumpRates(CStringArray &szRates) CONST
{
	return m_pTCProcessEngine->EnumTCDiagnosticsOversamplingDumpRates(szRates);
}

BOOL CTCProcessThread::EncodeTCDiagnosticsOversamplingDump(CONST CTimeTag &tExecutionTime, CONST COversamplingParameters &pOversamplingParameters, CDatabaseTCFunction *pDatabaseTCFunction)
{
	return m_pTCProcessEngine->EncodeTCDiagnosticsOversamplingDump(GetDatabase(), tExecutionTime, pOversamplingParameters, pDatabaseTCFunction);
}

BOOL CTCProcessThread::DecodeTCDiagnosticsOversamplingDump(CONST CDatabaseTCFunction *pDatabaseTCFunction, COversamplingParameters &pOversamplingParameters)
{
	return m_pTCProcessEngine->DecodeTCDiagnosticsOversamplingDump(GetDatabase(), pDatabaseTCFunction, pOversamplingParameters);
}
BOOL CTCProcessThread::DecodeTCDiagnosticsOversamplingDump(CONST CTMEnvironment *pTMEnvironment, COversamplingParameters &pOversamplingParameters, BOOL bAutomatic)
{
	return m_pTCProcessEngine->DecodeTCDiagnosticsOversamplingDump(GetDatabase(), pTMEnvironment, pOversamplingParameters, bAutomatic);
}

double CTCProcessThread::CalculateTCDiagnosticsOversamplingBandwidth(COversamplingParameters &pOversamplingParameters) CONST
{
	return m_pTCProcessEngine->CalculateTCDiagnosticsOversamplingBandwidth(GetDatabase(), pOversamplingParameters);
}

INT CTCProcessThread::EnumTCOnBoardBufferTypes(CStringArray &szTypes) CONST
{
	return m_pTCProcessEngine->EnumTCOnBoardBufferTypes(szTypes);
}

INT CTCProcessThread::EnumTCOnBoardBufferQueues(CTCOnBoardBufferQueues &pQueues) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return pQueues.Copy(&m_pTCOnBoardBufferQueues);
}
INT CTCProcessThread::EnumTCOnBoardBufferQueues(LPCTSTR pszType, CStringArray &szNames) CONST
{
	return m_pTCProcessEngine->EnumTCOnBoardBufferQueues(pszType, szNames);
}
INT CTCProcessThread::EnumTCOnBoardBufferQueues(LPCTSTR pszType, CStringArray &szNames, CUIntArray &nAPIDs, CUIntArray &nSubScheduleIDs, CUIntArray &nLimits, CStringArray &szUnits, CUIntArray &tTimeouts) CONST
{
	return m_pTCProcessEngine->EnumTCOnBoardBufferQueues(pszType, szNames, nAPIDs, nSubScheduleIDs, nLimits, szUnits, tTimeouts);
}

INT CTCProcessThread::UpdateTCOnBoardBufferQueues(CONST CTMEnvironment *pTMEnvironment, CStringArray &szTypes, CStringArray &szNames, CUIntArray &nSubScheduleIDs, CUIntArray &nCounts, CTimeTagArray &tUpdateTimes, CUIntArray &nStatus)
{
	return m_pTCProcessEngine->UpdateTCOnBoardBufferQueues(GetDatabase(), pTMEnvironment, szTypes, szNames, nSubScheduleIDs, nCounts, tUpdateTimes, nStatus);
}
BOOL CTCProcessThread::UpdateTCOnBoardBufferQueues(CONST CTCOnBoardBufferQueues &pQueues, BOOL bAll)
{
	CComputerToken  cComputerToken;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	UpdateTCOnBoardBufferQueues(cComputerToken.GetComputerName(), pQueues, bAll);
	m_pTCInterfaceThread->UpdateTCOnBoardBufferQueues(pQueues, bAll);
	return TRUE;
}
VOID CTCProcessThread::UpdateTCOnBoardBufferQueues(LPCTSTR pszOriginator, CONST CTCOnBoardBufferQueues &pQueues, BOOL bAll)
{
	INT  nQueue;
	INT  nQueues;
	CTCOnBoardBufferQueue  *pQueue[2];
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nQueue = 0, nQueues = (((bAll && !IsCommandHandler() && m_pTCOnBoardBufferQueues.Copy(&pQueues)) || IsCommandHandler() || !bAll) && lstrlen(pszOriginator) > 0) ? (INT)((IsCommandHandler() || !bAll)*pQueues.GetSize()) : -1; nQueue < nQueues; nQueue++)
	{
		if ((pQueue[1] = ((pQueue[0] = pQueues.GetAt(nQueue))) ? m_pTCOnBoardBufferQueues.GetAt(m_pTCOnBoardBufferQueues.Find(pQueue[0]->GetType(), pQueue[0]->GetName(), pQueue[0]->GetSubScheduleID())) : (CTCOnBoardBufferQueue *)NULL))
		{
			pQueue[1]->Copy(pQueue[0]);
			continue;
		}
		if ((pQueue[1] = new CTCOnBoardBufferQueue))
		{
			if (pQueue[1]->Copy(pQueue[0]) && m_pTCOnBoardBufferQueues.Add(pQueue[1]) >= 0) continue;
			delete pQueue[1];
		}
		break;
	}
	for (nQueue = 0, nQueues = (bAll && m_pTCOnBoardBufferQueues.GetSize() > pQueues.GetSize() && lstrlen(pszOriginator) > 0) ? (INT)m_pTCOnBoardBufferQueues.GetSize() : 0; nQueue < nQueues; nQueue++)
	{
		if ((pQueue[0] = m_pTCOnBoardBufferQueues.GetAt(nQueue)) && pQueues.Find(pQueue[0]->GetType(), pQueue[0]->GetType(), pQueue[0]->GetSubScheduleID()) < 0)
		{
			m_pTCOnBoardBufferQueues.RemoveAt(nQueue);
			delete pQueue[0];
			nQueues--;
			nQueue--;
		}
	}
	if (m_pTCOnBoardBufferQueuesWnd != (CTCOnBoardBufferQueuesWnd *)NULL) m_pTCOnBoardBufferQueuesWnd->UpdateMonitoring(m_pTCOnBoardBufferQueues);
}

BOOL CTCProcessThread::CheckTCOnBoardBufferQueues(CONST CTCItems &pItems, INT nChecks) CONST
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	INT  nCount;
	BOOL  bItems;
	BOOL  bBlocked;
	UINT  cbEntry;
	UINT  nSubScheduleID;
	CString  szName;
	CString  szType;
	CTCItem  *pQueueItem[3];
	CTimeTag  tExecutionTime;
	CTCPacket  cTCPacket;
	CPtrArray  pQueuedItems;
	CUIntArray  nQueueCounts;
	CDatabaseTCPacket  *pPacket[2];
	CDatabaseTCPackets  pPackets;
	CDatabaseTCFunction  *pFunction[2];
	CDatabaseTCFunctions  pFunctions;
	CTCOnBoardBufferQueue  *pQueue;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nItem = 0, nItems = (nChecks >= 0) ? (INT)min(pItems.GetSize(), nChecks) : (INT)pItems.GetSize(), tExecutionTime = 0, bItems = FALSE; nItem < nItems; nItem++)
	{
		if ((pQueueItem[0] = pItems.GetAt(nItem)) && pQueueItem[0]->GetType() == TCITEM_TYPE_FUNCTION && ((pQueueItem[0]->GetFlags() & TCITEM_LINKAGEFLAG_BLOCKED) || ((pQueueItem[0]->GetFlags() & TCITEM_EXECUTIONFLAG_TIMETAGGED) && pQueueItem[0]->GetExecutionTime(tExecutionTime)) || (pQueueItem[0]->GetFlags() & TCITEM_EXECUTIONFLAG_1STSTEP)))
		{
			if ((pFunction[0] = new CDatabaseTCFunction) != (CDatabaseTCFunction *)NULL)
			{
				if ((pPacket[0] = new CDatabaseTCPacket) != (CDatabaseTCPacket *)NULL)
				{
					if (pFunction[0]->CDatabaseTCFunction::Copy(pQueueItem[0]) && pQueueItem[0]->GetTCPacket(pPacket[0]))
					{
						if (InitializeTCPacket(pQueueItem[0], pPacket[0]) && GenerateTCPackets(pQueueItem[0], pPacket[0], pQueueItem[0]->GetMemoryPatch(), (pQueueItem[0]->GetFlags() & TCITEM_EXECUTIONFLAG_TIMETAGGED) ? TRUE : FALSE, FALSE, (bBlocked = ((pQueueItem[0]->GetFlags() & TCITEM_LINKAGEFLAG_BLOCKED) && pQueueItem[0]->GetReleaseBlockID() > 0) ? TRUE : FALSE), TRUE, pFunctions, pPackets))
						{
							for (nIndex = 0, nCount = (INT)pPackets.GetSize(); nIndex < nCount; nIndex++)
							{
								if ((pFunction[1] = pFunctions.GetAt(nIndex)))
								{
									if ((pPacket[1] = pPackets.GetAt(nIndex)))
									{
										if (!bBlocked  &&  InitializeTCPacket(pQueueItem[0], pFunction[1], pPacket[1], nIndex) && InitializeTCPacket(pFunction[1], pPacket[1], &cTCPacket, tExecutionTime, (pQueueItem[0]->GetReleaseBlockID() == 0) ? TRUE : FALSE, TRUE))
										{
											pQueuedItems.Add(pQueueItem[0]);
											continue;
										}
										if (bBlocked)
										{
											if (CollectTCPacket(pFunction[1], &cTCPacket, pQueueItem[0]->GetReleaseBlockID()))
											{
												pQueuedItems.Add(pQueueItem[0]);
												continue;
											}
										}
									}
								}
								break;
							}
							if (nIndex == nCount)
							{
								if ((pQueueItem[1] = pItems.GetAt(nItem + 1)) == (CTCItem *)NULL || (pQueueItem[1]->GetFlags() & TCITEM_LINKAGEFLAG_BLOCKED) != TCITEM_LINKAGEFLAG_BLOCKED)
								{
									if ((pQueue = (FindTCOnBoardBufferQueue(&cTCPacket, szType, szName, nSubScheduleID)) ? m_pTCOnBoardBufferQueues.GetAt((nIndex = m_pTCOnBoardBufferQueues.Find(szType, szName, nSubScheduleID))) : (CTCOnBoardBufferQueue *)NULL))
									{
										for (nQueueCounts.SetAtGrow(nIndex, ((cbEntry = CalculateTCOnBoardBufferQueueEntry(&cTCPacket)) != (UINT)-1 && nIndex < nQueueCounts.GetSize()) ? (nQueueCounts.GetAt(nIndex) + cbEntry) : cbEntry); pQueuedItems.GetSize() > 0; pQueuedItems.RemoveAt(0))
										{
											if ((pQueueItem[2] = (CTCItem *)pQueuedItems.GetAt(0)) && ((pQueue->GetCount() + nQueueCounts.GetAt(nIndex) <= pQueue->GetLimit() && (pQueue->GetStatus() & TCONBOARDBUFFERQUEUE_STATUS_ENABLED) && (pQueueItem[2]->GetResult() & TCITEM_FAILURE_PTV_ONBOARDBUFFER)) || ((pQueue->GetCount() + nQueueCounts.GetAt(nIndex) > pQueue->GetLimit() || (pQueue->GetStatus() & TCONBOARDBUFFERQUEUE_STATUS_DISABLED)) && (pQueueItem[2]->GetResult() & TCITEM_FAILURE_PTV_ONBOARDBUFFER) != TCITEM_FAILURE_PTV_ONBOARDBUFFER)))
											{
												pQueueItem[2]->SetResult((pQueue->GetCount() + nQueueCounts.GetAt(nIndex) > pQueue->GetLimit() || (pQueue->GetStatus() & TCONBOARDBUFFERQUEUE_STATUS_DISABLED)) ? (pQueueItem[2]->GetResult() | TCITEM_FAILURE_PTV_ONBOARDBUFFER) : (pQueueItem[2]->GetResult() & ~TCITEM_FAILURE_PTV_ONBOARDBUFFER));
												bItems = TRUE;
											}
										}
									}
									pQueuedItems.RemoveAll();
								}
								delete pFunction[0];
								delete pPacket[0];
								continue;
							}
						}
					}
					delete pPacket[0];
				}
				delete pFunction[0];
			}
			break;
		}
	}
	return((nItem == nItems) ? bItems : FALSE);
}

BOOL CTCProcessThread::UpdateTCOnBoardBufferQueue(LPCTSTR pszType, LPCTSTR pszName, UINT nSubScheduleID, CONST CTCItems &pItems)
{
	INT  nItem;
	INT  nItems;
	INT  nIndex;
	CTCItem  *pItem[2];
	CTCOnBoardBufferQueue  *pQueue[2];
	CTCOnBoardBufferQueues  pQueues;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pQueue[0] = new CTCOnBoardBufferQueue))
	{
		if ((pQueue[1] = m_pTCOnBoardBufferQueues.GetAt(m_pTCOnBoardBufferQueues.Find(pszType, pszName, nSubScheduleID))))
		{
			for (nItem = 0, nItems = (INT)pItems.GetSize(); nItem < nItems; nItem++)
			{
				if ((pItem[0] = pItems.GetAt(nItem)) != (CTCItem *)NULL)
				{
					if ((pItem[1] = pQueue[1]->GetAt((nIndex = pQueue[1]->Find(pItem[0])))))
					{
						pQueue[1]->SetCount((pQueue[1]->GetCount() >= pItem[1]->GetQueuedSize()) ? (pQueue[1]->GetCount() - pItem[1]->GetQueuedSize()) : 0);
						pQueue[1]->RemoveAt(nIndex);
						delete pItem[1];
					}
				}
			}
			for (DiscardTelecommands(pItems); pQueue[0]->Copy(pQueue[1]) && pQueues.Add(pQueue[0]) >= 0; )
			{
				UpdateTCOnBoardBufferQueues(pQueues, FALSE);
				return TRUE;
			}
		}
		delete pQueue[0];
	}
	return FALSE;
}
BOOL CTCProcessThread::UpdateTCOnBoardBufferQueue(LPCTSTR pszType, LPCTSTR pszName, UINT nSubScheduleID, UINT nFlags, UINT nAPID, UINT nPSC, INT nLowEntry, INT nHighEntry, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime)
{
	INT  nItem;
	INT  nItems;
	INT  nCount;
	CTCItem  *pItem;
	CTCItems  pItems;
	CTCPacket  cTCPacket;
	CTimeTag  tExecutionTime;
	CByteArray  nPacketData;
	CTCOnBoardBufferQueue  *pQueue[2];
	CTCOnBoardBufferQueues  pQueues;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pQueue[0] = new CTCOnBoardBufferQueue))
	{
		if ((pQueue[1] = m_pTCOnBoardBufferQueues.GetAt(m_pTCOnBoardBufferQueues.Find(pszType, pszName, nSubScheduleID))))
		{
			for (nItem = 0, nItems = (nFlags & TCONBOARDBUFFERQUEUE_FLAG_CLEARDOWNLOADSTATUS) ? (INT)pQueue[1]->GetSize() : 0, pQueue[1]->SetFlags((nFlags & TCONBOARDBUFFERQUEUE_FLAG_SYNCHRONIZEBYDOWNLOAD) ? (pQueue[1]->GetFlags() | TCONBOARDBUFFERQUEUE_FLAG_SYNCHRONIZEBYDOWNLOAD) : (pQueue[1]->GetFlags() & ~TCONBOARDBUFFERQUEUE_FLAG_SYNCHRONIZEBYDOWNLOAD)); nItem < nItems; nItem++)
			{
				if ((pItem = pQueue[1]->GetAt(nItem)) != (CTCItem *)NULL)
				{
					pItem->SetFlags(pItem->GetFlags() & ~TCITEM_DUMPFLAG_SYNCHRONIZED);
					pItem->SetFlags(pItem->GetFlags() & ~TCITEM_DUMPFLAG_NOTSYNCHRONIZED);
				}
			}
			if (nFlags & TCONBOARDBUFFERQUEUE_FLAG_ALLOWDELETEALL)
			{
				if (pQueue[1]->GetSize() > 0 || pQueue[1]->GetCount() > 0)
				{
					pItems.Copy(pQueue[1]);
					pQueue[1]->SetCount(0);
					pQueue[1]->RemoveAll();
				}
			}
			if (nFlags & TCONBOARDBUFFERQUEUE_FLAG_ALLOWDELETEBYRANGE)
			{
				for (nItem = 0, nItems = (INT)pQueue[1]->GetSize(), nCount = 0; nItem < nItems; nItem++)
				{
					if ((pItem = (nItem + nCount >= nLowEntry  &&  nItem + nCount <= nHighEntry) ? pQueue[1]->GetAt(nItem) : (CTCItem *)NULL))
					{
						pQueue[1]->SetCount((pQueue[1]->GetCount() >= pItem->GetQueuedSize()) ? (pQueue[1]->GetCount() - pItem->GetQueuedSize()) : 0);
						pQueue[1]->RemoveAt(nItem, 1);
						pItems.InsertAt(pItems.GetSize(), pItem, 1);
						nCount++;
						nItems--;
						nItem--;
					}
				}
			}
			if (nFlags & TCONBOARDBUFFERQUEUE_FLAG_ALLOWDELETEBYTIMERANGE)
			{
				for (nItem = 0, nItems = (INT)pQueue[1]->GetSize(); nItem < nItems; nItem++)
				{
					if ((pItem = pQueue[1]->GetAt(nItem)) && pItem->GetExecutionTime(tExecutionTime) && tExecutionTime.GetTimeInSeconds() >= tStartTime.GetTime() && tExecutionTime.GetTimeInSeconds() <= tStopTime.GetTime())
					{
						pQueue[1]->SetCount((pQueue[1]->GetCount() >= pItem->GetQueuedSize()) ? (pQueue[1]->GetCount() - pItem->GetQueuedSize()) : 0);
						pQueue[1]->RemoveAt(nItem, 1);
						pItems.InsertAt(pItems.GetSize(), pItem, 1);
						nItems--;
						nItem--;
					}
				}
			}
			if (nFlags & TCONBOARDBUFFERQUEUE_FLAG_ALLOWDELETEBYSUBSYSTEM)
			{
				for (nItem = 0, nItems = (INT)pQueue[1]->GetSize(); nItem < nItems; nItem++)
				{
					if ((pItem = pQueue[1]->GetAt(nItem)) && pItem->GetTCPacket(nPacketData) > 0 && cTCPacket.Unmap(nPacketData) && cTCPacket.GetAPID() == nAPID)
					{
						if ((nFlags & TCONBOARDBUFFERQUEUE_FLAG_ALLOWDELETEBYSEQUENCECOUNTER) != TCONBOARDBUFFERQUEUE_FLAG_ALLOWDELETEBYSEQUENCECOUNTER || cTCPacket.GetSequenceCount() == nPSC)
						{
							pQueue[1]->SetCount((pQueue[1]->GetCount() >= pItem->GetQueuedSize()) ? (pQueue[1]->GetCount() - pItem->GetQueuedSize()) : 0);
							pQueue[1]->RemoveAt(nItem, 1);
							pItems.InsertAt(pItems.GetSize(), pItem, 1);
							nItems--;
							nItem--;
						}
					}
				}
			}
			if (nFlags & TCONBOARDBUFFERQUEUE_FLAG_ALLOWDELETEBYSEQUENCECOUNTER)
			{
				for (nItem = 0, nItems = ((nFlags & TCONBOARDBUFFERQUEUE_FLAG_ALLOWDELETEBYSUBSYSTEM) != TCONBOARDBUFFERQUEUE_FLAG_ALLOWDELETEBYSUBSYSTEM) ? (INT)pQueue[1]->GetSize() : 0; nItem < nItems; nItem++)
				{
					if ((pItem = pQueue[1]->GetAt(nItem)) && pItem->GetTCPacket(nPacketData) > 0 && cTCPacket.Unmap(nPacketData) && cTCPacket.GetSequenceCount() == nPSC)
					{
						pQueue[1]->SetCount((pQueue[1]->GetCount() >= pItem->GetQueuedSize()) ? (pQueue[1]->GetCount() - pItem->GetQueuedSize()) : 0);
						pQueue[1]->RemoveAt(nItem, 1);
						pItems.InsertAt(pItems.GetSize(), pItem, 1);
						nItems--;
						nItem--;
					}
				}
			}
			for (DiscardTelecommands(pItems); pQueue[0]->Copy(pQueue[1]) && pQueues.Add(pQueue[0]) >= 0; )
			{
				UpdateTCOnBoardBufferQueues(pQueues, FALSE);
				return TRUE;
			}
		}
		delete pQueue[0];
	}
	return FALSE;
}

BOOL CTCProcessThread::AcknowledgeTCOnBoardBufferQueue(LPCTSTR pszType, LPCTSTR pszName, UINT nSubScheduleID, UINT nFlags)
{
	CTCOnBoardBufferQueue  *pQueue[2];
	CTCOnBoardBufferQueues  pQueues;
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	if ((pQueue[0] = new CTCOnBoardBufferQueue))
	{
		if ((pQueue[1] = m_pTCOnBoardBufferQueues.GetAt(m_pTCOnBoardBufferQueues.Find(pszType, pszName, nSubScheduleID))))
		{
			for (pQueue[1]->Alert(nFlags); pQueue[0]->Copy(pQueue[1]) && pQueues.Add(pQueue[0]) >= 0; )
			{
				UpdateTCOnBoardBufferQueues(pQueues, FALSE);
				return TRUE;
			}
		}
		delete pQueue[0];
	}
	return FALSE;
}

BOOL CTCProcessThread::CheckTCOnBoardBufferQueue(LPCTSTR pszType, LPCTSTR pszName, BOOL &bStatus, BOOL &bDumpAllEntries, BOOL &bDumpByAPID, BOOL &bDumpByPSC, BOOL &bDumpByEntryRange, BOOL &bDumpByTimeRange, BOOL &bResetAllEntries, BOOL &bResetByAPID, BOOL &bResetByPSC, BOOL &bResetByEntryRange, BOOL &bResetByTimeRange) CONST
{
	return m_pTCProcessEngine->CheckTCOnBoardBufferQueue(pszType, pszName, bStatus, bDumpAllEntries, bDumpByAPID, bDumpByPSC, bDumpByEntryRange, bDumpByTimeRange, bResetAllEntries, bResetByAPID, bResetByPSC, bResetByEntryRange, bResetByTimeRange);
}
BOOL CTCProcessThread::CheckTCOnBoardBufferQueue(CONST CTCItem *pItem) CONST
{
	INT  nIndex;
	INT  nCount;
	BOOL  bBlocked;
	CTCItem  *pQueueItem;
	CTCPacket  cTCPacket;
	CByteArray  nPacketData[2];
	CDatabaseTCPacket  *pPacket[2];
	CDatabaseTCPackets  pPackets;
	CDatabaseTCFunction  *pFunction[2];
	CDatabaseTCFunctions  pFunctions;

	if (m_pTMEnvironment->Lock())
	{
		if ((pItem->GetFlags() & TCITEM_EXECUTIONFLAG_2NDSTEP) && m_pTCProcessEngine->Get1stStepTCData(m_pTMEnvironment, nPacketData[0]))
		{
			if ((pQueueItem = new CTCItem))
			{
				if ((pFunction[0] = new CDatabaseTCFunction))
				{
					if ((pPacket[0] = new CDatabaseTCPacket))
					{
						if (pQueueItem->Copy(pItem) && pFunction[0]->CDatabaseTCFunction::Copy(pQueueItem) && pQueueItem->GetTCPacket(pPacket[0]))
						{
							for (pQueueItem->SetFlags((pQueueItem->GetFlags() & ~TCITEM_EXECUTIONFLAG_2NDSTEP) | TCITEM_EXECUTIONFLAG_1STSTEP), pQueueItem->SetAttributes((pQueueItem->GetAttributes() & ~TCFUNCTION_EXETYPE_SECONDSTEP) | TCFUNCTION_EXETYPE_FIRSTSTEP), pFunction[0]->SetAttributes((pFunction[0]->GetAttributes() & ~TCFUNCTION_EXETYPE_SECONDSTEP) | TCFUNCTION_EXETYPE_FIRSTSTEP); InitializeTCPacket(pQueueItem, pPacket[0]) && GenerateTCPackets(pQueueItem, pPacket[0], pQueueItem->GetMemoryPatch(), FALSE, FALSE, (bBlocked = ((pQueueItem->GetFlags() & TCITEM_LINKAGEFLAG_BLOCKED) && pQueueItem->GetReleaseBlockID() > 0) ? TRUE : FALSE), TRUE, pFunctions, pPackets); )
							{
								for (nIndex = 0, nCount = (INT)pPackets.GetSize(); nIndex < nCount; nIndex++)
								{
									if ((pFunction[1] = pFunctions.GetAt(nIndex)))
									{
										if ((pPacket[1] = pPackets.GetAt(nIndex)))
										{
											if (!bBlocked  &&  InitializeTCPacket(pQueueItem, pFunction[1], pPacket[1], nIndex) && InitializeTCPacket(pFunction[1], pPacket[1], &cTCPacket, 0, (pQueueItem->GetReleaseBlockID() == 0) ? TRUE : FALSE, TRUE)) continue;
											if (bBlocked  &&  CollectTCPacket(pFunction[1], &cTCPacket, pQueueItem->GetReleaseBlockID())) continue;
										}
									}
									break;
								}
								if (nIndex == nCount)
								{
									if (cTCPacket.GetData(nPacketData[1]) && nPacketData[0].GetSize() == nPacketData[1].GetSize() && !memcmp(nPacketData[0].GetData(), nPacketData[1].GetData(), nPacketData[0].GetSize()))
									{
										m_pTMEnvironment->Unlock();
										delete pFunction[0];
										delete pPacket[0];
										delete pQueueItem;
										return TRUE;
									}
								}
								break;
							}
						}
						delete pPacket[0];
					}
					delete pFunction[0];
				}
				delete pQueueItem;
			}
		}
		m_pTMEnvironment->Unlock();
		return(((pItem->GetFlags() & TCITEM_EXECUTIONFLAG_2NDSTEP) != TCITEM_EXECUTIONFLAG_2NDSTEP) ? TRUE : FALSE);
	}
	return FALSE;
}

BOOL CTCProcessThread::EncodeTCOnBoardBufferQueueStatus(LPCTSTR pszType, LPCTSTR pszName, CONST CTimeTag &tExecutionTime, BOOL bEnable, CDatabaseTCFunction *pDatabaseTCFunction) CONST
{
	return m_pTCProcessEngine->EncodeTCOnBoardBufferQueueStatus(GetDatabase(), m_pTCEnvironment, pszType, pszName, tExecutionTime, bEnable, pDatabaseTCFunction);
}
BOOL CTCProcessThread::EncodeTCOnBoardBufferQueueDump(LPCTSTR pszType, LPCTSTR pszName, CONST CTimeTag &tExecutionTime, UINT nAPID, UINT nPSC, UINT nLowEntry, UINT nHighEntry, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, CDatabaseTCFunction *pDatabaseTCFunction) CONST
{
	return m_pTCProcessEngine->EncodeTCOnBoardBufferQueueDump(GetDatabase(), m_pTCEnvironment, pszType, pszName, tExecutionTime, nAPID, nPSC, nLowEntry, nHighEntry, tStartTime, tStopTime, pDatabaseTCFunction);
}
BOOL CTCProcessThread::EncodeTCOnBoardBufferQueueReset(LPCTSTR pszType, LPCTSTR pszName, CONST CTimeTag &tExecutionTime, UINT nAPID, UINT nPSC, UINT nLowEntry, UINT nHighEntry, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, CONST CTCPacket *pTCPacket, CDatabaseTCFunction *pDatabaseTCFunction) CONST
{
	return m_pTCProcessEngine->EncodeTCOnBoardBufferQueueReset(GetDatabase(), m_pTCEnvironment, pszType, pszName, tExecutionTime, nAPID, nPSC, nLowEntry, nHighEntry, tStartTime, tStopTime, pTCPacket, pDatabaseTCFunction);
}

BOOL CTCProcessThread::FindTCOnBoardBufferQueue(CONST CTCPacket *pTCPacket, CString &szType, CString &szName, UINT &nSubScheduleID) CONST
{
	return m_pTCProcessEngine->FindTCOnBoardBufferQueue(pTCPacket, szType, szName, nSubScheduleID);
}

BOOL CTCProcessThread::ExpandTCOnBoardBufferQueueEntry(CONST CTCPacket *pTCPacket, UINT &nBlockOffset, UINT &nBlockBytes, CUIntArray &nBlockSizes, CTimeTagArray &tBlockTimes) CONST
{
	return m_pTCProcessEngine->ExpandTCOnBoardBufferQueueEntry(m_pTCEnvironment, pTCPacket, nBlockOffset, nBlockBytes, nBlockSizes, tBlockTimes);
}

UINT CTCProcessThread::CalculateTCOnBoardBufferQueueEntry(CONST CTCPacket *pTCPacket) CONST
{
	return m_pTCProcessEngine->CalculateTCOnBoardBufferQueueEntry(pTCPacket);
}

BOOL CTCProcessThread::CheckTCOnBoardMemoryImageDumpCapabilities(CONST CDatabaseOBProcessor *pProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage, BOOL &bStop) CONST
{
	return m_pTCProcessEngine->CheckTCOnBoardMemoryImageDumpCapabilities(GetDatabase(), pProcessor, pImage, bStop);
}

BOOL CTCProcessThread::EncodeTCOnBoardMemoryImageDump(CONST CDatabaseOBProcessor *pProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage, CONST CTimeKey &tExecutionTime, BOOL bStop, CDatabaseTCFunction *pDatabaseTCFunction)
{
	if (m_pTCEnvironment->Lock())
	{
		if (m_pTCProcessEngine->EncodeTCOnBoardMemoryImageDump(GetDatabase(), m_pTCEnvironment, pProcessor, pImage, tExecutionTime, bStop, pDatabaseTCFunction))
		{
			m_pTCEnvironment->Unlock();
			return TRUE;
		}
		m_pTCEnvironment->Unlock();
	}
	return FALSE;
}

BOOL CTCProcessThread::IsTCOnBoardMemoryImageDump(CONST CTMEnvironment *pTMEnvironment) CONST
{
	return m_pTCProcessEngine->IsTCOnBoardMemoryImageDump(GetDatabase(), pTMEnvironment);
}

BOOL CTCProcessThread::CheckTCOnBoardMemoryImagePatchCapabilities(CONST CDatabaseOBProcessor *pProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage) CONST
{
	return m_pTCProcessEngine->CheckTCOnBoardMemoryImagePatchCapabilities(GetDatabase(), pProcessor, pImage);
}

BOOL CTCProcessThread::EncodeTCOnBoardMemoryImagePatch(CONST CDatabaseOBProcessor *pProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage, CONST CTimeKey &tExecutionTime, CDatabaseTCFunctions &pDatabaseTCFunctions, CDatabaseTCPackets &pDatabaseTCPackets)
{
	if (m_pTMEnvironment->Lock())
	{
		if (m_pTCEnvironment->Lock())
		{
			if (m_pTCProcessEngine->EncodeTCOnBoardMemoryImagePatch(GetDatabase(), m_pTMEnvironment, m_pTCEnvironment, pProcessor, pImage, tExecutionTime, pDatabaseTCFunctions, pDatabaseTCPackets))
			{
				m_pTCEnvironment->Unlock();
				m_pTMEnvironment->Unlock();
				return TRUE;
			}
			m_pTCEnvironment->Unlock();
		}
		m_pTMEnvironment->Unlock();
	}
	return FALSE;
}

BOOL CTCProcessThread::CalculateTCOnBoardMemoryImageCRC(CONST CDatabaseOBProcessor *pProcessor, CDatabaseOBProcessorMemoryImage *pImage, LPCTSTR pszImageVersion) CONST
{
	return m_pTCProcessEngine->CalculateTCOnBoardMemoryImageCRC(GetDatabase(), pProcessor, pImage, pszImageVersion);
}

BOOL CTCProcessThread::IsTCOnBoardMemoryImagePatch(CONST CTCPacket *pTCPacket, CString &szProcessor) CONST
{
	return m_pTCProcessEngine->IsTCOnBoardMemoryImagePatch(GetDatabase(), pTCPacket, szProcessor);
}

BOOL CTCProcessThread::ConvertTimeToOBRT(CONST CTimeTag &tOBRT, UINT &nOBRT) CONST
{
	if (m_pTCProcessEngine->CanConvertTimeToOBRT(m_pTCEnvironment))
	{
		nOBRT = m_pTCProcessEngine->ConvertTimeToOBRT(m_pTCEnvironment, tOBRT);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcessThread::ConvertOBRTToTime(UINT nOBRT, CTimeTag &tOBRT) CONST
{
	if (m_pTCProcessEngine->CanConvertOBRTToTime(m_pTCEnvironment))
	{
		tOBRT = m_pTCProcessEngine->ConvertOBRTToTime(m_pTCEnvironment, nOBRT);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcessThread::CorrelateTCTransferFrameSequenceNumber()
{
	return m_pTCProcessEngine->CorrelateTCTransferFrameSequenceNumber();
}

BOOL CTCProcessThread::CanCorrelateTCTransferFrameSequenceNumber() CONST
{
	return m_pTCProcessEngine->CanCorrelateTCTransferFrameSequenceNumber();
}

BOOL CTCProcessThread::EnableTestMode(BOOL bEnable)
{
	m_bTestMode = bEnable;
	m_bUpdate = TRUE;
	return Update();
}

BOOL CTCProcessThread::IsTestModeEnabled() CONST
{
	return m_bTestMode;
}

int CTCProcessThread::Run()
{
	INT  nID[2];
	INT  nIndex;
	INT  nCount;
	INT  nEntry;
	INT  nEntries;
	INT  nItem[2];
	INT  nItems[2];
	INT  nBlockID;
	INT  nDevice;
	INT  nDevices;
	BOOL  bDevice;
	BOOL  bGrouped;
	BOOL  bCritical;
	BOOL  bProcedure;
	BOOL  bEarlierExecution;
	UINT  nExecutionMode;
	ULONGLONG  nAckFlags;
	DWORD  dwTimeout;
	DWORD  dwResult;
	DWORD  dwCount;
	DWORD  dwOffset[2];
	HANDLE  hEvents[4];
	HANDLE  hResult[2];
	HANDLE  hSuccess;
	HANDLE  hFailure;
	CString  szStep;
	CString  szThread;
	CString  szFunction;
	CString  szSequence;
	CString  szMessage[4];
	CString  szMessageType;
	CString  szTelecommand;
	CTCItem  *pItem[2];
	CTCItems  pItems[2];
	CTimeTag  tReleaseTime;
	CTimeTag  tScheduleTime;
	CTimeTag  tExecutionTime;
	CTimeSpan  tTimePeriod;
	CPtrArray  hProcedures;
	CPtrArray  hItemResults[2];
	CUIntArray  nProcedureIDs;
	CUIntArray  nItemIDs[2];
	CStringArray  szItems[2];
	CStringArray  szProcedures;
	CTimeTagArray  tItemTimes;
	CTCUplinkDevice  cDevice;
	CTCUplinkDevices  pDevices;

	for (hEvents[0] = m_cUpdate[0], hEvents[1] = m_pTCEnvironment->SignalMessageQueue(), hEvents[2] = m_pTCEnvironment->SignalTCFunctionQueue(), hEvents[3] = m_cCommandUpdateEvent, dwTimeout = 0; ((dwResult = Wait(hEvents, (dwCount = (DWORD)(sizeof(hEvents) / sizeof(HANDLE))), FALSE, dwTimeout)) > WAIT_OBJECT_0 && dwResult <= WAIT_OBJECT_0 + dwCount) || dwResult == WAIT_TIMEOUT; dwTimeout = (HasTCUplinkDevices()) ? ((m_cTCDevice.GetStatusIndication() & IODEVICE_STATUS_CONNECTED) ? (1000 * (DWORD)(m_cTCDevice.IsStandBy(tTimePeriod)*tTimePeriod.GetTotalSeconds())) : 0) : INFINITE)
	{
		if (dwResult == WAIT_OBJECT_0 + 1 || dwResult == WAIT_TIMEOUT)
		{
			for (bDevice = FALSE; dwResult == WAIT_OBJECT_0 + 1; )
			{
				for (GetActiveTCUplinkDevice(&cDevice); m_bUpdate; )
				{
					if (!IsTestModeEnabled() || !m_cTCDevice.Compare(&cDevice) || !m_cTCDevice.IsLocal())
					{
						for (StopDevice(); m_cUpdate[1].SetEvent() && m_hUpdate != (HANDLE)NULL; )
						{
							Wait(m_hUpdate, FALSE);
							break;
						}
						m_cTCDevice.SetStatusIndication((m_cTCDevice.GetStatusIndication() & ~(IODEVICE_STATUS_GOOD | IODEVICE_STATUS_WARNING | IODEVICE_STATUS_CONNECTED)) | IODEVICE_STATUS_ERROR | IODEVICE_STATUS_NOTCONNECTED);
						cDevice.SetStatusIndication((cDevice.GetStatusIndication() & ~(IODEVICE_STATUS_GOOD | IODEVICE_STATUS_WARNING | IODEVICE_STATUS_CONNECTED)) | IODEVICE_STATUS_ERROR | IODEVICE_STATUS_NOTCONNECTED);
						m_cTCDevice.SetStatus(STRING(IDS_TELECOMMANDUPLINKDEVICE_STATUS_NOTREADY));
						cDevice.SetStatus(STRING(IDS_TELECOMMANDUPLINKDEVICE_STATUS_NOTREADY));
						SetActiveTCUplinkDevice(&cDevice);
						m_hUpdate = (HANDLE)NULL;
						m_bUpdate = FALSE;
					}
					break;
				}
				for (; !m_cTCDevice.Compare(&cDevice); )
				{
					if (m_cTCDevice.GetDeviceBrand().IsEmpty() || m_cTCDevice.GetDeviceName().IsEmpty())
					{
						SetDevice(&cDevice);
						bDevice = TRUE;
						break;
					}
					if (m_cTCDevice.IsOpen())
					{
						if (m_cTCDevice.IsLocal() || !IsTestModeEnabled())
						{
							if (m_cTCDevice.Update(&cDevice, bDevice) && !bDevice)
							{
								for (; !m_cTCDevice.Compare(&cDevice); )
								{
									SetDevice(&cDevice);
									break;
								}
								if (cDevice.IsStandBy())
								{
									UpdateTelecommandStatus(&cDevice);
									break;
								}
								bDevice = TRUE;
							}
						}
						StopDevice();
						break;
					}
					if (m_cTCDevice.Open())
					{
						if (m_cTCDevice.IsLocal() || !IsTestModeEnabled())
						{
							if (m_cTCDevice.Update(&cDevice, bDevice) && !bDevice)
							{
								for (; !m_cTCDevice.Compare(&cDevice); )
								{
									SetDevice(&cDevice);
									break;
								}
								if (!cDevice.IsStandBy())
								{
									m_cTCDevice.Close();
									break;
								}
								bDevice = TRUE;
							}
						}
						m_cTCDevice.Close();
					}
					break;
				}
				if (bDevice)
				{
					StartDevice();
					break;
				}
				break;
			}
			for (; dwResult == WAIT_TIMEOUT; )
			{
				if (StartDevice())
				{
					bDevice = TRUE;
					break;
				}
				for (nDevice = 0, nDevices = m_pTCDevices.EnumBackupDevices(&m_cTCDevice, pDevices), GetDevice(&cDevice); (dwResult = Wait(m_cUpdate, sizeof(m_cUpdate) / sizeof(CEvent) - 1, FALSE, TCPROCESSTHREAD_DEVICE_TIMEOUT, FALSE)) == WAIT_TIMEOUT && nDevice < nDevices; nDevice++)
				{
					if (StartDevice(pDevices.GetAt(nDevice)))
					{
						bDevice = TRUE;
						break;
					}
				}
				if (!bDevice)
				{
					if (dwResult == WAIT_OBJECT_0 + 1)
					{
						Update();
						break;
					}
					if (dwResult == WAIT_TIMEOUT)
					{
						SetDevice(&cDevice);
						break;
					}
				}
				break;
			}
			if (bDevice) SetActiveTCUplinkDevice(&m_cTCDevice);
			if (dwResult == WAIT_TIMEOUT) continue;
		}
		if (dwResult == WAIT_OBJECT_0 + 2)
		{
			while (m_pTCEnvironment->RemoveMessage(nID[1], szMessageType, szMessage[0]))
			{
				if (m_pTCProceduresMonitorWnd) m_pTCProceduresMonitorWnd->AlertProcedure(-nID[1] - 1, (szMessageType == STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_TYPE_SUCCESS)) ? TCPROCEDURESMONITORITEM_ALERTTYPE_INFORMATIONAL : ((szMessageType == STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_TYPE_WARNING)) ? TCPROCEDURESMONITORITEM_ALERTTYPE_WARNING : ((szMessageType == STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_TYPE_ERROR)) ? TCPROCEDURESMONITORITEM_ALERTTYPE_ERROR : ((szMessageType == STRING(IDS_TELECOMMANDPROCEDUREMESSAGE_TYPE_ALERT)) ? TCPROCEDURESMONITORITEM_ALERTTYPE_ALERT : TCPROCEDURESMONITORITEM_ALERTTYPE_INFORMATIONAL))), szMessage[0]);
				continue;
			}
			continue;
		}
		if (dwResult == WAIT_OBJECT_0 + 3)
		{
			for (szItems[0].RemoveAll(), szItems[1].RemoveAll(), nItemIDs[0].RemoveAll(), nItemIDs[1].RemoveAll(), tItemTimes.RemoveAll(), hItemResults[0].RemoveAll(), hItemResults[1].RemoveAll(); m_pTCEnvironment->RemoveTCFunction(nID[0], nID[1], szThread, szStep, szSequence, szFunction, bProcedure, nEntry, nEntries, tScheduleTime, tReleaseTime, dwOffset[0], tExecutionTime, dwOffset[1], bEarlierExecution, nBlockID, bGrouped, bCritical, nExecutionMode, nAckFlags, hSuccess, hFailure); )
			{
				if ((pItem[0] = (m_pTCProceduresMonitorWnd != (CTCProceduresMonitorWnd *)NULL) ? new CTCItem : (CTCItem *)NULL))
				{
					for (nIndex = 0, nCount = m_pTCEnvironment->EnumTCProcedures(szProcedures, nProcedureIDs, hProcedures); nIndex < nCount; nIndex++)
					{
						if (nProcedureIDs.GetAt(nIndex) == nID[1]) break;
						continue;
					}
					for (nItem[0] = 0, nItems[0] = (INT)szItems[0].GetSize(), nItem[1] = -1; nItem[0] < nItems[0]; nItem[0]++)
					{
						for (nItem[1] = (szItems[0].GetAt(nItem[0]) == szSequence && tItemTimes.GetAt(nItem[0]) == tScheduleTime) ? (nItems[0] - 1) : -1; nItem[1] >= 0; nItem[1]--)
						{
							if (szItems[0].GetAt(nItem[1]) == szSequence  &&  tItemTimes.GetAt(nItem[1]) == tScheduleTime) break;
							continue;
						}
						if (nItem[1] >= 0)
						{
							szItems[0].InsertAt(nItem[1] + 1, szSequence);
							szItems[1].InsertAt(nItem[1] + 1, szFunction);
							nItemIDs[0].InsertAt(nItem[1] + 1, nEntry);
							nItemIDs[1].InsertAt(nItem[1] + 1, nEntries);
							tItemTimes.InsertAt(nItem[1] + 1, tScheduleTime);
							hItemResults[0].InsertAt(nItem[1] + 1, hSuccess);
							hItemResults[1].InsertAt(nItem[1] + 1, hFailure);
							break;
						}
					}
					if (nItem[1] < 0)
					{
						for (nItem[0] = 0, nItems[0] = (nIndex == nCount || !Initialize(szProcedures.GetAt(nIndex), nID[0], nID[1], szThread, szStep, szSequence, szFunction, bProcedure, nEntry, nEntries, tScheduleTime, tReleaseTime, dwOffset[0], tExecutionTime, dwOffset[1], bEarlierExecution, nBlockID, bGrouped, bCritical, nExecutionMode, nAckFlags, (HINSTANCE)hProcedures.GetAt(nIndex), hSuccess, hFailure, pItem[0]) || pItems[0].Add(pItem[0]) < 0) ? (INT)pItems[0].GetSize() : -1; nItem[0] < nItems[0]; nItem[0]++)
						{
							if ((pItem[1] = pItems[0].GetAt(nItem[0])) && pItem[1]->GetMembership() == szSequence  &&  pItem[1]->GetLoadTime() == tScheduleTime)
							{
								szItems[0].Add(pItem[1]->GetMembership());
								szItems[1].Add(pItem[1]->GetName());
								nItemIDs[0].Add(pItem[1]->GetMembershipID());
								nItemIDs[1].Add(pItem[1]->GetMembershipSize());
								tItemTimes.Add(pItem[1]->GetLoadTime());
								hItemResults[0].Add((pItem[1]->GetVerificationHandles(hResult[0], hResult[1])) ? hResult[0] : (HANDLE)NULL);
								hItemResults[1].Add((pItem[1]->GetVerificationHandles(hResult[0], hResult[1])) ? hResult[1] : (HANDLE)NULL);
								pItems[0].RemoveAt(nItem[0]);
								delete pItem[1];
								nItems[0]--;
								nItem[0]--;
							}
						}
						if (nItems[0] >= 0)
						{
							szItems[0].Add(szSequence);
							szItems[1].Add(szFunction);
							nItemIDs[0].Add(nEntry);
							nItemIDs[1].Add(nEntries);
							tItemTimes.Add(tScheduleTime);
							hItemResults[0].Add(hSuccess);
							hItemResults[1].Add(hFailure);
							delete pItem[0];
						}
						continue;
					}
					delete pItem[0];
				}
			}
			for (nItem[0] = 0, nItems[0] = (INT)pItems[0].GetSize(); nItem[0] < nItems[0]; nItem[0]++)
			{
				if ((pItem[0] = (pItems[0].Collect(nItem[0], pItems[1]) > 0) ? pItems[1].GetAt((INT)pItems[1].GetUpperBound()) : (CTCItem *)NULL) && (pItem[0]->GetMembershipID() == (UINT)-1 || pItem[0]->GetMembershipSize() == (UINT)pItems[1].GetSize()))
				{
					for (nItem[1] = 0, nItems[1] = (INT)pItems[1].GetSize(); nItem[1] < nItems[1]; nItem[1]++)
					{
						if ((pItem[1] = pItems[1].GetAt(nItem[1])))
						{
							if ((nIndex = pItems[0].Find(pItem[1])) >= 0)
							{
								delete pItems[0].GetAt(nIndex);
								pItems[0].RemoveAt(nIndex);
								nItems[0] = nItems[0] - 1;
								nItem[0] = -1;
							}
						}
					}
					for (nItem[1] = 0, nItems[1] = (!Initialize(pItems[1]) || (!AuthorizeTelecommands(pItems[1]) && !DispatchTelecommands(pItems[1]))) ? (INT)pItems[1].GetSize() : 0; nItem[1] < nItems[1]; nItem[1]++)
					{
						if ((pItem[1] = pItems[1].GetAt(nItem[1])))
						{
							szItems[0].Add(pItem[1]->GetMembership());
							szItems[1].Add(pItem[1]->GetName());
							nItemIDs[0].Add(pItem[1]->GetMembershipID());
							nItemIDs[1].Add(pItem[1]->GetMembershipSize());
							tItemTimes.Add(pItem[1]->GetLoadTime().GetTime());
							hItemResults[0].Add((pItem[1]->GetVerificationHandles(hSuccess, hFailure)) ? hSuccess : (HANDLE)NULL);
							hItemResults[1].Add((pItem[1]->GetVerificationHandles(hSuccess, hFailure)) ? hFailure : (HANDLE)NULL);
						}
					}
					continue;
				}
				if (!pItems[1].GetSize())
				{
					delete pItems[0].GetAt(nItem[0]);
					pItems[0].RemoveAt(nItem[0]);
					nItems[0]--;
					nItem[0]--;
				}
			}
			for (nItem[0] = 0, nItems[0] = (INT)szItems[0].GetSize(); nItem[0] < nItems[0]; nItem[0]++)
			{
				for (nItem[1] = nItem[0], nItems[1] = nItems[0], szMessage[0].Empty(), nCount = 0; nItem[1] < nItems[1]; nItem[1]++, nCount++)
				{
					if ((!szItems[0].GetAt(nItem[0]).IsEmpty() && szItems[0].GetAt(nItem[0]) == szItems[0].GetAt(nItem[1]) && tItemTimes.GetAt(nItem[0]) == tItemTimes.GetAt(nItem[1])) || szMessage[0].IsEmpty())
					{
						szTelecommand.Format(STRING(IDS_TCPROCEDURESMONITOR_ALERTMESSAGE_TELECOMMAND_FORMAT), (LPCTSTR)szItems[1].GetAt(nItem[1]));
						szMessage[0] += (!szMessage[0].IsEmpty()) ? (STRING(IDS_TCPROCEDURESMONITOR_ALERTMESSAGE_TELECOMMAND_DELIMITER) + szTelecommand) : szTelecommand;
						if (szItems[0].GetAt(nItem[1]).IsEmpty()) break;
					}
				}
				for (szMessage[1].Empty(), szMessage[2].Empty(), szMessage[3].Empty(); nItem[1] < nItems[1]; )
				{
					szMessage[1].Format(STRING(IDS_TCPROCEDURESMONITOR_ALERTMESSAGE_DISPATCHFAILURE), (LPCTSTR)szMessage[0]);
					break;
				}
				for (; nItem[1] == nItems[1] && nCount == 1; )
				{
					szMessage[2].Format(STRING(IDS_TCPROCEDURESMONITOR_ALERTMESSAGE_DISPATCHMEMBERFAILURE), (LPCTSTR)szMessage[0], (LPCTSTR)szItems[0].GetAt(nItem[0]));
					break;
				}
				for (; nItem[1] == nItems[1] && nCount > 1; )
				{
					szMessage[3].Format(STRING(IDS_TCPROCEDURESMONITOR_ALERTMESSAGE_DISPATCHMEMBERSFAILURE), (LPCTSTR)szMessage[0], (LPCTSTR)szItems[0].GetAt(nItem[0]));
					break;
				}
				for (nItem[1] = nItems[1] - 1, nItem[0] = nItem[0] - 1; nItem[0] < nItem[1]; nItem[1]--)
				{
					if (((szItems[0].GetAt(nItem[0] + 1) == szItems[0].GetAt(nItem[1]) && !szItems[0].GetAt(nItem[0] + 1).IsEmpty()) || (szItems[1].GetAt(nItem[0] + 1) == szItems[1].GetAt(nItem[1]) && szItems[0].GetAt(nItem[0] + 1).IsEmpty())) && tItemTimes.GetAt(nItem[0] + 1) == tItemTimes.GetAt(nItem[1]))
					{
						for (hFailure = (HANDLE)hItemResults[1].GetAt(nItem[1]), szItems[0].RemoveAt(nItem[1]), szItems[1].RemoveAt(nItem[1]), nItemIDs[0].RemoveAt(nItem[1]), nItemIDs[1].RemoveAt(nItem[1]), tItemTimes.RemoveAt(nItem[1]), hItemResults[0].RemoveAt(nItem[1]), hItemResults[1].RemoveAt(nItem[1]); hFailure != (HANDLE)NULL; )
						{
							SetEvent(hFailure);
							break;
						}
						nItems[0]--;
					}
				}
				m_pTCProceduresMonitorWnd->AlertProcedure(-nID[1] - 1, TCPROCEDURESMONITORITEM_ALERTTYPE_ERROR, (!szMessage[1].IsEmpty()) ? szMessage[1] : (!szMessage[2].IsEmpty()) ? szMessage[2] : szMessage[3]);
			}
			continue;
		}
		for (Lock(); dwResult == WAIT_OBJECT_0 + 4; )
		{
			UpdateQueues();
			break;
		}
		Unlock();
	}
	StopDevice();
	return ExitInstance();
}

BOOL CTCProcessThread::Initialize()
{
	INT  nQueue[2];
	INT  nQueues[2];
	BOOL  bQueueFlag[11];
	CTimeSpan  tTimeWindow[2];
	CUIntArray  nSubSystemIDs;
	CUIntArray  nSubSystemStatus;
	CUIntArray  nOnBoardQueueIDs[2];
	CUIntArray  nOnBoardQueueLimits;
	CUIntArray  tOnBoardQueueTimeouts;
	CStringArray  szOnBoardQueues[2];
	CStringArray  szOnBoardQueueUnits;
	CStringArray  szSubSystemEvents[2];
	CTCOnBoardBufferQueue  *pOnBoardQueue;
	CTCProcessCommandSources  pCommandSources;
	CTCProcessCommandSourceInfo  *pCommandSourceInfo[3];

	if ((pCommandSourceInfo[0] = new CTCProcessCommandSourceInfo))
	{
		if ((pCommandSourceInfo[1] = new CTCProcessCommandSourceInfo))
		{
			if ((pCommandSourceInfo[2] = new CTCProcessCommandSourceInfo))
			{
				for (pCommandSourceInfo[0]->SetSourceType(TCSERVICE_COMMANDSOURCETYPE_MANUALSTACK); m_pTCManualStackWnd; )
				{
					pCommandSourceInfo[0]->SetTelecommandingMode(m_pTCManualStackWnd->GetTelecommandingMode());
					pCommandSourceInfo[0]->SetTelecommandingState(m_pTCManualStackWnd->GetTelecommandingState());
					pCommandSourceInfo[0]->SetTelecommandingChecks(m_pTCManualStackWnd->GetTelecommandingChecks());
					pCommandSourceInfo[0]->EnableTelecommandingInterlockMode(m_pTCManualStackWnd->IsTelecommandingInterlockModeEnabled());
					pCommandSourceInfo[0]->EnableTelecommandingReleaseWaitMode(m_pTCManualStackWnd->IsTelecommandingReleaseWaitModeEnabled());
					pCommandSourceInfo[0]->EnableTelecommandingAutoRejectionMode(m_pTCManualStackWnd->IsTelecommandingAutoRejectionModeEnabled());
					pCommandSourceInfo[0]->SetDefaultReleaseTimeWindow((m_pTCManualStackWnd->GetDefaultReleaseTimeWindow(tTimeWindow[0])) ? tTimeWindow[0] : TCSERVICE_COMMANDHANDLERTIMEWINDOW_DEFAULTRELEASEINTERVAL);
					pCommandSourceInfo[0]->SetDispatchTimeWindow((m_pTCManualStackWnd->GetDispatchTimeWindow(tTimeWindow[1])) ? tTimeWindow[1] : TCSERVICE_COMMANDHANDLERTIMEWINDOW_DISPATCHINTERVAL);
					break;
				}
				for (pCommandSourceInfo[1]->SetSourceType(TCSERVICE_COMMANDSOURCETYPE_AUTOMATICSTACK); m_pTCAutomaticStackWnd != (CTCAutomaticStackWnd *)NULL && m_pTCAutomaticStackWnd->GetSubSystemChecks(nSubSystemIDs, szSubSystemEvents[0], szSubSystemEvents[1], nSubSystemStatus); )
				{
					pCommandSourceInfo[1]->SetTelecommandingMode(m_pTCAutomaticStackWnd->GetTelecommandingMode());
					pCommandSourceInfo[1]->SetTelecommandingState(m_pTCAutomaticStackWnd->GetTelecommandingState());
					pCommandSourceInfo[1]->SetTelecommandingChecks(m_pTCAutomaticStackWnd->GetTelecommandingChecks());
					pCommandSourceInfo[1]->EnableTelecommandingInterlockMode(m_pTCAutomaticStackWnd->IsTelecommandingInterlockModeEnabled());
					pCommandSourceInfo[1]->EnableTelecommandingReleaseWaitMode(m_pTCAutomaticStackWnd->IsTelecommandingReleaseWaitModeEnabled());
					pCommandSourceInfo[1]->EnableTelecommandingAutoRejectionMode(m_pTCAutomaticStackWnd->IsTelecommandingAutoRejectionModeEnabled());
					pCommandSourceInfo[1]->SetSubSystemChecks(nSubSystemIDs, szSubSystemEvents[0], szSubSystemEvents[1], nSubSystemStatus);
					pCommandSourceInfo[1]->SetDefaultReleaseTimeWindow((m_pTCAutomaticStackWnd->GetDefaultReleaseTimeWindow(tTimeWindow[0])) ? tTimeWindow[0] : TCSERVICE_COMMANDHANDLERTIMEWINDOW_DEFAULTRELEASEINTERVAL);
					pCommandSourceInfo[1]->SetDispatchTimeWindow((m_pTCAutomaticStackWnd->GetDispatchTimeWindow(tTimeWindow[1])) ? tTimeWindow[1] : TCSERVICE_COMMANDHANDLERTIMEWINDOW_DISPATCHINTERVAL);
					break;
				}
				for (pCommandSourceInfo[2]->SetSourceType(TCSERVICE_COMMANDSOURCETYPE_PROCEDURESMONITOR); m_pTCProceduresMonitorWnd; )
				{
					pCommandSourceInfo[2]->SetTelecommandingMode(m_pTCProceduresMonitorWnd->GetTelecommandingMode());
					pCommandSourceInfo[2]->SetTelecommandingState(m_pTCProceduresMonitorWnd->GetTelecommandingState());
					pCommandSourceInfo[2]->SetTelecommandingChecks(m_pTCProceduresMonitorWnd->GetTelecommandingChecks());
					pCommandSourceInfo[2]->EnableTelecommandingReleaseWaitMode(m_pTCProceduresMonitorWnd->IsTelecommandingReleaseWaitModeEnabled());
					pCommandSourceInfo[2]->EnableTelecommandingInterlockMode(TRUE);
					pCommandSourceInfo[2]->EnableTelecommandingAutoRejectionMode(FALSE);
					pCommandSourceInfo[2]->SetDefaultReleaseTimeWindow(0);
					pCommandSourceInfo[2]->SetDispatchTimeWindow(0);
					break;
				}
				if (pCommandSources.Add(pCommandSourceInfo[0]) >= 0)
				{
					if (pCommandSources.Add(pCommandSourceInfo[1]) >= 0)
					{
						if (pCommandSources.Add(pCommandSourceInfo[2]) >= 0)
						{
							for (Lock(), nQueue[0] = 0, nQueues[0] = (!m_pTCOnBoardBufferQueues.GetSize()) ? EnumTCOnBoardBufferTypes(szOnBoardQueues[0]) : 0, SetCommandSources(pCommandSources); nQueue[0] < nQueues[0]; nQueue[0]++)
							{
								for (nQueue[1] = 0, nQueues[1] = EnumTCOnBoardBufferQueues(szOnBoardQueues[0].GetAt(nQueue[0]), szOnBoardQueues[1], nOnBoardQueueIDs[0], nOnBoardQueueIDs[1], nOnBoardQueueLimits, szOnBoardQueueUnits, tOnBoardQueueTimeouts); nQueue[1] < nQueues[1]; nQueue[1]++)
								{
									if (CheckTCOnBoardBufferQueue(szOnBoardQueues[0].GetAt(nQueue[0]), szOnBoardQueues[1].GetAt(nQueue[1]), bQueueFlag[0], bQueueFlag[1], bQueueFlag[2], bQueueFlag[3], bQueueFlag[4], bQueueFlag[5], bQueueFlag[6], bQueueFlag[7], bQueueFlag[8], bQueueFlag[9], bQueueFlag[10]))
									{
										if ((pOnBoardQueue = new CTCOnBoardBufferQueue))
										{
											pOnBoardQueue->SetType(szOnBoardQueues[0].GetAt(nQueue[0]));
											pOnBoardQueue->SetName(szOnBoardQueues[1].GetAt(nQueue[1]));
											pOnBoardQueue->SetFlags((bQueueFlag[0]) ? (pOnBoardQueue->GetFlags() | TCONBOARDBUFFERQUEUE_FLAG_ALLOWSTATUSCHANGE) : pOnBoardQueue->GetFlags());
											pOnBoardQueue->SetFlags((bQueueFlag[1]) ? (pOnBoardQueue->GetFlags() | TCONBOARDBUFFERQUEUE_FLAG_ALLOWDOWNLOADALL) : pOnBoardQueue->GetFlags());
											pOnBoardQueue->SetFlags((bQueueFlag[2]) ? (pOnBoardQueue->GetFlags() | TCONBOARDBUFFERQUEUE_FLAG_ALLOWDOWNLOADBYSUBSYSTEM) : pOnBoardQueue->GetFlags());
											pOnBoardQueue->SetFlags((bQueueFlag[3]) ? (pOnBoardQueue->GetFlags() | TCONBOARDBUFFERQUEUE_FLAG_ALLOWDOWNLOADBYSEQUENCECOUNTER) : pOnBoardQueue->GetFlags());
											pOnBoardQueue->SetFlags((bQueueFlag[4]) ? (pOnBoardQueue->GetFlags() | TCONBOARDBUFFERQUEUE_FLAG_ALLOWDOWNLOADBYRANGE) : pOnBoardQueue->GetFlags());
											pOnBoardQueue->SetFlags((bQueueFlag[5]) ? (pOnBoardQueue->GetFlags() | TCONBOARDBUFFERQUEUE_FLAG_ALLOWDOWNLOADBYTIMERANGE) : pOnBoardQueue->GetFlags());
											pOnBoardQueue->SetFlags((bQueueFlag[6]) ? (pOnBoardQueue->GetFlags() | TCONBOARDBUFFERQUEUE_FLAG_ALLOWDELETEALL) : pOnBoardQueue->GetFlags());
											pOnBoardQueue->SetFlags((bQueueFlag[7]) ? (pOnBoardQueue->GetFlags() | TCONBOARDBUFFERQUEUE_FLAG_ALLOWDELETEBYSUBSYSTEM) : pOnBoardQueue->GetFlags());
											pOnBoardQueue->SetFlags((bQueueFlag[8]) ? (pOnBoardQueue->GetFlags() | TCONBOARDBUFFERQUEUE_FLAG_ALLOWDELETEBYSEQUENCECOUNTER) : pOnBoardQueue->GetFlags());
											pOnBoardQueue->SetFlags((bQueueFlag[9]) ? (pOnBoardQueue->GetFlags() | TCONBOARDBUFFERQUEUE_FLAG_ALLOWDELETEBYRANGE) : pOnBoardQueue->GetFlags());
											pOnBoardQueue->SetFlags((bQueueFlag[10]) ? (pOnBoardQueue->GetFlags() | TCONBOARDBUFFERQUEUE_FLAG_ALLOWDELETEBYTIMERANGE) : pOnBoardQueue->GetFlags());
											pOnBoardQueue->SetAPID(nOnBoardQueueIDs[0].GetAt(nQueue[1]));
											pOnBoardQueue->SetSubScheduleID(nOnBoardQueueIDs[1].GetAt(nQueue[1]));
											pOnBoardQueue->SetLimit(nOnBoardQueueLimits.GetAt(nQueue[1]));
											pOnBoardQueue->SetUnit(szOnBoardQueueUnits.GetAt(nQueue[1]));
											pOnBoardQueue->SetTimeout(tOnBoardQueueTimeouts.GetAt(nQueue[1]));
											if (m_pTCOnBoardBufferQueues.Add(pOnBoardQueue) >= 0) continue;
											delete pOnBoardQueue;
										}
									}
								}
							}
							Unlock();
							return TRUE;
						}
						delete pCommandSourceInfo[2];
						return FALSE;
					}
					delete pCommandSourceInfo[1];
					return FALSE;
				}
				delete pCommandSourceInfo[2];
			}
			delete pCommandSourceInfo[1];
		}
		delete pCommandSourceInfo[0];
	}
	return FALSE;
}

BOOL CTCProcessThread::Uninitialize()
{
	CByteArray  nData;
	CTCProcessCommandSources  pCommandSources;
	CProfile  cProfile;

	if (m_pTCEnvironment->GetType() != 0)
	{
		for (; GetCommandSources(pCommandSources) && pCommandSources.GetSize() > 0 && GetContentsData(nData); )
		{
			if (!cProfile.SetTelecommandServiceContentsInfo(nData)) nData.RemoveAll();
			break;
		}
	}
	pCommandSources.RemoveAll();
	SetCommandSources(pCommandSources);
	m_pTCOnBoardBufferQueues.RemoveAll();
	return(nData.GetSize() > 0);
}

BOOL CTCProcessThread::Initialize(CTCItems &pItems) CONST
{
	INT  nItem;
	INT  nItems;
	CTCItem  *pItem;
	CString  szMembership;
	CString  szDescription;
	CDatabaseTCSequence  *pSequence;

	for (nItem = 0, nItems = (INT)pItems.GetSize(); nItem < nItems; nItem++)
	{
		if ((pItem = pItems.GetAt(nItem)) != (CTCItem *)NULL)
		{
			if (lstrlen((szMembership = pItem->GetMembership())) > 0 && !nItem)
			{
				if ((pSequence = GetDatabase()->GetTCSequences()->GetAt(GetDatabase()->GetTCSequences()->Find(szMembership))))
				{
					szDescription = pSequence->GetDescription();
					continue;
				}
				break;
			}
			if (!szMembership.IsEmpty()) pItem->SetMembershipDescription(szDescription);
		}
	}
	return((nItem == nItems  &&  nItems > 0) ? TRUE : FALSE);
}
BOOL CTCProcessThread::Initialize(LPCTSTR pszProcedure, INT nProcedureID, INT nProcessID, LPCTSTR pszThread, LPCTSTR pszStep, LPCTSTR pszSequence, LPCTSTR pszFunction, BOOL bProcedure, INT nEntry, INT nEntries, CONST CTimeTag &tScheduleTime, CONST CTimeTag &tReleaseTime, DWORD dwReleaseOffset, CONST CTimeTag &tExecutionTime, DWORD dwExecutionOffset, BOOL bEarlierExecution, INT nBlockID, BOOL bGrouped, BOOL bCritical, UINT nExecutionMode, ULONGLONG nAckFlags, HINSTANCE hModule, HANDLE hSuccess, HANDLE hFailure, CTCItem *pItem) CONST
{
	INT  nPos;
	INT  nPath;
	INT  nPaths;
	INT  nLength;
	CString  szFilePathStub;
	CFileFindEx  cFileFind;
	CStringArray  szFilePaths;
	CDatabaseTCPacket  *pPacket;
	CDatabaseTCFunction  *pFunction;
	CLogicalDrives  cLogicalDrives;
	CComputerToken  cComputerToken;
	TCHAR  szFilePath[MAX_PATH];

	for (pItem->SetName(pszFunction), pItem->SetSourceType(TCITEM_SOURCETYPE_PROCEDURESMONITOR), pItem->SetType((!bProcedure) ? TCITEM_TYPE_FUNCTION : TCITEM_TYPE_PROCEDURE), pItem->SetFlags(((nBlockID >= 0) ? TCITEM_LINKAGEFLAG_BLOCKED : 0) | ((bGrouped) ? TCITEM_LINKAGEFLAG_GROUPED : 0) | ((bCritical) ? TCITEM_CHECKFLAG_AUTHORIZEABLE : 0) | (((!lstrlen(pszSequence) && (nAckFlags & TCFUNCTION_ACKFLAG_ACCEPTANCE)) || (lstrlen(pszSequence) > 0 && (nAckFlags & TCSEQUENCEENTRY_ACKFLAG_ACCEPTANCE))) ? TCITEM_ACKNOWLEDGEFLAG_ACCEPTANCE : 0) | (((!lstrlen(pszSequence) && (nAckFlags & TCFUNCTION_ACKFLAG_START)) || (lstrlen(pszSequence) > 0 && (nAckFlags & TCSEQUENCEENTRY_ACKFLAG_START))) ? TCITEM_ACKNOWLEDGEFLAG_START : 0) | (((!lstrlen(pszSequence) && (nAckFlags & TCFUNCTION_ACKFLAG_PROGRESS)) || (lstrlen(pszSequence) > 0 && (nAckFlags & TCSEQUENCEENTRY_ACKFLAG_PROGRESS))) ? TCITEM_ACKNOWLEDGEFLAG_PROGRESS : 0) | (((!lstrlen(pszSequence) && (nAckFlags & TCFUNCTION_ACKFLAG_COMPLETION)) || (lstrlen(pszSequence) > 0 && (nAckFlags & TCSEQUENCEENTRY_ACKFLAG_COMPLETION))) ? TCITEM_ACKNOWLEDGEFLAG_COMPLETION : 0)), pItem->SetMembership(pszSequence), pItem->SetMembershipID(max(nEntry - 1, -1)), pItem->SetMembershipSize(nEntries), pItem->SetLoadTime(tScheduleTime), pItem->SetDispatchTime(CTimeTag()), pItem->SetReleaseBlockID(nBlockID), pItem->SetExecutionMode(nExecutionMode), pItem->SetVerificationProcedure(pszProcedure), pItem->SetVerificationThread(pszThread), pItem->SetVerificationStep(pszStep), pItem->SetVerificationHandles(hSuccess, hFailure), pItem->SetStatus(TCITEM_STATUS_DISPATCHED); ((pPacket = ((pFunction = (!bProcedure) ? GetDatabase()->GetTCFunctions()->GetAt(GetDatabase()->GetTCFunctions()->Find(pszFunction)) : (CDatabaseTCFunction *)NULL)) ? GetDatabase()->GetTCPackets()->GetAt(pFunction->GetTCPacketRef()) : (CDatabaseTCPacket *)NULL) && pItem->CDatabaseTCFunction::Copy(pFunction) && pItem->SetTCPacket(pPacket)) || bProcedure; )
	{
		for (pItem->SetReleaseTimeWindow(tReleaseTime); dwReleaseOffset > 0; )
		{
			pItem->SetReleaseTimeWindow(dwReleaseOffset, FALSE);
			break;
		}
		for (pItem->SetExecutionTime(tExecutionTime); !bProcedure && (pFunction->GetAttributes() & TCFUNCTION_EXETYPE_TIMETAG) && tExecutionTime == 0; )
		{
			pItem->SetExecutionTimeOffset(dwExecutionOffset, bEarlierExecution);
			break;
		}
		for (pItem->SetVerificationProcessID(nProcessID); GetModuleFileName(hModule, szFilePath, sizeof(szFilePath) / sizeof(TCHAR)) > 0; )
		{
			for (nPath = 0, nPaths = GetNetworkBrowseService()->EnumNetworkDisks(szFilePaths), szFilePathStub = szFilePath; nPath < nPaths; nPath++)
			{
				if (!szFilePaths.GetAt(nPath).Left(cComputerToken.GetComputerUNCName().GetLength()).CompareNoCase(cComputerToken.GetComputerUNCName()))
				{
					for (; (nPos = szFilePathStub.Find(cLogicalDrives.GetPathDelimiter())) >= 0; szFilePathStub = szFilePathStub.Mid(1))
					{
						if (cFileFind.FindFile(szFilePaths.GetAt(nPath) + (szFilePathStub = szFilePathStub.Mid(nPos))))
						{
							cFileFind.Close();
							break;
						}
					}
					if (nPos >= 0)
					{
						CopyMemory(szFilePath, (LPCTSTR)(szFilePaths.GetAt(nPath) + szFilePathStub), ((nLength = szFilePaths.GetAt(nPath).GetLength() + szFilePathStub.GetLength()) < sizeof(szFilePath) / sizeof(TCHAR)) ? (nLength + 1)*sizeof(TCHAR) : 0);
						break;
					}
				}
				szFilePathStub = szFilePath;
			}
			pItem->SetVerificationModuleFileName(szFilePath);
			break;
		}
		return((!bProcedure) ? m_pTCProceduresMonitorWnd->InitializeTelecommand(nProcedureID, pszThread, pszStep, pszFunction, nEntry, pItem) : TRUE);
	}
	return FALSE;
}
BOOL CTCProcessThread::Initialize(HINSTANCE hModule, LPCTSTR pszName, INT nID, CONST CPtrArray &hEvents, CONST CTMEnvironment *pTMEnvironment, CTCItem *pItem)
{
	INT  nStage;
	INT  nStages;
	INT  nIdentifier;
	INT  nIdentifiers;
	CString  szProcedure[4];
	CPtrArray  pIdentifiers;
	CUIntArray  nIdentifierTypes;
	CUIntArray  nIdentifierAttributes;
	CUIntArray  nStageIDs;
	CUIntArray  nStageTimeWindow[3];
	CStringArray  szErrorParameters;
	CStringArray  szIdentifiers;
	CTMParameter  *pTMParameter;
	CTMParameters  pTMParameters;
	CDatabaseTMParameter  *pParameter;
	BOOL(__cdecl *pInitialize)(CONST CDatabaseEngine *pDatabase, CTCProcessEngine *pTCProcessEngine, CTCEnvironment *pTCEnvironment, LPCTSTR pszName, INT nProcedureID, INT nID, UINT nExecutionMode, BOOL bSynchronized, CONST CPtrArray &hEvents, CStringArray &szErrorParameters);
	BOOL(__cdecl *pInitializeParameters)(INT nID, CONST CTMParameters &pTMParameters, double fTotalTMBandwidth, double fAvailableTMBandwidth, double fMaxDiagnosticTMBandwidth, double fAvailableDiagnosticTMBandwidth, CONST CTimeTag &tTMBandwidth);
	BOOL(__cdecl *pEnumThreadTCFunctionExecutionVerificationTimeWindows)(INT nID, LPCTSTR pszThread, LPCTSTR pszStep, INT nEntry, CUIntArray &nStageIDs, CUIntArray &nStageTimeWindowOffsets, CUIntArray &nStageTimeWindowSizes, CUIntArray &nStageTimeWindowUncertainties);
	INT(__cdecl *pEnumIdentifiers)(INT nID, CStringArray &szIdentifiers, CUIntArray &nIdentifierTypes, CUIntArray &nIdentifierAttributes, CPtrArray &pIdentifiers);

#ifndef UNICODE
	szProcedure[0] = STRING(IDS_EXPORTINTERFACE_INITIALIZETCPROCEDURE);
	szProcedure[1] = STRING(IDS_EXPORTINTERFACE_INITIALIZETCPROCEDUREPARAMETERS);
	szProcedure[2] = STRING(IDS_EXPORTINTERFACE_ENUMTCPROCEDUREIDENTIFIERS);
	szProcedure[3] = STRING(IDS_EXPORTINTERFACE_ENUMTCPROCEDUREFUNCTIONEXECUTIONVERIFICATIONTIMEWINDOWS);
#else
	WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_INITIALIZETCPROCEDURE), -1, (LPSTR)szProcedure[0].GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_INITIALIZETCPROCEDURE))), lstrlen(STRING(IDS_EXPORTINTERFACE_INITIALIZETCPROCEDURE)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
	WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_INITIALIZETCPROCEDUREPARAMETERS), -1, (LPSTR)szProcedure[1].GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_INITIALIZETCPROCEDUREPARAMETERS))), lstrlen(STRING(IDS_EXPORTINTERFACE_INITIALIZETCPROCEDUREPARAMETERS)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
	WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_ENUMTCPROCEDUREIDENTIFIERS), -1, (LPSTR)szProcedure[2].GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_ENUMTCPROCEDUREIDENTIFIERS))), lstrlen(STRING(IDS_EXPORTINTERFACE_ENUMTCPROCEDUREIDENTIFIERS)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
	WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_ENUMTCPROCEDUREFUNCTIONEXECUTIONVERIFICATIONTIMEWINDOWS), -1, (LPSTR)szProcedure[3].GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_ENUMTCPROCEDUREFUNCTIONEXECUTIONVERIFICATIONTIMEWINDOWS))), lstrlen(STRING(IDS_EXPORTINTERFACE_ENUMTCPROCEDUREFUNCTIONEXECUTIONVERIFICATIONTIMEWINDOWS)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
	szProcedure[0].ReleaseBuffer();
	szProcedure[1].ReleaseBuffer();
	szProcedure[2].ReleaseBuffer();
	szProcedure[3].ReleaseBuffer();
#endif
	if ((pInitialize = (BOOL(__cdecl *)(CONST CDatabaseEngine *pDatabase, CTCProcessEngine *pTCProcessEngine, CTCEnvironment *pTCEnvironment, LPCTSTR pszName, INT nProcedureID, INT nID, UINT nExecutionMode, BOOL bSynchronized, CONST CPtrArray &hEvents, CStringArray &szErrorParameters)) GetProcAddress(hModule, (LPCSTR)(LPCTSTR)szProcedure[0])) && (*pInitialize)(GetDatabase(), m_pTCProcessEngine, m_pTCEnvironment, pszName, -1, nID, pItem->GetExecutionMode(), FALSE, hEvents, szErrorParameters))
	{
		if ((pEnumIdentifiers = (INT(__cdecl *)(INT nID, CStringArray &szIdentifiers, CUIntArray &nIdentifierTypes, CUIntArray &nIdentifierAttributes, CPtrArray &pIdentifiers)) GetProcAddress(hModule, (LPCSTR)(LPCTSTR)szProcedure[2])) && (*pEnumIdentifiers)(nID, szIdentifiers, nIdentifierTypes, nIdentifierAttributes, pIdentifiers) >= 0)
		{
			for (nIdentifier = 0, nIdentifiers = (INT)szIdentifiers.GetSize(); nIdentifier < nIdentifiers; nIdentifier++)
			{
				if (nIdentifierTypes.GetAt(nIdentifier) == TCPROCEDUREPROCESS_IDENTIFIERTYPE_TMPARAMETER)
				{
					if ((pTMParameter = new CTMParameter) != (CTMParameter *)NULL)
					{
						if ((pParameter = GetDatabase()->GetTMParameters()->GetAt(GetDatabase()->GetTMParameters()->Find(szIdentifiers.GetAt(nIdentifier)))))
						{
							pTMParameter->SetTag(pParameter->GetTag());
							pTMParameter->SetAttributes(pParameter->GetAttributes());
							if (pTMParameters.Add(pTMParameter) >= 0) continue;
						}
						delete pTMParameter;
						break;
					}
				}
			}
			if ((pInitializeParameters = (nIdentifier == nIdentifiers  &&  InitializeTMData(pTMParameters)) ? (BOOL(__cdecl *)(INT nID, CONST CTMParameters &pTMParameters, double fTotalTMBandwidth, double fAvailableTMBandwidth, double fMaxDiagnosticTMBandwidth, double fAvailableDiagnosticTMBandwidth, CONST CTimeTag &tTMBandwidth)) GetProcAddress(hModule, (LPCSTR)(LPCTSTR)szProcedure[1]) : (BOOL(__cdecl *)(INT nID, CONST CTMParameters &pTMParameters, double fTotalTMBandwidth, double fAvailableTMBandwidth, double fMaxDiagnosticTMBandwidth, double fAvailableDiagnosticTMBandwidth, CONST CTimeTag &tTMBandwidth)) NULL) && (*pInitializeParameters)(nID, pTMParameters, GetTMService()->GetTotalTMBandwidth(), GetTMService()->GetAvailableTMBandwidth(), GetTMService()->GetMaxDiagnosticTMBandwidth(), GetTMService()->GetAvailableDiagnosticTMBandwidth(), GetTMService()->GetLastTMBandwidthMeasurementTime()))
			{
				if ((pEnumThreadTCFunctionExecutionVerificationTimeWindows = (BOOL(__cdecl *)(INT nID, LPCTSTR pszThread, LPCTSTR pszStep, INT nEntry, CUIntArray &nStageIDs, CUIntArray &nStageTimeWindowOffsets, CUIntArray &nStageTimeWindowSizes, CUIntArray &nStageTimeWindowUncertainties)) GetProcAddress(hModule, (LPCSTR)(LPCTSTR)szProcedure[3])))
				{
					for (nStage = 0, nStages = ((*pEnumThreadTCFunctionExecutionVerificationTimeWindows)(nID, pItem->GetVerificationThread(), pItem->GetVerificationStep(), (pItem->GetMembershipID() != (UINT)-1) ? (pItem->GetMembershipID() + 1) : -1, nStageIDs, nStageTimeWindow[0], nStageTimeWindow[1], nStageTimeWindow[2])) ? (INT)nStageIDs.GetSize() : 0; nStage < nStages; nStage++)
					{
						pItem->SetVerificationTimeWindow(nStageIDs.GetAt(nStage), nStageTimeWindow[0].GetAt(nStage), nStageTimeWindow[1].GetAt(nStage), nStageTimeWindow[2].GetAt(nStage));
						continue;
					}
					pItem->SetVerificationProcessID(nID);
					pItem->SetVerificationModule(hModule);
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

BOOL CTCProcessThread::Update(HINSTANCE hModule, INT nID, CONST CTMEnvironment *pTMEnvironment)
{
	CString  szProcedure;
	BOOL(__cdecl *pUpdate)(INT nID, CONST CTMEnvironment *pTMEnvironment);

#ifndef UNICODE
	szProcedure = STRING(IDS_EXPORTINTERFACE_UPDATETCPROCEDURE);
#else
	WideCharToMultiByte(CP_ACP, 0, STRING(IDS_EXPORTINTERFACE_UPDATETCPROCEDURE), -1, (LPSTR)szProcedure.GetBufferSetLength(lstrlen(STRING(IDS_EXPORTINTERFACE_UPDATETCPROCEDURE))), lstrlen(STRING(IDS_EXPORTINTERFACE_UPDATETCPROCEDURE)) + 1, (LPCSTR)NULL, (LPBOOL)NULL);
	szProcedure.ReleaseBuffer();
#endif
	if ((pUpdate = (BOOL(__cdecl *)(INT nID, CONST CTMEnvironment *pTMEnvironment)) GetProcAddress(hModule, (LPCSTR)(LPCTSTR)szProcedure))) return (*pUpdate)(nID, pTMEnvironment);
	return FALSE;
}

BOOL CTCProcessThread::SetDevice(CONST CTCUplinkDevice *pDevice)
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return m_cTCDevice.Copy(pDevice);
}

BOOL CTCProcessThread::GetDevice(CTCUplinkDevice *pDevice) CONST
{
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	return pDevice->Copy(&m_cTCDevice);
}

BOOL CTCProcessThread::StartDevice(CTCUplinkDevice *pDevice)
{
	CString  szMessage;
	CTCUplinkDevice  cDevice;

	for (StopDevice(); SetDevice(pDevice) && StartDevice(); )
	{
		if (pDevice->GetBackupOptions() & TELECOMMANDUPLINKDEVICE_BACKUP_RETRIES)
		{
			m_cTCDevice.SetBackupRetryCount(0);
			pDevice->SetBackupRetryCount(0);
		}
		for (GetActiveTCUplinkDevice(&cDevice); (pDevice->GetDeviceBrand() != cDevice.GetDeviceBrand() || pDevice->GetDeviceName() != cDevice.GetDeviceName()) && (cDevice.GetBackupOptions() & TELECOMMANDUPLINKDEVICE_BACKUP_AUDITFAILURES); )
		{
			szMessage.Format(STRING(IDS_TELECOMMANDUPLINKDEVICE_BACKUPMESSAGE_FAILURE), (LPCTSTR)cDevice.GetDeviceName(), (LPCTSTR)pDevice->GetDeviceName());
			ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
			break;
		}
		return TRUE;
	}
	return FALSE;
}
BOOL CTCProcessThread::StartDevice()
{
	UINT  nRetry;
	UINT  nRetries;
	CString  szMessage;

	for (StopDevice(); m_cTCDevice.Open(); )
	{
		if (m_cTCDevice.IsLocal() || !IsTestModeEnabled())
		{
			if (m_cTCDevice.IsStandBy())
			{
				if (m_cTCDevice.Initialize((m_cTCDevice.GetCapabilities() & ~(IODEVICE_TYPE_SERVER | IODEVICE_SERVICE_TM | ((m_pTCProcessEngine->DetectTCServiceLevel() == TCSERVICELEVEL_TRANSFERFRAMES) ? (IODEVICE_DATASERVICE_RAW | IODEVICE_DATASERVICE_SOURCEPACKETS) : (IODEVICE_DATASERVICE_RAW | IODEVICE_DATASERVICE_TRANSFERFRAMES)))) | IODEVICE_TYPE_CLIENT | IODEVICE_SERVICE_TC | ((m_pTCProcessEngine->DetectTCServiceLevel() == TCSERVICELEVEL_TRANSFERFRAMES) ? IODEVICE_DATASERVICE_TRANSFERFRAMES : IODEVICE_DATASERVICE_SOURCEPACKETS), 0, 0) && m_cTCDevice.Start())
				{
					for (m_cTCDevice.SetStatusIndication((m_cTCDevice.GetStatusIndication() & ~(IODEVICE_STATUS_NOTCONNECTED | IODEVICE_STATUS_OFFLINE)) | (IODEVICE_STATUS_CONNECTED | IODEVICE_STATUS_ONLINE)); m_cTCDevice.GetStatus() == STRING(IDS_TELECOMMANDUPLINKDEVICE_STATUS_NOTREADY) || m_cTCDevice.GetStatus() == STRING(IDS_TELECOMMANDUPLINKDEVICE_STATUS_OFFLINE) || m_cTCDevice.GetStatus() == STRING(IDS_TELECOMMANDUPLINKDEVICE_STATUS_DISABLED); )
					{
						m_cTCDevice.SetStatusIndication((m_cTCDevice.GetStatusIndication() | IODEVICE_STATUS_WARNING) & ~(IODEVICE_STATUS_GOOD | IODEVICE_STATUS_ERROR));
						m_cTCDevice.SetStatus(STRING(IDS_TELECOMMANDUPLINKDEVICE_STATUS_READY));
						break;
					}
					return TRUE;
				}
				if ((m_cTCDevice.GetStatusIndication() & IODEVICE_STATUS_ONLINE) != IODEVICE_STATUS_ONLINE)
				{
					if ((m_cTCDevice.GetScheduleOptions() & TELECOMMANDUPLINKDEVICE_SCHEDULE_ALWAYS) != TELECOMMANDUPLINKDEVICE_SCHEDULE_ALWAYS && (m_cTCDevice.GetScheduleOptions() & TELECOMMANDUPLINKDEVICE_SCHEDULE_DISABLED) != TELECOMMANDUPLINKDEVICE_SCHEDULE_DISABLED && (m_cTCDevice.GetScheduleOptions() & TELECOMMANDUPLINKDEVICE_SCHEDULE_AUDIT))
					{
						szMessage.Format(STRING(IDS_TELECOMMANDUPLINKDEVICE_SCHEDULEMESSAGE_ACTIVE), (LPCTSTR)m_cTCDevice.GetDeviceName());
						ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
					}
				}
				if (m_cTCDevice.GetBackupOptions() & TELECOMMANDUPLINKDEVICE_BACKUP_RETRIES)
				{
					for (m_cTCDevice.GetBackupRetryCount(nRetry), m_cTCDevice.GetBackupRetries(nRetries); nRetry <= nRetries; )
					{
						for (m_cTCDevice.SetBackupRetryCount(nRetry + 1); (m_cTCDevice.GetBackupOptions() & TELECOMMANDUPLINKDEVICE_BACKUP_AUDITFAILURES) && nRetry == nRetries; )
						{
							szMessage.Format(STRING(IDS_TELECOMMANDUPLINKDEVICE_BACKUPMESSAGE_RETRIES), (LPCTSTR)m_cTCDevice.GetDeviceName(), nRetries);
							ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szMessage);
							break;
						}
						break;
					}
				}
				m_cTCDevice.SetStatusIndication((m_cTCDevice.GetStatusIndication() & ~(IODEVICE_STATUS_CONNECTED | IODEVICE_STATUS_OFFLINE)) | (IODEVICE_STATUS_NOTCONNECTED | IODEVICE_STATUS_ONLINE));
				m_cTCDevice.SetStatus(STRING(IDS_TELECOMMANDUPLINKDEVICE_STATUS_NOTREADY));
			}
			else
			{
				if ((m_cTCDevice.GetStatusIndication() & IODEVICE_STATUS_ONLINE) || (m_cTCDevice.GetStatusIndication() & (IODEVICE_STATUS_ONLINE | IODEVICE_STATUS_OFFLINE)) == 0)
				{
					if ((m_cTCDevice.GetScheduleOptions() & TELECOMMANDUPLINKDEVICE_SCHEDULE_ALWAYS) != TELECOMMANDUPLINKDEVICE_SCHEDULE_ALWAYS && (m_cTCDevice.GetScheduleOptions() & TELECOMMANDUPLINKDEVICE_SCHEDULE_DISABLED) != TELECOMMANDUPLINKDEVICE_SCHEDULE_DISABLED && (m_cTCDevice.GetScheduleOptions() & TELECOMMANDUPLINKDEVICE_SCHEDULE_AUDIT))
					{
						szMessage.Format(STRING(IDS_TELECOMMANDUPLINKDEVICE_SCHEDULEMESSAGE_INACTIVE), (LPCTSTR)m_cTCDevice.GetDeviceName());
						ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
					}
				}
				m_cTCDevice.SetStatusIndication((m_cTCDevice.GetStatusIndication() & ~(IODEVICE_STATUS_CONNECTED | IODEVICE_STATUS_ONLINE)) | (IODEVICE_STATUS_NOTCONNECTED | IODEVICE_STATUS_OFFLINE));
				m_cTCDevice.SetStatus((m_cTCDevice.GetScheduleOptions() & TELECOMMANDUPLINKDEVICE_SCHEDULE_DISABLED) ? STRING(IDS_TELECOMMANDUPLINKDEVICE_STATUS_DISABLED) : STRING(IDS_TELECOMMANDUPLINKDEVICE_STATUS_OFFLINE));
			}
		}
		m_cTCDevice.Close();
		break;
	}
	return FALSE;
}

VOID CTCProcessThread::StopDevice()
{
	CString  szMessage;

	if (!m_cTCDevice.IsStandBy())
	{
		if (m_cTCDevice.GetStatusIndication() & IODEVICE_STATUS_ONLINE)
		{
			if ((m_cTCDevice.GetScheduleOptions() & TELECOMMANDUPLINKDEVICE_SCHEDULE_ALWAYS) != TELECOMMANDUPLINKDEVICE_SCHEDULE_ALWAYS && (m_cTCDevice.GetScheduleOptions() & TELECOMMANDUPLINKDEVICE_SCHEDULE_DISABLED) != TELECOMMANDUPLINKDEVICE_SCHEDULE_DISABLED && (m_cTCDevice.GetScheduleOptions() & TELECOMMANDUPLINKDEVICE_SCHEDULE_AUDIT))
			{
				szMessage.Format(STRING(IDS_TELECOMMANDUPLINKDEVICE_SCHEDULEMESSAGE_INACTIVE), (LPCTSTR)m_cTCDevice.GetDeviceName());
				ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szMessage, FALSE);
			}
		}
		m_cTCDevice.SetStatusIndication((m_cTCDevice.GetStatusIndication() & ~(IODEVICE_STATUS_CONNECTED | IODEVICE_STATUS_ONLINE)) | (IODEVICE_STATUS_NOTCONNECTED | IODEVICE_STATUS_OFFLINE));
		m_cTCDevice.SetStatus((m_cTCDevice.GetScheduleOptions() & TELECOMMANDUPLINKDEVICE_SCHEDULE_ALWAYS) ? STRING(IDS_TELECOMMANDUPLINKDEVICE_STATUS_NOTREADY) : ((m_cTCDevice.GetScheduleOptions() & TELECOMMANDUPLINKDEVICE_SCHEDULE_DISABLED) ? STRING(IDS_TELECOMMANDUPLINKDEVICE_STATUS_DISABLED) : STRING(IDS_TELECOMMANDUPLINKDEVICE_STATUS_OFFLINE)));
	}
	m_cTCDevice.Close();
}

BOOL CTCProcessThread::StartDisplay(INT nType, BOOL bRestart)
{
	switch (nType)
	{
	case DISPLAY_TYPE_TCMANUALSTACK:
	{ return(((m_pTCManualStackWnd = (CTCManualStackWnd *)GetDisplayArea()->FindDisplay(nType))) ? m_pTCManualStackWnd->StartTelecommanding(m_pTCProcessEngine, m_pTCEnvironment) : FALSE);
	break;
	}
	case DISPLAY_TYPE_TCAUTOMATICSTACK:
	{ return(((m_pTCAutomaticStackWnd = (CTCAutomaticStackWnd *)GetDisplayArea()->FindDisplay(nType))) ? m_pTCAutomaticStackWnd->StartTelecommanding(m_pTCProcessEngine, m_pTCEnvironment) : FALSE);
	break;
	}
	case DISPLAY_TYPE_TCPROCEDURESMONITOR:
	{ return(((m_pTCProceduresMonitorWnd = (CTCProceduresMonitorWnd *)GetDisplayArea()->FindDisplay(nType))) ? m_pTCProceduresMonitorWnd->StartMonitoring(m_pTCProcessEngine, m_pTCEnvironment, bRestart) : FALSE);
	break;
	}
	case DISPLAY_TYPE_TCDIAGNOSTICSOVERSAMPLINGDUMP:
	{ return(((m_pTCDiagnosticsOversamplingDumpWnd = (CTCDiagnosticsOversamplingDumpWnd *)GetDisplayArea()->FindDisplay(nType))) ? m_pTCDiagnosticsOversamplingDumpWnd->StartMonitoring() : FALSE);
	break;
	}
	case DISPLAY_TYPE_TCONBOARDBUFFERQUEUES:
	{ return(((m_pTCOnBoardBufferQueuesWnd = (CTCOnBoardBufferQueuesWnd *)GetDisplayArea()->FindDisplay(nType))) ? m_pTCOnBoardBufferQueuesWnd->StartMonitoring() : FALSE);
	break;
	}
	case DISPLAY_TYPE_TCONBOARDMEMORYIMAGES:
	{ return(((m_pTCOnBoardMemoryImagesWnd = (CTCOnBoardMemoryImagesWnd *)GetDisplayArea()->FindDisplay(nType))) ? m_pTCOnBoardMemoryImagesWnd->StartMonitoring() : FALSE);
	break;
	}
	case DISPLAY_TYPE_TCHISTORY:
	{ return(((m_pTCHistoryWnd = (CTCHistoryWnd *)GetDisplayArea()->FindDisplay(nType))) ? m_pTCHistoryWnd->StartMonitoring() : FALSE);
	break;
	}
	default: break;
	}
	return FALSE;
}

BOOL CTCProcessThread::StopDisplay(INT nType)
{
	switch (nType)
	{
	case DISPLAY_TYPE_TCMANUALSTACK:
	{ if (m_pTCManualStackWnd != (CTCManualStackWnd *)NULL  &&  m_pTCManualStackWnd->StopTelecommanding())
	{
		m_pTCManualStackWnd = (CTCManualStackWnd *)NULL;
		return TRUE;
	}
	return((!m_pTCManualStackWnd) ? TRUE : FALSE);
	}
	case DISPLAY_TYPE_TCAUTOMATICSTACK:
	{ if (m_pTCAutomaticStackWnd != (CTCAutomaticStackWnd *)NULL  &&  m_pTCAutomaticStackWnd->StopTelecommanding())
	{
		m_pTCAutomaticStackWnd = (CTCAutomaticStackWnd *)NULL;
		return TRUE;
	}
	return((!m_pTCAutomaticStackWnd) ? TRUE : FALSE);
	}
	case DISPLAY_TYPE_TCPROCEDURESMONITOR:
	{ if (m_pTCProceduresMonitorWnd != (CTCProceduresMonitorWnd *)NULL  &&  m_pTCProceduresMonitorWnd->StopMonitoring())
	{
		m_pTCProceduresMonitorWnd = (CTCProceduresMonitorWnd *)NULL;
		return TRUE;
	}
	return((!m_pTCProceduresMonitorWnd) ? TRUE : FALSE);
	}
	case DISPLAY_TYPE_TCDIAGNOSTICSOVERSAMPLINGDUMP:
	{ if (m_pTCDiagnosticsOversamplingDumpWnd != (CTCDiagnosticsOversamplingDumpWnd *)NULL  &&  m_pTCDiagnosticsOversamplingDumpWnd->StopMonitoring())
	{
		m_pTCDiagnosticsOversamplingDumpWnd = (CTCDiagnosticsOversamplingDumpWnd *)NULL;
		return TRUE;
	}
	return((!m_pTCDiagnosticsOversamplingDumpWnd) ? TRUE : FALSE);
	}
	case DISPLAY_TYPE_TCONBOARDBUFFERQUEUES:
	{ if (m_pTCOnBoardBufferQueuesWnd != (CTCOnBoardBufferQueuesWnd *)NULL  &&  m_pTCOnBoardBufferQueuesWnd->StopMonitoring())
	{
		m_pTCOnBoardBufferQueuesWnd = (CTCOnBoardBufferQueuesWnd *)NULL;
		return TRUE;
	}
	return((!m_pTCOnBoardBufferQueuesWnd) ? TRUE : FALSE);
	}
	case DISPLAY_TYPE_TCONBOARDMEMORYIMAGES:
	{ if (m_pTCOnBoardMemoryImagesWnd != (CTCOnBoardMemoryImagesWnd *)NULL  &&  m_pTCOnBoardMemoryImagesWnd->StopMonitoring())
	{
		m_pTCOnBoardMemoryImagesWnd = (CTCOnBoardMemoryImagesWnd *)NULL;
		return TRUE;
	}
	return((!m_pTCOnBoardMemoryImagesWnd) ? TRUE : FALSE);
	}
	case DISPLAY_TYPE_TCHISTORY:
	{ if (m_pTCHistoryWnd != (CTCHistoryWnd *)NULL  &&  m_pTCHistoryWnd->StopMonitoring())
	{
		m_pTCHistoryWnd = (CTCHistoryWnd *)NULL;
		return TRUE;
	}
	return((!m_pTCHistoryWnd) ? TRUE : FALSE);
	}
	default: break;
	}
	return FALSE;
}

BOOL CTCProcessThread::InitializeData()
{
	CByteArray  nData;
	CProfile  cProfile;

	return(((!cProfile.GetTelecommandServiceContentsInfo(nData) || SetContentsData(nData)) + (!cProfile.GetTelecommandServiceProcessInfo(nData) || SetProcessData(nData)) > TRUE) ? TRUE : FALSE);
}

BOOL CTCProcessThread::SetContentsData(CONST CByteArray &nData)
{
	INT  cbData;
	CTCItems  pItems;
	CByteArray  nItemsData;
	CByteArray  nQueuesData;
	CByteArray  nInterlocksData;
	CByteArray  nParametersData;
	CTCOnBoardBufferQueues  pQueues;
	CTCInterlocks  pInterlocks;
	CONTENTSDATA  sData;

	for (CopyMemory(&sData, nData.GetData(), (nData.GetSize() >= sizeof(CONTENTSDATA)) ? sizeof(CONTENTSDATA) : 0); nData.GetSize() >= sizeof(CONTENTSDATA) && sData.cbSize == nData.GetSize() && sData.cbSize == sizeof(CONTENTSDATA) + sData.cbItems + sData.cbInterlocks + sData.cbQueues + sData.cbParameters && sData.cbItems >= 0 && sData.cbInterlocks >= 0 && sData.cbQueues >= 0 && sData.cbParameters >= 0; )
	{
		for (nItemsData.SetSize(sData.cbItems), nInterlocksData.SetSize(sData.cbInterlocks), nQueuesData.SetSize(sData.cbQueues), nParametersData.SetSize(sData.cbParameters), CopyMemory(nItemsData.GetData(), nData.GetData() + (cbData = sizeof(CONTENTSDATA)), sData.cbItems), CopyMemory(nInterlocksData.GetData(), nData.GetData() + (cbData = cbData + sData.cbItems), sData.cbInterlocks), CopyMemory(nQueuesData.GetData(), nData.GetData() + (cbData = cbData + sData.cbInterlocks), sData.cbQueues), CopyMemory(nParametersData.GetData(), nData.GetData() + (cbData = cbData + sData.cbQueues), sData.cbParameters), m_pTCEnvironment->GetTCParameters()->Unmap(nParametersData); pItems.Unmap(nItemsData, TRUE) && pInterlocks.Unmap(nInterlocksData) && pQueues.Unmap(nQueuesData); ) return SetCommandHandlerContents(pItems, pInterlocks, pQueues);
		break;
	}
	return FALSE;
}

BOOL CTCProcessThread::GetContentsData(CByteArray &nData) CONST
{
	INT  cbData;
	CTCItems  pItems;
	CByteArray  nItemsData;
	CByteArray  nQueuesData;
	CByteArray  nInterlocksData;
	CByteArray  nParametersData;
	CTCOnBoardBufferQueues  pQueues;
	CTCInterlocks  pInterlocks;
	CONTENTSDATA  sData;

	if (!IsCommandHandler() || GetCommandHandlerContents(pItems, pInterlocks, pQueues))
	{
		for (sData.cbItems = (pItems.Map(nItemsData, TRUE)) ? (INT)nItemsData.GetSize() : -1, sData.cbInterlocks = (pInterlocks.Map(nInterlocksData)) ? (INT)nInterlocksData.GetSize() : -1, sData.cbQueues = (pQueues.Map(nQueuesData)) ? (INT)nQueuesData.GetSize() : -1, sData.cbParameters = (m_pTCEnvironment->GetTCParameters()->Map(nParametersData)) ? (INT)nParametersData.GetSize() : -1, nData.SetSize((sData.cbSize = sizeof(CONTENTSDATA) + max(sData.cbItems, 0) + max(sData.cbInterlocks, 0) + max(sData.cbQueues, 0) + max(sData.cbParameters, 0))); nData.GetSize() == sData.cbSize && sData.cbItems >= 0 && sData.cbInterlocks >= 0 && sData.cbQueues >= 0 && sData.cbParameters >= 0; )
		{
			CopyMemory(nData.GetData(), &sData, sizeof(CONTENTSDATA));
			CopyMemory(nData.GetData() + (cbData = sizeof(CONTENTSDATA)), nItemsData.GetData(), sData.cbItems);
			CopyMemory(nData.GetData() + (cbData = cbData + sData.cbItems), nInterlocksData.GetData(), sData.cbInterlocks);
			CopyMemory(nData.GetData() + (cbData = cbData + sData.cbInterlocks), nQueuesData.GetData(), sData.cbQueues);
			CopyMemory(nData.GetData() + (cbData = cbData + sData.cbQueues), nParametersData.GetData(), sData.cbParameters);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CTCProcessThread::SetProcessData(CONST CByteArray &nData)
{
	return m_pTCEnvironment->GetTCProcessInfo()->SetData(nData);
}

BOOL CTCProcessThread::GetProcessData(CByteArray &nData) CONST
{
	return(m_pTCEnvironment->GetTCProcessInfo()->GetData(nData) > 0);
}

BOOL CTCProcessThread::UpdateProcessData(CONST BYTE *pData)
{
	CByteArray  nData;
	CProfile  cProfile;

	for (nData.SetSize(GlobalSize((HGLOBAL)pData)), CopyMemory(nData.GetData(), pData, nData.GetSize()); SetProcessData(nData); )
	{
		cProfile.SetTelecommandServiceProcessInfo(nData);
		return TRUE;
	}
	return FALSE;
}

VOID CTCProcessThread::UpdateQueues()
{
	INT  nItem;
	INT  nItems;
	INT  nQueue;
	INT  nQueues;
	CTCItem  *pItem;
	CTimeTag  tTime[3];
	CPtrArray  pQueues;
	CTCPacket  cTCPacket;
	CTCOnBoardBufferQueue  *pQueue;

	for (nQueue = 0, nQueues = (INT)m_pTCOnBoardBufferQueues.GetSize(), m_nCommandUpdateTimerID *= (m_nCommandUpdateTimerID > 0) ? !KillTimer((HWND)NULL, m_nCommandUpdateTimerID) : 0, tTime[0] = 0; nQueue < nQueues; nQueue++)
	{
		if ((pQueue = m_pTCOnBoardBufferQueues.GetAt(nQueue)) && pQueue->GetTimeout() > 0)
		{
			for (nItem = 0, nItems = (INT)pQueue->GetSize(); nItem < nItems; nItem++)
			{
				if ((pItem = pQueue->GetAt(nItem)) && (pItem->GetFlags() & TCITEM_EXECUTIONFLAG_1STSTEP))
				{
					if ((tTime[1] = pItem->GetTransmissionTime().GetTime() + 1000000 * pQueue->GetTimeout().GetTotalSeconds()) > tTime[2] && pItem->GetTransmissionTime() > 0)
					{
						tTime[0] = (tTime[0] > 0) ? min(tTime[0], tTime[1]) : tTime[1];
						continue;
					}
					pQueue->SetCount((pItem->GetQueuedSize() <= pQueue->GetCount()) ? (pQueue->GetCount() - pItem->GetQueuedSize()) : 0);
					pQueue->SetUpdateTime(tTime[2]);
					pQueue->RemoveAt(nItem);
					pQueues.Add(pQueue);
					delete pItem;
					nItems--;
					nItem--;
				}
			}
		}
	}
	for (nQueue = 0; nQueue < nQueues; nQueue++)
	{
		if ((pQueue = m_pTCOnBoardBufferQueues.GetAt(nQueue)) && pQueue->GetTimeout() == 0)
		{
			for (nItem = 0, nItems = (INT)pQueue->GetSize(); nItem < nItems; nItem = nItem + 1)
			{
				if ((pItem = pQueue->GetAt(nItem)) && (pItem->GetFlags() & TCITEM_EXECUTIONFLAG_IMMEDIATE))
				{
					if (pItem->GetExecutionTime(tTime[1]) && tTime[1] > tTime[2])
					{
						tTime[0] = (tTime[0] > 0) ? min(tTime[0], tTime[1]) : tTime[1];
						continue;
					}
					pQueue->SetCount((pItem->GetQueuedSize() <= pQueue->GetCount()) ? (pQueue->GetCount() - pItem->GetQueuedSize()) : 0);
					pQueue->SetUpdateTime(tTime[2]);
					pQueue->RemoveAt(nItem);
					pQueues.Add(pQueue);
					delete pItem;
					nItems--;
					nItem--;
				}
			}
		}
	}
	for (; tTime[0] > tTime[2]; )
	{
		m_nCommandUpdateTimerID = SetTimer((HWND)NULL, TCPROCESSTHREAD_UPDATECOMMANDS_TIMERID, (UINT)min((tTime[0].GetTime() - tTime[2].GetTime()) / 1000, 1000 * SECONDSPERDAY), NULL);
		break;
	}
	UpdateQueues(pQueues);
}
VOID CTCProcessThread::UpdateQueues(CONST CPtrArray &pInfo)
{
	INT  nQueue;
	INT  nQueues;
	CTCOnBoardBufferQueue  *pQueue[2];
	CTCOnBoardBufferQueues  pQueues;

	for (nQueue = 0, nQueues = (INT)pInfo.GetSize(); nQueue < nQueues; nQueue++)
	{
		if ((pQueue[1] = ((pQueue[0] = (CTCOnBoardBufferQueue *)pInfo.GetAt(nQueue))) ? new CTCOnBoardBufferQueue : (CTCOnBoardBufferQueue *)NULL))
		{
			if (pQueue[1]->Copy(pQueue[0]) && pQueues.Add(pQueue[1]) >= 0) continue;
			delete pQueue[1];
		}
	}
	if (pQueues.GetSize() > 0)
	{
		UpdateTCOnBoardBufferQueues(pQueues, FALSE);
		Update();
	}
}

VOID CTCProcessThread::UpdateArchives()
{
	CTCItems  pItems;

	UpdateArchives(pItems);
}
VOID CTCProcessThread::UpdateArchives(CONST CTCItems &pItems)
{
	INT  nItem;
	INT  nItems;
	INT  nFile;
	INT  nFiles;
	UINT  nResult;
	BOOL  bBuffering;
	CTCItem  *pItem;
	CString  szError;
	CUIntArray  nErrors;
	CHistoryStoreFile  *pFile;
	CHistoryStoreFiles  pFiles;

	for (nItem = 0, nItems = (INT)pItems.GetSize(), m_nArchiveBufferTimerID *= (m_nArchiveBufferTimerID > 0) ? !KillTimer((HWND)NULL, m_nArchiveBufferTimerID) : 0, bBuffering = FALSE; nItem < nItems || (!nItem && m_bArchiveBufferFlash); nItem++)
	{
		if (((pItem = pItems.GetAt(nItem)) && Initialize(pItem, m_pTCEnvironment) && GetTCService()->UpdateTCHistoryFiles(m_pTCEnvironment, pFiles, nErrors) >= 0) || (m_bArchiveBufferFlash  &&  GetTCService()->UpdateTCHistoryFiles(pFiles, nErrors) >= 0))
		{
			for (nFile = 0, nFiles = (INT)pFiles.GetSize(); nFile < nFiles; nFile++)
			{
				if ((pFile = pFiles.GetAt(nFile)) != (CHistoryStoreFile *)NULL)
				{
					if (HIWORD((nResult = nErrors.GetAt(nFile))) & HISTORYSTORE_BACKUP)
					{
						if (!DoBackup(pFile, FALSE) && (pFile->GetOptions() & HISTORYSTORE_OPTION_BACKUPAUDITFAILURES))
						{
							szError.Format(STRING(IDS_TELECOMMANDARCHIVES_BACKUP_FAILURE), (LPCTSTR)pFile->GetFileName());
							ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szError);
						}
						continue;
					}
					if (LOWORD(nResult) & HISTORYSTORE_FILEOPEN_FAILURE)
					{
						szError.Format(STRING(IDS_TELECOMMANDARCHIVES_FILEOPEN_FAILURE), (LPCTSTR)pFile->GetFileName());
						ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szError);
					}
					if (LOWORD(nResult) & HISTORYSTORE_FILEUPDATE_FAILURE)
					{
						szError.Format(STRING(IDS_TELECOMMANDARCHIVES_FILEUPDATE_FAILURE), (LPCTSTR)pFile->GetFileName());
						ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szError);
					}
					if (LOWORD(nResult) & HISTORYSTORE_FILECLOSE_FAILURE)
					{
						szError.Format(STRING(IDS_TELECOMMANDARCHIVES_FILECLOSE_FAILURE), (LPCTSTR)pFile->GetFileName());
						ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szError);
					}
					if (LOWORD(nResult) & HISTORYSTORE_SECONDARY_FAILURE)
					{
						szError.Format(STRING(IDS_TELECOMMANDARCHIVES_SECONDARY_FAILURE), (LPCTSTR)pFile->GetFileName());
						ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING, szError);
					}
					if (HIWORD(nResult) & HISTORYSTORE_SECONDARY_USE)
					{
						szError.Format(STRING(IDS_TELECOMMANDARCHIVES_SECONDARY_USE), (LPCTSTR)pFile->GetFileName());
						ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szError, FALSE);
					}
					if (HIWORD(nResult) & HISTORYSTORE_DATA_LOST)
					{
						szError.Format(STRING(IDS_TELECOMMANDARCHIVES_DATA_LOST), (LPCTSTR)pFile->GetFileName());
						ReportEvent(EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL, szError, FALSE);
					}
					bBuffering = (HIWORD(nResult) & HISTORYSTORE_DATA_BUFFERED) ? TRUE : bBuffering;
				}
			}
			for (; pFiles.GetSize() > 0; )
			{
				if (!m_nArchiveBufferTimerID  &&  bBuffering)
				{
					m_nArchiveBufferTimerID = SetTimer((HWND)NULL, TCPROCESSTHREAD_UPDATEARCHIVES_TIMERID, TCPROCESSTHREAD_UPDATEARCHIVES_TIMEOUT, NULL);
					break;
				}
				if (m_nArchiveBufferTimerID > 0 && !bBuffering)
				{
					KillTimer((HWND)NULL, m_nArchiveBufferTimerID);
					m_nArchiveBufferTimerID = 0;
				}
				break;
			}
		}
	}
}

BOOL CTCProcessThread::UpdateCommandLinkControlWord(DWORD dwCLCW)
{
	CCLCWToolWnd  *pCLCWToolWnd;
	CMainWnd  *pMainWnd;

	if ((pCLCWToolWnd = ((pMainWnd = ::GetMainWnd())) ? pMainWnd->GetCLCWToolWnd() : (CCLCWToolWnd *)NULL))
	{
		pCLCWToolWnd->SetCLCW(dwCLCW);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCProcessThread::DoBackup(CONST CHistoryStoreFile *pFile, BOOL bDelayed)
{
	CTCArchivesBackupThread  *pBackupThread;

	if ((pBackupThread = new CTCArchivesBackupThread))
	{
		if (pBackupThread->Start(pFile, bDelayed, m_cArchiveBackupFiles, m_hObject)) return TRUE;
		delete pBackupThread;
	}
	return FALSE;
}

BOOL CTCProcessThread::Map(CByteArray &nInfo) CONST
{
	INT  cbData;
	INT  nClient;
	INT  nClients;
	BOOL  bCommandHandler[3];
	UINT  nCommandHandlerPort;
	UINT  nCommandHandlerOptions;
	UINT  nCommandHandlerBufferSize;
	UINT  nTelecommandingMode;
	UINT  nTelecommandingState;
	UINT  nTelecommandingFlags;
	BOOL  bTelecommandingInterlockMode;
	BOOL  bTelecommandingReleaseWaitMode;
	BOOL  bTelecommandingAutoRejectionMode;
	CString  szPreferredCommandHandler;
	CString  szBackupCommandHandler;
	CString  szDefaultHistoryFileName;
	CTimeSpan  tCommandHandlerTimeout;
	CTimeSpan  tMaximumTimeCheckPeriod;
	CTimeSpan  tMaximumExecutionTimePeriod;
	CTimeSpan  tVerificationUncertaintyTimeWindow;
	CTimeSpan  tDefaultReleaseTimeWindow;
	CByteArray  nHistoryFilesData[2];
	CByteArray  nCommandHandlerClients;
	CByteArray  nCommandHandlerStartTimes;
	CByteArray  nCommandHandlerStopTimes;
	CUIntArray  nCommandHandlerAccessCodes;
	CStringArray  szCommandHandlerClients;
	CTimeKeyArray  tCommandHandlerStartTimes;
	CTimeKeyArray  tCommandHandlerStopTimes;
	CONFIGURATIONDATA  sCommandHandlerData;
	CHistoryStoreFiles  pHistoryFiles[2];
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (nInfo.RemoveAll(); GetCommandHandlerConfiguration(szPreferredCommandHandler, szBackupCommandHandler, bCommandHandler[0], bCommandHandler[1], bCommandHandler[2], nCommandHandlerOptions, nCommandHandlerPort, nCommandHandlerBufferSize, tCommandHandlerTimeout, szCommandHandlerClients, nCommandHandlerAccessCodes, tCommandHandlerStartTimes, tCommandHandlerStopTimes) && GetCommandHandlerConfiguration(nTelecommandingMode, nTelecommandingState, nTelecommandingFlags, bTelecommandingInterlockMode, bTelecommandingReleaseWaitMode, bTelecommandingAutoRejectionMode, tVerificationUncertaintyTimeWindow, tMaximumExecutionTimePeriod, tMaximumTimeCheckPeriod, tDefaultReleaseTimeWindow, pHistoryFiles[0], pHistoryFiles[1], szDefaultHistoryFileName); )
	{
		for (nClient = 0, nClients = (INT)szCommandHandlerClients.GetSize(), sCommandHandlerData.cbCommandHandler[0] = (szPreferredCommandHandler.GetLength() + 1)*sizeof(TCHAR), sCommandHandlerData.cbCommandHandler[1] = (szBackupCommandHandler.GetLength() + 1)*sizeof(TCHAR), sCommandHandlerData.cbHistoryFiles[0] = (pHistoryFiles[0].Map(nHistoryFilesData[0])) ? (INT)nHistoryFilesData[0].GetSize() : -1, sCommandHandlerData.cbHistoryFiles[1] = (pHistoryFiles[1].Map(nHistoryFilesData[1])) ? (INT)nHistoryFilesData[1].GetSize() : -1, sCommandHandlerData.cbDefaultHistoryFileName = (szDefaultHistoryFileName.GetLength() + 1)*sizeof(TCHAR), sCommandHandlerData.cbCommandHandlerAccessCodes = (INT)(nCommandHandlerAccessCodes.GetSize()*sizeof(UINT)), sCommandHandlerData.cbCommandHandlerStartTimes = tCommandHandlerStartTimes.Map(nCommandHandlerStartTimes), sCommandHandlerData.cbCommandHandlerStopTimes = tCommandHandlerStopTimes.Map(nCommandHandlerStopTimes), sCommandHandlerData.cbCommandHandlerClients = 0; nClient < nClients; nClient++, sCommandHandlerData.cbCommandHandlerClients += cbData)
		{
			nCommandHandlerClients.SetSize(sCommandHandlerData.cbCommandHandlerClients + (cbData = (szCommandHandlerClients.GetAt(nClient).GetLength() + 1)*sizeof(TCHAR)));
			CopyMemory(nCommandHandlerClients.GetData() + sCommandHandlerData.cbCommandHandlerClients, (LPCTSTR)szCommandHandlerClients.GetAt(nClient), cbData);
		}
		for (nInfo.SetSize((sCommandHandlerData.cbSize = sizeof(CONFIGURATIONDATA) + sCommandHandlerData.cbCommandHandler[0] + sCommandHandlerData.cbCommandHandler[1] + max(sCommandHandlerData.cbHistoryFiles[0], 0) + max(sCommandHandlerData.cbHistoryFiles[1], 0) + sCommandHandlerData.cbDefaultHistoryFileName + sCommandHandlerData.cbCommandHandlerAccessCodes + sCommandHandlerData.cbCommandHandlerStartTimes + sCommandHandlerData.cbCommandHandlerStopTimes + sCommandHandlerData.cbCommandHandlerClients)), sCommandHandlerData.bCommandHandler[0] = bCommandHandler[0], sCommandHandlerData.bCommandHandler[1] = bCommandHandler[1], sCommandHandlerData.bCommandHandler[2] = bCommandHandler[2], sCommandHandlerData.nCommandHandlerOptions = nCommandHandlerOptions, sCommandHandlerData.nCommandHandlerPort = nCommandHandlerPort, sCommandHandlerData.nCommandHandlerBufferSize = nCommandHandlerBufferSize, sCommandHandlerData.tCommandHandlerTimeout = tCommandHandlerTimeout.GetTotalSeconds(), sCommandHandlerData.nTelecommandingMode = nTelecommandingMode, sCommandHandlerData.nTelecommandingState = nTelecommandingState, sCommandHandlerData.nTelecommandingFlags = nTelecommandingFlags, sCommandHandlerData.bTelecommandingInterlockMode = bTelecommandingInterlockMode, sCommandHandlerData.bTelecommandingReleaseWaitMode = bTelecommandingReleaseWaitMode, sCommandHandlerData.bTelecommandingAutoRejectionMode = bTelecommandingAutoRejectionMode, sCommandHandlerData.tVerificationUncertaintyTimeWindow = tVerificationUncertaintyTimeWindow.GetTotalSeconds(), sCommandHandlerData.tDefaultReleaseTimeWindow = tDefaultReleaseTimeWindow.GetTotalSeconds(), sCommandHandlerData.tMaximumExecutionTimePeriod = tMaximumExecutionTimePeriod.GetTotalSeconds(), sCommandHandlerData.tMaximumTimeCheckPeriod = tMaximumTimeCheckPeriod.GetTotalSeconds(); nInfo.GetSize() == sCommandHandlerData.cbSize && sCommandHandlerData.cbHistoryFiles[0] >= 0 && sCommandHandlerData.cbHistoryFiles[1] >= 0; )
		{
			CopyMemory(nInfo.GetData(), &sCommandHandlerData, sizeof(CONFIGURATIONDATA));
			CopyMemory(nInfo.GetData() + (cbData = sizeof(CONFIGURATIONDATA)), (LPCTSTR)szPreferredCommandHandler, sCommandHandlerData.cbCommandHandler[0]);
			CopyMemory(nInfo.GetData() + (cbData = cbData + sCommandHandlerData.cbCommandHandler[0]), (LPCTSTR)szBackupCommandHandler, sCommandHandlerData.cbCommandHandler[1]);
			CopyMemory(nInfo.GetData() + (cbData = cbData + sCommandHandlerData.cbCommandHandler[1]), nCommandHandlerClients.GetData(), sCommandHandlerData.cbCommandHandlerClients);
			CopyMemory(nInfo.GetData() + (cbData = cbData + sCommandHandlerData.cbCommandHandlerClients), nCommandHandlerAccessCodes.GetData(), sCommandHandlerData.cbCommandHandlerAccessCodes);
			CopyMemory(nInfo.GetData() + (cbData = cbData + sCommandHandlerData.cbCommandHandlerAccessCodes), nCommandHandlerStartTimes.GetData(), sCommandHandlerData.cbCommandHandlerStartTimes);
			CopyMemory(nInfo.GetData() + (cbData = cbData + sCommandHandlerData.cbCommandHandlerStartTimes), nCommandHandlerStopTimes.GetData(), sCommandHandlerData.cbCommandHandlerStopTimes);
			CopyMemory(nInfo.GetData() + (cbData = cbData + sCommandHandlerData.cbCommandHandlerStopTimes), nHistoryFilesData[0].GetData(), sCommandHandlerData.cbHistoryFiles[0]);
			CopyMemory(nInfo.GetData() + (cbData = cbData + sCommandHandlerData.cbHistoryFiles[0]), nHistoryFilesData[1].GetData(), sCommandHandlerData.cbHistoryFiles[1]);
			CopyMemory(nInfo.GetData() + (cbData = cbData + sCommandHandlerData.cbHistoryFiles[1]), (LPCTSTR)szDefaultHistoryFileName, sCommandHandlerData.cbDefaultHistoryFileName);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

BOOL CTCProcessThread::Unmap(CONST CByteArray &nInfo)
{
	INT  cbData;
	INT  cbClient;
	INT  cbClients;
	BOOL  bCommandHandler[3];
	UINT  nCommandHandlerPort;
	UINT  nCommandHandlerOptions;
	UINT  nCommandHandlerBufferSize;
	UINT  nTelecommandingMode;
	UINT  nTelecommandingState;
	UINT  nTelecommandingFlags;
	BOOL  bTelecommandingInterlockMode;
	BOOL  bTelecommandingReleaseWaitMode;
	BOOL  bTelecommandingAutoRejectionMode;
	CString  szPreferredCommandHandler;
	CString  szBackupCommandHandler;
	CString  szDefaultHistoryFileName;
	CTimeSpan  tCommandHandlerTimeout;
	CTimeSpan  tMaximumTimeCheckPeriod;
	CTimeSpan  tMaximumExecutionTimePeriod;
	CTimeSpan  tVerificationUncertaintyTimeWindow;
	CTimeSpan  tDefaultReleaseTimeWindow;
	CByteArray  nHistoryFilesData[2];
	CByteArray  nCommandHandlerClients;
	CByteArray  nCommandHandlerStartTimes;
	CByteArray  nCommandHandlerStopTimes;
	CUIntArray  nCommandHandlerAccessCodes;
	CStringArray  szCommandHandlerClients;
	CTimeKeyArray  tCommandHandlerStartTimes;
	CTimeKeyArray  tCommandHandlerStopTimes;
	CONFIGURATIONDATA  sCommandHandlerData;
	CHistoryStoreFiles  pHistoryFiles[2];
	CSingleLock  cLock(m_pCriticalSection, TRUE);

	for (CopyMemory(&sCommandHandlerData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(CONFIGURATIONDATA)) ? sizeof(CONFIGURATIONDATA) : 0); nInfo.GetSize() >= sizeof(CONFIGURATIONDATA) && sCommandHandlerData.cbSize == nInfo.GetSize() && sCommandHandlerData.cbSize == sizeof(CONFIGURATIONDATA) + sCommandHandlerData.cbCommandHandler[0] + sCommandHandlerData.cbCommandHandler[1] + sCommandHandlerData.cbCommandHandlerClients + sCommandHandlerData.cbCommandHandlerAccessCodes + sCommandHandlerData.cbCommandHandlerStartTimes + sCommandHandlerData.cbCommandHandlerStopTimes + sCommandHandlerData.cbHistoryFiles[0] + sCommandHandlerData.cbHistoryFiles[1] + sCommandHandlerData.cbDefaultHistoryFileName && sCommandHandlerData.cbCommandHandler[0] > 0 && sCommandHandlerData.cbCommandHandler[1] > 0 && sCommandHandlerData.cbCommandHandlerClients >= 0 && sCommandHandlerData.cbCommandHandlerAccessCodes >= 0 && sCommandHandlerData.cbCommandHandlerStartTimes >= 0 && sCommandHandlerData.cbCommandHandlerStopTimes >= 0 && sCommandHandlerData.cbHistoryFiles[0] >= 0 && sCommandHandlerData.cbHistoryFiles[1] >= 0 && sCommandHandlerData.cbDefaultHistoryFileName > 0; )
	{
		for (nCommandHandlerClients.SetSize(sCommandHandlerData.cbCommandHandlerClients), nCommandHandlerAccessCodes.SetSize(sCommandHandlerData.cbCommandHandlerAccessCodes / sizeof(UINT)), nCommandHandlerStartTimes.SetSize(sCommandHandlerData.cbCommandHandlerStartTimes), nCommandHandlerStopTimes.SetSize(sCommandHandlerData.cbCommandHandlerStopTimes), nHistoryFilesData[0].SetSize(sCommandHandlerData.cbHistoryFiles[0]), nHistoryFilesData[1].SetSize(sCommandHandlerData.cbHistoryFiles[1]), CopyMemory(szPreferredCommandHandler.GetBufferSetLength(STRINGCHARS(sCommandHandlerData.cbCommandHandler[0])), nInfo.GetData() + (cbData = sizeof(CONFIGURATIONDATA)), STRINGBYTES(sCommandHandlerData.cbCommandHandler[0])), CopyMemory(szBackupCommandHandler.GetBufferSetLength(STRINGCHARS(sCommandHandlerData.cbCommandHandler[1])), nInfo.GetData() + (cbData = cbData + sCommandHandlerData.cbCommandHandler[0]), STRINGBYTES(sCommandHandlerData.cbCommandHandler[1])), CopyMemory(nCommandHandlerClients.GetData(), nInfo.GetData() + (cbData = cbData + sCommandHandlerData.cbCommandHandler[1]), sCommandHandlerData.cbCommandHandlerClients), CopyMemory(nCommandHandlerAccessCodes.GetData(), nInfo.GetData() + (cbData = cbData + sCommandHandlerData.cbCommandHandlerClients), sCommandHandlerData.cbCommandHandlerAccessCodes), CopyMemory(nCommandHandlerStartTimes.GetData(), nInfo.GetData() + (cbData = cbData + sCommandHandlerData.cbCommandHandlerAccessCodes), sCommandHandlerData.cbCommandHandlerStartTimes), CopyMemory(nCommandHandlerStopTimes.GetData(), nInfo.GetData() + (cbData = cbData + sCommandHandlerData.cbCommandHandlerStartTimes), sCommandHandlerData.cbCommandHandlerStopTimes), CopyMemory(nHistoryFilesData[0].GetData(), nInfo.GetData() + (cbData = cbData + sCommandHandlerData.cbCommandHandlerStopTimes), sCommandHandlerData.cbHistoryFiles[0]), CopyMemory(nHistoryFilesData[1].GetData(), nInfo.GetData() + (cbData = cbData + sCommandHandlerData.cbHistoryFiles[0]), sCommandHandlerData.cbHistoryFiles[1]), CopyMemory(szDefaultHistoryFileName.GetBufferSetLength(STRINGCHARS(sCommandHandlerData.cbDefaultHistoryFileName)), nInfo.GetData() + (cbData = cbData + sCommandHandlerData.cbHistoryFiles[1]), STRINGBYTES(sCommandHandlerData.cbDefaultHistoryFileName)), bCommandHandler[0] = sCommandHandlerData.bCommandHandler[0], bCommandHandler[1] = sCommandHandlerData.bCommandHandler[1], bCommandHandler[2] = sCommandHandlerData.bCommandHandler[2], nCommandHandlerOptions = sCommandHandlerData.nCommandHandlerOptions, nCommandHandlerPort = sCommandHandlerData.nCommandHandlerPort, nCommandHandlerBufferSize = sCommandHandlerData.nCommandHandlerBufferSize, tCommandHandlerTimeout = sCommandHandlerData.tCommandHandlerTimeout, nTelecommandingMode = sCommandHandlerData.nTelecommandingMode, nTelecommandingState = sCommandHandlerData.nTelecommandingState, nTelecommandingFlags = sCommandHandlerData.nTelecommandingFlags, bTelecommandingInterlockMode = sCommandHandlerData.bTelecommandingInterlockMode, bTelecommandingReleaseWaitMode = sCommandHandlerData.bTelecommandingReleaseWaitMode, bTelecommandingAutoRejectionMode = sCommandHandlerData.bTelecommandingAutoRejectionMode, tVerificationUncertaintyTimeWindow = sCommandHandlerData.tVerificationUncertaintyTimeWindow, tDefaultReleaseTimeWindow = sCommandHandlerData.tDefaultReleaseTimeWindow, tMaximumExecutionTimePeriod = sCommandHandlerData.tMaximumExecutionTimePeriod, tMaximumTimeCheckPeriod = sCommandHandlerData.tMaximumTimeCheckPeriod, szPreferredCommandHandler.ReleaseBuffer(), szBackupCommandHandler.ReleaseBuffer(), szDefaultHistoryFileName.ReleaseBuffer(); tCommandHandlerStartTimes.Unmap(nCommandHandlerStartTimes) && tCommandHandlerStopTimes.Unmap(nCommandHandlerStopTimes) && pHistoryFiles[0].Unmap(nHistoryFilesData[0]) && pHistoryFiles[1].Unmap(nHistoryFilesData[1]); )
		{
			for (cbClient = cbClients = 0, szCommandHandlerClients.RemoveAll(); cbClients < sCommandHandlerData.cbCommandHandlerClients; cbClients += cbClient)
			{
				szCommandHandlerClients.Add((LPCTSTR)(nCommandHandlerClients.GetData() + cbClients));
				cbClient = (szCommandHandlerClients.GetAt(szCommandHandlerClients.GetUpperBound()).GetLength() + 1)*sizeof(TCHAR);
			}
			if (SetCommandHandlerConfiguration(szPreferredCommandHandler, szBackupCommandHandler, bCommandHandler[0], bCommandHandler[1], bCommandHandler[2], nCommandHandlerOptions, nCommandHandlerPort, nCommandHandlerBufferSize, tCommandHandlerTimeout, szCommandHandlerClients, nCommandHandlerAccessCodes, tCommandHandlerStartTimes, tCommandHandlerStopTimes) && SetCommandHandlerConfiguration(nTelecommandingMode, nTelecommandingState, nTelecommandingFlags, bTelecommandingInterlockMode, bTelecommandingReleaseWaitMode, bTelecommandingAutoRejectionMode, tVerificationUncertaintyTimeWindow, tMaximumExecutionTimePeriod, tMaximumTimeCheckPeriod, tDefaultReleaseTimeWindow, pHistoryFiles[0], pHistoryFiles[1], szDefaultHistoryFileName)) return TRUE;
			break;
		}
		break;
	}
	return((!nInfo.GetSize()) ? TRUE : FALSE);
}

BOOL CTCProcessThread::PreTranslateMessage(MSG *pMsg)
{
	if (pMsg->message == WM_TIMER)
	{
		for (Lock(); pMsg->wParam == m_nCommandUpdateTimerID && m_nCommandUpdateTimerID > 0; )
		{
			UpdateQueues();
			Unlock();
			return TRUE;
		}
		if (pMsg->wParam == m_nArchiveBufferTimerID  &&  m_nArchiveBufferTimerID > 0)
		{
			for (m_bArchiveBufferFlash = TRUE; m_bArchiveBufferFlash; m_bArchiveBufferFlash = FALSE)
			{
				UpdateArchives();
				continue;
			}
			Unlock();
			return TRUE;
		}
		Unlock();
	}
	return CThread::PreTranslateMessage(pMsg);
}

BEGIN_MESSAGE_MAP(CTCProcessThread, CThread)
	//{{AFX_MSG_MAP(CTCProcessThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCProcessThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CTCArchivesBackupThread

IMPLEMENT_DYNCREATE(CTCArchivesBackupThread, CThread)

BOOL CTCArchivesBackupThread::Start(CONST CHistoryStoreFile *pFile, BOOL bDelayed, HANDLE hSync, HANDLE bQuit)
{
	INT  nPos;
	CFileFindEx  cFileFind;
	CHistoryFile  cHistoryFile;
	TCHAR  szFileName[MAX_PATH];

	if (CreateThread((LPVOID)NULL, THREAD_PRIORITY_BELOW_NORMAL, TRUE))
	{
		if (bDelayed  &&  cFileFind.FindFile(pFile->GetBackupFileName()) && !cFileFind.FindNextFile())
		{
			m_szFileName[0] = cFileFind.GetRoot();
			m_szFileName[1] = cFileFind.GetFileTitle();
			m_szFileName[2] = cFileFind.GetFilePath().Right(cFileFind.GetFileName().GetLength() - m_szFileName[1].GetLength());
			m_szFileName[1] = pFile->GetFileName().Mid(pFile->GetBackupFileName().Find(m_szFileName[1]));
			m_szFileName[2] = ((nPos = (!m_szFileName[2].IsEmpty()) ? pFile->GetFileName().ReverseFind(m_szFileName[2][0]) : -1) >= 0) ? (LPCTSTR)pFile->GetFileName().Right(pFile->GetFileName().GetLength() - nPos) : EMPTYSTRING;
			m_szFileName[1] = (nPos >= 0) ? (LPCTSTR)m_szFileName[1].Left(m_szFileName[1].GetLength() - m_szFileName[2].GetLength()) : EMPTYSTRING;
			m_cFile.Copy(pFile);
			m_bAutoDelete = TRUE;
			cFileFind.Close();
			m_hSync = hSync;
			m_bQuit = bQuit;
			ResumeThread();
			return TRUE;
		}
		if (!bDelayed  &&  cFileFind.FindFile(pFile->GetFileName()) && !cFileFind.FindNextFile())
		{
			if (GetTempFileName(cFileFind.GetRoot(), GetAccountSpacecraftName(), 0, szFileName) >= 0)
			{
				if (cHistoryFile.Rename(pFile->GetFileName(), szFileName, TRUE))
				{
					for (m_szFileName[0] = cFileFind.GetRoot(), m_szFileName[1] = cFileFind.GetFileTitle(), m_szFileName[2] = cFileFind.GetFilePath().Right(cFileFind.GetFileName().GetLength() - m_szFileName[1].GetLength()), m_cFile.Copy(pFile), m_bAutoDelete = TRUE, m_hSync = hSync, m_bQuit = bQuit; TRUE; )
					{
						m_cFile.SetBackupFileName(szFileName);
						break;
					}
					cFileFind.Close();
					ResumeThread();
					return TRUE;
				}
			}
			cFileFind.Close();
		}
		ResumeThread();
		DestroyThread();
	}
	Alert(pFile, FALSE);
	return FALSE;
}

BOOL CTCArchivesBackupThread::Stop()
{
	m_szFileName[0].Empty();
	m_szFileName[1].Empty();
	m_szFileName[2].Empty();
	return((DestroyThread() >= 0) ? TRUE : FALSE);
}

int CTCArchivesBackupThread::Run()
{
	UINT  nCount;
	UINT  nRetry;
	DWORD  dwWait;
	DWORD  dwData[2];
	DWORD  dwSize[2];
	PBYTE  pfBuffer;
	CString  szRoot;
	CString  szName;
	CString  szTitle;
	CString  szError;
	CFileEx  cFiles[2];
	CLogFile  cLogFile;
	CTimeKey  tTime[2];
	CTimeSpan  tStartTime;
	CTimeSpan  tStopTime;
	CTimeSpan  tInterval;
	CByteArray  nFileData;
	CFileFindEx  cFileFind;
	CFileFindEx  cCopyFile;
	CFileFindEx  cDiskFile;
	CFileFindEx  cEnumFile;
	CHistoryFile  cHistoryFile;
	CLogicalDrives  cDrives;
	ULARGE_INTEGER  nDiskInfo[3];
	TCHAR  szFileName[MAX_PATH];

	while (Wait(m_bQuit, FALSE, 0) == WAIT_TIMEOUT)
	{
		if (m_cFile.GetBackupTime(tTime[0]) && tTime[0] > tTime[1])
		{
			Wait(m_bQuit, FALSE, (DWORD)(1000 * (tTime[0].GetTime() - tTime[1].GetTime())));
			tTime[1] = CTime::GetCurrentTime().GetTime();
		}
		if (m_cFile.GetBackupDailyPeriod(tStartTime, tStopTime) && tTime[1].GetTime() % SECONDSPERDAY >= tStartTime.GetTotalSeconds() && tTime[1].GetTime() % SECONDSPERDAY <= tStopTime.GetTotalSeconds())
		{
			Wait(m_bQuit, FALSE, (DWORD)(1000 * (tStopTime.GetTotalSeconds() - tTime[1].GetTime() % SECONDSPERDAY)));
			tTime[1] = CTime::GetCurrentTime().GetTime();
		}
		if (Lock())
		{
			if (m_cFile.GetOptions() & HISTORYSTORE_OPTION_BACKUPPROTECTEDDISK)
			{
				GetTempFileName(cDrives.ExtractDrive(m_cFile.GetBackupDirectory()), EMPTYSTRING, 0, szFileName);
				if (GetLastError() != NO_ERROR  &&  Wait(m_bQuit, FALSE, 1000 * TELECOMMANDARCHIVESBACKUP_DELAY_INTERVAL) == WAIT_TIMEOUT)
				{
					Unlock();
					continue;
				}
				CFileEx::Remove(szFileName);
			}
			if (m_cFile.GetOptions() & HISTORYSTORE_OPTION_BACKUPEMPTYDISK)
			{
				if (cDiskFile.FindFile(cDrives.ExtractDrive(m_cFile.GetBackupDirectory()).Left(cDrives.ExtractDrive(m_cFile.GetBackupDirectory()).GetLength() - 1) + STRING(IDS_FILENAME_ALL)))
				{
					while (cDiskFile.FindNextFile())
					{
						if (cDiskFile.IsDots()) continue;
						break;
					}
					if (!cDiskFile.IsDots() && Wait(m_bQuit, FALSE, 1000 * TELECOMMANDARCHIVESBACKUP_DELAY_INTERVAL) == WAIT_TIMEOUT)
					{
						cDiskFile.Close();
						Unlock();
						continue;
					}
					cDiskFile.Close();
				}
			}
			for (_tcscpy_s(szFileName, sizeof(szFileName) / sizeof(TCHAR), EMPTYSTRING); m_cFile.GetOptions() & HISTORYSTORE_OPTION_BACKUPSIMPLE; )
			{
				for (_tcscpy_s(szFileName, sizeof(szFileName) / sizeof(TCHAR), m_cFile.GetBackupDirectory()); m_cFile.GetBackupDirectory().Right(1) != CString(cDrives.GetPathDelimiter()); )
				{
					_tcscat_s(szFileName, sizeof(szFileName) / sizeof(TCHAR), CString(cDrives.GetPathDelimiter()));
					break;
				}
				for (_tcscat_s(szFileName, sizeof(szFileName) / sizeof(TCHAR), m_szFileName[1] + m_szFileName[2]); cFileFind.FindFile(szFileName); )
				{
					for (szName.Format(STRING(IDS_HISTORYFILE_SINGLEBACKUPFORMAT), (LPCTSTR)(m_szFileName[1] + m_szFileName[2])), szRoot = m_cFile.GetBackupDirectory(); szRoot.Right(1) != CString(cDrives.GetPathDelimiter()); )
					{
						szRoot += cDrives.GetPathDelimiter();
						break;
					}
					if (cCopyFile.FindFile((szName = szRoot + szName)))
					{
						for (nCount = 2; nCount != (UINT)-1; nCount++)
						{
							szName.Format(STRING(IDS_HISTORYFILE_MULTIPLEBACKUPFORMAT), nCount, (LPCTSTR)(m_szFileName[1] + m_szFileName[2]));
							if (cEnumFile.FindFile((szName = szRoot + szName)))
							{
								cEnumFile.Close();
								continue;
							}
							break;
						}
						_tcscpy_s(szFileName, sizeof(szFileName) / sizeof(TCHAR), (nCount != (UINT)-1) ? (LPCTSTR)szName : EMPTYSTRING);
						cCopyFile.Close();
					}
					else
					{
						_tcscpy_s(szFileName, sizeof(szFileName) / sizeof(TCHAR), szName);
						cFileFind.Close();
					}
					break;
				}
				szError.Format(STRING(IDS_TELECOMMANDARCHIVES_BACKUP_BEGIN), (LPCTSTR)m_cFile.GetFileName());
				ReportEvent((m_cFile.GetOptions() & HISTORYSTORE_OPTION_BACKUPAUDITFAILURES) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL) : 0, szError, FALSE);
				break;
			}
			if (m_cFile.GetOptions() & HISTORYSTORE_OPTION_BACKUPTIMETAGGED)
			{
				if (cLogFile.Open(m_cFile.GetBackupFileName(), GetAccountSpacecraftName(), STRING(IDS_LOGFILETYPE_TCHISTORY), CFile::modeRead))
				{
					if (cLogFile.SeekToFirst() && cLogFile.Read(tTime[0], nFileData))
					{
						for (_tcscpy_s(szFileName, sizeof(szFileName) / sizeof(TCHAR), m_cFile.GetBackupDirectory()); m_cFile.GetBackupDirectory().Right(1) != CString(cDrives.GetPathDelimiter()); )
						{
							_tcscat_s(szFileName, sizeof(szFileName) / sizeof(TCHAR), CString(cDrives.GetPathDelimiter()));
							break;
						}
						_tcscat_s(szFileName, sizeof(szFileName) / sizeof(TCHAR), tTime[0].FormatGmt(STRING(IDS_HISTORYFILE_TIMETAGGEDFORMAT)));
						_tcscat_s(szFileName, sizeof(szFileName) / sizeof(TCHAR), m_szFileName[2]);
					}
					cLogFile.Close();
				}
				szError.Format(STRING(IDS_TELECOMMANDARCHIVES_BACKUP_BEGIN), (LPCTSTR)m_cFile.GetFileName());
				ReportEvent((m_cFile.GetOptions() & HISTORYSTORE_OPTION_BACKUPAUDITFAILURES) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL) : 0, szError, FALSE);
			}
			if (m_cFile.GetOptions() & HISTORYSTORE_OPTION_BACKUPENUMERATED)
			{
				for (nCount = 0, szRoot = (m_cFile.GetBackupDirectory().Right(1) != CString(cDrives.GetPathDelimiter())) ? (m_cFile.GetBackupDirectory() + cDrives.GetPathDelimiter()) : m_cFile.GetBackupDirectory(); nCount != (UINT)-1; nCount++)
				{
					szTitle.Format(STRING(IDS_HISTORYFILE_ENUMERATEDFORMAT), (LPCTSTR)GetAccountSpacecraftName(), nCount);
					_tcscpy_s(szFileName, sizeof(szFileName) / sizeof(TCHAR), szRoot + szTitle + m_szFileName[2]);
					if (cFileFind.FindFile(szFileName))
					{
						cFileFind.Close();
						continue;
					}
					break;
				}
				szError.Format(STRING(IDS_TELECOMMANDARCHIVES_BACKUP_BEGIN), (LPCTSTR)m_cFile.GetFileName());
				ReportEvent((m_cFile.GetOptions() & HISTORYSTORE_OPTION_BACKUPAUDITFAILURES) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL) : 0, szError, FALSE);
			}
			if (lstrlen(szFileName) > 0)
			{
				if (TestDirectory(szFileName))
				{
					if ((pfBuffer = new BYTE[TELECOMMANDARCHIVESBACKUP_COPY_BUFFER]))
					{
						if (cFiles[0].Open(szFileName, CFile::modeCreate | CFile::modeReadWrite | CFile::shareExclusive))
						{
							if (cFiles[1].Open(m_cFile.GetBackupFileName(), CFile::modeRead | CFile::shareExclusive))
							{
								if (GetDiskFreeSpaceEx(cDrives.ExtractDrive(szFileName), &nDiskInfo[0], &nDiskInfo[1], &nDiskInfo[2]))
								{
									if ((dwSize[0] = GetFileSize((HANDLE)cFiles[1].m_hFile, &dwSize[1])) >= 0 && (dwSize[1] < nDiskInfo[0].HighPart || (dwSize[1] == nDiskInfo[0].HighPart  &&  dwSize[0] < nDiskInfo[0].LowPart)))
									{
										while ((dwWait = Wait(m_bQuit, FALSE, 0)) == WAIT_TIMEOUT)
										{
											if (ReadFile(cFiles[1].m_hFile, pfBuffer, TELECOMMANDARCHIVESBACKUP_COPY_BUFFER, &dwData[0], (LPOVERLAPPED)NULL) && dwData[0] > 0 && WriteFile(cFiles[0].m_hFile, pfBuffer, dwData[0], &dwData[1], (LPOVERLAPPED)NULL) && dwData[0] == dwData[1])
											{
												if (dwData[0] == TELECOMMANDARCHIVESBACKUP_COPY_BUFFER)
												{
													UpdateArchivingStatus();
													continue;
												}
											}
											break;
										}
										if (dwWait == WAIT_TIMEOUT)
										{
											if (GetFileSize((HANDLE)cFiles[0].m_hFile, &dwSize[0]) == GetFileSize((HANDLE)cFiles[1].m_hFile, &dwSize[1]) && dwSize[0] == dwSize[1])
											{
												delete[] pfBuffer;
												cFiles[0].Close();
												cFiles[1].Close();
												cHistoryFile.Remove(m_cFile.GetBackupFileName());
												szError.Format(STRING(IDS_TELECOMMANDARCHIVES_BACKUP_END), (LPCTSTR)m_cFile.GetFileName());
												ReportEvent((m_cFile.GetOptions() & HISTORYSTORE_OPTION_BACKUPAUDITFAILURES) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL) : 0, szError, FALSE);
												UpdateArchivingStatus();
												Alert(&m_cFile, TRUE);
												Unlock();
												return 0;
											}
										}
									}
								}
								cFiles[1].Close();
							}
							cFiles[0].Close();
							CFileEx::Remove(szFileName);
							UpdateArchivingStatus();
						}
						delete[] pfBuffer;
					}
				}
				if ((dwWait = Wait(m_bQuit, FALSE, 0)) == WAIT_TIMEOUT)
				{
					if (m_cFile.GetOptions() & HISTORYSTORE_OPTION_BACKUPRETRIES)
					{
						if ((nCount = m_cFile.GetBackupRetryCount()) > 0)
						{
							m_cFile.GetBackupRetryInfo(nRetry, tInterval);
							m_cFile.SetBackupRetryCount(nCount - 1);
							szError.Format(STRING(IDS_TELECOMMANDARCHIVES_BACKUP_RETRYLATER), (LPCTSTR)m_cFile.GetFileName(), tInterval.GetTotalSeconds() / SECONDSPERMINUTE);
							ReportEvent((m_cFile.GetOptions() & HISTORYSTORE_OPTION_BACKUPAUDITFAILURES) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL) : 0, szError, FALSE);
							if ((dwWait = Wait(m_bQuit, FALSE, (DWORD)(1000 * tInterval.GetTotalSeconds()))) == WAIT_TIMEOUT)
							{
								Unlock();
								continue;
							}
						}
					}
					for (; dwWait == WAIT_TIMEOUT; )
					{
						cHistoryFile.Remove(m_cFile.GetBackupFileName());
						break;
					}
				}
			}
			Unlock();
			break;
		}
	}
	if ((dwWait = Wait(m_bQuit, FALSE, 0)) != WAIT_OBJECT_0 + 1)
	{
		szError.Format((m_cFile.GetOptions() & HISTORYSTORE_OPTION_BACKUPRETRIES) ? (((nCount = m_cFile.GetBackupRetryCount()) >= 0 && m_cFile.GetBackupRetryInfo(nRetry, tInterval) && nCount < nRetry) ? STRING(IDS_TELECOMMANDARCHIVES_BACKUP_RETRIES) : STRING(IDS_TELECOMMANDARCHIVES_BACKUP_FAILURE)) : STRING(IDS_TELECOMMANDARCHIVES_BACKUP_FAILURE), (LPCTSTR)m_cFile.GetFileName(), ((nCount = m_cFile.GetBackupRetryCount()) >= 0 && m_cFile.GetBackupRetryInfo(nRetry, tInterval)) ? (nRetry - nCount) : 0);
		ReportEvent((m_cFile.GetOptions() & HISTORYSTORE_OPTION_BACKUPAUDITFAILURES) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING) : 0, szError);
		Alert(&m_cFile, FALSE);
		return 0;
	}
	if (!DelayBackup())
	{
		szError.Format(STRING(IDS_TELECOMMANDARCHIVES_BACKUP_DELAY), (LPCTSTR)m_cFile.GetFileName());
		ReportEvent((m_cFile.GetOptions() & HISTORYSTORE_OPTION_BACKUPAUDITFAILURES) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_WARNING) : 0, szError);
		Alert(&m_cFile, FALSE);
	}
	szError.Format(STRING(IDS_TELECOMMANDARCHIVES_BACKUP_QUIT), (LPCTSTR)m_cFile.GetFileName());
	ReportEvent((m_cFile.GetOptions() & HISTORYSTORE_OPTION_BACKUPAUDITFAILURES) ? (EVENT_CATEGORY_SYSTEM | EVENT_TYPE_INFORMATIONAL) : 0, szError, FALSE);
	return 0;
}

VOID CTCArchivesBackupThread::Alert(CONST CHistoryStoreFile *pFile, BOOL bSuccess)
{
	CString  szMessage[2];
	CTimeKey  tAlertTime;
	CSystemAlerts  pAlertList;
	CComputerToken  cComputerToken;
	CSystemAlertInfo  *pAlertInfo[2];

	if ((pAlertInfo[0] = (GetSystemAlerts(pAlertList)) ? new CSystemAlertInfo : (CSystemAlertInfo *)NULL))
	{
		if ((pAlertInfo[1] = (bSuccess) ? pAlertList.GetAt(pAlertList.Find(STRING(IDS_SYSTEMALERTS_NAME_HISTORY_FILE_BACKUPS_SUCCESS))) : pAlertList.GetAt(pAlertList.Find(STRING(IDS_SYSTEMALERTS_NAME_HISTORY_FILE_BACKUPS_FAILURE)))))
		{
			szMessage[0].Format(STRING(IDS_SYSTEMALERTS_MESSAGE_HISTORY_FILE_BACKUPS_SUCCESS), (LPCTSTR)pFile->GetFileName(), (LPCTSTR)tAlertTime.FormatGmt(STRING(IDS_TIMEKEY_DEFAULTFORMAT)), (LPCTSTR)cComputerToken.GetComputerName());
			szMessage[1].Format(STRING(IDS_SYSTEMALERTS_MESSAGE_HISTORY_FILE_BACKUPS_FAILURE), (LPCTSTR)cComputerToken.GetComputerName(), (LPCTSTR)tAlertTime.FormatGmt(STRING(IDS_TIMEKEY_DEFAULTFORMAT)), (LPCTSTR)pFile->GetFileName());
			if (pAlertInfo[1]->GetMessage() != STRING(IDS_SYSTEMALERTS_MESSAGE_HISTORY_FILE_BACKUPS_SUCCESS) && pAlertInfo[1]->GetMessage() != STRING(IDS_SYSTEMALERTS_MESSAGE_HISTORY_FILE_BACKUPS_FAILURE))
			{
				szMessage[0] = pAlertInfo[1]->GetMessage();
				szMessage[1] = pAlertInfo[1]->GetMessage();
			}
			pAlertInfo[0]->Copy(pAlertInfo[1]);
			pAlertInfo[0]->SetCategory(EVENT_CATEGORY_SYSTEM);
			pAlertInfo[0]->SetType((bSuccess) ? EVENT_TYPE_SUCCESS : EVENT_TYPE_WARNING);
			pAlertInfo[0]->SetMessage((bSuccess) ? szMessage[0] : szMessage[1]);
			pAlertInfo[0]->SetExtraInfo(pFile->GetFileName());
			ReportEvent(pAlertInfo[0]);
		}
		delete pAlertInfo[0];
	}
}

BOOL CTCArchivesBackupThread::TestDirectory(LPCTSTR pszFileName) CONST
{
	INT  nPos;
	CString  szDrive;
	CString  szFilePath;
	CString  szFileName;
	CString  szFileTitle;
	CFileFindEx  cFileFind;
	CLogicalDrives  cDrives;

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
			szFilePath = (nPos > 0 && cDrives.GetDriveDelimiter() == szFileName.GetAt(nPos - 1)) ? szFileName.Left(nPos - 1) : szFileName.Left(nPos);
			break;
		}
	}
	if (!szFilePath.IsEmpty())
	{
		if (cFileFind.FindFile(szFilePath))
		{
			cFileFind.Close();
			return TRUE;
		}
		return((SHCreateDirectoryEx((HWND)NULL, CFileEx::TranslateToUNCName(szFilePath), (LPSECURITY_ATTRIBUTES)NULL) == ERROR_SUCCESS) ? TRUE : FALSE);
	}
	return TRUE;
}

BOOL CTCArchivesBackupThread::DelayBackup()
{
	CByteArray  nBackupData;
	CHistoryStoreFile  *pFile;
	CHistoryStoreFiles  pFiles;
	CProfile  cProfile;

	if (Wait(m_hSync, FALSE, INFINITE))
	{
		if ((pFile = new CHistoryStoreFile))
		{
			if (cProfile.GetTelecommandArchivesBackupInfo(nBackupData) && pFiles.Unmap(nBackupData))
			{
				for (pFile->Copy(&m_cFile), pFiles.InsertAt(pFiles.GetSize(), pFile, 1); pFiles.Map(nBackupData) && cProfile.SetTelecommandArchivesBackupInfo(nBackupData); )
				{
					ReleaseMutex(m_hSync);
					return TRUE;
				}
			}
			delete pFile;
		}
		ReleaseMutex(m_hSync);
	}
	return FALSE;
}

BOOL CTCArchivesBackupThread::Lock()
{
	HANDLE  hSyncObjects[2] = { m_bQuit,m_hSync };

	return((Wait(hSyncObjects, sizeof(hSyncObjects) / sizeof(HANDLE), FALSE, INFINITE) != WAIT_OBJECT_0 + 1) ? TRUE : FALSE);
}

BOOL CTCArchivesBackupThread::Unlock()
{
	return ReleaseMutex(m_hSync);
}

BEGIN_MESSAGE_MAP(CTCArchivesBackupThread, CThread)
	//{{AFX_MSG_MAP(CTCArchivesBackupThread)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCArchivesBackupThread message handlers


/////////////////////////////////////////////////////////////////////////////
// CTCService

CTCService::CTCService() : CObject()
{
	InitializeLoggingOptions();
	m_tLastTCRetrieveTime = 0;
}

BOOL CTCService::Start(LPCTSTR pszName)
{
	m_cTCHistoryStore.Open(pszName, HISTORYSTORE_TYPE_TC);
	ReportEvent((!LoadServiceInfo()) ? SYSTEM_WARNING_TELECOMMANDSERVICE_LOAD_FAILURE : SYSTEM_NOERROR, FALSE);
	ReportEvent((!HasTCUplinkDevices()) ? SYSTEM_INFORMATIONAL_TELECOMMANDSERVICE_NOT_AVAILABLE : SYSTEM_NOERROR, FALSE);
	return m_cTCProcessThread.Start(pszName);
}

BOOL CTCService::Suspend()
{
	return m_cTCProcessThread.Suspend();
}

BOOL CTCService::IsSuspended() CONST
{
	return m_cTCProcessThread.IsSuspended();
}

BOOL CTCService::Resume()
{
	return m_cTCProcessThread.Resume();
}

VOID CTCService::Stop()
{
	ReportEvent((!SaveServiceInfo()) ? SYSTEM_WARNING_TELECOMMANDSERVICE_SAVE_FAILURE : SYSTEM_NOERROR);
	m_cTCProcessThread.Stop();
	m_cTCHistoryStore.Close();
}

BOOL CTCService::Initialize(CTMEnvironment *pTMEnvironment)
{
	return m_cTCProcessThread.Initialize(pTMEnvironment);
}
BOOL CTCService::Initialize(CTCParameters &pTCParameters)
{
	return m_cTCProcessThread.Initialize(pTCParameters);
}
BOOL CTCService::Initialize(CONST CTCItem *pItem, CTCEnvironment *pTCEnvironment)
{
	return m_cTCProcessThread.Initialize(pItem, pTCEnvironment);
}
BOOL CTCService::Initialize(CONST CTCEnvironment *pTCEnvironment, CTCItem *pItem)
{
	return m_cTCProcessThread.Initialize(pTCEnvironment, pItem);
}

VOID CTCService::Update(CONST CTMProcessEngine *pTMProcessEngine, CONST CTMEnvironment *pTMEnvironment)
{
	m_cTCProcessThread.Update(pTMProcessEngine, pTMEnvironment);
}
VOID CTCService::Update(INT nDataID, UINT nStatus, BOOL bSuccess)
{
	m_cTCProcessThread.Update(nDataID, nStatus, bSuccess);
}
VOID CTCService::Update(LPCTSTR pszEvent)
{
	m_cTCProcessThread.Update(pszEvent);
}
BOOL CTCService::Update()
{
	return m_cTCProcessThread.Update();
}

INT CTCService::EnumTCSubSystems(CStringArray &szSubSystems, BOOL bAll) CONST
{
	return m_cTCProcessThread.EnumTCSubSystems(szSubSystems, bAll);
}

UINT CTCService::TranslateTCSubSystemToID(LPCTSTR pszSubSystem) CONST
{
	return m_cTCProcessThread.TranslateTCSubSystemToID(pszSubSystem);
}

CString CTCService::TranslateIDToTCSubSystem(UINT nSubSystemID) CONST
{
	return m_cTCProcessThread.TranslateIDToTCSubSystem(nSubSystemID);
}

BOOL CTCService::SetTCUplinkDevices(CONST CTCUplinkDevices &pDevices)
{
	return m_cTCProcessThread.SetTCUplinkDevices(pDevices);
}

INT CTCService::GetTCUplinkDevices(CTCUplinkDevices &pDevices) CONST
{
	return m_cTCProcessThread.GetTCUplinkDevices(pDevices);
}

BOOL CTCService::HasTCUplinkDevices(BOOL bSupported) CONST
{
	return m_cTCProcessThread.HasTCUplinkDevices(bSupported);
}

BOOL CTCService::SetActiveTCUplinkDevice(CONST CTCUplinkDevice *pDevice)
{
	return m_cTCProcessThread.SetActiveTCUplinkDevice(pDevice);
}

BOOL CTCService::GetActiveTCUplinkDevice(CTCUplinkDevice *pDevice) CONST
{
	return m_cTCProcessThread.GetActiveTCUplinkDevice(pDevice);
}

BOOL CTCService::SetTCHistoryFiles(UINT nType, CONST CHistoryStoreFiles &pFiles)
{
	return m_cTCHistoryStore.SetHistoryFiles(nType, pFiles);
}

INT CTCService::GetTCHistoryFiles(UINT nType, CHistoryStoreFiles &pFiles) CONST
{
	return m_cTCHistoryStore.GetHistoryFiles(nType, pFiles);
}

INT CTCService::UpdateTCHistoryFiles(CONST CTCEnvironment *pTCEnvironment, CHistoryStoreFiles &pFiles, CUIntArray &nErrors)
{
	return((!m_cTCProcessThread.IsTestModeEnabled()) ? m_cTCHistoryStore.Update(pTCEnvironment, pFiles, nErrors) : 0);
}
INT CTCService::UpdateTCHistoryFiles(CHistoryStoreFiles &pFiles, CUIntArray &nErrors)
{
	return m_cTCHistoryStore.Update(pFiles, nErrors);
}

BOOL CTCService::SetDefaultTCHistoryFile(UINT nType, CONST CHistoryStoreFile &cFile)
{
	return m_cTCHistoryStore.SetDefaultHistoryFile(nType, cFile);
}

BOOL CTCService::GetDefaultTCHistoryFile(UINT nType, CHistoryStoreFile &cFile) CONST
{
	return m_cTCHistoryStore.GetDefaultHistoryFile(nType, cFile);
}

BOOL CTCService::SetRecentTCHistoryTimeKey(CONST CTimeKey &tTime)
{
	CSingleLock  cLock(m_cTCProcessThread.m_pCriticalSection, TRUE);

	return(((m_tLastTCRetrieveTime = tTime) > 0) ? TRUE : FALSE);
}

BOOL CTCService::GetRecentTCHistoryTimeKey(CTimeKey &tTime) CONST
{
	CSingleLock  cLock(m_cTCProcessThread.m_pCriticalSection, TRUE);

	return(((tTime = m_tLastTCRetrieveTime) > 0) ? TRUE : FALSE);
}

BOOL CTCService::UpdateTCDisplays(BOOL bStart)
{
	return m_cTCProcessThread.UpdateTCDisplays(bStart);
}

BOOL CTCService::UpdateTCParameters(CONST CTCParameters &pTCParameters)
{
	return m_cTCProcessThread.UpdateTCParameters(pTCParameters);
}

BOOL CTCService::ResetTCParameters()
{
	return m_cTCProcessThread.ResetTCParameters();
}

BOOL CTCService::SetCommandHandlerConfiguration(LPCTSTR pszPreferredCommandHandler, LPCTSTR pszBackupCommandHandler, BOOL bSelfCommandHandler, BOOL bAnyCommandHandler, BOOL bExclusiveCommandHandler, UINT nCommandHandlerOptions, UINT nCommandHandlerPort, UINT nCommandHandlerBufferSize, CONST CTimeSpan &tCommandHandlerTimeout, CONST CStringArray &szCommandHandlerClients, CONST CUIntArray &nCommandHandlerAccessCodes, CONST CTimeKeyArray &tCommandHandlerStartTimes, CONST CTimeKeyArray &tCommandHandlerStopTimes)
{
	return m_cTCProcessThread.SetCommandHandlerConfiguration(pszPreferredCommandHandler, pszBackupCommandHandler, bSelfCommandHandler, bAnyCommandHandler, bExclusiveCommandHandler, nCommandHandlerOptions, nCommandHandlerPort, nCommandHandlerBufferSize, tCommandHandlerTimeout, szCommandHandlerClients, nCommandHandlerAccessCodes, tCommandHandlerStartTimes, tCommandHandlerStopTimes);
}
BOOL CTCService::SetCommandHandlerConfiguration(CONST CTCProcessCommandSources &pCommandSources, UINT nTelecommandingMode, UINT nTelecommandingState, UINT nTelecommandingFlags, BOOL bTelecommandingInterlockMode, BOOL bTelecommandingReleaseWaitMode, BOOL bTelecommandingAutoRejectionMode, CONST CTimeSpan &tVerificationUncertaintyTimeWindow, CONST CTimeSpan &tMaximumExecutionTimePeriod, CONST CTimeSpan &tMaximumTimeCheckPeriod, CONST CTimeSpan &tDefaultReleaseTimeWindow, CONST CHistoryStoreFiles &pHistoryArchivalFiles, CONST CHistoryStoreFiles &pHistoryRetrievalFiles, LPCTSTR pszDefaultHistoryFileName, BOOL bUpdate)
{
	return m_cTCProcessThread.SetCommandHandlerConfiguration(pCommandSources, nTelecommandingMode, nTelecommandingState, nTelecommandingFlags, bTelecommandingInterlockMode, bTelecommandingReleaseWaitMode, bTelecommandingAutoRejectionMode, tVerificationUncertaintyTimeWindow, tMaximumExecutionTimePeriod, tMaximumTimeCheckPeriod, tDefaultReleaseTimeWindow, pHistoryArchivalFiles, pHistoryRetrievalFiles, pszDefaultHistoryFileName, bUpdate);
}

BOOL CTCService::GetCommandHandlerConfiguration(CString &szPreferredCommandHandler, CString &szBackupCommandHandler, BOOL &bSelfCommandHandler, BOOL &bAnyCommandHandler, BOOL &bExclusiveCommandHandler, UINT &nCommandHandlerOptions, UINT &nCommandHandlerPort, UINT &nCommandHandlerBufferSize, CTimeSpan &tCommandHandlerTimeout, CStringArray &szCommandHandlerClients, CUIntArray &nCommandHandlerAccessCodes, CTimeKeyArray &tCommandHandlerStartTimes, CTimeKeyArray &tCommandHandlerStopTimes) CONST
{
	return m_cTCProcessThread.GetCommandHandlerConfiguration(szPreferredCommandHandler, szBackupCommandHandler, bSelfCommandHandler, bAnyCommandHandler, bExclusiveCommandHandler, nCommandHandlerOptions, nCommandHandlerPort, nCommandHandlerBufferSize, tCommandHandlerTimeout, szCommandHandlerClients, nCommandHandlerAccessCodes, tCommandHandlerStartTimes, tCommandHandlerStopTimes);
}
BOOL CTCService::GetCommandHandlerConfiguration(CTCProcessCommandSources &pCommandSources, UINT &nTelecommandingMode, UINT &nTelecommandingState, UINT &nTelecommandingFlags, BOOL &bTelecommandingInterlockMode, BOOL &bTelecommandingReleaseWaitMode, BOOL &bTelecommandingAutoRejectionMode, CTimeSpan &tVerificationUncertaintyTimeWindow, CTimeSpan &tMaximumExecutionTimePeriod, CTimeSpan &tMaximumTimeCheckPeriod, CTimeSpan &tDefaultReleaseTimeWindow, CTCItems &pItems, CTCInterlocks &pInterlocks, CHistoryStoreFiles &pHistoryArchivalFiles, CHistoryStoreFiles &pHistoryRetrievalFiles, CString &szDefaultHistoryFileName, HWND hUpdateWnd, UINT_PTR nUpdateTimerID, BOOL &bUpdate)
{
	return m_cTCProcessThread.GetCommandHandlerConfiguration(pCommandSources, nTelecommandingMode, nTelecommandingState, nTelecommandingFlags, bTelecommandingInterlockMode, bTelecommandingReleaseWaitMode, bTelecommandingAutoRejectionMode, tVerificationUncertaintyTimeWindow, tMaximumExecutionTimePeriod, tMaximumTimeCheckPeriod, tDefaultReleaseTimeWindow, pItems, pInterlocks, pHistoryArchivalFiles, pHistoryRetrievalFiles, szDefaultHistoryFileName, hUpdateWnd, nUpdateTimerID, bUpdate);
}

BOOL CTCService::SetCommandHandlerContents(CONST CTCItems &pItems, CONST CTCInterlocks &pInterlocks, CONST CTCOnBoardBufferQueues &pQueues)
{
	return m_cTCProcessThread.SetCommandHandlerContents(pItems, pInterlocks, pQueues);
}

BOOL CTCService::GetCommandHandlerContents(CTCItems &pItems, CTCInterlocks &pInterlocks, CTCOnBoardBufferQueues &pQueues) CONST
{
	return m_cTCProcessThread.GetCommandHandlerContents(pItems, pInterlocks, pQueues);
}

BOOL CTCService::SetCommandHandlerVerificationUncertaintyTimeWindow(CONST CTimeSpan &tTimeWindow)
{
	return m_cTCProcessThread.SetCommandHandlerVerificationUncertaintyTimeWindow(tTimeWindow);
}

BOOL CTCService::GetCommandHandlerVerificationUncertaintyTimeWindow(CTimeSpan &tTimeWindow) CONST
{
	return m_cTCProcessThread.GetCommandHandlerVerificationUncertaintyTimeWindow(tTimeWindow);
}

BOOL CTCService::SetCommandHandlerDefaultReleaseTimeWindow(CONST CTimeSpan &tTimeWindow)
{
	return m_cTCProcessThread.SetCommandHandlerDefaultReleaseTimeWindow(tTimeWindow);
}

BOOL CTCService::GetCommandHandlerDefaultReleaseTimeWindow(CTimeSpan &tTimeWindow) CONST
{
	return m_cTCProcessThread.GetCommandHandlerDefaultReleaseTimeWindow(tTimeWindow);
}

BOOL CTCService::SetCommandHandlerOptions(UINT nOptions)
{
	return m_cTCProcessThread.SetCommandHandlerOptions(nOptions);
}

UINT CTCService::GetCommandHandlerOptions() CONST
{
	return m_cTCProcessThread.GetCommandHandlerOptions();
}

BOOL CTCService::SetCommandHandlerState(UINT nState)
{
	return m_cTCProcessThread.SetCommandHandlerState(nState);
}

UINT CTCService::GetCommandHandlerState() CONST
{
	return m_cTCProcessThread.GetCommandHandlerState();
}

BOOL CTCService::SetCommandSourceTelecommandingMode(UINT nSourceType, UINT nMode)
{
	CComputerToken  cComputerToken;

	return m_cTCProcessThread.SetCommandSourceTelecommandingMode(cComputerToken.GetComputerName(), nSourceType, nMode);
}

UINT CTCService::GetCommandSourceTelecommandingMode(UINT nSourceType) CONST
{
	CComputerToken  cComputerToken;

	return m_cTCProcessThread.GetCommandSourceTelecommandingMode(cComputerToken.GetComputerName(), nSourceType);
}

BOOL CTCService::SetCommandSourceTelecommandingState(UINT nSourceType, UINT nState)
{
	CComputerToken  cComputerToken;

	return m_cTCProcessThread.SetCommandSourceTelecommandingState(cComputerToken.GetComputerName(), nSourceType, nState);
}

UINT CTCService::GetCommandSourceTelecommandingState(UINT nSourceType) CONST
{
	CComputerToken  cComputerToken;

	return m_cTCProcessThread.GetCommandSourceTelecommandingState(cComputerToken.GetComputerName(), nSourceType);
}

BOOL CTCService::SetCommandSourceTelecommandingChecks(UINT nSourceType, UINT nFlags)
{
	CComputerToken  cComputerToken;

	return m_cTCProcessThread.SetCommandSourceTelecommandingChecks(cComputerToken.GetComputerName(), nSourceType, nFlags);
}

UINT CTCService::GetCommandSourceTelecommandingChecks(UINT nSourceType) CONST
{
	CComputerToken  cComputerToken;

	return m_cTCProcessThread.GetCommandSourceTelecommandingChecks(cComputerToken.GetComputerName(), nSourceType);
}

BOOL CTCService::EnableCommandSourceTelecommandingInterlockMode(UINT nSourceType, BOOL bEnable)
{
	CComputerToken  cComputerToken;

	return m_cTCProcessThread.EnableCommandSourceTelecommandingInterlockMode(cComputerToken.GetComputerName(), nSourceType, bEnable);
}

BOOL CTCService::IsCommandSourceTelecommandingInterlockModeEnabled(UINT nSourceType) CONST
{
	CComputerToken  cComputerToken;

	return m_cTCProcessThread.IsCommandSourceTelecommandingInterlockModeEnabled(cComputerToken.GetComputerName(), nSourceType);
}

BOOL CTCService::EnableCommandSourceTelecommandingReleaseWaitMode(UINT nSourceType, BOOL bEnable)
{
	CComputerToken  cComputerToken;

	return m_cTCProcessThread.EnableCommandSourceTelecommandingReleaseWaitMode(cComputerToken.GetComputerName(), nSourceType, bEnable);
}

BOOL CTCService::IsCommandSourceTelecommandingReleaseWaitModeEnabled(UINT nSourceType) CONST
{
	CComputerToken  cComputerToken;

	return m_cTCProcessThread.IsCommandSourceTelecommandingReleaseWaitModeEnabled(cComputerToken.GetComputerName(), nSourceType);
}

BOOL CTCService::EnableCommandSourceTelecommandingAutoRejectionMode(UINT nSourceType, BOOL bEnable)
{
	CComputerToken  cComputerToken;

	return m_cTCProcessThread.EnableCommandSourceTelecommandingAutoRejectionMode(cComputerToken.GetComputerName(), nSourceType, bEnable);
}

BOOL CTCService::IsCommandSourceTelecommandingAutoRejectionModeEnabled(UINT nSourceType) CONST
{
	CComputerToken  cComputerToken;

	return m_cTCProcessThread.IsCommandSourceTelecommandingAutoRejectionModeEnabled(cComputerToken.GetComputerName(), nSourceType);
}

BOOL CTCService::SetCommandSourceSubSystemChecks(UINT nSourceType, CONST CUIntArray &nSubSystemIDs, CONST CStringArray &szEnablingEvents, CONST CStringArray &szDisablingEvents, CONST CUIntArray &nStatus)
{
	CComputerToken  cComputerToken;

	return m_cTCProcessThread.SetCommandSourceSubSystemChecks(cComputerToken.GetComputerName(), nSourceType, nSubSystemIDs, szEnablingEvents, szDisablingEvents, nStatus);
}

BOOL CTCService::GetCommandSourceSubSystemChecks(UINT nSourceType, CUIntArray &nSubSystemIDs, CStringArray &szEnablingEvents, CStringArray &szDisablingEvents, CUIntArray &nStatus) CONST
{
	CComputerToken  cComputerToken;

	return m_cTCProcessThread.GetCommandSourceSubSystemChecks(cComputerToken.GetComputerName(), nSourceType, nSubSystemIDs, szEnablingEvents, szDisablingEvents, nStatus);
}

BOOL CTCService::IsCommandSourceSubSystemEnabled(UINT nSourceType, CONST CTCItem *pItem) CONST
{
	CComputerToken  cComputerToken;

	return m_cTCProcessThread.IsCommandSourceSubSystemEnabled(cComputerToken.GetComputerName(), nSourceType, pItem);
}

BOOL CTCService::SetDefaultReleaseTimeWindow(UINT nSourceType, CONST CTimeSpan &tTimeWindow)
{
	CComputerToken  cComputerToken;

	return m_cTCProcessThread.SetDefaultReleaseTimeWindow(cComputerToken.GetComputerName(), nSourceType, tTimeWindow);
}

CTimeSpan CTCService::GetDefaultReleaseTimeWindow(UINT nSourceType) CONST
{
	CComputerToken  cComputerToken;

	return m_cTCProcessThread.GetDefaultReleaseTimeWindow(cComputerToken.GetComputerName(), nSourceType);
}

BOOL CTCService::SetDispatchTimeWindow(UINT nSourceType, CONST CTimeSpan &tTimeWindow)
{
	CComputerToken  cComputerToken;

	return m_cTCProcessThread.SetDispatchTimeWindow(cComputerToken.GetComputerName(), nSourceType, tTimeWindow);
}

CTimeSpan CTCService::GetDispatchTimeWindow(UINT nSourceType) CONST
{
	CComputerToken  cComputerToken;

	return m_cTCProcessThread.GetDispatchTimeWindow(cComputerToken.GetComputerName(), nSourceType);
}

BOOL CTCService::LoadTelecommands(CONST CTCItems &pItems)
{
	return m_cTCProcessThread.LoadTelecommands(pItems);
}

BOOL CTCService::DispatchTelecommands(CONST CTCItems &pItems, BOOL bUndo)
{
	return m_cTCProcessThread.DispatchTelecommands(pItems, bUndo);
}

BOOL CTCService::AcknowledgeTelecommands(CONST CTCItems &pItems)
{
	return m_cTCProcessThread.AcknowledgeTelecommands(pItems);
}

BOOL CTCService::GenerateTCPackets(CONST CDatabaseTCFunction *pFunction, CONST CDatabaseTCPacket *pPacket, LPCTSTR pszMemoryPatch, BOOL bTimeTagged, BOOL b2ndStep, BOOL bBlocked, BOOL bExample, CDatabaseTCFunctions &pFunctions, CDatabaseTCPackets &pPackets)
{
	return m_cTCProcessThread.GenerateTCPackets(pFunction, pPacket, pszMemoryPatch, bTimeTagged, b2ndStep, bBlocked, bExample, pFunctions, pPackets);
}

BOOL CTCService::DecodeTCPacket(CONST CTCPacket *pTCPacket, CDatabaseTCFunction *pDatabaseTCFunction, CDatabaseTCFunctions &pDatabaseBlockedTCFunctions, CDatabaseTCPacket *pDatabaseTCPacket) CONST
{
	return m_cTCProcessThread.DecodeTCPacket(pTCPacket, pDatabaseTCFunction, pDatabaseBlockedTCFunctions, pDatabaseTCPacket);
}

BOOL CTCService::CheckTCFunctionExecutionTime(CONST CDatabaseTCFunction *pDatabaseTCFunction, CONST CDatabaseTCPacket *pDatabaseTCPacket, CONST CTimeTag &tExecutionTime) CONST
{
	return m_cTCProcessThread.CheckTCFunctionExecutionTime(pDatabaseTCFunction, pDatabaseTCPacket, tExecutionTime);
}

BOOL CTCService::SetTCFunctionExecutionTimeOffsets(CONST CTimeSpan &tMin, CONST CTimeSpan &tMax)
{
	return m_cTCProcessThread.SetTCFunctionExecutionTimeOffsets(tMin, tMax);
}

BOOL CTCService::GetTCFunctionExecutionTimeOffsets(CTimeSpan &tMin, CTimeSpan &tMax) CONST
{
	return m_cTCProcessThread.GetTCFunctionExecutionTimeOffsets(tMin, tMax);
}

BOOL CTCService::SetTCFunctionParameterTimeOffsets(CONST CTimeSpan &tMin, CONST CTimeSpan &tMax)
{
	return m_cTCProcessThread.SetTCFunctionParameterTimeOffsets(tMin, tMax);
}

BOOL CTCService::GetTCFunctionParameterTimeOffsets(CTimeSpan &tMin, CTimeSpan &tMax) CONST
{
	return m_cTCProcessThread.GetTCFunctionParameterTimeOffsets(tMin, tMax);
}

BOOL CTCService::ConvertTCParameterValue(LPCTSTR pszTag, ULONGLONG nAttributes, LPCTSTR pszValue, ULONGLONG &nValue) CONST
{
	return m_cTCProcessThread.ConvertTCParameterValue(pszTag, nAttributes, pszValue, nValue);
}
BOOL CTCService::ConvertTCParameterValue(CONST CDatabaseTCParameter *pDatabaseTCParameter, ULONGLONG &nValue) CONST
{
	return m_cTCProcessThread.ConvertTCParameterValue(pDatabaseTCParameter, nValue);
}

BOOL CTCService::CheckTCParameterOolStatus(CONST CDatabaseTCParameter *pParameter, UINT &nOolStatus) CONST
{
	return m_cTCProcessThread.CheckTCParameterOolStatus(pParameter, nOolStatus);
}

BOOL CTCService::CheckTCFunctionElementOolStatus(CONST CDatabaseTCFunctionElement *pFunctionElement, UINT &nOolStatus) CONST
{
	return m_cTCProcessThread.CheckTCFunctionElementOolStatus(pFunctionElement, nOolStatus);
}

BOOL CTCService::CheckTCPacketParameterOolStatus(CONST CDatabaseTCPacketParameter *pPacketParameter, UINT &nOolStatus) CONST
{
	return m_cTCProcessThread.CheckTCPacketParameterOolStatus(pPacketParameter, nOolStatus);
}

BOOL CTCService::CheckTCProcedureArgumentOolStatus(CONST CDatabaseTCProcedureArgument *pArgument, UINT &nOolStatus) CONST
{
	return m_cTCProcessThread.CheckTCProcedureArgumentOolStatus(pArgument, nOolStatus);
}

BOOL CTCService::CheckTCFunctionPreexecutionParameterGroup(INT nGroupID, CStringArray &szParameters) CONST
{
	return m_cTCProcessThread.CheckTCFunctionPreexecutionParameterGroup(nGroupID, szParameters);
}

BOOL CTCService::SetTCInterlocks(CONST CTCInterlocks &pInterlocks)
{
	return m_cTCProcessThread.SetTCInterlocks(pInterlocks);
}
BOOL CTCService::SetTCInterlocks(UINT nSourceType, CONST CTCInterlocks &pInterlocks)
{
	return m_cTCProcessThread.SetTCInterlocks(nSourceType, pInterlocks);
}

BOOL CTCService::GetTCInterlocks(CTCInterlocks &pInterlocks) CONST
{
	return m_cTCProcessThread.GetTCInterlocks(pInterlocks);
}
BOOL CTCService::GetTCInterlocks(UINT nSourceType, CTCInterlocks &pInterlocks) CONST
{
	return m_cTCProcessThread.GetTCInterlocks(nSourceType, pInterlocks);
}

BOOL CTCService::CheckTCInterlocks(UINT nSourceType, UINT nState) CONST
{
	return m_cTCProcessThread.CheckTCInterlocks(nSourceType, nState);
}

BOOL CTCService::CheckTCInterlock(UINT nSourceType, LPCTSTR pszInterlock, UINT &nState) CONST
{
	return m_cTCProcessThread.CheckTCInterlock(nSourceType, pszInterlock, nState);
}
BOOL CTCService::CheckTCInterlock(UINT nSourceType, LPCTSTR pszInterlock, UINT &nScope, UINT &nStage, UINT &nState) CONST
{
	return m_cTCProcessThread.CheckTCInterlock(nSourceType, pszInterlock, nScope, nStage, nState);
}
BOOL CTCService::CheckTCInterlock(CONST CTCItem *pItem) CONST
{
	return m_cTCProcessThread.CheckTCInterlock(pItem);
}

INT CTCService::EnumTCDiagnosticsOversamplingDumpRates(CStringArray &szRates) CONST
{
	return m_cTCProcessThread.EnumTCDiagnosticsOversamplingDumpRates(szRates);
}

BOOL CTCService::EncodeTCDiagnosticsOversamplingDump(CONST CTimeTag &tExecutionTime, CONST COversamplingParameters &pOversamplingParameters, CDatabaseTCFunction *pDatabaseTCFunction)
{
	return m_cTCProcessThread.EncodeTCDiagnosticsOversamplingDump(tExecutionTime, pOversamplingParameters, pDatabaseTCFunction);
}

BOOL CTCService::DecodeTCDiagnosticsOversamplingDump(CONST CDatabaseTCFunction *pDatabaseTCFunction, COversamplingParameters &pOversamplingParameters)
{
	return m_cTCProcessThread.DecodeTCDiagnosticsOversamplingDump(pDatabaseTCFunction, pOversamplingParameters);
}
BOOL CTCService::DecodeTCDiagnosticsOversamplingDump(CONST CTMEnvironment *pTMEnvironment, COversamplingParameters &pOversamplingParameters, BOOL bAutomatic)
{
	return m_cTCProcessThread.DecodeTCDiagnosticsOversamplingDump(pTMEnvironment, pOversamplingParameters, bAutomatic);
}

double CTCService::CalculateTCDiagnosticsOversamplingBandwidth(COversamplingParameters &pOversamplingParameters) CONST
{
	return m_cTCProcessThread.CalculateTCDiagnosticsOversamplingBandwidth(pOversamplingParameters);
}

INT CTCService::EnumTCOnBoardBufferTypes(CStringArray &szTypes) CONST
{
	return m_cTCProcessThread.EnumTCOnBoardBufferTypes(szTypes);
}

INT CTCService::EnumTCOnBoardBufferQueues(CTCOnBoardBufferQueues &pQueues) CONST
{
	return m_cTCProcessThread.EnumTCOnBoardBufferQueues(pQueues);
}
INT CTCService::EnumTCOnBoardBufferQueues(LPCTSTR pszType, CStringArray &szNames) CONST
{
	return m_cTCProcessThread.EnumTCOnBoardBufferQueues(pszType, szNames);
}
INT CTCService::EnumTCOnBoardBufferQueues(LPCTSTR pszType, CStringArray &szNames, CUIntArray &nAPIDs, CUIntArray &nSubScheduleIDs, CUIntArray &nLimits, CStringArray &szUnits, CUIntArray &tTimeouts) CONST
{
	return m_cTCProcessThread.EnumTCOnBoardBufferQueues(pszType, szNames, nAPIDs, nSubScheduleIDs, nLimits, szUnits, tTimeouts);
}

INT CTCService::UpdateTCOnBoardBufferQueues(CONST CTMEnvironment *pTMEnvironment, CStringArray &szTypes, CStringArray &szNames, CUIntArray &nSubScheduleIDs, CUIntArray &nCounts, CTimeTagArray &tUpdateTimes, CUIntArray &nStatus)
{
	return m_cTCProcessThread.UpdateTCOnBoardBufferQueues(pTMEnvironment, szTypes, szNames, nSubScheduleIDs, nCounts, tUpdateTimes, nStatus);
}

BOOL CTCService::CheckTCOnBoardBufferQueues(CONST CTCItems &pItems, INT nChecks) CONST
{
	return m_cTCProcessThread.CheckTCOnBoardBufferQueues(pItems, nChecks);
}

BOOL CTCService::UpdateTCOnBoardBufferQueue(LPCTSTR pszType, LPCTSTR pszName, UINT nSubScheduleID, CONST CTCItems &pItems)
{
	return m_cTCProcessThread.UpdateTCOnBoardBufferQueue(pszType, pszName, nSubScheduleID, pItems);
}
BOOL CTCService::UpdateTCOnBoardBufferQueue(LPCTSTR pszType, LPCTSTR pszName, UINT nSubScheduleID, UINT nFlags, UINT nAPID, UINT nPSC, INT nLowEntry, INT nHighEntry, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime)
{
	return m_cTCProcessThread.UpdateTCOnBoardBufferQueue(pszType, pszName, nSubScheduleID, nFlags, nAPID, nPSC, nLowEntry, nHighEntry, tStartTime, tStopTime);
}

BOOL CTCService::AcknowledgeTCOnBoardBufferQueue(LPCTSTR pszType, LPCTSTR pszName, UINT nSubScheduleID, UINT nFlags)
{
	return m_cTCProcessThread.AcknowledgeTCOnBoardBufferQueue(pszType, pszName, nSubScheduleID, nFlags);
}

BOOL CTCService::CheckTCOnBoardBufferQueue(LPCTSTR pszType, LPCTSTR pszName, BOOL &bStatus, BOOL &bDumpAllEntries, BOOL &bDumpByAPID, BOOL &bDumpByPSC, BOOL &bDumpByEntryRange, BOOL &bDumpByTimeRange, BOOL &bResetAllEntries, BOOL &bResetByAPID, BOOL &bResetByPSC, BOOL &bResetByEntryRange, BOOL &bResetByTimeRange) CONST
{
	return m_cTCProcessThread.CheckTCOnBoardBufferQueue(pszType, pszName, bStatus, bDumpAllEntries, bDumpByAPID, bDumpByPSC, bDumpByEntryRange, bDumpByTimeRange, bResetAllEntries, bResetByAPID, bResetByPSC, bResetByEntryRange, bResetByTimeRange);
}
BOOL CTCService::CheckTCOnBoardBufferQueue(CONST CTCItem *pItem) CONST
{
	return m_cTCProcessThread.CheckTCOnBoardBufferQueue(pItem);
}

BOOL CTCService::EncodeTCOnBoardBufferQueueStatus(LPCTSTR pszType, LPCTSTR pszName, CONST CTimeTag &tExecutionTime, BOOL bEnable, CDatabaseTCFunction *pDatabaseTCFunction) CONST
{
	return m_cTCProcessThread.EncodeTCOnBoardBufferQueueStatus(pszType, pszName, tExecutionTime, bEnable, pDatabaseTCFunction);
}
BOOL CTCService::EncodeTCOnBoardBufferQueueDump(LPCTSTR pszType, LPCTSTR pszName, CONST CTimeTag &tExecutionTime, UINT nAPID, UINT nPSC, UINT nLowEntry, UINT nHighEntry, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, CDatabaseTCFunction *pDatabaseTCFunction) CONST
{
	return m_cTCProcessThread.EncodeTCOnBoardBufferQueueDump(pszType, pszName, tExecutionTime, nAPID, nPSC, nLowEntry, nHighEntry, tStartTime, tStopTime, pDatabaseTCFunction);
}
BOOL CTCService::EncodeTCOnBoardBufferQueueReset(LPCTSTR pszType, LPCTSTR pszName, CONST CTimeTag &tExecutionTime, UINT nAPID, UINT nPSC, UINT nLowEntry, UINT nHighEntry, CONST CTimeKey &tStartTime, CONST CTimeKey &tStopTime, CONST CTCPacket *pTCPacket, CDatabaseTCFunction *pDatabaseTCFunction) CONST
{
	return m_cTCProcessThread.EncodeTCOnBoardBufferQueueReset(pszType, pszName, tExecutionTime, nAPID, nPSC, nLowEntry, nHighEntry, tStartTime, tStopTime, pTCPacket, pDatabaseTCFunction);
}

BOOL CTCService::FindTCOnBoardBufferQueue(CONST CTCPacket *pTCPacket, CString &szType, CString &szName, UINT &nSubScheduleID) CONST
{
	return m_cTCProcessThread.FindTCOnBoardBufferQueue(pTCPacket, szType, szName, nSubScheduleID);
}

BOOL CTCService::ExpandTCOnBoardBufferQueueEntry(CONST CTCPacket *pTCPacket, UINT &nBlockOffset, UINT &nBlockBytes, CUIntArray &nBlockSizes, CTimeTagArray &tBlockTimes) CONST
{
	return m_cTCProcessThread.ExpandTCOnBoardBufferQueueEntry(pTCPacket, nBlockOffset, nBlockBytes, nBlockSizes, tBlockTimes);
}

UINT CTCService::CalculateTCOnBoardBufferQueueEntry(CONST CTCPacket *pTCPacket) CONST
{
	return m_cTCProcessThread.CalculateTCOnBoardBufferQueueEntry(pTCPacket);
}

BOOL CTCService::CheckTCOnBoardMemoryImageDumpCapabilities(CONST CDatabaseOBProcessor *pProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage, BOOL &bStop) CONST
{
	return m_cTCProcessThread.CheckTCOnBoardMemoryImageDumpCapabilities(pProcessor, pImage, bStop);
}

BOOL CTCService::EncodeTCOnBoardMemoryImageDump(CONST CDatabaseOBProcessor *pProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage, CONST CTimeKey &tExecutionTime, BOOL bStop, CDatabaseTCFunction *pDatabaseTCFunction)
{
	return m_cTCProcessThread.EncodeTCOnBoardMemoryImageDump(pProcessor, pImage, tExecutionTime, bStop, pDatabaseTCFunction);
}

BOOL CTCService::IsTCOnBoardMemoryImageDump(CONST CTMEnvironment *pTMEnvironment) CONST
{
	return m_cTCProcessThread.IsTCOnBoardMemoryImageDump(pTMEnvironment);
}

BOOL CTCService::CheckTCOnBoardMemoryImagePatchCapabilities(CONST CDatabaseOBProcessor *pProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage) CONST
{
	return m_cTCProcessThread.CheckTCOnBoardMemoryImagePatchCapabilities(pProcessor, pImage);
}

BOOL CTCService::EncodeTCOnBoardMemoryImagePatch(CONST CDatabaseOBProcessor *pProcessor, CONST CDatabaseOBProcessorMemoryImage *pImage, CONST CTimeKey &tExecutionTime, CDatabaseTCFunctions &pDatabaseTCFunctions, CDatabaseTCPackets &pDatabaseTCPackets)
{
	return m_cTCProcessThread.EncodeTCOnBoardMemoryImagePatch(pProcessor, pImage, tExecutionTime, pDatabaseTCFunctions, pDatabaseTCPackets);
}

BOOL CTCService::CalculateTCOnBoardMemoryImageCRC(CONST CDatabaseOBProcessor *pProcessor, CDatabaseOBProcessorMemoryImage *pImage, LPCTSTR pszImageVersion) CONST
{
	return m_cTCProcessThread.CalculateTCOnBoardMemoryImageCRC(pProcessor, pImage, pszImageVersion);
}

BOOL CTCService::IsTCOnBoardMemoryImagePatch(CONST CTCPacket *pTCPacket, CString &szProcessor) CONST
{
	return m_cTCProcessThread.IsTCOnBoardMemoryImagePatch(pTCPacket, szProcessor);
}

BOOL CTCService::InitializeLoggingOptions()
{
	CString  szFileName;
	CEventLog  cEventLog;
	CFileFindEx  cFileFind;
	CLogicalDrives  cDrives;
	CSingleLock  cLock(m_cTCProcessThread.m_pCriticalSection, TRUE);

	if (cEventLog.SetOwner(GetAccountComputerName(), GetAccountSpacecraftName(), GetAccountUserName()))
	{
		if (cEventLog.QuerySpacecraftLogFileName(szFileName) && cFileFind.FindFile(szFileName) && !cFileFind.FindNextFile())
		{
			m_szLoggingFileName[0] = m_szLoggingFileName[1] = (cFileFind.GetRoot().Right(1).GetAt(0) != cDrives.GetPathDelimiter()) ? (cFileFind.GetRoot() + cDrives.GetPathDelimiter() + STRING(IDS_TELECOMMANDOPTIONS_LOGFILE_DEFAULTFILENAME)) : (cFileFind.GetRoot() + STRING(IDS_TELECOMMANDOPTIONS_LOGFILE_DEFAULTFILENAME));
			m_nLoggingPolicy = LOGFILE_POLICY_CYCLICMODE | LOGFILE_POLICY_RETENTIONBYTIME;
			m_tLoggingRetention = DAYSPERWEEK*SECONDSPERDAY;
			m_dwLoggingRetention = 0;
			m_nLoggingReloadCount = 0;
			m_bLoggingAsEvent = FALSE;
			cFileFind.Close();
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CTCService::SetLoggingOptions(UINT nArchivalPolicy, LPCTSTR pszArchivalFileName, DWORDLONG dwArchivalRetention, CONST CTimeSpan &tArchivalRetention, LPCTSTR pszRetrievalFileName, UINT nRetrievalReloadCount, BOOL bShowAsEvent)
{
	CSingleLock  cLock(m_cTCProcessThread.m_pCriticalSection, TRUE);

	m_nLoggingPolicy = nArchivalPolicy;
	m_szLoggingFileName[0] = pszArchivalFileName;
	m_szLoggingFileName[1] = pszRetrievalFileName;
	m_dwLoggingRetention = dwArchivalRetention;
	m_tLoggingRetention = tArchivalRetention;
	m_nLoggingReloadCount = nRetrievalReloadCount;
	m_bLoggingAsEvent = bShowAsEvent;
	return TRUE;
}

BOOL CTCService::GetLoggingOptions(UINT &nArchivalPolicy, CString &szArchivalFileName, DWORDLONG &dwArchivalRetention, CTimeSpan &tArchivalRetention, CString &szRetrievalFileName, UINT &nRetrievalReloadCount, BOOL &bShowAsEvent) CONST
{
	CSingleLock  cLock(m_cTCProcessThread.m_pCriticalSection, TRUE);

	nArchivalPolicy = m_nLoggingPolicy;
	szArchivalFileName = m_szLoggingFileName[0];
	szRetrievalFileName = m_szLoggingFileName[1];
	dwArchivalRetention = m_dwLoggingRetention;
	tArchivalRetention = m_tLoggingRetention;
	nRetrievalReloadCount = m_nLoggingReloadCount;
	bShowAsEvent = m_bLoggingAsEvent;
	return TRUE;
}

BOOL CTCService::ConvertTimeToOBRT(CONST CTimeTag &tOBRT, UINT &nOBRT) CONST
{
	return m_cTCProcessThread.ConvertTimeToOBRT(tOBRT, nOBRT);
}

BOOL CTCService::ConvertOBRTToTime(UINT nOBRT, CTimeTag &tOBRT) CONST
{
	return m_cTCProcessThread.ConvertOBRTToTime(nOBRT, tOBRT);
}

BOOL CTCService::CorrelateTCTransferFrameSequenceNumber()
{
	return m_cTCProcessThread.CorrelateTCTransferFrameSequenceNumber();
}

BOOL CTCService::CanCorrelateTCTransferFrameSequenceNumber() CONST
{
	return m_cTCProcessThread.CanCorrelateTCTransferFrameSequenceNumber();
}

BOOL CTCService::EnableTestMode(BOOL bEnable)
{
	return m_cTCProcessThread.EnableTestMode(bEnable);
}

BOOL CTCService::IsTestModeEnabled() CONST
{
	return m_cTCProcessThread.IsTestModeEnabled();
}

BOOL CTCService::IsHealthy() CONST
{
	return !m_cTCProcessThread.IsThreadActive() || m_cTCProcessThread.IsThreadHealthy();
}

BOOL CTCService::SetServiceInfo(CONST CByteArray &nInfo)
{
	SERVICEINFO  sServiceInfo;
	CByteArray  nServiceInfo[3];
	CSingleLock  cLock(m_cTCProcessThread.m_pCriticalSection, TRUE);

	if (nInfo.GetSize() >= sizeof(SERVICEINFO))
	{
		for (CopyMemory(&sServiceInfo, nInfo.GetData(), sizeof(SERVICEINFO)); sServiceInfo.cbSize == sizeof(SERVICEINFO) + sServiceInfo.cbServiceInfo[0] + sServiceInfo.cbServiceInfo[1] + sServiceInfo.cbArchivesSettingsInfo && sServiceInfo.cbServiceInfo[0] >= 0 && sServiceInfo.cbServiceInfo[1] >= 0 && sServiceInfo.cbArchivesSettingsInfo >= 0; )
		{
			nServiceInfo[0].SetSize(sServiceInfo.cbServiceInfo[0]);
			nServiceInfo[1].SetSize(sServiceInfo.cbServiceInfo[1]);
			nServiceInfo[2].SetSize(sServiceInfo.cbArchivesSettingsInfo);
			CopyMemory(nServiceInfo[0].GetData(), nInfo.GetData() + sizeof(SERVICEINFO), sServiceInfo.cbServiceInfo[0]);
			CopyMemory(nServiceInfo[1].GetData(), nInfo.GetData() + sizeof(SERVICEINFO) + sServiceInfo.cbServiceInfo[0], sServiceInfo.cbServiceInfo[1]);
			CopyMemory(nServiceInfo[2].GetData(), nInfo.GetData() + sizeof(SERVICEINFO) + sServiceInfo.cbServiceInfo[0] + sServiceInfo.cbServiceInfo[1], sServiceInfo.cbArchivesSettingsInfo);
			if (Unmap(nServiceInfo[0]) && m_cTCProcessThread.Unmap(nServiceInfo[1]) && m_cTCHistoryStore.Unmap(nServiceInfo[2]))
			{
				UpdateTelecommandStatus();
				Update();
				return TRUE;
			}
			break;
		}
	}
	return((!nInfo.GetSize()) ? TRUE : FALSE);
}

BOOL CTCService::GetServiceInfo(CByteArray &nInfo) CONST
{
	SERVICEINFO  sServiceInfo;
	CByteArray  nServiceInfo[3];
	CSingleLock  cLock(m_cTCProcessThread.m_pCriticalSection, TRUE);

	if (Map(nServiceInfo[0]) && m_cTCProcessThread.Map(nServiceInfo[1]) && m_cTCHistoryStore.Map(nServiceInfo[2]))
	{
		nInfo.SetSize((sServiceInfo.cbSize = (INT)(sizeof(SERVICEINFO) + (sServiceInfo.cbServiceInfo[0] = (INT)nServiceInfo[0].GetSize()) + (sServiceInfo.cbServiceInfo[1] = (INT)nServiceInfo[1].GetSize()) + (sServiceInfo.cbArchivesSettingsInfo = (INT)nServiceInfo[2].GetSize()))));
		CopyMemory(nInfo.GetData(), &sServiceInfo, sizeof(SERVICEINFO));
		CopyMemory(nInfo.GetData() + sizeof(SERVICEINFO), nServiceInfo[0].GetData(), nServiceInfo[0].GetSize());
		CopyMemory(nInfo.GetData() + sizeof(SERVICEINFO) + nServiceInfo[0].GetSize(), nServiceInfo[1].GetData(), nServiceInfo[1].GetSize());
		CopyMemory(nInfo.GetData() + sizeof(SERVICEINFO) + nServiceInfo[0].GetSize() + nServiceInfo[1].GetSize(), nServiceInfo[2].GetData(), nServiceInfo[2].GetSize());
		return TRUE;
	}
	return FALSE;
}

BOOL CTCService::UpdateServiceInfo(BOOL bSave)
{
	CSingleLock  cLock(m_cTCProcessThread.m_pCriticalSection, TRUE);

	return((bSave  &&  SaveServiceInfo()) || (!bSave  &&  LoadServiceInfo()));
}

BOOL CTCService::SaveServiceInfo()
{
	BOOL  bSuccess;
	BOOL  bLogEvent;
	UINT  nLogPolicy;
	UINT  nLogReloadCount;
	CString  szLogFileName[2];
	DWORDLONG  dwLogRetention;
	CTimeSpan  tLogRetention;
	CByteArray  nInfo;
	CProfile  cProfile;

	bSuccess = Map(nInfo) && cProfile.SetTelecommandServiceInfo(nInfo);
	bSuccess &= m_cTCHistoryStore.Map(nInfo) && cProfile.SetTelecommandArchivesSettingsInfo(nInfo);
	bSuccess &= m_cTCProcessThread.Map(nInfo) && cProfile.SetTelecommandServiceConfigurationInfo(nInfo);
	bSuccess &= GetLoggingOptions(nLogPolicy, szLogFileName[0], dwLogRetention, tLogRetention, szLogFileName[1], nLogReloadCount, bLogEvent) && cProfile.SetTelecommandServiceLoggingInfo(nLogPolicy, szLogFileName[0], dwLogRetention, tLogRetention, szLogFileName[1], nLogReloadCount, bLogEvent);
	return bSuccess;
}

BOOL CTCService::LoadServiceInfo()
{
	BOOL  bSuccess;
	BOOL  bLogEvent;
	UINT  nLogPolicy;
	UINT  nLogReloadCount;
	CString  szLogFileName[2];
	DWORDLONG  dwLogRetention;
	CTimeSpan  tLogRetention;
	CByteArray  nInfo;
	CProfile  cProfile;

	bSuccess = cProfile.GetTelecommandServiceInfo(nInfo) && Unmap(nInfo);
	bSuccess &= cProfile.GetTelecommandArchivesSettingsInfo(nInfo) && m_cTCHistoryStore.Unmap(nInfo);
	bSuccess &= cProfile.GetTelecommandServiceConfigurationInfo(nInfo) && m_cTCProcessThread.Unmap(nInfo);
	bSuccess &= (cProfile.GetTelecommandServiceLoggingInfo(nLogPolicy, szLogFileName[0], dwLogRetention, tLogRetention, szLogFileName[1], nLogReloadCount, bLogEvent) && SetLoggingOptions(nLogPolicy, szLogFileName[0], dwLogRetention, tLogRetention, szLogFileName[1], nLogReloadCount, bLogEvent)) || InitializeLoggingOptions();
	return bSuccess;
}

BOOL CTCService::Map(CByteArray &nInfo) CONST
{
	INT  cbData;
	DATA  sData;
	CByteArray  nDevicesData;
	CTCUplinkDevices  pDevices;
	CSingleLock  cLock(m_cTCProcessThread.m_pCriticalSection, TRUE);

	sData.cbDevicesData = (GetTCUplinkDevices(pDevices) >= 0 && pDevices.Map(nDevicesData)) ? (INT)nDevicesData.GetSize() : -1;
	for (nInfo.SetSize((sData.cbSize = sizeof(DATA) + max(sData.cbDevicesData, 0))); nInfo.GetSize() == sData.cbSize && sData.cbDevicesData >= 0; )
	{
		CopyMemory(nInfo.GetData(), &sData, sizeof(DATA));
		CopyMemory(nInfo.GetData() + (cbData = sizeof(DATA)), nDevicesData.GetData(), sData.cbDevicesData);
		return TRUE;
	}
	return FALSE;
}

BOOL CTCService::Unmap(CONST CByteArray &nInfo)
{
	INT  cbData;
	DATA  sData;
	CByteArray  nDevicesData;
	CTCUplinkDevices  pDevices;
	CSingleLock  cLock(m_cTCProcessThread.m_pCriticalSection, TRUE);

	for (CopyMemory(&sData, nInfo.GetData(), (nInfo.GetSize() >= sizeof(DATA)) ? sizeof(DATA) : 0); nInfo.GetSize() >= sizeof(DATA) && nInfo.GetSize() == sData.cbSize && sData.cbSize == sizeof(DATA) + sData.cbDevicesData && sData.cbDevicesData >= 0; )
	{
		for (nDevicesData.SetSize(sData.cbDevicesData), CopyMemory(nDevicesData.GetData(), nInfo.GetData() + (cbData = sizeof(DATA)), sData.cbDevicesData); pDevices.Unmap(nDevicesData); ) return SetTCUplinkDevices(pDevices);
		break;
	}
	return((!nInfo.GetSize()) ? SetTCUplinkDevices(pDevices) : FALSE);
}

BOOL CTCService::Lock()
{
	return m_cTCProcessThread.m_pCriticalSection->Lock();
}

BOOL CTCService::Unlock()
{
	return m_cTCProcessThread.m_pCriticalSection->Unlock();
}
